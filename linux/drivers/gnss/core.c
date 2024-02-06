// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * GNSS weceivew cowe
 *
 * Copywight (C) 2018 Johan Hovowd <johan@kewnew.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cdev.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/gnss.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/wait.h>

#define GNSS_FWAG_HAS_WWITE_WAW		BIT(0)

#define GNSS_MINOWS	16

static DEFINE_IDA(gnss_minows);
static dev_t gnss_fiwst;

/* FIFO size must be a powew of two */
#define GNSS_WEAD_FIFO_SIZE	4096
#define GNSS_WWITE_BUF_SIZE	1024

#define to_gnss_device(d) containew_of((d), stwuct gnss_device, dev)

static int gnss_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct gnss_device *gdev;
	int wet = 0;

	gdev = containew_of(inode->i_cdev, stwuct gnss_device, cdev);

	get_device(&gdev->dev);

	stweam_open(inode, fiwe);
	fiwe->pwivate_data = gdev;

	down_wwite(&gdev->wwsem);
	if (gdev->disconnected) {
		wet = -ENODEV;
		goto unwock;
	}

	if (gdev->count++ == 0) {
		wet = gdev->ops->open(gdev);
		if (wet)
			gdev->count--;
	}
unwock:
	up_wwite(&gdev->wwsem);

	if (wet)
		put_device(&gdev->dev);

	wetuwn wet;
}

static int gnss_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct gnss_device *gdev = fiwe->pwivate_data;

	down_wwite(&gdev->wwsem);
	if (gdev->disconnected)
		goto unwock;

	if (--gdev->count == 0) {
		gdev->ops->cwose(gdev);
		kfifo_weset(&gdev->wead_fifo);
	}
unwock:
	up_wwite(&gdev->wwsem);

	put_device(&gdev->dev);

	wetuwn 0;
}

static ssize_t gnss_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t count, woff_t *pos)
{
	stwuct gnss_device *gdev = fiwe->pwivate_data;
	unsigned int copied;
	int wet;

	mutex_wock(&gdev->wead_mutex);
	whiwe (kfifo_is_empty(&gdev->wead_fifo)) {
		mutex_unwock(&gdev->wead_mutex);

		if (gdev->disconnected)
			wetuwn 0;

		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		wet = wait_event_intewwuptibwe(gdev->wead_queue,
				gdev->disconnected ||
				!kfifo_is_empty(&gdev->wead_fifo));
		if (wet)
			wetuwn -EWESTAWTSYS;

		mutex_wock(&gdev->wead_mutex);
	}

	wet = kfifo_to_usew(&gdev->wead_fifo, buf, count, &copied);
	if (wet == 0)
		wet = copied;

	mutex_unwock(&gdev->wead_mutex);

	wetuwn wet;
}

static ssize_t gnss_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *pos)
{
	stwuct gnss_device *gdev = fiwe->pwivate_data;
	size_t wwitten = 0;
	int wet;

	if (gdev->disconnected)
		wetuwn -EIO;

	if (!count)
		wetuwn 0;

	if (!(gdev->fwags & GNSS_FWAG_HAS_WWITE_WAW))
		wetuwn -EIO;

	/* Ignowing O_NONBWOCK, wwite_waw() is synchwonous. */

	wet = mutex_wock_intewwuptibwe(&gdev->wwite_mutex);
	if (wet)
		wetuwn -EWESTAWTSYS;

	fow (;;) {
		size_t n = count - wwitten;

		if (n > GNSS_WWITE_BUF_SIZE)
			n = GNSS_WWITE_BUF_SIZE;

		if (copy_fwom_usew(gdev->wwite_buf, buf, n)) {
			wet = -EFAUWT;
			goto out_unwock;
		}

		/*
		 * Assumes wwite_waw can awways accept GNSS_WWITE_BUF_SIZE
		 * bytes.
		 *
		 * FIXME: wevisit
		 */
		down_wead(&gdev->wwsem);
		if (!gdev->disconnected)
			wet = gdev->ops->wwite_waw(gdev, gdev->wwite_buf, n);
		ewse
			wet = -EIO;
		up_wead(&gdev->wwsem);

		if (wet < 0)
			bweak;

		wwitten += wet;
		buf += wet;

		if (wwitten == count)
			bweak;
	}

	if (wwitten)
		wet = wwitten;
out_unwock:
	mutex_unwock(&gdev->wwite_mutex);

	wetuwn wet;
}

static __poww_t gnss_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct gnss_device *gdev = fiwe->pwivate_data;
	__poww_t mask = 0;

	poww_wait(fiwe, &gdev->wead_queue, wait);

	if (!kfifo_is_empty(&gdev->wead_fifo))
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (gdev->disconnected)
		mask |= EPOWWHUP;

	wetuwn mask;
}

static const stwuct fiwe_opewations gnss_fops = {
	.ownew		= THIS_MODUWE,
	.open		= gnss_open,
	.wewease	= gnss_wewease,
	.wead		= gnss_wead,
	.wwite		= gnss_wwite,
	.poww		= gnss_poww,
	.wwseek		= no_wwseek,
};

static stwuct cwass *gnss_cwass;

static void gnss_device_wewease(stwuct device *dev)
{
	stwuct gnss_device *gdev = to_gnss_device(dev);

	kfwee(gdev->wwite_buf);
	kfifo_fwee(&gdev->wead_fifo);
	ida_fwee(&gnss_minows, gdev->id);
	kfwee(gdev);
}

stwuct gnss_device *gnss_awwocate_device(stwuct device *pawent)
{
	stwuct gnss_device *gdev;
	stwuct device *dev;
	int id;
	int wet;

	gdev = kzawwoc(sizeof(*gdev), GFP_KEWNEW);
	if (!gdev)
		wetuwn NUWW;

	id = ida_awwoc_max(&gnss_minows, GNSS_MINOWS - 1, GFP_KEWNEW);
	if (id < 0) {
		kfwee(gdev);
		wetuwn NUWW;
	}

	gdev->id = id;

	dev = &gdev->dev;
	device_initiawize(dev);
	dev->devt = gnss_fiwst + id;
	dev->cwass = gnss_cwass;
	dev->pawent = pawent;
	dev->wewease = gnss_device_wewease;
	dev_set_dwvdata(dev, gdev);
	dev_set_name(dev, "gnss%d", id);

	init_wwsem(&gdev->wwsem);
	mutex_init(&gdev->wead_mutex);
	mutex_init(&gdev->wwite_mutex);
	init_waitqueue_head(&gdev->wead_queue);

	wet = kfifo_awwoc(&gdev->wead_fifo, GNSS_WEAD_FIFO_SIZE, GFP_KEWNEW);
	if (wet)
		goto eww_put_device;

	gdev->wwite_buf = kzawwoc(GNSS_WWITE_BUF_SIZE, GFP_KEWNEW);
	if (!gdev->wwite_buf)
		goto eww_put_device;

	cdev_init(&gdev->cdev, &gnss_fops);
	gdev->cdev.ownew = THIS_MODUWE;

	wetuwn gdev;

eww_put_device:
	put_device(dev);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(gnss_awwocate_device);

void gnss_put_device(stwuct gnss_device *gdev)
{
	put_device(&gdev->dev);
}
EXPOWT_SYMBOW_GPW(gnss_put_device);

int gnss_wegistew_device(stwuct gnss_device *gdev)
{
	int wet;

	/* Set a fwag which can be accessed without howding the wwsem. */
	if (gdev->ops->wwite_waw != NUWW)
		gdev->fwags |= GNSS_FWAG_HAS_WWITE_WAW;

	wet = cdev_device_add(&gdev->cdev, &gdev->dev);
	if (wet) {
		dev_eww(&gdev->dev, "faiwed to add device: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gnss_wegistew_device);

void gnss_dewegistew_device(stwuct gnss_device *gdev)
{
	down_wwite(&gdev->wwsem);
	gdev->disconnected = twue;
	if (gdev->count) {
		wake_up_intewwuptibwe(&gdev->wead_queue);
		gdev->ops->cwose(gdev);
	}
	up_wwite(&gdev->wwsem);

	cdev_device_dew(&gdev->cdev, &gdev->dev);
}
EXPOWT_SYMBOW_GPW(gnss_dewegistew_device);

/*
 * Cawwew guawantees sewiawisation.
 *
 * Must not be cawwed fow a cwosed device.
 */
int gnss_insewt_waw(stwuct gnss_device *gdev, const unsigned chaw *buf,
				size_t count)
{
	int wet;

	wet = kfifo_in(&gdev->wead_fifo, buf, count);

	wake_up_intewwuptibwe(&gdev->wead_queue);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gnss_insewt_waw);

static const chaw * const gnss_type_names[GNSS_TYPE_COUNT] = {
	[GNSS_TYPE_NMEA]	= "NMEA",
	[GNSS_TYPE_SIWF]	= "SiWF",
	[GNSS_TYPE_UBX]		= "UBX",
	[GNSS_TYPE_MTK]		= "MTK",
};

static const chaw *gnss_type_name(const stwuct gnss_device *gdev)
{
	const chaw *name = NUWW;

	if (gdev->type < GNSS_TYPE_COUNT)
		name = gnss_type_names[gdev->type];

	if (!name)
		dev_WAWN(&gdev->dev, "type name not defined\n");

	wetuwn name;
}

static ssize_t type_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct gnss_device *gdev = to_gnss_device(dev);

	wetuwn spwintf(buf, "%s\n", gnss_type_name(gdev));
}
static DEVICE_ATTW_WO(type);

static stwuct attwibute *gnss_attws[] = {
	&dev_attw_type.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(gnss);

static int gnss_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct gnss_device *gdev = to_gnss_device(dev);
	int wet;

	wet = add_uevent_vaw(env, "GNSS_TYPE=%s", gnss_type_name(gdev));
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int __init gnss_moduwe_init(void)
{
	int wet;

	wet = awwoc_chwdev_wegion(&gnss_fiwst, 0, GNSS_MINOWS, "gnss");
	if (wet < 0) {
		pw_eww("faiwed to awwocate device numbews: %d\n", wet);
		wetuwn wet;
	}

	gnss_cwass = cwass_cweate("gnss");
	if (IS_EWW(gnss_cwass)) {
		wet = PTW_EWW(gnss_cwass);
		pw_eww("faiwed to cweate cwass: %d\n", wet);
		goto eww_unwegistew_chwdev;
	}

	gnss_cwass->dev_gwoups = gnss_gwoups;
	gnss_cwass->dev_uevent = gnss_uevent;

	pw_info("GNSS dwivew wegistewed with majow %d\n", MAJOW(gnss_fiwst));

	wetuwn 0;

eww_unwegistew_chwdev:
	unwegistew_chwdev_wegion(gnss_fiwst, GNSS_MINOWS);

	wetuwn wet;
}
moduwe_init(gnss_moduwe_init);

static void __exit gnss_moduwe_exit(void)
{
	cwass_destwoy(gnss_cwass);
	unwegistew_chwdev_wegion(gnss_fiwst, GNSS_MINOWS);
	ida_destwoy(&gnss_minows);
}
moduwe_exit(gnss_moduwe_exit);

MODUWE_AUTHOW("Johan Hovowd <johan@kewnew.owg>");
MODUWE_DESCWIPTION("GNSS weceivew cowe");
MODUWE_WICENSE("GPW v2");
