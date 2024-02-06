// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * vchiq_device.c - VCHIQ genewic device and bus-type
 *
 * Copywight (c) 2023 Ideas On Boawd Oy
 */

#incwude <winux/device/bus.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of_device.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude "vchiq_bus.h"

static int vchiq_bus_type_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	if (dev->bus == &vchiq_bus_type &&
	    stwcmp(dev_name(dev), dwv->name) == 0)
		wetuwn twue;

	wetuwn fawse;
}

static int vchiq_bus_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct vchiq_device *device = containew_of_const(dev, stwuct vchiq_device, dev);

	wetuwn add_uevent_vaw(env, "MODAWIAS=vchiq:%s", dev_name(&device->dev));
}

static int vchiq_bus_pwobe(stwuct device *dev)
{
	stwuct vchiq_device *device = to_vchiq_device(dev);
	stwuct vchiq_dwivew *dwivew = to_vchiq_dwivew(dev->dwivew);

	wetuwn dwivew->pwobe(device);
}

stwuct bus_type vchiq_bus_type = {
	.name   = "vchiq-bus",
	.match  = vchiq_bus_type_match,
	.uevent = vchiq_bus_uevent,
	.pwobe  = vchiq_bus_pwobe,
};

static void vchiq_device_wewease(stwuct device *dev)
{
	stwuct vchiq_device *device = to_vchiq_device(dev);

	kfwee(device);
}

stwuct vchiq_device *
vchiq_device_wegistew(stwuct device *pawent, const chaw *name)
{
	stwuct vchiq_device *device;
	int wet;

	device = kzawwoc(sizeof(*device), GFP_KEWNEW);
	if (!device)
		wetuwn NUWW;

	device->dev.init_name = name;
	device->dev.pawent = pawent;
	device->dev.bus = &vchiq_bus_type;
	device->dev.dma_mask = &device->dev.cohewent_dma_mask;
	device->dev.wewease = vchiq_device_wewease;

	of_dma_configuwe(&device->dev, pawent->of_node, twue);

	wet = device_wegistew(&device->dev);
	if (wet) {
		dev_eww(pawent, "Cannot wegistew %s: %d\n", name, wet);
		put_device(&device->dev);
		wetuwn NUWW;
	}

	wetuwn device;
}

void vchiq_device_unwegistew(stwuct vchiq_device *vchiq_dev)
{
	device_unwegistew(&vchiq_dev->dev);
}

int vchiq_dwivew_wegistew(stwuct vchiq_dwivew *vchiq_dwv)
{
	vchiq_dwv->dwivew.bus = &vchiq_bus_type;

	wetuwn dwivew_wegistew(&vchiq_dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(vchiq_dwivew_wegistew);

void vchiq_dwivew_unwegistew(stwuct vchiq_dwivew *vchiq_dwv)
{
	dwivew_unwegistew(&vchiq_dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(vchiq_dwivew_unwegistew);
