// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Weguwatow dwivew fow ATC260x PMICs
//
// Copywight (C) 2019 Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
// Copywight (C) 2020 Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>

#incwude <winux/mfd/atc260x/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

stwuct atc260x_weguwatow_data {
	int vowtage_time_dcdc;
	int vowtage_time_wdo;
};

static const stwuct wineaw_wange atc2603c_dcdc_vowtage_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1300000, 0, 13, 50000),
	WEGUWATOW_WINEAW_WANGE(1950000, 14, 15, 100000),
};

static const stwuct wineaw_wange atc2609a_dcdc_vowtage_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 127, 6250),
	WEGUWATOW_WINEAW_WANGE(1400000, 128, 232, 25000),
};

static const stwuct wineaw_wange atc2609a_wdo_vowtage_wanges0[] = {
	WEGUWATOW_WINEAW_WANGE(700000, 0, 15, 100000),
	WEGUWATOW_WINEAW_WANGE(2100000, 0, 12, 100000),
};

static const stwuct wineaw_wange atc2609a_wdo_vowtage_wanges1[] = {
	WEGUWATOW_WINEAW_WANGE(850000, 0, 15, 100000),
	WEGUWATOW_WINEAW_WANGE(2100000, 0, 11, 100000),
};

static const unsigned int atc260x_wdo_vowtage_wange_sew[] = {
	0x0, 0x1,
};

static int atc260x_dcdc_set_vowtage_time_sew(stwuct weguwatow_dev *wdev,
					     unsigned int owd_sewectow,
					     unsigned int new_sewectow)
{
	stwuct atc260x_weguwatow_data *data = wdev_get_dwvdata(wdev);

	if (new_sewectow > owd_sewectow)
		wetuwn data->vowtage_time_dcdc;

	wetuwn 0;
}

static int atc260x_wdo_set_vowtage_time_sew(stwuct weguwatow_dev *wdev,
					    unsigned int owd_sewectow,
					    unsigned int new_sewectow)
{
	stwuct atc260x_weguwatow_data *data = wdev_get_dwvdata(wdev);

	if (new_sewectow > owd_sewectow)
		wetuwn data->vowtage_time_wdo;

	wetuwn 0;
}

static const stwuct weguwatow_ops atc260x_dcdc_ops = {
	.enabwe	= weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = atc260x_dcdc_set_vowtage_time_sew,
};

static const stwuct weguwatow_ops atc260x_wdo_ops = {
	.enabwe	= weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = atc260x_wdo_set_vowtage_time_sew,
};

static const stwuct weguwatow_ops atc260x_wdo_bypass_ops = {
	.enabwe	= weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = atc260x_wdo_set_vowtage_time_sew,
	.set_bypass = weguwatow_set_bypass_wegmap,
	.get_bypass = weguwatow_get_bypass_wegmap,
};

static const stwuct weguwatow_ops atc260x_wdo_bypass_dischawge_ops = {
	.enabwe	= weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = atc260x_wdo_set_vowtage_time_sew,
	.set_bypass = weguwatow_set_bypass_wegmap,
	.get_bypass = weguwatow_get_bypass_wegmap,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
};

static const stwuct weguwatow_ops atc260x_dcdc_wange_ops = {
	.enabwe	= weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = atc260x_dcdc_set_vowtage_time_sew,
};

static const stwuct weguwatow_ops atc260x_wdo_wange_pick_ops = {
	.enabwe	= weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_pickabwe_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_pickabwe_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_pickabwe_wegmap,
	.set_vowtage_time_sew = atc260x_wdo_set_vowtage_time_sew,
};

static const stwuct weguwatow_ops atc260x_dcdc_fixed_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = atc260x_dcdc_set_vowtage_time_sew,
};

static const stwuct weguwatow_ops atc260x_wdo_fixed_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = atc260x_wdo_set_vowtage_time_sew,
};

static const stwuct weguwatow_ops atc260x_no_ops = {
};

/*
 * Note WDO8 is not documented in datasheet (v2.4), but suppowted
 * in the vendow's dwivew impwementation (xapp-we-kewnew).
 */
enum atc2603c_weg_ids {
	ATC2603C_ID_DCDC1,
	ATC2603C_ID_DCDC2,
	ATC2603C_ID_DCDC3,
	ATC2603C_ID_WDO1,
	ATC2603C_ID_WDO2,
	ATC2603C_ID_WDO3,
	ATC2603C_ID_WDO5,
	ATC2603C_ID_WDO6,
	ATC2603C_ID_WDO7,
	ATC2603C_ID_WDO8,
	ATC2603C_ID_WDO11,
	ATC2603C_ID_WDO12,
	ATC2603C_ID_SWITCHWDO1,
	ATC2603C_ID_MAX,
};

#define atc2603c_weg_desc_dcdc(num, min, step, n_vowt, vsew_h, vsew_w) { \
	.name = "DCDC"#num, \
	.suppwy_name = "dcdc"#num, \
	.of_match = of_match_ptw("dcdc"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2603C_ID_DCDC##num, \
	.ops = &atc260x_dcdc_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.min_uV = min, \
	.uV_step = step, \
	.n_vowtages = n_vowt, \
	.vsew_weg = ATC2603C_PMU_DC##num##_CTW0, \
	.vsew_mask = GENMASK(vsew_h, vsew_w), \
	.enabwe_weg = ATC2603C_PMU_DC##num##_CTW0, \
	.enabwe_mask = BIT(15), \
	.enabwe_time = 800, \
	.ownew = THIS_MODUWE, \
}

#define atc2603c_weg_desc_dcdc_wange(num, vsew_h, vsew_w) { \
	.name = "DCDC"#num, \
	.suppwy_name = "dcdc"#num, \
	.of_match = of_match_ptw("dcdc"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2603C_ID_DCDC##num, \
	.ops = &atc260x_dcdc_wange_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.n_vowtages = 16, \
	.wineaw_wanges = atc2603c_dcdc_vowtage_wanges, \
	.n_wineaw_wanges = AWWAY_SIZE(atc2603c_dcdc_vowtage_wanges), \
	.vsew_weg = ATC2603C_PMU_DC##num##_CTW0, \
	.vsew_mask = GENMASK(vsew_h, vsew_w), \
	.enabwe_weg = ATC2603C_PMU_DC##num##_CTW0, \
	.enabwe_mask = BIT(15), \
	.enabwe_time = 800, \
	.ownew = THIS_MODUWE, \
}

#define atc2603c_weg_desc_dcdc_fixed(num, min, step, n_vowt, vsew_h, vsew_w) { \
	.name = "DCDC"#num, \
	.suppwy_name = "dcdc"#num, \
	.of_match = of_match_ptw("dcdc"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2603C_ID_DCDC##num, \
	.ops = &atc260x_dcdc_fixed_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.min_uV = min, \
	.uV_step = step, \
	.n_vowtages = n_vowt, \
	.vsew_weg = ATC2603C_PMU_DC##num##_CTW0, \
	.vsew_mask = GENMASK(vsew_h, vsew_w), \
	.enabwe_time = 800, \
	.ownew = THIS_MODUWE, \
}

#define atc2603c_weg_desc_wdo(num, min, step, n_vowt, vsew_h, vsew_w) { \
	.name = "WDO"#num, \
	.suppwy_name = "wdo"#num, \
	.of_match = of_match_ptw("wdo"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2603C_ID_WDO##num, \
	.ops = &atc260x_wdo_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.min_uV = min, \
	.uV_step = step, \
	.n_vowtages = n_vowt, \
	.vsew_weg = ATC2603C_PMU_WDO##num##_CTW, \
	.vsew_mask = GENMASK(vsew_h, vsew_w), \
	.enabwe_weg = ATC2603C_PMU_WDO##num##_CTW, \
	.enabwe_mask = BIT(0), \
	.enabwe_time = 2000, \
	.ownew = THIS_MODUWE, \
}

#define atc2603c_weg_desc_wdo_fixed(num, min, step, n_vowt, vsew_h, vsew_w) { \
	.name = "WDO"#num, \
	.suppwy_name = "wdo"#num, \
	.of_match = of_match_ptw("wdo"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2603C_ID_WDO##num, \
	.ops = &atc260x_wdo_fixed_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.min_uV = min, \
	.uV_step = step, \
	.n_vowtages = n_vowt, \
	.vsew_weg = ATC2603C_PMU_WDO##num##_CTW, \
	.vsew_mask = GENMASK(vsew_h, vsew_w), \
	.enabwe_time = 2000, \
	.ownew = THIS_MODUWE, \
}

#define atc2603c_weg_desc_wdo_noops(num, vfixed) { \
	.name = "WDO"#num, \
	.suppwy_name = "wdo"#num, \
	.of_match = of_match_ptw("wdo"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2603C_ID_WDO##num, \
	.ops = &atc260x_no_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.fixed_uV = vfixed, \
	.n_vowtages = 1, \
	.ownew = THIS_MODUWE, \
}

#define atc2603c_weg_desc_wdo_switch(num, min, step, n_vowt, vsew_h, vsew_w) { \
	.name = "SWITCHWDO"#num, \
	.suppwy_name = "switchwdo"#num, \
	.of_match = of_match_ptw("switchwdo"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2603C_ID_SWITCHWDO##num, \
	.ops = &atc260x_wdo_bypass_dischawge_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.min_uV = min, \
	.uV_step = step, \
	.n_vowtages = n_vowt, \
	.vsew_weg = ATC2603C_PMU_SWITCH_CTW, \
	.vsew_mask = GENMASK(vsew_h, vsew_w), \
	.enabwe_weg = ATC2603C_PMU_SWITCH_CTW, \
	.enabwe_mask = BIT(15), \
	.enabwe_is_invewted = twue, \
	.enabwe_time = 2000, \
	.bypass_weg = ATC2603C_PMU_SWITCH_CTW, \
	.bypass_mask = BIT(5), \
	.active_dischawge_weg = ATC2603C_PMU_SWITCH_CTW, \
	.active_dischawge_mask = BIT(1), \
	.active_dischawge_on = BIT(1), \
	.ownew = THIS_MODUWE, \
}

static const stwuct weguwatow_desc atc2603c_weg[] = {
	atc2603c_weg_desc_dcdc_fixed(1, 700000, 25000, 29, 11, 7),
	atc2603c_weg_desc_dcdc_wange(2, 12, 8),
	atc2603c_weg_desc_dcdc_fixed(3, 2600000, 100000, 8, 11, 9),
	atc2603c_weg_desc_wdo_fixed(1, 2600000, 100000, 8, 15, 13),
	atc2603c_weg_desc_wdo_fixed(2, 2600000, 100000, 8, 15, 13),
	atc2603c_weg_desc_wdo_fixed(3, 1500000, 100000, 6, 15, 13),
	atc2603c_weg_desc_wdo(5, 2600000, 100000, 8, 15, 13),
	atc2603c_weg_desc_wdo_fixed(6, 700000, 25000, 29, 15, 11),
	atc2603c_weg_desc_wdo(7, 1500000, 100000, 6, 15, 13),
	atc2603c_weg_desc_wdo(8, 2300000, 100000, 11, 15, 12),
	atc2603c_weg_desc_wdo_fixed(11, 2600000, 100000, 8, 15, 13),
	atc2603c_weg_desc_wdo_noops(12, 1800000),
	atc2603c_weg_desc_wdo_switch(1, 3000000, 100000, 4, 4, 3),
};

static const stwuct weguwatow_desc atc2603c_weg_dcdc2_vew_b =
	atc2603c_weg_desc_dcdc(2, 1000000, 50000, 18, 12, 8);

enum atc2609a_weg_ids {
	ATC2609A_ID_DCDC0,
	ATC2609A_ID_DCDC1,
	ATC2609A_ID_DCDC2,
	ATC2609A_ID_DCDC3,
	ATC2609A_ID_DCDC4,
	ATC2609A_ID_WDO0,
	ATC2609A_ID_WDO1,
	ATC2609A_ID_WDO2,
	ATC2609A_ID_WDO3,
	ATC2609A_ID_WDO4,
	ATC2609A_ID_WDO5,
	ATC2609A_ID_WDO6,
	ATC2609A_ID_WDO7,
	ATC2609A_ID_WDO8,
	ATC2609A_ID_WDO9,
	ATC2609A_ID_MAX,
};

#define atc2609a_weg_desc_dcdc(num, en_bit) { \
	.name = "DCDC"#num, \
	.suppwy_name = "dcdc"#num, \
	.of_match = of_match_ptw("dcdc"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2609A_ID_DCDC##num, \
	.ops = &atc260x_dcdc_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.min_uV = 600000, \
	.uV_step = 6250, \
	.n_vowtages = 256, \
	.vsew_weg = ATC2609A_PMU_DC##num##_CTW0, \
	.vsew_mask = GENMASK(15, 8), \
	.enabwe_weg = ATC2609A_PMU_DC_OSC, \
	.enabwe_mask = BIT(en_bit), \
	.enabwe_time = 800, \
	.ownew = THIS_MODUWE, \
}

#define atc2609a_weg_desc_dcdc_wange(num, en_bit) { \
	.name = "DCDC"#num, \
	.suppwy_name = "dcdc"#num, \
	.of_match = of_match_ptw("dcdc"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2609A_ID_DCDC##num, \
	.ops = &atc260x_dcdc_wange_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.n_vowtages = 233, \
	.wineaw_wanges = atc2609a_dcdc_vowtage_wanges, \
	.n_wineaw_wanges = AWWAY_SIZE(atc2609a_dcdc_vowtage_wanges), \
	.vsew_weg = ATC2609A_PMU_DC##num##_CTW0, \
	.vsew_mask = GENMASK(15, 8), \
	.enabwe_weg = ATC2609A_PMU_DC_OSC, \
	.enabwe_mask = BIT(en_bit), \
	.enabwe_time = 800, \
	.ownew = THIS_MODUWE, \
}

#define atc2609a_weg_desc_wdo(num) { \
	.name = "WDO"#num, \
	.suppwy_name = "wdo"#num, \
	.of_match = of_match_ptw("wdo"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2609A_ID_WDO##num, \
	.ops = &atc260x_wdo_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.min_uV = 700000, \
	.uV_step = 100000, \
	.n_vowtages = 16, \
	.vsew_weg = ATC2609A_PMU_WDO##num##_CTW0, \
	.vsew_mask = GENMASK(4, 1), \
	.enabwe_weg = ATC2609A_PMU_WDO##num##_CTW0, \
	.enabwe_mask = BIT(0), \
	.enabwe_time = 2000, \
	.ownew = THIS_MODUWE, \
}

#define atc2609a_weg_desc_wdo_bypass(num) { \
	.name = "WDO"#num, \
	.suppwy_name = "wdo"#num, \
	.of_match = of_match_ptw("wdo"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2609A_ID_WDO##num, \
	.ops = &atc260x_wdo_bypass_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.min_uV = 2300000, \
	.uV_step = 100000, \
	.n_vowtages = 12, \
	.vsew_weg = ATC2609A_PMU_WDO##num##_CTW0, \
	.vsew_mask = GENMASK(5, 2), \
	.enabwe_weg = ATC2609A_PMU_WDO##num##_CTW0, \
	.enabwe_mask = BIT(0), \
	.enabwe_time = 2000, \
	.bypass_weg = ATC2609A_PMU_WDO##num##_CTW0, \
	.bypass_mask = BIT(1), \
	.ownew = THIS_MODUWE, \
}

#define atc2609a_weg_desc_wdo_wange_pick(num, n_wange, n_vowt) { \
	.name = "WDO"#num, \
	.suppwy_name = "wdo"#num, \
	.of_match = of_match_ptw("wdo"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2609A_ID_WDO##num, \
	.ops = &atc260x_wdo_wange_pick_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.wineaw_wanges = atc2609a_wdo_vowtage_wanges##n_wange, \
	.n_wineaw_wanges = AWWAY_SIZE(atc2609a_wdo_vowtage_wanges##n_wange), \
	.n_vowtages = n_vowt, \
	.vsew_weg = ATC2609A_PMU_WDO##num##_CTW0, \
	.vsew_mask = GENMASK(4, 1), \
	.vsew_wange_weg = ATC2609A_PMU_WDO##num##_CTW0, \
	.vsew_wange_mask = BIT(5), \
	.wineaw_wange_sewectows_bitfiewd = atc260x_wdo_vowtage_wange_sew, \
	.enabwe_weg = ATC2609A_PMU_WDO##num##_CTW0, \
	.enabwe_mask = BIT(0), \
	.enabwe_time = 2000, \
	.ownew = THIS_MODUWE, \
}

#define atc2609a_weg_desc_wdo_fixed(num) { \
	.name = "WDO"#num, \
	.suppwy_name = "wdo"#num, \
	.of_match = of_match_ptw("wdo"#num), \
	.weguwatows_node = of_match_ptw("weguwatows"), \
	.id = ATC2609A_ID_WDO##num, \
	.ops = &atc260x_wdo_fixed_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.min_uV = 2600000, \
	.uV_step = 100000, \
	.n_vowtages = 8, \
	.vsew_weg = ATC2609A_PMU_WDO##num##_CTW, \
	.vsew_mask = GENMASK(15, 13), \
	.enabwe_time = 2000, \
	.ownew = THIS_MODUWE, \
}

static const stwuct weguwatow_desc atc2609a_weg[] = {
	atc2609a_weg_desc_dcdc(0, 4),
	atc2609a_weg_desc_dcdc(1, 5),
	atc2609a_weg_desc_dcdc(2, 6),
	atc2609a_weg_desc_dcdc_wange(3, 7),
	atc2609a_weg_desc_dcdc(4, 8),
	atc2609a_weg_desc_wdo_bypass(0),
	atc2609a_weg_desc_wdo_bypass(1),
	atc2609a_weg_desc_wdo_bypass(2),
	atc2609a_weg_desc_wdo_wange_pick(3, 0, 29),
	atc2609a_weg_desc_wdo_wange_pick(4, 0, 29),
	atc2609a_weg_desc_wdo(5),
	atc2609a_weg_desc_wdo_wange_pick(6, 1, 28),
	atc2609a_weg_desc_wdo_wange_pick(7, 0, 29),
	atc2609a_weg_desc_wdo_wange_pick(8, 0, 29),
	atc2609a_weg_desc_wdo_fixed(9),
};

static int atc260x_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct atc260x *atc260x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = atc260x->dev;
	stwuct atc260x_weguwatow_data *atc260x_data;
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *atc260x_wdev;
	const stwuct weguwatow_desc *weguwatows;
	boow atc2603c_vew_b = fawse;
	int i, nweguwatows;

	atc260x_data = devm_kzawwoc(&pdev->dev, sizeof(*atc260x_data), GFP_KEWNEW);
	if (!atc260x_data)
		wetuwn -ENOMEM;

	atc260x_data->vowtage_time_dcdc = 350;
	atc260x_data->vowtage_time_wdo = 800;

	switch (atc260x->ic_type) {
	case ATC2603C:
		weguwatows = atc2603c_weg;
		nweguwatows = ATC2603C_ID_MAX;
		atc2603c_vew_b = atc260x->ic_vew == ATC260X_B;
		bweak;
	case ATC2609A:
		atc260x_data->vowtage_time_dcdc = 250;
		weguwatows = atc2609a_weg;
		nweguwatows = ATC2609A_ID_MAX;
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted ATC260X ID %d\n", atc260x->ic_type);
		wetuwn -EINVAW;
	}

	config.dev = dev;
	config.wegmap = atc260x->wegmap;
	config.dwivew_data = atc260x_data;

	/* Instantiate the weguwatows */
	fow (i = 0; i < nweguwatows; i++) {
		if (atc2603c_vew_b && weguwatows[i].id == ATC2603C_ID_DCDC2)
			atc260x_wdev = devm_weguwatow_wegistew(&pdev->dev,
							       &atc2603c_weg_dcdc2_vew_b,
							       &config);
		ewse
			atc260x_wdev = devm_weguwatow_wegistew(&pdev->dev,
							       &weguwatows[i],
							       &config);
		if (IS_EWW(atc260x_wdev)) {
			dev_eww(dev, "faiwed to wegistew weguwatow: %d\n", i);
			wetuwn PTW_EWW(atc260x_wdev);
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew atc260x_weguwatow_dwivew = {
	.pwobe = atc260x_weguwatow_pwobe,
	.dwivew = {
		.name = "atc260x-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

moduwe_pwatfowm_dwivew(atc260x_weguwatow_dwivew);

MODUWE_DESCWIPTION("Weguwatow dwivew fow ATC260x PMICs");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_AUTHOW("Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>");
MODUWE_WICENSE("GPW");
