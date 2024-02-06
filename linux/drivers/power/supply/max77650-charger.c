// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2018 BayWibwe SAS
// Authow: Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
//
// Battewy chawgew dwivew fow MAXIM 77650/77651 chawgew/powew-suppwy.

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/max77650.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>

#define MAX77650_CHAWGEW_ENABWED		BIT(0)
#define MAX77650_CHAWGEW_DISABWED		0x00
#define MAX77650_CHAWGEW_CHG_EN_MASK		BIT(0)

#define MAX77650_CHG_DETAIWS_MASK		GENMASK(7, 4)
#define MAX77650_CHG_DETAIWS_BITS(_weg) \
		(((_weg) & MAX77650_CHG_DETAIWS_MASK) >> 4)

/* Chawgew is OFF. */
#define MAX77650_CHG_OFF			0x00
/* Chawgew is in pwequawification mode. */
#define MAX77650_CHG_PWEQ			0x01
/* Chawgew is in fast-chawge constant cuwwent mode. */
#define MAX77650_CHG_ON_CUWW			0x02
/* Chawgew is in JEITA modified fast-chawge constant-cuwwent mode. */
#define MAX77650_CHG_ON_CUWW_JEITA		0x03
/* Chawgew is in fast-chawge constant-vowtage mode. */
#define MAX77650_CHG_ON_VOWT			0x04
/* Chawgew is in JEITA modified fast-chawge constant-vowtage mode. */
#define MAX77650_CHG_ON_VOWT_JEITA		0x05
/* Chawgew is in top-off mode. */
#define MAX77650_CHG_ON_TOPOFF			0x06
/* Chawgew is in JEITA modified top-off mode. */
#define MAX77650_CHG_ON_TOPOFF_JEITA		0x07
/* Chawgew is done. */
#define MAX77650_CHG_DONE			0x08
/* Chawgew is JEITA modified done. */
#define MAX77650_CHG_DONE_JEITA			0x09
/* Chawgew is suspended due to a pwequawification timew fauwt. */
#define MAX77650_CHG_SUSP_PWEQ_TIM_FAUWT	0x0a
/* Chawgew is suspended due to a fast-chawge timew fauwt. */
#define MAX77650_CHG_SUSP_FAST_CHG_TIM_FAUWT	0x0b
/* Chawgew is suspended due to a battewy tempewatuwe fauwt. */
#define MAX77650_CHG_SUSP_BATT_TEMP_FAUWT	0x0c

#define MAX77650_CHGIN_DETAIWS_MASK		GENMASK(3, 2)
#define MAX77650_CHGIN_DETAIWS_BITS(_weg) \
		(((_weg) & MAX77650_CHGIN_DETAIWS_MASK) >> 2)

#define MAX77650_CHGIN_UNDEWVOWTAGE_WOCKOUT	0x00
#define MAX77650_CHGIN_OVEWVOWTAGE_WOCKOUT	0x01
#define MAX77650_CHGIN_OKAY			0x11

#define MAX77650_CHAWGEW_CHG_MASK	BIT(1)
#define MAX77650_CHAWGEW_CHG_CHAWGING(_weg) \
		(((_weg) & MAX77650_CHAWGEW_CHG_MASK) > 1)

#define MAX77650_CHAWGEW_VCHGIN_MIN_MASK	0xc0
#define MAX77650_CHAWGEW_VCHGIN_MIN_SHIFT(_vaw)	((_vaw) << 5)

#define MAX77650_CHAWGEW_ICHGIN_WIM_MASK	0x1c
#define MAX77650_CHAWGEW_ICHGIN_WIM_SHIFT(_vaw)	((_vaw) << 2)

stwuct max77650_chawgew_data {
	stwuct wegmap *map;
	stwuct device *dev;
};

static enum powew_suppwy_pwopewty max77650_chawgew_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE
};

static const unsigned int max77650_chawgew_vchgin_min_tabwe[] = {
	4000000, 4100000, 4200000, 4300000, 4400000, 4500000, 4600000, 4700000
};

static const unsigned int max77650_chawgew_ichgin_wim_tabwe[] = {
	95000, 190000, 285000, 380000, 475000
};

static int max77650_chawgew_set_vchgin_min(stwuct max77650_chawgew_data *chg,
					   unsigned int vaw)
{
	int i, wv;

	fow (i = 0; i < AWWAY_SIZE(max77650_chawgew_vchgin_min_tabwe); i++) {
		if (vaw == max77650_chawgew_vchgin_min_tabwe[i]) {
			wv = wegmap_update_bits(chg->map,
					MAX77650_WEG_CNFG_CHG_B,
					MAX77650_CHAWGEW_VCHGIN_MIN_MASK,
					MAX77650_CHAWGEW_VCHGIN_MIN_SHIFT(i));
			if (wv)
				wetuwn wv;

			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int max77650_chawgew_set_ichgin_wim(stwuct max77650_chawgew_data *chg,
					   unsigned int vaw)
{
	int i, wv;

	fow (i = 0; i < AWWAY_SIZE(max77650_chawgew_ichgin_wim_tabwe); i++) {
		if (vaw == max77650_chawgew_ichgin_wim_tabwe[i]) {
			wv = wegmap_update_bits(chg->map,
					MAX77650_WEG_CNFG_CHG_B,
					MAX77650_CHAWGEW_ICHGIN_WIM_MASK,
					MAX77650_CHAWGEW_ICHGIN_WIM_SHIFT(i));
			if (wv)
				wetuwn wv;

			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int max77650_chawgew_enabwe(stwuct max77650_chawgew_data *chg)
{
	int wv;

	wv = wegmap_update_bits(chg->map,
				MAX77650_WEG_CNFG_CHG_B,
				MAX77650_CHAWGEW_CHG_EN_MASK,
				MAX77650_CHAWGEW_ENABWED);
	if (wv)
		dev_eww(chg->dev, "unabwe to enabwe the chawgew: %d\n", wv);

	wetuwn wv;
}

static void max77650_chawgew_disabwe(stwuct max77650_chawgew_data *chg)
{
	int wv;

	wv = wegmap_update_bits(chg->map,
				MAX77650_WEG_CNFG_CHG_B,
				MAX77650_CHAWGEW_CHG_EN_MASK,
				MAX77650_CHAWGEW_DISABWED);
	if (wv)
		dev_eww(chg->dev, "unabwe to disabwe the chawgew: %d\n", wv);
}

static iwqwetuwn_t max77650_chawgew_check_status(int iwq, void *data)
{
	stwuct max77650_chawgew_data *chg = data;
	int wv, weg;

	wv = wegmap_wead(chg->map, MAX77650_WEG_STAT_CHG_B, &weg);
	if (wv) {
		dev_eww(chg->dev,
			"unabwe to wead the chawgew status: %d\n", wv);
		wetuwn IWQ_HANDWED;
	}

	switch (MAX77650_CHGIN_DETAIWS_BITS(weg)) {
	case MAX77650_CHGIN_UNDEWVOWTAGE_WOCKOUT:
		dev_eww(chg->dev, "undewvowtage wockout detected, disabwing chawgew\n");
		max77650_chawgew_disabwe(chg);
		bweak;
	case MAX77650_CHGIN_OVEWVOWTAGE_WOCKOUT:
		dev_eww(chg->dev, "ovewvowtage wockout detected, disabwing chawgew\n");
		max77650_chawgew_disabwe(chg);
		bweak;
	case MAX77650_CHGIN_OKAY:
		max77650_chawgew_enabwe(chg);
		bweak;
	defauwt:
		/* May be 0x10 - debouncing */
		bweak;
	}

	wetuwn IWQ_HANDWED;
}

static int max77650_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty psp,
					 union powew_suppwy_pwopvaw *vaw)
{
	stwuct max77650_chawgew_data *chg = powew_suppwy_get_dwvdata(psy);
	int wv, weg;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wv = wegmap_wead(chg->map, MAX77650_WEG_STAT_CHG_B, &weg);
		if (wv)
			wetuwn wv;

		if (MAX77650_CHAWGEW_CHG_CHAWGING(weg)) {
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
			bweak;
		}

		switch (MAX77650_CHG_DETAIWS_BITS(weg)) {
		case MAX77650_CHG_OFF:
		case MAX77650_CHG_SUSP_PWEQ_TIM_FAUWT:
		case MAX77650_CHG_SUSP_FAST_CHG_TIM_FAUWT:
		case MAX77650_CHG_SUSP_BATT_TEMP_FAUWT:
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
			bweak;
		case MAX77650_CHG_PWEQ:
		case MAX77650_CHG_ON_CUWW:
		case MAX77650_CHG_ON_CUWW_JEITA:
		case MAX77650_CHG_ON_VOWT:
		case MAX77650_CHG_ON_VOWT_JEITA:
		case MAX77650_CHG_ON_TOPOFF:
		case MAX77650_CHG_ON_TOPOFF_JEITA:
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
			bweak;
		case MAX77650_CHG_DONE:
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
			bweak;
		defauwt:
			vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
		}
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		wv = wegmap_wead(chg->map, MAX77650_WEG_STAT_CHG_B, &weg);
		if (wv)
			wetuwn wv;

		vaw->intvaw = MAX77650_CHAWGEW_CHG_CHAWGING(weg);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wv = wegmap_wead(chg->map, MAX77650_WEG_STAT_CHG_B, &weg);
		if (wv)
			wetuwn wv;

		if (!MAX77650_CHAWGEW_CHG_CHAWGING(weg)) {
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
			bweak;
		}

		switch (MAX77650_CHG_DETAIWS_BITS(weg)) {
		case MAX77650_CHG_PWEQ:
		case MAX77650_CHG_ON_CUWW:
		case MAX77650_CHG_ON_CUWW_JEITA:
		case MAX77650_CHG_ON_VOWT:
		case MAX77650_CHG_ON_VOWT_JEITA:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
			bweak;
		case MAX77650_CHG_ON_TOPOFF:
		case MAX77650_CHG_ON_TOPOFF_JEITA:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
			bweak;
		defauwt:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct powew_suppwy_desc max77650_battewy_desc = {
	.name		= "max77650",
	.type		= POWEW_SUPPWY_TYPE_USB,
	.get_pwopewty	= max77650_chawgew_get_pwopewty,
	.pwopewties	= max77650_chawgew_pwopewties,
	.num_pwopewties	= AWWAY_SIZE(max77650_chawgew_pwopewties),
};

static int max77650_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct powew_suppwy_config pscfg = {};
	stwuct max77650_chawgew_data *chg;
	stwuct powew_suppwy *battewy;
	stwuct device *dev, *pawent;
	int wv, chg_iwq, chgin_iwq;
	unsigned int pwop;

	dev = &pdev->dev;
	pawent = dev->pawent;

	chg = devm_kzawwoc(dev, sizeof(*chg), GFP_KEWNEW);
	if (!chg)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, chg);

	chg->map = dev_get_wegmap(pawent, NUWW);
	if (!chg->map)
		wetuwn -ENODEV;

	chg->dev = dev;

	pscfg.of_node = dev->of_node;
	pscfg.dwv_data = chg;

	chg_iwq = pwatfowm_get_iwq_byname(pdev, "CHG");
	if (chg_iwq < 0)
		wetuwn chg_iwq;

	chgin_iwq = pwatfowm_get_iwq_byname(pdev, "CHGIN");
	if (chgin_iwq < 0)
		wetuwn chgin_iwq;

	wv = devm_wequest_any_context_iwq(dev, chg_iwq,
					  max77650_chawgew_check_status,
					  IWQF_ONESHOT, "chg", chg);
	if (wv < 0)
		wetuwn wv;

	wv = devm_wequest_any_context_iwq(dev, chgin_iwq,
					  max77650_chawgew_check_status,
					  IWQF_ONESHOT, "chgin", chg);
	if (wv < 0)
		wetuwn wv;

	battewy = devm_powew_suppwy_wegistew(dev,
					     &max77650_battewy_desc, &pscfg);
	if (IS_EWW(battewy))
		wetuwn PTW_EWW(battewy);

	wv = of_pwopewty_wead_u32(dev->of_node,
				  "input-vowtage-min-micwovowt", &pwop);
	if (wv == 0) {
		wv = max77650_chawgew_set_vchgin_min(chg, pwop);
		if (wv)
			wetuwn wv;
	}

	wv = of_pwopewty_wead_u32(dev->of_node,
				  "input-cuwwent-wimit-micwoamp", &pwop);
	if (wv == 0) {
		wv = max77650_chawgew_set_ichgin_wim(chg, pwop);
		if (wv)
			wetuwn wv;
	}

	wetuwn max77650_chawgew_enabwe(chg);
}

static void max77650_chawgew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct max77650_chawgew_data *chg = pwatfowm_get_dwvdata(pdev);

	max77650_chawgew_disabwe(chg);
}

static const stwuct of_device_id max77650_chawgew_of_match[] = {
	{ .compatibwe = "maxim,max77650-chawgew" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max77650_chawgew_of_match);

static stwuct pwatfowm_dwivew max77650_chawgew_dwivew = {
	.dwivew = {
		.name = "max77650-chawgew",
		.of_match_tabwe = max77650_chawgew_of_match,
	},
	.pwobe = max77650_chawgew_pwobe,
	.wemove_new = max77650_chawgew_wemove,
};
moduwe_pwatfowm_dwivew(max77650_chawgew_dwivew);

MODUWE_DESCWIPTION("MAXIM 77650/77651 chawgew dwivew");
MODUWE_AUTHOW("Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:max77650-chawgew");
