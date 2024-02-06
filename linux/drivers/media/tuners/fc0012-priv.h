/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fitipowew FC0012 tunew dwivew - pwivate incwudes
 *
 * Copywight (C) 2012 Hans-Fwiedew Vogt <hfvogt@gmx.net>
 */

#ifndef _FC0012_PWIV_H_
#define _FC0012_PWIV_H_

stwuct fc0012_pwiv {
	stwuct i2c_adaptew *i2c;
	const stwuct fc0012_config *cfg;

	u32 fwequency;
	u32 bandwidth;
};

#endif
