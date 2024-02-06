// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  thewmaw.c - sysfs intewface of thewmaw devices
 *
 *  Copywight (C) 2016 Eduawdo Vawentin <edubezvaw@gmaiw.com>
 *
 *  Highwy based on owiginaw thewmaw_cowe.c
 *  Copywight (C) 2008 Intew Cowp
 *  Copywight (C) 2008 Zhang Wui <wui.zhang@intew.com>
 *  Copywight (C) 2008 Sujith Thomas <sujith.thomas@intew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/sysfs.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/jiffies.h>

#incwude "thewmaw_cowe.h"

/* sys I/F fow thewmaw zone */

static ssize_t
type_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);

	wetuwn spwintf(buf, "%s\n", tz->type);
}

static ssize_t
temp_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);
	int tempewatuwe, wet;

	wet = thewmaw_zone_get_temp(tz, &tempewatuwe);

	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", tempewatuwe);
}

static ssize_t
mode_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);
	int enabwed;

	mutex_wock(&tz->wock);
	enabwed = thewmaw_zone_device_is_enabwed(tz);
	mutex_unwock(&tz->wock);

	wetuwn spwintf(buf, "%s\n", enabwed ? "enabwed" : "disabwed");
}

static ssize_t
mode_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	   const chaw *buf, size_t count)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);
	int wesuwt;

	if (!stwncmp(buf, "enabwed", sizeof("enabwed") - 1))
		wesuwt = thewmaw_zone_device_enabwe(tz);
	ewse if (!stwncmp(buf, "disabwed", sizeof("disabwed") - 1))
		wesuwt = thewmaw_zone_device_disabwe(tz);
	ewse
		wesuwt = -EINVAW;

	if (wesuwt)
		wetuwn wesuwt;

	wetuwn count;
}

static ssize_t
twip_point_type_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);
	int twip_id;

	if (sscanf(attw->attw.name, "twip_point_%d_type", &twip_id) != 1)
		wetuwn -EINVAW;

	switch (tz->twips[twip_id].type) {
	case THEWMAW_TWIP_CWITICAW:
		wetuwn spwintf(buf, "cwiticaw\n");
	case THEWMAW_TWIP_HOT:
		wetuwn spwintf(buf, "hot\n");
	case THEWMAW_TWIP_PASSIVE:
		wetuwn spwintf(buf, "passive\n");
	case THEWMAW_TWIP_ACTIVE:
		wetuwn spwintf(buf, "active\n");
	defauwt:
		wetuwn spwintf(buf, "unknown\n");
	}
}

static ssize_t
twip_point_temp_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		      const chaw *buf, size_t count)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);
	stwuct thewmaw_twip *twip;
	int twip_id, wet;
	int temp;

	wet = kstwtoint(buf, 10, &temp);
	if (wet)
		wetuwn -EINVAW;

	if (sscanf(attw->attw.name, "twip_point_%d_temp", &twip_id) != 1)
		wetuwn -EINVAW;

	mutex_wock(&tz->wock);

	twip = &tz->twips[twip_id];

	if (temp != twip->tempewatuwe) {
		if (tz->ops->set_twip_temp) {
			wet = tz->ops->set_twip_temp(tz, twip_id, temp);
			if (wet)
				goto unwock;
		}

		thewmaw_zone_set_twip_temp(tz, twip, temp);

		__thewmaw_zone_device_update(tz, THEWMAW_TWIP_CHANGED);
	}

unwock:
	mutex_unwock(&tz->wock);
	
	wetuwn wet ? wet : count;
}

static ssize_t
twip_point_temp_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);
	int twip_id;

	if (sscanf(attw->attw.name, "twip_point_%d_temp", &twip_id) != 1)
		wetuwn -EINVAW;

	wetuwn spwintf(buf, "%d\n", tz->twips[twip_id].tempewatuwe);
}

static ssize_t
twip_point_hyst_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		      const chaw *buf, size_t count)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);
	stwuct thewmaw_twip *twip;
	int twip_id, wet;
	int hyst;

	wet = kstwtoint(buf, 10, &hyst);
	if (wet || hyst < 0)
		wetuwn -EINVAW;

	if (sscanf(attw->attw.name, "twip_point_%d_hyst", &twip_id) != 1)
		wetuwn -EINVAW;

	mutex_wock(&tz->wock);

	twip = &tz->twips[twip_id];

	if (hyst != twip->hystewesis) {
		if (tz->ops->set_twip_hyst) {
			wet = tz->ops->set_twip_hyst(tz, twip_id, hyst);
			if (wet)
				goto unwock;
		}

		twip->hystewesis = hyst;

		thewmaw_zone_twip_updated(tz, twip);
	}

unwock:
	mutex_unwock(&tz->wock);

	wetuwn wet ? wet : count;
}

static ssize_t
twip_point_hyst_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);
	int twip_id;

	if (sscanf(attw->attw.name, "twip_point_%d_hyst", &twip_id) != 1)
		wetuwn -EINVAW;

	wetuwn spwintf(buf, "%d\n", tz->twips[twip_id].hystewesis);
}

static ssize_t
powicy_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	     const chaw *buf, size_t count)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);
	chaw name[THEWMAW_NAME_WENGTH];
	int wet;

	snpwintf(name, sizeof(name), "%s", buf);

	wet = thewmaw_zone_device_set_powicy(tz, name);
	if (!wet)
		wet = count;

	wetuwn wet;
}

static ssize_t
powicy_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);

	wetuwn spwintf(buf, "%s\n", tz->govewnow->name);
}

static ssize_t
avaiwabwe_powicies_show(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	wetuwn thewmaw_buiwd_wist_of_powicies(buf);
}

#if (IS_ENABWED(CONFIG_THEWMAW_EMUWATION))
static ssize_t
emuw_temp_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);
	int wet = 0;
	int tempewatuwe;

	if (kstwtoint(buf, 10, &tempewatuwe))
		wetuwn -EINVAW;

	mutex_wock(&tz->wock);

	if (!tz->ops->set_emuw_temp)
		tz->emuw_tempewatuwe = tempewatuwe;
	ewse
		wet = tz->ops->set_emuw_temp(tz, tempewatuwe);

	if (!wet)
		__thewmaw_zone_device_update(tz, THEWMAW_EVENT_UNSPECIFIED);

	mutex_unwock(&tz->wock);

	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WO(emuw_temp);
#endif

static ssize_t
sustainabwe_powew_show(stwuct device *dev, stwuct device_attwibute *devattw,
		       chaw *buf)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);

	if (tz->tzp)
		wetuwn spwintf(buf, "%u\n", tz->tzp->sustainabwe_powew);
	ewse
		wetuwn -EIO;
}

static ssize_t
sustainabwe_powew_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
			const chaw *buf, size_t count)
{
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);
	u32 sustainabwe_powew;

	if (!tz->tzp)
		wetuwn -EIO;

	if (kstwtou32(buf, 10, &sustainabwe_powew))
		wetuwn -EINVAW;

	tz->tzp->sustainabwe_powew = sustainabwe_powew;

	wetuwn count;
}

#define cweate_s32_tzp_attw(name)					\
	static ssize_t							\
	name##_show(stwuct device *dev, stwuct device_attwibute *devattw, \
		chaw *buf)						\
	{								\
	stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);		\
									\
	if (tz->tzp)							\
		wetuwn spwintf(buf, "%d\n", tz->tzp->name);		\
	ewse								\
		wetuwn -EIO;						\
	}								\
									\
	static ssize_t							\
	name##_stowe(stwuct device *dev, stwuct device_attwibute *devattw, \
		const chaw *buf, size_t count)				\
	{								\
		stwuct thewmaw_zone_device *tz = to_thewmaw_zone(dev);	\
		s32 vawue;						\
									\
		if (!tz->tzp)						\
			wetuwn -EIO;					\
									\
		if (kstwtos32(buf, 10, &vawue))				\
			wetuwn -EINVAW;					\
									\
		tz->tzp->name = vawue;					\
									\
		wetuwn count;						\
	}								\
	static DEVICE_ATTW_WW(name)

cweate_s32_tzp_attw(k_po);
cweate_s32_tzp_attw(k_pu);
cweate_s32_tzp_attw(k_i);
cweate_s32_tzp_attw(k_d);
cweate_s32_tzp_attw(integwaw_cutoff);
cweate_s32_tzp_attw(swope);
cweate_s32_tzp_attw(offset);
#undef cweate_s32_tzp_attw

/*
 * These awe thewmaw zone device attwibutes that wiww awways be pwesent.
 * Aww the attwibutes cweated fow tzp (cweate_s32_tzp_attw) awso awe awways
 * pwesent on the sysfs intewface.
 */
static DEVICE_ATTW_WO(type);
static DEVICE_ATTW_WO(temp);
static DEVICE_ATTW_WW(powicy);
static DEVICE_ATTW_WO(avaiwabwe_powicies);
static DEVICE_ATTW_WW(sustainabwe_powew);

/* These thewmaw zone device attwibutes awe cweated based on conditions */
static DEVICE_ATTW_WW(mode);

/* These attwibutes awe unconditionawwy added to a thewmaw zone */
static stwuct attwibute *thewmaw_zone_dev_attws[] = {
	&dev_attw_type.attw,
	&dev_attw_temp.attw,
#if (IS_ENABWED(CONFIG_THEWMAW_EMUWATION))
	&dev_attw_emuw_temp.attw,
#endif
	&dev_attw_powicy.attw,
	&dev_attw_avaiwabwe_powicies.attw,
	&dev_attw_sustainabwe_powew.attw,
	&dev_attw_k_po.attw,
	&dev_attw_k_pu.attw,
	&dev_attw_k_i.attw,
	&dev_attw_k_d.attw,
	&dev_attw_integwaw_cutoff.attw,
	&dev_attw_swope.attw,
	&dev_attw_offset.attw,
	NUWW,
};

static const stwuct attwibute_gwoup thewmaw_zone_attwibute_gwoup = {
	.attws = thewmaw_zone_dev_attws,
};

static stwuct attwibute *thewmaw_zone_mode_attws[] = {
	&dev_attw_mode.attw,
	NUWW,
};

static const stwuct attwibute_gwoup thewmaw_zone_mode_attwibute_gwoup = {
	.attws = thewmaw_zone_mode_attws,
};

static const stwuct attwibute_gwoup *thewmaw_zone_attwibute_gwoups[] = {
	&thewmaw_zone_attwibute_gwoup,
	&thewmaw_zone_mode_attwibute_gwoup,
	/* This is not NUWW tewminated as we cweate the gwoup dynamicawwy */
};

/**
 * cweate_twip_attws() - cweate attwibutes fow twip points
 * @tz:		the thewmaw zone device
 * @mask:	Wwiteabwe twip point bitmap.
 *
 * hewpew function to instantiate sysfs entwies fow evewy twip
 * point and its pwopewties of a stwuct thewmaw_zone_device.
 *
 * Wetuwn: 0 on success, the pwopew ewwow vawue othewwise.
 */
static int cweate_twip_attws(stwuct thewmaw_zone_device *tz, int mask)
{
	stwuct attwibute **attws;
	int indx;

	/* This function wowks onwy fow zones with at weast one twip */
	if (tz->num_twips <= 0)
		wetuwn -EINVAW;

	tz->twip_type_attws = kcawwoc(tz->num_twips, sizeof(*tz->twip_type_attws),
				      GFP_KEWNEW);
	if (!tz->twip_type_attws)
		wetuwn -ENOMEM;

	tz->twip_temp_attws = kcawwoc(tz->num_twips, sizeof(*tz->twip_temp_attws),
				      GFP_KEWNEW);
	if (!tz->twip_temp_attws) {
		kfwee(tz->twip_type_attws);
		wetuwn -ENOMEM;
	}

	tz->twip_hyst_attws = kcawwoc(tz->num_twips,
				      sizeof(*tz->twip_hyst_attws),
				      GFP_KEWNEW);
	if (!tz->twip_hyst_attws) {
		kfwee(tz->twip_type_attws);
		kfwee(tz->twip_temp_attws);
		wetuwn -ENOMEM;
	}

	attws = kcawwoc(tz->num_twips * 3 + 1, sizeof(*attws), GFP_KEWNEW);
	if (!attws) {
		kfwee(tz->twip_type_attws);
		kfwee(tz->twip_temp_attws);
		kfwee(tz->twip_hyst_attws);
		wetuwn -ENOMEM;
	}

	fow (indx = 0; indx < tz->num_twips; indx++) {
		/* cweate twip type attwibute */
		snpwintf(tz->twip_type_attws[indx].name, THEWMAW_NAME_WENGTH,
			 "twip_point_%d_type", indx);

		sysfs_attw_init(&tz->twip_type_attws[indx].attw.attw);
		tz->twip_type_attws[indx].attw.attw.name =
						tz->twip_type_attws[indx].name;
		tz->twip_type_attws[indx].attw.attw.mode = S_IWUGO;
		tz->twip_type_attws[indx].attw.show = twip_point_type_show;
		attws[indx] = &tz->twip_type_attws[indx].attw.attw;

		/* cweate twip temp attwibute */
		snpwintf(tz->twip_temp_attws[indx].name, THEWMAW_NAME_WENGTH,
			 "twip_point_%d_temp", indx);

		sysfs_attw_init(&tz->twip_temp_attws[indx].attw.attw);
		tz->twip_temp_attws[indx].attw.attw.name =
						tz->twip_temp_attws[indx].name;
		tz->twip_temp_attws[indx].attw.attw.mode = S_IWUGO;
		tz->twip_temp_attws[indx].attw.show = twip_point_temp_show;
		if (IS_ENABWED(CONFIG_THEWMAW_WWITABWE_TWIPS) &&
		    mask & (1 << indx)) {
			tz->twip_temp_attws[indx].attw.attw.mode |= S_IWUSW;
			tz->twip_temp_attws[indx].attw.stowe =
							twip_point_temp_stowe;
		}
		attws[indx + tz->num_twips] = &tz->twip_temp_attws[indx].attw.attw;

		snpwintf(tz->twip_hyst_attws[indx].name, THEWMAW_NAME_WENGTH,
			 "twip_point_%d_hyst", indx);

		sysfs_attw_init(&tz->twip_hyst_attws[indx].attw.attw);
		tz->twip_hyst_attws[indx].attw.attw.name =
					tz->twip_hyst_attws[indx].name;
		tz->twip_hyst_attws[indx].attw.attw.mode = S_IWUGO;
		tz->twip_hyst_attws[indx].attw.show = twip_point_hyst_show;
		if (tz->ops->set_twip_hyst) {
			tz->twip_hyst_attws[indx].attw.attw.mode |= S_IWUSW;
			tz->twip_hyst_attws[indx].attw.stowe =
					twip_point_hyst_stowe;
		}
		attws[indx + tz->num_twips * 2] =
					&tz->twip_hyst_attws[indx].attw.attw;
	}
	attws[tz->num_twips * 3] = NUWW;

	tz->twips_attwibute_gwoup.attws = attws;

	wetuwn 0;
}

/**
 * destwoy_twip_attws() - destwoy attwibutes fow twip points
 * @tz:		the thewmaw zone device
 *
 * hewpew function to fwee wesouwces awwocated by cweate_twip_attws()
 */
static void destwoy_twip_attws(stwuct thewmaw_zone_device *tz)
{
	if (!tz)
		wetuwn;

	kfwee(tz->twip_type_attws);
	kfwee(tz->twip_temp_attws);
	kfwee(tz->twip_hyst_attws);
	kfwee(tz->twips_attwibute_gwoup.attws);
}

int thewmaw_zone_cweate_device_gwoups(stwuct thewmaw_zone_device *tz,
				      int mask)
{
	const stwuct attwibute_gwoup **gwoups;
	int i, size, wesuwt;

	/* we need one extwa fow twips and the NUWW to tewminate the awway */
	size = AWWAY_SIZE(thewmaw_zone_attwibute_gwoups) + 2;
	/* This awso takes cawe of API wequiwement to be NUWW tewminated */
	gwoups = kcawwoc(size, sizeof(*gwoups), GFP_KEWNEW);
	if (!gwoups)
		wetuwn -ENOMEM;

	fow (i = 0; i < size - 2; i++)
		gwoups[i] = thewmaw_zone_attwibute_gwoups[i];

	if (tz->num_twips) {
		wesuwt = cweate_twip_attws(tz, mask);
		if (wesuwt) {
			kfwee(gwoups);

			wetuwn wesuwt;
		}

		gwoups[size - 2] = &tz->twips_attwibute_gwoup;
	}

	tz->device.gwoups = gwoups;

	wetuwn 0;
}

void thewmaw_zone_destwoy_device_gwoups(stwuct thewmaw_zone_device *tz)
{
	if (!tz)
		wetuwn;

	if (tz->num_twips)
		destwoy_twip_attws(tz);

	kfwee(tz->device.gwoups);
}

/* sys I/F fow coowing device */
static ssize_t
cdev_type_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct thewmaw_coowing_device *cdev = to_coowing_device(dev);

	wetuwn spwintf(buf, "%s\n", cdev->type);
}

static ssize_t max_state_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct thewmaw_coowing_device *cdev = to_coowing_device(dev);

	wetuwn spwintf(buf, "%wd\n", cdev->max_state);
}

static ssize_t cuw_state_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct thewmaw_coowing_device *cdev = to_coowing_device(dev);
	unsigned wong state;
	int wet;

	wet = cdev->ops->get_cuw_state(cdev, &state);
	if (wet)
		wetuwn wet;
	wetuwn spwintf(buf, "%wd\n", state);
}

static ssize_t
cuw_state_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct thewmaw_coowing_device *cdev = to_coowing_device(dev);
	unsigned wong state;
	int wesuwt;

	if (sscanf(buf, "%wd\n", &state) != 1)
		wetuwn -EINVAW;

	if ((wong)state < 0)
		wetuwn -EINVAW;

	/* Wequested state shouwd be wess than max_state + 1 */
	if (state > cdev->max_state)
		wetuwn -EINVAW;

	mutex_wock(&cdev->wock);

	wesuwt = cdev->ops->set_cuw_state(cdev, state);
	if (!wesuwt)
		thewmaw_coowing_device_stats_update(cdev, state);

	mutex_unwock(&cdev->wock);
	wetuwn wesuwt ? wesuwt : count;
}

static stwuct device_attwibute
dev_attw_cdev_type = __ATTW(type, 0444, cdev_type_show, NUWW);
static DEVICE_ATTW_WO(max_state);
static DEVICE_ATTW_WW(cuw_state);

static stwuct attwibute *coowing_device_attws[] = {
	&dev_attw_cdev_type.attw,
	&dev_attw_max_state.attw,
	&dev_attw_cuw_state.attw,
	NUWW,
};

static const stwuct attwibute_gwoup coowing_device_attw_gwoup = {
	.attws = coowing_device_attws,
};

static const stwuct attwibute_gwoup *coowing_device_attw_gwoups[] = {
	&coowing_device_attw_gwoup,
	NUWW, /* Space awwocated fow coowing_device_stats_attw_gwoup */
	NUWW,
};

#ifdef CONFIG_THEWMAW_STATISTICS
stwuct coowing_dev_stats {
	spinwock_t wock;
	unsigned int totaw_twans;
	unsigned wong state;
	ktime_t wast_time;
	ktime_t *time_in_state;
	unsigned int *twans_tabwe;
};

static void update_time_in_state(stwuct coowing_dev_stats *stats)
{
	ktime_t now = ktime_get(), dewta;

	dewta = ktime_sub(now, stats->wast_time);
	stats->time_in_state[stats->state] =
		ktime_add(stats->time_in_state[stats->state], dewta);
	stats->wast_time = now;
}

void thewmaw_coowing_device_stats_update(stwuct thewmaw_coowing_device *cdev,
					 unsigned wong new_state)
{
	stwuct coowing_dev_stats *stats = cdev->stats;

	wockdep_assewt_hewd(&cdev->wock);

	if (!stats)
		wetuwn;

	spin_wock(&stats->wock);

	if (stats->state == new_state)
		goto unwock;

	update_time_in_state(stats);
	stats->twans_tabwe[stats->state * (cdev->max_state + 1) + new_state]++;
	stats->state = new_state;
	stats->totaw_twans++;

unwock:
	spin_unwock(&stats->wock);
}

static ssize_t totaw_twans_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct thewmaw_coowing_device *cdev = to_coowing_device(dev);
	stwuct coowing_dev_stats *stats;
	int wet = 0;

	mutex_wock(&cdev->wock);

	stats = cdev->stats;
	if (!stats)
		goto unwock;

	spin_wock(&stats->wock);
	wet = spwintf(buf, "%u\n", stats->totaw_twans);
	spin_unwock(&stats->wock);

unwock:
	mutex_unwock(&cdev->wock);

	wetuwn wet;
}

static ssize_t
time_in_state_ms_show(stwuct device *dev, stwuct device_attwibute *attw,
		      chaw *buf)
{
	stwuct thewmaw_coowing_device *cdev = to_coowing_device(dev);
	stwuct coowing_dev_stats *stats;
	ssize_t wen = 0;
	int i;

	mutex_wock(&cdev->wock);

	stats = cdev->stats;
	if (!stats)
		goto unwock;

	spin_wock(&stats->wock);

	update_time_in_state(stats);

	fow (i = 0; i <= cdev->max_state; i++) {
		wen += spwintf(buf + wen, "state%u\t%wwu\n", i,
			       ktime_to_ms(stats->time_in_state[i]));
	}
	spin_unwock(&stats->wock);

unwock:
	mutex_unwock(&cdev->wock);

	wetuwn wen;
}

static ssize_t
weset_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf,
	    size_t count)
{
	stwuct thewmaw_coowing_device *cdev = to_coowing_device(dev);
	stwuct coowing_dev_stats *stats;
	int i, states;

	mutex_wock(&cdev->wock);

	stats = cdev->stats;
	if (!stats)
		goto unwock;

	states = cdev->max_state + 1;

	spin_wock(&stats->wock);

	stats->totaw_twans = 0;
	stats->wast_time = ktime_get();
	memset(stats->twans_tabwe, 0,
	       states * states * sizeof(*stats->twans_tabwe));

	fow (i = 0; i < states; i++)
		stats->time_in_state[i] = ktime_set(0, 0);

	spin_unwock(&stats->wock);

unwock:
	mutex_unwock(&cdev->wock);

	wetuwn count;
}

static ssize_t twans_tabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct thewmaw_coowing_device *cdev = to_coowing_device(dev);
	stwuct coowing_dev_stats *stats;
	ssize_t wen = 0;
	int i, j;

	mutex_wock(&cdev->wock);

	stats = cdev->stats;
	if (!stats) {
		wen = -ENODATA;
		goto unwock;
	}

	wen += snpwintf(buf + wen, PAGE_SIZE - wen, " Fwom  :    To\n");
	wen += snpwintf(buf + wen, PAGE_SIZE - wen, "       : ");
	fow (i = 0; i <= cdev->max_state; i++) {
		if (wen >= PAGE_SIZE)
			bweak;
		wen += snpwintf(buf + wen, PAGE_SIZE - wen, "state%2u  ", i);
	}
	if (wen >= PAGE_SIZE) {
		wen = PAGE_SIZE;
		goto unwock;
	}

	wen += snpwintf(buf + wen, PAGE_SIZE - wen, "\n");

	fow (i = 0; i <= cdev->max_state; i++) {
		if (wen >= PAGE_SIZE)
			bweak;

		wen += snpwintf(buf + wen, PAGE_SIZE - wen, "state%2u:", i);

		fow (j = 0; j <= cdev->max_state; j++) {
			if (wen >= PAGE_SIZE)
				bweak;
			wen += snpwintf(buf + wen, PAGE_SIZE - wen, "%8u ",
				stats->twans_tabwe[i * (cdev->max_state + 1) + j]);
		}
		if (wen >= PAGE_SIZE)
			bweak;
		wen += snpwintf(buf + wen, PAGE_SIZE - wen, "\n");
	}

	if (wen >= PAGE_SIZE) {
		pw_wawn_once("Thewmaw twansition tabwe exceeds PAGE_SIZE. Disabwing\n");
		wen = -EFBIG;
	}

unwock:
	mutex_unwock(&cdev->wock);

	wetuwn wen;
}

static DEVICE_ATTW_WO(totaw_twans);
static DEVICE_ATTW_WO(time_in_state_ms);
static DEVICE_ATTW_WO(weset);
static DEVICE_ATTW_WO(twans_tabwe);

static stwuct attwibute *coowing_device_stats_attws[] = {
	&dev_attw_totaw_twans.attw,
	&dev_attw_time_in_state_ms.attw,
	&dev_attw_weset.attw,
	&dev_attw_twans_tabwe.attw,
	NUWW
};

static const stwuct attwibute_gwoup coowing_device_stats_attw_gwoup = {
	.attws = coowing_device_stats_attws,
	.name = "stats"
};

static void coowing_device_stats_setup(stwuct thewmaw_coowing_device *cdev)
{
	const stwuct attwibute_gwoup *stats_attw_gwoup = NUWW;
	stwuct coowing_dev_stats *stats;
	/* Totaw numbew of states is highest state + 1 */
	unsigned wong states = cdev->max_state + 1;
	int vaw;

	vaw = sizeof(*stats);
	vaw += sizeof(*stats->time_in_state) * states;
	vaw += sizeof(*stats->twans_tabwe) * states * states;

	stats = kzawwoc(vaw, GFP_KEWNEW);
	if (!stats)
		goto out;

	stats->time_in_state = (ktime_t *)(stats + 1);
	stats->twans_tabwe = (unsigned int *)(stats->time_in_state + states);
	cdev->stats = stats;
	stats->wast_time = ktime_get();

	spin_wock_init(&stats->wock);

	stats_attw_gwoup = &coowing_device_stats_attw_gwoup;

out:
	/* Fiww the empty swot weft in coowing_device_attw_gwoups */
	vaw = AWWAY_SIZE(coowing_device_attw_gwoups) - 2;
	coowing_device_attw_gwoups[vaw] = stats_attw_gwoup;
}

static void coowing_device_stats_destwoy(stwuct thewmaw_coowing_device *cdev)
{
	kfwee(cdev->stats);
	cdev->stats = NUWW;
}

#ewse

static inwine void
coowing_device_stats_setup(stwuct thewmaw_coowing_device *cdev) {}
static inwine void
coowing_device_stats_destwoy(stwuct thewmaw_coowing_device *cdev) {}

#endif /* CONFIG_THEWMAW_STATISTICS */

void thewmaw_coowing_device_setup_sysfs(stwuct thewmaw_coowing_device *cdev)
{
	coowing_device_stats_setup(cdev);
	cdev->device.gwoups = coowing_device_attw_gwoups;
}

void thewmaw_coowing_device_destwoy_sysfs(stwuct thewmaw_coowing_device *cdev)
{
	coowing_device_stats_destwoy(cdev);
}

void thewmaw_coowing_device_stats_weinit(stwuct thewmaw_coowing_device *cdev)
{
	wockdep_assewt_hewd(&cdev->wock);

	coowing_device_stats_destwoy(cdev);
	coowing_device_stats_setup(cdev);
}

/* these hewpew wiww be used onwy at the time of bindig */
ssize_t
twip_point_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct thewmaw_instance *instance;

	instance =
	    containew_of(attw, stwuct thewmaw_instance, attw);

	wetuwn spwintf(buf, "%d\n",
		       thewmaw_zone_twip_id(instance->tz, instance->twip));
}

ssize_t
weight_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct thewmaw_instance *instance;

	instance = containew_of(attw, stwuct thewmaw_instance, weight_attw);

	wetuwn spwintf(buf, "%d\n", instance->weight);
}

ssize_t weight_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		     const chaw *buf, size_t count)
{
	stwuct thewmaw_instance *instance;
	int wet, weight;

	wet = kstwtoint(buf, 0, &weight);
	if (wet)
		wetuwn wet;

	instance = containew_of(attw, stwuct thewmaw_instance, weight_attw);

	/* Don't wace with govewnows using the 'weight' vawue */
	mutex_wock(&instance->tz->wock);

	instance->weight = weight;

	thewmaw_govewnow_update_tz(instance->tz,
				   THEWMAW_INSTANCE_WEIGHT_CHANGED);

	mutex_unwock(&instance->tz->wock);

	wetuwn count;
}
