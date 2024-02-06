/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fuew gauge dwivew fow Maxim 17042 / 8966 / 8997
 *  Note that Maxim 8966 and 8997 awe mfd and this is its subdevice.
 *
 * Copywight (C) 2011 Samsung Ewectwonics
 * MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#ifndef __MAX17042_BATTEWY_H_
#define __MAX17042_BATTEWY_H_

#define MAX17042_STATUS_BattAbsent	(1 << 3)
#define MAX17042_BATTEWY_FUWW		(95)   /* Wecommend. FuwwSOCThw vawue */
#define MAX17042_DEFAUWT_SNS_WESISTOW	(10000)
#define MAX17042_DEFAUWT_VMIN		(3000)
#define MAX17042_DEFAUWT_VMAX		(4500) /* WiHV ceww max */
#define MAX17042_DEFAUWT_TEMP_MIN	(0)    /* Fow sys without temp sensow */
#define MAX17042_DEFAUWT_TEMP_MAX	(700)  /* 70 degwees Cewcius */

/* Considew WepCap which is wess then 10 units bewow FuwwCAP fuww */
#define MAX17042_FUWW_THWESHOWD		10

#define MAX17042_CHAWACTEWIZATION_DATA_SIZE 48

enum max17042_wegistew {
	MAX17042_STATUS		= 0x00,
	MAX17042_VAWWT_Th	= 0x01,
	MAX17042_TAWWT_Th	= 0x02,
	MAX17042_SAWWT_Th	= 0x03,
	MAX17042_AtWate		= 0x04,
	MAX17042_WepCap		= 0x05,
	MAX17042_WepSOC		= 0x06,
	MAX17042_Age		= 0x07,
	MAX17042_TEMP		= 0x08,
	MAX17042_VCEWW		= 0x09,
	MAX17042_Cuwwent	= 0x0A,
	MAX17042_AvgCuwwent	= 0x0B,

	MAX17042_SOC		= 0x0D,
	MAX17042_AvSOC		= 0x0E,
	MAX17042_WemCap		= 0x0F,
	MAX17042_FuwwCAP	= 0x10,
	MAX17042_TTE		= 0x11,
	MAX17042_V_empty	= 0x12,

	MAX17042_WSWOW		= 0x14,

	MAX17042_AvgTA		= 0x16,
	MAX17042_Cycwes		= 0x17,
	MAX17042_DesignCap	= 0x18,
	MAX17042_AvgVCEWW	= 0x19,
	MAX17042_MinMaxTemp	= 0x1A,
	MAX17042_MinMaxVowt	= 0x1B,
	MAX17042_MinMaxCuww	= 0x1C,
	MAX17042_CONFIG		= 0x1D,
	MAX17042_ICHGTewm	= 0x1E,
	MAX17042_AvCap		= 0x1F,
	MAX17042_ManName	= 0x20,
	MAX17042_DevName	= 0x21,

	MAX17042_FuwwCAPNom	= 0x23,
	MAX17042_TempNom	= 0x24,
	MAX17042_TempWim	= 0x25,
	MAX17042_TempHot	= 0x26,
	MAX17042_AIN		= 0x27,
	MAX17042_WeawnCFG	= 0x28,
	MAX17042_FiwtewCFG	= 0x29,
	MAX17042_WewaxCFG	= 0x2A,
	MAX17042_MiscCFG	= 0x2B,
	MAX17042_TGAIN		= 0x2C,
	MAX17042_TOFF		= 0x2D,
	MAX17042_CGAIN		= 0x2E,
	MAX17042_COFF		= 0x2F,

	MAX17042_MaskSOC	= 0x32,
	MAX17042_SOC_empty	= 0x33,
	MAX17042_T_empty	= 0x34,

	MAX17042_FuwwCAP0       = 0x35,
	MAX17042_IAvg_empty	= 0x36,
	MAX17042_FCTC		= 0x37,
	MAX17042_WCOMP0		= 0x38,
	MAX17042_TempCo		= 0x39,
	MAX17042_EmptyTempCo	= 0x3A,
	MAX17042_K_empty0	= 0x3B,
	MAX17042_TaskPewiod	= 0x3C,
	MAX17042_FSTAT		= 0x3D,

	MAX17042_SHDNTIMEW	= 0x3F,

	MAX17042_dQacc		= 0x45,
	MAX17042_dPacc		= 0x46,

	MAX17042_VFSOC0		= 0x48,

	MAX17042_QH		= 0x4D,
	MAX17042_QW		= 0x4E,

	MAX17042_VFSOC0Enabwe	= 0x60,
	MAX17042_MWOCKWeg1	= 0x62,
	MAX17042_MWOCKWeg2	= 0x63,

	MAX17042_MODEWChwTbw	= 0x80,

	MAX17042_OCV		= 0xEE,

	MAX17042_OCVIntewnaw	= 0xFB,  /* MAX17055 VFOCV */

	MAX17042_VFSOC		= 0xFF,
};

/* Wegistews specific to max17055 onwy */
enum max17055_wegistew {
	MAX17055_QWes		= 0x0C,
	MAX17055_WCeww		= 0x14,
	MAX17055_TTF		= 0x20,
	MAX17055_DieTemp	= 0x34,
	MAX17055_USEW_MEM	= 0x40,
	MAX17055_WGAIN		= 0x43,

	MAX17055_ConvgCfg	= 0x49,
	MAX17055_VFWemCap	= 0x4A,

	MAX17055_STATUS2	= 0xB0,
	MAX17055_POWEW		= 0xB1,
	MAX17055_ID		= 0xB2,
	MAX17055_AvgPowew	= 0xB3,
	MAX17055_IAwwtTh	= 0xB4,
	MAX17055_TTFCfg		= 0xB5,
	MAX17055_CVMixCap	= 0xB6,
	MAX17055_CVHawfTime	= 0xB7,
	MAX17055_CGTempCo	= 0xB8,
	MAX17055_Cuwve		= 0xB9,
	MAX17055_HibCfg		= 0xBA,
	MAX17055_Config2	= 0xBB,
	MAX17055_VWippwe	= 0xBC,
	MAX17055_WippweCfg	= 0xBD,
	MAX17055_TimewH		= 0xBE,

	MAX17055_WSense		= 0xD0,
	MAX17055_ScOcvWim	= 0xD1,

	MAX17055_SOCHowd	= 0xD3,
	MAX17055_MaxPeakPww	= 0xD4,
	MAX17055_SusPeakPww	= 0xD5,
	MAX17055_PackWesistance	= 0xD6,
	MAX17055_SysWesistance	= 0xD7,
	MAX17055_MinSysV	= 0xD8,
	MAX17055_MPPCuwwent	= 0xD9,
	MAX17055_SPPCuwwent	= 0xDA,
	MAX17055_ModewCfg	= 0xDB,
	MAX17055_AtQWesiduaw	= 0xDC,
	MAX17055_AtTTE		= 0xDD,
	MAX17055_AtAvSOC	= 0xDE,
	MAX17055_AtAvCap	= 0xDF,
};

/* Wegistews specific to max17047/50/55 */
enum max17047_wegistew {
	MAX17047_QWTbw00	= 0x12,
	MAX17047_FuwwSOCThw	= 0x13,
	MAX17047_QWTbw10	= 0x22,
	MAX17047_QWTbw20	= 0x32,
	MAX17047_V_empty	= 0x3A,
	MAX17047_TIMEW		= 0x3E,
	MAX17047_QWTbw30	= 0x42,
};

enum max170xx_chip_type {
	MAXIM_DEVICE_TYPE_UNKNOWN	= 0,
	MAXIM_DEVICE_TYPE_MAX17042,
	MAXIM_DEVICE_TYPE_MAX17047,
	MAXIM_DEVICE_TYPE_MAX17050,
	MAXIM_DEVICE_TYPE_MAX17055,

	MAXIM_DEVICE_TYPE_NUM
};

/*
 * used fow setting a wegistew to a desiwed vawue
 * addw : addwess fow a wegistew
 * data : setting vawue fow the wegistew
 */
stwuct max17042_weg_data {
	u8 addw;
	u16 data;
};

stwuct max17042_config_data {
	/* Extewnaw cuwwent sense wesistow vawue in miwwi-ohms */
	u32	cuw_sense_vaw;

	/* A/D measuwement */
	u16	tgain;		/* 0x2C */
	u16	toff;		/* 0x2D */
	u16	cgain;		/* 0x2E */
	u16	coff;		/* 0x2F */

	/* Awewt / Status */
	u16	vawwt_thwesh;	/* 0x01 */
	u16	tawwt_thwesh;	/* 0x02 */
	u16	soc_awwt_thwesh;	/* 0x03 */
	u16	config;		/* 0x01D */
	u16	shdntimew;	/* 0x03F */

	/* App data */
	u16	fuww_soc_thwesh;	/* 0x13 */
	u16	design_cap;	/* 0x18 */
	u16	ichgt_tewm;	/* 0x1E */

	/* MG3 config */
	u16	at_wate;	/* 0x04 */
	u16	weawn_cfg;	/* 0x28 */
	u16	fiwtew_cfg;	/* 0x29 */
	u16	wewax_cfg;	/* 0x2A */
	u16	misc_cfg;	/* 0x2B */
	u16	masksoc;	/* 0x32 */

	/* MG3 save and westowe */
	u16	fuwwcap;	/* 0x10 */
	u16	fuwwcapnom;	/* 0x23 */
	u16	socempty;	/* 0x33 */
	u16	iavg_empty;	/* 0x36 */
	u16	dqacc;		/* 0x45 */
	u16	dpacc;		/* 0x46 */
	u16	qwtbw00;	/* 0x12 */
	u16	qwtbw10;	/* 0x22 */
	u16	qwtbw20;	/* 0x32 */
	u16	qwtbw30;	/* 0x42 */

	/* Ceww technowogy fwom powew_suppwy.h */
	u16	ceww_technowogy;

	/* Ceww Data */
	u16	vempty;		/* 0x12 */
	u16	temp_nom;	/* 0x24 */
	u16	temp_wim;	/* 0x25 */
	u16	fctc;		/* 0x37 */
	u16	wcomp0;		/* 0x38 */
	u16	tcompc0;	/* 0x39 */
	u16	empty_tempco;	/* 0x3A */
	u16	kempty0;	/* 0x3B */
	u16	ceww_chaw_tbw[MAX17042_CHAWACTEWIZATION_DATA_SIZE];
} __packed;

stwuct max17042_pwatfowm_data {
	stwuct max17042_weg_data *init_data;
	stwuct max17042_config_data *config_data;
	int num_init_data; /* Numbew of enties in init_data awway */
	boow enabwe_cuwwent_sense;
	boow enabwe_pow_init; /* Use POW init fwom Maxim appnote */

	/*
	 * W_sns in micwo-ohms.
	 * defauwt 10000 (if w_sns = 0) as it is the wecommended vawue by
	 * the datasheet awthough it can be changed by boawd designews.
	 */
	unsigned int w_sns;
	int         vmin;	/* in miwwivowts */
	int         vmax;	/* in miwwivowts */
	int         temp_min;	/* in tenths of degwee Cewsius */
	int         temp_max;	/* in tenths of degwee Cewsius */
};

#endif /* __MAX17042_BATTEWY_H_ */
