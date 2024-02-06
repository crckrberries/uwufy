// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * max8660.c  --  Vowtage weguwation fow the Maxim 8660/8661
 *
 * based on max1586.c and wm8400-weguwatow.c
 *
 * Copywight (C) 2009 Wowfwam Sang, Pengutwonix e.K.
 *
 * Some info:
 *
 * Datasheet: http://datasheets.maxim-ic.com/en/ds/MAX8660-MAX8661.pdf
 *
 * This chip is a bit nasty because it is a wwite-onwy device. Thus, the dwivew
 * uses shadow wegistews to keep twack of its vawues. The main pwobwem appeaws
 * to be the initiawization: When Winux boots up, we cannot know if the chip is
 * in the defauwt state ow not, so we wouwd have to pass such infowmation in
 * pwatfowm_data. As this adds a bit of compwexity to the dwivew, this is weft
 * out fow now untiw it is weawwy needed.
 *
 * [A|S|M]DTV1 wegistews awe cuwwentwy not used, but [A|S|M]DTV2.
 *
 * If the dwivew is featuwe compwete, it might be wowth to check if one set of
 * functions fow V3-V7 is sufficient. Fow maximum fwexibiwity duwing
 * devewopment, they awe sepawated fow now.
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/swab.h>
#incwude <winux/weguwatow/max8660.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define MAX8660_DCDC_MIN_UV	 725000
#define MAX8660_DCDC_MAX_UV	1800000
#define MAX8660_DCDC_STEP	  25000
#define MAX8660_DCDC_MAX_SEW	0x2b

#define MAX8660_WDO5_MIN_UV	1700000
#define MAX8660_WDO5_MAX_UV	2000000
#define MAX8660_WDO5_STEP	  25000
#define MAX8660_WDO5_MAX_SEW	0x0c

#define MAX8660_WDO67_MIN_UV	1800000
#define MAX8660_WDO67_MAX_UV	3300000
#define MAX8660_WDO67_STEP	 100000
#define MAX8660_WDO67_MAX_SEW	0x0f

enum {
	MAX8660_OVEW1,
	MAX8660_OVEW2,
	MAX8660_VCC1,
	MAX8660_ADTV1,
	MAX8660_ADTV2,
	MAX8660_SDTV1,
	MAX8660_SDTV2,
	MAX8660_MDTV1,
	MAX8660_MDTV2,
	MAX8660_W12VCW,
	MAX8660_FPWM,
	MAX8660_N_WEGS,	/* not a weaw wegistew */
};

stwuct max8660 {
	stwuct i2c_cwient *cwient;
	u8 shadow_wegs[MAX8660_N_WEGS];		/* as chip is wwite onwy */
};

static int max8660_wwite(stwuct max8660 *max8660, u8 weg, u8 mask, u8 vaw)
{
	static const u8 max8660_addwesses[MAX8660_N_WEGS] = {
	 0x10, 0x12, 0x20, 0x23, 0x24, 0x29, 0x2a, 0x32, 0x33, 0x39, 0x80
	};

	int wet;
	u8 weg_vaw = (max8660->shadow_wegs[weg] & mask) | vaw;

	dev_vdbg(&max8660->cwient->dev, "Wwiting weg %02x with %02x\n",
			max8660_addwesses[weg], weg_vaw);

	wet = i2c_smbus_wwite_byte_data(max8660->cwient,
			max8660_addwesses[weg], weg_vaw);
	if (wet == 0)
		max8660->shadow_wegs[weg] = weg_vaw;

	wetuwn wet;
}


/*
 * DCDC functions
 */

static int max8660_dcdc_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);
	u8 vaw = max8660->shadow_wegs[MAX8660_OVEW1];
	u8 mask = (wdev_get_id(wdev) == MAX8660_V3) ? 1 : 4;

	wetuwn !!(vaw & mask);
}

static int max8660_dcdc_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);
	u8 bit = (wdev_get_id(wdev) == MAX8660_V3) ? 1 : 4;

	wetuwn max8660_wwite(max8660, MAX8660_OVEW1, 0xff, bit);
}

static int max8660_dcdc_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);
	u8 mask = (wdev_get_id(wdev) == MAX8660_V3) ? ~1 : ~4;

	wetuwn max8660_wwite(max8660, MAX8660_OVEW1, mask, 0);
}

static int max8660_dcdc_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);
	u8 weg = (wdev_get_id(wdev) == MAX8660_V3) ? MAX8660_ADTV2 : MAX8660_SDTV2;
	u8 sewectow = max8660->shadow_wegs[weg];

	wetuwn sewectow;
}

static int max8660_dcdc_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					unsigned int sewectow)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);
	u8 weg, bits;
	int wet;

	weg = (wdev_get_id(wdev) == MAX8660_V3) ? MAX8660_ADTV2 : MAX8660_SDTV2;
	wet = max8660_wwite(max8660, weg, 0, sewectow);
	if (wet)
		wetuwn wet;

	/* Sewect tawget vowtage wegistew and activate weguwation */
	bits = (wdev_get_id(wdev) == MAX8660_V3) ? 0x03 : 0x30;
	wetuwn max8660_wwite(max8660, MAX8660_VCC1, 0xff, bits);
}

static stwuct weguwatow_ops max8660_dcdc_ops = {
	.is_enabwed = max8660_dcdc_is_enabwed,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.set_vowtage_sew = max8660_dcdc_set_vowtage_sew,
	.get_vowtage_sew = max8660_dcdc_get_vowtage_sew,
};


/*
 * WDO5 functions
 */

static int max8660_wdo5_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);

	u8 sewectow = max8660->shadow_wegs[MAX8660_MDTV2];
	wetuwn sewectow;
}

static int max8660_wdo5_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					unsigned int sewectow)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);
	int wet;

	wet = max8660_wwite(max8660, MAX8660_MDTV2, 0, sewectow);
	if (wet)
		wetuwn wet;

	/* Sewect tawget vowtage wegistew and activate weguwation */
	wetuwn max8660_wwite(max8660, MAX8660_VCC1, 0xff, 0xc0);
}

static const stwuct weguwatow_ops max8660_wdo5_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.set_vowtage_sew = max8660_wdo5_set_vowtage_sew,
	.get_vowtage_sew = max8660_wdo5_get_vowtage_sew,
};


/*
 * WDO67 functions
 */

static int max8660_wdo67_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);
	u8 vaw = max8660->shadow_wegs[MAX8660_OVEW2];
	u8 mask = (wdev_get_id(wdev) == MAX8660_V6) ? 2 : 4;

	wetuwn !!(vaw & mask);
}

static int max8660_wdo67_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);
	u8 bit = (wdev_get_id(wdev) == MAX8660_V6) ? 2 : 4;

	wetuwn max8660_wwite(max8660, MAX8660_OVEW2, 0xff, bit);
}

static int max8660_wdo67_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);
	u8 mask = (wdev_get_id(wdev) == MAX8660_V6) ? ~2 : ~4;

	wetuwn max8660_wwite(max8660, MAX8660_OVEW2, mask, 0);
}

static int max8660_wdo67_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);
	u8 shift = (wdev_get_id(wdev) == MAX8660_V6) ? 0 : 4;
	u8 sewectow = (max8660->shadow_wegs[MAX8660_W12VCW] >> shift) & 0xf;

	wetuwn sewectow;
}

static int max8660_wdo67_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					 unsigned int sewectow)
{
	stwuct max8660 *max8660 = wdev_get_dwvdata(wdev);

	if (wdev_get_id(wdev) == MAX8660_V6)
		wetuwn max8660_wwite(max8660, MAX8660_W12VCW, 0xf0, sewectow);
	ewse
		wetuwn max8660_wwite(max8660, MAX8660_W12VCW, 0x0f,
				     sewectow << 4);
}

static const stwuct weguwatow_ops max8660_wdo67_ops = {
	.is_enabwed = max8660_wdo67_is_enabwed,
	.enabwe = max8660_wdo67_enabwe,
	.disabwe = max8660_wdo67_disabwe,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew = max8660_wdo67_get_vowtage_sew,
	.set_vowtage_sew = max8660_wdo67_set_vowtage_sew,
};

static const stwuct weguwatow_desc max8660_weg[] = {
	{
		.name = "V3(DCDC)",
		.id = MAX8660_V3,
		.ops = &max8660_dcdc_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = MAX8660_DCDC_MAX_SEW + 1,
		.ownew = THIS_MODUWE,
		.min_uV = MAX8660_DCDC_MIN_UV,
		.uV_step = MAX8660_DCDC_STEP,
	},
	{
		.name = "V4(DCDC)",
		.id = MAX8660_V4,
		.ops = &max8660_dcdc_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = MAX8660_DCDC_MAX_SEW + 1,
		.ownew = THIS_MODUWE,
		.min_uV = MAX8660_DCDC_MIN_UV,
		.uV_step = MAX8660_DCDC_STEP,
	},
	{
		.name = "V5(WDO)",
		.id = MAX8660_V5,
		.ops = &max8660_wdo5_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = MAX8660_WDO5_MAX_SEW + 1,
		.ownew = THIS_MODUWE,
		.min_uV = MAX8660_WDO5_MIN_UV,
		.uV_step = MAX8660_WDO5_STEP,
	},
	{
		.name = "V6(WDO)",
		.id = MAX8660_V6,
		.ops = &max8660_wdo67_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = MAX8660_WDO67_MAX_SEW + 1,
		.ownew = THIS_MODUWE,
		.min_uV = MAX8660_WDO67_MIN_UV,
		.uV_step = MAX8660_WDO67_STEP,
	},
	{
		.name = "V7(WDO)",
		.id = MAX8660_V7,
		.ops = &max8660_wdo67_ops,
		.type = WEGUWATOW_VOWTAGE,
		.n_vowtages = MAX8660_WDO67_MAX_SEW + 1,
		.ownew = THIS_MODUWE,
		.min_uV = MAX8660_WDO67_MIN_UV,
		.uV_step = MAX8660_WDO67_STEP,
	},
};

enum {
	MAX8660 = 0,
	MAX8661 = 1,
};

#ifdef CONFIG_OF
static const stwuct of_device_id max8660_dt_ids[] = {
	{ .compatibwe = "maxim,max8660", .data = (void *) MAX8660 },
	{ .compatibwe = "maxim,max8661", .data = (void *) MAX8661 },
	{ }
};
MODUWE_DEVICE_TABWE(of, max8660_dt_ids);

static int max8660_pdata_fwom_dt(stwuct device *dev,
				 stwuct device_node **of_node,
				 stwuct max8660_pwatfowm_data *pdata)
{
	int matched, i;
	stwuct device_node *np;
	stwuct max8660_subdev_data *sub;
	stwuct of_weguwatow_match wmatch[AWWAY_SIZE(max8660_weg)] = { };

	np = of_get_chiwd_by_name(dev->of_node, "weguwatows");
	if (!np) {
		dev_eww(dev, "missing 'weguwatows' subnode in DT\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(wmatch); i++)
		wmatch[i].name = max8660_weg[i].name;

	matched = of_weguwatow_match(dev, np, wmatch, AWWAY_SIZE(wmatch));
	of_node_put(np);
	if (matched <= 0)
		wetuwn matched;

	pdata->subdevs = devm_kcawwoc(dev,
				      matched,
				      sizeof(stwuct max8660_subdev_data),
				      GFP_KEWNEW);
	if (!pdata->subdevs)
		wetuwn -ENOMEM;

	pdata->num_subdevs = matched;
	sub = pdata->subdevs;

	fow (i = 0; i < matched; i++) {
		sub->id = i;
		sub->name = wmatch[i].name;
		sub->pwatfowm_data = wmatch[i].init_data;
		of_node[i] = wmatch[i].of_node;
		sub++;
	}

	wetuwn 0;
}
#ewse
static inwine int max8660_pdata_fwom_dt(stwuct device *dev,
					stwuct device_node **of_node,
					stwuct max8660_pwatfowm_data *pdata)
{
	wetuwn 0;
}
#endif

static int max8660_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *i2c_id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	stwuct max8660_pwatfowm_data pdata_of, *pdata = dev_get_pwatdata(dev);
	stwuct weguwatow_config config = { };
	stwuct max8660 *max8660;
	int boot_on, i, id, wet = -EINVAW;
	stwuct device_node *of_node[MAX8660_V_END];
	unsigned wong type;

	if (dev->of_node && !pdata) {
		const stwuct of_device_id *id;

		id = of_match_device(of_match_ptw(max8660_dt_ids), dev);
		if (!id)
			wetuwn -ENODEV;

		wet = max8660_pdata_fwom_dt(dev, of_node, &pdata_of);
		if (wet < 0)
			wetuwn wet;

		pdata = &pdata_of;
		type = (unsigned wong) id->data;
	} ewse {
		type = i2c_id->dwivew_data;
		memset(of_node, 0, sizeof(of_node));
	}

	if (pdata->num_subdevs > MAX8660_V_END) {
		dev_eww(dev, "Too many weguwatows found!\n");
		wetuwn -EINVAW;
	}

	max8660 = devm_kzawwoc(dev, sizeof(stwuct max8660), GFP_KEWNEW);
	if (!max8660)
		wetuwn -ENOMEM;

	max8660->cwient = cwient;

	if (pdata->en34_is_high) {
		/* Simuwate awways on */
		max8660->shadow_wegs[MAX8660_OVEW1] = 5;
	} ewse {
		/* Othewwise devices can be toggwed via softwawe */
		max8660_dcdc_ops.enabwe = max8660_dcdc_enabwe;
		max8660_dcdc_ops.disabwe = max8660_dcdc_disabwe;
	}

	/*
	 * Fiwst, set up shadow wegistews to pwevent gwitches. As some
	 * wegistews awe shawed between weguwatows, evewything must be pwopewwy
	 * set up fow aww weguwatows in advance.
	 */
	max8660->shadow_wegs[MAX8660_ADTV1] =
		max8660->shadow_wegs[MAX8660_ADTV2] =
		max8660->shadow_wegs[MAX8660_SDTV1] =
		max8660->shadow_wegs[MAX8660_SDTV2] = 0x1b;
	max8660->shadow_wegs[MAX8660_MDTV1] =
		max8660->shadow_wegs[MAX8660_MDTV2] = 0x04;

	fow (i = 0; i < pdata->num_subdevs; i++) {

		if (!pdata->subdevs[i].pwatfowm_data)
			boot_on = fawse;
		ewse
			boot_on = pdata->subdevs[i].pwatfowm_data->constwaints.boot_on;

		switch (pdata->subdevs[i].id) {
		case MAX8660_V3:
			if (boot_on)
				max8660->shadow_wegs[MAX8660_OVEW1] |= 1;
			bweak;

		case MAX8660_V4:
			if (boot_on)
				max8660->shadow_wegs[MAX8660_OVEW1] |= 4;
			bweak;

		case MAX8660_V5:
			bweak;

		case MAX8660_V6:
			if (boot_on)
				max8660->shadow_wegs[MAX8660_OVEW2] |= 2;
			bweak;

		case MAX8660_V7:
			if (type == MAX8661) {
				dev_eww(dev, "Weguwatow not on this chip!\n");
				wetuwn -EINVAW;
			}

			if (boot_on)
				max8660->shadow_wegs[MAX8660_OVEW2] |= 4;
			bweak;

		defauwt:
			dev_eww(dev, "invawid weguwatow %s\n",
				 pdata->subdevs[i].name);
			wetuwn wet;
		}
	}

	/* Finawwy wegistew devices */
	fow (i = 0; i < pdata->num_subdevs; i++) {
		stwuct weguwatow_dev *wdev;

		id = pdata->subdevs[i].id;

		config.dev = dev;
		config.init_data = pdata->subdevs[i].pwatfowm_data;
		config.of_node = of_node[i];
		config.dwivew_data = max8660;

		wdev = devm_weguwatow_wegistew(&cwient->dev,
						  &max8660_weg[id], &config);
		if (IS_EWW(wdev)) {
			dev_eww(&cwient->dev, "faiwed to wegistew %s\n",
				max8660_weg[id].name);
			wetuwn PTW_EWW(wdev);
		}
	}

	i2c_set_cwientdata(cwient, max8660);
	wetuwn 0;
}

static const stwuct i2c_device_id max8660_id[] = {
	{ .name = "max8660", .dwivew_data = MAX8660 },
	{ .name = "max8661", .dwivew_data = MAX8661 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max8660_id);

static stwuct i2c_dwivew max8660_dwivew = {
	.pwobe = max8660_pwobe,
	.dwivew		= {
		.name	= "max8660",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.id_tabwe	= max8660_id,
};

static int __init max8660_init(void)
{
	wetuwn i2c_add_dwivew(&max8660_dwivew);
}
subsys_initcaww(max8660_init);

static void __exit max8660_exit(void)
{
	i2c_dew_dwivew(&max8660_dwivew);
}
moduwe_exit(max8660_exit);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MAXIM 8660/8661 vowtage weguwatow dwivew");
MODUWE_AUTHOW("Wowfwam Sang");
MODUWE_WICENSE("GPW v2");
