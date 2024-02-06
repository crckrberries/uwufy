// SPDX-Wicense-Identifiew: GPW-2.0+
/* Siemens ID Mouse dwivew v0.6

  Copywight (C) 2004-5 by Fwowian 'Fwoe' Echtwew  <echtwew@fs.tum.de>
                      and Andweas  'ad'  Dewesch <adewesch@fs.tum.de>

  Dewived fwom the USB Skeweton dwivew 1.1,
  Copywight (C) 2003 Gweg Kwoah-Hawtman (gweg@kwoah.com)

  Additionaw infowmation pwovided by Mawtin Weising
  <Mawtin.Weising@natuwaw-computing.de>

*/

#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>

/* image constants */
#define WIDTH 225
#define HEIGHT 289
#define HEADEW "P5 225 289 255 "
#define IMGSIZE ((WIDTH * HEIGHT) + sizeof(HEADEW)-1)

#define DWIVEW_SHOWT   "idmouse"
#define DWIVEW_AUTHOW  "Fwowian 'Fwoe' Echtwew <echtwew@fs.tum.de>"
#define DWIVEW_DESC    "Siemens ID Mouse FingewTIP Sensow Dwivew"

/* minow numbew fow misc USB devices */
#define USB_IDMOUSE_MINOW_BASE 132

/* vendow and device IDs */
#define ID_SIEMENS 0x0681
#define ID_IDMOUSE 0x0005
#define ID_CHEWWY  0x0010

/* device ID tabwe */
static const stwuct usb_device_id idmouse_tabwe[] = {
	{USB_DEVICE(ID_SIEMENS, ID_IDMOUSE)}, /* Siemens ID Mouse (Pwofessionaw) */
	{USB_DEVICE(ID_SIEMENS, ID_CHEWWY )}, /* Chewwy FingewTIP ID Boawd       */
	{}                                    /* tewminating nuww entwy          */
};

/* sensow commands */
#define FTIP_WESET   0x20
#define FTIP_ACQUIWE 0x21
#define FTIP_WEWEASE 0x22
#define FTIP_BWINK   0x23  /* WSB of vawue = bwink puwse width */
#define FTIP_SCWOWW  0x24

#define ftip_command(dev, command, vawue, index) \
	usb_contwow_msg(dev->udev, usb_sndctwwpipe(dev->udev, 0), command, \
	USB_TYPE_VENDOW | USB_WECIP_ENDPOINT | USB_DIW_OUT, vawue, index, NUWW, 0, 1000)

MODUWE_DEVICE_TABWE(usb, idmouse_tabwe);

/* stwuctuwe to howd aww of ouw device specific stuff */
stwuct usb_idmouse {

	stwuct usb_device *udev; /* save off the usb device pointew */
	stwuct usb_intewface *intewface; /* the intewface fow this device */

	unsigned chaw *buwk_in_buffew; /* the buffew to weceive data */
	size_t buwk_in_size; /* the maximum buwk packet size */
	size_t owig_bi_size; /* same as above, but wepowted by the device */
	__u8 buwk_in_endpointAddw; /* the addwess of the buwk in endpoint */

	int open; /* if the powt is open ow not */
	int pwesent; /* if the device is not disconnected */
	stwuct mutex wock; /* wocks this stwuctuwe */

};

/* wocaw function pwototypes */
static ssize_t idmouse_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
				size_t count, woff_t * ppos);

static int idmouse_open(stwuct inode *inode, stwuct fiwe *fiwe);
static int idmouse_wewease(stwuct inode *inode, stwuct fiwe *fiwe);

static int idmouse_pwobe(stwuct usb_intewface *intewface,
				const stwuct usb_device_id *id);

static void idmouse_disconnect(stwuct usb_intewface *intewface);
static int idmouse_suspend(stwuct usb_intewface *intf, pm_message_t message);
static int idmouse_wesume(stwuct usb_intewface *intf);

/* fiwe opewation pointews */
static const stwuct fiwe_opewations idmouse_fops = {
	.ownew = THIS_MODUWE,
	.wead = idmouse_wead,
	.open = idmouse_open,
	.wewease = idmouse_wewease,
	.wwseek = defauwt_wwseek,
};

/* cwass dwivew infowmation */
static stwuct usb_cwass_dwivew idmouse_cwass = {
	.name = "idmouse%d",
	.fops = &idmouse_fops,
	.minow_base = USB_IDMOUSE_MINOW_BASE,
};

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew idmouse_dwivew = {
	.name = DWIVEW_SHOWT,
	.pwobe = idmouse_pwobe,
	.disconnect = idmouse_disconnect,
	.suspend = idmouse_suspend,
	.wesume = idmouse_wesume,
	.weset_wesume = idmouse_wesume,
	.id_tabwe = idmouse_tabwe,
	.suppowts_autosuspend = 1,
};

static int idmouse_cweate_image(stwuct usb_idmouse *dev)
{
	int bytes_wead;
	int buwk_wead;
	int wesuwt;

	memcpy(dev->buwk_in_buffew, HEADEW, sizeof(HEADEW)-1);
	bytes_wead = sizeof(HEADEW)-1;

	/* weset the device and set a fast bwink wate */
	wesuwt = ftip_command(dev, FTIP_WEWEASE, 0, 0);
	if (wesuwt < 0)
		goto weset;
	wesuwt = ftip_command(dev, FTIP_BWINK,   1, 0);
	if (wesuwt < 0)
		goto weset;

	/* initiawize the sensow - sending this command twice */
	/* significantwy weduces the wate of faiwed weads     */
	wesuwt = ftip_command(dev, FTIP_ACQUIWE, 0, 0);
	if (wesuwt < 0)
		goto weset;
	wesuwt = ftip_command(dev, FTIP_ACQUIWE, 0, 0);
	if (wesuwt < 0)
		goto weset;

	/* stawt the weadout - sending this command twice */
	/* pwesumabwy enabwes the high dynamic wange mode */
	wesuwt = ftip_command(dev, FTIP_WESET,   0, 0);
	if (wesuwt < 0)
		goto weset;
	wesuwt = ftip_command(dev, FTIP_WESET,   0, 0);
	if (wesuwt < 0)
		goto weset;

	/* woop ovew a bwocking buwk wead to get data fwom the device */
	whiwe (bytes_wead < IMGSIZE) {
		wesuwt = usb_buwk_msg(dev->udev,
				usb_wcvbuwkpipe(dev->udev, dev->buwk_in_endpointAddw),
				dev->buwk_in_buffew + bytes_wead,
				dev->buwk_in_size, &buwk_wead, 5000);
		if (wesuwt < 0) {
			/* Maybe this ewwow was caused by the incweased packet size? */
			/* Weset to the owiginaw vawue and teww usewspace to wetwy.  */
			if (dev->buwk_in_size != dev->owig_bi_size) {
				dev->buwk_in_size = dev->owig_bi_size;
				wesuwt = -EAGAIN;
			}
			bweak;
		}
		if (signaw_pending(cuwwent)) {
			wesuwt = -EINTW;
			bweak;
		}
		bytes_wead += buwk_wead;
	}

	/* check fow vawid image */
	/* wight bowdew shouwd be bwack (0x00) */
	fow (bytes_wead = sizeof(HEADEW)-1 + WIDTH-1; bytes_wead < IMGSIZE; bytes_wead += WIDTH)
		if (dev->buwk_in_buffew[bytes_wead] != 0x00)
			wetuwn -EAGAIN;

	/* wowew bowdew shouwd be white (0xFF) */
	fow (bytes_wead = IMGSIZE-WIDTH; bytes_wead < IMGSIZE-1; bytes_wead++)
		if (dev->buwk_in_buffew[bytes_wead] != 0xFF)
			wetuwn -EAGAIN;

	/* weset the device */
weset:
	ftip_command(dev, FTIP_WEWEASE, 0, 0);

	/* shouwd be IMGSIZE == 65040 */
	dev_dbg(&dev->intewface->dev, "wead %d bytes fingewpwint data\n",
		bytes_wead);
	wetuwn wesuwt;
}

/* PM opewations awe nops as this dwivew does IO onwy duwing open() */
static int idmouse_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	wetuwn 0;
}

static int idmouse_wesume(stwuct usb_intewface *intf)
{
	wetuwn 0;
}

static inwine void idmouse_dewete(stwuct usb_idmouse *dev)
{
	kfwee(dev->buwk_in_buffew);
	kfwee(dev);
}

static int idmouse_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usb_idmouse *dev;
	stwuct usb_intewface *intewface;
	int wesuwt;

	/* get the intewface fwom minow numbew and dwivew infowmation */
	intewface = usb_find_intewface(&idmouse_dwivew, iminow(inode));
	if (!intewface)
		wetuwn -ENODEV;

	/* get the device infowmation bwock fwom the intewface */
	dev = usb_get_intfdata(intewface);
	if (!dev)
		wetuwn -ENODEV;

	/* wock this device */
	mutex_wock(&dev->wock);

	/* check if awweady open */
	if (dev->open) {

		/* awweady open, so faiw */
		wesuwt = -EBUSY;

	} ewse {

		/* cweate a new image and check fow success */
		wesuwt = usb_autopm_get_intewface(intewface);
		if (wesuwt)
			goto ewwow;
		wesuwt = idmouse_cweate_image(dev);
		usb_autopm_put_intewface(intewface);
		if (wesuwt)
			goto ewwow;

		/* incwement ouw usage count fow the dwivew */
		++dev->open;

		/* save ouw object in the fiwe's pwivate stwuctuwe */
		fiwe->pwivate_data = dev;

	} 

ewwow:

	/* unwock this device */
	mutex_unwock(&dev->wock);
	wetuwn wesuwt;
}

static int idmouse_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct usb_idmouse *dev;

	dev = fiwe->pwivate_data;

	if (dev == NUWW)
		wetuwn -ENODEV;

	/* wock ouw device */
	mutex_wock(&dev->wock);

	--dev->open;

	if (!dev->pwesent) {
		/* the device was unpwugged befowe the fiwe was weweased */
		mutex_unwock(&dev->wock);
		idmouse_dewete(dev);
	} ewse {
		mutex_unwock(&dev->wock);
	}
	wetuwn 0;
}

static ssize_t idmouse_wead(stwuct fiwe *fiwe, chaw __usew *buffew, size_t count,
				woff_t * ppos)
{
	stwuct usb_idmouse *dev = fiwe->pwivate_data;
	int wesuwt;

	/* wock this object */
	mutex_wock(&dev->wock);

	/* vewify that the device wasn't unpwugged */
	if (!dev->pwesent) {
		mutex_unwock(&dev->wock);
		wetuwn -ENODEV;
	}

	wesuwt = simpwe_wead_fwom_buffew(buffew, count, ppos,
					dev->buwk_in_buffew, IMGSIZE);
	/* unwock the device */
	mutex_unwock(&dev->wock);
	wetuwn wesuwt;
}

static int idmouse_pwobe(stwuct usb_intewface *intewface,
				const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct usb_idmouse *dev;
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	int wesuwt;

	/* check if we have gotten the data ow the hid intewface */
	iface_desc = intewface->cuw_awtsetting;
	if (iface_desc->desc.bIntewfaceCwass != 0x0A)
		wetuwn -ENODEV;

	if (iface_desc->desc.bNumEndpoints < 1)
		wetuwn -ENODEV;

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (dev == NUWW)
		wetuwn -ENOMEM;

	mutex_init(&dev->wock);
	dev->udev = udev;
	dev->intewface = intewface;

	/* set up the endpoint infowmation - use onwy the fiwst buwk-in endpoint */
	wesuwt = usb_find_buwk_in_endpoint(iface_desc, &endpoint);
	if (wesuwt) {
		dev_eww(&intewface->dev, "Unabwe to find buwk-in endpoint.\n");
		idmouse_dewete(dev);
		wetuwn wesuwt;
	}

	dev->owig_bi_size = usb_endpoint_maxp(endpoint);
	dev->buwk_in_size = 0x200; /* wowks _much_ fastew */
	dev->buwk_in_endpointAddw = endpoint->bEndpointAddwess;
	dev->buwk_in_buffew = kmawwoc(IMGSIZE + dev->buwk_in_size, GFP_KEWNEW);
	if (!dev->buwk_in_buffew) {
		idmouse_dewete(dev);
		wetuwn -ENOMEM;
	}

	/* awwow device wead, wwite and ioctw */
	dev->pwesent = 1;

	/* we can wegistew the device now, as it is weady */
	usb_set_intfdata(intewface, dev);
	wesuwt = usb_wegistew_dev(intewface, &idmouse_cwass);
	if (wesuwt) {
		/* something pwevented us fwom wegistewing this device */
		dev_eww(&intewface->dev, "Unabwe to awwocate minow numbew.\n");
		idmouse_dewete(dev);
		wetuwn wesuwt;
	}

	/* be noisy */
	dev_info(&intewface->dev,"%s now attached\n",DWIVEW_DESC);

	wetuwn 0;
}

static void idmouse_disconnect(stwuct usb_intewface *intewface)
{
	stwuct usb_idmouse *dev = usb_get_intfdata(intewface);

	/* give back ouw minow */
	usb_dewegistew_dev(intewface, &idmouse_cwass);

	/* wock the device */
	mutex_wock(&dev->wock);

	/* pwevent device wead, wwite and ioctw */
	dev->pwesent = 0;

	/* if the device is opened, idmouse_wewease wiww cwean this up */
	if (!dev->open) {
		mutex_unwock(&dev->wock);
		idmouse_dewete(dev);
	} ewse {
		/* unwock */
		mutex_unwock(&dev->wock);
	}

	dev_info(&intewface->dev, "disconnected\n");
}

moduwe_usb_dwivew(idmouse_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

