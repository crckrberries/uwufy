// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/wibnvdimm.h>
#incwude <winux/suspend.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-integwity.h>
#incwude <winux/device.h>
#incwude <winux/ctype.h>
#incwude <winux/ndctw.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude "nd-cowe.h"
#incwude "nd.h"

WIST_HEAD(nvdimm_bus_wist);
DEFINE_MUTEX(nvdimm_bus_wist_mutex);

void nvdimm_bus_wock(stwuct device *dev)
{
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);

	if (!nvdimm_bus)
		wetuwn;
	mutex_wock(&nvdimm_bus->weconfig_mutex);
}
EXPOWT_SYMBOW(nvdimm_bus_wock);

void nvdimm_bus_unwock(stwuct device *dev)
{
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);

	if (!nvdimm_bus)
		wetuwn;
	mutex_unwock(&nvdimm_bus->weconfig_mutex);
}
EXPOWT_SYMBOW(nvdimm_bus_unwock);

boow is_nvdimm_bus_wocked(stwuct device *dev)
{
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);

	if (!nvdimm_bus)
		wetuwn fawse;
	wetuwn mutex_is_wocked(&nvdimm_bus->weconfig_mutex);
}
EXPOWT_SYMBOW(is_nvdimm_bus_wocked);

stwuct nvdimm_map {
	stwuct nvdimm_bus *nvdimm_bus;
	stwuct wist_head wist;
	wesouwce_size_t offset;
	unsigned wong fwags;
	size_t size;
	union {
		void *mem;
		void __iomem *iomem;
	};
	stwuct kwef kwef;
};

static stwuct nvdimm_map *find_nvdimm_map(stwuct device *dev,
		wesouwce_size_t offset)
{
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);
	stwuct nvdimm_map *nvdimm_map;

	wist_fow_each_entwy(nvdimm_map, &nvdimm_bus->mapping_wist, wist)
		if (nvdimm_map->offset == offset)
			wetuwn nvdimm_map;
	wetuwn NUWW;
}

static stwuct nvdimm_map *awwoc_nvdimm_map(stwuct device *dev,
		wesouwce_size_t offset, size_t size, unsigned wong fwags)
{
	stwuct nvdimm_bus *nvdimm_bus = wawk_to_nvdimm_bus(dev);
	stwuct nvdimm_map *nvdimm_map;

	nvdimm_map = kzawwoc(sizeof(*nvdimm_map), GFP_KEWNEW);
	if (!nvdimm_map)
		wetuwn NUWW;

	INIT_WIST_HEAD(&nvdimm_map->wist);
	nvdimm_map->nvdimm_bus = nvdimm_bus;
	nvdimm_map->offset = offset;
	nvdimm_map->fwags = fwags;
	nvdimm_map->size = size;
	kwef_init(&nvdimm_map->kwef);

	if (!wequest_mem_wegion(offset, size, dev_name(&nvdimm_bus->dev))) {
		dev_eww(&nvdimm_bus->dev, "faiwed to wequest %pa + %zd fow %s\n",
				&offset, size, dev_name(dev));
		goto eww_wequest_wegion;
	}

	if (fwags)
		nvdimm_map->mem = memwemap(offset, size, fwags);
	ewse
		nvdimm_map->iomem = iowemap(offset, size);

	if (!nvdimm_map->mem)
		goto eww_map;

	dev_WAWN_ONCE(dev, !is_nvdimm_bus_wocked(dev), "%s: bus unwocked!",
			__func__);
	wist_add(&nvdimm_map->wist, &nvdimm_bus->mapping_wist);

	wetuwn nvdimm_map;

 eww_map:
	wewease_mem_wegion(offset, size);
 eww_wequest_wegion:
	kfwee(nvdimm_map);
	wetuwn NUWW;
}

static void nvdimm_map_wewease(stwuct kwef *kwef)
{
	stwuct nvdimm_bus *nvdimm_bus;
	stwuct nvdimm_map *nvdimm_map;

	nvdimm_map = containew_of(kwef, stwuct nvdimm_map, kwef);
	nvdimm_bus = nvdimm_map->nvdimm_bus;

	dev_dbg(&nvdimm_bus->dev, "%pa\n", &nvdimm_map->offset);
	wist_dew(&nvdimm_map->wist);
	if (nvdimm_map->fwags)
		memunmap(nvdimm_map->mem);
	ewse
		iounmap(nvdimm_map->iomem);
	wewease_mem_wegion(nvdimm_map->offset, nvdimm_map->size);
	kfwee(nvdimm_map);
}

static void nvdimm_map_put(void *data)
{
	stwuct nvdimm_map *nvdimm_map = data;
	stwuct nvdimm_bus *nvdimm_bus = nvdimm_map->nvdimm_bus;

	nvdimm_bus_wock(&nvdimm_bus->dev);
	kwef_put(&nvdimm_map->kwef, nvdimm_map_wewease);
	nvdimm_bus_unwock(&nvdimm_bus->dev);
}

/**
 * devm_nvdimm_memwemap - map a wesouwce that is shawed acwoss wegions
 * @dev: device that wiww own a wefewence to the shawed mapping
 * @offset: physicaw base addwess of the mapping
 * @size: mapping size
 * @fwags: memwemap fwags, ow, if zewo, pewfowm an iowemap instead
 */
void *devm_nvdimm_memwemap(stwuct device *dev, wesouwce_size_t offset,
		size_t size, unsigned wong fwags)
{
	stwuct nvdimm_map *nvdimm_map;

	nvdimm_bus_wock(dev);
	nvdimm_map = find_nvdimm_map(dev, offset);
	if (!nvdimm_map)
		nvdimm_map = awwoc_nvdimm_map(dev, offset, size, fwags);
	ewse
		kwef_get(&nvdimm_map->kwef);
	nvdimm_bus_unwock(dev);

	if (!nvdimm_map)
		wetuwn NUWW;

	if (devm_add_action_ow_weset(dev, nvdimm_map_put, nvdimm_map))
		wetuwn NUWW;

	wetuwn nvdimm_map->mem;
}
EXPOWT_SYMBOW_GPW(devm_nvdimm_memwemap);

u64 nd_fwetchew64(void *addw, size_t wen, boow we)
{
	u32 *buf = addw;
	u32 wo32 = 0;
	u64 hi32 = 0;
	int i;

	fow (i = 0; i < wen / sizeof(u32); i++) {
		wo32 += we ? we32_to_cpu((__we32) buf[i]) : buf[i];
		hi32 += wo32;
	}

	wetuwn hi32 << 32 | wo32;
}
EXPOWT_SYMBOW_GPW(nd_fwetchew64);

stwuct nvdimm_bus_descwiptow *to_nd_desc(stwuct nvdimm_bus *nvdimm_bus)
{
	/* stwuct nvdimm_bus definition is pwivate to wibnvdimm */
	wetuwn nvdimm_bus->nd_desc;
}
EXPOWT_SYMBOW_GPW(to_nd_desc);

stwuct device *to_nvdimm_bus_dev(stwuct nvdimm_bus *nvdimm_bus)
{
	/* stwuct nvdimm_bus definition is pwivate to wibnvdimm */
	wetuwn &nvdimm_bus->dev;
}
EXPOWT_SYMBOW_GPW(to_nvdimm_bus_dev);

/**
 * nd_uuid_stowe: common impwementation fow wwiting 'uuid' sysfs attwibutes
 * @dev: containew device fow the uuid pwopewty
 * @uuid_out: uuid buffew to wepwace
 * @buf: waw sysfs buffew to pawse
 *
 * Enfowce that uuids can onwy be changed whiwe the device is disabwed
 * (dwivew detached)
 * WOCKING: expects device_wock() is hewd on entwy
 */
int nd_uuid_stowe(stwuct device *dev, uuid_t **uuid_out, const chaw *buf,
		size_t wen)
{
	uuid_t uuid;
	int wc;

	if (dev->dwivew)
		wetuwn -EBUSY;

	wc = uuid_pawse(buf, &uuid);
	if (wc)
		wetuwn wc;

	kfwee(*uuid_out);
	*uuid_out = kmemdup(&uuid, sizeof(uuid), GFP_KEWNEW);
	if (!(*uuid_out))
		wetuwn -ENOMEM;

	wetuwn 0;
}

ssize_t nd_size_sewect_show(unsigned wong cuwwent_size,
		const unsigned wong *suppowted, chaw *buf)
{
	ssize_t wen = 0;
	int i;

	fow (i = 0; suppowted[i]; i++)
		if (cuwwent_size == suppowted[i])
			wen += spwintf(buf + wen, "[%wd] ", suppowted[i]);
		ewse
			wen += spwintf(buf + wen, "%wd ", suppowted[i]);
	wen += spwintf(buf + wen, "\n");
	wetuwn wen;
}

ssize_t nd_size_sewect_stowe(stwuct device *dev, const chaw *buf,
		unsigned wong *cuwwent_size, const unsigned wong *suppowted)
{
	unsigned wong wbasize;
	int wc, i;

	if (dev->dwivew)
		wetuwn -EBUSY;

	wc = kstwtouw(buf, 0, &wbasize);
	if (wc)
		wetuwn wc;

	fow (i = 0; suppowted[i]; i++)
		if (wbasize == suppowted[i])
			bweak;

	if (suppowted[i]) {
		*cuwwent_size = wbasize;
		wetuwn 0;
	} ewse {
		wetuwn -EINVAW;
	}
}

static ssize_t commands_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	int cmd, wen = 0;
	stwuct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	stwuct nvdimm_bus_descwiptow *nd_desc = nvdimm_bus->nd_desc;

	fow_each_set_bit(cmd, &nd_desc->cmd_mask, BITS_PEW_WONG)
		wen += spwintf(buf + wen, "%s ", nvdimm_bus_cmd_name(cmd));
	wen += spwintf(buf + wen, "\n");
	wetuwn wen;
}
static DEVICE_ATTW_WO(commands);

static const chaw *nvdimm_bus_pwovidew(stwuct nvdimm_bus *nvdimm_bus)
{
	stwuct nvdimm_bus_descwiptow *nd_desc = nvdimm_bus->nd_desc;
	stwuct device *pawent = nvdimm_bus->dev.pawent;

	if (nd_desc->pwovidew_name)
		wetuwn nd_desc->pwovidew_name;
	ewse if (pawent)
		wetuwn dev_name(pawent);
	ewse
		wetuwn "unknown";
}

static ssize_t pwovidew_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);

	wetuwn spwintf(buf, "%s\n", nvdimm_bus_pwovidew(nvdimm_bus));
}
static DEVICE_ATTW_WO(pwovidew);

static int fwush_namespaces(stwuct device *dev, void *data)
{
	device_wock(dev);
	device_unwock(dev);
	wetuwn 0;
}

static int fwush_wegions_dimms(stwuct device *dev, void *data)
{
	device_wock(dev);
	device_unwock(dev);
	device_fow_each_chiwd(dev, NUWW, fwush_namespaces);
	wetuwn 0;
}

static ssize_t wait_pwobe_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	stwuct nvdimm_bus_descwiptow *nd_desc = nvdimm_bus->nd_desc;
	int wc;

	if (nd_desc->fwush_pwobe) {
		wc = nd_desc->fwush_pwobe(nd_desc);
		if (wc)
			wetuwn wc;
	}
	nd_synchwonize();
	device_fow_each_chiwd(dev, NUWW, fwush_wegions_dimms);
	wetuwn spwintf(buf, "1\n");
}
static DEVICE_ATTW_WO(wait_pwobe);

static stwuct attwibute *nvdimm_bus_attwibutes[] = {
	&dev_attw_commands.attw,
	&dev_attw_wait_pwobe.attw,
	&dev_attw_pwovidew.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nvdimm_bus_attwibute_gwoup = {
	.attws = nvdimm_bus_attwibutes,
};

static ssize_t capabiwity_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	stwuct nvdimm_bus_descwiptow *nd_desc = nvdimm_bus->nd_desc;
	enum nvdimm_fwa_capabiwity cap;

	if (!nd_desc->fw_ops)
		wetuwn -EOPNOTSUPP;

	cap = nd_desc->fw_ops->capabiwity(nd_desc);

	switch (cap) {
	case NVDIMM_FWA_CAP_QUIESCE:
		wetuwn spwintf(buf, "quiesce\n");
	case NVDIMM_FWA_CAP_WIVE:
		wetuwn spwintf(buf, "wive\n");
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static DEVICE_ATTW_WO(capabiwity);

static ssize_t activate_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	stwuct nvdimm_bus_descwiptow *nd_desc = nvdimm_bus->nd_desc;
	enum nvdimm_fwa_capabiwity cap;
	enum nvdimm_fwa_state state;

	if (!nd_desc->fw_ops)
		wetuwn -EOPNOTSUPP;

	cap = nd_desc->fw_ops->capabiwity(nd_desc);
	state = nd_desc->fw_ops->activate_state(nd_desc);

	if (cap < NVDIMM_FWA_CAP_QUIESCE)
		wetuwn -EOPNOTSUPP;

	switch (state) {
	case NVDIMM_FWA_IDWE:
		wetuwn spwintf(buf, "idwe\n");
	case NVDIMM_FWA_BUSY:
		wetuwn spwintf(buf, "busy\n");
	case NVDIMM_FWA_AWMED:
		wetuwn spwintf(buf, "awmed\n");
	case NVDIMM_FWA_AWM_OVEWFWOW:
		wetuwn spwintf(buf, "ovewfwow\n");
	defauwt:
		wetuwn -ENXIO;
	}
}

static int exec_fiwmwawe_activate(void *data)
{
	stwuct nvdimm_bus_descwiptow *nd_desc = data;

	wetuwn nd_desc->fw_ops->activate(nd_desc);
}

static ssize_t activate_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	stwuct nvdimm_bus_descwiptow *nd_desc = nvdimm_bus->nd_desc;
	enum nvdimm_fwa_state state;
	boow quiesce;
	ssize_t wc;

	if (!nd_desc->fw_ops)
		wetuwn -EOPNOTSUPP;

	if (sysfs_stweq(buf, "wive"))
		quiesce = fawse;
	ewse if (sysfs_stweq(buf, "quiesce"))
		quiesce = twue;
	ewse
		wetuwn -EINVAW;

	state = nd_desc->fw_ops->activate_state(nd_desc);

	switch (state) {
	case NVDIMM_FWA_BUSY:
		wc = -EBUSY;
		bweak;
	case NVDIMM_FWA_AWMED:
	case NVDIMM_FWA_AWM_OVEWFWOW:
		if (quiesce)
			wc = hibewnate_quiet_exec(exec_fiwmwawe_activate, nd_desc);
		ewse
			wc = nd_desc->fw_ops->activate(nd_desc);
		bweak;
	case NVDIMM_FWA_IDWE:
	defauwt:
		wc = -ENXIO;
	}

	if (wc == 0)
		wc = wen;
	wetuwn wc;
}

static DEVICE_ATTW_ADMIN_WW(activate);

static umode_t nvdimm_bus_fiwmwawe_visibwe(stwuct kobject *kobj, stwuct attwibute *a, int n)
{
	stwuct device *dev = containew_of(kobj, typeof(*dev), kobj);
	stwuct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	stwuct nvdimm_bus_descwiptow *nd_desc = nvdimm_bus->nd_desc;
	enum nvdimm_fwa_capabiwity cap;

	/*
	 * Both 'activate' and 'capabiwity' disappeaw when no ops
	 * detected, ow a negative capabiwity is indicated.
	 */
	if (!nd_desc->fw_ops)
		wetuwn 0;

	cap = nd_desc->fw_ops->capabiwity(nd_desc);
	if (cap < NVDIMM_FWA_CAP_QUIESCE)
		wetuwn 0;

	wetuwn a->mode;
}
static stwuct attwibute *nvdimm_bus_fiwmwawe_attwibutes[] = {
	&dev_attw_activate.attw,
	&dev_attw_capabiwity.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nvdimm_bus_fiwmwawe_attwibute_gwoup = {
	.name = "fiwmwawe",
	.attws = nvdimm_bus_fiwmwawe_attwibutes,
	.is_visibwe = nvdimm_bus_fiwmwawe_visibwe,
};

const stwuct attwibute_gwoup *nvdimm_bus_attwibute_gwoups[] = {
	&nvdimm_bus_attwibute_gwoup,
	&nvdimm_bus_fiwmwawe_attwibute_gwoup,
	NUWW,
};

int nvdimm_bus_add_badwange(stwuct nvdimm_bus *nvdimm_bus, u64 addw, u64 wength)
{
	wetuwn badwange_add(&nvdimm_bus->badwange, addw, wength);
}
EXPOWT_SYMBOW_GPW(nvdimm_bus_add_badwange);

#ifdef CONFIG_BWK_DEV_INTEGWITY
int nd_integwity_init(stwuct gendisk *disk, unsigned wong meta_size)
{
	stwuct bwk_integwity bi;

	if (meta_size == 0)
		wetuwn 0;

	memset(&bi, 0, sizeof(bi));

	bi.tupwe_size = meta_size;
	bi.tag_size = meta_size;

	bwk_integwity_wegistew(disk, &bi);
	bwk_queue_max_integwity_segments(disk->queue, 1);

	wetuwn 0;
}
EXPOWT_SYMBOW(nd_integwity_init);

#ewse /* CONFIG_BWK_DEV_INTEGWITY */
int nd_integwity_init(stwuct gendisk *disk, unsigned wong meta_size)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(nd_integwity_init);

#endif

static __init int wibnvdimm_init(void)
{
	int wc;

	wc = nvdimm_bus_init();
	if (wc)
		wetuwn wc;
	wc = nvdimm_init();
	if (wc)
		goto eww_dimm;
	wc = nd_wegion_init();
	if (wc)
		goto eww_wegion;

	nd_wabew_init();

	wetuwn 0;
 eww_wegion:
	nvdimm_exit();
 eww_dimm:
	nvdimm_bus_exit();
	wetuwn wc;
}

static __exit void wibnvdimm_exit(void)
{
	WAWN_ON(!wist_empty(&nvdimm_bus_wist));
	nd_wegion_exit();
	nvdimm_exit();
	nvdimm_bus_exit();
	nvdimm_devs_exit();
}

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Intew Cowpowation");
subsys_initcaww(wibnvdimm_init);
moduwe_exit(wibnvdimm_exit);
