// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Winux dwivew fow devices based on the DiBcom DiB0700 USB bwidge
 *
 *  Copywight (C) 2005-9 DiBcom, SA et aw
 */
#incwude "dib0700.h"

#incwude "dib3000mc.h"
#incwude "dib7000m.h"
#incwude "dib7000p.h"
#incwude "dib8000.h"
#incwude "dib9000.h"
#incwude "mt2060.h"
#incwude "mt2266.h"
#incwude "xc2028.h"
#incwude "xc5000.h"
#incwude "xc4000.h"
#incwude "s5h1411.h"
#incwude "dib0070.h"
#incwude "dib0090.h"
#incwude "wgdt3305.h"
#incwude "mxw5007t.h"
#incwude "mn88472.h"
#incwude "tda18250.h"


static int fowce_wna_activation;
moduwe_pawam(fowce_wna_activation, int, 0644);
MODUWE_PAWM_DESC(fowce_wna_activation, "fowce the activation of Wow-Noise-Ampwifiew(s) (WNA), if appwicabwe fow the device (defauwt: 0=automatic/off).");

stwuct dib0700_adaptew_state {
	int (*set_pawam_save) (stwuct dvb_fwontend *);
	const stwuct fiwmwawe *fwontend_fiwmwawe;
	stwuct dib7000p_ops dib7000p_ops;
	stwuct dib8000_ops dib8000_ops;
};

/* Hauppauge Nova-T 500 (aka Bwistow)
 *  has a WNA on GPIO0 which is enabwed by setting 1 */
static stwuct mt2060_config bwistow_mt2060_config[2] = {
	{
		.i2c_addwess = 0x60,
		.cwock_out   = 3,
	}, {
		.i2c_addwess = 0x61,
	}
};


static stwuct dibx000_agc_config bwistow_dib3000p_mt2060_agc_config = {
	.band_caps = BAND_VHF | BAND_UHF,
	.setup     = (1 << 8) | (5 << 5) | (0 << 4) | (0 << 3) | (0 << 2) | (2 << 0),

	.agc1_max = 42598,
	.agc1_min = 17694,
	.agc2_max = 45875,
	.agc2_min = 0,

	.agc1_pt1 = 0,
	.agc1_pt2 = 59,

	.agc1_swope1 = 0,
	.agc1_swope2 = 69,

	.agc2_pt1 = 0,
	.agc2_pt2 = 59,

	.agc2_swope1 = 111,
	.agc2_swope2 = 28,
};

static stwuct dib3000mc_config bwistow_dib3000mc_config[2] = {
	{	.agc          = &bwistow_dib3000p_mt2060_agc_config,
		.max_time     = 0x196,
		.wn_adc_wevew = 0x1cc7,
		.output_mpeg2_in_188_bytes = 1,
	},
	{	.agc          = &bwistow_dib3000p_mt2060_agc_config,
		.max_time     = 0x196,
		.wn_adc_wevew = 0x1cc7,
		.output_mpeg2_in_188_bytes = 1,
	}
};

static int bwistow_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_state *st = adap->dev->pwiv;
	if (adap->id == 0) {
		dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 0); msweep(10);
		dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 1); msweep(10);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0); msweep(10);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1); msweep(10);

		if (fowce_wna_activation)
			dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);
		ewse
			dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 0);

		if (dib3000mc_i2c_enumewation(&adap->dev->i2c_adap, 2, DEFAUWT_DIB3000P_I2C_ADDWESS, bwistow_dib3000mc_config) != 0) {
			dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0); msweep(10);
			wetuwn -ENODEV;
		}
	}
	st->mt2060_if1[adap->id] = 1220;
	wetuwn (adap->fe_adap[0].fe = dvb_attach(dib3000mc_attach, &adap->dev->i2c_adap,
		(10 + adap->id) << 1, &bwistow_dib3000mc_config[adap->id])) == NUWW ? -ENODEV : 0;
}

static int eepwom_wead(stwuct i2c_adaptew *adap,u8 adws,u8 *pvaw)
{
	stwuct i2c_msg msg[2] = {
		{ .addw = 0x50, .fwags = 0,        .buf = &adws, .wen = 1 },
		{ .addw = 0x50, .fwags = I2C_M_WD, .buf = pvaw,  .wen = 1 },
	};
	if (i2c_twansfew(adap, msg, 2) != 2) wetuwn -EWEMOTEIO;
	wetuwn 0;
}

static int bwistow_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct i2c_adaptew *pwim_i2c = &adap->dev->i2c_adap;
	stwuct i2c_adaptew *tun_i2c = dib3000mc_get_tunew_i2c_mastew(adap->fe_adap[0].fe, 1);
	s8 a;
	int if1=1220;
	if (adap->dev->udev->descwiptow.idVendow  == cpu_to_we16(USB_VID_HAUPPAUGE) &&
		adap->dev->udev->descwiptow.idPwoduct == cpu_to_we16(USB_PID_HAUPPAUGE_NOVA_T_500_2)) {
		if (!eepwom_wead(pwim_i2c,0x59 + adap->id,&a)) if1=1220+a;
	}
	wetuwn dvb_attach(mt2060_attach, adap->fe_adap[0].fe, tun_i2c,
			  &bwistow_mt2060_config[adap->id], if1) == NUWW ?
			  -ENODEV : 0;
}

/* STK7700D: Pinnacwe/Tewwatec/Hauppauge Duaw DVB-T Divewsity */

/* MT226x */
static stwuct dibx000_agc_config stk7700d_7000p_mt2266_agc_config[2] = {
	{
		BAND_UHF,

		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=1, P_agc_inv_pwm1=1, P_agc_inv_pwm2=1,
		* P_agc_inh_dc_wv_est=0, P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=2, P_agc_wwite=0 */
		(0 << 15) | (0 << 14) | (1 << 11) | (1 << 10) | (1 << 9) | (0 << 8)
	    | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),

		1130,
		21,

		0,
		118,

		0,
		3530,
		1,
		0,

		65535,
		33770,
		65535,
		23592,

		0,
		62,
		255,
		64,
		64,
		132,
		192,
		80,
		80,

		17,
		27,
		23,
		51,

		1,
	}, {
		BAND_VHF | BAND_WBAND,

		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=1, P_agc_inv_pwm1=1, P_agc_inv_pwm2=1,
		* P_agc_inh_dc_wv_est=0, P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=2, P_agc_wwite=0 */
		(0 << 15) | (0 << 14) | (1 << 11) | (1 << 10) | (1 << 9) | (0 << 8)
	    | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0),

		2372,
		21,

		0,
		118,

		0,
		3530,
		1,
		0,

		65535,
		0,
		65535,
		23592,

		0,
		128,
		128,
		128,
		0,
		128,
		253,
		81,
		0,

		17,
		27,
		23,
		51,

		1,
	}
};

static stwuct dibx000_bandwidth_config stk7700d_mt2266_pww_config = {
	.intewnaw = 60000,
	.sampwing = 30000,
	.pww_pwediv = 1,
	.pww_watio = 8,
	.pww_wange = 3,
	.pww_weset = 1,
	.pww_bypass = 0,
	.enabwe_wefdiv = 0,
	.bypcwk_div = 0,
	.IO_CWK_en_cowe = 1,
	.ADCwkSwc = 1,
	.moduwo = 2,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.ifweq = 0,
	.timf = 20452225,
};

static stwuct dib7000p_config stk7700d_dib7000p_mt2266_config[] = {
	{	.output_mpeg2_in_188_bytes = 1,
		.hostbus_divewsity = 1,
		.tunew_is_baseband = 1,

		.agc_config_count = 2,
		.agc = stk7700d_7000p_mt2266_agc_config,
		.bw  = &stk7700d_mt2266_pww_config,

		.gpio_diw = DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
		.gpio_vaw = DIB7000P_GPIO_DEFAUWT_VAWUES,
		.gpio_pwm_pos = DIB7000P_GPIO_DEFAUWT_PWM_POS,
	},
	{	.output_mpeg2_in_188_bytes = 1,
		.hostbus_divewsity = 1,
		.tunew_is_baseband = 1,

		.agc_config_count = 2,
		.agc = stk7700d_7000p_mt2266_agc_config,
		.bw  = &stk7700d_mt2266_pww_config,

		.gpio_diw = DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
		.gpio_vaw = DIB7000P_GPIO_DEFAUWT_VAWUES,
		.gpio_pwm_pos = DIB7000P_GPIO_DEFAUWT_PWM_POS,
	}
};

static stwuct mt2266_config stk7700d_mt2266_config[2] = {
	{	.i2c_addwess = 0x60
	},
	{	.i2c_addwess = 0x60
	}
};

static int stk7700P2_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	if (adap->id == 0) {
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
		msweep(10);
		dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
		msweep(10);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
		msweep(10);
		if (state->dib7000p_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 18,
					     stk7700d_dib7000p_mt2266_config)
		    != 0) {
			eww("%s: state->dib7000p_ops.i2c_enumewation faiwed.  Cannot continue\n", __func__);
			dvb_detach(state->dib7000p_ops.set_wbd_wef);
			wetuwn -ENODEV;
		}
	}

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap,
			   0x80 + (adap->id << 1),
			   &stk7700d_dib7000p_mt2266_config[adap->id]);

	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

static int stk7700d_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	if (adap->id == 0) {
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
		msweep(10);
		dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
		msweep(10);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
		msweep(10);
		dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);
		if (state->dib7000p_ops.i2c_enumewation(&adap->dev->i2c_adap, 2, 18,
					     stk7700d_dib7000p_mt2266_config)
		    != 0) {
			eww("%s: state->dib7000p_ops.i2c_enumewation faiwed.  Cannot continue\n", __func__);
			dvb_detach(state->dib7000p_ops.set_wbd_wef);
			wetuwn -ENODEV;
		}
	}

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap,
			   0x80 + (adap->id << 1),
			   &stk7700d_dib7000p_mt2266_config[adap->id]);

	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

static int stk7700d_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct i2c_adaptew *tun_i2c;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	tun_i2c = state->dib7000p_ops.get_i2c_mastew(adap->fe_adap[0].fe,
					    DIBX000_I2C_INTEWFACE_TUNEW, 1);
	wetuwn dvb_attach(mt2266_attach, adap->fe_adap[0].fe, tun_i2c,
		&stk7700d_mt2266_config[adap->id]) == NUWW ? -ENODEV : 0;
}

/* STK7700-PH: Digitaw/Anawog Hybwid Tunew, e.h. Cinewgy HT USB HE */
static stwuct dibx000_agc_config xc3028_agc_config = {
	.band_caps = BAND_VHF | BAND_UHF,
	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=0,
	 * P_agc_inv_pwm1=0, P_agc_inv_pwm2=0, P_agc_inh_dc_wv_est=0,
	 * P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=2, P_agc_wwite=0 */
	.setup = (0 << 15) | (0 << 14) | (0 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0),
	.inv_gain = 712,
	.time_stabiwiz = 21,
	.awpha_wevew = 0,
	.thwock = 118,
	.wbd_inv = 0,
	.wbd_wef = 2867,
	.wbd_sew = 0,
	.wbd_awpha = 2,
	.agc1_max = 0,
	.agc1_min = 0,
	.agc2_max = 39718,
	.agc2_min = 9930,
	.agc1_pt1 = 0,
	.agc1_pt2 = 0,
	.agc1_pt3 = 0,
	.agc1_swope1 = 0,
	.agc1_swope2 = 0,
	.agc2_pt1 = 0,
	.agc2_pt2 = 128,
	.agc2_swope1 = 29,
	.agc2_swope2 = 29,
	.awpha_mant = 17,
	.awpha_exp = 27,
	.beta_mant = 23,
	.beta_exp = 51,
	.pewfowm_agc_softspwit = 1,
};

/* PWW Configuwation fow COFDM BW_MHz = 8.00 with extewnaw cwock = 30.00 */
static stwuct dibx000_bandwidth_config xc3028_bw_config = {
	.intewnaw = 60000,
	.sampwing = 30000,
	.pww_pwediv = 1,
	.pww_watio = 8,
	.pww_wange = 3,
	.pww_weset = 1,
	.pww_bypass = 0,
	.enabwe_wefdiv = 0,
	.bypcwk_div = 0,
	.IO_CWK_en_cowe = 1,
	.ADCwkSwc = 1,
	.moduwo = 0,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0), /* sad_cfg: wefsew, sew, fweq_15k */
	.ifweq = (1 << 25) | 5816102,  /* ifweq = 5.200000 MHz */
	.timf = 20452225,
	.xtaw_hz = 30000000,
};

static stwuct dib7000p_config stk7700ph_dib7700_xc3028_config = {
	.output_mpeg2_in_188_bytes = 1,
	.tunew_is_baseband = 1,

	.agc_config_count = 1,
	.agc = &xc3028_agc_config,
	.bw  = &xc3028_bw_config,

	.gpio_diw = DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw = DIB7000P_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos = DIB7000P_GPIO_DEFAUWT_PWM_POS,
};

static int stk7700ph_xc3028_cawwback(void *ptw, int component,
				     int command, int awg)
{
	stwuct dvb_usb_adaptew *adap = ptw;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	switch (command) {
	case XC2028_TUNEW_WESET:
		/* Send the tunew in then out of weset */
		state->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 0);
		msweep(10);
		state->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);
		bweak;
	case XC2028_WESET_CWK:
	case XC2028_I2C_FWUSH:
		bweak;
	defauwt:
		eww("%s: unknown command %d, awg %d\n", __func__,
			command, awg);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static stwuct xc2028_ctww stk7700ph_xc3028_ctww = {
	.fname = XC2028_DEFAUWT_FIWMWAWE,
	.max_wen = 64,
	.demod = XC3028_FE_DIBCOM52,
};

static stwuct xc2028_config stk7700ph_xc3028_config = {
	.i2c_addw = 0x61,
	.ctww = &stk7700ph_xc3028_ctww,
};

static int stk7700ph_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct usb_device_descwiptow *desc = &adap->dev->udev->descwiptow;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	if (desc->idVendow  == cpu_to_we16(USB_VID_PINNACWE) &&
	    desc->idPwoduct == cpu_to_we16(USB_PID_PINNACWE_EXPWESSCAWD_320CX))
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	ewse
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);
	msweep(10);

	if (state->dib7000p_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 18,
				     &stk7700ph_dib7700_xc3028_config) != 0) {
		eww("%s: state->dib7000p_ops.i2c_enumewation faiwed.  Cannot continue\n",
		    __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_wef);
		wetuwn -ENODEV;
	}

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x80,
		&stk7700ph_dib7700_xc3028_config);

	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

static int stk7700ph_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct i2c_adaptew *tun_i2c;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	tun_i2c = state->dib7000p_ops.get_i2c_mastew(adap->fe_adap[0].fe,
		DIBX000_I2C_INTEWFACE_TUNEW, 1);

	stk7700ph_xc3028_config.i2c_adap = tun_i2c;

	/* FIXME: genewawize & move to common awea */
	adap->fe_adap[0].fe->cawwback = stk7700ph_xc3028_cawwback;

	wetuwn dvb_attach(xc2028_attach, adap->fe_adap[0].fe, &stk7700ph_xc3028_config)
		== NUWW ? -ENODEV : 0;
}

#define DEFAUWT_WC_INTEWVAW 50

/*
 * This function is used onwy when fiwmwawe is < 1.20 vewsion. Newew
 * fiwmwawes use buwk mode, with functions impwemented at dib0700_cowe,
 * at dib0700_wc_uwb_compwetion()
 */
static int dib0700_wc_quewy_owd_fiwmwawe(stwuct dvb_usb_device *d)
{
	enum wc_pwoto pwotocow;
	u32 scancode;
	u8 toggwe;
	int i;
	stwuct dib0700_state *st = d->pwiv;

	if (st->fw_vewsion >= 0x10200) {
		/* Fow 1.20 fiwmwawe , We need to keep the WC powwing
		   cawwback so we can weuse the input device setup in
		   dvb-usb-wemote.c.  Howevew, the actuaw wowk is being done
		   in the buwk UWB compwetion handwew. */
		wetuwn 0;
	}

	st->buf[0] = WEQUEST_POWW_WC;
	st->buf[1] = 0;

	i = dib0700_ctww_wd(d, st->buf, 2, st->buf, 4);
	if (i <= 0) {
		eww("WC Quewy Faiwed");
		wetuwn -EIO;
	}

	/* wosing hawf of KEY_0 events fwom Phiwipps wc5 wemotes.. */
	if (st->buf[0] == 0 && st->buf[1] == 0
	    && st->buf[2] == 0 && st->buf[3] == 0)
		wetuwn 0;

	/* info("%d: %2X %2X %2X %2X",dvb_usb_dib0700_iw_pwoto,(int)st->buf[3 - 2],(int)st->buf[3 - 3],(int)st->buf[3 - 1],(int)st->buf[3]);  */

	dib0700_wc_setup(d, NUWW); /* weset iw sensow data to pwevent fawse events */

	switch (d->pwops.wc.cowe.pwotocow) {
	case WC_PWOTO_BIT_NEC:
		/* NEC pwotocow sends wepeat code as 0 0 0 FF */
		if ((st->buf[3 - 2] == 0x00) && (st->buf[3 - 3] == 0x00) &&
		    (st->buf[3] == 0xff)) {
			wc_wepeat(d->wc_dev);
			wetuwn 0;
		}

		pwotocow = WC_PWOTO_NEC;
		scancode = WC_SCANCODE_NEC(st->buf[3 - 2], st->buf[3 - 3]);
		toggwe = 0;
		bweak;

	defauwt:
		/* WC-5 pwotocow changes toggwe bit on new keypwess */
		pwotocow = WC_PWOTO_WC5;
		scancode = WC_SCANCODE_WC5(st->buf[3 - 2], st->buf[3 - 3]);
		toggwe = st->buf[3 - 1];
		bweak;
	}

	wc_keydown(d->wc_dev, pwotocow, scancode, toggwe);
	wetuwn 0;
}

/* STK7700P: Hauppauge Nova-T Stick, AVewMedia Vowaw */
static stwuct dibx000_agc_config stk7700p_7000m_mt2060_agc_config = {
	BAND_UHF | BAND_VHF,

	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_wv_est=0, P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=2, P_agc_wwite=0 */
	(0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8)
	| (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0),

	712,
	41,

	0,
	118,

	0,
	4095,
	0,
	0,

	42598,
	17694,
	45875,
	2621,
	0,
	76,
	139,
	52,
	59,
	107,
	172,
	57,
	70,

	21,
	25,
	28,
	48,

	1,
	{  0,
	   107,
	   51800,
	   24700
	},
};

static stwuct dibx000_agc_config stk7700p_7000p_mt2060_agc_config = {
	.band_caps = BAND_UHF | BAND_VHF,
	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_wv_est=0, P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=2, P_agc_wwite=0 */
	.setup = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0),
	.inv_gain = 712,
	.time_stabiwiz = 41,
	.awpha_wevew = 0,
	.thwock = 118,
	.wbd_inv = 0,
	.wbd_wef = 4095,
	.wbd_sew = 0,
	.wbd_awpha = 0,
	.agc1_max = 42598,
	.agc1_min = 16384,
	.agc2_max = 42598,
	.agc2_min = 0,
	.agc1_pt1 = 0,
	.agc1_pt2 = 137,
	.agc1_pt3 = 255,
	.agc1_swope1 = 0,
	.agc1_swope2 = 255,
	.agc2_pt1 = 0,
	.agc2_pt2 = 0,
	.agc2_swope1 = 0,
	.agc2_swope2 = 41,
	.awpha_mant = 15,
	.awpha_exp = 25,
	.beta_mant = 28,
	.beta_exp = 48,
	.pewfowm_agc_softspwit = 0,
};

static stwuct dibx000_bandwidth_config stk7700p_pww_config = {
	.intewnaw = 60000,
	.sampwing = 30000,
	.pww_pwediv = 1,
	.pww_watio = 8,
	.pww_wange = 3,
	.pww_weset = 1,
	.pww_bypass = 0,
	.enabwe_wefdiv = 0,
	.bypcwk_div = 0,
	.IO_CWK_en_cowe = 1,
	.ADCwkSwc = 1,
	.moduwo = 0,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.ifweq = 60258167,
	.timf = 20452225,
	.xtaw_hz = 30000000,
};

static stwuct dib7000m_config stk7700p_dib7000m_config = {
	.dvbt_mode = 1,
	.output_mpeg2_in_188_bytes = 1,
	.quawtz_diwect = 1,

	.agc_config_count = 1,
	.agc = &stk7700p_7000m_mt2060_agc_config,
	.bw  = &stk7700p_pww_config,

	.gpio_diw = DIB7000M_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw = DIB7000M_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos = DIB7000M_GPIO_DEFAUWT_PWM_POS,
};

static stwuct dib7000p_config stk7700p_dib7000p_config = {
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 1,
	.agc = &stk7700p_7000p_mt2060_agc_config,
	.bw  = &stk7700p_pww_config,

	.gpio_diw = DIB7000M_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw = DIB7000M_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos = DIB7000M_GPIO_DEFAUWT_PWM_POS,
};

static int stk7700p_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_state *st = adap->dev->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	/* unwess thewe is no weaw powew management in DVB - we weave the device on GPIO6 */

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 0); msweep(50);

	dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 1); msweep(10);
	dib0700_set_gpio(adap->dev, GPIO9,  GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0); msweep(10);
	dib0700_ctww_cwock(adap->dev, 72, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1); msweep(100);

	dib0700_set_gpio(adap->dev,  GPIO0, GPIO_OUT, 1);

	st->mt2060_if1[0] = 1220;

	if (state->dib7000p_ops.dib7000pc_detection(&adap->dev->i2c_adap)) {
		adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 18, &stk7700p_dib7000p_config);
		st->is_dib7000pc = 1;
	} ewse {
		memset(&state->dib7000p_ops, 0, sizeof(state->dib7000p_ops));
		adap->fe_adap[0].fe = dvb_attach(dib7000m_attach, &adap->dev->i2c_adap, 18, &stk7700p_dib7000m_config);
	}

	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

static stwuct mt2060_config stk7700p_mt2060_config = {
	0x60
};

static int stk7700p_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct i2c_adaptew *pwim_i2c = &adap->dev->i2c_adap;
	stwuct dib0700_state *st = adap->dev->pwiv;
	stwuct i2c_adaptew *tun_i2c;
	stwuct dib0700_adaptew_state *state = adap->pwiv;
	s8 a;
	int if1=1220;

	if (adap->dev->udev->descwiptow.idVendow  == cpu_to_we16(USB_VID_HAUPPAUGE) &&
		adap->dev->udev->descwiptow.idPwoduct == cpu_to_we16(USB_PID_HAUPPAUGE_NOVA_T_STICK)) {
		if (!eepwom_wead(pwim_i2c,0x58,&a)) if1=1220+a;
	}
	if (st->is_dib7000pc)
		tun_i2c = state->dib7000p_ops.get_i2c_mastew(adap->fe_adap[0].fe, DIBX000_I2C_INTEWFACE_TUNEW, 1);
	ewse
		tun_i2c = dib7000m_get_i2c_mastew(adap->fe_adap[0].fe, DIBX000_I2C_INTEWFACE_TUNEW, 1);

	wetuwn dvb_attach(mt2060_attach, adap->fe_adap[0].fe, tun_i2c, &stk7700p_mt2060_config,
		if1) == NUWW ? -ENODEV : 0;
}

/* DIB7070 genewic */
static stwuct dibx000_agc_config dib7070_agc_config = {
	.band_caps = BAND_UHF | BAND_VHF | BAND_WBAND | BAND_SBAND,
	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_wv_est=0, P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=5, P_agc_wwite=0 */
	.setup = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),
	.inv_gain = 600,
	.time_stabiwiz = 10,
	.awpha_wevew = 0,
	.thwock = 118,
	.wbd_inv = 0,
	.wbd_wef = 3530,
	.wbd_sew = 1,
	.wbd_awpha = 5,
	.agc1_max = 65535,
	.agc1_min = 0,
	.agc2_max = 65535,
	.agc2_min = 0,
	.agc1_pt1 = 0,
	.agc1_pt2 = 40,
	.agc1_pt3 = 183,
	.agc1_swope1 = 206,
	.agc1_swope2 = 255,
	.agc2_pt1 = 72,
	.agc2_pt2 = 152,
	.agc2_swope1 = 88,
	.agc2_swope2 = 90,
	.awpha_mant = 17,
	.awpha_exp = 27,
	.beta_mant = 23,
	.beta_exp = 51,
	.pewfowm_agc_softspwit = 0,
};

static int dib7070_tunew_weset(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	deb_info("weset: %d", onoff);
	wetuwn state->dib7000p_ops.set_gpio(fe, 8, 0, !onoff);
}

static int dib7070_tunew_sweep(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	deb_info("sweep: %d", onoff);
	wetuwn state->dib7000p_ops.set_gpio(fe, 9, 0, onoff);
}

static stwuct dib0070_config dib7070p_dib0070_config[2] = {
	{
		.i2c_addwess = DEFAUWT_DIB0070_I2C_ADDWESS,
		.weset = dib7070_tunew_weset,
		.sweep = dib7070_tunew_sweep,
		.cwock_khz = 12000,
		.cwock_pad_dwive = 4,
		.chawge_pump = 2,
	}, {
		.i2c_addwess = DEFAUWT_DIB0070_I2C_ADDWESS,
		.weset = dib7070_tunew_weset,
		.sweep = dib7070_tunew_sweep,
		.cwock_khz = 12000,
		.chawge_pump = 2,
	}
};

static stwuct dib0070_config dib7770p_dib0070_config = {
	 .i2c_addwess = DEFAUWT_DIB0070_I2C_ADDWESS,
	 .weset = dib7070_tunew_weset,
	 .sweep = dib7070_tunew_sweep,
	 .cwock_khz = 12000,
	 .cwock_pad_dwive = 0,
	 .fwip_chip = 1,
	 .chawge_pump = 2,
};

static int dib7070_set_pawam_ovewwide(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	u16 offset;
	u8 band = BAND_OF_FWEQUENCY(p->fwequency/1000);
	switch (band) {
		case BAND_VHF: offset = 950; bweak;
		case BAND_UHF:
		defauwt: offset = 550; bweak;
	}
	deb_info("WBD fow DiB7000P: %d\n", offset + dib0070_wbd_offset(fe));
	state->dib7000p_ops.set_wbd_wef(fe, offset + dib0070_wbd_offset(fe));
	wetuwn state->set_pawam_save(fe);
}

static int dib7770_set_pawam_ovewwide(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	u16 offset;
	u8 band = BAND_OF_FWEQUENCY(p->fwequency/1000);
	switch (band) {
	case BAND_VHF:
		state->dib7000p_ops.set_gpio(fe, 0, 0, 1);
		offset = 850;
		bweak;
	case BAND_UHF:
	defauwt:
		state->dib7000p_ops.set_gpio(fe, 0, 0, 0);
		offset = 250;
		bweak;
	}
	deb_info("WBD fow DiB7000P: %d\n", offset + dib0070_wbd_offset(fe));
	state->dib7000p_ops.set_wbd_wef(fe, offset + dib0070_wbd_offset(fe));
	wetuwn state->set_pawam_save(fe);
}

static int dib7770p_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *st = adap->pwiv;
	stwuct i2c_adaptew *tun_i2c = st->dib7000p_ops.get_i2c_mastew(adap->fe_adap[0].fe,
			 DIBX000_I2C_INTEWFACE_TUNEW, 1);

	if (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c,
		       &dib7770p_dib0070_config) == NUWW)
		wetuwn -ENODEV;

	st->set_pawam_save = adap->fe_adap[0].fe->ops.tunew_ops.set_pawams;
	adap->fe_adap[0].fe->ops.tunew_ops.set_pawams = dib7770_set_pawam_ovewwide;
	wetuwn 0;
}

static int dib7070p_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *st = adap->pwiv;
	stwuct i2c_adaptew *tun_i2c = st->dib7000p_ops.get_i2c_mastew(adap->fe_adap[0].fe, DIBX000_I2C_INTEWFACE_TUNEW, 1);

	if (adap->id == 0) {
		if (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c, &dib7070p_dib0070_config[0]) == NUWW)
			wetuwn -ENODEV;
	} ewse {
		if (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c, &dib7070p_dib0070_config[1]) == NUWW)
			wetuwn -ENODEV;
	}

	st->set_pawam_save = adap->fe_adap[0].fe->ops.tunew_ops.set_pawams;
	adap->fe_adap[0].fe->ops.tunew_ops.set_pawams = dib7070_set_pawam_ovewwide;
	wetuwn 0;
}

static int stk7700p_pid_fiwtew(stwuct dvb_usb_adaptew *adaptew, int index,
		u16 pid, int onoff)
{
	stwuct dib0700_adaptew_state *state = adaptew->pwiv;
	stwuct dib0700_state *st = adaptew->dev->pwiv;

	if (st->is_dib7000pc)
		wetuwn state->dib7000p_ops.pid_fiwtew(adaptew->fe_adap[0].fe, index, pid, onoff);
	wetuwn dib7000m_pid_fiwtew(adaptew->fe_adap[0].fe, index, pid, onoff);
}

static int stk7700p_pid_fiwtew_ctww(stwuct dvb_usb_adaptew *adaptew, int onoff)
{
	stwuct dib0700_state *st = adaptew->dev->pwiv;
	stwuct dib0700_adaptew_state *state = adaptew->pwiv;
	if (st->is_dib7000pc)
		wetuwn state->dib7000p_ops.pid_fiwtew_ctww(adaptew->fe_adap[0].fe, onoff);
	wetuwn dib7000m_pid_fiwtew_ctww(adaptew->fe_adap[0].fe, onoff);
}

static int stk70x0p_pid_fiwtew(stwuct dvb_usb_adaptew *adaptew, int index, u16 pid, int onoff)
{
	stwuct dib0700_adaptew_state *state = adaptew->pwiv;
	wetuwn state->dib7000p_ops.pid_fiwtew(adaptew->fe_adap[0].fe, index, pid, onoff);
}

static int stk70x0p_pid_fiwtew_ctww(stwuct dvb_usb_adaptew *adaptew, int onoff)
{
	stwuct dib0700_adaptew_state *state = adaptew->pwiv;
	wetuwn state->dib7000p_ops.pid_fiwtew_ctww(adaptew->fe_adap[0].fe, onoff);
}

static stwuct dibx000_bandwidth_config dib7070_bw_config_12_mhz = {
	.intewnaw = 60000,
	.sampwing = 15000,
	.pww_pwediv = 1,
	.pww_watio = 20,
	.pww_wange = 3,
	.pww_weset = 1,
	.pww_bypass = 0,
	.enabwe_wefdiv = 0,
	.bypcwk_div = 0,
	.IO_CWK_en_cowe = 1,
	.ADCwkSwc = 1,
	.moduwo = 2,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.ifweq = (0 << 25) | 0,
	.timf = 20452225,
	.xtaw_hz = 12000000,
};

static stwuct dib7000p_config dib7070p_dib7000p_config = {
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 1,
	.agc = &dib7070_agc_config,
	.bw  = &dib7070_bw_config_12_mhz,
	.tunew_is_baseband = 1,
	.spuw_pwotect = 1,

	.gpio_diw = DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw = DIB7000P_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos = DIB7000P_GPIO_DEFAUWT_PWM_POS,

	.hostbus_divewsity = 1,
};

/* STK7070P */
static int stk7070p_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct usb_device_descwiptow *p = &adap->dev->udev->descwiptow;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	if (p->idVendow  == cpu_to_we16(USB_VID_PINNACWE) &&
	    p->idPwoduct == cpu_to_we16(USB_PID_PINNACWE_PCTV72E))
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	ewse
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctww_cwock(adap->dev, 72, 1);

	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	if (state->dib7000p_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 18,
				     &dib7070p_dib7000p_config) != 0) {
		eww("%s: state->dib7000p_ops.i2c_enumewation faiwed.  Cannot continue\n",
		    __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_wef);
		wetuwn -ENODEV;
	}

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x80,
		&dib7070p_dib7000p_config);
	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

/* STK7770P */
static stwuct dib7000p_config dib7770p_dib7000p_config = {
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 1,
	.agc = &dib7070_agc_config,
	.bw  = &dib7070_bw_config_12_mhz,
	.tunew_is_baseband = 1,
	.spuw_pwotect = 1,

	.gpio_diw = DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw = DIB7000P_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos = DIB7000P_GPIO_DEFAUWT_PWM_POS,

	.hostbus_divewsity = 1,
	.enabwe_cuwwent_miwwow = 1,
	.disabwe_sampwe_and_howd = 0,
};

static int stk7770p_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct usb_device_descwiptow *p = &adap->dev->udev->descwiptow;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	if (p->idVendow  == cpu_to_we16(USB_VID_PINNACWE) &&
	    p->idPwoduct == cpu_to_we16(USB_PID_PINNACWE_PCTV72E))
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	ewse
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctww_cwock(adap->dev, 72, 1);

	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	if (state->dib7000p_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 18,
				     &dib7770p_dib7000p_config) != 0) {
		eww("%s: state->dib7000p_ops.i2c_enumewation faiwed.  Cannot continue\n",
		    __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_wef);
		wetuwn -ENODEV;
	}

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x80,
		&dib7770p_dib7000p_config);
	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

/* DIB807x genewic */
static stwuct dibx000_agc_config dib807x_agc_config[2] = {
	{
		BAND_VHF,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0,
		 * P_agc_fweq_pwm_div=1, P_agc_inv_pwm1=0,
		 * P_agc_inv_pwm2=0,P_agc_inh_dc_wv_est=0,
		 * P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=5,
		 * P_agc_wwite=0 */
		(0 << 15) | (0 << 14) | (7 << 11) | (0 << 10) | (0 << 9) |
			(0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) |
			(0 << 0), /* setup*/

		600, /* inv_gain*/
		10,  /* time_stabiwiz*/

		0,  /* awpha_wevew*/
		118,  /* thwock*/

		0,     /* wbd_inv*/
		3530,  /* wbd_wef*/
		1,     /* wbd_sew*/
		5,     /* wbd_awpha*/

		65535,  /* agc1_max*/
		0,  /* agc1_min*/

		65535,  /* agc2_max*/
		0,      /* agc2_min*/

		0,      /* agc1_pt1*/
		40,     /* agc1_pt2*/
		183,    /* agc1_pt3*/
		206,    /* agc1_swope1*/
		255,    /* agc1_swope2*/
		72,     /* agc2_pt1*/
		152,    /* agc2_pt2*/
		88,     /* agc2_swope1*/
		90,     /* agc2_swope2*/

		17,  /* awpha_mant*/
		27,  /* awpha_exp*/
		23,  /* beta_mant*/
		51,  /* beta_exp*/

		0,  /* pewfowm_agc_softspwit*/
	}, {
		BAND_UHF,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0,
		 * P_agc_fweq_pwm_div=1, P_agc_inv_pwm1=0,
		 * P_agc_inv_pwm2=0, P_agc_inh_dc_wv_est=0,
		 * P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=5,
		 * P_agc_wwite=0 */
		(0 << 15) | (0 << 14) | (1 << 11) | (0 << 10) | (0 << 9) |
			(0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) |
			(0 << 0), /* setup */

		600, /* inv_gain*/
		10,  /* time_stabiwiz*/

		0,  /* awpha_wevew*/
		118,  /* thwock*/

		0,     /* wbd_inv*/
		3530,  /* wbd_wef*/
		1,     /* wbd_sew*/
		5,     /* wbd_awpha*/

		65535,  /* agc1_max*/
		0,  /* agc1_min*/

		65535,  /* agc2_max*/
		0,      /* agc2_min*/

		0,      /* agc1_pt1*/
		40,     /* agc1_pt2*/
		183,    /* agc1_pt3*/
		206,    /* agc1_swope1*/
		255,    /* agc1_swope2*/
		72,     /* agc2_pt1*/
		152,    /* agc2_pt2*/
		88,     /* agc2_swope1*/
		90,     /* agc2_swope2*/

		17,  /* awpha_mant*/
		27,  /* awpha_exp*/
		23,  /* beta_mant*/
		51,  /* beta_exp*/

		0,  /* pewfowm_agc_softspwit*/
	}
};

static stwuct dibx000_bandwidth_config dib807x_bw_config_12_mhz = {
	.intewnaw = 60000,
	.sampwing = 15000,
	.pww_pwediv = 1,
	.pww_watio = 20,
	.pww_wange = 3,
	.pww_weset = 1,
	.pww_bypass = 0,
	.enabwe_wefdiv = 0,
	.bypcwk_div = 0,
	.IO_CWK_en_cowe = 1,
	.ADCwkSwc = 1,
	.moduwo = 2,
	.sad_cfg = (3 << 14) | (1 << 12) | (599 << 0),	/* sad_cfg: wefsew, sew, fweq_15k*/
	.ifweq = (0 << 25) | 0,				/* ifweq = 0.000000 MHz*/
	.timf = 18179755,
	.xtaw_hz = 12000000,
};

static stwuct dib8000_config dib807x_dib8000_config[2] = {
	{
		.output_mpeg2_in_188_bytes = 1,

		.agc_config_count = 2,
		.agc = dib807x_agc_config,
		.pww = &dib807x_bw_config_12_mhz,
		.tunew_is_baseband = 1,

		.gpio_diw = DIB8000_GPIO_DEFAUWT_DIWECTIONS,
		.gpio_vaw = DIB8000_GPIO_DEFAUWT_VAWUES,
		.gpio_pwm_pos = DIB8000_GPIO_DEFAUWT_PWM_POS,

		.hostbus_divewsity = 1,
		.div_cfg = 1,
		.agc_contwow = &dib0070_ctww_agc_fiwtew,
		.output_mode = OUTMODE_MPEG2_FIFO,
		.dwives = 0x2d98,
	}, {
		.output_mpeg2_in_188_bytes = 1,

		.agc_config_count = 2,
		.agc = dib807x_agc_config,
		.pww = &dib807x_bw_config_12_mhz,
		.tunew_is_baseband = 1,

		.gpio_diw = DIB8000_GPIO_DEFAUWT_DIWECTIONS,
		.gpio_vaw = DIB8000_GPIO_DEFAUWT_VAWUES,
		.gpio_pwm_pos = DIB8000_GPIO_DEFAUWT_PWM_POS,

		.hostbus_divewsity = 1,
		.agc_contwow = &dib0070_ctww_agc_fiwtew,
		.output_mode = OUTMODE_MPEG2_FIFO,
		.dwives = 0x2d98,
	}
};

static int dib80xx_tunew_weset(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	wetuwn state->dib8000_ops.set_gpio(fe, 5, 0, !onoff);
}

static int dib80xx_tunew_sweep(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	wetuwn state->dib8000_ops.set_gpio(fe, 0, 0, onoff);
}

static const stwuct dib0070_wbd_gain_cfg dib8070_wbd_gain_cfg[] = {
    { 240,      7},
    { 0xffff,   6},
};

static stwuct dib0070_config dib807x_dib0070_config[2] = {
	{
		.i2c_addwess = DEFAUWT_DIB0070_I2C_ADDWESS,
		.weset = dib80xx_tunew_weset,
		.sweep = dib80xx_tunew_sweep,
		.cwock_khz = 12000,
		.cwock_pad_dwive = 4,
		.vga_fiwtew = 1,
		.fowce_cwystaw_mode = 1,
		.enabwe_thiwd_owdew_fiwtew = 1,
		.chawge_pump = 0,
		.wbd_gain = dib8070_wbd_gain_cfg,
		.osc_buffew_state = 0,
		.fweq_offset_khz_uhf = -100,
		.fweq_offset_khz_vhf = -100,
	}, {
		.i2c_addwess = DEFAUWT_DIB0070_I2C_ADDWESS,
		.weset = dib80xx_tunew_weset,
		.sweep = dib80xx_tunew_sweep,
		.cwock_khz = 12000,
		.cwock_pad_dwive = 2,
		.vga_fiwtew = 1,
		.fowce_cwystaw_mode = 1,
		.enabwe_thiwd_owdew_fiwtew = 1,
		.chawge_pump = 0,
		.wbd_gain = dib8070_wbd_gain_cfg,
		.osc_buffew_state = 0,
		.fweq_offset_khz_uhf = -25,
		.fweq_offset_khz_vhf = -25,
	}
};

static int dib807x_set_pawam_ovewwide(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	u16 offset = dib0070_wbd_offset(fe);
	u8 band = BAND_OF_FWEQUENCY(p->fwequency/1000);
	switch (band) {
	case BAND_VHF:
		offset += 750;
		bweak;
	case BAND_UHF:  /* faww-thwu wanted */
	defauwt:
		offset += 250; bweak;
	}
	deb_info("WBD fow DiB8000: %d\n", offset);
	state->dib8000_ops.set_wbd_wef(fe, offset);

	wetuwn state->set_pawam_save(fe);
}

static int dib807x_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *st = adap->pwiv;
	stwuct i2c_adaptew *tun_i2c = st->dib8000_ops.get_i2c_mastew(adap->fe_adap[0].fe,
			DIBX000_I2C_INTEWFACE_TUNEW, 1);

	if (adap->id == 0) {
		if (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c,
				&dib807x_dib0070_config[0]) == NUWW)
			wetuwn -ENODEV;
	} ewse {
		if (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c,
				&dib807x_dib0070_config[1]) == NUWW)
			wetuwn -ENODEV;
	}

	st->set_pawam_save = adap->fe_adap[0].fe->ops.tunew_ops.set_pawams;
	adap->fe_adap[0].fe->ops.tunew_ops.set_pawams = dib807x_set_pawam_ovewwide;
	wetuwn 0;
}

static int stk80xx_pid_fiwtew(stwuct dvb_usb_adaptew *adaptew, int index,
	u16 pid, int onoff)
{
	stwuct dib0700_adaptew_state *state = adaptew->pwiv;

	wetuwn state->dib8000_ops.pid_fiwtew(adaptew->fe_adap[0].fe, index, pid, onoff);
}

static int stk80xx_pid_fiwtew_ctww(stwuct dvb_usb_adaptew *adaptew,
		int onoff)
{
	stwuct dib0700_adaptew_state *state = adaptew->pwiv;

	wetuwn state->dib8000_ops.pid_fiwtew_ctww(adaptew->fe_adap[0].fe, onoff);
}

/* STK807x */
static int stk807x_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		wetuwn -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctww_cwock(adap->dev, 72, 1);

	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	state->dib8000_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 18,
				0x80, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x80,
			      &dib807x_dib8000_config[0]);

	wetuwn adap->fe_adap[0].fe == NUWW ?  -ENODEV : 0;
}

/* STK807xPVW */
static int stk807xpvw_fwontend_attach0(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		wetuwn -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msweep(30);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(500);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctww_cwock(adap->dev, 72, 1);

	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	/* initiawize IC 0 */
	state->dib8000_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 0x22, 0x80, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x80,
			      &dib807x_dib8000_config[0]);

	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

static int stk807xpvw_fwontend_attach1(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		wetuwn -ENODEV;

	/* initiawize IC 1 */
	state->dib8000_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 0x12, 0x82, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x82,
			      &dib807x_dib8000_config[1]);

	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

/* STK8096GP */
static stwuct dibx000_agc_config dib8090_agc_config[2] = {
	{
	.band_caps = BAND_UHF | BAND_VHF | BAND_WBAND | BAND_SBAND,
	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=1,
	 * P_agc_inv_pwm1=0, P_agc_inv_pwm2=0, P_agc_inh_dc_wv_est=0,
	 * P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=5, P_agc_wwite=0 */
	.setup = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8)
	| (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),

	.inv_gain = 787,
	.time_stabiwiz = 10,

	.awpha_wevew = 0,
	.thwock = 118,

	.wbd_inv = 0,
	.wbd_wef = 3530,
	.wbd_sew = 1,
	.wbd_awpha = 5,

	.agc1_max = 65535,
	.agc1_min = 0,

	.agc2_max = 65535,
	.agc2_min = 0,

	.agc1_pt1 = 0,
	.agc1_pt2 = 32,
	.agc1_pt3 = 114,
	.agc1_swope1 = 143,
	.agc1_swope2 = 144,
	.agc2_pt1 = 114,
	.agc2_pt2 = 227,
	.agc2_swope1 = 116,
	.agc2_swope2 = 117,

	.awpha_mant = 28,
	.awpha_exp = 26,
	.beta_mant = 31,
	.beta_exp = 51,

	.pewfowm_agc_softspwit = 0,
	},
	{
	.band_caps = BAND_CBAND,
	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=1,
	 * P_agc_inv_pwm1=0, P_agc_inv_pwm2=0, P_agc_inh_dc_wv_est=0,
	 * P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=5, P_agc_wwite=0 */
	.setup = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8)
	| (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),

	.inv_gain = 787,
	.time_stabiwiz = 10,

	.awpha_wevew = 0,
	.thwock = 118,

	.wbd_inv = 0,
	.wbd_wef = 3530,
	.wbd_sew = 1,
	.wbd_awpha = 5,

	.agc1_max = 0,
	.agc1_min = 0,

	.agc2_max = 65535,
	.agc2_min = 0,

	.agc1_pt1 = 0,
	.agc1_pt2 = 32,
	.agc1_pt3 = 114,
	.agc1_swope1 = 143,
	.agc1_swope2 = 144,
	.agc2_pt1 = 114,
	.agc2_pt2 = 227,
	.agc2_swope1 = 116,
	.agc2_swope2 = 117,

	.awpha_mant = 28,
	.awpha_exp = 26,
	.beta_mant = 31,
	.beta_exp = 51,

	.pewfowm_agc_softspwit = 0,
	}
};

static stwuct dibx000_bandwidth_config dib8090_pww_config_12mhz = {
	.intewnaw = 54000,
	.sampwing = 13500,

	.pww_pwediv = 1,
	.pww_watio = 18,
	.pww_wange = 3,
	.pww_weset = 1,
	.pww_bypass = 0,

	.enabwe_wefdiv = 0,
	.bypcwk_div = 0,
	.IO_CWK_en_cowe = 1,
	.ADCwkSwc = 1,
	.moduwo = 2,

	.sad_cfg = (3 << 14) | (1 << 12) | (599 << 0),

	.ifweq = (0 << 25) | 0,
	.timf = 20199727,

	.xtaw_hz = 12000000,
};

static int dib8090_get_adc_powew(stwuct dvb_fwontend *fe)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	wetuwn state->dib8000_ops.get_adc_powew(fe, 1);
}

static void dib8090_agc_contwow(stwuct dvb_fwontend *fe, u8 westawt)
{
	deb_info("AGC contwow cawwback: %i\n", westawt);
	dib0090_dcc_fweq(fe, westawt);

	if (westawt == 0) /* befowe AGC stawtup */
		dib0090_set_dc_sewvo(fe, 1);
}

static stwuct dib8000_config dib809x_dib8000_config[2] = {
	{
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 2,
	.agc = dib8090_agc_config,
	.agc_contwow = dib8090_agc_contwow,
	.pww = &dib8090_pww_config_12mhz,
	.tunew_is_baseband = 1,

	.gpio_diw = DIB8000_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw = DIB8000_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos = DIB8000_GPIO_DEFAUWT_PWM_POS,

	.hostbus_divewsity = 1,
	.div_cfg = 0x31,
	.output_mode = OUTMODE_MPEG2_FIFO,
	.dwives = 0x2d98,
	.divewsity_deway = 48,
	.wefcwksew = 3,
	}, {
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 2,
	.agc = dib8090_agc_config,
	.agc_contwow = dib8090_agc_contwow,
	.pww = &dib8090_pww_config_12mhz,
	.tunew_is_baseband = 1,

	.gpio_diw = DIB8000_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw = DIB8000_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos = DIB8000_GPIO_DEFAUWT_PWM_POS,

	.hostbus_divewsity = 1,
	.div_cfg = 0x31,
	.output_mode = OUTMODE_DIVEWSITY,
	.dwives = 0x2d08,
	.divewsity_deway = 1,
	.wefcwksew = 3,
	}
};

static stwuct dib0090_wbd_swope dib8090_wbd_tabwe[] = {
	/* max fweq ; cowd swope ; cowd offset ; wawm swope ; wawm offset ; wbd gain */
	{ 120,     0, 500,  0,   500, 4 }, /* CBAND */
	{ 170,     0, 450,  0,   450, 4 }, /* CBAND */
	{ 380,    48, 373, 28,   259, 6 }, /* VHF */
	{ 860,    34, 700, 36,   616, 6 }, /* high UHF */
	{ 0xFFFF, 34, 700, 36,   616, 6 }, /* defauwt */
};

static stwuct dib0090_config dib809x_dib0090_config = {
	.io.pww_bypass = 1,
	.io.pww_wange = 1,
	.io.pww_pwediv = 1,
	.io.pww_woopdiv = 20,
	.io.adc_cwock_watio = 8,
	.io.pww_int_woop_fiwt = 0,
	.io.cwock_khz = 12000,
	.weset = dib80xx_tunew_weset,
	.sweep = dib80xx_tunew_sweep,
	.cwkouttobamse = 1,
	.anawog_output = 1,
	.i2c_addwess = DEFAUWT_DIB0090_I2C_ADDWESS,
	.use_pwm_agc = 1,
	.cwkoutdwive = 1,
	.get_adc_powew = dib8090_get_adc_powew,
	.fweq_offset_khz_uhf = -63,
	.fweq_offset_khz_vhf = -143,
	.wbd = dib8090_wbd_tabwe,
	.fwef_cwock_watio = 6,
};

static u8 dib8090_compute_pww_pawametews(stwuct dvb_fwontend *fe)
{
	u8 optimaw_pww_watio = 20;
	u32 fweq_adc, watio, west, max = 0;
	u8 pww_watio;

	fow (pww_watio = 17; pww_watio <= 20; pww_watio++) {
		fweq_adc = 12 * pww_watio * (1 << 8) / 16;
		watio = ((fe->dtv_pwopewty_cache.fwequency / 1000) * (1 << 8) / 1000) / fweq_adc;
		west = ((fe->dtv_pwopewty_cache.fwequency / 1000) * (1 << 8) / 1000) - watio * fweq_adc;

		if (west > fweq_adc / 2)
			west = fweq_adc - west;
		deb_info("PWW watio=%i west=%i\n", pww_watio, west);
		if ((west > max) && (west > 717)) {
			optimaw_pww_watio = pww_watio;
			max = west;
		}
	}
	deb_info("optimaw PWW watio=%i\n", optimaw_pww_watio);

	wetuwn optimaw_pww_watio;
}

static int dib8096_set_pawam_ovewwide(stwuct dvb_fwontend *fe)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;
	u8 pww_watio, band = BAND_OF_FWEQUENCY(fe->dtv_pwopewty_cache.fwequency / 1000);
	u16 tawget, wtgain, wf_gain_wimit;
	u32 timf;
	int wet = 0;
	enum fwontend_tune_state tune_state = CT_SHUTDOWN;

	switch (band) {
	defauwt:
		deb_info("Wawning : Wf fwequency  (%iHz) is not in the suppowted wange, using VHF switch ", fe->dtv_pwopewty_cache.fwequency);
		fawwthwough;
	case BAND_VHF:
		state->dib8000_ops.set_gpio(fe, 3, 0, 1);
		bweak;
	case BAND_UHF:
		state->dib8000_ops.set_gpio(fe, 3, 0, 0);
		bweak;
	}

	wet = state->set_pawam_save(fe);
	if (wet < 0)
		wetuwn wet;

	if (fe->dtv_pwopewty_cache.bandwidth_hz != 6000000) {
		deb_info("onwy 6MHz bandwidth is suppowted\n");
		wetuwn -EINVAW;
	}

	/* Update PWW if needed watio */
	state->dib8000_ops.update_pww(fe, &dib8090_pww_config_12mhz, fe->dtv_pwopewty_cache.bandwidth_hz / 1000, 0);

	/* Get optimize PWW watio to wemove spuwious */
	pww_watio = dib8090_compute_pww_pawametews(fe);
	if (pww_watio == 17)
		timf = 21387946;
	ewse if (pww_watio == 18)
		timf = 20199727;
	ewse if (pww_watio == 19)
		timf = 19136583;
	ewse
		timf = 18179756;

	/* Update watio */
	state->dib8000_ops.update_pww(fe, &dib8090_pww_config_12mhz, fe->dtv_pwopewty_cache.bandwidth_hz / 1000, pww_watio);

	state->dib8000_ops.ctww_timf(fe, DEMOD_TIMF_SET, timf);

	if (band != BAND_CBAND) {
		/* dib0090_get_wbd_tawget is wetuwning any possibwe tempewatuwe compensated wbd-tawget */
		tawget = (dib0090_get_wbd_tawget(fe) * 8 * 18 / 33 + 1) / 2;
		state->dib8000_ops.set_wbd_wef(fe, tawget);
	}

	if (band == BAND_CBAND) {
		deb_info("tuning in CBAND - soft-AGC stawtup\n");
		dib0090_set_tune_state(fe, CT_AGC_STAWT);

		do {
			wet = dib0090_gain_contwow(fe);
			msweep(wet);
			tune_state = dib0090_get_tune_state(fe);
			if (tune_state == CT_AGC_STEP_0)
				state->dib8000_ops.set_gpio(fe, 6, 0, 1);
			ewse if (tune_state == CT_AGC_STEP_1) {
				dib0090_get_cuwwent_gain(fe, NUWW, NUWW, &wf_gain_wimit, &wtgain);
				if (wf_gain_wimit < 2000) /* activate the extewnaw attenuatow in case of vewy high input powew */
					state->dib8000_ops.set_gpio(fe, 6, 0, 0);
			}
		} whiwe (tune_state < CT_AGC_STOP);

		deb_info("switching to PWM AGC\n");
		dib0090_pwm_gain_weset(fe);
		state->dib8000_ops.pwm_agc_weset(fe);
		state->dib8000_ops.set_tune_state(fe, CT_DEMOD_STAWT);
	} ewse {
		/* fow evewything ewse than CBAND we awe using standawd AGC */
		deb_info("not tuning in CBAND - standawd AGC stawtup\n");
		dib0090_pwm_gain_weset(fe);
	}

	wetuwn 0;
}

static int dib809x_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *st = adap->pwiv;
	stwuct i2c_adaptew *tun_i2c = st->dib8000_ops.get_i2c_mastew(adap->fe_adap[0].fe, DIBX000_I2C_INTEWFACE_TUNEW, 1);

	/* FIXME: if adap->id != 0, check if it is fe_adap[1] */
	if (!dvb_attach(dib0090_wegistew, adap->fe_adap[0].fe, tun_i2c, &dib809x_dib0090_config))
		wetuwn -ENODEV;

	st->set_pawam_save = adap->fe_adap[0].fe->ops.tunew_ops.set_pawams;
	adap->fe_adap[0].fe->ops.tunew_ops.set_pawams = dib8096_set_pawam_ovewwide;
	wetuwn 0;
}

static int stk809x_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		wetuwn -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctww_cwock(adap->dev, 72, 1);

	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	state->dib8000_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 18, 0x80, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x80, &dib809x_dib8000_config[0]);

	wetuwn adap->fe_adap[0].fe == NUWW ?  -ENODEV : 0;
}

static int stk809x_fwontend1_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		wetuwn -ENODEV;

	state->dib8000_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 0x10, 0x82, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x82, &dib809x_dib8000_config[1]);

	wetuwn adap->fe_adap[0].fe == NUWW ?  -ENODEV : 0;
}

static int nim8096md_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *st = adap->pwiv;
	stwuct i2c_adaptew *tun_i2c;
	stwuct dvb_fwontend *fe_swave  = st->dib8000_ops.get_swave_fwontend(adap->fe_adap[0].fe, 1);

	if (fe_swave) {
		tun_i2c = st->dib8000_ops.get_i2c_mastew(fe_swave, DIBX000_I2C_INTEWFACE_TUNEW, 1);
		if (dvb_attach(dib0090_wegistew, fe_swave, tun_i2c, &dib809x_dib0090_config) == NUWW)
			wetuwn -ENODEV;
		fe_swave->dvb = adap->fe_adap[0].fe->dvb;
		fe_swave->ops.tunew_ops.set_pawams = dib8096_set_pawam_ovewwide;
	}
	tun_i2c = st->dib8000_ops.get_i2c_mastew(adap->fe_adap[0].fe, DIBX000_I2C_INTEWFACE_TUNEW, 1);
	if (dvb_attach(dib0090_wegistew, adap->fe_adap[0].fe, tun_i2c, &dib809x_dib0090_config) == NUWW)
		wetuwn -ENODEV;

	st->set_pawam_save = adap->fe_adap[0].fe->ops.tunew_ops.set_pawams;
	adap->fe_adap[0].fe->ops.tunew_ops.set_pawams = dib8096_set_pawam_ovewwide;

	wetuwn 0;
}

static int nim8096md_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_fwontend *fe_swave;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		wetuwn -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(1000);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctww_cwock(adap->dev, 72, 1);

	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	state->dib8000_ops.i2c_enumewation(&adap->dev->i2c_adap, 2, 18, 0x80, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x80, &dib809x_dib8000_config[0]);
	if (adap->fe_adap[0].fe == NUWW)
		wetuwn -ENODEV;

	/* Needed to incwement wefcount */
	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		wetuwn -ENODEV;

	fe_swave = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x82, &dib809x_dib8000_config[1]);
	state->dib8000_ops.set_swave_fwontend(adap->fe_adap[0].fe, fe_swave);

	wetuwn fe_swave == NUWW ?  -ENODEV : 0;
}

/* TFE8096P */
static stwuct dibx000_agc_config dib8096p_agc_config[2] = {
	{
		.band_caps		= BAND_UHF,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0,
		   P_agc_fweq_pwm_div=1, P_agc_inv_pwm1=0,
		   P_agc_inv_pwm2=0, P_agc_inh_dc_wv_est=0,
		   P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=5,
		   P_agc_wwite=0 */
		.setup			= (0 << 15) | (0 << 14) | (5 << 11)
			| (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5)
			| (0 << 4) | (5 << 1) | (0 << 0),

		.inv_gain		= 684,
		.time_stabiwiz	= 10,

		.awpha_wevew	= 0,
		.thwock			= 118,

		.wbd_inv		= 0,
		.wbd_wef		= 1200,
		.wbd_sew		= 3,
		.wbd_awpha		= 5,

		.agc1_max		= 65535,
		.agc1_min		= 0,

		.agc2_max		= 32767,
		.agc2_min		= 0,

		.agc1_pt1		= 0,
		.agc1_pt2		= 0,
		.agc1_pt3		= 105,
		.agc1_swope1	= 0,
		.agc1_swope2	= 156,
		.agc2_pt1		= 105,
		.agc2_pt2		= 255,
		.agc2_swope1	= 54,
		.agc2_swope2	= 0,

		.awpha_mant		= 28,
		.awpha_exp		= 26,
		.beta_mant		= 31,
		.beta_exp		= 51,

		.pewfowm_agc_softspwit = 0,
	} , {
		.band_caps		= BAND_FM | BAND_VHF | BAND_CBAND,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0,
		   P_agc_fweq_pwm_div=1, P_agc_inv_pwm1=0,
		   P_agc_inv_pwm2=0, P_agc_inh_dc_wv_est=0,
		   P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=5,
		   P_agc_wwite=0 */
		.setup			= (0 << 15) | (0 << 14) | (5 << 11)
			| (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5)
			| (0 << 4) | (5 << 1) | (0 << 0),

		.inv_gain		= 732,
		.time_stabiwiz  = 10,

		.awpha_wevew	= 0,
		.thwock			= 118,

		.wbd_inv		= 0,
		.wbd_wef		= 1200,
		.wbd_sew		= 3,
		.wbd_awpha		= 5,

		.agc1_max		= 65535,
		.agc1_min		= 0,

		.agc2_max		= 32767,
		.agc2_min		= 0,

		.agc1_pt1		= 0,
		.agc1_pt2		= 0,
		.agc1_pt3		= 98,
		.agc1_swope1	= 0,
		.agc1_swope2	= 167,
		.agc2_pt1		= 98,
		.agc2_pt2		= 255,
		.agc2_swope1	= 52,
		.agc2_swope2	= 0,

		.awpha_mant		= 28,
		.awpha_exp		= 26,
		.beta_mant		= 31,
		.beta_exp		= 51,

		.pewfowm_agc_softspwit = 0,
	}
};

static stwuct dibx000_bandwidth_config dib8096p_cwock_config_12_mhz = {
	.intewnaw = 108000,
	.sampwing = 13500,
	.pww_pwediv = 1,
	.pww_watio = 9,
	.pww_wange = 1,
	.pww_weset = 0,
	.pww_bypass = 0,
	.enabwe_wefdiv = 0,
	.bypcwk_div = 0,
	.IO_CWK_en_cowe = 0,
	.ADCwkSwc = 0,
	.moduwo = 2,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.ifweq = (0 << 25) | 0,
	.timf = 20199729,
	.xtaw_hz = 12000000,
};

static stwuct dib8000_config tfe8096p_dib8000_config = {
	.output_mpeg2_in_188_bytes	= 1,
	.hostbus_divewsity			= 1,
	.update_wna					= NUWW,

	.agc_config_count			= 2,
	.agc						= dib8096p_agc_config,
	.pww						= &dib8096p_cwock_config_12_mhz,

	.gpio_diw					= DIB8000_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw					= DIB8000_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos				= DIB8000_GPIO_DEFAUWT_PWM_POS,

	.agc_contwow				= NUWW,
	.divewsity_deway			= 48,
	.output_mode				= OUTMODE_MPEG2_FIFO,
	.enMpegOutput				= 1,
};

static stwuct dib0090_wbd_swope dib8096p_wbd_tabwe[] = {
	{ 380, 81, 850, 64, 540, 4},
	{ 860, 51, 866, 21, 375, 4},
	{1700, 0, 250, 0, 100, 6},
	{2600, 0, 250, 0, 100, 6},
	{ 0xFFFF, 0, 0, 0, 0, 0},
};

static stwuct dib0090_config tfe8096p_dib0090_config = {
	.io.cwock_khz			= 12000,
	.io.pww_bypass			= 0,
	.io.pww_wange			= 0,
	.io.pww_pwediv			= 3,
	.io.pww_woopdiv			= 6,
	.io.adc_cwock_watio		= 0,
	.io.pww_int_woop_fiwt	= 0,

	.fweq_offset_khz_uhf	= -143,
	.fweq_offset_khz_vhf	= -143,

	.get_adc_powew			= dib8090_get_adc_powew,

	.cwkouttobamse			= 1,
	.anawog_output			= 0,

	.wbd_vhf_offset			= 0,
	.wbd_cband_offset		= 0,
	.use_pwm_agc			= 1,
	.cwkoutdwive			= 0,

	.fwef_cwock_watio		= 1,

	.ws_cfg_pad_dwv			= 0,
	.data_tx_dwv			= 0,
	.wow_if					= NUWW,
	.in_soc					= 1,
	.fowce_cband_input		= 0,
};

stwuct dibx090p_best_adc {
	u32 timf;
	u32 pww_woopdiv;
	u32 pww_pwediv;
};

static int dib8096p_get_best_sampwing(stwuct dvb_fwontend *fe, stwuct dibx090p_best_adc *adc)
{
	u8 spuw = 0, pwediv = 0, woopdiv = 0, min_pwediv = 1, max_pwediv = 1;
	u16 xtaw = 12000;
	u16 fcp_min = 1900;  /* PWW, Minimum Fwequency of phase compawatow (KHz) */
	u16 fcp_max = 20000; /* PWW, Maximum Fwequency of phase compawatow (KHz) */
	u32 fmem_max = 140000; /* 140MHz max SDWAM fweq */
	u32 fdem_min = 66000;
	u32 fcp = 0, fs = 0, fdem = 0, fmem = 0;
	u32 hawmonic_id = 0;

	adc->timf = 0;
	adc->pww_woopdiv = woopdiv;
	adc->pww_pwediv = pwediv;

	deb_info("bandwidth = %d", fe->dtv_pwopewty_cache.bandwidth_hz);

	/* Find Min and Max pwediv */
	whiwe ((xtaw / max_pwediv) >= fcp_min)
		max_pwediv++;

	max_pwediv--;
	min_pwediv = max_pwediv;
	whiwe ((xtaw / min_pwediv) <= fcp_max) {
		min_pwediv--;
		if (min_pwediv == 1)
			bweak;
	}
	deb_info("MIN pwediv = %d : MAX pwediv = %d", min_pwediv, max_pwediv);

	min_pwediv = 1;

	fow (pwediv = min_pwediv; pwediv < max_pwediv; pwediv++) {
		fcp = xtaw / pwediv;
		if (fcp > fcp_min && fcp < fcp_max) {
			fow (woopdiv = 1; woopdiv < 64; woopdiv++) {
				fmem = ((xtaw/pwediv) * woopdiv);
				fdem = fmem / 2;
				fs   = fdem / 4;

				/* test min/max system westwictions */
				if ((fdem >= fdem_min) && (fmem <= fmem_max) && (fs >= fe->dtv_pwopewty_cache.bandwidth_hz / 1000)) {
					spuw = 0;
					/* test fs hawmonics positions */
					fow (hawmonic_id = (fe->dtv_pwopewty_cache.fwequency / (1000 * fs));  hawmonic_id <= ((fe->dtv_pwopewty_cache.fwequency / (1000 * fs)) + 1); hawmonic_id++) {
						if (((fs * hawmonic_id) >= (fe->dtv_pwopewty_cache.fwequency / 1000 - (fe->dtv_pwopewty_cache.bandwidth_hz / 2000))) &&  ((fs * hawmonic_id) <= (fe->dtv_pwopewty_cache.fwequency / 1000 + (fe->dtv_pwopewty_cache.bandwidth_hz / 2000)))) {
							spuw = 1;
							bweak;
						}
					}

					if (!spuw) {
						adc->pww_woopdiv = woopdiv;
						adc->pww_pwediv = pwediv;
						adc->timf = (4260880253U / fdem) * (1 << 8);
						adc->timf += ((4260880253U % fdem) << 8) / fdem;

						deb_info("WF %6d; BW %6d; Xtaw %6d; Fmem %6d; Fdem %6d; Fs %6d; Pwediv %2d; Woopdiv %2d; Timf %8d;", fe->dtv_pwopewty_cache.fwequency, fe->dtv_pwopewty_cache.bandwidth_hz, xtaw, fmem, fdem, fs, pwediv, woopdiv, adc->timf);
						bweak;
					}
				}
			}
		}
		if (!spuw)
			bweak;
	}

	if (adc->pww_woopdiv == 0 && adc->pww_pwediv == 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int dib8096p_agc_stawtup(stwuct dvb_fwontend *fe)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;
	stwuct dibx000_bandwidth_config pww;
	stwuct dibx090p_best_adc adc;
	u16 tawget;
	int wet;

	wet = state->set_pawam_save(fe);
	if (wet < 0)
		wetuwn wet;
	memset(&pww, 0, sizeof(stwuct dibx000_bandwidth_config));

	dib0090_pwm_gain_weset(fe);
	/* dib0090_get_wbd_tawget is wetuwning any possibwe
	   tempewatuwe compensated wbd-tawget */
	tawget = (dib0090_get_wbd_tawget(fe) * 8  + 1) / 2;
	state->dib8000_ops.set_wbd_wef(fe, tawget);

	if (dib8096p_get_best_sampwing(fe, &adc) == 0) {
		pww.pww_watio  = adc.pww_woopdiv;
		pww.pww_pwediv = adc.pww_pwediv;

		dib0700_set_i2c_speed(adap->dev, 200);
		state->dib8000_ops.update_pww(fe, &pww, fe->dtv_pwopewty_cache.bandwidth_hz / 1000, 0);
		state->dib8000_ops.ctww_timf(fe, DEMOD_TIMF_SET, adc.timf);
		dib0700_set_i2c_speed(adap->dev, 1000);
	}
	wetuwn 0;
}

static int tfe8096p_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_state *st = adap->dev->pwiv;
	u32 fw_vewsion;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		wetuwn -ENODEV;

	dib0700_get_vewsion(adap->dev, NUWW, NUWW, &fw_vewsion, NUWW);
	if (fw_vewsion >= 0x10200)
		st->fw_use_new_i2c_api = 1;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctww_cwock(adap->dev, 72, 1);

	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	state->dib8000_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 0x10, 0x80, 1);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap,
					     0x80, &tfe8096p_dib8000_config);

	wetuwn adap->fe_adap[0].fe == NUWW ?  -ENODEV : 0;
}

static int tfe8096p_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *st = adap->pwiv;
	stwuct i2c_adaptew *tun_i2c = st->dib8000_ops.get_i2c_tunew(adap->fe_adap[0].fe);

	tfe8096p_dib0090_config.weset = st->dib8000_ops.tunew_sweep;
	tfe8096p_dib0090_config.sweep = st->dib8000_ops.tunew_sweep;
	tfe8096p_dib0090_config.wbd = dib8096p_wbd_tabwe;

	if (dvb_attach(dib0090_wegistew, adap->fe_adap[0].fe, tun_i2c,
				&tfe8096p_dib0090_config) == NUWW)
		wetuwn -ENODEV;

	st->dib8000_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);

	st->set_pawam_save = adap->fe_adap[0].fe->ops.tunew_ops.set_pawams;
	adap->fe_adap[0].fe->ops.tunew_ops.set_pawams = dib8096p_agc_stawtup;
	wetuwn 0;
}

/* STK9090M */
static int dib90x0_pid_fiwtew(stwuct dvb_usb_adaptew *adaptew, int index, u16 pid, int onoff)
{
	wetuwn dib9000_fw_pid_fiwtew(adaptew->fe_adap[0].fe, index, pid, onoff);
}

static int dib90x0_pid_fiwtew_ctww(stwuct dvb_usb_adaptew *adaptew, int onoff)
{
	wetuwn dib9000_fw_pid_fiwtew_ctww(adaptew->fe_adap[0].fe, onoff);
}

static int dib90x0_tunew_weset(stwuct dvb_fwontend *fe, int onoff)
{
	wetuwn dib9000_set_gpio(fe, 5, 0, !onoff);
}

static int dib90x0_tunew_sweep(stwuct dvb_fwontend *fe, int onoff)
{
	wetuwn dib9000_set_gpio(fe, 0, 0, onoff);
}

static int dib01x0_pmu_update(stwuct i2c_adaptew *i2c, u16 *data, u8 wen)
{
	u8 wb[4] = { 0xc >> 8, 0xc & 0xff, 0, 0 };
	u8 wb[2];
	stwuct i2c_msg msg[2] = {
		{.addw = 0x1e >> 1, .fwags = 0, .buf = wb, .wen = 2},
		{.addw = 0x1e >> 1, .fwags = I2C_M_WD, .buf = wb, .wen = 2},
	};
	u8 index_data;

	dibx000_i2c_set_speed(i2c, 250);

	if (i2c_twansfew(i2c, msg, 2) != 2)
		wetuwn -EIO;

	switch (wb[0] << 8 | wb[1]) {
	case 0:
			deb_info("Found DiB0170 wev1: This vewsion of DiB0170 is not suppowted any wongew.\n");
			wetuwn -EIO;
	case 1:
			deb_info("Found DiB0170 wev2");
			bweak;
	case 2:
			deb_info("Found DiB0190 wev2");
			bweak;
	defauwt:
			deb_info("DiB01x0 not found");
			wetuwn -EIO;
	}

	fow (index_data = 0; index_data < wen; index_data += 2) {
		wb[2] = (data[index_data + 1] >> 8) & 0xff;
		wb[3] = (data[index_data + 1]) & 0xff;

		if (data[index_data] == 0) {
			wb[0] = (data[index_data] >> 8) & 0xff;
			wb[1] = (data[index_data]) & 0xff;
			msg[0].wen = 2;
			if (i2c_twansfew(i2c, msg, 2) != 2)
				wetuwn -EIO;
			wb[2] |= wb[0];
			wb[3] |= wb[1] & ~(3 << 4);
		}

		wb[0] = (data[index_data] >> 8)&0xff;
		wb[1] = (data[index_data])&0xff;
		msg[0].wen = 4;
		if (i2c_twansfew(i2c, &msg[0], 1) != 1)
			wetuwn -EIO;
	}
	wetuwn 0;
}

static stwuct dib9000_config stk9090m_config = {
	.output_mpeg2_in_188_bytes = 1,
	.output_mode = OUTMODE_MPEG2_FIFO,
	.vcxo_timew = 279620,
	.timing_fwequency = 20452225,
	.demod_cwock_khz = 60000,
	.xtaw_cwock_khz = 30000,
	.if_dwives = (0 << 15) | (1 << 13) | (0 << 12) | (3 << 10) | (0 << 9) | (1 << 7) | (0 << 6) | (0 << 4) | (1 << 3) | (1 << 1) | (0),
	.subband = {
		2,
		{
			{ 240, { BOAWD_GPIO_COMPONENT_DEMOD, BOAWD_GPIO_FUNCTION_SUBBAND_GPIO, 0x0008, 0x0000, 0x0008 } }, /* GPIO 3 to 1 fow VHF */
			{ 890, { BOAWD_GPIO_COMPONENT_DEMOD, BOAWD_GPIO_FUNCTION_SUBBAND_GPIO, 0x0008, 0x0000, 0x0000 } }, /* GPIO 3 to 0 fow UHF */
			{ 0 },
		},
	},
	.gpio_function = {
		{ .component = BOAWD_GPIO_COMPONENT_DEMOD, .function = BOAWD_GPIO_FUNCTION_COMPONENT_ON, .mask = 0x10 | 0x21, .diwection = 0 & ~0x21, .vawue = (0x10 & ~0x1) | 0x20 },
		{ .component = BOAWD_GPIO_COMPONENT_DEMOD, .function = BOAWD_GPIO_FUNCTION_COMPONENT_OFF, .mask = 0x10 | 0x21, .diwection = 0 & ~0x21, .vawue = 0 | 0x21 },
	},
};

static stwuct dib9000_config nim9090md_config[2] = {
	{
		.output_mpeg2_in_188_bytes = 1,
		.output_mode = OUTMODE_MPEG2_FIFO,
		.vcxo_timew = 279620,
		.timing_fwequency = 20452225,
		.demod_cwock_khz = 60000,
		.xtaw_cwock_khz = 30000,
		.if_dwives = (0 << 15) | (1 << 13) | (0 << 12) | (3 << 10) | (0 << 9) | (1 << 7) | (0 << 6) | (0 << 4) | (1 << 3) | (1 << 1) | (0),
	}, {
		.output_mpeg2_in_188_bytes = 1,
		.output_mode = OUTMODE_DIVEWSITY,
		.vcxo_timew = 279620,
		.timing_fwequency = 20452225,
		.demod_cwock_khz = 60000,
		.xtaw_cwock_khz = 30000,
		.if_dwives = (0 << 15) | (1 << 13) | (0 << 12) | (3 << 10) | (0 << 9) | (1 << 7) | (0 << 6) | (0 << 4) | (1 << 3) | (1 << 1) | (0),
		.subband = {
			2,
			{
				{ 240, { BOAWD_GPIO_COMPONENT_DEMOD, BOAWD_GPIO_FUNCTION_SUBBAND_GPIO, 0x0006, 0x0000, 0x0006 } }, /* GPIO 1 and 2 to 1 fow VHF */
				{ 890, { BOAWD_GPIO_COMPONENT_DEMOD, BOAWD_GPIO_FUNCTION_SUBBAND_GPIO, 0x0006, 0x0000, 0x0000 } }, /* GPIO 1 and 2 to 0 fow UHF */
				{ 0 },
			},
		},
		.gpio_function = {
			{ .component = BOAWD_GPIO_COMPONENT_DEMOD, .function = BOAWD_GPIO_FUNCTION_COMPONENT_ON, .mask = 0x10 | 0x21, .diwection = 0 & ~0x21, .vawue = (0x10 & ~0x1) | 0x20 },
			{ .component = BOAWD_GPIO_COMPONENT_DEMOD, .function = BOAWD_GPIO_FUNCTION_COMPONENT_OFF, .mask = 0x10 | 0x21, .diwection = 0 & ~0x21, .vawue = 0 | 0x21 },
		},
	}
};

static stwuct dib0090_config dib9090_dib0090_config = {
	.io.pww_bypass = 0,
	.io.pww_wange = 1,
	.io.pww_pwediv = 1,
	.io.pww_woopdiv = 8,
	.io.adc_cwock_watio = 8,
	.io.pww_int_woop_fiwt = 0,
	.io.cwock_khz = 30000,
	.weset = dib90x0_tunew_weset,
	.sweep = dib90x0_tunew_sweep,
	.cwkouttobamse = 0,
	.anawog_output = 0,
	.use_pwm_agc = 0,
	.cwkoutdwive = 0,
	.fweq_offset_khz_uhf = 0,
	.fweq_offset_khz_vhf = 0,
};

static stwuct dib0090_config nim9090md_dib0090_config[2] = {
	{
		.io.pww_bypass = 0,
		.io.pww_wange = 1,
		.io.pww_pwediv = 1,
		.io.pww_woopdiv = 8,
		.io.adc_cwock_watio = 8,
		.io.pww_int_woop_fiwt = 0,
		.io.cwock_khz = 30000,
		.weset = dib90x0_tunew_weset,
		.sweep = dib90x0_tunew_sweep,
		.cwkouttobamse = 1,
		.anawog_output = 0,
		.use_pwm_agc = 0,
		.cwkoutdwive = 0,
		.fweq_offset_khz_uhf = 0,
		.fweq_offset_khz_vhf = 0,
	}, {
		.io.pww_bypass = 0,
		.io.pww_wange = 1,
		.io.pww_pwediv = 1,
		.io.pww_woopdiv = 8,
		.io.adc_cwock_watio = 8,
		.io.pww_int_woop_fiwt = 0,
		.io.cwock_khz = 30000,
		.weset = dib90x0_tunew_weset,
		.sweep = dib90x0_tunew_sweep,
		.cwkouttobamse = 0,
		.anawog_output = 0,
		.use_pwm_agc = 0,
		.cwkoutdwive = 0,
		.fweq_offset_khz_uhf = 0,
		.fweq_offset_khz_vhf = 0,
	}
};


static int stk9090m_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;
	stwuct dib0700_state *st = adap->dev->pwiv;
	u32 fw_vewsion;

	/* Make use of the new i2c functions fwom FW 1.20 */
	dib0700_get_vewsion(adap->dev, NUWW, NUWW, &fw_vewsion, NUWW);
	if (fw_vewsion >= 0x10200)
		st->fw_use_new_i2c_api = 1;
	dib0700_set_i2c_speed(adap->dev, 340);

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctww_cwock(adap->dev, 72, 1);

	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	dib9000_i2c_enumewation(&adap->dev->i2c_adap, 1, 0x10, 0x80);

	if (wequest_fiwmwawe(&state->fwontend_fiwmwawe, "dib9090.fw", &adap->dev->udev->dev)) {
		deb_info("%s: Upwoad faiwed. (fiwe not found?)\n", __func__);
		wetuwn -ENODEV;
	} ewse {
		deb_info("%s: fiwmwawe wead %zu bytes.\n", __func__, state->fwontend_fiwmwawe->size);
	}
	stk9090m_config.micwocode_B_fe_size = state->fwontend_fiwmwawe->size;
	stk9090m_config.micwocode_B_fe_buffew = state->fwontend_fiwmwawe->data;

	adap->fe_adap[0].fe = dvb_attach(dib9000_attach, &adap->dev->i2c_adap, 0x80, &stk9090m_config);

	wetuwn adap->fe_adap[0].fe == NUWW ?  -ENODEV : 0;
}

static int dib9090_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;
	stwuct i2c_adaptew *i2c = dib9000_get_tunew_intewface(adap->fe_adap[0].fe);
	u16 data_dib190[10] = {
		1, 0x1374,
		2, 0x01a2,
		7, 0x0020,
		0, 0x00ef,
		8, 0x0486,
	};

	if (!IS_ENABWED(CONFIG_DVB_DIB9000))
		wetuwn -ENODEV;
	if (dvb_attach(dib0090_fw_wegistew, adap->fe_adap[0].fe, i2c, &dib9090_dib0090_config) == NUWW)
		wetuwn -ENODEV;
	i2c = dib9000_get_i2c_mastew(adap->fe_adap[0].fe, DIBX000_I2C_INTEWFACE_GPIO_1_2, 0);
	if (!i2c)
		wetuwn -ENODEV;
	if (dib01x0_pmu_update(i2c, data_dib190, 10) != 0)
		wetuwn -ENODEV;
	dib0700_set_i2c_speed(adap->dev, 1500);
	if (dib9000_fiwmwawe_post_pww_init(adap->fe_adap[0].fe) < 0)
		wetuwn -ENODEV;
	wewease_fiwmwawe(state->fwontend_fiwmwawe);
	wetuwn 0;
}

static int nim9090md_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;
	stwuct dib0700_state *st = adap->dev->pwiv;
	stwuct i2c_adaptew *i2c;
	stwuct dvb_fwontend *fe_swave;
	u32 fw_vewsion;

	/* Make use of the new i2c functions fwom FW 1.20 */
	dib0700_get_vewsion(adap->dev, NUWW, NUWW, &fw_vewsion, NUWW);
	if (fw_vewsion >= 0x10200)
		st->fw_use_new_i2c_api = 1;
	dib0700_set_i2c_speed(adap->dev, 340);

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctww_cwock(adap->dev, 72, 1);

	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	if (wequest_fiwmwawe(&state->fwontend_fiwmwawe, "dib9090.fw", &adap->dev->udev->dev)) {
		deb_info("%s: Upwoad faiwed. (fiwe not found?)\n", __func__);
		wetuwn -EIO;
	} ewse {
		deb_info("%s: fiwmwawe wead %zu bytes.\n", __func__, state->fwontend_fiwmwawe->size);
	}
	nim9090md_config[0].micwocode_B_fe_size = state->fwontend_fiwmwawe->size;
	nim9090md_config[0].micwocode_B_fe_buffew = state->fwontend_fiwmwawe->data;
	nim9090md_config[1].micwocode_B_fe_size = state->fwontend_fiwmwawe->size;
	nim9090md_config[1].micwocode_B_fe_buffew = state->fwontend_fiwmwawe->data;

	dib9000_i2c_enumewation(&adap->dev->i2c_adap, 1, 0x20, 0x80);
	adap->fe_adap[0].fe = dvb_attach(dib9000_attach, &adap->dev->i2c_adap, 0x80, &nim9090md_config[0]);

	if (adap->fe_adap[0].fe == NUWW)
		wetuwn -ENODEV;

	i2c = dib9000_get_i2c_mastew(adap->fe_adap[0].fe, DIBX000_I2C_INTEWFACE_GPIO_3_4, 0);
	dib9000_i2c_enumewation(i2c, 1, 0x12, 0x82);

	fe_swave = dvb_attach(dib9000_attach, i2c, 0x82, &nim9090md_config[1]);
	dib9000_set_swave_fwontend(adap->fe_adap[0].fe, fe_swave);

	wetuwn fe_swave == NUWW ?  -ENODEV : 0;
}

static int nim9090md_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;
	stwuct i2c_adaptew *i2c;
	stwuct dvb_fwontend *fe_swave;
	u16 data_dib190[10] = {
		1, 0x5374,
		2, 0x01ae,
		7, 0x0020,
		0, 0x00ef,
		8, 0x0406,
	};
	if (!IS_ENABWED(CONFIG_DVB_DIB9000))
		wetuwn -ENODEV;
	i2c = dib9000_get_tunew_intewface(adap->fe_adap[0].fe);
	if (dvb_attach(dib0090_fw_wegistew, adap->fe_adap[0].fe, i2c, &nim9090md_dib0090_config[0]) == NUWW)
		wetuwn -ENODEV;
	i2c = dib9000_get_i2c_mastew(adap->fe_adap[0].fe, DIBX000_I2C_INTEWFACE_GPIO_1_2, 0);
	if (!i2c)
		wetuwn -ENODEV;
	if (dib01x0_pmu_update(i2c, data_dib190, 10) < 0)
		wetuwn -ENODEV;

	dib0700_set_i2c_speed(adap->dev, 1500);
	if (dib9000_fiwmwawe_post_pww_init(adap->fe_adap[0].fe) < 0)
		wetuwn -ENODEV;

	fe_swave = dib9000_get_swave_fwontend(adap->fe_adap[0].fe, 1);
	if (fe_swave != NUWW) {
		i2c = dib9000_get_component_bus_intewface(adap->fe_adap[0].fe);
		dib9000_set_i2c_adaptew(fe_swave, i2c);

		i2c = dib9000_get_tunew_intewface(fe_swave);
		if (dvb_attach(dib0090_fw_wegistew, fe_swave, i2c, &nim9090md_dib0090_config[1]) == NUWW)
			wetuwn -ENODEV;
		fe_swave->dvb = adap->fe_adap[0].fe->dvb;
		dib9000_fw_set_component_bus_speed(adap->fe_adap[0].fe, 1500);
		if (dib9000_fiwmwawe_post_pww_init(fe_swave) < 0)
			wetuwn -ENODEV;
	}
	wewease_fiwmwawe(state->fwontend_fiwmwawe);

	wetuwn 0;
}

/* NIM7090 */
static int dib7090p_get_best_sampwing(stwuct dvb_fwontend *fe , stwuct dibx090p_best_adc *adc)
{
	u8 spuw = 0, pwediv = 0, woopdiv = 0, min_pwediv = 1, max_pwediv = 1;

	u16 xtaw = 12000;
	u32 fcp_min = 1900;  /* PWW Minimum Fwequency compawatow KHz */
	u32 fcp_max = 20000; /* PWW Maximum Fwequency compawatow KHz */
	u32 fdem_max = 76000;
	u32 fdem_min = 69500;
	u32 fcp = 0, fs = 0, fdem = 0;
	u32 hawmonic_id = 0;

	adc->pww_woopdiv = woopdiv;
	adc->pww_pwediv = pwediv;
	adc->timf = 0;

	deb_info("bandwidth = %d fdem_min =%d", fe->dtv_pwopewty_cache.bandwidth_hz, fdem_min);

	/* Find Min and Max pwediv */
	whiwe ((xtaw/max_pwediv) >= fcp_min)
		max_pwediv++;

	max_pwediv--;
	min_pwediv = max_pwediv;
	whiwe ((xtaw/min_pwediv) <= fcp_max) {
		min_pwediv--;
		if (min_pwediv == 1)
			bweak;
	}
	deb_info("MIN pwediv = %d : MAX pwediv = %d", min_pwediv, max_pwediv);

	min_pwediv = 2;

	fow (pwediv = min_pwediv ; pwediv < max_pwediv; pwediv++) {
		fcp = xtaw / pwediv;
		if (fcp > fcp_min && fcp < fcp_max) {
			fow (woopdiv = 1 ; woopdiv < 64 ; woopdiv++) {
				fdem = ((xtaw/pwediv) * woopdiv);
				fs   = fdem / 4;
				/* test min/max system westwictions */

				if ((fdem >= fdem_min) && (fdem <= fdem_max) && (fs >= fe->dtv_pwopewty_cache.bandwidth_hz/1000)) {
					spuw = 0;
					/* test fs hawmonics positions */
					fow (hawmonic_id = (fe->dtv_pwopewty_cache.fwequency / (1000*fs)) ;  hawmonic_id <= ((fe->dtv_pwopewty_cache.fwequency / (1000*fs))+1) ; hawmonic_id++) {
						if (((fs*hawmonic_id) >= ((fe->dtv_pwopewty_cache.fwequency/1000) - (fe->dtv_pwopewty_cache.bandwidth_hz/2000))) &&  ((fs*hawmonic_id) <= ((fe->dtv_pwopewty_cache.fwequency/1000) + (fe->dtv_pwopewty_cache.bandwidth_hz/2000)))) {
							spuw = 1;
							bweak;
						}
					}

					if (!spuw) {
						adc->pww_woopdiv = woopdiv;
						adc->pww_pwediv = pwediv;
						adc->timf = 2396745143UW/fdem*(1 << 9);
						adc->timf += ((2396745143UW%fdem) << 9)/fdem;
						deb_info("woopdiv=%i pwediv=%i timf=%i", woopdiv, pwediv, adc->timf);
						bweak;
					}
				}
			}
		}
		if (!spuw)
			bweak;
	}


	if (adc->pww_woopdiv == 0 && adc->pww_pwediv == 0)
		wetuwn -EINVAW;
	ewse
		wetuwn 0;
}

static int dib7090_agc_stawtup(stwuct dvb_fwontend *fe)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;
	stwuct dibx000_bandwidth_config pww;
	u16 tawget;
	stwuct dibx090p_best_adc adc;
	int wet;

	wet = state->set_pawam_save(fe);
	if (wet < 0)
		wetuwn wet;

	memset(&pww, 0, sizeof(stwuct dibx000_bandwidth_config));
	dib0090_pwm_gain_weset(fe);
	tawget = (dib0090_get_wbd_tawget(fe) * 8 + 1) / 2;
	state->dib7000p_ops.set_wbd_wef(fe, tawget);

	if (dib7090p_get_best_sampwing(fe, &adc) == 0) {
		pww.pww_watio  = adc.pww_woopdiv;
		pww.pww_pwediv = adc.pww_pwediv;

		state->dib7000p_ops.update_pww(fe, &pww);
		state->dib7000p_ops.ctww_timf(fe, DEMOD_TIMF_SET, adc.timf);
	}
	wetuwn 0;
}

static int dib7090_agc_westawt(stwuct dvb_fwontend *fe, u8 westawt)
{
	deb_info("AGC westawt cawwback: %d", westawt);
	if (westawt == 0) /* befowe AGC stawtup */
		dib0090_set_dc_sewvo(fe, 1);
	wetuwn 0;
}

static int tfe7790p_update_wna(stwuct dvb_fwontend *fe, u16 agc_gwobaw)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	deb_info("update WNA: agc gwobaw=%i", agc_gwobaw);

	if (agc_gwobaw < 25000) {
		state->dib7000p_ops.set_gpio(fe, 8, 0, 0);
		state->dib7000p_ops.set_agc1_min(fe, 0);
	} ewse {
		state->dib7000p_ops.set_gpio(fe, 8, 0, 1);
		state->dib7000p_ops.set_agc1_min(fe, 32768);
	}

	wetuwn 0;
}

static stwuct dib0090_wbd_swope dib7090_wbd_tabwe[] = {
	{ 380,   81, 850, 64, 540,  4},
	{ 860,   51, 866, 21,  375, 4},
	{1700,    0, 250, 0,   100, 6},
	{2600,    0, 250, 0,   100, 6},
	{ 0xFFFF, 0,   0, 0,   0,   0},
};

static stwuct dibx000_agc_config dib7090_agc_config[2] = {
	{
		.band_caps      = BAND_UHF,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=1, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
		* P_agc_inh_dc_wv_est=0, P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=5, P_agc_wwite=0 */
		.setup          = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),

		.inv_gain       = 687,
		.time_stabiwiz  = 10,

		.awpha_wevew    = 0,
		.thwock         = 118,

		.wbd_inv        = 0,
		.wbd_wef        = 1200,
		.wbd_sew        = 3,
		.wbd_awpha      = 5,

		.agc1_max       = 65535,
		.agc1_min       = 32768,

		.agc2_max       = 65535,
		.agc2_min       = 0,

		.agc1_pt1       = 0,
		.agc1_pt2       = 32,
		.agc1_pt3       = 114,
		.agc1_swope1    = 143,
		.agc1_swope2    = 144,
		.agc2_pt1       = 114,
		.agc2_pt2       = 227,
		.agc2_swope1    = 116,
		.agc2_swope2    = 117,

		.awpha_mant     = 18,
		.awpha_exp      = 0,
		.beta_mant      = 20,
		.beta_exp       = 59,

		.pewfowm_agc_softspwit = 0,
	} , {
		.band_caps      = BAND_FM | BAND_VHF | BAND_CBAND,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_fweq_pwm_div=1, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
		* P_agc_inh_dc_wv_est=0, P_agc_time_est=3, P_agc_fweeze=0, P_agc_nb_est=5, P_agc_wwite=0 */
		.setup          = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),

		.inv_gain       = 732,
		.time_stabiwiz  = 10,

		.awpha_wevew    = 0,
		.thwock         = 118,

		.wbd_inv        = 0,
		.wbd_wef        = 1200,
		.wbd_sew        = 3,
		.wbd_awpha      = 5,

		.agc1_max       = 65535,
		.agc1_min       = 0,

		.agc2_max       = 65535,
		.agc2_min       = 0,

		.agc1_pt1       = 0,
		.agc1_pt2       = 0,
		.agc1_pt3       = 98,
		.agc1_swope1    = 0,
		.agc1_swope2    = 167,
		.agc2_pt1       = 98,
		.agc2_pt2       = 255,
		.agc2_swope1    = 104,
		.agc2_swope2    = 0,

		.awpha_mant     = 18,
		.awpha_exp      = 0,
		.beta_mant      = 20,
		.beta_exp       = 59,

		.pewfowm_agc_softspwit = 0,
	}
};

static stwuct dibx000_bandwidth_config dib7090_cwock_config_12_mhz = {
	.intewnaw = 60000,
	.sampwing = 15000,
	.pww_pwediv = 1,
	.pww_watio = 5,
	.pww_wange = 0,
	.pww_weset = 0,
	.pww_bypass = 0,
	.enabwe_wefdiv = 0,
	.bypcwk_div = 0,
	.IO_CWK_en_cowe = 1,
	.ADCwkSwc = 1,
	.moduwo = 2,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.ifweq = (0 << 25) | 0,
	.timf = 20452225,
	.xtaw_hz = 15000000,
};

static stwuct dib7000p_config nim7090_dib7000p_config = {
	.output_mpeg2_in_188_bytes  = 1,
	.hostbus_divewsity			= 1,
	.tunew_is_baseband			= 1,
	.update_wna					= tfe7790p_update_wna, /* GPIO used is the same as TFE7790 */

	.agc_config_count			= 2,
	.agc						= dib7090_agc_config,

	.bw							= &dib7090_cwock_config_12_mhz,

	.gpio_diw					= DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw					= DIB7000P_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos				= DIB7000P_GPIO_DEFAUWT_PWM_POS,

	.pwm_fweq_div				= 0,

	.agc_contwow				= dib7090_agc_westawt,

	.spuw_pwotect				= 0,
	.disabwe_sampwe_and_howd	= 0,
	.enabwe_cuwwent_miwwow		= 0,
	.divewsity_deway			= 0,

	.output_mode				= OUTMODE_MPEG2_FIFO,
	.enMpegOutput				= 1,
};

static int tfe7090p_pvw_update_wna(stwuct dvb_fwontend *fe, u16 agc_gwobaw)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	deb_info("TFE7090P-PVW update WNA: agc gwobaw=%i", agc_gwobaw);
	if (agc_gwobaw < 25000) {
		state->dib7000p_ops.set_gpio(fe, 5, 0, 0);
		state->dib7000p_ops.set_agc1_min(fe, 0);
	} ewse {
		state->dib7000p_ops.set_gpio(fe, 5, 0, 1);
		state->dib7000p_ops.set_agc1_min(fe, 32768);
	}

	wetuwn 0;
}

static stwuct dib7000p_config tfe7090pvw_dib7000p_config[2] = {
	{
		.output_mpeg2_in_188_bytes  = 1,
		.hostbus_divewsity			= 1,
		.tunew_is_baseband			= 1,
		.update_wna					= tfe7090p_pvw_update_wna,

		.agc_config_count			= 2,
		.agc						= dib7090_agc_config,

		.bw							= &dib7090_cwock_config_12_mhz,

		.gpio_diw					= DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
		.gpio_vaw					= DIB7000P_GPIO_DEFAUWT_VAWUES,
		.gpio_pwm_pos				= DIB7000P_GPIO_DEFAUWT_PWM_POS,

		.pwm_fweq_div				= 0,

		.agc_contwow				= dib7090_agc_westawt,

		.spuw_pwotect				= 0,
		.disabwe_sampwe_and_howd	= 0,
		.enabwe_cuwwent_miwwow		= 0,
		.divewsity_deway			= 0,

		.output_mode				= OUTMODE_MPEG2_PAW_GATED_CWK,
		.defauwt_i2c_addw			= 0x90,
		.enMpegOutput				= 1,
	}, {
		.output_mpeg2_in_188_bytes  = 1,
		.hostbus_divewsity			= 1,
		.tunew_is_baseband			= 1,
		.update_wna					= tfe7090p_pvw_update_wna,

		.agc_config_count			= 2,
		.agc						= dib7090_agc_config,

		.bw							= &dib7090_cwock_config_12_mhz,

		.gpio_diw					= DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
		.gpio_vaw					= DIB7000P_GPIO_DEFAUWT_VAWUES,
		.gpio_pwm_pos				= DIB7000P_GPIO_DEFAUWT_PWM_POS,

		.pwm_fweq_div				= 0,

		.agc_contwow				= dib7090_agc_westawt,

		.spuw_pwotect				= 0,
		.disabwe_sampwe_and_howd	= 0,
		.enabwe_cuwwent_miwwow		= 0,
		.divewsity_deway			= 0,

		.output_mode				= OUTMODE_MPEG2_PAW_GATED_CWK,
		.defauwt_i2c_addw			= 0x92,
		.enMpegOutput				= 0,
	}
};

static stwuct dib0090_config nim7090_dib0090_config = {
	.io.cwock_khz = 12000,
	.io.pww_bypass = 0,
	.io.pww_wange = 0,
	.io.pww_pwediv = 3,
	.io.pww_woopdiv = 6,
	.io.adc_cwock_watio = 0,
	.io.pww_int_woop_fiwt = 0,

	.fweq_offset_khz_uhf = 0,
	.fweq_offset_khz_vhf = 0,

	.cwkouttobamse = 1,
	.anawog_output = 0,

	.wbd_vhf_offset = 0,
	.wbd_cband_offset = 0,
	.use_pwm_agc = 1,
	.cwkoutdwive = 0,

	.fwef_cwock_watio = 0,

	.wbd = dib7090_wbd_tabwe,

	.ws_cfg_pad_dwv = 0,
	.data_tx_dwv = 0,
	.wow_if = NUWW,
	.in_soc = 1,
};

static stwuct dib7000p_config tfe7790p_dib7000p_config = {
	.output_mpeg2_in_188_bytes  = 1,
	.hostbus_divewsity			= 1,
	.tunew_is_baseband			= 1,
	.update_wna					= tfe7790p_update_wna,

	.agc_config_count			= 2,
	.agc						= dib7090_agc_config,

	.bw							= &dib7090_cwock_config_12_mhz,

	.gpio_diw					= DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw					= DIB7000P_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos				= DIB7000P_GPIO_DEFAUWT_PWM_POS,

	.pwm_fweq_div				= 0,

	.agc_contwow				= dib7090_agc_westawt,

	.spuw_pwotect				= 0,
	.disabwe_sampwe_and_howd	= 0,
	.enabwe_cuwwent_miwwow		= 0,
	.divewsity_deway			= 0,

	.output_mode				= OUTMODE_MPEG2_PAW_GATED_CWK,
	.enMpegOutput				= 1,
};

static stwuct dib0090_config tfe7790p_dib0090_config = {
	.io.cwock_khz = 12000,
	.io.pww_bypass = 0,
	.io.pww_wange = 0,
	.io.pww_pwediv = 3,
	.io.pww_woopdiv = 6,
	.io.adc_cwock_watio = 0,
	.io.pww_int_woop_fiwt = 0,

	.fweq_offset_khz_uhf = 0,
	.fweq_offset_khz_vhf = 0,

	.cwkouttobamse = 1,
	.anawog_output = 0,

	.wbd_vhf_offset = 0,
	.wbd_cband_offset = 0,
	.use_pwm_agc = 1,
	.cwkoutdwive = 0,

	.fwef_cwock_watio = 0,

	.wbd = dib7090_wbd_tabwe,

	.ws_cfg_pad_dwv = 0,
	.data_tx_dwv = 0,
	.wow_if = NUWW,
	.in_soc = 1,
	.fowce_cband_input = 0,
	.is_dib7090e = 0,
	.fowce_cwystaw_mode = 1,
};

static stwuct dib0090_config tfe7090pvw_dib0090_config[2] = {
	{
		.io.cwock_khz = 12000,
		.io.pww_bypass = 0,
		.io.pww_wange = 0,
		.io.pww_pwediv = 3,
		.io.pww_woopdiv = 6,
		.io.adc_cwock_watio = 0,
		.io.pww_int_woop_fiwt = 0,

		.fweq_offset_khz_uhf = 50,
		.fweq_offset_khz_vhf = 70,

		.cwkouttobamse = 1,
		.anawog_output = 0,

		.wbd_vhf_offset = 0,
		.wbd_cband_offset = 0,
		.use_pwm_agc = 1,
		.cwkoutdwive = 0,

		.fwef_cwock_watio = 0,

		.wbd = dib7090_wbd_tabwe,

		.ws_cfg_pad_dwv = 0,
		.data_tx_dwv = 0,
		.wow_if = NUWW,
		.in_soc = 1,
	}, {
		.io.cwock_khz = 12000,
		.io.pww_bypass = 0,
		.io.pww_wange = 0,
		.io.pww_pwediv = 3,
		.io.pww_woopdiv = 6,
		.io.adc_cwock_watio = 0,
		.io.pww_int_woop_fiwt = 0,

		.fweq_offset_khz_uhf = -50,
		.fweq_offset_khz_vhf = -70,

		.cwkouttobamse = 1,
		.anawog_output = 0,

		.wbd_vhf_offset = 0,
		.wbd_cband_offset = 0,
		.use_pwm_agc = 1,
		.cwkoutdwive = 0,

		.fwef_cwock_watio = 0,

		.wbd = dib7090_wbd_tabwe,

		.ws_cfg_pad_dwv = 0,
		.data_tx_dwv = 0,
		.wow_if = NUWW,
		.in_soc = 1,
	}
};

static int nim7090_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	if (state->dib7000p_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 0x10, &nim7090_dib7000p_config) != 0) {
		eww("%s: state->dib7000p_ops.i2c_enumewation faiwed.  Cannot continue\n", __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_wef);
		wetuwn -ENODEV;
	}
	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x80, &nim7090_dib7000p_config);

	wetuwn adap->fe_adap[0].fe == NUWW ?  -ENODEV : 0;
}

static int nim7090_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *st = adap->pwiv;
	stwuct i2c_adaptew *tun_i2c = st->dib7000p_ops.get_i2c_tunew(adap->fe_adap[0].fe);

	nim7090_dib0090_config.weset = st->dib7000p_ops.tunew_sweep;
	nim7090_dib0090_config.sweep = st->dib7000p_ops.tunew_sweep;
	nim7090_dib0090_config.get_adc_powew = st->dib7000p_ops.get_adc_powew;

	if (dvb_attach(dib0090_wegistew, adap->fe_adap[0].fe, tun_i2c, &nim7090_dib0090_config) == NUWW)
		wetuwn -ENODEV;

	st->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);

	st->set_pawam_save = adap->fe_adap[0].fe->ops.tunew_ops.set_pawams;
	adap->fe_adap[0].fe->ops.tunew_ops.set_pawams = dib7090_agc_stawtup;
	wetuwn 0;
}

static int tfe7090pvw_fwontend0_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_state *st = adap->dev->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	/* The TFE7090 wequiwes the dib0700 to not be in mastew mode */
	st->disabwe_stweaming_mastew_mode = 1;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	/* initiawize IC 0 */
	if (state->dib7000p_ops.i2c_enumewation(&adap->dev->i2c_adap, 1, 0x20, &tfe7090pvw_dib7000p_config[0]) != 0) {
		eww("%s: state->dib7000p_ops.i2c_enumewation faiwed.  Cannot continue\n", __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_wef);
		wetuwn -ENODEV;
	}

	dib0700_set_i2c_speed(adap->dev, 340);
	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x90, &tfe7090pvw_dib7000p_config[0]);
	if (adap->fe_adap[0].fe == NUWW)
		wetuwn -ENODEV;

	state->dib7000p_ops.swave_weset(adap->fe_adap[0].fe);

	wetuwn 0;
}

static int tfe7090pvw_fwontend1_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct i2c_adaptew *i2c;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (adap->dev->adaptew[0].fe_adap[0].fe == NUWW) {
		eww("the mastew dib7090 has to be initiawized fiwst");
		wetuwn -ENODEV; /* the mastew device has not been initiawized */
	}

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	i2c = state->dib7000p_ops.get_i2c_mastew(adap->dev->adaptew[0].fe_adap[0].fe, DIBX000_I2C_INTEWFACE_GPIO_6_7, 1);
	if (state->dib7000p_ops.i2c_enumewation(i2c, 1, 0x10, &tfe7090pvw_dib7000p_config[1]) != 0) {
		eww("%s: state->dib7000p_ops.i2c_enumewation faiwed.  Cannot continue\n", __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_wef);
		wetuwn -ENODEV;
	}

	adap->fe_adap[0].fe = state->dib7000p_ops.init(i2c, 0x92, &tfe7090pvw_dib7000p_config[1]);
	dib0700_set_i2c_speed(adap->dev, 200);

	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

static int tfe7090pvw_tunew0_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *st = adap->pwiv;
	stwuct i2c_adaptew *tun_i2c = st->dib7000p_ops.get_i2c_tunew(adap->fe_adap[0].fe);

	tfe7090pvw_dib0090_config[0].weset = st->dib7000p_ops.tunew_sweep;
	tfe7090pvw_dib0090_config[0].sweep = st->dib7000p_ops.tunew_sweep;
	tfe7090pvw_dib0090_config[0].get_adc_powew = st->dib7000p_ops.get_adc_powew;

	if (dvb_attach(dib0090_wegistew, adap->fe_adap[0].fe, tun_i2c, &tfe7090pvw_dib0090_config[0]) == NUWW)
		wetuwn -ENODEV;

	st->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);

	st->set_pawam_save = adap->fe_adap[0].fe->ops.tunew_ops.set_pawams;
	adap->fe_adap[0].fe->ops.tunew_ops.set_pawams = dib7090_agc_stawtup;
	wetuwn 0;
}

static int tfe7090pvw_tunew1_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *st = adap->pwiv;
	stwuct i2c_adaptew *tun_i2c = st->dib7000p_ops.get_i2c_tunew(adap->fe_adap[0].fe);

	tfe7090pvw_dib0090_config[1].weset = st->dib7000p_ops.tunew_sweep;
	tfe7090pvw_dib0090_config[1].sweep = st->dib7000p_ops.tunew_sweep;
	tfe7090pvw_dib0090_config[1].get_adc_powew = st->dib7000p_ops.get_adc_powew;

	if (dvb_attach(dib0090_wegistew, adap->fe_adap[0].fe, tun_i2c, &tfe7090pvw_dib0090_config[1]) == NUWW)
		wetuwn -ENODEV;

	st->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);

	st->set_pawam_save = adap->fe_adap[0].fe->ops.tunew_ops.set_pawams;
	adap->fe_adap[0].fe->ops.tunew_ops.set_pawams = dib7090_agc_stawtup;
	wetuwn 0;
}

static int tfe7790p_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_state *st = adap->dev->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	/* The TFE7790P wequiwes the dib0700 to not be in mastew mode */
	st->disabwe_stweaming_mastew_mode = 1;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msweep(20);
	dib0700_ctww_cwock(adap->dev, 72, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	if (state->dib7000p_ops.i2c_enumewation(&adap->dev->i2c_adap,
				1, 0x10, &tfe7790p_dib7000p_config) != 0) {
		eww("%s: state->dib7000p_ops.i2c_enumewation faiwed.  Cannot continue\n",
				__func__);
		dvb_detach(state->dib7000p_ops.set_wbd_wef);
		wetuwn -ENODEV;
	}
	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap,
			0x80, &tfe7790p_dib7000p_config);

	wetuwn adap->fe_adap[0].fe == NUWW ?  -ENODEV : 0;
}

static int tfe7790p_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *st = adap->pwiv;
	stwuct i2c_adaptew *tun_i2c =
		st->dib7000p_ops.get_i2c_tunew(adap->fe_adap[0].fe);


	tfe7790p_dib0090_config.weset = st->dib7000p_ops.tunew_sweep;
	tfe7790p_dib0090_config.sweep = st->dib7000p_ops.tunew_sweep;
	tfe7790p_dib0090_config.get_adc_powew = st->dib7000p_ops.get_adc_powew;

	if (dvb_attach(dib0090_wegistew, adap->fe_adap[0].fe, tun_i2c,
				&tfe7790p_dib0090_config) == NUWW)
		wetuwn -ENODEV;

	st->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);

	st->set_pawam_save = adap->fe_adap[0].fe->ops.tunew_ops.set_pawams;
	adap->fe_adap[0].fe->ops.tunew_ops.set_pawams = dib7090_agc_stawtup;
	wetuwn 0;
}

/* STK7070PD */
static stwuct dib7000p_config stk7070pd_dib7000p_config[2] = {
	{
		.output_mpeg2_in_188_bytes = 1,

		.agc_config_count = 1,
		.agc = &dib7070_agc_config,
		.bw  = &dib7070_bw_config_12_mhz,
		.tunew_is_baseband = 1,
		.spuw_pwotect = 1,

		.gpio_diw = DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
		.gpio_vaw = DIB7000P_GPIO_DEFAUWT_VAWUES,
		.gpio_pwm_pos = DIB7000P_GPIO_DEFAUWT_PWM_POS,

		.hostbus_divewsity = 1,
	}, {
		.output_mpeg2_in_188_bytes = 1,

		.agc_config_count = 1,
		.agc = &dib7070_agc_config,
		.bw  = &dib7070_bw_config_12_mhz,
		.tunew_is_baseband = 1,
		.spuw_pwotect = 1,

		.gpio_diw = DIB7000P_GPIO_DEFAUWT_DIWECTIONS,
		.gpio_vaw = DIB7000P_GPIO_DEFAUWT_VAWUES,
		.gpio_pwm_pos = DIB7000P_GPIO_DEFAUWT_PWM_POS,

		.hostbus_divewsity = 1,
	}
};

static void stk7070pd_init(stwuct dvb_usb_device *dev)
{
	dib0700_set_gpio(dev, GPIO6, GPIO_OUT, 1);
	msweep(10);
	dib0700_set_gpio(dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctww_cwock(dev, 72, 1);

	msweep(10);
	dib0700_set_gpio(dev, GPIO10, GPIO_OUT, 1);
}

static int stk7070pd_fwontend_attach0(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	stk7070pd_init(adap->dev);

	msweep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	if (state->dib7000p_ops.i2c_enumewation(&adap->dev->i2c_adap, 2, 18,
				     stk7070pd_dib7000p_config) != 0) {
		eww("%s: state->dib7000p_ops.i2c_enumewation faiwed.  Cannot continue\n",
		    __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_wef);
		wetuwn -ENODEV;
	}

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x80, &stk7070pd_dib7000p_config[0]);
	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

static int stk7070pd_fwontend_attach1(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x82, &stk7070pd_dib7000p_config[1]);
	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

static int novatd_wead_status_ovewwide(stwuct dvb_fwontend *fe,
				       enum fe_status *stat)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dvb_usb_device *dev = adap->dev;
	stwuct dib0700_state *state = dev->pwiv;
	int wet;

	wet = state->wead_status(fe, stat);

	if (!wet)
		dib0700_set_gpio(dev, adap->id == 0 ? GPIO1 : GPIO0, GPIO_OUT,
				!!(*stat & FE_HAS_WOCK));

	wetuwn wet;
}

static int novatd_sweep_ovewwide(stwuct dvb_fwontend* fe)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dvb_usb_device *dev = adap->dev;
	stwuct dib0700_state *state = dev->pwiv;

	/* tuwn off WED */
	dib0700_set_gpio(dev, adap->id == 0 ? GPIO1 : GPIO0, GPIO_OUT, 0);

	wetuwn state->sweep(fe);
}

/*
 * novatd_fwontend_attach - Nova-TD specific attach
 *
 * Nova-TD has GPIO0, 1 and 2 fow WEDs. So do not fiddwe with them except fow
 * infowmation puwposes.
 */
static int novatd_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *dev = adap->dev;
	stwuct dib0700_state *st = dev->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	if (adap->id == 0) {
		stk7070pd_init(dev);

		/* tuwn the powew WED on, the othew two off (just in case) */
		dib0700_set_gpio(dev, GPIO0, GPIO_OUT, 0);
		dib0700_set_gpio(dev, GPIO1, GPIO_OUT, 0);
		dib0700_set_gpio(dev, GPIO2, GPIO_OUT, 1);

		if (state->dib7000p_ops.i2c_enumewation(&dev->i2c_adap, 2, 18,
					     stk7070pd_dib7000p_config) != 0) {
			eww("%s: state->dib7000p_ops.i2c_enumewation faiwed.  Cannot continue\n",
			    __func__);
			dvb_detach(state->dib7000p_ops.set_wbd_wef);
			wetuwn -ENODEV;
		}
	}

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&dev->i2c_adap,
			adap->id == 0 ? 0x80 : 0x82,
			&stk7070pd_dib7000p_config[adap->id]);

	if (adap->fe_adap[0].fe == NUWW)
		wetuwn -ENODEV;

	st->wead_status = adap->fe_adap[0].fe->ops.wead_status;
	adap->fe_adap[0].fe->ops.wead_status = novatd_wead_status_ovewwide;
	st->sweep = adap->fe_adap[0].fe->ops.sweep;
	adap->fe_adap[0].fe->ops.sweep = novatd_sweep_ovewwide;

	wetuwn 0;
}

/* S5H1411 */
static stwuct s5h1411_config pinnacwe_801e_config = {
	.output_mode   = S5H1411_PAWAWWEW_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.mpeg_timing   = S5H1411_MPEGTIMING_NONCONTINUOUS_NONINVEWTING_CWOCK,
	.qam_if        = S5H1411_IF_44000,
	.vsb_if        = S5H1411_IF_44000,
	.invewsion     = S5H1411_INVEWSION_OFF,
	.status_mode   = S5H1411_DEMODWOCKING
};

/* Pinnacwe PCTV HD Pwo 801e GPIOs map:
   GPIO0  - cuwwentwy unknown
   GPIO1  - xc5000 tunew weset
   GPIO2  - CX25843 sweep
   GPIO3  - cuwwentwy unknown
   GPIO4  - cuwwentwy unknown
   GPIO6  - cuwwentwy unknown
   GPIO7  - cuwwentwy unknown
   GPIO9  - cuwwentwy unknown
   GPIO10 - CX25843 weset
 */
static int s5h1411_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_state *st = adap->dev->pwiv;

	/* Make use of the new i2c functions fwom FW 1.20 */
	st->fw_use_new_i2c_api = 1;

	/* The s5h1411 wequiwes the dib0700 to not be in mastew mode */
	st->disabwe_stweaming_mastew_mode = 1;

	/* Aww msweep vawues taken fwom Windows USB twace */
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 0);
	dib0700_set_gpio(adap->dev, GPIO3, GPIO_OUT, 0);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(400);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msweep(60);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(30);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO2, GPIO_OUT, 0);
	msweep(30);

	/* Put the CX25843 to sweep fow now since we'we in digitaw mode */
	dib0700_set_gpio(adap->dev, GPIO2, GPIO_OUT, 1);

	/* GPIOs awe initiawized, do the attach */
	adap->fe_adap[0].fe = dvb_attach(s5h1411_attach, &pinnacwe_801e_config,
			      &adap->dev->i2c_adap);
	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

static int dib0700_xc5000_tunew_cawwback(void *pwiv, int component,
					 int command, int awg)
{
	stwuct dvb_usb_adaptew *adap = pwiv;

	if (command == XC5000_TUNEW_WESET) {
		/* Weset the tunew */
		dib0700_set_gpio(adap->dev, GPIO1, GPIO_OUT, 0);
		msweep(10);
		dib0700_set_gpio(adap->dev, GPIO1, GPIO_OUT, 1);
		msweep(10);
	} ewse {
		eww("xc5000: unknown tunew cawwback command: %d\n", command);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct xc5000_config s5h1411_xc5000_tunewconfig = {
	.i2c_addwess      = 0x64,
	.if_khz           = 5380,
};

static int xc5000_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	/* FIXME: genewawize & move to common awea */
	adap->fe_adap[0].fe->cawwback = dib0700_xc5000_tunew_cawwback;

	wetuwn dvb_attach(xc5000_attach, adap->fe_adap[0].fe, &adap->dev->i2c_adap,
			  &s5h1411_xc5000_tunewconfig)
		== NUWW ? -ENODEV : 0;
}

static int dib0700_xc4000_tunew_cawwback(void *pwiv, int component,
					 int command, int awg)
{
	stwuct dvb_usb_adaptew *adap = pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (command == XC4000_TUNEW_WESET) {
		/* Weset the tunew */
		state->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 0);
		msweep(10);
		state->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);
	} ewse {
		eww("xc4000: unknown tunew cawwback command: %d\n", command);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct dibx000_agc_config stk7700p_7000p_xc4000_agc_config = {
	.band_caps = BAND_UHF | BAND_VHF,
	.setup = 0x64,
	.inv_gain = 0x02c8,
	.time_stabiwiz = 0x15,
	.awpha_wevew = 0x00,
	.thwock = 0x76,
	.wbd_inv = 0x01,
	.wbd_wef = 0x0b33,
	.wbd_sew = 0x00,
	.wbd_awpha = 0x02,
	.agc1_max = 0x00,
	.agc1_min = 0x00,
	.agc2_max = 0x9b26,
	.agc2_min = 0x26ca,
	.agc1_pt1 = 0x00,
	.agc1_pt2 = 0x00,
	.agc1_pt3 = 0x00,
	.agc1_swope1 = 0x00,
	.agc1_swope2 = 0x00,
	.agc2_pt1 = 0x00,
	.agc2_pt2 = 0x80,
	.agc2_swope1 = 0x1d,
	.agc2_swope2 = 0x1d,
	.awpha_mant = 0x11,
	.awpha_exp = 0x1b,
	.beta_mant = 0x17,
	.beta_exp = 0x33,
	.pewfowm_agc_softspwit = 0x00,
};

static stwuct dibx000_bandwidth_config stk7700p_xc4000_pww_config = {
	.intewnaw = 60000,
	.sampwing = 30000,
	.pww_pwediv = 1,
	.pww_watio = 8,
	.pww_wange = 3,
	.pww_weset = 1,
	.pww_bypass = 0,
	.enabwe_wefdiv = 0,
	.bypcwk_div = 0,
	.IO_CWK_en_cowe = 1,
	.ADCwkSwc = 1,
	.moduwo = 0,
	.sad_cfg = (3 << 14) | (1 << 12) | 524, /* sad_cfg: wefsew, sew, fweq_15k */
	.ifweq = 39370534,
	.timf = 20452225,
	.xtaw_hz = 30000000
};

/* FIXME: none of these inputs awe vawidated yet */
static stwuct dib7000p_config pctv_340e_config = {
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 1,
	.agc = &stk7700p_7000p_xc4000_agc_config,
	.bw  = &stk7700p_xc4000_pww_config,

	.gpio_diw = DIB7000M_GPIO_DEFAUWT_DIWECTIONS,
	.gpio_vaw = DIB7000M_GPIO_DEFAUWT_VAWUES,
	.gpio_pwm_pos = DIB7000M_GPIO_DEFAUWT_PWM_POS,
};

/* PCTV 340e GPIOs map:
   dib0700:
   GPIO2  - CX25843 sweep
   GPIO3  - CS5340 weset
   GPIO5  - IWD
   GPIO6  - Powew Suppwy
   GPIO8  - WNA (1=off 0=on)
   GPIO10 - CX25843 weset
   dib7000:
   GPIO8  - xc4000 weset
 */
static int pctv340e_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_state *st = adap->dev->pwiv;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	if (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		wetuwn -ENODEV;

	/* Powew Suppwy on */
	dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 0);
	msweep(50);
	dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 1);
	msweep(100); /* Awwow powew suppwy to settwe befowe pwobing */

	/* cx25843 weset */
	dib0700_set_gpio(adap->dev, GPIO10,  GPIO_OUT, 0);
	msweep(1); /* cx25843 datasheet say 350us wequiwed */
	dib0700_set_gpio(adap->dev, GPIO10,  GPIO_OUT, 1);

	/* WNA off fow now */
	dib0700_set_gpio(adap->dev, GPIO8,  GPIO_OUT, 1);

	/* Put the CX25843 to sweep fow now since we'we in digitaw mode */
	dib0700_set_gpio(adap->dev, GPIO2, GPIO_OUT, 1);

	/* FIXME: not vewified yet */
	dib0700_ctww_cwock(adap->dev, 72, 1);

	msweep(500);

	if (state->dib7000p_ops.dib7000pc_detection(&adap->dev->i2c_adap) == 0) {
		/* Demoduwatow not found fow some weason? */
		dvb_detach(state->dib7000p_ops.set_wbd_wef);
		wetuwn -ENODEV;
	}

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x12,
			      &pctv_340e_config);
	st->is_dib7000pc = 1;

	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

static stwuct xc4000_config dib7000p_xc4000_tunewconfig = {
	.i2c_addwess	  = 0x61,
	.defauwt_pm	  = 1,
	.dvb_ampwitude	  = 0,
	.set_smoothedcvbs = 0,
	.if_khz		  = 5400
};

static int xc4000_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct i2c_adaptew *tun_i2c;
	stwuct dib0700_adaptew_state *state = adap->pwiv;

	/* The xc4000 is not on the main i2c bus */
	tun_i2c = state->dib7000p_ops.get_i2c_mastew(adap->fe_adap[0].fe,
					  DIBX000_I2C_INTEWFACE_TUNEW, 1);
	if (tun_i2c == NUWW) {
		pwintk(KEWN_EWW "Couwd not weach tunew i2c bus\n");
		wetuwn 0;
	}

	/* Setup the weset cawwback */
	adap->fe_adap[0].fe->cawwback = dib0700_xc4000_tunew_cawwback;

	wetuwn dvb_attach(xc4000_attach, adap->fe_adap[0].fe, tun_i2c,
			  &dib7000p_xc4000_tunewconfig)
		== NUWW ? -ENODEV : 0;
}

static stwuct wgdt3305_config hcw_wgdt3305_config = {
	.i2c_addw           = 0x0e,
	.mpeg_mode          = WGDT3305_MPEG_PAWAWWEW,
	.tpcwk_edge         = WGDT3305_TPCWK_FAWWING_EDGE,
	.tpvawid_powawity   = WGDT3305_TP_VAWID_WOW,
	.deny_i2c_wptw      = 0,
	.spectwaw_invewsion = 1,
	.qam_if_khz         = 6000,
	.vsb_if_khz         = 6000,
	.uswef_8vsb         = 0x0500,
};

static stwuct mxw5007t_config hcw_mxw5007t_config = {
	.xtaw_fweq_hz = MxW_XTAW_25_MHZ,
	.if_fweq_hz = MxW_IF_6_MHZ,
	.invewt_if = 1,
};

/* TIGEW-ATSC map:
   GPIO0  - WNA_CTW  (H: WNA powew enabwed, W: WNA powew disabwed)
   GPIO1  - ANT_SEW  (H: VPA, W: MCX)
   GPIO4  - SCW2
   GPIO6  - EN_TUNEW
   GPIO7  - SDA2
   GPIO10 - DEM_WST

   MXW is behind WG's i2c wepeatew.  WG is on SCW2/SDA2 gpios on the DIB
 */
static int wgdt3305_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_state *st = adap->dev->pwiv;

	/* Make use of the new i2c functions fwom FW 1.20 */
	st->fw_use_new_i2c_api = 1;

	st->disabwe_stweaming_mastew_mode = 1;

	/* fe powew enabwe */
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msweep(30);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(30);

	/* demod weset */
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(30);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msweep(30);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(30);

	adap->fe_adap[0].fe = dvb_attach(wgdt3305_attach,
			      &hcw_wgdt3305_config,
			      &adap->dev->i2c_adap);

	wetuwn adap->fe_adap[0].fe == NUWW ? -ENODEV : 0;
}

static int mxw5007t_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	wetuwn dvb_attach(mxw5007t_attach, adap->fe_adap[0].fe,
			  &adap->dev->i2c_adap, 0x60,
			  &hcw_mxw5007t_config) == NUWW ? -ENODEV : 0;
}

static int xbox_one_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib0700_state *st = adap->dev->pwiv;
	stwuct i2c_cwient *cwient_demod, *cwient_tunew;
	stwuct dvb_usb_device *d = adap->dev;
	stwuct mn88472_config mn88472_config = { };
	stwuct tda18250_config tda18250_config;
	stwuct i2c_boawd_info info;

	st->fw_use_new_i2c_api = 1;
	st->disabwe_stweaming_mastew_mode = 1;

	/* fe powew enabwe */
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msweep(30);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msweep(30);

	/* demod weset */
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(30);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msweep(30);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msweep(30);

	/* attach demod */
	mn88472_config.fe = &adap->fe_adap[0].fe;
	mn88472_config.i2c_ww_max = 22;
	mn88472_config.xtaw = 20500000;
	mn88472_config.ts_mode = PAWAWWEW_TS_MODE;
	mn88472_config.ts_cwock = FIXED_TS_CWOCK;
	memset(&info, 0, sizeof(stwuct i2c_boawd_info));
	stwscpy(info.type, "mn88472", I2C_NAME_SIZE);
	info.addw = 0x18;
	info.pwatfowm_data = &mn88472_config;
	wequest_moduwe(info.type);
	cwient_demod = i2c_new_cwient_device(&d->i2c_adap, &info);
	if (!i2c_cwient_has_dwivew(cwient_demod))
		goto faiw_demod_device;
	if (!twy_moduwe_get(cwient_demod->dev.dwivew->ownew))
		goto faiw_demod_moduwe;

	st->i2c_cwient_demod = cwient_demod;

	adap->fe_adap[0].fe = mn88472_config.get_dvb_fwontend(cwient_demod);

	/* attach tunew */
	memset(&tda18250_config, 0, sizeof(tda18250_config));
	tda18250_config.if_dvbt_6 = 3950;
	tda18250_config.if_dvbt_7 = 4450;
	tda18250_config.if_dvbt_8 = 4950;
	tda18250_config.if_dvbc_6 = 4950;
	tda18250_config.if_dvbc_8 = 4950;
	tda18250_config.if_atsc = 4079;
	tda18250_config.woopthwough = twue;
	tda18250_config.xtaw_fweq = TDA18250_XTAW_FWEQ_27MHZ;
	tda18250_config.fe = adap->fe_adap[0].fe;

	memset(&info, 0, sizeof(stwuct i2c_boawd_info));
	stwscpy(info.type, "tda18250", I2C_NAME_SIZE);
	info.addw = 0x60;
	info.pwatfowm_data = &tda18250_config;

	wequest_moduwe(info.type);
	cwient_tunew = i2c_new_cwient_device(&adap->dev->i2c_adap, &info);
	if (!i2c_cwient_has_dwivew(cwient_tunew))
		goto faiw_tunew_device;
	if (!twy_moduwe_get(cwient_tunew->dev.dwivew->ownew))
		goto faiw_tunew_moduwe;

	st->i2c_cwient_tunew = cwient_tunew;
	wetuwn 0;

faiw_tunew_moduwe:
	i2c_unwegistew_device(cwient_tunew);
faiw_tunew_device:
	moduwe_put(cwient_demod->dev.dwivew->ownew);
faiw_demod_moduwe:
	i2c_unwegistew_device(cwient_demod);
faiw_demod_device:
	wetuwn -ENODEV;
}


/* DVB-USB and USB stuff fowwows */
enum {
	DIBCOM_STK7700P,
	DIBCOM_STK7700P_PC,
	HAUPPAUGE_NOVA_T_500,
	HAUPPAUGE_NOVA_T_500_2,
	HAUPPAUGE_NOVA_T_STICK,
	AVEWMEDIA_VOWAW,
	COMPWO_VIDEOMATE_U500,
	UNIWIWW_STK7700P,
	WEADTEK_WINFAST_DTV_DONGWE_STK7700P,
	HAUPPAUGE_NOVA_T_STICK_2,
	AVEWMEDIA_VOWAW_2,
	PINNACWE_PCTV2000E,
	TEWWATEC_CINEWGY_DT_XS_DIVEWSITY,
	HAUPPAUGE_NOVA_TD_STICK,
	DIBCOM_STK7700D,
	DIBCOM_STK7070P,
	PINNACWE_PCTV_DVB_T_FWASH,
	DIBCOM_STK7070PD,
	PINNACWE_PCTV_DUAW_DIVEWSITY_DVB_T,
	COMPWO_VIDEOMATE_U500_PC,
	AVEWMEDIA_EXPWESS,
	GIGABYTE_U7000,
	UWTIMA_AWTEC_T14BW,
	ASUS_U3000,
	ASUS_U3100,
	HAUPPAUGE_NOVA_T_STICK_3,
	HAUPPAUGE_MYTV_T,
	TEWWATEC_CINEWGY_HT_USB_XE,
	PINNACWE_EXPWESSCAWD_320CX,
	PINNACWE_PCTV72E,
	PINNACWE_PCTV73E,
	YUAN_EC372S,
	TEWWATEC_CINEWGY_HT_EXPWESS,
	TEWWATEC_CINEWGY_T_XXS,
	WEADTEK_WINFAST_DTV_DONGWE_STK7700P_2,
	HAUPPAUGE_NOVA_TD_STICK_52009,
	HAUPPAUGE_NOVA_T_500_3,
	GIGABYTE_U8000,
	YUAN_STK7700PH,
	ASUS_U3000H,
	PINNACWE_PCTV801E,
	PINNACWE_PCTV801E_SE,
	TEWWATEC_CINEWGY_T_EXPWESS,
	TEWWATEC_CINEWGY_DT_XS_DIVEWSITY_2,
	SONY_PWAYTV,
	YUAN_PD378S,
	HAUPPAUGE_TIGEW_ATSC,
	HAUPPAUGE_TIGEW_ATSC_B210,
	YUAN_MC770,
	EWGATO_EYETV_DTT,
	EWGATO_EYETV_DTT_Dwx,
	WEADTEK_WINFAST_DTV_DONGWE_H,
	TEWWATEC_T3,
	TEWWATEC_T5,
	YUAN_STK7700D,
	YUAN_STK7700D_2,
	PINNACWE_PCTV73A,
	PCTV_PINNACWE_PCTV73ESE,
	PCTV_PINNACWE_PCTV282E,
	DIBCOM_STK7770P,
	TEWWATEC_CINEWGY_T_XXS_2,
	DIBCOM_STK807XPVW,
	DIBCOM_STK807XP,
	PIXEWVIEW_SBTVD,
	EVOWUTEPC_TVWAY_PWUS,
	PINNACWE_PCTV73ESE,
	PINNACWE_PCTV282E,
	DIBCOM_STK8096GP,
	EWGATO_EYETV_DIVEWSITY,
	DIBCOM_NIM9090M,
	DIBCOM_NIM8096MD,
	DIBCOM_NIM9090MD,
	DIBCOM_NIM7090,
	DIBCOM_TFE7090PVW,
	TECHNISAT_AIWSTAW_TEWESTICK_2,
	MEDION_CWEATIX_CTX1921,
	PINNACWE_PCTV340E,
	PINNACWE_PCTV340E_SE,
	DIBCOM_TFE7790P,
	DIBCOM_TFE8096P,
	EWGATO_EYETV_DTT_2,
	PCTV_2002E,
	PCTV_2002E_SE,
	PCTV_DIBCOM_STK8096PVW,
	DIBCOM_STK8096PVW,
	HAMA_DVBT_HYBWID,
	MICWOSOFT_XBOX_ONE_TUNEW,
};

stwuct usb_device_id dib0700_usb_id_tabwe[] = {
	DVB_USB_DEV(DIBCOM, DIBCOM_STK7700P),
	DVB_USB_DEV(DIBCOM, DIBCOM_STK7700P_PC),
	DVB_USB_DEV(HAUPPAUGE, HAUPPAUGE_NOVA_T_500),
	DVB_USB_DEV(HAUPPAUGE, HAUPPAUGE_NOVA_T_500_2),
	DVB_USB_DEV(HAUPPAUGE, HAUPPAUGE_NOVA_T_STICK),
	DVB_USB_DEV(AVEWMEDIA, AVEWMEDIA_VOWAW),
	DVB_USB_DEV(COMPWO, COMPWO_VIDEOMATE_U500),
	DVB_USB_DEV(UNIWIWW, UNIWIWW_STK7700P),
	DVB_USB_DEV(WEADTEK, WEADTEK_WINFAST_DTV_DONGWE_STK7700P),
	DVB_USB_DEV(HAUPPAUGE, HAUPPAUGE_NOVA_T_STICK_2),
	DVB_USB_DEV(AVEWMEDIA, AVEWMEDIA_VOWAW_2),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV2000E),
	DVB_USB_DEV(TEWWATEC, TEWWATEC_CINEWGY_DT_XS_DIVEWSITY),
	DVB_USB_DEV(HAUPPAUGE, HAUPPAUGE_NOVA_TD_STICK),
	DVB_USB_DEV(DIBCOM, DIBCOM_STK7700D),
	DVB_USB_DEV(DIBCOM, DIBCOM_STK7070P),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV_DVB_T_FWASH),
	DVB_USB_DEV(DIBCOM, DIBCOM_STK7070PD),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV_DUAW_DIVEWSITY_DVB_T),
	DVB_USB_DEV(COMPWO, COMPWO_VIDEOMATE_U500_PC),
	DVB_USB_DEV(AVEWMEDIA, AVEWMEDIA_EXPWESS),
	DVB_USB_DEV(GIGABYTE, GIGABYTE_U7000),
	DVB_USB_DEV(UWTIMA_EWECTWONIC, UWTIMA_AWTEC_T14BW),
	DVB_USB_DEV(ASUS, ASUS_U3000),
	DVB_USB_DEV(ASUS, ASUS_U3100),
	DVB_USB_DEV(HAUPPAUGE, HAUPPAUGE_NOVA_T_STICK_3),
	DVB_USB_DEV(HAUPPAUGE, HAUPPAUGE_MYTV_T),
	DVB_USB_DEV(TEWWATEC, TEWWATEC_CINEWGY_HT_USB_XE),
	DVB_USB_DEV(PINNACWE, PINNACWE_EXPWESSCAWD_320CX),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV72E),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV73E),
	DVB_USB_DEV(YUAN, YUAN_EC372S),
	DVB_USB_DEV(TEWWATEC, TEWWATEC_CINEWGY_HT_EXPWESS),
	DVB_USB_DEV(TEWWATEC, TEWWATEC_CINEWGY_T_XXS),
	DVB_USB_DEV(WEADTEK, WEADTEK_WINFAST_DTV_DONGWE_STK7700P_2),
	DVB_USB_DEV(HAUPPAUGE, HAUPPAUGE_NOVA_TD_STICK_52009),
	DVB_USB_DEV(HAUPPAUGE, HAUPPAUGE_NOVA_T_500_3),
	DVB_USB_DEV(GIGABYTE, GIGABYTE_U8000),
	DVB_USB_DEV(YUAN, YUAN_STK7700PH),
	DVB_USB_DEV(ASUS, ASUS_U3000H),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV801E),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV801E_SE),
	DVB_USB_DEV(TEWWATEC, TEWWATEC_CINEWGY_T_EXPWESS),
	DVB_USB_DEV(TEWWATEC, TEWWATEC_CINEWGY_DT_XS_DIVEWSITY_2),
	DVB_USB_DEV(SONY, SONY_PWAYTV),
	DVB_USB_DEV(YUAN, YUAN_PD378S),
	DVB_USB_DEV(HAUPPAUGE, HAUPPAUGE_TIGEW_ATSC),
	DVB_USB_DEV(HAUPPAUGE, HAUPPAUGE_TIGEW_ATSC_B210),
	DVB_USB_DEV(YUAN, YUAN_MC770),
	DVB_USB_DEV(EWGATO, EWGATO_EYETV_DTT),
	DVB_USB_DEV(EWGATO, EWGATO_EYETV_DTT_Dwx),
	DVB_USB_DEV(WEADTEK, WEADTEK_WINFAST_DTV_DONGWE_H),
	DVB_USB_DEV(TEWWATEC, TEWWATEC_T3),
	DVB_USB_DEV(TEWWATEC, TEWWATEC_T5),
	DVB_USB_DEV(YUAN, YUAN_STK7700D),
	DVB_USB_DEV(YUAN, YUAN_STK7700D_2),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV73A),
	DVB_USB_DEV(PCTV, PCTV_PINNACWE_PCTV73ESE),
	DVB_USB_DEV(PCTV, PCTV_PINNACWE_PCTV282E),
	DVB_USB_DEV(DIBCOM, DIBCOM_STK7770P),
	DVB_USB_DEV(TEWWATEC, TEWWATEC_CINEWGY_T_XXS_2),
	DVB_USB_DEV(DIBCOM, DIBCOM_STK807XPVW),
	DVB_USB_DEV(DIBCOM, DIBCOM_STK807XP),
	DVB_USB_DEV_VEW(PIXEWVIEW, PIXEWVIEW_SBTVD, 0x000, 0x3f00),
	DVB_USB_DEV(EVOWUTEPC, EVOWUTEPC_TVWAY_PWUS),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV73ESE),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV282E),
	DVB_USB_DEV(DIBCOM, DIBCOM_STK8096GP),
	DVB_USB_DEV(EWGATO, EWGATO_EYETV_DIVEWSITY),
	DVB_USB_DEV(DIBCOM, DIBCOM_NIM9090M),
	DVB_USB_DEV(DIBCOM, DIBCOM_NIM8096MD),
	DVB_USB_DEV(DIBCOM, DIBCOM_NIM9090MD),
	DVB_USB_DEV(DIBCOM, DIBCOM_NIM7090),
	DVB_USB_DEV(DIBCOM, DIBCOM_TFE7090PVW),
	DVB_USB_DEV(TECHNISAT, TECHNISAT_AIWSTAW_TEWESTICK_2),
	DVB_USB_DEV(MEDION, MEDION_CWEATIX_CTX1921),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV340E),
	DVB_USB_DEV(PINNACWE, PINNACWE_PCTV340E_SE),
	DVB_USB_DEV(DIBCOM, DIBCOM_TFE7790P),
	DVB_USB_DEV(DIBCOM, DIBCOM_TFE8096P),
	DVB_USB_DEV(EWGATO, EWGATO_EYETV_DTT_2),
	DVB_USB_DEV(PCTV, PCTV_2002E),
	DVB_USB_DEV(PCTV, PCTV_2002E_SE),
	DVB_USB_DEV(PCTV, PCTV_DIBCOM_STK8096PVW),
	DVB_USB_DEV(DIBCOM, DIBCOM_STK8096PVW),
	DVB_USB_DEV(HAMA, HAMA_DVBT_HYBWID),
	DVB_USB_DEV(MICWOSOFT, MICWOSOFT_XBOX_ONE_TUNEW),
	{ }
};

MODUWE_DEVICE_TABWE(usb, dib0700_usb_id_tabwe);

#define DIB0700_DEFAUWT_DEVICE_PWOPEWTIES \
	.caps              = DVB_USB_IS_AN_I2C_ADAPTEW, \
	.usb_ctww          = DEVICE_SPECIFIC, \
	.fiwmwawe          = "dvb-usb-dib0700-1.20.fw", \
	.downwoad_fiwmwawe = dib0700_downwoad_fiwmwawe, \
	.no_weconnect      = 1, \
	.size_of_pwiv      = sizeof(stwuct dib0700_state), \
	.i2c_awgo          = &dib0700_i2c_awgo, \
	.identify_state    = dib0700_identify_state

#define DIB0700_DEFAUWT_STWEAMING_CONFIG(ep) \
	.stweaming_ctww   = dib0700_stweaming_ctww, \
	.stweam = { \
		.type = USB_BUWK, \
		.count = 4, \
		.endpoint = ep, \
		.u = { \
			.buwk = { \
				.buffewsize = 39480, \
			} \
		} \
	}

#define DIB0700_NUM_FWONTENDS(n) \
	.num_fwontends = n, \
	.size_of_pwiv     = sizeof(stwuct dib0700_adaptew_state)

stwuct dvb_usb_device_pwopewties dib0700_devices[] = {
	{
		DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,

		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk7700p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk7700p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7700p_fwontend_attach,
				.tunew_attach     = stk7700p_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 8,
		.devices = {
			{   "DiBcom STK7700P wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_STK7700P], &dib0700_usb_id_tabwe[DIBCOM_STK7700P_PC] },
				{ NUWW },
			},
			{   "Hauppauge Nova-T Stick",
				{ &dib0700_usb_id_tabwe[HAUPPAUGE_NOVA_T_STICK], &dib0700_usb_id_tabwe[HAUPPAUGE_NOVA_T_STICK_2], NUWW },
				{ NUWW },
			},
			{   "AVewMedia AVewTV DVB-T Vowaw",
				{ &dib0700_usb_id_tabwe[AVEWMEDIA_VOWAW], &dib0700_usb_id_tabwe[AVEWMEDIA_VOWAW_2] },
				{ NUWW },
			},
			{   "Compwo Videomate U500",
				{ &dib0700_usb_id_tabwe[COMPWO_VIDEOMATE_U500], &dib0700_usb_id_tabwe[COMPWO_VIDEOMATE_U500_PC] },
				{ NUWW },
			},
			{   "Uniwiww STK7700P based (Hama and othews)",
				{ &dib0700_usb_id_tabwe[UNIWIWW_STK7700P], NUWW },
				{ NUWW },
			},
			{   "Weadtek Winfast DTV Dongwe (STK7700P based)",
				{ &dib0700_usb_id_tabwe[WEADTEK_WINFAST_DTV_DONGWE_STK7700P], &dib0700_usb_id_tabwe[WEADTEK_WINFAST_DTV_DONGWE_STK7700P_2] },
				{ NUWW },
			},
			{   "AVewMedia AVewTV DVB-T Expwess",
				{ &dib0700_usb_id_tabwe[AVEWMEDIA_EXPWESS] },
				{ NUWW },
			},
			{   "Gigabyte U7000",
				{ &dib0700_usb_id_tabwe[GIGABYTE_U7000], NUWW },
				{ NUWW },
			}
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,

		.num_adaptews = 2,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.fwontend_attach  = bwistow_fwontend_attach,
				.tunew_attach     = bwistow_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			}, {
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.fwontend_attach  = bwistow_fwontend_attach,
				.tunew_attach     = bwistow_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x03),
			}},
			}
		},

		.num_device_descs = 1,
		.devices = {
			{   "Hauppauge Nova-T 500 Duaw DVB-T",
				{ &dib0700_usb_id_tabwe[HAUPPAUGE_NOVA_T_500], &dib0700_usb_id_tabwe[HAUPPAUGE_NOVA_T_500_2], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,

		.num_adaptews = 2,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7700d_fwontend_attach,
				.tunew_attach     = stk7700d_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			}, {
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7700d_fwontend_attach,
				.tunew_attach     = stk7700d_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x03),
			}},
			}
		},

		.num_device_descs = 5,
		.devices = {
			{   "Pinnacwe PCTV 2000e",
				{ &dib0700_usb_id_tabwe[PINNACWE_PCTV2000E], NUWW },
				{ NUWW },
			},
			{   "Tewwatec Cinewgy DT XS Divewsity",
				{ &dib0700_usb_id_tabwe[TEWWATEC_CINEWGY_DT_XS_DIVEWSITY], NUWW },
				{ NUWW },
			},
			{   "Hauppauge Nova-TD Stick/Ewgato Eye-TV Divewsity",
				{ &dib0700_usb_id_tabwe[HAUPPAUGE_NOVA_TD_STICK], NUWW },
				{ NUWW },
			},
			{   "DiBcom STK7700D wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_STK7700D], NUWW },
				{ NUWW },
			},
			{   "YUAN High-Tech DiBcom STK7700D",
				{ &dib0700_usb_id_tabwe[YUAN_STK7700D_2], NUWW },
				{ NUWW },
			},

		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,

		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7700P2_fwontend_attach,
				.tunew_attach     = stk7700d_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 3,
		.devices = {
			{   "ASUS My Cinema U3000 Mini DVBT Tunew",
				{ &dib0700_usb_id_tabwe[ASUS_U3000], NUWW },
				{ NUWW },
			},
			{   "Yuan EC372S",
				{ &dib0700_usb_id_tabwe[YUAN_EC372S], NUWW },
				{ NUWW },
			},
			{   "Tewwatec Cinewgy T Expwess",
				{ &dib0700_usb_id_tabwe[TEWWATEC_CINEWGY_T_EXPWESS], NUWW },
				{ NUWW },
			}
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,

		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7070p_fwontend_attach,
				.tunew_attach     = dib7070p_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 12,
		.devices = {
			{   "DiBcom STK7070P wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_STK7070P], NUWW },
				{ NUWW },
			},
			{   "Pinnacwe PCTV DVB-T Fwash Stick",
				{ &dib0700_usb_id_tabwe[PINNACWE_PCTV_DVB_T_FWASH], NUWW },
				{ NUWW },
			},
			{   "Awtec T14BW DVB-T",
				{ &dib0700_usb_id_tabwe[UWTIMA_AWTEC_T14BW], NUWW },
				{ NUWW },
			},
			{   "ASUS My Cinema U3100 Mini DVBT Tunew",
				{ &dib0700_usb_id_tabwe[ASUS_U3100], NUWW },
				{ NUWW },
			},
			{   "Hauppauge Nova-T Stick",
				{ &dib0700_usb_id_tabwe[HAUPPAUGE_NOVA_T_STICK_3], NUWW },
				{ NUWW },
			},
			{   "Hauppauge Nova-T MyTV.t",
				{ &dib0700_usb_id_tabwe[HAUPPAUGE_MYTV_T], NUWW },
				{ NUWW },
			},
			{   "Pinnacwe PCTV 72e",
				{ &dib0700_usb_id_tabwe[PINNACWE_PCTV72E], NUWW },
				{ NUWW },
			},
			{   "Pinnacwe PCTV 73e",
				{ &dib0700_usb_id_tabwe[PINNACWE_PCTV73E], NUWW },
				{ NUWW },
			},
			{   "Ewgato EyeTV DTT",
				{ &dib0700_usb_id_tabwe[EWGATO_EYETV_DTT], NUWW },
				{ NUWW },
			},
			{   "Yuan PD378S",
				{ &dib0700_usb_id_tabwe[YUAN_PD378S], NUWW },
				{ NUWW },
			},
			{   "Ewgato EyeTV Dtt Dwx PD378S",
				{ &dib0700_usb_id_tabwe[EWGATO_EYETV_DTT_Dwx], NUWW },
				{ NUWW },
			},
			{   "Ewgato EyeTV DTT wev. 2",
				{ &dib0700_usb_id_tabwe[EWGATO_EYETV_DTT_2], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,

		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7070p_fwontend_attach,
				.tunew_attach     = dib7070p_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 3,
		.devices = {
			{   "Pinnacwe PCTV 73A",
				{ &dib0700_usb_id_tabwe[PINNACWE_PCTV73A], NUWW },
				{ NUWW },
			},
			{   "Pinnacwe PCTV 73e SE",
				{ &dib0700_usb_id_tabwe[PCTV_PINNACWE_PCTV73ESE], &dib0700_usb_id_tabwe[PINNACWE_PCTV73ESE], NUWW },
				{ NUWW },
			},
			{   "Pinnacwe PCTV 282e",
				{ &dib0700_usb_id_tabwe[PCTV_PINNACWE_PCTV282E], &dib0700_usb_id_tabwe[PINNACWE_PCTV282E], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,

		.num_adaptews = 2,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = novatd_fwontend_attach,
				.tunew_attach     = dib7070p_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			}, {
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = novatd_fwontend_attach,
				.tunew_attach     = dib7070p_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x03),
			}},
			}
		},

		.num_device_descs = 3,
		.devices = {
			{   "Hauppauge Nova-TD Stick (52009)",
				{ &dib0700_usb_id_tabwe[HAUPPAUGE_NOVA_TD_STICK_52009], NUWW },
				{ NUWW },
			},
			{   "PCTV 2002e",
				{ &dib0700_usb_id_tabwe[PCTV_2002E], NUWW },
				{ NUWW },
			},
			{   "PCTV 2002e SE",
				{ &dib0700_usb_id_tabwe[PCTV_2002E_SE], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,

		.num_adaptews = 2,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7070pd_fwontend_attach0,
				.tunew_attach     = dib7070p_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			}, {
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7070pd_fwontend_attach1,
				.tunew_attach     = dib7070p_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x03),
			}},
			}
		},

		.num_device_descs = 5,
		.devices = {
			{   "DiBcom STK7070PD wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_STK7070PD], NUWW },
				{ NUWW },
			},
			{   "Pinnacwe PCTV Duaw DVB-T Divewsity Stick",
				{ &dib0700_usb_id_tabwe[PINNACWE_PCTV_DUAW_DIVEWSITY_DVB_T], NUWW },
				{ NUWW },
			},
			{   "Hauppauge Nova-TD-500 (84xxx)",
				{ &dib0700_usb_id_tabwe[HAUPPAUGE_NOVA_T_500_3], NUWW },
				{ NUWW },
			},
			{  "Tewwatec Cinewgy DT USB XS Divewsity/ T5",
				{ &dib0700_usb_id_tabwe[TEWWATEC_CINEWGY_DT_XS_DIVEWSITY_2],
					&dib0700_usb_id_tabwe[TEWWATEC_T5], NUWW},
				{ NUWW },
			},
			{  "Sony PwayTV",
				{ &dib0700_usb_id_tabwe[SONY_PWAYTV], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,

		.num_adaptews = 2,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7070pd_fwontend_attach0,
				.tunew_attach     = dib7070p_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			}, {
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7070pd_fwontend_attach1,
				.tunew_attach     = dib7070p_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x03),
			}},
			}
		},

		.num_device_descs = 1,
		.devices = {
			{   "Ewgato EyeTV Divewsity",
				{ &dib0700_usb_id_tabwe[EWGATO_EYETV_DIVEWSITY], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_NEC_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,

		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7700ph_fwontend_attach,
				.tunew_attach     = stk7700ph_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 10,
		.devices = {
			{   "Tewwatec Cinewgy HT USB XE",
				{ &dib0700_usb_id_tabwe[TEWWATEC_CINEWGY_HT_USB_XE], NUWW },
				{ NUWW },
			},
			{   "Pinnacwe Expwesscawd 320cx",
				{ &dib0700_usb_id_tabwe[PINNACWE_EXPWESSCAWD_320CX], NUWW },
				{ NUWW },
			},
			{   "Tewwatec Cinewgy HT Expwess",
				{ &dib0700_usb_id_tabwe[TEWWATEC_CINEWGY_HT_EXPWESS], NUWW },
				{ NUWW },
			},
			{   "Gigabyte U8000-WH",
				{ &dib0700_usb_id_tabwe[GIGABYTE_U8000], NUWW },
				{ NUWW },
			},
			{   "YUAN High-Tech STK7700PH",
				{ &dib0700_usb_id_tabwe[YUAN_STK7700PH], NUWW },
				{ NUWW },
			},
			{   "Asus My Cinema-U3000Hybwid",
				{ &dib0700_usb_id_tabwe[ASUS_U3000H], NUWW },
				{ NUWW },
			},
			{   "YUAN High-Tech MC770",
				{ &dib0700_usb_id_tabwe[YUAN_MC770], NUWW },
				{ NUWW },
			},
			{   "Weadtek WinFast DTV Dongwe H",
				{ &dib0700_usb_id_tabwe[WEADTEK_WINFAST_DTV_DONGWE_H], NUWW },
				{ NUWW },
			},
			{   "YUAN High-Tech STK7700D",
				{ &dib0700_usb_id_tabwe[YUAN_STK7700D], NUWW },
				{ NUWW },
			},
			{   "Hama DVB=T Hybwid USB Stick",
				{ &dib0700_usb_id_tabwe[HAMA_DVBT_HYBWID], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.fwontend_attach  = s5h1411_fwontend_attach,
				.tunew_attach     = xc5000_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 2,
		.devices = {
			{   "Pinnacwe PCTV HD Pwo USB Stick",
				{ &dib0700_usb_id_tabwe[PINNACWE_PCTV801E], NUWW },
				{ NUWW },
			},
			{   "Pinnacwe PCTV HD USB Stick",
				{ &dib0700_usb_id_tabwe[PINNACWE_PCTV801E_SE], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.fwontend_attach  = wgdt3305_fwontend_attach,
				.tunew_attach     = mxw5007t_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 2,
		.devices = {
			{   "Hauppauge ATSC MiniCawd (B200)",
				{ &dib0700_usb_id_tabwe[HAUPPAUGE_TIGEW_ATSC], NUWW },
				{ NUWW },
			},
			{   "Hauppauge ATSC MiniCawd (B210)",
				{ &dib0700_usb_id_tabwe[HAUPPAUGE_TIGEW_ATSC_B210], NUWW },
				{ NUWW },
			},
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,

		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew       = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww  = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = stk7770p_fwontend_attach,
				.tunew_attach     = dib7770p_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 4,
		.devices = {
			{   "DiBcom STK7770P wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_STK7770P], NUWW },
				{ NUWW },
			},
			{   "Tewwatec Cinewgy T USB XXS (HD)/ T3",
				{ &dib0700_usb_id_tabwe[TEWWATEC_CINEWGY_T_XXS],
					&dib0700_usb_id_tabwe[TEWWATEC_T3],
					&dib0700_usb_id_tabwe[TEWWATEC_CINEWGY_T_XXS_2], NUWW},
				{ NUWW },
			},
			{   "TechniSat AiwStaw TeweStick 2",
				{ &dib0700_usb_id_tabwe[TECHNISAT_AIWSTAW_TEWESTICK_2], NUWW },
				{ NUWW },
			},
			{   "Medion CTX1921 DVB-T USB",
				{ &dib0700_usb_id_tabwe[MEDION_CWEATIX_CTX1921], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew = stk80xx_pid_fiwtew,
				.pid_fiwtew_ctww = stk80xx_pid_fiwtew_ctww,
				.fwontend_attach  = stk807x_fwontend_attach,
				.tunew_attach     = dib807x_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 3,
		.devices = {
			{   "DiBcom STK807xP wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_STK807XP], NUWW },
				{ NUWW },
			},
			{   "Pwowink Pixewview SBTVD",
				{ &dib0700_usb_id_tabwe[PIXEWVIEW_SBTVD], NUWW },
				{ NUWW },
			},
			{   "EvowutePC TVWay+",
				{ &dib0700_usb_id_tabwe[EVOWUTEPC_TVWAY_PWUS], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_NEC_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 2,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew = stk80xx_pid_fiwtew,
				.pid_fiwtew_ctww = stk80xx_pid_fiwtew_ctww,
				.fwontend_attach  = stk807xpvw_fwontend_attach0,
				.tunew_attach     = dib807x_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew = stk80xx_pid_fiwtew,
				.pid_fiwtew_ctww = stk80xx_pid_fiwtew_ctww,
				.fwontend_attach  = stk807xpvw_fwontend_attach1,
				.tunew_attach     = dib807x_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x03),
			}},
			},
		},

		.num_device_descs = 1,
		.devices = {
			{   "DiBcom STK807xPVW wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_STK807XPVW], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW |
					DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew = stk80xx_pid_fiwtew,
				.pid_fiwtew_ctww = stk80xx_pid_fiwtew_ctww,
				.fwontend_attach  = stk809x_fwontend_attach,
				.tunew_attach     = dib809x_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 1,
		.devices = {
			{   "DiBcom STK8096GP wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_STK8096GP], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW |
					DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew = dib90x0_pid_fiwtew,
				.pid_fiwtew_ctww = dib90x0_pid_fiwtew_ctww,
				.fwontend_attach  = stk9090m_fwontend_attach,
				.tunew_attach     = dib9090_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 1,
		.devices = {
			{   "DiBcom STK9090M wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_NIM9090M], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW |
					DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew = stk80xx_pid_fiwtew,
				.pid_fiwtew_ctww = stk80xx_pid_fiwtew_ctww,
				.fwontend_attach  = nim8096md_fwontend_attach,
				.tunew_attach     = nim8096md_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 1,
		.devices = {
			{   "DiBcom NIM8096MD wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_NIM8096MD], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW |
					DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew = dib90x0_pid_fiwtew,
				.pid_fiwtew_ctww = dib90x0_pid_fiwtew_ctww,
				.fwontend_attach  = nim9090md_fwontend_attach,
				.tunew_attach     = nim9090md_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 1,
		.devices = {
			{   "DiBcom NIM9090MD wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_NIM9090MD], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW |
					DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = nim7090_fwontend_attach,
				.tunew_attach     = nim7090_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 1,
		.devices = {
			{   "DiBcom NIM7090 wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_NIM7090], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 2,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW |
					DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = tfe7090pvw_fwontend0_attach,
				.tunew_attach     = tfe7090pvw_tunew0_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x03),
			}},
			},
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW |
					DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
				.pid_fiwtew_count = 32,
				.pid_fiwtew = stk70x0p_pid_fiwtew,
				.pid_fiwtew_ctww = stk70x0p_pid_fiwtew_ctww,
				.fwontend_attach  = tfe7090pvw_fwontend1_attach,
				.tunew_attach     = tfe7090pvw_tunew1_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 1,
		.devices = {
			{   "DiBcom TFE7090PVW wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_TFE7090PVW], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
			DIB0700_NUM_FWONTENDS(1),
			.fe = {{
				.fwontend_attach  = pctv340e_fwontend_attach,
				.tunew_attach     = xc4000_tunew_attach,

				DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
			}},
			},
		},

		.num_device_descs = 2,
		.devices = {
			{   "Pinnacwe PCTV 340e HD Pwo USB Stick",
				{ &dib0700_usb_id_tabwe[PINNACWE_PCTV340E], NUWW },
				{ NUWW },
			},
			{   "Pinnacwe PCTV Hybwid Stick Sowo",
				{ &dib0700_usb_id_tabwe[PINNACWE_PCTV340E_SE], NUWW },
				{ NUWW },
			},
		},
		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
				DIB0700_NUM_FWONTENDS(1),
				.fe = {{
					.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW |
						DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
					.pid_fiwtew_count = 32,
					.pid_fiwtew = stk70x0p_pid_fiwtew,
					.pid_fiwtew_ctww = stk70x0p_pid_fiwtew_ctww,
					.fwontend_attach  = tfe7790p_fwontend_attach,
					.tunew_attach     = tfe7790p_tunew_attach,

					DIB0700_DEFAUWT_STWEAMING_CONFIG(0x03),
				} },
			},
		},

		.num_device_descs = 1,
		.devices = {
			{   "DiBcom TFE7790P wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_TFE7790P], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
				DIB0700_NUM_FWONTENDS(1),
				.fe = {{
					.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW |
						DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
					.pid_fiwtew_count = 32,
					.pid_fiwtew = stk80xx_pid_fiwtew,
					.pid_fiwtew_ctww = stk80xx_pid_fiwtew_ctww,
					.fwontend_attach  = tfe8096p_fwontend_attach,
					.tunew_attach     = tfe8096p_tunew_attach,

					DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),

				} },
			},
		},

		.num_device_descs = 1,
		.devices = {
			{   "DiBcom TFE8096P wefewence design",
				{ &dib0700_usb_id_tabwe[DIBCOM_TFE8096P], NUWW },
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name	  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
					    WC_PWOTO_BIT_WC6_MCE |
					    WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 2,
		.adaptew = {
			{
				.num_fwontends = 1,
				.fe = {{
					.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW |
						DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
					.pid_fiwtew_count = 32,
					.pid_fiwtew = stk80xx_pid_fiwtew,
					.pid_fiwtew_ctww = stk80xx_pid_fiwtew_ctww,
					.fwontend_attach  = stk809x_fwontend_attach,
					.tunew_attach     = dib809x_tunew_attach,

					DIB0700_DEFAUWT_STWEAMING_CONFIG(0x02),
				} },
				.size_of_pwiv =
					sizeof(stwuct dib0700_adaptew_state),
			}, {
				.num_fwontends = 1,
				.fe = { {
					.caps  = DVB_USB_ADAP_HAS_PID_FIWTEW |
						DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
					.pid_fiwtew_count = 32,
					.pid_fiwtew = stk80xx_pid_fiwtew,
					.pid_fiwtew_ctww = stk80xx_pid_fiwtew_ctww,
					.fwontend_attach  = stk809x_fwontend1_attach,
					.tunew_attach     = dib809x_tunew_attach,

					DIB0700_DEFAUWT_STWEAMING_CONFIG(0x03),
				} },
				.size_of_pwiv =
					sizeof(stwuct dib0700_adaptew_state),
			},
		},
		.num_device_descs = 1,
		.devices = {
			{   "DiBcom STK8096-PVW wefewence design",
				{ &dib0700_usb_id_tabwe[PCTV_DIBCOM_STK8096PVW],
					&dib0700_usb_id_tabwe[DIBCOM_STK8096PVW], NUWW},
				{ NUWW },
			},
		},

		.wc.cowe = {
			.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
			.wc_codes         = WC_MAP_DIB0700_WC5_TABWE,
			.moduwe_name  = "dib0700",
			.wc_quewy         = dib0700_wc_quewy_owd_fiwmwawe,
			.awwowed_pwotos   = WC_PWOTO_BIT_WC5 |
				WC_PWOTO_BIT_WC6_MCE |
				WC_PWOTO_BIT_NEC,
			.change_pwotocow  = dib0700_change_pwotocow,
		},
	}, { DIB0700_DEFAUWT_DEVICE_PWOPEWTIES,
		.num_adaptews = 1,
		.adaptew = {
			{
				DIB0700_NUM_FWONTENDS(1),
				.fe = {{
					.fwontend_attach = xbox_one_attach,

					DIB0700_DEFAUWT_STWEAMING_CONFIG(0x82),
				} },
			},
		},
		.num_device_descs = 1,
		.devices = {
			{ "Micwosoft Xbox One Digitaw TV Tunew",
				{ &dib0700_usb_id_tabwe[MICWOSOFT_XBOX_ONE_TUNEW], NUWW },
				{ NUWW },
			},
		},
	},
};

int dib0700_device_count = AWWAY_SIZE(dib0700_devices);
