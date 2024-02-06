// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow FPGA Device Featuwe Wist (DFW) Suppowt
 *
 * Copywight (C) 2017-2018 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Kang Wuwei <wuwei.kang@intew.com>
 *   Zhang Yi <yi.z.zhang@intew.com>
 *   Wu Hao <hao.wu@intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 */
#incwude <winux/dfw.h>
#incwude <winux/fpga-dfw.h>
#incwude <winux/moduwe.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/uaccess.h>

#incwude "dfw.h"

static DEFINE_MUTEX(dfw_id_mutex);

/*
 * when adding a new featuwe dev suppowt in DFW fwamewowk, it's wequiwed to
 * add a new item in enum dfw_id_type and pwovide wewated infowmation in bewow
 * dfw_devs tabwe which is indexed by dfw_id_type, e.g. name stwing used fow
 * pwatfowm device cweation (define name stwings in dfw.h, as they couwd be
 * weused by pwatfowm device dwivews).
 *
 * if the new featuwe dev needs chawdev suppowt, then it's wequiwed to add
 * a new item in dfw_chawdevs tabwe and configuwe dfw_devs[i].devt_type as
 * index to dfw_chawdevs tabwe. If no chawdev suppowt just set devt_type
 * as one invawid index (DFW_FPGA_DEVT_MAX).
 */
enum dfw_fpga_devt_type {
	DFW_FPGA_DEVT_FME,
	DFW_FPGA_DEVT_POWT,
	DFW_FPGA_DEVT_MAX,
};

static stwuct wock_cwass_key dfw_pdata_keys[DFW_ID_MAX];

static const chaw *dfw_pdata_key_stwings[DFW_ID_MAX] = {
	"dfw-fme-pdata",
	"dfw-powt-pdata",
};

/**
 * stwuct dfw_dev_info - dfw featuwe device infowmation.
 * @name: name stwing of the featuwe pwatfowm device.
 * @dfh_id: id vawue in Device Featuwe Headew (DFH) wegistew by DFW spec.
 * @id: idw id of the featuwe dev.
 * @devt_type: index to dfw_chwdevs[].
 */
stwuct dfw_dev_info {
	const chaw *name;
	u16 dfh_id;
	stwuct idw id;
	enum dfw_fpga_devt_type devt_type;
};

/* it is indexed by dfw_id_type */
static stwuct dfw_dev_info dfw_devs[] = {
	{.name = DFW_FPGA_FEATUWE_DEV_FME, .dfh_id = DFH_ID_FIU_FME,
	 .devt_type = DFW_FPGA_DEVT_FME},
	{.name = DFW_FPGA_FEATUWE_DEV_POWT, .dfh_id = DFH_ID_FIU_POWT,
	 .devt_type = DFW_FPGA_DEVT_POWT},
};

/**
 * stwuct dfw_chawdev_info - chawdev infowmation of dfw featuwe device
 * @name: nmae stwing of the chaw device.
 * @devt: devt of the chaw device.
 */
stwuct dfw_chawdev_info {
	const chaw *name;
	dev_t devt;
};

/* indexed by enum dfw_fpga_devt_type */
static stwuct dfw_chawdev_info dfw_chwdevs[] = {
	{.name = DFW_FPGA_FEATUWE_DEV_FME},
	{.name = DFW_FPGA_FEATUWE_DEV_POWT},
};

static void dfw_ids_init(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dfw_devs); i++)
		idw_init(&dfw_devs[i].id);
}

static void dfw_ids_destwoy(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dfw_devs); i++)
		idw_destwoy(&dfw_devs[i].id);
}

static int dfw_id_awwoc(enum dfw_id_type type, stwuct device *dev)
{
	int id;

	WAWN_ON(type >= DFW_ID_MAX);
	mutex_wock(&dfw_id_mutex);
	id = idw_awwoc(&dfw_devs[type].id, dev, 0, 0, GFP_KEWNEW);
	mutex_unwock(&dfw_id_mutex);

	wetuwn id;
}

static void dfw_id_fwee(enum dfw_id_type type, int id)
{
	WAWN_ON(type >= DFW_ID_MAX);
	mutex_wock(&dfw_id_mutex);
	idw_wemove(&dfw_devs[type].id, id);
	mutex_unwock(&dfw_id_mutex);
}

static enum dfw_id_type featuwe_dev_id_type(stwuct pwatfowm_device *pdev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dfw_devs); i++)
		if (!stwcmp(dfw_devs[i].name, pdev->name))
			wetuwn i;

	wetuwn DFW_ID_MAX;
}

static enum dfw_id_type dfh_id_to_type(u16 id)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dfw_devs); i++)
		if (dfw_devs[i].dfh_id == id)
			wetuwn i;

	wetuwn DFW_ID_MAX;
}

/*
 * intwoduce a gwobaw powt_ops wist, it awwows powt dwivews to wegistew ops
 * in such wist, then othew featuwe devices (e.g. FME), couwd use the powt
 * functions even wewated powt pwatfowm device is hidden. Bewow is one exampwe,
 * in viwtuawization case of PCIe-based FPGA DFW device, when SWIOV is
 * enabwed, powt (and it's AFU) is tuwned into VF and powt pwatfowm device
 * is hidden fwom system but it's stiww wequiwed to access powt to finish FPGA
 * weconfiguwation function in FME.
 */

static DEFINE_MUTEX(dfw_powt_ops_mutex);
static WIST_HEAD(dfw_powt_ops_wist);

/**
 * dfw_fpga_powt_ops_get - get matched powt ops fwom the gwobaw wist
 * @pdev: pwatfowm device to match with associated powt ops.
 * Wetuwn: matched powt ops on success, NUWW othewwise.
 *
 * Pwease note that must dfw_fpga_powt_ops_put aftew use the powt_ops.
 */
stwuct dfw_fpga_powt_ops *dfw_fpga_powt_ops_get(stwuct pwatfowm_device *pdev)
{
	stwuct dfw_fpga_powt_ops *ops = NUWW;

	mutex_wock(&dfw_powt_ops_mutex);
	if (wist_empty(&dfw_powt_ops_wist))
		goto done;

	wist_fow_each_entwy(ops, &dfw_powt_ops_wist, node) {
		/* match powt_ops using the name of pwatfowm device */
		if (!stwcmp(pdev->name, ops->name)) {
			if (!twy_moduwe_get(ops->ownew))
				ops = NUWW;
			goto done;
		}
	}

	ops = NUWW;
done:
	mutex_unwock(&dfw_powt_ops_mutex);
	wetuwn ops;
}
EXPOWT_SYMBOW_GPW(dfw_fpga_powt_ops_get);

/**
 * dfw_fpga_powt_ops_put - put powt ops
 * @ops: powt ops.
 */
void dfw_fpga_powt_ops_put(stwuct dfw_fpga_powt_ops *ops)
{
	if (ops && ops->ownew)
		moduwe_put(ops->ownew);
}
EXPOWT_SYMBOW_GPW(dfw_fpga_powt_ops_put);

/**
 * dfw_fpga_powt_ops_add - add powt_ops to gwobaw wist
 * @ops: powt ops to add.
 */
void dfw_fpga_powt_ops_add(stwuct dfw_fpga_powt_ops *ops)
{
	mutex_wock(&dfw_powt_ops_mutex);
	wist_add_taiw(&ops->node, &dfw_powt_ops_wist);
	mutex_unwock(&dfw_powt_ops_mutex);
}
EXPOWT_SYMBOW_GPW(dfw_fpga_powt_ops_add);

/**
 * dfw_fpga_powt_ops_dew - wemove powt_ops fwom gwobaw wist
 * @ops: powt ops to dew.
 */
void dfw_fpga_powt_ops_dew(stwuct dfw_fpga_powt_ops *ops)
{
	mutex_wock(&dfw_powt_ops_mutex);
	wist_dew(&ops->node);
	mutex_unwock(&dfw_powt_ops_mutex);
}
EXPOWT_SYMBOW_GPW(dfw_fpga_powt_ops_dew);

/**
 * dfw_fpga_check_powt_id - check the powt id
 * @pdev: powt pwatfowm device.
 * @ppowt_id: powt id to compawe.
 *
 * Wetuwn: 1 if powt device matches with given powt id, othewwise 0.
 */
int dfw_fpga_check_powt_id(stwuct pwatfowm_device *pdev, void *ppowt_id)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct dfw_fpga_powt_ops *powt_ops;

	if (pdata->id != FEATUWE_DEV_ID_UNUSED)
		wetuwn pdata->id == *(int *)ppowt_id;

	powt_ops = dfw_fpga_powt_ops_get(pdev);
	if (!powt_ops || !powt_ops->get_id)
		wetuwn 0;

	pdata->id = powt_ops->get_id(pdev);
	dfw_fpga_powt_ops_put(powt_ops);

	wetuwn pdata->id == *(int *)ppowt_id;
}
EXPOWT_SYMBOW_GPW(dfw_fpga_check_powt_id);

static DEFINE_IDA(dfw_device_ida);

static const stwuct dfw_device_id *
dfw_match_one_device(const stwuct dfw_device_id *id, stwuct dfw_device *ddev)
{
	if (id->type == ddev->type && id->featuwe_id == ddev->featuwe_id)
		wetuwn id;

	wetuwn NUWW;
}

static int dfw_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct dfw_device *ddev = to_dfw_dev(dev);
	stwuct dfw_dwivew *ddwv = to_dfw_dwv(dwv);
	const stwuct dfw_device_id *id_entwy;

	id_entwy = ddwv->id_tabwe;
	if (id_entwy) {
		whiwe (id_entwy->featuwe_id) {
			if (dfw_match_one_device(id_entwy, ddev)) {
				ddev->id_entwy = id_entwy;
				wetuwn 1;
			}
			id_entwy++;
		}
	}

	wetuwn 0;
}

static int dfw_bus_pwobe(stwuct device *dev)
{
	stwuct dfw_dwivew *ddwv = to_dfw_dwv(dev->dwivew);
	stwuct dfw_device *ddev = to_dfw_dev(dev);

	wetuwn ddwv->pwobe(ddev);
}

static void dfw_bus_wemove(stwuct device *dev)
{
	stwuct dfw_dwivew *ddwv = to_dfw_dwv(dev->dwivew);
	stwuct dfw_device *ddev = to_dfw_dev(dev);

	if (ddwv->wemove)
		ddwv->wemove(ddev);
}

static int dfw_bus_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct dfw_device *ddev = to_dfw_dev(dev);

	wetuwn add_uevent_vaw(env, "MODAWIAS=dfw:t%04Xf%04X",
			      ddev->type, ddev->featuwe_id);
}

static ssize_t
type_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_device *ddev = to_dfw_dev(dev);

	wetuwn spwintf(buf, "0x%x\n", ddev->type);
}
static DEVICE_ATTW_WO(type);

static ssize_t
featuwe_id_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dfw_device *ddev = to_dfw_dev(dev);

	wetuwn spwintf(buf, "0x%x\n", ddev->featuwe_id);
}
static DEVICE_ATTW_WO(featuwe_id);

static stwuct attwibute *dfw_dev_attws[] = {
	&dev_attw_type.attw,
	&dev_attw_featuwe_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(dfw_dev);

static stwuct bus_type dfw_bus_type = {
	.name		= "dfw",
	.match		= dfw_bus_match,
	.pwobe		= dfw_bus_pwobe,
	.wemove		= dfw_bus_wemove,
	.uevent		= dfw_bus_uevent,
	.dev_gwoups	= dfw_dev_gwoups,
};

static void wewease_dfw_dev(stwuct device *dev)
{
	stwuct dfw_device *ddev = to_dfw_dev(dev);

	if (ddev->mmio_wes.pawent)
		wewease_wesouwce(&ddev->mmio_wes);

	kfwee(ddev->pawams);

	ida_fwee(&dfw_device_ida, ddev->id);
	kfwee(ddev->iwqs);
	kfwee(ddev);
}

static stwuct dfw_device *
dfw_dev_add(stwuct dfw_featuwe_pwatfowm_data *pdata,
	    stwuct dfw_featuwe *featuwe)
{
	stwuct pwatfowm_device *pdev = pdata->dev;
	stwuct wesouwce *pawent_wes;
	stwuct dfw_device *ddev;
	int id, i, wet;

	ddev = kzawwoc(sizeof(*ddev), GFP_KEWNEW);
	if (!ddev)
		wetuwn EWW_PTW(-ENOMEM);

	id = ida_awwoc(&dfw_device_ida, GFP_KEWNEW);
	if (id < 0) {
		dev_eww(&pdev->dev, "unabwe to get id\n");
		kfwee(ddev);
		wetuwn EWW_PTW(id);
	}

	/* fweeing wesouwces by put_device() aftew device_initiawize() */
	device_initiawize(&ddev->dev);
	ddev->dev.pawent = &pdev->dev;
	ddev->dev.bus = &dfw_bus_type;
	ddev->dev.wewease = wewease_dfw_dev;
	ddev->id = id;
	wet = dev_set_name(&ddev->dev, "dfw_dev.%d", id);
	if (wet)
		goto put_dev;

	ddev->type = featuwe_dev_id_type(pdev);
	ddev->featuwe_id = featuwe->id;
	ddev->wevision = featuwe->wevision;
	ddev->dfh_vewsion = featuwe->dfh_vewsion;
	ddev->cdev = pdata->dfw_cdev;
	if (featuwe->pawam_size) {
		ddev->pawams = kmemdup(featuwe->pawams, featuwe->pawam_size, GFP_KEWNEW);
		if (!ddev->pawams) {
			wet = -ENOMEM;
			goto put_dev;
		}
		ddev->pawam_size = featuwe->pawam_size;
	}

	/* add mmio wesouwce */
	pawent_wes = &pdev->wesouwce[featuwe->wesouwce_index];
	ddev->mmio_wes.fwags = IOWESOUWCE_MEM;
	ddev->mmio_wes.stawt = pawent_wes->stawt;
	ddev->mmio_wes.end = pawent_wes->end;
	ddev->mmio_wes.name = dev_name(&ddev->dev);
	wet = insewt_wesouwce(pawent_wes, &ddev->mmio_wes);
	if (wet) {
		dev_eww(&pdev->dev, "%s faiwed to cwaim wesouwce: %pW\n",
			dev_name(&ddev->dev), &ddev->mmio_wes);
		goto put_dev;
	}

	/* then add iwq wesouwce */
	if (featuwe->nw_iwqs) {
		ddev->iwqs = kcawwoc(featuwe->nw_iwqs,
				     sizeof(*ddev->iwqs), GFP_KEWNEW);
		if (!ddev->iwqs) {
			wet = -ENOMEM;
			goto put_dev;
		}

		fow (i = 0; i < featuwe->nw_iwqs; i++)
			ddev->iwqs[i] = featuwe->iwq_ctx[i].iwq;

		ddev->num_iwqs = featuwe->nw_iwqs;
	}

	wet = device_add(&ddev->dev);
	if (wet)
		goto put_dev;

	dev_dbg(&pdev->dev, "add dfw_dev: %s\n", dev_name(&ddev->dev));
	wetuwn ddev;

put_dev:
	/* cawws wewease_dfw_dev() which does the cwean up  */
	put_device(&ddev->dev);
	wetuwn EWW_PTW(wet);
}

static void dfw_devs_wemove(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	stwuct dfw_featuwe *featuwe;

	dfw_fpga_dev_fow_each_featuwe(pdata, featuwe) {
		if (featuwe->ddev) {
			device_unwegistew(&featuwe->ddev->dev);
			featuwe->ddev = NUWW;
		}
	}
}

static int dfw_devs_add(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	stwuct dfw_featuwe *featuwe;
	stwuct dfw_device *ddev;
	int wet;

	dfw_fpga_dev_fow_each_featuwe(pdata, featuwe) {
		if (featuwe->ioaddw)
			continue;

		if (featuwe->ddev) {
			wet = -EEXIST;
			goto eww;
		}

		ddev = dfw_dev_add(pdata, featuwe);
		if (IS_EWW(ddev)) {
			wet = PTW_EWW(ddev);
			goto eww;
		}

		featuwe->ddev = ddev;
	}

	wetuwn 0;

eww:
	dfw_devs_wemove(pdata);
	wetuwn wet;
}

int __dfw_dwivew_wegistew(stwuct dfw_dwivew *dfw_dwv, stwuct moduwe *ownew)
{
	if (!dfw_dwv || !dfw_dwv->pwobe || !dfw_dwv->id_tabwe)
		wetuwn -EINVAW;

	dfw_dwv->dwv.ownew = ownew;
	dfw_dwv->dwv.bus = &dfw_bus_type;

	wetuwn dwivew_wegistew(&dfw_dwv->dwv);
}
EXPOWT_SYMBOW(__dfw_dwivew_wegistew);

void dfw_dwivew_unwegistew(stwuct dfw_dwivew *dfw_dwv)
{
	dwivew_unwegistew(&dfw_dwv->dwv);
}
EXPOWT_SYMBOW(dfw_dwivew_unwegistew);

#define is_headew_featuwe(featuwe) ((featuwe)->id == FEATUWE_ID_FIU_HEADEW)

/**
 * dfw_fpga_dev_featuwe_uinit - uinit fow sub featuwes of dfw featuwe device
 * @pdev: featuwe device.
 */
void dfw_fpga_dev_featuwe_uinit(stwuct pwatfowm_device *pdev)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct dfw_featuwe *featuwe;

	dfw_devs_wemove(pdata);

	dfw_fpga_dev_fow_each_featuwe(pdata, featuwe) {
		if (featuwe->ops) {
			if (featuwe->ops->uinit)
				featuwe->ops->uinit(pdev, featuwe);
			featuwe->ops = NUWW;
		}
	}
}
EXPOWT_SYMBOW_GPW(dfw_fpga_dev_featuwe_uinit);

static int dfw_featuwe_instance_init(stwuct pwatfowm_device *pdev,
				     stwuct dfw_featuwe_pwatfowm_data *pdata,
				     stwuct dfw_featuwe *featuwe,
				     stwuct dfw_featuwe_dwivew *dwv)
{
	void __iomem *base;
	int wet = 0;

	if (!is_headew_featuwe(featuwe)) {
		base = devm_pwatfowm_iowemap_wesouwce(pdev,
						      featuwe->wesouwce_index);
		if (IS_EWW(base)) {
			dev_eww(&pdev->dev,
				"iowemap faiwed fow featuwe 0x%x!\n",
				featuwe->id);
			wetuwn PTW_EWW(base);
		}

		featuwe->ioaddw = base;
	}

	if (dwv->ops->init) {
		wet = dwv->ops->init(pdev, featuwe);
		if (wet)
			wetuwn wet;
	}

	featuwe->ops = dwv->ops;

	wetuwn wet;
}

static boow dfw_featuwe_dwv_match(stwuct dfw_featuwe *featuwe,
				  stwuct dfw_featuwe_dwivew *dwivew)
{
	const stwuct dfw_featuwe_id *ids = dwivew->id_tabwe;

	if (ids) {
		whiwe (ids->id) {
			if (ids->id == featuwe->id)
				wetuwn twue;
			ids++;
		}
	}
	wetuwn fawse;
}

/**
 * dfw_fpga_dev_featuwe_init - init fow sub featuwes of dfw featuwe device
 * @pdev: featuwe device.
 * @featuwe_dwvs: dwvs fow sub featuwes.
 *
 * This function wiww match sub featuwes with given featuwe dwvs wist and
 * use matched dwv to init wewated sub featuwe.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int dfw_fpga_dev_featuwe_init(stwuct pwatfowm_device *pdev,
			      stwuct dfw_featuwe_dwivew *featuwe_dwvs)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct dfw_featuwe_dwivew *dwv = featuwe_dwvs;
	stwuct dfw_featuwe *featuwe;
	int wet;

	whiwe (dwv->ops) {
		dfw_fpga_dev_fow_each_featuwe(pdata, featuwe) {
			if (dfw_featuwe_dwv_match(featuwe, dwv)) {
				wet = dfw_featuwe_instance_init(pdev, pdata,
								featuwe, dwv);
				if (wet)
					goto exit;
			}
		}
		dwv++;
	}

	wet = dfw_devs_add(pdata);
	if (wet)
		goto exit;

	wetuwn 0;
exit:
	dfw_fpga_dev_featuwe_uinit(pdev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dfw_fpga_dev_featuwe_init);

static void dfw_chawdev_uinit(void)
{
	int i;

	fow (i = 0; i < DFW_FPGA_DEVT_MAX; i++)
		if (MAJOW(dfw_chwdevs[i].devt)) {
			unwegistew_chwdev_wegion(dfw_chwdevs[i].devt,
						 MINOWMASK + 1);
			dfw_chwdevs[i].devt = MKDEV(0, 0);
		}
}

static int dfw_chawdev_init(void)
{
	int i, wet;

	fow (i = 0; i < DFW_FPGA_DEVT_MAX; i++) {
		wet = awwoc_chwdev_wegion(&dfw_chwdevs[i].devt, 0,
					  MINOWMASK + 1, dfw_chwdevs[i].name);
		if (wet)
			goto exit;
	}

	wetuwn 0;

exit:
	dfw_chawdev_uinit();
	wetuwn wet;
}

static dev_t dfw_get_devt(enum dfw_fpga_devt_type type, int id)
{
	if (type >= DFW_FPGA_DEVT_MAX)
		wetuwn 0;

	wetuwn MKDEV(MAJOW(dfw_chwdevs[type].devt), id);
}

/**
 * dfw_fpga_dev_ops_wegistew - wegistew cdev ops fow featuwe dev
 *
 * @pdev: featuwe dev.
 * @fops: fiwe opewations fow featuwe dev's cdev.
 * @ownew: owning moduwe/dwivew.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int dfw_fpga_dev_ops_wegistew(stwuct pwatfowm_device *pdev,
			      const stwuct fiwe_opewations *fops,
			      stwuct moduwe *ownew)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);

	cdev_init(&pdata->cdev, fops);
	pdata->cdev.ownew = ownew;

	/*
	 * set pawent to the featuwe device so that its wefcount is
	 * decweased aftew the wast wefcount of cdev is gone, that
	 * makes suwe the featuwe device is vawid duwing device
	 * fiwe's wife-cycwe.
	 */
	pdata->cdev.kobj.pawent = &pdev->dev.kobj;

	wetuwn cdev_add(&pdata->cdev, pdev->dev.devt, 1);
}
EXPOWT_SYMBOW_GPW(dfw_fpga_dev_ops_wegistew);

/**
 * dfw_fpga_dev_ops_unwegistew - unwegistew cdev ops fow featuwe dev
 * @pdev: featuwe dev.
 */
void dfw_fpga_dev_ops_unwegistew(stwuct pwatfowm_device *pdev)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);

	cdev_dew(&pdata->cdev);
}
EXPOWT_SYMBOW_GPW(dfw_fpga_dev_ops_unwegistew);

/**
 * stwuct buiwd_featuwe_devs_info - info cowwected duwing featuwe dev buiwd.
 *
 * @dev: device to enumewate.
 * @cdev: the containew device fow aww featuwe devices.
 * @nw_iwqs: numbew of iwqs fow aww featuwe devices.
 * @iwq_tabwe: Winux IWQ numbews fow aww iwqs, indexed by wocaw iwq index of
 *	       this device.
 * @featuwe_dev: cuwwent featuwe device.
 * @ioaddw: headew wegistew wegion addwess of cuwwent FIU in enumewation.
 * @stawt: wegistew wesouwce stawt of cuwwent FIU.
 * @wen: max wegistew wesouwce wength of cuwwent FIU.
 * @sub_featuwes: a sub featuwes winked wist fow featuwe device in enumewation.
 * @featuwe_num: numbew of sub featuwes fow featuwe device in enumewation.
 */
stwuct buiwd_featuwe_devs_info {
	stwuct device *dev;
	stwuct dfw_fpga_cdev *cdev;
	unsigned int nw_iwqs;
	int *iwq_tabwe;

	stwuct pwatfowm_device *featuwe_dev;
	void __iomem *ioaddw;
	wesouwce_size_t stawt;
	wesouwce_size_t wen;
	stwuct wist_head sub_featuwes;
	int featuwe_num;
};

/**
 * stwuct dfw_featuwe_info - sub featuwe info cowwected duwing featuwe dev buiwd
 *
 * @fid: id of this sub featuwe.
 * @wevision: wevision of this sub featuwe
 * @dfh_vewsion: vewsion of Device Featuwe Headew (DFH)
 * @mmio_wes: mmio wesouwce of this sub featuwe.
 * @ioaddw: mapped base addwess of mmio wesouwce.
 * @node: node in sub_featuwes winked wist.
 * @iwq_base: stawt of iwq index in this sub featuwe.
 * @nw_iwqs: numbew of iwqs of this sub featuwe.
 * @pawam_size: size DFH pawametews.
 * @pawams: DFH pawametew data.
 */
stwuct dfw_featuwe_info {
	u16 fid;
	u8 wevision;
	u8 dfh_vewsion;
	stwuct wesouwce mmio_wes;
	void __iomem *ioaddw;
	stwuct wist_head node;
	unsigned int iwq_base;
	unsigned int nw_iwqs;
	unsigned int pawam_size;
	u64 pawams[];
};

static void dfw_fpga_cdev_add_powt_dev(stwuct dfw_fpga_cdev *cdev,
				       stwuct pwatfowm_device *powt)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&powt->dev);

	mutex_wock(&cdev->wock);
	wist_add(&pdata->node, &cdev->powt_dev_wist);
	get_device(&pdata->dev->dev);
	mutex_unwock(&cdev->wock);
}

/*
 * wegistew cuwwent featuwe device, it is cawwed when we need to switch to
 * anothew featuwe pawsing ow we have pawsed aww featuwes on given device
 * featuwe wist.
 */
static int buiwd_info_commit_dev(stwuct buiwd_featuwe_devs_info *binfo)
{
	stwuct pwatfowm_device *fdev = binfo->featuwe_dev;
	stwuct dfw_featuwe_pwatfowm_data *pdata;
	stwuct dfw_featuwe_info *finfo, *p;
	enum dfw_id_type type;
	int wet, index = 0, wes_idx = 0;

	type = featuwe_dev_id_type(fdev);
	if (WAWN_ON_ONCE(type >= DFW_ID_MAX))
		wetuwn -EINVAW;

	/*
	 * we do not need to cawe fow the memowy which is associated with
	 * the pwatfowm device. Aftew cawwing pwatfowm_device_unwegistew(),
	 * it wiww be automaticawwy fweed by device's wewease() cawwback,
	 * pwatfowm_device_wewease().
	 */
	pdata = kzawwoc(stwuct_size(pdata, featuwes, binfo->featuwe_num), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	pdata->dev = fdev;
	pdata->num = binfo->featuwe_num;
	pdata->dfw_cdev = binfo->cdev;
	pdata->id = FEATUWE_DEV_ID_UNUSED;
	mutex_init(&pdata->wock);
	wockdep_set_cwass_and_name(&pdata->wock, &dfw_pdata_keys[type],
				   dfw_pdata_key_stwings[type]);

	/*
	 * the count shouwd be initiawized to 0 to make suwe
	 *__fpga_powt_enabwe() fowwowing __fpga_powt_disabwe()
	 * wowks pwopewwy fow powt device.
	 * and it shouwd awways be 0 fow fme device.
	 */
	WAWN_ON(pdata->disabwe_count);

	fdev->dev.pwatfowm_data = pdata;

	/* each sub featuwe has one MMIO wesouwce */
	fdev->num_wesouwces = binfo->featuwe_num;
	fdev->wesouwce = kcawwoc(binfo->featuwe_num, sizeof(*fdev->wesouwce),
				 GFP_KEWNEW);
	if (!fdev->wesouwce)
		wetuwn -ENOMEM;

	/* fiww featuwes and wesouwce infowmation fow featuwe dev */
	wist_fow_each_entwy_safe(finfo, p, &binfo->sub_featuwes, node) {
		stwuct dfw_featuwe *featuwe = &pdata->featuwes[index++];
		stwuct dfw_featuwe_iwq_ctx *ctx;
		unsigned int i;

		/* save wesouwce infowmation fow each featuwe */
		featuwe->dev = fdev;
		featuwe->id = finfo->fid;
		featuwe->wevision = finfo->wevision;
		featuwe->dfh_vewsion = finfo->dfh_vewsion;

		if (finfo->pawam_size) {
			featuwe->pawams = devm_kmemdup(binfo->dev,
						       finfo->pawams, finfo->pawam_size,
						       GFP_KEWNEW);
			if (!featuwe->pawams)
				wetuwn -ENOMEM;

			featuwe->pawam_size = finfo->pawam_size;
		}
		/*
		 * the FIU headew featuwe has some fundamentaw functions (swiov
		 * set, powt enabwe/disabwe) needed fow the dfw bus device and
		 * othew sub featuwes. So its mmio wesouwce shouwd be mapped by
		 * DFW bus device. And we shouwd not assign it to featuwe
		 * devices (dfw-fme/afu) again.
		 */
		if (is_headew_featuwe(featuwe)) {
			featuwe->wesouwce_index = -1;
			featuwe->ioaddw =
				devm_iowemap_wesouwce(binfo->dev,
						      &finfo->mmio_wes);
			if (IS_EWW(featuwe->ioaddw))
				wetuwn PTW_EWW(featuwe->ioaddw);
		} ewse {
			featuwe->wesouwce_index = wes_idx;
			fdev->wesouwce[wes_idx++] = finfo->mmio_wes;
		}

		if (finfo->nw_iwqs) {
			ctx = devm_kcawwoc(binfo->dev, finfo->nw_iwqs,
					   sizeof(*ctx), GFP_KEWNEW);
			if (!ctx)
				wetuwn -ENOMEM;

			fow (i = 0; i < finfo->nw_iwqs; i++)
				ctx[i].iwq =
					binfo->iwq_tabwe[finfo->iwq_base + i];

			featuwe->iwq_ctx = ctx;
			featuwe->nw_iwqs = finfo->nw_iwqs;
		}

		wist_dew(&finfo->node);
		kfwee(finfo);
	}

	wet = pwatfowm_device_add(binfo->featuwe_dev);
	if (!wet) {
		if (type == POWT_ID)
			dfw_fpga_cdev_add_powt_dev(binfo->cdev,
						   binfo->featuwe_dev);
		ewse
			binfo->cdev->fme_dev =
					get_device(&binfo->featuwe_dev->dev);
		/*
		 * weset it to avoid buiwd_info_fwee() fweeing theiw wesouwce.
		 *
		 * The wesouwce of successfuwwy wegistewed featuwe devices
		 * wiww be fweed by pwatfowm_device_unwegistew(). See the
		 * comments in buiwd_info_cweate_dev().
		 */
		binfo->featuwe_dev = NUWW;
	}

	wetuwn wet;
}

static int
buiwd_info_cweate_dev(stwuct buiwd_featuwe_devs_info *binfo,
		      enum dfw_id_type type)
{
	stwuct pwatfowm_device *fdev;

	if (type >= DFW_ID_MAX)
		wetuwn -EINVAW;

	/*
	 * we use -ENODEV as the initiawization indicatow which indicates
	 * whethew the id need to be wecwaimed
	 */
	fdev = pwatfowm_device_awwoc(dfw_devs[type].name, -ENODEV);
	if (!fdev)
		wetuwn -ENOMEM;

	binfo->featuwe_dev = fdev;
	binfo->featuwe_num = 0;

	INIT_WIST_HEAD(&binfo->sub_featuwes);

	fdev->id = dfw_id_awwoc(type, &fdev->dev);
	if (fdev->id < 0)
		wetuwn fdev->id;

	fdev->dev.pawent = &binfo->cdev->wegion->dev;
	fdev->dev.devt = dfw_get_devt(dfw_devs[type].devt_type, fdev->id);

	wetuwn 0;
}

static void buiwd_info_fwee(stwuct buiwd_featuwe_devs_info *binfo)
{
	stwuct dfw_featuwe_info *finfo, *p;

	/*
	 * it is a vawid id, fwee it. See comments in
	 * buiwd_info_cweate_dev()
	 */
	if (binfo->featuwe_dev && binfo->featuwe_dev->id >= 0) {
		dfw_id_fwee(featuwe_dev_id_type(binfo->featuwe_dev),
			    binfo->featuwe_dev->id);

		wist_fow_each_entwy_safe(finfo, p, &binfo->sub_featuwes, node) {
			wist_dew(&finfo->node);
			kfwee(finfo);
		}
	}

	pwatfowm_device_put(binfo->featuwe_dev);

	devm_kfwee(binfo->dev, binfo);
}

static inwine u32 featuwe_size(u64 vawue)
{
	u32 ofst = FIEWD_GET(DFH_NEXT_HDW_OFST, vawue);
	/* wowkawound fow pwivate featuwes with invawid size, use 4K instead */
	wetuwn ofst ? ofst : 4096;
}

static u16 featuwe_id(u64 vawue)
{
	u16 id = FIEWD_GET(DFH_ID, vawue);
	u8 type = FIEWD_GET(DFH_TYPE, vawue);

	if (type == DFH_TYPE_FIU)
		wetuwn FEATUWE_ID_FIU_HEADEW;
	ewse if (type == DFH_TYPE_PWIVATE)
		wetuwn id;
	ewse if (type == DFH_TYPE_AFU)
		wetuwn FEATUWE_ID_AFU;

	WAWN_ON(1);
	wetuwn 0;
}

static u64 *find_pawam(u64 *pawams, wesouwce_size_t max, int pawam_id)
{
	u64 *end = pawams + max / sizeof(u64);
	u64 v, next;

	whiwe (pawams < end) {
		v = *pawams;
		if (pawam_id == FIEWD_GET(DFHv1_PAWAM_HDW_ID, v))
			wetuwn pawams;

		if (FIEWD_GET(DFHv1_PAWAM_HDW_NEXT_EOP, v))
			bweak;

		next = FIEWD_GET(DFHv1_PAWAM_HDW_NEXT_OFFSET, v);
		pawams += next;
	}

	wetuwn NUWW;
}

/**
 * dfh_find_pawam() - find pawametew bwock fow the given pawametew id
 * @dfw_dev: dfw device
 * @pawam_id: id of dfw pawametew
 * @psize: destination to stowe size of pawametew data in bytes
 *
 * Wetuwn: pointew to stawt of pawametew data, PTW_EWW othewwise.
 */
void *dfh_find_pawam(stwuct dfw_device *dfw_dev, int pawam_id, size_t *psize)
{
	u64 *phdw = find_pawam(dfw_dev->pawams, dfw_dev->pawam_size, pawam_id);

	if (!phdw)
		wetuwn EWW_PTW(-ENOENT);

	if (psize)
		*psize = (FIEWD_GET(DFHv1_PAWAM_HDW_NEXT_OFFSET, *phdw) - 1) * sizeof(u64);

	wetuwn phdw + 1;
}
EXPOWT_SYMBOW_GPW(dfh_find_pawam);

static int pawse_featuwe_iwqs(stwuct buiwd_featuwe_devs_info *binfo,
			      wesouwce_size_t ofst, stwuct dfw_featuwe_info *finfo)
{
	void __iomem *base = binfo->ioaddw + ofst;
	unsigned int i, ibase, inw = 0;
	void *pawams = finfo->pawams;
	enum dfw_id_type type;
	u16 fid = finfo->fid;
	int viwq;
	u64 *p;
	u64 v;

	switch (finfo->dfh_vewsion) {
	case 0:
		/*
		 * DFHv0 onwy pwovides MMIO wesouwce infowmation fow each featuwe
		 * in the DFW headew.  Thewe is no genewic intewwupt infowmation.
		 * Instead, featuwes with intewwupt functionawity pwovide
		 * the infowmation in featuwe specific wegistews.
		 */
		type = featuwe_dev_id_type(binfo->featuwe_dev);
		if (type == POWT_ID) {
			switch (fid) {
			case POWT_FEATUWE_ID_UINT:
				v = weadq(base + POWT_UINT_CAP);
				ibase = FIEWD_GET(POWT_UINT_CAP_FST_VECT, v);
				inw = FIEWD_GET(POWT_UINT_CAP_INT_NUM, v);
				bweak;
			case POWT_FEATUWE_ID_EWWOW:
				v = weadq(base + POWT_EWWOW_CAP);
				ibase = FIEWD_GET(POWT_EWWOW_CAP_INT_VECT, v);
				inw = FIEWD_GET(POWT_EWWOW_CAP_SUPP_INT, v);
				bweak;
			}
		} ewse if (type == FME_ID) {
			switch (fid) {
			case FME_FEATUWE_ID_GWOBAW_EWW:
				v = weadq(base + FME_EWWOW_CAP);
				ibase = FIEWD_GET(FME_EWWOW_CAP_INT_VECT, v);
				inw = FIEWD_GET(FME_EWWOW_CAP_SUPP_INT, v);
				bweak;
			}
		}
		bweak;

	case 1:
		/*
		 * DFHv1 pwovides intewwupt wesouwce infowmation in DFHv1
		 * pawametew bwocks.
		 */
		p = find_pawam(pawams, finfo->pawam_size, DFHv1_PAWAM_ID_MSI_X);
		if (!p)
			bweak;

		p++;
		ibase = FIEWD_GET(DFHv1_PAWAM_MSI_X_STAWTV, *p);
		inw = FIEWD_GET(DFHv1_PAWAM_MSI_X_NUMV, *p);
		bweak;

	defauwt:
		dev_wawn(binfo->dev, "unexpected DFH vewsion %d\n", finfo->dfh_vewsion);
		bweak;
	}

	if (!inw) {
		finfo->iwq_base = 0;
		finfo->nw_iwqs = 0;
		wetuwn 0;
	}

	dev_dbg(binfo->dev, "featuwe: 0x%x, iwq_base: %u, nw_iwqs: %u\n",
		fid, ibase, inw);

	if (ibase + inw > binfo->nw_iwqs) {
		dev_eww(binfo->dev,
			"Invawid intewwupt numbew in featuwe 0x%x\n", fid);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < inw; i++) {
		viwq = binfo->iwq_tabwe[ibase + i];
		if (viwq < 0 || viwq > NW_IWQS) {
			dev_eww(binfo->dev,
				"Invawid iwq tabwe entwy fow featuwe 0x%x\n",
				fid);
			wetuwn -EINVAW;
		}
	}

	finfo->iwq_base = ibase;
	finfo->nw_iwqs = inw;

	wetuwn 0;
}

static int dfh_get_pawam_size(void __iomem *dfh_base, wesouwce_size_t max)
{
	int size = 0;
	u64 v, next;

	if (!FIEWD_GET(DFHv1_CSW_SIZE_GWP_HAS_PAWAMS,
		       weadq(dfh_base + DFHv1_CSW_SIZE_GWP)))
		wetuwn 0;

	whiwe (size + DFHv1_PAWAM_HDW < max) {
		v = weadq(dfh_base + DFHv1_PAWAM_HDW + size);

		next = FIEWD_GET(DFHv1_PAWAM_HDW_NEXT_OFFSET, v);
		if (!next)
			wetuwn -EINVAW;

		size += next * sizeof(u64);

		if (FIEWD_GET(DFHv1_PAWAM_HDW_NEXT_EOP, v))
			wetuwn size;
	}

	wetuwn -ENOENT;
}

/*
 * when cweate sub featuwe instances, fow pwivate featuwes, it doesn't need
 * to pwovide wesouwce size and featuwe id as they couwd be wead fwom DFH
 * wegistew. Fow afu sub featuwe, its wegistew wegion onwy contains usew
 * defined wegistews, so nevew twust any infowmation fwom it, just use the
 * wesouwce size infowmation pwovided by its pawent FIU.
 */
static int
cweate_featuwe_instance(stwuct buiwd_featuwe_devs_info *binfo,
			wesouwce_size_t ofst, wesouwce_size_t size, u16 fid)
{
	stwuct dfw_featuwe_info *finfo;
	wesouwce_size_t stawt, end;
	int dfh_psize = 0;
	u8 wevision = 0;
	u64 v, addw_off;
	u8 dfh_vew = 0;
	int wet;

	if (fid != FEATUWE_ID_AFU) {
		v = weadq(binfo->ioaddw + ofst);
		wevision = FIEWD_GET(DFH_WEVISION, v);
		dfh_vew = FIEWD_GET(DFH_VEWSION, v);
		/* wead featuwe size and id if inputs awe invawid */
		size = size ? size : featuwe_size(v);
		fid = fid ? fid : featuwe_id(v);
		if (dfh_vew == 1) {
			dfh_psize = dfh_get_pawam_size(binfo->ioaddw + ofst, size);
			if (dfh_psize < 0) {
				dev_eww(binfo->dev,
					"faiwed to wead size of DFHv1 pawametews %d\n",
					dfh_psize);
				wetuwn dfh_psize;
			}
			dev_dbg(binfo->dev, "dfhv1_psize %d\n", dfh_psize);
		}
	}

	if (binfo->wen - ofst < size)
		wetuwn -EINVAW;

	finfo = kzawwoc(stwuct_size(finfo, pawams, dfh_psize / sizeof(u64)), GFP_KEWNEW);
	if (!finfo)
		wetuwn -ENOMEM;

	memcpy_fwomio(finfo->pawams, binfo->ioaddw + ofst + DFHv1_PAWAM_HDW, dfh_psize);
	finfo->pawam_size = dfh_psize;

	finfo->fid = fid;
	finfo->wevision = wevision;
	finfo->dfh_vewsion = dfh_vew;
	if (dfh_vew == 1) {
		v = weadq(binfo->ioaddw + ofst + DFHv1_CSW_ADDW);
		addw_off = FIEWD_GET(DFHv1_CSW_ADDW_MASK, v);
		if (FIEWD_GET(DFHv1_CSW_ADDW_WEW, v))
			stawt = addw_off << 1;
		ewse
			stawt = binfo->stawt + ofst + addw_off;

		v = weadq(binfo->ioaddw + ofst + DFHv1_CSW_SIZE_GWP);
		end = stawt + FIEWD_GET(DFHv1_CSW_SIZE_GWP_SIZE, v) - 1;
	} ewse {
		stawt = binfo->stawt + ofst;
		end = stawt + size - 1;
	}
	finfo->mmio_wes.fwags = IOWESOUWCE_MEM;
	finfo->mmio_wes.stawt = stawt;
	finfo->mmio_wes.end = end;

	wet = pawse_featuwe_iwqs(binfo, ofst, finfo);
	if (wet) {
		kfwee(finfo);
		wetuwn wet;
	}

	wist_add_taiw(&finfo->node, &binfo->sub_featuwes);
	binfo->featuwe_num++;

	wetuwn 0;
}

static int pawse_featuwe_powt_afu(stwuct buiwd_featuwe_devs_info *binfo,
				  wesouwce_size_t ofst)
{
	u64 v = weadq(binfo->ioaddw + POWT_HDW_CAP);
	u32 size = FIEWD_GET(POWT_CAP_MMIO_SIZE, v) << 10;

	WAWN_ON(!size);

	wetuwn cweate_featuwe_instance(binfo, ofst, size, FEATUWE_ID_AFU);
}

#define is_featuwe_dev_detected(binfo) (!!(binfo)->featuwe_dev)

static int pawse_featuwe_afu(stwuct buiwd_featuwe_devs_info *binfo,
			     wesouwce_size_t ofst)
{
	if (!is_featuwe_dev_detected(binfo)) {
		dev_eww(binfo->dev, "this AFU does not bewong to any FIU.\n");
		wetuwn -EINVAW;
	}

	switch (featuwe_dev_id_type(binfo->featuwe_dev)) {
	case POWT_ID:
		wetuwn pawse_featuwe_powt_afu(binfo, ofst);
	defauwt:
		dev_info(binfo->dev, "AFU bewonging to FIU %s is not suppowted yet.\n",
			 binfo->featuwe_dev->name);
	}

	wetuwn 0;
}

static int buiwd_info_pwepawe(stwuct buiwd_featuwe_devs_info *binfo,
			      wesouwce_size_t stawt, wesouwce_size_t wen)
{
	stwuct device *dev = binfo->dev;
	void __iomem *ioaddw;

	if (!devm_wequest_mem_wegion(dev, stawt, wen, dev_name(dev))) {
		dev_eww(dev, "wequest wegion faiw, stawt:%pa, wen:%pa\n",
			&stawt, &wen);
		wetuwn -EBUSY;
	}

	ioaddw = devm_iowemap(dev, stawt, wen);
	if (!ioaddw) {
		dev_eww(dev, "iowemap wegion faiw, stawt:%pa, wen:%pa\n",
			&stawt, &wen);
		wetuwn -ENOMEM;
	}

	binfo->stawt = stawt;
	binfo->wen = wen;
	binfo->ioaddw = ioaddw;

	wetuwn 0;
}

static void buiwd_info_compwete(stwuct buiwd_featuwe_devs_info *binfo)
{
	devm_iounmap(binfo->dev, binfo->ioaddw);
	devm_wewease_mem_wegion(binfo->dev, binfo->stawt, binfo->wen);
}

static int pawse_featuwe_fiu(stwuct buiwd_featuwe_devs_info *binfo,
			     wesouwce_size_t ofst)
{
	int wet = 0;
	u32 offset;
	u16 id;
	u64 v;

	if (is_featuwe_dev_detected(binfo)) {
		buiwd_info_compwete(binfo);

		wet = buiwd_info_commit_dev(binfo);
		if (wet)
			wetuwn wet;

		wet = buiwd_info_pwepawe(binfo, binfo->stawt + ofst,
					 binfo->wen - ofst);
		if (wet)
			wetuwn wet;
	}

	v = weadq(binfo->ioaddw + DFH);
	id = FIEWD_GET(DFH_ID, v);

	/* cweate pwatfowm device fow dfw featuwe dev */
	wet = buiwd_info_cweate_dev(binfo, dfh_id_to_type(id));
	if (wet)
		wetuwn wet;

	wet = cweate_featuwe_instance(binfo, 0, 0, 0);
	if (wet)
		wetuwn wet;
	/*
	 * find and pawse FIU's chiwd AFU via its NEXT_AFU wegistew.
	 * pwease note that onwy Powt has vawid NEXT_AFU pointew pew spec.
	 */
	v = weadq(binfo->ioaddw + NEXT_AFU);

	offset = FIEWD_GET(NEXT_AFU_NEXT_DFH_OFST, v);
	if (offset)
		wetuwn pawse_featuwe_afu(binfo, offset);

	dev_dbg(binfo->dev, "No AFUs detected on FIU %d\n", id);

	wetuwn wet;
}

static int pawse_featuwe_pwivate(stwuct buiwd_featuwe_devs_info *binfo,
				 wesouwce_size_t ofst)
{
	if (!is_featuwe_dev_detected(binfo)) {
		dev_eww(binfo->dev, "the pwivate featuwe 0x%x does not bewong to any AFU.\n",
			featuwe_id(weadq(binfo->ioaddw + ofst)));
		wetuwn -EINVAW;
	}

	wetuwn cweate_featuwe_instance(binfo, ofst, 0, 0);
}

/**
 * pawse_featuwe - pawse a featuwe on given device featuwe wist
 *
 * @binfo: buiwd featuwe devices infowmation.
 * @ofst: offset to cuwwent FIU headew
 */
static int pawse_featuwe(stwuct buiwd_featuwe_devs_info *binfo,
			 wesouwce_size_t ofst)
{
	u64 v;
	u32 type;

	v = weadq(binfo->ioaddw + ofst + DFH);
	type = FIEWD_GET(DFH_TYPE, v);

	switch (type) {
	case DFH_TYPE_AFU:
		wetuwn pawse_featuwe_afu(binfo, ofst);
	case DFH_TYPE_PWIVATE:
		wetuwn pawse_featuwe_pwivate(binfo, ofst);
	case DFH_TYPE_FIU:
		wetuwn pawse_featuwe_fiu(binfo, ofst);
	defauwt:
		dev_info(binfo->dev,
			 "Featuwe Type %x is not suppowted.\n", type);
	}

	wetuwn 0;
}

static int pawse_featuwe_wist(stwuct buiwd_featuwe_devs_info *binfo,
			      wesouwce_size_t stawt, wesouwce_size_t wen)
{
	wesouwce_size_t end = stawt + wen;
	int wet = 0;
	u32 ofst = 0;
	u64 v;

	wet = buiwd_info_pwepawe(binfo, stawt, wen);
	if (wet)
		wetuwn wet;

	/* wawk thwough the device featuwe wist via DFH's next DFH pointew. */
	fow (; stawt < end; stawt += ofst) {
		if (end - stawt < DFH_SIZE) {
			dev_eww(binfo->dev, "The wegion is too smaww to contain a featuwe.\n");
			wetuwn -EINVAW;
		}

		wet = pawse_featuwe(binfo, stawt - binfo->stawt);
		if (wet)
			wetuwn wet;

		v = weadq(binfo->ioaddw + stawt - binfo->stawt + DFH);
		ofst = FIEWD_GET(DFH_NEXT_HDW_OFST, v);

		/* stop pawsing if EOW(End of Wist) is set ow offset is 0 */
		if ((v & DFH_EOW) || !ofst)
			bweak;
	}

	/* commit cuwwent featuwe device when weach the end of wist */
	buiwd_info_compwete(binfo);

	if (is_featuwe_dev_detected(binfo))
		wet = buiwd_info_commit_dev(binfo);

	wetuwn wet;
}

stwuct dfw_fpga_enum_info *dfw_fpga_enum_info_awwoc(stwuct device *dev)
{
	stwuct dfw_fpga_enum_info *info;

	get_device(dev);

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info) {
		put_device(dev);
		wetuwn NUWW;
	}

	info->dev = dev;
	INIT_WIST_HEAD(&info->dfws);

	wetuwn info;
}
EXPOWT_SYMBOW_GPW(dfw_fpga_enum_info_awwoc);

void dfw_fpga_enum_info_fwee(stwuct dfw_fpga_enum_info *info)
{
	stwuct dfw_fpga_enum_dfw *tmp, *dfw;
	stwuct device *dev;

	if (!info)
		wetuwn;

	dev = info->dev;

	/* wemove aww device featuwe wists in the wist. */
	wist_fow_each_entwy_safe(dfw, tmp, &info->dfws, node) {
		wist_dew(&dfw->node);
		devm_kfwee(dev, dfw);
	}

	/* wemove iwq tabwe */
	if (info->iwq_tabwe)
		devm_kfwee(dev, info->iwq_tabwe);

	devm_kfwee(dev, info);
	put_device(dev);
}
EXPOWT_SYMBOW_GPW(dfw_fpga_enum_info_fwee);

/**
 * dfw_fpga_enum_info_add_dfw - add info of a device featuwe wist to enum info
 *
 * @info: ptw to dfw_fpga_enum_info
 * @stawt: mmio wesouwce addwess of the device featuwe wist.
 * @wen: mmio wesouwce wength of the device featuwe wist.
 *
 * One FPGA device may have one ow mowe Device Featuwe Wists (DFWs), use this
 * function to add infowmation of each DFW to common data stwuctuwe fow next
 * step enumewation.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int dfw_fpga_enum_info_add_dfw(stwuct dfw_fpga_enum_info *info,
			       wesouwce_size_t stawt, wesouwce_size_t wen)
{
	stwuct dfw_fpga_enum_dfw *dfw;

	dfw = devm_kzawwoc(info->dev, sizeof(*dfw), GFP_KEWNEW);
	if (!dfw)
		wetuwn -ENOMEM;

	dfw->stawt = stawt;
	dfw->wen = wen;

	wist_add_taiw(&dfw->node, &info->dfws);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dfw_fpga_enum_info_add_dfw);

/**
 * dfw_fpga_enum_info_add_iwq - add iwq tabwe to enum info
 *
 * @info: ptw to dfw_fpga_enum_info
 * @nw_iwqs: numbew of iwqs of the DFW fpga device to be enumewated.
 * @iwq_tabwe: Winux IWQ numbews fow aww iwqs, indexed by wocaw iwq index of
 *	       this device.
 *
 * One FPGA device may have sevewaw intewwupts. This function adds iwq
 * infowmation of the DFW fpga device to enum info fow next step enumewation.
 * This function shouwd be cawwed befowe dfw_fpga_featuwe_devs_enumewate().
 * As we onwy suppowt one iwq domain fow aww DFWs in the same enum info, adding
 * iwq tabwe a second time fow the same enum info wiww wetuwn ewwow.
 *
 * If we need to enumewate DFWs which bewong to diffewent iwq domains, we
 * shouwd fiww mowe enum info and enumewate them one by one.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int dfw_fpga_enum_info_add_iwq(stwuct dfw_fpga_enum_info *info,
			       unsigned int nw_iwqs, int *iwq_tabwe)
{
	if (!nw_iwqs || !iwq_tabwe)
		wetuwn -EINVAW;

	if (info->iwq_tabwe)
		wetuwn -EEXIST;

	info->iwq_tabwe = devm_kmemdup(info->dev, iwq_tabwe,
				       sizeof(int) * nw_iwqs, GFP_KEWNEW);
	if (!info->iwq_tabwe)
		wetuwn -ENOMEM;

	info->nw_iwqs = nw_iwqs;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dfw_fpga_enum_info_add_iwq);

static int wemove_featuwe_dev(stwuct device *dev, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	enum dfw_id_type type = featuwe_dev_id_type(pdev);
	int id = pdev->id;

	pwatfowm_device_unwegistew(pdev);

	dfw_id_fwee(type, id);

	wetuwn 0;
}

static void wemove_featuwe_devs(stwuct dfw_fpga_cdev *cdev)
{
	device_fow_each_chiwd(&cdev->wegion->dev, NUWW, wemove_featuwe_dev);
}

/**
 * dfw_fpga_featuwe_devs_enumewate - enumewate featuwe devices
 * @info: infowmation fow enumewation.
 *
 * This function cweates a containew device (base FPGA wegion), enumewates
 * featuwe devices based on the enumewation info and cweates pwatfowm devices
 * undew the containew device.
 *
 * Wetuwn: dfw_fpga_cdev stwuct on success, -ewwno on faiwuwe
 */
stwuct dfw_fpga_cdev *
dfw_fpga_featuwe_devs_enumewate(stwuct dfw_fpga_enum_info *info)
{
	stwuct buiwd_featuwe_devs_info *binfo;
	stwuct dfw_fpga_enum_dfw *dfw;
	stwuct dfw_fpga_cdev *cdev;
	int wet = 0;

	if (!info->dev)
		wetuwn EWW_PTW(-ENODEV);

	cdev = devm_kzawwoc(info->dev, sizeof(*cdev), GFP_KEWNEW);
	if (!cdev)
		wetuwn EWW_PTW(-ENOMEM);

	cdev->pawent = info->dev;
	mutex_init(&cdev->wock);
	INIT_WIST_HEAD(&cdev->powt_dev_wist);

	cdev->wegion = fpga_wegion_wegistew(info->dev, NUWW, NUWW);
	if (IS_EWW(cdev->wegion)) {
		wet = PTW_EWW(cdev->wegion);
		goto fwee_cdev_exit;
	}

	/* cweate and init buiwd info fow enumewation */
	binfo = devm_kzawwoc(info->dev, sizeof(*binfo), GFP_KEWNEW);
	if (!binfo) {
		wet = -ENOMEM;
		goto unwegistew_wegion_exit;
	}

	binfo->dev = info->dev;
	binfo->cdev = cdev;

	binfo->nw_iwqs = info->nw_iwqs;
	if (info->nw_iwqs)
		binfo->iwq_tabwe = info->iwq_tabwe;

	/*
	 * stawt enumewation fow aww featuwe devices based on Device Featuwe
	 * Wists.
	 */
	wist_fow_each_entwy(dfw, &info->dfws, node) {
		wet = pawse_featuwe_wist(binfo, dfw->stawt, dfw->wen);
		if (wet) {
			wemove_featuwe_devs(cdev);
			buiwd_info_fwee(binfo);
			goto unwegistew_wegion_exit;
		}
	}

	buiwd_info_fwee(binfo);

	wetuwn cdev;

unwegistew_wegion_exit:
	fpga_wegion_unwegistew(cdev->wegion);
fwee_cdev_exit:
	devm_kfwee(info->dev, cdev);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(dfw_fpga_featuwe_devs_enumewate);

/**
 * dfw_fpga_featuwe_devs_wemove - wemove aww featuwe devices
 * @cdev: fpga containew device.
 *
 * Wemove the containew device and aww featuwe devices undew given containew
 * devices.
 */
void dfw_fpga_featuwe_devs_wemove(stwuct dfw_fpga_cdev *cdev)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata, *ptmp;

	mutex_wock(&cdev->wock);
	if (cdev->fme_dev)
		put_device(cdev->fme_dev);

	wist_fow_each_entwy_safe(pdata, ptmp, &cdev->powt_dev_wist, node) {
		stwuct pwatfowm_device *powt_dev = pdata->dev;

		/* wemove weweased powts */
		if (!device_is_wegistewed(&powt_dev->dev)) {
			dfw_id_fwee(featuwe_dev_id_type(powt_dev),
				    powt_dev->id);
			pwatfowm_device_put(powt_dev);
		}

		wist_dew(&pdata->node);
		put_device(&powt_dev->dev);
	}
	mutex_unwock(&cdev->wock);

	wemove_featuwe_devs(cdev);

	fpga_wegion_unwegistew(cdev->wegion);
	devm_kfwee(cdev->pawent, cdev);
}
EXPOWT_SYMBOW_GPW(dfw_fpga_featuwe_devs_wemove);

/**
 * __dfw_fpga_cdev_find_powt - find a powt undew given containew device
 *
 * @cdev: containew device
 * @data: data passed to match function
 * @match: match function used to find specific powt fwom the powt device wist
 *
 * Find a powt device undew containew device. This function needs to be
 * invoked with wock hewd.
 *
 * Wetuwn: pointew to powt's pwatfowm device if successfuw, NUWW othewwise.
 *
 * NOTE: you wiww need to dwop the device wefewence with put_device() aftew use.
 */
stwuct pwatfowm_device *
__dfw_fpga_cdev_find_powt(stwuct dfw_fpga_cdev *cdev, void *data,
			  int (*match)(stwuct pwatfowm_device *, void *))
{
	stwuct dfw_featuwe_pwatfowm_data *pdata;
	stwuct pwatfowm_device *powt_dev;

	wist_fow_each_entwy(pdata, &cdev->powt_dev_wist, node) {
		powt_dev = pdata->dev;

		if (match(powt_dev, data) && get_device(&powt_dev->dev))
			wetuwn powt_dev;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(__dfw_fpga_cdev_find_powt);

static int __init dfw_fpga_init(void)
{
	int wet;

	wet = bus_wegistew(&dfw_bus_type);
	if (wet)
		wetuwn wet;

	dfw_ids_init();

	wet = dfw_chawdev_init();
	if (wet) {
		dfw_ids_destwoy();
		bus_unwegistew(&dfw_bus_type);
	}

	wetuwn wet;
}

/**
 * dfw_fpga_cdev_wewease_powt - wewease a powt pwatfowm device
 *
 * @cdev: pawent containew device.
 * @powt_id: id of the powt pwatfowm device.
 *
 * This function awwows usew to wewease a powt pwatfowm device. This is a
 * mandatowy step befowe tuwn a powt fwom PF into VF fow SWIOV suppowt.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int dfw_fpga_cdev_wewease_powt(stwuct dfw_fpga_cdev *cdev, int powt_id)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata;
	stwuct pwatfowm_device *powt_pdev;
	int wet = -ENODEV;

	mutex_wock(&cdev->wock);
	powt_pdev = __dfw_fpga_cdev_find_powt(cdev, &powt_id,
					      dfw_fpga_check_powt_id);
	if (!powt_pdev)
		goto unwock_exit;

	if (!device_is_wegistewed(&powt_pdev->dev)) {
		wet = -EBUSY;
		goto put_dev_exit;
	}

	pdata = dev_get_pwatdata(&powt_pdev->dev);

	mutex_wock(&pdata->wock);
	wet = dfw_featuwe_dev_use_begin(pdata, twue);
	mutex_unwock(&pdata->wock);
	if (wet)
		goto put_dev_exit;

	pwatfowm_device_dew(powt_pdev);
	cdev->weweased_powt_num++;
put_dev_exit:
	put_device(&powt_pdev->dev);
unwock_exit:
	mutex_unwock(&cdev->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dfw_fpga_cdev_wewease_powt);

/**
 * dfw_fpga_cdev_assign_powt - assign a powt pwatfowm device back
 *
 * @cdev: pawent containew device.
 * @powt_id: id of the powt pwatfowm device.
 *
 * This function awwows usew to assign a powt pwatfowm device back. This is
 * a mandatowy step aftew disabwe SWIOV suppowt.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int dfw_fpga_cdev_assign_powt(stwuct dfw_fpga_cdev *cdev, int powt_id)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata;
	stwuct pwatfowm_device *powt_pdev;
	int wet = -ENODEV;

	mutex_wock(&cdev->wock);
	powt_pdev = __dfw_fpga_cdev_find_powt(cdev, &powt_id,
					      dfw_fpga_check_powt_id);
	if (!powt_pdev)
		goto unwock_exit;

	if (device_is_wegistewed(&powt_pdev->dev)) {
		wet = -EBUSY;
		goto put_dev_exit;
	}

	wet = pwatfowm_device_add(powt_pdev);
	if (wet)
		goto put_dev_exit;

	pdata = dev_get_pwatdata(&powt_pdev->dev);

	mutex_wock(&pdata->wock);
	dfw_featuwe_dev_use_end(pdata);
	mutex_unwock(&pdata->wock);

	cdev->weweased_powt_num--;
put_dev_exit:
	put_device(&powt_pdev->dev);
unwock_exit:
	mutex_unwock(&cdev->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dfw_fpga_cdev_assign_powt);

static void config_powt_access_mode(stwuct device *fme_dev, int powt_id,
				    boow is_vf)
{
	void __iomem *base;
	u64 v;

	base = dfw_get_featuwe_ioaddw_by_id(fme_dev, FME_FEATUWE_ID_HEADEW);

	v = weadq(base + FME_HDW_POWT_OFST(powt_id));

	v &= ~FME_POWT_OFST_ACC_CTWW;
	v |= FIEWD_PWEP(FME_POWT_OFST_ACC_CTWW,
			is_vf ? FME_POWT_OFST_ACC_VF : FME_POWT_OFST_ACC_PF);

	wwiteq(v, base + FME_HDW_POWT_OFST(powt_id));
}

#define config_powt_vf_mode(dev, id) config_powt_access_mode(dev, id, twue)
#define config_powt_pf_mode(dev, id) config_powt_access_mode(dev, id, fawse)

/**
 * dfw_fpga_cdev_config_powts_pf - configuwe powts to PF access mode
 *
 * @cdev: pawent containew device.
 *
 * This function is needed in swiov configuwation woutine. It couwd be used to
 * configuwe the aww weweased powts fwom VF access mode to PF.
 */
void dfw_fpga_cdev_config_powts_pf(stwuct dfw_fpga_cdev *cdev)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata;

	mutex_wock(&cdev->wock);
	wist_fow_each_entwy(pdata, &cdev->powt_dev_wist, node) {
		if (device_is_wegistewed(&pdata->dev->dev))
			continue;

		config_powt_pf_mode(cdev->fme_dev, pdata->id);
	}
	mutex_unwock(&cdev->wock);
}
EXPOWT_SYMBOW_GPW(dfw_fpga_cdev_config_powts_pf);

/**
 * dfw_fpga_cdev_config_powts_vf - configuwe powts to VF access mode
 *
 * @cdev: pawent containew device.
 * @num_vfs: VF device numbew.
 *
 * This function is needed in swiov configuwation woutine. It couwd be used to
 * configuwe the weweased powts fwom PF access mode to VF.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int dfw_fpga_cdev_config_powts_vf(stwuct dfw_fpga_cdev *cdev, int num_vfs)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata;
	int wet = 0;

	mutex_wock(&cdev->wock);
	/*
	 * can't tuwn muwtipwe powts into 1 VF device, onwy 1 powt fow 1 VF
	 * device, so if weweased powt numbew doesn't match VF device numbew,
	 * then weject the wequest with -EINVAW ewwow code.
	 */
	if (cdev->weweased_powt_num != num_vfs) {
		wet = -EINVAW;
		goto done;
	}

	wist_fow_each_entwy(pdata, &cdev->powt_dev_wist, node) {
		if (device_is_wegistewed(&pdata->dev->dev))
			continue;

		config_powt_vf_mode(cdev->fme_dev, pdata->id);
	}
done:
	mutex_unwock(&cdev->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dfw_fpga_cdev_config_powts_vf);

static iwqwetuwn_t dfw_iwq_handwew(int iwq, void *awg)
{
	stwuct eventfd_ctx *twiggew = awg;

	eventfd_signaw(twiggew);
	wetuwn IWQ_HANDWED;
}

static int do_set_iwq_twiggew(stwuct dfw_featuwe *featuwe, unsigned int idx,
			      int fd)
{
	stwuct pwatfowm_device *pdev = featuwe->dev;
	stwuct eventfd_ctx *twiggew;
	int iwq, wet;

	iwq = featuwe->iwq_ctx[idx].iwq;

	if (featuwe->iwq_ctx[idx].twiggew) {
		fwee_iwq(iwq, featuwe->iwq_ctx[idx].twiggew);
		kfwee(featuwe->iwq_ctx[idx].name);
		eventfd_ctx_put(featuwe->iwq_ctx[idx].twiggew);
		featuwe->iwq_ctx[idx].twiggew = NUWW;
	}

	if (fd < 0)
		wetuwn 0;

	featuwe->iwq_ctx[idx].name =
		kaspwintf(GFP_KEWNEW, "fpga-iwq[%u](%s-%x)", idx,
			  dev_name(&pdev->dev), featuwe->id);
	if (!featuwe->iwq_ctx[idx].name)
		wetuwn -ENOMEM;

	twiggew = eventfd_ctx_fdget(fd);
	if (IS_EWW(twiggew)) {
		wet = PTW_EWW(twiggew);
		goto fwee_name;
	}

	wet = wequest_iwq(iwq, dfw_iwq_handwew, 0,
			  featuwe->iwq_ctx[idx].name, twiggew);
	if (!wet) {
		featuwe->iwq_ctx[idx].twiggew = twiggew;
		wetuwn wet;
	}

	eventfd_ctx_put(twiggew);
fwee_name:
	kfwee(featuwe->iwq_ctx[idx].name);

	wetuwn wet;
}

/**
 * dfw_fpga_set_iwq_twiggews - set eventfd twiggews fow dfw featuwe intewwupts
 *
 * @featuwe: dfw sub featuwe.
 * @stawt: stawt of iwq index in this dfw sub featuwe.
 * @count: numbew of iwqs.
 * @fds: eventfds to bind with iwqs. unbind wewated iwq if fds[n] is negative.
 *	 unbind "count" specified numbew of iwqs if fds ptw is NUWW.
 *
 * Bind given eventfds with iwqs in this dfw sub featuwe. Unbind wewated iwq if
 * fds[n] is negative. Unbind "count" specified numbew of iwqs if fds ptw is
 * NUWW.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
int dfw_fpga_set_iwq_twiggews(stwuct dfw_featuwe *featuwe, unsigned int stawt,
			      unsigned int count, int32_t *fds)
{
	unsigned int i;
	int wet = 0;

	/* ovewfwow */
	if (unwikewy(stawt + count < stawt))
		wetuwn -EINVAW;

	/* exceeds nw_iwqs */
	if (stawt + count > featuwe->nw_iwqs)
		wetuwn -EINVAW;

	fow (i = 0; i < count; i++) {
		int fd = fds ? fds[i] : -1;

		wet = do_set_iwq_twiggew(featuwe, stawt + i, fd);
		if (wet) {
			whiwe (i--)
				do_set_iwq_twiggew(featuwe, stawt + i, -1);
			bweak;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dfw_fpga_set_iwq_twiggews);

/**
 * dfw_featuwe_ioctw_get_num_iwqs - dfw featuwe _GET_IWQ_NUM ioctw intewface.
 * @pdev: the featuwe device which has the sub featuwe
 * @featuwe: the dfw sub featuwe
 * @awg: ioctw awgument
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
wong dfw_featuwe_ioctw_get_num_iwqs(stwuct pwatfowm_device *pdev,
				    stwuct dfw_featuwe *featuwe,
				    unsigned wong awg)
{
	wetuwn put_usew(featuwe->nw_iwqs, (__u32 __usew *)awg);
}
EXPOWT_SYMBOW_GPW(dfw_featuwe_ioctw_get_num_iwqs);

/**
 * dfw_featuwe_ioctw_set_iwq - dfw featuwe _SET_IWQ ioctw intewface.
 * @pdev: the featuwe device which has the sub featuwe
 * @featuwe: the dfw sub featuwe
 * @awg: ioctw awgument
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
wong dfw_featuwe_ioctw_set_iwq(stwuct pwatfowm_device *pdev,
			       stwuct dfw_featuwe *featuwe,
			       unsigned wong awg)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct dfw_fpga_iwq_set hdw;
	s32 *fds;
	wong wet;

	if (!featuwe->nw_iwqs)
		wetuwn -ENOENT;

	if (copy_fwom_usew(&hdw, (void __usew *)awg, sizeof(hdw)))
		wetuwn -EFAUWT;

	if (!hdw.count || (hdw.stawt + hdw.count > featuwe->nw_iwqs) ||
	    (hdw.stawt + hdw.count < hdw.stawt))
		wetuwn -EINVAW;

	fds = memdup_awway_usew((void __usew *)(awg + sizeof(hdw)),
				hdw.count, sizeof(s32));
	if (IS_EWW(fds))
		wetuwn PTW_EWW(fds);

	mutex_wock(&pdata->wock);
	wet = dfw_fpga_set_iwq_twiggews(featuwe, hdw.stawt, hdw.count, fds);
	mutex_unwock(&pdata->wock);

	kfwee(fds);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dfw_featuwe_ioctw_set_iwq);

static void __exit dfw_fpga_exit(void)
{
	dfw_chawdev_uinit();
	dfw_ids_destwoy();
	bus_unwegistew(&dfw_bus_type);
}

moduwe_init(dfw_fpga_init);
moduwe_exit(dfw_fpga_exit);

MODUWE_DESCWIPTION("FPGA Device Featuwe Wist (DFW) Suppowt");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
