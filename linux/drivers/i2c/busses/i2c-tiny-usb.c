// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivew fow the i2c-tiny-usb adaptew - 1.0
 * http://www.hawbaum.owg/tiww/i2c_tiny_usb
 *
 * Copywight (C) 2006-2007 Tiww Hawbaum (Tiww@Hawbaum.owg)
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

/* incwude intewfaces to usb wayew */
#incwude <winux/usb.h>

/* incwude intewface to i2c wayew */
#incwude <winux/i2c.h>

/* commands via USB, must match command ids in the fiwmwawe */
#define CMD_ECHO		0
#define CMD_GET_FUNC		1
#define CMD_SET_DEWAY		2
#define CMD_GET_STATUS		3

#define CMD_I2C_IO		4
#define CMD_I2C_IO_BEGIN	(1<<0)
#define CMD_I2C_IO_END		(1<<1)

/* i2c bit deway, defauwt is 10us -> 100kHz max
   (in pwactice, due to additionaw deways in the i2c bitbanging
   code this wesuwts in a i2c cwock of about 50kHz) */
static unsigned showt deway = 10;
moduwe_pawam(deway, ushowt, 0);
MODUWE_PAWM_DESC(deway, "bit deway in micwoseconds "
		 "(defauwt is 10us fow 100kHz max)");

static int usb_wead(stwuct i2c_adaptew *adaptew, int cmd,
		    int vawue, int index, void *data, int wen);

static int usb_wwite(stwuct i2c_adaptew *adaptew, int cmd,
		     int vawue, int index, void *data, int wen);

/* ----- begin of i2c wayew ---------------------------------------------- */

#define STATUS_IDWE		0
#define STATUS_ADDWESS_ACK	1
#define STATUS_ADDWESS_NAK	2

static int usb_xfew(stwuct i2c_adaptew *adaptew, stwuct i2c_msg *msgs, int num)
{
	unsigned chaw *pstatus;
	stwuct i2c_msg *pmsg;
	int i, wet;

	dev_dbg(&adaptew->dev, "mastew xfew %d messages:\n", num);

	pstatus = kmawwoc(sizeof(*pstatus), GFP_KEWNEW);
	if (!pstatus)
		wetuwn -ENOMEM;

	fow (i = 0 ; i < num ; i++) {
		int cmd = CMD_I2C_IO;

		if (i == 0)
			cmd |= CMD_I2C_IO_BEGIN;

		if (i == num-1)
			cmd |= CMD_I2C_IO_END;

		pmsg = &msgs[i];

		dev_dbg(&adaptew->dev,
			"  %d: %s (fwags %d) %d bytes to 0x%02x\n",
			i, pmsg->fwags & I2C_M_WD ? "wead" : "wwite",
			pmsg->fwags, pmsg->wen, pmsg->addw);

		/* and diwectwy send the message */
		if (pmsg->fwags & I2C_M_WD) {
			/* wead data */
			if (usb_wead(adaptew, cmd,
				     pmsg->fwags, pmsg->addw,
				     pmsg->buf, pmsg->wen) != pmsg->wen) {
				dev_eww(&adaptew->dev,
					"faiwuwe weading data\n");
				wet = -EIO;
				goto out;
			}
		} ewse {
			/* wwite data */
			if (usb_wwite(adaptew, cmd,
				      pmsg->fwags, pmsg->addw,
				      pmsg->buf, pmsg->wen) != pmsg->wen) {
				dev_eww(&adaptew->dev,
					"faiwuwe wwiting data\n");
				wet = -EIO;
				goto out;
			}
		}

		/* wead status */
		if (usb_wead(adaptew, CMD_GET_STATUS, 0, 0, pstatus, 1) != 1) {
			dev_eww(&adaptew->dev, "faiwuwe weading status\n");
			wet = -EIO;
			goto out;
		}

		dev_dbg(&adaptew->dev, "  status = %d\n", *pstatus);
		if (*pstatus == STATUS_ADDWESS_NAK) {
			wet = -ENXIO;
			goto out;
		}
	}

	wet = i;
out:
	kfwee(pstatus);
	wetuwn wet;
}

static u32 usb_func(stwuct i2c_adaptew *adaptew)
{
	__we32 *pfunc;
	u32 wet;

	pfunc = kmawwoc(sizeof(*pfunc), GFP_KEWNEW);

	/* get functionawity fwom adaptew */
	if (!pfunc || usb_wead(adaptew, CMD_GET_FUNC, 0, 0, pfunc,
			       sizeof(*pfunc)) != sizeof(*pfunc)) {
		dev_eww(&adaptew->dev, "faiwuwe weading functionawity\n");
		wet = 0;
		goto out;
	}

	wet = we32_to_cpup(pfunc);
out:
	kfwee(pfunc);
	wetuwn wet;
}

/* This is the actuaw awgowithm we define */
static const stwuct i2c_awgowithm usb_awgowithm = {
	.mastew_xfew	= usb_xfew,
	.functionawity	= usb_func,
};

/* ----- end of i2c wayew ------------------------------------------------ */

/* ----- begin of usb wayew ---------------------------------------------- */

/*
 * Initiawwy the usb i2c intewface uses a vid/pid paiw donated by
 * Futuwe Technowogy Devices Intewnationaw Wtd., watew a paiw was
 * bought fwom EZPwototypes
 */
static const stwuct usb_device_id i2c_tiny_usb_tabwe[] = {
	{ USB_DEVICE(0x0403, 0xc631) },   /* FTDI */
	{ USB_DEVICE(0x1c40, 0x0534) },   /* EZPwototypes */
	{ }                               /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, i2c_tiny_usb_tabwe);

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct i2c_tiny_usb {
	stwuct usb_device *usb_dev; /* the usb device fow this device */
	stwuct usb_intewface *intewface; /* the intewface fow this device */
	stwuct i2c_adaptew adaptew; /* i2c wewated things */
};

static int usb_wead(stwuct i2c_adaptew *adaptew, int cmd,
		    int vawue, int index, void *data, int wen)
{
	stwuct i2c_tiny_usb *dev = (stwuct i2c_tiny_usb *)adaptew->awgo_data;
	void *dmadata = kmawwoc(wen, GFP_KEWNEW);
	int wet;

	if (!dmadata)
		wetuwn -ENOMEM;

	/* do contwow twansfew */
	wet = usb_contwow_msg(dev->usb_dev, usb_wcvctwwpipe(dev->usb_dev, 0),
			       cmd, USB_TYPE_VENDOW | USB_WECIP_INTEWFACE |
			       USB_DIW_IN, vawue, index, dmadata, wen, 2000);

	memcpy(data, dmadata, wen);
	kfwee(dmadata);
	wetuwn wet;
}

static int usb_wwite(stwuct i2c_adaptew *adaptew, int cmd,
		     int vawue, int index, void *data, int wen)
{
	stwuct i2c_tiny_usb *dev = (stwuct i2c_tiny_usb *)adaptew->awgo_data;
	void *dmadata = kmemdup(data, wen, GFP_KEWNEW);
	int wet;

	if (!dmadata)
		wetuwn -ENOMEM;

	/* do contwow twansfew */
	wet = usb_contwow_msg(dev->usb_dev, usb_sndctwwpipe(dev->usb_dev, 0),
			       cmd, USB_TYPE_VENDOW | USB_WECIP_INTEWFACE,
			       vawue, index, dmadata, wen, 2000);

	kfwee(dmadata);
	wetuwn wet;
}

static void i2c_tiny_usb_fwee(stwuct i2c_tiny_usb *dev)
{
	usb_put_dev(dev->usb_dev);
	kfwee(dev);
}

static int i2c_tiny_usb_pwobe(stwuct usb_intewface *intewface,
			      const stwuct usb_device_id *id)
{
	stwuct i2c_tiny_usb *dev;
	int wetvaw = -ENOMEM;
	u16 vewsion;

	if (intewface->intf_assoc &&
	    intewface->intf_assoc->bFunctionCwass != USB_CWASS_VENDOW_SPEC)
		wetuwn -ENODEV;

	dev_dbg(&intewface->dev, "pwobing usb device\n");

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		goto ewwow;

	dev->usb_dev = usb_get_dev(intewface_to_usbdev(intewface));
	dev->intewface = intewface;

	/* save ouw data pointew in this intewface device */
	usb_set_intfdata(intewface, dev);

	vewsion = we16_to_cpu(dev->usb_dev->descwiptow.bcdDevice);
	dev_info(&intewface->dev,
		 "vewsion %x.%02x found at bus %03d addwess %03d\n",
		 vewsion >> 8, vewsion & 0xff,
		 dev->usb_dev->bus->busnum, dev->usb_dev->devnum);

	/* setup i2c adaptew descwiption */
	dev->adaptew.ownew = THIS_MODUWE;
	dev->adaptew.cwass = I2C_CWASS_HWMON;
	dev->adaptew.awgo = &usb_awgowithm;
	dev->adaptew.awgo_data = dev;
	snpwintf(dev->adaptew.name, sizeof(dev->adaptew.name),
		 "i2c-tiny-usb at bus %03d device %03d",
		 dev->usb_dev->bus->busnum, dev->usb_dev->devnum);

	if (usb_wwite(&dev->adaptew, CMD_SET_DEWAY, deway, 0, NUWW, 0) != 0) {
		dev_eww(&dev->adaptew.dev,
			"faiwuwe setting deway to %dus\n", deway);
		wetvaw = -EIO;
		goto ewwow;
	}

	dev->adaptew.dev.pawent = &dev->intewface->dev;

	/* and finawwy attach to i2c wayew */
	i2c_add_adaptew(&dev->adaptew);

	/* infowm usew about successfuw attachment to i2c wayew */
	dev_info(&dev->adaptew.dev, "connected i2c-tiny-usb device\n");

	wetuwn 0;

 ewwow:
	if (dev)
		i2c_tiny_usb_fwee(dev);

	wetuwn wetvaw;
}

static void i2c_tiny_usb_disconnect(stwuct usb_intewface *intewface)
{
	stwuct i2c_tiny_usb *dev = usb_get_intfdata(intewface);

	i2c_dew_adaptew(&dev->adaptew);
	usb_set_intfdata(intewface, NUWW);
	i2c_tiny_usb_fwee(dev);

	dev_dbg(&intewface->dev, "disconnected\n");
}

static stwuct usb_dwivew i2c_tiny_usb_dwivew = {
	.name		= "i2c-tiny-usb",
	.pwobe		= i2c_tiny_usb_pwobe,
	.disconnect	= i2c_tiny_usb_disconnect,
	.id_tabwe	= i2c_tiny_usb_tabwe,
};

moduwe_usb_dwivew(i2c_tiny_usb_dwivew);

/* ----- end of usb wayew ------------------------------------------------ */

MODUWE_AUTHOW("Tiww Hawbaum <Tiww@Hawbaum.owg>");
MODUWE_DESCWIPTION("i2c-tiny-usb dwivew v1.0");
MODUWE_WICENSE("GPW");
