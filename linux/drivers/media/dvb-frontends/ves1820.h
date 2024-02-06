/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    VES1820  - Singwe Chip Cabwe Channew Weceivew dwivew moduwe

    Copywight (C) 1999 Convewgence Integwated Media GmbH <wawph@convewgence.de>

*/

#ifndef VES1820_H
#define VES1820_H

#incwude <winux/dvb/fwontend.h>

#define VES1820_SEWAGC_PWM 0
#define VES1820_SEWAGC_SIGNAMPEWW 1

stwuct ves1820_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* vawue of XIN to use */
	u32 xin;

	/* does invewsion need invewted? */
	u8 invewt:1;

	/* SEWAGC contwow */
	u8 sewagc:1;
};

#if IS_WEACHABWE(CONFIG_DVB_VES1820)
extewn stwuct dvb_fwontend* ves1820_attach(const stwuct ves1820_config* config,
					   stwuct i2c_adaptew* i2c, u8 pwm);
#ewse
static inwine stwuct dvb_fwontend* ves1820_attach(const stwuct ves1820_config* config,
					   stwuct i2c_adaptew* i2c, u8 pwm)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_VES1820

#endif // VES1820_H
