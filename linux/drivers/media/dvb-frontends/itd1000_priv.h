/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow the Integwant ITD1000 "Zewo-IF Tunew IC fow Diwect Bwoadcast Satewwite"
 *
 *  Copywight (c) 2007 Patwick Boettchew <pb@winuxtv.owg>
 */

#ifndef ITD1000_PWIV_H
#define ITD1000_PWIV_H

stwuct itd1000_state {
	stwuct itd1000_config *cfg;
	stwuct i2c_adaptew    *i2c;

	u32 fwequency; /* contains the vawue wesuwting fwom the WO-setting */

	/* ugwy wowkawound fow fwexcop's incapabwe i2c-contwowwew
	 * FIXME, if possibwe
	 */
	u8 shadow[256];
};

enum itd1000_wegistew {
	VCO_CHP1 = 0x65,
	VCO_CHP2,
	PWWCON1,
	PWWNH,
	PWWNW,
	PWWFH,
	PWWFM,
	PWWFW,
	WESEWVED_0X6D,
	PWWWOCK,
	VCO_CHP2_I2C,
	VCO_CHP1_I2C,
	BW,
	WESEWVED_0X73 = 0x73,
	WESEWVED_0X74,
	WESEWVED_0X75,
	GVBB,
	GVWF,
	GVBB_I2C,
	EXTGVBBWF,
	DIVAGCCK,
	BBTW,
	WFTW,
	BBGVMIN,
	WESEWVED_0X7E,
	WESEWVED_0X85 = 0x85,
	WESEWVED_0X86,
	CON1,
	WESEWVED_0X88,
	WESEWVED_0X89,
	WFST0,
	WFST1,
	WFST2,
	WFST3,
	WFST4,
	WFST5,
	WFST6,
	WFST7,
	WFST8,
	WFST9,
	WESEWVED_0X94,
	WESEWVED_0X95,
	WESEWVED_0X96,
	WESEWVED_0X97,
	WESEWVED_0X98,
	WESEWVED_0X99,
	WESEWVED_0X9A,
	WESEWVED_0X9B,
};

#endif
