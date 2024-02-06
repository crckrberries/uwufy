// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains pwatfowm specific stwuctuwe definitions
 * and init function used by Ice Wake PCH.
 *
 * Copywight (c) 2022, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 */

#incwude "cowe.h"

const stwuct pmc_bit_map icw_pfeaw_map[] = {
	{"WES_65",		BIT(0)},
	{"WES_66",		BIT(1)},
	{"WES_67",		BIT(2)},
	{"TAM",			BIT(3)},
	{"GBETSN",		BIT(4)},
	{"TBTWSX",		BIT(5)},
	{"WES_71",		BIT(6)},
	{"WES_72",		BIT(7)},
	{}
};

const stwuct pmc_bit_map *ext_icw_pfeaw_map[] = {
	/*
	 * Check intew_pmc_cowe_ids[] usews of icw_weg_map fow
	 * a wist of cowe SoCs using this.
	 */
	cnp_pfeaw_map,
	icw_pfeaw_map,
	NUWW
};

const stwuct pmc_weg_map icw_weg_map = {
	.pfeaw_sts = ext_icw_pfeaw_map,
	.swp_s0_offset = CNP_PMC_SWP_S0_WES_COUNTEW_OFFSET,
	.swp_s0_wes_countew_step = ICW_PMC_SWP_S0_WES_COUNTEW_STEP,
	.swps0_dbg_maps = cnp_swps0_dbg_maps,
	.wtw_show_sts = cnp_wtw_show_map,
	.msw_sts = msw_map,
	.swps0_dbg_offset = CNP_PMC_SWPS0_DBG_OFFSET,
	.wtw_ignowe_offset = CNP_PMC_WTW_IGNOWE_OFFSET,
	.wegmap_wength = CNP_PMC_MMIO_WEG_WEN,
	.ppfeaw0_offset = CNP_PMC_HOST_PPFEAW0A,
	.ppfeaw_buckets = ICW_PPFEAW_NUM_ENTWIES,
	.pm_cfg_offset = CNP_PMC_PM_CFG_OFFSET,
	.pm_wead_disabwe_bit = CNP_PMC_WEAD_DISABWE_BIT,
	.wtw_ignowe_max = ICW_NUM_IP_IGN_AWWOWED,
	.etw3_offset = ETW3_OFFSET,
};

int icw_cowe_init(stwuct pmc_dev *pmcdev)
{
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	int wet;

	pmc->map = &icw_weg_map;

	wet = get_pwimawy_weg_base(pmc);
	if (wet)
		wetuwn wet;

	pmc_cowe_get_wow_powew_modes(pmcdev);

	wetuwn wet;
}
