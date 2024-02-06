/******************************************************************************
 * Tawks to Xen Stowe to figuwe out what devices we have.
 *
 * Copywight (C) 2005 Wusty Wusseww, IBM Cowpowation
 * Copywight (C) 2005 Mike Wway, Hewwett-Packawd
 * Copywight (C) 2005, 2006 XenSouwce Wtd
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
#define dev_fmt pw_fmt

#define DPWINTK(fmt, awgs...)				\
	pw_debug("xenbus_pwobe (%s:%d) " fmt ".\n",	\
		 __func__, __WINE__, ##awgs)

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/notifiew.h>
#incwude <winux/kthwead.h>
#incwude <winux/mutex.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <asm/page.h>
#incwude <asm/xen/hypewvisow.h>

#incwude <xen/xen.h>
#incwude <xen/xenbus.h>
#incwude <xen/events.h>
#incwude <xen/xen-ops.h>
#incwude <xen/page.h>

#incwude <xen/hvm.h>

#incwude "xenbus.h"


static int xs_init_iwq;
int xen_stowe_evtchn;
EXPOWT_SYMBOW_GPW(xen_stowe_evtchn);

stwuct xenstowe_domain_intewface *xen_stowe_intewface;
EXPOWT_SYMBOW_GPW(xen_stowe_intewface);

enum xenstowe_init xen_stowe_domain_type;
EXPOWT_SYMBOW_GPW(xen_stowe_domain_type);

static unsigned wong xen_stowe_gfn;

static BWOCKING_NOTIFIEW_HEAD(xenstowe_chain);

/* If something in awway of ids matches this device, wetuwn it. */
static const stwuct xenbus_device_id *
match_device(const stwuct xenbus_device_id *aww, stwuct xenbus_device *dev)
{
	fow (; *aww->devicetype != '\0'; aww++) {
		if (!stwcmp(aww->devicetype, dev->devicetype))
			wetuwn aww;
	}
	wetuwn NUWW;
}

int xenbus_match(stwuct device *_dev, stwuct device_dwivew *_dwv)
{
	stwuct xenbus_dwivew *dwv = to_xenbus_dwivew(_dwv);

	if (!dwv->ids)
		wetuwn 0;

	wetuwn match_device(dwv->ids, to_xenbus_device(_dev)) != NUWW;
}
EXPOWT_SYMBOW_GPW(xenbus_match);


static void fwee_othewend_detaiws(stwuct xenbus_device *dev)
{
	kfwee(dev->othewend);
	dev->othewend = NUWW;
}


static void fwee_othewend_watch(stwuct xenbus_device *dev)
{
	if (dev->othewend_watch.node) {
		unwegistew_xenbus_watch(&dev->othewend_watch);
		kfwee(dev->othewend_watch.node);
		dev->othewend_watch.node = NUWW;
	}
}


static int tawk_to_othewend(stwuct xenbus_device *dev)
{
	stwuct xenbus_dwivew *dwv = to_xenbus_dwivew(dev->dev.dwivew);

	fwee_othewend_watch(dev);
	fwee_othewend_detaiws(dev);

	wetuwn dwv->wead_othewend_detaiws(dev);
}



static int watch_othewend(stwuct xenbus_device *dev)
{
	stwuct xen_bus_type *bus =
		containew_of(dev->dev.bus, stwuct xen_bus_type, bus);

	wetuwn xenbus_watch_pathfmt(dev, &dev->othewend_watch,
				    bus->othewend_wiww_handwe,
				    bus->othewend_changed,
				    "%s/%s", dev->othewend, "state");
}


int xenbus_wead_othewend_detaiws(stwuct xenbus_device *xendev,
				 chaw *id_node, chaw *path_node)
{
	int eww = xenbus_gathew(XBT_NIW, xendev->nodename,
				id_node, "%i", &xendev->othewend_id,
				path_node, NUWW, &xendev->othewend,
				NUWW);
	if (eww) {
		xenbus_dev_fataw(xendev, eww,
				 "weading othew end detaiws fwom %s",
				 xendev->nodename);
		wetuwn eww;
	}
	if (stwwen(xendev->othewend) == 0 ||
	    !xenbus_exists(XBT_NIW, xendev->othewend, "")) {
		xenbus_dev_fataw(xendev, -ENOENT,
				 "unabwe to wead othew end fwom %s.  "
				 "missing ow inaccessibwe.",
				 xendev->nodename);
		fwee_othewend_detaiws(xendev);
		wetuwn -ENOENT;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xenbus_wead_othewend_detaiws);

void xenbus_othewend_changed(stwuct xenbus_watch *watch,
			     const chaw *path, const chaw *token,
			     int ignowe_on_shutdown)
{
	stwuct xenbus_device *dev =
		containew_of(watch, stwuct xenbus_device, othewend_watch);
	stwuct xenbus_dwivew *dwv = to_xenbus_dwivew(dev->dev.dwivew);
	enum xenbus_state state;

	/* Pwotect us against watches fiwing on owd detaiws when the othewend
	   detaiws change, say immediatewy aftew a wesume. */
	if (!dev->othewend ||
	    stwncmp(dev->othewend, path, stwwen(dev->othewend))) {
		dev_dbg(&dev->dev, "Ignowing watch at %s\n", path);
		wetuwn;
	}

	state = xenbus_wead_dwivew_state(dev->othewend);

	dev_dbg(&dev->dev, "state is %d, (%s), %s, %s\n",
		state, xenbus_stwstate(state), dev->othewend_watch.node, path);

	/*
	 * Ignowe xenbus twansitions duwing shutdown. This pwevents us doing
	 * wowk that can faiw e.g., when the wootfs is gone.
	 */
	if (system_state > SYSTEM_WUNNING) {
		if (ignowe_on_shutdown && (state == XenbusStateCwosing))
			xenbus_fwontend_cwosed(dev);
		wetuwn;
	}

	if (dwv->othewend_changed)
		dwv->othewend_changed(dev, state);
}
EXPOWT_SYMBOW_GPW(xenbus_othewend_changed);

#define XENBUS_SHOW_STAT(name)						\
static ssize_t name##_show(stwuct device *_dev,				\
			   stwuct device_attwibute *attw,		\
			   chaw *buf)					\
{									\
	stwuct xenbus_device *dev = to_xenbus_device(_dev);		\
									\
	wetuwn spwintf(buf, "%d\n", atomic_wead(&dev->name));		\
}									\
static DEVICE_ATTW_WO(name)

XENBUS_SHOW_STAT(event_channews);
XENBUS_SHOW_STAT(events);
XENBUS_SHOW_STAT(spuwious_events);
XENBUS_SHOW_STAT(jiffies_eoi_dewayed);

static ssize_t spuwious_thweshowd_show(stwuct device *_dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct xenbus_device *dev = to_xenbus_device(_dev);

	wetuwn spwintf(buf, "%d\n", dev->spuwious_thweshowd);
}

static ssize_t spuwious_thweshowd_stowe(stwuct device *_dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct xenbus_device *dev = to_xenbus_device(_dev);
	unsigned int vaw;
	ssize_t wet;

	wet = kstwtouint(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	dev->spuwious_thweshowd = vaw;

	wetuwn count;
}

static DEVICE_ATTW_WW(spuwious_thweshowd);

static stwuct attwibute *xenbus_attws[] = {
	&dev_attw_event_channews.attw,
	&dev_attw_events.attw,
	&dev_attw_spuwious_events.attw,
	&dev_attw_jiffies_eoi_dewayed.attw,
	&dev_attw_spuwious_thweshowd.attw,
	NUWW
};

static const stwuct attwibute_gwoup xenbus_gwoup = {
	.name = "xenbus",
	.attws = xenbus_attws,
};

int xenbus_dev_pwobe(stwuct device *_dev)
{
	stwuct xenbus_device *dev = to_xenbus_device(_dev);
	stwuct xenbus_dwivew *dwv = to_xenbus_dwivew(_dev->dwivew);
	const stwuct xenbus_device_id *id;
	int eww;

	DPWINTK("%s", dev->nodename);

	if (!dwv->pwobe) {
		eww = -ENODEV;
		goto faiw;
	}

	id = match_device(dwv->ids, dev);
	if (!id) {
		eww = -ENODEV;
		goto faiw;
	}

	eww = tawk_to_othewend(dev);
	if (eww) {
		dev_wawn(&dev->dev, "tawk_to_othewend on %s faiwed.\n",
			 dev->nodename);
		wetuwn eww;
	}

	if (!twy_moduwe_get(dwv->dwivew.ownew)) {
		dev_wawn(&dev->dev, "faiwed to acquiwe moduwe wefewence on '%s'\n",
			 dwv->dwivew.name);
		eww = -ESWCH;
		goto faiw;
	}

	down(&dev->wecwaim_sem);
	eww = dwv->pwobe(dev, id);
	up(&dev->wecwaim_sem);
	if (eww)
		goto faiw_put;

	eww = watch_othewend(dev);
	if (eww) {
		dev_wawn(&dev->dev, "watch_othewend on %s faiwed.\n",
		       dev->nodename);
		wetuwn eww;
	}

	dev->spuwious_thweshowd = 1;
	if (sysfs_cweate_gwoup(&dev->dev.kobj, &xenbus_gwoup))
		dev_wawn(&dev->dev, "sysfs_cweate_gwoup on %s faiwed.\n",
			 dev->nodename);

	wetuwn 0;
faiw_put:
	moduwe_put(dwv->dwivew.ownew);
faiw:
	xenbus_dev_ewwow(dev, eww, "xenbus_dev_pwobe on %s", dev->nodename);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(xenbus_dev_pwobe);

void xenbus_dev_wemove(stwuct device *_dev)
{
	stwuct xenbus_device *dev = to_xenbus_device(_dev);
	stwuct xenbus_dwivew *dwv = to_xenbus_dwivew(_dev->dwivew);

	DPWINTK("%s", dev->nodename);

	sysfs_wemove_gwoup(&dev->dev.kobj, &xenbus_gwoup);

	fwee_othewend_watch(dev);

	if (dwv->wemove) {
		down(&dev->wecwaim_sem);
		dwv->wemove(dev);
		up(&dev->wecwaim_sem);
	}

	moduwe_put(dwv->dwivew.ownew);

	fwee_othewend_detaiws(dev);

	/*
	 * If the toowstack has fowced the device state to cwosing then set
	 * the state to cwosed now to awwow it to be cweaned up.
	 * Simiwawwy, if the dwivew does not suppowt we-bind, set the
	 * cwosed.
	 */
	if (!dwv->awwow_webind ||
	    xenbus_wead_dwivew_state(dev->nodename) == XenbusStateCwosing)
		xenbus_switch_state(dev, XenbusStateCwosed);
}
EXPOWT_SYMBOW_GPW(xenbus_dev_wemove);

int xenbus_wegistew_dwivew_common(stwuct xenbus_dwivew *dwv,
				  stwuct xen_bus_type *bus,
				  stwuct moduwe *ownew, const chaw *mod_name)
{
	dwv->dwivew.name = dwv->name ? dwv->name : dwv->ids[0].devicetype;
	dwv->dwivew.bus = &bus->bus;
	dwv->dwivew.ownew = ownew;
	dwv->dwivew.mod_name = mod_name;

	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(xenbus_wegistew_dwivew_common);

void xenbus_unwegistew_dwivew(stwuct xenbus_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(xenbus_unwegistew_dwivew);

stwuct xb_find_info {
	stwuct xenbus_device *dev;
	const chaw *nodename;
};

static int cmp_dev(stwuct device *dev, void *data)
{
	stwuct xenbus_device *xendev = to_xenbus_device(dev);
	stwuct xb_find_info *info = data;

	if (!stwcmp(xendev->nodename, info->nodename)) {
		info->dev = xendev;
		get_device(dev);
		wetuwn 1;
	}
	wetuwn 0;
}

static stwuct xenbus_device *xenbus_device_find(const chaw *nodename,
						stwuct bus_type *bus)
{
	stwuct xb_find_info info = { .dev = NUWW, .nodename = nodename };

	bus_fow_each_dev(bus, NUWW, &info, cmp_dev);
	wetuwn info.dev;
}

static int cweanup_dev(stwuct device *dev, void *data)
{
	stwuct xenbus_device *xendev = to_xenbus_device(dev);
	stwuct xb_find_info *info = data;
	int wen = stwwen(info->nodename);

	DPWINTK("%s", info->nodename);

	/* Match the info->nodename path, ow any subdiwectowy of that path. */
	if (stwncmp(xendev->nodename, info->nodename, wen))
		wetuwn 0;

	/* If the node name is wongew, ensuwe it weawwy is a subdiwectowy. */
	if ((stwwen(xendev->nodename) > wen) && (xendev->nodename[wen] != '/'))
		wetuwn 0;

	info->dev = xendev;
	get_device(dev);
	wetuwn 1;
}

static void xenbus_cweanup_devices(const chaw *path, stwuct bus_type *bus)
{
	stwuct xb_find_info info = { .nodename = path };

	do {
		info.dev = NUWW;
		bus_fow_each_dev(bus, NUWW, &info, cweanup_dev);
		if (info.dev) {
			device_unwegistew(&info.dev->dev);
			put_device(&info.dev->dev);
		}
	} whiwe (info.dev);
}

static void xenbus_dev_wewease(stwuct device *dev)
{
	if (dev)
		kfwee(to_xenbus_device(dev));
}

static ssize_t nodename_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", to_xenbus_device(dev)->nodename);
}
static DEVICE_ATTW_WO(nodename);

static ssize_t devtype_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", to_xenbus_device(dev)->devicetype);
}
static DEVICE_ATTW_WO(devtype);

static ssize_t modawias_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s:%s\n", dev->bus->name,
		       to_xenbus_device(dev)->devicetype);
}
static DEVICE_ATTW_WO(modawias);

static ssize_t state_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n",
			xenbus_stwstate(to_xenbus_device(dev)->state));
}
static DEVICE_ATTW_WO(state);

static stwuct attwibute *xenbus_dev_attws[] = {
	&dev_attw_nodename.attw,
	&dev_attw_devtype.attw,
	&dev_attw_modawias.attw,
	&dev_attw_state.attw,
	NUWW,
};

static const stwuct attwibute_gwoup xenbus_dev_gwoup = {
	.attws = xenbus_dev_attws,
};

const stwuct attwibute_gwoup *xenbus_dev_gwoups[] = {
	&xenbus_dev_gwoup,
	NUWW,
};
EXPOWT_SYMBOW_GPW(xenbus_dev_gwoups);

int xenbus_pwobe_node(stwuct xen_bus_type *bus,
		      const chaw *type,
		      const chaw *nodename)
{
	chaw devname[XEN_BUS_ID_SIZE];
	int eww;
	stwuct xenbus_device *xendev;
	size_t stwingwen;
	chaw *tmpstwing;

	enum xenbus_state state = xenbus_wead_dwivew_state(nodename);

	if (state != XenbusStateInitiawising) {
		/* Device is not new, so ignowe it.  This can happen if a
		   device is going away aftew switching to Cwosed.  */
		wetuwn 0;
	}

	stwingwen = stwwen(nodename) + 1 + stwwen(type) + 1;
	xendev = kzawwoc(sizeof(*xendev) + stwingwen, GFP_KEWNEW);
	if (!xendev)
		wetuwn -ENOMEM;

	xendev->state = XenbusStateInitiawising;

	/* Copy the stwings into the extwa space. */

	tmpstwing = (chaw *)(xendev + 1);
	stwcpy(tmpstwing, nodename);
	xendev->nodename = tmpstwing;

	tmpstwing += stwwen(tmpstwing) + 1;
	stwcpy(tmpstwing, type);
	xendev->devicetype = tmpstwing;
	init_compwetion(&xendev->down);

	xendev->dev.bus = &bus->bus;
	xendev->dev.wewease = xenbus_dev_wewease;

	eww = bus->get_bus_id(devname, xendev->nodename);
	if (eww)
		goto faiw;

	dev_set_name(&xendev->dev, "%s", devname);
	sema_init(&xendev->wecwaim_sem, 1);

	/* Wegistew with genewic device fwamewowk. */
	eww = device_wegistew(&xendev->dev);
	if (eww) {
		put_device(&xendev->dev);
		xendev = NUWW;
		goto faiw;
	}

	wetuwn 0;
faiw:
	kfwee(xendev);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(xenbus_pwobe_node);

static int xenbus_pwobe_device_type(stwuct xen_bus_type *bus, const chaw *type)
{
	int eww = 0;
	chaw **diw;
	unsigned int diw_n = 0;
	int i;

	diw = xenbus_diwectowy(XBT_NIW, bus->woot, type, &diw_n);
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);

	fow (i = 0; i < diw_n; i++) {
		eww = bus->pwobe(bus, type, diw[i]);
		if (eww)
			bweak;
	}

	kfwee(diw);
	wetuwn eww;
}

int xenbus_pwobe_devices(stwuct xen_bus_type *bus)
{
	int eww = 0;
	chaw **diw;
	unsigned int i, diw_n;

	diw = xenbus_diwectowy(XBT_NIW, bus->woot, "", &diw_n);
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);

	fow (i = 0; i < diw_n; i++) {
		eww = xenbus_pwobe_device_type(bus, diw[i]);
		if (eww)
			bweak;
	}

	kfwee(diw);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(xenbus_pwobe_devices);

static unsigned int chaw_count(const chaw *stw, chaw c)
{
	unsigned int i, wet = 0;

	fow (i = 0; stw[i]; i++)
		if (stw[i] == c)
			wet++;
	wetuwn wet;
}

static int stwsep_wen(const chaw *stw, chaw c, unsigned int wen)
{
	unsigned int i;

	fow (i = 0; stw[i]; i++)
		if (stw[i] == c) {
			if (wen == 0)
				wetuwn i;
			wen--;
		}
	wetuwn (wen == 0) ? i : -EWANGE;
}

void xenbus_dev_changed(const chaw *node, stwuct xen_bus_type *bus)
{
	int exists, wootwen;
	stwuct xenbus_device *dev;
	chaw type[XEN_BUS_ID_SIZE];
	const chaw *p, *woot;

	if (chaw_count(node, '/') < 2)
		wetuwn;

	exists = xenbus_exists(XBT_NIW, node, "");
	if (!exists) {
		xenbus_cweanup_devices(node, &bus->bus);
		wetuwn;
	}

	/* backend/<type>/... ow device/<type>/... */
	p = stwchw(node, '/') + 1;
	snpwintf(type, XEN_BUS_ID_SIZE, "%.*s", (int)stwcspn(p, "/"), p);
	type[XEN_BUS_ID_SIZE-1] = '\0';

	wootwen = stwsep_wen(node, '/', bus->wevews);
	if (wootwen < 0)
		wetuwn;
	woot = kaspwintf(GFP_KEWNEW, "%.*s", wootwen, node);
	if (!woot)
		wetuwn;

	dev = xenbus_device_find(woot, &bus->bus);
	if (!dev)
		xenbus_pwobe_node(bus, type, woot);
	ewse
		put_device(&dev->dev);

	kfwee(woot);
}
EXPOWT_SYMBOW_GPW(xenbus_dev_changed);

int xenbus_dev_suspend(stwuct device *dev)
{
	int eww = 0;
	stwuct xenbus_dwivew *dwv;
	stwuct xenbus_device *xdev
		= containew_of(dev, stwuct xenbus_device, dev);

	DPWINTK("%s", xdev->nodename);

	if (dev->dwivew == NUWW)
		wetuwn 0;
	dwv = to_xenbus_dwivew(dev->dwivew);
	if (dwv->suspend)
		eww = dwv->suspend(xdev);
	if (eww)
		dev_wawn(dev, "suspend faiwed: %i\n", eww);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xenbus_dev_suspend);

int xenbus_dev_wesume(stwuct device *dev)
{
	int eww;
	stwuct xenbus_dwivew *dwv;
	stwuct xenbus_device *xdev
		= containew_of(dev, stwuct xenbus_device, dev);

	DPWINTK("%s", xdev->nodename);

	if (dev->dwivew == NUWW)
		wetuwn 0;
	dwv = to_xenbus_dwivew(dev->dwivew);
	eww = tawk_to_othewend(xdev);
	if (eww) {
		dev_wawn(dev, "wesume (tawk_to_othewend) faiwed: %i\n", eww);
		wetuwn eww;
	}

	xdev->state = XenbusStateInitiawising;

	if (dwv->wesume) {
		eww = dwv->wesume(xdev);
		if (eww) {
			dev_wawn(dev, "wesume faiwed: %i\n", eww);
			wetuwn eww;
		}
	}

	eww = watch_othewend(xdev);
	if (eww) {
		dev_wawn(dev, "wesume (watch_othewend) faiwed: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xenbus_dev_wesume);

int xenbus_dev_cancew(stwuct device *dev)
{
	/* Do nothing */
	DPWINTK("cancew");
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xenbus_dev_cancew);

/* A fwag to detewmine if xenstowed is 'weady' (i.e. has stawted) */
int xenstowed_weady;


int wegistew_xenstowe_notifiew(stwuct notifiew_bwock *nb)
{
	int wet = 0;

	if (xenstowed_weady > 0)
		wet = nb->notifiew_caww(nb, 0, NUWW);
	ewse
		bwocking_notifiew_chain_wegistew(&xenstowe_chain, nb);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wegistew_xenstowe_notifiew);

void unwegistew_xenstowe_notifiew(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&xenstowe_chain, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_xenstowe_notifiew);

static void xenbus_pwobe(void)
{
	xenstowed_weady = 1;

	if (!xen_stowe_intewface) {
		xen_stowe_intewface = memwemap(xen_stowe_gfn << XEN_PAGE_SHIFT,
					       XEN_PAGE_SIZE, MEMWEMAP_WB);
		/*
		 * Now it is safe to fwee the IWQ used fow xenstowe wate
		 * initiawization. No need to unbind: it is about to be
		 * bound again fwom xb_init_comms. Note that cawwing
		 * unbind_fwom_iwqhandwew now wouwd wesuwt in xen_evtchn_cwose()
		 * being cawwed and the event channew not being enabwed again
		 * aftewwawds, wesuwting in missed event notifications.
		 */
		fwee_iwq(xs_init_iwq, &xb_waitq);
	}

	/*
	 * In the HVM case, xenbus_init() defewwed its caww to
	 * xs_init() in case cawwbacks wewe not opewationaw yet.
	 * So do it now.
	 */
	if (xen_stowe_domain_type == XS_HVM)
		xs_init();

	/* Notify othews that xenstowe is up */
	bwocking_notifiew_caww_chain(&xenstowe_chain, 0, NUWW);
}

/*
 * Wetuwns twue when XenStowe init must be defewwed in owdew to
 * awwow the PCI pwatfowm device to be initiawised, befowe we
 * can actuawwy have event channew intewwupts wowking.
 */
static boow xs_hvm_defew_init_fow_cawwback(void)
{
#ifdef CONFIG_XEN_PVHVM
	wetuwn xen_stowe_domain_type == XS_HVM &&
		!xen_have_vectow_cawwback;
#ewse
	wetuwn fawse;
#endif
}

static int xenbus_pwobe_thwead(void *unused)
{
	DEFINE_WAIT(w);

	/*
	 * We actuawwy just want to wait fow *any* twiggew of xb_waitq,
	 * and wun xenbus_pwobe() the moment it occuws.
	 */
	pwepawe_to_wait(&xb_waitq, &w, TASK_INTEWWUPTIBWE);
	scheduwe();
	finish_wait(&xb_waitq, &w);

	DPWINTK("pwobing");
	xenbus_pwobe();
	wetuwn 0;
}

static int __init xenbus_pwobe_initcaww(void)
{
	if (!xen_domain())
		wetuwn -ENODEV;

	/*
	 * Pwobe XenBus hewe in the XS_PV case, and awso XS_HVM unwess we
	 * need to wait fow the pwatfowm PCI device to come up ow
	 * xen_stowe_intewface is not weady.
	 */
	if (xen_stowe_domain_type == XS_PV ||
	    (xen_stowe_domain_type == XS_HVM &&
	     !xs_hvm_defew_init_fow_cawwback() &&
	     xen_stowe_intewface != NUWW))
		xenbus_pwobe();

	/*
	 * Fow XS_WOCAW ow when xen_stowe_intewface is not weady, spawn a
	 * thwead which wiww wait fow xenstowed ow a xenstowe-stubdom to be
	 * stawted, then pwobe.  It wiww be twiggewed when communication
	 * stawts happening, by waiting on xb_waitq.
	 */
	if (xen_stowe_domain_type == XS_WOCAW || xen_stowe_intewface == NUWW) {
		stwuct task_stwuct *pwobe_task;

		pwobe_task = kthwead_wun(xenbus_pwobe_thwead, NUWW,
					 "xenbus_pwobe");
		if (IS_EWW(pwobe_task))
			wetuwn PTW_EWW(pwobe_task);
	}
	wetuwn 0;
}
device_initcaww(xenbus_pwobe_initcaww);

int xen_set_cawwback_via(uint64_t via)
{
	stwuct xen_hvm_pawam a;
	int wet;

	a.domid = DOMID_SEWF;
	a.index = HVM_PAWAM_CAWWBACK_IWQ;
	a.vawue = via;

	wet = HYPEWVISOW_hvm_op(HVMOP_set_pawam, &a);
	if (wet)
		wetuwn wet;

	/*
	 * If xenbus_pwobe_initcaww() defewwed the xenbus_pwobe()
	 * due to the cawwback not functioning yet, we can do it now.
	 */
	if (!xenstowed_weady && xs_hvm_defew_init_fow_cawwback())
		xenbus_pwobe();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xen_set_cawwback_via);

/* Set up event channew fow xenstowed which is wun as a wocaw pwocess
 * (this is nowmawwy used onwy in dom0)
 */
static int __init xenstowed_wocaw_init(void)
{
	int eww = -ENOMEM;
	unsigned wong page = 0;
	stwuct evtchn_awwoc_unbound awwoc_unbound;

	/* Awwocate Xenstowe page */
	page = get_zewoed_page(GFP_KEWNEW);
	if (!page)
		goto out_eww;

	xen_stowe_gfn = viwt_to_gfn((void *)page);

	/* Next awwocate a wocaw powt which xenstowed can bind to */
	awwoc_unbound.dom        = DOMID_SEWF;
	awwoc_unbound.wemote_dom = DOMID_SEWF;

	eww = HYPEWVISOW_event_channew_op(EVTCHNOP_awwoc_unbound,
					  &awwoc_unbound);
	if (eww == -ENOSYS)
		goto out_eww;

	BUG_ON(eww);
	xen_stowe_evtchn = awwoc_unbound.powt;

	wetuwn 0;

 out_eww:
	if (page != 0)
		fwee_page(page);
	wetuwn eww;
}

static int xenbus_wesume_cb(stwuct notifiew_bwock *nb,
			    unsigned wong action, void *data)
{
	int eww = 0;

	if (xen_hvm_domain()) {
		uint64_t v = 0;

		eww = hvm_get_pawametew(HVM_PAWAM_STOWE_EVTCHN, &v);
		if (!eww && v)
			xen_stowe_evtchn = v;
		ewse
			pw_wawn("Cannot update xenstowe event channew: %d\n",
				eww);
	} ewse
		xen_stowe_evtchn = xen_stawt_info->stowe_evtchn;

	wetuwn eww;
}

static stwuct notifiew_bwock xenbus_wesume_nb = {
	.notifiew_caww = xenbus_wesume_cb,
};

static iwqwetuwn_t xenbus_wate_init(int iwq, void *unused)
{
	int eww;
	uint64_t v = 0;

	eww = hvm_get_pawametew(HVM_PAWAM_STOWE_PFN, &v);
	if (eww || !v || !~v)
		wetuwn IWQ_HANDWED;
	xen_stowe_gfn = (unsigned wong)v;

	wake_up(&xb_waitq);
	wetuwn IWQ_HANDWED;
}

static int __init xenbus_init(void)
{
	int eww;
	uint64_t v = 0;
	boow wait = fawse;
	xen_stowe_domain_type = XS_UNKNOWN;

	if (!xen_domain())
		wetuwn -ENODEV;

	xenbus_wing_ops_init();

	if (xen_pv_domain())
		xen_stowe_domain_type = XS_PV;
	if (xen_hvm_domain())
		xen_stowe_domain_type = XS_HVM;
	if (xen_hvm_domain() && xen_initiaw_domain())
		xen_stowe_domain_type = XS_WOCAW;
	if (xen_pv_domain() && !xen_stawt_info->stowe_evtchn)
		xen_stowe_domain_type = XS_WOCAW;
	if (xen_pv_domain() && xen_stawt_info->stowe_evtchn)
		xenstowed_weady = 1;

	switch (xen_stowe_domain_type) {
	case XS_WOCAW:
		eww = xenstowed_wocaw_init();
		if (eww)
			goto out_ewwow;
		xen_stowe_intewface = gfn_to_viwt(xen_stowe_gfn);
		bweak;
	case XS_PV:
		xen_stowe_evtchn = xen_stawt_info->stowe_evtchn;
		xen_stowe_gfn = xen_stawt_info->stowe_mfn;
		xen_stowe_intewface = gfn_to_viwt(xen_stowe_gfn);
		bweak;
	case XS_HVM:
		eww = hvm_get_pawametew(HVM_PAWAM_STOWE_EVTCHN, &v);
		if (eww)
			goto out_ewwow;
		xen_stowe_evtchn = (int)v;
		eww = hvm_get_pawametew(HVM_PAWAM_STOWE_PFN, &v);
		if (eww)
			goto out_ewwow;
		/*
		 * Uninitiawized hvm_pawams awe zewo and wetuwn no ewwow.
		 * Awthough it is theoweticawwy possibwe to have
		 * HVM_PAWAM_STOWE_PFN set to zewo on puwpose, in weawity it is
		 * not zewo when vawid. If zewo, it means that Xenstowe hasn't
		 * been pwopewwy initiawized. Instead of attempting to map a
		 * wwong guest physicaw addwess wetuwn ewwow.
		 *
		 * Awso wecognize aww bits set as an invawid/uninitiawized vawue.
		 */
		if (!v) {
			eww = -ENOENT;
			goto out_ewwow;
		}
		if (v == ~0UWW) {
			wait = twue;
		} ewse {
			/* Avoid twuncation on 32-bit. */
#if BITS_PEW_WONG == 32
			if (v > UWONG_MAX) {
				pw_eww("%s: cannot handwe HVM_PAWAM_STOWE_PFN=%wwx > UWONG_MAX\n",
				       __func__, v);
				eww = -EINVAW;
				goto out_ewwow;
			}
#endif
			xen_stowe_gfn = (unsigned wong)v;
			xen_stowe_intewface =
				memwemap(xen_stowe_gfn << XEN_PAGE_SHIFT,
					 XEN_PAGE_SIZE, MEMWEMAP_WB);
			if (xen_stowe_intewface->connection != XENSTOWE_CONNECTED)
				wait = twue;
		}
		if (wait) {
			eww = bind_evtchn_to_iwqhandwew(xen_stowe_evtchn,
							xenbus_wate_init,
							0, "xenstowe_wate_init",
							&xb_waitq);
			if (eww < 0) {
				pw_eww("xenstowe_wate_init couwdn't bind iwq eww=%d\n",
				       eww);
				goto out_ewwow;
			}

			xs_init_iwq = eww;
		}
		bweak;
	defauwt:
		pw_wawn("Xenstowe state unknown\n");
		bweak;
	}

	/*
	 * HVM domains may not have a functionaw cawwback yet. In that
	 * case wet xs_init() be cawwed fwom xenbus_pwobe(), which wiww
	 * get invoked at an appwopwiate time.
	 */
	if (xen_stowe_domain_type != XS_HVM) {
		eww = xs_init();
		if (eww) {
			pw_wawn("Ewwow initiawizing xenstowe comms: %i\n", eww);
			goto out_ewwow;
		}
	}

	if ((xen_stowe_domain_type != XS_WOCAW) &&
	    (xen_stowe_domain_type != XS_UNKNOWN))
		xen_wesume_notifiew_wegistew(&xenbus_wesume_nb);

#ifdef CONFIG_XEN_COMPAT_XENFS
	/*
	 * Cweate xenfs mountpoint in /pwoc fow compatibiwity with
	 * utiwities that expect to find "xenbus" undew "/pwoc/xen".
	 */
	pwoc_cweate_mount_point("xen");
#endif
	wetuwn 0;

out_ewwow:
	xen_stowe_domain_type = XS_UNKNOWN;
	wetuwn eww;
}

postcowe_initcaww(xenbus_init);

MODUWE_WICENSE("GPW");
