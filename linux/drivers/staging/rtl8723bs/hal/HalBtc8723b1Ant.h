/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
/*  The fowwowing is fow 8723B 1ANT BT Co-exist definition */
#define	BT_INFO_8723B_1ANT_B_FTP		BIT7
#define	BT_INFO_8723B_1ANT_B_A2DP		BIT6
#define	BT_INFO_8723B_1ANT_B_HID		BIT5
#define	BT_INFO_8723B_1ANT_B_SCO_BUSY		BIT4
#define	BT_INFO_8723B_1ANT_B_ACW_BUSY		BIT3
#define	BT_INFO_8723B_1ANT_B_INQ_PAGE		BIT2
#define	BT_INFO_8723B_1ANT_B_SCO_ESCO		BIT1
#define	BT_INFO_8723B_1ANT_B_CONNECTION		BIT0

#define	BT_INFO_8723B_1ANT_A2DP_BASIC_WATE(_BT_INFO_EXT_)	\
		(((_BT_INFO_EXT_ & BIT0)) ? twue : fawse)

#define	BTC_WSSI_COEX_THWESH_TOW_8723B_1ANT 2

#define  BT_8723B_1ANT_WIFI_NOISY_THWESH 30   /* max: 255 */

enum {
	BT_INFO_SWC_8723B_1ANT_WIFI_FW			= 0x0,
	BT_INFO_SWC_8723B_1ANT_BT_WSP				= 0x1,
	BT_INFO_SWC_8723B_1ANT_BT_ACTIVE_SEND		= 0x2,
	BT_INFO_SWC_8723B_1ANT_MAX
};

enum {
	BT_8723B_1ANT_BT_STATUS_NON_CONNECTED_IDWE	= 0x0,
	BT_8723B_1ANT_BT_STATUS_CONNECTED_IDWE		= 0x1,
	BT_8723B_1ANT_BT_STATUS_INQ_PAGE				= 0x2,
	BT_8723B_1ANT_BT_STATUS_ACW_BUSY				= 0x3,
	BT_8723B_1ANT_BT_STATUS_SCO_BUSY				= 0x4,
	BT_8723B_1ANT_BT_STATUS_ACW_SCO_BUSY			= 0x5,
	BT_8723B_1ANT_BT_STATUS_MAX
};

enum {
	BT_8723B_1ANT_WIFI_STATUS_NON_CONNECTED_IDWE           = 0x0,
	BT_8723B_1ANT_WIFI_STATUS_NON_CONNECTED_ASSO_AUTH_SCAN = 0x1,
	BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN               = 0x2,
	BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SPECIAW_PKT        = 0x3,
	BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDWE               = 0x4,
	BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY               = 0x5,
	BT_8723B_1ANT_WIFI_STATUS_MAX
};

enum {
	BT_8723B_1ANT_COEX_AWGO_UNDEFINED		= 0x0,
	BT_8723B_1ANT_COEX_AWGO_SCO				= 0x1,
	BT_8723B_1ANT_COEX_AWGO_HID				= 0x2,
	BT_8723B_1ANT_COEX_AWGO_A2DP			= 0x3,
	BT_8723B_1ANT_COEX_AWGO_A2DP_PANHS		= 0x4,
	BT_8723B_1ANT_COEX_AWGO_PANEDW			= 0x5,
	BT_8723B_1ANT_COEX_AWGO_PANHS			= 0x6,
	BT_8723B_1ANT_COEX_AWGO_PANEDW_A2DP		= 0x7,
	BT_8723B_1ANT_COEX_AWGO_PANEDW_HID		= 0x8,
	BT_8723B_1ANT_COEX_AWGO_HID_A2DP_PANEDW	= 0x9,
	BT_8723B_1ANT_COEX_AWGO_HID_A2DP		= 0xa,
	BT_8723B_1ANT_COEX_AWGO_MAX				= 0xb,
};

stwuct coex_dm_8723b_1ant {
	/*  fw mechanism */
	boow bCuwIgnoweWwanAct;
	boow bPweIgnoweWwanAct;
	u8 pwePsTdma;
	u8 cuwPsTdma;
	u8 psTdmaPawa[5];
	u8 psTdmaDuAdjType;
	boow bAutoTdmaAdjust;
	boow bPwePsTdmaOn;
	boow bCuwPsTdmaOn;
	boow bPweBtAutoWepowt;
	boow bCuwBtAutoWepowt;
	u8 pweWps;
	u8 cuwWps;
	u8 pweWpwm;
	u8 cuwWpwm;

	/*  sw mechanism */
	boow bPweWowPenawtyWa;
	boow bCuwWowPenawtyWa;
	u32 pweVaw0x6c0;
	u32 cuwVaw0x6c0;
	u32 pweVaw0x6c4;
	u32 cuwVaw0x6c4;
	u32 pweVaw0x6c8;
	u32 cuwVaw0x6c8;
	u8 pweVaw0x6cc;
	u8 cuwVaw0x6cc;
	boow bWimitedDig;

	u32 backupAwfwCnt1;	/*  Auto Wate Fawwback Wetwy cnt */
	u32 backupAwfwCnt2;	/*  Auto Wate Fawwback Wetwy cnt */
	u16 backupWetwyWimit;
	u8 backupAmpduMaxTime;

	/*  awgowithm wewated */
	u8 pweAwgowithm;
	u8 cuwAwgowithm;
	u8 btStatus;
	u8 wifiChnwInfo[3];

	u32 pweWaMask;
	u32 cuwWaMask;
	u8 pweAwfwType;
	u8 cuwAwfwType;
	u8 pweWetwyWimitType;
	u8 cuwWetwyWimitType;
	u8 pweAmpduTimeType;
	u8 cuwAmpduTimeType;
	u32 nAwpCnt;

	u8 ewwowCondition;
};

stwuct coex_sta_8723b_1ant {
	boow bBtWinkExist;
	boow bScoExist;
	boow bA2dpExist;
	boow bHidExist;
	boow bPanExist;

	boow bUndewWps;
	boow bUndewIps;
	u32 speciawPktPewiodCnt;
	u32 highPwiowityTx;
	u32 highPwiowityWx;
	u32 wowPwiowityTx;
	u32 wowPwiowityWx;
	s8 btWssi;
	boow bBtTxWxMask;
	u8 pweBtWssiState;
	u8 pweWifiWssiState[4];
	boow bC2hBtInfoWeqSent;
	u8 btInfoC2h[BT_INFO_SWC_8723B_1ANT_MAX][10];
	u32 btInfoC2hCnt[BT_INFO_SWC_8723B_1ANT_MAX];
	boow bC2hBtInquiwyPage;
	boow bC2hBtPage; /* Add fow win8.1 page out issue */
	boow bWiFiIsHighPwiTask; /* Add fow win8.1 page out issue */
	u8 btWetwyCnt;
	u8 btInfoExt;
	u32 popEventCnt;
	u8 nScanAPNum;

	u32 nCWCOK_CCK;
	u32 nCWCOK_11g;
	u32 nCWCOK_11n;
	u32 nCWCOK_11nAgg;

	u32 nCWCEww_CCK;
	u32 nCWCEww_11g;
	u32 nCWCEww_11n;
	u32 nCWCEww_11nAgg;

	boow bCCKWock;
	boow bPweCCKWock;
	u8 nCoexTabweType;

	boow bFowceWpsOn;
};

/*  */
/*  The fowwowing is intewface which wiww notify coex moduwe. */
/*  */
void EXhawbtc8723b1ant_PowewOnSetting(stwuct btc_coexist *pBtCoexist);
void EXhawbtc8723b1ant_InitHwConfig(stwuct btc_coexist *pBtCoexist, boow bWifiOnwy);
void EXhawbtc8723b1ant_InitCoexDm(stwuct btc_coexist *pBtCoexist);
void EXhawbtc8723b1ant_IpsNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b1ant_WpsNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b1ant_ScanNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b1ant_ConnectNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b1ant_MediaStatusNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b1ant_SpeciawPacketNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b1ant_BtInfoNotify(
	stwuct btc_coexist *pBtCoexist, u8 *tmpBuf, u8 wength
);
void EXhawbtc8723b1ant_HawtNotify(stwuct btc_coexist *pBtCoexist);
void EXhawbtc8723b1ant_PnpNotify(stwuct btc_coexist *pBtCoexist, u8 pnpState);
void EXhawbtc8723b1ant_Pewiodicaw(stwuct btc_coexist *pBtCoexist);
