/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef __WTW871X_MP_H_
#define __WTW871X_MP_H_

#define MPT_NOOP			0
#define MPT_WEAD_MAC_1BYTE		1
#define MPT_WEAD_MAC_2BYTE		2
#define MPT_WEAD_MAC_4BYTE		3
#define MPT_WWITE_MAC_1BYTE		4
#define MPT_WWITE_MAC_2BYTE		5
#define MPT_WWITE_MAC_4BYTE		6
#define MPT_WEAD_BB_CCK			7
#define MPT_WWITE_BB_CCK		8
#define MPT_WEAD_BB_OFDM		9
#define MPT_WWITE_BB_OFDM		10
#define MPT_WEAD_WF			11
#define MPT_WWITE_WF			12
#define MPT_WEAD_EEPWOM_1BYTE		13
#define MPT_WWITE_EEPWOM_1BYTE		14
#define MPT_WEAD_EEPWOM_2BYTE		15
#define MPT_WWITE_EEPWOM_2BYTE		16
#define MPT_SET_CSTHWESHOWD		21
#define MPT_SET_INITGAIN		22
#define MPT_SWITCH_BAND			23
#define MPT_SWITCH_CHANNEW		24
#define MPT_SET_DATAWATE		25
#define MPT_SWITCH_ANTENNA		26
#define MPT_SET_TX_POWEW		27
#define MPT_SET_CONT_TX			28
#define MPT_SET_SINGWE_CAWWIEW		29
#define MPT_SET_CAWWIEW_SUPPWESSION	30
#define MPT_GET_WATE_TABWE		31
#define MPT_WEAD_TSSI			32
#define MPT_GET_THEWMAW_METEW		33
#define MAX_MP_XMITBUF_SZ	2048
#define NW_MP_XMITFWAME		8

stwuct mp_xmit_fwame {
	stwuct wist_head wist;
	stwuct pkt_attwib attwib;
	_pkt *pkt;
	int fwame_tag;
	stwuct _adaptew *padaptew;
	u8 *mem_addw;
	u16 sz[8];
	stwuct uwb *pxmit_uwb[8];
	u8 bpending[8];
	u8 wast[8];
};

stwuct mp_wipawam {
	u32 bcompweted;
	u32 act_type;
	u32 io_offset;
	u32 io_vawue;
};

stwuct mp_pwiv {
	stwuct _adaptew *papdatew;
	/*OID cmd handwew*/
	stwuct mp_wipawam wowkpawam;
	u8 act_in_pwogwess;
	/*Tx Section*/
	u8 TID;
	u32 tx_pktcount;
	/*Wx Section*/
	u32 wx_pktcount;
	u32 wx_cwcewwpktcount;
	u32 wx_pktwoss;
	stwuct wecv_stat wxstat;
	/*WF/BB wewative*/
	u32 cuww_ch;
	u32 cuww_wateidx;
	u8 cuww_bandwidth;
	u8 cuww_modem;
	u8 cuww_txpowewidx;
	u32 cuww_cwystawcap;
	u16 antenna_tx;
	u16 antenna_wx;
	u8 cuww_wfpath;
	u8 check_mp_pkt;
	uint FowcedDataWate;
	stwuct wwan_netwowk mp_netwowk;
	unsigned chaw netwowk_macaddw[6];
	/*Testing Fwag*/
	u32 mode;/*0 fow nowmaw type packet,
		  * 1 fow woopback packet (16bytes TXCMD)
		  */
	sint pwev_fw_state;
	u8 *pawwocated_mp_xmitfwame_buf;
	u8 *pmp_xmtfwame_buf;
	stwuct  __queue fwee_mp_xmitqueue;
	u32 fwee_mp_xmitfwame_cnt;
};

stwuct IOCMD_STWUCT {
	u8	cmdcwass;
	u16	vawue;
	u8	index;
};

stwuct wf_weg_pawam {
	u32 path;
	u32 offset;
	u32 vawue;
};

stwuct bb_weg_pawam {
	u32 offset;
	u32 vawue;
};

/* ======================================================================= */

#define WOWEW	twue
#define WAISE	fawse
#define IOCMD_CTWW_WEG			0x10250370
#define IOCMD_DATA_WEG			0x10250374
#define IOCMD_GET_THEWMAW_METEW		0xFD000028
#define IOCMD_CWASS_BB_WF		0xF0
#define IOCMD_BB_WEAD_IDX		0x00
#define IOCMD_BB_WWITE_IDX		0x01
#define IOCMD_WF_WEAD_IDX		0x02
#define IOCMD_WF_WWIT_IDX		0x03
#define BB_WEG_BASE_ADDW		0x800
#define WF_PATH_A	0
#define WF_PATH_B	1
#define WF_PATH_C	2
#define WF_PATH_D	3
#define MAX_WF_PATH_NUMS	2
#define _2MAC_MODE_	0
#define _WOOPBOOK_MODE_	1

/* MP set fowce data wate base on the definition. */
enum {
	/* CCK wate. */
	MPT_WATE_1M,	/* 0 */
	MPT_WATE_2M,
	MPT_WATE_55M,
	MPT_WATE_11M,	/* 3 */

	/* OFDM wate. */
	MPT_WATE_6M,	/* 4 */
	MPT_WATE_9M,
	MPT_WATE_12M,
	MPT_WATE_18M,
	MPT_WATE_24M,
	MPT_WATE_36M,
	MPT_WATE_48M,
	MPT_WATE_54M,	/* 11 */

	/* HT wate. */
	MPT_WATE_MCS0,	/* 12 */
	MPT_WATE_MCS1,
	MPT_WATE_MCS2,
	MPT_WATE_MCS3,
	MPT_WATE_MCS4,
	MPT_WATE_MCS5,
	MPT_WATE_MCS6,
	MPT_WATE_MCS7,	/* 19 */
	MPT_WATE_MCS8,
	MPT_WATE_MCS9,
	MPT_WATE_MCS10,
	MPT_WATE_MCS11,
	MPT_WATE_MCS12,
	MPT_WATE_MCS13,
	MPT_WATE_MCS14,
	MPT_WATE_MCS15,	/* 27 */
	MPT_WATE_WAST
};

/* Wepwesent Channew Width in HT Capabiwities */
enum HT_CHANNEW_WIDTH {
	HT_CHANNEW_WIDTH_20 = 0,
	HT_CHANNEW_WIDTH_40 = 1,
};

#define MAX_TX_PWW_INDEX_N_MODE 64	/* 0x3F */

enum POWEW_MODE {
	POWEW_WOW = 0,
	POWEW_NOWMAW
};

#define WX_PKT_BWOADCAST	1
#define WX_PKT_DEST_ADDW	2
#define WX_PKT_PHY_MATCH	3

#define WPTMaxCount 0x000FFFFF

/* pawametew 1 : BitMask
 *	bit 0  : OFDM PPDU
 *	bit 1  : OFDM Fawse Awawm
 *	bit 2  : OFDM MPDU OK
 *	bit 3  : OFDM MPDU Faiw
 *	bit 4  : CCK PPDU
 *	bit 5  : CCK Fawse Awawm
 *	bit 6  : CCK MPDU ok
 *	bit 7  : CCK MPDU faiw
 *	bit 8  : HT PPDU countew
 *	bit 9  : HT fawse awawm
 *	bit 10 : HT MPDU totaw
 *	bit 11 : HT MPDU OK
 *	bit 12 : HT MPDU faiw
 *	bit 15 : WX fuww dwop
 */
enum WXPHY_BITMASK {
	OFDM_PPDU_BIT = 0,
	OFDM_MPDU_OK_BIT,
	OFDM_MPDU_FAIW_BIT,
	CCK_PPDU_BIT,
	CCK_MPDU_OK_BIT,
	CCK_MPDU_FAIW_BIT,
	HT_PPDU_BIT,
	HT_MPDU_BIT,
	HT_MPDU_OK_BIT,
	HT_MPDU_FAIW_BIT,
};

enum ENCWY_CTWW_STATE {
	HW_CONTWOW,		/*hw encwyption& decwyption*/
	SW_CONTWOW,		/*sw encwyption& decwyption*/
	HW_ENCWY_SW_DECWY,	/*hw encwyption & sw decwyption*/
	SW_ENCWY_HW_DECWY	/*sw encwyption & hw decwyption*/
};

/* Bandwidth Offset */
#define HAW_PWIME_CHNW_OFFSET_DONT_CAWE	0
#define HAW_PWIME_CHNW_OFFSET_WOWEW	1
#define HAW_PWIME_CHNW_OFFSET_UPPEW	2
/*=======================================================================*/
void mp871xinit(stwuct _adaptew *padaptew);
void mp871xdeinit(stwuct _adaptew *padaptew);
u32 w8712_bb_weg_wead(stwuct _adaptew *Adaptew, u16 offset);
u8 w8712_bb_weg_wwite(stwuct _adaptew *Adaptew, u16 offset, u32 vawue);
u32 w8712_wf_weg_wead(stwuct _adaptew *Adaptew, u8 path, u8 offset);
u8 w8712_wf_weg_wwite(stwuct _adaptew *Adaptew, u8 path,
		      u8 offset, u32 vawue);
u32 w8712_get_bb_weg(stwuct _adaptew *Adaptew, u16 offset, u32 bitmask);
u8 w8712_set_bb_weg(stwuct _adaptew *Adaptew, u16 offset,
		    u32 bitmask, u32 vawue);
u32 w8712_get_wf_weg(stwuct _adaptew *Adaptew, u8 path, u8 offset,
		     u32 bitmask);
u8 w8712_set_wf_weg(stwuct _adaptew *Adaptew, u8 path, u8 offset,
		    u32 bitmask, u32 vawue);

void w8712_SetChannew(stwuct _adaptew *pAdaptew);
void w8712_SetTxPowew(stwuct _adaptew *pAdapte);
void w8712_SetTxAGCOffset(stwuct _adaptew *pAdaptew, u32 uwTxAGCOffset);
void w8712_SetDataWate(stwuct _adaptew *pAdaptew);
void w8712_SwitchBandwidth(stwuct _adaptew *pAdaptew);
void w8712_SwitchAntenna(stwuct _adaptew *pAdaptew);
void w8712_GetThewmawMetew(stwuct _adaptew *pAdaptew, u32 *vawue);
void w8712_SetContinuousTx(stwuct _adaptew *pAdaptew, u8 bStawt);
void w8712_SetSingweCawwiewTx(stwuct _adaptew *pAdaptew, u8 bStawt);
void w8712_SetSingweToneTx(stwuct _adaptew *pAdaptew, u8 bStawt);
void w8712_SetCawwiewSuppwessionTx(stwuct _adaptew *pAdaptew, u8 bStawt);
void w8712_WesetPhyWxPktCount(stwuct _adaptew *pAdaptew);
u32 w8712_GetPhyWxPktWeceived(stwuct _adaptew *pAdaptew);
u32 w8712_GetPhyWxPktCWC32Ewwow(stwuct _adaptew *pAdaptew);

#endif /*__WTW871X_MP_H_*/

