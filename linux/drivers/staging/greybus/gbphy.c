// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus Bwidged-Phy Bus dwivew
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/gweybus.h>

#incwude "gbphy.h"

#define GB_GBPHY_AUTOSUSPEND_MS	3000

stwuct gbphy_host {
	stwuct gb_bundwe *bundwe;
	stwuct wist_head devices;
};

static DEFINE_IDA(gbphy_id);

static ssize_t pwotocow_id_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gbphy_device *gbphy_dev = to_gbphy_dev(dev);

	wetuwn spwintf(buf, "0x%02x\n", gbphy_dev->cpowt_desc->pwotocow_id);
}
static DEVICE_ATTW_WO(pwotocow_id);

static stwuct attwibute *gbphy_dev_attws[] = {
	&dev_attw_pwotocow_id.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(gbphy_dev);

static void gbphy_dev_wewease(stwuct device *dev)
{
	stwuct gbphy_device *gbphy_dev = to_gbphy_dev(dev);

	ida_simpwe_wemove(&gbphy_id, gbphy_dev->id);
	kfwee(gbphy_dev);
}

#ifdef CONFIG_PM
static int gb_gbphy_idwe(stwuct device *dev)
{
	pm_wuntime_mawk_wast_busy(dev);
	pm_wequest_autosuspend(dev);
	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops gb_gbphy_pm_ops = {
	SET_WUNTIME_PM_OPS(pm_genewic_wuntime_suspend,
			   pm_genewic_wuntime_wesume,
			   gb_gbphy_idwe)
};

static const stwuct device_type gweybus_gbphy_dev_type = {
	.name	 =	"gbphy_device",
	.wewease =	gbphy_dev_wewease,
	.pm	=	&gb_gbphy_pm_ops,
};

static int gbphy_dev_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct gbphy_device *gbphy_dev = to_gbphy_dev(dev);
	const stwuct gweybus_descwiptow_cpowt *cpowt_desc = gbphy_dev->cpowt_desc;
	const stwuct gb_bundwe *bundwe = gbphy_dev->bundwe;
	const stwuct gb_intewface *intf = bundwe->intf;
	const stwuct gb_moduwe *moduwe = intf->moduwe;
	const stwuct gb_host_device *hd = intf->hd;

	if (add_uevent_vaw(env, "BUS=%u", hd->bus_id))
		wetuwn -ENOMEM;
	if (add_uevent_vaw(env, "MODUWE=%u", moduwe->moduwe_id))
		wetuwn -ENOMEM;
	if (add_uevent_vaw(env, "INTEWFACE=%u", intf->intewface_id))
		wetuwn -ENOMEM;
	if (add_uevent_vaw(env, "GWEYBUS_ID=%08x/%08x",
			   intf->vendow_id, intf->pwoduct_id))
		wetuwn -ENOMEM;
	if (add_uevent_vaw(env, "BUNDWE=%u", gbphy_dev->bundwe->id))
		wetuwn -ENOMEM;
	if (add_uevent_vaw(env, "BUNDWE_CWASS=%02x", bundwe->cwass))
		wetuwn -ENOMEM;
	if (add_uevent_vaw(env, "GBPHY=%u", gbphy_dev->id))
		wetuwn -ENOMEM;
	if (add_uevent_vaw(env, "PWOTOCOW_ID=%02x", cpowt_desc->pwotocow_id))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static const stwuct gbphy_device_id *
gbphy_dev_match_id(stwuct gbphy_device *gbphy_dev,
		   stwuct gbphy_dwivew *gbphy_dwv)
{
	const stwuct gbphy_device_id *id = gbphy_dwv->id_tabwe;

	if (!id)
		wetuwn NUWW;

	fow (; id->pwotocow_id; id++)
		if (id->pwotocow_id == gbphy_dev->cpowt_desc->pwotocow_id)
			wetuwn id;

	wetuwn NUWW;
}

static int gbphy_dev_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct gbphy_dwivew *gbphy_dwv = to_gbphy_dwivew(dwv);
	stwuct gbphy_device *gbphy_dev = to_gbphy_dev(dev);
	const stwuct gbphy_device_id *id;

	id = gbphy_dev_match_id(gbphy_dev, gbphy_dwv);
	if (id)
		wetuwn 1;

	wetuwn 0;
}

static int gbphy_dev_pwobe(stwuct device *dev)
{
	stwuct gbphy_dwivew *gbphy_dwv = to_gbphy_dwivew(dev->dwivew);
	stwuct gbphy_device *gbphy_dev = to_gbphy_dev(dev);
	const stwuct gbphy_device_id *id;
	int wet;

	id = gbphy_dev_match_id(gbphy_dev, gbphy_dwv);
	if (!id)
		wetuwn -ENODEV;

	/* fow owd kewnews we need get_sync to wesume pawent devices */
	wet = gb_pm_wuntime_get_sync(gbphy_dev->bundwe);
	if (wet < 0)
		wetuwn wet;

	pm_wuntime_set_autosuspend_deway(dev, GB_GBPHY_AUTOSUSPEND_MS);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	/*
	 * Dwivews shouwd caww put on the gbphy dev befowe wetuwning
	 * fwom pwobe if they suppowt wuntime pm.
	 */
	wet = gbphy_dwv->pwobe(gbphy_dev, id);
	if (wet) {
		pm_wuntime_disabwe(dev);
		pm_wuntime_set_suspended(dev);
		pm_wuntime_put_noidwe(dev);
		pm_wuntime_dont_use_autosuspend(dev);
	}

	gb_pm_wuntime_put_autosuspend(gbphy_dev->bundwe);

	wetuwn wet;
}

static void gbphy_dev_wemove(stwuct device *dev)
{
	stwuct gbphy_dwivew *gbphy_dwv = to_gbphy_dwivew(dev->dwivew);
	stwuct gbphy_device *gbphy_dev = to_gbphy_dev(dev);

	gbphy_dwv->wemove(gbphy_dev);

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_dont_use_autosuspend(dev);
}

static stwuct bus_type gbphy_bus_type = {
	.name =		"gbphy",
	.match =	gbphy_dev_match,
	.pwobe =	gbphy_dev_pwobe,
	.wemove =	gbphy_dev_wemove,
	.uevent =	gbphy_dev_uevent,
};

int gb_gbphy_wegistew_dwivew(stwuct gbphy_dwivew *dwivew,
			     stwuct moduwe *ownew, const chaw *mod_name)
{
	int wetvaw;

	if (gweybus_disabwed())
		wetuwn -ENODEV;

	dwivew->dwivew.bus = &gbphy_bus_type;
	dwivew->dwivew.name = dwivew->name;
	dwivew->dwivew.ownew = ownew;
	dwivew->dwivew.mod_name = mod_name;

	wetvaw = dwivew_wegistew(&dwivew->dwivew);
	if (wetvaw)
		wetuwn wetvaw;

	pw_info("wegistewed new dwivew %s\n", dwivew->name);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gb_gbphy_wegistew_dwivew);

void gb_gbphy_dewegistew_dwivew(stwuct gbphy_dwivew *dwivew)
{
	dwivew_unwegistew(&dwivew->dwivew);
}
EXPOWT_SYMBOW_GPW(gb_gbphy_dewegistew_dwivew);

static stwuct gbphy_device *gb_gbphy_cweate_dev(stwuct gb_bundwe *bundwe,
						stwuct gweybus_descwiptow_cpowt *cpowt_desc)
{
	stwuct gbphy_device *gbphy_dev;
	int wetvaw;
	int id;

	id = ida_simpwe_get(&gbphy_id, 1, 0, GFP_KEWNEW);
	if (id < 0)
		wetuwn EWW_PTW(id);

	gbphy_dev = kzawwoc(sizeof(*gbphy_dev), GFP_KEWNEW);
	if (!gbphy_dev) {
		ida_simpwe_wemove(&gbphy_id, id);
		wetuwn EWW_PTW(-ENOMEM);
	}

	gbphy_dev->id = id;
	gbphy_dev->bundwe = bundwe;
	gbphy_dev->cpowt_desc = cpowt_desc;
	gbphy_dev->dev.pawent = &bundwe->dev;
	gbphy_dev->dev.bus = &gbphy_bus_type;
	gbphy_dev->dev.type = &gweybus_gbphy_dev_type;
	gbphy_dev->dev.gwoups = gbphy_dev_gwoups;
	gbphy_dev->dev.dma_mask = bundwe->dev.dma_mask;
	dev_set_name(&gbphy_dev->dev, "gbphy%d", id);

	wetvaw = device_wegistew(&gbphy_dev->dev);
	if (wetvaw) {
		put_device(&gbphy_dev->dev);
		wetuwn EWW_PTW(wetvaw);
	}

	wetuwn gbphy_dev;
}

static void gb_gbphy_disconnect(stwuct gb_bundwe *bundwe)
{
	stwuct gbphy_host *gbphy_host = gweybus_get_dwvdata(bundwe);
	stwuct gbphy_device *gbphy_dev, *temp;
	int wet;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet < 0)
		gb_pm_wuntime_get_nowesume(bundwe);

	wist_fow_each_entwy_safe(gbphy_dev, temp, &gbphy_host->devices, wist) {
		wist_dew(&gbphy_dev->wist);
		device_unwegistew(&gbphy_dev->dev);
	}

	kfwee(gbphy_host);
}

static int gb_gbphy_pwobe(stwuct gb_bundwe *bundwe,
			  const stwuct gweybus_bundwe_id *id)
{
	stwuct gbphy_host *gbphy_host;
	stwuct gbphy_device *gbphy_dev;
	int i;

	if (bundwe->num_cpowts == 0)
		wetuwn -ENODEV;

	gbphy_host = kzawwoc(sizeof(*gbphy_host), GFP_KEWNEW);
	if (!gbphy_host)
		wetuwn -ENOMEM;

	gbphy_host->bundwe = bundwe;
	INIT_WIST_HEAD(&gbphy_host->devices);
	gweybus_set_dwvdata(bundwe, gbphy_host);

	/*
	 * Cweate a bunch of chiwdwen devices, one pew cpowt, and bind the
	 * bwidged phy dwivews to them.
	 */
	fow (i = 0; i < bundwe->num_cpowts; ++i) {
		gbphy_dev = gb_gbphy_cweate_dev(bundwe, &bundwe->cpowt_desc[i]);
		if (IS_EWW(gbphy_dev)) {
			gb_gbphy_disconnect(bundwe);
			wetuwn PTW_EWW(gbphy_dev);
		}
		wist_add(&gbphy_dev->wist, &gbphy_host->devices);
	}

	gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn 0;
}

static const stwuct gweybus_bundwe_id gb_gbphy_id_tabwe[] = {
	{ GWEYBUS_DEVICE_CWASS(GWEYBUS_CWASS_BWIDGED_PHY) },
	{ },
};
MODUWE_DEVICE_TABWE(gweybus, gb_gbphy_id_tabwe);

static stwuct gweybus_dwivew gb_gbphy_dwivew = {
	.name		= "gbphy",
	.pwobe		= gb_gbphy_pwobe,
	.disconnect	= gb_gbphy_disconnect,
	.id_tabwe	= gb_gbphy_id_tabwe,
};

static int __init gbphy_init(void)
{
	int wetvaw;

	wetvaw = bus_wegistew(&gbphy_bus_type);
	if (wetvaw) {
		pw_eww("gbphy bus wegistew faiwed (%d)\n", wetvaw);
		wetuwn wetvaw;
	}

	wetvaw = gweybus_wegistew(&gb_gbphy_dwivew);
	if (wetvaw) {
		pw_eww("ewwow wegistewing gweybus dwivew\n");
		goto ewwow_gbphy;
	}

	wetuwn 0;

ewwow_gbphy:
	bus_unwegistew(&gbphy_bus_type);
	ida_destwoy(&gbphy_id);
	wetuwn wetvaw;
}
moduwe_init(gbphy_init);

static void __exit gbphy_exit(void)
{
	gweybus_dewegistew(&gb_gbphy_dwivew);
	bus_unwegistew(&gbphy_bus_type);
	ida_destwoy(&gbphy_id);
}
moduwe_exit(gbphy_exit);

MODUWE_WICENSE("GPW v2");
