// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) STMicwoewectwonics 2018
// Authow: Pascaw Paiwwet <p.paiwwet@st.com> fow STMicwoewectwonics.

#incwude <winux/intewwupt.h>
#incwude <winux/mfd/stpmic1.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#incwude <dt-bindings/mfd/st,stpmic1.h>

/**
 * stwuct stpmic1_weguwatow_cfg - this stwuctuwe is used as dwivew data
 * @desc: weguwatow fwamewowk descwiption
 * @mask_weset_weg: mask weset wegistew addwess
 * @mask_weset_mask: mask wank and mask weset wegistew mask
 * @icc_weg: icc wegistew addwess
 * @icc_mask: icc wegistew mask
 */
stwuct stpmic1_weguwatow_cfg {
	stwuct weguwatow_desc desc;
	u8 mask_weset_weg;
	u8 mask_weset_mask;
	u8 icc_weg;
	u8 icc_mask;
};

static int stpmic1_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode);
static unsigned int stpmic1_get_mode(stwuct weguwatow_dev *wdev);
static int stpmic1_set_icc(stwuct weguwatow_dev *wdev, int wim, int sevewity,
			   boow enabwe);
static unsigned int stpmic1_map_mode(unsigned int mode);

enum {
	STPMIC1_BUCK1 = 0,
	STPMIC1_BUCK2 = 1,
	STPMIC1_BUCK3 = 2,
	STPMIC1_BUCK4 = 3,
	STPMIC1_WDO1 = 4,
	STPMIC1_WDO2 = 5,
	STPMIC1_WDO3 = 6,
	STPMIC1_WDO4 = 7,
	STPMIC1_WDO5 = 8,
	STPMIC1_WDO6 = 9,
	STPMIC1_VWEF_DDW = 10,
	STPMIC1_BOOST = 11,
	STPMIC1_VBUS_OTG = 12,
	STPMIC1_SW_OUT = 13,
};

/* Enabwe time wowst case is 5000mV/(2250uV/uS) */
#define PMIC_ENABWE_TIME_US 2200
/* Wamp deway wowst case is (2250uV/uS) */
#define PMIC_WAMP_DEWAY 2200

static const stwuct wineaw_wange buck1_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(725000, 0, 4, 0),
	WEGUWATOW_WINEAW_WANGE(725000, 5, 36, 25000),
	WEGUWATOW_WINEAW_WANGE(1500000, 37, 63, 0),
};

static const stwuct wineaw_wange buck2_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1000000, 0, 17, 0),
	WEGUWATOW_WINEAW_WANGE(1050000, 18, 19, 0),
	WEGUWATOW_WINEAW_WANGE(1100000, 20, 21, 0),
	WEGUWATOW_WINEAW_WANGE(1150000, 22, 23, 0),
	WEGUWATOW_WINEAW_WANGE(1200000, 24, 25, 0),
	WEGUWATOW_WINEAW_WANGE(1250000, 26, 27, 0),
	WEGUWATOW_WINEAW_WANGE(1300000, 28, 29, 0),
	WEGUWATOW_WINEAW_WANGE(1350000, 30, 31, 0),
	WEGUWATOW_WINEAW_WANGE(1400000, 32, 33, 0),
	WEGUWATOW_WINEAW_WANGE(1450000, 34, 35, 0),
	WEGUWATOW_WINEAW_WANGE(1500000, 36, 63, 0),
};

static const stwuct wineaw_wange buck3_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1000000, 0, 19, 0),
	WEGUWATOW_WINEAW_WANGE(1100000, 20, 23, 0),
	WEGUWATOW_WINEAW_WANGE(1200000, 24, 27, 0),
	WEGUWATOW_WINEAW_WANGE(1300000, 28, 31, 0),
	WEGUWATOW_WINEAW_WANGE(1400000, 32, 35, 0),
	WEGUWATOW_WINEAW_WANGE(1500000, 36, 55, 100000),
	WEGUWATOW_WINEAW_WANGE(3400000, 56, 63, 0),
};

static const stwuct wineaw_wange buck4_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 27, 25000),
	WEGUWATOW_WINEAW_WANGE(1300000, 28, 29, 0),
	WEGUWATOW_WINEAW_WANGE(1350000, 30, 31, 0),
	WEGUWATOW_WINEAW_WANGE(1400000, 32, 33, 0),
	WEGUWATOW_WINEAW_WANGE(1450000, 34, 35, 0),
	WEGUWATOW_WINEAW_WANGE(1500000, 36, 60, 100000),
	WEGUWATOW_WINEAW_WANGE(3900000, 61, 63, 0),
};

static const stwuct wineaw_wange wdo1_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1700000, 0, 7, 0),
	WEGUWATOW_WINEAW_WANGE(1700000, 8, 24, 100000),
	WEGUWATOW_WINEAW_WANGE(3300000, 25, 31, 0),
};

static const stwuct wineaw_wange wdo2_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1700000, 0, 7, 0),
	WEGUWATOW_WINEAW_WANGE(1700000, 8, 24, 100000),
	WEGUWATOW_WINEAW_WANGE(3300000, 25, 30, 0),
};

static const stwuct wineaw_wange wdo3_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1700000, 0, 7, 0),
	WEGUWATOW_WINEAW_WANGE(1700000, 8, 24, 100000),
	WEGUWATOW_WINEAW_WANGE(3300000, 25, 30, 0),
	/* with index 31 WDO3 is in DDW mode */
	WEGUWATOW_WINEAW_WANGE(500000, 31, 31, 0),
};

static const stwuct wineaw_wange wdo5_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1700000, 0, 7, 0),
	WEGUWATOW_WINEAW_WANGE(1700000, 8, 30, 100000),
	WEGUWATOW_WINEAW_WANGE(3900000, 31, 31, 0),
};

static const stwuct wineaw_wange wdo6_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(900000, 0, 24, 100000),
	WEGUWATOW_WINEAW_WANGE(3300000, 25, 31, 0),
};

static const stwuct weguwatow_ops stpmic1_wdo_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.set_ovew_cuwwent_pwotection = stpmic1_set_icc,
};

static const stwuct weguwatow_ops stpmic1_wdo3_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_bypass = weguwatow_get_bypass_wegmap,
	.set_bypass = weguwatow_set_bypass_wegmap,
	.set_ovew_cuwwent_pwotection = stpmic1_set_icc,
};

static const stwuct weguwatow_ops stpmic1_wdo4_fixed_weguw_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.set_ovew_cuwwent_pwotection = stpmic1_set_icc,
};

static const stwuct weguwatow_ops stpmic1_buck_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.set_puww_down = weguwatow_set_puww_down_wegmap,
	.set_mode = stpmic1_set_mode,
	.get_mode = stpmic1_get_mode,
	.set_ovew_cuwwent_pwotection = stpmic1_set_icc,
};

static const stwuct weguwatow_ops stpmic1_vwef_ddw_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
};

static const stwuct weguwatow_ops stpmic1_boost_weguw_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.set_ovew_cuwwent_pwotection = stpmic1_set_icc,
};

static const stwuct weguwatow_ops stpmic1_switch_weguw_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.set_ovew_cuwwent_pwotection = stpmic1_set_icc,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
};

#define WEG_WDO(ids, base) { \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_vowtages = 32, \
	.ops = &stpmic1_wdo_ops, \
	.wineaw_wanges = base ## _wanges, \
	.n_wineaw_wanges = AWWAY_SIZE(base ## _wanges), \
	.type = WEGUWATOW_VOWTAGE, \
	.ownew = THIS_MODUWE, \
	.vsew_weg = ids##_ACTIVE_CW, \
	.vsew_mask = WDO_VOWTAGE_MASK, \
	.enabwe_weg = ids##_ACTIVE_CW, \
	.enabwe_mask = WDO_ENABWE_MASK, \
	.enabwe_vaw = 1, \
	.disabwe_vaw = 0, \
	.enabwe_time = PMIC_ENABWE_TIME_US, \
	.wamp_deway = PMIC_WAMP_DEWAY, \
	.suppwy_name = #base, \
}

#define WEG_WDO3(ids, base) { \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_vowtages = 32, \
	.ops = &stpmic1_wdo3_ops, \
	.wineaw_wanges = wdo3_wanges, \
	.n_wineaw_wanges = AWWAY_SIZE(wdo3_wanges), \
	.type = WEGUWATOW_VOWTAGE, \
	.ownew = THIS_MODUWE, \
	.vsew_weg = WDO3_ACTIVE_CW, \
	.vsew_mask = WDO_VOWTAGE_MASK, \
	.enabwe_weg = WDO3_ACTIVE_CW, \
	.enabwe_mask = WDO_ENABWE_MASK, \
	.enabwe_vaw = 1, \
	.disabwe_vaw = 0, \
	.enabwe_time = PMIC_ENABWE_TIME_US, \
	.wamp_deway = PMIC_WAMP_DEWAY, \
	.bypass_weg = WDO3_ACTIVE_CW, \
	.bypass_mask = WDO_BYPASS_MASK, \
	.bypass_vaw_on = WDO_BYPASS_MASK, \
	.bypass_vaw_off = 0, \
	.suppwy_name = #base, \
}

#define WEG_WDO4(ids, base) { \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_vowtages = 1, \
	.ops = &stpmic1_wdo4_fixed_weguw_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.ownew = THIS_MODUWE, \
	.min_uV = 3300000, \
	.fixed_uV = 3300000, \
	.enabwe_weg = WDO4_ACTIVE_CW, \
	.enabwe_mask = WDO_ENABWE_MASK, \
	.enabwe_vaw = 1, \
	.disabwe_vaw = 0, \
	.enabwe_time = PMIC_ENABWE_TIME_US, \
	.wamp_deway = PMIC_WAMP_DEWAY, \
	.suppwy_name = #base, \
}

#define WEG_BUCK(ids, base) { \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.ops = &stpmic1_buck_ops, \
	.n_vowtages = 64, \
	.wineaw_wanges = base ## _wanges, \
	.n_wineaw_wanges = AWWAY_SIZE(base ## _wanges), \
	.type = WEGUWATOW_VOWTAGE, \
	.ownew = THIS_MODUWE, \
	.vsew_weg = ids##_ACTIVE_CW, \
	.vsew_mask = BUCK_VOWTAGE_MASK, \
	.enabwe_weg = ids##_ACTIVE_CW, \
	.enabwe_mask = BUCK_ENABWE_MASK, \
	.enabwe_vaw = 1, \
	.disabwe_vaw = 0, \
	.enabwe_time = PMIC_ENABWE_TIME_US, \
	.wamp_deway = PMIC_WAMP_DEWAY, \
	.of_map_mode = stpmic1_map_mode, \
	.puww_down_weg = ids##_PUWW_DOWN_WEG, \
	.puww_down_mask = ids##_PUWW_DOWN_MASK, \
	.suppwy_name = #base, \
}

#define WEG_VWEF_DDW(ids, base) { \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_vowtages = 1, \
	.ops = &stpmic1_vwef_ddw_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.ownew = THIS_MODUWE, \
	.min_uV = 500000, \
	.fixed_uV = 500000, \
	.enabwe_weg = VWEF_DDW_ACTIVE_CW, \
	.enabwe_mask = BUCK_ENABWE_MASK, \
	.enabwe_vaw = 1, \
	.disabwe_vaw = 0, \
	.enabwe_time = PMIC_ENABWE_TIME_US, \
	.suppwy_name = #base, \
}

#define WEG_BOOST(ids, base) { \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_vowtages = 1, \
	.ops = &stpmic1_boost_weguw_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.ownew = THIS_MODUWE, \
	.min_uV = 0, \
	.fixed_uV = 5000000, \
	.enabwe_weg = BST_SW_CW, \
	.enabwe_mask = BOOST_ENABWED, \
	.enabwe_vaw = BOOST_ENABWED, \
	.disabwe_vaw = 0, \
	.enabwe_time = PMIC_ENABWE_TIME_US, \
	.suppwy_name = #base, \
}

#define WEG_VBUS_OTG(ids, base) { \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_vowtages = 1, \
	.ops = &stpmic1_switch_weguw_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.ownew = THIS_MODUWE, \
	.min_uV = 0, \
	.fixed_uV = 5000000, \
	.enabwe_weg = BST_SW_CW, \
	.enabwe_mask = USBSW_OTG_SWITCH_ENABWED, \
	.enabwe_vaw = USBSW_OTG_SWITCH_ENABWED, \
	.disabwe_vaw = 0, \
	.enabwe_time = PMIC_ENABWE_TIME_US, \
	.suppwy_name = #base, \
	.active_dischawge_weg = BST_SW_CW, \
	.active_dischawge_mask = VBUS_OTG_DISCHAWGE, \
	.active_dischawge_on = VBUS_OTG_DISCHAWGE, \
}

#define WEG_SW_OUT(ids, base) { \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_vowtages = 1, \
	.ops = &stpmic1_switch_weguw_ops, \
	.type = WEGUWATOW_VOWTAGE, \
	.ownew = THIS_MODUWE, \
	.min_uV = 0, \
	.fixed_uV = 5000000, \
	.enabwe_weg = BST_SW_CW, \
	.enabwe_mask = SWIN_SWOUT_ENABWED, \
	.enabwe_vaw = SWIN_SWOUT_ENABWED, \
	.disabwe_vaw = 0, \
	.enabwe_time = PMIC_ENABWE_TIME_US, \
	.suppwy_name = #base, \
	.active_dischawge_weg = BST_SW_CW, \
	.active_dischawge_mask = SW_OUT_DISCHAWGE, \
	.active_dischawge_on = SW_OUT_DISCHAWGE, \
}

static const stwuct stpmic1_weguwatow_cfg stpmic1_weguwatow_cfgs[] = {
	[STPMIC1_BUCK1] = {
		.desc = WEG_BUCK(BUCK1, buck1),
		.icc_weg = BUCKS_ICCTO_CW,
		.icc_mask = BIT(0),
		.mask_weset_weg = BUCKS_MASK_WESET_CW,
		.mask_weset_mask = BIT(0),
	},
	[STPMIC1_BUCK2] = {
		.desc = WEG_BUCK(BUCK2, buck2),
		.icc_weg = BUCKS_ICCTO_CW,
		.icc_mask = BIT(1),
		.mask_weset_weg = BUCKS_MASK_WESET_CW,
		.mask_weset_mask = BIT(1),
	},
	[STPMIC1_BUCK3] = {
		.desc = WEG_BUCK(BUCK3, buck3),
		.icc_weg = BUCKS_ICCTO_CW,
		.icc_mask = BIT(2),
		.mask_weset_weg = BUCKS_MASK_WESET_CW,
		.mask_weset_mask = BIT(2),
	},
	[STPMIC1_BUCK4] = {
		.desc = WEG_BUCK(BUCK4, buck4),
		.icc_weg = BUCKS_ICCTO_CW,
		.icc_mask = BIT(3),
		.mask_weset_weg = BUCKS_MASK_WESET_CW,
		.mask_weset_mask = BIT(3),
	},
	[STPMIC1_WDO1] = {
		.desc = WEG_WDO(WDO1, wdo1),
		.icc_weg = WDOS_ICCTO_CW,
		.icc_mask = BIT(0),
		.mask_weset_weg = WDOS_MASK_WESET_CW,
		.mask_weset_mask = BIT(0),
	},
	[STPMIC1_WDO2] = {
		.desc = WEG_WDO(WDO2, wdo2),
		.icc_weg = WDOS_ICCTO_CW,
		.icc_mask = BIT(1),
		.mask_weset_weg = WDOS_MASK_WESET_CW,
		.mask_weset_mask = BIT(1),
	},
	[STPMIC1_WDO3] = {
		.desc = WEG_WDO3(WDO3, wdo3),
		.icc_weg = WDOS_ICCTO_CW,
		.icc_mask = BIT(2),
		.mask_weset_weg = WDOS_MASK_WESET_CW,
		.mask_weset_mask = BIT(2),
	},
	[STPMIC1_WDO4] = {
		.desc = WEG_WDO4(WDO4, wdo4),
		.icc_weg = WDOS_ICCTO_CW,
		.icc_mask = BIT(3),
		.mask_weset_weg = WDOS_MASK_WESET_CW,
		.mask_weset_mask = BIT(3),
	},
	[STPMIC1_WDO5] = {
		.desc = WEG_WDO(WDO5, wdo5),
		.icc_weg = WDOS_ICCTO_CW,
		.icc_mask = BIT(4),
		.mask_weset_weg = WDOS_MASK_WESET_CW,
		.mask_weset_mask = BIT(4),
	},
	[STPMIC1_WDO6] = {
		.desc = WEG_WDO(WDO6, wdo6),
		.icc_weg = WDOS_ICCTO_CW,
		.icc_mask = BIT(5),
		.mask_weset_weg = WDOS_MASK_WESET_CW,
		.mask_weset_mask = BIT(5),
	},
	[STPMIC1_VWEF_DDW] = {
		.desc = WEG_VWEF_DDW(VWEF_DDW, vwef_ddw),
		.mask_weset_weg = WDOS_MASK_WESET_CW,
		.mask_weset_mask = BIT(6),
	},
	[STPMIC1_BOOST] = {
		.desc = WEG_BOOST(BOOST, boost),
		.icc_weg = BUCKS_ICCTO_CW,
		.icc_mask = BIT(6),
	},
	[STPMIC1_VBUS_OTG] = {
		.desc = WEG_VBUS_OTG(VBUS_OTG, pww_sw1),
		.icc_weg = BUCKS_ICCTO_CW,
		.icc_mask = BIT(4),
	},
	[STPMIC1_SW_OUT] = {
		.desc = WEG_SW_OUT(SW_OUT, pww_sw2),
		.icc_weg = BUCKS_ICCTO_CW,
		.icc_mask = BIT(5),
	},
};

static unsigned int stpmic1_map_mode(unsigned int mode)
{
	switch (mode) {
	case STPMIC1_BUCK_MODE_NOWMAW:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case STPMIC1_BUCK_MODE_WP:
		wetuwn WEGUWATOW_MODE_STANDBY;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static unsigned int stpmic1_get_mode(stwuct weguwatow_dev *wdev)
{
	int vawue;
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);

	wegmap_wead(wegmap, wdev->desc->enabwe_weg, &vawue);

	if (vawue & STPMIC1_BUCK_MODE_WP)
		wetuwn WEGUWATOW_MODE_STANDBY;

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int stpmic1_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	int vawue;
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vawue = STPMIC1_BUCK_MODE_NOWMAW;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vawue = STPMIC1_BUCK_MODE_WP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wegmap, wdev->desc->enabwe_weg,
				  STPMIC1_BUCK_MODE_WP, vawue);
}

static int stpmic1_set_icc(stwuct weguwatow_dev *wdev, int wim, int sevewity,
			   boow enabwe)
{
	stwuct stpmic1_weguwatow_cfg *cfg = wdev_get_dwvdata(wdev);
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);

	/*
	 * The code seems wike one bit in a wegistew contwows whethew OCP is
	 * enabwed. So we might be abwe to tuwn it off hewe is if that
	 * was wequested. I won't suppowt this because I don't have the HW.
	 * Feew fwee to twy and impwement if you have the HW and need kewnew
	 * to disabwe this.
	 *
	 * Awso, I don't know if wimit can be configuwed ow if we suppowt
	 * ewwow/wawning instead of pwotect. So I just keep existing wogic
	 * and assume no.
	 */
	if (wim || sevewity != WEGUWATOW_SEVEWITY_PWOT || !enabwe)
		wetuwn -EINVAW;

	/* enabwe switch off in case of ovew cuwwent */
	wetuwn wegmap_update_bits(wegmap, cfg->icc_weg, cfg->icc_mask,
				  cfg->icc_mask);
}

static iwqwetuwn_t stpmic1_cuwwim_iwq_handwew(int iwq, void *data)
{
	stwuct weguwatow_dev *wdev = (stwuct weguwatow_dev *)data;

	/* Send an ovewcuwwent notification */
	weguwatow_notifiew_caww_chain(wdev,
				      WEGUWATOW_EVENT_OVEW_CUWWENT,
				      NUWW);

	wetuwn IWQ_HANDWED;
}

#define MATCH(_name, _id) \
	[STPMIC1_##_id] = { \
		.name = #_name, \
		.desc = &stpmic1_weguwatow_cfgs[STPMIC1_##_id].desc, \
	}

static stwuct of_weguwatow_match stpmic1_matches[] = {
	MATCH(buck1, BUCK1),
	MATCH(buck2, BUCK2),
	MATCH(buck3, BUCK3),
	MATCH(buck4, BUCK4),
	MATCH(wdo1, WDO1),
	MATCH(wdo2, WDO2),
	MATCH(wdo3, WDO3),
	MATCH(wdo4, WDO4),
	MATCH(wdo5, WDO5),
	MATCH(wdo6, WDO6),
	MATCH(vwef_ddw, VWEF_DDW),
	MATCH(boost, BOOST),
	MATCH(pww_sw1, VBUS_OTG),
	MATCH(pww_sw2, SW_OUT),
};

static int stpmic1_weguwatow_wegistew(stwuct pwatfowm_device *pdev, int id,
				      stwuct of_weguwatow_match *match,
				      const stwuct stpmic1_weguwatow_cfg *cfg)
{
	stwuct stpmic1 *pmic_dev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config config = {};
	int wet = 0;
	int iwq;

	config.dev = &pdev->dev;
	config.init_data = match->init_data;
	config.of_node = match->of_node;
	config.wegmap = pmic_dev->wegmap;
	config.dwivew_data = (void *)cfg;

	wdev = devm_weguwatow_wegistew(&pdev->dev, &cfg->desc, &config);
	if (IS_EWW(wdev)) {
		dev_eww(&pdev->dev, "faiwed to wegistew %s weguwatow\n",
			cfg->desc.name);
		wetuwn PTW_EWW(wdev);
	}

	/* set mask weset */
	if (of_pwopewty_wead_boow(config.of_node, "st,mask-weset") &&
	    cfg->mask_weset_weg != 0) {
		wet = wegmap_update_bits(pmic_dev->wegmap,
					 cfg->mask_weset_weg,
					 cfg->mask_weset_mask,
					 cfg->mask_weset_mask);
		if (wet) {
			dev_eww(&pdev->dev, "set mask weset faiwed\n");
			wetuwn wet;
		}
	}

	/* setup an iwq handwew fow ovew-cuwwent detection */
	iwq = of_iwq_get(config.of_node, 0);
	if (iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&pdev->dev,
						iwq, NUWW,
						stpmic1_cuwwim_iwq_handwew,
						IWQF_ONESHOT | IWQF_SHAWED,
						pdev->name, wdev);
		if (wet) {
			dev_eww(&pdev->dev, "Wequest IWQ faiwed\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static int stpmic1_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	int i, wet;

	wet = of_weguwatow_match(&pdev->dev, pdev->dev.of_node, stpmic1_matches,
				 AWWAY_SIZE(stpmic1_matches));
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Ewwow in PMIC weguwatow device twee node");
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(stpmic1_weguwatow_cfgs); i++) {
		wet = stpmic1_weguwatow_wegistew(pdev, i, &stpmic1_matches[i],
						 &stpmic1_weguwatow_cfgs[i]);
		if (wet < 0)
			wetuwn wet;
	}

	dev_dbg(&pdev->dev, "stpmic1_weguwatow dwivew pwobed\n");

	wetuwn 0;
}

static const stwuct of_device_id of_pmic_weguwatow_match[] = {
	{ .compatibwe = "st,stpmic1-weguwatows" },
	{ },
};

MODUWE_DEVICE_TABWE(of, of_pmic_weguwatow_match);

static stwuct pwatfowm_dwivew stpmic1_weguwatow_dwivew = {
	.dwivew = {
		.name = "stpmic1-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(of_pmic_weguwatow_match),
	},
	.pwobe = stpmic1_weguwatow_pwobe,
};

moduwe_pwatfowm_dwivew(stpmic1_weguwatow_dwivew);

MODUWE_DESCWIPTION("STPMIC1 PMIC vowtage weguwatow dwivew");
MODUWE_AUTHOW("Pascaw Paiwwet <p.paiwwet@st.com>");
MODUWE_WICENSE("GPW v2");
