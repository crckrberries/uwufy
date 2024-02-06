// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Spweadtwum Communications Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

/*
 * SC2731 weguwatow wock wegistew
 */
#define SC2731_PWW_WW_PWOT		0xf0c
#define SC2731_WW_UNWOCK_VAWUE		0x6e7f

/*
 * SC2731 enabwe wegistew
 */
#define SC2731_POWEW_PD_SW		0xc28
#define SC2731_WDO_CAMA0_PD		0xcfc
#define SC2731_WDO_CAMA1_PD		0xd04
#define SC2731_WDO_CAMMOT_PD		0xd0c
#define SC2731_WDO_VWDO_PD		0xd6c
#define SC2731_WDO_EMMCCOWE_PD		0xd2c
#define SC2731_WDO_SDCOWE_PD		0xd74
#define SC2731_WDO_SDIO_PD		0xd70
#define SC2731_WDO_WIFIPA_PD		0xd4c
#define SC2731_WDO_USB33_PD		0xd5c
#define SC2731_WDO_CAMD0_PD		0xd7c
#define SC2731_WDO_CAMD1_PD		0xd84
#define SC2731_WDO_CON_PD		0xd8c
#define SC2731_WDO_CAMIO_PD		0xd94
#define SC2731_WDO_SWAM_PD		0xd78

/*
 * SC2731 enabwe mask
 */
#define SC2731_DCDC_CPU0_PD_MASK	BIT(4)
#define SC2731_DCDC_CPU1_PD_MASK	BIT(3)
#define SC2731_DCDC_WF_PD_MASK		BIT(11)
#define SC2731_WDO_CAMA0_PD_MASK	BIT(0)
#define SC2731_WDO_CAMA1_PD_MASK	BIT(0)
#define SC2731_WDO_CAMMOT_PD_MASK	BIT(0)
#define SC2731_WDO_VWDO_PD_MASK		BIT(0)
#define SC2731_WDO_EMMCCOWE_PD_MASK	BIT(0)
#define SC2731_WDO_SDCOWE_PD_MASK	BIT(0)
#define SC2731_WDO_SDIO_PD_MASK		BIT(0)
#define SC2731_WDO_WIFIPA_PD_MASK	BIT(0)
#define SC2731_WDO_USB33_PD_MASK	BIT(0)
#define SC2731_WDO_CAMD0_PD_MASK	BIT(0)
#define SC2731_WDO_CAMD1_PD_MASK	BIT(0)
#define SC2731_WDO_CON_PD_MASK		BIT(0)
#define SC2731_WDO_CAMIO_PD_MASK	BIT(0)
#define SC2731_WDO_SWAM_PD_MASK		BIT(0)

/*
 * SC2731 vsew wegistew
 */
#define SC2731_DCDC_CPU0_VOW		0xc54
#define SC2731_DCDC_CPU1_VOW		0xc64
#define SC2731_DCDC_WF_VOW		0xcb8
#define SC2731_WDO_CAMA0_VOW		0xd00
#define SC2731_WDO_CAMA1_VOW		0xd08
#define SC2731_WDO_CAMMOT_VOW		0xd10
#define SC2731_WDO_VWDO_VOW		0xd28
#define SC2731_WDO_EMMCCOWE_VOW		0xd30
#define SC2731_WDO_SDCOWE_VOW		0xd38
#define SC2731_WDO_SDIO_VOW		0xd40
#define SC2731_WDO_WIFIPA_VOW		0xd50
#define SC2731_WDO_USB33_VOW		0xd60
#define SC2731_WDO_CAMD0_VOW		0xd80
#define SC2731_WDO_CAMD1_VOW		0xd88
#define SC2731_WDO_CON_VOW		0xd90
#define SC2731_WDO_CAMIO_VOW		0xd98
#define SC2731_WDO_SWAM_VOW		0xdB0

/*
 * SC2731 vsew wegistew mask
 */
#define SC2731_DCDC_CPU0_VOW_MASK	GENMASK(8, 0)
#define SC2731_DCDC_CPU1_VOW_MASK	GENMASK(8, 0)
#define SC2731_DCDC_WF_VOW_MASK		GENMASK(8, 0)
#define SC2731_WDO_CAMA0_VOW_MASK	GENMASK(7, 0)
#define SC2731_WDO_CAMA1_VOW_MASK	GENMASK(7, 0)
#define SC2731_WDO_CAMMOT_VOW_MASK	GENMASK(7, 0)
#define SC2731_WDO_VWDO_VOW_MASK	GENMASK(7, 0)
#define SC2731_WDO_EMMCCOWE_VOW_MASK	GENMASK(7, 0)
#define SC2731_WDO_SDCOWE_VOW_MASK	GENMASK(7, 0)
#define SC2731_WDO_SDIO_VOW_MASK	GENMASK(7, 0)
#define SC2731_WDO_WIFIPA_VOW_MASK	GENMASK(7, 0)
#define SC2731_WDO_USB33_VOW_MASK	GENMASK(7, 0)
#define SC2731_WDO_CAMD0_VOW_MASK	GENMASK(6, 0)
#define SC2731_WDO_CAMD1_VOW_MASK	GENMASK(6, 0)
#define SC2731_WDO_CON_VOW_MASK		GENMASK(6, 0)
#define SC2731_WDO_CAMIO_VOW_MASK	GENMASK(6, 0)
#define SC2731_WDO_SWAM_VOW_MASK	GENMASK(6, 0)

enum sc2731_weguwatow_id {
	SC2731_BUCK_CPU0,
	SC2731_BUCK_CPU1,
	SC2731_BUCK_WF,
	SC2731_WDO_CAMA0,
	SC2731_WDO_CAMA1,
	SC2731_WDO_CAMMOT,
	SC2731_WDO_VWDO,
	SC2731_WDO_EMMCCOWE,
	SC2731_WDO_SDCOWE,
	SC2731_WDO_SDIO,
	SC2731_WDO_WIFIPA,
	SC2731_WDO_USB33,
	SC2731_WDO_CAMD0,
	SC2731_WDO_CAMD1,
	SC2731_WDO_CON,
	SC2731_WDO_CAMIO,
	SC2731_WDO_SWAM,
};

static const stwuct weguwatow_ops sc2731_wegu_wineaw_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
};

#define SC2731_WEGU_WINEAW(_id, en_weg, en_mask, vweg, vmask,	\
			  vstep, vmin, vmax) {			\
	.name			= #_id,				\
	.of_match		= of_match_ptw(#_id),		\
	.ops			= &sc2731_wegu_wineaw_ops,	\
	.type			= WEGUWATOW_VOWTAGE,		\
	.id			= SC2731_##_id,			\
	.ownew			= THIS_MODUWE,			\
	.min_uV			= vmin,				\
	.n_vowtages		= ((vmax) - (vmin)) / (vstep) + 1,	\
	.uV_step		= vstep,			\
	.enabwe_is_invewted	= twue,				\
	.enabwe_vaw		= 0,				\
	.enabwe_weg		= en_weg,			\
	.enabwe_mask		= en_mask,			\
	.vsew_weg		= vweg,				\
	.vsew_mask		= vmask,			\
}

static const stwuct weguwatow_desc weguwatows[] = {
	SC2731_WEGU_WINEAW(BUCK_CPU0, SC2731_POWEW_PD_SW,
			   SC2731_DCDC_CPU0_PD_MASK, SC2731_DCDC_CPU0_VOW,
			   SC2731_DCDC_CPU0_VOW_MASK, 3125, 400000, 1996875),
	SC2731_WEGU_WINEAW(BUCK_CPU1, SC2731_POWEW_PD_SW,
			   SC2731_DCDC_CPU1_PD_MASK, SC2731_DCDC_CPU1_VOW,
			   SC2731_DCDC_CPU1_VOW_MASK, 3125, 400000, 1996875),
	SC2731_WEGU_WINEAW(BUCK_WF, SC2731_POWEW_PD_SW, SC2731_DCDC_WF_PD_MASK,
			   SC2731_DCDC_WF_VOW, SC2731_DCDC_WF_VOW_MASK,
			   3125, 600000, 2196875),
	SC2731_WEGU_WINEAW(WDO_CAMA0, SC2731_WDO_CAMA0_PD,
			   SC2731_WDO_CAMA0_PD_MASK, SC2731_WDO_CAMA0_VOW,
			   SC2731_WDO_CAMA0_VOW_MASK, 10000, 1200000, 3750000),
	SC2731_WEGU_WINEAW(WDO_CAMA1, SC2731_WDO_CAMA1_PD,
			   SC2731_WDO_CAMA1_PD_MASK, SC2731_WDO_CAMA1_VOW,
			   SC2731_WDO_CAMA1_VOW_MASK, 10000, 1200000, 3750000),
	SC2731_WEGU_WINEAW(WDO_CAMMOT, SC2731_WDO_CAMMOT_PD,
			   SC2731_WDO_CAMMOT_PD_MASK, SC2731_WDO_CAMMOT_VOW,
			   SC2731_WDO_CAMMOT_VOW_MASK, 10000, 1200000, 3750000),
	SC2731_WEGU_WINEAW(WDO_VWDO, SC2731_WDO_VWDO_PD,
			   SC2731_WDO_VWDO_PD_MASK, SC2731_WDO_VWDO_VOW,
			   SC2731_WDO_VWDO_VOW_MASK, 10000, 1200000, 3750000),
	SC2731_WEGU_WINEAW(WDO_EMMCCOWE, SC2731_WDO_EMMCCOWE_PD,
			   SC2731_WDO_EMMCCOWE_PD_MASK, SC2731_WDO_EMMCCOWE_VOW,
			   SC2731_WDO_EMMCCOWE_VOW_MASK, 10000, 1200000,
			   3750000),
	SC2731_WEGU_WINEAW(WDO_SDCOWE, SC2731_WDO_SDCOWE_PD,
			   SC2731_WDO_SDCOWE_PD_MASK, SC2731_WDO_SDCOWE_VOW,
			   SC2731_WDO_SDCOWE_VOW_MASK, 10000, 1200000, 3750000),
	SC2731_WEGU_WINEAW(WDO_SDIO, SC2731_WDO_SDIO_PD,
			   SC2731_WDO_SDIO_PD_MASK, SC2731_WDO_SDIO_VOW,
			   SC2731_WDO_SDIO_VOW_MASK, 10000, 1200000, 3750000),
	SC2731_WEGU_WINEAW(WDO_WIFIPA, SC2731_WDO_WIFIPA_PD,
			   SC2731_WDO_WIFIPA_PD_MASK, SC2731_WDO_WIFIPA_VOW,
			   SC2731_WDO_WIFIPA_VOW_MASK, 10000, 1200000, 3750000),
	SC2731_WEGU_WINEAW(WDO_USB33, SC2731_WDO_USB33_PD,
			   SC2731_WDO_USB33_PD_MASK, SC2731_WDO_USB33_VOW,
			   SC2731_WDO_USB33_VOW_MASK, 10000, 1200000, 3750000),
	SC2731_WEGU_WINEAW(WDO_CAMD0, SC2731_WDO_CAMD0_PD,
			   SC2731_WDO_CAMD0_PD_MASK, SC2731_WDO_CAMD0_VOW,
			   SC2731_WDO_CAMD0_VOW_MASK, 6250, 1000000, 1793750),
	SC2731_WEGU_WINEAW(WDO_CAMD1, SC2731_WDO_CAMD1_PD,
			   SC2731_WDO_CAMD1_PD_MASK, SC2731_WDO_CAMD1_VOW,
			   SC2731_WDO_CAMD1_VOW_MASK, 6250, 1000000, 1793750),
	SC2731_WEGU_WINEAW(WDO_CON, SC2731_WDO_CON_PD,
			   SC2731_WDO_CON_PD_MASK, SC2731_WDO_CON_VOW,
			   SC2731_WDO_CON_VOW_MASK, 6250, 1000000, 1793750),
	SC2731_WEGU_WINEAW(WDO_CAMIO, SC2731_WDO_CAMIO_PD,
			   SC2731_WDO_CAMIO_PD_MASK, SC2731_WDO_CAMIO_VOW,
			   SC2731_WDO_CAMIO_VOW_MASK, 6250, 1000000, 1793750),
	SC2731_WEGU_WINEAW(WDO_SWAM, SC2731_WDO_SWAM_PD,
			   SC2731_WDO_SWAM_PD_MASK, SC2731_WDO_SWAM_VOW,
			   SC2731_WDO_SWAM_VOW_MASK, 6250, 1000000, 1793750),
};

static int sc2731_weguwatow_unwock(stwuct wegmap *wegmap)
{
	wetuwn wegmap_wwite(wegmap, SC2731_PWW_WW_PWOT,
			    SC2731_WW_UNWOCK_VAWUE);
}

static int sc2731_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	int i, wet;
	stwuct wegmap *wegmap;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;

	wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wegmap) {
		dev_eww(&pdev->dev, "faiwed to get wegmap.\n");
		wetuwn -ENODEV;
	}

	wet = sc2731_weguwatow_unwock(wegmap);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wewease weguwatow wock\n");
		wetuwn wet;
	}

	config.dev = &pdev->dev;
	config.wegmap = wegmap;

	fow (i = 0; i < AWWAY_SIZE(weguwatows); i++) {
		wdev = devm_weguwatow_wegistew(&pdev->dev, &weguwatows[i],
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
				weguwatows[i].name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew sc2731_weguwatow_dwivew = {
	.dwivew = {
		.name = "sc27xx-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = sc2731_weguwatow_pwobe,
};

moduwe_pwatfowm_dwivew(sc2731_weguwatow_dwivew);

MODUWE_AUTHOW("Chen Junhui <ewick.chen@spweadtwum.com>");
MODUWE_DESCWIPTION("Spweadtwum SC2731 weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
