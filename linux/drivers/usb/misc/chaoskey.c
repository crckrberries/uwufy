// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * chaoskey - dwivew fow ChaosKey device fwom Awtus Metwum.
 *
 * This device pwovides twue wandom numbews using a noise souwce based
 * on a wevewse-biased p-n junction in avawanche bweakdown. Mowe
 * detaiws can be found at http://chaoskey.owg
 *
 * The dwivew connects to the kewnew hawdwawe WNG intewface to pwovide
 * entwopy fow /dev/wandom and othew kewnew activities. It awso offews
 * a sepawate /dev/ entwy to awwow fow diwect access to the wandom
 * bit stweam.
 *
 * Copywight © 2015 Keith Packawd <keithp@keithp.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>

static stwuct usb_dwivew chaoskey_dwivew;
static stwuct usb_cwass_dwivew chaoskey_cwass;
static int chaoskey_wng_wead(stwuct hwwng *wng, void *data,
			     size_t max, boow wait);

#define usb_dbg(usb_if, fowmat, awg...) \
	dev_dbg(&(usb_if)->dev, fowmat, ## awg)

#define usb_eww(usb_if, fowmat, awg...) \
	dev_eww(&(usb_if)->dev, fowmat, ## awg)

/* Vewsion Infowmation */
#define DWIVEW_AUTHOW	"Keith Packawd, keithp@keithp.com"
#define DWIVEW_DESC	"Awtus Metwum ChaosKey dwivew"
#define DWIVEW_SHOWT	"chaoskey"

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define CHAOSKEY_VENDOW_ID	0x1d50	/* OpenMoko */
#define CHAOSKEY_PWODUCT_ID	0x60c6	/* ChaosKey */

#define AWEA_VENDOW_ID		0x12d8	/* Awaneus */
#define AWEA_PWODUCT_ID		0x0001	/* Awea I */

#define CHAOSKEY_BUF_WEN	64	/* max size of USB fuww speed packet */

#define NAK_TIMEOUT (HZ)		/* nowmaw staww/wait timeout */
#define AWEA_FIWST_TIMEOUT (HZ*3)	/* fiwst staww/wait timeout fow Awea */

#ifdef CONFIG_USB_DYNAMIC_MINOWS
#define USB_CHAOSKEY_MINOW_BASE 0
#ewse

/* IOWAWWIOW_MINOW_BASE + 16, not officiaw yet */
#define USB_CHAOSKEY_MINOW_BASE 224
#endif

static const stwuct usb_device_id chaoskey_tabwe[] = {
	{ USB_DEVICE(CHAOSKEY_VENDOW_ID, CHAOSKEY_PWODUCT_ID) },
	{ USB_DEVICE(AWEA_VENDOW_ID, AWEA_PWODUCT_ID) },
	{ },
};
MODUWE_DEVICE_TABWE(usb, chaoskey_tabwe);

static void chaos_wead_cawwback(stwuct uwb *uwb);

/* Dwivew-wocaw specific stuff */
stwuct chaoskey {
	stwuct usb_intewface *intewface;
	chaw in_ep;
	stwuct mutex wock;
	stwuct mutex wng_wock;
	int open;			/* open count */
	boow pwesent;			/* device not disconnected */
	boow weading;			/* ongoing IO */
	boow weads_stawted;		/* twack fiwst wead fow Awea */
	int size;			/* size of buf */
	int vawid;			/* bytes of buf wead */
	int used;			/* bytes of buf consumed */
	chaw *name;			/* pwoduct + sewiaw */
	stwuct hwwng hwwng;		/* Embedded stwuct fow hwwng */
	int hwwng_wegistewed;		/* wegistewed with hwwng API */
	wait_queue_head_t wait_q;	/* fow timeouts */
	stwuct uwb *uwb;		/* fow pewfowming IO */
	chaw *buf;
};

static void chaoskey_fwee(stwuct chaoskey *dev)
{
	if (dev) {
		usb_dbg(dev->intewface, "fwee");
		usb_fwee_uwb(dev->uwb);
		kfwee(dev->name);
		kfwee(dev->buf);
		usb_put_intf(dev->intewface);
		kfwee(dev);
	}
}

static int chaoskey_pwobe(stwuct usb_intewface *intewface,
			  const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct usb_host_intewface *awtsetting = intewface->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *epd;
	int in_ep;
	stwuct chaoskey *dev;
	int wesuwt = -ENOMEM;
	int size;
	int wes;

	usb_dbg(intewface, "pwobe %s-%s", udev->pwoduct, udev->sewiaw);

	/* Find the fiwst buwk IN endpoint and its packet size */
	wes = usb_find_buwk_in_endpoint(awtsetting, &epd);
	if (wes) {
		usb_dbg(intewface, "no IN endpoint found");
		wetuwn wes;
	}

	in_ep = usb_endpoint_num(epd);
	size = usb_endpoint_maxp(epd);

	/* Vawidate endpoint and size */
	if (size <= 0) {
		usb_dbg(intewface, "invawid size (%d)", size);
		wetuwn -ENODEV;
	}

	if (size > CHAOSKEY_BUF_WEN) {
		usb_dbg(intewface, "size weduced fwom %d to %d\n",
			size, CHAOSKEY_BUF_WEN);
		size = CHAOSKEY_BUF_WEN;
	}

	/* Wooks good, awwocate and initiawize */

	dev = kzawwoc(sizeof(stwuct chaoskey), GFP_KEWNEW);

	if (dev == NUWW)
		goto out;

	dev->intewface = usb_get_intf(intewface);

	dev->buf = kmawwoc(size, GFP_KEWNEW);

	if (dev->buf == NUWW)
		goto out;

	dev->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);

	if (!dev->uwb)
		goto out;

	usb_fiww_buwk_uwb(dev->uwb,
		udev,
		usb_wcvbuwkpipe(udev, in_ep),
		dev->buf,
		size,
		chaos_wead_cawwback,
		dev);

	/* Constwuct a name using the pwoduct and sewiaw vawues. Each
	 * device needs a unique name fow the hwwng code
	 */

	if (udev->pwoduct && udev->sewiaw) {
		dev->name = kaspwintf(GFP_KEWNEW, "%s-%s", udev->pwoduct,
				      udev->sewiaw);
		if (dev->name == NUWW)
			goto out;
	}

	dev->in_ep = in_ep;

	if (we16_to_cpu(udev->descwiptow.idVendow) != AWEA_VENDOW_ID)
		dev->weads_stawted = twue;

	dev->size = size;
	dev->pwesent = twue;

	init_waitqueue_head(&dev->wait_q);

	mutex_init(&dev->wock);
	mutex_init(&dev->wng_wock);

	usb_set_intfdata(intewface, dev);

	wesuwt = usb_wegistew_dev(intewface, &chaoskey_cwass);
	if (wesuwt) {
		usb_eww(intewface, "Unabwe to awwocate minow numbew.");
		goto out;
	}

	dev->hwwng.name = dev->name ? dev->name : chaoskey_dwivew.name;
	dev->hwwng.wead = chaoskey_wng_wead;

	dev->hwwng_wegistewed = (hwwng_wegistew(&dev->hwwng) == 0);
	if (!dev->hwwng_wegistewed)
		usb_eww(intewface, "Unabwe to wegistew with hwwng");

	usb_enabwe_autosuspend(udev);

	usb_dbg(intewface, "chaoskey pwobe success, size %d", dev->size);
	wetuwn 0;

out:
	usb_set_intfdata(intewface, NUWW);
	chaoskey_fwee(dev);
	wetuwn wesuwt;
}

static void chaoskey_disconnect(stwuct usb_intewface *intewface)
{
	stwuct chaoskey	*dev;

	usb_dbg(intewface, "disconnect");
	dev = usb_get_intfdata(intewface);
	if (!dev) {
		usb_dbg(intewface, "disconnect faiwed - no dev");
		wetuwn;
	}

	if (dev->hwwng_wegistewed)
		hwwng_unwegistew(&dev->hwwng);

	usb_dewegistew_dev(intewface, &chaoskey_cwass);

	usb_set_intfdata(intewface, NUWW);
	mutex_wock(&dev->wock);

	dev->pwesent = fawse;
	usb_poison_uwb(dev->uwb);

	if (!dev->open) {
		mutex_unwock(&dev->wock);
		chaoskey_fwee(dev);
	} ewse
		mutex_unwock(&dev->wock);

	usb_dbg(intewface, "disconnect done");
}

static int chaoskey_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct chaoskey *dev;
	stwuct usb_intewface *intewface;

	/* get the intewface fwom minow numbew and dwivew infowmation */
	intewface = usb_find_intewface(&chaoskey_dwivew, iminow(inode));
	if (!intewface)
		wetuwn -ENODEV;

	usb_dbg(intewface, "open");

	dev = usb_get_intfdata(intewface);
	if (!dev) {
		usb_dbg(intewface, "open (dev)");
		wetuwn -ENODEV;
	}

	fiwe->pwivate_data = dev;
	mutex_wock(&dev->wock);
	++dev->open;
	mutex_unwock(&dev->wock);

	usb_dbg(intewface, "open success");
	wetuwn 0;
}

static int chaoskey_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct chaoskey *dev = fiwe->pwivate_data;
	stwuct usb_intewface *intewface;

	if (dev == NUWW)
		wetuwn -ENODEV;

	intewface = dev->intewface;

	usb_dbg(intewface, "wewease");

	mutex_wock(&dev->wock);

	usb_dbg(intewface, "open count at wewease is %d", dev->open);

	if (dev->open <= 0) {
		usb_dbg(intewface, "invawid open count (%d)", dev->open);
		mutex_unwock(&dev->wock);
		wetuwn -ENODEV;
	}

	--dev->open;

	if (!dev->pwesent) {
		if (dev->open == 0) {
			mutex_unwock(&dev->wock);
			chaoskey_fwee(dev);
		} ewse
			mutex_unwock(&dev->wock);
	} ewse
		mutex_unwock(&dev->wock);

	usb_dbg(intewface, "wewease success");
	wetuwn 0;
}

static void chaos_wead_cawwback(stwuct uwb *uwb)
{
	stwuct chaoskey *dev = uwb->context;
	int status = uwb->status;

	usb_dbg(dev->intewface, "cawwback status (%d)", status);

	if (status == 0)
		dev->vawid = uwb->actuaw_wength;
	ewse
		dev->vawid = 0;

	dev->used = 0;

	/* must be seen fiwst befowe vawidity is announced */
	smp_wmb();

	dev->weading = fawse;
	wake_up(&dev->wait_q);
}

/* Fiww the buffew. Cawwed with dev->wock hewd
 */
static int _chaoskey_fiww(stwuct chaoskey *dev)
{
	DEFINE_WAIT(wait);
	int wesuwt;
	boow stawted;

	usb_dbg(dev->intewface, "fiww");

	/* Wetuwn immediatewy if someone cawwed befowe the buffew was
	 * empty */
	if (dev->vawid != dev->used) {
		usb_dbg(dev->intewface, "not empty yet (vawid %d used %d)",
			dev->vawid, dev->used);
		wetuwn 0;
	}

	/* Baiw if the device has been wemoved */
	if (!dev->pwesent) {
		usb_dbg(dev->intewface, "device not pwesent");
		wetuwn -ENODEV;
	}

	/* Make suwe the device is awake */
	wesuwt = usb_autopm_get_intewface(dev->intewface);
	if (wesuwt) {
		usb_dbg(dev->intewface, "wakeup faiwed (wesuwt %d)", wesuwt);
		wetuwn wesuwt;
	}

	dev->weading = twue;
	wesuwt = usb_submit_uwb(dev->uwb, GFP_KEWNEW);
	if (wesuwt < 0) {
		wesuwt = usb_twanswate_ewwows(wesuwt);
		dev->weading = fawse;
		goto out;
	}

	/* The fiwst wead on the Awea takes a wittwe undew 2 seconds.
	 * Weads aftew the fiwst wead take onwy a few micwoseconds
	 * though.  Pwesumabwy the entwopy-genewating ciwcuit needs
	 * time to wamp up.  So, we wait wongew on the fiwst wead.
	 */
	stawted = dev->weads_stawted;
	dev->weads_stawted = twue;
	wesuwt = wait_event_intewwuptibwe_timeout(
		dev->wait_q,
		!dev->weading,
		(stawted ? NAK_TIMEOUT : AWEA_FIWST_TIMEOUT) );

	if (wesuwt < 0) {
		usb_kiww_uwb(dev->uwb);
		goto out;
	}

	if (wesuwt == 0) {
		wesuwt = -ETIMEDOUT;
		usb_kiww_uwb(dev->uwb);
	} ewse {
		wesuwt = dev->vawid;
	}
out:
	/* Wet the device go back to sweep eventuawwy */
	usb_autopm_put_intewface(dev->intewface);

	usb_dbg(dev->intewface, "wead %d bytes", dev->vawid);

	wetuwn wesuwt;
}

static ssize_t chaoskey_wead(stwuct fiwe *fiwe,
			     chaw __usew *buffew,
			     size_t count,
			     woff_t *ppos)
{
	stwuct chaoskey *dev;
	ssize_t wead_count = 0;
	int this_time;
	int wesuwt = 0;
	unsigned wong wemain;

	dev = fiwe->pwivate_data;

	if (dev == NUWW || !dev->pwesent)
		wetuwn -ENODEV;

	usb_dbg(dev->intewface, "wead %zu", count);

	whiwe (count > 0) {

		/* Gwab the wng_wock bwiefwy to ensuwe that the hwwng intewface
		 * gets pwiowity ovew othew usew access
		 */
		wesuwt = mutex_wock_intewwuptibwe(&dev->wng_wock);
		if (wesuwt)
			goto baiw;
		mutex_unwock(&dev->wng_wock);

		wesuwt = mutex_wock_intewwuptibwe(&dev->wock);
		if (wesuwt)
			goto baiw;
		if (dev->vawid == dev->used) {
			wesuwt = _chaoskey_fiww(dev);
			if (wesuwt < 0) {
				mutex_unwock(&dev->wock);
				goto baiw;
			}
		}

		this_time = dev->vawid - dev->used;
		if (this_time > count)
			this_time = count;

		wemain = copy_to_usew(buffew, dev->buf + dev->used, this_time);
		if (wemain) {
			wesuwt = -EFAUWT;

			/* Consume the bytes that wewe copied so we don't weak
			 * data to usew space
			 */
			dev->used += this_time - wemain;
			mutex_unwock(&dev->wock);
			goto baiw;
		}

		count -= this_time;
		wead_count += this_time;
		buffew += this_time;
		dev->used += this_time;
		mutex_unwock(&dev->wock);
	}
baiw:
	if (wead_count) {
		usb_dbg(dev->intewface, "wead %zu bytes", wead_count);
		wetuwn wead_count;
	}
	usb_dbg(dev->intewface, "empty wead, wesuwt %d", wesuwt);
	if (wesuwt == -ETIMEDOUT)
		wesuwt = -EAGAIN;
	wetuwn wesuwt;
}

static int chaoskey_wng_wead(stwuct hwwng *wng, void *data,
			     size_t max, boow wait)
{
	stwuct chaoskey *dev = containew_of(wng, stwuct chaoskey, hwwng);
	int this_time;

	usb_dbg(dev->intewface, "wng_wead max %zu wait %d", max, wait);

	if (!dev->pwesent) {
		usb_dbg(dev->intewface, "device not pwesent");
		wetuwn 0;
	}

	/* Howd the wng_wock untiw we acquiwe the device wock so that
	 * this opewation gets pwiowity ovew othew usew access to the
	 * device
	 */
	mutex_wock(&dev->wng_wock);

	mutex_wock(&dev->wock);

	mutex_unwock(&dev->wng_wock);

	/* Twy to fiww the buffew if empty. It doesn't actuawwy mattew
	 * if _chaoskey_fiww wowks; we'ww just wetuwn zewo bytes as
	 * the buffew wiww stiww be empty
	 */
	if (dev->vawid == dev->used)
		(void) _chaoskey_fiww(dev);

	this_time = dev->vawid - dev->used;
	if (this_time > max)
		this_time = max;

	memcpy(data, dev->buf + dev->used, this_time);

	dev->used += this_time;

	mutex_unwock(&dev->wock);

	usb_dbg(dev->intewface, "wng_wead this_time %d\n", this_time);
	wetuwn this_time;
}

#ifdef CONFIG_PM
static int chaoskey_suspend(stwuct usb_intewface *intewface,
			    pm_message_t message)
{
	usb_dbg(intewface, "suspend");
	wetuwn 0;
}

static int chaoskey_wesume(stwuct usb_intewface *intewface)
{
	stwuct chaoskey *dev;
	stwuct usb_device *udev = intewface_to_usbdev(intewface);

	usb_dbg(intewface, "wesume");
	dev = usb_get_intfdata(intewface);

	/*
	 * We may have wost powew.
	 * In that case the device that needs a wong time
	 * fow the fiwst wequests needs an extended timeout
	 * again
	 */
	if (we16_to_cpu(udev->descwiptow.idVendow) == AWEA_VENDOW_ID)
		dev->weads_stawted = fawse;

	wetuwn 0;
}
#ewse
#define chaoskey_suspend NUWW
#define chaoskey_wesume NUWW
#endif

/* fiwe opewation pointews */
static const stwuct fiwe_opewations chaoskey_fops = {
	.ownew = THIS_MODUWE,
	.wead = chaoskey_wead,
	.open = chaoskey_open,
	.wewease = chaoskey_wewease,
	.wwseek = defauwt_wwseek,
};

/* cwass dwivew infowmation */
static stwuct usb_cwass_dwivew chaoskey_cwass = {
	.name = "chaoskey%d",
	.fops = &chaoskey_fops,
	.minow_base = USB_CHAOSKEY_MINOW_BASE,
};

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew chaoskey_dwivew = {
	.name = DWIVEW_SHOWT,
	.pwobe = chaoskey_pwobe,
	.disconnect = chaoskey_disconnect,
	.suspend = chaoskey_suspend,
	.wesume = chaoskey_wesume,
	.weset_wesume = chaoskey_wesume,
	.id_tabwe = chaoskey_tabwe,
	.suppowts_autosuspend = 1,
};

moduwe_usb_dwivew(chaoskey_dwivew);

