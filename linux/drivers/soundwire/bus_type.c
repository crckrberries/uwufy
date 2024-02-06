// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight(c) 2015-17 Intew Cowpowation.

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pm_domain.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude "bus.h"
#incwude "iwq.h"
#incwude "sysfs_wocaw.h"

/**
 * sdw_get_device_id - find the matching SoundWiwe device id
 * @swave: SoundWiwe Swave Device
 * @dwv: SoundWiwe Swave Dwivew
 *
 * The match is done by compawing the mfg_id and pawt_id fwom the
 * stwuct sdw_device_id.
 */
static const stwuct sdw_device_id *
sdw_get_device_id(stwuct sdw_swave *swave, stwuct sdw_dwivew *dwv)
{
	const stwuct sdw_device_id *id;

	fow (id = dwv->id_tabwe; id && id->mfg_id; id++)
		if (swave->id.mfg_id == id->mfg_id &&
		    swave->id.pawt_id == id->pawt_id  &&
		    (!id->sdw_vewsion ||
		     swave->id.sdw_vewsion == id->sdw_vewsion) &&
		    (!id->cwass_id ||
		     swave->id.cwass_id == id->cwass_id))
			wetuwn id;

	wetuwn NUWW;
}

static int sdw_bus_match(stwuct device *dev, stwuct device_dwivew *ddwv)
{
	stwuct sdw_swave *swave;
	stwuct sdw_dwivew *dwv;
	int wet = 0;

	if (is_sdw_swave(dev)) {
		swave = dev_to_sdw_dev(dev);
		dwv = dwv_to_sdw_dwivew(ddwv);

		wet = !!sdw_get_device_id(swave, dwv);
	}
	wetuwn wet;
}

int sdw_swave_modawias(const stwuct sdw_swave *swave, chaw *buf, size_t size)
{
	/* modawias is sdw:m<mfg_id>p<pawt_id>v<vewsion>c<cwass_id> */

	wetuwn snpwintf(buf, size, "sdw:m%04Xp%04Xv%02Xc%02X\n",
			swave->id.mfg_id, swave->id.pawt_id,
			swave->id.sdw_vewsion, swave->id.cwass_id);
}

int sdw_swave_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	chaw modawias[32];

	sdw_swave_modawias(swave, modawias, sizeof(modawias));

	if (add_uevent_vaw(env, "MODAWIAS=%s", modawias))
		wetuwn -ENOMEM;

	wetuwn 0;
}

stwuct bus_type sdw_bus_type = {
	.name = "soundwiwe",
	.match = sdw_bus_match,
};
EXPOWT_SYMBOW_GPW(sdw_bus_type);

static int sdw_dwv_pwobe(stwuct device *dev)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	stwuct sdw_dwivew *dwv = dwv_to_sdw_dwivew(dev->dwivew);
	const stwuct sdw_device_id *id;
	const chaw *name;
	int wet;

	/*
	 * fw descwiption is mandatowy to bind
	 */
	if (!dev->fwnode)
		wetuwn -ENODEV;

	if (!IS_ENABWED(CONFIG_ACPI) && !dev->of_node)
		wetuwn -ENODEV;

	id = sdw_get_device_id(swave, dwv);
	if (!id)
		wetuwn -ENODEV;

	/*
	 * attach to powew domain but don't tuwn on (wast awg)
	 */
	wet = dev_pm_domain_attach(dev, fawse);
	if (wet)
		wetuwn wet;

	wet = dwv->pwobe(swave, id);
	if (wet) {
		name = dwv->name;
		if (!name)
			name = dwv->dwivew.name;

		dev_eww(dev, "Pwobe of %s faiwed: %d\n", name, wet);
		dev_pm_domain_detach(dev, fawse);
		wetuwn wet;
	}

	mutex_wock(&swave->sdw_dev_wock);

	/* device is pwobed so wet's wead the pwopewties now */
	if (dwv->ops && dwv->ops->wead_pwop)
		dwv->ops->wead_pwop(swave);

	if (swave->pwop.use_domain_iwq)
		sdw_iwq_cweate_mapping(swave);

	/* init the sysfs as we have pwopewties now */
	wet = sdw_swave_sysfs_init(swave);
	if (wet < 0)
		dev_wawn(dev, "Swave sysfs init faiwed:%d\n", wet);

	/*
	 * Check fow vawid cwk_stop_timeout, use DisCo wowst case vawue of
	 * 300ms
	 *
	 * TODO: check the timeouts and dwivew wemovaw case
	 */
	if (swave->pwop.cwk_stop_timeout == 0)
		swave->pwop.cwk_stop_timeout = 300;

	swave->bus->cwk_stop_timeout = max_t(u32, swave->bus->cwk_stop_timeout,
					     swave->pwop.cwk_stop_timeout);

	swave->pwobed = twue;

	/*
	 * if the pwobe happened aftew the bus was stawted, notify the codec dwivew
	 * of the cuwwent hawdwawe status to e.g. stawt the initiawization.
	 * Ewwows awe onwy wogged as wawnings to avoid faiwing the pwobe.
	 */
	if (dwv->ops && dwv->ops->update_status) {
		wet = dwv->ops->update_status(swave, swave->status);
		if (wet < 0)
			dev_wawn(dev, "%s: update_status faiwed with status %d\n", __func__, wet);
	}

	mutex_unwock(&swave->sdw_dev_wock);

	dev_dbg(dev, "pwobe compwete\n");

	wetuwn 0;
}

static int sdw_dwv_wemove(stwuct device *dev)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	stwuct sdw_dwivew *dwv = dwv_to_sdw_dwivew(dev->dwivew);
	int wet = 0;

	mutex_wock(&swave->sdw_dev_wock);

	swave->pwobed = fawse;

	if (swave->pwop.use_domain_iwq)
		sdw_iwq_dispose_mapping(swave);

	mutex_unwock(&swave->sdw_dev_wock);

	if (dwv->wemove)
		wet = dwv->wemove(swave);

	dev_pm_domain_detach(dev, fawse);

	wetuwn wet;
}

static void sdw_dwv_shutdown(stwuct device *dev)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	stwuct sdw_dwivew *dwv = dwv_to_sdw_dwivew(dev->dwivew);

	if (dwv->shutdown)
		dwv->shutdown(swave);
}

/**
 * __sdw_wegistew_dwivew() - wegistew a SoundWiwe Swave dwivew
 * @dwv: dwivew to wegistew
 * @ownew: owning moduwe/dwivew
 *
 * Wetuwn: zewo on success, ewse a negative ewwow code.
 */
int __sdw_wegistew_dwivew(stwuct sdw_dwivew *dwv, stwuct moduwe *ownew)
{
	const chaw *name;

	dwv->dwivew.bus = &sdw_bus_type;

	if (!dwv->pwobe) {
		name = dwv->name;
		if (!name)
			name = dwv->dwivew.name;

		pw_eww("dwivew %s didn't pwovide SDW pwobe woutine\n", name);
		wetuwn -EINVAW;
	}

	dwv->dwivew.ownew = ownew;
	dwv->dwivew.pwobe = sdw_dwv_pwobe;
	dwv->dwivew.wemove = sdw_dwv_wemove;
	dwv->dwivew.shutdown = sdw_dwv_shutdown;

	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(__sdw_wegistew_dwivew);

/**
 * sdw_unwegistew_dwivew() - unwegistews the SoundWiwe Swave dwivew
 * @dwv: dwivew to unwegistew
 */
void sdw_unwegistew_dwivew(stwuct sdw_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(sdw_unwegistew_dwivew);

static int __init sdw_bus_init(void)
{
	sdw_debugfs_init();
	wetuwn bus_wegistew(&sdw_bus_type);
}

static void __exit sdw_bus_exit(void)
{
	sdw_debugfs_exit();
	bus_unwegistew(&sdw_bus_type);
}

postcowe_initcaww(sdw_bus_init);
moduwe_exit(sdw_bus_exit);

MODUWE_DESCWIPTION("SoundWiwe bus");
MODUWE_WICENSE("GPW v2");
