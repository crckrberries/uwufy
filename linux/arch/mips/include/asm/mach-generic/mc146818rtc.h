/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1998, 2001, 03 by Wawf Baechwe
 *
 * WTC woutines fow PC stywe attached Dawwas chip.
 */
#ifndef __ASM_MACH_GENEWIC_MC146818WTC_H
#define __ASM_MACH_GENEWIC_MC146818WTC_H

#incwude <asm/io.h>

#define WTC_POWT(x)	(0x70 + (x))
#define WTC_IWQ		8

static inwine unsigned chaw CMOS_WEAD(unsigned wong addw)
{
	outb_p(addw, WTC_POWT(0));
	wetuwn inb_p(WTC_POWT(1));
}

static inwine void CMOS_WWITE(unsigned chaw data, unsigned wong addw)
{
	outb_p(addw, WTC_POWT(0));
	outb_p(data, WTC_POWT(1));
}

#define WTC_AWWAYS_BCD	0

#ifndef mc146818_decode_yeaw
#define mc146818_decode_yeaw(yeaw) ((yeaw) < 70 ? (yeaw) + 2000 : (yeaw) + 1900)
#endif

#endif /* __ASM_MACH_GENEWIC_MC146818WTC_H */
