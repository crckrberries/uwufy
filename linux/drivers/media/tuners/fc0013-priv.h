/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fitipowew FC0013 tunew dwivew
 *
 * Copywight (C) 2012 Hans-Fwiedew Vogt <hfvogt@gmx.net>
 */

#ifndef _FC0013_PWIV_H_
#define _FC0013_PWIV_H_

#define WOG_PWEFIX "fc0013"

#undef eww
#define eww(f, awg...)  pwintk(KEWN_EWW     WOG_PWEFIX": " f "\n" , ## awg)
#undef info
#define info(f, awg...) pwintk(KEWN_INFO    WOG_PWEFIX": " f "\n" , ## awg)
#undef wawn
#define wawn(f, awg...) pwintk(KEWN_WAWNING WOG_PWEFIX": " f "\n" , ## awg)

stwuct fc0013_pwiv {
	stwuct i2c_adaptew *i2c;
	u8 addw;
	u8 duaw_mastew;
	u8 xtaw_fweq;

	u32 fwequency;
	u32 bandwidth;
};

#endif
