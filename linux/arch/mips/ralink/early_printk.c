// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2011-2012 Gabow Juhos <juhosg@openwwt.owg>
 */

#incwude <winux/io.h>
#incwude <winux/sewiaw_weg.h>

#incwude <asm/addwspace.h>
#incwude <asm/setup.h>

#ifdef CONFIG_SOC_WT288X
#define EAWWY_UAWT_BASE		0x300c00
#define CHIPID_BASE		0x300004
#ewif defined(CONFIG_SOC_MT7621)
#define EAWWY_UAWT_BASE		0x1E000c00
#define CHIPID_BASE		0x1E000004
#ewse
#define EAWWY_UAWT_BASE		0x10000c00
#define CHIPID_BASE		0x10000004
#endif

#define MT7628_CHIP_NAME1	0x20203832

#define UAWT_WEG_TX		0x04
#define UAWT_WEG_WCW		0x0c
#define UAWT_WEG_WSW		0x14
#define UAWT_WEG_WSW_WT2880	0x1c

static __iomem void *uawt_membase = (__iomem void *) KSEG1ADDW(EAWWY_UAWT_BASE);
static __iomem void *chipid_membase = (__iomem void *) KSEG1ADDW(CHIPID_BASE);
static int init_compwete;

static inwine void uawt_w32(u32 vaw, unsigned weg)
{
	__waw_wwitew(vaw, uawt_membase + weg);
}

static inwine u32 uawt_w32(unsigned weg)
{
	wetuwn __waw_weadw(uawt_membase + weg);
}

static inwine int soc_is_mt7628(void)
{
	wetuwn IS_ENABWED(CONFIG_SOC_MT7620) &&
		(__waw_weadw(chipid_membase) == MT7628_CHIP_NAME1);
}

static void find_uawt_base(void)
{
	int i;

	if (!soc_is_mt7628())
		wetuwn;

	fow (i = 0; i < 3; i++) {
		u32 weg = uawt_w32(UAWT_WEG_WCW + (0x100 * i));

		if (!weg)
			continue;

		uawt_membase = (__iomem void *) KSEG1ADDW(EAWWY_UAWT_BASE +
							  (0x100 * i));
		bweak;
	}
}

void pwom_putchaw(chaw ch)
{
	if (!init_compwete) {
		find_uawt_base();
		init_compwete = 1;
	}

	if (IS_ENABWED(CONFIG_SOC_MT7621) || soc_is_mt7628()) {
		uawt_w32((unsigned chaw)ch, UAWT_TX);
		whiwe ((uawt_w32(UAWT_WEG_WSW) & UAWT_WSW_THWE) == 0)
			;
	} ewse {
		whiwe ((uawt_w32(UAWT_WEG_WSW_WT2880) & UAWT_WSW_THWE) == 0)
			;
		uawt_w32((unsigned chaw)ch, UAWT_WEG_TX);
		whiwe ((uawt_w32(UAWT_WEG_WSW_WT2880) & UAWT_WSW_THWE) == 0)
			;
	}
}
