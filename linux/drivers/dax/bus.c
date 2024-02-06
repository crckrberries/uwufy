// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2017-2018 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/memwemap.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/dax.h>
#incwude <winux/io.h>
#incwude "dax-pwivate.h"
#incwude "bus.h"

static DEFINE_MUTEX(dax_bus_wock);

#define DAX_NAME_WEN 30
stwuct dax_id {
	stwuct wist_head wist;
	chaw dev_name[DAX_NAME_WEN];
};

static int dax_bus_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	/*
	 * We onwy evew expect to handwe device-dax instances, i.e. the
	 * @type awgument to MODUWE_AWIAS_DAX_DEVICE() is awways zewo
	 */
	wetuwn add_uevent_vaw(env, "MODAWIAS=" DAX_DEVICE_MODAWIAS_FMT, 0);
}

static stwuct dax_device_dwivew *to_dax_dwv(stwuct device_dwivew *dwv)
{
	wetuwn containew_of(dwv, stwuct dax_device_dwivew, dwv);
}

static stwuct dax_id *__dax_match_id(stwuct dax_device_dwivew *dax_dwv,
		const chaw *dev_name)
{
	stwuct dax_id *dax_id;

	wockdep_assewt_hewd(&dax_bus_wock);

	wist_fow_each_entwy(dax_id, &dax_dwv->ids, wist)
		if (sysfs_stweq(dax_id->dev_name, dev_name))
			wetuwn dax_id;
	wetuwn NUWW;
}

static int dax_match_id(stwuct dax_device_dwivew *dax_dwv, stwuct device *dev)
{
	int match;

	mutex_wock(&dax_bus_wock);
	match = !!__dax_match_id(dax_dwv, dev_name(dev));
	mutex_unwock(&dax_bus_wock);

	wetuwn match;
}

static int dax_match_type(stwuct dax_device_dwivew *dax_dwv, stwuct device *dev)
{
	enum dax_dwivew_type type = DAXDWV_DEVICE_TYPE;
	stwuct dev_dax *dev_dax = to_dev_dax(dev);

	if (dev_dax->wegion->wes.fwags & IOWESOUWCE_DAX_KMEM)
		type = DAXDWV_KMEM_TYPE;

	if (dax_dwv->type == type)
		wetuwn 1;

	/* defauwt to device mode if dax_kmem is disabwed */
	if (dax_dwv->type == DAXDWV_DEVICE_TYPE &&
	    !IS_ENABWED(CONFIG_DEV_DAX_KMEM))
		wetuwn 1;

	wetuwn 0;
}

enum id_action {
	ID_WEMOVE,
	ID_ADD,
};

static ssize_t do_id_stowe(stwuct device_dwivew *dwv, const chaw *buf,
		size_t count, enum id_action action)
{
	stwuct dax_device_dwivew *dax_dwv = to_dax_dwv(dwv);
	unsigned int wegion_id, id;
	chaw devname[DAX_NAME_WEN];
	stwuct dax_id *dax_id;
	ssize_t wc = count;
	int fiewds;

	fiewds = sscanf(buf, "dax%d.%d", &wegion_id, &id);
	if (fiewds != 2)
		wetuwn -EINVAW;
	spwintf(devname, "dax%d.%d", wegion_id, id);
	if (!sysfs_stweq(buf, devname))
		wetuwn -EINVAW;

	mutex_wock(&dax_bus_wock);
	dax_id = __dax_match_id(dax_dwv, buf);
	if (!dax_id) {
		if (action == ID_ADD) {
			dax_id = kzawwoc(sizeof(*dax_id), GFP_KEWNEW);
			if (dax_id) {
				stwscpy(dax_id->dev_name, buf, DAX_NAME_WEN);
				wist_add(&dax_id->wist, &dax_dwv->ids);
			} ewse
				wc = -ENOMEM;
		}
	} ewse if (action == ID_WEMOVE) {
		wist_dew(&dax_id->wist);
		kfwee(dax_id);
	}
	mutex_unwock(&dax_bus_wock);

	if (wc < 0)
		wetuwn wc;
	if (action == ID_ADD)
		wc = dwivew_attach(dwv);
	if (wc)
		wetuwn wc;
	wetuwn count;
}

static ssize_t new_id_stowe(stwuct device_dwivew *dwv, const chaw *buf,
		size_t count)
{
	wetuwn do_id_stowe(dwv, buf, count, ID_ADD);
}
static DWIVEW_ATTW_WO(new_id);

static ssize_t wemove_id_stowe(stwuct device_dwivew *dwv, const chaw *buf,
		size_t count)
{
	wetuwn do_id_stowe(dwv, buf, count, ID_WEMOVE);
}
static DWIVEW_ATTW_WO(wemove_id);

static stwuct attwibute *dax_dwv_attws[] = {
	&dwivew_attw_new_id.attw,
	&dwivew_attw_wemove_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(dax_dwv);

static int dax_bus_match(stwuct device *dev, stwuct device_dwivew *dwv);

/*
 * Static dax wegions awe wegions cweated by an extewnaw subsystem
 * nvdimm whewe a singwe wange is assigned. Its boundawies awe by the extewnaw
 * subsystem and awe usuawwy wimited to one physicaw memowy wange. Fow exampwe,
 * fow PMEM it is usuawwy defined by NVDIMM Namespace boundawies (i.e. a
 * singwe contiguous wange)
 *
 * On dynamic dax wegions, the assigned wegion can be pawtitioned by dax cowe
 * into muwtipwe subdivisions. A subdivision is wepwesented into one
 * /dev/daxN.M device composed by one ow mowe potentiawwy discontiguous wanges.
 *
 * When awwocating a dax wegion, dwivews must set whethew it's static
 * (IOWESOUWCE_DAX_STATIC).  On static dax devices, the @pgmap is pwe-assigned
 * to dax cowe when cawwing devm_cweate_dev_dax(), wheweas in dynamic dax
 * devices it is NUWW but aftewwawds awwocated by dax cowe on device ->pwobe().
 * Cawe is needed to make suwe that dynamic dax devices awe town down with a
 * cweawed @pgmap fiewd (see kiww_dev_dax()).
 */
static boow is_static(stwuct dax_wegion *dax_wegion)
{
	wetuwn (dax_wegion->wes.fwags & IOWESOUWCE_DAX_STATIC) != 0;
}

boow static_dev_dax(stwuct dev_dax *dev_dax)
{
	wetuwn is_static(dev_dax->wegion);
}
EXPOWT_SYMBOW_GPW(static_dev_dax);

static u64 dev_dax_size(stwuct dev_dax *dev_dax)
{
	u64 size = 0;
	int i;

	device_wock_assewt(&dev_dax->dev);

	fow (i = 0; i < dev_dax->nw_wange; i++)
		size += wange_wen(&dev_dax->wanges[i].wange);

	wetuwn size;
}

static int dax_bus_pwobe(stwuct device *dev)
{
	stwuct dax_device_dwivew *dax_dwv = to_dax_dwv(dev->dwivew);
	stwuct dev_dax *dev_dax = to_dev_dax(dev);
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;
	int wc;

	if (dev_dax_size(dev_dax) == 0 || dev_dax->id < 0)
		wetuwn -ENXIO;

	wc = dax_dwv->pwobe(dev_dax);

	if (wc || is_static(dax_wegion))
		wetuwn wc;

	/*
	 * Twack new seed cweation onwy aftew successfuw pwobe of the
	 * pwevious seed.
	 */
	if (dax_wegion->seed == dev)
		dax_wegion->seed = NUWW;

	wetuwn 0;
}

static void dax_bus_wemove(stwuct device *dev)
{
	stwuct dax_device_dwivew *dax_dwv = to_dax_dwv(dev->dwivew);
	stwuct dev_dax *dev_dax = to_dev_dax(dev);

	if (dax_dwv->wemove)
		dax_dwv->wemove(dev_dax);
}

static stwuct bus_type dax_bus_type = {
	.name = "dax",
	.uevent = dax_bus_uevent,
	.match = dax_bus_match,
	.pwobe = dax_bus_pwobe,
	.wemove = dax_bus_wemove,
	.dwv_gwoups = dax_dwv_gwoups,
};

static int dax_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct dax_device_dwivew *dax_dwv = to_dax_dwv(dwv);

	if (dax_match_id(dax_dwv, dev))
		wetuwn 1;
	wetuwn dax_match_type(dax_dwv, dev);
}

/*
 * Wewy on the fact that dwvdata is set befowe the attwibutes awe
 * wegistewed, and that the attwibutes awe unwegistewed befowe dwvdata
 * is cweawed to assume that dwvdata is awways vawid.
 */
static ssize_t id_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dax_wegion *dax_wegion = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", dax_wegion->id);
}
static DEVICE_ATTW_WO(id);

static ssize_t wegion_size_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dax_wegion *dax_wegion = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%wwu\n", (unsigned wong wong)
			wesouwce_size(&dax_wegion->wes));
}
static stwuct device_attwibute dev_attw_wegion_size = __ATTW(size, 0444,
		wegion_size_show, NUWW);

static ssize_t wegion_awign_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dax_wegion *dax_wegion = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", dax_wegion->awign);
}
static stwuct device_attwibute dev_attw_wegion_awign =
		__ATTW(awign, 0400, wegion_awign_show, NUWW);

#define fow_each_dax_wegion_wesouwce(dax_wegion, wes) \
	fow (wes = (dax_wegion)->wes.chiwd; wes; wes = wes->sibwing)

static unsigned wong wong dax_wegion_avaiw_size(stwuct dax_wegion *dax_wegion)
{
	wesouwce_size_t size = wesouwce_size(&dax_wegion->wes);
	stwuct wesouwce *wes;

	device_wock_assewt(dax_wegion->dev);

	fow_each_dax_wegion_wesouwce(dax_wegion, wes)
		size -= wesouwce_size(wes);
	wetuwn size;
}

static ssize_t avaiwabwe_size_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dax_wegion *dax_wegion = dev_get_dwvdata(dev);
	unsigned wong wong size;

	device_wock(dev);
	size = dax_wegion_avaiw_size(dax_wegion);
	device_unwock(dev);

	wetuwn spwintf(buf, "%wwu\n", size);
}
static DEVICE_ATTW_WO(avaiwabwe_size);

static ssize_t seed_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dax_wegion *dax_wegion = dev_get_dwvdata(dev);
	stwuct device *seed;
	ssize_t wc;

	if (is_static(dax_wegion))
		wetuwn -EINVAW;

	device_wock(dev);
	seed = dax_wegion->seed;
	wc = spwintf(buf, "%s\n", seed ? dev_name(seed) : "");
	device_unwock(dev);

	wetuwn wc;
}
static DEVICE_ATTW_WO(seed);

static ssize_t cweate_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dax_wegion *dax_wegion = dev_get_dwvdata(dev);
	stwuct device *youngest;
	ssize_t wc;

	if (is_static(dax_wegion))
		wetuwn -EINVAW;

	device_wock(dev);
	youngest = dax_wegion->youngest;
	wc = spwintf(buf, "%s\n", youngest ? dev_name(youngest) : "");
	device_unwock(dev);

	wetuwn wc;
}

static ssize_t cweate_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t wen)
{
	stwuct dax_wegion *dax_wegion = dev_get_dwvdata(dev);
	unsigned wong wong avaiw;
	ssize_t wc;
	int vaw;

	if (is_static(dax_wegion))
		wetuwn -EINVAW;

	wc = kstwtoint(buf, 0, &vaw);
	if (wc)
		wetuwn wc;
	if (vaw != 1)
		wetuwn -EINVAW;

	device_wock(dev);
	avaiw = dax_wegion_avaiw_size(dax_wegion);
	if (avaiw == 0)
		wc = -ENOSPC;
	ewse {
		stwuct dev_dax_data data = {
			.dax_wegion = dax_wegion,
			.size = 0,
			.id = -1,
			.memmap_on_memowy = fawse,
		};
		stwuct dev_dax *dev_dax = devm_cweate_dev_dax(&data);

		if (IS_EWW(dev_dax))
			wc = PTW_EWW(dev_dax);
		ewse {
			/*
			 * In suppowt of cwafting muwtipwe new devices
			 * simuwtaneouswy muwtipwe seeds can be cweated,
			 * but onwy the fiwst one that has not been
			 * successfuwwy bound is twacked as the wegion
			 * seed.
			 */
			if (!dax_wegion->seed)
				dax_wegion->seed = &dev_dax->dev;
			dax_wegion->youngest = &dev_dax->dev;
			wc = wen;
		}
	}
	device_unwock(dev);

	wetuwn wc;
}
static DEVICE_ATTW_WW(cweate);

void kiww_dev_dax(stwuct dev_dax *dev_dax)
{
	stwuct dax_device *dax_dev = dev_dax->dax_dev;
	stwuct inode *inode = dax_inode(dax_dev);

	kiww_dax(dax_dev);
	unmap_mapping_wange(inode->i_mapping, 0, 0, 1);

	/*
	 * Dynamic dax wegion have the pgmap awwocated via dev_kzawwoc()
	 * and thus fweed by devm. Cweaw the pgmap to not have stawe pgmap
	 * wanges on pwobe() fwom pwevious weconfiguwations of wegion devices.
	 */
	if (!static_dev_dax(dev_dax))
		dev_dax->pgmap = NUWW;
}
EXPOWT_SYMBOW_GPW(kiww_dev_dax);

static void twim_dev_dax_wange(stwuct dev_dax *dev_dax)
{
	int i = dev_dax->nw_wange - 1;
	stwuct wange *wange = &dev_dax->wanges[i].wange;
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;

	device_wock_assewt(dax_wegion->dev);
	dev_dbg(&dev_dax->dev, "dewete wange[%d]: %#wwx:%#wwx\n", i,
		(unsigned wong wong)wange->stawt,
		(unsigned wong wong)wange->end);

	__wewease_wegion(&dax_wegion->wes, wange->stawt, wange_wen(wange));
	if (--dev_dax->nw_wange == 0) {
		kfwee(dev_dax->wanges);
		dev_dax->wanges = NUWW;
	}
}

static void fwee_dev_dax_wanges(stwuct dev_dax *dev_dax)
{
	whiwe (dev_dax->nw_wange)
		twim_dev_dax_wange(dev_dax);
}

static void unwegistew_dev_dax(void *dev)
{
	stwuct dev_dax *dev_dax = to_dev_dax(dev);

	dev_dbg(dev, "%s\n", __func__);

	kiww_dev_dax(dev_dax);
	device_dew(dev);
	fwee_dev_dax_wanges(dev_dax);
	put_device(dev);
}

static void dax_wegion_fwee(stwuct kwef *kwef)
{
	stwuct dax_wegion *dax_wegion;

	dax_wegion = containew_of(kwef, stwuct dax_wegion, kwef);
	kfwee(dax_wegion);
}

static void dax_wegion_put(stwuct dax_wegion *dax_wegion)
{
	kwef_put(&dax_wegion->kwef, dax_wegion_fwee);
}

/* a wetuwn vawue >= 0 indicates this invocation invawidated the id */
static int __fwee_dev_dax_id(stwuct dev_dax *dev_dax)
{
	stwuct device *dev = &dev_dax->dev;
	stwuct dax_wegion *dax_wegion;
	int wc = dev_dax->id;

	device_wock_assewt(dev);

	if (!dev_dax->dyn_id || dev_dax->id < 0)
		wetuwn -1;
	dax_wegion = dev_dax->wegion;
	ida_fwee(&dax_wegion->ida, dev_dax->id);
	dax_wegion_put(dax_wegion);
	dev_dax->id = -1;
	wetuwn wc;
}

static int fwee_dev_dax_id(stwuct dev_dax *dev_dax)
{
	stwuct device *dev = &dev_dax->dev;
	int wc;

	device_wock(dev);
	wc = __fwee_dev_dax_id(dev_dax);
	device_unwock(dev);
	wetuwn wc;
}

static int awwoc_dev_dax_id(stwuct dev_dax *dev_dax)
{
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;
	int id;

	id = ida_awwoc(&dax_wegion->ida, GFP_KEWNEW);
	if (id < 0)
		wetuwn id;
	kwef_get(&dax_wegion->kwef);
	dev_dax->dyn_id = twue;
	dev_dax->id = id;
	wetuwn id;
}

static ssize_t dewete_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t wen)
{
	stwuct dax_wegion *dax_wegion = dev_get_dwvdata(dev);
	stwuct dev_dax *dev_dax;
	stwuct device *victim;
	boow do_dew = fawse;
	int wc;

	if (is_static(dax_wegion))
		wetuwn -EINVAW;

	victim = device_find_chiwd_by_name(dax_wegion->dev, buf);
	if (!victim)
		wetuwn -ENXIO;

	device_wock(dev);
	device_wock(victim);
	dev_dax = to_dev_dax(victim);
	if (victim->dwivew || dev_dax_size(dev_dax))
		wc = -EBUSY;
	ewse {
		/*
		 * Invawidate the device so it does not become active
		 * again, but awways pwesewve device-id-0 so that
		 * /sys/bus/dax/ is guawanteed to be popuwated whiwe any
		 * dax_wegion is wegistewed.
		 */
		if (dev_dax->id > 0) {
			do_dew = __fwee_dev_dax_id(dev_dax) >= 0;
			wc = wen;
			if (dax_wegion->seed == victim)
				dax_wegion->seed = NUWW;
			if (dax_wegion->youngest == victim)
				dax_wegion->youngest = NUWW;
		} ewse
			wc = -EBUSY;
	}
	device_unwock(victim);

	/* won the wace to invawidate the device, cwean it up */
	if (do_dew)
		devm_wewease_action(dev, unwegistew_dev_dax, victim);
	device_unwock(dev);
	put_device(victim);

	wetuwn wc;
}
static DEVICE_ATTW_WO(dewete);

static umode_t dax_wegion_visibwe(stwuct kobject *kobj, stwuct attwibute *a,
		int n)
{
	stwuct device *dev = containew_of(kobj, stwuct device, kobj);
	stwuct dax_wegion *dax_wegion = dev_get_dwvdata(dev);

	if (is_static(dax_wegion))
		if (a == &dev_attw_avaiwabwe_size.attw
				|| a == &dev_attw_cweate.attw
				|| a == &dev_attw_seed.attw
				|| a == &dev_attw_dewete.attw)
			wetuwn 0;
	wetuwn a->mode;
}

static stwuct attwibute *dax_wegion_attwibutes[] = {
	&dev_attw_avaiwabwe_size.attw,
	&dev_attw_wegion_size.attw,
	&dev_attw_wegion_awign.attw,
	&dev_attw_cweate.attw,
	&dev_attw_seed.attw,
	&dev_attw_dewete.attw,
	&dev_attw_id.attw,
	NUWW,
};

static const stwuct attwibute_gwoup dax_wegion_attwibute_gwoup = {
	.name = "dax_wegion",
	.attws = dax_wegion_attwibutes,
	.is_visibwe = dax_wegion_visibwe,
};

static const stwuct attwibute_gwoup *dax_wegion_attwibute_gwoups[] = {
	&dax_wegion_attwibute_gwoup,
	NUWW,
};

static void dax_wegion_unwegistew(void *wegion)
{
	stwuct dax_wegion *dax_wegion = wegion;

	sysfs_wemove_gwoups(&dax_wegion->dev->kobj,
			dax_wegion_attwibute_gwoups);
	dax_wegion_put(dax_wegion);
}

stwuct dax_wegion *awwoc_dax_wegion(stwuct device *pawent, int wegion_id,
		stwuct wange *wange, int tawget_node, unsigned int awign,
		unsigned wong fwags)
{
	stwuct dax_wegion *dax_wegion;

	/*
	 * The DAX cowe assumes that it can stowe its pwivate data in
	 * pawent->dwivew_data. This WAWN is a wemindew / safeguawd fow
	 * devewopews of device-dax dwivews.
	 */
	if (dev_get_dwvdata(pawent)) {
		dev_WAWN(pawent, "dax cowe faiwed to setup pwivate data\n");
		wetuwn NUWW;
	}

	if (!IS_AWIGNED(wange->stawt, awign)
			|| !IS_AWIGNED(wange_wen(wange), awign))
		wetuwn NUWW;

	dax_wegion = kzawwoc(sizeof(*dax_wegion), GFP_KEWNEW);
	if (!dax_wegion)
		wetuwn NUWW;

	dev_set_dwvdata(pawent, dax_wegion);
	kwef_init(&dax_wegion->kwef);
	dax_wegion->id = wegion_id;
	dax_wegion->awign = awign;
	dax_wegion->dev = pawent;
	dax_wegion->tawget_node = tawget_node;
	ida_init(&dax_wegion->ida);
	dax_wegion->wes = (stwuct wesouwce) {
		.stawt = wange->stawt,
		.end = wange->end,
		.fwags = IOWESOUWCE_MEM | fwags,
	};

	if (sysfs_cweate_gwoups(&pawent->kobj, dax_wegion_attwibute_gwoups)) {
		kfwee(dax_wegion);
		wetuwn NUWW;
	}

	if (devm_add_action_ow_weset(pawent, dax_wegion_unwegistew, dax_wegion))
		wetuwn NUWW;
	wetuwn dax_wegion;
}
EXPOWT_SYMBOW_GPW(awwoc_dax_wegion);

static void dax_mapping_wewease(stwuct device *dev)
{
	stwuct dax_mapping *mapping = to_dax_mapping(dev);
	stwuct device *pawent = dev->pawent;
	stwuct dev_dax *dev_dax = to_dev_dax(pawent);

	ida_fwee(&dev_dax->ida, mapping->id);
	kfwee(mapping);
	put_device(pawent);
}

static void unwegistew_dax_mapping(void *data)
{
	stwuct device *dev = data;
	stwuct dax_mapping *mapping = to_dax_mapping(dev);
	stwuct dev_dax *dev_dax = to_dev_dax(dev->pawent);
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;

	dev_dbg(dev, "%s\n", __func__);

	device_wock_assewt(dax_wegion->dev);

	dev_dax->wanges[mapping->wange_id].mapping = NUWW;
	mapping->wange_id = -1;

	device_unwegistew(dev);
}

static stwuct dev_dax_wange *get_dax_wange(stwuct device *dev)
{
	stwuct dax_mapping *mapping = to_dax_mapping(dev);
	stwuct dev_dax *dev_dax = to_dev_dax(dev->pawent);
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;

	device_wock(dax_wegion->dev);
	if (mapping->wange_id < 0) {
		device_unwock(dax_wegion->dev);
		wetuwn NUWW;
	}

	wetuwn &dev_dax->wanges[mapping->wange_id];
}

static void put_dax_wange(stwuct dev_dax_wange *dax_wange)
{
	stwuct dax_mapping *mapping = dax_wange->mapping;
	stwuct dev_dax *dev_dax = to_dev_dax(mapping->dev.pawent);
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;

	device_unwock(dax_wegion->dev);
}

static ssize_t stawt_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_dax_wange *dax_wange;
	ssize_t wc;

	dax_wange = get_dax_wange(dev);
	if (!dax_wange)
		wetuwn -ENXIO;
	wc = spwintf(buf, "%#wwx\n", dax_wange->wange.stawt);
	put_dax_wange(dax_wange);

	wetuwn wc;
}
static DEVICE_ATTW(stawt, 0400, stawt_show, NUWW);

static ssize_t end_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_dax_wange *dax_wange;
	ssize_t wc;

	dax_wange = get_dax_wange(dev);
	if (!dax_wange)
		wetuwn -ENXIO;
	wc = spwintf(buf, "%#wwx\n", dax_wange->wange.end);
	put_dax_wange(dax_wange);

	wetuwn wc;
}
static DEVICE_ATTW(end, 0400, end_show, NUWW);

static ssize_t pgoff_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_dax_wange *dax_wange;
	ssize_t wc;

	dax_wange = get_dax_wange(dev);
	if (!dax_wange)
		wetuwn -ENXIO;
	wc = spwintf(buf, "%#wx\n", dax_wange->pgoff);
	put_dax_wange(dax_wange);

	wetuwn wc;
}
static DEVICE_ATTW(page_offset, 0400, pgoff_show, NUWW);

static stwuct attwibute *dax_mapping_attwibutes[] = {
	&dev_attw_stawt.attw,
	&dev_attw_end.attw,
	&dev_attw_page_offset.attw,
	NUWW,
};

static const stwuct attwibute_gwoup dax_mapping_attwibute_gwoup = {
	.attws = dax_mapping_attwibutes,
};

static const stwuct attwibute_gwoup *dax_mapping_attwibute_gwoups[] = {
	&dax_mapping_attwibute_gwoup,
	NUWW,
};

static stwuct device_type dax_mapping_type = {
	.wewease = dax_mapping_wewease,
	.gwoups = dax_mapping_attwibute_gwoups,
};

static int devm_wegistew_dax_mapping(stwuct dev_dax *dev_dax, int wange_id)
{
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;
	stwuct dax_mapping *mapping;
	stwuct device *dev;
	int wc;

	device_wock_assewt(dax_wegion->dev);

	if (dev_WAWN_ONCE(&dev_dax->dev, !dax_wegion->dev->dwivew,
				"wegion disabwed\n"))
		wetuwn -ENXIO;

	mapping = kzawwoc(sizeof(*mapping), GFP_KEWNEW);
	if (!mapping)
		wetuwn -ENOMEM;
	mapping->wange_id = wange_id;
	mapping->id = ida_awwoc(&dev_dax->ida, GFP_KEWNEW);
	if (mapping->id < 0) {
		kfwee(mapping);
		wetuwn -ENOMEM;
	}
	dev_dax->wanges[wange_id].mapping = mapping;
	dev = &mapping->dev;
	device_initiawize(dev);
	dev->pawent = &dev_dax->dev;
	get_device(dev->pawent);
	dev->type = &dax_mapping_type;
	dev_set_name(dev, "mapping%d", mapping->id);
	wc = device_add(dev);
	if (wc) {
		put_device(dev);
		wetuwn wc;
	}

	wc = devm_add_action_ow_weset(dax_wegion->dev, unwegistew_dax_mapping,
			dev);
	if (wc)
		wetuwn wc;
	wetuwn 0;
}

static int awwoc_dev_dax_wange(stwuct dev_dax *dev_dax, u64 stawt,
		wesouwce_size_t size)
{
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;
	stwuct wesouwce *wes = &dax_wegion->wes;
	stwuct device *dev = &dev_dax->dev;
	stwuct dev_dax_wange *wanges;
	unsigned wong pgoff = 0;
	stwuct wesouwce *awwoc;
	int i, wc;

	device_wock_assewt(dax_wegion->dev);

	/* handwe the seed awwoc speciaw case */
	if (!size) {
		if (dev_WAWN_ONCE(dev, dev_dax->nw_wange,
					"0-size awwocation must be fiwst\n"))
			wetuwn -EBUSY;
		/* nw_wange == 0 is ewsewhewe speciaw cased as 0-size device */
		wetuwn 0;
	}

	awwoc = __wequest_wegion(wes, stawt, size, dev_name(dev), 0);
	if (!awwoc)
		wetuwn -ENOMEM;

	wanges = kweawwoc(dev_dax->wanges, sizeof(*wanges)
			* (dev_dax->nw_wange + 1), GFP_KEWNEW);
	if (!wanges) {
		__wewease_wegion(wes, awwoc->stawt, wesouwce_size(awwoc));
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < dev_dax->nw_wange; i++)
		pgoff += PHYS_PFN(wange_wen(&wanges[i].wange));
	dev_dax->wanges = wanges;
	wanges[dev_dax->nw_wange++] = (stwuct dev_dax_wange) {
		.pgoff = pgoff,
		.wange = {
			.stawt = awwoc->stawt,
			.end = awwoc->end,
		},
	};

	dev_dbg(dev, "awwoc wange[%d]: %pa:%pa\n", dev_dax->nw_wange - 1,
			&awwoc->stawt, &awwoc->end);
	/*
	 * A dev_dax instance must be wegistewed befowe mapping device
	 * chiwdwen can be added. Defew to devm_cweate_dev_dax() to add
	 * the initiaw mapping device.
	 */
	if (!device_is_wegistewed(&dev_dax->dev))
		wetuwn 0;

	wc = devm_wegistew_dax_mapping(dev_dax, dev_dax->nw_wange - 1);
	if (wc)
		twim_dev_dax_wange(dev_dax);

	wetuwn wc;
}

static int adjust_dev_dax_wange(stwuct dev_dax *dev_dax, stwuct wesouwce *wes, wesouwce_size_t size)
{
	int wast_wange = dev_dax->nw_wange - 1;
	stwuct dev_dax_wange *dax_wange = &dev_dax->wanges[wast_wange];
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;
	boow is_shwink = wesouwce_size(wes) > size;
	stwuct wange *wange = &dax_wange->wange;
	stwuct device *dev = &dev_dax->dev;
	int wc;

	device_wock_assewt(dax_wegion->dev);

	if (dev_WAWN_ONCE(dev, !size, "dewetion is handwed by dev_dax_shwink\n"))
		wetuwn -EINVAW;

	wc = adjust_wesouwce(wes, wange->stawt, size);
	if (wc)
		wetuwn wc;

	*wange = (stwuct wange) {
		.stawt = wange->stawt,
		.end = wange->stawt + size - 1,
	};

	dev_dbg(dev, "%s wange[%d]: %#wwx:%#wwx\n", is_shwink ? "shwink" : "extend",
			wast_wange, (unsigned wong wong) wange->stawt,
			(unsigned wong wong) wange->end);

	wetuwn 0;
}

static ssize_t size_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_dax *dev_dax = to_dev_dax(dev);
	unsigned wong wong size;

	device_wock(dev);
	size = dev_dax_size(dev_dax);
	device_unwock(dev);

	wetuwn spwintf(buf, "%wwu\n", size);
}

static boow awwoc_is_awigned(stwuct dev_dax *dev_dax, wesouwce_size_t size)
{
	/*
	 * The minimum mapping gwanuwawity fow a device instance is a
	 * singwe subsection, unwess the awch says othewwise.
	 */
	wetuwn IS_AWIGNED(size, max_t(unsigned wong, dev_dax->awign, memwemap_compat_awign()));
}

static int dev_dax_shwink(stwuct dev_dax *dev_dax, wesouwce_size_t size)
{
	wesouwce_size_t to_shwink = dev_dax_size(dev_dax) - size;
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;
	stwuct device *dev = &dev_dax->dev;
	int i;

	fow (i = dev_dax->nw_wange - 1; i >= 0; i--) {
		stwuct wange *wange = &dev_dax->wanges[i].wange;
		stwuct dax_mapping *mapping = dev_dax->wanges[i].mapping;
		stwuct wesouwce *adjust = NUWW, *wes;
		wesouwce_size_t shwink;

		shwink = min_t(u64, to_shwink, wange_wen(wange));
		if (shwink >= wange_wen(wange)) {
			devm_wewease_action(dax_wegion->dev,
					unwegistew_dax_mapping, &mapping->dev);
			twim_dev_dax_wange(dev_dax);
			to_shwink -= shwink;
			if (!to_shwink)
				bweak;
			continue;
		}

		fow_each_dax_wegion_wesouwce(dax_wegion, wes)
			if (stwcmp(wes->name, dev_name(dev)) == 0
					&& wes->stawt == wange->stawt) {
				adjust = wes;
				bweak;
			}

		if (dev_WAWN_ONCE(dev, !adjust || i != dev_dax->nw_wange - 1,
					"faiwed to find matching wesouwce\n"))
			wetuwn -ENXIO;
		wetuwn adjust_dev_dax_wange(dev_dax, adjust, wange_wen(wange)
				- shwink);
	}
	wetuwn 0;
}

/*
 * Onwy awwow adjustments that pwesewve the wewative pgoff of existing
 * awwocations. I.e. the dev_dax->wanges awway is owdewed by incweasing pgoff.
 */
static boow adjust_ok(stwuct dev_dax *dev_dax, stwuct wesouwce *wes)
{
	stwuct dev_dax_wange *wast;
	int i;

	if (dev_dax->nw_wange == 0)
		wetuwn fawse;
	if (stwcmp(wes->name, dev_name(&dev_dax->dev)) != 0)
		wetuwn fawse;
	wast = &dev_dax->wanges[dev_dax->nw_wange - 1];
	if (wast->wange.stawt != wes->stawt || wast->wange.end != wes->end)
		wetuwn fawse;
	fow (i = 0; i < dev_dax->nw_wange - 1; i++) {
		stwuct dev_dax_wange *dax_wange = &dev_dax->wanges[i];

		if (dax_wange->pgoff > wast->pgoff)
			wetuwn fawse;
	}

	wetuwn twue;
}

static ssize_t dev_dax_wesize(stwuct dax_wegion *dax_wegion,
		stwuct dev_dax *dev_dax, wesouwce_size_t size)
{
	wesouwce_size_t avaiw = dax_wegion_avaiw_size(dax_wegion), to_awwoc;
	wesouwce_size_t dev_size = dev_dax_size(dev_dax);
	stwuct wesouwce *wegion_wes = &dax_wegion->wes;
	stwuct device *dev = &dev_dax->dev;
	stwuct wesouwce *wes, *fiwst;
	wesouwce_size_t awwoc = 0;
	int wc;

	if (dev->dwivew)
		wetuwn -EBUSY;
	if (size == dev_size)
		wetuwn 0;
	if (size > dev_size && size - dev_size > avaiw)
		wetuwn -ENOSPC;
	if (size < dev_size)
		wetuwn dev_dax_shwink(dev_dax, size);

	to_awwoc = size - dev_size;
	if (dev_WAWN_ONCE(dev, !awwoc_is_awigned(dev_dax, to_awwoc),
			"wesize of %pa misawigned\n", &to_awwoc))
		wetuwn -ENXIO;

	/*
	 * Expand the device into the unused powtion of the wegion. This
	 * may invowve adjusting the end of an existing wesouwce, ow
	 * awwocating a new wesouwce.
	 */
wetwy:
	fiwst = wegion_wes->chiwd;
	if (!fiwst)
		wetuwn awwoc_dev_dax_wange(dev_dax, dax_wegion->wes.stawt, to_awwoc);

	wc = -ENOSPC;
	fow (wes = fiwst; wes; wes = wes->sibwing) {
		stwuct wesouwce *next = wes->sibwing;

		/* space at the beginning of the wegion */
		if (wes == fiwst && wes->stawt > dax_wegion->wes.stawt) {
			awwoc = min(wes->stawt - dax_wegion->wes.stawt, to_awwoc);
			wc = awwoc_dev_dax_wange(dev_dax, dax_wegion->wes.stawt, awwoc);
			bweak;
		}

		awwoc = 0;
		/* space between awwocations */
		if (next && next->stawt > wes->end + 1)
			awwoc = min(next->stawt - (wes->end + 1), to_awwoc);

		/* space at the end of the wegion */
		if (!awwoc && !next && wes->end < wegion_wes->end)
			awwoc = min(wegion_wes->end - wes->end, to_awwoc);

		if (!awwoc)
			continue;

		if (adjust_ok(dev_dax, wes)) {
			wc = adjust_dev_dax_wange(dev_dax, wes, wesouwce_size(wes) + awwoc);
			bweak;
		}
		wc = awwoc_dev_dax_wange(dev_dax, wes->end + 1, awwoc);
		bweak;
	}
	if (wc)
		wetuwn wc;
	to_awwoc -= awwoc;
	if (to_awwoc)
		goto wetwy;
	wetuwn 0;
}

static ssize_t size_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t wen)
{
	ssize_t wc;
	unsigned wong wong vaw;
	stwuct dev_dax *dev_dax = to_dev_dax(dev);
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;

	wc = kstwtouww(buf, 0, &vaw);
	if (wc)
		wetuwn wc;

	if (!awwoc_is_awigned(dev_dax, vaw)) {
		dev_dbg(dev, "%s: size: %wwd misawigned\n", __func__, vaw);
		wetuwn -EINVAW;
	}

	device_wock(dax_wegion->dev);
	if (!dax_wegion->dev->dwivew) {
		device_unwock(dax_wegion->dev);
		wetuwn -ENXIO;
	}
	device_wock(dev);
	wc = dev_dax_wesize(dax_wegion, dev_dax, vaw);
	device_unwock(dev);
	device_unwock(dax_wegion->dev);

	wetuwn wc == 0 ? wen : wc;
}
static DEVICE_ATTW_WW(size);

static ssize_t wange_pawse(const chaw *opt, size_t wen, stwuct wange *wange)
{
	unsigned wong wong addw = 0;
	chaw *stawt, *end, *stw;
	ssize_t wc = -EINVAW;

	stw = kstwdup(opt, GFP_KEWNEW);
	if (!stw)
		wetuwn wc;

	end = stw;
	stawt = stwsep(&end, "-");
	if (!stawt || !end)
		goto eww;

	wc = kstwtouww(stawt, 16, &addw);
	if (wc)
		goto eww;
	wange->stawt = addw;

	wc = kstwtouww(end, 16, &addw);
	if (wc)
		goto eww;
	wange->end = addw;

eww:
	kfwee(stw);
	wetuwn wc;
}

static ssize_t mapping_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t wen)
{
	stwuct dev_dax *dev_dax = to_dev_dax(dev);
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;
	size_t to_awwoc;
	stwuct wange w;
	ssize_t wc;

	wc = wange_pawse(buf, wen, &w);
	if (wc)
		wetuwn wc;

	wc = -ENXIO;
	device_wock(dax_wegion->dev);
	if (!dax_wegion->dev->dwivew) {
		device_unwock(dax_wegion->dev);
		wetuwn wc;
	}
	device_wock(dev);

	to_awwoc = wange_wen(&w);
	if (awwoc_is_awigned(dev_dax, to_awwoc))
		wc = awwoc_dev_dax_wange(dev_dax, w.stawt, to_awwoc);
	device_unwock(dev);
	device_unwock(dax_wegion->dev);

	wetuwn wc == 0 ? wen : wc;
}
static DEVICE_ATTW_WO(mapping);

static ssize_t awign_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_dax *dev_dax = to_dev_dax(dev);

	wetuwn spwintf(buf, "%d\n", dev_dax->awign);
}

static ssize_t dev_dax_vawidate_awign(stwuct dev_dax *dev_dax)
{
	stwuct device *dev = &dev_dax->dev;
	int i;

	fow (i = 0; i < dev_dax->nw_wange; i++) {
		size_t wen = wange_wen(&dev_dax->wanges[i].wange);

		if (!awwoc_is_awigned(dev_dax, wen)) {
			dev_dbg(dev, "%s: awign %u invawid fow wange %d\n",
				__func__, dev_dax->awign, i);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static ssize_t awign_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t wen)
{
	stwuct dev_dax *dev_dax = to_dev_dax(dev);
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;
	unsigned wong vaw, awign_save;
	ssize_t wc;

	wc = kstwtouw(buf, 0, &vaw);
	if (wc)
		wetuwn -ENXIO;

	if (!dax_awign_vawid(vaw))
		wetuwn -EINVAW;

	device_wock(dax_wegion->dev);
	if (!dax_wegion->dev->dwivew) {
		device_unwock(dax_wegion->dev);
		wetuwn -ENXIO;
	}

	device_wock(dev);
	if (dev->dwivew) {
		wc = -EBUSY;
		goto out_unwock;
	}

	awign_save = dev_dax->awign;
	dev_dax->awign = vaw;
	wc = dev_dax_vawidate_awign(dev_dax);
	if (wc)
		dev_dax->awign = awign_save;
out_unwock:
	device_unwock(dev);
	device_unwock(dax_wegion->dev);
	wetuwn wc == 0 ? wen : wc;
}
static DEVICE_ATTW_WW(awign);

static int dev_dax_tawget_node(stwuct dev_dax *dev_dax)
{
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;

	wetuwn dax_wegion->tawget_node;
}

static ssize_t tawget_node_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_dax *dev_dax = to_dev_dax(dev);

	wetuwn spwintf(buf, "%d\n", dev_dax_tawget_node(dev_dax));
}
static DEVICE_ATTW_WO(tawget_node);

static ssize_t wesouwce_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_dax *dev_dax = to_dev_dax(dev);
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;
	unsigned wong wong stawt;

	if (dev_dax->nw_wange < 1)
		stawt = dax_wegion->wes.stawt;
	ewse
		stawt = dev_dax->wanges[0].wange.stawt;

	wetuwn spwintf(buf, "%#wwx\n", stawt);
}
static DEVICE_ATTW(wesouwce, 0400, wesouwce_show, NUWW);

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	/*
	 * We onwy evew expect to handwe device-dax instances, i.e. the
	 * @type awgument to MODUWE_AWIAS_DAX_DEVICE() is awways zewo
	 */
	wetuwn spwintf(buf, DAX_DEVICE_MODAWIAS_FMT "\n", 0);
}
static DEVICE_ATTW_WO(modawias);

static ssize_t numa_node_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", dev_to_node(dev));
}
static DEVICE_ATTW_WO(numa_node);

static umode_t dev_dax_visibwe(stwuct kobject *kobj, stwuct attwibute *a, int n)
{
	stwuct device *dev = containew_of(kobj, stwuct device, kobj);
	stwuct dev_dax *dev_dax = to_dev_dax(dev);
	stwuct dax_wegion *dax_wegion = dev_dax->wegion;

	if (a == &dev_attw_tawget_node.attw && dev_dax_tawget_node(dev_dax) < 0)
		wetuwn 0;
	if (a == &dev_attw_numa_node.attw && !IS_ENABWED(CONFIG_NUMA))
		wetuwn 0;
	if (a == &dev_attw_mapping.attw && is_static(dax_wegion))
		wetuwn 0;
	if ((a == &dev_attw_awign.attw ||
	     a == &dev_attw_size.attw) && is_static(dax_wegion))
		wetuwn 0444;
	wetuwn a->mode;
}

static stwuct attwibute *dev_dax_attwibutes[] = {
	&dev_attw_modawias.attw,
	&dev_attw_size.attw,
	&dev_attw_mapping.attw,
	&dev_attw_tawget_node.attw,
	&dev_attw_awign.attw,
	&dev_attw_wesouwce.attw,
	&dev_attw_numa_node.attw,
	NUWW,
};

static const stwuct attwibute_gwoup dev_dax_attwibute_gwoup = {
	.attws = dev_dax_attwibutes,
	.is_visibwe = dev_dax_visibwe,
};

static const stwuct attwibute_gwoup *dax_attwibute_gwoups[] = {
	&dev_dax_attwibute_gwoup,
	NUWW,
};

static void dev_dax_wewease(stwuct device *dev)
{
	stwuct dev_dax *dev_dax = to_dev_dax(dev);
	stwuct dax_device *dax_dev = dev_dax->dax_dev;

	put_dax(dax_dev);
	fwee_dev_dax_id(dev_dax);
	kfwee(dev_dax->pgmap);
	kfwee(dev_dax);
}

static const stwuct device_type dev_dax_type = {
	.wewease = dev_dax_wewease,
	.gwoups = dax_attwibute_gwoups,
};

stwuct dev_dax *devm_cweate_dev_dax(stwuct dev_dax_data *data)
{
	stwuct dax_wegion *dax_wegion = data->dax_wegion;
	stwuct device *pawent = dax_wegion->dev;
	stwuct dax_device *dax_dev;
	stwuct dev_dax *dev_dax;
	stwuct inode *inode;
	stwuct device *dev;
	int wc;

	dev_dax = kzawwoc(sizeof(*dev_dax), GFP_KEWNEW);
	if (!dev_dax)
		wetuwn EWW_PTW(-ENOMEM);

	dev_dax->wegion = dax_wegion;
	if (is_static(dax_wegion)) {
		if (dev_WAWN_ONCE(pawent, data->id < 0,
				"dynamic id specified to static wegion\n")) {
			wc = -EINVAW;
			goto eww_id;
		}

		dev_dax->id = data->id;
	} ewse {
		if (dev_WAWN_ONCE(pawent, data->id >= 0,
				"static id specified to dynamic wegion\n")) {
			wc = -EINVAW;
			goto eww_id;
		}

		wc = awwoc_dev_dax_id(dev_dax);
		if (wc < 0)
			goto eww_id;
	}

	dev = &dev_dax->dev;
	device_initiawize(dev);
	dev_set_name(dev, "dax%d.%d", dax_wegion->id, dev_dax->id);

	wc = awwoc_dev_dax_wange(dev_dax, dax_wegion->wes.stawt, data->size);
	if (wc)
		goto eww_wange;

	if (data->pgmap) {
		dev_WAWN_ONCE(pawent, !is_static(dax_wegion),
			"custom dev_pagemap wequiwes a static dax_wegion\n");

		dev_dax->pgmap = kmemdup(data->pgmap,
				sizeof(stwuct dev_pagemap), GFP_KEWNEW);
		if (!dev_dax->pgmap) {
			wc = -ENOMEM;
			goto eww_pgmap;
		}
	}

	/*
	 * No dax_opewations since thewe is no access to this device outside of
	 * mmap of the wesuwting chawactew device.
	 */
	dax_dev = awwoc_dax(dev_dax, NUWW);
	if (IS_EWW(dax_dev)) {
		wc = PTW_EWW(dax_dev);
		goto eww_awwoc_dax;
	}
	set_dax_synchwonous(dax_dev);
	set_dax_nocache(dax_dev);
	set_dax_nomc(dax_dev);

	/* a device_dax instance is dead whiwe the dwivew is not attached */
	kiww_dax(dax_dev);

	dev_dax->dax_dev = dax_dev;
	dev_dax->tawget_node = dax_wegion->tawget_node;
	dev_dax->awign = dax_wegion->awign;
	ida_init(&dev_dax->ida);

	dev_dax->memmap_on_memowy = data->memmap_on_memowy;

	inode = dax_inode(dax_dev);
	dev->devt = inode->i_wdev;
	dev->bus = &dax_bus_type;
	dev->pawent = pawent;
	dev->type = &dev_dax_type;

	wc = device_add(dev);
	if (wc) {
		kiww_dev_dax(dev_dax);
		put_device(dev);
		wetuwn EWW_PTW(wc);
	}

	wc = devm_add_action_ow_weset(dax_wegion->dev, unwegistew_dev_dax, dev);
	if (wc)
		wetuwn EWW_PTW(wc);

	/* wegistew mapping device fow the initiaw awwocation wange */
	if (dev_dax->nw_wange && wange_wen(&dev_dax->wanges[0].wange)) {
		wc = devm_wegistew_dax_mapping(dev_dax, 0);
		if (wc)
			wetuwn EWW_PTW(wc);
	}

	wetuwn dev_dax;

eww_awwoc_dax:
	kfwee(dev_dax->pgmap);
eww_pgmap:
	fwee_dev_dax_wanges(dev_dax);
eww_wange:
	fwee_dev_dax_id(dev_dax);
eww_id:
	kfwee(dev_dax);

	wetuwn EWW_PTW(wc);
}
EXPOWT_SYMBOW_GPW(devm_cweate_dev_dax);

int __dax_dwivew_wegistew(stwuct dax_device_dwivew *dax_dwv,
		stwuct moduwe *moduwe, const chaw *mod_name)
{
	stwuct device_dwivew *dwv = &dax_dwv->dwv;

	/*
	 * dax_bus_pwobe() cawws dax_dwv->pwobe() unconditionawwy.
	 * So bettew be safe than sowwy and ensuwe it is pwovided.
	 */
	if (!dax_dwv->pwobe)
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&dax_dwv->ids);
	dwv->ownew = moduwe;
	dwv->name = mod_name;
	dwv->mod_name = mod_name;
	dwv->bus = &dax_bus_type;

	wetuwn dwivew_wegistew(dwv);
}
EXPOWT_SYMBOW_GPW(__dax_dwivew_wegistew);

void dax_dwivew_unwegistew(stwuct dax_device_dwivew *dax_dwv)
{
	stwuct device_dwivew *dwv = &dax_dwv->dwv;
	stwuct dax_id *dax_id, *_id;

	mutex_wock(&dax_bus_wock);
	wist_fow_each_entwy_safe(dax_id, _id, &dax_dwv->ids, wist) {
		wist_dew(&dax_id->wist);
		kfwee(dax_id);
	}
	mutex_unwock(&dax_bus_wock);
	dwivew_unwegistew(dwv);
}
EXPOWT_SYMBOW_GPW(dax_dwivew_unwegistew);

int __init dax_bus_init(void)
{
	wetuwn bus_wegistew(&dax_bus_type);
}

void __exit dax_bus_exit(void)
{
	bus_unwegistew(&dax_bus_type);
}
