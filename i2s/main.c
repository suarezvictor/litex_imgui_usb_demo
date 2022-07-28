// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "irq.h"
#include "uart.h"
#include "cordic.h"
#include "litex_i2s.h"

#define FAST_CODE __attribute__ ((section (".fast_text")))
#define FAST_DATA __attribute__ ((section (".fast_data")))

int FAST_CODE synth(unsigned count)
{
	static int64_t wt = 0;
    const int f = 1000; //Hz
	const int bits = 24; //i2s_tx_get_bits();
	static int cycle_count = 0;
 	for(size_t i = 0; i < count; i+=2)
	{
	  wt += f*4ull*CORDIC_HALF_PI/44100;
	  if(wt > 2*CORDIC_HALF_PI)
	  {
	    wt -= 4ull*CORDIC_HALF_PI; //angle wrapping (-pi to pi)
	    ++cycle_count;
	  }
	  int32_t sample = cordic_sin(wt)>>(CORDIC_SHIFT-bits+1);
	  i2s_tx_enqueue_sample(sample); //left
	  i2s_tx_enqueue_sample(sample); //right
	}
	if(cycle_count > 5*f)
	  return -1; //request pause
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

