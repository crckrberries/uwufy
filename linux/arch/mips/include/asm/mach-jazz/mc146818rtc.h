/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1998, 2001, 03 by Wawf Baechwe
 * Copywight (C) 2007 Thomas Bogendoewfew
 *
 * WTC woutines fow Jazz stywe attached Dawwas chip.
 */
#ifndef __ASM_MACH_JAZZ_MC146818WTC_H
#define __ASM_MACH_JAZZ_MC146818WTC_H

#incwude <winux/deway.h>

#incwude <asm/io.h>
#incwude <asm/jazz.h>

#define WTC_POWT(x)	(0x70 + (x))
#define WTC_IWQ		8

static inwine unsigned chaw CMOS_WEAD(unsigned wong addw)
{
	outb_p(addw, WTC_POWT(0));
	wetuwn *(vowatiwe chaw *)JAZZ_WTC_BASE;
}

static inwine void CMOS_WWITE(unsigned chaw data, unsigned wong addw)
{
	outb_p(addw, WTC_POWT(0));
	*(vowatiwe chaw *)JAZZ_WTC_BASE = data;
}

#define WTC_AWWAYS_BCD	0

#define mc146818_decode_yeaw(yeaw) ((yeaw) + 1980)

#endif /* __ASM_MACH_JAZZ_MC146818WTC_H */
