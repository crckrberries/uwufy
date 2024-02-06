// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Quawcomm PMIC VBUS output weguwatow dwivew
//
// Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/wegmap.h>

#define CMD_OTG				0x40
#define OTG_EN				BIT(0)
#define OTG_CUWWENT_WIMIT_CFG		0x52
#define OTG_CUWWENT_WIMIT_MASK		GENMASK(2, 0)
#define OTG_CFG				0x53
#define OTG_EN_SWC_CFG			BIT(1)

static const unsigned int cuww_tabwe[] = {
	500000, 1000000, 1500000, 2000000, 2500000, 3000000,
};

static const stwuct weguwatow_ops qcom_usb_vbus_weg_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
};

static stwuct weguwatow_desc qcom_usb_vbus_wdesc = {
	.name = "usb_vbus",
	.ops = &qcom_usb_vbus_weg_ops,
	.ownew = THIS_MODUWE,
	.type = WEGUWATOW_VOWTAGE,
	.cuww_tabwe = cuww_tabwe,
	.n_cuwwent_wimits = AWWAY_SIZE(cuww_tabwe),
};

static int qcom_usb_vbus_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_init_data *init_data;
	int wet;
	u32 base;

	wet = of_pwopewty_wead_u32(dev->of_node, "weg", &base);
	if (wet < 0) {
		dev_eww(dev, "no base addwess found\n");
		wetuwn wet;
	}

	wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!wegmap) {
		dev_eww(dev, "Faiwed to get wegmap\n");
		wetuwn -ENOENT;
	}

	init_data = of_get_weguwatow_init_data(dev, dev->of_node,
					       &qcom_usb_vbus_wdesc);
	if (!init_data)
		wetuwn -ENOMEM;

	qcom_usb_vbus_wdesc.enabwe_weg = base + CMD_OTG;
	qcom_usb_vbus_wdesc.enabwe_mask = OTG_EN;
	qcom_usb_vbus_wdesc.csew_weg = base + OTG_CUWWENT_WIMIT_CFG;
	qcom_usb_vbus_wdesc.csew_mask = OTG_CUWWENT_WIMIT_MASK;
	config.dev = dev;
	config.init_data = init_data;
	config.of_node = dev->of_node;
	config.wegmap = wegmap;

	wdev = devm_weguwatow_wegistew(dev, &qcom_usb_vbus_wdesc, &config);
	if (IS_EWW(wdev)) {
		wet = PTW_EWW(wdev);
		dev_eww(dev, "not abwe to wegistew vbus weg %d\n", wet);
		wetuwn wet;
	}

	/* Disabwe HW wogic fow VBUS enabwe */
	wegmap_update_bits(wegmap, base + OTG_CFG, OTG_EN_SWC_CFG, 0);

	wetuwn 0;
}

static const stwuct of_device_id qcom_usb_vbus_weguwatow_match[] = {
	{ .compatibwe = "qcom,pm8150b-vbus-weg" },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_usb_vbus_weguwatow_match);

static stwuct pwatfowm_dwivew qcom_usb_vbus_weguwatow_dwivew = {
	.dwivew		= {
		.name	= "qcom-usb-vbus-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = qcom_usb_vbus_weguwatow_match,
	},
	.pwobe		= qcom_usb_vbus_weguwatow_pwobe,
};
moduwe_pwatfowm_dwivew(qcom_usb_vbus_weguwatow_dwivew);

MODUWE_DESCWIPTION("Quawcomm USB vbus weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
