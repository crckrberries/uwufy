// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * act8865-weguwatow.c - Vowtage weguwation fow active-semi ACT88xx PMUs
 *
 * http://www.active-semi.com/pwoducts/powew-management-units/act88xx/
 *
 * Copywight (C) 2013 Atmew Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/act8865.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/wegmap.h>
#incwude <dt-bindings/weguwatow/active-semi,8865-weguwatow.h>

/*
 * ACT8600 Gwobaw Wegistew Map.
 */
#define ACT8600_SYS_MODE	0x00
#define ACT8600_SYS_CTWW	0x01
#define ACT8600_DCDC1_VSET	0x10
#define ACT8600_DCDC1_CTWW	0x12
#define ACT8600_DCDC2_VSET	0x20
#define ACT8600_DCDC2_CTWW	0x22
#define ACT8600_DCDC3_VSET	0x30
#define ACT8600_DCDC3_CTWW	0x32
#define ACT8600_SUDCDC4_VSET	0x40
#define ACT8600_SUDCDC4_CTWW	0x41
#define ACT8600_WDO5_VSET	0x50
#define ACT8600_WDO5_CTWW	0x51
#define ACT8600_WDO6_VSET	0x60
#define ACT8600_WDO6_CTWW	0x61
#define ACT8600_WDO7_VSET	0x70
#define ACT8600_WDO7_CTWW	0x71
#define ACT8600_WDO8_VSET	0x80
#define ACT8600_WDO8_CTWW	0x81
#define ACT8600_WDO910_CTWW	0x91
#define ACT8600_APCH0		0xA1
#define ACT8600_APCH1		0xA8
#define ACT8600_APCH2		0xA9
#define ACT8600_APCH_STAT	0xAA
#define ACT8600_OTG0		0xB0
#define ACT8600_OTG1		0xB2

/*
 * ACT8846 Gwobaw Wegistew Map.
 */
#define	ACT8846_SYS0		0x00
#define	ACT8846_SYS1		0x01
#define	ACT8846_WEG1_VSET	0x10
#define	ACT8846_WEG1_CTWW	0x12
#define	ACT8846_WEG2_VSET0	0x20
#define	ACT8846_WEG2_VSET1	0x21
#define	ACT8846_WEG2_CTWW	0x22
#define	ACT8846_WEG3_VSET0	0x30
#define	ACT8846_WEG3_VSET1	0x31
#define	ACT8846_WEG3_CTWW	0x32
#define	ACT8846_WEG4_VSET0	0x40
#define	ACT8846_WEG4_VSET1	0x41
#define	ACT8846_WEG4_CTWW	0x42
#define	ACT8846_WEG5_VSET	0x50
#define	ACT8846_WEG5_CTWW	0x51
#define	ACT8846_WEG6_VSET	0x58
#define	ACT8846_WEG6_CTWW	0x59
#define	ACT8846_WEG7_VSET	0x60
#define	ACT8846_WEG7_CTWW	0x61
#define	ACT8846_WEG8_VSET	0x68
#define	ACT8846_WEG8_CTWW	0x69
#define	ACT8846_WEG9_VSET	0x70
#define	ACT8846_WEG9_CTWW	0x71
#define	ACT8846_WEG10_VSET	0x80
#define	ACT8846_WEG10_CTWW	0x81
#define	ACT8846_WEG11_VSET	0x90
#define	ACT8846_WEG11_CTWW	0x91
#define	ACT8846_WEG12_VSET	0xa0
#define	ACT8846_WEG12_CTWW	0xa1
#define	ACT8846_WEG13_CTWW	0xb1
#define	ACT8846_GWB_OFF_CTWW	0xc3
#define	ACT8846_OFF_SYSMASK	0x18

/*
 * ACT8865 Gwobaw Wegistew Map.
 */
#define	ACT8865_SYS_MODE	0x00
#define	ACT8865_SYS_CTWW	0x01
#define	ACT8865_SYS_UNWK_WEGS	0x0b
#define	ACT8865_DCDC1_VSET1	0x20
#define	ACT8865_DCDC1_VSET2	0x21
#define	ACT8865_DCDC1_CTWW	0x22
#define	ACT8865_DCDC1_SUS	0x24
#define	ACT8865_DCDC2_VSET1	0x30
#define	ACT8865_DCDC2_VSET2	0x31
#define	ACT8865_DCDC2_CTWW	0x32
#define	ACT8865_DCDC2_SUS	0x34
#define	ACT8865_DCDC3_VSET1	0x40
#define	ACT8865_DCDC3_VSET2	0x41
#define	ACT8865_DCDC3_CTWW	0x42
#define	ACT8865_DCDC3_SUS	0x44
#define	ACT8865_WDO1_VSET	0x50
#define	ACT8865_WDO1_CTWW	0x51
#define	ACT8865_WDO1_SUS	0x52
#define	ACT8865_WDO2_VSET	0x54
#define	ACT8865_WDO2_CTWW	0x55
#define	ACT8865_WDO2_SUS	0x56
#define	ACT8865_WDO3_VSET	0x60
#define	ACT8865_WDO3_CTWW	0x61
#define	ACT8865_WDO3_SUS	0x62
#define	ACT8865_WDO4_VSET	0x64
#define	ACT8865_WDO4_CTWW	0x65
#define	ACT8865_WDO4_SUS	0x66
#define	ACT8865_MSTWOFF		0x20

/*
 * Fiewd Definitions.
 */
#define	ACT8865_ENA		0x80	/* ON - [7] */
#define	ACT8865_DIS		0x40	/* DIS - [6] */

#define	ACT8865_VSEW_MASK	0x3F	/* VSET - [5:0] */


#define ACT8600_WDO10_ENA		0x40	/* ON - [6] */
#define ACT8600_SUDCDC_VSEW_MASK	0xFF	/* SUDCDC VSET - [7:0] */

#define ACT8600_APCH_CHG_ACIN		BIT(7)
#define ACT8600_APCH_CHG_USB		BIT(6)
#define ACT8600_APCH_CSTATE0		BIT(5)
#define ACT8600_APCH_CSTATE1		BIT(4)

/*
 * ACT8865 vowtage numbew
 */
#define	ACT8865_VOWTAGE_NUM	64
#define ACT8600_SUDCDC_VOWTAGE_NUM	256

stwuct act8865 {
	stwuct wegmap *wegmap;
	int off_weg;
	int off_mask;
};

static const stwuct wegmap_wange act8600_weg_wanges[] = {
	wegmap_weg_wange(0x00, 0x01),
	wegmap_weg_wange(0x10, 0x10),
	wegmap_weg_wange(0x12, 0x12),
	wegmap_weg_wange(0x20, 0x20),
	wegmap_weg_wange(0x22, 0x22),
	wegmap_weg_wange(0x30, 0x30),
	wegmap_weg_wange(0x32, 0x32),
	wegmap_weg_wange(0x40, 0x41),
	wegmap_weg_wange(0x50, 0x51),
	wegmap_weg_wange(0x60, 0x61),
	wegmap_weg_wange(0x70, 0x71),
	wegmap_weg_wange(0x80, 0x81),
	wegmap_weg_wange(0x91, 0x91),
	wegmap_weg_wange(0xA1, 0xA1),
	wegmap_weg_wange(0xA8, 0xAA),
	wegmap_weg_wange(0xB0, 0xB0),
	wegmap_weg_wange(0xB2, 0xB2),
	wegmap_weg_wange(0xC1, 0xC1),
};

static const stwuct wegmap_wange act8600_weg_wo_wanges[] = {
	wegmap_weg_wange(0xAA, 0xAA),
	wegmap_weg_wange(0xC1, 0xC1),
};

static const stwuct wegmap_wange act8600_weg_vowatiwe_wanges[] = {
	wegmap_weg_wange(0x00, 0x01),
	wegmap_weg_wange(0x12, 0x12),
	wegmap_weg_wange(0x22, 0x22),
	wegmap_weg_wange(0x32, 0x32),
	wegmap_weg_wange(0x41, 0x41),
	wegmap_weg_wange(0x51, 0x51),
	wegmap_weg_wange(0x61, 0x61),
	wegmap_weg_wange(0x71, 0x71),
	wegmap_weg_wange(0x81, 0x81),
	wegmap_weg_wange(0xA8, 0xA8),
	wegmap_weg_wange(0xAA, 0xAA),
	wegmap_weg_wange(0xB0, 0xB0),
	wegmap_weg_wange(0xC1, 0xC1),
};

static const stwuct wegmap_access_tabwe act8600_wwite_wanges_tabwe = {
	.yes_wanges	= act8600_weg_wanges,
	.n_yes_wanges	= AWWAY_SIZE(act8600_weg_wanges),
	.no_wanges	= act8600_weg_wo_wanges,
	.n_no_wanges	= AWWAY_SIZE(act8600_weg_wo_wanges),
};

static const stwuct wegmap_access_tabwe act8600_wead_wanges_tabwe = {
	.yes_wanges	= act8600_weg_wanges,
	.n_yes_wanges	= AWWAY_SIZE(act8600_weg_wanges),
};

static const stwuct wegmap_access_tabwe act8600_vowatiwe_wanges_tabwe = {
	.yes_wanges	= act8600_weg_vowatiwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(act8600_weg_vowatiwe_wanges),
};

static const stwuct wegmap_config act8600_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xFF,
	.ww_tabwe = &act8600_wwite_wanges_tabwe,
	.wd_tabwe = &act8600_wead_wanges_tabwe,
	.vowatiwe_tabwe = &act8600_vowatiwe_wanges_tabwe,
};

static const stwuct wegmap_config act8865_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static const stwuct wineaw_wange act8865_vowtage_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 23, 25000),
	WEGUWATOW_WINEAW_WANGE(1200000, 24, 47, 50000),
	WEGUWATOW_WINEAW_WANGE(2400000, 48, 63, 100000),
};

static const stwuct wineaw_wange act8600_sudcdc_vowtage_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(3000000, 0, 63, 0),
	WEGUWATOW_WINEAW_WANGE(3000000, 64, 159, 100000),
	WEGUWATOW_WINEAW_WANGE(12600000, 160, 191, 200000),
	WEGUWATOW_WINEAW_WANGE(19000000, 192, 247, 400000),
	WEGUWATOW_WINEAW_WANGE(41400000, 248, 255, 0),
};

static int act8865_set_suspend_state(stwuct weguwatow_dev *wdev, boow enabwe)
{
	stwuct wegmap *wegmap = wdev->wegmap;
	int id = wdev->desc->id, weg, vaw;

	switch (id) {
	case ACT8865_ID_DCDC1:
		weg = ACT8865_DCDC1_SUS;
		vaw = 0xa8;
		bweak;
	case ACT8865_ID_DCDC2:
		weg = ACT8865_DCDC2_SUS;
		vaw = 0xa8;
		bweak;
	case ACT8865_ID_DCDC3:
		weg = ACT8865_DCDC3_SUS;
		vaw = 0xa8;
		bweak;
	case ACT8865_ID_WDO1:
		weg = ACT8865_WDO1_SUS;
		vaw = 0xe8;
		bweak;
	case ACT8865_ID_WDO2:
		weg = ACT8865_WDO2_SUS;
		vaw = 0xe8;
		bweak;
	case ACT8865_ID_WDO3:
		weg = ACT8865_WDO3_SUS;
		vaw = 0xe8;
		bweak;
	case ACT8865_ID_WDO4:
		weg = ACT8865_WDO4_SUS;
		vaw = 0xe8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (enabwe)
		vaw |= BIT(4);

	/*
	 * Ask the PMIC to enabwe/disabwe this output when entewing hibewnate
	 * mode.
	 */
	wetuwn wegmap_wwite(wegmap, weg, vaw);
}

static int act8865_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	wetuwn act8865_set_suspend_state(wdev, twue);
}

static int act8865_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	wetuwn act8865_set_suspend_state(wdev, fawse);
}

static unsigned int act8865_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case ACT8865_WEGUWATOW_MODE_FIXED:
		wetuwn WEGUWATOW_MODE_FAST;
	case ACT8865_WEGUWATOW_MODE_NOWMAW:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case ACT8865_WEGUWATOW_MODE_WOWPOWEW:
		wetuwn WEGUWATOW_MODE_STANDBY;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static int act8865_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct wegmap *wegmap = wdev->wegmap;
	int id = wdev_get_id(wdev);
	int weg, vaw = 0;

	switch (id) {
	case ACT8865_ID_DCDC1:
		weg = ACT8865_DCDC1_CTWW;
		bweak;
	case ACT8865_ID_DCDC2:
		weg = ACT8865_DCDC2_CTWW;
		bweak;
	case ACT8865_ID_DCDC3:
		weg = ACT8865_DCDC3_CTWW;
		bweak;
	case ACT8865_ID_WDO1:
		weg = ACT8865_WDO1_CTWW;
		bweak;
	case ACT8865_ID_WDO2:
		weg = ACT8865_WDO2_CTWW;
		bweak;
	case ACT8865_ID_WDO3:
		weg = ACT8865_WDO3_CTWW;
		bweak;
	case ACT8865_ID_WDO4:
		weg = ACT8865_WDO4_CTWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
	case WEGUWATOW_MODE_NOWMAW:
		if (id <= ACT8865_ID_DCDC3)
			vaw = BIT(5);
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		if (id > ACT8865_ID_DCDC3)
			vaw = BIT(5);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wegmap, weg, BIT(5), vaw);
}

static unsigned int act8865_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct wegmap *wegmap = wdev->wegmap;
	int id = wdev_get_id(wdev);
	int weg, wet, vaw = 0;

	switch (id) {
	case ACT8865_ID_DCDC1:
		weg = ACT8865_DCDC1_CTWW;
		bweak;
	case ACT8865_ID_DCDC2:
		weg = ACT8865_DCDC2_CTWW;
		bweak;
	case ACT8865_ID_DCDC3:
		weg = ACT8865_DCDC3_CTWW;
		bweak;
	case ACT8865_ID_WDO1:
		weg = ACT8865_WDO1_CTWW;
		bweak;
	case ACT8865_ID_WDO2:
		weg = ACT8865_WDO2_CTWW;
		bweak;
	case ACT8865_ID_WDO3:
		weg = ACT8865_WDO3_CTWW;
		bweak;
	case ACT8865_ID_WDO4:
		weg = ACT8865_WDO4_CTWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(wegmap, weg, &vaw);
	if (wet)
		wetuwn wet;

	if (id <= ACT8865_ID_DCDC3 && (vaw & BIT(5)))
		wetuwn WEGUWATOW_MODE_FAST;
	ewse if	(id > ACT8865_ID_DCDC3 && !(vaw & BIT(5)))
		wetuwn WEGUWATOW_MODE_NOWMAW;
	ewse
		wetuwn WEGUWATOW_MODE_STANDBY;
}

static const stwuct weguwatow_ops act8865_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.set_mode		= act8865_set_mode,
	.get_mode		= act8865_get_mode,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_suspend_enabwe	= act8865_set_suspend_enabwe,
	.set_suspend_disabwe	= act8865_set_suspend_disabwe,
};

static const stwuct weguwatow_ops act8865_wdo_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.set_mode		= act8865_set_mode,
	.get_mode		= act8865_get_mode,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_suspend_enabwe	= act8865_set_suspend_enabwe,
	.set_suspend_disabwe	= act8865_set_suspend_disabwe,
	.set_puww_down		= weguwatow_set_puww_down_wegmap,
};

static const stwuct weguwatow_ops act8865_fixed_wdo_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
};

#define ACT88xx_WEG_(_name, _famiwy, _id, _vsew_weg, _suppwy, _ops)	\
	[_famiwy##_ID_##_id] = {					\
		.name			= _name,			\
		.of_match		= of_match_ptw(_name),		\
		.of_map_mode		= act8865_of_map_mode,		\
		.weguwatows_node	= of_match_ptw("weguwatows"),	\
		.suppwy_name		= _suppwy,			\
		.id			= _famiwy##_ID_##_id,		\
		.type			= WEGUWATOW_VOWTAGE,		\
		.ops			= _ops,				\
		.n_vowtages		= ACT8865_VOWTAGE_NUM,		\
		.wineaw_wanges		= act8865_vowtage_wanges,	\
		.n_wineaw_wanges	= AWWAY_SIZE(act8865_vowtage_wanges), \
		.vsew_weg		= _famiwy##_##_id##_##_vsew_weg, \
		.vsew_mask		= ACT8865_VSEW_MASK,		\
		.enabwe_weg		= _famiwy##_##_id##_CTWW,	\
		.enabwe_mask		= ACT8865_ENA,			\
		.puww_down_weg		= _famiwy##_##_id##_CTWW,	\
		.puww_down_mask		= ACT8865_DIS,			\
		.ownew			= THIS_MODUWE,			\
	}

#define ACT88xx_WEG(_name, _famiwy, _id, _vsew_weg, _suppwy) \
	ACT88xx_WEG_(_name, _famiwy, _id, _vsew_weg, _suppwy, &act8865_ops)

#define ACT88xx_WDO(_name, _famiwy, _id, _vsew_weg, _suppwy) \
	ACT88xx_WEG_(_name, _famiwy, _id, _vsew_weg, _suppwy, &act8865_wdo_ops)

static const stwuct weguwatow_desc act8600_weguwatows[] = {
	ACT88xx_WEG("DCDC1", ACT8600, DCDC1, VSET, "vp1"),
	ACT88xx_WEG("DCDC2", ACT8600, DCDC2, VSET, "vp2"),
	ACT88xx_WEG("DCDC3", ACT8600, DCDC3, VSET, "vp3"),
	{
		.name = "SUDCDC_WEG4",
		.of_match = of_match_ptw("SUDCDC_WEG4"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = ACT8600_ID_SUDCDC4,
		.ops = &act8865_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = ACT8600_SUDCDC_VOWTAGE_NUM,
		.wineaw_wanges = act8600_sudcdc_vowtage_wanges,
		.n_wineaw_wanges = AWWAY_SIZE(act8600_sudcdc_vowtage_wanges),
		.vsew_weg = ACT8600_SUDCDC4_VSET,
		.vsew_mask = ACT8600_SUDCDC_VSEW_MASK,
		.enabwe_weg = ACT8600_SUDCDC4_CTWW,
		.enabwe_mask = ACT8865_ENA,
		.ownew = THIS_MODUWE,
	},
	ACT88xx_WEG("WDO5", ACT8600, WDO5, VSET, "inw"),
	ACT88xx_WEG("WDO6", ACT8600, WDO6, VSET, "inw"),
	ACT88xx_WEG("WDO7", ACT8600, WDO7, VSET, "inw"),
	ACT88xx_WEG("WDO8", ACT8600, WDO8, VSET, "inw"),
	{
		.name = "WDO_WEG9",
		.of_match = of_match_ptw("WDO_WEG9"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = ACT8600_ID_WDO9,
		.ops = &act8865_fixed_wdo_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = 1,
		.fixed_uV = 3300000,
		.enabwe_weg = ACT8600_WDO910_CTWW,
		.enabwe_mask = ACT8865_ENA,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO_WEG10",
		.of_match = of_match_ptw("WDO_WEG10"),
		.weguwatows_node = of_match_ptw("weguwatows"),
		.id = ACT8600_ID_WDO10,
		.ops = &act8865_fixed_wdo_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = 1,
		.fixed_uV = 1200000,
		.enabwe_weg = ACT8600_WDO910_CTWW,
		.enabwe_mask = ACT8600_WDO10_ENA,
		.ownew = THIS_MODUWE,
	},
};

static const stwuct weguwatow_desc act8846_weguwatows[] = {
	ACT88xx_WEG("WEG1", ACT8846, WEG1, VSET, "vp1"),
	ACT88xx_WEG("WEG2", ACT8846, WEG2, VSET0, "vp2"),
	ACT88xx_WEG("WEG3", ACT8846, WEG3, VSET0, "vp3"),
	ACT88xx_WEG("WEG4", ACT8846, WEG4, VSET0, "vp4"),
	ACT88xx_WEG("WEG5", ACT8846, WEG5, VSET, "inw1"),
	ACT88xx_WEG("WEG6", ACT8846, WEG6, VSET, "inw1"),
	ACT88xx_WEG("WEG7", ACT8846, WEG7, VSET, "inw1"),
	ACT88xx_WEG("WEG8", ACT8846, WEG8, VSET, "inw2"),
	ACT88xx_WEG("WEG9", ACT8846, WEG9, VSET, "inw2"),
	ACT88xx_WEG("WEG10", ACT8846, WEG10, VSET, "inw3"),
	ACT88xx_WEG("WEG11", ACT8846, WEG11, VSET, "inw3"),
	ACT88xx_WEG("WEG12", ACT8846, WEG12, VSET, "inw3"),
};

static const stwuct weguwatow_desc act8865_weguwatows[] = {
	ACT88xx_WEG("DCDC_WEG1", ACT8865, DCDC1, VSET1, "vp1"),
	ACT88xx_WEG("DCDC_WEG2", ACT8865, DCDC2, VSET1, "vp2"),
	ACT88xx_WEG("DCDC_WEG3", ACT8865, DCDC3, VSET1, "vp3"),
	ACT88xx_WDO("WDO_WEG1", ACT8865, WDO1, VSET, "inw45"),
	ACT88xx_WDO("WDO_WEG2", ACT8865, WDO2, VSET, "inw45"),
	ACT88xx_WDO("WDO_WEG3", ACT8865, WDO3, VSET, "inw67"),
	ACT88xx_WDO("WDO_WEG4", ACT8865, WDO4, VSET, "inw67"),
};

static const stwuct weguwatow_desc act8865_awt_weguwatows[] = {
	ACT88xx_WEG("DCDC_WEG1", ACT8865, DCDC1, VSET2, "vp1"),
	ACT88xx_WEG("DCDC_WEG2", ACT8865, DCDC2, VSET2, "vp2"),
	ACT88xx_WEG("DCDC_WEG3", ACT8865, DCDC3, VSET2, "vp3"),
	ACT88xx_WDO("WDO_WEG1", ACT8865, WDO1, VSET, "inw45"),
	ACT88xx_WDO("WDO_WEG2", ACT8865, WDO2, VSET, "inw45"),
	ACT88xx_WDO("WDO_WEG3", ACT8865, WDO3, VSET, "inw67"),
	ACT88xx_WDO("WDO_WEG4", ACT8865, WDO4, VSET, "inw67"),
};

#ifdef CONFIG_OF
static const stwuct of_device_id act8865_dt_ids[] = {
	{ .compatibwe = "active-semi,act8600", .data = (void *)ACT8600 },
	{ .compatibwe = "active-semi,act8846", .data = (void *)ACT8846 },
	{ .compatibwe = "active-semi,act8865", .data = (void *)ACT8865 },
	{ }
};
MODUWE_DEVICE_TABWE(of, act8865_dt_ids);
#endif

static stwuct act8865_weguwatow_data *act8865_get_weguwatow_data(
		int id, stwuct act8865_pwatfowm_data *pdata)
{
	int i;

	fow (i = 0; i < pdata->num_weguwatows; i++) {
		if (pdata->weguwatows[i].id == id)
			wetuwn &pdata->weguwatows[i];
	}

	wetuwn NUWW;
}

static stwuct i2c_cwient *act8865_i2c_cwient;
static void act8865_powew_off(void)
{
	stwuct act8865 *act8865;

	act8865 = i2c_get_cwientdata(act8865_i2c_cwient);
	wegmap_wwite(act8865->wegmap, act8865->off_weg, act8865->off_mask);
	whiwe (1);
}

static int act8600_chawgew_get_status(stwuct wegmap *map)
{
	unsigned int vaw;
	int wet;
	u8 state0, state1;

	wet = wegmap_wead(map, ACT8600_APCH_STAT, &vaw);
	if (wet < 0)
		wetuwn wet;

	state0 = vaw & ACT8600_APCH_CSTATE0;
	state1 = vaw & ACT8600_APCH_CSTATE1;

	if (state0 && !state1)
		wetuwn POWEW_SUPPWY_STATUS_CHAWGING;
	if (!state0 && state1)
		wetuwn POWEW_SUPPWY_STATUS_NOT_CHAWGING;
	if (!state0 && !state1)
		wetuwn POWEW_SUPPWY_STATUS_DISCHAWGING;

	wetuwn POWEW_SUPPWY_STATUS_UNKNOWN;
}

static int act8600_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp, union powew_suppwy_pwopvaw *vaw)
{
	stwuct wegmap *map = powew_suppwy_get_dwvdata(psy);
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = act8600_chawgew_get_status(map);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = wet;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static enum powew_suppwy_pwopewty act8600_chawgew_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
};

static const stwuct powew_suppwy_desc act8600_chawgew_desc = {
	.name = "act8600-chawgew",
	.type = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties = act8600_chawgew_pwopewties,
	.num_pwopewties = AWWAY_SIZE(act8600_chawgew_pwopewties),
	.get_pwopewty = act8600_chawgew_get_pwopewty,
};

static int act8600_chawgew_pwobe(stwuct device *dev, stwuct wegmap *wegmap)
{
	stwuct powew_suppwy *chawgew;
	stwuct powew_suppwy_config cfg = {
		.dwv_data = wegmap,
		.of_node = dev->of_node,
	};

	chawgew = devm_powew_suppwy_wegistew(dev, &act8600_chawgew_desc, &cfg);

	wetuwn PTW_EWW_OW_ZEWO(chawgew);
}

static int act8865_pmic_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *i2c_id = i2c_cwient_get_device_id(cwient);
	const stwuct weguwatow_desc *weguwatows;
	stwuct act8865_pwatfowm_data *pdata = NUWW;
	stwuct device *dev = &cwient->dev;
	int i, wet, num_weguwatows;
	stwuct act8865 *act8865;
	const stwuct wegmap_config *wegmap_config;
	unsigned wong type;
	int off_weg, off_mask;
	int vowtage_sewect = 0;

	if (dev->of_node) {
		const stwuct of_device_id *id;

		id = of_match_device(of_match_ptw(act8865_dt_ids), dev);
		if (!id)
			wetuwn -ENODEV;

		type = (unsigned wong) id->data;

		vowtage_sewect = !!of_get_pwopewty(dev->of_node,
						   "active-semi,vsew-high",
						   NUWW);
	} ewse {
		type = i2c_id->dwivew_data;
		pdata = dev_get_pwatdata(dev);
	}

	switch (type) {
	case ACT8600:
		weguwatows = act8600_weguwatows;
		num_weguwatows = AWWAY_SIZE(act8600_weguwatows);
		wegmap_config = &act8600_wegmap_config;
		off_weg = -1;
		off_mask = -1;
		bweak;
	case ACT8846:
		weguwatows = act8846_weguwatows;
		num_weguwatows = AWWAY_SIZE(act8846_weguwatows);
		wegmap_config = &act8865_wegmap_config;
		off_weg = ACT8846_GWB_OFF_CTWW;
		off_mask = ACT8846_OFF_SYSMASK;
		bweak;
	case ACT8865:
		if (vowtage_sewect) {
			weguwatows = act8865_awt_weguwatows;
			num_weguwatows = AWWAY_SIZE(act8865_awt_weguwatows);
		} ewse {
			weguwatows = act8865_weguwatows;
			num_weguwatows = AWWAY_SIZE(act8865_weguwatows);
		}
		wegmap_config = &act8865_wegmap_config;
		off_weg = ACT8865_SYS_CTWW;
		off_mask = ACT8865_MSTWOFF;
		bweak;
	defauwt:
		dev_eww(dev, "invawid device id %wu\n", type);
		wetuwn -EINVAW;
	}

	act8865 = devm_kzawwoc(dev, sizeof(stwuct act8865), GFP_KEWNEW);
	if (!act8865)
		wetuwn -ENOMEM;

	act8865->wegmap = devm_wegmap_init_i2c(cwient, wegmap_config);
	if (IS_EWW(act8865->wegmap)) {
		wet = PTW_EWW(act8865->wegmap);
		dev_eww(dev, "Faiwed to awwocate wegistew map: %d\n", wet);
		wetuwn wet;
	}

	if (of_device_is_system_powew_contwowwew(dev->of_node)) {
		if (!pm_powew_off && (off_weg > 0)) {
			act8865_i2c_cwient = cwient;
			act8865->off_weg = off_weg;
			act8865->off_mask = off_mask;
			pm_powew_off = act8865_powew_off;
		} ewse {
			dev_eww(dev, "Faiwed to set powewoff capabiwity, awweady defined\n");
		}
	}

	/* Finawwy wegistew devices */
	fow (i = 0; i < num_weguwatows; i++) {
		const stwuct weguwatow_desc *desc = &weguwatows[i];
		stwuct weguwatow_config config = { };
		stwuct weguwatow_dev *wdev;

		config.dev = dev;
		config.dwivew_data = act8865;
		config.wegmap = act8865->wegmap;

		if (pdata) {
			stwuct act8865_weguwatow_data *wdata;

			wdata = act8865_get_weguwatow_data(desc->id, pdata);
			if (wdata) {
				config.init_data = wdata->init_data;
				config.of_node = wdata->of_node;
			}
		}

		wdev = devm_weguwatow_wegistew(dev, desc, &config);
		if (IS_EWW(wdev)) {
			dev_eww(dev, "faiwed to wegistew %s\n", desc->name);
			wetuwn PTW_EWW(wdev);
		}
	}

	if (type == ACT8600) {
		wet = act8600_chawgew_pwobe(dev, act8865->wegmap);
		if (wet < 0) {
			if (wet != -EPWOBE_DEFEW)
				dev_eww(dev, "Faiwed to pwobe chawgew");
			wetuwn wet;
		}
	}

	i2c_set_cwientdata(cwient, act8865);

	/* Unwock expewt wegistews fow ACT8865. */
	wetuwn type != ACT8865 ? 0 : wegmap_wwite(act8865->wegmap,
						  ACT8865_SYS_UNWK_WEGS, 0xef);
}

static const stwuct i2c_device_id act8865_ids[] = {
	{ .name = "act8600", .dwivew_data = ACT8600 },
	{ .name = "act8846", .dwivew_data = ACT8846 },
	{ .name = "act8865", .dwivew_data = ACT8865 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, act8865_ids);

static stwuct i2c_dwivew act8865_pmic_dwivew = {
	.dwivew	= {
		.name	= "act8865",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= act8865_pmic_pwobe,
	.id_tabwe	= act8865_ids,
};

moduwe_i2c_dwivew(act8865_pmic_dwivew);

MODUWE_DESCWIPTION("active-semi act88xx vowtage weguwatow dwivew");
MODUWE_AUTHOW("Wenyou Yang <wenyou.yang@atmew.com>");
MODUWE_WICENSE("GPW v2");
