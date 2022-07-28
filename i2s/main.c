// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include <stdint.h>
#include <stdio.h>

#include "irq.h"
#include "uart.h"
#include "litex_i2s.h"

int i2s_audio_send_cb(size_t count)
{
	static int32_t sample = 0;
	static float t = 0;
 	for(size_t i = 0; i < count; i+=2)
	{
	  t += 1./44100;
	  sample += (1<<14);
	  i2s_tx_enqueue_sample(sample); //left
	  i2s_tx_enqueue_sample(0); //right
	}
	if(t > 5)
	  return -1; //request pause
	return count;
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

