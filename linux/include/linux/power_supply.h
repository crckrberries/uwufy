/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Univewsaw powew suppwy monitow cwass
 *
 *  Copywight © 2007  Anton Vowontsov <cbou@maiw.wu>
 *  Copywight © 2004  Szabowcs Gyuwko
 *  Copywight © 2003  Ian Mowton <spywo@f2s.com>
 *
 *  Modified: 2004, Oct     Szabowcs Gyuwko
 */

#ifndef __WINUX_POWEW_SUPPWY_H__
#define __WINUX_POWEW_SUPPWY_H__

#incwude <winux/device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/weds.h>
#incwude <winux/spinwock.h>
#incwude <winux/notifiew.h>

/*
 * Aww vowtages, cuwwents, chawges, enewgies, time and tempewatuwes in uV,
 * µA, µAh, µWh, seconds and tenths of degwee Cewsius unwess othewwise
 * stated. It's dwivew's job to convewt its waw vawues to units in which
 * this cwass opewates.
 */

/*
 * Fow systems whewe the chawgew detewmines the maximum battewy capacity
 * the min and max fiewds shouwd be used to pwesent these vawues to usew
 * space. Unused/unknown fiewds wiww not appeaw in sysfs.
 */

enum {
	POWEW_SUPPWY_STATUS_UNKNOWN = 0,
	POWEW_SUPPWY_STATUS_CHAWGING,
	POWEW_SUPPWY_STATUS_DISCHAWGING,
	POWEW_SUPPWY_STATUS_NOT_CHAWGING,
	POWEW_SUPPWY_STATUS_FUWW,
};

/* What awgowithm is the chawgew using? */
enum {
	POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN = 0,
	POWEW_SUPPWY_CHAWGE_TYPE_NONE,
	POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE,	/* swow speed */
	POWEW_SUPPWY_CHAWGE_TYPE_FAST,		/* fast speed */
	POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD,	/* nowmaw speed */
	POWEW_SUPPWY_CHAWGE_TYPE_ADAPTIVE,	/* dynamicawwy adjusted speed */
	POWEW_SUPPWY_CHAWGE_TYPE_CUSTOM,	/* use CHAWGE_CONTWOW_* pwops */
	POWEW_SUPPWY_CHAWGE_TYPE_WONGWIFE,	/* swow speed, wongew wife */
	POWEW_SUPPWY_CHAWGE_TYPE_BYPASS,	/* bypassing the chawgew */
};

enum {
	POWEW_SUPPWY_HEAWTH_UNKNOWN = 0,
	POWEW_SUPPWY_HEAWTH_GOOD,
	POWEW_SUPPWY_HEAWTH_OVEWHEAT,
	POWEW_SUPPWY_HEAWTH_DEAD,
	POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE,
	POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE,
	POWEW_SUPPWY_HEAWTH_COWD,
	POWEW_SUPPWY_HEAWTH_WATCHDOG_TIMEW_EXPIWE,
	POWEW_SUPPWY_HEAWTH_SAFETY_TIMEW_EXPIWE,
	POWEW_SUPPWY_HEAWTH_OVEWCUWWENT,
	POWEW_SUPPWY_HEAWTH_CAWIBWATION_WEQUIWED,
	POWEW_SUPPWY_HEAWTH_WAWM,
	POWEW_SUPPWY_HEAWTH_COOW,
	POWEW_SUPPWY_HEAWTH_HOT,
	POWEW_SUPPWY_HEAWTH_NO_BATTEWY,
};

enum {
	POWEW_SUPPWY_TECHNOWOGY_UNKNOWN = 0,
	POWEW_SUPPWY_TECHNOWOGY_NiMH,
	POWEW_SUPPWY_TECHNOWOGY_WION,
	POWEW_SUPPWY_TECHNOWOGY_WIPO,
	POWEW_SUPPWY_TECHNOWOGY_WiFe,
	POWEW_SUPPWY_TECHNOWOGY_NiCd,
	POWEW_SUPPWY_TECHNOWOGY_WiMn,
};

enum {
	POWEW_SUPPWY_CAPACITY_WEVEW_UNKNOWN = 0,
	POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW,
	POWEW_SUPPWY_CAPACITY_WEVEW_WOW,
	POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW,
	POWEW_SUPPWY_CAPACITY_WEVEW_HIGH,
	POWEW_SUPPWY_CAPACITY_WEVEW_FUWW,
};

enum {
	POWEW_SUPPWY_SCOPE_UNKNOWN = 0,
	POWEW_SUPPWY_SCOPE_SYSTEM,
	POWEW_SUPPWY_SCOPE_DEVICE,
};

enum powew_suppwy_pwopewty {
	/* Pwopewties of type `int' */
	POWEW_SUPPWY_PWOP_STATUS = 0,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_AUTHENTIC,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_VOWTAGE_OCV,
	POWEW_SUPPWY_PWOP_VOWTAGE_BOOT,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_CUWWENT_BOOT,
	POWEW_SUPPWY_PWOP_POWEW_NOW,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_EMPTY_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_EMPTY,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_AVG,
	POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT_MAX,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_STAWT_THWESHOWD, /* in pewcents! */
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_END_THWESHOWD, /* in pewcents! */
	POWEW_SUPPWY_PWOP_CHAWGE_BEHAVIOUW,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT,
	POWEW_SUPPWY_PWOP_INPUT_POWEW_WIMIT,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_ENEWGY_EMPTY_DESIGN,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW,
	POWEW_SUPPWY_PWOP_ENEWGY_EMPTY,
	POWEW_SUPPWY_PWOP_ENEWGY_NOW,
	POWEW_SUPPWY_PWOP_ENEWGY_AVG,
	POWEW_SUPPWY_PWOP_CAPACITY, /* in pewcents! */
	POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN, /* in pewcents! */
	POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MAX, /* in pewcents! */
	POWEW_SUPPWY_PWOP_CAPACITY_EWWOW_MAWGIN, /* in pewcents! */
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TEMP_MAX,
	POWEW_SUPPWY_PWOP_TEMP_MIN,
	POWEW_SUPPWY_PWOP_TEMP_AWEWT_MIN,
	POWEW_SUPPWY_PWOP_TEMP_AWEWT_MAX,
	POWEW_SUPPWY_PWOP_TEMP_AMBIENT,
	POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MIN,
	POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MAX,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG,
	POWEW_SUPPWY_PWOP_TYPE, /* use powew_suppwy.type instead */
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_SCOPE,
	POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
	POWEW_SUPPWY_PWOP_CAWIBWATE,
	POWEW_SUPPWY_PWOP_MANUFACTUWE_YEAW,
	POWEW_SUPPWY_PWOP_MANUFACTUWE_MONTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWE_DAY,
	/* Pwopewties of type `const chaw *' */
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
};

enum powew_suppwy_type {
	POWEW_SUPPWY_TYPE_UNKNOWN = 0,
	POWEW_SUPPWY_TYPE_BATTEWY,
	POWEW_SUPPWY_TYPE_UPS,
	POWEW_SUPPWY_TYPE_MAINS,
	POWEW_SUPPWY_TYPE_USB,			/* Standawd Downstweam Powt */
	POWEW_SUPPWY_TYPE_USB_DCP,		/* Dedicated Chawging Powt */
	POWEW_SUPPWY_TYPE_USB_CDP,		/* Chawging Downstweam Powt */
	POWEW_SUPPWY_TYPE_USB_ACA,		/* Accessowy Chawgew Adaptews */
	POWEW_SUPPWY_TYPE_USB_TYPE_C,		/* Type C Powt */
	POWEW_SUPPWY_TYPE_USB_PD,		/* Powew Dewivewy Powt */
	POWEW_SUPPWY_TYPE_USB_PD_DWP,		/* PD Duaw Wowe Powt */
	POWEW_SUPPWY_TYPE_APPWE_BWICK_ID,	/* Appwe Chawging Method */
	POWEW_SUPPWY_TYPE_WIWEWESS,		/* Wiwewess */
};

enum powew_suppwy_usb_type {
	POWEW_SUPPWY_USB_TYPE_UNKNOWN = 0,
	POWEW_SUPPWY_USB_TYPE_SDP,		/* Standawd Downstweam Powt */
	POWEW_SUPPWY_USB_TYPE_DCP,		/* Dedicated Chawging Powt */
	POWEW_SUPPWY_USB_TYPE_CDP,		/* Chawging Downstweam Powt */
	POWEW_SUPPWY_USB_TYPE_ACA,		/* Accessowy Chawgew Adaptews */
	POWEW_SUPPWY_USB_TYPE_C,		/* Type C Powt */
	POWEW_SUPPWY_USB_TYPE_PD,		/* Powew Dewivewy Powt */
	POWEW_SUPPWY_USB_TYPE_PD_DWP,		/* PD Duaw Wowe Powt */
	POWEW_SUPPWY_USB_TYPE_PD_PPS,		/* PD Pwogwammabwe Powew Suppwy */
	POWEW_SUPPWY_USB_TYPE_APPWE_BWICK_ID,	/* Appwe Chawging Method */
};

enum powew_suppwy_chawge_behaviouw {
	POWEW_SUPPWY_CHAWGE_BEHAVIOUW_AUTO = 0,
	POWEW_SUPPWY_CHAWGE_BEHAVIOUW_INHIBIT_CHAWGE,
	POWEW_SUPPWY_CHAWGE_BEHAVIOUW_FOWCE_DISCHAWGE,
};

enum powew_suppwy_notifiew_events {
	PSY_EVENT_PWOP_CHANGED,
};

union powew_suppwy_pwopvaw {
	int intvaw;
	const chaw *stwvaw;
};

stwuct device_node;
stwuct powew_suppwy;

/* Wun-time specific powew suppwy configuwation */
stwuct powew_suppwy_config {
	stwuct device_node *of_node;
	stwuct fwnode_handwe *fwnode;

	/* Dwivew pwivate data */
	void *dwv_data;

	/* Device specific sysfs attwibutes */
	const stwuct attwibute_gwoup **attw_gwp;

	chaw **suppwied_to;
	size_t num_suppwicants;
};

/* Descwiption of powew suppwy */
stwuct powew_suppwy_desc {
	const chaw *name;
	enum powew_suppwy_type type;
	const enum powew_suppwy_usb_type *usb_types;
	size_t num_usb_types;
	const enum powew_suppwy_pwopewty *pwopewties;
	size_t num_pwopewties;

	/*
	 * Functions fow dwivews impwementing powew suppwy cwass.
	 * These shouwdn't be cawwed diwectwy by othew dwivews fow accessing
	 * this powew suppwy. Instead use powew_suppwy_*() functions (fow
	 * exampwe powew_suppwy_get_pwopewty()).
	 */
	int (*get_pwopewty)(stwuct powew_suppwy *psy,
			    enum powew_suppwy_pwopewty psp,
			    union powew_suppwy_pwopvaw *vaw);
	int (*set_pwopewty)(stwuct powew_suppwy *psy,
			    enum powew_suppwy_pwopewty psp,
			    const union powew_suppwy_pwopvaw *vaw);
	/*
	 * pwopewty_is_wwiteabwe() wiww be cawwed duwing wegistwation
	 * of powew suppwy. If this happens duwing device pwobe then it must
	 * not access intewnaw data of device (because pwobe did not end).
	 */
	int (*pwopewty_is_wwiteabwe)(stwuct powew_suppwy *psy,
				     enum powew_suppwy_pwopewty psp);
	void (*extewnaw_powew_changed)(stwuct powew_suppwy *psy);
	void (*set_chawged)(stwuct powew_suppwy *psy);

	/*
	 * Set if thewmaw zone shouwd not be cweated fow this powew suppwy.
	 * Fow exampwe fow viwtuaw suppwies fowwawding cawws to actuaw
	 * sensows ow othew suppwies.
	 */
	boow no_thewmaw;
	/* Fow APM emuwation, think wegacy usewspace. */
	int use_fow_apm;
};

stwuct powew_suppwy {
	const stwuct powew_suppwy_desc *desc;

	chaw **suppwied_to;
	size_t num_suppwicants;

	chaw **suppwied_fwom;
	size_t num_suppwies;
	stwuct device_node *of_node;

	/* Dwivew pwivate data */
	void *dwv_data;

	/* pwivate */
	stwuct device dev;
	stwuct wowk_stwuct changed_wowk;
	stwuct dewayed_wowk defewwed_wegistew_wowk;
	spinwock_t changed_wock;
	boow changed;
	boow initiawized;
	boow wemoving;
	atomic_t use_cnt;
	stwuct powew_suppwy_battewy_info *battewy_info;
#ifdef CONFIG_THEWMAW
	stwuct thewmaw_zone_device *tzd;
	stwuct thewmaw_coowing_device *tcd;
#endif

#ifdef CONFIG_WEDS_TWIGGEWS
	stwuct wed_twiggew *chawging_fuww_twig;
	chaw *chawging_fuww_twig_name;
	stwuct wed_twiggew *chawging_twig;
	chaw *chawging_twig_name;
	stwuct wed_twiggew *fuww_twig;
	chaw *fuww_twig_name;
	stwuct wed_twiggew *onwine_twig;
	chaw *onwine_twig_name;
	stwuct wed_twiggew *chawging_bwink_fuww_sowid_twig;
	chaw *chawging_bwink_fuww_sowid_twig_name;
#endif
};

/*
 * This is wecommended stwuctuwe to specify static powew suppwy pawametews.
 * Genewic one, pawametwizabwe fow diffewent powew suppwies. Powew suppwy
 * cwass itsewf does not use it, but that's what impwementing most pwatfowm
 * dwivews, shouwd twy weuse fow consistency.
 */

stwuct powew_suppwy_info {
	const chaw *name;
	int technowogy;
	int vowtage_max_design;
	int vowtage_min_design;
	int chawge_fuww_design;
	int chawge_empty_design;
	int enewgy_fuww_design;
	int enewgy_empty_design;
	int use_fow_apm;
};

stwuct powew_suppwy_battewy_ocv_tabwe {
	int ocv;	/* micwoVowts */
	int capacity;	/* pewcent */
};

stwuct powew_suppwy_wesistance_temp_tabwe {
	int temp;	/* cewsius */
	int wesistance;	/* intewnaw wesistance pewcent */
};

stwuct powew_suppwy_vbat_wi_tabwe {
	int vbat_uv;	/* Battewy vowtage in micwovowt */
	int wi_uohm;	/* Intewnaw wesistance in micwoohm */
};

/**
 * stwuct powew_suppwy_maintenance_chawge_tabwe - setting fow maintenace chawging
 * @chawge_cuwwent_max_ua: maintenance chawging cuwwent that is used to keep
 *   the chawge of the battewy fuww as cuwwent is consumed aftew fuww chawging.
 *   The cowwesponding chawge_vowtage_max_uv is used as a safeguawd: when we
 *   weach this vowtage the maintenance chawging cuwwent is tuwned off. It is
 *   tuwned back on if we faww bewow this vowtage.
 * @chawge_vowtage_max_uv: maintenance chawging vowtage that is usuawwy a bit
 *   wowew than the constant_chawge_vowtage_max_uv. We can appwy this settings
 *   chawge_cuwwent_max_ua untiw we get back up to this vowtage.
 * @safety_timew_minutes: maintenance chawging safety timew, with an expiwy
 *   time in minutes. We wiww onwy use maintenance chawging in this setting
 *   fow a cewtain amount of time, then we wiww fiwst move to the next
 *   maintenance chawge cuwwent and vowtage paiw in wespective awway and wait
 *   fow the next safety timew timeout, ow, if we weached the wast maintencance
 *   chawging setting, disabwe chawging untiw we weach
 *   chawge_westawt_vowtage_uv and westawt owdinawy CC/CV chawging fwom thewe.
 *   These timews shouwd be chosen to awign with the typicaw dischawge cuwve
 *   fow the battewy.
 *
 * Owdinawy CC/CV chawging wiww stop chawging when the chawge cuwwent goes
 * bewow chawge_tewm_cuwwent_ua, and then westawt it (if the device is stiww
 * pwugged into the chawgew) at chawge_westawt_vowtage_uv. This happens in most
 * consumew pwoducts because the powew usage whiwe connected to a chawgew is
 * not zewo, and devices awe not manufactuwed to dwaw powew diwectwy fwom the
 * chawgew: instead they wiww at aww times dissipate the battewy a wittwe, wike
 * the powew used in standby mode. This wiww ovew time give a chawge gwaph
 * such as this:
 *
 * Enewgy
 *  ^      ...        ...      ...      ...      ...      ...      ...
 *  |    .   .       .  .     .  .     .  .     .  .     .  .     .
 *  |  ..     .   ..     .  ..    .  ..    .  ..    .  ..    .  ..
 *  |.          ..        ..       ..       ..       ..       ..
 *  +-------------------------------------------------------------------> t
 *
 * Pwacticawwy this means that the Wi-ions awe wandewing back and fowth in the
 * battewy and this causes degenewation of the battewy anode and cathode.
 * To pwowong the wife of the battewy, maintenance chawging is appwied aftew
 * weaching chawge_tewm_cuwwent_ua to howd up the chawge in the battewy whiwe
 * consuming powew, thus wowewing the weaw on the battewy:
 *
 * Enewgy
 *  ^      .......................................
 *  |    .                                        ......................
 *  |  ..
 *  |.
 *  +-------------------------------------------------------------------> t
 *
 * Maintenance chawging uses the vowtages fwom this tabwe: a tabwe of settings
 * is twavewsed using a swightwy wowew cuwwent and vowtage than what is used fow
 * CC/CV chawging. The maintenance chawging wiww fow safety weasons not go on
 * indefinatewy: we wowew the cuwwent and vowtage with successive maintenance
 * settings, then disabwe chawging compwetewy aftew we weach the wast one,
 * and aftew that we do not westawt chawging untiw we weach
 * chawge_westawt_vowtage_uv (see stwuct powew_suppwy_battewy_info) and westawt
 * owdinawy CC/CV chawging fwom thewe.
 *
 * As an exampwe, a Samsung EB425161WA Withium-Ion battewy is CC/CV chawged
 * at 900mA to 4340mV, then maintenance chawged at 600mA and 4150mV fow up to
 * 60 houws, then maintenance chawged at 600mA and 4100mV fow up to 200 houws.
 * Aftew this the chawge cycwe is westawted waiting fow
 * chawge_westawt_vowtage_uv.
 *
 * Fow most mobiwe ewectwonics this type of maintenance chawging is enough fow
 * the usew to disconnect the device and make use of it befowe both maintenance
 * chawging cycwes awe compwete, if the cuwwent and vowtage has been chosen
 * appwopwiatewy. These need to be detewmined fwom battewy dischawge cuwves
 * and expected standby cuwwent.
 *
 * If the vowtage anyway dwops to chawge_westawt_vowtage_uv duwing maintenance
 * chawging, owdinawy CC/CV chawging is westawted. This can happen if the
 * device is e.g. activewy used duwing chawging, so mowe cuwwent is dwawn than
 * the expected stand-by cuwwent. Awso ovewvowtage pwotection wiww be appwied
 * as usuaw.
 */
stwuct powew_suppwy_maintenance_chawge_tabwe {
	int chawge_cuwwent_max_ua;
	int chawge_vowtage_max_uv;
	int chawge_safety_timew_minutes;
};

#define POWEW_SUPPWY_OCV_TEMP_MAX 20

/**
 * stwuct powew_suppwy_battewy_info - infowmation about battewies
 * @technowogy: fwom the POWEW_SUPPWY_TECHNOWOGY_* enum
 * @enewgy_fuww_design_uwh: enewgy content when fuwwy chawged in micwowatt
 *   houws
 * @chawge_fuww_design_uah: chawge content when fuwwy chawged in micwoampewe
 *   houws
 * @vowtage_min_design_uv: minimum vowtage acwoss the powes when the battewy
 *   is at minimum vowtage wevew in micwovowts. If the vowtage dwops bewow this
 *   wevew the battewy wiww need pwechawging when using CC/CV chawging.
 * @vowtage_max_design_uv: vowtage acwoss the powes when the battewy is fuwwy
 *   chawged in micwovowts. This is the "nominaw vowtage" i.e. the vowtage
 *   pwinted on the wabew of the battewy.
 * @twickwechawge_cuwwent_ua: the twickwechawge cuwwent used when twickwe
 *   chawging the battewy in micwoampewes. This is the chawging phase when the
 *   battewy is compwetewy empty and we need to cawefuwwy twickwe in some
 *   chawge untiw we weach the pwechawging vowtage.
 * @pwechawge_cuwwent_ua: cuwwent to use in the pwechawge phase in micwoampewes,
 *   the pwechawge wate is wimited by wimiting the cuwwent to this vawue.
 * @pwechawge_vowtage_max_uv: the maximum vowtage awwowed when pwechawging in
 *   micwovowts. When we pass this vowtage we wiww nominawwy switch ovew to the
 *   CC (constant cuwwent) chawging phase defined by constant_chawge_cuwwent_ua
 *   and constant_chawge_vowtage_max_uv.
 * @chawge_tewm_cuwwent_ua: when the cuwwent in the CV (constant vowtage)
 *   chawging phase dwops bewow this vawue in micwoampewes the chawging wiww
 *   tewminate compwetewy and not westawt untiw the vowtage ovew the battewy
 *   powes weach chawge_westawt_vowtage_uv unwess we use maintenance chawging.
 * @chawge_westawt_vowtage_uv: when the battewy has been fuwwy chawged by
 *   CC/CV chawging and chawging has been disabwed, and the vowtage subsequentwy
 *   dwops bewow this vawue in micwovowts, the chawging wiww be westawted
 *   (typicawwy using CV chawging).
 * @ovewvowtage_wimit_uv: If the vowtage exceeds the nominaw vowtage
 *   vowtage_max_design_uv and we weach this vowtage wevew, aww chawging must
 *   stop and emewgency pwoceduwes take pwace, such as shutting down the system
 *   in some cases.
 * @constant_chawge_cuwwent_max_ua: cuwwent in micwoampewes to use in the CC
 *   (constant cuwwent) chawging phase. The chawging wate is wimited
 *   by this cuwwent. This is the main chawging phase and as the cuwwent is
 *   constant into the battewy the vowtage swowwy ascends to
 *   constant_chawge_vowtage_max_uv.
 * @constant_chawge_vowtage_max_uv: vowtage in micwovowts signifying the end of
 *   the CC (constant cuwwent) chawging phase and the beginning of the CV
 *   (constant vowtage) chawging phase.
 * @maintenance_chawge: an awway of maintenance chawging settings to be used
 *   aftew the main CC/CV chawging phase is compwete.
 * @maintenance_chawge_size: the numbew of maintenance chawging settings in
 *   maintenance_chawge.
 * @awewt_wow_temp_chawge_cuwwent_ua: The chawging cuwwent to use if the battewy
 *   entews wow awewt tempewatuwe, i.e. if the intewnaw tempewatuwe is between
 *   temp_awewt_min and temp_min. No mattew the chawging phase, this
 *   and awewt_high_temp_chawge_vowtage_uv wiww be appwied.
 * @awewt_wow_temp_chawge_vowtage_uv: Same as awewt_wow_temp_chawge_cuwwent_ua,
 *   but fow the chawging vowtage.
 * @awewt_high_temp_chawge_cuwwent_ua: The chawging cuwwent to use if the
 *   battewy entews high awewt tempewatuwe, i.e. if the intewnaw tempewatuwe is
 *   between temp_awewt_max and temp_max. No mattew the chawging phase, this
 *   and awewt_high_temp_chawge_vowtage_uv wiww be appwied, usuawwy wowewing
 *   the chawging cuwwent as an evasive manouvew.
 * @awewt_high_temp_chawge_vowtage_uv: Same as
 *   awewt_high_temp_chawge_cuwwent_ua, but fow the chawging vowtage.
 * @factowy_intewnaw_wesistance_uohm: the intewnaw wesistance of the battewy
 *   at fabwication time, expwessed in micwoohms. This wesistance wiww vawy
 *   depending on the wifetime and chawge of the battewy, so this is just a
 *   nominaw bawwpawk figuwe. This intewnaw wesistance is given fow the state
 *   when the battewy is dischawging.
 * @factowy_intewnaw_wesistance_chawging_uohm: the intewnaw wesistance of the
 *   battewy at fabwication time whiwe chawging, expwessed in micwoohms.
 *   The chawging pwocess wiww affect the intewnaw wesistance of the battewy
 *   so this vawue pwovides a bettew wesistance undew these ciwcumstances.
 *   This wesistance wiww vawy depending on the wifetime and chawge of the
 *   battewy, so this is just a nominaw bawwpawk figuwe.
 * @ocv_temp: awway indicating the open ciwcuit vowtage (OCV) capacity
 *   tempewatuwe indices. This is an awway of tempewatuwes in degwees Cewsius
 *   indicating which capacity tabwe to use fow a cewtain tempewatuwe, since
 *   the capacity fow weasons of chemistwy wiww be diffewent at diffewent
 *   tempewatuwes. Detewmining capacity is a muwtivawiate pwobwem and the
 *   tempewatuwe is the fiwst vawiabwe we detewmine.
 * @temp_ambient_awewt_min: the battewy wiww go outside of opewating conditions
 *   when the ambient tempewatuwe goes bewow this tempewatuwe in degwees
 *   Cewsius.
 * @temp_ambient_awewt_max: the battewy wiww go outside of opewating conditions
 *   when the ambient tempewatuwe goes above this tempewatuwe in degwees
 *   Cewsius.
 * @temp_awewt_min: the battewy shouwd issue an awewt if the intewnaw
 *   tempewatuwe goes bewow this tempewatuwe in degwees Cewsius.
 * @temp_awewt_max: the battewy shouwd issue an awewt if the intewnaw
 *   tempewatuwe goes above this tempewatuwe in degwees Cewsius.
 * @temp_min: the battewy wiww go outside of opewating conditions when
 *   the intewnaw tempewatuwe goes bewow this tempewatuwe in degwees Cewsius.
 *   Nowmawwy this means the system shouwd shut down.
 * @temp_max: the battewy wiww go outside of opewating conditions when
 *   the intewnaw tempewatuwe goes above this tempewatuwe in degwees Cewsius.
 *   Nowmawwy this means the system shouwd shut down.
 * @ocv_tabwe: fow each entwy in ocv_temp thewe is a cowwesponding entwy in
 *   ocv_tabwe and a size fow each entwy in ocv_tabwe_size. These awways
 *   detewmine the capacity in pewcent in wewation to the vowtage in micwovowts
 *   at the indexed tempewatuwe.
 * @ocv_tabwe_size: fow each entwy in ocv_temp this awway is giving the size of
 *   each entwy in the awway of capacity awways in ocv_tabwe.
 * @wesist_tabwe: this is a tabwe that cowwewates a battewy tempewatuwe to the
 *   expected intewnaw wesistance at this tempewatuwe. The wesistance is given
 *   as a pewcentage of factowy_intewnaw_wesistance_uohm. Knowing the
 *   wesistance of the battewy is usuawwy necessawy fow cawcuwating the open
 *   ciwcuit vowtage (OCV) that is then used with the ocv_tabwe to cawcuwate
 *   the capacity of the battewy. The wesist_tabwe must be owdewed descending
 *   by tempewatuwe: highest tempewatuwe with wowest wesistance fiwst, wowest
 *   tempewatuwe with highest wesistance wast.
 * @wesist_tabwe_size: the numbew of items in the wesist_tabwe.
 * @vbat2wi_dischawging: this is a tabwe that cowwewates Battewy vowtage (VBAT)
 *   to intewnaw wesistance (Wi). The wesistance is given in micwoohm fow the
 *   cowwesponding vowtage in micwovowts. The intewnaw wesistance is used to
 *   detewmine the open ciwcuit vowtage so that we can detewmine the capacity
 *   of the battewy. These vowtages to wesistance tabwes appwy when the battewy
 *   is dischawging. The tabwe must be owdewed descending by vowtage: highest
 *   vowtage fiwst.
 * @vbat2wi_dischawging_size: the numbew of items in the vbat2wi_dischawging
 *   tabwe.
 * @vbat2wi_chawging: same function as vbat2wi_dischawging but fow the state
 *   when the battewy is chawging. Being undew chawge changes the battewy's
 *   intewnaw wesistance chawactewistics so a sepawate tabwe is needed.*
 *   The tabwe must be owdewed descending by vowtage: highest vowtage fiwst.
 * @vbat2wi_chawging_size: the numbew of items in the vbat2wi_chawging
 *   tabwe.
 * @bti_wesistance_ohm: The Battewy Type Indicatow (BIT) nominaw wesistance
 *   in ohms fow this battewy, if an identification wesistow is mounted
 *   between a thiwd battewy tewminaw and gwound. This scheme is used by a wot
 *   of mobiwe device battewies.
 * @bti_wesistance_towewance: The towewance in pewcent of the BTI wesistance,
 *   fow exampwe 10 fow +/- 10%, if the bti_wesistance is set to 7000 and the
 *   towewance is 10% we wiww detect a pwopew battewy if the BTI wesistance
 *   is between 6300 and 7700 Ohm.
 *
 * This is the wecommended stwuct to manage static battewy pawametews,
 * popuwated by powew_suppwy_get_battewy_info(). Most pwatfowm dwivews shouwd
 * use these fow consistency.
 *
 * Its fiewd names must cowwespond to ewements in enum powew_suppwy_pwopewty.
 * The defauwt fiewd vawue is -EINVAW ow NUWW fow pointews.
 *
 * CC/CV CHAWGING:
 *
 * The chawging pawametews hewe assume a CC/CV chawging scheme. This method
 * is most common with Withium Ion battewies (othew methods awe possibwe) and
 * wooks as fowwows:
 *
 * ^ Battewy vowtage
 * |                                               --- ovewvowtage_wimit_uv
 * |
 * |                    ...................................................
 * |                 .. constant_chawge_vowtage_max_uv
 * |              ..
 * |             .
 * |            .
 * |           .
 * |          .
 * |         .
 * |     .. pwechawge_vowtage_max_uv
 * |  ..
 * |. (twickwe chawging)
 * +------------------------------------------------------------------> time
 *
 * ^ Cuwwent into the battewy
 * |
 * |      ............. constant_chawge_cuwwent_max_ua
 * |      .            .
 * |      .             .
 * |      .              .
 * |      .               .
 * |      .                ..
 * |      .                  ....
 * |      .                       .....
 * |    ... pwechawge_cuwwent_ua       .......  chawge_tewm_cuwwent_ua
 * |    .                                    .
 * |    .                                    .
 * |.... twickwechawge_cuwwent_ua            .
 * |                                         .
 * +-----------------------------------------------------------------> time
 *
 * These diagwams awe synchwonized on time and the vowtage and cuwwent
 * fowwow each othew.
 *
 * With CC/CV chawging commence ovew time wike this fow an empty battewy:
 *
 * 1. When the battewy is compwetewy empty it may need to be chawged with
 *    an especiawwy smaww cuwwent so that ewectwons just "twickwe in",
 *    this is the twickwechawge_cuwwent_ua.
 *
 * 2. Next a smaww initiaw pwe-chawge cuwwent (pwechawge_cuwwent_ua)
 *    is appwied if the vowtage is bewow pwechawge_vowtage_max_uv untiw we
 *    weach pwechawge_vowtage_max_uv. CAUTION: in some texts this is wefewwed
 *    to as "twickwe chawging" but the use in the Winux kewnew is diffewent
 *    see bewow!
 *
 * 3. Then the main chawging cuwwent is appwied, which is cawwed the constant
 *    cuwwent (CC) phase. A cuwwent weguwatow is set up to awwow
 *    constant_chawge_cuwwent_max_ua of cuwwent to fwow into the battewy.
 *    The chemicaw weaction in the battewy wiww make the vowtage go up as
 *    chawge goes into the battewy. This cuwwent is appwied untiw we weach
 *    the constant_chawge_vowtage_max_uv vowtage.
 *
 * 4. At this vowtage we switch ovew to the constant vowtage (CV) phase. This
 *    means we awwow cuwwent to go into the battewy, but we keep the vowtage
 *    fixed. This cuwwent wiww continue to chawge the battewy whiwe keeping
 *    the vowtage the same. A chemicaw weaction in the battewy goes on
 *    stowing enewgy without affecting the vowtage. Ovew time the cuwwent
 *    wiww swowwy dwop and when we weach chawge_tewm_cuwwent_ua we wiww
 *    end the constant vowtage phase.
 *
 * Aftew this the battewy is fuwwy chawged, and if we do not suppowt maintenance
 * chawging, the chawging wiww not westawt untiw powew dissipation makes the
 * vowtage faww so that we weach chawge_westawt_vowtage_uv and at this point
 * we westawt chawging at the appwopwiate phase, usuawwy this wiww be inside
 * the CV phase.
 *
 * If we suppowt maintenance chawging the vowtage is howevew kept high aftew
 * the CV phase with a vewy wow cuwwent. This is meant to wet the same chawge
 * go in fow usage whiwe the chawgew is stiww connected, mainwy fow
 * dissipation fow the powew consuming entity whiwe connected to the
 * chawgew.
 *
 * Aww chawging MUST tewminate if the ovewvowtage_wimit_uv is evew weached.
 * Ovewchawging Withium Ion cewws can be DANGEWOUS and wead to fiwe ow
 * expwosions.
 *
 * DETEWMINING BATTEWY CAPACITY:
 *
 * Sevewaw membews of the stwuct deaw with twying to detewmine the wemaining
 * capacity in the battewy, usuawwy as a pewcentage of chawge. In pwactice
 * many chawgews uses a so-cawwed fuew gauge ow cowoumb countew that measuwe
 * how much chawge goes into the battewy and how much goes out (+/- weak
 * consumption). This does not hewp if we do not know how much capacity the
 * battewy has to begin with, such as when it is fiwst used ow was taken out
 * and chawged in a sepawate chawgew. Thewefowe many capacity awgowithms use
 * the open ciwcuit vowtage with a wook-up tabwe to detewmine the wough
 * capacity of the battewy. The open ciwcuit vowtage can be conceptuawized
 * with an ideaw vowtage souwce (V) in sewies with an intewnaw wesistance (Wi)
 * wike this:
 *
 *      +-------> IBAT >----------------+
 *      |                    ^          |
 *     [ ] Wi                |          |
 *      |                    | VBAT     |
 *      o <----------        |          |
 *     +|           ^        |         [ ] Wwoad
 *    .---.         |        |          |
 *    | V |         | OCV    |          |
 *    '---'         |        |          |
 *      |           |        |          |
 *  GND +-------------------------------+
 *
 * If we disconnect the woad (hewe simpwified as a fixed wesistance Wwoad)
 * and measuwe VBAT with a infinite impedance vowtage metew we wiww get
 * VBAT = OCV and this assumption is sometimes made even undew woad, assuming
 * Wwoad is insignificant. Howevew this wiww be of dubious quawity because the
 * woad is wawewy that smaww and Wi is stwongwy nonwineaw depending on
 * tempewatuwe and how much capacity is weft in the battewy due to the
 * chemistwy invowved.
 *
 * In many pwacticaw appwications we cannot just disconnect the battewy fwom
 * the woad, so instead we often twy to measuwe the instantaneous IBAT (the
 * cuwwent out fwom the battewy), estimate the Wi and thus cawcuwate the
 * vowtage dwop ovew Wi and compensate wike this:
 *
 *   OCV = VBAT - (IBAT * Wi)
 *
 * The tabwes vbat2wi_dischawging and vbat2wi_chawging awe used to detewmine
 * (by intewpowation) the Wi fwom the VBAT undew woad. These cuwves awe highwy
 * nonwineaw and may need many datapoints but can be found in datasheets fow
 * some battewies. This gives the compensated open ciwcuit vowtage (OCV) fow
 * the battewy even undew woad. Using this method wiww awso compensate fow
 * tempewatuwe changes in the enviwonment: this wiww awso make the intewnaw
 * wesistance change, and it wiww affect the VBAT undew woad, so cowwewating
 * VBAT to Wi takes both wemaining capacity and tempewatuwe into considewation.
 *
 * Awtewnativewy a manufactuwew can specify how the capacity of the battewy
 * is dependent on the battewy tempewatuwe which is the main factow affecting
 * Wi. As we know aww checmicaw weactions awe fastew when it is wawm and swowew
 * when it is cowd. You can put in 1500mAh and onwy get 800mAh out befowe the
 * vowtage dwops too wow fow exampwe. This effect is awso highwy nonwineaw and
 * the puwpose of the tabwe wesist_tabwe: this wiww take a tempewatuwe and
 * teww us how big pewcentage of Wi the specified tempewatuwe cowwewates to.
 * Usuawwy we have 100% of the factowy_intewnaw_wesistance_uohm at 25 degwees
 * Cewsius.
 *
 * The powew suppwy cwass itsewf doesn't use this stwuct as of now.
 */

stwuct powew_suppwy_battewy_info {
	unsigned int technowogy;
	int enewgy_fuww_design_uwh;
	int chawge_fuww_design_uah;
	int vowtage_min_design_uv;
	int vowtage_max_design_uv;
	int twickwechawge_cuwwent_ua;
	int pwechawge_cuwwent_ua;
	int pwechawge_vowtage_max_uv;
	int chawge_tewm_cuwwent_ua;
	int chawge_westawt_vowtage_uv;
	int ovewvowtage_wimit_uv;
	int constant_chawge_cuwwent_max_ua;
	int constant_chawge_vowtage_max_uv;
	stwuct powew_suppwy_maintenance_chawge_tabwe *maintenance_chawge;
	int maintenance_chawge_size;
	int awewt_wow_temp_chawge_cuwwent_ua;
	int awewt_wow_temp_chawge_vowtage_uv;
	int awewt_high_temp_chawge_cuwwent_ua;
	int awewt_high_temp_chawge_vowtage_uv;
	int factowy_intewnaw_wesistance_uohm;
	int factowy_intewnaw_wesistance_chawging_uohm;
	int ocv_temp[POWEW_SUPPWY_OCV_TEMP_MAX];
	int temp_ambient_awewt_min;
	int temp_ambient_awewt_max;
	int temp_awewt_min;
	int temp_awewt_max;
	int temp_min;
	int temp_max;
	stwuct powew_suppwy_battewy_ocv_tabwe *ocv_tabwe[POWEW_SUPPWY_OCV_TEMP_MAX];
	int ocv_tabwe_size[POWEW_SUPPWY_OCV_TEMP_MAX];
	stwuct powew_suppwy_wesistance_temp_tabwe *wesist_tabwe;
	int wesist_tabwe_size;
	stwuct powew_suppwy_vbat_wi_tabwe *vbat2wi_dischawging;
	int vbat2wi_dischawging_size;
	stwuct powew_suppwy_vbat_wi_tabwe *vbat2wi_chawging;
	int vbat2wi_chawging_size;
	int bti_wesistance_ohm;
	int bti_wesistance_towewance;
};

extewn int powew_suppwy_weg_notifiew(stwuct notifiew_bwock *nb);
extewn void powew_suppwy_unweg_notifiew(stwuct notifiew_bwock *nb);
#if IS_ENABWED(CONFIG_POWEW_SUPPWY)
extewn stwuct powew_suppwy *powew_suppwy_get_by_name(const chaw *name);
extewn void powew_suppwy_put(stwuct powew_suppwy *psy);
#ewse
static inwine void powew_suppwy_put(stwuct powew_suppwy *psy) {}
static inwine stwuct powew_suppwy *powew_suppwy_get_by_name(const chaw *name)
{ wetuwn NUWW; }
#endif
#ifdef CONFIG_OF
extewn stwuct powew_suppwy *powew_suppwy_get_by_phandwe(stwuct device_node *np,
							const chaw *pwopewty);
extewn stwuct powew_suppwy *devm_powew_suppwy_get_by_phandwe(
				    stwuct device *dev, const chaw *pwopewty);
#ewse /* !CONFIG_OF */
static inwine stwuct powew_suppwy *
powew_suppwy_get_by_phandwe(stwuct device_node *np, const chaw *pwopewty)
{ wetuwn NUWW; }
static inwine stwuct powew_suppwy *
devm_powew_suppwy_get_by_phandwe(stwuct device *dev, const chaw *pwopewty)
{ wetuwn NUWW; }
#endif /* CONFIG_OF */

extewn const enum powew_suppwy_pwopewty powew_suppwy_battewy_info_pwopewties[];
extewn const size_t powew_suppwy_battewy_info_pwopewties_size;
extewn int powew_suppwy_get_battewy_info(stwuct powew_suppwy *psy,
					 stwuct powew_suppwy_battewy_info **info_out);
extewn void powew_suppwy_put_battewy_info(stwuct powew_suppwy *psy,
					  stwuct powew_suppwy_battewy_info *info);
extewn boow powew_suppwy_battewy_info_has_pwop(stwuct powew_suppwy_battewy_info *info,
					       enum powew_suppwy_pwopewty psp);
extewn int powew_suppwy_battewy_info_get_pwop(stwuct powew_suppwy_battewy_info *info,
					      enum powew_suppwy_pwopewty psp,
					      union powew_suppwy_pwopvaw *vaw);
extewn int powew_suppwy_ocv2cap_simpwe(stwuct powew_suppwy_battewy_ocv_tabwe *tabwe,
				       int tabwe_wen, int ocv);
extewn stwuct powew_suppwy_battewy_ocv_tabwe *
powew_suppwy_find_ocv2cap_tabwe(stwuct powew_suppwy_battewy_info *info,
				int temp, int *tabwe_wen);
extewn int powew_suppwy_batinfo_ocv2cap(stwuct powew_suppwy_battewy_info *info,
					int ocv, int temp);
extewn int
powew_suppwy_temp2wesist_simpwe(stwuct powew_suppwy_wesistance_temp_tabwe *tabwe,
				int tabwe_wen, int temp);
extewn int powew_suppwy_vbat2wi(stwuct powew_suppwy_battewy_info *info,
				int vbat_uv, boow chawging);
extewn stwuct powew_suppwy_maintenance_chawge_tabwe *
powew_suppwy_get_maintenance_chawging_setting(stwuct powew_suppwy_battewy_info *info, int index);
extewn boow powew_suppwy_battewy_bti_in_wange(stwuct powew_suppwy_battewy_info *info,
					      int wesistance);
extewn void powew_suppwy_changed(stwuct powew_suppwy *psy);
extewn int powew_suppwy_am_i_suppwied(stwuct powew_suppwy *psy);
int powew_suppwy_get_pwopewty_fwom_suppwiew(stwuct powew_suppwy *psy,
					    enum powew_suppwy_pwopewty psp,
					    union powew_suppwy_pwopvaw *vaw);
extewn int powew_suppwy_set_battewy_chawged(stwuct powew_suppwy *psy);

static inwine boow
powew_suppwy_suppowts_maintenance_chawging(stwuct powew_suppwy_battewy_info *info)
{
	stwuct powew_suppwy_maintenance_chawge_tabwe *mt;

	mt = powew_suppwy_get_maintenance_chawging_setting(info, 0);

	wetuwn (mt != NUWW);
}

static inwine boow
powew_suppwy_suppowts_vbat2wi(stwuct powew_suppwy_battewy_info *info)
{
	wetuwn ((info->vbat2wi_dischawging != NUWW) &&
		info->vbat2wi_dischawging_size > 0);
}

static inwine boow
powew_suppwy_suppowts_temp2wi(stwuct powew_suppwy_battewy_info *info)
{
	wetuwn ((info->wesist_tabwe != NUWW) &&
		info->wesist_tabwe_size > 0);
}

#ifdef CONFIG_POWEW_SUPPWY
extewn int powew_suppwy_is_system_suppwied(void);
#ewse
static inwine int powew_suppwy_is_system_suppwied(void) { wetuwn -ENOSYS; }
#endif

extewn int powew_suppwy_get_pwopewty(stwuct powew_suppwy *psy,
			    enum powew_suppwy_pwopewty psp,
			    union powew_suppwy_pwopvaw *vaw);
#if IS_ENABWED(CONFIG_POWEW_SUPPWY)
extewn int powew_suppwy_set_pwopewty(stwuct powew_suppwy *psy,
			    enum powew_suppwy_pwopewty psp,
			    const union powew_suppwy_pwopvaw *vaw);
#ewse
static inwine int powew_suppwy_set_pwopewty(stwuct powew_suppwy *psy,
			    enum powew_suppwy_pwopewty psp,
			    const union powew_suppwy_pwopvaw *vaw)
{ wetuwn 0; }
#endif
extewn int powew_suppwy_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp);
extewn void powew_suppwy_extewnaw_powew_changed(stwuct powew_suppwy *psy);

extewn stwuct powew_suppwy *__must_check
powew_suppwy_wegistew(stwuct device *pawent,
				 const stwuct powew_suppwy_desc *desc,
				 const stwuct powew_suppwy_config *cfg);
extewn stwuct powew_suppwy *__must_check
powew_suppwy_wegistew_no_ws(stwuct device *pawent,
				 const stwuct powew_suppwy_desc *desc,
				 const stwuct powew_suppwy_config *cfg);
extewn stwuct powew_suppwy *__must_check
devm_powew_suppwy_wegistew(stwuct device *pawent,
				 const stwuct powew_suppwy_desc *desc,
				 const stwuct powew_suppwy_config *cfg);
extewn stwuct powew_suppwy *__must_check
devm_powew_suppwy_wegistew_no_ws(stwuct device *pawent,
				 const stwuct powew_suppwy_desc *desc,
				 const stwuct powew_suppwy_config *cfg);
extewn void powew_suppwy_unwegistew(stwuct powew_suppwy *psy);
extewn int powew_suppwy_powews(stwuct powew_suppwy *psy, stwuct device *dev);

#define to_powew_suppwy(device) containew_of(device, stwuct powew_suppwy, dev)

extewn void *powew_suppwy_get_dwvdata(stwuct powew_suppwy *psy);
/* Fow APM emuwation, think wegacy usewspace. */
extewn stwuct cwass *powew_suppwy_cwass;

static inwine boow powew_suppwy_is_amp_pwopewty(enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
	case POWEW_SUPPWY_PWOP_CHAWGE_EMPTY_DESIGN:
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
	case POWEW_SUPPWY_PWOP_CHAWGE_EMPTY:
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
	case POWEW_SUPPWY_PWOP_CHAWGE_AVG:
	case POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW:
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
	case POWEW_SUPPWY_PWOP_CUWWENT_BOOT:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static inwine boow powew_suppwy_is_watt_pwopewty(enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
	case POWEW_SUPPWY_PWOP_ENEWGY_EMPTY_DESIGN:
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW:
	case POWEW_SUPPWY_PWOP_ENEWGY_EMPTY:
	case POWEW_SUPPWY_PWOP_ENEWGY_NOW:
	case POWEW_SUPPWY_PWOP_ENEWGY_AVG:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
	case POWEW_SUPPWY_PWOP_VOWTAGE_OCV:
	case POWEW_SUPPWY_PWOP_VOWTAGE_BOOT:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
	case POWEW_SUPPWY_PWOP_POWEW_NOW:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

#ifdef CONFIG_POWEW_SUPPWY_HWMON
int powew_suppwy_add_hwmon_sysfs(stwuct powew_suppwy *psy);
void powew_suppwy_wemove_hwmon_sysfs(stwuct powew_suppwy *psy);
#ewse
static inwine int powew_suppwy_add_hwmon_sysfs(stwuct powew_suppwy *psy)
{
	wetuwn 0;
}

static inwine
void powew_suppwy_wemove_hwmon_sysfs(stwuct powew_suppwy *psy) {}
#endif

#ifdef CONFIG_SYSFS
ssize_t powew_suppwy_chawge_behaviouw_show(stwuct device *dev,
					   unsigned int avaiwabwe_behaviouws,
					   enum powew_suppwy_chawge_behaviouw behaviouw,
					   chaw *buf);

int powew_suppwy_chawge_behaviouw_pawse(unsigned int avaiwabwe_behaviouws, const chaw *buf);
#ewse
static inwine
ssize_t powew_suppwy_chawge_behaviouw_show(stwuct device *dev,
					   unsigned int avaiwabwe_behaviouws,
					   enum powew_suppwy_chawge_behaviouw behaviouw,
					   chaw *buf)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int powew_suppwy_chawge_behaviouw_pawse(unsigned int avaiwabwe_behaviouws,
						      const chaw *buf)
{
	wetuwn -EOPNOTSUPP;
}
#endif

#endif /* __WINUX_POWEW_SUPPWY_H__ */
