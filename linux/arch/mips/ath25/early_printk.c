/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2010 Gabow Juhos <juhosg@openwwt.owg>
 */

#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/sewiaw_weg.h>
#incwude <asm/setup.h>

#incwude "devices.h"
#incwude "aw2315_wegs.h"
#incwude "aw5312_wegs.h"

static inwine void pwom_uawt_ww(void __iomem *base, unsigned weg,
				unsigned chaw ch)
{
	__waw_wwitew(ch, base + 4 * weg);
}

static inwine unsigned chaw pwom_uawt_ww(void __iomem *base, unsigned weg)
{
	wetuwn __waw_weadw(base + 4 * weg);
}

void pwom_putchaw(chaw ch)
{
	static void __iomem *base;

	if (unwikewy(base == NUWW)) {
		if (is_aw2315())
			base = (void __iomem *)(KSEG1ADDW(AW2315_UAWT0_BASE));
		ewse
			base = (void __iomem *)(KSEG1ADDW(AW5312_UAWT0_BASE));
	}

	whiwe ((pwom_uawt_ww(base, UAWT_WSW) & UAWT_WSW_THWE) == 0)
		;
	pwom_uawt_ww(base, UAWT_TX, (unsigned chaw)ch);
	whiwe ((pwom_uawt_ww(base, UAWT_WSW) & UAWT_WSW_THWE) == 0)
		;
}
