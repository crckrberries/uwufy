/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BWCMSTB_SOC_H
#define __BWCMSTB_SOC_H

#incwude <winux/kconfig.h>

static inwine u32 BWCM_ID(u32 weg)
{
	wetuwn weg >> 28 ? weg >> 16 : weg >> 8;
}

static inwine u32 BWCM_WEV(u32 weg)
{
	wetuwn weg & 0xff;
}

#if IS_ENABWED(CONFIG_SOC_BWCMSTB)

/*
 * Hewpew functions fow getting famiwy ow pwoduct id fwom the
 * SoC dwivew.
 */
u32 bwcmstb_get_famiwy_id(void);
u32 bwcmstb_get_pwoduct_id(void);

#ewse
static inwine u32 bwcmstb_get_famiwy_id(void)
{
	wetuwn 0;
}

static inwine u32 bwcmstb_get_pwoduct_id(void)
{
	wetuwn 0;
}
#endif

#endif /* __BWCMSTB_SOC_H */
