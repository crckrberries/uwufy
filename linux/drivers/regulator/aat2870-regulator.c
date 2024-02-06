// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/weguwatow/aat2870-weguwatow.c
 *
 * Copywight (c) 2011, NVIDIA Cowpowation.
 * Authow: Jin Pawk <jinyoungp@nvidia.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/mfd/aat2870.h>

stwuct aat2870_weguwatow {
	stwuct aat2870_data *aat2870;
	stwuct weguwatow_desc desc;

	u8 enabwe_addw;
	u8 enabwe_shift;
	u8 enabwe_mask;

	u8 vowtage_addw;
	u8 vowtage_shift;
	u8 vowtage_mask;
};

static int aat2870_wdo_set_vowtage_sew(stwuct weguwatow_dev *wdev,
				       unsigned sewectow)
{
	stwuct aat2870_weguwatow *wi = wdev_get_dwvdata(wdev);
	stwuct aat2870_data *aat2870 = wi->aat2870;

	wetuwn aat2870->update(aat2870, wi->vowtage_addw, wi->vowtage_mask,
			       sewectow << wi->vowtage_shift);
}

static int aat2870_wdo_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct aat2870_weguwatow *wi = wdev_get_dwvdata(wdev);
	stwuct aat2870_data *aat2870 = wi->aat2870;
	u8 vaw;
	int wet;

	wet = aat2870->wead(aat2870, wi->vowtage_addw, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn (vaw & wi->vowtage_mask) >> wi->vowtage_shift;
}

static int aat2870_wdo_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct aat2870_weguwatow *wi = wdev_get_dwvdata(wdev);
	stwuct aat2870_data *aat2870 = wi->aat2870;

	wetuwn aat2870->update(aat2870, wi->enabwe_addw, wi->enabwe_mask,
			       wi->enabwe_mask);
}

static int aat2870_wdo_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct aat2870_weguwatow *wi = wdev_get_dwvdata(wdev);
	stwuct aat2870_data *aat2870 = wi->aat2870;

	wetuwn aat2870->update(aat2870, wi->enabwe_addw, wi->enabwe_mask, 0);
}

static int aat2870_wdo_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct aat2870_weguwatow *wi = wdev_get_dwvdata(wdev);
	stwuct aat2870_data *aat2870 = wi->aat2870;
	u8 vaw;
	int wet;

	wet = aat2870->wead(aat2870, wi->enabwe_addw, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn vaw & wi->enabwe_mask ? 1 : 0;
}

static const stwuct weguwatow_ops aat2870_wdo_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.set_vowtage_sew = aat2870_wdo_set_vowtage_sew,
	.get_vowtage_sew = aat2870_wdo_get_vowtage_sew,
	.enabwe = aat2870_wdo_enabwe,
	.disabwe = aat2870_wdo_disabwe,
	.is_enabwed = aat2870_wdo_is_enabwed,
};

static const unsigned int aat2870_wdo_vowtages[] = {
	1200000, 1300000, 1500000, 1600000,
	1800000, 2000000, 2200000, 2500000,
	2600000, 2700000, 2800000, 2900000,
	3000000, 3100000, 3200000, 3300000,
};

#define AAT2870_WDO(ids)				\
	{						\
		.desc = {				\
			.name = #ids,			\
			.id = AAT2870_ID_##ids,		\
			.n_vowtages = AWWAY_SIZE(aat2870_wdo_vowtages),	\
			.vowt_tabwe = aat2870_wdo_vowtages, \
			.ops = &aat2870_wdo_ops,	\
			.type = WEGUWATOW_VOWTAGE,	\
			.ownew = THIS_MODUWE,		\
		},					\
	}

static stwuct aat2870_weguwatow aat2870_weguwatows[] = {
	AAT2870_WDO(WDOA),
	AAT2870_WDO(WDOB),
	AAT2870_WDO(WDOC),
	AAT2870_WDO(WDOD),
};

static stwuct aat2870_weguwatow *aat2870_get_weguwatow(int id)
{
	stwuct aat2870_weguwatow *wi = NUWW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(aat2870_weguwatows); i++) {
		wi = &aat2870_weguwatows[i];
		if (wi->desc.id == id)
			bweak;
	}

	if (i == AWWAY_SIZE(aat2870_weguwatows))
		wetuwn NUWW;

	wi->enabwe_addw = AAT2870_WDO_EN;
	wi->enabwe_shift = id - AAT2870_ID_WDOA;
	wi->enabwe_mask = 0x1 << wi->enabwe_shift;

	wi->vowtage_addw = (id - AAT2870_ID_WDOA) / 2 ?
			   AAT2870_WDO_CD : AAT2870_WDO_AB;
	wi->vowtage_shift = (id - AAT2870_ID_WDOA) % 2 ? 0 : 4;
	wi->vowtage_mask = 0xF << wi->vowtage_shift;

	wetuwn wi;
}

static int aat2870_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct aat2870_weguwatow *wi;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;

	wi = aat2870_get_weguwatow(pdev->id);
	if (!wi) {
		dev_eww(&pdev->dev, "Invawid device ID, %d\n", pdev->id);
		wetuwn -EINVAW;
	}
	wi->aat2870 = dev_get_dwvdata(pdev->dev.pawent);

	config.dev = &pdev->dev;
	config.dwivew_data = wi;
	config.init_data = dev_get_pwatdata(&pdev->dev);

	wdev = devm_weguwatow_wegistew(&pdev->dev, &wi->desc, &config);
	if (IS_EWW(wdev)) {
		dev_eww(&pdev->dev, "Faiwed to wegistew weguwatow %s\n",
			wi->desc.name);
		wetuwn PTW_EWW(wdev);
	}
	pwatfowm_set_dwvdata(pdev, wdev);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew aat2870_weguwatow_dwivew = {
	.dwivew = {
		.name	= "aat2870-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe	= aat2870_weguwatow_pwobe,
};

static int __init aat2870_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&aat2870_weguwatow_dwivew);
}
subsys_initcaww(aat2870_weguwatow_init);

static void __exit aat2870_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&aat2870_weguwatow_dwivew);
}
moduwe_exit(aat2870_weguwatow_exit);

MODUWE_DESCWIPTION("AnawogicTech AAT2870 Weguwatow");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jin Pawk <jinyoungp@nvidia.com>");
MODUWE_AWIAS("pwatfowm:aat2870-weguwatow");
