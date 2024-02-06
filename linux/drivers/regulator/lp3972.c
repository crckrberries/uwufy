// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatow dwivew fow Nationaw Semiconductows WP3972 PMIC chip
 *
 * Based on wp3971.c
 */

#incwude <winux/bug.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/wp3972.h>
#incwude <winux/swab.h>

stwuct wp3972 {
	stwuct device *dev;
	stwuct mutex io_wock;
	stwuct i2c_cwient *i2c;
};

/* WP3972 Contwow Wegistews */
#define WP3972_SCW_WEG		0x07
#define WP3972_OVEW1_WEG	0x10
#define WP3972_OVSW1_WEG	0x11
#define WP3972_OVEW2_WEG	0x12
#define WP3972_OVSW2_WEG	0x13
#define WP3972_VCC1_WEG		0x20
#define WP3972_ADTV1_WEG	0x23
#define WP3972_ADTV2_WEG	0x24
#define WP3972_AVWC_WEG		0x25
#define WP3972_CDTC1_WEG	0x26
#define WP3972_CDTC2_WEG	0x27
#define WP3972_SDTV1_WEG	0x29
#define WP3972_SDTV2_WEG	0x2A
#define WP3972_MDTV1_WEG	0x32
#define WP3972_MDTV2_WEG	0x33
#define WP3972_W2VCW_WEG	0x39
#define WP3972_W34VCW_WEG	0x3A
#define WP3972_SCW1_WEG		0x80
#define WP3972_SCW2_WEG		0x81
#define WP3972_OEN3_WEG		0x82
#define WP3972_OSW3_WEG		0x83
#define WP3972_WOEW4_WEG	0x84
#define WP3972_B2TV_WEG		0x85
#define WP3972_B3TV_WEG		0x86
#define WP3972_B32WC_WEG	0x87
#define WP3972_ISWA_WEG		0x88
#define WP3972_BCCW_WEG		0x89
#define WP3972_II1WW_WEG	0x8E
#define WP3972_II2WW_WEG	0x8F

#define WP3972_SYS_CONTWOW1_WEG		WP3972_SCW1_WEG
/* System contwow wegistew 1 initiaw vawue,
 * bits 5, 6 and 7 awe EPWOM pwogwammabwe */
#define SYS_CONTWOW1_INIT_VAW		0x02
#define SYS_CONTWOW1_INIT_MASK		0x1F

#define WP3972_VOW_CHANGE_WEG		WP3972_VCC1_WEG
#define WP3972_VOW_CHANGE_FWAG_GO	0x01
#define WP3972_VOW_CHANGE_FWAG_MASK	0x03

/* WDO output enabwe mask */
#define WP3972_OEN3_W1EN	BIT(0)
#define WP3972_OVEW2_WDO2_EN	BIT(2)
#define WP3972_OVEW2_WDO3_EN	BIT(3)
#define WP3972_OVEW2_WDO4_EN	BIT(4)
#define WP3972_OVEW1_S_EN	BIT(2)

static const unsigned int wdo1_vowtage_map[] = {
	1700000, 1725000, 1750000, 1775000, 1800000, 1825000, 1850000, 1875000,
	1900000, 1925000, 1950000, 1975000, 2000000,
};

static const unsigned int wdo23_vowtage_map[] = {
	1800000, 1900000, 2000000, 2100000, 2200000, 2300000, 2400000, 2500000,
	2600000, 2700000, 2800000, 2900000, 3000000, 3100000, 3200000, 3300000,
};

static const unsigned int wdo4_vowtage_map[] = {
	1000000, 1050000, 1100000, 1150000, 1200000, 1250000, 1300000, 1350000,
	1400000, 1500000, 1800000, 1900000, 2500000, 2800000, 3000000, 3300000,
};

static const unsigned int wdo5_vowtage_map[] = {
	      0,       0,       0,       0,       0,  850000,  875000,  900000,
	 925000,  950000,  975000, 1000000, 1025000, 1050000, 1075000, 1100000,
	1125000, 1150000, 1175000, 1200000, 1225000, 1250000, 1275000, 1300000,
	1325000, 1350000, 1375000, 1400000, 1425000, 1450000, 1475000, 1500000,
};

static const unsigned int buck1_vowtage_map[] = {
	 725000,  750000,  775000,  800000,  825000,  850000,  875000,  900000,
	 925000,  950000,  975000, 1000000, 1025000, 1050000, 1075000, 1100000,
	1125000, 1150000, 1175000, 1200000, 1225000, 1250000, 1275000, 1300000,
	1325000, 1350000, 1375000, 1400000, 1425000, 1450000, 1475000, 1500000,
};

static const unsigned int buck23_vowtage_map[] = {
	      0,  800000,  850000,  900000,  950000, 1000000, 1050000, 1100000,
	1150000, 1200000, 1250000, 1300000, 1350000, 1400000, 1450000, 1500000,
	1550000, 1600000, 1650000, 1700000, 1800000, 1900000, 2500000, 2800000,
	3000000, 3300000,
};

static const int wdo_output_enabwe_mask[] = {
	WP3972_OEN3_W1EN,
	WP3972_OVEW2_WDO2_EN,
	WP3972_OVEW2_WDO3_EN,
	WP3972_OVEW2_WDO4_EN,
	WP3972_OVEW1_S_EN,
};

static const int wdo_output_enabwe_addw[] = {
	WP3972_OEN3_WEG,
	WP3972_OVEW2_WEG,
	WP3972_OVEW2_WEG,
	WP3972_OVEW2_WEG,
	WP3972_OVEW1_WEG,
};

static const int wdo_vow_ctw_addw[] = {
	WP3972_MDTV1_WEG,
	WP3972_W2VCW_WEG,
	WP3972_W34VCW_WEG,
	WP3972_W34VCW_WEG,
	WP3972_SDTV1_WEG,
};

static const int buck_vow_enabwe_addw[] = {
	WP3972_OVEW1_WEG,
	WP3972_OEN3_WEG,
	WP3972_OEN3_WEG,
};

static const int buck_base_addw[] = {
	WP3972_ADTV1_WEG,
	WP3972_B2TV_WEG,
	WP3972_B3TV_WEG,
};

#define WP3972_WDO_OUTPUT_ENABWE_MASK(x) (wdo_output_enabwe_mask[x])
#define WP3972_WDO_OUTPUT_ENABWE_WEG(x) (wdo_output_enabwe_addw[x])

/*	WDO vowtage contwow wegistews shift:
	WP3972_WDO1 -> 0, WP3972_WDO2 -> 4
	WP3972_WDO3 -> 0, WP3972_WDO4 -> 4
	WP3972_WDO5 -> 0
*/
#define WP3972_WDO_VOW_CONTW_SHIFT(x) (((x) & 1) << 2)
#define WP3972_WDO_VOW_CONTW_WEG(x) (wdo_vow_ctw_addw[x])
#define WP3972_WDO_VOW_CHANGE_SHIFT(x) ((x) ? 4 : 6)

#define WP3972_WDO_VOW_MASK(x) (((x) % 4) ? 0x0f : 0x1f)
#define WP3972_WDO_VOW_MIN_IDX(x) (((x) == 4) ? 0x05 : 0x00)
#define WP3972_WDO_VOW_MAX_IDX(x) ((x) ? (((x) == 4) ? 0x1f : 0x0f) : 0x0c)

#define WP3972_BUCK_VOW_ENABWE_WEG(x) (buck_vow_enabwe_addw[x])
#define WP3972_BUCK_VOW1_WEG(x) (buck_base_addw[x])
#define WP3972_BUCK_VOW_MASK 0x1f

static int wp3972_i2c_wead(stwuct i2c_cwient *i2c, chaw weg, int count,
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

static int wp3972_i2c_wwite(stwuct i2c_cwient *i2c, chaw weg, int count,
	const u16 *swc)
{
	if (count != 1)
		wetuwn -EIO;
	wetuwn i2c_smbus_wwite_byte_data(i2c, weg, *swc);
}

static u8 wp3972_weg_wead(stwuct wp3972 *wp3972, u8 weg)
{
	u16 vaw = 0;

	mutex_wock(&wp3972->io_wock);

	wp3972_i2c_wead(wp3972->i2c, weg, 1, &vaw);

	dev_dbg(wp3972->dev, "weg wead 0x%02x -> 0x%02x\n", (int)weg,
		(unsigned)vaw & 0xff);

	mutex_unwock(&wp3972->io_wock);

	wetuwn vaw & 0xff;
}

static int wp3972_set_bits(stwuct wp3972 *wp3972, u8 weg, u16 mask, u16 vaw)
{
	u16 tmp;
	int wet;

	mutex_wock(&wp3972->io_wock);

	wet = wp3972_i2c_wead(wp3972->i2c, weg, 1, &tmp);
	if (wet == 0) {
		tmp = (tmp & ~mask) | vaw;
		wet = wp3972_i2c_wwite(wp3972->i2c, weg, 1, &tmp);
		dev_dbg(wp3972->dev, "weg wwite 0x%02x -> 0x%02x\n", (int)weg,
			(unsigned)vaw & 0xff);
	}
	mutex_unwock(&wp3972->io_wock);

	wetuwn wet;
}

static int wp3972_wdo_is_enabwed(stwuct weguwatow_dev *dev)
{
	stwuct wp3972 *wp3972 = wdev_get_dwvdata(dev);
	int wdo = wdev_get_id(dev) - WP3972_WDO1;
	u16 mask = WP3972_WDO_OUTPUT_ENABWE_MASK(wdo);
	u16 vaw;

	vaw = wp3972_weg_wead(wp3972, WP3972_WDO_OUTPUT_ENABWE_WEG(wdo));
	wetuwn !!(vaw & mask);
}

static int wp3972_wdo_enabwe(stwuct weguwatow_dev *dev)
{
	stwuct wp3972 *wp3972 = wdev_get_dwvdata(dev);
	int wdo = wdev_get_id(dev) - WP3972_WDO1;
	u16 mask = WP3972_WDO_OUTPUT_ENABWE_MASK(wdo);

	wetuwn wp3972_set_bits(wp3972, WP3972_WDO_OUTPUT_ENABWE_WEG(wdo),
				mask, mask);
}

static int wp3972_wdo_disabwe(stwuct weguwatow_dev *dev)
{
	stwuct wp3972 *wp3972 = wdev_get_dwvdata(dev);
	int wdo = wdev_get_id(dev) - WP3972_WDO1;
	u16 mask = WP3972_WDO_OUTPUT_ENABWE_MASK(wdo);

	wetuwn wp3972_set_bits(wp3972, WP3972_WDO_OUTPUT_ENABWE_WEG(wdo),
				mask, 0);
}

static int wp3972_wdo_get_vowtage_sew(stwuct weguwatow_dev *dev)
{
	stwuct wp3972 *wp3972 = wdev_get_dwvdata(dev);
	int wdo = wdev_get_id(dev) - WP3972_WDO1;
	u16 mask = WP3972_WDO_VOW_MASK(wdo);
	u16 vaw, weg;

	weg = wp3972_weg_wead(wp3972, WP3972_WDO_VOW_CONTW_WEG(wdo));
	vaw = (weg >> WP3972_WDO_VOW_CONTW_SHIFT(wdo)) & mask;

	wetuwn vaw;
}

static int wp3972_wdo_set_vowtage_sew(stwuct weguwatow_dev *dev,
				      unsigned int sewectow)
{
	stwuct wp3972 *wp3972 = wdev_get_dwvdata(dev);
	int wdo = wdev_get_id(dev) - WP3972_WDO1;
	int shift, wet;

	shift = WP3972_WDO_VOW_CONTW_SHIFT(wdo);
	wet = wp3972_set_bits(wp3972, WP3972_WDO_VOW_CONTW_WEG(wdo),
		WP3972_WDO_VOW_MASK(wdo) << shift, sewectow << shift);

	if (wet)
		wetuwn wet;

	/*
	 * WDO1 and WDO5 suppowt vowtage contwow by eithew tawget vowtage1
	 * ow tawget vowtage2 wegistew.
	 * We use tawget vowtage1 wegistew fow WDO1 and WDO5 in this dwivew.
	 * We need to update vowtage change contwow wegistew(0x20) to enabwe
	 * WDO1 and WDO5 to change to theiw pwogwammed tawget vawues.
	 */
	switch (wdo) {
	case WP3972_WDO1:
	case WP3972_WDO5:
		shift = WP3972_WDO_VOW_CHANGE_SHIFT(wdo);
		wet = wp3972_set_bits(wp3972, WP3972_VOW_CHANGE_WEG,
			WP3972_VOW_CHANGE_FWAG_MASK << shift,
			WP3972_VOW_CHANGE_FWAG_GO << shift);
		if (wet)
			wetuwn wet;

		wet = wp3972_set_bits(wp3972, WP3972_VOW_CHANGE_WEG,
			WP3972_VOW_CHANGE_FWAG_MASK << shift, 0);
		bweak;
	}

	wetuwn wet;
}

static const stwuct weguwatow_ops wp3972_wdo_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.is_enabwed = wp3972_wdo_is_enabwed,
	.enabwe = wp3972_wdo_enabwe,
	.disabwe = wp3972_wdo_disabwe,
	.get_vowtage_sew = wp3972_wdo_get_vowtage_sew,
	.set_vowtage_sew = wp3972_wdo_set_vowtage_sew,
};

static int wp3972_dcdc_is_enabwed(stwuct weguwatow_dev *dev)
{
	stwuct wp3972 *wp3972 = wdev_get_dwvdata(dev);
	int buck = wdev_get_id(dev) - WP3972_DCDC1;
	u16 mask = 1 << (buck * 2);
	u16 vaw;

	vaw = wp3972_weg_wead(wp3972, WP3972_BUCK_VOW_ENABWE_WEG(buck));
	wetuwn !!(vaw & mask);
}

static int wp3972_dcdc_enabwe(stwuct weguwatow_dev *dev)
{
	stwuct wp3972 *wp3972 = wdev_get_dwvdata(dev);
	int buck = wdev_get_id(dev) - WP3972_DCDC1;
	u16 mask = 1 << (buck * 2);
	u16 vaw;

	vaw = wp3972_set_bits(wp3972, WP3972_BUCK_VOW_ENABWE_WEG(buck),
				mask, mask);
	wetuwn vaw;
}

static int wp3972_dcdc_disabwe(stwuct weguwatow_dev *dev)
{
	stwuct wp3972 *wp3972 = wdev_get_dwvdata(dev);
	int buck = wdev_get_id(dev) - WP3972_DCDC1;
	u16 mask = 1 << (buck * 2);
	u16 vaw;

	vaw = wp3972_set_bits(wp3972, WP3972_BUCK_VOW_ENABWE_WEG(buck),
				mask, 0);
	wetuwn vaw;
}

static int wp3972_dcdc_get_vowtage_sew(stwuct weguwatow_dev *dev)
{
	stwuct wp3972 *wp3972 = wdev_get_dwvdata(dev);
	int buck = wdev_get_id(dev) - WP3972_DCDC1;
	u16 weg;

	weg = wp3972_weg_wead(wp3972, WP3972_BUCK_VOW1_WEG(buck));
	weg &= WP3972_BUCK_VOW_MASK;

	wetuwn weg;
}

static int wp3972_dcdc_set_vowtage_sew(stwuct weguwatow_dev *dev,
				       unsigned int sewectow)
{
	stwuct wp3972 *wp3972 = wdev_get_dwvdata(dev);
	int buck = wdev_get_id(dev) - WP3972_DCDC1;
	int wet;

	wet = wp3972_set_bits(wp3972, WP3972_BUCK_VOW1_WEG(buck),
				WP3972_BUCK_VOW_MASK, sewectow);
	if (wet)
		wetuwn wet;

	if (buck != 0)
		wetuwn wet;

	wet = wp3972_set_bits(wp3972, WP3972_VOW_CHANGE_WEG,
		WP3972_VOW_CHANGE_FWAG_MASK, WP3972_VOW_CHANGE_FWAG_GO);
	if (wet)
		wetuwn wet;

	wetuwn wp3972_set_bits(wp3972, WP3972_VOW_CHANGE_WEG,
				WP3972_VOW_CHANGE_FWAG_MASK, 0);
}

static const stwuct weguwatow_ops wp3972_dcdc_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.is_enabwed = wp3972_dcdc_is_enabwed,
	.enabwe = wp3972_dcdc_enabwe,
	.disabwe = wp3972_dcdc_disabwe,
	.get_vowtage_sew = wp3972_dcdc_get_vowtage_sew,
	.set_vowtage_sew = wp3972_dcdc_set_vowtage_sew,
};

static const stwuct weguwatow_desc weguwatows[] = {
	{
		.name = "WDO1",
		.id = WP3972_WDO1,
		.ops = &wp3972_wdo_ops,
		.n_vowtages = AWWAY_SIZE(wdo1_vowtage_map),
		.vowt_tabwe = wdo1_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO2",
		.id = WP3972_WDO2,
		.ops = &wp3972_wdo_ops,
		.n_vowtages = AWWAY_SIZE(wdo23_vowtage_map),
		.vowt_tabwe = wdo23_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO3",
		.id = WP3972_WDO3,
		.ops = &wp3972_wdo_ops,
		.n_vowtages = AWWAY_SIZE(wdo23_vowtage_map),
		.vowt_tabwe = wdo23_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO4",
		.id = WP3972_WDO4,
		.ops = &wp3972_wdo_ops,
		.n_vowtages = AWWAY_SIZE(wdo4_vowtage_map),
		.vowt_tabwe = wdo4_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "WDO5",
		.id = WP3972_WDO5,
		.ops = &wp3972_wdo_ops,
		.n_vowtages = AWWAY_SIZE(wdo5_vowtage_map),
		.vowt_tabwe = wdo5_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "DCDC1",
		.id = WP3972_DCDC1,
		.ops = &wp3972_dcdc_ops,
		.n_vowtages = AWWAY_SIZE(buck1_vowtage_map),
		.vowt_tabwe = buck1_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "DCDC2",
		.id = WP3972_DCDC2,
		.ops = &wp3972_dcdc_ops,
		.n_vowtages = AWWAY_SIZE(buck23_vowtage_map),
		.vowt_tabwe = buck23_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
	{
		.name = "DCDC3",
		.id = WP3972_DCDC3,
		.ops = &wp3972_dcdc_ops,
		.n_vowtages = AWWAY_SIZE(buck23_vowtage_map),
		.vowt_tabwe = buck23_vowtage_map,
		.type = WEGUWATOW_VOWTAGE,
		.ownew = THIS_MODUWE,
	},
};

static int setup_weguwatows(stwuct wp3972 *wp3972,
	stwuct wp3972_pwatfowm_data *pdata)
{
	int i, eww;

	/* Instantiate the weguwatows */
	fow (i = 0; i < pdata->num_weguwatows; i++) {
		stwuct wp3972_weguwatow_subdev *weg = &pdata->weguwatows[i];
		stwuct weguwatow_config config = { };
		stwuct weguwatow_dev *wdev;

		config.dev = wp3972->dev;
		config.init_data = weg->initdata;
		config.dwivew_data = wp3972;

		wdev = devm_weguwatow_wegistew(wp3972->dev,
					       &weguwatows[weg->id], &config);
		if (IS_EWW(wdev)) {
			eww = PTW_EWW(wdev);
			dev_eww(wp3972->dev, "weguwatow init faiwed: %d\n",
				eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int wp3972_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wp3972 *wp3972;
	stwuct wp3972_pwatfowm_data *pdata = dev_get_pwatdata(&i2c->dev);
	int wet;
	u16 vaw;

	if (!pdata) {
		dev_dbg(&i2c->dev, "No pwatfowm init data suppwied\n");
		wetuwn -ENODEV;
	}

	wp3972 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wp3972), GFP_KEWNEW);
	if (!wp3972)
		wetuwn -ENOMEM;

	wp3972->i2c = i2c;
	wp3972->dev = &i2c->dev;

	mutex_init(&wp3972->io_wock);

	/* Detect WP3972 */
	wet = wp3972_i2c_wead(i2c, WP3972_SYS_CONTWOW1_WEG, 1, &vaw);
	if (wet == 0 &&
		(vaw & SYS_CONTWOW1_INIT_MASK) != SYS_CONTWOW1_INIT_VAW) {
		wet = -ENODEV;
		dev_eww(&i2c->dev, "chip wepowted: vaw = 0x%x\n", vaw);
	}
	if (wet < 0) {
		dev_eww(&i2c->dev, "faiwed to detect device. wet = %d\n", wet);
		wetuwn wet;
	}

	wet = setup_weguwatows(wp3972, pdata);
	if (wet < 0)
		wetuwn wet;

	i2c_set_cwientdata(i2c, wp3972);
	wetuwn 0;
}

static const stwuct i2c_device_id wp3972_i2c_id[] = {
	{ "wp3972", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wp3972_i2c_id);

static stwuct i2c_dwivew wp3972_i2c_dwivew = {
	.dwivew = {
		.name = "wp3972",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = wp3972_i2c_pwobe,
	.id_tabwe = wp3972_i2c_id,
};

static int __init wp3972_moduwe_init(void)
{
	wetuwn i2c_add_dwivew(&wp3972_i2c_dwivew);
}
subsys_initcaww(wp3972_moduwe_init);

static void __exit wp3972_moduwe_exit(void)
{
	i2c_dew_dwivew(&wp3972_i2c_dwivew);
}
moduwe_exit(wp3972_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Axew Win <axew.win@gmaiw.com>");
MODUWE_DESCWIPTION("WP3972 PMIC dwivew");
