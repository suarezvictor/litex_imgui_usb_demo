#ifndef __CORDIC_H__
#define __CORDIC_H__

// (C) Julian Kemmerer, LICENSE GPL 3.0
// https://github.com/JulianKemmerer/PipelineC/blob/master/examples/cordic.h
// (C) Victor Suarez Rovere
// based on http://www.dcs.gla.ac.uk/~jhw/cordic/

//Cordic in 32 bit signed fixed point math
//Function is valid for arguments in range -pi/2 -- pi/2
//for values pi/2--pi: value = half_pi-(theta-half_pi) and similarly for values -pi---pi/2
//
// 1.0 = 1073741824
// 1/k = 0.6072529350088812561694
// pi = 3.1415926535897932384626
//Constants
#define CORDIC_1K 0x26DD3B6A
#define CORDIC_SHIFT 30
#define CORDIC_HALF_PI (uint32_t)((1<<(CORDIC_SHIFT-1))*M_PI)
#define CORDIC_NTAB 32
#define CORDIC_N_ITER 32 //can be lower

// Cordic limited to int32 fixed point -pi/2 -- pi/2
typedef struct
{
	int32_t s;
	int32_t c;
} cordic_fixed32_t;

static int32_t cordic_ctab[CORDIC_NTAB] = {0x3243F6A8, 0x1DAC6705, 0x0FADBAFC, 0x07F56EA6, 0x03FEAB76, 0x01FFD55B, 
0x00FFFAAA, 0x007FFF55, 0x003FFFEA, 0x001FFFFD, 0x000FFFFF, 0x0007FFFF, 0x0003FFFF, 
0x0001FFFF, 0x0000FFFF, 0x00007FFF, 0x00003FFF, 0x00001FFF, 0x00000FFF, 0x000007FF, 
0x000003FF, 0x000001FF, 0x000000FF, 0x0000007F, 0x0000003F, 0x0000001F, 0x0000000F, 
0x00000008, 0x00000004, 0x00000002, 0x00000001, 0x00000000};

static inline cordic_fixed32_t cordic_fixed32_n32(int32_t theta)
{
  int32_t k, d, tx, ty, tz;
  int32_t x = CORDIC_1K;
  int32_t y = 0;
  int32_t z = theta;
  for (k=0; k<CORDIC_N_ITER; k=k+1)
  {
    d = z>>31; //sign extends
    //get sign. for other architectures, you might want to use the more portable version
    //d = z>=0 ? 0 : -1;
    tx = x - (((y>>k) ^ d) - d);
    ty = y + (((x>>k) ^ d) - d);
    tz = z - ((cordic_ctab[k] ^ d) - d);
    x = tx; y = ty; z = tz;
  }  
  
  cordic_fixed32_t rv = {y, x};
  return rv;
}

static inline int32_t cordic_sin(int64_t x) //0 to 2*PI
{
  if(x < CORDIC_HALF_PI) 
    return cordic_fixed32_n32(x).s;
  if(x < 2*CORDIC_HALF_PI) 
    return cordic_fixed32_n32(x-CORDIC_HALF_PI).c;
  return -cordic_fixed32_n32((x-CORDIC_HALF_PI)-2*CORDIC_HALF_PI).c; //succesive substraction to avoud overflows
}

#endif //__CORDIC_H__
