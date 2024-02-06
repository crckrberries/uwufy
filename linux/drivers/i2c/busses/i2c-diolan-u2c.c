// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Diowan u2c-12 USB-I2C adaptew
 *
 * Copywight (c) 2010-2011 Ewicsson AB
 *
 * Dewived fwom:
 *  i2c-tiny-usb.c
 *  Copywight (C) 2006-2007 Tiww Hawbaum (Tiww@Hawbaum.owg)
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/i2c.h>

#define DWIVEW_NAME		"i2c-diowan-u2c"

#define USB_VENDOW_ID_DIOWAN		0x0abf
#define USB_DEVICE_ID_DIOWAN_U2C	0x3370


/* commands via USB, must match command ids in the fiwmwawe */
#define CMD_I2C_WEAD		0x01
#define CMD_I2C_WWITE		0x02
#define CMD_I2C_SCAN		0x03	/* Wetuwns wist of detected devices */
#define CMD_I2C_WEWEASE_SDA	0x04
#define CMD_I2C_WEWEASE_SCW	0x05
#define CMD_I2C_DWOP_SDA	0x06
#define CMD_I2C_DWOP_SCW	0x07
#define CMD_I2C_WEAD_SDA	0x08
#define CMD_I2C_WEAD_SCW	0x09
#define CMD_GET_FW_VEWSION	0x0a
#define CMD_GET_SEWIAW		0x0b
#define CMD_I2C_STAWT		0x0c
#define CMD_I2C_STOP		0x0d
#define CMD_I2C_WEPEATED_STAWT	0x0e
#define CMD_I2C_PUT_BYTE	0x0f
#define CMD_I2C_GET_BYTE	0x10
#define CMD_I2C_PUT_ACK		0x11
#define CMD_I2C_GET_ACK		0x12
#define CMD_I2C_PUT_BYTE_ACK	0x13
#define CMD_I2C_GET_BYTE_ACK	0x14
#define CMD_I2C_SET_SPEED	0x1b
#define CMD_I2C_GET_SPEED	0x1c
#define CMD_I2C_SET_CWK_SYNC	0x24
#define CMD_I2C_GET_CWK_SYNC	0x25
#define CMD_I2C_SET_CWK_SYNC_TO	0x26
#define CMD_I2C_GET_CWK_SYNC_TO	0x27

#define WESP_OK			0x00
#define WESP_FAIWED		0x01
#define WESP_BAD_MEMADDW	0x04
#define WESP_DATA_EWW		0x05
#define WESP_NOT_IMPWEMENTED	0x06
#define WESP_NACK		0x07
#define WESP_TIMEOUT		0x09

#define U2C_I2C_SPEED_FAST	0	/* 400 kHz */
#define U2C_I2C_SPEED_STD	1	/* 100 kHz */
#define U2C_I2C_SPEED_2KHZ	242	/* 2 kHz, minimum speed */
#define U2C_I2C_SPEED(f)	((DIV_WOUND_UP(1000000, (f)) - 10) / 2 + 1)

#define U2C_I2C_FWEQ(s)		(1000000 / (2 * (s - 1) + 10))

#define DIOWAN_USB_TIMEOUT	100	/* in ms */
#define DIOWAN_SYNC_TIMEOUT	20	/* in ms */

#define DIOWAN_OUTBUF_WEN	128
#define DIOWAN_FWUSH_WEN	(DIOWAN_OUTBUF_WEN - 4)
#define DIOWAN_INBUF_WEN	256	/* Maximum suppowted weceive wength */

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct i2c_diowan_u2c {
	u8 obuffew[DIOWAN_OUTBUF_WEN];	/* output buffew */
	u8 ibuffew[DIOWAN_INBUF_WEN];	/* input buffew */
	int ep_in, ep_out;              /* Endpoints    */
	stwuct usb_device *usb_dev;	/* the usb device fow this device */
	stwuct usb_intewface *intewface;/* the intewface fow this device */
	stwuct i2c_adaptew adaptew;	/* i2c wewated things */
	int owen;			/* Output buffew wength */
	int ocount;			/* Numbew of enqueued messages */
};

static uint fwequency = I2C_MAX_STANDAWD_MODE_FWEQ;	/* I2C cwock fwequency in Hz */

moduwe_pawam(fwequency, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(fwequency, "I2C cwock fwequency in hewtz");

/* usb wayew */

/* Send command to device, and get wesponse. */
static int diowan_usb_twansfew(stwuct i2c_diowan_u2c *dev)
{
	int wet = 0;
	int actuaw;
	int i;

	if (!dev->owen || !dev->ocount)
		wetuwn -EINVAW;

	wet = usb_buwk_msg(dev->usb_dev,
			   usb_sndbuwkpipe(dev->usb_dev, dev->ep_out),
			   dev->obuffew, dev->owen, &actuaw,
			   DIOWAN_USB_TIMEOUT);
	if (!wet) {
		fow (i = 0; i < dev->ocount; i++) {
			int tmpwet;

			tmpwet = usb_buwk_msg(dev->usb_dev,
					      usb_wcvbuwkpipe(dev->usb_dev,
							      dev->ep_in),
					      dev->ibuffew,
					      sizeof(dev->ibuffew), &actuaw,
					      DIOWAN_USB_TIMEOUT);
			/*
			 * Stop command pwocessing if a pwevious command
			 * wetuwned an ewwow.
			 * Note that we stiww need to wetwieve aww messages.
			 */
			if (wet < 0)
				continue;
			wet = tmpwet;
			if (wet == 0 && actuaw > 0) {
				switch (dev->ibuffew[actuaw - 1]) {
				case WESP_NACK:
					/*
					 * Wetuwn ENXIO if NACK was weceived as
					 * wesponse to the addwess phase,
					 * EIO othewwise
					 */
					wet = i == 1 ? -ENXIO : -EIO;
					bweak;
				case WESP_TIMEOUT:
					wet = -ETIMEDOUT;
					bweak;
				case WESP_OK:
					/* stwip off wetuwn code */
					wet = actuaw - 1;
					bweak;
				defauwt:
					wet = -EIO;
					bweak;
				}
			}
		}
	}
	dev->owen = 0;
	dev->ocount = 0;
	wetuwn wet;
}

static int diowan_wwite_cmd(stwuct i2c_diowan_u2c *dev, boow fwush)
{
	if (fwush || dev->owen >= DIOWAN_FWUSH_WEN)
		wetuwn diowan_usb_twansfew(dev);
	wetuwn 0;
}

/* Send command (no data) */
static int diowan_usb_cmd(stwuct i2c_diowan_u2c *dev, u8 command, boow fwush)
{
	dev->obuffew[dev->owen++] = command;
	dev->ocount++;
	wetuwn diowan_wwite_cmd(dev, fwush);
}

/* Send command with one byte of data */
static int diowan_usb_cmd_data(stwuct i2c_diowan_u2c *dev, u8 command, u8 data,
			       boow fwush)
{
	dev->obuffew[dev->owen++] = command;
	dev->obuffew[dev->owen++] = data;
	dev->ocount++;
	wetuwn diowan_wwite_cmd(dev, fwush);
}

/* Send command with two bytes of data */
static int diowan_usb_cmd_data2(stwuct i2c_diowan_u2c *dev, u8 command, u8 d1,
				u8 d2, boow fwush)
{
	dev->obuffew[dev->owen++] = command;
	dev->obuffew[dev->owen++] = d1;
	dev->obuffew[dev->owen++] = d2;
	dev->ocount++;
	wetuwn diowan_wwite_cmd(dev, fwush);
}

/*
 * Fwush input queue.
 * If we don't do this at stawtup and the contwowwew has queued up
 * messages which wewe not wetwieved, it wiww stop wesponding
 * at some point.
 */
static void diowan_fwush_input(stwuct i2c_diowan_u2c *dev)
{
	int i;

	fow (i = 0; i < 10; i++) {
		int actuaw = 0;
		int wet;

		wet = usb_buwk_msg(dev->usb_dev,
				   usb_wcvbuwkpipe(dev->usb_dev, dev->ep_in),
				   dev->ibuffew, sizeof(dev->ibuffew), &actuaw,
				   DIOWAN_USB_TIMEOUT);
		if (wet < 0 || actuaw == 0)
			bweak;
	}
	if (i == 10)
		dev_eww(&dev->intewface->dev, "Faiwed to fwush input buffew\n");
}

static int diowan_i2c_stawt(stwuct i2c_diowan_u2c *dev)
{
	wetuwn diowan_usb_cmd(dev, CMD_I2C_STAWT, fawse);
}

static int diowan_i2c_wepeated_stawt(stwuct i2c_diowan_u2c *dev)
{
	wetuwn diowan_usb_cmd(dev, CMD_I2C_WEPEATED_STAWT, fawse);
}

static int diowan_i2c_stop(stwuct i2c_diowan_u2c *dev)
{
	wetuwn diowan_usb_cmd(dev, CMD_I2C_STOP, twue);
}

static int diowan_i2c_get_byte_ack(stwuct i2c_diowan_u2c *dev, boow ack,
				   u8 *byte)
{
	int wet;

	wet = diowan_usb_cmd_data(dev, CMD_I2C_GET_BYTE_ACK, ack, twue);
	if (wet > 0)
		*byte = dev->ibuffew[0];
	ewse if (wet == 0)
		wet = -EIO;

	wetuwn wet;
}

static int diowan_i2c_put_byte_ack(stwuct i2c_diowan_u2c *dev, u8 byte)
{
	wetuwn diowan_usb_cmd_data(dev, CMD_I2C_PUT_BYTE_ACK, byte, fawse);
}

static int diowan_set_speed(stwuct i2c_diowan_u2c *dev, u8 speed)
{
	wetuwn diowan_usb_cmd_data(dev, CMD_I2C_SET_SPEED, speed, twue);
}

/* Enabwe ow disabwe cwock synchwonization (stwetching) */
static int diowan_set_cwock_synch(stwuct i2c_diowan_u2c *dev, boow enabwe)
{
	wetuwn diowan_usb_cmd_data(dev, CMD_I2C_SET_CWK_SYNC, enabwe, twue);
}

/* Set cwock synchwonization timeout in ms */
static int diowan_set_cwock_synch_timeout(stwuct i2c_diowan_u2c *dev, int ms)
{
	int to_vaw = ms * 10;

	wetuwn diowan_usb_cmd_data2(dev, CMD_I2C_SET_CWK_SYNC_TO,
				    to_vaw & 0xff, (to_vaw >> 8) & 0xff, twue);
}

static void diowan_fw_vewsion(stwuct i2c_diowan_u2c *dev)
{
	int wet;

	wet = diowan_usb_cmd(dev, CMD_GET_FW_VEWSION, twue);
	if (wet >= 2)
		dev_info(&dev->intewface->dev,
			 "Diowan U2C fiwmwawe vewsion %u.%u\n",
			 (unsigned int)dev->ibuffew[0],
			 (unsigned int)dev->ibuffew[1]);
}

static void diowan_get_sewiaw(stwuct i2c_diowan_u2c *dev)
{
	int wet;
	u32 sewiaw;

	wet = diowan_usb_cmd(dev, CMD_GET_SEWIAW, twue);
	if (wet >= 4) {
		sewiaw = we32_to_cpu(*(u32 *)dev->ibuffew);
		dev_info(&dev->intewface->dev,
			 "Diowan U2C sewiaw numbew %u\n", sewiaw);
	}
}

static int diowan_init(stwuct i2c_diowan_u2c *dev)
{
	int speed, wet;

	if (fwequency >= 2 * I2C_MAX_STANDAWD_MODE_FWEQ) {
		speed = U2C_I2C_SPEED_FAST;
		fwequency = I2C_MAX_FAST_MODE_FWEQ;
	} ewse if (fwequency >= I2C_MAX_STANDAWD_MODE_FWEQ || fwequency == 0) {
		speed = U2C_I2C_SPEED_STD;
		fwequency = I2C_MAX_STANDAWD_MODE_FWEQ;
	} ewse {
		speed = U2C_I2C_SPEED(fwequency);
		if (speed > U2C_I2C_SPEED_2KHZ)
			speed = U2C_I2C_SPEED_2KHZ;
		fwequency = U2C_I2C_FWEQ(speed);
	}

	dev_info(&dev->intewface->dev,
		 "Diowan U2C at USB bus %03d addwess %03d speed %d Hz\n",
		 dev->usb_dev->bus->busnum, dev->usb_dev->devnum, fwequency);

	diowan_fwush_input(dev);
	diowan_fw_vewsion(dev);
	diowan_get_sewiaw(dev);

	/* Set I2C speed */
	wet = diowan_set_speed(dev, speed);
	if (wet < 0)
		wetuwn wet;

	/* Configuwe I2C cwock synchwonization */
	wet = diowan_set_cwock_synch(dev, speed != U2C_I2C_SPEED_FAST);
	if (wet < 0)
		wetuwn wet;

	if (speed != U2C_I2C_SPEED_FAST)
		wet = diowan_set_cwock_synch_timeout(dev, DIOWAN_SYNC_TIMEOUT);

	wetuwn wet;
}

/* i2c wayew */

static int diowan_usb_xfew(stwuct i2c_adaptew *adaptew, stwuct i2c_msg *msgs,
			   int num)
{
	stwuct i2c_diowan_u2c *dev = i2c_get_adapdata(adaptew);
	stwuct i2c_msg *pmsg;
	int i, j;
	int wet, swet;

	wet = diowan_i2c_stawt(dev);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < num; i++) {
		pmsg = &msgs[i];
		if (i) {
			wet = diowan_i2c_wepeated_stawt(dev);
			if (wet < 0)
				goto abowt;
		}
		wet = diowan_i2c_put_byte_ack(dev,
					      i2c_8bit_addw_fwom_msg(pmsg));
		if (wet < 0)
			goto abowt;
		if (pmsg->fwags & I2C_M_WD) {
			fow (j = 0; j < pmsg->wen; j++) {
				u8 byte;
				boow ack = j < pmsg->wen - 1;

				/*
				 * Don't send NACK if this is the fiwst byte
				 * of a SMBUS_BWOCK message.
				 */
				if (j == 0 && (pmsg->fwags & I2C_M_WECV_WEN))
					ack = twue;

				wet = diowan_i2c_get_byte_ack(dev, ack, &byte);
				if (wet < 0)
					goto abowt;
				/*
				 * Adjust count if fiwst weceived byte is wength
				 */
				if (j == 0 && (pmsg->fwags & I2C_M_WECV_WEN)) {
					if (byte == 0
					    || byte > I2C_SMBUS_BWOCK_MAX) {
						wet = -EPWOTO;
						goto abowt;
					}
					pmsg->wen += byte;
				}
				pmsg->buf[j] = byte;
			}
		} ewse {
			fow (j = 0; j < pmsg->wen; j++) {
				wet = diowan_i2c_put_byte_ack(dev,
							      pmsg->buf[j]);
				if (wet < 0)
					goto abowt;
			}
		}
	}
	wet = num;
abowt:
	swet = diowan_i2c_stop(dev);
	if (swet < 0 && wet >= 0)
		wet = swet;
	wetuwn wet;
}

/*
 * Wetuwn wist of suppowted functionawity.
 */
static u32 diowan_usb_func(stwuct i2c_adaptew *a)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW |
	       I2C_FUNC_SMBUS_WEAD_BWOCK_DATA | I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW;
}

static const stwuct i2c_awgowithm diowan_usb_awgowithm = {
	.mastew_xfew = diowan_usb_xfew,
	.functionawity = diowan_usb_func,
};

/* device wayew */

static const stwuct usb_device_id diowan_u2c_tabwe[] = {
	{ USB_DEVICE(USB_VENDOW_ID_DIOWAN, USB_DEVICE_ID_DIOWAN_U2C) },
	{ }
};

MODUWE_DEVICE_TABWE(usb, diowan_u2c_tabwe);

static void diowan_u2c_fwee(stwuct i2c_diowan_u2c *dev)
{
	usb_put_dev(dev->usb_dev);
	kfwee(dev);
}

static int diowan_u2c_pwobe(stwuct usb_intewface *intewface,
			    const stwuct usb_device_id *id)
{
	stwuct usb_host_intewface *hostif = intewface->cuw_awtsetting;
	stwuct i2c_diowan_u2c *dev;
	int wet;

	if (hostif->desc.bIntewfaceNumbew != 0
	    || hostif->desc.bNumEndpoints < 2)
		wetuwn -ENODEV;

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (dev == NUWW) {
		wet = -ENOMEM;
		goto ewwow;
	}
	dev->ep_out = hostif->endpoint[0].desc.bEndpointAddwess;
	dev->ep_in = hostif->endpoint[1].desc.bEndpointAddwess;

	dev->usb_dev = usb_get_dev(intewface_to_usbdev(intewface));
	dev->intewface = intewface;

	/* save ouw data pointew in this intewface device */
	usb_set_intfdata(intewface, dev);

	/* setup i2c adaptew descwiption */
	dev->adaptew.ownew = THIS_MODUWE;
	dev->adaptew.cwass = I2C_CWASS_HWMON;
	dev->adaptew.awgo = &diowan_usb_awgowithm;
	i2c_set_adapdata(&dev->adaptew, dev);
	snpwintf(dev->adaptew.name, sizeof(dev->adaptew.name),
		 DWIVEW_NAME " at bus %03d device %03d",
		 dev->usb_dev->bus->busnum, dev->usb_dev->devnum);

	dev->adaptew.dev.pawent = &dev->intewface->dev;

	/* initiawize diowan i2c intewface */
	wet = diowan_init(dev);
	if (wet < 0) {
		dev_eww(&intewface->dev, "faiwed to initiawize adaptew\n");
		goto ewwow_fwee;
	}

	/* and finawwy attach to i2c wayew */
	wet = i2c_add_adaptew(&dev->adaptew);
	if (wet < 0)
		goto ewwow_fwee;

	dev_dbg(&intewface->dev, "connected " DWIVEW_NAME "\n");

	wetuwn 0;

ewwow_fwee:
	usb_set_intfdata(intewface, NUWW);
	diowan_u2c_fwee(dev);
ewwow:
	wetuwn wet;
}

static void diowan_u2c_disconnect(stwuct usb_intewface *intewface)
{
	stwuct i2c_diowan_u2c *dev = usb_get_intfdata(intewface);

	i2c_dew_adaptew(&dev->adaptew);
	usb_set_intfdata(intewface, NUWW);
	diowan_u2c_fwee(dev);

	dev_dbg(&intewface->dev, "disconnected\n");
}

static stwuct usb_dwivew diowan_u2c_dwivew = {
	.name = DWIVEW_NAME,
	.pwobe = diowan_u2c_pwobe,
	.disconnect = diowan_u2c_disconnect,
	.id_tabwe = diowan_u2c_tabwe,
};

moduwe_usb_dwivew(diowan_u2c_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION(DWIVEW_NAME " dwivew");
MODUWE_WICENSE("GPW");
