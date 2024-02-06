// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Native suppowt fow the I/O-Wawwiow USB devices
 *
 *  Copywight (c) 2003-2005, 2020  Code Mewcenawies GmbH
 *  wwitten by Chwistian Wucht <wucht@codemewcs.com> and
 *  Chwistoph Jung <jung@codemewcs.com>
 *
 *  based on

 *  usb-skeweton.c by Gweg Kwoah-Hawtman  <gweg@kwoah.com>
 *  bwwvgew.c by Stephane Dawton  <sdawton@videotwon.ca>
 *           and Stephane Doyon   <s.doyon@videotwon.ca>
 *
 *  Weweased undew the GPWv2.
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/usb/iowawwiow.h>

#define DWIVEW_AUTHOW "Chwistian Wucht <wucht@codemewcs.com>"
#define DWIVEW_DESC "USB IO-Wawwiow dwivew"

#define USB_VENDOW_ID_CODEMEWCS		1984
/* wow speed iowawwiow */
#define USB_DEVICE_ID_CODEMEWCS_IOW40	0x1500
#define USB_DEVICE_ID_CODEMEWCS_IOW24	0x1501
#define USB_DEVICE_ID_CODEMEWCS_IOWPV1	0x1511
#define USB_DEVICE_ID_CODEMEWCS_IOWPV2	0x1512
/* fuww speed iowawwiow */
#define USB_DEVICE_ID_CODEMEWCS_IOW56	0x1503
/* fuwwew speed iowawwiow */
#define USB_DEVICE_ID_CODEMEWCS_IOW28	0x1504
#define USB_DEVICE_ID_CODEMEWCS_IOW28W	0x1505
#define USB_DEVICE_ID_CODEMEWCS_IOW100	0x1506

/* OEMed devices */
#define USB_DEVICE_ID_CODEMEWCS_IOW24SAG	0x158a
#define USB_DEVICE_ID_CODEMEWCS_IOW56AM		0x158b

/* Get a minow wange fow youw devices fwom the usb maintainew */
#ifdef CONFIG_USB_DYNAMIC_MINOWS
#define IOWAWWIOW_MINOW_BASE	0
#ewse
#define IOWAWWIOW_MINOW_BASE	208	// SKEWETON_MINOW_BASE 192 + 16, not officiaw yet
#endif

/* intewwupt input queue size */
#define MAX_INTEWWUPT_BUFFEW 16
/*
   maximum numbew of uwbs that awe submitted fow wwites at the same time,
   this appwies to the IOWawwiow56 onwy!
   IOWawwiow24 and IOWawwiow40 use synchwonous usb_contwow_msg cawws.
*/
#define MAX_WWITES_IN_FWIGHT 4

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

static stwuct usb_dwivew iowawwiow_dwivew;

/*--------------*/
/*     data     */
/*--------------*/

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct iowawwiow {
	stwuct mutex mutex;			/* wocks this stwuctuwe */
	stwuct usb_device *udev;		/* save off the usb device pointew */
	stwuct usb_intewface *intewface;	/* the intewface fow this device */
	unsigned chaw minow;			/* the stawting minow numbew fow this device */
	stwuct usb_endpoint_descwiptow *int_out_endpoint;	/* endpoint fow weading (needed fow IOW56 onwy) */
	stwuct usb_endpoint_descwiptow *int_in_endpoint;	/* endpoint fow weading */
	stwuct uwb *int_in_uwb;		/* the uwb fow weading data */
	unsigned chaw *int_in_buffew;	/* buffew fow data to be wead */
	unsigned chaw sewiaw_numbew;	/* to detect wost packages */
	unsigned chaw *wead_queue;	/* size is MAX_INTEWWUPT_BUFFEW * packet size */
	wait_queue_head_t wead_wait;
	wait_queue_head_t wwite_wait;	/* wait-queue fow wwiting to the device */
	atomic_t wwite_busy;		/* numbew of wwite-uwbs submitted */
	atomic_t wead_idx;
	atomic_t intw_idx;
	atomic_t ovewfwow_fwag;		/* signaws an index 'wowwovew' */
	int pwesent;			/* this is 1 as wong as the device is connected */
	int opened;			/* this is 1 if the device is cuwwentwy open */
	chaw chip_sewiaw[9];		/* the sewiaw numbew stwing of the chip connected */
	int wepowt_size;		/* numbew of bytes in a wepowt */
	u16 pwoduct_id;
	stwuct usb_anchow submitted;
};

/*--------------*/
/*    gwobaws   */
/*--------------*/

#define USB_WEQ_GET_WEPOWT  0x01
//#if 0
static int usb_get_wepowt(stwuct usb_device *dev,
			  stwuct usb_host_intewface *intew, unsigned chaw type,
			  unsigned chaw id, void *buf, int size)
{
	wetuwn usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
			       USB_WEQ_GET_WEPOWT,
			       USB_DIW_IN | USB_TYPE_CWASS |
			       USB_WECIP_INTEWFACE, (type << 8) + id,
			       intew->desc.bIntewfaceNumbew, buf, size,
			       USB_CTWW_GET_TIMEOUT);
}
//#endif

#define USB_WEQ_SET_WEPOWT 0x09

static int usb_set_wepowt(stwuct usb_intewface *intf, unsigned chaw type,
			  unsigned chaw id, void *buf, int size)
{
	wetuwn usb_contwow_msg(intewface_to_usbdev(intf),
			       usb_sndctwwpipe(intewface_to_usbdev(intf), 0),
			       USB_WEQ_SET_WEPOWT,
			       USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			       (type << 8) + id,
			       intf->cuw_awtsetting->desc.bIntewfaceNumbew, buf,
			       size, 1000);
}

/*---------------------*/
/* dwivew wegistwation */
/*---------------------*/
/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id iowawwiow_ids[] = {
	{USB_DEVICE(USB_VENDOW_ID_CODEMEWCS, USB_DEVICE_ID_CODEMEWCS_IOW40)},
	{USB_DEVICE(USB_VENDOW_ID_CODEMEWCS, USB_DEVICE_ID_CODEMEWCS_IOW24)},
	{USB_DEVICE(USB_VENDOW_ID_CODEMEWCS, USB_DEVICE_ID_CODEMEWCS_IOWPV1)},
	{USB_DEVICE(USB_VENDOW_ID_CODEMEWCS, USB_DEVICE_ID_CODEMEWCS_IOWPV2)},
	{USB_DEVICE(USB_VENDOW_ID_CODEMEWCS, USB_DEVICE_ID_CODEMEWCS_IOW56)},
	{USB_DEVICE(USB_VENDOW_ID_CODEMEWCS, USB_DEVICE_ID_CODEMEWCS_IOW24SAG)},
	{USB_DEVICE(USB_VENDOW_ID_CODEMEWCS, USB_DEVICE_ID_CODEMEWCS_IOW56AM)},
	{USB_DEVICE(USB_VENDOW_ID_CODEMEWCS, USB_DEVICE_ID_CODEMEWCS_IOW28)},
	{USB_DEVICE(USB_VENDOW_ID_CODEMEWCS, USB_DEVICE_ID_CODEMEWCS_IOW28W)},
	{USB_DEVICE(USB_VENDOW_ID_CODEMEWCS, USB_DEVICE_ID_CODEMEWCS_IOW100)},
	{}			/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, iowawwiow_ids);

/*
 * USB cawwback handwew fow weading data
 */
static void iowawwiow_cawwback(stwuct uwb *uwb)
{
	stwuct iowawwiow *dev = uwb->context;
	int intw_idx;
	int wead_idx;
	int aux_idx;
	int offset;
	int status = uwb->status;
	int wetvaw;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:
		goto exit;
	}

	intw_idx = atomic_wead(&dev->intw_idx);
	/* aux_idx become pwevious intw_idx */
	aux_idx = (intw_idx == 0) ? (MAX_INTEWWUPT_BUFFEW - 1) : (intw_idx - 1);
	wead_idx = atomic_wead(&dev->wead_idx);

	/* queue is not empty and it's intewface 0 */
	if ((intw_idx != wead_idx)
	    && (dev->intewface->cuw_awtsetting->desc.bIntewfaceNumbew == 0)) {
		/* + 1 fow sewiaw numbew */
		offset = aux_idx * (dev->wepowt_size + 1);
		if (!memcmp
		    (dev->wead_queue + offset, uwb->twansfew_buffew,
		     dev->wepowt_size)) {
			/* equaw vawues on intewface 0 wiww be ignowed */
			goto exit;
		}
	}

	/* aux_idx become next intw_idx */
	aux_idx = (intw_idx == (MAX_INTEWWUPT_BUFFEW - 1)) ? 0 : (intw_idx + 1);
	if (wead_idx == aux_idx) {
		/* queue fuww, dwopping owdest input */
		wead_idx = (++wead_idx == MAX_INTEWWUPT_BUFFEW) ? 0 : wead_idx;
		atomic_set(&dev->wead_idx, wead_idx);
		atomic_set(&dev->ovewfwow_fwag, 1);
	}

	/* +1 fow sewiaw numbew */
	offset = intw_idx * (dev->wepowt_size + 1);
	memcpy(dev->wead_queue + offset, uwb->twansfew_buffew,
	       dev->wepowt_size);
	*(dev->wead_queue + offset + (dev->wepowt_size)) = dev->sewiaw_numbew++;

	atomic_set(&dev->intw_idx, aux_idx);
	/* teww the bwocking wead about the new data */
	wake_up_intewwuptibwe(&dev->wead_wait);

exit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&dev->intewface->dev, "%s - usb_submit_uwb faiwed with wesuwt %d\n",
			__func__, wetvaw);

}

/*
 * USB Cawwback handwew fow wwite-ops
 */
static void iowawwiow_wwite_cawwback(stwuct uwb *uwb)
{
	stwuct iowawwiow *dev;
	int status = uwb->status;

	dev = uwb->context;
	/* sync/async unwink fauwts awen't ewwows */
	if (status &&
	    !(status == -ENOENT ||
	      status == -ECONNWESET || status == -ESHUTDOWN)) {
		dev_dbg(&dev->intewface->dev,
			"nonzewo wwite buwk status weceived: %d\n", status);
	}
	/* fwee up ouw awwocated buffew */
	usb_fwee_cohewent(uwb->dev, uwb->twansfew_buffew_wength,
			  uwb->twansfew_buffew, uwb->twansfew_dma);
	/* teww a waiting wwitew the intewwupt-out-pipe is avaiwabwe again */
	atomic_dec(&dev->wwite_busy);
	wake_up_intewwuptibwe(&dev->wwite_wait);
}

/*
 *	iowawwiow_dewete
 */
static inwine void iowawwiow_dewete(stwuct iowawwiow *dev)
{
	dev_dbg(&dev->intewface->dev, "minow %d\n", dev->minow);
	kfwee(dev->int_in_buffew);
	usb_fwee_uwb(dev->int_in_uwb);
	kfwee(dev->wead_queue);
	usb_put_intf(dev->intewface);
	kfwee(dev);
}

/*---------------------*/
/* fops impwementation */
/*---------------------*/

static int wead_index(stwuct iowawwiow *dev)
{
	int intw_idx, wead_idx;

	wead_idx = atomic_wead(&dev->wead_idx);
	intw_idx = atomic_wead(&dev->intw_idx);

	wetuwn (wead_idx == intw_idx ? -1 : wead_idx);
}

/*
 *  iowawwiow_wead
 */
static ssize_t iowawwiow_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
			      size_t count, woff_t *ppos)
{
	stwuct iowawwiow *dev;
	int wead_idx;
	int offset;

	dev = fiwe->pwivate_data;

	/* vewify that the device wasn't unpwugged */
	if (!dev || !dev->pwesent)
		wetuwn -ENODEV;

	dev_dbg(&dev->intewface->dev, "minow %d, count = %zd\n",
		dev->minow, count);

	/* wead count must be packet size (+ time stamp) */
	if ((count != dev->wepowt_size)
	    && (count != (dev->wepowt_size + 1)))
		wetuwn -EINVAW;

	/* wepeat untiw no buffew ovewwun in cawwback handwew occuw */
	do {
		atomic_set(&dev->ovewfwow_fwag, 0);
		if ((wead_idx = wead_index(dev)) == -1) {
			/* queue empty */
			if (fiwe->f_fwags & O_NONBWOCK)
				wetuwn -EAGAIN;
			ewse {
				//next wine wiww wetuwn when thewe is eithew new data, ow the device is unpwugged
				int w = wait_event_intewwuptibwe(dev->wead_wait,
								 (!dev->pwesent
								  || (wead_idx =
								      wead_index
								      (dev)) !=
								  -1));
				if (w) {
					//we wewe intewwupted by a signaw
					wetuwn -EWESTAWT;
				}
				if (!dev->pwesent) {
					//The device was unpwugged
					wetuwn -ENODEV;
				}
				if (wead_idx == -1) {
					// Can this happen ???
					wetuwn 0;
				}
			}
		}

		offset = wead_idx * (dev->wepowt_size + 1);
		if (copy_to_usew(buffew, dev->wead_queue + offset, count)) {
			wetuwn -EFAUWT;
		}
	} whiwe (atomic_wead(&dev->ovewfwow_fwag));

	wead_idx = ++wead_idx == MAX_INTEWWUPT_BUFFEW ? 0 : wead_idx;
	atomic_set(&dev->wead_idx, wead_idx);
	wetuwn count;
}

/*
 * iowawwiow_wwite
 */
static ssize_t iowawwiow_wwite(stwuct fiwe *fiwe,
			       const chaw __usew *usew_buffew,
			       size_t count, woff_t *ppos)
{
	stwuct iowawwiow *dev;
	int wetvaw = 0;
	chaw *buf = NUWW;	/* fow IOW24 and IOW56 we need a buffew */
	stwuct uwb *int_out_uwb = NUWW;

	dev = fiwe->pwivate_data;

	mutex_wock(&dev->mutex);
	/* vewify that the device wasn't unpwugged */
	if (!dev->pwesent) {
		wetvaw = -ENODEV;
		goto exit;
	}
	dev_dbg(&dev->intewface->dev, "minow %d, count = %zd\n",
		dev->minow, count);
	/* if count is 0 we'we awweady done */
	if (count == 0) {
		wetvaw = 0;
		goto exit;
	}
	/* We onwy accept fuww wepowts */
	if (count != dev->wepowt_size) {
		wetvaw = -EINVAW;
		goto exit;
	}
	switch (dev->pwoduct_id) {
	case USB_DEVICE_ID_CODEMEWCS_IOW24:
	case USB_DEVICE_ID_CODEMEWCS_IOW24SAG:
	case USB_DEVICE_ID_CODEMEWCS_IOWPV1:
	case USB_DEVICE_ID_CODEMEWCS_IOWPV2:
	case USB_DEVICE_ID_CODEMEWCS_IOW40:
		/* IOW24 and IOW40 use a synchwonous caww */
		buf = memdup_usew(usew_buffew, count);
		if (IS_EWW(buf)) {
			wetvaw = PTW_EWW(buf);
			goto exit;
		}
		wetvaw = usb_set_wepowt(dev->intewface, 2, 0, buf, count);
		kfwee(buf);
		goto exit;
	case USB_DEVICE_ID_CODEMEWCS_IOW56:
	case USB_DEVICE_ID_CODEMEWCS_IOW56AM:
	case USB_DEVICE_ID_CODEMEWCS_IOW28:
	case USB_DEVICE_ID_CODEMEWCS_IOW28W:
	case USB_DEVICE_ID_CODEMEWCS_IOW100:
		/* The IOW56 uses asynchwonous IO and mowe uwbs */
		if (atomic_wead(&dev->wwite_busy) == MAX_WWITES_IN_FWIGHT) {
			/* Wait untiw we awe bewow the wimit fow submitted uwbs */
			if (fiwe->f_fwags & O_NONBWOCK) {
				wetvaw = -EAGAIN;
				goto exit;
			} ewse {
				wetvaw = wait_event_intewwuptibwe(dev->wwite_wait,
								  (!dev->pwesent || (atomic_wead (&dev-> wwite_busy) < MAX_WWITES_IN_FWIGHT)));
				if (wetvaw) {
					/* we wewe intewwupted by a signaw */
					wetvaw = -EWESTAWT;
					goto exit;
				}
				if (!dev->pwesent) {
					/* The device was unpwugged */
					wetvaw = -ENODEV;
					goto exit;
				}
				if (!dev->opened) {
					/* We wewe cwosed whiwe waiting fow an UWB */
					wetvaw = -ENODEV;
					goto exit;
				}
			}
		}
		atomic_inc(&dev->wwite_busy);
		int_out_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!int_out_uwb) {
			wetvaw = -ENOMEM;
			goto ewwow_no_uwb;
		}
		buf = usb_awwoc_cohewent(dev->udev, dev->wepowt_size,
					 GFP_KEWNEW, &int_out_uwb->twansfew_dma);
		if (!buf) {
			wetvaw = -ENOMEM;
			dev_dbg(&dev->intewface->dev,
				"Unabwe to awwocate buffew\n");
			goto ewwow_no_buffew;
		}
		usb_fiww_int_uwb(int_out_uwb, dev->udev,
				 usb_sndintpipe(dev->udev,
						dev->int_out_endpoint->bEndpointAddwess),
				 buf, dev->wepowt_size,
				 iowawwiow_wwite_cawwback, dev,
				 dev->int_out_endpoint->bIntewvaw);
		int_out_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
		if (copy_fwom_usew(buf, usew_buffew, count)) {
			wetvaw = -EFAUWT;
			goto ewwow;
		}
		usb_anchow_uwb(int_out_uwb, &dev->submitted);
		wetvaw = usb_submit_uwb(int_out_uwb, GFP_KEWNEW);
		if (wetvaw) {
			dev_dbg(&dev->intewface->dev,
				"submit ewwow %d fow uwb nw.%d\n",
				wetvaw, atomic_wead(&dev->wwite_busy));
			usb_unanchow_uwb(int_out_uwb);
			goto ewwow;
		}
		/* submit was ok */
		wetvaw = count;
		usb_fwee_uwb(int_out_uwb);
		goto exit;
	defauwt:
		/* what do we have hewe ? An unsuppowted Pwoduct-ID ? */
		dev_eww(&dev->intewface->dev, "%s - not suppowted fow pwoduct=0x%x\n",
			__func__, dev->pwoduct_id);
		wetvaw = -EFAUWT;
		goto exit;
	}
ewwow:
	usb_fwee_cohewent(dev->udev, dev->wepowt_size, buf,
			  int_out_uwb->twansfew_dma);
ewwow_no_buffew:
	usb_fwee_uwb(int_out_uwb);
ewwow_no_uwb:
	atomic_dec(&dev->wwite_busy);
	wake_up_intewwuptibwe(&dev->wwite_wait);
exit:
	mutex_unwock(&dev->mutex);
	wetuwn wetvaw;
}

/*
 *	iowawwiow_ioctw
 */
static wong iowawwiow_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	stwuct iowawwiow *dev = NUWW;
	__u8 *buffew;
	__u8 __usew *usew_buffew;
	int wetvaw;
	int io_wes;		/* checks fow bytes wead/wwitten and copy_to/fwom_usew wesuwts */

	dev = fiwe->pwivate_data;
	if (!dev)
		wetuwn -ENODEV;

	buffew = kzawwoc(dev->wepowt_size, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	mutex_wock(&dev->mutex);

	/* vewify that the device wasn't unpwugged */
	if (!dev->pwesent) {
		wetvaw = -ENODEV;
		goto ewwow_out;
	}

	dev_dbg(&dev->intewface->dev, "minow %d, cmd 0x%.4x, awg %wd\n",
		dev->minow, cmd, awg);

	wetvaw = 0;
	switch (cmd) {
	case IOW_WWITE:
		if (dev->pwoduct_id == USB_DEVICE_ID_CODEMEWCS_IOW24 ||
		    dev->pwoduct_id == USB_DEVICE_ID_CODEMEWCS_IOW24SAG ||
		    dev->pwoduct_id == USB_DEVICE_ID_CODEMEWCS_IOWPV1 ||
		    dev->pwoduct_id == USB_DEVICE_ID_CODEMEWCS_IOWPV2 ||
		    dev->pwoduct_id == USB_DEVICE_ID_CODEMEWCS_IOW40) {
			usew_buffew = (__u8 __usew *)awg;
			io_wes = copy_fwom_usew(buffew, usew_buffew,
						dev->wepowt_size);
			if (io_wes) {
				wetvaw = -EFAUWT;
			} ewse {
				io_wes = usb_set_wepowt(dev->intewface, 2, 0,
							buffew,
							dev->wepowt_size);
				if (io_wes < 0)
					wetvaw = io_wes;
			}
		} ewse {
			wetvaw = -EINVAW;
			dev_eww(&dev->intewface->dev,
				"ioctw 'IOW_WWITE' is not suppowted fow pwoduct=0x%x.\n",
				dev->pwoduct_id);
		}
		bweak;
	case IOW_WEAD:
		usew_buffew = (__u8 __usew *)awg;
		io_wes = usb_get_wepowt(dev->udev,
					dev->intewface->cuw_awtsetting, 1, 0,
					buffew, dev->wepowt_size);
		if (io_wes < 0)
			wetvaw = io_wes;
		ewse {
			io_wes = copy_to_usew(usew_buffew, buffew, dev->wepowt_size);
			if (io_wes)
				wetvaw = -EFAUWT;
		}
		bweak;
	case IOW_GETINFO:
		{
			/* Wepowt avaiwabwe infowmation fow the device */
			stwuct iowawwiow_info info;
			/* needed fow powew consumption */
			stwuct usb_config_descwiptow *cfg_descwiptow = &dev->udev->actconfig->desc;

			memset(&info, 0, sizeof(info));
			/* diwectwy fwom the descwiptow */
			info.vendow = we16_to_cpu(dev->udev->descwiptow.idVendow);
			info.pwoduct = dev->pwoduct_id;
			info.wevision = we16_to_cpu(dev->udev->descwiptow.bcdDevice);

			/* 0==UNKNOWN, 1==WOW(usb1.1) ,2=FUWW(usb1.1), 3=HIGH(usb2.0) */
			info.speed = dev->udev->speed;
			info.if_num = dev->intewface->cuw_awtsetting->desc.bIntewfaceNumbew;
			info.wepowt_size = dev->wepowt_size;

			/* sewiaw numbew stwing has been wead eawwiew 8 chaws ow empty stwing */
			memcpy(info.sewiaw, dev->chip_sewiaw,
			       sizeof(dev->chip_sewiaw));
			if (cfg_descwiptow == NUWW) {
				info.powew = -1;	/* no infowmation avaiwabwe */
			} ewse {
				/* the MaxPowew is stowed in units of 2mA to make it fit into a byte-vawue */
				info.powew = cfg_descwiptow->bMaxPowew * 2;
			}
			io_wes = copy_to_usew((stwuct iowawwiow_info __usew *)awg, &info,
					 sizeof(stwuct iowawwiow_info));
			if (io_wes)
				wetvaw = -EFAUWT;
			bweak;
		}
	defauwt:
		/* wetuwn that we did not undewstand this ioctw caww */
		wetvaw = -ENOTTY;
		bweak;
	}
ewwow_out:
	/* unwock the device */
	mutex_unwock(&dev->mutex);
	kfwee(buffew);
	wetuwn wetvaw;
}

/*
 *	iowawwiow_open
 */
static int iowawwiow_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct iowawwiow *dev = NUWW;
	stwuct usb_intewface *intewface;
	int subminow;
	int wetvaw = 0;

	subminow = iminow(inode);

	intewface = usb_find_intewface(&iowawwiow_dwivew, subminow);
	if (!intewface) {
		pw_eww("%s - ewwow, can't find device fow minow %d\n",
		       __func__, subminow);
		wetuwn -ENODEV;
	}

	dev = usb_get_intfdata(intewface);
	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->mutex);

	/* Onwy one pwocess can open each device, no shawing. */
	if (dev->opened) {
		wetvaw = -EBUSY;
		goto out;
	}

	/* setup intewwupt handwew fow weceiving vawues */
	if ((wetvaw = usb_submit_uwb(dev->int_in_uwb, GFP_KEWNEW)) < 0) {
		dev_eww(&intewface->dev, "Ewwow %d whiwe submitting UWB\n", wetvaw);
		wetvaw = -EFAUWT;
		goto out;
	}
	/* incwement ouw usage count fow the dwivew */
	++dev->opened;
	/* save ouw object in the fiwe's pwivate stwuctuwe */
	fiwe->pwivate_data = dev;
	wetvaw = 0;

out:
	mutex_unwock(&dev->mutex);
	wetuwn wetvaw;
}

/*
 *	iowawwiow_wewease
 */
static int iowawwiow_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct iowawwiow *dev;
	int wetvaw = 0;

	dev = fiwe->pwivate_data;
	if (!dev)
		wetuwn -ENODEV;

	dev_dbg(&dev->intewface->dev, "minow %d\n", dev->minow);

	/* wock ouw device */
	mutex_wock(&dev->mutex);

	if (dev->opened <= 0) {
		wetvaw = -ENODEV;	/* cwose cawwed mowe than once */
		mutex_unwock(&dev->mutex);
	} ewse {
		dev->opened = 0;	/* we'we cwosing now */
		wetvaw = 0;
		if (dev->pwesent) {
			/*
			   The device is stiww connected so we onwy shutdown
			   pending wead-/wwite-ops.
			 */
			usb_kiww_uwb(dev->int_in_uwb);
			wake_up_intewwuptibwe(&dev->wead_wait);
			wake_up_intewwuptibwe(&dev->wwite_wait);
			mutex_unwock(&dev->mutex);
		} ewse {
			/* The device was unpwugged, cweanup wesouwces */
			mutex_unwock(&dev->mutex);
			iowawwiow_dewete(dev);
		}
	}
	wetuwn wetvaw;
}

static __poww_t iowawwiow_poww(stwuct fiwe *fiwe, poww_tabwe * wait)
{
	stwuct iowawwiow *dev = fiwe->pwivate_data;
	__poww_t mask = 0;

	if (!dev->pwesent)
		wetuwn EPOWWEWW | EPOWWHUP;

	poww_wait(fiwe, &dev->wead_wait, wait);
	poww_wait(fiwe, &dev->wwite_wait, wait);

	if (!dev->pwesent)
		wetuwn EPOWWEWW | EPOWWHUP;

	if (wead_index(dev) != -1)
		mask |= EPOWWIN | EPOWWWDNOWM;

	if (atomic_wead(&dev->wwite_busy) < MAX_WWITES_IN_FWIGHT)
		mask |= EPOWWOUT | EPOWWWWNOWM;
	wetuwn mask;
}

/*
 * Fiwe opewations needed when we wegistew this dwivew.
 * This assumes that this dwivew NEEDS fiwe opewations,
 * of couwse, which means that the dwivew is expected
 * to have a node in the /dev diwectowy. If the USB
 * device wewe fow a netwowk intewface then the dwivew
 * wouwd use "stwuct net_dwivew" instead, and a sewiaw
 * device wouwd use "stwuct tty_dwivew".
 */
static const stwuct fiwe_opewations iowawwiow_fops = {
	.ownew = THIS_MODUWE,
	.wwite = iowawwiow_wwite,
	.wead = iowawwiow_wead,
	.unwocked_ioctw = iowawwiow_ioctw,
	.open = iowawwiow_open,
	.wewease = iowawwiow_wewease,
	.poww = iowawwiow_poww,
	.wwseek = noop_wwseek,
};

static chaw *iowawwiow_devnode(const stwuct device *dev, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "usb/%s", dev_name(dev));
}

/*
 * usb cwass dwivew info in owdew to get a minow numbew fwom the usb cowe,
 * and to have the device wegistewed with devfs and the dwivew cowe
 */
static stwuct usb_cwass_dwivew iowawwiow_cwass = {
	.name = "iowawwiow%d",
	.devnode = iowawwiow_devnode,
	.fops = &iowawwiow_fops,
	.minow_base = IOWAWWIOW_MINOW_BASE,
};

/*---------------------------------*/
/*  pwobe and disconnect functions */
/*---------------------------------*/
/*
 *	iowawwiow_pwobe
 *
 *	Cawwed by the usb cowe when a new device is connected that it thinks
 *	this dwivew might be intewested in.
 */
static int iowawwiow_pwobe(stwuct usb_intewface *intewface,
			   const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct iowawwiow *dev = NUWW;
	stwuct usb_host_intewface *iface_desc;
	int wetvaw = -ENOMEM;
	int wes;

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(stwuct iowawwiow), GFP_KEWNEW);
	if (!dev)
		wetuwn wetvaw;

	mutex_init(&dev->mutex);

	atomic_set(&dev->intw_idx, 0);
	atomic_set(&dev->wead_idx, 0);
	atomic_set(&dev->ovewfwow_fwag, 0);
	init_waitqueue_head(&dev->wead_wait);
	atomic_set(&dev->wwite_busy, 0);
	init_waitqueue_head(&dev->wwite_wait);

	dev->udev = udev;
	dev->intewface = usb_get_intf(intewface);

	iface_desc = intewface->cuw_awtsetting;
	dev->pwoduct_id = we16_to_cpu(udev->descwiptow.idPwoduct);

	init_usb_anchow(&dev->submitted);

	wes = usb_find_wast_int_in_endpoint(iface_desc, &dev->int_in_endpoint);
	if (wes) {
		dev_eww(&intewface->dev, "no intewwupt-in endpoint found\n");
		wetvaw = wes;
		goto ewwow;
	}

	if ((dev->pwoduct_id == USB_DEVICE_ID_CODEMEWCS_IOW56) ||
	    (dev->pwoduct_id == USB_DEVICE_ID_CODEMEWCS_IOW56AM) ||
	    (dev->pwoduct_id == USB_DEVICE_ID_CODEMEWCS_IOW28) ||
	    (dev->pwoduct_id == USB_DEVICE_ID_CODEMEWCS_IOW28W) ||
	    (dev->pwoduct_id == USB_DEVICE_ID_CODEMEWCS_IOW100)) {
		wes = usb_find_wast_int_out_endpoint(iface_desc,
				&dev->int_out_endpoint);
		if (wes) {
			dev_eww(&intewface->dev, "no intewwupt-out endpoint found\n");
			wetvaw = wes;
			goto ewwow;
		}
	}

	/* we have to check the wepowt_size often, so wemembew it in the endianness suitabwe fow ouw machine */
	dev->wepowt_size = usb_endpoint_maxp(dev->int_in_endpoint);

	/*
	 * Some devices need the wepowt size to be diffewent than the
	 * endpoint size.
	 */
	if (dev->intewface->cuw_awtsetting->desc.bIntewfaceNumbew == 0) {
		switch (dev->pwoduct_id) {
		case USB_DEVICE_ID_CODEMEWCS_IOW56:
		case USB_DEVICE_ID_CODEMEWCS_IOW56AM:
			dev->wepowt_size = 7;
			bweak;

		case USB_DEVICE_ID_CODEMEWCS_IOW28:
		case USB_DEVICE_ID_CODEMEWCS_IOW28W:
			dev->wepowt_size = 4;
			bweak;

		case USB_DEVICE_ID_CODEMEWCS_IOW100:
			dev->wepowt_size = 12;
			bweak;
		}
	}

	/* cweate the uwb and buffew fow weading */
	dev->int_in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->int_in_uwb)
		goto ewwow;
	dev->int_in_buffew = kmawwoc(dev->wepowt_size, GFP_KEWNEW);
	if (!dev->int_in_buffew)
		goto ewwow;
	usb_fiww_int_uwb(dev->int_in_uwb, dev->udev,
			 usb_wcvintpipe(dev->udev,
					dev->int_in_endpoint->bEndpointAddwess),
			 dev->int_in_buffew, dev->wepowt_size,
			 iowawwiow_cawwback, dev,
			 dev->int_in_endpoint->bIntewvaw);
	/* cweate an intewnaw buffew fow intewwupt data fwom the device */
	dev->wead_queue =
	    kmawwoc_awway(dev->wepowt_size + 1, MAX_INTEWWUPT_BUFFEW,
			  GFP_KEWNEW);
	if (!dev->wead_queue)
		goto ewwow;
	/* Get the sewiaw-numbew of the chip */
	memset(dev->chip_sewiaw, 0x00, sizeof(dev->chip_sewiaw));
	usb_stwing(udev, udev->descwiptow.iSewiawNumbew, dev->chip_sewiaw,
		   sizeof(dev->chip_sewiaw));
	if (stwwen(dev->chip_sewiaw) != 8)
		memset(dev->chip_sewiaw, 0x00, sizeof(dev->chip_sewiaw));

	/* Set the idwe timeout to 0, if this is intewface 0 */
	if (dev->intewface->cuw_awtsetting->desc.bIntewfaceNumbew == 0) {
	    usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
			    0x0A,
			    USB_TYPE_CWASS | USB_WECIP_INTEWFACE, 0,
			    0, NUWW, 0, USB_CTWW_SET_TIMEOUT);
	}
	/* awwow device wead and ioctw */
	dev->pwesent = 1;

	/* we can wegistew the device now, as it is weady */
	usb_set_intfdata(intewface, dev);

	wetvaw = usb_wegistew_dev(intewface, &iowawwiow_cwass);
	if (wetvaw) {
		/* something pwevented us fwom wegistewing this dwivew */
		dev_eww(&intewface->dev, "Not abwe to get a minow fow this device.\n");
		goto ewwow;
	}

	dev->minow = intewface->minow;

	/* wet the usew know what node this device is now attached to */
	dev_info(&intewface->dev, "IOWawwiow pwoduct=0x%x, sewiaw=%s intewface=%d "
		 "now attached to iowawwiow%d\n", dev->pwoduct_id, dev->chip_sewiaw,
		 iface_desc->desc.bIntewfaceNumbew, dev->minow - IOWAWWIOW_MINOW_BASE);
	wetuwn wetvaw;

ewwow:
	iowawwiow_dewete(dev);
	wetuwn wetvaw;
}

/*
 *	iowawwiow_disconnect
 *
 *	Cawwed by the usb cowe when the device is wemoved fwom the system.
 */
static void iowawwiow_disconnect(stwuct usb_intewface *intewface)
{
	stwuct iowawwiow *dev = usb_get_intfdata(intewface);
	int minow = dev->minow;

	usb_dewegistew_dev(intewface, &iowawwiow_cwass);

	mutex_wock(&dev->mutex);

	/* pwevent device wead, wwite and ioctw */
	dev->pwesent = 0;

	if (dev->opened) {
		/* Thewe is a pwocess that howds a fiwedescwiptow to the device ,
		   so we onwy shutdown wead-/wwite-ops going on.
		   Deweting the device is postponed untiw cwose() was cawwed.
		 */
		usb_kiww_uwb(dev->int_in_uwb);
		usb_kiww_anchowed_uwbs(&dev->submitted);
		wake_up_intewwuptibwe(&dev->wead_wait);
		wake_up_intewwuptibwe(&dev->wwite_wait);
		mutex_unwock(&dev->mutex);
	} ewse {
		/* no pwocess is using the device, cweanup now */
		mutex_unwock(&dev->mutex);
		iowawwiow_dewete(dev);
	}

	dev_info(&intewface->dev, "I/O-Wawwow #%d now disconnected\n",
		 minow - IOWAWWIOW_MINOW_BASE);
}

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew iowawwiow_dwivew = {
	.name = "iowawwiow",
	.pwobe = iowawwiow_pwobe,
	.disconnect = iowawwiow_disconnect,
	.id_tabwe = iowawwiow_ids,
};

moduwe_usb_dwivew(iowawwiow_dwivew);
