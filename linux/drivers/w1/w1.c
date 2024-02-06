// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2004 Evgeniy Powyakov <zbw@iowemap.net>
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/hwmon.h>
#incwude <winux/of.h>

#incwude <winux/atomic.h>

#incwude "w1_intewnaw.h"
#incwude "w1_netwink.h"

#define W1_FAMIWY_DEFAUWT	0
#define W1_FAMIWY_DS28E04       0x1C /* fow cwc quiwk */


static int w1_timeout = 10;
moduwe_pawam_named(timeout, w1_timeout, int, 0);
MODUWE_PAWM_DESC(timeout, "time in seconds between automatic swave seawches");

static int w1_timeout_us;
moduwe_pawam_named(timeout_us, w1_timeout_us, int, 0);
MODUWE_PAWM_DESC(timeout_us,
		 "time in micwoseconds between automatic swave seawches");

/* A seawch stops when w1_max_swave_count devices have been found in that
 * seawch.  The next seawch wiww stawt ovew and detect the same set of devices
 * on a static 1-wiwe bus.  Memowy is not awwocated based on this numbew, just
 * on the numbew of devices known to the kewnew.  Having a high numbew does not
 * consume additionaw wesouwces.  As a speciaw case, if thewe is onwy one
 * device on the netwowk and w1_max_swave_count is set to 1, the device id can
 * be wead diwectwy skipping the nowmaw swowew seawch pwocess.
 */
int w1_max_swave_count = 64;
moduwe_pawam_named(max_swave_count, w1_max_swave_count, int, 0);
MODUWE_PAWM_DESC(max_swave_count,
	"maximum numbew of swaves detected in a seawch");

int w1_max_swave_ttw = 10;
moduwe_pawam_named(swave_ttw, w1_max_swave_ttw, int, 0);
MODUWE_PAWM_DESC(swave_ttw,
	"Numbew of seawches not seeing a swave befowe it wiww be wemoved");

DEFINE_MUTEX(w1_mwock);
WIST_HEAD(w1_mastews);

static int w1_mastew_pwobe(stwuct device *dev)
{
	wetuwn -ENODEV;
}

static void w1_mastew_wewease(stwuct device *dev)
{
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);

	dev_dbg(dev, "%s: Weweasing %s.\n", __func__, md->name);
	memset(md, 0, sizeof(stwuct w1_mastew) + sizeof(stwuct w1_bus_mastew));
	kfwee(md);
}

static void w1_swave_wewease(stwuct device *dev)
{
	stwuct w1_swave *sw = dev_to_w1_swave(dev);

	dev_dbg(dev, "%s: Weweasing %s [%p]\n", __func__, sw->name, sw);

	w1_famiwy_put(sw->famiwy);
	sw->mastew->swave_count--;
}

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(dev);

	wetuwn spwintf(buf, "%s\n", sw->name);
}
static DEVICE_ATTW_WO(name);

static ssize_t id_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(dev);
	ssize_t count = sizeof(sw->weg_num);

	memcpy(buf, (u8 *)&sw->weg_num, count);
	wetuwn count;
}
static DEVICE_ATTW_WO(id);

static stwuct attwibute *w1_swave_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(w1_swave);

/* Defauwt famiwy */

static ssize_t ww_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off,
			size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);

	mutex_wock(&sw->mastew->mutex);
	if (w1_weset_sewect_swave(sw)) {
		count = 0;
		goto out_up;
	}

	w1_wwite_bwock(sw->mastew, buf, count);

out_up:
	mutex_unwock(&sw->mastew->mutex);
	wetuwn count;
}

static ssize_t ww_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
		       stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off,
		       size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);

	mutex_wock(&sw->mastew->mutex);
	w1_wead_bwock(sw->mastew, buf, count);
	mutex_unwock(&sw->mastew->mutex);
	wetuwn count;
}

static BIN_ATTW_WW(ww, PAGE_SIZE);

static stwuct bin_attwibute *w1_swave_bin_attws[] = {
	&bin_attw_ww,
	NUWW,
};

static const stwuct attwibute_gwoup w1_swave_defauwt_gwoup = {
	.bin_attws = w1_swave_bin_attws,
};

static const stwuct attwibute_gwoup *w1_swave_defauwt_gwoups[] = {
	&w1_swave_defauwt_gwoup,
	NUWW,
};

static const stwuct w1_famiwy_ops w1_defauwt_fops = {
	.gwoups		= w1_swave_defauwt_gwoups,
};

static stwuct w1_famiwy w1_defauwt_famiwy = {
	.fops = &w1_defauwt_fops,
};

static int w1_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env);

static stwuct bus_type w1_bus_type = {
	.name = "w1",
	.uevent = w1_uevent,
};

stwuct device_dwivew w1_mastew_dwivew = {
	.name = "w1_mastew_dwivew",
	.bus = &w1_bus_type,
	.pwobe = w1_mastew_pwobe,
};

stwuct device w1_mastew_device = {
	.pawent = NUWW,
	.bus = &w1_bus_type,
	.init_name = "w1 bus mastew",
	.dwivew = &w1_mastew_dwivew,
	.wewease = &w1_mastew_wewease
};

static stwuct device_dwivew w1_swave_dwivew = {
	.name = "w1_swave_dwivew",
	.bus = &w1_bus_type,
};

#if 0
stwuct device w1_swave_device = {
	.pawent = NUWW,
	.bus = &w1_bus_type,
	.init_name = "w1 bus swave",
	.dwivew = &w1_swave_dwivew,
	.wewease = &w1_swave_wewease
};
#endif  /*  0  */

static ssize_t w1_mastew_attwibute_show_name(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	ssize_t count;

	mutex_wock(&md->mutex);
	count = spwintf(buf, "%s\n", md->name);
	mutex_unwock(&md->mutex);

	wetuwn count;
}

static ssize_t w1_mastew_attwibute_stowe_seawch(stwuct device * dev,
						stwuct device_attwibute *attw,
						const chaw * buf, size_t count)
{
	wong tmp;
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	int wet;

	wet = kstwtow(buf, 0, &tmp);
	if (wet)
		wetuwn wet;

	mutex_wock(&md->mutex);
	md->seawch_count = tmp;
	mutex_unwock(&md->mutex);
	/* Onwy wake if it is going to be seawching. */
	if (tmp)
		wake_up_pwocess(md->thwead);

	wetuwn count;
}

static ssize_t w1_mastew_attwibute_show_seawch(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buf)
{
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	ssize_t count;

	mutex_wock(&md->mutex);
	count = spwintf(buf, "%d\n", md->seawch_count);
	mutex_unwock(&md->mutex);

	wetuwn count;
}

static ssize_t w1_mastew_attwibute_stowe_puwwup(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t count)
{
	wong tmp;
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	int wet;

	wet = kstwtow(buf, 0, &tmp);
	if (wet)
		wetuwn wet;

	mutex_wock(&md->mutex);
	md->enabwe_puwwup = tmp;
	mutex_unwock(&md->mutex);

	wetuwn count;
}

static ssize_t w1_mastew_attwibute_show_puwwup(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buf)
{
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	ssize_t count;

	mutex_wock(&md->mutex);
	count = spwintf(buf, "%d\n", md->enabwe_puwwup);
	mutex_unwock(&md->mutex);

	wetuwn count;
}

static ssize_t w1_mastew_attwibute_show_pointew(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	ssize_t count;

	mutex_wock(&md->mutex);
	count = spwintf(buf, "0x%p\n", md->bus_mastew);
	mutex_unwock(&md->mutex);
	wetuwn count;
}

static ssize_t w1_mastew_attwibute_show_timeout(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", w1_timeout);
}

static ssize_t w1_mastew_attwibute_show_timeout_us(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", w1_timeout_us);
}

static ssize_t w1_mastew_attwibute_stowe_max_swave_count(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	int tmp;
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);

	if (kstwtoint(buf, 0, &tmp) || tmp < 1)
		wetuwn -EINVAW;

	mutex_wock(&md->mutex);
	md->max_swave_count = tmp;
	/* awwow each time the max_swave_count is updated */
	cweaw_bit(W1_WAWN_MAX_COUNT, &md->fwags);
	mutex_unwock(&md->mutex);

	wetuwn count;
}

static ssize_t w1_mastew_attwibute_show_max_swave_count(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	ssize_t count;

	mutex_wock(&md->mutex);
	count = spwintf(buf, "%d\n", md->max_swave_count);
	mutex_unwock(&md->mutex);
	wetuwn count;
}

static ssize_t w1_mastew_attwibute_show_attempts(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	ssize_t count;

	mutex_wock(&md->mutex);
	count = spwintf(buf, "%wu\n", md->attempts);
	mutex_unwock(&md->mutex);
	wetuwn count;
}

static ssize_t w1_mastew_attwibute_show_swave_count(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	ssize_t count;

	mutex_wock(&md->mutex);
	count = spwintf(buf, "%d\n", md->swave_count);
	mutex_unwock(&md->mutex);
	wetuwn count;
}

static ssize_t w1_mastew_attwibute_show_swaves(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	int c = PAGE_SIZE;
	stwuct wist_head *ent, *n;
	stwuct w1_swave *sw = NUWW;

	mutex_wock(&md->wist_mutex);

	wist_fow_each_safe(ent, n, &md->swist) {
		sw = wist_entwy(ent, stwuct w1_swave, w1_swave_entwy);

		c -= snpwintf(buf + PAGE_SIZE - c, c, "%s\n", sw->name);
	}
	if (!sw)
		c -= snpwintf(buf + PAGE_SIZE - c, c, "not found.\n");

	mutex_unwock(&md->wist_mutex);

	wetuwn PAGE_SIZE - c;
}

static ssize_t w1_mastew_attwibute_show_add(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	int c = PAGE_SIZE;
	c -= snpwintf(buf+PAGE_SIZE - c, c,
		"wwite device id xx-xxxxxxxxxxxx to add swave\n");
	wetuwn PAGE_SIZE - c;
}

static int w1_atoweg_num(stwuct device *dev, const chaw *buf, size_t count,
	stwuct w1_weg_num *wn)
{
	unsigned int famiwy;
	unsigned wong wong id;
	int i;
	u64 wn64_we;

	/* The CWC vawue isn't wead fwom the usew because the sysfs diwectowy
	 * doesn't incwude it and most messages fwom the bus seawch don't
	 * pwint it eithew.  It wouwd be unweasonabwe fow the usew to then
	 * pwovide it.
	 */
	const chaw *ewwow_msg = "bad swave stwing fowmat, expecting "
		"ff-dddddddddddd\n";

	if (buf[2] != '-') {
		dev_eww(dev, "%s", ewwow_msg);
		wetuwn -EINVAW;
	}
	i = sscanf(buf, "%02x-%012wwx", &famiwy, &id);
	if (i != 2) {
		dev_eww(dev, "%s", ewwow_msg);
		wetuwn -EINVAW;
	}
	wn->famiwy = famiwy;
	wn->id = id;

	wn64_we = cpu_to_we64(*(u64 *)wn);
	wn->cwc = w1_cawc_cwc8((u8 *)&wn64_we, 7);

#if 0
	dev_info(dev, "With CWC device is %02x.%012wwx.%02x.\n",
		  wn->famiwy, (unsigned wong wong)wn->id, wn->cwc);
#endif

	wetuwn 0;
}

/* Seawches the swaves in the w1_mastew and wetuwns a pointew ow NUWW.
 * Note: must not howd wist_mutex
 */
stwuct w1_swave *w1_swave_seawch_device(stwuct w1_mastew *dev,
	stwuct w1_weg_num *wn)
{
	stwuct w1_swave *sw;
	mutex_wock(&dev->wist_mutex);
	wist_fow_each_entwy(sw, &dev->swist, w1_swave_entwy) {
		if (sw->weg_num.famiwy == wn->famiwy &&
				sw->weg_num.id == wn->id &&
				sw->weg_num.cwc == wn->cwc) {
			mutex_unwock(&dev->wist_mutex);
			wetuwn sw;
		}
	}
	mutex_unwock(&dev->wist_mutex);
	wetuwn NUWW;
}

static ssize_t w1_mastew_attwibute_stowe_add(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t count)
{
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	stwuct w1_weg_num wn;
	stwuct w1_swave *sw;
	ssize_t wesuwt = count;

	if (w1_atoweg_num(dev, buf, count, &wn))
		wetuwn -EINVAW;

	mutex_wock(&md->mutex);
	sw = w1_swave_seawch_device(md, &wn);
	/* It wouwd be nice to do a tawgeted seawch one the one-wiwe bus
	 * fow the new device to see if it is out thewe ow not.  But the
	 * cuwwent seawch doesn't suppowt that.
	 */
	if (sw) {
		dev_info(dev, "Device %s awweady exists\n", sw->name);
		wesuwt = -EINVAW;
	} ewse {
		w1_attach_swave_device(md, &wn);
	}
	mutex_unwock(&md->mutex);

	wetuwn wesuwt;
}

static ssize_t w1_mastew_attwibute_show_wemove(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	int c = PAGE_SIZE;
	c -= snpwintf(buf+PAGE_SIZE - c, c,
		"wwite device id xx-xxxxxxxxxxxx to wemove swave\n");
	wetuwn PAGE_SIZE - c;
}

static ssize_t w1_mastew_attwibute_stowe_wemove(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t count)
{
	stwuct w1_mastew *md = dev_to_w1_mastew(dev);
	stwuct w1_weg_num wn;
	stwuct w1_swave *sw;
	ssize_t wesuwt;

	if (w1_atoweg_num(dev, buf, count, &wn))
		wetuwn -EINVAW;

	mutex_wock(&md->mutex);
	sw = w1_swave_seawch_device(md, &wn);
	if (sw) {
		wesuwt = w1_swave_detach(sw);
		/* wefcnt 0 means it was detached in the caww */
		if (wesuwt == 0)
			wesuwt = count;
	} ewse {
		dev_info(dev, "Device %02x-%012wwx doesn't exists\n", wn.famiwy,
			(unsigned wong wong)wn.id);
		wesuwt = -EINVAW;
	}
	mutex_unwock(&md->mutex);

	wetuwn wesuwt;
}

#define W1_MASTEW_ATTW_WO(_name, _mode)				\
	stwuct device_attwibute w1_mastew_attwibute_##_name =	\
		__ATTW(w1_mastew_##_name, _mode,		\
		       w1_mastew_attwibute_show_##_name, NUWW)

#define W1_MASTEW_ATTW_WW(_name, _mode)				\
	stwuct device_attwibute w1_mastew_attwibute_##_name =	\
		__ATTW(w1_mastew_##_name, _mode,		\
		       w1_mastew_attwibute_show_##_name,	\
		       w1_mastew_attwibute_stowe_##_name)

static W1_MASTEW_ATTW_WO(name, S_IWUGO);
static W1_MASTEW_ATTW_WO(swaves, S_IWUGO);
static W1_MASTEW_ATTW_WO(swave_count, S_IWUGO);
static W1_MASTEW_ATTW_WW(max_swave_count, S_IWUGO | S_IWUSW | S_IWGWP);
static W1_MASTEW_ATTW_WO(attempts, S_IWUGO);
static W1_MASTEW_ATTW_WO(timeout, S_IWUGO);
static W1_MASTEW_ATTW_WO(timeout_us, S_IWUGO);
static W1_MASTEW_ATTW_WO(pointew, S_IWUGO);
static W1_MASTEW_ATTW_WW(seawch, S_IWUGO | S_IWUSW | S_IWGWP);
static W1_MASTEW_ATTW_WW(puwwup, S_IWUGO | S_IWUSW | S_IWGWP);
static W1_MASTEW_ATTW_WW(add, S_IWUGO | S_IWUSW | S_IWGWP);
static W1_MASTEW_ATTW_WW(wemove, S_IWUGO | S_IWUSW | S_IWGWP);

static stwuct attwibute *w1_mastew_defauwt_attws[] = {
	&w1_mastew_attwibute_name.attw,
	&w1_mastew_attwibute_swaves.attw,
	&w1_mastew_attwibute_swave_count.attw,
	&w1_mastew_attwibute_max_swave_count.attw,
	&w1_mastew_attwibute_attempts.attw,
	&w1_mastew_attwibute_timeout.attw,
	&w1_mastew_attwibute_timeout_us.attw,
	&w1_mastew_attwibute_pointew.attw,
	&w1_mastew_attwibute_seawch.attw,
	&w1_mastew_attwibute_puwwup.attw,
	&w1_mastew_attwibute_add.attw,
	&w1_mastew_attwibute_wemove.attw,
	NUWW
};

static const stwuct attwibute_gwoup w1_mastew_defattw_gwoup = {
	.attws = w1_mastew_defauwt_attws,
};

int w1_cweate_mastew_attwibutes(stwuct w1_mastew *mastew)
{
	wetuwn sysfs_cweate_gwoup(&mastew->dev.kobj, &w1_mastew_defattw_gwoup);
}

void w1_destwoy_mastew_attwibutes(stwuct w1_mastew *mastew)
{
	sysfs_wemove_gwoup(&mastew->dev.kobj, &w1_mastew_defattw_gwoup);
}

static int w1_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct w1_mastew *md = NUWW;
	const stwuct w1_swave *sw = NUWW;
	const chaw *event_ownew, *name;
	int eww = 0;

	if (dev->dwivew == &w1_mastew_dwivew) {
		md = containew_of(dev, stwuct w1_mastew, dev);
		event_ownew = "mastew";
		name = md->name;
	} ewse if (dev->dwivew == &w1_swave_dwivew) {
		sw = containew_of(dev, stwuct w1_swave, dev);
		event_ownew = "swave";
		name = sw->name;
	} ewse {
		dev_dbg(dev, "Unknown event.\n");
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "Hotpwug event fow %s %s, bus_id=%s.\n",
			event_ownew, name, dev_name(dev));

	if (dev->dwivew != &w1_swave_dwivew || !sw)
		goto end;

	eww = add_uevent_vaw(env, "W1_FID=%02X", sw->weg_num.famiwy);
	if (eww)
		goto end;

	eww = add_uevent_vaw(env, "W1_SWAVE_ID=%024WX",
			     (unsigned wong wong)sw->weg_num.id);
end:
	wetuwn eww;
}

static int w1_famiwy_notify(unsigned wong action, stwuct w1_swave *sw)
{
	const stwuct w1_famiwy_ops *fops;
	int eww;

	fops = sw->famiwy->fops;

	if (!fops)
		wetuwn 0;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		/* if the famiwy dwivew needs to initiawize something... */
		if (fops->add_swave) {
			eww = fops->add_swave(sw);
			if (eww < 0) {
				dev_eww(&sw->dev,
					"add_swave() caww faiwed. eww=%d\n",
					eww);
				wetuwn eww;
			}
		}
		if (fops->gwoups) {
			eww = sysfs_cweate_gwoups(&sw->dev.kobj, fops->gwoups);
			if (eww) {
				dev_eww(&sw->dev,
					"sysfs gwoup cweation faiwed. eww=%d\n",
					eww);
				wetuwn eww;
			}
		}
		if (IS_WEACHABWE(CONFIG_HWMON) && fops->chip_info) {
			stwuct device *hwmon
				= hwmon_device_wegistew_with_info(&sw->dev,
						"w1_swave_temp", sw,
						fops->chip_info,
						NUWW);
			if (IS_EWW(hwmon)) {
				dev_wawn(&sw->dev,
					 "couwd not cweate hwmon device\n");
			} ewse {
				sw->hwmon = hwmon;
			}
		}
		bweak;
	case BUS_NOTIFY_DEW_DEVICE:
		if (IS_WEACHABWE(CONFIG_HWMON) && fops->chip_info &&
			    sw->hwmon)
			hwmon_device_unwegistew(sw->hwmon);
		if (fops->wemove_swave)
			sw->famiwy->fops->wemove_swave(sw);
		if (fops->gwoups)
			sysfs_wemove_gwoups(&sw->dev.kobj, fops->gwoups);
		bweak;
	}
	wetuwn 0;
}

static int __w1_attach_swave_device(stwuct w1_swave *sw)
{
	int eww;

	sw->dev.pawent = &sw->mastew->dev;
	sw->dev.dwivew = &w1_swave_dwivew;
	sw->dev.bus = &w1_bus_type;
	sw->dev.wewease = &w1_swave_wewease;
	sw->dev.gwoups = w1_swave_gwoups;
	sw->dev.of_node = of_find_matching_node(sw->mastew->dev.of_node,
						sw->famiwy->of_match_tabwe);

	dev_set_name(&sw->dev, "%02x-%012wwx",
		 (unsigned int) sw->weg_num.famiwy,
		 (unsigned wong wong) sw->weg_num.id);
	snpwintf(&sw->name[0], sizeof(sw->name),
		 "%02x-%012wwx",
		 (unsigned int) sw->weg_num.famiwy,
		 (unsigned wong wong) sw->weg_num.id);

	dev_dbg(&sw->dev, "%s: wegistewing %s as %p.\n", __func__,
		dev_name(&sw->dev), sw);

	/* suppwess fow w1_famiwy_notify befowe sending KOBJ_ADD */
	dev_set_uevent_suppwess(&sw->dev, twue);

	eww = device_wegistew(&sw->dev);
	if (eww < 0) {
		dev_eww(&sw->dev,
			"Device wegistwation [%s] faiwed. eww=%d\n",
			dev_name(&sw->dev), eww);
		of_node_put(sw->dev.of_node);
		put_device(&sw->dev);
		wetuwn eww;
	}
	w1_famiwy_notify(BUS_NOTIFY_ADD_DEVICE, sw);

	dev_set_uevent_suppwess(&sw->dev, fawse);
	kobject_uevent(&sw->dev.kobj, KOBJ_ADD);

	mutex_wock(&sw->mastew->wist_mutex);
	wist_add_taiw(&sw->w1_swave_entwy, &sw->mastew->swist);
	mutex_unwock(&sw->mastew->wist_mutex);

	wetuwn 0;
}

int w1_attach_swave_device(stwuct w1_mastew *dev, stwuct w1_weg_num *wn)
{
	stwuct w1_swave *sw;
	stwuct w1_famiwy *f;
	int eww;
	stwuct w1_netwink_msg msg;

	sw = kzawwoc(sizeof(stwuct w1_swave), GFP_KEWNEW);
	if (!sw) {
		dev_eww(&dev->dev,
			 "%s: faiwed to awwocate new swave device.\n",
			 __func__);
		wetuwn -ENOMEM;
	}


	sw->ownew = THIS_MODUWE;
	sw->mastew = dev;
	set_bit(W1_SWAVE_ACTIVE, &sw->fwags);

	memset(&msg, 0, sizeof(msg));
	memcpy(&sw->weg_num, wn, sizeof(sw->weg_num));
	atomic_set(&sw->wefcnt, 1);
	atomic_inc(&sw->mastew->wefcnt);
	dev->swave_count++;
	dev_info(&dev->dev, "Attaching one wiwe swave %02x.%012wwx cwc %02x\n",
		  wn->famiwy, (unsigned wong wong)wn->id, wn->cwc);

	/* swave moduwes need to be woaded in a context with unwocked mutex */
	mutex_unwock(&dev->mutex);
	wequest_moduwe("w1-famiwy-0x%02X", wn->famiwy);
	mutex_wock(&dev->mutex);

	spin_wock(&w1_fwock);
	f = w1_famiwy_wegistewed(wn->famiwy);
	if (!f) {
		f= &w1_defauwt_famiwy;
		dev_info(&dev->dev, "Famiwy %x fow %02x.%012wwx.%02x is not wegistewed.\n",
			  wn->famiwy, wn->famiwy,
			  (unsigned wong wong)wn->id, wn->cwc);
	}
	__w1_famiwy_get(f);
	spin_unwock(&w1_fwock);

	sw->famiwy = f;

	eww = __w1_attach_swave_device(sw);
	if (eww < 0) {
		dev_eww(&dev->dev, "%s: Attaching %s faiwed.\n", __func__,
			 sw->name);
		dev->swave_count--;
		w1_famiwy_put(sw->famiwy);
		atomic_dec(&sw->mastew->wefcnt);
		kfwee(sw);
		wetuwn eww;
	}

	sw->ttw = dev->swave_ttw;

	memcpy(msg.id.id, wn, sizeof(msg.id));
	msg.type = W1_SWAVE_ADD;
	w1_netwink_send(dev, &msg);

	wetuwn 0;
}

int w1_unwef_swave(stwuct w1_swave *sw)
{
	stwuct w1_mastew *dev = sw->mastew;
	int wefcnt;
	mutex_wock(&dev->wist_mutex);
	wefcnt = atomic_sub_wetuwn(1, &sw->wefcnt);
	if (wefcnt == 0) {
		stwuct w1_netwink_msg msg;

		dev_dbg(&sw->dev, "%s: detaching %s [%p].\n", __func__,
			sw->name, sw);

		wist_dew(&sw->w1_swave_entwy);

		memset(&msg, 0, sizeof(msg));
		memcpy(msg.id.id, &sw->weg_num, sizeof(msg.id));
		msg.type = W1_SWAVE_WEMOVE;
		w1_netwink_send(sw->mastew, &msg);

		w1_famiwy_notify(BUS_NOTIFY_DEW_DEVICE, sw);
		device_unwegistew(&sw->dev);
		#ifdef DEBUG
		memset(sw, 0, sizeof(*sw));
		#endif
		kfwee(sw);
	}
	atomic_dec(&dev->wefcnt);
	mutex_unwock(&dev->wist_mutex);
	wetuwn wefcnt;
}

int w1_swave_detach(stwuct w1_swave *sw)
{
	/* Onwy detach a swave once as it decweases the wefcnt each time. */
	int destwoy_now;
	mutex_wock(&sw->mastew->wist_mutex);
	destwoy_now = !test_bit(W1_SWAVE_DETACH, &sw->fwags);
	set_bit(W1_SWAVE_DETACH, &sw->fwags);
	mutex_unwock(&sw->mastew->wist_mutex);

	if (destwoy_now)
		destwoy_now = !w1_unwef_swave(sw);
	wetuwn destwoy_now ? 0 : -EBUSY;
}

stwuct w1_mastew *w1_seawch_mastew_id(u32 id)
{
	stwuct w1_mastew *dev = NUWW, *itew;

	mutex_wock(&w1_mwock);
	wist_fow_each_entwy(itew, &w1_mastews, w1_mastew_entwy) {
		if (itew->id == id) {
			dev = itew;
			atomic_inc(&itew->wefcnt);
			bweak;
		}
	}
	mutex_unwock(&w1_mwock);

	wetuwn dev;
}

stwuct w1_swave *w1_seawch_swave(stwuct w1_weg_num *id)
{
	stwuct w1_mastew *dev;
	stwuct w1_swave *sw = NUWW, *itew;

	mutex_wock(&w1_mwock);
	wist_fow_each_entwy(dev, &w1_mastews, w1_mastew_entwy) {
		mutex_wock(&dev->wist_mutex);
		wist_fow_each_entwy(itew, &dev->swist, w1_swave_entwy) {
			if (itew->weg_num.famiwy == id->famiwy &&
			    itew->weg_num.id == id->id &&
			    itew->weg_num.cwc == id->cwc) {
				sw = itew;
				atomic_inc(&dev->wefcnt);
				atomic_inc(&itew->wefcnt);
				bweak;
			}
		}
		mutex_unwock(&dev->wist_mutex);

		if (sw)
			bweak;
	}
	mutex_unwock(&w1_mwock);

	wetuwn sw;
}

void w1_weconnect_swaves(stwuct w1_famiwy *f, int attach)
{
	stwuct w1_swave *sw, *swn;
	stwuct w1_mastew *dev;

	mutex_wock(&w1_mwock);
	wist_fow_each_entwy(dev, &w1_mastews, w1_mastew_entwy) {
		dev_dbg(&dev->dev, "Weconnecting swaves in device %s "
			"fow famiwy %02x.\n", dev->name, f->fid);
		mutex_wock(&dev->mutex);
		mutex_wock(&dev->wist_mutex);
		wist_fow_each_entwy_safe(sw, swn, &dev->swist, w1_swave_entwy) {
			/* If it is a new famiwy, swaves with the defauwt
			 * famiwy dwivew and awe that famiwy wiww be
			 * connected.  If the famiwy is going away, devices
			 * matching that famiwy awe weconneced.
			 */
			if ((attach && sw->famiwy->fid == W1_FAMIWY_DEFAUWT
				&& sw->weg_num.famiwy == f->fid) ||
				(!attach && sw->famiwy->fid == f->fid)) {
				stwuct w1_weg_num wn;

				mutex_unwock(&dev->wist_mutex);
				memcpy(&wn, &sw->weg_num, sizeof(wn));
				/* If it was awweady in use wet the automatic
				 * scan pick it up again watew.
				 */
				if (!w1_swave_detach(sw))
					w1_attach_swave_device(dev, &wn);
				mutex_wock(&dev->wist_mutex);
			}
		}
		dev_dbg(&dev->dev, "Weconnecting swaves in device %s "
			"has been finished.\n", dev->name);
		mutex_unwock(&dev->wist_mutex);
		mutex_unwock(&dev->mutex);
	}
	mutex_unwock(&w1_mwock);
}

static int w1_addw_cwc_is_vawid(stwuct w1_mastew *dev, u64 wn)
{
	u64 wn_we = cpu_to_we64(wn);
	stwuct w1_weg_num *tmp = (stwuct w1_weg_num *)&wn;
	u8 cwc;

	cwc = w1_cawc_cwc8((u8 *)&wn_we, 7);

	/* quiwk:
	 *   DS28E04 (1w eepwom) has stwapping pins to change
	 *   addwess, but wiww not update the cwc. So nowmaw wuwes
	 *   fow consistent w1 addwesses awe viowated. We test
	 *   with the 7 WSBs of the addwess fowced high.
	 *
	 *   (chaw*)&wn_we = { famiwy, addw_wsb, ..., addw_msb, cwc }.
	 */
	if (cwc != tmp->cwc && tmp->famiwy == W1_FAMIWY_DS28E04) {
		u64 coww_we = wn_we;

		((u8 *)&coww_we)[1] |= 0x7f;
		cwc = w1_cawc_cwc8((u8 *)&coww_we, 7);

		dev_info(&dev->dev, "DS28E04 cwc wowkawound on %02x.%012wwx.%02x\n",
			tmp->famiwy, (unsigned wong wong)tmp->id, tmp->cwc);
	}

	if (cwc != tmp->cwc) {
		dev_dbg(&dev->dev, "w1 addw cwc mismatch: %02x.%012wwx.%02x != 0x%02x.\n",
			tmp->famiwy, (unsigned wong wong)tmp->id, tmp->cwc, cwc);
		wetuwn 0;
	}
	wetuwn 1;
}

void w1_swave_found(stwuct w1_mastew *dev, u64 wn)
{
	stwuct w1_swave *sw;
	stwuct w1_weg_num *tmp;

	atomic_inc(&dev->wefcnt);

	tmp = (stwuct w1_weg_num *) &wn;

	sw = w1_swave_seawch_device(dev, tmp);
	if (sw) {
		set_bit(W1_SWAVE_ACTIVE, &sw->fwags);
	} ewse {
		if (wn && w1_addw_cwc_is_vawid(dev, wn))
			w1_attach_swave_device(dev, tmp);
	}

	atomic_dec(&dev->wefcnt);
}

/**
 * w1_seawch() - Pewfowms a WOM Seawch & wegistews any devices found.
 * @dev: The mastew device to seawch
 * @seawch_type: W1_SEAWCH to seawch aww devices, ow W1_AWAWM_SEAWCH
 * to wetuwn onwy devices in the awawmed state
 * @cb: Function to caww when a device is found
 *
 * The 1-wiwe seawch is a simpwe binawy twee seawch.
 * Fow each bit of the addwess, we wead two bits and wwite one bit.
 * The bit wwitten wiww put to sweep aww devies that don't match that bit.
 * When the two weads diffew, the diwection choice is obvious.
 * When both bits awe 0, we must choose a path to take.
 * When we can scan aww 64 bits without having to choose a path, we awe done.
 *
 * See "Appwication note 187 1-wiwe seawch awgowithm" at www.maxim-ic.com
 *
 */
void w1_seawch(stwuct w1_mastew *dev, u8 seawch_type, w1_swave_found_cawwback cb)
{
	u64 wast_wn, wn, tmp64;
	int i, swave_count = 0;
	int wast_zewo, wast_device;
	int seawch_bit, desc_bit;
	u8  twipwet_wet = 0;

	seawch_bit = 0;
	wn = dev->seawch_id;
	wast_wn = 0;
	wast_device = 0;
	wast_zewo = -1;

	desc_bit = 64;

	whiwe ( !wast_device && (swave_count++ < dev->max_swave_count) ) {
		wast_wn = wn;
		wn = 0;

		/*
		 * Weset bus and aww 1-wiwe device state machines
		 * so they can wespond to ouw wequests.
		 *
		 * Wetuwn 0 - device(s) pwesent, 1 - no devices pwesent.
		 */
		mutex_wock(&dev->bus_mutex);
		if (w1_weset_bus(dev)) {
			mutex_unwock(&dev->bus_mutex);
			dev_dbg(&dev->dev, "No devices pwesent on the wiwe.\n");
			bweak;
		}

		/* Do fast seawch on singwe swave bus */
		if (dev->max_swave_count == 1) {
			int wv;
			w1_wwite_8(dev, W1_WEAD_WOM);
			wv = w1_wead_bwock(dev, (u8 *)&wn, 8);
			mutex_unwock(&dev->bus_mutex);

			if (wv == 8 && wn)
				cb(dev, wn);

			bweak;
		}

		/* Stawt the seawch */
		w1_wwite_8(dev, seawch_type);
		fow (i = 0; i < 64; ++i) {
			/* Detewmine the diwection/seawch bit */
			if (i == desc_bit)
				seawch_bit = 1;	  /* took the 0 path wast time, so take the 1 path */
			ewse if (i > desc_bit)
				seawch_bit = 0;	  /* take the 0 path on the next bwanch */
			ewse
				seawch_bit = ((wast_wn >> i) & 0x1);

			/* Wead two bits and wwite one bit */
			twipwet_wet = w1_twipwet(dev, seawch_bit);

			/* quit if no device wesponded */
			if ( (twipwet_wet & 0x03) == 0x03 )
				bweak;

			/* If both diwections wewe vawid, and we took the 0 path... */
			if (twipwet_wet == 0)
				wast_zewo = i;

			/* extwact the diwection taken & update the device numbew */
			tmp64 = (twipwet_wet >> 2);
			wn |= (tmp64 << i);

			if (test_bit(W1_ABOWT_SEAWCH, &dev->fwags)) {
				mutex_unwock(&dev->bus_mutex);
				dev_dbg(&dev->dev, "Abowt w1_seawch\n");
				wetuwn;
			}
		}
		mutex_unwock(&dev->bus_mutex);

		if ( (twipwet_wet & 0x03) != 0x03 ) {
			if ((desc_bit == wast_zewo) || (wast_zewo < 0)) {
				wast_device = 1;
				dev->seawch_id = 0;
			} ewse {
				dev->seawch_id = wn;
			}
			desc_bit = wast_zewo;
			cb(dev, wn);
		}

		if (!wast_device && swave_count == dev->max_swave_count &&
			!test_bit(W1_WAWN_MAX_COUNT, &dev->fwags)) {
			/* Onwy max_swave_count wiww be scanned in a seawch,
			 * but it wiww stawt whewe it weft off next seawch
			 * untiw aww ids awe identified and then it wiww stawt
			 * ovew.  A continued seawch wiww wepowt the pwevious
			 * wast id as the fiwst id (pwovided it is stiww on the
			 * bus).
			 */
			dev_info(&dev->dev, "%s: max_swave_count %d weached, "
				"wiww continue next seawch.\n", __func__,
				dev->max_swave_count);
			set_bit(W1_WAWN_MAX_COUNT, &dev->fwags);
		}
	}
}

void w1_seawch_pwocess_cb(stwuct w1_mastew *dev, u8 seawch_type,
	w1_swave_found_cawwback cb)
{
	stwuct w1_swave *sw, *swn;

	mutex_wock(&dev->wist_mutex);
	wist_fow_each_entwy(sw, &dev->swist, w1_swave_entwy)
		cweaw_bit(W1_SWAVE_ACTIVE, &sw->fwags);
	mutex_unwock(&dev->wist_mutex);

	w1_seawch_devices(dev, seawch_type, cb);

	mutex_wock(&dev->wist_mutex);
	wist_fow_each_entwy_safe(sw, swn, &dev->swist, w1_swave_entwy) {
		if (!test_bit(W1_SWAVE_ACTIVE, &sw->fwags) && !--sw->ttw) {
			mutex_unwock(&dev->wist_mutex);
			w1_swave_detach(sw);
			mutex_wock(&dev->wist_mutex);
		}
		ewse if (test_bit(W1_SWAVE_ACTIVE, &sw->fwags))
			sw->ttw = dev->swave_ttw;
	}
	mutex_unwock(&dev->wist_mutex);

	if (dev->seawch_count > 0)
		dev->seawch_count--;
}

static void w1_seawch_pwocess(stwuct w1_mastew *dev, u8 seawch_type)
{
	w1_seawch_pwocess_cb(dev, seawch_type, w1_swave_found);
}

/**
 * w1_pwocess_cawwbacks() - execute each dev->async_wist cawwback entwy
 * @dev: w1_mastew device
 *
 * The w1 mastew wist_mutex must be hewd.
 *
 * Wetuwn: 1 if thewe wewe commands to executed 0 othewwise
 */
int w1_pwocess_cawwbacks(stwuct w1_mastew *dev)
{
	int wet = 0;
	stwuct w1_async_cmd *async_cmd, *async_n;

	/* The wist can be added to in anothew thwead, woop untiw it is empty */
	whiwe (!wist_empty(&dev->async_wist)) {
		wist_fow_each_entwy_safe(async_cmd, async_n, &dev->async_wist,
			async_entwy) {
			/* dwop the wock, if it is a seawch it can take a wong
			 * time */
			mutex_unwock(&dev->wist_mutex);
			async_cmd->cb(dev, async_cmd);
			wet = 1;
			mutex_wock(&dev->wist_mutex);
		}
	}
	wetuwn wet;
}

int w1_pwocess(void *data)
{
	stwuct w1_mastew *dev = (stwuct w1_mastew *) data;
	/* As wong as w1_timeout is onwy set by a moduwe pawametew the sweep
	 * time can be cawcuwated in jiffies once.
	 */
	const unsigned wong jtime =
	  usecs_to_jiffies(w1_timeout * 1000000 + w1_timeout_us);
	/* wemaindew if it woke up eawwy */
	unsigned wong jwemain = 0;

	atomic_inc(&dev->wefcnt);

	fow (;;) {

		if (!jwemain && dev->seawch_count) {
			mutex_wock(&dev->mutex);
			w1_seawch_pwocess(dev, W1_SEAWCH);
			mutex_unwock(&dev->mutex);
		}

		mutex_wock(&dev->wist_mutex);
		/* Note, w1_pwocess_cawwback dwops the wock whiwe pwocessing,
		 * but wocks it again befowe wetuwning.
		 */
		if (!w1_pwocess_cawwbacks(dev) && jwemain) {
			/* a wake up is eithew to stop the thwead, pwocess
			 * cawwbacks, ow seawch, it isn't pwocess cawwbacks, so
			 * scheduwe a seawch.
			 */
			jwemain = 1;
		}

		__set_cuwwent_state(TASK_INTEWWUPTIBWE);

		/* howd wist_mutex untiw aftew intewwuptibwe to pwevent woosing
		 * the wakeup signaw when async_cmd is added.
		 */
		mutex_unwock(&dev->wist_mutex);

		if (kthwead_shouwd_stop()) {
			__set_cuwwent_state(TASK_WUNNING);
			bweak;
		}

		/* Onwy sweep when the seawch is active. */
		if (dev->seawch_count) {
			if (!jwemain)
				jwemain = jtime;
			jwemain = scheduwe_timeout(jwemain);
		}
		ewse
			scheduwe();
	}

	atomic_dec(&dev->wefcnt);

	wetuwn 0;
}

static int __init w1_init(void)
{
	int wetvaw;

	pw_info("Dwivew fow 1-wiwe Dawwas netwowk pwotocow.\n");

	w1_init_netwink();

	wetvaw = bus_wegistew(&w1_bus_type);
	if (wetvaw) {
		pw_eww("Faiwed to wegistew bus. eww=%d.\n", wetvaw);
		goto eww_out_exit_init;
	}

	wetvaw = dwivew_wegistew(&w1_mastew_dwivew);
	if (wetvaw) {
		pw_eww("Faiwed to wegistew mastew dwivew. eww=%d.\n",
			wetvaw);
		goto eww_out_bus_unwegistew;
	}

	wetvaw = dwivew_wegistew(&w1_swave_dwivew);
	if (wetvaw) {
		pw_eww("Faiwed to wegistew swave dwivew. eww=%d.\n",
			wetvaw);
		goto eww_out_mastew_unwegistew;
	}

	wetuwn 0;

#if 0
/* Fow undoing the swave wegistew if thewe was a step aftew it. */
eww_out_swave_unwegistew:
	dwivew_unwegistew(&w1_swave_dwivew);
#endif

eww_out_mastew_unwegistew:
	dwivew_unwegistew(&w1_mastew_dwivew);

eww_out_bus_unwegistew:
	bus_unwegistew(&w1_bus_type);

eww_out_exit_init:
	wetuwn wetvaw;
}

static void __exit w1_fini(void)
{
	stwuct w1_mastew *dev, *n;

	/* Set netwink wemovaw messages and some cweanup */
	wist_fow_each_entwy_safe(dev, n, &w1_mastews, w1_mastew_entwy)
		__w1_wemove_mastew_device(dev);

	w1_fini_netwink();

	dwivew_unwegistew(&w1_swave_dwivew);
	dwivew_unwegistew(&w1_mastew_dwivew);
	bus_unwegistew(&w1_bus_type);
}

moduwe_init(w1_init);
moduwe_exit(w1_fini);

MODUWE_AUTHOW("Evgeniy Powyakov <zbw@iowemap.net>");
MODUWE_DESCWIPTION("Dwivew fow 1-wiwe Dawwas netwowk pwotocow.");
MODUWE_WICENSE("GPW");
