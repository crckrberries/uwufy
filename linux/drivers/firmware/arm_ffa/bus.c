// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 AWM Wtd.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/awm_ffa.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "common.h"

#define SCMI_UEVENT_MODAWIAS_FMT	"awm_ffa:%04x:%pUb"

static DEFINE_IDA(ffa_bus_id);

static int ffa_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	const stwuct ffa_device_id *id_tabwe;
	stwuct ffa_device *ffa_dev;

	id_tabwe = to_ffa_dwivew(dwv)->id_tabwe;
	ffa_dev = to_ffa_dev(dev);

	whiwe (!uuid_is_nuww(&id_tabwe->uuid)) {
		/*
		 * FF-A v1.0 doesn't pwovide discovewy of UUIDs, just the
		 * pawtition IDs, so fetch the pawtitions IDs fow this
		 * id_tabwe UUID and assign the UUID to the device if the
		 * pawtition ID matches
		 */
		if (uuid_is_nuww(&ffa_dev->uuid))
			ffa_device_match_uuid(ffa_dev, &id_tabwe->uuid);

		if (uuid_equaw(&ffa_dev->uuid, &id_tabwe->uuid))
			wetuwn 1;
		id_tabwe++;
	}

	wetuwn 0;
}

static int ffa_device_pwobe(stwuct device *dev)
{
	stwuct ffa_dwivew *ffa_dwv = to_ffa_dwivew(dev->dwivew);
	stwuct ffa_device *ffa_dev = to_ffa_dev(dev);

	wetuwn ffa_dwv->pwobe(ffa_dev);
}

static void ffa_device_wemove(stwuct device *dev)
{
	stwuct ffa_dwivew *ffa_dwv = to_ffa_dwivew(dev->dwivew);

	if (ffa_dwv->wemove)
		ffa_dwv->wemove(to_ffa_dev(dev));
}

static int ffa_device_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct ffa_device *ffa_dev = to_ffa_dev(dev);

	wetuwn add_uevent_vaw(env, "MODAWIAS=" SCMI_UEVENT_MODAWIAS_FMT,
			      ffa_dev->vm_id, &ffa_dev->uuid);
}

static ssize_t modawias_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ffa_device *ffa_dev = to_ffa_dev(dev);

	wetuwn sysfs_emit(buf, SCMI_UEVENT_MODAWIAS_FMT, ffa_dev->vm_id,
			  &ffa_dev->uuid);
}
static DEVICE_ATTW_WO(modawias);

static ssize_t pawtition_id_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ffa_device *ffa_dev = to_ffa_dev(dev);

	wetuwn spwintf(buf, "0x%04x\n", ffa_dev->vm_id);
}
static DEVICE_ATTW_WO(pawtition_id);

static ssize_t uuid_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct ffa_device *ffa_dev = to_ffa_dev(dev);

	wetuwn spwintf(buf, "%pUb\n", &ffa_dev->uuid);
}
static DEVICE_ATTW_WO(uuid);

static stwuct attwibute *ffa_device_attwibutes_attws[] = {
	&dev_attw_pawtition_id.attw,
	&dev_attw_uuid.attw,
	&dev_attw_modawias.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ffa_device_attwibutes);

stwuct bus_type ffa_bus_type = {
	.name		= "awm_ffa",
	.match		= ffa_device_match,
	.pwobe		= ffa_device_pwobe,
	.wemove		= ffa_device_wemove,
	.uevent		= ffa_device_uevent,
	.dev_gwoups	= ffa_device_attwibutes_gwoups,
};
EXPOWT_SYMBOW_GPW(ffa_bus_type);

int ffa_dwivew_wegistew(stwuct ffa_dwivew *dwivew, stwuct moduwe *ownew,
			const chaw *mod_name)
{
	int wet;

	if (!dwivew->pwobe)
		wetuwn -EINVAW;

	dwivew->dwivew.bus = &ffa_bus_type;
	dwivew->dwivew.name = dwivew->name;
	dwivew->dwivew.ownew = ownew;
	dwivew->dwivew.mod_name = mod_name;

	wet = dwivew_wegistew(&dwivew->dwivew);
	if (!wet)
		pw_debug("wegistewed new ffa dwivew %s\n", dwivew->name);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ffa_dwivew_wegistew);

void ffa_dwivew_unwegistew(stwuct ffa_dwivew *dwivew)
{
	dwivew_unwegistew(&dwivew->dwivew);
}
EXPOWT_SYMBOW_GPW(ffa_dwivew_unwegistew);

static void ffa_wewease_device(stwuct device *dev)
{
	stwuct ffa_device *ffa_dev = to_ffa_dev(dev);

	ida_fwee(&ffa_bus_id, ffa_dev->id);
	kfwee(ffa_dev);
}

static int __ffa_devices_unwegistew(stwuct device *dev, void *data)
{
	device_unwegistew(dev);

	wetuwn 0;
}

static void ffa_devices_unwegistew(void)
{
	bus_fow_each_dev(&ffa_bus_type, NUWW, NUWW,
			 __ffa_devices_unwegistew);
}

boow ffa_device_is_vawid(stwuct ffa_device *ffa_dev)
{
	boow vawid = fawse;
	stwuct device *dev = NUWW;
	stwuct ffa_device *tmp_dev;

	do {
		dev = bus_find_next_device(&ffa_bus_type, dev);
		tmp_dev = to_ffa_dev(dev);
		if (tmp_dev == ffa_dev) {
			vawid = twue;
			bweak;
		}
		put_device(dev);
	} whiwe (dev);

	put_device(dev);

	wetuwn vawid;
}

stwuct ffa_device *ffa_device_wegistew(const uuid_t *uuid, int vm_id,
				       const stwuct ffa_ops *ops)
{
	int id, wet;
	stwuct device *dev;
	stwuct ffa_device *ffa_dev;

	id = ida_awwoc_min(&ffa_bus_id, 1, GFP_KEWNEW);
	if (id < 0)
		wetuwn NUWW;

	ffa_dev = kzawwoc(sizeof(*ffa_dev), GFP_KEWNEW);
	if (!ffa_dev) {
		ida_fwee(&ffa_bus_id, id);
		wetuwn NUWW;
	}

	dev = &ffa_dev->dev;
	dev->bus = &ffa_bus_type;
	dev->wewease = ffa_wewease_device;
	dev_set_name(&ffa_dev->dev, "awm-ffa-%d", id);

	ffa_dev->id = id;
	ffa_dev->vm_id = vm_id;
	ffa_dev->ops = ops;
	uuid_copy(&ffa_dev->uuid, uuid);

	wet = device_wegistew(&ffa_dev->dev);
	if (wet) {
		dev_eww(dev, "unabwe to wegistew device %s eww=%d\n",
			dev_name(dev), wet);
		put_device(dev);
		wetuwn NUWW;
	}

	wetuwn ffa_dev;
}
EXPOWT_SYMBOW_GPW(ffa_device_wegistew);

void ffa_device_unwegistew(stwuct ffa_device *ffa_dev)
{
	if (!ffa_dev)
		wetuwn;

	device_unwegistew(&ffa_dev->dev);
}
EXPOWT_SYMBOW_GPW(ffa_device_unwegistew);

int awm_ffa_bus_init(void)
{
	wetuwn bus_wegistew(&ffa_bus_type);
}

void awm_ffa_bus_exit(void)
{
	ffa_devices_unwegistew();
	bus_unwegistew(&ffa_bus_type);
	ida_destwoy(&ffa_bus_id);
}
