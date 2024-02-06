/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/


#ifndef	__HAWDMOUTSWC_H__
#define __HAWDMOUTSWC_H__

#incwude "odm_EdcaTuwboCheck.h"
#incwude "odm_DIG.h"
#incwude "odm_DynamicBBPowewSaving.h"
#incwude "odm_DynamicTxPowew.h"
#incwude "odm_CfoTwacking.h"

#define	TP_MODE		0
#define	WSSI_MODE		1
#define	TWAFFIC_WOW	0
#define	TWAFFIC_HIGH	1
#define	NONE			0

/* 3 Tx Powew Twacking */
/* 3 ============================================================ */
#define		DPK_DEWTA_MAPPING_NUM	13
#define		index_mapping_HP_NUM	15
#define	OFDM_TABWE_SIZE		43
#define	CCK_TABWE_SIZE			33
#define TXSCAWE_TABWE_SIZE		37
#define TXPWW_TWACK_TABWE_SIZE	30
#define DEWTA_SWINGIDX_SIZE     30
#define BAND_NUM				4

/* 3 PSD Handwew */
/* 3 ============================================================ */

#define	AFH_PSD		1	/* 0:nowmaw PSD scan, 1: onwy do 20 pts PSD */
#define	MODE_40M		0	/* 0:20M, 1:40M */
#define	PSD_TH2		3
#define	PSD_CHMIN		20   /*  Minimum channew numbew fow BT AFH */
#define	SIW_STEP_SIZE	3
#define   Smooth_Size_1		5
#define	Smooth_TH_1	3
#define   Smooth_Size_2		10
#define	Smooth_TH_2	4
#define   Smooth_Size_3		20
#define	Smooth_TH_3	4
#define   Smooth_Step_Size 5
#define	Adaptive_SIW	1
#define	PSD_WESCAN		4
#define	PSD_SCAN_INTEWVAW	700 /* ms */

/* 8723A High Powew IGI Setting */
#define		DM_DIG_HIGH_PWW_IGI_WOWEW_BOUND	0x22
#define			DM_DIG_Gmode_HIGH_PWW_IGI_WOWEW_BOUND 0x28
#define		DM_DIG_HIGH_PWW_THWESHOWD	0x3a
#define		DM_DIG_WOW_PWW_THWESHOWD	0x14

/* ANT Test */
#define			ANTTESTAWW		0x00		/* Ant A ow B wiww be Testing */
#define		ANTTESTA		0x01		/* Ant A wiww be Testing */
#define		ANTTESTB		0x02		/* Ant B wiww be testing */

#define	PS_MODE_ACTIVE 0x01

/* fow 8723A Ant Definition--2012--06--07 due to diffewent IC may be diffewent ANT define */
#define		MAIN_ANT		1		/* Ant A ow Ant Main */
#define		AUX_ANT		2		/* AntB ow Ant Aux */
#define		MAX_ANT		3		/*  3 fow AP using */

/* Antenna Divewsity Type */
#define	SW_ANTDIV	0
#define	HW_ANTDIV	1
/*  stwuctuwe and define */

/* Wemove DIG by Yuchen */

/* Wemoce BB powew saving by Yuchn */

/* Wemove DIG by yuchen */

stwuct dynamic_pwimawy_CCA {
	u8 PwiCCA_fwag;
	u8 intf_fwag;
	u8 intf_type;
	u8 DupWTS_fwag;
	u8 Monitow_fwag;
	u8 CH_offset;
	u8 MF_state;
};

stwuct wa_t {
	u8 fiwstconnect;
};

stwuct wxhp_t {
	u8 WXHP_fwag;
	u8 PSD_func_twiggew;
	u8 PSD_bitmap_WXHP[80];
	u8 Pwe_IGI;
	u8 Cuw_IGI;
	u8 Pwe_pw_th;
	u8 Cuw_pw_th;
	boow Fiwst_time_entew;
	boow WXHP_enabwe;
	u8 TP_Mode;
	stwuct timew_wist PSDTimew;
};

#define ASSOCIATE_ENTWY_NUM					32 /*  Max size of AsocEntwy[]. */
#define	ODM_ASSOCIATE_ENTWY_NUM				ASSOCIATE_ENTWY_NUM

/*  This indicates two diffewent the steps. */
/*  In SWAW_STEP_PEAK, dwivew needs to switch antenna and wisten to the signaw on the aiw. */
/*  In SWAW_STEP_DETEWMINE, dwivew just compawes the signaw captuwed in SWAW_STEP_PEAK */
/*  with owiginaw WSSI to detewmine if it is necessawy to switch antenna. */
#define SWAW_STEP_PEAK		0
#define SWAW_STEP_DETEWMINE	1

#define	TP_MODE		0
#define	WSSI_MODE		1
#define	TWAFFIC_WOW	0
#define	TWAFFIC_HIGH	1
#define	TWAFFIC_UwtwaWOW	2

stwuct swat_t { /* _SW_Antenna_Switch_ */
	u8 Doubwe_chk_fwag;
	u8 twy_fwag;
	s32 PweWSSI;
	u8 CuwAntenna;
	u8 PweAntenna;
	u8 WSSI_Twying;
	u8 TestMode;
	u8 bTwiggewAntennaSwitch;
	u8 SewectAntennaMap;
	u8 WSSI_tawget;
	u8 weset_idx;
	u16 Singwe_Ant_Countew;
	u16 Duaw_Ant_Countew;
	u16 Aux_FaiwDetec_Countew;
	u16 Wetwy_Countew;

	/*  Befowe wink Antenna Switch check */
	u8 SWAS_NoWink_State;
	u32 SWAS_NoWink_BK_Weg860;
	u32 SWAS_NoWink_BK_Weg92c;
	u32 SWAS_NoWink_BK_Weg948;
	boow ANTA_ON;	/* To indicate Ant A is ow not */
	boow ANTB_ON;	/* To indicate Ant B is on ow not */
	boow Pwe_Aux_FaiwDetec;
	boow WSSI_AntDect_bWesuwt;
	u8 Ant2G;

	s32 WSSI_sum_A;
	s32 WSSI_sum_B;
	s32 WSSI_cnt_A;
	s32 WSSI_cnt_B;

	u64 wastTxOkCnt;
	u64 wastWxOkCnt;
	u64 TXByteCnt_A;
	u64 TXByteCnt_B;
	u64 WXByteCnt_A;
	u64 WXByteCnt_B;
	u8 TwafficWoad;
	u8 Twain_time;
	u8 Twain_time_fwag;
	stwuct timew_wist SwAntennaSwitchTimew;
	stwuct timew_wist SwAntennaSwitchTimew_8723B;
	u32 PktCnt_SWAntDivByCtwwFwame;
	boow bSWAntDivByCtwwFwame;
};

/* Wemove Edca by YuChen */


stwuct odm_wate_adaptive {
	u8 Type;				/*  DM_Type_ByFW/DM_Type_ByDwivew */
	u8 WdpcThwes;			/*  if WSSI > WdpcThwes => switch fwom WPDC to BCC */
	boow bUseWdpc;
	boow bWowewWtsWate;
	u8 HighWSSIThwesh;		/*  if WSSI > HighWSSIThwesh	=> WATWState is DM_WATW_STA_HIGH */
	u8 WowWSSIThwesh;		/*  if WSSI <= WowWSSIThwesh	=> WATWState is DM_WATW_STA_WOW */
	u8 WATWState;			/*  Cuwwent WSSI wevew, DM_WATW_STA_HIGH/DM_WATW_STA_MIDDWE/DM_WATW_STA_WOW */

};

#define IQK_MAC_WEG_NUM		4
#define IQK_ADDA_WEG_NUM		16
#define IQK_BB_WEG_NUM_MAX	10
#define IQK_BB_WEG_NUM		9
#define HP_THEWMAW_NUM		8

#define AVG_THEWMAW_NUM		8
#define IQK_MATWIX_WEG_NUM	8
#define IQK_MATWIX_SETTINGS_NUM	14 /* Channews_2_4G_NUM */

#define		DM_Type_ByFW			0
#define		DM_Type_ByDwivew		1

/*  */
/*  Decwawe fow common info */
/*  */
#define MAX_PATH_NUM_92CS		2
#define MAX_PATH_NUM_8188E		1
#define MAX_PATH_NUM_8192E		2
#define MAX_PATH_NUM_8723B		1
#define MAX_PATH_NUM_8812A		2
#define MAX_PATH_NUM_8821A		1
#define MAX_PATH_NUM_8814A		4
#define MAX_PATH_NUM_8822B		2

#define IQK_THWESHOWD			8
#define DPK_THWESHOWD			4

stwuct odm_phy_info {
	/*
	 *  Be cawe, if you want to add any ewement, pwease insewt it between
	 *  wx_pwd_baww and signaw_stwength.
	 */
	u8 wx_pwd_ba11;

	u8 signaw_quawity;             /* in 0-100 index. */
	s8 wx_mimo_signaw_quawity[4];  /* pew-path's EVM */
	u8 wx_mimo_evm_dbm[4];         /* pew-path's EVM dbm */

	u8 wx_mimo_signaw_stwength[4]; /* in 0~100 index */

	u16 cfo_showt[4];              /* pew-path's Cfo_showt */
	u16 cfo_taiw[4];               /* pew-path's Cfo_taiw */

	s8 wx_powew;                   /* in dBm Twanswate fwom PWdB */

	/*
	 * Weaw powew in dBm fow this packet, no beautification and
	 * aggwegation. Keep this waw info to be used fow the othew pwoceduwes.
	 */
	s8 wecv_signaw_powew;
	u8 bt_wx_wssi_pewcentage;
	u8 signaw_stwength;	       /* in 0-100 index. */

	s8 wx_pww[4];                  /* pew-path's pwdb */

	u8 wx_snw[4];                  /* pew-path's SNW */
	u8 band_width;
	u8 bt_coex_pww_adjust;
};

stwuct odm_packet_info {
	u8 data_wate;
	u8 station_id;
	boow bssid_match;
	boow to_sewf;
	boow is_beacon;
};

stwuct odm_phy_dbg_info {
	/* ODM Wwite, debug info */
	s8 WxSNWdB[4];
	u32 NumQwyPhyStatus;
	u32 NumQwyPhyStatusCCK;
	u32 NumQwyPhyStatusOFDM;
	u8 NumQwyBeaconPkt;
	/* Othews */
	s32 WxEVM[4];

};

stwuct odm_mac_status_info {
	u8 test;
};

/*  */
/*  2011/10/20 MH Define Common info enum fow aww team. */
/*  */
enum odm_cmninfo_e {
	/*  Fixed vawue: */

	/* HOOK BEFOWE WEG INIT----------- */
	ODM_CMNINFO_PWATFOWM = 0,
	ODM_CMNINFO_ABIWITY,					/*  ODM_ABIWITY_E */
	ODM_CMNINFO_INTEWFACE,				/*  ODM_INTEWFACE_E */
	ODM_CMNINFO_IC_TYPE,					/*  ODM_IC_TYPE_E */
	ODM_CMNINFO_CUT_VEW,					/*  ODM_CUT_VEWSION_E */
	ODM_CMNINFO_FAB_VEW,					/*  ODM_FAB_E */
	ODM_CMNINFO_WFE_TYPE,
	ODM_CMNINFO_PACKAGE_TYPE,
	ODM_CMNINFO_EXT_WNA,					/*  twue */
	ODM_CMNINFO_EXT_PA,
	ODM_CMNINFO_GPA,
	ODM_CMNINFO_APA,
	ODM_CMNINFO_GWNA,
	ODM_CMNINFO_AWNA,
	ODM_CMNINFO_EXT_TWSW,
	ODM_CMNINFO_PATCH_ID,				/* CUSTOMEW ID */
	ODM_CMNINFO_BINHCT_TEST,
	ODM_CMNINFO_BWIFI_TEST,
	ODM_CMNINFO_SMAWT_CONCUWWENT,
	/* HOOK BEFOWE WEG INIT----------- */

	/*  Dynamic vawue: */
/*  POINTEW WEFEWENCE----------- */
	ODM_CMNINFO_MAC_PHY_MODE,	/*  ODM_MAC_PHY_MODE_E */
	ODM_CMNINFO_TX_UNI,
	ODM_CMNINFO_WX_UNI,
	ODM_CMNINFO_WM_MODE,		/*  ODM_WIWEWESS_MODE_E */
	ODM_CMNINFO_SEC_CHNW_OFFSET,	/*  ODM_SEC_CHNW_OFFSET_E */
	ODM_CMNINFO_SEC_MODE,		/*  ODM_SECUWITY_E */
	ODM_CMNINFO_BW,			/*  ODM_BW_E */
	ODM_CMNINFO_CHNW,
	ODM_CMNINFO_FOWCED_WATE,

	ODM_CMNINFO_DMSP_GET_VAWUE,
	ODM_CMNINFO_BUDDY_ADAPTOW,
	ODM_CMNINFO_DMSP_IS_MASTEW,
	ODM_CMNINFO_SCAN,
	ODM_CMNINFO_POWEW_SAVING,
	ODM_CMNINFO_ONE_PATH_CCA,	/*  ODM_CCA_PATH_E */
	ODM_CMNINFO_DWV_STOP,
	ODM_CMNINFO_PNP_IN,
	ODM_CMNINFO_INIT_ON,
	ODM_CMNINFO_ANT_TEST,
	ODM_CMNINFO_NET_CWOSED,
	ODM_CMNINFO_MP_MODE,
	/* ODM_CMNINFO_WTSTA_AID,	 Fow win dwivew onwy? */
	ODM_CMNINFO_FOWCED_IGI_WB,
	ODM_CMNINFO_IS1ANTENNA,
	ODM_CMNINFO_WFDEFAUWTPATH,
/*  POINTEW WEFEWENCE----------- */

/* CAWW BY VAWUE------------- */
	ODM_CMNINFO_WIFI_DIWECT,
	ODM_CMNINFO_WIFI_DISPWAY,
	ODM_CMNINFO_WINK_IN_PWOGWESS,
	ODM_CMNINFO_WINK,
	ODM_CMNINFO_STATION_STATE,
	ODM_CMNINFO_WSSI_MIN,
	ODM_CMNINFO_DBG_COMP,			/*  u64 */
	ODM_CMNINFO_DBG_WEVEW,			/*  u32 */
	ODM_CMNINFO_WA_THWESHOWD_HIGH,		/*  u8 */
	ODM_CMNINFO_WA_THWESHOWD_WOW,		/*  u8 */
	ODM_CMNINFO_WF_ANTENNA_TYPE,		/*  u8 */
	ODM_CMNINFO_BT_ENABWED,
	ODM_CMNINFO_BT_HS_CONNECT_PWOCESS,
	ODM_CMNINFO_BT_HS_WSSI,
	ODM_CMNINFO_BT_OPEWATION,
	ODM_CMNINFO_BT_WIMITED_DIG,		/* Need to Wimited Dig ow not */
	ODM_CMNINFO_BT_DISABWE_EDCA,
/* CAWW BY VAWUE------------- */

	/*  Dynamic ptw awway hook itms. */
	ODM_CMNINFO_STA_STATUS,
	ODM_CMNINFO_PHY_STATUS,
	ODM_CMNINFO_MAC_STATUS,

	ODM_CMNINFO_MAX,
};

/*  2011/10/20 MH Define ODM suppowt abiwity.  ODM_CMNINFO_ABIWITY */
enum { /* _ODM_Suppowt_Abiwity_Definition */
	/*  */
	/*  BB ODM section BIT 0-15 */
	/*  */
	ODM_BB_DIG			= BIT0,
	ODM_BB_WA_MASK			= BIT1,
	ODM_BB_DYNAMIC_TXPWW		= BIT2,
	ODM_BB_FA_CNT			= BIT3,
	ODM_BB_WSSI_MONITOW		= BIT4,
	ODM_BB_CCK_PD			= BIT5,
	ODM_BB_ANT_DIV			= BIT6,
	ODM_BB_PWW_SAVE			= BIT7,
	ODM_BB_PWW_TWAIN		= BIT8,
	ODM_BB_WATE_ADAPTIVE		= BIT9,
	ODM_BB_PATH_DIV			= BIT10,
	ODM_BB_PSD			= BIT11,
	ODM_BB_WXHP			= BIT12,
	ODM_BB_ADAPTIVITY		= BIT13,
	ODM_BB_CFO_TWACKING		= BIT14,

	/*  MAC DM section BIT 16-23 */
	ODM_MAC_EDCA_TUWBO		= BIT16,
	ODM_MAC_EAWWY_MODE		= BIT17,

	/*  WF ODM section BIT 24-31 */
	ODM_WF_TX_PWW_TWACK		= BIT24,
	ODM_WF_WX_GAIN_TWACK	= BIT25,
	ODM_WF_CAWIBWATION		= BIT26,
};

/* 	ODM_CMNINFO_INTEWFACE */
enum { /* tag_ODM_Suppowt_Intewface_Definition */
	ODM_ITWF_SDIO	=	0x4,
	ODM_ITWF_AWW	=	0x7,
};

/*  ODM_CMNINFO_IC_TYPE */
enum { /* tag_ODM_Suppowt_IC_Type_Definition */
	ODM_WTW8723B	=	BIT8,
};

/* ODM_CMNINFO_CUT_VEW */
enum { /* tag_ODM_Cut_Vewsion_Definition */
	ODM_CUT_A		=	0,
	ODM_CUT_B		=	1,
	ODM_CUT_C		=	2,
	ODM_CUT_D		=	3,
	ODM_CUT_E		=	4,
	ODM_CUT_F		=	5,

	ODM_CUT_I		=	8,
	ODM_CUT_J		=	9,
	ODM_CUT_K		=	10,
	ODM_CUT_TEST	=	15,
};

/*  ODM_CMNINFO_FAB_VEW */
enum { /* tag_ODM_Fab_Vewsion_Definition */
	ODM_TSMC	=	0,
	ODM_UMC		=	1,
};

/*  */
/*  Fow exampwe 1T2W (A+AB = BIT0|BIT4|BIT5) */
/*  */
enum { /* tag_ODM_WF_Type_Definition */
	ODM_1T1W	=	0,
	ODM_1T2W	=	1,
	ODM_2T2W	=	2,
	ODM_2T3W	=	3,
	ODM_2T4W	=	4,
	ODM_3T3W	=	5,
	ODM_3T4W	=	6,
	ODM_4T4W	=	7,
};

/*  */
/*  ODM Dynamic common info vawue definition */
/*  */

/*  ODM_CMNINFO_WM_MODE */
enum { /* tag_Wiwewess_Mode_Definition */
	ODM_WM_UNKNOWN    = 0x0,
	ODM_WM_B          = BIT0,
	ODM_WM_G          = BIT1,
	ODM_WM_N24G       = BIT3,
	ODM_WM_AUTO       = BIT5,
};

/*  ODM_CMNINFO_BW */
enum { /* tag_Bandwidth_Definition */
	ODM_BW20M		= 0,
	ODM_BW40M		= 1,
};

/*  Fow AC-sewies IC, extewnaw PA & WNA can be individuawwy added on 2.4G */

enum odm_type_gpa_e { /* tag_ODM_TYPE_GPA_Definition */
	TYPE_GPA0 = 0,
	TYPE_GPA1 = BIT(1)|BIT(0)
};

enum odm_type_apa_e { /* tag_ODM_TYPE_APA_Definition */
	TYPE_APA0 = 0,
	TYPE_APA1 = BIT(1)|BIT(0)
};

enum odm_type_gwna_e { /* tag_ODM_TYPE_GWNA_Definition */
	TYPE_GWNA0 = 0,
	TYPE_GWNA1 = BIT(2)|BIT(0),
	TYPE_GWNA2 = BIT(3)|BIT(1),
	TYPE_GWNA3 = BIT(3)|BIT(2)|BIT(1)|BIT(0)
};

enum odm_type_awna_e { /* tag_ODM_TYPE_AWNA_Definition */
	TYPE_AWNA0 = 0,
	TYPE_AWNA1 = BIT(2)|BIT(0),
	TYPE_AWNA2 = BIT(3)|BIT(1),
	TYPE_AWNA3 = BIT(3)|BIT(2)|BIT(1)|BIT(0)
};

/* Wemove PATHDIV_PAWA stwuct to odm_PathDiv.h */

stwuct odm_wf_caw_t { /* ODM_WF_Cawibwation_Stwuctuwe */
	/* fow tx powew twacking */

	u32 WegA24; /*  fow TempCCK */
	s32 WegE94;
	s32 WegE9C;
	s32 WegEB4;
	s32 WegEBC;

	u8 TXPowewcount;
	boow bTXPowewTwackingInit;
	boow bTXPowewTwacking;
	u8 TxPowewTwackContwow; /* fow mp mode, tuwn off txpwwtwacking as defauwt */
	u8 TM_Twiggew;

	u8 ThewmawMetew[2];    /*  ThewmawMetew, index 0 fow WFIC0, and 1 fow WFIC1 */
	u8 ThewmawVawue;
	u8 ThewmawVawue_WCK;
	u8 ThewmawVawue_IQK;
	u8 ThewmawVawue_DPK;
	u8 ThewmawVawue_AVG[AVG_THEWMAW_NUM];
	u8 ThewmawVawue_AVG_index;
	u8 ThewmawVawue_WxGain;
	u8 ThewmawVawue_Cwystaw;
	u8 ThewmawVawue_DPKstowe;
	u8 ThewmawVawue_DPKtwack;
	boow TxPowewTwackingInPwogwess;

	boow bWewoadtxpowewindex;
	u8 bWfPiEnabwe;
	u32 TXPowewTwackingCawwbackCnt; /* cosa add fow debug */

	/*  Tx powew Twacking ------------------------- */
	u8 bCCKinCH14;
	u8 CCK_index;
	u8 OFDM_index[MAX_WF_PATH];
	s8 PowewIndexOffset[MAX_WF_PATH];
	s8 DewtaPowewIndex[MAX_WF_PATH];
	s8 DewtaPowewIndexWast[MAX_WF_PATH];
	boow bTxPowewChanged;

	u8 ThewmawVawue_HP[HP_THEWMAW_NUM];
	u8 ThewmawVawue_HP_index;
	s32 iqk_matwix_wegs_setting_vawue[IQK_MATWIX_SETTINGS_NUM][IQK_MATWIX_WEG_NUM];
	boow bNeedIQK;
	boow bIQKInPwogwess;
	u8 Dewta_IQK;
	u8 Dewta_WCK;
	s8 BBSwingDiff2G; /*  Unit: dB */
	u8 DewtaSwingTabweIdx_2GCCKA_P[DEWTA_SWINGIDX_SIZE];
	u8 DewtaSwingTabweIdx_2GCCKA_N[DEWTA_SWINGIDX_SIZE];
	u8 DewtaSwingTabweIdx_2GCCKB_P[DEWTA_SWINGIDX_SIZE];
	u8 DewtaSwingTabweIdx_2GCCKB_N[DEWTA_SWINGIDX_SIZE];
	u8 DewtaSwingTabweIdx_2GA_P[DEWTA_SWINGIDX_SIZE];
	u8 DewtaSwingTabweIdx_2GA_N[DEWTA_SWINGIDX_SIZE];
	u8 DewtaSwingTabweIdx_2GB_P[DEWTA_SWINGIDX_SIZE];
	u8 DewtaSwingTabweIdx_2GB_N[DEWTA_SWINGIDX_SIZE];
	u8 DewtaSwingTabweIdx_2GA_P_8188E[DEWTA_SWINGIDX_SIZE];
	u8 DewtaSwingTabweIdx_2GA_N_8188E[DEWTA_SWINGIDX_SIZE];

	/*  */

	/* fow IQK */
	u32 WegC04;
	u32 Weg874;
	u32 WegC08;
	u32 WegB68;
	u32 WegB6C;
	u32 Weg870;
	u32 Weg860;
	u32 Weg864;

	boow bIQKInitiawized;
	boow bWCKInPwogwess;
	boow bAntennaDetected;
	u32 ADDA_backup[IQK_ADDA_WEG_NUM];
	u32 IQK_MAC_backup[IQK_MAC_WEG_NUM];
	u32 IQK_BB_backup_wecovew[9];
	u32 IQK_BB_backup[IQK_BB_WEG_NUM];
	u32 TxIQC_8723B[2][3][2]; /*  { {S1: 0xc94, 0xc80, 0xc4c} , {S0: 0xc9c, 0xc88, 0xc4c}} */
	u32 WxIQC_8723B[2][2][2]; /*  { {S1: 0xc14, 0xca0} ,           {S0: 0xc14, 0xca0}} */

	/* fow APK */
	u32 APKoutput[2][2]; /* path A/B; output1_1a/output1_2a */
	u8 bAPKdone;
	u8 bAPKThewmawMetewIgnowe;

	/*  DPK */
	boow bDPKFaiw;
	u8 bDPdone;
	u8 bDPPathAOK;
	u8 bDPPathBOK;

	u32 TxWOK[2];

};
/*  */
/*  ODM Dynamic common info vawue definition */
/*  */

stwuct fat_t { /* _FAST_ANTENNA_TWAINNING_ */
	u8 Bssid[6];
	u8 antsew_wx_keep_0;
	u8 antsew_wx_keep_1;
	u8 antsew_wx_keep_2;
	u8 antsew_wx_keep_3;
	u32 antSumWSSI[7];
	u32 antWSSIcnt[7];
	u32 antAveWSSI[7];
	u8 FAT_State;
	u32 TwainIdx;
	u8 antsew_a[ODM_ASSOCIATE_ENTWY_NUM];
	u8 antsew_b[ODM_ASSOCIATE_ENTWY_NUM];
	u8 antsew_c[ODM_ASSOCIATE_ENTWY_NUM];
	u32 MainAnt_Sum[ODM_ASSOCIATE_ENTWY_NUM];
	u32 AuxAnt_Sum[ODM_ASSOCIATE_ENTWY_NUM];
	u32 MainAnt_Cnt[ODM_ASSOCIATE_ENTWY_NUM];
	u32 AuxAnt_Cnt[ODM_ASSOCIATE_ENTWY_NUM];
	u8 WxIdweAnt;
	boow	bBecomeWinked;
	u32 MinMaxWSSI;
	u8 idx_AntDiv_countew_2G;
	u32 CCK_countew_main;
	u32 CCK_countew_aux;
	u32 OFDM_countew_main;
	u32 OFDM_countew_aux;

	u32 CCK_CtwwFwame_Cnt_main;
	u32 CCK_CtwwFwame_Cnt_aux;
	u32 OFDM_CtwwFwame_Cnt_main;
	u32 OFDM_CtwwFwame_Cnt_aux;
	u32 MainAnt_CtwwFwame_Sum;
	u32 AuxAnt_CtwwFwame_Sum;
	u32 MainAnt_CtwwFwame_Cnt;
	u32 AuxAnt_CtwwFwame_Cnt;

};

enum {
	NO_ANTDIV			= 0xFF,
	CG_TWX_HW_ANTDIV		= 0x01,
	CGCS_WX_HW_ANTDIV	= 0x02,
	FIXED_HW_ANTDIV		= 0x03,
	CG_TWX_SMAWT_ANTDIV	= 0x04,
	CGCS_WX_SW_ANTDIV	= 0x05,
	S0S1_SW_ANTDIV          = 0x06 /* 8723B intwnaw switch S0 S1 */
};

stwuct pathdiv_t { /* _ODM_PATH_DIVEWSITY_ */
	u8 WespTxPath;
	u8 PathSew[ODM_ASSOCIATE_ENTWY_NUM];
	u32 PathA_Sum[ODM_ASSOCIATE_ENTWY_NUM];
	u32 PathB_Sum[ODM_ASSOCIATE_ENTWY_NUM];
	u32 PathA_Cnt[ODM_ASSOCIATE_ENTWY_NUM];
	u32 PathB_Cnt[ODM_ASSOCIATE_ENTWY_NUM];
};

enum phy_weg_pg_type { /* _BASEBAND_CONFIG_PHY_WEG_PG_VAWUE_TYPE */
	PHY_WEG_PG_WEWATIVE_VAWUE = 0,
	PHY_WEG_PG_EXACT_VAWUE = 1
};

/*  */
/*  Antenna detection infowmation fwom singwe tone mechanism, added by Wogew, 2012.11.27. */
/*  */
stwuct ant_detected_info {
	boow bAntDetected;
	u32 dBFowAntA;
	u32 dBFowAntB;
	u32 dBFowAntO;
};

/*  */
/*  2011/09/22 MH Copy fwom SD4 defined stwuctuwe. We use to suppowt PHY DM integwation. */
/*  */
stwuct dm_odm_t { /* DM_Out_Souwce_Dynamic_Mechanism_Stwuctuwe */
	/* stwuct timew_wist	FastAntTwainingTimew; */
	/*  */
	/* 	Add fow diffewent team use tempowawiwy */
	/*  */
	stwuct adaptew *Adaptew;		/*  Fow CE/NIC team */
	/*  WHen you use Adaptew ow pwiv pointew, you must make suwe the pointew is weady. */
	boow odm_weady;

	enum phy_weg_pg_type PhyWegPgVawueType;
	u8 PhyWegPgVewsion;

	u32 NumQwyPhyStatusAww;	/* CCK + OFDM */
	u32 WastNumQwyPhyStatusAww;
	u32 WxPWDBAve;
	boow MPDIG_2G;		/* off MPDIG */
	u8 Times_2G;

/*  ODM HANDWE, DWIVEW NEEDS NOT TO HOOK------ */
	boow bCckHighPowew;
	u8 WFPathWxEnabwe;		/*  ODM_CMNINFO_WFPATH_ENABWE */
	u8 ContwowChannew;
/*  ODM HANDWE, DWIVEW NEEDS NOT TO HOOK------ */

/* WEMOVED COMMON INFO---------- */
	/* u8 		PseudoMacPhyMode; */
	/* boow			*BTCoexist; */
	/* boow			PseudoBtCoexist; */
	/* u8 		OPMode; */
	/* boow			bAPMode; */
	/* boow			bCwientMode; */
	/* boow			bAdHocMode; */
	/* boow			bSwaveOfDMSP; */
/* WEMOVED COMMON INFO---------- */

/* 1  COMMON INFOWMATION */

	/*  */
	/*  Init Vawue */
	/*  */
/* HOOK BEFOWE WEG INIT----------- */
	/*  ODM Pwatfowm info AP/ADSW/CE/MP = 1/2/3/4 */
	u8 SuppowtPwatfowm;
	/*  ODM Suppowt Abiwity DIG/WATW/TX_PWW_TWACK/... = 1/2/3/... */
	u32 SuppowtAbiwity;
	/*  ODM PCIE/USB/SDIO = 1/2/3 */
	u8 SuppowtIntewface;
	/*  ODM composite ow independent. Bit owiented/ 92C+92D+ .... ow any othew type = 1/2/3/... */
	u32 SuppowtICType;
	/*  Cut Vewsion TestChip/A-cut/B-cut... = 0/1/2/3/... */
	u8 CutVewsion;
	/*  Fab Vewsion TSMC/UMC = 0/1 */
	u8 FabVewsion;
	/*  WF Type 4T4W/3T3W/2T2W/1T2W/1T1W/... */
	u8 WFEType;
	/*  Boawd Type Nowmaw/HighPowew/MiniCawd/SWIM/Combo/... = 0/1/2/3/4/... */
	u8 BoawdType;
	u8 PackageType;
	u8 TypeGWNA;
	u8 TypeGPA;
	u8 TypeAWNA;
	u8 TypeAPA;
	/*  with extewnaw WNA  NO/Yes = 0/1 */
	u8 ExtWNA;
	/*  with extewnaw PA  NO/Yes = 0/1 */
	u8 ExtPA;
	/*  with extewnaw TWSW  NO/Yes = 0/1 */
	u8 ExtTWSW;
	u8 PatchID; /* Customew ID */
	boow bInHctTest;
	boow bWIFITest;

	boow bDuawMacSmawtConcuwwent;
	u32 BK_SuppowtAbiwity;
	u8 AntDivType;
/* HOOK BEFOWE WEG INIT----------- */

	/*  */
	/*  Dynamic Vawue */
	/*  */
/*  POINTEW WEFEWENCE----------- */

	u8 u8_temp;
	boow boow_temp;
	stwuct adaptew *adaptew_temp;

	/*  MAC PHY Mode SMSP/DMSP/DMDP = 0/1/2 */
	u8 *pMacPhyMode;
	/* TX Unicast byte count */
	u64 *pNumTxBytesUnicast;
	/* WX Unicast byte count */
	u64 *pNumWxBytesUnicast;
	/*  Wiwewess mode B/G/A/N = BIT0/BIT1/BIT2/BIT3 */
	u8 *pwiwewessmode; /* ODM_WIWEWESS_MODE_E */
	/*  Secondawy channew offset don't_cawe/bewow/above = 0/1/2 */
	u8 *pSecChOffset;
	/*  Secuwity mode Open/WEP/AES/TKIP = 0/1/2/3 */
	u8 *pSecuwity;
	/*  BW info 20M/40M/80M = 0/1/2 */
	u8 *pBandWidth;
	/*  Centwaw channew wocation Ch1/Ch2/.... */
	u8 *pChannew; /* centwaw channew numbew */
	boow DPK_Done;
	/*  Common info fow 92D DMSP */

	boow *pbGetVawueFwomOthewMac;
	stwuct adaptew **pBuddyAdaptew;
	boow *pbMastewOfDMSP; /* MAC0: mastew, MAC1: swave */
	/*  Common info fow Status */
	boow *pbScanInPwocess;
	boow *pbPowewSaving;
	/*  CCA Path 2-path/path-A/path-B = 0/1/2; using ODM_CCA_PATH_E. */
	u8 *pOnePathCCA;
	/* pMgntInfo->AntennaTest */
	u8 *pAntennaTest;
	boow *pbNet_cwosed;
	u8 *mp_mode;
	/* u8 	*pAidMap; */
	u8 *pu1FowcedIgiWb;
/*  Fow 8723B IQK----------- */
	boow *pIs1Antenna;
	u8 *pWFDefauwtPath;
	/*  0:S1, 1:S0 */

/*  POINTEW WEFEWENCE----------- */
	u16 *pFowcedDataWate;
/* CAWW BY VAWUE------------- */
	boow bWinkInPwocess;
	boow bWIFI_Diwect;
	boow bWIFI_Dispway;
	boow bWinked;

	boow bsta_state;
	u8 WSSI_Min;
	u8 IntewfaceIndex; /*  Add fow 92D  duaw MAC: 0--Mac0 1--Mac1 */
	boow bOneEntwyOnwy;
	/*  Common info fow BTDM */
	boow bBtEnabwed;			/*  BT is disabwed */
	boow bBtConnectPwocess;	/*  BT HS is undew connection pwogwess. */
	u8 btHsWssi;				/*  BT HS mode wifi wssi vawue. */
	boow bBtHsOpewation;		/*  BT HS mode is undew pwogwess */
	boow bBtDisabweEdcaTuwbo;	/*  Undew some condition, don't enabwe the EDCA Tuwbo */
	boow bBtWimitedDig;			/*  BT is busy. */
/* CAWW BY VAWUE------------- */
	u8 WSSI_A;
	u8 WSSI_B;
	u64 WSSI_TWSW;
	u64 WSSI_TWSW_H;
	u64 WSSI_TWSW_W;
	u64 WSSI_TWSW_iso;

	u8 WxWate;
	boow bNoisyState;
	u8 TxWate;
	u8 WinkedIntewvaw;
	u8 pweChannew;
	u32 TxagcOffsetVawueA;
	boow IsTxagcOffsetPositiveA;
	u32 TxagcOffsetVawueB;
	boow IsTxagcOffsetPositiveB;
	u64	wastTxOkCnt;
	u64	wastWxOkCnt;
	u32 BbSwingOffsetA;
	boow IsBbSwingOffsetPositiveA;
	u32 BbSwingOffsetB;
	boow IsBbSwingOffsetPositiveB;
	s8 TH_W2H_ini;
	s8 TH_EDCCA_HW_diff;
	s8 IGI_Base;
	u8 IGI_tawget;
	boow FowceEDCCA;
	u8 AdapEn_WSSI;
	s8 Fowce_TH_H;
	s8 Fowce_TH_W;
	u8 IGI_WowewBound;
	u8 antdiv_wssi;
	u8 AntType;
	u8 pwe_AntType;
	u8 antdiv_pewiod;
	u8 antdiv_sewect;
	u8 NdpaPewiod;
	boow H2C_WAWpt_connect;

	/*  add by Yu Cehn fow adaptivtiy */
	boow adaptivity_fwag;
	boow NHM_disabwe;
	boow TxHangFwg;
	boow Cawwiew_Sense_enabwe;
	u8 towewance_cnt;
	u64 NHMCuwTxOkcnt;
	u64 NHMCuwWxOkcnt;
	u64 NHMWastTxOkcnt;
	u64 NHMWastWxOkcnt;
	u8 txEdcca1;
	u8 txEdcca0;
	s8 H2W_wb;
	s8 W2H_wb;
	u8 Adaptivity_IGI_uppew;
	u8 NHM_cnt_0;

	/*  */
	/* 2 Define STA info. */
	/*  _ODM_STA_INFO */
	/*  2012/01/12 MH Fow MP, we need to weduce one awway pointew fow defauwt powt.?? */
	PSTA_INFO_T pODM_StaInfo[ODM_ASSOCIATE_ENTWY_NUM];

	/*  */
	/*  2012/02/14 MH Add to shawe 88E wa with othew SW team. */
	/*  We need to cowewct aww suppowt abiwit to a pwopew awea. */
	/*  */
	boow WaSuppowt88E;

	/*  Define ........... */

	/*  Watest packet phy info (ODM wwite) */
	stwuct odm_phy_dbg_info PhyDbgInfo;
	/* PHY_INFO_88E		PhyInfo; */

	/*  Watest packet phy info (ODM wwite) */
	stwuct odm_mac_status_info *pMacInfo;
	/* MAC_INFO_88E		MacInfo; */

	/*  Diffewent Team independt stwuctuwe?? */

	/*  */
	/* TX_WTP_CMN		TX_wetwpo; */
	/* TX_WTP_88E		TX_wetwpo; */
	/* TX_WTP_8195		TX_wetwpo; */

	/*  */
	/* ODM Stwuctuwe */
	/*  */
	stwuct fat_t DM_FatTabwe;
	stwuct dig_t DM_DigTabwe;
	stwuct ps_t DM_PSTabwe;
	stwuct dynamic_pwimawy_CCA DM_PwiCCA;
	stwuct wxhp_t dM_WXHP_Tabwe;
	stwuct wa_t DM_WA_Tabwe;
	stwuct fawse_AWAWM_STATISTICS FawseAwmCnt;
	stwuct fawse_AWAWM_STATISTICS FwaseAwmCntBuddyAdaptew;
	stwuct swat_t DM_SWAT_Tabwe;
	boow WSSI_test;
	stwuct cfo_twacking DM_CfoTwack;

	stwuct edca_t DM_EDCA_Tabwe;
	u32 WMMEDCA_BE;
	stwuct pathdiv_t DM_PathDiv;
	/*  Copy fwom SD4 stwuctuwe */
	/*  */
	/*  ================================================== */
	/*  */

	/* common */
	/* u8 DM_Type; */
	/* u8    PSD_Wepowt_WXHP[80];    Add By Gawy */
	/* u8    PSD_func_fwag;                Add By Gawy */
	/* fow DIG */
	/* u8 bDMInitiawGainEnabwe; */
	/* u8 binitiawized;  fow dm_initiaw_gain_Muwti_STA use. */
	/* fow Antenna divewsity */
	/* u8 AntDivCfg; 0:OFF , 1:ON, 2:by efuse */
	/* PSTA_INFO_T WSSI_tawget; */

	boow *pbDwivewStopped;
	boow *pbDwivewIsGoingToPnpSetPowewSweep;
	boow *pinit_adpt_in_pwogwess;

	/* PSD */
	boow bUsewAssignWevew;
	stwuct timew_wist PSDTimew;
	u8 WSSI_BT;			/* come fwom BT */
	boow bPSDinPwocess;
	boow bPSDactive;
	boow bDMInitiawGainEnabwe;

	/* MPT DIG */
	stwuct timew_wist MPT_DIGTimew;

	/* fow wate adaptive, in fact,  88c/92c fw wiww handwe this */
	u8 bUseWAMask;

	stwuct odm_wate_adaptive WateAdaptive;

	stwuct ant_detected_info AntDetectedInfo; /*  Antenna detected infowmation fow WSSI toow */

	stwuct odm_wf_caw_t WFCawibwateInfo;

	/*  */
	/*  TX powew twacking */
	/*  */
	u8 BbSwingIdxOfdm[MAX_WF_PATH];
	u8 BbSwingIdxOfdmCuwwent;
	u8 BbSwingIdxOfdmBase[MAX_WF_PATH];
	boow BbSwingFwagOfdm;
	u8 BbSwingIdxCck;
	u8 BbSwingIdxCckCuwwent;
	u8 BbSwingIdxCckBase;
	u8 DefauwtOfdmIndex;
	u8 DefauwtCckIndex;
	boow BbSwingFwagCck;

	s8 Absowute_OFDMSwingIdx[MAX_WF_PATH];
	s8 Wemnant_OFDMSwingIdx[MAX_WF_PATH];
	s8 Wemnant_CCKSwingIdx;
	s8 Modify_TxAGC_Vawue;       /* Wemnat compensate vawue at TxAGC */
	boow Modify_TxAGC_Fwag_PathA;
	boow Modify_TxAGC_Fwag_PathB;
	boow Modify_TxAGC_Fwag_PathC;
	boow Modify_TxAGC_Fwag_PathD;
	boow Modify_TxAGC_Fwag_PathA_CCK;

	s8 KfweeOffset[MAX_WF_PATH];
	/*  */
	/*  ODM system wesouwce. */
	/*  */

	/*  ODM wewative time. */
	stwuct timew_wist PathDivSwitchTimew;
	/* 2011.09.27 add fow Path Divewsity */
	stwuct timew_wist CCKPathDivewsityTimew;
	stwuct timew_wist FastAntTwainingTimew;

	/*  ODM wewative wowkitem. */

	#if (BEAMFOWMING_SUPPOWT == 1)
	WT_BEAMFOWMING_INFO BeamfowmingInfo;
	#endif
};

 enum odm_wf_content {
	odm_wadioa_txt = 0x1000,
	odm_wadiob_txt = 0x1001,
	odm_wadioc_txt = 0x1002,
	odm_wadiod_txt = 0x1003
};

enum ODM_BB_Config_Type {
	CONFIG_BB_PHY_WEG,
	CONFIG_BB_AGC_TAB,
	CONFIG_BB_AGC_TAB_2G,
	CONFIG_BB_PHY_WEG_PG,
	CONFIG_BB_PHY_WEG_MP,
	CONFIG_BB_AGC_TAB_DIFF,
};

enum ODM_WF_Config_Type {
	CONFIG_WF_WADIO,
	CONFIG_WF_TXPWW_WMT,
};

enum ODM_FW_Config_Type {
	CONFIG_FW_NIC,
	CONFIG_FW_NIC_2,
	CONFIG_FW_AP,
	CONFIG_FW_WoWWAN,
	CONFIG_FW_WoWWAN_2,
	CONFIG_FW_AP_WoWWAN,
	CONFIG_FW_BT,
};

#ifdef WEMOVE_PACK
#pwagma pack()
#endif

/* incwude "odm_function.h" */

/* 3 =========================================================== */
/* 3 DIG */
/* 3 =========================================================== */

/* Wemove DIG by Yuchen */

/* 3 =========================================================== */
/* 3 AGC WX High Powew Mode */
/* 3 =========================================================== */
#define          WNA_Wow_Gain_1                      0x64
#define          WNA_Wow_Gain_2                      0x5A
#define          WNA_Wow_Gain_3                      0x58

#define          FA_WXHP_TH1                           5000
#define          FA_WXHP_TH2                           1500
#define          FA_WXHP_TH3                             800
#define          FA_WXHP_TH4                             600
#define          FA_WXHP_TH5                             500

/* 3 =========================================================== */
/* 3 EDCA */
/* 3 =========================================================== */

/* 3 =========================================================== */
/* 3 Dynamic Tx Powew */
/* 3 =========================================================== */
/* Dynamic Tx Powew Contwow Thweshowd */

/* 3 =========================================================== */
/* 3 Wate Adaptive */
/* 3 =========================================================== */
#define		DM_WATW_STA_INIT			0
#define		DM_WATW_STA_HIGH			1
#define		DM_WATW_STA_MIDDWE			2
#define		DM_WATW_STA_WOW				3

/* 3 =========================================================== */
/* 3 BB Powew Save */
/* 3 =========================================================== */

enum { /* tag_1W_CCA_Type_Definition */
	CCA_1W = 0,
	CCA_2W = 1,
	CCA_MAX = 2,
};

enum { /* tag_WF_Type_Definition */
	WF_Save = 0,
	WF_Nowmaw = 1,
	WF_MAX = 2,
};

/*  Maximaw numbew of antenna detection mechanism needs to pewfowm, added by Wogew, 2011.12.28. */
#define	MAX_ANTENNA_DETECTION_CNT	10

/*  */
/*  Extewn Gwobaw Vawiabwes. */
/*  */
extewn	u32 OFDMSwingTabwe[OFDM_TABWE_SIZE];
extewn	u8 CCKSwingTabwe_Ch1_Ch13[CCK_TABWE_SIZE][8];
extewn	u8 CCKSwingTabwe_Ch14[CCK_TABWE_SIZE][8];

extewn	u32 OFDMSwingTabwe_New[OFDM_TABWE_SIZE];
extewn	u8 CCKSwingTabwe_Ch1_Ch13_New[CCK_TABWE_SIZE][8];
extewn	u8 CCKSwingTabwe_Ch14_New[CCK_TABWE_SIZE][8];

extewn  u32 TxScawingTabwe_Jaguaw[TXSCAWE_TABWE_SIZE];

/*  */
/*  check Sta pointew vawid ow not */
/*  */
#define IS_STA_VAWID(pSta)		(pSta)
/*  20100514 Joseph: Add definition fow antenna switching test aftew wink. */
/*  This indicates two diffewent the steps. */
/*  In SWAW_STEP_PEAK, dwivew needs to switch antenna and wisten to the signaw on the aiw. */
/*  In SWAW_STEP_DETEWMINE, dwivew just compawes the signaw captuwed in SWAW_STEP_PEAK */
/*  with owiginaw WSSI to detewmine if it is necessawy to switch antenna. */
#define SWAW_STEP_PEAK		0
#define SWAW_STEP_DETEWMINE	1

/* Wemove BB powew saving by Yuchen */

#define dm_CheckTXPowewTwacking ODM_TXPowewTwackingCheck
void ODM_TXPowewTwackingCheck(stwuct dm_odm_t *pDM_Odm);

boow ODM_WAStateCheck(
	stwuct dm_odm_t *pDM_Odm,
	s32	WSSI,
	boow bFowceUpdate,
	u8 *pWATWState
);

#define dm_SWAW_WSSI_Check	ODM_SwAntDivChkPewPktWssi
void ODM_SwAntDivChkPewPktWssi(
	stwuct dm_odm_t *pDM_Odm,
	u8 StationID,
	stwuct odm_phy_info *pPhyInfo
);

u32 ODM_Get_Wate_Bitmap(
	stwuct dm_odm_t *pDM_Odm,
	u32 macid,
	u32 wa_mask,
	u8 wssi_wevew
);

#if (BEAMFOWMING_SUPPOWT == 1)
BEAMFOWMING_CAP Beamfowming_GetEntwyBeamCapByMacId(PMGNT_INFO pMgntInfo, u8 MacId);
#endif

void odm_TXPowewTwackingInit(stwuct dm_odm_t *pDM_Odm);

void ODM_DMInit(stwuct dm_odm_t *pDM_Odm);

void ODM_DMWatchdog(stwuct dm_odm_t *pDM_Odm); /*  Fow common use in the futuwe */

void ODM_CmnInfoInit(stwuct dm_odm_t *pDM_Odm, enum odm_cmninfo_e CmnInfo, u32 Vawue);

void ODM_CmnInfoHook(stwuct dm_odm_t *pDM_Odm, enum odm_cmninfo_e CmnInfo, void *pVawue);

void ODM_CmnInfoPtwAwwayHook(
	stwuct dm_odm_t *pDM_Odm,
	enum odm_cmninfo_e CmnInfo,
	u16 Index,
	void *pVawue
);

void ODM_CmnInfoUpdate(stwuct dm_odm_t *pDM_Odm, u32 CmnInfo, u64 Vawue);

void ODM_InitAwwTimews(stwuct dm_odm_t *pDM_Odm);

void ODM_CancewAwwTimews(stwuct dm_odm_t *pDM_Odm);

void ODM_WeweaseAwwTimews(stwuct dm_odm_t *pDM_Odm);

void ODM_AntsewStatistics_88C(
	stwuct dm_odm_t *pDM_Odm,
	u8 MacId,
	u32 PWDBAww,
	boow isCCKwate
);

void ODM_DynamicAWFBSewect(stwuct dm_odm_t *pDM_Odm, u8 wate, boow Cowwision_State);

#endif
