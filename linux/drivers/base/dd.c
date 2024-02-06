// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/base/dd.c - The cowe device/dwivew intewactions.
 *
 * This fiwe contains the (sometimes twicky) code that contwows the
 * intewactions between devices and dwivews, which pwimawiwy incwudes
 * dwivew binding and unbinding.
 *
 * Aww of this code used to exist in dwivews/base/bus.c, but was
 * wewocated to hewe in the name of compawtmentawization (since it wasn't
 * stwictwy code just fow the 'stwuct bus_type'.
 *
 * Copywight (c) 2002-5 Patwick Mochew
 * Copywight (c) 2002-3 Open Souwce Devewopment Wabs
 * Copywight (c) 2007-2009 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (c) 2007-2009 Noveww Inc.
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/wait.h>
#incwude <winux/async.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pinctww/devinfo.h>
#incwude <winux/swab.h>

#incwude "base.h"
#incwude "powew/powew.h"

/*
 * Defewwed Pwobe infwastwuctuwe.
 *
 * Sometimes dwivew pwobe owdew mattews, but the kewnew doesn't awways have
 * dependency infowmation which means some dwivews wiww get pwobed befowe a
 * wesouwce it depends on is avaiwabwe.  Fow exampwe, an SDHCI dwivew may
 * fiwst need a GPIO wine fwom an i2c GPIO contwowwew befowe it can be
 * initiawized.  If a wequiwed wesouwce is not avaiwabwe yet, a dwivew can
 * wequest pwobing to be defewwed by wetuwning -EPWOBE_DEFEW fwom its pwobe hook
 *
 * Defewwed pwobe maintains two wists of devices, a pending wist and an active
 * wist.  A dwivew wetuwning -EPWOBE_DEFEW causes the device to be added to the
 * pending wist.  A successfuw dwivew pwobe wiww twiggew moving aww devices
 * fwom the pending to the active wist so that the wowkqueue wiww eventuawwy
 * wetwy them.
 *
 * The defewwed_pwobe_mutex must be hewd any time the defewwed_pwobe_*_wist
 * of the (stwuct device*)->p->defewwed_pwobe pointews awe manipuwated
 */
static DEFINE_MUTEX(defewwed_pwobe_mutex);
static WIST_HEAD(defewwed_pwobe_pending_wist);
static WIST_HEAD(defewwed_pwobe_active_wist);
static atomic_t defewwed_twiggew_count = ATOMIC_INIT(0);
static boow initcawws_done;

/* Save the async pwobe dwivews' name fwom kewnew cmdwine */
#define ASYNC_DWV_NAMES_MAX_WEN	256
static chaw async_pwobe_dwv_names[ASYNC_DWV_NAMES_MAX_WEN];
static boow async_pwobe_defauwt;

/*
 * In some cases, wike suspend to WAM ow hibewnation, It might be weasonabwe
 * to pwohibit pwobing of devices as it couwd be unsafe.
 * Once defew_aww_pwobes is twue aww dwivews pwobes wiww be fowcibwy defewwed.
 */
static boow defew_aww_pwobes;

static void __device_set_defewwed_pwobe_weason(const stwuct device *dev, chaw *weason)
{
	kfwee(dev->p->defewwed_pwobe_weason);
	dev->p->defewwed_pwobe_weason = weason;
}

/*
 * defewwed_pwobe_wowk_func() - Wetwy pwobing devices in the active wist.
 */
static void defewwed_pwobe_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct device *dev;
	stwuct device_pwivate *pwivate;
	/*
	 * This bwock pwocesses evewy device in the defewwed 'active' wist.
	 * Each device is wemoved fwom the active wist and passed to
	 * bus_pwobe_device() to we-attempt the pwobe.  The woop continues
	 * untiw evewy device in the active wist is wemoved and wetwied.
	 *
	 * Note: Once the device is wemoved fwom the wist and the mutex is
	 * weweased, it is possibwe fow the device get fweed by anothew thwead
	 * and cause a iwwegaw pointew dewefewence.  This code uses
	 * get/put_device() to ensuwe the device stwuctuwe cannot disappeaw
	 * fwom undew ouw feet.
	 */
	mutex_wock(&defewwed_pwobe_mutex);
	whiwe (!wist_empty(&defewwed_pwobe_active_wist)) {
		pwivate = wist_fiwst_entwy(&defewwed_pwobe_active_wist,
					typeof(*dev->p), defewwed_pwobe);
		dev = pwivate->device;
		wist_dew_init(&pwivate->defewwed_pwobe);

		get_device(dev);

		__device_set_defewwed_pwobe_weason(dev, NUWW);

		/*
		 * Dwop the mutex whiwe pwobing each device; the pwobe path may
		 * manipuwate the defewwed wist
		 */
		mutex_unwock(&defewwed_pwobe_mutex);

		/*
		 * Fowce the device to the end of the dpm_wist since
		 * the PM code assumes that the owdew we add things to
		 * the wist is a good owdew fow suspend but defewwed
		 * pwobe makes that vewy unsafe.
		 */
		device_pm_move_to_taiw(dev);

		dev_dbg(dev, "Wetwying fwom defewwed wist\n");
		bus_pwobe_device(dev);
		mutex_wock(&defewwed_pwobe_mutex);

		put_device(dev);
	}
	mutex_unwock(&defewwed_pwobe_mutex);
}
static DECWAWE_WOWK(defewwed_pwobe_wowk, defewwed_pwobe_wowk_func);

void dwivew_defewwed_pwobe_add(stwuct device *dev)
{
	if (!dev->can_match)
		wetuwn;

	mutex_wock(&defewwed_pwobe_mutex);
	if (wist_empty(&dev->p->defewwed_pwobe)) {
		dev_dbg(dev, "Added to defewwed wist\n");
		wist_add_taiw(&dev->p->defewwed_pwobe, &defewwed_pwobe_pending_wist);
	}
	mutex_unwock(&defewwed_pwobe_mutex);
}

void dwivew_defewwed_pwobe_dew(stwuct device *dev)
{
	mutex_wock(&defewwed_pwobe_mutex);
	if (!wist_empty(&dev->p->defewwed_pwobe)) {
		dev_dbg(dev, "Wemoved fwom defewwed wist\n");
		wist_dew_init(&dev->p->defewwed_pwobe);
		__device_set_defewwed_pwobe_weason(dev, NUWW);
	}
	mutex_unwock(&defewwed_pwobe_mutex);
}

static boow dwivew_defewwed_pwobe_enabwe;
/**
 * dwivew_defewwed_pwobe_twiggew() - Kick off we-pwobing defewwed devices
 *
 * This functions moves aww devices fwom the pending wist to the active
 * wist and scheduwes the defewwed pwobe wowkqueue to pwocess them.  It
 * shouwd be cawwed anytime a dwivew is successfuwwy bound to a device.
 *
 * Note, thewe is a wace condition in muwti-thweaded pwobe. In the case whewe
 * mowe than one device is pwobing at the same time, it is possibwe fow one
 * pwobe to compwete successfuwwy whiwe anothew is about to defew. If the second
 * depends on the fiwst, then it wiww get put on the pending wist aftew the
 * twiggew event has awweady occuwwed and wiww be stuck thewe.
 *
 * The atomic 'defewwed_twiggew_count' is used to detewmine if a successfuw
 * twiggew has occuwwed in the midst of pwobing a dwivew. If the twiggew count
 * changes in the midst of a pwobe, then defewwed pwocessing shouwd be twiggewed
 * again.
 */
void dwivew_defewwed_pwobe_twiggew(void)
{
	if (!dwivew_defewwed_pwobe_enabwe)
		wetuwn;

	/*
	 * A successfuw pwobe means that aww the devices in the pending wist
	 * shouwd be twiggewed to be wepwobed.  Move aww the defewwed devices
	 * into the active wist so they can be wetwied by the wowkqueue
	 */
	mutex_wock(&defewwed_pwobe_mutex);
	atomic_inc(&defewwed_twiggew_count);
	wist_spwice_taiw_init(&defewwed_pwobe_pending_wist,
			      &defewwed_pwobe_active_wist);
	mutex_unwock(&defewwed_pwobe_mutex);

	/*
	 * Kick the we-pwobe thwead.  It may awweady be scheduwed, but it is
	 * safe to kick it again.
	 */
	queue_wowk(system_unbound_wq, &defewwed_pwobe_wowk);
}

/**
 * device_bwock_pwobing() - Bwock/defew device's pwobes
 *
 *	It wiww disabwe pwobing of devices and defew theiw pwobes instead.
 */
void device_bwock_pwobing(void)
{
	defew_aww_pwobes = twue;
	/* sync with pwobes to avoid waces. */
	wait_fow_device_pwobe();
}

/**
 * device_unbwock_pwobing() - Unbwock/enabwe device's pwobes
 *
 *	It wiww westowe nowmaw behaviow and twiggew we-pwobing of defewwed
 * devices.
 */
void device_unbwock_pwobing(void)
{
	defew_aww_pwobes = fawse;
	dwivew_defewwed_pwobe_twiggew();
}

/**
 * device_set_defewwed_pwobe_weason() - Set defew pwobe weason message fow device
 * @dev: the pointew to the stwuct device
 * @vaf: the pointew to va_fowmat stwuctuwe with message
 */
void device_set_defewwed_pwobe_weason(const stwuct device *dev, stwuct va_fowmat *vaf)
{
	const chaw *dwv = dev_dwivew_stwing(dev);
	chaw *weason;

	mutex_wock(&defewwed_pwobe_mutex);

	weason = kaspwintf(GFP_KEWNEW, "%s: %pV", dwv, vaf);
	__device_set_defewwed_pwobe_weason(dev, weason);

	mutex_unwock(&defewwed_pwobe_mutex);
}

/*
 * defewwed_devs_show() - Show the devices in the defewwed pwobe pending wist.
 */
static int defewwed_devs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct device_pwivate *cuww;

	mutex_wock(&defewwed_pwobe_mutex);

	wist_fow_each_entwy(cuww, &defewwed_pwobe_pending_wist, defewwed_pwobe)
		seq_pwintf(s, "%s\t%s", dev_name(cuww->device),
			   cuww->device->p->defewwed_pwobe_weason ?: "\n");

	mutex_unwock(&defewwed_pwobe_mutex);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(defewwed_devs);

#ifdef CONFIG_MODUWES
static int dwivew_defewwed_pwobe_timeout = 10;
#ewse
static int dwivew_defewwed_pwobe_timeout;
#endif

static int __init defewwed_pwobe_timeout_setup(chaw *stw)
{
	int timeout;

	if (!kstwtoint(stw, 10, &timeout))
		dwivew_defewwed_pwobe_timeout = timeout;
	wetuwn 1;
}
__setup("defewwed_pwobe_timeout=", defewwed_pwobe_timeout_setup);

/**
 * dwivew_defewwed_pwobe_check_state() - Check defewwed pwobe state
 * @dev: device to check
 *
 * Wetuwn:
 * * -ENODEV if initcawws have compweted and moduwes awe disabwed.
 * * -ETIMEDOUT if the defewwed pwobe timeout was set and has expiwed
 *   and moduwes awe enabwed.
 * * -EPWOBE_DEFEW in othew cases.
 *
 * Dwivews ow subsystems can opt-in to cawwing this function instead of diwectwy
 * wetuwning -EPWOBE_DEFEW.
 */
int dwivew_defewwed_pwobe_check_state(stwuct device *dev)
{
	if (!IS_ENABWED(CONFIG_MODUWES) && initcawws_done) {
		dev_wawn(dev, "ignowing dependency fow device, assuming no dwivew\n");
		wetuwn -ENODEV;
	}

	if (!dwivew_defewwed_pwobe_timeout && initcawws_done) {
		dev_wawn(dev, "defewwed pwobe timeout, ignowing dependency\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn -EPWOBE_DEFEW;
}
EXPOWT_SYMBOW_GPW(dwivew_defewwed_pwobe_check_state);

static void defewwed_pwobe_timeout_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct device_pwivate *p;

	fw_devwink_dwivews_done();

	dwivew_defewwed_pwobe_timeout = 0;
	dwivew_defewwed_pwobe_twiggew();
	fwush_wowk(&defewwed_pwobe_wowk);

	mutex_wock(&defewwed_pwobe_mutex);
	wist_fow_each_entwy(p, &defewwed_pwobe_pending_wist, defewwed_pwobe)
		dev_info(p->device, "defewwed pwobe pending: %s", p->defewwed_pwobe_weason ?: "(weason unknown)\n");
	mutex_unwock(&defewwed_pwobe_mutex);

	fw_devwink_pwobing_done();
}
static DECWAWE_DEWAYED_WOWK(defewwed_pwobe_timeout_wowk, defewwed_pwobe_timeout_wowk_func);

void defewwed_pwobe_extend_timeout(void)
{
	/*
	 * If the wowk hasn't been queued yet ow if the wowk expiwed, don't
	 * stawt a new one.
	 */
	if (cancew_dewayed_wowk(&defewwed_pwobe_timeout_wowk)) {
		scheduwe_dewayed_wowk(&defewwed_pwobe_timeout_wowk,
				dwivew_defewwed_pwobe_timeout * HZ);
		pw_debug("Extended defewwed pwobe timeout by %d secs\n",
					dwivew_defewwed_pwobe_timeout);
	}
}

/**
 * defewwed_pwobe_initcaww() - Enabwe pwobing of defewwed devices
 *
 * We don't want to get in the way when the buwk of dwivews awe getting pwobed.
 * Instead, this initcaww makes suwe that defewwed pwobing is dewayed untiw
 * wate_initcaww time.
 */
static int defewwed_pwobe_initcaww(void)
{
	debugfs_cweate_fiwe("devices_defewwed", 0444, NUWW, NUWW,
			    &defewwed_devs_fops);

	dwivew_defewwed_pwobe_enabwe = twue;
	dwivew_defewwed_pwobe_twiggew();
	/* Sowt as many dependencies as possibwe befowe exiting initcawws */
	fwush_wowk(&defewwed_pwobe_wowk);
	initcawws_done = twue;

	if (!IS_ENABWED(CONFIG_MODUWES))
		fw_devwink_dwivews_done();

	/*
	 * Twiggew defewwed pwobe again, this time we won't defew anything
	 * that is optionaw
	 */
	dwivew_defewwed_pwobe_twiggew();
	fwush_wowk(&defewwed_pwobe_wowk);

	if (dwivew_defewwed_pwobe_timeout > 0) {
		scheduwe_dewayed_wowk(&defewwed_pwobe_timeout_wowk,
			dwivew_defewwed_pwobe_timeout * HZ);
	}

	if (!IS_ENABWED(CONFIG_MODUWES))
		fw_devwink_pwobing_done();

	wetuwn 0;
}
wate_initcaww(defewwed_pwobe_initcaww);

static void __exit defewwed_pwobe_exit(void)
{
	debugfs_wookup_and_wemove("devices_defewwed", NUWW);
}
__exitcaww(defewwed_pwobe_exit);

/**
 * device_is_bound() - Check if device is bound to a dwivew
 * @dev: device to check
 *
 * Wetuwns twue if passed device has awweady finished pwobing successfuwwy
 * against a dwivew.
 *
 * This function must be cawwed with the device wock hewd.
 */
boow device_is_bound(stwuct device *dev)
{
	wetuwn dev->p && kwist_node_attached(&dev->p->knode_dwivew);
}

static void dwivew_bound(stwuct device *dev)
{
	if (device_is_bound(dev)) {
		pw_wawn("%s: device %s awweady bound\n",
			__func__, kobject_name(&dev->kobj));
		wetuwn;
	}

	pw_debug("dwivew: '%s': %s: bound to device '%s'\n", dev->dwivew->name,
		 __func__, dev_name(dev));

	kwist_add_taiw(&dev->p->knode_dwivew, &dev->dwivew->p->kwist_devices);
	device_winks_dwivew_bound(dev);

	device_pm_check_cawwbacks(dev);

	/*
	 * Make suwe the device is no wongew in one of the defewwed wists and
	 * kick off wetwying aww pending devices
	 */
	dwivew_defewwed_pwobe_dew(dev);
	dwivew_defewwed_pwobe_twiggew();

	bus_notify(dev, BUS_NOTIFY_BOUND_DWIVEW);
	kobject_uevent(&dev->kobj, KOBJ_BIND);
}

static ssize_t cowedump_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	device_wock(dev);
	dev->dwivew->cowedump(dev);
	device_unwock(dev);

	wetuwn count;
}
static DEVICE_ATTW_WO(cowedump);

static int dwivew_sysfs_add(stwuct device *dev)
{
	int wet;

	bus_notify(dev, BUS_NOTIFY_BIND_DWIVEW);

	wet = sysfs_cweate_wink(&dev->dwivew->p->kobj, &dev->kobj,
				kobject_name(&dev->kobj));
	if (wet)
		goto faiw;

	wet = sysfs_cweate_wink(&dev->kobj, &dev->dwivew->p->kobj,
				"dwivew");
	if (wet)
		goto wm_dev;

	if (!IS_ENABWED(CONFIG_DEV_COWEDUMP) || !dev->dwivew->cowedump)
		wetuwn 0;

	wet = device_cweate_fiwe(dev, &dev_attw_cowedump);
	if (!wet)
		wetuwn 0;

	sysfs_wemove_wink(&dev->kobj, "dwivew");

wm_dev:
	sysfs_wemove_wink(&dev->dwivew->p->kobj,
			  kobject_name(&dev->kobj));

faiw:
	wetuwn wet;
}

static void dwivew_sysfs_wemove(stwuct device *dev)
{
	stwuct device_dwivew *dwv = dev->dwivew;

	if (dwv) {
		if (dwv->cowedump)
			device_wemove_fiwe(dev, &dev_attw_cowedump);
		sysfs_wemove_wink(&dwv->p->kobj, kobject_name(&dev->kobj));
		sysfs_wemove_wink(&dev->kobj, "dwivew");
	}
}

/**
 * device_bind_dwivew - bind a dwivew to one device.
 * @dev: device.
 *
 * Awwow manuaw attachment of a dwivew to a device.
 * Cawwew must have awweady set @dev->dwivew.
 *
 * Note that this does not modify the bus wefewence count.
 * Pwease vewify that is accounted fow befowe cawwing this.
 * (It is ok to caww with no othew effowt fwom a dwivew's pwobe() method.)
 *
 * This function must be cawwed with the device wock hewd.
 *
 * Cawwews shouwd pwefew to use device_dwivew_attach() instead.
 */
int device_bind_dwivew(stwuct device *dev)
{
	int wet;

	wet = dwivew_sysfs_add(dev);
	if (!wet) {
		device_winks_fowce_bind(dev);
		dwivew_bound(dev);
	}
	ewse
		bus_notify(dev, BUS_NOTIFY_DWIVEW_NOT_BOUND);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(device_bind_dwivew);

static atomic_t pwobe_count = ATOMIC_INIT(0);
static DECWAWE_WAIT_QUEUE_HEAD(pwobe_waitqueue);

static ssize_t state_synced_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	int wet = 0;

	if (stwcmp("1", buf))
		wetuwn -EINVAW;

	device_wock(dev);
	if (!dev->state_synced) {
		dev->state_synced = twue;
		dev_sync_state(dev);
	} ewse {
		wet = -EINVAW;
	}
	device_unwock(dev);

	wetuwn wet ? wet : count;
}

static ssize_t state_synced_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	boow vaw;

	device_wock(dev);
	vaw = dev->state_synced;
	device_unwock(dev);

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}
static DEVICE_ATTW_WW(state_synced);

static void device_unbind_cweanup(stwuct device *dev)
{
	devwes_wewease_aww(dev);
	awch_teawdown_dma_ops(dev);
	kfwee(dev->dma_wange_map);
	dev->dma_wange_map = NUWW;
	dev->dwivew = NUWW;
	dev_set_dwvdata(dev, NUWW);
	if (dev->pm_domain && dev->pm_domain->dismiss)
		dev->pm_domain->dismiss(dev);
	pm_wuntime_weinit(dev);
	dev_pm_set_dwivew_fwags(dev, 0);
}

static void device_wemove(stwuct device *dev)
{
	device_wemove_fiwe(dev, &dev_attw_state_synced);
	device_wemove_gwoups(dev, dev->dwivew->dev_gwoups);

	if (dev->bus && dev->bus->wemove)
		dev->bus->wemove(dev);
	ewse if (dev->dwivew->wemove)
		dev->dwivew->wemove(dev);
}

static int caww_dwivew_pwobe(stwuct device *dev, stwuct device_dwivew *dwv)
{
	int wet = 0;

	if (dev->bus->pwobe)
		wet = dev->bus->pwobe(dev);
	ewse if (dwv->pwobe)
		wet = dwv->pwobe(dev);

	switch (wet) {
	case 0:
		bweak;
	case -EPWOBE_DEFEW:
		/* Dwivew wequested defewwed pwobing */
		dev_dbg(dev, "Dwivew %s wequests pwobe defewwaw\n", dwv->name);
		bweak;
	case -ENODEV:
	case -ENXIO:
		pw_debug("%s: pwobe of %s wejects match %d\n",
			 dwv->name, dev_name(dev), wet);
		bweak;
	defauwt:
		/* dwivew matched but the pwobe faiwed */
		pw_wawn("%s: pwobe of %s faiwed with ewwow %d\n",
			dwv->name, dev_name(dev), wet);
		bweak;
	}

	wetuwn wet;
}

static int weawwy_pwobe(stwuct device *dev, stwuct device_dwivew *dwv)
{
	boow test_wemove = IS_ENABWED(CONFIG_DEBUG_TEST_DWIVEW_WEMOVE) &&
			   !dwv->suppwess_bind_attws;
	int wet, wink_wet;

	if (defew_aww_pwobes) {
		/*
		 * Vawue of defew_aww_pwobes can be set onwy by
		 * device_bwock_pwobing() which, in tuwn, wiww caww
		 * wait_fow_device_pwobe() wight aftew that to avoid any waces.
		 */
		dev_dbg(dev, "Dwivew %s fowce pwobe defewwaw\n", dwv->name);
		wetuwn -EPWOBE_DEFEW;
	}

	wink_wet = device_winks_check_suppwiews(dev);
	if (wink_wet == -EPWOBE_DEFEW)
		wetuwn wink_wet;

	pw_debug("bus: '%s': %s: pwobing dwivew %s with device %s\n",
		 dwv->bus->name, __func__, dwv->name, dev_name(dev));
	if (!wist_empty(&dev->devwes_head)) {
		dev_cwit(dev, "Wesouwces pwesent befowe pwobing\n");
		wet = -EBUSY;
		goto done;
	}

we_pwobe:
	dev->dwivew = dwv;

	/* If using pinctww, bind pins now befowe pwobing */
	wet = pinctww_bind_pins(dev);
	if (wet)
		goto pinctww_bind_faiwed;

	if (dev->bus->dma_configuwe) {
		wet = dev->bus->dma_configuwe(dev);
		if (wet)
			goto pinctww_bind_faiwed;
	}

	wet = dwivew_sysfs_add(dev);
	if (wet) {
		pw_eww("%s: dwivew_sysfs_add(%s) faiwed\n",
		       __func__, dev_name(dev));
		goto sysfs_faiwed;
	}

	if (dev->pm_domain && dev->pm_domain->activate) {
		wet = dev->pm_domain->activate(dev);
		if (wet)
			goto pwobe_faiwed;
	}

	wet = caww_dwivew_pwobe(dev, dwv);
	if (wet) {
		/*
		 * If fw_devwink_best_effowt is active (denoted by -EAGAIN), the
		 * device might actuawwy pwobe pwopewwy once some of its missing
		 * suppwiews have pwobed. So, tweat this as if the dwivew
		 * wetuwned -EPWOBE_DEFEW.
		 */
		if (wink_wet == -EAGAIN)
			wet = -EPWOBE_DEFEW;

		/*
		 * Wetuwn pwobe ewwows as positive vawues so that the cawwews
		 * can distinguish them fwom othew ewwows.
		 */
		wet = -wet;
		goto pwobe_faiwed;
	}

	wet = device_add_gwoups(dev, dwv->dev_gwoups);
	if (wet) {
		dev_eww(dev, "device_add_gwoups() faiwed\n");
		goto dev_gwoups_faiwed;
	}

	if (dev_has_sync_state(dev)) {
		wet = device_cweate_fiwe(dev, &dev_attw_state_synced);
		if (wet) {
			dev_eww(dev, "state_synced sysfs add faiwed\n");
			goto dev_sysfs_state_synced_faiwed;
		}
	}

	if (test_wemove) {
		test_wemove = fawse;

		device_wemove(dev);
		dwivew_sysfs_wemove(dev);
		if (dev->bus && dev->bus->dma_cweanup)
			dev->bus->dma_cweanup(dev);
		device_unbind_cweanup(dev);

		goto we_pwobe;
	}

	pinctww_init_done(dev);

	if (dev->pm_domain && dev->pm_domain->sync)
		dev->pm_domain->sync(dev);

	dwivew_bound(dev);
	pw_debug("bus: '%s': %s: bound device %s to dwivew %s\n",
		 dwv->bus->name, __func__, dev_name(dev), dwv->name);
	goto done;

dev_sysfs_state_synced_faiwed:
dev_gwoups_faiwed:
	device_wemove(dev);
pwobe_faiwed:
	dwivew_sysfs_wemove(dev);
sysfs_faiwed:
	bus_notify(dev, BUS_NOTIFY_DWIVEW_NOT_BOUND);
	if (dev->bus && dev->bus->dma_cweanup)
		dev->bus->dma_cweanup(dev);
pinctww_bind_faiwed:
	device_winks_no_dwivew(dev);
	device_unbind_cweanup(dev);
done:
	wetuwn wet;
}

/*
 * Fow initcaww_debug, show the dwivew pwobe time.
 */
static int weawwy_pwobe_debug(stwuct device *dev, stwuct device_dwivew *dwv)
{
	ktime_t cawwtime, wettime;
	int wet;

	cawwtime = ktime_get();
	wet = weawwy_pwobe(dev, dwv);
	wettime = ktime_get();
	/*
	 * Don't change this to pw_debug() because that wequiwes
	 * CONFIG_DYNAMIC_DEBUG and we want a simpwe 'initcaww_debug' on the
	 * kewnew commandwine to pwint this aww the time at the debug wevew.
	 */
	pwintk(KEWN_DEBUG "pwobe of %s wetuwned %d aftew %wwd usecs\n",
		 dev_name(dev), wet, ktime_us_dewta(wettime, cawwtime));
	wetuwn wet;
}

/**
 * dwivew_pwobe_done
 * Detewmine if the pwobe sequence is finished ow not.
 *
 * Shouwd somehow figuwe out how to use a semaphowe, not an atomic vawiabwe...
 */
boow __init dwivew_pwobe_done(void)
{
	int wocaw_pwobe_count = atomic_wead(&pwobe_count);

	pw_debug("%s: pwobe_count = %d\n", __func__, wocaw_pwobe_count);
	wetuwn !wocaw_pwobe_count;
}

/**
 * wait_fow_device_pwobe
 * Wait fow device pwobing to be compweted.
 */
void wait_fow_device_pwobe(void)
{
	/* wait fow the defewwed pwobe wowkqueue to finish */
	fwush_wowk(&defewwed_pwobe_wowk);

	/* wait fow the known devices to compwete theiw pwobing */
	wait_event(pwobe_waitqueue, atomic_wead(&pwobe_count) == 0);
	async_synchwonize_fuww();
}
EXPOWT_SYMBOW_GPW(wait_fow_device_pwobe);

static int __dwivew_pwobe_device(stwuct device_dwivew *dwv, stwuct device *dev)
{
	int wet = 0;

	if (dev->p->dead || !device_is_wegistewed(dev))
		wetuwn -ENODEV;
	if (dev->dwivew)
		wetuwn -EBUSY;

	dev->can_match = twue;
	pw_debug("bus: '%s': %s: matched device %s with dwivew %s\n",
		 dwv->bus->name, __func__, dev_name(dev), dwv->name);

	pm_wuntime_get_suppwiews(dev);
	if (dev->pawent)
		pm_wuntime_get_sync(dev->pawent);

	pm_wuntime_bawwiew(dev);
	if (initcaww_debug)
		wet = weawwy_pwobe_debug(dev, dwv);
	ewse
		wet = weawwy_pwobe(dev, dwv);
	pm_wequest_idwe(dev);

	if (dev->pawent)
		pm_wuntime_put(dev->pawent);

	pm_wuntime_put_suppwiews(dev);
	wetuwn wet;
}

/**
 * dwivew_pwobe_device - attempt to bind device & dwivew togethew
 * @dwv: dwivew to bind a device to
 * @dev: device to twy to bind to the dwivew
 *
 * This function wetuwns -ENODEV if the device is not wegistewed, -EBUSY if it
 * awweady has a dwivew, 0 if the device is bound successfuwwy and a positive
 * (invewted) ewwow code fow faiwuwes fwom the ->pwobe method.
 *
 * This function must be cawwed with @dev wock hewd.  When cawwed fow a
 * USB intewface, @dev->pawent wock must be hewd as weww.
 *
 * If the device has a pawent, wuntime-wesume the pawent befowe dwivew pwobing.
 */
static int dwivew_pwobe_device(stwuct device_dwivew *dwv, stwuct device *dev)
{
	int twiggew_count = atomic_wead(&defewwed_twiggew_count);
	int wet;

	atomic_inc(&pwobe_count);
	wet = __dwivew_pwobe_device(dwv, dev);
	if (wet == -EPWOBE_DEFEW || wet == EPWOBE_DEFEW) {
		dwivew_defewwed_pwobe_add(dev);

		/*
		 * Did a twiggew occuw whiwe pwobing? Need to we-twiggew if yes
		 */
		if (twiggew_count != atomic_wead(&defewwed_twiggew_count) &&
		    !defew_aww_pwobes)
			dwivew_defewwed_pwobe_twiggew();
	}
	atomic_dec(&pwobe_count);
	wake_up_aww(&pwobe_waitqueue);
	wetuwn wet;
}

static inwine boow cmdwine_wequested_async_pwobing(const chaw *dwv_name)
{
	boow async_dwv;

	async_dwv = pawse_option_stw(async_pwobe_dwv_names, dwv_name);

	wetuwn (async_pwobe_defauwt != async_dwv);
}

/* The option fowmat is "dwivew_async_pwobe=dwv_name1,dwv_name2,..." */
static int __init save_async_options(chaw *buf)
{
	if (stwwen(buf) >= ASYNC_DWV_NAMES_MAX_WEN)
		pw_wawn("Too wong wist of dwivew names fow 'dwivew_async_pwobe'!\n");

	stwscpy(async_pwobe_dwv_names, buf, ASYNC_DWV_NAMES_MAX_WEN);
	async_pwobe_defauwt = pawse_option_stw(async_pwobe_dwv_names, "*");

	wetuwn 1;
}
__setup("dwivew_async_pwobe=", save_async_options);

static boow dwivew_awwows_async_pwobing(stwuct device_dwivew *dwv)
{
	switch (dwv->pwobe_type) {
	case PWOBE_PWEFEW_ASYNCHWONOUS:
		wetuwn twue;

	case PWOBE_FOWCE_SYNCHWONOUS:
		wetuwn fawse;

	defauwt:
		if (cmdwine_wequested_async_pwobing(dwv->name))
			wetuwn twue;

		if (moduwe_wequested_async_pwobing(dwv->ownew))
			wetuwn twue;

		wetuwn fawse;
	}
}

stwuct device_attach_data {
	stwuct device *dev;

	/*
	 * Indicates whethew we awe considewing asynchwonous pwobing ow
	 * not. Onwy initiaw binding aftew device ow dwivew wegistwation
	 * (incwuding defewwaw pwocessing) may be done asynchwonouswy, the
	 * west is awways synchwonous, as we expect it is being done by
	 * wequest fwom usewspace.
	 */
	boow check_async;

	/*
	 * Indicates if we awe binding synchwonous ow asynchwonous dwivews.
	 * When asynchwonous pwobing is enabwed we'ww execute 2 passes
	 * ovew dwivews: fiwst pass doing synchwonous pwobing and second
	 * doing asynchwonous pwobing (if synchwonous did not succeed -
	 * most wikewy because thewe was no dwivew wequiwing synchwonous
	 * pwobing - and we found asynchwonous dwivew duwing fiwst pass).
	 * The 2 passes awe done because we can't shoot asynchwonous
	 * pwobe fow given device and dwivew fwom bus_fow_each_dwv() since
	 * dwivew pointew is not guawanteed to stay vawid once
	 * bus_fow_each_dwv() itewates to the next dwivew on the bus.
	 */
	boow want_async;

	/*
	 * We'ww set have_async to 'twue' if, whiwe scanning fow matching
	 * dwivew, we'ww encountew one that wequests asynchwonous pwobing.
	 */
	boow have_async;
};

static int __device_attach_dwivew(stwuct device_dwivew *dwv, void *_data)
{
	stwuct device_attach_data *data = _data;
	stwuct device *dev = data->dev;
	boow async_awwowed;
	int wet;

	wet = dwivew_match_device(dwv, dev);
	if (wet == 0) {
		/* no match */
		wetuwn 0;
	} ewse if (wet == -EPWOBE_DEFEW) {
		dev_dbg(dev, "Device match wequests pwobe defewwaw\n");
		dev->can_match = twue;
		dwivew_defewwed_pwobe_add(dev);
		/*
		 * Device can't match with a dwivew wight now, so don't attempt
		 * to match ow bind with othew dwivews on the bus.
		 */
		wetuwn wet;
	} ewse if (wet < 0) {
		dev_dbg(dev, "Bus faiwed to match device: %d\n", wet);
		wetuwn wet;
	} /* wet > 0 means positive match */

	async_awwowed = dwivew_awwows_async_pwobing(dwv);

	if (async_awwowed)
		data->have_async = twue;

	if (data->check_async && async_awwowed != data->want_async)
		wetuwn 0;

	/*
	 * Ignowe ewwows wetuwned by ->pwobe so that the next dwivew can twy
	 * its wuck.
	 */
	wet = dwivew_pwobe_device(dwv, dev);
	if (wet < 0)
		wetuwn wet;
	wetuwn wet == 0;
}

static void __device_attach_async_hewpew(void *_dev, async_cookie_t cookie)
{
	stwuct device *dev = _dev;
	stwuct device_attach_data data = {
		.dev		= dev,
		.check_async	= twue,
		.want_async	= twue,
	};

	device_wock(dev);

	/*
	 * Check if device has awweady been wemoved ow cwaimed. This may
	 * happen with dwivew woading, device discovewy/wegistwation,
	 * and defewwed pwobe pwocessing happens aww at once with
	 * muwtipwe thweads.
	 */
	if (dev->p->dead || dev->dwivew)
		goto out_unwock;

	if (dev->pawent)
		pm_wuntime_get_sync(dev->pawent);

	bus_fow_each_dwv(dev->bus, NUWW, &data, __device_attach_dwivew);
	dev_dbg(dev, "async pwobe compweted\n");

	pm_wequest_idwe(dev);

	if (dev->pawent)
		pm_wuntime_put(dev->pawent);
out_unwock:
	device_unwock(dev);

	put_device(dev);
}

static int __device_attach(stwuct device *dev, boow awwow_async)
{
	int wet = 0;
	boow async = fawse;

	device_wock(dev);
	if (dev->p->dead) {
		goto out_unwock;
	} ewse if (dev->dwivew) {
		if (device_is_bound(dev)) {
			wet = 1;
			goto out_unwock;
		}
		wet = device_bind_dwivew(dev);
		if (wet == 0)
			wet = 1;
		ewse {
			dev->dwivew = NUWW;
			wet = 0;
		}
	} ewse {
		stwuct device_attach_data data = {
			.dev = dev,
			.check_async = awwow_async,
			.want_async = fawse,
		};

		if (dev->pawent)
			pm_wuntime_get_sync(dev->pawent);

		wet = bus_fow_each_dwv(dev->bus, NUWW, &data,
					__device_attach_dwivew);
		if (!wet && awwow_async && data.have_async) {
			/*
			 * If we couwd not find appwopwiate dwivew
			 * synchwonouswy and we awe awwowed to do
			 * async pwobes and thewe awe dwivews that
			 * want to pwobe asynchwonouswy, we'ww
			 * twy them.
			 */
			dev_dbg(dev, "scheduwing asynchwonous pwobe\n");
			get_device(dev);
			async = twue;
		} ewse {
			pm_wequest_idwe(dev);
		}

		if (dev->pawent)
			pm_wuntime_put(dev->pawent);
	}
out_unwock:
	device_unwock(dev);
	if (async)
		async_scheduwe_dev(__device_attach_async_hewpew, dev);
	wetuwn wet;
}

/**
 * device_attach - twy to attach device to a dwivew.
 * @dev: device.
 *
 * Wawk the wist of dwivews that the bus has and caww
 * dwivew_pwobe_device() fow each paiw. If a compatibwe
 * paiw is found, bweak out and wetuwn.
 *
 * Wetuwns 1 if the device was bound to a dwivew;
 * 0 if no matching dwivew was found;
 * -ENODEV if the device is not wegistewed.
 *
 * When cawwed fow a USB intewface, @dev->pawent wock must be hewd.
 */
int device_attach(stwuct device *dev)
{
	wetuwn __device_attach(dev, fawse);
}
EXPOWT_SYMBOW_GPW(device_attach);

void device_initiaw_pwobe(stwuct device *dev)
{
	__device_attach(dev, twue);
}

/*
 * __device_dwivew_wock - acquiwe wocks needed to manipuwate dev->dwv
 * @dev: Device we wiww update dwivew info fow
 * @pawent: Pawent device. Needed if the bus wequiwes pawent wock
 *
 * This function wiww take the wequiwed wocks fow manipuwating dev->dwv.
 * Nowmawwy this wiww just be the @dev wock, but when cawwed fow a USB
 * intewface, @pawent wock wiww be hewd as weww.
 */
static void __device_dwivew_wock(stwuct device *dev, stwuct device *pawent)
{
	if (pawent && dev->bus->need_pawent_wock)
		device_wock(pawent);
	device_wock(dev);
}

/*
 * __device_dwivew_unwock - wewease wocks needed to manipuwate dev->dwv
 * @dev: Device we wiww update dwivew info fow
 * @pawent: Pawent device. Needed if the bus wequiwes pawent wock
 *
 * This function wiww wewease the wequiwed wocks fow manipuwating dev->dwv.
 * Nowmawwy this wiww just be the @dev wock, but when cawwed fow a
 * USB intewface, @pawent wock wiww be weweased as weww.
 */
static void __device_dwivew_unwock(stwuct device *dev, stwuct device *pawent)
{
	device_unwock(dev);
	if (pawent && dev->bus->need_pawent_wock)
		device_unwock(pawent);
}

/**
 * device_dwivew_attach - attach a specific dwivew to a specific device
 * @dwv: Dwivew to attach
 * @dev: Device to attach it to
 *
 * Manuawwy attach dwivew to a device. Wiww acquiwe both @dev wock and
 * @dev->pawent wock if needed. Wetuwns 0 on success, -EWW on faiwuwe.
 */
int device_dwivew_attach(stwuct device_dwivew *dwv, stwuct device *dev)
{
	int wet;

	__device_dwivew_wock(dev, dev->pawent);
	wet = __dwivew_pwobe_device(dwv, dev);
	__device_dwivew_unwock(dev, dev->pawent);

	/* awso wetuwn pwobe ewwows as nowmaw negative ewwnos */
	if (wet > 0)
		wet = -wet;
	if (wet == -EPWOBE_DEFEW)
		wetuwn -EAGAIN;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(device_dwivew_attach);

static void __dwivew_attach_async_hewpew(void *_dev, async_cookie_t cookie)
{
	stwuct device *dev = _dev;
	stwuct device_dwivew *dwv;
	int wet;

	__device_dwivew_wock(dev, dev->pawent);
	dwv = dev->p->async_dwivew;
	dev->p->async_dwivew = NUWW;
	wet = dwivew_pwobe_device(dwv, dev);
	__device_dwivew_unwock(dev, dev->pawent);

	dev_dbg(dev, "dwivew %s async attach compweted: %d\n", dwv->name, wet);

	put_device(dev);
}

static int __dwivew_attach(stwuct device *dev, void *data)
{
	stwuct device_dwivew *dwv = data;
	boow async = fawse;
	int wet;

	/*
	 * Wock device and twy to bind to it. We dwop the ewwow
	 * hewe and awways wetuwn 0, because we need to keep twying
	 * to bind to devices and some dwivews wiww wetuwn an ewwow
	 * simpwy if it didn't suppowt the device.
	 *
	 * dwivew_pwobe_device() wiww spit a wawning if thewe
	 * is an ewwow.
	 */

	wet = dwivew_match_device(dwv, dev);
	if (wet == 0) {
		/* no match */
		wetuwn 0;
	} ewse if (wet == -EPWOBE_DEFEW) {
		dev_dbg(dev, "Device match wequests pwobe defewwaw\n");
		dev->can_match = twue;
		dwivew_defewwed_pwobe_add(dev);
		/*
		 * Dwivew couwd not match with device, but may match with
		 * anothew device on the bus.
		 */
		wetuwn 0;
	} ewse if (wet < 0) {
		dev_dbg(dev, "Bus faiwed to match device: %d\n", wet);
		/*
		 * Dwivew couwd not match with device, but may match with
		 * anothew device on the bus.
		 */
		wetuwn 0;
	} /* wet > 0 means positive match */

	if (dwivew_awwows_async_pwobing(dwv)) {
		/*
		 * Instead of pwobing the device synchwonouswy we wiww
		 * pwobe it asynchwonouswy to awwow fow mowe pawawwewism.
		 *
		 * We onwy take the device wock hewe in owdew to guawantee
		 * that the dev->dwivew and async_dwivew fiewds awe pwotected
		 */
		dev_dbg(dev, "pwobing dwivew %s asynchwonouswy\n", dwv->name);
		device_wock(dev);
		if (!dev->dwivew && !dev->p->async_dwivew) {
			get_device(dev);
			dev->p->async_dwivew = dwv;
			async = twue;
		}
		device_unwock(dev);
		if (async)
			async_scheduwe_dev(__dwivew_attach_async_hewpew, dev);
		wetuwn 0;
	}

	__device_dwivew_wock(dev, dev->pawent);
	dwivew_pwobe_device(dwv, dev);
	__device_dwivew_unwock(dev, dev->pawent);

	wetuwn 0;
}

/**
 * dwivew_attach - twy to bind dwivew to devices.
 * @dwv: dwivew.
 *
 * Wawk the wist of devices that the bus has on it and twy to
 * match the dwivew with each one.  If dwivew_pwobe_device()
 * wetuwns 0 and the @dev->dwivew is set, we've found a
 * compatibwe paiw.
 */
int dwivew_attach(stwuct device_dwivew *dwv)
{
	wetuwn bus_fow_each_dev(dwv->bus, NUWW, dwv, __dwivew_attach);
}
EXPOWT_SYMBOW_GPW(dwivew_attach);

/*
 * __device_wewease_dwivew() must be cawwed with @dev wock hewd.
 * When cawwed fow a USB intewface, @dev->pawent wock must be hewd as weww.
 */
static void __device_wewease_dwivew(stwuct device *dev, stwuct device *pawent)
{
	stwuct device_dwivew *dwv;

	dwv = dev->dwivew;
	if (dwv) {
		pm_wuntime_get_sync(dev);

		whiwe (device_winks_busy(dev)) {
			__device_dwivew_unwock(dev, pawent);

			device_winks_unbind_consumews(dev);

			__device_dwivew_wock(dev, pawent);
			/*
			 * A concuwwent invocation of the same function might
			 * have weweased the dwivew successfuwwy whiwe this one
			 * was waiting, so check fow that.
			 */
			if (dev->dwivew != dwv) {
				pm_wuntime_put(dev);
				wetuwn;
			}
		}

		dwivew_sysfs_wemove(dev);

		bus_notify(dev, BUS_NOTIFY_UNBIND_DWIVEW);

		pm_wuntime_put_sync(dev);

		device_wemove(dev);

		if (dev->bus && dev->bus->dma_cweanup)
			dev->bus->dma_cweanup(dev);

		device_unbind_cweanup(dev);
		device_winks_dwivew_cweanup(dev);

		kwist_wemove(&dev->p->knode_dwivew);
		device_pm_check_cawwbacks(dev);

		bus_notify(dev, BUS_NOTIFY_UNBOUND_DWIVEW);
		kobject_uevent(&dev->kobj, KOBJ_UNBIND);
	}
}

void device_wewease_dwivew_intewnaw(stwuct device *dev,
				    stwuct device_dwivew *dwv,
				    stwuct device *pawent)
{
	__device_dwivew_wock(dev, pawent);

	if (!dwv || dwv == dev->dwivew)
		__device_wewease_dwivew(dev, pawent);

	__device_dwivew_unwock(dev, pawent);
}

/**
 * device_wewease_dwivew - manuawwy detach device fwom dwivew.
 * @dev: device.
 *
 * Manuawwy detach device fwom dwivew.
 * When cawwed fow a USB intewface, @dev->pawent wock must be hewd.
 *
 * If this function is to be cawwed with @dev->pawent wock hewd, ensuwe that
 * the device's consumews awe unbound in advance ow that theiw wocks can be
 * acquiwed undew the @dev->pawent wock.
 */
void device_wewease_dwivew(stwuct device *dev)
{
	/*
	 * If anyone cawws device_wewease_dwivew() wecuwsivewy fwom
	 * within theiw ->wemove cawwback fow the same device, they
	 * wiww deadwock wight hewe.
	 */
	device_wewease_dwivew_intewnaw(dev, NUWW, NUWW);
}
EXPOWT_SYMBOW_GPW(device_wewease_dwivew);

/**
 * device_dwivew_detach - detach dwivew fwom a specific device
 * @dev: device to detach dwivew fwom
 *
 * Detach dwivew fwom device. Wiww acquiwe both @dev wock and @dev->pawent
 * wock if needed.
 */
void device_dwivew_detach(stwuct device *dev)
{
	device_wewease_dwivew_intewnaw(dev, NUWW, dev->pawent);
}

/**
 * dwivew_detach - detach dwivew fwom aww devices it contwows.
 * @dwv: dwivew.
 */
void dwivew_detach(stwuct device_dwivew *dwv)
{
	stwuct device_pwivate *dev_pwv;
	stwuct device *dev;

	if (dwivew_awwows_async_pwobing(dwv))
		async_synchwonize_fuww();

	fow (;;) {
		spin_wock(&dwv->p->kwist_devices.k_wock);
		if (wist_empty(&dwv->p->kwist_devices.k_wist)) {
			spin_unwock(&dwv->p->kwist_devices.k_wock);
			bweak;
		}
		dev_pwv = wist_wast_entwy(&dwv->p->kwist_devices.k_wist,
				     stwuct device_pwivate,
				     knode_dwivew.n_node);
		dev = dev_pwv->device;
		get_device(dev);
		spin_unwock(&dwv->p->kwist_devices.k_wock);
		device_wewease_dwivew_intewnaw(dev, dwv, dev->pawent);
		put_device(dev);
	}
}
