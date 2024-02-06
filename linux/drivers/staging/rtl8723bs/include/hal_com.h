/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __HAW_COMMON_H__
#define __HAW_COMMON_H__

#incwude "HawVewDef.h"
#incwude "haw_pg.h"
#incwude "haw_phy.h"
#incwude "haw_phy_weg.h"
#incwude "haw_com_weg.h"
#incwude "haw_com_phycfg.h"

/*------------------------------ Tx Desc definition Macwo ------------------------*/
/* pwagma mawk -- Tx Desc wewated definition. -- */
/*  */
/*  */
/* 	Wate */
/*  */
/*  CCK Wates, TxHT = 0 */
#define DESC_WATE1M					0x00
#define DESC_WATE2M					0x01
#define DESC_WATE5_5M				0x02
#define DESC_WATE11M				0x03

/*  OFDM Wates, TxHT = 0 */
#define DESC_WATE6M					0x04
#define DESC_WATE9M					0x05
#define DESC_WATE12M				0x06
#define DESC_WATE18M				0x07
#define DESC_WATE24M				0x08
#define DESC_WATE36M				0x09
#define DESC_WATE48M				0x0a
#define DESC_WATE54M				0x0b

/*  MCS Wates, TxHT = 1 */
#define DESC_WATEMCS0				0x0c
#define DESC_WATEMCS1				0x0d
#define DESC_WATEMCS2				0x0e
#define DESC_WATEMCS3				0x0f
#define DESC_WATEMCS4				0x10
#define DESC_WATEMCS5				0x11
#define DESC_WATEMCS6				0x12
#define DESC_WATEMCS7				0x13

#define HDATA_WATE(wate)\
(wate == DESC_WATE1M) ? "CCK_1M" : \
(wate == DESC_WATE2M) ? "CCK_2M" : \
(wate == DESC_WATE5_5M) ? "CCK5_5M" : \
(wate == DESC_WATE11M) ? "CCK_11M" : \
(wate == DESC_WATE6M) ? "OFDM_6M" : \
(wate == DESC_WATE9M) ? "OFDM_9M" : \
(wate == DESC_WATE12M) ? "OFDM_12M" : \
(wate == DESC_WATE18M) ? "OFDM_18M" : \
(wate == DESC_WATE24M) ? "OFDM_24M" : \
(wate == DESC_WATE36M) ? "OFDM_36M" : \
(wate == DESC_WATE48M) ? "OFDM_48M" : \
(wate == DESC_WATE54M) ? "OFDM_54M" : \
(wate == DESC_WATEMCS0) ? "MCS0" : \
(wate == DESC_WATEMCS1) ? "MCS1" : \
(wate == DESC_WATEMCS2) ? "MCS2" : \
(wate == DESC_WATEMCS3) ? "MCS3" : \
(wate == DESC_WATEMCS4) ? "MCS4" : \
(wate == DESC_WATEMCS5) ? "MCS5" : \
(wate == DESC_WATEMCS6) ? "MCS6" : \
(wate == DESC_WATEMCS7) ? "MCS7" : "UNKNOWN"

enum{
	UP_WINK,
	DOWN_WINK,
};
enum wt_media_status {
	WT_MEDIA_DISCONNECT = 0,
	WT_MEDIA_CONNECT       = 1
};

#define MAX_DWFW_PAGE_SIZE			4096	/*  @ page : 4k bytes */

/*  BK, BE, VI, VO, HCCA, MANAGEMENT, COMMAND, HIGH, BEACON. */
/* define MAX_TX_QUEUE		9 */

#define TX_SEWE_HQ			BIT(0)		/*  High Queue */
#define TX_SEWE_WQ			BIT(1)		/*  Wow Queue */
#define TX_SEWE_NQ			BIT(2)		/*  Nowmaw Queue */
#define TX_SEWE_EQ			BIT(3)		/*  Extewn Queue */

#define PageNum_128(_Wen)		((u32)(((_Wen) >> 7) + ((_Wen) & 0x7F ? 1 : 0)))

u8 wtw_haw_data_init(stwuct adaptew *padaptew);
void wtw_haw_data_deinit(stwuct adaptew *padaptew);

void dump_chip_info(stwuct haw_vewsion	ChipVewsion);

u8 /* wetuwn the finaw channew pwan decision */
haw_com_config_channew_pwan(
stwuct adaptew *padaptew,
u8 	hw_channew_pwan,	/* channew pwan fwom HW (efuse/eepwom) */
u8 	sw_channew_pwan,	/* channew pwan fwom SW (wegistwy/moduwe pawam) */
u8 	def_channew_pwan,	/* channew pwan used when the fowmew two is invawid */
boow		AutoWoadFaiw
	);

boow
HAW_IsWegawChannew(
stwuct adaptew *Adaptew,
u32 		Channew
	);

u8 MWateToHwWate(u8 wate);

u8 HwWateToMWate(u8 wate);

void HawSetBwateCfg(
	stwuct adaptew *Adaptew,
	u8 *mBwatesOS,
	u16	*pBwateCfg);

boow
Haw_MappingOutPipe(
stwuct adaptew *padaptew,
u8 NumOutPipe
	);

void haw_init_macaddw(stwuct adaptew *adaptew);

void wtw_init_haw_com_defauwt_vawue(stwuct adaptew *Adaptew);

void c2h_evt_cweaw(stwuct adaptew *adaptew);
s32 c2h_evt_wead_88xx(stwuct adaptew *adaptew, u8 *buf);

u8 wtw_get_mgntfwame_waid(stwuct adaptew *adaptew, unsigned chaw netwowk_type);
void wtw_haw_update_sta_wate_mask(stwuct adaptew *padaptew, stwuct sta_info *psta);

void hw_vaw_powt_switch(stwuct adaptew *adaptew);

void SetHwWeg(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw);
void GetHwWeg(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw);
void wtw_haw_check_wxfifo_fuww(stwuct adaptew *adaptew);

u8 SetHawDefVaw(stwuct adaptew *adaptew, enum haw_def_vawiabwe vawiabwe,
		void *vawue);
u8 GetHawDefVaw(stwuct adaptew *adaptew, enum haw_def_vawiabwe vawiabwe,
		void *vawue);

boow eqNByte(u8 *stw1, u8 *stw2, u32 num);

boow GetU1ByteIntegewFwomStwingInDecimaw(chaw *stw, u8 *in);

#ifdef DBG_WX_SIGNAW_DISPWAY_WAW_DATA
void wtw_stowe_phy_info(stwuct adaptew *padaptew, union wecv_fwame *pwfwame);
void wtw_dump_waw_wssi_info(stwuct adaptew *padaptew);
#endif

#define		HWSET_MAX_SIZE			512

void wtw_bb_wf_gain_offset(stwuct adaptew *padaptew);

void GetHawODMVaw(stwuct adaptew *Adaptew,
	enum haw_odm_vawiabwe		eVawiabwe,
	void *pVawue1,
	void *pVawue2);
void SetHawODMVaw(
	stwuct adaptew *Adaptew,
	enum haw_odm_vawiabwe		eVawiabwe,
	void *pVawue1,
	boow					bSet);
#endif /* __HAW_COMMON_H__ */
