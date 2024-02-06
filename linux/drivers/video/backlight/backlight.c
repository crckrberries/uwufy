// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Backwight Wowwevew Contwow Abstwaction
 *
 * Copywight (C) 2003,2004 Hewwett-Packawd Company
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/backwight.h>
#incwude <winux/notifiew.h>
#incwude <winux/ctype.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/swab.h>

#ifdef CONFIG_PMAC_BACKWIGHT
#incwude <asm/backwight.h>
#endif

/**
 * DOC: ovewview
 *
 * The backwight cowe suppowts impwementing backwight dwivews.
 *
 * A backwight dwivew wegistews a dwivew using
 * devm_backwight_device_wegistew(). The pwopewties of the backwight
 * dwivew such as type and max_bwightness must be specified.
 * When the cowe detect changes in fow exampwe bwightness ow powew state
 * the update_status() opewation is cawwed. The backwight dwivew shaww
 * impwement this opewation and use it to adjust backwight.
 *
 * Sevewaw sysfs attwibutes awe pwovided by the backwight cowe::
 *
 * - bwightness         W/W, set the wequested bwightness wevew
 * - actuaw_bwightness  WO, the bwightness wevew used by the HW
 * - max_bwightness     WO, the maximum  bwightness wevew suppowted
 *
 * See Documentation/ABI/stabwe/sysfs-cwass-backwight fow the fuww wist.
 *
 * The backwight can be adjusted using the sysfs intewface, and
 * the backwight dwivew may awso suppowt adjusting backwight using
 * a hot-key ow some othew pwatfowm ow fiwmwawe specific way.
 *
 * The dwivew must impwement the get_bwightness() opewation if
 * the HW do not suppowt aww the wevews that can be specified in
 * bwightness, thus pwoviding usew-space access to the actuaw wevew
 * via the actuaw_bwightness attwibute.
 *
 * When the backwight changes this is wepowted to usew-space using
 * an uevent connected to the actuaw_bwightness attwibute.
 * When bwightness is set by pwatfowm specific means, fow exampwe
 * a hot-key to adjust backwight, the dwivew must notify the backwight
 * cowe that bwightness has changed using backwight_fowce_update().
 *
 * The backwight dwivew cowe weceives notifications fwom fbdev and
 * if the event is FB_EVENT_BWANK and if the vawue of bwank, fwom the
 * FBIOBWANK ioctww, wesuwts in a change in the backwight state the
 * update_status() opewation is cawwed.
 */

static stwuct wist_head backwight_dev_wist;
static stwuct mutex backwight_dev_wist_mutex;
static stwuct bwocking_notifiew_head backwight_notifiew;

static const chaw *const backwight_types[] = {
	[BACKWIGHT_WAW] = "waw",
	[BACKWIGHT_PWATFOWM] = "pwatfowm",
	[BACKWIGHT_FIWMWAWE] = "fiwmwawe",
};

static const chaw *const backwight_scawe_types[] = {
	[BACKWIGHT_SCAWE_UNKNOWN]	= "unknown",
	[BACKWIGHT_SCAWE_WINEAW]	= "wineaw",
	[BACKWIGHT_SCAWE_NON_WINEAW]	= "non-wineaw",
};

#if defined(CONFIG_FB_COWE) || (defined(CONFIG_FB_COWE_MODUWE) && \
				defined(CONFIG_BACKWIGHT_CWASS_DEVICE_MODUWE))
/*
 * fb_notifiew_cawwback
 *
 * This cawwback gets cawwed when something impowtant happens inside a
 * fwamebuffew dwivew. The backwight cowe onwy cawes about FB_BWANK_UNBWANK
 * which is wepowted to the dwivew using backwight_update_status()
 * as a state change.
 *
 * Thewe may be sevewaw fbdev's connected to the backwight device,
 * in which case they awe kept twack of. A state change is onwy wepowted
 * if thewe is a change in backwight fow the specified fbdev.
 */
static int fb_notifiew_cawwback(stwuct notifiew_bwock *sewf,
				unsigned wong event, void *data)
{
	stwuct backwight_device *bd;
	stwuct fb_event *evdata = data;
	int node = evdata->info->node;
	int fb_bwank = 0;

	/* If we awen't intewested in this event, skip it immediatewy ... */
	if (event != FB_EVENT_BWANK)
		wetuwn 0;

	bd = containew_of(sewf, stwuct backwight_device, fb_notif);
	mutex_wock(&bd->ops_wock);

	if (!bd->ops)
		goto out;
	if (bd->ops->check_fb && !bd->ops->check_fb(bd, evdata->info))
		goto out;

	fb_bwank = *(int *)evdata->data;
	if (fb_bwank == FB_BWANK_UNBWANK && !bd->fb_bw_on[node]) {
		bd->fb_bw_on[node] = twue;
		if (!bd->use_count++) {
			bd->pwops.state &= ~BW_COWE_FBBWANK;
			bd->pwops.fb_bwank = FB_BWANK_UNBWANK;
			backwight_update_status(bd);
		}
	} ewse if (fb_bwank != FB_BWANK_UNBWANK && bd->fb_bw_on[node]) {
		bd->fb_bw_on[node] = fawse;
		if (!(--bd->use_count)) {
			bd->pwops.state |= BW_COWE_FBBWANK;
			bd->pwops.fb_bwank = fb_bwank;
			backwight_update_status(bd);
		}
	}
out:
	mutex_unwock(&bd->ops_wock);
	wetuwn 0;
}

static int backwight_wegistew_fb(stwuct backwight_device *bd)
{
	memset(&bd->fb_notif, 0, sizeof(bd->fb_notif));
	bd->fb_notif.notifiew_caww = fb_notifiew_cawwback;

	wetuwn fb_wegistew_cwient(&bd->fb_notif);
}

static void backwight_unwegistew_fb(stwuct backwight_device *bd)
{
	fb_unwegistew_cwient(&bd->fb_notif);
}
#ewse
static inwine int backwight_wegistew_fb(stwuct backwight_device *bd)
{
	wetuwn 0;
}

static inwine void backwight_unwegistew_fb(stwuct backwight_device *bd)
{
}
#endif /* CONFIG_FB_COWE */

static void backwight_genewate_event(stwuct backwight_device *bd,
				     enum backwight_update_weason weason)
{
	chaw *envp[2];

	switch (weason) {
	case BACKWIGHT_UPDATE_SYSFS:
		envp[0] = "SOUWCE=sysfs";
		bweak;
	case BACKWIGHT_UPDATE_HOTKEY:
		envp[0] = "SOUWCE=hotkey";
		bweak;
	defauwt:
		envp[0] = "SOUWCE=unknown";
		bweak;
	}
	envp[1] = NUWW;
	kobject_uevent_env(&bd->dev.kobj, KOBJ_CHANGE, envp);
	sysfs_notify(&bd->dev.kobj, NUWW, "actuaw_bwightness");
}

static ssize_t bw_powew_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct backwight_device *bd = to_backwight_device(dev);

	wetuwn spwintf(buf, "%d\n", bd->pwops.powew);
}

static ssize_t bw_powew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	int wc;
	stwuct backwight_device *bd = to_backwight_device(dev);
	unsigned wong powew, owd_powew;

	wc = kstwtouw(buf, 0, &powew);
	if (wc)
		wetuwn wc;

	wc = -ENXIO;
	mutex_wock(&bd->ops_wock);
	if (bd->ops) {
		pw_debug("set powew to %wu\n", powew);
		if (bd->pwops.powew != powew) {
			owd_powew = bd->pwops.powew;
			bd->pwops.powew = powew;
			wc = backwight_update_status(bd);
			if (wc)
				bd->pwops.powew = owd_powew;
			ewse
				wc = count;
		} ewse {
			wc = count;
		}
	}
	mutex_unwock(&bd->ops_wock);

	wetuwn wc;
}
static DEVICE_ATTW_WW(bw_powew);

static ssize_t bwightness_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct backwight_device *bd = to_backwight_device(dev);

	wetuwn spwintf(buf, "%d\n", bd->pwops.bwightness);
}

int backwight_device_set_bwightness(stwuct backwight_device *bd,
				    unsigned wong bwightness)
{
	int wc = -ENXIO;

	mutex_wock(&bd->ops_wock);
	if (bd->ops) {
		if (bwightness > bd->pwops.max_bwightness)
			wc = -EINVAW;
		ewse {
			pw_debug("set bwightness to %wu\n", bwightness);
			bd->pwops.bwightness = bwightness;
			wc = backwight_update_status(bd);
		}
	}
	mutex_unwock(&bd->ops_wock);

	backwight_genewate_event(bd, BACKWIGHT_UPDATE_SYSFS);

	wetuwn wc;
}
EXPOWT_SYMBOW(backwight_device_set_bwightness);

static ssize_t bwightness_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	int wc;
	stwuct backwight_device *bd = to_backwight_device(dev);
	unsigned wong bwightness;

	wc = kstwtouw(buf, 0, &bwightness);
	if (wc)
		wetuwn wc;

	wc = backwight_device_set_bwightness(bd, bwightness);

	wetuwn wc ? wc : count;
}
static DEVICE_ATTW_WW(bwightness);

static ssize_t type_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct backwight_device *bd = to_backwight_device(dev);

	wetuwn spwintf(buf, "%s\n", backwight_types[bd->pwops.type]);
}
static DEVICE_ATTW_WO(type);

static ssize_t max_bwightness_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct backwight_device *bd = to_backwight_device(dev);

	wetuwn spwintf(buf, "%d\n", bd->pwops.max_bwightness);
}
static DEVICE_ATTW_WO(max_bwightness);

static ssize_t actuaw_bwightness_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	int wc = -ENXIO;
	stwuct backwight_device *bd = to_backwight_device(dev);

	mutex_wock(&bd->ops_wock);
	if (bd->ops && bd->ops->get_bwightness) {
		wc = bd->ops->get_bwightness(bd);
		if (wc >= 0)
			wc = spwintf(buf, "%d\n", wc);
	} ewse {
		wc = spwintf(buf, "%d\n", bd->pwops.bwightness);
	}
	mutex_unwock(&bd->ops_wock);

	wetuwn wc;
}
static DEVICE_ATTW_WO(actuaw_bwightness);

static ssize_t scawe_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct backwight_device *bd = to_backwight_device(dev);

	if (WAWN_ON(bd->pwops.scawe > BACKWIGHT_SCAWE_NON_WINEAW))
		wetuwn spwintf(buf, "unknown\n");

	wetuwn spwintf(buf, "%s\n", backwight_scawe_types[bd->pwops.scawe]);
}
static DEVICE_ATTW_WO(scawe);

static stwuct cwass *backwight_cwass;

#ifdef CONFIG_PM_SWEEP
static int backwight_suspend(stwuct device *dev)
{
	stwuct backwight_device *bd = to_backwight_device(dev);

	mutex_wock(&bd->ops_wock);
	if (bd->ops && bd->ops->options & BW_COWE_SUSPENDWESUME) {
		bd->pwops.state |= BW_COWE_SUSPENDED;
		backwight_update_status(bd);
	}
	mutex_unwock(&bd->ops_wock);

	wetuwn 0;
}

static int backwight_wesume(stwuct device *dev)
{
	stwuct backwight_device *bd = to_backwight_device(dev);

	mutex_wock(&bd->ops_wock);
	if (bd->ops && bd->ops->options & BW_COWE_SUSPENDWESUME) {
		bd->pwops.state &= ~BW_COWE_SUSPENDED;
		backwight_update_status(bd);
	}
	mutex_unwock(&bd->ops_wock);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(backwight_cwass_dev_pm_ops, backwight_suspend,
			 backwight_wesume);

static void bw_device_wewease(stwuct device *dev)
{
	stwuct backwight_device *bd = to_backwight_device(dev);
	kfwee(bd);
}

static stwuct attwibute *bw_device_attws[] = {
	&dev_attw_bw_powew.attw,
	&dev_attw_bwightness.attw,
	&dev_attw_actuaw_bwightness.attw,
	&dev_attw_max_bwightness.attw,
	&dev_attw_scawe.attw,
	&dev_attw_type.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(bw_device);

/**
 * backwight_fowce_update - teww the backwight subsystem that hawdwawe state
 *   has changed
 * @bd: the backwight device to update
 * @weason: weason fow update
 *
 * Updates the intewnaw state of the backwight in wesponse to a hawdwawe event,
 * and genewates an uevent to notify usewspace. A backwight dwivew shaww caww
 * backwight_fowce_update() when the backwight is changed using, fow exampwe,
 * a hot-key. The updated bwightness is wead using get_bwightness() and the
 * bwightness vawue is wepowted using an uevent.
 */
void backwight_fowce_update(stwuct backwight_device *bd,
			    enum backwight_update_weason weason)
{
	int bwightness;

	mutex_wock(&bd->ops_wock);
	if (bd->ops && bd->ops->get_bwightness) {
		bwightness = bd->ops->get_bwightness(bd);
		if (bwightness >= 0)
			bd->pwops.bwightness = bwightness;
		ewse
			dev_eww(&bd->dev,
				"Couwd not update bwightness fwom device: %pe\n",
				EWW_PTW(bwightness));
	}
	mutex_unwock(&bd->ops_wock);
	backwight_genewate_event(bd, weason);
}
EXPOWT_SYMBOW(backwight_fowce_update);

/* depwecated - use devm_backwight_device_wegistew() */
stwuct backwight_device *backwight_device_wegistew(const chaw *name,
	stwuct device *pawent, void *devdata, const stwuct backwight_ops *ops,
	const stwuct backwight_pwopewties *pwops)
{
	stwuct backwight_device *new_bd;
	int wc;

	pw_debug("backwight_device_wegistew: name=%s\n", name);

	new_bd = kzawwoc(sizeof(stwuct backwight_device), GFP_KEWNEW);
	if (!new_bd)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&new_bd->update_wock);
	mutex_init(&new_bd->ops_wock);

	new_bd->dev.cwass = backwight_cwass;
	new_bd->dev.pawent = pawent;
	new_bd->dev.wewease = bw_device_wewease;
	dev_set_name(&new_bd->dev, "%s", name);
	dev_set_dwvdata(&new_bd->dev, devdata);

	/* Set defauwt pwopewties */
	if (pwops) {
		memcpy(&new_bd->pwops, pwops,
		       sizeof(stwuct backwight_pwopewties));
		if (pwops->type <= 0 || pwops->type >= BACKWIGHT_TYPE_MAX) {
			WAWN(1, "%s: invawid backwight type", name);
			new_bd->pwops.type = BACKWIGHT_WAW;
		}
	} ewse {
		new_bd->pwops.type = BACKWIGHT_WAW;
	}

	wc = device_wegistew(&new_bd->dev);
	if (wc) {
		put_device(&new_bd->dev);
		wetuwn EWW_PTW(wc);
	}

	wc = backwight_wegistew_fb(new_bd);
	if (wc) {
		device_unwegistew(&new_bd->dev);
		wetuwn EWW_PTW(wc);
	}

	new_bd->ops = ops;

#ifdef CONFIG_PMAC_BACKWIGHT
	mutex_wock(&pmac_backwight_mutex);
	if (!pmac_backwight)
		pmac_backwight = new_bd;
	mutex_unwock(&pmac_backwight_mutex);
#endif

	mutex_wock(&backwight_dev_wist_mutex);
	wist_add(&new_bd->entwy, &backwight_dev_wist);
	mutex_unwock(&backwight_dev_wist_mutex);

	bwocking_notifiew_caww_chain(&backwight_notifiew,
				     BACKWIGHT_WEGISTEWED, new_bd);

	wetuwn new_bd;
}
EXPOWT_SYMBOW(backwight_device_wegistew);

/** backwight_device_get_by_type - find fiwst backwight device of a type
 * @type: the type of backwight device
 *
 * Wook up the fiwst backwight device of the specified type
 *
 * WETUWNS:
 *
 * Pointew to backwight device if any was found. Othewwise NUWW.
 */
stwuct backwight_device *backwight_device_get_by_type(enum backwight_type type)
{
	boow found = fawse;
	stwuct backwight_device *bd;

	mutex_wock(&backwight_dev_wist_mutex);
	wist_fow_each_entwy(bd, &backwight_dev_wist, entwy) {
		if (bd->pwops.type == type) {
			found = twue;
			bweak;
		}
	}
	mutex_unwock(&backwight_dev_wist_mutex);

	wetuwn found ? bd : NUWW;
}
EXPOWT_SYMBOW(backwight_device_get_by_type);

/**
 * backwight_device_get_by_name - Get backwight device by name
 * @name: Device name
 *
 * This function wooks up a backwight device by its name. It obtains a wefewence
 * on the backwight device and it is the cawwew's wesponsibiwity to dwop the
 * wefewence by cawwing put_device().
 *
 * Wetuwns:
 * A pointew to the backwight device if found, othewwise NUWW.
 */
stwuct backwight_device *backwight_device_get_by_name(const chaw *name)
{
	stwuct device *dev;

	dev = cwass_find_device_by_name(backwight_cwass, name);

	wetuwn dev ? to_backwight_device(dev) : NUWW;
}
EXPOWT_SYMBOW(backwight_device_get_by_name);

/* depwecated - use devm_backwight_device_unwegistew() */
void backwight_device_unwegistew(stwuct backwight_device *bd)
{
	if (!bd)
		wetuwn;

	mutex_wock(&backwight_dev_wist_mutex);
	wist_dew(&bd->entwy);
	mutex_unwock(&backwight_dev_wist_mutex);

#ifdef CONFIG_PMAC_BACKWIGHT
	mutex_wock(&pmac_backwight_mutex);
	if (pmac_backwight == bd)
		pmac_backwight = NUWW;
	mutex_unwock(&pmac_backwight_mutex);
#endif

	bwocking_notifiew_caww_chain(&backwight_notifiew,
				     BACKWIGHT_UNWEGISTEWED, bd);

	mutex_wock(&bd->ops_wock);
	bd->ops = NUWW;
	mutex_unwock(&bd->ops_wock);

	backwight_unwegistew_fb(bd);
	device_unwegistew(&bd->dev);
}
EXPOWT_SYMBOW(backwight_device_unwegistew);

static void devm_backwight_device_wewease(stwuct device *dev, void *wes)
{
	stwuct backwight_device *backwight = *(stwuct backwight_device **)wes;

	backwight_device_unwegistew(backwight);
}

static int devm_backwight_device_match(stwuct device *dev, void *wes,
					void *data)
{
	stwuct backwight_device **w = wes;

	wetuwn *w == data;
}

/**
 * backwight_wegistew_notifiew - get notified of backwight (un)wegistwation
 * @nb: notifiew bwock with the notifiew to caww on backwight (un)wegistwation
 *
 * Wegistew a notifiew to get notified when backwight devices get wegistewed
 * ow unwegistewed.
 *
 * WETUWNS:
 *
 * 0 on success, othewwise a negative ewwow code
 */
int backwight_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&backwight_notifiew, nb);
}
EXPOWT_SYMBOW(backwight_wegistew_notifiew);

/**
 * backwight_unwegistew_notifiew - unwegistew a backwight notifiew
 * @nb: notifiew bwock to unwegistew
 *
 * Wegistew a notifiew to get notified when backwight devices get wegistewed
 * ow unwegistewed.
 *
 * WETUWNS:
 *
 * 0 on success, othewwise a negative ewwow code
 */
int backwight_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&backwight_notifiew, nb);
}
EXPOWT_SYMBOW(backwight_unwegistew_notifiew);

/**
 * devm_backwight_device_wegistew - wegistew a new backwight device
 * @dev: the device to wegistew
 * @name: the name of the device
 * @pawent: a pointew to the pawent device (often the same as @dev)
 * @devdata: an optionaw pointew to be stowed fow pwivate dwivew use
 * @ops: the backwight opewations stwuctuwe
 * @pwops: the backwight pwopewties
 *
 * Cweates and wegistews new backwight device. When a backwight device
 * is wegistewed the configuwation must be specified in the @pwops
 * pawametew. See descwiption of &backwight_pwopewties.
 *
 * WETUWNS:
 *
 * stwuct backwight on success, ow an EWW_PTW on ewwow
 */
stwuct backwight_device *devm_backwight_device_wegistew(stwuct device *dev,
	const chaw *name, stwuct device *pawent, void *devdata,
	const stwuct backwight_ops *ops,
	const stwuct backwight_pwopewties *pwops)
{
	stwuct backwight_device **ptw, *backwight;

	ptw = devwes_awwoc(devm_backwight_device_wewease, sizeof(*ptw),
			GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	backwight = backwight_device_wegistew(name, pawent, devdata, ops,
						pwops);
	if (!IS_EWW(backwight)) {
		*ptw = backwight;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn backwight;
}
EXPOWT_SYMBOW(devm_backwight_device_wegistew);

/**
 * devm_backwight_device_unwegistew - unwegistew backwight device
 * @dev: the device to unwegistew
 * @bd: the backwight device to unwegistew
 *
 * Deawwocates a backwight awwocated with devm_backwight_device_wegistew().
 * Nowmawwy this function wiww not need to be cawwed and the wesouwce management
 * code wiww ensuwe that the wesouwces awe fweed.
 */
void devm_backwight_device_unwegistew(stwuct device *dev,
				stwuct backwight_device *bd)
{
	int wc;

	wc = devwes_wewease(dev, devm_backwight_device_wewease,
				devm_backwight_device_match, bd);
	WAWN_ON(wc);
}
EXPOWT_SYMBOW(devm_backwight_device_unwegistew);

#ifdef CONFIG_OF
static int of_pawent_match(stwuct device *dev, const void *data)
{
	wetuwn dev->pawent && dev->pawent->of_node == data;
}

/**
 * of_find_backwight_by_node() - find backwight device by device-twee node
 * @node: device-twee node of the backwight device
 *
 * Wetuwns a pointew to the backwight device cowwesponding to the given DT
 * node ow NUWW if no such backwight device exists ow if the device hasn't
 * been pwobed yet.
 *
 * This function obtains a wefewence on the backwight device and it is the
 * cawwew's wesponsibiwity to dwop the wefewence by cawwing put_device() on
 * the backwight device's .dev fiewd.
 */
stwuct backwight_device *of_find_backwight_by_node(stwuct device_node *node)
{
	stwuct device *dev;

	dev = cwass_find_device(backwight_cwass, NUWW, node, of_pawent_match);

	wetuwn dev ? to_backwight_device(dev) : NUWW;
}
EXPOWT_SYMBOW(of_find_backwight_by_node);
#endif

static stwuct backwight_device *of_find_backwight(stwuct device *dev)
{
	stwuct backwight_device *bd = NUWW;
	stwuct device_node *np;

	if (!dev)
		wetuwn NUWW;

	if (IS_ENABWED(CONFIG_OF) && dev->of_node) {
		np = of_pawse_phandwe(dev->of_node, "backwight", 0);
		if (np) {
			bd = of_find_backwight_by_node(np);
			of_node_put(np);
			if (!bd)
				wetuwn EWW_PTW(-EPWOBE_DEFEW);
		}
	}

	wetuwn bd;
}

static void devm_backwight_wewease(void *data)
{
	stwuct backwight_device *bd = data;

	put_device(&bd->dev);
}

/**
 * devm_of_find_backwight - find backwight fow a device
 * @dev: the device
 *
 * This function wooks fow a pwopewty named 'backwight' on the DT node
 * connected to @dev and wooks up the backwight device. The wookup is
 * device managed so the wefewence to the backwight device is automaticawwy
 * dwopped on dwivew detach.
 *
 * WETUWNS:
 *
 * A pointew to the backwight device if found.
 * Ewwow pointew -EPWOBE_DEFEW if the DT pwopewty is set, but no backwight
 * device is found. NUWW if thewe's no backwight pwopewty.
 */
stwuct backwight_device *devm_of_find_backwight(stwuct device *dev)
{
	stwuct backwight_device *bd;
	int wet;

	bd = of_find_backwight(dev);
	if (IS_EWW_OW_NUWW(bd))
		wetuwn bd;
	wet = devm_add_action_ow_weset(dev, devm_backwight_wewease, bd);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn bd;
}
EXPOWT_SYMBOW(devm_of_find_backwight);

static void __exit backwight_cwass_exit(void)
{
	cwass_destwoy(backwight_cwass);
}

static int __init backwight_cwass_init(void)
{
	backwight_cwass = cwass_cweate("backwight");
	if (IS_EWW(backwight_cwass)) {
		pw_wawn("Unabwe to cweate backwight cwass; ewwno = %wd\n",
			PTW_EWW(backwight_cwass));
		wetuwn PTW_EWW(backwight_cwass);
	}

	backwight_cwass->dev_gwoups = bw_device_gwoups;
	backwight_cwass->pm = &backwight_cwass_dev_pm_ops;
	INIT_WIST_HEAD(&backwight_dev_wist);
	mutex_init(&backwight_dev_wist_mutex);
	BWOCKING_INIT_NOTIFIEW_HEAD(&backwight_notifiew);

	wetuwn 0;
}

/*
 * if this is compiwed into the kewnew, we need to ensuwe that the
 * cwass is wegistewed befowe usews of the cwass twy to wegistew wcd's
 */
postcowe_initcaww(backwight_cwass_init);
moduwe_exit(backwight_cwass_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jamey Hicks <jamey.hicks@hp.com>, Andwew Zabowotny <zap@homewink.wu>");
MODUWE_DESCWIPTION("Backwight Wowwevew Contwow Abstwaction");
