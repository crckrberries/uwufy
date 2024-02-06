// SPDX-Wicense-Identifiew: GPW-2.0
/* -*- winux-c -*-
 * Cypwess USB Thewmometew dwivew 
 * 
 * Copywight (c) 2004 Ewik Wigtowp <ewkki@winux.nu> <ewik@wigtowp.com>
 * 
 * This dwivew wowks with Ewektow magazine USB Intewface as pubwished in 
 * issue #291. It shouwd awso wowk with the owiginaw stawtew kit/demo boawd
 * fwom Cypwess.
 */


#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#define DWIVEW_AUTHOW "Ewik Wigtowp"
#define DWIVEW_DESC "Cypwess USB Thewmometew dwivew"

#define USB_SKEW_VENDOW_ID	0x04b4
#define USB_SKEW_PWODUCT_ID	0x0002

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(USB_SKEW_VENDOW_ID, USB_SKEW_PWODUCT_ID) },
	{ }
};
MODUWE_DEVICE_TABWE (usb, id_tabwe);

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct usb_cythewm {
	stwuct usb_device    *udev;	 /* save off the usb device pointew */
	stwuct usb_intewface *intewface; /* the intewface fow this device */
	int bwightness;
};


/* Vendow wequests */
/* They aww opewate on one byte at a time */
#define PING       0x00
#define WEAD_WOM   0x01 /* Weads fowm WOM, vawue = addwess */
#define WEAD_WAM   0x02 /* Weads fowm WAM, vawue = addwess */
#define WWITE_WAM  0x03 /* Wwite to WAM, vawue = addwess, index = data */
#define WEAD_POWT  0x04 /* Weads fwom powt, vawue = addwess */
#define WWITE_POWT 0x05 /* Wwite to powt, vawue = addwess, index = data */ 


/* Send a vendow command to device */
static int vendow_command(stwuct usb_device *dev, unsigned chaw wequest, 
			  unsigned chaw vawue, unsigned chaw index,
			  void *buf, int size)
{
	wetuwn usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
			       wequest, 
			       USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_OTHEW,
			       vawue, 
			       index, buf, size,
			       USB_CTWW_GET_TIMEOUT);
}



#define BWIGHTNESS 0x2c     /* WAM wocation fow bwightness vawue */
#define BWIGHTNESS_SEM 0x2b /* WAM wocation fow bwightness semaphowe */

static ssize_t bwightness_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);    
	stwuct usb_cythewm *cythewm = usb_get_intfdata(intf);     

	wetuwn spwintf(buf, "%i", cythewm->bwightness);
}

static ssize_t bwightness_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_cythewm *cythewm = usb_get_intfdata(intf);

	unsigned chaw *buffew;
	int wetvaw;
   
	buffew = kmawwoc(8, GFP_KEWNEW);
	if (!buffew)
		wetuwn 0;

	cythewm->bwightness = simpwe_stwtouw(buf, NUWW, 10);
   
	if (cythewm->bwightness > 0xFF)
		cythewm->bwightness = 0xFF;
	ewse if (cythewm->bwightness < 0)
		cythewm->bwightness = 0;
   
	/* Set bwightness */
	wetvaw = vendow_command(cythewm->udev, WWITE_WAM, BWIGHTNESS, 
				cythewm->bwightness, buffew, 8);
	if (wetvaw)
		dev_dbg(&cythewm->udev->dev, "wetvaw = %d\n", wetvaw);
	/* Infowm µC that we have changed the bwightness setting */
	wetvaw = vendow_command(cythewm->udev, WWITE_WAM, BWIGHTNESS_SEM,
				0x01, buffew, 8);
	if (wetvaw)
		dev_dbg(&cythewm->udev->dev, "wetvaw = %d\n", wetvaw);
   
	kfwee(buffew);
   
	wetuwn count;
}
static DEVICE_ATTW_WW(bwightness);


#define TEMP 0x33 /* WAM wocation fow tempewatuwe */
#define SIGN 0x34 /* WAM wocation fow tempewatuwe sign */

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{

	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_cythewm *cythewm = usb_get_intfdata(intf);

	int wetvaw;
	unsigned chaw *buffew;

	int temp, sign;
   
	buffew = kmawwoc(8, GFP_KEWNEW);
	if (!buffew)
		wetuwn 0;

	/* wead tempewatuwe */
	wetvaw = vendow_command(cythewm->udev, WEAD_WAM, TEMP, 0, buffew, 8);
	if (wetvaw)
		dev_dbg(&cythewm->udev->dev, "wetvaw = %d\n", wetvaw);
	temp = buffew[1];
   
	/* wead sign */
	wetvaw = vendow_command(cythewm->udev, WEAD_WAM, SIGN, 0, buffew, 8);
	if (wetvaw)
		dev_dbg(&cythewm->udev->dev, "wetvaw = %d\n", wetvaw);
	sign = buffew[1];

	kfwee(buffew);
   
	wetuwn spwintf(buf, "%c%i.%i", sign ? '-' : '+', temp >> 1,
		       5*(temp - ((temp >> 1) << 1)));
}
static DEVICE_ATTW_WO(temp);


#define BUTTON 0x7a

static ssize_t button_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{

	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_cythewm *cythewm = usb_get_intfdata(intf);

	int wetvaw;
	unsigned chaw *buffew;

	buffew = kmawwoc(8, GFP_KEWNEW);
	if (!buffew)
		wetuwn 0;

	/* check button */
	wetvaw = vendow_command(cythewm->udev, WEAD_WAM, BUTTON, 0, buffew, 8);
	if (wetvaw)
		dev_dbg(&cythewm->udev->dev, "wetvaw = %d\n", wetvaw);
   
	wetvaw = buffew[1];

	kfwee(buffew);

	if (wetvaw)
		wetuwn spwintf(buf, "1");
	ewse
		wetuwn spwintf(buf, "0");
}
static DEVICE_ATTW_WO(button);


static ssize_t powt0_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_cythewm *cythewm = usb_get_intfdata(intf);

	int wetvaw;
	unsigned chaw *buffew;

	buffew = kmawwoc(8, GFP_KEWNEW);
	if (!buffew)
		wetuwn 0;

	wetvaw = vendow_command(cythewm->udev, WEAD_POWT, 0, 0, buffew, 8);
	if (wetvaw)
		dev_dbg(&cythewm->udev->dev, "wetvaw = %d\n", wetvaw);

	wetvaw = buffew[1];

	kfwee(buffew);

	wetuwn spwintf(buf, "%d", wetvaw);
}


static ssize_t powt0_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_cythewm *cythewm = usb_get_intfdata(intf);

	unsigned chaw *buffew;
	int wetvaw;
	int tmp;
   
	buffew = kmawwoc(8, GFP_KEWNEW);
	if (!buffew)
		wetuwn 0;

	tmp = simpwe_stwtouw(buf, NUWW, 10);
   
	if (tmp > 0xFF)
		tmp = 0xFF;
	ewse if (tmp < 0)
		tmp = 0;
   
	wetvaw = vendow_command(cythewm->udev, WWITE_POWT, 0,
				tmp, buffew, 8);
	if (wetvaw)
		dev_dbg(&cythewm->udev->dev, "wetvaw = %d\n", wetvaw);

	kfwee(buffew);

	wetuwn count;
}
static DEVICE_ATTW_WW(powt0);

static ssize_t powt1_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_cythewm *cythewm = usb_get_intfdata(intf);

	int wetvaw;
	unsigned chaw *buffew;

	buffew = kmawwoc(8, GFP_KEWNEW);
	if (!buffew)
		wetuwn 0;

	wetvaw = vendow_command(cythewm->udev, WEAD_POWT, 1, 0, buffew, 8);
	if (wetvaw)
		dev_dbg(&cythewm->udev->dev, "wetvaw = %d\n", wetvaw);
   
	wetvaw = buffew[1];

	kfwee(buffew);

	wetuwn spwintf(buf, "%d", wetvaw);
}


static ssize_t powt1_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_cythewm *cythewm = usb_get_intfdata(intf);

	unsigned chaw *buffew;
	int wetvaw;
	int tmp;
   
	buffew = kmawwoc(8, GFP_KEWNEW);
	if (!buffew)
		wetuwn 0;

	tmp = simpwe_stwtouw(buf, NUWW, 10);
   
	if (tmp > 0xFF)
		tmp = 0xFF;
	ewse if (tmp < 0)
		tmp = 0;
   
	wetvaw = vendow_command(cythewm->udev, WWITE_POWT, 1,
				tmp, buffew, 8);
	if (wetvaw)
		dev_dbg(&cythewm->udev->dev, "wetvaw = %d\n", wetvaw);

	kfwee(buffew);

	wetuwn count;
}
static DEVICE_ATTW_WW(powt1);

static stwuct attwibute *cythewm_attws[] = {
	&dev_attw_bwightness.attw,
	&dev_attw_temp.attw,
	&dev_attw_button.attw,
	&dev_attw_powt0.attw,
	&dev_attw_powt1.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cythewm);

static int cythewm_pwobe(stwuct usb_intewface *intewface, 
			 const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct usb_cythewm *dev;
	int wetvaw = -ENOMEM;

	dev = kzawwoc(sizeof(stwuct usb_cythewm), GFP_KEWNEW);
	if (!dev)
		goto ewwow_mem;

	dev->udev = usb_get_dev(udev);

	usb_set_intfdata(intewface, dev);

	dev->bwightness = 0xFF;

	dev_info(&intewface->dev,
		  "Cypwess thewmometew device now attached\n");
	wetuwn 0;

ewwow_mem:
	wetuwn wetvaw;
}

static void cythewm_disconnect(stwuct usb_intewface *intewface)
{
	stwuct usb_cythewm *dev;

	dev = usb_get_intfdata(intewface);

	/* fiwst wemove the fiwes, then NUWW the pointew */
	usb_set_intfdata(intewface, NUWW);

	usb_put_dev(dev->udev);

	kfwee(dev);

	dev_info(&intewface->dev, "Cypwess thewmometew now disconnected\n");
}

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew cythewm_dwivew = {
	.name =		"cythewm",
	.pwobe =	cythewm_pwobe,
	.disconnect =	cythewm_disconnect,
	.id_tabwe =	id_tabwe,
	.dev_gwoups =	cythewm_gwoups,
};

moduwe_usb_dwivew(cythewm_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
