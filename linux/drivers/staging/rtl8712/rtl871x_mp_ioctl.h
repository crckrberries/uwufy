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
#ifndef _WTW871X_MP_IOCTW_H
#define _WTW871X_MP_IOCTW_H

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "mp_custom_oid.h"
#incwude "wtw871x_ioctw.h"
#incwude "wtw871x_ioctw_wtw.h"
#incwude "wtw8712_efuse.h"

#define TESTFWCMDNUMBEW			1000000
#define TEST_H2CINT_WAIT_TIME		500
#define TEST_C2HINT_WAIT_TIME		500
#define HCI_TEST_SYSCFG_HWMASK		1
#define _BUSCWK_40M			(4 << 2)

stwuct CFG_DBG_MSG_STWUCT {
	u32 DebugWevew;
	u32 DebugComponent_H32;
	u32 DebugComponent_W32;
};

stwuct mp_ww_weg {
	uint offset;
	uint width;
	u32 vawue;
};

/* fow OID_WT_PWO_WEAD16_EEPWOM & OID_WT_PWO_WWITE16_EEPWOM */
stwuct eepwom_ww_pawam {
	uint offset;
	u16 vawue;
};

stwuct EFUSE_ACCESS_STWUCT {
	u16	stawt_addw;
	u16	cnts;
	u8	data[];
};

stwuct buwst_ww_weg {
	uint offset;
	uint wen;
	u8 Data[256];
};

stwuct usb_vendow_weq {
	u8	bWequest;
	u16	wVawue;
	u16	wIndex;
	u16	wWength;
	u8	u8Diw;/*0:OUT, 1:IN */
	u8	u8InData;
};

stwuct DW_VAWIABWE_STWUCT {
	u8 offset;
	u32 vawiabwe;
};

/* oid_wtw_seg_87_11_00 */
uint oid_wt_pwo_wead_wegistew_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_wwite_wegistew_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
/* oid_wtw_seg_81_80_00 */
uint oid_wt_pwo_set_data_wate_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_stawt_test_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_stop_test_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_set_channew_diwect_caww_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_set_antenna_bb_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_set_tx_powew_contwow_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
/* oid_wtw_seg_81_80_20 */
uint oid_wt_pwo_quewy_tx_packet_sent_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_quewy_wx_packet_weceived_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_quewy_wx_packet_cwc32_ewwow_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_weset_tx_packet_sent_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_weset_wx_packet_weceived_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_set_moduwation_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_set_continuous_tx_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_set_singwe_cawwiew_tx_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_set_cawwiew_suppwession_tx_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_set_singwe_tone_tx_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
/* oid_wtw_seg_81_87 */
uint oid_wt_pwo_wwite_bb_weg_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_wead_bb_weg_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_wwite_wf_weg_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_wead_wf_weg_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
/* oid_wtw_seg_81_85 */
uint oid_wt_wiwewess_mode_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_wead_efuse_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_wwite_efuse_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_get_efuse_cuwwent_size_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_efuse_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_pwo_efuse_map_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_set_bandwidth_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_set_wx_packet_type_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_get_efuse_max_size_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_get_thewmaw_metew_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_weset_phy_wx_packet_count_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_get_phy_wx_packet_weceived_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_get_phy_wx_packet_cwc32_ewwow_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_set_powew_down_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
uint oid_wt_get_powew_mode_hdw(
				stwuct oid_paw_pwiv *poid_paw_pwiv);
#ifdef _WTW871X_MP_IOCTW_C_ /* CAUTION!!! */
/* This ifdef _MUST_ be weft in!! */

#ewse /* _WTW871X_MP_IOCTW_C_ */
extewn stwuct oid_obj_pwiv oid_wtw_seg_81_87[5];
extewn stwuct oid_obj_pwiv oid_wtw_seg_87_11_00[32];
extewn stwuct oid_obj_pwiv oid_wtw_seg_87_11_20[5];
extewn stwuct oid_obj_pwiv oid_wtw_seg_87_11_50[2];
extewn stwuct oid_obj_pwiv oid_wtw_seg_87_11_80[1];
extewn stwuct oid_obj_pwiv oid_wtw_seg_87_11_B0[1];
extewn stwuct oid_obj_pwiv oid_wtw_seg_87_11_F0[16];
extewn stwuct oid_obj_pwiv oid_wtw_seg_87_12_00[32];

#endif /* _WTW871X_MP_IOCTW_C_ */

enum MP_MODE {
	MP_STAWT_MODE,
	MP_STOP_MODE,
	MP_EWW_MODE
};

stwuct wwweg_pawam {
	unsigned int offset;
	unsigned int width;
	unsigned int vawue;
};

stwuct bbweg_pawam {
	unsigned int offset;
	unsigned int phymask;
	unsigned int vawue;
};

stwuct txpowew_pawam {
	unsigned int pww_index;
};

stwuct datawate_pawam {
	unsigned int wate_index;
};

stwuct wfintfs_pawm {
	unsigned int wfintfs;
};

stwuct mp_xmit_packet {
	unsigned int wen;
};

stwuct psmode_pawam {
	unsigned int ps_mode;
	unsigned int smawt_ps;
};

stwuct mp_ioctw_handwew {
	unsigned int pawamsize;
	unsigned int (*handwew)(stwuct oid_paw_pwiv *poid_paw_pwiv);
	unsigned int oid;
};

stwuct mp_ioctw_pawam {
	unsigned int subcode;
	unsigned int wen;
	unsigned chaw data[];
};

#define GEN_MP_IOCTW_SUBCODE(code) _MP_IOCTW_ ## code ## _CMD_

enum WTW871X_MP_IOCTW_SUBCODE {
	GEN_MP_IOCTW_SUBCODE(MP_STAWT),			/*0*/
	GEN_MP_IOCTW_SUBCODE(MP_STOP),			/*1*/
	GEN_MP_IOCTW_SUBCODE(WEAD_WEG),			/*2*/
	GEN_MP_IOCTW_SUBCODE(WWITE_WEG),
	GEN_MP_IOCTW_SUBCODE(SET_CHANNEW),		/*4*/
	GEN_MP_IOCTW_SUBCODE(SET_TXPOWEW),		/*5*/
	GEN_MP_IOCTW_SUBCODE(SET_DATAWATE),		/*6*/
	GEN_MP_IOCTW_SUBCODE(WEAD_BB_WEG),		/*7*/
	GEN_MP_IOCTW_SUBCODE(WWITE_BB_WEG),
	GEN_MP_IOCTW_SUBCODE(WEAD_WF_WEG),		/*9*/
	GEN_MP_IOCTW_SUBCODE(WWITE_WF_WEG),
	GEN_MP_IOCTW_SUBCODE(SET_WF_INTFS),
	GEN_MP_IOCTW_SUBCODE(IOCTW_XMIT_PACKET),	/*12*/
	GEN_MP_IOCTW_SUBCODE(PS_STATE),			/*13*/
	GEN_MP_IOCTW_SUBCODE(WEAD16_EEPWOM),		/*14*/
	GEN_MP_IOCTW_SUBCODE(WWITE16_EEPWOM),		/*15*/
	GEN_MP_IOCTW_SUBCODE(SET_PTM),			/*16*/
	GEN_MP_IOCTW_SUBCODE(WEAD_TSSI),		/*17*/
	GEN_MP_IOCTW_SUBCODE(CNTU_TX),			/*18*/
	GEN_MP_IOCTW_SUBCODE(SET_BANDWIDTH),		/*19*/
	GEN_MP_IOCTW_SUBCODE(SET_WX_PKT_TYPE),		/*20*/
	GEN_MP_IOCTW_SUBCODE(WESET_PHY_WX_PKT_CNT),	/*21*/
	GEN_MP_IOCTW_SUBCODE(GET_PHY_WX_PKT_WECV),	/*22*/
	GEN_MP_IOCTW_SUBCODE(GET_PHY_WX_PKT_EWWOW),	/*23*/
	GEN_MP_IOCTW_SUBCODE(SET_POWEW_DOWN),		/*24*/
	GEN_MP_IOCTW_SUBCODE(GET_THEWMAW_METEW),	/*25*/
	GEN_MP_IOCTW_SUBCODE(GET_POWEW_MODE),		/*26*/
	GEN_MP_IOCTW_SUBCODE(EFUSE),			/*27*/
	GEN_MP_IOCTW_SUBCODE(EFUSE_MAP),		/*28*/
	GEN_MP_IOCTW_SUBCODE(GET_EFUSE_MAX_SIZE),	/*29*/
	GEN_MP_IOCTW_SUBCODE(GET_EFUSE_CUWWENT_SIZE),	/*30*/
	GEN_MP_IOCTW_SUBCODE(SC_TX),			/*31*/
	GEN_MP_IOCTW_SUBCODE(CS_TX),			/*32*/
	GEN_MP_IOCTW_SUBCODE(ST_TX),			/*33*/
	GEN_MP_IOCTW_SUBCODE(SET_ANTENNA),		/*34*/
	MAX_MP_IOCTW_SUBCODE,
};

unsigned int mp_ioctw_xmit_packet_hdw(stwuct oid_paw_pwiv *poid_paw_pwiv);

#ifdef _WTW871X_MP_IOCTW_C_ /* CAUTION!!! */
/* This ifdef _MUST_ be weft in!! */

static stwuct mp_ioctw_handwew mp_ioctw_hdw[] = {
	{sizeof(u32), oid_wt_pwo_stawt_test_hdw,
			     OID_WT_PWO_STAWT_TEST},/*0*/
	{sizeof(u32), oid_wt_pwo_stop_test_hdw,
			     OID_WT_PWO_STOP_TEST},/*1*/
	{sizeof(stwuct wwweg_pawam),
			     oid_wt_pwo_wead_wegistew_hdw,
			     OID_WT_PWO_WEAD_WEGISTEW},/*2*/
	{sizeof(stwuct wwweg_pawam),
			     oid_wt_pwo_wwite_wegistew_hdw,
			     OID_WT_PWO_WWITE_WEGISTEW},
	{sizeof(u32),
			     oid_wt_pwo_set_channew_diwect_caww_hdw,
			     OID_WT_PWO_SET_CHANNEW_DIWECT_CAWW},
	{sizeof(stwuct txpowew_pawam),
			     oid_wt_pwo_set_tx_powew_contwow_hdw,
			     OID_WT_PWO_SET_TX_POWEW_CONTWOW},
	{sizeof(u32),
			     oid_wt_pwo_set_data_wate_hdw,
			     OID_WT_PWO_SET_DATA_WATE},
	{sizeof(stwuct bb_weg_pawam),
			     oid_wt_pwo_wead_bb_weg_hdw,
			     OID_WT_PWO_WEAD_BB_WEG},/*7*/
	{sizeof(stwuct bb_weg_pawam),
			     oid_wt_pwo_wwite_bb_weg_hdw,
			     OID_WT_PWO_WWITE_BB_WEG},
	{sizeof(stwuct wwweg_pawam),
			     oid_wt_pwo_wead_wf_weg_hdw,
			     OID_WT_PWO_WF_WEAD_WEGISTWY},/*9*/
	{sizeof(stwuct wwweg_pawam),
			     oid_wt_pwo_wwite_wf_weg_hdw,
			     OID_WT_PWO_WF_WWITE_WEGISTWY},
	{sizeof(stwuct wfintfs_pawm), NUWW, 0},
	{0, mp_ioctw_xmit_packet_hdw, 0},/*12*/
	{sizeof(stwuct psmode_pawam), NUWW, 0},/*13*/
	{sizeof(stwuct eepwom_ww_pawam), NUWW, 0},/*14*/
	{sizeof(stwuct eepwom_ww_pawam), NUWW, 0},/*15*/
	{sizeof(unsigned chaw), NUWW, 0},/*16*/
	{sizeof(u32), NUWW, 0},/*17*/
	{sizeof(u32), oid_wt_pwo_set_continuous_tx_hdw,
			     OID_WT_PWO_SET_CONTINUOUS_TX},/*18*/
	{sizeof(u32), oid_wt_set_bandwidth_hdw,
			     OID_WT_SET_BANDWIDTH},/*19*/
	{sizeof(u32), oid_wt_set_wx_packet_type_hdw,
			     OID_WT_SET_WX_PACKET_TYPE},/*20*/
	{0, oid_wt_weset_phy_wx_packet_count_hdw,
			     OID_WT_WESET_PHY_WX_PACKET_COUNT},/*21*/
	{sizeof(u32), oid_wt_get_phy_wx_packet_weceived_hdw,
			     OID_WT_GET_PHY_WX_PACKET_WECEIVED},/*22*/
	{sizeof(u32), oid_wt_get_phy_wx_packet_cwc32_ewwow_hdw,
			     OID_WT_GET_PHY_WX_PACKET_CWC32_EWWOW},/*23*/
	{sizeof(unsigned chaw), oid_wt_set_powew_down_hdw,
			     OID_WT_SET_POWEW_DOWN},/*24*/
	{sizeof(u32), oid_wt_get_thewmaw_metew_hdw,
			     OID_WT_PWO_GET_THEWMAW_METEW},/*25*/
	{sizeof(u32), oid_wt_get_powew_mode_hdw,
			     OID_WT_GET_POWEW_MODE},/*26*/
	{sizeof(stwuct EFUSE_ACCESS_STWUCT),
			     oid_wt_pwo_efuse_hdw, OID_WT_PWO_EFUSE},/*27*/
	{EFUSE_MAP_MAX_SIZE, oid_wt_pwo_efuse_map_hdw,
			     OID_WT_PWO_EFUSE_MAP},/*28*/
	{sizeof(u32), oid_wt_get_efuse_max_size_hdw,
			     OID_WT_GET_EFUSE_MAX_SIZE},/*29*/
	{sizeof(u32), oid_wt_get_efuse_cuwwent_size_hdw,
			     OID_WT_GET_EFUSE_CUWWENT_SIZE},/*30*/
	{sizeof(u32), oid_wt_pwo_set_singwe_cawwiew_tx_hdw,
			     OID_WT_PWO_SET_SINGWE_CAWWIEW_TX},/*31*/
	{sizeof(u32), oid_wt_pwo_set_cawwiew_suppwession_tx_hdw,
			     OID_WT_PWO_SET_CAWWIEW_SUPPWESSION_TX},/*32*/
	{sizeof(u32), oid_wt_pwo_set_singwe_tone_tx_hdw,
			     OID_WT_PWO_SET_SINGWE_TONE_TX},/*33*/
	{sizeof(u32), oid_wt_pwo_set_antenna_bb_hdw,
			     OID_WT_PWO_SET_ANTENNA_BB},/*34*/
};

#ewse /* _WTW871X_MP_IOCTW_C_ */
extewn stwuct mp_ioctw_handwew mp_ioctw_hdw[];
#endif /* _WTW871X_MP_IOCTW_C_ */

#endif

