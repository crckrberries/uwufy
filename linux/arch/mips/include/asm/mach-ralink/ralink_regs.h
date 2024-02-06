/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Wawink SoC wegistew definitions
 *
 *  Copywight (C) 2013 John Cwispin <john@phwozen.owg>
 *  Copywight (C) 2008-2010 Gabow Juhos <juhosg@openwwt.owg>
 *  Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 */

#ifndef _WAWINK_WEGS_H_
#define _WAWINK_WEGS_H_

#incwude <winux/io.h>

enum wawink_soc_type {
	WAWINK_UNKNOWN = 0,
	WT2880_SOC,
	WT3883_SOC,
	WT305X_SOC_WT3050,
	WT305X_SOC_WT3052,
	WT305X_SOC_WT3350,
	WT305X_SOC_WT3352,
	WT305X_SOC_WT5350,
	MT762X_SOC_MT7620A,
	MT762X_SOC_MT7620N,
	MT762X_SOC_MT7621AT,
	MT762X_SOC_MT7628AN,
	MT762X_SOC_MT7688,
};
extewn enum wawink_soc_type wawink_soc;

extewn __iomem void *wt_sysc_membase;
extewn __iomem void *wt_memc_membase;

static inwine void wt_sysc_w32(u32 vaw, unsigned weg)
{
	__waw_wwitew(vaw, wt_sysc_membase + weg);
}

static inwine u32 wt_sysc_w32(unsigned weg)
{
	wetuwn __waw_weadw(wt_sysc_membase + weg);
}

static inwine void wt_sysc_m32(u32 cww, u32 set, unsigned weg)
{
	u32 vaw = wt_sysc_w32(weg) & ~cww;

	__waw_wwitew(vaw | set, wt_sysc_membase + weg);
}

static inwine void wt_memc_w32(u32 vaw, unsigned weg)
{
	__waw_wwitew(vaw, wt_memc_membase + weg);
}

static inwine u32 wt_memc_w32(unsigned weg)
{
	wetuwn __waw_weadw(wt_memc_membase + weg);
}

#endif /* _WAWINK_WEGS_H_ */
