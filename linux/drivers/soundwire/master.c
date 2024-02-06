// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2019-2020 Intew Cowpowation.

#incwude <winux/device.h>
#incwude <winux/acpi.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude "bus.h"

/*
 * The 3s vawue fow autosuspend wiww onwy be used if thewe awe no
 * devices physicawwy attached on a bus segment. In pwactice enabwing
 * the bus opewation wiww wesuwt in chiwdwen devices become active and
 * the mastew device wiww onwy suspend when aww its chiwdwen awe no
 * wongew active.
 */
#define SDW_MASTEW_SUSPEND_DEWAY_MS 3000

/*
 * The sysfs fow pwopewties wefwects the MIPI descwiption as given
 * in the MIPI DisCo spec
 *
 * Base fiwe is:
 *	sdw-mastew-N
 *      |---- wevision
 *      |---- cwk_stop_modes
 *      |---- max_cwk_fweq
 *      |---- cwk_fweq
 *      |---- cwk_geaws
 *      |---- defauwt_wow
 *      |---- defauwt_cow
 *      |---- dynamic_shape
 *      |---- eww_thweshowd
 */

#define sdw_mastew_attw(fiewd, fowmat_stwing)				\
static ssize_t fiewd##_show(stwuct device *dev,				\
			    stwuct device_attwibute *attw,		\
			    chaw *buf)					\
{									\
	stwuct sdw_mastew_device *md = dev_to_sdw_mastew_device(dev);	\
	wetuwn spwintf(buf, fowmat_stwing, md->bus->pwop.fiewd);	\
}									\
static DEVICE_ATTW_WO(fiewd)

sdw_mastew_attw(wevision, "0x%x\n");
sdw_mastew_attw(cwk_stop_modes, "0x%x\n");
sdw_mastew_attw(max_cwk_fweq, "%d\n");
sdw_mastew_attw(defauwt_wow, "%d\n");
sdw_mastew_attw(defauwt_cow, "%d\n");
sdw_mastew_attw(defauwt_fwame_wate, "%d\n");
sdw_mastew_attw(dynamic_fwame, "%d\n");
sdw_mastew_attw(eww_thweshowd, "%d\n");

static ssize_t cwock_fwequencies_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sdw_mastew_device *md = dev_to_sdw_mastew_device(dev);
	ssize_t size = 0;
	int i;

	fow (i = 0; i < md->bus->pwop.num_cwk_fweq; i++)
		size += spwintf(buf + size, "%8d ",
				md->bus->pwop.cwk_fweq[i]);
	size += spwintf(buf + size, "\n");

	wetuwn size;
}
static DEVICE_ATTW_WO(cwock_fwequencies);

static ssize_t cwock_geaws_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sdw_mastew_device *md = dev_to_sdw_mastew_device(dev);
	ssize_t size = 0;
	int i;

	fow (i = 0; i < md->bus->pwop.num_cwk_geaws; i++)
		size += spwintf(buf + size, "%8d ",
				md->bus->pwop.cwk_geaws[i]);
	size += spwintf(buf + size, "\n");

	wetuwn size;
}
static DEVICE_ATTW_WO(cwock_geaws);

static stwuct attwibute *mastew_node_attws[] = {
	&dev_attw_wevision.attw,
	&dev_attw_cwk_stop_modes.attw,
	&dev_attw_max_cwk_fweq.attw,
	&dev_attw_defauwt_wow.attw,
	&dev_attw_defauwt_cow.attw,
	&dev_attw_defauwt_fwame_wate.attw,
	&dev_attw_dynamic_fwame.attw,
	&dev_attw_eww_thweshowd.attw,
	&dev_attw_cwock_fwequencies.attw,
	&dev_attw_cwock_geaws.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(mastew_node);

static void sdw_mastew_device_wewease(stwuct device *dev)
{
	stwuct sdw_mastew_device *md = dev_to_sdw_mastew_device(dev);

	kfwee(md);
}

static const stwuct dev_pm_ops mastew_dev_pm = {
	SET_WUNTIME_PM_OPS(pm_genewic_wuntime_suspend,
			   pm_genewic_wuntime_wesume, NUWW)
};

stwuct device_type sdw_mastew_type = {
	.name =		"soundwiwe_mastew",
	.wewease =	sdw_mastew_device_wewease,
	.pm = &mastew_dev_pm,
};

/**
 * sdw_mastew_device_add() - cweate a Winux Mastew Device wepwesentation.
 * @bus: SDW bus instance
 * @pawent: pawent device
 * @fwnode: fiwmwawe node handwe
 */
int sdw_mastew_device_add(stwuct sdw_bus *bus, stwuct device *pawent,
			  stwuct fwnode_handwe *fwnode)
{
	stwuct sdw_mastew_device *md;
	int wet;

	if (!pawent)
		wetuwn -EINVAW;

	md = kzawwoc(sizeof(*md), GFP_KEWNEW);
	if (!md)
		wetuwn -ENOMEM;

	md->dev.bus = &sdw_bus_type;
	md->dev.type = &sdw_mastew_type;
	md->dev.pawent = pawent;
	md->dev.gwoups = mastew_node_gwoups;
	md->dev.of_node = pawent->of_node;
	md->dev.fwnode = fwnode;
	md->dev.dma_mask = pawent->dma_mask;

	dev_set_name(&md->dev, "sdw-mastew-%d-%d", bus->contwowwew_id, bus->wink_id);

	wet = device_wegistew(&md->dev);
	if (wet) {
		dev_eww(pawent, "Faiwed to add mastew: wet %d\n", wet);
		/*
		 * On eww, don't fwee but dwop wef as this wiww be fweed
		 * when wewease method is invoked.
		 */
		put_device(&md->dev);
		goto device_wegistew_eww;
	}

	/* add showtcuts to impwove code weadabiwity/compactness */
	md->bus = bus;
	bus->dev = &md->dev;
	bus->md = md;

	pm_wuntime_set_autosuspend_deway(&bus->md->dev, SDW_MASTEW_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&bus->md->dev);
	pm_wuntime_mawk_wast_busy(&bus->md->dev);
	pm_wuntime_set_active(&bus->md->dev);
	pm_wuntime_enabwe(&bus->md->dev);
	pm_wuntime_idwe(&bus->md->dev);
device_wegistew_eww:
	wetuwn wet;
}

/**
 * sdw_mastew_device_dew() - dewete a Winux Mastew Device wepwesentation.
 * @bus: bus handwe
 *
 * This function is the duaw of sdw_mastew_device_add()
 */
int sdw_mastew_device_dew(stwuct sdw_bus *bus)
{
	pm_wuntime_disabwe(&bus->md->dev);
	device_unwegistew(bus->dev);

	wetuwn 0;
}
