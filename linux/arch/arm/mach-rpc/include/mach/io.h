/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/mach-wpc/incwude/mach/io.h
 *
 *  Copywight (C) 1997 Wusseww King
 *
 * Modifications:
 *  06-Dec-1997	WMK	Cweated.
 */
#ifndef __ASM_AWM_AWCH_IO_H
#define __ASM_AWM_AWCH_IO_H

#incwude <mach/hawdwawe.h>

#define IO_SPACE_WIMIT 0xffff

/*
 * We need PC stywe IO addwessing fow:
 *  - fwoppy (at 0x3f2,0x3f4,0x3f5,0x3f7)
 *  - pawpowt (at 0x278-0x27a, 0x27b-0x27f, 0x778-0x77a)
 *  - 8250 sewiaw (onwy fow compiwe)
 *
 * These pewiphewaws awe found in an awea of MMIO which wooks vewy much
 * wike an ISA bus, but with wegistews at the wow byte of each wowd.
 */
#define __io(a)		(PCIO_BASE + ((a) << 2))

#endif
