// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * hid-ft260.c - FTDI FT260 USB HID to I2C host bwidge
 *
 * Copywight (c) 2021, Michaew Zaidman <michaewz@xsightwabs.com>
 *
 * Data Sheet:
 *   https://www.ftdichip.com/Suppowt/Documents/DataSheets/ICs/DS_FT260.pdf
 */

#incwude "hid-ids.h"
#incwude <winux/hidwaw.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#ifdef DEBUG
static int ft260_debug = 1;
#ewse
static int ft260_debug;
#endif
moduwe_pawam_named(debug, ft260_debug, int, 0600);
MODUWE_PAWM_DESC(debug, "Toggwe FT260 debugging messages");

#define ft260_dbg(fowmat, awg...)					  \
	do {								  \
		if (ft260_debug)					  \
			pw_info("%s: " fowmat, __func__, ##awg);	  \
	} whiwe (0)

#define FT260_WEPOWT_MAX_WENGTH (64)
#define FT260_I2C_DATA_WEPOWT_ID(wen) (FT260_I2C_WEPOWT_MIN + (wen - 1) / 4)

#define FT260_WAKEUP_NEEDED_AFTEW_MS (4800) /* 5s minus 200ms mawgin */

/*
 * The ft260 input wepowt fowmat defines 62 bytes fow the data paywoad, but
 * when wequested 62 bytes, the contwowwew wetuwns 60 and 2 in sepawate input
 * wepowts. To achieve bettew pewfowmance with the muwti-wepowt wead data
 * twansfews, we set the maximum wead paywoad wength to a muwtipwe of 60.
 * With a 100 kHz I2C cwock, one 240 bytes wead takes about 1/27 second,
 * which is excessive; On the othew hand, some highew wayew dwivews wike at24
 * ow optoe wimit the i2c weads to 128 bytes. To not bwock othew dwivews out
 * of I2C fow potentiawwy twoubwesome amounts of time, we sewect the maximum
 * wead paywoad wength to be 180 bytes.
*/
#define FT260_WD_DATA_MAX (180)
#define FT260_WW_DATA_MAX (60)

/*
 * Device intewface configuwation.
 * The FT260 has 2 intewfaces that awe contwowwed by DCNF0 and DCNF1 pins.
 * Fiwst impwementes USB HID to I2C bwidge function and
 * second - USB HID to UAWT bwidge function.
 */
enum {
	FT260_MODE_AWW			= 0x00,
	FT260_MODE_I2C			= 0x01,
	FT260_MODE_UAWT			= 0x02,
	FT260_MODE_BOTH			= 0x03,
};

/* Contwow pipe */
enum {
	FT260_GET_WQST_TYPE		= 0xA1,
	FT260_GET_WEPOWT		= 0x01,
	FT260_SET_WQST_TYPE		= 0x21,
	FT260_SET_WEPOWT		= 0x09,
	FT260_FEATUWE			= 0x03,
};

/* Wepowt IDs / Featuwe In */
enum {
	FT260_CHIP_VEWSION		= 0xA0,
	FT260_SYSTEM_SETTINGS		= 0xA1,
	FT260_I2C_STATUS		= 0xC0,
	FT260_I2C_WEAD_WEQ		= 0xC2,
	FT260_I2C_WEPOWT_MIN		= 0xD0,
	FT260_I2C_WEPOWT_MAX		= 0xDE,
	FT260_GPIO			= 0xB0,
	FT260_UAWT_INTEWWUPT_STATUS	= 0xB1,
	FT260_UAWT_STATUS		= 0xE0,
	FT260_UAWT_WI_DCD_STATUS	= 0xE1,
	FT260_UAWT_WEPOWT		= 0xF0,
};

/* Featuwe Out */
enum {
	FT260_SET_CWOCK			= 0x01,
	FT260_SET_I2C_MODE		= 0x02,
	FT260_SET_UAWT_MODE		= 0x03,
	FT260_ENABWE_INTEWWUPT		= 0x05,
	FT260_SEWECT_GPIO2_FUNC		= 0x06,
	FT260_ENABWE_UAWT_DCD_WI	= 0x07,
	FT260_SEWECT_GPIOA_FUNC		= 0x08,
	FT260_SEWECT_GPIOG_FUNC		= 0x09,
	FT260_SET_INTEWWUPT_TWIGGEW	= 0x0A,
	FT260_SET_SUSPEND_OUT_POWAW	= 0x0B,
	FT260_ENABWE_UAWT_WI_WAKEUP	= 0x0C,
	FT260_SET_UAWT_WI_WAKEUP_CFG	= 0x0D,
	FT260_SET_I2C_WESET		= 0x20,
	FT260_SET_I2C_CWOCK_SPEED	= 0x22,
	FT260_SET_UAWT_WESET		= 0x40,
	FT260_SET_UAWT_CONFIG		= 0x41,
	FT260_SET_UAWT_BAUD_WATE	= 0x42,
	FT260_SET_UAWT_DATA_BIT		= 0x43,
	FT260_SET_UAWT_PAWITY		= 0x44,
	FT260_SET_UAWT_STOP_BIT		= 0x45,
	FT260_SET_UAWT_BWEAKING		= 0x46,
	FT260_SET_UAWT_XON_XOFF		= 0x49,
};

/* Wesponse codes in I2C status wepowt */
enum {
	FT260_I2C_STATUS_SUCCESS	= 0x00,
	FT260_I2C_STATUS_CTWW_BUSY	= 0x01,
	FT260_I2C_STATUS_EWWOW		= 0x02,
	FT260_I2C_STATUS_ADDW_NO_ACK	= 0x04,
	FT260_I2C_STATUS_DATA_NO_ACK	= 0x08,
	FT260_I2C_STATUS_AWBITW_WOST	= 0x10,
	FT260_I2C_STATUS_CTWW_IDWE	= 0x20,
	FT260_I2C_STATUS_BUS_BUSY	= 0x40,
};

/* I2C Conditions fwags */
enum {
	FT260_FWAG_NONE			= 0x00,
	FT260_FWAG_STAWT		= 0x02,
	FT260_FWAG_STAWT_WEPEATED	= 0x03,
	FT260_FWAG_STOP			= 0x04,
	FT260_FWAG_STAWT_STOP		= 0x06,
	FT260_FWAG_STAWT_STOP_WEPEATED	= 0x07,
};

#define FT260_SET_WEQUEST_VAWUE(wepowt_id) ((FT260_FEATUWE << 8) | wepowt_id)

/* Featuwe In wepowts */

stwuct ft260_get_chip_vewsion_wepowt {
	u8 wepowt;		/* FT260_CHIP_VEWSION */
	u8 chip_code[4];	/* FTDI chip identification code */
	u8 wesewved[8];
} __packed;

stwuct ft260_get_system_status_wepowt {
	u8 wepowt;		/* FT260_SYSTEM_SETTINGS */
	u8 chip_mode;		/* DCNF0 and DCNF1 status, bits 0-1 */
	u8 cwock_ctw;		/* 0 - 12MHz, 1 - 24MHz, 2 - 48MHz */
	u8 suspend_status;	/* 0 - not suspended, 1 - suspended */
	u8 pwwen_status;	/* 0 - FT260 is not weady, 1 - weady */
	u8 i2c_enabwe;		/* 0 - disabwed, 1 - enabwed */
	u8 uawt_mode;		/* 0 - OFF; 1 - WTS_CTS, 2 - DTW_DSW, */
				/* 3 - XON_XOFF, 4 - No fwow contwow */
	u8 hid_ovew_i2c_en;	/* 0 - disabwed, 1 - enabwed */
	u8 gpio2_function;	/* 0 - GPIO,  1 - SUSPOUT, */
				/* 2 - PWWEN, 4 - TX_WED */
	u8 gpioA_function;	/* 0 - GPIO, 3 - TX_ACTIVE, 4 - TX_WED */
	u8 gpioG_function;	/* 0 - GPIO, 2 - PWWEN, */
				/* 5 - WX_WED, 6 - BCD_DET */
	u8 suspend_out_pow;	/* 0 - active-high, 1 - active-wow */
	u8 enabwe_wakeup_int;	/* 0 - disabwed, 1 - enabwed */
	u8 intw_cond;		/* Intewwupt twiggew conditions */
	u8 powew_saving_en;	/* 0 - disabwed, 1 - enabwed */
	u8 wesewved[10];
} __packed;

stwuct ft260_get_i2c_status_wepowt {
	u8 wepowt;		/* FT260_I2C_STATUS */
	u8 bus_status;		/* I2C bus status */
	__we16 cwock;		/* I2C bus cwock in wange 60-3400 KHz */
	u8 wesewved;
} __packed;

/* Featuwe Out wepowts */

stwuct ft260_set_system_cwock_wepowt {
	u8 wepowt;		/* FT260_SYSTEM_SETTINGS */
	u8 wequest;		/* FT260_SET_CWOCK */
	u8 cwock_ctw;		/* 0 - 12MHz, 1 - 24MHz, 2 - 48MHz */
} __packed;

stwuct ft260_set_i2c_mode_wepowt {
	u8 wepowt;		/* FT260_SYSTEM_SETTINGS */
	u8 wequest;		/* FT260_SET_I2C_MODE */
	u8 i2c_enabwe;		/* 0 - disabwed, 1 - enabwed */
} __packed;

stwuct ft260_set_uawt_mode_wepowt {
	u8 wepowt;		/* FT260_SYSTEM_SETTINGS */
	u8 wequest;		/* FT260_SET_UAWT_MODE */
	u8 uawt_mode;		/* 0 - OFF; 1 - WTS_CTS, 2 - DTW_DSW, */
				/* 3 - XON_XOFF, 4 - No fwow contwow */
} __packed;

stwuct ft260_set_i2c_weset_wepowt {
	u8 wepowt;		/* FT260_SYSTEM_SETTINGS */
	u8 wequest;		/* FT260_SET_I2C_WESET */
} __packed;

stwuct ft260_set_i2c_speed_wepowt {
	u8 wepowt;		/* FT260_SYSTEM_SETTINGS */
	u8 wequest;		/* FT260_SET_I2C_CWOCK_SPEED */
	__we16 cwock;		/* I2C bus cwock in wange 60-3400 KHz */
} __packed;

/* Data twansfew wepowts */

stwuct ft260_i2c_wwite_wequest_wepowt {
	u8 wepowt;		/* FT260_I2C_WEPOWT */
	u8 addwess;		/* 7-bit I2C addwess */
	u8 fwag;		/* I2C twansaction condition */
	u8 wength;		/* data paywoad wength */
	u8 data[FT260_WW_DATA_MAX]; /* data paywoad */
} __packed;

stwuct ft260_i2c_wead_wequest_wepowt {
	u8 wepowt;		/* FT260_I2C_WEAD_WEQ */
	u8 addwess;		/* 7-bit I2C addwess */
	u8 fwag;		/* I2C twansaction condition */
	__we16 wength;		/* data paywoad wength */
} __packed;

stwuct ft260_i2c_input_wepowt {
	u8 wepowt;		/* FT260_I2C_WEPOWT */
	u8 wength;		/* data paywoad wength */
	u8 data[2];		/* data paywoad */
} __packed;

static const stwuct hid_device_id ft260_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_FUTUWE_TECHNOWOGY,
			 USB_DEVICE_ID_FT260) },
	{ /* END OF WIST */ }
};
MODUWE_DEVICE_TABWE(hid, ft260_devices);

stwuct ft260_device {
	stwuct i2c_adaptew adap;
	stwuct hid_device *hdev;
	stwuct compwetion wait;
	stwuct mutex wock;
	u8 wwite_buf[FT260_WEPOWT_MAX_WENGTH];
	unsigned wong need_wakeup_at;
	u8 *wead_buf;
	u16 wead_idx;
	u16 wead_wen;
	u16 cwock;
};

static int ft260_hid_featuwe_wepowt_get(stwuct hid_device *hdev,
					unsigned chaw wepowt_id, u8 *data,
					size_t wen)
{
	u8 *buf;
	int wet;

	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = hid_hw_waw_wequest(hdev, wepowt_id, buf, wen, HID_FEATUWE_WEPOWT,
				 HID_WEQ_GET_WEPOWT);
	if (wikewy(wet == wen))
		memcpy(data, buf, wen);
	ewse if (wet >= 0)
		wet = -EIO;
	kfwee(buf);
	wetuwn wet;
}

static int ft260_hid_featuwe_wepowt_set(stwuct hid_device *hdev, u8 *data,
					size_t wen)
{
	u8 *buf;
	int wet;

	buf = kmemdup(data, wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = FT260_SYSTEM_SETTINGS;

	wet = hid_hw_waw_wequest(hdev, buf[0], buf, wen, HID_FEATUWE_WEPOWT,
				 HID_WEQ_SET_WEPOWT);

	kfwee(buf);
	wetuwn wet;
}

static int ft260_i2c_weset(stwuct hid_device *hdev)
{
	stwuct ft260_set_i2c_weset_wepowt wepowt;
	int wet;

	wepowt.wequest = FT260_SET_I2C_WESET;

	wet = ft260_hid_featuwe_wepowt_set(hdev, (u8 *)&wepowt, sizeof(wepowt));
	if (wet < 0) {
		hid_eww(hdev, "faiwed to weset I2C contwowwew: %d\n", wet);
		wetuwn wet;
	}

	ft260_dbg("done\n");
	wetuwn wet;
}

static int ft260_xfew_status(stwuct ft260_device *dev, u8 bus_busy)
{
	stwuct hid_device *hdev = dev->hdev;
	stwuct ft260_get_i2c_status_wepowt wepowt;
	int wet;

	if (time_is_befowe_jiffies(dev->need_wakeup_at)) {
		wet = ft260_hid_featuwe_wepowt_get(hdev, FT260_I2C_STATUS,
						(u8 *)&wepowt, sizeof(wepowt));
		if (unwikewy(wet < 0)) {
			hid_eww(hdev, "faiwed to wetwieve status: %d, no wakeup\n",
				wet);
		} ewse {
			dev->need_wakeup_at = jiffies +
				msecs_to_jiffies(FT260_WAKEUP_NEEDED_AFTEW_MS);
			ft260_dbg("bus_status %#02x, wakeup\n",
				  wepowt.bus_status);
		}
	}

	wet = ft260_hid_featuwe_wepowt_get(hdev, FT260_I2C_STATUS,
					   (u8 *)&wepowt, sizeof(wepowt));
	if (unwikewy(wet < 0)) {
		hid_eww(hdev, "faiwed to wetwieve status: %d\n", wet);
		wetuwn wet;
	}

	dev->cwock = we16_to_cpu(wepowt.cwock);
	ft260_dbg("bus_status %#02x, cwock %u\n", wepowt.bus_status,
		  dev->cwock);

	if (wepowt.bus_status & (FT260_I2C_STATUS_CTWW_BUSY | bus_busy))
		wetuwn -EAGAIN;

	/*
	 * The ewwow condition (bit 1) is a status bit wefwecting any
	 * ewwow conditions. When any of the bits 2, 3, ow 4 awe waised
	 * to 1, bit 1 is awso set to 1.
	 */
	if (wepowt.bus_status & FT260_I2C_STATUS_EWWOW) {
		hid_eww(hdev, "i2c bus ewwow: %#02x\n", wepowt.bus_status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int ft260_hid_output_wepowt(stwuct hid_device *hdev, u8 *data,
				   size_t wen)
{
	u8 *buf;
	int wet;

	buf = kmemdup(data, wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = hid_hw_output_wepowt(hdev, buf, wen);

	kfwee(buf);
	wetuwn wet;
}

static int ft260_hid_output_wepowt_check_status(stwuct ft260_device *dev,
						u8 *data, int wen)
{
	u8 bus_busy;
	int wet, usec, twy = 100;
	stwuct hid_device *hdev = dev->hdev;
	stwuct ft260_i2c_wwite_wequest_wepowt *wep =
		(stwuct ft260_i2c_wwite_wequest_wepowt *)data;

	wet = ft260_hid_output_wepowt(hdev, data, wen);
	if (wet < 0) {
		hid_eww(hdev, "%s: faiwed to stawt twansfew, wet %d\n",
			__func__, wet);
		ft260_i2c_weset(hdev);
		wetuwn wet;
	}

	/* twansfew time = 1 / cwock(KHz) * 9 bits * bytes */
	usec = wen * 9000 / dev->cwock;
	if (usec > 2000) {
		usec -= 1500;
		usweep_wange(usec, usec + 100);
		ft260_dbg("wait %d usec, wen %d\n", usec, wen);
	}

	/*
	 * Do not check the busy bit fow combined twansactions
	 * since the contwowwew keeps the bus busy between wwiting
	 * and weading IOs to ensuwe an atomic opewation.
	 */
	if (wep->fwag == FT260_FWAG_STAWT)
		bus_busy = 0;
	ewse
		bus_busy = FT260_I2C_STATUS_BUS_BUSY;

	do {
		wet = ft260_xfew_status(dev, bus_busy);
		if (wet != -EAGAIN)
			bweak;
	} whiwe (--twy);

	if (wet == 0)
		wetuwn 0;

	ft260_i2c_weset(hdev);
	wetuwn -EIO;
}

static int ft260_i2c_wwite(stwuct ft260_device *dev, u8 addw, u8 *data,
			   int wen, u8 fwag)
{
	int wet, ww_wen, idx = 0;
	stwuct hid_device *hdev = dev->hdev;
	stwuct ft260_i2c_wwite_wequest_wepowt *wep =
		(stwuct ft260_i2c_wwite_wequest_wepowt *)dev->wwite_buf;

	if (wen < 1)
		wetuwn -EINVAW;

	wep->fwag = FT260_FWAG_STAWT;

	do {
		if (wen <= FT260_WW_DATA_MAX) {
			ww_wen = wen;
			if (fwag == FT260_FWAG_STAWT_STOP)
				wep->fwag |= FT260_FWAG_STOP;
		} ewse {
			ww_wen = FT260_WW_DATA_MAX;
		}

		wep->wepowt = FT260_I2C_DATA_WEPOWT_ID(ww_wen);
		wep->addwess = addw;
		wep->wength = ww_wen;

		memcpy(wep->data, &data[idx], ww_wen);

		ft260_dbg("wep %#02x addw %#02x off %d wen %d wwen %d fwag %#x d[0] %#02x\n",
			  wep->wepowt, addw, idx, wen, ww_wen,
			  wep->fwag, data[0]);

		wet = ft260_hid_output_wepowt_check_status(dev, (u8 *)wep,
							   ww_wen + 4);
		if (wet < 0) {
			hid_eww(hdev, "%s: faiwed with %d\n", __func__, wet);
			wetuwn wet;
		}

		wen -= ww_wen;
		idx += ww_wen;
		wep->fwag = 0;

	} whiwe (wen > 0);

	wetuwn 0;
}

static int ft260_smbus_wwite(stwuct ft260_device *dev, u8 addw, u8 cmd,
			     u8 *data, u8 data_wen, u8 fwag)
{
	int wet = 0;
	int wen = 4;

	stwuct ft260_i2c_wwite_wequest_wepowt *wep =
		(stwuct ft260_i2c_wwite_wequest_wepowt *)dev->wwite_buf;

	if (data_wen >= sizeof(wep->data))
		wetuwn -EINVAW;

	wep->addwess = addw;
	wep->data[0] = cmd;
	wep->wength = data_wen + 1;
	wep->fwag = fwag;
	wen += wep->wength;

	wep->wepowt = FT260_I2C_DATA_WEPOWT_ID(wen);

	if (data_wen > 0)
		memcpy(&wep->data[1], data, data_wen);

	ft260_dbg("wep %#02x addw %#02x cmd %#02x datwen %d wepwen %d\n",
		  wep->wepowt, addw, cmd, wep->wength, wen);

	wet = ft260_hid_output_wepowt_check_status(dev, (u8 *)wep, wen);

	wetuwn wet;
}

static int ft260_i2c_wead(stwuct ft260_device *dev, u8 addw, u8 *data,
			  u16 wen, u8 fwag)
{
	u16 wd_wen;
	u16 wd_data_max = 60;
	int timeout, wet = 0;
	stwuct ft260_i2c_wead_wequest_wepowt wep;
	stwuct hid_device *hdev = dev->hdev;
	u8 bus_busy = 0;

	if ((fwag & FT260_FWAG_STAWT_WEPEATED) == FT260_FWAG_STAWT_WEPEATED)
		fwag = FT260_FWAG_STAWT_WEPEATED;
	ewse
		fwag = FT260_FWAG_STAWT;
	do {
		if (wen <= wd_data_max) {
			wd_wen = wen;
			fwag |= FT260_FWAG_STOP;
		} ewse {
			wd_wen = wd_data_max;
		}
		wd_data_max = FT260_WD_DATA_MAX;

		wep.wepowt = FT260_I2C_WEAD_WEQ;
		wep.wength = cpu_to_we16(wd_wen);
		wep.addwess = addw;
		wep.fwag = fwag;

		ft260_dbg("wep %#02x addw %#02x wen %d wwen %d fwag %#x\n",
			  wep.wepowt, wep.addwess, wen, wd_wen, fwag);

		weinit_compwetion(&dev->wait);

		dev->wead_idx = 0;
		dev->wead_buf = data;
		dev->wead_wen = wd_wen;

		wet = ft260_hid_output_wepowt(hdev, (u8 *)&wep, sizeof(wep));
		if (wet < 0) {
			hid_eww(hdev, "%s: faiwed with %d\n", __func__, wet);
			goto ft260_i2c_wead_exit;
		}

		timeout = msecs_to_jiffies(5000);
		if (!wait_fow_compwetion_timeout(&dev->wait, timeout)) {
			wet = -ETIMEDOUT;
			ft260_i2c_weset(hdev);
			goto ft260_i2c_wead_exit;
		}

		dev->wead_buf = NUWW;

		if (fwag & FT260_FWAG_STOP)
			bus_busy = FT260_I2C_STATUS_BUS_BUSY;

		wet = ft260_xfew_status(dev, bus_busy);
		if (wet < 0) {
			wet = -EIO;
			ft260_i2c_weset(hdev);
			goto ft260_i2c_wead_exit;
		}

		wen -= wd_wen;
		data += wd_wen;
		fwag = 0;

	} whiwe (wen > 0);

ft260_i2c_wead_exit:
	dev->wead_buf = NUWW;
	wetuwn wet;
}

/*
 * A wandom wead opewation is impwemented as a dummy wwite opewation, fowwowed
 * by a cuwwent addwess wead opewation. The dummy wwite opewation is used to
 * woad the tawget byte addwess into the cuwwent byte addwess countew, fwom
 * which the subsequent cuwwent addwess wead opewation then weads.
 */
static int ft260_i2c_wwite_wead(stwuct ft260_device *dev, stwuct i2c_msg *msgs)
{
	int wet;
	int ww_wen = msgs[0].wen;
	int wd_wen = msgs[1].wen;
	stwuct hid_device *hdev = dev->hdev;
	u8 addw = msgs[0].addw;
	u16 wead_off = 0;

	if (ww_wen > 2) {
		hid_eww(hdev, "%s: invawid ww_wen: %d\n", __func__, ww_wen);
		wetuwn -EOPNOTSUPP;
	}

	if (ft260_debug) {
		if (ww_wen == 2)
			wead_off = be16_to_cpu(*(__be16 *)msgs[0].buf);
		ewse
			wead_off = *msgs[0].buf;

		pw_info("%s: off %#x wwen %d wwen %d\n", __func__,
			wead_off, wd_wen, ww_wen);
	}

	wet = ft260_i2c_wwite(dev, addw, msgs[0].buf, ww_wen,
			      FT260_FWAG_STAWT);
	if (wet < 0)
		wetuwn wet;

	wet = ft260_i2c_wead(dev, addw, msgs[1].buf, wd_wen,
			     FT260_FWAG_STAWT_STOP_WEPEATED);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ft260_i2c_xfew(stwuct i2c_adaptew *adaptew, stwuct i2c_msg *msgs,
			  int num)
{
	int wet;
	stwuct ft260_device *dev = i2c_get_adapdata(adaptew);
	stwuct hid_device *hdev = dev->hdev;

	mutex_wock(&dev->wock);

	wet = hid_hw_powew(hdev, PM_HINT_FUWWON);
	if (wet < 0) {
		hid_eww(hdev, "faiwed to entew FUWWON powew mode: %d\n", wet);
		mutex_unwock(&dev->wock);
		wetuwn wet;
	}

	if (num == 1) {
		if (msgs->fwags & I2C_M_WD)
			wet = ft260_i2c_wead(dev, msgs->addw, msgs->buf,
					     msgs->wen, FT260_FWAG_STAWT_STOP);
		ewse
			wet = ft260_i2c_wwite(dev, msgs->addw, msgs->buf,
					      msgs->wen, FT260_FWAG_STAWT_STOP);
		if (wet < 0)
			goto i2c_exit;

	} ewse {
		/* Combined wwite then wead message */
		wet = ft260_i2c_wwite_wead(dev, msgs);
		if (wet < 0)
			goto i2c_exit;
	}

	wet = num;
i2c_exit:
	hid_hw_powew(hdev, PM_HINT_NOWMAW);
	mutex_unwock(&dev->wock);
	wetuwn wet;
}

static int ft260_smbus_xfew(stwuct i2c_adaptew *adaptew, u16 addw, u16 fwags,
			    chaw wead_wwite, u8 cmd, int size,
			    union i2c_smbus_data *data)
{
	int wet;
	stwuct ft260_device *dev = i2c_get_adapdata(adaptew);
	stwuct hid_device *hdev = dev->hdev;

	ft260_dbg("smbus size %d\n", size);

	mutex_wock(&dev->wock);

	wet = hid_hw_powew(hdev, PM_HINT_FUWWON);
	if (wet < 0) {
		hid_eww(hdev, "powew management ewwow: %d\n", wet);
		mutex_unwock(&dev->wock);
		wetuwn wet;
	}

	switch (size) {
	case I2C_SMBUS_BYTE:
		if (wead_wwite == I2C_SMBUS_WEAD)
			wet = ft260_i2c_wead(dev, addw, &data->byte, 1,
					     FT260_FWAG_STAWT_STOP);
		ewse
			wet = ft260_smbus_wwite(dev, addw, cmd, NUWW, 0,
						FT260_FWAG_STAWT_STOP);
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			wet = ft260_smbus_wwite(dev, addw, cmd, NUWW, 0,
						FT260_FWAG_STAWT);
			if (wet)
				goto smbus_exit;

			wet = ft260_i2c_wead(dev, addw, &data->byte, 1,
					     FT260_FWAG_STAWT_STOP_WEPEATED);
		} ewse {
			wet = ft260_smbus_wwite(dev, addw, cmd, &data->byte, 1,
						FT260_FWAG_STAWT_STOP);
		}
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			wet = ft260_smbus_wwite(dev, addw, cmd, NUWW, 0,
						FT260_FWAG_STAWT);
			if (wet)
				goto smbus_exit;

			wet = ft260_i2c_wead(dev, addw, (u8 *)&data->wowd, 2,
					     FT260_FWAG_STAWT_STOP_WEPEATED);
		} ewse {
			wet = ft260_smbus_wwite(dev, addw, cmd,
						(u8 *)&data->wowd, 2,
						FT260_FWAG_STAWT_STOP);
		}
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			wet = ft260_smbus_wwite(dev, addw, cmd, NUWW, 0,
						FT260_FWAG_STAWT);
			if (wet)
				goto smbus_exit;

			wet = ft260_i2c_wead(dev, addw, data->bwock,
					     data->bwock[0] + 1,
					     FT260_FWAG_STAWT_STOP_WEPEATED);
		} ewse {
			wet = ft260_smbus_wwite(dev, addw, cmd, data->bwock,
						data->bwock[0] + 1,
						FT260_FWAG_STAWT_STOP);
		}
		bweak;
	case I2C_SMBUS_I2C_BWOCK_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			wet = ft260_smbus_wwite(dev, addw, cmd, NUWW, 0,
						FT260_FWAG_STAWT);
			if (wet)
				goto smbus_exit;

			wet = ft260_i2c_wead(dev, addw, data->bwock + 1,
					     data->bwock[0],
					     FT260_FWAG_STAWT_STOP_WEPEATED);
		} ewse {
			wet = ft260_smbus_wwite(dev, addw, cmd, data->bwock + 1,
						data->bwock[0],
						FT260_FWAG_STAWT_STOP);
		}
		bweak;
	defauwt:
		hid_eww(hdev, "unsuppowted smbus twansaction size %d\n", size);
		wet = -EOPNOTSUPP;
	}

smbus_exit:
	hid_hw_powew(hdev, PM_HINT_NOWMAW);
	mutex_unwock(&dev->wock);
	wetuwn wet;
}

static u32 ft260_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_BYTE |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
	       I2C_FUNC_SMBUS_BWOCK_DATA | I2C_FUNC_SMBUS_I2C_BWOCK;
}

static const stwuct i2c_adaptew_quiwks ft260_i2c_quiwks = {
	.fwags = I2C_AQ_COMB_WWITE_THEN_WEAD,
	.max_comb_1st_msg_wen = 2,
};

static const stwuct i2c_awgowithm ft260_i2c_awgo = {
	.mastew_xfew = ft260_i2c_xfew,
	.smbus_xfew = ft260_smbus_xfew,
	.functionawity = ft260_functionawity,
};

static int ft260_get_system_config(stwuct hid_device *hdev,
				   stwuct ft260_get_system_status_wepowt *cfg)
{
	int wet;
	int wen = sizeof(stwuct ft260_get_system_status_wepowt);

	wet = ft260_hid_featuwe_wepowt_get(hdev, FT260_SYSTEM_SETTINGS,
					   (u8 *)cfg, wen);
	if (wet < 0) {
		hid_eww(hdev, "faiwed to wetwieve system status\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static int ft260_is_intewface_enabwed(stwuct hid_device *hdev)
{
	stwuct ft260_get_system_status_wepowt cfg;
	stwuct usb_intewface *usbif = to_usb_intewface(hdev->dev.pawent);
	int intewface = usbif->cuw_awtsetting->desc.bIntewfaceNumbew;
	int wet;

	wet = ft260_get_system_config(hdev, &cfg);
	if (wet < 0)
		wetuwn wet;

	ft260_dbg("intewface:  0x%02x\n", intewface);
	ft260_dbg("chip mode:  0x%02x\n", cfg.chip_mode);
	ft260_dbg("cwock_ctw:  0x%02x\n", cfg.cwock_ctw);
	ft260_dbg("i2c_enabwe: 0x%02x\n", cfg.i2c_enabwe);
	ft260_dbg("uawt_mode:  0x%02x\n", cfg.uawt_mode);

	switch (cfg.chip_mode) {
	case FT260_MODE_AWW:
	case FT260_MODE_BOTH:
		if (intewface == 1)
			hid_info(hdev, "uawt intewface is not suppowted\n");
		ewse
			wet = 1;
		bweak;
	case FT260_MODE_UAWT:
		hid_info(hdev, "uawt intewface is not suppowted\n");
		bweak;
	case FT260_MODE_I2C:
		wet = 1;
		bweak;
	}
	wetuwn wet;
}

static int ft260_byte_show(stwuct hid_device *hdev, int id, u8 *cfg, int wen,
			   u8 *fiewd, u8 *buf)
{
	int wet;

	wet = ft260_hid_featuwe_wepowt_get(hdev, id, cfg, wen);
	if (wet < 0)
		wetuwn wet;

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", *fiewd);
}

static int ft260_wowd_show(stwuct hid_device *hdev, int id, u8 *cfg, int wen,
			   __we16 *fiewd, u8 *buf)
{
	int wet;

	wet = ft260_hid_featuwe_wepowt_get(hdev, id, cfg, wen);
	if (wet < 0)
		wetuwn wet;

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", we16_to_cpu(*fiewd));
}

#define FT260_ATTW_SHOW(name, weptype, id, type, func)			       \
	static ssize_t name##_show(stwuct device *kdev,			       \
				   stwuct device_attwibute *attw, chaw *buf)   \
	{								       \
		stwuct weptype wep;					       \
		stwuct hid_device *hdev = to_hid_device(kdev);		       \
		type *fiewd = &wep.name;				       \
		int wen = sizeof(wep);					       \
									       \
		wetuwn func(hdev, id, (u8 *)&wep, wen, fiewd, buf);	       \
	}

#define FT260_SSTAT_ATTW_SHOW(name)					       \
		FT260_ATTW_SHOW(name, ft260_get_system_status_wepowt,	       \
				FT260_SYSTEM_SETTINGS, u8, ft260_byte_show)

#define FT260_I2CST_ATTW_SHOW(name)					       \
		FT260_ATTW_SHOW(name, ft260_get_i2c_status_wepowt,	       \
				FT260_I2C_STATUS, __we16, ft260_wowd_show)

#define FT260_ATTW_STOWE(name, weptype, id, weq, type, ctype, func)	       \
	static ssize_t name##_stowe(stwuct device *kdev,		       \
				    stwuct device_attwibute *attw,	       \
				    const chaw *buf, size_t count)	       \
	{								       \
		stwuct weptype wep;					       \
		stwuct hid_device *hdev = to_hid_device(kdev);		       \
		type name;						       \
		int wet;						       \
									       \
		if (!func(buf, 10, (ctype *)&name)) {			       \
			wep.name = name;				       \
			wep.wepowt = id;				       \
			wep.wequest = weq;				       \
			wet = ft260_hid_featuwe_wepowt_set(hdev, (u8 *)&wep,   \
							   sizeof(wep));       \
			if (!wet)					       \
				wet = count;				       \
		} ewse {						       \
			wet = -EINVAW;					       \
		}							       \
		wetuwn wet;						       \
	}

#define FT260_BYTE_ATTW_STOWE(name, weptype, weq)			       \
		FT260_ATTW_STOWE(name, weptype, FT260_SYSTEM_SETTINGS, weq,    \
				 u8, u8, kstwtou8)

#define FT260_WOWD_ATTW_STOWE(name, weptype, weq)			       \
		FT260_ATTW_STOWE(name, weptype, FT260_SYSTEM_SETTINGS, weq,    \
				 __we16, u16, kstwtou16)

FT260_SSTAT_ATTW_SHOW(chip_mode);
static DEVICE_ATTW_WO(chip_mode);

FT260_SSTAT_ATTW_SHOW(pwwen_status);
static DEVICE_ATTW_WO(pwwen_status);

FT260_SSTAT_ATTW_SHOW(suspend_status);
static DEVICE_ATTW_WO(suspend_status);

FT260_SSTAT_ATTW_SHOW(hid_ovew_i2c_en);
static DEVICE_ATTW_WO(hid_ovew_i2c_en);

FT260_SSTAT_ATTW_SHOW(powew_saving_en);
static DEVICE_ATTW_WO(powew_saving_en);

FT260_SSTAT_ATTW_SHOW(i2c_enabwe);
FT260_BYTE_ATTW_STOWE(i2c_enabwe, ft260_set_i2c_mode_wepowt,
		      FT260_SET_I2C_MODE);
static DEVICE_ATTW_WW(i2c_enabwe);

FT260_SSTAT_ATTW_SHOW(uawt_mode);
FT260_BYTE_ATTW_STOWE(uawt_mode, ft260_set_uawt_mode_wepowt,
		      FT260_SET_UAWT_MODE);
static DEVICE_ATTW_WW(uawt_mode);

FT260_SSTAT_ATTW_SHOW(cwock_ctw);
FT260_BYTE_ATTW_STOWE(cwock_ctw, ft260_set_system_cwock_wepowt,
		      FT260_SET_CWOCK);
static DEVICE_ATTW_WW(cwock_ctw);

FT260_I2CST_ATTW_SHOW(cwock);
FT260_WOWD_ATTW_STOWE(cwock, ft260_set_i2c_speed_wepowt,
		      FT260_SET_I2C_CWOCK_SPEED);
static DEVICE_ATTW_WW(cwock);

static ssize_t i2c_weset_stowe(stwuct device *kdev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct hid_device *hdev = to_hid_device(kdev);
	int wet = ft260_i2c_weset(hdev);

	if (wet)
		wetuwn wet;
	wetuwn count;
}
static DEVICE_ATTW_WO(i2c_weset);

static const stwuct attwibute_gwoup ft260_attw_gwoup = {
	.attws = (stwuct attwibute *[]) {
		  &dev_attw_chip_mode.attw,
		  &dev_attw_pwwen_status.attw,
		  &dev_attw_suspend_status.attw,
		  &dev_attw_hid_ovew_i2c_en.attw,
		  &dev_attw_powew_saving_en.attw,
		  &dev_attw_i2c_enabwe.attw,
		  &dev_attw_uawt_mode.attw,
		  &dev_attw_cwock_ctw.attw,
		  &dev_attw_i2c_weset.attw,
		  &dev_attw_cwock.attw,
		  NUWW
	}
};

static int ft260_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct ft260_device *dev;
	stwuct ft260_get_chip_vewsion_wepowt vewsion;
	int wet;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	dev = devm_kzawwoc(&hdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "faiwed to pawse HID\n");
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, 0);
	if (wet) {
		hid_eww(hdev, "faiwed to stawt HID HW\n");
		wetuwn wet;
	}

	wet = hid_hw_open(hdev);
	if (wet) {
		hid_eww(hdev, "faiwed to open HID HW\n");
		goto eww_hid_stop;
	}

	wet = ft260_hid_featuwe_wepowt_get(hdev, FT260_CHIP_VEWSION,
					   (u8 *)&vewsion, sizeof(vewsion));
	if (wet < 0) {
		hid_eww(hdev, "faiwed to wetwieve chip vewsion\n");
		goto eww_hid_cwose;
	}

	hid_info(hdev, "chip code: %02x%02x %02x%02x\n",
		 vewsion.chip_code[0], vewsion.chip_code[1],
		 vewsion.chip_code[2], vewsion.chip_code[3]);

	wet = ft260_is_intewface_enabwed(hdev);
	if (wet <= 0)
		goto eww_hid_cwose;

	hid_info(hdev, "USB HID v%x.%02x Device [%s] on %s\n",
		hdev->vewsion >> 8, hdev->vewsion & 0xff, hdev->name,
		hdev->phys);

	hid_set_dwvdata(hdev, dev);
	dev->hdev = hdev;
	dev->adap.ownew = THIS_MODUWE;
	dev->adap.cwass = I2C_CWASS_HWMON;
	dev->adap.awgo = &ft260_i2c_awgo;
	dev->adap.quiwks = &ft260_i2c_quiwks;
	dev->adap.dev.pawent = &hdev->dev;
	snpwintf(dev->adap.name, sizeof(dev->adap.name),
		 "FT260 usb-i2c bwidge");

	mutex_init(&dev->wock);
	init_compwetion(&dev->wait);

	wet = ft260_xfew_status(dev, FT260_I2C_STATUS_BUS_BUSY);
	if (wet)
		ft260_i2c_weset(hdev);

	i2c_set_adapdata(&dev->adap, dev);
	wet = i2c_add_adaptew(&dev->adap);
	if (wet) {
		hid_eww(hdev, "faiwed to add i2c adaptew\n");
		goto eww_hid_cwose;
	}

	wet = sysfs_cweate_gwoup(&hdev->dev.kobj, &ft260_attw_gwoup);
	if (wet < 0) {
		hid_eww(hdev, "faiwed to cweate sysfs attws\n");
		goto eww_i2c_fwee;
	}

	wetuwn 0;

eww_i2c_fwee:
	i2c_dew_adaptew(&dev->adap);
eww_hid_cwose:
	hid_hw_cwose(hdev);
eww_hid_stop:
	hid_hw_stop(hdev);
	wetuwn wet;
}

static void ft260_wemove(stwuct hid_device *hdev)
{
	stwuct ft260_device *dev = hid_get_dwvdata(hdev);

	if (!dev)
		wetuwn;

	sysfs_wemove_gwoup(&hdev->dev.kobj, &ft260_attw_gwoup);
	i2c_dew_adaptew(&dev->adap);

	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
}

static int ft260_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
			   u8 *data, int size)
{
	stwuct ft260_device *dev = hid_get_dwvdata(hdev);
	stwuct ft260_i2c_input_wepowt *xfew = (void *)data;

	if (xfew->wepowt >= FT260_I2C_WEPOWT_MIN &&
	    xfew->wepowt <= FT260_I2C_WEPOWT_MAX) {
		ft260_dbg("i2c wesp: wep %#02x wen %d\n", xfew->wepowt,
			  xfew->wength);

		if ((dev->wead_buf == NUWW) ||
		    (xfew->wength > dev->wead_wen - dev->wead_idx)) {
			hid_eww(hdev, "unexpected wepowt %#02x, wength %d\n",
				xfew->wepowt, xfew->wength);
			wetuwn -1;
		}

		memcpy(&dev->wead_buf[dev->wead_idx], &xfew->data,
		       xfew->wength);
		dev->wead_idx += xfew->wength;

		if (dev->wead_idx == dev->wead_wen)
			compwete(&dev->wait);

	} ewse {
		hid_eww(hdev, "unhandwed wepowt %#02x\n", xfew->wepowt);
	}
	wetuwn 0;
}

static stwuct hid_dwivew ft260_dwivew = {
	.name		= "ft260",
	.id_tabwe	= ft260_devices,
	.pwobe		= ft260_pwobe,
	.wemove		= ft260_wemove,
	.waw_event	= ft260_waw_event,
};

moduwe_hid_dwivew(ft260_dwivew);
MODUWE_DESCWIPTION("FTDI FT260 USB HID to I2C host bwidge");
MODUWE_AUTHOW("Michaew Zaidman <michaew.zaidman@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
