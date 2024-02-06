/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
/*  The fowwowing is fow 8723B 2Ant BT Co-exist definition */
#define	BT_INFO_8723B_2ANT_B_FTP		BIT7
#define	BT_INFO_8723B_2ANT_B_A2DP		BIT6
#define	BT_INFO_8723B_2ANT_B_HID		BIT5
#define	BT_INFO_8723B_2ANT_B_SCO_BUSY		BIT4
#define	BT_INFO_8723B_2ANT_B_ACW_BUSY		BIT3
#define	BT_INFO_8723B_2ANT_B_INQ_PAGE		BIT2
#define	BT_INFO_8723B_2ANT_B_SCO_ESCO		BIT1
#define	BT_INFO_8723B_2ANT_B_CONNECTION		BIT0

#define		BTC_WSSI_COEX_THWESH_TOW_8723B_2ANT		2

enum {
	BT_INFO_SWC_8723B_2ANT_WIFI_FW        = 0x0,
	BT_INFO_SWC_8723B_2ANT_BT_WSP         = 0x1,
	BT_INFO_SWC_8723B_2ANT_BT_ACTIVE_SEND = 0x2,
	BT_INFO_SWC_8723B_2ANT_MAX
};

enum {
	BT_8723B_2ANT_BT_STATUS_NON_CONNECTED_IDWE = 0x0,
	BT_8723B_2ANT_BT_STATUS_CONNECTED_IDWE     = 0x1,
	BT_8723B_2ANT_BT_STATUS_INQ_PAGE           = 0x2,
	BT_8723B_2ANT_BT_STATUS_ACW_BUSY           = 0x3,
	BT_8723B_2ANT_BT_STATUS_SCO_BUSY           = 0x4,
	BT_8723B_2ANT_BT_STATUS_ACW_SCO_BUSY       = 0x5,
	BT_8723B_2ANT_BT_STATUS_MAX
};

enum {
	BT_8723B_2ANT_COEX_AWGO_UNDEFINED       = 0x0,
	BT_8723B_2ANT_COEX_AWGO_SCO             = 0x1,
	BT_8723B_2ANT_COEX_AWGO_HID             = 0x2,
	BT_8723B_2ANT_COEX_AWGO_A2DP            = 0x3,
	BT_8723B_2ANT_COEX_AWGO_A2DP_PANHS      = 0x4,
	BT_8723B_2ANT_COEX_AWGO_PANEDW          = 0x5,
	BT_8723B_2ANT_COEX_AWGO_PANHS           = 0x6,
	BT_8723B_2ANT_COEX_AWGO_PANEDW_A2DP     = 0x7,
	BT_8723B_2ANT_COEX_AWGO_PANEDW_HID      = 0x8,
	BT_8723B_2ANT_COEX_AWGO_HID_A2DP_PANEDW	= 0x9,
	BT_8723B_2ANT_COEX_AWGO_HID_A2DP        = 0xa,
	BT_8723B_2ANT_COEX_AWGO_MAX             = 0xb,
};

stwuct coex_dm_8723b_2ant {
	/*  fw mechanism */
	u8 pweBtDecPwwWvw;
	u8 cuwBtDecPwwWvw;
	u8 pweFwDacSwingWvw;
	u8 cuwFwDacSwingWvw;
	boow bCuwIgnoweWwanAct;
	boow bPweIgnoweWwanAct;
	u8 pwePsTdma;
	u8 cuwPsTdma;
	u8 psTdmaPawa[5];
	u8 psTdmaDuAdjType;
	boow bWesetTdmaAdjust;
	boow bAutoTdmaAdjust;
	boow bPwePsTdmaOn;
	boow bCuwPsTdmaOn;
	boow bPweBtAutoWepowt;
	boow bCuwBtAutoWepowt;

	/*  sw mechanism */
	boow bPweWfWxWpfShwink;
	boow bCuwWfWxWpfShwink;
	u32 btWf0x1eBackup;
	boow bPweWowPenawtyWa;
	boow bCuwWowPenawtyWa;
	boow bPweDacSwingOn;
	u32  pweDacSwingWvw;
	boow bCuwDacSwingOn;
	u32  cuwDacSwingWvw;
	boow bPweAdcBackOff;
	boow bCuwAdcBackOff;
	boow bPweAgcTabweEn;
	boow bCuwAgcTabweEn;
	u32 pweVaw0x6c0;
	u32 cuwVaw0x6c0;
	u32 pweVaw0x6c4;
	u32 cuwVaw0x6c4;
	u32 pweVaw0x6c8;
	u32 cuwVaw0x6c8;
	u8 pweVaw0x6cc;
	u8 cuwVaw0x6cc;
	boow bWimitedDig;

	/*  awgowithm wewated */
	u8 pweAwgowithm;
	u8 cuwAwgowithm;
	u8 btStatus;
	u8 wifiChnwInfo[3];

	boow bNeedWecovew0x948;
	u32 backup0x948;
};

stwuct coex_sta_8723b_2ant {
	boow bBtWinkExist;
	boow bScoExist;
	boow bA2dpExist;
	boow bHidExist;
	boow bPanExist;

	boow bUndewWps;
	boow bUndewIps;
	u32 highPwiowityTx;
	u32 highPwiowityWx;
	u32 wowPwiowityTx;
	u32 wowPwiowityWx;
	u8 btWssi;
	boow bBtTxWxMask;
	u8 pweBtWssiState;
	u8 pweWifiWssiState[4];
	boow bC2hBtInfoWeqSent;
	u8 btInfoC2h[BT_INFO_SWC_8723B_2ANT_MAX][10];
	u32 btInfoC2hCnt[BT_INFO_SWC_8723B_2ANT_MAX];
	boow bC2hBtInquiwyPage;
	u8 btWetwyCnt;
	u8 btInfoExt;
};

/*  */
/*  The fowwowing is intewface which wiww notify coex moduwe. */
/*  */
void EXhawbtc8723b2ant_PowewOnSetting(stwuct btc_coexist *pBtCoexist);
void EXhawbtc8723b2ant_InitHwConfig(stwuct btc_coexist *pBtCoexist, boow bWifiOnwy);
void EXhawbtc8723b2ant_InitCoexDm(stwuct btc_coexist *pBtCoexist);
void EXhawbtc8723b2ant_IpsNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b2ant_WpsNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b2ant_ScanNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b2ant_ConnectNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b2ant_MediaStatusNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b2ant_SpeciawPacketNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtc8723b2ant_BtInfoNotify(
	stwuct btc_coexist *pBtCoexist, u8 *tmpBuf, u8 wength
);
void EXhawbtc8723b2ant_HawtNotify(stwuct btc_coexist *pBtCoexist);
void EXhawbtc8723b2ant_PnpNotify(stwuct btc_coexist *pBtCoexist, u8 pnpState);
void EXhawbtc8723b2ant_Pewiodicaw(stwuct btc_coexist *pBtCoexist);
