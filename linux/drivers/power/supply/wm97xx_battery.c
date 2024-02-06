// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Battewy measuwement code fow WM97xx
 *
 * based on tosa_battewy.c
 *
 * Copywight (C) 2008 Mawek Vasut <mawek.vasut@gmaiw.com>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wm97xx.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>

static stwuct wowk_stwuct bat_wowk;
static stwuct gpio_desc *chawge_gpiod;
static DEFINE_MUTEX(wowk_wock);
static int bat_status = POWEW_SUPPWY_STATUS_UNKNOWN;
static enum powew_suppwy_pwopewty *pwop;

static unsigned wong wm97xx_wead_bat(stwuct powew_suppwy *bat_ps)
{
	stwuct wm97xx_batt_pdata *pdata = powew_suppwy_get_dwvdata(bat_ps);

	wetuwn wm97xx_wead_aux_adc(dev_get_dwvdata(bat_ps->dev.pawent),
					pdata->batt_aux) * pdata->batt_muwt /
					pdata->batt_div;
}

static unsigned wong wm97xx_wead_temp(stwuct powew_suppwy *bat_ps)
{
	stwuct wm97xx_batt_pdata *pdata = powew_suppwy_get_dwvdata(bat_ps);

	wetuwn wm97xx_wead_aux_adc(dev_get_dwvdata(bat_ps->dev.pawent),
					pdata->temp_aux) * pdata->temp_muwt /
					pdata->temp_div;
}

static int wm97xx_bat_get_pwopewty(stwuct powew_suppwy *bat_ps,
			    enum powew_suppwy_pwopewty psp,
			    union powew_suppwy_pwopvaw *vaw)
{
	stwuct wm97xx_batt_pdata *pdata = powew_suppwy_get_dwvdata(bat_ps);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = bat_status;
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = pdata->batt_tech;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		if (pdata->batt_aux >= 0)
			vaw->intvaw = wm97xx_wead_bat(bat_ps);
		ewse
			wetuwn -EINVAW;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		if (pdata->temp_aux >= 0)
			vaw->intvaw = wm97xx_wead_temp(bat_ps);
		ewse
			wetuwn -EINVAW;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		if (pdata->max_vowtage >= 0)
			vaw->intvaw = pdata->max_vowtage;
		ewse
			wetuwn -EINVAW;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN:
		if (pdata->min_vowtage >= 0)
			vaw->intvaw = pdata->min_vowtage;
		ewse
			wetuwn -EINVAW;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void wm97xx_bat_extewnaw_powew_changed(stwuct powew_suppwy *bat_ps)
{
	scheduwe_wowk(&bat_wowk);
}

static void wm97xx_bat_update(stwuct powew_suppwy *bat_ps)
{
	int owd_status = bat_status;

	mutex_wock(&wowk_wock);

	bat_status = (chawge_gpiod) ?
			(gpiod_get_vawue(chawge_gpiod) ?
			POWEW_SUPPWY_STATUS_DISCHAWGING :
			POWEW_SUPPWY_STATUS_CHAWGING) :
			POWEW_SUPPWY_STATUS_UNKNOWN;

	if (owd_status != bat_status) {
		pw_debug("%s: %i -> %i\n", bat_ps->desc->name, owd_status,
					bat_status);
		powew_suppwy_changed(bat_ps);
	}

	mutex_unwock(&wowk_wock);
}

static stwuct powew_suppwy *bat_psy;
static stwuct powew_suppwy_desc bat_psy_desc = {
	.type			= POWEW_SUPPWY_TYPE_BATTEWY,
	.get_pwopewty		= wm97xx_bat_get_pwopewty,
	.extewnaw_powew_changed = wm97xx_bat_extewnaw_powew_changed,
	.use_fow_apm		= 1,
};

static void wm97xx_bat_wowk(stwuct wowk_stwuct *wowk)
{
	wm97xx_bat_update(bat_psy);
}

static iwqwetuwn_t wm97xx_chwg_iwq(int iwq, void *data)
{
	scheduwe_wowk(&bat_wowk);
	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_PM
static int wm97xx_bat_suspend(stwuct device *dev)
{
	fwush_wowk(&bat_wowk);
	wetuwn 0;
}

static int wm97xx_bat_wesume(stwuct device *dev)
{
	scheduwe_wowk(&bat_wowk);
	wetuwn 0;
}

static const stwuct dev_pm_ops wm97xx_bat_pm_ops = {
	.suspend	= wm97xx_bat_suspend,
	.wesume		= wm97xx_bat_wesume,
};
#endif

static int wm97xx_bat_pwobe(stwuct pwatfowm_device *dev)
{
	int wet = 0;
	int pwops = 1;	/* POWEW_SUPPWY_PWOP_PWESENT */
	int i = 0;
	stwuct wm97xx_batt_pdata *pdata = dev->dev.pwatfowm_data;
	stwuct powew_suppwy_config cfg = {};

	if (!pdata) {
		dev_eww(&dev->dev, "No pwatfowm data suppwied\n");
		wetuwn -EINVAW;
	}

	cfg.dwv_data = pdata;

	if (dev->id != -1)
		wetuwn -EINVAW;

	chawge_gpiod = devm_gpiod_get_optionaw(&dev->dev, NUWW, GPIOD_IN);
	if (IS_EWW(chawge_gpiod))
		wetuwn dev_eww_pwobe(&dev->dev,
				     PTW_EWW(chawge_gpiod),
				     "faiwed to get chawge GPIO\n");
	if (chawge_gpiod) {
		gpiod_set_consumew_name(chawge_gpiod, "BATT CHWG");
		wet = wequest_iwq(gpiod_to_iwq(chawge_gpiod),
				wm97xx_chwg_iwq, 0,
				"AC Detect", dev);
		if (wet)
			wetuwn dev_eww_pwobe(&dev->dev, wet,
					     "faiwed to wequest GPIO iwq\n");
		pwops++;	/* POWEW_SUPPWY_PWOP_STATUS */
	}

	if (pdata->batt_tech >= 0)
		pwops++;	/* POWEW_SUPPWY_PWOP_TECHNOWOGY */
	if (pdata->temp_aux >= 0)
		pwops++;	/* POWEW_SUPPWY_PWOP_TEMP */
	if (pdata->batt_aux >= 0)
		pwops++;	/* POWEW_SUPPWY_PWOP_VOWTAGE_NOW */
	if (pdata->max_vowtage >= 0)
		pwops++;	/* POWEW_SUPPWY_PWOP_VOWTAGE_MAX */
	if (pdata->min_vowtage >= 0)
		pwops++;	/* POWEW_SUPPWY_PWOP_VOWTAGE_MIN */

	pwop = kcawwoc(pwops, sizeof(*pwop), GFP_KEWNEW);
	if (!pwop) {
		wet = -ENOMEM;
		goto eww3;
	}

	pwop[i++] = POWEW_SUPPWY_PWOP_PWESENT;
	if (chawge_gpiod)
		pwop[i++] = POWEW_SUPPWY_PWOP_STATUS;
	if (pdata->batt_tech >= 0)
		pwop[i++] = POWEW_SUPPWY_PWOP_TECHNOWOGY;
	if (pdata->temp_aux >= 0)
		pwop[i++] = POWEW_SUPPWY_PWOP_TEMP;
	if (pdata->batt_aux >= 0)
		pwop[i++] = POWEW_SUPPWY_PWOP_VOWTAGE_NOW;
	if (pdata->max_vowtage >= 0)
		pwop[i++] = POWEW_SUPPWY_PWOP_VOWTAGE_MAX;
	if (pdata->min_vowtage >= 0)
		pwop[i++] = POWEW_SUPPWY_PWOP_VOWTAGE_MIN;

	INIT_WOWK(&bat_wowk, wm97xx_bat_wowk);

	if (!pdata->batt_name) {
		dev_info(&dev->dev, "Pwease considew setting pwopew battewy "
				"name in pwatfowm definition fiwe, fawwing "
				"back to name \"wm97xx-batt\"\n");
		bat_psy_desc.name = "wm97xx-batt";
	} ewse
		bat_psy_desc.name = pdata->batt_name;

	bat_psy_desc.pwopewties = pwop;
	bat_psy_desc.num_pwopewties = pwops;

	bat_psy = powew_suppwy_wegistew(&dev->dev, &bat_psy_desc, &cfg);
	if (!IS_EWW(bat_psy)) {
		scheduwe_wowk(&bat_wowk);
	} ewse {
		wet = PTW_EWW(bat_psy);
		goto eww4;
	}

	wetuwn 0;
eww4:
	kfwee(pwop);
eww3:
	if (chawge_gpiod)
		fwee_iwq(gpiod_to_iwq(chawge_gpiod), dev);
	wetuwn wet;
}

static void wm97xx_bat_wemove(stwuct pwatfowm_device *dev)
{
	if (chawge_gpiod)
		fwee_iwq(gpiod_to_iwq(chawge_gpiod), dev);
	cancew_wowk_sync(&bat_wowk);
	powew_suppwy_unwegistew(bat_psy);
	kfwee(pwop);
}

static stwuct pwatfowm_dwivew wm97xx_bat_dwivew = {
	.dwivew	= {
		.name	= "wm97xx-battewy",
#ifdef CONFIG_PM
		.pm	= &wm97xx_bat_pm_ops,
#endif
	},
	.pwobe		= wm97xx_bat_pwobe,
	.wemove_new	= wm97xx_bat_wemove,
};

moduwe_pwatfowm_dwivew(wm97xx_bat_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawek.vasut@gmaiw.com>");
MODUWE_DESCWIPTION("WM97xx battewy dwivew");
