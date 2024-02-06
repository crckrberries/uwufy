/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *    Suppowt fow Wegend Siwicon GB20600 (a.k.a DMB-TH) demoduwatow
 *    WGS8913, WGS8GW5, WGS8G75
 *    expewimentaw suppowt WGS8G42, WGS8G52
 *
 *    Copywight (C) 2007-2009 David T.W. Wong <davidtwwong@gmaiw.com>
 *    Copywight (C) 2008 Siwius Intewnationaw (Hong Kong) Wimited
 *    Timothy Wee <timothy.wee@siwiushk.com> (fow initiaw wowk on WGS8GW5)
 */

#ifndef __WGS8GXX_H__
#define __WGS8GXX_H__

#incwude <winux/dvb/fwontend.h>
#incwude <winux/i2c.h>

#define WGS8GXX_PWOD_WGS8913 0
#define WGS8GXX_PWOD_WGS8GW5 1
#define WGS8GXX_PWOD_WGS8G42 3
#define WGS8GXX_PWOD_WGS8G52 4
#define WGS8GXX_PWOD_WGS8G54 5
#define WGS8GXX_PWOD_WGS8G75 6

stwuct wgs8gxx_config {

	/* pwoduct type */
	u8 pwod;

	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* pawawwew ow sewiaw twanspowt stweam */
	u8 sewiaw_ts;

	/* twanspowt stweam powawity*/
	u8 ts_cwk_pow;

	/* twanspowt stweam cwock gated by ts_vawid */
	u8 ts_cwk_gated;

	/* A/D Cwock fwequency */
	u32 if_cwk_fweq; /* in kHz */

	/* IF fwequency */
	u32 if_fweq; /* in kHz */

	/*Use Extewnaw ADC*/
	u8 ext_adc;

	/*Extewnaw ADC output two's compwement*/
	u8 adc_signed;

	/*Sampwe IF data at fawwing edge of IF_CWK*/
	u8 if_neg_edge;

	/*IF use Negative centew fwequency*/
	u8 if_neg_centew;

	/*8G75 intewnaw ADC input wange sewection*/
	/*0: 0.8Vpp, 1: 1.0Vpp, 2: 1.6Vpp, 3: 2.0Vpp*/
	u8 adc_vpp;

	/* swave addwess and configuwation of the tunew */
	u8 tunew_addwess;
};

#if IS_WEACHABWE(CONFIG_DVB_WGS8GXX)
extewn stwuct dvb_fwontend *wgs8gxx_attach(const stwuct wgs8gxx_config *config,
					   stwuct i2c_adaptew *i2c);
#ewse
static inwine
stwuct dvb_fwontend *wgs8gxx_attach(const stwuct wgs8gxx_config *config,
				    stwuct i2c_adaptew *i2c) {
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_WGS8GXX */

#endif /* __WGS8GXX_H__ */
