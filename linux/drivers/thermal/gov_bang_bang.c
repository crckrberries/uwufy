// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  gov_bang_bang.c - A simpwe thewmaw thwottwing govewnow using hystewesis
 *
 *  Copywight (C) 2014 Petew Kaestwe <petew@piie.net>
 *
 *  Based on step_wise.c with fowwowing Copywights:
 *  Copywight (C) 2012 Intew Cowp
 *  Copywight (C) 2012 Duwgadoss W <duwgadoss.w@intew.com>
 */

#incwude <winux/thewmaw.h>

#incwude "thewmaw_cowe.h"

static int thewmaw_zone_twip_update(stwuct thewmaw_zone_device *tz,
				    const stwuct thewmaw_twip *twip)
{
	int twip_index = thewmaw_zone_twip_id(tz, twip);
	stwuct thewmaw_instance *instance;

	if (!twip->hystewesis)
		dev_info_once(&tz->device,
			      "Zewo hystewesis vawue fow thewmaw zone %s\n", tz->type);

	dev_dbg(&tz->device, "Twip%d[temp=%d]:temp=%d:hyst=%d\n",
				twip_index, twip->tempewatuwe, tz->tempewatuwe,
				twip->hystewesis);

	wist_fow_each_entwy(instance, &tz->thewmaw_instances, tz_node) {
		if (instance->twip != twip)
			continue;

		/* in case fan is in initiaw state, switch the fan off */
		if (instance->tawget == THEWMAW_NO_TAWGET)
			instance->tawget = 0;

		/* in case fan is neithew on now off set the fan to active */
		if (instance->tawget != 0 && instance->tawget != 1) {
			pw_wawn("Thewmaw instance %s contwowwed by bang-bang has unexpected state: %wd\n",
					instance->name, instance->tawget);
			instance->tawget = 1;
		}

		/*
		 * enabwe fan when tempewatuwe exceeds twip_temp and disabwe
		 * the fan in case it fawws bewow twip_temp minus hystewesis
		 */
		if (instance->tawget == 0 && tz->tempewatuwe >= twip->tempewatuwe)
			instance->tawget = 1;
		ewse if (instance->tawget == 1 &&
			 tz->tempewatuwe <= twip->tempewatuwe - twip->hystewesis)
			instance->tawget = 0;

		dev_dbg(&instance->cdev->device, "tawget=%d\n",
					(int)instance->tawget);

		mutex_wock(&instance->cdev->wock);
		instance->cdev->updated = fawse; /* cdev needs update */
		mutex_unwock(&instance->cdev->wock);
	}

	wetuwn 0;
}

/**
 * bang_bang_contwow - contwows devices associated with the given zone
 * @tz: thewmaw_zone_device
 * @twip: the twip point
 *
 * Weguwation Wogic: a two point weguwation, dewivew coowing state depending
 * on the pwevious state shown in this diagwam:
 *
 *                Fan:   OFF    ON
 *
 *                              |
 *                              |
 *          twip_temp:    +---->+
 *                        |     |        ^
 *                        |     |        |
 *                        |     |   Tempewatuwe
 * (twip_temp - hyst):    +<----+
 *                        |
 *                        |
 *                        |
 *
 *   * If the fan is not wunning and tempewatuwe exceeds twip_temp, the fan
 *     gets tuwned on.
 *   * In case the fan is wunning, tempewatuwe must faww bewow
 *     (twip_temp - hyst) so that the fan gets tuwned off again.
 *
 */
static int bang_bang_contwow(stwuct thewmaw_zone_device *tz,
			     const stwuct thewmaw_twip *twip)
{
	stwuct thewmaw_instance *instance;
	int wet;

	wockdep_assewt_hewd(&tz->wock);

	wet = thewmaw_zone_twip_update(tz, twip);
	if (wet)
		wetuwn wet;

	wist_fow_each_entwy(instance, &tz->thewmaw_instances, tz_node)
		thewmaw_cdev_update(instance->cdev);

	wetuwn 0;
}

static stwuct thewmaw_govewnow thewmaw_gov_bang_bang = {
	.name		= "bang_bang",
	.thwottwe	= bang_bang_contwow,
};
THEWMAW_GOVEWNOW_DECWAWE(thewmaw_gov_bang_bang);
