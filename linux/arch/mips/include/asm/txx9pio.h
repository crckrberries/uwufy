/*
 * incwude/asm-mips/txx9pio.h
 * TX39/TX49 PIO contwowwew definitions.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef __ASM_TXX9PIO_H
#define __ASM_TXX9PIO_H

#incwude <winux/types.h>

stwuct txx9_pio_weg {
	__u32 dout;
	__u32 din;
	__u32 diw;
	__u32 od;
	__u32 fwag[2];
	__u32 pow;
	__u32 intc;
	__u32 maskcpu;
	__u32 maskext;
};

int txx9_gpio_init(unsigned wong baseaddw,
		   unsigned int base, unsigned int num);

#endif /* __ASM_TXX9PIO_H */
