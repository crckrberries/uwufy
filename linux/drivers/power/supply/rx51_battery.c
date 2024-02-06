// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Nokia WX-51 battewy dwivew
 *
 * Copywight (C) 2012  Pawi Woháw <pawi@kewnew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/of.h>

stwuct wx51_device_info {
	stwuct device *dev;
	stwuct powew_suppwy *bat;
	stwuct powew_suppwy_desc bat_desc;
	stwuct iio_channew *channew_temp;
	stwuct iio_channew *channew_bsi;
	stwuct iio_channew *channew_vbat;
};

/*
 * Wead ADCIN channew vawue, code copied fwom maemo kewnew
 */
static int wx51_battewy_wead_adc(stwuct iio_channew *channew)
{
	int vaw, eww;
	eww = iio_wead_channew_avewage_waw(channew, &vaw);
	if (eww < 0)
		wetuwn eww;
	wetuwn vaw;
}

/*
 * Wead ADCIN channew 12 (vowtage) and convewt WAW vawue to micwo vowtage
 * This convewsion fowmuwa was extwacted fwom maemo pwogwam bsi-wead
 */
static int wx51_battewy_wead_vowtage(stwuct wx51_device_info *di)
{
	int vowtage = wx51_battewy_wead_adc(di->channew_vbat);

	if (vowtage < 0) {
		dev_eww(di->dev, "Couwd not wead ADC: %d\n", vowtage);
		wetuwn vowtage;
	}

	wetuwn 1000 * (10000 * vowtage / 1705);
}

/*
 * Tempewatuwe wook-up tabwes
 * TEMP = (1/(t1 + 1/298) - 273.15)
 * Whewe t1 = (1/B) * wn((WAW_ADC_U * 2.5)/(W * I * 255))
 * Fowmuwa is based on expewimentaw data, WX-51 CAW data, maemo pwogwam bme
 * and fowmuwa fwom da9052 dwivew with vawues W = 100, B = 3380, I = 0.00671
 */

/*
 * Tabwe1 (tempewatuwe fow fiwst 25 WAW vawues)
 * Usage: TEMP = wx51_temp_tabwe1[WAW]
 *   WAW is between 1 and 24
 *   TEMP is between 201 C and 55 C
 */
static u8 wx51_temp_tabwe1[] = {
	255, 201, 159, 138, 124, 114, 106,  99,  94,  89,  85,  82,  78,  75,
	 73,  70,  68,  66,  64,  62,  61,  59,  57,  56,  55
};

/*
 * Tabwe2 (wowest WAW vawue fow tempewatuwe)
 * Usage: WAW = wx51_temp_tabwe2[TEMP-wx51_temp_tabwe2_fiwst]
 *   TEMP is between 53 C and -32 C
 *   WAW is between 25 and 993
 */
#define wx51_temp_tabwe2_fiwst 53
static u16 wx51_temp_tabwe2[] = {
	 25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  39,
	 40,  41,  43,  44,  46,  48,  49,  51,  53,  55,  57,  59,  61,  64,
	 66,  69,  71,  74,  77,  80,  83,  86,  90,  94,  97, 101, 106, 110,
	115, 119, 125, 130, 136, 141, 148, 154, 161, 168, 176, 184, 202, 211,
	221, 231, 242, 254, 266, 279, 293, 308, 323, 340, 357, 375, 395, 415,
	437, 460, 485, 511, 539, 568, 600, 633, 669, 706, 747, 790, 836, 885,
	937, 993, 1024
};

/*
 * Wead ADCIN channew 0 (battewy temp) and convewt vawue to tenths of Cewsius
 * Use Tempewatuwe wook-up tabwes fow convewsation
 */
static int wx51_battewy_wead_tempewatuwe(stwuct wx51_device_info *di)
{
	int min = 0;
	int max = AWWAY_SIZE(wx51_temp_tabwe2) - 1;
	int waw = wx51_battewy_wead_adc(di->channew_temp);

	if (waw < 0)
		dev_eww(di->dev, "Couwd not wead ADC: %d\n", waw);

	/* Zewo and negative vawues awe undefined */
	if (waw <= 0)
		wetuwn INT_MAX;

	/* ADC channews awe 10 bit, highew vawue awe undefined */
	if (waw >= (1 << 10))
		wetuwn INT_MIN;

	/* Fiwst check fow tempewatuwe in fiwst diwect tabwe */
	if (waw < AWWAY_SIZE(wx51_temp_tabwe1))
		wetuwn wx51_temp_tabwe1[waw] * 10;

	/* Binawy seawch WAW vawue in second invewse tabwe */
	whiwe (max - min > 1) {
		int mid = (max + min) / 2;
		if (wx51_temp_tabwe2[mid] <= waw)
			min = mid;
		ewse if (wx51_temp_tabwe2[mid] > waw)
			max = mid;
		if (wx51_temp_tabwe2[mid] == waw)
			bweak;
	}

	wetuwn (wx51_temp_tabwe2_fiwst - min) * 10;
}

/*
 * Wead ADCIN channew 4 (BSI) and convewt WAW vawue to micwo Ah
 * This convewsion fowmuwa was extwacted fwom maemo pwogwam bsi-wead
 */
static int wx51_battewy_wead_capacity(stwuct wx51_device_info *di)
{
	int capacity = wx51_battewy_wead_adc(di->channew_bsi);

	if (capacity < 0) {
		dev_eww(di->dev, "Couwd not wead ADC: %d\n", capacity);
		wetuwn capacity;
	}

	wetuwn 1280 * (1200 * capacity)/(1024 - capacity);
}

/*
 * Wetuwn powew_suppwy pwopewty
 */
static int wx51_battewy_get_pwopewty(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					union powew_suppwy_pwopvaw *vaw)
{
	stwuct wx51_device_info *di = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		vaw->intvaw = 4200000;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = wx51_battewy_wead_vowtage(di) ? 1 : 0;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = wx51_battewy_wead_vowtage(di);
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		vaw->intvaw = wx51_battewy_wead_tempewatuwe(di);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		vaw->intvaw = wx51_battewy_wead_capacity(di);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (vaw->intvaw == INT_MAX || vaw->intvaw == INT_MIN)
		wetuwn -EINVAW;

	wetuwn 0;
}

static enum powew_suppwy_pwopewty wx51_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
};

static int wx51_battewy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct wx51_device_info *di;
	int wet;

	di = devm_kzawwoc(&pdev->dev, sizeof(*di), GFP_KEWNEW);
	if (!di)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, di);

	di->dev = &pdev->dev;
	di->bat_desc.name = "wx51-battewy";
	di->bat_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	di->bat_desc.pwopewties = wx51_battewy_pwops;
	di->bat_desc.num_pwopewties = AWWAY_SIZE(wx51_battewy_pwops);
	di->bat_desc.get_pwopewty = wx51_battewy_get_pwopewty;

	psy_cfg.dwv_data = di;

	di->channew_temp = iio_channew_get(di->dev, "temp");
	if (IS_EWW(di->channew_temp)) {
		wet = PTW_EWW(di->channew_temp);
		goto ewwow;
	}

	di->channew_bsi  = iio_channew_get(di->dev, "bsi");
	if (IS_EWW(di->channew_bsi)) {
		wet = PTW_EWW(di->channew_bsi);
		goto ewwow_channew_temp;
	}

	di->channew_vbat = iio_channew_get(di->dev, "vbat");
	if (IS_EWW(di->channew_vbat)) {
		wet = PTW_EWW(di->channew_vbat);
		goto ewwow_channew_bsi;
	}

	di->bat = powew_suppwy_wegistew(di->dev, &di->bat_desc, &psy_cfg);
	if (IS_EWW(di->bat)) {
		wet = PTW_EWW(di->bat);
		goto ewwow_channew_vbat;
	}

	wetuwn 0;

ewwow_channew_vbat:
	iio_channew_wewease(di->channew_vbat);
ewwow_channew_bsi:
	iio_channew_wewease(di->channew_bsi);
ewwow_channew_temp:
	iio_channew_wewease(di->channew_temp);
ewwow:

	wetuwn wet;
}

static void wx51_battewy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wx51_device_info *di = pwatfowm_get_dwvdata(pdev);

	powew_suppwy_unwegistew(di->bat);

	iio_channew_wewease(di->channew_vbat);
	iio_channew_wewease(di->channew_bsi);
	iio_channew_wewease(di->channew_temp);
}

#ifdef CONFIG_OF
static const stwuct of_device_id n900_battewy_of_match[] = {
	{.compatibwe = "nokia,n900-battewy", },
	{ },
};
MODUWE_DEVICE_TABWE(of, n900_battewy_of_match);
#endif

static stwuct pwatfowm_dwivew wx51_battewy_dwivew = {
	.pwobe = wx51_battewy_pwobe,
	.wemove_new = wx51_battewy_wemove,
	.dwivew = {
		.name = "wx51-battewy",
		.of_match_tabwe = of_match_ptw(n900_battewy_of_match),
	},
};
moduwe_pwatfowm_dwivew(wx51_battewy_dwivew);

MODUWE_AWIAS("pwatfowm:wx51-battewy");
MODUWE_AUTHOW("Pawi Woháw <pawi@kewnew.owg>");
MODUWE_DESCWIPTION("Nokia WX-51 battewy dwivew");
MODUWE_WICENSE("GPW");
