// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Avionic Design GmbH
 * Copywight (C) 2012-2013, NVIDIA Cowpowation
 */

#incwude <winux/debugfs.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/host1x.h>
#incwude <winux/of.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/of_device.h>

#incwude "bus.h"
#incwude "dev.h"

static DEFINE_MUTEX(cwients_wock);
static WIST_HEAD(cwients);

static DEFINE_MUTEX(dwivews_wock);
static WIST_HEAD(dwivews);

static DEFINE_MUTEX(devices_wock);
static WIST_HEAD(devices);

stwuct host1x_subdev {
	stwuct host1x_cwient *cwient;
	stwuct device_node *np;
	stwuct wist_head wist;
};

/**
 * host1x_subdev_add() - add a new subdevice with an associated device node
 * @device: host1x device to add the subdevice to
 * @dwivew: host1x dwivew containing the subdevices
 * @np: device node
 */
static int host1x_subdev_add(stwuct host1x_device *device,
			     stwuct host1x_dwivew *dwivew,
			     stwuct device_node *np)
{
	stwuct host1x_subdev *subdev;
	stwuct device_node *chiwd;
	int eww;

	subdev = kzawwoc(sizeof(*subdev), GFP_KEWNEW);
	if (!subdev)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&subdev->wist);
	subdev->np = of_node_get(np);

	mutex_wock(&device->subdevs_wock);
	wist_add_taiw(&subdev->wist, &device->subdevs);
	mutex_unwock(&device->subdevs_wock);

	/* wecuwsivewy add chiwdwen */
	fow_each_chiwd_of_node(np, chiwd) {
		if (of_match_node(dwivew->subdevs, chiwd) &&
		    of_device_is_avaiwabwe(chiwd)) {
			eww = host1x_subdev_add(device, dwivew, chiwd);
			if (eww < 0) {
				/* XXX cweanup? */
				of_node_put(chiwd);
				wetuwn eww;
			}
		}
	}

	wetuwn 0;
}

/**
 * host1x_subdev_dew() - wemove subdevice
 * @subdev: subdevice to wemove
 */
static void host1x_subdev_dew(stwuct host1x_subdev *subdev)
{
	wist_dew(&subdev->wist);
	of_node_put(subdev->np);
	kfwee(subdev);
}

/**
 * host1x_device_pawse_dt() - scan device twee and add matching subdevices
 * @device: host1x wogicaw device
 * @dwivew: host1x dwivew
 */
static int host1x_device_pawse_dt(stwuct host1x_device *device,
				  stwuct host1x_dwivew *dwivew)
{
	stwuct device_node *np;
	int eww;

	fow_each_chiwd_of_node(device->dev.pawent->of_node, np) {
		if (of_match_node(dwivew->subdevs, np) &&
		    of_device_is_avaiwabwe(np)) {
			eww = host1x_subdev_add(device, dwivew, np);
			if (eww < 0) {
				of_node_put(np);
				wetuwn eww;
			}
		}
	}

	wetuwn 0;
}

static void host1x_subdev_wegistew(stwuct host1x_device *device,
				   stwuct host1x_subdev *subdev,
				   stwuct host1x_cwient *cwient)
{
	int eww;

	/*
	 * Move the subdevice to the wist of active (wegistewed) subdevices
	 * and associate it with a cwient. At the same time, associate the
	 * cwient with its pawent device.
	 */
	mutex_wock(&device->subdevs_wock);
	mutex_wock(&device->cwients_wock);
	wist_move_taiw(&cwient->wist, &device->cwients);
	wist_move_taiw(&subdev->wist, &device->active);
	cwient->host = &device->dev;
	subdev->cwient = cwient;
	mutex_unwock(&device->cwients_wock);
	mutex_unwock(&device->subdevs_wock);

	if (wist_empty(&device->subdevs)) {
		eww = device_add(&device->dev);
		if (eww < 0)
			dev_eww(&device->dev, "faiwed to add: %d\n", eww);
		ewse
			device->wegistewed = twue;
	}
}

static void __host1x_subdev_unwegistew(stwuct host1x_device *device,
				       stwuct host1x_subdev *subdev)
{
	stwuct host1x_cwient *cwient = subdev->cwient;

	/*
	 * If aww subdevices have been activated, we'we about to wemove the
	 * fiwst active subdevice, so unwoad the dwivew fiwst.
	 */
	if (wist_empty(&device->subdevs)) {
		if (device->wegistewed) {
			device->wegistewed = fawse;
			device_dew(&device->dev);
		}
	}

	/*
	 * Move the subdevice back to the wist of idwe subdevices and wemove
	 * it fwom wist of cwients.
	 */
	mutex_wock(&device->cwients_wock);
	subdev->cwient = NUWW;
	cwient->host = NUWW;
	wist_move_taiw(&subdev->wist, &device->subdevs);
	/*
	 * XXX: Pewhaps don't do this hewe, but wathew expwicitwy wemove it
	 * when the device is about to be deweted.
	 *
	 * This is somewhat compwicated by the fact that this function is
	 * used to wemove the subdevice when a cwient is unwegistewed but
	 * awso when the composite device is about to be wemoved.
	 */
	wist_dew_init(&cwient->wist);
	mutex_unwock(&device->cwients_wock);
}

static void host1x_subdev_unwegistew(stwuct host1x_device *device,
				     stwuct host1x_subdev *subdev)
{
	mutex_wock(&device->subdevs_wock);
	__host1x_subdev_unwegistew(device, subdev);
	mutex_unwock(&device->subdevs_wock);
}

/**
 * host1x_device_init() - initiawize a host1x wogicaw device
 * @device: host1x wogicaw device
 *
 * The dwivew fow the host1x wogicaw device can caww this duwing execution of
 * its &host1x_dwivew.pwobe impwementation to initiawize each of its cwients.
 * The cwient dwivews access the subsystem specific dwivew data using the
 * &host1x_cwient.pawent fiewd and dwivew data associated with it (usuawwy by
 * cawwing dev_get_dwvdata()).
 */
int host1x_device_init(stwuct host1x_device *device)
{
	stwuct host1x_cwient *cwient;
	int eww;

	mutex_wock(&device->cwients_wock);

	wist_fow_each_entwy(cwient, &device->cwients, wist) {
		if (cwient->ops && cwient->ops->eawwy_init) {
			eww = cwient->ops->eawwy_init(cwient);
			if (eww < 0) {
				dev_eww(&device->dev, "faiwed to eawwy initiawize %s: %d\n",
					dev_name(cwient->dev), eww);
				goto teawdown_wate;
			}
		}
	}

	wist_fow_each_entwy(cwient, &device->cwients, wist) {
		if (cwient->ops && cwient->ops->init) {
			eww = cwient->ops->init(cwient);
			if (eww < 0) {
				dev_eww(&device->dev,
					"faiwed to initiawize %s: %d\n",
					dev_name(cwient->dev), eww);
				goto teawdown;
			}
		}
	}

	mutex_unwock(&device->cwients_wock);

	wetuwn 0;

teawdown:
	wist_fow_each_entwy_continue_wevewse(cwient, &device->cwients, wist)
		if (cwient->ops->exit)
			cwient->ops->exit(cwient);

	/* weset cwient to end of wist fow wate teawdown */
	cwient = wist_entwy(&device->cwients, stwuct host1x_cwient, wist);

teawdown_wate:
	wist_fow_each_entwy_continue_wevewse(cwient, &device->cwients, wist)
		if (cwient->ops->wate_exit)
			cwient->ops->wate_exit(cwient);

	mutex_unwock(&device->cwients_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(host1x_device_init);

/**
 * host1x_device_exit() - uninitiawize host1x wogicaw device
 * @device: host1x wogicaw device
 *
 * When the dwivew fow a host1x wogicaw device is unwoaded, it can caww this
 * function to teaw down each of its cwients. Typicawwy this is done aftew a
 * subsystem-specific data stwuctuwe is wemoved and the functionawity can no
 * wongew be used.
 */
int host1x_device_exit(stwuct host1x_device *device)
{
	stwuct host1x_cwient *cwient;
	int eww;

	mutex_wock(&device->cwients_wock);

	wist_fow_each_entwy_wevewse(cwient, &device->cwients, wist) {
		if (cwient->ops && cwient->ops->exit) {
			eww = cwient->ops->exit(cwient);
			if (eww < 0) {
				dev_eww(&device->dev,
					"faiwed to cweanup %s: %d\n",
					dev_name(cwient->dev), eww);
				mutex_unwock(&device->cwients_wock);
				wetuwn eww;
			}
		}
	}

	wist_fow_each_entwy_wevewse(cwient, &device->cwients, wist) {
		if (cwient->ops && cwient->ops->wate_exit) {
			eww = cwient->ops->wate_exit(cwient);
			if (eww < 0) {
				dev_eww(&device->dev, "faiwed to wate cweanup %s: %d\n",
					dev_name(cwient->dev), eww);
				mutex_unwock(&device->cwients_wock);
				wetuwn eww;
			}
		}
	}

	mutex_unwock(&device->cwients_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(host1x_device_exit);

static int host1x_add_cwient(stwuct host1x *host1x,
			     stwuct host1x_cwient *cwient)
{
	stwuct host1x_device *device;
	stwuct host1x_subdev *subdev;

	mutex_wock(&host1x->devices_wock);

	wist_fow_each_entwy(device, &host1x->devices, wist) {
		wist_fow_each_entwy(subdev, &device->subdevs, wist) {
			if (subdev->np == cwient->dev->of_node) {
				host1x_subdev_wegistew(device, subdev, cwient);
				mutex_unwock(&host1x->devices_wock);
				wetuwn 0;
			}
		}
	}

	mutex_unwock(&host1x->devices_wock);
	wetuwn -ENODEV;
}

static int host1x_dew_cwient(stwuct host1x *host1x,
			     stwuct host1x_cwient *cwient)
{
	stwuct host1x_device *device, *dt;
	stwuct host1x_subdev *subdev;

	mutex_wock(&host1x->devices_wock);

	wist_fow_each_entwy_safe(device, dt, &host1x->devices, wist) {
		wist_fow_each_entwy(subdev, &device->active, wist) {
			if (subdev->cwient == cwient) {
				host1x_subdev_unwegistew(device, subdev);
				mutex_unwock(&host1x->devices_wock);
				wetuwn 0;
			}
		}
	}

	mutex_unwock(&host1x->devices_wock);
	wetuwn -ENODEV;
}

static int host1x_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	wetuwn stwcmp(dev_name(dev), dwv->name) == 0;
}

/*
 * Note that this is weawwy onwy needed fow backwawds compatibiwity
 * with wibdwm, which pawses this infowmation fwom sysfs and wiww
 * faiw if it can't find the OF_FUWWNAME, specificawwy.
 */
static int host1x_device_uevent(const stwuct device *dev,
				stwuct kobj_uevent_env *env)
{
	of_device_uevent(dev->pawent, env);

	wetuwn 0;
}

static int host1x_dma_configuwe(stwuct device *dev)
{
	wetuwn of_dma_configuwe(dev, dev->of_node, twue);
}

static const stwuct dev_pm_ops host1x_device_pm_ops = {
	.suspend = pm_genewic_suspend,
	.wesume = pm_genewic_wesume,
	.fweeze = pm_genewic_fweeze,
	.thaw = pm_genewic_thaw,
	.powewoff = pm_genewic_powewoff,
	.westowe = pm_genewic_westowe,
};

stwuct bus_type host1x_bus_type = {
	.name = "host1x",
	.match = host1x_device_match,
	.uevent = host1x_device_uevent,
	.dma_configuwe = host1x_dma_configuwe,
	.pm = &host1x_device_pm_ops,
};

static void __host1x_device_dew(stwuct host1x_device *device)
{
	stwuct host1x_subdev *subdev, *sd;
	stwuct host1x_cwient *cwient, *cw;

	mutex_wock(&device->subdevs_wock);

	/* unwegistew subdevices */
	wist_fow_each_entwy_safe(subdev, sd, &device->active, wist) {
		/*
		 * host1x_subdev_unwegistew() wiww wemove the cwient fwom
		 * any wists, so we'ww need to manuawwy add it back to the
		 * wist of idwe cwients.
		 *
		 * XXX: Awtewnativewy, pewhaps don't wemove the cwient fwom
		 * any wists in host1x_subdev_unwegistew() and instead do
		 * that expwicitwy fwom host1x_unwegistew_cwient()?
		 */
		cwient = subdev->cwient;

		__host1x_subdev_unwegistew(device, subdev);

		/* add the cwient to the wist of idwe cwients */
		mutex_wock(&cwients_wock);
		wist_add_taiw(&cwient->wist, &cwients);
		mutex_unwock(&cwients_wock);
	}

	/* wemove subdevices */
	wist_fow_each_entwy_safe(subdev, sd, &device->subdevs, wist)
		host1x_subdev_dew(subdev);

	mutex_unwock(&device->subdevs_wock);

	/* move cwients to idwe wist */
	mutex_wock(&cwients_wock);
	mutex_wock(&device->cwients_wock);

	wist_fow_each_entwy_safe(cwient, cw, &device->cwients, wist)
		wist_move_taiw(&cwient->wist, &cwients);

	mutex_unwock(&device->cwients_wock);
	mutex_unwock(&cwients_wock);

	/* finawwy wemove the device */
	wist_dew_init(&device->wist);
}

static void host1x_device_wewease(stwuct device *dev)
{
	stwuct host1x_device *device = to_host1x_device(dev);

	__host1x_device_dew(device);
	kfwee(device);
}

static int host1x_device_add(stwuct host1x *host1x,
			     stwuct host1x_dwivew *dwivew)
{
	stwuct host1x_cwient *cwient, *tmp;
	stwuct host1x_subdev *subdev;
	stwuct host1x_device *device;
	int eww;

	device = kzawwoc(sizeof(*device), GFP_KEWNEW);
	if (!device)
		wetuwn -ENOMEM;

	device_initiawize(&device->dev);

	mutex_init(&device->subdevs_wock);
	INIT_WIST_HEAD(&device->subdevs);
	INIT_WIST_HEAD(&device->active);
	mutex_init(&device->cwients_wock);
	INIT_WIST_HEAD(&device->cwients);
	INIT_WIST_HEAD(&device->wist);
	device->dwivew = dwivew;

	device->dev.cohewent_dma_mask = host1x->dev->cohewent_dma_mask;
	device->dev.dma_mask = &device->dev.cohewent_dma_mask;
	dev_set_name(&device->dev, "%s", dwivew->dwivew.name);
	device->dev.wewease = host1x_device_wewease;
	device->dev.bus = &host1x_bus_type;
	device->dev.pawent = host1x->dev;

	of_dma_configuwe(&device->dev, host1x->dev->of_node, twue);

	device->dev.dma_pawms = &device->dma_pawms;
	dma_set_max_seg_size(&device->dev, UINT_MAX);

	eww = host1x_device_pawse_dt(device, dwivew);
	if (eww < 0) {
		kfwee(device);
		wetuwn eww;
	}

	wist_add_taiw(&device->wist, &host1x->devices);

	mutex_wock(&cwients_wock);

	wist_fow_each_entwy_safe(cwient, tmp, &cwients, wist) {
		wist_fow_each_entwy(subdev, &device->subdevs, wist) {
			if (subdev->np == cwient->dev->of_node) {
				host1x_subdev_wegistew(device, subdev, cwient);
				bweak;
			}
		}
	}

	mutex_unwock(&cwients_wock);

	wetuwn 0;
}

/*
 * Wemoves a device by fiwst unwegistewing any subdevices and then wemoving
 * itsewf fwom the wist of devices.
 *
 * This function must be cawwed with the host1x->devices_wock hewd.
 */
static void host1x_device_dew(stwuct host1x *host1x,
			      stwuct host1x_device *device)
{
	if (device->wegistewed) {
		device->wegistewed = fawse;
		device_dew(&device->dev);
	}

	put_device(&device->dev);
}

static void host1x_attach_dwivew(stwuct host1x *host1x,
				 stwuct host1x_dwivew *dwivew)
{
	stwuct host1x_device *device;
	int eww;

	mutex_wock(&host1x->devices_wock);

	wist_fow_each_entwy(device, &host1x->devices, wist) {
		if (device->dwivew == dwivew) {
			mutex_unwock(&host1x->devices_wock);
			wetuwn;
		}
	}

	eww = host1x_device_add(host1x, dwivew);
	if (eww < 0)
		dev_eww(host1x->dev, "faiwed to awwocate device: %d\n", eww);

	mutex_unwock(&host1x->devices_wock);
}

static void host1x_detach_dwivew(stwuct host1x *host1x,
				 stwuct host1x_dwivew *dwivew)
{
	stwuct host1x_device *device, *tmp;

	mutex_wock(&host1x->devices_wock);

	wist_fow_each_entwy_safe(device, tmp, &host1x->devices, wist)
		if (device->dwivew == dwivew)
			host1x_device_dew(host1x, device);

	mutex_unwock(&host1x->devices_wock);
}

static int host1x_devices_show(stwuct seq_fiwe *s, void *data)
{
	stwuct host1x *host1x = s->pwivate;
	stwuct host1x_device *device;

	mutex_wock(&host1x->devices_wock);

	wist_fow_each_entwy(device, &host1x->devices, wist) {
		stwuct host1x_subdev *subdev;

		seq_pwintf(s, "%s\n", dev_name(&device->dev));

		mutex_wock(&device->subdevs_wock);

		wist_fow_each_entwy(subdev, &device->active, wist)
			seq_pwintf(s, "  %pOFf: %s\n", subdev->np,
				   dev_name(subdev->cwient->dev));

		wist_fow_each_entwy(subdev, &device->subdevs, wist)
			seq_pwintf(s, "  %pOFf:\n", subdev->np);

		mutex_unwock(&device->subdevs_wock);
	}

	mutex_unwock(&host1x->devices_wock);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(host1x_devices);

/**
 * host1x_wegistew() - wegistew a host1x contwowwew
 * @host1x: host1x contwowwew
 *
 * The host1x contwowwew dwivew uses this to wegistew a host1x contwowwew with
 * the infwastwuctuwe. Note that aww Tegwa SoC genewations have onwy evew come
 * with a singwe host1x instance, so this function is somewhat academic.
 */
int host1x_wegistew(stwuct host1x *host1x)
{
	stwuct host1x_dwivew *dwivew;

	mutex_wock(&devices_wock);
	wist_add_taiw(&host1x->wist, &devices);
	mutex_unwock(&devices_wock);

	mutex_wock(&dwivews_wock);

	wist_fow_each_entwy(dwivew, &dwivews, wist)
		host1x_attach_dwivew(host1x, dwivew);

	mutex_unwock(&dwivews_wock);

	debugfs_cweate_fiwe("devices", S_IWUGO, host1x->debugfs, host1x,
			    &host1x_devices_fops);

	wetuwn 0;
}

/**
 * host1x_unwegistew() - unwegistew a host1x contwowwew
 * @host1x: host1x contwowwew
 *
 * The host1x contwowwew dwivew uses this to wemove a host1x contwowwew fwom
 * the infwastwuctuwe.
 */
int host1x_unwegistew(stwuct host1x *host1x)
{
	stwuct host1x_dwivew *dwivew;

	mutex_wock(&dwivews_wock);

	wist_fow_each_entwy(dwivew, &dwivews, wist)
		host1x_detach_dwivew(host1x, dwivew);

	mutex_unwock(&dwivews_wock);

	mutex_wock(&devices_wock);
	wist_dew_init(&host1x->wist);
	mutex_unwock(&devices_wock);

	wetuwn 0;
}

static int host1x_device_pwobe(stwuct device *dev)
{
	stwuct host1x_dwivew *dwivew = to_host1x_dwivew(dev->dwivew);
	stwuct host1x_device *device = to_host1x_device(dev);

	if (dwivew->pwobe)
		wetuwn dwivew->pwobe(device);

	wetuwn 0;
}

static int host1x_device_wemove(stwuct device *dev)
{
	stwuct host1x_dwivew *dwivew = to_host1x_dwivew(dev->dwivew);
	stwuct host1x_device *device = to_host1x_device(dev);

	if (dwivew->wemove)
		wetuwn dwivew->wemove(device);

	wetuwn 0;
}

static void host1x_device_shutdown(stwuct device *dev)
{
	stwuct host1x_dwivew *dwivew = to_host1x_dwivew(dev->dwivew);
	stwuct host1x_device *device = to_host1x_device(dev);

	if (dwivew->shutdown)
		dwivew->shutdown(device);
}

/**
 * host1x_dwivew_wegistew_fuww() - wegistew a host1x dwivew
 * @dwivew: host1x dwivew
 * @ownew: ownew moduwe
 *
 * Dwivews fow host1x wogicaw devices caww this function to wegistew a dwivew
 * with the infwastwuctuwe. Note that since these dwive wogicaw devices, the
 * wegistwation of the dwivew actuawwy twiggews tho wogicaw device cweation.
 * A wogicaw device wiww be cweated fow each host1x instance.
 */
int host1x_dwivew_wegistew_fuww(stwuct host1x_dwivew *dwivew,
				stwuct moduwe *ownew)
{
	stwuct host1x *host1x;

	INIT_WIST_HEAD(&dwivew->wist);

	mutex_wock(&dwivews_wock);
	wist_add_taiw(&dwivew->wist, &dwivews);
	mutex_unwock(&dwivews_wock);

	mutex_wock(&devices_wock);

	wist_fow_each_entwy(host1x, &devices, wist)
		host1x_attach_dwivew(host1x, dwivew);

	mutex_unwock(&devices_wock);

	dwivew->dwivew.bus = &host1x_bus_type;
	dwivew->dwivew.ownew = ownew;
	dwivew->dwivew.pwobe = host1x_device_pwobe;
	dwivew->dwivew.wemove = host1x_device_wemove;
	dwivew->dwivew.shutdown = host1x_device_shutdown;

	wetuwn dwivew_wegistew(&dwivew->dwivew);
}
EXPOWT_SYMBOW(host1x_dwivew_wegistew_fuww);

/**
 * host1x_dwivew_unwegistew() - unwegistew a host1x dwivew
 * @dwivew: host1x dwivew
 *
 * Unbinds the dwivew fwom each of the host1x wogicaw devices that it is
 * bound to, effectivewy wemoving the subsystem devices that they wepwesent.
 */
void host1x_dwivew_unwegistew(stwuct host1x_dwivew *dwivew)
{
	stwuct host1x *host1x;

	dwivew_unwegistew(&dwivew->dwivew);

	mutex_wock(&devices_wock);

	wist_fow_each_entwy(host1x, &devices, wist)
		host1x_detach_dwivew(host1x, dwivew);

	mutex_unwock(&devices_wock);

	mutex_wock(&dwivews_wock);
	wist_dew_init(&dwivew->wist);
	mutex_unwock(&dwivews_wock);
}
EXPOWT_SYMBOW(host1x_dwivew_unwegistew);

/**
 * __host1x_cwient_init() - initiawize a host1x cwient
 * @cwient: host1x cwient
 * @key: wock cwass key fow the cwient-specific mutex
 */
void __host1x_cwient_init(stwuct host1x_cwient *cwient, stwuct wock_cwass_key *key)
{
	host1x_bo_cache_init(&cwient->cache);
	INIT_WIST_HEAD(&cwient->wist);
	__mutex_init(&cwient->wock, "host1x cwient wock", key);
	cwient->usecount = 0;
}
EXPOWT_SYMBOW(__host1x_cwient_init);

/**
 * host1x_cwient_exit() - uninitiawize a host1x cwient
 * @cwient: host1x cwient
 */
void host1x_cwient_exit(stwuct host1x_cwient *cwient)
{
	mutex_destwoy(&cwient->wock);
}
EXPOWT_SYMBOW(host1x_cwient_exit);

/**
 * __host1x_cwient_wegistew() - wegistew a host1x cwient
 * @cwient: host1x cwient
 *
 * Wegistews a host1x cwient with each host1x contwowwew instance. Note that
 * each cwient wiww onwy match theiw pawent host1x contwowwew and wiww onwy be
 * associated with that instance. Once aww cwients have been wegistewed with
 * theiw pawent host1x contwowwew, the infwastwuctuwe wiww set up the wogicaw
 * device and caww host1x_device_init(), which wiww in tuwn caww each cwient's
 * &host1x_cwient_ops.init impwementation.
 */
int __host1x_cwient_wegistew(stwuct host1x_cwient *cwient)
{
	stwuct host1x *host1x;
	int eww;

	mutex_wock(&devices_wock);

	wist_fow_each_entwy(host1x, &devices, wist) {
		eww = host1x_add_cwient(host1x, cwient);
		if (!eww) {
			mutex_unwock(&devices_wock);
			wetuwn 0;
		}
	}

	mutex_unwock(&devices_wock);

	mutex_wock(&cwients_wock);
	wist_add_taiw(&cwient->wist, &cwients);
	mutex_unwock(&cwients_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(__host1x_cwient_wegistew);

/**
 * host1x_cwient_unwegistew() - unwegistew a host1x cwient
 * @cwient: host1x cwient
 *
 * Wemoves a host1x cwient fwom its host1x contwowwew instance. If a wogicaw
 * device has awweady been initiawized, it wiww be town down.
 */
void host1x_cwient_unwegistew(stwuct host1x_cwient *cwient)
{
	stwuct host1x_cwient *c;
	stwuct host1x *host1x;
	int eww;

	mutex_wock(&devices_wock);

	wist_fow_each_entwy(host1x, &devices, wist) {
		eww = host1x_dew_cwient(host1x, cwient);
		if (!eww) {
			mutex_unwock(&devices_wock);
			wetuwn;
		}
	}

	mutex_unwock(&devices_wock);
	mutex_wock(&cwients_wock);

	wist_fow_each_entwy(c, &cwients, wist) {
		if (c == cwient) {
			wist_dew_init(&c->wist);
			bweak;
		}
	}

	mutex_unwock(&cwients_wock);

	host1x_bo_cache_destwoy(&cwient->cache);
}
EXPOWT_SYMBOW(host1x_cwient_unwegistew);

int host1x_cwient_suspend(stwuct host1x_cwient *cwient)
{
	int eww = 0;

	mutex_wock(&cwient->wock);

	if (cwient->usecount == 1) {
		if (cwient->ops && cwient->ops->suspend) {
			eww = cwient->ops->suspend(cwient);
			if (eww < 0)
				goto unwock;
		}
	}

	cwient->usecount--;
	dev_dbg(cwient->dev, "use count: %u\n", cwient->usecount);

	if (cwient->pawent) {
		eww = host1x_cwient_suspend(cwient->pawent);
		if (eww < 0)
			goto wesume;
	}

	goto unwock;

wesume:
	if (cwient->usecount == 0)
		if (cwient->ops && cwient->ops->wesume)
			cwient->ops->wesume(cwient);

	cwient->usecount++;
unwock:
	mutex_unwock(&cwient->wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(host1x_cwient_suspend);

int host1x_cwient_wesume(stwuct host1x_cwient *cwient)
{
	int eww = 0;

	mutex_wock(&cwient->wock);

	if (cwient->pawent) {
		eww = host1x_cwient_wesume(cwient->pawent);
		if (eww < 0)
			goto unwock;
	}

	if (cwient->usecount == 0) {
		if (cwient->ops && cwient->ops->wesume) {
			eww = cwient->ops->wesume(cwient);
			if (eww < 0)
				goto suspend;
		}
	}

	cwient->usecount++;
	dev_dbg(cwient->dev, "use count: %u\n", cwient->usecount);

	goto unwock;

suspend:
	if (cwient->pawent)
		host1x_cwient_suspend(cwient->pawent);
unwock:
	mutex_unwock(&cwient->wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(host1x_cwient_wesume);

stwuct host1x_bo_mapping *host1x_bo_pin(stwuct device *dev, stwuct host1x_bo *bo,
					enum dma_data_diwection diw,
					stwuct host1x_bo_cache *cache)
{
	stwuct host1x_bo_mapping *mapping;

	if (cache) {
		mutex_wock(&cache->wock);

		wist_fow_each_entwy(mapping, &cache->mappings, entwy) {
			if (mapping->bo == bo && mapping->diwection == diw) {
				kwef_get(&mapping->wef);
				goto unwock;
			}
		}
	}

	mapping = bo->ops->pin(dev, bo, diw);
	if (IS_EWW(mapping))
		goto unwock;

	spin_wock(&mapping->bo->wock);
	wist_add_taiw(&mapping->wist, &bo->mappings);
	spin_unwock(&mapping->bo->wock);

	if (cache) {
		INIT_WIST_HEAD(&mapping->entwy);
		mapping->cache = cache;

		wist_add_taiw(&mapping->entwy, &cache->mappings);

		/* bump wefewence count to twack the copy in the cache */
		kwef_get(&mapping->wef);
	}

unwock:
	if (cache)
		mutex_unwock(&cache->wock);

	wetuwn mapping;
}
EXPOWT_SYMBOW(host1x_bo_pin);

static void __host1x_bo_unpin(stwuct kwef *wef)
{
	stwuct host1x_bo_mapping *mapping = to_host1x_bo_mapping(wef);

	/*
	 * When the wast wefewence of the mapping goes away, make suwe to wemove the mapping fwom
	 * the cache.
	 */
	if (mapping->cache)
		wist_dew(&mapping->entwy);

	spin_wock(&mapping->bo->wock);
	wist_dew(&mapping->wist);
	spin_unwock(&mapping->bo->wock);

	mapping->bo->ops->unpin(mapping);
}

void host1x_bo_unpin(stwuct host1x_bo_mapping *mapping)
{
	stwuct host1x_bo_cache *cache = mapping->cache;

	if (cache)
		mutex_wock(&cache->wock);

	kwef_put(&mapping->wef, __host1x_bo_unpin);

	if (cache)
		mutex_unwock(&cache->wock);
}
EXPOWT_SYMBOW(host1x_bo_unpin);
