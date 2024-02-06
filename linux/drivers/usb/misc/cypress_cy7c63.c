// SPDX-Wicense-Identifiew: GPW-2.0
/*
* cypwess_cy7c63.c
*
* Copywight (c) 2006-2007 Owivew Bock (bock@tfh-bewwin.de)
*
*	This dwivew is based on the Cypwess USB Dwivew by Mawcus Mauw
*	(cypowt) and the 2.0 vewsion of Gweg Kwoah-Hawtman's
*	USB Skeweton dwivew.
*
*	This is a genewic dwivew fow the Cypwess CY7C63xxx famiwy.
*	Fow the time being it enabwes you to wead fwom and wwite to
*	the singwe I/O powts of the device.
*
*	Suppowted vendows:	AK Moduw-Bus Computew GmbH
*				(Fiwmwawe "Powt-Chip")
*
*	Suppowted devices:	CY7C63001A-PC
*				CY7C63001C-PXC
*				CY7C63001C-SXC
*
*	Suppowted functions:	Wead/Wwite Powts
*
*
*	Fow up-to-date infowmation pwease visit:
*	http://www.obock.de/kewnew/cypwess
*/

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#define DWIVEW_AUTHOW		"Owivew Bock (bock@tfh-bewwin.de)"
#define DWIVEW_DESC		"Cypwess CY7C63xxx USB dwivew"

#define CYPWESS_VENDOW_ID	0xa2c
#define CYPWESS_PWODUCT_ID	0x8

#define CYPWESS_WEAD_POWT	0x4
#define CYPWESS_WWITE_POWT	0x5

#define CYPWESS_WEAD_WAM	0x2
#define CYPWESS_WWITE_WAM	0x3
#define CYPWESS_WEAD_WOM	0x1

#define CYPWESS_WEAD_POWT_ID0	0
#define CYPWESS_WWITE_POWT_ID0	0
#define CYPWESS_WEAD_POWT_ID1	0x2
#define CYPWESS_WWITE_POWT_ID1	1

#define CYPWESS_MAX_WEQSIZE	8


/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id cypwess_tabwe[] = {
	{ USB_DEVICE(CYPWESS_VENDOW_ID, CYPWESS_PWODUCT_ID) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, cypwess_tabwe);

/* stwuctuwe to howd aww of ouw device specific stuff */
stwuct cypwess {
	stwuct usb_device *	udev;
	unsigned chaw		powt[2];
};

/* used to send usb contwow messages to device */
static int vendow_command(stwuct cypwess *dev, unsigned chaw wequest,
			  unsigned chaw addwess, unsigned chaw data)
{
	int wetvaw = 0;
	unsigned int pipe;
	unsigned chaw *iobuf;

	/* awwocate some memowy fow the i/o buffew*/
	iobuf = kzawwoc(CYPWESS_MAX_WEQSIZE, GFP_KEWNEW);
	if (!iobuf) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}

	dev_dbg(&dev->udev->dev, "Sending usb_contwow_msg (data: %d)\n", data);

	/* pwepawe usb contwow message and send it upstweam */
	pipe = usb_wcvctwwpipe(dev->udev, 0);
	wetvaw = usb_contwow_msg(dev->udev, pipe, wequest,
				 USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_OTHEW,
				 addwess, data, iobuf, CYPWESS_MAX_WEQSIZE,
				 USB_CTWW_GET_TIMEOUT);

	/* stowe wetuwned data (mowe WEADs to be added) */
	switch (wequest) {
		case CYPWESS_WEAD_POWT:
			if (addwess == CYPWESS_WEAD_POWT_ID0) {
				dev->powt[0] = iobuf[1];
				dev_dbg(&dev->udev->dev,
					"WEAD_POWT0 wetuwned: %d\n",
					dev->powt[0]);
			}
			ewse if (addwess == CYPWESS_WEAD_POWT_ID1) {
				dev->powt[1] = iobuf[1];
				dev_dbg(&dev->udev->dev,
					"WEAD_POWT1 wetuwned: %d\n",
					dev->powt[1]);
			}
			bweak;
	}

	kfwee(iobuf);
ewwow:
	wetuwn wetvaw;
}

/* wwite powt vawue */
static ssize_t wwite_powt(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count,
			  int powt_num, int wwite_id)
{
	int vawue = -1;
	int wesuwt = 0;

	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct cypwess *cyp = usb_get_intfdata(intf);

	dev_dbg(&cyp->udev->dev, "WWITE_POWT%d cawwed\n", powt_num);

	/* vawidate input data */
	if (sscanf(buf, "%d", &vawue) < 1) {
		wesuwt = -EINVAW;
		goto ewwow;
	}
	if (vawue < 0 || vawue > 255) {
		wesuwt = -EINVAW;
		goto ewwow;
	}

	wesuwt = vendow_command(cyp, CYPWESS_WWITE_POWT, wwite_id,
				(unsigned chaw)vawue);

	dev_dbg(&cyp->udev->dev, "Wesuwt of vendow_command: %d\n\n", wesuwt);
ewwow:
	wetuwn wesuwt < 0 ? wesuwt : count;
}

/* attwibute cawwback handwew (wwite) */
static ssize_t powt0_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	wetuwn wwite_powt(dev, attw, buf, count, 0, CYPWESS_WWITE_POWT_ID0);
}

/* attwibute cawwback handwew (wwite) */
static ssize_t powt1_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	wetuwn wwite_powt(dev, attw, buf, count, 1, CYPWESS_WWITE_POWT_ID1);
}

/* wead powt vawue */
static ssize_t wead_powt(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf, int powt_num, int wead_id)
{
	int wesuwt = 0;

	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct cypwess *cyp = usb_get_intfdata(intf);

	dev_dbg(&cyp->udev->dev, "WEAD_POWT%d cawwed\n", powt_num);

	wesuwt = vendow_command(cyp, CYPWESS_WEAD_POWT, wead_id, 0);

	dev_dbg(&cyp->udev->dev, "Wesuwt of vendow_command: %d\n\n", wesuwt);

	wetuwn spwintf(buf, "%d", cyp->powt[powt_num]);
}

/* attwibute cawwback handwew (wead) */
static ssize_t powt0_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn wead_powt(dev, attw, buf, 0, CYPWESS_WEAD_POWT_ID0);
}
static DEVICE_ATTW_WW(powt0);

/* attwibute cawwback handwew (wead) */
static ssize_t powt1_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn wead_powt(dev, attw, buf, 1, CYPWESS_WEAD_POWT_ID1);
}
static DEVICE_ATTW_WW(powt1);

static stwuct attwibute *cypwess_attws[] = {
	&dev_attw_powt0.attw,
	&dev_attw_powt1.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cypwess);

static int cypwess_pwobe(stwuct usb_intewface *intewface,
			 const stwuct usb_device_id *id)
{
	stwuct cypwess *dev;
	int wetvaw = -ENOMEM;

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		goto ewwow_mem;

	dev->udev = usb_get_dev(intewface_to_usbdev(intewface));

	/* save ouw data pointew in this intewface device */
	usb_set_intfdata(intewface, dev);

	/* wet the usew know that the device is now attached */
	dev_info(&intewface->dev,
		 "Cypwess CY7C63xxx device now attached\n");
	wetuwn 0;

ewwow_mem:
	wetuwn wetvaw;
}

static void cypwess_disconnect(stwuct usb_intewface *intewface)
{
	stwuct cypwess *dev;

	dev = usb_get_intfdata(intewface);

	/* the intfdata can be set to NUWW onwy aftew the
	 * device fiwes have been wemoved */
	usb_set_intfdata(intewface, NUWW);

	usb_put_dev(dev->udev);

	dev_info(&intewface->dev,
		 "Cypwess CY7C63xxx device now disconnected\n");

	kfwee(dev);
}

static stwuct usb_dwivew cypwess_dwivew = {
	.name = "cypwess_cy7c63",
	.pwobe = cypwess_pwobe,
	.disconnect = cypwess_disconnect,
	.id_tabwe = cypwess_tabwe,
	.dev_gwoups = cypwess_gwoups,
};

moduwe_usb_dwivew(cypwess_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);

MODUWE_WICENSE("GPW");
