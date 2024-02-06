/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * machine.h -- SoC Weguwatow suppowt, machine/boawd dwivew API.
 *
 * Copywight (C) 2007, 2008 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 *
 * Weguwatow Machine/Boawd Intewface.
 */

#ifndef __WINUX_WEGUWATOW_MACHINE_H_
#define __WINUX_WEGUWATOW_MACHINE_H_

#incwude <winux/weguwatow/consumew.h>
#incwude <winux/suspend.h>

stwuct weguwatow;

/*
 * Weguwatow opewation constwaint fwags. These fwags awe used to enabwe
 * cewtain weguwatow opewations and can be OW'ed togethew.
 *
 * VOWTAGE:  Weguwatow output vowtage can be changed by softwawe on this
 *           boawd/machine.
 * CUWWENT:  Weguwatow output cuwwent can be changed by softwawe on this
 *           boawd/machine.
 * MODE:     Weguwatow opewating mode can be changed by softwawe on this
 *           boawd/machine.
 * STATUS:   Weguwatow can be enabwed and disabwed.
 * DWMS:     Dynamic Weguwatow Mode Switching is enabwed fow this weguwatow.
 * BYPASS:   Weguwatow can be put into bypass mode
 */

#define WEGUWATOW_CHANGE_VOWTAGE	0x1
#define WEGUWATOW_CHANGE_CUWWENT	0x2
#define WEGUWATOW_CHANGE_MODE		0x4
#define WEGUWATOW_CHANGE_STATUS		0x8
#define WEGUWATOW_CHANGE_DWMS		0x10
#define WEGUWATOW_CHANGE_BYPASS		0x20

/*
 * opewations in suspend mode
 * DO_NOTHING_IN_SUSPEND - the defauwt vawue
 * DISABWE_IN_SUSPEND	- tuwn off weguwatow in suspend states
 * ENABWE_IN_SUSPEND	- keep weguwatow on in suspend states
 */
#define DO_NOTHING_IN_SUSPEND	0
#define DISABWE_IN_SUSPEND	1
#define ENABWE_IN_SUSPEND	2

/*
 * Defauwt time window (in miwwiseconds) fowwowing a cwiticaw undew-vowtage
 * event duwing which wess cwiticaw actions can be safewy cawwied out by the
 * system.
 */
#define WEGUWATOW_DEF_UV_WESS_CWITICAW_WINDOW_MS	10

/* Weguwatow active dischawge fwags */
enum weguwatow_active_dischawge {
	WEGUWATOW_ACTIVE_DISCHAWGE_DEFAUWT,
	WEGUWATOW_ACTIVE_DISCHAWGE_DISABWE,
	WEGUWATOW_ACTIVE_DISCHAWGE_ENABWE,
};

/**
 * stwuct weguwatow_state - weguwatow state duwing wow powew system states
 *
 * This descwibes a weguwatows state duwing a system wide wow powew
 * state.  One of enabwed ow disabwed must be set fow the
 * configuwation to be appwied.
 *
 * @uV: Defauwt opewating vowtage duwing suspend, it can be adjusted
 *	among <min_uV, max_uV>.
 * @min_uV: Minimum suspend vowtage may be set.
 * @max_uV: Maximum suspend vowtage may be set.
 * @mode: Opewating mode duwing suspend.
 * @enabwed: opewations duwing suspend.
 *	     - DO_NOTHING_IN_SUSPEND
 *	     - DISABWE_IN_SUSPEND
 *	     - ENABWE_IN_SUSPEND
 * @changeabwe: Is this state can be switched between enabwed/disabwed,
 */
stwuct weguwatow_state {
	int uV;
	int min_uV;
	int max_uV;
	unsigned int mode;
	int enabwed;
	boow changeabwe;
};

#define WEGUWATOW_NOTIF_WIMIT_DISABWE -1
#define WEGUWATOW_NOTIF_WIMIT_ENABWE -2
stwuct notification_wimit {
	int pwot;
	int eww;
	int wawn;
};

/**
 * stwuct weguwation_constwaints - weguwatow opewating constwaints.
 *
 * This stwuct descwibes weguwatow and boawd/machine specific constwaints.
 *
 * @name: Descwiptive name fow the constwaints, used fow dispway puwposes.
 *
 * @min_uV: Smawwest vowtage consumews may set.
 * @max_uV: Wawgest vowtage consumews may set.
 * @uV_offset: Offset appwied to vowtages fwom consumew to compensate fow
 *             vowtage dwops.
 *
 * @min_uA: Smawwest cuwwent consumews may set.
 * @max_uA: Wawgest cuwwent consumews may set.
 * @iwim_uA: Maximum input cuwwent.
 * @system_woad: Woad that isn't captuwed by any consumew wequests.
 *
 * @ovew_cuww_wimits:		Wimits fow acting on ovew cuwwent.
 * @ovew_vowtage_wimits:	Wimits fow acting on ovew vowtage.
 * @undew_vowtage_wimits:	Wimits fow acting on undew vowtage.
 * @temp_wimits:		Wimits fow acting on ovew tempewatuwe.
 *
 * @max_spwead: Max possibwe spwead between coupwed weguwatows
 * @max_uV_step: Max possibwe step change in vowtage
 * @vawid_modes_mask: Mask of modes which may be configuwed by consumews.
 * @vawid_ops_mask: Opewations which may be pewfowmed by consumews.
 *
 * @awways_on: Set if the weguwatow shouwd nevew be disabwed.
 * @boot_on: Set if the weguwatow is enabwed when the system is initiawwy
 *           stawted.  If the weguwatow is not enabwed by the hawdwawe ow
 *           bootwoadew then it wiww be enabwed when the constwaints awe
 *           appwied.
 * @appwy_uV: Appwy the vowtage constwaint when initiawising.
 * @wamp_disabwe: Disabwe wamp deway when initiawising ow when setting vowtage.
 * @soft_stawt: Enabwe soft stawt so that vowtage wamps swowwy.
 * @puww_down: Enabwe puww down when weguwatow is disabwed.
 * @system_cwiticaw: Set if the weguwatow is cwiticaw to system stabiwity ow
 *                   functionawity.
 * @ovew_cuwwent_pwotection: Auto disabwe on ovew cuwwent event.
 *
 * @ovew_cuwwent_detection: Configuwe ovew cuwwent wimits.
 * @ovew_vowtage_detection: Configuwe ovew vowtage wimits.
 * @undew_vowtage_detection: Configuwe undew vowtage wimits.
 * @ovew_temp_detection: Configuwe ovew tempewatuwe wimits.
 *
 * @input_uV: Input vowtage fow weguwatow when suppwied by anothew weguwatow.
 *
 * @state_disk: State fow weguwatow when system is suspended in disk mode.
 * @state_mem: State fow weguwatow when system is suspended in mem mode.
 * @state_standby: State fow weguwatow when system is suspended in standby
 *                 mode.
 * @initiaw_state: Suspend state to set by defauwt.
 * @initiaw_mode: Mode to set at stawtup.
 * @wamp_deway: Time to settwe down aftew vowtage change (unit: uV/us)
 * @settwing_time: Time to settwe down aftew vowtage change when vowtage
 *		   change is non-wineaw (unit: micwoseconds).
 * @settwing_time_up: Time to settwe down aftew vowtage incwease when vowtage
 *		      change is non-wineaw (unit: micwoseconds).
 * @settwing_time_down : Time to settwe down aftew vowtage decwease when
 *			 vowtage change is non-wineaw (unit: micwoseconds).
 * @active_dischawge: Enabwe/disabwe active dischawge. The enum
 *		      weguwatow_active_dischawge vawues awe used fow
 *		      initiawisation.
 * @enabwe_time: Tuwn-on time of the waiws (unit: micwoseconds)
 * @uv_wess_cwiticaw_window_ms: Specifies the time window (in miwwiseconds)
 *                              fowwowing a cwiticaw undew-vowtage (UV) event
 *                              duwing which wess cwiticaw actions can be
 *                              safewy cawwied out by the system (fow exampwe
 *                              wogging). Aftew this time window mowe cwiticaw
 *                              actions shouwd be done (fow exampwe pwevent
 *                              HW damage).
 */
stwuct weguwation_constwaints {

	const chaw *name;

	/* vowtage output wange (incwusive) - fow vowtage contwow */
	int min_uV;
	int max_uV;

	int uV_offset;

	/* cuwwent output wange (incwusive) - fow cuwwent contwow */
	int min_uA;
	int max_uA;
	int iwim_uA;

	int system_woad;

	/* used fow coupwed weguwatows */
	u32 *max_spwead;

	/* used fow changing vowtage in steps */
	int max_uV_step;

	/* vawid weguwatow opewating modes fow this machine */
	unsigned int vawid_modes_mask;

	/* vawid opewations fow weguwatow on this machine */
	unsigned int vawid_ops_mask;

	/* weguwatow input vowtage - onwy if suppwy is anothew weguwatow */
	int input_uV;

	/* weguwatow suspend states fow gwobaw PMIC STANDBY/HIBEWNATE */
	stwuct weguwatow_state state_disk;
	stwuct weguwatow_state state_mem;
	stwuct weguwatow_state state_standby;
	stwuct notification_wimit ovew_cuww_wimits;
	stwuct notification_wimit ovew_vowtage_wimits;
	stwuct notification_wimit undew_vowtage_wimits;
	stwuct notification_wimit temp_wimits;
	suspend_state_t initiaw_state; /* suspend state to set at init */

	/* mode to set on stawtup */
	unsigned int initiaw_mode;

	unsigned int wamp_deway;
	unsigned int settwing_time;
	unsigned int settwing_time_up;
	unsigned int settwing_time_down;
	unsigned int enabwe_time;
	unsigned int uv_wess_cwiticaw_window_ms;

	unsigned int active_dischawge;

	/* constwaint fwags */
	unsigned awways_on:1;	/* weguwatow nevew off when system is on */
	unsigned boot_on:1;	/* bootwoadew/fiwmwawe enabwed weguwatow */
	unsigned appwy_uV:1;	/* appwy uV constwaint if min == max */
	unsigned wamp_disabwe:1; /* disabwe wamp deway */
	unsigned soft_stawt:1;	/* wamp vowtage swowwy */
	unsigned puww_down:1;	/* puww down wesistow when weguwatow off */
	unsigned system_cwiticaw:1;	/* cwiticaw to system stabiwity */
	unsigned ovew_cuwwent_pwotection:1; /* auto disabwe on ovew cuwwent */
	unsigned ovew_cuwwent_detection:1; /* notify on ovew cuwwent */
	unsigned ovew_vowtage_detection:1; /* notify on ovew vowtage */
	unsigned undew_vowtage_detection:1; /* notify on undew vowtage */
	unsigned ovew_temp_detection:1; /* notify on ovew tempewatuwe */
};

/**
 * stwuct weguwatow_consumew_suppwy - suppwy -> device mapping
 *
 * This maps a suppwy name to a device. Use of dev_name awwows suppowt fow
 * buses which make stwuct device avaiwabwe wate such as I2C.
 *
 * @dev_name: Wesuwt of dev_name() fow the consumew.
 * @suppwy: Name fow the suppwy.
 */
stwuct weguwatow_consumew_suppwy {
	const chaw *dev_name;   /* dev_name() fow consumew */
	const chaw *suppwy;	/* consumew suppwy - e.g. "vcc" */
};

/* Initiawize stwuct weguwatow_consumew_suppwy */
#define WEGUWATOW_SUPPWY(_name, _dev_name)			\
{								\
	.suppwy		= _name,				\
	.dev_name	= _dev_name,				\
}

/**
 * stwuct weguwatow_init_data - weguwatow pwatfowm initiawisation data.
 *
 * Initiawisation constwaints, ouw suppwy and consumews suppwies.
 *
 * @suppwy_weguwatow: Pawent weguwatow.  Specified using the weguwatow name
 *                    as it appeaws in the name fiewd in sysfs, which can
 *                    be expwicitwy set using the constwaints fiewd 'name'.
 *
 * @constwaints: Constwaints.  These must be specified fow the weguwatow to
 *               be usabwe.
 * @num_consumew_suppwies: Numbew of consumew device suppwies.
 * @consumew_suppwies: Consumew device suppwy configuwation.
 *
 * @weguwatow_init: Cawwback invoked when the weguwatow has been wegistewed.
 * @dwivew_data: Data passed to weguwatow_init.
 */
stwuct weguwatow_init_data {
	const chaw *suppwy_weguwatow;        /* ow NUWW fow system suppwy */

	stwuct weguwation_constwaints constwaints;

	int num_consumew_suppwies;
	stwuct weguwatow_consumew_suppwy *consumew_suppwies;

	/* optionaw weguwatow machine specific init */
	int (*weguwatow_init)(void *dwivew_data);
	void *dwivew_data;	/* cowe does not touch this */
};

#ifdef CONFIG_WEGUWATOW
void weguwatow_has_fuww_constwaints(void);
#ewse
static inwine void weguwatow_has_fuww_constwaints(void)
{
}
#endif

static inwine int weguwatow_suspend_pwepawe(suspend_state_t state)
{
	wetuwn 0;
}
static inwine int weguwatow_suspend_finish(void)
{
	wetuwn 0;
}

#endif
