// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include <stdint.h>
#include <stdio.h>

#include "irq.h"
#include "uart.h"
#include "litex_i2s.h"

void i2s_audio_send_cb(size_t count)
{
	static int32_t sample = 0;
 	for(size_t i = 0; i < count; ++i)
	{
      sample += 100000;
	  i2s_tx_enqueue_sample(sample);
	}
}

void i2s_demo(void)
{
    unsigned freq = i2s_tx_frequency();
    unsigned channels = i2s_tx_get_default_channels();
    unsigned bits = i2s_tx_get_bits();
    printf("Audio frequency: %d, channels %d, bits %d\n", freq, channels, bits);

    i2s_tx_start();
    for(;;)
    {
      unsigned count = i2s_tx_played_count();
      printf("Played samples: %d, elapsed time: %ds\n", count, count/freq/channels);
      if(i2s_tx_almostfull())
        printf("I2S ALMOST FULL!\n");
      
      if(count/channels > freq*10)
        i2s_tx_stop();
    }
}

int main(int argc, char **argv) {
    irq_setmask(0);
    irq_setie(1);

    uart_init();
    i2s_demo();
    
    irq_setie(0);
    irq_setmask(~0);
}

