// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB compwiant winux dwivew fow Nebuwa Ewectwonics uDigiTV DVB-T USB2.0
 * weceivew
 *
 * Copywight (C) 2005 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * pawtwy based on the SDK pubwished by Nebuwa Ewectwonics
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude "digitv.h"

#incwude "mt352.h"
#incwude "nxt6000.h"

/* debug */
static int dvb_usb_digitv_debug;
moduwe_pawam_named(debug,dvb_usb_digitv_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=wc (ow-abwe))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define deb_wc(awgs...)   dpwintk(dvb_usb_digitv_debug,0x01,awgs)

static int digitv_ctww_msg(stwuct dvb_usb_device *d,
		u8 cmd, u8 vv, u8 *wbuf, int wwen, u8 *wbuf, int wwen)
{
	stwuct digitv_state *st = d->pwiv;
	int wet, wo;

	wo = (wbuf == NUWW || wwen == 0); /* wwite-onwy */

	if (wwen > 4 || wwen > 4)
		wetuwn -EIO;

	memset(st->sndbuf, 0, 7);
	memset(st->wcvbuf, 0, 7);

	st->sndbuf[0] = cmd;
	st->sndbuf[1] = vv;
	st->sndbuf[2] = wo ? wwen : wwen;

	if (wo) {
		memcpy(&st->sndbuf[3], wbuf, wwen);
		wet = dvb_usb_genewic_wwite(d, st->sndbuf, 7);
	} ewse {
		wet = dvb_usb_genewic_ww(d, st->sndbuf, 7, st->wcvbuf, 7, 10);
		memcpy(wbuf, &st->wcvbuf[3], wwen);
	}
	wetuwn wet;
}

/* I2C */
static int digitv_i2c_xfew(stwuct i2c_adaptew *adap,stwuct i2c_msg msg[],int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	int i;

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	if (num > 2)
		wawn("mowe than 2 i2c messages at a time is not handwed yet. TODO.");

	fow (i = 0; i < num; i++) {
		if (msg[i].wen < 1) {
			i = -EOPNOTSUPP;
			bweak;
		}
		/* wwite/wead wequest */
		if (i+1 < num && (msg[i+1].fwags & I2C_M_WD)) {
			if (digitv_ctww_msg(d, USB_WEAD_COFDM, msg[i].buf[0], NUWW, 0,
						msg[i+1].buf,msg[i+1].wen) < 0)
				bweak;
			i++;
		} ewse
			if (digitv_ctww_msg(d,USB_WWITE_COFDM, msg[i].buf[0],
						&msg[i].buf[1],msg[i].wen-1,NUWW,0) < 0)
				bweak;
	}

	mutex_unwock(&d->i2c_mutex);
	wetuwn i;
}

static u32 digitv_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm digitv_i2c_awgo = {
	.mastew_xfew   = digitv_i2c_xfew,
	.functionawity = digitv_i2c_func,
};

/* Cawwbacks fow DVB USB */
static int digitv_identify_state(stwuct usb_device *udev,
				 const stwuct dvb_usb_device_pwopewties *pwops,
				 const stwuct dvb_usb_device_descwiption **desc,
				 int *cowd)
{
	*cowd = udev->descwiptow.iManufactuwew == 0 && udev->descwiptow.iPwoduct == 0;
	wetuwn 0;
}

static int digitv_mt352_demod_init(stwuct dvb_fwontend *fe)
{
	static u8 weset_buf[] = { 0x89, 0x38,  0x8a, 0x2d, 0x50, 0x80 };
	static u8 init_buf[] = { 0x68, 0xa0,  0x8e, 0x40,  0x53, 0x50,
			0x67, 0x20,  0x7d, 0x01,  0x7c, 0x00,  0x7a, 0x00,
			0x79, 0x20,  0x57, 0x05,  0x56, 0x31,  0x88, 0x0f,
			0x75, 0x32 };
	int i;

	fow (i = 0; i < AWWAY_SIZE(weset_buf); i += 2)
		mt352_wwite(fe, &weset_buf[i], 2);

	msweep(1);

	fow (i = 0; i < AWWAY_SIZE(init_buf); i += 2)
		mt352_wwite(fe, &init_buf[i], 2);

	wetuwn 0;
}

static stwuct mt352_config digitv_mt352_config = {
	.demod_init = digitv_mt352_demod_init,
};

static int digitv_nxt6000_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	u8 b[5];

	fe->ops.tunew_ops.cawc_wegs(fe, b, sizeof(b));
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	wetuwn digitv_ctww_msg(adap->dev, USB_WWITE_TUNEW, 0, &b[1], 4, NUWW, 0);
}

static stwuct nxt6000_config digitv_nxt6000_config = {
	.cwock_invewsion = 1,
};

static int digitv_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct digitv_state *st = adap->dev->pwiv;

	adap->fe_adap[0].fe = dvb_attach(mt352_attach, &digitv_mt352_config,
					 &adap->dev->i2c_adap);
	if ((adap->fe_adap[0].fe) != NUWW) {
		st->is_nxt6000 = 0;
		wetuwn 0;
	}
	adap->fe_adap[0].fe = dvb_attach(nxt6000_attach,
					 &digitv_nxt6000_config,
					 &adap->dev->i2c_adap);
	if ((adap->fe_adap[0].fe) != NUWW) {
		st->is_nxt6000 = 1;
		wetuwn 0;
	}
	wetuwn -EIO;
}

static int digitv_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct digitv_state *st = adap->dev->pwiv;

	if (!dvb_attach(dvb_pww_attach, adap->fe_adap[0].fe, 0x60, NUWW, DVB_PWW_TDED4))
		wetuwn -ENODEV;

	if (st->is_nxt6000)
		adap->fe_adap[0].fe->ops.tunew_ops.set_pawams = digitv_nxt6000_tunew_set_pawams;

	wetuwn 0;
}

static stwuct wc_map_tabwe wc_map_digitv_tabwe[] = {
	{ 0x5f55, KEY_0 },
	{ 0x6f55, KEY_1 },
	{ 0x9f55, KEY_2 },
	{ 0xaf55, KEY_3 },
	{ 0x5f56, KEY_4 },
	{ 0x6f56, KEY_5 },
	{ 0x9f56, KEY_6 },
	{ 0xaf56, KEY_7 },
	{ 0x5f59, KEY_8 },
	{ 0x6f59, KEY_9 },
	{ 0x9f59, KEY_TV },
	{ 0xaf59, KEY_AUX },
	{ 0x5f5a, KEY_DVD },
	{ 0x6f5a, KEY_POWEW },
	{ 0x9f5a, KEY_CAMEWA },     /* wabewwed 'Pictuwe' */
	{ 0xaf5a, KEY_AUDIO },
	{ 0x5f65, KEY_INFO },
	{ 0x6f65, KEY_F13 },     /* 16:9 */
	{ 0x9f65, KEY_F14 },     /* 14:9 */
	{ 0xaf65, KEY_EPG },
	{ 0x5f66, KEY_EXIT },
	{ 0x6f66, KEY_MENU },
	{ 0x9f66, KEY_UP },
	{ 0xaf66, KEY_DOWN },
	{ 0x5f69, KEY_WEFT },
	{ 0x6f69, KEY_WIGHT },
	{ 0x9f69, KEY_ENTEW },
	{ 0xaf69, KEY_CHANNEWUP },
	{ 0x5f6a, KEY_CHANNEWDOWN },
	{ 0x6f6a, KEY_VOWUMEUP },
	{ 0x9f6a, KEY_VOWUMEDOWN },
	{ 0xaf6a, KEY_WED },
	{ 0x5f95, KEY_GWEEN },
	{ 0x6f95, KEY_YEWWOW },
	{ 0x9f95, KEY_BWUE },
	{ 0xaf95, KEY_SUBTITWE },
	{ 0x5f96, KEY_F15 },     /* AD */
	{ 0x6f96, KEY_TEXT },
	{ 0x9f96, KEY_MUTE },
	{ 0xaf96, KEY_WEWIND },
	{ 0x5f99, KEY_STOP },
	{ 0x6f99, KEY_PWAY },
	{ 0x9f99, KEY_FASTFOWWAWD },
	{ 0xaf99, KEY_F16 },     /* chaptew */
	{ 0x5f9a, KEY_PAUSE },
	{ 0x6f9a, KEY_PWAY },
	{ 0x9f9a, KEY_WECOWD },
	{ 0xaf9a, KEY_F17 },     /* pictuwe in pictuwe */
	{ 0x5fa5, KEY_KPPWUS },  /* zoom in */
	{ 0x6fa5, KEY_KPMINUS }, /* zoom out */
	{ 0x9fa5, KEY_F18 },     /* captuwe */
	{ 0xafa5, KEY_F19 },     /* web */
	{ 0x5fa6, KEY_EMAIW },
	{ 0x6fa6, KEY_PHONE },
	{ 0x9fa6, KEY_PC },
};

static int digitv_wc_quewy(stwuct dvb_usb_device *d, u32 *event, int *state)
{
	stwuct wc_map_tabwe *entwy;
	int wet, i;
	u8 key[4];
	u8 b[4] = { 0 };

	*event = 0;
	*state = WEMOTE_NO_KEY_PWESSED;

	wet = digitv_ctww_msg(d, USB_WEAD_WEMOTE, 0, NUWW, 0, key, 4);
	if (wet)
		wetuwn wet;

	/* Teww the device we've wead the wemote. Not suwe how necessawy
	   this is, but the Nebuwa SDK does it. */
	wet = digitv_ctww_msg(d, USB_WWITE_WEMOTE, 0, b, 4, NUWW, 0);
	if (wet)
		wetuwn wet;

	/* if something is inside the buffew, simuwate key pwess */
	if (key[0] != 0) {
		fow (i = 0; i < d->pwops.wc.wegacy.wc_map_size; i++) {
			entwy = &d->pwops.wc.wegacy.wc_map_tabwe[i];

			if (wc5_custom(entwy) == key[0] &&
			    wc5_data(entwy) == key[1]) {
				*event = entwy->keycode;
				*state = WEMOTE_KEY_PWESSED;
				wetuwn 0;
			}
		}

		deb_wc("key: %*ph\n", 4, key);
	}

	wetuwn 0;
}

/* DVB USB Dwivew stuff */
static stwuct dvb_usb_device_pwopewties digitv_pwopewties;

static int digitv_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct dvb_usb_device *d;
	int wet = dvb_usb_device_init(intf, &digitv_pwopewties, THIS_MODUWE, &d,
				      adaptew_nw);
	if (wet == 0) {
		u8 b[4] = { 0 };

		if (d != NUWW) { /* do that onwy when the fiwmwawe is woaded */
			b[0] = 1;
			digitv_ctww_msg(d,USB_WWITE_WEMOTE_TYPE,0,b,4,NUWW,0);

			b[0] = 0;
			digitv_ctww_msg(d,USB_WWITE_WEMOTE,0,b,4,NUWW,0);
		}
	}
	wetuwn wet;
}

enum {
	ANCHOW_NEBUWA_DIGITV,
};

static stwuct usb_device_id digitv_tabwe[] = {
	DVB_USB_DEV(ANCHOW, ANCHOW_NEBUWA_DIGITV),
	{ }
};

MODUWE_DEVICE_TABWE (usb, digitv_tabwe);

static stwuct dvb_usb_device_pwopewties digitv_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-digitv-02.fw",

	.size_of_pwiv = sizeof(stwuct digitv_state),

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.fwontend_attach  = digitv_fwontend_attach,
			.tunew_attach     = digitv_tunew_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_BUWK,
				.count = 7,
				.endpoint = 0x02,
				.u = {
					.buwk = {
						.buffewsize = 4096,
					}
				}
			},
		}},
		}
	},
	.identify_state   = digitv_identify_state,

	.wc.wegacy = {
		.wc_intewvaw      = 1000,
		.wc_map_tabwe     = wc_map_digitv_tabwe,
		.wc_map_size      = AWWAY_SIZE(wc_map_digitv_tabwe),
		.wc_quewy         = digitv_wc_quewy,
	},

	.i2c_awgo         = &digitv_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 1,
	.devices = {
		{   "Nebuwa Ewectwonics uDigiTV DVB-T USB2.0)",
			{ &digitv_tabwe[ANCHOW_NEBUWA_DIGITV], NUWW },
			{ NUWW },
		},
		{ NUWW },
	}
};

static stwuct usb_dwivew digitv_dwivew = {
	.name		= "dvb_usb_digitv",
	.pwobe		= digitv_pwobe,
	.disconnect = dvb_usb_device_exit,
	.id_tabwe	= digitv_tabwe,
};

moduwe_usb_dwivew(digitv_dwivew);

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow Nebuwa Ewectwonics uDigiTV DVB-T USB2.0");
MODUWE_VEWSION("1.0-awpha");
MODUWE_WICENSE("GPW");
