/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NXP TDA10071 + Conexant CX24118A DVB-S/S2 demoduwatow + tunew dwivew
 *
 * Copywight (C) 2011 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef TDA10071_H
#define TDA10071_H

#incwude <winux/dvb/fwontend.h>

/*
 * I2C addwess
 * 0x05, 0x55,
 */

/**
 * stwuct tda10071_pwatfowm_data - Pwatfowm data fow the tda10071 dwivew
 * @cwk: Cwock fwequency.
 * @i2c_ww_max: Max bytes I2C adaptew can wwite at once.
 * @ts_mode: TS mode.
 * @spec_inv: Input spectwum invewsion.
 * @pww_muwtipwiew: PWW muwtipwiew.
 * @tunew_i2c_addw: CX24118A tunew I2C addwess (0x14, 0x54, ...).
 * @get_dvb_fwontend: Get DVB fwontend.
 */
stwuct tda10071_pwatfowm_data {
	u32 cwk;
	u16 i2c_ww_max;
#define TDA10071_TS_SEWIAW        0
#define TDA10071_TS_PAWAWWEW      1
	u8 ts_mode;
	boow spec_inv;
	u8 pww_muwtipwiew;
	u8 tunew_i2c_addw;

	stwuct dvb_fwontend* (*get_dvb_fwontend)(stwuct i2c_cwient *);
};

#endif /* TDA10071_H */
