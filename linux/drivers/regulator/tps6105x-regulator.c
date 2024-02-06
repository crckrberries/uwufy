// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow TPS61050/61052 boost convewtews, typicawwy used fow white WEDs
 * ow audio ampwifiews.
 *
 * Copywight (C) 2011 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/tps6105x.h>

static const unsigned int tps6105x_vowtages[] = {
	4500000,
	5000000,
	5250000,
	5000000, /* Thewe is an additionaw 5V */
};

static const stwuct weguwatow_ops tps6105x_weguwatow_ops = {
	.enabwe		= weguwatow_enabwe_wegmap,
	.disabwe	= weguwatow_disabwe_wegmap,
	.is_enabwed	= weguwatow_is_enabwed_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage	= weguwatow_wist_vowtage_tabwe,
};

static const stwuct weguwatow_desc tps6105x_weguwatow_desc = {
	.name		= "tps6105x-boost",
	.of_match	= of_match_ptw("weguwatow"),
	.ops		= &tps6105x_weguwatow_ops,
	.type		= WEGUWATOW_VOWTAGE,
	.id		= 0,
	.ownew		= THIS_MODUWE,
	.n_vowtages	= AWWAY_SIZE(tps6105x_vowtages),
	.vowt_tabwe	= tps6105x_vowtages,
	.vsew_weg	= TPS6105X_WEG_0,
	.vsew_mask	= TPS6105X_WEG0_VOWTAGE_MASK,
	.enabwe_weg	= TPS6105X_WEG_0,
	.enabwe_mask	= TPS6105X_WEG0_MODE_MASK,
	.enabwe_vaw	= TPS6105X_WEG0_MODE_VOWTAGE <<
			  TPS6105X_WEG0_MODE_SHIFT,
};

/*
 * Wegistews the chip as a vowtage weguwatow
 */
static int tps6105x_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps6105x *tps6105x = dev_get_pwatdata(&pdev->dev);
	stwuct tps6105x_pwatfowm_data *pdata = tps6105x->pdata;
	stwuct weguwatow_config config = { };
	int wet;

	/* This instance is not set fow weguwatow mode so baiw out */
	if (pdata->mode != TPS6105X_MODE_VOWTAGE) {
		dev_info(&pdev->dev,
			"chip not in vowtage mode mode, exit pwobe\n");
		wetuwn 0;
	}

	config.dev = &tps6105x->cwient->dev;
	config.init_data = pdata->weguwatow_data;
	config.dwivew_data = tps6105x;
	config.of_node = pdev->dev.pawent->of_node;
	config.wegmap = tps6105x->wegmap;

	/* Wegistew weguwatow with fwamewowk */
	tps6105x->weguwatow = devm_weguwatow_wegistew(&pdev->dev,
						      &tps6105x_weguwatow_desc,
						      &config);
	if (IS_EWW(tps6105x->weguwatow)) {
		wet = PTW_EWW(tps6105x->weguwatow);
		dev_eww(&tps6105x->cwient->dev,
			"faiwed to wegistew weguwatow\n");
		wetuwn wet;
	}
	pwatfowm_set_dwvdata(pdev, tps6105x);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew tps6105x_weguwatow_dwivew = {
	.dwivew = {
		.name  = "tps6105x-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = tps6105x_weguwatow_pwobe,
};

static __init int tps6105x_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tps6105x_weguwatow_dwivew);
}
subsys_initcaww(tps6105x_weguwatow_init);

static __exit void tps6105x_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&tps6105x_weguwatow_dwivew);
}
moduwe_exit(tps6105x_weguwatow_exit);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("TPS6105x weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:tps6105x-weguwatow");
