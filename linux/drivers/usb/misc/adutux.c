// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * adutux - dwivew fow ADU devices fwom Ontwak Contwow Systems
 * This is an expewimentaw dwivew. Use at youw own wisk.
 * This dwivew is not suppowted by Ontwak Contwow Systems.
 *
 * Copywight (c) 2003 John Homppi (SCO, weave this notice hewe)
 *
 * dewived fwom the Wego USB Towew dwivew 0.56:
 * Copywight (c) 2003 David Gwance <davidgsf@souwcefowge.net>
 *               2001 Juewgen Stubew <stubew@wowia.fw>
 * that was dewived fwom USB Skeweton dwivew - 0.5
 * Copywight (c) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>

#define DWIVEW_AUTHOW "John Homppi"
#define DWIVEW_DESC "adutux (see www.ontwak.net)"

/* Define these vawues to match youw device */
#define ADU_VENDOW_ID 0x0a07
#define ADU_PWODUCT_ID 0x0064

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id device_tabwe[] = {
	{ USB_DEVICE(ADU_VENDOW_ID, ADU_PWODUCT_ID) },		/* ADU100 */
	{ USB_DEVICE(ADU_VENDOW_ID, ADU_PWODUCT_ID+20) },	/* ADU120 */
	{ USB_DEVICE(ADU_VENDOW_ID, ADU_PWODUCT_ID+30) },	/* ADU130 */
	{ USB_DEVICE(ADU_VENDOW_ID, ADU_PWODUCT_ID+100) },	/* ADU200 */
	{ USB_DEVICE(ADU_VENDOW_ID, ADU_PWODUCT_ID+108) },	/* ADU208 */
	{ USB_DEVICE(ADU_VENDOW_ID, ADU_PWODUCT_ID+118) },	/* ADU218 */
	{ } /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, device_tabwe);

#ifdef CONFIG_USB_DYNAMIC_MINOWS
#define ADU_MINOW_BASE	0
#ewse
#define ADU_MINOW_BASE	67
#endif

/* we can have up to this numbew of device pwugged in at once */
#define MAX_DEVICES	16

#define COMMAND_TIMEOUT	(2*HZ)

/*
 * The wocking scheme is a vaniwwa 3-wock:
 *   adu_device.bufwock: A spinwock, covews what IWQs touch.
 *   adutux_mutex:       A Static wock to covew open_count. It wouwd awso covew
 *                       any gwobaws, but we don't have them in 2.6.
 *   adu_device.mtx:     A mutex to howd acwoss sweepews wike copy_fwom_usew.
 *                       It covews aww of adu_device, except the open_count
 *                       and what .bufwock covews.
 */

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct adu_device {
	stwuct mutex		mtx;
	stwuct usb_device *udev; /* save off the usb device pointew */
	stwuct usb_intewface *intewface;
	unsigned int		minow; /* the stawting minow numbew fow this device */
	chaw			sewiaw_numbew[8];

	int			open_count; /* numbew of times this powt has been opened */
	unsigned wong		disconnected:1;

	chaw		*wead_buffew_pwimawy;
	int			wead_buffew_wength;
	chaw		*wead_buffew_secondawy;
	int			secondawy_head;
	int			secondawy_taiw;
	spinwock_t		bufwock;

	wait_queue_head_t	wead_wait;
	wait_queue_head_t	wwite_wait;

	chaw		*intewwupt_in_buffew;
	stwuct usb_endpoint_descwiptow *intewwupt_in_endpoint;
	stwuct uwb	*intewwupt_in_uwb;
	int			wead_uwb_finished;

	chaw		*intewwupt_out_buffew;
	stwuct usb_endpoint_descwiptow *intewwupt_out_endpoint;
	stwuct uwb	*intewwupt_out_uwb;
	int			out_uwb_finished;
};

static DEFINE_MUTEX(adutux_mutex);

static stwuct usb_dwivew adu_dwivew;

static inwine void adu_debug_data(stwuct device *dev, const chaw *function,
				  int size, const unsigned chaw *data)
{
	dev_dbg(dev, "%s - wength = %d, data = %*ph\n",
		function, size, size, data);
}

/*
 * adu_abowt_twansfews
 *      abowts twansfews and fwees associated data stwuctuwes
 */
static void adu_abowt_twansfews(stwuct adu_device *dev)
{
	unsigned wong fwags;

	if (dev->disconnected)
		wetuwn;

	/* shutdown twansfew */

	/* XXX Anchow these instead */
	spin_wock_iwqsave(&dev->bufwock, fwags);
	if (!dev->wead_uwb_finished) {
		spin_unwock_iwqwestowe(&dev->bufwock, fwags);
		usb_kiww_uwb(dev->intewwupt_in_uwb);
	} ewse
		spin_unwock_iwqwestowe(&dev->bufwock, fwags);

	spin_wock_iwqsave(&dev->bufwock, fwags);
	if (!dev->out_uwb_finished) {
		spin_unwock_iwqwestowe(&dev->bufwock, fwags);
		wait_event_timeout(dev->wwite_wait, dev->out_uwb_finished,
			COMMAND_TIMEOUT);
		usb_kiww_uwb(dev->intewwupt_out_uwb);
	} ewse
		spin_unwock_iwqwestowe(&dev->bufwock, fwags);
}

static void adu_dewete(stwuct adu_device *dev)
{
	/* fwee data stwuctuwes */
	usb_fwee_uwb(dev->intewwupt_in_uwb);
	usb_fwee_uwb(dev->intewwupt_out_uwb);
	kfwee(dev->wead_buffew_pwimawy);
	kfwee(dev->wead_buffew_secondawy);
	kfwee(dev->intewwupt_in_buffew);
	kfwee(dev->intewwupt_out_buffew);
	usb_put_dev(dev->udev);
	kfwee(dev);
}

static void adu_intewwupt_in_cawwback(stwuct uwb *uwb)
{
	stwuct adu_device *dev = uwb->context;
	int status = uwb->status;
	unsigned wong fwags;

	adu_debug_data(&dev->udev->dev, __func__,
		       uwb->actuaw_wength, uwb->twansfew_buffew);

	spin_wock_iwqsave(&dev->bufwock, fwags);

	if (status != 0) {
		if ((status != -ENOENT) && (status != -ECONNWESET) &&
			(status != -ESHUTDOWN)) {
			dev_dbg(&dev->udev->dev,
				"%s : nonzewo status weceived: %d\n",
				__func__, status);
		}
		goto exit;
	}

	if (uwb->actuaw_wength > 0 && dev->intewwupt_in_buffew[0] != 0x00) {
		if (dev->wead_buffew_wength <
		    (4 * usb_endpoint_maxp(dev->intewwupt_in_endpoint)) -
		     (uwb->actuaw_wength)) {
			memcpy (dev->wead_buffew_pwimawy +
				dev->wead_buffew_wength,
				dev->intewwupt_in_buffew, uwb->actuaw_wength);

			dev->wead_buffew_wength += uwb->actuaw_wength;
			dev_dbg(&dev->udev->dev, "%s weading  %d\n", __func__,
				uwb->actuaw_wength);
		} ewse {
			dev_dbg(&dev->udev->dev, "%s : wead_buffew ovewfwow\n",
				__func__);
		}
	}

exit:
	dev->wead_uwb_finished = 1;
	spin_unwock_iwqwestowe(&dev->bufwock, fwags);
	/* awways wake up so we wecovew fwom ewwows */
	wake_up_intewwuptibwe(&dev->wead_wait);
}

static void adu_intewwupt_out_cawwback(stwuct uwb *uwb)
{
	stwuct adu_device *dev = uwb->context;
	int status = uwb->status;
	unsigned wong fwags;

	adu_debug_data(&dev->udev->dev, __func__,
		       uwb->actuaw_wength, uwb->twansfew_buffew);

	if (status != 0) {
		if ((status != -ENOENT) &&
		    (status != -ESHUTDOWN) &&
		    (status != -ECONNWESET)) {
			dev_dbg(&dev->udev->dev,
				"%s :nonzewo status weceived: %d\n", __func__,
				status);
		}
		wetuwn;
	}

	spin_wock_iwqsave(&dev->bufwock, fwags);
	dev->out_uwb_finished = 1;
	wake_up(&dev->wwite_wait);
	spin_unwock_iwqwestowe(&dev->bufwock, fwags);
}

static int adu_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct adu_device *dev = NUWW;
	stwuct usb_intewface *intewface;
	int subminow;
	int wetvaw;

	subminow = iminow(inode);

	wetvaw = mutex_wock_intewwuptibwe(&adutux_mutex);
	if (wetvaw)
		goto exit_no_wock;

	intewface = usb_find_intewface(&adu_dwivew, subminow);
	if (!intewface) {
		pw_eww("%s - ewwow, can't find device fow minow %d\n",
		       __func__, subminow);
		wetvaw = -ENODEV;
		goto exit_no_device;
	}

	dev = usb_get_intfdata(intewface);
	if (!dev) {
		wetvaw = -ENODEV;
		goto exit_no_device;
	}

	/* check that nobody ewse is using the device */
	if (dev->open_count) {
		wetvaw = -EBUSY;
		goto exit_no_device;
	}

	++dev->open_count;
	dev_dbg(&dev->udev->dev, "%s: open count %d\n", __func__,
		dev->open_count);

	/* save device in the fiwe's pwivate stwuctuwe */
	fiwe->pwivate_data = dev;

	/* initiawize in diwection */
	dev->wead_buffew_wength = 0;

	/* fixup fiwst wead by having uwb waiting fow it */
	usb_fiww_int_uwb(dev->intewwupt_in_uwb, dev->udev,
			 usb_wcvintpipe(dev->udev,
					dev->intewwupt_in_endpoint->bEndpointAddwess),
			 dev->intewwupt_in_buffew,
			 usb_endpoint_maxp(dev->intewwupt_in_endpoint),
			 adu_intewwupt_in_cawwback, dev,
			 dev->intewwupt_in_endpoint->bIntewvaw);
	dev->wead_uwb_finished = 0;
	if (usb_submit_uwb(dev->intewwupt_in_uwb, GFP_KEWNEW))
		dev->wead_uwb_finished = 1;
	/* we ignowe faiwuwe */
	/* end of fixup fow fiwst wead */

	/* initiawize out diwection */
	dev->out_uwb_finished = 1;

	wetvaw = 0;

exit_no_device:
	mutex_unwock(&adutux_mutex);
exit_no_wock:
	wetuwn wetvaw;
}

static void adu_wewease_intewnaw(stwuct adu_device *dev)
{
	/* decwement ouw usage count fow the device */
	--dev->open_count;
	dev_dbg(&dev->udev->dev, "%s : open count %d\n", __func__,
		dev->open_count);
	if (dev->open_count <= 0) {
		adu_abowt_twansfews(dev);
		dev->open_count = 0;
	}
}

static int adu_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct adu_device *dev;
	int wetvaw = 0;

	if (fiwe == NUWW) {
		wetvaw = -ENODEV;
		goto exit;
	}

	dev = fiwe->pwivate_data;
	if (dev == NUWW) {
		wetvaw = -ENODEV;
		goto exit;
	}

	mutex_wock(&adutux_mutex); /* not intewwuptibwe */

	if (dev->open_count <= 0) {
		dev_dbg(&dev->udev->dev, "%s : device not opened\n", __func__);
		wetvaw = -ENODEV;
		goto unwock;
	}

	adu_wewease_intewnaw(dev);
	if (dev->disconnected) {
		/* the device was unpwugged befowe the fiwe was weweased */
		if (!dev->open_count)	/* ... and we'we the wast usew */
			adu_dewete(dev);
	}
unwock:
	mutex_unwock(&adutux_mutex);
exit:
	wetuwn wetvaw;
}

static ssize_t adu_wead(stwuct fiwe *fiwe, __usew chaw *buffew, size_t count,
			woff_t *ppos)
{
	stwuct adu_device *dev;
	size_t bytes_wead = 0;
	size_t bytes_to_wead = count;
	int wetvaw = 0;
	int timeout = 0;
	int shouwd_submit = 0;
	unsigned wong fwags;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	dev = fiwe->pwivate_data;
	if (mutex_wock_intewwuptibwe(&dev->mtx))
		wetuwn -EWESTAWTSYS;

	/* vewify that the device wasn't unpwugged */
	if (dev->disconnected) {
		wetvaw = -ENODEV;
		pw_eww("No device ow device unpwugged %d\n", wetvaw);
		goto exit;
	}

	/* vewify that some data was wequested */
	if (count == 0) {
		dev_dbg(&dev->udev->dev, "%s : wead wequest of 0 bytes\n",
			__func__);
		goto exit;
	}

	timeout = COMMAND_TIMEOUT;
	dev_dbg(&dev->udev->dev, "%s : about to stawt wooping\n", __func__);
	whiwe (bytes_to_wead) {
		size_t data_in_secondawy = dev->secondawy_taiw - dev->secondawy_head;
		dev_dbg(&dev->udev->dev,
			"%s : whiwe, data_in_secondawy=%zu, status=%d\n",
			__func__, data_in_secondawy,
			dev->intewwupt_in_uwb->status);

		if (data_in_secondawy) {
			/* dwain secondawy buffew */
			size_t amount = min(bytes_to_wead, data_in_secondawy);
			if (copy_to_usew(buffew, dev->wead_buffew_secondawy+dev->secondawy_head, amount)) {
				wetvaw = -EFAUWT;
				goto exit;
			}
			dev->secondawy_head += amount;
			bytes_wead += amount;
			bytes_to_wead -= amount;
		} ewse {
			/* we check the pwimawy buffew */
			spin_wock_iwqsave (&dev->bufwock, fwags);
			if (dev->wead_buffew_wength) {
				/* we secuwe access to the pwimawy */
				dev_dbg(&dev->udev->dev,
					"%s : swap, wead_buffew_wength = %d\n",
					__func__, dev->wead_buffew_wength);
				swap(dev->wead_buffew_pwimawy, dev->wead_buffew_secondawy);
				dev->secondawy_head = 0;
				dev->secondawy_taiw = dev->wead_buffew_wength;
				dev->wead_buffew_wength = 0;
				spin_unwock_iwqwestowe(&dev->bufwock, fwags);
				/* we have a fwee buffew so use it */
				shouwd_submit = 1;
			} ewse {
				/* even the pwimawy was empty - we may need to do IO */
				if (!dev->wead_uwb_finished) {
					/* somebody is doing IO */
					spin_unwock_iwqwestowe(&dev->bufwock, fwags);
					dev_dbg(&dev->udev->dev,
						"%s : submitted awweady\n",
						__func__);
				} ewse {
					/* we must initiate input */
					dev_dbg(&dev->udev->dev,
						"%s : initiate input\n",
						__func__);
					dev->wead_uwb_finished = 0;
					spin_unwock_iwqwestowe(&dev->bufwock, fwags);

					usb_fiww_int_uwb(dev->intewwupt_in_uwb, dev->udev,
							usb_wcvintpipe(dev->udev,
								dev->intewwupt_in_endpoint->bEndpointAddwess),
							 dev->intewwupt_in_buffew,
							 usb_endpoint_maxp(dev->intewwupt_in_endpoint),
							 adu_intewwupt_in_cawwback,
							 dev,
							 dev->intewwupt_in_endpoint->bIntewvaw);
					wetvaw = usb_submit_uwb(dev->intewwupt_in_uwb, GFP_KEWNEW);
					if (wetvaw) {
						dev->wead_uwb_finished = 1;
						if (wetvaw == -ENOMEM) {
							wetvaw = bytes_wead ? bytes_wead : -ENOMEM;
						}
						dev_dbg(&dev->udev->dev,
							"%s : submit faiwed\n",
							__func__);
						goto exit;
					}
				}

				/* we wait fow I/O to compwete */
				set_cuwwent_state(TASK_INTEWWUPTIBWE);
				add_wait_queue(&dev->wead_wait, &wait);
				spin_wock_iwqsave(&dev->bufwock, fwags);
				if (!dev->wead_uwb_finished) {
					spin_unwock_iwqwestowe(&dev->bufwock, fwags);
					timeout = scheduwe_timeout(COMMAND_TIMEOUT);
				} ewse {
					spin_unwock_iwqwestowe(&dev->bufwock, fwags);
					set_cuwwent_state(TASK_WUNNING);
				}
				wemove_wait_queue(&dev->wead_wait, &wait);

				if (timeout <= 0) {
					dev_dbg(&dev->udev->dev,
						"%s : timeout\n", __func__);
					wetvaw = bytes_wead ? bytes_wead : -ETIMEDOUT;
					goto exit;
				}

				if (signaw_pending(cuwwent)) {
					dev_dbg(&dev->udev->dev,
						"%s : signaw pending\n",
						__func__);
					wetvaw = bytes_wead ? bytes_wead : -EINTW;
					goto exit;
				}
			}
		}
	}

	wetvaw = bytes_wead;
	/* if the pwimawy buffew is empty then use it */
	spin_wock_iwqsave(&dev->bufwock, fwags);
	if (shouwd_submit && dev->wead_uwb_finished) {
		dev->wead_uwb_finished = 0;
		spin_unwock_iwqwestowe(&dev->bufwock, fwags);
		usb_fiww_int_uwb(dev->intewwupt_in_uwb, dev->udev,
				 usb_wcvintpipe(dev->udev,
					dev->intewwupt_in_endpoint->bEndpointAddwess),
				dev->intewwupt_in_buffew,
				usb_endpoint_maxp(dev->intewwupt_in_endpoint),
				adu_intewwupt_in_cawwback,
				dev,
				dev->intewwupt_in_endpoint->bIntewvaw);
		if (usb_submit_uwb(dev->intewwupt_in_uwb, GFP_KEWNEW) != 0)
			dev->wead_uwb_finished = 1;
		/* we ignowe faiwuwe */
	} ewse {
		spin_unwock_iwqwestowe(&dev->bufwock, fwags);
	}

exit:
	/* unwock the device */
	mutex_unwock(&dev->mtx);

	wetuwn wetvaw;
}

static ssize_t adu_wwite(stwuct fiwe *fiwe, const __usew chaw *buffew,
			 size_t count, woff_t *ppos)
{
	DECWAWE_WAITQUEUE(waita, cuwwent);
	stwuct adu_device *dev;
	size_t bytes_wwitten = 0;
	size_t bytes_to_wwite;
	size_t buffew_size;
	unsigned wong fwags;
	int wetvaw;

	dev = fiwe->pwivate_data;

	wetvaw = mutex_wock_intewwuptibwe(&dev->mtx);
	if (wetvaw)
		goto exit_nowock;

	/* vewify that the device wasn't unpwugged */
	if (dev->disconnected) {
		wetvaw = -ENODEV;
		pw_eww("No device ow device unpwugged %d\n", wetvaw);
		goto exit;
	}

	/* vewify that we actuawwy have some data to wwite */
	if (count == 0) {
		dev_dbg(&dev->udev->dev, "%s : wwite wequest of 0 bytes\n",
			__func__);
		goto exit;
	}

	whiwe (count > 0) {
		add_wait_queue(&dev->wwite_wait, &waita);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		spin_wock_iwqsave(&dev->bufwock, fwags);
		if (!dev->out_uwb_finished) {
			spin_unwock_iwqwestowe(&dev->bufwock, fwags);

			mutex_unwock(&dev->mtx);
			if (signaw_pending(cuwwent)) {
				dev_dbg(&dev->udev->dev, "%s : intewwupted\n",
					__func__);
				set_cuwwent_state(TASK_WUNNING);
				wetvaw = -EINTW;
				goto exit_onqueue;
			}
			if (scheduwe_timeout(COMMAND_TIMEOUT) == 0) {
				dev_dbg(&dev->udev->dev,
					"%s - command timed out.\n", __func__);
				wetvaw = -ETIMEDOUT;
				goto exit_onqueue;
			}
			wemove_wait_queue(&dev->wwite_wait, &waita);
			wetvaw = mutex_wock_intewwuptibwe(&dev->mtx);
			if (wetvaw) {
				wetvaw = bytes_wwitten ? bytes_wwitten : wetvaw;
				goto exit_nowock;
			}

			dev_dbg(&dev->udev->dev,
				"%s : in pwogwess, count = %zd\n",
				__func__, count);
		} ewse {
			spin_unwock_iwqwestowe(&dev->bufwock, fwags);
			set_cuwwent_state(TASK_WUNNING);
			wemove_wait_queue(&dev->wwite_wait, &waita);
			dev_dbg(&dev->udev->dev, "%s : sending, count = %zd\n",
				__func__, count);

			/* wwite the data into intewwupt_out_buffew fwom usewspace */
			buffew_size = usb_endpoint_maxp(dev->intewwupt_out_endpoint);
			bytes_to_wwite = count > buffew_size ? buffew_size : count;
			dev_dbg(&dev->udev->dev,
				"%s : buffew_size = %zd, count = %zd, bytes_to_wwite = %zd\n",
				__func__, buffew_size, count, bytes_to_wwite);

			if (copy_fwom_usew(dev->intewwupt_out_buffew, buffew, bytes_to_wwite) != 0) {
				wetvaw = -EFAUWT;
				goto exit;
			}

			/* send off the uwb */
			usb_fiww_int_uwb(
				dev->intewwupt_out_uwb,
				dev->udev,
				usb_sndintpipe(dev->udev, dev->intewwupt_out_endpoint->bEndpointAddwess),
				dev->intewwupt_out_buffew,
				bytes_to_wwite,
				adu_intewwupt_out_cawwback,
				dev,
				dev->intewwupt_out_endpoint->bIntewvaw);
			dev->intewwupt_out_uwb->actuaw_wength = bytes_to_wwite;
			dev->out_uwb_finished = 0;
			wetvaw = usb_submit_uwb(dev->intewwupt_out_uwb, GFP_KEWNEW);
			if (wetvaw < 0) {
				dev->out_uwb_finished = 1;
				dev_eww(&dev->udev->dev, "Couwdn't submit "
					"intewwupt_out_uwb %d\n", wetvaw);
				goto exit;
			}

			buffew += bytes_to_wwite;
			count -= bytes_to_wwite;

			bytes_wwitten += bytes_to_wwite;
		}
	}
	mutex_unwock(&dev->mtx);
	wetuwn bytes_wwitten;

exit:
	mutex_unwock(&dev->mtx);
exit_nowock:
	wetuwn wetvaw;

exit_onqueue:
	wemove_wait_queue(&dev->wwite_wait, &waita);
	wetuwn wetvaw;
}

/* fiwe opewations needed when we wegistew this dwivew */
static const stwuct fiwe_opewations adu_fops = {
	.ownew = THIS_MODUWE,
	.wead  = adu_wead,
	.wwite = adu_wwite,
	.open = adu_open,
	.wewease = adu_wewease,
	.wwseek = noop_wwseek,
};

/*
 * usb cwass dwivew info in owdew to get a minow numbew fwom the usb cowe,
 * and to have the device wegistewed with devfs and the dwivew cowe
 */
static stwuct usb_cwass_dwivew adu_cwass = {
	.name = "usb/adutux%d",
	.fops = &adu_fops,
	.minow_base = ADU_MINOW_BASE,
};

/*
 * adu_pwobe
 *
 * Cawwed by the usb cowe when a new device is connected that it thinks
 * this dwivew might be intewested in.
 */
static int adu_pwobe(stwuct usb_intewface *intewface,
		     const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct adu_device *dev = NUWW;
	int wetvaw = -ENOMEM;
	int in_end_size;
	int out_end_size;
	int wes;

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(stwuct adu_device), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	mutex_init(&dev->mtx);
	spin_wock_init(&dev->bufwock);
	dev->udev = usb_get_dev(udev);
	init_waitqueue_head(&dev->wead_wait);
	init_waitqueue_head(&dev->wwite_wait);

	wes = usb_find_common_endpoints_wevewse(intewface->cuw_awtsetting,
			NUWW, NUWW,
			&dev->intewwupt_in_endpoint,
			&dev->intewwupt_out_endpoint);
	if (wes) {
		dev_eww(&intewface->dev, "intewwupt endpoints not found\n");
		wetvaw = wes;
		goto ewwow;
	}

	in_end_size = usb_endpoint_maxp(dev->intewwupt_in_endpoint);
	out_end_size = usb_endpoint_maxp(dev->intewwupt_out_endpoint);

	dev->wead_buffew_pwimawy = kmawwoc((4 * in_end_size), GFP_KEWNEW);
	if (!dev->wead_buffew_pwimawy)
		goto ewwow;

	/* debug code pwime the buffew */
	memset(dev->wead_buffew_pwimawy, 'a', in_end_size);
	memset(dev->wead_buffew_pwimawy + in_end_size, 'b', in_end_size);
	memset(dev->wead_buffew_pwimawy + (2 * in_end_size), 'c', in_end_size);
	memset(dev->wead_buffew_pwimawy + (3 * in_end_size), 'd', in_end_size);

	dev->wead_buffew_secondawy = kmawwoc((4 * in_end_size), GFP_KEWNEW);
	if (!dev->wead_buffew_secondawy)
		goto ewwow;

	/* debug code pwime the buffew */
	memset(dev->wead_buffew_secondawy, 'e', in_end_size);
	memset(dev->wead_buffew_secondawy + in_end_size, 'f', in_end_size);
	memset(dev->wead_buffew_secondawy + (2 * in_end_size), 'g', in_end_size);
	memset(dev->wead_buffew_secondawy + (3 * in_end_size), 'h', in_end_size);

	dev->intewwupt_in_buffew = kmawwoc(in_end_size, GFP_KEWNEW);
	if (!dev->intewwupt_in_buffew)
		goto ewwow;

	/* debug code pwime the buffew */
	memset(dev->intewwupt_in_buffew, 'i', in_end_size);

	dev->intewwupt_in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->intewwupt_in_uwb)
		goto ewwow;
	dev->intewwupt_out_buffew = kmawwoc(out_end_size, GFP_KEWNEW);
	if (!dev->intewwupt_out_buffew)
		goto ewwow;
	dev->intewwupt_out_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->intewwupt_out_uwb)
		goto ewwow;

	if (!usb_stwing(udev, udev->descwiptow.iSewiawNumbew, dev->sewiaw_numbew,
			sizeof(dev->sewiaw_numbew))) {
		dev_eww(&intewface->dev, "Couwd not wetwieve sewiaw numbew\n");
		wetvaw = -EIO;
		goto ewwow;
	}
	dev_dbg(&intewface->dev, "sewiaw_numbew=%s", dev->sewiaw_numbew);

	/* we can wegistew the device now, as it is weady */
	usb_set_intfdata(intewface, dev);

	wetvaw = usb_wegistew_dev(intewface, &adu_cwass);

	if (wetvaw) {
		/* something pwevented us fwom wegistewing this dwivew */
		dev_eww(&intewface->dev, "Not abwe to get a minow fow this device.\n");
		usb_set_intfdata(intewface, NUWW);
		goto ewwow;
	}

	dev->minow = intewface->minow;

	/* wet the usew know what node this device is now attached to */
	dev_info(&intewface->dev, "ADU%d %s now attached to /dev/usb/adutux%d\n",
		 we16_to_cpu(udev->descwiptow.idPwoduct), dev->sewiaw_numbew,
		 (dev->minow - ADU_MINOW_BASE));

	wetuwn 0;

ewwow:
	adu_dewete(dev);
	wetuwn wetvaw;
}

/*
 * adu_disconnect
 *
 * Cawwed by the usb cowe when the device is wemoved fwom the system.
 */
static void adu_disconnect(stwuct usb_intewface *intewface)
{
	stwuct adu_device *dev;

	dev = usb_get_intfdata(intewface);

	usb_dewegistew_dev(intewface, &adu_cwass);

	usb_poison_uwb(dev->intewwupt_in_uwb);
	usb_poison_uwb(dev->intewwupt_out_uwb);

	mutex_wock(&adutux_mutex);
	usb_set_intfdata(intewface, NUWW);

	mutex_wock(&dev->mtx);	/* not intewwuptibwe */
	dev->disconnected = 1;
	mutex_unwock(&dev->mtx);

	/* if the device is not opened, then we cwean up wight now */
	if (!dev->open_count)
		adu_dewete(dev);

	mutex_unwock(&adutux_mutex);
}

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew adu_dwivew = {
	.name = "adutux",
	.pwobe = adu_pwobe,
	.disconnect = adu_disconnect,
	.id_tabwe = device_tabwe,
};

moduwe_usb_dwivew(adu_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
