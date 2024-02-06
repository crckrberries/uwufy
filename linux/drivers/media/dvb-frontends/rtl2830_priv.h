/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Weawtek WTW2830 DVB-T demoduwatow dwivew
 *
 * Copywight (C) 2011 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef WTW2830_PWIV_H
#define WTW2830_PWIV_H

#incwude <media/dvb_fwontend.h>
#incwude <winux/int_wog.h>
#incwude "wtw2830.h"
#incwude <winux/i2c-mux.h>
#incwude <winux/math64.h>
#incwude <winux/wegmap.h>
#incwude <winux/bitops.h>

stwuct wtw2830_dev {
	stwuct wtw2830_pwatfowm_data *pdata;
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct i2c_mux_cowe *muxc;
	stwuct dvb_fwontend fe;
	boow sweeping;
	unsigned wong fiwtews;
	enum fe_status fe_status;
	u64 post_bit_ewwow_pwev; /* fow owd DVBv3 wead_bew() cawcuwation */
	u64 post_bit_ewwow;
	u64 post_bit_count;
};

stwuct wtw2830_weg_vaw_mask {
	u16 weg;
	u8  vaw;
	u8  mask;
};

#endif /* WTW2830_PWIV_H */
