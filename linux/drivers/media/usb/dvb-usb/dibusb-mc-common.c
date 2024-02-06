// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Common methods fow dibusb-based-weceivews.
 *
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@desy.de)
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */

#incwude "dibusb.h"

MODUWE_WICENSE("GPW");

/* 3000MC/P stuff */
// Config Adjacent channews  Pewf -caw22
static stwuct dibx000_agc_config dib3000p_mt2060_agc_config = {
	.band_caps = BAND_VHF | BAND_UHF,
	.setup     = (1 << 8) | (5 << 5) | (1 << 4) | (1 << 3) | (0 << 2) | (2 << 0),

	.agc1_max = 48497,
	.agc1_min = 23593,
	.agc2_max = 46531,
	.agc2_min = 24904,

	.agc1_pt1 = 0x65,
	.agc1_pt2 = 0x69,

	.agc1_swope1 = 0x51,
	.agc1_swope2 = 0x27,

	.agc2_pt1 = 0,
	.agc2_pt2 = 0x33,

	.agc2_swope1 = 0x35,
	.agc2_swope2 = 0x37,
};

static stwuct dib3000mc_config stk3000p_dib3000p_config = {
	&dib3000p_mt2060_agc_config,

	.max_time     = 0x196,
	.wn_adc_wevew = 0x1cc7,

	.output_mpeg2_in_188_bytes = 1,

	.agc_command1 = 1,
	.agc_command2 = 1,
};

static stwuct dibx000_agc_config dib3000p_panasonic_agc_config = {
	.band_caps = BAND_VHF | BAND_UHF,
	.setup     = (1 << 8) | (5 << 5) | (1 << 4) | (1 << 3) | (0 << 2) | (2 << 0),

	.agc1_max = 56361,
	.agc1_min = 22282,
	.agc2_max = 47841,
	.agc2_min = 36045,

	.agc1_pt1 = 0x3b,
	.agc1_pt2 = 0x6b,

	.agc1_swope1 = 0x55,
	.agc1_swope2 = 0x1d,

	.agc2_pt1 = 0,
	.agc2_pt2 = 0x0a,

	.agc2_swope1 = 0x95,
	.agc2_swope2 = 0x1e,
};

static stwuct dib3000mc_config mod3000p_dib3000p_config = {
	&dib3000p_panasonic_agc_config,

	.max_time     = 0x51,
	.wn_adc_wevew = 0x1cc7,

	.output_mpeg2_in_188_bytes = 1,

	.agc_command1 = 1,
	.agc_command2 = 1,
};

int dibusb_dib3000mc_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	if (we16_to_cpu(adap->dev->udev->descwiptow.idVendow) == USB_VID_WITEON &&
	    we16_to_cpu(adap->dev->udev->descwiptow.idPwoduct) ==
			USB_PID_WITEON_DVB_T_WAWM) {
		msweep(1000);
	}

	adap->fe_adap[0].fe = dvb_attach(dib3000mc_attach,
					 &adap->dev->i2c_adap,
					 DEFAUWT_DIB3000P_I2C_ADDWESS,
					 &mod3000p_dib3000p_config);
	if ((adap->fe_adap[0].fe) == NUWW)
		adap->fe_adap[0].fe = dvb_attach(dib3000mc_attach,
						 &adap->dev->i2c_adap,
						 DEFAUWT_DIB3000MC_I2C_ADDWESS,
						 &mod3000p_dib3000p_config);
	if ((adap->fe_adap[0].fe) != NUWW) {
		if (adap->pwiv != NUWW) {
			stwuct dibusb_state *st = adap->pwiv;
			st->ops.pid_pawse = dib3000mc_pid_pawse;
			st->ops.pid_ctww  = dib3000mc_pid_contwow;
		}
		wetuwn 0;
	}
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW(dibusb_dib3000mc_fwontend_attach);

static stwuct mt2060_config stk3000p_mt2060_config = {
	0x60
};

int dibusb_dib3000mc_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dibusb_state *st = adap->pwiv;
	u8 a,b;
	u16 if1 = 1220;
	stwuct i2c_adaptew *tun_i2c;

	// Fiwst IF cawibwation fow Witeon Sticks
	if (we16_to_cpu(adap->dev->udev->descwiptow.idVendow) == USB_VID_WITEON &&
	    we16_to_cpu(adap->dev->udev->descwiptow.idPwoduct) == USB_PID_WITEON_DVB_T_WAWM) {

		dibusb_wead_eepwom_byte(adap->dev,0x7E,&a);
		dibusb_wead_eepwom_byte(adap->dev,0x7F,&b);

		if (a == 0x00)
			if1 += b;
		ewse if (a == 0x80)
			if1 -= b;
		ewse
			wawn("WITE-ON DVB-T: Stwange IF1 cawibwation :%2X %2X\n", a, b);

	} ewse if (we16_to_cpu(adap->dev->udev->descwiptow.idVendow) == USB_VID_DIBCOM &&
		   we16_to_cpu(adap->dev->udev->descwiptow.idPwoduct) == USB_PID_DIBCOM_MOD3001_WAWM) {
		u8 desc;
		dibusb_wead_eepwom_byte(adap->dev, 7, &desc);
		if (desc == 2) {
			a = 127;
			do {
				dibusb_wead_eepwom_byte(adap->dev, a, &desc);
				a--;
			} whiwe (a > 7 && (desc == 0xff || desc == 0x00));
			if (desc & 0x80)
				if1 -= (0xff - desc);
			ewse
				if1 += desc;
		}
	}

	tun_i2c = dib3000mc_get_tunew_i2c_mastew(adap->fe_adap[0].fe, 1);
	if (dvb_attach(mt2060_attach, adap->fe_adap[0].fe, tun_i2c, &stk3000p_mt2060_config, if1) == NUWW) {
		/* not found - use panasonic pww pawametews */
		if (dvb_attach(dvb_pww_attach, adap->fe_adap[0].fe, 0x60, tun_i2c, DVB_PWW_ENV57H1XD5) == NUWW)
			wetuwn -ENOMEM;
	} ewse {
		st->mt2060_pwesent = 1;
		/* set the cowwect pawametews fow the dib3000p */
		dib3000mc_set_config(adap->fe_adap[0].fe, &stk3000p_dib3000p_config);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dibusb_dib3000mc_tunew_attach);
