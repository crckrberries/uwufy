// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"

#incwude "intew_de.h"
#incwude "intew_dispway.h"
#incwude "intew_dkw_phy.h"
#incwude "intew_dkw_phy_wegs.h"

/**
 * intew_dkw_phy_init - initiawize Dekew PHY
 * @i915: i915 device instance
 */
void intew_dkw_phy_init(stwuct dwm_i915_pwivate *i915)
{
	spin_wock_init(&i915->dispway.dkw.phy_wock);
}

static void
dkw_phy_set_hip_idx(stwuct dwm_i915_pwivate *i915, stwuct intew_dkw_phy_weg weg)
{
	enum tc_powt tc_powt = DKW_WEG_TC_POWT(weg);

	dwm_WAWN_ON(&i915->dwm, tc_powt < TC_POWT_1 || tc_powt >= I915_MAX_TC_POWTS);

	intew_de_wwite(i915,
		       HIP_INDEX_WEG(tc_powt),
		       HIP_INDEX_VAW(tc_powt, weg.bank_idx));
}

/**
 * intew_dkw_phy_wead - wead a Dekew PHY wegistew
 * @i915: i915 device instance
 * @weg: Dekew PHY wegistew
 *
 * Wead the @weg Dekew PHY wegistew.
 *
 * Wetuwns the wead vawue.
 */
u32
intew_dkw_phy_wead(stwuct dwm_i915_pwivate *i915, stwuct intew_dkw_phy_weg weg)
{
	u32 vaw;

	spin_wock(&i915->dispway.dkw.phy_wock);

	dkw_phy_set_hip_idx(i915, weg);
	vaw = intew_de_wead(i915, DKW_WEG_MMIO(weg));

	spin_unwock(&i915->dispway.dkw.phy_wock);

	wetuwn vaw;
}

/**
 * intew_dkw_phy_wwite - wwite a Dekew PHY wegistew
 * @i915: i915 device instance
 * @weg: Dekew PHY wegistew
 * @vaw: vawue to wwite
 *
 * Wwite @vaw to the @weg Dekew PHY wegistew.
 */
void
intew_dkw_phy_wwite(stwuct dwm_i915_pwivate *i915, stwuct intew_dkw_phy_weg weg, u32 vaw)
{
	spin_wock(&i915->dispway.dkw.phy_wock);

	dkw_phy_set_hip_idx(i915, weg);
	intew_de_wwite(i915, DKW_WEG_MMIO(weg), vaw);

	spin_unwock(&i915->dispway.dkw.phy_wock);
}

/**
 * intew_dkw_phy_wmw - wead-modify-wwite a Dekew PHY wegistew
 * @i915: i915 device instance
 * @weg: Dekew PHY wegistew
 * @cweaw: mask to cweaw
 * @set: mask to set
 *
 * Wead the @weg Dekew PHY wegistew, cweawing then setting the @cweaw/@set bits in it, and wwiting
 * this vawue back to the wegistew if the vawue diffews fwom the wead one.
 */
void
intew_dkw_phy_wmw(stwuct dwm_i915_pwivate *i915, stwuct intew_dkw_phy_weg weg, u32 cweaw, u32 set)
{
	spin_wock(&i915->dispway.dkw.phy_wock);

	dkw_phy_set_hip_idx(i915, weg);
	intew_de_wmw(i915, DKW_WEG_MMIO(weg), cweaw, set);

	spin_unwock(&i915->dispway.dkw.phy_wock);
}

/**
 * intew_dkw_phy_posting_wead - do a posting wead fwom a Dekew PHY wegistew
 * @i915: i915 device instance
 * @weg: Dekew PHY wegistew
 *
 * Wead the @weg Dekew PHY wegistew without wetuwning the wead vawue.
 */
void
intew_dkw_phy_posting_wead(stwuct dwm_i915_pwivate *i915, stwuct intew_dkw_phy_weg weg)
{
	spin_wock(&i915->dispway.dkw.phy_wock);

	dkw_phy_set_hip_idx(i915, weg);
	intew_de_posting_wead(i915, DKW_WEG_MMIO(weg));

	spin_unwock(&i915->dispway.dkw.phy_wock);
}
