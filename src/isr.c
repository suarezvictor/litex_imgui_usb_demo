// This file is Copyright (c) 2020 Florent Kermarrec <florent@enjoy-digital.fr>
// License: BSD

#include <generated/csr.h>
#include <generated/soc.h>
#include <irq.h>
#include <libbase/uart.h>

void isr(void);

#ifdef CONFIG_CPU_HAS_INTERRUPT

void isr(void)
{
	__attribute__((unused)) unsigned int irqs;

	irqs = irq_pending() & irq_getmask();
/*
#ifdef TIMER0_INTERRUPT
#ifndef TIMER0_POLLING
	if(irqs & (1 << TIMER0_INTERRUPT))
		timer0_isr();
#endif
#endif
*/

#ifndef UART_POLLING
	if(irqs & (1 << UART_INTERRUPT))
		uart_isr();
#endif
}

#else
#error interrupt handling should be enabled
void isr(void){};

#endif
