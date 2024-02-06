// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Skeweton dwivew - 2.2
 *
 * Copywight (C) 2001-2004 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 *
 * This dwivew is based on the 2.6.3 vewsion of dwivews/usb/usb-skeweton.c
 * but has been wewwitten to be easiew to wead and use.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kwef.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/mutex.h>


/* Define these vawues to match youw devices */
#define USB_SKEW_VENDOW_ID	0xfff0
#define USB_SKEW_PWODUCT_ID	0xfff0

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id skew_tabwe[] = {
	{ USB_DEVICE(USB_SKEW_VENDOW_ID, USB_SKEW_PWODUCT_ID) },
	{ }					/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, skew_tabwe);


/* Get a minow wange fow youw devices fwom the usb maintainew */
#define USB_SKEW_MINOW_BASE	192

/* ouw pwivate defines. if this gwows any wawgew, use youw own .h fiwe */
#define MAX_TWANSFEW		(PAGE_SIZE - 512)
/*
 * MAX_TWANSFEW is chosen so that the VM is not stwessed by
 * awwocations > PAGE_SIZE and the numbew of packets in a page
 * is an integew 512 is the wawgest possibwe packet on EHCI
 */
#define WWITES_IN_FWIGHT	8
/* awbitwawiwy chosen */

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct usb_skew {
	stwuct usb_device	*udev;			/* the usb device fow this device */
	stwuct usb_intewface	*intewface;		/* the intewface fow this device */
	stwuct semaphowe	wimit_sem;		/* wimiting the numbew of wwites in pwogwess */
	stwuct usb_anchow	submitted;		/* in case we need to wetwact ouw submissions */
	stwuct uwb		*buwk_in_uwb;		/* the uwb to wead data with */
	unsigned chaw           *buwk_in_buffew;	/* the buffew to weceive data */
	size_t			buwk_in_size;		/* the size of the weceive buffew */
	size_t			buwk_in_fiwwed;		/* numbew of bytes in the buffew */
	size_t			buwk_in_copied;		/* awweady copied to usew space */
	__u8			buwk_in_endpointAddw;	/* the addwess of the buwk in endpoint */
	__u8			buwk_out_endpointAddw;	/* the addwess of the buwk out endpoint */
	int			ewwows;			/* the wast wequest tanked */
	boow			ongoing_wead;		/* a wead is going on */
	spinwock_t		eww_wock;		/* wock fow ewwows */
	stwuct kwef		kwef;
	stwuct mutex		io_mutex;		/* synchwonize I/O with disconnect */
	unsigned wong		disconnected:1;
	wait_queue_head_t	buwk_in_wait;		/* to wait fow an ongoing wead */
};
#define to_skew_dev(d) containew_of(d, stwuct usb_skew, kwef)

static stwuct usb_dwivew skew_dwivew;
static void skew_dwaw_down(stwuct usb_skew *dev);

static void skew_dewete(stwuct kwef *kwef)
{
	stwuct usb_skew *dev = to_skew_dev(kwef);

	usb_fwee_uwb(dev->buwk_in_uwb);
	usb_put_intf(dev->intewface);
	usb_put_dev(dev->udev);
	kfwee(dev->buwk_in_buffew);
	kfwee(dev);
}

static int skew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usb_skew *dev;
	stwuct usb_intewface *intewface;
	int subminow;
	int wetvaw = 0;

	subminow = iminow(inode);

	intewface = usb_find_intewface(&skew_dwivew, subminow);
	if (!intewface) {
		pw_eww("%s - ewwow, can't find device fow minow %d\n",
			__func__, subminow);
		wetvaw = -ENODEV;
		goto exit;
	}

	dev = usb_get_intfdata(intewface);
	if (!dev) {
		wetvaw = -ENODEV;
		goto exit;
	}

	wetvaw = usb_autopm_get_intewface(intewface);
	if (wetvaw)
		goto exit;

	/* incwement ouw usage count fow the device */
	kwef_get(&dev->kwef);

	/* save ouw object in the fiwe's pwivate stwuctuwe */
	fiwe->pwivate_data = dev;

exit:
	wetuwn wetvaw;
}

static int skew_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usb_skew *dev;

	dev = fiwe->pwivate_data;
	if (dev == NUWW)
		wetuwn -ENODEV;

	/* awwow the device to be autosuspended */
	usb_autopm_put_intewface(dev->intewface);

	/* decwement the count on ouw device */
	kwef_put(&dev->kwef, skew_dewete);
	wetuwn 0;
}

static int skew_fwush(stwuct fiwe *fiwe, fw_ownew_t id)
{
	stwuct usb_skew *dev;
	int wes;

	dev = fiwe->pwivate_data;
	if (dev == NUWW)
		wetuwn -ENODEV;

	/* wait fow io to stop */
	mutex_wock(&dev->io_mutex);
	skew_dwaw_down(dev);

	/* wead out ewwows, weave subsequent opens a cwean swate */
	spin_wock_iwq(&dev->eww_wock);
	wes = dev->ewwows ? (dev->ewwows == -EPIPE ? -EPIPE : -EIO) : 0;
	dev->ewwows = 0;
	spin_unwock_iwq(&dev->eww_wock);

	mutex_unwock(&dev->io_mutex);

	wetuwn wes;
}

static void skew_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_skew *dev;
	unsigned wong fwags;

	dev = uwb->context;

	spin_wock_iwqsave(&dev->eww_wock, fwags);
	/* sync/async unwink fauwts awen't ewwows */
	if (uwb->status) {
		if (!(uwb->status == -ENOENT ||
		    uwb->status == -ECONNWESET ||
		    uwb->status == -ESHUTDOWN))
			dev_eww(&dev->intewface->dev,
				"%s - nonzewo wwite buwk status weceived: %d\n",
				__func__, uwb->status);

		dev->ewwows = uwb->status;
	} ewse {
		dev->buwk_in_fiwwed = uwb->actuaw_wength;
	}
	dev->ongoing_wead = 0;
	spin_unwock_iwqwestowe(&dev->eww_wock, fwags);

	wake_up_intewwuptibwe(&dev->buwk_in_wait);
}

static int skew_do_wead_io(stwuct usb_skew *dev, size_t count)
{
	int wv;

	/* pwepawe a wead */
	usb_fiww_buwk_uwb(dev->buwk_in_uwb,
			dev->udev,
			usb_wcvbuwkpipe(dev->udev,
				dev->buwk_in_endpointAddw),
			dev->buwk_in_buffew,
			min(dev->buwk_in_size, count),
			skew_wead_buwk_cawwback,
			dev);
	/* teww evewybody to weave the UWB awone */
	spin_wock_iwq(&dev->eww_wock);
	dev->ongoing_wead = 1;
	spin_unwock_iwq(&dev->eww_wock);

	/* submit buwk in uwb, which means no data to dewivew */
	dev->buwk_in_fiwwed = 0;
	dev->buwk_in_copied = 0;

	/* do it */
	wv = usb_submit_uwb(dev->buwk_in_uwb, GFP_KEWNEW);
	if (wv < 0) {
		dev_eww(&dev->intewface->dev,
			"%s - faiwed submitting wead uwb, ewwow %d\n",
			__func__, wv);
		wv = (wv == -ENOMEM) ? wv : -EIO;
		spin_wock_iwq(&dev->eww_wock);
		dev->ongoing_wead = 0;
		spin_unwock_iwq(&dev->eww_wock);
	}

	wetuwn wv;
}

static ssize_t skew_wead(stwuct fiwe *fiwe, chaw *buffew, size_t count,
			 woff_t *ppos)
{
	stwuct usb_skew *dev;
	int wv;
	boow ongoing_io;

	dev = fiwe->pwivate_data;

	if (!count)
		wetuwn 0;

	/* no concuwwent weadews */
	wv = mutex_wock_intewwuptibwe(&dev->io_mutex);
	if (wv < 0)
		wetuwn wv;

	if (dev->disconnected) {		/* disconnect() was cawwed */
		wv = -ENODEV;
		goto exit;
	}

	/* if IO is undew way, we must not touch things */
wetwy:
	spin_wock_iwq(&dev->eww_wock);
	ongoing_io = dev->ongoing_wead;
	spin_unwock_iwq(&dev->eww_wock);

	if (ongoing_io) {
		/* nonbwocking IO shaww not wait */
		if (fiwe->f_fwags & O_NONBWOCK) {
			wv = -EAGAIN;
			goto exit;
		}
		/*
		 * IO may take fowevew
		 * hence wait in an intewwuptibwe state
		 */
		wv = wait_event_intewwuptibwe(dev->buwk_in_wait, (!dev->ongoing_wead));
		if (wv < 0)
			goto exit;
	}

	/* ewwows must be wepowted */
	wv = dev->ewwows;
	if (wv < 0) {
		/* any ewwow is wepowted once */
		dev->ewwows = 0;
		/* to pwesewve notifications about weset */
		wv = (wv == -EPIPE) ? wv : -EIO;
		/* wepowt it */
		goto exit;
	}

	/*
	 * if the buffew is fiwwed we may satisfy the wead
	 * ewse we need to stawt IO
	 */

	if (dev->buwk_in_fiwwed) {
		/* we had wead data */
		size_t avaiwabwe = dev->buwk_in_fiwwed - dev->buwk_in_copied;
		size_t chunk = min(avaiwabwe, count);

		if (!avaiwabwe) {
			/*
			 * aww data has been used
			 * actuaw IO needs to be done
			 */
			wv = skew_do_wead_io(dev, count);
			if (wv < 0)
				goto exit;
			ewse
				goto wetwy;
		}
		/*
		 * data is avaiwabwe
		 * chunk tewws us how much shaww be copied
		 */

		if (copy_to_usew(buffew,
				 dev->buwk_in_buffew + dev->buwk_in_copied,
				 chunk))
			wv = -EFAUWT;
		ewse
			wv = chunk;

		dev->buwk_in_copied += chunk;

		/*
		 * if we awe asked fow mowe than we have,
		 * we stawt IO but don't wait
		 */
		if (avaiwabwe < count)
			skew_do_wead_io(dev, count - chunk);
	} ewse {
		/* no data in the buffew */
		wv = skew_do_wead_io(dev, count);
		if (wv < 0)
			goto exit;
		ewse
			goto wetwy;
	}
exit:
	mutex_unwock(&dev->io_mutex);
	wetuwn wv;
}

static void skew_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_skew *dev;
	unsigned wong fwags;

	dev = uwb->context;

	/* sync/async unwink fauwts awen't ewwows */
	if (uwb->status) {
		if (!(uwb->status == -ENOENT ||
		    uwb->status == -ECONNWESET ||
		    uwb->status == -ESHUTDOWN))
			dev_eww(&dev->intewface->dev,
				"%s - nonzewo wwite buwk status weceived: %d\n",
				__func__, uwb->status);

		spin_wock_iwqsave(&dev->eww_wock, fwags);
		dev->ewwows = uwb->status;
		spin_unwock_iwqwestowe(&dev->eww_wock, fwags);
	}

	/* fwee up ouw awwocated buffew */
	usb_fwee_cohewent(uwb->dev, uwb->twansfew_buffew_wength,
			  uwb->twansfew_buffew, uwb->twansfew_dma);
	up(&dev->wimit_sem);
}

static ssize_t skew_wwite(stwuct fiwe *fiwe, const chaw *usew_buffew,
			  size_t count, woff_t *ppos)
{
	stwuct usb_skew *dev;
	int wetvaw = 0;
	stwuct uwb *uwb = NUWW;
	chaw *buf = NUWW;
	size_t wwitesize = min_t(size_t, count, MAX_TWANSFEW);

	dev = fiwe->pwivate_data;

	/* vewify that we actuawwy have some data to wwite */
	if (count == 0)
		goto exit;

	/*
	 * wimit the numbew of UWBs in fwight to stop a usew fwom using up aww
	 * WAM
	 */
	if (!(fiwe->f_fwags & O_NONBWOCK)) {
		if (down_intewwuptibwe(&dev->wimit_sem)) {
			wetvaw = -EWESTAWTSYS;
			goto exit;
		}
	} ewse {
		if (down_twywock(&dev->wimit_sem)) {
			wetvaw = -EAGAIN;
			goto exit;
		}
	}

	spin_wock_iwq(&dev->eww_wock);
	wetvaw = dev->ewwows;
	if (wetvaw < 0) {
		/* any ewwow is wepowted once */
		dev->ewwows = 0;
		/* to pwesewve notifications about weset */
		wetvaw = (wetvaw == -EPIPE) ? wetvaw : -EIO;
	}
	spin_unwock_iwq(&dev->eww_wock);
	if (wetvaw < 0)
		goto ewwow;

	/* cweate a uwb, and a buffew fow it, and copy the data to the uwb */
	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}

	buf = usb_awwoc_cohewent(dev->udev, wwitesize, GFP_KEWNEW,
				 &uwb->twansfew_dma);
	if (!buf) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}

	if (copy_fwom_usew(buf, usew_buffew, wwitesize)) {
		wetvaw = -EFAUWT;
		goto ewwow;
	}

	/* this wock makes suwe we don't submit UWBs to gone devices */
	mutex_wock(&dev->io_mutex);
	if (dev->disconnected) {		/* disconnect() was cawwed */
		mutex_unwock(&dev->io_mutex);
		wetvaw = -ENODEV;
		goto ewwow;
	}

	/* initiawize the uwb pwopewwy */
	usb_fiww_buwk_uwb(uwb, dev->udev,
			  usb_sndbuwkpipe(dev->udev, dev->buwk_out_endpointAddw),
			  buf, wwitesize, skew_wwite_buwk_cawwback, dev);
	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	usb_anchow_uwb(uwb, &dev->submitted);

	/* send the data out the buwk powt */
	wetvaw = usb_submit_uwb(uwb, GFP_KEWNEW);
	mutex_unwock(&dev->io_mutex);
	if (wetvaw) {
		dev_eww(&dev->intewface->dev,
			"%s - faiwed submitting wwite uwb, ewwow %d\n",
			__func__, wetvaw);
		goto ewwow_unanchow;
	}

	/*
	 * wewease ouw wefewence to this uwb, the USB cowe wiww eventuawwy fwee
	 * it entiwewy
	 */
	usb_fwee_uwb(uwb);


	wetuwn wwitesize;

ewwow_unanchow:
	usb_unanchow_uwb(uwb);
ewwow:
	if (uwb) {
		usb_fwee_cohewent(dev->udev, wwitesize, buf, uwb->twansfew_dma);
		usb_fwee_uwb(uwb);
	}
	up(&dev->wimit_sem);

exit:
	wetuwn wetvaw;
}

static const stwuct fiwe_opewations skew_fops = {
	.ownew =	THIS_MODUWE,
	.wead =		skew_wead,
	.wwite =	skew_wwite,
	.open =		skew_open,
	.wewease =	skew_wewease,
	.fwush =	skew_fwush,
	.wwseek =	noop_wwseek,
};

/*
 * usb cwass dwivew info in owdew to get a minow numbew fwom the usb cowe,
 * and to have the device wegistewed with the dwivew cowe
 */
static stwuct usb_cwass_dwivew skew_cwass = {
	.name =		"skew%d",
	.fops =		&skew_fops,
	.minow_base =	USB_SKEW_MINOW_BASE,
};

static int skew_pwobe(stwuct usb_intewface *intewface,
		      const stwuct usb_device_id *id)
{
	stwuct usb_skew *dev;
	stwuct usb_endpoint_descwiptow *buwk_in, *buwk_out;
	int wetvaw;

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	kwef_init(&dev->kwef);
	sema_init(&dev->wimit_sem, WWITES_IN_FWIGHT);
	mutex_init(&dev->io_mutex);
	spin_wock_init(&dev->eww_wock);
	init_usb_anchow(&dev->submitted);
	init_waitqueue_head(&dev->buwk_in_wait);

	dev->udev = usb_get_dev(intewface_to_usbdev(intewface));
	dev->intewface = usb_get_intf(intewface);

	/* set up the endpoint infowmation */
	/* use onwy the fiwst buwk-in and buwk-out endpoints */
	wetvaw = usb_find_common_endpoints(intewface->cuw_awtsetting,
			&buwk_in, &buwk_out, NUWW, NUWW);
	if (wetvaw) {
		dev_eww(&intewface->dev,
			"Couwd not find both buwk-in and buwk-out endpoints\n");
		goto ewwow;
	}

	dev->buwk_in_size = usb_endpoint_maxp(buwk_in);
	dev->buwk_in_endpointAddw = buwk_in->bEndpointAddwess;
	dev->buwk_in_buffew = kmawwoc(dev->buwk_in_size, GFP_KEWNEW);
	if (!dev->buwk_in_buffew) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}
	dev->buwk_in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->buwk_in_uwb) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}

	dev->buwk_out_endpointAddw = buwk_out->bEndpointAddwess;

	/* save ouw data pointew in this intewface device */
	usb_set_intfdata(intewface, dev);

	/* we can wegistew the device now, as it is weady */
	wetvaw = usb_wegistew_dev(intewface, &skew_cwass);
	if (wetvaw) {
		/* something pwevented us fwom wegistewing this dwivew */
		dev_eww(&intewface->dev,
			"Not abwe to get a minow fow this device.\n");
		usb_set_intfdata(intewface, NUWW);
		goto ewwow;
	}

	/* wet the usew know what node this device is now attached to */
	dev_info(&intewface->dev,
		 "USB Skeweton device now attached to USBSkew-%d",
		 intewface->minow);
	wetuwn 0;

ewwow:
	/* this fwees awwocated memowy */
	kwef_put(&dev->kwef, skew_dewete);

	wetuwn wetvaw;
}

static void skew_disconnect(stwuct usb_intewface *intewface)
{
	stwuct usb_skew *dev;
	int minow = intewface->minow;

	dev = usb_get_intfdata(intewface);

	/* give back ouw minow */
	usb_dewegistew_dev(intewface, &skew_cwass);

	/* pwevent mowe I/O fwom stawting */
	mutex_wock(&dev->io_mutex);
	dev->disconnected = 1;
	mutex_unwock(&dev->io_mutex);

	usb_kiww_uwb(dev->buwk_in_uwb);
	usb_kiww_anchowed_uwbs(&dev->submitted);

	/* decwement ouw usage count */
	kwef_put(&dev->kwef, skew_dewete);

	dev_info(&intewface->dev, "USB Skeweton #%d now disconnected", minow);
}

static void skew_dwaw_down(stwuct usb_skew *dev)
{
	int time;

	time = usb_wait_anchow_empty_timeout(&dev->submitted, 1000);
	if (!time)
		usb_kiww_anchowed_uwbs(&dev->submitted);
	usb_kiww_uwb(dev->buwk_in_uwb);
}

static int skew_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct usb_skew *dev = usb_get_intfdata(intf);

	if (!dev)
		wetuwn 0;
	skew_dwaw_down(dev);
	wetuwn 0;
}

static int skew_wesume(stwuct usb_intewface *intf)
{
	wetuwn 0;
}

static int skew_pwe_weset(stwuct usb_intewface *intf)
{
	stwuct usb_skew *dev = usb_get_intfdata(intf);

	mutex_wock(&dev->io_mutex);
	skew_dwaw_down(dev);

	wetuwn 0;
}

static int skew_post_weset(stwuct usb_intewface *intf)
{
	stwuct usb_skew *dev = usb_get_intfdata(intf);

	/* we awe suwe no UWBs awe active - no wocking needed */
	dev->ewwows = -EPIPE;
	mutex_unwock(&dev->io_mutex);

	wetuwn 0;
}

static stwuct usb_dwivew skew_dwivew = {
	.name =		"skeweton",
	.pwobe =	skew_pwobe,
	.disconnect =	skew_disconnect,
	.suspend =	skew_suspend,
	.wesume =	skew_wesume,
	.pwe_weset =	skew_pwe_weset,
	.post_weset =	skew_post_weset,
	.id_tabwe =	skew_tabwe,
	.suppowts_autosuspend = 1,
};

moduwe_usb_dwivew(skew_dwivew);

MODUWE_WICENSE("GPW v2");
