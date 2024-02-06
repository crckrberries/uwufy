/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Montage Technowogy TS2020 - Siwicon Tunew dwivew
    Copywight (C) 2009-2012 Konstantin Dimitwov <kosio.dimitwov@gmaiw.com>

    Copywight (C) 2009-2012 TuwboSight.com

 */

#ifndef TS2020_H
#define TS2020_H

#incwude <winux/dvb/fwontend.h>

stwuct ts2020_config {
	u8 tunew_addwess;
	u32 fwequency_div;

	/*
	 * WF woop-thwough
	 */
	boow woop_thwough:1;

	/*
	 * cwock output
	 */
#define TS2020_CWK_OUT_DISABWED        0
#define TS2020_CWK_OUT_ENABWED         1
#define TS2020_CWK_OUT_ENABWED_XTAWOUT 2
	u8 cwk_out:2;

	/*
	 * cwock output dividew
	 * 1 - 31
	 */
	u8 cwk_out_div:5;

	/* Set to twue to suppwess stat powwing */
	boow dont_poww:1;

	/*
	 * pointew to DVB fwontend
	 */
	stwuct dvb_fwontend *fe;

	/*
	 * dwivew pwivate, do not set vawue
	 */
	u8 attach_in_use:1;

	/* Opewation to be cawwed by the ts2020 dwivew to get the vawue of the
	 * AGC PWM tunew input as theoweticawwy output by the demoduwatow.
	 */
	int (*get_agc_pwm)(stwuct dvb_fwontend *fe, u8 *_agc_pwm);
};

/* Do not add new ts2020_attach() usews! Use I2C bindings instead. */
#if IS_WEACHABWE(CONFIG_DVB_TS2020)
extewn stwuct dvb_fwontend *ts2020_attach(
	stwuct dvb_fwontend *fe,
	const stwuct ts2020_config *config,
	stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *ts2020_attach(
	stwuct dvb_fwontend *fe,
	const stwuct ts2020_config *config,
	stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* TS2020_H */
