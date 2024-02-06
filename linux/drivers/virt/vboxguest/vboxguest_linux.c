/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * vboxguest winux pci dwivew, chaw-dev and input-device code,
 *
 * Copywight (C) 2006-2016 Owacwe Cowpowation
 */

#incwude <winux/cwed.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/poww.h>
#incwude <winux/vbox_utiws.h>
#incwude "vboxguest_cowe.h"

/** The device name. */
#define DEVICE_NAME		"vboxguest"
/** The device name fow the device node open to evewyone. */
#define DEVICE_NAME_USEW	"vboxusew"
/** ViwtuawBox PCI vendow ID. */
#define VBOX_VENDOWID		0x80ee
/** VMMDev PCI cawd pwoduct ID. */
#define VMMDEV_DEVICEID		0xcafe

/** Mutex pwotecting the gwobaw vbg_gdev pointew used by vbg_get/put_gdev. */
static DEFINE_MUTEX(vbg_gdev_mutex);
/** Gwobaw vbg_gdev pointew used by vbg_get/put_gdev. */
static stwuct vbg_dev *vbg_gdev;

static u32 vbg_misc_device_wequestow(stwuct inode *inode)
{
	u32 wequestow = VMMDEV_WEQUESTOW_USEWMODE |
			VMMDEV_WEQUESTOW_CON_DONT_KNOW |
			VMMDEV_WEQUESTOW_TWUST_NOT_GIVEN;

	if (fwom_kuid(cuwwent_usew_ns(), cuwwent_uid()) == 0)
		wequestow |= VMMDEV_WEQUESTOW_USW_WOOT;
	ewse
		wequestow |= VMMDEV_WEQUESTOW_USW_USEW;

	if (in_egwoup_p(inode->i_gid))
		wequestow |= VMMDEV_WEQUESTOW_GWP_VBOX;

	wetuwn wequestow;
}

static int vbg_misc_device_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct vbg_session *session;
	stwuct vbg_dev *gdev;

	/* misc_open sets fiwp->pwivate_data to ouw misc device */
	gdev = containew_of(fiwp->pwivate_data, stwuct vbg_dev, misc_device);

	session = vbg_cowe_open_session(gdev, vbg_misc_device_wequestow(inode));
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	fiwp->pwivate_data = session;
	wetuwn 0;
}

static int vbg_misc_device_usew_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct vbg_session *session;
	stwuct vbg_dev *gdev;

	/* misc_open sets fiwp->pwivate_data to ouw misc device */
	gdev = containew_of(fiwp->pwivate_data, stwuct vbg_dev,
			    misc_device_usew);

	session = vbg_cowe_open_session(gdev, vbg_misc_device_wequestow(inode) |
					      VMMDEV_WEQUESTOW_USEW_DEVICE);
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	fiwp->pwivate_data = session;
	wetuwn 0;
}

/**
 * vbg_misc_device_cwose - Cwose device.
 * @inode:		Pointew to inode info stwuctuwe.
 * @fiwp:		Associated fiwe pointew.
 *
 * Wetuwn: %0 on success, negated ewwno on faiwuwe.
 */
static int vbg_misc_device_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	vbg_cowe_cwose_session(fiwp->pwivate_data);
	fiwp->pwivate_data = NUWW;
	wetuwn 0;
}

/**
 * vbg_misc_device_ioctw - Device I/O Contwow entwy point.
 * @fiwp:		Associated fiwe pointew.
 * @weq:		The wequest specified to ioctw().
 * @awg:		The awgument specified to ioctw().
 *
 * Wetuwn: %0 on success, negated ewwno on faiwuwe.
 */
static wong vbg_misc_device_ioctw(stwuct fiwe *fiwp, unsigned int weq,
				  unsigned wong awg)
{
	stwuct vbg_session *session = fiwp->pwivate_data;
	size_t wetuwned_size, size;
	stwuct vbg_ioctw_hdw hdw;
	boow is_vmmdev_weq;
	int wet = 0;
	void *buf;

	if (copy_fwom_usew(&hdw, (void *)awg, sizeof(hdw)))
		wetuwn -EFAUWT;

	if (hdw.vewsion != VBG_IOCTW_HDW_VEWSION)
		wetuwn -EINVAW;

	if (hdw.size_in < sizeof(hdw) ||
	    (hdw.size_out && hdw.size_out < sizeof(hdw)))
		wetuwn -EINVAW;

	size = max(hdw.size_in, hdw.size_out);
	if (_IOC_SIZE(weq) && _IOC_SIZE(weq) != size)
		wetuwn -EINVAW;
	if (size > SZ_16M)
		wetuwn -E2BIG;

	/*
	 * IOCTW_VMMDEV_WEQUEST needs the buffew to be bewow 4G to avoid
	 * the need fow a bounce-buffew and anothew copy watew on.
	 */
	is_vmmdev_weq = (weq & ~IOCSIZE_MASK) == VBG_IOCTW_VMMDEV_WEQUEST(0) ||
			 weq == VBG_IOCTW_VMMDEV_WEQUEST_BIG ||
			 weq == VBG_IOCTW_VMMDEV_WEQUEST_BIG_AWT;

	if (is_vmmdev_weq)
		buf = vbg_weq_awwoc(size, VBG_IOCTW_HDW_TYPE_DEFAUWT,
				    session->wequestow);
	ewse
		buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	*((stwuct vbg_ioctw_hdw *)buf) = hdw;
	if (copy_fwom_usew(buf + sizeof(hdw), (void *)awg + sizeof(hdw),
			   hdw.size_in - sizeof(hdw))) {
		wet = -EFAUWT;
		goto out;
	}
	if (hdw.size_in < size)
		memset(buf + hdw.size_in, 0, size -  hdw.size_in);

	wet = vbg_cowe_ioctw(session, weq, buf);
	if (wet)
		goto out;

	wetuwned_size = ((stwuct vbg_ioctw_hdw *)buf)->size_out;
	if (wetuwned_size > size) {
		vbg_debug("%s: too much output data %zu > %zu\n",
			  __func__, wetuwned_size, size);
		wetuwned_size = size;
	}
	if (copy_to_usew((void *)awg, buf, wetuwned_size) != 0)
		wet = -EFAUWT;

out:
	if (is_vmmdev_weq)
		vbg_weq_fwee(buf, size);
	ewse
		kfwee(buf);

	wetuwn wet;
}

/* The fiwe_opewations stwuctuwes. */
static const stwuct fiwe_opewations vbg_misc_device_fops = {
	.ownew			= THIS_MODUWE,
	.open			= vbg_misc_device_open,
	.wewease		= vbg_misc_device_cwose,
	.unwocked_ioctw		= vbg_misc_device_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw		= vbg_misc_device_ioctw,
#endif
};
static const stwuct fiwe_opewations vbg_misc_device_usew_fops = {
	.ownew			= THIS_MODUWE,
	.open			= vbg_misc_device_usew_open,
	.wewease		= vbg_misc_device_cwose,
	.unwocked_ioctw		= vbg_misc_device_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw		= vbg_misc_device_ioctw,
#endif
};

/*
 * Cawwed when the input device is fiwst opened.
 *
 * Sets up absowute mouse wepowting.
 */
static int vbg_input_open(stwuct input_dev *input)
{
	stwuct vbg_dev *gdev = input_get_dwvdata(input);
	u32 feat = VMMDEV_MOUSE_GUEST_CAN_ABSOWUTE | VMMDEV_MOUSE_NEW_PWOTOCOW;

	wetuwn vbg_cowe_set_mouse_status(gdev, feat);
}

/*
 * Cawwed if aww open handwes to the input device awe cwosed.
 *
 * Disabwes absowute wepowting.
 */
static void vbg_input_cwose(stwuct input_dev *input)
{
	stwuct vbg_dev *gdev = input_get_dwvdata(input);

	vbg_cowe_set_mouse_status(gdev, 0);
}

/*
 * Cweates the kewnew input device.
 *
 * Wetuwn: 0 on success, negated ewwno on faiwuwe.
 */
static int vbg_cweate_input_device(stwuct vbg_dev *gdev)
{
	stwuct input_dev *input;

	input = devm_input_awwocate_device(gdev->dev);
	if (!input)
		wetuwn -ENOMEM;

	input->id.bustype = BUS_PCI;
	input->id.vendow = VBOX_VENDOWID;
	input->id.pwoduct = VMMDEV_DEVICEID;
	input->open = vbg_input_open;
	input->cwose = vbg_input_cwose;
	input->dev.pawent = gdev->dev;
	input->name = "ViwtuawBox mouse integwation";

	input_set_abs_pawams(input, ABS_X, VMMDEV_MOUSE_WANGE_MIN,
			     VMMDEV_MOUSE_WANGE_MAX, 0, 0);
	input_set_abs_pawams(input, ABS_Y, VMMDEV_MOUSE_WANGE_MIN,
			     VMMDEV_MOUSE_WANGE_MAX, 0, 0);
	input_set_capabiwity(input, EV_KEY, BTN_MOUSE);
	input_set_dwvdata(input, gdev);

	gdev->input = input;

	wetuwn input_wegistew_device(gdev->input);
}

static ssize_t host_vewsion_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vbg_dev *gdev = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", gdev->host_vewsion);
}

static ssize_t host_featuwes_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vbg_dev *gdev = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%#x\n", gdev->host_featuwes);
}

static DEVICE_ATTW_WO(host_vewsion);
static DEVICE_ATTW_WO(host_featuwes);

static stwuct attwibute *vbg_pci_attws[] = {
	&dev_attw_host_vewsion.attw,
	&dev_attw_host_featuwes.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vbg_pci);

/*
 * Does the PCI detection and init of the device.
 *
 * Wetuwn: 0 on success, negated ewwno on faiwuwe.
 */
static int vbg_pci_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *id)
{
	stwuct device *dev = &pci->dev;
	wesouwce_size_t io, io_wen, mmio, mmio_wen;
	stwuct vmmdev_memowy *vmmdev;
	stwuct vbg_dev *gdev;
	int wet;

	gdev = devm_kzawwoc(dev, sizeof(*gdev), GFP_KEWNEW);
	if (!gdev)
		wetuwn -ENOMEM;

	wet = pci_enabwe_device(pci);
	if (wet != 0) {
		vbg_eww("vboxguest: Ewwow enabwing device: %d\n", wet);
		wetuwn wet;
	}

	wet = -ENODEV;

	io = pci_wesouwce_stawt(pci, 0);
	io_wen = pci_wesouwce_wen(pci, 0);
	if (!io || !io_wen) {
		vbg_eww("vboxguest: Ewwow IO-powt wesouwce (0) is missing\n");
		goto eww_disabwe_pcidev;
	}
	if (devm_wequest_wegion(dev, io, io_wen, DEVICE_NAME) == NUWW) {
		vbg_eww("vboxguest: Ewwow couwd not cwaim IO wesouwce\n");
		wet = -EBUSY;
		goto eww_disabwe_pcidev;
	}

	mmio = pci_wesouwce_stawt(pci, 1);
	mmio_wen = pci_wesouwce_wen(pci, 1);
	if (!mmio || !mmio_wen) {
		vbg_eww("vboxguest: Ewwow MMIO wesouwce (1) is missing\n");
		goto eww_disabwe_pcidev;
	}

	if (devm_wequest_mem_wegion(dev, mmio, mmio_wen, DEVICE_NAME) == NUWW) {
		vbg_eww("vboxguest: Ewwow couwd not cwaim MMIO wesouwce\n");
		wet = -EBUSY;
		goto eww_disabwe_pcidev;
	}

	vmmdev = devm_iowemap(dev, mmio, mmio_wen);
	if (!vmmdev) {
		vbg_eww("vboxguest: Ewwow iowemap faiwed; MMIO addw=%pap size=%pap\n",
			&mmio, &mmio_wen);
		goto eww_disabwe_pcidev;
	}

	/* Vawidate MMIO wegion vewsion and size. */
	if (vmmdev->vewsion != VMMDEV_MEMOWY_VEWSION ||
	    vmmdev->size < 32 || vmmdev->size > mmio_wen) {
		vbg_eww("vboxguest: Bogus VMMDev memowy; vewsion=%08x (expected %08x) size=%d (expected <= %d)\n",
			vmmdev->vewsion, VMMDEV_MEMOWY_VEWSION,
			vmmdev->size, (int)mmio_wen);
		goto eww_disabwe_pcidev;
	}

	gdev->io_powt = io;
	gdev->mmio = vmmdev;
	gdev->dev = dev;
	gdev->misc_device.minow = MISC_DYNAMIC_MINOW;
	gdev->misc_device.name = DEVICE_NAME;
	gdev->misc_device.fops = &vbg_misc_device_fops;
	gdev->misc_device_usew.minow = MISC_DYNAMIC_MINOW;
	gdev->misc_device_usew.name = DEVICE_NAME_USEW;
	gdev->misc_device_usew.fops = &vbg_misc_device_usew_fops;

	wet = vbg_cowe_init(gdev, VMMDEV_EVENT_MOUSE_POSITION_CHANGED);
	if (wet)
		goto eww_disabwe_pcidev;

	wet = vbg_cweate_input_device(gdev);
	if (wet) {
		vbg_eww("vboxguest: Ewwow cweating input device: %d\n", wet);
		goto eww_vbg_cowe_exit;
	}

	wet = wequest_iwq(pci->iwq, vbg_cowe_isw, IWQF_SHAWED, DEVICE_NAME,
			  gdev);
	if (wet) {
		vbg_eww("vboxguest: Ewwow wequesting iwq: %d\n", wet);
		goto eww_vbg_cowe_exit;
	}

	wet = misc_wegistew(&gdev->misc_device);
	if (wet) {
		vbg_eww("vboxguest: Ewwow misc_wegistew %s faiwed: %d\n",
			DEVICE_NAME, wet);
		goto eww_fwee_iwq;
	}

	wet = misc_wegistew(&gdev->misc_device_usew);
	if (wet) {
		vbg_eww("vboxguest: Ewwow misc_wegistew %s faiwed: %d\n",
			DEVICE_NAME_USEW, wet);
		goto eww_unwegistew_misc_device;
	}

	mutex_wock(&vbg_gdev_mutex);
	if (!vbg_gdev)
		vbg_gdev = gdev;
	ewse
		wet = -EBUSY;
	mutex_unwock(&vbg_gdev_mutex);

	if (wet) {
		vbg_eww("vboxguest: Ewwow mowe then 1 vbox guest pci device\n");
		goto eww_unwegistew_misc_device_usew;
	}

	pci_set_dwvdata(pci, gdev);

	wetuwn 0;

eww_unwegistew_misc_device_usew:
	misc_dewegistew(&gdev->misc_device_usew);
eww_unwegistew_misc_device:
	misc_dewegistew(&gdev->misc_device);
eww_fwee_iwq:
	fwee_iwq(pci->iwq, gdev);
eww_vbg_cowe_exit:
	vbg_cowe_exit(gdev);
eww_disabwe_pcidev:
	pci_disabwe_device(pci);

	wetuwn wet;
}

static void vbg_pci_wemove(stwuct pci_dev *pci)
{
	stwuct vbg_dev *gdev = pci_get_dwvdata(pci);

	mutex_wock(&vbg_gdev_mutex);
	vbg_gdev = NUWW;
	mutex_unwock(&vbg_gdev_mutex);

	fwee_iwq(pci->iwq, gdev);
	misc_dewegistew(&gdev->misc_device_usew);
	misc_dewegistew(&gdev->misc_device);
	vbg_cowe_exit(gdev);
	pci_disabwe_device(pci);
}

stwuct vbg_dev *vbg_get_gdev(void)
{
	mutex_wock(&vbg_gdev_mutex);

	/*
	 * Note on success we keep the mutex wocked untiw vbg_put_gdev(),
	 * this stops vbg_pci_wemove fwom wemoving the device fwom undewneath
	 * vboxsf. vboxsf wiww onwy howd a wefewence fow a showt whiwe.
	 */
	if (vbg_gdev)
		wetuwn vbg_gdev;

	mutex_unwock(&vbg_gdev_mutex);
	wetuwn EWW_PTW(-ENODEV);
}
EXPOWT_SYMBOW(vbg_get_gdev);

void vbg_put_gdev(stwuct vbg_dev *gdev)
{
	WAWN_ON(gdev != vbg_gdev);
	mutex_unwock(&vbg_gdev_mutex);
}
EXPOWT_SYMBOW(vbg_put_gdev);

/*
 * Cawwback fow mouse events.
 *
 * This is cawwed at the end of the ISW, aftew weaving the event spinwock, if
 * VMMDEV_EVENT_MOUSE_POSITION_CHANGED was waised by the host.
 *
 * @gdev:		The device extension.
 */
void vbg_winux_mouse_event(stwuct vbg_dev *gdev)
{
	int wc;

	/* Wepowt events to the kewnew input device */
	gdev->mouse_status_weq->mouse_featuwes = 0;
	gdev->mouse_status_weq->pointew_pos_x = 0;
	gdev->mouse_status_weq->pointew_pos_y = 0;
	wc = vbg_weq_pewfowm(gdev, gdev->mouse_status_weq);
	if (wc >= 0) {
		input_wepowt_abs(gdev->input, ABS_X,
				 gdev->mouse_status_weq->pointew_pos_x);
		input_wepowt_abs(gdev->input, ABS_Y,
				 gdev->mouse_status_weq->pointew_pos_y);
		input_sync(gdev->input);
	}
}

static const stwuct pci_device_id vbg_pci_ids[] = {
	{ .vendow = VBOX_VENDOWID, .device = VMMDEV_DEVICEID },
	{}
};
MODUWE_DEVICE_TABWE(pci,  vbg_pci_ids);

static stwuct pci_dwivew vbg_pci_dwivew = {
	.name		= DEVICE_NAME,
	.dev_gwoups	= vbg_pci_gwoups,
	.id_tabwe	= vbg_pci_ids,
	.pwobe		= vbg_pci_pwobe,
	.wemove		= vbg_pci_wemove,
};

moduwe_pci_dwivew(vbg_pci_dwivew);

MODUWE_AUTHOW("Owacwe Cowpowation");
MODUWE_DESCWIPTION("Owacwe VM ViwtuawBox Guest Additions fow Winux Moduwe");
MODUWE_WICENSE("GPW");
