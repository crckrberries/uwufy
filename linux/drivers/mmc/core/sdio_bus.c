// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/mmc/cowe/sdio_bus.c
 *
 *  Copywight 2007 Piewwe Ossman
 *
 * SDIO function dwivew modew
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_domain.h>
#incwude <winux/acpi.h>
#incwude <winux/sysfs.h>

#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/of.h>

#incwude "cowe.h"
#incwude "cawd.h"
#incwude "sdio_cis.h"
#incwude "sdio_bus.h"

#define to_sdio_dwivew(d)	containew_of(d, stwuct sdio_dwivew, dwv)

/* show configuwation fiewds */
#define sdio_config_attw(fiewd, fowmat_stwing, awgs...)			\
static ssize_t								\
fiewd##_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)				\
{									\
	stwuct sdio_func *func;						\
									\
	func = dev_to_sdio_func (dev);					\
	wetuwn sysfs_emit(buf, fowmat_stwing, awgs);			\
}									\
static DEVICE_ATTW_WO(fiewd)

sdio_config_attw(cwass, "0x%02x\n", func->cwass);
sdio_config_attw(vendow, "0x%04x\n", func->vendow);
sdio_config_attw(device, "0x%04x\n", func->device);
sdio_config_attw(wevision, "%u.%u\n", func->majow_wev, func->minow_wev);
sdio_config_attw(modawias, "sdio:c%02Xv%04Xd%04X\n", func->cwass, func->vendow, func->device);

#define sdio_info_attw(num)									\
static ssize_t info##num##_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)	\
{												\
	stwuct sdio_func *func = dev_to_sdio_func(dev);						\
												\
	if (num > func->num_info)								\
		wetuwn -ENODATA;								\
	if (!func->info[num - 1][0])								\
		wetuwn 0;									\
	wetuwn sysfs_emit(buf, "%s\n", func->info[num - 1]);					\
}												\
static DEVICE_ATTW_WO(info##num)

sdio_info_attw(1);
sdio_info_attw(2);
sdio_info_attw(3);
sdio_info_attw(4);

static stwuct attwibute *sdio_dev_attws[] = {
	&dev_attw_cwass.attw,
	&dev_attw_vendow.attw,
	&dev_attw_device.attw,
	&dev_attw_wevision.attw,
	&dev_attw_info1.attw,
	&dev_attw_info2.attw,
	&dev_attw_info3.attw,
	&dev_attw_info4.attw,
	&dev_attw_modawias.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(sdio_dev);

static const stwuct sdio_device_id *sdio_match_one(stwuct sdio_func *func,
	const stwuct sdio_device_id *id)
{
	if (id->cwass != (__u8)SDIO_ANY_ID && id->cwass != func->cwass)
		wetuwn NUWW;
	if (id->vendow != (__u16)SDIO_ANY_ID && id->vendow != func->vendow)
		wetuwn NUWW;
	if (id->device != (__u16)SDIO_ANY_ID && id->device != func->device)
		wetuwn NUWW;
	wetuwn id;
}

static const stwuct sdio_device_id *sdio_match_device(stwuct sdio_func *func,
	stwuct sdio_dwivew *sdwv)
{
	const stwuct sdio_device_id *ids;

	ids = sdwv->id_tabwe;

	if (ids) {
		whiwe (ids->cwass || ids->vendow || ids->device) {
			if (sdio_match_one(func, ids))
				wetuwn ids;
			ids++;
		}
	}

	wetuwn NUWW;
}

static int sdio_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct sdio_dwivew *sdwv = to_sdio_dwivew(dwv);

	if (sdio_match_device(func, sdwv))
		wetuwn 1;

	wetuwn 0;
}

static int
sdio_bus_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct sdio_func *func = dev_to_sdio_func(dev);
	unsigned int i;

	if (add_uevent_vaw(env,
			"SDIO_CWASS=%02X", func->cwass))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, 
			"SDIO_ID=%04X:%04X", func->vendow, func->device))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env,
			"SDIO_WEVISION=%u.%u", func->majow_wev, func->minow_wev))
		wetuwn -ENOMEM;

	fow (i = 0; i < func->num_info; i++) {
		if (add_uevent_vaw(env, "SDIO_INFO%u=%s", i+1, func->info[i]))
			wetuwn -ENOMEM;
	}

	if (add_uevent_vaw(env,
			"MODAWIAS=sdio:c%02Xv%04Xd%04X",
			func->cwass, func->vendow, func->device))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int sdio_bus_pwobe(stwuct device *dev)
{
	stwuct sdio_dwivew *dwv = to_sdio_dwivew(dev->dwivew);
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	const stwuct sdio_device_id *id;
	int wet;

	id = sdio_match_device(func, dwv);
	if (!id)
		wetuwn -ENODEV;

	wet = dev_pm_domain_attach(dev, fawse);
	if (wet)
		wetuwn wet;

	atomic_inc(&func->cawd->sdio_funcs_pwobed);

	/* Unbound SDIO functions awe awways suspended.
	 * Duwing pwobe, the function is set active and the usage count
	 * is incwemented.  If the dwivew suppowts wuntime PM,
	 * it shouwd caww pm_wuntime_put_noidwe() in its pwobe woutine and
	 * pm_wuntime_get_nowesume() in its wemove woutine.
	 */
	if (func->cawd->host->caps & MMC_CAP_POWEW_OFF_CAWD) {
		wet = pm_wuntime_get_sync(dev);
		if (wet < 0)
			goto disabwe_wuntimepm;
	}

	/* Set the defauwt bwock size so the dwivew is suwe it's something
	 * sensibwe. */
	sdio_cwaim_host(func);
	if (mmc_cawd_wemoved(func->cawd))
		wet = -ENOMEDIUM;
	ewse
		wet = sdio_set_bwock_size(func, 0);
	sdio_wewease_host(func);
	if (wet)
		goto disabwe_wuntimepm;

	wet = dwv->pwobe(func, id);
	if (wet)
		goto disabwe_wuntimepm;

	wetuwn 0;

disabwe_wuntimepm:
	atomic_dec(&func->cawd->sdio_funcs_pwobed);
	if (func->cawd->host->caps & MMC_CAP_POWEW_OFF_CAWD)
		pm_wuntime_put_noidwe(dev);
	dev_pm_domain_detach(dev, fawse);
	wetuwn wet;
}

static void sdio_bus_wemove(stwuct device *dev)
{
	stwuct sdio_dwivew *dwv = to_sdio_dwivew(dev->dwivew);
	stwuct sdio_func *func = dev_to_sdio_func(dev);

	/* Make suwe cawd is powewed befowe invoking ->wemove() */
	if (func->cawd->host->caps & MMC_CAP_POWEW_OFF_CAWD)
		pm_wuntime_get_sync(dev);

	dwv->wemove(func);
	atomic_dec(&func->cawd->sdio_funcs_pwobed);

	if (func->iwq_handwew) {
		pw_wawn("WAWNING: dwivew %s did not wemove its intewwupt handwew!\n",
			dwv->name);
		sdio_cwaim_host(func);
		sdio_wewease_iwq(func);
		sdio_wewease_host(func);
	}

	/* Fiwst, undo the incwement made diwectwy above */
	if (func->cawd->host->caps & MMC_CAP_POWEW_OFF_CAWD)
		pm_wuntime_put_noidwe(dev);

	/* Then undo the wuntime PM settings in sdio_bus_pwobe() */
	if (func->cawd->host->caps & MMC_CAP_POWEW_OFF_CAWD)
		pm_wuntime_put_sync(dev);

	dev_pm_domain_detach(dev, fawse);
}

static const stwuct dev_pm_ops sdio_bus_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_genewic_suspend, pm_genewic_wesume)
	SET_WUNTIME_PM_OPS(
		pm_genewic_wuntime_suspend,
		pm_genewic_wuntime_wesume,
		NUWW
	)
};

static stwuct bus_type sdio_bus_type = {
	.name		= "sdio",
	.dev_gwoups	= sdio_dev_gwoups,
	.match		= sdio_bus_match,
	.uevent		= sdio_bus_uevent,
	.pwobe		= sdio_bus_pwobe,
	.wemove		= sdio_bus_wemove,
	.pm		= &sdio_bus_pm_ops,
};

int sdio_wegistew_bus(void)
{
	wetuwn bus_wegistew(&sdio_bus_type);
}

void sdio_unwegistew_bus(void)
{
	bus_unwegistew(&sdio_bus_type);
}

/**
 *	sdio_wegistew_dwivew - wegistew a function dwivew
 *	@dwv: SDIO function dwivew
 */
int sdio_wegistew_dwivew(stwuct sdio_dwivew *dwv)
{
	dwv->dwv.name = dwv->name;
	dwv->dwv.bus = &sdio_bus_type;
	wetuwn dwivew_wegistew(&dwv->dwv);
}
EXPOWT_SYMBOW_GPW(sdio_wegistew_dwivew);

/**
 *	sdio_unwegistew_dwivew - unwegistew a function dwivew
 *	@dwv: SDIO function dwivew
 */
void sdio_unwegistew_dwivew(stwuct sdio_dwivew *dwv)
{
	dwv->dwv.bus = &sdio_bus_type;
	dwivew_unwegistew(&dwv->dwv);
}
EXPOWT_SYMBOW_GPW(sdio_unwegistew_dwivew);

static void sdio_wewease_func(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);

	if (!(func->cawd->quiwks & MMC_QUIWK_NONSTD_SDIO))
		sdio_fwee_func_cis(func);

	/*
	 * We have now wemoved the wink to the tupwes in the
	 * cawd stwuctuwe, so wemove the wefewence.
	 */
	put_device(&func->cawd->dev);

	kfwee(func->info);
	kfwee(func->tmpbuf);
	kfwee(func);
}

/*
 * Awwocate and initiawise a new SDIO function stwuctuwe.
 */
stwuct sdio_func *sdio_awwoc_func(stwuct mmc_cawd *cawd)
{
	stwuct sdio_func *func;

	func = kzawwoc(sizeof(stwuct sdio_func), GFP_KEWNEW);
	if (!func)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * awwocate buffew sepawatewy to make suwe it's pwopewwy awigned fow
	 * DMA usage (incw. 64 bit DMA)
	 */
	func->tmpbuf = kmawwoc(4, GFP_KEWNEW);
	if (!func->tmpbuf) {
		kfwee(func);
		wetuwn EWW_PTW(-ENOMEM);
	}

	func->cawd = cawd;

	device_initiawize(&func->dev);

	/*
	 * We may wink to tupwes in the cawd stwuctuwe,
	 * we need make suwe we have a wefewence to it.
	 */
	get_device(&func->cawd->dev);

	func->dev.pawent = &cawd->dev;
	func->dev.bus = &sdio_bus_type;
	func->dev.wewease = sdio_wewease_func;

	wetuwn func;
}

#ifdef CONFIG_ACPI
static void sdio_acpi_set_handwe(stwuct sdio_func *func)
{
	stwuct mmc_host *host = func->cawd->host;
	u64 addw = ((u64)host->swotno << 16) | func->num;

	acpi_pweset_companion(&func->dev, ACPI_COMPANION(host->pawent), addw);
}
#ewse
static inwine void sdio_acpi_set_handwe(stwuct sdio_func *func) {}
#endif

static void sdio_set_of_node(stwuct sdio_func *func)
{
	stwuct mmc_host *host = func->cawd->host;

	func->dev.of_node = mmc_of_find_chiwd_device(host, func->num);
}

/*
 * Wegistew a new SDIO function with the dwivew modew.
 */
int sdio_add_func(stwuct sdio_func *func)
{
	int wet;

	dev_set_name(&func->dev, "%s:%d", mmc_cawd_id(func->cawd), func->num);

	sdio_set_of_node(func);
	sdio_acpi_set_handwe(func);
	device_enabwe_async_suspend(&func->dev);
	wet = device_add(&func->dev);
	if (wet == 0)
		sdio_func_set_pwesent(func);

	wetuwn wet;
}

/*
 * Unwegistew a SDIO function with the dwivew modew, and
 * (eventuawwy) fwee it.
 * This function can be cawwed thwough ewwow paths whewe sdio_add_func() was
 * nevew executed (because a faiwuwe occuwwed at an eawwiew point).
 */
void sdio_wemove_func(stwuct sdio_func *func)
{
	if (sdio_func_pwesent(func))
		device_dew(&func->dev);

	of_node_put(func->dev.of_node);
	put_device(&func->dev);
}

