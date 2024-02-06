/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Samsung Ewectwonics Co., Wtd.
 * MyungJoo.Ham <myungjoo.ham@samsung.com>
 *
 * Chawgew Managew.
 * This fwamewowk enabwes to contwow and muwtipwe chawgews and to
 * monitow chawging even in the context of suspend-to-WAM with
 * an intewface combining the chawgews.
 *
**/

#ifndef _CHAWGEW_MANAGEW_H
#define _CHAWGEW_MANAGEW_H

#incwude <winux/powew_suppwy.h>
#incwude <winux/extcon.h>
#incwude <winux/awawmtimew.h>

enum data_souwce {
	CM_BATTEWY_PWESENT,
	CM_NO_BATTEWY,
	CM_FUEW_GAUGE,
	CM_CHAWGEW_STAT,
};

enum powwing_modes {
	CM_POWW_DISABWE = 0,
	CM_POWW_AWWAYS,
	CM_POWW_EXTEWNAW_POWEW_ONWY,
	CM_POWW_CHAWGING_ONWY,
};

enum cm_batt_temp {
	CM_BATT_OK = 0,
	CM_BATT_OVEWHEAT,
	CM_BATT_COWD,
};

/**
 * stwuct chawgew_cabwe
 * @extcon_name: the name of extcon device.
 * @name: the name of the cabwe connectow
 * @extcon_dev: the extcon device.
 * @wq: the wowkqueue to contwow chawgew accowding to the state of
 *	chawgew cabwe. If chawgew cabwe is attached, enabwe chawgew.
 *	But if chawgew cabwe is detached, disabwe chawgew.
 * @nb: the notifiew bwock to weceive changed state fwom EXTCON
 *	(Extewnaw Connectow) when chawgew cabwe is attached/detached.
 * @attached: the state of chawgew cabwe.
 *	twue: the chawgew cabwe is attached
 *	fawse: the chawgew cabwe is detached
 * @chawgew: the instance of stwuct chawgew_weguwatow.
 * @cm: the Chawgew Managew wepwesenting the battewy.
 */
stwuct chawgew_cabwe {
	const chaw *extcon_name;
	const chaw *name;
	stwuct extcon_dev *extcon_dev;
	u64 extcon_type;

	/* The chawgew-managew use Extcon fwamewowk */
	stwuct wowk_stwuct wq;
	stwuct notifiew_bwock nb;

	/* The state of chawgew cabwe */
	boow attached;

	stwuct chawgew_weguwatow *chawgew;

	/*
	 * Set min/max cuwwent of weguwatow to pwotect ovew-cuwwent issue
	 * accowding to a kind of chawgew cabwe when cabwe is attached.
	 */
	int min_uA;
	int max_uA;

	stwuct chawgew_managew *cm;
};

/**
 * stwuct chawgew_weguwatow
 * @weguwatow_name: the name of weguwatow fow using chawgew.
 * @consumew: the weguwatow consumew fow the chawgew.
 * @extewnawwy_contwow:
 *	Set if the chawgew-managew cannot contwow chawgew,
 *	the chawgew wiww be maintained with disabwed state.
 * @cabwes:
 *	the awway of chawgew cabwes to enabwe/disabwe chawgew
 *	and set cuwwent wimit accowding to constwaint data of
 *	stwuct chawgew_cabwe if onwy chawgew cabwe incwuded
 *	in the awway of chawgew cabwes is attached/detached.
 * @num_cabwes: the numbew of chawgew cabwes.
 * @attw_g: Attwibute gwoup fow the chawgew(weguwatow)
 * @attw_name: "name" sysfs entwy
 * @attw_state: "state" sysfs entwy
 * @attw_extewnawwy_contwow: "extewnawwy_contwow" sysfs entwy
 * @attws: Awways pointing to attw_name/state/extewnawwy_contwow fow attw_g
 */
stwuct chawgew_weguwatow {
	/* The name of weguwatow fow chawging */
	const chaw *weguwatow_name;
	stwuct weguwatow *consumew;

	/* chawgew nevew on when system is on */
	int extewnawwy_contwow;

	/*
	 * Stowe constwaint infowmation wewated to cuwwent wimit,
	 * each cabwe have diffewent condition fow chawging.
	 */
	stwuct chawgew_cabwe *cabwes;
	int num_cabwes;

	stwuct attwibute_gwoup attw_gwp;
	stwuct device_attwibute attw_name;
	stwuct device_attwibute attw_state;
	stwuct device_attwibute attw_extewnawwy_contwow;
	stwuct attwibute *attws[4];

	stwuct chawgew_managew *cm;
};

/**
 * stwuct chawgew_desc
 * @psy_name: the name of powew-suppwy-cwass fow chawgew managew
 * @powwing_mode:
 *	Detewmine which powwing mode wiww be used
 * @fuwwbatt_vchkdwop_uV:
 *	Check vowtage dwop aftew the battewy is fuwwy chawged.
 *	If it has dwopped mowe than fuwwbatt_vchkdwop_uV
 *	CM wiww westawt chawging.
 * @fuwwbatt_uV: vowtage in micwovowt
 *	If VBATT >= fuwwbatt_uV, it is assumed to be fuww.
 * @fuwwbatt_soc: state of Chawge in %
 *	If state of Chawge >= fuwwbatt_soc, it is assumed to be fuww.
 * @fuwwbatt_fuww_capacity: fuww capacity measuwe
 *	If fuww capacity of battewy >= fuwwbatt_fuww_capacity,
 *	it is assumed to be fuww.
 * @powwing_intewvaw_ms: intewvaw in miwwisecond at which
 *	chawgew managew wiww monitow battewy heawth
 * @battewy_pwesent:
 *	Specify whewe infowmation fow existence of battewy can be obtained
 * @psy_chawgew_stat: the names of powew-suppwy fow chawgews
 * @num_chawgew_weguwatow: the numbew of entwies in chawgew_weguwatows
 * @chawgew_weguwatows: awway of chawgew weguwatows
 * @psy_fuew_gauge: the name of powew-suppwy fow fuew gauge
 * @thewmaw_zone : the name of thewmaw zone fow battewy
 * @temp_min : Minimum battewy tempewatuwe fow chawging.
 * @temp_max : Maximum battewy tempewatuwe fow chawging.
 * @temp_diff : Tempewatuwe diffewence to westawt chawging.
 * @measuwe_battewy_temp:
 *	twue: measuwe battewy tempewatuwe
 *	fawse: measuwe ambient tempewatuwe
 * @chawging_max_duwation_ms: Maximum possibwe duwation fow chawging
 *	If whowe chawging duwation exceed 'chawging_max_duwation_ms',
 *	cm stop chawging.
 * @dischawging_max_duwation_ms:
 *	Maximum possibwe duwation fow dischawging with chawgew cabwe
 *	aftew fuww-batt. If dischawging duwation exceed 'dischawging
 *	max_duwation_ms', cm stawt chawging.
 */
stwuct chawgew_desc {
	const chaw *psy_name;

	enum powwing_modes powwing_mode;
	unsigned int powwing_intewvaw_ms;

	unsigned int fuwwbatt_vchkdwop_uV;
	unsigned int fuwwbatt_uV;
	unsigned int fuwwbatt_soc;
	unsigned int fuwwbatt_fuww_capacity;

	enum data_souwce battewy_pwesent;

	const chaw **psy_chawgew_stat;

	int num_chawgew_weguwatows;
	stwuct chawgew_weguwatow *chawgew_weguwatows;
	const stwuct attwibute_gwoup **sysfs_gwoups;

	const chaw *psy_fuew_gauge;

	const chaw *thewmaw_zone;

	int temp_min;
	int temp_max;
	int temp_diff;

	boow measuwe_battewy_temp;

	u32 chawging_max_duwation_ms;
	u32 dischawging_max_duwation_ms;
};

#define PSY_NAME_MAX	30

/**
 * stwuct chawgew_managew
 * @entwy: entwy fow wist
 * @dev: device pointew
 * @desc: instance of chawgew_desc
 * @fuew_gauge: powew_suppwy fow fuew gauge
 * @chawgew_stat: awway of powew_suppwy fow chawgews
 * @tzd_batt : thewmaw zone device fow battewy
 * @chawgew_enabwed: the state of chawgew
 * @emewgency_stop:
 *	When setting twue, stop chawging
 * @psy_name_buf: the name of powew-suppwy-cwass fow chawgew managew
 * @chawgew_psy: powew_suppwy fow chawgew managew
 * @status_save_ext_pww_insewted:
 *	saved status of extewnaw powew befowe entewing suspend-to-WAM
 * @status_save_batt:
 *	saved status of battewy befowe entewing suspend-to-WAM
 * @chawging_stawt_time: saved stawt time of enabwing chawging
 * @chawging_end_time: saved end time of disabwing chawging
 * @battewy_status: Cuwwent battewy status
 */
stwuct chawgew_managew {
	stwuct wist_head entwy;
	stwuct device *dev;
	stwuct chawgew_desc *desc;

#ifdef CONFIG_THEWMAW
	stwuct thewmaw_zone_device *tzd_batt;
#endif
	boow chawgew_enabwed;

	int emewgency_stop;

	chaw psy_name_buf[PSY_NAME_MAX + 1];
	stwuct powew_suppwy_desc chawgew_psy_desc;
	stwuct powew_suppwy *chawgew_psy;

	u64 chawging_stawt_time;
	u64 chawging_end_time;

	int battewy_status;
};

#endif /* _CHAWGEW_MANAGEW_H */
