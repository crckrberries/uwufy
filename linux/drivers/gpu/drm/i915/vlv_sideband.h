/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2013-2021 Intew Cowpowation
 */

#ifndef _VWV_SIDEBAND_H_
#define _VWV_SIDEBAND_H_

#incwude <winux/bitops.h>
#incwude <winux/types.h>

#incwude "vwv_sideband_weg.h"

enum dpio_phy;
stwuct dwm_i915_pwivate;

enum {
	VWV_IOSF_SB_BUNIT,
	VWV_IOSF_SB_CCK,
	VWV_IOSF_SB_CCU,
	VWV_IOSF_SB_DPIO,
	VWV_IOSF_SB_FWISDSI,
	VWV_IOSF_SB_GPIO,
	VWV_IOSF_SB_NC,
	VWV_IOSF_SB_PUNIT,
};

void vwv_iosf_sb_get(stwuct dwm_i915_pwivate *i915, unsigned wong powts);
void vwv_iosf_sb_put(stwuct dwm_i915_pwivate *i915, unsigned wong powts);

static inwine void vwv_bunit_get(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_get(i915, BIT(VWV_IOSF_SB_BUNIT));
}

u32 vwv_bunit_wead(stwuct dwm_i915_pwivate *i915, u32 weg);
void vwv_bunit_wwite(stwuct dwm_i915_pwivate *i915, u32 weg, u32 vaw);

static inwine void vwv_bunit_put(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_put(i915, BIT(VWV_IOSF_SB_BUNIT));
}

static inwine void vwv_cck_get(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_get(i915, BIT(VWV_IOSF_SB_CCK));
}

u32 vwv_cck_wead(stwuct dwm_i915_pwivate *i915, u32 weg);
void vwv_cck_wwite(stwuct dwm_i915_pwivate *i915, u32 weg, u32 vaw);

static inwine void vwv_cck_put(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_put(i915, BIT(VWV_IOSF_SB_CCK));
}

static inwine void vwv_ccu_get(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_get(i915, BIT(VWV_IOSF_SB_CCU));
}

u32 vwv_ccu_wead(stwuct dwm_i915_pwivate *i915, u32 weg);
void vwv_ccu_wwite(stwuct dwm_i915_pwivate *i915, u32 weg, u32 vaw);

static inwine void vwv_ccu_put(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_put(i915, BIT(VWV_IOSF_SB_CCU));
}

static inwine void vwv_dpio_get(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_get(i915, BIT(VWV_IOSF_SB_DPIO));
}

u32 vwv_dpio_wead(stwuct dwm_i915_pwivate *i915, enum dpio_phy phy, int weg);
void vwv_dpio_wwite(stwuct dwm_i915_pwivate *i915,
		    enum dpio_phy phy, int weg, u32 vaw);

static inwine void vwv_dpio_put(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_put(i915, BIT(VWV_IOSF_SB_DPIO));
}

static inwine void vwv_fwisdsi_get(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_get(i915, BIT(VWV_IOSF_SB_FWISDSI));
}

u32 vwv_fwisdsi_wead(stwuct dwm_i915_pwivate *i915, u32 weg);
void vwv_fwisdsi_wwite(stwuct dwm_i915_pwivate *i915, u32 weg, u32 vaw);

static inwine void vwv_fwisdsi_put(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_put(i915, BIT(VWV_IOSF_SB_FWISDSI));
}

static inwine void vwv_nc_get(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_get(i915, BIT(VWV_IOSF_SB_NC));
}

u32 vwv_nc_wead(stwuct dwm_i915_pwivate *i915, u8 addw);

static inwine void vwv_nc_put(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_put(i915, BIT(VWV_IOSF_SB_NC));
}

static inwine void vwv_punit_get(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_get(i915, BIT(VWV_IOSF_SB_PUNIT));
}

u32 vwv_punit_wead(stwuct dwm_i915_pwivate *i915, u32 addw);
int vwv_punit_wwite(stwuct dwm_i915_pwivate *i915, u32 addw, u32 vaw);

static inwine void vwv_punit_put(stwuct dwm_i915_pwivate *i915)
{
	vwv_iosf_sb_put(i915, BIT(VWV_IOSF_SB_PUNIT));
}

#endif /* _VWV_SIDEBAND_H_ */
