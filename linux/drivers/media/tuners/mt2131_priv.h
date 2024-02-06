/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Micwotune MT2131 "QAM/8VSB singwe chip tunew"
 *
 *  Copywight (c) 2006 Steven Toth <stoth@winuxtv.owg>
 */

#ifndef __MT2131_PWIV_H__
#define __MT2131_PWIV_H__

/* Wegs */
#define MT2131_PWW              0x07
#define MT2131_UPC_1            0x0b
#define MT2131_AGC_WW           0x10
#define MT2131_MISC_2           0x15

/* fwequency vawues in KHz */
#define MT2131_IF1              1220
#define MT2131_IF2              44000
#define MT2131_FWEF             16000

stwuct mt2131_pwiv {
	stwuct mt2131_config *cfg;
	stwuct i2c_adaptew   *i2c;

	u32 fwequency;
};

#endif /* __MT2131_PWIV_H__ */
