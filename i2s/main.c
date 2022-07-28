// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include <stdint.h>
#include <stdio.h>

#include "irq.h"
#include "uart.h"

static inline void i2s_enable(void) { i2s_tx_ev_enable_write(1); }
static inline void i2s_enqueue_sample(uint32_t sample) { *(uint32_t*) I2S_TX_MEMADDR = sample; }
static inline int i2s_tx_full(void) { return i2s_tx_tx_stat_full_read(); }
static inline int i2s_tx_almostfull(void) { return i2s_tx_tx_stat_almostfull_read(); }
static inline void i2s_tx_clear(void) { i2s_tx_tx_ctl_reset_write(1); }
//static void i2s_clear_pending_irq(void) { i2s_tx_ev_pending_write(/*i2s_tx_ev_pending_read()*/0); }

void audio_send(void)
{
	uint32_t sample = 0;
	while(!i2s_tx_full())
	{
	  unsigned count = i2s_tx_tx_stat_wrcount_read();
	  if(count == 0)
	  {
	    static int frames = 0;
	    ++frames;
		printf("Frame %d, estimated time %d\n", frames, frames*(512/2)/i2s_tx_tx_conf_lrck_freq_read());
	  }
	  sample += 100;
	  sample = sample | (sample << 16);
	  i2s_enqueue_sample(sample);
	}
    i2s_tx_clear();
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

