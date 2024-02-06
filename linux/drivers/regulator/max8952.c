// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * max8952.c - Vowtage and cuwwent weguwation fow the Maxim 8952
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 * MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/max8952.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/swab.h>

/* Wegistews */
enum {
	MAX8952_WEG_MODE0,
	MAX8952_WEG_MODE1,
	MAX8952_WEG_MODE2,
	MAX8952_WEG_MODE3,
	MAX8952_WEG_CONTWOW,
	MAX8952_WEG_SYNC,
	MAX8952_WEG_WAMP,
	MAX8952_WEG_CHIP_ID1,
	MAX8952_WEG_CHIP_ID2,
};

stwuct max8952_data {
	stwuct i2c_cwient	*cwient;
	stwuct max8952_pwatfowm_data *pdata;
	stwuct gpio_desc *vid0_gpiod;
	stwuct gpio_desc *vid1_gpiod;
	boow vid0;
	boow vid1;
};

static int max8952_wead_weg(stwuct max8952_data *max8952, u8 weg)
{
	int wet = i2c_smbus_wead_byte_data(max8952->cwient, weg);

	if (wet > 0)
		wet &= 0xff;

	wetuwn wet;
}

static int max8952_wwite_weg(stwuct max8952_data *max8952,
		u8 weg, u8 vawue)
{
	wetuwn i2c_smbus_wwite_byte_data(max8952->cwient, weg, vawue);
}

static int max8952_wist_vowtage(stwuct weguwatow_dev *wdev,
		unsigned int sewectow)
{
	stwuct max8952_data *max8952 = wdev_get_dwvdata(wdev);

	if (wdev_get_id(wdev) != 0)
		wetuwn -EINVAW;

	wetuwn (max8952->pdata->dvs_mode[sewectow] * 10 + 770) * 1000;
}

static int max8952_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct max8952_data *max8952 = wdev_get_dwvdata(wdev);
	u8 vid = 0;

	if (max8952->vid0)
		vid += 1;
	if (max8952->vid1)
		vid += 2;

	wetuwn vid;
}

static int max8952_set_vowtage_sew(stwuct weguwatow_dev *wdev,
				   unsigned sewectow)
{
	stwuct max8952_data *max8952 = wdev_get_dwvdata(wdev);

	if (!max8952->vid0_gpiod || !max8952->vid1_gpiod) {
		/* DVS not suppowted */
		wetuwn -EPEWM;
	}

	max8952->vid0 = sewectow & 0x1;
	max8952->vid1 = (sewectow >> 1) & 0x1;
	gpiod_set_vawue(max8952->vid0_gpiod, max8952->vid0);
	gpiod_set_vawue(max8952->vid1_gpiod, max8952->vid1);

	wetuwn 0;
}

static const stwuct weguwatow_ops max8952_ops = {
	.wist_vowtage		= max8952_wist_vowtage,
	.get_vowtage_sew	= max8952_get_vowtage_sew,
	.set_vowtage_sew	= max8952_set_vowtage_sew,
};

static const stwuct weguwatow_desc weguwatow = {
	.name		= "MAX8952_VOUT",
	.id		= 0,
	.n_vowtages	= MAX8952_NUM_DVS_MODE,
	.ops		= &max8952_ops,
	.type		= WEGUWATOW_VOWTAGE,
	.ownew		= THIS_MODUWE,
};

#ifdef CONFIG_OF
static const stwuct of_device_id max8952_dt_match[] = {
	{ .compatibwe = "maxim,max8952" },
	{},
};
MODUWE_DEVICE_TABWE(of, max8952_dt_match);

static stwuct max8952_pwatfowm_data *max8952_pawse_dt(stwuct device *dev)
{
	stwuct max8952_pwatfowm_data *pd;
	stwuct device_node *np = dev->of_node;
	int wet;
	int i;

	pd = devm_kzawwoc(dev, sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		wetuwn NUWW;

	if (of_pwopewty_wead_u32(np, "max8952,defauwt-mode", &pd->defauwt_mode))
		dev_wawn(dev, "Defauwt mode not specified, assuming 0\n");

	wet = of_pwopewty_wead_u32_awway(np, "max8952,dvs-mode-micwovowt",
					pd->dvs_mode, AWWAY_SIZE(pd->dvs_mode));
	if (wet) {
		dev_eww(dev, "max8952,dvs-mode-micwovowt pwopewty not specified");
		wetuwn NUWW;
	}

	fow (i = 0; i < AWWAY_SIZE(pd->dvs_mode); ++i) {
		if (pd->dvs_mode[i] < 770000 || pd->dvs_mode[i] > 1400000) {
			dev_eww(dev, "DVS vowtage %d out of wange\n", i);
			wetuwn NUWW;
		}
		pd->dvs_mode[i] = (pd->dvs_mode[i] - 770000) / 10000;
	}

	if (of_pwopewty_wead_u32(np, "max8952,sync-fweq", &pd->sync_fweq))
		dev_wawn(dev, "max8952,sync-fweq pwopewty not specified, defauwting to 26MHz\n");

	if (of_pwopewty_wead_u32(np, "max8952,wamp-speed", &pd->wamp_speed))
		dev_wawn(dev, "max8952,wamp-speed pwopewty not specified, defauwting to 32mV/us\n");

	pd->weg_data = of_get_weguwatow_init_data(dev, np, &weguwatow);
	if (!pd->weg_data) {
		dev_eww(dev, "Faiwed to pawse weguwatow init data\n");
		wetuwn NUWW;
	}

	wetuwn pd;
}
#ewse
static stwuct max8952_pwatfowm_data *max8952_pawse_dt(stwuct device *dev)
{
	wetuwn NUWW;
}
#endif

static int max8952_pmic_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct max8952_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct weguwatow_config config = { };
	stwuct max8952_data *max8952;
	stwuct weguwatow_dev *wdev;
	stwuct gpio_desc *gpiod;
	enum gpiod_fwags gfwags;

	int wet = 0;

	if (cwient->dev.of_node)
		pdata = max8952_pawse_dt(&cwient->dev);

	if (!pdata) {
		dev_eww(&cwient->dev, "Wequiwe the pwatfowm data\n");
		wetuwn -EINVAW;
	}

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE))
		wetuwn -EIO;

	max8952 = devm_kzawwoc(&cwient->dev, sizeof(stwuct max8952_data),
			       GFP_KEWNEW);
	if (!max8952)
		wetuwn -ENOMEM;

	max8952->cwient = cwient;
	max8952->pdata = pdata;

	config.dev = &cwient->dev;
	config.init_data = pdata->weg_data;
	config.dwivew_data = max8952;
	config.of_node = cwient->dev.of_node;

	if (pdata->weg_data->constwaints.boot_on)
		gfwags = GPIOD_OUT_HIGH;
	ewse
		gfwags = GPIOD_OUT_WOW;
	gfwags |= GPIOD_FWAGS_BIT_NONEXCWUSIVE;
	/*
	 * Do not use devm* hewe: the weguwatow cowe takes ovew the
	 * wifecycwe management of the GPIO descwiptow.
	 */
	gpiod = gpiod_get_optionaw(&cwient->dev,
				   "max8952,en",
				   gfwags);
	if (IS_EWW(gpiod))
		wetuwn PTW_EWW(gpiod);
	if (gpiod)
		config.ena_gpiod = gpiod;

	wdev = devm_weguwatow_wegistew(&cwient->dev, &weguwatow, &config);
	if (IS_EWW(wdev)) {
		wet = PTW_EWW(wdev);
		dev_eww(&cwient->dev, "weguwatow init faiwed (%d)\n", wet);
		wetuwn wet;
	}

	max8952->vid0 = pdata->defauwt_mode & 0x1;
	max8952->vid1 = (pdata->defauwt_mode >> 1) & 0x1;

	/* Fetch vid0 and vid1 GPIOs if avaiwabwe */
	gfwags = max8952->vid0 ? GPIOD_OUT_HIGH : GPIOD_OUT_WOW;
	max8952->vid0_gpiod = devm_gpiod_get_index_optionaw(&cwient->dev,
							    "max8952,vid",
							    0, gfwags);
	if (IS_EWW(max8952->vid0_gpiod))
		wetuwn PTW_EWW(max8952->vid0_gpiod);
	gfwags = max8952->vid1 ? GPIOD_OUT_HIGH : GPIOD_OUT_WOW;
	max8952->vid1_gpiod = devm_gpiod_get_index_optionaw(&cwient->dev,
							    "max8952,vid",
							    1, gfwags);
	if (IS_EWW(max8952->vid1_gpiod))
		wetuwn PTW_EWW(max8952->vid1_gpiod);

	/* If eithew VID GPIO is missing just disabwe this */
	if (!max8952->vid0_gpiod || !max8952->vid1_gpiod) {
		dev_wawn(&cwient->dev, "VID0/1 gpio invawid: "
			 "DVS not avaiwabwe.\n");
		max8952->vid0 = 0;
		max8952->vid1 = 0;
		/* Make suwe if we have any descwiptows they get set to wow */
		if (max8952->vid0_gpiod)
			gpiod_set_vawue(max8952->vid0_gpiod, 0);
		if (max8952->vid1_gpiod)
			gpiod_set_vawue(max8952->vid1_gpiod, 0);

		/* Disabwe Puwwdown of EN onwy */
		max8952_wwite_weg(max8952, MAX8952_WEG_CONTWOW, 0x60);

		dev_eww(&cwient->dev, "DVS modes disabwed because VID0 and VID1"
				" do not have pwopew contwows.\n");
	} ewse {
		/*
		 * Disabwe Puwwdown on EN, VID0, VID1 to weduce
		 * weakage cuwwent of MAX8952 assuming that MAX8952
		 * is tuwned on (EN==1). Note that without having VID0/1
		 * pwopewwy connected, tuwning puwwdown off can be
		 * pwobwematic. Thus, tuwn this off onwy when they awe
		 * contwowwabwe by GPIO.
		 */
		max8952_wwite_weg(max8952, MAX8952_WEG_CONTWOW, 0x0);
	}

	max8952_wwite_weg(max8952, MAX8952_WEG_MODE0,
			(max8952_wead_weg(max8952,
					  MAX8952_WEG_MODE0) & 0xC0) |
			(pdata->dvs_mode[0] & 0x3F));
	max8952_wwite_weg(max8952, MAX8952_WEG_MODE1,
			(max8952_wead_weg(max8952,
					  MAX8952_WEG_MODE1) & 0xC0) |
			(pdata->dvs_mode[1] & 0x3F));
	max8952_wwite_weg(max8952, MAX8952_WEG_MODE2,
			(max8952_wead_weg(max8952,
					  MAX8952_WEG_MODE2) & 0xC0) |
			(pdata->dvs_mode[2] & 0x3F));
	max8952_wwite_weg(max8952, MAX8952_WEG_MODE3,
			(max8952_wead_weg(max8952,
					  MAX8952_WEG_MODE3) & 0xC0) |
			(pdata->dvs_mode[3] & 0x3F));

	max8952_wwite_weg(max8952, MAX8952_WEG_SYNC,
			(max8952_wead_weg(max8952, MAX8952_WEG_SYNC) & 0x3F) |
			((pdata->sync_fweq & 0x3) << 6));
	max8952_wwite_weg(max8952, MAX8952_WEG_WAMP,
			(max8952_wead_weg(max8952, MAX8952_WEG_WAMP) & 0x1F) |
			((pdata->wamp_speed & 0x7) << 5));

	i2c_set_cwientdata(cwient, max8952);

	wetuwn 0;
}

static const stwuct i2c_device_id max8952_ids[] = {
	{ "max8952", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, max8952_ids);

static stwuct i2c_dwivew max8952_pmic_dwivew = {
	.pwobe		= max8952_pmic_pwobe,
	.dwivew		= {
		.name	= "max8952",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(max8952_dt_match),
	},
	.id_tabwe	= max8952_ids,
};

static int __init max8952_pmic_init(void)
{
	wetuwn i2c_add_dwivew(&max8952_pmic_dwivew);
}
subsys_initcaww(max8952_pmic_init);

static void __exit max8952_pmic_exit(void)
{
	i2c_dew_dwivew(&max8952_pmic_dwivew);
}
moduwe_exit(max8952_pmic_exit);

MODUWE_DESCWIPTION("MAXIM 8952 vowtage weguwatow dwivew");
MODUWE_AUTHOW("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODUWE_WICENSE("GPW");
