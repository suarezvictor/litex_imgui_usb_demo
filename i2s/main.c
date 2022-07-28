// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "irq.h"
#include "uart.h"
#include "litex_i2s.h"

#define FAST_CODE __attribute__ ((section (".fast_text")))

//https://www.gamedev.net/forums/topic/621589-extremely-fast-sin-approximation/
double FAST_CODE fast_sin(double x) {
int k;
double y;
double z;

z = x;
z *= 0.3183098861837907;
z += 6755399441055744.0;
k = *((int *) &z);
z = k;
z *= 3.1415926535897932;
x -= z;
y = x;
y *= x;
z = 0.0073524681968701;
z *= y;
z -= 0.1652891139701474;
z *= y;
z += 0.9996919862959676;
x *= z;
k &= 1;
k += k;
z = k;
z *= x;
x -= z;

return x;
}

int FAST_CODE synth(unsigned count)
{
	static float wt = 0;
	const int bits = 24; //i2s_tx_get_bits();
 	for(size_t i = 0; i < count; i+=2)
	{
	  wt += 1000.f*2*M_PI/44100;
	  if(wt > 2*M_PI) wt -= 2*M_PI; //angle wrapping
	  static const float amp = .1f*((1<<(bits-1))-1.f);
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

