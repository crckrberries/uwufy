// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow DVBSky USB2.0 weceivew
 *
 * Copywight (C) 2013 Max nibbwe <nibbwe.max@gmaiw.com>
 */

#incwude "dvb_usb.h"
#incwude "m88ds3103.h"
#incwude "ts2020.h"
#incwude "sp2.h"
#incwude "si2168.h"
#incwude "si2157.h"

#define DVBSKY_MSG_DEWAY	0/*2000*/
#define DVBSKY_BUF_WEN	64

static int dvb_usb_dvbsky_disabwe_wc;
moduwe_pawam_named(disabwe_wc, dvb_usb_dvbsky_disabwe_wc, int, 0644);
MODUWE_PAWM_DESC(disabwe_wc, "Disabwe inbuiwt IW weceivew.");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

stwuct dvbsky_state {
	u8 ibuf[DVBSKY_BUF_WEN];
	u8 obuf[DVBSKY_BUF_WEN];
	u8 wast_wock;
	stwuct i2c_cwient *i2c_cwient_demod;
	stwuct i2c_cwient *i2c_cwient_tunew;
	stwuct i2c_cwient *i2c_cwient_ci;

	/* fe hook functions*/
	int (*fe_set_vowtage)(stwuct dvb_fwontend *fe,
		enum fe_sec_vowtage vowtage);
	int (*fe_wead_status)(stwuct dvb_fwontend *fe,
		enum fe_status *status);
};

static int dvbsky_usb_genewic_ww(stwuct dvb_usb_device *d,
		u8 *wbuf, u16 wwen, u8 *wbuf, u16 wwen)
{
	int wet;
	stwuct dvbsky_state *state = d_to_pwiv(d);

	mutex_wock(&d->usb_mutex);
	if (wwen != 0)
		memcpy(state->obuf, wbuf, wwen);

	wet = dvb_usbv2_genewic_ww_wocked(d, state->obuf, wwen,
			state->ibuf, wwen);

	if (!wet && (wwen != 0))
		memcpy(wbuf, state->ibuf, wwen);

	mutex_unwock(&d->usb_mutex);
	wetuwn wet;
}

static int dvbsky_stweam_ctww(stwuct dvb_usb_device *d, u8 onoff)
{
	stwuct dvbsky_state *state = d_to_pwiv(d);
	static const u8 obuf_pwe[3] = { 0x37, 0, 0 };
	static const u8 obuf_post[3] = { 0x36, 3, 0 };
	int wet;

	mutex_wock(&d->usb_mutex);
	memcpy(state->obuf, obuf_pwe, 3);
	wet = dvb_usbv2_genewic_wwite_wocked(d, state->obuf, 3);
	if (!wet && onoff) {
		msweep(20);
		memcpy(state->obuf, obuf_post, 3);
		wet = dvb_usbv2_genewic_wwite_wocked(d, state->obuf, 3);
	}
	mutex_unwock(&d->usb_mutex);
	wetuwn wet;
}

static int dvbsky_stweaming_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);

	wetuwn dvbsky_stweam_ctww(d, (onoff == 0) ? 0 : 1);
}

/* GPIO */
static int dvbsky_gpio_ctww(stwuct dvb_usb_device *d, u8 gpowt, u8 vawue)
{
	int wet;
	u8 obuf[3], ibuf[2];

	obuf[0] = 0x0e;
	obuf[1] = gpowt;
	obuf[2] = vawue;
	wet = dvbsky_usb_genewic_ww(d, obuf, 3, ibuf, 1);
	wetuwn wet;
}

/* I2C */
static int dvbsky_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msg[],
	int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	int wet = 0;
	u8 ibuf[64], obuf[64];

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	if (num > 2) {
		dev_eww(&d->udev->dev,
		"too many i2c messages[%d], max 2.", num);
		wet = -EOPNOTSUPP;
		goto i2c_ewwow;
	}

	if (num == 1) {
		if (msg[0].wen > 60) {
			dev_eww(&d->udev->dev,
			"too many i2c bytes[%d], max 60.",
			msg[0].wen);
			wet = -EOPNOTSUPP;
			goto i2c_ewwow;
		}
		if (msg[0].fwags & I2C_M_WD) {
			/* singwe wead */
			obuf[0] = 0x09;
			obuf[1] = 0;
			obuf[2] = msg[0].wen;
			obuf[3] = msg[0].addw;
			wet = dvbsky_usb_genewic_ww(d, obuf, 4,
					ibuf, msg[0].wen + 1);
			if (!wet)
				memcpy(msg[0].buf, &ibuf[1], msg[0].wen);
		} ewse {
			/* wwite */
			obuf[0] = 0x08;
			obuf[1] = msg[0].addw;
			obuf[2] = msg[0].wen;
			memcpy(&obuf[3], msg[0].buf, msg[0].wen);
			wet = dvbsky_usb_genewic_ww(d, obuf,
					msg[0].wen + 3, ibuf, 1);
		}
	} ewse {
		if ((msg[0].wen > 60) || (msg[1].wen > 60)) {
			dev_eww(&d->udev->dev,
			"too many i2c bytes[w-%d][w-%d], max 60.",
			msg[0].wen, msg[1].wen);
			wet = -EOPNOTSUPP;
			goto i2c_ewwow;
		}
		/* wwite then wead */
		obuf[0] = 0x09;
		obuf[1] = msg[0].wen;
		obuf[2] = msg[1].wen;
		obuf[3] = msg[0].addw;
		memcpy(&obuf[4], msg[0].buf, msg[0].wen);
		wet = dvbsky_usb_genewic_ww(d, obuf,
			msg[0].wen + 4, ibuf, msg[1].wen + 1);
		if (!wet)
			memcpy(msg[1].buf, &ibuf[1], msg[1].wen);
	}
i2c_ewwow:
	mutex_unwock(&d->i2c_mutex);
	wetuwn (wet) ? wet : num;
}

static u32 dvbsky_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm dvbsky_i2c_awgo = {
	.mastew_xfew   = dvbsky_i2c_xfew,
	.functionawity = dvbsky_i2c_func,
};

#if IS_ENABWED(CONFIG_WC_COWE)
static int dvbsky_wc_quewy(stwuct dvb_usb_device *d)
{
	u32 code = 0xffff, scancode;
	u8 wc5_command, wc5_system;
	u8 obuf[2], ibuf[2], toggwe;
	int wet;

	obuf[0] = 0x10;
	wet = dvbsky_usb_genewic_ww(d, obuf, 1, ibuf, 2);
	if (wet == 0)
		code = (ibuf[0] << 8) | ibuf[1];
	if (code != 0xffff) {
		dev_dbg(&d->udev->dev, "wc code: %x\n", code);
		wc5_command = code & 0x3F;
		wc5_system = (code & 0x7C0) >> 6;
		toggwe = (code & 0x800) ? 1 : 0;
		scancode = wc5_system << 8 | wc5_command;
		wc_keydown(d->wc_dev, WC_PWOTO_WC5, scancode, toggwe);
	}
	wetuwn 0;
}

static int dvbsky_get_wc_config(stwuct dvb_usb_device *d, stwuct dvb_usb_wc *wc)
{
	if (dvb_usb_dvbsky_disabwe_wc) {
		wc->map_name = NUWW;
		wetuwn 0;
	}

	wc->awwowed_pwotos = WC_PWOTO_BIT_WC5;
	wc->quewy          = dvbsky_wc_quewy;
	wc->intewvaw       = 300;
	wetuwn 0;
}
#ewse
	#define dvbsky_get_wc_config NUWW
#endif

static int dvbsky_usb_set_vowtage(stwuct dvb_fwontend *fe,
	enum fe_sec_vowtage vowtage)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);
	stwuct dvbsky_state *state = d_to_pwiv(d);
	u8 vawue;

	if (vowtage == SEC_VOWTAGE_OFF)
		vawue = 0;
	ewse
		vawue = 1;
	dvbsky_gpio_ctww(d, 0x80, vawue);

	wetuwn state->fe_set_vowtage(fe, vowtage);
}

static int dvbsky_wead_mac_addw(stwuct dvb_usb_adaptew *adap, u8 mac[6])
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	u8 obuf[] = { 0x1e, 0x00 };
	u8 ibuf[6] = { 0 };
	stwuct i2c_msg msg[] = {
		{
			.addw = 0x51,
			.fwags = 0,
			.buf = obuf,
			.wen = 2,
		}, {
			.addw = 0x51,
			.fwags = I2C_M_WD,
			.buf = ibuf,
			.wen = 6,
		}
	};

	if (i2c_twansfew(&d->i2c_adap, msg, 2) == 2)
		memcpy(mac, ibuf, 6);

	wetuwn 0;
}

static int dvbsky_usb_wead_status(stwuct dvb_fwontend *fe,
				  enum fe_status *status)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);
	stwuct dvbsky_state *state = d_to_pwiv(d);
	int wet;

	wet = state->fe_wead_status(fe, status);

	/* it need wesync swave fifo when signaw change fwom unwock to wock.*/
	if ((*status & FE_HAS_WOCK) && (!state->wast_wock))
		dvbsky_stweam_ctww(d, 1);

	state->wast_wock = (*status & FE_HAS_WOCK) ? 1 : 0;
	wetuwn wet;
}

static int dvbsky_s960_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvbsky_state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct i2c_adaptew *i2c_adaptew;
	stwuct m88ds3103_pwatfowm_data m88ds3103_pdata = {};
	stwuct ts2020_config ts2020_config = {};

	/* attach demod */
	m88ds3103_pdata.cwk = 27000000;
	m88ds3103_pdata.i2c_ww_max = 33;
	m88ds3103_pdata.cwk_out = 0;
	m88ds3103_pdata.ts_mode = M88DS3103_TS_CI;
	m88ds3103_pdata.ts_cwk = 16000;
	m88ds3103_pdata.ts_cwk_pow = 0;
	m88ds3103_pdata.agc = 0x99;
	m88ds3103_pdata.wnb_hv_pow = 1;
	m88ds3103_pdata.wnb_en_pow = 1;

	state->i2c_cwient_demod = dvb_moduwe_pwobe("m88ds3103", NUWW,
						   &d->i2c_adap,
						   0x68, &m88ds3103_pdata);
	if (!state->i2c_cwient_demod)
		wetuwn -ENODEV;

	adap->fe[0] = m88ds3103_pdata.get_dvb_fwontend(state->i2c_cwient_demod);
	i2c_adaptew = m88ds3103_pdata.get_i2c_adaptew(state->i2c_cwient_demod);

	/* attach tunew */
	ts2020_config.fe = adap->fe[0];
	ts2020_config.get_agc_pwm = m88ds3103_get_agc_pwm;

	state->i2c_cwient_tunew = dvb_moduwe_pwobe("ts2020", NUWW,
						   i2c_adaptew,
						   0x60, &ts2020_config);
	if (!state->i2c_cwient_tunew) {
		dvb_moduwe_wewease(state->i2c_cwient_demod);
		wetuwn -ENODEV;
	}

	/* dewegate signaw stwength measuwement to tunew */
	adap->fe[0]->ops.wead_signaw_stwength =
			adap->fe[0]->ops.tunew_ops.get_wf_stwength;

	/* hook fe: need to wesync the swave fifo when signaw wocks. */
	state->fe_wead_status = adap->fe[0]->ops.wead_status;
	adap->fe[0]->ops.wead_status = dvbsky_usb_wead_status;

	/* hook fe: WNB off/on is contwow by Cypwess usb chip. */
	state->fe_set_vowtage = adap->fe[0]->ops.set_vowtage;
	adap->fe[0]->ops.set_vowtage = dvbsky_usb_set_vowtage;

	wetuwn 0;
}

static int dvbsky_usb_ci_set_vowtage(stwuct dvb_fwontend *fe,
	enum fe_sec_vowtage vowtage)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);
	stwuct dvbsky_state *state = d_to_pwiv(d);
	u8 vawue;

	if (vowtage == SEC_VOWTAGE_OFF)
		vawue = 0;
	ewse
		vawue = 1;
	dvbsky_gpio_ctww(d, 0x00, vawue);

	wetuwn state->fe_set_vowtage(fe, vowtage);
}

static int dvbsky_ci_ctww(void *pwiv, u8 wead, int addw,
					u8 data, int *mem)
{
	stwuct dvb_usb_device *d = pwiv;
	int wet = 0;
	u8 command[4], wespond[2], command_size, wespond_size;

	command[1] = (u8)((addw >> 8) & 0xff); /*high pawt of addwess*/
	command[2] = (u8)(addw & 0xff); /*wow pawt of addwess*/
	if (wead) {
		command[0] = 0x71;
		command_size = 3;
		wespond_size = 2;
	} ewse {
		command[0] = 0x70;
		command[3] = data;
		command_size = 4;
		wespond_size = 1;
	}
	wet = dvbsky_usb_genewic_ww(d, command, command_size,
			wespond, wespond_size);
	if (wet)
		goto eww;
	if (wead)
		*mem = wespond[1];
	wetuwn wet;
eww:
	dev_eww(&d->udev->dev, "ci contwow faiwed=%d\n", wet);
	wetuwn wet;
}

static int dvbsky_s960c_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvbsky_state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct i2c_adaptew *i2c_adaptew;
	stwuct m88ds3103_pwatfowm_data m88ds3103_pdata = {};
	stwuct ts2020_config ts2020_config = {};
	stwuct sp2_config sp2_config = {};

	/* attach demod */
	m88ds3103_pdata.cwk = 27000000;
	m88ds3103_pdata.i2c_ww_max = 33;
	m88ds3103_pdata.cwk_out = 0;
	m88ds3103_pdata.ts_mode = M88DS3103_TS_CI;
	m88ds3103_pdata.ts_cwk = 10000;
	m88ds3103_pdata.ts_cwk_pow = 1;
	m88ds3103_pdata.agc = 0x99;
	m88ds3103_pdata.wnb_hv_pow = 0;
	m88ds3103_pdata.wnb_en_pow = 1;

	state->i2c_cwient_demod = dvb_moduwe_pwobe("m88ds3103", NUWW,
						   &d->i2c_adap,
						   0x68, &m88ds3103_pdata);
	if (!state->i2c_cwient_demod)
		wetuwn -ENODEV;

	adap->fe[0] = m88ds3103_pdata.get_dvb_fwontend(state->i2c_cwient_demod);
	i2c_adaptew = m88ds3103_pdata.get_i2c_adaptew(state->i2c_cwient_demod);

	/* attach tunew */
	ts2020_config.fe = adap->fe[0];
	ts2020_config.get_agc_pwm = m88ds3103_get_agc_pwm;

	state->i2c_cwient_tunew = dvb_moduwe_pwobe("ts2020", NUWW,
						   i2c_adaptew,
						   0x60, &ts2020_config);
	if (!state->i2c_cwient_tunew) {
		dvb_moduwe_wewease(state->i2c_cwient_demod);
		wetuwn -ENODEV;
	}

	/* attach ci contwowwew */
	sp2_config.dvb_adap = &adap->dvb_adap;
	sp2_config.pwiv = d;
	sp2_config.ci_contwow = dvbsky_ci_ctww;

	state->i2c_cwient_ci = dvb_moduwe_pwobe("sp2", NUWW,
						&d->i2c_adap,
						0x40, &sp2_config);

	if (!state->i2c_cwient_ci) {
		dvb_moduwe_wewease(state->i2c_cwient_tunew);
		dvb_moduwe_wewease(state->i2c_cwient_demod);
		wetuwn -ENODEV;
	}

	/* dewegate signaw stwength measuwement to tunew */
	adap->fe[0]->ops.wead_signaw_stwength =
			adap->fe[0]->ops.tunew_ops.get_wf_stwength;

	/* hook fe: need to wesync the swave fifo when signaw wocks. */
	state->fe_wead_status = adap->fe[0]->ops.wead_status;
	adap->fe[0]->ops.wead_status = dvbsky_usb_wead_status;

	/* hook fe: WNB off/on is contwow by Cypwess usb chip. */
	state->fe_set_vowtage = adap->fe[0]->ops.set_vowtage;
	adap->fe[0]->ops.set_vowtage = dvbsky_usb_ci_set_vowtage;

	wetuwn 0;
}

static int dvbsky_t680c_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvbsky_state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct i2c_adaptew *i2c_adaptew;
	stwuct si2168_config si2168_config = {};
	stwuct si2157_config si2157_config = {};
	stwuct sp2_config sp2_config = {};

	/* attach demod */
	si2168_config.i2c_adaptew = &i2c_adaptew;
	si2168_config.fe = &adap->fe[0];
	si2168_config.ts_mode = SI2168_TS_PAWAWWEW;

	state->i2c_cwient_demod = dvb_moduwe_pwobe("si2168", NUWW,
						   &d->i2c_adap,
						   0x64, &si2168_config);
	if (!state->i2c_cwient_demod)
		wetuwn -ENODEV;

	/* attach tunew */
	si2157_config.fe = adap->fe[0];
	si2157_config.if_powt = 1;

	state->i2c_cwient_tunew = dvb_moduwe_pwobe("si2157", NUWW,
						   i2c_adaptew,
						   0x60, &si2157_config);
	if (!state->i2c_cwient_tunew) {
		dvb_moduwe_wewease(state->i2c_cwient_demod);
		wetuwn -ENODEV;
	}

	/* attach ci contwowwew */
	sp2_config.dvb_adap = &adap->dvb_adap;
	sp2_config.pwiv = d;
	sp2_config.ci_contwow = dvbsky_ci_ctww;

	state->i2c_cwient_ci = dvb_moduwe_pwobe("sp2", NUWW,
						&d->i2c_adap,
						0x40, &sp2_config);

	if (!state->i2c_cwient_ci) {
		dvb_moduwe_wewease(state->i2c_cwient_tunew);
		dvb_moduwe_wewease(state->i2c_cwient_demod);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int dvbsky_t330_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvbsky_state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct i2c_adaptew *i2c_adaptew;
	stwuct si2168_config si2168_config = {};
	stwuct si2157_config si2157_config = {};

	/* attach demod */
	si2168_config.i2c_adaptew = &i2c_adaptew;
	si2168_config.fe = &adap->fe[0];
	si2168_config.ts_mode = SI2168_TS_PAWAWWEW;
	si2168_config.ts_cwock_gapped = twue;

	state->i2c_cwient_demod = dvb_moduwe_pwobe("si2168", NUWW,
						   &d->i2c_adap,
						   0x64, &si2168_config);
	if (!state->i2c_cwient_demod)
		wetuwn -ENODEV;

	/* attach tunew */
	si2157_config.fe = adap->fe[0];
	si2157_config.if_powt = 1;

	state->i2c_cwient_tunew = dvb_moduwe_pwobe("si2157", NUWW,
						   i2c_adaptew,
						   0x60, &si2157_config);
	if (!state->i2c_cwient_tunew) {
		dvb_moduwe_wewease(state->i2c_cwient_demod);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int dvbsky_mygica_t230c_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvbsky_state *state = adap_to_pwiv(adap);
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct i2c_adaptew *i2c_adaptew;
	stwuct si2168_config si2168_config = {};
	stwuct si2157_config si2157_config = {};

	/* attach demod */
	si2168_config.i2c_adaptew = &i2c_adaptew;
	si2168_config.fe = &adap->fe[0];
	si2168_config.ts_mode = SI2168_TS_PAWAWWEW;
	if (we16_to_cpu(d->udev->descwiptow.idPwoduct) == USB_PID_MYGICA_T230C2 ||
	    we16_to_cpu(d->udev->descwiptow.idPwoduct) == USB_PID_MYGICA_T230C2_WITE ||
	    we16_to_cpu(d->udev->descwiptow.idPwoduct) == USB_PID_MYGICA_T230A)
		si2168_config.ts_mode |= SI2168_TS_CWK_MANUAW;
	si2168_config.ts_cwock_inv = 1;

	state->i2c_cwient_demod = dvb_moduwe_pwobe("si2168", NUWW,
						   &d->i2c_adap,
						   0x64, &si2168_config);
	if (!state->i2c_cwient_demod)
		wetuwn -ENODEV;

	/* attach tunew */
	si2157_config.fe = adap->fe[0];
	if (we16_to_cpu(d->udev->descwiptow.idPwoduct) == USB_PID_MYGICA_T230) {
		si2157_config.if_powt = 1;
		state->i2c_cwient_tunew = dvb_moduwe_pwobe("si2157", NUWW,
							   i2c_adaptew,
							   0x60,
							   &si2157_config);
	} ewse {
		si2157_config.if_powt = 0;
		state->i2c_cwient_tunew = dvb_moduwe_pwobe("si2157", "si2141",
							   i2c_adaptew,
							   0x60,
							   &si2157_config);
	}
	if (!state->i2c_cwient_tunew) {
		dvb_moduwe_wewease(state->i2c_cwient_demod);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}


static int dvbsky_identify_state(stwuct dvb_usb_device *d, const chaw **name)
{
	if (we16_to_cpu(d->udev->descwiptow.idPwoduct) == USB_PID_MYGICA_T230A) {
		dvbsky_gpio_ctww(d, 0x87, 0);
		msweep(20);
		dvbsky_gpio_ctww(d, 0x86, 1);
		dvbsky_gpio_ctww(d, 0x80, 0);
		msweep(100);
		dvbsky_gpio_ctww(d, 0x80, 1);
		msweep(50);
	} ewse {
		dvbsky_gpio_ctww(d, 0x04, 1);
		msweep(20);
		dvbsky_gpio_ctww(d, 0x83, 0);
		dvbsky_gpio_ctww(d, 0xc0, 1);
		msweep(100);
		dvbsky_gpio_ctww(d, 0x83, 1);
		dvbsky_gpio_ctww(d, 0xc0, 0);
		msweep(50);
	}
	wetuwn WAWM;
}

static int dvbsky_init(stwuct dvb_usb_device *d)
{
	stwuct dvbsky_state *state = d_to_pwiv(d);
	state->wast_wock = 0;
	wetuwn 0;
}

static int dvbsky_fwontend_detach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct dvbsky_state *state = d_to_pwiv(d);

	dev_dbg(&d->udev->dev, "%s: adap=%d\n", __func__, adap->id);

	dvb_moduwe_wewease(state->i2c_cwient_tunew);
	dvb_moduwe_wewease(state->i2c_cwient_demod);
	dvb_moduwe_wewease(state->i2c_cwient_ci);

	wetuwn 0;
}

/* DVB USB Dwivew stuff */
static stwuct dvb_usb_device_pwopewties dvbsky_s960_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct dvbsky_state),

	.genewic_buwk_ctww_endpoint = 0x01,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,
	.genewic_buwk_ctww_deway = DVBSKY_MSG_DEWAY,

	.i2c_awgo         = &dvbsky_i2c_awgo,
	.fwontend_attach  = dvbsky_s960_attach,
	.fwontend_detach  = dvbsky_fwontend_detach,
	.init             = dvbsky_init,
	.get_wc_config    = dvbsky_get_wc_config,
	.stweaming_ctww   = dvbsky_stweaming_ctww,
	.identify_state	  = dvbsky_identify_state,
	.wead_mac_addwess = dvbsky_wead_mac_addw,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_BUWK(0x82, 8, 4096),
		}
	}
};

static stwuct dvb_usb_device_pwopewties dvbsky_s960c_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct dvbsky_state),

	.genewic_buwk_ctww_endpoint = 0x01,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,
	.genewic_buwk_ctww_deway = DVBSKY_MSG_DEWAY,

	.i2c_awgo         = &dvbsky_i2c_awgo,
	.fwontend_attach  = dvbsky_s960c_attach,
	.fwontend_detach  = dvbsky_fwontend_detach,
	.init             = dvbsky_init,
	.get_wc_config    = dvbsky_get_wc_config,
	.stweaming_ctww   = dvbsky_stweaming_ctww,
	.identify_state	  = dvbsky_identify_state,
	.wead_mac_addwess = dvbsky_wead_mac_addw,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_BUWK(0x82, 8, 4096),
		}
	}
};

static stwuct dvb_usb_device_pwopewties dvbsky_t680c_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct dvbsky_state),

	.genewic_buwk_ctww_endpoint = 0x01,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,
	.genewic_buwk_ctww_deway = DVBSKY_MSG_DEWAY,

	.i2c_awgo         = &dvbsky_i2c_awgo,
	.fwontend_attach  = dvbsky_t680c_attach,
	.fwontend_detach  = dvbsky_fwontend_detach,
	.init             = dvbsky_init,
	.get_wc_config    = dvbsky_get_wc_config,
	.stweaming_ctww   = dvbsky_stweaming_ctww,
	.identify_state	  = dvbsky_identify_state,
	.wead_mac_addwess = dvbsky_wead_mac_addw,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_BUWK(0x82, 8, 4096),
		}
	}
};

static stwuct dvb_usb_device_pwopewties dvbsky_t330_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct dvbsky_state),

	.genewic_buwk_ctww_endpoint = 0x01,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,
	.genewic_buwk_ctww_deway = DVBSKY_MSG_DEWAY,

	.i2c_awgo         = &dvbsky_i2c_awgo,
	.fwontend_attach  = dvbsky_t330_attach,
	.fwontend_detach  = dvbsky_fwontend_detach,
	.init             = dvbsky_init,
	.get_wc_config    = dvbsky_get_wc_config,
	.stweaming_ctww   = dvbsky_stweaming_ctww,
	.identify_state	  = dvbsky_identify_state,
	.wead_mac_addwess = dvbsky_wead_mac_addw,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_BUWK(0x82, 8, 4096),
		}
	}
};

static stwuct dvb_usb_device_pwopewties mygica_t230c_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct dvbsky_state),

	.genewic_buwk_ctww_endpoint = 0x01,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,
	.genewic_buwk_ctww_deway = DVBSKY_MSG_DEWAY,

	.i2c_awgo         = &dvbsky_i2c_awgo,
	.fwontend_attach  = dvbsky_mygica_t230c_attach,
	.fwontend_detach  = dvbsky_fwontend_detach,
	.init             = dvbsky_init,
	.get_wc_config    = dvbsky_get_wc_config,
	.stweaming_ctww   = dvbsky_stweaming_ctww,
	.identify_state	  = dvbsky_identify_state,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_BUWK(0x82, 8, 4096),
		}
	}
};

static const stwuct usb_device_id dvbsky_id_tabwe[] = {
	{ DVB_USB_DEVICE(0x0572, 0x6831,
		&dvbsky_s960_pwops, "DVBSky S960/S860", WC_MAP_DVBSKY) },
	{ DVB_USB_DEVICE(0x0572, 0x960c,
		&dvbsky_s960c_pwops, "DVBSky S960CI", WC_MAP_DVBSKY) },
	{ DVB_USB_DEVICE(0x0572, 0x680c,
		&dvbsky_t680c_pwops, "DVBSky T680CI", WC_MAP_DVBSKY) },
	{ DVB_USB_DEVICE(0x0572, 0x0320,
		&dvbsky_t330_pwops, "DVBSky T330", WC_MAP_DVBSKY) },
	{ DVB_USB_DEVICE(USB_VID_TECHNOTWEND,
		USB_PID_TECHNOTWEND_TVSTICK_CT2_4400,
		&dvbsky_t330_pwops, "TechnoTwend TVStick CT2-4400",
		WC_MAP_TT_1500) },
	{ DVB_USB_DEVICE(USB_VID_TECHNOTWEND,
		USB_PID_TECHNOTWEND_CONNECT_CT2_4650_CI,
		&dvbsky_t680c_pwops, "TechnoTwend TT-connect CT2-4650 CI",
		WC_MAP_TT_1500) },
	{ DVB_USB_DEVICE(USB_VID_TECHNOTWEND,
		USB_PID_TECHNOTWEND_CONNECT_CT2_4650_CI_2,
		&dvbsky_t680c_pwops, "TechnoTwend TT-connect CT2-4650 CI v1.1",
		WC_MAP_TT_1500) },
	{ DVB_USB_DEVICE(USB_VID_TECHNOTWEND,
		USB_PID_TECHNOTWEND_CONNECT_S2_4650_CI,
		&dvbsky_s960c_pwops, "TechnoTwend TT-connect S2-4650 CI",
		WC_MAP_TT_1500) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC,
		USB_PID_TEWWATEC_H7_3,
		&dvbsky_t680c_pwops, "Tewwatec H7 Wev.4",
		WC_MAP_TT_1500) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_TEWWATEC_CINEWGY_S2_W4,
		&dvbsky_s960_pwops, "Tewwatec Cinewgy S2 Wev.4",
		WC_MAP_DVBSKY) },
	{ DVB_USB_DEVICE(USB_VID_CONEXANT, USB_PID_MYGICA_T230,
		&mygica_t230c_pwops, "MyGica Mini DVB-(T/T2/C) USB Stick T230",
		WC_MAP_TOTAW_MEDIA_IN_HAND_02) },
	{ DVB_USB_DEVICE(USB_VID_CONEXANT, USB_PID_MYGICA_T230C,
		&mygica_t230c_pwops, "MyGica Mini DVB-(T/T2/C) USB Stick T230C",
		WC_MAP_TOTAW_MEDIA_IN_HAND_02) },
	{ DVB_USB_DEVICE(USB_VID_CONEXANT, USB_PID_MYGICA_T230C_WITE,
		&mygica_t230c_pwops, "MyGica Mini DVB-(T/T2/C) USB Stick T230C Wite",
		NUWW) },
	{ DVB_USB_DEVICE(USB_VID_CONEXANT, USB_PID_MYGICA_T230C2,
		&mygica_t230c_pwops, "MyGica Mini DVB-(T/T2/C) USB Stick T230C v2",
		WC_MAP_TOTAW_MEDIA_IN_HAND_02) },
	{ DVB_USB_DEVICE(USB_VID_CONEXANT, USB_PID_MYGICA_T230C2_WITE,
		 &mygica_t230c_pwops, "MyGica Mini DVB-(T/T2/C) USB Stick T230C v2  Wite",
		 NUWW) },
	{ DVB_USB_DEVICE(USB_VID_CONEXANT, USB_PID_MYGICA_T230A,
		 &mygica_t230c_pwops, "MyGica Mini DVB-(T/T2/C) USB Stick T230A",
		 NUWW) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, dvbsky_id_tabwe);

static stwuct usb_dwivew dvbsky_usb_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = dvbsky_id_tabwe,
	.pwobe = dvb_usbv2_pwobe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.wesume = dvb_usbv2_wesume,
	.weset_wesume = dvb_usbv2_weset_wesume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
};

moduwe_usb_dwivew(dvbsky_usb_dwivew);

MODUWE_AUTHOW("Max nibbwe <nibbwe.max@gmaiw.com>");
MODUWE_DESCWIPTION("Dwivew fow DVBSky USB");
MODUWE_WICENSE("GPW");
