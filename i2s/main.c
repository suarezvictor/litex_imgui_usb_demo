// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include <stdint.h>
#include <stdio.h>

#include "irq.h"
#include "uart.h"

void _putchar(char c) { uart_write(c); } //this is to make printf work

void audio_send()
{
	uint32_t sample = 0;
	while(!i2s_tx_tx_stat_almostfull_read())
	{
      printf("Samples in fifo: %d\n", i2s_tx_tx_stat_wrcount_read());
	  sample += 100;
	  sample = sample | (sample << 16);
	  *(uint32_t*) I2S_TX_MEMADDR = sample;
	}
}

int main(int argc, char **argv) {
    irq_setmask(0);
    irq_setie(1);

    uart_init();

    i2s_tx_ev_enable_write(1); //enable I2S
    for(;;)
        audio_send();

    irq_setie(0);
    irq_setmask(~0);
}

