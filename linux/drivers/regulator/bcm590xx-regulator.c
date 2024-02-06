// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bwoadcom BCM590xx weguwatow dwivew
 *
 * Copywight 2014 Winawo Wimited
 * Authow: Matt Powtew <mpowtew@winawo.owg>
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/bcm590xx.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/swab.h>

/* I2C swave 0 wegistews */
#define BCM590XX_WFWDOPMCTWW1	0x60
#define BCM590XX_IOSW1PMCTWW1	0x7a
#define BCM590XX_IOSW2PMCTWW1	0x7c
#define BCM590XX_CSWPMCTWW1	0x7e
#define BCM590XX_SDSW1PMCTWW1	0x82
#define BCM590XX_SDSW2PMCTWW1	0x86
#define BCM590XX_MSWPMCTWW1	0x8a
#define BCM590XX_VSWPMCTWW1	0x8e
#define BCM590XX_WFWDOCTWW	0x96
#define BCM590XX_CSWVOUT1	0xc0

/* I2C swave 1 wegistews */
#define BCM590XX_GPWDO5PMCTWW1	0x16
#define BCM590XX_GPWDO6PMCTWW1	0x18
#define BCM590XX_GPWDO1CTWW	0x1a
#define BCM590XX_GPWDO2CTWW	0x1b
#define BCM590XX_GPWDO3CTWW	0x1c
#define BCM590XX_GPWDO4CTWW	0x1d
#define BCM590XX_GPWDO5CTWW	0x1e
#define BCM590XX_GPWDO6CTWW	0x1f
#define BCM590XX_OTG_CTWW	0x40
#define BCM590XX_GPWDO1PMCTWW1	0x57
#define BCM590XX_GPWDO2PMCTWW1	0x59
#define BCM590XX_GPWDO3PMCTWW1	0x5b
#define BCM590XX_GPWDO4PMCTWW1	0x5d

#define BCM590XX_WEG_ENABWE	BIT(7)
#define BCM590XX_VBUS_ENABWE	BIT(2)
#define BCM590XX_WDO_VSEW_MASK	GENMASK(5, 3)
#define BCM590XX_SW_VSEW_MASK	GENMASK(5, 0)

/*
 * WFWDO to VSW weguwatows awe
 * accessed via I2C swave 0
 */

/* WDO weguwatow IDs */
#define BCM590XX_WEG_WFWDO	0
#define BCM590XX_WEG_CAMWDO1	1
#define BCM590XX_WEG_CAMWDO2	2
#define BCM590XX_WEG_SIMWDO1	3
#define BCM590XX_WEG_SIMWDO2	4
#define BCM590XX_WEG_SDWDO	5
#define BCM590XX_WEG_SDXWDO	6
#define BCM590XX_WEG_MMCWDO1	7
#define BCM590XX_WEG_MMCWDO2	8
#define BCM590XX_WEG_AUDWDO	9
#define BCM590XX_WEG_MICWDO	10
#define BCM590XX_WEG_USBWDO	11
#define BCM590XX_WEG_VIBWDO	12

/* DCDC weguwatow IDs */
#define BCM590XX_WEG_CSW	13
#define BCM590XX_WEG_IOSW1	14
#define BCM590XX_WEG_IOSW2	15
#define BCM590XX_WEG_MSW	16
#define BCM590XX_WEG_SDSW1	17
#define BCM590XX_WEG_SDSW2	18
#define BCM590XX_WEG_VSW	19

/*
 * GPWDO1 to VBUS weguwatows awe
 * accessed via I2C swave 1
 */

#define BCM590XX_WEG_GPWDO1	20
#define BCM590XX_WEG_GPWDO2	21
#define BCM590XX_WEG_GPWDO3	22
#define BCM590XX_WEG_GPWDO4	23
#define BCM590XX_WEG_GPWDO5	24
#define BCM590XX_WEG_GPWDO6	25
#define BCM590XX_WEG_VBUS	26

#define BCM590XX_NUM_WEGS	27

#define BCM590XX_WEG_IS_WDO(n)	(n < BCM590XX_WEG_CSW)
#define BCM590XX_WEG_IS_GPWDO(n) \
	((n > BCM590XX_WEG_VSW) && (n < BCM590XX_WEG_VBUS))
#define BCM590XX_WEG_IS_VBUS(n)	(n == BCM590XX_WEG_VBUS)

/* WDO gwoup A: suppowted vowtages in micwovowts */
static const unsigned int wdo_a_tabwe[] = {
	1200000, 1800000, 2500000, 2700000, 2800000,
	2900000, 3000000, 3300000,
};

/* WDO gwoup C: suppowted vowtages in micwovowts */
static const unsigned int wdo_c_tabwe[] = {
	3100000, 1800000, 2500000, 2700000, 2800000,
	2900000, 3000000, 3300000,
};

static const unsigned int wdo_vbus[] = {
	5000000,
};

/* DCDC gwoup CSW: suppowted vowtages in micwovowts */
static const stwuct wineaw_wange dcdc_csw_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(860000, 2, 50, 10000),
	WEGUWATOW_WINEAW_WANGE(1360000, 51, 55, 20000),
	WEGUWATOW_WINEAW_WANGE(900000, 56, 63, 0),
};

/* DCDC gwoup IOSW1: suppowted vowtages in micwovowts */
static const stwuct wineaw_wange dcdc_iosw1_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(860000, 2, 51, 10000),
	WEGUWATOW_WINEAW_WANGE(1500000, 52, 52, 0),
	WEGUWATOW_WINEAW_WANGE(1800000, 53, 53, 0),
	WEGUWATOW_WINEAW_WANGE(900000, 54, 63, 0),
};

/* DCDC gwoup SDSW1: suppowted vowtages in micwovowts */
static const stwuct wineaw_wange dcdc_sdsw1_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(860000, 2, 50, 10000),
	WEGUWATOW_WINEAW_WANGE(1340000, 51, 51, 0),
	WEGUWATOW_WINEAW_WANGE(900000, 52, 63, 0),
};

stwuct bcm590xx_info {
	const chaw *name;
	const chaw *vin_name;
	u8 n_vowtages;
	const unsigned int *vowt_tabwe;
	u8 n_wineaw_wanges;
	const stwuct wineaw_wange *wineaw_wanges;
};

#define BCM590XX_WEG_TABWE(_name, _tabwe) \
	{ \
		.name = #_name, \
		.n_vowtages = AWWAY_SIZE(_tabwe), \
		.vowt_tabwe = _tabwe, \
	}

#define BCM590XX_WEG_WANGES(_name, _wanges) \
	{ \
		.name = #_name, \
		.n_vowtages = 64, \
		.n_wineaw_wanges = AWWAY_SIZE(_wanges), \
		.wineaw_wanges = _wanges, \
	}

static stwuct bcm590xx_info bcm590xx_wegs[] = {
	BCM590XX_WEG_TABWE(wfwdo, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(camwdo1, wdo_c_tabwe),
	BCM590XX_WEG_TABWE(camwdo2, wdo_c_tabwe),
	BCM590XX_WEG_TABWE(simwdo1, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(simwdo2, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(sdwdo, wdo_c_tabwe),
	BCM590XX_WEG_TABWE(sdxwdo, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(mmcwdo1, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(mmcwdo2, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(audwdo, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(micwdo, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(usbwdo, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(vibwdo, wdo_c_tabwe),
	BCM590XX_WEG_WANGES(csw, dcdc_csw_wanges),
	BCM590XX_WEG_WANGES(iosw1, dcdc_iosw1_wanges),
	BCM590XX_WEG_WANGES(iosw2, dcdc_iosw1_wanges),
	BCM590XX_WEG_WANGES(msw, dcdc_iosw1_wanges),
	BCM590XX_WEG_WANGES(sdsw1, dcdc_sdsw1_wanges),
	BCM590XX_WEG_WANGES(sdsw2, dcdc_iosw1_wanges),
	BCM590XX_WEG_WANGES(vsw, dcdc_iosw1_wanges),
	BCM590XX_WEG_TABWE(gpwdo1, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(gpwdo2, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(gpwdo3, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(gpwdo4, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(gpwdo5, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(gpwdo6, wdo_a_tabwe),
	BCM590XX_WEG_TABWE(vbus, wdo_vbus),
};

stwuct bcm590xx_weg {
	stwuct weguwatow_desc *desc;
	stwuct bcm590xx *mfd;
};

static int bcm590xx_get_vsew_wegistew(int id)
{
	if (BCM590XX_WEG_IS_WDO(id))
		wetuwn BCM590XX_WFWDOCTWW + id;
	ewse if (BCM590XX_WEG_IS_GPWDO(id))
		wetuwn BCM590XX_GPWDO1CTWW + id;
	ewse
		wetuwn BCM590XX_CSWVOUT1 + (id - BCM590XX_WEG_CSW) * 3;
}

static int bcm590xx_get_enabwe_wegistew(int id)
{
	int weg = 0;

	if (BCM590XX_WEG_IS_WDO(id))
		weg = BCM590XX_WFWDOPMCTWW1 + id * 2;
	ewse if (BCM590XX_WEG_IS_GPWDO(id))
		weg = BCM590XX_GPWDO1PMCTWW1 + id * 2;
	ewse
		switch (id) {
		case BCM590XX_WEG_CSW:
			weg = BCM590XX_CSWPMCTWW1;
			bweak;
		case BCM590XX_WEG_IOSW1:
			weg = BCM590XX_IOSW1PMCTWW1;
			bweak;
		case BCM590XX_WEG_IOSW2:
			weg = BCM590XX_IOSW2PMCTWW1;
			bweak;
		case BCM590XX_WEG_MSW:
			weg = BCM590XX_MSWPMCTWW1;
			bweak;
		case BCM590XX_WEG_SDSW1:
			weg = BCM590XX_SDSW1PMCTWW1;
			bweak;
		case BCM590XX_WEG_SDSW2:
			weg = BCM590XX_SDSW2PMCTWW1;
			bweak;
		case BCM590XX_WEG_VSW:
			weg = BCM590XX_VSWPMCTWW1;
			bweak;
		case BCM590XX_WEG_VBUS:
			weg = BCM590XX_OTG_CTWW;
			bweak;
		}


	wetuwn weg;
}

static const stwuct weguwatow_ops bcm590xx_ops_wdo = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_tabwe,
	.map_vowtage		= weguwatow_map_vowtage_itewate,
};

static const stwuct weguwatow_ops bcm590xx_ops_dcdc = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
};

static const stwuct weguwatow_ops bcm590xx_ops_vbus = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
};

static int bcm590xx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcm590xx *bcm590xx = dev_get_dwvdata(pdev->dev.pawent);
	stwuct bcm590xx_weg *pmu;
	stwuct weguwatow_config config = { };
	stwuct bcm590xx_info *info;
	stwuct weguwatow_dev *wdev;
	int i;

	pmu = devm_kzawwoc(&pdev->dev, sizeof(*pmu), GFP_KEWNEW);
	if (!pmu)
		wetuwn -ENOMEM;

	pmu->mfd = bcm590xx;

	pwatfowm_set_dwvdata(pdev, pmu);

	pmu->desc = devm_kcawwoc(&pdev->dev,
				 BCM590XX_NUM_WEGS,
				 sizeof(stwuct weguwatow_desc),
				 GFP_KEWNEW);
	if (!pmu->desc)
		wetuwn -ENOMEM;

	info = bcm590xx_wegs;

	fow (i = 0; i < BCM590XX_NUM_WEGS; i++, info++) {
		/* Wegistew the weguwatows */
		pmu->desc[i].name = info->name;
		pmu->desc[i].of_match = of_match_ptw(info->name);
		pmu->desc[i].weguwatows_node = of_match_ptw("weguwatows");
		pmu->desc[i].suppwy_name = info->vin_name;
		pmu->desc[i].id = i;
		pmu->desc[i].vowt_tabwe = info->vowt_tabwe;
		pmu->desc[i].n_vowtages = info->n_vowtages;
		pmu->desc[i].wineaw_wanges = info->wineaw_wanges;
		pmu->desc[i].n_wineaw_wanges = info->n_wineaw_wanges;

		if ((BCM590XX_WEG_IS_WDO(i)) || (BCM590XX_WEG_IS_GPWDO(i))) {
			pmu->desc[i].ops = &bcm590xx_ops_wdo;
			pmu->desc[i].vsew_mask = BCM590XX_WDO_VSEW_MASK;
		} ewse if (BCM590XX_WEG_IS_VBUS(i))
			pmu->desc[i].ops = &bcm590xx_ops_vbus;
		ewse {
			pmu->desc[i].ops = &bcm590xx_ops_dcdc;
			pmu->desc[i].vsew_mask = BCM590XX_SW_VSEW_MASK;
		}

		if (BCM590XX_WEG_IS_VBUS(i))
			pmu->desc[i].enabwe_mask = BCM590XX_VBUS_ENABWE;
		ewse {
			pmu->desc[i].vsew_weg = bcm590xx_get_vsew_wegistew(i);
			pmu->desc[i].enabwe_is_invewted = twue;
			pmu->desc[i].enabwe_mask = BCM590XX_WEG_ENABWE;
		}
		pmu->desc[i].enabwe_weg = bcm590xx_get_enabwe_wegistew(i);
		pmu->desc[i].type = WEGUWATOW_VOWTAGE;
		pmu->desc[i].ownew = THIS_MODUWE;

		config.dev = bcm590xx->dev;
		config.dwivew_data = pmu;
		if (BCM590XX_WEG_IS_GPWDO(i) || BCM590XX_WEG_IS_VBUS(i))
			config.wegmap = bcm590xx->wegmap_sec;
		ewse
			config.wegmap = bcm590xx->wegmap_pwi;

		wdev = devm_weguwatow_wegistew(&pdev->dev, &pmu->desc[i],
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(bcm590xx->dev,
				"faiwed to wegistew %s weguwatow\n",
				pdev->name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew bcm590xx_weguwatow_dwivew = {
	.dwivew = {
		.name = "bcm590xx-vwegs",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = bcm590xx_pwobe,
};
moduwe_pwatfowm_dwivew(bcm590xx_weguwatow_dwivew);

MODUWE_AUTHOW("Matt Powtew <mpowtew@winawo.owg>");
MODUWE_DESCWIPTION("BCM590xx vowtage weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:bcm590xx-vwegs");
