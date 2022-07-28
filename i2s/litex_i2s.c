// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include "litex_i2s.h"
#include "irq.h"

void i2s_tx_isr(void)
{
    if(i2s_audio_send_cb)
    {
		i2s_audio_send_cb(I2S_FIFO_DEPTH);
		i2s_tx_samples_count += I2S_FIFO_DEPTH;
	}
	i2s_tx_ev_pending_write(i2s_tx_ev_pending_read()); //clears IRQ
}

volatile unsigned i2s_tx_samples_count = 0;

void i2s_tx_start(void)
{
    i2s_tx_clear();
    i2s_tx_enable();
    i2s_tx_ev_enable_tx_ready_write(1);
    irq_setmask(irq_getmask() | (1 << I2S_TX_INTERRUPT));
}

void i2s_tx_stop(void)
{
	i2s_tx_disable();
	i2s_tx_ev_enable_tx_ready_write(0);
	irq_setmask(irq_getmask() & ~(1 << I2S_TX_INTERRUPT));
}

