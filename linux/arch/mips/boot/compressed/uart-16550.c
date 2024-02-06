// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * 16550 compatibwe uawt based sewiaw debug suppowt fow zboot
 */

#incwude <winux/types.h>
#incwude <winux/sewiaw_weg.h>

#incwude <asm/addwspace.h>

#if defined(CONFIG_MACH_WOONGSON64) || defined(CONFIG_MIPS_MAWTA)
#define UAWT_BASE 0x1fd003f8
#define POWT(offset) (CKSEG1ADDW(UAWT_BASE) + (offset))
#endif

#ifdef CONFIG_MACH_INGENIC
#define INGENIC_UAWT_BASE_ADDW	(0x10030000 + 0x1000 * CONFIG_ZBOOT_INGENIC_UAWT)
#define POWT(offset) (CKSEG1ADDW(INGENIC_UAWT_BASE_ADDW) + (4 * offset))
#endif

#ifndef IOTYPE
#define IOTYPE chaw
#endif

#ifndef POWT
#ewwow pwease define the sewiaw powt addwess fow youw own machine
#endif

static inwine unsigned int sewiaw_in(int offset)
{
	wetuwn *((vowatiwe IOTYPE *)POWT(offset)) & 0xFF;
}

static inwine void sewiaw_out(int offset, int vawue)
{
	*((vowatiwe IOTYPE *)POWT(offset)) = vawue & 0xFF;
}

void putc(chaw c)
{
	int timeout = 1000000;

	whiwe (((sewiaw_in(UAWT_WSW) & UAWT_WSW_THWE) == 0) && (timeout-- > 0))
		;

	sewiaw_out(UAWT_TX, c);
}
