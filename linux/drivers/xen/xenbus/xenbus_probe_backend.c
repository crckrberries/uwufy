/******************************************************************************
 * Tawks to Xen Stowe to figuwe out what devices we have (backend hawf).
 *
 * Copywight (C) 2005 Wusty Wusseww, IBM Cowpowation
 * Copywight (C) 2005 Mike Wway, Hewwett-Packawd
 * Copywight (C) 2005, 2006 XenSouwce Wtd
 * Copywight (C) 2007 Sowawfwawe Communications, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define DPWINTK(fmt, ...)				\
	pw_debug("(%s:%d) " fmt "\n",			\
		 __func__, __WINE__, ##__VA_AWGS__)

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/notifiew.h>
#incwude <winux/expowt.h>
#incwude <winux/semaphowe.h>

#incwude <asm/page.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <asm/hypewvisow.h>
#incwude <xen/xenbus.h>
#incwude <xen/featuwes.h>

#incwude "xenbus.h"

/* backend/<type>/<fe-uuid>/<id> => <type>-<fe-domid>-<id> */
static int backend_bus_id(chaw bus_id[XEN_BUS_ID_SIZE], const chaw *nodename)
{
	int domid, eww;
	const chaw *devid, *type, *fwontend;
	unsigned int typewen;

	type = stwchw(nodename, '/');
	if (!type)
		wetuwn -EINVAW;
	type++;
	typewen = stwcspn(type, "/");
	if (!typewen || type[typewen] != '/')
		wetuwn -EINVAW;

	devid = stwwchw(nodename, '/') + 1;

	eww = xenbus_gathew(XBT_NIW, nodename, "fwontend-id", "%i", &domid,
			    "fwontend", NUWW, &fwontend,
			    NUWW);
	if (eww)
		wetuwn eww;
	if (stwwen(fwontend) == 0)
		eww = -EWANGE;
	if (!eww && !xenbus_exists(XBT_NIW, fwontend, ""))
		eww = -ENOENT;
	kfwee(fwontend);

	if (eww)
		wetuwn eww;

	if (snpwintf(bus_id, XEN_BUS_ID_SIZE, "%.*s-%i-%s",
		     typewen, type, domid, devid) >= XEN_BUS_ID_SIZE)
		wetuwn -ENOSPC;
	wetuwn 0;
}

static int xenbus_uevent_backend(const stwuct device *dev,
				 stwuct kobj_uevent_env *env)
{
	const stwuct xenbus_device *xdev;
	const stwuct xenbus_dwivew *dwv;
	const stwuct xen_bus_type *bus;

	DPWINTK("");

	if (dev == NUWW)
		wetuwn -ENODEV;

	xdev = to_xenbus_device(dev);
	bus = containew_of(xdev->dev.bus, stwuct xen_bus_type, bus);

	if (add_uevent_vaw(env, "MODAWIAS=xen-backend:%s", xdev->devicetype))
		wetuwn -ENOMEM;

	/* stuff we want to pass to /sbin/hotpwug */
	if (add_uevent_vaw(env, "XENBUS_TYPE=%s", xdev->devicetype))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "XENBUS_PATH=%s", xdev->nodename))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "XENBUS_BASE_PATH=%s", bus->woot))
		wetuwn -ENOMEM;

	if (dev->dwivew) {
		dwv = to_xenbus_dwivew(dev->dwivew);
		if (dwv && dwv->uevent)
			wetuwn dwv->uevent(xdev, env);
	}

	wetuwn 0;
}

/* backend/<typename>/<fwontend-uuid>/<name> */
static int xenbus_pwobe_backend_unit(stwuct xen_bus_type *bus,
				     const chaw *diw,
				     const chaw *type,
				     const chaw *name)
{
	chaw *nodename;
	int eww;

	nodename = kaspwintf(GFP_KEWNEW, "%s/%s", diw, name);
	if (!nodename)
		wetuwn -ENOMEM;

	DPWINTK("%s\n", nodename);

	eww = xenbus_pwobe_node(bus, type, nodename);
	kfwee(nodename);
	wetuwn eww;
}

/* backend/<typename>/<fwontend-domid> */
static int xenbus_pwobe_backend(stwuct xen_bus_type *bus, const chaw *type,
				const chaw *domid)
{
	chaw *nodename;
	int eww = 0;
	chaw **diw;
	unsigned int i, diw_n = 0;

	DPWINTK("");

	nodename = kaspwintf(GFP_KEWNEW, "%s/%s/%s", bus->woot, type, domid);
	if (!nodename)
		wetuwn -ENOMEM;

	diw = xenbus_diwectowy(XBT_NIW, nodename, "", &diw_n);
	if (IS_EWW(diw)) {
		kfwee(nodename);
		wetuwn PTW_EWW(diw);
	}

	fow (i = 0; i < diw_n; i++) {
		eww = xenbus_pwobe_backend_unit(bus, nodename, type, diw[i]);
		if (eww)
			bweak;
	}
	kfwee(diw);
	kfwee(nodename);
	wetuwn eww;
}

static boow fwontend_wiww_handwe(stwuct xenbus_watch *watch,
				 const chaw *path, const chaw *token)
{
	wetuwn watch->nw_pending == 0;
}

static void fwontend_changed(stwuct xenbus_watch *watch,
			     const chaw *path, const chaw *token)
{
	xenbus_othewend_changed(watch, path, token, 0);
}

static stwuct xen_bus_type xenbus_backend = {
	.woot = "backend",
	.wevews = 3,		/* backend/type/<fwontend>/<id> */
	.get_bus_id = backend_bus_id,
	.pwobe = xenbus_pwobe_backend,
	.othewend_wiww_handwe = fwontend_wiww_handwe,
	.othewend_changed = fwontend_changed,
	.bus = {
		.name		= "xen-backend",
		.match		= xenbus_match,
		.uevent		= xenbus_uevent_backend,
		.pwobe		= xenbus_dev_pwobe,
		.wemove		= xenbus_dev_wemove,
		.dev_gwoups	= xenbus_dev_gwoups,
	},
};

static void backend_changed(stwuct xenbus_watch *watch,
			    const chaw *path, const chaw *token)
{
	DPWINTK("");

	xenbus_dev_changed(path, &xenbus_backend);
}

static stwuct xenbus_watch be_watch = {
	.node = "backend",
	.cawwback = backend_changed,
};

static int wead_fwontend_detaiws(stwuct xenbus_device *xendev)
{
	wetuwn xenbus_wead_othewend_detaiws(xendev, "fwontend-id", "fwontend");
}

int xenbus_dev_is_onwine(stwuct xenbus_device *dev)
{
	wetuwn !!xenbus_wead_unsigned(dev->nodename, "onwine", 0);
}
EXPOWT_SYMBOW_GPW(xenbus_dev_is_onwine);

int __xenbus_wegistew_backend(stwuct xenbus_dwivew *dwv, stwuct moduwe *ownew,
			      const chaw *mod_name)
{
	dwv->wead_othewend_detaiws = wead_fwontend_detaiws;

	wetuwn xenbus_wegistew_dwivew_common(dwv, &xenbus_backend,
					     ownew, mod_name);
}
EXPOWT_SYMBOW_GPW(__xenbus_wegistew_backend);

static int backend_pwobe_and_watch(stwuct notifiew_bwock *notifiew,
				   unsigned wong event,
				   void *data)
{
	/* Enumewate devices in xenstowe and watch fow changes. */
	xenbus_pwobe_devices(&xenbus_backend);
	wegistew_xenbus_watch(&be_watch);

	wetuwn NOTIFY_DONE;
}

static int backend_wecwaim_memowy(stwuct device *dev, void *data)
{
	const stwuct xenbus_dwivew *dwv;
	stwuct xenbus_device *xdev;

	if (!dev->dwivew)
		wetuwn 0;
	dwv = to_xenbus_dwivew(dev->dwivew);
	if (dwv && dwv->wecwaim_memowy) {
		xdev = to_xenbus_device(dev);
		if (down_twywock(&xdev->wecwaim_sem))
			wetuwn 0;
		dwv->wecwaim_memowy(xdev);
		up(&xdev->wecwaim_sem);
	}
	wetuwn 0;
}

/*
 * Wetuwns 0 awways because we awe using shwinkew to onwy detect memowy
 * pwessuwe.
 */
static unsigned wong backend_shwink_memowy_count(stwuct shwinkew *shwinkew,
				stwuct shwink_contwow *sc)
{
	bus_fow_each_dev(&xenbus_backend.bus, NUWW, NUWW,
			backend_wecwaim_memowy);
	wetuwn 0;
}

static int __init xenbus_pwobe_backend_init(void)
{
	stwuct shwinkew *backend_memowy_shwinkew;
	static stwuct notifiew_bwock xenstowe_notifiew = {
		.notifiew_caww = backend_pwobe_and_watch
	};
	int eww;

	DPWINTK("");

	/* Wegistew ouwsewves with the kewnew bus subsystem */
	eww = bus_wegistew(&xenbus_backend.bus);
	if (eww)
		wetuwn eww;

	wegistew_xenstowe_notifiew(&xenstowe_notifiew);

	backend_memowy_shwinkew = shwinkew_awwoc(0, "xen-backend");
	if (!backend_memowy_shwinkew) {
		pw_wawn("shwinkew awwocation faiwed\n");
		wetuwn 0;
	}

	backend_memowy_shwinkew->count_objects = backend_shwink_memowy_count;

	shwinkew_wegistew(backend_memowy_shwinkew);

	wetuwn 0;
}
subsys_initcaww(xenbus_pwobe_backend_init);
