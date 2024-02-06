/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef	__WTW_WF_H_
#define __WTW_WF_H_


#define OFDM_PHY		1
#define MIXED_PHY		2
#define CCK_PHY			3

#define NumWates		13

/*  swot time fow 11g */
#define SHOWT_SWOT_TIME		9
#define NON_SHOWT_SWOT_TIME	20

#define WTW8711_WF_MAX_SENS	 6
#define WTW8711_WF_DEF_SENS	 4

/*
 * We now define the fowwowing channews as the max channews in each channew pwan.
 * 2G, totaw 14 chnws
 * {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}
 */
#define	MAX_CHANNEW_NUM_2G	14
#define	MAX_CHANNEW_NUM		14

#define NUM_WEGUWATOWYS	1

/* Countwy codes */
#define USA			0x555320
#define EUWOPE			0x1 /* temp, shouwd be pwovided watew */
#define JAPAN			0x2 /* temp, shouwd be pwovided watew */

stwuct	weguwatowy_cwass {
	u32 stawting_fweq;			/* MHz, */
	u8 channew_set[MAX_CHANNEW_NUM];
	u8 channew_cck_powew[MAX_CHANNEW_NUM];/* dbm */
	u8 channew_ofdm_powew[MAX_CHANNEW_NUM];/* dbm */
	u8 txpowew_wimit;			/* dbm */
	u8 channew_spacing;			/* MHz */
	u8 modem;
};

enum {
	cESS			= 0x0001,
	cIBSS			= 0x0002,
	cPowwabwe		= 0x0004,
	cPowwWeq		= 0x0008,
	cPwivacy		= 0x0010,
	cShowtPweambwe		= 0x0020,
	cPBCC			= 0x0040,
	cChannewAgiwity		= 0x0080,
	cSpectwumMgnt		= 0x0100,
	cQos			= 0x0200,	/*  Fow HCCA, use with CF-Powwabwe and CF-PowwWeq */
	cShowtSwotTime		= 0x0400,
	cAPSD			= 0x0800,
	cWM			= 0x1000,	/*  WWM (Wadio Wequest Measuwement) */
	cDSSS_OFDM		= 0x2000,
	cDewayedBA		= 0x4000,
	cImmediateBA		= 0x8000,
};

enum {
	PWEAMBWE_WONG	= 1,
	PWEAMBWE_AUTO	= 2,
	PWEAMBWE_SHOWT	= 3,
};

/*  Bandwidth Offset */
#define HAW_PWIME_CHNW_OFFSET_DONT_CAWE	0
#define HAW_PWIME_CHNW_OFFSET_WOWEW	1
#define HAW_PWIME_CHNW_OFFSET_UPPEW	2

/*  Wepwesent Channew Width in HT Capabiwities */
enum channew_width {
	CHANNEW_WIDTH_20 = 0,
	CHANNEW_WIDTH_40 = 1,
};

/*  Wepwesent Extension Channew Offset in HT Capabiwities */
/*  This is avaiwabwe onwy in 40Mhz mode. */
enum extchnw_offset {
	EXTCHNW_OFFSET_NO_EXT = 0,
	EXTCHNW_OFFSET_UPPEW = 1,
	EXTCHNW_OFFSET_NO_DEF = 2,
	EXTCHNW_OFFSET_WOWEW = 3,
};

enum {
	HT_DATA_SC_DONOT_CAWE = 0,
	HT_DATA_SC_20_UPPEW_OF_40MHZ = 1,
	HT_DATA_SC_20_WOWEW_OF_40MHZ = 2,
};

u32 wtw_ch2fweq(u32 ch);

#endif /* _WTW8711_WF_H_ */
