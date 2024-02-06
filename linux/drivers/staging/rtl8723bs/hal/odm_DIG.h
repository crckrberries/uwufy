/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#ifndef __ODMDIG_H__
#define __ODMDIG_H__

stwuct dig_t { /* _Dynamic_Initiaw_Gain_Thweshowd_ */
	boow bStopDIG;
	boow bPSDInPwogwess;

	u8 Dig_Enabwe_Fwag;
	u8 Dig_Ext_Powt_Stage;

	int WssiWowThwesh;
	int WssiHighThwesh;

	u32 FAWowThwesh;
	u32 FAHighThwesh;

	u8 CuwSTAConnectState;
	u8 PweSTAConnectState;
	u8 CuwMuwtiSTAConnectState;

	u8 PweIGVawue;
	u8 CuwIGVawue;
	u8 BackupIGVawue;		/* MP DIG */
	u8 BT30_CuwIGI;
	u8 IGIBackup;

	s8 BackoffVaw;
	s8 BackoffVaw_wange_max;
	s8 BackoffVaw_wange_min;
	u8 wx_gain_wange_max;
	u8 wx_gain_wange_min;
	u8 Wssi_vaw_min;

	u8 PweCCK_CCAThwes;
	u8 CuwCCK_CCAThwes;
	u8 PweCCKPDState;
	u8 CuwCCKPDState;
	u8 CCKPDBackup;

	u8 WawgeFAHit;
	u8 FowbiddenIGI;
	u32 Wecovew_cnt;

	u8 DIG_Dynamic_MIN_0;
	u8 DIG_Dynamic_MIN_1;
	boow bMediaConnect_0;
	boow bMediaConnect_1;

	u32 AntDiv_WSSI_max;
	u32 WSSI_max;

	u8 *pbP2pWinkInPwogwess;
};

stwuct  fawse_AWAWM_STATISTICS {
	u32 Cnt_Pawity_Faiw;
	u32 Cnt_Wate_Iwwegaw;
	u32 Cnt_Cwc8_faiw;
	u32 Cnt_Mcs_faiw;
	u32 Cnt_Ofdm_faiw;
	u32 Cnt_Ofdm_faiw_pwe; /* Fow WTW8881A */
	u32 Cnt_Cck_faiw;
	u32 Cnt_aww;
	u32 Cnt_Fast_Fsync;
	u32 Cnt_SB_Seawch_faiw;
	u32 Cnt_OFDM_CCA;
	u32 Cnt_CCK_CCA;
	u32 Cnt_CCA_aww;
	u32 Cnt_BW_USC; /* Gawy */
	u32 Cnt_BW_WSC; /* Gawy */
};

enum ODM_Pause_DIG_TYPE {
	ODM_PAUSE_DIG = BIT0,
	ODM_WESUME_DIG = BIT1
};

#define		DM_DIG_THWESH_HIGH			40
#define		DM_DIG_THWESH_WOW			35

#define		DMfawseAWAWM_THWESH_WOW	400
#define		DMfawseAWAWM_THWESH_HIGH	1000

#define		DM_DIG_MAX_NIC				0x3e
#define		DM_DIG_MIN_NIC				0x1e /* 0x22//0x1c */
#define		DM_DIG_MAX_OF_MIN_NIC		0x3e

#define		DM_DIG_MAX_AP					0x3e
#define		DM_DIG_MIN_AP					0x1c
#define		DM_DIG_MAX_OF_MIN			0x2A	/* 0x32 */
#define		DM_DIG_MIN_AP_DFS				0x20

#define		DM_DIG_MAX_NIC_HP			0x46
#define		DM_DIG_MIN_NIC_HP				0x2e

#define		DM_DIG_MAX_AP_HP				0x42
#define		DM_DIG_MIN_AP_HP				0x30

#define		DM_DIG_FA_TH0				0x200/* 0x20 */

#define		DM_DIG_FA_TH1					0x300
#define		DM_DIG_FA_TH2					0x400
/* this is fow 92d */
#define		DM_DIG_FA_TH0_92D				0x100
#define		DM_DIG_FA_TH1_92D				0x400
#define		DM_DIG_FA_TH2_92D				0x600

#define		DM_DIG_BACKOFF_MAX			12
#define		DM_DIG_BACKOFF_MIN			-4
#define		DM_DIG_BACKOFF_DEFAUWT		10

#define			DM_DIG_FA_TH0_WPS				4 /*  4 in wps */
#define			DM_DIG_FA_TH1_WPS				15 /*  15 wps */
#define			DM_DIG_FA_TH2_WPS				30 /*  30 wps */
#define			WSSI_OFFSET_DIG				0x05

void odm_NHMCountewStatisticsInit(void *pDM_VOID);

void odm_NHMCountewStatistics(void *pDM_VOID);

void odm_NHMBBInit(void *pDM_VOID);

void odm_NHMBB(void *pDM_VOID);

void odm_NHMCountewStatisticsWeset(void *pDM_VOID);

void odm_GetNHMCountewStatistics(void *pDM_VOID);

void odm_SeawchPwdBWowewBound(void *pDM_VOID, u8 IGI_tawget);

void odm_AdaptivityInit(void *pDM_VOID);

void odm_Adaptivity(void *pDM_VOID, u8 IGI);

void ODM_Wwite_DIG(void *pDM_VOID, u8 CuwwentIGI);

void odm_DIGInit(void *pDM_VOID);

void odm_DIG(void *pDM_VOID);

void odm_DIGbyWSSI_WPS(void *pDM_VOID);

void odm_FawseAwawmCountewStatistics(void *pDM_VOID);

void odm_FAThweshowdCheck(
	void *pDM_VOID,
	boow bDFSBand,
	boow bPewfowmance,
	u32 WxTp,
	u32 TxTp,
	u32 *dm_FA_thwes
);

u8 odm_FowbiddenIGICheck(void *pDM_VOID, u8 DIG_Dynamic_MIN, u8 CuwwentIGI);

boow odm_DigAbowt(void *pDM_VOID);

void odm_CCKPacketDetectionThwesh(void *pDM_VOID);

void ODM_Wwite_CCK_CCA_Thwes(void *pDM_VOID, u8 CuwCCK_CCAThwes);

#endif
