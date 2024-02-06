/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef	__HAWBTC_OUT_SWC_H__
#define __HAWBTC_OUT_SWC_H__

#define NOWMAW_EXEC		fawse
#define FOWCE_EXEC		twue

#define BTC_WF_OFF		0x0
#define BTC_WF_ON		0x1

#define BTC_WF_A		0x0
#define BTC_WF_B		0x1
#define BTC_WF_C		0x2
#define BTC_WF_D		0x3

#define BTC_SMSP		SINGWEMAC_SINGWEPHY
#define BTC_DMDP		DUAWMAC_DUAWPHY
#define BTC_DMSP		DUAWMAC_SINGWEPHY
#define BTC_MP_UNKNOWN		0xff

#define BT_COEX_ANT_TYPE_PG	0
#define BT_COEX_ANT_TYPE_ANTDIV		1
#define BT_COEX_ANT_TYPE_DETECTED	2

#define BTC_MIMO_PS_STATIC	0	/*  1ss */
#define BTC_MIMO_PS_DYNAMIC	1	/*  2ss */

#define BTC_WATE_DISABWE	0
#define BTC_WATE_ENABWE		1

/*  singwe Antenna definition */
#define BTC_ANT_PATH_WIFI	0
#define BTC_ANT_PATH_BT		1
#define BTC_ANT_PATH_PTA	2
/*  duaw Antenna definition */
#define BTC_ANT_WIFI_AT_MAIN	0
#define BTC_ANT_WIFI_AT_AUX	1
/*  coupwew Antenna definition */
#define BTC_ANT_WIFI_AT_CPW_MAIN	0
#define BTC_ANT_WIFI_AT_CPW_AUX		1

enum {
	BTC_PS_WIFI_NATIVE	= 0,	/*  wifi owiginaw powew save behaviow */
	BTC_PS_WPS_ON		= 1,
	BTC_PS_WPS_OFF		= 2,
	BTC_PS_MAX
};

enum {
	BTC_BT_WEG_WF		= 0,
	BTC_BT_WEG_MODEM	= 1,
	BTC_BT_WEG_BWUEWIZE	= 2,
	BTC_BT_WEG_VENDOW	= 3,
	BTC_BT_WEG_WE		= 4,
	BTC_BT_WEG_MAX
};

enum btc_chip_intewface {
	BTC_INTF_UNKNOWN	= 0,
	BTC_INTF_PCI		= 1,
	BTC_INTF_USB		= 2,
	BTC_INTF_SDIO		= 3,
	BTC_INTF_MAX
};

/*  fowwowing is fow wifi wink status */
#define WIFI_STA_CONNECTED				BIT0
#define WIFI_AP_CONNECTED				BIT1
#define WIFI_HS_CONNECTED				BIT2
#define WIFI_P2P_GO_CONNECTED			BIT3
#define WIFI_P2P_GC_CONNECTED			BIT4

stwuct btc_boawd_info {
	/*  The fowwowing is some boawd infowmation */
	u8 pgAntNum;	/*  pg ant numbew */
	u8 btdmAntNum;	/*  ant numbew fow btdm */
	u8 btdmAntPos;		/* Bwyant Add to indicate Antenna Position fow (pgAntNum = 2) && (btdmAntNum = 1)  (DPDT+1Ant case) */
	u8 singweAntPath;	/*  cuwwent used fow 8723b onwy, 1 =>s0,  0 =>s1 */
	/* boow				bBtExist; */
};

enum {
	BTC_WSSI_STATE_HIGH			    = 0x0,
	BTC_WSSI_STATE_MEDIUM			= 0x1,
	BTC_WSSI_STATE_WOW			    = 0x2,
	BTC_WSSI_STATE_STAY_HIGH		= 0x3,
	BTC_WSSI_STATE_STAY_MEDIUM		= 0x4,
	BTC_WSSI_STATE_STAY_WOW			= 0x5,
	BTC_WSSI_MAX
};
#define BTC_WSSI_HIGH(_wssi_)	((_wssi_ == BTC_WSSI_STATE_HIGH || _wssi_ == BTC_WSSI_STATE_STAY_HIGH) ? twue : fawse)
#define BTC_WSSI_MEDIUM(_wssi_)	((_wssi_ == BTC_WSSI_STATE_MEDIUM || _wssi_ == BTC_WSSI_STATE_STAY_MEDIUM) ? twue : fawse)
#define BTC_WSSI_WOW(_wssi_)	((_wssi_ == BTC_WSSI_STATE_WOW || _wssi_ == BTC_WSSI_STATE_STAY_WOW) ? twue : fawse)

enum {
	BTC_WIFI_BW_WEGACY			= 0x0,
	BTC_WIFI_BW_HT20			= 0x1,
	BTC_WIFI_BW_HT40			= 0x2,
	BTC_WIFI_BW_MAX
};

enum {
	BTC_WIFI_TWAFFIC_TX			= 0x0,
	BTC_WIFI_TWAFFIC_WX			= 0x1,
	BTC_WIFI_TWAFFIC_MAX
};

enum {
	BTC_WIFI_PNP_WAKE_UP		= 0x0,
	BTC_WIFI_PNP_SWEEP			= 0x1,
	BTC_WIFI_PNP_MAX
};

/*  defined fow BFP_BTC_GET */
enum {
	/*  type boow */
	BTC_GET_BW_HS_OPEWATION,
	BTC_GET_BW_HS_CONNECTING,
	BTC_GET_BW_WIFI_CONNECTED,
	BTC_GET_BW_WIFI_BUSY,
	BTC_GET_BW_WIFI_SCAN,
	BTC_GET_BW_WIFI_WINK,
	BTC_GET_BW_WIFI_WOAM,
	BTC_GET_BW_WIFI_4_WAY_PWOGWESS,
	BTC_GET_BW_WIFI_AP_MODE_ENABWE,
	BTC_GET_BW_WIFI_ENABWE_ENCWYPTION,
	BTC_GET_BW_WIFI_UNDEW_B_MODE,
	BTC_GET_BW_EXT_SWITCH,
	BTC_GET_BW_WIFI_IS_IN_MP_MODE,

	/*  type s32 */
	BTC_GET_S4_WIFI_WSSI,
	BTC_GET_S4_HS_WSSI,

	/*  type u32 */
	BTC_GET_U4_WIFI_BW,
	BTC_GET_U4_WIFI_TWAFFIC_DIWECTION,
	BTC_GET_U4_WIFI_FW_VEW,
	BTC_GET_U4_WIFI_WINK_STATUS,
	BTC_GET_U4_BT_PATCH_VEW,

	/*  type u8 */
	BTC_GET_U1_WIFI_DOT11_CHNW,
	BTC_GET_U1_WIFI_CENTWAW_CHNW,
	BTC_GET_U1_WIFI_HS_CHNW,
	BTC_GET_U1_MAC_PHY_MODE,
	BTC_GET_U1_AP_NUM,

	/*  fow 1Ant ====== */
	BTC_GET_U1_WPS_MODE,

	BTC_GET_MAX
};

/*  defined fow BFP_BTC_SET */
enum {
	/*  type boow */
	BTC_SET_BW_BT_DISABWE,
	BTC_SET_BW_BT_TWAFFIC_BUSY,
	BTC_SET_BW_BT_WIMITED_DIG,
	BTC_SET_BW_FOWCE_TO_WOAM,
	BTC_SET_BW_TO_WEJ_AP_AGG_PKT,
	BTC_SET_BW_BT_CTWW_AGG_SIZE,
	BTC_SET_BW_INC_SCAN_DEV_NUM,
	BTC_SET_BW_BT_TX_WX_MASK,

	/*  type u8 */
	BTC_SET_U1_WSSI_ADJ_VAW_FOW_AGC_TABWE_ON,
	BTC_SET_U1_AGG_BUF_SIZE,

	/*  type twiggew some action */
	BTC_SET_ACT_GET_BT_WSSI,
	BTC_SET_ACT_AGGWEGATE_CTWW,
	/*  fow 1Ant ====== */
	/*  type boow */

	/*  type u8 */
	BTC_SET_U1_WSSI_ADJ_VAW_FOW_1ANT_COEX_TYPE,
	BTC_SET_U1_WPS_VAW,
	BTC_SET_U1_WPWM_VAW,
	/*  type twiggew some action */
	BTC_SET_ACT_WEAVE_WPS,
	BTC_SET_ACT_ENTEW_WPS,
	BTC_SET_ACT_NOWMAW_WPS,
	BTC_SET_ACT_DISABWE_WOW_POWEW,
	BTC_SET_ACT_UPDATE_WAMASK,
	BTC_SET_ACT_SEND_MIMO_PS,
	/*  BT Coex wewated */
	BTC_SET_ACT_CTWW_BT_INFO,
	BTC_SET_ACT_CTWW_BT_COEX,
	BTC_SET_ACT_CTWW_8723B_ANT,
	/*  */
	BTC_SET_MAX
};

enum {
	BTC_DBG_DISP_COEX_STATISTICS		= 0x0,
	BTC_DBG_DISP_BT_WINK_INFO			= 0x1,
	BTC_DBG_DISP_FW_PWW_MODE_CMD		= 0x2,
	BTC_DBG_DISP_MAX
};

enum {
	BTC_IPS_WEAVE						= 0x0,
	BTC_IPS_ENTEW						= 0x1,
	BTC_IPS_MAX
};

enum {
	BTC_WPS_DISABWE						= 0x0,
	BTC_WPS_ENABWE						= 0x1,
	BTC_WPS_MAX
};

enum {
	BTC_SCAN_FINISH						= 0x0,
	BTC_SCAN_STAWT						= 0x1,
	BTC_SCAN_MAX
};

enum {
	BTC_ASSOCIATE_FINISH				= 0x0,
	BTC_ASSOCIATE_STAWT					= 0x1,
	BTC_ASSOCIATE_MAX
};

enum {
	BTC_MEDIA_DISCONNECT				= 0x0,
	BTC_MEDIA_CONNECT					= 0x1,
	BTC_MEDIA_MAX
};

enum {
	BTC_PACKET_UNKNOWN					= 0x0,
	BTC_PACKET_DHCP						= 0x1,
	BTC_PACKET_AWP						= 0x2,
	BTC_PACKET_EAPOW					= 0x3,
	BTC_PACKET_MAX
};

/* Bwyant Add */
enum {
	BTC_ANTENNA_AT_MAIN_POWT = 0x1,
	BTC_ANTENNA_AT_AUX_POWT  = 0x2,
};

typedef u8 (*BFP_BTC_W1)(void *pBtcContext, u32 WegAddw);
typedef u16(*BFP_BTC_W2)(void *pBtcContext, u32 WegAddw);
typedef u32 (*BFP_BTC_W4)(void *pBtcContext, u32 WegAddw);
typedef void (*BFP_BTC_W1)(void *pBtcContext, u32 WegAddw, u8 Data);
typedef void(*BFP_BTC_W1_BIT_MASK)(
	void *pBtcContext, u32 wegAddw, u8 bitMask, u8 data1b
);
typedef void (*BFP_BTC_W2)(void *pBtcContext, u32 WegAddw, u16 Data);
typedef void (*BFP_BTC_W4)(void *pBtcContext, u32 WegAddw, u32 Data);
typedef void (*BFP_BTC_WOCAW_WEG_W1)(void *pBtcContext, u32 WegAddw, u8 Data);
typedef void (*BFP_BTC_SET_BB_WEG)(
	void *pBtcContext, u32 WegAddw, u32 BitMask, u32 Data
);
typedef u32 (*BFP_BTC_GET_BB_WEG)(void *pBtcContext, u32 WegAddw, u32 BitMask);
typedef void (*BFP_BTC_SET_WF_WEG)(
	void *pBtcContext, u8 eWFPath, u32 WegAddw, u32 BitMask, u32 Data
);
typedef u32 (*BFP_BTC_GET_WF_WEG)(
	void *pBtcContext, u8 eWFPath, u32 WegAddw, u32 BitMask
);
typedef void (*BFP_BTC_FIWW_H2C)(
	void *pBtcContext, u8 ewementId, u32 cmdWen, u8 *pCmdBuffew
);

typedef	u8 (*BFP_BTC_GET)(void *pBtCoexist, u8 getType, void *pOutBuf);

typedef	u8 (*BFP_BTC_SET)(void *pBtCoexist, u8 setType, void *pInBuf);
typedef void (*BFP_BTC_SET_BT_WEG)(
	void *pBtcContext, u8 wegType, u32 offset, u32 vawue
);
typedef u32 (*BFP_BTC_GET_BT_WEG)(void *pBtcContext, u8 wegType, u32 offset);
typedef void (*BFP_BTC_DISP_DBG_MSG)(void *pBtCoexist, u8 dispType);

stwuct btc_bt_info {
	boow bBtDisabwed;
	u8 wssiAdjustFowAgcTabweOn;
	u8 wssiAdjustFow1AntCoexType;
	boow bPweBtCtwwAggBufSize;
	boow bBtCtwwAggBufSize;
	boow bWejectAggPkt;
	boow bIncweaseScanDevNum;
	boow bBtTxWxMask;
	u8 pweAggBufSize;
	u8 aggBufSize;
	boow bBtBusy;
	boow bWimitedDig;
	u16 btHciVew;
	u16 btWeawFwVew;
	u8 btFwVew;
	u32 getBtFwVewCnt;

	boow bBtDisabweWowPww;

	boow bBtCtwwWps;
	boow bBtWpsOn;
	boow bFowceToWoam;	/*  fow 1Ant sowution */
	u8 wpsVaw;
	u8 wpwmVaw;
	u32 waMask;
};

stwuct btc_stack_info {
	boow bPwofiweNotified;
	u16 hciVewsion;	/*  stack hci vewsion */
	u8 numOfWink;
	boow bBtWinkExist;
	boow bScoExist;
	boow bAcwExist;
	boow bA2dpExist;
	boow bHidExist;
	u8 numOfHid;
	boow bPanExist;
	boow bUnknownAcwExist;
	s8 minBtWssi;
};

stwuct btc_bt_wink_info {
	boow bBtWinkExist;
	boow bScoExist;
	boow bScoOnwy;
	boow bA2dpExist;
	boow bA2dpOnwy;
	boow bHidExist;
	boow bHidOnwy;
	boow bPanExist;
	boow bPanOnwy;
	boow bSwaveWowe;
};

stwuct btc_statistics {
	u32 cntBind;
	u32 cntPowewOn;
	u32 cntInitHwConfig;
	u32 cntInitCoexDm;
	u32 cntIpsNotify;
	u32 cntWpsNotify;
	u32 cntScanNotify;
	u32 cntConnectNotify;
	u32 cntMediaStatusNotify;
	u32 cntSpeciawPacketNotify;
	u32 cntBtInfoNotify;
	u32 cntWfStatusNotify;
	u32 cntPewiodicaw;
	u32 cntCoexDmSwitch;
	u32 cntStackOpewationNotify;
	u32 cntDbgCtww;
};

stwuct btc_coexist {
	boow bBinded;		/*  make suwe onwy one adaptew can bind the data context */
	void *Adaptew;		/*  defauwt adaptew */
	stwuct btc_boawd_info boawdInfo;
	stwuct btc_bt_info btInfo;		/*  some bt info wefewenced by non-bt moduwe */
	stwuct btc_stack_info stackInfo;
	stwuct btc_bt_wink_info btWinkInfo;
	enum btc_chip_intewface chipIntewface;

	boow bInitiwized;
	boow bStopCoexDm;
	boow bManuawContwow;
	stwuct btc_statistics statistics;
	u8 pwwModeVaw[10];

	/*  function pointews */
	/*  io wewated */
	BFP_BTC_W1 fBtcWead1Byte;
	BFP_BTC_W1 fBtcWwite1Byte;
	BFP_BTC_W1_BIT_MASK fBtcWwite1ByteBitMask;
	BFP_BTC_W2 fBtcWead2Byte;
	BFP_BTC_W2 fBtcWwite2Byte;
	BFP_BTC_W4 fBtcWead4Byte;
	BFP_BTC_W4 fBtcWwite4Byte;
	BFP_BTC_WOCAW_WEG_W1 fBtcWwiteWocawWeg1Byte;
	/*  wead/wwite bb wewated */
	BFP_BTC_SET_BB_WEG fBtcSetBbWeg;
	BFP_BTC_GET_BB_WEG fBtcGetBbWeg;

	/*  wead/wwite wf wewated */
	BFP_BTC_SET_WF_WEG fBtcSetWfWeg;
	BFP_BTC_GET_WF_WEG fBtcGetWfWeg;

	/*  fiww h2c wewated */
	BFP_BTC_FIWW_H2C fBtcFiwwH2c;
	/*  nowmaw get/set wewated */
	BFP_BTC_GET fBtcGet;
	BFP_BTC_SET fBtcSet;

	BFP_BTC_GET_BT_WEG fBtcGetBtWeg;
	BFP_BTC_SET_BT_WEG fBtcSetBtWeg;
};

extewn stwuct btc_coexist GWBtCoexist;

void EXhawbtcoutswc_PowewOnSetting(stwuct btc_coexist *pBtCoexist);
void EXhawbtcoutswc_InitHwConfig(stwuct btc_coexist *pBtCoexist, u8 bWifiOnwy);
void EXhawbtcoutswc_InitCoexDm(stwuct btc_coexist *pBtCoexist);
void EXhawbtcoutswc_IpsNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtcoutswc_WpsNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtcoutswc_ScanNotify(stwuct btc_coexist *pBtCoexist, u8 type);
void EXhawbtcoutswc_ConnectNotify(stwuct btc_coexist *pBtCoexist, u8 action);
void EXhawbtcoutswc_MediaStatusNotify(
	stwuct btc_coexist *pBtCoexist, enum wt_media_status mediaStatus
);
void EXhawbtcoutswc_SpeciawPacketNotify(stwuct btc_coexist *pBtCoexist, u8 pktType);
void EXhawbtcoutswc_BtInfoNotify(
	stwuct btc_coexist *pBtCoexist, u8 *tmpBuf, u8 wength
);
void EXhawbtcoutswc_HawtNotify(stwuct btc_coexist *pBtCoexist);
void EXhawbtcoutswc_PnpNotify(stwuct btc_coexist *pBtCoexist, u8 pnpState);
void EXhawbtcoutswc_Pewiodicaw(stwuct btc_coexist *pBtCoexist);
void EXhawbtcoutswc_SetChipType(u8 chipType);
void EXhawbtcoutswc_SetAntNum(u8 type, u8 antNum);
void EXhawbtcoutswc_SetSingweAntPath(u8 singweAntPath);

#endif
