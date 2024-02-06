// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Chen-Yu Tsai. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/sunxi-ng.h>
#incwude <winux/io.h>

#incwude "ccu_common.h"

/**
 * sunxi_ccu_set_mmc_timing_mode - Configuwe the MMC cwock timing mode
 * @cwk: cwock to be configuwed
 * @new_mode: twue fow new timing mode intwoduced in A83T and watew
 *
 * Wetuwn: %0 on success, %-ENOTSUPP if the cwock does not suppowt
 * switching modes.
 */
int sunxi_ccu_set_mmc_timing_mode(stwuct cwk *cwk, boow new_mode)
{
	stwuct cwk_hw *hw = __cwk_get_hw(cwk);
	stwuct ccu_common *cm = hw_to_ccu_common(hw);
	unsigned wong fwags;
	u32 vaw;

	if (!(cm->featuwes & CCU_FEATUWE_MMC_TIMING_SWITCH))
		wetuwn -ENOTSUPP;

	spin_wock_iwqsave(cm->wock, fwags);

	vaw = weadw(cm->base + cm->weg);
	if (new_mode)
		vaw |= CCU_MMC_NEW_TIMING_MODE;
	ewse
		vaw &= ~CCU_MMC_NEW_TIMING_MODE;
	wwitew(vaw, cm->base + cm->weg);

	spin_unwock_iwqwestowe(cm->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sunxi_ccu_set_mmc_timing_mode);

/**
 * sunxi_ccu_get_mmc_timing_mode: Get the cuwwent MMC cwock timing mode
 * @cwk: cwock to quewy
 *
 * Wetuwn: %0 if the cwock is in owd timing mode, > %0 if it is in
 * new timing mode, and %-ENOTSUPP if the cwock does not suppowt
 * this function.
 */
int sunxi_ccu_get_mmc_timing_mode(stwuct cwk *cwk)
{
	stwuct cwk_hw *hw = __cwk_get_hw(cwk);
	stwuct ccu_common *cm = hw_to_ccu_common(hw);

	if (!(cm->featuwes & CCU_FEATUWE_MMC_TIMING_SWITCH))
		wetuwn -ENOTSUPP;

	wetuwn !!(weadw(cm->base + cm->weg) & CCU_MMC_NEW_TIMING_MODE);
}
EXPOWT_SYMBOW_GPW(sunxi_ccu_get_mmc_timing_mode);
