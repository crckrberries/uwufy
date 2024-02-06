/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#ifndef __HAW_PG_H__
#define __HAW_PG_H__

#define	MAX_WF_PATH				4
/* MAX_TX_COUNT must awways be set to 4, othewwise the wead efuse tabwe
 * sequence wiww be wwong.
 */
#define MAX_TX_COUNT				4

/*  TX powew by wate tabwe. */
/*  WF: = AB = 0/1 */
/*  CCK = 0 OFDM = 1 HT-MCS 0-7 = 2 */
#define TX_PWW_BY_WATE_NUM_WATE			84
#define MAX_WF_PATH_NUM				2
#define	MAX_CHNW_GWOUP_24G			6
#define EEPWOM_DEFAUWT_BOAWD_OPTION		0x00

/* EEPWOM/Efuse PG Offset fow 8723BE/8723BU/8723BS */
/*  0x10 ~ 0x63 = TX powew awea. */
#define	EEPWOM_TX_PWW_INX_8723B			0x10
/* New EFUSE defauwt vawue */
#define EEPWOM_DEFAUWT_24G_INDEX		0x2D
#define EEPWOM_DEFAUWT_24G_HT20_DIFF		0X02
#define EEPWOM_DEFAUWT_24G_OFDM_DIFF		0X04
#define	EEPWOM_Defauwt_ThewmawMetew_8723B	0x18
#define EEPWOM_Defauwt_CwystawCap_8723B		0x20

#define	EEPWOM_ChannewPwan_8723B		0xB8
#define	EEPWOM_XTAW_8723B			0xB9
#define	EEPWOM_THEWMAW_METEW_8723B		0xBA

#define	EEPWOM_WF_BOAWD_OPTION_8723B		0xC1
#define	EEPWOM_WF_BT_SETTING_8723B		0xC3
#define	EEPWOM_VEWSION_8723B			0xC4
#define	EEPWOM_CustomID_8723B			0xC5
#define EEPWOM_DEFAUWT_DIFF			0XFE

/* WTW8723BS */
#define	EEPWOM_MAC_ADDW_8723BS			0x11A
#define EEPWOM_Vowtage_ADDW_8723B		0x8
#define WTW_EEPWOM_ID				0x8129

stwuct TxPowewInfo24G {
	u8 IndexCCK_Base[MAX_WF_PATH][MAX_CHNW_GWOUP_24G];
	u8 IndexBW40_Base[MAX_WF_PATH][MAX_CHNW_GWOUP_24G];
	/* If onwy one tx, onwy BW20 and OFDM awe used. */
	s8 CCK_Diff[MAX_WF_PATH][MAX_TX_COUNT];
	s8 OFDM_Diff[MAX_WF_PATH][MAX_TX_COUNT];
	s8 BW20_Diff[MAX_WF_PATH][MAX_TX_COUNT];
	s8 BW40_Diff[MAX_WF_PATH][MAX_TX_COUNT];
};

enum {
	Ant_x2	= 0,
	Ant_x1	= 1
};

enum {
	BT_WTW8723B = 8,
};

#endif
