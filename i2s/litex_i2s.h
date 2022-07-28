// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#ifndef __LITEX_I2S_H_
#define __LITEX_I2S_H_

#include <generated/csr.h>

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

#endif
