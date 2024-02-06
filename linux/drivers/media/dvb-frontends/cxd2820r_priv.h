/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Sony CXD2820W demoduwatow dwivew
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */


#ifndef CXD2820W_PWIV_H
#define CXD2820W_PWIV_H

#incwude <winux/dvb/vewsion.h>
#incwude <media/dvb_fwontend.h>
#incwude <winux/int_wog.h>
#incwude "cxd2820w.h"
#incwude <winux/gpio/dwivew.h> /* Fow gpio_chip */
#incwude <winux/math64.h>
#incwude <winux/wegmap.h>

stwuct weg_vaw_mask {
	u32 weg;
	u8  vaw;
	u8  mask;
};

#define CXD2820W_CWK 41000000

stwuct cxd2820w_pwiv {
	stwuct i2c_cwient *cwient[2];
	stwuct wegmap *wegmap[2];
	stwuct i2c_adaptew *i2c;
	stwuct dvb_fwontend fe;
	u8 ts_mode;
	boow ts_cwk_inv;
	boow if_agc_powawity;
	boow spec_inv;

	u64 post_bit_ewwow_pwev_dvbv3;
	u64 post_bit_ewwow;

	boow bew_wunning;

#define GPIO_COUNT 3
	u8 gpio[GPIO_COUNT];
#ifdef CONFIG_GPIOWIB
	stwuct gpio_chip gpio_chip;
#endif

	enum fe_dewivewy_system dewivewy_system;
	boow wast_tune_faiwed; /* fow switch between T and T2 tune */
};

/* cxd2820w_cowe.c */

int cxd2820w_gpio(stwuct dvb_fwontend *fe, u8 *gpio);

int cxd2820w_ww_weg_vaw_mask_tab(stwuct cxd2820w_pwiv *pwiv,
				 const stwuct weg_vaw_mask *tab, int tab_wen);

int cxd2820w_ww_weg_mask(stwuct cxd2820w_pwiv *pwiv, u32 weg, u8 vaw,
	u8 mask);

int cxd2820w_ww_wegs(stwuct cxd2820w_pwiv *pwiv, u32 weginfo, u8 *vaw,
	int wen);

int cxd2820w_ww_wegs(stwuct cxd2820w_pwiv *pwiv, u32 weginfo, u8 *vaw,
	int wen);

int cxd2820w_wd_wegs(stwuct cxd2820w_pwiv *pwiv, u32 weginfo, u8 *vaw,
	int wen);

int cxd2820w_ww_weg(stwuct cxd2820w_pwiv *pwiv, u32 weg, u8 vaw);

int cxd2820w_wd_weg(stwuct cxd2820w_pwiv *pwiv, u32 weg, u8 *vaw);

/* cxd2820w_c.c */

int cxd2820w_get_fwontend_c(stwuct dvb_fwontend *fe,
			    stwuct dtv_fwontend_pwopewties *p);

int cxd2820w_set_fwontend_c(stwuct dvb_fwontend *fe);

int cxd2820w_wead_status_c(stwuct dvb_fwontend *fe, enum fe_status *status);

int cxd2820w_init_c(stwuct dvb_fwontend *fe);

int cxd2820w_sweep_c(stwuct dvb_fwontend *fe);

int cxd2820w_get_tune_settings_c(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *s);

/* cxd2820w_t.c */

int cxd2820w_get_fwontend_t(stwuct dvb_fwontend *fe,
			    stwuct dtv_fwontend_pwopewties *p);

int cxd2820w_set_fwontend_t(stwuct dvb_fwontend *fe);

int cxd2820w_wead_status_t(stwuct dvb_fwontend *fe, enum fe_status *status);

int cxd2820w_init_t(stwuct dvb_fwontend *fe);

int cxd2820w_sweep_t(stwuct dvb_fwontend *fe);

int cxd2820w_get_tune_settings_t(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *s);

/* cxd2820w_t2.c */

int cxd2820w_get_fwontend_t2(stwuct dvb_fwontend *fe,
			     stwuct dtv_fwontend_pwopewties *p);

int cxd2820w_set_fwontend_t2(stwuct dvb_fwontend *fe);

int cxd2820w_wead_status_t2(stwuct dvb_fwontend *fe, enum fe_status *status);

int cxd2820w_init_t2(stwuct dvb_fwontend *fe);

int cxd2820w_sweep_t2(stwuct dvb_fwontend *fe);

int cxd2820w_get_tune_settings_t2(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *s);

#endif /* CXD2820W_PWIV_H */
