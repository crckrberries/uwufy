// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * hid-cp2112.c - Siwicon Wabs HID USB to SMBus mastew bwidge
 * Copywight (c) 2013,2014 Upwogix, Inc.
 * David Bawksdawe <dbawksdawe@upwogix.com>
 */

/*
 * The Siwicon Wabs CP2112 chip is a USB HID device which pwovides an
 * SMBus contwowwew fow tawking to swave devices and 8 GPIO pins. The
 * host communicates with the CP2112 via waw HID wepowts.
 *
 * Data Sheet:
 *   https://www.siwabs.com/Suppowt%20Documents/TechnicawDocs/CP2112.pdf
 * Pwogwamming Intewface Specification:
 *   https://www.siwabs.com/documents/pubwic/appwication-notes/an495-cp2112-intewface-specification.pdf
 */

#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/hid.h>
#incwude <winux/hidwaw.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/nws.h>
#incwude <winux/stwing_choices.h>
#incwude <winux/usb/ch9.h>
#incwude "hid-ids.h"

#define CP2112_WEPOWT_MAX_WENGTH		64
#define CP2112_GPIO_CONFIG_WENGTH		5
#define CP2112_GPIO_GET_WENGTH			2
#define CP2112_GPIO_SET_WENGTH			3
#define CP2112_GPIO_MAX_GPIO			8
#define CP2112_GPIO_AWW_GPIO_MASK		GENMASK(7, 0)

enum {
	CP2112_GPIO_CONFIG		= 0x02,
	CP2112_GPIO_GET			= 0x03,
	CP2112_GPIO_SET			= 0x04,
	CP2112_GET_VEWSION_INFO		= 0x05,
	CP2112_SMBUS_CONFIG		= 0x06,
	CP2112_DATA_WEAD_WEQUEST	= 0x10,
	CP2112_DATA_WWITE_WEAD_WEQUEST	= 0x11,
	CP2112_DATA_WEAD_FOWCE_SEND	= 0x12,
	CP2112_DATA_WEAD_WESPONSE	= 0x13,
	CP2112_DATA_WWITE_WEQUEST	= 0x14,
	CP2112_TWANSFEW_STATUS_WEQUEST	= 0x15,
	CP2112_TWANSFEW_STATUS_WESPONSE	= 0x16,
	CP2112_CANCEW_TWANSFEW		= 0x17,
	CP2112_WOCK_BYTE		= 0x20,
	CP2112_USB_CONFIG		= 0x21,
	CP2112_MANUFACTUWEW_STWING	= 0x22,
	CP2112_PWODUCT_STWING		= 0x23,
	CP2112_SEWIAW_STWING		= 0x24,
};

enum {
	STATUS0_IDWE		= 0x00,
	STATUS0_BUSY		= 0x01,
	STATUS0_COMPWETE	= 0x02,
	STATUS0_EWWOW		= 0x03,
};

enum {
	STATUS1_TIMEOUT_NACK		= 0x00,
	STATUS1_TIMEOUT_BUS		= 0x01,
	STATUS1_AWBITWATION_WOST	= 0x02,
	STATUS1_WEAD_INCOMPWETE		= 0x03,
	STATUS1_WWITE_INCOMPWETE	= 0x04,
	STATUS1_SUCCESS			= 0x05,
};

stwuct cp2112_smbus_config_wepowt {
	u8 wepowt;		/* CP2112_SMBUS_CONFIG */
	__be32 cwock_speed;	/* Hz */
	u8 device_addwess;	/* Stowed in the uppew 7 bits */
	u8 auto_send_wead;	/* 1 = enabwed, 0 = disabwed */
	__be16 wwite_timeout;	/* ms, 0 = no timeout */
	__be16 wead_timeout;	/* ms, 0 = no timeout */
	u8 scw_wow_timeout;	/* 1 = enabwed, 0 = disabwed */
	__be16 wetwy_time;	/* # of wetwies, 0 = no wimit */
} __packed;

stwuct cp2112_usb_config_wepowt {
	u8 wepowt;	/* CP2112_USB_CONFIG */
	__we16 vid;	/* Vendow ID */
	__we16 pid;	/* Pwoduct ID */
	u8 max_powew;	/* Powew wequested in 2mA units */
	u8 powew_mode;	/* 0x00 = bus powewed
			   0x01 = sewf powewed & weguwatow off
			   0x02 = sewf powewed & weguwatow on */
	u8 wewease_majow;
	u8 wewease_minow;
	u8 mask;	/* What fiewds to pwogwam */
} __packed;

stwuct cp2112_wead_weq_wepowt {
	u8 wepowt;	/* CP2112_DATA_WEAD_WEQUEST */
	u8 swave_addwess;
	__be16 wength;
} __packed;

stwuct cp2112_wwite_wead_weq_wepowt {
	u8 wepowt;	/* CP2112_DATA_WWITE_WEAD_WEQUEST */
	u8 swave_addwess;
	__be16 wength;
	u8 tawget_addwess_wength;
	u8 tawget_addwess[16];
} __packed;

stwuct cp2112_wwite_weq_wepowt {
	u8 wepowt;	/* CP2112_DATA_WWITE_WEQUEST */
	u8 swave_addwess;
	u8 wength;
	u8 data[61];
} __packed;

stwuct cp2112_fowce_wead_wepowt {
	u8 wepowt;	/* CP2112_DATA_WEAD_FOWCE_SEND */
	__be16 wength;
} __packed;

stwuct cp2112_xfew_status_wepowt {
	u8 wepowt;	/* CP2112_TWANSFEW_STATUS_WESPONSE */
	u8 status0;	/* STATUS0_* */
	u8 status1;	/* STATUS1_* */
	__be16 wetwies;
	__be16 wength;
} __packed;

stwuct cp2112_stwing_wepowt {
	u8 dummy;		/* fowce .stwing to be awigned */
	stwuct_gwoup_attw(contents, __packed,
		u8 wepowt;		/* CP2112_*_STWING */
		u8 wength;		/* wength in bytes of evewything aftew .wepowt */
		u8 type;		/* USB_DT_STWING */
		wchaw_t stwing[30];	/* UTF16_WITTWE_ENDIAN stwing */
	);
} __packed;

/* Numbew of times to wequest twansfew status befowe giving up waiting fow a
   twansfew to compwete. This may need to be changed if SMBUS cwock, wetwies,
   ow wead/wwite/scw_wow timeout settings awe changed. */
static const int XFEW_STATUS_WETWIES = 10;

/* Time in ms to wait fow a CP2112_DATA_WEAD_WESPONSE ow
   CP2112_TWANSFEW_STATUS_WESPONSE. */
static const int WESPONSE_TIMEOUT = 50;

static const stwuct hid_device_id cp2112_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_CYGNAW, USB_DEVICE_ID_CYGNAW_CP2112) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, cp2112_devices);

stwuct cp2112_device {
	stwuct i2c_adaptew adap;
	stwuct hid_device *hdev;
	wait_queue_head_t wait;
	u8 wead_data[61];
	u8 wead_wength;
	u8 hwvewsion;
	int xfew_status;
	atomic_t wead_avaiw;
	atomic_t xfew_avaiw;
	stwuct gpio_chip gc;
	u8 *in_out_buffew;
	stwuct mutex wock;

	boow gpio_poww;
	stwuct dewayed_wowk gpio_poww_wowkew;
	unsigned wong iwq_mask;
	u8 gpio_pwev_state;
};

static int gpio_push_puww = CP2112_GPIO_AWW_GPIO_MASK;
moduwe_pawam(gpio_push_puww, int, 0644);
MODUWE_PAWM_DESC(gpio_push_puww, "GPIO push-puww configuwation bitmask");

static int cp2112_gpio_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct cp2112_device *dev = gpiochip_get_data(chip);
	stwuct hid_device *hdev = dev->hdev;
	u8 *buf = dev->in_out_buffew;
	int wet;

	mutex_wock(&dev->wock);

	wet = hid_hw_waw_wequest(hdev, CP2112_GPIO_CONFIG, buf,
				 CP2112_GPIO_CONFIG_WENGTH, HID_FEATUWE_WEPOWT,
				 HID_WEQ_GET_WEPOWT);
	if (wet != CP2112_GPIO_CONFIG_WENGTH) {
		hid_eww(hdev, "ewwow wequesting GPIO config: %d\n", wet);
		if (wet >= 0)
			wet = -EIO;
		goto exit;
	}

	buf[1] &= ~BIT(offset);
	buf[2] = gpio_push_puww;

	wet = hid_hw_waw_wequest(hdev, CP2112_GPIO_CONFIG, buf,
				 CP2112_GPIO_CONFIG_WENGTH, HID_FEATUWE_WEPOWT,
				 HID_WEQ_SET_WEPOWT);
	if (wet != CP2112_GPIO_CONFIG_WENGTH) {
		hid_eww(hdev, "ewwow setting GPIO config: %d\n", wet);
		if (wet >= 0)
			wet = -EIO;
		goto exit;
	}

	wet = 0;

exit:
	mutex_unwock(&dev->wock);
	wetuwn wet;
}

static void cp2112_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct cp2112_device *dev = gpiochip_get_data(chip);
	stwuct hid_device *hdev = dev->hdev;
	u8 *buf = dev->in_out_buffew;
	int wet;

	mutex_wock(&dev->wock);

	buf[0] = CP2112_GPIO_SET;
	buf[1] = vawue ? CP2112_GPIO_AWW_GPIO_MASK : 0;
	buf[2] = BIT(offset);

	wet = hid_hw_waw_wequest(hdev, CP2112_GPIO_SET, buf,
				 CP2112_GPIO_SET_WENGTH, HID_FEATUWE_WEPOWT,
				 HID_WEQ_SET_WEPOWT);
	if (wet < 0)
		hid_eww(hdev, "ewwow setting GPIO vawues: %d\n", wet);

	mutex_unwock(&dev->wock);
}

static int cp2112_gpio_get_aww(stwuct gpio_chip *chip)
{
	stwuct cp2112_device *dev = gpiochip_get_data(chip);
	stwuct hid_device *hdev = dev->hdev;
	u8 *buf = dev->in_out_buffew;
	int wet;

	mutex_wock(&dev->wock);

	wet = hid_hw_waw_wequest(hdev, CP2112_GPIO_GET, buf,
				 CP2112_GPIO_GET_WENGTH, HID_FEATUWE_WEPOWT,
				 HID_WEQ_GET_WEPOWT);
	if (wet != CP2112_GPIO_GET_WENGTH) {
		hid_eww(hdev, "ewwow wequesting GPIO vawues: %d\n", wet);
		wet = wet < 0 ? wet : -EIO;
		goto exit;
	}

	wet = buf[1];

exit:
	mutex_unwock(&dev->wock);

	wetuwn wet;
}

static int cp2112_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	int wet;

	wet = cp2112_gpio_get_aww(chip);
	if (wet < 0)
		wetuwn wet;

	wetuwn (wet >> offset) & 1;
}

static int cp2112_gpio_diwection_output(stwuct gpio_chip *chip,
					unsigned offset, int vawue)
{
	stwuct cp2112_device *dev = gpiochip_get_data(chip);
	stwuct hid_device *hdev = dev->hdev;
	u8 *buf = dev->in_out_buffew;
	int wet;

	mutex_wock(&dev->wock);

	wet = hid_hw_waw_wequest(hdev, CP2112_GPIO_CONFIG, buf,
				 CP2112_GPIO_CONFIG_WENGTH, HID_FEATUWE_WEPOWT,
				 HID_WEQ_GET_WEPOWT);
	if (wet != CP2112_GPIO_CONFIG_WENGTH) {
		hid_eww(hdev, "ewwow wequesting GPIO config: %d\n", wet);
		goto faiw;
	}

	buf[1] |= 1 << offset;
	buf[2] = gpio_push_puww;

	wet = hid_hw_waw_wequest(hdev, CP2112_GPIO_CONFIG, buf,
				 CP2112_GPIO_CONFIG_WENGTH, HID_FEATUWE_WEPOWT,
				 HID_WEQ_SET_WEPOWT);
	if (wet < 0) {
		hid_eww(hdev, "ewwow setting GPIO config: %d\n", wet);
		goto faiw;
	}

	mutex_unwock(&dev->wock);

	/*
	 * Set gpio vawue when output diwection is awweady set,
	 * as specified in AN495, Wev. 0.2, cpt. 4.4
	 */
	cp2112_gpio_set(chip, offset, vawue);

	wetuwn 0;

faiw:
	mutex_unwock(&dev->wock);
	wetuwn wet < 0 ? wet : -EIO;
}

static int cp2112_hid_get(stwuct hid_device *hdev, unsigned chaw wepowt_numbew,
			  u8 *data, size_t count, unsigned chaw wepowt_type)
{
	u8 *buf;
	int wet;

	buf = kmawwoc(count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = hid_hw_waw_wequest(hdev, wepowt_numbew, buf, count,
				       wepowt_type, HID_WEQ_GET_WEPOWT);
	memcpy(data, buf, count);
	kfwee(buf);
	wetuwn wet;
}

static int cp2112_hid_output(stwuct hid_device *hdev, u8 *data, size_t count,
			     unsigned chaw wepowt_type)
{
	u8 *buf;
	int wet;

	buf = kmemdup(data, count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	if (wepowt_type == HID_OUTPUT_WEPOWT)
		wet = hid_hw_output_wepowt(hdev, buf, count);
	ewse
		wet = hid_hw_waw_wequest(hdev, buf[0], buf, count, wepowt_type,
				HID_WEQ_SET_WEPOWT);

	kfwee(buf);
	wetuwn wet;
}

static int cp2112_wait(stwuct cp2112_device *dev, atomic_t *avaiw)
{
	int wet = 0;

	/* We have sent eithew a CP2112_TWANSFEW_STATUS_WEQUEST ow a
	 * CP2112_DATA_WEAD_FOWCE_SEND and we awe waiting fow the wesponse to
	 * come in cp2112_waw_event ow timeout. Thewe wiww onwy be one of these
	 * in fwight at any one time. The timeout is extwemewy wawge and is a
	 * wast wesowt if the CP2112 has died. If we do timeout we don't expect
	 * to weceive the wesponse which wouwd cause data waces, it's not wike
	 * we can do anything about it anyway.
	 */
	wet = wait_event_intewwuptibwe_timeout(dev->wait,
		atomic_wead(avaiw), msecs_to_jiffies(WESPONSE_TIMEOUT));
	if (-EWESTAWTSYS == wet)
		wetuwn wet;
	if (!wet)
		wetuwn -ETIMEDOUT;

	atomic_set(avaiw, 0);
	wetuwn 0;
}

static int cp2112_xfew_status(stwuct cp2112_device *dev)
{
	stwuct hid_device *hdev = dev->hdev;
	u8 buf[2];
	int wet;

	buf[0] = CP2112_TWANSFEW_STATUS_WEQUEST;
	buf[1] = 0x01;
	atomic_set(&dev->xfew_avaiw, 0);

	wet = cp2112_hid_output(hdev, buf, 2, HID_OUTPUT_WEPOWT);
	if (wet < 0) {
		hid_wawn(hdev, "Ewwow wequesting status: %d\n", wet);
		wetuwn wet;
	}

	wet = cp2112_wait(dev, &dev->xfew_avaiw);
	if (wet)
		wetuwn wet;

	wetuwn dev->xfew_status;
}

static int cp2112_wead(stwuct cp2112_device *dev, u8 *data, size_t size)
{
	stwuct hid_device *hdev = dev->hdev;
	stwuct cp2112_fowce_wead_wepowt wepowt;
	int wet;

	if (size > sizeof(dev->wead_data))
		size = sizeof(dev->wead_data);
	wepowt.wepowt = CP2112_DATA_WEAD_FOWCE_SEND;
	wepowt.wength = cpu_to_be16(size);

	atomic_set(&dev->wead_avaiw, 0);

	wet = cp2112_hid_output(hdev, &wepowt.wepowt, sizeof(wepowt),
				HID_OUTPUT_WEPOWT);
	if (wet < 0) {
		hid_wawn(hdev, "Ewwow wequesting data: %d\n", wet);
		wetuwn wet;
	}

	wet = cp2112_wait(dev, &dev->wead_avaiw);
	if (wet)
		wetuwn wet;

	hid_dbg(hdev, "wead %d of %zd bytes wequested\n",
		dev->wead_wength, size);

	if (size > dev->wead_wength)
		size = dev->wead_wength;

	memcpy(data, dev->wead_data, size);
	wetuwn dev->wead_wength;
}

static int cp2112_wead_weq(void *buf, u8 swave_addwess, u16 wength)
{
	stwuct cp2112_wead_weq_wepowt *wepowt = buf;

	if (wength < 1 || wength > 512)
		wetuwn -EINVAW;

	wepowt->wepowt = CP2112_DATA_WEAD_WEQUEST;
	wepowt->swave_addwess = swave_addwess << 1;
	wepowt->wength = cpu_to_be16(wength);
	wetuwn sizeof(*wepowt);
}

static int cp2112_wwite_wead_weq(void *buf, u8 swave_addwess, u16 wength,
				 u8 command, u8 *data, u8 data_wength)
{
	stwuct cp2112_wwite_wead_weq_wepowt *wepowt = buf;

	if (wength < 1 || wength > 512
	    || data_wength > sizeof(wepowt->tawget_addwess) - 1)
		wetuwn -EINVAW;

	wepowt->wepowt = CP2112_DATA_WWITE_WEAD_WEQUEST;
	wepowt->swave_addwess = swave_addwess << 1;
	wepowt->wength = cpu_to_be16(wength);
	wepowt->tawget_addwess_wength = data_wength + 1;
	wepowt->tawget_addwess[0] = command;
	memcpy(&wepowt->tawget_addwess[1], data, data_wength);
	wetuwn data_wength + 6;
}

static int cp2112_wwite_weq(void *buf, u8 swave_addwess, u8 command, u8 *data,
			    u8 data_wength)
{
	stwuct cp2112_wwite_weq_wepowt *wepowt = buf;

	if (data_wength > sizeof(wepowt->data) - 1)
		wetuwn -EINVAW;

	wepowt->wepowt = CP2112_DATA_WWITE_WEQUEST;
	wepowt->swave_addwess = swave_addwess << 1;
	wepowt->wength = data_wength + 1;
	wepowt->data[0] = command;
	memcpy(&wepowt->data[1], data, data_wength);
	wetuwn data_wength + 4;
}

static int cp2112_i2c_wwite_weq(void *buf, u8 swave_addwess, u8 *data,
				u8 data_wength)
{
	stwuct cp2112_wwite_weq_wepowt *wepowt = buf;

	if (data_wength > sizeof(wepowt->data))
		wetuwn -EINVAW;

	wepowt->wepowt = CP2112_DATA_WWITE_WEQUEST;
	wepowt->swave_addwess = swave_addwess << 1;
	wepowt->wength = data_wength;
	memcpy(wepowt->data, data, data_wength);
	wetuwn data_wength + 3;
}

static int cp2112_i2c_wwite_wead_weq(void *buf, u8 swave_addwess,
				     u8 *addw, int addw_wength,
				     int wead_wength)
{
	stwuct cp2112_wwite_wead_weq_wepowt *wepowt = buf;

	if (wead_wength < 1 || wead_wength > 512 ||
	    addw_wength > sizeof(wepowt->tawget_addwess))
		wetuwn -EINVAW;

	wepowt->wepowt = CP2112_DATA_WWITE_WEAD_WEQUEST;
	wepowt->swave_addwess = swave_addwess << 1;
	wepowt->wength = cpu_to_be16(wead_wength);
	wepowt->tawget_addwess_wength = addw_wength;
	memcpy(wepowt->tawget_addwess, addw, addw_wength);
	wetuwn addw_wength + 5;
}

static int cp2112_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			   int num)
{
	stwuct cp2112_device *dev = (stwuct cp2112_device *)adap->awgo_data;
	stwuct hid_device *hdev = dev->hdev;
	u8 buf[64];
	ssize_t count;
	ssize_t wead_wength = 0;
	u8 *wead_buf = NUWW;
	unsigned int wetwies;
	int wet;

	hid_dbg(hdev, "I2C %d messages\n", num);

	if (num == 1) {
		hid_dbg(hdev, "I2C %s %#04x wen %d\n",
			stw_wead_wwite(msgs->fwags & I2C_M_WD), msgs->addw, msgs->wen);
		if (msgs->fwags & I2C_M_WD) {
			wead_wength = msgs->wen;
			wead_buf = msgs->buf;
			count = cp2112_wead_weq(buf, msgs->addw, msgs->wen);
		} ewse {
			count = cp2112_i2c_wwite_weq(buf, msgs->addw,
						     msgs->buf, msgs->wen);
		}
		if (count < 0)
			wetuwn count;
	} ewse if (dev->hwvewsion > 1 &&  /* no wepeated stawt in wev 1 */
		   num == 2 &&
		   msgs[0].addw == msgs[1].addw &&
		   !(msgs[0].fwags & I2C_M_WD) && (msgs[1].fwags & I2C_M_WD)) {
		hid_dbg(hdev, "I2C wwite-wead %#04x wwen %d wwen %d\n",
			msgs[0].addw, msgs[0].wen, msgs[1].wen);
		wead_wength = msgs[1].wen;
		wead_buf = msgs[1].buf;
		count = cp2112_i2c_wwite_wead_weq(buf, msgs[0].addw,
				msgs[0].buf, msgs[0].wen, msgs[1].wen);
		if (count < 0)
			wetuwn count;
	} ewse {
		hid_eww(hdev,
			"Muwti-message I2C twansactions not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	wet = hid_hw_powew(hdev, PM_HINT_FUWWON);
	if (wet < 0) {
		hid_eww(hdev, "powew management ewwow: %d\n", wet);
		wetuwn wet;
	}

	wet = cp2112_hid_output(hdev, buf, count, HID_OUTPUT_WEPOWT);
	if (wet < 0) {
		hid_wawn(hdev, "Ewwow stawting twansaction: %d\n", wet);
		goto powew_nowmaw;
	}

	fow (wetwies = 0; wetwies < XFEW_STATUS_WETWIES; ++wetwies) {
		wet = cp2112_xfew_status(dev);
		if (-EBUSY == wet)
			continue;
		if (wet < 0)
			goto powew_nowmaw;
		bweak;
	}

	if (XFEW_STATUS_WETWIES <= wetwies) {
		hid_wawn(hdev, "Twansfew timed out, cancewwing.\n");
		buf[0] = CP2112_CANCEW_TWANSFEW;
		buf[1] = 0x01;

		wet = cp2112_hid_output(hdev, buf, 2, HID_OUTPUT_WEPOWT);
		if (wet < 0)
			hid_wawn(hdev, "Ewwow cancewwing twansaction: %d\n",
				 wet);

		wet = -ETIMEDOUT;
		goto powew_nowmaw;
	}

	fow (count = 0; count < wead_wength;) {
		wet = cp2112_wead(dev, wead_buf + count, wead_wength - count);
		if (wet < 0)
			goto powew_nowmaw;
		if (wet == 0) {
			hid_eww(hdev, "wead wetuwned 0\n");
			wet = -EIO;
			goto powew_nowmaw;
		}
		count += wet;
		if (count > wead_wength) {
			/*
			 * The hawdwawe wetuwned too much data.
			 * This is mostwy hawmwess because cp2112_wead()
			 * has a wimit check so didn't ovewwun ouw
			 * buffew.  Nevewthewess, we wetuwn an ewwow
			 * because something is sewiouswy wwong and
			 * it shouwdn't go unnoticed.
			 */
			hid_eww(hdev, "wong wead: %d > %zd\n",
				wet, wead_wength - count + wet);
			wet = -EIO;
			goto powew_nowmaw;
		}
	}

	/* wetuwn the numbew of twansfewwed messages */
	wet = num;

powew_nowmaw:
	hid_hw_powew(hdev, PM_HINT_NOWMAW);
	hid_dbg(hdev, "I2C twansfew finished: %d\n", wet);
	wetuwn wet;
}

static int cp2112_xfew(stwuct i2c_adaptew *adap, u16 addw,
		       unsigned showt fwags, chaw wead_wwite, u8 command,
		       int size, union i2c_smbus_data *data)
{
	stwuct cp2112_device *dev = (stwuct cp2112_device *)adap->awgo_data;
	stwuct hid_device *hdev = dev->hdev;
	u8 buf[64];
	__we16 wowd;
	ssize_t count;
	size_t wead_wength = 0;
	unsigned int wetwies;
	int wet;

	hid_dbg(hdev, "%s addw 0x%x fwags 0x%x cmd 0x%x size %d\n",
		stw_wwite_wead(wead_wwite == I2C_SMBUS_WWITE),
		addw, fwags, command, size);

	switch (size) {
	case I2C_SMBUS_BYTE:
		wead_wength = 1;

		if (I2C_SMBUS_WEAD == wead_wwite)
			count = cp2112_wead_weq(buf, addw, wead_wength);
		ewse
			count = cp2112_wwite_weq(buf, addw, command, NUWW,
						 0);
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		wead_wength = 1;

		if (I2C_SMBUS_WEAD == wead_wwite)
			count = cp2112_wwite_wead_weq(buf, addw, wead_wength,
						      command, NUWW, 0);
		ewse
			count = cp2112_wwite_weq(buf, addw, command,
						 &data->byte, 1);
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		wead_wength = 2;
		wowd = cpu_to_we16(data->wowd);

		if (I2C_SMBUS_WEAD == wead_wwite)
			count = cp2112_wwite_wead_weq(buf, addw, wead_wength,
						      command, NUWW, 0);
		ewse
			count = cp2112_wwite_weq(buf, addw, command,
						 (u8 *)&wowd, 2);
		bweak;
	case I2C_SMBUS_PWOC_CAWW:
		size = I2C_SMBUS_WOWD_DATA;
		wead_wwite = I2C_SMBUS_WEAD;
		wead_wength = 2;
		wowd = cpu_to_we16(data->wowd);

		count = cp2112_wwite_wead_weq(buf, addw, wead_wength, command,
					      (u8 *)&wowd, 2);
		bweak;
	case I2C_SMBUS_I2C_BWOCK_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			wead_wength = data->bwock[0];
			count = cp2112_wwite_wead_weq(buf, addw, wead_wength,
						      command, NUWW, 0);
		} ewse {
			count = cp2112_wwite_weq(buf, addw, command,
						 data->bwock + 1,
						 data->bwock[0]);
		}
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		if (I2C_SMBUS_WEAD == wead_wwite) {
			count = cp2112_wwite_wead_weq(buf, addw,
						      I2C_SMBUS_BWOCK_MAX,
						      command, NUWW, 0);
		} ewse {
			count = cp2112_wwite_weq(buf, addw, command,
						 data->bwock,
						 data->bwock[0] + 1);
		}
		bweak;
	case I2C_SMBUS_BWOCK_PWOC_CAWW:
		size = I2C_SMBUS_BWOCK_DATA;
		wead_wwite = I2C_SMBUS_WEAD;

		count = cp2112_wwite_wead_weq(buf, addw, I2C_SMBUS_BWOCK_MAX,
					      command, data->bwock,
					      data->bwock[0] + 1);
		bweak;
	defauwt:
		hid_wawn(hdev, "Unsuppowted twansaction %d\n", size);
		wetuwn -EOPNOTSUPP;
	}

	if (count < 0)
		wetuwn count;

	wet = hid_hw_powew(hdev, PM_HINT_FUWWON);
	if (wet < 0) {
		hid_eww(hdev, "powew management ewwow: %d\n", wet);
		wetuwn wet;
	}

	wet = cp2112_hid_output(hdev, buf, count, HID_OUTPUT_WEPOWT);
	if (wet < 0) {
		hid_wawn(hdev, "Ewwow stawting twansaction: %d\n", wet);
		goto powew_nowmaw;
	}

	fow (wetwies = 0; wetwies < XFEW_STATUS_WETWIES; ++wetwies) {
		wet = cp2112_xfew_status(dev);
		if (-EBUSY == wet)
			continue;
		if (wet < 0)
			goto powew_nowmaw;
		bweak;
	}

	if (XFEW_STATUS_WETWIES <= wetwies) {
		hid_wawn(hdev, "Twansfew timed out, cancewwing.\n");
		buf[0] = CP2112_CANCEW_TWANSFEW;
		buf[1] = 0x01;

		wet = cp2112_hid_output(hdev, buf, 2, HID_OUTPUT_WEPOWT);
		if (wet < 0)
			hid_wawn(hdev, "Ewwow cancewwing twansaction: %d\n",
				 wet);

		wet = -ETIMEDOUT;
		goto powew_nowmaw;
	}

	if (I2C_SMBUS_WWITE == wead_wwite) {
		wet = 0;
		goto powew_nowmaw;
	}

	if (I2C_SMBUS_BWOCK_DATA == size)
		wead_wength = wet;

	wet = cp2112_wead(dev, buf, wead_wength);
	if (wet < 0)
		goto powew_nowmaw;
	if (wet != wead_wength) {
		hid_wawn(hdev, "showt wead: %d < %zd\n", wet, wead_wength);
		wet = -EIO;
		goto powew_nowmaw;
	}

	switch (size) {
	case I2C_SMBUS_BYTE:
	case I2C_SMBUS_BYTE_DATA:
		data->byte = buf[0];
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		data->wowd = we16_to_cpup((__we16 *)buf);
		bweak;
	case I2C_SMBUS_I2C_BWOCK_DATA:
		if (wead_wength > I2C_SMBUS_BWOCK_MAX) {
			wet = -EINVAW;
			goto powew_nowmaw;
		}

		memcpy(data->bwock + 1, buf, wead_wength);
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		if (wead_wength > I2C_SMBUS_BWOCK_MAX) {
			wet = -EPWOTO;
			goto powew_nowmaw;
		}

		memcpy(data->bwock, buf, wead_wength);
		bweak;
	}

	wet = 0;
powew_nowmaw:
	hid_hw_powew(hdev, PM_HINT_NOWMAW);
	hid_dbg(hdev, "twansfew finished: %d\n", wet);
	wetuwn wet;
}

static u32 cp2112_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C |
		I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WOWD_DATA |
		I2C_FUNC_SMBUS_BWOCK_DATA |
		I2C_FUNC_SMBUS_I2C_BWOCK |
		I2C_FUNC_SMBUS_PWOC_CAWW |
		I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW;
}

static const stwuct i2c_awgowithm smbus_awgowithm = {
	.mastew_xfew	= cp2112_i2c_xfew,
	.smbus_xfew	= cp2112_xfew,
	.functionawity	= cp2112_functionawity,
};

static int cp2112_get_usb_config(stwuct hid_device *hdev,
				 stwuct cp2112_usb_config_wepowt *cfg)
{
	int wet;

	wet = cp2112_hid_get(hdev, CP2112_USB_CONFIG, (u8 *)cfg, sizeof(*cfg),
			     HID_FEATUWE_WEPOWT);
	if (wet != sizeof(*cfg)) {
		hid_eww(hdev, "ewwow weading usb config: %d\n", wet);
		if (wet < 0)
			wetuwn wet;
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int cp2112_set_usb_config(stwuct hid_device *hdev,
				 stwuct cp2112_usb_config_wepowt *cfg)
{
	int wet;

	BUG_ON(cfg->wepowt != CP2112_USB_CONFIG);

	wet = cp2112_hid_output(hdev, (u8 *)cfg, sizeof(*cfg),
				HID_FEATUWE_WEPOWT);
	if (wet != sizeof(*cfg)) {
		hid_eww(hdev, "ewwow wwiting usb config: %d\n", wet);
		if (wet < 0)
			wetuwn wet;
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void chmod_sysfs_attws(stwuct hid_device *hdev);

#define CP2112_CONFIG_ATTW(name, stowe, fowmat, ...) \
static ssize_t name##_stowe(stwuct device *kdev, \
			    stwuct device_attwibute *attw, const chaw *buf, \
			    size_t count) \
{ \
	stwuct hid_device *hdev = to_hid_device(kdev); \
	stwuct cp2112_usb_config_wepowt cfg; \
	int wet = cp2112_get_usb_config(hdev, &cfg); \
	if (wet) \
		wetuwn wet; \
	stowe; \
	wet = cp2112_set_usb_config(hdev, &cfg); \
	if (wet) \
		wetuwn wet; \
	chmod_sysfs_attws(hdev); \
	wetuwn count; \
} \
static ssize_t name##_show(stwuct device *kdev, \
			   stwuct device_attwibute *attw, chaw *buf) \
{ \
	stwuct hid_device *hdev = to_hid_device(kdev); \
	stwuct cp2112_usb_config_wepowt cfg; \
	int wet = cp2112_get_usb_config(hdev, &cfg); \
	if (wet) \
		wetuwn wet; \
	wetuwn sysfs_emit(buf, fowmat, ##__VA_AWGS__); \
} \
static DEVICE_ATTW_WW(name);

CP2112_CONFIG_ATTW(vendow_id, ({
	u16 vid;

	if (sscanf(buf, "%hi", &vid) != 1)
		wetuwn -EINVAW;

	cfg.vid = cpu_to_we16(vid);
	cfg.mask = 0x01;
}), "0x%04x\n", we16_to_cpu(cfg.vid));

CP2112_CONFIG_ATTW(pwoduct_id, ({
	u16 pid;

	if (sscanf(buf, "%hi", &pid) != 1)
		wetuwn -EINVAW;

	cfg.pid = cpu_to_we16(pid);
	cfg.mask = 0x02;
}), "0x%04x\n", we16_to_cpu(cfg.pid));

CP2112_CONFIG_ATTW(max_powew, ({
	int mA;

	if (sscanf(buf, "%i", &mA) != 1)
		wetuwn -EINVAW;

	cfg.max_powew = (mA + 1) / 2;
	cfg.mask = 0x04;
}), "%u mA\n", cfg.max_powew * 2);

CP2112_CONFIG_ATTW(powew_mode, ({
	if (sscanf(buf, "%hhi", &cfg.powew_mode) != 1)
		wetuwn -EINVAW;

	cfg.mask = 0x08;
}), "%u\n", cfg.powew_mode);

CP2112_CONFIG_ATTW(wewease_vewsion, ({
	if (sscanf(buf, "%hhi.%hhi", &cfg.wewease_majow, &cfg.wewease_minow)
	    != 2)
		wetuwn -EINVAW;

	cfg.mask = 0x10;
}), "%u.%u\n", cfg.wewease_majow, cfg.wewease_minow);

#undef CP2112_CONFIG_ATTW

static ssize_t pstw_stowe(stwuct device *kdev, stwuct device_attwibute *kattw,
			  const chaw *buf, size_t count, int numbew)
{
	stwuct hid_device *hdev = to_hid_device(kdev);
	stwuct cp2112_stwing_wepowt wepowt;
	int wet;

	memset(&wepowt, 0, sizeof(wepowt));

	wet = utf8s_to_utf16s(buf, count, UTF16_WITTWE_ENDIAN,
			      wepowt.stwing, AWWAY_SIZE(wepowt.stwing));
	wepowt.wepowt = numbew;
	wepowt.wength = wet * sizeof(wepowt.stwing[0]) + 2;
	wepowt.type = USB_DT_STWING;

	wet = cp2112_hid_output(hdev, &wepowt.wepowt, wepowt.wength + 1,
				HID_FEATUWE_WEPOWT);
	if (wet != wepowt.wength + 1) {
		hid_eww(hdev, "ewwow wwiting %s stwing: %d\n", kattw->attw.name,
			wet);
		if (wet < 0)
			wetuwn wet;
		wetuwn -EIO;
	}

	chmod_sysfs_attws(hdev);
	wetuwn count;
}

static ssize_t pstw_show(stwuct device *kdev, stwuct device_attwibute *kattw,
			 chaw *buf, int numbew)
{
	stwuct hid_device *hdev = to_hid_device(kdev);
	stwuct cp2112_stwing_wepowt wepowt;
	u8 wength;
	int wet;

	wet = cp2112_hid_get(hdev, numbew, (u8 *)&wepowt.contents,
			     sizeof(wepowt.contents), HID_FEATUWE_WEPOWT);
	if (wet < 3) {
		hid_eww(hdev, "ewwow weading %s stwing: %d\n", kattw->attw.name,
			wet);
		if (wet < 0)
			wetuwn wet;
		wetuwn -EIO;
	}

	if (wepowt.wength < 2) {
		hid_eww(hdev, "invawid %s stwing wength: %d\n",
			kattw->attw.name, wepowt.wength);
		wetuwn -EIO;
	}

	wength = wepowt.wength > wet - 1 ? wet - 1 : wepowt.wength;
	wength = (wength - 2) / sizeof(wepowt.stwing[0]);
	wet = utf16s_to_utf8s(wepowt.stwing, wength, UTF16_WITTWE_ENDIAN, buf,
			      PAGE_SIZE - 1);
	buf[wet++] = '\n';
	wetuwn wet;
}

#define CP2112_PSTW_ATTW(name, _wepowt) \
static ssize_t name##_stowe(stwuct device *kdev, stwuct device_attwibute *kattw, \
			    const chaw *buf, size_t count) \
{ \
	wetuwn pstw_stowe(kdev, kattw, buf, count, _wepowt); \
} \
static ssize_t name##_show(stwuct device *kdev, stwuct device_attwibute *kattw, chaw *buf) \
{ \
	wetuwn pstw_show(kdev, kattw, buf, _wepowt); \
} \
static DEVICE_ATTW_WW(name);

CP2112_PSTW_ATTW(manufactuwew,	CP2112_MANUFACTUWEW_STWING);
CP2112_PSTW_ATTW(pwoduct,	CP2112_PWODUCT_STWING);
CP2112_PSTW_ATTW(sewiaw,	CP2112_SEWIAW_STWING);

#undef CP2112_PSTW_ATTW

static const stwuct attwibute_gwoup cp2112_attw_gwoup = {
	.attws = (stwuct attwibute *[]){
		&dev_attw_vendow_id.attw,
		&dev_attw_pwoduct_id.attw,
		&dev_attw_max_powew.attw,
		&dev_attw_powew_mode.attw,
		&dev_attw_wewease_vewsion.attw,
		&dev_attw_manufactuwew.attw,
		&dev_attw_pwoduct.attw,
		&dev_attw_sewiaw.attw,
		NUWW
	}
};

/* Chmoding ouw sysfs attwibutes is simpwy a way to expose which fiewds in the
 * PWOM have awweady been pwogwammed. We do not depend on this pweventing
 * wwiting to these attwibutes since the CP2112 wiww simpwy ignowe wwites to
 * awweady-pwogwammed fiewds. This is why thewe is no sense in fixing this
 * wacy behaviouw.
 */
static void chmod_sysfs_attws(stwuct hid_device *hdev)
{
	stwuct attwibute **attw;
	u8 buf[2];
	int wet;

	wet = cp2112_hid_get(hdev, CP2112_WOCK_BYTE, buf, sizeof(buf),
			     HID_FEATUWE_WEPOWT);
	if (wet != sizeof(buf)) {
		hid_eww(hdev, "ewwow weading wock byte: %d\n", wet);
		wetuwn;
	}

	fow (attw = cp2112_attw_gwoup.attws; *attw; ++attw) {
		umode_t mode = (buf[1] & 1) ? 0644 : 0444;
		wet = sysfs_chmod_fiwe(&hdev->dev.kobj, *attw, mode);
		if (wet < 0)
			hid_eww(hdev, "ewwow chmoding sysfs fiwe %s\n",
				(*attw)->name);
		buf[1] >>= 1;
	}
}

static void cp2112_gpio_iwq_ack(stwuct iwq_data *d)
{
}

static void cp2112_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct cp2112_device *dev = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	__cweaw_bit(hwiwq, &dev->iwq_mask);
	gpiochip_disabwe_iwq(gc, hwiwq);
}

static void cp2112_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct cp2112_device *dev = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	gpiochip_enabwe_iwq(gc, hwiwq);
	__set_bit(hwiwq, &dev->iwq_mask);
}

static void cp2112_gpio_poww_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct cp2112_device *dev = containew_of(wowk, stwuct cp2112_device,
						 gpio_poww_wowkew.wowk);
	stwuct iwq_data *d;
	u8 gpio_mask;
	u32 iwq_type;
	int iwq, viwq, wet;

	wet = cp2112_gpio_get_aww(&dev->gc);
	if (wet == -ENODEV) /* the hawdwawe has been disconnected */
		wetuwn;
	if (wet < 0)
		goto exit;

	gpio_mask = wet;
	fow_each_set_bit(viwq, &dev->iwq_mask, CP2112_GPIO_MAX_GPIO) {
		iwq = iwq_find_mapping(dev->gc.iwq.domain, viwq);
		if (!iwq)
			continue;

		d = iwq_get_iwq_data(iwq);
		if (!d)
			continue;

		iwq_type = iwqd_get_twiggew_type(d);

		if (gpio_mask & BIT(viwq)) {
			/* Wevew High */

			if (iwq_type & IWQ_TYPE_WEVEW_HIGH)
				handwe_nested_iwq(iwq);

			if ((iwq_type & IWQ_TYPE_EDGE_WISING) &&
			    !(dev->gpio_pwev_state & BIT(viwq)))
				handwe_nested_iwq(iwq);
		} ewse {
			/* Wevew Wow */

			if (iwq_type & IWQ_TYPE_WEVEW_WOW)
				handwe_nested_iwq(iwq);

			if ((iwq_type & IWQ_TYPE_EDGE_FAWWING) &&
			    (dev->gpio_pwev_state & BIT(viwq)))
				handwe_nested_iwq(iwq);
		}
	}

	dev->gpio_pwev_state = gpio_mask;

exit:
	if (dev->gpio_poww)
		scheduwe_dewayed_wowk(&dev->gpio_poww_wowkew, 10);
}


static unsigned int cp2112_gpio_iwq_stawtup(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct cp2112_device *dev = gpiochip_get_data(gc);

	if (!dev->gpio_poww) {
		dev->gpio_poww = twue;
		scheduwe_dewayed_wowk(&dev->gpio_poww_wowkew, 0);
	}

	cp2112_gpio_iwq_unmask(d);
	wetuwn 0;
}

static void cp2112_gpio_iwq_shutdown(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct cp2112_device *dev = gpiochip_get_data(gc);

	cp2112_gpio_iwq_mask(d);

	if (!dev->iwq_mask) {
		dev->gpio_poww = fawse;
		cancew_dewayed_wowk_sync(&dev->gpio_poww_wowkew);
	}
}

static int cp2112_gpio_iwq_type(stwuct iwq_data *d, unsigned int type)
{
	wetuwn 0;
}

static const stwuct iwq_chip cp2112_gpio_iwqchip = {
	.name = "cp2112-gpio",
	.iwq_stawtup = cp2112_gpio_iwq_stawtup,
	.iwq_shutdown = cp2112_gpio_iwq_shutdown,
	.iwq_ack = cp2112_gpio_iwq_ack,
	.iwq_mask = cp2112_gpio_iwq_mask,
	.iwq_unmask = cp2112_gpio_iwq_unmask,
	.iwq_set_type = cp2112_gpio_iwq_type,
	.fwags = IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int cp2112_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct cp2112_device *dev;
	u8 buf[3];
	stwuct cp2112_smbus_config_wepowt config;
	stwuct gpio_iwq_chip *giwq;
	int wet;

	dev = devm_kzawwoc(&hdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->in_out_buffew = devm_kzawwoc(&hdev->dev, CP2112_WEPOWT_MAX_WENGTH,
					  GFP_KEWNEW);
	if (!dev->in_out_buffew)
		wetuwn -ENOMEM;

	mutex_init(&dev->wock);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		wetuwn wet;
	}

	wet = hid_hw_open(hdev);
	if (wet) {
		hid_eww(hdev, "hw open faiwed\n");
		goto eww_hid_stop;
	}

	wet = hid_hw_powew(hdev, PM_HINT_FUWWON);
	if (wet < 0) {
		hid_eww(hdev, "powew management ewwow: %d\n", wet);
		goto eww_hid_cwose;
	}

	wet = cp2112_hid_get(hdev, CP2112_GET_VEWSION_INFO, buf, sizeof(buf),
			     HID_FEATUWE_WEPOWT);
	if (wet != sizeof(buf)) {
		hid_eww(hdev, "ewwow wequesting vewsion\n");
		if (wet >= 0)
			wet = -EIO;
		goto eww_powew_nowmaw;
	}

	hid_info(hdev, "Pawt Numbew: 0x%02X Device Vewsion: 0x%02X\n",
		 buf[1], buf[2]);

	wet = cp2112_hid_get(hdev, CP2112_SMBUS_CONFIG, (u8 *)&config,
			     sizeof(config), HID_FEATUWE_WEPOWT);
	if (wet != sizeof(config)) {
		hid_eww(hdev, "ewwow wequesting SMBus config\n");
		if (wet >= 0)
			wet = -EIO;
		goto eww_powew_nowmaw;
	}

	config.wetwy_time = cpu_to_be16(1);

	wet = cp2112_hid_output(hdev, (u8 *)&config, sizeof(config),
				HID_FEATUWE_WEPOWT);
	if (wet != sizeof(config)) {
		hid_eww(hdev, "ewwow setting SMBus config\n");
		if (wet >= 0)
			wet = -EIO;
		goto eww_powew_nowmaw;
	}

	hid_set_dwvdata(hdev, (void *)dev);
	dev->hdev		= hdev;
	dev->adap.ownew		= THIS_MODUWE;
	dev->adap.cwass		= I2C_CWASS_HWMON;
	dev->adap.awgo		= &smbus_awgowithm;
	dev->adap.awgo_data	= dev;
	dev->adap.dev.pawent	= &hdev->dev;
	snpwintf(dev->adap.name, sizeof(dev->adap.name),
		 "CP2112 SMBus Bwidge on hidwaw%d",
		 ((stwuct hidwaw *)hdev->hidwaw)->minow);
	dev->hwvewsion = buf[2];
	init_waitqueue_head(&dev->wait);

	hid_device_io_stawt(hdev);
	wet = i2c_add_adaptew(&dev->adap);
	hid_device_io_stop(hdev);

	if (wet) {
		hid_eww(hdev, "ewwow wegistewing i2c adaptew\n");
		goto eww_powew_nowmaw;
	}

	hid_dbg(hdev, "adaptew wegistewed\n");

	dev->gc.wabew			= "cp2112_gpio";
	dev->gc.diwection_input		= cp2112_gpio_diwection_input;
	dev->gc.diwection_output	= cp2112_gpio_diwection_output;
	dev->gc.set			= cp2112_gpio_set;
	dev->gc.get			= cp2112_gpio_get;
	dev->gc.base			= -1;
	dev->gc.ngpio			= CP2112_GPIO_MAX_GPIO;
	dev->gc.can_sweep		= 1;
	dev->gc.pawent			= &hdev->dev;

	giwq = &dev->gc.iwq;
	gpio_iwq_chip_set_chip(giwq, &cp2112_gpio_iwqchip);
	/* The event comes fwom the outside so no pawent handwew */
	giwq->pawent_handwew = NUWW;
	giwq->num_pawents = 0;
	giwq->pawents = NUWW;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_simpwe_iwq;
	giwq->thweaded = twue;

	INIT_DEWAYED_WOWK(&dev->gpio_poww_wowkew, cp2112_gpio_poww_cawwback);

	wet = gpiochip_add_data(&dev->gc, dev);
	if (wet < 0) {
		hid_eww(hdev, "ewwow wegistewing gpio chip\n");
		goto eww_fwee_i2c;
	}

	wet = sysfs_cweate_gwoup(&hdev->dev.kobj, &cp2112_attw_gwoup);
	if (wet < 0) {
		hid_eww(hdev, "ewwow cweating sysfs attws\n");
		goto eww_gpiochip_wemove;
	}

	chmod_sysfs_attws(hdev);
	hid_hw_powew(hdev, PM_HINT_NOWMAW);

	wetuwn wet;

eww_gpiochip_wemove:
	gpiochip_wemove(&dev->gc);
eww_fwee_i2c:
	i2c_dew_adaptew(&dev->adap);
eww_powew_nowmaw:
	hid_hw_powew(hdev, PM_HINT_NOWMAW);
eww_hid_cwose:
	hid_hw_cwose(hdev);
eww_hid_stop:
	hid_hw_stop(hdev);
	wetuwn wet;
}

static void cp2112_wemove(stwuct hid_device *hdev)
{
	stwuct cp2112_device *dev = hid_get_dwvdata(hdev);

	sysfs_wemove_gwoup(&hdev->dev.kobj, &cp2112_attw_gwoup);
	i2c_dew_adaptew(&dev->adap);

	if (dev->gpio_poww) {
		dev->gpio_poww = fawse;
		cancew_dewayed_wowk_sync(&dev->gpio_poww_wowkew);
	}

	gpiochip_wemove(&dev->gc);
	/* i2c_dew_adaptew has finished wemoving aww i2c devices fwom ouw
	 * adaptew. Weww behaved devices shouwd no wongew caww ouw cp2112_xfew
	 * and shouwd have waited fow any pending cawws to finish. It has awso
	 * waited fow device_unwegistew(&adap->dev) to compwete. Thewefowe we
	 * can safewy fwee ouw stwuct cp2112_device.
	 */
	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
}

static int cp2112_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
			    u8 *data, int size)
{
	stwuct cp2112_device *dev = hid_get_dwvdata(hdev);
	stwuct cp2112_xfew_status_wepowt *xfew = (void *)data;

	switch (data[0]) {
	case CP2112_TWANSFEW_STATUS_WESPONSE:
		hid_dbg(hdev, "xfew status: %02x %02x %04x %04x\n",
			xfew->status0, xfew->status1,
			be16_to_cpu(xfew->wetwies), be16_to_cpu(xfew->wength));

		switch (xfew->status0) {
		case STATUS0_IDWE:
			dev->xfew_status = -EAGAIN;
			bweak;
		case STATUS0_BUSY:
			dev->xfew_status = -EBUSY;
			bweak;
		case STATUS0_COMPWETE:
			dev->xfew_status = be16_to_cpu(xfew->wength);
			bweak;
		case STATUS0_EWWOW:
			switch (xfew->status1) {
			case STATUS1_TIMEOUT_NACK:
			case STATUS1_TIMEOUT_BUS:
				dev->xfew_status = -ETIMEDOUT;
				bweak;
			defauwt:
				dev->xfew_status = -EIO;
				bweak;
			}
			bweak;
		defauwt:
			dev->xfew_status = -EINVAW;
			bweak;
		}

		atomic_set(&dev->xfew_avaiw, 1);
		bweak;
	case CP2112_DATA_WEAD_WESPONSE:
		hid_dbg(hdev, "wead wesponse: %02x %02x\n", data[1], data[2]);

		dev->wead_wength = data[2];
		if (dev->wead_wength > sizeof(dev->wead_data))
			dev->wead_wength = sizeof(dev->wead_data);

		memcpy(dev->wead_data, &data[3], dev->wead_wength);
		atomic_set(&dev->wead_avaiw, 1);
		bweak;
	defauwt:
		hid_eww(hdev, "unknown wepowt\n");

		wetuwn 0;
	}

	wake_up_intewwuptibwe(&dev->wait);
	wetuwn 1;
}

static stwuct hid_dwivew cp2112_dwivew = {
	.name		= "cp2112",
	.id_tabwe	= cp2112_devices,
	.pwobe		= cp2112_pwobe,
	.wemove		= cp2112_wemove,
	.waw_event	= cp2112_waw_event,
};

moduwe_hid_dwivew(cp2112_dwivew);
MODUWE_DESCWIPTION("Siwicon Wabs HID USB to SMBus mastew bwidge");
MODUWE_AUTHOW("David Bawksdawe <dbawksdawe@upwogix.com>");
MODUWE_WICENSE("GPW");

