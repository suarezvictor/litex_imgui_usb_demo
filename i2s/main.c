// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "irq.h"
#include "uart.h"
#include "litex_i2s.h"

#define FAST_CODE __attribute__ ((section (".fast_text")))
#define FAST_DATA __attribute__ ((section (".fast_data")))

//NOTE: this is from (C) Julian Kemmerer, LICENSE GPL 3.0
// https://github.com/JulianKemmerer/PipelineC/blob/master/examples/cordic.h

// http://www.dcs.gla.ac.uk/~jhw/cordic/     **Slightly modified
//Cordic in 32 bit signed fixed point math
//Function is valid for arguments in range -pi/2 -- pi/2
//for values pi/2--pi: value = half_pi-(theta-half_pi) and similarly for values -pi---pi/2
//
// 1.0 = 1073741824
// 1/k = 0.6072529350088812561694
// pi = 3.1415926535897932384626
//Constants
#define CORDIC_1K 0x26DD3B6A
#define CORDIC_MUL 1073741824.000000
#define CORDIC_NTAB 32
#define CORDIC_N_ITER 32 //can be lower

// Cordic limited to int32 fixed point -pi/2 -- pi/2
typedef struct
{
	int32_t s;
	int32_t c;
} cordic_fixed32_t;

int32_t FAST_DATA cordic_ctab[CORDIC_NTAB] = {0x3243F6A8, 0x1DAC6705, 0x0FADBAFC, 0x07F56EA6, 0x03FEAB76, 0x01FFD55B, 
0x00FFFAAA, 0x007FFF55, 0x003FFFEA, 0x001FFFFD, 0x000FFFFF, 0x0007FFFF, 0x0003FFFF, 
0x0001FFFF, 0x0000FFFF, 0x00007FFF, 0x00003FFF, 0x00001FFF, 0x00000FFF, 0x000007FF, 
0x000003FF, 0x000001FF, 0x000000FF, 0x0000007F, 0x0000003F, 0x0000001F, 0x0000000F, 
0x00000008, 0x00000004, 0x00000002, 0x00000001, 0x00000000};

static inline cordic_fixed32_t FAST_CODE cordic_fixed32_n32(int32_t theta)
{
  int32_t k, d, tx, ty, tz;
  int32_t x = CORDIC_1K;
  int32_t y = 0;
  int32_t z = theta;
  for (k=0; k<CORDIC_N_ITER; k=k+1)
  {
    d = z>>31;
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


// Cordic limited to float -pi/2 -- pi/2 per fixed point cordic implementation
typedef struct { float s, c; } cordic_float_t;

static inline cordic_float_t FAST_CODE cordic_float_fixed32_n32(float theta)
{
	// Convert float to fixed
	int32_t theta_fixed = theta*CORDIC_MUL;
	
	// Do fixed math
	cordic_fixed32_t fixed_result = cordic_fixed32_n32(theta_fixed);

	// Convert fixed to float
	cordic_float_t rv;
	rv.s = ((float)fixed_result.s)*(1.0/CORDIC_MUL);
	rv.c = ((float)fixed_result.c)*(1.0/CORDIC_MUL);
	return rv;
}

static inline float FAST_CODE fast_sin(float x) //0 to 2*PI
{
  if(x < M_PI/2) 
    return cordic_float_fixed32_n32(x).s;
  if(x < M_PI) 
    return cordic_float_fixed32_n32(x-M_PI/2).c;
  return -cordic_float_fixed32_n32(x-3*M_PI/2).c;
}

int FAST_CODE synth(unsigned count)
{
	static float wt = 0;
	const int bits = 24; //i2s_tx_get_bits();
 	for(size_t i = 0; i < count; i+=2)
	{
	  wt += 1000.f*2*M_PI/44100;
	  if(wt > 2*M_PI) wt -= 2*M_PI; //angle wrapping
	  static const float amp = ((1<<(bits-1))-1.f);
	  int32_t sample = amp*fast_sin(wt);
	  i2s_tx_enqueue_sample(sample); //left
	  i2s_tx_enqueue_sample(sample); //right
	}
	//if(wt > 5*2*M_PI)
	//  return -1; //request pause
	return count;
}

int i2s_audio_send_cb(unsigned count)
{
  return synth(count);
}

void i2s_demo(void)
{
    unsigned freq = i2s_tx_frequency();
    unsigned channels = i2s_tx_get_default_channels();
    unsigned bits = i2s_tx_get_bits();
    printf("Audio frequency: %d, channels %d, bits %d\n", freq, channels, bits);

    i2s_tx_start();
    while(i2s_is_playing())
    {
      unsigned count = i2s_tx_played_count();
      printf("Played samples: %d, elapsed time: %ds\n", count, count/freq/channels);
    }
    i2s_tx_stop();
    printf("Stopped\n");

    for(;;); //keeps interrupts enabled for flushing uart data
}

int main(int argc, char **argv) {
    irq_setmask(0);
    irq_setie(1);

    uart_init();
    i2s_demo();
    
    irq_setie(0);
    irq_setmask(~0);
}

