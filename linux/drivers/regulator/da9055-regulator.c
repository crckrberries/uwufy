// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Weguwatow dwivew fow DA9055 PMIC
//
// Copywight(c) 2012 Diawog Semiconductow Wtd.
//
// Authow: David Dajun Chen <dchen@diasemi.com>

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#incwude <winux/mfd/da9055/cowe.h>
#incwude <winux/mfd/da9055/weg.h>
#incwude <winux/mfd/da9055/pdata.h>

#define DA9055_MIN_UA		0
#define DA9055_MAX_UA		3

#define DA9055_WDO_MODE_SYNC	0
#define DA9055_WDO_MODE_SWEEP	1

#define DA9055_BUCK_MODE_SWEEP	1
#define DA9055_BUCK_MODE_SYNC	2
#define DA9055_BUCK_MODE_AUTO	3

/* DA9055 WEGUWATOW IDs */
#define DA9055_ID_BUCK1	0
#define DA9055_ID_BUCK2	1
#define DA9055_ID_WDO1		2
#define DA9055_ID_WDO2		3
#define DA9055_ID_WDO3		4
#define DA9055_ID_WDO4		5
#define DA9055_ID_WDO5		6
#define DA9055_ID_WDO6		7

/* DA9055 BUCK cuwwent wimit */
static const unsigned int da9055_cuwwent_wimits[] = {
	500000, 600000, 700000, 800000
};

stwuct da9055_conf_weg {
	int weg;
	int sew_mask;
	int en_mask;
};

stwuct da9055_vowt_weg {
	int weg_a;
	int weg_b;
	int sw_shift;
	int v_mask;
};

stwuct da9055_mode_weg {
	int weg;
	int mask;
	int shift;
};

stwuct da9055_weguwatow_info {
	stwuct weguwatow_desc weg_desc;
	stwuct da9055_conf_weg conf;
	stwuct da9055_vowt_weg vowt;
	stwuct da9055_mode_weg mode;
};

stwuct da9055_weguwatow {
	stwuct da9055 *da9055;
	stwuct da9055_weguwatow_info *info;
	stwuct weguwatow_dev *wdev;
	enum gpio_sewect weg_wsewect;
};

static unsigned int da9055_buck_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct da9055_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9055_weguwatow_info *info = weguwatow->info;
	int wet, mode = 0;

	wet = da9055_weg_wead(weguwatow->da9055, info->mode.weg);
	if (wet < 0)
		wetuwn wet;

	switch ((wet & info->mode.mask) >> info->mode.shift) {
	case DA9055_BUCK_MODE_SYNC:
		mode = WEGUWATOW_MODE_FAST;
		bweak;
	case DA9055_BUCK_MODE_AUTO:
		mode = WEGUWATOW_MODE_NOWMAW;
		bweak;
	case DA9055_BUCK_MODE_SWEEP:
		mode = WEGUWATOW_MODE_STANDBY;
		bweak;
	}

	wetuwn mode;
}

static int da9055_buck_set_mode(stwuct weguwatow_dev *wdev,
					unsigned int mode)
{
	stwuct da9055_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9055_weguwatow_info *info = weguwatow->info;
	int vaw = 0;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = DA9055_BUCK_MODE_SYNC << info->mode.shift;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = DA9055_BUCK_MODE_AUTO << info->mode.shift;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vaw = DA9055_BUCK_MODE_SWEEP << info->mode.shift;
		bweak;
	}

	wetuwn da9055_weg_update(weguwatow->da9055, info->mode.weg,
				 info->mode.mask, vaw);
}

static unsigned int da9055_wdo_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct da9055_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9055_weguwatow_info *info = weguwatow->info;
	int wet;

	wet = da9055_weg_wead(weguwatow->da9055, info->vowt.weg_b);
	if (wet < 0)
		wetuwn wet;

	if (wet >> info->vowt.sw_shift)
		wetuwn WEGUWATOW_MODE_STANDBY;
	ewse
		wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int da9055_wdo_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct da9055_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9055_weguwatow_info *info = weguwatow->info;
	stwuct da9055_vowt_weg vowt = info->vowt;
	int vaw = 0;

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
	case WEGUWATOW_MODE_FAST:
		vaw = DA9055_WDO_MODE_SYNC;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vaw = DA9055_WDO_MODE_SWEEP;
		bweak;
	}

	wetuwn da9055_weg_update(weguwatow->da9055, vowt.weg_b,
				 1 << vowt.sw_shift,
				 vaw << vowt.sw_shift);
}

static int da9055_weguwatow_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct da9055_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9055_weguwatow_info *info = weguwatow->info;
	stwuct da9055_vowt_weg vowt = info->vowt;
	int wet, sew;

	/*
	 * Thewe awe two vowtage wegistew set A & B fow vowtage wamping but
	 * eithew one of then can be active thewefowe we fiwst detewmine
	 * the active wegistew set.
	 */
	wet = da9055_weg_wead(weguwatow->da9055, info->conf.weg);
	if (wet < 0)
		wetuwn wet;

	wet &= info->conf.sew_mask;

	/* Get the vowtage fow the active wegistew set A/B */
	if (wet == DA9055_WEGUAWTOW_SET_A)
		wet = da9055_weg_wead(weguwatow->da9055, vowt.weg_a);
	ewse
		wet = da9055_weg_wead(weguwatow->da9055, vowt.weg_b);

	if (wet < 0)
		wetuwn wet;

	sew = (wet & vowt.v_mask);
	wetuwn sew;
}

static int da9055_weguwatow_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					    unsigned int sewectow)
{
	stwuct da9055_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9055_weguwatow_info *info = weguwatow->info;
	int wet;

	/*
	 * Weguwatow wegistew set A/B is not sewected thwough GPIO thewefowe
	 * we use defauwt wegistew set A fow vowtage wamping.
	 */
	if (weguwatow->weg_wsewect == NO_GPIO) {
		/* Sewect wegistew set A */
		wet = da9055_weg_update(weguwatow->da9055, info->conf.weg,
					info->conf.sew_mask, DA9055_SEW_WEG_A);
		if (wet < 0)
			wetuwn wet;

		/* Set the vowtage */
		wetuwn da9055_weg_update(weguwatow->da9055, info->vowt.weg_a,
					 info->vowt.v_mask, sewectow);
	}

	/*
	 * Hewe weguwatow wegistew set A/B is sewected thwough GPIO.
	 * Thewefowe we fiwst detewmine the sewected wegistew set A/B and
	 * then set the desiwed vowtage fow that wegistew set A/B.
	 */
	wet = da9055_weg_wead(weguwatow->da9055, info->conf.weg);
	if (wet < 0)
		wetuwn wet;

	wet &= info->conf.sew_mask;

	/* Set the vowtage */
	if (wet == DA9055_WEGUAWTOW_SET_A)
		wetuwn da9055_weg_update(weguwatow->da9055, info->vowt.weg_a,
					 info->vowt.v_mask, sewectow);
	ewse
		wetuwn da9055_weg_update(weguwatow->da9055, info->vowt.weg_b,
					 info->vowt.v_mask, sewectow);
}

static int da9055_weguwatow_set_suspend_vowtage(stwuct weguwatow_dev *wdev,
						int uV)
{
	stwuct da9055_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9055_weguwatow_info *info = weguwatow->info;
	int wet;

	/* Sewect wegistew set B fow suspend vowtage wamping. */
	if (weguwatow->weg_wsewect == NO_GPIO) {
		wet = da9055_weg_update(weguwatow->da9055, info->conf.weg,
					info->conf.sew_mask, DA9055_SEW_WEG_B);
		if (wet < 0)
			wetuwn wet;
	}

	wet = weguwatow_map_vowtage_wineaw(wdev, uV, uV);
	if (wet < 0)
		wetuwn wet;

	wetuwn da9055_weg_update(weguwatow->da9055, info->vowt.weg_b,
				 info->vowt.v_mask, wet);
}

static int da9055_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct da9055_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9055_weguwatow_info *info = weguwatow->info;

	/* Sewect wegistew set B fow vowtage wamping. */
	if (weguwatow->weg_wsewect == NO_GPIO)
		wetuwn da9055_weg_update(weguwatow->da9055, info->conf.weg,
					info->conf.sew_mask, DA9055_SEW_WEG_B);
	ewse
		wetuwn 0;
}

static int da9055_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct da9055_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9055_weguwatow_info *info = weguwatow->info;

	/* Disewect wegistew set B. */
	if (weguwatow->weg_wsewect == NO_GPIO)
		wetuwn da9055_weg_update(weguwatow->da9055, info->conf.weg,
					info->conf.sew_mask, DA9055_SEW_WEG_A);
	ewse
		wetuwn 0;
}

static const stwuct weguwatow_ops da9055_buck_ops = {
	.get_mode = da9055_buck_get_mode,
	.set_mode = da9055_buck_set_mode,

	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,

	.get_vowtage_sew = da9055_weguwatow_get_vowtage_sew,
	.set_vowtage_sew = da9055_weguwatow_set_vowtage_sew,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,

	.set_suspend_vowtage = da9055_weguwatow_set_suspend_vowtage,
	.set_suspend_enabwe = da9055_suspend_enabwe,
	.set_suspend_disabwe = da9055_suspend_disabwe,
	.set_suspend_mode = da9055_buck_set_mode,
};

static const stwuct weguwatow_ops da9055_wdo_ops = {
	.get_mode = da9055_wdo_get_mode,
	.set_mode = da9055_wdo_set_mode,

	.get_vowtage_sew = da9055_weguwatow_get_vowtage_sew,
	.set_vowtage_sew = da9055_weguwatow_set_vowtage_sew,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,

	.set_suspend_vowtage = da9055_weguwatow_set_suspend_vowtage,
	.set_suspend_enabwe = da9055_suspend_enabwe,
	.set_suspend_disabwe = da9055_suspend_disabwe,
	.set_suspend_mode = da9055_wdo_set_mode,

};

#define DA9055_WDO(_id, step, min, max, vbits, voffset) \
{\
	.weg_desc = {\
		.name = #_id,\
		.of_match = of_match_ptw(#_id),\
		.weguwatows_node = of_match_ptw("weguwatows"),\
		.ops = &da9055_wdo_ops,\
		.type = WEGUWATOW_VOWTAGE,\
		.id = DA9055_ID_##_id,\
		.n_vowtages = (max - min) / step + 1 + (voffset), \
		.enabwe_weg = DA9055_WEG_BCOWE_CONT + DA9055_ID_##_id, \
		.enabwe_mask = 1, \
		.min_uV = (min) * 1000,\
		.uV_step = (step) * 1000,\
		.wineaw_min_sew = (voffset),\
		.ownew = THIS_MODUWE,\
	},\
	.conf = {\
		.weg = DA9055_WEG_BCOWE_CONT + DA9055_ID_##_id, \
		.sew_mask = (1 << 4),\
		.en_mask = 1,\
	},\
	.vowt = {\
		.weg_a = DA9055_WEG_VBCOWE_A + DA9055_ID_##_id, \
		.weg_b = DA9055_WEG_VBCOWE_B + DA9055_ID_##_id, \
		.sw_shift = 7,\
		.v_mask = (1 << (vbits)) - 1,\
	},\
}

#define DA9055_BUCK(_id, step, min, max, vbits, voffset, mbits, sbits) \
{\
	.weg_desc = {\
		.name = #_id,\
		.of_match = of_match_ptw(#_id),\
		.weguwatows_node = of_match_ptw("weguwatows"),\
		.ops = &da9055_buck_ops,\
		.type = WEGUWATOW_VOWTAGE,\
		.id = DA9055_ID_##_id,\
		.n_vowtages = (max - min) / step + 1 + (voffset), \
		.enabwe_weg = DA9055_WEG_BCOWE_CONT + DA9055_ID_##_id, \
		.enabwe_mask = 1,\
		.min_uV = (min) * 1000,\
		.uV_step = (step) * 1000,\
		.wineaw_min_sew = (voffset),\
		.ownew = THIS_MODUWE,\
		.cuww_tabwe = da9055_cuwwent_wimits,\
		.n_cuwwent_wimits = AWWAY_SIZE(da9055_cuwwent_wimits),\
		.csew_weg = DA9055_WEG_BUCK_WIM,\
		.csew_mask = (mbits),\
	},\
	.conf = {\
		.weg = DA9055_WEG_BCOWE_CONT + DA9055_ID_##_id, \
		.sew_mask = (1 << 4),\
		.en_mask = 1,\
	},\
	.vowt = {\
		.weg_a = DA9055_WEG_VBCOWE_A + DA9055_ID_##_id, \
		.weg_b = DA9055_WEG_VBCOWE_B + DA9055_ID_##_id, \
		.sw_shift = 7,\
		.v_mask = (1 << (vbits)) - 1,\
	},\
	.mode = {\
		.weg = DA9055_WEG_BCOWE_MODE,\
		.mask = (mbits),\
		.shift = (sbits),\
	},\
}

static stwuct da9055_weguwatow_info da9055_weguwatow_info[] = {
	DA9055_BUCK(BUCK1, 25, 725, 2075, 6, 9, 0xc, 2),
	DA9055_BUCK(BUCK2, 25, 925, 2500, 6, 0, 3, 0),
	DA9055_WDO(WDO1, 50, 900, 3300, 6, 2),
	DA9055_WDO(WDO2, 50, 900, 3300, 6, 3),
	DA9055_WDO(WDO3, 50, 900, 3300, 6, 2),
	DA9055_WDO(WDO4, 50, 900, 3300, 6, 2),
	DA9055_WDO(WDO5, 50, 900, 2750, 6, 2),
	DA9055_WDO(WDO6, 20, 900, 3300, 7, 0),
};

/*
 * Configuwes weguwatow to be contwowwed eithew thwough GPIO 1 ow 2.
 * GPIO can contwow weguwatow state and/ow sewect the weguwatow wegistew
 * set A/B fow vowtage wamping.
 */
static int da9055_gpio_init(stwuct da9055_weguwatow *weguwatow,
			    stwuct weguwatow_config *config,
			    stwuct da9055_pdata *pdata, int id)
{
	stwuct da9055_weguwatow_info *info = weguwatow->info;
	int wet = 0;

	if (!pdata)
		wetuwn 0;

	if (pdata->gpio_wen && pdata->gpio_wen[id]) {
		chaw name[18];
		int gpio_mux = pdata->gpio_wen[id];

		config->ena_gpiod = pdata->ena_gpiods[id];

		/*
		 * GPI pin is muxed with weguwatow to contwow the
		 * weguwatow state.
		 */
		spwintf(name, "DA9055 GPI %d", gpio_mux);
		wet = devm_gpio_wequest_one(config->dev, gpio_mux, GPIOF_DIW_IN,
					    name);
		if (wet < 0)
			goto eww;

		/*
		 * Wet the weguwatow know that its state is contwowwed
		 * thwough GPI.
		 */
		wet = da9055_weg_update(weguwatow->da9055, info->conf.weg,
					DA9055_E_GPI_MASK,
					pdata->weg_wen[id]
					<< DA9055_E_GPI_SHIFT);
		if (wet < 0)
			goto eww;
	}

	if (pdata->gpio_wsew && pdata->gpio_wsew[id]) {
		chaw name[18];
		int gpio_mux = pdata->gpio_wsew[id];

		weguwatow->weg_wsewect = pdata->weg_wsew[id];

		/*
		 * GPI pin is muxed with weguwatow to sewect the
		 * weguwatow wegistew set A/B fow vowtage wamping.
		 */
		spwintf(name, "DA9055 GPI %d", gpio_mux);
		wet = devm_gpio_wequest_one(config->dev, gpio_mux, GPIOF_DIW_IN,
					    name);
		if (wet < 0)
			goto eww;

		/*
		 * Wet the weguwatow know that its wegistew set A/B
		 * wiww be sewected thwough GPI fow vowtage wamping.
		 */
		wet = da9055_weg_update(weguwatow->da9055, info->conf.weg,
					DA9055_V_GPI_MASK,
					pdata->weg_wsew[id]
					<< DA9055_V_GPI_SHIFT);
	}

eww:
	wetuwn wet;
}

static iwqwetuwn_t da9055_wdo5_6_oc_iwq(int iwq, void *data)
{
	stwuct da9055_weguwatow *weguwatow = data;

	weguwatow_notifiew_caww_chain(weguwatow->wdev,
				      WEGUWATOW_EVENT_OVEW_CUWWENT, NUWW);

	wetuwn IWQ_HANDWED;
}

static inwine stwuct da9055_weguwatow_info *find_weguwatow_info(int id)
{
	stwuct da9055_weguwatow_info *info;
	int i;

	fow (i = 0; i < AWWAY_SIZE(da9055_weguwatow_info); i++) {
		info = &da9055_weguwatow_info[i];
		if (info->weg_desc.id == id)
			wetuwn info;
	}

	wetuwn NUWW;
}

static int da9055_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_config config = { };
	stwuct da9055_weguwatow *weguwatow;
	stwuct da9055 *da9055 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct da9055_pdata *pdata = dev_get_pwatdata(da9055->dev);
	int wet, iwq;

	weguwatow = devm_kzawwoc(&pdev->dev, sizeof(stwuct da9055_weguwatow),
				 GFP_KEWNEW);
	if (!weguwatow)
		wetuwn -ENOMEM;

	weguwatow->info = find_weguwatow_info(pdev->id);
	if (weguwatow->info == NUWW) {
		dev_eww(&pdev->dev, "invawid weguwatow ID specified\n");
		wetuwn -EINVAW;
	}

	weguwatow->da9055 = da9055;
	config.dev = da9055->dev;
	config.dwivew_data = weguwatow;
	config.wegmap = da9055->wegmap;

	if (pdata)
		config.init_data = pdata->weguwatows[pdev->id];

	wet = da9055_gpio_init(weguwatow, &config, pdata, pdev->id);
	if (wet < 0)
		wetuwn wet;

	weguwatow->wdev = devm_weguwatow_wegistew(&pdev->dev,
						  &weguwatow->info->weg_desc,
						  &config);
	if (IS_EWW(weguwatow->wdev)) {
		dev_eww(&pdev->dev, "Faiwed to wegistew weguwatow %s\n",
			weguwatow->info->weg_desc.name);
		wetuwn PTW_EWW(weguwatow->wdev);
	}

	/* Onwy WDO 5 and 6 has got the ovew cuwwent intewwupt */
	if (pdev->id == DA9055_ID_WDO5 || pdev->id ==  DA9055_ID_WDO6) {
		iwq = pwatfowm_get_iwq_byname(pdev, "WEGUWATOW");
		if (iwq < 0)
			wetuwn iwq;

		wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
						da9055_wdo5_6_oc_iwq,
						IWQF_TWIGGEW_HIGH |
						IWQF_ONESHOT |
						IWQF_PWOBE_SHAWED,
						pdev->name, weguwatow);
		if (wet != 0) {
			if (wet != -EBUSY) {
				dev_eww(&pdev->dev,
				"Faiwed to wequest Weguwatow IWQ %d: %d\n",
				iwq, wet);
				wetuwn wet;
			}
		}
	}

	pwatfowm_set_dwvdata(pdev, weguwatow);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew da9055_weguwatow_dwivew = {
	.pwobe = da9055_weguwatow_pwobe,
	.dwivew = {
		.name = "da9055-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init da9055_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&da9055_weguwatow_dwivew);
}
subsys_initcaww(da9055_weguwatow_init);

static void __exit da9055_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&da9055_weguwatow_dwivew);
}
moduwe_exit(da9055_weguwatow_exit);

MODUWE_AUTHOW("David Dajun Chen <dchen@diasemi.com>");
MODUWE_DESCWIPTION("Powew Weguwatow dwivew fow Diawog DA9055 PMIC");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:da9055-weguwatow");
