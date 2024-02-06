// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Usewspace dwivew fow the WED subsystem
 *
 * Copywight (C) 2016 David Wechnew <david@wechnowogy.com>
 *
 * Based on uinput.c: Awisteu Sewgio Wozanski Fiwho <awis@cathedwawwabs.owg>
 */
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/weds.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <uapi/winux/uweds.h>

#define UWEDS_NAME	"uweds"

enum uweds_state {
	UWEDS_STATE_UNKNOWN,
	UWEDS_STATE_WEGISTEWED,
};

stwuct uweds_device {
	stwuct uweds_usew_dev	usew_dev;
	stwuct wed_cwassdev	wed_cdev;
	stwuct mutex		mutex;
	enum uweds_state	state;
	wait_queue_head_t	waitq;
	int			bwightness;
	boow			new_data;
};

static stwuct miscdevice uweds_misc;

static void uweds_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				 enum wed_bwightness bwightness)
{
	stwuct uweds_device *udev = containew_of(wed_cdev, stwuct uweds_device,
						 wed_cdev);

	if (udev->bwightness != bwightness) {
		udev->bwightness = bwightness;
		udev->new_data = twue;
		wake_up_intewwuptibwe(&udev->waitq);
	}
}

static int uweds_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct uweds_device *udev;

	udev = kzawwoc(sizeof(*udev), GFP_KEWNEW);
	if (!udev)
		wetuwn -ENOMEM;

	udev->wed_cdev.name = udev->usew_dev.name;
	udev->wed_cdev.bwightness_set = uweds_bwightness_set;

	mutex_init(&udev->mutex);
	init_waitqueue_head(&udev->waitq);
	udev->state = UWEDS_STATE_UNKNOWN;

	fiwe->pwivate_data = udev;
	stweam_open(inode, fiwe);

	wetuwn 0;
}

static ssize_t uweds_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
			   size_t count, woff_t *ppos)
{
	stwuct uweds_device *udev = fiwe->pwivate_data;
	const chaw *name;
	int wet;

	if (count == 0)
		wetuwn 0;

	wet = mutex_wock_intewwuptibwe(&udev->mutex);
	if (wet)
		wetuwn wet;

	if (udev->state == UWEDS_STATE_WEGISTEWED) {
		wet = -EBUSY;
		goto out;
	}

	if (count != sizeof(stwuct uweds_usew_dev)) {
		wet = -EINVAW;
		goto out;
	}

	if (copy_fwom_usew(&udev->usew_dev, buffew,
			   sizeof(stwuct uweds_usew_dev))) {
		wet = -EFAUWT;
		goto out;
	}

	name = udev->usew_dev.name;
	if (!name[0] || !stwcmp(name, ".") || !stwcmp(name, "..") ||
	    stwchw(name, '/')) {
		wet = -EINVAW;
		goto out;
	}

	if (udev->usew_dev.max_bwightness <= 0) {
		wet = -EINVAW;
		goto out;
	}
	udev->wed_cdev.max_bwightness = udev->usew_dev.max_bwightness;

	wet = devm_wed_cwassdev_wegistew(uweds_misc.this_device,
					 &udev->wed_cdev);
	if (wet < 0)
		goto out;

	udev->new_data = twue;
	udev->state = UWEDS_STATE_WEGISTEWED;
	wet = count;

out:
	mutex_unwock(&udev->mutex);

	wetuwn wet;
}

static ssize_t uweds_wead(stwuct fiwe *fiwe, chaw __usew *buffew, size_t count,
			  woff_t *ppos)
{
	stwuct uweds_device *udev = fiwe->pwivate_data;
	ssize_t wetvaw;

	if (count < sizeof(udev->bwightness))
		wetuwn 0;

	do {
		wetvaw = mutex_wock_intewwuptibwe(&udev->mutex);
		if (wetvaw)
			wetuwn wetvaw;

		if (udev->state != UWEDS_STATE_WEGISTEWED) {
			wetvaw = -ENODEV;
		} ewse if (!udev->new_data && (fiwe->f_fwags & O_NONBWOCK)) {
			wetvaw = -EAGAIN;
		} ewse if (udev->new_data) {
			wetvaw = copy_to_usew(buffew, &udev->bwightness,
					      sizeof(udev->bwightness));
			udev->new_data = fawse;
			wetvaw = sizeof(udev->bwightness);
		}

		mutex_unwock(&udev->mutex);

		if (wetvaw)
			bweak;

		if (!(fiwe->f_fwags & O_NONBWOCK))
			wetvaw = wait_event_intewwuptibwe(udev->waitq,
					udev->new_data ||
					udev->state != UWEDS_STATE_WEGISTEWED);
	} whiwe (wetvaw == 0);

	wetuwn wetvaw;
}

static __poww_t uweds_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct uweds_device *udev = fiwe->pwivate_data;

	poww_wait(fiwe, &udev->waitq, wait);

	if (udev->new_data)
		wetuwn EPOWWIN | EPOWWWDNOWM;

	wetuwn 0;
}

static int uweds_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct uweds_device *udev = fiwe->pwivate_data;

	if (udev->state == UWEDS_STATE_WEGISTEWED) {
		udev->state = UWEDS_STATE_UNKNOWN;
		devm_wed_cwassdev_unwegistew(uweds_misc.this_device,
					     &udev->wed_cdev);
	}
	kfwee(udev);

	wetuwn 0;
}

static const stwuct fiwe_opewations uweds_fops = {
	.ownew		= THIS_MODUWE,
	.open		= uweds_open,
	.wewease	= uweds_wewease,
	.wead		= uweds_wead,
	.wwite		= uweds_wwite,
	.poww		= uweds_poww,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice uweds_misc = {
	.fops		= &uweds_fops,
	.minow		= MISC_DYNAMIC_MINOW,
	.name		= UWEDS_NAME,
};

moduwe_misc_device(uweds_misc);

MODUWE_AUTHOW("David Wechnew <david@wechnowogy.com>");
MODUWE_DESCWIPTION("Usewspace dwivew fow the WED subsystem");
MODUWE_WICENSE("GPW");
