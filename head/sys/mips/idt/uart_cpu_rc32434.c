/*-
 * Copyright (c) 2006 Wojciech A. Koszek <wkoszek@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id$
 */
/*
 * Skeleton of this file was based on respective code for ARM
 * code written by Olivier Houchard.
 */
/*
 * XXXMIPS: This file is hacked from arm/... . XXXMIPS here means this file is
 * experimental and was written for MIPS32 port.
 */
#include "opt_uart.h"

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: soc2013/dpl/head/sys/mips/idt/uart_cpu_rc32434.c 202218 2010-01-12 21:36:08Z imp $");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/bus.h>
#include <sys/cons.h>

#include <machine/bus.h>

#include <dev/uart/uart.h>
#include <dev/uart/uart_cpu.h>

extern struct uart_class uart_rc32434_uart_class;
bus_space_tag_t uart_bus_space_io;
bus_space_tag_t uart_bus_space_mem;

int
uart_cpu_eqres(struct uart_bas *b1, struct uart_bas *b2)
{

	return ((b1->bsh == b2->bsh && b1->bst == b2->bst) ? 1 : 0);
}

int
uart_cpu_getdev(int devtype, struct uart_devinfo *di)
{
	uint32_t maddr;

	if (resource_int_value("uart", 0, "maddr", &maddr) != 0 ||
	    maddr == 0)
		return (ENXIO);

	/* Got it. Fill in the instance and return it. */
	di->ops = uart_getops(&uart_ns8250_class);
	di->bas.chan = 0;
	di->bas.bst = mips_bus_space_generic;
	di->bas.regshft = 2;
	di->bas.rclk = 330000000UL/2; /* IPbus clock */
	di->baudrate = 115200;
	di->databits = 8;
	di->stopbits = 1;
	di->parity = UART_PARITY_NONE;
	uart_bus_space_io = 0;
	uart_bus_space_mem = mips_bus_space_generic;
	di->bas.bsh = MIPS_PHYS_TO_KSEG1(maddr);
	return (0);
}
