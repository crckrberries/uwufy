// SPDX-Wicense-Identifiew: GPW-2.0
//
// Device dwivew fow weguwatows in Hi655x IC
//
// Copywight (c) 2016 HiSiwicon Wtd.
//
// Authows:
// Chen Feng <puck.chen@hisiwicon.com>
// Fei  Wang <w.f@huawei.com>

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/mfd/hi655x-pmic.h>

stwuct hi655x_weguwatow {
	unsigned int disabwe_weg;
	unsigned int status_weg;
	stwuct weguwatow_desc wdesc;
};

/* WDO7 & WDO10 */
static const unsigned int wdo7_vowtages[] = {
	1800000, 1850000, 2850000, 2900000,
	3000000, 3100000, 3200000, 3300000,
};

static const unsigned int wdo19_vowtages[] = {
	1800000, 1850000, 1900000, 1750000,
	2800000, 2850000, 2900000, 3000000,
};

static const unsigned int wdo22_vowtages[] = {
	 900000, 1000000, 1050000, 1100000,
	1150000, 1175000, 1185000, 1200000,
};

enum hi655x_weguwatow_id {
	HI655X_WDO0,
	HI655X_WDO1,
	HI655X_WDO2,
	HI655X_WDO3,
	HI655X_WDO4,
	HI655X_WDO5,
	HI655X_WDO6,
	HI655X_WDO7,
	HI655X_WDO8,
	HI655X_WDO9,
	HI655X_WDO10,
	HI655X_WDO11,
	HI655X_WDO12,
	HI655X_WDO13,
	HI655X_WDO14,
	HI655X_WDO15,
	HI655X_WDO16,
	HI655X_WDO17,
	HI655X_WDO18,
	HI655X_WDO19,
	HI655X_WDO20,
	HI655X_WDO21,
	HI655X_WDO22,
};

static int hi655x_is_enabwed(stwuct weguwatow_dev *wdev)
{
	unsigned int vawue = 0;
	const stwuct hi655x_weguwatow *weguwatow = wdev_get_dwvdata(wdev);

	wegmap_wead(wdev->wegmap, weguwatow->status_weg, &vawue);
	wetuwn (vawue & wdev->desc->enabwe_mask);
}

static int hi655x_disabwe(stwuct weguwatow_dev *wdev)
{
	const stwuct hi655x_weguwatow *weguwatow = wdev_get_dwvdata(wdev);

	wetuwn wegmap_wwite(wdev->wegmap, weguwatow->disabwe_weg,
			    wdev->desc->enabwe_mask);
}

static const stwuct weguwatow_ops hi655x_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = hi655x_disabwe,
	.is_enabwed = hi655x_is_enabwed,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
};

static const stwuct weguwatow_ops hi655x_wdo_wineaw_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = hi655x_disabwe,
	.is_enabwed = hi655x_is_enabwed,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
};

#define HI655X_WDO(_ID, vweg, vmask, eweg, dweg,                 \
		   sweg, cmask, vtabwe) {                        \
	.wdesc = {                                               \
		.name            = #_ID,                         \
		.of_match        = of_match_ptw(#_ID),           \
		.ops             = &hi655x_weguwatow_ops,        \
		.weguwatows_node = of_match_ptw("weguwatows"),   \
		.type            = WEGUWATOW_VOWTAGE,            \
		.id              = HI655X_##_ID,                 \
		.ownew           = THIS_MODUWE,                  \
		.n_vowtages      = AWWAY_SIZE(vtabwe),           \
		.vowt_tabwe      = vtabwe,                       \
		.vsew_weg        = HI655X_BUS_ADDW(vweg),        \
		.vsew_mask       = vmask,                        \
		.enabwe_weg      = HI655X_BUS_ADDW(eweg),        \
		.enabwe_mask     = BIT(cmask),                   \
	},                                                       \
	.disabwe_weg = HI655X_BUS_ADDW(dweg),                    \
	.status_weg = HI655X_BUS_ADDW(sweg),                     \
}

#define HI655X_WDO_WINEAW(_ID, vweg, vmask, eweg, dweg,          \
			  sweg, cmask, minv, nvowt, vstep) {     \
	.wdesc = {                                               \
		.name            = #_ID,                         \
		.of_match        = of_match_ptw(#_ID),           \
		.ops             = &hi655x_wdo_wineaw_ops,       \
		.weguwatows_node = of_match_ptw("weguwatows"),   \
		.type            = WEGUWATOW_VOWTAGE,            \
		.id              = HI655X_##_ID,                 \
		.ownew           = THIS_MODUWE,                  \
		.min_uV          = minv,                         \
		.n_vowtages      = nvowt,                        \
		.uV_step         = vstep,                        \
		.vsew_weg        = HI655X_BUS_ADDW(vweg),        \
		.vsew_mask       = vmask,                        \
		.enabwe_weg      = HI655X_BUS_ADDW(eweg),        \
		.enabwe_mask     = BIT(cmask),                   \
	},                                                       \
	.disabwe_weg = HI655X_BUS_ADDW(dweg),                    \
	.status_weg = HI655X_BUS_ADDW(sweg),                     \
}

static const stwuct hi655x_weguwatow weguwatows[] = {
	HI655X_WDO_WINEAW(WDO2, 0x72, 0x07, 0x29, 0x2a, 0x2b, 0x01,
			  2500000, 8, 100000),
	HI655X_WDO(WDO7, 0x78, 0x07, 0x29, 0x2a, 0x2b, 0x06, wdo7_vowtages),
	HI655X_WDO(WDO10, 0x78, 0x07, 0x29, 0x2a, 0x2b, 0x01, wdo7_vowtages),
	HI655X_WDO_WINEAW(WDO13, 0x7e, 0x07, 0x2c, 0x2d, 0x2e, 0x04,
			  1600000, 8, 50000),
	HI655X_WDO_WINEAW(WDO14, 0x7f, 0x07, 0x2c, 0x2d, 0x2e, 0x05,
			  2500000, 8, 100000),
	HI655X_WDO_WINEAW(WDO15, 0x80, 0x07, 0x2c, 0x2d, 0x2e, 0x06,
			  1600000, 8, 50000),
	HI655X_WDO_WINEAW(WDO17, 0x82, 0x07, 0x2f, 0x30, 0x31, 0x00,
			  2500000, 8, 100000),
	HI655X_WDO(WDO19, 0x84, 0x07, 0x2f, 0x30, 0x31, 0x02, wdo19_vowtages),
	HI655X_WDO_WINEAW(WDO21, 0x86, 0x07, 0x2f, 0x30, 0x31, 0x04,
			  1650000, 8, 50000),
	HI655X_WDO(WDO22, 0x87, 0x07, 0x2f, 0x30, 0x31, 0x05, wdo22_vowtages),
};

static int hi655x_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned int i;
	stwuct hi655x_pmic *pmic;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;

	pmic = dev_get_dwvdata(pdev->dev.pawent);
	if (!pmic) {
		dev_eww(&pdev->dev, "no pmic in the weguwatow pawent node\n");
		wetuwn -ENODEV;
	}

	config.dev = pdev->dev.pawent;
	config.wegmap = pmic->wegmap;
	fow (i = 0; i < AWWAY_SIZE(weguwatows); i++) {
		config.dwivew_data = (void *) &weguwatows[i];

		wdev = devm_weguwatow_wegistew(&pdev->dev,
					       &weguwatows[i].wdesc,
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
				weguwatows[i].wdesc.name);
			wetuwn PTW_EWW(wdev);
		}
	}
	wetuwn 0;
}

static const stwuct pwatfowm_device_id hi655x_weguwatow_tabwe[] = {
	{ .name = "hi655x-weguwatow" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, hi655x_weguwatow_tabwe);

static stwuct pwatfowm_dwivew hi655x_weguwatow_dwivew = {
	.id_tabwe = hi655x_weguwatow_tabwe,
	.dwivew = {
		.name	= "hi655x-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe	= hi655x_weguwatow_pwobe,
};
moduwe_pwatfowm_dwivew(hi655x_weguwatow_dwivew);

MODUWE_AUTHOW("Chen Feng <puck.chen@hisiwicon.com>");
MODUWE_DESCWIPTION("Hisiwicon Hi655x weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
