// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include <stdint.h>
#include <stdio.h>

#include <generated/csr.h>
#include "irq.h"
#include "uart.h"

static inline void i2s_tx_enable(void) { i2s_tx_tx_ctl_enable_write(1); }
static inline void i2s_tx_disable(void) { i2s_tx_tx_ctl_enable_write(0); }
static inline void i2s_tx_enqueue_sample(uint32_t sample) { *(uint32_t*) I2S_TX_MEMADDR = sample; }
static inline int i2s_tx_full(void) { return i2s_tx_tx_stat_full_read(); }
static inline int i2s_tx_almostfull(void) { return i2s_tx_tx_stat_almostfull_read(); }
static inline void i2s_tx_clear(void) { i2s_tx_tx_ctl_reset_write(1); }
static inline unsigned i2s_tx_frequency(void) { return i2s_tx_tx_conf_lrck_freq_read(); }
static inline unsigned i2s_tx_get_default_channels(void) { return 2; } 
static inline unsigned i2s_tx_get_bits(void) { return i2s_tx_tx_conf_sample_width_read(); } 

extern volatile unsigned i2s_tx_samples_count;
static inline unsigned i2s_tx_played_count(void) { return i2s_tx_samples_count; }

volatile unsigned i2s_tx_samples_count = 0;
void __attribute__((weak)) i2s_audio_send_cb(size_t count);

static void i2s_tx_start(void)
{
    i2s_tx_clear();
    i2s_tx_enable();
    i2s_tx_ev_enable_tx_ready_write(1);
    irq_setmask(irq_getmask() | (1 << I2S_TX_INTERRUPT));
}

static void i2s_tx_stop(void)
{
	i2s_tx_disable();
	i2s_tx_ev_enable_tx_ready_write(0);
	irq_setmask(irq_getmask() & ~(1 << I2S_TX_INTERRUPT));
}

void i2s_tx_isr(void)
{
    if(i2s_audio_send_cb)
		i2s_audio_send_cb(I2S_FIFO_DEPTH);
	i2s_tx_ev_pending_write(i2s_tx_ev_pending_read()); //clears IRQ
}

void i2s_audio_send_cb(size_t count)
{
	static int32_t sample = 0;
 	for(size_t i = 0; i < count; ++i)
	{
      sample += 100000;
	  i2s_tx_enqueue_sample(sample);
      ++i2s_tx_samples_count;
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

