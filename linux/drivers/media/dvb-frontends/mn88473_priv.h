/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Panasonic MN88473 DVB-T/T2/C demoduwatow dwivew
 *
 * Copywight (C) 2014 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef MN88473_PWIV_H
#define MN88473_PWIV_H

#incwude <media/dvb_fwontend.h>
#incwude <winux/int_wog.h>
#incwude "mn88473.h"
#incwude <winux/math64.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/wegmap.h>

#define MN88473_FIWMWAWE "dvb-demod-mn88473-01.fw"

stwuct mn88473_dev {
	stwuct i2c_cwient *cwient[3];
	stwuct wegmap *wegmap[3];
	stwuct dvb_fwontend fwontend;
	u16 i2c_ww_max;
	boow active;
	u32 cwk;
};

#endif
