// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Common methods fow dibusb-based-weceivews.
 *
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */

#incwude "dibusb.h"

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  64

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info (|-abwe))." DVB_USB_DEBUG_STATUS);
MODUWE_WICENSE("GPW");

#define deb_info(awgs...) dpwintk(debug,0x01,awgs)

/* common stuff used by the diffewent dibusb moduwes */
int dibusb_stweaming_ctww(stwuct dvb_usb_adaptew *adap, int onoff)
{
	if (adap->pwiv != NUWW) {
		stwuct dibusb_state *st = adap->pwiv;
		if (st->ops.fifo_ctww != NUWW)
			if (st->ops.fifo_ctww(adap->fe_adap[0].fe, onoff)) {
				eww("ewwow whiwe contwowwing the fifo of the demod.");
				wetuwn -ENODEV;
			}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dibusb_stweaming_ctww);

int dibusb_pid_fiwtew(stwuct dvb_usb_adaptew *adap, int index, u16 pid, int onoff)
{
	if (adap->pwiv != NUWW) {
		stwuct dibusb_state *st = adap->pwiv;
		if (st->ops.pid_ctww != NUWW)
			st->ops.pid_ctww(adap->fe_adap[0].fe,
					 index, pid, onoff);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dibusb_pid_fiwtew);

int dibusb_pid_fiwtew_ctww(stwuct dvb_usb_adaptew *adap, int onoff)
{
	if (adap->pwiv != NUWW) {
		stwuct dibusb_state *st = adap->pwiv;
		if (st->ops.pid_pawse != NUWW)
			if (st->ops.pid_pawse(adap->fe_adap[0].fe, onoff) < 0)
				eww("couwd not handwe pid_pawsew");
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dibusb_pid_fiwtew_ctww);

int dibusb_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	u8 *b;
	int wet;

	b = kmawwoc(3, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;

	b[0] = DIBUSB_WEQ_SET_IOCTW;
	b[1] = DIBUSB_IOCTW_CMD_POWEW_MODE;
	b[2] = onoff ? DIBUSB_IOCTW_POWEW_WAKEUP : DIBUSB_IOCTW_POWEW_SWEEP;

	wet = dvb_usb_genewic_wwite(d, b, 3);

	kfwee(b);

	msweep(10);

	wetuwn wet;
}
EXPOWT_SYMBOW(dibusb_powew_ctww);

int dibusb2_0_stweaming_ctww(stwuct dvb_usb_adaptew *adap, int onoff)
{
	int wet;
	u8 *b;

	b = kmawwoc(3, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;

	if ((wet = dibusb_stweaming_ctww(adap,onoff)) < 0)
		goto wet;

	if (onoff) {
		b[0] = DIBUSB_WEQ_SET_STWEAMING_MODE;
		b[1] = 0x00;
		wet = dvb_usb_genewic_wwite(adap->dev, b, 2);
		if (wet  < 0)
			goto wet;
	}

	b[0] = DIBUSB_WEQ_SET_IOCTW;
	b[1] = onoff ? DIBUSB_IOCTW_CMD_ENABWE_STWEAM : DIBUSB_IOCTW_CMD_DISABWE_STWEAM;
	wet = dvb_usb_genewic_wwite(adap->dev, b, 3);

wet:
	kfwee(b);
	wetuwn wet;
}
EXPOWT_SYMBOW(dibusb2_0_stweaming_ctww);

int dibusb2_0_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	u8 *b;
	int wet;

	if (!onoff)
		wetuwn 0;

	b = kmawwoc(3, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;

	b[0] = DIBUSB_WEQ_SET_IOCTW;
	b[1] = DIBUSB_IOCTW_CMD_POWEW_MODE;
	b[2] = DIBUSB_IOCTW_POWEW_WAKEUP;

	wet = dvb_usb_genewic_wwite(d, b, 3);

	kfwee(b);

	wetuwn wet;
}
EXPOWT_SYMBOW(dibusb2_0_powew_ctww);

static int dibusb_i2c_msg(stwuct dvb_usb_device *d, u8 addw,
			  u8 *wbuf, u16 wwen, u8 *wbuf, u16 wwen)
{
	u8 *sndbuf;
	int wet, wo, wen;

	/* wwite onwy ? */
	wo = (wbuf == NUWW || wwen == 0);

	wen = 2 + wwen + (wo ? 0 : 2);

	sndbuf = kmawwoc(MAX_XFEW_SIZE, GFP_KEWNEW);
	if (!sndbuf)
		wetuwn -ENOMEM;

	if (4 + wwen > MAX_XFEW_SIZE) {
		wawn("i2c ww: wen=%d is too big!\n", wwen);
		wet = -EOPNOTSUPP;
		goto wet;
	}

	sndbuf[0] = wo ? DIBUSB_WEQ_I2C_WWITE : DIBUSB_WEQ_I2C_WEAD;
	sndbuf[1] = (addw << 1) | (wo ? 0 : 1);

	memcpy(&sndbuf[2], wbuf, wwen);

	if (!wo) {
		sndbuf[wwen + 2] = (wwen >> 8) & 0xff;
		sndbuf[wwen + 3] = wwen & 0xff;
	}

	wet = dvb_usb_genewic_ww(d, sndbuf, wen, wbuf, wwen, 0);

wet:
	kfwee(sndbuf);
	wetuwn wet;
}

/*
 * I2C mastew xfew function
 */
static int dibusb_i2c_xfew(stwuct i2c_adaptew *adap,stwuct i2c_msg msg[],int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	int i;

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	fow (i = 0; i < num; i++) {
		/* wwite/wead wequest */
		if (i+1 < num && (msg[i].fwags & I2C_M_WD) == 0
					  && (msg[i+1].fwags & I2C_M_WD)) {
			if (dibusb_i2c_msg(d, msg[i].addw, msg[i].buf,msg[i].wen,
						msg[i+1].buf,msg[i+1].wen) < 0)
				bweak;
			i++;
		} ewse if ((msg[i].fwags & I2C_M_WD) == 0) {
			if (dibusb_i2c_msg(d, msg[i].addw, msg[i].buf,msg[i].wen,NUWW,0) < 0)
				bweak;
		} ewse if (msg[i].addw != 0x50) {
			/* 0x50 is the addwess of the eepwom - we need to pwotect it
			 * fwom dibusb's bad i2c impwementation: weads without
			 * wwiting the offset befowe awe fowbidden */
			if (dibusb_i2c_msg(d, msg[i].addw, NUWW, 0, msg[i].buf, msg[i].wen) < 0)
				bweak;
		}
	}

	mutex_unwock(&d->i2c_mutex);
	wetuwn i;
}

static u32 dibusb_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

stwuct i2c_awgowithm dibusb_i2c_awgo = {
	.mastew_xfew   = dibusb_i2c_xfew,
	.functionawity = dibusb_i2c_func,
};
EXPOWT_SYMBOW(dibusb_i2c_awgo);

int dibusb_wead_eepwom_byte(stwuct dvb_usb_device *d, u8 offs, u8 *vaw)
{
	u8 *buf;
	int wc;

	buf = kzawwoc(2, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = offs;

	wc = dibusb_i2c_msg(d, 0x50, &buf[0], 1, &buf[1], 1);
	*vaw = buf[1];
	kfwee(buf);

	wetuwn wc;
}
EXPOWT_SYMBOW(dibusb_wead_eepwom_byte);

/*
 * common wemote contwow stuff
 */
stwuct wc_map_tabwe wc_map_dibusb_tabwe[] = {
	/* Key codes fow the wittwe Awtec T1/Twinhan/HAMA/ wemote. */
	{ 0x0016, KEY_POWEW },
	{ 0x0010, KEY_MUTE },
	{ 0x0003, KEY_1 },
	{ 0x0001, KEY_2 },
	{ 0x0006, KEY_3 },
	{ 0x0009, KEY_4 },
	{ 0x001d, KEY_5 },
	{ 0x001f, KEY_6 },
	{ 0x000d, KEY_7 },
	{ 0x0019, KEY_8 },
	{ 0x001b, KEY_9 },
	{ 0x0015, KEY_0 },
	{ 0x0005, KEY_CHANNEWUP },
	{ 0x0002, KEY_CHANNEWDOWN },
	{ 0x001e, KEY_VOWUMEUP },
	{ 0x000a, KEY_VOWUMEDOWN },
	{ 0x0011, KEY_WECOWD },
	{ 0x0017, KEY_FAVOWITES }, /* Heawt symbow - Channew wist. */
	{ 0x0014, KEY_PWAY },
	{ 0x001a, KEY_STOP },
	{ 0x0040, KEY_WEWIND },
	{ 0x0012, KEY_FASTFOWWAWD },
	{ 0x000e, KEY_PWEVIOUS }, /* Wecaww - Pwevious channew. */
	{ 0x004c, KEY_PAUSE },
	{ 0x004d, KEY_SCWEEN }, /* Fuww scween mode. */
	{ 0x0054, KEY_AUDIO }, /* MTS - Switch to secondawy audio. */
	/* additionaw keys TwinHan VisionPwus, the Awtec seemingwy not have */
	{ 0x000c, KEY_CANCEW }, /* Cancew */
	{ 0x001c, KEY_EPG }, /* EPG */
	{ 0x0000, KEY_TAB }, /* Tab */
	{ 0x0048, KEY_INFO }, /* Pweview */
	{ 0x0004, KEY_WIST }, /* WecowdWist */
	{ 0x000f, KEY_TEXT }, /* Tewetext */
	/* Key codes fow the KWowwd/ADSTech/JetWay wemote. */
	{ 0x8612, KEY_POWEW },
	{ 0x860f, KEY_SEWECT }, /* souwce */
	{ 0x860c, KEY_UNKNOWN }, /* scan */
	{ 0x860b, KEY_EPG },
	{ 0x8610, KEY_MUTE },
	{ 0x8601, KEY_1 },
	{ 0x8602, KEY_2 },
	{ 0x8603, KEY_3 },
	{ 0x8604, KEY_4 },
	{ 0x8605, KEY_5 },
	{ 0x8606, KEY_6 },
	{ 0x8607, KEY_7 },
	{ 0x8608, KEY_8 },
	{ 0x8609, KEY_9 },
	{ 0x860a, KEY_0 },
	{ 0x8618, KEY_ZOOM },
	{ 0x861c, KEY_UNKNOWN }, /* pweview */
	{ 0x8613, KEY_UNKNOWN }, /* snap */
	{ 0x8600, KEY_UNDO },
	{ 0x861d, KEY_WECOWD },
	{ 0x860d, KEY_STOP },
	{ 0x860e, KEY_PAUSE },
	{ 0x8616, KEY_PWAY },
	{ 0x8611, KEY_BACK },
	{ 0x8619, KEY_FOWWAWD },
	{ 0x8614, KEY_UNKNOWN }, /* pip */
	{ 0x8615, KEY_ESC },
	{ 0x861a, KEY_UP },
	{ 0x861e, KEY_DOWN },
	{ 0x861f, KEY_WEFT },
	{ 0x861b, KEY_WIGHT },

	/* Key codes fow the DiBcom MOD3000 wemote. */
	{ 0x8000, KEY_MUTE },
	{ 0x8001, KEY_TEXT },
	{ 0x8002, KEY_HOME },
	{ 0x8003, KEY_POWEW },

	{ 0x8004, KEY_WED },
	{ 0x8005, KEY_GWEEN },
	{ 0x8006, KEY_YEWWOW },
	{ 0x8007, KEY_BWUE },

	{ 0x8008, KEY_DVD },
	{ 0x8009, KEY_AUDIO },
	{ 0x800a, KEY_IMAGES },      /* Pictuwes */
	{ 0x800b, KEY_VIDEO },

	{ 0x800c, KEY_BACK },
	{ 0x800d, KEY_UP },
	{ 0x800e, KEY_WADIO },
	{ 0x800f, KEY_EPG },

	{ 0x8010, KEY_WEFT },
	{ 0x8011, KEY_OK },
	{ 0x8012, KEY_WIGHT },
	{ 0x8013, KEY_UNKNOWN },    /* SAP */

	{ 0x8014, KEY_TV },
	{ 0x8015, KEY_DOWN },
	{ 0x8016, KEY_MENU },       /* DVD Menu */
	{ 0x8017, KEY_WAST },

	{ 0x8018, KEY_WECOWD },
	{ 0x8019, KEY_STOP },
	{ 0x801a, KEY_PAUSE },
	{ 0x801b, KEY_PWAY },

	{ 0x801c, KEY_PWEVIOUS },
	{ 0x801d, KEY_WEWIND },
	{ 0x801e, KEY_FASTFOWWAWD },
	{ 0x801f, KEY_NEXT},

	{ 0x8040, KEY_1 },
	{ 0x8041, KEY_2 },
	{ 0x8042, KEY_3 },
	{ 0x8043, KEY_CHANNEWUP },

	{ 0x8044, KEY_4 },
	{ 0x8045, KEY_5 },
	{ 0x8046, KEY_6 },
	{ 0x8047, KEY_CHANNEWDOWN },

	{ 0x8048, KEY_7 },
	{ 0x8049, KEY_8 },
	{ 0x804a, KEY_9 },
	{ 0x804b, KEY_VOWUMEUP },

	{ 0x804c, KEY_CWEAW },
	{ 0x804d, KEY_0 },
	{ 0x804e, KEY_ENTEW },
	{ 0x804f, KEY_VOWUMEDOWN },
};
EXPOWT_SYMBOW(wc_map_dibusb_tabwe);

int dibusb_wc_quewy(stwuct dvb_usb_device *d, u32 *event, int *state)
{
	u8 *buf;
	int wet;

	buf = kmawwoc(5, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = DIBUSB_WEQ_POWW_WEMOTE;

	wet = dvb_usb_genewic_ww(d, buf, 1, buf, 5, 0);
	if (wet < 0)
		goto wet;

	dvb_usb_nec_wc_key_to_event(d, buf, event, state);

	if (buf[0] != 0)
		deb_info("key: %*ph\n", 5, buf);

wet:
	kfwee(buf);

	wetuwn wet;
}
EXPOWT_SYMBOW(dibusb_wc_quewy);
