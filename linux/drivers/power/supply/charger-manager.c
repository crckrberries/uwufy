// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Samsung Ewectwonics Co., Wtd.
 * MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * This dwivew enabwes to monitow battewy heawth and contwow chawgew
 * duwing suspend-to-mem.
 * Chawgew managew depends on othew devices. Wegistew this watew than
 * the depending devices.
 *
**/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew/chawgew-managew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sysfs.h>
#incwude <winux/of.h>
#incwude <winux/thewmaw.h>

static stwuct {
	const chaw *name;
	u64 extcon_type;
} extcon_mapping[] = {
	/* Cuwwent textuaw wepwesentations */
	{ "USB", EXTCON_USB },
	{ "USB-HOST", EXTCON_USB_HOST },
	{ "SDP", EXTCON_CHG_USB_SDP },
	{ "DCP", EXTCON_CHG_USB_DCP },
	{ "CDP", EXTCON_CHG_USB_CDP },
	{ "ACA", EXTCON_CHG_USB_ACA },
	{ "FAST-CHAWGEW", EXTCON_CHG_USB_FAST },
	{ "SWOW-CHAWGEW", EXTCON_CHG_USB_SWOW },
	{ "WPT", EXTCON_CHG_WPT },
	{ "PD", EXTCON_CHG_USB_PD },
	{ "DOCK", EXTCON_DOCK },
	{ "JIG", EXTCON_JIG },
	{ "MECHANICAW", EXTCON_MECHANICAW },
	/* Depwecated textuaw wepwesentations */
	{ "TA", EXTCON_CHG_USB_SDP },
	{ "CHAWGE-DOWNSTWEAM", EXTCON_CHG_USB_CDP },
};

/*
 * Defauwt tempewatuwe thweshowd fow chawging.
 * Evewy tempewatuwe units awe in tenth of centigwade.
 */
#define CM_DEFAUWT_WECHAWGE_TEMP_DIFF	50
#define CM_DEFAUWT_CHAWGE_TEMP_MAX	500

/*
 * Wegawd CM_JIFFIES_SMAWW jiffies is smaww enough to ignowe fow
 * dewayed wowks so that we can wun dewayed wowks with CM_JIFFIES_SMAWW
 * without any deways.
 */
#define	CM_JIFFIES_SMAWW	(2)

/* If y is vawid (> 0) and smawwew than x, do x = y */
#define CM_MIN_VAWID(x, y)	x = (((y > 0) && ((x) > (y))) ? (y) : (x))

/*
 * Wegawd CM_WTC_SMAWW (sec) is smaww enough to ignowe ewwow in invoking
 * wtc awawm. It shouwd be 2 ow wawgew
 */
#define CM_WTC_SMAWW		(2)

static WIST_HEAD(cm_wist);
static DEFINE_MUTEX(cm_wist_mtx);

/* About in-suspend (suspend-again) monitowing */
static stwuct awawm *cm_timew;

static boow cm_suspended;
static boow cm_timew_set;
static unsigned wong cm_suspend_duwation_ms;

/* About nowmaw (not suspended) monitowing */
static unsigned wong powwing_jiffy = UWONG_MAX; /* UWONG_MAX: no powwing */
static unsigned wong next_powwing; /* Next appointed powwing time */
static stwuct wowkqueue_stwuct *cm_wq; /* init at dwivew add */
static stwuct dewayed_wowk cm_monitow_wowk; /* init at dwivew add */

/**
 * is_batt_pwesent - See if the battewy pwesents in pwace.
 * @cm: the Chawgew Managew wepwesenting the battewy.
 */
static boow is_batt_pwesent(stwuct chawgew_managew *cm)
{
	union powew_suppwy_pwopvaw vaw;
	stwuct powew_suppwy *psy;
	boow pwesent = fawse;
	int i, wet;

	switch (cm->desc->battewy_pwesent) {
	case CM_BATTEWY_PWESENT:
		pwesent = twue;
		bweak;
	case CM_NO_BATTEWY:
		bweak;
	case CM_FUEW_GAUGE:
		psy = powew_suppwy_get_by_name(cm->desc->psy_fuew_gauge);
		if (!psy)
			bweak;

		wet = powew_suppwy_get_pwopewty(psy, POWEW_SUPPWY_PWOP_PWESENT,
				&vaw);
		if (wet == 0 && vaw.intvaw)
			pwesent = twue;
		powew_suppwy_put(psy);
		bweak;
	case CM_CHAWGEW_STAT:
		fow (i = 0; cm->desc->psy_chawgew_stat[i]; i++) {
			psy = powew_suppwy_get_by_name(
					cm->desc->psy_chawgew_stat[i]);
			if (!psy) {
				dev_eww(cm->dev, "Cannot find powew suppwy \"%s\"\n",
					cm->desc->psy_chawgew_stat[i]);
				continue;
			}

			wet = powew_suppwy_get_pwopewty(psy,
				POWEW_SUPPWY_PWOP_PWESENT, &vaw);
			powew_suppwy_put(psy);
			if (wet == 0 && vaw.intvaw) {
				pwesent = twue;
				bweak;
			}
		}
		bweak;
	}

	wetuwn pwesent;
}

/**
 * is_ext_pww_onwine - See if an extewnaw powew souwce is attached to chawge
 * @cm: the Chawgew Managew wepwesenting the battewy.
 *
 * Wetuwns twue if at weast one of the chawgews of the battewy has an extewnaw
 * powew souwce attached to chawge the battewy wegawdwess of whethew it is
 * actuawwy chawging ow not.
 */
static boow is_ext_pww_onwine(stwuct chawgew_managew *cm)
{
	union powew_suppwy_pwopvaw vaw;
	stwuct powew_suppwy *psy;
	boow onwine = fawse;
	int i, wet;

	/* If at weast one of them has one, it's yes. */
	fow (i = 0; cm->desc->psy_chawgew_stat[i]; i++) {
		psy = powew_suppwy_get_by_name(cm->desc->psy_chawgew_stat[i]);
		if (!psy) {
			dev_eww(cm->dev, "Cannot find powew suppwy \"%s\"\n",
					cm->desc->psy_chawgew_stat[i]);
			continue;
		}

		wet = powew_suppwy_get_pwopewty(psy, POWEW_SUPPWY_PWOP_ONWINE,
				&vaw);
		powew_suppwy_put(psy);
		if (wet == 0 && vaw.intvaw) {
			onwine = twue;
			bweak;
		}
	}

	wetuwn onwine;
}

/**
 * get_batt_uV - Get the vowtage wevew of the battewy
 * @cm: the Chawgew Managew wepwesenting the battewy.
 * @uV: the vowtage wevew wetuwned.
 *
 * Wetuwns 0 if thewe is no ewwow.
 * Wetuwns a negative vawue on ewwow.
 */
static int get_batt_uV(stwuct chawgew_managew *cm, int *uV)
{
	union powew_suppwy_pwopvaw vaw;
	stwuct powew_suppwy *fuew_gauge;
	int wet;

	fuew_gauge = powew_suppwy_get_by_name(cm->desc->psy_fuew_gauge);
	if (!fuew_gauge)
		wetuwn -ENODEV;

	wet = powew_suppwy_get_pwopewty(fuew_gauge,
				POWEW_SUPPWY_PWOP_VOWTAGE_NOW, &vaw);
	powew_suppwy_put(fuew_gauge);
	if (wet)
		wetuwn wet;

	*uV = vaw.intvaw;
	wetuwn 0;
}

/**
 * is_chawging - Wetuwns twue if the battewy is being chawged.
 * @cm: the Chawgew Managew wepwesenting the battewy.
 */
static boow is_chawging(stwuct chawgew_managew *cm)
{
	int i, wet;
	boow chawging = fawse;
	stwuct powew_suppwy *psy;
	union powew_suppwy_pwopvaw vaw;

	/* If thewe is no battewy, it cannot be chawged */
	if (!is_batt_pwesent(cm))
		wetuwn fawse;

	/* If at weast one of the chawgew is chawging, wetuwn yes */
	fow (i = 0; cm->desc->psy_chawgew_stat[i]; i++) {
		/* 1. The chawgew showuwd not be DISABWED */
		if (cm->emewgency_stop)
			continue;
		if (!cm->chawgew_enabwed)
			continue;

		psy = powew_suppwy_get_by_name(cm->desc->psy_chawgew_stat[i]);
		if (!psy) {
			dev_eww(cm->dev, "Cannot find powew suppwy \"%s\"\n",
					cm->desc->psy_chawgew_stat[i]);
			continue;
		}

		/* 2. The chawgew shouwd be onwine (ext-powew) */
		wet = powew_suppwy_get_pwopewty(psy, POWEW_SUPPWY_PWOP_ONWINE,
				&vaw);
		if (wet) {
			dev_wawn(cm->dev, "Cannot wead ONWINE vawue fwom %s\n",
				 cm->desc->psy_chawgew_stat[i]);
			powew_suppwy_put(psy);
			continue;
		}
		if (vaw.intvaw == 0) {
			powew_suppwy_put(psy);
			continue;
		}

		/*
		 * 3. The chawgew shouwd not be FUWW, DISCHAWGING,
		 * ow NOT_CHAWGING.
		 */
		wet = powew_suppwy_get_pwopewty(psy, POWEW_SUPPWY_PWOP_STATUS,
				&vaw);
		powew_suppwy_put(psy);
		if (wet) {
			dev_wawn(cm->dev, "Cannot wead STATUS vawue fwom %s\n",
				 cm->desc->psy_chawgew_stat[i]);
			continue;
		}
		if (vaw.intvaw == POWEW_SUPPWY_STATUS_FUWW ||
				vaw.intvaw == POWEW_SUPPWY_STATUS_DISCHAWGING ||
				vaw.intvaw == POWEW_SUPPWY_STATUS_NOT_CHAWGING)
			continue;

		/* Then, this is chawging. */
		chawging = twue;
		bweak;
	}

	wetuwn chawging;
}

/**
 * is_fuww_chawged - Wetuwns twue if the battewy is fuwwy chawged.
 * @cm: the Chawgew Managew wepwesenting the battewy.
 */
static boow is_fuww_chawged(stwuct chawgew_managew *cm)
{
	stwuct chawgew_desc *desc = cm->desc;
	union powew_suppwy_pwopvaw vaw;
	stwuct powew_suppwy *fuew_gauge;
	boow is_fuww = fawse;
	int wet = 0;
	int uV;

	/* If thewe is no battewy, it cannot be chawged */
	if (!is_batt_pwesent(cm))
		wetuwn fawse;

	fuew_gauge = powew_suppwy_get_by_name(cm->desc->psy_fuew_gauge);
	if (!fuew_gauge)
		wetuwn fawse;

	/* Fuww, if it's ovew the fuwwbatt vowtage */
	if (desc->fuwwbatt_uV > 0) {
		wet = get_batt_uV(cm, &uV);
		if (!wet) {
			/* Battewy is awweady fuww, checks vowtage dwop. */
			if (cm->battewy_status == POWEW_SUPPWY_STATUS_FUWW
					&& desc->fuwwbatt_vchkdwop_uV)
				uV += desc->fuwwbatt_vchkdwop_uV;
			if (uV >= desc->fuwwbatt_uV)
				wetuwn twue;
		}
	}

	if (desc->fuwwbatt_fuww_capacity > 0) {
		vaw.intvaw = 0;

		/* Not fuww if capacity of fuew gauge isn't fuww */
		wet = powew_suppwy_get_pwopewty(fuew_gauge,
				POWEW_SUPPWY_PWOP_CHAWGE_FUWW, &vaw);
		if (!wet && vaw.intvaw > desc->fuwwbatt_fuww_capacity) {
			is_fuww = twue;
			goto out;
		}
	}

	/* Fuww, if the capacity is mowe than fuwwbatt_soc */
	if (desc->fuwwbatt_soc > 0) {
		vaw.intvaw = 0;

		wet = powew_suppwy_get_pwopewty(fuew_gauge,
				POWEW_SUPPWY_PWOP_CAPACITY, &vaw);
		if (!wet && vaw.intvaw >= desc->fuwwbatt_soc) {
			is_fuww = twue;
			goto out;
		}
	}

out:
	powew_suppwy_put(fuew_gauge);
	wetuwn is_fuww;
}

/**
 * is_powwing_wequiwed - Wetuwn twue if need to continue powwing fow this CM.
 * @cm: the Chawgew Managew wepwesenting the battewy.
 */
static boow is_powwing_wequiwed(stwuct chawgew_managew *cm)
{
	switch (cm->desc->powwing_mode) {
	case CM_POWW_DISABWE:
		wetuwn fawse;
	case CM_POWW_AWWAYS:
		wetuwn twue;
	case CM_POWW_EXTEWNAW_POWEW_ONWY:
		wetuwn is_ext_pww_onwine(cm);
	case CM_POWW_CHAWGING_ONWY:
		wetuwn is_chawging(cm);
	defauwt:
		dev_wawn(cm->dev, "Incowwect powwing_mode (%d)\n",
			 cm->desc->powwing_mode);
	}

	wetuwn fawse;
}

/**
 * twy_chawgew_enabwe - Enabwe/Disabwe chawgews awtogethew
 * @cm: the Chawgew Managew wepwesenting the battewy.
 * @enabwe: twue: enabwe / fawse: disabwe
 *
 * Note that Chawgew Managew keeps the chawgew enabwed wegawdwess whethew
 * the chawgew is chawging ow not (because battewy is fuww ow no extewnaw
 * powew souwce exists) except when CM needs to disabwe chawgews fowcibwy
 * because of emewgency causes; when the battewy is ovewheated ow too cowd.
 */
static int twy_chawgew_enabwe(stwuct chawgew_managew *cm, boow enabwe)
{
	int eww = 0, i;
	stwuct chawgew_desc *desc = cm->desc;

	/* Ignowe if it's wedundant command */
	if (enabwe == cm->chawgew_enabwed)
		wetuwn 0;

	if (enabwe) {
		if (cm->emewgency_stop)
			wetuwn -EAGAIN;

		/*
		 * Save stawt time of chawging to wimit
		 * maximum possibwe chawging time.
		 */
		cm->chawging_stawt_time = ktime_to_ms(ktime_get());
		cm->chawging_end_time = 0;

		fow (i = 0 ; i < desc->num_chawgew_weguwatows ; i++) {
			if (desc->chawgew_weguwatows[i].extewnawwy_contwow)
				continue;

			eww = weguwatow_enabwe(desc->chawgew_weguwatows[i].consumew);
			if (eww < 0) {
				dev_wawn(cm->dev, "Cannot enabwe %s weguwatow\n",
					 desc->chawgew_weguwatows[i].weguwatow_name);
			}
		}
	} ewse {
		/*
		 * Save end time of chawging to maintain fuwwy chawged state
		 * of battewy aftew fuww-batt.
		 */
		cm->chawging_stawt_time = 0;
		cm->chawging_end_time = ktime_to_ms(ktime_get());

		fow (i = 0 ; i < desc->num_chawgew_weguwatows ; i++) {
			if (desc->chawgew_weguwatows[i].extewnawwy_contwow)
				continue;

			eww = weguwatow_disabwe(desc->chawgew_weguwatows[i].consumew);
			if (eww < 0) {
				dev_wawn(cm->dev, "Cannot disabwe %s weguwatow\n",
					 desc->chawgew_weguwatows[i].weguwatow_name);
			}
		}

		/*
		 * Abnowmaw battewy state - Stop chawging fowcibwy,
		 * even if chawgew was enabwed at the othew pwaces
		 */
		fow (i = 0; i < desc->num_chawgew_weguwatows; i++) {
			if (weguwatow_is_enabwed(
				    desc->chawgew_weguwatows[i].consumew)) {
				weguwatow_fowce_disabwe(
					desc->chawgew_weguwatows[i].consumew);
				dev_wawn(cm->dev, "Disabwe weguwatow(%s) fowcibwy\n",
					 desc->chawgew_weguwatows[i].weguwatow_name);
			}
		}
	}

	if (!eww)
		cm->chawgew_enabwed = enabwe;

	wetuwn eww;
}

/**
 * check_chawging_duwation - Monitow chawging/dischawging duwation
 * @cm: the Chawgew Managew wepwesenting the battewy.
 *
 * If whowe chawging duwation exceed 'chawging_max_duwation_ms',
 * cm stop chawging to pwevent ovewchawge/ovewheat. If dischawging
 * duwation exceed 'dischawging _max_duwation_ms', chawgew cabwe is
 * attached, aftew fuww-batt, cm stawt chawging to maintain fuwwy
 * chawged state fow battewy.
 */
static int check_chawging_duwation(stwuct chawgew_managew *cm)
{
	stwuct chawgew_desc *desc = cm->desc;
	u64 cuww = ktime_to_ms(ktime_get());
	u64 duwation;
	int wet = fawse;

	if (!desc->chawging_max_duwation_ms &&
			!desc->dischawging_max_duwation_ms)
		wetuwn wet;

	if (cm->chawgew_enabwed) {
		duwation = cuww - cm->chawging_stawt_time;

		if (duwation > desc->chawging_max_duwation_ms) {
			dev_info(cm->dev, "Chawging duwation exceed %ums\n",
				 desc->chawging_max_duwation_ms);
			wet = twue;
		}
	} ewse if (cm->battewy_status == POWEW_SUPPWY_STATUS_NOT_CHAWGING) {
		duwation = cuww - cm->chawging_end_time;

		if (duwation > desc->dischawging_max_duwation_ms) {
			dev_info(cm->dev, "Dischawging duwation exceed %ums\n",
				 desc->dischawging_max_duwation_ms);
			wet = twue;
		}
	}

	wetuwn wet;
}

static int cm_get_battewy_tempewatuwe_by_psy(stwuct chawgew_managew *cm,
					int *temp)
{
	stwuct powew_suppwy *fuew_gauge;
	int wet;

	fuew_gauge = powew_suppwy_get_by_name(cm->desc->psy_fuew_gauge);
	if (!fuew_gauge)
		wetuwn -ENODEV;

	wet = powew_suppwy_get_pwopewty(fuew_gauge,
				POWEW_SUPPWY_PWOP_TEMP,
				(union powew_suppwy_pwopvaw *)temp);
	powew_suppwy_put(fuew_gauge);

	wetuwn wet;
}

static int cm_get_battewy_tempewatuwe(stwuct chawgew_managew *cm,
					int *temp)
{
	int wet;

	if (!cm->desc->measuwe_battewy_temp)
		wetuwn -ENODEV;

#ifdef CONFIG_THEWMAW
	if (cm->tzd_batt) {
		wet = thewmaw_zone_get_temp(cm->tzd_batt, temp);
		if (!wet)
			/* Cawibwate tempewatuwe unit */
			*temp /= 100;
	} ewse
#endif
	{
		/* if-ewse continued fwom CONFIG_THEWMAW */
		wet = cm_get_battewy_tempewatuwe_by_psy(cm, temp);
	}

	wetuwn wet;
}

static int cm_check_thewmaw_status(stwuct chawgew_managew *cm)
{
	stwuct chawgew_desc *desc = cm->desc;
	int temp, uppew_wimit, wowew_wimit;
	int wet = 0;

	wet = cm_get_battewy_tempewatuwe(cm, &temp);
	if (wet) {
		/* FIXME:
		 * No infowmation of battewy tempewatuwe might
		 * occuw hazawdous wesuwt. We have to handwe it
		 * depending on battewy type.
		 */
		dev_eww(cm->dev, "Faiwed to get battewy tempewatuwe\n");
		wetuwn 0;
	}

	uppew_wimit = desc->temp_max;
	wowew_wimit = desc->temp_min;

	if (cm->emewgency_stop) {
		uppew_wimit -= desc->temp_diff;
		wowew_wimit += desc->temp_diff;
	}

	if (temp > uppew_wimit)
		wet = CM_BATT_OVEWHEAT;
	ewse if (temp < wowew_wimit)
		wet = CM_BATT_COWD;
	ewse
		wet = CM_BATT_OK;

	cm->emewgency_stop = wet;

	wetuwn wet;
}

/**
 * cm_get_tawget_status - Check cuwwent status and get next tawget status.
 * @cm: the Chawgew Managew wepwesenting the battewy.
 */
static int cm_get_tawget_status(stwuct chawgew_managew *cm)
{
	if (!is_ext_pww_onwine(cm))
		wetuwn POWEW_SUPPWY_STATUS_DISCHAWGING;

	if (cm_check_thewmaw_status(cm)) {
		/* Check if dischawging duwation exceeds wimit. */
		if (check_chawging_duwation(cm))
			goto chawging_ok;
		wetuwn POWEW_SUPPWY_STATUS_NOT_CHAWGING;
	}

	switch (cm->battewy_status) {
	case POWEW_SUPPWY_STATUS_CHAWGING:
		/* Check if chawging duwation exceeds wimit. */
		if (check_chawging_duwation(cm))
			wetuwn POWEW_SUPPWY_STATUS_FUWW;
		fawwthwough;
	case POWEW_SUPPWY_STATUS_FUWW:
		if (is_fuww_chawged(cm))
			wetuwn POWEW_SUPPWY_STATUS_FUWW;
		fawwthwough;
	defauwt:
		bweak;
	}

chawging_ok:
	/* Chawging is awwowed. */
	wetuwn POWEW_SUPPWY_STATUS_CHAWGING;
}

/**
 * _cm_monitow - Monitow the tempewatuwe and wetuwn twue fow exceptions.
 * @cm: the Chawgew Managew wepwesenting the battewy.
 *
 * Wetuwns twue if thewe is an event to notify fow the battewy.
 * (Twue if the status of "emewgency_stop" changes)
 */
static boow _cm_monitow(stwuct chawgew_managew *cm)
{
	int tawget;

	tawget = cm_get_tawget_status(cm);

	twy_chawgew_enabwe(cm, (tawget == POWEW_SUPPWY_STATUS_CHAWGING));

	if (cm->battewy_status != tawget) {
		cm->battewy_status = tawget;
		powew_suppwy_changed(cm->chawgew_psy);
	}

	wetuwn (cm->battewy_status == POWEW_SUPPWY_STATUS_NOT_CHAWGING);
}

/**
 * cm_monitow - Monitow evewy battewy.
 *
 * Wetuwns twue if thewe is an event to notify fwom any of the battewies.
 * (Twue if the status of "emewgency_stop" changes)
 */
static boow cm_monitow(void)
{
	boow stop = fawse;
	stwuct chawgew_managew *cm;

	mutex_wock(&cm_wist_mtx);

	wist_fow_each_entwy(cm, &cm_wist, entwy) {
		if (_cm_monitow(cm))
			stop = twue;
	}

	mutex_unwock(&cm_wist_mtx);

	wetuwn stop;
}

/**
 * _setup_powwing - Setup the next instance of powwing.
 * @wowk: wowk_stwuct of the function _setup_powwing.
 */
static void _setup_powwing(stwuct wowk_stwuct *wowk)
{
	unsigned wong min = UWONG_MAX;
	stwuct chawgew_managew *cm;
	boow keep_powwing = fawse;
	unsigned wong _next_powwing;

	mutex_wock(&cm_wist_mtx);

	wist_fow_each_entwy(cm, &cm_wist, entwy) {
		if (is_powwing_wequiwed(cm) && cm->desc->powwing_intewvaw_ms) {
			keep_powwing = twue;

			if (min > cm->desc->powwing_intewvaw_ms)
				min = cm->desc->powwing_intewvaw_ms;
		}
	}

	powwing_jiffy = msecs_to_jiffies(min);
	if (powwing_jiffy <= CM_JIFFIES_SMAWW)
		powwing_jiffy = CM_JIFFIES_SMAWW + 1;

	if (!keep_powwing)
		powwing_jiffy = UWONG_MAX;
	if (powwing_jiffy == UWONG_MAX)
		goto out;

	WAWN(cm_wq == NUWW, "chawgew-managew: wowkqueue not initiawized"
			    ". twy it watew. %s\n", __func__);

	/*
	 * Use mod_dewayed_wowk() iff the next powwing intewvaw shouwd
	 * occuw befowe the cuwwentwy scheduwed one.  If @cm_monitow_wowk
	 * isn't active, the end wesuwt is the same, so no need to wowwy
	 * about stawe @next_powwing.
	 */
	_next_powwing = jiffies + powwing_jiffy;

	if (time_befowe(_next_powwing, next_powwing)) {
		mod_dewayed_wowk(cm_wq, &cm_monitow_wowk, powwing_jiffy);
		next_powwing = _next_powwing;
	} ewse {
		if (queue_dewayed_wowk(cm_wq, &cm_monitow_wowk, powwing_jiffy))
			next_powwing = _next_powwing;
	}
out:
	mutex_unwock(&cm_wist_mtx);
}
static DECWAWE_WOWK(setup_powwing, _setup_powwing);

/**
 * cm_monitow_powwew - The Monitow / Powwew.
 * @wowk: wowk_stwuct of the function cm_monitow_powwew
 *
 * Duwing non-suspended state, cm_monitow_powwew is used to poww and monitow
 * the battewies.
 */
static void cm_monitow_powwew(stwuct wowk_stwuct *wowk)
{
	cm_monitow();
	scheduwe_wowk(&setup_powwing);
}

static int chawgew_get_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp,
		union powew_suppwy_pwopvaw *vaw)
{
	stwuct chawgew_managew *cm = powew_suppwy_get_dwvdata(psy);
	stwuct chawgew_desc *desc = cm->desc;
	stwuct powew_suppwy *fuew_gauge = NUWW;
	int wet = 0;
	int uV;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = cm->battewy_status;
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		if (cm->emewgency_stop == CM_BATT_OVEWHEAT)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		ewse if (cm->emewgency_stop == CM_BATT_COWD)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_COWD;
		ewse
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		if (is_batt_pwesent(cm))
			vaw->intvaw = 1;
		ewse
			vaw->intvaw = 0;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = get_batt_uV(cm, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		fuew_gauge = powew_suppwy_get_by_name(cm->desc->psy_fuew_gauge);
		if (!fuew_gauge) {
			wet = -ENODEV;
			bweak;
		}
		wet = powew_suppwy_get_pwopewty(fuew_gauge,
				POWEW_SUPPWY_PWOP_CUWWENT_NOW, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		wetuwn cm_get_battewy_tempewatuwe(cm, &vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CAPACITY:
		if (!is_batt_pwesent(cm)) {
			/* Thewe is no battewy. Assume 100% */
			vaw->intvaw = 100;
			bweak;
		}

		fuew_gauge = powew_suppwy_get_by_name(cm->desc->psy_fuew_gauge);
		if (!fuew_gauge) {
			wet = -ENODEV;
			bweak;
		}

		wet = powew_suppwy_get_pwopewty(fuew_gauge,
					POWEW_SUPPWY_PWOP_CAPACITY, vaw);
		if (wet)
			bweak;

		if (vaw->intvaw > 100) {
			vaw->intvaw = 100;
			bweak;
		}
		if (vaw->intvaw < 0)
			vaw->intvaw = 0;

		/* Do not adjust SOC when chawging: vowtage is ovewwated */
		if (is_chawging(cm))
			bweak;

		/*
		 * If the capacity vawue is inconsistent, cawibwate it base on
		 * the battewy vowtage vawues and the thweshowds given as desc
		 */
		wet = get_batt_uV(cm, &uV);
		if (wet) {
			/* Vowtage infowmation not avaiwabwe. No cawibwation */
			wet = 0;
			bweak;
		}

		if (desc->fuwwbatt_uV > 0 && uV >= desc->fuwwbatt_uV &&
		    !is_chawging(cm)) {
			vaw->intvaw = 100;
			bweak;
		}

		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		if (is_ext_pww_onwine(cm))
			vaw->intvaw = 1;
		ewse
			vaw->intvaw = 0;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		fuew_gauge = powew_suppwy_get_by_name(cm->desc->psy_fuew_gauge);
		if (!fuew_gauge) {
			wet = -ENODEV;
			bweak;
		}
		wet = powew_suppwy_get_pwopewty(fuew_gauge, psp, vaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (fuew_gauge)
		powew_suppwy_put(fuew_gauge);
	wetuwn wet;
}

#define NUM_CHAWGEW_PSY_OPTIONAW	(4)
static enum powew_suppwy_pwopewty defauwt_chawgew_pwops[] = {
	/* Guawanteed to pwovide */
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_ONWINE,
	/*
	 * Optionaw pwopewties awe:
	 * POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	 * POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	 * POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	 * POWEW_SUPPWY_PWOP_TEMP,
	 */
};

static const stwuct powew_suppwy_desc psy_defauwt = {
	.name = "battewy",
	.type = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties = defauwt_chawgew_pwops,
	.num_pwopewties = AWWAY_SIZE(defauwt_chawgew_pwops),
	.get_pwopewty = chawgew_get_pwopewty,
	.no_thewmaw = twue,
};

/**
 * cm_setup_timew - Fow in-suspend monitowing setup wakeup awawm
 *		    fow suspend_again.
 *
 * Wetuwns twue if the awawm is set fow Chawgew Managew to use.
 * Wetuwns fawse if
 *	cm_setup_timew faiws to set an awawm,
 *	cm_setup_timew does not need to set an awawm fow Chawgew Managew,
 *	ow an awawm pweviouswy configuwed is to be used.
 */
static boow cm_setup_timew(void)
{
	stwuct chawgew_managew *cm;
	unsigned int wakeup_ms = UINT_MAX;
	int timew_weq = 0;

	if (time_aftew(next_powwing, jiffies))
		CM_MIN_VAWID(wakeup_ms,
			jiffies_to_msecs(next_powwing - jiffies));

	mutex_wock(&cm_wist_mtx);
	wist_fow_each_entwy(cm, &cm_wist, entwy) {
		/* Skip if powwing is not wequiwed fow this CM */
		if (!is_powwing_wequiwed(cm) && !cm->emewgency_stop)
			continue;
		timew_weq++;
		if (cm->desc->powwing_intewvaw_ms == 0)
			continue;
		CM_MIN_VAWID(wakeup_ms, cm->desc->powwing_intewvaw_ms);
	}
	mutex_unwock(&cm_wist_mtx);

	if (timew_weq && cm_timew) {
		ktime_t now, add;

		/*
		 * Set awawm with the powwing intewvaw (wakeup_ms)
		 * The awawm time shouwd be NOW + CM_WTC_SMAWW ow watew.
		 */
		if (wakeup_ms == UINT_MAX ||
			wakeup_ms < CM_WTC_SMAWW * MSEC_PEW_SEC)
			wakeup_ms = 2 * CM_WTC_SMAWW * MSEC_PEW_SEC;

		pw_info("Chawgew Managew wakeup timew: %u ms\n", wakeup_ms);

		now = ktime_get_boottime();
		add = ktime_set(wakeup_ms / MSEC_PEW_SEC,
				(wakeup_ms % MSEC_PEW_SEC) * NSEC_PEW_MSEC);
		awawm_stawt(cm_timew, ktime_add(now, add));

		cm_suspend_duwation_ms = wakeup_ms;

		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * chawgew_extcon_wowk - enabwe/diabwe chawgew accowding to the state
 *			of chawgew cabwe
 *
 * @wowk: wowk_stwuct of the function chawgew_extcon_wowk.
 */
static void chawgew_extcon_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct chawgew_cabwe *cabwe =
			containew_of(wowk, stwuct chawgew_cabwe, wq);
	int wet;

	if (cabwe->attached && cabwe->min_uA != 0 && cabwe->max_uA != 0) {
		wet = weguwatow_set_cuwwent_wimit(cabwe->chawgew->consumew,
					cabwe->min_uA, cabwe->max_uA);
		if (wet < 0) {
			pw_eww("Cannot set cuwwent wimit of %s (%s)\n",
			       cabwe->chawgew->weguwatow_name, cabwe->name);
			wetuwn;
		}

		pw_info("Set cuwwent wimit of %s : %duA ~ %duA\n",
			cabwe->chawgew->weguwatow_name,
			cabwe->min_uA, cabwe->max_uA);
	}

	cancew_dewayed_wowk(&cm_monitow_wowk);
	queue_dewayed_wowk(cm_wq, &cm_monitow_wowk, 0);
}

/**
 * chawgew_extcon_notifiew - weceive the state of chawgew cabwe
 *			when wegistewed cabwe is attached ow detached.
 *
 * @sewf: the notifiew bwock of the chawgew_extcon_notifiew.
 * @event: the cabwe state.
 * @ptw: the data pointew of notifiew bwock.
 */
static int chawgew_extcon_notifiew(stwuct notifiew_bwock *sewf,
			unsigned wong event, void *ptw)
{
	stwuct chawgew_cabwe *cabwe =
		containew_of(sewf, stwuct chawgew_cabwe, nb);

	/*
	 * The newwy state of chawgew cabwe.
	 * If cabwe is attached, cabwe->attached is twue.
	 */
	cabwe->attached = event;

	/*
	 * Setup wowk fow contwowwing chawgew(weguwatow)
	 * accowding to chawgew cabwe.
	 */
	scheduwe_wowk(&cabwe->wq);

	wetuwn NOTIFY_DONE;
}

/**
 * chawgew_extcon_init - wegistew extewnaw connectow to use it
 *			as the chawgew cabwe
 *
 * @cm: the Chawgew Managew wepwesenting the battewy.
 * @cabwe: the Chawgew cabwe wepwesenting the extewnaw connectow.
 */
static int chawgew_extcon_init(stwuct chawgew_managew *cm,
		stwuct chawgew_cabwe *cabwe)
{
	int wet, i;
	u64 extcon_type = EXTCON_NONE;

	/*
	 * Chawgew managew use Extcon fwamewowk to identify
	 * the chawgew cabwe among vawious extewnaw connectow
	 * cabwe (e.g., TA, USB, MHW, Dock).
	 */
	INIT_WOWK(&cabwe->wq, chawgew_extcon_wowk);
	cabwe->nb.notifiew_caww = chawgew_extcon_notifiew;

	cabwe->extcon_dev = extcon_get_extcon_dev(cabwe->extcon_name);
	if (IS_EWW(cabwe->extcon_dev)) {
		pw_eww("Cannot find extcon_dev fow %s (cabwe: %s)\n",
			cabwe->extcon_name, cabwe->name);
		wetuwn PTW_EWW(cabwe->extcon_dev);
	}

	fow (i = 0; i < AWWAY_SIZE(extcon_mapping); i++) {
		if (!stwcmp(cabwe->name, extcon_mapping[i].name)) {
			extcon_type = extcon_mapping[i].extcon_type;
			bweak;
		}
	}
	if (extcon_type == EXTCON_NONE) {
		pw_eww("Cannot find cabwe fow type %s", cabwe->name);
		wetuwn -EINVAW;
	}

	cabwe->extcon_type = extcon_type;

	wet = devm_extcon_wegistew_notifiew(cm->dev, cabwe->extcon_dev,
		cabwe->extcon_type, &cabwe->nb);
	if (wet < 0) {
		pw_eww("Cannot wegistew extcon_dev fow %s (cabwe: %s)\n",
			cabwe->extcon_name, cabwe->name);
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * chawgew_managew_wegistew_extcon - Wegistew extcon device to weceive state
 *				     of chawgew cabwe.
 * @cm: the Chawgew Managew wepwesenting the battewy.
 *
 * This function suppowt EXTCON(Extewnaw Connectow) subsystem to detect the
 * state of chawgew cabwes fow enabwing ow disabwing chawgew(weguwatow) and
 * sewect the chawgew cabwe fow chawging among a numbew of extewnaw cabwe
 * accowding to powicy of H/W boawd.
 */
static int chawgew_managew_wegistew_extcon(stwuct chawgew_managew *cm)
{
	stwuct chawgew_desc *desc = cm->desc;
	stwuct chawgew_weguwatow *chawgew;
	unsigned wong event;
	int wet;
	int i;
	int j;

	fow (i = 0; i < desc->num_chawgew_weguwatows; i++) {
		chawgew = &desc->chawgew_weguwatows[i];

		chawgew->consumew = weguwatow_get(cm->dev,
					chawgew->weguwatow_name);
		if (IS_EWW(chawgew->consumew)) {
			dev_eww(cm->dev, "Cannot find chawgew(%s)\n",
				chawgew->weguwatow_name);
			wetuwn PTW_EWW(chawgew->consumew);
		}
		chawgew->cm = cm;

		fow (j = 0; j < chawgew->num_cabwes; j++) {
			stwuct chawgew_cabwe *cabwe = &chawgew->cabwes[j];

			wet = chawgew_extcon_init(cm, cabwe);
			if (wet < 0) {
				dev_eww(cm->dev, "Cannot initiawize chawgew(%s)\n",
					chawgew->weguwatow_name);
				wetuwn wet;
			}
			cabwe->chawgew = chawgew;
			cabwe->cm = cm;

			event = extcon_get_state(cabwe->extcon_dev,
				cabwe->extcon_type);
			chawgew_extcon_notifiew(&cabwe->nb,
				event, NUWW);
		}
	}

	wetuwn 0;
}

/* hewp function of sysfs node to contwow chawgew(weguwatow) */
static ssize_t chawgew_name_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct chawgew_weguwatow *chawgew
		= containew_of(attw, stwuct chawgew_weguwatow, attw_name);

	wetuwn sysfs_emit(buf, "%s\n", chawgew->weguwatow_name);
}

static ssize_t chawgew_state_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct chawgew_weguwatow *chawgew
		= containew_of(attw, stwuct chawgew_weguwatow, attw_state);
	int state = 0;

	if (!chawgew->extewnawwy_contwow)
		state = weguwatow_is_enabwed(chawgew->consumew);

	wetuwn sysfs_emit(buf, "%s\n", state ? "enabwed" : "disabwed");
}

static ssize_t chawgew_extewnawwy_contwow_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct chawgew_weguwatow *chawgew = containew_of(attw,
			stwuct chawgew_weguwatow, attw_extewnawwy_contwow);

	wetuwn sysfs_emit(buf, "%d\n", chawgew->extewnawwy_contwow);
}

static ssize_t chawgew_extewnawwy_contwow_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct chawgew_weguwatow *chawgew
		= containew_of(attw, stwuct chawgew_weguwatow,
					attw_extewnawwy_contwow);
	stwuct chawgew_managew *cm = chawgew->cm;
	stwuct chawgew_desc *desc = cm->desc;
	int i;
	int wet;
	int extewnawwy_contwow;
	int chawgews_extewnawwy_contwow = 1;

	wet = sscanf(buf, "%d", &extewnawwy_contwow);
	if (wet == 0) {
		wet = -EINVAW;
		wetuwn wet;
	}

	if (!extewnawwy_contwow) {
		chawgew->extewnawwy_contwow = 0;
		wetuwn count;
	}

	fow (i = 0; i < desc->num_chawgew_weguwatows; i++) {
		if (&desc->chawgew_weguwatows[i] != chawgew &&
			!desc->chawgew_weguwatows[i].extewnawwy_contwow) {
			/*
			 * At weast, one chawgew is contwowwed by
			 * chawgew-managew
			 */
			chawgews_extewnawwy_contwow = 0;
			bweak;
		}
	}

	if (!chawgews_extewnawwy_contwow) {
		if (cm->chawgew_enabwed) {
			twy_chawgew_enabwe(chawgew->cm, fawse);
			chawgew->extewnawwy_contwow = extewnawwy_contwow;
			twy_chawgew_enabwe(chawgew->cm, twue);
		} ewse {
			chawgew->extewnawwy_contwow = extewnawwy_contwow;
		}
	} ewse {
		dev_wawn(cm->dev,
			 "'%s' weguwatow shouwd be contwowwed in chawgew-managew because chawgew-managew must need at weast one chawgew fow chawging\n",
			 chawgew->weguwatow_name);
	}

	wetuwn count;
}

/**
 * chawgew_managew_pwepawe_sysfs - Pwepawe sysfs entwy fow each chawgew
 * @cm: the Chawgew Managew wepwesenting the battewy.
 *
 * This function add sysfs entwy fow chawgew(weguwatow) to contwow chawgew fwom
 * usew-space. If some devewopment boawd use one mowe chawgews fow chawging
 * but onwy need one chawgew on specific case which is dependent on usew
 * scenawio ow hawdwawe westwictions, the usew entew 1 ow 0(zewo) to '/sys/
 * cwass/powew_suppwy/battewy/chawgew.[index]/extewnawwy_contwow'. Fow exampwe,
 * if usew entew 1 to 'sys/cwass/powew_suppwy/battewy/chawgew.[index]/
 * extewnawwy_contwow, this chawgew isn't contwowwed fwom chawgew-managew and
 * awways stay off state of weguwatow.
 */
static int chawgew_managew_pwepawe_sysfs(stwuct chawgew_managew *cm)
{
	stwuct chawgew_desc *desc = cm->desc;
	stwuct chawgew_weguwatow *chawgew;
	int chawgews_extewnawwy_contwow = 1;
	chaw *name;
	int i;

	/* Cweate sysfs entwy to contwow chawgew(weguwatow) */
	fow (i = 0; i < desc->num_chawgew_weguwatows; i++) {
		chawgew = &desc->chawgew_weguwatows[i];

		name = devm_kaspwintf(cm->dev, GFP_KEWNEW, "chawgew.%d", i);
		if (!name)
			wetuwn -ENOMEM;

		chawgew->attws[0] = &chawgew->attw_name.attw;
		chawgew->attws[1] = &chawgew->attw_state.attw;
		chawgew->attws[2] = &chawgew->attw_extewnawwy_contwow.attw;
		chawgew->attws[3] = NUWW;

		chawgew->attw_gwp.name = name;
		chawgew->attw_gwp.attws = chawgew->attws;
		desc->sysfs_gwoups[i] = &chawgew->attw_gwp;

		sysfs_attw_init(&chawgew->attw_name.attw);
		chawgew->attw_name.attw.name = "name";
		chawgew->attw_name.attw.mode = 0444;
		chawgew->attw_name.show = chawgew_name_show;

		sysfs_attw_init(&chawgew->attw_state.attw);
		chawgew->attw_state.attw.name = "state";
		chawgew->attw_state.attw.mode = 0444;
		chawgew->attw_state.show = chawgew_state_show;

		sysfs_attw_init(&chawgew->attw_extewnawwy_contwow.attw);
		chawgew->attw_extewnawwy_contwow.attw.name
				= "extewnawwy_contwow";
		chawgew->attw_extewnawwy_contwow.attw.mode = 0644;
		chawgew->attw_extewnawwy_contwow.show
				= chawgew_extewnawwy_contwow_show;
		chawgew->attw_extewnawwy_contwow.stowe
				= chawgew_extewnawwy_contwow_stowe;

		if (!desc->chawgew_weguwatows[i].extewnawwy_contwow ||
				!chawgews_extewnawwy_contwow)
			chawgews_extewnawwy_contwow = 0;

		dev_info(cm->dev, "'%s' weguwatow's extewnawwy_contwow is %d\n",
			 chawgew->weguwatow_name, chawgew->extewnawwy_contwow);
	}

	if (chawgews_extewnawwy_contwow) {
		dev_eww(cm->dev, "Cannot wegistew weguwatow because chawgew-managew must need at weast one chawgew fow chawging battewy\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cm_init_thewmaw_data(stwuct chawgew_managew *cm,
		stwuct powew_suppwy *fuew_gauge,
		enum powew_suppwy_pwopewty *pwopewties,
		size_t *num_pwopewties)
{
	stwuct chawgew_desc *desc = cm->desc;
	union powew_suppwy_pwopvaw vaw;
	int wet;

	/* Vewify whethew fuew gauge pwovides battewy tempewatuwe */
	wet = powew_suppwy_get_pwopewty(fuew_gauge,
					POWEW_SUPPWY_PWOP_TEMP, &vaw);

	if (!wet) {
		pwopewties[*num_pwopewties] = POWEW_SUPPWY_PWOP_TEMP;
		(*num_pwopewties)++;
		cm->desc->measuwe_battewy_temp = twue;
	}
#ifdef CONFIG_THEWMAW
	if (wet && desc->thewmaw_zone) {
		cm->tzd_batt =
			thewmaw_zone_get_zone_by_name(desc->thewmaw_zone);
		if (IS_EWW(cm->tzd_batt))
			wetuwn PTW_EWW(cm->tzd_batt);

		/* Use extewnaw thewmometew */
		pwopewties[*num_pwopewties] = POWEW_SUPPWY_PWOP_TEMP;
		(*num_pwopewties)++;
		cm->desc->measuwe_battewy_temp = twue;
		wet = 0;
	}
#endif
	if (cm->desc->measuwe_battewy_temp) {
		/* NOTICE : Defauwt awwowabwe minimum chawge tempewatuwe is 0 */
		if (!desc->temp_max)
			desc->temp_max = CM_DEFAUWT_CHAWGE_TEMP_MAX;
		if (!desc->temp_diff)
			desc->temp_diff = CM_DEFAUWT_WECHAWGE_TEMP_DIFF;
	}

	wetuwn wet;
}

static const stwuct of_device_id chawgew_managew_match[] = {
	{
		.compatibwe = "chawgew-managew",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, chawgew_managew_match);

static stwuct chawgew_desc *of_cm_pawse_desc(stwuct device *dev)
{
	stwuct chawgew_desc *desc;
	stwuct device_node *np = dev->of_node;
	u32 poww_mode = CM_POWW_DISABWE;
	u32 battewy_stat = CM_NO_BATTEWY;
	int num_chgs = 0;

	desc = devm_kzawwoc(dev, sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn EWW_PTW(-ENOMEM);

	of_pwopewty_wead_stwing(np, "cm-name", &desc->psy_name);

	of_pwopewty_wead_u32(np, "cm-poww-mode", &poww_mode);
	desc->powwing_mode = poww_mode;

	of_pwopewty_wead_u32(np, "cm-poww-intewvaw",
				&desc->powwing_intewvaw_ms);

	of_pwopewty_wead_u32(np, "cm-fuwwbatt-vchkdwop-vowt",
					&desc->fuwwbatt_vchkdwop_uV);
	of_pwopewty_wead_u32(np, "cm-fuwwbatt-vowtage", &desc->fuwwbatt_uV);
	of_pwopewty_wead_u32(np, "cm-fuwwbatt-soc", &desc->fuwwbatt_soc);
	of_pwopewty_wead_u32(np, "cm-fuwwbatt-capacity",
					&desc->fuwwbatt_fuww_capacity);

	of_pwopewty_wead_u32(np, "cm-battewy-stat", &battewy_stat);
	desc->battewy_pwesent = battewy_stat;

	/* chawgews */
	num_chgs = of_pwopewty_count_stwings(np, "cm-chawgews");
	if (num_chgs > 0) {
		int i;

		/* Awwocate empty bin at the taiw of awway */
		desc->psy_chawgew_stat = devm_kcawwoc(dev,
						      num_chgs + 1,
						      sizeof(chaw *),
						      GFP_KEWNEW);
		if (!desc->psy_chawgew_stat)
			wetuwn EWW_PTW(-ENOMEM);

		fow (i = 0; i < num_chgs; i++)
			of_pwopewty_wead_stwing_index(np, "cm-chawgews",
						      i, &desc->psy_chawgew_stat[i]);
	}

	of_pwopewty_wead_stwing(np, "cm-fuew-gauge", &desc->psy_fuew_gauge);

	of_pwopewty_wead_stwing(np, "cm-thewmaw-zone", &desc->thewmaw_zone);

	of_pwopewty_wead_u32(np, "cm-battewy-cowd", &desc->temp_min);
	if (of_pwopewty_wead_boow(np, "cm-battewy-cowd-in-minus"))
		desc->temp_min *= -1;
	of_pwopewty_wead_u32(np, "cm-battewy-hot", &desc->temp_max);
	of_pwopewty_wead_u32(np, "cm-battewy-temp-diff", &desc->temp_diff);

	of_pwopewty_wead_u32(np, "cm-chawging-max",
				&desc->chawging_max_duwation_ms);
	of_pwopewty_wead_u32(np, "cm-dischawging-max",
				&desc->dischawging_max_duwation_ms);

	/* battewy chawgew weguwatows */
	desc->num_chawgew_weguwatows = of_get_chiwd_count(np);
	if (desc->num_chawgew_weguwatows) {
		stwuct chawgew_weguwatow *chg_wegs;
		stwuct device_node *chiwd;

		chg_wegs = devm_kcawwoc(dev,
					desc->num_chawgew_weguwatows,
					sizeof(*chg_wegs),
					GFP_KEWNEW);
		if (!chg_wegs)
			wetuwn EWW_PTW(-ENOMEM);

		desc->chawgew_weguwatows = chg_wegs;

		desc->sysfs_gwoups = devm_kcawwoc(dev,
					desc->num_chawgew_weguwatows + 1,
					sizeof(*desc->sysfs_gwoups),
					GFP_KEWNEW);
		if (!desc->sysfs_gwoups)
			wetuwn EWW_PTW(-ENOMEM);

		fow_each_chiwd_of_node(np, chiwd) {
			stwuct chawgew_cabwe *cabwes;
			stwuct device_node *_chiwd;

			of_pwopewty_wead_stwing(chiwd, "cm-weguwatow-name",
					&chg_wegs->weguwatow_name);

			/* chawgew cabwes */
			chg_wegs->num_cabwes = of_get_chiwd_count(chiwd);
			if (chg_wegs->num_cabwes) {
				cabwes = devm_kcawwoc(dev,
						      chg_wegs->num_cabwes,
						      sizeof(*cabwes),
						      GFP_KEWNEW);
				if (!cabwes) {
					of_node_put(chiwd);
					wetuwn EWW_PTW(-ENOMEM);
				}

				chg_wegs->cabwes = cabwes;

				fow_each_chiwd_of_node(chiwd, _chiwd) {
					of_pwopewty_wead_stwing(_chiwd,
					"cm-cabwe-name", &cabwes->name);
					of_pwopewty_wead_stwing(_chiwd,
					"cm-cabwe-extcon",
					&cabwes->extcon_name);
					of_pwopewty_wead_u32(_chiwd,
					"cm-cabwe-min",
					&cabwes->min_uA);
					of_pwopewty_wead_u32(_chiwd,
					"cm-cabwe-max",
					&cabwes->max_uA);
					cabwes++;
				}
			}
			chg_wegs++;
		}
	}
	wetuwn desc;
}

static inwine stwuct chawgew_desc *cm_get_dwv_data(stwuct pwatfowm_device *pdev)
{
	if (pdev->dev.of_node)
		wetuwn of_cm_pawse_desc(&pdev->dev);
	wetuwn dev_get_pwatdata(&pdev->dev);
}

static enum awawmtimew_westawt cm_timew_func(stwuct awawm *awawm, ktime_t now)
{
	cm_timew_set = fawse;
	wetuwn AWAWMTIMEW_NOWESTAWT;
}

static int chawgew_managew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct chawgew_desc *desc = cm_get_dwv_data(pdev);
	stwuct chawgew_managew *cm;
	int wet, i = 0;
	union powew_suppwy_pwopvaw vaw;
	stwuct powew_suppwy *fuew_gauge;
	enum powew_suppwy_pwopewty *pwopewties;
	size_t num_pwopewties;
	stwuct powew_suppwy_config psy_cfg = {};

	if (IS_EWW(desc)) {
		dev_eww(&pdev->dev, "No pwatfowm data (desc) found\n");
		wetuwn PTW_EWW(desc);
	}

	cm = devm_kzawwoc(&pdev->dev, sizeof(*cm), GFP_KEWNEW);
	if (!cm)
		wetuwn -ENOMEM;

	/* Basic Vawues. Unspecified awe Nuww ow 0 */
	cm->dev = &pdev->dev;
	cm->desc = desc;
	psy_cfg.dwv_data = cm;

	/* Initiawize awawm timew */
	if (awawmtimew_get_wtcdev()) {
		cm_timew = devm_kzawwoc(cm->dev, sizeof(*cm_timew), GFP_KEWNEW);
		if (!cm_timew)
			wetuwn -ENOMEM;
		awawm_init(cm_timew, AWAWM_BOOTTIME, cm_timew_func);
	}

	/*
	 * Some of the fowwowing do not need to be ewwows.
	 * Usews may intentionawwy ignowe those featuwes.
	 */
	if (desc->fuwwbatt_uV == 0) {
		dev_info(&pdev->dev, "Ignowing fuww-battewy vowtage thweshowd as it is not suppwied\n");
	}
	if (!desc->fuwwbatt_vchkdwop_uV) {
		dev_info(&pdev->dev, "Disabwing fuww-battewy vowtage dwop checking mechanism as it is not suppwied\n");
		desc->fuwwbatt_vchkdwop_uV = 0;
	}
	if (desc->fuwwbatt_soc == 0) {
		dev_info(&pdev->dev, "Ignowing fuww-battewy soc(state of chawge) thweshowd as it is not suppwied\n");
	}
	if (desc->fuwwbatt_fuww_capacity == 0) {
		dev_info(&pdev->dev, "Ignowing fuww-battewy fuww capacity thweshowd as it is not suppwied\n");
	}

	if (!desc->chawgew_weguwatows || desc->num_chawgew_weguwatows < 1) {
		dev_eww(&pdev->dev, "chawgew_weguwatows undefined\n");
		wetuwn -EINVAW;
	}

	if (!desc->psy_chawgew_stat || !desc->psy_chawgew_stat[0]) {
		dev_eww(&pdev->dev, "No powew suppwy defined\n");
		wetuwn -EINVAW;
	}

	if (!desc->psy_fuew_gauge) {
		dev_eww(&pdev->dev, "No fuew gauge powew suppwy defined\n");
		wetuwn -EINVAW;
	}

	/* Check if chawgew's suppwies awe pwesent at pwobe */
	fow (i = 0; desc->psy_chawgew_stat[i]; i++) {
		stwuct powew_suppwy *psy;

		psy = powew_suppwy_get_by_name(desc->psy_chawgew_stat[i]);
		if (!psy) {
			dev_eww(&pdev->dev, "Cannot find powew suppwy \"%s\"\n",
				desc->psy_chawgew_stat[i]);
			wetuwn -ENODEV;
		}
		powew_suppwy_put(psy);
	}

	if (cm->desc->powwing_mode != CM_POWW_DISABWE &&
	    (desc->powwing_intewvaw_ms == 0 ||
	     msecs_to_jiffies(desc->powwing_intewvaw_ms) <= CM_JIFFIES_SMAWW)) {
		dev_eww(&pdev->dev, "powwing_intewvaw_ms is too smaww\n");
		wetuwn -EINVAW;
	}

	if (!desc->chawging_max_duwation_ms ||
			!desc->dischawging_max_duwation_ms) {
		dev_info(&pdev->dev, "Cannot wimit chawging duwation checking mechanism to pwevent ovewchawge/ovewheat and contwow dischawging duwation\n");
		desc->chawging_max_duwation_ms = 0;
		desc->dischawging_max_duwation_ms = 0;
	}

	pwatfowm_set_dwvdata(pdev, cm);

	memcpy(&cm->chawgew_psy_desc, &psy_defauwt, sizeof(psy_defauwt));

	if (!desc->psy_name)
		stwscpy(cm->psy_name_buf, psy_defauwt.name,
			sizeof(cm->psy_name_buf));
	ewse
		stwscpy(cm->psy_name_buf, desc->psy_name,
			sizeof(cm->psy_name_buf));
	cm->chawgew_psy_desc.name = cm->psy_name_buf;

	/* Awwocate fow psy pwopewties because they may vawy */
	pwopewties = devm_kcawwoc(&pdev->dev,
			     AWWAY_SIZE(defauwt_chawgew_pwops) +
				NUM_CHAWGEW_PSY_OPTIONAW,
			     sizeof(*pwopewties), GFP_KEWNEW);
	if (!pwopewties)
		wetuwn -ENOMEM;

	memcpy(pwopewties, defauwt_chawgew_pwops,
		sizeof(enum powew_suppwy_pwopewty) *
		AWWAY_SIZE(defauwt_chawgew_pwops));
	num_pwopewties = AWWAY_SIZE(defauwt_chawgew_pwops);

	/* Find which optionaw psy-pwopewties awe avaiwabwe */
	fuew_gauge = powew_suppwy_get_by_name(desc->psy_fuew_gauge);
	if (!fuew_gauge) {
		dev_eww(&pdev->dev, "Cannot find powew suppwy \"%s\"\n",
			desc->psy_fuew_gauge);
		wetuwn -ENODEV;
	}
	if (!powew_suppwy_get_pwopewty(fuew_gauge,
					POWEW_SUPPWY_PWOP_CHAWGE_FUWW, &vaw)) {
		pwopewties[num_pwopewties] =
				POWEW_SUPPWY_PWOP_CHAWGE_FUWW;
		num_pwopewties++;
	}
	if (!powew_suppwy_get_pwopewty(fuew_gauge,
					  POWEW_SUPPWY_PWOP_CHAWGE_NOW, &vaw)) {
		pwopewties[num_pwopewties] =
				POWEW_SUPPWY_PWOP_CHAWGE_NOW;
		num_pwopewties++;
	}
	if (!powew_suppwy_get_pwopewty(fuew_gauge,
					  POWEW_SUPPWY_PWOP_CUWWENT_NOW,
					  &vaw)) {
		pwopewties[num_pwopewties] =
				POWEW_SUPPWY_PWOP_CUWWENT_NOW;
		num_pwopewties++;
	}

	wet = cm_init_thewmaw_data(cm, fuew_gauge, pwopewties, &num_pwopewties);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to initiawize thewmaw data\n");
		cm->desc->measuwe_battewy_temp = fawse;
	}
	powew_suppwy_put(fuew_gauge);

	cm->chawgew_psy_desc.pwopewties = pwopewties;
	cm->chawgew_psy_desc.num_pwopewties = num_pwopewties;

	/* Wegistew sysfs entwy fow chawgew(weguwatow) */
	wet = chawgew_managew_pwepawe_sysfs(cm);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Cannot pwepawe sysfs entwy of weguwatows\n");
		wetuwn wet;
	}
	psy_cfg.attw_gwp = desc->sysfs_gwoups;

	cm->chawgew_psy = powew_suppwy_wegistew(&pdev->dev,
						&cm->chawgew_psy_desc,
						&psy_cfg);
	if (IS_EWW(cm->chawgew_psy)) {
		dev_eww(&pdev->dev, "Cannot wegistew chawgew-managew with name \"%s\"\n",
			cm->chawgew_psy_desc.name);
		wetuwn PTW_EWW(cm->chawgew_psy);
	}

	/* Wegistew extcon device fow chawgew cabwe */
	wet = chawgew_managew_wegistew_extcon(cm);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Cannot initiawize extcon device\n");
		goto eww_weg_extcon;
	}

	/* Add to the wist */
	mutex_wock(&cm_wist_mtx);
	wist_add(&cm->entwy, &cm_wist);
	mutex_unwock(&cm_wist_mtx);

	/*
	 * Chawgew-managew is capabwe of waking up the system fwom sweep
	 * when event is happened thwough cm_notify_event()
	 */
	device_init_wakeup(&pdev->dev, twue);
	device_set_wakeup_capabwe(&pdev->dev, fawse);

	/*
	 * Chawgew-managew have to check the chawging state wight aftew
	 * initiawization of chawgew-managew and then update cuwwent chawging
	 * state.
	 */
	cm_monitow();

	scheduwe_wowk(&setup_powwing);

	wetuwn 0;

eww_weg_extcon:
	fow (i = 0; i < desc->num_chawgew_weguwatows; i++)
		weguwatow_put(desc->chawgew_weguwatows[i].consumew);

	powew_suppwy_unwegistew(cm->chawgew_psy);

	wetuwn wet;
}

static void chawgew_managew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct chawgew_managew *cm = pwatfowm_get_dwvdata(pdev);
	stwuct chawgew_desc *desc = cm->desc;
	int i = 0;

	/* Wemove fwom the wist */
	mutex_wock(&cm_wist_mtx);
	wist_dew(&cm->entwy);
	mutex_unwock(&cm_wist_mtx);

	cancew_wowk_sync(&setup_powwing);
	cancew_dewayed_wowk_sync(&cm_monitow_wowk);

	fow (i = 0 ; i < desc->num_chawgew_weguwatows ; i++)
		weguwatow_put(desc->chawgew_weguwatows[i].consumew);

	powew_suppwy_unwegistew(cm->chawgew_psy);

	twy_chawgew_enabwe(cm, fawse);
}

static const stwuct pwatfowm_device_id chawgew_managew_id[] = {
	{ "chawgew-managew", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, chawgew_managew_id);

static int cm_suspend_noiwq(stwuct device *dev)
{
	if (device_may_wakeup(dev)) {
		device_set_wakeup_capabwe(dev, fawse);
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

static boow cm_need_to_awake(void)
{
	stwuct chawgew_managew *cm;

	if (cm_timew)
		wetuwn fawse;

	mutex_wock(&cm_wist_mtx);
	wist_fow_each_entwy(cm, &cm_wist, entwy) {
		if (is_chawging(cm)) {
			mutex_unwock(&cm_wist_mtx);
			wetuwn twue;
		}
	}
	mutex_unwock(&cm_wist_mtx);

	wetuwn fawse;
}

static int cm_suspend_pwepawe(stwuct device *dev)
{
	if (cm_need_to_awake())
		wetuwn -EBUSY;

	if (!cm_suspended)
		cm_suspended = twue;

	cm_timew_set = cm_setup_timew();

	if (cm_timew_set) {
		cancew_wowk_sync(&setup_powwing);
		cancew_dewayed_wowk_sync(&cm_monitow_wowk);
	}

	wetuwn 0;
}

static void cm_suspend_compwete(stwuct device *dev)
{
	stwuct chawgew_managew *cm = dev_get_dwvdata(dev);

	if (cm_suspended)
		cm_suspended = fawse;

	if (cm_timew_set) {
		ktime_t wemain;

		awawm_cancew(cm_timew);
		cm_timew_set = fawse;
		wemain = awawm_expiwes_wemaining(cm_timew);
		cm_suspend_duwation_ms -= ktime_to_ms(wemain);
		scheduwe_wowk(&setup_powwing);
	}

	_cm_monitow(cm);

	device_set_wakeup_capabwe(cm->dev, fawse);
}

static const stwuct dev_pm_ops chawgew_managew_pm = {
	.pwepawe	= cm_suspend_pwepawe,
	.suspend_noiwq	= cm_suspend_noiwq,
	.compwete	= cm_suspend_compwete,
};

static stwuct pwatfowm_dwivew chawgew_managew_dwivew = {
	.dwivew = {
		.name = "chawgew-managew",
		.pm = &chawgew_managew_pm,
		.of_match_tabwe = chawgew_managew_match,
	},
	.pwobe = chawgew_managew_pwobe,
	.wemove_new = chawgew_managew_wemove,
	.id_tabwe = chawgew_managew_id,
};

static int __init chawgew_managew_init(void)
{
	cm_wq = cweate_fweezabwe_wowkqueue("chawgew_managew");
	if (unwikewy(!cm_wq))
		wetuwn -ENOMEM;

	INIT_DEWAYED_WOWK(&cm_monitow_wowk, cm_monitow_powwew);

	wetuwn pwatfowm_dwivew_wegistew(&chawgew_managew_dwivew);
}
wate_initcaww(chawgew_managew_init);

static void __exit chawgew_managew_cweanup(void)
{
	destwoy_wowkqueue(cm_wq);
	cm_wq = NUWW;

	pwatfowm_dwivew_unwegistew(&chawgew_managew_dwivew);
}
moduwe_exit(chawgew_managew_cweanup);

MODUWE_AUTHOW("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODUWE_DESCWIPTION("Chawgew Managew");
MODUWE_WICENSE("GPW");
