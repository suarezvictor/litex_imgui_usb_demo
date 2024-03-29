#include "lite_fb.h"
#include <string.h>


/*
 * fb_clear(), fb_fillrect() and fb_fill_poly() can be made *much faster* by 
 * adding a very crude "blitter" to the LiteX SOC. The Blitter can fill a
 * contiguous zone of memory with a 32 bit value using DMA (much faster than
 * with the CPU !). When the Blitter is declared, then CSR_BLITTER_BASE is
 * defined in <generated/csr.h>. Else a (much slower) software fallback is
 * used.
 * 
 * The Blitter can be added to 
 *                litex-boards/litex_boards/targets/radiona_ulx3s.py:
 * 
 * class Blitter(Module, AutoCSR):
 *     def __init__(self,port): # port = self.sdram.crossbar.get_port()
 *         self._value = CSRStorage(32)
 *         from litedram.frontend.dma import LiteDRAMDMAWriter
 *         dma_writer = LiteDRAMDMAWriter(
 *             port=port,fifo_depth=16,fifo_buffered=False,with_csr=True
 *         )
 *         self.submodules.dma_writer = dma_writer
 *         self.comb += dma_writer.sink.data.eq(self._value.storage)
 *         self.comb += dma_writer.sink.valid.eq(1)
 * 
 *  ....
 * 
 *     if with_video_framebuffer:
 *          self.add_video_framebuffer(
 *              phy=self.videophy, timings="640x480@75Hz", 
 *              format="rgb888", clock_domain="hdmi"
 *          )
 *          blitter = Blitter(port=self.sdram.crossbar.get_port(mode="write", data_width=32))
 *          self.submodules.blitter = blitter
 *  ...
 */ 
#ifndef CSR_VIDEO_FRAMEBUFFER_BASE
void     fb_set_read_page(uint32_t addr) {}
void     fb_set_write_page(uint32_t addr) {}
int      fb_init(void) { return 0; }
void     fb_on(void) {}
void     fb_off(void) {}
void     fb_clear(void) {}

#else

#define FB_MIN(x,y) ((x) < (y) ? (x) : (y))
#define FB_MAX(x,y) ((x) > (y) ? (x) : (y))
#define FB_SGN(x)   (((x) > (0)) ? 1 : ((x) ? -1 : 0))

uint32_t* fb_base = (uint32_t*)FB_PAGE1;

#ifdef CSR_VIDEO_FRAMEBUFFER_BASE

void fb_set_read_page(uint32_t addr) {
    video_framebuffer_dma_base_write(addr);
}

void fb_set_write_page(uint32_t addr) {
    fb_base = (uint32_t*)addr;
}

void fb_on(void) {
    flush_l2_cache();    
    video_framebuffer_vtg_enable_write(1);
    video_framebuffer_dma_enable_write(1);
}

void fb_off(void) {
    video_framebuffer_vtg_enable_write(0);
    video_framebuffer_dma_enable_write(0);
}


int fb_init(void) {
#ifndef LITEX_SIMULATION
    fb_off(); //simulation needs the video always on to determine resolution
#endif
    fb_set_read_page(FB_PAGE1);
    fb_set_write_page(FB_PAGE1);
    fb_clear();
    fb_on();
    fb_set_cliprect(0,0,FB_WIDTH-1,FB_HEIGHT-1);
    fb_set_poly_mode(FB_POLY_FILL);
    fb_set_poly_culling(FB_POLY_NO_CULLING);
    return 1;
}

void fb_clear(void) {
#ifdef CSR_BLITTER_BASE
    /* 
     * If blitter is available, clear screen using DMA
     * transfer (much much faster !) 
     */ 
    blitter_value_write(0x000000);
    blitter_dma_writer_base_write((uint32_t)(fb_base));
    blitter_dma_writer_length_write(FB_WIDTH*FB_HEIGHT*VIDEO_FRAMEBUFFER_DEPTH/8);
    blitter_dma_writer_enable_write(1);
    while(!blitter_dma_writer_done_read());
    blitter_dma_writer_enable_write(0);    
#else
    memset((void*)fb_base, 0, FB_WIDTH*FB_HEIGHT*VIDEO_FRAMEBUFFER_DEPTH/8);
#endif    
}

#else

void     fb_set_read_page(uint32_t addr) {}
void     fb_set_write_page(uint32_t addr) {}
int      fb_init(void) { return 0; }
void     fb_on(void) {}
void     fb_off(void) {}
void     fb_clear(void) {}

#endif

/*****************************************************************************/

void fb_set_dual_buffering(int doit) {
   if(doit) {
      fb_set_write_page(FB_PAGE2);
      fb_clear();
   } else {
      fb_set_read_page(FB_PAGE1);
      fb_set_write_page(FB_PAGE1);
   }
}

void fb_swap_buffers(void) {
   flush_l2_cache(); // There may be some pixels still in l2 and not in SDRAM.
   if((uint32_t)fb_base == FB_PAGE1) {
      fb_set_read_page(FB_PAGE1);
      fb_set_write_page(FB_PAGE2);
   } else {
      fb_set_read_page(FB_PAGE2);
      fb_set_write_page(FB_PAGE1);
   }
}

/******************************************************************************/

static int fb_clip_x1 = 0;
static int fb_clip_y1 = 0;
static int fb_clip_x2 = FB_WIDTH-1;
static int fb_clip_y2 = FB_HEIGHT-1;

void fb_set_cliprect(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
    fb_clip_x1 = x1;
    fb_clip_y1 = y1;
    fb_clip_x2 = x2;
    fb_clip_y2 = y2;    
}

/******************************************************************************/

/**
 * \brief Draws a line using DMA transfer.
 * \details Does not wait for DMA transfer completion.
 * \param[in] pix_start address of the first pixel
 * \param[in] len number of pixels
 * \param[in] RGB color
 */ 
static inline int fb_hline_no_wait_dma(uint32_t* pix_start, uint32_t len, uint32_t RGB) {
#ifdef CSR_BLITTER_BASE
#if CSR_BLITTER_VALUE_SIZE == 1
    blitter_dma_writer_base_write((uint32_t)(pix_start));
    blitter_dma_writer_length_write(len*4);
    blitter_value_write(RGB);
    blitter_dma_writer_enable_write(1);
    return 1;
#elif CSR_BLITTER_VALUE_SIZE == 2
     //this is an optimized implementations that allows DMA of two pixels and
     //correct the missing parts on the left and right, in a chache-aware way
     //TODO: best implementation would be to DMA single-pixel at left part,
     //simultaneously DMA single-pixel at right part, and also simultaneously
     //the middle part at the widest possible bus size

#ifndef CPU_CACHE_SIZE
#define CPU_CACHE_SIZE 16 //in bytes
#warning CPU_CACHE_SIZE should match SoC definition
#endif

#define CACHE_MASK ((CPU_CACHE_SIZE/sizeof(*pix_start))-1)
    //write left misaligned part
    for(;;)
    {
      if(len == 0) return 0;
      uint8_t misalingment = ((intptr_t) pix_start) & (CACHE_MASK*sizeof(*pix_start));
      if(!misalingment) break;
      
      *pix_start++ = RGB; //0xFF0000;
      --len;
    }
    
    uint32_t masked_len = len & ~CACHE_MASK;
    
    blitter_dma_writer_base_write((uint32_t)(pix_start));
    if(masked_len)
    {
      blitter_value_write(RGB | ((uint64_t)RGB << 32));
      blitter_dma_writer_length_write(masked_len*sizeof(*pix_start));
      blitter_dma_writer_enable_write(1);
    }
    
    //write right misaligned part
    uint32_t *pix_end = pix_start + len;
    pix_start += masked_len;
    while(pix_start != pix_end)
      *pix_start++ = RGB; //0xFF0000;
      
    return masked_len != 0;

#else
#error unsupported bilitter width
#endif    
#else
    for(uint32_t i=0; i<len; ++i) {
	*pix_start = RGB;
	++pix_start;
    }
    return 1;
#endif    
}

/**
 * \brief Waits for DMA transfer completion.
 * \see fb_hline_no_wait_dma()
 * \details With fb_hline_no_wait_dma(), can be
 *   used to overlap computations between 
 *   initiation of DMA transfer and its completion.
 */ 
static inline void fb_hline_wait_dma(void) {
#ifdef CSR_BLITTER_BASE   
    while(!blitter_dma_writer_done_read());
    blitter_dma_writer_enable_write(0);    
#endif
}

/**
 * \brief Draws a line using DMA transfer.
 * \details Waits for DMA transfer completion
 * \param[in] pix_start address of the first pixel
 * \param[in] len number of pixels
 * \param[in] RGB color
 */ 
static inline void fb_hline(uint32_t* pix_start, uint32_t len, uint32_t RGB) {
   if(fb_hline_no_wait_dma(pix_start, len, RGB))
     fb_hline_wait_dma();
}

void fb_fillrect(
    uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t RGB
) {
    if(x1>x2 || y1>y2) return;
    
    uint32_t w = x2-x1+1;
    uint32_t* line_ptr = fb_pixel_address(x1,y1);
    for(int y=y1; y<=y2; ++y) {
	fb_hline(line_ptr,w,RGB);
	line_ptr += FB_WIDTH;
    }
}

/******************************************************************************/

#define INSIDE 0
#define LEFT   1
#define RIGHT  2
#define BOTTOM 4
#define TOP    8

#define code(x,y) ((x) < fb_clip_x1) | (((x) > fb_clip_x2)<<1) | (((y) < fb_clip_y1)<<2) | (((y) > fb_clip_y2)<<3) 

void fb_line(int x1, int y1, int x2, int y2, uint32_t RGB) {
   
    /* Cohen-Sutherland line clipping. */
    int code1 = code(x1,y1);
    int code2 = code(x2,y2);
    int codeout;
    /* Bresenham */
    int x,y,dx,dy,sx,sy;
    /* Pixel pointer */
    uint8_t* pix_ptr;
    int sx_ptr;
    int sy_ptr;
    
    for(;;) {
	/* Both points inside. */
	if(code1 == 0 && code2 == 0) {
	    break;
	}

	/* No point inside. */
	if(code1 & code2) {
	    return;
	}

	/* One of the points is outside. */
	codeout = code1 ? code1 : code2;

	/* Compute intersection. */
	if (codeout & TOP) { 
	    x = x1 + (x2 - x1) * (fb_clip_y2 - y1) / (y2 - y1); 
	    y = fb_clip_y2; 
	} else if (codeout & BOTTOM) { 
	    x = x1 + (x2 - x1) * (fb_clip_y1 - y1) / (y2 - y1); 
	    y = fb_clip_y1; 
	}  else if (codeout & RIGHT) { 
	    y = y1 + (y2 - y1) * (fb_clip_x2 - x1) / (x2 - x1); 
	    x = fb_clip_x2; 
	} else if (codeout & LEFT) { 
	    y = y1 + (y2 - y1) * (fb_clip_x1 - x1) / (x2 - x1); 
	    x = fb_clip_x1; 
	} 
	
	/* Replace outside point with intersection. */
	if (codeout == code1) { 
	    x1 = x; 
	    y1 = y;
	    code1 = code(x1,y1);
	} else { 
	    x2 = x; 
	    y2 = y;
	    code2 = code(x2,y2);
	}
    }
   
    /* Bresenham line drawing. */
    dy = y2 - y1;
    sy = 1;
    if(dy < 0) {
	sy = -1;
	dy = -dy;
    }

    dx = x2 - x1;
    sx = 1;
    if(dx < 0) {
	sx = -1;
	dx = -dx;
    }

    // Pointer increments for x,y displacements
    sx_ptr = sx*sizeof(uint32_t);
    sy_ptr = sy*sizeof(uint32_t)*FB_WIDTH;
   
    // Next line equivalent to: x = x1; y = y1;
    pix_ptr = (uint8_t*)(fb_base + y1 * FB_WIDTH + x1);
   
    // Instead of updating x,y and computing pixel pointer
    // from x,y, we update pixel pointer (gains a few ticks
    // per pixel).
    // 
    //   fb_set_pixel(x,y,RGB) --> *(uint32_t*)pix_ptr = RGB
    //   x += sx               --> pix_ptr += sx_ptr
    //   y += sy               --> pix_ptr += sy_ptr
   
    if(dy > dx) {
	int ex = (dx << 1) - dy;
	for(int u=0; u<dy; u++) {
	   
	    // Next two lines equivalent to:
	    //  fb_setpixel(x,y,RGB);
	    //  y += sy;
	    *(uint32_t*)pix_ptr = RGB;
	    pix_ptr += sy_ptr;
	   
	    while(ex >= 0)  {
	       
	        // Next two lines equivalent to:	       
		//  fb_setpixel(x,y,RGB);		
		//  x += sx;
		*(uint32_t*)pix_ptr = RGB;
		pix_ptr += sx_ptr;
		ex -= dy << 1;
	    }
	    ex += dx << 1;
	}
    } else {
	int ey = (dy << 1) - dx;
	for(int u=0; u<dx; u++) {
	   
	    // Next two lines equivalent to:
	    //  fb_setpixel(x,y,RGB);
	    //  x += sx;
	    *(uint32_t*)pix_ptr = RGB;
	    pix_ptr += sx_ptr;
	   
	    while(ey >= 0) {
	        // Next two lines equivalent to:
		//   fb_setpixel(x,y,RGB);
		//   y += sy;
		*(uint32_t*)pix_ptr = RGB;
		pix_ptr += sy_ptr;
		ey -= dx << 1;
	    }
	    ey += dy << 1;
	}
    }
}

/************************************************************************************/

static PolyMode fb_poly_mode = FB_POLY_FILL;
void fb_set_poly_mode(PolyMode mode) { fb_poly_mode = mode; }

static PolyCulling fb_poly_culling = FB_POLY_NO_CULLING;
void fb_set_poly_culling(PolyCulling culling) { fb_poly_culling = culling; }

/************************************************************************************/


/** 
 * \brief Clips a polygon by a half-plane.
 * \param[in] number of vertices of the input polygon.
 * \param[in] buff1 vertices of the input polygon.
 * \param[out] buff2 vertices of the resulting polygon.
 * \param[in] a , b , c equation of the half-plane: ax + by + c >= 0
 * \return number of vertices in resulting polygon.
 */
static int clip_H(
    int nb_pts, int* buff1, int* buff2, int a, int b, int c
) {
    if(nb_pts == 0) {
	return 0;
    }

    if(nb_pts == 1) {
	if(a*buff1[0] + b*buff1[1] + c >= 0) {
	    buff2[0] = buff1[0];
	    buff2[1] = buff1[1];
	    return 1;
	} else {
	    return 0;
	}
    }

    int nb_result = 0;
    int prev_x = buff1[2*(nb_pts-1)];
    int prev_y = buff1[2*(nb_pts-1)+1];
    int prev_status = FB_SGN(a*prev_x + b*prev_y +c);

    for(int i=0; i<nb_pts; ++i) {
	int x = buff1[2*i];
	int y = buff1[2*i+1];
	int status = FB_SGN(a*x + b*y + c);
	if(status != prev_status && status != 0 && prev_status != 0) {

	    /*
	     * Remember, femtorv32 does not always have hardware mul,
	     * so we replace the following code with two switches
	     * (a and b take values in -1,0,1, no need to mul).
	     * int t_num   = -a*prev_x-b*prev_y-c;
	     * int t_denom = a*(x - prev_x) + b*(y - prev_y);
	     */

	    int t_num = -c;
	    int t_denom = 0;
	    
	    switch(a) {
	    case -1:
		t_num += prev_x;
		t_denom -= (x - prev_x);
		break;
	    case  1:
		t_num -= prev_x;
		t_denom += (x - prev_x);
		break;
	    }

	    switch(b) {
	    case -1:
		t_num += prev_y;
		t_denom -= (y - prev_y);
		break;
	    case  1:
		t_num -= prev_y;
		t_denom += (y - prev_y);
		break;
	    }
	    
	    int Ix = prev_x + t_num * (x - prev_x) / t_denom;
	    int Iy = prev_y + t_num * (y - prev_y) / t_denom;
	    buff2[2*nb_result]   = Ix;
	    buff2[2*nb_result+1] = Iy;
	    ++nb_result;
	}
	if(status >= 0) {
	    buff2[2*nb_result]   = x;
	    buff2[2*nb_result+1] = y;
	    ++nb_result;
	}
	prev_x = x;
	prev_y = y;
	prev_status = status;
    }

    return nb_result;
}

/**
 * \brief Clips a polygon by the screen.
 * \param[in] number of vertices of the input polygon.
 * \param[in,out] poly vertices of the polygon.
 * \return number of vertices in the result polygon.
 */
static int fb_clip(int nb_pts, int** poly) {
    static int  buff1[20];    
    int  buff2[20];
    nb_pts = clip_H(nb_pts, *poly, buff2, 1, 0, fb_clip_x1);
    nb_pts = clip_H(nb_pts, buff2, buff1,-1, 0, fb_clip_x2);
    nb_pts = clip_H(nb_pts, buff1, buff2, 0, 1, fb_clip_y1);
    nb_pts = clip_H(nb_pts, buff2, buff1, 0,-1, fb_clip_y2);
    *poly = buff1;
    return nb_pts;
}

#if 0 //disable poly until needed, to avoid issues with required buffers
void fb_fill_poly(uint32_t nb_pts, int* points, uint32_t RGB) {
    static uint32_t x_left[FB_HEIGHT];
    static uint32_t x_right[FB_HEIGHT];

    /* determine miny, maxy */
    int clockwise = 0;
    int minx =  10000;
    int maxx = -10000;
    int miny =  10000;
    int maxy = -10000;
   
    for(int i=0; i<nb_pts; ++i) {
	int x = points[2*i];
	int y = points[2*i+1];
	minx = FB_MIN(minx,x);
	maxx = FB_MAX(maxx,x);
	miny = FB_MIN(miny,y);
	maxy = FB_MAX(maxy,y);
    }

    /* Culling */
    if(fb_poly_culling != FB_POLY_NO_CULLING) {
       for(int i1=0; i1<nb_pts; ++i1) {
	  int i2=(i1==nb_pts-1) ? 0 : i1+1;
	  int i3=(i2==nb_pts-1) ? 0 : i2+1;
	  int x1 = points[2*i1];
	  int y1 = points[2*i1+1];
	  int dx1 = points[2*i2]   - x1;
	  int dy1 = points[2*i2+1] - y1;
	  int dx2 = points[2*i3]   - x1;
	  int dy2 = points[2*i3+1] - y1;
	  clockwise += dx1 * dy2 - dx2 * dy1;
       }
       if((fb_poly_culling == FB_POLY_CW) && (clockwise < 0)) {
	  return;
       }
       if((fb_poly_culling == FB_POLY_CCW) && (clockwise > 0)) {
	  return;
       }
    }
   
    /* Clipping */
    if((minx < fb_clip_x1) || (miny < fb_clip_y1) || (maxx > fb_clip_x2) || (maxy > fb_clip_y2)) {
	nb_pts = fb_clip(nb_pts, (int**)&points);
	miny =  10000;
	maxy = -10000;
	for(int i1=0; i1<nb_pts; ++i1) {
	    int y1 = points[2*i1+1];
	    miny = FB_MIN(miny,y1);
	    maxy = FB_MAX(maxy,y1);
	}
    }

    /* Determine x_left and x_right for each scaline */
    // Note: x_left and x_right may be swapped depending
    // on polygon orientation (we no longer compute orientation
    // systematically, and swap line extremities instead). 
    // Extremities test and swapping is overlapped with previous
    // line's DMA transfer (costs nothing).
    for(int i1=0; i1<nb_pts; ++i1) {
	int i2=(i1==nb_pts-1) ? 0 : i1+1;

	int x1 = points[2*i1];
	int y1 = points[2*i1+1];
	int x2 = points[2*i2];
	int y2 = points[2*i2+1];

	if(fb_poly_mode == FB_POLY_LINES) {
	    fb_line(x1,y1,x2,y2,RGB);
	    continue;
	}

        // uint32_t* x_buffer = ((clockwise > 0) ^ (y2 > y1)) ? x_left : x_right;
	// No need to consult clockwise: we swap extremities in the end if needed
	//  (need the test anyway in the case there is a non-convex polygon)
        uint32_t* x_buffer = (y2 > y1) ? x_left : x_right;
       
	int dx = x2 - x1;
	int sx = 1;
	int dy = y2 - y1;
	int sy = 1;
	int x = x1;
	int y = y1;
	int ex;
	
	if(dx < 0) {
	    sx = -1;
	    dx = -dx;
	}
	
	if(dy < 0) {
	    sy = -1;
	    dy = -dy;
	}

	if(y1 == y2) {
	  x_left[y1]  = FB_MIN(x1,x2);
	  x_right[y1] = FB_MAX(x1,x2);
	  continue;
	}

	ex = (dx << 1) - dy;

	for(int u=0; u <= dy; ++u) {
    	    x_buffer[y] = x; 
	    y += sy;
	    while(ex >= 0) {
		x += sx;
		ex -= dy << 1;
	    }
	    ex += dx << 1;
	}
    }

    if(fb_poly_mode == FB_POLY_LINES) {    
	return;
    }

    uint32_t* line_ptr = (uint32_t*)(fb_base) + miny * FB_WIDTH;
    for(int y = miny; y <= maxy; ++y) {
	int x1 = x_left[y];
	int x2 = x_right[y];
       
        /* swap x1,x2 (may happen with non-convex polygons) */
        if(x2 < x1) { 
	   x1 = x1 ^ x2;
	   x2 = x2 ^ x1;
	   x1 = x1 ^ x2;
	}
       
        /* wait end of DMA transfer for previous line */
        if(y != miny) {
	   fb_hline_wait_dma();
	}
       
        /* 
	 * Initiate DMA transfer for current line. Next 
	 * line fetch and x1,x2 swap are overlapped with
	 * DMA transfer.
	 */ 
        fb_hline_no_wait_dma(line_ptr+x1, x2-x1+1, RGB);
	line_ptr += FB_WIDTH;
    }
   
    /* Wait end of DMA transfer for last line. */
    fb_hline_wait_dma();
}
#endif

#define int_swap(a, b) { a = a ^ b; b = b ^ a; a = a ^ b; }

void fb_horizline(int x1, int x2, int y, uint32_t c)
{
    if(x2 < x1) int_swap(x1, x2);  

    uint32_t* line_ptr = fb_pixel_address(x1,y);
#if 1
    for(int x=x1; x<=x2; ++x) //this seems faster
	 *line_ptr++ = c;
#else
	fb_hline(line_ptr, x2-x1+1, c);
#endif
}

void fb_filltriangle(float v0x, float v0y, float v1x, float v1y, float v2x, float v2y, uint32_t c)
{
    //https://www.codegrepper.com/code-examples/c/how+to+fill+a+triangle+in+c
    int x1 = v0x, y1 = v0y, x2 = v1x, y2 = v1y, x3 = v2x, y3 = v2y;

	int t1x, t2x, y, minx, maxx, t1xp, t2xp;
	int changed1 = 0;
	int changed2 = 0;
	int signx1, signx2, dx1, dy1, dx2, dy2;
	int e1, e2;

    // Sort vertices
	if (y1 > y2) { int_swap(y1,y2); int_swap(x1,x2); }
	if (y1 > y3) { int_swap(y1,y3); int_swap(x1,x3); }
	if (y2 > y3) { int_swap(y2,y3); int_swap(x2,x3); }

	t1x = t2x = x1; 
    y = y1;   // Starting points

	dx1 = (x2 - x1); if(dx1<0) { dx1=-dx1; signx1=-1; } else signx1=1;
	dy1 = (y2 - y1);
 
	dx2 = (x3 - x1); if(dx2<0) { dx2=-dx2; signx2=-1; } else signx2=1;
	dy2 = (y3 - y1);
	
	if (dy1 > dx1) {   // swap values
        int_swap(dx1,dy1);
		changed1 = 1;
	}
	if (dy2 > dx2) {   // swap values
        int_swap(dy2,dx2);
		changed2 = 1;
	}
	
	e2 = (dx2>>1);
    // Flat top, just process the second half
    if(y1==y2) goto next;
    e1 = (dx1>>1);
	
	for (int i = 0; i < dx1;) {
		t1xp=0; t2xp=0;
		if(t1x<t2x) { minx=t1x; maxx=t2x; }
		else		{ minx=t2x; maxx=t1x; }
        // process first line until y value is about to change
		while(i<dx1) {
			i++;			
			e1 += dy1;
	   	   	while (e1 >= dx1) {
				e1 -= dx1;
   	   	   	   if (changed1) t1xp=signx1;//t1x += signx1;
				else          goto next1;
			}
			if (changed1) break;
			else t1x += signx1;
		}
	// Move line
	next1:
        // process second line until y value is about to change
		while (1) {
			e2 += dy2;		
			while (e2 >= dx2) {
				e2 -= dx2;
				if (changed2) t2xp=signx2;//t2x += signx2;
				else          goto next2;
			}
			if (changed2)     break;
			else              t2x += signx2;
		}
	next2:
		if(minx>t1x) minx=t1x;
		if(minx>t2x) minx=t2x;
		if(maxx<t1x) maxx=t1x;
		if(maxx<t2x) maxx=t2x;
	   	fb_horizline(minx, maxx, y, c);    // Draw line from min to max points found on the y
		// Now increase y
		if(!changed1) t1x += signx1;
		t1x+=t1xp;
		if(!changed2) t2x += signx2;
		t2x+=t2xp;
    	y += 1;
		if(y==y2) break;
		
   }
	next:
	// Second half
	dx1 = (x3 - x2); if(dx1<0) { dx1=-dx1; signx1=-1; } else signx1=1;
	dy1 = (y3 - y2);
	t1x=x2;
 
	if (dy1 > dx1) {   // swap values
        int_swap(dy1,dx1);
		changed1 = 1;
	} else changed1 = 0;
	
	e1 = (dx1>>1);
	
	for (int i = 0; i<=dx1; i++) {
		t1xp=0; t2xp=0;
		if(t1x<t2x) { minx=t1x; maxx=t2x; }
		else		{ minx=t2x; maxx=t1x; }
	    // process first line until y value is about to change
		while(i<dx1) {
    		e1 += dy1;
	   	   	while (e1 >= dx1) {
				e1 -= dx1;
   	   	   	   	if (changed1) { t1xp=signx1; break; }//t1x += signx1;
				else          goto next3;
			}
			if (changed1) break;
			else   	   	  t1x += signx1;
			if(i<dx1) i++;
		}
	next3:
        // process second line until y value is about to change
		while (t2x!=x3) {
			e2 += dy2;
	   	   	while (e2 >= dx2) {
				e2 -= dx2;
				if(changed2) t2xp=signx2;
				else          goto next4;
			}
			if (changed2)     break;
			else              t2x += signx2;
		}	   	   
	next4:

		if(minx>t1x) minx=t1x;
		if(minx>t2x) minx=t2x;
		if(maxx<t1x) maxx=t1x;
		if(maxx<t2x) maxx=t2x;
	   	fb_horizline(minx, maxx, y, c);    // Draw line from min to max points found on the y
		// Now increase y
		if(!changed1) t1x += signx1;
		t1x+=t1xp;
		if(!changed2) t2x += signx2;
		t2x+=t2xp;
    	y += 1;
		if(y>y3) return;
	}
}


/******************************************************************************/
#endif // CSR_VIDEO_FRAMEBUFFER_BASE


