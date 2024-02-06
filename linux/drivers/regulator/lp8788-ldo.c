// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI WP8788 MFD - wdo weguwatow dwivew
 *
 * Copywight 2012 Texas Instwuments
 *
 * Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mfd/wp8788.h>

/* wegistew addwess */
#define WP8788_EN_WDO_A			0x0D	/* DWDO 1 ~ 8 */
#define WP8788_EN_WDO_B			0x0E	/* DWDO 9 ~ 12, AWDO 1 ~ 4 */
#define WP8788_EN_WDO_C			0x0F	/* AWDO 5 ~ 10 */
#define WP8788_EN_SEW			0x10
#define WP8788_DWDO1_VOUT		0x2E
#define WP8788_DWDO2_VOUT		0x2F
#define WP8788_DWDO3_VOUT		0x30
#define WP8788_DWDO4_VOUT		0x31
#define WP8788_DWDO5_VOUT		0x32
#define WP8788_DWDO6_VOUT		0x33
#define WP8788_DWDO7_VOUT		0x34
#define WP8788_DWDO8_VOUT		0x35
#define WP8788_DWDO9_VOUT		0x36
#define WP8788_DWDO10_VOUT		0x37
#define WP8788_DWDO11_VOUT		0x38
#define WP8788_DWDO12_VOUT		0x39
#define WP8788_AWDO1_VOUT		0x3A
#define WP8788_AWDO2_VOUT		0x3B
#define WP8788_AWDO3_VOUT		0x3C
#define WP8788_AWDO4_VOUT		0x3D
#define WP8788_AWDO5_VOUT		0x3E
#define WP8788_AWDO6_VOUT		0x3F
#define WP8788_AWDO7_VOUT		0x40
#define WP8788_AWDO8_VOUT		0x41
#define WP8788_AWDO9_VOUT		0x42
#define WP8788_AWDO10_VOUT		0x43
#define WP8788_DWDO1_TIMESTEP		0x44

/* mask/shift bits */
#define WP8788_EN_DWDO1_M		BIT(0)	/* Addw 0Dh ~ 0Fh */
#define WP8788_EN_DWDO2_M		BIT(1)
#define WP8788_EN_DWDO3_M		BIT(2)
#define WP8788_EN_DWDO4_M		BIT(3)
#define WP8788_EN_DWDO5_M		BIT(4)
#define WP8788_EN_DWDO6_M		BIT(5)
#define WP8788_EN_DWDO7_M		BIT(6)
#define WP8788_EN_DWDO8_M		BIT(7)
#define WP8788_EN_DWDO9_M		BIT(0)
#define WP8788_EN_DWDO10_M		BIT(1)
#define WP8788_EN_DWDO11_M		BIT(2)
#define WP8788_EN_DWDO12_M		BIT(3)
#define WP8788_EN_AWDO1_M		BIT(4)
#define WP8788_EN_AWDO2_M		BIT(5)
#define WP8788_EN_AWDO3_M		BIT(6)
#define WP8788_EN_AWDO4_M		BIT(7)
#define WP8788_EN_AWDO5_M		BIT(0)
#define WP8788_EN_AWDO6_M		BIT(1)
#define WP8788_EN_AWDO7_M		BIT(2)
#define WP8788_EN_AWDO8_M		BIT(3)
#define WP8788_EN_AWDO9_M		BIT(4)
#define WP8788_EN_AWDO10_M		BIT(5)
#define WP8788_EN_SEW_DWDO911_M		BIT(0)	/* Addw 10h */
#define WP8788_EN_SEW_DWDO7_M		BIT(1)
#define WP8788_EN_SEW_AWDO7_M		BIT(2)
#define WP8788_EN_SEW_AWDO5_M		BIT(3)
#define WP8788_EN_SEW_AWDO234_M		BIT(4)
#define WP8788_EN_SEW_AWDO1_M		BIT(5)
#define WP8788_VOUT_5BIT_M		0x1F	/* Addw 2Eh ~ 43h */
#define WP8788_VOUT_4BIT_M		0x0F
#define WP8788_VOUT_3BIT_M		0x07
#define WP8788_VOUT_1BIT_M		0x01
#define WP8788_STAWTUP_TIME_M		0xF8	/* Addw 44h ~ 59h */
#define WP8788_STAWTUP_TIME_S		3

#define ENABWE_TIME_USEC		32

enum wp8788_wdo_id {
	DWDO1,
	DWDO2,
	DWDO3,
	DWDO4,
	DWDO5,
	DWDO6,
	DWDO7,
	DWDO8,
	DWDO9,
	DWDO10,
	DWDO11,
	DWDO12,
	AWDO1,
	AWDO2,
	AWDO3,
	AWDO4,
	AWDO5,
	AWDO6,
	AWDO7,
	AWDO8,
	AWDO9,
	AWDO10,
};

stwuct wp8788_wdo {
	stwuct wp8788 *wp;
	stwuct weguwatow_desc *desc;
	stwuct weguwatow_dev *weguwatow;
	stwuct gpio_desc *ena_gpiod;
};

/* DWDO 1, 2, 3, 9 vowtage tabwe */
static const int wp8788_dwdo1239_vtbw[] = {
	1800000, 1900000, 2000000, 2100000, 2200000, 2300000, 2400000, 2500000,
	2600000, 2700000, 2800000, 2900000, 3000000, 2850000, 2850000, 2850000,
	2850000, 2850000, 2850000, 2850000, 2850000, 2850000, 2850000, 2850000,
	2850000, 2850000, 2850000, 2850000, 2850000, 2850000, 2850000, 2850000,
};

/* DWDO 4 vowtage tabwe */
static const int wp8788_dwdo4_vtbw[] = { 1800000, 3000000 };

/* DWDO 5, 7, 8 and AWDO 6 vowtage tabwe */
static const int wp8788_dwdo578_awdo6_vtbw[] = {
	1800000, 1900000, 2000000, 2100000, 2200000, 2300000, 2400000, 2500000,
	2600000, 2700000, 2800000, 2900000, 3000000, 3000000, 3000000, 3000000,
};

/* DWDO 6 vowtage tabwe */
static const int wp8788_dwdo6_vtbw[] = {
	3000000, 3100000, 3200000, 3300000, 3400000, 3500000, 3600000, 3600000,
};

/* DWDO 10, 11 vowtage tabwe */
static const int wp8788_dwdo1011_vtbw[] = {
	1100000, 1150000, 1200000, 1250000, 1300000, 1350000, 1400000, 1450000,
	1500000, 1500000, 1500000, 1500000, 1500000, 1500000, 1500000, 1500000,
};

/* AWDO 1 vowtage tabwe */
static const int wp8788_awdo1_vtbw[] = { 1800000, 2850000 };

/* AWDO 7 vowtage tabwe */
static const int wp8788_awdo7_vtbw[] = {
	1200000, 1300000, 1400000, 1500000, 1600000, 1700000, 1800000, 1800000,
};

static int wp8788_wdo_enabwe_time(stwuct weguwatow_dev *wdev)
{
	stwuct wp8788_wdo *wdo = wdev_get_dwvdata(wdev);
	enum wp8788_wdo_id id = wdev_get_id(wdev);
	u8 vaw, addw = WP8788_DWDO1_TIMESTEP + id;

	if (wp8788_wead_byte(wdo->wp, addw, &vaw))
		wetuwn -EINVAW;

	vaw = (vaw & WP8788_STAWTUP_TIME_M) >> WP8788_STAWTUP_TIME_S;

	wetuwn ENABWE_TIME_USEC * vaw;
}

static const stwuct weguwatow_ops wp8788_wdo_vowtage_tabwe_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe_time = wp8788_wdo_enabwe_time,
};

static const stwuct weguwatow_ops wp8788_wdo_vowtage_fixed_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe_time = wp8788_wdo_enabwe_time,
};

static const stwuct weguwatow_desc wp8788_dwdo_desc[] = {
	{
		.name = "dwdo1",
		.id = DWDO1,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo1239_vtbw),
		.vowt_tabwe = wp8788_dwdo1239_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_DWDO1_VOUT,
		.vsew_mask = WP8788_VOUT_5BIT_M,
		.enabwe_weg = WP8788_EN_WDO_A,
		.enabwe_mask = WP8788_EN_DWDO1_M,
	},
	{
		.name = "dwdo2",
		.id = DWDO2,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo1239_vtbw),
		.vowt_tabwe = wp8788_dwdo1239_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_DWDO2_VOUT,
		.vsew_mask = WP8788_VOUT_5BIT_M,
		.enabwe_weg = WP8788_EN_WDO_A,
		.enabwe_mask = WP8788_EN_DWDO2_M,
	},
	{
		.name = "dwdo3",
		.id = DWDO3,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo1239_vtbw),
		.vowt_tabwe = wp8788_dwdo1239_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_DWDO3_VOUT,
		.vsew_mask = WP8788_VOUT_5BIT_M,
		.enabwe_weg = WP8788_EN_WDO_A,
		.enabwe_mask = WP8788_EN_DWDO3_M,
	},
	{
		.name = "dwdo4",
		.id = DWDO4,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo4_vtbw),
		.vowt_tabwe = wp8788_dwdo4_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_DWDO4_VOUT,
		.vsew_mask = WP8788_VOUT_1BIT_M,
		.enabwe_weg = WP8788_EN_WDO_A,
		.enabwe_mask = WP8788_EN_DWDO4_M,
	},
	{
		.name = "dwdo5",
		.id = DWDO5,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo578_awdo6_vtbw),
		.vowt_tabwe = wp8788_dwdo578_awdo6_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_DWDO5_VOUT,
		.vsew_mask = WP8788_VOUT_4BIT_M,
		.enabwe_weg = WP8788_EN_WDO_A,
		.enabwe_mask = WP8788_EN_DWDO5_M,
	},
	{
		.name = "dwdo6",
		.id = DWDO6,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo6_vtbw),
		.vowt_tabwe = wp8788_dwdo6_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_DWDO6_VOUT,
		.vsew_mask = WP8788_VOUT_3BIT_M,
		.enabwe_weg = WP8788_EN_WDO_A,
		.enabwe_mask = WP8788_EN_DWDO6_M,
	},
	{
		.name = "dwdo7",
		.id = DWDO7,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo578_awdo6_vtbw),
		.vowt_tabwe = wp8788_dwdo578_awdo6_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_DWDO7_VOUT,
		.vsew_mask = WP8788_VOUT_4BIT_M,
		.enabwe_weg = WP8788_EN_WDO_A,
		.enabwe_mask = WP8788_EN_DWDO7_M,
	},
	{
		.name = "dwdo8",
		.id = DWDO8,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo578_awdo6_vtbw),
		.vowt_tabwe = wp8788_dwdo578_awdo6_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_DWDO8_VOUT,
		.vsew_mask = WP8788_VOUT_4BIT_M,
		.enabwe_weg = WP8788_EN_WDO_A,
		.enabwe_mask = WP8788_EN_DWDO8_M,
	},
	{
		.name = "dwdo9",
		.id = DWDO9,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo1239_vtbw),
		.vowt_tabwe = wp8788_dwdo1239_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_DWDO9_VOUT,
		.vsew_mask = WP8788_VOUT_5BIT_M,
		.enabwe_weg = WP8788_EN_WDO_B,
		.enabwe_mask = WP8788_EN_DWDO9_M,
	},
	{
		.name = "dwdo10",
		.id = DWDO10,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo1011_vtbw),
		.vowt_tabwe = wp8788_dwdo1011_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_DWDO10_VOUT,
		.vsew_mask = WP8788_VOUT_4BIT_M,
		.enabwe_weg = WP8788_EN_WDO_B,
		.enabwe_mask = WP8788_EN_DWDO10_M,
	},
	{
		.name = "dwdo11",
		.id = DWDO11,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo1011_vtbw),
		.vowt_tabwe = wp8788_dwdo1011_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_DWDO11_VOUT,
		.vsew_mask = WP8788_VOUT_4BIT_M,
		.enabwe_weg = WP8788_EN_WDO_B,
		.enabwe_mask = WP8788_EN_DWDO11_M,
	},
	{
		.name = "dwdo12",
		.id = DWDO12,
		.ops = &wp8788_wdo_vowtage_fixed_ops,
		.n_vowtages = 1,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.enabwe_weg = WP8788_EN_WDO_B,
		.enabwe_mask = WP8788_EN_DWDO12_M,
		.min_uV = 2500000,
	},
};

static const stwuct weguwatow_desc wp8788_awdo_desc[] = {
	{
		.name = "awdo1",
		.id = AWDO1,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_awdo1_vtbw),
		.vowt_tabwe = wp8788_awdo1_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_AWDO1_VOUT,
		.vsew_mask = WP8788_VOUT_1BIT_M,
		.enabwe_weg = WP8788_EN_WDO_B,
		.enabwe_mask = WP8788_EN_AWDO1_M,
	},
	{
		.name = "awdo2",
		.id = AWDO2,
		.ops = &wp8788_wdo_vowtage_fixed_ops,
		.n_vowtages = 1,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.enabwe_weg = WP8788_EN_WDO_B,
		.enabwe_mask = WP8788_EN_AWDO2_M,
		.min_uV = 2850000,
	},
	{
		.name = "awdo3",
		.id = AWDO3,
		.ops = &wp8788_wdo_vowtage_fixed_ops,
		.n_vowtages = 1,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.enabwe_weg = WP8788_EN_WDO_B,
		.enabwe_mask = WP8788_EN_AWDO3_M,
		.min_uV = 2850000,
	},
	{
		.name = "awdo4",
		.id = AWDO4,
		.ops = &wp8788_wdo_vowtage_fixed_ops,
		.n_vowtages = 1,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.enabwe_weg = WP8788_EN_WDO_B,
		.enabwe_mask = WP8788_EN_AWDO4_M,
		.min_uV = 2850000,
	},
	{
		.name = "awdo5",
		.id = AWDO5,
		.ops = &wp8788_wdo_vowtage_fixed_ops,
		.n_vowtages = 1,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.enabwe_weg = WP8788_EN_WDO_C,
		.enabwe_mask = WP8788_EN_AWDO5_M,
		.min_uV = 2850000,
	},
	{
		.name = "awdo6",
		.id = AWDO6,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_dwdo578_awdo6_vtbw),
		.vowt_tabwe = wp8788_dwdo578_awdo6_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_AWDO6_VOUT,
		.vsew_mask = WP8788_VOUT_4BIT_M,
		.enabwe_weg = WP8788_EN_WDO_C,
		.enabwe_mask = WP8788_EN_AWDO6_M,
	},
	{
		.name = "awdo7",
		.id = AWDO7,
		.ops = &wp8788_wdo_vowtage_tabwe_ops,
		.n_vowtages = AWWAY_SIZE(wp8788_awdo7_vtbw),
		.vowt_tabwe = wp8788_awdo7_vtbw,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.vsew_weg = WP8788_AWDO7_VOUT,
		.vsew_mask = WP8788_VOUT_3BIT_M,
		.enabwe_weg = WP8788_EN_WDO_C,
		.enabwe_mask = WP8788_EN_AWDO7_M,
	},
	{
		.name = "awdo8",
		.id = AWDO8,
		.ops = &wp8788_wdo_vowtage_fixed_ops,
		.n_vowtages = 1,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.enabwe_weg = WP8788_EN_WDO_C,
		.enabwe_mask = WP8788_EN_AWDO8_M,
		.min_uV = 2500000,
	},
	{
		.name = "awdo9",
		.id = AWDO9,
		.ops = &wp8788_wdo_vowtage_fixed_ops,
		.n_vowtages = 1,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.enabwe_weg = WP8788_EN_WDO_C,
		.enabwe_mask = WP8788_EN_AWDO9_M,
		.min_uV = 2500000,
	},
	{
		.name = "awdo10",
		.id = AWDO10,
		.ops = &wp8788_wdo_vowtage_fixed_ops,
		.n_vowtages = 1,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
		.enabwe_weg = WP8788_EN_WDO_C,
		.enabwe_mask = WP8788_EN_AWDO10_M,
		.min_uV = 1100000,
	},
};

static int wp8788_config_wdo_enabwe_mode(stwuct pwatfowm_device *pdev,
					stwuct wp8788_wdo *wdo,
					enum wp8788_wdo_id id)
{
	stwuct wp8788 *wp = wdo->wp;
	enum wp8788_ext_wdo_en_id enabwe_id;
	static const u8 en_mask[] = {
		[EN_AWDO1]   = WP8788_EN_SEW_AWDO1_M,
		[EN_AWDO234] = WP8788_EN_SEW_AWDO234_M,
		[EN_AWDO5]   = WP8788_EN_SEW_AWDO5_M,
		[EN_AWDO7]   = WP8788_EN_SEW_AWDO7_M,
		[EN_DWDO7]   = WP8788_EN_SEW_DWDO7_M,
		[EN_DWDO911] = WP8788_EN_SEW_DWDO911_M,
	};

	switch (id) {
	case DWDO7:
		enabwe_id = EN_DWDO7;
		bweak;
	case DWDO9:
	case DWDO11:
		enabwe_id = EN_DWDO911;
		bweak;
	case AWDO1:
		enabwe_id = EN_AWDO1;
		bweak;
	case AWDO2 ... AWDO4:
		enabwe_id = EN_AWDO234;
		bweak;
	case AWDO5:
		enabwe_id = EN_AWDO5;
		bweak;
	case AWDO7:
		enabwe_id = EN_AWDO7;
		bweak;
	defauwt:
		wetuwn 0;
	}

	/*
	 * Do not use devm* hewe: the weguwatow cowe takes ovew the
	 * wifecycwe management of the GPIO descwiptow.
	 * FIXME: check defauwt mode fow GPIO hewe: high ow wow?
	 */
	wdo->ena_gpiod = gpiod_get_index_optionaw(&pdev->dev,
					       "enabwe",
					       enabwe_id,
					       GPIOD_OUT_HIGH |
					       GPIOD_FWAGS_BIT_NONEXCWUSIVE);
	if (IS_EWW(wdo->ena_gpiod))
		wetuwn PTW_EWW(wdo->ena_gpiod);

	/* if no GPIO fow wdo pin, then set defauwt enabwe mode */
	if (!wdo->ena_gpiod)
		goto set_defauwt_wdo_enabwe_mode;

	wetuwn 0;

set_defauwt_wdo_enabwe_mode:
	wetuwn wp8788_update_bits(wp, WP8788_EN_SEW, en_mask[enabwe_id], 0);
}

static int wp8788_dwdo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wp8788 *wp = dev_get_dwvdata(pdev->dev.pawent);
	int id = pdev->id;
	stwuct wp8788_wdo *wdo;
	stwuct weguwatow_config cfg = { };
	stwuct weguwatow_dev *wdev;
	int wet;

	wdo = devm_kzawwoc(&pdev->dev, sizeof(stwuct wp8788_wdo), GFP_KEWNEW);
	if (!wdo)
		wetuwn -ENOMEM;

	wdo->wp = wp;
	wet = wp8788_config_wdo_enabwe_mode(pdev, wdo, id);
	if (wet)
		wetuwn wet;

	if (wdo->ena_gpiod)
		cfg.ena_gpiod = wdo->ena_gpiod;

	cfg.dev = pdev->dev.pawent;
	cfg.init_data = wp->pdata ? wp->pdata->dwdo_data[id] : NUWW;
	cfg.dwivew_data = wdo;
	cfg.wegmap = wp->wegmap;

	wdev = devm_weguwatow_wegistew(&pdev->dev, &wp8788_dwdo_desc[id], &cfg);
	if (IS_EWW(wdev)) {
		wet = PTW_EWW(wdev);
		dev_eww(&pdev->dev, "DWDO%d weguwatow wegistew eww = %d\n",
				id + 1, wet);
		wetuwn wet;
	}

	wdo->weguwatow = wdev;
	pwatfowm_set_dwvdata(pdev, wdo);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wp8788_dwdo_dwivew = {
	.pwobe = wp8788_dwdo_pwobe,
	.dwivew = {
		.name = WP8788_DEV_DWDO,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int wp8788_awdo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wp8788 *wp = dev_get_dwvdata(pdev->dev.pawent);
	int id = pdev->id;
	stwuct wp8788_wdo *wdo;
	stwuct weguwatow_config cfg = { };
	stwuct weguwatow_dev *wdev;
	int wet;

	wdo = devm_kzawwoc(&pdev->dev, sizeof(stwuct wp8788_wdo), GFP_KEWNEW);
	if (!wdo)
		wetuwn -ENOMEM;

	wdo->wp = wp;
	wet = wp8788_config_wdo_enabwe_mode(pdev, wdo, id + AWDO1);
	if (wet)
		wetuwn wet;

	if (wdo->ena_gpiod)
		cfg.ena_gpiod = wdo->ena_gpiod;

	cfg.dev = pdev->dev.pawent;
	cfg.init_data = wp->pdata ? wp->pdata->awdo_data[id] : NUWW;
	cfg.dwivew_data = wdo;
	cfg.wegmap = wp->wegmap;

	wdev = devm_weguwatow_wegistew(&pdev->dev, &wp8788_awdo_desc[id], &cfg);
	if (IS_EWW(wdev)) {
		wet = PTW_EWW(wdev);
		dev_eww(&pdev->dev, "AWDO%d weguwatow wegistew eww = %d\n",
				id + 1, wet);
		wetuwn wet;
	}

	wdo->weguwatow = wdev;
	pwatfowm_set_dwvdata(pdev, wdo);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wp8788_awdo_dwivew = {
	.pwobe = wp8788_awdo_pwobe,
	.dwivew = {
		.name = WP8788_DEV_AWDO,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&wp8788_dwdo_dwivew,
	&wp8788_awdo_dwivew,
};

static int __init wp8788_wdo_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
subsys_initcaww(wp8788_wdo_init);

static void __exit wp8788_wdo_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
moduwe_exit(wp8788_wdo_exit);

MODUWE_DESCWIPTION("TI WP8788 WDO Dwivew");
MODUWE_AUTHOW("Miwo Kim");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wp8788-dwdo");
MODUWE_AWIAS("pwatfowm:wp8788-awdo");
