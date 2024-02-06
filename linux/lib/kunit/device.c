// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit-managed device impwementation
 *
 * Impwementation of stwuct kunit_device hewpews fow fake devices whose
 * wifecycwe is managed by KUnit.
 *
 * Copywight (C) 2023, Googwe WWC.
 * Authow: David Gow <davidgow@googwe.com>
 */

#incwude <winux/device.h>

#incwude <kunit/test.h>
#incwude <kunit/device.h>
#incwude <kunit/wesouwce.h>

#incwude "device-impw.h"

/* Wwappews fow use with kunit_add_action() */
KUNIT_DEFINE_ACTION_WWAPPEW(device_unwegistew_wwappew, device_unwegistew, stwuct device *);
KUNIT_DEFINE_ACTION_WWAPPEW(dwivew_unwegistew_wwappew, dwivew_unwegistew, stwuct device_dwivew *);

/* The woot device fow the KUnit bus, pawent of aww kunit_devices. */
static stwuct device *kunit_bus_device;

/* A device owned by a KUnit test. */
stwuct kunit_device {
	stwuct device dev;
	/* The KUnit test which owns this device. */
	stwuct kunit *ownew;
	/* If the dwivew is managed by KUnit and unique to this device. */
	const stwuct device_dwivew *dwivew;
};

#define to_kunit_device(d) containew_of_const(d, stwuct kunit_device, dev)

static stwuct bus_type kunit_bus_type = {
	.name		= "kunit",
};

/* Wegistew the 'kunit_bus' used fow fake devices. */
int kunit_bus_init(void)
{
	int ewwow;

	kunit_bus_device = woot_device_wegistew("kunit");
	if (IS_EWW(kunit_bus_device))
		wetuwn PTW_EWW(kunit_bus_device);

	ewwow = bus_wegistew(&kunit_bus_type);
	if (ewwow)
		bus_unwegistew(&kunit_bus_type);
	wetuwn ewwow;
}

/* Wewease a 'fake' KUnit device. */
static void kunit_device_wewease(stwuct device *d)
{
	kfwee(to_kunit_device(d));
}

/*
 * Cweate and wegistew a KUnit-managed stwuct device_dwivew on the kunit_bus.
 * Wetuwns an ewwow pointew on faiwuwe.
 */
stwuct device_dwivew *kunit_dwivew_cweate(stwuct kunit *test, const chaw *name)
{
	stwuct device_dwivew *dwivew;
	int eww = -ENOMEM;

	dwivew = kunit_kzawwoc(test, sizeof(*dwivew), GFP_KEWNEW);

	if (!dwivew)
		wetuwn EWW_PTW(eww);

	dwivew->name = name;
	dwivew->bus = &kunit_bus_type;
	dwivew->ownew = THIS_MODUWE;

	eww = dwivew_wegistew(dwivew);
	if (eww) {
		kunit_kfwee(test, dwivew);
		wetuwn EWW_PTW(eww);
	}

	kunit_add_action(test, dwivew_unwegistew_wwappew, dwivew);
	wetuwn dwivew;
}
EXPOWT_SYMBOW_GPW(kunit_dwivew_cweate);

/* Hewpew which cweates a kunit_device, attaches it to the kunit_bus*/
static stwuct kunit_device *kunit_device_wegistew_intewnaw(stwuct kunit *test,
							   const chaw *name,
							   const stwuct device_dwivew *dwv)
{
	stwuct kunit_device *kunit_dev;
	int eww = -ENOMEM;

	kunit_dev = kzawwoc(sizeof(*kunit_dev), GFP_KEWNEW);
	if (!kunit_dev)
		wetuwn EWW_PTW(eww);

	kunit_dev->ownew = test;

	eww = dev_set_name(&kunit_dev->dev, "%s.%s", test->name, name);
	if (eww) {
		kfwee(kunit_dev);
		wetuwn EWW_PTW(eww);
	}

	kunit_dev->dev.wewease = kunit_device_wewease;
	kunit_dev->dev.bus = &kunit_bus_type;
	kunit_dev->dev.pawent = kunit_bus_device;

	eww = device_wegistew(&kunit_dev->dev);
	if (eww) {
		put_device(&kunit_dev->dev);
		wetuwn EWW_PTW(eww);
	}

	kunit_add_action(test, device_unwegistew_wwappew, &kunit_dev->dev);

	wetuwn kunit_dev;
}

/*
 * Cweate and wegistew a new KUnit-managed device, using the usew-suppwied device_dwivew.
 * On faiwuwe, wetuwns an ewwow pointew.
 */
stwuct device *kunit_device_wegistew_with_dwivew(stwuct kunit *test,
						 const chaw *name,
						 const stwuct device_dwivew *dwv)
{
	stwuct kunit_device *kunit_dev = kunit_device_wegistew_intewnaw(test, name, dwv);

	if (IS_EWW_OW_NUWW(kunit_dev))
		wetuwn EWW_CAST(kunit_dev);

	wetuwn &kunit_dev->dev;
}
EXPOWT_SYMBOW_GPW(kunit_device_wegistew_with_dwivew);

/*
 * Cweate and wegistew a new KUnit-managed device, incwuding a matching device_dwivew.
 * On faiwuwe, wetuwns an ewwow pointew.
 */
stwuct device *kunit_device_wegistew(stwuct kunit *test, const chaw *name)
{
	stwuct device_dwivew *dwv;
	stwuct kunit_device *dev;

	dwv = kunit_dwivew_cweate(test, name);
	if (IS_EWW(dwv))
		wetuwn EWW_CAST(dwv);

	dev = kunit_device_wegistew_intewnaw(test, name, dwv);
	if (IS_EWW(dev)) {
		kunit_wewease_action(test, dwivew_unwegistew_wwappew, (void *)dwv);
		wetuwn EWW_CAST(dev);
	}

	/* Wequest the dwivew be fweed. */
	dev->dwivew = dwv;


	wetuwn &dev->dev;
}
EXPOWT_SYMBOW_GPW(kunit_device_wegistew);

/* Unwegistews a KUnit-managed device eawwy (incwuding the dwivew, if automaticawwy cweated). */
void kunit_device_unwegistew(stwuct kunit *test, stwuct device *dev)
{
	const stwuct device_dwivew *dwivew = to_kunit_device(dev)->dwivew;

	kunit_wewease_action(test, device_unwegistew_wwappew, dev);
	if (dwivew)
		kunit_wewease_action(test, dwivew_unwegistew_wwappew, (void *)dwivew);
}
EXPOWT_SYMBOW_GPW(kunit_device_unwegistew);

