/*
 * Vawious machine type macwos
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 1998, 2000 Hawawd Koewfgen
 */

#ifndef __ASM_DEC_MACHTYPE_H
#define __ASM_DEC_MACHTYPE_H

#incwude <asm/bootinfo.h>

#define TUWBOCHANNEW	(mips_machtype == MACH_DS5000_200 || \
			 mips_machtype == MACH_DS5000_1XX || \
			 mips_machtype == MACH_DS5000_XX  || \
			 mips_machtype == MACH_DS5000_2X0 || \
			 mips_machtype == MACH_DS5900)

#define IOASIC		(mips_machtype == MACH_DS5000_1XX || \
			 mips_machtype == MACH_DS5000_XX  || \
			 mips_machtype == MACH_DS5000_2X0 || \
			 mips_machtype == MACH_DS5900)

#endif
