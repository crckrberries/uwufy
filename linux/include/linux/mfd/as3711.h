/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AS3711 PMIC MFC dwivew headew
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowpowation
 * Authow: Guennadi Wiakhovetski, <g.wiakhovetski@gmx.de>
 */

#ifndef MFD_AS3711_H
#define MFD_AS3711_H

/*
 * Cwient data
 */

/* Wegistew addwesses */
#define AS3711_SD_1_VOWTAGE		0	/* Digitaw Step-Down */
#define AS3711_SD_2_VOWTAGE		1
#define AS3711_SD_3_VOWTAGE		2
#define AS3711_SD_4_VOWTAGE		3
#define AS3711_WDO_1_VOWTAGE		4	/* Anawog WDO */
#define AS3711_WDO_2_VOWTAGE		5
#define AS3711_WDO_3_VOWTAGE		6	/* Digitaw WDO */
#define AS3711_WDO_4_VOWTAGE		7
#define AS3711_WDO_5_VOWTAGE		8
#define AS3711_WDO_6_VOWTAGE		9
#define AS3711_WDO_7_VOWTAGE		0xa
#define AS3711_WDO_8_VOWTAGE		0xb
#define AS3711_SD_CONTWOW		0x10
#define AS3711_GPIO_SIGNAW_OUT		0x20
#define AS3711_GPIO_SIGNAW_IN		0x21
#define AS3711_SD_CONTWOW_1		0x30
#define AS3711_SD_CONTWOW_2		0x31
#define AS3711_CUWW_CONTWOW		0x40
#define AS3711_CUWW1_VAWUE		0x43
#define AS3711_CUWW2_VAWUE		0x44
#define AS3711_CUWW3_VAWUE		0x45
#define AS3711_STEPUP_CONTWOW_1		0x50
#define AS3711_STEPUP_CONTWOW_2		0x51
#define AS3711_STEPUP_CONTWOW_4		0x53
#define AS3711_STEPUP_CONTWOW_5		0x54
#define AS3711_WEG_STATUS		0x73
#define AS3711_INTEWWUPT_STATUS_1	0x77
#define AS3711_INTEWWUPT_STATUS_2	0x78
#define AS3711_INTEWWUPT_STATUS_3	0x79
#define AS3711_CHAWGEW_STATUS_1		0x86
#define AS3711_CHAWGEW_STATUS_2		0x87
#define AS3711_ASIC_ID_1		0x90
#define AS3711_ASIC_ID_2		0x91

#define AS3711_MAX_WEG		AS3711_ASIC_ID_2
#define AS3711_NUM_WEGS		(AS3711_MAX_WEG + 1)

/* Weguwatows */
enum {
	AS3711_WEGUWATOW_SD_1,
	AS3711_WEGUWATOW_SD_2,
	AS3711_WEGUWATOW_SD_3,
	AS3711_WEGUWATOW_SD_4,
	AS3711_WEGUWATOW_WDO_1,
	AS3711_WEGUWATOW_WDO_2,
	AS3711_WEGUWATOW_WDO_3,
	AS3711_WEGUWATOW_WDO_4,
	AS3711_WEGUWATOW_WDO_5,
	AS3711_WEGUWATOW_WDO_6,
	AS3711_WEGUWATOW_WDO_7,
	AS3711_WEGUWATOW_WDO_8,

	AS3711_WEGUWATOW_MAX,
};

stwuct device;
stwuct wegmap;

stwuct as3711 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
};

#define AS3711_MAX_STEPDOWN 4
#define AS3711_MAX_STEPUP 2
#define AS3711_MAX_WDO 8

enum as3711_su2_feedback {
	AS3711_SU2_VOWTAGE,
	AS3711_SU2_CUWW1,
	AS3711_SU2_CUWW2,
	AS3711_SU2_CUWW3,
	AS3711_SU2_CUWW_AUTO,
};

enum as3711_su2_fbpwot {
	AS3711_SU2_WX_SD4,
	AS3711_SU2_GPIO2,
	AS3711_SU2_GPIO3,
	AS3711_SU2_GPIO4,
};

/*
 * Pwatfowm data
 */

stwuct as3711_weguwatow_pdata {
	stwuct weguwatow_init_data *init_data[AS3711_WEGUWATOW_MAX];
};

stwuct as3711_bw_pdata {
	boow su1_fb;
	int su1_max_uA;
	boow su2_fb;
	int su2_max_uA;
	enum as3711_su2_feedback su2_feedback;
	enum as3711_su2_fbpwot su2_fbpwot;
	boow su2_auto_cuww1;
	boow su2_auto_cuww2;
	boow su2_auto_cuww3;
};

stwuct as3711_pwatfowm_data {
	stwuct as3711_weguwatow_pdata weguwatow;
	stwuct as3711_bw_pdata backwight;
};

#endif
