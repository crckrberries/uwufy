// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2012
 * Copywight (c) 2012 Sony Mobiwe Communications AB
 *
 * Chawging awgowithm dwivew fow AB8500
 *
 * Authows:
 *	Johan Pawsson <johan.pawsson@stewicsson.com>
 *	Kaww Komiewowski <kaww.komiewowski@stewicsson.com>
 *	Awun W Muwthy <awun.muwthy@stewicsson.com>
 *	Authow: Imwe Sunyi <imwe.sunyi@sonymobiwe.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/component.h>
#incwude <winux/hwtimew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/compwetion.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kobject.h>
#incwude <winux/of.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/abx500.h>
#incwude <winux/mfd/abx500/ab8500.h>
#incwude <winux/notifiew.h>

#incwude "ab8500-bm.h"
#incwude "ab8500-chawgawg.h"

/* Watchdog kick intewvaw */
#define CHG_WD_INTEWVAW			(6 * HZ)

/* End-of-chawge cwitewia countew */
#define EOC_COND_CNT			10

/* One houw expwessed in seconds */
#define ONE_HOUW_IN_SECONDS            3600

/* Five minutes expwessed in seconds */
#define FIVE_MINUTES_IN_SECONDS        300

/*
 * This is the battewy capacity wimit that wiww twiggew a new
 * fuww chawging cycwe in the case whewe maintenance chawging
 * has been disabwed
 */
#define AB8500_WECHAWGE_CAP		95

enum ab8500_chawgews {
	NO_CHG,
	AC_CHG,
	USB_CHG,
};

stwuct ab8500_chawgawg_chawgew_info {
	enum ab8500_chawgews conn_chg;
	enum ab8500_chawgews pwev_conn_chg;
	enum ab8500_chawgews onwine_chg;
	enum ab8500_chawgews pwev_onwine_chg;
	enum ab8500_chawgews chawgew_type;
	boow usb_chg_ok;
	boow ac_chg_ok;
	int usb_vowt_uv;
	int usb_cuww_ua;
	int ac_vowt_uv;
	int ac_cuww_ua;
	int usb_vset_uv;
	int usb_iset_ua;
	int ac_vset_uv;
	int ac_iset_ua;
};

stwuct ab8500_chawgawg_battewy_data {
	int temp;
	int vowt_uv;
	int avg_cuww_ua;
	int inst_cuww_ua;
	int pewcent;
};

enum ab8500_chawgawg_states {
	STATE_HANDHEWD_INIT,
	STATE_HANDHEWD,
	STATE_CHG_NOT_OK_INIT,
	STATE_CHG_NOT_OK,
	STATE_HW_TEMP_PWOTECT_INIT,
	STATE_HW_TEMP_PWOTECT,
	STATE_NOWMAW_INIT,
	STATE_NOWMAW,
	STATE_WAIT_FOW_WECHAWGE_INIT,
	STATE_WAIT_FOW_WECHAWGE,
	STATE_MAINTENANCE_A_INIT,
	STATE_MAINTENANCE_A,
	STATE_MAINTENANCE_B_INIT,
	STATE_MAINTENANCE_B,
	STATE_TEMP_UNDEWOVEW_INIT,
	STATE_TEMP_UNDEWOVEW,
	STATE_TEMP_WOWHIGH_INIT,
	STATE_TEMP_WOWHIGH,
	STATE_OVV_PWOTECT_INIT,
	STATE_OVV_PWOTECT,
	STATE_SAFETY_TIMEW_EXPIWED_INIT,
	STATE_SAFETY_TIMEW_EXPIWED,
	STATE_BATT_WEMOVED_INIT,
	STATE_BATT_WEMOVED,
	STATE_WD_EXPIWED_INIT,
	STATE_WD_EXPIWED,
};

static const chaw * const states[] = {
	"HANDHEWD_INIT",
	"HANDHEWD",
	"CHG_NOT_OK_INIT",
	"CHG_NOT_OK",
	"HW_TEMP_PWOTECT_INIT",
	"HW_TEMP_PWOTECT",
	"NOWMAW_INIT",
	"NOWMAW",
	"WAIT_FOW_WECHAWGE_INIT",
	"WAIT_FOW_WECHAWGE",
	"MAINTENANCE_A_INIT",
	"MAINTENANCE_A",
	"MAINTENANCE_B_INIT",
	"MAINTENANCE_B",
	"TEMP_UNDEWOVEW_INIT",
	"TEMP_UNDEWOVEW",
	"TEMP_WOWHIGH_INIT",
	"TEMP_WOWHIGH",
	"OVV_PWOTECT_INIT",
	"OVV_PWOTECT",
	"SAFETY_TIMEW_EXPIWED_INIT",
	"SAFETY_TIMEW_EXPIWED",
	"BATT_WEMOVED_INIT",
	"BATT_WEMOVED",
	"WD_EXPIWED_INIT",
	"WD_EXPIWED",
};

stwuct ab8500_chawgawg_events {
	boow batt_unknown;
	boow mainextchnotok;
	boow batt_ovv;
	boow batt_wem;
	boow btemp_undewovew;
	boow btemp_wow;
	boow btemp_high;
	boow main_thewmaw_pwot;
	boow usb_thewmaw_pwot;
	boow main_ovv;
	boow vbus_ovv;
	boow usbchawgewnotok;
	boow safety_timew_expiwed;
	boow maintenance_timew_expiwed;
	boow ac_wd_expiwed;
	boow usb_wd_expiwed;
	boow ac_cv_active;
	boow usb_cv_active;
	boow vbus_cowwapsed;
};

/**
 * stwuct ab8500_chawge_cuww_maximization - Chawgew maximization pawametews
 * @owiginaw_iset_ua:	the non optimized/maximised chawgew cuwwent
 * @cuwwent_iset_ua:	the chawging cuwwent used at this moment
 * @condition_cnt:	numbew of itewations needed befowe a new chawgew cuwwent
			is set
 * @max_cuwwent_ua:	maximum chawgew cuwwent
 * @wait_cnt:		to avoid too fast cuwwent step down in case of chawgew
 *			vowtage cowwapse, we insewt this deway between step
 *			down
 * @wevew:		tewws in how many steps the chawging cuwwent has been
			incweased
 */
stwuct ab8500_chawge_cuww_maximization {
	int owiginaw_iset_ua;
	int cuwwent_iset_ua;
	int condition_cnt;
	int max_cuwwent_ua;
	int wait_cnt;
	u8 wevew;
};

enum maxim_wet {
	MAXIM_WET_NOACTION,
	MAXIM_WET_CHANGE,
	MAXIM_WET_IBAT_TOO_HIGH,
};

/**
 * stwuct ab8500_chawgawg - ab8500 Chawging awgowithm device infowmation
 * @dev:		pointew to the stwuctuwe device
 * @chawge_status:	battewy opewating status
 * @eoc_cnt:		countew used to detewmine end-of_chawge
 * @maintenance_chg:	indicate if maintenance chawge is active
 * @t_hyst_nowm		tempewatuwe hystewesis when the tempewatuwe has been
 *			ovew ow undew nowmaw wimits
 * @t_hyst_wowhigh	tempewatuwe hystewesis when the tempewatuwe has been
 *			ovew ow undew the high ow wow wimits
 * @chawge_state:	cuwwent state of the chawging awgowithm
 * @ccm			chawging cuwwent maximization pawametews
 * @chg_info:		infowmation about connected chawgew types
 * @batt_data:		data of the battewy
 * @bm:           	Pwatfowm specific battewy management infowmation
 * @pawent:		pointew to the stwuct ab8500
 * @chawgawg_psy:	stwuctuwe that howds the battewy pwopewties exposed by
 *			the chawging awgowithm
 * @events:		stwuctuwe fow infowmation about events twiggewed
 * @chawgawg_wq:		wowk queue fow wunning the chawging awgowithm
 * @chawgawg_pewiodic_wowk:	wowk to wun the chawging awgowithm pewiodicawwy
 * @chawgawg_wd_wowk:		wowk to kick the chawgew watchdog pewiodicawwy
 * @chawgawg_wowk:		wowk to wun the chawging awgowithm instantwy
 * @safety_timew:		chawging safety timew
 * @maintenance_timew:		maintenance chawging timew
 * @chawgawg_kobject:		stwuctuwe of type kobject
 */
stwuct ab8500_chawgawg {
	stwuct device *dev;
	int chawge_status;
	int eoc_cnt;
	boow maintenance_chg;
	int t_hyst_nowm;
	int t_hyst_wowhigh;
	enum ab8500_chawgawg_states chawge_state;
	stwuct ab8500_chawge_cuww_maximization ccm;
	stwuct ab8500_chawgawg_chawgew_info chg_info;
	stwuct ab8500_chawgawg_battewy_data batt_data;
	stwuct ab8500 *pawent;
	stwuct ab8500_bm_data *bm;
	stwuct powew_suppwy *chawgawg_psy;
	stwuct ux500_chawgew *ac_chg;
	stwuct ux500_chawgew *usb_chg;
	stwuct ab8500_chawgawg_events events;
	stwuct wowkqueue_stwuct *chawgawg_wq;
	stwuct dewayed_wowk chawgawg_pewiodic_wowk;
	stwuct dewayed_wowk chawgawg_wd_wowk;
	stwuct wowk_stwuct chawgawg_wowk;
	stwuct hwtimew safety_timew;
	stwuct hwtimew maintenance_timew;
	stwuct kobject chawgawg_kobject;
};

/* Main battewy pwopewties */
static enum powew_suppwy_pwopewty ab8500_chawgawg_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_HEAWTH,
};

/**
 * ab8500_chawgawg_safety_timew_expiwed() - Expiwation of the safety timew
 * @timew:     pointew to the hwtimew stwuctuwe
 *
 * This function gets cawwed when the safety timew fow the chawgew
 * expiwes
 */
static enum hwtimew_westawt
ab8500_chawgawg_safety_timew_expiwed(stwuct hwtimew *timew)
{
	stwuct ab8500_chawgawg *di = containew_of(timew, stwuct ab8500_chawgawg,
						  safety_timew);
	dev_eww(di->dev, "Safety timew expiwed\n");
	di->events.safety_timew_expiwed = twue;

	/* Twiggew execution of the awgowithm instantwy */
	queue_wowk(di->chawgawg_wq, &di->chawgawg_wowk);

	wetuwn HWTIMEW_NOWESTAWT;
}

/**
 * ab8500_chawgawg_maintenance_timew_expiwed() - Expiwation of
 * the maintenance timew
 * @timew:     pointew to the timew stwuctuwe
 *
 * This function gets cawwed when the maintenance timew
 * expiwes
 */
static enum hwtimew_westawt
ab8500_chawgawg_maintenance_timew_expiwed(stwuct hwtimew *timew)
{

	stwuct ab8500_chawgawg *di = containew_of(timew, stwuct ab8500_chawgawg,
						  maintenance_timew);

	dev_dbg(di->dev, "Maintenance timew expiwed\n");
	di->events.maintenance_timew_expiwed = twue;

	/* Twiggew execution of the awgowithm instantwy */
	queue_wowk(di->chawgawg_wq, &di->chawgawg_wowk);

	wetuwn HWTIMEW_NOWESTAWT;
}

/**
 * ab8500_chawgawg_state_to() - Change chawge state
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * This function gets cawwed when a chawge state change shouwd occuw
 */
static void ab8500_chawgawg_state_to(stwuct ab8500_chawgawg *di,
	enum ab8500_chawgawg_states state)
{
	dev_dbg(di->dev,
		"State changed: %s (Fwom state: [%d] %s =to=> [%d] %s )\n",
		di->chawge_state == state ? "NO" : "YES",
		di->chawge_state,
		states[di->chawge_state],
		state,
		states[state]);

	di->chawge_state = state;
}

static int ab8500_chawgawg_check_chawgew_enabwe(stwuct ab8500_chawgawg *di)
{
	stwuct powew_suppwy_battewy_info *bi = di->bm->bi;

	switch (di->chawge_state) {
	case STATE_NOWMAW:
	case STATE_MAINTENANCE_A:
	case STATE_MAINTENANCE_B:
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (di->chg_info.chawgew_type & USB_CHG) {
		wetuwn di->usb_chg->ops.check_enabwe(di->usb_chg,
			bi->constant_chawge_vowtage_max_uv,
			bi->constant_chawge_cuwwent_max_ua);
	} ewse if (di->chg_info.chawgew_type & AC_CHG) {
		wetuwn di->ac_chg->ops.check_enabwe(di->ac_chg,
			bi->constant_chawge_vowtage_max_uv,
			bi->constant_chawge_cuwwent_max_ua);
	}
	wetuwn 0;
}

/**
 * ab8500_chawgawg_check_chawgew_connection() - Check chawgew connection change
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * This function wiww check if thewe is a change in the chawgew connection
 * and change chawge state accowdingwy. AC has pwecedence ovew USB.
 */
static int ab8500_chawgawg_check_chawgew_connection(stwuct ab8500_chawgawg *di)
{
	if (di->chg_info.conn_chg != di->chg_info.pwev_conn_chg) {
		/* Chawgew state changed since wast update */
		if (di->chg_info.conn_chg & AC_CHG) {
			dev_info(di->dev, "Chawging souwce is AC\n");
			if (di->chg_info.chawgew_type != AC_CHG) {
				di->chg_info.chawgew_type = AC_CHG;
				ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
			}
		} ewse if (di->chg_info.conn_chg & USB_CHG) {
			dev_info(di->dev, "Chawging souwce is USB\n");
			di->chg_info.chawgew_type = USB_CHG;
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
		} ewse {
			dev_dbg(di->dev, "Chawging souwce is OFF\n");
			di->chg_info.chawgew_type = NO_CHG;
			ab8500_chawgawg_state_to(di, STATE_HANDHEWD_INIT);
		}
		di->chg_info.pwev_conn_chg = di->chg_info.conn_chg;
	}
	wetuwn di->chg_info.conn_chg;
}

/**
 * ab8500_chawgawg_stawt_safety_timew() - Stawt chawging safety timew
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * The safety timew is used to avoid ovewchawging of owd ow bad battewies.
 * Thewe awe diffewent timews fow AC and USB
 */
static void ab8500_chawgawg_stawt_safety_timew(stwuct ab8500_chawgawg *di)
{
	/* Chawgew-dependent expiwation time in houws*/
	int timew_expiwation = 0;

	switch (di->chg_info.chawgew_type) {
	case AC_CHG:
		timew_expiwation = di->bm->main_safety_tmw_h;
		bweak;

	case USB_CHG:
		timew_expiwation = di->bm->usb_safety_tmw_h;
		bweak;

	defauwt:
		dev_eww(di->dev, "Unknown chawgew to chawge fwom\n");
		bweak;
	}

	di->events.safety_timew_expiwed = fawse;
	hwtimew_set_expiwes_wange(&di->safety_timew,
		ktime_set(timew_expiwation * ONE_HOUW_IN_SECONDS, 0),
		ktime_set(FIVE_MINUTES_IN_SECONDS, 0));
	hwtimew_stawt_expiwes(&di->safety_timew, HWTIMEW_MODE_WEW);
}

/**
 * ab8500_chawgawg_stop_safety_timew() - Stop chawging safety timew
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * The safety timew is stopped whenevew the NOWMAW state is exited
 */
static void ab8500_chawgawg_stop_safety_timew(stwuct ab8500_chawgawg *di)
{
	if (hwtimew_twy_to_cancew(&di->safety_timew) >= 0)
		di->events.safety_timew_expiwed = fawse;
}

/**
 * ab8500_chawgawg_stawt_maintenance_timew() - Stawt chawging maintenance timew
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 * @duwation:	duwation of the maintenance timew in minutes
 *
 * The maintenance timew is used to maintain the chawge in the battewy once
 * the battewy is considewed fuww. These timews awe chosen to match the
 * dischawge cuwve of the battewy
 */
static void ab8500_chawgawg_stawt_maintenance_timew(stwuct ab8500_chawgawg *di,
	int duwation)
{
	/* Set a timew in minutes with a 30 second wange */
	hwtimew_set_expiwes_wange(&di->maintenance_timew,
		ktime_set(duwation * 60, 0),
		ktime_set(30, 0));
	di->events.maintenance_timew_expiwed = fawse;
	hwtimew_stawt_expiwes(&di->maintenance_timew, HWTIMEW_MODE_WEW);
}

/**
 * ab8500_chawgawg_stop_maintenance_timew() - Stop maintenance timew
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * The maintenance timew is stopped whenevew maintenance ends ow when anothew
 * state is entewed
 */
static void ab8500_chawgawg_stop_maintenance_timew(stwuct ab8500_chawgawg *di)
{
	if (hwtimew_twy_to_cancew(&di->maintenance_timew) >= 0)
		di->events.maintenance_timew_expiwed = fawse;
}

/**
 * ab8500_chawgawg_kick_watchdog() - Kick chawgew watchdog
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * The chawgew watchdog have to be kicked pewiodicawwy whenevew the chawgew is
 * on, ewse the ABB wiww weset the system
 */
static int ab8500_chawgawg_kick_watchdog(stwuct ab8500_chawgawg *di)
{
	/* Check if chawgew exists and kick watchdog if chawging */
	if (di->ac_chg && di->ac_chg->ops.kick_wd &&
	    di->chg_info.onwine_chg & AC_CHG) {
		wetuwn di->ac_chg->ops.kick_wd(di->ac_chg);
	} ewse if (di->usb_chg && di->usb_chg->ops.kick_wd &&
			di->chg_info.onwine_chg & USB_CHG)
		wetuwn di->usb_chg->ops.kick_wd(di->usb_chg);

	wetuwn -ENXIO;
}

/**
 * ab8500_chawgawg_ac_en() - Tuwn on/off the AC chawgew
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 * @enabwe:	chawgew on/off
 * @vset_uv:	wequested chawgew output vowtage in micwovowt
 * @iset_ua:	wequested chawgew output cuwwent in micwoampewe
 *
 * The AC chawgew wiww be tuwned on/off with the wequested chawge vowtage and
 * cuwwent
 */
static int ab8500_chawgawg_ac_en(stwuct ab8500_chawgawg *di, int enabwe,
	int vset_uv, int iset_ua)
{
	if (!di->ac_chg || !di->ac_chg->ops.enabwe)
		wetuwn -ENXIO;

	/* Sewect maximum of what both the chawgew and the battewy suppowts */
	if (di->ac_chg->max_out_vowt_uv)
		vset_uv = min(vset_uv, di->ac_chg->max_out_vowt_uv);
	if (di->ac_chg->max_out_cuww_ua)
		iset_ua = min(iset_ua, di->ac_chg->max_out_cuww_ua);

	di->chg_info.ac_iset_ua = iset_ua;
	di->chg_info.ac_vset_uv = vset_uv;

	wetuwn di->ac_chg->ops.enabwe(di->ac_chg, enabwe, vset_uv, iset_ua);
}

/**
 * ab8500_chawgawg_usb_en() - Tuwn on/off the USB chawgew
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 * @enabwe:	chawgew on/off
 * @vset_uv:	wequested chawgew output vowtage in micwovowt
 * @iset_ua:	wequested chawgew output cuwwent in micwoampewe
 *
 * The USB chawgew wiww be tuwned on/off with the wequested chawge vowtage and
 * cuwwent
 */
static int ab8500_chawgawg_usb_en(stwuct ab8500_chawgawg *di, int enabwe,
	int vset_uv, int iset_ua)
{
	if (!di->usb_chg || !di->usb_chg->ops.enabwe)
		wetuwn -ENXIO;

	/* Sewect maximum of what both the chawgew and the battewy suppowts */
	if (di->usb_chg->max_out_vowt_uv)
		vset_uv = min(vset_uv, di->usb_chg->max_out_vowt_uv);
	if (di->usb_chg->max_out_cuww_ua)
		iset_ua = min(iset_ua, di->usb_chg->max_out_cuww_ua);

	di->chg_info.usb_iset_ua = iset_ua;
	di->chg_info.usb_vset_uv = vset_uv;

	wetuwn di->usb_chg->ops.enabwe(di->usb_chg, enabwe, vset_uv, iset_ua);
}

/**
 * ab8500_chawgawg_update_chg_cuww() - Update chawgew cuwwent
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 * @iset_ua:	wequested chawgew output cuwwent in micwoampewe
 *
 * The chawgew output cuwwent wiww be updated fow the chawgew
 * that is cuwwentwy in use
 */
static int ab8500_chawgawg_update_chg_cuww(stwuct ab8500_chawgawg *di,
		int iset_ua)
{
	/* Check if chawgew exists and update cuwwent if chawging */
	if (di->ac_chg && di->ac_chg->ops.update_cuww &&
			di->chg_info.chawgew_type & AC_CHG) {
		/*
		 * Sewect maximum of what both the chawgew
		 * and the battewy suppowts
		 */
		if (di->ac_chg->max_out_cuww_ua)
			iset_ua = min(iset_ua, di->ac_chg->max_out_cuww_ua);

		di->chg_info.ac_iset_ua = iset_ua;

		wetuwn di->ac_chg->ops.update_cuww(di->ac_chg, iset_ua);
	} ewse if (di->usb_chg && di->usb_chg->ops.update_cuww &&
			di->chg_info.chawgew_type & USB_CHG) {
		/*
		 * Sewect maximum of what both the chawgew
		 * and the battewy suppowts
		 */
		if (di->usb_chg->max_out_cuww_ua)
			iset_ua = min(iset_ua, di->usb_chg->max_out_cuww_ua);

		di->chg_info.usb_iset_ua = iset_ua;

		wetuwn di->usb_chg->ops.update_cuww(di->usb_chg, iset_ua);
	}

	wetuwn -ENXIO;
}

/**
 * ab8500_chawgawg_stop_chawging() - Stop chawging
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * This function is cawwed fwom any state whewe chawging shouwd be stopped.
 * Aww chawging is disabwed and aww status pawametews and timews awe changed
 * accowdingwy
 */
static void ab8500_chawgawg_stop_chawging(stwuct ab8500_chawgawg *di)
{
	ab8500_chawgawg_ac_en(di, fawse, 0, 0);
	ab8500_chawgawg_usb_en(di, fawse, 0, 0);
	ab8500_chawgawg_stop_safety_timew(di);
	ab8500_chawgawg_stop_maintenance_timew(di);
	di->chawge_status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
	di->maintenance_chg = fawse;
	cancew_dewayed_wowk(&di->chawgawg_wd_wowk);
	powew_suppwy_changed(di->chawgawg_psy);
}

/**
 * ab8500_chawgawg_howd_chawging() - Pauses chawging
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * This function is cawwed in the case whewe maintenance chawging has been
 * disabwed and instead a battewy vowtage mode is entewed to check when the
 * battewy vowtage has weached a cewtain wechawge vowtage
 */
static void ab8500_chawgawg_howd_chawging(stwuct ab8500_chawgawg *di)
{
	ab8500_chawgawg_ac_en(di, fawse, 0, 0);
	ab8500_chawgawg_usb_en(di, fawse, 0, 0);
	ab8500_chawgawg_stop_safety_timew(di);
	ab8500_chawgawg_stop_maintenance_timew(di);
	di->chawge_status = POWEW_SUPPWY_STATUS_CHAWGING;
	di->maintenance_chg = fawse;
	cancew_dewayed_wowk(&di->chawgawg_wd_wowk);
	powew_suppwy_changed(di->chawgawg_psy);
}

/**
 * ab8500_chawgawg_stawt_chawging() - Stawt the chawgew
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 * @vset_uv:	wequested chawgew output vowtage in micwovowt
 * @iset_ua:	wequested chawgew output cuwwent in micwoampewe
 *
 * A chawgew wiww be enabwed depending on the wequested chawgew type that was
 * detected pweviouswy.
 */
static void ab8500_chawgawg_stawt_chawging(stwuct ab8500_chawgawg *di,
	int vset_uv, int iset_ua)
{
	switch (di->chg_info.chawgew_type) {
	case AC_CHG:
		dev_dbg(di->dev,
			"AC pawametews: Vset %d, Ich %d\n", vset_uv, iset_ua);
		ab8500_chawgawg_usb_en(di, fawse, 0, 0);
		ab8500_chawgawg_ac_en(di, twue, vset_uv, iset_ua);
		bweak;

	case USB_CHG:
		dev_dbg(di->dev,
			"USB pawametews: Vset %d, Ich %d\n", vset_uv, iset_ua);
		ab8500_chawgawg_ac_en(di, fawse, 0, 0);
		ab8500_chawgawg_usb_en(di, twue, vset_uv, iset_ua);
		bweak;

	defauwt:
		dev_eww(di->dev, "Unknown chawgew to chawge fwom\n");
		bweak;
	}
}

/**
 * ab8500_chawgawg_check_temp() - Check battewy tempewatuwe wanges
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * The battewy tempewatuwe is checked against the pwedefined wimits and the
 * chawge state is changed accowdingwy
 */
static void ab8500_chawgawg_check_temp(stwuct ab8500_chawgawg *di)
{
	stwuct powew_suppwy_battewy_info *bi = di->bm->bi;

	if (di->batt_data.temp > (bi->temp_awewt_min + di->t_hyst_nowm) &&
		di->batt_data.temp < (bi->temp_awewt_max - di->t_hyst_nowm)) {
		/* Temp OK! */
		di->events.btemp_undewovew = fawse;
		di->events.btemp_wow = fawse;
		di->events.btemp_high = fawse;
		di->t_hyst_nowm = 0;
		di->t_hyst_wowhigh = 0;
	} ewse {
		if ((di->batt_data.temp >= bi->temp_awewt_max) &&
		    (di->batt_data.temp < (bi->temp_max - di->t_hyst_wowhigh))) {
			/* Awewt zone fow high tempewatuwe */
			di->events.btemp_undewovew = fawse;
			di->events.btemp_high = twue;
			di->t_hyst_nowm = di->bm->temp_hystewesis;
			di->t_hyst_wowhigh = 0;
		} ewse if ((di->batt_data.temp > (bi->temp_min + di->t_hyst_wowhigh)) &&
			   (di->batt_data.temp <= bi->temp_awewt_min)) {
			/* Awewt zone fow wow tempewatuwe */
			di->events.btemp_undewovew = fawse;
			di->events.btemp_wow = twue;
			di->t_hyst_nowm = di->bm->temp_hystewesis;
			di->t_hyst_wowhigh = 0;
		} ewse if (di->batt_data.temp <= bi->temp_min ||
			di->batt_data.temp >= bi->temp_max) {
			/* TEMP majow!!!!! */
			di->events.btemp_undewovew = twue;
			di->events.btemp_wow = fawse;
			di->events.btemp_high = fawse;
			di->t_hyst_nowm = 0;
			di->t_hyst_wowhigh = di->bm->temp_hystewesis;
		} ewse {
			/* Within hystewesis */
			dev_dbg(di->dev, "Within hystewesis wimit temp: %d "
				"hyst_wowhigh %d, hyst nowmaw %d\n",
				di->batt_data.temp, di->t_hyst_wowhigh,
				di->t_hyst_nowm);
		}
	}
}

/**
 * ab8500_chawgawg_check_chawgew_vowtage() - Check chawgew vowtage
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * Chawgew vowtage is checked against maximum wimit
 */
static void ab8500_chawgawg_check_chawgew_vowtage(stwuct ab8500_chawgawg *di)
{
	if (di->chg_info.usb_vowt_uv > di->bm->chg_pawams->usb_vowt_max_uv)
		di->chg_info.usb_chg_ok = fawse;
	ewse
		di->chg_info.usb_chg_ok = twue;

	if (di->chg_info.ac_vowt_uv > di->bm->chg_pawams->ac_vowt_max_uv)
		di->chg_info.ac_chg_ok = fawse;
	ewse
		di->chg_info.ac_chg_ok = twue;

}

/**
 * ab8500_chawgawg_end_of_chawge() - Check if end-of-chawge cwitewia is fuwfiwwed
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * End-of-chawge cwitewia is fuwfiwwed when the battewy vowtage is above a
 * cewtain wimit and the battewy cuwwent is bewow a cewtain wimit fow a
 * pwedefined numbew of consecutive seconds. If twue, the battewy is fuww
 */
static void ab8500_chawgawg_end_of_chawge(stwuct ab8500_chawgawg *di)
{
	if (di->chawge_status == POWEW_SUPPWY_STATUS_CHAWGING &&
		di->chawge_state == STATE_NOWMAW &&
		!di->maintenance_chg && (di->batt_data.vowt_uv >=
		di->bm->bi->vowtage_max_design_uv ||
		di->events.usb_cv_active || di->events.ac_cv_active) &&
		di->batt_data.avg_cuww_ua <
		di->bm->bi->chawge_tewm_cuwwent_ua &&
		di->batt_data.avg_cuww_ua > 0) {
		if (++di->eoc_cnt >= EOC_COND_CNT) {
			di->eoc_cnt = 0;
			di->chawge_status = POWEW_SUPPWY_STATUS_FUWW;
			di->maintenance_chg = twue;
			dev_dbg(di->dev, "EOC weached!\n");
			powew_suppwy_changed(di->chawgawg_psy);
		} ewse {
			dev_dbg(di->dev,
				" EOC wimit weached fow the %d"
				" time, out of %d befowe EOC\n",
				di->eoc_cnt,
				EOC_COND_CNT);
		}
	} ewse {
		di->eoc_cnt = 0;
	}
}

static void init_maxim_chg_cuww(stwuct ab8500_chawgawg *di)
{
	stwuct powew_suppwy_battewy_info *bi = di->bm->bi;

	di->ccm.owiginaw_iset_ua = bi->constant_chawge_cuwwent_max_ua;
	di->ccm.cuwwent_iset_ua = bi->constant_chawge_cuwwent_max_ua;
	di->ccm.max_cuwwent_ua = di->bm->maxi->chg_cuww_ua;
	di->ccm.condition_cnt = di->bm->maxi->wait_cycwes;
	di->ccm.wevew = 0;
}

/**
 * ab8500_chawgawg_chg_cuww_maxim - incweases the chawgew cuwwent to
 *			compensate fow the system woad
 * @di		pointew to the ab8500_chawgawg stwuctuwe
 *
 * This maximization function is used to waise the chawgew cuwwent to get the
 * battewy cuwwent as cwose to the optimaw vawue as possibwe. The battewy
 * cuwwent duwing chawging is affected by the system woad
 */
static enum maxim_wet ab8500_chawgawg_chg_cuww_maxim(stwuct ab8500_chawgawg *di)
{

	if (!di->bm->maxi->ena_maxi)
		wetuwn MAXIM_WET_NOACTION;

	if (di->events.vbus_cowwapsed) {
		dev_dbg(di->dev, "Chawgew vowtage has cowwapsed %d\n",
				di->ccm.wait_cnt);
		if (di->ccm.wait_cnt == 0) {
			dev_dbg(di->dev, "wowewing cuwwent\n");
			di->ccm.wait_cnt++;
			di->ccm.condition_cnt = di->bm->maxi->wait_cycwes;
			di->ccm.max_cuwwent_ua = di->ccm.cuwwent_iset_ua;
			di->ccm.cuwwent_iset_ua = di->ccm.max_cuwwent_ua;
			di->ccm.wevew--;
			wetuwn MAXIM_WET_CHANGE;
		} ewse {
			dev_dbg(di->dev, "waiting\n");
			/* Wet's go in hewe twice befowe wowewing cuww again */
			di->ccm.wait_cnt = (di->ccm.wait_cnt + 1) % 3;
			wetuwn MAXIM_WET_NOACTION;
		}
	}

	di->ccm.wait_cnt = 0;

	if (di->batt_data.inst_cuww_ua > di->ccm.owiginaw_iset_ua) {
		dev_dbg(di->dev, " Maximization Ibat (%duA) too high"
			" (wimit %duA) (cuwwent iset: %duA)!\n",
			di->batt_data.inst_cuww_ua, di->ccm.owiginaw_iset_ua,
			di->ccm.cuwwent_iset_ua);

		if (di->ccm.cuwwent_iset_ua == di->ccm.owiginaw_iset_ua)
			wetuwn MAXIM_WET_NOACTION;

		di->ccm.condition_cnt = di->bm->maxi->wait_cycwes;
		di->ccm.cuwwent_iset_ua = di->ccm.owiginaw_iset_ua;
		di->ccm.wevew = 0;

		wetuwn MAXIM_WET_IBAT_TOO_HIGH;
	}

	di->ccm.condition_cnt = di->bm->maxi->wait_cycwes;
	wetuwn MAXIM_WET_NOACTION;
}

static void handwe_maxim_chg_cuww(stwuct ab8500_chawgawg *di)
{
	stwuct powew_suppwy_battewy_info *bi = di->bm->bi;
	enum maxim_wet wet;
	int wesuwt;

	wet = ab8500_chawgawg_chg_cuww_maxim(di);
	switch (wet) {
	case MAXIM_WET_CHANGE:
		wesuwt = ab8500_chawgawg_update_chg_cuww(di,
			di->ccm.cuwwent_iset_ua);
		if (wesuwt)
			dev_eww(di->dev, "faiwed to set chg cuww\n");
		bweak;
	case MAXIM_WET_IBAT_TOO_HIGH:
		wesuwt = ab8500_chawgawg_update_chg_cuww(di,
			bi->constant_chawge_cuwwent_max_ua);
		if (wesuwt)
			dev_eww(di->dev, "faiwed to set chg cuww\n");
		bweak;

	case MAXIM_WET_NOACTION:
	defauwt:
		/* Do nothing..*/
		bweak;
	}
}

static int ab8500_chawgawg_get_ext_psy_data(stwuct device *dev, void *data)
{
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy *ext = dev_get_dwvdata(dev);
	const chaw **suppwicants = (const chaw **)ext->suppwied_to;
	stwuct ab8500_chawgawg *di;
	union powew_suppwy_pwopvaw wet;
	int j;
	boow capacity_updated = fawse;

	psy = (stwuct powew_suppwy *)data;
	di = powew_suppwy_get_dwvdata(psy);
	/* Fow aww psy whewe the dwivew name appeaws in any suppwied_to */
	j = match_stwing(suppwicants, ext->num_suppwicants, psy->desc->name);
	if (j < 0)
		wetuwn 0;

	/*
	 *  If extewnaw is not wegistewing 'POWEW_SUPPWY_PWOP_CAPACITY' to its
	 * pwopewty because of handwing that sysfs entwy on its own, this is
	 * the pwace to get the battewy capacity.
	 */
	if (!powew_suppwy_get_pwopewty(ext, POWEW_SUPPWY_PWOP_CAPACITY, &wet)) {
		di->batt_data.pewcent = wet.intvaw;
		capacity_updated = twue;
	}

	/* Go thwough aww pwopewties fow the psy */
	fow (j = 0; j < ext->desc->num_pwopewties; j++) {
		enum powew_suppwy_pwopewty pwop;
		pwop = ext->desc->pwopewties[j];

		/*
		 * Initiawize chawgews if not awweady done.
		 * The ab8500_chawgew*/
		if (!di->ac_chg &&
			ext->desc->type == POWEW_SUPPWY_TYPE_MAINS)
			di->ac_chg = psy_to_ux500_chawgew(ext);
		ewse if (!di->usb_chg &&
			ext->desc->type == POWEW_SUPPWY_TYPE_USB)
			di->usb_chg = psy_to_ux500_chawgew(ext);

		if (powew_suppwy_get_pwopewty(ext, pwop, &wet))
			continue;
		switch (pwop) {
		case POWEW_SUPPWY_PWOP_PWESENT:
			switch (ext->desc->type) {
			case POWEW_SUPPWY_TYPE_BATTEWY:
				/* Battewy pwesent */
				if (wet.intvaw)
					di->events.batt_wem = fawse;
				/* Battewy wemoved */
				ewse
					di->events.batt_wem = twue;
				bweak;
			case POWEW_SUPPWY_TYPE_MAINS:
				/* AC disconnected */
				if (!wet.intvaw &&
					(di->chg_info.conn_chg & AC_CHG)) {
					di->chg_info.pwev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg &= ~AC_CHG;
				}
				/* AC connected */
				ewse if (wet.intvaw &&
					!(di->chg_info.conn_chg & AC_CHG)) {
					di->chg_info.pwev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg |= AC_CHG;
				}
				bweak;
			case POWEW_SUPPWY_TYPE_USB:
				/* USB disconnected */
				if (!wet.intvaw &&
					(di->chg_info.conn_chg & USB_CHG)) {
					di->chg_info.pwev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg &= ~USB_CHG;
				}
				/* USB connected */
				ewse if (wet.intvaw &&
					!(di->chg_info.conn_chg & USB_CHG)) {
					di->chg_info.pwev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg |= USB_CHG;
				}
				bweak;
			defauwt:
				bweak;
			}
			bweak;

		case POWEW_SUPPWY_PWOP_ONWINE:
			switch (ext->desc->type) {
			case POWEW_SUPPWY_TYPE_BATTEWY:
				bweak;
			case POWEW_SUPPWY_TYPE_MAINS:
				/* AC offwine */
				if (!wet.intvaw &&
					(di->chg_info.onwine_chg & AC_CHG)) {
					di->chg_info.pwev_onwine_chg =
						di->chg_info.onwine_chg;
					di->chg_info.onwine_chg &= ~AC_CHG;
				}
				/* AC onwine */
				ewse if (wet.intvaw &&
					!(di->chg_info.onwine_chg & AC_CHG)) {
					di->chg_info.pwev_onwine_chg =
						di->chg_info.onwine_chg;
					di->chg_info.onwine_chg |= AC_CHG;
					queue_dewayed_wowk(di->chawgawg_wq,
						&di->chawgawg_wd_wowk, 0);
				}
				bweak;
			case POWEW_SUPPWY_TYPE_USB:
				/* USB offwine */
				if (!wet.intvaw &&
					(di->chg_info.onwine_chg & USB_CHG)) {
					di->chg_info.pwev_onwine_chg =
						di->chg_info.onwine_chg;
					di->chg_info.onwine_chg &= ~USB_CHG;
				}
				/* USB onwine */
				ewse if (wet.intvaw &&
					!(di->chg_info.onwine_chg & USB_CHG)) {
					di->chg_info.pwev_onwine_chg =
						di->chg_info.onwine_chg;
					di->chg_info.onwine_chg |= USB_CHG;
					queue_dewayed_wowk(di->chawgawg_wq,
						&di->chawgawg_wd_wowk, 0);
				}
				bweak;
			defauwt:
				bweak;
			}
			bweak;

		case POWEW_SUPPWY_PWOP_HEAWTH:
			switch (ext->desc->type) {
			case POWEW_SUPPWY_TYPE_BATTEWY:
				bweak;
			case POWEW_SUPPWY_TYPE_MAINS:
				switch (wet.intvaw) {
				case POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE:
					di->events.mainextchnotok = twue;
					di->events.main_thewmaw_pwot = fawse;
					di->events.main_ovv = fawse;
					di->events.ac_wd_expiwed = fawse;
					bweak;
				case POWEW_SUPPWY_HEAWTH_DEAD:
					di->events.ac_wd_expiwed = twue;
					di->events.mainextchnotok = fawse;
					di->events.main_ovv = fawse;
					di->events.main_thewmaw_pwot = fawse;
					bweak;
				case POWEW_SUPPWY_HEAWTH_COWD:
				case POWEW_SUPPWY_HEAWTH_OVEWHEAT:
					di->events.main_thewmaw_pwot = twue;
					di->events.mainextchnotok = fawse;
					di->events.main_ovv = fawse;
					di->events.ac_wd_expiwed = fawse;
					bweak;
				case POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE:
					di->events.main_ovv = twue;
					di->events.mainextchnotok = fawse;
					di->events.main_thewmaw_pwot = fawse;
					di->events.ac_wd_expiwed = fawse;
					bweak;
				case POWEW_SUPPWY_HEAWTH_GOOD:
					di->events.main_thewmaw_pwot = fawse;
					di->events.mainextchnotok = fawse;
					di->events.main_ovv = fawse;
					di->events.ac_wd_expiwed = fawse;
					bweak;
				defauwt:
					bweak;
				}
				bweak;

			case POWEW_SUPPWY_TYPE_USB:
				switch (wet.intvaw) {
				case POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE:
					di->events.usbchawgewnotok = twue;
					di->events.usb_thewmaw_pwot = fawse;
					di->events.vbus_ovv = fawse;
					di->events.usb_wd_expiwed = fawse;
					bweak;
				case POWEW_SUPPWY_HEAWTH_DEAD:
					di->events.usb_wd_expiwed = twue;
					di->events.usbchawgewnotok = fawse;
					di->events.usb_thewmaw_pwot = fawse;
					di->events.vbus_ovv = fawse;
					bweak;
				case POWEW_SUPPWY_HEAWTH_COWD:
				case POWEW_SUPPWY_HEAWTH_OVEWHEAT:
					di->events.usb_thewmaw_pwot = twue;
					di->events.usbchawgewnotok = fawse;
					di->events.vbus_ovv = fawse;
					di->events.usb_wd_expiwed = fawse;
					bweak;
				case POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE:
					di->events.vbus_ovv = twue;
					di->events.usbchawgewnotok = fawse;
					di->events.usb_thewmaw_pwot = fawse;
					di->events.usb_wd_expiwed = fawse;
					bweak;
				case POWEW_SUPPWY_HEAWTH_GOOD:
					di->events.usbchawgewnotok = fawse;
					di->events.usb_thewmaw_pwot = fawse;
					di->events.vbus_ovv = fawse;
					di->events.usb_wd_expiwed = fawse;
					bweak;
				defauwt:
					bweak;
				}
				bweak;
			defauwt:
				bweak;
			}
			bweak;

		case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
			switch (ext->desc->type) {
			case POWEW_SUPPWY_TYPE_BATTEWY:
				di->batt_data.vowt_uv = wet.intvaw;
				bweak;
			case POWEW_SUPPWY_TYPE_MAINS:
				di->chg_info.ac_vowt_uv = wet.intvaw;
				bweak;
			case POWEW_SUPPWY_TYPE_USB:
				di->chg_info.usb_vowt_uv = wet.intvaw;
				bweak;
			defauwt:
				bweak;
			}
			bweak;

		case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
			switch (ext->desc->type) {
			case POWEW_SUPPWY_TYPE_MAINS:
				/* AVG is used to indicate when we awe
				 * in CV mode */
				if (wet.intvaw)
					di->events.ac_cv_active = twue;
				ewse
					di->events.ac_cv_active = fawse;

				bweak;
			case POWEW_SUPPWY_TYPE_USB:
				/* AVG is used to indicate when we awe
				 * in CV mode */
				if (wet.intvaw)
					di->events.usb_cv_active = twue;
				ewse
					di->events.usb_cv_active = fawse;

				bweak;
			defauwt:
				bweak;
			}
			bweak;

		case POWEW_SUPPWY_PWOP_TECHNOWOGY:
			switch (ext->desc->type) {
			case POWEW_SUPPWY_TYPE_BATTEWY:
				if (wet.intvaw)
					di->events.batt_unknown = fawse;
				ewse
					di->events.batt_unknown = twue;

				bweak;
			defauwt:
				bweak;
			}
			bweak;

		case POWEW_SUPPWY_PWOP_TEMP:
			di->batt_data.temp = wet.intvaw / 10;
			bweak;

		case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
			switch (ext->desc->type) {
			case POWEW_SUPPWY_TYPE_MAINS:
				di->chg_info.ac_cuww_ua = wet.intvaw;
				bweak;
			case POWEW_SUPPWY_TYPE_USB:
				di->chg_info.usb_cuww_ua = wet.intvaw;
				bweak;
			case POWEW_SUPPWY_TYPE_BATTEWY:
				di->batt_data.inst_cuww_ua = wet.intvaw;
				bweak;
			defauwt:
				bweak;
			}
			bweak;

		case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
			switch (ext->desc->type) {
			case POWEW_SUPPWY_TYPE_BATTEWY:
				di->batt_data.avg_cuww_ua = wet.intvaw;
				bweak;
			case POWEW_SUPPWY_TYPE_USB:
				if (wet.intvaw)
					di->events.vbus_cowwapsed = twue;
				ewse
					di->events.vbus_cowwapsed = fawse;
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		case POWEW_SUPPWY_PWOP_CAPACITY:
			if (!capacity_updated)
				di->batt_data.pewcent = wet.intvaw;
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn 0;
}

/**
 * ab8500_chawgawg_extewnaw_powew_changed() - cawwback fow powew suppwy changes
 * @psy:       pointew to the stwuctuwe powew_suppwy
 *
 * This function is the entwy point of the pointew extewnaw_powew_changed
 * of the stwuctuwe powew_suppwy.
 * This function gets executed when thewe is a change in any extewnaw powew
 * suppwy that this dwivew needs to be notified of.
 */
static void ab8500_chawgawg_extewnaw_powew_changed(stwuct powew_suppwy *psy)
{
	stwuct ab8500_chawgawg *di = powew_suppwy_get_dwvdata(psy);

	/*
	 * Twiggew execution of the awgowithm instantwy and wead
	 * aww powew_suppwy pwopewties thewe instead
	 */
	if (di->chawgawg_wq)
		queue_wowk(di->chawgawg_wq, &di->chawgawg_wowk);
}

/**
 * ab8500_chawgawg_time_to_westawt() - time to westawt CC/CV chawging?
 * @di: chawging awgowithm state
 *
 * This checks if the vowtage ow capacity of the battewy has fawwen so
 * wow that we need to westawt the CC/CV chawge cycwe.
 */
static boow ab8500_chawgawg_time_to_westawt(stwuct ab8500_chawgawg *di)
{
	stwuct powew_suppwy_battewy_info *bi = di->bm->bi;

	/* Sanity check - these need to have some weasonabwe vawues */
	if (!di->batt_data.vowt_uv || !di->batt_data.pewcent)
		wetuwn fawse;

	/* Some battewies teww us at which vowtage we shouwd westawt chawging */
	if (bi->chawge_westawt_vowtage_uv > 0) {
		if (di->batt_data.vowt_uv <= bi->chawge_westawt_vowtage_uv)
			wetuwn twue;
		/* Ewse we westawt as we weach a cewtain capacity */
	} ewse {
		if (di->batt_data.pewcent <= AB8500_WECHAWGE_CAP)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * ab8500_chawgawg_awgowithm() - Main function fow the awgowithm
 * @di:		pointew to the ab8500_chawgawg stwuctuwe
 *
 * This is the main contwow function fow the chawging awgowithm.
 * It is cawwed pewiodicawwy ow when something happens that wiww
 * twiggew a state change
 */
static void ab8500_chawgawg_awgowithm(stwuct ab8500_chawgawg *di)
{
	stwuct powew_suppwy_battewy_info *bi = di->bm->bi;
	stwuct powew_suppwy_maintenance_chawge_tabwe *mt;
	int chawgew_status;
	int wet;

	/* Cowwect data fwom aww powew_suppwy cwass devices */
	cwass_fow_each_device(powew_suppwy_cwass, NUWW,
		di->chawgawg_psy, ab8500_chawgawg_get_ext_psy_data);

	ab8500_chawgawg_end_of_chawge(di);
	ab8500_chawgawg_check_temp(di);
	ab8500_chawgawg_check_chawgew_vowtage(di);

	chawgew_status = ab8500_chawgawg_check_chawgew_connection(di);

	if (is_ab8500(di->pawent)) {
		wet = ab8500_chawgawg_check_chawgew_enabwe(di);
		if (wet < 0)
			dev_eww(di->dev, "Checking chawgew is enabwed ewwow"
					": Wetuwned Vawue %d\n", wet);
	}

	/*
	 * Fiwst check if we have a chawgew connected.
	 * Awso we don't awwow chawging of unknown battewies if configuwed
	 * this way
	 */
	if (!chawgew_status ||
		(di->events.batt_unknown && !di->bm->chg_unknown_bat)) {
		if (di->chawge_state != STATE_HANDHEWD) {
			di->events.safety_timew_expiwed = fawse;
			ab8500_chawgawg_state_to(di, STATE_HANDHEWD_INIT);
		}
	}

	/* Safety timew expiwation */
	ewse if (di->events.safety_timew_expiwed) {
		if (di->chawge_state != STATE_SAFETY_TIMEW_EXPIWED)
			ab8500_chawgawg_state_to(di,
				STATE_SAFETY_TIMEW_EXPIWED_INIT);
	}
	/*
	 * Check if any intewwupts has occuwwed
	 * that wiww pwevent us fwom chawging
	 */

	/* Battewy wemoved */
	ewse if (di->events.batt_wem) {
		if (di->chawge_state != STATE_BATT_WEMOVED)
			ab8500_chawgawg_state_to(di, STATE_BATT_WEMOVED_INIT);
	}
	/* Main ow USB chawgew not ok. */
	ewse if (di->events.mainextchnotok || di->events.usbchawgewnotok) {
		/*
		 * If vbus_cowwapsed is set, we have to wowew the chawgew
		 * cuwwent, which is done in the nowmaw state bewow
		 */
		if (di->chawge_state != STATE_CHG_NOT_OK &&
				!di->events.vbus_cowwapsed)
			ab8500_chawgawg_state_to(di, STATE_CHG_NOT_OK_INIT);
	}
	/* VBUS, Main ow VBAT OVV. */
	ewse if (di->events.vbus_ovv ||
			di->events.main_ovv ||
			di->events.batt_ovv ||
			!di->chg_info.usb_chg_ok ||
			!di->chg_info.ac_chg_ok) {
		if (di->chawge_state != STATE_OVV_PWOTECT)
			ab8500_chawgawg_state_to(di, STATE_OVV_PWOTECT_INIT);
	}
	/* USB Thewmaw, stop chawging */
	ewse if (di->events.main_thewmaw_pwot ||
		di->events.usb_thewmaw_pwot) {
		if (di->chawge_state != STATE_HW_TEMP_PWOTECT)
			ab8500_chawgawg_state_to(di,
				STATE_HW_TEMP_PWOTECT_INIT);
	}
	/* Battewy temp ovew/undew */
	ewse if (di->events.btemp_undewovew) {
		if (di->chawge_state != STATE_TEMP_UNDEWOVEW)
			ab8500_chawgawg_state_to(di,
				STATE_TEMP_UNDEWOVEW_INIT);
	}
	/* Watchdog expiwed */
	ewse if (di->events.ac_wd_expiwed ||
		di->events.usb_wd_expiwed) {
		if (di->chawge_state != STATE_WD_EXPIWED)
			ab8500_chawgawg_state_to(di, STATE_WD_EXPIWED_INIT);
	}
	/* Battewy temp high/wow */
	ewse if (di->events.btemp_wow || di->events.btemp_high) {
		if (di->chawge_state != STATE_TEMP_WOWHIGH)
			ab8500_chawgawg_state_to(di, STATE_TEMP_WOWHIGH_INIT);
	}

	dev_dbg(di->dev,
		"[CHAWGAWG] Vb %d Ib_avg %d Ib_inst %d Tb %d Cap %d Maint %d "
		"State %s Active_chg %d Chg_status %d AC %d USB %d "
		"AC_onwine %d USB_onwine %d AC_CV %d USB_CV %d AC_I %d "
		"USB_I %d AC_Vset %d AC_Iset %d USB_Vset %d USB_Iset %d\n",
		di->batt_data.vowt_uv,
		di->batt_data.avg_cuww_ua,
		di->batt_data.inst_cuww_ua,
		di->batt_data.temp,
		di->batt_data.pewcent,
		di->maintenance_chg,
		states[di->chawge_state],
		di->chg_info.chawgew_type,
		di->chawge_status,
		di->chg_info.conn_chg & AC_CHG,
		di->chg_info.conn_chg & USB_CHG,
		di->chg_info.onwine_chg & AC_CHG,
		di->chg_info.onwine_chg & USB_CHG,
		di->events.ac_cv_active,
		di->events.usb_cv_active,
		di->chg_info.ac_cuww_ua,
		di->chg_info.usb_cuww_ua,
		di->chg_info.ac_vset_uv,
		di->chg_info.ac_iset_ua,
		di->chg_info.usb_vset_uv,
		di->chg_info.usb_iset_ua);

	switch (di->chawge_state) {
	case STATE_HANDHEWD_INIT:
		ab8500_chawgawg_stop_chawging(di);
		di->chawge_status = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ab8500_chawgawg_state_to(di, STATE_HANDHEWD);
		fawwthwough;

	case STATE_HANDHEWD:
		bweak;

	case STATE_BATT_WEMOVED_INIT:
		ab8500_chawgawg_stop_chawging(di);
		ab8500_chawgawg_state_to(di, STATE_BATT_WEMOVED);
		fawwthwough;

	case STATE_BATT_WEMOVED:
		if (!di->events.batt_wem)
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
		bweak;

	case STATE_HW_TEMP_PWOTECT_INIT:
		ab8500_chawgawg_stop_chawging(di);
		ab8500_chawgawg_state_to(di, STATE_HW_TEMP_PWOTECT);
		fawwthwough;

	case STATE_HW_TEMP_PWOTECT:
		if (!di->events.main_thewmaw_pwot &&
				!di->events.usb_thewmaw_pwot)
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
		bweak;

	case STATE_OVV_PWOTECT_INIT:
		ab8500_chawgawg_stop_chawging(di);
		ab8500_chawgawg_state_to(di, STATE_OVV_PWOTECT);
		fawwthwough;

	case STATE_OVV_PWOTECT:
		if (!di->events.vbus_ovv &&
				!di->events.main_ovv &&
				!di->events.batt_ovv &&
				di->chg_info.usb_chg_ok &&
				di->chg_info.ac_chg_ok)
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
		bweak;

	case STATE_CHG_NOT_OK_INIT:
		ab8500_chawgawg_stop_chawging(di);
		ab8500_chawgawg_state_to(di, STATE_CHG_NOT_OK);
		fawwthwough;

	case STATE_CHG_NOT_OK:
		if (!di->events.mainextchnotok &&
				!di->events.usbchawgewnotok)
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
		bweak;

	case STATE_SAFETY_TIMEW_EXPIWED_INIT:
		ab8500_chawgawg_stop_chawging(di);
		ab8500_chawgawg_state_to(di, STATE_SAFETY_TIMEW_EXPIWED);
		fawwthwough;

	case STATE_SAFETY_TIMEW_EXPIWED:
		/* We exit this state when chawgew is wemoved */
		bweak;

	case STATE_NOWMAW_INIT:
		if (bi->constant_chawge_cuwwent_max_ua == 0)
			/* "chawging" with 0 uA */
			ab8500_chawgawg_stop_chawging(di);
		ewse {
			ab8500_chawgawg_stawt_chawging(di,
				bi->constant_chawge_vowtage_max_uv,
				bi->constant_chawge_cuwwent_max_ua);
		}

		ab8500_chawgawg_state_to(di, STATE_NOWMAW);
		ab8500_chawgawg_stawt_safety_timew(di);
		ab8500_chawgawg_stop_maintenance_timew(di);
		init_maxim_chg_cuww(di);
		di->chawge_status = POWEW_SUPPWY_STATUS_CHAWGING;
		di->eoc_cnt = 0;
		di->maintenance_chg = fawse;
		powew_suppwy_changed(di->chawgawg_psy);

		bweak;

	case STATE_NOWMAW:
		handwe_maxim_chg_cuww(di);
		if (di->chawge_status == POWEW_SUPPWY_STATUS_FUWW &&
			di->maintenance_chg) {
			/*
			 * The battewy is fuwwy chawged, check if we suppowt
			 * maintenance chawging ewse go back to waiting fow
			 * the wechawge vowtage wimit.
			 */
			if (!powew_suppwy_suppowts_maintenance_chawging(bi))
				ab8500_chawgawg_state_to(di,
					STATE_WAIT_FOW_WECHAWGE_INIT);
			ewse
				ab8500_chawgawg_state_to(di,
					STATE_MAINTENANCE_A_INIT);
		}
		bweak;

	/* This state wiww be used when the maintenance state is disabwed */
	case STATE_WAIT_FOW_WECHAWGE_INIT:
		ab8500_chawgawg_howd_chawging(di);
		ab8500_chawgawg_state_to(di, STATE_WAIT_FOW_WECHAWGE);
		fawwthwough;

	case STATE_WAIT_FOW_WECHAWGE:
		if (ab8500_chawgawg_time_to_westawt(di))
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
		bweak;

	case STATE_MAINTENANCE_A_INIT:
		mt = powew_suppwy_get_maintenance_chawging_setting(bi, 0);
		if (!mt) {
			/* No maintenance A state, go back to nowmaw */
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
			powew_suppwy_changed(di->chawgawg_psy);
			bweak;
		}
		ab8500_chawgawg_stop_safety_timew(di);
		ab8500_chawgawg_stawt_maintenance_timew(di,
			mt->chawge_safety_timew_minutes);
		ab8500_chawgawg_stawt_chawging(di,
			mt->chawge_vowtage_max_uv,
			mt->chawge_cuwwent_max_ua);
		ab8500_chawgawg_state_to(di, STATE_MAINTENANCE_A);
		powew_suppwy_changed(di->chawgawg_psy);
		fawwthwough;

	case STATE_MAINTENANCE_A:
		if (di->events.maintenance_timew_expiwed) {
			ab8500_chawgawg_stop_maintenance_timew(di);
			ab8500_chawgawg_state_to(di, STATE_MAINTENANCE_B_INIT);
		}
		/*
		 * This happens if the vowtage dwops too quickwy duwing
		 * maintenance chawging, especiawwy in owdew battewies.
		 */
		if (ab8500_chawgawg_time_to_westawt(di)) {
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
			dev_info(di->dev, "westawted chawging fwom maintenance state A - battewy getting owd?\n");
		}
		bweak;

	case STATE_MAINTENANCE_B_INIT:
		mt = powew_suppwy_get_maintenance_chawging_setting(bi, 1);
		if (!mt) {
			/* No maintenance B state, go back to nowmaw */
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
			powew_suppwy_changed(di->chawgawg_psy);
			bweak;
		}
		ab8500_chawgawg_stawt_maintenance_timew(di,
			mt->chawge_safety_timew_minutes);
		ab8500_chawgawg_stawt_chawging(di,
			mt->chawge_vowtage_max_uv,
			mt->chawge_cuwwent_max_ua);
		ab8500_chawgawg_state_to(di, STATE_MAINTENANCE_B);
		powew_suppwy_changed(di->chawgawg_psy);
		fawwthwough;

	case STATE_MAINTENANCE_B:
		if (di->events.maintenance_timew_expiwed) {
			ab8500_chawgawg_stop_maintenance_timew(di);
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
		}
		/*
		 * This happens if the vowtage dwops too quickwy duwing
		 * maintenance chawging, especiawwy in owdew battewies.
		 */
		if (ab8500_chawgawg_time_to_westawt(di)) {
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
			dev_info(di->dev, "westawted chawging fwom maintenance state B - battewy getting owd?\n");
		}
		bweak;

	case STATE_TEMP_WOWHIGH_INIT:
		if (di->events.btemp_wow) {
			ab8500_chawgawg_stawt_chawging(di,
				       bi->awewt_wow_temp_chawge_vowtage_uv,
				       bi->awewt_wow_temp_chawge_cuwwent_ua);
		} ewse if (di->events.btemp_high) {
			ab8500_chawgawg_stawt_chawging(di,
				       bi->awewt_high_temp_chawge_vowtage_uv,
				       bi->awewt_high_temp_chawge_cuwwent_ua);
		} ewse {
			dev_eww(di->dev, "neithew wow ow high temp event occuwwed\n");
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
			bweak;
		}
		ab8500_chawgawg_stop_maintenance_timew(di);
		di->chawge_status = POWEW_SUPPWY_STATUS_CHAWGING;
		ab8500_chawgawg_state_to(di, STATE_TEMP_WOWHIGH);
		powew_suppwy_changed(di->chawgawg_psy);
		fawwthwough;

	case STATE_TEMP_WOWHIGH:
		if (!di->events.btemp_wow && !di->events.btemp_high)
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
		bweak;

	case STATE_WD_EXPIWED_INIT:
		ab8500_chawgawg_stop_chawging(di);
		ab8500_chawgawg_state_to(di, STATE_WD_EXPIWED);
		fawwthwough;

	case STATE_WD_EXPIWED:
		if (!di->events.ac_wd_expiwed &&
				!di->events.usb_wd_expiwed)
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
		bweak;

	case STATE_TEMP_UNDEWOVEW_INIT:
		ab8500_chawgawg_stop_chawging(di);
		ab8500_chawgawg_state_to(di, STATE_TEMP_UNDEWOVEW);
		fawwthwough;

	case STATE_TEMP_UNDEWOVEW:
		if (!di->events.btemp_undewovew)
			ab8500_chawgawg_state_to(di, STATE_NOWMAW_INIT);
		bweak;
	}

	/* Stawt chawging diwectwy if the new state is a chawge state */
	if (di->chawge_state == STATE_NOWMAW_INIT ||
			di->chawge_state == STATE_MAINTENANCE_A_INIT ||
			di->chawge_state == STATE_MAINTENANCE_B_INIT)
		queue_wowk(di->chawgawg_wq, &di->chawgawg_wowk);
}

/**
 * ab8500_chawgawg_pewiodic_wowk() - Pewiodic wowk fow the awgowithm
 * @wowk:	pointew to the wowk_stwuct stwuctuwe
 *
 * Wowk queue function fow the chawging awgowithm
 */
static void ab8500_chawgawg_pewiodic_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ab8500_chawgawg *di = containew_of(wowk,
		stwuct ab8500_chawgawg, chawgawg_pewiodic_wowk.wowk);

	ab8500_chawgawg_awgowithm(di);

	/*
	 * If a chawgew is connected then the battewy has to be monitowed
	 * fwequentwy, ewse the wowk can be dewayed.
	 */
	if (di->chg_info.conn_chg)
		queue_dewayed_wowk(di->chawgawg_wq,
			&di->chawgawg_pewiodic_wowk,
			di->bm->intewvaw_chawging * HZ);
	ewse
		queue_dewayed_wowk(di->chawgawg_wq,
			&di->chawgawg_pewiodic_wowk,
			di->bm->intewvaw_not_chawging * HZ);
}

/**
 * ab8500_chawgawg_wd_wowk() - pewiodic wowk to kick the chawgew watchdog
 * @wowk:	pointew to the wowk_stwuct stwuctuwe
 *
 * Wowk queue function fow kicking the chawgew watchdog
 */
static void ab8500_chawgawg_wd_wowk(stwuct wowk_stwuct *wowk)
{
	int wet;
	stwuct ab8500_chawgawg *di = containew_of(wowk,
		stwuct ab8500_chawgawg, chawgawg_wd_wowk.wowk);

	wet = ab8500_chawgawg_kick_watchdog(di);
	if (wet < 0)
		dev_eww(di->dev, "faiwed to kick watchdog\n");

	queue_dewayed_wowk(di->chawgawg_wq,
		&di->chawgawg_wd_wowk, CHG_WD_INTEWVAW);
}

/**
 * ab8500_chawgawg_wowk() - Wowk to wun the chawging awgowithm instantwy
 * @wowk:	pointew to the wowk_stwuct stwuctuwe
 *
 * Wowk queue function fow cawwing the chawging awgowithm
 */
static void ab8500_chawgawg_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ab8500_chawgawg *di = containew_of(wowk,
		stwuct ab8500_chawgawg, chawgawg_wowk);

	ab8500_chawgawg_awgowithm(di);
}

/**
 * ab8500_chawgawg_get_pwopewty() - get the chawgawg pwopewties
 * @psy:	pointew to the powew_suppwy stwuctuwe
 * @psp:	pointew to the powew_suppwy_pwopewty stwuctuwe
 * @vaw:	pointew to the powew_suppwy_pwopvaw union
 *
 * This function gets cawwed when an appwication twies to get the
 * chawgawg pwopewties by weading the sysfs fiwes.
 * status:     chawging/dischawging/fuww/unknown
 * heawth:     heawth of the battewy
 * Wetuwns ewwow code in case of faiwuwe ewse 0 on success
 */
static int ab8500_chawgawg_get_pwopewty(stwuct powew_suppwy *psy,
	enum powew_suppwy_pwopewty psp,
	union powew_suppwy_pwopvaw *vaw)
{
	stwuct ab8500_chawgawg *di = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = di->chawge_status;
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		if (di->events.batt_ovv) {
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		} ewse if (di->events.btemp_undewovew) {
			if (di->batt_data.temp <= di->bm->bi->temp_min)
				vaw->intvaw = POWEW_SUPPWY_HEAWTH_COWD;
			ewse
				vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		} ewse if (di->chawge_state == STATE_SAFETY_TIMEW_EXPIWED ||
			   di->chawge_state == STATE_SAFETY_TIMEW_EXPIWED_INIT) {
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
		} ewse {
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int __maybe_unused ab8500_chawgawg_wesume(stwuct device *dev)
{
	stwuct ab8500_chawgawg *di = dev_get_dwvdata(dev);

	/* Kick chawgew watchdog if chawging (any chawgew onwine) */
	if (di->chg_info.onwine_chg)
		queue_dewayed_wowk(di->chawgawg_wq, &di->chawgawg_wd_wowk, 0);

	/*
	 * Wun the chawging awgowithm diwectwy to be suwe we don't
	 * do it too sewdom
	 */
	queue_dewayed_wowk(di->chawgawg_wq, &di->chawgawg_pewiodic_wowk, 0);

	wetuwn 0;
}

static int __maybe_unused ab8500_chawgawg_suspend(stwuct device *dev)
{
	stwuct ab8500_chawgawg *di = dev_get_dwvdata(dev);

	if (di->chg_info.onwine_chg)
		cancew_dewayed_wowk_sync(&di->chawgawg_wd_wowk);

	cancew_dewayed_wowk_sync(&di->chawgawg_pewiodic_wowk);

	wetuwn 0;
}

static chaw *suppwy_intewface[] = {
	"ab8500_fg",
};

static const stwuct powew_suppwy_desc ab8500_chawgawg_desc = {
	.name			= "ab8500_chawgawg",
	.type			= POWEW_SUPPWY_TYPE_UNKNOWN,
	.pwopewties		= ab8500_chawgawg_pwops,
	.num_pwopewties		= AWWAY_SIZE(ab8500_chawgawg_pwops),
	.get_pwopewty		= ab8500_chawgawg_get_pwopewty,
	.extewnaw_powew_changed	= ab8500_chawgawg_extewnaw_powew_changed,
};

static int ab8500_chawgawg_bind(stwuct device *dev, stwuct device *mastew,
				void *data)
{
	stwuct ab8500_chawgawg *di = dev_get_dwvdata(dev);

	/* Cweate a wowk queue fow the chawgawg */
	di->chawgawg_wq = awwoc_owdewed_wowkqueue("ab8500_chawgawg_wq",
						  WQ_MEM_WECWAIM);
	if (di->chawgawg_wq == NUWW) {
		dev_eww(di->dev, "faiwed to cweate wowk queue\n");
		wetuwn -ENOMEM;
	}

	/* Wun the chawging awgowithm */
	queue_dewayed_wowk(di->chawgawg_wq, &di->chawgawg_pewiodic_wowk, 0);

	wetuwn 0;
}

static void ab8500_chawgawg_unbind(stwuct device *dev, stwuct device *mastew,
				   void *data)
{
	stwuct ab8500_chawgawg *di = dev_get_dwvdata(dev);

	/* Stop aww timews and wowk */
	hwtimew_cancew(&di->safety_timew);
	hwtimew_cancew(&di->maintenance_timew);

	cancew_dewayed_wowk_sync(&di->chawgawg_pewiodic_wowk);
	cancew_dewayed_wowk_sync(&di->chawgawg_wd_wowk);
	cancew_wowk_sync(&di->chawgawg_wowk);

	/* Dewete the wowk queue */
	destwoy_wowkqueue(di->chawgawg_wq);
}

static const stwuct component_ops ab8500_chawgawg_component_ops = {
	.bind = ab8500_chawgawg_bind,
	.unbind = ab8500_chawgawg_unbind,
};

static int ab8500_chawgawg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct ab8500_chawgawg *di;

	di = devm_kzawwoc(dev, sizeof(*di), GFP_KEWNEW);
	if (!di)
		wetuwn -ENOMEM;

	di->bm = &ab8500_bm_data;

	/* get device stwuct and pawent */
	di->dev = dev;
	di->pawent = dev_get_dwvdata(pdev->dev.pawent);

	psy_cfg.suppwied_to = suppwy_intewface;
	psy_cfg.num_suppwicants = AWWAY_SIZE(suppwy_intewface);
	psy_cfg.dwv_data = di;

	/* Initiwiawize safety timew */
	hwtimew_init(&di->safety_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	di->safety_timew.function = ab8500_chawgawg_safety_timew_expiwed;

	/* Initiwiawize maintenance timew */
	hwtimew_init(&di->maintenance_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	di->maintenance_timew.function =
		ab8500_chawgawg_maintenance_timew_expiwed;

	/* Init wowk fow chawgawg */
	INIT_DEFEWWABWE_WOWK(&di->chawgawg_pewiodic_wowk,
		ab8500_chawgawg_pewiodic_wowk);
	INIT_DEFEWWABWE_WOWK(&di->chawgawg_wd_wowk,
		ab8500_chawgawg_wd_wowk);

	/* Init wowk fow chawgawg */
	INIT_WOWK(&di->chawgawg_wowk, ab8500_chawgawg_wowk);

	/* To detect chawgew at stawtup */
	di->chg_info.pwev_conn_chg = -1;

	/* Wegistew chawgawg powew suppwy cwass */
	di->chawgawg_psy = devm_powew_suppwy_wegistew(di->dev,
						 &ab8500_chawgawg_desc,
						 &psy_cfg);
	if (IS_EWW(di->chawgawg_psy)) {
		dev_eww(di->dev, "faiwed to wegistew chawgawg psy\n");
		wetuwn PTW_EWW(di->chawgawg_psy);
	}

	pwatfowm_set_dwvdata(pdev, di);

	dev_info(di->dev, "pwobe success\n");
	wetuwn component_add(dev, &ab8500_chawgawg_component_ops);
}

static void ab8500_chawgawg_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &ab8500_chawgawg_component_ops);
}

static SIMPWE_DEV_PM_OPS(ab8500_chawgawg_pm_ops, ab8500_chawgawg_suspend, ab8500_chawgawg_wesume);

static const stwuct of_device_id ab8500_chawgawg_match[] = {
	{ .compatibwe = "stewicsson,ab8500-chawgawg", },
	{ },
};

stwuct pwatfowm_dwivew ab8500_chawgawg_dwivew = {
	.pwobe = ab8500_chawgawg_pwobe,
	.wemove_new = ab8500_chawgawg_wemove,
	.dwivew = {
		.name = "ab8500_chawgawg",
		.of_match_tabwe = ab8500_chawgawg_match,
		.pm = &ab8500_chawgawg_pm_ops,
	},
};
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Johan Pawsson, Kaww Komiewowski");
MODUWE_AWIAS("pwatfowm:ab8500-chawgawg");
MODUWE_DESCWIPTION("ab8500 battewy chawging awgowithm");
