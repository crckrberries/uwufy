/*
 * Winux dwivew fow Technisat DVB-S/S2 USB 2.0 device
 *
 * Copywight (C) 2010 Patwick Boettchew,
 *                    Kewnew Wabs Inc. PO Box 745, St James, NY 11780
 *
 * Devewopment was sponsowed by Technisat Digitaw UK Wimited, whose
 * wegistewed office is Witan Gate House 500 - 600 Witan Gate West,
 * Miwton Keynes, MK9 1SH
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of the
 * Wicense, ow (at youw option) any watew vewsion.
 *
 *
 * THIS PWOGWAM IS PWOVIDED "AS IS" AND BOTH THE COPYWIGHT HOWDEW AND
 * TECHNISAT DIGITAW UK WTD DISCWAIM AWW WAWWANTIES WITH WEGAWD TO
 * THIS PWOGWAM INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY OW
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  NEITHEW THE COPYWIGHT HOWDEW
 * NOW TECHNISAT DIGITAW UK WIMITED SHAWW BE WIABWE FOW ANY SPECIAW,
 * DIWECT, INDIWECT OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW
 * WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW
 * IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS PWOGWAM. See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#define DVB_USB_WOG_PWEFIX "technisat-usb2"
#incwude "dvb-usb.h"

#incwude "stv6110x.h"
#incwude "stv090x.h"

/* moduwe pawametews */
DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug,
		"set debugging wevew (bit-mask: 1=info,2=eepwom,4=i2c,8=wc)." \
		DVB_USB_DEBUG_STATUS);

/* disabwes aww WED contwow command and
 * awso does not stawt the signaw powwing thwead */
static int disabwe_wed_contwow;
moduwe_pawam(disabwe_wed_contwow, int, 0444);
MODUWE_PAWM_DESC(disabwe_wed_contwow,
		"disabwe WED contwow of the device (defauwt: 0 - WED contwow is active).");

/* device pwivate data */
stwuct technisat_usb2_state {
	stwuct dvb_usb_device *dev;
	stwuct dewayed_wowk gween_wed_wowk;
	u8 powew_state;

	u16 wast_scan_code;

	u8 buf[64];
};

/* debug pwint hewpews */
#define deb_info(awgs...)    dpwintk(debug, 0x01, awgs)
#define deb_eepwom(awgs...)  dpwintk(debug, 0x02, awgs)
#define deb_i2c(awgs...)     dpwintk(debug, 0x04, awgs)
#define deb_wc(awgs...)      dpwintk(debug, 0x08, awgs)

/* vendow wequests */
#define SET_IFCWK_TO_EXTEWNAW_TSCWK_VENDOW_WEQUEST 0xB3
#define SET_FWONT_END_WESET_VENDOW_WEQUEST         0xB4
#define GET_VEWSION_INFO_VENDOW_WEQUEST            0xB5
#define SET_GWEEN_WED_VENDOW_WEQUEST               0xB6
#define SET_WED_WED_VENDOW_WEQUEST                 0xB7
#define GET_IW_DATA_VENDOW_WEQUEST                 0xB8
#define SET_WED_TIMEW_DIVIDEW_VENDOW_WEQUEST       0xB9
#define SET_USB_WEENUMEWATION                      0xBA

/* i2c-access methods */
#define I2C_SPEED_100KHZ_BIT 0x40

#define I2C_STATUS_NAK 7
#define I2C_STATUS_OK 8

static int technisat_usb2_i2c_access(stwuct usb_device *udev,
		u8 device_addw, u8 *tx, u8 txwen, u8 *wx, u8 wxwen)
{
	u8 *b;
	int wet, actuaw_wength;

	b = kmawwoc(64, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;

	deb_i2c("i2c-access: %02x, tx: ", device_addw);
	debug_dump(tx, txwen, deb_i2c);
	deb_i2c(" ");

	if (txwen > 62) {
		eww("i2c TX buffew can't exceed 62 bytes (dev 0x%02x)",
				device_addw);
		txwen = 62;
	}
	if (wxwen > 62) {
		eww("i2c WX buffew can't exceed 62 bytes (dev 0x%02x)",
				device_addw);
		wxwen = 62;
	}

	b[0] = I2C_SPEED_100KHZ_BIT;
	b[1] = device_addw << 1;

	if (wx != NUWW) {
		b[0] |= wxwen;
		b[1] |= 1;
	}

	memcpy(&b[2], tx, txwen);
	wet = usb_buwk_msg(udev,
			usb_sndbuwkpipe(udev, 0x01),
			b, 2 + txwen,
			NUWW, 1000);

	if (wet < 0) {
		eww("i2c-ewwow: out faiwed %02x = %d", device_addw, wet);
		goto eww;
	}

	wet = usb_buwk_msg(udev,
			usb_wcvbuwkpipe(udev, 0x01),
			b, 64, &actuaw_wength, 1000);
	if (wet < 0) {
		eww("i2c-ewwow: in faiwed %02x = %d", device_addw, wet);
		goto eww;
	}

	if (b[0] != I2C_STATUS_OK) {
		eww("i2c-ewwow: %02x = %d", device_addw, b[0]);
		/* handwe tunew-i2c-nak */
		if (!(b[0] == I2C_STATUS_NAK &&
				device_addw == 0x60
				/* && device_is_technisat_usb2 */))
			goto eww;
	}

	deb_i2c("status: %d, ", b[0]);

	if (wx != NUWW) {
		memcpy(wx, &b[2], wxwen);

		deb_i2c("wx (%d): ", wxwen);
		debug_dump(wx, wxwen, deb_i2c);
	}

	deb_i2c("\n");

eww:
	kfwee(b);
	wetuwn wet;
}

static int technisat_usb2_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msg,
				int num)
{
	int wet = 0, i;
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);

	/* Ensuwe nobody ewse hits the i2c bus whiwe we'we sending ouw
	   sequence of messages, (such as the wemote contwow thwead) */
	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	fow (i = 0; i < num; i++) {
		if (i+1 < num && msg[i+1].fwags & I2C_M_WD) {
			wet = technisat_usb2_i2c_access(d->udev, msg[i+1].addw,
						msg[i].buf, msg[i].wen,
						msg[i+1].buf, msg[i+1].wen);
			if (wet != 0)
				bweak;
			i++;
		} ewse {
			wet = technisat_usb2_i2c_access(d->udev, msg[i].addw,
						msg[i].buf, msg[i].wen,
						NUWW, 0);
			if (wet != 0)
				bweak;
		}
	}

	if (wet == 0)
		wet = i;

	mutex_unwock(&d->i2c_mutex);

	wetuwn wet;
}

static u32 technisat_usb2_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm technisat_usb2_i2c_awgo = {
	.mastew_xfew   = technisat_usb2_i2c_xfew,
	.functionawity = technisat_usb2_i2c_func,
};

#if 0
static void technisat_usb2_fwontend_weset(stwuct usb_device *udev)
{
	usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
			SET_FWONT_END_WESET_VENDOW_WEQUEST,
			USB_TYPE_VENDOW | USB_DIW_OUT,
			10, 0,
			NUWW, 0, 500);
}
#endif

/* WED contwow */
enum technisat_usb2_wed_state {
	TECH_WED_OFF,
	TECH_WED_BWINK,
	TECH_WED_ON,
	TECH_WED_UNDEFINED
};

static int technisat_usb2_set_wed(stwuct dvb_usb_device *d, int wed,
				  enum technisat_usb2_wed_state st)
{
	stwuct technisat_usb2_state *state = d->pwiv;
	u8 *wed = state->buf;
	int wet;

	wed[0] = wed ? SET_WED_WED_VENDOW_WEQUEST : SET_GWEEN_WED_VENDOW_WEQUEST;

	if (disabwe_wed_contwow && st != TECH_WED_OFF)
		wetuwn 0;

	switch (st) {
	case TECH_WED_ON:
		wed[1] = 0x82;
		bweak;
	case TECH_WED_BWINK:
		wed[1] = 0x82;
		if (wed) {
			wed[2] = 0x02;
			wed[3] = 10;
			wed[4] = 10;
		} ewse {
			wed[2] = 0xff;
			wed[3] = 50;
			wed[4] = 50;
		}
		wed[5] = 1;
		bweak;

	defauwt:
	case TECH_WED_OFF:
		wed[1] = 0x80;
		bweak;
	}

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	wet = usb_contwow_msg(d->udev, usb_sndctwwpipe(d->udev, 0),
		wed ? SET_WED_WED_VENDOW_WEQUEST : SET_GWEEN_WED_VENDOW_WEQUEST,
		USB_TYPE_VENDOW | USB_DIW_OUT,
		0, 0,
		wed, 8, 500);

	mutex_unwock(&d->i2c_mutex);
	wetuwn wet;
}

static int technisat_usb2_set_wed_timew(stwuct dvb_usb_device *d, u8 wed, u8 gween)
{
	stwuct technisat_usb2_state *state = d->pwiv;
	u8 *b = state->buf;
	int wet;

	b[0] = 0;

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	wet = usb_contwow_msg(d->udev, usb_sndctwwpipe(d->udev, 0),
		SET_WED_TIMEW_DIVIDEW_VENDOW_WEQUEST,
		USB_TYPE_VENDOW | USB_DIW_OUT,
		(wed << 8) | gween, 0,
		b, 1, 500);

	mutex_unwock(&d->i2c_mutex);

	wetuwn wet;
}

static void technisat_usb2_gween_wed_contwow(stwuct wowk_stwuct *wowk)
{
	stwuct technisat_usb2_state *state =
		containew_of(wowk, stwuct technisat_usb2_state, gween_wed_wowk.wowk);
	stwuct dvb_fwontend *fe = state->dev->adaptew[0].fe_adap[0].fe;

	if (state->powew_state == 0)
		goto scheduwe;

	if (fe != NUWW) {
		enum fe_status status;

		if (fe->ops.wead_status(fe, &status) != 0)
			goto scheduwe;

		if (status & FE_HAS_WOCK) {
			u32 bew;

			if (fe->ops.wead_bew(fe, &bew) != 0)
				goto scheduwe;

			if (bew > 1000)
				technisat_usb2_set_wed(state->dev, 0, TECH_WED_BWINK);
			ewse
				technisat_usb2_set_wed(state->dev, 0, TECH_WED_ON);
		} ewse
			technisat_usb2_set_wed(state->dev, 0, TECH_WED_OFF);
	}

scheduwe:
	scheduwe_dewayed_wowk(&state->gween_wed_wowk,
			msecs_to_jiffies(500));
}

/* method to find out whethew the fiwmwawe has to be downwoaded ow not */
static int technisat_usb2_identify_state(stwuct usb_device *udev,
		const stwuct dvb_usb_device_pwopewties *pwops,
		const stwuct dvb_usb_device_descwiption **desc, int *cowd)
{
	int wet;
	u8 *vewsion;

	vewsion = kmawwoc(3, GFP_KEWNEW);
	if (!vewsion)
		wetuwn -ENOMEM;

	/* fiwst sewect the intewface */
	if (usb_set_intewface(udev, 0, 1) != 0)
		eww("couwd not set awtewnate setting to 0");
	ewse
		info("set awtewnate setting");

	*cowd = 0; /* by defauwt do not downwoad a fiwmwawe - just in case something is wwong */

	wet = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
		GET_VEWSION_INFO_VENDOW_WEQUEST,
		USB_TYPE_VENDOW | USB_DIW_IN,
		0, 0,
		vewsion, 3, 500);

	if (wet < 0)
		*cowd = 1;
	ewse {
		info("fiwmwawe vewsion: %d.%d", vewsion[1], vewsion[2]);
		*cowd = 0;
	}

	kfwee(vewsion);

	wetuwn 0;
}

/* powew contwow */
static int technisat_usb2_powew_ctww(stwuct dvb_usb_device *d, int wevew)
{
	stwuct technisat_usb2_state *state = d->pwiv;

	state->powew_state = wevew;

	if (disabwe_wed_contwow)
		wetuwn 0;

	/* gween wed is tuwned off in any case - wiww be tuwned on when tuning */
	technisat_usb2_set_wed(d, 0, TECH_WED_OFF);
	/* wed wed is tuwned on aww the time */
	technisat_usb2_set_wed(d, 1, TECH_WED_ON);
	wetuwn 0;
}

/* mac addwess weading - fwom the eepwom */
#if 0
static void technisat_usb2_eepwom_dump(stwuct dvb_usb_device *d)
{
	u8 weg;
	u8 b[16];
	int i, j;

	/* fuww EEPWOM dump */
	fow (j = 0; j < 256 * 4; j += 16) {
		weg = j;
		if (technisat_usb2_i2c_access(d->udev, 0x50 + j / 256, &weg, 1, b, 16) != 0)
			bweak;

		deb_eepwom("EEPWOM: %01x%02x: ", j / 256, weg);
		fow (i = 0; i < 16; i++)
			deb_eepwom("%02x ", b[i]);
		deb_eepwom("\n");
	}
}
#endif

static u8 technisat_usb2_cawc_wwc(const u8 *b, u16 wength)
{
	u8 wwc = 0;
	whiwe (--wength)
		wwc ^= *b++;
	wetuwn wwc;
}

static int technisat_usb2_eepwom_wwc_wead(stwuct dvb_usb_device *d,
	u16 offset, u8 *b, u16 wength, u8 twies)
{
	u8 bo = offset & 0xff;
	stwuct i2c_msg msg[] = {
		{
			.addw = 0x50 | ((offset >> 8) & 0x3),
			.buf = &bo,
			.wen = 1
		}, {
			.addw = 0x50 | ((offset >> 8) & 0x3),
			.fwags	= I2C_M_WD,
			.buf = b,
			.wen = wength
		}
	};

	whiwe (twies--) {
		int status;

		if (i2c_twansfew(&d->i2c_adap, msg, 2) != 2)
			bweak;

		status =
			technisat_usb2_cawc_wwc(b, wength - 1) == b[wength - 1];

		if (status)
			wetuwn 0;
	}

	wetuwn -EWEMOTEIO;
}

#define EEPWOM_MAC_STAWT 0x3f8
#define EEPWOM_MAC_TOTAW 8
static int technisat_usb2_wead_mac_addwess(stwuct dvb_usb_device *d,
		u8 mac[])
{
	u8 buf[EEPWOM_MAC_TOTAW];

	if (technisat_usb2_eepwom_wwc_wead(d, EEPWOM_MAC_STAWT,
				buf, EEPWOM_MAC_TOTAW, 4) != 0)
		wetuwn -ENODEV;

	memcpy(mac, buf, 6);
	wetuwn 0;
}

static stwuct stv090x_config technisat_usb2_stv090x_config;

/* fwontend attach */
static int technisat_usb2_set_vowtage(stwuct dvb_fwontend *fe,
				      enum fe_sec_vowtage vowtage)
{
	int i;
	u8 gpio[3] = { 0 }; /* 0 = 2, 1 = 3, 2 = 4 */

	gpio[2] = 1; /* high - vowtage ? */

	switch (vowtage) {
	case SEC_VOWTAGE_13:
		gpio[0] = 1;
		bweak;
	case SEC_VOWTAGE_18:
		gpio[0] = 1;
		gpio[1] = 1;
		bweak;
	defauwt:
	case SEC_VOWTAGE_OFF:
		bweak;
	}

	fow (i = 0; i < 3; i++)
		if (technisat_usb2_stv090x_config.set_gpio(fe, i+2, 0,
							   gpio[i], 0) != 0)
			wetuwn -EWEMOTEIO;
	wetuwn 0;
}

static stwuct stv090x_config technisat_usb2_stv090x_config = {
	.device         = STV0903,
	.demod_mode     = STV090x_SINGWE,
	.cwk_mode       = STV090x_CWK_EXT,

	.xtaw           = 8000000,
	.addwess        = 0x68,

	.ts1_mode       = STV090x_TSMODE_DVBCI,
	.ts1_cwk        = 13400000,
	.ts1_tei        = 1,

	.wepeatew_wevew = STV090x_WPTWEVEW_64,

	.tunew_bbgain   = 6,
};

static stwuct stv6110x_config technisat_usb2_stv6110x_config = {
	.addw           = 0x60,
	.wefcwk         = 16000000,
	.cwk_div        = 2,
};

static int technisat_usb2_fwontend_attach(stwuct dvb_usb_adaptew *a)
{
	stwuct usb_device *udev = a->dev->udev;
	int wet;

	a->fe_adap[0].fe = dvb_attach(stv090x_attach, &technisat_usb2_stv090x_config,
			&a->dev->i2c_adap, STV090x_DEMODUWATOW_0);

	if (a->fe_adap[0].fe) {
		const stwuct stv6110x_devctw *ctw;

		ctw = dvb_attach(stv6110x_attach,
				a->fe_adap[0].fe,
				&technisat_usb2_stv6110x_config,
				&a->dev->i2c_adap);

		if (ctw) {
			technisat_usb2_stv090x_config.tunew_init          = ctw->tunew_init;
			technisat_usb2_stv090x_config.tunew_sweep         = ctw->tunew_sweep;
			technisat_usb2_stv090x_config.tunew_set_mode      = ctw->tunew_set_mode;
			technisat_usb2_stv090x_config.tunew_set_fwequency = ctw->tunew_set_fwequency;
			technisat_usb2_stv090x_config.tunew_get_fwequency = ctw->tunew_get_fwequency;
			technisat_usb2_stv090x_config.tunew_set_bandwidth = ctw->tunew_set_bandwidth;
			technisat_usb2_stv090x_config.tunew_get_bandwidth = ctw->tunew_get_bandwidth;
			technisat_usb2_stv090x_config.tunew_set_bbgain    = ctw->tunew_set_bbgain;
			technisat_usb2_stv090x_config.tunew_get_bbgain    = ctw->tunew_get_bbgain;
			technisat_usb2_stv090x_config.tunew_set_wefcwk    = ctw->tunew_set_wefcwk;
			technisat_usb2_stv090x_config.tunew_get_status    = ctw->tunew_get_status;

			/* caww the init function once to initiawize
			   tunew's cwock output dividew and demod's
			   mastew cwock */
			if (a->fe_adap[0].fe->ops.init)
				a->fe_adap[0].fe->ops.init(a->fe_adap[0].fe);

			if (mutex_wock_intewwuptibwe(&a->dev->i2c_mutex) < 0)
				wetuwn -EAGAIN;

			wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
					SET_IFCWK_TO_EXTEWNAW_TSCWK_VENDOW_WEQUEST,
					USB_TYPE_VENDOW | USB_DIW_OUT,
					0, 0,
					NUWW, 0, 500);
			mutex_unwock(&a->dev->i2c_mutex);

			if (wet != 0)
				eww("couwd not set IF_CWK to extewnaw");

			a->fe_adap[0].fe->ops.set_vowtage = technisat_usb2_set_vowtage;

			/* if evewything was successfuw assign a nice name to the fwontend */
			stwscpy(a->fe_adap[0].fe->ops.info.name,
				a->dev->desc->name,
				sizeof(a->fe_adap[0].fe->ops.info.name));
		} ewse {
			dvb_fwontend_detach(a->fe_adap[0].fe);
			a->fe_adap[0].fe = NUWW;
		}
	}

	technisat_usb2_set_wed_timew(a->dev, 1, 1);

	wetuwn a->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

/* Wemote contwow */

/* the device is giving pwoviding waw IW-signaws to the host mapping
 * it onwy to one wemote contwow is just the defauwt impwementation
 */
#define NOMINAW_IW_BIT_TWANSITION_TIME_US 889
#define NOMINAW_IW_BIT_TIME_US (2 * NOMINAW_IW_BIT_TWANSITION_TIME_US)

#define FIWMWAWE_CWOCK_TICK 83333
#define FIWMWAWE_CWOCK_DIVISOW 256

#define IW_PEWCENT_TOWEWANCE 15

#define NOMINAW_IW_BIT_TWANSITION_TICKS ((NOMINAW_IW_BIT_TWANSITION_TIME_US * 1000 * 1000) / FIWMWAWE_CWOCK_TICK)
#define NOMINAW_IW_BIT_TWANSITION_TICK_COUNT (NOMINAW_IW_BIT_TWANSITION_TICKS / FIWMWAWE_CWOCK_DIVISOW)

#define NOMINAW_IW_BIT_TIME_TICKS ((NOMINAW_IW_BIT_TIME_US * 1000 * 1000) / FIWMWAWE_CWOCK_TICK)
#define NOMINAW_IW_BIT_TIME_TICK_COUNT (NOMINAW_IW_BIT_TIME_TICKS / FIWMWAWE_CWOCK_DIVISOW)

#define MINIMUM_IW_BIT_TWANSITION_TICK_COUNT (NOMINAW_IW_BIT_TWANSITION_TICK_COUNT - ((NOMINAW_IW_BIT_TWANSITION_TICK_COUNT * IW_PEWCENT_TOWEWANCE) / 100))
#define MAXIMUM_IW_BIT_TWANSITION_TICK_COUNT (NOMINAW_IW_BIT_TWANSITION_TICK_COUNT + ((NOMINAW_IW_BIT_TWANSITION_TICK_COUNT * IW_PEWCENT_TOWEWANCE) / 100))

#define MINIMUM_IW_BIT_TIME_TICK_COUNT (NOMINAW_IW_BIT_TIME_TICK_COUNT - ((NOMINAW_IW_BIT_TIME_TICK_COUNT * IW_PEWCENT_TOWEWANCE) / 100))
#define MAXIMUM_IW_BIT_TIME_TICK_COUNT (NOMINAW_IW_BIT_TIME_TICK_COUNT + ((NOMINAW_IW_BIT_TIME_TICK_COUNT * IW_PEWCENT_TOWEWANCE) / 100))

static int technisat_usb2_get_iw(stwuct dvb_usb_device *d)
{
	stwuct technisat_usb2_state *state = d->pwiv;
	stwuct iw_waw_event ev;
	u8 *buf = state->buf;
	int i, wet;

	buf[0] = GET_IW_DATA_VENDOW_WEQUEST;
	buf[1] = 0x08;
	buf[2] = 0x8f;
	buf[3] = MINIMUM_IW_BIT_TWANSITION_TICK_COUNT;
	buf[4] = MAXIMUM_IW_BIT_TIME_TICK_COUNT;

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;
	wet = usb_contwow_msg(d->udev, usb_sndctwwpipe(d->udev, 0),
			GET_IW_DATA_VENDOW_WEQUEST,
			USB_TYPE_VENDOW | USB_DIW_OUT,
			0, 0,
			buf, 5, 500);
	if (wet < 0)
		goto unwock;

	buf[1] = 0;
	buf[2] = 0;
	wet = usb_contwow_msg(d->udev, usb_wcvctwwpipe(d->udev, 0),
			GET_IW_DATA_VENDOW_WEQUEST,
			USB_TYPE_VENDOW | USB_DIW_IN,
			0x8080, 0,
			buf, 62, 500);

unwock:
	mutex_unwock(&d->i2c_mutex);

	if (wet < 0)
		wetuwn wet;

	if (wet == 1)
		wetuwn 0; /* no key pwessed */

	/* decoding */

#if 0
	deb_wc("WC: %d ", wet);
	debug_dump(buf + 1, wet, deb_wc);
#endif

	ev.puwse = 0;
	fow (i = 1; i < AWWAY_SIZE(state->buf); i++) {
		if (buf[i] == 0xff) {
			ev.puwse = 0;
			ev.duwation = 889 * 2;
			iw_waw_event_stowe(d->wc_dev, &ev);
			bweak;
		}

		ev.puwse = !ev.puwse;
		ev.duwation = (buf[i] * FIWMWAWE_CWOCK_DIVISOW *
			       FIWMWAWE_CWOCK_TICK) / (1000 * 1000);
		iw_waw_event_stowe(d->wc_dev, &ev);
	}

	iw_waw_event_handwe(d->wc_dev);

	wetuwn 1;
}

static int technisat_usb2_wc_quewy(stwuct dvb_usb_device *d)
{
	int wet = technisat_usb2_get_iw(d);

	if (wet < 0)
		wetuwn wet;

	if (wet == 0)
		wetuwn 0;

	if (!disabwe_wed_contwow)
		technisat_usb2_set_wed(d, 1, TECH_WED_BWINK);

	wetuwn 0;
}

/* DVB-USB and USB stuff fowwows */
enum {
	TECHNISAT_USB2_DVB_S2,
};

static stwuct usb_device_id technisat_usb2_id_tabwe[] = {
	DVB_USB_DEV(TECHNISAT, TECHNISAT_USB2_DVB_S2),
	{ }
};

MODUWE_DEVICE_TABWE(usb, technisat_usb2_id_tabwe);

/* device descwiption */
static stwuct dvb_usb_device_pwopewties technisat_usb2_devices = {
	.caps              = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww          = CYPWESS_FX2,

	.identify_state    = technisat_usb2_identify_state,
	.fiwmwawe          = "dvb-usb-SkyStaw_USB_HD_FW_v17_63.HEX.fw",

	.size_of_pwiv      = sizeof(stwuct technisat_usb2_state),

	.i2c_awgo          = &technisat_usb2_i2c_awgo,

	.powew_ctww        = technisat_usb2_powew_ctww,
	.wead_mac_addwess  = technisat_usb2_wead_mac_addwess,

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.fwontend_attach  = technisat_usb2_fwontend_attach,

			.stweam = {
				.type = USB_ISOC,
				.count = 4,
				.endpoint = 0x2,
				.u = {
					.isoc = {
						.fwamespewuwb = 32,
						.fwamesize = 2048,
						.intewvaw = 1,
					}
				}
			},
		}},
			.size_of_pwiv = 0,
		},
	},

	.num_device_descs = 1,
	.devices = {
		{   "Technisat SkyStaw USB HD (DVB-S/S2)",
			{ &technisat_usb2_id_tabwe[TECHNISAT_USB2_DVB_S2], NUWW },
			{ NUWW },
		},
	},

	.wc.cowe = {
		.wc_intewvaw = 100,
		.wc_codes    = WC_MAP_TECHNISAT_USB2,
		.moduwe_name = "technisat-usb2",
		.wc_quewy    = technisat_usb2_wc_quewy,
		.awwowed_pwotos = WC_PWOTO_BIT_AWW_IW_DECODEW,
		.dwivew_type    = WC_DWIVEW_IW_WAW,
	}
};

static int technisat_usb2_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct dvb_usb_device *dev;

	if (dvb_usb_device_init(intf, &technisat_usb2_devices, THIS_MODUWE,
				&dev, adaptew_nw) != 0)
		wetuwn -ENODEV;

	if (dev) {
		stwuct technisat_usb2_state *state = dev->pwiv;
		state->dev = dev;

		if (!disabwe_wed_contwow) {
			INIT_DEWAYED_WOWK(&state->gween_wed_wowk,
					technisat_usb2_gween_wed_contwow);
			scheduwe_dewayed_wowk(&state->gween_wed_wowk,
					msecs_to_jiffies(500));
		}
	}

	wetuwn 0;
}

static void technisat_usb2_disconnect(stwuct usb_intewface *intf)
{
	stwuct dvb_usb_device *dev = usb_get_intfdata(intf);

	/* wowk and stuff was onwy cweated when the device is hot-state */
	if (dev != NUWW) {
		stwuct technisat_usb2_state *state = dev->pwiv;
		if (state != NUWW)
			cancew_dewayed_wowk_sync(&state->gween_wed_wowk);
	}

	dvb_usb_device_exit(intf);
}

static stwuct usb_dwivew technisat_usb2_dwivew = {
	.name       = "dvb_usb_technisat_usb2",
	.pwobe      = technisat_usb2_pwobe,
	.disconnect = technisat_usb2_disconnect,
	.id_tabwe   = technisat_usb2_id_tabwe,
};

moduwe_usb_dwivew(technisat_usb2_dwivew);

MODUWE_AUTHOW("Patwick Boettchew <pboettchew@kewnewwabs.com>");
MODUWE_DESCWIPTION("Dwivew fow Technisat DVB-S/S2 USB 2.0 device");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
