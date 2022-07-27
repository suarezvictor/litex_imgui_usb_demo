// This file is Copyright (c) 2022 Victor Suarez Rovere <suarezvictor@gmail.com>
// License: BSD-2-Clause

#include <stdint.h>
#include <stdio.h>

#include "irq.h"
#include "uart.h"

void _putchar(char c) { uart_write(c); } //this is to make printf work

int main(int argc, char **argv) {
    irq_setmask(0);
    irq_setie(1);

    uart_init();
	printf("Hello world!\n");

    irq_setie(0);
    irq_setmask(~0);
}

