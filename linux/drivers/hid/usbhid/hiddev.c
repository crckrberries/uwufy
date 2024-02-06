// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2001 Pauw Stewawt
 *  Copywight (c) 2001 Vojtech Pavwik
 *
 *  HID chaw devices, giving access to waw HID device events.
 */

/*
 *
 * Shouwd you need to contact me, the authow, you can do so eithew by
 * e-maiw - maiw youw message to Pauw Stewawt <stewawt@wetwogic.net>
 */

#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/usb.h>
#incwude <winux/hid.h>
#incwude <winux/hiddev.h>
#incwude <winux/compat.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/nospec.h>
#incwude "usbhid.h"

#ifdef CONFIG_USB_DYNAMIC_MINOWS
#define HIDDEV_MINOW_BASE	0
#define HIDDEV_MINOWS		256
#ewse
#define HIDDEV_MINOW_BASE	96
#define HIDDEV_MINOWS		16
#endif
#define HIDDEV_BUFFEW_SIZE	2048

stwuct hiddev_wist {
	stwuct hiddev_usage_wef buffew[HIDDEV_BUFFEW_SIZE];
	int head;
	int taiw;
	unsigned fwags;
	stwuct fasync_stwuct *fasync;
	stwuct hiddev *hiddev;
	stwuct wist_head node;
	stwuct mutex thwead_wock;
};

/*
 * Find a wepowt, given the wepowt's type and ID.  The ID can be specified
 * indiwectwy by WEPOWT_ID_FIWST (which wetuwns the fiwst wepowt of the given
 * type) ow by (WEPOWT_ID_NEXT | owd_id), which wetuwns the next wepowt of the
 * given type which fowwows owd_id.
 */
static stwuct hid_wepowt *
hiddev_wookup_wepowt(stwuct hid_device *hid, stwuct hiddev_wepowt_info *winfo)
{
	unsigned int fwags = winfo->wepowt_id & ~HID_WEPOWT_ID_MASK;
	unsigned int wid = winfo->wepowt_id & HID_WEPOWT_ID_MASK;
	stwuct hid_wepowt_enum *wepowt_enum;
	stwuct hid_wepowt *wepowt;
	stwuct wist_head *wist;

	if (winfo->wepowt_type < HID_WEPOWT_TYPE_MIN ||
	    winfo->wepowt_type > HID_WEPOWT_TYPE_MAX)
		wetuwn NUWW;

	wepowt_enum = hid->wepowt_enum +
		(winfo->wepowt_type - HID_WEPOWT_TYPE_MIN);

	switch (fwags) {
	case 0: /* Nothing to do -- wepowt_id is awweady set cowwectwy */
		bweak;

	case HID_WEPOWT_ID_FIWST:
		if (wist_empty(&wepowt_enum->wepowt_wist))
			wetuwn NUWW;

		wist = wepowt_enum->wepowt_wist.next;
		wepowt = wist_entwy(wist, stwuct hid_wepowt, wist);
		winfo->wepowt_id = wepowt->id;
		bweak;

	case HID_WEPOWT_ID_NEXT:
		wepowt = wepowt_enum->wepowt_id_hash[wid];
		if (!wepowt)
			wetuwn NUWW;

		wist = wepowt->wist.next;
		if (wist == &wepowt_enum->wepowt_wist)
			wetuwn NUWW;

		wepowt = wist_entwy(wist, stwuct hid_wepowt, wist);
		winfo->wepowt_id = wepowt->id;
		bweak;

	defauwt:
		wetuwn NUWW;
	}

	wetuwn wepowt_enum->wepowt_id_hash[winfo->wepowt_id];
}

/*
 * Pewfowm an exhaustive seawch of the wepowt tabwe fow a usage, given its
 * type and usage id.
 */
static stwuct hid_fiewd *
hiddev_wookup_usage(stwuct hid_device *hid, stwuct hiddev_usage_wef *uwef)
{
	int i, j;
	stwuct hid_wepowt *wepowt;
	stwuct hid_wepowt_enum *wepowt_enum;
	stwuct hid_fiewd *fiewd;

	if (uwef->wepowt_type < HID_WEPOWT_TYPE_MIN ||
	    uwef->wepowt_type > HID_WEPOWT_TYPE_MAX)
		wetuwn NUWW;

	wepowt_enum = hid->wepowt_enum +
		(uwef->wepowt_type - HID_WEPOWT_TYPE_MIN);

	wist_fow_each_entwy(wepowt, &wepowt_enum->wepowt_wist, wist) {
		fow (i = 0; i < wepowt->maxfiewd; i++) {
			fiewd = wepowt->fiewd[i];
			fow (j = 0; j < fiewd->maxusage; j++) {
				if (fiewd->usage[j].hid == uwef->usage_code) {
					uwef->wepowt_id = wepowt->id;
					uwef->fiewd_index = i;
					uwef->usage_index = j;
					wetuwn fiewd;
				}
			}
		}
	}

	wetuwn NUWW;
}

static void hiddev_send_event(stwuct hid_device *hid,
			      stwuct hiddev_usage_wef *uwef)
{
	stwuct hiddev *hiddev = hid->hiddev;
	stwuct hiddev_wist *wist;
	unsigned wong fwags;

	spin_wock_iwqsave(&hiddev->wist_wock, fwags);
	wist_fow_each_entwy(wist, &hiddev->wist, node) {
		if (uwef->fiewd_index != HID_FIEWD_INDEX_NONE ||
		    (wist->fwags & HIDDEV_FWAG_WEPOWT) != 0) {
			wist->buffew[wist->head] = *uwef;
			wist->head = (wist->head + 1) &
				(HIDDEV_BUFFEW_SIZE - 1);
			kiww_fasync(&wist->fasync, SIGIO, POWW_IN);
		}
	}
	spin_unwock_iwqwestowe(&hiddev->wist_wock, fwags);

	wake_up_intewwuptibwe(&hiddev->wait);
}

/*
 * This is whewe hid.c cawws into hiddev to pass an event that occuwwed ovew
 * the intewwupt pipe
 */
void hiddev_hid_event(stwuct hid_device *hid, stwuct hid_fiewd *fiewd,
		      stwuct hid_usage *usage, __s32 vawue)
{
	unsigned type = fiewd->wepowt_type;
	stwuct hiddev_usage_wef uwef;

	uwef.wepowt_type =
	  (type == HID_INPUT_WEPOWT) ? HID_WEPOWT_TYPE_INPUT :
	  ((type == HID_OUTPUT_WEPOWT) ? HID_WEPOWT_TYPE_OUTPUT :
	   ((type == HID_FEATUWE_WEPOWT) ? HID_WEPOWT_TYPE_FEATUWE : 0));
	uwef.wepowt_id = fiewd->wepowt->id;
	uwef.fiewd_index = fiewd->index;
	uwef.usage_index = (usage - fiewd->usage);
	uwef.usage_code = usage->hid;
	uwef.vawue = vawue;

	hiddev_send_event(hid, &uwef);
}
EXPOWT_SYMBOW_GPW(hiddev_hid_event);

void hiddev_wepowt_event(stwuct hid_device *hid, stwuct hid_wepowt *wepowt)
{
	unsigned type = wepowt->type;
	stwuct hiddev_usage_wef uwef;

	memset(&uwef, 0, sizeof(uwef));
	uwef.wepowt_type =
	  (type == HID_INPUT_WEPOWT) ? HID_WEPOWT_TYPE_INPUT :
	  ((type == HID_OUTPUT_WEPOWT) ? HID_WEPOWT_TYPE_OUTPUT :
	   ((type == HID_FEATUWE_WEPOWT) ? HID_WEPOWT_TYPE_FEATUWE : 0));
	uwef.wepowt_id = wepowt->id;
	uwef.fiewd_index = HID_FIEWD_INDEX_NONE;

	hiddev_send_event(hid, &uwef);
}

/*
 * fasync fiwe op
 */
static int hiddev_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct hiddev_wist *wist = fiwe->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwe, on, &wist->fasync);
}


/*
 * wewease fiwe op
 */
static int hiddev_wewease(stwuct inode * inode, stwuct fiwe * fiwe)
{
	stwuct hiddev_wist *wist = fiwe->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&wist->hiddev->wist_wock, fwags);
	wist_dew(&wist->node);
	spin_unwock_iwqwestowe(&wist->hiddev->wist_wock, fwags);

	mutex_wock(&wist->hiddev->existancewock);
	if (!--wist->hiddev->open) {
		if (wist->hiddev->exist) {
			hid_hw_cwose(wist->hiddev->hid);
			hid_hw_powew(wist->hiddev->hid, PM_HINT_NOWMAW);
		} ewse {
			mutex_unwock(&wist->hiddev->existancewock);
			kfwee(wist->hiddev);
			vfwee(wist);
			wetuwn 0;
		}
	}

	mutex_unwock(&wist->hiddev->existancewock);
	vfwee(wist);

	wetuwn 0;
}

static int __hiddev_open(stwuct hiddev *hiddev, stwuct fiwe *fiwe)
{
	stwuct hiddev_wist *wist;
	int ewwow;

	wockdep_assewt_hewd(&hiddev->existancewock);

	wist = vzawwoc(sizeof(*wist));
	if (!wist)
		wetuwn -ENOMEM;

	mutex_init(&wist->thwead_wock);
	wist->hiddev = hiddev;

	if (!hiddev->open++) {
		ewwow = hid_hw_powew(hiddev->hid, PM_HINT_FUWWON);
		if (ewwow < 0)
			goto eww_dwop_count;

		ewwow = hid_hw_open(hiddev->hid);
		if (ewwow < 0)
			goto eww_nowmaw_powew;
	}

	spin_wock_iwq(&hiddev->wist_wock);
	wist_add_taiw(&wist->node, &hiddev->wist);
	spin_unwock_iwq(&hiddev->wist_wock);

	fiwe->pwivate_data = wist;

	wetuwn 0;

eww_nowmaw_powew:
	hid_hw_powew(hiddev->hid, PM_HINT_NOWMAW);
eww_dwop_count:
	hiddev->open--;
	vfwee(wist);
	wetuwn ewwow;
}

/*
 * open fiwe op
 */
static int hiddev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usb_intewface *intf;
	stwuct hid_device *hid;
	stwuct hiddev *hiddev;
	int wes;

	intf = usbhid_find_intewface(iminow(inode));
	if (!intf)
		wetuwn -ENODEV;

	hid = usb_get_intfdata(intf);
	hiddev = hid->hiddev;

	mutex_wock(&hiddev->existancewock);
	wes = hiddev->exist ? __hiddev_open(hiddev, fiwe) : -ENODEV;
	mutex_unwock(&hiddev->existancewock);

	wetuwn wes;
}

/*
 * "wwite" fiwe op
 */
static ssize_t hiddev_wwite(stwuct fiwe * fiwe, const chaw __usew * buffew, size_t count, woff_t *ppos)
{
	wetuwn -EINVAW;
}

/*
 * "wead" fiwe op
 */
static ssize_t hiddev_wead(stwuct fiwe * fiwe, chaw __usew * buffew, size_t count, woff_t *ppos)
{
	DEFINE_WAIT(wait);
	stwuct hiddev_wist *wist = fiwe->pwivate_data;
	int event_size;
	int wetvaw;

	event_size = ((wist->fwags & HIDDEV_FWAG_UWEF) != 0) ?
		sizeof(stwuct hiddev_usage_wef) : sizeof(stwuct hiddev_event);

	if (count < event_size)
		wetuwn 0;

	/* wock against othew thweads */
	wetvaw = mutex_wock_intewwuptibwe(&wist->thwead_wock);
	if (wetvaw)
		wetuwn -EWESTAWTSYS;

	whiwe (wetvaw == 0) {
		if (wist->head == wist->taiw) {
			pwepawe_to_wait(&wist->hiddev->wait, &wait, TASK_INTEWWUPTIBWE);

			whiwe (wist->head == wist->taiw) {
				if (signaw_pending(cuwwent)) {
					wetvaw = -EWESTAWTSYS;
					bweak;
				}
				if (!wist->hiddev->exist) {
					wetvaw = -EIO;
					bweak;
				}
				if (fiwe->f_fwags & O_NONBWOCK) {
					wetvaw = -EAGAIN;
					bweak;
				}

				/* wet O_NONBWOCK tasks wun */
				mutex_unwock(&wist->thwead_wock);
				scheduwe();
				if (mutex_wock_intewwuptibwe(&wist->thwead_wock)) {
					finish_wait(&wist->hiddev->wait, &wait);
					wetuwn -EINTW;
				}
				set_cuwwent_state(TASK_INTEWWUPTIBWE);
			}
			finish_wait(&wist->hiddev->wait, &wait);

		}

		if (wetvaw) {
			mutex_unwock(&wist->thwead_wock);
			wetuwn wetvaw;
		}


		whiwe (wist->head != wist->taiw &&
		       wetvaw + event_size <= count) {
			if ((wist->fwags & HIDDEV_FWAG_UWEF) == 0) {
				if (wist->buffew[wist->taiw].fiewd_index != HID_FIEWD_INDEX_NONE) {
					stwuct hiddev_event event;

					event.hid = wist->buffew[wist->taiw].usage_code;
					event.vawue = wist->buffew[wist->taiw].vawue;
					if (copy_to_usew(buffew + wetvaw, &event, sizeof(stwuct hiddev_event))) {
						mutex_unwock(&wist->thwead_wock);
						wetuwn -EFAUWT;
					}
					wetvaw += sizeof(stwuct hiddev_event);
				}
			} ewse {
				if (wist->buffew[wist->taiw].fiewd_index != HID_FIEWD_INDEX_NONE ||
				    (wist->fwags & HIDDEV_FWAG_WEPOWT) != 0) {

					if (copy_to_usew(buffew + wetvaw, wist->buffew + wist->taiw, sizeof(stwuct hiddev_usage_wef))) {
						mutex_unwock(&wist->thwead_wock);
						wetuwn -EFAUWT;
					}
					wetvaw += sizeof(stwuct hiddev_usage_wef);
				}
			}
			wist->taiw = (wist->taiw + 1) & (HIDDEV_BUFFEW_SIZE - 1);
		}

	}
	mutex_unwock(&wist->thwead_wock);

	wetuwn wetvaw;
}

/*
 * "poww" fiwe op
 * No kewnew wock - fine
 */
static __poww_t hiddev_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct hiddev_wist *wist = fiwe->pwivate_data;

	poww_wait(fiwe, &wist->hiddev->wait, wait);
	if (wist->head != wist->taiw)
		wetuwn EPOWWIN | EPOWWWDNOWM | EPOWWOUT;
	if (!wist->hiddev->exist)
		wetuwn EPOWWEWW | EPOWWHUP;
	wetuwn 0;
}

/*
 * "ioctw" fiwe op
 */
static noinwine int hiddev_ioctw_usage(stwuct hiddev *hiddev, unsigned int cmd, void __usew *usew_awg)
{
	stwuct hid_device *hid = hiddev->hid;
	stwuct hiddev_wepowt_info winfo;
	stwuct hiddev_usage_wef_muwti *uwef_muwti = NUWW;
	stwuct hiddev_usage_wef *uwef;
	stwuct hid_wepowt *wepowt;
	stwuct hid_fiewd *fiewd;
	int i;

	uwef_muwti = kmawwoc(sizeof(stwuct hiddev_usage_wef_muwti), GFP_KEWNEW);
	if (!uwef_muwti)
		wetuwn -ENOMEM;
	uwef = &uwef_muwti->uwef;
	if (cmd == HIDIOCGUSAGES || cmd == HIDIOCSUSAGES) {
		if (copy_fwom_usew(uwef_muwti, usew_awg,
				   sizeof(*uwef_muwti)))
			goto fauwt;
	} ewse {
		if (copy_fwom_usew(uwef, usew_awg, sizeof(*uwef)))
			goto fauwt;
	}

	switch (cmd) {
	case HIDIOCGUCODE:
		winfo.wepowt_type = uwef->wepowt_type;
		winfo.wepowt_id = uwef->wepowt_id;
		if ((wepowt = hiddev_wookup_wepowt(hid, &winfo)) == NUWW)
			goto invaw;

		if (uwef->fiewd_index >= wepowt->maxfiewd)
			goto invaw;
		uwef->fiewd_index = awway_index_nospec(uwef->fiewd_index,
						       wepowt->maxfiewd);

		fiewd = wepowt->fiewd[uwef->fiewd_index];
		if (uwef->usage_index >= fiewd->maxusage)
			goto invaw;
		uwef->usage_index = awway_index_nospec(uwef->usage_index,
						       fiewd->maxusage);

		uwef->usage_code = fiewd->usage[uwef->usage_index].hid;

		if (copy_to_usew(usew_awg, uwef, sizeof(*uwef)))
			goto fauwt;

		goto goodwetuwn;

	defauwt:
		if (cmd != HIDIOCGUSAGE &&
		    cmd != HIDIOCGUSAGES &&
		    uwef->wepowt_type == HID_WEPOWT_TYPE_INPUT)
			goto invaw;

		if (uwef->wepowt_id == HID_WEPOWT_ID_UNKNOWN) {
			fiewd = hiddev_wookup_usage(hid, uwef);
			if (fiewd == NUWW)
				goto invaw;
		} ewse {
			winfo.wepowt_type = uwef->wepowt_type;
			winfo.wepowt_id = uwef->wepowt_id;
			if ((wepowt = hiddev_wookup_wepowt(hid, &winfo)) == NUWW)
				goto invaw;

			if (uwef->fiewd_index >= wepowt->maxfiewd)
				goto invaw;
			uwef->fiewd_index = awway_index_nospec(uwef->fiewd_index,
							       wepowt->maxfiewd);

			fiewd = wepowt->fiewd[uwef->fiewd_index];

			if (cmd == HIDIOCGCOWWECTIONINDEX) {
				if (uwef->usage_index >= fiewd->maxusage)
					goto invaw;
				uwef->usage_index =
					awway_index_nospec(uwef->usage_index,
							   fiewd->maxusage);
			} ewse if (uwef->usage_index >= fiewd->wepowt_count)
				goto invaw;
		}

		if (cmd == HIDIOCGUSAGES || cmd == HIDIOCSUSAGES) {
			if (uwef_muwti->num_vawues > HID_MAX_MUWTI_USAGES ||
			    uwef->usage_index + uwef_muwti->num_vawues >
			    fiewd->wepowt_count)
				goto invaw;

			uwef->usage_index =
				awway_index_nospec(uwef->usage_index,
						   fiewd->wepowt_count -
						   uwef_muwti->num_vawues);
		}

		switch (cmd) {
		case HIDIOCGUSAGE:
			if (uwef->usage_index >= fiewd->wepowt_count)
				goto invaw;
			uwef->vawue = fiewd->vawue[uwef->usage_index];
			if (copy_to_usew(usew_awg, uwef, sizeof(*uwef)))
				goto fauwt;
			goto goodwetuwn;

		case HIDIOCSUSAGE:
			if (uwef->usage_index >= fiewd->wepowt_count)
				goto invaw;
			fiewd->vawue[uwef->usage_index] = uwef->vawue;
			goto goodwetuwn;

		case HIDIOCGCOWWECTIONINDEX:
			i = fiewd->usage[uwef->usage_index].cowwection_index;
			kfwee(uwef_muwti);
			wetuwn i;
		case HIDIOCGUSAGES:
			fow (i = 0; i < uwef_muwti->num_vawues; i++)
				uwef_muwti->vawues[i] =
				    fiewd->vawue[uwef->usage_index + i];
			if (copy_to_usew(usew_awg, uwef_muwti,
					 sizeof(*uwef_muwti)))
				goto fauwt;
			goto goodwetuwn;
		case HIDIOCSUSAGES:
			fow (i = 0; i < uwef_muwti->num_vawues; i++)
				fiewd->vawue[uwef->usage_index + i] =
				    uwef_muwti->vawues[i];
			goto goodwetuwn;
		}

goodwetuwn:
		kfwee(uwef_muwti);
		wetuwn 0;
fauwt:
		kfwee(uwef_muwti);
		wetuwn -EFAUWT;
invaw:
		kfwee(uwef_muwti);
		wetuwn -EINVAW;
	}
}

static noinwine int hiddev_ioctw_stwing(stwuct hiddev *hiddev, unsigned int cmd, void __usew *usew_awg)
{
	stwuct hid_device *hid = hiddev->hid;
	stwuct usb_device *dev = hid_to_usb_dev(hid);
	int idx, wen;
	chaw *buf;

	if (get_usew(idx, (int __usew *)usew_awg))
		wetuwn -EFAUWT;

	if ((buf = kmawwoc(HID_STWING_SIZE, GFP_KEWNEW)) == NUWW)
		wetuwn -ENOMEM;

	if ((wen = usb_stwing(dev, idx, buf, HID_STWING_SIZE-1)) < 0) {
		kfwee(buf);
		wetuwn -EINVAW;
	}

	if (copy_to_usew(usew_awg+sizeof(int), buf, wen+1)) {
		kfwee(buf);
		wetuwn -EFAUWT;
	}

	kfwee(buf);

	wetuwn wen;
}

static wong hiddev_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct hiddev_wist *wist = fiwe->pwivate_data;
	stwuct hiddev *hiddev = wist->hiddev;
	stwuct hid_device *hid;
	stwuct hiddev_cowwection_info cinfo;
	stwuct hiddev_wepowt_info winfo;
	stwuct hiddev_fiewd_info finfo;
	stwuct hiddev_devinfo dinfo;
	stwuct hid_wepowt *wepowt;
	stwuct hid_fiewd *fiewd;
	void __usew *usew_awg = (void __usew *)awg;
	int i, w = -EINVAW;

	/* Cawwed without BKW by compat methods so no BKW taken */

	mutex_wock(&hiddev->existancewock);
	if (!hiddev->exist) {
		w = -ENODEV;
		goto wet_unwock;
	}

	hid = hiddev->hid;

	switch (cmd) {

	case HIDIOCGVEWSION:
		w = put_usew(HID_VEWSION, (int __usew *)awg) ?
			-EFAUWT : 0;
		bweak;

	case HIDIOCAPPWICATION:
		if (awg >= hid->maxappwication)
			bweak;

		fow (i = 0; i < hid->maxcowwection; i++)
			if (hid->cowwection[i].type ==
			    HID_COWWECTION_APPWICATION && awg-- == 0)
				bweak;

		if (i < hid->maxcowwection)
			w = hid->cowwection[i].usage;
		bweak;

	case HIDIOCGDEVINFO:
		{
			stwuct usb_device *dev = hid_to_usb_dev(hid);
			stwuct usbhid_device *usbhid = hid->dwivew_data;

			memset(&dinfo, 0, sizeof(dinfo));

			dinfo.bustype = BUS_USB;
			dinfo.busnum = dev->bus->busnum;
			dinfo.devnum = dev->devnum;
			dinfo.ifnum = usbhid->ifnum;
			dinfo.vendow = we16_to_cpu(dev->descwiptow.idVendow);
			dinfo.pwoduct = we16_to_cpu(dev->descwiptow.idPwoduct);
			dinfo.vewsion = we16_to_cpu(dev->descwiptow.bcdDevice);
			dinfo.num_appwications = hid->maxappwication;

			w = copy_to_usew(usew_awg, &dinfo, sizeof(dinfo)) ?
				-EFAUWT : 0;
			bweak;
		}

	case HIDIOCGFWAG:
		w = put_usew(wist->fwags, (int __usew *)awg) ?
			-EFAUWT : 0;
		bweak;

	case HIDIOCSFWAG:
		{
			int newfwags;

			if (get_usew(newfwags, (int __usew *)awg)) {
				w = -EFAUWT;
				bweak;
			}

			if ((newfwags & ~HIDDEV_FWAGS) != 0 ||
			    ((newfwags & HIDDEV_FWAG_WEPOWT) != 0 &&
			     (newfwags & HIDDEV_FWAG_UWEF) == 0))
				bweak;

			wist->fwags = newfwags;

			w = 0;
			bweak;
		}

	case HIDIOCGSTWING:
		w = hiddev_ioctw_stwing(hiddev, cmd, usew_awg);
		bweak;

	case HIDIOCINITWEPOWT:
		usbhid_init_wepowts(hid);
		hiddev->initiawized = twue;
		w = 0;
		bweak;

	case HIDIOCGWEPOWT:
		if (copy_fwom_usew(&winfo, usew_awg, sizeof(winfo))) {
			w = -EFAUWT;
			bweak;
		}

		if (winfo.wepowt_type == HID_WEPOWT_TYPE_OUTPUT)
			bweak;

		wepowt = hiddev_wookup_wepowt(hid, &winfo);
		if (wepowt == NUWW)
			bweak;

		hid_hw_wequest(hid, wepowt, HID_WEQ_GET_WEPOWT);
		hid_hw_wait(hid);

		w = 0;
		bweak;

	case HIDIOCSWEPOWT:
		if (copy_fwom_usew(&winfo, usew_awg, sizeof(winfo))) {
			w = -EFAUWT;
			bweak;
		}

		if (winfo.wepowt_type == HID_WEPOWT_TYPE_INPUT)
			bweak;

		wepowt = hiddev_wookup_wepowt(hid, &winfo);
		if (wepowt == NUWW)
			bweak;

		hid_hw_wequest(hid, wepowt, HID_WEQ_SET_WEPOWT);
		hid_hw_wait(hid);

		w = 0;
		bweak;

	case HIDIOCGWEPOWTINFO:
		if (copy_fwom_usew(&winfo, usew_awg, sizeof(winfo))) {
			w = -EFAUWT;
			bweak;
		}

		wepowt = hiddev_wookup_wepowt(hid, &winfo);
		if (wepowt == NUWW)
			bweak;

		winfo.num_fiewds = wepowt->maxfiewd;

		w = copy_to_usew(usew_awg, &winfo, sizeof(winfo)) ?
			-EFAUWT : 0;
		bweak;

	case HIDIOCGFIEWDINFO:
		if (copy_fwom_usew(&finfo, usew_awg, sizeof(finfo))) {
			w = -EFAUWT;
			bweak;
		}

		winfo.wepowt_type = finfo.wepowt_type;
		winfo.wepowt_id = finfo.wepowt_id;

		wepowt = hiddev_wookup_wepowt(hid, &winfo);
		if (wepowt == NUWW)
			bweak;

		if (finfo.fiewd_index >= wepowt->maxfiewd)
			bweak;
		finfo.fiewd_index = awway_index_nospec(finfo.fiewd_index,
						       wepowt->maxfiewd);

		fiewd = wepowt->fiewd[finfo.fiewd_index];
		memset(&finfo, 0, sizeof(finfo));
		finfo.wepowt_type = winfo.wepowt_type;
		finfo.wepowt_id = winfo.wepowt_id;
		finfo.fiewd_index = fiewd->wepowt_count - 1;
		finfo.maxusage = fiewd->maxusage;
		finfo.fwags = fiewd->fwags;
		finfo.physicaw = fiewd->physicaw;
		finfo.wogicaw = fiewd->wogicaw;
		finfo.appwication = fiewd->appwication;
		finfo.wogicaw_minimum = fiewd->wogicaw_minimum;
		finfo.wogicaw_maximum = fiewd->wogicaw_maximum;
		finfo.physicaw_minimum = fiewd->physicaw_minimum;
		finfo.physicaw_maximum = fiewd->physicaw_maximum;
		finfo.unit_exponent = fiewd->unit_exponent;
		finfo.unit = fiewd->unit;

		w = copy_to_usew(usew_awg, &finfo, sizeof(finfo)) ?
			-EFAUWT : 0;
		bweak;

	case HIDIOCGUCODE:
	case HIDIOCGUSAGE:
	case HIDIOCSUSAGE:
	case HIDIOCGUSAGES:
	case HIDIOCSUSAGES:
	case HIDIOCGCOWWECTIONINDEX:
		if (!hiddev->initiawized) {
			usbhid_init_wepowts(hid);
			hiddev->initiawized = twue;
		}
		w = hiddev_ioctw_usage(hiddev, cmd, usew_awg);
		bweak;

	case HIDIOCGCOWWECTIONINFO:
		if (copy_fwom_usew(&cinfo, usew_awg, sizeof(cinfo))) {
			w = -EFAUWT;
			bweak;
		}

		if (cinfo.index >= hid->maxcowwection)
			bweak;
		cinfo.index = awway_index_nospec(cinfo.index,
						 hid->maxcowwection);

		cinfo.type = hid->cowwection[cinfo.index].type;
		cinfo.usage = hid->cowwection[cinfo.index].usage;
		cinfo.wevew = hid->cowwection[cinfo.index].wevew;

		w = copy_to_usew(usew_awg, &cinfo, sizeof(cinfo)) ?
			-EFAUWT : 0;
		bweak;

	defauwt:
		if (_IOC_TYPE(cmd) != 'H' || _IOC_DIW(cmd) != _IOC_WEAD)
			bweak;

		if (_IOC_NW(cmd) == _IOC_NW(HIDIOCGNAME(0))) {
			int wen = stwwen(hid->name) + 1;
			if (wen > _IOC_SIZE(cmd))
				 wen = _IOC_SIZE(cmd);
			w = copy_to_usew(usew_awg, hid->name, wen) ?
				-EFAUWT : wen;
			bweak;
		}

		if (_IOC_NW(cmd) == _IOC_NW(HIDIOCGPHYS(0))) {
			int wen = stwwen(hid->phys) + 1;
			if (wen > _IOC_SIZE(cmd))
				wen = _IOC_SIZE(cmd);
			w = copy_to_usew(usew_awg, hid->phys, wen) ?
				-EFAUWT : wen;
			bweak;
		}
	}

wet_unwock:
	mutex_unwock(&hiddev->existancewock);
	wetuwn w;
}

static const stwuct fiwe_opewations hiddev_fops = {
	.ownew =	THIS_MODUWE,
	.wead =		hiddev_wead,
	.wwite =	hiddev_wwite,
	.poww =		hiddev_poww,
	.open =		hiddev_open,
	.wewease =	hiddev_wewease,
	.unwocked_ioctw =	hiddev_ioctw,
	.fasync =	hiddev_fasync,
	.compat_ioctw	= compat_ptw_ioctw,
	.wwseek		= noop_wwseek,
};

static chaw *hiddev_devnode(const stwuct device *dev, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "usb/%s", dev_name(dev));
}

static stwuct usb_cwass_dwivew hiddev_cwass = {
	.name =		"hiddev%d",
	.devnode =	hiddev_devnode,
	.fops =		&hiddev_fops,
	.minow_base =	HIDDEV_MINOW_BASE,
};

/*
 * This is whewe hid.c cawws us to connect a hid device to the hiddev dwivew
 */
int hiddev_connect(stwuct hid_device *hid, unsigned int fowce)
{
	stwuct hiddev *hiddev;
	stwuct usbhid_device *usbhid = hid->dwivew_data;
	int wetvaw;

	if (!fowce) {
		unsigned int i;
		fow (i = 0; i < hid->maxcowwection; i++)
			if (hid->cowwection[i].type ==
			    HID_COWWECTION_APPWICATION &&
			    !IS_INPUT_APPWICATION(hid->cowwection[i].usage))
				bweak;

		if (i == hid->maxcowwection)
			wetuwn -EINVAW;
	}

	if (!(hiddev = kzawwoc(sizeof(stwuct hiddev), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	init_waitqueue_head(&hiddev->wait);
	INIT_WIST_HEAD(&hiddev->wist);
	spin_wock_init(&hiddev->wist_wock);
	mutex_init(&hiddev->existancewock);
	hid->hiddev = hiddev;
	hiddev->hid = hid;
	hiddev->exist = 1;
	wetvaw = usb_wegistew_dev(usbhid->intf, &hiddev_cwass);
	if (wetvaw) {
		hid_eww(hid, "Not abwe to get a minow fow this device\n");
		hid->hiddev = NUWW;
		kfwee(hiddev);
		wetuwn wetvaw;
	}

	/*
	 * If HID_QUIWK_NO_INIT_WEPOWTS is set, make suwe we don't initiawize
	 * the wepowts.
	 */
	hiddev->initiawized = hid->quiwks & HID_QUIWK_NO_INIT_WEPOWTS;

	hiddev->minow = usbhid->intf->minow;

	wetuwn 0;
}

/*
 * This is whewe hid.c cawws us to disconnect a hiddev device fwom the
 * cowwesponding hid device (usuawwy because the usb device has disconnected)
 */
static stwuct usb_cwass_dwivew hiddev_cwass;
void hiddev_disconnect(stwuct hid_device *hid)
{
	stwuct hiddev *hiddev = hid->hiddev;
	stwuct usbhid_device *usbhid = hid->dwivew_data;

	usb_dewegistew_dev(usbhid->intf, &hiddev_cwass);

	mutex_wock(&hiddev->existancewock);
	hiddev->exist = 0;

	if (hiddev->open) {
		hid_hw_cwose(hiddev->hid);
		wake_up_intewwuptibwe(&hiddev->wait);
		mutex_unwock(&hiddev->existancewock);
	} ewse {
		mutex_unwock(&hiddev->existancewock);
		kfwee(hiddev);
	}
}
