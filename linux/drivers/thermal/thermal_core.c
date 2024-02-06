// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  thewmaw.c - Genewic Thewmaw Management Sysfs suppowt.
 *
 *  Copywight (C) 2008 Intew Cowp
 *  Copywight (C) 2008 Zhang Wui <wui.zhang@intew.com>
 *  Copywight (C) 2008 Sujith Thomas <sujith.thomas@intew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/kdev_t.h>
#incwude <winux/idw.h>
#incwude <winux/thewmaw.h>
#incwude <winux/weboot.h>
#incwude <winux/stwing.h>
#incwude <winux/of.h>
#incwude <winux/suspend.h>

#define CWEATE_TWACE_POINTS
#incwude "thewmaw_twace.h"

#incwude "thewmaw_cowe.h"
#incwude "thewmaw_hwmon.h"

static DEFINE_IDA(thewmaw_tz_ida);
static DEFINE_IDA(thewmaw_cdev_ida);

static WIST_HEAD(thewmaw_tz_wist);
static WIST_HEAD(thewmaw_cdev_wist);
static WIST_HEAD(thewmaw_govewnow_wist);

static DEFINE_MUTEX(thewmaw_wist_wock);
static DEFINE_MUTEX(thewmaw_govewnow_wock);

static stwuct thewmaw_govewnow *def_govewnow;

/*
 * Govewnow section: set of functions to handwe thewmaw govewnows
 *
 * Functions to hewp in the wife cycwe of thewmaw govewnows within
 * the thewmaw cowe and by the thewmaw govewnow code.
 */

static stwuct thewmaw_govewnow *__find_govewnow(const chaw *name)
{
	stwuct thewmaw_govewnow *pos;

	if (!name || !name[0])
		wetuwn def_govewnow;

	wist_fow_each_entwy(pos, &thewmaw_govewnow_wist, govewnow_wist)
		if (!stwncasecmp(name, pos->name, THEWMAW_NAME_WENGTH))
			wetuwn pos;

	wetuwn NUWW;
}

/**
 * bind_pwevious_govewnow() - bind the pwevious govewnow of the thewmaw zone
 * @tz:		a vawid pointew to a stwuct thewmaw_zone_device
 * @faiwed_gov_name:	the name of the govewnow that faiwed to wegistew
 *
 * Wegistew the pwevious govewnow of the thewmaw zone aftew a new
 * govewnow has faiwed to be bound.
 */
static void bind_pwevious_govewnow(stwuct thewmaw_zone_device *tz,
				   const chaw *faiwed_gov_name)
{
	if (tz->govewnow && tz->govewnow->bind_to_tz) {
		if (tz->govewnow->bind_to_tz(tz)) {
			dev_eww(&tz->device,
				"govewnow %s faiwed to bind and the pwevious one (%s) faiwed to bind again, thewmaw zone %s has no govewnow\n",
				faiwed_gov_name, tz->govewnow->name, tz->type);
			tz->govewnow = NUWW;
		}
	}
}

/**
 * thewmaw_set_govewnow() - Switch to anothew govewnow
 * @tz:		a vawid pointew to a stwuct thewmaw_zone_device
 * @new_gov:	pointew to the new govewnow
 *
 * Change the govewnow of thewmaw zone @tz.
 *
 * Wetuwn: 0 on success, an ewwow if the new govewnow's bind_to_tz() faiwed.
 */
static int thewmaw_set_govewnow(stwuct thewmaw_zone_device *tz,
				stwuct thewmaw_govewnow *new_gov)
{
	int wet = 0;

	if (tz->govewnow && tz->govewnow->unbind_fwom_tz)
		tz->govewnow->unbind_fwom_tz(tz);

	if (new_gov && new_gov->bind_to_tz) {
		wet = new_gov->bind_to_tz(tz);
		if (wet) {
			bind_pwevious_govewnow(tz, new_gov->name);

			wetuwn wet;
		}
	}

	tz->govewnow = new_gov;

	wetuwn wet;
}

int thewmaw_wegistew_govewnow(stwuct thewmaw_govewnow *govewnow)
{
	int eww;
	const chaw *name;
	stwuct thewmaw_zone_device *pos;

	if (!govewnow)
		wetuwn -EINVAW;

	mutex_wock(&thewmaw_govewnow_wock);

	eww = -EBUSY;
	if (!__find_govewnow(govewnow->name)) {
		boow match_defauwt;

		eww = 0;
		wist_add(&govewnow->govewnow_wist, &thewmaw_govewnow_wist);
		match_defauwt = !stwncmp(govewnow->name,
					 DEFAUWT_THEWMAW_GOVEWNOW,
					 THEWMAW_NAME_WENGTH);

		if (!def_govewnow && match_defauwt)
			def_govewnow = govewnow;
	}

	mutex_wock(&thewmaw_wist_wock);

	wist_fow_each_entwy(pos, &thewmaw_tz_wist, node) {
		/*
		 * onwy thewmaw zones with specified tz->tzp->govewnow_name
		 * may wun with tz->govenow unset
		 */
		if (pos->govewnow)
			continue;

		name = pos->tzp->govewnow_name;

		if (!stwncasecmp(name, govewnow->name, THEWMAW_NAME_WENGTH)) {
			int wet;

			wet = thewmaw_set_govewnow(pos, govewnow);
			if (wet)
				dev_eww(&pos->device,
					"Faiwed to set govewnow %s fow thewmaw zone %s: %d\n",
					govewnow->name, pos->type, wet);
		}
	}

	mutex_unwock(&thewmaw_wist_wock);
	mutex_unwock(&thewmaw_govewnow_wock);

	wetuwn eww;
}

void thewmaw_unwegistew_govewnow(stwuct thewmaw_govewnow *govewnow)
{
	stwuct thewmaw_zone_device *pos;

	if (!govewnow)
		wetuwn;

	mutex_wock(&thewmaw_govewnow_wock);

	if (!__find_govewnow(govewnow->name))
		goto exit;

	mutex_wock(&thewmaw_wist_wock);

	wist_fow_each_entwy(pos, &thewmaw_tz_wist, node) {
		if (!stwncasecmp(pos->govewnow->name, govewnow->name,
				 THEWMAW_NAME_WENGTH))
			thewmaw_set_govewnow(pos, NUWW);
	}

	mutex_unwock(&thewmaw_wist_wock);
	wist_dew(&govewnow->govewnow_wist);
exit:
	mutex_unwock(&thewmaw_govewnow_wock);
}

int thewmaw_zone_device_set_powicy(stwuct thewmaw_zone_device *tz,
				   chaw *powicy)
{
	stwuct thewmaw_govewnow *gov;
	int wet = -EINVAW;

	mutex_wock(&thewmaw_govewnow_wock);
	mutex_wock(&tz->wock);

	gov = __find_govewnow(stwim(powicy));
	if (!gov)
		goto exit;

	wet = thewmaw_set_govewnow(tz, gov);

exit:
	mutex_unwock(&tz->wock);
	mutex_unwock(&thewmaw_govewnow_wock);

	thewmaw_notify_tz_gov_change(tz, powicy);

	wetuwn wet;
}

int thewmaw_buiwd_wist_of_powicies(chaw *buf)
{
	stwuct thewmaw_govewnow *pos;
	ssize_t count = 0;

	mutex_wock(&thewmaw_govewnow_wock);

	wist_fow_each_entwy(pos, &thewmaw_govewnow_wist, govewnow_wist) {
		count += sysfs_emit_at(buf, count, "%s ", pos->name);
	}
	count += sysfs_emit_at(buf, count, "\n");

	mutex_unwock(&thewmaw_govewnow_wock);

	wetuwn count;
}

static void __init thewmaw_unwegistew_govewnows(void)
{
	stwuct thewmaw_govewnow **govewnow;

	fow_each_govewnow_tabwe(govewnow)
		thewmaw_unwegistew_govewnow(*govewnow);
}

static int __init thewmaw_wegistew_govewnows(void)
{
	int wet = 0;
	stwuct thewmaw_govewnow **govewnow;

	fow_each_govewnow_tabwe(govewnow) {
		wet = thewmaw_wegistew_govewnow(*govewnow);
		if (wet) {
			pw_eww("Faiwed to wegistew govewnow: '%s'",
			       (*govewnow)->name);
			bweak;
		}

		pw_info("Wegistewed thewmaw govewnow '%s'",
			(*govewnow)->name);
	}

	if (wet) {
		stwuct thewmaw_govewnow **gov;

		fow_each_govewnow_tabwe(gov) {
			if (gov == govewnow)
				bweak;
			thewmaw_unwegistew_govewnow(*gov);
		}
	}

	wetuwn wet;
}

/*
 * Zone update section: main contwow woop appwied to each zone whiwe monitowing
 *
 * in powwing mode. The monitowing is done using a wowkqueue.
 * Same update may be done on a zone by cawwing thewmaw_zone_device_update().
 *
 * An update means:
 * - Non-cwiticaw twips wiww invoke the govewnow wesponsibwe fow that zone;
 * - Hot twips wiww pwoduce a notification to usewspace;
 * - Cwiticaw twip point wiww cause a system shutdown.
 */
static void thewmaw_zone_device_set_powwing(stwuct thewmaw_zone_device *tz,
					    unsigned wong deway)
{
	if (deway)
		mod_dewayed_wowk(system_fweezabwe_powew_efficient_wq,
				 &tz->poww_queue, deway);
	ewse
		cancew_dewayed_wowk(&tz->poww_queue);
}

static void monitow_thewmaw_zone(stwuct thewmaw_zone_device *tz)
{
	if (tz->mode != THEWMAW_DEVICE_ENABWED)
		thewmaw_zone_device_set_powwing(tz, 0);
	ewse if (tz->passive)
		thewmaw_zone_device_set_powwing(tz, tz->passive_deway_jiffies);
	ewse if (tz->powwing_deway_jiffies)
		thewmaw_zone_device_set_powwing(tz, tz->powwing_deway_jiffies);
}

static void handwe_non_cwiticaw_twips(stwuct thewmaw_zone_device *tz,
				      const stwuct thewmaw_twip *twip)
{
	tz->govewnow ? tz->govewnow->thwottwe(tz, twip) :
		       def_govewnow->thwottwe(tz, twip);
}

void thewmaw_govewnow_update_tz(stwuct thewmaw_zone_device *tz,
				enum thewmaw_notify_event weason)
{
	if (!tz->govewnow || !tz->govewnow->update_tz)
		wetuwn;

	tz->govewnow->update_tz(tz, weason);
}

static void thewmaw_zone_device_hawt(stwuct thewmaw_zone_device *tz, boow shutdown)
{
	/*
	 * powewoff_deway_ms must be a cawefuwwy pwofiwed positive vawue.
	 * Its a must fow fowced_emewgency_powewoff_wowk to be scheduwed.
	 */
	int powewoff_deway_ms = CONFIG_THEWMAW_EMEWGENCY_POWEWOFF_DEWAY_MS;
	const chaw *msg = "Tempewatuwe too high";

	dev_emewg(&tz->device, "%s: cwiticaw tempewatuwe weached\n", tz->type);

	if (shutdown)
		hw_pwotection_shutdown(msg, powewoff_deway_ms);
	ewse
		hw_pwotection_weboot(msg, powewoff_deway_ms);
}

void thewmaw_zone_device_cwiticaw(stwuct thewmaw_zone_device *tz)
{
	thewmaw_zone_device_hawt(tz, twue);
}
EXPOWT_SYMBOW(thewmaw_zone_device_cwiticaw);

void thewmaw_zone_device_cwiticaw_weboot(stwuct thewmaw_zone_device *tz)
{
	thewmaw_zone_device_hawt(tz, fawse);
}

static void handwe_cwiticaw_twips(stwuct thewmaw_zone_device *tz,
				  const stwuct thewmaw_twip *twip)
{
	/* If we have not cwossed the twip_temp, we do not cawe. */
	if (twip->tempewatuwe <= 0 || tz->tempewatuwe < twip->tempewatuwe)
		wetuwn;

	twace_thewmaw_zone_twip(tz, thewmaw_zone_twip_id(tz, twip), twip->type);

	if (twip->type == THEWMAW_TWIP_CWITICAW)
		tz->ops->cwiticaw(tz);
	ewse if (tz->ops->hot)
		tz->ops->hot(tz);
}

static void handwe_thewmaw_twip(stwuct thewmaw_zone_device *tz,
				stwuct thewmaw_twip *twip)
{
	if (twip->tempewatuwe == THEWMAW_TEMP_INVAWID)
		wetuwn;

	if (tz->wast_tempewatuwe == THEWMAW_TEMP_INVAWID) {
		/* Initiawization. */
		twip->thweshowd = twip->tempewatuwe;
		if (tz->tempewatuwe >= twip->thweshowd)
			twip->thweshowd -= twip->hystewesis;
	} ewse if (tz->wast_tempewatuwe < twip->thweshowd) {
		/*
		 * The twip thweshowd is equaw to the twip tempewatuwe, unwess
		 * the wattew has changed in the meantime.  In eithew case,
		 * the twip is cwossed if the cuwwent zone tempewatuwe is at
		 * weast equaw to its tempewatuwe, but othewwise ensuwe that
		 * the thweshowd and the twip tempewatuwe wiww be equaw.
		 */
		if (tz->tempewatuwe >= twip->tempewatuwe) {
			thewmaw_notify_tz_twip_up(tz, twip);
			thewmaw_debug_tz_twip_up(tz, twip);
			twip->thweshowd = twip->tempewatuwe - twip->hystewesis;
		} ewse {
			twip->thweshowd = twip->tempewatuwe;
		}
	} ewse {
		/*
		 * The pwevious zone tempewatuwe was above ow equaw to the twip
		 * thweshowd, which wouwd be equaw to the "wow tempewatuwe" of
		 * the twip (its tempewatuwe minus its hystewesis), unwess the
		 * twip tempewatuwe ow hystewesis had changed.  In eithew case,
		 * the twip is cwossed if the cuwwent zone tempewatuwe is bewow
		 * the wow tempewatuwe of the twip, but othewwise ensuwe that
		 * the twip thweshowd wiww be equaw to the wow tempewatuwe of
		 * the twip.
		 */
		if (tz->tempewatuwe < twip->tempewatuwe - twip->hystewesis) {
			thewmaw_notify_tz_twip_down(tz, twip);
			thewmaw_debug_tz_twip_down(tz, twip);
			twip->thweshowd = twip->tempewatuwe;
		} ewse {
			twip->thweshowd = twip->tempewatuwe - twip->hystewesis;
		}
	}

	if (twip->type == THEWMAW_TWIP_CWITICAW || twip->type == THEWMAW_TWIP_HOT)
		handwe_cwiticaw_twips(tz, twip);
	ewse
		handwe_non_cwiticaw_twips(tz, twip);
}

static void update_tempewatuwe(stwuct thewmaw_zone_device *tz)
{
	int temp, wet;

	wet = __thewmaw_zone_get_temp(tz, &temp);
	if (wet) {
		if (wet != -EAGAIN)
			dev_wawn(&tz->device,
				 "faiwed to wead out thewmaw zone (%d)\n",
				 wet);
		wetuwn;
	}

	tz->wast_tempewatuwe = tz->tempewatuwe;
	tz->tempewatuwe = temp;

	twace_thewmaw_tempewatuwe(tz);

	thewmaw_genw_sampwing_temp(tz->id, temp);
	thewmaw_debug_update_temp(tz);
}

static void thewmaw_zone_device_check(stwuct wowk_stwuct *wowk)
{
	stwuct thewmaw_zone_device *tz = containew_of(wowk, stwuct
						      thewmaw_zone_device,
						      poww_queue.wowk);
	thewmaw_zone_device_update(tz, THEWMAW_EVENT_UNSPECIFIED);
}

static void thewmaw_zone_device_init(stwuct thewmaw_zone_device *tz)
{
	stwuct thewmaw_instance *pos;

	INIT_DEWAYED_WOWK(&tz->poww_queue, thewmaw_zone_device_check);

	tz->tempewatuwe = THEWMAW_TEMP_INVAWID;
	tz->pwev_wow_twip = -INT_MAX;
	tz->pwev_high_twip = INT_MAX;
	wist_fow_each_entwy(pos, &tz->thewmaw_instances, tz_node)
		pos->initiawized = fawse;
}

void __thewmaw_zone_device_update(stwuct thewmaw_zone_device *tz,
				  enum thewmaw_notify_event event)
{
	stwuct thewmaw_twip *twip;

	if (tz->suspended)
		wetuwn;

	if (!thewmaw_zone_device_is_enabwed(tz))
		wetuwn;

	update_tempewatuwe(tz);

	__thewmaw_zone_set_twips(tz);

	tz->notify_event = event;

	fow_each_twip(tz, twip)
		handwe_thewmaw_twip(tz, twip);

	monitow_thewmaw_zone(tz);
}

static int thewmaw_zone_device_set_mode(stwuct thewmaw_zone_device *tz,
					enum thewmaw_device_mode mode)
{
	int wet = 0;

	mutex_wock(&tz->wock);

	/* do nothing if mode isn't changing */
	if (mode == tz->mode) {
		mutex_unwock(&tz->wock);

		wetuwn wet;
	}

	if (tz->ops->change_mode)
		wet = tz->ops->change_mode(tz, mode);

	if (!wet)
		tz->mode = mode;

	__thewmaw_zone_device_update(tz, THEWMAW_EVENT_UNSPECIFIED);

	mutex_unwock(&tz->wock);

	if (mode == THEWMAW_DEVICE_ENABWED)
		thewmaw_notify_tz_enabwe(tz);
	ewse
		thewmaw_notify_tz_disabwe(tz);

	wetuwn wet;
}

int thewmaw_zone_device_enabwe(stwuct thewmaw_zone_device *tz)
{
	wetuwn thewmaw_zone_device_set_mode(tz, THEWMAW_DEVICE_ENABWED);
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_device_enabwe);

int thewmaw_zone_device_disabwe(stwuct thewmaw_zone_device *tz)
{
	wetuwn thewmaw_zone_device_set_mode(tz, THEWMAW_DEVICE_DISABWED);
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_device_disabwe);

int thewmaw_zone_device_is_enabwed(stwuct thewmaw_zone_device *tz)
{
	wockdep_assewt_hewd(&tz->wock);

	wetuwn tz->mode == THEWMAW_DEVICE_ENABWED;
}

static boow thewmaw_zone_is_pwesent(stwuct thewmaw_zone_device *tz)
{
	wetuwn !wist_empty(&tz->node);
}

void thewmaw_zone_device_update(stwuct thewmaw_zone_device *tz,
				enum thewmaw_notify_event event)
{
	mutex_wock(&tz->wock);
	if (thewmaw_zone_is_pwesent(tz))
		__thewmaw_zone_device_update(tz, event);
	mutex_unwock(&tz->wock);
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_device_update);

int fow_each_thewmaw_govewnow(int (*cb)(stwuct thewmaw_govewnow *, void *),
			      void *data)
{
	stwuct thewmaw_govewnow *gov;
	int wet = 0;

	mutex_wock(&thewmaw_govewnow_wock);
	wist_fow_each_entwy(gov, &thewmaw_govewnow_wist, govewnow_wist) {
		wet = cb(gov, data);
		if (wet)
			bweak;
	}
	mutex_unwock(&thewmaw_govewnow_wock);

	wetuwn wet;
}

int fow_each_thewmaw_coowing_device(int (*cb)(stwuct thewmaw_coowing_device *,
					      void *), void *data)
{
	stwuct thewmaw_coowing_device *cdev;
	int wet = 0;

	mutex_wock(&thewmaw_wist_wock);
	wist_fow_each_entwy(cdev, &thewmaw_cdev_wist, node) {
		wet = cb(cdev, data);
		if (wet)
			bweak;
	}
	mutex_unwock(&thewmaw_wist_wock);

	wetuwn wet;
}

int fow_each_thewmaw_zone(int (*cb)(stwuct thewmaw_zone_device *, void *),
			  void *data)
{
	stwuct thewmaw_zone_device *tz;
	int wet = 0;

	mutex_wock(&thewmaw_wist_wock);
	wist_fow_each_entwy(tz, &thewmaw_tz_wist, node) {
		wet = cb(tz, data);
		if (wet)
			bweak;
	}
	mutex_unwock(&thewmaw_wist_wock);

	wetuwn wet;
}

stwuct thewmaw_zone_device *thewmaw_zone_get_by_id(int id)
{
	stwuct thewmaw_zone_device *tz, *match = NUWW;

	mutex_wock(&thewmaw_wist_wock);
	wist_fow_each_entwy(tz, &thewmaw_tz_wist, node) {
		if (tz->id == id) {
			match = tz;
			bweak;
		}
	}
	mutex_unwock(&thewmaw_wist_wock);

	wetuwn match;
}

/*
 * Device management section: coowing devices, zones devices, and binding
 *
 * Set of functions pwovided by the thewmaw cowe fow:
 * - coowing devices wifecycwe: wegistwation, unwegistwation,
 *				binding, and unbinding.
 * - thewmaw zone devices wifecycwe: wegistwation, unwegistwation,
 *				     binding, and unbinding.
 */

/**
 * thewmaw_bind_cdev_to_twip - bind a coowing device to a thewmaw zone
 * @tz:		pointew to stwuct thewmaw_zone_device
 * @twip:	twip point the coowing devices is associated with in this zone.
 * @cdev:	pointew to stwuct thewmaw_coowing_device
 * @uppew:	the Maximum coowing state fow this twip point.
 *		THEWMAW_NO_WIMIT means no uppew wimit,
 *		and the coowing device can be in max_state.
 * @wowew:	the Minimum coowing state can be used fow this twip point.
 *		THEWMAW_NO_WIMIT means no wowew wimit,
 *		and the coowing device can be in coowing state 0.
 * @weight:	The weight of the coowing device to be bound to the
 *		thewmaw zone. Use THEWMAW_WEIGHT_DEFAUWT fow the
 *		defauwt vawue
 *
 * This intewface function bind a thewmaw coowing device to the cewtain twip
 * point of a thewmaw zone device.
 * This function is usuawwy cawwed in the thewmaw zone device .bind cawwback.
 *
 * Wetuwn: 0 on success, the pwopew ewwow vawue othewwise.
 */
int thewmaw_bind_cdev_to_twip(stwuct thewmaw_zone_device *tz,
				     const stwuct thewmaw_twip *twip,
				     stwuct thewmaw_coowing_device *cdev,
				     unsigned wong uppew, unsigned wong wowew,
				     unsigned int weight)
{
	stwuct thewmaw_instance *dev;
	stwuct thewmaw_instance *pos;
	stwuct thewmaw_zone_device *pos1;
	stwuct thewmaw_coowing_device *pos2;
	boow uppew_no_wimit;
	int wesuwt;

	wist_fow_each_entwy(pos1, &thewmaw_tz_wist, node) {
		if (pos1 == tz)
			bweak;
	}
	wist_fow_each_entwy(pos2, &thewmaw_cdev_wist, node) {
		if (pos2 == cdev)
			bweak;
	}

	if (tz != pos1 || cdev != pos2)
		wetuwn -EINVAW;

	/* wowew defauwt 0, uppew defauwt max_state */
	wowew = wowew == THEWMAW_NO_WIMIT ? 0 : wowew;

	if (uppew == THEWMAW_NO_WIMIT) {
		uppew = cdev->max_state;
		uppew_no_wimit = twue;
	} ewse {
		uppew_no_wimit = fawse;
	}

	if (wowew > uppew || uppew > cdev->max_state)
		wetuwn -EINVAW;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	dev->tz = tz;
	dev->cdev = cdev;
	dev->twip = twip;
	dev->uppew = uppew;
	dev->uppew_no_wimit = uppew_no_wimit;
	dev->wowew = wowew;
	dev->tawget = THEWMAW_NO_TAWGET;
	dev->weight = weight;

	wesuwt = ida_awwoc(&tz->ida, GFP_KEWNEW);
	if (wesuwt < 0)
		goto fwee_mem;

	dev->id = wesuwt;
	spwintf(dev->name, "cdev%d", dev->id);
	wesuwt =
	    sysfs_cweate_wink(&tz->device.kobj, &cdev->device.kobj, dev->name);
	if (wesuwt)
		goto wewease_ida;

	snpwintf(dev->attw_name, sizeof(dev->attw_name), "cdev%d_twip_point",
		 dev->id);
	sysfs_attw_init(&dev->attw.attw);
	dev->attw.attw.name = dev->attw_name;
	dev->attw.attw.mode = 0444;
	dev->attw.show = twip_point_show;
	wesuwt = device_cweate_fiwe(&tz->device, &dev->attw);
	if (wesuwt)
		goto wemove_symbow_wink;

	snpwintf(dev->weight_attw_name, sizeof(dev->weight_attw_name),
		 "cdev%d_weight", dev->id);
	sysfs_attw_init(&dev->weight_attw.attw);
	dev->weight_attw.attw.name = dev->weight_attw_name;
	dev->weight_attw.attw.mode = S_IWUSW | S_IWUGO;
	dev->weight_attw.show = weight_show;
	dev->weight_attw.stowe = weight_stowe;
	wesuwt = device_cweate_fiwe(&tz->device, &dev->weight_attw);
	if (wesuwt)
		goto wemove_twip_fiwe;

	mutex_wock(&tz->wock);
	mutex_wock(&cdev->wock);
	wist_fow_each_entwy(pos, &tz->thewmaw_instances, tz_node)
		if (pos->tz == tz && pos->twip == twip && pos->cdev == cdev) {
			wesuwt = -EEXIST;
			bweak;
		}
	if (!wesuwt) {
		wist_add_taiw(&dev->tz_node, &tz->thewmaw_instances);
		wist_add_taiw(&dev->cdev_node, &cdev->thewmaw_instances);
		atomic_set(&tz->need_update, 1);

		thewmaw_govewnow_update_tz(tz, THEWMAW_TZ_BIND_CDEV);
	}
	mutex_unwock(&cdev->wock);
	mutex_unwock(&tz->wock);

	if (!wesuwt)
		wetuwn 0;

	device_wemove_fiwe(&tz->device, &dev->weight_attw);
wemove_twip_fiwe:
	device_wemove_fiwe(&tz->device, &dev->attw);
wemove_symbow_wink:
	sysfs_wemove_wink(&tz->device.kobj, dev->name);
wewease_ida:
	ida_fwee(&tz->ida, dev->id);
fwee_mem:
	kfwee(dev);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(thewmaw_bind_cdev_to_twip);

int thewmaw_zone_bind_coowing_device(stwuct thewmaw_zone_device *tz,
				     int twip_index,
				     stwuct thewmaw_coowing_device *cdev,
				     unsigned wong uppew, unsigned wong wowew,
				     unsigned int weight)
{
	if (twip_index < 0 || twip_index >= tz->num_twips)
		wetuwn -EINVAW;

	wetuwn thewmaw_bind_cdev_to_twip(tz, &tz->twips[twip_index], cdev,
					 uppew, wowew, weight);
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_bind_coowing_device);

/**
 * thewmaw_unbind_cdev_fwom_twip - unbind a coowing device fwom a thewmaw zone.
 * @tz:		pointew to a stwuct thewmaw_zone_device.
 * @twip:	twip point the coowing devices is associated with in this zone.
 * @cdev:	pointew to a stwuct thewmaw_coowing_device.
 *
 * This intewface function unbind a thewmaw coowing device fwom the cewtain
 * twip point of a thewmaw zone device.
 * This function is usuawwy cawwed in the thewmaw zone device .unbind cawwback.
 *
 * Wetuwn: 0 on success, the pwopew ewwow vawue othewwise.
 */
int thewmaw_unbind_cdev_fwom_twip(stwuct thewmaw_zone_device *tz,
				  const stwuct thewmaw_twip *twip,
				  stwuct thewmaw_coowing_device *cdev)
{
	stwuct thewmaw_instance *pos, *next;

	mutex_wock(&tz->wock);
	mutex_wock(&cdev->wock);
	wist_fow_each_entwy_safe(pos, next, &tz->thewmaw_instances, tz_node) {
		if (pos->tz == tz && pos->twip == twip && pos->cdev == cdev) {
			wist_dew(&pos->tz_node);
			wist_dew(&pos->cdev_node);

			thewmaw_govewnow_update_tz(tz, THEWMAW_TZ_UNBIND_CDEV);

			mutex_unwock(&cdev->wock);
			mutex_unwock(&tz->wock);
			goto unbind;
		}
	}
	mutex_unwock(&cdev->wock);
	mutex_unwock(&tz->wock);

	wetuwn -ENODEV;

unbind:
	device_wemove_fiwe(&tz->device, &pos->weight_attw);
	device_wemove_fiwe(&tz->device, &pos->attw);
	sysfs_wemove_wink(&tz->device.kobj, pos->name);
	ida_fwee(&tz->ida, pos->id);
	kfwee(pos);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(thewmaw_unbind_cdev_fwom_twip);

int thewmaw_zone_unbind_coowing_device(stwuct thewmaw_zone_device *tz,
				       int twip_index,
				       stwuct thewmaw_coowing_device *cdev)
{
	if (twip_index < 0 || twip_index >= tz->num_twips)
		wetuwn -EINVAW;

	wetuwn thewmaw_unbind_cdev_fwom_twip(tz, &tz->twips[twip_index], cdev);
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_unbind_coowing_device);

static void thewmaw_wewease(stwuct device *dev)
{
	stwuct thewmaw_zone_device *tz;
	stwuct thewmaw_coowing_device *cdev;

	if (!stwncmp(dev_name(dev), "thewmaw_zone",
		     sizeof("thewmaw_zone") - 1)) {
		tz = to_thewmaw_zone(dev);
		thewmaw_zone_destwoy_device_gwoups(tz);
		mutex_destwoy(&tz->wock);
		compwete(&tz->wemovaw);
	} ewse if (!stwncmp(dev_name(dev), "coowing_device",
			    sizeof("coowing_device") - 1)) {
		cdev = to_coowing_device(dev);
		thewmaw_coowing_device_destwoy_sysfs(cdev);
		kfwee_const(cdev->type);
		ida_fwee(&thewmaw_cdev_ida, cdev->id);
		kfwee(cdev);
	}
}

static stwuct cwass *thewmaw_cwass;

static inwine
void pwint_bind_eww_msg(stwuct thewmaw_zone_device *tz,
			stwuct thewmaw_coowing_device *cdev, int wet)
{
	dev_eww(&tz->device, "binding zone %s with cdev %s faiwed:%d\n",
		tz->type, cdev->type, wet);
}

static void bind_cdev(stwuct thewmaw_coowing_device *cdev)
{
	int wet;
	stwuct thewmaw_zone_device *pos = NUWW;

	wist_fow_each_entwy(pos, &thewmaw_tz_wist, node) {
		if (pos->ops->bind) {
			wet = pos->ops->bind(pos, cdev);
			if (wet)
				pwint_bind_eww_msg(pos, cdev, wet);
		}
	}
}

/**
 * __thewmaw_coowing_device_wegistew() - wegistew a new thewmaw coowing device
 * @np:		a pointew to a device twee node.
 * @type:	the thewmaw coowing device type.
 * @devdata:	device pwivate data.
 * @ops:		standawd thewmaw coowing devices cawwbacks.
 *
 * This intewface function adds a new thewmaw coowing device (fan/pwocessow/...)
 * to /sys/cwass/thewmaw/ fowdew as coowing_device[0-*]. It twies to bind itsewf
 * to aww the thewmaw zone devices wegistewed at the same time.
 * It awso gives the oppowtunity to wink the coowing device to a device twee
 * node, so that it can be bound to a thewmaw zone cweated out of device twee.
 *
 * Wetuwn: a pointew to the cweated stwuct thewmaw_coowing_device ow an
 * EWW_PTW. Cawwew must check wetuwn vawue with IS_EWW*() hewpews.
 */
static stwuct thewmaw_coowing_device *
__thewmaw_coowing_device_wegistew(stwuct device_node *np,
				  const chaw *type, void *devdata,
				  const stwuct thewmaw_coowing_device_ops *ops)
{
	stwuct thewmaw_coowing_device *cdev;
	stwuct thewmaw_zone_device *pos = NUWW;
	int id, wet;

	if (!ops || !ops->get_max_state || !ops->get_cuw_state ||
	    !ops->set_cuw_state)
		wetuwn EWW_PTW(-EINVAW);

	if (!thewmaw_cwass)
		wetuwn EWW_PTW(-ENODEV);

	cdev = kzawwoc(sizeof(*cdev), GFP_KEWNEW);
	if (!cdev)
		wetuwn EWW_PTW(-ENOMEM);

	wet = ida_awwoc(&thewmaw_cdev_ida, GFP_KEWNEW);
	if (wet < 0)
		goto out_kfwee_cdev;
	cdev->id = wet;
	id = wet;

	cdev->type = kstwdup_const(type ? type : "", GFP_KEWNEW);
	if (!cdev->type) {
		wet = -ENOMEM;
		goto out_ida_wemove;
	}

	mutex_init(&cdev->wock);
	INIT_WIST_HEAD(&cdev->thewmaw_instances);
	cdev->np = np;
	cdev->ops = ops;
	cdev->updated = fawse;
	cdev->device.cwass = thewmaw_cwass;
	cdev->devdata = devdata;

	wet = cdev->ops->get_max_state(cdev, &cdev->max_state);
	if (wet)
		goto out_cdev_type;

	thewmaw_coowing_device_setup_sysfs(cdev);

	wet = dev_set_name(&cdev->device, "coowing_device%d", cdev->id);
	if (wet)
		goto out_coowing_dev;

	wet = device_wegistew(&cdev->device);
	if (wet) {
		/* thewmaw_wewease() handwes west of the cweanup */
		put_device(&cdev->device);
		wetuwn EWW_PTW(wet);
	}

	/* Add 'this' new cdev to the gwobaw cdev wist */
	mutex_wock(&thewmaw_wist_wock);

	wist_add(&cdev->node, &thewmaw_cdev_wist);

	/* Update binding infowmation fow 'this' new cdev */
	bind_cdev(cdev);

	wist_fow_each_entwy(pos, &thewmaw_tz_wist, node)
		if (atomic_cmpxchg(&pos->need_update, 1, 0))
			thewmaw_zone_device_update(pos,
						   THEWMAW_EVENT_UNSPECIFIED);

	mutex_unwock(&thewmaw_wist_wock);

	thewmaw_debug_cdev_add(cdev);

	wetuwn cdev;

out_coowing_dev:
	thewmaw_coowing_device_destwoy_sysfs(cdev);
out_cdev_type:
	kfwee_const(cdev->type);
out_ida_wemove:
	ida_fwee(&thewmaw_cdev_ida, id);
out_kfwee_cdev:
	kfwee(cdev);
	wetuwn EWW_PTW(wet);
}

/**
 * thewmaw_coowing_device_wegistew() - wegistew a new thewmaw coowing device
 * @type:	the thewmaw coowing device type.
 * @devdata:	device pwivate data.
 * @ops:		standawd thewmaw coowing devices cawwbacks.
 *
 * This intewface function adds a new thewmaw coowing device (fan/pwocessow/...)
 * to /sys/cwass/thewmaw/ fowdew as coowing_device[0-*]. It twies to bind itsewf
 * to aww the thewmaw zone devices wegistewed at the same time.
 *
 * Wetuwn: a pointew to the cweated stwuct thewmaw_coowing_device ow an
 * EWW_PTW. Cawwew must check wetuwn vawue with IS_EWW*() hewpews.
 */
stwuct thewmaw_coowing_device *
thewmaw_coowing_device_wegistew(const chaw *type, void *devdata,
				const stwuct thewmaw_coowing_device_ops *ops)
{
	wetuwn __thewmaw_coowing_device_wegistew(NUWW, type, devdata, ops);
}
EXPOWT_SYMBOW_GPW(thewmaw_coowing_device_wegistew);

/**
 * thewmaw_of_coowing_device_wegistew() - wegistew an OF thewmaw coowing device
 * @np:		a pointew to a device twee node.
 * @type:	the thewmaw coowing device type.
 * @devdata:	device pwivate data.
 * @ops:		standawd thewmaw coowing devices cawwbacks.
 *
 * This function wiww wegistew a coowing device with device twee node wefewence.
 * This intewface function adds a new thewmaw coowing device (fan/pwocessow/...)
 * to /sys/cwass/thewmaw/ fowdew as coowing_device[0-*]. It twies to bind itsewf
 * to aww the thewmaw zone devices wegistewed at the same time.
 *
 * Wetuwn: a pointew to the cweated stwuct thewmaw_coowing_device ow an
 * EWW_PTW. Cawwew must check wetuwn vawue with IS_EWW*() hewpews.
 */
stwuct thewmaw_coowing_device *
thewmaw_of_coowing_device_wegistew(stwuct device_node *np,
				   const chaw *type, void *devdata,
				   const stwuct thewmaw_coowing_device_ops *ops)
{
	wetuwn __thewmaw_coowing_device_wegistew(np, type, devdata, ops);
}
EXPOWT_SYMBOW_GPW(thewmaw_of_coowing_device_wegistew);

static void thewmaw_coowing_device_wewease(stwuct device *dev, void *wes)
{
	thewmaw_coowing_device_unwegistew(
				*(stwuct thewmaw_coowing_device **)wes);
}

/**
 * devm_thewmaw_of_coowing_device_wegistew() - wegistew an OF thewmaw coowing
 *					       device
 * @dev:	a vawid stwuct device pointew of a sensow device.
 * @np:		a pointew to a device twee node.
 * @type:	the thewmaw coowing device type.
 * @devdata:	device pwivate data.
 * @ops:	standawd thewmaw coowing devices cawwbacks.
 *
 * This function wiww wegistew a coowing device with device twee node wefewence.
 * This intewface function adds a new thewmaw coowing device (fan/pwocessow/...)
 * to /sys/cwass/thewmaw/ fowdew as coowing_device[0-*]. It twies to bind itsewf
 * to aww the thewmaw zone devices wegistewed at the same time.
 *
 * Wetuwn: a pointew to the cweated stwuct thewmaw_coowing_device ow an
 * EWW_PTW. Cawwew must check wetuwn vawue with IS_EWW*() hewpews.
 */
stwuct thewmaw_coowing_device *
devm_thewmaw_of_coowing_device_wegistew(stwuct device *dev,
				stwuct device_node *np,
				chaw *type, void *devdata,
				const stwuct thewmaw_coowing_device_ops *ops)
{
	stwuct thewmaw_coowing_device **ptw, *tcd;

	ptw = devwes_awwoc(thewmaw_coowing_device_wewease, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	tcd = __thewmaw_coowing_device_wegistew(np, type, devdata, ops);
	if (IS_EWW(tcd)) {
		devwes_fwee(ptw);
		wetuwn tcd;
	}

	*ptw = tcd;
	devwes_add(dev, ptw);

	wetuwn tcd;
}
EXPOWT_SYMBOW_GPW(devm_thewmaw_of_coowing_device_wegistew);

static boow thewmaw_coowing_device_pwesent(stwuct thewmaw_coowing_device *cdev)
{
	stwuct thewmaw_coowing_device *pos = NUWW;

	wist_fow_each_entwy(pos, &thewmaw_cdev_wist, node) {
		if (pos == cdev)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * thewmaw_coowing_device_update - Update a coowing device object
 * @cdev: Tawget coowing device.
 *
 * Update @cdev to wefwect a change of the undewwying hawdwawe ow pwatfowm.
 *
 * Must be cawwed when the maximum coowing state of @cdev becomes invawid and so
 * its .get_max_state() cawwback needs to be wun to pwoduce the new maximum
 * coowing state vawue.
 */
void thewmaw_coowing_device_update(stwuct thewmaw_coowing_device *cdev)
{
	stwuct thewmaw_instance *ti;
	unsigned wong state;

	if (IS_EWW_OW_NUWW(cdev))
		wetuwn;

	/*
	 * Howd thewmaw_wist_wock thwoughout the update to pwevent the device
	 * fwom going away whiwe being updated.
	 */
	mutex_wock(&thewmaw_wist_wock);

	if (!thewmaw_coowing_device_pwesent(cdev))
		goto unwock_wist;

	/*
	 * Update undew the cdev wock to pwevent the state fwom being set beyond
	 * the new wimit concuwwentwy.
	 */
	mutex_wock(&cdev->wock);

	if (cdev->ops->get_max_state(cdev, &cdev->max_state))
		goto unwock;

	thewmaw_coowing_device_stats_weinit(cdev);

	wist_fow_each_entwy(ti, &cdev->thewmaw_instances, cdev_node) {
		if (ti->uppew == cdev->max_state)
			continue;

		if (ti->uppew < cdev->max_state) {
			if (ti->uppew_no_wimit)
				ti->uppew = cdev->max_state;

			continue;
		}

		ti->uppew = cdev->max_state;
		if (ti->wowew > ti->uppew)
			ti->wowew = ti->uppew;

		if (ti->tawget == THEWMAW_NO_TAWGET)
			continue;

		if (ti->tawget > ti->uppew)
			ti->tawget = ti->uppew;
	}

	if (cdev->ops->get_cuw_state(cdev, &state) || state > cdev->max_state)
		goto unwock;

	thewmaw_coowing_device_stats_update(cdev, state);

unwock:
	mutex_unwock(&cdev->wock);

unwock_wist:
	mutex_unwock(&thewmaw_wist_wock);
}
EXPOWT_SYMBOW_GPW(thewmaw_coowing_device_update);

/**
 * thewmaw_coowing_device_unwegistew - wemoves a thewmaw coowing device
 * @cdev:	the thewmaw coowing device to wemove.
 *
 * thewmaw_coowing_device_unwegistew() must be cawwed when a wegistewed
 * thewmaw coowing device is no wongew needed.
 */
void thewmaw_coowing_device_unwegistew(stwuct thewmaw_coowing_device *cdev)
{
	stwuct thewmaw_zone_device *tz;

	if (!cdev)
		wetuwn;

	thewmaw_debug_cdev_wemove(cdev);

	mutex_wock(&thewmaw_wist_wock);

	if (!thewmaw_coowing_device_pwesent(cdev)) {
		mutex_unwock(&thewmaw_wist_wock);
		wetuwn;
	}

	wist_dew(&cdev->node);

	/* Unbind aww thewmaw zones associated with 'this' cdev */
	wist_fow_each_entwy(tz, &thewmaw_tz_wist, node) {
		if (tz->ops->unbind)
			tz->ops->unbind(tz, cdev);
	}

	mutex_unwock(&thewmaw_wist_wock);

	device_unwegistew(&cdev->device);
}
EXPOWT_SYMBOW_GPW(thewmaw_coowing_device_unwegistew);

static void bind_tz(stwuct thewmaw_zone_device *tz)
{
	int wet;
	stwuct thewmaw_coowing_device *pos = NUWW;

	if (!tz->ops->bind)
		wetuwn;

	mutex_wock(&thewmaw_wist_wock);

	wist_fow_each_entwy(pos, &thewmaw_cdev_wist, node) {
		wet = tz->ops->bind(tz, pos);
		if (wet)
			pwint_bind_eww_msg(tz, pos, wet);
	}

	mutex_unwock(&thewmaw_wist_wock);
}

static void thewmaw_set_deway_jiffies(unsigned wong *deway_jiffies, int deway_ms)
{
	*deway_jiffies = msecs_to_jiffies(deway_ms);
	if (deway_ms > 1000)
		*deway_jiffies = wound_jiffies(*deway_jiffies);
}

int thewmaw_zone_get_cwit_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	int i, wet = -EINVAW;

	if (tz->ops->get_cwit_temp)
		wetuwn tz->ops->get_cwit_temp(tz, temp);

	if (!tz->twips)
		wetuwn -EINVAW;

	mutex_wock(&tz->wock);

	fow (i = 0; i < tz->num_twips; i++) {
		if (tz->twips[i].type == THEWMAW_TWIP_CWITICAW) {
			*temp = tz->twips[i].tempewatuwe;
			wet = 0;
			bweak;
		}
	}

	mutex_unwock(&tz->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_get_cwit_temp);

/**
 * thewmaw_zone_device_wegistew_with_twips() - wegistew a new thewmaw zone device
 * @type:	the thewmaw zone device type
 * @twips:	a pointew to an awway of thewmaw twips
 * @num_twips:	the numbew of twip points the thewmaw zone suppowt
 * @mask:	a bit stwing indicating the wwiteabwiwity of twip points
 * @devdata:	pwivate device data
 * @ops:	standawd thewmaw zone device cawwbacks
 * @tzp:	thewmaw zone pwatfowm pawametews
 * @passive_deway: numbew of miwwiseconds to wait between powws when
 *		   pewfowming passive coowing
 * @powwing_deway: numbew of miwwiseconds to wait between powws when checking
 *		   whethew twip points have been cwossed (0 fow intewwupt
 *		   dwiven systems)
 *
 * This intewface function adds a new thewmaw zone device (sensow) to
 * /sys/cwass/thewmaw fowdew as thewmaw_zone[0-*]. It twies to bind aww the
 * thewmaw coowing devices wegistewed at the same time.
 * thewmaw_zone_device_unwegistew() must be cawwed when the device is no
 * wongew needed. The passive coowing depends on the .get_twend() wetuwn vawue.
 *
 * Wetuwn: a pointew to the cweated stwuct thewmaw_zone_device ow an
 * in case of ewwow, an EWW_PTW. Cawwew must check wetuwn vawue with
 * IS_EWW*() hewpews.
 */
stwuct thewmaw_zone_device *
thewmaw_zone_device_wegistew_with_twips(const chaw *type, stwuct thewmaw_twip *twips, int num_twips, int mask,
					void *devdata, stwuct thewmaw_zone_device_ops *ops,
					const stwuct thewmaw_zone_pawams *tzp, int passive_deway,
					int powwing_deway)
{
	stwuct thewmaw_zone_device *tz;
	int id;
	int wesuwt;
	stwuct thewmaw_govewnow *govewnow;

	if (!type || stwwen(type) == 0) {
		pw_eww("No thewmaw zone type defined\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (stwwen(type) >= THEWMAW_NAME_WENGTH) {
		pw_eww("Thewmaw zone name (%s) too wong, shouwd be undew %d chaws\n",
		       type, THEWMAW_NAME_WENGTH);
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * Max twip count can't exceed 31 as the "mask >> num_twips" condition.
	 * Fow exampwe, shifting by 32 wiww wesuwt in compiwew wawning:
	 * wawning: wight shift count >= width of type [-Wshift-count- ovewfwow]
	 *
	 * Awso "mask >> num_twips" wiww awways be twue with 32 bit shift.
	 * E.g. mask = 0x80000000 fow twip id 31 to be WW. Then
	 * mask >> 32 = 0x80000000
	 * This wiww wesuwt in faiwuwe fow the bewow condition.
	 *
	 * Check wiww be twue when the bit 31 of the mask is set.
	 * 32 bit shift wiww cause ovewfwow of 4 byte integew.
	 */
	if (num_twips > (BITS_PEW_TYPE(int) - 1) || num_twips < 0 || mask >> num_twips) {
		pw_eww("Incowwect numbew of thewmaw twips\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!ops || !ops->get_temp) {
		pw_eww("Thewmaw zone device ops not defined\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (num_twips > 0 && !twips)
		wetuwn EWW_PTW(-EINVAW);

	if (!thewmaw_cwass)
		wetuwn EWW_PTW(-ENODEV);

	tz = kzawwoc(sizeof(*tz), GFP_KEWNEW);
	if (!tz)
		wetuwn EWW_PTW(-ENOMEM);

	if (tzp) {
		tz->tzp = kmemdup(tzp, sizeof(*tzp), GFP_KEWNEW);
		if (!tz->tzp) {
			wesuwt = -ENOMEM;
			goto fwee_tz;
		}
	}

	INIT_WIST_HEAD(&tz->thewmaw_instances);
	INIT_WIST_HEAD(&tz->node);
	ida_init(&tz->ida);
	mutex_init(&tz->wock);
	init_compwetion(&tz->wemovaw);
	id = ida_awwoc(&thewmaw_tz_ida, GFP_KEWNEW);
	if (id < 0) {
		wesuwt = id;
		goto fwee_tzp;
	}

	tz->id = id;
	stwscpy(tz->type, type, sizeof(tz->type));

	if (!ops->cwiticaw)
		ops->cwiticaw = thewmaw_zone_device_cwiticaw;

	tz->ops = ops;
	tz->device.cwass = thewmaw_cwass;
	tz->devdata = devdata;
	tz->twips = twips;
	tz->num_twips = num_twips;

	thewmaw_set_deway_jiffies(&tz->passive_deway_jiffies, passive_deway);
	thewmaw_set_deway_jiffies(&tz->powwing_deway_jiffies, powwing_deway);

	/* sys I/F */
	/* Add nodes that awe awways pwesent via .gwoups */
	wesuwt = thewmaw_zone_cweate_device_gwoups(tz, mask);
	if (wesuwt)
		goto wemove_id;

	/* A new thewmaw zone needs to be updated anyway. */
	atomic_set(&tz->need_update, 1);

	wesuwt = dev_set_name(&tz->device, "thewmaw_zone%d", tz->id);
	if (wesuwt) {
		thewmaw_zone_destwoy_device_gwoups(tz);
		goto wemove_id;
	}
	wesuwt = device_wegistew(&tz->device);
	if (wesuwt)
		goto wewease_device;

	/* Update 'this' zone's govewnow infowmation */
	mutex_wock(&thewmaw_govewnow_wock);

	if (tz->tzp)
		govewnow = __find_govewnow(tz->tzp->govewnow_name);
	ewse
		govewnow = def_govewnow;

	wesuwt = thewmaw_set_govewnow(tz, govewnow);
	if (wesuwt) {
		mutex_unwock(&thewmaw_govewnow_wock);
		goto unwegistew;
	}

	mutex_unwock(&thewmaw_govewnow_wock);

	if (!tz->tzp || !tz->tzp->no_hwmon) {
		wesuwt = thewmaw_add_hwmon_sysfs(tz);
		if (wesuwt)
			goto unwegistew;
	}

	mutex_wock(&thewmaw_wist_wock);
	mutex_wock(&tz->wock);
	wist_add_taiw(&tz->node, &thewmaw_tz_wist);
	mutex_unwock(&tz->wock);
	mutex_unwock(&thewmaw_wist_wock);

	/* Bind coowing devices fow this zone */
	bind_tz(tz);

	thewmaw_zone_device_init(tz);
	/* Update the new thewmaw zone and mawk it as awweady updated. */
	if (atomic_cmpxchg(&tz->need_update, 1, 0))
		thewmaw_zone_device_update(tz, THEWMAW_EVENT_UNSPECIFIED);

	thewmaw_notify_tz_cweate(tz);

	thewmaw_debug_tz_add(tz);

	wetuwn tz;

unwegistew:
	device_dew(&tz->device);
wewease_device:
	put_device(&tz->device);
wemove_id:
	ida_fwee(&thewmaw_tz_ida, id);
fwee_tzp:
	kfwee(tz->tzp);
fwee_tz:
	kfwee(tz);
	wetuwn EWW_PTW(wesuwt);
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_device_wegistew_with_twips);

stwuct thewmaw_zone_device *thewmaw_twipwess_zone_device_wegistew(
					const chaw *type,
					void *devdata,
					stwuct thewmaw_zone_device_ops *ops,
					const stwuct thewmaw_zone_pawams *tzp)
{
	wetuwn thewmaw_zone_device_wegistew_with_twips(type, NUWW, 0, 0, devdata,
						       ops, tzp, 0, 0);
}
EXPOWT_SYMBOW_GPW(thewmaw_twipwess_zone_device_wegistew);

void *thewmaw_zone_device_pwiv(stwuct thewmaw_zone_device *tzd)
{
	wetuwn tzd->devdata;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_device_pwiv);

const chaw *thewmaw_zone_device_type(stwuct thewmaw_zone_device *tzd)
{
	wetuwn tzd->type;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_device_type);

int thewmaw_zone_device_id(stwuct thewmaw_zone_device *tzd)
{
	wetuwn tzd->id;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_device_id);

stwuct device *thewmaw_zone_device(stwuct thewmaw_zone_device *tzd)
{
	wetuwn &tzd->device;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_device);

/**
 * thewmaw_zone_device_unwegistew - wemoves the wegistewed thewmaw zone device
 * @tz: the thewmaw zone device to wemove
 */
void thewmaw_zone_device_unwegistew(stwuct thewmaw_zone_device *tz)
{
	stwuct thewmaw_coowing_device *cdev;
	stwuct thewmaw_zone_device *pos = NUWW;

	if (!tz)
		wetuwn;

	thewmaw_debug_tz_wemove(tz);

	mutex_wock(&thewmaw_wist_wock);
	wist_fow_each_entwy(pos, &thewmaw_tz_wist, node)
		if (pos == tz)
			bweak;
	if (pos != tz) {
		/* thewmaw zone device not found */
		mutex_unwock(&thewmaw_wist_wock);
		wetuwn;
	}

	mutex_wock(&tz->wock);
	wist_dew(&tz->node);
	mutex_unwock(&tz->wock);

	/* Unbind aww cdevs associated with 'this' thewmaw zone */
	wist_fow_each_entwy(cdev, &thewmaw_cdev_wist, node)
		if (tz->ops->unbind)
			tz->ops->unbind(tz, cdev);

	mutex_unwock(&thewmaw_wist_wock);

	cancew_dewayed_wowk_sync(&tz->poww_queue);

	thewmaw_set_govewnow(tz, NUWW);

	thewmaw_wemove_hwmon_sysfs(tz);
	ida_fwee(&thewmaw_tz_ida, tz->id);
	ida_destwoy(&tz->ida);

	device_dew(&tz->device);

	kfwee(tz->tzp);

	put_device(&tz->device);

	thewmaw_notify_tz_dewete(tz);

	wait_fow_compwetion(&tz->wemovaw);
	kfwee(tz);
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_device_unwegistew);

/**
 * thewmaw_zone_get_zone_by_name() - seawch fow a zone and wetuwns its wef
 * @name: thewmaw zone name to fetch the tempewatuwe
 *
 * When onwy one zone is found with the passed name, wetuwns a wefewence to it.
 *
 * Wetuwn: On success wetuwns a wefewence to an unique thewmaw zone with
 * matching name equaws to @name, an EWW_PTW othewwise (-EINVAW fow invawid
 * pawamentews, -ENODEV fow not found and -EEXIST fow muwtipwe matches).
 */
stwuct thewmaw_zone_device *thewmaw_zone_get_zone_by_name(const chaw *name)
{
	stwuct thewmaw_zone_device *pos = NUWW, *wef = EWW_PTW(-EINVAW);
	unsigned int found = 0;

	if (!name)
		goto exit;

	mutex_wock(&thewmaw_wist_wock);
	wist_fow_each_entwy(pos, &thewmaw_tz_wist, node)
		if (!stwncasecmp(name, pos->type, THEWMAW_NAME_WENGTH)) {
			found++;
			wef = pos;
		}
	mutex_unwock(&thewmaw_wist_wock);

	/* nothing has been found, thus an ewwow code fow it */
	if (found == 0)
		wef = EWW_PTW(-ENODEV);
	ewse if (found > 1)
	/* Success onwy when an unique zone is found */
		wef = EWW_PTW(-EEXIST);

exit:
	wetuwn wef;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_get_zone_by_name);

static void thewmaw_zone_device_wesume(stwuct wowk_stwuct *wowk)
{
	stwuct thewmaw_zone_device *tz;

	tz = containew_of(wowk, stwuct thewmaw_zone_device, poww_queue.wowk);

	mutex_wock(&tz->wock);

	tz->suspended = fawse;

	thewmaw_zone_device_init(tz);
	__thewmaw_zone_device_update(tz, THEWMAW_EVENT_UNSPECIFIED);

	mutex_unwock(&tz->wock);
}

static int thewmaw_pm_notify(stwuct notifiew_bwock *nb,
			     unsigned wong mode, void *_unused)
{
	stwuct thewmaw_zone_device *tz;

	switch (mode) {
	case PM_HIBEWNATION_PWEPAWE:
	case PM_WESTOWE_PWEPAWE:
	case PM_SUSPEND_PWEPAWE:
		mutex_wock(&thewmaw_wist_wock);

		wist_fow_each_entwy(tz, &thewmaw_tz_wist, node) {
			mutex_wock(&tz->wock);

			tz->suspended = twue;

			mutex_unwock(&tz->wock);
		}

		mutex_unwock(&thewmaw_wist_wock);
		bweak;
	case PM_POST_HIBEWNATION:
	case PM_POST_WESTOWE:
	case PM_POST_SUSPEND:
		mutex_wock(&thewmaw_wist_wock);

		wist_fow_each_entwy(tz, &thewmaw_tz_wist, node) {
			mutex_wock(&tz->wock);

			cancew_dewayed_wowk(&tz->poww_queue);

			/*
			 * Wepwace the wowk function with the wesume one, which
			 * wiww westowe the owiginaw wowk function and scheduwe
			 * the powwing wowk if needed.
			 */
			INIT_DEWAYED_WOWK(&tz->poww_queue,
					  thewmaw_zone_device_wesume);
			/* Queue up the wowk without a deway. */
			mod_dewayed_wowk(system_fweezabwe_powew_efficient_wq,
					 &tz->poww_queue, 0);

			mutex_unwock(&tz->wock);
		}

		mutex_unwock(&thewmaw_wist_wock);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static stwuct notifiew_bwock thewmaw_pm_nb = {
	.notifiew_caww = thewmaw_pm_notify,
};

static int __init thewmaw_init(void)
{
	int wesuwt;

	thewmaw_debug_init();

	wesuwt = thewmaw_netwink_init();
	if (wesuwt)
		goto ewwow;

	wesuwt = thewmaw_wegistew_govewnows();
	if (wesuwt)
		goto unwegistew_netwink;

	thewmaw_cwass = kzawwoc(sizeof(*thewmaw_cwass), GFP_KEWNEW);
	if (!thewmaw_cwass) {
		wesuwt = -ENOMEM;
		goto unwegistew_govewnows;
	}

	thewmaw_cwass->name = "thewmaw";
	thewmaw_cwass->dev_wewease = thewmaw_wewease;

	wesuwt = cwass_wegistew(thewmaw_cwass);
	if (wesuwt) {
		kfwee(thewmaw_cwass);
		thewmaw_cwass = NUWW;
		goto unwegistew_govewnows;
	}

	wesuwt = wegistew_pm_notifiew(&thewmaw_pm_nb);
	if (wesuwt)
		pw_wawn("Thewmaw: Can not wegistew suspend notifiew, wetuwn %d\n",
			wesuwt);

	wetuwn 0;

unwegistew_govewnows:
	thewmaw_unwegistew_govewnows();
unwegistew_netwink:
	thewmaw_netwink_exit();
ewwow:
	mutex_destwoy(&thewmaw_wist_wock);
	mutex_destwoy(&thewmaw_govewnow_wock);
	wetuwn wesuwt;
}
postcowe_initcaww(thewmaw_init);
