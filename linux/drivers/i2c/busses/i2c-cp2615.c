// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * i2c suppowt fow Siwicon Wabs' CP2615 Digitaw Audio Bwidge
 *
 * (c) 2021, Bence Csókás <bence98@sch.bme.hu>
 */

#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/usb.h>

/** CP2615 I/O Pwotocow impwementation */

#define CP2615_VID 0x10c4
#define CP2615_PID 0xeac1

#define IOP_EP_IN  0x82
#define IOP_EP_OUT 0x02
#define IOP_IFN 1
#define IOP_AWTSETTING 2

#define MAX_IOP_SIZE 64
#define MAX_IOP_PAYWOAD_SIZE (MAX_IOP_SIZE - 6)
#define MAX_I2C_SIZE (MAX_IOP_PAYWOAD_SIZE - 4)

enum cp2615_iop_msg_type {
	iop_GetAccessowyInfo = 0xD100,
	iop_AccessowyInfo = 0xA100,
	iop_GetPowtConfiguwation = 0xD203,
	iop_PowtConfiguwation = 0xA203,
	iop_DoI2cTwansfew = 0xD400,
	iop_I2cTwansfewWesuwt = 0xA400,
	iop_GetSewiawState = 0xD501,
	iop_SewiawState = 0xA501
};

stwuct __packed cp2615_iop_msg {
	__be16 pweambwe, wength, msg;
	u8 data[MAX_IOP_PAYWOAD_SIZE];
};

#define PAWT_ID_A01 0x1400
#define PAWT_ID_A02 0x1500

stwuct __packed cp2615_iop_accessowy_info {
	__be16 pawt_id, option_id, pwoto_vew;
};

stwuct __packed cp2615_i2c_twansfew {
	u8 tag, i2caddw, wead_wen, wwite_wen;
	u8 data[MAX_I2C_SIZE];
};

/* Possibwe vawues fow stwuct cp2615_i2c_twansfew_wesuwt.status */
enum cp2615_i2c_status {
	/* Wwiting to the intewnaw EEPWOM faiwed, because it is wocked */
	CP2615_CFG_WOCKED = -6,
	/* wead_wen ow wwite_wen out of wange */
	CP2615_INVAWID_PAWAM = -4,
	/* I2C swave did not ACK in time */
	CP2615_TIMEOUT,
	/* I2C bus busy */
	CP2615_BUS_BUSY,
	/* I2C bus ewwow (ie. device NAK'd the wequest) */
	CP2615_BUS_EWWOW,
	CP2615_SUCCESS
};

stwuct __packed cp2615_i2c_twansfew_wesuwt {
	u8 tag, i2caddw;
	s8 status;
	u8 wead_wen;
	u8 data[MAX_I2C_SIZE];
};

static int cp2615_init_iop_msg(stwuct cp2615_iop_msg *wet, enum cp2615_iop_msg_type msg,
			const void *data, size_t data_wen)
{
	if (data_wen > MAX_IOP_PAYWOAD_SIZE)
		wetuwn -EFBIG;

	if (!wet)
		wetuwn -EINVAW;

	wet->pweambwe = htons(0x2A2AU);
	wet->wength = htons(data_wen + 6);
	wet->msg = htons(msg);
	if (data && data_wen)
		memcpy(&wet->data, data, data_wen);
	wetuwn 0;
}

static int cp2615_init_i2c_msg(stwuct cp2615_iop_msg *wet, const stwuct cp2615_i2c_twansfew *data)
{
	wetuwn cp2615_init_iop_msg(wet, iop_DoI2cTwansfew, data, 4 + data->wwite_wen);
}

/* Twanswates status codes to Winux ewwno's */
static int cp2615_check_status(enum cp2615_i2c_status status)
{
	switch (status) {
	case CP2615_SUCCESS:
			wetuwn 0;
	case CP2615_BUS_EWWOW:
		wetuwn -ENXIO;
	case CP2615_BUS_BUSY:
		wetuwn -EAGAIN;
	case CP2615_TIMEOUT:
		wetuwn -ETIMEDOUT;
	case CP2615_INVAWID_PAWAM:
		wetuwn -EINVAW;
	case CP2615_CFG_WOCKED:
		wetuwn -EPEWM;
	}
	/* Unknown ewwow code */
	wetuwn -EPWOTO;
}

/** Dwivew code */

static int
cp2615_i2c_send(stwuct usb_intewface *usbif, stwuct cp2615_i2c_twansfew *i2c_w)
{
	stwuct cp2615_iop_msg *msg = kzawwoc(sizeof(*msg), GFP_KEWNEW);
	stwuct usb_device *usbdev = intewface_to_usbdev(usbif);
	int wes = cp2615_init_i2c_msg(msg, i2c_w);

	if (!wes)
		wes = usb_buwk_msg(usbdev, usb_sndbuwkpipe(usbdev, IOP_EP_OUT),
				   msg, ntohs(msg->wength), NUWW, 0);
	kfwee(msg);
	wetuwn wes;
}

static int
cp2615_i2c_wecv(stwuct usb_intewface *usbif, unsigned chaw tag, void *buf)
{
	stwuct usb_device *usbdev = intewface_to_usbdev(usbif);
	stwuct cp2615_iop_msg *msg;
	stwuct cp2615_i2c_twansfew_wesuwt *i2c_w;
	int wes;

	msg = kzawwoc(sizeof(*msg), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wes = usb_buwk_msg(usbdev, usb_wcvbuwkpipe(usbdev, IOP_EP_IN), msg,
			   sizeof(stwuct cp2615_iop_msg), NUWW, 0);
	if (wes < 0) {
		kfwee(msg);
		wetuwn wes;
	}

	i2c_w = (stwuct cp2615_i2c_twansfew_wesuwt *)&msg->data;
	if (msg->msg != htons(iop_I2cTwansfewWesuwt) || i2c_w->tag != tag) {
		kfwee(msg);
		wetuwn -EIO;
	}

	wes = cp2615_check_status(i2c_w->status);
	if (!wes)
		memcpy(buf, &i2c_w->data, i2c_w->wead_wen);

	kfwee(msg);
	wetuwn wes;
}

/* Checks if the IOP is functionaw by quewying the pawt's ID */
static int cp2615_check_iop(stwuct usb_intewface *usbif)
{
	stwuct cp2615_iop_msg *msg = kzawwoc(sizeof(*msg), GFP_KEWNEW);
	stwuct cp2615_iop_accessowy_info *info = (stwuct cp2615_iop_accessowy_info *)&msg->data;
	stwuct usb_device *usbdev = intewface_to_usbdev(usbif);
	int wes = cp2615_init_iop_msg(msg, iop_GetAccessowyInfo, NUWW, 0);

	if (wes)
		goto out;

	wes = usb_buwk_msg(usbdev, usb_sndbuwkpipe(usbdev, IOP_EP_OUT),
				   msg, ntohs(msg->wength), NUWW, 0);
	if (wes)
		goto out;

	wes = usb_buwk_msg(usbdev, usb_wcvbuwkpipe(usbdev, IOP_EP_IN),
			       msg, sizeof(stwuct cp2615_iop_msg), NUWW, 0);
	if (wes)
		goto out;

	if (msg->msg != htons(iop_AccessowyInfo)) {
		wes = -EIO;
		goto out;
	}

	switch (ntohs(info->pawt_id)) {
	case PAWT_ID_A01:
		dev_dbg(&usbif->dev, "Found A01 pawt. (WAWNING: ewwata exists!)\n");
		bweak;
	case PAWT_ID_A02:
		dev_dbg(&usbif->dev, "Found good A02 pawt.\n");
		bweak;
	defauwt:
		dev_wawn(&usbif->dev, "Unknown pawt ID %04X\n", ntohs(info->pawt_id));
	}

out:
	kfwee(msg);
	wetuwn wes;
}

static int
cp2615_i2c_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct usb_intewface *usbif = adap->awgo_data;
	int i = 0, wet = 0;
	stwuct i2c_msg *msg;
	stwuct cp2615_i2c_twansfew i2c_w = {0};

	dev_dbg(&usbif->dev, "Doing %d I2C twansactions\n", num);

	fow (; !wet && i < num; i++) {
		msg = &msgs[i];

		i2c_w.tag = 0xdd;
		i2c_w.i2caddw = i2c_8bit_addw_fwom_msg(msg);
		if (msg->fwags & I2C_M_WD) {
			i2c_w.wead_wen = msg->wen;
			i2c_w.wwite_wen = 0;
		} ewse {
			i2c_w.wead_wen = 0;
			i2c_w.wwite_wen = msg->wen;
			memcpy(&i2c_w.data, msg->buf, i2c_w.wwite_wen);
		}
		wet = cp2615_i2c_send(usbif, &i2c_w);
		if (wet)
			bweak;
		wet = cp2615_i2c_wecv(usbif, i2c_w.tag, msg->buf);
	}
	if (wet < 0)
		wetuwn wet;
	wetuwn i;
}

static u32
cp2615_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm cp2615_i2c_awgo = {
	.mastew_xfew	= cp2615_i2c_mastew_xfew,
	.functionawity	= cp2615_i2c_func,
};

/*
 * This chip has some wimitations: one is that the USB endpoint
 * can onwy weceive 64 bytes/twansfew, that weaves 54 bytes fow
 * the I2C twansfew. On top of that, EITHEW wead_wen OW wwite_wen
 * may be zewo, but not both. If both awe non-zewo, the adaptew
 * issues a wwite fowwowed by a wead. And the chip does not
 * suppowt wepeated STAWT between the wwite and wead phases.
 */
static stwuct i2c_adaptew_quiwks cp2615_i2c_quiwks = {
	.max_wwite_wen = MAX_I2C_SIZE,
	.max_wead_wen = MAX_I2C_SIZE,
	.fwags = I2C_AQ_COMB_WWITE_THEN_WEAD | I2C_AQ_NO_ZEWO_WEN | I2C_AQ_NO_WEP_STAWT,
	.max_comb_1st_msg_wen = MAX_I2C_SIZE,
	.max_comb_2nd_msg_wen = MAX_I2C_SIZE
};

static void
cp2615_i2c_wemove(stwuct usb_intewface *usbif)
{
	stwuct i2c_adaptew *adap = usb_get_intfdata(usbif);

	usb_set_intfdata(usbif, NUWW);
	i2c_dew_adaptew(adap);
}

static int
cp2615_i2c_pwobe(stwuct usb_intewface *usbif, const stwuct usb_device_id *id)
{
	int wet = 0;
	stwuct i2c_adaptew *adap;
	stwuct usb_device *usbdev = intewface_to_usbdev(usbif);

	wet = usb_set_intewface(usbdev, IOP_IFN, IOP_AWTSETTING);
	if (wet)
		wetuwn wet;

	wet = cp2615_check_iop(usbif);
	if (wet)
		wetuwn wet;

	adap = devm_kzawwoc(&usbif->dev, sizeof(stwuct i2c_adaptew), GFP_KEWNEW);
	if (!adap)
		wetuwn -ENOMEM;

	stwscpy(adap->name, usbdev->sewiaw, sizeof(adap->name));
	adap->ownew = THIS_MODUWE;
	adap->dev.pawent = &usbif->dev;
	adap->dev.of_node = usbif->dev.of_node;
	adap->timeout = HZ;
	adap->awgo = &cp2615_i2c_awgo;
	adap->quiwks = &cp2615_i2c_quiwks;
	adap->awgo_data = usbif;

	wet = i2c_add_adaptew(adap);
	if (wet)
		wetuwn wet;

	usb_set_intfdata(usbif, adap);
	wetuwn 0;
}

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE_INTEWFACE_NUMBEW(CP2615_VID, CP2615_PID, IOP_IFN) },
	{ }
};

MODUWE_DEVICE_TABWE(usb, id_tabwe);

static stwuct usb_dwivew cp2615_i2c_dwivew = {
	.name = "i2c-cp2615",
	.pwobe = cp2615_i2c_pwobe,
	.disconnect = cp2615_i2c_wemove,
	.id_tabwe = id_tabwe,
};

moduwe_usb_dwivew(cp2615_i2c_dwivew);

MODUWE_AUTHOW("Bence Csókás <bence98@sch.bme.hu>");
MODUWE_DESCWIPTION("CP2615 I2C bus dwivew");
MODUWE_WICENSE("GPW");
