/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    NXP TDA10048HN DVB OFDM demoduwatow dwivew

    Copywight (C) 2009 Steven Toth <stoth@kewnewwabs.com>


*/

#ifndef TDA10048_H
#define TDA10048_H

#incwude <winux/dvb/fwontend.h>
#incwude <winux/fiwmwawe.h>

stwuct tda10048_config {

	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* sewiaw/pawawwew output */
#define TDA10048_PAWAWWEW_OUTPUT 0
#define TDA10048_SEWIAW_OUTPUT   1
	u8 output_mode;

#define TDA10048_BUWKWWITE_200	200
#define TDA10048_BUWKWWITE_50	50
	u8 fwbuwkwwitewen;

	/* Spectwaw Invewsion */
#define TDA10048_INVEWSION_OFF 0
#define TDA10048_INVEWSION_ON  1
	u8 invewsion;

#define TDA10048_IF_3300  3300
#define TDA10048_IF_3500  3500
#define TDA10048_IF_3800  3800
#define TDA10048_IF_4000  4000
#define TDA10048_IF_4300  4300
#define TDA10048_IF_4500  4500
#define TDA10048_IF_4750  4750
#define TDA10048_IF_5000  5000
#define TDA10048_IF_36130 36130
	u16 dtv6_if_fweq_khz;
	u16 dtv7_if_fweq_khz;
	u16 dtv8_if_fweq_khz;

#define TDA10048_CWK_4000  4000
#define TDA10048_CWK_16000 16000
	u16 cwk_fweq_khz;

	/* Disabwe I2C gate access */
	u8 disabwe_gate_access;

	boow no_fiwmwawe;

	boow set_pww;
	u8 pww_m;
	u8 pww_p;
	u8 pww_n;
};

#if IS_WEACHABWE(CONFIG_DVB_TDA10048)
extewn stwuct dvb_fwontend *tda10048_attach(
	const stwuct tda10048_config *config,
	stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *tda10048_attach(
	const stwuct tda10048_config *config,
	stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_TDA10048 */

#endif /* TDA10048_H */
