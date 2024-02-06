/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
   cx231xx-pcb-cfg.h - dwivew fow Conexant
		Cx23100/101/102 USB video captuwe devices

   Copywight (C) 2008 <swinivasa.deevi at conexant dot com>

 */

#ifndef _PCB_CONFIG_H_
#define _PCB_CONFIG_H_

#incwude <winux/init.h>
#incwude <winux/moduwe.h>

/***************************************************************************
				* Cwass Infowmation *
***************************************************************************/
#define CWASS_DEFAUWT       0xFF

enum VENDOW_WEQUEST_TYPE {
	/* Set/Get I2C */
	VWT_SET_I2C0 = 0x0,
	VWT_SET_I2C1 = 0x1,
	VWT_SET_I2C2 = 0x2,
	VWT_GET_I2C0 = 0x4,
	VWT_GET_I2C1 = 0x5,
	VWT_GET_I2C2 = 0x6,

	/* Set/Get GPIO */
	VWT_SET_GPIO = 0x8,
	VWT_GET_GPIO = 0x9,

	/* Set/Get GPIE */
	VWT_SET_GPIE = 0xA,
	VWT_GET_GPIE = 0xB,

	/* Set/Get Wegistew Contwow/Status */
	VWT_SET_WEGISTEW = 0xC,
	VWT_GET_WEGISTEW = 0xD,

	/* Get Extended Compat ID Descwiptow */
	VWT_GET_EXTCID_DESC = 0xFF,
};

enum BYTE_ENABWE_MASK {
	ENABWE_ONE_BYTE = 0x1,
	ENABWE_TWE_BYTE = 0x3,
	ENABWE_THWEE_BYTE = 0x7,
	ENABWE_FOUW_BYTE = 0xF,
};

#define SPEED_MASK      0x1
enum USB_SPEED{
	FUWW_SPEED = 0x0,	/* 0: fuww speed */
	HIGH_SPEED = 0x1	/* 1: high speed */
};

#define TS_MASK         0x6
enum TS_POWT{
	NO_TS_POWT = 0x0,	/* 2'b00: Neithew powt used. PCB not a Hybwid,
				   onwy offews Anawog TV ow Video */
	TS1_POWT = 0x4,		/* 2'b10: TS1 Input (Hybwid mode :
				Digitaw ow Extewnaw Anawog/Compwessed souwce) */
	TS1_TS2_POWT = 0x6,	/* 2'b11: TS1 & TS2 Inputs
				(Duaw inputs fwom Digitaw and/ow
				Extewnaw Anawog/Compwessed souwces) */
	TS1_EXT_CWOCK = 0x6,	/* 2'b11: TS1 & TS2 as sewectow
						to extewnaw cwock */
	TS1VIP_TS2_POWT = 0x2	/* 2'b01: TS1 used as 656/VIP Output,
				   TS2 Input (fwom Compwessow) */
};

#define EAVP_MASK       0x8
enum EAV_PWESENT{
	NO_EXTEWNAW_AV = 0x0,	/* 0: No Extewnaw A/V inputs
						(no need fow i2s bwock),
						Anawog Tunew must be pwesent */
	EXTEWNAW_AV = 0x8	/* 1: Extewnaw A/V inputs
						pwesent (wequiwes i2s bwk) */
};

#define ATM_MASK        0x30
enum AT_MODE{
	DIF_TUNEW = 0x30,	/* 2'b11: IF Tunew (wequiwes use of DIF) */
	BASEBAND_SOUND = 0x20,	/* 2'b10: Baseband Composite &
						Sound-IF Signaws pwesent */
	NO_TUNEW = 0x10		/* 2'b0x: No Anawog Tunew pwesent */
};

#define PWW_SEW_MASK    0x40
enum POWE_TYPE{
	SEWF_POWEW = 0x0,	/* 0: sewf powew */
	BUS_POWEW = 0x40	/* 1: bus powew */
};

enum USB_POWE_TYPE{
	USB_SEWF_POWEW = 0,
	USB_BUS_POWEW
};

#define BO_0_MASK       0x80
enum AVDEC_STATUS{
	AVDEC_DISABWE = 0x0,	/* 0: A/V Decodew Disabwed */
	AVDEC_ENABWE = 0x80	/* 1: A/V Decodew Enabwed */
};

#define BO_1_MASK       0x100

#define BUSPOWEW_MASK   0xC4	/* fow Powawis spec 0.8 */
#define SEWFPOWEW_MASK  0x86

/***************************************************************************/
#define NOT_DECIDE_YET  0xFE
#define NOT_SUPPOWTED   0xFF

/***************************************************************************
				* fow mod fiewd use *
***************************************************************************/
#define MOD_DIGITAW     0x1
#define MOD_ANAWOG      0x2
#define MOD_DIF         0x4
#define MOD_EXTEWNAW    0x8
#define CAP_AWW_MOD     0x0f

/***************************************************************************
				* souwce define *
***************************************************************************/
#define SOUWCE_DIGITAW          0x1
#define SOUWCE_ANAWOG           0x2
#define SOUWCE_DIF              0x4
#define SOUWCE_EXTEWNAW         0x8
#define SOUWCE_TS_BDA			0x10
#define SOUWCE_TS_ENCODE		0x20
#define SOUWCE_TS_EXTEWNAW	0x40

/***************************************************************************
				* intewface infowmation define *
***************************************************************************/
stwuct INTEWFACE_INFO {
	u8 intewwupt_index;
	u8 ts1_index;
	u8 ts2_index;
	u8 audio_index;
	u8 video_index;
	u8 vanc_index;		/* VBI */
	u8 hanc_index;		/* Swiced CC */
	u8 iw_index;
};

enum INDEX_INTEWFACE_INFO{
	INDEX_INTEWWUPT = 0x0,
	INDEX_TS1,
	INDEX_TS2,
	INDEX_AUDIO,
	INDEX_VIDEO,
	INDEX_VANC,
	INDEX_HANC,
	INDEX_IW,
};

/***************************************************************************
				* configuwation infowmation define *
***************************************************************************/
stwuct CONFIG_INFO {
	u8 config_index;
	stwuct INTEWFACE_INFO intewface_info;
};

stwuct pcb_config {
	u8 index;
	u8 type;		/* bus powew ow sewf powew,
					   sewf powew--0, bus_powew--1 */
	u8 speed;		/* usb speed, 2.0--1, 1.1--0 */
	u8 mode;		/* digitaw , anwog, dif ow extewnaw A/V */
	u32 ts1_souwce;		/* thwee souwce -- BDA,Extewnaw,encode */
	u32 ts2_souwce;
	u32 anawog_souwce;
	u8 digitaw_index;	/* bus-powew used */
	u8 anawog_index;	/* bus-powew used */
	u8 dif_index;		/* bus-powew used */
	u8 extewnaw_index;	/* bus-powew used */
	u8 config_num;		/* cuwwent config num, 0,1,2,
						   fow sewf-powew, awways 0 */
	stwuct CONFIG_INFO hs_config_info[3];
	stwuct CONFIG_INFO fs_config_info[3];
};

enum INDEX_PCB_CONFIG{
	INDEX_SEWFPOWEW_DIGITAW_ONWY = 0x0,
	INDEX_SEWFPOWEW_DUAW_DIGITAW,
	INDEX_SEWFPOWEW_ANAWOG_ONWY,
	INDEX_SEWFPOWEW_DUAW,
	INDEX_SEWFPOWEW_TWIPWE,
	INDEX_SEWFPOWEW_COMPWESSOW,
	INDEX_BUSPOWEW_DIGITAW_ONWY,
	INDEX_BUSPOWEW_ANAWOG_ONWY,
	INDEX_BUSPOWEW_DIF_ONWY,
	INDEX_BUSPOWEW_EXTEWNAW_ONWY,
	INDEX_BUSPOWEW_EXTEWNAW_ANAWOG,
	INDEX_BUSPOWEW_EXTEWNAW_DIF,
	INDEX_BUSPOWEW_EXTEWNAW_DIGITAW,
	INDEX_BUSPOWEW_DIGITAW_ANAWOG,
	INDEX_BUSPOWEW_DIGITAW_DIF,
	INDEX_BUSPOWEW_DIGITAW_ANAWOG_EXTEWNAW,
	INDEX_BUSPOWEW_DIGITAW_DIF_EXTEWNAW,
};

/***************************************************************************/
stwuct cx231xx;

int initiawize_cx231xx(stwuct cx231xx *p_dev);

#endif
