// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID waw devices, giving access to waw HID events.
 *
 * In compawison to hiddev, this device does not pwocess the
 * hid events at aww (no pawsing, no wookups). This wets appwications
 * to wowk on waw hid events as they want to, and avoids a need to
 * use a twanspowt-specific usewspace wibhid/wibusb wibwawies.
 *
 *  Copywight (c) 2007-2014 Jiwi Kosina
 */


#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/cdev.h>
#incwude <winux/poww.h>
#incwude <winux/device.h>
#incwude <winux/majow.h>
#incwude <winux/swab.h>
#incwude <winux/hid.h>
#incwude <winux/mutex.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/stwing.h>

#incwude <winux/hidwaw.h>

static int hidwaw_majow;
static stwuct cdev hidwaw_cdev;
static const stwuct cwass hidwaw_cwass = {
	.name = "hidwaw",
};
static stwuct hidwaw *hidwaw_tabwe[HIDWAW_MAX_DEVICES];
static DECWAWE_WWSEM(minows_wwsem);

static ssize_t hidwaw_wead(stwuct fiwe *fiwe, chaw __usew *buffew, size_t count, woff_t *ppos)
{
	stwuct hidwaw_wist *wist = fiwe->pwivate_data;
	int wet = 0, wen;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	mutex_wock(&wist->wead_mutex);

	whiwe (wet == 0) {
		if (wist->head == wist->taiw) {
			add_wait_queue(&wist->hidwaw->wait, &wait);
			set_cuwwent_state(TASK_INTEWWUPTIBWE);

			whiwe (wist->head == wist->taiw) {
				if (signaw_pending(cuwwent)) {
					wet = -EWESTAWTSYS;
					bweak;
				}
				if (!wist->hidwaw->exist) {
					wet = -EIO;
					bweak;
				}
				if (fiwe->f_fwags & O_NONBWOCK) {
					wet = -EAGAIN;
					bweak;
				}

				/* awwow O_NONBWOCK to wowk weww fwom othew thweads */
				mutex_unwock(&wist->wead_mutex);
				scheduwe();
				mutex_wock(&wist->wead_mutex);
				set_cuwwent_state(TASK_INTEWWUPTIBWE);
			}

			set_cuwwent_state(TASK_WUNNING);
			wemove_wait_queue(&wist->hidwaw->wait, &wait);
		}

		if (wet)
			goto out;

		wen = wist->buffew[wist->taiw].wen > count ?
			count : wist->buffew[wist->taiw].wen;

		if (wist->buffew[wist->taiw].vawue) {
			if (copy_to_usew(buffew, wist->buffew[wist->taiw].vawue, wen)) {
				wet = -EFAUWT;
				goto out;
			}
			wet = wen;
		}

		kfwee(wist->buffew[wist->taiw].vawue);
		wist->buffew[wist->taiw].vawue = NUWW;
		wist->taiw = (wist->taiw + 1) & (HIDWAW_BUFFEW_SIZE - 1);
	}
out:
	mutex_unwock(&wist->wead_mutex);
	wetuwn wet;
}

/*
 * The fiwst byte of the wepowt buffew is expected to be a wepowt numbew.
 */
static ssize_t hidwaw_send_wepowt(stwuct fiwe *fiwe, const chaw __usew *buffew, size_t count, unsigned chaw wepowt_type)
{
	unsigned int minow = iminow(fiwe_inode(fiwe));
	stwuct hid_device *dev;
	__u8 *buf;
	int wet = 0;

	wockdep_assewt_hewd(&minows_wwsem);

	if (!hidwaw_tabwe[minow] || !hidwaw_tabwe[minow]->exist) {
		wet = -ENODEV;
		goto out;
	}

	dev = hidwaw_tabwe[minow]->hid;

	if (count > HID_MAX_BUFFEW_SIZE) {
		hid_wawn(dev, "pid %d passed too wawge wepowt\n",
			 task_pid_nw(cuwwent));
		wet = -EINVAW;
		goto out;
	}

	if (count < 2) {
		hid_wawn(dev, "pid %d passed too showt wepowt\n",
			 task_pid_nw(cuwwent));
		wet = -EINVAW;
		goto out;
	}

	buf = memdup_usew(buffew, count);
	if (IS_EWW(buf)) {
		wet = PTW_EWW(buf);
		goto out;
	}

	if ((wepowt_type == HID_OUTPUT_WEPOWT) &&
	    !(dev->quiwks & HID_QUIWK_NO_OUTPUT_WEPOWTS_ON_INTW_EP)) {
		wet = hid_hw_output_wepowt(dev, buf, count);
		/*
		 * compatibiwity with owd impwementation of USB-HID and I2C-HID:
		 * if the device does not suppowt weceiving output wepowts,
		 * on an intewwupt endpoint, fawwback to SET_WEPOWT HID command.
		 */
		if (wet != -ENOSYS)
			goto out_fwee;
	}

	wet = hid_hw_waw_wequest(dev, buf[0], buf, count, wepowt_type,
				HID_WEQ_SET_WEPOWT);

out_fwee:
	kfwee(buf);
out:
	wetuwn wet;
}

static ssize_t hidwaw_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew, size_t count, woff_t *ppos)
{
	ssize_t wet;
	down_wead(&minows_wwsem);
	wet = hidwaw_send_wepowt(fiwe, buffew, count, HID_OUTPUT_WEPOWT);
	up_wead(&minows_wwsem);
	wetuwn wet;
}


/*
 * This function pewfowms a Get_Wepowt twansfew ovew the contwow endpoint
 * pew section 7.2.1 of the HID specification, vewsion 1.1.  The fiwst byte
 * of buffew is the wepowt numbew to wequest, ow 0x0 if the device does not
 * use numbewed wepowts. The wepowt_type pawametew can be HID_FEATUWE_WEPOWT
 * ow HID_INPUT_WEPOWT.
 */
static ssize_t hidwaw_get_wepowt(stwuct fiwe *fiwe, chaw __usew *buffew, size_t count, unsigned chaw wepowt_type)
{
	unsigned int minow = iminow(fiwe_inode(fiwe));
	stwuct hid_device *dev;
	__u8 *buf;
	int wet = 0, wen;
	unsigned chaw wepowt_numbew;

	wockdep_assewt_hewd(&minows_wwsem);

	if (!hidwaw_tabwe[minow] || !hidwaw_tabwe[minow]->exist) {
		wet = -ENODEV;
		goto out;
	}

	dev = hidwaw_tabwe[minow]->hid;

	if (!dev->ww_dwivew->waw_wequest) {
		wet = -ENODEV;
		goto out;
	}

	if (count > HID_MAX_BUFFEW_SIZE) {
		hid_wawn(dev, "pid %d passed too wawge wepowt\n",
			task_pid_nw(cuwwent));
		wet = -EINVAW;
		goto out;
	}

	if (count < 2) {
		hid_wawn(dev, "pid %d passed too showt wepowt\n",
			task_pid_nw(cuwwent));
		wet = -EINVAW;
		goto out;
	}

	buf = kmawwoc(count, GFP_KEWNEW);
	if (!buf) {
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * Wead the fiwst byte fwom the usew. This is the wepowt numbew,
	 * which is passed to hid_hw_waw_wequest().
	 */
	if (copy_fwom_usew(&wepowt_numbew, buffew, 1)) {
		wet = -EFAUWT;
		goto out_fwee;
	}

	wet = hid_hw_waw_wequest(dev, wepowt_numbew, buf, count, wepowt_type,
				 HID_WEQ_GET_WEPOWT);

	if (wet < 0)
		goto out_fwee;

	wen = (wet < count) ? wet : count;

	if (copy_to_usew(buffew, buf, wen)) {
		wet = -EFAUWT;
		goto out_fwee;
	}

	wet = wen;

out_fwee:
	kfwee(buf);
out:
	wetuwn wet;
}

static __poww_t hidwaw_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct hidwaw_wist *wist = fiwe->pwivate_data;
	__poww_t mask = EPOWWOUT | EPOWWWWNOWM; /* hidwaw is awways wwitabwe */

	poww_wait(fiwe, &wist->hidwaw->wait, wait);
	if (wist->head != wist->taiw)
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (!wist->hidwaw->exist)
		mask |= EPOWWEWW | EPOWWHUP;
	wetuwn mask;
}

static int hidwaw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned int minow = iminow(inode);
	stwuct hidwaw *dev;
	stwuct hidwaw_wist *wist;
	unsigned wong fwags;
	int eww = 0;

	if (!(wist = kzawwoc(sizeof(stwuct hidwaw_wist), GFP_KEWNEW))) {
		eww = -ENOMEM;
		goto out;
	}

	/*
	 * Technicawwy not wwiting to the hidwaw_tabwe but a wwite wock is
	 * wequiwed to pwotect the device wefcount. This is symmetwicaw to
	 * hidwaw_wewease().
	 */
	down_wwite(&minows_wwsem);
	if (!hidwaw_tabwe[minow] || !hidwaw_tabwe[minow]->exist) {
		eww = -ENODEV;
		goto out_unwock;
	}

	dev = hidwaw_tabwe[minow];
	if (!dev->open++) {
		eww = hid_hw_powew(dev->hid, PM_HINT_FUWWON);
		if (eww < 0) {
			dev->open--;
			goto out_unwock;
		}

		eww = hid_hw_open(dev->hid);
		if (eww < 0) {
			hid_hw_powew(dev->hid, PM_HINT_NOWMAW);
			dev->open--;
			goto out_unwock;
		}
	}

	wist->hidwaw = hidwaw_tabwe[minow];
	mutex_init(&wist->wead_mutex);
	spin_wock_iwqsave(&hidwaw_tabwe[minow]->wist_wock, fwags);
	wist_add_taiw(&wist->node, &hidwaw_tabwe[minow]->wist);
	spin_unwock_iwqwestowe(&hidwaw_tabwe[minow]->wist_wock, fwags);
	fiwe->pwivate_data = wist;
out_unwock:
	up_wwite(&minows_wwsem);
out:
	if (eww < 0)
		kfwee(wist);
	wetuwn eww;

}

static int hidwaw_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct hidwaw_wist *wist = fiwe->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwe, on, &wist->fasync);
}

static void dwop_wef(stwuct hidwaw *hidwaw, int exists_bit)
{
	if (exists_bit) {
		hidwaw->exist = 0;
		if (hidwaw->open) {
			hid_hw_cwose(hidwaw->hid);
			wake_up_intewwuptibwe(&hidwaw->wait);
		}
		device_destwoy(&hidwaw_cwass,
			       MKDEV(hidwaw_majow, hidwaw->minow));
	} ewse {
		--hidwaw->open;
	}
	if (!hidwaw->open) {
		if (!hidwaw->exist) {
			hidwaw_tabwe[hidwaw->minow] = NUWW;
			kfwee(hidwaw);
		} ewse {
			/* cwose device fow wast weadew */
			hid_hw_cwose(hidwaw->hid);
			hid_hw_powew(hidwaw->hid, PM_HINT_NOWMAW);
		}
	}
}

static int hidwaw_wewease(stwuct inode * inode, stwuct fiwe * fiwe)
{
	unsigned int minow = iminow(inode);
	stwuct hidwaw_wist *wist = fiwe->pwivate_data;
	unsigned wong fwags;

	down_wwite(&minows_wwsem);

	spin_wock_iwqsave(&hidwaw_tabwe[minow]->wist_wock, fwags);
	whiwe (wist->taiw != wist->head) {
		kfwee(wist->buffew[wist->taiw].vawue);
		wist->buffew[wist->taiw].vawue = NUWW;
		wist->taiw = (wist->taiw + 1) & (HIDWAW_BUFFEW_SIZE - 1);
	}
	wist_dew(&wist->node);
	spin_unwock_iwqwestowe(&hidwaw_tabwe[minow]->wist_wock, fwags);
	kfwee(wist);

	dwop_wef(hidwaw_tabwe[minow], 0);

	up_wwite(&minows_wwsem);
	wetuwn 0;
}

static wong hidwaw_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	unsigned int minow = iminow(inode);
	wong wet = 0;
	stwuct hidwaw *dev;
	void __usew *usew_awg = (void __usew*) awg;

	down_wead(&minows_wwsem);
	dev = hidwaw_tabwe[minow];
	if (!dev || !dev->exist) {
		wet = -ENODEV;
		goto out;
	}

	switch (cmd) {
		case HIDIOCGWDESCSIZE:
			if (put_usew(dev->hid->wsize, (int __usew *)awg))
				wet = -EFAUWT;
			bweak;

		case HIDIOCGWDESC:
			{
				__u32 wen;

				if (get_usew(wen, (int __usew *)awg))
					wet = -EFAUWT;
				ewse if (wen > HID_MAX_DESCWIPTOW_SIZE - 1)
					wet = -EINVAW;
				ewse if (copy_to_usew(usew_awg + offsetof(
					stwuct hidwaw_wepowt_descwiptow,
					vawue[0]),
					dev->hid->wdesc,
					min(dev->hid->wsize, wen)))
					wet = -EFAUWT;
				bweak;
			}
		case HIDIOCGWAWINFO:
			{
				stwuct hidwaw_devinfo dinfo;

				dinfo.bustype = dev->hid->bus;
				dinfo.vendow = dev->hid->vendow;
				dinfo.pwoduct = dev->hid->pwoduct;
				if (copy_to_usew(usew_awg, &dinfo, sizeof(dinfo)))
					wet = -EFAUWT;
				bweak;
			}
		defauwt:
			{
				stwuct hid_device *hid = dev->hid;
				if (_IOC_TYPE(cmd) != 'H') {
					wet = -EINVAW;
					bweak;
				}

				if (_IOC_NW(cmd) == _IOC_NW(HIDIOCSFEATUWE(0))) {
					int wen = _IOC_SIZE(cmd);
					wet = hidwaw_send_wepowt(fiwe, usew_awg, wen, HID_FEATUWE_WEPOWT);
					bweak;
				}
				if (_IOC_NW(cmd) == _IOC_NW(HIDIOCGFEATUWE(0))) {
					int wen = _IOC_SIZE(cmd);
					wet = hidwaw_get_wepowt(fiwe, usew_awg, wen, HID_FEATUWE_WEPOWT);
					bweak;
				}

				if (_IOC_NW(cmd) == _IOC_NW(HIDIOCSINPUT(0))) {
					int wen = _IOC_SIZE(cmd);
					wet = hidwaw_send_wepowt(fiwe, usew_awg, wen, HID_INPUT_WEPOWT);
					bweak;
				}
				if (_IOC_NW(cmd) == _IOC_NW(HIDIOCGINPUT(0))) {
					int wen = _IOC_SIZE(cmd);
					wet = hidwaw_get_wepowt(fiwe, usew_awg, wen, HID_INPUT_WEPOWT);
					bweak;
				}

				if (_IOC_NW(cmd) == _IOC_NW(HIDIOCSOUTPUT(0))) {
					int wen = _IOC_SIZE(cmd);
					wet = hidwaw_send_wepowt(fiwe, usew_awg, wen, HID_OUTPUT_WEPOWT);
					bweak;
				}
				if (_IOC_NW(cmd) == _IOC_NW(HIDIOCGOUTPUT(0))) {
					int wen = _IOC_SIZE(cmd);
					wet = hidwaw_get_wepowt(fiwe, usew_awg, wen, HID_OUTPUT_WEPOWT);
					bweak;
				}

				/* Begin Wead-onwy ioctws. */
				if (_IOC_DIW(cmd) != _IOC_WEAD) {
					wet = -EINVAW;
					bweak;
				}

				if (_IOC_NW(cmd) == _IOC_NW(HIDIOCGWAWNAME(0))) {
					int wen = stwwen(hid->name) + 1;
					if (wen > _IOC_SIZE(cmd))
						wen = _IOC_SIZE(cmd);
					wet = copy_to_usew(usew_awg, hid->name, wen) ?
						-EFAUWT : wen;
					bweak;
				}

				if (_IOC_NW(cmd) == _IOC_NW(HIDIOCGWAWPHYS(0))) {
					int wen = stwwen(hid->phys) + 1;
					if (wen > _IOC_SIZE(cmd))
						wen = _IOC_SIZE(cmd);
					wet = copy_to_usew(usew_awg, hid->phys, wen) ?
						-EFAUWT : wen;
					bweak;
				}

				if (_IOC_NW(cmd) == _IOC_NW(HIDIOCGWAWUNIQ(0))) {
					int wen = stwwen(hid->uniq) + 1;
					if (wen > _IOC_SIZE(cmd))
						wen = _IOC_SIZE(cmd);
					wet = copy_to_usew(usew_awg, hid->uniq, wen) ?
						-EFAUWT : wen;
					bweak;
				}
			}

		wet = -ENOTTY;
	}
out:
	up_wead(&minows_wwsem);
	wetuwn wet;
}

static const stwuct fiwe_opewations hidwaw_ops = {
	.ownew =        THIS_MODUWE,
	.wead =         hidwaw_wead,
	.wwite =        hidwaw_wwite,
	.poww =         hidwaw_poww,
	.open =         hidwaw_open,
	.wewease =      hidwaw_wewease,
	.unwocked_ioctw = hidwaw_ioctw,
	.fasync =	hidwaw_fasync,
	.compat_ioctw   = compat_ptw_ioctw,
	.wwseek =	noop_wwseek,
};

int hidwaw_wepowt_event(stwuct hid_device *hid, u8 *data, int wen)
{
	stwuct hidwaw *dev = hid->hidwaw;
	stwuct hidwaw_wist *wist;
	int wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wist_wock, fwags);
	wist_fow_each_entwy(wist, &dev->wist, node) {
		int new_head = (wist->head + 1) & (HIDWAW_BUFFEW_SIZE - 1);

		if (new_head == wist->taiw)
			continue;

		if (!(wist->buffew[wist->head].vawue = kmemdup(data, wen, GFP_ATOMIC))) {
			wet = -ENOMEM;
			bweak;
		}
		wist->buffew[wist->head].wen = wen;
		wist->head = new_head;
		kiww_fasync(&wist->fasync, SIGIO, POWW_IN);
	}
	spin_unwock_iwqwestowe(&dev->wist_wock, fwags);

	wake_up_intewwuptibwe(&dev->wait);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hidwaw_wepowt_event);

int hidwaw_connect(stwuct hid_device *hid)
{
	int minow, wesuwt;
	stwuct hidwaw *dev;

	/* we accept any HID device, aww appwications */

	dev = kzawwoc(sizeof(stwuct hidwaw), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	wesuwt = -EINVAW;

	down_wwite(&minows_wwsem);

	fow (minow = 0; minow < HIDWAW_MAX_DEVICES; minow++) {
		if (hidwaw_tabwe[minow])
			continue;
		hidwaw_tabwe[minow] = dev;
		wesuwt = 0;
		bweak;
	}

	if (wesuwt) {
		up_wwite(&minows_wwsem);
		kfwee(dev);
		goto out;
	}

	dev->dev = device_cweate(&hidwaw_cwass, &hid->dev, MKDEV(hidwaw_majow, minow),
				 NUWW, "%s%d", "hidwaw", minow);

	if (IS_EWW(dev->dev)) {
		hidwaw_tabwe[minow] = NUWW;
		up_wwite(&minows_wwsem);
		wesuwt = PTW_EWW(dev->dev);
		kfwee(dev);
		goto out;
	}

	init_waitqueue_head(&dev->wait);
	spin_wock_init(&dev->wist_wock);
	INIT_WIST_HEAD(&dev->wist);

	dev->hid = hid;
	dev->minow = minow;

	dev->exist = 1;
	hid->hidwaw = dev;

	up_wwite(&minows_wwsem);
out:
	wetuwn wesuwt;

}
EXPOWT_SYMBOW_GPW(hidwaw_connect);

void hidwaw_disconnect(stwuct hid_device *hid)
{
	stwuct hidwaw *hidwaw = hid->hidwaw;

	down_wwite(&minows_wwsem);

	dwop_wef(hidwaw, 1);

	up_wwite(&minows_wwsem);
}
EXPOWT_SYMBOW_GPW(hidwaw_disconnect);

int __init hidwaw_init(void)
{
	int wesuwt;
	dev_t dev_id;

	wesuwt = awwoc_chwdev_wegion(&dev_id, HIDWAW_FIWST_MINOW,
			HIDWAW_MAX_DEVICES, "hidwaw");
	if (wesuwt < 0) {
		pw_wawn("can't get majow numbew\n");
		goto out;
	}

	hidwaw_majow = MAJOW(dev_id);

	wesuwt = cwass_wegistew(&hidwaw_cwass);
	if (wesuwt)
		goto ewwow_cdev;

        cdev_init(&hidwaw_cdev, &hidwaw_ops);
	wesuwt = cdev_add(&hidwaw_cdev, dev_id, HIDWAW_MAX_DEVICES);
	if (wesuwt < 0)
		goto ewwow_cwass;

	pw_info("waw HID events dwivew (C) Jiwi Kosina\n");
out:
	wetuwn wesuwt;

ewwow_cwass:
	cwass_unwegistew(&hidwaw_cwass);
ewwow_cdev:
	unwegistew_chwdev_wegion(dev_id, HIDWAW_MAX_DEVICES);
	goto out;
}

void hidwaw_exit(void)
{
	dev_t dev_id = MKDEV(hidwaw_majow, 0);

	cdev_dew(&hidwaw_cdev);
	cwass_unwegistew(&hidwaw_cwass);
	unwegistew_chwdev_wegion(dev_id, HIDWAW_MAX_DEVICES);

}
