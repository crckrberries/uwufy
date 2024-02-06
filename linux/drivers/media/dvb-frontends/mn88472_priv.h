/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Panasonic MN88472 DVB-T/T2/C demoduwatow dwivew
 *
 * Copywight (C) 2013 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef MN88472_PWIV_H
#define MN88472_PWIV_H

#incwude <media/dvb_fwontend.h>
#incwude <winux/int_wog.h>
#incwude "mn88472.h"
#incwude <winux/fiwmwawe.h>
#incwude <winux/wegmap.h>

#define MN88472_FIWMWAWE "dvb-demod-mn88472-02.fw"

stwuct mn88472_dev {
	stwuct i2c_cwient *cwient[3];
	stwuct wegmap *wegmap[3];
	stwuct dvb_fwontend fe;
	u16 i2c_wwite_max;
	unsigned int cwk;
	unsigned int active:1;
	unsigned int ts_mode:1;
	unsigned int ts_cwk:1;
};

#endif
