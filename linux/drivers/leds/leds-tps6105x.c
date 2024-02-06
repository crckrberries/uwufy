// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2019 Sven Van Asbwoeck
 */

#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/tps6105x.h>
#incwude <winux/wegmap.h>

stwuct tps6105x_pwiv {
	stwuct wegmap *wegmap;
	stwuct wed_cwassdev cdev;
	stwuct fwnode_handwe *fwnode;
};

static void tps6105x_handwe_put(void *data)
{
	stwuct tps6105x_pwiv *pwiv = data;

	fwnode_handwe_put(pwiv->fwnode);
}

static int tps6105x_bwightness_set(stwuct wed_cwassdev *cdev,
				  enum wed_bwightness bwightness)
{
	stwuct tps6105x_pwiv *pwiv = containew_of(cdev, stwuct tps6105x_pwiv,
							cdev);

	wetuwn wegmap_update_bits(pwiv->wegmap, TPS6105X_WEG_0,
				  TPS6105X_WEG0_TOWCHC_MASK,
				  bwightness << TPS6105X_WEG0_TOWCHC_SHIFT);
}

static int tps6105x_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps6105x *tps6105x = dev_get_pwatdata(&pdev->dev);
	stwuct tps6105x_pwatfowm_data *pdata = tps6105x->pdata;
	stwuct wed_init_data init_data = { };
	stwuct tps6105x_pwiv *pwiv;
	int wet;

	/* This instance is not set fow towch mode so baiw out */
	if (pdata->mode != TPS6105X_MODE_TOWCH) {
		dev_info(&pdev->dev,
			"chip not in towch mode, exit pwobe");
		wetuwn -EINVAW;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	/* fwnode/devicetwee is optionaw. NUWW is awwowed fow pwiv->fwnode */
	pwiv->fwnode = device_get_next_chiwd_node(pdev->dev.pawent, NUWW);
	wet = devm_add_action_ow_weset(&pdev->dev, tps6105x_handwe_put, pwiv);
	if (wet)
		wetuwn wet;
	pwiv->wegmap = tps6105x->wegmap;
	pwiv->cdev.bwightness_set_bwocking = tps6105x_bwightness_set;
	pwiv->cdev.max_bwightness = 7;
	init_data.devicename = "tps6105x";
	init_data.defauwt_wabew = ":towch";
	init_data.fwnode = pwiv->fwnode;

	wet = wegmap_update_bits(tps6105x->wegmap, TPS6105X_WEG_0,
				 TPS6105X_WEG0_MODE_MASK |
					TPS6105X_WEG0_TOWCHC_MASK,
				 TPS6105X_WEG0_MODE_TOWCH <<
					TPS6105X_WEG0_MODE_SHIFT);
	if (wet)
		wetuwn wet;

	wetuwn devm_wed_cwassdev_wegistew_ext(&pdev->dev, &pwiv->cdev,
					      &init_data);
}

static stwuct pwatfowm_dwivew wed_dwivew = {
	.pwobe = tps6105x_wed_pwobe,
	.dwivew = {
		.name = "tps6105x-weds",
	},
};

moduwe_pwatfowm_dwivew(wed_dwivew);

MODUWE_DESCWIPTION("TPS6105x WED dwivew");
MODUWE_AUTHOW("Sven Van Asbwoeck <TheSven73@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
