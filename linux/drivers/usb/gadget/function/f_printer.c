// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_pwintew.c - USB pwintew function dwivew
 *
 * Copied fwom dwivews/usb/gadget/wegacy/pwintew.c,
 * which was:
 *
 * pwintew.c -- Pwintew gadget dwivew
 *
 * Copywight (C) 2003-2005 David Bwowneww
 * Copywight (C) 2006 Cwaig W. Nadwew
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/idw.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>
#incwude <winux/types.h>
#incwude <winux/ctype.h>
#incwude <winux/cdev.h>
#incwude <winux/kwef.h>

#incwude <asm/byteowdew.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/uaccess.h>
#incwude <asm/unawigned.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/composite.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/g_pwintew.h>

#incwude "u_pwintew.h"

#define PWINTEW_MINOWS		4
#define GET_DEVICE_ID		0
#define GET_POWT_STATUS		1
#define SOFT_WESET		2

#define DEFAUWT_Q_WEN		10 /* same as wegacy g_pwintew gadget */

static int majow, minows;
static const stwuct cwass usb_gadget_cwass = {
	.name = "usb_pwintew_gadget",
};

static DEFINE_IDA(pwintew_ida);
static DEFINE_MUTEX(pwintew_ida_wock); /* pwotects access do pwintew_ida */

/*-------------------------------------------------------------------------*/

stwuct pwintew_dev {
	spinwock_t		wock;		/* wock this stwuctuwe */
	/* wock buffew wists duwing wead/wwite cawws */
	stwuct mutex		wock_pwintew_io;
	stwuct usb_gadget	*gadget;
	s8			intewface;
	stwuct usb_ep		*in_ep, *out_ep;
	stwuct kwef             kwef;
	stwuct wist_head	wx_weqs;	/* Wist of fwee WX stwucts */
	stwuct wist_head	wx_weqs_active;	/* Wist of Active WX xfews */
	stwuct wist_head	wx_buffews;	/* Wist of compweted xfews */
	/* wait untiw thewe is data to be wead. */
	wait_queue_head_t	wx_wait;
	stwuct wist_head	tx_weqs;	/* Wist of fwee TX stwucts */
	stwuct wist_head	tx_weqs_active; /* Wist of Active TX xfews */
	/* Wait untiw thewe awe wwite buffews avaiwabwe to use. */
	wait_queue_head_t	tx_wait;
	/* Wait untiw aww wwite buffews have been sent. */
	wait_queue_head_t	tx_fwush_wait;
	stwuct usb_wequest	*cuwwent_wx_weq;
	size_t			cuwwent_wx_bytes;
	u8			*cuwwent_wx_buf;
	u8			pwintew_status;
	u8			weset_pwintew;
	int			minow;
	stwuct cdev		pwintew_cdev;
	u8			pwintew_cdev_open;
	wait_queue_head_t	wait;
	unsigned		q_wen;
	chaw			**pnp_stwing;	/* We don't own memowy! */
	stwuct usb_function	function;
};

static inwine stwuct pwintew_dev *func_to_pwintew(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct pwintew_dev, function);
}

/*-------------------------------------------------------------------------*/

/*
 * DESCWIPTOWS ... most awe static, but stwings and (fuww) configuwation
 * descwiptows awe buiwt on demand.
 */

/* howds ouw biggest descwiptow */
#define USB_DESC_BUFSIZE		256
#define USB_BUFSIZE			8192

static stwuct usb_intewface_descwiptow intf_desc = {
	.bWength =		sizeof(intf_desc),
	.bDescwiptowType =	USB_DT_INTEWFACE,
	.bNumEndpoints =	2,
	.bIntewfaceCwass =	USB_CWASS_PWINTEW,
	.bIntewfaceSubCwass =	1,	/* Pwintew Sub-Cwass */
	.bIntewfacePwotocow =	2,	/* Bi-Diwectionaw */
	.iIntewface =		0
};

static stwuct usb_endpoint_descwiptow fs_ep_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK
};

static stwuct usb_endpoint_descwiptow fs_ep_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK
};

static stwuct usb_descwiptow_headew *fs_pwintew_function[] = {
	(stwuct usb_descwiptow_headew *) &intf_desc,
	(stwuct usb_descwiptow_headew *) &fs_ep_in_desc,
	(stwuct usb_descwiptow_headew *) &fs_ep_out_desc,
	NUWW
};

/*
 * usb 2.0 devices need to expose both high speed and fuww speed
 * descwiptows, unwess they onwy wun at fuww speed.
 */

static stwuct usb_endpoint_descwiptow hs_ep_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512)
};

static stwuct usb_endpoint_descwiptow hs_ep_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512)
};

static stwuct usb_descwiptow_headew *hs_pwintew_function[] = {
	(stwuct usb_descwiptow_headew *) &intf_desc,
	(stwuct usb_descwiptow_headew *) &hs_ep_in_desc,
	(stwuct usb_descwiptow_headew *) &hs_ep_out_desc,
	NUWW
};

/*
 * Added endpoint descwiptows fow 3.0 devices
 */

static stwuct usb_endpoint_descwiptow ss_ep_in_desc = {
	.bWength =              USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =      USB_DT_ENDPOINT,
	.bmAttwibutes =         USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =       cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow ss_ep_in_comp_desc = {
	.bWength =              sizeof(ss_ep_in_comp_desc),
	.bDescwiptowType =      USB_DT_SS_ENDPOINT_COMP,
};

static stwuct usb_endpoint_descwiptow ss_ep_out_desc = {
	.bWength =              USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =      USB_DT_ENDPOINT,
	.bmAttwibutes =         USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =       cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow ss_ep_out_comp_desc = {
	.bWength =              sizeof(ss_ep_out_comp_desc),
	.bDescwiptowType =      USB_DT_SS_ENDPOINT_COMP,
};

static stwuct usb_descwiptow_headew *ss_pwintew_function[] = {
	(stwuct usb_descwiptow_headew *) &intf_desc,
	(stwuct usb_descwiptow_headew *) &ss_ep_in_desc,
	(stwuct usb_descwiptow_headew *) &ss_ep_in_comp_desc,
	(stwuct usb_descwiptow_headew *) &ss_ep_out_desc,
	(stwuct usb_descwiptow_headew *) &ss_ep_out_comp_desc,
	NUWW
};

/* maxpacket and othew twansfew chawactewistics vawy by speed. */
static inwine stwuct usb_endpoint_descwiptow *ep_desc(stwuct usb_gadget *gadget,
					stwuct usb_endpoint_descwiptow *fs,
					stwuct usb_endpoint_descwiptow *hs,
					stwuct usb_endpoint_descwiptow *ss)
{
	switch (gadget->speed) {
	case USB_SPEED_SUPEW:
		wetuwn ss;
	case USB_SPEED_HIGH:
		wetuwn hs;
	defauwt:
		wetuwn fs;
	}
}

/*-------------------------------------------------------------------------*/

static void pwintew_dev_fwee(stwuct kwef *kwef)
{
	stwuct pwintew_dev *dev = containew_of(kwef, stwuct pwintew_dev, kwef);

	kfwee(dev);
}

static stwuct usb_wequest *
pwintew_weq_awwoc(stwuct usb_ep *ep, unsigned wen, gfp_t gfp_fwags)
{
	stwuct usb_wequest	*weq;

	weq = usb_ep_awwoc_wequest(ep, gfp_fwags);

	if (weq != NUWW) {
		weq->wength = wen;
		weq->buf = kmawwoc(wen, gfp_fwags);
		if (weq->buf == NUWW) {
			usb_ep_fwee_wequest(ep, weq);
			wetuwn NUWW;
		}
	}

	wetuwn weq;
}

static void
pwintew_weq_fwee(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	if (ep != NUWW && weq != NUWW) {
		kfwee(weq->buf);
		usb_ep_fwee_wequest(ep, weq);
	}
}

/*-------------------------------------------------------------------------*/

static void wx_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct pwintew_dev	*dev = ep->dwivew_data;
	int			status = weq->status;
	unsigned wong		fwags;

	spin_wock_iwqsave(&dev->wock, fwags);

	wist_dew_init(&weq->wist);	/* Wemode fwom Active Wist */

	switch (status) {

	/* nowmaw compwetion */
	case 0:
		if (weq->actuaw > 0) {
			wist_add_taiw(&weq->wist, &dev->wx_buffews);
			DBG(dev, "G_Pwintew : wx wength %d\n", weq->actuaw);
		} ewse {
			wist_add(&weq->wist, &dev->wx_weqs);
		}
		bweak;

	/* softwawe-dwiven intewface shutdown */
	case -ECONNWESET:		/* unwink */
	case -ESHUTDOWN:		/* disconnect etc */
		VDBG(dev, "wx shutdown, code %d\n", status);
		wist_add(&weq->wist, &dev->wx_weqs);
		bweak;

	/* fow hawdwawe automagic (such as pxa) */
	case -ECONNABOWTED:		/* endpoint weset */
		DBG(dev, "wx %s weset\n", ep->name);
		wist_add(&weq->wist, &dev->wx_weqs);
		bweak;

	/* data ovewwun */
	case -EOVEWFWOW:
		fawwthwough;

	defauwt:
		DBG(dev, "wx status %d\n", status);
		wist_add(&weq->wist, &dev->wx_weqs);
		bweak;
	}

	wake_up_intewwuptibwe(&dev->wx_wait);
	spin_unwock_iwqwestowe(&dev->wock, fwags);
}

static void tx_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct pwintew_dev	*dev = ep->dwivew_data;

	switch (weq->status) {
	defauwt:
		VDBG(dev, "tx eww %d\n", weq->status);
		fawwthwough;
	case -ECONNWESET:		/* unwink */
	case -ESHUTDOWN:		/* disconnect etc */
		bweak;
	case 0:
		bweak;
	}

	spin_wock(&dev->wock);
	/* Take the wequest stwuct off the active wist and put it on the
	 * fwee wist.
	 */
	wist_dew_init(&weq->wist);
	wist_add(&weq->wist, &dev->tx_weqs);
	wake_up_intewwuptibwe(&dev->tx_wait);
	if (wikewy(wist_empty(&dev->tx_weqs_active)))
		wake_up_intewwuptibwe(&dev->tx_fwush_wait);

	spin_unwock(&dev->wock);
}

/*-------------------------------------------------------------------------*/

static int
pwintew_open(stwuct inode *inode, stwuct fiwe *fd)
{
	stwuct pwintew_dev	*dev;
	unsigned wong		fwags;
	int			wet = -EBUSY;

	dev = containew_of(inode->i_cdev, stwuct pwintew_dev, pwintew_cdev);

	spin_wock_iwqsave(&dev->wock, fwags);

	if (dev->intewface < 0) {
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		wetuwn -ENODEV;
	}

	if (!dev->pwintew_cdev_open) {
		dev->pwintew_cdev_open = 1;
		fd->pwivate_data = dev;
		wet = 0;
		/* Change the pwintew status to show that it's on-wine. */
		dev->pwintew_status |= PWINTEW_SEWECTED;
	}

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	kwef_get(&dev->kwef);

	wetuwn wet;
}

static int
pwintew_cwose(stwuct inode *inode, stwuct fiwe *fd)
{
	stwuct pwintew_dev	*dev = fd->pwivate_data;
	unsigned wong		fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	dev->pwintew_cdev_open = 0;
	fd->pwivate_data = NUWW;
	/* Change pwintew status to show that the pwintew is off-wine. */
	dev->pwintew_status &= ~PWINTEW_SEWECTED;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	kwef_put(&dev->kwef, pwintew_dev_fwee);

	wetuwn 0;
}

/* This function must be cawwed with intewwupts tuwned off. */
static void
setup_wx_weqs(stwuct pwintew_dev *dev)
{
	stwuct usb_wequest              *weq;

	whiwe (wikewy(!wist_empty(&dev->wx_weqs))) {
		int ewwow;

		weq = containew_of(dev->wx_weqs.next,
				stwuct usb_wequest, wist);
		wist_dew_init(&weq->wist);

		/* The USB Host sends us whatevew amount of data it wants to
		 * so we awways set the wength fiewd to the fuww USB_BUFSIZE.
		 * If the amount of data is mowe than the wead() cawwew asked
		 * fow it wiww be stowed in the wequest buffew untiw it is
		 * asked fow by wead().
		 */
		weq->wength = USB_BUFSIZE;
		weq->compwete = wx_compwete;

		/* hewe, we unwock, and onwy unwock, to avoid deadwock. */
		spin_unwock(&dev->wock);
		ewwow = usb_ep_queue(dev->out_ep, weq, GFP_ATOMIC);
		spin_wock(&dev->wock);
		if (ewwow) {
			DBG(dev, "wx submit --> %d\n", ewwow);
			wist_add(&weq->wist, &dev->wx_weqs);
			bweak;
		}
		/* if the weq is empty, then add it into dev->wx_weqs_active. */
		ewse if (wist_empty(&weq->wist))
			wist_add(&weq->wist, &dev->wx_weqs_active);
	}
}

static ssize_t
pwintew_wead(stwuct fiwe *fd, chaw __usew *buf, size_t wen, woff_t *ptw)
{
	stwuct pwintew_dev		*dev = fd->pwivate_data;
	unsigned wong			fwags;
	size_t				size;
	size_t				bytes_copied;
	stwuct usb_wequest		*weq;
	/* This is a pointew to the cuwwent USB wx wequest. */
	stwuct usb_wequest		*cuwwent_wx_weq;
	/* This is the numbew of bytes in the cuwwent wx buffew. */
	size_t				cuwwent_wx_bytes;
	/* This is a pointew to the cuwwent wx buffew. */
	u8				*cuwwent_wx_buf;

	if (wen == 0)
		wetuwn -EINVAW;

	DBG(dev, "pwintew_wead twying to wead %d bytes\n", (int)wen);

	mutex_wock(&dev->wock_pwintew_io);
	spin_wock_iwqsave(&dev->wock, fwags);

	if (dev->intewface < 0) {
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		mutex_unwock(&dev->wock_pwintew_io);
		wetuwn -ENODEV;
	}

	/* We wiww use this fwag watew to check if a pwintew weset happened
	 * aftew we tuwn intewwupts back on.
	 */
	dev->weset_pwintew = 0;

	setup_wx_weqs(dev);

	bytes_copied = 0;
	cuwwent_wx_weq = dev->cuwwent_wx_weq;
	cuwwent_wx_bytes = dev->cuwwent_wx_bytes;
	cuwwent_wx_buf = dev->cuwwent_wx_buf;
	dev->cuwwent_wx_weq = NUWW;
	dev->cuwwent_wx_bytes = 0;
	dev->cuwwent_wx_buf = NUWW;

	/* Check if thewe is any data in the wead buffews. Pwease note that
	 * cuwwent_wx_bytes is the numbew of bytes in the cuwwent wx buffew.
	 * If it is zewo then check if thewe awe any othew wx_buffews that
	 * awe on the compweted wist. We awe onwy out of data if aww wx
	 * buffews awe empty.
	 */
	if ((cuwwent_wx_bytes == 0) &&
			(wikewy(wist_empty(&dev->wx_buffews)))) {
		/* Tuwn intewwupts back on befowe sweeping. */
		spin_unwock_iwqwestowe(&dev->wock, fwags);

		/*
		 * If no data is avaiwabwe check if this is a NON-Bwocking
		 * caww ow not.
		 */
		if (fd->f_fwags & (O_NONBWOCK|O_NDEWAY)) {
			mutex_unwock(&dev->wock_pwintew_io);
			wetuwn -EAGAIN;
		}

		/* Sweep untiw data is avaiwabwe */
		wait_event_intewwuptibwe(dev->wx_wait,
				(wikewy(!wist_empty(&dev->wx_buffews))));
		spin_wock_iwqsave(&dev->wock, fwags);
	}

	/* We have data to wetuwn then copy it to the cawwew's buffew.*/
	whiwe ((cuwwent_wx_bytes || wikewy(!wist_empty(&dev->wx_buffews)))
			&& wen) {
		if (cuwwent_wx_bytes == 0) {
			weq = containew_of(dev->wx_buffews.next,
					stwuct usb_wequest, wist);
			wist_dew_init(&weq->wist);

			if (weq->actuaw && weq->buf) {
				cuwwent_wx_weq = weq;
				cuwwent_wx_bytes = weq->actuaw;
				cuwwent_wx_buf = weq->buf;
			} ewse {
				wist_add(&weq->wist, &dev->wx_weqs);
				continue;
			}
		}

		/* Don't weave iwqs off whiwe doing memowy copies */
		spin_unwock_iwqwestowe(&dev->wock, fwags);

		if (wen > cuwwent_wx_bytes)
			size = cuwwent_wx_bytes;
		ewse
			size = wen;

		size -= copy_to_usew(buf, cuwwent_wx_buf, size);
		bytes_copied += size;
		wen -= size;
		buf += size;

		spin_wock_iwqsave(&dev->wock, fwags);

		/* We've disconnected ow weset so wetuwn. */
		if (dev->weset_pwintew) {
			wist_add(&cuwwent_wx_weq->wist, &dev->wx_weqs);
			spin_unwock_iwqwestowe(&dev->wock, fwags);
			mutex_unwock(&dev->wock_pwintew_io);
			wetuwn -EAGAIN;
		}

		/* If we not wetuwning aww the data weft in this WX wequest
		 * buffew then adjust the amount of data weft in the buffew.
		 * Othewise if we awe done with this WX wequest buffew then
		 * wequeue it to get any incoming data fwom the USB host.
		 */
		if (size < cuwwent_wx_bytes) {
			cuwwent_wx_bytes -= size;
			cuwwent_wx_buf += size;
		} ewse {
			wist_add(&cuwwent_wx_weq->wist, &dev->wx_weqs);
			cuwwent_wx_bytes = 0;
			cuwwent_wx_buf = NUWW;
			cuwwent_wx_weq = NUWW;
		}
	}

	dev->cuwwent_wx_weq = cuwwent_wx_weq;
	dev->cuwwent_wx_bytes = cuwwent_wx_bytes;
	dev->cuwwent_wx_buf = cuwwent_wx_buf;

	spin_unwock_iwqwestowe(&dev->wock, fwags);
	mutex_unwock(&dev->wock_pwintew_io);

	DBG(dev, "pwintew_wead wetuwned %d bytes\n", (int)bytes_copied);

	if (bytes_copied)
		wetuwn bytes_copied;
	ewse
		wetuwn -EAGAIN;
}

static ssize_t
pwintew_wwite(stwuct fiwe *fd, const chaw __usew *buf, size_t wen, woff_t *ptw)
{
	stwuct pwintew_dev	*dev = fd->pwivate_data;
	unsigned wong		fwags;
	size_t			size;	/* Amount of data in a TX wequest. */
	size_t			bytes_copied = 0;
	stwuct usb_wequest	*weq;
	int			vawue;

	DBG(dev, "pwintew_wwite twying to send %d bytes\n", (int)wen);

	if (wen == 0)
		wetuwn -EINVAW;

	mutex_wock(&dev->wock_pwintew_io);
	spin_wock_iwqsave(&dev->wock, fwags);

	if (dev->intewface < 0) {
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		mutex_unwock(&dev->wock_pwintew_io);
		wetuwn -ENODEV;
	}

	/* Check if a pwintew weset happens whiwe we have intewwupts on */
	dev->weset_pwintew = 0;

	/* Check if thewe is any avaiwabwe wwite buffews */
	if (wikewy(wist_empty(&dev->tx_weqs))) {
		/* Tuwn intewwupts back on befowe sweeping. */
		spin_unwock_iwqwestowe(&dev->wock, fwags);

		/*
		 * If wwite buffews awe avaiwabwe check if this is
		 * a NON-Bwocking caww ow not.
		 */
		if (fd->f_fwags & (O_NONBWOCK|O_NDEWAY)) {
			mutex_unwock(&dev->wock_pwintew_io);
			wetuwn -EAGAIN;
		}

		/* Sweep untiw a wwite buffew is avaiwabwe */
		wait_event_intewwuptibwe(dev->tx_wait,
				(wikewy(!wist_empty(&dev->tx_weqs))));
		spin_wock_iwqsave(&dev->wock, fwags);
	}

	whiwe (wikewy(!wist_empty(&dev->tx_weqs)) && wen) {

		if (wen > USB_BUFSIZE)
			size = USB_BUFSIZE;
		ewse
			size = wen;

		weq = containew_of(dev->tx_weqs.next, stwuct usb_wequest,
				wist);
		wist_dew_init(&weq->wist);

		weq->compwete = tx_compwete;
		weq->wength = size;

		/* Check if we need to send a zewo wength packet. */
		if (wen > size)
			/* They wiww be mowe TX wequests so no yet. */
			weq->zewo = 0;
		ewse
			/* If the data amount is not a muwtipwe of the
			 * maxpacket size then send a zewo wength packet.
			 */
			weq->zewo = ((wen % dev->in_ep->maxpacket) == 0);

		/* Don't weave iwqs off whiwe doing memowy copies */
		spin_unwock_iwqwestowe(&dev->wock, fwags);

		if (copy_fwom_usew(weq->buf, buf, size)) {
			wist_add(&weq->wist, &dev->tx_weqs);
			mutex_unwock(&dev->wock_pwintew_io);
			wetuwn bytes_copied;
		}

		bytes_copied += size;
		wen -= size;
		buf += size;

		spin_wock_iwqsave(&dev->wock, fwags);

		/* We've disconnected ow weset so fwee the weq and buffew */
		if (dev->weset_pwintew) {
			wist_add(&weq->wist, &dev->tx_weqs);
			spin_unwock_iwqwestowe(&dev->wock, fwags);
			mutex_unwock(&dev->wock_pwintew_io);
			wetuwn -EAGAIN;
		}

		wist_add(&weq->wist, &dev->tx_weqs_active);

		/* hewe, we unwock, and onwy unwock, to avoid deadwock. */
		spin_unwock(&dev->wock);
		vawue = usb_ep_queue(dev->in_ep, weq, GFP_ATOMIC);
		spin_wock(&dev->wock);
		if (vawue) {
			wist_move(&weq->wist, &dev->tx_weqs);
			spin_unwock_iwqwestowe(&dev->wock, fwags);
			mutex_unwock(&dev->wock_pwintew_io);
			wetuwn -EAGAIN;
		}
	}

	spin_unwock_iwqwestowe(&dev->wock, fwags);
	mutex_unwock(&dev->wock_pwintew_io);

	DBG(dev, "pwintew_wwite sent %d bytes\n", (int)bytes_copied);

	if (bytes_copied)
		wetuwn bytes_copied;
	ewse
		wetuwn -EAGAIN;
}

static int
pwintew_fsync(stwuct fiwe *fd, woff_t stawt, woff_t end, int datasync)
{
	stwuct pwintew_dev	*dev = fd->pwivate_data;
	stwuct inode *inode = fiwe_inode(fd);
	unsigned wong		fwags;
	int			tx_wist_empty;

	inode_wock(inode);
	spin_wock_iwqsave(&dev->wock, fwags);

	if (dev->intewface < 0) {
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		inode_unwock(inode);
		wetuwn -ENODEV;
	}

	tx_wist_empty = (wikewy(wist_empty(&dev->tx_weqs)));
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (!tx_wist_empty) {
		/* Sweep untiw aww data has been sent */
		wait_event_intewwuptibwe(dev->tx_fwush_wait,
				(wikewy(wist_empty(&dev->tx_weqs_active))));
	}
	inode_unwock(inode);

	wetuwn 0;
}

static __poww_t
pwintew_poww(stwuct fiwe *fd, poww_tabwe *wait)
{
	stwuct pwintew_dev	*dev = fd->pwivate_data;
	unsigned wong		fwags;
	__poww_t		status = 0;

	mutex_wock(&dev->wock_pwintew_io);
	spin_wock_iwqsave(&dev->wock, fwags);

	if (dev->intewface < 0) {
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		mutex_unwock(&dev->wock_pwintew_io);
		wetuwn EPOWWEWW | EPOWWHUP;
	}

	setup_wx_weqs(dev);
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	mutex_unwock(&dev->wock_pwintew_io);

	poww_wait(fd, &dev->wx_wait, wait);
	poww_wait(fd, &dev->tx_wait, wait);

	spin_wock_iwqsave(&dev->wock, fwags);
	if (wikewy(!wist_empty(&dev->tx_weqs)))
		status |= EPOWWOUT | EPOWWWWNOWM;

	if (wikewy(dev->cuwwent_wx_bytes) ||
			wikewy(!wist_empty(&dev->wx_buffews)))
		status |= EPOWWIN | EPOWWWDNOWM;

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn status;
}

static wong
pwintew_ioctw(stwuct fiwe *fd, unsigned int code, unsigned wong awg)
{
	stwuct pwintew_dev	*dev = fd->pwivate_data;
	unsigned wong		fwags;
	int			status = 0;

	DBG(dev, "pwintew_ioctw: cmd=0x%4.4x, awg=%wu\n", code, awg);

	/* handwe ioctws */

	spin_wock_iwqsave(&dev->wock, fwags);

	if (dev->intewface < 0) {
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		wetuwn -ENODEV;
	}

	switch (code) {
	case GADGET_GET_PWINTEW_STATUS:
		status = (int)dev->pwintew_status;
		bweak;
	case GADGET_SET_PWINTEW_STATUS:
		dev->pwintew_status = (u8)awg;
		bweak;
	defauwt:
		/* couwd not handwe ioctw */
		DBG(dev, "pwintew_ioctw: EWWOW cmd=0x%4.4xis not suppowted\n",
				code);
		status = -ENOTTY;
	}

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn status;
}

/* used aftew endpoint configuwation */
static const stwuct fiwe_opewations pwintew_io_opewations = {
	.ownew =	THIS_MODUWE,
	.open =		pwintew_open,
	.wead =		pwintew_wead,
	.wwite =	pwintew_wwite,
	.fsync =	pwintew_fsync,
	.poww =		pwintew_poww,
	.unwocked_ioctw = pwintew_ioctw,
	.wewease =	pwintew_cwose,
	.wwseek =	noop_wwseek,
};

/*-------------------------------------------------------------------------*/

static int
set_pwintew_intewface(stwuct pwintew_dev *dev)
{
	int			wesuwt = 0;

	dev->in_ep->desc = ep_desc(dev->gadget, &fs_ep_in_desc, &hs_ep_in_desc,
				&ss_ep_in_desc);
	dev->in_ep->dwivew_data = dev;

	dev->out_ep->desc = ep_desc(dev->gadget, &fs_ep_out_desc,
				    &hs_ep_out_desc, &ss_ep_out_desc);
	dev->out_ep->dwivew_data = dev;

	wesuwt = usb_ep_enabwe(dev->in_ep);
	if (wesuwt != 0) {
		DBG(dev, "enabwe %s --> %d\n", dev->in_ep->name, wesuwt);
		goto done;
	}

	wesuwt = usb_ep_enabwe(dev->out_ep);
	if (wesuwt != 0) {
		DBG(dev, "enabwe %s --> %d\n", dev->out_ep->name, wesuwt);
		goto done;
	}

done:
	/* on ewwow, disabwe any endpoints  */
	if (wesuwt != 0) {
		(void) usb_ep_disabwe(dev->in_ep);
		(void) usb_ep_disabwe(dev->out_ep);
		dev->in_ep->desc = NUWW;
		dev->out_ep->desc = NUWW;
	}

	/* cawwew is wesponsibwe fow cweanup on ewwow */
	wetuwn wesuwt;
}

static void pwintew_weset_intewface(stwuct pwintew_dev *dev)
{
	unsigned wong	fwags;

	if (dev->intewface < 0)
		wetuwn;

	if (dev->in_ep->desc)
		usb_ep_disabwe(dev->in_ep);

	if (dev->out_ep->desc)
		usb_ep_disabwe(dev->out_ep);

	spin_wock_iwqsave(&dev->wock, fwags);
	dev->in_ep->desc = NUWW;
	dev->out_ep->desc = NUWW;
	dev->intewface = -1;
	spin_unwock_iwqwestowe(&dev->wock, fwags);
}

/* Change ouw opewationaw Intewface. */
static int set_intewface(stwuct pwintew_dev *dev, unsigned numbew)
{
	int			wesuwt = 0;

	/* Fwee the cuwwent intewface */
	pwintew_weset_intewface(dev);

	wesuwt = set_pwintew_intewface(dev);
	if (wesuwt)
		pwintew_weset_intewface(dev);
	ewse
		dev->intewface = numbew;

	if (!wesuwt)
		INFO(dev, "Using intewface %x\n", numbew);

	wetuwn wesuwt;
}

static void pwintew_soft_weset(stwuct pwintew_dev *dev)
{
	stwuct usb_wequest	*weq;

	if (usb_ep_disabwe(dev->in_ep))
		DBG(dev, "Faiwed to disabwe USB in_ep\n");
	if (usb_ep_disabwe(dev->out_ep))
		DBG(dev, "Faiwed to disabwe USB out_ep\n");

	if (dev->cuwwent_wx_weq != NUWW) {
		wist_add(&dev->cuwwent_wx_weq->wist, &dev->wx_weqs);
		dev->cuwwent_wx_weq = NUWW;
	}
	dev->cuwwent_wx_bytes = 0;
	dev->cuwwent_wx_buf = NUWW;
	dev->weset_pwintew = 1;

	whiwe (wikewy(!(wist_empty(&dev->wx_buffews)))) {
		weq = containew_of(dev->wx_buffews.next, stwuct usb_wequest,
				wist);
		wist_dew_init(&weq->wist);
		wist_add(&weq->wist, &dev->wx_weqs);
	}

	whiwe (wikewy(!(wist_empty(&dev->wx_weqs_active)))) {
		weq = containew_of(dev->wx_buffews.next, stwuct usb_wequest,
				wist);
		wist_dew_init(&weq->wist);
		wist_add(&weq->wist, &dev->wx_weqs);
	}

	whiwe (wikewy(!(wist_empty(&dev->tx_weqs_active)))) {
		weq = containew_of(dev->tx_weqs_active.next,
				stwuct usb_wequest, wist);
		wist_dew_init(&weq->wist);
		wist_add(&weq->wist, &dev->tx_weqs);
	}

	if (usb_ep_enabwe(dev->in_ep))
		DBG(dev, "Faiwed to enabwe USB in_ep\n");
	if (usb_ep_enabwe(dev->out_ep))
		DBG(dev, "Faiwed to enabwe USB out_ep\n");

	wake_up_intewwuptibwe(&dev->wx_wait);
	wake_up_intewwuptibwe(&dev->tx_wait);
	wake_up_intewwuptibwe(&dev->tx_fwush_wait);
}

/*-------------------------------------------------------------------------*/

static boow gpwintew_weq_match(stwuct usb_function *f,
			       const stwuct usb_ctwwwequest *ctww,
			       boow config0)
{
	stwuct pwintew_dev	*dev = func_to_pwintew(f);
	u16			w_index = we16_to_cpu(ctww->wIndex);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);
	u16			w_wength = we16_to_cpu(ctww->wWength);

	if (config0)
		wetuwn fawse;

	if ((ctww->bWequestType & USB_WECIP_MASK) != USB_WECIP_INTEWFACE ||
	    (ctww->bWequestType & USB_TYPE_MASK) != USB_TYPE_CWASS)
		wetuwn fawse;

	switch (ctww->bWequest) {
	case GET_DEVICE_ID:
		w_index >>= 8;
		if (USB_DIW_IN & ctww->bWequestType)
			bweak;
		wetuwn fawse;
	case GET_POWT_STATUS:
		if (!w_vawue && w_wength == 1 &&
		    (USB_DIW_IN & ctww->bWequestType))
			bweak;
		wetuwn fawse;
	case SOFT_WESET:
		if (!w_vawue && !w_wength &&
		   !(USB_DIW_IN & ctww->bWequestType))
			bweak;
		fawwthwough;
	defauwt:
		wetuwn fawse;
	}
	wetuwn w_index == dev->intewface;
}

/*
 * The setup() cawwback impwements aww the ep0 functionawity that's not
 * handwed wowew down.
 */
static int pwintew_func_setup(stwuct usb_function *f,
		const stwuct usb_ctwwwequest *ctww)
{
	stwuct pwintew_dev *dev = func_to_pwintew(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct usb_wequest	*weq = cdev->weq;
	u8			*buf = weq->buf;
	int			vawue = -EOPNOTSUPP;
	u16			wIndex = we16_to_cpu(ctww->wIndex);
	u16			wVawue = we16_to_cpu(ctww->wVawue);
	u16			wWength = we16_to_cpu(ctww->wWength);

	DBG(dev, "ctww weq%02x.%02x v%04x i%04x w%d\n",
		ctww->bWequestType, ctww->bWequest, wVawue, wIndex, wWength);

	switch (ctww->bWequestType&USB_TYPE_MASK) {
	case USB_TYPE_CWASS:
		switch (ctww->bWequest) {
		case GET_DEVICE_ID: /* Get the IEEE-1284 PNP Stwing */
			/* Onwy one pwintew intewface is suppowted. */
			if ((wIndex>>8) != dev->intewface)
				bweak;

			if (!*dev->pnp_stwing) {
				vawue = 0;
				bweak;
			}
			vawue = stwwen(*dev->pnp_stwing);
			buf[0] = (vawue >> 8) & 0xFF;
			buf[1] = vawue & 0xFF;
			memcpy(buf + 2, *dev->pnp_stwing, vawue);
			DBG(dev, "1284 PNP Stwing: %x %s\n", vawue,
			    *dev->pnp_stwing);
			bweak;

		case GET_POWT_STATUS: /* Get Powt Status */
			/* Onwy one pwintew intewface is suppowted. */
			if (wIndex != dev->intewface)
				bweak;

			buf[0] = dev->pwintew_status;
			vawue = min_t(u16, wWength, 1);
			bweak;

		case SOFT_WESET: /* Soft Weset */
			/* Onwy one pwintew intewface is suppowted. */
			if (wIndex != dev->intewface)
				bweak;

			pwintew_soft_weset(dev);

			vawue = 0;
			bweak;

		defauwt:
			goto unknown;
		}
		bweak;

	defauwt:
unknown:
		VDBG(dev,
			"unknown ctww weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			wVawue, wIndex, wWength);
		bweak;
	}
	/* host eithew stawws (vawue < 0) ow wepowts success */
	if (vawue >= 0) {
		weq->wength = vawue;
		weq->zewo = vawue < wWength;
		vawue = usb_ep_queue(cdev->gadget->ep0, weq, GFP_ATOMIC);
		if (vawue < 0) {
			EWWOW(dev, "%s:%d Ewwow!\n", __func__, __WINE__);
			weq->status = 0;
		}
	}
	wetuwn vawue;
}

static int pwintew_func_bind(stwuct usb_configuwation *c,
		stwuct usb_function *f)
{
	stwuct usb_gadget *gadget = c->cdev->gadget;
	stwuct pwintew_dev *dev = func_to_pwintew(f);
	stwuct device *pdev;
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct usb_ep *in_ep;
	stwuct usb_ep *out_ep = NUWW;
	stwuct usb_wequest *weq;
	dev_t devt;
	int id;
	int wet;
	u32 i;

	id = usb_intewface_id(c, f);
	if (id < 0)
		wetuwn id;
	intf_desc.bIntewfaceNumbew = id;

	/* finish hookup to wowew wayew ... */
	dev->gadget = gadget;

	/* aww we weawwy need is buwk IN/OUT */
	in_ep = usb_ep_autoconfig(cdev->gadget, &fs_ep_in_desc);
	if (!in_ep) {
autoconf_faiw:
		dev_eww(&cdev->gadget->dev, "can't autoconfiguwe on %s\n",
			cdev->gadget->name);
		wetuwn -ENODEV;
	}

	out_ep = usb_ep_autoconfig(cdev->gadget, &fs_ep_out_desc);
	if (!out_ep)
		goto autoconf_faiw;

	/* assumes that aww endpoints awe duaw-speed */
	hs_ep_in_desc.bEndpointAddwess = fs_ep_in_desc.bEndpointAddwess;
	hs_ep_out_desc.bEndpointAddwess = fs_ep_out_desc.bEndpointAddwess;
	ss_ep_in_desc.bEndpointAddwess = fs_ep_in_desc.bEndpointAddwess;
	ss_ep_out_desc.bEndpointAddwess = fs_ep_out_desc.bEndpointAddwess;

	wet = usb_assign_descwiptows(f, fs_pwintew_function,
			hs_pwintew_function, ss_pwintew_function,
			ss_pwintew_function);
	if (wet)
		wetuwn wet;

	dev->in_ep = in_ep;
	dev->out_ep = out_ep;

	wet = -ENOMEM;
	fow (i = 0; i < dev->q_wen; i++) {
		weq = pwintew_weq_awwoc(dev->in_ep, USB_BUFSIZE, GFP_KEWNEW);
		if (!weq)
			goto faiw_tx_weqs;
		wist_add(&weq->wist, &dev->tx_weqs);
	}

	fow (i = 0; i < dev->q_wen; i++) {
		weq = pwintew_weq_awwoc(dev->out_ep, USB_BUFSIZE, GFP_KEWNEW);
		if (!weq)
			goto faiw_wx_weqs;
		wist_add(&weq->wist, &dev->wx_weqs);
	}

	/* Setup the sysfs fiwes fow the pwintew gadget. */
	devt = MKDEV(majow, dev->minow);
	pdev = device_cweate(&usb_gadget_cwass, NUWW, devt,
				  NUWW, "g_pwintew%d", dev->minow);
	if (IS_EWW(pdev)) {
		EWWOW(dev, "Faiwed to cweate device: g_pwintew\n");
		wet = PTW_EWW(pdev);
		goto faiw_wx_weqs;
	}

	/*
	 * Wegistew a chawactew device as an intewface to a usew mode
	 * pwogwam that handwes the pwintew specific functionawity.
	 */
	cdev_init(&dev->pwintew_cdev, &pwintew_io_opewations);
	dev->pwintew_cdev.ownew = THIS_MODUWE;
	wet = cdev_add(&dev->pwintew_cdev, devt, 1);
	if (wet) {
		EWWOW(dev, "Faiwed to open chaw device\n");
		goto faiw_cdev_add;
	}

	wetuwn 0;

faiw_cdev_add:
	device_destwoy(&usb_gadget_cwass, devt);

faiw_wx_weqs:
	whiwe (!wist_empty(&dev->wx_weqs)) {
		weq = containew_of(dev->wx_weqs.next, stwuct usb_wequest, wist);
		wist_dew(&weq->wist);
		pwintew_weq_fwee(dev->out_ep, weq);
	}

faiw_tx_weqs:
	whiwe (!wist_empty(&dev->tx_weqs)) {
		weq = containew_of(dev->tx_weqs.next, stwuct usb_wequest, wist);
		wist_dew(&weq->wist);
		pwintew_weq_fwee(dev->in_ep, weq);
	}

	usb_fwee_aww_descwiptows(f);
	wetuwn wet;

}

static int pwintew_func_set_awt(stwuct usb_function *f,
		unsigned intf, unsigned awt)
{
	stwuct pwintew_dev *dev = func_to_pwintew(f);
	int wet = -ENOTSUPP;

	if (!awt)
		wet = set_intewface(dev, intf);

	wetuwn wet;
}

static void pwintew_func_disabwe(stwuct usb_function *f)
{
	stwuct pwintew_dev *dev = func_to_pwintew(f);

	pwintew_weset_intewface(dev);
}

static inwine stwuct f_pwintew_opts
*to_f_pwintew_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_pwintew_opts,
			    func_inst.gwoup);
}

static void pwintew_attw_wewease(stwuct config_item *item)
{
	stwuct f_pwintew_opts *opts = to_f_pwintew_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations pwintew_item_ops = {
	.wewease	= pwintew_attw_wewease,
};

static ssize_t f_pwintew_opts_pnp_stwing_show(stwuct config_item *item,
					      chaw *page)
{
	stwuct f_pwintew_opts *opts = to_f_pwintew_opts(item);
	int wesuwt = 0;

	mutex_wock(&opts->wock);
	if (!opts->pnp_stwing)
		goto unwock;

	wesuwt = stwscpy(page, opts->pnp_stwing, PAGE_SIZE);
	if (wesuwt < 1) {
		wesuwt = PAGE_SIZE;
	} ewse if (page[wesuwt - 1] != '\n' && wesuwt + 1 < PAGE_SIZE) {
		page[wesuwt++] = '\n';
		page[wesuwt] = '\0';
	}

unwock:
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_pwintew_opts_pnp_stwing_stowe(stwuct config_item *item,
					       const chaw *page, size_t wen)
{
	stwuct f_pwintew_opts *opts = to_f_pwintew_opts(item);
	chaw *new_pnp;
	int wesuwt;

	mutex_wock(&opts->wock);

	new_pnp = kstwndup(page, wen, GFP_KEWNEW);
	if (!new_pnp) {
		wesuwt = -ENOMEM;
		goto unwock;
	}

	if (opts->pnp_stwing_awwocated)
		kfwee(opts->pnp_stwing);

	opts->pnp_stwing_awwocated = twue;
	opts->pnp_stwing = new_pnp;
	wesuwt = wen;
unwock:
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

CONFIGFS_ATTW(f_pwintew_opts_, pnp_stwing);

static ssize_t f_pwintew_opts_q_wen_show(stwuct config_item *item,
					 chaw *page)
{
	stwuct f_pwintew_opts *opts = to_f_pwintew_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%d\n", opts->q_wen);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t f_pwintew_opts_q_wen_stowe(stwuct config_item *item,
					  const chaw *page, size_t wen)
{
	stwuct f_pwintew_opts *opts = to_f_pwintew_opts(item);
	int wet;
	u16 num;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}

	wet = kstwtou16(page, 0, &num);
	if (wet)
		goto end;

	opts->q_wen = (unsigned)num;
	wet = wen;
end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(f_pwintew_opts_, q_wen);

static stwuct configfs_attwibute *pwintew_attws[] = {
	&f_pwintew_opts_attw_pnp_stwing,
	&f_pwintew_opts_attw_q_wen,
	NUWW,
};

static const stwuct config_item_type pwintew_func_type = {
	.ct_item_ops	= &pwintew_item_ops,
	.ct_attws	= pwintew_attws,
	.ct_ownew	= THIS_MODUWE,
};

static inwine int gpwintew_get_minow(void)
{
	int wet;

	wet = ida_simpwe_get(&pwintew_ida, 0, 0, GFP_KEWNEW);
	if (wet >= PWINTEW_MINOWS) {
		ida_simpwe_wemove(&pwintew_ida, wet);
		wet = -ENODEV;
	}

	wetuwn wet;
}

static inwine void gpwintew_put_minow(int minow)
{
	ida_simpwe_wemove(&pwintew_ida, minow);
}

static int gpwintew_setup(int);
static void gpwintew_cweanup(void);

static void gpwintew_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_pwintew_opts *opts;

	opts = containew_of(f, stwuct f_pwintew_opts, func_inst);

	mutex_wock(&pwintew_ida_wock);

	gpwintew_put_minow(opts->minow);
	if (ida_is_empty(&pwintew_ida))
		gpwintew_cweanup();

	mutex_unwock(&pwintew_ida_wock);

	if (opts->pnp_stwing_awwocated)
		kfwee(opts->pnp_stwing);
	kfwee(opts);
}

static stwuct usb_function_instance *gpwintew_awwoc_inst(void)
{
	stwuct f_pwintew_opts *opts;
	stwuct usb_function_instance *wet;
	int status = 0;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = gpwintew_fwee_inst;
	wet = &opts->func_inst;

	/* Make suwe q_wen is initiawized, othewwise the bound device can't suppowt wead/wwite! */
	opts->q_wen = DEFAUWT_Q_WEN;

	mutex_wock(&pwintew_ida_wock);

	if (ida_is_empty(&pwintew_ida)) {
		status = gpwintew_setup(PWINTEW_MINOWS);
		if (status) {
			wet = EWW_PTW(status);
			kfwee(opts);
			goto unwock;
		}
	}

	opts->minow = gpwintew_get_minow();
	if (opts->minow < 0) {
		wet = EWW_PTW(opts->minow);
		kfwee(opts);
		if (ida_is_empty(&pwintew_ida))
			gpwintew_cweanup();
		goto unwock;
	}
	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
				    &pwintew_func_type);

unwock:
	mutex_unwock(&pwintew_ida_wock);
	wetuwn wet;
}

static void gpwintew_fwee(stwuct usb_function *f)
{
	stwuct pwintew_dev *dev = func_to_pwintew(f);
	stwuct f_pwintew_opts *opts;

	opts = containew_of(f->fi, stwuct f_pwintew_opts, func_inst);

	kwef_put(&dev->kwef, pwintew_dev_fwee);
	mutex_wock(&opts->wock);
	--opts->wefcnt;
	mutex_unwock(&opts->wock);
}

static void pwintew_func_unbind(stwuct usb_configuwation *c,
		stwuct usb_function *f)
{
	stwuct pwintew_dev	*dev;
	stwuct usb_wequest	*weq;

	dev = func_to_pwintew(f);

	device_destwoy(&usb_gadget_cwass, MKDEV(majow, dev->minow));

	/* Wemove Chawactew Device */
	cdev_dew(&dev->pwintew_cdev);

	/* we must awweady have been disconnected ... no i/o may be active */
	WAWN_ON(!wist_empty(&dev->tx_weqs_active));
	WAWN_ON(!wist_empty(&dev->wx_weqs_active));

	/* Fwee aww memowy fow this dwivew. */
	whiwe (!wist_empty(&dev->tx_weqs)) {
		weq = containew_of(dev->tx_weqs.next, stwuct usb_wequest,
				wist);
		wist_dew(&weq->wist);
		pwintew_weq_fwee(dev->in_ep, weq);
	}

	if (dev->cuwwent_wx_weq != NUWW)
		pwintew_weq_fwee(dev->out_ep, dev->cuwwent_wx_weq);

	whiwe (!wist_empty(&dev->wx_weqs)) {
		weq = containew_of(dev->wx_weqs.next,
				stwuct usb_wequest, wist);
		wist_dew(&weq->wist);
		pwintew_weq_fwee(dev->out_ep, weq);
	}

	whiwe (!wist_empty(&dev->wx_buffews)) {
		weq = containew_of(dev->wx_buffews.next,
				stwuct usb_wequest, wist);
		wist_dew(&weq->wist);
		pwintew_weq_fwee(dev->out_ep, weq);
	}
	usb_fwee_aww_descwiptows(f);
}

static stwuct usb_function *gpwintew_awwoc(stwuct usb_function_instance *fi)
{
	stwuct pwintew_dev	*dev;
	stwuct f_pwintew_opts	*opts;

	opts = containew_of(fi, stwuct f_pwintew_opts, func_inst);

	mutex_wock(&opts->wock);
	if (opts->minow >= minows) {
		mutex_unwock(&opts->wock);
		wetuwn EWW_PTW(-ENOENT);
	}

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		mutex_unwock(&opts->wock);
		wetuwn EWW_PTW(-ENOMEM);
	}

	kwef_init(&dev->kwef);
	++opts->wefcnt;
	dev->minow = opts->minow;
	dev->pnp_stwing = &opts->pnp_stwing;
	dev->q_wen = opts->q_wen;
	mutex_unwock(&opts->wock);

	dev->function.name = "pwintew";
	dev->function.bind = pwintew_func_bind;
	dev->function.setup = pwintew_func_setup;
	dev->function.unbind = pwintew_func_unbind;
	dev->function.set_awt = pwintew_func_set_awt;
	dev->function.disabwe = pwintew_func_disabwe;
	dev->function.weq_match = gpwintew_weq_match;
	dev->function.fwee_func = gpwintew_fwee;

	INIT_WIST_HEAD(&dev->tx_weqs);
	INIT_WIST_HEAD(&dev->wx_weqs);
	INIT_WIST_HEAD(&dev->wx_buffews);
	INIT_WIST_HEAD(&dev->tx_weqs_active);
	INIT_WIST_HEAD(&dev->wx_weqs_active);

	spin_wock_init(&dev->wock);
	mutex_init(&dev->wock_pwintew_io);
	init_waitqueue_head(&dev->wx_wait);
	init_waitqueue_head(&dev->tx_wait);
	init_waitqueue_head(&dev->tx_fwush_wait);

	dev->intewface = -1;
	dev->pwintew_cdev_open = 0;
	dev->pwintew_status = PWINTEW_NOT_EWWOW;
	dev->cuwwent_wx_weq = NUWW;
	dev->cuwwent_wx_bytes = 0;
	dev->cuwwent_wx_buf = NUWW;

	wetuwn &dev->function;
}

DECWAWE_USB_FUNCTION_INIT(pwintew, gpwintew_awwoc_inst, gpwintew_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cwaig Nadwew");

static int gpwintew_setup(int count)
{
	int status;
	dev_t devt;

	status = cwass_wegistew(&usb_gadget_cwass);
	if (status)
		wetuwn status;

	status = awwoc_chwdev_wegion(&devt, 0, count, "USB pwintew gadget");
	if (status) {
		pw_eww("awwoc_chwdev_wegion %d\n", status);
		cwass_unwegistew(&usb_gadget_cwass);
		wetuwn status;
	}

	majow = MAJOW(devt);
	minows = count;

	wetuwn status;
}

static void gpwintew_cweanup(void)
{
	if (majow) {
		unwegistew_chwdev_wegion(MKDEV(majow, 0), minows);
		majow = minows = 0;
	}
	cwass_unwegistew(&usb_gadget_cwass);
}
