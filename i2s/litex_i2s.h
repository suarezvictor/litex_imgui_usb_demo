// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#ifndef __LITEX_I2S_H_
#define __LITEX_I2S_H_

#include <generated/csr.h>

#ifdef I2S_ENABLED

void i2s_tx_start(void);
void i2s_tx_stop(void);

static inline void i2s_tx_play(void) { i2s_tx_tx_ctl_enable_write(1); }
static inline void i2s_tx_pause(void) { i2s_tx_tx_ctl_enable_write(0); }
static inline void i2s_tx_enqueue_sample(uint32_t sample) { *(volatile uint32_t*) I2S_TX_MEMADDR = sample; }
static inline int i2s_tx_full(void) { return i2s_tx_tx_stat_full_read(); }
static inline int i2s_tx_almostfull(void) { return i2s_tx_tx_stat_almostfull_read(); }
static inline void i2s_tx_clear(void) { i2s_tx_tx_ctl_reset_write(1); }
static inline unsigned i2s_tx_frequency(void) { return i2s_tx_tx_conf_lrck_freq_read(); }
static inline unsigned i2s_tx_get_default_channels(void) { return 2; } 
static inline unsigned i2s_tx_get_bits(void) { return i2s_tx_tx_conf_sample_width_read(); } 
static inline int i2s_is_playing(void) { return i2s_tx_tx_ctl_enable_read(); } 

extern volatile unsigned i2s_tx_samples_count;
static inline unsigned i2s_tx_played_count(void) { return i2s_tx_samples_count; }

int __attribute__((weak)) i2s_audio_send_cb(unsigned count);
#endif //I2S_ENABLED

#endif
