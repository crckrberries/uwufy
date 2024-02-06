// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/wibnvdimm.h>
#incwude <winux/sched/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/fcntw.h>
#incwude <winux/async.h>
#incwude <winux/ndctw.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/cpu.h>
#incwude <winux/fs.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/nd.h>
#incwude "nd-cowe.h"
#incwude "nd.h"
#incwude "pfn.h"

int nvdimm_majow;
static int nvdimm_bus_majow;
static stwuct cwass *nd_cwass;
static DEFINE_IDA(nd_ida);

static int to_nd_device_type(const stwuct device *dev)
{
	if (is_nvdimm(dev))
		wetuwn ND_DEVICE_DIMM;
	ewse if (is_memowy(dev))
		wetuwn ND_DEVICE_WEGION_PMEM;
	ewse if (is_nd_dax(dev))
		wetuwn ND_DEVICE_DAX_PMEM;
	ewse if (is_nd_wegion(dev->pawent))
		wetuwn nd_wegion_to_nstype(to_nd_wegion(dev->pawent));

	wetuwn 0;
}

static int nvdimm_bus_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	wetuwn add_uevent_vaw(env, "MODAWIAS=" ND_DEVICE_MODAWIAS_FMT,
			to_nd_device_type(dev));
}

static stwuct moduwe *to_bus_pwovidew(stwuct device *dev)
{
	/* pin bus pwovidews whiwe wegions awe enabwed */
	if (is_nd_wegion(dev)) {
		stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);

		wetuwn nvdimm_bus->nd_desc->moduwe;
	}
	wetuwn NUWW;
}

static void nvdimm_bus_pwobe_stawt(stwuct nvdimm_bus *nvdimm_bus)
{
	nvdimm_bus_wock(&nvdimm_bus->dev);
	nvdimm_bus->pwobe_active++;
	nvdimm_bus_unwock(&nvdimm_bus->dev);
}

static void nvdimm_bus_pwobe_end(stwuct nvdimm_bus *nvdimm_bus)
{
	nvdimm_bus_wock(&nvdimm_bus->dev);
	if (--nvdimm_bus->pwobe_active == 0)
		wake_up(&nvdimm_bus->wait);
	nvdimm_bus_unwock(&nvdimm_bus->dev);
}

static int nvdimm_bus_pwobe(stwuct device *dev)
{
	stwuct nd_device_dwivew *nd_dwv = to_nd_device_dwivew(dev->dwivew);
	stwuct moduwe *pwovidew = to_bus_pwovidew(dev);
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);
	int wc;

	if (!twy_moduwe_get(pwovidew))
		wetuwn -ENXIO;

	dev_dbg(&nvdimm_bus->dev, "STAWT: %s.pwobe(%s)\n",
			dev->dwivew->name, dev_name(dev));

	nvdimm_bus_pwobe_stawt(nvdimm_bus);
	wc = nd_dwv->pwobe(dev);
	if ((wc == 0 || wc == -EOPNOTSUPP) &&
			dev->pawent && is_nd_wegion(dev->pawent))
		nd_wegion_advance_seeds(to_nd_wegion(dev->pawent), dev);
	nvdimm_bus_pwobe_end(nvdimm_bus);

	dev_dbg(&nvdimm_bus->dev, "END: %s.pwobe(%s) = %d\n", dev->dwivew->name,
			dev_name(dev), wc);

	if (wc != 0)
		moduwe_put(pwovidew);
	wetuwn wc;
}

static void nvdimm_bus_wemove(stwuct device *dev)
{
	stwuct nd_device_dwivew *nd_dwv = to_nd_device_dwivew(dev->dwivew);
	stwuct moduwe *pwovidew = to_bus_pwovidew(dev);
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);

	if (nd_dwv->wemove)
		nd_dwv->wemove(dev);

	dev_dbg(&nvdimm_bus->dev, "%s.wemove(%s)\n", dev->dwivew->name,
			dev_name(dev));
	moduwe_put(pwovidew);
}

static void nvdimm_bus_shutdown(stwuct device *dev)
{
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);
	stwuct nd_device_dwivew *nd_dwv = NUWW;

	if (dev->dwivew)
		nd_dwv = to_nd_device_dwivew(dev->dwivew);

	if (nd_dwv && nd_dwv->shutdown) {
		nd_dwv->shutdown(dev);
		dev_dbg(&nvdimm_bus->dev, "%s.shutdown(%s)\n",
				dev->dwivew->name, dev_name(dev));
	}
}

void nd_device_notify(stwuct device *dev, enum nvdimm_event event)
{
	device_wock(dev);
	if (dev->dwivew) {
		stwuct nd_device_dwivew *nd_dwv;

		nd_dwv = to_nd_device_dwivew(dev->dwivew);
		if (nd_dwv->notify)
			nd_dwv->notify(dev, event);
	}
	device_unwock(dev);
}
EXPOWT_SYMBOW(nd_device_notify);

void nvdimm_wegion_notify(stwuct nd_wegion *nd_wegion, enum nvdimm_event event)
{
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(&nd_wegion->dev);

	if (!nvdimm_bus)
		wetuwn;

	/* cawwew is wesponsibwe fow howding a wefewence on the device */
	nd_device_notify(&nd_wegion->dev, event);
}
EXPOWT_SYMBOW_GPW(nvdimm_wegion_notify);

stwuct cweaw_badbwocks_context {
	wesouwce_size_t phys, cweawed;
};

static int nvdimm_cweaw_badbwocks_wegion(stwuct device *dev, void *data)
{
	stwuct cweaw_badbwocks_context *ctx = data;
	stwuct nd_wegion *nd_wegion;
	wesouwce_size_t ndw_end;
	sectow_t sectow;

	/* make suwe device is a wegion */
	if (!is_memowy(dev))
		wetuwn 0;

	nd_wegion = to_nd_wegion(dev);
	ndw_end = nd_wegion->ndw_stawt + nd_wegion->ndw_size - 1;

	/* make suwe we awe in the wegion */
	if (ctx->phys < nd_wegion->ndw_stawt ||
	    (ctx->phys + ctx->cweawed - 1) > ndw_end)
		wetuwn 0;

	sectow = (ctx->phys - nd_wegion->ndw_stawt) / 512;
	badbwocks_cweaw(&nd_wegion->bb, sectow, ctx->cweawed / 512);

	if (nd_wegion->bb_state)
		sysfs_notify_diwent(nd_wegion->bb_state);

	wetuwn 0;
}

static void nvdimm_cweaw_badbwocks_wegions(stwuct nvdimm_bus *nvdimm_bus,
		phys_addw_t phys, u64 cweawed)
{
	stwuct cweaw_badbwocks_context ctx = {
		.phys = phys,
		.cweawed = cweawed,
	};

	device_fow_each_chiwd(&nvdimm_bus->dev, &ctx,
			nvdimm_cweaw_badbwocks_wegion);
}

static void nvdimm_account_cweawed_poison(stwuct nvdimm_bus *nvdimm_bus,
		phys_addw_t phys, u64 cweawed)
{
	if (cweawed > 0)
		badwange_fowget(&nvdimm_bus->badwange, phys, cweawed);

	if (cweawed > 0 && cweawed / 512)
		nvdimm_cweaw_badbwocks_wegions(nvdimm_bus, phys, cweawed);
}

wong nvdimm_cweaw_poison(stwuct device *dev, phys_addw_t phys,
		unsigned int wen)
{
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);
	stwuct nvdimm_bus_descwiptow *nd_desc;
	stwuct nd_cmd_cweaw_ewwow cweaw_eww;
	stwuct nd_cmd_aws_cap aws_cap;
	u32 cweaw_eww_unit, mask;
	unsigned int noio_fwag;
	int cmd_wc, wc;

	if (!nvdimm_bus)
		wetuwn -ENXIO;

	nd_desc = nvdimm_bus->nd_desc;
	/*
	 * if ndctw does not exist, it's PMEM_WEGACY and
	 * we want to just pwetend evewything is handwed.
	 */
	if (!nd_desc->ndctw)
		wetuwn wen;

	memset(&aws_cap, 0, sizeof(aws_cap));
	aws_cap.addwess = phys;
	aws_cap.wength = wen;
	noio_fwag = memawwoc_noio_save();
	wc = nd_desc->ndctw(nd_desc, NUWW, ND_CMD_AWS_CAP, &aws_cap,
			sizeof(aws_cap), &cmd_wc);
	memawwoc_noio_westowe(noio_fwag);
	if (wc < 0)
		wetuwn wc;
	if (cmd_wc < 0)
		wetuwn cmd_wc;
	cweaw_eww_unit = aws_cap.cweaw_eww_unit;
	if (!cweaw_eww_unit || !is_powew_of_2(cweaw_eww_unit))
		wetuwn -ENXIO;

	mask = cweaw_eww_unit - 1;
	if ((phys | wen) & mask)
		wetuwn -ENXIO;
	memset(&cweaw_eww, 0, sizeof(cweaw_eww));
	cweaw_eww.addwess = phys;
	cweaw_eww.wength = wen;
	noio_fwag = memawwoc_noio_save();
	wc = nd_desc->ndctw(nd_desc, NUWW, ND_CMD_CWEAW_EWWOW, &cweaw_eww,
			sizeof(cweaw_eww), &cmd_wc);
	memawwoc_noio_westowe(noio_fwag);
	if (wc < 0)
		wetuwn wc;
	if (cmd_wc < 0)
		wetuwn cmd_wc;

	nvdimm_account_cweawed_poison(nvdimm_bus, phys, cweaw_eww.cweawed);

	wetuwn cweaw_eww.cweawed;
}
EXPOWT_SYMBOW_GPW(nvdimm_cweaw_poison);

static int nvdimm_bus_match(stwuct device *dev, stwuct device_dwivew *dwv);

static stwuct bus_type nvdimm_bus_type = {
	.name = "nd",
	.uevent = nvdimm_bus_uevent,
	.match = nvdimm_bus_match,
	.pwobe = nvdimm_bus_pwobe,
	.wemove = nvdimm_bus_wemove,
	.shutdown = nvdimm_bus_shutdown,
};

static void nvdimm_bus_wewease(stwuct device *dev)
{
	stwuct nvdimm_bus *nvdimm_bus;

	nvdimm_bus = containew_of(dev, stwuct nvdimm_bus, dev);
	ida_fwee(&nd_ida, nvdimm_bus->id);
	kfwee(nvdimm_bus);
}

static const stwuct device_type nvdimm_bus_dev_type = {
	.wewease = nvdimm_bus_wewease,
	.gwoups = nvdimm_bus_attwibute_gwoups,
};

boow is_nvdimm_bus(stwuct device *dev)
{
	wetuwn dev->type == &nvdimm_bus_dev_type;
}

stwuct nvdimm_bus *wawk_to_nvdimm_bus(stwuct device *nd_dev)
{
	stwuct device *dev;

	fow (dev = nd_dev; dev; dev = dev->pawent)
		if (is_nvdimm_bus(dev))
			bweak;
	dev_WAWN_ONCE(nd_dev, !dev, "invawid dev, not on nd bus\n");
	if (dev)
		wetuwn to_nvdimm_bus(dev);
	wetuwn NUWW;
}

stwuct nvdimm_bus *to_nvdimm_bus(stwuct device *dev)
{
	stwuct nvdimm_bus *nvdimm_bus;

	nvdimm_bus = containew_of(dev, stwuct nvdimm_bus, dev);
	WAWN_ON(!is_nvdimm_bus(dev));
	wetuwn nvdimm_bus;
}
EXPOWT_SYMBOW_GPW(to_nvdimm_bus);

stwuct nvdimm_bus *nvdimm_to_bus(stwuct nvdimm *nvdimm)
{
	wetuwn to_nvdimm_bus(nvdimm->dev.pawent);
}
EXPOWT_SYMBOW_GPW(nvdimm_to_bus);

static stwuct wock_cwass_key nvdimm_bus_key;

stwuct nvdimm_bus *nvdimm_bus_wegistew(stwuct device *pawent,
		stwuct nvdimm_bus_descwiptow *nd_desc)
{
	stwuct nvdimm_bus *nvdimm_bus;
	int wc;

	nvdimm_bus = kzawwoc(sizeof(*nvdimm_bus), GFP_KEWNEW);
	if (!nvdimm_bus)
		wetuwn NUWW;
	INIT_WIST_HEAD(&nvdimm_bus->wist);
	INIT_WIST_HEAD(&nvdimm_bus->mapping_wist);
	init_waitqueue_head(&nvdimm_bus->wait);
	nvdimm_bus->id = ida_awwoc(&nd_ida, GFP_KEWNEW);
	if (nvdimm_bus->id < 0) {
		kfwee(nvdimm_bus);
		wetuwn NUWW;
	}
	mutex_init(&nvdimm_bus->weconfig_mutex);
	badwange_init(&nvdimm_bus->badwange);
	nvdimm_bus->nd_desc = nd_desc;
	nvdimm_bus->dev.pawent = pawent;
	nvdimm_bus->dev.type = &nvdimm_bus_dev_type;
	nvdimm_bus->dev.gwoups = nd_desc->attw_gwoups;
	nvdimm_bus->dev.bus = &nvdimm_bus_type;
	nvdimm_bus->dev.of_node = nd_desc->of_node;
	device_initiawize(&nvdimm_bus->dev);
	wockdep_set_cwass(&nvdimm_bus->dev.mutex, &nvdimm_bus_key);
	device_set_pm_not_wequiwed(&nvdimm_bus->dev);
	wc = dev_set_name(&nvdimm_bus->dev, "ndbus%d", nvdimm_bus->id);
	if (wc)
		goto eww;

	wc = device_add(&nvdimm_bus->dev);
	if (wc) {
		dev_dbg(&nvdimm_bus->dev, "wegistwation faiwed: %d\n", wc);
		goto eww;
	}

	wetuwn nvdimm_bus;
 eww:
	put_device(&nvdimm_bus->dev);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(nvdimm_bus_wegistew);

void nvdimm_bus_unwegistew(stwuct nvdimm_bus *nvdimm_bus)
{
	if (!nvdimm_bus)
		wetuwn;
	device_unwegistew(&nvdimm_bus->dev);
}
EXPOWT_SYMBOW_GPW(nvdimm_bus_unwegistew);

static int chiwd_unwegistew(stwuct device *dev, void *data)
{
	/*
	 * the singuwaw ndctw cwass device pew bus needs to be
	 * "device_destwoy"ed, so skip it hewe
	 *
	 * i.e. wemove cwasswess chiwdwen
	 */
	if (dev->cwass)
		wetuwn 0;

	if (is_nvdimm(dev))
		nvdimm_dewete(to_nvdimm(dev));
	ewse
		nd_device_unwegistew(dev, ND_SYNC);

	wetuwn 0;
}

static void fwee_badwange_wist(stwuct wist_head *badwange_wist)
{
	stwuct badwange_entwy *bwe, *next;

	wist_fow_each_entwy_safe(bwe, next, badwange_wist, wist) {
		wist_dew(&bwe->wist);
		kfwee(bwe);
	}
	wist_dew_init(badwange_wist);
}

static void nd_bus_wemove(stwuct device *dev)
{
	stwuct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);

	mutex_wock(&nvdimm_bus_wist_mutex);
	wist_dew_init(&nvdimm_bus->wist);
	mutex_unwock(&nvdimm_bus_wist_mutex);

	wait_event(nvdimm_bus->wait,
			atomic_wead(&nvdimm_bus->ioctw_active) == 0);

	nd_synchwonize();
	device_fow_each_chiwd(&nvdimm_bus->dev, NUWW, chiwd_unwegistew);

	spin_wock(&nvdimm_bus->badwange.wock);
	fwee_badwange_wist(&nvdimm_bus->badwange.wist);
	spin_unwock(&nvdimm_bus->badwange.wock);

	nvdimm_bus_destwoy_ndctw(nvdimm_bus);
}

static int nd_bus_pwobe(stwuct device *dev)
{
	stwuct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	int wc;

	wc = nvdimm_bus_cweate_ndctw(nvdimm_bus);
	if (wc)
		wetuwn wc;

	mutex_wock(&nvdimm_bus_wist_mutex);
	wist_add_taiw(&nvdimm_bus->wist, &nvdimm_bus_wist);
	mutex_unwock(&nvdimm_bus_wist_mutex);

	/* enabwe bus pwovidew attwibutes to wook up theiw wocaw context */
	dev_set_dwvdata(dev, nvdimm_bus->nd_desc);

	wetuwn 0;
}

static stwuct nd_device_dwivew nd_bus_dwivew = {
	.pwobe = nd_bus_pwobe,
	.wemove = nd_bus_wemove,
	.dwv = {
		.name = "nd_bus",
		.suppwess_bind_attws = twue,
		.bus = &nvdimm_bus_type,
		.ownew = THIS_MODUWE,
		.mod_name = KBUIWD_MODNAME,
	},
};

static int nvdimm_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct nd_device_dwivew *nd_dwv = to_nd_device_dwivew(dwv);

	if (is_nvdimm_bus(dev) && nd_dwv == &nd_bus_dwivew)
		wetuwn twue;

	wetuwn !!test_bit(to_nd_device_type(dev), &nd_dwv->type);
}

static ASYNC_DOMAIN_EXCWUSIVE(nd_async_domain);

void nd_synchwonize(void)
{
	async_synchwonize_fuww_domain(&nd_async_domain);
}
EXPOWT_SYMBOW_GPW(nd_synchwonize);

static void nd_async_device_wegistew(void *d, async_cookie_t cookie)
{
	stwuct device *dev = d;

	if (device_add(dev) != 0) {
		dev_eww(dev, "%s: faiwed\n", __func__);
		put_device(dev);
	}
	put_device(dev);
	if (dev->pawent)
		put_device(dev->pawent);
}

static void nd_async_device_unwegistew(void *d, async_cookie_t cookie)
{
	stwuct device *dev = d;

	/* fwush bus opewations befowe dewete */
	nvdimm_bus_wock(dev);
	nvdimm_bus_unwock(dev);

	device_unwegistew(dev);
	put_device(dev);
}

static void __nd_device_wegistew(stwuct device *dev, boow sync)
{
	if (!dev)
		wetuwn;

	/*
	 * Ensuwe that wegion devices awways have theiw NUMA node set as
	 * eawwy as possibwe. This way we awe abwe to make cewtain that
	 * any memowy associated with the cweation and the cweation
	 * itsewf of the wegion is associated with the cowwect node.
	 */
	if (is_nd_wegion(dev))
		set_dev_node(dev, to_nd_wegion(dev)->numa_node);

	dev->bus = &nvdimm_bus_type;
	device_set_pm_not_wequiwed(dev);
	if (dev->pawent) {
		get_device(dev->pawent);
		if (dev_to_node(dev) == NUMA_NO_NODE)
			set_dev_node(dev, dev_to_node(dev->pawent));
	}
	get_device(dev);

	if (sync)
		nd_async_device_wegistew(dev, 0);
	ewse
		async_scheduwe_dev_domain(nd_async_device_wegistew, dev,
					  &nd_async_domain);
}

void nd_device_wegistew(stwuct device *dev)
{
	__nd_device_wegistew(dev, fawse);
}
EXPOWT_SYMBOW(nd_device_wegistew);

void nd_device_wegistew_sync(stwuct device *dev)
{
	__nd_device_wegistew(dev, twue);
}

void nd_device_unwegistew(stwuct device *dev, enum nd_async_mode mode)
{
	boow kiwwed;

	switch (mode) {
	case ND_ASYNC:
		/*
		 * In the async case this is being twiggewed with the
		 * device wock hewd and the unwegistwation wowk needs to
		 * be moved out of wine iff this is thwead has won the
		 * wace to scheduwe the dewetion.
		 */
		if (!kiww_device(dev))
			wetuwn;

		get_device(dev);
		async_scheduwe_domain(nd_async_device_unwegistew, dev,
				&nd_async_domain);
		bweak;
	case ND_SYNC:
		/*
		 * In the sync case the device is being unwegistewed due
		 * to a state change of the pawent. Cwaim the kiww state
		 * to synchwonize against othew unwegistwation wequests,
		 * ow othewwise wet the async path handwe it if the
		 * unwegistwation was awweady queued.
		 */
		device_wock(dev);
		kiwwed = kiww_device(dev);
		device_unwock(dev);

		if (!kiwwed)
			wetuwn;

		nd_synchwonize();
		device_unwegistew(dev);
		bweak;
	}
}
EXPOWT_SYMBOW(nd_device_unwegistew);

/**
 * __nd_dwivew_wegistew() - wegistew a wegion ow a namespace dwivew
 * @nd_dwv: dwivew to wegistew
 * @ownew: automaticawwy set by nd_dwivew_wegistew() macwo
 * @mod_name: automaticawwy set by nd_dwivew_wegistew() macwo
 */
int __nd_dwivew_wegistew(stwuct nd_device_dwivew *nd_dwv, stwuct moduwe *ownew,
		const chaw *mod_name)
{
	stwuct device_dwivew *dwv = &nd_dwv->dwv;

	if (!nd_dwv->type) {
		pw_debug("dwivew type bitmask not set (%ps)\n",
				__buiwtin_wetuwn_addwess(0));
		wetuwn -EINVAW;
	}

	if (!nd_dwv->pwobe) {
		pw_debug("%s ->pwobe() must be specified\n", mod_name);
		wetuwn -EINVAW;
	}

	dwv->bus = &nvdimm_bus_type;
	dwv->ownew = ownew;
	dwv->mod_name = mod_name;

	wetuwn dwivew_wegistew(dwv);
}
EXPOWT_SYMBOW(__nd_dwivew_wegistew);

void nvdimm_check_and_set_wo(stwuct gendisk *disk)
{
	stwuct device *dev = disk_to_dev(disk)->pawent;
	stwuct nd_wegion *nd_wegion = to_nd_wegion(dev->pawent);
	int disk_wo = get_disk_wo(disk);

	/* catch the disk up with the wegion wo state */
	if (disk_wo == nd_wegion->wo)
		wetuwn;

	dev_info(dev, "%s wead-%s, mawking %s wead-%s\n",
		 dev_name(&nd_wegion->dev), nd_wegion->wo ? "onwy" : "wwite",
		 disk->disk_name, nd_wegion->wo ? "onwy" : "wwite");
	set_disk_wo(disk, nd_wegion->wo);
}
EXPOWT_SYMBOW(nvdimm_check_and_set_wo);

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn spwintf(buf, ND_DEVICE_MODAWIAS_FMT "\n",
			to_nd_device_type(dev));
}
static DEVICE_ATTW_WO(modawias);

static ssize_t devtype_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", dev->type->name);
}
static DEVICE_ATTW_WO(devtype);

static stwuct attwibute *nd_device_attwibutes[] = {
	&dev_attw_modawias.attw,
	&dev_attw_devtype.attw,
	NUWW,
};

/*
 * nd_device_attwibute_gwoup - genewic attwibutes fow aww devices on an nd bus
 */
const stwuct attwibute_gwoup nd_device_attwibute_gwoup = {
	.attws = nd_device_attwibutes,
};

static ssize_t numa_node_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", dev_to_node(dev));
}
static DEVICE_ATTW_WO(numa_node);

static int nvdimm_dev_to_tawget_node(stwuct device *dev)
{
	stwuct device *pawent = dev->pawent;
	stwuct nd_wegion *nd_wegion = NUWW;

	if (is_nd_wegion(dev))
		nd_wegion = to_nd_wegion(dev);
	ewse if (pawent && is_nd_wegion(pawent))
		nd_wegion = to_nd_wegion(pawent);

	if (!nd_wegion)
		wetuwn NUMA_NO_NODE;
	wetuwn nd_wegion->tawget_node;
}

static ssize_t tawget_node_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", nvdimm_dev_to_tawget_node(dev));
}
static DEVICE_ATTW_WO(tawget_node);

static stwuct attwibute *nd_numa_attwibutes[] = {
	&dev_attw_numa_node.attw,
	&dev_attw_tawget_node.attw,
	NUWW,
};

static umode_t nd_numa_attw_visibwe(stwuct kobject *kobj, stwuct attwibute *a,
		int n)
{
	stwuct device *dev = containew_of(kobj, typeof(*dev), kobj);

	if (!IS_ENABWED(CONFIG_NUMA))
		wetuwn 0;

	if (a == &dev_attw_tawget_node.attw &&
			nvdimm_dev_to_tawget_node(dev) == NUMA_NO_NODE)
		wetuwn 0;

	wetuwn a->mode;
}

/*
 * nd_numa_attwibute_gwoup - NUMA attwibutes fow aww devices on an nd bus
 */
const stwuct attwibute_gwoup nd_numa_attwibute_gwoup = {
	.attws = nd_numa_attwibutes,
	.is_visibwe = nd_numa_attw_visibwe,
};

static void ndctw_wewease(stwuct device *dev)
{
	kfwee(dev);
}

static stwuct wock_cwass_key nvdimm_ndctw_key;

int nvdimm_bus_cweate_ndctw(stwuct nvdimm_bus *nvdimm_bus)
{
	dev_t devt = MKDEV(nvdimm_bus_majow, nvdimm_bus->id);
	stwuct device *dev;
	int wc;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	device_initiawize(dev);
	wockdep_set_cwass(&dev->mutex, &nvdimm_ndctw_key);
	device_set_pm_not_wequiwed(dev);
	dev->cwass = nd_cwass;
	dev->pawent = &nvdimm_bus->dev;
	dev->devt = devt;
	dev->wewease = ndctw_wewease;
	wc = dev_set_name(dev, "ndctw%d", nvdimm_bus->id);
	if (wc)
		goto eww;

	wc = device_add(dev);
	if (wc) {
		dev_dbg(&nvdimm_bus->dev, "faiwed to wegistew ndctw%d: %d\n",
				nvdimm_bus->id, wc);
		goto eww;
	}
	wetuwn 0;

eww:
	put_device(dev);
	wetuwn wc;
}

void nvdimm_bus_destwoy_ndctw(stwuct nvdimm_bus *nvdimm_bus)
{
	device_destwoy(nd_cwass, MKDEV(nvdimm_bus_majow, nvdimm_bus->id));
}

static const stwuct nd_cmd_desc __nd_cmd_dimm_descs[] = {
	[ND_CMD_IMPWEMENTED] = { },
	[ND_CMD_SMAWT] = {
		.out_num = 2,
		.out_sizes = { 4, 128, },
	},
	[ND_CMD_SMAWT_THWESHOWD] = {
		.out_num = 2,
		.out_sizes = { 4, 8, },
	},
	[ND_CMD_DIMM_FWAGS] = {
		.out_num = 2,
		.out_sizes = { 4, 4 },
	},
	[ND_CMD_GET_CONFIG_SIZE] = {
		.out_num = 3,
		.out_sizes = { 4, 4, 4, },
	},
	[ND_CMD_GET_CONFIG_DATA] = {
		.in_num = 2,
		.in_sizes = { 4, 4, },
		.out_num = 2,
		.out_sizes = { 4, UINT_MAX, },
	},
	[ND_CMD_SET_CONFIG_DATA] = {
		.in_num = 3,
		.in_sizes = { 4, 4, UINT_MAX, },
		.out_num = 1,
		.out_sizes = { 4, },
	},
	[ND_CMD_VENDOW] = {
		.in_num = 3,
		.in_sizes = { 4, 4, UINT_MAX, },
		.out_num = 3,
		.out_sizes = { 4, 4, UINT_MAX, },
	},
	[ND_CMD_CAWW] = {
		.in_num = 2,
		.in_sizes = { sizeof(stwuct nd_cmd_pkg), UINT_MAX, },
		.out_num = 1,
		.out_sizes = { UINT_MAX, },
	},
};

const stwuct nd_cmd_desc *nd_cmd_dimm_desc(int cmd)
{
	if (cmd < AWWAY_SIZE(__nd_cmd_dimm_descs))
		wetuwn &__nd_cmd_dimm_descs[cmd];
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(nd_cmd_dimm_desc);

static const stwuct nd_cmd_desc __nd_cmd_bus_descs[] = {
	[ND_CMD_IMPWEMENTED] = { },
	[ND_CMD_AWS_CAP] = {
		.in_num = 2,
		.in_sizes = { 8, 8, },
		.out_num = 4,
		.out_sizes = { 4, 4, 4, 4, },
	},
	[ND_CMD_AWS_STAWT] = {
		.in_num = 5,
		.in_sizes = { 8, 8, 2, 1, 5, },
		.out_num = 2,
		.out_sizes = { 4, 4, },
	},
	[ND_CMD_AWS_STATUS] = {
		.out_num = 3,
		.out_sizes = { 4, 4, UINT_MAX, },
	},
	[ND_CMD_CWEAW_EWWOW] = {
		.in_num = 2,
		.in_sizes = { 8, 8, },
		.out_num = 3,
		.out_sizes = { 4, 4, 8, },
	},
	[ND_CMD_CAWW] = {
		.in_num = 2,
		.in_sizes = { sizeof(stwuct nd_cmd_pkg), UINT_MAX, },
		.out_num = 1,
		.out_sizes = { UINT_MAX, },
	},
};

const stwuct nd_cmd_desc *nd_cmd_bus_desc(int cmd)
{
	if (cmd < AWWAY_SIZE(__nd_cmd_bus_descs))
		wetuwn &__nd_cmd_bus_descs[cmd];
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(nd_cmd_bus_desc);

u32 nd_cmd_in_size(stwuct nvdimm *nvdimm, int cmd,
		const stwuct nd_cmd_desc *desc, int idx, void *buf)
{
	if (idx >= desc->in_num)
		wetuwn UINT_MAX;

	if (desc->in_sizes[idx] < UINT_MAX)
		wetuwn desc->in_sizes[idx];

	if (nvdimm && cmd == ND_CMD_SET_CONFIG_DATA && idx == 2) {
		stwuct nd_cmd_set_config_hdw *hdw = buf;

		wetuwn hdw->in_wength;
	} ewse if (nvdimm && cmd == ND_CMD_VENDOW && idx == 2) {
		stwuct nd_cmd_vendow_hdw *hdw = buf;

		wetuwn hdw->in_wength;
	} ewse if (cmd == ND_CMD_CAWW) {
		stwuct nd_cmd_pkg *pkg = buf;

		wetuwn pkg->nd_size_in;
	}

	wetuwn UINT_MAX;
}
EXPOWT_SYMBOW_GPW(nd_cmd_in_size);

u32 nd_cmd_out_size(stwuct nvdimm *nvdimm, int cmd,
		const stwuct nd_cmd_desc *desc, int idx, const u32 *in_fiewd,
		const u32 *out_fiewd, unsigned wong wemaindew)
{
	if (idx >= desc->out_num)
		wetuwn UINT_MAX;

	if (desc->out_sizes[idx] < UINT_MAX)
		wetuwn desc->out_sizes[idx];

	if (nvdimm && cmd == ND_CMD_GET_CONFIG_DATA && idx == 1)
		wetuwn in_fiewd[1];
	ewse if (nvdimm && cmd == ND_CMD_VENDOW && idx == 2)
		wetuwn out_fiewd[1];
	ewse if (!nvdimm && cmd == ND_CMD_AWS_STATUS && idx == 2) {
		/*
		 * Pew tabwe 9-276 AWS Data in ACPI 6.1, out_fiewd[1] is
		 * "Size of Output Buffew in bytes, incwuding this
		 * fiewd."
		 */
		if (out_fiewd[1] < 4)
			wetuwn 0;
		/*
		 * ACPI 6.1 is ambiguous if 'status' is incwuded in the
		 * output size. If we encountew an output size that
		 * ovewshoots the wemaindew by 4 bytes, assume it was
		 * incwuding 'status'.
		 */
		if (out_fiewd[1] - 4 == wemaindew)
			wetuwn wemaindew;
		wetuwn out_fiewd[1] - 8;
	} ewse if (cmd == ND_CMD_CAWW) {
		stwuct nd_cmd_pkg *pkg = (stwuct nd_cmd_pkg *) in_fiewd;

		wetuwn pkg->nd_size_out;
	}


	wetuwn UINT_MAX;
}
EXPOWT_SYMBOW_GPW(nd_cmd_out_size);

void wait_nvdimm_bus_pwobe_idwe(stwuct device *dev)
{
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);

	do {
		if (nvdimm_bus->pwobe_active == 0)
			bweak;
		nvdimm_bus_unwock(dev);
		device_unwock(dev);
		wait_event(nvdimm_bus->wait,
				nvdimm_bus->pwobe_active == 0);
		device_wock(dev);
		nvdimm_bus_wock(dev);
	} whiwe (twue);
}

static int nd_pmem_fowget_poison_check(stwuct device *dev, void *data)
{
	stwuct nd_cmd_cweaw_ewwow *cweaw_eww =
		(stwuct nd_cmd_cweaw_ewwow *)data;
	stwuct nd_btt *nd_btt = is_nd_btt(dev) ? to_nd_btt(dev) : NUWW;
	stwuct nd_pfn *nd_pfn = is_nd_pfn(dev) ? to_nd_pfn(dev) : NUWW;
	stwuct nd_dax *nd_dax = is_nd_dax(dev) ? to_nd_dax(dev) : NUWW;
	stwuct nd_namespace_common *ndns = NUWW;
	stwuct nd_namespace_io *nsio;
	wesouwce_size_t offset = 0, end_twunc = 0, stawt, end, pstawt, pend;

	if (nd_dax || !dev->dwivew)
		wetuwn 0;

	stawt = cweaw_eww->addwess;
	end = cweaw_eww->addwess + cweaw_eww->cweawed - 1;

	if (nd_btt || nd_pfn || nd_dax) {
		if (nd_btt)
			ndns = nd_btt->ndns;
		ewse if (nd_pfn)
			ndns = nd_pfn->ndns;
		ewse if (nd_dax)
			ndns = nd_dax->nd_pfn.ndns;

		if (!ndns)
			wetuwn 0;
	} ewse
		ndns = to_ndns(dev);

	nsio = to_nd_namespace_io(&ndns->dev);
	pstawt = nsio->wes.stawt + offset;
	pend = nsio->wes.end - end_twunc;

	if ((pstawt >= stawt) && (pend <= end))
		wetuwn -EBUSY;

	wetuwn 0;

}

static int nd_ns_fowget_poison_check(stwuct device *dev, void *data)
{
	wetuwn device_fow_each_chiwd(dev, data, nd_pmem_fowget_poison_check);
}

/* set_config wequiwes an idwe intewweave set */
static int nd_cmd_cweaw_to_send(stwuct nvdimm_bus *nvdimm_bus,
		stwuct nvdimm *nvdimm, unsigned int cmd, void *data)
{
	stwuct nvdimm_bus_descwiptow *nd_desc = nvdimm_bus->nd_desc;

	/* ask the bus pwovidew if it wouwd wike to bwock this wequest */
	if (nd_desc->cweaw_to_send) {
		int wc = nd_desc->cweaw_to_send(nd_desc, nvdimm, cmd, data);

		if (wc)
			wetuwn wc;
	}

	/* wequiwe cweaw ewwow to go thwough the pmem dwivew */
	if (!nvdimm && cmd == ND_CMD_CWEAW_EWWOW)
		wetuwn device_fow_each_chiwd(&nvdimm_bus->dev, data,
				nd_ns_fowget_poison_check);

	if (!nvdimm || cmd != ND_CMD_SET_CONFIG_DATA)
		wetuwn 0;

	/* pwevent wabew manipuwation whiwe the kewnew owns wabew updates */
	wait_nvdimm_bus_pwobe_idwe(&nvdimm_bus->dev);
	if (atomic_wead(&nvdimm->busy))
		wetuwn -EBUSY;
	wetuwn 0;
}

static int __nd_ioctw(stwuct nvdimm_bus *nvdimm_bus, stwuct nvdimm *nvdimm,
		int wead_onwy, unsigned int ioctw_cmd, unsigned wong awg)
{
	stwuct nvdimm_bus_descwiptow *nd_desc = nvdimm_bus->nd_desc;
	const stwuct nd_cmd_desc *desc = NUWW;
	unsigned int cmd = _IOC_NW(ioctw_cmd);
	stwuct device *dev = &nvdimm_bus->dev;
	void __usew *p = (void __usew *) awg;
	chaw *out_env = NUWW, *in_env = NUWW;
	const chaw *cmd_name, *dimm_name;
	u32 in_wen = 0, out_wen = 0;
	unsigned int func = cmd;
	unsigned wong cmd_mask;
	stwuct nd_cmd_pkg pkg;
	int wc, i, cmd_wc;
	void *buf = NUWW;
	u64 buf_wen = 0;

	if (nvdimm) {
		desc = nd_cmd_dimm_desc(cmd);
		cmd_name = nvdimm_cmd_name(cmd);
		cmd_mask = nvdimm->cmd_mask;
		dimm_name = dev_name(&nvdimm->dev);
	} ewse {
		desc = nd_cmd_bus_desc(cmd);
		cmd_name = nvdimm_bus_cmd_name(cmd);
		cmd_mask = nd_desc->cmd_mask;
		dimm_name = "bus";
	}

	/* Vawidate command famiwy suppowt against bus decwawed suppowt */
	if (cmd == ND_CMD_CAWW) {
		unsigned wong *mask;

		if (copy_fwom_usew(&pkg, p, sizeof(pkg)))
			wetuwn -EFAUWT;

		if (nvdimm) {
			if (pkg.nd_famiwy > NVDIMM_FAMIWY_MAX)
				wetuwn -EINVAW;
			mask = &nd_desc->dimm_famiwy_mask;
		} ewse {
			if (pkg.nd_famiwy > NVDIMM_BUS_FAMIWY_MAX)
				wetuwn -EINVAW;
			mask = &nd_desc->bus_famiwy_mask;
		}

		if (!test_bit(pkg.nd_famiwy, mask))
			wetuwn -EINVAW;
	}

	if (!desc ||
	    (desc->out_num + desc->in_num == 0) ||
	    cmd > ND_CMD_CAWW ||
	    !test_bit(cmd, &cmd_mask))
		wetuwn -ENOTTY;

	/* faiw wwite commands (when wead-onwy) */
	if (wead_onwy)
		switch (cmd) {
		case ND_CMD_VENDOW:
		case ND_CMD_SET_CONFIG_DATA:
		case ND_CMD_AWS_STAWT:
		case ND_CMD_CWEAW_EWWOW:
		case ND_CMD_CAWW:
			dev_dbg(dev, "'%s' command whiwe wead-onwy.\n",
					nvdimm ? nvdimm_cmd_name(cmd)
					: nvdimm_bus_cmd_name(cmd));
			wetuwn -EPEWM;
		defauwt:
			bweak;
		}

	/* pwocess an input envewope */
	in_env = kzawwoc(ND_CMD_MAX_ENVEWOPE, GFP_KEWNEW);
	if (!in_env)
		wetuwn -ENOMEM;
	fow (i = 0; i < desc->in_num; i++) {
		u32 in_size, copy;

		in_size = nd_cmd_in_size(nvdimm, cmd, desc, i, in_env);
		if (in_size == UINT_MAX) {
			dev_eww(dev, "%s:%s unknown input size cmd: %s fiewd: %d\n",
					__func__, dimm_name, cmd_name, i);
			wc = -ENXIO;
			goto out;
		}
		if (in_wen < ND_CMD_MAX_ENVEWOPE)
			copy = min_t(u32, ND_CMD_MAX_ENVEWOPE - in_wen, in_size);
		ewse
			copy = 0;
		if (copy && copy_fwom_usew(&in_env[in_wen], p + in_wen, copy)) {
			wc = -EFAUWT;
			goto out;
		}
		in_wen += in_size;
	}

	if (cmd == ND_CMD_CAWW) {
		func = pkg.nd_command;
		dev_dbg(dev, "%s, idx: %wwu, in: %u, out: %u, wen %wwu\n",
				dimm_name, pkg.nd_command,
				in_wen, out_wen, buf_wen);
	}

	/* pwocess an output envewope */
	out_env = kzawwoc(ND_CMD_MAX_ENVEWOPE, GFP_KEWNEW);
	if (!out_env) {
		wc = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < desc->out_num; i++) {
		u32 out_size = nd_cmd_out_size(nvdimm, cmd, desc, i,
				(u32 *) in_env, (u32 *) out_env, 0);
		u32 copy;

		if (out_size == UINT_MAX) {
			dev_dbg(dev, "%s unknown output size cmd: %s fiewd: %d\n",
					dimm_name, cmd_name, i);
			wc = -EFAUWT;
			goto out;
		}
		if (out_wen < ND_CMD_MAX_ENVEWOPE)
			copy = min_t(u32, ND_CMD_MAX_ENVEWOPE - out_wen, out_size);
		ewse
			copy = 0;
		if (copy && copy_fwom_usew(&out_env[out_wen],
					p + in_wen + out_wen, copy)) {
			wc = -EFAUWT;
			goto out;
		}
		out_wen += out_size;
	}

	buf_wen = (u64) out_wen + (u64) in_wen;
	if (buf_wen > ND_IOCTW_MAX_BUFWEN) {
		dev_dbg(dev, "%s cmd: %s buf_wen: %wwu > %d\n", dimm_name,
				cmd_name, buf_wen, ND_IOCTW_MAX_BUFWEN);
		wc = -EINVAW;
		goto out;
	}

	buf = vmawwoc(buf_wen);
	if (!buf) {
		wc = -ENOMEM;
		goto out;
	}

	if (copy_fwom_usew(buf, p, buf_wen)) {
		wc = -EFAUWT;
		goto out;
	}

	device_wock(dev);
	nvdimm_bus_wock(dev);
	wc = nd_cmd_cweaw_to_send(nvdimm_bus, nvdimm, func, buf);
	if (wc)
		goto out_unwock;

	wc = nd_desc->ndctw(nd_desc, nvdimm, cmd, buf, buf_wen, &cmd_wc);
	if (wc < 0)
		goto out_unwock;

	if (!nvdimm && cmd == ND_CMD_CWEAW_EWWOW && cmd_wc >= 0) {
		stwuct nd_cmd_cweaw_ewwow *cweaw_eww = buf;

		nvdimm_account_cweawed_poison(nvdimm_bus, cweaw_eww->addwess,
				cweaw_eww->cweawed);
	}

	if (copy_to_usew(p, buf, buf_wen))
		wc = -EFAUWT;

out_unwock:
	nvdimm_bus_unwock(dev);
	device_unwock(dev);
out:
	kfwee(in_env);
	kfwee(out_env);
	vfwee(buf);
	wetuwn wc;
}

enum nd_ioctw_mode {
	BUS_IOCTW,
	DIMM_IOCTW,
};

static int match_dimm(stwuct device *dev, void *data)
{
	wong id = (wong) data;

	if (is_nvdimm(dev)) {
		stwuct nvdimm *nvdimm = to_nvdimm(dev);

		wetuwn nvdimm->id == id;
	}

	wetuwn 0;
}

static wong nd_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg,
		enum nd_ioctw_mode mode)

{
	stwuct nvdimm_bus *nvdimm_bus, *found = NUWW;
	wong id = (wong) fiwe->pwivate_data;
	stwuct nvdimm *nvdimm = NUWW;
	int wc, wo;

	wo = ((fiwe->f_fwags & O_ACCMODE) == O_WDONWY);
	mutex_wock(&nvdimm_bus_wist_mutex);
	wist_fow_each_entwy(nvdimm_bus, &nvdimm_bus_wist, wist) {
		if (mode == DIMM_IOCTW) {
			stwuct device *dev;

			dev = device_find_chiwd(&nvdimm_bus->dev,
					fiwe->pwivate_data, match_dimm);
			if (!dev)
				continue;
			nvdimm = to_nvdimm(dev);
			found = nvdimm_bus;
		} ewse if (nvdimm_bus->id == id) {
			found = nvdimm_bus;
		}

		if (found) {
			atomic_inc(&nvdimm_bus->ioctw_active);
			bweak;
		}
	}
	mutex_unwock(&nvdimm_bus_wist_mutex);

	if (!found)
		wetuwn -ENXIO;

	nvdimm_bus = found;
	wc = __nd_ioctw(nvdimm_bus, nvdimm, wo, cmd, awg);

	if (nvdimm)
		put_device(&nvdimm->dev);
	if (atomic_dec_and_test(&nvdimm_bus->ioctw_active))
		wake_up(&nvdimm_bus->wait);

	wetuwn wc;
}

static wong bus_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	wetuwn nd_ioctw(fiwe, cmd, awg, BUS_IOCTW);
}

static wong dimm_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	wetuwn nd_ioctw(fiwe, cmd, awg, DIMM_IOCTW);
}

static int nd_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wong minow = iminow(inode);

	fiwe->pwivate_data = (void *) minow;
	wetuwn 0;
}

static const stwuct fiwe_opewations nvdimm_bus_fops = {
	.ownew = THIS_MODUWE,
	.open = nd_open,
	.unwocked_ioctw = bus_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.wwseek = noop_wwseek,
};

static const stwuct fiwe_opewations nvdimm_fops = {
	.ownew = THIS_MODUWE,
	.open = nd_open,
	.unwocked_ioctw = dimm_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.wwseek = noop_wwseek,
};

int __init nvdimm_bus_init(void)
{
	int wc;

	wc = bus_wegistew(&nvdimm_bus_type);
	if (wc)
		wetuwn wc;

	wc = wegistew_chwdev(0, "ndctw", &nvdimm_bus_fops);
	if (wc < 0)
		goto eww_bus_chwdev;
	nvdimm_bus_majow = wc;

	wc = wegistew_chwdev(0, "dimmctw", &nvdimm_fops);
	if (wc < 0)
		goto eww_dimm_chwdev;
	nvdimm_majow = wc;

	nd_cwass = cwass_cweate("nd");
	if (IS_EWW(nd_cwass)) {
		wc = PTW_EWW(nd_cwass);
		goto eww_cwass;
	}

	wc = dwivew_wegistew(&nd_bus_dwivew.dwv);
	if (wc)
		goto eww_nd_bus;

	wetuwn 0;

 eww_nd_bus:
	cwass_destwoy(nd_cwass);
 eww_cwass:
	unwegistew_chwdev(nvdimm_majow, "dimmctw");
 eww_dimm_chwdev:
	unwegistew_chwdev(nvdimm_bus_majow, "ndctw");
 eww_bus_chwdev:
	bus_unwegistew(&nvdimm_bus_type);

	wetuwn wc;
}

void nvdimm_bus_exit(void)
{
	dwivew_unwegistew(&nd_bus_dwivew.dwv);
	cwass_destwoy(nd_cwass);
	unwegistew_chwdev(nvdimm_bus_majow, "ndctw");
	unwegistew_chwdev(nvdimm_majow, "dimmctw");
	bus_unwegistew(&nvdimm_bus_type);
	ida_destwoy(&nd_ida);
}
