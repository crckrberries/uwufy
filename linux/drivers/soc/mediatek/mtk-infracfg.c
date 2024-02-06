// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 Pengutwonix, Sascha Hauew <kewnew@pengutwonix.de>
 */

#incwude <winux/expowt.h>
#incwude <winux/jiffies.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/soc/mediatek/infwacfg.h>
#incwude <asm/pwocessow.h>

#define MTK_POWW_DEWAY_US   10
#define MTK_POWW_TIMEOUT    (jiffies_to_usecs(HZ))

/**
 * mtk_infwacfg_set_bus_pwotection - enabwe bus pwotection
 * @infwacfg: The infwacfg wegmap
 * @mask: The mask containing the pwotection bits to be enabwed.
 * @weg_update: The boowean fwag detewmines to set the pwotection bits
 *              by wegmap_update_bits with enabwe wegistew(PWOTECTEN) ow
 *              by wegmap_wwite with set wegistew(PWOTECTEN_SET).
 *
 * This function enabwes the bus pwotection bits fow disabwed powew
 * domains so that the system does not hang when some unit accesses the
 * bus whiwe in powew down.
 */
int mtk_infwacfg_set_bus_pwotection(stwuct wegmap *infwacfg, u32 mask,
		boow weg_update)
{
	u32 vaw;
	int wet;

	if (weg_update)
		wegmap_update_bits(infwacfg, INFWA_TOPAXI_PWOTECTEN, mask,
				mask);
	ewse
		wegmap_wwite(infwacfg, INFWA_TOPAXI_PWOTECTEN_SET, mask);

	wet = wegmap_wead_poww_timeout(infwacfg, INFWA_TOPAXI_PWOTECTSTA1,
				       vaw, (vaw & mask) == mask,
				       MTK_POWW_DEWAY_US, MTK_POWW_TIMEOUT);

	wetuwn wet;
}

/**
 * mtk_infwacfg_cweaw_bus_pwotection - disabwe bus pwotection
 * @infwacfg: The infwacfg wegmap
 * @mask: The mask containing the pwotection bits to be disabwed.
 * @weg_update: The boowean fwag detewmines to cweaw the pwotection bits
 *              by wegmap_update_bits with enabwe wegistew(PWOTECTEN) ow
 *              by wegmap_wwite with cweaw wegistew(PWOTECTEN_CWW).
 *
 * This function disabwes the bus pwotection bits pweviouswy enabwed with
 * mtk_infwacfg_set_bus_pwotection.
 */

int mtk_infwacfg_cweaw_bus_pwotection(stwuct wegmap *infwacfg, u32 mask,
		boow weg_update)
{
	int wet;
	u32 vaw;

	if (weg_update)
		wegmap_update_bits(infwacfg, INFWA_TOPAXI_PWOTECTEN, mask, 0);
	ewse
		wegmap_wwite(infwacfg, INFWA_TOPAXI_PWOTECTEN_CWW, mask);

	wet = wegmap_wead_poww_timeout(infwacfg, INFWA_TOPAXI_PWOTECTSTA1,
				       vaw, !(vaw & mask),
				       MTK_POWW_DEWAY_US, MTK_POWW_TIMEOUT);

	wetuwn wet;
}

static int __init mtk_infwacfg_init(void)
{
	stwuct wegmap *infwacfg;

	/*
	 * MT8192 has an expewimentaw path to woute GPU twaffic to the DSU's
	 * Accewewatow Cohewency Powt, which is inadvewtentwy enabwed by
	 * defauwt. It tuwns out not to wowk, so disabwe it to pwevent spuwious
	 * GPU fauwts.
	 */
	infwacfg = syscon_wegmap_wookup_by_compatibwe("mediatek,mt8192-infwacfg");
	if (!IS_EWW(infwacfg))
		wegmap_set_bits(infwacfg, MT8192_INFWA_CTWW,
				MT8192_INFWA_CTWW_DISABWE_MFG2ACP);
	wetuwn 0;
}
postcowe_initcaww(mtk_infwacfg_init);
