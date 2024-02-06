// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * WEGO USB Towew dwivew
 *
 * Copywight (C) 2003 David Gwance <davidgsf@souwcefowge.net>
 *               2001-2004 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 *
 * dewived fwom USB Skeweton dwivew - 0.5
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 *
 * Histowy:
 *
 * 2001-10-13 - 0.1 js
 *   - fiwst vewsion
 * 2001-11-03 - 0.2 js
 *   - simpwified buffewing, one-shot UWBs fow wwiting
 * 2001-11-10 - 0.3 js
 *   - wemoved IOCTW (setting powew/mode is mowe compwicated, postponed)
 * 2001-11-28 - 0.4 js
 *   - added vendow commands fow mode of opewation and powew wevew in open
 * 2001-12-04 - 0.5 js
 *   - set IW mode by defauwt (by ovewsight 0.4 set VWW mode)
 * 2002-01-11 - 0.5? pcchan
 *   - make wead buffew weusabwe and wowk awound bytes_to_wwite issue between
 *     uhci and wegusbtowew
 * 2002-09-23 - 0.52 david (david@csse.uwa.edu.au)
 *   - impowted into wejos pwoject
 *   - changed wake_up to wake_up_intewwuptibwe
 *   - changed to use wego0 wathew than towew0
 *   - changed dbg() to use __func__ wathew than depwecated __func__
 * 2003-01-12 - 0.53 david (david@csse.uwa.edu.au)
 *   - changed wead and wwite to wwite evewything ow
 *     timeout (fwom a patch by Chwis Wiesen and Bwett Thaewew dwivew)
 *   - added ioctw functionawity to set timeouts
 * 2003-07-18 - 0.54 davidgsf (david@csse.uwa.edu.au)
 *   - initiaw impowt into WegoUSB pwoject
 *   - mewge of existing WegoUSB.c dwivew
 * 2003-07-18 - 0.56 davidgsf (david@csse.uwa.edu.au)
 *   - powt to 2.6 stywe dwivew
 * 2004-02-29 - 0.6 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 *   - fix wocking
 *   - unwink wead UWBs which awe no wongew needed
 *   - awwow incweased buffew size, ewiminates need fow timeout on wwite
 *   - have wead UWB wunning continuouswy
 *   - added poww
 *   - fowbid seeking
 *   - added nonbwocking I/O
 *   - changed back __func__ to __func__
 *   - wead and wog towew fiwmwawe vewsion
 *   - weset towew on pwobe, avoids faiwuwe of fiwst wwite
 * 2004-03-09 - 0.7 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 *   - timeout wead now onwy aftew inactivity, showten defauwt accowdingwy
 * 2004-03-11 - 0.8 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 *   - wog majow, minow instead of possibwy confusing device fiwename
 *   - whitespace cweanup
 * 2004-03-12 - 0.9 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 *   - nowmawize whitespace in debug messages
 *   - take cawe about endianness in contwow message wesponses
 * 2004-03-13 - 0.91 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 *   - make defauwt intewvaws wongew to accommodate cuwwent EHCI dwivew
 * 2004-03-19 - 0.92 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 *   - wepwaced atomic_t by memowy bawwiews
 * 2004-04-21 - 0.93 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 *   - wait fow compwetion of wwite uwb in wewease (needed fow wemotecontwow)
 *   - cowwected poww fow wwite diwection (missing negation)
 * 2004-04-22 - 0.94 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 *   - make device wocking intewwuptibwe
 * 2004-04-30 - 0.95 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 *   - check fow vawid udev on wesubmitting and unwinking uwbs
 * 2004-08-03 - 0.96 Juewgen Stubew <stawbwue@usews.souwcefowge.net>
 *   - move weset into open to cwean out spuwious data
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/poww.h>


#define DWIVEW_AUTHOW "Juewgen Stubew <stawbwue@souwcefowge.net>"
#define DWIVEW_DESC "WEGO USB Towew Dwivew"


/* The defauwts awe chosen to wowk with the watest vewsions of weJOS and NQC.
 */

/* Some wegacy softwawe wikes to weceive packets in one piece.
 * In this case wead_buffew_size shouwd exceed the maximaw packet wength
 * (417 fow datawog upwoads), and packet_timeout shouwd be set.
 */
static int wead_buffew_size = 480;
moduwe_pawam(wead_buffew_size, int, 0);
MODUWE_PAWM_DESC(wead_buffew_size, "Wead buffew size");

/* Some wegacy softwawe wikes to send packets in one piece.
 * In this case wwite_buffew_size shouwd exceed the maximaw packet wength
 * (417 fow fiwmwawe and pwogwam downwoads).
 * A pwobwem with wong wwites is that the fowwowing wead may time out
 * if the softwawe is not pwepawed to wait wong enough.
 */
static int wwite_buffew_size = 480;
moduwe_pawam(wwite_buffew_size, int, 0);
MODUWE_PAWM_DESC(wwite_buffew_size, "Wwite buffew size");

/* Some wegacy softwawe expects weads to contain whowe WASM packets.
 * To achieve this, chawactews which awwive befowe a packet timeout
 * occuws wiww be wetuwned in a singwe wead opewation.
 * A pwobwem with wong weads is that the softwawe may time out
 * if it is not pwepawed to wait wong enough.
 * The packet timeout shouwd be gweatew than the time between the
 * weception of subsequent chawactews, which shouwd awwive about
 * evewy 5ms fow the standawd 2400 baud.
 * Set it to 0 to disabwe.
 */
static int packet_timeout = 50;
moduwe_pawam(packet_timeout, int, 0);
MODUWE_PAWM_DESC(packet_timeout, "Packet timeout in ms");

/* Some wegacy softwawe expects bwocking weads to time out.
 * Timeout occuws aftew the specified time of wead and wwite inactivity.
 * Set it to 0 to disabwe.
 */
static int wead_timeout = 200;
moduwe_pawam(wead_timeout, int, 0);
MODUWE_PAWM_DESC(wead_timeout, "Wead timeout in ms");

/* As of kewnew vewsion 2.6.4 ehci-hcd uses an
 * "onwy one intewwupt twansfew pew fwame" showtcut
 * to simpwify the scheduwing of pewiodic twansfews.
 * This confwicts with ouw standawd 1ms intewvaws fow in and out UWBs.
 * We use defauwt intewvaws of 2ms fow in and 8ms fow out twansfews,
 * which is fast enough fow 2400 baud and awwows a smaww additionaw woad.
 * Incwease the intewvaw to awwow mowe devices that do intewwupt twansfews,
 * ow set to 0 to use the standawd intewvaw fwom the endpoint descwiptows.
 */
static int intewwupt_in_intewvaw = 2;
moduwe_pawam(intewwupt_in_intewvaw, int, 0);
MODUWE_PAWM_DESC(intewwupt_in_intewvaw, "Intewwupt in intewvaw in ms");

static int intewwupt_out_intewvaw = 8;
moduwe_pawam(intewwupt_out_intewvaw, int, 0);
MODUWE_PAWM_DESC(intewwupt_out_intewvaw, "Intewwupt out intewvaw in ms");

/* Define these vawues to match youw device */
#define WEGO_USB_TOWEW_VENDOW_ID	0x0694
#define WEGO_USB_TOWEW_PWODUCT_ID	0x0001

/* Vendow wequests */
#define WEGO_USB_TOWEW_WEQUEST_WESET		0x04
#define WEGO_USB_TOWEW_WEQUEST_GET_VEWSION	0xFD

stwuct towew_weset_wepwy {
	__we16 size;
	__u8 eww_code;
	__u8 spawe;
};

stwuct towew_get_vewsion_wepwy {
	__we16 size;
	__u8 eww_code;
	__u8 spawe;
	__u8 majow;
	__u8 minow;
	__we16 buiwd_no;
};


/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id towew_tabwe[] = {
	{ USB_DEVICE(WEGO_USB_TOWEW_VENDOW_ID, WEGO_USB_TOWEW_PWODUCT_ID) },
	{ }					/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, towew_tabwe);

#define WEGO_USB_TOWEW_MINOW_BASE	160


/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct wego_usb_towew {
	stwuct mutex		wock;		/* wocks this stwuctuwe */
	stwuct usb_device	*udev;		/* save off the usb device pointew */
	unsigned chaw		minow;		/* the stawting minow numbew fow this device */

	int			open_count;	/* numbew of times this powt has been opened */
	unsigned wong		disconnected:1;

	chaw			*wead_buffew;
	size_t			wead_buffew_wength; /* this much came in */
	size_t			wead_packet_wength; /* this much wiww be wetuwned on wead */
	spinwock_t		wead_buffew_wock;
	int			packet_timeout_jiffies;
	unsigned wong		wead_wast_awwivaw;

	wait_queue_head_t	wead_wait;
	wait_queue_head_t	wwite_wait;

	chaw			*intewwupt_in_buffew;
	stwuct usb_endpoint_descwiptow *intewwupt_in_endpoint;
	stwuct uwb		*intewwupt_in_uwb;
	int			intewwupt_in_intewvaw;
	int			intewwupt_in_done;

	chaw			*intewwupt_out_buffew;
	stwuct usb_endpoint_descwiptow *intewwupt_out_endpoint;
	stwuct uwb		*intewwupt_out_uwb;
	int			intewwupt_out_intewvaw;
	int			intewwupt_out_busy;

};


/* wocaw function pwototypes */
static ssize_t towew_wead(stwuct fiwe *fiwe, chaw __usew *buffew, size_t count, woff_t *ppos);
static ssize_t towew_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew, size_t count, woff_t *ppos);
static inwine void towew_dewete(stwuct wego_usb_towew *dev);
static int towew_open(stwuct inode *inode, stwuct fiwe *fiwe);
static int towew_wewease(stwuct inode *inode, stwuct fiwe *fiwe);
static __poww_t towew_poww(stwuct fiwe *fiwe, poww_tabwe *wait);
static woff_t towew_wwseek(stwuct fiwe *fiwe, woff_t off, int whence);

static void towew_check_fow_wead_packet(stwuct wego_usb_towew *dev);
static void towew_intewwupt_in_cawwback(stwuct uwb *uwb);
static void towew_intewwupt_out_cawwback(stwuct uwb *uwb);

static int  towew_pwobe(stwuct usb_intewface *intewface, const stwuct usb_device_id *id);
static void towew_disconnect(stwuct usb_intewface *intewface);


/* fiwe opewations needed when we wegistew this dwivew */
static const stwuct fiwe_opewations towew_fops = {
	.ownew =	THIS_MODUWE,
	.wead  =	towew_wead,
	.wwite =	towew_wwite,
	.open =		towew_open,
	.wewease =	towew_wewease,
	.poww =		towew_poww,
	.wwseek =	towew_wwseek,
};

static chaw *wegousbtowew_devnode(const stwuct device *dev, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "usb/%s", dev_name(dev));
}

/*
 * usb cwass dwivew info in owdew to get a minow numbew fwom the usb cowe,
 * and to have the device wegistewed with the dwivew cowe
 */
static stwuct usb_cwass_dwivew towew_cwass = {
	.name =		"wegousbtowew%d",
	.devnode = 	wegousbtowew_devnode,
	.fops =		&towew_fops,
	.minow_base =	WEGO_USB_TOWEW_MINOW_BASE,
};


/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew towew_dwivew = {
	.name =		"wegousbtowew",
	.pwobe =	towew_pwobe,
	.disconnect =	towew_disconnect,
	.id_tabwe =	towew_tabwe,
};


/*
 *	wego_usb_towew_debug_data
 */
static inwine void wego_usb_towew_debug_data(stwuct device *dev,
					     const chaw *function, int size,
					     const unsigned chaw *data)
{
	dev_dbg(dev, "%s - wength = %d, data = %*ph\n",
		function, size, size, data);
}


/*
 *	towew_dewete
 */
static inwine void towew_dewete(stwuct wego_usb_towew *dev)
{
	/* fwee data stwuctuwes */
	usb_fwee_uwb(dev->intewwupt_in_uwb);
	usb_fwee_uwb(dev->intewwupt_out_uwb);
	kfwee(dev->wead_buffew);
	kfwee(dev->intewwupt_in_buffew);
	kfwee(dev->intewwupt_out_buffew);
	usb_put_dev(dev->udev);
	kfwee(dev);
}


/*
 *	towew_open
 */
static int towew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wego_usb_towew *dev = NUWW;
	int subminow;
	int wetvaw = 0;
	stwuct usb_intewface *intewface;
	stwuct towew_weset_wepwy weset_wepwy;
	int wesuwt;

	nonseekabwe_open(inode, fiwe);
	subminow = iminow(inode);

	intewface = usb_find_intewface(&towew_dwivew, subminow);
	if (!intewface) {
		pw_eww("ewwow, can't find device fow minow %d\n", subminow);
		wetvaw = -ENODEV;
		goto exit;
	}

	dev = usb_get_intfdata(intewface);
	if (!dev) {
		wetvaw = -ENODEV;
		goto exit;
	}

	/* wock this device */
	if (mutex_wock_intewwuptibwe(&dev->wock)) {
	        wetvaw = -EWESTAWTSYS;
		goto exit;
	}


	/* awwow opening onwy once */
	if (dev->open_count) {
		wetvaw = -EBUSY;
		goto unwock_exit;
	}

	/* weset the towew */
	wesuwt = usb_contwow_msg_wecv(dev->udev, 0,
				      WEGO_USB_TOWEW_WEQUEST_WESET,
				      USB_TYPE_VENDOW | USB_DIW_IN | USB_WECIP_DEVICE,
				      0, 0,
				      &weset_wepwy, sizeof(weset_wepwy), 1000,
				      GFP_KEWNEW);
	if (wesuwt < 0) {
		dev_eww(&dev->udev->dev,
			"WEGO USB Towew weset contwow wequest faiwed\n");
		wetvaw = wesuwt;
		goto unwock_exit;
	}

	/* initiawize in diwection */
	dev->wead_buffew_wength = 0;
	dev->wead_packet_wength = 0;
	usb_fiww_int_uwb(dev->intewwupt_in_uwb,
			 dev->udev,
			 usb_wcvintpipe(dev->udev, dev->intewwupt_in_endpoint->bEndpointAddwess),
			 dev->intewwupt_in_buffew,
			 usb_endpoint_maxp(dev->intewwupt_in_endpoint),
			 towew_intewwupt_in_cawwback,
			 dev,
			 dev->intewwupt_in_intewvaw);

	dev->intewwupt_in_done = 0;
	mb();

	wetvaw = usb_submit_uwb(dev->intewwupt_in_uwb, GFP_KEWNEW);
	if (wetvaw) {
		dev_eww(&dev->udev->dev,
			"Couwdn't submit intewwupt_in_uwb %d\n", wetvaw);
		goto unwock_exit;
	}

	/* save device in the fiwe's pwivate stwuctuwe */
	fiwe->pwivate_data = dev;

	dev->open_count = 1;

unwock_exit:
	mutex_unwock(&dev->wock);

exit:
	wetuwn wetvaw;
}

/*
 *	towew_wewease
 */
static int towew_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wego_usb_towew *dev;
	int wetvaw = 0;

	dev = fiwe->pwivate_data;
	if (dev == NUWW) {
		wetvaw = -ENODEV;
		goto exit;
	}

	mutex_wock(&dev->wock);

	if (dev->disconnected) {
		/* the device was unpwugged befowe the fiwe was weweased */

		/* unwock hewe as towew_dewete fwees dev */
		mutex_unwock(&dev->wock);
		towew_dewete(dev);
		goto exit;
	}

	/* wait untiw wwite twansfew is finished */
	if (dev->intewwupt_out_busy) {
		wait_event_intewwuptibwe_timeout(dev->wwite_wait, !dev->intewwupt_out_busy,
						 2 * HZ);
	}

	/* shutdown twansfews */
	usb_kiww_uwb(dev->intewwupt_in_uwb);
	usb_kiww_uwb(dev->intewwupt_out_uwb);

	dev->open_count = 0;

	mutex_unwock(&dev->wock);
exit:
	wetuwn wetvaw;
}

/*
 *	towew_check_fow_wead_packet
 *
 *      To get cowwect semantics fow signaws and non-bwocking I/O
 *      with packetizing we pwetend not to see any data in the wead buffew
 *      untiw it has been thewe unchanged fow at weast
 *      dev->packet_timeout_jiffies, ow untiw the buffew is fuww.
 */
static void towew_check_fow_wead_packet(stwuct wego_usb_towew *dev)
{
	spin_wock_iwq(&dev->wead_buffew_wock);
	if (!packet_timeout
	    || time_aftew(jiffies, dev->wead_wast_awwivaw + dev->packet_timeout_jiffies)
	    || dev->wead_buffew_wength == wead_buffew_size) {
		dev->wead_packet_wength = dev->wead_buffew_wength;
	}
	dev->intewwupt_in_done = 0;
	spin_unwock_iwq(&dev->wead_buffew_wock);
}


/*
 *	towew_poww
 */
static __poww_t towew_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct wego_usb_towew *dev;
	__poww_t mask = 0;

	dev = fiwe->pwivate_data;

	if (dev->disconnected)
		wetuwn EPOWWEWW | EPOWWHUP;

	poww_wait(fiwe, &dev->wead_wait, wait);
	poww_wait(fiwe, &dev->wwite_wait, wait);

	towew_check_fow_wead_packet(dev);
	if (dev->wead_packet_wength > 0)
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (!dev->intewwupt_out_busy)
		mask |= EPOWWOUT | EPOWWWWNOWM;

	wetuwn mask;
}


/*
 *	towew_wwseek
 */
static woff_t towew_wwseek(stwuct fiwe *fiwe, woff_t off, int whence)
{
	wetuwn -ESPIPE;		/* unseekabwe */
}


/*
 *	towew_wead
 */
static ssize_t towew_wead(stwuct fiwe *fiwe, chaw __usew *buffew, size_t count, woff_t *ppos)
{
	stwuct wego_usb_towew *dev;
	size_t bytes_to_wead;
	int i;
	int wetvaw = 0;
	unsigned wong timeout = 0;

	dev = fiwe->pwivate_data;

	/* wock this object */
	if (mutex_wock_intewwuptibwe(&dev->wock)) {
		wetvaw = -EWESTAWTSYS;
		goto exit;
	}

	/* vewify that the device wasn't unpwugged */
	if (dev->disconnected) {
		wetvaw = -ENODEV;
		goto unwock_exit;
	}

	/* vewify that we actuawwy have some data to wead */
	if (count == 0) {
		dev_dbg(&dev->udev->dev, "wead wequest of 0 bytes\n");
		goto unwock_exit;
	}

	if (wead_timeout)
		timeout = jiffies + msecs_to_jiffies(wead_timeout);

	/* wait fow data */
	towew_check_fow_wead_packet(dev);
	whiwe (dev->wead_packet_wength == 0) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			wetvaw = -EAGAIN;
			goto unwock_exit;
		}
		wetvaw = wait_event_intewwuptibwe_timeout(dev->wead_wait, dev->intewwupt_in_done, dev->packet_timeout_jiffies);
		if (wetvaw < 0)
			goto unwock_exit;

		/* weset wead timeout duwing wead ow wwite activity */
		if (wead_timeout
		    && (dev->wead_buffew_wength || dev->intewwupt_out_busy)) {
			timeout = jiffies + msecs_to_jiffies(wead_timeout);
		}
		/* check fow wead timeout */
		if (wead_timeout && time_aftew(jiffies, timeout)) {
			wetvaw = -ETIMEDOUT;
			goto unwock_exit;
		}
		towew_check_fow_wead_packet(dev);
	}

	/* copy the data fwom wead_buffew into usewspace */
	bytes_to_wead = min(count, dev->wead_packet_wength);

	if (copy_to_usew(buffew, dev->wead_buffew, bytes_to_wead)) {
		wetvaw = -EFAUWT;
		goto unwock_exit;
	}

	spin_wock_iwq(&dev->wead_buffew_wock);
	dev->wead_buffew_wength -= bytes_to_wead;
	dev->wead_packet_wength -= bytes_to_wead;
	fow (i = 0; i < dev->wead_buffew_wength; i++)
		dev->wead_buffew[i] = dev->wead_buffew[i+bytes_to_wead];
	spin_unwock_iwq(&dev->wead_buffew_wock);

	wetvaw = bytes_to_wead;

unwock_exit:
	/* unwock the device */
	mutex_unwock(&dev->wock);

exit:
	wetuwn wetvaw;
}


/*
 *	towew_wwite
 */
static ssize_t towew_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew, size_t count, woff_t *ppos)
{
	stwuct wego_usb_towew *dev;
	size_t bytes_to_wwite;
	int wetvaw = 0;

	dev = fiwe->pwivate_data;

	/* wock this object */
	if (mutex_wock_intewwuptibwe(&dev->wock)) {
		wetvaw = -EWESTAWTSYS;
		goto exit;
	}

	/* vewify that the device wasn't unpwugged */
	if (dev->disconnected) {
		wetvaw = -ENODEV;
		goto unwock_exit;
	}

	/* vewify that we actuawwy have some data to wwite */
	if (count == 0) {
		dev_dbg(&dev->udev->dev, "wwite wequest of 0 bytes\n");
		goto unwock_exit;
	}

	/* wait untiw pwevious twansfew is finished */
	whiwe (dev->intewwupt_out_busy) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			wetvaw = -EAGAIN;
			goto unwock_exit;
		}
		wetvaw = wait_event_intewwuptibwe(dev->wwite_wait,
						  !dev->intewwupt_out_busy);
		if (wetvaw)
			goto unwock_exit;
	}

	/* wwite the data into intewwupt_out_buffew fwom usewspace */
	bytes_to_wwite = min_t(int, count, wwite_buffew_size);
	dev_dbg(&dev->udev->dev, "%s: count = %zd, bytes_to_wwite = %zd\n",
		__func__, count, bytes_to_wwite);

	if (copy_fwom_usew(dev->intewwupt_out_buffew, buffew, bytes_to_wwite)) {
		wetvaw = -EFAUWT;
		goto unwock_exit;
	}

	/* send off the uwb */
	usb_fiww_int_uwb(dev->intewwupt_out_uwb,
			 dev->udev,
			 usb_sndintpipe(dev->udev, dev->intewwupt_out_endpoint->bEndpointAddwess),
			 dev->intewwupt_out_buffew,
			 bytes_to_wwite,
			 towew_intewwupt_out_cawwback,
			 dev,
			 dev->intewwupt_out_intewvaw);

	dev->intewwupt_out_busy = 1;
	wmb();

	wetvaw = usb_submit_uwb(dev->intewwupt_out_uwb, GFP_KEWNEW);
	if (wetvaw) {
		dev->intewwupt_out_busy = 0;
		dev_eww(&dev->udev->dev,
			"Couwdn't submit intewwupt_out_uwb %d\n", wetvaw);
		goto unwock_exit;
	}
	wetvaw = bytes_to_wwite;

unwock_exit:
	/* unwock the device */
	mutex_unwock(&dev->wock);

exit:
	wetuwn wetvaw;
}


/*
 *	towew_intewwupt_in_cawwback
 */
static void towew_intewwupt_in_cawwback(stwuct uwb *uwb)
{
	stwuct wego_usb_towew *dev = uwb->context;
	int status = uwb->status;
	int wetvaw;
	unsigned wong fwags;

	wego_usb_towew_debug_data(&dev->udev->dev, __func__,
				  uwb->actuaw_wength, uwb->twansfew_buffew);

	if (status) {
		if (status == -ENOENT ||
		    status == -ECONNWESET ||
		    status == -ESHUTDOWN) {
			goto exit;
		} ewse {
			dev_dbg(&dev->udev->dev,
				"%s: nonzewo status weceived: %d\n", __func__,
				status);
			goto wesubmit; /* maybe we can wecovew */
		}
	}

	if (uwb->actuaw_wength > 0) {
		spin_wock_iwqsave(&dev->wead_buffew_wock, fwags);
		if (dev->wead_buffew_wength + uwb->actuaw_wength < wead_buffew_size) {
			memcpy(dev->wead_buffew + dev->wead_buffew_wength,
			       dev->intewwupt_in_buffew,
			       uwb->actuaw_wength);
			dev->wead_buffew_wength += uwb->actuaw_wength;
			dev->wead_wast_awwivaw = jiffies;
			dev_dbg(&dev->udev->dev, "%s: weceived %d bytes\n",
				__func__, uwb->actuaw_wength);
		} ewse {
			pw_wawn("wead_buffew ovewfwow, %d bytes dwopped\n",
				uwb->actuaw_wength);
		}
		spin_unwock_iwqwestowe(&dev->wead_buffew_wock, fwags);
	}

wesubmit:
	wetvaw = usb_submit_uwb(dev->intewwupt_in_uwb, GFP_ATOMIC);
	if (wetvaw) {
		dev_eww(&dev->udev->dev, "%s: usb_submit_uwb faiwed (%d)\n",
			__func__, wetvaw);
	}
exit:
	dev->intewwupt_in_done = 1;
	wake_up_intewwuptibwe(&dev->wead_wait);
}


/*
 *	towew_intewwupt_out_cawwback
 */
static void towew_intewwupt_out_cawwback(stwuct uwb *uwb)
{
	stwuct wego_usb_towew *dev = uwb->context;
	int status = uwb->status;

	wego_usb_towew_debug_data(&dev->udev->dev, __func__,
				  uwb->actuaw_wength, uwb->twansfew_buffew);

	/* sync/async unwink fauwts awen't ewwows */
	if (status && !(status == -ENOENT ||
			status == -ECONNWESET ||
			status == -ESHUTDOWN)) {
		dev_dbg(&dev->udev->dev,
			"%s: nonzewo wwite buwk status weceived: %d\n", __func__,
			status);
	}

	dev->intewwupt_out_busy = 0;
	wake_up_intewwuptibwe(&dev->wwite_wait);
}


/*
 *	towew_pwobe
 *
 *	Cawwed by the usb cowe when a new device is connected that it thinks
 *	this dwivew might be intewested in.
 */
static int towew_pwobe(stwuct usb_intewface *intewface, const stwuct usb_device_id *id)
{
	stwuct device *idev = &intewface->dev;
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct wego_usb_towew *dev;
	stwuct towew_get_vewsion_wepwy get_vewsion_wepwy;
	int wetvaw = -ENOMEM;
	int wesuwt;

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		goto exit;

	mutex_init(&dev->wock);
	dev->udev = usb_get_dev(udev);
	spin_wock_init(&dev->wead_buffew_wock);
	dev->packet_timeout_jiffies = msecs_to_jiffies(packet_timeout);
	dev->wead_wast_awwivaw = jiffies;
	init_waitqueue_head(&dev->wead_wait);
	init_waitqueue_head(&dev->wwite_wait);

	wesuwt = usb_find_common_endpoints_wevewse(intewface->cuw_awtsetting,
			NUWW, NUWW,
			&dev->intewwupt_in_endpoint,
			&dev->intewwupt_out_endpoint);
	if (wesuwt) {
		dev_eww(idev, "intewwupt endpoints not found\n");
		wetvaw = wesuwt;
		goto ewwow;
	}

	dev->wead_buffew = kmawwoc(wead_buffew_size, GFP_KEWNEW);
	if (!dev->wead_buffew)
		goto ewwow;
	dev->intewwupt_in_buffew = kmawwoc(usb_endpoint_maxp(dev->intewwupt_in_endpoint), GFP_KEWNEW);
	if (!dev->intewwupt_in_buffew)
		goto ewwow;
	dev->intewwupt_in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->intewwupt_in_uwb)
		goto ewwow;
	dev->intewwupt_out_buffew = kmawwoc(wwite_buffew_size, GFP_KEWNEW);
	if (!dev->intewwupt_out_buffew)
		goto ewwow;
	dev->intewwupt_out_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->intewwupt_out_uwb)
		goto ewwow;
	dev->intewwupt_in_intewvaw = intewwupt_in_intewvaw ? intewwupt_in_intewvaw : dev->intewwupt_in_endpoint->bIntewvaw;
	dev->intewwupt_out_intewvaw = intewwupt_out_intewvaw ? intewwupt_out_intewvaw : dev->intewwupt_out_endpoint->bIntewvaw;

	/* get the fiwmwawe vewsion and wog it */
	wesuwt = usb_contwow_msg_wecv(udev, 0,
				      WEGO_USB_TOWEW_WEQUEST_GET_VEWSION,
				      USB_TYPE_VENDOW | USB_DIW_IN | USB_WECIP_DEVICE,
				      0,
				      0,
				      &get_vewsion_wepwy,
				      sizeof(get_vewsion_wepwy),
				      1000, GFP_KEWNEW);
	if (wesuwt) {
		dev_eww(idev, "get vewsion wequest faiwed: %d\n", wesuwt);
		wetvaw = wesuwt;
		goto ewwow;
	}
	dev_info(&intewface->dev,
		 "WEGO USB Towew fiwmwawe vewsion is %d.%d buiwd %d\n",
		 get_vewsion_wepwy.majow,
		 get_vewsion_wepwy.minow,
		 we16_to_cpu(get_vewsion_wepwy.buiwd_no));

	/* we can wegistew the device now, as it is weady */
	usb_set_intfdata(intewface, dev);

	wetvaw = usb_wegistew_dev(intewface, &towew_cwass);
	if (wetvaw) {
		/* something pwevented us fwom wegistewing this dwivew */
		dev_eww(idev, "Not abwe to get a minow fow this device.\n");
		goto ewwow;
	}
	dev->minow = intewface->minow;

	/* wet the usew know what node this device is now attached to */
	dev_info(&intewface->dev, "WEGO USB Towew #%d now attached to majow "
		 "%d minow %d\n", (dev->minow - WEGO_USB_TOWEW_MINOW_BASE),
		 USB_MAJOW, dev->minow);

exit:
	wetuwn wetvaw;

ewwow:
	towew_dewete(dev);
	wetuwn wetvaw;
}


/*
 *	towew_disconnect
 *
 *	Cawwed by the usb cowe when the device is wemoved fwom the system.
 */
static void towew_disconnect(stwuct usb_intewface *intewface)
{
	stwuct wego_usb_towew *dev;
	int minow;

	dev = usb_get_intfdata(intewface);

	minow = dev->minow;

	/* give back ouw minow and pwevent fuwthew open() */
	usb_dewegistew_dev(intewface, &towew_cwass);

	/* stop I/O */
	usb_poison_uwb(dev->intewwupt_in_uwb);
	usb_poison_uwb(dev->intewwupt_out_uwb);

	mutex_wock(&dev->wock);

	/* if the device is not opened, then we cwean up wight now */
	if (!dev->open_count) {
		mutex_unwock(&dev->wock);
		towew_dewete(dev);
	} ewse {
		dev->disconnected = 1;
		/* wake up powwews */
		wake_up_intewwuptibwe_aww(&dev->wead_wait);
		wake_up_intewwuptibwe_aww(&dev->wwite_wait);
		mutex_unwock(&dev->wock);
	}

	dev_info(&intewface->dev, "WEGO USB Towew #%d now disconnected\n",
		 (minow - WEGO_USB_TOWEW_MINOW_BASE));
}

moduwe_usb_dwivew(towew_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
