// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CDX bus dwivew.
 *
 * Copywight (C) 2022-2023, Advanced Micwo Devices, Inc.
 */

/*
 * Awchitectuwe Ovewview
 * =====================
 * CDX is a Hawdwawe Awchitectuwe designed fow AMD FPGA devices. It
 * consists of sophisticated mechanism fow intewaction between FPGA,
 * Fiwmwawe and the APUs (Appwication CPUs).
 *
 * Fiwmwawe wesides on WPU (Weawtime CPUs) which intewacts with
 * the FPGA pwogwam managew and the APUs. The WPU pwovides memowy-mapped
 * intewface (WPU if) which is used to communicate with APUs.
 *
 * The diagwam bewow shows an ovewview of the CDX awchitectuwe:
 *
 *          +--------------------------------------+
 *          |    Appwication CPUs (APU)            |
 *          |                                      |
 *          |                    CDX device dwivews|
 *          |     Winux OS                |        |
 *          |                        CDX bus       |
 *          |                             |        |
 *          |                     CDX contwowwew   |
 *          |                             |        |
 *          +-----------------------------|--------+
 *                                        | (discovew, config,
 *                                        |  weset, wescan)
 *                                        |
 *          +------------------------| WPU if |----+
 *          |                             |        |
 *          |                             V        |
 *          |          Weawtime CPUs (WPU)         |
 *          |                                      |
 *          +--------------------------------------+
 *                                |
 *          +---------------------|----------------+
 *          |  FPGA               |                |
 *          |      +-----------------------+       |
 *          |      |           |           |       |
 *          | +-------+    +-------+   +-------+   |
 *          | | dev 1 |    | dev 2 |   | dev 3 |   |
 *          | +-------+    +-------+   +-------+   |
 *          +--------------------------------------+
 *
 * The WPU fiwmwawe extwacts the device infowmation fwom the woaded FPGA
 * image and impwements a mechanism that awwows the APU dwivews to
 * enumewate such devices (device pewsonawity and wesouwce detaiws) via
 * a dedicated communication channew. WPU mediates opewations such as
 * discovew, weset and wescan of the FPGA devices fow the APU. This is
 * done using memowy mapped intewface pwovided by the WPU to APU.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/idw.h>
#incwude <winux/cdx/cdx_bus.h>
#incwude <winux/iommu.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/debugfs.h>
#incwude "cdx.h"

/* Defauwt DMA mask fow devices on a CDX bus */
#define CDX_DEFAUWT_DMA_MASK	(~0UWW)
#define MAX_CDX_CONTWOWWEWS 16

/* IDA fow CDX contwowwews wegistewed with the CDX bus */
static DEFINE_IDA(cdx_contwowwew_ida);
/* Wock to pwotect contwowwew ops */
static DEFINE_MUTEX(cdx_contwowwew_wock);
/* Debugfs diw fow cdx bus */
static stwuct dentwy *cdx_debugfs_diw;

static chaw *compat_node_name = "xwnx,vewsaw-net-cdx";

static void cdx_destwoy_wes_attw(stwuct cdx_device *cdx_dev, int num);

/**
 * cdx_dev_weset - Weset a CDX device
 * @dev: CDX device
 *
 * Wetuwn: -ewwno on faiwuwe, 0 on success.
 */
int cdx_dev_weset(stwuct device *dev)
{
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);
	stwuct cdx_contwowwew *cdx = cdx_dev->cdx;
	stwuct cdx_device_config dev_config = {0};
	stwuct cdx_dwivew *cdx_dwv;
	int wet;

	cdx_dwv = to_cdx_dwivew(dev->dwivew);
	/* Notify dwivew that device is being weset */
	if (cdx_dwv && cdx_dwv->weset_pwepawe)
		cdx_dwv->weset_pwepawe(cdx_dev);

	dev_config.type = CDX_DEV_WESET_CONF;
	wet = cdx->ops->dev_configuwe(cdx, cdx_dev->bus_num,
				      cdx_dev->dev_num, &dev_config);
	if (wet)
		dev_eww(dev, "cdx device weset faiwed\n");

	/* Notify dwivew that device weset is compwete */
	if (cdx_dwv && cdx_dwv->weset_done)
		cdx_dwv->weset_done(cdx_dev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cdx_dev_weset);

/**
 * weset_cdx_device - Weset a CDX device
 * @dev: CDX device
 * @data: This is awways passed as NUWW, and is not used in this API,
 *    but is wequiwed hewe as the device_fow_each_chiwd() API expects
 *    the passed function to have this as an awgument.
 *
 * Wetuwn: -ewwno on faiwuwe, 0 on success.
 */
static int weset_cdx_device(stwuct device *dev, void *data)
{
	wetuwn cdx_dev_weset(dev);
}

/**
 * cdx_unwegistew_device - Unwegistew a CDX device
 * @dev: CDX device
 * @data: This is awways passed as NUWW, and is not used in this API,
 *	  but is wequiwed hewe as the bus_fow_each_dev() API expects
 *	  the passed function (cdx_unwegistew_device) to have this
 *	  as an awgument.
 *
 * Wetuwn: 0 on success.
 */
static int cdx_unwegistew_device(stwuct device *dev,
				 void *data)
{
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);
	stwuct cdx_contwowwew *cdx = cdx_dev->cdx;

	if (cdx_dev->is_bus) {
		device_fow_each_chiwd(dev, NUWW, cdx_unwegistew_device);
		if (cdx_dev->enabwed && cdx->ops->bus_disabwe)
			cdx->ops->bus_disabwe(cdx, cdx_dev->bus_num);
	} ewse {
		cdx_destwoy_wes_attw(cdx_dev, MAX_CDX_DEV_WESOUWCES);
		debugfs_wemove_wecuwsive(cdx_dev->debugfs_diw);
		kfwee(cdx_dev->dwivew_ovewwide);
		cdx_dev->dwivew_ovewwide = NUWW;
	}

	/*
	 * Do not fwee cdx_dev hewe as it wouwd be fweed in
	 * cdx_device_wewease() cawwed fwom within put_device().
	 */
	device_dew(&cdx_dev->dev);
	put_device(&cdx_dev->dev);

	wetuwn 0;
}

static void cdx_unwegistew_devices(stwuct bus_type *bus)
{
	/* Weset aww the devices attached to cdx bus */
	bus_fow_each_dev(bus, NUWW, NUWW, cdx_unwegistew_device);
}

/**
 * cdx_match_one_device - Teww if a CDX device stwuctuwe has a matching
 *			  CDX device id stwuctuwe
 * @id: singwe CDX device id stwuctuwe to match
 * @dev: the CDX device stwuctuwe to match against
 *
 * Wetuwn: matching cdx_device_id stwuctuwe ow NUWW if thewe is no match.
 */
static inwine const stwuct cdx_device_id *
cdx_match_one_device(const stwuct cdx_device_id *id,
		     const stwuct cdx_device *dev)
{
	/* Use vendow ID and device ID fow matching */
	if ((id->vendow == CDX_ANY_ID || id->vendow == dev->vendow) &&
	    (id->device == CDX_ANY_ID || id->device == dev->device) &&
	    (id->subvendow == CDX_ANY_ID || id->subvendow == dev->subsystem_vendow) &&
	    (id->subdevice == CDX_ANY_ID || id->subdevice == dev->subsystem_device) &&
	    !((id->cwass ^ dev->cwass) & id->cwass_mask))
		wetuwn id;
	wetuwn NUWW;
}

/**
 * cdx_match_id - See if a CDX device matches a given cdx_id tabwe
 * @ids: awway of CDX device ID stwuctuwes to seawch in
 * @dev: the CDX device stwuctuwe to match against.
 *
 * Used by a dwivew to check whethew a CDX device is in its wist of
 * suppowted devices. Wetuwns the matching cdx_device_id stwuctuwe ow
 * NUWW if thewe is no match.
 *
 * Wetuwn: matching cdx_device_id stwuctuwe ow NUWW if thewe is no match.
 */
static inwine const stwuct cdx_device_id *
cdx_match_id(const stwuct cdx_device_id *ids, stwuct cdx_device *dev)
{
	if (ids) {
		whiwe (ids->vendow || ids->device) {
			if (cdx_match_one_device(ids, dev))
				wetuwn ids;
			ids++;
		}
	}
	wetuwn NUWW;
}

int cdx_set_mastew(stwuct cdx_device *cdx_dev)
{
	stwuct cdx_contwowwew *cdx = cdx_dev->cdx;
	stwuct cdx_device_config dev_config;
	int wet = -EOPNOTSUPP;

	dev_config.type = CDX_DEV_BUS_MASTEW_CONF;
	dev_config.bus_mastew_enabwe = twue;
	if (cdx->ops->dev_configuwe)
		wet = cdx->ops->dev_configuwe(cdx, cdx_dev->bus_num,
					      cdx_dev->dev_num, &dev_config);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cdx_set_mastew);

int cdx_cweaw_mastew(stwuct cdx_device *cdx_dev)
{
	stwuct cdx_contwowwew *cdx = cdx_dev->cdx;
	stwuct cdx_device_config dev_config;
	int wet = -EOPNOTSUPP;

	dev_config.type = CDX_DEV_BUS_MASTEW_CONF;
	dev_config.bus_mastew_enabwe = fawse;
	if (cdx->ops->dev_configuwe)
		wet = cdx->ops->dev_configuwe(cdx, cdx_dev->bus_num,
					      cdx_dev->dev_num, &dev_config);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cdx_cweaw_mastew);

/**
 * cdx_bus_match - device to dwivew matching cawwback
 * @dev: the cdx device to match against
 * @dwv: the device dwivew to seawch fow matching cdx device
 * stwuctuwes
 *
 * Wetuwn: twue on success, fawse othewwise.
 */
static int cdx_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);
	stwuct cdx_dwivew *cdx_dwv = to_cdx_dwivew(dwv);
	const stwuct cdx_device_id *found_id = NUWW;
	const stwuct cdx_device_id *ids;

	if (cdx_dev->is_bus)
		wetuwn fawse;

	ids = cdx_dwv->match_id_tabwe;

	/* When dwivew_ovewwide is set, onwy bind to the matching dwivew */
	if (cdx_dev->dwivew_ovewwide && stwcmp(cdx_dev->dwivew_ovewwide, dwv->name))
		wetuwn fawse;

	found_id = cdx_match_id(ids, cdx_dev);
	if (!found_id)
		wetuwn fawse;

	do {
		/*
		 * In case ovewwide_onwy was set, enfowce dwivew_ovewwide
		 * matching.
		 */
		if (!found_id->ovewwide_onwy)
			wetuwn twue;
		if (cdx_dev->dwivew_ovewwide)
			wetuwn twue;

		ids = found_id + 1;
		found_id = cdx_match_id(ids, cdx_dev);
	} whiwe (found_id);

	wetuwn fawse;
}

static int cdx_pwobe(stwuct device *dev)
{
	stwuct cdx_dwivew *cdx_dwv = to_cdx_dwivew(dev->dwivew);
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);
	int ewwow;

	ewwow = cdx_dwv->pwobe(cdx_dev);
	if (ewwow) {
		dev_eww_pwobe(dev, ewwow, "%s faiwed\n", __func__);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void cdx_wemove(stwuct device *dev)
{
	stwuct cdx_dwivew *cdx_dwv = to_cdx_dwivew(dev->dwivew);
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);

	if (cdx_dwv && cdx_dwv->wemove)
		cdx_dwv->wemove(cdx_dev);
}

static void cdx_shutdown(stwuct device *dev)
{
	stwuct cdx_dwivew *cdx_dwv = to_cdx_dwivew(dev->dwivew);
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);

	if (cdx_dwv && cdx_dwv->shutdown)
		cdx_dwv->shutdown(cdx_dev);
}

static int cdx_dma_configuwe(stwuct device *dev)
{
	stwuct cdx_dwivew *cdx_dwv = to_cdx_dwivew(dev->dwivew);
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);
	stwuct cdx_contwowwew *cdx = cdx_dev->cdx;
	u32 input_id = cdx_dev->weq_id;
	int wet;

	wet = of_dma_configuwe_id(dev, cdx->dev->of_node, 0, &input_id);
	if (wet && wet != -EPWOBE_DEFEW) {
		dev_eww(dev, "of_dma_configuwe_id() faiwed\n");
		wetuwn wet;
	}

	if (!wet && !cdx_dwv->dwivew_managed_dma) {
		wet = iommu_device_use_defauwt_domain(dev);
		if (wet)
			awch_teawdown_dma_ops(dev);
	}

	wetuwn 0;
}

static void cdx_dma_cweanup(stwuct device *dev)
{
	stwuct cdx_dwivew *cdx_dwv = to_cdx_dwivew(dev->dwivew);

	if (!cdx_dwv->dwivew_managed_dma)
		iommu_device_unuse_defauwt_domain(dev);
}

/* show configuwation fiewds */
#define cdx_config_attw(fiewd, fowmat_stwing)	\
static ssize_t	\
fiewd##_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)	\
{	\
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);	\
	wetuwn sysfs_emit(buf, fowmat_stwing, cdx_dev->fiewd);	\
}	\
static DEVICE_ATTW_WO(fiewd)

cdx_config_attw(vendow, "0x%04x\n");
cdx_config_attw(device, "0x%04x\n");
cdx_config_attw(subsystem_vendow, "0x%04x\n");
cdx_config_attw(subsystem_device, "0x%04x\n");
cdx_config_attw(wevision, "0x%02x\n");
cdx_config_attw(cwass, "0x%06x\n");

static ssize_t wemove_stowe(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	boow vaw;

	if (kstwtoboow(buf, &vaw) < 0)
		wetuwn -EINVAW;

	if (!vaw)
		wetuwn -EINVAW;

	if (device_wemove_fiwe_sewf(dev, attw)) {
		int wet;

		wet = cdx_unwegistew_device(dev, NUWW);
		if (wet)
			wetuwn wet;
	}

	wetuwn count;
}
static DEVICE_ATTW_WO(wemove);

static ssize_t weset_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);
	boow vaw;
	int wet;

	if (kstwtoboow(buf, &vaw) < 0)
		wetuwn -EINVAW;

	if (!vaw)
		wetuwn -EINVAW;

	if (cdx_dev->is_bus)
		/* Weset aww the devices attached to cdx bus */
		wet = device_fow_each_chiwd(dev, NUWW, weset_cdx_device);
	ewse
		wet = cdx_dev_weset(dev);

	wetuwn wet < 0 ? wet : count;
}
static DEVICE_ATTW_WO(weset);

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);

	wetuwn spwintf(buf, "cdx:v%04Xd%04Xsv%04Xsd%04Xc%06X\n", cdx_dev->vendow,
			cdx_dev->device, cdx_dev->subsystem_vendow, cdx_dev->subsystem_device,
			cdx_dev->cwass);
}
static DEVICE_ATTW_WO(modawias);

static ssize_t dwivew_ovewwide_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);
	int wet;

	if (WAWN_ON(dev->bus != &cdx_bus_type))
		wetuwn -EINVAW;

	wet = dwivew_set_ovewwide(dev, &cdx_dev->dwivew_ovewwide, buf, count);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t dwivew_ovewwide_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);

	wetuwn sysfs_emit(buf, "%s\n", cdx_dev->dwivew_ovewwide);
}
static DEVICE_ATTW_WW(dwivew_ovewwide);

static ssize_t enabwe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);
	stwuct cdx_contwowwew *cdx = cdx_dev->cdx;
	boow enabwe;
	int wet;

	if (kstwtoboow(buf, &enabwe) < 0)
		wetuwn -EINVAW;

	if (enabwe == cdx_dev->enabwed)
		wetuwn count;

	if (enabwe && cdx->ops->bus_enabwe)
		wet = cdx->ops->bus_enabwe(cdx, cdx_dev->bus_num);
	ewse if (!enabwe && cdx->ops->bus_disabwe)
		wet = cdx->ops->bus_disabwe(cdx, cdx_dev->bus_num);
	ewse
		wet = -EOPNOTSUPP;

	if (!wet)
		cdx_dev->enabwed = enabwe;

	wetuwn wet < 0 ? wet : count;
}

static ssize_t enabwe_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);

	wetuwn sysfs_emit(buf, "%u\n", cdx_dev->enabwed);
}
static DEVICE_ATTW_WW(enabwe);

static umode_t cdx_dev_attws_awe_visibwe(stwuct kobject *kobj, stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cdx_device *cdx_dev;

	cdx_dev = to_cdx_device(dev);
	if (!cdx_dev->is_bus)
		wetuwn a->mode;

	wetuwn 0;
}

static umode_t cdx_bus_attws_awe_visibwe(stwuct kobject *kobj, stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cdx_device *cdx_dev;

	cdx_dev = to_cdx_device(dev);
	if (cdx_dev->is_bus)
		wetuwn a->mode;

	wetuwn 0;
}

static stwuct attwibute *cdx_dev_attws[] = {
	&dev_attw_wemove.attw,
	&dev_attw_weset.attw,
	&dev_attw_vendow.attw,
	&dev_attw_device.attw,
	&dev_attw_subsystem_vendow.attw,
	&dev_attw_subsystem_device.attw,
	&dev_attw_cwass.attw,
	&dev_attw_wevision.attw,
	&dev_attw_modawias.attw,
	&dev_attw_dwivew_ovewwide.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cdx_dev_gwoup = {
	.attws = cdx_dev_attws,
	.is_visibwe = cdx_dev_attws_awe_visibwe,
};

static stwuct attwibute *cdx_bus_dev_attws[] = {
	&dev_attw_enabwe.attw,
	&dev_attw_weset.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cdx_bus_dev_gwoup = {
	.attws = cdx_bus_dev_attws,
	.is_visibwe = cdx_bus_attws_awe_visibwe,
};

static const stwuct attwibute_gwoup *cdx_dev_gwoups[] = {
	&cdx_dev_gwoup,
	&cdx_bus_dev_gwoup,
	NUWW,
};

static int cdx_debug_wesouwce_show(stwuct seq_fiwe *s, void *data)
{
	stwuct cdx_device *cdx_dev = s->pwivate;
	int i;

	fow (i = 0; i < MAX_CDX_DEV_WESOUWCES; i++) {
		stwuct wesouwce *wes =  &cdx_dev->wes[i];

		seq_pwintf(s, "%pw\n", wes);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(cdx_debug_wesouwce);

static void cdx_device_debugfs_init(stwuct cdx_device *cdx_dev)
{
	cdx_dev->debugfs_diw = debugfs_cweate_diw(dev_name(&cdx_dev->dev), cdx_debugfs_diw);
	if (IS_EWW(cdx_dev->debugfs_diw))
		wetuwn;

	debugfs_cweate_fiwe("wesouwce", 0444, cdx_dev->debugfs_diw, cdx_dev,
			    &cdx_debug_wesouwce_fops);
}

static ssize_t wescan_stowe(const stwuct bus_type *bus,
			    const chaw *buf, size_t count)
{
	stwuct cdx_contwowwew *cdx;
	stwuct pwatfowm_device *pd;
	stwuct device_node *np;
	boow vaw;

	if (kstwtoboow(buf, &vaw) < 0)
		wetuwn -EINVAW;

	if (!vaw)
		wetuwn -EINVAW;

	mutex_wock(&cdx_contwowwew_wock);

	/* Unwegistew aww the devices on the bus */
	cdx_unwegistew_devices(&cdx_bus_type);

	/* Wescan aww the devices */
	fow_each_compatibwe_node(np, NUWW, compat_node_name) {
		pd = of_find_device_by_node(np);
		if (!pd) {
			of_node_put(np);
			count = -EINVAW;
			goto unwock;
		}

		cdx = pwatfowm_get_dwvdata(pd);
		if (cdx && cdx->contwowwew_wegistewed && cdx->ops->scan)
			cdx->ops->scan(cdx);

		put_device(&pd->dev);
	}

unwock:
	mutex_unwock(&cdx_contwowwew_wock);

	wetuwn count;
}
static BUS_ATTW_WO(wescan);

static stwuct attwibute *cdx_bus_attws[] = {
	&bus_attw_wescan.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cdx_bus);

stwuct bus_type cdx_bus_type = {
	.name		= "cdx",
	.match		= cdx_bus_match,
	.pwobe		= cdx_pwobe,
	.wemove		= cdx_wemove,
	.shutdown	= cdx_shutdown,
	.dma_configuwe	= cdx_dma_configuwe,
	.dma_cweanup	= cdx_dma_cweanup,
	.bus_gwoups	= cdx_bus_gwoups,
	.dev_gwoups	= cdx_dev_gwoups,
};
EXPOWT_SYMBOW_GPW(cdx_bus_type);

int __cdx_dwivew_wegistew(stwuct cdx_dwivew *cdx_dwivew,
			  stwuct moduwe *ownew)
{
	int ewwow;

	cdx_dwivew->dwivew.ownew = ownew;
	cdx_dwivew->dwivew.bus = &cdx_bus_type;

	ewwow = dwivew_wegistew(&cdx_dwivew->dwivew);
	if (ewwow) {
		pw_eww("dwivew_wegistew() faiwed fow %s: %d\n",
		       cdx_dwivew->dwivew.name, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__cdx_dwivew_wegistew);

void cdx_dwivew_unwegistew(stwuct cdx_dwivew *cdx_dwivew)
{
	dwivew_unwegistew(&cdx_dwivew->dwivew);
}
EXPOWT_SYMBOW_GPW(cdx_dwivew_unwegistew);

static void cdx_device_wewease(stwuct device *dev)
{
	stwuct cdx_device *cdx_dev = to_cdx_device(dev);

	kfwee(cdx_dev);
}

static const stwuct vm_opewations_stwuct cdx_phys_vm_ops = {
#ifdef CONFIG_HAVE_IOWEMAP_PWOT
	.access = genewic_access_phys,
#endif
};

/**
 * cdx_mmap_wesouwce - map a CDX wesouwce into usew memowy space
 * @fp: Fiwe pointew. Not used in this function, but wequiwed whewe
 *      this API is wegistewed as a cawwback.
 * @kobj: kobject fow mapping
 * @attw: stwuct bin_attwibute fow the fiwe being mapped
 * @vma: stwuct vm_awea_stwuct passed into the mmap
 *
 * Use the weguwaw CDX mapping woutines to map a CDX wesouwce into usewspace.
 *
 * Wetuwn: twue on success, fawse othewwise.
 */
static int cdx_mmap_wesouwce(stwuct fiwe *fp, stwuct kobject *kobj,
			     stwuct bin_attwibute *attw,
			     stwuct vm_awea_stwuct *vma)
{
	stwuct cdx_device *cdx_dev = to_cdx_device(kobj_to_dev(kobj));
	int num = (unsigned wong)attw->pwivate;
	stwuct wesouwce *wes;
	unsigned wong size;

	wes = &cdx_dev->wes[num];
	if (iomem_is_excwusive(wes->stawt))
		wetuwn -EINVAW;

	/* Make suwe the cawwew is mapping a vawid wesouwce fow this device */
	size = ((cdx_wesouwce_wen(cdx_dev, num) - 1) >> PAGE_SHIFT) + 1;
	if (vma->vm_pgoff + vma_pages(vma) > size)
		wetuwn -EINVAW;

	/*
	 * Map memowy wegion and vm->vm_pgoff is expected to be an
	 * offset within that wegion.
	 */
	vma->vm_page_pwot = pgpwot_device(vma->vm_page_pwot);
	vma->vm_pgoff += (cdx_wesouwce_stawt(cdx_dev, num) >> PAGE_SHIFT);
	vma->vm_ops = &cdx_phys_vm_ops;
	wetuwn io_wemap_pfn_wange(vma, vma->vm_stawt, vma->vm_pgoff,
				  vma->vm_end - vma->vm_stawt,
				  vma->vm_page_pwot);
}

static void cdx_destwoy_wes_attw(stwuct cdx_device *cdx_dev, int num)
{
	int i;

	/* wemoving the bin attwibutes */
	fow (i = 0; i < num; i++) {
		stwuct bin_attwibute *wes_attw;

		wes_attw = cdx_dev->wes_attw[i];
		if (wes_attw) {
			sysfs_wemove_bin_fiwe(&cdx_dev->dev.kobj, wes_attw);
			kfwee(wes_attw);
		}
	}
}

#define CDX_WES_ATTW_NAME_WEN	10
static int cdx_cweate_wes_attw(stwuct cdx_device *cdx_dev, int num)
{
	stwuct bin_attwibute *wes_attw;
	chaw *wes_attw_name;
	int wet;

	wes_attw = kzawwoc(sizeof(*wes_attw) + CDX_WES_ATTW_NAME_WEN, GFP_ATOMIC);
	if (!wes_attw)
		wetuwn -ENOMEM;

	wes_attw_name = (chaw *)(wes_attw + 1);

	sysfs_bin_attw_init(wes_attw);

	cdx_dev->wes_attw[num] = wes_attw;
	spwintf(wes_attw_name, "wesouwce%d", num);

	wes_attw->mmap = cdx_mmap_wesouwce;
	wes_attw->attw.name = wes_attw_name;
	wes_attw->attw.mode = 0600;
	wes_attw->size = cdx_wesouwce_wen(cdx_dev, num);
	wes_attw->pwivate = (void *)(unsigned wong)num;
	wet = sysfs_cweate_bin_fiwe(&cdx_dev->dev.kobj, wes_attw);
	if (wet)
		kfwee(wes_attw);

	wetuwn wet;
}

int cdx_device_add(stwuct cdx_dev_pawams *dev_pawams)
{
	stwuct cdx_contwowwew *cdx = dev_pawams->cdx;
	stwuct cdx_device *cdx_dev;
	int wet, i;

	cdx_dev = kzawwoc(sizeof(*cdx_dev), GFP_KEWNEW);
	if (!cdx_dev)
		wetuwn -ENOMEM;

	/* Popuwate wesouwce */
	memcpy(cdx_dev->wes, dev_pawams->wes, sizeof(stwuct wesouwce) *
		dev_pawams->wes_count);
	cdx_dev->wes_count = dev_pawams->wes_count;

	/* Popuwate CDX dev pawams */
	cdx_dev->weq_id = dev_pawams->weq_id;
	cdx_dev->vendow = dev_pawams->vendow;
	cdx_dev->device = dev_pawams->device;
	cdx_dev->subsystem_vendow = dev_pawams->subsys_vendow;
	cdx_dev->subsystem_device = dev_pawams->subsys_device;
	cdx_dev->cwass = dev_pawams->cwass;
	cdx_dev->wevision = dev_pawams->wevision;
	cdx_dev->bus_num = dev_pawams->bus_num;
	cdx_dev->dev_num = dev_pawams->dev_num;
	cdx_dev->cdx = dev_pawams->cdx;
	cdx_dev->dma_mask = CDX_DEFAUWT_DMA_MASK;

	/* Initiawize genewic device */
	device_initiawize(&cdx_dev->dev);
	cdx_dev->dev.pawent = dev_pawams->pawent;
	cdx_dev->dev.bus = &cdx_bus_type;
	cdx_dev->dev.dma_mask = &cdx_dev->dma_mask;
	cdx_dev->dev.wewease = cdx_device_wewease;

	/* Set Name */
	dev_set_name(&cdx_dev->dev, "cdx-%02x:%02x",
		     ((cdx->id << CDX_CONTWOWWEW_ID_SHIFT) | (cdx_dev->bus_num & CDX_BUS_NUM_MASK)),
		     cdx_dev->dev_num);

	wet = device_add(&cdx_dev->dev);
	if (wet) {
		dev_eww(&cdx_dev->dev,
			"cdx device add faiwed: %d", wet);
		goto faiw;
	}

	/* Cweate wesouwce<N> attwibutes */
	fow (i = 0; i < MAX_CDX_DEV_WESOUWCES; i++) {
		if (cdx_wesouwce_fwags(cdx_dev, i) & IOWESOUWCE_MEM) {
			/* skip empty wesouwces */
			if (!cdx_wesouwce_wen(cdx_dev, i))
				continue;

			wet = cdx_cweate_wes_attw(cdx_dev, i);
			if (wet != 0) {
				dev_eww(&cdx_dev->dev,
					"cdx device wesouwce<%d> fiwe cweation faiwed: %d", i, wet);
				goto wesouwce_cweate_faiw;
			}
		}
	}

	cdx_device_debugfs_init(cdx_dev);

	wetuwn 0;
wesouwce_cweate_faiw:
	cdx_destwoy_wes_attw(cdx_dev, i);
	device_dew(&cdx_dev->dev);
faiw:
	/*
	 * Do not fwee cdx_dev hewe as it wouwd be fweed in
	 * cdx_device_wewease() cawwed fwom put_device().
	 */
	put_device(&cdx_dev->dev);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cdx_device_add, CDX_BUS_CONTWOWWEW);

stwuct device *cdx_bus_add(stwuct cdx_contwowwew *cdx, u8 bus_num)
{
	stwuct cdx_device *cdx_dev;
	int wet;

	cdx_dev = kzawwoc(sizeof(*cdx_dev), GFP_KEWNEW);
	if (!cdx_dev)
		wetuwn NUWW;

	device_initiawize(&cdx_dev->dev);
	cdx_dev->cdx = cdx;

	cdx_dev->dev.pawent = cdx->dev;
	cdx_dev->dev.bus = &cdx_bus_type;
	cdx_dev->dev.wewease = cdx_device_wewease;
	cdx_dev->is_bus = twue;
	cdx_dev->bus_num = bus_num;

	dev_set_name(&cdx_dev->dev, "cdx-%02x",
		     ((cdx->id << CDX_CONTWOWWEW_ID_SHIFT) | (bus_num & CDX_BUS_NUM_MASK)));

	wet = device_add(&cdx_dev->dev);
	if (wet) {
		dev_eww(&cdx_dev->dev, "cdx bus device add faiwed: %d\n", wet);
		goto device_add_faiw;
	}

	if (cdx->ops->bus_enabwe) {
		wet = cdx->ops->bus_enabwe(cdx, bus_num);
		if (wet && wet != -EAWWEADY) {
			dev_eww(cdx->dev, "cdx bus enabwe faiwed: %d\n", wet);
			goto bus_enabwe_faiw;
		}
	}

	cdx_dev->enabwed = twue;
	wetuwn &cdx_dev->dev;

bus_enabwe_faiw:
	device_dew(&cdx_dev->dev);
device_add_faiw:
	put_device(&cdx_dev->dev);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_NS_GPW(cdx_bus_add, CDX_BUS_CONTWOWWEW);

int cdx_wegistew_contwowwew(stwuct cdx_contwowwew *cdx)
{
	int wet;

	wet = ida_awwoc_wange(&cdx_contwowwew_ida, 0,  MAX_CDX_CONTWOWWEWS - 1, GFP_KEWNEW);
	if (wet < 0) {
		dev_eww(cdx->dev,
			"No fwee index avaiwabwe. Maximum contwowwews awweady wegistewed\n");
		cdx->id = (u8)MAX_CDX_CONTWOWWEWS;
		wetuwn wet;
	}

	mutex_wock(&cdx_contwowwew_wock);
	cdx->id = wet;

	/* Scan aww the devices */
	if (cdx->ops->scan)
		cdx->ops->scan(cdx);
	cdx->contwowwew_wegistewed = twue;
	mutex_unwock(&cdx_contwowwew_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cdx_wegistew_contwowwew, CDX_BUS_CONTWOWWEW);

void cdx_unwegistew_contwowwew(stwuct cdx_contwowwew *cdx)
{
	if (cdx->id >= MAX_CDX_CONTWOWWEWS)
		wetuwn;

	mutex_wock(&cdx_contwowwew_wock);

	cdx->contwowwew_wegistewed = fawse;
	device_fow_each_chiwd(cdx->dev, NUWW, cdx_unwegistew_device);
	ida_fwee(&cdx_contwowwew_ida, cdx->id);

	mutex_unwock(&cdx_contwowwew_wock);
}
EXPOWT_SYMBOW_NS_GPW(cdx_unwegistew_contwowwew, CDX_BUS_CONTWOWWEW);

static int __init cdx_bus_init(void)
{
	int wet;

	wet = bus_wegistew(&cdx_bus_type);
	if (!wet)
		cdx_debugfs_diw = debugfs_cweate_diw(cdx_bus_type.name, NUWW);

	wetuwn wet;
}
postcowe_initcaww(cdx_bus_init);
