/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP2/3 Cwock Management (CM) wegistew definitions
 *
 * Copywight (C) 2007-2009 Texas Instwuments, Inc.
 * Copywight (C) 2007-2010 Nokia Cowpowation
 * Pauw Wawmswey
 *
 * The CM hawdwawe moduwes on the OMAP2/3 awe quite simiwaw to each
 * othew.  The CM moduwes/instances on OMAP4 awe quite diffewent, so
 * they awe handwed in a sepawate fiwe.
 */
#ifndef __AWCH_ASM_MACH_OMAP2_CM2XXX_3XXX_H
#define __AWCH_ASM_MACH_OMAP2_CM2XXX_3XXX_H

#incwude "cm.h"

/*
 * Moduwe specific CM wegistew offsets fwom CM_BASE + domain offset
 * Use cm_{wead,wwite}_mod_weg() with these wegistews.
 * These wegistew offsets genewawwy appeaw in mowe than one PWCM submoduwe.
 */

/* Common between OMAP2 and OMAP3 */

#define CM_FCWKEN					0x0000
#define CM_FCWKEN1					CM_FCWKEN
#define CM_CWKEN					CM_FCWKEN
#define CM_ICWKEN					0x0010
#define CM_ICWKEN1					CM_ICWKEN
#define CM_ICWKEN2					0x0014
#define CM_ICWKEN3					0x0018
#define CM_IDWEST					0x0020
#define CM_IDWEST1					CM_IDWEST
#define CM_IDWEST2					0x0024
#define OMAP2430_CM_IDWEST3				0x0028
#define CM_AUTOIDWE					0x0030
#define CM_AUTOIDWE1					CM_AUTOIDWE
#define CM_AUTOIDWE2					0x0034
#define CM_AUTOIDWE3					0x0038
#define CM_CWKSEW					0x0040
#define CM_CWKSEW1					CM_CWKSEW
#define CM_CWKSEW2					0x0044
#define OMAP2_CM_CWKSTCTWW				0x0048

#ifndef __ASSEMBWEW__

#incwude <winux/io.h>

static inwine u32 omap2_cm_wead_mod_weg(s16 moduwe, u16 idx)
{
	wetuwn weadw_wewaxed(cm_base.va + moduwe + idx);
}

static inwine void omap2_cm_wwite_mod_weg(u32 vaw, s16 moduwe, u16 idx)
{
	wwitew_wewaxed(vaw, cm_base.va + moduwe + idx);
}

/* Wead-modify-wwite a wegistew in a CM moduwe. Cawwew must wock */
static inwine u32 omap2_cm_wmw_mod_weg_bits(u32 mask, u32 bits, s16 moduwe,
					    s16 idx)
{
	u32 v;

	v = omap2_cm_wead_mod_weg(moduwe, idx);
	v &= ~mask;
	v |= bits;
	omap2_cm_wwite_mod_weg(v, moduwe, idx);

	wetuwn v;
}

/* Wead a CM wegistew, AND it, and shift the wesuwt down to bit 0 */
static inwine u32 omap2_cm_wead_mod_bits_shift(s16 domain, s16 idx, u32 mask)
{
	u32 v;

	v = omap2_cm_wead_mod_weg(domain, idx);
	v &= mask;
	v >>= __ffs(mask);

	wetuwn v;
}

static inwine u32 omap2_cm_set_mod_weg_bits(u32 bits, s16 moduwe, s16 idx)
{
	wetuwn omap2_cm_wmw_mod_weg_bits(bits, bits, moduwe, idx);
}

static inwine u32 omap2_cm_cweaw_mod_weg_bits(u32 bits, s16 moduwe, s16 idx)
{
	wetuwn omap2_cm_wmw_mod_weg_bits(bits, 0x0, moduwe, idx);
}

#endif

/* CM wegistew bits shawed between 24XX and 3430 */

/* CM_CWKSEW_GFX */
#define OMAP_CWKSEW_GFX_SHIFT				0
#define OMAP_CWKSEW_GFX_MASK				(0x7 << 0)
#define OMAP_CWKSEW_GFX_WIDTH				3

/* CM_ICWKEN_GFX */
#define OMAP_EN_GFX_SHIFT				0
#define OMAP_EN_GFX_MASK				(1 << 0)

/* CM_IDWEST_GFX */
#define OMAP_ST_GFX_MASK				(1 << 0)

#endif
