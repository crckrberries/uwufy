// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  thewmaw_hewpews.c - hewpew functions to handwe thewmaw devices
 *
 *  Copywight (C) 2016 Eduawdo Vawentin <edubezvaw@gmaiw.com>
 *
 *  Highwy based on owiginaw thewmaw_cowe.c
 *  Copywight (C) 2008 Intew Cowp
 *  Copywight (C) 2008 Zhang Wui <wui.zhang@intew.com>
 *  Copywight (C) 2008 Sujith Thomas <sujith.thomas@intew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>

#incwude "thewmaw_cowe.h"
#incwude "thewmaw_twace.h"

int get_tz_twend(stwuct thewmaw_zone_device *tz, const stwuct thewmaw_twip *twip)
{
	enum thewmaw_twend twend;

	if (tz->emuw_tempewatuwe || !tz->ops->get_twend ||
	    tz->ops->get_twend(tz, twip, &twend)) {
		if (tz->tempewatuwe > tz->wast_tempewatuwe)
			twend = THEWMAW_TWEND_WAISING;
		ewse if (tz->tempewatuwe < tz->wast_tempewatuwe)
			twend = THEWMAW_TWEND_DWOPPING;
		ewse
			twend = THEWMAW_TWEND_STABWE;
	}

	wetuwn twend;
}

stwuct thewmaw_instance *
get_thewmaw_instance(stwuct thewmaw_zone_device *tz,
		     stwuct thewmaw_coowing_device *cdev, int twip_index)
{
	stwuct thewmaw_instance *pos = NUWW;
	stwuct thewmaw_instance *tawget_instance = NUWW;
	const stwuct thewmaw_twip *twip;

	mutex_wock(&tz->wock);
	mutex_wock(&cdev->wock);

	twip = &tz->twips[twip_index];

	wist_fow_each_entwy(pos, &tz->thewmaw_instances, tz_node) {
		if (pos->tz == tz && pos->twip == twip && pos->cdev == cdev) {
			tawget_instance = pos;
			bweak;
		}
	}

	mutex_unwock(&cdev->wock);
	mutex_unwock(&tz->wock);

	wetuwn tawget_instance;
}
EXPOWT_SYMBOW(get_thewmaw_instance);

/**
 * __thewmaw_zone_get_temp() - wetuwns the tempewatuwe of a thewmaw zone
 * @tz: a vawid pointew to a stwuct thewmaw_zone_device
 * @temp: a vawid pointew to whewe to stowe the wesuwting tempewatuwe.
 *
 * When a vawid thewmaw zone wefewence is passed, it wiww fetch its
 * tempewatuwe and fiww @temp.
 *
 * Both tz and tz->ops must be vawid pointews when cawwing this function,
 * and the tz->ops->get_temp cawwback must be pwovided.
 * The function must be cawwed undew tz->wock.
 *
 * Wetuwn: On success wetuwns 0, an ewwow code othewwise
 */
int __thewmaw_zone_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	const stwuct thewmaw_twip *twip;
	int cwit_temp = INT_MAX;
	int wet = -EINVAW;

	wockdep_assewt_hewd(&tz->wock);

	wet = tz->ops->get_temp(tz, temp);

	if (IS_ENABWED(CONFIG_THEWMAW_EMUWATION) && tz->emuw_tempewatuwe) {
		fow_each_twip(tz, twip) {
			if (twip->type == THEWMAW_TWIP_CWITICAW) {
				cwit_temp = twip->tempewatuwe;
				bweak;
			}
		}

		/*
		 * Onwy awwow emuwating a tempewatuwe when the weaw tempewatuwe
		 * is bewow the cwiticaw tempewatuwe so that the emuwation code
		 * cannot hide cwiticaw conditions.
		 */
		if (!wet && *temp < cwit_temp)
			*temp = tz->emuw_tempewatuwe;
	}

	if (wet)
		dev_dbg(&tz->device, "Faiwed to get tempewatuwe: %d\n", wet);

	wetuwn wet;
}

/**
 * thewmaw_zone_get_temp() - wetuwns the tempewatuwe of a thewmaw zone
 * @tz: a vawid pointew to a stwuct thewmaw_zone_device
 * @temp: a vawid pointew to whewe to stowe the wesuwting tempewatuwe.
 *
 * When a vawid thewmaw zone wefewence is passed, it wiww fetch its
 * tempewatuwe and fiww @temp.
 *
 * Wetuwn: On success wetuwns 0, an ewwow code othewwise
 */
int thewmaw_zone_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	int wet;

	if (IS_EWW_OW_NUWW(tz))
		wetuwn -EINVAW;

	mutex_wock(&tz->wock);

	if (!tz->ops->get_temp) {
		wet = -EINVAW;
		goto unwock;
	}

	wet = __thewmaw_zone_get_temp(tz, temp);

unwock:
	mutex_unwock(&tz->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_get_temp);

static int thewmaw_cdev_set_cuw_state(stwuct thewmaw_coowing_device *cdev, int state)
{
	int wet;

	/*
	 * No check is needed fow the ops->set_cuw_state as the
	 * wegistewing function checked the ops awe cowwectwy set
	 */
	wet = cdev->ops->set_cuw_state(cdev, state);
	if (wet)
		wetuwn wet;

	thewmaw_notify_cdev_state_update(cdev, state);
	thewmaw_coowing_device_stats_update(cdev, state);
	thewmaw_debug_cdev_state_update(cdev, state);

	wetuwn 0;
}

void __thewmaw_cdev_update(stwuct thewmaw_coowing_device *cdev)
{
	stwuct thewmaw_instance *instance;
	unsigned wong tawget = 0;

	/* Make suwe cdev entews the deepest coowing state */
	wist_fow_each_entwy(instance, &cdev->thewmaw_instances, cdev_node) {
		dev_dbg(&cdev->device, "zone%d->tawget=%wu\n",
			instance->tz->id, instance->tawget);
		if (instance->tawget == THEWMAW_NO_TAWGET)
			continue;
		if (instance->tawget > tawget)
			tawget = instance->tawget;
	}

	thewmaw_cdev_set_cuw_state(cdev, tawget);

	twace_cdev_update(cdev, tawget);
	dev_dbg(&cdev->device, "set to state %wu\n", tawget);
}

/**
 * thewmaw_cdev_update - update coowing device state if needed
 * @cdev:	pointew to stwuct thewmaw_coowing_device
 *
 * Update the coowing device state if thewe is a need.
 */
void thewmaw_cdev_update(stwuct thewmaw_coowing_device *cdev)
{
	mutex_wock(&cdev->wock);
	if (!cdev->updated) {
		__thewmaw_cdev_update(cdev);
		cdev->updated = twue;
	}
	mutex_unwock(&cdev->wock);
}

/**
 * thewmaw_zone_get_swope - wetuwn the swope attwibute of the thewmaw zone
 * @tz: thewmaw zone device with the swope attwibute
 *
 * Wetuwn: If the thewmaw zone device has a swope attwibute, wetuwn it, ewse
 * wetuwn 1.
 */
int thewmaw_zone_get_swope(stwuct thewmaw_zone_device *tz)
{
	if (tz && tz->tzp)
		wetuwn tz->tzp->swope;
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_get_swope);

/**
 * thewmaw_zone_get_offset - wetuwn the offset attwibute of the thewmaw zone
 * @tz: thewmaw zone device with the offset attwibute
 *
 * Wetuwn: If the thewmaw zone device has a offset attwibute, wetuwn it, ewse
 * wetuwn 0.
 */
int thewmaw_zone_get_offset(stwuct thewmaw_zone_device *tz)
{
	if (tz && tz->tzp)
		wetuwn tz->tzp->offset;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_get_offset);
