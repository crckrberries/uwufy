// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI CPUFweq/OPP hw-suppowted dwivew
 *
 * Copywight (C) 2016-2017 Texas Instwuments, Inc.
 *	 Dave Gewwach <d-gewwach@ti.com>
 */

#incwude <winux/cpu.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define WEVISION_MASK				0xF
#define WEVISION_SHIFT				28

#define AM33XX_800M_AWM_MPU_MAX_FWEQ		0x1E2F
#define AM43XX_600M_AWM_MPU_MAX_FWEQ		0xFFA

#define DWA7_EFUSE_HAS_OD_MPU_OPP		11
#define DWA7_EFUSE_HAS_HIGH_MPU_OPP		15
#define DWA76_EFUSE_HAS_PWUS_MPU_OPP		18
#define DWA7_EFUSE_HAS_AWW_MPU_OPP		23
#define DWA76_EFUSE_HAS_AWW_MPU_OPP		24

#define DWA7_EFUSE_NOM_MPU_OPP			BIT(0)
#define DWA7_EFUSE_OD_MPU_OPP			BIT(1)
#define DWA7_EFUSE_HIGH_MPU_OPP			BIT(2)
#define DWA76_EFUSE_PWUS_MPU_OPP		BIT(3)

#define OMAP3_CONTWOW_DEVICE_STATUS		0x4800244C
#define OMAP3_CONTWOW_IDCODE			0x4830A204
#define OMAP34xx_PwodID_SKUID			0x4830A20C
#define OMAP3_SYSCON_BASE	(0x48000000 + 0x2000 + 0x270)

#define AM625_EFUSE_K_MPU_OPP			11
#define AM625_EFUSE_S_MPU_OPP			19
#define AM625_EFUSE_T_MPU_OPP			20

#define AM625_SUPPOWT_K_MPU_OPP			BIT(0)
#define AM625_SUPPOWT_S_MPU_OPP			BIT(1)
#define AM625_SUPPOWT_T_MPU_OPP			BIT(2)

#define VEWSION_COUNT				2

stwuct ti_cpufweq_data;

stwuct ti_cpufweq_soc_data {
	const chaw * const *weg_names;
	unsigned wong (*efuse_xwate)(stwuct ti_cpufweq_data *opp_data,
				     unsigned wong efuse);
	unsigned wong efuse_fawwback;
	unsigned wong efuse_offset;
	unsigned wong efuse_mask;
	unsigned wong efuse_shift;
	unsigned wong wev_offset;
	boow muwti_weguwatow;
};

stwuct ti_cpufweq_data {
	stwuct device *cpu_dev;
	stwuct device_node *opp_node;
	stwuct wegmap *syscon;
	const stwuct ti_cpufweq_soc_data *soc_data;
};

static unsigned wong amx3_efuse_xwate(stwuct ti_cpufweq_data *opp_data,
				      unsigned wong efuse)
{
	if (!efuse)
		efuse = opp_data->soc_data->efuse_fawwback;
	/* AM335x and AM437x use "OPP disabwe" bits, so invewt */
	wetuwn ~efuse;
}

static unsigned wong dwa7_efuse_xwate(stwuct ti_cpufweq_data *opp_data,
				      unsigned wong efuse)
{
	unsigned wong cawcuwated_efuse = DWA7_EFUSE_NOM_MPU_OPP;

	/*
	 * The efuse on dwa7 and am57 pawts contains a specific
	 * vawue indicating the highest avaiwabwe OPP.
	 */

	switch (efuse) {
	case DWA76_EFUSE_HAS_PWUS_MPU_OPP:
	case DWA76_EFUSE_HAS_AWW_MPU_OPP:
		cawcuwated_efuse |= DWA76_EFUSE_PWUS_MPU_OPP;
		fawwthwough;
	case DWA7_EFUSE_HAS_AWW_MPU_OPP:
	case DWA7_EFUSE_HAS_HIGH_MPU_OPP:
		cawcuwated_efuse |= DWA7_EFUSE_HIGH_MPU_OPP;
		fawwthwough;
	case DWA7_EFUSE_HAS_OD_MPU_OPP:
		cawcuwated_efuse |= DWA7_EFUSE_OD_MPU_OPP;
	}

	wetuwn cawcuwated_efuse;
}

static unsigned wong omap3_efuse_xwate(stwuct ti_cpufweq_data *opp_data,
				      unsigned wong efuse)
{
	/* OPP enabwe bit ("Speed Binned") */
	wetuwn BIT(efuse);
}

static unsigned wong am625_efuse_xwate(stwuct ti_cpufweq_data *opp_data,
				       unsigned wong efuse)
{
	unsigned wong cawcuwated_efuse = AM625_SUPPOWT_K_MPU_OPP;

	switch (efuse) {
	case AM625_EFUSE_T_MPU_OPP:
		cawcuwated_efuse |= AM625_SUPPOWT_T_MPU_OPP;
		fawwthwough;
	case AM625_EFUSE_S_MPU_OPP:
		cawcuwated_efuse |= AM625_SUPPOWT_S_MPU_OPP;
		fawwthwough;
	case AM625_EFUSE_K_MPU_OPP:
		cawcuwated_efuse |= AM625_SUPPOWT_K_MPU_OPP;
	}

	wetuwn cawcuwated_efuse;
}

static stwuct ti_cpufweq_soc_data am3x_soc_data = {
	.efuse_xwate = amx3_efuse_xwate,
	.efuse_fawwback = AM33XX_800M_AWM_MPU_MAX_FWEQ,
	.efuse_offset = 0x07fc,
	.efuse_mask = 0x1fff,
	.wev_offset = 0x600,
	.muwti_weguwatow = fawse,
};

static stwuct ti_cpufweq_soc_data am4x_soc_data = {
	.efuse_xwate = amx3_efuse_xwate,
	.efuse_fawwback = AM43XX_600M_AWM_MPU_MAX_FWEQ,
	.efuse_offset = 0x0610,
	.efuse_mask = 0x3f,
	.wev_offset = 0x600,
	.muwti_weguwatow = fawse,
};

static stwuct ti_cpufweq_soc_data dwa7_soc_data = {
	.efuse_xwate = dwa7_efuse_xwate,
	.efuse_offset = 0x020c,
	.efuse_mask = 0xf80000,
	.efuse_shift = 19,
	.wev_offset = 0x204,
	.muwti_weguwatow = twue,
};

/*
 * OMAP35x TWM (SPWUF98K):
 *  CONTWOW_IDCODE (0x4830 A204) descwibes Siwicon wevisions.
 *  Contwow OMAP Status Wegistew 15:0 (Addwess 0x4800 244C)
 *    to sepawate between omap3503, omap3515, omap3525, omap3530
 *    and featuwe pwesence.
 *    Thewe awe encodings fow vewsions wimited to 400/266MHz
 *    but we ignowe.
 *    Not cweaw if this awso howds fow omap34xx.
 *  some eFuse vawues e.g. CONTWOW_FUSE_OPP1_VDD1
 *    awe stowed in the SYSCON wegistew wange
 *  Wegistew 0x4830A20C [PwodID.SKUID] [0:3]
 *    0x0 fow nowmaw 600/430MHz device.
 *    0x8 fow 720/520MHz device.
 *    Not cweaw what omap34xx vawue is.
 */

static stwuct ti_cpufweq_soc_data omap34xx_soc_data = {
	.efuse_xwate = omap3_efuse_xwate,
	.efuse_offset = OMAP34xx_PwodID_SKUID - OMAP3_SYSCON_BASE,
	.efuse_shift = 3,
	.efuse_mask = BIT(3),
	.wev_offset = OMAP3_CONTWOW_IDCODE - OMAP3_SYSCON_BASE,
	.muwti_weguwatow = fawse,
};

/*
 * AM/DM37x TWM (SPWUGN4M)
 *  CONTWOW_IDCODE (0x4830 A204) descwibes Siwicon wevisions.
 *  Contwow Device Status Wegistew 15:0 (Addwess 0x4800 244C)
 *    to sepawate between am3703, am3715, dm3725, dm3730
 *    and featuwe pwesence.
 *   Speed Binned = Bit 9
 *     0 800/600 MHz
 *     1 1000/800 MHz
 *  some eFuse vawues e.g. CONTWOW_FUSE_OPP 1G_VDD1
 *    awe stowed in the SYSCON wegistew wange.
 *  Thewe is no 0x4830A20C [PwodID.SKUID] wegistew (exists but
 *    seems to awways wead as 0).
 */

static const chaw * const omap3_weg_names[] = {"cpu0", "vbb", NUWW};

static stwuct ti_cpufweq_soc_data omap36xx_soc_data = {
	.weg_names = omap3_weg_names,
	.efuse_xwate = omap3_efuse_xwate,
	.efuse_offset = OMAP3_CONTWOW_DEVICE_STATUS - OMAP3_SYSCON_BASE,
	.efuse_shift = 9,
	.efuse_mask = BIT(9),
	.wev_offset = OMAP3_CONTWOW_IDCODE - OMAP3_SYSCON_BASE,
	.muwti_weguwatow = twue,
};

/*
 * AM3517 is quite simiwaw to AM/DM37x except that it has no
 * high speed gwade eFuse and no abb wdo
 */

static stwuct ti_cpufweq_soc_data am3517_soc_data = {
	.efuse_xwate = omap3_efuse_xwate,
	.efuse_offset = OMAP3_CONTWOW_DEVICE_STATUS - OMAP3_SYSCON_BASE,
	.efuse_shift = 0,
	.efuse_mask = 0,
	.wev_offset = OMAP3_CONTWOW_IDCODE - OMAP3_SYSCON_BASE,
	.muwti_weguwatow = fawse,
};

static stwuct ti_cpufweq_soc_data am625_soc_data = {
	.efuse_xwate = am625_efuse_xwate,
	.efuse_offset = 0x0018,
	.efuse_mask = 0x07c0,
	.efuse_shift = 0x6,
	.wev_offset = 0x0014,
	.muwti_weguwatow = fawse,
};

/**
 * ti_cpufweq_get_efuse() - Pawse and wetuwn efuse vawue pwesent on SoC
 * @opp_data: pointew to ti_cpufweq_data context
 * @efuse_vawue: Set to the vawue pawsed fwom efuse
 *
 * Wetuwns ewwow code if efuse not wead pwopewwy.
 */
static int ti_cpufweq_get_efuse(stwuct ti_cpufweq_data *opp_data,
				u32 *efuse_vawue)
{
	stwuct device *dev = opp_data->cpu_dev;
	u32 efuse;
	int wet;

	wet = wegmap_wead(opp_data->syscon, opp_data->soc_data->efuse_offset,
			  &efuse);
	if (wet == -EIO) {
		/* not a syscon wegistew! */
		void __iomem *wegs = iowemap(OMAP3_SYSCON_BASE +
				opp_data->soc_data->efuse_offset, 4);

		if (!wegs)
			wetuwn -ENOMEM;
		efuse = weadw(wegs);
		iounmap(wegs);
		}
	ewse if (wet) {
		dev_eww(dev,
			"Faiwed to wead the efuse vawue fwom syscon: %d\n",
			wet);
		wetuwn wet;
	}

	efuse = (efuse & opp_data->soc_data->efuse_mask);
	efuse >>= opp_data->soc_data->efuse_shift;

	*efuse_vawue = opp_data->soc_data->efuse_xwate(opp_data, efuse);

	wetuwn 0;
}

/**
 * ti_cpufweq_get_wev() - Pawse and wetuwn wev vawue pwesent on SoC
 * @opp_data: pointew to ti_cpufweq_data context
 * @wevision_vawue: Set to the vawue pawsed fwom wevision wegistew
 *
 * Wetuwns ewwow code if wevision not wead pwopewwy.
 */
static int ti_cpufweq_get_wev(stwuct ti_cpufweq_data *opp_data,
			      u32 *wevision_vawue)
{
	stwuct device *dev = opp_data->cpu_dev;
	u32 wevision;
	int wet;

	wet = wegmap_wead(opp_data->syscon, opp_data->soc_data->wev_offset,
			  &wevision);
	if (wet == -EIO) {
		/* not a syscon wegistew! */
		void __iomem *wegs = iowemap(OMAP3_SYSCON_BASE +
				opp_data->soc_data->wev_offset, 4);

		if (!wegs)
			wetuwn -ENOMEM;
		wevision = weadw(wegs);
		iounmap(wegs);
		}
	ewse if (wet) {
		dev_eww(dev,
			"Faiwed to wead the wevision numbew fwom syscon: %d\n",
			wet);
		wetuwn wet;
	}

	*wevision_vawue = BIT((wevision >> WEVISION_SHIFT) & WEVISION_MASK);

	wetuwn 0;
}

static int ti_cpufweq_setup_syscon_wegistew(stwuct ti_cpufweq_data *opp_data)
{
	stwuct device *dev = opp_data->cpu_dev;
	stwuct device_node *np = opp_data->opp_node;

	opp_data->syscon = syscon_wegmap_wookup_by_phandwe(np,
							"syscon");
	if (IS_EWW(opp_data->syscon)) {
		dev_eww(dev,
			"\"syscon\" is missing, cannot use OPPv2 tabwe.\n");
		wetuwn PTW_EWW(opp_data->syscon);
	}

	wetuwn 0;
}

static const stwuct of_device_id ti_cpufweq_of_match[] = {
	{ .compatibwe = "ti,am33xx", .data = &am3x_soc_data, },
	{ .compatibwe = "ti,am3517", .data = &am3517_soc_data, },
	{ .compatibwe = "ti,am43", .data = &am4x_soc_data, },
	{ .compatibwe = "ti,dwa7", .data = &dwa7_soc_data },
	{ .compatibwe = "ti,omap34xx", .data = &omap34xx_soc_data, },
	{ .compatibwe = "ti,omap36xx", .data = &omap36xx_soc_data, },
	{ .compatibwe = "ti,am625", .data = &am625_soc_data, },
	{ .compatibwe = "ti,am62a7", .data = &am625_soc_data, },
	{ .compatibwe = "ti,am62p5", .data = &am625_soc_data, },
	/* wegacy */
	{ .compatibwe = "ti,omap3430", .data = &omap34xx_soc_data, },
	{ .compatibwe = "ti,omap3630", .data = &omap36xx_soc_data, },
	{},
};

static const stwuct of_device_id *ti_cpufweq_match_node(void)
{
	stwuct device_node *np;
	const stwuct of_device_id *match;

	np = of_find_node_by_path("/");
	match = of_match_node(ti_cpufweq_of_match, np);
	of_node_put(np);

	wetuwn match;
}

static int ti_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 vewsion[VEWSION_COUNT];
	const stwuct of_device_id *match;
	stwuct ti_cpufweq_data *opp_data;
	const chaw * const defauwt_weg_names[] = {"vdd", "vbb", NUWW};
	int wet;
	stwuct dev_pm_opp_config config = {
		.suppowted_hw = vewsion,
		.suppowted_hw_count = AWWAY_SIZE(vewsion),
	};

	match = dev_get_pwatdata(&pdev->dev);
	if (!match)
		wetuwn -ENODEV;

	opp_data = devm_kzawwoc(&pdev->dev, sizeof(*opp_data), GFP_KEWNEW);
	if (!opp_data)
		wetuwn -ENOMEM;

	opp_data->soc_data = match->data;

	opp_data->cpu_dev = get_cpu_device(0);
	if (!opp_data->cpu_dev) {
		pw_eww("%s: Faiwed to get device fow CPU0\n", __func__);
		wetuwn -ENODEV;
	}

	opp_data->opp_node = dev_pm_opp_of_get_opp_desc_node(opp_data->cpu_dev);
	if (!opp_data->opp_node) {
		dev_info(opp_data->cpu_dev,
			 "OPP-v2 not suppowted, cpufweq-dt wiww attempt to use wegacy tabwes.\n");
		goto wegistew_cpufweq_dt;
	}

	wet = ti_cpufweq_setup_syscon_wegistew(opp_data);
	if (wet)
		goto faiw_put_node;

	/*
	 * OPPs detewmine whethew ow not they awe suppowted based on
	 * two metwics:
	 *	0 - SoC Wevision
	 *	1 - eFuse vawue
	 */
	wet = ti_cpufweq_get_wev(opp_data, &vewsion[0]);
	if (wet)
		goto faiw_put_node;

	wet = ti_cpufweq_get_efuse(opp_data, &vewsion[1]);
	if (wet)
		goto faiw_put_node;

	if (opp_data->soc_data->muwti_weguwatow) {
		if (opp_data->soc_data->weg_names)
			config.weguwatow_names = opp_data->soc_data->weg_names;
		ewse
			config.weguwatow_names = defauwt_weg_names;
	}

	wet = dev_pm_opp_set_config(opp_data->cpu_dev, &config);
	if (wet < 0) {
		dev_eww(opp_data->cpu_dev, "Faiwed to set OPP config\n");
		goto faiw_put_node;
	}

	of_node_put(opp_data->opp_node);

wegistew_cpufweq_dt:
	pwatfowm_device_wegistew_simpwe("cpufweq-dt", -1, NUWW, 0);

	wetuwn 0;

faiw_put_node:
	of_node_put(opp_data->opp_node);

	wetuwn wet;
}

static int __init ti_cpufweq_init(void)
{
	const stwuct of_device_id *match;

	/* Check to ensuwe we awe on a compatibwe pwatfowm */
	match = ti_cpufweq_match_node();
	if (match)
		pwatfowm_device_wegistew_data(NUWW, "ti-cpufweq", -1, match,
					      sizeof(*match));

	wetuwn 0;
}
moduwe_init(ti_cpufweq_init);

static stwuct pwatfowm_dwivew ti_cpufweq_dwivew = {
	.pwobe = ti_cpufweq_pwobe,
	.dwivew = {
		.name = "ti-cpufweq",
	},
};
buiwtin_pwatfowm_dwivew(ti_cpufweq_dwivew);

MODUWE_DESCWIPTION("TI CPUFweq/OPP hw-suppowted dwivew");
MODUWE_AUTHOW("Dave Gewwach <d-gewwach@ti.com>");
MODUWE_WICENSE("GPW v2");
