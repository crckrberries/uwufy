/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *    Suppowt fow AwtoBeam GB20600 (a.k.a DMB-TH) demoduwatow
 *    ATBM8830, ATBM8831
 *
 *    Copywight (C) 2009 David T.W. Wong <davidtwwong@gmaiw.com>
 */

#ifndef __ATBM8830_H__
#define __ATBM8830_H__

#incwude <winux/dvb/fwontend.h>
#incwude <winux/i2c.h>

#define ATBM8830_PWOD_8830 0
#define ATBM8830_PWOD_8831 1

stwuct atbm8830_config {

	/* pwoduct type */
	u8 pwod;

	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* pawawwew ow sewiaw twanspowt stweam */
	u8 sewiaw_ts;

	/* twanspowt stweam cwock output onwy when weceiving vawid stweam */
	u8 ts_cwk_gated;

	/* Decodew sampwe TS data at wising edge of cwock */
	u8 ts_sampwing_edge;

	/* Osciwwatow cwock fwequency */
	u32 osc_cwk_fweq; /* in kHz */

	/* IF fwequency */
	u32 if_fweq; /* in kHz */

	/* Swap I/Q fow zewo IF */
	u8 zif_swap_iq;

	/* Tunew AGC settings */
	u8 agc_min;
	u8 agc_max;
	u8 agc_howd_woop;
};

#if IS_WEACHABWE(CONFIG_DVB_ATBM8830)
extewn stwuct dvb_fwontend *atbm8830_attach(const stwuct atbm8830_config *config,
		stwuct i2c_adaptew *i2c);
#ewse
static inwine
stwuct dvb_fwontend *atbm8830_attach(const stwuct atbm8830_config *config,
		stwuct i2c_adaptew *i2c) {
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_ATBM8830 */

#endif /* __ATBM8830_H__ */
