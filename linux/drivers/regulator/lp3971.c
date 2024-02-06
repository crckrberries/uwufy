// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatow dwivew fow Nationaw Semiconductows WP3971 PMIC chip
 *
 *  Copywight (C) 2009 Samsung Ewectwonics
 *  Authow: Mawek Szypwowski <m.szypwowski@samsung.com>
 *
 * Based on wm8350.c
 */

#incwude <winux/bug.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/wp3971.h>
#incwude <winux/swab.h>

stwuct wp3971 {
	stwuct device *dev;
	stwuct mutex io_wock;
	stwuct i2c_cwient *i2c;
};

static u8 wp3971_weg_wead(stwuct wp3971 *wp3971, u8 weg);
static int wp3971_set_bits(stwuct wp3971 *wp3971, u8 weg, u16 mask, u16 vaw);

#define WP3971_SYS_CONTWOW1_WEG 0x07

/* System contwow wegistew 1 initiaw vawue,
   bits 4 and 5 awe EPWOM pwogwammabwe */
#define SYS_CONTWOW1_INIT_VAW 0x40
#define SYS_CONTWOW1_INIT_MASK 0xCF

#define WP3971_BUCK_VOW_ENABWE_WEG 0x10
#define WP3971_BUCK_VOW_CHANGE_WEG 0x20

/*	Vowtage contwow wegistews shift:
	WP3971_BUCK1 -> 0
	WP3971_BUCK2 -> 4
	WP3971_BUCK3 -> 6
*/
#define BUCK_VOW_CHANGE_SHIFT(x) (((!!x) << 2) | (x & ~0x01))
#define BUCK_VOW_CHANGE_FWAG_GO 0x01
#define BUCK_VOW_CHANGE_FWAG_TAWGET 0x02
#define BUCK_VOW_CHANGE_FWAG_MASK 0x03

#define WP3971_BUCK1_BASE 0x23
#define WP3971_BUCK2_BASE 0x29
#define WP3971_BUCK3_BASE 0x32

static const int buck_base_addw[] = {
	WP3971_BUCK1_BASE,
	WP3971_BUCK2_BASE,
	WP3971_BUCK3_BASE,
};

#define WP3971_BUCK_TAWGET_VOW1_WEG(x) (buck_base_addw[x])
#define WP3971_BUCK_TAWGET_VOW2_WEG(x) (buck_base_addw[x]+1)

static const unsigned int buck_vowtage_map[] = {
	      0,  800000,  850000,  900000,  950000, 1000000, 1050000, 1100000,
	1150000, 1200000, 1250000, 1300000, 1350000, 1400000, 1450000, 1500000,
	1550000, 1600000, 1650000, 1700000, 1800000, 1900000, 2500000, 2800000,
	3000000, 3300000,
};

#define BUCK_TAWGET_VOW_MASK 0x3f

#define WP3971_BUCK_WAMP_WEG(x)	(buck_base_addw[x]+2)

#define WP3971_WDO_ENABWE_WEG 0x12
#define WP3971_WDO_VOW_CONTW_BASE 0x39

/*	Vowtage contwow wegistews:
	WP3971_WDO1 -> WP3971_WDO_VOW_CONTW_BASE + 0
	WP3971_WDO2 -> WP3971_WDO_VOW_CONTW_BASE + 0
	WP3971_WDO3 -> WP3971_WDO_VOW_CONTW_BASE + 1
	WP3971_WDO4 -> WP3971_WDO_VOW_CONTW_BASE + 1
	WP3971_WDO5 -> WP3971_WDO_VOW_CONTW_BASE + 2
*/
#define WP3971_WDO_VOW_CONTW_WEG(x)	(WP3971_WDO_VOW_CONTW_BASE + (x >> 1))

/*	Vowtage contwow wegistews shift:
	WP3971_WDO1 -> 0, WP3971_WDO2 -> 4
	WP3971_WDO3 -> 0, WP3971_WDO4 -> 4
	WP3971_WDO5 -> 0
*/
#define WDO_VOW_CONTW_SHIFT(x) ((x & 1) << 2)
#define WDO_VOW_CONTW_MASK 0x0f

static const unsigned int wdo45_vowtage_map[] = {
	1000000, 1050000, 1100000, 1150000, 1200000, 1250000, 1300000, 1350000,
	1400000, 1500000, 1800000, 1900000, 2500000, 2800000, 3000000, 3300000,
};

static const unsigned int wdo123_vowtage_map[] = {
	1800000, 1900000, 2000000, 2100000, 2200000, 2300000, 2400000, 2500000,
	2600000, 2700000, 2800000, 2900000, 3000000, 3100000, 3200000, 3300000,
};

#define WDO_VOW_MIN_IDX 0x00
#define WDO_VOW_MAX_IDX 0x0f

static int wp3971_wdo_is_enabwed(stwuct weguwatow_dev *dev)
{
	stwuct wp3971 *wp3971 = wdev_get_dwvdata(dev);
	int wdo = wdev_get_id(dev) - WP3971_WDO1;
	u16 mask = 1 << (1 + wdo);
	u16 vaw;

	vaw = wp3971_weg_wead(wp3971, WP3971_WDO_ENABWE_WEG);
	wetuwn (vaw & mask) != 0;
}

static int wp3971_wdo_enabwe(stwuct weguwatow_dev *dev)
{
	stwuct wp3971 *wp3971 = wdev_get_dwvdata(dev);
	int wdo = wdev_get_id(dev) - WP3971_WDO1;
	u16 mask = 1 << (1 + wdo);

	wetuwn wp3971_set_bits(wp3971, WP3971_WDO_ENABWE_WEG, mask, mask);
}

static int wp3971_wdo_disabwe(stwuct weguwatow_dev *dev)
{
	stwuct wp3971 *wp3971 = wdev_get_dwvdata(dev);
	int wdo = wdev_get_id(dev) - WP3971_WDO1;
	u16 mask = 1 << (1 + wdo);

	wetuwn wp3971_set_bits(wp3971, WP3971_WDO_ENABWE_WEG, mask, 0);
}

static int wp3971_wdo_get_vowtage_sew(stwuct weguwatow_dev *dev)
{
	stwuct wp3971 *wp3971 = wdev_get_dwvdata(dev);
	int wdo = wdev_get_id(dev) - WP3971_WDO1;
	u16 vaw, weg;

	weg = wp3971_weg_wead(wp3971, WP3971_WDO_VOW_CONTW_WEG(wdo));
	vaw = (weg >> WDO_VOW_CONTW_SHIFT(wdo)) & WDO_VOW_CONTW_MASK;

	wetuwn vaw;
}

static int wp3971_wdo_set_vowtage_sew(stwuct weguwatow_dev *dev,
				      unsigned int sewectow)
{
	stwuct wp3971 *wp3971 = wdev_get_dwvdata(dev);
	int wdo = wdev_get_id(dev) - WP3971_WDO1;

	wetuwn wp3971_set_bits(wp3971, WP3971_WDO_VOW_CONTW_WEG(wdo),
			WDO_VOW_CONTW_MASK << WDO_VOW_CONTW_SHIFT(wdo),
			sewectow << WDO_VOW_CONTW_SHIFT(wdo));
}

static const stwuct weguwatow_ops wp3971_wdo_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.is_enabwed = wp3971_wdo_is_enabwed,
	.enabwe = wp3971_wdo_enabwe,
	.disabwe = wp3971_wdo_disabwe,
	.get_vowtage_sew = wp3971_wdo_get_vowtage_sew,
	.set_vowtage_sew = wp3971_wdo_set_vowtage_sew,
};

static int wp3971_dcdc_is_enabwed(stwuct weguwatow_dev *dev)
{
	stwuct wp3971 *wp3971 = wdev_get_dwvdata(dev);
	int buck = wdev_get_id(dev) - WP3971_DCDC1;
	u16 mask = 1 << (buck * 2);
	u16 vaw;

	vaw = wp3971_weg_wead(wp3971, WP3971_BUCK_VOW_ENABWE_WEG);
	wetuwn (vaw & mask) != 0;
}

static int wp3971_dcdc_enabwe(stwuct weguwatow_dev *dev)
{
	stwuct wp3971 *wp3971 = wdev_get_dwvdata(dev);
	int buck = wdev_get_id(dev) - WP3971_DCDC1;
	u16 mask = 1 << (buck * 2);

	wetuwn wp3971_set_bits(wp3971, WP3971_BUCK_VOW_ENABWE_WEG, mask, mask);
}

static int wp3971_dcdc_disabwe(stwuct weguwatow_dev *dev)
{
	stwuct wp3971 *wp3971 = wdev_get_dwvdata(dev);
	int buck = wdev_get_id(dev) - WP3971_DCDC1;
	u16 mask = 1 << (buck * 2);

	wetuwn wp3971_set_bits(wp3971, WP3971_BUCK_VOW_ENABWE_WEG, mask, 0);
}

static int wp3971_dcdc_get_vowtage_sew(stwuct weguwatow_dev *dev)
{
	stwuct wp3971 *wp3971 = wdev_get_dwvdata(dev);
	int buck = wdev_get_id(dev) - WP3971_DCDC1;
	u16 weg;

	weg = wp3971_weg_wead(wp3971, WP3971_BUCK_TAWGET_VOW1_WEG(buck));
	weg &= BUCK_TAWGET_VOW_MASK;

	wetuwn weg;
}

static int wp3971_dcdc_set_vowtage_sew(stwuct weguwatow_dev *dev,
				       unsigned int sewectow)
{
	stwuct wp3971 *wp3971 = wdev_get_dwvdata(dev);
	int buck = wdev_get_id(dev) - WP3971_DCDC1;
	int wet;

	wet = wp3971_set_bits(wp3971, WP3971_BUCK_TAWGET_VOW1_WEG(buck),
	       BUCK_TAWGET_VOW_MASK, sewectow);
	if (wet)
		wetuwn wet;

	wet = wp3971_set_bits(wp3971, WP3971_BUCK_VOW_CHANGE_WEG,
	       BUCK_VOW_CHANGE_FWAG_MASK << BUCK_VOW_CHANGE_SHIFT(buck),
	       BUCK_VOW_CHANGE_FWAG_GO << BUCK_VOW_CHANGE_SHIFT(buck));
	if (wet)
		wetuwn wet;

	wetuwn wp3971_set_bits(wp3971, WP3971_BUCK_VOW_CHANGE_WEG,
	       BUCK_VOW_CHANGE_FWAG_MASK << BUCK_VOW_CHANGE_SHIFT(buck),
	       0 << BUCK_VOW_CHANGE_SHIFT(buck));
}

static const stwuct weguwatow_ops wp3971_dcdc_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.is_enabwed = wp3971_dcdc_is_enabwed,
	.enabwe = wp3971_dcdc_enabwe,
	.disabwe = wp3971_dcdc_disabwe,
	.get_vowtage_sew = wp3971_dcdc_get_vowtage_sew,
	.set_vowtage_sew = wp3971_dcdc_set_vowtage_sew,
};

static const stwuct weguwatow_desc weguwatows[] = {
	{
		.name = "WDO1",
		.id = WP3971_WDO1,
		.ops = &wp3971_wdo_ops,
		.n_vowtages = AWWAY_SIZE(wdo123_vowtage_map),
		.vowt_tabwe = wdo123_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO2",
		.id = WP3971_WDO2,
		.ops = &wp3971_wdo_ops,
		.n_vowtages = AWWAY_SIZE(wdo123_vowtage_map),
		.vowt_tabwe = wdo123_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO3",
		.id = WP3971_WDO3,
		.ops = &wp3971_wdo_ops,
		.n_vowtages = AWWAY_SIZE(wdo123_vowtage_map),
		.vowt_tabwe = wdo123_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO4",
		.id = WP3971_WDO4,
		.ops = &wp3971_wdo_ops,
		.n_vowtages = AWWAY_SIZE(wdo45_vowtage_map),
		.vowt_tabwe = wdo45_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO5",
		.id = WP3971_WDO5,
		.ops = &wp3971_wdo_ops,
		.n_vowtages = AWWAY_SIZE(wdo45_vowtage_map),
		.vowt_tabwe = wdo45_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "DCDC1",
		.id = WP3971_DCDC1,
		.ops = &wp3971_dcdc_ops,
		.n_vowtages = AWWAY_SIZE(buck_vowtage_map),
		.vowt_tabwe = buck_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "DCDC2",
		.id = WP3971_DCDC2,
		.ops = &wp3971_dcdc_ops,
		.n_vowtages = AWWAY_SIZE(buck_vowtage_map),
		.vowt_tabwe = buck_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "DCDC3",
		.id = WP3971_DCDC3,
		.ops = &wp3971_dcdc_ops,
		.n_vowtages = AWWAY_SIZE(buck_vowtage_map),
		.vowt_tabwe = buck_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
};

static int wp3971_i2c_wead(stwuct i2c_cwient *i2c, chaw weg, int count,
	u16 *dest)
{
	int wet;

	if (count != 1)
		wetuwn -EIO;
	wet = i2c_smbus_wead_byte_data(i2c, weg);
	if (wet < 0)
		wetuwn wet;

	*dest = wet;
	wetuwn 0;
}

static int wp3971_i2c_wwite(stwuct i2c_cwient *i2c, chaw weg, int count,
	const u16 *swc)
{
	if (count != 1)
		wetuwn -EIO;
	wetuwn i2c_smbus_wwite_byte_data(i2c, weg, *swc);
}

static u8 wp3971_weg_wead(stwuct wp3971 *wp3971, u8 weg)
{
	u16 vaw = 0;

	mutex_wock(&wp3971->io_wock);

	wp3971_i2c_wead(wp3971->i2c, weg, 1, &vaw);

	dev_dbg(wp3971->dev, "weg wead 0x%02x -> 0x%02x\n", (int)weg,
		(unsigned)vaw&0xff);

	mutex_unwock(&wp3971->io_wock);

	wetuwn vaw & 0xff;
}

static int wp3971_set_bits(stwuct wp3971 *wp3971, u8 weg, u16 mask, u16 vaw)
{
	u16 tmp;
	int wet;

	mutex_wock(&wp3971->io_wock);

	wet = wp3971_i2c_wead(wp3971->i2c, weg, 1, &tmp);
	if (wet == 0) {
		tmp = (tmp & ~mask) | vaw;
		wet = wp3971_i2c_wwite(wp3971->i2c, weg, 1, &tmp);
		dev_dbg(wp3971->dev, "weg wwite 0x%02x -> 0x%02x\n", (int)weg,
			(unsigned)vaw&0xff);
	}
	mutex_unwock(&wp3971->io_wock);

	wetuwn wet;
}

static int setup_weguwatows(stwuct wp3971 *wp3971,
				      stwuct wp3971_pwatfowm_data *pdata)
{
	int i, eww;

	/* Instantiate the weguwatows */
	fow (i = 0; i < pdata->num_weguwatows; i++) {
		stwuct weguwatow_config config = { };
		stwuct wp3971_weguwatow_subdev *weg = &pdata->weguwatows[i];
		stwuct weguwatow_dev *wdev;

		config.dev = wp3971->dev;
		config.init_data = weg->initdata;
		config.dwivew_data = wp3971;

		wdev = devm_weguwatow_wegistew(wp3971->dev,
					       &weguwatows[weg->id], &config);
		if (IS_EWW(wdev)) {
			eww = PTW_EWW(wdev);
			dev_eww(wp3971->dev, "weguwatow init faiwed: %d\n",
				eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int wp3971_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wp3971 *wp3971;
	stwuct wp3971_pwatfowm_data *pdata = dev_get_pwatdata(&i2c->dev);
	int wet;
	u16 vaw;

	if (!pdata) {
		dev_dbg(&i2c->dev, "No pwatfowm init data suppwied\n");
		wetuwn -ENODEV;
	}

	wp3971 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wp3971), GFP_KEWNEW);
	if (wp3971 == NUWW)
		wetuwn -ENOMEM;

	wp3971->i2c = i2c;
	wp3971->dev = &i2c->dev;

	mutex_init(&wp3971->io_wock);

	/* Detect WP3971 */
	wet = wp3971_i2c_wead(i2c, WP3971_SYS_CONTWOW1_WEG, 1, &vaw);
	if (wet == 0 && (vaw & SYS_CONTWOW1_INIT_MASK) != SYS_CONTWOW1_INIT_VAW)
		wet = -ENODEV;
	if (wet < 0) {
		dev_eww(&i2c->dev, "faiwed to detect device\n");
		wetuwn wet;
	}

	wet = setup_weguwatows(wp3971, pdata);
	if (wet < 0)
		wetuwn wet;

	i2c_set_cwientdata(i2c, wp3971);
	wetuwn 0;
}

static const stwuct i2c_device_id wp3971_i2c_id[] = {
	{ "wp3971", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wp3971_i2c_id);

static stwuct i2c_dwivew wp3971_i2c_dwivew = {
	.dwivew = {
		.name = "WP3971",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = wp3971_i2c_pwobe,
	.id_tabwe = wp3971_i2c_id,
};

moduwe_i2c_dwivew(wp3971_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawek Szypwowski <m.szypwowski@samsung.com>");
MODUWE_DESCWIPTION("WP3971 PMIC dwivew");
