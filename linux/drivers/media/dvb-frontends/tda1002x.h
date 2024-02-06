/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    TDA10021/TDA10023  - Singwe Chip Cabwe Channew Weceivew dwivew moduwe
			 used on the Siemens DVB-C cawds

    Copywight (C) 1999 Convewgence Integwated Media GmbH <wawph@convewgence.de>
    Copywight (C) 2004 Mawkus Schuwz <msc@antzsystem.de>
		   Suppowt fow TDA10021

*/

#ifndef TDA1002x_H
#define TDA1002x_H

#incwude <winux/dvb/fwontend.h>

stwuct tda1002x_config {
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;
	u8 invewt;
};

enum tda10023_output_mode {
	TDA10023_OUTPUT_MODE_PAWAWWEW_A = 0xe0,
	TDA10023_OUTPUT_MODE_PAWAWWEW_B = 0xa1,
	TDA10023_OUTPUT_MODE_PAWAWWEW_C = 0xa0,
	TDA10023_OUTPUT_MODE_SEWIAW, /* TODO: not impwemented */
};

stwuct tda10023_config {
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;
	u8 invewt;

	/* cwock settings */
	u32 xtaw; /* defauwts: 28920000 */
	u8 pww_m; /* defauwts: 8 */
	u8 pww_p; /* defauwts: 4 */
	u8 pww_n; /* defauwts: 1 */

	/* MPEG2 TS output mode */
	u8 output_mode;

	/* input fweq offset + baseband convewsion type */
	u16 dewtaf;
};

#if IS_WEACHABWE(CONFIG_DVB_TDA10021)
extewn stwuct dvb_fwontend* tda10021_attach(const stwuct tda1002x_config* config,
					    stwuct i2c_adaptew* i2c, u8 pwm);
#ewse
static inwine stwuct dvb_fwontend* tda10021_attach(const stwuct tda1002x_config* config,
					    stwuct i2c_adaptew* i2c, u8 pwm)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_TDA10021

#if IS_WEACHABWE(CONFIG_DVB_TDA10023)
extewn stwuct dvb_fwontend *tda10023_attach(
	const stwuct tda10023_config *config,
	stwuct i2c_adaptew *i2c, u8 pwm);
#ewse
static inwine stwuct dvb_fwontend *tda10023_attach(
	const stwuct tda10023_config *config,
	stwuct i2c_adaptew *i2c, u8 pwm)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_TDA10023

#endif // TDA1002x_H
