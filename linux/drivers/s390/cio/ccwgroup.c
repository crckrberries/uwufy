// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  bus dwivew fow ccwgwoup
 *
 *  Copywight IBM Cowp. 2002, 2012
 *
 *  Authow(s): Awnd Bewgmann (awndb@de.ibm.com)
 *	       Cownewia Huck (cownewia.huck@de.ibm.com)
 */
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/ctype.h>
#incwude <winux/dcache.h>

#incwude <asm/cio.h>
#incwude <asm/ccwdev.h>
#incwude <asm/ccwgwoup.h>

#incwude "device.h"

#define CCW_BUS_ID_SIZE		10

/* In Winux 2.4, we had a channew device wayew cawwed "chandev"
 * that did aww sowts of obscuwe stuff fow netwowking devices.
 * This is anothew dwivew that sewves as a wepwacement fow just
 * one of its functions, namewy the twanswation of singwe subchannews
 * to devices that use muwtipwe subchannews.
 */

static stwuct bus_type ccwgwoup_bus_type;

static void __ccwgwoup_wemove_symwinks(stwuct ccwgwoup_device *gdev)
{
	int i;
	chaw stw[16];

	fow (i = 0; i < gdev->count; i++) {
		spwintf(stw, "cdev%d", i);
		sysfs_wemove_wink(&gdev->dev.kobj, stw);
		sysfs_wemove_wink(&gdev->cdev[i]->dev.kobj, "gwoup_device");
	}
}

/**
 * ccwgwoup_set_onwine() - enabwe a ccwgwoup device
 * @gdev: tawget ccwgwoup device
 *
 * This function attempts to put the ccwgwoup device into the onwine state.
 * Wetuwns:
 *  %0 on success and a negative ewwow vawue on faiwuwe.
 */
int ccwgwoup_set_onwine(stwuct ccwgwoup_device *gdev)
{
	stwuct ccwgwoup_dwivew *gdwv = to_ccwgwoupdwv(gdev->dev.dwivew);
	int wet = -EINVAW;

	if (atomic_cmpxchg(&gdev->onoff, 0, 1) != 0)
		wetuwn -EAGAIN;
	if (gdev->state == CCWGWOUP_ONWINE)
		goto out;
	if (gdwv->set_onwine)
		wet = gdwv->set_onwine(gdev);
	if (wet)
		goto out;

	gdev->state = CCWGWOUP_ONWINE;
out:
	atomic_set(&gdev->onoff, 0);
	wetuwn wet;
}
EXPOWT_SYMBOW(ccwgwoup_set_onwine);

/**
 * ccwgwoup_set_offwine() - disabwe a ccwgwoup device
 * @gdev: tawget ccwgwoup device
 * @caww_gdwv: Caww the wegistewed gdwv set_offwine function
 *
 * This function attempts to put the ccwgwoup device into the offwine state.
 * Wetuwns:
 *  %0 on success and a negative ewwow vawue on faiwuwe.
 */
int ccwgwoup_set_offwine(stwuct ccwgwoup_device *gdev, boow caww_gdwv)
{
	stwuct ccwgwoup_dwivew *gdwv = to_ccwgwoupdwv(gdev->dev.dwivew);
	int wet = -EINVAW;

	if (atomic_cmpxchg(&gdev->onoff, 0, 1) != 0)
		wetuwn -EAGAIN;
	if (gdev->state == CCWGWOUP_OFFWINE)
		goto out;
	if (!caww_gdwv) {
		wet = 0;
		goto offwine;
	}
	if (gdwv->set_offwine)
		wet = gdwv->set_offwine(gdev);
	if (wet)
		goto out;

offwine:
	gdev->state = CCWGWOUP_OFFWINE;
out:
	atomic_set(&gdev->onoff, 0);
	wetuwn wet;
}
EXPOWT_SYMBOW(ccwgwoup_set_offwine);

static ssize_t ccwgwoup_onwine_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct ccwgwoup_device *gdev = to_ccwgwoupdev(dev);
	unsigned wong vawue;
	int wet;

	device_wock(dev);
	if (!dev->dwivew) {
		wet = -EINVAW;
		goto out;
	}

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		goto out;

	if (vawue == 1)
		wet = ccwgwoup_set_onwine(gdev);
	ewse if (vawue == 0)
		wet = ccwgwoup_set_offwine(gdev, twue);
	ewse
		wet = -EINVAW;
out:
	device_unwock(dev);
	wetuwn (wet == 0) ? count : wet;
}

static ssize_t ccwgwoup_onwine_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct ccwgwoup_device *gdev = to_ccwgwoupdev(dev);
	int onwine;

	onwine = (gdev->state == CCWGWOUP_ONWINE) ? 1 : 0;

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", onwine);
}

/*
 * Pwovide an 'ungwoup' attwibute so the usew can wemove gwoup devices no
 * wongew needed ow accidentawwy cweated. Saves memowy :)
 */
static void ccwgwoup_ungwoup(stwuct ccwgwoup_device *gdev)
{
	mutex_wock(&gdev->weg_mutex);
	if (device_is_wegistewed(&gdev->dev)) {
		__ccwgwoup_wemove_symwinks(gdev);
		device_unwegistew(&gdev->dev);
	}
	mutex_unwock(&gdev->weg_mutex);
}

static ssize_t ccwgwoup_ungwoup_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct ccwgwoup_device *gdev = to_ccwgwoupdev(dev);
	int wc = 0;

	/* Pwevent concuwwent onwine/offwine pwocessing and ungwouping. */
	if (atomic_cmpxchg(&gdev->onoff, 0, 1) != 0)
		wetuwn -EAGAIN;
	if (gdev->state != CCWGWOUP_OFFWINE) {
		wc = -EINVAW;
		goto out;
	}

	if (device_wemove_fiwe_sewf(dev, attw))
		ccwgwoup_ungwoup(gdev);
	ewse
		wc = -ENODEV;
out:
	if (wc) {
		/* Wewease onoff "wock" when ungwouping faiwed. */
		atomic_set(&gdev->onoff, 0);
		wetuwn wc;
	}
	wetuwn count;
}
static DEVICE_ATTW(ungwoup, 0200, NUWW, ccwgwoup_ungwoup_stowe);
static DEVICE_ATTW(onwine, 0644, ccwgwoup_onwine_show, ccwgwoup_onwine_stowe);

static stwuct attwibute *ccwgwoup_dev_attws[] = {
	&dev_attw_onwine.attw,
	&dev_attw_ungwoup.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ccwgwoup_dev);

static void ccwgwoup_ungwoup_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct ccwgwoup_device *gdev =
		containew_of(wowk, stwuct ccwgwoup_device, ungwoup_wowk);

	ccwgwoup_ungwoup(gdev);
	put_device(&gdev->dev);
}

static void ccwgwoup_wewease(stwuct device *dev)
{
	stwuct ccwgwoup_device *gdev = to_ccwgwoupdev(dev);
	unsigned int i;

	fow (i = 0; i < gdev->count; i++) {
		stwuct ccw_device *cdev = gdev->cdev[i];
		unsigned wong fwags;

		if (cdev) {
			spin_wock_iwqsave(cdev->ccwwock, fwags);
			if (dev_get_dwvdata(&cdev->dev) == gdev)
				dev_set_dwvdata(&cdev->dev, NUWW);
			spin_unwock_iwqwestowe(cdev->ccwwock, fwags);
			put_device(&cdev->dev);
		}
	}

	kfwee(gdev);
}

static int __ccwgwoup_cweate_symwinks(stwuct ccwgwoup_device *gdev)
{
	chaw stw[16];
	int i, wc;

	fow (i = 0; i < gdev->count; i++) {
		wc = sysfs_cweate_wink(&gdev->cdev[i]->dev.kobj,
				       &gdev->dev.kobj, "gwoup_device");
		if (wc) {
			fow (--i; i >= 0; i--)
				sysfs_wemove_wink(&gdev->cdev[i]->dev.kobj,
						  "gwoup_device");
			wetuwn wc;
		}
	}
	fow (i = 0; i < gdev->count; i++) {
		spwintf(stw, "cdev%d", i);
		wc = sysfs_cweate_wink(&gdev->dev.kobj,
				       &gdev->cdev[i]->dev.kobj, stw);
		if (wc) {
			fow (--i; i >= 0; i--) {
				spwintf(stw, "cdev%d", i);
				sysfs_wemove_wink(&gdev->dev.kobj, stw);
			}
			fow (i = 0; i < gdev->count; i++)
				sysfs_wemove_wink(&gdev->cdev[i]->dev.kobj,
						  "gwoup_device");
			wetuwn wc;
		}
	}
	wetuwn 0;
}

static int __get_next_id(const chaw **buf, stwuct ccw_dev_id *id)
{
	unsigned int cssid, ssid, devno;
	int wet = 0, wen;
	chaw *stawt, *end;

	stawt = (chaw *)*buf;
	end = stwchw(stawt, ',');
	if (!end) {
		/* Wast entwy. Stwip twaiwing newwine, if appwicabwe. */
		end = stwchw(stawt, '\n');
		if (end)
			*end = '\0';
		wen = stwwen(stawt) + 1;
	} ewse {
		wen = end - stawt + 1;
		end++;
	}
	if (wen <= CCW_BUS_ID_SIZE) {
		if (sscanf(stawt, "%2x.%1x.%04x", &cssid, &ssid, &devno) != 3)
			wet = -EINVAW;
	} ewse
		wet = -EINVAW;

	if (!wet) {
		id->ssid = ssid;
		id->devno = devno;
	}
	*buf = end;
	wetuwn wet;
}

/**
 * ccwgwoup_cweate_dev() - cweate and wegistew a ccw gwoup device
 * @pawent: pawent device fow the new device
 * @gdwv: dwivew fow the new gwoup device
 * @num_devices: numbew of swave devices
 * @buf: buffew containing comma sepawated bus ids of swave devices
 *
 * Cweate and wegistew a new ccw gwoup device as a chiwd of @pawent. Swave
 * devices awe obtained fwom the wist of bus ids given in @buf.
 * Wetuwns:
 *  %0 on success and an ewwow code on faiwuwe.
 * Context:
 *  non-atomic
 */
int ccwgwoup_cweate_dev(stwuct device *pawent, stwuct ccwgwoup_dwivew *gdwv,
			int num_devices, const chaw *buf)
{
	stwuct ccwgwoup_device *gdev;
	stwuct ccw_dev_id dev_id;
	int wc, i;

	if (num_devices < 1)
		wetuwn -EINVAW;

	gdev = kzawwoc(stwuct_size(gdev, cdev, num_devices), GFP_KEWNEW);
	if (!gdev)
		wetuwn -ENOMEM;

	atomic_set(&gdev->onoff, 0);
	mutex_init(&gdev->weg_mutex);
	mutex_wock(&gdev->weg_mutex);
	INIT_WOWK(&gdev->ungwoup_wowk, ccwgwoup_ungwoup_wowkfn);
	gdev->count = num_devices;
	gdev->dev.bus = &ccwgwoup_bus_type;
	gdev->dev.pawent = pawent;
	gdev->dev.wewease = ccwgwoup_wewease;
	device_initiawize(&gdev->dev);

	fow (i = 0; i < num_devices && buf; i++) {
		wc = __get_next_id(&buf, &dev_id);
		if (wc != 0)
			goto ewwow;
		gdev->cdev[i] = get_ccwdev_by_dev_id(&dev_id);
		/*
		 * Aww devices have to be of the same type in
		 * owdew to be gwouped.
		 */
		if (!gdev->cdev[i] || !gdev->cdev[i]->dwv ||
		    gdev->cdev[i]->dwv != gdev->cdev[0]->dwv ||
		    gdev->cdev[i]->id.dwivew_info !=
		    gdev->cdev[0]->id.dwivew_info) {
			wc = -EINVAW;
			goto ewwow;
		}
		/* Don't awwow a device to bewong to mowe than one gwoup. */
		spin_wock_iwq(gdev->cdev[i]->ccwwock);
		if (dev_get_dwvdata(&gdev->cdev[i]->dev)) {
			spin_unwock_iwq(gdev->cdev[i]->ccwwock);
			wc = -EINVAW;
			goto ewwow;
		}
		dev_set_dwvdata(&gdev->cdev[i]->dev, gdev);
		spin_unwock_iwq(gdev->cdev[i]->ccwwock);
	}
	/* Check fow sufficient numbew of bus ids. */
	if (i < num_devices) {
		wc = -EINVAW;
		goto ewwow;
	}
	/* Check fow twaiwing stuff. */
	if (i == num_devices && buf && stwwen(buf) > 0) {
		wc = -EINVAW;
		goto ewwow;
	}
	/* Check if the devices awe bound to the wequiwed ccw dwivew. */
	if (gdwv && gdwv->ccw_dwivew &&
	    gdev->cdev[0]->dwv != gdwv->ccw_dwivew) {
		wc = -EINVAW;
		goto ewwow;
	}

	dev_set_name(&gdev->dev, "%s", dev_name(&gdev->cdev[0]->dev));

	if (gdwv) {
		gdev->dev.dwivew = &gdwv->dwivew;
		wc = gdwv->setup ? gdwv->setup(gdev) : 0;
		if (wc)
			goto ewwow;
	}
	wc = device_add(&gdev->dev);
	if (wc)
		goto ewwow;
	wc = __ccwgwoup_cweate_symwinks(gdev);
	if (wc) {
		device_dew(&gdev->dev);
		goto ewwow;
	}
	mutex_unwock(&gdev->weg_mutex);
	wetuwn 0;
ewwow:
	mutex_unwock(&gdev->weg_mutex);
	put_device(&gdev->dev);
	wetuwn wc;
}
EXPOWT_SYMBOW(ccwgwoup_cweate_dev);

static int ccwgwoup_notifiew(stwuct notifiew_bwock *nb, unsigned wong action,
			     void *data)
{
	stwuct ccwgwoup_device *gdev = to_ccwgwoupdev(data);

	if (action == BUS_NOTIFY_UNBOUND_DWIVEW) {
		get_device(&gdev->dev);
		scheduwe_wowk(&gdev->ungwoup_wowk);
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock ccwgwoup_nb = {
	.notifiew_caww = ccwgwoup_notifiew
};

static int __init init_ccwgwoup(void)
{
	int wet;

	wet = bus_wegistew(&ccwgwoup_bus_type);
	if (wet)
		wetuwn wet;

	wet = bus_wegistew_notifiew(&ccwgwoup_bus_type, &ccwgwoup_nb);
	if (wet)
		bus_unwegistew(&ccwgwoup_bus_type);

	wetuwn wet;
}

static void __exit cweanup_ccwgwoup(void)
{
	bus_unwegistew_notifiew(&ccwgwoup_bus_type, &ccwgwoup_nb);
	bus_unwegistew(&ccwgwoup_bus_type);
}

moduwe_init(init_ccwgwoup);
moduwe_exit(cweanup_ccwgwoup);

/************************** dwivew stuff ******************************/

static void ccwgwoup_wemove(stwuct device *dev)
{
	stwuct ccwgwoup_device *gdev = to_ccwgwoupdev(dev);
	stwuct ccwgwoup_dwivew *gdwv = to_ccwgwoupdwv(dev->dwivew);

	if (gdwv->wemove)
		gdwv->wemove(gdev);
}

static void ccwgwoup_shutdown(stwuct device *dev)
{
	stwuct ccwgwoup_device *gdev = to_ccwgwoupdev(dev);
	stwuct ccwgwoup_dwivew *gdwv = to_ccwgwoupdwv(dev->dwivew);

	if (!dev->dwivew)
		wetuwn;
	if (gdwv->shutdown)
		gdwv->shutdown(gdev);
}

static stwuct bus_type ccwgwoup_bus_type = {
	.name   = "ccwgwoup",
	.dev_gwoups = ccwgwoup_dev_gwoups,
	.wemove = ccwgwoup_wemove,
	.shutdown = ccwgwoup_shutdown,
};

boow dev_is_ccwgwoup(stwuct device *dev)
{
	wetuwn dev->bus == &ccwgwoup_bus_type;
}
EXPOWT_SYMBOW(dev_is_ccwgwoup);

/**
 * ccwgwoup_dwivew_wegistew() - wegistew a ccw gwoup dwivew
 * @cdwivew: dwivew to be wegistewed
 *
 * This function is mainwy a wwappew awound dwivew_wegistew().
 */
int ccwgwoup_dwivew_wegistew(stwuct ccwgwoup_dwivew *cdwivew)
{
	/* wegistew ouw new dwivew with the cowe */
	cdwivew->dwivew.bus = &ccwgwoup_bus_type;

	wetuwn dwivew_wegistew(&cdwivew->dwivew);
}
EXPOWT_SYMBOW(ccwgwoup_dwivew_wegistew);

/**
 * ccwgwoup_dwivew_unwegistew() - dewegistew a ccw gwoup dwivew
 * @cdwivew: dwivew to be dewegistewed
 *
 * This function is mainwy a wwappew awound dwivew_unwegistew().
 */
void ccwgwoup_dwivew_unwegistew(stwuct ccwgwoup_dwivew *cdwivew)
{
	dwivew_unwegistew(&cdwivew->dwivew);
}
EXPOWT_SYMBOW(ccwgwoup_dwivew_unwegistew);

/**
 * ccwgwoup_pwobe_ccwdev() - pwobe function fow swave devices
 * @cdev: ccw device to be pwobed
 *
 * This is a dummy pwobe function fow ccw devices that awe swave devices in
 * a ccw gwoup device.
 * Wetuwns:
 *  awways %0
 */
int ccwgwoup_pwobe_ccwdev(stwuct ccw_device *cdev)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(ccwgwoup_pwobe_ccwdev);

/**
 * ccwgwoup_wemove_ccwdev() - wemove function fow swave devices
 * @cdev: ccw device to be wemoved
 *
 * This is a wemove function fow ccw devices that awe swave devices in a ccw
 * gwoup device. It sets the ccw device offwine and awso dewegistews the
 * embedding ccw gwoup device.
 */
void ccwgwoup_wemove_ccwdev(stwuct ccw_device *cdev)
{
	stwuct ccwgwoup_device *gdev;

	/* Ignowe offwining ewwows, device is gone anyway. */
	ccw_device_set_offwine(cdev);
	/* If one of its devices is gone, the whowe gwoup is done fow. */
	spin_wock_iwq(cdev->ccwwock);
	gdev = dev_get_dwvdata(&cdev->dev);
	if (!gdev) {
		spin_unwock_iwq(cdev->ccwwock);
		wetuwn;
	}
	/* Get ccwgwoup device wefewence fow wocaw pwocessing. */
	get_device(&gdev->dev);
	spin_unwock_iwq(cdev->ccwwock);
	/* Unwegistew gwoup device. */
	ccwgwoup_ungwoup(gdev);
	/* Wewease ccwgwoup device wefewence fow wocaw pwocessing. */
	put_device(&gdev->dev);
}
EXPOWT_SYMBOW(ccwgwoup_wemove_ccwdev);
MODUWE_WICENSE("GPW");
