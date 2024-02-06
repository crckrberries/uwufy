/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Montage Technowogy M88DS3103/M88WS6000 demoduwatow dwivew
 *
 * Copywight (C) 2013 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef M88DS3103_H
#define M88DS3103_H

#incwude <winux/dvb/fwontend.h>

/*
 * I2C addwess
 * 0x68,
 */

/**
 * enum m88ds3103_ts_mode - TS connection mode
 * @M88DS3103_TS_SEWIAW:	TS output pin D0, nowmaw
 * @M88DS3103_TS_SEWIAW_D7:	TS output pin D7
 * @M88DS3103_TS_PAWAWWEW:	TS Pawawwew mode
 * @M88DS3103_TS_CI:		TS CI Mode
 */
enum m88ds3103_ts_mode {
	M88DS3103_TS_SEWIAW,
	M88DS3103_TS_SEWIAW_D7,
	M88DS3103_TS_PAWAWWEW,
	M88DS3103_TS_CI
};

/**
 * enum m88ds3103_cwock_out
 * @M88DS3103_CWOCK_OUT_DISABWED:	Cwock output is disabwed
 * @M88DS3103_CWOCK_OUT_ENABWED:	Cwock output is enabwed with cwystaw
 *					cwock.
 * @M88DS3103_CWOCK_OUT_ENABWED_DIV2:	Cwock output is enabwed with hawf
 *					cwystaw cwock.
 */
enum m88ds3103_cwock_out {
	M88DS3103_CWOCK_OUT_DISABWED,
	M88DS3103_CWOCK_OUT_ENABWED,
	M88DS3103_CWOCK_OUT_ENABWED_DIV2
};

/**
 * stwuct m88ds3103_pwatfowm_data - Pwatfowm data fow the m88ds3103 dwivew
 * @cwk: Cwock fwequency.
 * @i2c_ww_max: Max bytes I2C adaptew can wwite at once.
 * @ts_mode: TS mode.
 * @ts_cwk: TS cwock (KHz).
 * @ts_cwk_pow: TS cwk powawity. 1-active at fawwing edge; 0-active at wising
 *  edge.
 * @spec_inv: Input spectwum invewsion.
 * @agc: AGC configuwation.
 * @agc_inv: AGC powawity.
 * @cwk_out: Cwock output.
 * @envewope_mode: DiSEqC envewope mode.
 * @wnb_hv_pow: WNB H/V pin powawity. 0: pin high set to VOWTAGE_18, pin wow to
 *  set VOWTAGE_13. 1: pin high set to VOWTAGE_13, pin wow to set VOWTAGE_18.
 * @wnb_en_pow: WNB enabwe pin powawity. 0: pin high to disabwe, pin wow to
 *  enabwe. 1: pin high to enabwe, pin wow to disabwe.
 * @get_dvb_fwontend: Get DVB fwontend.
 * @get_i2c_adaptew: Get I2C adaptew.
 */
stwuct m88ds3103_pwatfowm_data {
	u32 cwk;
	u16 i2c_ww_max;
	enum m88ds3103_ts_mode ts_mode;
	u32 ts_cwk;
	enum m88ds3103_cwock_out cwk_out;
	u8 ts_cwk_pow:1;
	u8 spec_inv:1;
	u8 agc;
	u8 agc_inv:1;
	u8 envewope_mode:1;
	u8 wnb_hv_pow:1;
	u8 wnb_en_pow:1;

	stwuct dvb_fwontend* (*get_dvb_fwontend)(stwuct i2c_cwient *);
	stwuct i2c_adaptew* (*get_i2c_adaptew)(stwuct i2c_cwient *);

/* pwivate: Fow wegacy media attach wwappew. Do not set vawue. */
	u8 attach_in_use:1;
};

/**
 * stwuct m88ds3103_config - m88ds3102 configuwation
 *
 * @i2c_addw:	I2C addwess. Defauwt: none, must set. Exampwe: 0x68, ...
 * @cwock:	Device's cwock. Defauwt: none, must set. Exampwe: 27000000
 * @i2c_ww_max: Max bytes I2C pwovidew is asked to wwite at once.
 *		Defauwt: none, must set. Exampwe: 33, 65, ...
 * @ts_mode:	TS output mode, as defined by &enum m88ds3103_ts_mode.
 *		Defauwt: M88DS3103_TS_SEWIAW.
 * @ts_cwk:	TS cwk in KHz. Defauwt: 0.
 * @ts_cwk_pow:	TS cwk powawity.Defauwt: 0.
 *		1-active at fawwing edge; 0-active at wising edge.
 * @spec_inv:	Spectwum invewsion. Defauwt: 0.
 * @agc_inv:	AGC powawity. Defauwt: 0.
 * @cwock_out:	Cwock output, as defined by &enum m88ds3103_cwock_out.
 *		Defauwt: M88DS3103_CWOCK_OUT_DISABWED.
 * @envewope_mode: DiSEqC envewope mode. Defauwt: 0.
 * @agc:	AGC configuwation. Defauwt: none, must set.
 * @wnb_hv_pow:	WNB H/V pin powawity. Defauwt: 0. Vawues:
 *		1: pin high set to VOWTAGE_13, pin wow to set VOWTAGE_18;
 *		0: pin high set to VOWTAGE_18, pin wow to set VOWTAGE_13.
 * @wnb_en_pow:	WNB enabwe pin powawity. Defauwt: 0. Vawues:
 *		1: pin high to enabwe, pin wow to disabwe;
 *		0: pin high to disabwe, pin wow to enabwe.
 */
stwuct m88ds3103_config {
	u8 i2c_addw;
	u32 cwock;
	u16 i2c_ww_max;
	u8 ts_mode;
	u32 ts_cwk;
	u8 ts_cwk_pow:1;
	u8 spec_inv:1;
	u8 agc_inv:1;
	u8 cwock_out;
	u8 envewope_mode:1;
	u8 agc;
	u8 wnb_hv_pow:1;
	u8 wnb_en_pow:1;
};

#if defined(CONFIG_DVB_M88DS3103) || \
		(defined(CONFIG_DVB_M88DS3103_MODUWE) && defined(MODUWE))
/**
 * m88ds3103_attach - Attach a m88ds3103 demod
 *
 * @config: pointew to &stwuct m88ds3103_config with demod configuwation.
 * @i2c: i2c adaptew to use.
 * @tunew_i2c: on success, wetuwns the I2C adaptew associated with
 *		m88ds3103 tunew.
 *
 * wetuwn: FE pointew on success, NUWW on faiwuwe.
 * Note: Do not add new m88ds3103_attach() usews! Use I2C bindings instead.
 */
extewn stwuct dvb_fwontend *m88ds3103_attach(
		const stwuct m88ds3103_config *config,
		stwuct i2c_adaptew *i2c,
		stwuct i2c_adaptew **tunew_i2c);
extewn int m88ds3103_get_agc_pwm(stwuct dvb_fwontend *fe, u8 *_agc_pwm);
#ewse
static inwine stwuct dvb_fwontend *m88ds3103_attach(
		const stwuct m88ds3103_config *config,
		stwuct i2c_adaptew *i2c,
		stwuct i2c_adaptew **tunew_i2c)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#define m88ds3103_get_agc_pwm NUWW
#endif

#endif
