// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include <stdint.h>
#include <stdio.h>

#include <generated/csr.h>
#include "irq.h"
#include "uart.h"

static inline void i2s_tx_enable(void) { i2s_tx_tx_ctl_enable_write(1); }
static inline void i2s_tx_enqueue_sample(uint32_t sample) { *(uint32_t*) I2S_TX_MEMADDR = sample; }
static inline int i2s_tx_full(void) { return i2s_tx_tx_stat_full_read(); }
static inline int i2s_tx_almostfull(void) { return i2s_tx_tx_stat_almostfull_read(); }
static inline void i2s_tx_clear(void) { i2s_tx_tx_ctl_reset_write(1); }
static inline unsigned i2s_tx_frequency(void) { return i2s_tx_tx_conf_lrck_freq_read(); }

static void i2s_tx_start(void)
{
    i2s_tx_clear();
    i2s_tx_enable();
    i2s_tx_ev_enable_tx_ready_write(1);
    irq_setmask(irq_getmask() | (1 << I2S_TX_INTERRUPT));
}

static void i2s_tx_stop(void)
{
  i2s_tx_ev_enable_tx_ready_write(0);
  irq_setmask(irq_getmask() & ~(1 << I2S_TX_INTERRUPT));
}

volatile int i2s_tx_samples_count = 0;

void audio_send(size_t count)
{
	static int32_t sample = 0;
 	for(size_t i = 0; i < count; ++i)
	{
      sample += 100000;
	  i2s_tx_enqueue_sample(sample);
      ++i2s_tx_samples_count;
	}
}

void i2s_tx_isr(void)
{
	audio_send(I2S_FIFO_DEPTH);
	i2s_tx_ev_pending_write(i2s_tx_ev_pending_read()); //clears IRQ
}

int main(int argc, char **argv) {
    irq_setmask(0);
    irq_setie(1);

    uart_init();

    unsigned freq = i2s_tx_frequency();
    printf("Audio frequency %d\n", freq, i2s_tx_samples_count);

    i2s_tx_start();
    for(;;)
    {
      printf("played samples %d, elapsed time %ds\n", i2s_tx_samples_count, i2s_tx_samples_count/freq/2);
      if(i2s_tx_samples_count/2 > freq*10)
        i2s_tx_stop();
    }

    irq_setie(0);
    irq_setmask(~0);
}

