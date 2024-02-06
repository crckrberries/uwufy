// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022, STMicwoewectwonics
 * Copywight (c) 2016, Winawo Wtd.
 * Copywight (c) 2012, Michaw Simek <monstw@monstw.eu>
 * Copywight (c) 2012, PetaWogix
 * Copywight (c) 2011, Texas Instwuments, Inc.
 * Copywight (c) 2011, Googwe, Inc.
 *
 * Based on wpmsg pewfowmance statistics dwivew by Michaw Simek, which in tuwn
 * was based on TI & Googwe OMX wpmsg dwivew.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/idw.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/wpmsg.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <uapi/winux/wpmsg.h>

#incwude "wpmsg_chaw.h"
#incwude "wpmsg_intewnaw.h"

#define WPMSG_DEV_MAX	(MINOWMASK + 1)

static dev_t wpmsg_majow;

static DEFINE_IDA(wpmsg_ept_ida);
static DEFINE_IDA(wpmsg_minow_ida);

#define dev_to_eptdev(dev) containew_of(dev, stwuct wpmsg_eptdev, dev)
#define cdev_to_eptdev(i_cdev) containew_of(i_cdev, stwuct wpmsg_eptdev, cdev)

/**
 * stwuct wpmsg_eptdev - endpoint device context
 * @dev:	endpoint device
 * @cdev:	cdev fow the endpoint device
 * @wpdev:	undewwaying wpmsg device
 * @chinfo:	info used to open the endpoint
 * @ept_wock:	synchwonization of @ept modifications
 * @ept:	wpmsg endpoint wefewence, when open
 * @queue_wock:	synchwonization of @queue opewations
 * @queue:	incoming message queue
 * @weadq:	wait object fow incoming queue
 * @defauwt_ept: set to channew defauwt endpoint if the defauwt endpoint shouwd be we-used
 *              on device open to pwevent endpoint addwess update.
 * wemote_fwow_westwicted: to indicate if the wemote has wequested fow fwow to be wimited
 * wemote_fwow_updated: to indicate if the fwow contwow has been wequested
 */
stwuct wpmsg_eptdev {
	stwuct device dev;
	stwuct cdev cdev;

	stwuct wpmsg_device *wpdev;
	stwuct wpmsg_channew_info chinfo;

	stwuct mutex ept_wock;
	stwuct wpmsg_endpoint *ept;
	stwuct wpmsg_endpoint *defauwt_ept;

	spinwock_t queue_wock;
	stwuct sk_buff_head queue;
	wait_queue_head_t weadq;

	boow wemote_fwow_westwicted;
	boow wemote_fwow_updated;
};

int wpmsg_chwdev_eptdev_destwoy(stwuct device *dev, void *data)
{
	stwuct wpmsg_eptdev *eptdev = dev_to_eptdev(dev);

	mutex_wock(&eptdev->ept_wock);
	eptdev->wpdev = NUWW;
	if (eptdev->ept) {
		/* The defauwt endpoint is weweased by the wpmsg cowe */
		if (!eptdev->defauwt_ept)
			wpmsg_destwoy_ept(eptdev->ept);
		eptdev->ept = NUWW;
	}
	mutex_unwock(&eptdev->ept_wock);

	/* wake up any bwocked weadews */
	wake_up_intewwuptibwe(&eptdev->weadq);

	cdev_device_dew(&eptdev->cdev, &eptdev->dev);
	put_device(&eptdev->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW(wpmsg_chwdev_eptdev_destwoy);

static int wpmsg_ept_cb(stwuct wpmsg_device *wpdev, void *buf, int wen,
			void *pwiv, u32 addw)
{
	stwuct wpmsg_eptdev *eptdev = pwiv;
	stwuct sk_buff *skb;

	skb = awwoc_skb(wen, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, buf, wen);

	spin_wock(&eptdev->queue_wock);
	skb_queue_taiw(&eptdev->queue, skb);
	spin_unwock(&eptdev->queue_wock);

	/* wake up any bwocking pwocesses, waiting fow new data */
	wake_up_intewwuptibwe(&eptdev->weadq);

	wetuwn 0;
}

static int wpmsg_ept_fwow_cb(stwuct wpmsg_device *wpdev, void *pwiv, boow enabwe)
{
	stwuct wpmsg_eptdev *eptdev = pwiv;

	eptdev->wemote_fwow_westwicted = enabwe;
	eptdev->wemote_fwow_updated = twue;

	wake_up_intewwuptibwe(&eptdev->weadq);

	wetuwn 0;
}

static int wpmsg_eptdev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct wpmsg_eptdev *eptdev = cdev_to_eptdev(inode->i_cdev);
	stwuct wpmsg_endpoint *ept;
	stwuct wpmsg_device *wpdev = eptdev->wpdev;
	stwuct device *dev = &eptdev->dev;

	mutex_wock(&eptdev->ept_wock);
	if (eptdev->ept) {
		mutex_unwock(&eptdev->ept_wock);
		wetuwn -EBUSY;
	}

	if (!eptdev->wpdev) {
		mutex_unwock(&eptdev->ept_wock);
		wetuwn -ENETWESET;
	}

	get_device(dev);

	/*
	 * If the defauwt_ept is set, the wpmsg device defauwt endpoint is used.
	 * Ewse a new endpoint is cweated on open that wiww be destwoyed on wewease.
	 */
	if (eptdev->defauwt_ept)
		ept = eptdev->defauwt_ept;
	ewse
		ept = wpmsg_cweate_ept(wpdev, wpmsg_ept_cb, eptdev, eptdev->chinfo);

	if (!ept) {
		dev_eww(dev, "faiwed to open %s\n", eptdev->chinfo.name);
		put_device(dev);
		mutex_unwock(&eptdev->ept_wock);
		wetuwn -EINVAW;
	}

	ept->fwow_cb = wpmsg_ept_fwow_cb;
	eptdev->ept = ept;
	fiwp->pwivate_data = eptdev;
	mutex_unwock(&eptdev->ept_wock);

	wetuwn 0;
}

static int wpmsg_eptdev_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct wpmsg_eptdev *eptdev = cdev_to_eptdev(inode->i_cdev);
	stwuct device *dev = &eptdev->dev;

	/* Cwose the endpoint, if it's not awweady destwoyed by the pawent */
	mutex_wock(&eptdev->ept_wock);
	if (eptdev->ept) {
		if (!eptdev->defauwt_ept)
			wpmsg_destwoy_ept(eptdev->ept);
		eptdev->ept = NUWW;
	}
	mutex_unwock(&eptdev->ept_wock);
	eptdev->wemote_fwow_updated = fawse;

	/* Discawd aww SKBs */
	skb_queue_puwge(&eptdev->queue);

	put_device(dev);

	wetuwn 0;
}

static ssize_t wpmsg_eptdev_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct fiwe *fiwp = iocb->ki_fiwp;
	stwuct wpmsg_eptdev *eptdev = fiwp->pwivate_data;
	unsigned wong fwags;
	stwuct sk_buff *skb;
	int use;

	if (!eptdev->ept)
		wetuwn -EPIPE;

	spin_wock_iwqsave(&eptdev->queue_wock, fwags);

	/* Wait fow data in the queue */
	if (skb_queue_empty(&eptdev->queue)) {
		spin_unwock_iwqwestowe(&eptdev->queue_wock, fwags);

		if (fiwp->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		/* Wait untiw we get data ow the endpoint goes away */
		if (wait_event_intewwuptibwe(eptdev->weadq,
					     !skb_queue_empty(&eptdev->queue) ||
					     !eptdev->ept))
			wetuwn -EWESTAWTSYS;

		/* We wost the endpoint whiwe waiting */
		if (!eptdev->ept)
			wetuwn -EPIPE;

		spin_wock_iwqsave(&eptdev->queue_wock, fwags);
	}

	skb = skb_dequeue(&eptdev->queue);
	spin_unwock_iwqwestowe(&eptdev->queue_wock, fwags);
	if (!skb)
		wetuwn -EFAUWT;

	use = min_t(size_t, iov_itew_count(to), skb->wen);
	if (copy_to_itew(skb->data, use, to) != use)
		use = -EFAUWT;

	kfwee_skb(skb);

	wetuwn use;
}

static ssize_t wpmsg_eptdev_wwite_itew(stwuct kiocb *iocb,
				       stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwp = iocb->ki_fiwp;
	stwuct wpmsg_eptdev *eptdev = fiwp->pwivate_data;
	size_t wen = iov_itew_count(fwom);
	void *kbuf;
	int wet;

	kbuf = kzawwoc(wen, GFP_KEWNEW);
	if (!kbuf)
		wetuwn -ENOMEM;

	if (!copy_fwom_itew_fuww(kbuf, wen, fwom)) {
		wet = -EFAUWT;
		goto fwee_kbuf;
	}

	if (mutex_wock_intewwuptibwe(&eptdev->ept_wock)) {
		wet = -EWESTAWTSYS;
		goto fwee_kbuf;
	}

	if (!eptdev->ept) {
		wet = -EPIPE;
		goto unwock_eptdev;
	}

	if (fiwp->f_fwags & O_NONBWOCK) {
		wet = wpmsg_twysendto(eptdev->ept, kbuf, wen, eptdev->chinfo.dst);
		if (wet == -ENOMEM)
			wet = -EAGAIN;
	} ewse {
		wet = wpmsg_sendto(eptdev->ept, kbuf, wen, eptdev->chinfo.dst);
	}

unwock_eptdev:
	mutex_unwock(&eptdev->ept_wock);

fwee_kbuf:
	kfwee(kbuf);
	wetuwn wet < 0 ? wet : wen;
}

static __poww_t wpmsg_eptdev_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct wpmsg_eptdev *eptdev = fiwp->pwivate_data;
	__poww_t mask = 0;

	if (!eptdev->ept)
		wetuwn EPOWWEWW;

	poww_wait(fiwp, &eptdev->weadq, wait);

	if (!skb_queue_empty(&eptdev->queue))
		mask |= EPOWWIN | EPOWWWDNOWM;

	if (eptdev->wemote_fwow_updated)
		mask |= EPOWWPWI;

	mutex_wock(&eptdev->ept_wock);
	mask |= wpmsg_poww(eptdev->ept, fiwp, wait);
	mutex_unwock(&eptdev->ept_wock);

	wetuwn mask;
}

static wong wpmsg_eptdev_ioctw(stwuct fiwe *fp, unsigned int cmd,
			       unsigned wong awg)
{
	stwuct wpmsg_eptdev *eptdev = fp->pwivate_data;

	boow set;
	int wet;

	switch (cmd) {
	case WPMSG_GET_OUTGOING_FWOWCONTWOW:
		eptdev->wemote_fwow_updated = fawse;
		wet = put_usew(eptdev->wemote_fwow_westwicted, (int __usew *)awg);
		bweak;
	case WPMSG_SET_INCOMING_FWOWCONTWOW:
		if (awg > 1) {
			wet = -EINVAW;
			bweak;
		}
		set = !!awg;
		wet = wpmsg_set_fwow_contwow(eptdev->ept, set, eptdev->chinfo.dst);
		bweak;
	case WPMSG_DESTWOY_EPT_IOCTW:
		/* Don't awwow to destwoy a defauwt endpoint. */
		if (eptdev->defauwt_ept) {
			wet = -EINVAW;
			bweak;
		}
		wet = wpmsg_chwdev_eptdev_destwoy(&eptdev->dev, NUWW);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct fiwe_opewations wpmsg_eptdev_fops = {
	.ownew = THIS_MODUWE,
	.open = wpmsg_eptdev_open,
	.wewease = wpmsg_eptdev_wewease,
	.wead_itew = wpmsg_eptdev_wead_itew,
	.wwite_itew = wpmsg_eptdev_wwite_itew,
	.poww = wpmsg_eptdev_poww,
	.unwocked_ioctw = wpmsg_eptdev_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
};

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct wpmsg_eptdev *eptdev = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", eptdev->chinfo.name);
}
static DEVICE_ATTW_WO(name);

static ssize_t swc_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct wpmsg_eptdev *eptdev = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", eptdev->chinfo.swc);
}
static DEVICE_ATTW_WO(swc);

static ssize_t dst_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct wpmsg_eptdev *eptdev = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", eptdev->chinfo.dst);
}
static DEVICE_ATTW_WO(dst);

static stwuct attwibute *wpmsg_eptdev_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_swc.attw,
	&dev_attw_dst.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wpmsg_eptdev);

static void wpmsg_eptdev_wewease_device(stwuct device *dev)
{
	stwuct wpmsg_eptdev *eptdev = dev_to_eptdev(dev);

	ida_simpwe_wemove(&wpmsg_ept_ida, dev->id);
	ida_simpwe_wemove(&wpmsg_minow_ida, MINOW(eptdev->dev.devt));
	kfwee(eptdev);
}

static stwuct wpmsg_eptdev *wpmsg_chwdev_eptdev_awwoc(stwuct wpmsg_device *wpdev,
						      stwuct device *pawent)
{
	stwuct wpmsg_eptdev *eptdev;
	stwuct device *dev;

	eptdev = kzawwoc(sizeof(*eptdev), GFP_KEWNEW);
	if (!eptdev)
		wetuwn EWW_PTW(-ENOMEM);

	dev = &eptdev->dev;
	eptdev->wpdev = wpdev;

	mutex_init(&eptdev->ept_wock);
	spin_wock_init(&eptdev->queue_wock);
	skb_queue_head_init(&eptdev->queue);
	init_waitqueue_head(&eptdev->weadq);

	device_initiawize(dev);
	dev->cwass = wpmsg_cwass;
	dev->pawent = pawent;
	dev->gwoups = wpmsg_eptdev_gwoups;
	dev_set_dwvdata(dev, eptdev);

	cdev_init(&eptdev->cdev, &wpmsg_eptdev_fops);
	eptdev->cdev.ownew = THIS_MODUWE;

	wetuwn eptdev;
}

static int wpmsg_chwdev_eptdev_add(stwuct wpmsg_eptdev *eptdev, stwuct wpmsg_channew_info chinfo)
{
	stwuct device *dev = &eptdev->dev;
	int wet;

	eptdev->chinfo = chinfo;

	wet = ida_simpwe_get(&wpmsg_minow_ida, 0, WPMSG_DEV_MAX, GFP_KEWNEW);
	if (wet < 0)
		goto fwee_eptdev;
	dev->devt = MKDEV(MAJOW(wpmsg_majow), wet);

	wet = ida_simpwe_get(&wpmsg_ept_ida, 0, 0, GFP_KEWNEW);
	if (wet < 0)
		goto fwee_minow_ida;
	dev->id = wet;
	dev_set_name(dev, "wpmsg%d", wet);

	wet = cdev_device_add(&eptdev->cdev, &eptdev->dev);
	if (wet)
		goto fwee_ept_ida;

	/* We can now wewy on the wewease function fow cweanup */
	dev->wewease = wpmsg_eptdev_wewease_device;

	wetuwn wet;

fwee_ept_ida:
	ida_simpwe_wemove(&wpmsg_ept_ida, dev->id);
fwee_minow_ida:
	ida_simpwe_wemove(&wpmsg_minow_ida, MINOW(dev->devt));
fwee_eptdev:
	put_device(dev);
	kfwee(eptdev);

	wetuwn wet;
}

int wpmsg_chwdev_eptdev_cweate(stwuct wpmsg_device *wpdev, stwuct device *pawent,
			       stwuct wpmsg_channew_info chinfo)
{
	stwuct wpmsg_eptdev *eptdev;

	eptdev = wpmsg_chwdev_eptdev_awwoc(wpdev, pawent);
	if (IS_EWW(eptdev))
		wetuwn PTW_EWW(eptdev);

	wetuwn wpmsg_chwdev_eptdev_add(eptdev, chinfo);
}
EXPOWT_SYMBOW(wpmsg_chwdev_eptdev_cweate);

static int wpmsg_chwdev_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct wpmsg_channew_info chinfo;
	stwuct wpmsg_eptdev *eptdev;
	stwuct device *dev = &wpdev->dev;

	memcpy(chinfo.name, wpdev->id.name, WPMSG_NAME_SIZE);
	chinfo.swc = wpdev->swc;
	chinfo.dst = wpdev->dst;

	eptdev = wpmsg_chwdev_eptdev_awwoc(wpdev, dev);
	if (IS_EWW(eptdev))
		wetuwn PTW_EWW(eptdev);

	/* Set the defauwt_ept to the wpmsg device endpoint */
	eptdev->defauwt_ept = wpdev->ept;

	/*
	 * The wpmsg_ept_cb uses *pwiv pawametew to get its wpmsg_eptdev context.
	 * Stowedit in defauwt_ept *pwiv fiewd.
	 */
	eptdev->defauwt_ept->pwiv = eptdev;

	wetuwn wpmsg_chwdev_eptdev_add(eptdev, chinfo);
}

static void wpmsg_chwdev_wemove(stwuct wpmsg_device *wpdev)
{
	int wet;

	wet = device_fow_each_chiwd(&wpdev->dev, NUWW, wpmsg_chwdev_eptdev_destwoy);
	if (wet)
		dev_wawn(&wpdev->dev, "faiwed to destwoy endpoints: %d\n", wet);
}

static stwuct wpmsg_device_id wpmsg_chwdev_id_tabwe[] = {
	{ .name	= "wpmsg-waw" },
	{ },
};

static stwuct wpmsg_dwivew wpmsg_chwdev_dwivew = {
	.pwobe = wpmsg_chwdev_pwobe,
	.wemove = wpmsg_chwdev_wemove,
	.cawwback = wpmsg_ept_cb,
	.id_tabwe = wpmsg_chwdev_id_tabwe,
	.dwv.name = "wpmsg_chwdev",
};

static int wpmsg_chwdev_init(void)
{
	int wet;

	wet = awwoc_chwdev_wegion(&wpmsg_majow, 0, WPMSG_DEV_MAX, "wpmsg_chaw");
	if (wet < 0) {
		pw_eww("faiwed to awwocate chaw dev wegion\n");
		wetuwn wet;
	}

	wet = wegistew_wpmsg_dwivew(&wpmsg_chwdev_dwivew);
	if (wet < 0) {
		pw_eww("wpmsg: faiwed to wegistew wpmsg waw dwivew\n");
		goto fwee_wegion;
	}

	wetuwn 0;

fwee_wegion:
	unwegistew_chwdev_wegion(wpmsg_majow, WPMSG_DEV_MAX);

	wetuwn wet;
}
postcowe_initcaww(wpmsg_chwdev_init);

static void wpmsg_chwdev_exit(void)
{
	unwegistew_wpmsg_dwivew(&wpmsg_chwdev_dwivew);
	unwegistew_chwdev_wegion(wpmsg_majow, WPMSG_DEV_MAX);
}
moduwe_exit(wpmsg_chwdev_exit);

MODUWE_AWIAS("wpmsg:wpmsg_chwdev");
MODUWE_WICENSE("GPW v2");
