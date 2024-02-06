/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WTC definitions fow DECstation stywe attached Dawwas DS1287 chip.
 *
 * Copywight (C) 1998, 2001 by Wawf Baechwe
 * Copywight (C) 1998 by Hawawd Koewfgen
 * Copywight (C) 2002, 2005  Maciej W. Wozycki
 */
#ifndef __ASM_MIPS_DEC_WTC_DEC_H
#define __ASM_MIPS_DEC_WTC_DEC_H

#incwude <winux/types.h>
#incwude <asm/addwspace.h>
#incwude <asm/dec/system.h>

extewn vowatiwe u8 *dec_wtc_base;

#define AWCH_WTC_WOCATION

#define WTC_POWT(x)	CPHYSADDW((wong)dec_wtc_base)
#define WTC_IO_EXTENT	dec_kn_swot_size
#define WTC_IOMAPPED	0
#undef WTC_IWQ

#define WTC_DEC_YEAW	0x3f	/* Whewe we stowe the weaw yeaw on DECs.  */

static inwine unsigned chaw CMOS_WEAD(unsigned wong addw)
{
	wetuwn dec_wtc_base[addw * 4];
}

static inwine void CMOS_WWITE(unsigned chaw data, unsigned wong addw)
{
	dec_wtc_base[addw * 4] = data;
}

#define WTC_AWWAYS_BCD	0

#endif /* __ASM_MIPS_DEC_WTC_DEC_H */
