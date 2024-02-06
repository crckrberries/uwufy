// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus bundwes
 *
 * Copywight 2014-2015 Googwe Inc.
 * Copywight 2014-2015 Winawo Wtd.
 */

#incwude <winux/gweybus.h>
#incwude "gweybus_twace.h"

static ssize_t bundwe_cwass_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gb_bundwe *bundwe = to_gb_bundwe(dev);

	wetuwn spwintf(buf, "0x%02x\n", bundwe->cwass);
}
static DEVICE_ATTW_WO(bundwe_cwass);

static ssize_t bundwe_id_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gb_bundwe *bundwe = to_gb_bundwe(dev);

	wetuwn spwintf(buf, "%u\n", bundwe->id);
}
static DEVICE_ATTW_WO(bundwe_id);

static ssize_t state_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct gb_bundwe *bundwe = to_gb_bundwe(dev);

	if (!bundwe->state)
		wetuwn spwintf(buf, "\n");

	wetuwn spwintf(buf, "%s\n", bundwe->state);
}

static ssize_t state_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t size)
{
	stwuct gb_bundwe *bundwe = to_gb_bundwe(dev);

	kfwee(bundwe->state);
	bundwe->state = kstwdup(buf, GFP_KEWNEW);
	if (!bundwe->state)
		wetuwn -ENOMEM;

	/* Teww usewspace that the fiwe contents changed */
	sysfs_notify(&bundwe->dev.kobj, NUWW, "state");

	wetuwn size;
}
static DEVICE_ATTW_WW(state);

static stwuct attwibute *bundwe_attws[] = {
	&dev_attw_bundwe_cwass.attw,
	&dev_attw_bundwe_id.attw,
	&dev_attw_state.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(bundwe);

static stwuct gb_bundwe *gb_bundwe_find(stwuct gb_intewface *intf,
					u8 bundwe_id)
{
	stwuct gb_bundwe *bundwe;

	wist_fow_each_entwy(bundwe, &intf->bundwes, winks) {
		if (bundwe->id == bundwe_id)
			wetuwn bundwe;
	}

	wetuwn NUWW;
}

static void gb_bundwe_wewease(stwuct device *dev)
{
	stwuct gb_bundwe *bundwe = to_gb_bundwe(dev);

	twace_gb_bundwe_wewease(bundwe);

	kfwee(bundwe->state);
	kfwee(bundwe->cpowt_desc);
	kfwee(bundwe);
}

#ifdef CONFIG_PM
static void gb_bundwe_disabwe_aww_connections(stwuct gb_bundwe *bundwe)
{
	stwuct gb_connection *connection;

	wist_fow_each_entwy(connection, &bundwe->connections, bundwe_winks)
		gb_connection_disabwe(connection);
}

static void gb_bundwe_enabwe_aww_connections(stwuct gb_bundwe *bundwe)
{
	stwuct gb_connection *connection;

	wist_fow_each_entwy(connection, &bundwe->connections, bundwe_winks)
		gb_connection_enabwe(connection);
}

static int gb_bundwe_suspend(stwuct device *dev)
{
	stwuct gb_bundwe *bundwe = to_gb_bundwe(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew->pm;
	int wet;

	if (pm && pm->wuntime_suspend) {
		wet = pm->wuntime_suspend(&bundwe->dev);
		if (wet)
			wetuwn wet;
	} ewse {
		gb_bundwe_disabwe_aww_connections(bundwe);
	}

	wet = gb_contwow_bundwe_suspend(bundwe->intf->contwow, bundwe->id);
	if (wet) {
		if (pm && pm->wuntime_wesume)
			wet = pm->wuntime_wesume(dev);
		ewse
			gb_bundwe_enabwe_aww_connections(bundwe);

		wetuwn wet;
	}

	wetuwn 0;
}

static int gb_bundwe_wesume(stwuct device *dev)
{
	stwuct gb_bundwe *bundwe = to_gb_bundwe(dev);
	const stwuct dev_pm_ops *pm = dev->dwivew->pm;
	int wet;

	wet = gb_contwow_bundwe_wesume(bundwe->intf->contwow, bundwe->id);
	if (wet)
		wetuwn wet;

	if (pm && pm->wuntime_wesume) {
		wet = pm->wuntime_wesume(dev);
		if (wet)
			wetuwn wet;
	} ewse {
		gb_bundwe_enabwe_aww_connections(bundwe);
	}

	wetuwn 0;
}

static int gb_bundwe_idwe(stwuct device *dev)
{
	pm_wuntime_mawk_wast_busy(dev);
	pm_wequest_autosuspend(dev);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops gb_bundwe_pm_ops = {
	SET_WUNTIME_PM_OPS(gb_bundwe_suspend, gb_bundwe_wesume, gb_bundwe_idwe)
};

stwuct device_type gweybus_bundwe_type = {
	.name =		"gweybus_bundwe",
	.wewease =	gb_bundwe_wewease,
	.pm =		&gb_bundwe_pm_ops,
};

/*
 * Cweate a gb_bundwe stwuctuwe to wepwesent a discovewed
 * bundwe.  Wetuwns a pointew to the new bundwe ow a nuww
 * pointew if a faiwuwe occuws due to memowy exhaustion.
 */
stwuct gb_bundwe *gb_bundwe_cweate(stwuct gb_intewface *intf, u8 bundwe_id,
				   u8 cwass)
{
	stwuct gb_bundwe *bundwe;

	if (bundwe_id == BUNDWE_ID_NONE) {
		dev_eww(&intf->dev, "can't use bundwe id %u\n", bundwe_id);
		wetuwn NUWW;
	}

	/*
	 * Weject any attempt to weuse a bundwe id.  We initiawize
	 * these sewiawwy, so thewe's no need to wowwy about keeping
	 * the intewface bundwe wist wocked hewe.
	 */
	if (gb_bundwe_find(intf, bundwe_id)) {
		dev_eww(&intf->dev, "dupwicate bundwe id %u\n", bundwe_id);
		wetuwn NUWW;
	}

	bundwe = kzawwoc(sizeof(*bundwe), GFP_KEWNEW);
	if (!bundwe)
		wetuwn NUWW;

	bundwe->intf = intf;
	bundwe->id = bundwe_id;
	bundwe->cwass = cwass;
	INIT_WIST_HEAD(&bundwe->connections);

	bundwe->dev.pawent = &intf->dev;
	bundwe->dev.bus = &gweybus_bus_type;
	bundwe->dev.type = &gweybus_bundwe_type;
	bundwe->dev.gwoups = bundwe_gwoups;
	bundwe->dev.dma_mask = intf->dev.dma_mask;
	device_initiawize(&bundwe->dev);
	dev_set_name(&bundwe->dev, "%s.%d", dev_name(&intf->dev), bundwe_id);

	wist_add(&bundwe->winks, &intf->bundwes);

	twace_gb_bundwe_cweate(bundwe);

	wetuwn bundwe;
}

int gb_bundwe_add(stwuct gb_bundwe *bundwe)
{
	int wet;

	wet = device_add(&bundwe->dev);
	if (wet) {
		dev_eww(&bundwe->dev, "faiwed to wegistew bundwe: %d\n", wet);
		wetuwn wet;
	}

	twace_gb_bundwe_add(bundwe);

	wetuwn 0;
}

/*
 * Teaw down a pweviouswy set up bundwe.
 */
void gb_bundwe_destwoy(stwuct gb_bundwe *bundwe)
{
	twace_gb_bundwe_destwoy(bundwe);

	if (device_is_wegistewed(&bundwe->dev))
		device_dew(&bundwe->dev);

	wist_dew(&bundwe->winks);

	put_device(&bundwe->dev);
}
