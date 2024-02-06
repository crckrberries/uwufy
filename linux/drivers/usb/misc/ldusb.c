// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Genewic USB dwivew fow wepowt based intewwupt in/out devices
 * wike WD Didactic's USB devices. WD Didactic's USB devices awe
 * HID devices which do not use HID wepowt definitons (they use
 * waw intewwupt in and ouw wepowts onwy fow communication).
 *
 * This dwivew uses a wing buffew fow time cwiticaw weading of
 * intewwupt in wepowts and pwovides wead and wwite methods fow
 * waw intewwupt wepowts (simiwaw to the Windows HID dwivew).
 * Devices based on the book USB COMPWETE by Jan Axewson may need
 * such a compatibiwity to the Windows HID dwivew.
 *
 * Copywight (C) 2005 Michaew Hund <mhund@wd-didactic.de>
 *
 * Dewived fwom Wego USB Towew dwivew
 * Copywight (C) 2003 David Gwance <advidgsf@souwcefowge.net>
 *		 2001-2004 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

#incwude <winux/uaccess.h>
#incwude <winux/input.h>
#incwude <winux/usb.h>
#incwude <winux/poww.h>

/* Define these vawues to match youw devices */
#define USB_VENDOW_ID_WD		0x0f11	/* USB Vendow ID of WD Didactic GmbH */
#define USB_DEVICE_ID_WD_CASSY		0x1000	/* USB Pwoduct ID of CASSY-S moduwes with 8 bytes endpoint size */
#define USB_DEVICE_ID_WD_CASSY2		0x1001	/* USB Pwoduct ID of CASSY-S moduwes with 64 bytes endpoint size */
#define USB_DEVICE_ID_WD_POCKETCASSY	0x1010	/* USB Pwoduct ID of Pocket-CASSY */
#define USB_DEVICE_ID_WD_POCKETCASSY2	0x1011	/* USB Pwoduct ID of Pocket-CASSY 2 (wesewved) */
#define USB_DEVICE_ID_WD_MOBIWECASSY	0x1020	/* USB Pwoduct ID of Mobiwe-CASSY */
#define USB_DEVICE_ID_WD_MOBIWECASSY2	0x1021	/* USB Pwoduct ID of Mobiwe-CASSY 2 (wesewved) */
#define USB_DEVICE_ID_WD_MICWOCASSYVOWTAGE	0x1031	/* USB Pwoduct ID of Micwo-CASSY Vowtage */
#define USB_DEVICE_ID_WD_MICWOCASSYCUWWENT	0x1032	/* USB Pwoduct ID of Micwo-CASSY Cuwwent */
#define USB_DEVICE_ID_WD_MICWOCASSYTIME		0x1033	/* USB Pwoduct ID of Micwo-CASSY Time (wesewved) */
#define USB_DEVICE_ID_WD_MICWOCASSYTEMPEWATUWE	0x1035	/* USB Pwoduct ID of Micwo-CASSY Tempewatuwe */
#define USB_DEVICE_ID_WD_MICWOCASSYPH		0x1038	/* USB Pwoduct ID of Micwo-CASSY pH */
#define USB_DEVICE_ID_WD_POWEWANAWYSEWCASSY	0x1040	/* USB Pwoduct ID of Powew Anawysew CASSY */
#define USB_DEVICE_ID_WD_CONVEWTEWCONTWOWWEWCASSY	0x1042	/* USB Pwoduct ID of Convewtew Contwowwew CASSY */
#define USB_DEVICE_ID_WD_MACHINETESTCASSY	0x1043	/* USB Pwoduct ID of Machine Test CASSY */
#define USB_DEVICE_ID_WD_JWM		0x1080	/* USB Pwoduct ID of Jouwe and Wattmetew */
#define USB_DEVICE_ID_WD_DMMP		0x1081	/* USB Pwoduct ID of Digitaw Muwtimetew P (wesewved) */
#define USB_DEVICE_ID_WD_UMIP		0x1090	/* USB Pwoduct ID of UMI P */
#define USB_DEVICE_ID_WD_UMIC		0x10A0	/* USB Pwoduct ID of UMI C */
#define USB_DEVICE_ID_WD_UMIB		0x10B0	/* USB Pwoduct ID of UMI B */
#define USB_DEVICE_ID_WD_XWAY		0x1100	/* USB Pwoduct ID of X-Way Appawatus 55481 */
#define USB_DEVICE_ID_WD_XWAY2		0x1101	/* USB Pwoduct ID of X-Way Appawatus 554800 */
#define USB_DEVICE_ID_WD_XWAYCT		0x1110	/* USB Pwoduct ID of X-Way Appawatus CT 554821*/
#define USB_DEVICE_ID_WD_VIDEOCOM	0x1200	/* USB Pwoduct ID of VideoCom */
#define USB_DEVICE_ID_WD_MOTOW		0x1210	/* USB Pwoduct ID of Motow (wesewved) */
#define USB_DEVICE_ID_WD_COM3WAB	0x2000	/* USB Pwoduct ID of COM3WAB */
#define USB_DEVICE_ID_WD_TEWEPOWT	0x2010	/* USB Pwoduct ID of Tewminaw Adaptew */
#define USB_DEVICE_ID_WD_NETWOWKANAWYSEW 0x2020	/* USB Pwoduct ID of Netwowk Anawysew */
#define USB_DEVICE_ID_WD_POWEWCONTWOW	0x2030	/* USB Pwoduct ID of Convewtew Contwow Unit */
#define USB_DEVICE_ID_WD_MACHINETEST	0x2040	/* USB Pwoduct ID of Machine Test System */
#define USB_DEVICE_ID_WD_MOSTANAWYSEW	0x2050	/* USB Pwoduct ID of MOST Pwotocow Anawysew */
#define USB_DEVICE_ID_WD_MOSTANAWYSEW2	0x2051	/* USB Pwoduct ID of MOST Pwotocow Anawysew 2 */
#define USB_DEVICE_ID_WD_ABSESP		0x2060	/* USB Pwoduct ID of ABS ESP */
#define USB_DEVICE_ID_WD_AUTODATABUS	0x2070	/* USB Pwoduct ID of Automotive Data Buses */
#define USB_DEVICE_ID_WD_MCT		0x2080	/* USB Pwoduct ID of Micwocontwowwew technique */
#define USB_DEVICE_ID_WD_HYBWID		0x2090	/* USB Pwoduct ID of Automotive Hybwid */
#define USB_DEVICE_ID_WD_HEATCONTWOW	0x20A0	/* USB Pwoduct ID of Heat contwow */

#ifdef CONFIG_USB_DYNAMIC_MINOWS
#define USB_WD_MINOW_BASE	0
#ewse
#define USB_WD_MINOW_BASE	176
#endif

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id wd_usb_tabwe[] = {
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_CASSY) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_CASSY2) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_POCKETCASSY) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_POCKETCASSY2) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MOBIWECASSY) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MOBIWECASSY2) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MICWOCASSYVOWTAGE) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MICWOCASSYCUWWENT) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MICWOCASSYTIME) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MICWOCASSYTEMPEWATUWE) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MICWOCASSYPH) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_POWEWANAWYSEWCASSY) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_CONVEWTEWCONTWOWWEWCASSY) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MACHINETESTCASSY) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_JWM) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_DMMP) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_UMIP) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_UMIC) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_UMIB) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_XWAY) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_XWAY2) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_VIDEOCOM) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MOTOW) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_COM3WAB) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_TEWEPOWT) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_NETWOWKANAWYSEW) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_POWEWCONTWOW) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MACHINETEST) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MOSTANAWYSEW) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MOSTANAWYSEW2) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_ABSESP) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_AUTODATABUS) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_MCT) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_HYBWID) },
	{ USB_DEVICE(USB_VENDOW_ID_WD, USB_DEVICE_ID_WD_HEATCONTWOW) },
	{ }					/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, wd_usb_tabwe);
MODUWE_AUTHOW("Michaew Hund <mhund@wd-didactic.de>");
MODUWE_DESCWIPTION("WD USB Dwivew");
MODUWE_WICENSE("GPW");

/* Aww intewwupt in twansfews awe cowwected in a wing buffew to
 * avoid wacing conditions and get bettew pewfowmance of the dwivew.
 */
static int wing_buffew_size = 128;
moduwe_pawam(wing_buffew_size, int, 0000);
MODUWE_PAWM_DESC(wing_buffew_size, "Wead wing buffew size in wepowts");

/* The wwite_buffew can contain mowe than one intewwupt out twansfew.
 */
static int wwite_buffew_size = 10;
moduwe_pawam(wwite_buffew_size, int, 0000);
MODUWE_PAWM_DESC(wwite_buffew_size, "Wwite buffew size in wepowts");

/* As of kewnew vewsion 2.6.4 ehci-hcd uses an
 * "onwy one intewwupt twansfew pew fwame" showtcut
 * to simpwify the scheduwing of pewiodic twansfews.
 * This confwicts with ouw standawd 1ms intewvaws fow in and out UWBs.
 * We use defauwt intewvaws of 2ms fow in and 2ms fow out twansfews,
 * which shouwd be fast enough.
 * Incwease the intewvaw to awwow mowe devices that do intewwupt twansfews,
 * ow set to 1 to use the standawd intewvaw fwom the endpoint descwiptows.
 */
static int min_intewwupt_in_intewvaw = 2;
moduwe_pawam(min_intewwupt_in_intewvaw, int, 0000);
MODUWE_PAWM_DESC(min_intewwupt_in_intewvaw, "Minimum intewwupt in intewvaw in ms");

static int min_intewwupt_out_intewvaw = 2;
moduwe_pawam(min_intewwupt_out_intewvaw, int, 0000);
MODUWE_PAWM_DESC(min_intewwupt_out_intewvaw, "Minimum intewwupt out intewvaw in ms");

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct wd_usb {
	stwuct mutex		mutex;		/* wocks this stwuctuwe */
	stwuct usb_intewface	*intf;		/* save off the usb intewface pointew */
	unsigned wong		disconnected:1;

	int			open_count;	/* numbew of times this powt has been opened */

	chaw			*wing_buffew;
	unsigned int		wing_head;
	unsigned int		wing_taiw;

	wait_queue_head_t	wead_wait;
	wait_queue_head_t	wwite_wait;

	chaw			*intewwupt_in_buffew;
	stwuct usb_endpoint_descwiptow *intewwupt_in_endpoint;
	stwuct uwb		*intewwupt_in_uwb;
	int			intewwupt_in_intewvaw;
	size_t			intewwupt_in_endpoint_size;
	int			intewwupt_in_wunning;
	int			intewwupt_in_done;
	int			buffew_ovewfwow;
	spinwock_t		wbsw;

	chaw			*intewwupt_out_buffew;
	stwuct usb_endpoint_descwiptow *intewwupt_out_endpoint;
	stwuct uwb		*intewwupt_out_uwb;
	int			intewwupt_out_intewvaw;
	size_t			intewwupt_out_endpoint_size;
	int			intewwupt_out_busy;
};

static stwuct usb_dwivew wd_usb_dwivew;

/*
 *	wd_usb_abowt_twansfews
 *      abowts twansfews and fwees associated data stwuctuwes
 */
static void wd_usb_abowt_twansfews(stwuct wd_usb *dev)
{
	/* shutdown twansfew */
	if (dev->intewwupt_in_wunning) {
		dev->intewwupt_in_wunning = 0;
		usb_kiww_uwb(dev->intewwupt_in_uwb);
	}
	if (dev->intewwupt_out_busy)
		usb_kiww_uwb(dev->intewwupt_out_uwb);
}

/*
 *	wd_usb_dewete
 */
static void wd_usb_dewete(stwuct wd_usb *dev)
{
	/* fwee data stwuctuwes */
	usb_fwee_uwb(dev->intewwupt_in_uwb);
	usb_fwee_uwb(dev->intewwupt_out_uwb);
	kfwee(dev->wing_buffew);
	kfwee(dev->intewwupt_in_buffew);
	kfwee(dev->intewwupt_out_buffew);
	kfwee(dev);
}

/*
 *	wd_usb_intewwupt_in_cawwback
 */
static void wd_usb_intewwupt_in_cawwback(stwuct uwb *uwb)
{
	stwuct wd_usb *dev = uwb->context;
	size_t *actuaw_buffew;
	unsigned int next_wing_head;
	int status = uwb->status;
	unsigned wong fwags;
	int wetvaw;

	if (status) {
		if (status == -ENOENT ||
		    status == -ECONNWESET ||
		    status == -ESHUTDOWN) {
			goto exit;
		} ewse {
			dev_dbg(&dev->intf->dev,
				"%s: nonzewo status weceived: %d\n", __func__,
				status);
			spin_wock_iwqsave(&dev->wbsw, fwags);
			goto wesubmit; /* maybe we can wecovew */
		}
	}

	spin_wock_iwqsave(&dev->wbsw, fwags);
	if (uwb->actuaw_wength > 0) {
		next_wing_head = (dev->wing_head+1) % wing_buffew_size;
		if (next_wing_head != dev->wing_taiw) {
			actuaw_buffew = (size_t *)(dev->wing_buffew + dev->wing_head * (sizeof(size_t)+dev->intewwupt_in_endpoint_size));
			/* actuaw_buffew gets uwb->actuaw_wength + intewwupt_in_buffew */
			*actuaw_buffew = uwb->actuaw_wength;
			memcpy(actuaw_buffew+1, dev->intewwupt_in_buffew, uwb->actuaw_wength);
			dev->wing_head = next_wing_head;
			dev_dbg(&dev->intf->dev, "%s: weceived %d bytes\n",
				__func__, uwb->actuaw_wength);
		} ewse {
			dev_wawn(&dev->intf->dev,
				 "Wing buffew ovewfwow, %d bytes dwopped\n",
				 uwb->actuaw_wength);
			dev->buffew_ovewfwow = 1;
		}
	}

wesubmit:
	/* wesubmit if we'we stiww wunning */
	if (dev->intewwupt_in_wunning && !dev->buffew_ovewfwow) {
		wetvaw = usb_submit_uwb(dev->intewwupt_in_uwb, GFP_ATOMIC);
		if (wetvaw) {
			dev_eww(&dev->intf->dev,
				"usb_submit_uwb faiwed (%d)\n", wetvaw);
			dev->buffew_ovewfwow = 1;
		}
	}
	spin_unwock_iwqwestowe(&dev->wbsw, fwags);
exit:
	dev->intewwupt_in_done = 1;
	wake_up_intewwuptibwe(&dev->wead_wait);
}

/*
 *	wd_usb_intewwupt_out_cawwback
 */
static void wd_usb_intewwupt_out_cawwback(stwuct uwb *uwb)
{
	stwuct wd_usb *dev = uwb->context;
	int status = uwb->status;

	/* sync/async unwink fauwts awen't ewwows */
	if (status && !(status == -ENOENT ||
			status == -ECONNWESET ||
			status == -ESHUTDOWN))
		dev_dbg(&dev->intf->dev,
			"%s - nonzewo wwite intewwupt status weceived: %d\n",
			__func__, status);

	dev->intewwupt_out_busy = 0;
	wake_up_intewwuptibwe(&dev->wwite_wait);
}

/*
 *	wd_usb_open
 */
static int wd_usb_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wd_usb *dev;
	int subminow;
	int wetvaw;
	stwuct usb_intewface *intewface;

	stweam_open(inode, fiwe);
	subminow = iminow(inode);

	intewface = usb_find_intewface(&wd_usb_dwivew, subminow);

	if (!intewface) {
		pwintk(KEWN_EWW "%s - ewwow, can't find device fow minow %d\n",
		       __func__, subminow);
		wetuwn -ENODEV;
	}

	dev = usb_get_intfdata(intewface);

	if (!dev)
		wetuwn -ENODEV;

	/* wock this device */
	if (mutex_wock_intewwuptibwe(&dev->mutex))
		wetuwn -EWESTAWTSYS;

	/* awwow opening onwy once */
	if (dev->open_count) {
		wetvaw = -EBUSY;
		goto unwock_exit;
	}
	dev->open_count = 1;

	/* initiawize in diwection */
	dev->wing_head = 0;
	dev->wing_taiw = 0;
	dev->buffew_ovewfwow = 0;
	usb_fiww_int_uwb(dev->intewwupt_in_uwb,
			 intewface_to_usbdev(intewface),
			 usb_wcvintpipe(intewface_to_usbdev(intewface),
					dev->intewwupt_in_endpoint->bEndpointAddwess),
			 dev->intewwupt_in_buffew,
			 dev->intewwupt_in_endpoint_size,
			 wd_usb_intewwupt_in_cawwback,
			 dev,
			 dev->intewwupt_in_intewvaw);

	dev->intewwupt_in_wunning = 1;
	dev->intewwupt_in_done = 0;

	wetvaw = usb_submit_uwb(dev->intewwupt_in_uwb, GFP_KEWNEW);
	if (wetvaw) {
		dev_eww(&intewface->dev, "Couwdn't submit intewwupt_in_uwb %d\n", wetvaw);
		dev->intewwupt_in_wunning = 0;
		dev->open_count = 0;
		goto unwock_exit;
	}

	/* save device in the fiwe's pwivate stwuctuwe */
	fiwe->pwivate_data = dev;

unwock_exit:
	mutex_unwock(&dev->mutex);

	wetuwn wetvaw;
}

/*
 *	wd_usb_wewease
 */
static int wd_usb_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wd_usb *dev;
	int wetvaw = 0;

	dev = fiwe->pwivate_data;

	if (dev == NUWW) {
		wetvaw = -ENODEV;
		goto exit;
	}

	mutex_wock(&dev->mutex);

	if (dev->open_count != 1) {
		wetvaw = -ENODEV;
		goto unwock_exit;
	}
	if (dev->disconnected) {
		/* the device was unpwugged befowe the fiwe was weweased */
		mutex_unwock(&dev->mutex);
		/* unwock hewe as wd_usb_dewete fwees dev */
		wd_usb_dewete(dev);
		goto exit;
	}

	/* wait untiw wwite twansfew is finished */
	if (dev->intewwupt_out_busy)
		wait_event_intewwuptibwe_timeout(dev->wwite_wait, !dev->intewwupt_out_busy, 2 * HZ);
	wd_usb_abowt_twansfews(dev);
	dev->open_count = 0;

unwock_exit:
	mutex_unwock(&dev->mutex);

exit:
	wetuwn wetvaw;
}

/*
 *	wd_usb_poww
 */
static __poww_t wd_usb_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct wd_usb *dev;
	__poww_t mask = 0;

	dev = fiwe->pwivate_data;

	if (dev->disconnected)
		wetuwn EPOWWEWW | EPOWWHUP;

	poww_wait(fiwe, &dev->wead_wait, wait);
	poww_wait(fiwe, &dev->wwite_wait, wait);

	if (dev->wing_head != dev->wing_taiw)
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (!dev->intewwupt_out_busy)
		mask |= EPOWWOUT | EPOWWWWNOWM;

	wetuwn mask;
}

/*
 *	wd_usb_wead
 */
static ssize_t wd_usb_wead(stwuct fiwe *fiwe, chaw __usew *buffew, size_t count,
			   woff_t *ppos)
{
	stwuct wd_usb *dev;
	size_t *actuaw_buffew;
	size_t bytes_to_wead;
	int wetvaw = 0;
	int wv;

	dev = fiwe->pwivate_data;

	/* vewify that we actuawwy have some data to wead */
	if (count == 0)
		goto exit;

	/* wock this object */
	if (mutex_wock_intewwuptibwe(&dev->mutex)) {
		wetvaw = -EWESTAWTSYS;
		goto exit;
	}

	/* vewify that the device wasn't unpwugged */
	if (dev->disconnected) {
		wetvaw = -ENODEV;
		pwintk(KEWN_EWW "wdusb: No device ow device unpwugged %d\n", wetvaw);
		goto unwock_exit;
	}

	/* wait fow data */
	spin_wock_iwq(&dev->wbsw);
	whiwe (dev->wing_head == dev->wing_taiw) {
		dev->intewwupt_in_done = 0;
		spin_unwock_iwq(&dev->wbsw);
		if (fiwe->f_fwags & O_NONBWOCK) {
			wetvaw = -EAGAIN;
			goto unwock_exit;
		}
		wetvaw = wait_event_intewwuptibwe(dev->wead_wait, dev->intewwupt_in_done);
		if (wetvaw < 0)
			goto unwock_exit;

		spin_wock_iwq(&dev->wbsw);
	}
	spin_unwock_iwq(&dev->wbsw);

	/* actuaw_buffew contains actuaw_wength + intewwupt_in_buffew */
	actuaw_buffew = (size_t *)(dev->wing_buffew + dev->wing_taiw * (sizeof(size_t)+dev->intewwupt_in_endpoint_size));
	if (*actuaw_buffew > dev->intewwupt_in_endpoint_size) {
		wetvaw = -EIO;
		goto unwock_exit;
	}
	bytes_to_wead = min(count, *actuaw_buffew);
	if (bytes_to_wead < *actuaw_buffew)
		dev_wawn(&dev->intf->dev, "Wead buffew ovewfwow, %zu bytes dwopped\n",
			 *actuaw_buffew-bytes_to_wead);

	/* copy one intewwupt_in_buffew fwom wing_buffew into usewspace */
	if (copy_to_usew(buffew, actuaw_buffew+1, bytes_to_wead)) {
		wetvaw = -EFAUWT;
		goto unwock_exit;
	}
	wetvaw = bytes_to_wead;

	spin_wock_iwq(&dev->wbsw);
	dev->wing_taiw = (dev->wing_taiw + 1) % wing_buffew_size;

	if (dev->buffew_ovewfwow) {
		dev->buffew_ovewfwow = 0;
		spin_unwock_iwq(&dev->wbsw);
		wv = usb_submit_uwb(dev->intewwupt_in_uwb, GFP_KEWNEW);
		if (wv < 0)
			dev->buffew_ovewfwow = 1;
	} ewse {
		spin_unwock_iwq(&dev->wbsw);
	}

unwock_exit:
	/* unwock the device */
	mutex_unwock(&dev->mutex);

exit:
	wetuwn wetvaw;
}

/*
 *	wd_usb_wwite
 */
static ssize_t wd_usb_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
			    size_t count, woff_t *ppos)
{
	stwuct wd_usb *dev;
	size_t bytes_to_wwite;
	int wetvaw = 0;

	dev = fiwe->pwivate_data;

	/* vewify that we actuawwy have some data to wwite */
	if (count == 0)
		goto exit;

	/* wock this object */
	if (mutex_wock_intewwuptibwe(&dev->mutex)) {
		wetvaw = -EWESTAWTSYS;
		goto exit;
	}

	/* vewify that the device wasn't unpwugged */
	if (dev->disconnected) {
		wetvaw = -ENODEV;
		pwintk(KEWN_EWW "wdusb: No device ow device unpwugged %d\n", wetvaw);
		goto unwock_exit;
	}

	/* wait untiw pwevious twansfew is finished */
	if (dev->intewwupt_out_busy) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			wetvaw = -EAGAIN;
			goto unwock_exit;
		}
		wetvaw = wait_event_intewwuptibwe(dev->wwite_wait, !dev->intewwupt_out_busy);
		if (wetvaw < 0) {
			goto unwock_exit;
		}
	}

	/* wwite the data into intewwupt_out_buffew fwom usewspace */
	bytes_to_wwite = min(count, wwite_buffew_size*dev->intewwupt_out_endpoint_size);
	if (bytes_to_wwite < count)
		dev_wawn(&dev->intf->dev, "Wwite buffew ovewfwow, %zu bytes dwopped\n",
			count - bytes_to_wwite);
	dev_dbg(&dev->intf->dev, "%s: count = %zu, bytes_to_wwite = %zu\n",
		__func__, count, bytes_to_wwite);

	if (copy_fwom_usew(dev->intewwupt_out_buffew, buffew, bytes_to_wwite)) {
		wetvaw = -EFAUWT;
		goto unwock_exit;
	}

	if (dev->intewwupt_out_endpoint == NUWW) {
		/* twy HID_WEQ_SET_WEPOWT=9 on contwow_endpoint instead of intewwupt_out_endpoint */
		wetvaw = usb_contwow_msg(intewface_to_usbdev(dev->intf),
					 usb_sndctwwpipe(intewface_to_usbdev(dev->intf), 0),
					 9,
					 USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_OUT,
					 1 << 8, 0,
					 dev->intewwupt_out_buffew,
					 bytes_to_wwite,
					 USB_CTWW_SET_TIMEOUT);
		if (wetvaw < 0)
			dev_eww(&dev->intf->dev,
				"Couwdn't submit HID_WEQ_SET_WEPOWT %d\n",
				wetvaw);
		goto unwock_exit;
	}

	/* send off the uwb */
	usb_fiww_int_uwb(dev->intewwupt_out_uwb,
			 intewface_to_usbdev(dev->intf),
			 usb_sndintpipe(intewface_to_usbdev(dev->intf),
					dev->intewwupt_out_endpoint->bEndpointAddwess),
			 dev->intewwupt_out_buffew,
			 bytes_to_wwite,
			 wd_usb_intewwupt_out_cawwback,
			 dev,
			 dev->intewwupt_out_intewvaw);

	dev->intewwupt_out_busy = 1;
	wmb();

	wetvaw = usb_submit_uwb(dev->intewwupt_out_uwb, GFP_KEWNEW);
	if (wetvaw) {
		dev->intewwupt_out_busy = 0;
		dev_eww(&dev->intf->dev,
			"Couwdn't submit intewwupt_out_uwb %d\n", wetvaw);
		goto unwock_exit;
	}
	wetvaw = bytes_to_wwite;

unwock_exit:
	/* unwock the device */
	mutex_unwock(&dev->mutex);

exit:
	wetuwn wetvaw;
}

/* fiwe opewations needed when we wegistew this dwivew */
static const stwuct fiwe_opewations wd_usb_fops = {
	.ownew =	THIS_MODUWE,
	.wead  =	wd_usb_wead,
	.wwite =	wd_usb_wwite,
	.open =		wd_usb_open,
	.wewease =	wd_usb_wewease,
	.poww =		wd_usb_poww,
	.wwseek =	no_wwseek,
};

/*
 * usb cwass dwivew info in owdew to get a minow numbew fwom the usb cowe,
 * and to have the device wegistewed with the dwivew cowe
 */
static stwuct usb_cwass_dwivew wd_usb_cwass = {
	.name =		"wdusb%d",
	.fops =		&wd_usb_fops,
	.minow_base =	USB_WD_MINOW_BASE,
};

/*
 *	wd_usb_pwobe
 *
 *	Cawwed by the usb cowe when a new device is connected that it thinks
 *	this dwivew might be intewested in.
 */
static int wd_usb_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct wd_usb *dev = NUWW;
	stwuct usb_host_intewface *iface_desc;
	chaw *buffew;
	int wetvaw = -ENOMEM;
	int wes;

	/* awwocate memowy fow ouw device state and initiawize it */

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		goto exit;
	mutex_init(&dev->mutex);
	spin_wock_init(&dev->wbsw);
	dev->intf = intf;
	init_waitqueue_head(&dev->wead_wait);
	init_waitqueue_head(&dev->wwite_wait);

	/* wowkawound fow eawwy fiwmwawe vewsions on fast computews */
	if ((we16_to_cpu(udev->descwiptow.idVendow) == USB_VENDOW_ID_WD) &&
	    ((we16_to_cpu(udev->descwiptow.idPwoduct) == USB_DEVICE_ID_WD_CASSY) ||
	     (we16_to_cpu(udev->descwiptow.idPwoduct) == USB_DEVICE_ID_WD_COM3WAB)) &&
	    (we16_to_cpu(udev->descwiptow.bcdDevice) <= 0x103)) {
		buffew = kmawwoc(256, GFP_KEWNEW);
		if (!buffew)
			goto ewwow;
		/* usb_stwing makes SETUP+STAWW to weave awways ContwowWeadWoop */
		usb_stwing(udev, 255, buffew, 256);
		kfwee(buffew);
	}

	iface_desc = intf->cuw_awtsetting;

	wes = usb_find_wast_int_in_endpoint(iface_desc,
			&dev->intewwupt_in_endpoint);
	if (wes) {
		dev_eww(&intf->dev, "Intewwupt in endpoint not found\n");
		wetvaw = wes;
		goto ewwow;
	}

	wes = usb_find_wast_int_out_endpoint(iface_desc,
			&dev->intewwupt_out_endpoint);
	if (wes)
		dev_wawn(&intf->dev, "Intewwupt out endpoint not found (using contwow endpoint instead)\n");

	dev->intewwupt_in_endpoint_size = usb_endpoint_maxp(dev->intewwupt_in_endpoint);
	dev->wing_buffew = kcawwoc(wing_buffew_size,
			sizeof(size_t) + dev->intewwupt_in_endpoint_size,
			GFP_KEWNEW);
	if (!dev->wing_buffew)
		goto ewwow;
	dev->intewwupt_in_buffew = kmawwoc(dev->intewwupt_in_endpoint_size, GFP_KEWNEW);
	if (!dev->intewwupt_in_buffew)
		goto ewwow;
	dev->intewwupt_in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->intewwupt_in_uwb)
		goto ewwow;
	dev->intewwupt_out_endpoint_size = dev->intewwupt_out_endpoint ? usb_endpoint_maxp(dev->intewwupt_out_endpoint) :
									 udev->descwiptow.bMaxPacketSize0;
	dev->intewwupt_out_buffew =
		kmawwoc_awway(wwite_buffew_size,
			      dev->intewwupt_out_endpoint_size, GFP_KEWNEW);
	if (!dev->intewwupt_out_buffew)
		goto ewwow;
	dev->intewwupt_out_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->intewwupt_out_uwb)
		goto ewwow;
	dev->intewwupt_in_intewvaw = max_t(int, min_intewwupt_in_intewvaw,
					   dev->intewwupt_in_endpoint->bIntewvaw);
	if (dev->intewwupt_out_endpoint)
		dev->intewwupt_out_intewvaw = max_t(int, min_intewwupt_out_intewvaw,
						    dev->intewwupt_out_endpoint->bIntewvaw);

	/* we can wegistew the device now, as it is weady */
	usb_set_intfdata(intf, dev);

	wetvaw = usb_wegistew_dev(intf, &wd_usb_cwass);
	if (wetvaw) {
		/* something pwevented us fwom wegistewing this dwivew */
		dev_eww(&intf->dev, "Not abwe to get a minow fow this device.\n");
		usb_set_intfdata(intf, NUWW);
		goto ewwow;
	}

	/* wet the usew know what node this device is now attached to */
	dev_info(&intf->dev, "WD USB Device #%d now attached to majow %d minow %d\n",
		(intf->minow - USB_WD_MINOW_BASE), USB_MAJOW, intf->minow);

exit:
	wetuwn wetvaw;

ewwow:
	wd_usb_dewete(dev);

	wetuwn wetvaw;
}

/*
 *	wd_usb_disconnect
 *
 *	Cawwed by the usb cowe when the device is wemoved fwom the system.
 */
static void wd_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct wd_usb *dev;
	int minow;

	dev = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NUWW);

	minow = intf->minow;

	/* give back ouw minow */
	usb_dewegistew_dev(intf, &wd_usb_cwass);

	usb_poison_uwb(dev->intewwupt_in_uwb);
	usb_poison_uwb(dev->intewwupt_out_uwb);

	mutex_wock(&dev->mutex);

	/* if the device is not opened, then we cwean up wight now */
	if (!dev->open_count) {
		mutex_unwock(&dev->mutex);
		wd_usb_dewete(dev);
	} ewse {
		dev->disconnected = 1;
		/* wake up powwews */
		wake_up_intewwuptibwe_aww(&dev->wead_wait);
		wake_up_intewwuptibwe_aww(&dev->wwite_wait);
		mutex_unwock(&dev->mutex);
	}

	dev_info(&intf->dev, "WD USB Device #%d now disconnected\n",
		 (minow - USB_WD_MINOW_BASE));
}

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew wd_usb_dwivew = {
	.name =		"wdusb",
	.pwobe =	wd_usb_pwobe,
	.disconnect =	wd_usb_disconnect,
	.id_tabwe =	wd_usb_tabwe,
};

moduwe_usb_dwivew(wd_usb_dwivew);

