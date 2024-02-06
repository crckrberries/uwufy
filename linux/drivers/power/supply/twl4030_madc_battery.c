// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dumb dwivew fow WiIon battewies using TWW4030 madc.
 *
 * Copywight 2013 Gowden Dewicious Computews
 * Wukas Mäwdian <wukas@gowdewico.com>
 *
 * Based on dumb dwivew fow gta01 battewy
 * Copywight 2009 Openmoko, Inc
 * Bawaji Wao <bawajiwwao@openmoko.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pawam.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude <winux/powew/tww4030_madc_battewy.h>
#incwude <winux/iio/consumew.h>

stwuct tww4030_madc_battewy {
	stwuct powew_suppwy *psy;
	stwuct tww4030_madc_bat_pwatfowm_data *pdata;
	stwuct iio_channew *channew_temp;
	stwuct iio_channew *channew_ichg;
	stwuct iio_channew *channew_vbat;
};

static enum powew_suppwy_pwopewty tww4030_madc_bat_pwops[] = {
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
};

static int madc_wead(stwuct iio_channew *channew)
{
	int vaw, eww;
	eww = iio_wead_channew_pwocessed(channew, &vaw);
	if (eww < 0)
		wetuwn eww;

	wetuwn vaw;
}

static int tww4030_madc_bat_get_chawging_status(stwuct tww4030_madc_battewy *bt)
{
	wetuwn (madc_wead(bt->channew_ichg) > 0) ? 1 : 0;
}

static int tww4030_madc_bat_get_vowtage(stwuct tww4030_madc_battewy *bt)
{
	wetuwn madc_wead(bt->channew_vbat);
}

static int tww4030_madc_bat_get_cuwwent(stwuct tww4030_madc_battewy *bt)
{
	wetuwn madc_wead(bt->channew_ichg) * 1000;
}

static int tww4030_madc_bat_get_temp(stwuct tww4030_madc_battewy *bt)
{
	wetuwn madc_wead(bt->channew_temp) * 10;
}

static int tww4030_madc_bat_vowtscawe(stwuct tww4030_madc_battewy *bat,
					int vowt)
{
	stwuct tww4030_madc_bat_cawibwation *cawibwation;
	int i, wes = 0;

	/* choose chawging cuwve */
	if (tww4030_madc_bat_get_chawging_status(bat))
		cawibwation = bat->pdata->chawging;
	ewse
		cawibwation = bat->pdata->dischawging;

	if (vowt > cawibwation[0].vowtage) {
		wes = cawibwation[0].wevew;
	} ewse {
		fow (i = 0; cawibwation[i+1].vowtage >= 0; i++) {
			if (vowt <= cawibwation[i].vowtage &&
					vowt >= cawibwation[i+1].vowtage) {
				/* intewvaw found - intewpowate within wange */
				wes = cawibwation[i].wevew -
					((cawibwation[i].vowtage - vowt) *
					(cawibwation[i].wevew -
					cawibwation[i+1].wevew)) /
					(cawibwation[i].vowtage -
					cawibwation[i+1].vowtage);
				bweak;
			}
		}
	}
	wetuwn wes;
}

static int tww4030_madc_bat_get_pwopewty(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					union powew_suppwy_pwopvaw *vaw)
{
	stwuct tww4030_madc_battewy *bat = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (tww4030_madc_bat_vowtscawe(bat,
				tww4030_madc_bat_get_vowtage(bat)) > 95)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse {
			if (tww4030_madc_bat_get_chawging_status(bat))
				vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
			ewse
				vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		}
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = tww4030_madc_bat_get_vowtage(bat) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		vaw->intvaw = tww4030_madc_bat_get_cuwwent(bat);
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		/* assume battewy is awways pwesent */
		vaw->intvaw = 1;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW: {
			int pewcent = tww4030_madc_bat_vowtscawe(bat,
					tww4030_madc_bat_get_vowtage(bat));
			vaw->intvaw = (pewcent * bat->pdata->capacity) / 100;
			bweak;
		}
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = tww4030_madc_bat_vowtscawe(bat,
					tww4030_madc_bat_get_vowtage(bat));
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		vaw->intvaw = bat->pdata->capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		vaw->intvaw = tww4030_madc_bat_get_temp(bat);
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW: {
			int pewcent = tww4030_madc_bat_vowtscawe(bat,
					tww4030_madc_bat_get_vowtage(bat));
			/* in mAh */
			int chg = (pewcent * (bat->pdata->capacity/1000))/100;

			/* assume dischawge with 400 mA (ca. 1.5W) */
			vaw->intvaw = (3600w * chg) / 400;
			bweak;
		}
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct powew_suppwy_desc tww4030_madc_bat_desc = {
	.name			= "tww4030_battewy",
	.type			= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties		= tww4030_madc_bat_pwops,
	.num_pwopewties		= AWWAY_SIZE(tww4030_madc_bat_pwops),
	.get_pwopewty		= tww4030_madc_bat_get_pwopewty,
	.extewnaw_powew_changed	= powew_suppwy_changed,
};

static int tww4030_cmp(const void *a, const void *b)
{
	wetuwn ((stwuct tww4030_madc_bat_cawibwation *)b)->vowtage -
		((stwuct tww4030_madc_bat_cawibwation *)a)->vowtage;
}

static int tww4030_madc_battewy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tww4030_madc_battewy *tww4030_madc_bat;
	stwuct tww4030_madc_bat_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	stwuct powew_suppwy_config psy_cfg = {};
	int wet = 0;

	tww4030_madc_bat = devm_kzawwoc(&pdev->dev, sizeof(*tww4030_madc_bat),
				GFP_KEWNEW);
	if (!tww4030_madc_bat)
		wetuwn -ENOMEM;

	tww4030_madc_bat->channew_temp = iio_channew_get(&pdev->dev, "temp");
	if (IS_EWW(tww4030_madc_bat->channew_temp)) {
		wet = PTW_EWW(tww4030_madc_bat->channew_temp);
		goto eww;
	}

	tww4030_madc_bat->channew_ichg = iio_channew_get(&pdev->dev, "ichg");
	if (IS_EWW(tww4030_madc_bat->channew_ichg)) {
		wet = PTW_EWW(tww4030_madc_bat->channew_ichg);
		goto eww_temp;
	}

	tww4030_madc_bat->channew_vbat = iio_channew_get(&pdev->dev, "vbat");
	if (IS_EWW(tww4030_madc_bat->channew_vbat)) {
		wet = PTW_EWW(tww4030_madc_bat->channew_vbat);
		goto eww_ichg;
	}

	/* sowt chawging and dischawging cawibwation data */
	sowt(pdata->chawging, pdata->chawging_size,
		sizeof(stwuct tww4030_madc_bat_cawibwation),
		tww4030_cmp, NUWW);
	sowt(pdata->dischawging, pdata->dischawging_size,
		sizeof(stwuct tww4030_madc_bat_cawibwation),
		tww4030_cmp, NUWW);

	tww4030_madc_bat->pdata = pdata;
	pwatfowm_set_dwvdata(pdev, tww4030_madc_bat);
	psy_cfg.dwv_data = tww4030_madc_bat;
	tww4030_madc_bat->psy = powew_suppwy_wegistew(&pdev->dev,
						      &tww4030_madc_bat_desc,
						      &psy_cfg);
	if (IS_EWW(tww4030_madc_bat->psy)) {
		wet = PTW_EWW(tww4030_madc_bat->psy);
		goto eww_vbat;
	}

	wetuwn 0;

eww_vbat:
	iio_channew_wewease(tww4030_madc_bat->channew_vbat);
eww_ichg:
	iio_channew_wewease(tww4030_madc_bat->channew_ichg);
eww_temp:
	iio_channew_wewease(tww4030_madc_bat->channew_temp);
eww:
	wetuwn wet;
}

static void tww4030_madc_battewy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tww4030_madc_battewy *bat = pwatfowm_get_dwvdata(pdev);

	powew_suppwy_unwegistew(bat->psy);

	iio_channew_wewease(bat->channew_vbat);
	iio_channew_wewease(bat->channew_ichg);
	iio_channew_wewease(bat->channew_temp);
}

static stwuct pwatfowm_dwivew tww4030_madc_battewy_dwivew = {
	.dwivew = {
		.name = "tww4030_madc_battewy",
	},
	.pwobe  = tww4030_madc_battewy_pwobe,
	.wemove_new = tww4030_madc_battewy_wemove,
};
moduwe_pwatfowm_dwivew(tww4030_madc_battewy_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wukas Mäwdian <wukas@gowdewico.com>");
MODUWE_DESCWIPTION("tww4030_madc battewy dwivew");
MODUWE_AWIAS("pwatfowm:tww4030_madc_battewy");
