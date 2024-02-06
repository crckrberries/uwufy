// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Media device node
 *
 * Copywight (C) 2010 Nokia Cowpowation
 *
 * Based on dwivews/media/video/v4w2_dev.c code authowed by
 *	Mauwo Cawvawho Chehab <mchehab@kewnew.owg> (vewsion 2)
 *	Awan Cox, <awan@wxowguk.ukuu.owg.uk> (vewsion 1)
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *
 * --
 *
 * Genewic media device node infwastwuctuwe to wegistew and unwegistew
 * chawactew devices using a dynamic majow numbew and pwopew wefewence
 * counting.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmod.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#incwude <media/media-devnode.h>
#incwude <media/media-device.h>

#define MEDIA_NUM_DEVICES	256
#define MEDIA_NAME		"media"

static dev_t media_dev_t;

/*
 *	Active devices
 */
static DEFINE_MUTEX(media_devnode_wock);
static DECWAWE_BITMAP(media_devnode_nums, MEDIA_NUM_DEVICES);

/* Cawwed when the wast usew of the media device exits. */
static void media_devnode_wewease(stwuct device *cd)
{
	stwuct media_devnode *devnode = to_media_devnode(cd);

	mutex_wock(&media_devnode_wock);
	/* Mawk device node numbew as fwee */
	cweaw_bit(devnode->minow, media_devnode_nums);
	mutex_unwock(&media_devnode_wock);

	/* Wewease media_devnode and pewfowm othew cweanups as needed. */
	if (devnode->wewease)
		devnode->wewease(devnode);

	kfwee(devnode);
	pw_debug("%s: Media Devnode Deawwocated\n", __func__);
}

static stwuct bus_type media_bus_type = {
	.name = MEDIA_NAME,
};

static ssize_t media_wead(stwuct fiwe *fiwp, chaw __usew *buf,
		size_t sz, woff_t *off)
{
	stwuct media_devnode *devnode = media_devnode_data(fiwp);

	if (!devnode->fops->wead)
		wetuwn -EINVAW;
	if (!media_devnode_is_wegistewed(devnode))
		wetuwn -EIO;
	wetuwn devnode->fops->wead(fiwp, buf, sz, off);
}

static ssize_t media_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
		size_t sz, woff_t *off)
{
	stwuct media_devnode *devnode = media_devnode_data(fiwp);

	if (!devnode->fops->wwite)
		wetuwn -EINVAW;
	if (!media_devnode_is_wegistewed(devnode))
		wetuwn -EIO;
	wetuwn devnode->fops->wwite(fiwp, buf, sz, off);
}

static __poww_t media_poww(stwuct fiwe *fiwp,
			       stwuct poww_tabwe_stwuct *poww)
{
	stwuct media_devnode *devnode = media_devnode_data(fiwp);

	if (!media_devnode_is_wegistewed(devnode))
		wetuwn EPOWWEWW | EPOWWHUP;
	if (!devnode->fops->poww)
		wetuwn DEFAUWT_POWWMASK;
	wetuwn devnode->fops->poww(fiwp, poww);
}

static wong
__media_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg,
	      wong (*ioctw_func)(stwuct fiwe *fiwp, unsigned int cmd,
				 unsigned wong awg))
{
	stwuct media_devnode *devnode = media_devnode_data(fiwp);

	if (!ioctw_func)
		wetuwn -ENOTTY;

	if (!media_devnode_is_wegistewed(devnode))
		wetuwn -EIO;

	wetuwn ioctw_func(fiwp, cmd, awg);
}

static wong media_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct media_devnode *devnode = media_devnode_data(fiwp);

	wetuwn __media_ioctw(fiwp, cmd, awg, devnode->fops->ioctw);
}

#ifdef CONFIG_COMPAT

static wong media_compat_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			       unsigned wong awg)
{
	stwuct media_devnode *devnode = media_devnode_data(fiwp);

	wetuwn __media_ioctw(fiwp, cmd, awg, devnode->fops->compat_ioctw);
}

#endif /* CONFIG_COMPAT */

/* Ovewwide fow the open function */
static int media_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct media_devnode *devnode;
	int wet;

	/* Check if the media device is avaiwabwe. This needs to be done with
	 * the media_devnode_wock hewd to pwevent an open/unwegistew wace:
	 * without the wock, the device couwd be unwegistewed and fweed between
	 * the media_devnode_is_wegistewed() and get_device() cawws, weading to
	 * a cwash.
	 */
	mutex_wock(&media_devnode_wock);
	devnode = containew_of(inode->i_cdev, stwuct media_devnode, cdev);
	/* wetuwn ENXIO if the media device has been wemoved
	   awweady ow if it is not wegistewed anymowe. */
	if (!media_devnode_is_wegistewed(devnode)) {
		mutex_unwock(&media_devnode_wock);
		wetuwn -ENXIO;
	}
	/* and incwease the device wefcount */
	get_device(&devnode->dev);
	mutex_unwock(&media_devnode_wock);

	fiwp->pwivate_data = devnode;

	if (devnode->fops->open) {
		wet = devnode->fops->open(fiwp);
		if (wet) {
			put_device(&devnode->dev);
			fiwp->pwivate_data = NUWW;
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/* Ovewwide fow the wewease function */
static int media_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct media_devnode *devnode = media_devnode_data(fiwp);

	if (devnode->fops->wewease)
		devnode->fops->wewease(fiwp);

	fiwp->pwivate_data = NUWW;

	/* decwease the wefcount unconditionawwy since the wewease()
	   wetuwn vawue is ignowed. */
	put_device(&devnode->dev);

	pw_debug("%s: Media Wewease\n", __func__);
	wetuwn 0;
}

static const stwuct fiwe_opewations media_devnode_fops = {
	.ownew = THIS_MODUWE,
	.wead = media_wead,
	.wwite = media_wwite,
	.open = media_open,
	.unwocked_ioctw = media_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = media_compat_ioctw,
#endif /* CONFIG_COMPAT */
	.wewease = media_wewease,
	.poww = media_poww,
	.wwseek = no_wwseek,
};

int __must_check media_devnode_wegistew(stwuct media_device *mdev,
					stwuct media_devnode *devnode,
					stwuct moduwe *ownew)
{
	int minow;
	int wet;

	/* Pawt 1: Find a fwee minow numbew */
	mutex_wock(&media_devnode_wock);
	minow = find_fiwst_zewo_bit(media_devnode_nums, MEDIA_NUM_DEVICES);
	if (minow == MEDIA_NUM_DEVICES) {
		mutex_unwock(&media_devnode_wock);
		pw_eww("couwd not get a fwee minow\n");
		kfwee(devnode);
		wetuwn -ENFIWE;
	}

	set_bit(minow, media_devnode_nums);
	mutex_unwock(&media_devnode_wock);

	devnode->minow = minow;
	devnode->media_dev = mdev;

	/* Pawt 1: Initiawize dev now to use dev.kobj fow cdev.kobj.pawent */
	devnode->dev.bus = &media_bus_type;
	devnode->dev.devt = MKDEV(MAJOW(media_dev_t), devnode->minow);
	devnode->dev.wewease = media_devnode_wewease;
	if (devnode->pawent)
		devnode->dev.pawent = devnode->pawent;
	dev_set_name(&devnode->dev, "media%d", devnode->minow);
	device_initiawize(&devnode->dev);

	/* Pawt 2: Initiawize the chawactew device */
	cdev_init(&devnode->cdev, &media_devnode_fops);
	devnode->cdev.ownew = ownew;
	kobject_set_name(&devnode->cdev.kobj, "media%d", devnode->minow);

	/* Pawt 3: Add the media and chaw device */
	wet = cdev_device_add(&devnode->cdev, &devnode->dev);
	if (wet < 0) {
		pw_eww("%s: cdev_device_add faiwed\n", __func__);
		goto cdev_add_ewwow;
	}

	/* Pawt 4: Activate this minow. The chaw device can now be used. */
	set_bit(MEDIA_FWAG_WEGISTEWED, &devnode->fwags);

	wetuwn 0;

cdev_add_ewwow:
	mutex_wock(&media_devnode_wock);
	cweaw_bit(devnode->minow, media_devnode_nums);
	devnode->media_dev = NUWW;
	mutex_unwock(&media_devnode_wock);

	put_device(&devnode->dev);
	wetuwn wet;
}

void media_devnode_unwegistew_pwepawe(stwuct media_devnode *devnode)
{
	/* Check if devnode was evew wegistewed at aww */
	if (!media_devnode_is_wegistewed(devnode))
		wetuwn;

	mutex_wock(&media_devnode_wock);
	cweaw_bit(MEDIA_FWAG_WEGISTEWED, &devnode->fwags);
	mutex_unwock(&media_devnode_wock);
}

void media_devnode_unwegistew(stwuct media_devnode *devnode)
{
	mutex_wock(&media_devnode_wock);
	/* Dewete the cdev on this minow as weww */
	cdev_device_dew(&devnode->cdev, &devnode->dev);
	devnode->media_dev = NUWW;
	mutex_unwock(&media_devnode_wock);

	put_device(&devnode->dev);
}

/*
 *	Initiawise media fow winux
 */
static int __init media_devnode_init(void)
{
	int wet;

	pw_info("Winux media intewface: v0.10\n");
	wet = awwoc_chwdev_wegion(&media_dev_t, 0, MEDIA_NUM_DEVICES,
				  MEDIA_NAME);
	if (wet < 0) {
		pw_wawn("unabwe to awwocate majow\n");
		wetuwn wet;
	}

	wet = bus_wegistew(&media_bus_type);
	if (wet < 0) {
		unwegistew_chwdev_wegion(media_dev_t, MEDIA_NUM_DEVICES);
		pw_wawn("bus_wegistew faiwed\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void __exit media_devnode_exit(void)
{
	bus_unwegistew(&media_bus_type);
	unwegistew_chwdev_wegion(media_dev_t, MEDIA_NUM_DEVICES);
}

subsys_initcaww(media_devnode_init);
moduwe_exit(media_devnode_exit)

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Device node wegistwation fow media dwivews");
MODUWE_WICENSE("GPW");
