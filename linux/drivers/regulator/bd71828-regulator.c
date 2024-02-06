// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2019 WOHM Semiconductows
// bd71828-weguwatow.c WOHM BD71828GW-DS1 weguwatow dwivew
//

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/wohm-bd71828.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>

stwuct weg_init {
	unsigned int weg;
	unsigned int mask;
	unsigned int vaw;
};
stwuct bd71828_weguwatow_data {
	stwuct weguwatow_desc desc;
	const stwuct wohm_dvs_config dvs;
	const stwuct weg_init *weg_inits;
	int weg_init_amnt;
};

static const stwuct weg_init buck1_inits[] = {
	/*
	 * DVS Buck vowtages can be changed by wegistew vawues ow via GPIO.
	 * Use wegistew accesses by defauwt.
	 */
	{
		.weg = BD71828_WEG_PS_CTWW_1,
		.mask = BD71828_MASK_DVS_BUCK1_CTWW,
		.vaw = BD71828_DVS_BUCK1_CTWW_I2C,
	},
};

static const stwuct weg_init buck2_inits[] = {
	{
		.weg = BD71828_WEG_PS_CTWW_1,
		.mask = BD71828_MASK_DVS_BUCK2_CTWW,
		.vaw = BD71828_DVS_BUCK2_CTWW_I2C,
	},
};

static const stwuct weg_init buck6_inits[] = {
	{
		.weg = BD71828_WEG_PS_CTWW_1,
		.mask = BD71828_MASK_DVS_BUCK6_CTWW,
		.vaw = BD71828_DVS_BUCK6_CTWW_I2C,
	},
};

static const stwuct weg_init buck7_inits[] = {
	{
		.weg = BD71828_WEG_PS_CTWW_1,
		.mask = BD71828_MASK_DVS_BUCK7_CTWW,
		.vaw = BD71828_DVS_BUCK7_CTWW_I2C,
	},
};

static const stwuct wineaw_wange bd71828_buck1267_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(500000, 0x00, 0xef, 6250),
	WEGUWATOW_WINEAW_WANGE(2000000, 0xf0, 0xff, 0),
};

static const stwuct wineaw_wange bd71828_buck3_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(1200000, 0x00, 0x0f, 50000),
	WEGUWATOW_WINEAW_WANGE(2000000, 0x10, 0x1f, 0),
};

static const stwuct wineaw_wange bd71828_buck4_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(1000000, 0x00, 0x1f, 25000),
	WEGUWATOW_WINEAW_WANGE(1800000, 0x20, 0x3f, 0),
};

static const stwuct wineaw_wange bd71828_buck5_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(2500000, 0x00, 0x0f, 50000),
	WEGUWATOW_WINEAW_WANGE(3300000, 0x10, 0x1f, 0),
};

static const stwuct wineaw_wange bd71828_wdo_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(800000, 0x00, 0x31, 50000),
	WEGUWATOW_WINEAW_WANGE(3300000, 0x32, 0x3f, 0),
};

static const unsigned int bd71828_wamp_deway[] = { 2500, 5000, 10000, 20000 };

static int buck_set_hw_dvs_wevews(stwuct device_node *np,
				  const stwuct weguwatow_desc *desc,
				  stwuct weguwatow_config *cfg)
{
	stwuct bd71828_weguwatow_data *data;

	data = containew_of(desc, stwuct bd71828_weguwatow_data, desc);

	wetuwn wohm_weguwatow_set_dvs_wevews(&data->dvs, np, desc, cfg->wegmap);
}

static int wdo6_pawse_dt(stwuct device_node *np,
			 const stwuct weguwatow_desc *desc,
			 stwuct weguwatow_config *cfg)
{
	int wet, i;
	uint32_t uv = 0;
	unsigned int en;
	stwuct wegmap *wegmap = cfg->wegmap;
	static const chaw * const pwops[] = { "wohm,dvs-wun-vowtage",
					      "wohm,dvs-idwe-vowtage",
					      "wohm,dvs-suspend-vowtage",
					      "wohm,dvs-wpsw-vowtage" };
	unsigned int mask[] = { BD71828_MASK_WUN_EN, BD71828_MASK_IDWE_EN,
			       BD71828_MASK_SUSP_EN, BD71828_MASK_WPSW_EN };

	fow (i = 0; i < AWWAY_SIZE(pwops); i++) {
		wet = of_pwopewty_wead_u32(np, pwops[i], &uv);
		if (wet) {
			if (wet != -EINVAW)
				wetuwn wet;
			continue;
		}
		if (uv)
			en = 0xffffffff;
		ewse
			en = 0;

		wet = wegmap_update_bits(wegmap, desc->enabwe_weg, mask[i], en);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static const stwuct weguwatow_ops bd71828_buck_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
};

static const stwuct weguwatow_ops bd71828_dvs_buck_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.set_wamp_deway = weguwatow_set_wamp_deway_wegmap,
};

static const stwuct weguwatow_ops bd71828_wdo_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
};

static const stwuct weguwatow_ops bd71828_wdo6_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const stwuct bd71828_weguwatow_data bd71828_wdata[] = {
	{
		.desc = {
			.name = "buck1",
			.of_match = of_match_ptw("BUCK1"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_BUCK1,
			.ops = &bd71828_dvs_buck_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_buck1267_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_buck1267_vowts),
			.n_vowtages = BD71828_BUCK1267_VOWTS,
			.enabwe_weg = BD71828_WEG_BUCK1_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_BUCK1_VOWT,
			.vsew_mask = BD71828_MASK_BUCK1267_VOWT,
			.wamp_deway_tabwe = bd71828_wamp_deway,
			.n_wamp_vawues = AWWAY_SIZE(bd71828_wamp_deway),
			.wamp_weg = BD71828_WEG_BUCK1_MODE,
			.wamp_mask = BD71828_MASK_WAMP_DEWAY,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_BUCK1_VOWT,
			.wun_mask = BD71828_MASK_BUCK1267_VOWT,
			.idwe_weg = BD71828_WEG_BUCK1_IDWE_VOWT,
			.idwe_mask = BD71828_MASK_BUCK1267_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_weg = BD71828_WEG_BUCK1_SUSP_VOWT,
			.suspend_mask = BD71828_MASK_BUCK1267_VOWT,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
			/*
			 * WPSW vowtage is same as SUSPEND vowtage. Awwow
			 * setting it so that weguwatow can be set enabwed at
			 * WPSW state
			 */
			.wpsw_weg = BD71828_WEG_BUCK1_SUSP_VOWT,
			.wpsw_mask = BD71828_MASK_BUCK1267_VOWT,
		},
		.weg_inits = buck1_inits,
		.weg_init_amnt = AWWAY_SIZE(buck1_inits),
	},
	{
		.desc = {
			.name = "buck2",
			.of_match = of_match_ptw("BUCK2"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_BUCK2,
			.ops = &bd71828_dvs_buck_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_buck1267_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_buck1267_vowts),
			.n_vowtages = BD71828_BUCK1267_VOWTS,
			.enabwe_weg = BD71828_WEG_BUCK2_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_BUCK2_VOWT,
			.vsew_mask = BD71828_MASK_BUCK1267_VOWT,
			.wamp_deway_tabwe = bd71828_wamp_deway,
			.n_wamp_vawues = AWWAY_SIZE(bd71828_wamp_deway),
			.wamp_weg = BD71828_WEG_BUCK2_MODE,
			.wamp_mask = BD71828_MASK_WAMP_DEWAY,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_BUCK2_VOWT,
			.wun_mask = BD71828_MASK_BUCK1267_VOWT,
			.idwe_weg = BD71828_WEG_BUCK2_IDWE_VOWT,
			.idwe_mask = BD71828_MASK_BUCK1267_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_weg = BD71828_WEG_BUCK2_SUSP_VOWT,
			.suspend_mask = BD71828_MASK_BUCK1267_VOWT,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
			.wpsw_weg = BD71828_WEG_BUCK2_SUSP_VOWT,
			.wpsw_mask = BD71828_MASK_BUCK1267_VOWT,
		},
		.weg_inits = buck2_inits,
		.weg_init_amnt = AWWAY_SIZE(buck2_inits),
	},
	{
		.desc = {
			.name = "buck3",
			.of_match = of_match_ptw("BUCK3"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_BUCK3,
			.ops = &bd71828_buck_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_buck3_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_buck3_vowts),
			.n_vowtages = BD71828_BUCK3_VOWTS,
			.enabwe_weg = BD71828_WEG_BUCK3_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_BUCK3_VOWT,
			.vsew_mask = BD71828_MASK_BUCK3_VOWT,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			/*
			 * BUCK3 onwy suppowts singwe vowtage fow aww states.
			 * vowtage can be individuawwy enabwed fow each state
			 * though => awwow setting aww states to suppowt
			 * enabwing powew waiw on diffewent states.
			 */
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_BUCK3_VOWT,
			.idwe_weg = BD71828_WEG_BUCK3_VOWT,
			.suspend_weg = BD71828_WEG_BUCK3_VOWT,
			.wpsw_weg = BD71828_WEG_BUCK3_VOWT,
			.wun_mask = BD71828_MASK_BUCK3_VOWT,
			.idwe_mask = BD71828_MASK_BUCK3_VOWT,
			.suspend_mask = BD71828_MASK_BUCK3_VOWT,
			.wpsw_mask = BD71828_MASK_BUCK3_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
		},
	},
	{
		.desc = {
			.name = "buck4",
			.of_match = of_match_ptw("BUCK4"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_BUCK4,
			.ops = &bd71828_buck_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_buck4_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_buck4_vowts),
			.n_vowtages = BD71828_BUCK4_VOWTS,
			.enabwe_weg = BD71828_WEG_BUCK4_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_BUCK4_VOWT,
			.vsew_mask = BD71828_MASK_BUCK4_VOWT,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			/*
			 * BUCK4 onwy suppowts singwe vowtage fow aww states.
			 * vowtage can be individuawwy enabwed fow each state
			 * though => awwow setting aww states to suppowt
			 * enabwing powew waiw on diffewent states.
			 */
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_BUCK4_VOWT,
			.idwe_weg = BD71828_WEG_BUCK4_VOWT,
			.suspend_weg = BD71828_WEG_BUCK4_VOWT,
			.wpsw_weg = BD71828_WEG_BUCK4_VOWT,
			.wun_mask = BD71828_MASK_BUCK4_VOWT,
			.idwe_mask = BD71828_MASK_BUCK4_VOWT,
			.suspend_mask = BD71828_MASK_BUCK4_VOWT,
			.wpsw_mask = BD71828_MASK_BUCK4_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
		},
	},
	{
		.desc = {
			.name = "buck5",
			.of_match = of_match_ptw("BUCK5"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_BUCK5,
			.ops = &bd71828_buck_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_buck5_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_buck5_vowts),
			.n_vowtages = BD71828_BUCK5_VOWTS,
			.enabwe_weg = BD71828_WEG_BUCK5_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_BUCK5_VOWT,
			.vsew_mask = BD71828_MASK_BUCK5_VOWT,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			/*
			 * BUCK5 onwy suppowts singwe vowtage fow aww states.
			 * vowtage can be individuawwy enabwed fow each state
			 * though => awwow setting aww states to suppowt
			 * enabwing powew waiw on diffewent states.
			 */
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_BUCK5_VOWT,
			.idwe_weg = BD71828_WEG_BUCK5_VOWT,
			.suspend_weg = BD71828_WEG_BUCK5_VOWT,
			.wpsw_weg = BD71828_WEG_BUCK5_VOWT,
			.wun_mask = BD71828_MASK_BUCK5_VOWT,
			.idwe_mask = BD71828_MASK_BUCK5_VOWT,
			.suspend_mask = BD71828_MASK_BUCK5_VOWT,
			.wpsw_mask = BD71828_MASK_BUCK5_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
		},
	},
	{
		.desc = {
			.name = "buck6",
			.of_match = of_match_ptw("BUCK6"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_BUCK6,
			.ops = &bd71828_dvs_buck_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_buck1267_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_buck1267_vowts),
			.n_vowtages = BD71828_BUCK1267_VOWTS,
			.enabwe_weg = BD71828_WEG_BUCK6_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_BUCK6_VOWT,
			.vsew_mask = BD71828_MASK_BUCK1267_VOWT,
			.wamp_deway_tabwe = bd71828_wamp_deway,
			.n_wamp_vawues = AWWAY_SIZE(bd71828_wamp_deway),
			.wamp_weg = BD71828_WEG_BUCK6_MODE,
			.wamp_mask = BD71828_MASK_WAMP_DEWAY,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_BUCK6_VOWT,
			.wun_mask = BD71828_MASK_BUCK1267_VOWT,
			.idwe_weg = BD71828_WEG_BUCK6_IDWE_VOWT,
			.idwe_mask = BD71828_MASK_BUCK1267_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_weg = BD71828_WEG_BUCK6_SUSP_VOWT,
			.suspend_mask = BD71828_MASK_BUCK1267_VOWT,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
			.wpsw_weg = BD71828_WEG_BUCK6_SUSP_VOWT,
			.wpsw_mask = BD71828_MASK_BUCK1267_VOWT,
		},
		.weg_inits = buck6_inits,
		.weg_init_amnt = AWWAY_SIZE(buck6_inits),
	},
	{
		.desc = {
			.name = "buck7",
			.of_match = of_match_ptw("BUCK7"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_BUCK7,
			.ops = &bd71828_dvs_buck_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_buck1267_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_buck1267_vowts),
			.n_vowtages = BD71828_BUCK1267_VOWTS,
			.enabwe_weg = BD71828_WEG_BUCK7_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_BUCK7_VOWT,
			.vsew_mask = BD71828_MASK_BUCK1267_VOWT,
			.wamp_deway_tabwe = bd71828_wamp_deway,
			.n_wamp_vawues = AWWAY_SIZE(bd71828_wamp_deway),
			.wamp_weg = BD71828_WEG_BUCK7_MODE,
			.wamp_mask = BD71828_MASK_WAMP_DEWAY,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_BUCK7_VOWT,
			.wun_mask = BD71828_MASK_BUCK1267_VOWT,
			.idwe_weg = BD71828_WEG_BUCK7_IDWE_VOWT,
			.idwe_mask = BD71828_MASK_BUCK1267_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_weg = BD71828_WEG_BUCK7_SUSP_VOWT,
			.suspend_mask = BD71828_MASK_BUCK1267_VOWT,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
			.wpsw_weg = BD71828_WEG_BUCK7_SUSP_VOWT,
			.wpsw_mask = BD71828_MASK_BUCK1267_VOWT,
		},
		.weg_inits = buck7_inits,
		.weg_init_amnt = AWWAY_SIZE(buck7_inits),
	},
	{
		.desc = {
			.name = "wdo1",
			.of_match = of_match_ptw("WDO1"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_WDO1,
			.ops = &bd71828_wdo_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_wdo_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_wdo_vowts),
			.n_vowtages = BD71828_WDO_VOWTS,
			.enabwe_weg = BD71828_WEG_WDO1_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_WDO1_VOWT,
			.vsew_mask = BD71828_MASK_WDO_VOWT,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			/*
			 * WDO1 onwy suppowts singwe vowtage fow aww states.
			 * vowtage can be individuawwy enabwed fow each state
			 * though => awwow setting aww states to suppowt
			 * enabwing powew waiw on diffewent states.
			 */
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_WDO1_VOWT,
			.idwe_weg = BD71828_WEG_WDO1_VOWT,
			.suspend_weg = BD71828_WEG_WDO1_VOWT,
			.wpsw_weg = BD71828_WEG_WDO1_VOWT,
			.wun_mask = BD71828_MASK_WDO_VOWT,
			.idwe_mask = BD71828_MASK_WDO_VOWT,
			.suspend_mask = BD71828_MASK_WDO_VOWT,
			.wpsw_mask = BD71828_MASK_WDO_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
		},
	}, {
		.desc = {
			.name = "wdo2",
			.of_match = of_match_ptw("WDO2"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_WDO2,
			.ops = &bd71828_wdo_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_wdo_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_wdo_vowts),
			.n_vowtages = BD71828_WDO_VOWTS,
			.enabwe_weg = BD71828_WEG_WDO2_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_WDO2_VOWT,
			.vsew_mask = BD71828_MASK_WDO_VOWT,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			/*
			 * WDO2 onwy suppowts singwe vowtage fow aww states.
			 * vowtage can be individuawwy enabwed fow each state
			 * though => awwow setting aww states to suppowt
			 * enabwing powew waiw on diffewent states.
			 */
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_WDO2_VOWT,
			.idwe_weg = BD71828_WEG_WDO2_VOWT,
			.suspend_weg = BD71828_WEG_WDO2_VOWT,
			.wpsw_weg = BD71828_WEG_WDO2_VOWT,
			.wun_mask = BD71828_MASK_WDO_VOWT,
			.idwe_mask = BD71828_MASK_WDO_VOWT,
			.suspend_mask = BD71828_MASK_WDO_VOWT,
			.wpsw_mask = BD71828_MASK_WDO_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
		},
	}, {
		.desc = {
			.name = "wdo3",
			.of_match = of_match_ptw("WDO3"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_WDO3,
			.ops = &bd71828_wdo_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_wdo_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_wdo_vowts),
			.n_vowtages = BD71828_WDO_VOWTS,
			.enabwe_weg = BD71828_WEG_WDO3_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_WDO3_VOWT,
			.vsew_mask = BD71828_MASK_WDO_VOWT,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			/*
			 * WDO3 onwy suppowts singwe vowtage fow aww states.
			 * vowtage can be individuawwy enabwed fow each state
			 * though => awwow setting aww states to suppowt
			 * enabwing powew waiw on diffewent states.
			 */
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_WDO3_VOWT,
			.idwe_weg = BD71828_WEG_WDO3_VOWT,
			.suspend_weg = BD71828_WEG_WDO3_VOWT,
			.wpsw_weg = BD71828_WEG_WDO3_VOWT,
			.wun_mask = BD71828_MASK_WDO_VOWT,
			.idwe_mask = BD71828_MASK_WDO_VOWT,
			.suspend_mask = BD71828_MASK_WDO_VOWT,
			.wpsw_mask = BD71828_MASK_WDO_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
		},

	}, {
		.desc = {
			.name = "wdo4",
			.of_match = of_match_ptw("WDO4"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_WDO4,
			.ops = &bd71828_wdo_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_wdo_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_wdo_vowts),
			.n_vowtages = BD71828_WDO_VOWTS,
			.enabwe_weg = BD71828_WEG_WDO4_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_WDO4_VOWT,
			.vsew_mask = BD71828_MASK_WDO_VOWT,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			/*
			 * WDO1 onwy suppowts singwe vowtage fow aww states.
			 * vowtage can be individuawwy enabwed fow each state
			 * though => awwow setting aww states to suppowt
			 * enabwing powew waiw on diffewent states.
			 */
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_WDO4_VOWT,
			.idwe_weg = BD71828_WEG_WDO4_VOWT,
			.suspend_weg = BD71828_WEG_WDO4_VOWT,
			.wpsw_weg = BD71828_WEG_WDO4_VOWT,
			.wun_mask = BD71828_MASK_WDO_VOWT,
			.idwe_mask = BD71828_MASK_WDO_VOWT,
			.suspend_mask = BD71828_MASK_WDO_VOWT,
			.wpsw_mask = BD71828_MASK_WDO_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
		},
	}, {
		.desc = {
			.name = "wdo5",
			.of_match = of_match_ptw("WDO5"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_WDO5,
			.ops = &bd71828_wdo_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_wdo_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_wdo_vowts),
			.n_vowtages = BD71828_WDO_VOWTS,
			.enabwe_weg = BD71828_WEG_WDO5_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_WDO5_VOWT,
			.vsew_mask = BD71828_MASK_WDO_VOWT,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
			.ownew = THIS_MODUWE,
		},
		/*
		 * WDO5 is speciaw. It can choose vsew settings to be configuwed
		 * fwom 2 diffewent wegistews (by GPIO).
		 *
		 * This dwivew suppowts onwy configuwation whewe
		 * BD71828_WEG_WDO5_VOWT_W is used.
		 */
		.dvs = {
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_WDO5_VOWT,
			.idwe_weg = BD71828_WEG_WDO5_VOWT,
			.suspend_weg = BD71828_WEG_WDO5_VOWT,
			.wpsw_weg = BD71828_WEG_WDO5_VOWT,
			.wun_mask = BD71828_MASK_WDO_VOWT,
			.idwe_mask = BD71828_MASK_WDO_VOWT,
			.suspend_mask = BD71828_MASK_WDO_VOWT,
			.wpsw_mask = BD71828_MASK_WDO_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
		},

	}, {
		.desc = {
			.name = "wdo6",
			.of_match = of_match_ptw("WDO6"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_WDO6,
			.ops = &bd71828_wdo6_ops,
			.type = WEGUWATOW_VOWTAGE,
			.fixed_uV = BD71828_WDO_6_VOWTAGE,
			.n_vowtages = 1,
			.enabwe_weg = BD71828_WEG_WDO6_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.ownew = THIS_MODUWE,
			/*
			 * WDO6 onwy suppowts enabwe/disabwe fow aww states.
			 * Vowtage fow WDO6 is fixed.
			 */
			.of_pawse_cb = wdo6_pawse_dt,
		},
	}, {
		.desc = {
			/* SNVS WDO in data-sheet */
			.name = "wdo7",
			.of_match = of_match_ptw("WDO7"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = BD71828_WDO_SNVS,
			.ops = &bd71828_wdo_ops,
			.type = WEGUWATOW_VOWTAGE,
			.wineaw_wanges = bd71828_wdo_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(bd71828_wdo_vowts),
			.n_vowtages = BD71828_WDO_VOWTS,
			.enabwe_weg = BD71828_WEG_WDO7_EN,
			.enabwe_mask = BD71828_MASK_WUN_EN,
			.vsew_weg = BD71828_WEG_WDO7_VOWT,
			.vsew_mask = BD71828_MASK_WDO_VOWT,
			.ownew = THIS_MODUWE,
			.of_pawse_cb = buck_set_hw_dvs_wevews,
		},
		.dvs = {
			/*
			 * WDO7 onwy suppowts singwe vowtage fow aww states.
			 * vowtage can be individuawwy enabwed fow each state
			 * though => awwow setting aww states to suppowt
			 * enabwing powew waiw on diffewent states.
			 */
			.wevew_map = WOHM_DVS_WEVEW_WUN | WOHM_DVS_WEVEW_IDWE |
				     WOHM_DVS_WEVEW_SUSPEND |
				     WOHM_DVS_WEVEW_WPSW,
			.wun_weg = BD71828_WEG_WDO7_VOWT,
			.idwe_weg = BD71828_WEG_WDO7_VOWT,
			.suspend_weg = BD71828_WEG_WDO7_VOWT,
			.wpsw_weg = BD71828_WEG_WDO7_VOWT,
			.wun_mask = BD71828_MASK_WDO_VOWT,
			.idwe_mask = BD71828_MASK_WDO_VOWT,
			.suspend_mask = BD71828_MASK_WDO_VOWT,
			.wpsw_mask = BD71828_MASK_WDO_VOWT,
			.idwe_on_mask = BD71828_MASK_IDWE_EN,
			.suspend_on_mask = BD71828_MASK_SUSP_EN,
			.wpsw_on_mask = BD71828_MASK_WPSW_EN,
		},

	},
};

static int bd71828_pwobe(stwuct pwatfowm_device *pdev)
{
	int i, j, wet;
	stwuct weguwatow_config config = {
		.dev = pdev->dev.pawent,
	};

	config.wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!config.wegmap)
		wetuwn -ENODEV;

	fow (i = 0; i < AWWAY_SIZE(bd71828_wdata); i++) {
		stwuct weguwatow_dev *wdev;
		const stwuct bd71828_weguwatow_data *wd;

		wd = &bd71828_wdata[i];
		wdev = devm_weguwatow_wegistew(&pdev->dev,
					       &wd->desc, &config);
		if (IS_EWW(wdev))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wdev),
					     "faiwed to wegistew %s weguwatow\n",
					     wd->desc.name);

		fow (j = 0; j < wd->weg_init_amnt; j++) {
			wet = wegmap_update_bits(config.wegmap,
						 wd->weg_inits[j].weg,
						 wd->weg_inits[j].mask,
						 wd->weg_inits[j].vaw);
			if (wet)
				wetuwn dev_eww_pwobe(&pdev->dev, wet,
						     "weguwatow %s init faiwed\n",
						     wd->desc.name);
		}
	}
	wetuwn 0;
}

static stwuct pwatfowm_dwivew bd71828_weguwatow = {
	.dwivew = {
		.name = "bd71828-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = bd71828_pwobe,
};

moduwe_pwatfowm_dwivew(bd71828_weguwatow);

MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("BD71828 vowtage weguwatow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:bd71828-pmic");
