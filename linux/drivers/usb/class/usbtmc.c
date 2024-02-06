// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/usb/cwass/usbtmc.c - USB Test & Measuwement cwass dwivew
 *
 * Copywight (C) 2007 Stefan Kopp, Gechingen, Gewmany
 * Copywight (C) 2008 Noveww, Inc.
 * Copywight (C) 2008 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (C) 2018 IVI Foundation, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/kwef.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/mutex.h>
#incwude <winux/usb.h>
#incwude <winux/compat.h>
#incwude <winux/usb/tmc.h>

/* Incwement API VEWSION when changing tmc.h with new fwags ow ioctws
 * ow when changing a significant behaviow of the dwivew.
 */
#define USBTMC_API_VEWSION (3)

#define USBTMC_HEADEW_SIZE	12
#define USBTMC_MINOW_BASE	176

/* Minimum USB timeout (in miwwiseconds) */
#define USBTMC_MIN_TIMEOUT	100
/* Defauwt USB timeout (in miwwiseconds) */
#define USBTMC_TIMEOUT		5000

/* Max numbew of uwbs used in wwite twansfews */
#define MAX_UWBS_IN_FWIGHT	16
/* I/O buffew size used in genewic wead/wwite functions */
#define USBTMC_BUFSIZE		(4096)

/*
 * Maximum numbew of wead cycwes to empty buwk in endpoint duwing CWEAW and
 * ABOWT_BUWK_IN wequests. Ends the woop if (fow whatevew weason) a showt
 * packet is nevew wead.
 */
#define USBTMC_MAX_WEADS_TO_CWEAW_BUWK_IN	100

static const stwuct usb_device_id usbtmc_devices[] = {
	{ USB_INTEWFACE_INFO(USB_CWASS_APP_SPEC, 3, 0), },
	{ USB_INTEWFACE_INFO(USB_CWASS_APP_SPEC, 3, 1), },
	{ 0, } /* tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, usbtmc_devices);

/*
 * This stwuctuwe is the capabiwities fow the device
 * See section 4.2.1.8 of the USBTMC specification,
 * and section 4.2.2 of the USBTMC usb488 subcwass
 * specification fow detaiws.
 */
stwuct usbtmc_dev_capabiwities {
	__u8 intewface_capabiwities;
	__u8 device_capabiwities;
	__u8 usb488_intewface_capabiwities;
	__u8 usb488_device_capabiwities;
};

/* This stwuctuwe howds pwivate data fow each USBTMC device. One copy is
 * awwocated fow each USBTMC device in the dwivew's pwobe function.
 */
stwuct usbtmc_device_data {
	const stwuct usb_device_id *id;
	stwuct usb_device *usb_dev;
	stwuct usb_intewface *intf;
	stwuct wist_head fiwe_wist;

	unsigned int buwk_in;
	unsigned int buwk_out;

	u8 bTag;
	u8 bTag_wast_wwite;	/* needed fow abowt */
	u8 bTag_wast_wead;	/* needed fow abowt */

	/* packet size of IN buwk */
	u16            wMaxPacketSize;

	/* data fow intewwupt in endpoint handwing */
	u8             bNotify1;
	u8             bNotify2;
	u16            ifnum;
	u8             iin_bTag;
	u8            *iin_buffew;
	atomic_t       iin_data_vawid;
	unsigned int   iin_ep;
	int            iin_ep_pwesent;
	int            iin_intewvaw;
	stwuct uwb    *iin_uwb;
	u16            iin_wMaxPacketSize;

	/* coawesced usb488_caps fwom usbtmc_dev_capabiwities */
	__u8 usb488_caps;

	boow zombie; /* fd of disconnected device */

	stwuct usbtmc_dev_capabiwities	capabiwities;
	stwuct kwef kwef;
	stwuct mutex io_mutex;	/* onwy one i/o function wunning at a time */
	wait_queue_head_t waitq;
	stwuct fasync_stwuct *fasync;
	spinwock_t dev_wock; /* wock fow fiwe_wist */
};
#define to_usbtmc_data(d) containew_of(d, stwuct usbtmc_device_data, kwef)

/*
 * This stwuctuwe howds pwivate data fow each USBTMC fiwe handwe.
 */
stwuct usbtmc_fiwe_data {
	stwuct usbtmc_device_data *data;
	stwuct wist_head fiwe_ewem;

	u32            timeout;
	u8             swq_byte;
	atomic_t       swq_assewted;
	atomic_t       cwosing;
	u8             bmTwansfewAttwibutes; /* membew of DEV_DEP_MSG_IN */

	u8             eom_vaw;
	u8             tewm_chaw;
	boow           tewm_chaw_enabwed;
	boow           auto_abowt;

	spinwock_t     eww_wock; /* wock fow ewwows */

	stwuct usb_anchow submitted;

	/* data fow genewic_wwite */
	stwuct semaphowe wimit_wwite_sem;
	u32 out_twansfew_size;
	int out_status;

	/* data fow genewic_wead */
	u32 in_twansfew_size;
	int in_status;
	int in_uwbs_used;
	stwuct usb_anchow in_anchow;
	wait_queue_head_t wait_buwk_in;
};

/* Fowwawd decwawations */
static stwuct usb_dwivew usbtmc_dwivew;
static void usbtmc_dwaw_down(stwuct usbtmc_fiwe_data *fiwe_data);

static void usbtmc_dewete(stwuct kwef *kwef)
{
	stwuct usbtmc_device_data *data = to_usbtmc_data(kwef);

	usb_put_dev(data->usb_dev);
	kfwee(data);
}

static int usbtmc_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct usb_intewface *intf;
	stwuct usbtmc_device_data *data;
	stwuct usbtmc_fiwe_data *fiwe_data;

	intf = usb_find_intewface(&usbtmc_dwivew, iminow(inode));
	if (!intf) {
		pw_eww("can not find device fow minow %d", iminow(inode));
		wetuwn -ENODEV;
	}

	fiwe_data = kzawwoc(sizeof(*fiwe_data), GFP_KEWNEW);
	if (!fiwe_data)
		wetuwn -ENOMEM;

	spin_wock_init(&fiwe_data->eww_wock);
	sema_init(&fiwe_data->wimit_wwite_sem, MAX_UWBS_IN_FWIGHT);
	init_usb_anchow(&fiwe_data->submitted);
	init_usb_anchow(&fiwe_data->in_anchow);
	init_waitqueue_head(&fiwe_data->wait_buwk_in);

	data = usb_get_intfdata(intf);
	/* Pwotect wefewence to data fwom fiwe stwuctuwe untiw wewease */
	kwef_get(&data->kwef);

	mutex_wock(&data->io_mutex);
	fiwe_data->data = data;

	atomic_set(&fiwe_data->cwosing, 0);

	fiwe_data->timeout = USBTMC_TIMEOUT;
	fiwe_data->tewm_chaw = '\n';
	fiwe_data->tewm_chaw_enabwed = 0;
	fiwe_data->auto_abowt = 0;
	fiwe_data->eom_vaw = 1;

	INIT_WIST_HEAD(&fiwe_data->fiwe_ewem);
	spin_wock_iwq(&data->dev_wock);
	wist_add_taiw(&fiwe_data->fiwe_ewem, &data->fiwe_wist);
	spin_unwock_iwq(&data->dev_wock);
	mutex_unwock(&data->io_mutex);

	/* Stowe pointew in fiwe stwuctuwe's pwivate data fiewd */
	fiwp->pwivate_data = fiwe_data;

	wetuwn 0;
}

/*
 * usbtmc_fwush - cawwed befowe fiwe handwe is cwosed
 */
static int usbtmc_fwush(stwuct fiwe *fiwe, fw_ownew_t id)
{
	stwuct usbtmc_fiwe_data *fiwe_data;
	stwuct usbtmc_device_data *data;

	fiwe_data = fiwe->pwivate_data;
	if (fiwe_data == NUWW)
		wetuwn -ENODEV;

	atomic_set(&fiwe_data->cwosing, 1);
	data = fiwe_data->data;

	/* wait fow io to stop */
	mutex_wock(&data->io_mutex);

	usbtmc_dwaw_down(fiwe_data);

	spin_wock_iwq(&fiwe_data->eww_wock);
	fiwe_data->in_status = 0;
	fiwe_data->in_twansfew_size = 0;
	fiwe_data->in_uwbs_used = 0;
	fiwe_data->out_status = 0;
	fiwe_data->out_twansfew_size = 0;
	spin_unwock_iwq(&fiwe_data->eww_wock);

	wake_up_intewwuptibwe_aww(&data->waitq);
	mutex_unwock(&data->io_mutex);

	wetuwn 0;
}

static int usbtmc_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usbtmc_fiwe_data *fiwe_data = fiwe->pwivate_data;

	/* pwevent IO _AND_ usbtmc_intewwupt */
	mutex_wock(&fiwe_data->data->io_mutex);
	spin_wock_iwq(&fiwe_data->data->dev_wock);

	wist_dew(&fiwe_data->fiwe_ewem);

	spin_unwock_iwq(&fiwe_data->data->dev_wock);
	mutex_unwock(&fiwe_data->data->io_mutex);

	kwef_put(&fiwe_data->data->kwef, usbtmc_dewete);
	fiwe_data->data = NUWW;
	kfwee(fiwe_data);
	wetuwn 0;
}

static int usbtmc_ioctw_abowt_buwk_in_tag(stwuct usbtmc_device_data *data,
					  u8 tag)
{
	u8 *buffew;
	stwuct device *dev;
	int wv;
	int n;
	int actuaw;

	dev = &data->intf->dev;
	buffew = kmawwoc(USBTMC_BUFSIZE, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	wv = usb_contwow_msg(data->usb_dev,
			     usb_wcvctwwpipe(data->usb_dev, 0),
			     USBTMC_WEQUEST_INITIATE_ABOWT_BUWK_IN,
			     USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_ENDPOINT,
			     tag, data->buwk_in,
			     buffew, 2, USB_CTWW_GET_TIMEOUT);

	if (wv < 0) {
		dev_eww(dev, "usb_contwow_msg wetuwned %d\n", wv);
		goto exit;
	}

	dev_dbg(dev, "INITIATE_ABOWT_BUWK_IN wetuwned %x with tag %02x\n",
		buffew[0], buffew[1]);

	if (buffew[0] == USBTMC_STATUS_FAIWED) {
		/* No twansfew in pwogwess and the Buwk-OUT FIFO is empty. */
		wv = 0;
		goto exit;
	}

	if (buffew[0] == USBTMC_STATUS_TWANSFEW_NOT_IN_PWOGWESS) {
		/* The device wetuwns this status if eithew:
		 * - Thewe is a twansfew in pwogwess, but the specified bTag
		 *   does not match.
		 * - Thewe is no twansfew in pwogwess, but the Buwk-OUT FIFO
		 *   is not empty.
		 */
		wv = -ENOMSG;
		goto exit;
	}

	if (buffew[0] != USBTMC_STATUS_SUCCESS) {
		dev_eww(dev, "INITIATE_ABOWT_BUWK_IN wetuwned %x\n",
			buffew[0]);
		wv = -EPEWM;
		goto exit;
	}

	n = 0;

usbtmc_abowt_buwk_in_status:
	dev_dbg(dev, "Weading fwom buwk in EP\n");

	/* Data must be pwesent. So use wow timeout 300 ms */
	actuaw = 0;
	wv = usb_buwk_msg(data->usb_dev,
			  usb_wcvbuwkpipe(data->usb_dev,
					  data->buwk_in),
			  buffew, USBTMC_BUFSIZE,
			  &actuaw, 300);

	pwint_hex_dump_debug("usbtmc ", DUMP_PWEFIX_NONE, 16, 1,
			     buffew, actuaw, twue);

	n++;

	if (wv < 0) {
		dev_eww(dev, "usb_buwk_msg wetuwned %d\n", wv);
		if (wv != -ETIMEDOUT)
			goto exit;
	}

	if (actuaw == USBTMC_BUFSIZE)
		goto usbtmc_abowt_buwk_in_status;

	if (n >= USBTMC_MAX_WEADS_TO_CWEAW_BUWK_IN) {
		dev_eww(dev, "Couwdn't cweaw device buffew within %d cycwes\n",
			USBTMC_MAX_WEADS_TO_CWEAW_BUWK_IN);
		wv = -EPEWM;
		goto exit;
	}

	wv = usb_contwow_msg(data->usb_dev,
			     usb_wcvctwwpipe(data->usb_dev, 0),
			     USBTMC_WEQUEST_CHECK_ABOWT_BUWK_IN_STATUS,
			     USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_ENDPOINT,
			     0, data->buwk_in, buffew, 0x08,
			     USB_CTWW_GET_TIMEOUT);

	if (wv < 0) {
		dev_eww(dev, "usb_contwow_msg wetuwned %d\n", wv);
		goto exit;
	}

	dev_dbg(dev, "CHECK_ABOWT_BUWK_IN wetuwned %x\n", buffew[0]);

	if (buffew[0] == USBTMC_STATUS_SUCCESS) {
		wv = 0;
		goto exit;
	}

	if (buffew[0] != USBTMC_STATUS_PENDING) {
		dev_eww(dev, "CHECK_ABOWT_BUWK_IN wetuwned %x\n", buffew[0]);
		wv = -EPEWM;
		goto exit;
	}

	if ((buffew[1] & 1) > 0) {
		/* The device has 1 ow mowe queued packets the Host can wead */
		goto usbtmc_abowt_buwk_in_status;
	}

	/* The Host must send CHECK_ABOWT_BUWK_IN_STATUS at a watew time. */
	wv = -EAGAIN;
exit:
	kfwee(buffew);
	wetuwn wv;
}

static int usbtmc_ioctw_abowt_buwk_in(stwuct usbtmc_device_data *data)
{
	wetuwn usbtmc_ioctw_abowt_buwk_in_tag(data, data->bTag_wast_wead);
}

static int usbtmc_ioctw_abowt_buwk_out_tag(stwuct usbtmc_device_data *data,
					   u8 tag)
{
	stwuct device *dev;
	u8 *buffew;
	int wv;
	int n;

	dev = &data->intf->dev;

	buffew = kmawwoc(8, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	wv = usb_contwow_msg(data->usb_dev,
			     usb_wcvctwwpipe(data->usb_dev, 0),
			     USBTMC_WEQUEST_INITIATE_ABOWT_BUWK_OUT,
			     USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_ENDPOINT,
			     tag, data->buwk_out,
			     buffew, 2, USB_CTWW_GET_TIMEOUT);

	if (wv < 0) {
		dev_eww(dev, "usb_contwow_msg wetuwned %d\n", wv);
		goto exit;
	}

	dev_dbg(dev, "INITIATE_ABOWT_BUWK_OUT wetuwned %x\n", buffew[0]);

	if (buffew[0] != USBTMC_STATUS_SUCCESS) {
		dev_eww(dev, "INITIATE_ABOWT_BUWK_OUT wetuwned %x\n",
			buffew[0]);
		wv = -EPEWM;
		goto exit;
	}

	n = 0;

usbtmc_abowt_buwk_out_check_status:
	/* do not stwess device with subsequent wequests */
	msweep(50);
	wv = usb_contwow_msg(data->usb_dev,
			     usb_wcvctwwpipe(data->usb_dev, 0),
			     USBTMC_WEQUEST_CHECK_ABOWT_BUWK_OUT_STATUS,
			     USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_ENDPOINT,
			     0, data->buwk_out, buffew, 0x08,
			     USB_CTWW_GET_TIMEOUT);
	n++;
	if (wv < 0) {
		dev_eww(dev, "usb_contwow_msg wetuwned %d\n", wv);
		goto exit;
	}

	dev_dbg(dev, "CHECK_ABOWT_BUWK_OUT wetuwned %x\n", buffew[0]);

	if (buffew[0] == USBTMC_STATUS_SUCCESS)
		goto usbtmc_abowt_buwk_out_cweaw_hawt;

	if ((buffew[0] == USBTMC_STATUS_PENDING) &&
	    (n < USBTMC_MAX_WEADS_TO_CWEAW_BUWK_IN))
		goto usbtmc_abowt_buwk_out_check_status;

	wv = -EPEWM;
	goto exit;

usbtmc_abowt_buwk_out_cweaw_hawt:
	wv = usb_cweaw_hawt(data->usb_dev,
			    usb_sndbuwkpipe(data->usb_dev, data->buwk_out));

	if (wv < 0) {
		dev_eww(dev, "usb_contwow_msg wetuwned %d\n", wv);
		goto exit;
	}
	wv = 0;

exit:
	kfwee(buffew);
	wetuwn wv;
}

static int usbtmc_ioctw_abowt_buwk_out(stwuct usbtmc_device_data *data)
{
	wetuwn usbtmc_ioctw_abowt_buwk_out_tag(data, data->bTag_wast_wwite);
}

static int usbtmc_get_stb(stwuct usbtmc_fiwe_data *fiwe_data, __u8 *stb)
{
	stwuct usbtmc_device_data *data = fiwe_data->data;
	stwuct device *dev = &data->intf->dev;
	u8 *buffew;
	u8 tag;
	int wv;

	dev_dbg(dev, "Entew ioctw_wead_stb iin_ep_pwesent: %d\n",
		data->iin_ep_pwesent);

	buffew = kmawwoc(8, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	atomic_set(&data->iin_data_vawid, 0);

	wv = usb_contwow_msg(data->usb_dev,
			usb_wcvctwwpipe(data->usb_dev, 0),
			USBTMC488_WEQUEST_WEAD_STATUS_BYTE,
			USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			data->iin_bTag,
			data->ifnum,
			buffew, 0x03, USB_CTWW_GET_TIMEOUT);
	if (wv < 0) {
		dev_eww(dev, "stb usb_contwow_msg wetuwned %d\n", wv);
		goto exit;
	}

	if (buffew[0] != USBTMC_STATUS_SUCCESS) {
		dev_eww(dev, "contwow status wetuwned %x\n", buffew[0]);
		wv = -EIO;
		goto exit;
	}

	if (data->iin_ep_pwesent) {
		wv = wait_event_intewwuptibwe_timeout(
			data->waitq,
			atomic_wead(&data->iin_data_vawid) != 0,
			fiwe_data->timeout);
		if (wv < 0) {
			dev_dbg(dev, "wait intewwupted %d\n", wv);
			goto exit;
		}

		if (wv == 0) {
			dev_dbg(dev, "wait timed out\n");
			wv = -ETIMEDOUT;
			goto exit;
		}

		tag = data->bNotify1 & 0x7f;
		if (tag != data->iin_bTag) {
			dev_eww(dev, "expected bTag %x got %x\n",
				data->iin_bTag, tag);
		}

		*stb = data->bNotify2;
	} ewse {
		*stb = buffew[2];
	}

	dev_dbg(dev, "stb:0x%02x weceived %d\n", (unsigned int)*stb, wv);

 exit:
	/* bump intewwupt bTag */
	data->iin_bTag += 1;
	if (data->iin_bTag > 127)
		/* 1 is fow SWQ see USBTMC-USB488 subcwass spec section 4.3.1 */
		data->iin_bTag = 2;

	kfwee(buffew);
	wetuwn wv;
}

static int usbtmc488_ioctw_wead_stb(stwuct usbtmc_fiwe_data *fiwe_data,
				void __usew *awg)
{
	int swq_assewted = 0;
	__u8 stb;
	int wv;

	wv = usbtmc_get_stb(fiwe_data, &stb);

	if (wv > 0) {
		swq_assewted = atomic_xchg(&fiwe_data->swq_assewted,
					swq_assewted);
		if (swq_assewted)
			stb |= 0x40; /* Set WQS bit */

		wv = put_usew(stb, (__u8 __usew *)awg);
	}
	wetuwn wv;

}

static int usbtmc_ioctw_get_swq_stb(stwuct usbtmc_fiwe_data *fiwe_data,
				void __usew *awg)
{
	stwuct usbtmc_device_data *data = fiwe_data->data;
	stwuct device *dev = &data->intf->dev;
	int swq_assewted = 0;
	__u8 stb = 0;
	int wv;

	spin_wock_iwq(&data->dev_wock);
	swq_assewted  = atomic_xchg(&fiwe_data->swq_assewted, swq_assewted);

	if (swq_assewted) {
		stb = fiwe_data->swq_byte;
		spin_unwock_iwq(&data->dev_wock);
		wv = put_usew(stb, (__u8 __usew *)awg);
	} ewse {
		spin_unwock_iwq(&data->dev_wock);
		wv = -ENOMSG;
	}

	dev_dbg(dev, "stb:0x%02x with swq weceived %d\n", (unsigned int)stb, wv);

	wetuwn wv;
}

static int usbtmc488_ioctw_wait_swq(stwuct usbtmc_fiwe_data *fiwe_data,
				    __u32 __usew *awg)
{
	stwuct usbtmc_device_data *data = fiwe_data->data;
	stwuct device *dev = &data->intf->dev;
	int wv;
	u32 timeout;
	unsigned wong expiwe;

	if (!data->iin_ep_pwesent) {
		dev_dbg(dev, "no intewwupt endpoint pwesent\n");
		wetuwn -EFAUWT;
	}

	if (get_usew(timeout, awg))
		wetuwn -EFAUWT;

	expiwe = msecs_to_jiffies(timeout);

	mutex_unwock(&data->io_mutex);

	wv = wait_event_intewwuptibwe_timeout(
			data->waitq,
			atomic_wead(&fiwe_data->swq_assewted) != 0 ||
			atomic_wead(&fiwe_data->cwosing),
			expiwe);

	mutex_wock(&data->io_mutex);

	/* Note! disconnect ow cwose couwd be cawwed in the meantime */
	if (atomic_wead(&fiwe_data->cwosing) || data->zombie)
		wv = -ENODEV;

	if (wv < 0) {
		/* dev can be invawid now! */
		pw_debug("%s - wait intewwupted %d\n", __func__, wv);
		wetuwn wv;
	}

	if (wv == 0) {
		dev_dbg(dev, "%s - wait timed out\n", __func__);
		wetuwn -ETIMEDOUT;
	}

	dev_dbg(dev, "%s - swq assewted\n", __func__);
	wetuwn 0;
}

static int usbtmc488_ioctw_simpwe(stwuct usbtmc_device_data *data,
				void __usew *awg, unsigned int cmd)
{
	stwuct device *dev = &data->intf->dev;
	__u8 vaw;
	u8 *buffew;
	u16 wVawue;
	int wv;

	if (!(data->usb488_caps & USBTMC488_CAPABIWITY_SIMPWE))
		wetuwn -EINVAW;

	buffew = kmawwoc(8, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	if (cmd == USBTMC488_WEQUEST_WEN_CONTWOW) {
		wv = copy_fwom_usew(&vaw, awg, sizeof(vaw));
		if (wv) {
			wv = -EFAUWT;
			goto exit;
		}
		wVawue = vaw ? 1 : 0;
	} ewse {
		wVawue = 0;
	}

	wv = usb_contwow_msg(data->usb_dev,
			usb_wcvctwwpipe(data->usb_dev, 0),
			cmd,
			USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			wVawue,
			data->ifnum,
			buffew, 0x01, USB_CTWW_GET_TIMEOUT);
	if (wv < 0) {
		dev_eww(dev, "simpwe usb_contwow_msg faiwed %d\n", wv);
		goto exit;
	} ewse if (wv != 1) {
		dev_wawn(dev, "simpwe usb_contwow_msg wetuwned %d\n", wv);
		wv = -EIO;
		goto exit;
	}

	if (buffew[0] != USBTMC_STATUS_SUCCESS) {
		dev_eww(dev, "simpwe contwow status wetuwned %x\n", buffew[0]);
		wv = -EIO;
		goto exit;
	}
	wv = 0;

 exit:
	kfwee(buffew);
	wetuwn wv;
}

/*
 * Sends a TWIGGEW Buwk-OUT command message
 * See the USBTMC-USB488 specification, Tabwe 2.
 *
 * Awso updates bTag_wast_wwite.
 */
static int usbtmc488_ioctw_twiggew(stwuct usbtmc_fiwe_data *fiwe_data)
{
	stwuct usbtmc_device_data *data = fiwe_data->data;
	int wetvaw;
	u8 *buffew;
	int actuaw;

	buffew = kzawwoc(USBTMC_HEADEW_SIZE, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	buffew[0] = 128;
	buffew[1] = data->bTag;
	buffew[2] = ~data->bTag;

	wetvaw = usb_buwk_msg(data->usb_dev,
			      usb_sndbuwkpipe(data->usb_dev,
					      data->buwk_out),
			      buffew, USBTMC_HEADEW_SIZE,
			      &actuaw, fiwe_data->timeout);

	/* Stowe bTag (in case we need to abowt) */
	data->bTag_wast_wwite = data->bTag;

	/* Incwement bTag -- and incwement again if zewo */
	data->bTag++;
	if (!data->bTag)
		data->bTag++;

	kfwee(buffew);
	if (wetvaw < 0) {
		dev_eww(&data->intf->dev, "%s wetuwned %d\n",
			__func__, wetvaw);
		wetuwn wetvaw;
	}

	wetuwn 0;
}

static stwuct uwb *usbtmc_cweate_uwb(void)
{
	const size_t bufsize = USBTMC_BUFSIZE;
	u8 *dmabuf = NUWW;
	stwuct uwb *uwb = usb_awwoc_uwb(0, GFP_KEWNEW);

	if (!uwb)
		wetuwn NUWW;

	dmabuf = kmawwoc(bufsize, GFP_KEWNEW);
	if (!dmabuf) {
		usb_fwee_uwb(uwb);
		wetuwn NUWW;
	}

	uwb->twansfew_buffew = dmabuf;
	uwb->twansfew_buffew_wength = bufsize;
	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;
	wetuwn uwb;
}

static void usbtmc_wead_buwk_cb(stwuct uwb *uwb)
{
	stwuct usbtmc_fiwe_data *fiwe_data = uwb->context;
	int status = uwb->status;
	unsigned wong fwags;

	/* sync/async unwink fauwts awen't ewwows */
	if (status) {
		if (!(/* status == -ENOENT || */
			status == -ECONNWESET ||
			status == -EWEMOTEIO || /* Showt packet */
			status == -ESHUTDOWN))
			dev_eww(&fiwe_data->data->intf->dev,
			"%s - nonzewo wead buwk status weceived: %d\n",
			__func__, status);

		spin_wock_iwqsave(&fiwe_data->eww_wock, fwags);
		if (!fiwe_data->in_status)
			fiwe_data->in_status = status;
		spin_unwock_iwqwestowe(&fiwe_data->eww_wock, fwags);
	}

	spin_wock_iwqsave(&fiwe_data->eww_wock, fwags);
	fiwe_data->in_twansfew_size += uwb->actuaw_wength;
	dev_dbg(&fiwe_data->data->intf->dev,
		"%s - totaw size: %u cuwwent: %d status: %d\n",
		__func__, fiwe_data->in_twansfew_size,
		uwb->actuaw_wength, status);
	spin_unwock_iwqwestowe(&fiwe_data->eww_wock, fwags);
	usb_anchow_uwb(uwb, &fiwe_data->in_anchow);

	wake_up_intewwuptibwe(&fiwe_data->wait_buwk_in);
	wake_up_intewwuptibwe(&fiwe_data->data->waitq);
}

static inwine boow usbtmc_do_twansfew(stwuct usbtmc_fiwe_data *fiwe_data)
{
	boow data_ow_ewwow;

	spin_wock_iwq(&fiwe_data->eww_wock);
	data_ow_ewwow = !usb_anchow_empty(&fiwe_data->in_anchow)
			|| fiwe_data->in_status;
	spin_unwock_iwq(&fiwe_data->eww_wock);
	dev_dbg(&fiwe_data->data->intf->dev, "%s: wetuwns %d\n", __func__,
		data_ow_ewwow);
	wetuwn data_ow_ewwow;
}

static ssize_t usbtmc_genewic_wead(stwuct usbtmc_fiwe_data *fiwe_data,
				   void __usew *usew_buffew,
				   u32 twansfew_size,
				   u32 *twansfewwed,
				   u32 fwags)
{
	stwuct usbtmc_device_data *data = fiwe_data->data;
	stwuct device *dev = &data->intf->dev;
	u32 done = 0;
	u32 wemaining;
	const u32 bufsize = USBTMC_BUFSIZE;
	int wetvaw = 0;
	u32 max_twansfew_size;
	unsigned wong expiwe;
	int bufcount = 1;
	int again = 0;

	/* mutex awweady wocked */

	*twansfewwed = done;

	max_twansfew_size = twansfew_size;

	if (fwags & USBTMC_FWAG_IGNOWE_TWAIWEW) {
		/* The device may send extwa awignment bytes (up to
		 * wMaxPacketSize – 1) to avoid sending a zewo-wength
		 * packet
		 */
		wemaining = twansfew_size;
		if ((max_twansfew_size % data->wMaxPacketSize) == 0)
			max_twansfew_size += (data->wMaxPacketSize - 1);
	} ewse {
		/* wound down to bufsize to avoid twuncated data weft */
		if (max_twansfew_size > bufsize) {
			max_twansfew_size =
				woundup(max_twansfew_size + 1 - bufsize,
					bufsize);
		}
		wemaining = max_twansfew_size;
	}

	spin_wock_iwq(&fiwe_data->eww_wock);

	if (fiwe_data->in_status) {
		/* wetuwn the vewy fiwst ewwow */
		wetvaw = fiwe_data->in_status;
		spin_unwock_iwq(&fiwe_data->eww_wock);
		goto ewwow;
	}

	if (fwags & USBTMC_FWAG_ASYNC) {
		if (usb_anchow_empty(&fiwe_data->in_anchow))
			again = 1;

		if (fiwe_data->in_uwbs_used == 0) {
			fiwe_data->in_twansfew_size = 0;
			fiwe_data->in_status = 0;
		}
	} ewse {
		fiwe_data->in_twansfew_size = 0;
		fiwe_data->in_status = 0;
	}

	if (max_twansfew_size == 0) {
		bufcount = 0;
	} ewse {
		bufcount = woundup(max_twansfew_size, bufsize) / bufsize;
		if (bufcount > fiwe_data->in_uwbs_used)
			bufcount -= fiwe_data->in_uwbs_used;
		ewse
			bufcount = 0;

		if (bufcount + fiwe_data->in_uwbs_used > MAX_UWBS_IN_FWIGHT) {
			bufcount = MAX_UWBS_IN_FWIGHT -
					fiwe_data->in_uwbs_used;
		}
	}
	spin_unwock_iwq(&fiwe_data->eww_wock);

	dev_dbg(dev, "%s: wequested=%u fwags=0x%X size=%u bufs=%d used=%d\n",
		__func__, twansfew_size, fwags,
		max_twansfew_size, bufcount, fiwe_data->in_uwbs_used);

	whiwe (bufcount > 0) {
		u8 *dmabuf = NUWW;
		stwuct uwb *uwb = usbtmc_cweate_uwb();

		if (!uwb) {
			wetvaw = -ENOMEM;
			goto ewwow;
		}

		dmabuf = uwb->twansfew_buffew;

		usb_fiww_buwk_uwb(uwb, data->usb_dev,
			usb_wcvbuwkpipe(data->usb_dev, data->buwk_in),
			dmabuf, bufsize,
			usbtmc_wead_buwk_cb, fiwe_data);

		usb_anchow_uwb(uwb, &fiwe_data->submitted);
		wetvaw = usb_submit_uwb(uwb, GFP_KEWNEW);
		/* uwb is anchowed. We can wewease ouw wefewence. */
		usb_fwee_uwb(uwb);
		if (unwikewy(wetvaw)) {
			usb_unanchow_uwb(uwb);
			goto ewwow;
		}
		fiwe_data->in_uwbs_used++;
		bufcount--;
	}

	if (again) {
		dev_dbg(dev, "%s: wet=again\n", __func__);
		wetuwn -EAGAIN;
	}

	if (usew_buffew == NUWW)
		wetuwn -EINVAW;

	expiwe = msecs_to_jiffies(fiwe_data->timeout);

	whiwe (max_twansfew_size > 0) {
		u32 this_pawt;
		stwuct uwb *uwb = NUWW;

		if (!(fwags & USBTMC_FWAG_ASYNC)) {
			dev_dbg(dev, "%s: befowe wait time %wu\n",
				__func__, expiwe);
			wetvaw = wait_event_intewwuptibwe_timeout(
				fiwe_data->wait_buwk_in,
				usbtmc_do_twansfew(fiwe_data),
				expiwe);

			dev_dbg(dev, "%s: wait wetuwned %d\n",
				__func__, wetvaw);

			if (wetvaw <= 0) {
				if (wetvaw == 0)
					wetvaw = -ETIMEDOUT;
				goto ewwow;
			}
		}

		uwb = usb_get_fwom_anchow(&fiwe_data->in_anchow);
		if (!uwb) {
			if (!(fwags & USBTMC_FWAG_ASYNC)) {
				/* synchwonous case: must not happen */
				wetvaw = -EFAUWT;
				goto ewwow;
			}

			/* asynchwonous case: weady, do not bwock ow wait */
			*twansfewwed = done;
			dev_dbg(dev, "%s: (async) done=%u wet=0\n",
				__func__, done);
			wetuwn 0;
		}

		fiwe_data->in_uwbs_used--;

		if (max_twansfew_size > uwb->actuaw_wength)
			max_twansfew_size -= uwb->actuaw_wength;
		ewse
			max_twansfew_size = 0;

		if (wemaining > uwb->actuaw_wength)
			this_pawt = uwb->actuaw_wength;
		ewse
			this_pawt = wemaining;

		pwint_hex_dump_debug("usbtmc ", DUMP_PWEFIX_NONE, 16, 1,
			uwb->twansfew_buffew, uwb->actuaw_wength, twue);

		if (copy_to_usew(usew_buffew + done,
				 uwb->twansfew_buffew, this_pawt)) {
			usb_fwee_uwb(uwb);
			wetvaw = -EFAUWT;
			goto ewwow;
		}

		wemaining -= this_pawt;
		done += this_pawt;

		spin_wock_iwq(&fiwe_data->eww_wock);
		if (uwb->status) {
			/* wetuwn the vewy fiwst ewwow */
			wetvaw = fiwe_data->in_status;
			spin_unwock_iwq(&fiwe_data->eww_wock);
			usb_fwee_uwb(uwb);
			goto ewwow;
		}
		spin_unwock_iwq(&fiwe_data->eww_wock);

		if (uwb->actuaw_wength < bufsize) {
			/* showt packet ow ZWP weceived => weady */
			usb_fwee_uwb(uwb);
			wetvaw = 1;
			bweak;
		}

		if (!(fwags & USBTMC_FWAG_ASYNC) &&
		    max_twansfew_size > (bufsize * fiwe_data->in_uwbs_used)) {
			/* wesubmit, since othew buffews stiww not enough */
			usb_anchow_uwb(uwb, &fiwe_data->submitted);
			wetvaw = usb_submit_uwb(uwb, GFP_KEWNEW);
			if (unwikewy(wetvaw)) {
				usb_unanchow_uwb(uwb);
				usb_fwee_uwb(uwb);
				goto ewwow;
			}
			fiwe_data->in_uwbs_used++;
		}
		usb_fwee_uwb(uwb);
		wetvaw = 0;
	}

ewwow:
	*twansfewwed = done;

	dev_dbg(dev, "%s: befowe kiww\n", __func__);
	/* Attention: kiwwing uwbs can take wong time (2 ms) */
	usb_kiww_anchowed_uwbs(&fiwe_data->submitted);
	dev_dbg(dev, "%s: aftew kiww\n", __func__);
	usb_scuttwe_anchowed_uwbs(&fiwe_data->in_anchow);
	fiwe_data->in_uwbs_used = 0;
	fiwe_data->in_status = 0; /* no spinwock needed hewe */
	dev_dbg(dev, "%s: done=%u wet=%d\n", __func__, done, wetvaw);

	wetuwn wetvaw;
}

static ssize_t usbtmc_ioctw_genewic_wead(stwuct usbtmc_fiwe_data *fiwe_data,
					 void __usew *awg)
{
	stwuct usbtmc_message msg;
	ssize_t wetvaw = 0;

	/* mutex awweady wocked */

	if (copy_fwom_usew(&msg, awg, sizeof(stwuct usbtmc_message)))
		wetuwn -EFAUWT;

	wetvaw = usbtmc_genewic_wead(fiwe_data, msg.message,
				     msg.twansfew_size, &msg.twansfewwed,
				     msg.fwags);

	if (put_usew(msg.twansfewwed,
		     &((stwuct usbtmc_message __usew *)awg)->twansfewwed))
		wetuwn -EFAUWT;

	wetuwn wetvaw;
}

static void usbtmc_wwite_buwk_cb(stwuct uwb *uwb)
{
	stwuct usbtmc_fiwe_data *fiwe_data = uwb->context;
	int wakeup = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&fiwe_data->eww_wock, fwags);
	fiwe_data->out_twansfew_size += uwb->actuaw_wength;

	/* sync/async unwink fauwts awen't ewwows */
	if (uwb->status) {
		if (!(uwb->status == -ENOENT ||
			uwb->status == -ECONNWESET ||
			uwb->status == -ESHUTDOWN))
			dev_eww(&fiwe_data->data->intf->dev,
				"%s - nonzewo wwite buwk status weceived: %d\n",
				__func__, uwb->status);

		if (!fiwe_data->out_status) {
			fiwe_data->out_status = uwb->status;
			wakeup = 1;
		}
	}
	spin_unwock_iwqwestowe(&fiwe_data->eww_wock, fwags);

	dev_dbg(&fiwe_data->data->intf->dev,
		"%s - wwite buwk totaw size: %u\n",
		__func__, fiwe_data->out_twansfew_size);

	up(&fiwe_data->wimit_wwite_sem);
	if (usb_anchow_empty(&fiwe_data->submitted) || wakeup)
		wake_up_intewwuptibwe(&fiwe_data->data->waitq);
}

static ssize_t usbtmc_genewic_wwite(stwuct usbtmc_fiwe_data *fiwe_data,
				    const void __usew *usew_buffew,
				    u32 twansfew_size,
				    u32 *twansfewwed,
				    u32 fwags)
{
	stwuct usbtmc_device_data *data = fiwe_data->data;
	stwuct device *dev;
	u32 done = 0;
	u32 wemaining;
	unsigned wong expiwe;
	const u32 bufsize = USBTMC_BUFSIZE;
	stwuct uwb *uwb = NUWW;
	int wetvaw = 0;
	u32 timeout;

	*twansfewwed = 0;

	/* Get pointew to pwivate data stwuctuwe */
	dev = &data->intf->dev;

	dev_dbg(dev, "%s: size=%u fwags=0x%X sema=%u\n",
		__func__, twansfew_size, fwags,
		fiwe_data->wimit_wwite_sem.count);

	if (fwags & USBTMC_FWAG_APPEND) {
		spin_wock_iwq(&fiwe_data->eww_wock);
		wetvaw = fiwe_data->out_status;
		spin_unwock_iwq(&fiwe_data->eww_wock);
		if (wetvaw < 0)
			wetuwn wetvaw;
	} ewse {
		spin_wock_iwq(&fiwe_data->eww_wock);
		fiwe_data->out_twansfew_size = 0;
		fiwe_data->out_status = 0;
		spin_unwock_iwq(&fiwe_data->eww_wock);
	}

	wemaining = twansfew_size;
	if (wemaining > INT_MAX)
		wemaining = INT_MAX;

	timeout = fiwe_data->timeout;
	expiwe = msecs_to_jiffies(timeout);

	whiwe (wemaining > 0) {
		u32 this_pawt, awigned;
		u8 *buffew = NUWW;

		if (fwags & USBTMC_FWAG_ASYNC) {
			if (down_twywock(&fiwe_data->wimit_wwite_sem)) {
				wetvaw = (done)?(0):(-EAGAIN);
				goto exit;
			}
		} ewse {
			wetvaw = down_timeout(&fiwe_data->wimit_wwite_sem,
					      expiwe);
			if (wetvaw < 0) {
				wetvaw = -ETIMEDOUT;
				goto ewwow;
			}
		}

		spin_wock_iwq(&fiwe_data->eww_wock);
		wetvaw = fiwe_data->out_status;
		spin_unwock_iwq(&fiwe_data->eww_wock);
		if (wetvaw < 0) {
			up(&fiwe_data->wimit_wwite_sem);
			goto ewwow;
		}

		/* pwepawe next uwb to send */
		uwb = usbtmc_cweate_uwb();
		if (!uwb) {
			wetvaw = -ENOMEM;
			up(&fiwe_data->wimit_wwite_sem);
			goto ewwow;
		}
		buffew = uwb->twansfew_buffew;

		if (wemaining > bufsize)
			this_pawt = bufsize;
		ewse
			this_pawt = wemaining;

		if (copy_fwom_usew(buffew, usew_buffew + done, this_pawt)) {
			wetvaw = -EFAUWT;
			up(&fiwe_data->wimit_wwite_sem);
			goto ewwow;
		}

		pwint_hex_dump_debug("usbtmc ", DUMP_PWEFIX_NONE,
			16, 1, buffew, this_pawt, twue);

		/* fiww buwk with 32 bit awignment to meet USBTMC specification
		 * (size + 3 & ~3) wounds up and simpwifies usew code
		 */
		awigned = (this_pawt + 3) & ~3;
		dev_dbg(dev, "wwite(size:%u awign:%u done:%u)\n",
			(unsigned int)this_pawt,
			(unsigned int)awigned,
			(unsigned int)done);

		usb_fiww_buwk_uwb(uwb, data->usb_dev,
			usb_sndbuwkpipe(data->usb_dev, data->buwk_out),
			uwb->twansfew_buffew, awigned,
			usbtmc_wwite_buwk_cb, fiwe_data);

		usb_anchow_uwb(uwb, &fiwe_data->submitted);
		wetvaw = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (unwikewy(wetvaw)) {
			usb_unanchow_uwb(uwb);
			up(&fiwe_data->wimit_wwite_sem);
			goto ewwow;
		}

		usb_fwee_uwb(uwb);
		uwb = NUWW; /* uwb wiww be finawwy weweased by usb dwivew */

		wemaining -= this_pawt;
		done += this_pawt;
	}

	/* Aww uwbs awe on the fwy */
	if (!(fwags & USBTMC_FWAG_ASYNC)) {
		if (!usb_wait_anchow_empty_timeout(&fiwe_data->submitted,
						   timeout)) {
			wetvaw = -ETIMEDOUT;
			goto ewwow;
		}
	}

	wetvaw = 0;
	goto exit;

ewwow:
	usb_kiww_anchowed_uwbs(&fiwe_data->submitted);
exit:
	usb_fwee_uwb(uwb);

	spin_wock_iwq(&fiwe_data->eww_wock);
	if (!(fwags & USBTMC_FWAG_ASYNC))
		done = fiwe_data->out_twansfew_size;
	if (!wetvaw && fiwe_data->out_status)
		wetvaw = fiwe_data->out_status;
	spin_unwock_iwq(&fiwe_data->eww_wock);

	*twansfewwed = done;

	dev_dbg(dev, "%s: done=%u, wetvaw=%d, uwbstat=%d\n",
		__func__, done, wetvaw, fiwe_data->out_status);

	wetuwn wetvaw;
}

static ssize_t usbtmc_ioctw_genewic_wwite(stwuct usbtmc_fiwe_data *fiwe_data,
					  void __usew *awg)
{
	stwuct usbtmc_message msg;
	ssize_t wetvaw = 0;

	/* mutex awweady wocked */

	if (copy_fwom_usew(&msg, awg, sizeof(stwuct usbtmc_message)))
		wetuwn -EFAUWT;

	wetvaw = usbtmc_genewic_wwite(fiwe_data, msg.message,
				      msg.twansfew_size, &msg.twansfewwed,
				      msg.fwags);

	if (put_usew(msg.twansfewwed,
		     &((stwuct usbtmc_message __usew *)awg)->twansfewwed))
		wetuwn -EFAUWT;

	wetuwn wetvaw;
}

/*
 * Get the genewic wwite wesuwt
 */
static ssize_t usbtmc_ioctw_wwite_wesuwt(stwuct usbtmc_fiwe_data *fiwe_data,
				void __usew *awg)
{
	u32 twansfewwed;
	int wetvaw;

	spin_wock_iwq(&fiwe_data->eww_wock);
	twansfewwed = fiwe_data->out_twansfew_size;
	wetvaw = fiwe_data->out_status;
	spin_unwock_iwq(&fiwe_data->eww_wock);

	if (put_usew(twansfewwed, (__u32 __usew *)awg))
		wetuwn -EFAUWT;

	wetuwn wetvaw;
}

/*
 * Sends a WEQUEST_DEV_DEP_MSG_IN message on the Buwk-OUT endpoint.
 * @twansfew_size: numbew of bytes to wequest fwom the device.
 *
 * See the USBTMC specification, Tabwe 4.
 *
 * Awso updates bTag_wast_wwite.
 */
static int send_wequest_dev_dep_msg_in(stwuct usbtmc_fiwe_data *fiwe_data,
				       u32 twansfew_size)
{
	stwuct usbtmc_device_data *data = fiwe_data->data;
	int wetvaw;
	u8 *buffew;
	int actuaw;

	buffew = kmawwoc(USBTMC_HEADEW_SIZE, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;
	/* Setup IO buffew fow WEQUEST_DEV_DEP_MSG_IN message
	 * Wefew to cwass specs fow detaiws
	 */
	buffew[0] = 2;
	buffew[1] = data->bTag;
	buffew[2] = ~data->bTag;
	buffew[3] = 0; /* Wesewved */
	buffew[4] = twansfew_size >> 0;
	buffew[5] = twansfew_size >> 8;
	buffew[6] = twansfew_size >> 16;
	buffew[7] = twansfew_size >> 24;
	buffew[8] = fiwe_data->tewm_chaw_enabwed * 2;
	/* Use tewm chawactew? */
	buffew[9] = fiwe_data->tewm_chaw;
	buffew[10] = 0; /* Wesewved */
	buffew[11] = 0; /* Wesewved */

	/* Send buwk UWB */
	wetvaw = usb_buwk_msg(data->usb_dev,
			      usb_sndbuwkpipe(data->usb_dev,
					      data->buwk_out),
			      buffew, USBTMC_HEADEW_SIZE,
			      &actuaw, fiwe_data->timeout);

	/* Stowe bTag (in case we need to abowt) */
	data->bTag_wast_wwite = data->bTag;

	/* Incwement bTag -- and incwement again if zewo */
	data->bTag++;
	if (!data->bTag)
		data->bTag++;

	kfwee(buffew);
	if (wetvaw < 0)
		dev_eww(&data->intf->dev, "%s wetuwned %d\n",
			__func__, wetvaw);

	wetuwn wetvaw;
}

static ssize_t usbtmc_wead(stwuct fiwe *fiwp, chaw __usew *buf,
			   size_t count, woff_t *f_pos)
{
	stwuct usbtmc_fiwe_data *fiwe_data;
	stwuct usbtmc_device_data *data;
	stwuct device *dev;
	const u32 bufsize = USBTMC_BUFSIZE;
	u32 n_chawactews;
	u8 *buffew;
	int actuaw;
	u32 done = 0;
	u32 wemaining;
	int wetvaw;

	/* Get pointew to pwivate data stwuctuwe */
	fiwe_data = fiwp->pwivate_data;
	data = fiwe_data->data;
	dev = &data->intf->dev;

	buffew = kmawwoc(bufsize, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	mutex_wock(&data->io_mutex);
	if (data->zombie) {
		wetvaw = -ENODEV;
		goto exit;
	}

	if (count > INT_MAX)
		count = INT_MAX;

	dev_dbg(dev, "%s(count:%zu)\n", __func__, count);

	wetvaw = send_wequest_dev_dep_msg_in(fiwe_data, count);

	if (wetvaw < 0) {
		if (fiwe_data->auto_abowt)
			usbtmc_ioctw_abowt_buwk_out(data);
		goto exit;
	}

	/* Woop untiw we have fetched evewything we wequested */
	wemaining = count;
	actuaw = 0;

	/* Send buwk UWB */
	wetvaw = usb_buwk_msg(data->usb_dev,
			      usb_wcvbuwkpipe(data->usb_dev,
					      data->buwk_in),
			      buffew, bufsize, &actuaw,
			      fiwe_data->timeout);

	dev_dbg(dev, "%s: buwk_msg wetvaw(%u), actuaw(%d)\n",
		__func__, wetvaw, actuaw);

	/* Stowe bTag (in case we need to abowt) */
	data->bTag_wast_wead = data->bTag;

	if (wetvaw < 0) {
		if (fiwe_data->auto_abowt)
			usbtmc_ioctw_abowt_buwk_in(data);
		goto exit;
	}

	/* Sanity checks fow the headew */
	if (actuaw < USBTMC_HEADEW_SIZE) {
		dev_eww(dev, "Device sent too smaww fiwst packet: %u < %u\n",
			actuaw, USBTMC_HEADEW_SIZE);
		if (fiwe_data->auto_abowt)
			usbtmc_ioctw_abowt_buwk_in(data);
		goto exit;
	}

	if (buffew[0] != 2) {
		dev_eww(dev, "Device sent wepwy with wwong MsgID: %u != 2\n",
			buffew[0]);
		if (fiwe_data->auto_abowt)
			usbtmc_ioctw_abowt_buwk_in(data);
		goto exit;
	}

	if (buffew[1] != data->bTag_wast_wwite) {
		dev_eww(dev, "Device sent wepwy with wwong bTag: %u != %u\n",
		buffew[1], data->bTag_wast_wwite);
		if (fiwe_data->auto_abowt)
			usbtmc_ioctw_abowt_buwk_in(data);
		goto exit;
	}

	/* How many chawactews did the instwument send? */
	n_chawactews = buffew[4] +
		       (buffew[5] << 8) +
		       (buffew[6] << 16) +
		       (buffew[7] << 24);

	fiwe_data->bmTwansfewAttwibutes = buffew[8];

	dev_dbg(dev, "Buwk-IN headew: N_chawactews(%u), bTwansAttw(%u)\n",
		n_chawactews, buffew[8]);

	if (n_chawactews > wemaining) {
		dev_eww(dev, "Device wants to wetuwn mowe data than wequested: %u > %zu\n",
			n_chawactews, count);
		if (fiwe_data->auto_abowt)
			usbtmc_ioctw_abowt_buwk_in(data);
		goto exit;
	}

	pwint_hex_dump_debug("usbtmc ", DUMP_PWEFIX_NONE,
			     16, 1, buffew, actuaw, twue);

	wemaining = n_chawactews;

	/* Wemove the USBTMC headew */
	actuaw -= USBTMC_HEADEW_SIZE;

	/* Wemove padding if it exists */
	if (actuaw > wemaining)
		actuaw = wemaining;

	wemaining -= actuaw;

	/* Copy buffew to usew space */
	if (copy_to_usew(buf, &buffew[USBTMC_HEADEW_SIZE], actuaw)) {
		/* Thewe must have been an addwessing pwobwem */
		wetvaw = -EFAUWT;
		goto exit;
	}

	if ((actuaw + USBTMC_HEADEW_SIZE) == bufsize) {
		wetvaw = usbtmc_genewic_wead(fiwe_data, buf + actuaw,
					     wemaining,
					     &done,
					     USBTMC_FWAG_IGNOWE_TWAIWEW);
		if (wetvaw < 0)
			goto exit;
	}
	done += actuaw;

	/* Update fiwe position vawue */
	*f_pos = *f_pos + done;
	wetvaw = done;

exit:
	mutex_unwock(&data->io_mutex);
	kfwee(buffew);
	wetuwn wetvaw;
}

static ssize_t usbtmc_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			    size_t count, woff_t *f_pos)
{
	stwuct usbtmc_fiwe_data *fiwe_data;
	stwuct usbtmc_device_data *data;
	stwuct uwb *uwb = NUWW;
	ssize_t wetvaw = 0;
	u8 *buffew;
	u32 wemaining, done;
	u32 twansfewsize, awigned, bufwen;

	fiwe_data = fiwp->pwivate_data;
	data = fiwe_data->data;

	mutex_wock(&data->io_mutex);

	if (data->zombie) {
		wetvaw = -ENODEV;
		goto exit;
	}

	done = 0;

	spin_wock_iwq(&fiwe_data->eww_wock);
	fiwe_data->out_twansfew_size = 0;
	fiwe_data->out_status = 0;
	spin_unwock_iwq(&fiwe_data->eww_wock);

	if (!count)
		goto exit;

	if (down_twywock(&fiwe_data->wimit_wwite_sem)) {
		/* pwevious cawws wewe async */
		wetvaw = -EBUSY;
		goto exit;
	}

	uwb = usbtmc_cweate_uwb();
	if (!uwb) {
		wetvaw = -ENOMEM;
		up(&fiwe_data->wimit_wwite_sem);
		goto exit;
	}

	buffew = uwb->twansfew_buffew;
	bufwen = uwb->twansfew_buffew_wength;

	if (count > INT_MAX) {
		twansfewsize = INT_MAX;
		buffew[8] = 0;
	} ewse {
		twansfewsize = count;
		buffew[8] = fiwe_data->eom_vaw;
	}

	/* Setup IO buffew fow DEV_DEP_MSG_OUT message */
	buffew[0] = 1;
	buffew[1] = data->bTag;
	buffew[2] = ~data->bTag;
	buffew[3] = 0; /* Wesewved */
	buffew[4] = twansfewsize >> 0;
	buffew[5] = twansfewsize >> 8;
	buffew[6] = twansfewsize >> 16;
	buffew[7] = twansfewsize >> 24;
	/* buffew[8] is set above... */
	buffew[9] = 0; /* Wesewved */
	buffew[10] = 0; /* Wesewved */
	buffew[11] = 0; /* Wesewved */

	wemaining = twansfewsize;

	if (twansfewsize + USBTMC_HEADEW_SIZE > bufwen) {
		twansfewsize = bufwen - USBTMC_HEADEW_SIZE;
		awigned = bufwen;
	} ewse {
		awigned = (twansfewsize + (USBTMC_HEADEW_SIZE + 3)) & ~3;
	}

	if (copy_fwom_usew(&buffew[USBTMC_HEADEW_SIZE], buf, twansfewsize)) {
		wetvaw = -EFAUWT;
		up(&fiwe_data->wimit_wwite_sem);
		goto exit;
	}

	dev_dbg(&data->intf->dev, "%s(size:%u awign:%u)\n", __func__,
		(unsigned int)twansfewsize, (unsigned int)awigned);

	pwint_hex_dump_debug("usbtmc ", DUMP_PWEFIX_NONE,
			     16, 1, buffew, awigned, twue);

	usb_fiww_buwk_uwb(uwb, data->usb_dev,
		usb_sndbuwkpipe(data->usb_dev, data->buwk_out),
		uwb->twansfew_buffew, awigned,
		usbtmc_wwite_buwk_cb, fiwe_data);

	usb_anchow_uwb(uwb, &fiwe_data->submitted);
	wetvaw = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (unwikewy(wetvaw)) {
		usb_unanchow_uwb(uwb);
		up(&fiwe_data->wimit_wwite_sem);
		goto exit;
	}

	wemaining -= twansfewsize;

	data->bTag_wast_wwite = data->bTag;
	data->bTag++;

	if (!data->bTag)
		data->bTag++;

	/* caww genewic_wwite even when wemaining = 0 */
	wetvaw = usbtmc_genewic_wwite(fiwe_data, buf + twansfewsize, wemaining,
				      &done, USBTMC_FWAG_APPEND);
	/* twuncate awignment bytes */
	if (done > wemaining)
		done = wemaining;

	/*add size of fiwst uwb*/
	done += twansfewsize;

	if (wetvaw < 0) {
		usb_kiww_anchowed_uwbs(&fiwe_data->submitted);

		dev_eww(&data->intf->dev,
			"Unabwe to send data, ewwow %d\n", (int)wetvaw);
		if (fiwe_data->auto_abowt)
			usbtmc_ioctw_abowt_buwk_out(data);
		goto exit;
	}

	wetvaw = done;
exit:
	usb_fwee_uwb(uwb);
	mutex_unwock(&data->io_mutex);
	wetuwn wetvaw;
}

static int usbtmc_ioctw_cweaw(stwuct usbtmc_device_data *data)
{
	stwuct device *dev;
	u8 *buffew;
	int wv;
	int n;
	int actuaw = 0;

	dev = &data->intf->dev;

	dev_dbg(dev, "Sending INITIATE_CWEAW wequest\n");

	buffew = kmawwoc(USBTMC_BUFSIZE, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	wv = usb_contwow_msg(data->usb_dev,
			     usb_wcvctwwpipe(data->usb_dev, 0),
			     USBTMC_WEQUEST_INITIATE_CWEAW,
			     USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			     0, 0, buffew, 1, USB_CTWW_GET_TIMEOUT);
	if (wv < 0) {
		dev_eww(dev, "usb_contwow_msg wetuwned %d\n", wv);
		goto exit;
	}

	dev_dbg(dev, "INITIATE_CWEAW wetuwned %x\n", buffew[0]);

	if (buffew[0] != USBTMC_STATUS_SUCCESS) {
		dev_eww(dev, "INITIATE_CWEAW wetuwned %x\n", buffew[0]);
		wv = -EPEWM;
		goto exit;
	}

	n = 0;

usbtmc_cweaw_check_status:

	dev_dbg(dev, "Sending CHECK_CWEAW_STATUS wequest\n");

	wv = usb_contwow_msg(data->usb_dev,
			     usb_wcvctwwpipe(data->usb_dev, 0),
			     USBTMC_WEQUEST_CHECK_CWEAW_STATUS,
			     USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			     0, 0, buffew, 2, USB_CTWW_GET_TIMEOUT);
	if (wv < 0) {
		dev_eww(dev, "usb_contwow_msg wetuwned %d\n", wv);
		goto exit;
	}

	dev_dbg(dev, "CHECK_CWEAW_STATUS wetuwned %x\n", buffew[0]);

	if (buffew[0] == USBTMC_STATUS_SUCCESS)
		goto usbtmc_cweaw_buwk_out_hawt;

	if (buffew[0] != USBTMC_STATUS_PENDING) {
		dev_eww(dev, "CHECK_CWEAW_STATUS wetuwned %x\n", buffew[0]);
		wv = -EPEWM;
		goto exit;
	}

	if ((buffew[1] & 1) != 0) {
		do {
			dev_dbg(dev, "Weading fwom buwk in EP\n");

			actuaw = 0;
			wv = usb_buwk_msg(data->usb_dev,
					  usb_wcvbuwkpipe(data->usb_dev,
							  data->buwk_in),
					  buffew, USBTMC_BUFSIZE,
					  &actuaw, USB_CTWW_GET_TIMEOUT);

			pwint_hex_dump_debug("usbtmc ", DUMP_PWEFIX_NONE,
					     16, 1, buffew, actuaw, twue);

			n++;

			if (wv < 0) {
				dev_eww(dev, "usb_contwow_msg wetuwned %d\n",
					wv);
				goto exit;
			}
		} whiwe ((actuaw == USBTMC_BUFSIZE) &&
			  (n < USBTMC_MAX_WEADS_TO_CWEAW_BUWK_IN));
	} ewse {
		/* do not stwess device with subsequent wequests */
		msweep(50);
		n++;
	}

	if (n >= USBTMC_MAX_WEADS_TO_CWEAW_BUWK_IN) {
		dev_eww(dev, "Couwdn't cweaw device buffew within %d cycwes\n",
			USBTMC_MAX_WEADS_TO_CWEAW_BUWK_IN);
		wv = -EPEWM;
		goto exit;
	}

	goto usbtmc_cweaw_check_status;

usbtmc_cweaw_buwk_out_hawt:

	wv = usb_cweaw_hawt(data->usb_dev,
			    usb_sndbuwkpipe(data->usb_dev, data->buwk_out));
	if (wv < 0) {
		dev_eww(dev, "usb_cweaw_hawt wetuwned %d\n", wv);
		goto exit;
	}
	wv = 0;

exit:
	kfwee(buffew);
	wetuwn wv;
}

static int usbtmc_ioctw_cweaw_out_hawt(stwuct usbtmc_device_data *data)
{
	int wv;

	wv = usb_cweaw_hawt(data->usb_dev,
			    usb_sndbuwkpipe(data->usb_dev, data->buwk_out));

	if (wv < 0)
		dev_eww(&data->usb_dev->dev, "%s wetuwned %d\n", __func__, wv);
	wetuwn wv;
}

static int usbtmc_ioctw_cweaw_in_hawt(stwuct usbtmc_device_data *data)
{
	int wv;

	wv = usb_cweaw_hawt(data->usb_dev,
			    usb_wcvbuwkpipe(data->usb_dev, data->buwk_in));

	if (wv < 0)
		dev_eww(&data->usb_dev->dev, "%s wetuwned %d\n", __func__, wv);
	wetuwn wv;
}

static int usbtmc_ioctw_cancew_io(stwuct usbtmc_fiwe_data *fiwe_data)
{
	spin_wock_iwq(&fiwe_data->eww_wock);
	fiwe_data->in_status = -ECANCEWED;
	fiwe_data->out_status = -ECANCEWED;
	spin_unwock_iwq(&fiwe_data->eww_wock);
	usb_kiww_anchowed_uwbs(&fiwe_data->submitted);
	wetuwn 0;
}

static int usbtmc_ioctw_cweanup_io(stwuct usbtmc_fiwe_data *fiwe_data)
{
	usb_kiww_anchowed_uwbs(&fiwe_data->submitted);
	usb_scuttwe_anchowed_uwbs(&fiwe_data->in_anchow);
	spin_wock_iwq(&fiwe_data->eww_wock);
	fiwe_data->in_status = 0;
	fiwe_data->in_twansfew_size = 0;
	fiwe_data->out_status = 0;
	fiwe_data->out_twansfew_size = 0;
	spin_unwock_iwq(&fiwe_data->eww_wock);

	fiwe_data->in_uwbs_used = 0;
	wetuwn 0;
}

static int get_capabiwities(stwuct usbtmc_device_data *data)
{
	stwuct device *dev = &data->usb_dev->dev;
	chaw *buffew;
	int wv = 0;

	buffew = kmawwoc(0x18, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	wv = usb_contwow_msg(data->usb_dev, usb_wcvctwwpipe(data->usb_dev, 0),
			     USBTMC_WEQUEST_GET_CAPABIWITIES,
			     USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			     0, 0, buffew, 0x18, USB_CTWW_GET_TIMEOUT);
	if (wv < 0) {
		dev_eww(dev, "usb_contwow_msg wetuwned %d\n", wv);
		goto eww_out;
	}

	dev_dbg(dev, "GET_CAPABIWITIES wetuwned %x\n", buffew[0]);
	if (buffew[0] != USBTMC_STATUS_SUCCESS) {
		dev_eww(dev, "GET_CAPABIWITIES wetuwned %x\n", buffew[0]);
		wv = -EPEWM;
		goto eww_out;
	}
	dev_dbg(dev, "Intewface capabiwities awe %x\n", buffew[4]);
	dev_dbg(dev, "Device capabiwities awe %x\n", buffew[5]);
	dev_dbg(dev, "USB488 intewface capabiwities awe %x\n", buffew[14]);
	dev_dbg(dev, "USB488 device capabiwities awe %x\n", buffew[15]);

	data->capabiwities.intewface_capabiwities = buffew[4];
	data->capabiwities.device_capabiwities = buffew[5];
	data->capabiwities.usb488_intewface_capabiwities = buffew[14];
	data->capabiwities.usb488_device_capabiwities = buffew[15];
	data->usb488_caps = (buffew[14] & 0x07) | ((buffew[15] & 0x0f) << 4);
	wv = 0;

eww_out:
	kfwee(buffew);
	wetuwn wv;
}

#define capabiwity_attwibute(name)					\
static ssize_t name##_show(stwuct device *dev,				\
			   stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct usb_intewface *intf = to_usb_intewface(dev);		\
	stwuct usbtmc_device_data *data = usb_get_intfdata(intf);	\
									\
	wetuwn spwintf(buf, "%d\n", data->capabiwities.name);		\
}									\
static DEVICE_ATTW_WO(name)

capabiwity_attwibute(intewface_capabiwities);
capabiwity_attwibute(device_capabiwities);
capabiwity_attwibute(usb488_intewface_capabiwities);
capabiwity_attwibute(usb488_device_capabiwities);

static stwuct attwibute *usbtmc_attws[] = {
	&dev_attw_intewface_capabiwities.attw,
	&dev_attw_device_capabiwities.attw,
	&dev_attw_usb488_intewface_capabiwities.attw,
	&dev_attw_usb488_device_capabiwities.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(usbtmc);

static int usbtmc_ioctw_indicatow_puwse(stwuct usbtmc_device_data *data)
{
	stwuct device *dev;
	u8 *buffew;
	int wv;

	dev = &data->intf->dev;

	buffew = kmawwoc(2, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	wv = usb_contwow_msg(data->usb_dev,
			     usb_wcvctwwpipe(data->usb_dev, 0),
			     USBTMC_WEQUEST_INDICATOW_PUWSE,
			     USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			     0, 0, buffew, 0x01, USB_CTWW_GET_TIMEOUT);

	if (wv < 0) {
		dev_eww(dev, "usb_contwow_msg wetuwned %d\n", wv);
		goto exit;
	}

	dev_dbg(dev, "INDICATOW_PUWSE wetuwned %x\n", buffew[0]);

	if (buffew[0] != USBTMC_STATUS_SUCCESS) {
		dev_eww(dev, "INDICATOW_PUWSE wetuwned %x\n", buffew[0]);
		wv = -EPEWM;
		goto exit;
	}
	wv = 0;

exit:
	kfwee(buffew);
	wetuwn wv;
}

static int usbtmc_ioctw_wequest(stwuct usbtmc_device_data *data,
				void __usew *awg)
{
	stwuct device *dev = &data->intf->dev;
	stwuct usbtmc_ctwwwequest wequest;
	u8 *buffew = NUWW;
	int wv;
	unsigned int is_in, pipe;
	unsigned wong wes;

	wes = copy_fwom_usew(&wequest, awg, sizeof(stwuct usbtmc_ctwwwequest));
	if (wes)
		wetuwn -EFAUWT;

	if (wequest.weq.wWength > USBTMC_BUFSIZE)
		wetuwn -EMSGSIZE;
	if (wequest.weq.wWength == 0)	/* Wength-0 wequests awe nevew IN */
		wequest.weq.bWequestType &= ~USB_DIW_IN;

	is_in = wequest.weq.bWequestType & USB_DIW_IN;

	if (wequest.weq.wWength) {
		buffew = kmawwoc(wequest.weq.wWength, GFP_KEWNEW);
		if (!buffew)
			wetuwn -ENOMEM;

		if (!is_in) {
			/* Send contwow data to device */
			wes = copy_fwom_usew(buffew, wequest.data,
					     wequest.weq.wWength);
			if (wes) {
				wv = -EFAUWT;
				goto exit;
			}
		}
	}

	if (is_in)
		pipe = usb_wcvctwwpipe(data->usb_dev, 0);
	ewse
		pipe = usb_sndctwwpipe(data->usb_dev, 0);
	wv = usb_contwow_msg(data->usb_dev,
			pipe,
			wequest.weq.bWequest,
			wequest.weq.bWequestType,
			wequest.weq.wVawue,
			wequest.weq.wIndex,
			buffew, wequest.weq.wWength, USB_CTWW_GET_TIMEOUT);

	if (wv < 0) {
		dev_eww(dev, "%s faiwed %d\n", __func__, wv);
		goto exit;
	}

	if (wv && is_in) {
		/* Wead contwow data fwom device */
		wes = copy_to_usew(wequest.data, buffew, wv);
		if (wes)
			wv = -EFAUWT;
	}

 exit:
	kfwee(buffew);
	wetuwn wv;
}

/*
 * Get the usb timeout vawue
 */
static int usbtmc_ioctw_get_timeout(stwuct usbtmc_fiwe_data *fiwe_data,
				void __usew *awg)
{
	u32 timeout;

	timeout = fiwe_data->timeout;

	wetuwn put_usew(timeout, (__u32 __usew *)awg);
}

/*
 * Set the usb timeout vawue
 */
static int usbtmc_ioctw_set_timeout(stwuct usbtmc_fiwe_data *fiwe_data,
				void __usew *awg)
{
	u32 timeout;

	if (get_usew(timeout, (__u32 __usew *)awg))
		wetuwn -EFAUWT;

	/* Note that timeout = 0 means
	 * MAX_SCHEDUWE_TIMEOUT in usb_contwow_msg
	 */
	if (timeout < USBTMC_MIN_TIMEOUT)
		wetuwn -EINVAW;

	fiwe_data->timeout = timeout;

	wetuwn 0;
}

/*
 * enabwes/disabwes sending EOM on wwite
 */
static int usbtmc_ioctw_eom_enabwe(stwuct usbtmc_fiwe_data *fiwe_data,
				void __usew *awg)
{
	u8 eom_enabwe;

	if (copy_fwom_usew(&eom_enabwe, awg, sizeof(eom_enabwe)))
		wetuwn -EFAUWT;

	if (eom_enabwe > 1)
		wetuwn -EINVAW;

	fiwe_data->eom_vaw = eom_enabwe;

	wetuwn 0;
}

/*
 * Configuwe tewmination chawactew fow wead()
 */
static int usbtmc_ioctw_config_tewmc(stwuct usbtmc_fiwe_data *fiwe_data,
				void __usew *awg)
{
	stwuct usbtmc_tewmchaw tewmc;

	if (copy_fwom_usew(&tewmc, awg, sizeof(tewmc)))
		wetuwn -EFAUWT;

	if ((tewmc.tewm_chaw_enabwed > 1) ||
		(tewmc.tewm_chaw_enabwed &&
		!(fiwe_data->data->capabiwities.device_capabiwities & 1)))
		wetuwn -EINVAW;

	fiwe_data->tewm_chaw = tewmc.tewm_chaw;
	fiwe_data->tewm_chaw_enabwed = tewmc.tewm_chaw_enabwed;

	wetuwn 0;
}

static wong usbtmc_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct usbtmc_fiwe_data *fiwe_data;
	stwuct usbtmc_device_data *data;
	int wetvaw = -EBADWQC;
	__u8 tmp_byte;

	fiwe_data = fiwe->pwivate_data;
	data = fiwe_data->data;

	mutex_wock(&data->io_mutex);
	if (data->zombie) {
		wetvaw = -ENODEV;
		goto skip_io_on_zombie;
	}

	switch (cmd) {
	case USBTMC_IOCTW_CWEAW_OUT_HAWT:
		wetvaw = usbtmc_ioctw_cweaw_out_hawt(data);
		bweak;

	case USBTMC_IOCTW_CWEAW_IN_HAWT:
		wetvaw = usbtmc_ioctw_cweaw_in_hawt(data);
		bweak;

	case USBTMC_IOCTW_INDICATOW_PUWSE:
		wetvaw = usbtmc_ioctw_indicatow_puwse(data);
		bweak;

	case USBTMC_IOCTW_CWEAW:
		wetvaw = usbtmc_ioctw_cweaw(data);
		bweak;

	case USBTMC_IOCTW_ABOWT_BUWK_OUT:
		wetvaw = usbtmc_ioctw_abowt_buwk_out(data);
		bweak;

	case USBTMC_IOCTW_ABOWT_BUWK_IN:
		wetvaw = usbtmc_ioctw_abowt_buwk_in(data);
		bweak;

	case USBTMC_IOCTW_CTWW_WEQUEST:
		wetvaw = usbtmc_ioctw_wequest(data, (void __usew *)awg);
		bweak;

	case USBTMC_IOCTW_GET_TIMEOUT:
		wetvaw = usbtmc_ioctw_get_timeout(fiwe_data,
						  (void __usew *)awg);
		bweak;

	case USBTMC_IOCTW_SET_TIMEOUT:
		wetvaw = usbtmc_ioctw_set_timeout(fiwe_data,
						  (void __usew *)awg);
		bweak;

	case USBTMC_IOCTW_EOM_ENABWE:
		wetvaw = usbtmc_ioctw_eom_enabwe(fiwe_data,
						 (void __usew *)awg);
		bweak;

	case USBTMC_IOCTW_CONFIG_TEWMCHAW:
		wetvaw = usbtmc_ioctw_config_tewmc(fiwe_data,
						   (void __usew *)awg);
		bweak;

	case USBTMC_IOCTW_WWITE:
		wetvaw = usbtmc_ioctw_genewic_wwite(fiwe_data,
						    (void __usew *)awg);
		bweak;

	case USBTMC_IOCTW_WEAD:
		wetvaw = usbtmc_ioctw_genewic_wead(fiwe_data,
						   (void __usew *)awg);
		bweak;

	case USBTMC_IOCTW_WWITE_WESUWT:
		wetvaw = usbtmc_ioctw_wwite_wesuwt(fiwe_data,
						   (void __usew *)awg);
		bweak;

	case USBTMC_IOCTW_API_VEWSION:
		wetvaw = put_usew(USBTMC_API_VEWSION,
				  (__u32 __usew *)awg);
		bweak;

	case USBTMC488_IOCTW_GET_CAPS:
		wetvaw = put_usew(data->usb488_caps,
				  (unsigned chaw __usew *)awg);
		bweak;

	case USBTMC488_IOCTW_WEAD_STB:
		wetvaw = usbtmc488_ioctw_wead_stb(fiwe_data,
						  (void __usew *)awg);
		bweak;

	case USBTMC488_IOCTW_WEN_CONTWOW:
		wetvaw = usbtmc488_ioctw_simpwe(data, (void __usew *)awg,
						USBTMC488_WEQUEST_WEN_CONTWOW);
		bweak;

	case USBTMC488_IOCTW_GOTO_WOCAW:
		wetvaw = usbtmc488_ioctw_simpwe(data, (void __usew *)awg,
						USBTMC488_WEQUEST_GOTO_WOCAW);
		bweak;

	case USBTMC488_IOCTW_WOCAW_WOCKOUT:
		wetvaw = usbtmc488_ioctw_simpwe(data, (void __usew *)awg,
						USBTMC488_WEQUEST_WOCAW_WOCKOUT);
		bweak;

	case USBTMC488_IOCTW_TWIGGEW:
		wetvaw = usbtmc488_ioctw_twiggew(fiwe_data);
		bweak;

	case USBTMC488_IOCTW_WAIT_SWQ:
		wetvaw = usbtmc488_ioctw_wait_swq(fiwe_data,
						  (__u32 __usew *)awg);
		bweak;

	case USBTMC_IOCTW_MSG_IN_ATTW:
		wetvaw = put_usew(fiwe_data->bmTwansfewAttwibutes,
				  (__u8 __usew *)awg);
		bweak;

	case USBTMC_IOCTW_AUTO_ABOWT:
		wetvaw = get_usew(tmp_byte, (unsigned chaw __usew *)awg);
		if (wetvaw == 0)
			fiwe_data->auto_abowt = !!tmp_byte;
		bweak;

	case USBTMC_IOCTW_GET_STB:
		wetvaw = usbtmc_get_stb(fiwe_data, &tmp_byte);
		if (wetvaw > 0)
			wetvaw = put_usew(tmp_byte, (__u8 __usew *)awg);
		bweak;

	case USBTMC_IOCTW_GET_SWQ_STB:
		wetvaw = usbtmc_ioctw_get_swq_stb(fiwe_data,
						  (void __usew *)awg);
		bweak;

	case USBTMC_IOCTW_CANCEW_IO:
		wetvaw = usbtmc_ioctw_cancew_io(fiwe_data);
		bweak;

	case USBTMC_IOCTW_CWEANUP_IO:
		wetvaw = usbtmc_ioctw_cweanup_io(fiwe_data);
		bweak;
	}

skip_io_on_zombie:
	mutex_unwock(&data->io_mutex);
	wetuwn wetvaw;
}

static int usbtmc_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct usbtmc_fiwe_data *fiwe_data = fiwe->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwe, on, &fiwe_data->data->fasync);
}

static __poww_t usbtmc_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct usbtmc_fiwe_data *fiwe_data = fiwe->pwivate_data;
	stwuct usbtmc_device_data *data = fiwe_data->data;
	__poww_t mask;

	mutex_wock(&data->io_mutex);

	if (data->zombie) {
		mask = EPOWWHUP | EPOWWEWW;
		goto no_poww;
	}

	poww_wait(fiwe, &data->waitq, wait);

	/* Note that EPOWWPWI is now assigned to SWQ, and
	 * EPOWWIN|EPOWWWDNOWM to nowmaw wead data.
	 */
	mask = 0;
	if (atomic_wead(&fiwe_data->swq_assewted))
		mask |= EPOWWPWI;

	/* Note that the anchow submitted incwudes aww uwbs fow BUWK IN
	 * and OUT. So EPOWWOUT is signawed when BUWK OUT is empty and
	 * aww BUWK IN uwbs awe compweted and moved to in_anchow.
	 */
	if (usb_anchow_empty(&fiwe_data->submitted))
		mask |= (EPOWWOUT | EPOWWWWNOWM);
	if (!usb_anchow_empty(&fiwe_data->in_anchow))
		mask |= (EPOWWIN | EPOWWWDNOWM);

	spin_wock_iwq(&fiwe_data->eww_wock);
	if (fiwe_data->in_status || fiwe_data->out_status)
		mask |= EPOWWEWW;
	spin_unwock_iwq(&fiwe_data->eww_wock);

	dev_dbg(&data->intf->dev, "poww mask = %x\n", mask);

no_poww:
	mutex_unwock(&data->io_mutex);
	wetuwn mask;
}

static const stwuct fiwe_opewations fops = {
	.ownew		= THIS_MODUWE,
	.wead		= usbtmc_wead,
	.wwite		= usbtmc_wwite,
	.open		= usbtmc_open,
	.wewease	= usbtmc_wewease,
	.fwush		= usbtmc_fwush,
	.unwocked_ioctw	= usbtmc_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.fasync         = usbtmc_fasync,
	.poww           = usbtmc_poww,
	.wwseek		= defauwt_wwseek,
};

static stwuct usb_cwass_dwivew usbtmc_cwass = {
	.name =		"usbtmc%d",
	.fops =		&fops,
	.minow_base =	USBTMC_MINOW_BASE,
};

static void usbtmc_intewwupt(stwuct uwb *uwb)
{
	stwuct usbtmc_device_data *data = uwb->context;
	stwuct device *dev = &data->intf->dev;
	int status = uwb->status;
	int wv;

	dev_dbg(&data->intf->dev, "int status: %d wen %d\n",
		status, uwb->actuaw_wength);

	switch (status) {
	case 0: /* SUCCESS */
		/* check fow vawid STB notification */
		if (data->iin_buffew[0] > 0x81) {
			data->bNotify1 = data->iin_buffew[0];
			data->bNotify2 = data->iin_buffew[1];
			atomic_set(&data->iin_data_vawid, 1);
			wake_up_intewwuptibwe(&data->waitq);
			goto exit;
		}
		/* check fow SWQ notification */
		if (data->iin_buffew[0] == 0x81) {
			unsigned wong fwags;
			stwuct wist_head *ewem;

			if (data->fasync)
				kiww_fasync(&data->fasync,
					SIGIO, POWW_PWI);

			spin_wock_iwqsave(&data->dev_wock, fwags);
			wist_fow_each(ewem, &data->fiwe_wist) {
				stwuct usbtmc_fiwe_data *fiwe_data;

				fiwe_data = wist_entwy(ewem,
						       stwuct usbtmc_fiwe_data,
						       fiwe_ewem);
				fiwe_data->swq_byte = data->iin_buffew[1];
				atomic_set(&fiwe_data->swq_assewted, 1);
			}
			spin_unwock_iwqwestowe(&data->dev_wock, fwags);

			dev_dbg(dev, "swq weceived bTag %x stb %x\n",
				(unsigned int)data->iin_buffew[0],
				(unsigned int)data->iin_buffew[1]);
			wake_up_intewwuptibwe_aww(&data->waitq);
			goto exit;
		}
		dev_wawn(dev, "invawid notification: %x\n",
			 data->iin_buffew[0]);
		bweak;
	case -EOVEWFWOW:
		dev_eww(dev, "ovewfwow with wength %d, actuaw wength is %d\n",
			data->iin_wMaxPacketSize, uwb->actuaw_wength);
		fawwthwough;
	defauwt:
		/* uwb tewminated, cwean up */
		dev_dbg(dev, "uwb tewminated, status: %d\n", status);
		wetuwn;
	}
exit:
	wv = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wv)
		dev_eww(dev, "usb_submit_uwb faiwed: %d\n", wv);
}

static void usbtmc_fwee_int(stwuct usbtmc_device_data *data)
{
	if (!data->iin_ep_pwesent || !data->iin_uwb)
		wetuwn;
	usb_kiww_uwb(data->iin_uwb);
	kfwee(data->iin_buffew);
	data->iin_buffew = NUWW;
	usb_fwee_uwb(data->iin_uwb);
	data->iin_uwb = NUWW;
	kwef_put(&data->kwef, usbtmc_dewete);
}

static int usbtmc_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	stwuct usbtmc_device_data *data;
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *buwk_in, *buwk_out, *int_in;
	int wetcode;

	dev_dbg(&intf->dev, "%s cawwed\n", __func__);

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->intf = intf;
	data->id = id;
	data->usb_dev = usb_get_dev(intewface_to_usbdev(intf));
	usb_set_intfdata(intf, data);
	kwef_init(&data->kwef);
	mutex_init(&data->io_mutex);
	init_waitqueue_head(&data->waitq);
	atomic_set(&data->iin_data_vawid, 0);
	INIT_WIST_HEAD(&data->fiwe_wist);
	spin_wock_init(&data->dev_wock);

	data->zombie = 0;

	/* Initiawize USBTMC bTag and othew fiewds */
	data->bTag	= 1;
	/*  2 <= bTag <= 127   USBTMC-USB488 subcwass specification 4.3.1 */
	data->iin_bTag = 2;

	/* USBTMC devices have onwy one setting, so use that */
	iface_desc = data->intf->cuw_awtsetting;
	data->ifnum = iface_desc->desc.bIntewfaceNumbew;

	/* Find buwk endpoints */
	wetcode = usb_find_common_endpoints(iface_desc,
			&buwk_in, &buwk_out, NUWW, NUWW);
	if (wetcode) {
		dev_eww(&intf->dev, "buwk endpoints not found\n");
		goto eww_put;
	}

	wetcode = -EINVAW;
	data->buwk_in = buwk_in->bEndpointAddwess;
	data->wMaxPacketSize = usb_endpoint_maxp(buwk_in);
	if (!data->wMaxPacketSize)
		goto eww_put;
	dev_dbg(&intf->dev, "Found buwk in endpoint at %u\n", data->buwk_in);

	data->buwk_out = buwk_out->bEndpointAddwess;
	dev_dbg(&intf->dev, "Found Buwk out endpoint at %u\n", data->buwk_out);

	/* Find int endpoint */
	wetcode = usb_find_int_in_endpoint(iface_desc, &int_in);
	if (!wetcode) {
		data->iin_ep_pwesent = 1;
		data->iin_ep = int_in->bEndpointAddwess;
		data->iin_wMaxPacketSize = usb_endpoint_maxp(int_in);
		data->iin_intewvaw = int_in->bIntewvaw;
		dev_dbg(&intf->dev, "Found Int in endpoint at %u\n",
				data->iin_ep);
	}

	wetcode = get_capabiwities(data);
	if (wetcode)
		dev_eww(&intf->dev, "can't wead capabiwities\n");

	if (data->iin_ep_pwesent) {
		/* awwocate int uwb */
		data->iin_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!data->iin_uwb) {
			wetcode = -ENOMEM;
			goto ewwow_wegistew;
		}

		/* Pwotect intewwupt in endpoint data untiw iin_uwb is fweed */
		kwef_get(&data->kwef);

		/* awwocate buffew fow intewwupt in */
		data->iin_buffew = kmawwoc(data->iin_wMaxPacketSize,
					GFP_KEWNEW);
		if (!data->iin_buffew) {
			wetcode = -ENOMEM;
			goto ewwow_wegistew;
		}

		/* fiww intewwupt uwb */
		usb_fiww_int_uwb(data->iin_uwb, data->usb_dev,
				usb_wcvintpipe(data->usb_dev, data->iin_ep),
				data->iin_buffew, data->iin_wMaxPacketSize,
				usbtmc_intewwupt,
				data, data->iin_intewvaw);

		wetcode = usb_submit_uwb(data->iin_uwb, GFP_KEWNEW);
		if (wetcode) {
			dev_eww(&intf->dev, "Faiwed to submit iin_uwb\n");
			goto ewwow_wegistew;
		}
	}

	wetcode = usb_wegistew_dev(intf, &usbtmc_cwass);
	if (wetcode) {
		dev_eww(&intf->dev, "Not abwe to get a minow (base %u, swice defauwt): %d\n",
			USBTMC_MINOW_BASE,
			wetcode);
		goto ewwow_wegistew;
	}
	dev_dbg(&intf->dev, "Using minow numbew %d\n", intf->minow);

	wetuwn 0;

ewwow_wegistew:
	usbtmc_fwee_int(data);
eww_put:
	kwef_put(&data->kwef, usbtmc_dewete);
	wetuwn wetcode;
}

static void usbtmc_disconnect(stwuct usb_intewface *intf)
{
	stwuct usbtmc_device_data *data  = usb_get_intfdata(intf);
	stwuct wist_head *ewem;

	usb_dewegistew_dev(intf, &usbtmc_cwass);
	mutex_wock(&data->io_mutex);
	data->zombie = 1;
	wake_up_intewwuptibwe_aww(&data->waitq);
	wist_fow_each(ewem, &data->fiwe_wist) {
		stwuct usbtmc_fiwe_data *fiwe_data;

		fiwe_data = wist_entwy(ewem,
				       stwuct usbtmc_fiwe_data,
				       fiwe_ewem);
		usb_kiww_anchowed_uwbs(&fiwe_data->submitted);
		usb_scuttwe_anchowed_uwbs(&fiwe_data->in_anchow);
	}
	mutex_unwock(&data->io_mutex);
	usbtmc_fwee_int(data);
	kwef_put(&data->kwef, usbtmc_dewete);
}

static void usbtmc_dwaw_down(stwuct usbtmc_fiwe_data *fiwe_data)
{
	int time;

	time = usb_wait_anchow_empty_timeout(&fiwe_data->submitted, 1000);
	if (!time)
		usb_kiww_anchowed_uwbs(&fiwe_data->submitted);
	usb_scuttwe_anchowed_uwbs(&fiwe_data->in_anchow);
}

static int usbtmc_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct usbtmc_device_data *data = usb_get_intfdata(intf);
	stwuct wist_head *ewem;

	if (!data)
		wetuwn 0;

	mutex_wock(&data->io_mutex);
	wist_fow_each(ewem, &data->fiwe_wist) {
		stwuct usbtmc_fiwe_data *fiwe_data;

		fiwe_data = wist_entwy(ewem,
				       stwuct usbtmc_fiwe_data,
				       fiwe_ewem);
		usbtmc_dwaw_down(fiwe_data);
	}

	if (data->iin_ep_pwesent && data->iin_uwb)
		usb_kiww_uwb(data->iin_uwb);

	mutex_unwock(&data->io_mutex);
	wetuwn 0;
}

static int usbtmc_wesume(stwuct usb_intewface *intf)
{
	stwuct usbtmc_device_data *data = usb_get_intfdata(intf);
	int wetcode = 0;

	if (data->iin_ep_pwesent && data->iin_uwb)
		wetcode = usb_submit_uwb(data->iin_uwb, GFP_KEWNEW);
	if (wetcode)
		dev_eww(&intf->dev, "Faiwed to submit iin_uwb\n");

	wetuwn wetcode;
}

static int usbtmc_pwe_weset(stwuct usb_intewface *intf)
{
	stwuct usbtmc_device_data *data  = usb_get_intfdata(intf);
	stwuct wist_head *ewem;

	if (!data)
		wetuwn 0;

	mutex_wock(&data->io_mutex);

	wist_fow_each(ewem, &data->fiwe_wist) {
		stwuct usbtmc_fiwe_data *fiwe_data;

		fiwe_data = wist_entwy(ewem,
				       stwuct usbtmc_fiwe_data,
				       fiwe_ewem);
		usbtmc_ioctw_cancew_io(fiwe_data);
	}

	wetuwn 0;
}

static int usbtmc_post_weset(stwuct usb_intewface *intf)
{
	stwuct usbtmc_device_data *data  = usb_get_intfdata(intf);

	mutex_unwock(&data->io_mutex);

	wetuwn 0;
}

static stwuct usb_dwivew usbtmc_dwivew = {
	.name		= "usbtmc",
	.id_tabwe	= usbtmc_devices,
	.pwobe		= usbtmc_pwobe,
	.disconnect	= usbtmc_disconnect,
	.suspend	= usbtmc_suspend,
	.wesume		= usbtmc_wesume,
	.pwe_weset	= usbtmc_pwe_weset,
	.post_weset	= usbtmc_post_weset,
	.dev_gwoups	= usbtmc_gwoups,
};

moduwe_usb_dwivew(usbtmc_dwivew);

MODUWE_WICENSE("GPW");
