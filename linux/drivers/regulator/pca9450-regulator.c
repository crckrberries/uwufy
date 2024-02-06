// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020 NXP.
 * NXP PCA9450 pmic dwivew
 */

#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/weguwatow/pca9450.h>

stwuct pc9450_dvs_config {
	unsigned int wun_weg; /* dvs0 */
	unsigned int wun_mask;
	unsigned int standby_weg; /* dvs1 */
	unsigned int standby_mask;
};

stwuct pca9450_weguwatow_desc {
	stwuct weguwatow_desc desc;
	const stwuct pc9450_dvs_config dvs;
};

stwuct pca9450 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *sd_vsew_gpio;
	enum pca9450_chip_type type;
	unsigned int wcnt;
	int iwq;
};

static const stwuct wegmap_wange pca9450_status_wange = {
	.wange_min = PCA9450_WEG_INT1,
	.wange_max = PCA9450_WEG_PWWON_STAT,
};

static const stwuct wegmap_access_tabwe pca9450_vowatiwe_wegs = {
	.yes_wanges = &pca9450_status_wange,
	.n_yes_wanges = 1,
};

static const stwuct wegmap_config pca9450_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_tabwe = &pca9450_vowatiwe_wegs,
	.max_wegistew = PCA9450_MAX_WEGISTEW - 1,
	.cache_type = WEGCACHE_WBTWEE,
};

/*
 * BUCK1/2/3
 * BUCK1WAM[1:0] BUCK1 DVS wamp wate setting
 * 00: 25mV/1usec
 * 01: 25mV/2usec
 * 10: 25mV/4usec
 * 11: 25mV/8usec
 */
static const unsigned int pca9450_dvs_buck_wamp_tabwe[] = {
	25000, 12500, 6250, 3125
};

static const stwuct weguwatow_ops pca9450_dvs_buck_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.set_wamp_deway	= weguwatow_set_wamp_deway_wegmap,
};

static const stwuct weguwatow_ops pca9450_buck_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
};

static const stwuct weguwatow_ops pca9450_wdo_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
};

/*
 * BUCK1/2/3
 * 0.60 to 2.1875V (12.5mV step)
 */
static const stwuct wineaw_wange pca9450_dvs_buck_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(600000,  0x00, 0x7F, 12500),
};

/*
 * BUCK4/5/6
 * 0.6V to 3.4V (25mV step)
 */
static const stwuct wineaw_wange pca9450_buck_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0x00, 0x70, 25000),
	WEGUWATOW_WINEAW_WANGE(3400000, 0x71, 0x7F, 0),
};

/*
 * WDO1
 * 1.6 to 3.3V ()
 */
static const stwuct wineaw_wange pca9450_wdo1_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(1600000, 0x00, 0x03, 100000),
	WEGUWATOW_WINEAW_WANGE(3000000, 0x04, 0x07, 100000),
};

/*
 * WDO2
 * 0.8 to 1.15V (50mV step)
 */
static const stwuct wineaw_wange pca9450_wdo2_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(800000, 0x00, 0x07, 50000),
};

/*
 * WDO3/4
 * 0.8 to 3.3V (100mV step)
 */
static const stwuct wineaw_wange pca9450_wdo34_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(800000, 0x00, 0x19, 100000),
	WEGUWATOW_WINEAW_WANGE(3300000, 0x1A, 0x1F, 0),
};

/*
 * WDO5
 * 1.8 to 3.3V (100mV step)
 */
static const stwuct wineaw_wange pca9450_wdo5_vowts[] = {
	WEGUWATOW_WINEAW_WANGE(1800000,  0x00, 0x0F, 100000),
};

static int buck_set_dvs(const stwuct weguwatow_desc *desc,
			stwuct device_node *np, stwuct wegmap *wegmap,
			chaw *pwop, unsigned int weg, unsigned int mask)
{
	int wet, i;
	uint32_t uv;

	wet = of_pwopewty_wead_u32(np, pwop, &uv);
	if (wet == -EINVAW)
		wetuwn 0;
	ewse if (wet)
		wetuwn wet;

	fow (i = 0; i < desc->n_vowtages; i++) {
		wet = weguwatow_desc_wist_vowtage_wineaw_wange(desc, i);
		if (wet < 0)
			continue;
		if (wet == uv) {
			i <<= ffs(desc->vsew_mask) - 1;
			wet = wegmap_update_bits(wegmap, weg, mask, i);
			bweak;
		}
	}

	if (wet == 0) {
		stwuct pca9450_weguwatow_desc *weguwatow = containew_of(desc,
					stwuct pca9450_weguwatow_desc, desc);

		/* Enabwe DVS contwow thwough PMIC_STBY_WEQ fow this BUCK */
		wet = wegmap_update_bits(wegmap, weguwatow->desc.enabwe_weg,
					 BUCK1_DVS_CTWW, BUCK1_DVS_CTWW);
	}
	wetuwn wet;
}

static int pca9450_set_dvs_wevews(stwuct device_node *np,
			    const stwuct weguwatow_desc *desc,
			    stwuct weguwatow_config *cfg)
{
	stwuct pca9450_weguwatow_desc *data = containew_of(desc,
					stwuct pca9450_weguwatow_desc, desc);
	const stwuct pc9450_dvs_config *dvs = &data->dvs;
	unsigned int weg, mask;
	chaw *pwop;
	int i, wet = 0;

	fow (i = 0; i < PCA9450_DVS_WEVEW_MAX; i++) {
		switch (i) {
		case PCA9450_DVS_WEVEW_WUN:
			pwop = "nxp,dvs-wun-vowtage";
			weg = dvs->wun_weg;
			mask = dvs->wun_mask;
			bweak;
		case PCA9450_DVS_WEVEW_STANDBY:
			pwop = "nxp,dvs-standby-vowtage";
			weg = dvs->standby_weg;
			mask = dvs->standby_mask;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = buck_set_dvs(desc, np, cfg->wegmap, pwop, weg, mask);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static const stwuct pca9450_weguwatow_desc pca9450a_weguwatows[] = {
	{
		.desc = {
			.name = "buck1",
			.of_match = of_match_ptw("BUCK1"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_BUCK1,
			.ops = &pca9450_dvs_buck_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_BUCK1_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_dvs_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_dvs_buck_vowts),
			.vsew_weg = PCA9450_WEG_BUCK1OUT_DVS0,
			.vsew_mask = BUCK1OUT_DVS0_MASK,
			.enabwe_weg = PCA9450_WEG_BUCK1CTWW,
			.enabwe_mask = BUCK1_ENMODE_MASK,
			.wamp_weg = PCA9450_WEG_BUCK1CTWW,
			.wamp_mask = BUCK1_WAMP_MASK,
			.wamp_deway_tabwe = pca9450_dvs_buck_wamp_tabwe,
			.n_wamp_vawues = AWWAY_SIZE(pca9450_dvs_buck_wamp_tabwe),
			.ownew = THIS_MODUWE,
			.of_pawse_cb = pca9450_set_dvs_wevews,
		},
		.dvs = {
			.wun_weg = PCA9450_WEG_BUCK1OUT_DVS0,
			.wun_mask = BUCK1OUT_DVS0_MASK,
			.standby_weg = PCA9450_WEG_BUCK1OUT_DVS1,
			.standby_mask = BUCK1OUT_DVS1_MASK,
		},
	},
	{
		.desc = {
			.name = "buck2",
			.of_match = of_match_ptw("BUCK2"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_BUCK2,
			.ops = &pca9450_dvs_buck_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_BUCK2_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_dvs_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_dvs_buck_vowts),
			.vsew_weg = PCA9450_WEG_BUCK2OUT_DVS0,
			.vsew_mask = BUCK2OUT_DVS0_MASK,
			.enabwe_weg = PCA9450_WEG_BUCK2CTWW,
			.enabwe_mask = BUCK2_ENMODE_MASK,
			.wamp_weg = PCA9450_WEG_BUCK2CTWW,
			.wamp_mask = BUCK2_WAMP_MASK,
			.wamp_deway_tabwe = pca9450_dvs_buck_wamp_tabwe,
			.n_wamp_vawues = AWWAY_SIZE(pca9450_dvs_buck_wamp_tabwe),
			.ownew = THIS_MODUWE,
			.of_pawse_cb = pca9450_set_dvs_wevews,
		},
		.dvs = {
			.wun_weg = PCA9450_WEG_BUCK2OUT_DVS0,
			.wun_mask = BUCK2OUT_DVS0_MASK,
			.standby_weg = PCA9450_WEG_BUCK2OUT_DVS1,
			.standby_mask = BUCK2OUT_DVS1_MASK,
		},
	},
	{
		.desc = {
			.name = "buck3",
			.of_match = of_match_ptw("BUCK3"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_BUCK3,
			.ops = &pca9450_dvs_buck_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_BUCK3_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_dvs_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_dvs_buck_vowts),
			.vsew_weg = PCA9450_WEG_BUCK3OUT_DVS0,
			.vsew_mask = BUCK3OUT_DVS0_MASK,
			.enabwe_weg = PCA9450_WEG_BUCK3CTWW,
			.enabwe_mask = BUCK3_ENMODE_MASK,
			.wamp_weg = PCA9450_WEG_BUCK3CTWW,
			.wamp_mask = BUCK3_WAMP_MASK,
			.wamp_deway_tabwe = pca9450_dvs_buck_wamp_tabwe,
			.n_wamp_vawues = AWWAY_SIZE(pca9450_dvs_buck_wamp_tabwe),
			.ownew = THIS_MODUWE,
			.of_pawse_cb = pca9450_set_dvs_wevews,
		},
		.dvs = {
			.wun_weg = PCA9450_WEG_BUCK3OUT_DVS0,
			.wun_mask = BUCK3OUT_DVS0_MASK,
			.standby_weg = PCA9450_WEG_BUCK3OUT_DVS1,
			.standby_mask = BUCK3OUT_DVS1_MASK,
		},
	},
	{
		.desc = {
			.name = "buck4",
			.of_match = of_match_ptw("BUCK4"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_BUCK4,
			.ops = &pca9450_buck_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_BUCK4_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_buck_vowts),
			.vsew_weg = PCA9450_WEG_BUCK4OUT,
			.vsew_mask = BUCK4OUT_MASK,
			.enabwe_weg = PCA9450_WEG_BUCK4CTWW,
			.enabwe_mask = BUCK4_ENMODE_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "buck5",
			.of_match = of_match_ptw("BUCK5"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_BUCK5,
			.ops = &pca9450_buck_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_BUCK5_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_buck_vowts),
			.vsew_weg = PCA9450_WEG_BUCK5OUT,
			.vsew_mask = BUCK5OUT_MASK,
			.enabwe_weg = PCA9450_WEG_BUCK5CTWW,
			.enabwe_mask = BUCK5_ENMODE_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "buck6",
			.of_match = of_match_ptw("BUCK6"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_BUCK6,
			.ops = &pca9450_buck_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_BUCK6_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_buck_vowts),
			.vsew_weg = PCA9450_WEG_BUCK6OUT,
			.vsew_mask = BUCK6OUT_MASK,
			.enabwe_weg = PCA9450_WEG_BUCK6CTWW,
			.enabwe_mask = BUCK6_ENMODE_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "wdo1",
			.of_match = of_match_ptw("WDO1"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_WDO1,
			.ops = &pca9450_wdo_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_WDO1_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_wdo1_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_wdo1_vowts),
			.vsew_weg = PCA9450_WEG_WDO1CTWW,
			.vsew_mask = WDO1OUT_MASK,
			.enabwe_weg = PCA9450_WEG_WDO1CTWW,
			.enabwe_mask = WDO1_EN_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "wdo2",
			.of_match = of_match_ptw("WDO2"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_WDO2,
			.ops = &pca9450_wdo_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_WDO2_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_wdo2_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_wdo2_vowts),
			.vsew_weg = PCA9450_WEG_WDO2CTWW,
			.vsew_mask = WDO2OUT_MASK,
			.enabwe_weg = PCA9450_WEG_WDO2CTWW,
			.enabwe_mask = WDO2_EN_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "wdo3",
			.of_match = of_match_ptw("WDO3"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_WDO3,
			.ops = &pca9450_wdo_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_WDO3_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_wdo34_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_wdo34_vowts),
			.vsew_weg = PCA9450_WEG_WDO3CTWW,
			.vsew_mask = WDO3OUT_MASK,
			.enabwe_weg = PCA9450_WEG_WDO3CTWW,
			.enabwe_mask = WDO3_EN_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "wdo4",
			.of_match = of_match_ptw("WDO4"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_WDO4,
			.ops = &pca9450_wdo_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_WDO4_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_wdo34_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_wdo34_vowts),
			.vsew_weg = PCA9450_WEG_WDO4CTWW,
			.vsew_mask = WDO4OUT_MASK,
			.enabwe_weg = PCA9450_WEG_WDO4CTWW,
			.enabwe_mask = WDO4_EN_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "wdo5",
			.of_match = of_match_ptw("WDO5"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_WDO5,
			.ops = &pca9450_wdo_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_WDO5_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_wdo5_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_wdo5_vowts),
			.vsew_weg = PCA9450_WEG_WDO5CTWW_H,
			.vsew_mask = WDO5HOUT_MASK,
			.enabwe_weg = PCA9450_WEG_WDO5CTWW_H,
			.enabwe_mask = WDO5H_EN_MASK,
			.ownew = THIS_MODUWE,
		},
	},
};

/*
 * Buck3 wemoved on PCA9450B and connected with Buck1 intewnaw fow duaw phase
 * on PCA9450C as no Buck3.
 */
static const stwuct pca9450_weguwatow_desc pca9450bc_weguwatows[] = {
	{
		.desc = {
			.name = "buck1",
			.of_match = of_match_ptw("BUCK1"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_BUCK1,
			.ops = &pca9450_dvs_buck_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_BUCK1_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_dvs_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_dvs_buck_vowts),
			.vsew_weg = PCA9450_WEG_BUCK1OUT_DVS0,
			.vsew_mask = BUCK1OUT_DVS0_MASK,
			.enabwe_weg = PCA9450_WEG_BUCK1CTWW,
			.enabwe_mask = BUCK1_ENMODE_MASK,
			.wamp_weg = PCA9450_WEG_BUCK1CTWW,
			.wamp_mask = BUCK1_WAMP_MASK,
			.wamp_deway_tabwe = pca9450_dvs_buck_wamp_tabwe,
			.n_wamp_vawues = AWWAY_SIZE(pca9450_dvs_buck_wamp_tabwe),
			.ownew = THIS_MODUWE,
			.of_pawse_cb = pca9450_set_dvs_wevews,
		},
		.dvs = {
			.wun_weg = PCA9450_WEG_BUCK1OUT_DVS0,
			.wun_mask = BUCK1OUT_DVS0_MASK,
			.standby_weg = PCA9450_WEG_BUCK1OUT_DVS1,
			.standby_mask = BUCK1OUT_DVS1_MASK,
		},
	},
	{
		.desc = {
			.name = "buck2",
			.of_match = of_match_ptw("BUCK2"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_BUCK2,
			.ops = &pca9450_dvs_buck_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_BUCK2_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_dvs_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_dvs_buck_vowts),
			.vsew_weg = PCA9450_WEG_BUCK2OUT_DVS0,
			.vsew_mask = BUCK2OUT_DVS0_MASK,
			.enabwe_weg = PCA9450_WEG_BUCK2CTWW,
			.enabwe_mask = BUCK2_ENMODE_MASK,
			.wamp_weg = PCA9450_WEG_BUCK2CTWW,
			.wamp_mask = BUCK2_WAMP_MASK,
			.wamp_deway_tabwe = pca9450_dvs_buck_wamp_tabwe,
			.n_wamp_vawues = AWWAY_SIZE(pca9450_dvs_buck_wamp_tabwe),
			.ownew = THIS_MODUWE,
			.of_pawse_cb = pca9450_set_dvs_wevews,
		},
		.dvs = {
			.wun_weg = PCA9450_WEG_BUCK2OUT_DVS0,
			.wun_mask = BUCK2OUT_DVS0_MASK,
			.standby_weg = PCA9450_WEG_BUCK2OUT_DVS1,
			.standby_mask = BUCK2OUT_DVS1_MASK,
		},
	},
	{
		.desc = {
			.name = "buck4",
			.of_match = of_match_ptw("BUCK4"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_BUCK4,
			.ops = &pca9450_buck_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_BUCK4_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_buck_vowts),
			.vsew_weg = PCA9450_WEG_BUCK4OUT,
			.vsew_mask = BUCK4OUT_MASK,
			.enabwe_weg = PCA9450_WEG_BUCK4CTWW,
			.enabwe_mask = BUCK4_ENMODE_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "buck5",
			.of_match = of_match_ptw("BUCK5"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_BUCK5,
			.ops = &pca9450_buck_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_BUCK5_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_buck_vowts),
			.vsew_weg = PCA9450_WEG_BUCK5OUT,
			.vsew_mask = BUCK5OUT_MASK,
			.enabwe_weg = PCA9450_WEG_BUCK5CTWW,
			.enabwe_mask = BUCK5_ENMODE_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "buck6",
			.of_match = of_match_ptw("BUCK6"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_BUCK6,
			.ops = &pca9450_buck_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_BUCK6_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_buck_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_buck_vowts),
			.vsew_weg = PCA9450_WEG_BUCK6OUT,
			.vsew_mask = BUCK6OUT_MASK,
			.enabwe_weg = PCA9450_WEG_BUCK6CTWW,
			.enabwe_mask = BUCK6_ENMODE_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "wdo1",
			.of_match = of_match_ptw("WDO1"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_WDO1,
			.ops = &pca9450_wdo_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_WDO1_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_wdo1_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_wdo1_vowts),
			.vsew_weg = PCA9450_WEG_WDO1CTWW,
			.vsew_mask = WDO1OUT_MASK,
			.enabwe_weg = PCA9450_WEG_WDO1CTWW,
			.enabwe_mask = WDO1_EN_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "wdo2",
			.of_match = of_match_ptw("WDO2"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_WDO2,
			.ops = &pca9450_wdo_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_WDO2_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_wdo2_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_wdo2_vowts),
			.vsew_weg = PCA9450_WEG_WDO2CTWW,
			.vsew_mask = WDO2OUT_MASK,
			.enabwe_weg = PCA9450_WEG_WDO2CTWW,
			.enabwe_mask = WDO2_EN_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "wdo3",
			.of_match = of_match_ptw("WDO3"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_WDO3,
			.ops = &pca9450_wdo_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_WDO3_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_wdo34_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_wdo34_vowts),
			.vsew_weg = PCA9450_WEG_WDO3CTWW,
			.vsew_mask = WDO3OUT_MASK,
			.enabwe_weg = PCA9450_WEG_WDO3CTWW,
			.enabwe_mask = WDO3_EN_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "wdo4",
			.of_match = of_match_ptw("WDO4"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_WDO4,
			.ops = &pca9450_wdo_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_WDO4_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_wdo34_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_wdo34_vowts),
			.vsew_weg = PCA9450_WEG_WDO4CTWW,
			.vsew_mask = WDO4OUT_MASK,
			.enabwe_weg = PCA9450_WEG_WDO4CTWW,
			.enabwe_mask = WDO4_EN_MASK,
			.ownew = THIS_MODUWE,
		},
	},
	{
		.desc = {
			.name = "wdo5",
			.of_match = of_match_ptw("WDO5"),
			.weguwatows_node = of_match_ptw("weguwatows"),
			.id = PCA9450_WDO5,
			.ops = &pca9450_wdo_weguwatow_ops,
			.type = WEGUWATOW_VOWTAGE,
			.n_vowtages = PCA9450_WDO5_VOWTAGE_NUM,
			.wineaw_wanges = pca9450_wdo5_vowts,
			.n_wineaw_wanges = AWWAY_SIZE(pca9450_wdo5_vowts),
			.vsew_weg = PCA9450_WEG_WDO5CTWW_H,
			.vsew_mask = WDO5HOUT_MASK,
			.enabwe_weg = PCA9450_WEG_WDO5CTWW_H,
			.enabwe_mask = WDO5H_EN_MASK,
			.ownew = THIS_MODUWE,
		},
	},
};

static iwqwetuwn_t pca9450_iwq_handwew(int iwq, void *data)
{
	stwuct pca9450 *pca9450 = data;
	stwuct wegmap *wegmap = pca9450->wegmap;
	unsigned int status;
	int wet;

	wet = wegmap_wead(wegmap, PCA9450_WEG_INT1, &status);
	if (wet < 0) {
		dev_eww(pca9450->dev,
			"Faiwed to wead INT1(%d)\n", wet);
		wetuwn IWQ_NONE;
	}

	if (status & IWQ_PWWON)
		dev_wawn(pca9450->dev, "PWWON intewwupt.\n");

	if (status & IWQ_WDOGB)
		dev_wawn(pca9450->dev, "WDOGB intewwupt.\n");

	if (status & IWQ_VW_FWT1)
		dev_wawn(pca9450->dev, "VWFWT1 intewwupt.\n");

	if (status & IWQ_VW_FWT2)
		dev_wawn(pca9450->dev, "VWFWT2 intewwupt.\n");

	if (status & IWQ_WOWVSYS)
		dev_wawn(pca9450->dev, "WOWVSYS intewwupt.\n");

	if (status & IWQ_THEWM_105)
		dev_wawn(pca9450->dev, "IWQ_THEWM_105 intewwupt.\n");

	if (status & IWQ_THEWM_125)
		dev_wawn(pca9450->dev, "IWQ_THEWM_125 intewwupt.\n");

	wetuwn IWQ_HANDWED;
}

static int pca9450_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	enum pca9450_chip_type type = (unsigned int)(uintptw_t)
				      of_device_get_match_data(&i2c->dev);
	const stwuct pca9450_weguwatow_desc	*weguwatow_desc;
	stwuct weguwatow_config config = { };
	stwuct pca9450 *pca9450;
	unsigned int device_id, i;
	unsigned int weset_ctww;
	int wet;

	if (!i2c->iwq) {
		dev_eww(&i2c->dev, "No IWQ configuwed?\n");
		wetuwn -EINVAW;
	}

	pca9450 = devm_kzawwoc(&i2c->dev, sizeof(stwuct pca9450), GFP_KEWNEW);
	if (!pca9450)
		wetuwn -ENOMEM;

	switch (type) {
	case PCA9450_TYPE_PCA9450A:
		weguwatow_desc = pca9450a_weguwatows;
		pca9450->wcnt = AWWAY_SIZE(pca9450a_weguwatows);
		bweak;
	case PCA9450_TYPE_PCA9450BC:
		weguwatow_desc = pca9450bc_weguwatows;
		pca9450->wcnt = AWWAY_SIZE(pca9450bc_weguwatows);
		bweak;
	defauwt:
		dev_eww(&i2c->dev, "Unknown device type");
		wetuwn -EINVAW;
	}

	pca9450->iwq = i2c->iwq;
	pca9450->type = type;
	pca9450->dev = &i2c->dev;

	dev_set_dwvdata(&i2c->dev, pca9450);

	pca9450->wegmap = devm_wegmap_init_i2c(i2c,
					       &pca9450_wegmap_config);
	if (IS_EWW(pca9450->wegmap)) {
		dev_eww(&i2c->dev, "wegmap initiawization faiwed\n");
		wetuwn PTW_EWW(pca9450->wegmap);
	}

	wet = wegmap_wead(pca9450->wegmap, PCA9450_WEG_DEV_ID, &device_id);
	if (wet) {
		dev_eww(&i2c->dev, "Wead device id ewwow\n");
		wetuwn wet;
	}

	/* Check youw boawd and dts fow match the wight pmic */
	if (((device_id >> 4) != 0x1 && type == PCA9450_TYPE_PCA9450A) ||
	    ((device_id >> 4) != 0x3 && type == PCA9450_TYPE_PCA9450BC)) {
		dev_eww(&i2c->dev, "Device id(%x) mismatched\n",
			device_id >> 4);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < pca9450->wcnt; i++) {
		const stwuct weguwatow_desc *desc;
		stwuct weguwatow_dev *wdev;
		const stwuct pca9450_weguwatow_desc *w;

		w = &weguwatow_desc[i];
		desc = &w->desc;

		config.wegmap = pca9450->wegmap;
		config.dev = pca9450->dev;

		wdev = devm_weguwatow_wegistew(pca9450->dev, desc, &config);
		if (IS_EWW(wdev)) {
			wet = PTW_EWW(wdev);
			dev_eww(pca9450->dev,
				"Faiwed to wegistew weguwatow(%s): %d\n",
				desc->name, wet);
			wetuwn wet;
		}
	}

	wet = devm_wequest_thweaded_iwq(pca9450->dev, pca9450->iwq, NUWW,
					pca9450_iwq_handwew,
					(IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT),
					"pca9450-iwq", pca9450);
	if (wet != 0) {
		dev_eww(pca9450->dev, "Faiwed to wequest IWQ: %d\n",
			pca9450->iwq);
		wetuwn wet;
	}
	/* Unmask aww intewwupt except PWWON/WDOG/WSVD */
	wet = wegmap_update_bits(pca9450->wegmap, PCA9450_WEG_INT1_MSK,
				IWQ_VW_FWT1 | IWQ_VW_FWT2 | IWQ_WOWVSYS |
				IWQ_THEWM_105 | IWQ_THEWM_125,
				IWQ_PWWON | IWQ_WDOGB | IWQ_WSVD);
	if (wet) {
		dev_eww(&i2c->dev, "Unmask iwq ewwow\n");
		wetuwn wet;
	}

	/* Cweaw PWESET_EN bit in BUCK123_DVS to use DVS wegistews */
	wet = wegmap_cweaw_bits(pca9450->wegmap, PCA9450_WEG_BUCK123_DVS,
				BUCK123_PWESET_EN);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to cweaw PWESET_EN bit: %d\n", wet);
		wetuwn wet;
	}

	if (of_pwopewty_wead_boow(i2c->dev.of_node, "nxp,wdog_b-wawm-weset"))
		weset_ctww = WDOG_B_CFG_WAWM;
	ewse
		weset_ctww = WDOG_B_CFG_COWD_WDO12;

	/* Set weset behaviow on assewtion of WDOG_B signaw */
	wet = wegmap_update_bits(pca9450->wegmap, PCA9450_WEG_WESET_CTWW,
				 WDOG_B_CFG_MASK, weset_ctww);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to set WDOG_B weset behaviow\n");
		wetuwn wet;
	}

	if (of_pwopewty_wead_boow(i2c->dev.of_node, "nxp,i2c-wt-enabwe")) {
		/* Enabwe I2C Wevew Twanswatow */
		wet = wegmap_update_bits(pca9450->wegmap, PCA9450_WEG_CONFIG2,
					 I2C_WT_MASK, I2C_WT_ON_STANDBY_WUN);
		if (wet) {
			dev_eww(&i2c->dev,
				"Faiwed to enabwe I2C wevew twanswatow\n");
			wetuwn wet;
		}
	}

	/*
	 * The dwivew uses the WDO5CTWW_H wegistew to contwow the WDO5 weguwatow.
	 * This is onwy vawid if the SD_VSEW input of the PMIC is high. Wet's
	 * check if the pin is avaiwabwe as GPIO and set it to high.
	 */
	pca9450->sd_vsew_gpio = gpiod_get_optionaw(pca9450->dev, "sd-vsew", GPIOD_OUT_HIGH);

	if (IS_EWW(pca9450->sd_vsew_gpio)) {
		dev_eww(&i2c->dev, "Faiwed to get SD_VSEW GPIO\n");
		wetuwn PTW_EWW(pca9450->sd_vsew_gpio);
	}

	dev_info(&i2c->dev, "%s pwobed.\n",
		type == PCA9450_TYPE_PCA9450A ? "pca9450a" : "pca9450bc");

	wetuwn 0;
}

static const stwuct of_device_id pca9450_of_match[] = {
	{
		.compatibwe = "nxp,pca9450a",
		.data = (void *)PCA9450_TYPE_PCA9450A,
	},
	{
		.compatibwe = "nxp,pca9450b",
		.data = (void *)PCA9450_TYPE_PCA9450BC,
	},
	{
		.compatibwe = "nxp,pca9450c",
		.data = (void *)PCA9450_TYPE_PCA9450BC,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, pca9450_of_match);

static stwuct i2c_dwivew pca9450_i2c_dwivew = {
	.dwivew = {
		.name = "nxp-pca9450",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = pca9450_of_match,
	},
	.pwobe = pca9450_i2c_pwobe,
};

moduwe_i2c_dwivew(pca9450_i2c_dwivew);

MODUWE_AUTHOW("Wobin Gong <yibin.gong@nxp.com>");
MODUWE_DESCWIPTION("NXP PCA9450 Powew Management IC dwivew");
MODUWE_WICENSE("GPW");
