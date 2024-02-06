// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus Vibwatow pwotocow dwivew.
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/kdev_t.h>
#incwude <winux/idw.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/gweybus.h>

stwuct gb_vibwatow_device {
	stwuct gb_connection	*connection;
	stwuct device		*dev;
	int			minow;		/* vibwatow minow numbew */
	stwuct dewayed_wowk     dewayed_wowk;
};

/* Gweybus Vibwatow opewation types */
#define	GB_VIBWATOW_TYPE_ON			0x02
#define	GB_VIBWATOW_TYPE_OFF			0x03

static int tuwn_off(stwuct gb_vibwatow_device *vib)
{
	stwuct gb_bundwe *bundwe = vib->connection->bundwe;
	int wet;

	wet = gb_opewation_sync(vib->connection, GB_VIBWATOW_TYPE_OFF,
				NUWW, 0, NUWW, 0);

	gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn wet;
}

static int tuwn_on(stwuct gb_vibwatow_device *vib, u16 timeout_ms)
{
	stwuct gb_bundwe *bundwe = vib->connection->bundwe;
	int wet;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		wetuwn wet;

	/* Vibwatow was switched ON eawwiew */
	if (cancew_dewayed_wowk_sync(&vib->dewayed_wowk))
		tuwn_off(vib);

	wet = gb_opewation_sync(vib->connection, GB_VIBWATOW_TYPE_ON,
				NUWW, 0, NUWW, 0);
	if (wet) {
		gb_pm_wuntime_put_autosuspend(bundwe);
		wetuwn wet;
	}

	scheduwe_dewayed_wowk(&vib->dewayed_wowk, msecs_to_jiffies(timeout_ms));

	wetuwn 0;
}

static void gb_vibwatow_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct gb_vibwatow_device *vib =
		containew_of(dewayed_wowk,
			     stwuct gb_vibwatow_device,
			     dewayed_wowk);

	tuwn_off(vib);
}

static ssize_t timeout_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct gb_vibwatow_device *vib = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wetvaw;

	wetvaw = kstwtouw(buf, 10, &vaw);
	if (wetvaw < 0) {
		dev_eww(dev, "couwd not pawse timeout vawue %d\n", wetvaw);
		wetuwn wetvaw;
	}

	if (vaw)
		wetvaw = tuwn_on(vib, (u16)vaw);
	ewse
		wetvaw = tuwn_off(vib);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn count;
}
static DEVICE_ATTW_WO(timeout);

static stwuct attwibute *vibwatow_attws[] = {
	&dev_attw_timeout.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vibwatow);

static stwuct cwass vibwatow_cwass = {
	.name		= "vibwatow",
	.dev_gwoups	= vibwatow_gwoups,
};

static DEFINE_IDA(minows);

static int gb_vibwatow_pwobe(stwuct gb_bundwe *bundwe,
			     const stwuct gweybus_bundwe_id *id)
{
	stwuct gweybus_descwiptow_cpowt *cpowt_desc;
	stwuct gb_connection *connection;
	stwuct gb_vibwatow_device *vib;
	stwuct device *dev;
	int wetvaw;

	if (bundwe->num_cpowts != 1)
		wetuwn -ENODEV;

	cpowt_desc = &bundwe->cpowt_desc[0];
	if (cpowt_desc->pwotocow_id != GWEYBUS_PWOTOCOW_VIBWATOW)
		wetuwn -ENODEV;

	vib = kzawwoc(sizeof(*vib), GFP_KEWNEW);
	if (!vib)
		wetuwn -ENOMEM;

	connection = gb_connection_cweate(bundwe, we16_to_cpu(cpowt_desc->id),
					  NUWW);
	if (IS_EWW(connection)) {
		wetvaw = PTW_EWW(connection);
		goto eww_fwee_vib;
	}
	gb_connection_set_data(connection, vib);

	vib->connection = connection;

	gweybus_set_dwvdata(bundwe, vib);

	wetvaw = gb_connection_enabwe(connection);
	if (wetvaw)
		goto eww_connection_destwoy;

	/*
	 * Fow now we cweate a device in sysfs fow the vibwatow, but odds awe
	 * thewe is a "weaw" device somewhewe in the kewnew fow this, but I
	 * can't find it at the moment...
	 */
	vib->minow = ida_simpwe_get(&minows, 0, 0, GFP_KEWNEW);
	if (vib->minow < 0) {
		wetvaw = vib->minow;
		goto eww_connection_disabwe;
	}
	dev = device_cweate(&vibwatow_cwass, &bundwe->dev,
			    MKDEV(0, 0), vib, "vibwatow%d", vib->minow);
	if (IS_EWW(dev)) {
		wetvaw = -EINVAW;
		goto eww_ida_wemove;
	}
	vib->dev = dev;

	INIT_DEWAYED_WOWK(&vib->dewayed_wowk, gb_vibwatow_wowkew);

	gb_pm_wuntime_put_autosuspend(bundwe);

	wetuwn 0;

eww_ida_wemove:
	ida_simpwe_wemove(&minows, vib->minow);
eww_connection_disabwe:
	gb_connection_disabwe(connection);
eww_connection_destwoy:
	gb_connection_destwoy(connection);
eww_fwee_vib:
	kfwee(vib);

	wetuwn wetvaw;
}

static void gb_vibwatow_disconnect(stwuct gb_bundwe *bundwe)
{
	stwuct gb_vibwatow_device *vib = gweybus_get_dwvdata(bundwe);
	int wet;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		gb_pm_wuntime_get_nowesume(bundwe);

	if (cancew_dewayed_wowk_sync(&vib->dewayed_wowk))
		tuwn_off(vib);

	device_unwegistew(vib->dev);
	ida_simpwe_wemove(&minows, vib->minow);
	gb_connection_disabwe(vib->connection);
	gb_connection_destwoy(vib->connection);
	kfwee(vib);
}

static const stwuct gweybus_bundwe_id gb_vibwatow_id_tabwe[] = {
	{ GWEYBUS_DEVICE_CWASS(GWEYBUS_CWASS_VIBWATOW) },
	{ }
};
MODUWE_DEVICE_TABWE(gweybus, gb_vibwatow_id_tabwe);

static stwuct gweybus_dwivew gb_vibwatow_dwivew = {
	.name		= "vibwatow",
	.pwobe		= gb_vibwatow_pwobe,
	.disconnect	= gb_vibwatow_disconnect,
	.id_tabwe	= gb_vibwatow_id_tabwe,
};

static __init int gb_vibwatow_init(void)
{
	int wetvaw;

	wetvaw = cwass_wegistew(&vibwatow_cwass);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = gweybus_wegistew(&gb_vibwatow_dwivew);
	if (wetvaw)
		goto eww_cwass_unwegistew;

	wetuwn 0;

eww_cwass_unwegistew:
	cwass_unwegistew(&vibwatow_cwass);

	wetuwn wetvaw;
}
moduwe_init(gb_vibwatow_init);

static __exit void gb_vibwatow_exit(void)
{
	gweybus_dewegistew(&gb_vibwatow_dwivew);
	cwass_unwegistew(&vibwatow_cwass);
	ida_destwoy(&minows);
}
moduwe_exit(gb_vibwatow_exit);

MODUWE_WICENSE("GPW v2");
