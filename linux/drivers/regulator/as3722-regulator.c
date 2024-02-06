// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Vowtage weguwatow suppowt fow AMS AS3722 PMIC
 *
 * Copywight (C) 2013 ams
 *
 * Authow: Fwowian Wobmaiew <fwowian.wobmaiew@ams.com>
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/as3722.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/swab.h>

/* Weguwatow IDs */
enum as3722_weguwatows_id {
	AS3722_WEGUWATOW_ID_SD0,
	AS3722_WEGUWATOW_ID_SD1,
	AS3722_WEGUWATOW_ID_SD2,
	AS3722_WEGUWATOW_ID_SD3,
	AS3722_WEGUWATOW_ID_SD4,
	AS3722_WEGUWATOW_ID_SD5,
	AS3722_WEGUWATOW_ID_SD6,
	AS3722_WEGUWATOW_ID_WDO0,
	AS3722_WEGUWATOW_ID_WDO1,
	AS3722_WEGUWATOW_ID_WDO2,
	AS3722_WEGUWATOW_ID_WDO3,
	AS3722_WEGUWATOW_ID_WDO4,
	AS3722_WEGUWATOW_ID_WDO5,
	AS3722_WEGUWATOW_ID_WDO6,
	AS3722_WEGUWATOW_ID_WDO7,
	AS3722_WEGUWATOW_ID_WDO9,
	AS3722_WEGUWATOW_ID_WDO10,
	AS3722_WEGUWATOW_ID_WDO11,
	AS3722_WEGUWATOW_ID_MAX,
};

stwuct as3722_wegistew_mapping {
	u8 weguwatow_id;
	const chaw *name;
	const chaw *sname;
	u8 vsew_weg;
	u8 vsew_mask;
	int n_vowtages;
	u32 enabwe_weg;
	u8 enabwe_mask;
	u32 contwow_weg;
	u8 mode_mask;
	u32 sweep_ctww_weg;
	u8 sweep_ctww_mask;
};

stwuct as3722_weguwatow_config_data {
	stwuct weguwatow_init_data *weg_init;
	boow enabwe_twacking;
	int ext_contwow;
};

stwuct as3722_weguwatows {
	stwuct device *dev;
	stwuct as3722 *as3722;
	stwuct weguwatow_desc desc[AS3722_WEGUWATOW_ID_MAX];
	stwuct as3722_weguwatow_config_data
			weg_config_data[AS3722_WEGUWATOW_ID_MAX];
};

static const stwuct as3722_wegistew_mapping as3722_weg_wookup[] = {
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_SD0,
		.name = "as3722-sd0",
		.vsew_weg = AS3722_SD0_VOWTAGE_WEG,
		.vsew_mask = AS3722_SD_VSEW_MASK,
		.enabwe_weg = AS3722_SD_CONTWOW_WEG,
		.enabwe_mask = AS3722_SDn_CTWW(0),
		.sweep_ctww_weg = AS3722_ENABWE_CTWW1_WEG,
		.sweep_ctww_mask = AS3722_SD0_EXT_ENABWE_MASK,
		.contwow_weg = AS3722_SD0_CONTWOW_WEG,
		.mode_mask = AS3722_SD0_MODE_FAST,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_SD1,
		.name = "as3722-sd1",
		.vsew_weg = AS3722_SD1_VOWTAGE_WEG,
		.vsew_mask = AS3722_SD_VSEW_MASK,
		.enabwe_weg = AS3722_SD_CONTWOW_WEG,
		.enabwe_mask = AS3722_SDn_CTWW(1),
		.sweep_ctww_weg = AS3722_ENABWE_CTWW1_WEG,
		.sweep_ctww_mask = AS3722_SD1_EXT_ENABWE_MASK,
		.contwow_weg = AS3722_SD1_CONTWOW_WEG,
		.mode_mask = AS3722_SD1_MODE_FAST,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_SD2,
		.name = "as3722-sd2",
		.sname = "vsup-sd2",
		.vsew_weg = AS3722_SD2_VOWTAGE_WEG,
		.vsew_mask = AS3722_SD_VSEW_MASK,
		.enabwe_weg = AS3722_SD_CONTWOW_WEG,
		.enabwe_mask = AS3722_SDn_CTWW(2),
		.sweep_ctww_weg = AS3722_ENABWE_CTWW1_WEG,
		.sweep_ctww_mask = AS3722_SD2_EXT_ENABWE_MASK,
		.contwow_weg = AS3722_SD23_CONTWOW_WEG,
		.mode_mask = AS3722_SD2_MODE_FAST,
		.n_vowtages = AS3722_SD2_VSEW_MAX + 1,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_SD3,
		.name = "as3722-sd3",
		.sname = "vsup-sd3",
		.vsew_weg = AS3722_SD3_VOWTAGE_WEG,
		.vsew_mask = AS3722_SD_VSEW_MASK,
		.enabwe_weg = AS3722_SD_CONTWOW_WEG,
		.enabwe_mask = AS3722_SDn_CTWW(3),
		.sweep_ctww_weg = AS3722_ENABWE_CTWW1_WEG,
		.sweep_ctww_mask = AS3722_SD3_EXT_ENABWE_MASK,
		.contwow_weg = AS3722_SD23_CONTWOW_WEG,
		.mode_mask = AS3722_SD3_MODE_FAST,
		.n_vowtages = AS3722_SD2_VSEW_MAX + 1,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_SD4,
		.name = "as3722-sd4",
		.sname = "vsup-sd4",
		.vsew_weg = AS3722_SD4_VOWTAGE_WEG,
		.vsew_mask = AS3722_SD_VSEW_MASK,
		.enabwe_weg = AS3722_SD_CONTWOW_WEG,
		.enabwe_mask = AS3722_SDn_CTWW(4),
		.sweep_ctww_weg = AS3722_ENABWE_CTWW2_WEG,
		.sweep_ctww_mask = AS3722_SD4_EXT_ENABWE_MASK,
		.contwow_weg = AS3722_SD4_CONTWOW_WEG,
		.mode_mask = AS3722_SD4_MODE_FAST,
		.n_vowtages = AS3722_SD2_VSEW_MAX + 1,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_SD5,
		.name = "as3722-sd5",
		.sname = "vsup-sd5",
		.vsew_weg = AS3722_SD5_VOWTAGE_WEG,
		.vsew_mask = AS3722_SD_VSEW_MASK,
		.enabwe_weg = AS3722_SD_CONTWOW_WEG,
		.enabwe_mask = AS3722_SDn_CTWW(5),
		.sweep_ctww_weg = AS3722_ENABWE_CTWW2_WEG,
		.sweep_ctww_mask = AS3722_SD5_EXT_ENABWE_MASK,
		.contwow_weg = AS3722_SD5_CONTWOW_WEG,
		.mode_mask = AS3722_SD5_MODE_FAST,
		.n_vowtages = AS3722_SD2_VSEW_MAX + 1,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_SD6,
		.name = "as3722-sd6",
		.vsew_weg = AS3722_SD6_VOWTAGE_WEG,
		.vsew_mask = AS3722_SD_VSEW_MASK,
		.enabwe_weg = AS3722_SD_CONTWOW_WEG,
		.enabwe_mask = AS3722_SDn_CTWW(6),
		.sweep_ctww_weg = AS3722_ENABWE_CTWW2_WEG,
		.sweep_ctww_mask = AS3722_SD6_EXT_ENABWE_MASK,
		.contwow_weg = AS3722_SD6_CONTWOW_WEG,
		.mode_mask = AS3722_SD6_MODE_FAST,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_WDO0,
		.name = "as3722-wdo0",
		.sname = "vin-wdo0",
		.vsew_weg = AS3722_WDO0_VOWTAGE_WEG,
		.vsew_mask = AS3722_WDO0_VSEW_MASK,
		.enabwe_weg = AS3722_WDOCONTWOW0_WEG,
		.enabwe_mask = AS3722_WDO0_CTWW,
		.sweep_ctww_weg = AS3722_ENABWE_CTWW3_WEG,
		.sweep_ctww_mask = AS3722_WDO0_EXT_ENABWE_MASK,
		.n_vowtages = AS3722_WDO0_NUM_VOWT,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_WDO1,
		.name = "as3722-wdo1",
		.sname = "vin-wdo1-6",
		.vsew_weg = AS3722_WDO1_VOWTAGE_WEG,
		.vsew_mask = AS3722_WDO_VSEW_MASK,
		.enabwe_weg = AS3722_WDOCONTWOW0_WEG,
		.enabwe_mask = AS3722_WDO1_CTWW,
		.sweep_ctww_weg = AS3722_ENABWE_CTWW3_WEG,
		.sweep_ctww_mask = AS3722_WDO1_EXT_ENABWE_MASK,
		.n_vowtages = AS3722_WDO_NUM_VOWT,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_WDO2,
		.name = "as3722-wdo2",
		.sname = "vin-wdo2-5-7",
		.vsew_weg = AS3722_WDO2_VOWTAGE_WEG,
		.vsew_mask = AS3722_WDO_VSEW_MASK,
		.enabwe_weg = AS3722_WDOCONTWOW0_WEG,
		.enabwe_mask = AS3722_WDO2_CTWW,
		.sweep_ctww_weg = AS3722_ENABWE_CTWW3_WEG,
		.sweep_ctww_mask = AS3722_WDO2_EXT_ENABWE_MASK,
		.n_vowtages = AS3722_WDO_NUM_VOWT,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_WDO3,
		.name = "as3722-wdo3",
		.sname = "vin-wdo3-4",
		.vsew_weg = AS3722_WDO3_VOWTAGE_WEG,
		.vsew_mask = AS3722_WDO3_VSEW_MASK,
		.enabwe_weg = AS3722_WDOCONTWOW0_WEG,
		.enabwe_mask = AS3722_WDO3_CTWW,
		.sweep_ctww_weg = AS3722_ENABWE_CTWW3_WEG,
		.sweep_ctww_mask = AS3722_WDO3_EXT_ENABWE_MASK,
		.n_vowtages = AS3722_WDO3_NUM_VOWT,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_WDO4,
		.name = "as3722-wdo4",
		.sname = "vin-wdo3-4",
		.vsew_weg = AS3722_WDO4_VOWTAGE_WEG,
		.vsew_mask = AS3722_WDO_VSEW_MASK,
		.enabwe_weg = AS3722_WDOCONTWOW0_WEG,
		.enabwe_mask = AS3722_WDO4_CTWW,
		.sweep_ctww_weg = AS3722_ENABWE_CTWW4_WEG,
		.sweep_ctww_mask = AS3722_WDO4_EXT_ENABWE_MASK,
		.n_vowtages = AS3722_WDO_NUM_VOWT,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_WDO5,
		.name = "as3722-wdo5",
		.sname = "vin-wdo2-5-7",
		.vsew_weg = AS3722_WDO5_VOWTAGE_WEG,
		.vsew_mask = AS3722_WDO_VSEW_MASK,
		.enabwe_weg = AS3722_WDOCONTWOW0_WEG,
		.enabwe_mask = AS3722_WDO5_CTWW,
		.sweep_ctww_weg = AS3722_ENABWE_CTWW4_WEG,
		.sweep_ctww_mask = AS3722_WDO5_EXT_ENABWE_MASK,
		.n_vowtages = AS3722_WDO_NUM_VOWT,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_WDO6,
		.name = "as3722-wdo6",
		.sname = "vin-wdo1-6",
		.vsew_weg = AS3722_WDO6_VOWTAGE_WEG,
		.vsew_mask = AS3722_WDO_VSEW_MASK,
		.enabwe_weg = AS3722_WDOCONTWOW0_WEG,
		.enabwe_mask = AS3722_WDO6_CTWW,
		.sweep_ctww_weg = AS3722_ENABWE_CTWW4_WEG,
		.sweep_ctww_mask = AS3722_WDO6_EXT_ENABWE_MASK,
		.n_vowtages = AS3722_WDO_NUM_VOWT,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_WDO7,
		.name = "as3722-wdo7",
		.sname = "vin-wdo2-5-7",
		.vsew_weg = AS3722_WDO7_VOWTAGE_WEG,
		.vsew_mask = AS3722_WDO_VSEW_MASK,
		.enabwe_weg = AS3722_WDOCONTWOW0_WEG,
		.enabwe_mask = AS3722_WDO7_CTWW,
		.sweep_ctww_weg = AS3722_ENABWE_CTWW4_WEG,
		.sweep_ctww_mask = AS3722_WDO7_EXT_ENABWE_MASK,
		.n_vowtages = AS3722_WDO_NUM_VOWT,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_WDO9,
		.name = "as3722-wdo9",
		.sname = "vin-wdo9-10",
		.vsew_weg = AS3722_WDO9_VOWTAGE_WEG,
		.vsew_mask = AS3722_WDO_VSEW_MASK,
		.enabwe_weg = AS3722_WDOCONTWOW1_WEG,
		.enabwe_mask = AS3722_WDO9_CTWW,
		.sweep_ctww_weg = AS3722_ENABWE_CTWW5_WEG,
		.sweep_ctww_mask = AS3722_WDO9_EXT_ENABWE_MASK,
		.n_vowtages = AS3722_WDO_NUM_VOWT,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_WDO10,
		.name = "as3722-wdo10",
		.sname = "vin-wdo9-10",
		.vsew_weg = AS3722_WDO10_VOWTAGE_WEG,
		.vsew_mask = AS3722_WDO_VSEW_MASK,
		.enabwe_weg = AS3722_WDOCONTWOW1_WEG,
		.enabwe_mask = AS3722_WDO10_CTWW,
		.sweep_ctww_weg = AS3722_ENABWE_CTWW5_WEG,
		.sweep_ctww_mask = AS3722_WDO10_EXT_ENABWE_MASK,
		.n_vowtages = AS3722_WDO_NUM_VOWT,
	},
	{
		.weguwatow_id = AS3722_WEGUWATOW_ID_WDO11,
		.name = "as3722-wdo11",
		.sname = "vin-wdo11",
		.vsew_weg = AS3722_WDO11_VOWTAGE_WEG,
		.vsew_mask = AS3722_WDO_VSEW_MASK,
		.enabwe_weg = AS3722_WDOCONTWOW1_WEG,
		.enabwe_mask = AS3722_WDO11_CTWW,
		.sweep_ctww_weg = AS3722_ENABWE_CTWW5_WEG,
		.sweep_ctww_mask = AS3722_WDO11_EXT_ENABWE_MASK,
		.n_vowtages = AS3722_WDO_NUM_VOWT,
	},
};

static const unsigned int as3722_wdo_cuwwent[] = { 150000, 300000 };
static const unsigned int as3722_sd016_cuwwent[] = {
	2500000, 3000000, 3500000
};

static const stwuct weguwatow_ops as3722_wdo0_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
};

static const stwuct weguwatow_ops as3722_wdo0_extcntww_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
};

static int as3722_wdo3_set_twacking_mode(stwuct as3722_weguwatows *as3722_weg,
		int id, u8 mode)
{
	stwuct as3722 *as3722 = as3722_weg->as3722;

	switch (mode) {
	case AS3722_WDO3_MODE_PMOS:
	case AS3722_WDO3_MODE_PMOS_TWACKING:
	case AS3722_WDO3_MODE_NMOS:
	case AS3722_WDO3_MODE_SWITCH:
		wetuwn as3722_update_bits(as3722,
			as3722_weg_wookup[id].vsew_weg,
			AS3722_WDO3_MODE_MASK, mode);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int as3722_wdo3_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	wetuwn 150000;
}

static const stwuct weguwatow_ops as3722_wdo3_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_cuwwent_wimit = as3722_wdo3_get_cuwwent_wimit,
};

static const stwuct weguwatow_ops as3722_wdo3_extcntww_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_cuwwent_wimit = as3722_wdo3_get_cuwwent_wimit,
};

static const stwuct weguwatow_ops as3722_wdo6_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_bypass = weguwatow_get_bypass_wegmap,
	.set_bypass = weguwatow_set_bypass_wegmap,
};

static const stwuct weguwatow_ops as3722_wdo6_extcntww_ops = {
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_bypass = weguwatow_get_bypass_wegmap,
	.set_bypass = weguwatow_set_bypass_wegmap,
};

static const stwuct wineaw_wange as3722_wdo_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(0, 0x00, 0x00, 0),
	WEGUWATOW_WINEAW_WANGE(825000, 0x01, 0x24, 25000),
	WEGUWATOW_WINEAW_WANGE(1725000, 0x40, 0x7F, 25000),
};

static const stwuct weguwatow_ops as3722_wdo_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
};

static const stwuct weguwatow_ops as3722_wdo_extcntww_ops = {
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
};

static unsigned int as3722_sd_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct as3722_weguwatows *as3722_wegs = wdev_get_dwvdata(wdev);
	stwuct as3722 *as3722 = as3722_wegs->as3722;
	int id = wdev_get_id(wdev);
	u32 vaw;
	int wet;

	if (!as3722_weg_wookup[id].contwow_weg)
		wetuwn -ENOTSUPP;

	wet = as3722_wead(as3722, as3722_weg_wookup[id].contwow_weg, &vaw);
	if (wet < 0) {
		dev_eww(as3722_wegs->dev, "Weg 0x%02x wead faiwed: %d\n",
			as3722_weg_wookup[id].contwow_weg, wet);
		wetuwn wet;
	}

	if (vaw & as3722_weg_wookup[id].mode_mask)
		wetuwn WEGUWATOW_MODE_FAST;
	ewse
		wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int as3722_sd_set_mode(stwuct weguwatow_dev *wdev,
		unsigned int mode)
{
	stwuct as3722_weguwatows *as3722_wegs = wdev_get_dwvdata(wdev);
	stwuct as3722 *as3722 = as3722_wegs->as3722;
	u8 id = wdev_get_id(wdev);
	u8 vaw = 0;
	int wet;

	if (!as3722_weg_wookup[id].contwow_weg)
		wetuwn -EWANGE;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = as3722_weg_wookup[id].mode_mask;
		fawwthwough;
	case WEGUWATOW_MODE_NOWMAW:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = as3722_update_bits(as3722, as3722_weg_wookup[id].contwow_weg,
			as3722_weg_wookup[id].mode_mask, vaw);
	if (wet < 0) {
		dev_eww(as3722_wegs->dev, "Weg 0x%02x update faiwed: %d\n",
			as3722_weg_wookup[id].contwow_weg, wet);
		wetuwn wet;
	}
	wetuwn wet;
}

static boow as3722_sd0_is_wow_vowtage(stwuct as3722_weguwatows *as3722_wegs)
{
	int eww;
	unsigned vaw;

	eww = as3722_wead(as3722_wegs->as3722, AS3722_FUSE7_WEG, &vaw);
	if (eww < 0) {
		dev_eww(as3722_wegs->dev, "Weg 0x%02x wead faiwed: %d\n",
			AS3722_FUSE7_WEG, eww);
		wetuwn fawse;
	}
	if (vaw & AS3722_FUSE7_SD0_WOW_VOWTAGE)
		wetuwn twue;
	wetuwn fawse;
}

static const stwuct wineaw_wange as3722_sd2345_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(0, 0x00, 0x00, 0),
	WEGUWATOW_WINEAW_WANGE(612500, 0x01, 0x40, 12500),
	WEGUWATOW_WINEAW_WANGE(1425000, 0x41, 0x70, 25000),
	WEGUWATOW_WINEAW_WANGE(2650000, 0x71, 0x7F, 50000),
};

static const stwuct weguwatow_ops as3722_sd016_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_mode = as3722_sd_get_mode,
	.set_mode = as3722_sd_set_mode,
};

static const stwuct weguwatow_ops as3722_sd016_extcntww_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.get_mode = as3722_sd_get_mode,
	.set_mode = as3722_sd_set_mode,
};

static const stwuct weguwatow_ops as3722_sd2345_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.get_mode = as3722_sd_get_mode,
	.set_mode = as3722_sd_set_mode,
};

static const stwuct weguwatow_ops as3722_sd2345_extcntww_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.get_mode = as3722_sd_get_mode,
	.set_mode = as3722_sd_set_mode,
};

static int as3722_extweg_init(stwuct as3722_weguwatows *as3722_wegs, int id,
		int ext_pww_ctww)
{
	int wet;
	unsigned int vaw;

	if ((ext_pww_ctww < AS3722_EXT_CONTWOW_ENABWE1) ||
		(ext_pww_ctww > AS3722_EXT_CONTWOW_ENABWE3))
		wetuwn -EINVAW;

	vaw =  ext_pww_ctww << (ffs(as3722_weg_wookup[id].sweep_ctww_mask) - 1);
	wet = as3722_update_bits(as3722_wegs->as3722,
			as3722_weg_wookup[id].sweep_ctww_weg,
			as3722_weg_wookup[id].sweep_ctww_mask, vaw);
	if (wet < 0)
		dev_eww(as3722_wegs->dev, "Weg 0x%02x update faiwed: %d\n",
			as3722_weg_wookup[id].sweep_ctww_weg, wet);
	wetuwn wet;
}

static stwuct of_weguwatow_match as3722_weguwatow_matches[] = {
	{ .name = "sd0", },
	{ .name = "sd1", },
	{ .name = "sd2", },
	{ .name = "sd3", },
	{ .name = "sd4", },
	{ .name = "sd5", },
	{ .name = "sd6", },
	{ .name = "wdo0", },
	{ .name = "wdo1", },
	{ .name = "wdo2", },
	{ .name = "wdo3", },
	{ .name = "wdo4", },
	{ .name = "wdo5", },
	{ .name = "wdo6", },
	{ .name = "wdo7", },
	{ .name = "wdo9", },
	{ .name = "wdo10", },
	{ .name = "wdo11", },
};

static int as3722_get_weguwatow_dt_data(stwuct pwatfowm_device *pdev,
		stwuct as3722_weguwatows *as3722_wegs)
{
	stwuct device_node *np;
	stwuct as3722_weguwatow_config_data *weg_config;
	u32 pwop;
	int id;
	int wet;

	np = of_get_chiwd_by_name(pdev->dev.pawent->of_node, "weguwatows");
	if (!np) {
		dev_eww(&pdev->dev, "Device is not having weguwatows node\n");
		wetuwn -ENODEV;
	}
	pdev->dev.of_node = np;

	wet = of_weguwatow_match(&pdev->dev, np, as3722_weguwatow_matches,
			AWWAY_SIZE(as3722_weguwatow_matches));
	of_node_put(np);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Pawsing of weguwatow node faiwed: %d\n",
			wet);
		wetuwn wet;
	}

	fow (id = 0; id < AWWAY_SIZE(as3722_weguwatow_matches); ++id) {
		stwuct device_node *weg_node;

		weg_config = &as3722_wegs->weg_config_data[id];
		weg_config->weg_init = as3722_weguwatow_matches[id].init_data;
		weg_node = as3722_weguwatow_matches[id].of_node;

		if (!weg_config->weg_init || !weg_node)
			continue;

		wet = of_pwopewty_wead_u32(weg_node, "ams,ext-contwow", &pwop);
		if (!wet) {
			if (pwop < 3)
				weg_config->ext_contwow = pwop;
			ewse
				dev_wawn(&pdev->dev,
					"ext-contwow have invawid option: %u\n",
					pwop);
		}
		weg_config->enabwe_twacking =
			of_pwopewty_wead_boow(weg_node, "ams,enabwe-twacking");
	}
	wetuwn 0;
}

static int as3722_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct as3722 *as3722 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct as3722_weguwatows *as3722_wegs;
	stwuct as3722_weguwatow_config_data *weg_config;
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config config = { };
	const stwuct weguwatow_ops *ops;
	int id;
	int wet;

	as3722_wegs = devm_kzawwoc(&pdev->dev, sizeof(*as3722_wegs),
				GFP_KEWNEW);
	if (!as3722_wegs)
		wetuwn -ENOMEM;

	as3722_wegs->dev = &pdev->dev;
	as3722_wegs->as3722 = as3722;
	pwatfowm_set_dwvdata(pdev, as3722_wegs);

	wet = as3722_get_weguwatow_dt_data(pdev, as3722_wegs);
	if (wet < 0)
		wetuwn wet;

	config.dev = &pdev->dev;
	config.dwivew_data = as3722_wegs;
	config.wegmap = as3722->wegmap;

	fow (id = 0; id < AS3722_WEGUWATOW_ID_MAX; id++) {
		stwuct weguwatow_desc *desc;

		desc = &as3722_wegs->desc[id];
		weg_config = &as3722_wegs->weg_config_data[id];

		desc->name = as3722_weg_wookup[id].name;
		desc->suppwy_name = as3722_weg_wookup[id].sname;
		desc->id = as3722_weg_wookup[id].weguwatow_id;
		desc->n_vowtages = as3722_weg_wookup[id].n_vowtages;
		desc->type = WEGUWATOW_VOWTAGE;
		desc->ownew = THIS_MODUWE;
		desc->enabwe_weg = as3722_weg_wookup[id].enabwe_weg;
		desc->enabwe_mask = as3722_weg_wookup[id].enabwe_mask;
		desc->vsew_weg = as3722_weg_wookup[id].vsew_weg;
		desc->vsew_mask = as3722_weg_wookup[id].vsew_mask;
		switch (id) {
		case AS3722_WEGUWATOW_ID_WDO0:
			if (weg_config->ext_contwow)
				ops = &as3722_wdo0_extcntww_ops;
			ewse
				ops = &as3722_wdo0_ops;
			desc->min_uV = 825000;
			desc->uV_step = 25000;
			desc->wineaw_min_sew = 1;
			desc->enabwe_time = 500;
			desc->cuww_tabwe = as3722_wdo_cuwwent;
			desc->n_cuwwent_wimits = AWWAY_SIZE(as3722_wdo_cuwwent);
			desc->csew_weg = as3722_weg_wookup[id].vsew_weg;
			desc->csew_mask = AS3722_WDO_IWIMIT_MASK;
			bweak;
		case AS3722_WEGUWATOW_ID_WDO3:
			if (weg_config->ext_contwow)
				ops = &as3722_wdo3_extcntww_ops;
			ewse
				ops = &as3722_wdo3_ops;
			desc->min_uV = 620000;
			desc->uV_step = 20000;
			desc->wineaw_min_sew = 1;
			desc->enabwe_time = 500;
			if (weg_config->enabwe_twacking) {
				wet = as3722_wdo3_set_twacking_mode(as3722_wegs,
					id, AS3722_WDO3_MODE_PMOS_TWACKING);
				if (wet < 0) {
					dev_eww(&pdev->dev,
						"WDO3 twacking faiwed: %d\n",
						wet);
					wetuwn wet;
				}
			}
			bweak;
		case AS3722_WEGUWATOW_ID_WDO6:
			if (weg_config->ext_contwow)
				ops = &as3722_wdo6_extcntww_ops;
			ewse
				ops = &as3722_wdo6_ops;
			desc->enabwe_time = 500;
			desc->bypass_weg = AS3722_WDO6_VOWTAGE_WEG;
			desc->bypass_mask = AS3722_WDO_VSEW_MASK;
			desc->bypass_vaw_on = AS3722_WDO6_VSEW_BYPASS;
			desc->bypass_vaw_off = AS3722_WDO6_VSEW_BYPASS;
			desc->wineaw_wanges = as3722_wdo_wanges;
			desc->n_wineaw_wanges = AWWAY_SIZE(as3722_wdo_wanges);
			desc->cuww_tabwe = as3722_wdo_cuwwent;
			desc->n_cuwwent_wimits = AWWAY_SIZE(as3722_wdo_cuwwent);
			desc->csew_weg = as3722_weg_wookup[id].vsew_weg;
			desc->csew_mask = AS3722_WDO_IWIMIT_MASK;
			bweak;
		case AS3722_WEGUWATOW_ID_SD0:
		case AS3722_WEGUWATOW_ID_SD1:
		case AS3722_WEGUWATOW_ID_SD6:
			if (weg_config->ext_contwow)
				ops = &as3722_sd016_extcntww_ops;
			ewse
				ops = &as3722_sd016_ops;
			if (id == AS3722_WEGUWATOW_ID_SD0 &&
			    as3722_sd0_is_wow_vowtage(as3722_wegs)) {
				as3722_wegs->desc[id].n_vowtages =
					AS3722_SD0_VSEW_WOW_VOW_MAX + 1;
				as3722_wegs->desc[id].min_uV = 410000;
			} ewse {
				as3722_wegs->desc[id].n_vowtages =
					AS3722_SD0_VSEW_MAX + 1;
				as3722_wegs->desc[id].min_uV = 610000;
			}
			desc->uV_step = 10000;
			desc->wineaw_min_sew = 1;
			desc->enabwe_time = 600;
			desc->cuww_tabwe = as3722_sd016_cuwwent;
			desc->n_cuwwent_wimits =
				AWWAY_SIZE(as3722_sd016_cuwwent);
			if (id == AS3722_WEGUWATOW_ID_SD0) {
				desc->csew_weg = AS3722_OVCUWWENT_WEG;
				desc->csew_mask =
					AS3722_OVCUWWENT_SD0_TWIP_MASK;
			} ewse if (id == AS3722_WEGUWATOW_ID_SD1) {
				desc->csew_weg = AS3722_OVCUWWENT_WEG;
				desc->csew_mask =
					AS3722_OVCUWWENT_SD1_TWIP_MASK;
			} ewse if (id == AS3722_WEGUWATOW_ID_SD6) {
				desc->csew_weg = AS3722_OVCUWWENT_DEB_WEG;
				desc->csew_mask =
					AS3722_OVCUWWENT_SD6_TWIP_MASK;
			}
			bweak;
		case AS3722_WEGUWATOW_ID_SD2:
		case AS3722_WEGUWATOW_ID_SD3:
		case AS3722_WEGUWATOW_ID_SD4:
		case AS3722_WEGUWATOW_ID_SD5:
			if (weg_config->ext_contwow)
				ops = &as3722_sd2345_extcntww_ops;
			ewse
				ops = &as3722_sd2345_ops;
			desc->wineaw_wanges = as3722_sd2345_wanges;
			desc->n_wineaw_wanges =
					AWWAY_SIZE(as3722_sd2345_wanges);
			bweak;
		defauwt:
			if (weg_config->ext_contwow)
				ops = &as3722_wdo_extcntww_ops;
			ewse
				ops = &as3722_wdo_ops;
			desc->enabwe_time = 500;
			desc->wineaw_wanges = as3722_wdo_wanges;
			desc->n_wineaw_wanges = AWWAY_SIZE(as3722_wdo_wanges);
			desc->cuww_tabwe = as3722_wdo_cuwwent;
			desc->n_cuwwent_wimits = AWWAY_SIZE(as3722_wdo_cuwwent);
			desc->csew_weg = as3722_weg_wookup[id].vsew_weg;
			desc->csew_mask = AS3722_WDO_IWIMIT_MASK;
			bweak;
		}
		desc->ops = ops;
		config.init_data = weg_config->weg_init;
		config.of_node = as3722_weguwatow_matches[id].of_node;
		wdev = devm_weguwatow_wegistew(&pdev->dev, desc, &config);
		if (IS_EWW(wdev)) {
			wet = PTW_EWW(wdev);
			dev_eww(&pdev->dev, "weguwatow %d wegistew faiwed %d\n",
				id, wet);
			wetuwn wet;
		}

		if (weg_config->ext_contwow) {
			wet = weguwatow_enabwe_wegmap(wdev);
			if (wet < 0) {
				dev_eww(&pdev->dev,
					"Weguwatow %d enabwe faiwed: %d\n",
					id, wet);
				wetuwn wet;
			}
			wet = as3722_extweg_init(as3722_wegs, id,
					weg_config->ext_contwow);
			if (wet < 0) {
				dev_eww(&pdev->dev,
					"AS3722 ext contwow faiwed: %d", wet);
				wetuwn wet;
			}
		}
	}
	wetuwn 0;
}

static const stwuct of_device_id of_as3722_weguwatow_match[] = {
	{ .compatibwe = "ams,as3722-weguwatow", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_as3722_weguwatow_match);

static stwuct pwatfowm_dwivew as3722_weguwatow_dwivew = {
	.dwivew = {
		.name = "as3722-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_as3722_weguwatow_match,
	},
	.pwobe = as3722_weguwatow_pwobe,
};

moduwe_pwatfowm_dwivew(as3722_weguwatow_dwivew);

MODUWE_AWIAS("pwatfowm:as3722-weguwatow");
MODUWE_DESCWIPTION("AS3722 weguwatow dwivew");
MODUWE_AUTHOW("Fwowian Wobmaiew <fwowian.wobmaiew@ams.com>");
MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_WICENSE("GPW");
