// This file is Copyright (c) 2020 Florent Kermarrec <florent@enjoy-digital.fr>
// License: BSD

#include <generated/csr.h>
#include <irq.h>
#include <libbase/uart.h>

void __attribute__((weak)) timer0_isr(void);

#ifndef CONFIG_CPU_HAS_INTERRUPT
#error CONFIG_CPU_HAS_INTERRUPT should be enabled
#endif

void isr_handler(void)
{
	__attribute__((unused)) unsigned int irqs;

	irqs = irq_pending() & irq_getmask();

#if defined(UART_INTERRUPT) && !defined(UART_POLLING)
	if(irqs & (1 << UART_INTERRUPT))
	{
		uart_isr();
	}
#endif
#if defined(TIMER0_INTERRUPT) && !defined(TIMER0_POLLING)
	if(irqs & (1 << TIMER0_INTERRUPT))
	{
		if(timer0_isr)
			timer0_isr();
	}
#endif
}

