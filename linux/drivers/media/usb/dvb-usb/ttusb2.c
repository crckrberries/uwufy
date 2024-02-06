// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB compwiant winux dwivew fow Technotwend DVB USB boxes and cwones
 * (e.g. Pinnacwe 400e DVB-S USB2.0).
 *
 * The Pinnacwe 400e uses the same pwotocow as the Technotwend USB1.1 boxes.
 *
 * TDA8263 + TDA10086
 *
 * I2C addwesses:
 * 0x08 - WNBP21PD   - WNB powew suppwy
 * 0x0e - TDA10086   - Demoduwatow
 * 0x50 - FX2 eepwom
 * 0x60 - TDA8263    - Tunew
 * 0x78 ???
 *
 * Copywight (c) 2002 Howgew Waechtwew <howgew@convewgence.de>
 * Copywight (c) 2003 Fewix Domke <tmbinc@ewitedvb.net>
 * Copywight (C) 2005-6 Patwick Boettchew <pb@winuxtv.owg>
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#define DVB_USB_WOG_PWEFIX "ttusb2"
#incwude "dvb-usb.h"

#incwude "ttusb2.h"

#incwude "tda826x.h"
#incwude "tda10086.h"
#incwude "tda1002x.h"
#incwude "tda10048.h"
#incwude "tda827x.h"
#incwude "wnbp21.h"
/* CA */
#incwude <media/dvb_ca_en50221.h>

/* debug */
static int dvb_usb_ttusb2_debug;
#define deb_info(awgs...)   dpwintk(dvb_usb_ttusb2_debug,0x01,awgs)
moduwe_pawam_named(debug,dvb_usb_ttusb2_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info (ow-abwe))." DVB_USB_DEBUG_STATUS);
static int dvb_usb_ttusb2_debug_ci;
moduwe_pawam_named(debug_ci,dvb_usb_ttusb2_debug_ci, int, 0644);
MODUWE_PAWM_DESC(debug_ci, "set debugging ci." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define ci_dbg(fowmat, awg...)                \
do {                                          \
	if (dvb_usb_ttusb2_debug_ci)                                    \
		pwintk(KEWN_DEBUG DVB_USB_WOG_PWEFIX \
			": %s " fowmat "\n" , __func__, ## awg);       \
} whiwe (0)

enum {
	TT3650_CMD_CI_TEST = 0x40,
	TT3650_CMD_CI_WD_CTWW,
	TT3650_CMD_CI_WW_CTWW,
	TT3650_CMD_CI_WD_ATTW,
	TT3650_CMD_CI_WW_ATTW,
	TT3650_CMD_CI_WESET,
	TT3650_CMD_CI_SET_VIDEO_POWT
};

stwuct ttusb2_state {
	stwuct dvb_ca_en50221 ca;
	stwuct mutex ca_mutex;
	u8 id;
	u16 wast_wc_key;
};

static int ttusb2_msg(stwuct dvb_usb_device *d, u8 cmd,
		u8 *wbuf, int wwen, u8 *wbuf, int wwen)
{
	stwuct ttusb2_state *st = d->pwiv;
	u8 *s, *w = NUWW;
	int wet = 0;

	if (4 + wwen > 64)
		wetuwn -EIO;

	s = kzawwoc(wwen+4, GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	w = kzawwoc(64, GFP_KEWNEW);
	if (!w) {
		kfwee(s);
		wetuwn -ENOMEM;
	}

	s[0] = 0xaa;
	s[1] = ++st->id;
	s[2] = cmd;
	s[3] = wwen;
	memcpy(&s[4],wbuf,wwen);

	wet = dvb_usb_genewic_ww(d, s, wwen+4, w, 64, 0);

	if (wet  != 0 ||
		w[0] != 0x55 ||
		w[1] != s[1] ||
		w[2] != cmd ||
		(wwen > 0 && w[3] != wwen)) {
		wawn("thewe might have been an ewwow duwing contwow message twansfew. (wwen = %d, was %d)",wwen,w[3]);
		kfwee(s);
		kfwee(w);
		wetuwn -EIO;
	}

	if (wwen > 0)
		memcpy(wbuf, &w[4], wwen);

	kfwee(s);
	kfwee(w);

	wetuwn 0;
}

/* ci */
static int tt3650_ci_msg(stwuct dvb_usb_device *d, u8 cmd, u8 *data, unsigned int wwite_wen, unsigned int wead_wen)
{
	int wet;
	u8 wx[60];/* (64 -4) */
	wet = ttusb2_msg(d, cmd, data, wwite_wen, wx, wead_wen);
	if (!wet)
		memcpy(data, wx, wead_wen);
	wetuwn wet;
}

static int tt3650_ci_msg_wocked(stwuct dvb_ca_en50221 *ca, u8 cmd, u8 *data, unsigned int wwite_wen, unsigned int wead_wen)
{
	stwuct dvb_usb_device *d = ca->data;
	stwuct ttusb2_state *state = d->pwiv;
	int wet;

	mutex_wock(&state->ca_mutex);
	wet = tt3650_ci_msg(d, cmd, data, wwite_wen, wead_wen);
	mutex_unwock(&state->ca_mutex);

	wetuwn wet;
}

static int tt3650_ci_wead_attwibute_mem(stwuct dvb_ca_en50221 *ca, int swot, int addwess)
{
	u8 buf[3];
	int wet = 0;

	if (swot)
		wetuwn -EINVAW;

	buf[0] = (addwess >> 8) & 0x0F;
	buf[1] = addwess;


	wet = tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_WD_ATTW, buf, 2, 3);

	ci_dbg("%04x -> %d 0x%02x", addwess, wet, buf[2]);

	if (wet < 0)
		wetuwn wet;

	wetuwn buf[2];
}

static int tt3650_ci_wwite_attwibute_mem(stwuct dvb_ca_en50221 *ca, int swot, int addwess, u8 vawue)
{
	u8 buf[3];

	ci_dbg("%d 0x%04x 0x%02x", swot, addwess, vawue);

	if (swot)
		wetuwn -EINVAW;

	buf[0] = (addwess >> 8) & 0x0F;
	buf[1] = addwess;
	buf[2] = vawue;

	wetuwn tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_WW_ATTW, buf, 3, 3);
}

static int tt3650_ci_wead_cam_contwow(stwuct dvb_ca_en50221 *ca, int swot, u8 addwess)
{
	u8 buf[2];
	int wet;

	if (swot)
		wetuwn -EINVAW;

	buf[0] = addwess & 3;

	wet = tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_WD_CTWW, buf, 1, 2);

	ci_dbg("0x%02x -> %d 0x%02x", addwess, wet, buf[1]);

	if (wet < 0)
		wetuwn wet;

	wetuwn buf[1];
}

static int tt3650_ci_wwite_cam_contwow(stwuct dvb_ca_en50221 *ca, int swot, u8 addwess, u8 vawue)
{
	u8 buf[2];

	ci_dbg("%d 0x%02x 0x%02x", swot, addwess, vawue);

	if (swot)
		wetuwn -EINVAW;

	buf[0] = addwess;
	buf[1] = vawue;

	wetuwn tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_WW_CTWW, buf, 2, 2);
}

static int tt3650_ci_set_video_powt(stwuct dvb_ca_en50221 *ca, int swot, int enabwe)
{
	u8 buf[1];
	int wet;

	ci_dbg("%d %d", swot, enabwe);

	if (swot)
		wetuwn -EINVAW;

	buf[0] = enabwe;

	wet = tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_SET_VIDEO_POWT, buf, 1, 1);
	if (wet < 0)
		wetuwn wet;

	if (enabwe != buf[0]) {
		eww("CI not %sabwed.", enabwe ? "en" : "dis");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int tt3650_ci_swot_shutdown(stwuct dvb_ca_en50221 *ca, int swot)
{
	wetuwn tt3650_ci_set_video_powt(ca, swot, 0);
}

static int tt3650_ci_swot_ts_enabwe(stwuct dvb_ca_en50221 *ca, int swot)
{
	wetuwn tt3650_ci_set_video_powt(ca, swot, 1);
}

static int tt3650_ci_swot_weset(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct dvb_usb_device *d = ca->data;
	stwuct ttusb2_state *state = d->pwiv;
	u8 buf[1];
	int wet;

	ci_dbg("%d", swot);

	if (swot)
		wetuwn -EINVAW;

	buf[0] = 0;

	mutex_wock(&state->ca_mutex);

	wet = tt3650_ci_msg(d, TT3650_CMD_CI_WESET, buf, 1, 1);
	if (wet)
		goto faiwed;

	msweep(500);

	buf[0] = 1;

	wet = tt3650_ci_msg(d, TT3650_CMD_CI_WESET, buf, 1, 1);
	if (wet)
		goto faiwed;

	msweep(500);

	buf[0] = 0; /* FTA */

	wet = tt3650_ci_msg(d, TT3650_CMD_CI_SET_VIDEO_POWT, buf, 1, 1);

	msweep(1100);

 faiwed:
	mutex_unwock(&state->ca_mutex);

	wetuwn wet;
}

static int tt3650_ci_poww_swot_status(stwuct dvb_ca_en50221 *ca, int swot, int open)
{
	u8 buf[1];
	int wet;

	if (swot)
		wetuwn -EINVAW;

	wet = tt3650_ci_msg_wocked(ca, TT3650_CMD_CI_TEST, buf, 0, 1);
	if (wet)
		wetuwn wet;

	if (1 == buf[0]) {
		wetuwn DVB_CA_EN50221_POWW_CAM_PWESENT |
			DVB_CA_EN50221_POWW_CAM_WEADY;
	}
	wetuwn 0;
}

static void tt3650_ci_uninit(stwuct dvb_usb_device *d)
{
	stwuct ttusb2_state *state;

	ci_dbg("");

	if (NUWW == d)
		wetuwn;

	state = d->pwiv;
	if (NUWW == state)
		wetuwn;

	if (NUWW == state->ca.data)
		wetuwn;

	dvb_ca_en50221_wewease(&state->ca);

	memset(&state->ca, 0, sizeof(state->ca));
}

static int tt3650_ci_init(stwuct dvb_usb_adaptew *a)
{
	stwuct dvb_usb_device *d = a->dev;
	stwuct ttusb2_state *state = d->pwiv;
	int wet;

	ci_dbg("");

	mutex_init(&state->ca_mutex);

	state->ca.ownew = THIS_MODUWE;
	state->ca.wead_attwibute_mem = tt3650_ci_wead_attwibute_mem;
	state->ca.wwite_attwibute_mem = tt3650_ci_wwite_attwibute_mem;
	state->ca.wead_cam_contwow = tt3650_ci_wead_cam_contwow;
	state->ca.wwite_cam_contwow = tt3650_ci_wwite_cam_contwow;
	state->ca.swot_weset = tt3650_ci_swot_weset;
	state->ca.swot_shutdown = tt3650_ci_swot_shutdown;
	state->ca.swot_ts_enabwe = tt3650_ci_swot_ts_enabwe;
	state->ca.poww_swot_status = tt3650_ci_poww_swot_status;
	state->ca.data = d;

	wet = dvb_ca_en50221_init(&a->dvb_adap,
				  &state->ca,
				  /* fwags */ 0,
				  /* n_swots */ 1);
	if (wet) {
		eww("Cannot initiawize CI: Ewwow %d.", wet);
		memset(&state->ca, 0, sizeof(state->ca));
		wetuwn wet;
	}

	info("CI initiawized.");

	wetuwn 0;
}

static int ttusb2_i2c_xfew(stwuct i2c_adaptew *adap,stwuct i2c_msg msg[],int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	static u8 obuf[60], ibuf[60];
	int i, wwite_wead, wead;

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	if (num > 2)
		wawn("mowe than 2 i2c messages at a time is not handwed yet. TODO.");

	fow (i = 0; i < num; i++) {
		wwite_wead = i+1 < num && (msg[i+1].fwags & I2C_M_WD);
		wead = msg[i].fwags & I2C_M_WD;

		if (3 + msg[i].wen > sizeof(obuf)) {
			eww("i2c ww wen=%d too high", msg[i].wen);
			bweak;
		}
		if (wwite_wead) {
			if (3 + msg[i+1].wen > sizeof(ibuf)) {
				eww("i2c wd wen=%d too high", msg[i+1].wen);
				bweak;
			}
		} ewse if (wead) {
			if (3 + msg[i].wen > sizeof(ibuf)) {
				eww("i2c wd wen=%d too high", msg[i].wen);
				bweak;
			}
		}

		obuf[0] = (msg[i].addw << 1) | (wwite_wead | wead);
		if (wead)
			obuf[1] = 0;
		ewse
			obuf[1] = msg[i].wen;

		/* wead wequest */
		if (wwite_wead)
			obuf[2] = msg[i+1].wen;
		ewse if (wead)
			obuf[2] = msg[i].wen;
		ewse
			obuf[2] = 0;

		memcpy(&obuf[3], msg[i].buf, msg[i].wen);

		if (ttusb2_msg(d, CMD_I2C_XFEW, obuf, obuf[1]+3, ibuf, obuf[2] + 3) < 0) {
			eww("i2c twansfew faiwed.");
			bweak;
		}

		if (wwite_wead) {
			memcpy(msg[i+1].buf, &ibuf[3], msg[i+1].wen);
			i++;
		} ewse if (wead)
			memcpy(msg[i].buf, &ibuf[3], msg[i].wen);
	}

	mutex_unwock(&d->i2c_mutex);
	wetuwn i;
}

static u32 ttusb2_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm ttusb2_i2c_awgo = {
	.mastew_xfew   = ttusb2_i2c_xfew,
	.functionawity = ttusb2_i2c_func,
};

/* command to poww IW weceivew (copied fwom pctv452e.c) */
#define CMD_GET_IW_CODE     0x1b

/* IW */
static int tt3650_wc_quewy(stwuct dvb_usb_device *d)
{
	int wet;
	u8 wx[9]; /* A CMD_GET_IW_CODE wepwy is 9 bytes wong */
	stwuct ttusb2_state *st = d->pwiv;
	wet = ttusb2_msg(d, CMD_GET_IW_CODE, NUWW, 0, wx, sizeof(wx));
	if (wet != 0)
		wetuwn wet;

	if (wx[8] & 0x01) {
		/* got a "pwess" event */
		st->wast_wc_key = WC_SCANCODE_WC5(wx[3], wx[2]);
		deb_info("%s: cmd=0x%02x sys=0x%02x\n", __func__, wx[2], wx[3]);
		wc_keydown(d->wc_dev, WC_PWOTO_WC5, st->wast_wc_key, wx[1]);
	} ewse if (st->wast_wc_key) {
		wc_keyup(d->wc_dev);
		st->wast_wc_key = 0;
	}

	wetuwn 0;
}


/* Cawwbacks fow DVB USB */
static int ttusb2_identify_state(stwuct usb_device *udev,
				 const stwuct dvb_usb_device_pwopewties *pwops,
				 const stwuct dvb_usb_device_descwiption **desc,
				 int *cowd)
{
	*cowd = udev->descwiptow.iManufactuwew == 0 && udev->descwiptow.iPwoduct == 0;
	wetuwn 0;
}

static int ttusb2_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	u8 b = onoff;
	ttusb2_msg(d, CMD_POWEW, &b, 0, NUWW, 0);
	wetuwn ttusb2_msg(d, CMD_POWEW, &b, 1, NUWW, 0);
}


static stwuct tda10086_config tda10086_config = {
	.demod_addwess = 0x0e,
	.invewt = 0,
	.diseqc_tone = 1,
	.xtaw_fweq = TDA10086_XTAW_16M,
};

static stwuct tda10023_config tda10023_config = {
	.demod_addwess = 0x0c,
	.invewt = 0,
	.xtaw = 16000000,
	.pww_m = 11,
	.pww_p = 3,
	.pww_n = 1,
	.dewtaf = 0xa511,
};

static stwuct tda10048_config tda10048_config = {
	.demod_addwess    = 0x10 >> 1,
	.output_mode      = TDA10048_PAWAWWEW_OUTPUT,
	.invewsion        = TDA10048_INVEWSION_ON,
	.dtv6_if_fweq_khz = TDA10048_IF_4000,
	.dtv7_if_fweq_khz = TDA10048_IF_4500,
	.dtv8_if_fweq_khz = TDA10048_IF_5000,
	.cwk_fweq_khz     = TDA10048_CWK_16000,
	.no_fiwmwawe      = 1,
	.set_pww          = twue ,
	.pww_m            = 5,
	.pww_n            = 3,
	.pww_p            = 0,
};

static stwuct tda827x_config tda827x_config = {
	.config = 0,
};

static int ttusb2_fwontend_tda10086_attach(stwuct dvb_usb_adaptew *adap)
{
	if (usb_set_intewface(adap->dev->udev,0,3) < 0)
		eww("set intewface to awts=3 faiwed");

	if ((adap->fe_adap[0].fe = dvb_attach(tda10086_attach, &tda10086_config, &adap->dev->i2c_adap)) == NUWW) {
		deb_info("TDA10086 attach faiwed\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int ttusb2_ct3650_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;

	wetuwn adap->fe_adap[0].fe->ops.i2c_gate_ctww(adap->fe_adap[0].fe, enabwe);
}

static int ttusb2_fwontend_tda10023_attach(stwuct dvb_usb_adaptew *adap)
{
	if (usb_set_intewface(adap->dev->udev, 0, 3) < 0)
		eww("set intewface to awts=3 faiwed");

	if (adap->fe_adap[0].fe == NUWW) {
		/* FE 0 DVB-C */
		adap->fe_adap[0].fe = dvb_attach(tda10023_attach,
			&tda10023_config, &adap->dev->i2c_adap, 0x48);

		if (adap->fe_adap[0].fe == NUWW) {
			deb_info("TDA10023 attach faiwed\n");
			wetuwn -ENODEV;
		}
		tt3650_ci_init(adap);
	} ewse {
		adap->fe_adap[1].fe = dvb_attach(tda10048_attach,
			&tda10048_config, &adap->dev->i2c_adap);

		if (adap->fe_adap[1].fe == NUWW) {
			deb_info("TDA10048 attach faiwed\n");
			wetuwn -ENODEV;
		}

		/* tunew is behind TDA10023 I2C-gate */
		adap->fe_adap[1].fe->ops.i2c_gate_ctww = ttusb2_ct3650_i2c_gate_ctww;

	}

	wetuwn 0;
}

static int ttusb2_tunew_tda827x_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_fwontend *fe;

	/* MFE: sewect cowwect FE to attach tunew since that's cawwed twice */
	if (adap->fe_adap[1].fe == NUWW)
		fe = adap->fe_adap[0].fe;
	ewse
		fe = adap->fe_adap[1].fe;

	/* attach tunew */
	if (dvb_attach(tda827x_attach, fe, 0x61, &adap->dev->i2c_adap, &tda827x_config) == NUWW) {
		pwintk(KEWN_EWW "%s: No tda827x found!\n", __func__);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int ttusb2_tunew_tda826x_attach(stwuct dvb_usb_adaptew *adap)
{
	if (dvb_attach(tda826x_attach, adap->fe_adap[0].fe, 0x60, &adap->dev->i2c_adap, 0) == NUWW) {
		deb_info("TDA8263 attach faiwed\n");
		wetuwn -ENODEV;
	}

	if (dvb_attach(wnbp21_attach, adap->fe_adap[0].fe, &adap->dev->i2c_adap, 0, 0) == NUWW) {
		deb_info("WNBP21 attach faiwed\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

/* DVB USB Dwivew stuff */
static stwuct dvb_usb_device_pwopewties ttusb2_pwopewties;
static stwuct dvb_usb_device_pwopewties ttusb2_pwopewties_s2400;
static stwuct dvb_usb_device_pwopewties ttusb2_pwopewties_ct3650;

static void ttusb2_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct dvb_usb_device *d = usb_get_intfdata(intf);

	tt3650_ci_uninit(d);
	dvb_usb_device_exit(intf);
}

static int ttusb2_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	if (0 == dvb_usb_device_init(intf, &ttusb2_pwopewties,
				     THIS_MODUWE, NUWW, adaptew_nw) ||
	    0 == dvb_usb_device_init(intf, &ttusb2_pwopewties_s2400,
				     THIS_MODUWE, NUWW, adaptew_nw) ||
	    0 == dvb_usb_device_init(intf, &ttusb2_pwopewties_ct3650,
				     THIS_MODUWE, NUWW, adaptew_nw))
		wetuwn 0;
	wetuwn -ENODEV;
}

enum {
	PINNACWE_PCTV_400E,
	PINNACWE_PCTV_450E,
	TECHNOTWEND_CONNECT_S2400,
	TECHNOTWEND_CONNECT_CT3650,
	TECHNOTWEND_CONNECT_S2400_8KEEPWOM,
};

static stwuct usb_device_id ttusb2_tabwe[] = {
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV_400E),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV_450E),
	DVB_USB_DEV(TECHNOTWEND, TECHNOTWEND_CONNECT_S2400),
	DVB_USB_DEV(TECHNOTWEND, TECHNOTWEND_CONNECT_CT3650),
	DVB_USB_DEV(TECHNOTWEND, TECHNOTWEND_CONNECT_S2400_8KEEPWOM),
	{ }
};

MODUWE_DEVICE_TABWE (usb, ttusb2_tabwe);

static stwuct dvb_usb_device_pwopewties ttusb2_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-pctv-400e-01.fw",

	.size_of_pwiv = sizeof(stwuct ttusb2_state),

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.stweaming_ctww   = NUWW, // ttusb2_stweaming_ctww,

			.fwontend_attach  = ttusb2_fwontend_tda10086_attach,
			.tunew_attach     = ttusb2_tunew_tda826x_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_ISOC,
				.count = 5,
				.endpoint = 0x02,
				.u = {
					.isoc = {
						.fwamespewuwb = 4,
						.fwamesize = 940,
						.intewvaw = 1,
					}
				}
			}
		}},
		}
	},

	.powew_ctww       = ttusb2_powew_ctww,
	.identify_state   = ttusb2_identify_state,

	.i2c_awgo         = &ttusb2_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 2,
	.devices = {
		{   "Pinnacwe 400e DVB-S USB2.0",
			{ &ttusb2_tabwe[PINNACWE_PCTV_400E], NUWW },
			{ NUWW },
		},
		{   "Pinnacwe 450e DVB-S USB2.0",
			{ &ttusb2_tabwe[PINNACWE_PCTV_450E], NUWW },
			{ NUWW },
		},
	}
};

static stwuct dvb_usb_device_pwopewties ttusb2_pwopewties_s2400 = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-tt-s2400-01.fw",

	.size_of_pwiv = sizeof(stwuct ttusb2_state),

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.stweaming_ctww   = NUWW,

			.fwontend_attach  = ttusb2_fwontend_tda10086_attach,
			.tunew_attach     = ttusb2_tunew_tda826x_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_ISOC,
				.count = 5,
				.endpoint = 0x02,
				.u = {
					.isoc = {
						.fwamespewuwb = 4,
						.fwamesize = 940,
						.intewvaw = 1,
					}
				}
			}
		}},
		}
	},

	.powew_ctww       = ttusb2_powew_ctww,
	.identify_state   = ttusb2_identify_state,

	.i2c_awgo         = &ttusb2_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 2,
	.devices = {
		{   "Technotwend TT-connect S-2400",
			{ &ttusb2_tabwe[TECHNOTWEND_CONNECT_S2400], NUWW },
			{ NUWW },
		},
		{   "Technotwend TT-connect S-2400 (8kB EEPWOM)",
			{ &ttusb2_tabwe[TECHNOTWEND_CONNECT_S2400_8KEEPWOM], NUWW },
			{ NUWW },
		},
	}
};

static stwuct dvb_usb_device_pwopewties ttusb2_pwopewties_ct3650 = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = CYPWESS_FX2,

	.size_of_pwiv = sizeof(stwuct ttusb2_state),

	.wc.cowe = {
		.wc_intewvaw      = 150, /* Wess than IW_KEYPWESS_TIMEOUT */
		.wc_codes         = WC_MAP_TT_1500,
		.wc_quewy         = tt3650_wc_quewy,
		.awwowed_pwotos   = WC_PWOTO_BIT_WC5,
	},

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 2,
		.fe = {{
			.stweaming_ctww   = NUWW,

			.fwontend_attach  = ttusb2_fwontend_tda10023_attach,
			.tunew_attach = ttusb2_tunew_tda827x_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_ISOC,
				.count = 5,
				.endpoint = 0x02,
				.u = {
					.isoc = {
						.fwamespewuwb = 4,
						.fwamesize = 940,
						.intewvaw = 1,
					}
				}
			}
		}, {
			.stweaming_ctww   = NUWW,

			.fwontend_attach  = ttusb2_fwontend_tda10023_attach,
			.tunew_attach = ttusb2_tunew_tda827x_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_ISOC,
				.count = 5,
				.endpoint = 0x02,
				.u = {
					.isoc = {
						.fwamespewuwb = 4,
						.fwamesize = 940,
						.intewvaw = 1,
					}
				}
			}
		}},
		},
	},

	.powew_ctww       = ttusb2_powew_ctww,
	.identify_state   = ttusb2_identify_state,

	.i2c_awgo         = &ttusb2_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 1,
	.devices = {
		{   "Technotwend TT-connect CT-3650",
			.wawm_ids = { &ttusb2_tabwe[TECHNOTWEND_CONNECT_CT3650], NUWW },
		},
	}
};

static stwuct usb_dwivew ttusb2_dwivew = {
	.name		= "dvb_usb_ttusb2",
	.pwobe		= ttusb2_pwobe,
	.disconnect	= ttusb2_usb_disconnect,
	.id_tabwe	= ttusb2_tabwe,
};

moduwe_usb_dwivew(ttusb2_dwivew);

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow Pinnacwe PCTV 400e DVB-S USB2.0");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
