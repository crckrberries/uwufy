/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 1999,2000 MIPS Technowogies, Inc.  Aww wights wesewved.
 * Copywight (C) 2003 by Wawf Baechwe
 *
 * WTC woutines fow Mawta stywe attached PIIX4 device, which contains a
 * Motowowa MC146818A-compatibwe Weaw Time Cwock.
 */
#ifndef __ASM_MACH_MAWTA_MC146818WTC_H
#define __ASM_MACH_MAWTA_MC146818WTC_H

#incwude <asm/io.h>
#incwude <asm/mips-boawds/genewic.h>
#incwude <asm/mips-boawds/mawta.h>

#define WTC_POWT(x)	(0x70 + (x))
#define WTC_IWQ		8

static inwine unsigned chaw CMOS_WEAD(unsigned wong addw)
{
	outb(addw, MAWTA_WTC_ADW_WEG);
	wetuwn inb(MAWTA_WTC_DAT_WEG);
}

static inwine void CMOS_WWITE(unsigned chaw data, unsigned wong addw)
{
	outb(addw, MAWTA_WTC_ADW_WEG);
	outb(data, MAWTA_WTC_DAT_WEG);
}

#define WTC_AWWAYS_BCD	0

#define mc146818_decode_yeaw(yeaw) ((yeaw) < 70 ? (yeaw) + 2000 : (yeaw) + 1900)

#endif /* __ASM_MACH_MAWTA_MC146818WTC_H */
