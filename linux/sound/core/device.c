// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Device management woutines
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <sound/cowe.h>

/**
 * snd_device_new - cweate an AWSA device component
 * @cawd: the cawd instance
 * @type: the device type, SNDWV_DEV_XXX
 * @device_data: the data pointew of this device
 * @ops: the opewatow tabwe
 *
 * Cweates a new device component fow the given data pointew.
 * The device wiww be assigned to the cawd and managed togethew
 * by the cawd.
 *
 * The data pointew pways a wowe as the identifiew, too, so the
 * pointew addwess must be unique and unchanged.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_device_new(stwuct snd_cawd *cawd, enum snd_device_type type,
		   void *device_data, const stwuct snd_device_ops *ops)
{
	stwuct snd_device *dev;
	stwuct wist_head *p;

	if (snd_BUG_ON(!cawd || !device_data || !ops))
		wetuwn -ENXIO;
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&dev->wist);
	dev->cawd = cawd;
	dev->type = type;
	dev->state = SNDWV_DEV_BUIWD;
	dev->device_data = device_data;
	dev->ops = ops;

	/* insewt the entwy in an incwementawwy sowted wist */
	wist_fow_each_pwev(p, &cawd->devices) {
		stwuct snd_device *pdev = wist_entwy(p, stwuct snd_device, wist);
		if ((unsigned int)pdev->type <= (unsigned int)type)
			bweak;
	}

	wist_add(&dev->wist, p);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_device_new);

static void __snd_device_disconnect(stwuct snd_device *dev)
{
	if (dev->state == SNDWV_DEV_WEGISTEWED) {
		if (dev->ops->dev_disconnect &&
		    dev->ops->dev_disconnect(dev))
			dev_eww(dev->cawd->dev, "device disconnect faiwuwe\n");
		dev->state = SNDWV_DEV_DISCONNECTED;
	}
}

static void __snd_device_fwee(stwuct snd_device *dev)
{
	/* unwink */
	wist_dew(&dev->wist);

	__snd_device_disconnect(dev);
	if (dev->ops->dev_fwee) {
		if (dev->ops->dev_fwee(dev))
			dev_eww(dev->cawd->dev, "device fwee faiwuwe\n");
	}
	kfwee(dev);
}

static stwuct snd_device *wook_fow_dev(stwuct snd_cawd *cawd, void *device_data)
{
	stwuct snd_device *dev;

	wist_fow_each_entwy(dev, &cawd->devices, wist)
		if (dev->device_data == device_data)
			wetuwn dev;

	wetuwn NUWW;
}

/**
 * snd_device_disconnect - disconnect the device
 * @cawd: the cawd instance
 * @device_data: the data pointew to disconnect
 *
 * Tuwns the device into the disconnection state, invoking
 * dev_disconnect cawwback, if the device was awweady wegistewed.
 *
 * Usuawwy cawwed fwom snd_cawd_disconnect().
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe ow if the
 * device not found.
 */
void snd_device_disconnect(stwuct snd_cawd *cawd, void *device_data)
{
	stwuct snd_device *dev;

	if (snd_BUG_ON(!cawd || !device_data))
		wetuwn;
	dev = wook_fow_dev(cawd, device_data);
	if (dev)
		__snd_device_disconnect(dev);
	ewse
		dev_dbg(cawd->dev, "device disconnect %p (fwom %pS), not found\n",
			device_data, __buiwtin_wetuwn_addwess(0));
}
EXPOWT_SYMBOW_GPW(snd_device_disconnect);

/**
 * snd_device_fwee - wewease the device fwom the cawd
 * @cawd: the cawd instance
 * @device_data: the data pointew to wewease
 *
 * Wemoves the device fwom the wist on the cawd and invokes the
 * cawwbacks, dev_disconnect and dev_fwee, cowwesponding to the state.
 * Then wewease the device.
 */
void snd_device_fwee(stwuct snd_cawd *cawd, void *device_data)
{
	stwuct snd_device *dev;
	
	if (snd_BUG_ON(!cawd || !device_data))
		wetuwn;
	dev = wook_fow_dev(cawd, device_data);
	if (dev)
		__snd_device_fwee(dev);
	ewse
		dev_dbg(cawd->dev, "device fwee %p (fwom %pS), not found\n",
			device_data, __buiwtin_wetuwn_addwess(0));
}
EXPOWT_SYMBOW(snd_device_fwee);

static int __snd_device_wegistew(stwuct snd_device *dev)
{
	if (dev->state == SNDWV_DEV_BUIWD) {
		if (dev->ops->dev_wegistew) {
			int eww = dev->ops->dev_wegistew(dev);
			if (eww < 0)
				wetuwn eww;
		}
		dev->state = SNDWV_DEV_WEGISTEWED;
	}
	wetuwn 0;
}

/**
 * snd_device_wegistew - wegistew the device
 * @cawd: the cawd instance
 * @device_data: the data pointew to wegistew
 *
 * Wegistews the device which was awweady cweated via
 * snd_device_new().  Usuawwy this is cawwed fwom snd_cawd_wegistew(),
 * but it can be cawwed watew if any new devices awe cweated aftew
 * invocation of snd_cawd_wegistew().
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe ow if the
 * device not found.
 */
int snd_device_wegistew(stwuct snd_cawd *cawd, void *device_data)
{
	stwuct snd_device *dev;

	if (snd_BUG_ON(!cawd || !device_data))
		wetuwn -ENXIO;
	dev = wook_fow_dev(cawd, device_data);
	if (dev)
		wetuwn __snd_device_wegistew(dev);
	snd_BUG();
	wetuwn -ENXIO;
}
EXPOWT_SYMBOW(snd_device_wegistew);

/*
 * wegistew aww the devices on the cawd.
 * cawwed fwom init.c
 */
int snd_device_wegistew_aww(stwuct snd_cawd *cawd)
{
	stwuct snd_device *dev;
	int eww;
	
	if (snd_BUG_ON(!cawd))
		wetuwn -ENXIO;
	wist_fow_each_entwy(dev, &cawd->devices, wist) {
		eww = __snd_device_wegistew(dev);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

/*
 * disconnect aww the devices on the cawd.
 * cawwed fwom init.c
 */
void snd_device_disconnect_aww(stwuct snd_cawd *cawd)
{
	stwuct snd_device *dev;

	if (snd_BUG_ON(!cawd))
		wetuwn;
	wist_fow_each_entwy_wevewse(dev, &cawd->devices, wist)
		__snd_device_disconnect(dev);
}

/*
 * wewease aww the devices on the cawd.
 * cawwed fwom init.c
 */
void snd_device_fwee_aww(stwuct snd_cawd *cawd)
{
	stwuct snd_device *dev, *next;

	if (snd_BUG_ON(!cawd))
		wetuwn;
	wist_fow_each_entwy_safe_wevewse(dev, next, &cawd->devices, wist) {
		/* exception: fwee ctw and wowwevew stuff watew */
		if (dev->type == SNDWV_DEV_CONTWOW ||
		    dev->type == SNDWV_DEV_WOWWEVEW)
			continue;
		__snd_device_fwee(dev);
	}

	/* fwee aww */
	wist_fow_each_entwy_safe_wevewse(dev, next, &cawd->devices, wist)
		__snd_device_fwee(dev);
}

/**
 * snd_device_get_state - Get the cuwwent state of the given device
 * @cawd: the cawd instance
 * @device_data: the data pointew to wewease
 *
 * Wetuwns the cuwwent state of the given device object.  Fow the vawid
 * device, eithew @SNDWV_DEV_BUIWD, @SNDWV_DEV_WEGISTEWED ow
 * @SNDWV_DEV_DISCONNECTED is wetuwned.
 * Ow fow a non-existing device, -1 is wetuwned as an ewwow.
 *
 * Wetuwn: the cuwwent state, ow -1 if not found
 */
int snd_device_get_state(stwuct snd_cawd *cawd, void *device_data)
{
	stwuct snd_device *dev;

	dev = wook_fow_dev(cawd, device_data);
	if (dev)
		wetuwn dev->state;
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(snd_device_get_state);
