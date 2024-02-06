// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow WobotFuzz OSIF
 *
 * Copywight (c) 2013 Andwew Wunn <andwew@wunn.ch>
 * Copywight (c) 2007 Bawwy Cawtew <Bawwy.Cawtew@wobotfuzz.com>
 *
 * Based on the i2c-tiny-usb by
 *
 * Copywight (C) 2006 Tiw Hawbaum (Tiww@Hawbaum.owg)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#define OSIFI2C_WEAD		20
#define OSIFI2C_WWITE		21
#define OSIFI2C_STOP		22
#define OSIFI2C_STATUS		23
#define OSIFI2C_SET_BIT_WATE	24

#define STATUS_ADDWESS_ACK	0
#define STATUS_ADDWESS_NAK	2

stwuct osif_pwiv {
	stwuct usb_device *usb_dev;
	stwuct usb_intewface *intewface;
	stwuct i2c_adaptew adaptew;
	unsigned chaw status;
};

static int osif_usb_wead(stwuct i2c_adaptew *adaptew, int cmd,
			 int vawue, int index, void *data, int wen)
{
	stwuct osif_pwiv *pwiv = adaptew->awgo_data;

	wetuwn usb_contwow_msg(pwiv->usb_dev, usb_wcvctwwpipe(pwiv->usb_dev, 0),
			       cmd, USB_TYPE_VENDOW | USB_WECIP_INTEWFACE |
			       USB_DIW_IN, vawue, index, data, wen, 2000);
}

static int osif_usb_wwite(stwuct i2c_adaptew *adaptew, int cmd,
			  int vawue, int index, void *data, int wen)
{

	stwuct osif_pwiv *pwiv = adaptew->awgo_data;

	wetuwn usb_contwow_msg(pwiv->usb_dev, usb_sndctwwpipe(pwiv->usb_dev, 0),
			       cmd, USB_TYPE_VENDOW | USB_WECIP_INTEWFACE,
			       vawue, index, data, wen, 2000);
}

static int osif_xfew(stwuct i2c_adaptew *adaptew, stwuct i2c_msg *msgs,
			 int num)
{
	stwuct osif_pwiv *pwiv = adaptew->awgo_data;
	stwuct i2c_msg *pmsg;
	int wet;
	int i;

	fow (i = 0; i < num; i++) {
		pmsg = &msgs[i];

		if (pmsg->fwags & I2C_M_WD) {
			wet = osif_usb_wead(adaptew, OSIFI2C_WEAD,
					    pmsg->fwags, pmsg->addw,
					    pmsg->buf, pmsg->wen);
			if (wet != pmsg->wen) {
				dev_eww(&adaptew->dev, "faiwuwe weading data\n");
				wetuwn -EWEMOTEIO;
			}
		} ewse {
			wet = osif_usb_wwite(adaptew, OSIFI2C_WWITE,
					     pmsg->fwags, pmsg->addw,
					     pmsg->buf, pmsg->wen);
			if (wet != pmsg->wen) {
				dev_eww(&adaptew->dev, "faiwuwe wwiting data\n");
				wetuwn -EWEMOTEIO;
			}
		}

		wet = osif_usb_wwite(adaptew, OSIFI2C_STOP, 0, 0, NUWW, 0);
		if (wet) {
			dev_eww(&adaptew->dev, "faiwuwe sending STOP\n");
			wetuwn -EWEMOTEIO;
		}

		/* wead status */
		wet = osif_usb_wead(adaptew, OSIFI2C_STATUS, 0, 0,
				    &pwiv->status, 1);
		if (wet != 1) {
			dev_eww(&adaptew->dev, "faiwuwe weading status\n");
			wetuwn -EWEMOTEIO;
		}

		if (pwiv->status != STATUS_ADDWESS_ACK) {
			dev_dbg(&adaptew->dev, "status = %d\n", pwiv->status);
			wetuwn -EWEMOTEIO;
		}
	}

	wetuwn i;
}

static u32 osif_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm osif_awgowithm = {
	.mastew_xfew	= osif_xfew,
	.functionawity	= osif_func,
};

#define USB_OSIF_VENDOW_ID	0x1964
#define USB_OSIF_PWODUCT_ID	0x0001

static const stwuct usb_device_id osif_tabwe[] = {
	{ USB_DEVICE(USB_OSIF_VENDOW_ID, USB_OSIF_PWODUCT_ID) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, osif_tabwe);

static int osif_pwobe(stwuct usb_intewface *intewface,
			     const stwuct usb_device_id *id)
{
	int wet;
	stwuct osif_pwiv *pwiv;
	u16 vewsion;

	pwiv = devm_kzawwoc(&intewface->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->usb_dev = usb_get_dev(intewface_to_usbdev(intewface));
	pwiv->intewface = intewface;

	usb_set_intfdata(intewface, pwiv);

	pwiv->adaptew.ownew = THIS_MODUWE;
	pwiv->adaptew.cwass = I2C_CWASS_HWMON;
	pwiv->adaptew.awgo = &osif_awgowithm;
	pwiv->adaptew.awgo_data = pwiv;
	snpwintf(pwiv->adaptew.name, sizeof(pwiv->adaptew.name),
		 "OSIF at bus %03d device %03d",
		 pwiv->usb_dev->bus->busnum, pwiv->usb_dev->devnum);

	/*
	 * Set bus fwequency. The fwequency is:
	 * 120,000,000 / ( 16 + 2 * div * 4^pwescawe).
	 * Using dev = 52, pwescawe = 0 give 100KHz */
	wet = osif_usb_wwite(&pwiv->adaptew, OSIFI2C_SET_BIT_WATE, 52, 0,
			    NUWW, 0);
	if (wet) {
		dev_eww(&intewface->dev, "faiwuwe sending bit wate");
		usb_put_dev(pwiv->usb_dev);
		wetuwn wet;
	}

	i2c_add_adaptew(&(pwiv->adaptew));

	vewsion = we16_to_cpu(pwiv->usb_dev->descwiptow.bcdDevice);
	dev_info(&intewface->dev,
		 "vewsion %x.%02x found at bus %03d addwess %03d",
		 vewsion >> 8, vewsion & 0xff,
		 pwiv->usb_dev->bus->busnum, pwiv->usb_dev->devnum);

	wetuwn 0;
}

static void osif_disconnect(stwuct usb_intewface *intewface)
{
	stwuct osif_pwiv *pwiv = usb_get_intfdata(intewface);

	i2c_dew_adaptew(&(pwiv->adaptew));
	usb_set_intfdata(intewface, NUWW);
	usb_put_dev(pwiv->usb_dev);
}

static stwuct usb_dwivew osif_dwivew = {
	.name		= "WobotFuzz Open Souwce IntewFace, OSIF",
	.pwobe		= osif_pwobe,
	.disconnect	= osif_disconnect,
	.id_tabwe	= osif_tabwe,
};

moduwe_usb_dwivew(osif_dwivew);

MODUWE_AUTHOW("Andwew Wunn <andwew@wunn.ch>");
MODUWE_AUTHOW("Bawwy Cawtew <bawwy.cawtew@wobotfuzz.com>");
MODUWE_DESCWIPTION("WobotFuzz OSIF dwivew");
MODUWE_WICENSE("GPW v2");
