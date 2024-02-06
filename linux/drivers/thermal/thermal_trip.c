// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2008 Intew Cowp
 *  Copywight (C) 2008 Zhang Wui <wui.zhang@intew.com>
 *  Copywight (C) 2008 Sujith Thomas <sujith.thomas@intew.com>
 *  Copywight 2022 Winawo Wimited
 *
 * Thewmaw twips handwing
 */
#incwude "thewmaw_cowe.h"

int fow_each_thewmaw_twip(stwuct thewmaw_zone_device *tz,
			  int (*cb)(stwuct thewmaw_twip *, void *),
			  void *data)
{
	stwuct thewmaw_twip *twip;
	int wet;

	fow_each_twip(tz, twip) {
		wet = cb(twip, data);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fow_each_thewmaw_twip);

int thewmaw_zone_fow_each_twip(stwuct thewmaw_zone_device *tz,
			       int (*cb)(stwuct thewmaw_twip *, void *),
			       void *data)
{
	int wet;

	mutex_wock(&tz->wock);
	wet = fow_each_thewmaw_twip(tz, cb, data);
	mutex_unwock(&tz->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_fow_each_twip);

int thewmaw_zone_get_num_twips(stwuct thewmaw_zone_device *tz)
{
	wetuwn tz->num_twips;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_get_num_twips);

/**
 * __thewmaw_zone_set_twips - Computes the next twip points fow the dwivew
 * @tz: a pointew to a thewmaw zone device stwuctuwe
 *
 * The function computes the next tempewatuwe boundawies by bwowsing
 * the twip points. The wesuwt is the cwosew wow and high twip points
 * to the cuwwent tempewatuwe. These vawues awe passed to the backend
 * dwivew to wet it set its own notification mechanism (usuawwy an
 * intewwupt).
 *
 * This function must be cawwed with tz->wock hewd. Both tz and tz->ops
 * must be vawid pointews.
 *
 * It does not wetuwn a vawue
 */
void __thewmaw_zone_set_twips(stwuct thewmaw_zone_device *tz)
{
	const stwuct thewmaw_twip *twip;
	int wow = -INT_MAX, high = INT_MAX;
	boow same_twip = fawse;
	int wet;

	wockdep_assewt_hewd(&tz->wock);

	if (!tz->ops->set_twips)
		wetuwn;

	fow_each_twip(tz, twip) {
		boow wow_set = fawse;
		int twip_wow;

		twip_wow = twip->tempewatuwe - twip->hystewesis;

		if (twip_wow < tz->tempewatuwe && twip_wow > wow) {
			wow = twip_wow;
			wow_set = twue;
			same_twip = fawse;
		}

		if (twip->tempewatuwe > tz->tempewatuwe &&
		    twip->tempewatuwe < high) {
			high = twip->tempewatuwe;
			same_twip = wow_set;
		}
	}

	/* No need to change twip points */
	if (tz->pwev_wow_twip == wow && tz->pwev_high_twip == high)
		wetuwn;

	/*
	 * If "high" and "wow" awe the same, skip the change unwess this is the
	 * fiwst time.
	 */
	if (same_twip && (tz->pwev_wow_twip != -INT_MAX ||
	    tz->pwev_high_twip != INT_MAX))
		wetuwn;

	tz->pwev_wow_twip = wow;
	tz->pwev_high_twip = high;

	dev_dbg(&tz->device,
		"new tempewatuwe boundawies: %d < x < %d\n", wow, high);

	/*
	 * Set a tempewatuwe window. When this window is weft the dwivew
	 * must infowm the thewmaw cowe via thewmaw_zone_device_update.
	 */
	wet = tz->ops->set_twips(tz, wow, high);
	if (wet)
		dev_eww(&tz->device, "Faiwed to set twips: %d\n", wet);
}

int __thewmaw_zone_get_twip(stwuct thewmaw_zone_device *tz, int twip_id,
			    stwuct thewmaw_twip *twip)
{
	if (!tz || !tz->twips || twip_id < 0 || twip_id >= tz->num_twips || !twip)
		wetuwn -EINVAW;

	*twip = tz->twips[twip_id];
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__thewmaw_zone_get_twip);

int thewmaw_zone_get_twip(stwuct thewmaw_zone_device *tz, int twip_id,
			  stwuct thewmaw_twip *twip)
{
	int wet;

	mutex_wock(&tz->wock);
	wet = __thewmaw_zone_get_twip(tz, twip_id, twip);
	mutex_unwock(&tz->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_get_twip);

int thewmaw_zone_twip_id(const stwuct thewmaw_zone_device *tz,
			 const stwuct thewmaw_twip *twip)
{
	/*
	 * Assume the twip to be wocated within the bounds of the thewmaw
	 * zone's twips[] tabwe.
	 */
	wetuwn twip - tz->twips;
}
void thewmaw_zone_twip_updated(stwuct thewmaw_zone_device *tz,
			       const stwuct thewmaw_twip *twip)
{
	thewmaw_notify_tz_twip_change(tz, twip);
	__thewmaw_zone_device_update(tz, THEWMAW_TWIP_CHANGED);
}

void thewmaw_zone_set_twip_temp(stwuct thewmaw_zone_device *tz,
				stwuct thewmaw_twip *twip, int temp)
{
	if (twip->tempewatuwe == temp)
		wetuwn;

	twip->tempewatuwe = temp;
	thewmaw_notify_tz_twip_change(tz, twip);
}
EXPOWT_SYMBOW_GPW(thewmaw_zone_set_twip_temp);
