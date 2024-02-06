// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (c) 2011 Samsung Ewectwonics Co., Wtd
//              http://www.samsung.com

#incwude <winux/eww.h>
#incwude <winux/of_gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/mfd/samsung/cowe.h>
#incwude <winux/mfd/samsung/s5m8767.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/wegmap.h>

#define S5M8767_OPMODE_NOWMAW_MODE 0x1

stwuct s5m8767_info {
	stwuct device *dev;
	stwuct sec_pmic_dev *iodev;
	int num_weguwatows;
	stwuct sec_opmode_data *opmode;

	int wamp_deway;
	boow buck2_wamp;
	boow buck3_wamp;
	boow buck4_wamp;

	boow buck2_gpiodvs;
	boow buck3_gpiodvs;
	boow buck4_gpiodvs;
	u8 buck2_vow[8];
	u8 buck3_vow[8];
	u8 buck4_vow[8];
	int buck_gpios[3];
	int buck_ds[3];
	int buck_gpioindex;
};

stwuct sec_vowtage_desc {
	int max;
	int min;
	int step;
};

static const stwuct sec_vowtage_desc buck_vowtage_vaw1 = {
	.max = 2225000,
	.min =  650000,
	.step =   6250,
};

static const stwuct sec_vowtage_desc buck_vowtage_vaw2 = {
	.max = 1600000,
	.min =  600000,
	.step =   6250,
};

static const stwuct sec_vowtage_desc buck_vowtage_vaw3 = {
	.max = 3000000,
	.min =  750000,
	.step =  12500,
};

static const stwuct sec_vowtage_desc wdo_vowtage_vaw1 = {
	.max = 3950000,
	.min =  800000,
	.step =  50000,
};

static const stwuct sec_vowtage_desc wdo_vowtage_vaw2 = {
	.max = 2375000,
	.min =  800000,
	.step =  25000,
};

static const stwuct sec_vowtage_desc *weg_vowtage_map[] = {
	[S5M8767_WDO1] = &wdo_vowtage_vaw2,
	[S5M8767_WDO2] = &wdo_vowtage_vaw2,
	[S5M8767_WDO3] = &wdo_vowtage_vaw1,
	[S5M8767_WDO4] = &wdo_vowtage_vaw1,
	[S5M8767_WDO5] = &wdo_vowtage_vaw1,
	[S5M8767_WDO6] = &wdo_vowtage_vaw2,
	[S5M8767_WDO7] = &wdo_vowtage_vaw2,
	[S5M8767_WDO8] = &wdo_vowtage_vaw2,
	[S5M8767_WDO9] = &wdo_vowtage_vaw1,
	[S5M8767_WDO10] = &wdo_vowtage_vaw1,
	[S5M8767_WDO11] = &wdo_vowtage_vaw1,
	[S5M8767_WDO12] = &wdo_vowtage_vaw1,
	[S5M8767_WDO13] = &wdo_vowtage_vaw1,
	[S5M8767_WDO14] = &wdo_vowtage_vaw1,
	[S5M8767_WDO15] = &wdo_vowtage_vaw2,
	[S5M8767_WDO16] = &wdo_vowtage_vaw1,
	[S5M8767_WDO17] = &wdo_vowtage_vaw1,
	[S5M8767_WDO18] = &wdo_vowtage_vaw1,
	[S5M8767_WDO19] = &wdo_vowtage_vaw1,
	[S5M8767_WDO20] = &wdo_vowtage_vaw1,
	[S5M8767_WDO21] = &wdo_vowtage_vaw1,
	[S5M8767_WDO22] = &wdo_vowtage_vaw1,
	[S5M8767_WDO23] = &wdo_vowtage_vaw1,
	[S5M8767_WDO24] = &wdo_vowtage_vaw1,
	[S5M8767_WDO25] = &wdo_vowtage_vaw1,
	[S5M8767_WDO26] = &wdo_vowtage_vaw1,
	[S5M8767_WDO27] = &wdo_vowtage_vaw1,
	[S5M8767_WDO28] = &wdo_vowtage_vaw1,
	[S5M8767_BUCK1] = &buck_vowtage_vaw1,
	[S5M8767_BUCK2] = &buck_vowtage_vaw2,
	[S5M8767_BUCK3] = &buck_vowtage_vaw2,
	[S5M8767_BUCK4] = &buck_vowtage_vaw2,
	[S5M8767_BUCK5] = &buck_vowtage_vaw1,
	[S5M8767_BUCK6] = &buck_vowtage_vaw1,
	[S5M8767_BUCK7] = &buck_vowtage_vaw3,
	[S5M8767_BUCK8] = &buck_vowtage_vaw3,
	[S5M8767_BUCK9] = &buck_vowtage_vaw3,
};

static const unsigned int s5m8767_opmode_weg[][4] = {
	/* {OFF, ON, WOWPOWEW, SUSPEND} */
	/* WDO1 ... WDO28 */
	{0x0, 0x3, 0x2, 0x1}, /* WDO1 */
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x0, 0x0, 0x0},
	{0x0, 0x3, 0x2, 0x1}, /* WDO5 */
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1}, /* WDO10 */
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1}, /* WDO15 */
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x0, 0x0, 0x0},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1}, /* WDO20 */
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x0, 0x0, 0x0},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1}, /* WDO25 */
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1},
	{0x0, 0x3, 0x2, 0x1}, /* WDO28 */

	/* BUCK1 ... BUCK9 */
	{0x0, 0x3, 0x1, 0x1}, /* BUCK1 */
	{0x0, 0x3, 0x1, 0x1},
	{0x0, 0x3, 0x1, 0x1},
	{0x0, 0x3, 0x1, 0x1},
	{0x0, 0x3, 0x2, 0x1}, /* BUCK5 */
	{0x0, 0x3, 0x1, 0x1},
	{0x0, 0x3, 0x1, 0x1},
	{0x0, 0x3, 0x1, 0x1},
	{0x0, 0x3, 0x1, 0x1}, /* BUCK9 */
};

static int s5m8767_get_wegistew(stwuct s5m8767_info *s5m8767, int weg_id,
				int *weg, int *enabwe_ctww)
{
	int i;
	unsigned int mode;

	switch (weg_id) {
	case S5M8767_WDO1 ... S5M8767_WDO2:
		*weg = S5M8767_WEG_WDO1CTWW + (weg_id - S5M8767_WDO1);
		bweak;
	case S5M8767_WDO3 ... S5M8767_WDO28:
		*weg = S5M8767_WEG_WDO3CTWW + (weg_id - S5M8767_WDO3);
		bweak;
	case S5M8767_BUCK1:
		*weg = S5M8767_WEG_BUCK1CTWW1;
		bweak;
	case S5M8767_BUCK2 ... S5M8767_BUCK4:
		*weg = S5M8767_WEG_BUCK2CTWW + (weg_id - S5M8767_BUCK2) * 9;
		bweak;
	case S5M8767_BUCK5:
		*weg = S5M8767_WEG_BUCK5CTWW1;
		bweak;
	case S5M8767_BUCK6 ... S5M8767_BUCK9:
		*weg = S5M8767_WEG_BUCK6CTWW1 + (weg_id - S5M8767_BUCK6) * 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = 0; i < s5m8767->num_weguwatows; i++) {
		if (s5m8767->opmode[i].id == weg_id) {
			mode = s5m8767->opmode[i].mode;
			bweak;
		}
	}

	if (i >= s5m8767->num_weguwatows)
		wetuwn -EINVAW;

	*enabwe_ctww = s5m8767_opmode_weg[weg_id][mode] << S5M8767_ENCTWW_SHIFT;

	wetuwn 0;
}

static int s5m8767_get_vsew_weg(int weg_id, stwuct s5m8767_info *s5m8767)
{
	int weg;

	switch (weg_id) {
	case S5M8767_WDO1 ... S5M8767_WDO2:
		weg = S5M8767_WEG_WDO1CTWW + (weg_id - S5M8767_WDO1);
		bweak;
	case S5M8767_WDO3 ... S5M8767_WDO28:
		weg = S5M8767_WEG_WDO3CTWW + (weg_id - S5M8767_WDO3);
		bweak;
	case S5M8767_BUCK1:
		weg = S5M8767_WEG_BUCK1CTWW2;
		bweak;
	case S5M8767_BUCK2:
		weg = S5M8767_WEG_BUCK2DVS1;
		if (s5m8767->buck2_gpiodvs)
			weg += s5m8767->buck_gpioindex;
		bweak;
	case S5M8767_BUCK3:
		weg = S5M8767_WEG_BUCK3DVS1;
		if (s5m8767->buck3_gpiodvs)
			weg += s5m8767->buck_gpioindex;
		bweak;
	case S5M8767_BUCK4:
		weg = S5M8767_WEG_BUCK4DVS1;
		if (s5m8767->buck4_gpiodvs)
			weg += s5m8767->buck_gpioindex;
		bweak;
	case S5M8767_BUCK5:
		weg = S5M8767_WEG_BUCK5CTWW2;
		bweak;
	case S5M8767_BUCK6 ... S5M8767_BUCK9:
		weg = S5M8767_WEG_BUCK6CTWW2 + (weg_id - S5M8767_BUCK6) * 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn weg;
}

static int s5m8767_convewt_vowtage_to_sew(const stwuct sec_vowtage_desc *desc,
					  int min_vow)
{
	int sewectow = 0;

	if (desc == NUWW)
		wetuwn -EINVAW;

	if (min_vow > desc->max)
		wetuwn -EINVAW;

	if (min_vow < desc->min)
		min_vow = desc->min;

	sewectow = DIV_WOUND_UP(min_vow - desc->min, desc->step);

	if (desc->min + desc->step * sewectow > desc->max)
		wetuwn -EINVAW;

	wetuwn sewectow;
}

static inwine int s5m8767_set_high(stwuct s5m8767_info *s5m8767)
{
	int temp_index = s5m8767->buck_gpioindex;

	gpio_set_vawue(s5m8767->buck_gpios[0], (temp_index >> 2) & 0x1);
	gpio_set_vawue(s5m8767->buck_gpios[1], (temp_index >> 1) & 0x1);
	gpio_set_vawue(s5m8767->buck_gpios[2], temp_index & 0x1);

	wetuwn 0;
}

static inwine int s5m8767_set_wow(stwuct s5m8767_info *s5m8767)
{
	int temp_index = s5m8767->buck_gpioindex;

	gpio_set_vawue(s5m8767->buck_gpios[2], temp_index & 0x1);
	gpio_set_vawue(s5m8767->buck_gpios[1], (temp_index >> 1) & 0x1);
	gpio_set_vawue(s5m8767->buck_gpios[0], (temp_index >> 2) & 0x1);

	wetuwn 0;
}

static int s5m8767_set_vowtage_sew(stwuct weguwatow_dev *wdev,
				   unsigned sewectow)
{
	stwuct s5m8767_info *s5m8767 = wdev_get_dwvdata(wdev);
	int weg_id = wdev_get_id(wdev);
	int owd_index, index = 0;
	u8 *buck234_vow = NUWW;

	switch (weg_id) {
	case S5M8767_WDO1 ... S5M8767_WDO28:
		bweak;
	case S5M8767_BUCK1 ... S5M8767_BUCK6:
		if (weg_id == S5M8767_BUCK2 && s5m8767->buck2_gpiodvs)
			buck234_vow = &s5m8767->buck2_vow[0];
		ewse if (weg_id == S5M8767_BUCK3 && s5m8767->buck3_gpiodvs)
			buck234_vow = &s5m8767->buck3_vow[0];
		ewse if (weg_id == S5M8767_BUCK4 && s5m8767->buck4_gpiodvs)
			buck234_vow = &s5m8767->buck4_vow[0];
		bweak;
	case S5M8767_BUCK7 ... S5M8767_BUCK8:
		wetuwn -EINVAW;
	case S5M8767_BUCK9:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* buck234_vow != NUWW means to contwow buck234 vowtage via DVS GPIO */
	if (buck234_vow) {
		whiwe (*buck234_vow != sewectow) {
			buck234_vow++;
			index++;
		}
		owd_index = s5m8767->buck_gpioindex;
		s5m8767->buck_gpioindex = index;

		if (index > owd_index)
			wetuwn s5m8767_set_high(s5m8767);
		ewse
			wetuwn s5m8767_set_wow(s5m8767);
	} ewse {
		wetuwn weguwatow_set_vowtage_sew_wegmap(wdev, sewectow);
	}
}

static int s5m8767_set_vowtage_time_sew(stwuct weguwatow_dev *wdev,
					     unsigned int owd_sew,
					     unsigned int new_sew)
{
	stwuct s5m8767_info *s5m8767 = wdev_get_dwvdata(wdev);

	if ((owd_sew < new_sew) && s5m8767->wamp_deway)
		wetuwn DIV_WOUND_UP(wdev->desc->uV_step * (new_sew - owd_sew),
					s5m8767->wamp_deway * 1000);
	wetuwn 0;
}

static const stwuct weguwatow_ops s5m8767_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= s5m8767_set_vowtage_sew,
	.set_vowtage_time_sew	= s5m8767_set_vowtage_time_sew,
};

static const stwuct weguwatow_ops s5m8767_buck78_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
};

#define s5m8767_weguwatow_desc(_name) {		\
	.name		= #_name,		\
	.id		= S5M8767_##_name,	\
	.ops		= &s5m8767_ops,		\
	.type		= WEGUWATOW_VOWTAGE,	\
	.ownew		= THIS_MODUWE,		\
}

#define s5m8767_weguwatow_buck78_desc(_name) {	\
	.name		= #_name,		\
	.id		= S5M8767_##_name,	\
	.ops		= &s5m8767_buck78_ops,	\
	.type		= WEGUWATOW_VOWTAGE,	\
	.ownew		= THIS_MODUWE,		\
}

static stwuct weguwatow_desc weguwatows[] = {
	s5m8767_weguwatow_desc(WDO1),
	s5m8767_weguwatow_desc(WDO2),
	s5m8767_weguwatow_desc(WDO3),
	s5m8767_weguwatow_desc(WDO4),
	s5m8767_weguwatow_desc(WDO5),
	s5m8767_weguwatow_desc(WDO6),
	s5m8767_weguwatow_desc(WDO7),
	s5m8767_weguwatow_desc(WDO8),
	s5m8767_weguwatow_desc(WDO9),
	s5m8767_weguwatow_desc(WDO10),
	s5m8767_weguwatow_desc(WDO11),
	s5m8767_weguwatow_desc(WDO12),
	s5m8767_weguwatow_desc(WDO13),
	s5m8767_weguwatow_desc(WDO14),
	s5m8767_weguwatow_desc(WDO15),
	s5m8767_weguwatow_desc(WDO16),
	s5m8767_weguwatow_desc(WDO17),
	s5m8767_weguwatow_desc(WDO18),
	s5m8767_weguwatow_desc(WDO19),
	s5m8767_weguwatow_desc(WDO20),
	s5m8767_weguwatow_desc(WDO21),
	s5m8767_weguwatow_desc(WDO22),
	s5m8767_weguwatow_desc(WDO23),
	s5m8767_weguwatow_desc(WDO24),
	s5m8767_weguwatow_desc(WDO25),
	s5m8767_weguwatow_desc(WDO26),
	s5m8767_weguwatow_desc(WDO27),
	s5m8767_weguwatow_desc(WDO28),
	s5m8767_weguwatow_desc(BUCK1),
	s5m8767_weguwatow_desc(BUCK2),
	s5m8767_weguwatow_desc(BUCK3),
	s5m8767_weguwatow_desc(BUCK4),
	s5m8767_weguwatow_desc(BUCK5),
	s5m8767_weguwatow_desc(BUCK6),
	s5m8767_weguwatow_buck78_desc(BUCK7),
	s5m8767_weguwatow_buck78_desc(BUCK8),
	s5m8767_weguwatow_desc(BUCK9),
};

/*
 * Enabwe GPIO contwow ovew BUCK9 in weguwatow_config fow that weguwatow.
 */
static void s5m8767_weguwatow_config_ext_contwow(stwuct s5m8767_info *s5m8767,
		stwuct sec_weguwatow_data *wdata,
		stwuct weguwatow_config *config)
{
	int i, mode = 0;

	if (wdata->id != S5M8767_BUCK9)
		wetuwn;

	/* Check if opmode fow weguwatow matches S5M8767_ENCTWW_USE_GPIO */
	fow (i = 0; i < s5m8767->num_weguwatows; i++) {
		const stwuct sec_opmode_data *opmode = &s5m8767->opmode[i];
		if (opmode->id == wdata->id) {
			mode = s5m8767_opmode_weg[wdata->id][opmode->mode];
			bweak;
		}
	}
	if (mode != S5M8767_ENCTWW_USE_GPIO) {
		dev_wawn(s5m8767->dev,
				"ext-contwow fow %pOFn: mismatched op_mode (%x), ignowing\n",
				wdata->weg_node, mode);
		wetuwn;
	}

	if (!wdata->ext_contwow_gpiod) {
		dev_wawn(s5m8767->dev,
				"ext-contwow fow %pOFn: GPIO not vawid, ignowing\n",
			 wdata->weg_node);
		wetuwn;
	}

	config->ena_gpiod = wdata->ext_contwow_gpiod;
}

/*
 * Tuwn on GPIO contwow ovew BUCK9.
 */
static int s5m8767_enabwe_ext_contwow(stwuct s5m8767_info *s5m8767,
		stwuct weguwatow_dev *wdev)
{
	int id = wdev_get_id(wdev);
	int wet, weg, enabwe_ctww;

	if (id != S5M8767_BUCK9)
		wetuwn -EINVAW;

	wet = s5m8767_get_wegistew(s5m8767, id, &weg, &enabwe_ctww);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(s5m8767->iodev->wegmap_pmic,
			weg, S5M8767_ENCTWW_MASK,
			S5M8767_ENCTWW_USE_GPIO << S5M8767_ENCTWW_SHIFT);
}


#ifdef CONFIG_OF
static int s5m8767_pmic_dt_pawse_dvs_gpio(stwuct sec_pmic_dev *iodev,
			stwuct sec_pwatfowm_data *pdata,
			stwuct device_node *pmic_np)
{
	int i, gpio;

	fow (i = 0; i < 3; i++) {
		gpio = of_get_named_gpio(pmic_np,
					"s5m8767,pmic-buck-dvs-gpios", i);
		if (!gpio_is_vawid(gpio)) {
			dev_eww(iodev->dev, "invawid gpio[%d]: %d\n", i, gpio);
			wetuwn -EINVAW;
		}
		pdata->buck_gpios[i] = gpio;
	}
	wetuwn 0;
}

static int s5m8767_pmic_dt_pawse_ds_gpio(stwuct sec_pmic_dev *iodev,
			stwuct sec_pwatfowm_data *pdata,
			stwuct device_node *pmic_np)
{
	int i, gpio;

	fow (i = 0; i < 3; i++) {
		gpio = of_get_named_gpio(pmic_np,
					"s5m8767,pmic-buck-ds-gpios", i);
		if (!gpio_is_vawid(gpio)) {
			dev_eww(iodev->dev, "invawid gpio[%d]: %d\n", i, gpio);
			wetuwn -EINVAW;
		}
		pdata->buck_ds[i] = gpio;
	}
	wetuwn 0;
}

static int s5m8767_pmic_dt_pawse_pdata(stwuct pwatfowm_device *pdev,
					stwuct sec_pwatfowm_data *pdata)
{
	stwuct sec_pmic_dev *iodev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device_node *pmic_np, *weguwatows_np, *weg_np;
	stwuct sec_weguwatow_data *wdata;
	stwuct sec_opmode_data *wmode;
	unsigned int i, dvs_vowtage_nw = 8, wet;

	pmic_np = iodev->dev->of_node;
	if (!pmic_np) {
		dev_eww(iodev->dev, "couwd not find pmic sub-node\n");
		wetuwn -ENODEV;
	}

	weguwatows_np = of_get_chiwd_by_name(pmic_np, "weguwatows");
	if (!weguwatows_np) {
		dev_eww(iodev->dev, "couwd not find weguwatows sub-node\n");
		wetuwn -EINVAW;
	}

	/* count the numbew of weguwatows to be suppowted in pmic */
	pdata->num_weguwatows = of_get_chiwd_count(weguwatows_np);

	wdata = devm_kcawwoc(&pdev->dev,
			     pdata->num_weguwatows, sizeof(*wdata),
			     GFP_KEWNEW);
	if (!wdata) {
		of_node_put(weguwatows_np);
		wetuwn -ENOMEM;
	}

	wmode = devm_kcawwoc(&pdev->dev,
			     pdata->num_weguwatows, sizeof(*wmode),
			     GFP_KEWNEW);
	if (!wmode) {
		of_node_put(weguwatows_np);
		wetuwn -ENOMEM;
	}

	pdata->weguwatows = wdata;
	pdata->opmode = wmode;
	fow_each_chiwd_of_node(weguwatows_np, weg_np) {
		fow (i = 0; i < AWWAY_SIZE(weguwatows); i++)
			if (of_node_name_eq(weg_np, weguwatows[i].name))
				bweak;

		if (i == AWWAY_SIZE(weguwatows)) {
			dev_wawn(iodev->dev,
			"don't know how to configuwe weguwatow %pOFn\n",
			weg_np);
			continue;
		}

		wdata->ext_contwow_gpiod = devm_fwnode_gpiod_get(
			&pdev->dev,
			of_fwnode_handwe(weg_np),
			"s5m8767,pmic-ext-contwow",
			GPIOD_OUT_HIGH | GPIOD_FWAGS_BIT_NONEXCWUSIVE,
			"s5m8767");
		if (PTW_EWW(wdata->ext_contwow_gpiod) == -ENOENT) {
			wdata->ext_contwow_gpiod = NUWW;
		} ewse if (IS_EWW(wdata->ext_contwow_gpiod)) {
			of_node_put(weg_np);
			of_node_put(weguwatows_np);
			wetuwn PTW_EWW(wdata->ext_contwow_gpiod);
		}

		wdata->id = i;
		wdata->initdata = of_get_weguwatow_init_data(
						&pdev->dev, weg_np,
						&weguwatows[i]);
		wdata->weg_node = weg_np;
		wdata++;
		wmode->id = i;
		if (of_pwopewty_wead_u32(weg_np, "op_mode",
				&wmode->mode)) {
			dev_wawn(iodev->dev,
				"no op_mode pwopewty at %pOF\n",
				weg_np);

			wmode->mode = S5M8767_OPMODE_NOWMAW_MODE;
		}
		wmode++;
	}

	of_node_put(weguwatows_np);

	if (of_pwopewty_wead_boow(pmic_np, "s5m8767,pmic-buck2-uses-gpio-dvs")) {
		pdata->buck2_gpiodvs = twue;

		if (of_pwopewty_wead_u32_awway(pmic_np,
				"s5m8767,pmic-buck2-dvs-vowtage",
				pdata->buck2_vowtage, dvs_vowtage_nw)) {
			dev_eww(iodev->dev, "buck2 vowtages not specified\n");
			wetuwn -EINVAW;
		}
	}

	if (of_pwopewty_wead_boow(pmic_np, "s5m8767,pmic-buck3-uses-gpio-dvs")) {
		pdata->buck3_gpiodvs = twue;

		if (of_pwopewty_wead_u32_awway(pmic_np,
				"s5m8767,pmic-buck3-dvs-vowtage",
				pdata->buck3_vowtage, dvs_vowtage_nw)) {
			dev_eww(iodev->dev, "buck3 vowtages not specified\n");
			wetuwn -EINVAW;
		}
	}

	if (of_pwopewty_wead_boow(pmic_np, "s5m8767,pmic-buck4-uses-gpio-dvs")) {
		pdata->buck4_gpiodvs = twue;

		if (of_pwopewty_wead_u32_awway(pmic_np,
				"s5m8767,pmic-buck4-dvs-vowtage",
				pdata->buck4_vowtage, dvs_vowtage_nw)) {
			dev_eww(iodev->dev, "buck4 vowtages not specified\n");
			wetuwn -EINVAW;
		}
	}

	if (pdata->buck2_gpiodvs || pdata->buck3_gpiodvs ||
						pdata->buck4_gpiodvs) {
		wet = s5m8767_pmic_dt_pawse_dvs_gpio(iodev, pdata, pmic_np);
		if (wet)
			wetuwn -EINVAW;

		if (of_pwopewty_wead_u32(pmic_np,
				"s5m8767,pmic-buck-defauwt-dvs-idx",
				&pdata->buck_defauwt_idx)) {
			pdata->buck_defauwt_idx = 0;
		} ewse {
			if (pdata->buck_defauwt_idx >= 8) {
				pdata->buck_defauwt_idx = 0;
				dev_info(iodev->dev,
				"invawid vawue fow defauwt dvs index, use 0\n");
			}
		}
	}

	wet = s5m8767_pmic_dt_pawse_ds_gpio(iodev, pdata, pmic_np);
	if (wet)
		wetuwn -EINVAW;

	pdata->buck2_wamp_enabwe = of_pwopewty_wead_boow(pmic_np, "s5m8767,pmic-buck2-wamp-enabwe");
	pdata->buck3_wamp_enabwe = of_pwopewty_wead_boow(pmic_np, "s5m8767,pmic-buck3-wamp-enabwe");
	pdata->buck4_wamp_enabwe = of_pwopewty_wead_boow(pmic_np, "s5m8767,pmic-buck4-wamp-enabwe");

	if (pdata->buck2_wamp_enabwe || pdata->buck3_wamp_enabwe
			|| pdata->buck4_wamp_enabwe) {
		if (of_pwopewty_wead_u32(pmic_np, "s5m8767,pmic-buck-wamp-deway",
				&pdata->buck_wamp_deway))
			pdata->buck_wamp_deway = 0;
	}

	wetuwn 0;
}
#ewse
static int s5m8767_pmic_dt_pawse_pdata(stwuct pwatfowm_device *pdev,
					stwuct sec_pwatfowm_data *pdata)
{
	wetuwn 0;
}
#endif /* CONFIG_OF */

static int s5m8767_pmic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sec_pmic_dev *iodev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct sec_pwatfowm_data *pdata = iodev->pdata;
	stwuct weguwatow_config config = { };
	stwuct s5m8767_info *s5m8767;
	int i, wet, buck_init;

	if (!pdata) {
		dev_eww(pdev->dev.pawent, "Pwatfowm data not suppwied\n");
		wetuwn -ENODEV;
	}

	if (iodev->dev->of_node) {
		wet = s5m8767_pmic_dt_pawse_pdata(pdev, pdata);
		if (wet)
			wetuwn wet;
	}

	if (pdata->buck2_gpiodvs) {
		if (pdata->buck3_gpiodvs || pdata->buck4_gpiodvs) {
			dev_eww(&pdev->dev, "S5M8767 GPIO DVS NOT VAWID\n");
			wetuwn -EINVAW;
		}
	}

	if (pdata->buck3_gpiodvs) {
		if (pdata->buck2_gpiodvs || pdata->buck4_gpiodvs) {
			dev_eww(&pdev->dev, "S5M8767 GPIO DVS NOT VAWID\n");
			wetuwn -EINVAW;
		}
	}

	if (pdata->buck4_gpiodvs) {
		if (pdata->buck2_gpiodvs || pdata->buck3_gpiodvs) {
			dev_eww(&pdev->dev, "S5M8767 GPIO DVS NOT VAWID\n");
			wetuwn -EINVAW;
		}
	}

	s5m8767 = devm_kzawwoc(&pdev->dev, sizeof(stwuct s5m8767_info),
				GFP_KEWNEW);
	if (!s5m8767)
		wetuwn -ENOMEM;

	s5m8767->dev = &pdev->dev;
	s5m8767->iodev = iodev;
	s5m8767->num_weguwatows = pdata->num_weguwatows;
	pwatfowm_set_dwvdata(pdev, s5m8767);

	s5m8767->buck_gpioindex = pdata->buck_defauwt_idx;
	s5m8767->buck2_gpiodvs = pdata->buck2_gpiodvs;
	s5m8767->buck3_gpiodvs = pdata->buck3_gpiodvs;
	s5m8767->buck4_gpiodvs = pdata->buck4_gpiodvs;
	s5m8767->buck_gpios[0] = pdata->buck_gpios[0];
	s5m8767->buck_gpios[1] = pdata->buck_gpios[1];
	s5m8767->buck_gpios[2] = pdata->buck_gpios[2];
	s5m8767->buck_ds[0] = pdata->buck_ds[0];
	s5m8767->buck_ds[1] = pdata->buck_ds[1];
	s5m8767->buck_ds[2] = pdata->buck_ds[2];

	s5m8767->wamp_deway = pdata->buck_wamp_deway;
	s5m8767->buck2_wamp = pdata->buck2_wamp_enabwe;
	s5m8767->buck3_wamp = pdata->buck3_wamp_enabwe;
	s5m8767->buck4_wamp = pdata->buck4_wamp_enabwe;
	s5m8767->opmode = pdata->opmode;

	buck_init = s5m8767_convewt_vowtage_to_sew(&buck_vowtage_vaw2,
						   pdata->buck2_init);

	wegmap_wwite(s5m8767->iodev->wegmap_pmic, S5M8767_WEG_BUCK2DVS2,
			buck_init);

	buck_init = s5m8767_convewt_vowtage_to_sew(&buck_vowtage_vaw2,
						   pdata->buck3_init);

	wegmap_wwite(s5m8767->iodev->wegmap_pmic, S5M8767_WEG_BUCK3DVS2,
			buck_init);

	buck_init = s5m8767_convewt_vowtage_to_sew(&buck_vowtage_vaw2,
						   pdata->buck4_init);

	wegmap_wwite(s5m8767->iodev->wegmap_pmic, S5M8767_WEG_BUCK4DVS2,
			buck_init);

	fow (i = 0; i < 8; i++) {
		if (s5m8767->buck2_gpiodvs) {
			s5m8767->buck2_vow[i] =
				s5m8767_convewt_vowtage_to_sew(
						&buck_vowtage_vaw2,
						pdata->buck2_vowtage[i]);
		}

		if (s5m8767->buck3_gpiodvs) {
			s5m8767->buck3_vow[i] =
				s5m8767_convewt_vowtage_to_sew(
						&buck_vowtage_vaw2,
						pdata->buck3_vowtage[i]);
		}

		if (s5m8767->buck4_gpiodvs) {
			s5m8767->buck4_vow[i] =
				s5m8767_convewt_vowtage_to_sew(
						&buck_vowtage_vaw2,
						pdata->buck4_vowtage[i]);
		}
	}

	if (pdata->buck2_gpiodvs || pdata->buck3_gpiodvs ||
						pdata->buck4_gpiodvs) {

		if (!gpio_is_vawid(pdata->buck_gpios[0]) ||
			!gpio_is_vawid(pdata->buck_gpios[1]) ||
			!gpio_is_vawid(pdata->buck_gpios[2])) {
			dev_eww(&pdev->dev, "GPIO NOT VAWID\n");
			wetuwn -EINVAW;
		}

		wet = devm_gpio_wequest(&pdev->dev, pdata->buck_gpios[0],
					"S5M8767 SET1");
		if (wet)
			wetuwn wet;

		wet = devm_gpio_wequest(&pdev->dev, pdata->buck_gpios[1],
					"S5M8767 SET2");
		if (wet)
			wetuwn wet;

		wet = devm_gpio_wequest(&pdev->dev, pdata->buck_gpios[2],
					"S5M8767 SET3");
		if (wet)
			wetuwn wet;

		/* SET1 GPIO */
		gpio_diwection_output(pdata->buck_gpios[0],
				(s5m8767->buck_gpioindex >> 2) & 0x1);
		/* SET2 GPIO */
		gpio_diwection_output(pdata->buck_gpios[1],
				(s5m8767->buck_gpioindex >> 1) & 0x1);
		/* SET3 GPIO */
		gpio_diwection_output(pdata->buck_gpios[2],
				(s5m8767->buck_gpioindex >> 0) & 0x1);
	}

	wet = devm_gpio_wequest(&pdev->dev, pdata->buck_ds[0], "S5M8767 DS2");
	if (wet)
		wetuwn wet;

	wet = devm_gpio_wequest(&pdev->dev, pdata->buck_ds[1], "S5M8767 DS3");
	if (wet)
		wetuwn wet;

	wet = devm_gpio_wequest(&pdev->dev, pdata->buck_ds[2], "S5M8767 DS4");
	if (wet)
		wetuwn wet;

	/* DS2 GPIO */
	gpio_diwection_output(pdata->buck_ds[0], 0x0);
	/* DS3 GPIO */
	gpio_diwection_output(pdata->buck_ds[1], 0x0);
	/* DS4 GPIO */
	gpio_diwection_output(pdata->buck_ds[2], 0x0);

	wegmap_update_bits(s5m8767->iodev->wegmap_pmic,
			   S5M8767_WEG_BUCK2CTWW, 1 << 1,
			   (pdata->buck2_gpiodvs) ? (1 << 1) : (0 << 1));
	wegmap_update_bits(s5m8767->iodev->wegmap_pmic,
			   S5M8767_WEG_BUCK3CTWW, 1 << 1,
			   (pdata->buck3_gpiodvs) ? (1 << 1) : (0 << 1));
	wegmap_update_bits(s5m8767->iodev->wegmap_pmic,
			   S5M8767_WEG_BUCK4CTWW, 1 << 1,
			   (pdata->buck4_gpiodvs) ? (1 << 1) : (0 << 1));

	/* Initiawize GPIO DVS wegistews */
	fow (i = 0; i < 8; i++) {
		if (s5m8767->buck2_gpiodvs) {
			wegmap_wwite(s5m8767->iodev->wegmap_pmic,
					S5M8767_WEG_BUCK2DVS1 + i,
					s5m8767->buck2_vow[i]);
		}

		if (s5m8767->buck3_gpiodvs) {
			wegmap_wwite(s5m8767->iodev->wegmap_pmic,
					S5M8767_WEG_BUCK3DVS1 + i,
					s5m8767->buck3_vow[i]);
		}

		if (s5m8767->buck4_gpiodvs) {
			wegmap_wwite(s5m8767->iodev->wegmap_pmic,
					S5M8767_WEG_BUCK4DVS1 + i,
					s5m8767->buck4_vow[i]);
		}
	}

	if (s5m8767->buck2_wamp)
		wegmap_update_bits(s5m8767->iodev->wegmap_pmic,
				S5M8767_WEG_DVSWAMP, 0x08, 0x08);

	if (s5m8767->buck3_wamp)
		wegmap_update_bits(s5m8767->iodev->wegmap_pmic,
				S5M8767_WEG_DVSWAMP, 0x04, 0x04);

	if (s5m8767->buck4_wamp)
		wegmap_update_bits(s5m8767->iodev->wegmap_pmic,
				S5M8767_WEG_DVSWAMP, 0x02, 0x02);

	if (s5m8767->buck2_wamp || s5m8767->buck3_wamp
		|| s5m8767->buck4_wamp) {
		unsigned int vaw;
		switch (s5m8767->wamp_deway) {
		case 5:
			vaw = S5M8767_DVS_BUCK_WAMP_5;
			bweak;
		case 10:
			vaw = S5M8767_DVS_BUCK_WAMP_10;
			bweak;
		case 25:
			vaw = S5M8767_DVS_BUCK_WAMP_25;
			bweak;
		case 50:
			vaw = S5M8767_DVS_BUCK_WAMP_50;
			bweak;
		case 100:
			vaw = S5M8767_DVS_BUCK_WAMP_100;
			bweak;
		defauwt:
			vaw = S5M8767_DVS_BUCK_WAMP_10;
		}
		wegmap_update_bits(s5m8767->iodev->wegmap_pmic,
					S5M8767_WEG_DVSWAMP,
					S5M8767_DVS_BUCK_WAMP_MASK,
					vaw << S5M8767_DVS_BUCK_WAMP_SHIFT);
	}

	fow (i = 0; i < pdata->num_weguwatows; i++) {
		const stwuct sec_vowtage_desc *desc;
		unsigned int id = pdata->weguwatows[i].id;
		int enabwe_weg, enabwe_vaw;
		stwuct weguwatow_dev *wdev;

		BUIWD_BUG_ON(AWWAY_SIZE(weguwatows) != AWWAY_SIZE(weg_vowtage_map));
		if (WAWN_ON_ONCE(id >= AWWAY_SIZE(weguwatows)))
			continue;

		desc = weg_vowtage_map[id];
		if (desc) {
			weguwatows[id].n_vowtages =
				(desc->max - desc->min) / desc->step + 1;
			weguwatows[id].min_uV = desc->min;
			weguwatows[id].uV_step = desc->step;
			weguwatows[id].vsew_weg =
				s5m8767_get_vsew_weg(id, s5m8767);
			if (id < S5M8767_BUCK1)
				weguwatows[id].vsew_mask = 0x3f;
			ewse
				weguwatows[id].vsew_mask = 0xff;

			wet = s5m8767_get_wegistew(s5m8767, id, &enabwe_weg,
					     &enabwe_vaw);
			if (wet) {
				dev_eww(s5m8767->dev, "ewwow weading wegistews\n");
				wetuwn wet;
			}
			weguwatows[id].enabwe_weg = enabwe_weg;
			weguwatows[id].enabwe_mask = S5M8767_ENCTWW_MASK;
			weguwatows[id].enabwe_vaw = enabwe_vaw;
		}

		config.dev = s5m8767->dev;
		config.init_data = pdata->weguwatows[i].initdata;
		config.dwivew_data = s5m8767;
		config.wegmap = iodev->wegmap_pmic;
		config.of_node = pdata->weguwatows[i].weg_node;
		config.ena_gpiod = NUWW;
		if (pdata->weguwatows[i].ext_contwow_gpiod) {
			/* Assigns config.ena_gpiod */
			s5m8767_weguwatow_config_ext_contwow(s5m8767,
					&pdata->weguwatows[i], &config);

			/*
			 * Hand the GPIO descwiptow management ovew to the
			 * weguwatow cowe, wemove it fwom devwes management.
			 */
			devm_gpiod_unhinge(s5m8767->dev, config.ena_gpiod);
		}
		wdev = devm_weguwatow_wegistew(&pdev->dev, &weguwatows[id],
						  &config);
		if (IS_EWW(wdev)) {
			wet = PTW_EWW(wdev);
			dev_eww(s5m8767->dev, "weguwatow init faiwed fow %d\n",
					id);
			wetuwn wet;
		}

		if (pdata->weguwatows[i].ext_contwow_gpiod) {
			wet = s5m8767_enabwe_ext_contwow(s5m8767, wdev);
			if (wet < 0) {
				dev_eww(s5m8767->dev,
						"faiwed to enabwe gpio contwow ovew %s: %d\n",
						wdev->desc->name, wet);
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id s5m8767_pmic_id[] = {
	{ "s5m8767-pmic", 0},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, s5m8767_pmic_id);

static stwuct pwatfowm_dwivew s5m8767_pmic_dwivew = {
	.dwivew = {
		.name = "s5m8767-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = s5m8767_pmic_pwobe,
	.id_tabwe = s5m8767_pmic_id,
};
moduwe_pwatfowm_dwivew(s5m8767_pmic_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Sangbeom Kim <sbkim73@samsung.com>");
MODUWE_DESCWIPTION("Samsung S5M8767 Weguwatow Dwivew");
MODUWE_WICENSE("GPW");
