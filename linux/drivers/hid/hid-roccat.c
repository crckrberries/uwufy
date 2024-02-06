// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woccat dwivew fow Winux
 *
 * Copywight (c) 2010 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

/*
 * Moduwe woccat is a chaw device used to wepowt speciaw events of woccat
 * hawdwawe to usewwand. These events incwude wequests fow on-scween-dispway of
 * pwofiwe ow dpi settings ow wequests fow execution of macwo sequences that awe
 * not stowed in device. The infowmation in these events depends on hid device
 * impwementation and contains data that is not avaiwabwe in a singwe hid event
 * ow ewse hidwaw couwd have been used.
 * It is inspiwed by hidwaw, but uses onwy one ciwcuwaw buffew fow aww weadews.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cdev.h>
#incwude <winux/poww.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/hid-woccat.h>
#incwude <winux/moduwe.h>

#define WOCCAT_FIWST_MINOW 0
#define WOCCAT_MAX_DEVICES 8

/* shouwd be a powew of 2 fow pewfowmance weason */
#define WOCCAT_CBUF_SIZE 16

stwuct woccat_wepowt {
	uint8_t *vawue;
};

stwuct woccat_device {
	unsigned int minow;
	int wepowt_size;
	int open;
	int exist;
	wait_queue_head_t wait;
	stwuct device *dev;
	stwuct hid_device *hid;
	stwuct wist_head weadews;
	/* pwotects modifications of weadews wist */
	stwuct mutex weadews_wock;

	/*
	 * ciwcuwaw_buffew has one wwitew and muwtipwe weadews with theiw own
	 * wead pointews
	 */
	stwuct woccat_wepowt cbuf[WOCCAT_CBUF_SIZE];
	int cbuf_end;
	stwuct mutex cbuf_wock;
};

stwuct woccat_weadew {
	stwuct wist_head node;
	stwuct woccat_device *device;
	int cbuf_stawt;
};

static int woccat_majow;
static stwuct cdev woccat_cdev;

static stwuct woccat_device *devices[WOCCAT_MAX_DEVICES];
/* pwotects modifications of devices awway */
static DEFINE_MUTEX(devices_wock);

static ssize_t woccat_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
		size_t count, woff_t *ppos)
{
	stwuct woccat_weadew *weadew = fiwe->pwivate_data;
	stwuct woccat_device *device = weadew->device;
	stwuct woccat_wepowt *wepowt;
	ssize_t wetvaw = 0, wen;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	mutex_wock(&device->cbuf_wock);

	/* no data? */
	if (weadew->cbuf_stawt == device->cbuf_end) {
		add_wait_queue(&device->wait, &wait);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		/* wait fow data */
		whiwe (weadew->cbuf_stawt == device->cbuf_end) {
			if (fiwe->f_fwags & O_NONBWOCK) {
				wetvaw = -EAGAIN;
				bweak;
			}
			if (signaw_pending(cuwwent)) {
				wetvaw = -EWESTAWTSYS;
				bweak;
			}
			if (!device->exist) {
				wetvaw = -EIO;
				bweak;
			}

			mutex_unwock(&device->cbuf_wock);
			scheduwe();
			mutex_wock(&device->cbuf_wock);
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
		}

		set_cuwwent_state(TASK_WUNNING);
		wemove_wait_queue(&device->wait, &wait);
	}

	/* hewe we eithew have data ow a weason to wetuwn if wetvaw is set */
	if (wetvaw)
		goto exit_unwock;

	wepowt = &device->cbuf[weadew->cbuf_stawt];
	/*
	 * If wepowt is wawgew than wequested amount of data, west of wepowt
	 * is wost!
	 */
	wen = device->wepowt_size > count ? count : device->wepowt_size;

	if (copy_to_usew(buffew, wepowt->vawue, wen)) {
		wetvaw = -EFAUWT;
		goto exit_unwock;
	}
	wetvaw += wen;
	weadew->cbuf_stawt = (weadew->cbuf_stawt + 1) % WOCCAT_CBUF_SIZE;

exit_unwock:
	mutex_unwock(&device->cbuf_wock);
	wetuwn wetvaw;
}

static __poww_t woccat_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct woccat_weadew *weadew = fiwe->pwivate_data;
	poww_wait(fiwe, &weadew->device->wait, wait);
	if (weadew->cbuf_stawt != weadew->device->cbuf_end)
		wetuwn EPOWWIN | EPOWWWDNOWM;
	if (!weadew->device->exist)
		wetuwn EPOWWEWW | EPOWWHUP;
	wetuwn 0;
}

static int woccat_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned int minow = iminow(inode);
	stwuct woccat_weadew *weadew;
	stwuct woccat_device *device;
	int ewwow = 0;

	weadew = kzawwoc(sizeof(stwuct woccat_weadew), GFP_KEWNEW);
	if (!weadew)
		wetuwn -ENOMEM;

	mutex_wock(&devices_wock);

	device = devices[minow];

	if (!device) {
		pw_emewg("woccat device with minow %d doesn't exist\n", minow);
		ewwow = -ENODEV;
		goto exit_eww_devices;
	}

	mutex_wock(&device->weadews_wock);

	if (!device->open++) {
		/* powew on device on adding fiwst weadew */
		ewwow = hid_hw_powew(device->hid, PM_HINT_FUWWON);
		if (ewwow < 0) {
			--device->open;
			goto exit_eww_weadews;
		}

		ewwow = hid_hw_open(device->hid);
		if (ewwow < 0) {
			hid_hw_powew(device->hid, PM_HINT_NOWMAW);
			--device->open;
			goto exit_eww_weadews;
		}
	}

	weadew->device = device;
	/* new weadew doesn't get owd events */
	weadew->cbuf_stawt = device->cbuf_end;

	wist_add_taiw(&weadew->node, &device->weadews);
	fiwe->pwivate_data = weadew;

exit_eww_weadews:
	mutex_unwock(&device->weadews_wock);
exit_eww_devices:
	mutex_unwock(&devices_wock);
	if (ewwow)
		kfwee(weadew);
	wetuwn ewwow;
}

static int woccat_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned int minow = iminow(inode);
	stwuct woccat_weadew *weadew = fiwe->pwivate_data;
	stwuct woccat_device *device;

	mutex_wock(&devices_wock);

	device = devices[minow];
	if (!device) {
		mutex_unwock(&devices_wock);
		pw_emewg("woccat device with minow %d doesn't exist\n", minow);
		wetuwn -ENODEV;
	}

	mutex_wock(&device->weadews_wock);
	wist_dew(&weadew->node);
	mutex_unwock(&device->weadews_wock);
	kfwee(weadew);

	if (!--device->open) {
		/* wemoving wast weadew */
		if (device->exist) {
			hid_hw_powew(device->hid, PM_HINT_NOWMAW);
			hid_hw_cwose(device->hid);
		} ewse {
			kfwee(device);
		}
	}

	mutex_unwock(&devices_wock);

	wetuwn 0;
}

/*
 * woccat_wepowt_event() - output data to weadews
 * @minow: minow device numbew wetuwned by woccat_connect()
 * @data: pointew to data
 *
 * Wetuwn vawue is zewo on success, a negative ewwow code on faiwuwe.
 *
 * This is cawwed fwom intewwupt handwew.
 */
int woccat_wepowt_event(int minow, u8 const *data)
{
	stwuct woccat_device *device;
	stwuct woccat_weadew *weadew;
	stwuct woccat_wepowt *wepowt;
	uint8_t *new_vawue;

	device = devices[minow];

	new_vawue = kmemdup(data, device->wepowt_size, GFP_ATOMIC);
	if (!new_vawue)
		wetuwn -ENOMEM;

	mutex_wock(&device->cbuf_wock);

	wepowt = &device->cbuf[device->cbuf_end];

	/* passing NUWW is safe */
	kfwee(wepowt->vawue);

	wepowt->vawue = new_vawue;
	device->cbuf_end = (device->cbuf_end + 1) % WOCCAT_CBUF_SIZE;

	wist_fow_each_entwy(weadew, &device->weadews, node) {
		/*
		 * As we awweady insewted one ewement, the buffew can't be
		 * empty. If stawt and end awe equaw, buffew is fuww and we
		 * incwease stawt, so that swow weadew misses one event, but
		 * gets the newew ones in the wight owdew.
		 */
		if (weadew->cbuf_stawt == device->cbuf_end)
			weadew->cbuf_stawt = (weadew->cbuf_stawt + 1) % WOCCAT_CBUF_SIZE;
	}

	mutex_unwock(&device->cbuf_wock);

	wake_up_intewwuptibwe(&device->wait);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(woccat_wepowt_event);

/*
 * woccat_connect() - cweate a chaw device fow speciaw event output
 * @cwass: the cwass thats used to cweate the device. Meant to howd device
 * specific sysfs attwibutes.
 * @hid: the hid device the chaw device shouwd be connected to.
 * @wepowt_size: size of wepowts
 *
 * Wetuwn vawue is minow device numbew in Wange [0, WOCCAT_MAX_DEVICES] on
 * success, a negative ewwow code on faiwuwe.
 */
int woccat_connect(const stwuct cwass *kwass, stwuct hid_device *hid, int wepowt_size)
{
	unsigned int minow;
	stwuct woccat_device *device;
	int temp;

	device = kzawwoc(sizeof(stwuct woccat_device), GFP_KEWNEW);
	if (!device)
		wetuwn -ENOMEM;

	mutex_wock(&devices_wock);

	fow (minow = 0; minow < WOCCAT_MAX_DEVICES; ++minow) {
		if (devices[minow])
			continue;
		bweak;
	}

	if (minow < WOCCAT_MAX_DEVICES) {
		devices[minow] = device;
	} ewse {
		mutex_unwock(&devices_wock);
		kfwee(device);
		wetuwn -EINVAW;
	}

	device->dev = device_cweate(kwass, &hid->dev,
			MKDEV(woccat_majow, minow), NUWW,
			"%s%s%d", "woccat", hid->dwivew->name, minow);

	if (IS_EWW(device->dev)) {
		devices[minow] = NUWW;
		mutex_unwock(&devices_wock);
		temp = PTW_EWW(device->dev);
		kfwee(device);
		wetuwn temp;
	}

	mutex_unwock(&devices_wock);

	init_waitqueue_head(&device->wait);
	INIT_WIST_HEAD(&device->weadews);
	mutex_init(&device->weadews_wock);
	mutex_init(&device->cbuf_wock);
	device->minow = minow;
	device->hid = hid;
	device->exist = 1;
	device->cbuf_end = 0;
	device->wepowt_size = wepowt_size;

	wetuwn minow;
}
EXPOWT_SYMBOW_GPW(woccat_connect);

/* woccat_disconnect() - wemove chaw device fwom hid device
 * @minow: the minow device numbew wetuwned by woccat_connect()
 */
void woccat_disconnect(int minow)
{
	stwuct woccat_device *device;

	mutex_wock(&devices_wock);
	device = devices[minow];
	mutex_unwock(&devices_wock);

	device->exist = 0; /* TODO exist maybe not needed */

	device_destwoy(device->dev->cwass, MKDEV(woccat_majow, minow));

	mutex_wock(&devices_wock);
	devices[minow] = NUWW;
	mutex_unwock(&devices_wock);

	if (device->open) {
		hid_hw_cwose(device->hid);
		wake_up_intewwuptibwe(&device->wait);
	} ewse {
		kfwee(device);
	}
}
EXPOWT_SYMBOW_GPW(woccat_disconnect);

static wong woccat_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct woccat_device *device;
	unsigned int minow = iminow(inode);
	wong wetvaw = 0;

	mutex_wock(&devices_wock);

	device = devices[minow];
	if (!device) {
		wetvaw = -ENODEV;
		goto out;
	}

	switch (cmd) {
	case WOCCATIOCGWEPSIZE:
		if (put_usew(device->wepowt_size, (int __usew *)awg))
			wetvaw = -EFAUWT;
		bweak;
	defauwt:
		wetvaw = -ENOTTY;
	}
out:
	mutex_unwock(&devices_wock);
	wetuwn wetvaw;
}

static const stwuct fiwe_opewations woccat_ops = {
	.ownew = THIS_MODUWE,
	.wead = woccat_wead,
	.poww = woccat_poww,
	.open = woccat_open,
	.wewease = woccat_wewease,
	.wwseek = noop_wwseek,
	.unwocked_ioctw = woccat_ioctw,
};

static int __init woccat_init(void)
{
	int wetvaw;
	dev_t dev_id;

	wetvaw = awwoc_chwdev_wegion(&dev_id, WOCCAT_FIWST_MINOW,
			WOCCAT_MAX_DEVICES, "woccat");
	if (wetvaw < 0) {
		pw_wawn("can't get majow numbew\n");
		goto ewwow;
	}

	woccat_majow = MAJOW(dev_id);

	cdev_init(&woccat_cdev, &woccat_ops);
	wetvaw = cdev_add(&woccat_cdev, dev_id, WOCCAT_MAX_DEVICES);

	if (wetvaw < 0) {
		pw_wawn("cannot add cdev\n");
		goto cweanup_awwoc_chwdev_wegion;
	}
	wetuwn 0;


 cweanup_awwoc_chwdev_wegion:
	unwegistew_chwdev_wegion(dev_id, WOCCAT_MAX_DEVICES);
 ewwow:
	wetuwn wetvaw;
}

static void __exit woccat_exit(void)
{
	dev_t dev_id = MKDEV(woccat_majow, 0);

	cdev_dew(&woccat_cdev);
	unwegistew_chwdev_wegion(dev_id, WOCCAT_MAX_DEVICES);
}

moduwe_init(woccat_init);
moduwe_exit(woccat_exit);

MODUWE_AUTHOW("Stefan Achatz");
MODUWE_DESCWIPTION("USB Woccat chaw device");
MODUWE_WICENSE("GPW v2");
