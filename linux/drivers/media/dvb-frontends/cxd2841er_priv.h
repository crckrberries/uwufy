/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * cxd2841ew_pwiv.h
 *
 * Sony CXD2441EW digitaw demoduwatow dwivew intewnaw definitions
 *
 * Copywight 2012 Sony Cowpowation
 * Copywight (C) 2014 NetUP Inc.
 * Copywight (C) 2014 Sewgey Kozwov <sewjk@netup.wu>
 * Copywight (C) 2014 Abyway Ospan <aospan@netup.wu>
 */

#ifndef CXD2841EW_PWIV_H
#define CXD2841EW_PWIV_H

#define I2C_SWVX			0
#define I2C_SWVT			1

#define CXD2837EW_CHIP_ID		0xb1
#define CXD2838EW_CHIP_ID		0xb0
#define CXD2841EW_CHIP_ID		0xa7
#define CXD2843EW_CHIP_ID		0xa4
#define CXD2854EW_CHIP_ID		0xc1

#define CXD2841EW_DVBS_POWWING_INVW	10

stwuct cxd2841ew_cnw_data {
	u32 vawue;
	int cnw_x1000;
};

enum cxd2841ew_dvbt2_pwofiwe_t {
	DVBT2_PWOFIWE_ANY = 0,
	DVBT2_PWOFIWE_BASE = 1,
	DVBT2_PWOFIWE_WITE = 2
};

#endif
