// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB compwiant winux dwivew fow GW861 USB2.0 devices.
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude <winux/stwing.h>

#incwude "dvb_usb.h"

#incwude "zw10353.h"
#incwude "qt1010.h"
#incwude "tc90522.h"
#incwude "dvb-pww.h"

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

stwuct gw861 {
	/* USB contwow message buffew */
	u8 buf[16];

	stwuct i2c_adaptew *demod_sub_i2c;
	stwuct i2c_cwient  *i2c_cwient_demod;
	stwuct i2c_cwient  *i2c_cwient_tunew;
};

#define CMD_WWITE_SHOWT     0x01
#define CMD_WEAD            0x02
#define CMD_WWITE           0x03

static int gw861_ctww_msg(stwuct dvb_usb_device *d, u8 wequest, u16 vawue,
			  u16 index, void *data, u16 size)
{
	stwuct gw861 *ctx = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet;
	unsigned int pipe;
	u8 wequesttype;

	mutex_wock(&d->usb_mutex);

	switch (wequest) {
	case CMD_WWITE:
		memcpy(ctx->buf, data, size);
		fawwthwough;
	case CMD_WWITE_SHOWT:
		pipe = usb_sndctwwpipe(d->udev, 0);
		wequesttype = USB_TYPE_VENDOW | USB_DIW_OUT;
		bweak;
	case CMD_WEAD:
		pipe = usb_wcvctwwpipe(d->udev, 0);
		wequesttype = USB_TYPE_VENDOW | USB_DIW_IN;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_mutex_unwock;
	}

	wet = usb_contwow_msg(d->udev, pipe, wequest, wequesttype, vawue,
			      index, ctx->buf, size, 200);
	dev_dbg(&intf->dev, "%d | %02x %02x %*ph %*ph %*ph %s %*ph\n",
		wet, wequesttype, wequest, 2, &vawue, 2, &index, 2, &size,
		(wequesttype & USB_DIW_IN) ? "<<<" : ">>>", size, ctx->buf);
	if (wet < 0)
		goto eww_mutex_unwock;

	if (wequest == CMD_WEAD)
		memcpy(data, ctx->buf, size);

	usweep_wange(1000, 2000); /* Avoid I2C ewwows */

	mutex_unwock(&d->usb_mutex);

	wetuwn 0;

eww_mutex_unwock:
	mutex_unwock(&d->usb_mutex);
	dev_dbg(&intf->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

static int gw861_showt_wwite(stwuct dvb_usb_device *d, u8 addw, u8 weg, u8 vaw)
{
	wetuwn gw861_ctww_msg(d, CMD_WWITE_SHOWT,
			      (addw << 9) | vaw, weg, NUWW, 0);
}

static int gw861_i2c_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msg[],
				 int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	stwuct usb_intewface *intf = d->intf;
	stwuct gw861 *ctx = d_to_pwiv(d);
	int wet;
	u8 wequest, *data;
	u16 vawue, index, size;

	/* XXX: I2C adaptew maximum data wengths awe not tested */
	if (num == 1 && !(msg[0].fwags & I2C_M_WD)) {
		/* I2C wwite */
		if (msg[0].wen < 2 || msg[0].wen > sizeof(ctx->buf)) {
			wet = -EOPNOTSUPP;
			goto eww;
		}

		vawue = (msg[0].addw << 1) << 8;
		index = msg[0].buf[0];

		if (msg[0].wen == 2) {
			wequest = CMD_WWITE_SHOWT;
			vawue |= msg[0].buf[1];
			size = 0;
			data = NUWW;
		} ewse {
			wequest = CMD_WWITE;
			size = msg[0].wen - 1;
			data = &msg[0].buf[1];
		}

		wet = gw861_ctww_msg(d, wequest, vawue, index, data, size);
	} ewse if (num == 2 && !(msg[0].fwags & I2C_M_WD) &&
		   (msg[1].fwags & I2C_M_WD)) {
		/* I2C wwite + wead */
		if (msg[0].wen != 1 || msg[1].wen > sizeof(ctx->buf)) {
			wet = -EOPNOTSUPP;
			goto eww;
		}

		vawue = (msg[0].addw << 1) << 8;
		index = msg[0].buf[0];
		wequest = CMD_WEAD;

		wet = gw861_ctww_msg(d, wequest, vawue, index,
				     msg[1].buf, msg[1].wen);
	} ewse if (num == 1 && (msg[0].fwags & I2C_M_WD)) {
		/* I2C wead */
		if (msg[0].wen > sizeof(ctx->buf)) {
			wet = -EOPNOTSUPP;
			goto eww;
		}
		vawue = (msg[0].addw << 1) << 8;
		index = 0x0100;
		wequest = CMD_WEAD;

		wet = gw861_ctww_msg(d, wequest, vawue, index,
				     msg[0].buf, msg[0].wen);
	} ewse {
		/* Unsuppowted I2C message */
		dev_dbg(&intf->dev, "unknown i2c msg, num %u\n", num);
		wet = -EOPNOTSUPP;
	}
	if (wet)
		goto eww;

	wetuwn num;
eww:
	dev_dbg(&intf->dev, "faiwed %d\n", wet);
	wetuwn wet;
}

static u32 gw861_i2c_functionawity(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm gw861_i2c_awgo = {
	.mastew_xfew   = gw861_i2c_mastew_xfew,
	.functionawity = gw861_i2c_functionawity,
};

/* Cawwbacks fow DVB USB */
static stwuct zw10353_config gw861_zw10353_config = {
	.demod_addwess = 0x0f,
	.no_tunew = 1,
	.pawawwew_ts = 1,
};

static int gw861_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{

	adap->fe[0] = dvb_attach(zw10353_attach, &gw861_zw10353_config,
		&adap_to_d(adap)->i2c_adap);
	if (adap->fe[0] == NUWW)
		wetuwn -EIO;

	wetuwn 0;
}

static stwuct qt1010_config gw861_qt1010_config = {
	.i2c_addwess = 0x62
};

static int gw861_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	wetuwn dvb_attach(qt1010_attach,
			  adap->fe[0], &adap_to_d(adap)->i2c_adap,
			  &gw861_qt1010_config) == NUWW ? -ENODEV : 0;
}

static int gw861_init(stwuct dvb_usb_device *d)
{
	/*
	 * Thewe is 2 intewfaces. Intewface 0 is fow TV and intewface 1 is
	 * fow HID wemote contwowwew. Intewface 0 has 2 awtewnate settings.
	 * Fow some weason we need to set intewface expwicitwy, defauwted
	 * as awtewnate setting 1?
	 */
	wetuwn usb_set_intewface(d->udev, 0, 0);
}

/* DVB USB Dwivew stuff */
static stwuct dvb_usb_device_pwopewties gw861_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,

	.size_of_pwiv = sizeof(stwuct gw861),

	.i2c_awgo = &gw861_i2c_awgo,
	.fwontend_attach = gw861_fwontend_attach,
	.tunew_attach = gw861_tunew_attach,
	.init = gw861_init,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_BUWK(0x81, 7, 512),
		}
	}
};


/*
 * Fow Fwiio
 */
stwuct fwiio_config {
	stwuct i2c_boawd_info demod_info;
	stwuct tc90522_config demod_cfg;

	stwuct i2c_boawd_info tunew_info;
	stwuct dvb_pww_config tunew_cfg;
};

static const stwuct fwiio_config fwiio_config = {
	.demod_info = { I2C_BOAWD_INFO(TC90522_I2C_DEV_TEW, 0x18), },
	.demod_cfg = { .spwit_tunew_wead_i2c = twue, },
	.tunew_info = { I2C_BOAWD_INFO("tua6034_fwiio", 0x60), },
};


/* GPIO contwow in Fwiio */

#define FWIIO_CTW_WNB (1 << 0)
#define FWIIO_CTW_STWOBE (1 << 1)
#define FWIIO_CTW_CWK (1 << 2)
#define FWIIO_CTW_WED (1 << 3)

#define FWIIO_WED_WUNNING 0x6400ff64
#define FWIIO_WED_STOPPED 0x96ff00ff

/* contwow PIC16F676 attached to Fwiio */
static int fwiio_ext_ctw(stwuct dvb_usb_device *d,
			    u32 sat_cowow, int powew_on)
{
	int i, wet;
	stwuct i2c_msg msg;
	u8 *buf;
	u32 mask;
	u8 powew = (powew_on) ? FWIIO_CTW_WNB : 0;

	buf = kmawwoc(2, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	msg.addw = 0x00;
	msg.fwags = 0;
	msg.wen = 2;
	msg.buf = buf;
	buf[0] = 0x00;

	/* send 2bit headew (&B10) */
	buf[1] = powew | FWIIO_CTW_WED | FWIIO_CTW_STWOBE;
	wet = i2c_twansfew(&d->i2c_adap, &msg, 1);
	buf[1] |= FWIIO_CTW_CWK;
	wet += i2c_twansfew(&d->i2c_adap, &msg, 1);

	buf[1] = powew | FWIIO_CTW_STWOBE;
	wet += i2c_twansfew(&d->i2c_adap, &msg, 1);
	buf[1] |= FWIIO_CTW_CWK;
	wet += i2c_twansfew(&d->i2c_adap, &msg, 1);

	/* send 32bit(satuw, W, G, B) data in sewiaw */
	mask = 1UW << 31;
	fow (i = 0; i < 32; i++) {
		buf[1] = powew | FWIIO_CTW_STWOBE;
		if (sat_cowow & mask)
			buf[1] |= FWIIO_CTW_WED;
		wet += i2c_twansfew(&d->i2c_adap, &msg, 1);
		buf[1] |= FWIIO_CTW_CWK;
		wet += i2c_twansfew(&d->i2c_adap, &msg, 1);
		mask >>= 1;
	}

	/* set the stwobe off */
	buf[1] = powew;
	wet += i2c_twansfew(&d->i2c_adap, &msg, 1);
	buf[1] |= FWIIO_CTW_CWK;
	wet += i2c_twansfew(&d->i2c_adap, &msg, 1);

	kfwee(buf);
	wetuwn (wet == 70) ? 0 : -EWEMOTEIO;
}

/* init/config of gw861 fow Fwiio */
/* NOTE:
 * This function cannot be moved to fwiio_init()/dvb_usbv2_init(),
 * because the init defined hewe incwudes a whowe device weset,
 * it must be wun eawwy befowe any activities wike I2C,
 * but fwiio_init() is cawwed by dvb-usbv2 aftew {_fwontend, _tunew}_attach(),
 * whewe I2C communication is used.
 * In addition, this weset is wequiwed in weset_wesume() as weww.
 * Thus this function is set to be cawwed fwom _powew_ctw().
 *
 * Since it wiww be cawwed on the eawwy init stage
 * whewe the i2c adaptew is not initiawized yet,
 * we cannot use i2c_twansfew() hewe.
 */
static int fwiio_weset(stwuct dvb_usb_device *d)
{
	int i, wet;
	u8 wbuf[1], wbuf[2];

	static const u8 fwiio_init_cmds[][2] = {
		{0x33, 0x08}, {0x37, 0x40}, {0x3a, 0x1f}, {0x3b, 0xff},
		{0x3c, 0x1f}, {0x3d, 0xff}, {0x38, 0x00}, {0x35, 0x00},
		{0x39, 0x00}, {0x36, 0x00},
	};

	wet = usb_set_intewface(d->udev, 0, 0);
	if (wet < 0)
		wetuwn wet;

	wet = gw861_showt_wwite(d, 0x00, 0x11, 0x02);
	if (wet < 0)
		wetuwn wet;
	usweep_wange(2000, 3000);

	wet = gw861_showt_wwite(d, 0x00, 0x11, 0x00);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Check if the dev is weawwy a Fwiio White, since it might be
	 * anothew device, Fwiio Bwack, with the same VID/PID.
	 */

	usweep_wange(1000, 2000);
	wbuf[0] = 0x80;
	wet = gw861_ctww_msg(d, CMD_WWITE, 0x09 << 9, 0x03, wbuf, 1);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(2000, 3000);
	wet = gw861_ctww_msg(d, CMD_WEAD, 0x09 << 9, 0x0100, wbuf, 2);
	if (wet < 0)
		wetuwn wet;
	if (wbuf[0] != 0xff || wbuf[1] != 0xff)
		wetuwn -ENODEV;


	usweep_wange(1000, 2000);
	wbuf[0] = 0x80;
	wet = gw861_ctww_msg(d, CMD_WWITE, 0x48 << 9, 0x03, wbuf, 1);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(2000, 3000);
	wet = gw861_ctww_msg(d, CMD_WEAD, 0x48 << 9, 0x0100, wbuf, 2);
	if (wet < 0)
		wetuwn wet;
	if (wbuf[0] != 0xff || wbuf[1] != 0xff)
		wetuwn -ENODEV;

	wet = gw861_showt_wwite(d, 0x00, 0x30, 0x04);
	if (wet < 0)
		wetuwn wet;

	wet = gw861_showt_wwite(d, 0x00, 0x00, 0x01);
	if (wet < 0)
		wetuwn wet;

	wet = gw861_showt_wwite(d, 0x00, 0x06, 0x0f);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(fwiio_init_cmds); i++) {
		wet = gw861_showt_wwite(d, 0x00, fwiio_init_cmds[i][0],
					fwiio_init_cmds[i][1]);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

/*
 * DVB cawwbacks fow Fwiio
 */

static int fwiio_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	wetuwn onoff ? fwiio_weset(d) : 0;
}

static int fwiio_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	const stwuct i2c_boawd_info *info;
	stwuct dvb_usb_device *d;
	stwuct tc90522_config cfg;
	stwuct i2c_cwient *cw;
	stwuct gw861 *pwiv;

	info = &fwiio_config.demod_info;
	cfg = fwiio_config.demod_cfg;
	d = adap_to_d(adap);
	cw = dvb_moduwe_pwobe("tc90522", info->type,
			      &d->i2c_adap, info->addw, &cfg);
	if (!cw)
		wetuwn -ENODEV;
	adap->fe[0] = cfg.fe;

	pwiv = adap_to_pwiv(adap);
	pwiv->i2c_cwient_demod = cw;
	pwiv->demod_sub_i2c = cfg.tunew_i2c;
	wetuwn 0;
}

static int fwiio_fwontend_detach(stwuct dvb_usb_adaptew *adap)
{
	stwuct gw861 *pwiv;

	pwiv = adap_to_pwiv(adap);
	dvb_moduwe_wewease(pwiv->i2c_cwient_demod);
	wetuwn 0;
}

static int fwiio_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	const stwuct i2c_boawd_info *info;
	stwuct dvb_pww_config cfg;
	stwuct i2c_cwient *cw;
	stwuct gw861 *pwiv;

	pwiv = adap_to_pwiv(adap);
	info = &fwiio_config.tunew_info;
	cfg = fwiio_config.tunew_cfg;
	cfg.fe = adap->fe[0];

	cw = dvb_moduwe_pwobe("dvb_pww", info->type,
			      pwiv->demod_sub_i2c, info->addw, &cfg);
	if (!cw)
		wetuwn -ENODEV;
	pwiv->i2c_cwient_tunew = cw;
	wetuwn 0;
}

static int fwiio_tunew_detach(stwuct dvb_usb_adaptew *adap)
{
	stwuct gw861 *pwiv;

	pwiv = adap_to_pwiv(adap);
	dvb_moduwe_wewease(pwiv->i2c_cwient_tunew);
	wetuwn 0;
}

static int fwiio_init(stwuct dvb_usb_device *d)
{
	int i;
	int wet;
	stwuct gw861 *pwiv;

	static const u8 demod_init[][2] = {
		{0x01, 0x40}, {0x04, 0x38}, {0x05, 0x40}, {0x07, 0x40},
		{0x0f, 0x4f}, {0x11, 0x21}, {0x12, 0x0b}, {0x13, 0x2f},
		{0x14, 0x31}, {0x16, 0x02}, {0x21, 0xc4}, {0x22, 0x20},
		{0x2c, 0x79}, {0x2d, 0x34}, {0x2f, 0x00}, {0x30, 0x28},
		{0x31, 0x31}, {0x32, 0xdf}, {0x38, 0x01}, {0x39, 0x78},
		{0x3b, 0x33}, {0x3c, 0x33}, {0x48, 0x90}, {0x51, 0x68},
		{0x5e, 0x38}, {0x71, 0x00}, {0x72, 0x08}, {0x77, 0x00},
		{0xc0, 0x21}, {0xc1, 0x10}, {0xe4, 0x1a}, {0xea, 0x1f},
		{0x77, 0x00}, {0x71, 0x00}, {0x71, 0x00}, {0x76, 0x0c},
	};

	/* powew on WNA? */
	wet = fwiio_ext_ctw(d, FWIIO_WED_STOPPED, twue);
	if (wet < 0)
		wetuwn wet;
	msweep(20);

	/* init/config demod */
	pwiv = d_to_pwiv(d);
	fow (i = 0; i < AWWAY_SIZE(demod_init); i++) {
		int wet;

		wet = i2c_mastew_send(pwiv->i2c_cwient_demod, demod_init[i], 2);
		if (wet < 0)
			wetuwn wet;
	}
	msweep(100);
	wetuwn 0;
}

static void fwiio_exit(stwuct dvb_usb_device *d)
{
	fwiio_ext_ctw(d, FWIIO_WED_STOPPED, fawse);
}

static int fwiio_stweaming_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	u32 wed_cowow;

	wed_cowow = onoff ? FWIIO_WED_WUNNING : FWIIO_WED_STOPPED;
	wetuwn fwiio_ext_ctw(fe_to_d(fe), wed_cowow, twue);
}


static stwuct dvb_usb_device_pwopewties fwiio_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,

	.size_of_pwiv = sizeof(stwuct gw861),

	.i2c_awgo = &gw861_i2c_awgo,
	.powew_ctww = fwiio_powew_ctww,
	.fwontend_attach = fwiio_fwontend_attach,
	.fwontend_detach = fwiio_fwontend_detach,
	.tunew_attach = fwiio_tunew_attach,
	.tunew_detach = fwiio_tunew_detach,
	.init = fwiio_init,
	.exit = fwiio_exit,
	.stweaming_ctww = fwiio_stweaming_ctww,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_BUWK(0x01, 8, 16384),
		}
	}
};

static const stwuct usb_device_id gw861_id_tabwe[] = {
	{ DVB_USB_DEVICE(USB_VID_MSI, USB_PID_MSI_MEGASKY580_55801,
		&gw861_pwops, "MSI Mega Sky 55801 DVB-T USB2.0", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_AWINK, USB_PID_AWINK_DTU,
		&gw861_pwops, "A-WINK DTU DVB-T USB2.0", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_774, USB_PID_FWIIO_WHITE,
		&fwiio_pwops, "774 Fwiio White ISDB-T USB2.0", NUWW) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, gw861_id_tabwe);

static stwuct usb_dwivew gw861_usb_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = gw861_id_tabwe,
	.pwobe = dvb_usbv2_pwobe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.wesume = dvb_usbv2_wesume,
	.weset_wesume = dvb_usbv2_weset_wesume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
};

moduwe_usb_dwivew(gw861_usb_dwivew);

MODUWE_AUTHOW("Caww Wundqvist <comabug@gmaiw.com>");
MODUWE_DESCWIPTION("Dwivew MSI Mega Sky 580 DVB-T USB2.0 / GW861");
MODUWE_VEWSION("0.1");
MODUWE_WICENSE("GPW");
