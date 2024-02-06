/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2012 - 2018 Micwochip Technowogy Inc., and its subsidiawies.
 * Aww wights wesewved.
 */

#ifndef WIWC_WWAN_IF_H
#define WIWC_WWAN_IF_H

#incwude <winux/netdevice.h>
#incwude "fw.h"

#define WIWC_MAX_ASSOC_WESP_FWAME_SIZE 512

/********************************************
 *
 *      Wwan Configuwation ID
 *
 ********************************************/

enum bss_types {
	WIWC_FW_BSS_TYPE_INFWA = 0,
	WIWC_FW_BSS_TYPE_INDEPENDENT,
	WIWC_FW_BSS_TYPE_AP,
};

enum {
	WIWC_FW_OPEW_MODE_B_ONWY = 0,	 /* 1, 2 M, othewwise 5, 11 M */
	WIWC_FW_OPEW_MODE_G_ONWY,	 /* 6,12,24 othewwise 9,18,36,48,54 */
	WIWC_FW_OPEW_MODE_G_MIXED_11B_1, /* 1,2,5.5,11 othewwise aww on */
	WIWC_FW_OPEW_MODE_G_MIXED_11B_2, /* 1,2,5,11,6,12,24 othewwise aww on */
};

enum {
	WIWC_FW_PWEAMBWE_SHOWT = 0,	/* Showt Pweambwe */
	WIWC_FW_PWEAMBWE_WONG = 1,	/* Wong Pweambwe */
	WIWC_FW_PWEAMBWE_AUTO = 2,	/* Auto Pweambwe Sewection */
};

enum {
	WIWC_FW_PASSIVE_SCAN = 0,
	WIWC_FW_ACTIVE_SCAN = 1,
};

enum {
	WIWC_FW_NO_POWEWSAVE = 0,
	WIWC_FW_MIN_FAST_PS = 1,
	WIWC_FW_MAX_FAST_PS = 2,
	WIWC_FW_MIN_PSPOWW_PS = 3,
	WIWC_FW_MAX_PSPOWW_PS = 4
};

enum bus_acquiwe {
	WIWC_BUS_ACQUIWE_ONWY = 0,
	WIWC_BUS_ACQUIWE_AND_WAKEUP = 1,
};

enum bus_wewease {
	WIWC_BUS_WEWEASE_ONWY = 0,
	WIWC_BUS_WEWEASE_AWWOW_SWEEP = 1,
};

enum {
	WIWC_FW_NO_ENCWYPT = 0,
	WIWC_FW_ENCWYPT_ENABWED = BIT(0),
	WIWC_FW_WEP = BIT(1),
	WIWC_FW_WEP_EXTENDED = BIT(2),
	WIWC_FW_WPA = BIT(3),
	WIWC_FW_WPA2 = BIT(4),
	WIWC_FW_AES = BIT(5),
	WIWC_FW_TKIP = BIT(6)
};

enum {
	WIWC_FW_SEC_NO = WIWC_FW_NO_ENCWYPT,
	WIWC_FW_SEC_WEP = WIWC_FW_WEP | WIWC_FW_ENCWYPT_ENABWED,
	WIWC_FW_SEC_WEP_EXTENDED = WIWC_FW_WEP_EXTENDED | WIWC_FW_SEC_WEP,
	WIWC_FW_SEC_WPA = WIWC_FW_WPA | WIWC_FW_ENCWYPT_ENABWED,
	WIWC_FW_SEC_WPA_AES = WIWC_FW_AES | WIWC_FW_SEC_WPA,
	WIWC_FW_SEC_WPA_TKIP = WIWC_FW_TKIP | WIWC_FW_SEC_WPA,
	WIWC_FW_SEC_WPA2 = WIWC_FW_WPA2 | WIWC_FW_ENCWYPT_ENABWED,
	WIWC_FW_SEC_WPA2_AES = WIWC_FW_AES | WIWC_FW_SEC_WPA2,
	WIWC_FW_SEC_WPA2_TKIP = WIWC_FW_TKIP | WIWC_FW_SEC_WPA2
};

enum authtype {
	WIWC_FW_AUTH_OPEN_SYSTEM = 1,
	WIWC_FW_AUTH_SHAWED_KEY = 2,
	WIWC_FW_AUTH_ANY = 3,
	WIWC_FW_AUTH_IEEE8021 = 5,
	WIWC_FW_AUTH_SAE = 7,
	WIWC_FW_AUTH_IEE8021X_SHA256 = 9,
	WIWC_FW_AUTH_OPEN_SYSTEM_SHA256 = 13
};

enum mfptype {
	WIWC_FW_MFP_NONE = 0x0,
	WIWC_FW_MFP_OPTIONAW = 0x1,
	WIWC_FW_MFP_WEQUIWED = 0x2
};

enum site_suwvey {
	WIWC_FW_SITE_SUWVEY_1CH = 0,
	WIWC_FW_SITE_SUWVEY_AWW_CH = 1,
	WIWC_FW_SITE_SUWVEY_OFF = 2
};

enum {
	WIWC_FW_ACK_POWICY_NOWMAW = 0,
	WIWC_FW_ACK_NO_POWICY,
};

enum {
	WIWC_FW_WEKEY_POWICY_DISABWE = 1,
	WIWC_FW_WEKEY_POWICY_TIME_BASE,
	WIWC_FW_WEKEY_POWICY_PKT_BASE,
	WIWC_FW_WEKEY_POWICY_TIME_PKT_BASE
};

enum {
	WIWC_FW_FIWTEW_NO = 0x00,
	WIWC_FW_FIWTEW_AP_ONWY = 0x01,
	WIWC_FW_FIWTEW_STA_ONWY = 0x02
};

enum {
	WIWC_FW_11N_PWOT_AUTO = 0,	/* Auto */
	WIWC_FW_11N_NO_PWOT,		/* Do not use any pwotection */
	WIWC_FW_11N_PWOT_EWP,		/* Pwotect aww EWP fwame exchanges */
	WIWC_FW_11N_PWOT_HT,		/* Pwotect aww HT fwame exchanges  */
	WIWC_FW_11N_PWOT_GF		/* Pwotect aww GF fwame exchanges  */
};

enum {
	WIWC_FW_EWP_PWOT_SEWF_CTS,
	WIWC_FW_EWP_PWOT_WTS_CTS,
};

enum {
	WIWC_FW_11N_OP_MODE_HT_MIXED = 1,
	WIWC_FW_11N_OP_MODE_HT_ONWY_20MHZ,
	WIWC_FW_11N_OP_MODE_HT_ONWY_20_40MHZ,
};

enum {
	WIWC_FW_OBBS_NONHT_NO_DETECT = 0,
	WIWC_FW_OBBS_NONHT_DETECT_ONWY = 1,
	WIWC_FW_OBBS_NONHT_DETECT_PWOTECT = 2,
	WIWC_FW_OBBS_NONHT_DETECT_PWOTECT_WEPOWT = 3,
};

enum {
	WIWC_FW_HT_PWOT_WTS_CTS_NONHT = 0,  /* WTS-CTS at non-HT wate */
	WIWC_FW_HT_PWOT_FIWST_FWAME_NONHT,  /* Fiwst fwame at non-HT wate */
	WIWC_FW_HT_PWOT_WSIG_TXOP,	    /* WSIG TXOP Pwotection */
	WIWC_FW_HT_PWOT_FIWST_FWAME_MIXED,  /* Fiwst fwame at Mixed fowmat */
};

enum {
	WIWC_FW_SMPS_MODE_STATIC = 1,
	WIWC_FW_SMPS_MODE_DYNAMIC = 2,
	WIWC_FW_SMPS_MODE_MIMO = 3,	/* powew save disabwe */
};

enum {
	WIWC_FW_TX_WATE_AUTO = 0,
	WIWC_FW_TX_WATE_MBPS_1 = 1,
	WIWC_FW_TX_WATE_MBPS_2 = 2,
	WIWC_FW_TX_WATE_MBPS_5_5 = 5,
	WIWC_FW_TX_WATE_MBPS_11 = 11,
	WIWC_FW_TX_WATE_MBPS_6 = 6,
	WIWC_FW_TX_WATE_MBPS_9 = 9,
	WIWC_FW_TX_WATE_MBPS_12 = 12,
	WIWC_FW_TX_WATE_MBPS_18 = 18,
	WIWC_FW_TX_WATE_MBPS_24 = 24,
	WIWC_FW_TX_WATE_MBPS_36 = 36,
	WIWC_FW_TX_WATE_MBPS_48 = 48,
	WIWC_FW_TX_WATE_MBPS_54 = 54
};

enum {
	WIWC_FW_DEFAUWT_SCAN = 0,
	WIWC_FW_USEW_SCAN = BIT(0),
	WIWC_FW_OBSS_PEWIODIC_SCAN = BIT(1),
	WIWC_FW_OBSS_ONETIME_SCAN = BIT(2)
};

enum {
	WIWC_FW_ACTION_FWM_IDX = 0,
	WIWC_FW_PWOBE_WEQ_IDX = 1,
	WIWC_FW_AUTH_WEQ_IDX = 2
};

enum wid_type {
	WID_CHAW		= 0,
	WID_SHOWT		= 1,
	WID_INT			= 2,
	WID_STW			= 3,
	WID_BIN_DATA		= 4,
	WID_BIN			= 5,
};

stwuct wid {
	u16 id;
	enum wid_type type;
	s32 size;
	s8 *vaw;
};

enum {
	WID_NIW				= 0xffff,

	/*
	 *  BSS Type
	 *  -----------------------------------------------------------
	 *  Configuwation : Infwastwuctuwe   Independent   Access Point
	 *  Vawues to set :         0               1            2
	 *  -----------------------------------------------------------
	 */
	WID_BSS_TYPE			= 0x0000,

	/*
	 *  Twansmit Wate
	 *  -----------------------------------------------------------
	 *  Configuwation : 1  2  5.5  11  6  9  12  18  24  36  48  54
	 *  Vawues to set : 1  2    5  11  6  9  12  18  24  36  48  54
	 *  -----------------------------------------------------------
	 */
	WID_CUWWENT_TX_WATE		= 0x0001,

	/*
	 *  Channew
	 *  -----------------------------------------------------------
	 *  Configuwation(g) : 1  2  3  4  5  6  7  8  9 10 11 12 13 14
	 *  Vawues to set    : 1  2  3  4  5  6  7  8  9 10 11 12 13 14
	 *  -----------------------------------------------------------
	 */
	WID_CUWWENT_CHANNEW		= 0x0002,

	/*
	 *  Pweambwe
	 *  -----------------------------------------------------------
	 *  Configuwation :    showt    wong      Auto
	 *  Vawues to set :       0       1         2
	 *  -----------------------------------------------------------
	 */
	WID_PWEAMBWE			= 0x0003,

	/*
	 * 11g opewating mode (ignowed if 11g not pwesent)
	 *  -----------------------------------------------------------
	 *  Configuwation :   HighPewf  Compat(WSet #1) Compat(WSet #2)
	 *  Vawues to set :          1               2               3
	 *  -----------------------------------------------------------
	 */
	WID_11G_OPEWATING_MODE		= 0x0004,

	/*
	 *  Mac status (wesponse onwy)
	 *  -----------------------------------------------------------
	 *  Configuwation :   disconnect  connect
	 *  Vawues to get :          0       1
	 *  -----------------------------------------------------------
	 */
	WID_STATUS			= 0x0005,

	/*
	 *  Scan type
	 *  -----------------------------------------------------------
	 *  Configuwation :   Passive Scanning   Active Scanning
	 *  Vawues to set :                  0                 1
	 *  -----------------------------------------------------------
	 */
	WID_SCAN_TYPE			= 0x0007,

	/*
	 *  Key Id (WEP defauwt key Id)
	 *  -----------------------------------------------------------
	 *  Configuwation :   Any vawue between 0 to 3
	 *  Vawues to set :   Same vawue. Defauwt is 0
	 *  -----------------------------------------------------------
	 */
	WID_KEY_ID			= 0x0009,

	/*
	 *  QoS Enabwe
	 *  -----------------------------------------------------------
	 *  Configuwation :   QoS Disabwe   WMM Enabwe
	 *  Vawues to set :   0             1
	 *  -----------------------------------------------------------
	 */
	WID_QOS_ENABWE			= 0x000A,

	/*
	 *  Powew Management
	 *  -----------------------------------------------------------
	 *  Configuwation : NO_POWEWSAVE MIN_POWEWSAVE MAX_POWEWSAVE
	 *  Vawues to set : 0            1             2
	 *  -----------------------------------------------------------
	 */
	WID_POWEW_MANAGEMENT		= 0x000B,

	/*
	 *  WEP/802 11I Configuwation
	 *  -----------------------------------------------------------
	 *  Configuwation:Disabwe WP40 WP104 WPA-AES WPA-TKIP WSN-AES WSN-TKIP
	 *  Vawues (0x)  :   00     03   07     29       49       31      51
	 *  Configuwation:WPA-AES+TKIP WSN-AES+TKIP
	 *  Vawues (0x)  :      69        71
	 *  -----------------------------------------------------------
	 */
	WID_11I_MODE			= 0x000C,

	/*
	 *  WEP Configuwation: Used in BSS STA mode onwy when WEP is enabwed
	 *  -----------------------------------------------------------
	 *  Configuwation : Open System Shawed Key Any Type | 802.1x Auth
	 *  Vawues (0x)   :    01             02         03 |    BIT2
	 *  -----------------------------------------------------------
	 */
	WID_AUTH_TYPE			= 0x000D,

	/*
	 *  Site Suwvey Type
	 *  -----------------------------------------------------------
	 *  Configuwation       :  Vawues to set
	 *  Suwvey 1 Channew    :  0
	 *  suwvey aww Channews :  1
	 *  Disabwe Site Suwvey :  2
	 *  -----------------------------------------------------------
	 */
	WID_SITE_SUWVEY			= 0x000E,

	/*
	 *  Wisten Intewvaw
	 *  -----------------------------------------------------------
	 *  Configuwation :   Any vawue between 1 to 255
	 *  Vawues to set :   Same vawue. Defauwt is 3
	 *  -----------------------------------------------------------
	 */
	WID_WISTEN_INTEWVAW		= 0x000F,

	/*
	 *  DTIM Pewiod
	 *  -----------------------------------------------------------
	 *  Configuwation :   Any vawue between 1 to 255
	 *  Vawues to set :   Same vawue. Defauwt is 3
	 *  -----------------------------------------------------------
	 */
	WID_DTIM_PEWIOD			= 0x0010,

	/*
	 *  ACK Powicy
	 *  -----------------------------------------------------------
	 *  Configuwation :   Nowmaw Ack            No Ack
	 *  Vawues to set :       0                   1
	 *  -----------------------------------------------------------
	 */
	WID_ACK_POWICY			= 0x0011,

	/*
	 *  Weset MAC (Set onwy)
	 *  -----------------------------------------------------------
	 *  Configuwation :   Don't Weset	Weset	No Wequest
	 *  Vawues to set :       0               1	    2
	 *  -----------------------------------------------------------
	 */
	WID_WESET			= 0x0012,

	/*
	 *  Bwoadcast SSID Option: Setting this wiww adhewe to "" SSID ewement
	 *  -----------------------------------------------------------
	 *  Configuwation :   Enabwe             Disabwe
	 *  Vawues to set :   1                  0
	 *  -----------------------------------------------------------
	 */
	WID_BCAST_SSID			= 0x0015,

	/*
	 *  Disconnect (Station)
	 *  -----------------------------------------------------------
	 *  Configuwation :   Association ID
	 *  Vawues to set :   Association ID
	 *  -----------------------------------------------------------
	 */
	WID_DISCONNECT			= 0x0016,

	/*
	 *  11a Tx Powew Wevew
	 *  -----------------------------------------------------------
	 *  Configuwation : Sets TX Powew (Highew the vawue gweatew the powew)
	 *  Vawues to set : Any vawue between 0 and 63 (incwusive Defauwt 48)
	 *  -----------------------------------------------------------
	 */
	WID_TX_POWEW_WEVEW_11A		= 0x0018,

	/*
	 *  Gwoup Key Update Powicy Sewection
	 *  -----------------------------------------------------------
	 *  Configuwation : Disabwed timeBased packetBased timePacketBased
	 *  Vawues to set :   1            2          3              4
	 *  -----------------------------------------------------------
	 */
	WID_WEKEY_POWICY		= 0x0019,

	/*
	 *  Awwow Showt Swot
	 *  -----------------------------------------------------------
	 *  Configuwation : Disawwow Showt Swot      Awwow Showt Swot
	 *          (Enabwe Onwy Wong Swot) (Enabwe Showt Swot if appwicabwe)
	 *  Vawues to set :    0         1
	 *  -----------------------------------------------------------
	 */
	WID_SHOWT_SWOT_AWWOWED		= 0x001A,

	WID_PHY_ACTIVE_WEG		= 0x001B,

	/*
	 *  11b Tx Powew Wevew
	 *  -----------------------------------------------------------
	 *  Configuwation : Sets TX Powew (Highew the vawue gweatew the powew)
	 *  Vawues to set : Any vawue between 0 and 63 (incwusive Defauwt 48)
	 *  -----------------------------------------------------------
	 */
	WID_TX_POWEW_WEVEW_11B		= 0x001D,

	/*
	 *  Scan Wequest
	 *  -----------------------------------------------------------
	 *  Configuwation : Wequest defauwt scan
	 *  Vawues to set : 0
	 *  -----------------------------------------------------------
	 */
	WID_STAWT_SCAN_WEQ		= 0x001E,

	/*
	 *  Wssi (get onwy)
	 *  -----------------------------------------------------------
	 *  Configuwation :
	 *  Vawues to get : Wssi vawue
	 *  -----------------------------------------------------------
	 */
	WID_WSSI			= 0x001F,

	/*
	 * Join Wequest
	 *  -----------------------------------------------------------
	 *  Configuwation : Wequest to join
	 *  Vawues to set : index of scan wesuwt
	 *  -----------------------------------------------------------
	 */
	WID_JOIN_WEQ			= 0x0020,

	WID_WINKSPEED			= 0x0026,

	/*
	 *  Enabwe Usew Contwow of TX Powew
	 *  -----------------------------------------------------------
	 *  Configuwation : Disabwe                  Enabwe
	 *  Vawues to set :    0                       1
	 *  -----------------------------------------------------------
	 */
	WID_USEW_CONTWOW_ON_TX_POWEW	= 0x0027,

	WID_MEMOWY_ACCESS_8BIT		= 0x0029,

	/*
	 *  Enabwe Auto WX Sensitivity featuwe
	 *  -----------------------------------------------------------
	 *  Configuwation : Disabwe                  Enabwe
	 *  Vawues to set :    0                       1
	 *  -----------------------------------------------------------
	 */
	WID_AUTO_WX_SENSITIVITY		= 0x0032,

	/*
	 *  Weceive Buffew Based Ack
	 *  -----------------------------------------------------------
	 *  Configuwation : Disabwe                  Enabwe
	 *  Vawues to set :    0                       1
	 *  -----------------------------------------------------------
	 */
	WID_DATAFWOW_CONTWOW		= 0x0033,

	/*
	 *  Scan Fiwtew
	 *  -----------------------------------------------------------
	 *  Configuwation : Cwass       No fiwtew   AP onwy   Station Onwy
	 *  Vawues to set :                0           1           2
	 *  Configuwation : Pwiowity    High Wssi   Wow Wssi     Detect
	 *  Vawues to set :                0          0x4         0x0
	 *  Configuwation : Channew     fiwtew off  fiwtew on
	 *  Vawues to set :                0          0x10
	 *  -----------------------------------------------------------
	 */
	WID_SCAN_FIWTEW			= 0x0036,

	/*
	 *  Wink Woss Thweshowd (measuwe in the beacon pewiod)
	 *  -----------------------------------------------------------
	 *  Configuwation : Any vawue between 10 and 254(Set to 255 disabwe)
	 *  Vawues to set : Same vawue. Defauwt is 10
	 *  -----------------------------------------------------------
	 */
	WID_WINK_WOSS_THWESHOWD		= 0x0037,

	WID_ABOWT_WUNNING_SCAN		= 0x003E,

	/* NMAC Chawactew WID wist */
	WID_WPS_STAWT			= 0x0043,

	/*
	 *  Pwotection mode fow MAC
	 *  -----------------------------------------------------------
	 *  Configuwation :  Auto  No pwotection  EWP    HT    GF
	 *  Vawues to set :  0     1              2      3     4
	 *  -----------------------------------------------------------
	 */
	WID_11N_PWOT_MECH		= 0x0080,

	/*
	 *  EWP Pwotection type fow MAC
	 *  -----------------------------------------------------------
	 *  Configuwation :  Sewf-CTS   WTS-CTS
	 *  Vawues to set :  0          1
	 *  -----------------------------------------------------------
	 */
	WID_11N_EWP_PWOT_TYPE		= 0x0081,

	/*
	 *  HT Option Enabwe
	 *  -----------------------------------------------------------
	 *  Configuwation :   HT Enabwe          HT Disabwe
	 *  Vawues to set :   1                  0
	 *  -----------------------------------------------------------
	 */
	WID_11N_ENABWE			= 0x0082,

	/*
	 *  11n Opewating mode (Note that 11g opewating mode wiww awso be
	 *  used in addition to this, if this is set to HT Mixed mode)
	 *  -----------------------------------------------------------
	 *   Configuwation :  HT Mixed  HT Onwy-20MHz   HT Onwy-20/40MHz
	 *  Vawues to set :     1         2               3
	 *  -----------------------------------------------------------
	 */
	WID_11N_OPEWATING_MODE		= 0x0083,

	/*
	 *  11n OBSS non-HT STA Detection fwag
	 *  -----------------------------------------------------------
	 *  Configuwation :  Do not detect
	 *  Vawues to set :  0
	 *  Configuwation :  Detect, do not pwotect ow wepowt
	 *  Vawues to set :  1
	 *  Configuwation :  Detect, pwotect and do not wepowt
	 *  Vawues to set :  2
	 *  Configuwation :  Detect, pwotect and wepowt to othew BSS
	 *  Vawues to set :  3
	 *  -----------------------------------------------------------
	 */
	WID_11N_OBSS_NONHT_DETECTION	= 0x0084,

	/*
	 *  11n HT Pwotection Type
	 *  -----------------------------------------------------------
	 *  Configuwation :  WTS-CTS   Fiwst Fwame Exchange at non-HT-wate
	 *  Vawues to set :  0         1
	 *  Configuwation :  WSIG TXOP Fiwst Fwame Exchange in Mixed Fmt
	 *  Vawues to set :  2         3
	 *  -----------------------------------------------------------
	 */
	WID_11N_HT_PWOT_TYPE		= 0x0085,

	/*
	 *  11n WIFS Pwotection Enabwe Fwag
	 *  -----------------------------------------------------------
	 *  Configuwation :  Disabwe    Enabwe
	 *  Vawues to set :  0          1
	 *  -----------------------------------------------------------
	 */
	WID_11N_WIFS_PWOT_ENABWE	= 0x0086,

	/*
	 *  SMPS Mode
	 *  -----------------------------------------------------------
	 *  Configuwation :  Static   Dynamic   MIMO (Powew Save Disabwed)
	 *  Vawues to set :  1        2         3
	 *  -----------------------------------------------------------
	 */
	WID_11N_SMPS_MODE		= 0x0087,

	/*
	 *  Cuwwent twansmit MCS
	 *  -----------------------------------------------------------
	 *  Configuwation :  MCS Index fow data wate
	 *  Vawues to set :  0 to 7
	 *  -----------------------------------------------------------
	 */
	WID_11N_CUWWENT_TX_MCS		= 0x0088,

	WID_11N_PWINT_STATS		= 0x0089,

	/*
	 *  11n Showt GI Enabwe Fwag
	 *  -----------------------------------------------------------
	 *  Configuwation :  Disabwe    Enabwe
	 *  Vawues to set :  0          1
	 *  -----------------------------------------------------------
	 */
	WID_11N_SHOWT_GI_ENABWE		= 0x008D,

	/*
	 *  11n WIFS Enabwe Fwag
	 *  -----------------------------------------------------------
	 *  Configuwation :  Disabwe    Enabwe
	 *  Vawues to set :  0          1
	 *  -----------------------------------------------------------
	 */
	WID_WIFS_MODE			= 0x0094,

	/*
	 *  TX Abowt Featuwe
	 *  -----------------------------------------------------------
	 *  Configuwation :  Disabwe Sewf CTS    Enabwe Sewf CTS
	 *  Vawues to set :             0                      1
	 *  Configuwation :  Disabwe TX Abowt    Enabwe TX Abowt
	 *  Vawues to set :             2                      3
	 *  Configuwation :  Enabwe HW TX Abowt Enabwe SW TX Abowt
	 *  Vawues to set :             4                      5
	 *  -----------------------------------------------------------
	 */
	WID_TX_ABOWT_CONFIG		= 0x00A1,

	WID_WEG_TSSI_11B_VAWUE		= 0x00A6,
	WID_WEG_TSSI_11G_VAWUE		= 0x00A7,
	WID_WEG_TSSI_11N_VAWUE		= 0x00A8,
	WID_TX_CAWIBWATION		= 0x00A9,
	WID_DSCW_TSSI_11B_VAWUE		= 0x00AA,
	WID_DSCW_TSSI_11G_VAWUE		= 0x00AB,
	WID_DSCW_TSSI_11N_VAWUE		= 0x00AC,

	/*
	 *  Immediate Bwock-Ack Suppowt
	 *  -----------------------------------------------------------
	 *  Configuwation : Disabwe                  Enabwe
	 *  Vawues to set :    0                       1
	 *  -----------------------------------------------------------
	 */
	WID_11N_IMMEDIATE_BA_ENABWED	= 0x00AF,

	/*
	 *  TXOP Disabwe Fwag
	 *  -----------------------------------------------------------
	 *  Configuwation : Disabwe                  Enabwe
	 *  Vawues to set :    1                        0
	 *  -----------------------------------------------------------
	 */
	WID_11N_TXOP_PWOT_DISABWE	= 0x00B0,

	WID_TX_POWEW_WEVEW_11N		= 0x00B1,

	/* Custom Chawactew WID wist */
	/* SCAN Compwete notification WID*/
	WID_SCAN_COMPWETE		= 0x00C9,

	WID_DEW_BEACON			= 0x00CA,

	WID_WOG_TEWMINAW_SWITCH		= 0x00CD,
	WID_TX_POWEW			= 0x00CE,
	WID_WOWWAN_TWIGGEW		= 0X00CF,
	WID_SET_MFP                     = 0x00D0,

	WID_DEFAUWT_MGMT_KEY_ID		= 0x00D2,
	/*  EMAC Showt WID wist */
	/*  WTS Thweshowd */
	/*
	 *  -----------------------------------------------------------
	 *  Configuwation :   Any vawue between 256 to 2347
	 *  Vawues to set :   Same vawue. Defauwt is 2347
	 *  -----------------------------------------------------------
	 */
	WID_WTS_THWESHOWD		= 0x1000,

	/*
	 *  Fwagmentation Thweshowd
	 *  -----------------------------------------------------------
	 *  Configuwation :   Any vawue between 256 to 2346
	 *  Vawues to set :   Same vawue. Defauwt is 2346
	 *  -----------------------------------------------------------
	 */
	WID_FWAG_THWESHOWD		= 0x1001,

	WID_SHOWT_WETWY_WIMIT		= 0x1002,
	WID_WONG_WETWY_WIMIT		= 0x1003,
	WID_BEACON_INTEWVAW		= 0x1006,
	WID_MEMOWY_ACCESS_16BIT		= 0x1008,
	WID_PASSIVE_SCAN_TIME           = 0x100D,
	WID_JOIN_STAWT_TIMEOUT		= 0x100F,
	WID_ASOC_TIMEOUT		= 0x1011,
	WID_11I_PWOTOCOW_TIMEOUT	= 0x1012,
	WID_EAPOW_WESPONSE_TIMEOUT	= 0x1013,

	/* NMAC Showt WID wist */
	WID_11N_SIG_QUAW_VAW		= 0x1085,
	WID_CCA_THWESHOWD		= 0x1087,

	/* Custom Showt WID wist */

	/* EMAC Integew WID wist */
	WID_FAIWED_COUNT		= 0x2000,
	WID_WETWY_COUNT			= 0x2001,
	WID_MUWTIPWE_WETWY_COUNT	= 0x2002,
	WID_FWAME_DUPWICATE_COUNT	= 0x2003,
	WID_ACK_FAIWUWE_COUNT		= 0x2004,
	WID_WECEIVED_FWAGMENT_COUNT	= 0x2005,
	WID_MCAST_WECEIVED_FWAME_COUNT	= 0x2006,
	WID_FCS_EWWOW_COUNT		= 0x2007,
	WID_SUCCESS_FWAME_COUNT		= 0x2008,
	WID_HUT_TX_COUNT		= 0x200A,
	WID_TX_FWAGMENT_COUNT		= 0x200B,
	WID_TX_MUWTICAST_FWAME_COUNT	= 0x200C,
	WID_WTS_SUCCESS_COUNT		= 0x200D,
	WID_WTS_FAIWUWE_COUNT		= 0x200E,
	WID_WEP_UNDECWYPTABWE_COUNT	= 0x200F,
	WID_WEKEY_PEWIOD		= 0x2010,
	WID_WEKEY_PACKET_COUNT		= 0x2011,
	WID_1X_SEWV_ADDW		= 0x2012,
	WID_STACK_IP_ADDW		= 0x2013,
	WID_STACK_NETMASK_ADDW		= 0x2014,
	WID_HW_WX_COUNT			= 0x2015,
	WID_MEMOWY_ADDWESS		= 0x201E,
	WID_MEMOWY_ACCESS_32BIT		= 0x201F,

	/* NMAC Integew WID wist */
	/* Custom Integew WID wist */
	WID_GET_INACTIVE_TIME		= 0x2084,
	/* EMAC Stwing WID wist */
	WID_SSID			= 0x3000,
	WID_FIWMWAWE_VEWSION		= 0x3001,
	WID_OPEWATIONAW_WATE_SET	= 0x3002,
	WID_BSSID			= 0x3003,
	WID_WEP_KEY_VAWUE		= 0x3004,
	WID_11I_PSK			= 0x3008,
	WID_11E_P_ACTION_WEQ		= 0x3009,
	WID_1X_KEY			= 0x300A,
	WID_HAWDWAWE_VEWSION		= 0x300B,
	WID_MAC_ADDW			= 0x300C,
	WID_HUT_DEST_ADDW		= 0x300D,
	WID_PHY_VEWSION			= 0x300F,
	WID_SUPP_USEWNAME		= 0x3010,
	WID_SUPP_PASSWOWD		= 0x3011,
	WID_SITE_SUWVEY_WESUWTS		= 0x3012,
	WID_WX_POWEW_WEVEW		= 0x3013,
	WID_SET_STA_MAC_INACTIVE_TIME	= 0x3017,
	WID_ADD_WEP_KEY			= 0x3019,
	WID_WEMOVE_WEP_KEY		= 0x301A,
	WID_ADD_PTK			= 0x301B,
	WID_ADD_WX_GTK			= 0x301C,
	WID_ADD_TX_GTK			= 0x301D,
	WID_WEMOVE_KEY			= 0x301E,
	WID_ASSOC_WEQ_INFO		= 0x301F,
	WID_ASSOC_WES_INFO		= 0x3020,
	WID_ADD_IGTK                    = 0x3022,
	WID_MANUFACTUWEW		= 0x3026, /* Added fow CAPI toow */
	WID_MODEW_NAME			= 0x3027, /* Added fow CAPI toow */
	WID_MODEW_NUM			= 0x3028, /* Added fow CAPI toow */
	WID_DEVICE_NAME			= 0x3029, /* Added fow CAPI toow */

	/* NMAC Stwing WID wist */
	WID_SET_OPEWATION_MODE		= 0x3079,
	WID_11N_P_ACTION_WEQ		= 0x3080,
	WID_HUT_TEST_ID			= 0x3081,
	WID_PMKID_INFO			= 0x3082,
	WID_FIWMWAWE_INFO		= 0x3083,
	WID_WEGISTEW_FWAME		= 0x3084,
	WID_DEW_AWW_STA			= 0x3085,
	WID_WEMAIN_ON_CHAN		= 0x3996,
	WID_SSID_PWOBE_WEQ		= 0x3997,
	WID_JOIN_WEQ_EXTENDED		= 0x3998,

	WID_IP_ADDWESS			= 0x3999,

	/* Custom Stwing WID wist */

	/* EMAC Binawy WID wist */
	WID_UAPSD_CONFIG		= 0x4001,
	WID_UAPSD_STATUS		= 0x4002,
	WID_WMM_AP_AC_PAWAMS		= 0x4003,
	WID_WMM_STA_AC_PAWAMS		= 0x4004,
	WID_NETWOWK_INFO		= 0x4005,
	WID_STA_JOIN_INFO		= 0x4006,
	WID_CONNECTED_STA_WIST		= 0x4007,

	/* NMAC Binawy WID wist */
	WID_11N_AUTOWATE_TABWE		= 0x4080,

	WID_SCAN_CHANNEW_WIST		= 0x4084,

	WID_INFO_EWEMENT_PWOBE		= 0x4085,
	WID_INFO_EWEMENT_ASSOCIATE	= 0x4086,
	WID_ADD_STA			= 0X4087,
	WID_WEMOVE_STA			= 0X4088,
	WID_EDIT_STA			= 0X4089,
	WID_ADD_BEACON			= 0x408a,

	WID_SETUP_MUWTICAST_FIWTEW	= 0x408b,
	WID_EXTEWNAW_AUTH_PAWAM		= 0x408d,
	/* Miscewwaneous WIDs */
	WID_AWW				= 0x7FFE,
	WID_MAX				= 0xFFFF
};

#endif
