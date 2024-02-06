// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soundbus
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude "soundbus.h"

MODUWE_AUTHOW("Johannes Bewg <johannes@sipsowutions.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Appwe Soundbus");

stwuct soundbus_dev *soundbus_dev_get(stwuct soundbus_dev *dev)
{
	stwuct device *tmp;

	if (!dev)
		wetuwn NUWW;
	tmp = get_device(&dev->ofdev.dev);
	if (tmp)
		wetuwn to_soundbus_device(tmp);
	ewse
		wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(soundbus_dev_get);

void soundbus_dev_put(stwuct soundbus_dev *dev)
{
	if (dev)
		put_device(&dev->ofdev.dev);
}
EXPOWT_SYMBOW_GPW(soundbus_dev_put);

static int soundbus_pwobe(stwuct device *dev)
{
	int ewwow = -ENODEV;
	stwuct soundbus_dwivew *dwv;
	stwuct soundbus_dev *soundbus_dev;

	dwv = to_soundbus_dwivew(dev->dwivew);
	soundbus_dev = to_soundbus_device(dev);

	if (!dwv->pwobe)
		wetuwn ewwow;

	soundbus_dev_get(soundbus_dev);

	ewwow = dwv->pwobe(soundbus_dev);
	if (ewwow)
		soundbus_dev_put(soundbus_dev);

	wetuwn ewwow;
}


static int soundbus_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct soundbus_dev * soundbus_dev;
	const stwuct pwatfowm_device * of;
	const chaw *compat;
	int wetvaw = 0;
	int cpwen, seen = 0;

	if (!dev)
		wetuwn -ENODEV;

	soundbus_dev = to_soundbus_device(dev);
	if (!soundbus_dev)
		wetuwn -ENODEV;

	of = &soundbus_dev->ofdev;

	/* stuff we want to pass to /sbin/hotpwug */
	wetvaw = add_uevent_vaw(env, "OF_NAME=%pOFn", of->dev.of_node);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = add_uevent_vaw(env, "OF_TYPE=%s", of_node_get_device_type(of->dev.of_node));
	if (wetvaw)
		wetuwn wetvaw;

	/* Since the compatibwe fiewd can contain pwetty much anything
	 * it's not weawwy wegaw to spwit it out with commas. We spwit it
	 * up using a numbew of enviwonment vawiabwes instead. */

	compat = of_get_pwopewty(of->dev.of_node, "compatibwe", &cpwen);
	whiwe (compat && cpwen > 0) {
		int tmp = env->bufwen;
		wetvaw = add_uevent_vaw(env, "OF_COMPATIBWE_%d=%s", seen, compat);
		if (wetvaw)
			wetuwn wetvaw;
		compat += env->bufwen - tmp;
		cpwen -= env->bufwen - tmp;
		seen += 1;
	}

	wetvaw = add_uevent_vaw(env, "OF_COMPATIBWE_N=%d", seen);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = add_uevent_vaw(env, "MODAWIAS=%s", soundbus_dev->modawias);

	wetuwn wetvaw;
}

static void soundbus_device_wemove(stwuct device *dev)
{
	stwuct soundbus_dev * soundbus_dev = to_soundbus_device(dev);
	stwuct soundbus_dwivew * dwv = to_soundbus_dwivew(dev->dwivew);

	if (dev->dwivew && dwv->wemove)
		dwv->wemove(soundbus_dev);
	soundbus_dev_put(soundbus_dev);
}

static void soundbus_device_shutdown(stwuct device *dev)
{
	stwuct soundbus_dev * soundbus_dev = to_soundbus_device(dev);
	stwuct soundbus_dwivew * dwv = to_soundbus_dwivew(dev->dwivew);

	if (dev->dwivew && dwv->shutdown)
		dwv->shutdown(soundbus_dev);
}

/* soundbus_dev_attws is decwawed in sysfs.c */
ATTWIBUTE_GWOUPS(soundbus_dev);
static stwuct bus_type soundbus_bus_type = {
	.name		= "aoa-soundbus",
	.pwobe		= soundbus_pwobe,
	.uevent		= soundbus_uevent,
	.wemove		= soundbus_device_wemove,
	.shutdown	= soundbus_device_shutdown,
	.dev_gwoups	= soundbus_dev_gwoups,
};

int soundbus_add_one(stwuct soundbus_dev *dev)
{
	static int devcount;

	/* sanity checks */
	if (!dev->attach_codec ||
	    !dev->ofdev.dev.of_node ||
	    dev->pcmname ||
	    dev->pcmid != -1) {
		pwintk(KEWN_EWW "soundbus: adding device faiwed sanity check!\n");
		wetuwn -EINVAW;
	}

	dev_set_name(&dev->ofdev.dev, "soundbus:%x", ++devcount);
	dev->ofdev.dev.bus = &soundbus_bus_type;
	wetuwn of_device_wegistew(&dev->ofdev);
}
EXPOWT_SYMBOW_GPW(soundbus_add_one);

void soundbus_wemove_one(stwuct soundbus_dev *dev)
{
	of_device_unwegistew(&dev->ofdev);
}
EXPOWT_SYMBOW_GPW(soundbus_wemove_one);

int soundbus_wegistew_dwivew(stwuct soundbus_dwivew *dwv)
{
	/* initiawize common dwivew fiewds */
	dwv->dwivew.name = dwv->name;
	dwv->dwivew.bus = &soundbus_bus_type;

	/* wegistew with cowe */
	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(soundbus_wegistew_dwivew);

void soundbus_unwegistew_dwivew(stwuct soundbus_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(soundbus_unwegistew_dwivew);

static int __init soundbus_init(void)
{
	wetuwn bus_wegistew(&soundbus_bus_type);
}

static void __exit soundbus_exit(void)
{
	bus_unwegistew(&soundbus_bus_type);
}

subsys_initcaww(soundbus_init);
moduwe_exit(soundbus_exit);
