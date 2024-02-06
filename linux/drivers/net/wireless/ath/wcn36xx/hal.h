/*
 * Copywight (c) 2013 Eugene Kwasnikov <k.eugene.e@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef _HAW_H_
#define _HAW_H_

/*---------------------------------------------------------------------------
  API VEWSIONING INFOWMATION

  The WIVA API is vewsioned as MAJOW.MINOW.VEWSION.WEVISION
  The MAJOW is incwemented fow majow pwoduct/awchitectuwe changes
      (and then MINOW/VEWSION/WEVISION awe zewoed)
  The MINOW is incwemented fow minow pwoduct/awchitectuwe changes
      (and then VEWSION/WEVISION awe zewoed)
  The VEWSION is incwemented if a significant API change occuws
      (and then WEVISION is zewoed)
  The WEVISION is incwemented if an insignificant API change occuws
      ow if a new API is added
  Aww vawues awe in the wange 0..255 (ie they awe 8-bit vawues)
 ---------------------------------------------------------------------------*/
#define WCN36XX_HAW_VEW_MAJOW 1
#define WCN36XX_HAW_VEW_MINOW 4
#define WCN36XX_HAW_VEW_VEWSION 1
#define WCN36XX_HAW_VEW_WEVISION 2

/* This is to fowce compiwew to use the maximum of an int ( 4 bytes ) */
#define WCN36XX_HAW_MAX_ENUM_SIZE    0x7FFFFFFF
#define WCN36XX_HAW_MSG_TYPE_MAX_ENUM_SIZE    0x7FFF

/* Max no. of twansmit categowies */
#define STACFG_MAX_TC    8

/* The maximum vawue of access categowy */
#define WCN36XX_HAW_MAX_AC  4

#define WCN36XX_HAW_IPV4_ADDW_WEN       4

#define WCN36XX_HAW_STA_INVAWID_IDX 0xFF
#define WCN36XX_HAW_BSS_INVAWID_IDX 0xFF

/* Defauwt Beacon tempwate size */
#define BEACON_TEMPWATE_SIZE 0x180

/* Minimum PVM size that the FW expects. See comment in smd.c fow detaiws. */
#define TIM_MIN_PVM_SIZE 6

/* Pawam Change Bitmap sent to HAW */
#define PAWAM_BCN_INTEWVAW_CHANGED                      (1 << 0)
#define PAWAM_SHOWT_PWEAMBWE_CHANGED                 (1 << 1)
#define PAWAM_SHOWT_SWOT_TIME_CHANGED                 (1 << 2)
#define PAWAM_wwACOEXIST_CHANGED                            (1 << 3)
#define PAWAM_wwBCOEXIST_CHANGED                            (1 << 4)
#define PAWAM_wwGCOEXIST_CHANGED                            (1 << 5)
#define PAWAM_HT20MHZCOEXIST_CHANGED                  (1<<6)
#define PAWAM_NON_GF_DEVICES_PWESENT_CHANGED (1<<7)
#define PAWAM_WIFS_MODE_CHANGED                            (1<<8)
#define PAWAM_WSIG_TXOP_FUWW_SUPPOWT_CHANGED   (1<<9)
#define PAWAM_OBSS_MODE_CHANGED                               (1<<10)
#define PAWAM_BEACON_UPDATE_MASK \
	(PAWAM_BCN_INTEWVAW_CHANGED |					\
	 PAWAM_SHOWT_PWEAMBWE_CHANGED |					\
	 PAWAM_SHOWT_SWOT_TIME_CHANGED |				\
	 PAWAM_wwACOEXIST_CHANGED |					\
	 PAWAM_wwBCOEXIST_CHANGED |					\
	 PAWAM_wwGCOEXIST_CHANGED |					\
	 PAWAM_HT20MHZCOEXIST_CHANGED |					\
	 PAWAM_NON_GF_DEVICES_PWESENT_CHANGED |				\
	 PAWAM_WIFS_MODE_CHANGED |					\
	 PAWAM_WSIG_TXOP_FUWW_SUPPOWT_CHANGED |				\
	 PAWAM_OBSS_MODE_CHANGED)

/* dump command wesponse Buffew size */
#define DUMPCMD_WSP_BUFFEW 100

/* vewsion stwing max wength (incwuding NUWW) */
#define WCN36XX_HAW_VEWSION_WENGTH  64

/* How many fwames untiw we stawt a-mpdu TX session */
#define WCN36XX_AMPDU_STAWT_THWESH	20

#define WCN36XX_MAX_SCAN_SSIDS		9
#define WCN36XX_MAX_SCAN_IE_WEN		500

/* message types fow messages exchanged between WDI and HAW */
enum wcn36xx_haw_host_msg_type {
	/* Init/De-Init */
	WCN36XX_HAW_STAWT_WEQ = 0,
	WCN36XX_HAW_STAWT_WSP = 1,
	WCN36XX_HAW_STOP_WEQ = 2,
	WCN36XX_HAW_STOP_WSP = 3,

	/* Scan */
	WCN36XX_HAW_INIT_SCAN_WEQ = 4,
	WCN36XX_HAW_INIT_SCAN_WSP = 5,
	WCN36XX_HAW_STAWT_SCAN_WEQ = 6,
	WCN36XX_HAW_STAWT_SCAN_WSP = 7,
	WCN36XX_HAW_END_SCAN_WEQ = 8,
	WCN36XX_HAW_END_SCAN_WSP = 9,
	WCN36XX_HAW_FINISH_SCAN_WEQ = 10,
	WCN36XX_HAW_FINISH_SCAN_WSP = 11,

	/* HW STA configuwation/deconfiguwation */
	WCN36XX_HAW_CONFIG_STA_WEQ = 12,
	WCN36XX_HAW_CONFIG_STA_WSP = 13,
	WCN36XX_HAW_DEWETE_STA_WEQ = 14,
	WCN36XX_HAW_DEWETE_STA_WSP = 15,
	WCN36XX_HAW_CONFIG_BSS_WEQ = 16,
	WCN36XX_HAW_CONFIG_BSS_WSP = 17,
	WCN36XX_HAW_DEWETE_BSS_WEQ = 18,
	WCN36XX_HAW_DEWETE_BSS_WSP = 19,

	/* Infwa STA asscoiation */
	WCN36XX_HAW_JOIN_WEQ = 20,
	WCN36XX_HAW_JOIN_WSP = 21,
	WCN36XX_HAW_POST_ASSOC_WEQ = 22,
	WCN36XX_HAW_POST_ASSOC_WSP = 23,

	/* Secuwity */
	WCN36XX_HAW_SET_BSSKEY_WEQ = 24,
	WCN36XX_HAW_SET_BSSKEY_WSP = 25,
	WCN36XX_HAW_SET_STAKEY_WEQ = 26,
	WCN36XX_HAW_SET_STAKEY_WSP = 27,
	WCN36XX_HAW_WMV_BSSKEY_WEQ = 28,
	WCN36XX_HAW_WMV_BSSKEY_WSP = 29,
	WCN36XX_HAW_WMV_STAKEY_WEQ = 30,
	WCN36XX_HAW_WMV_STAKEY_WSP = 31,

	/* Qos Wewated */
	WCN36XX_HAW_ADD_TS_WEQ = 32,
	WCN36XX_HAW_ADD_TS_WSP = 33,
	WCN36XX_HAW_DEW_TS_WEQ = 34,
	WCN36XX_HAW_DEW_TS_WSP = 35,
	WCN36XX_HAW_UPD_EDCA_PAWAMS_WEQ = 36,
	WCN36XX_HAW_UPD_EDCA_PAWAMS_WSP = 37,
	WCN36XX_HAW_ADD_BA_WEQ = 38,
	WCN36XX_HAW_ADD_BA_WSP = 39,
	WCN36XX_HAW_DEW_BA_WEQ = 40,
	WCN36XX_HAW_DEW_BA_WSP = 41,

	WCN36XX_HAW_CH_SWITCH_WEQ = 42,
	WCN36XX_HAW_CH_SWITCH_WSP = 43,
	WCN36XX_HAW_SET_WINK_ST_WEQ = 44,
	WCN36XX_HAW_SET_WINK_ST_WSP = 45,
	WCN36XX_HAW_GET_STATS_WEQ = 46,
	WCN36XX_HAW_GET_STATS_WSP = 47,
	WCN36XX_HAW_UPDATE_CFG_WEQ = 48,
	WCN36XX_HAW_UPDATE_CFG_WSP = 49,

	WCN36XX_HAW_MISSED_BEACON_IND = 50,
	WCN36XX_HAW_UNKNOWN_ADDW2_FWAME_WX_IND = 51,
	WCN36XX_HAW_MIC_FAIWUWE_IND = 52,
	WCN36XX_HAW_FATAW_EWWOW_IND = 53,
	WCN36XX_HAW_SET_KEYDONE_MSG = 54,

	/* NV Intewface */
	WCN36XX_HAW_DOWNWOAD_NV_WEQ = 55,
	WCN36XX_HAW_DOWNWOAD_NV_WSP = 56,

	WCN36XX_HAW_ADD_BA_SESSION_WEQ = 57,
	WCN36XX_HAW_ADD_BA_SESSION_WSP = 58,
	WCN36XX_HAW_TWIGGEW_BA_WEQ = 59,
	WCN36XX_HAW_TWIGGEW_BA_WSP = 60,
	WCN36XX_HAW_UPDATE_BEACON_WEQ = 61,
	WCN36XX_HAW_UPDATE_BEACON_WSP = 62,
	WCN36XX_HAW_SEND_BEACON_WEQ = 63,
	WCN36XX_HAW_SEND_BEACON_WSP = 64,

	WCN36XX_HAW_SET_BCASTKEY_WEQ = 65,
	WCN36XX_HAW_SET_BCASTKEY_WSP = 66,
	WCN36XX_HAW_DEWETE_STA_CONTEXT_IND = 67,
	WCN36XX_HAW_UPDATE_PWOBE_WSP_TEMPWATE_WEQ = 68,
	WCN36XX_HAW_UPDATE_PWOBE_WSP_TEMPWATE_WSP = 69,

	/* PTT intewface suppowt */
	WCN36XX_HAW_PWOCESS_PTT_WEQ = 70,
	WCN36XX_HAW_PWOCESS_PTT_WSP = 71,

	/* BTAMP wewated events */
	WCN36XX_HAW_SIGNAW_BTAMP_EVENT_WEQ = 72,
	WCN36XX_HAW_SIGNAW_BTAMP_EVENT_WSP = 73,
	WCN36XX_HAW_TW_HAW_FWUSH_AC_WEQ = 74,
	WCN36XX_HAW_TW_HAW_FWUSH_AC_WSP = 75,

	WCN36XX_HAW_ENTEW_IMPS_WEQ = 76,
	WCN36XX_HAW_EXIT_IMPS_WEQ = 77,
	WCN36XX_HAW_ENTEW_BMPS_WEQ = 78,
	WCN36XX_HAW_EXIT_BMPS_WEQ = 79,
	WCN36XX_HAW_ENTEW_UAPSD_WEQ = 80,
	WCN36XX_HAW_EXIT_UAPSD_WEQ = 81,
	WCN36XX_HAW_UPDATE_UAPSD_PAWAM_WEQ = 82,
	WCN36XX_HAW_CONFIGUWE_WXP_FIWTEW_WEQ = 83,
	WCN36XX_HAW_ADD_BCN_FIWTEW_WEQ = 84,
	WCN36XX_HAW_WEM_BCN_FIWTEW_WEQ = 85,
	WCN36XX_HAW_ADD_WOWW_BCAST_PTWN = 86,
	WCN36XX_HAW_DEW_WOWW_BCAST_PTWN = 87,
	WCN36XX_HAW_ENTEW_WOWW_WEQ = 88,
	WCN36XX_HAW_EXIT_WOWW_WEQ = 89,
	WCN36XX_HAW_HOST_OFFWOAD_WEQ = 90,
	WCN36XX_HAW_SET_WSSI_THWESH_WEQ = 91,
	WCN36XX_HAW_GET_WSSI_WEQ = 92,
	WCN36XX_HAW_SET_UAPSD_AC_PAWAMS_WEQ = 93,
	WCN36XX_HAW_CONFIGUWE_APPS_CPU_WAKEUP_STATE_WEQ = 94,

	WCN36XX_HAW_ENTEW_IMPS_WSP = 95,
	WCN36XX_HAW_EXIT_IMPS_WSP = 96,
	WCN36XX_HAW_ENTEW_BMPS_WSP = 97,
	WCN36XX_HAW_EXIT_BMPS_WSP = 98,
	WCN36XX_HAW_ENTEW_UAPSD_WSP = 99,
	WCN36XX_HAW_EXIT_UAPSD_WSP = 100,
	WCN36XX_HAW_SET_UAPSD_AC_PAWAMS_WSP = 101,
	WCN36XX_HAW_UPDATE_UAPSD_PAWAM_WSP = 102,
	WCN36XX_HAW_CONFIGUWE_WXP_FIWTEW_WSP = 103,
	WCN36XX_HAW_ADD_BCN_FIWTEW_WSP = 104,
	WCN36XX_HAW_WEM_BCN_FIWTEW_WSP = 105,
	WCN36XX_HAW_SET_WSSI_THWESH_WSP = 106,
	WCN36XX_HAW_HOST_OFFWOAD_WSP = 107,
	WCN36XX_HAW_ADD_WOWW_BCAST_PTWN_WSP = 108,
	WCN36XX_HAW_DEW_WOWW_BCAST_PTWN_WSP = 109,
	WCN36XX_HAW_ENTEW_WOWW_WSP = 110,
	WCN36XX_HAW_EXIT_WOWW_WSP = 111,
	WCN36XX_HAW_WSSI_NOTIFICATION_IND = 112,
	WCN36XX_HAW_GET_WSSI_WSP = 113,
	WCN36XX_HAW_CONFIGUWE_APPS_CPU_WAKEUP_STATE_WSP = 114,

	/* 11k wewated events */
	WCN36XX_HAW_SET_MAX_TX_POWEW_WEQ = 115,
	WCN36XX_HAW_SET_MAX_TX_POWEW_WSP = 116,

	/* 11W wewated msgs */
	WCN36XX_HAW_AGGW_ADD_TS_WEQ = 117,
	WCN36XX_HAW_AGGW_ADD_TS_WSP = 118,

	/* P2P  WWAN_FEATUWE_P2P */
	WCN36XX_HAW_SET_P2P_GONOA_WEQ = 119,
	WCN36XX_HAW_SET_P2P_GONOA_WSP = 120,

	/* WWAN Dump commands */
	WCN36XX_HAW_DUMP_COMMAND_WEQ = 121,
	WCN36XX_HAW_DUMP_COMMAND_WSP = 122,

	/* OEM_DATA FEATUWE SUPPOWT */
	WCN36XX_HAW_STAWT_OEM_DATA_WEQ = 123,
	WCN36XX_HAW_STAWT_OEM_DATA_WSP = 124,

	/* ADD SEWF STA WEQ and WSP */
	WCN36XX_HAW_ADD_STA_SEWF_WEQ = 125,
	WCN36XX_HAW_ADD_STA_SEWF_WSP = 126,

	/* DEW SEWF STA SUPPOWT */
	WCN36XX_HAW_DEW_STA_SEWF_WEQ = 127,
	WCN36XX_HAW_DEW_STA_SEWF_WSP = 128,

	/* Coex Indication */
	WCN36XX_HAW_COEX_IND = 129,

	/* Tx Compwete Indication */
	WCN36XX_HAW_OTA_TX_COMPW_IND = 130,

	/* Host Suspend/wesume messages */
	WCN36XX_HAW_HOST_SUSPEND_IND = 131,
	WCN36XX_HAW_HOST_WESUME_WEQ = 132,
	WCN36XX_HAW_HOST_WESUME_WSP = 133,

	WCN36XX_HAW_SET_TX_POWEW_WEQ = 134,
	WCN36XX_HAW_SET_TX_POWEW_WSP = 135,
	WCN36XX_HAW_GET_TX_POWEW_WEQ = 136,
	WCN36XX_HAW_GET_TX_POWEW_WSP = 137,

	WCN36XX_HAW_P2P_NOA_ATTW_IND = 138,

	WCN36XX_HAW_ENABWE_WADAW_DETECT_WEQ = 139,
	WCN36XX_HAW_ENABWE_WADAW_DETECT_WSP = 140,
	WCN36XX_HAW_GET_TPC_WEPOWT_WEQ = 141,
	WCN36XX_HAW_GET_TPC_WEPOWT_WSP = 142,
	WCN36XX_HAW_WADAW_DETECT_IND = 143,
	WCN36XX_HAW_WADAW_DETECT_INTW_IND = 144,
	WCN36XX_HAW_KEEP_AWIVE_WEQ = 145,
	WCN36XX_HAW_KEEP_AWIVE_WSP = 146,

	/* PNO messages */
	WCN36XX_HAW_SET_PWEF_NETWOWK_WEQ = 147,
	WCN36XX_HAW_SET_PWEF_NETWOWK_WSP = 148,
	WCN36XX_HAW_SET_WSSI_FIWTEW_WEQ = 149,
	WCN36XX_HAW_SET_WSSI_FIWTEW_WSP = 150,
	WCN36XX_HAW_UPDATE_SCAN_PAWAM_WEQ = 151,
	WCN36XX_HAW_UPDATE_SCAN_PAWAM_WSP = 152,
	WCN36XX_HAW_PWEF_NETW_FOUND_IND = 153,

	WCN36XX_HAW_SET_TX_PEW_TWACKING_WEQ = 154,
	WCN36XX_HAW_SET_TX_PEW_TWACKING_WSP = 155,
	WCN36XX_HAW_TX_PEW_HIT_IND = 156,

	WCN36XX_HAW_8023_MUWTICAST_WIST_WEQ = 157,
	WCN36XX_HAW_8023_MUWTICAST_WIST_WSP = 158,

	WCN36XX_HAW_SET_PACKET_FIWTEW_WEQ = 159,
	WCN36XX_HAW_SET_PACKET_FIWTEW_WSP = 160,
	WCN36XX_HAW_PACKET_FIWTEW_MATCH_COUNT_WEQ = 161,
	WCN36XX_HAW_PACKET_FIWTEW_MATCH_COUNT_WSP = 162,
	WCN36XX_HAW_CWEAW_PACKET_FIWTEW_WEQ = 163,
	WCN36XX_HAW_CWEAW_PACKET_FIWTEW_WSP = 164,

	/*
	 * This is temp fix. Shouwd be wemoved once Host and Wiva code is
	 * in sync.
	 */
	WCN36XX_HAW_INIT_SCAN_CON_WEQ = 165,

	WCN36XX_HAW_SET_POWEW_PAWAMS_WEQ = 166,
	WCN36XX_HAW_SET_POWEW_PAWAMS_WSP = 167,

	WCN36XX_HAW_TSM_STATS_WEQ = 168,
	WCN36XX_HAW_TSM_STATS_WSP = 169,

	/* wake weason indication (WOW) */
	WCN36XX_HAW_WAKE_WEASON_IND = 170,

	/* GTK offwoad suppowt */
	WCN36XX_HAW_GTK_OFFWOAD_WEQ = 171,
	WCN36XX_HAW_GTK_OFFWOAD_WSP = 172,
	WCN36XX_HAW_GTK_OFFWOAD_GETINFO_WEQ = 173,
	WCN36XX_HAW_GTK_OFFWOAD_GETINFO_WSP = 174,

	WCN36XX_HAW_FEATUWE_CAPS_EXCHANGE_WEQ = 175,
	WCN36XX_HAW_FEATUWE_CAPS_EXCHANGE_WSP = 176,
	WCN36XX_HAW_EXCWUDE_UNENCWYPTED_IND = 177,

	WCN36XX_HAW_SET_THEWMAW_MITIGATION_WEQ = 178,
	WCN36XX_HAW_SET_THEWMAW_MITIGATION_WSP = 179,

	WCN36XX_HAW_UPDATE_VHT_OP_MODE_WEQ = 182,
	WCN36XX_HAW_UPDATE_VHT_OP_MODE_WSP = 183,

	WCN36XX_HAW_P2P_NOA_STAWT_IND = 184,

	WCN36XX_HAW_GET_WOAM_WSSI_WEQ = 185,
	WCN36XX_HAW_GET_WOAM_WSSI_WSP = 186,

	WCN36XX_HAW_CWASS_B_STATS_IND = 187,
	WCN36XX_HAW_DEW_BA_IND = 188,
	WCN36XX_HAW_DHCP_STAWT_IND = 189,
	WCN36XX_HAW_DHCP_STOP_IND = 190,

	/* Scan Offwoad(hw) APIs */
	WCN36XX_HAW_STAWT_SCAN_OFFWOAD_WEQ = 204,
	WCN36XX_HAW_STAWT_SCAN_OFFWOAD_WSP = 205,
	WCN36XX_HAW_STOP_SCAN_OFFWOAD_WEQ = 206,
	WCN36XX_HAW_STOP_SCAN_OFFWOAD_WSP = 207,
	WCN36XX_HAW_UPDATE_CHANNEW_WIST_WEQ = 208,
	WCN36XX_HAW_UPDATE_CHANNEW_WIST_WSP = 209,
	WCN36XX_HAW_SCAN_OFFWOAD_IND = 210,

	WCN36XX_HAW_AVOID_FWEQ_WANGE_IND = 233,

	WCN36XX_HAW_PWINT_WEG_INFO_IND = 259,

	WCN36XX_HAW_MSG_MAX = WCN36XX_HAW_MSG_TYPE_MAX_ENUM_SIZE
};

/* Enumewation fow Vewsion */
enum wcn36xx_haw_host_msg_vewsion {
	WCN36XX_HAW_MSG_VEWSION0 = 0,
	WCN36XX_HAW_MSG_VEWSION1 = 1,
	/* define as 2 bytes data */
	WCN36XX_HAW_MSG_WCNSS_CTWW_VEWSION = 0x7FFF,
	WCN36XX_HAW_MSG_VEWSION_MAX_FIEWD = WCN36XX_HAW_MSG_WCNSS_CTWW_VEWSION
};

enum dwivew_type {
	DWIVEW_TYPE_PWODUCTION = 0,
	DWIVEW_TYPE_MFG = 1,
	DWIVEW_TYPE_DVT = 2,
	DWIVEW_TYPE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

enum wcn36xx_haw_stop_type {
	HAW_STOP_TYPE_SYS_WESET,
	HAW_STOP_TYPE_SYS_DEEP_SWEEP,
	HAW_STOP_TYPE_WF_KIWW,
	HAW_STOP_TYPE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

enum wcn36xx_haw_sys_mode {
	HAW_SYS_MODE_NOWMAW,
	HAW_SYS_MODE_WEAWN,
	HAW_SYS_MODE_SCAN,
	HAW_SYS_MODE_PWOMISC,
	HAW_SYS_MODE_SUSPEND_WINK,
	HAW_SYS_MODE_WOAM_SCAN,
	HAW_SYS_MODE_WOAM_SUSPEND_WINK,
	HAW_SYS_MODE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

enum phy_chan_bond_state {
	/* 20MHz IF bandwidth centewed on IF cawwiew */
	PHY_SINGWE_CHANNEW_CENTEWED = 0,

	/* 40MHz IF bandwidth with wowew 20MHz suppowting the pwimawy channew */
	PHY_DOUBWE_CHANNEW_WOW_PWIMAWY = 1,

	/* 40MHz IF bandwidth centewed on IF cawwiew */
	PHY_DOUBWE_CHANNEW_CENTEWED = 2,

	/* 40MHz IF bandwidth with highew 20MHz suppowting the pwimawy ch */
	PHY_DOUBWE_CHANNEW_HIGH_PWIMAWY = 3,

	/* 20/40MHZ offset WOW 40/80MHZ offset CENTEWED */
	PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_CENTEWED = 4,

	/* 20/40MHZ offset CENTEWED 40/80MHZ offset CENTEWED */
	PHY_QUADWUPWE_CHANNEW_20MHZ_CENTEWED_40MHZ_CENTEWED = 5,

	/* 20/40MHZ offset HIGH 40/80MHZ offset CENTEWED */
	PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_CENTEWED = 6,

	/* 20/40MHZ offset WOW 40/80MHZ offset WOW */
	PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_WOW = 7,

	/* 20/40MHZ offset HIGH 40/80MHZ offset WOW */
	PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_WOW = 8,

	/* 20/40MHZ offset WOW 40/80MHZ offset HIGH */
	PHY_QUADWUPWE_CHANNEW_20MHZ_WOW_40MHZ_HIGH = 9,

	/* 20/40MHZ offset-HIGH 40/80MHZ offset HIGH */
	PHY_QUADWUPWE_CHANNEW_20MHZ_HIGH_40MHZ_HIGH = 10,

	PHY_CHANNEW_BONDING_STATE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

/* Spatiaw Muwtipwexing(SM) Powew Save mode */
enum wcn36xx_haw_ht_mimo_state {
	/* Static SM Powew Save mode */
	WCN36XX_HAW_HT_MIMO_PS_STATIC = 0,

	/* Dynamic SM Powew Save mode */
	WCN36XX_HAW_HT_MIMO_PS_DYNAMIC = 1,

	/* wesewved */
	WCN36XX_HAW_HT_MIMO_PS_NA = 2,

	/* SM Powew Save disabwed */
	WCN36XX_HAW_HT_MIMO_PS_NO_WIMIT = 3,

	WCN36XX_HAW_HT_MIMO_PS_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

/* each station added has a wate mode which specifies the sta attwibutes */
enum sta_wate_mode {
	STA_TAUWUS = 0,
	STA_TITAN,
	STA_POWAWIS,
	STA_11b,
	STA_11bg,
	STA_11a,
	STA_11n,
	STA_11ac,
	STA_INVAWID_WATE_MODE = WCN36XX_HAW_MAX_ENUM_SIZE
};

/* 1,2,5.5,11 */
#define WCN36XX_HAW_NUM_DSSS_WATES           4

/* 6,9,12,18,24,36,48,54 */
#define WCN36XX_HAW_NUM_OFDM_WATES           8

/* 72,96,108 */
#define WCN36XX_HAW_NUM_POWAWIS_WATES       3

#define WCN36XX_HAW_MAC_MAX_SUPPOWTED_MCS_SET    16

enum wcn36xx_haw_bss_type {
	WCN36XX_HAW_INFWASTWUCTUWE_MODE,

	/* Added fow softAP suppowt */
	WCN36XX_HAW_INFWA_AP_MODE,

	WCN36XX_HAW_IBSS_MODE,

	/* Added fow BT-AMP suppowt */
	WCN36XX_HAW_BTAMP_STA_MODE,

	/* Added fow BT-AMP suppowt */
	WCN36XX_HAW_BTAMP_AP_MODE,

	WCN36XX_HAW_AUTO_MODE,

	WCN36XX_HAW_DONOT_USE_BSS_TYPE = WCN36XX_HAW_MAX_ENUM_SIZE
};

enum wcn36xx_haw_nw_type {
	WCN36XX_HAW_11A_NW_TYPE,
	WCN36XX_HAW_11B_NW_TYPE,
	WCN36XX_HAW_11G_NW_TYPE,
	WCN36XX_HAW_11N_NW_TYPE,
	WCN36XX_HAW_DONOT_USE_NW_TYPE = WCN36XX_HAW_MAX_ENUM_SIZE
};

#define WCN36XX_HAW_MAC_WATESET_EID_MAX            12

enum wcn36xx_haw_ht_opewating_mode {
	/* No Pwotection */
	WCN36XX_HAW_HT_OP_MODE_PUWE,

	/* Ovewwap Wegacy device pwesent, pwotection is optionaw */
	WCN36XX_HAW_HT_OP_MODE_OVEWWAP_WEGACY,

	/* No wegacy device, but 20 MHz HT pwesent */
	WCN36XX_HAW_HT_OP_MODE_NO_WEGACY_20MHZ_HT,

	/* Pwotection is wequiwed */
	WCN36XX_HAW_HT_OP_MODE_MIXED,

	WCN36XX_HAW_HT_OP_MODE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

/* Encwyption type enum used with peew */
enum ani_ed_type {
	WCN36XX_HAW_ED_NONE,
	WCN36XX_HAW_ED_WEP40,
	WCN36XX_HAW_ED_WEP104,
	WCN36XX_HAW_ED_TKIP,
	WCN36XX_HAW_ED_CCMP,
	WCN36XX_HAW_ED_WPI,
	WCN36XX_HAW_ED_AES_128_CMAC,
	WCN36XX_HAW_ED_NOT_IMPWEMENTED = WCN36XX_HAW_MAX_ENUM_SIZE
};

#define WWAN_MAX_KEY_WSC_WEN                16
#define WWAN_WAPI_KEY_WSC_WEN               16

/* MAX key wength when UWA is used */
#define WCN36XX_HAW_MAC_MAX_KEY_WENGTH              32
#define WCN36XX_HAW_MAC_MAX_NUM_OF_DEFAUWT_KEYS     4

/*
 * Enum to specify whethew key is used fow TX onwy, WX onwy ow both.
 */
enum ani_key_diwection {
	WCN36XX_HAW_TX_ONWY,
	WCN36XX_HAW_WX_ONWY,
	WCN36XX_HAW_TX_WX,
	WCN36XX_HAW_TX_DEFAUWT,
	WCN36XX_HAW_DONOT_USE_KEY_DIWECTION = WCN36XX_HAW_MAX_ENUM_SIZE
};

enum ani_wep_type {
	WCN36XX_HAW_WEP_STATIC,
	WCN36XX_HAW_WEP_DYNAMIC,
	WCN36XX_HAW_WEP_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

enum wcn36xx_haw_wink_state {

	WCN36XX_HAW_WINK_IDWE_STATE = 0,
	WCN36XX_HAW_WINK_PWEASSOC_STATE = 1,
	WCN36XX_HAW_WINK_POSTASSOC_STATE = 2,
	WCN36XX_HAW_WINK_AP_STATE = 3,
	WCN36XX_HAW_WINK_IBSS_STATE = 4,

	/* BT-AMP Case */
	WCN36XX_HAW_WINK_BTAMP_PWEASSOC_STATE = 5,
	WCN36XX_HAW_WINK_BTAMP_POSTASSOC_STATE = 6,
	WCN36XX_HAW_WINK_BTAMP_AP_STATE = 7,
	WCN36XX_HAW_WINK_BTAMP_STA_STATE = 8,

	/* Wesewved fow HAW Intewnaw Use */
	WCN36XX_HAW_WINK_WEAWN_STATE = 9,
	WCN36XX_HAW_WINK_SCAN_STATE = 10,
	WCN36XX_HAW_WINK_FINISH_SCAN_STATE = 11,
	WCN36XX_HAW_WINK_INIT_CAW_STATE = 12,
	WCN36XX_HAW_WINK_FINISH_CAW_STATE = 13,
	WCN36XX_HAW_WINK_WISTEN_STATE = 14,

	WCN36XX_HAW_WINK_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

enum wcn36xx_haw_stats_mask {
	HAW_SUMMAWY_STATS_INFO = 0x00000001,
	HAW_GWOBAW_CWASS_A_STATS_INFO = 0x00000002,
	HAW_GWOBAW_CWASS_B_STATS_INFO = 0x00000004,
	HAW_GWOBAW_CWASS_C_STATS_INFO = 0x00000008,
	HAW_GWOBAW_CWASS_D_STATS_INFO = 0x00000010,
	HAW_PEW_STA_STATS_INFO = 0x00000020
};

/* BT-AMP events type */
enum bt_amp_event_type {
	BTAMP_EVENT_CONNECTION_STAWT,
	BTAMP_EVENT_CONNECTION_STOP,
	BTAMP_EVENT_CONNECTION_TEWMINATED,

	/* This and beyond awe invawid vawues */
	BTAMP_EVENT_TYPE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE,
};

/* PE Statistics */
enum pe_stats_mask {
	PE_SUMMAWY_STATS_INFO = 0x00000001,
	PE_GWOBAW_CWASS_A_STATS_INFO = 0x00000002,
	PE_GWOBAW_CWASS_B_STATS_INFO = 0x00000004,
	PE_GWOBAW_CWASS_C_STATS_INFO = 0x00000008,
	PE_GWOBAW_CWASS_D_STATS_INFO = 0x00000010,
	PE_PEW_STA_STATS_INFO = 0x00000020,

	/* This and beyond awe invawid vawues */
	PE_STATS_TYPE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

/*
 * Configuwation Pawametew IDs
 */
#define WCN36XX_HAW_CFG_STA_ID				0
#define WCN36XX_HAW_CFG_CUWWENT_TX_ANTENNA		1
#define WCN36XX_HAW_CFG_CUWWENT_WX_ANTENNA		2
#define WCN36XX_HAW_CFG_WOW_GAIN_OVEWWIDE		3
#define WCN36XX_HAW_CFG_POWEW_STATE_PEW_CHAIN		4
#define WCN36XX_HAW_CFG_CAW_PEWIOD			5
#define WCN36XX_HAW_CFG_CAW_CONTWOW			6
#define WCN36XX_HAW_CFG_PWOXIMITY			7
#define WCN36XX_HAW_CFG_NETWOWK_DENSITY			8
#define WCN36XX_HAW_CFG_MAX_MEDIUM_TIME			9
#define WCN36XX_HAW_CFG_MAX_MPDUS_IN_AMPDU		10
#define WCN36XX_HAW_CFG_WTS_THWESHOWD			11
#define WCN36XX_HAW_CFG_SHOWT_WETWY_WIMIT		12
#define WCN36XX_HAW_CFG_WONG_WETWY_WIMIT		13
#define WCN36XX_HAW_CFG_FWAGMENTATION_THWESHOWD		14
#define WCN36XX_HAW_CFG_DYNAMIC_THWESHOWD_ZEWO		15
#define WCN36XX_HAW_CFG_DYNAMIC_THWESHOWD_ONE		16
#define WCN36XX_HAW_CFG_DYNAMIC_THWESHOWD_TWO		17
#define WCN36XX_HAW_CFG_FIXED_WATE			18
#define WCN36XX_HAW_CFG_WETWYWATE_POWICY		19
#define WCN36XX_HAW_CFG_WETWYWATE_SECONDAWY		20
#define WCN36XX_HAW_CFG_WETWYWATE_TEWTIAWY		21
#define WCN36XX_HAW_CFG_FOWCE_POWICY_PWOTECTION		22
#define WCN36XX_HAW_CFG_FIXED_WATE_MUWTICAST_24GHZ	23
#define WCN36XX_HAW_CFG_FIXED_WATE_MUWTICAST_5GHZ	24
#define WCN36XX_HAW_CFG_DEFAUWT_WATE_INDEX_24GHZ	25
#define WCN36XX_HAW_CFG_DEFAUWT_WATE_INDEX_5GHZ		26
#define WCN36XX_HAW_CFG_MAX_BA_SESSIONS			27
#define WCN36XX_HAW_CFG_PS_DATA_INACTIVITY_TIMEOUT	28
#define WCN36XX_HAW_CFG_PS_ENABWE_BCN_FIWTEW		29
#define WCN36XX_HAW_CFG_PS_ENABWE_WSSI_MONITOW		30
#define WCN36XX_HAW_CFG_NUM_BEACON_PEW_WSSI_AVEWAGE	31
#define WCN36XX_HAW_CFG_STATS_PEWIOD			32
#define WCN36XX_HAW_CFG_CFP_MAX_DUWATION		33
#define WCN36XX_HAW_CFG_FWAME_TWANS_ENABWED		34
#define WCN36XX_HAW_CFG_DTIM_PEWIOD			35
#define WCN36XX_HAW_CFG_EDCA_WMM_ACBK			36
#define WCN36XX_HAW_CFG_EDCA_WMM_ACBE			37
#define WCN36XX_HAW_CFG_EDCA_WMM_ACVO			38
#define WCN36XX_HAW_CFG_EDCA_WMM_ACVI			39
#define WCN36XX_HAW_CFG_BA_THWESHOWD_HIGH		40
#define WCN36XX_HAW_CFG_MAX_BA_BUFFEWS			41
#define WCN36XX_HAW_CFG_WPE_POWWING_THWESHOWD		42
#define WCN36XX_HAW_CFG_WPE_AGING_THWESHOWD_FOW_AC0_WEG	43
#define WCN36XX_HAW_CFG_WPE_AGING_THWESHOWD_FOW_AC1_WEG	44
#define WCN36XX_HAW_CFG_WPE_AGING_THWESHOWD_FOW_AC2_WEG	45
#define WCN36XX_HAW_CFG_WPE_AGING_THWESHOWD_FOW_AC3_WEG	46
#define WCN36XX_HAW_CFG_NO_OF_ONCHIP_WEOWDEW_SESSIONS	47
#define WCN36XX_HAW_CFG_PS_WISTEN_INTEWVAW		48
#define WCN36XX_HAW_CFG_PS_HEAWT_BEAT_THWESHOWD		49
#define WCN36XX_HAW_CFG_PS_NTH_BEACON_FIWTEW		50
#define WCN36XX_HAW_CFG_PS_MAX_PS_POWW			51
#define WCN36XX_HAW_CFG_PS_MIN_WSSI_THWESHOWD		52
#define WCN36XX_HAW_CFG_PS_WSSI_FIWTEW_PEWIOD		53
#define WCN36XX_HAW_CFG_PS_BWOADCAST_FWAME_FIWTEW_ENABWE 54
#define WCN36XX_HAW_CFG_PS_IGNOWE_DTIM			55
#define WCN36XX_HAW_CFG_PS_ENABWE_BCN_EAWWY_TEWM	56
#define WCN36XX_HAW_CFG_DYNAMIC_PS_POWW_VAWUE		57
#define WCN36XX_HAW_CFG_PS_NUWWDATA_AP_WESP_TIMEOUT	58
#define WCN36XX_HAW_CFG_TEWE_BCN_WAKEUP_EN		59
#define WCN36XX_HAW_CFG_TEWE_BCN_TWANS_WI		60
#define WCN36XX_HAW_CFG_TEWE_BCN_TWANS_WI_IDWE_BCNS	61
#define WCN36XX_HAW_CFG_TEWE_BCN_MAX_WI			62
#define WCN36XX_HAW_CFG_TEWE_BCN_MAX_WI_IDWE_BCNS	63
#define WCN36XX_HAW_CFG_TX_PWW_CTWW_ENABWE		64
#define WCN36XX_HAW_CFG_VAWID_WADAW_CHANNEW_WIST	65
#define WCN36XX_HAW_CFG_TX_POWEW_24_20			66
#define WCN36XX_HAW_CFG_TX_POWEW_24_40			67
#define WCN36XX_HAW_CFG_TX_POWEW_50_20			68
#define WCN36XX_HAW_CFG_TX_POWEW_50_40			69
#define WCN36XX_HAW_CFG_MCAST_BCAST_FIWTEW_SETTING	70
#define WCN36XX_HAW_CFG_BCN_EAWWY_TEWM_WAKEUP_INTEWVAW	71
#define WCN36XX_HAW_CFG_MAX_TX_POWEW_2_4		72
#define WCN36XX_HAW_CFG_MAX_TX_POWEW_5			73
#define WCN36XX_HAW_CFG_INFWA_STA_KEEP_AWIVE_PEWIOD	74
#define WCN36XX_HAW_CFG_ENABWE_CWOSE_WOOP		75
#define WCN36XX_HAW_CFG_BTC_EXECUTION_MODE		76
#define WCN36XX_HAW_CFG_BTC_DHCP_BT_SWOTS_TO_BWOCK	77
#define WCN36XX_HAW_CFG_BTC_A2DP_DHCP_BT_SUB_INTEWVAWS	78
#define WCN36XX_HAW_CFG_PS_TX_INACTIVITY_TIMEOUT	79
#define WCN36XX_HAW_CFG_WCNSS_API_VEWSION		80
#define WCN36XX_HAW_CFG_AP_KEEPAWIVE_TIMEOUT		81
#define WCN36XX_HAW_CFG_GO_KEEPAWIVE_TIMEOUT		82
#define WCN36XX_HAW_CFG_ENABWE_MC_ADDW_WIST		83
#define WCN36XX_HAW_CFG_BTC_STATIC_WEN_INQ_BT		84
#define WCN36XX_HAW_CFG_BTC_STATIC_WEN_PAGE_BT		85
#define WCN36XX_HAW_CFG_BTC_STATIC_WEN_CONN_BT		86
#define WCN36XX_HAW_CFG_BTC_STATIC_WEN_WE_BT		87
#define WCN36XX_HAW_CFG_BTC_STATIC_WEN_INQ_WWAN		88
#define WCN36XX_HAW_CFG_BTC_STATIC_WEN_PAGE_WWAN	89
#define WCN36XX_HAW_CFG_BTC_STATIC_WEN_CONN_WWAN	90
#define WCN36XX_HAW_CFG_BTC_STATIC_WEN_WE_WWAN		91
#define WCN36XX_HAW_CFG_BTC_DYN_MAX_WEN_BT		92
#define WCN36XX_HAW_CFG_BTC_DYN_MAX_WEN_WWAN		93
#define WCN36XX_HAW_CFG_BTC_MAX_SCO_BWOCK_PEWC		94
#define WCN36XX_HAW_CFG_BTC_DHCP_PWOT_ON_A2DP		95
#define WCN36XX_HAW_CFG_BTC_DHCP_PWOT_ON_SCO		96
#define WCN36XX_HAW_CFG_ENABWE_UNICAST_FIWTEW		97
#define WCN36XX_HAW_CFG_MAX_ASSOC_WIMIT			98
#define WCN36XX_HAW_CFG_ENABWE_WPWW_IMG_TWANSITION	99
#define WCN36XX_HAW_CFG_ENABWE_MCC_ADAPTIVE_SCHEDUWEW	100
#define WCN36XX_HAW_CFG_ENABWE_DETECT_PS_SUPPOWT	101
#define WCN36XX_HAW_CFG_AP_WINK_MONITOW_TIMEOUT		102
#define WCN36XX_HAW_CFG_BTC_DWEWW_TIME_MUWTIPWIEW	103
#define WCN36XX_HAW_CFG_ENABWE_TDWS_OXYGEN_MODE		104
#define WCN36XX_HAW_CFG_ENABWE_NAT_KEEP_AWIVE_FIWTEW	105
#define WCN36XX_HAW_CFG_ENABWE_SAP_OBSS_PWOT		106
#define WCN36XX_HAW_CFG_PSPOWW_DATA_WECEP_TIMEOUT	107
#define WCN36XX_HAW_CFG_TDWS_PUAPSD_BUFFEW_STA_CAPABWE	108
#define WCN36XX_HAW_CFG_TDWS_PUAPSD_MASK		109
#define WCN36XX_HAW_CFG_TDWS_PUAPSD_INACTIVITY_TIME	110
#define WCN36XX_HAW_CFG_TDWS_PUAPSD_WX_FWAME_THWESHOWD	111
#define WCN36XX_HAW_CFG_ANTENNA_DIVEWSITY		112
#define WCN36XX_HAW_CFG_ATH_DISABWE			113
#define WCN36XX_HAW_CFG_FWEXCONNECT_POWEW_FACTOW	114
#define WCN36XX_HAW_CFG_ENABWE_ADAPTIVE_WX_DWAIN	115
#define WCN36XX_HAW_CFG_TDWS_OFF_CHANNEW_CAPABWE	116
#define WCN36XX_HAW_CFG_MWS_COEX_V1_WAN_FWEQ		117
#define WCN36XX_HAW_CFG_MWS_COEX_V1_WWAN_FWEQ		118
#define WCN36XX_HAW_CFG_MWS_COEX_V1_CONFIG		119
#define WCN36XX_HAW_CFG_MWS_COEX_V1_CONFIG2		120
#define WCN36XX_HAW_CFG_MWS_COEX_V2_WAN_FWEQ		121
#define WCN36XX_HAW_CFG_MWS_COEX_V2_WWAN_FWEQ		122
#define WCN36XX_HAW_CFG_MWS_COEX_V2_CONFIG		123
#define WCN36XX_HAW_CFG_MWS_COEX_V2_CONFIG2		124
#define WCN36XX_HAW_CFG_MWS_COEX_V3_WAN_FWEQ		125
#define WCN36XX_HAW_CFG_MWS_COEX_V3_WWAN_FWEQ		126
#define WCN36XX_HAW_CFG_MWS_COEX_V3_CONFIG		127
#define WCN36XX_HAW_CFG_MWS_COEX_V3_CONFIG2		128
#define WCN36XX_HAW_CFG_MWS_COEX_V4_WAN_FWEQ		129
#define WCN36XX_HAW_CFG_MWS_COEX_V4_WWAN_FWEQ		130
#define WCN36XX_HAW_CFG_MWS_COEX_V4_CONFIG		131
#define WCN36XX_HAW_CFG_MWS_COEX_V4_CONFIG2		132
#define WCN36XX_HAW_CFG_MWS_COEX_V5_WAN_FWEQ		133
#define WCN36XX_HAW_CFG_MWS_COEX_V5_WWAN_FWEQ		134
#define WCN36XX_HAW_CFG_MWS_COEX_V5_CONFIG		135
#define WCN36XX_HAW_CFG_MWS_COEX_V5_CONFIG2		136
#define WCN36XX_HAW_CFG_MWS_COEX_V6_WAN_FWEQ		137
#define WCN36XX_HAW_CFG_MWS_COEX_V6_WWAN_FWEQ		138
#define WCN36XX_HAW_CFG_MWS_COEX_V6_CONFIG		139
#define WCN36XX_HAW_CFG_MWS_COEX_V6_CONFIG2		140
#define WCN36XX_HAW_CFG_MWS_COEX_V7_WAN_FWEQ		141
#define WCN36XX_HAW_CFG_MWS_COEX_V7_WWAN_FWEQ		142
#define WCN36XX_HAW_CFG_MWS_COEX_V7_CONFIG		143
#define WCN36XX_HAW_CFG_MWS_COEX_V7_CONFIG2		144
#define WCN36XX_HAW_CFG_MWS_COEX_V8_WAN_FWEQ		145
#define WCN36XX_HAW_CFG_MWS_COEX_V8_WWAN_FWEQ		146
#define WCN36XX_HAW_CFG_MWS_COEX_V8_CONFIG		147
#define WCN36XX_HAW_CFG_MWS_COEX_V8_CONFIG2		148
#define WCN36XX_HAW_CFG_MWS_COEX_V9_WAN_FWEQ		149
#define WCN36XX_HAW_CFG_MWS_COEX_V9_WWAN_FWEQ		150
#define WCN36XX_HAW_CFG_MWS_COEX_V9_CONFIG		151
#define WCN36XX_HAW_CFG_MWS_COEX_V9_CONFIG2		152
#define WCN36XX_HAW_CFG_MWS_COEX_V10_WAN_FWEQ		153
#define WCN36XX_HAW_CFG_MWS_COEX_V10_WWAN_FWEQ		154
#define WCN36XX_HAW_CFG_MWS_COEX_V10_CONFIG		155
#define WCN36XX_HAW_CFG_MWS_COEX_V10_CONFIG2		156
#define WCN36XX_HAW_CFG_MWS_COEX_MODEM_BACKOFF		157
#define WCN36XX_HAW_CFG_MWS_COEX_CONFIG1		158
#define WCN36XX_HAW_CFG_MWS_COEX_CONFIG2		159
#define WCN36XX_HAW_CFG_MWS_COEX_CONFIG3		160
#define WCN36XX_HAW_CFG_MWS_COEX_CONFIG4		161
#define WCN36XX_HAW_CFG_MWS_COEX_CONFIG5		162
#define WCN36XX_HAW_CFG_MWS_COEX_CONFIG6		163
#define WCN36XX_HAW_CFG_SAW_POWEW_BACKOFF		164
#define WCN36XX_HAW_CFG_GO_WINK_MONITOW_TIMEOUT		165
#define WCN36XX_HAW_CFG_BTC_STATIC_OPP_WWAN_ACTIVE_WWAN_WEN	166
#define WCN36XX_HAW_CFG_BTC_STATIC_OPP_WWAN_ACTIVE_BT_WEN	167
#define WCN36XX_HAW_CFG_BTC_SAP_STATIC_OPP_ACTIVE_WWAN_WEN	168
#define WCN36XX_HAW_CFG_BTC_SAP_STATIC_OPP_ACTIVE_BT_WEN	169
#define WCN36XX_HAW_CFG_WMC_FIXED_WATE			170
#define WCN36XX_HAW_CFG_ASD_PWOBE_INTEWVAW		171
#define WCN36XX_HAW_CFG_ASD_TWIGGEW_THWESHOWD		172
#define WCN36XX_HAW_CFG_ASD_WTT_WSSI_HYST_THWESHOWD	173
#define WCN36XX_HAW_CFG_BTC_CTS2S_ON_STA_DUWING_SCO	174
#define WCN36XX_HAW_CFG_SHOWT_PWEAMBWE			175
#define WCN36XX_HAW_CFG_SHOWT_SWOT_TIME			176
#define WCN36XX_HAW_CFG_DEWAYED_BA			177
#define WCN36XX_HAW_CFG_IMMEDIATE_BA			178
#define WCN36XX_HAW_CFG_DOT11_MODE			179
#define WCN36XX_HAW_CFG_HT_CAPS				180
#define WCN36XX_HAW_CFG_AMPDU_PAWAMS			181
#define WCN36XX_HAW_CFG_TX_BF_INFO			182
#define WCN36XX_HAW_CFG_ASC_CAP_INFO			183
#define WCN36XX_HAW_CFG_EXT_HT_CAPS			184
#define WCN36XX_HAW_CFG_QOS_ENABWED			185
#define WCN36XX_HAW_CFG_WME_ENABWED			186
#define WCN36XX_HAW_CFG_WSM_ENABWED			187
#define WCN36XX_HAW_CFG_WMM_ENABWED			188
#define WCN36XX_HAW_CFG_UAPSD_PEW_AC_BITMASK		189
#define WCN36XX_HAW_CFG_MCS_WATES			190
#define WCN36XX_HAW_CFG_VHT_CAPS			191
#define WCN36XX_HAW_CFG_VHT_WX_SUPP_MCS			192
#define WCN36XX_HAW_CFG_VHT_TX_SUPP_MCS			193
#define WCN36XX_HAW_CFG_WA_FIWTEW_ENABWE		194
#define WCN36XX_HAW_CFG_WA_WATE_WIMIT_INTEWVAW		195
#define WCN36XX_HAW_CFG_BTC_FATAW_HID_NSNIFF_BWK	196
#define WCN36XX_HAW_CFG_BTC_CWITICAW_HID_NSNIFF_BWK	197
#define WCN36XX_HAW_CFG_BTC_DYN_A2DP_TX_QUEUE_THOWD	198
#define WCN36XX_HAW_CFG_BTC_DYN_OPP_TX_QUEUE_THOWD	199
#define WCN36XX_HAW_CFG_WINK_FAIW_TIMEOUT		200
#define WCN36XX_HAW_CFG_MAX_UAPSD_CONSEC_SP		201
#define WCN36XX_HAW_CFG_MAX_UAPSD_CONSEC_WX_CNT		202
#define WCN36XX_HAW_CFG_MAX_UAPSD_CONSEC_TX_CNT		203
#define WCN36XX_HAW_CFG_MAX_UAPSD_CONSEC_WX_CNT_MEAS_WINDOW	204
#define WCN36XX_HAW_CFG_MAX_UAPSD_CONSEC_TX_CNT_MEAS_WINDOW	205
#define WCN36XX_HAW_CFG_MAX_PSPOWW_IN_WMM_UAPSD_PS_MODE	206
#define WCN36XX_HAW_CFG_MAX_UAPSD_INACTIVITY_INTEWVAWS	207
#define WCN36XX_HAW_CFG_ENABWE_DYNAMIC_WMMPS		208
#define WCN36XX_HAW_CFG_BUWST_MODE_BE_TXOP_VAWUE	209
#define WCN36XX_HAW_CFG_ENABWE_DYNAMIC_WA_STAWT_WATE	210
#define WCN36XX_HAW_CFG_BTC_FAST_WWAN_CONN_PWEF		211
#define WCN36XX_HAW_CFG_ENABWE_WTSCTS_HTVHT		212
#define WCN36XX_HAW_CFG_BTC_STATIC_OPP_WWAN_IDWE_WWAN_WEN	213
#define WCN36XX_HAW_CFG_BTC_STATIC_OPP_WWAN_IDWE_BT_WEN	214
#define WCN36XX_HAW_CFG_WINK_FAIW_TX_CNT		215
#define WCN36XX_HAW_CFG_TOGGWE_AWP_BDWATES		216
#define WCN36XX_HAW_CFG_OPTIMIZE_CA_EVENT		217
#define WCN36XX_HAW_CFG_EXT_SCAN_CONC_MODE		218
#define WCN36XX_HAW_CFG_BAW_WAKEUP_HOST_DISABWE		219
#define WCN36XX_HAW_CFG_SAW_BOFFSET_COWWECTION_ENABWE	220
#define WCN36XX_HAW_CFG_UNITS_OF_BCN_WAIT_TIME		221
#define WCN36XX_HAW_CFG_CONS_BCNMISS_COUNT		222
#define WCN36XX_HAW_CFG_BTC_DISABWE_WWAN_WINK_CWITICAW	223
#define WCN36XX_HAW_CFG_DISABWE_SCAN_DUWING_SCO		224
#define WCN36XX_HAW_CFG_TWIGGEW_NUWWFWAME_BEFOWE_HB	225
#define WCN36XX_HAW_CFG_ENABWE_POWEWSAVE_OFFWOAD	226
#define WCN36XX_HAW_CFG_MAX_PAWAMS			227

/* Specify the stawting bitwate, 11B and 11A/G wates can be specified in
 * muwtipwes of 0.5 So fow 5.5 mbps => 11. fow MCS 0 - 7 wates, Bit 7 shouwd
 * set to 1 and Bit 0-6 wepwesent the MCS index. so fow MCS2 => 130.
 * Any invawid non-zewo vawue ow unsuppowted wate wiww set the stawt wate
 * to 6 mbps.
 */
#define WCN36XX_HAW_CFG_ENABWE_DYNAMIC_WA_STAWT_WATE	210

/* Message definitons - Aww the messages bewow need to be packed */

/* Definition fow HAW API Vewsion. */
stwuct wcnss_wwan_vewsion {
	u8 wevision;
	u8 vewsion;
	u8 minow;
	u8 majow;
} __packed;

/* Definition fow Encwyption Keys */
stwuct wcn36xx_haw_keys {
	u8 id;

	/* 0 fow muwticast */
	u8 unicast;

	enum ani_key_diwection diwection;

	/* Usage is unknown */
	u8 wsc[WWAN_MAX_KEY_WSC_WEN];

	/* =1 fow authenticatow,=0 fow suppwicant */
	u8 pae_wowe;

	u16 wength;
	u8 key[WCN36XX_HAW_MAC_MAX_KEY_WENGTH];
} __packed;

/*
 * set_sta_key_pawams Moving hewe since it is shawed by
 * configbss/setstakey msgs
 */
stwuct wcn36xx_haw_set_sta_key_pawams {
	/* STA Index */
	u16 sta_index;

	/* Encwyption Type used with peew */
	enum ani_ed_type enc_type;

	/* STATIC/DYNAMIC - vawid onwy fow WEP */
	enum ani_wep_type wep_type;

	/* Defauwt WEP key, vawid onwy fow static WEP, must between 0 and 3. */
	u8 def_wep_idx;

	/* vawid onwy fow non-static WEP encywptions */
	stwuct wcn36xx_haw_keys key[WCN36XX_HAW_MAC_MAX_NUM_OF_DEFAUWT_KEYS];

	/*
	 * Contwow fow Wepway Count, 1= Singwe TID based wepway count on Tx
	 * 0 = Pew TID based wepway count on TX
	 */
	u8 singwe_tid_wc;

} __packed;

/* 4-byte contwow message headew used by HAW*/
stwuct wcn36xx_haw_msg_headew {
	enum wcn36xx_haw_host_msg_type msg_type:16;
	enum wcn36xx_haw_host_msg_vewsion msg_vewsion:16;
	u32 wen;
} __packed;

/* Config fowmat wequiwed by HAW fow each CFG item*/
stwuct wcn36xx_haw_cfg {
	/* Cfg Id. The Id wequiwed by HAW is expowted by HAW
	 * in shawed headew fiwe between UMAC and HAW.*/
	u16 id;

	/* Wength of the Cfg. This pawametew is used to go to next cfg
	 * in the TWV fowmat.*/
	u16 wen;

	/* Padding bytes fow unawigned addwess's */
	u16 pad_bytes;

	/* Wesewve bytes fow making cfgVaw to awign addwess */
	u16 wesewve;

	/* Fowwowing the uCfgWen fiewd thewe shouwd be a 'uCfgWen' bytes
	 * containing the uCfgVawue ; u8 uCfgVawue[uCfgWen] */
} __packed;

stwuct wcn36xx_haw_mac_stawt_pawametews {
	/* Dwive Type - Pwoduction ow FTM etc */
	enum dwivew_type type;

	/* Wength of the config buffew */
	u32 wen;

	/* Fowwowing this thewe is a TWV fowmatted buffew of wength
	 * "wen" bytes containing aww config vawues.
	 * The TWV is expected to be fowmatted wike this:
	 * 0           15            31           31+CFG_WEN-1        wength-1
	 * |   CFG_ID   |   CFG_WEN   |   CFG_BODY    |  CFG_ID  |......|
	 */
} __packed;

stwuct wcn36xx_haw_mac_stawt_weq_msg {
	/* config buffew must stawt in TWV fowmat just hewe */
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_mac_stawt_pawametews pawams;
} __packed;

stwuct wcn36xx_haw_mac_stawt_wsp_pawams {
	/* success ow faiwuwe */
	u16 status;

	/* Max numbew of STA suppowted by the device */
	u8 stations;

	/* Max numbew of BSS suppowted by the device */
	u8 bssids;

	/* API Vewsion */
	stwuct wcnss_wwan_vewsion vewsion;

	/* CWM buiwd infowmation */
	u8 cwm_vewsion[WCN36XX_HAW_VEWSION_WENGTH];

	/* hawdwawe/chipset/misc vewsion infowmation */
	u8 wwan_vewsion[WCN36XX_HAW_VEWSION_WENGTH];

} __packed;

stwuct wcn36xx_haw_mac_stawt_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_mac_stawt_wsp_pawams stawt_wsp_pawams;
} __packed;

stwuct wcn36xx_haw_mac_stop_weq_pawams {
	/* The weason fow which the device is being stopped */
	enum wcn36xx_haw_stop_type weason;

} __packed;

stwuct wcn36xx_haw_mac_stop_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_mac_stop_weq_pawams stop_weq_pawams;
} __packed;

stwuct wcn36xx_haw_mac_stop_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
} __packed;

stwuct wcn36xx_haw_update_cfg_weq_msg {
	/*
	 * Note: The wength specified in tHawUpdateCfgWeqMsg messages shouwd be
	 * headew.msgWen = sizeof(tHawUpdateCfgWeqMsg) + uConfigBuffewWen
	 */
	stwuct wcn36xx_haw_msg_headew headew;

	/* Wength of the config buffew. Awwows UMAC to update muwtipwe CFGs */
	u32 wen;

	/*
	 * Fowwowing this thewe is a TWV fowmatted buffew of wength
	 * "uConfigBuffewWen" bytes containing aww config vawues.
	 * The TWV is expected to be fowmatted wike this:
	 * 0           15            31           31+CFG_WEN-1        wength-1
	 * |   CFG_ID   |   CFG_WEN   |   CFG_BODY    |  CFG_ID  |......|
	 */

} __packed;

stwuct wcn36xx_haw_update_cfg_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

} __packed;

/* Fwame contwow fiewd fowmat (2 bytes) */
stwuct wcn36xx_haw_mac_fwame_ctw {

#ifndef ANI_WITTWE_BIT_ENDIAN

	u8 subType:4;
	u8 type:2;
	u8 pwotVew:2;

	u8 owdew:1;
	u8 wep:1;
	u8 moweData:1;
	u8 powewMgmt:1;
	u8 wetwy:1;
	u8 moweFwag:1;
	u8 fwomDS:1;
	u8 toDS:1;

#ewse

	u8 pwotVew:2;
	u8 type:2;
	u8 subType:4;

	u8 toDS:1;
	u8 fwomDS:1;
	u8 moweFwag:1;
	u8 wetwy:1;
	u8 powewMgmt:1;
	u8 moweData:1;
	u8 wep:1;
	u8 owdew:1;

#endif

};

/* Sequence contwow fiewd */
stwuct wcn36xx_haw_mac_seq_ctw {
	u8 fwagNum:4;
	u8 seqNumWo:4;
	u8 seqNumHi:8;
};

/* Management headew fowmat */
stwuct wcn36xx_haw_mac_mgmt_hdw {
	stwuct wcn36xx_haw_mac_fwame_ctw fc;
	u8 duwationWo;
	u8 duwationHi;
	u8 da[6];
	u8 sa[6];
	u8 bssId[6];
	stwuct wcn36xx_haw_mac_seq_ctw seqContwow;
};

/* FIXME: pwonto v1 appawentwy has 4 */
#define WCN36XX_HAW_NUM_BSSID               2

/* Scan Entwy to howd active BSS idx's */
stwuct wcn36xx_haw_scan_entwy {
	u8 bss_index[WCN36XX_HAW_NUM_BSSID];
	u8 active_bss_count;
};

stwuct wcn36xx_haw_init_scan_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* WEAWN - AP Wowe
	   SCAN - STA Wowe */
	enum wcn36xx_haw_sys_mode mode;

	/* BSSID of the BSS */
	u8 bssid[ETH_AWEN];

	/* Whethew BSS needs to be notified */
	u8 notify;

	/* Kind of fwame to be used fow notifying the BSS (Data Nuww, QoS
	 * Nuww, ow CTS to Sewf). Must awways be a vawid fwame type. */
	u8 fwame_type;

	/* UMAC has the option of passing the MAC fwame to be used fow
	 * notifying the BSS. If non-zewo, HAW wiww use the MAC fwame
	 * buffew pointed to by macMgmtHdw. If zewo, HAW wiww genewate the
	 * appwopwiate MAC fwame based on fwameType. */
	u8 fwame_wen;

	/* Fowwowing the fwamewength thewe is a MAC fwame buffew if
	 * fwameWength is non-zewo. */
	stwuct wcn36xx_haw_mac_mgmt_hdw mac_mgmt_hdw;

	/* Entwy to howd numbew of active BSS idx's */
	stwuct wcn36xx_haw_scan_entwy scan_entwy;
};

stwuct wcn36xx_haw_init_scan_con_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* WEAWN - AP Wowe
	   SCAN - STA Wowe */
	enum wcn36xx_haw_sys_mode mode;

	/* BSSID of the BSS */
	u8 bssid[ETH_AWEN];

	/* Whethew BSS needs to be notified */
	u8 notify;

	/* Kind of fwame to be used fow notifying the BSS (Data Nuww, QoS
	 * Nuww, ow CTS to Sewf). Must awways be a vawid fwame type. */
	u8 fwame_type;

	/* UMAC has the option of passing the MAC fwame to be used fow
	 * notifying the BSS. If non-zewo, HAW wiww use the MAC fwame
	 * buffew pointed to by macMgmtHdw. If zewo, HAW wiww genewate the
	 * appwopwiate MAC fwame based on fwameType. */
	u8 fwame_wength;

	/* Fowwowing the fwamewength thewe is a MAC fwame buffew if
	 * fwameWength is non-zewo. */
	stwuct wcn36xx_haw_mac_mgmt_hdw mac_mgmt_hdw;

	/* Entwy to howd numbew of active BSS idx's */
	stwuct wcn36xx_haw_scan_entwy scan_entwy;

	/* Singwe NoA usage in Scanning */
	u8 use_noa;

	/* Indicates the scan duwation (in ms) */
	u16 scan_duwation;

};

stwuct wcn36xx_haw_init_scan_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

} __packed;

stwuct wcn36xx_haw_stawt_scan_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Indicates the channew to scan */
	u8 scan_channew;
} __packed;

stwuct wcn36xx_haw_stawt_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	u32 stawt_tsf[2];
	u8 tx_mgmt_powew;

} __packed;

stwuct wcn36xx_haw_end_scan_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Indicates the channew to stop scanning. Not used weawwy. But
	 * wetained fow symmetwy with "stawt Scan" message. It can awso
	 * hewp in ewwow check if needed. */
	u8 scan_channew;
} __packed;

stwuct wcn36xx_haw_end_scan_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
} __packed;

stwuct wcn36xx_haw_finish_scan_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Identifies the opewationaw state of the AP/STA
	 * WEAWN - AP Wowe SCAN - STA Wowe */
	enum wcn36xx_haw_sys_mode mode;

	/* Opewating channew to tune to. */
	u8 opew_channew;

	/* Channew Bonding state If 20/40 MHz is opewationaw, this wiww
	 * indicate the 40 MHz extension channew in combination with the
	 * contwow channew */
	enum phy_chan_bond_state cb_state;

	/* BSSID of the BSS */
	u8 bssid[ETH_AWEN];

	/* Whethew BSS needs to be notified */
	u8 notify;

	/* Kind of fwame to be used fow notifying the BSS (Data Nuww, QoS
	 * Nuww, ow CTS to Sewf). Must awways be a vawid fwame type. */
	u8 fwame_type;

	/* UMAC has the option of passing the MAC fwame to be used fow
	 * notifying the BSS. If non-zewo, HAW wiww use the MAC fwame
	 * buffew pointed to by macMgmtHdw. If zewo, HAW wiww genewate the
	 * appwopwiate MAC fwame based on fwameType. */
	u8 fwame_wength;

	/* Fowwowing the fwamewength thewe is a MAC fwame buffew if
	 * fwameWength is non-zewo. */
	stwuct wcn36xx_haw_mac_mgmt_hdw mac_mgmt_hdw;

	/* Entwy to howd numbew of active BSS idx's */
	stwuct wcn36xx_haw_scan_entwy scan_entwy;

} __packed;

stwuct wcn36xx_haw_finish_scan_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

} __packed;

enum wcn36xx_haw_scan_type {
	WCN36XX_HAW_SCAN_TYPE_PASSIVE = 0x00,
	WCN36XX_HAW_SCAN_TYPE_ACTIVE = WCN36XX_HAW_MAX_ENUM_SIZE
};

stwuct wcn36xx_haw_mac_ssid {
	u8 wength;
	u8 ssid[32];
} __packed;

stwuct wcn36xx_haw_stawt_scan_offwoad_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* BSSIDs hot wist */
	u8 num_bssid;
	u8 bssids[4][ETH_AWEN];

	/* Diwected pwobe-wequests wiww be sent fow wisted SSIDs (max 10)*/
	u8 num_ssid;
	stwuct wcn36xx_haw_mac_ssid ssids[10];

	/* Wepowt AP with hidden ssid */
	u8 scan_hidden;

	/* Sewf MAC addwess */
	u8 mac[ETH_AWEN];

	/* BSS type */
	enum wcn36xx_haw_bss_type bss_type;

	/* Scan type */
	enum wcn36xx_haw_scan_type scan_type;

	/* Minimum scanning time on each channew (ms) */
	u32 min_ch_time;

	/* Maximum scanning time on each channew */
	u32 max_ch_time;

	/* Is a p2p seawch */
	u8 p2p_seawch;

	/* Channews to scan */
	u8 num_channew;
	u8 channews[80];

	/* IE fiewd */
	u16 ie_wen;
	u8 ie[WCN36XX_MAX_SCAN_IE_WEN];
} __packed;

stwuct wcn36xx_haw_stawt_scan_offwoad_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
} __packed;

enum wcn36xx_haw_scan_offwoad_ind_type {
	/* Scan has been stawted */
	WCN36XX_HAW_SCAN_IND_STAWTED = 0x01,
	/* Scan has been compweted */
	WCN36XX_HAW_SCAN_IND_COMPWETED = 0x02,
	/* Moved to foweign channew */
	WCN36XX_HAW_SCAN_IND_FOWEIGN_CHANNEW = 0x08,
	/* scan wequest has been dequeued */
	WCN36XX_HAW_SCAN_IND_DEQUEUED = 0x10,
	/* pweempted by othew high pwiowity scan */
	WCN36XX_HAW_SCAN_IND_PWEEMPTED = 0x20,
	/* scan stawt faiwed */
	WCN36XX_HAW_SCAN_IND_FAIWED = 0x40,
	 /*scan westawted */
	WCN36XX_HAW_SCAN_IND_WESTAWTED = 0x80,
	WCN36XX_HAW_SCAN_IND_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

stwuct wcn36xx_haw_scan_offwoad_ind {
	stwuct wcn36xx_haw_msg_headew headew;

	u32 type;
	u32 channew_mhz;
	u32 scan_id;
} __packed;

stwuct wcn36xx_haw_stop_scan_offwoad_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
} __packed;

stwuct wcn36xx_haw_stop_scan_offwoad_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
} __packed;

#define WCN36XX_HAW_CHAN_WEG1_MIN_PWW_MASK  0x000000ff
#define WCN36XX_HAW_CHAN_WEG1_MAX_PWW_MASK  0x0000ff00
#define WCN36XX_HAW_CHAN_WEG1_WEG_PWW_MASK  0x00ff0000
#define WCN36XX_HAW_CHAN_WEG1_CWASS_ID_MASK 0xff000000
#define WCN36XX_HAW_CHAN_WEG2_ANT_GAIN_MASK 0x000000ff
#define WCN36XX_HAW_CHAN_INFO_FWAG_PASSIVE  BIT(7)
#define WCN36XX_HAW_CHAN_INFO_FWAG_DFS      BIT(10)
#define WCN36XX_HAW_CHAN_INFO_FWAG_HT       BIT(11)
#define WCN36XX_HAW_CHAN_INFO_FWAG_VHT      BIT(12)
#define WCN36XX_HAW_CHAN_INFO_PHY_11A       0
#define WCN36XX_HAW_CHAN_INFO_PHY_11BG      1
#define WCN36XX_HAW_DEFAUWT_ANT_GAIN        6
#define WCN36XX_HAW_DEFAUWT_MIN_POWEW       6

stwuct wcn36xx_haw_channew_pawam {
	u32 mhz;
	u32 band_centew_fweq1;
	u32 band_centew_fweq2;
	u32 channew_info;
	u32 weg_info_1;
	u32 weg_info_2;
} __packed;

stwuct wcn36xx_haw_update_channew_wist_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 num_channew;
	stwuct wcn36xx_haw_channew_pawam channews[80];
} __packed;

enum wcn36xx_haw_wate_index {
	HW_WATE_INDEX_1MBPS	= 0x82,
	HW_WATE_INDEX_2MBPS	= 0x84,
	HW_WATE_INDEX_5_5MBPS	= 0x8B,
	HW_WATE_INDEX_6MBPS	= 0x0C,
	HW_WATE_INDEX_9MBPS	= 0x12,
	HW_WATE_INDEX_11MBPS	= 0x96,
	HW_WATE_INDEX_12MBPS	= 0x18,
	HW_WATE_INDEX_18MBPS	= 0x24,
	HW_WATE_INDEX_24MBPS	= 0x30,
	HW_WATE_INDEX_36MBPS	= 0x48,
	HW_WATE_INDEX_48MBPS	= 0x60,
	HW_WATE_INDEX_54MBPS	= 0x6C
};

stwuct wcn36xx_haw_suppowted_wates {
	/*
	 * Fow Sewf STA Entwy: this wepwesents Sewf Mode.
	 * Fow Peew Stations, this wepwesents the mode of the peew.
	 * On Station:
	 *
	 * --this mode is updated when PE adds the Sewf Entwy.
	 *
	 * -- OW when PE sends 'ADD_BSS' message and station context in BSS
	 *    is used to indicate the mode of the AP.
	 *
	 * ON AP:
	 *
	 * -- this mode is updated when PE sends 'ADD_BSS' and Sta entwy
	 *     fow that BSS is used to indicate the sewf mode of the AP.
	 *
	 * -- OW when a station is associated, PE sends 'ADD_STA' message
	 *    with this mode updated.
	 */

	enum sta_wate_mode op_wate_mode;

	/* 11b, 11a and aniWegacyWates awe IE wates which gives wate in
	 * unit of 500Kbps */
	u16 dsss_wates[WCN36XX_HAW_NUM_DSSS_WATES];
	u16 ofdm_wates[WCN36XX_HAW_NUM_OFDM_WATES];
	u16 wegacy_wates[WCN36XX_HAW_NUM_POWAWIS_WATES];
	u16 wesewved;

	/* Tauwus onwy suppowts 26 Titan Wates(no ESF/concat Wates wiww be
	 * suppowted) Fiwst 26 bits awe wesewved fow those Titan wates and
	 * the wast 4 bits(bit28-31) fow Tauwus, 2(bit26-27) bits awe
	 * wesewved. */
	/* Titan and Tauwus Wates */
	u32 enhanced_wate_bitmap;

	/*
	 * 0-76 bits used, wemaining wesewved
	 * bits 0-15 and 32 shouwd be set.
	 */
	u8 suppowted_mcs_set[WCN36XX_HAW_MAC_MAX_SUPPOWTED_MCS_SET];

	/*
	 * WX Highest Suppowted Data Wate defines the highest data
	 * wate that the STA is abwe to weceive, in unites of 1Mbps.
	 * This vawue is dewived fwom "Suppowted MCS Set fiewd" inside
	 * the HT capabiwity ewement.
	 */
	u16 wx_highest_data_wate;

} __packed;

stwuct wcn36xx_haw_config_sta_pawams {
	/* BSSID of STA */
	u8 bssid[ETH_AWEN];

	/* ASSOC ID, as assigned by UMAC */
	u16 aid;

	/* STA entwy Type: 0 - Sewf, 1 - Othew/Peew, 2 - BSSID, 3 - BCAST */
	u8 type;

	/* Showt Pweambwe Suppowted. */
	u8 showt_pweambwe_suppowted;

	/* MAC Addwess of STA */
	u8 mac[ETH_AWEN];

	/* Wisten intewvaw of the STA */
	u16 wisten_intewvaw;

	/* Suppowt fow 11e/WMM */
	u8 wmm_enabwed;

	/* 11n HT capabwe STA */
	u8 ht_capabwe;

	/* TX Width Set: 0 - 20 MHz onwy, 1 - 20/40 MHz */
	u8 tx_channew_width_set;

	/* WIFS mode 0 - NA, 1 - Awwowed */
	u8 wifs_mode;

	/* W-SIG TXOP Pwotection mechanism
	   0 - No Suppowt, 1 - Suppowted
	   SG - thewe is gwobaw fiewd */
	u8 wsig_txop_pwotection;

	/* Max Ampdu Size suppowted by STA. TPE pwogwamming.
	   0 : 8k , 1 : 16k, 2 : 32k, 3 : 64k */
	u8 max_ampdu_size;

	/* Max Ampdu density. Used by WA.  3 : 0~7 : 2^(11nAMPDUdensity -4) */
	u8 max_ampdu_density;

	/* Max AMSDU size 1 : 3839 bytes, 0 : 7935 bytes */
	u8 max_amsdu_size;

	/* Showt GI suppowt fow 40Mhz packets */
	u8 sgi_40mhz;

	/* Showt GI suppowt fow 20Mhz packets */
	u8 sgi_20Mhz;

	/* TODO move this pawametew to the end fow 3680 */
	/* These wates awe the intewsection of peew and sewf capabiwities. */
	stwuct wcn36xx_haw_suppowted_wates suppowted_wates;

	/* Wobust Management Fwame (WMF) enabwed/disabwed */
	u8 wmf;

	/* The unicast encwyption type in the association */
	u32 encwypt_type;

	/* HAW shouwd update the existing STA entwy, if this fwag is set. UMAC
	   wiww set this fwag in case of WE-ASSOC, whewe we want to weuse the
	   owd STA ID. 0 = Add, 1 = Update */
	u8 action;

	/* U-APSD Fwags: 1b pew AC.  Encoded as fowwows:
	   b7 b6 b5 b4 b3 b2 b1 b0 =
	   X  X  X  X  BE BK VI VO */
	u8 uapsd;

	/* Max SP Wength */
	u8 max_sp_wen;

	/* 11n Gween Fiewd pweambwe suppowt
	   0 - Not suppowted, 1 - Suppowted */
	u8 gween_fiewd_capabwe;

	/* MIMO Powew Save mode */
	enum wcn36xx_haw_ht_mimo_state mimo_ps;

	/* Dewayed BA Suppowt */
	u8 dewayed_ba_suppowt;

	/* Max AMPDU duwation in 32us */
	u8 max_ampdu_duwation;

	/* HT STA shouwd set it to 1 if it is enabwed in BSS. HT STA shouwd
	 * set it to 0 if AP does not suppowt it. This indication is sent
	 * to HAW and HAW uses this fwag to pickup up appwopwiate 40Mhz
	 * wates. */
	u8 dsss_cck_mode_40mhz;

	/* Vawid STA Idx when action=Update. Set to 0xFF when invawid!
	 * Wetained fow backwawd compawibity with existing HAW code */
	u8 sta_index;

	/* BSSID of BSS to which station is associated. Set to 0xFF when
	 * invawid. Wetained fow backwawd compawibity with existing HAW
	 * code */
	u8 bssid_index;

	u8 p2p;

	/* TODO add this pawametew fow 3680. */
	/* Wesewved to awign next fiewd on a dwowd boundawy */
	/* u8 wesewved; */
} __packed;

stwuct wcn36xx_haw_config_sta_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_config_sta_pawams sta_pawams;
} __packed;

stwuct wcn36xx_haw_suppowted_wates_v1 {
	/* Fow Sewf STA Entwy: this wepwesents Sewf Mode.
	 * Fow Peew Stations, this wepwesents the mode of the peew.
	 * On Station:
	 *
	 * --this mode is updated when PE adds the Sewf Entwy.
	 *
	 * -- OW when PE sends 'ADD_BSS' message and station context in BSS
	 *    is used to indicate the mode of the AP.
	 *
	 * ON AP:
	 *
	 * -- this mode is updated when PE sends 'ADD_BSS' and Sta entwy
	 *     fow that BSS is used to indicate the sewf mode of the AP.
	 *
	 * -- OW when a station is associated, PE sends 'ADD_STA' message
	 *    with this mode updated.
	 */

	enum sta_wate_mode op_wate_mode;

	/* 11b, 11a and aniWegacyWates awe IE wates which gives wate in
	 * unit of 500Kbps
	 */
	u16 dsss_wates[WCN36XX_HAW_NUM_DSSS_WATES];
	u16 ofdm_wates[WCN36XX_HAW_NUM_OFDM_WATES];
	u16 wegacy_wates[WCN36XX_HAW_NUM_POWAWIS_WATES];
	u16 wesewved;

	/* Tauwus onwy suppowts 26 Titan Wates(no ESF/concat Wates wiww be
	 * suppowted) Fiwst 26 bits awe wesewved fow those Titan wates and
	 * the wast 4 bits(bit28-31) fow Tauwus, 2(bit26-27) bits awe
	 * wesewved
	 * Titan and Tauwus Wates
	 */
	u32 enhanced_wate_bitmap;

	/* 0-76 bits used, wemaining wesewved
	 * bits 0-15 and 32 shouwd be set.
	 */
	u8 suppowted_mcs_set[WCN36XX_HAW_MAC_MAX_SUPPOWTED_MCS_SET];

	/* WX Highest Suppowted Data Wate defines the highest data
	 * wate that the STA is abwe to weceive, in unites of 1Mbps.
	 * This vawue is dewived fwom "Suppowted MCS Set fiewd" inside
	 * the HT capabiwity ewement.
	 */
	u16 wx_highest_data_wate;

	/* Indicates the Maximum MCS that can be weceived fow each spatiaw
	 * stweam.
	 */
	u16 vht_wx_mcs_map;

	/* Indicates the highest VHT data wate that the STA is abwe to
	 * weceive.
	 */
	u16 vht_wx_highest_data_wate;

	/* Indicates the Maximum MCS that can be twansmitted fow each spatiaw
	 * stweam.
	 */
	u16 vht_tx_mcs_map;

	/* Indicates the highest VHT data wate that the STA is abwe to
	 * twansmit.
	 */
	u16 vht_tx_highest_data_wate;
} __packed;

stwuct wcn36xx_haw_config_sta_pawams_v1 {
	/* BSSID of STA */
	u8 bssid[ETH_AWEN];

	/* ASSOC ID, as assigned by UMAC */
	u16 aid;

	/* STA entwy Type: 0 - Sewf, 1 - Othew/Peew, 2 - BSSID, 3 - BCAST */
	u8 type;

	/* Showt Pweambwe Suppowted. */
	u8 showt_pweambwe_suppowted;

	/* MAC Addwess of STA */
	u8 mac[ETH_AWEN];

	/* Wisten intewvaw of the STA */
	u16 wisten_intewvaw;

	/* Suppowt fow 11e/WMM */
	u8 wmm_enabwed;

	/* 11n HT capabwe STA */
	u8 ht_capabwe;

	/* TX Width Set: 0 - 20 MHz onwy, 1 - 20/40 MHz */
	u8 tx_channew_width_set;

	/* WIFS mode 0 - NA, 1 - Awwowed */
	u8 wifs_mode;

	/* W-SIG TXOP Pwotection mechanism
	   0 - No Suppowt, 1 - Suppowted
	   SG - thewe is gwobaw fiewd */
	u8 wsig_txop_pwotection;

	/* Max Ampdu Size suppowted by STA. TPE pwogwamming.
	   0 : 8k , 1 : 16k, 2 : 32k, 3 : 64k */
	u8 max_ampdu_size;

	/* Max Ampdu density. Used by WA.  3 : 0~7 : 2^(11nAMPDUdensity -4) */
	u8 max_ampdu_density;

	/* Max AMSDU size 1 : 3839 bytes, 0 : 7935 bytes */
	u8 max_amsdu_size;

	/* Showt GI suppowt fow 40Mhz packets */
	u8 sgi_40mhz;

	/* Showt GI suppowt fow 20Mhz packets */
	u8 sgi_20Mhz;

	/* Wobust Management Fwame (WMF) enabwed/disabwed */
	u8 wmf;

	/* The unicast encwyption type in the association */
	u32 encwypt_type;

	/* HAW shouwd update the existing STA entwy, if this fwag is set. UMAC
	   wiww set this fwag in case of WE-ASSOC, whewe we want to weuse the
	   owd STA ID. 0 = Add, 1 = Update */
	u8 action;

	/* U-APSD Fwags: 1b pew AC.  Encoded as fowwows:
	   b7 b6 b5 b4 b3 b2 b1 b0 =
	   X  X  X  X  BE BK VI VO */
	u8 uapsd;

	/* Max SP Wength */
	u8 max_sp_wen;

	/* 11n Gween Fiewd pweambwe suppowt
	   0 - Not suppowted, 1 - Suppowted */
	u8 gween_fiewd_capabwe;

	/* MIMO Powew Save mode */
	enum wcn36xx_haw_ht_mimo_state mimo_ps;

	/* Dewayed BA Suppowt */
	u8 dewayed_ba_suppowt;

	/* Max AMPDU duwation in 32us */
	u8 max_ampdu_duwation;

	/* HT STA shouwd set it to 1 if it is enabwed in BSS. HT STA shouwd
	 * set it to 0 if AP does not suppowt it. This indication is sent
	 * to HAW and HAW uses this fwag to pickup up appwopwiate 40Mhz
	 * wates. */
	u8 dsss_cck_mode_40mhz;

	/* Vawid STA Idx when action=Update. Set to 0xFF when invawid!
	 * Wetained fow backwawd compawibity with existing HAW code */
	u8 sta_index;

	/* BSSID of BSS to which station is associated. Set to 0xFF when
	 * invawid. Wetained fow backwawd compawibity with existing HAW
	 * code */
	u8 bssid_index;

	u8 p2p;

	/* Wesewved to awign next fiewd on a dwowd boundawy */
	u8 ht_wdpc_enabwed:1;
	u8 vht_wdpc_enabwed:1;
	u8 vht_tx_bf_enabwed:1;
	u8 vht_tx_mu_beamfowmee_capabwe:1;
	u8 wesewved:4;

	/* These wates awe the intewsection of peew and sewf capabiwities. */
	stwuct wcn36xx_haw_suppowted_wates_v1 suppowted_wates;

	u8 vht_capabwe;
	u8 vht_tx_channew_width_set;

} __packed;

#define WCN36XX_DIFF_STA_PAWAMS_V1_NOVHT 10

stwuct wcn36xx_haw_config_sta_weq_msg_v1 {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_config_sta_pawams_v1 sta_pawams;
} __packed;

stwuct config_sta_wsp_pawams {
	/* success ow faiwuwe */
	u32 status;

	/* Station index; vawid onwy when 'status' fiewd vawue SUCCESS */
	u8 sta_index;

	/* BSSID Index of BSS to which the station is associated */
	u8 bssid_index;

	/* DPU Index fow PTK */
	u8 dpu_index;

	/* DPU Index fow GTK */
	u8 bcast_dpu_index;

	/* DPU Index fow IGTK  */
	u8 bcast_mgmt_dpu_idx;

	/* PTK DPU signatuwe */
	u8 uc_ucast_sig;

	/* GTK DPU isignatuwe */
	u8 uc_bcast_sig;

	/* IGTK DPU signatuwe */
	u8 uc_mgmt_sig;

	u8 p2p;

} __packed;

stwuct wcn36xx_haw_config_sta_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	stwuct config_sta_wsp_pawams pawams;
} __packed;

/* Dewete STA Wequest message */
stwuct wcn36xx_haw_dewete_sta_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Index of STA to dewete */
	u8 sta_index;

} __packed;

/* Dewete STA Wesponse message */
stwuct wcn36xx_haw_dewete_sta_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	/* Index of STA deweted */
	u8 sta_id;
} __packed;

/* 12 Bytes wong because this stwuctuwe can be used to wepwesent wate and
 * extended wate set IEs. The pawsew assume this to be at weast 12 */
stwuct wcn36xx_haw_wate_set {
	u8 num_wates;
	u8 wate[WCN36XX_HAW_MAC_WATESET_EID_MAX];
} __packed;

/* access categowy wecowd */
stwuct wcn36xx_haw_aci_aifsn {
#ifndef ANI_WITTWE_BIT_ENDIAN
	u8 wsvd:1;
	u8 aci:2;
	u8 acm:1;
	u8 aifsn:4;
#ewse
	u8 aifsn:4;
	u8 acm:1;
	u8 aci:2;
	u8 wsvd:1;
#endif
} __packed;

/* contention window size */
stwuct wcn36xx_haw_mac_cw {
#ifndef ANI_WITTWE_BIT_ENDIAN
	u8 max:4;
	u8 min:4;
#ewse
	u8 min:4;
	u8 max:4;
#endif
} __packed;

stwuct wcn36xx_haw_edca_pawam_wecowd {
	stwuct wcn36xx_haw_aci_aifsn aci;
	stwuct wcn36xx_haw_mac_cw cw;
	u16 txop_wimit;
} __packed;

/* Concuwwency wowe. These awe genewic IDs that identify the vawious wowes
 *  in the softwawe system. */
enum wcn36xx_haw_con_mode {
	WCN36XX_HAW_STA_MODE = 0,

	/* to suppowt softAp mode . This is misweading.
	   It means AP MODE onwy. */
	WCN36XX_HAW_STA_SAP_MODE = 1,

	WCN36XX_HAW_P2P_CWIENT_MODE,
	WCN36XX_HAW_P2P_GO_MODE,
	WCN36XX_HAW_MONITOW_MODE,
};

/* This is a bit pattewn to be set fow each mode
 * bit 0 - sta mode
 * bit 1 - ap mode
 * bit 2 - p2p cwient mode
 * bit 3 - p2p go mode */
enum wcn36xx_haw_concuwwency_mode {
	HAW_STA = 1,
	HAW_SAP = 2,

	/* to suppowt sta, softAp  mode . This means STA+AP mode */
	HAW_STA_SAP = 3,

	HAW_P2P_CWIENT = 4,
	HAW_P2P_GO = 8,
	HAW_MAX_CONCUWWENCY_PEWSONA = 4
};

stwuct wcn36xx_haw_config_bss_pawams {
	/* BSSID */
	u8 bssid[ETH_AWEN];

	/* Sewf Mac Addwess */
	u8 sewf_mac_addw[ETH_AWEN];

	/* BSS type */
	enum wcn36xx_haw_bss_type bss_type;

	/* Opewationaw Mode: AP =0, STA = 1 */
	u8 opew_mode;

	/* Netwowk Type */
	enum wcn36xx_haw_nw_type nw_type;

	/* Used to cwassify PUWE_11G/11G_MIXED to pwogwam MTU */
	u8 showt_swot_time_suppowted;

	/* Co-exist with 11a STA */
	u8 wwa_coexist;

	/* Co-exist with 11b STA */
	u8 wwb_coexist;

	/* Co-exist with 11g STA */
	u8 wwg_coexist;

	/* Coexistence with 11n STA */
	u8 ht20_coexist;

	/* Non GF coexist fwag */
	u8 wwn_non_gf_coexist;

	/* TXOP pwotection suppowt */
	u8 wsig_tx_op_pwotection_fuww_suppowt;

	/* WIFS mode */
	u8 wifs_mode;

	/* Beacon Intewvaw in TU */
	u16 beacon_intewvaw;

	/* DTIM pewiod */
	u8 dtim_pewiod;

	/* TX Width Set: 0 - 20 MHz onwy, 1 - 20/40 MHz */
	u8 tx_channew_width_set;

	/* Opewating channew */
	u8 opew_channew;

	/* Extension channew fow channew bonding */
	u8 ext_channew;

	/* Wesewved to awign next fiewd on a dwowd boundawy */
	u8 wesewved;

	/* TODO move sta to the end fow 3680 */
	/* Context of the station being added in HW
	 *  Add a STA entwy fow "itsewf" -
	 *
	 *  On AP  - Add the AP itsewf in an "STA context"
	 *
	 *  On STA - Add the AP to which this STA is joining in an
	 *  "STA context"
	 */
	stwuct wcn36xx_haw_config_sta_pawams sta;
	/* SSID of the BSS */
	stwuct wcn36xx_haw_mac_ssid ssid;

	/* HAW shouwd update the existing BSS entwy, if this fwag is set.
	 * UMAC wiww set this fwag in case of weassoc, whewe we want to
	 * wesue the owd BSSID and stiww wetuwn success 0 = Add, 1 =
	 * Update */
	u8 action;

	/* MAC Wate Set */
	stwuct wcn36xx_haw_wate_set wateset;

	/* Enabwe/Disabwe HT capabiwities of the BSS */
	u8 ht;

	/* Enabwe/Disabwe OBSS pwotection */
	u8 obss_pwot_enabwed;

	/* WMF enabwed/disabwed */
	u8 wmf;

	/* HT Opewating Mode opewating mode of the 802.11n STA */
	enum wcn36xx_haw_ht_opewating_mode ht_opew_mode;

	/* Duaw CTS Pwotection: 0 - Unused, 1 - Used */
	u8 duaw_cts_pwotection;

	/* Pwobe Wesponse Max wetwies */
	u8 max_pwobe_wesp_wetwy_wimit;

	/* To Enabwe Hidden ssid */
	u8 hidden_ssid;

	/* To Enabwe Disabwe FW Pwoxy Pwobe Wesp */
	u8 pwoxy_pwobe_wesp;

	/* Boowean to indicate if EDCA pawams awe vawid. UMAC might not
	 * have vawid EDCA pawams ow might not desiwe to appwy EDCA pawams
	 * duwing config BSS. 0 impwies Not Vawid ; Non-Zewo impwies
	 * vawid */
	u8 edca_pawams_vawid;

	/* EDCA Pawametews fow Best Effowt Access Categowy */
	stwuct wcn36xx_haw_edca_pawam_wecowd acbe;

	/* EDCA Pawametews fowBackgwound Access Categowy */
	stwuct wcn36xx_haw_edca_pawam_wecowd acbk;

	/* EDCA Pawametews fow Video Access Categowy */
	stwuct wcn36xx_haw_edca_pawam_wecowd acvi;

	/* EDCA Pawametews fow Voice Access Categowy */
	stwuct wcn36xx_haw_edca_pawam_wecowd acvo;

	/* Ext Bss Config Msg if set */
	u8 ext_set_sta_key_pawam_vawid;

	/* SetStaKeyPawams fow ext bss msg */
	stwuct wcn36xx_haw_set_sta_key_pawams ext_set_sta_key_pawam;

	/* Pewsona fow the BSS can be STA,AP,GO,CWIENT vawue same as enum
	 * wcn36xx_haw_con_mode */
	u8 wcn36xx_haw_pewsona;

	u8 spectwum_mgt_enabwe;

	/* HAW fiwws in the tx powew used fow mgmt fwames in txMgmtPowew */
	s8 tx_mgmt_powew;

	/* maxTxPowew has max powew to be used aftew appwying the powew
	 * constwaint if any */
	s8 max_tx_powew;
} __packed;

stwuct wcn36xx_haw_config_bss_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_config_bss_pawams bss_pawams;
} __packed;

stwuct wcn36xx_haw_config_bss_pawams_v1 {
	/* BSSID */
	u8 bssid[ETH_AWEN];

	/* Sewf Mac Addwess */
	u8 sewf_mac_addw[ETH_AWEN];

	/* BSS type */
	enum wcn36xx_haw_bss_type bss_type;

	/* Opewationaw Mode: AP =0, STA = 1 */
	u8 opew_mode;

	/* Netwowk Type */
	enum wcn36xx_haw_nw_type nw_type;

	/* Used to cwassify PUWE_11G/11G_MIXED to pwogwam MTU */
	u8 showt_swot_time_suppowted;

	/* Co-exist with 11a STA */
	u8 wwa_coexist;

	/* Co-exist with 11b STA */
	u8 wwb_coexist;

	/* Co-exist with 11g STA */
	u8 wwg_coexist;

	/* Coexistence with 11n STA */
	u8 ht20_coexist;

	/* Non GF coexist fwag */
	u8 wwn_non_gf_coexist;

	/* TXOP pwotection suppowt */
	u8 wsig_tx_op_pwotection_fuww_suppowt;

	/* WIFS mode */
	u8 wifs_mode;

	/* Beacon Intewvaw in TU */
	u16 beacon_intewvaw;

	/* DTIM pewiod */
	u8 dtim_pewiod;

	/* TX Width Set: 0 - 20 MHz onwy, 1 - 20/40 MHz */
	u8 tx_channew_width_set;

	/* Opewating channew */
	u8 opew_channew;

	/* Extension channew fow channew bonding */
	u8 ext_channew;

	/* Wesewved to awign next fiewd on a dwowd boundawy */
	u8 wesewved;

	/* SSID of the BSS */
	stwuct wcn36xx_haw_mac_ssid ssid;

	/* HAW shouwd update the existing BSS entwy, if this fwag is set.
	 * UMAC wiww set this fwag in case of weassoc, whewe we want to
	 * wesue the owd BSSID and stiww wetuwn success 0 = Add, 1 =
	 * Update */
	u8 action;

	/* MAC Wate Set */
	stwuct wcn36xx_haw_wate_set wateset;

	/* Enabwe/Disabwe HT capabiwities of the BSS */
	u8 ht;

	/* Enabwe/Disabwe OBSS pwotection */
	u8 obss_pwot_enabwed;

	/* WMF enabwed/disabwed */
	u8 wmf;

	/* HT Opewating Mode opewating mode of the 802.11n STA */
	enum wcn36xx_haw_ht_opewating_mode ht_opew_mode;

	/* Duaw CTS Pwotection: 0 - Unused, 1 - Used */
	u8 duaw_cts_pwotection;

	/* Pwobe Wesponse Max wetwies */
	u8 max_pwobe_wesp_wetwy_wimit;

	/* To Enabwe Hidden ssid */
	u8 hidden_ssid;

	/* To Enabwe Disabwe FW Pwoxy Pwobe Wesp */
	u8 pwoxy_pwobe_wesp;

	/* Boowean to indicate if EDCA pawams awe vawid. UMAC might not
	 * have vawid EDCA pawams ow might not desiwe to appwy EDCA pawams
	 * duwing config BSS. 0 impwies Not Vawid ; Non-Zewo impwies
	 * vawid */
	u8 edca_pawams_vawid;

	/* EDCA Pawametews fow Best Effowt Access Categowy */
	stwuct wcn36xx_haw_edca_pawam_wecowd acbe;

	/* EDCA Pawametews fowBackgwound Access Categowy */
	stwuct wcn36xx_haw_edca_pawam_wecowd acbk;

	/* EDCA Pawametews fow Video Access Categowy */
	stwuct wcn36xx_haw_edca_pawam_wecowd acvi;

	/* EDCA Pawametews fow Voice Access Categowy */
	stwuct wcn36xx_haw_edca_pawam_wecowd acvo;

	/* Ext Bss Config Msg if set */
	u8 ext_set_sta_key_pawam_vawid;

	/* SetStaKeyPawams fow ext bss msg */
	stwuct wcn36xx_haw_set_sta_key_pawams ext_set_sta_key_pawam;

	/* Pewsona fow the BSS can be STA,AP,GO,CWIENT vawue same as enum
	 * wcn36xx_haw_con_mode */
	u8 wcn36xx_haw_pewsona;

	u8 spectwum_mgt_enabwe;

	/* HAW fiwws in the tx powew used fow mgmt fwames in txMgmtPowew */
	s8 tx_mgmt_powew;

	/* maxTxPowew has max powew to be used aftew appwying the powew
	 * constwaint if any */
	s8 max_tx_powew;

	/* Context of the station being added in HW
	 *  Add a STA entwy fow "itsewf" -
	 *
	 *  On AP  - Add the AP itsewf in an "STA context"
	 *
	 *  On STA - Add the AP to which this STA is joining in an
	 *  "STA context"
	 */
	stwuct wcn36xx_haw_config_sta_pawams_v1 sta;

	u8 vht_capabwe;
	u8 vht_tx_channew_width_set;

} __packed;

#define WCN36XX_DIFF_BSS_PAWAMS_V1_NOVHT (WCN36XX_DIFF_STA_PAWAMS_V1_NOVHT + 2)

stwuct wcn36xx_haw_config_bss_weq_msg_v1 {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_config_bss_pawams_v1 bss_pawams;
} __packed;

stwuct wcn36xx_haw_config_bss_wsp_pawams {
	/* Success ow Faiwuwe */
	u32 status;

	/* BSS index awwocated by HAW */
	u8 bss_index;

	/* DPU descwiptow index fow PTK */
	u8 dpu_desc_index;

	/* PTK DPU signatuwe */
	u8 ucast_dpu_signatuwe;

	/* DPU descwiptow index fow GTK */
	u8 bcast_dpu_desc_indx;

	/* GTK DPU signatuwe */
	u8 bcast_dpu_signatuwe;

	/* DPU descwiptow fow IGTK */
	u8 mgmt_dpu_desc_index;

	/* IGTK DPU signatuwe */
	u8 mgmt_dpu_signatuwe;

	/* Station Index fow BSS entwy */
	u8 bss_sta_index;

	/* Sewf station index fow this BSS */
	u8 bss_sewf_sta_index;

	/* Bcast station fow buffewing bcast fwames in AP wowe */
	u8 bss_bcast_sta_idx;

	/* MAC Addwess of STA(PEEW/SEWF) in staContext of configBSSWeq */
	u8 mac[ETH_AWEN];

	/* HAW fiwws in the tx powew used fow mgmt fwames in this fiewd. */
	s8 tx_mgmt_powew;

} __packed;

stwuct wcn36xx_haw_config_bss_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_config_bss_wsp_pawams bss_wsp_pawams;
} __packed;

stwuct wcn36xx_haw_dewete_bss_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* BSS index to be deweted */
	u8 bss_index;

} __packed;

stwuct wcn36xx_haw_dewete_bss_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Success ow Faiwuwe */
	u32 status;

	/* BSS index that has been deweted */
	u8 bss_index;

} __packed;

stwuct wcn36xx_haw_join_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Indicates the BSSID to which STA is going to associate */
	u8 bssid[ETH_AWEN];

	/* Indicates the channew to switch to. */
	u8 channew;

	/* Sewf STA MAC */
	u8 sewf_sta_mac_addw[ETH_AWEN];

	/* Wocaw powew constwaint */
	u8 wocaw_powew_constwaint;

	/* Secondawy channew offset */
	enum phy_chan_bond_state secondawy_channew_offset;

	/* wink State */
	enum wcn36xx_haw_wink_state wink_state;

	/* Max TX powew */
	s8 max_tx_powew;
} __packed;

stwuct wcn36xx_haw_join_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	/* HAW fiwws in the tx powew used fow mgmt fwames in this fiewd */
	u8 tx_mgmt_powew;
} __packed;

stwuct post_assoc_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	stwuct wcn36xx_haw_config_sta_pawams sta_pawams;
	stwuct wcn36xx_haw_config_bss_pawams bss_pawams;
};

stwuct post_assoc_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct config_sta_wsp_pawams sta_wsp_pawams;
	stwuct wcn36xx_haw_config_bss_wsp_pawams bss_wsp_pawams;
};

/* This is used to cweate a set of WEP keys fow a given BSS. */
stwuct wcn36xx_haw_set_bss_key_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* BSS Index of the BSS */
	u8 bss_idx;

	/* Encwyption Type used with peew */
	enum ani_ed_type enc_type;

	/* Numbew of keys */
	u8 num_keys;

	/* Awway of keys. */
	stwuct wcn36xx_haw_keys keys[WCN36XX_HAW_MAC_MAX_NUM_OF_DEFAUWT_KEYS];

	/* Contwow fow Wepway Count, 1= Singwe TID based wepway count on Tx
	 * 0 = Pew TID based wepway count on TX */
	u8 singwe_tid_wc;
} __packed;

/* tagged vewsion of set bss key */
stwuct wcn36xx_haw_set_bss_key_weq_msg_tagged {
	stwuct wcn36xx_haw_set_bss_key_weq_msg Msg;
	u32 tag;
} __packed;

stwuct wcn36xx_haw_set_bss_key_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
} __packed;

/*
 * This is used  configuwe the key infowmation on a given station.
 * When the sec_type is WEP40 ow WEP104, the def_wep_idx is used to wocate
 * a pweconfiguwed key fwom a BSS the station associated with; othewwise
 * a new key descwiptow is cweated based on the key fiewd.
 */
stwuct wcn36xx_haw_set_sta_key_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_set_sta_key_pawams set_sta_key_pawams;
} __packed;

stwuct wcn36xx_haw_set_sta_key_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
} __packed;

stwuct wcn36xx_haw_wemove_bss_key_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* BSS Index of the BSS */
	u8 bss_idx;

	/* Encwyption Type used with peew */
	enum ani_ed_type enc_type;

	/* Key Id */
	u8 key_id;

	/* STATIC/DYNAMIC. Used in Nuwwifying in Key Descwiptows fow
	 * Static/Dynamic keys */
	enum ani_wep_type wep_type;
} __packed;

stwuct wcn36xx_haw_wemove_bss_key_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
} __packed;

/*
 * This is used by PE to Wemove the key infowmation on a given station.
 */
stwuct wcn36xx_haw_wemove_sta_key_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* STA Index */
	u16 sta_idx;

	/* Encwyption Type used with peew */
	enum ani_ed_type enc_type;

	/* Key Id */
	u8 key_id;

	/* Whethew to invawidate the Bwoadcast key ow Unicast key. In case
	 * of WEP, the same key is used fow both bwoadcast and unicast. */
	u8 unicast;

} __packed;

stwuct wcn36xx_haw_wemove_sta_key_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/*success ow faiwuwe */
	u32 status;

} __packed;

#ifdef FEATUWE_OEM_DATA_SUPPOWT

#ifndef OEM_DATA_WEQ_SIZE
#define OEM_DATA_WEQ_SIZE 134
#endif

#ifndef OEM_DATA_WSP_SIZE
#define OEM_DATA_WSP_SIZE 1968
#endif

stwuct stawt_oem_data_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u32 status;
	tSiwMacAddw sewf_mac_addw;
	u8 oem_data_weq[OEM_DATA_WEQ_SIZE];

};

stwuct stawt_oem_data_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 oem_data_wsp[OEM_DATA_WSP_SIZE];
};

#endif

stwuct wcn36xx_haw_switch_channew_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Channew numbew */
	u8 channew_numbew;

	/* Wocaw powew constwaint */
	u8 wocaw_powew_constwaint;

	/* Secondawy channew offset */
	enum phy_chan_bond_state secondawy_channew_offset;

	/* HAW fiwws in the tx powew used fow mgmt fwames in this fiewd. */
	u8 tx_mgmt_powew;

	/* Max TX powew */
	u8 max_tx_powew;

	/* Sewf STA MAC */
	u8 sewf_sta_mac_addw[ETH_AWEN];

	/* VO WIFI comment: BSSID needed to identify session. As the
	 * wequest has powew constwaints, this shouwd be appwied onwy to
	 * that session Since MTU timing and EDCA awe sessionized, this
	 * stwuct needs to be sessionized and bssid needs to be out of the
	 * VOWifi featuwe fwag V IMP: Keep bssId fiewd at the end of this
	 * msg. It is used to mantain backwawd compatbiwity by way of
	 * ignowing if using new host/owd FW ow owd host/new FW since it is
	 * at the end of this stwuct
	 */
	u8 bssid[ETH_AWEN];
} __packed;

stwuct wcn36xx_haw_switch_channew_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Status */
	u32 status;

	/* Channew numbew - same as in wequest */
	u8 channew_numbew;

	/* HAW fiwws in the tx powew used fow mgmt fwames in this fiewd */
	u8 tx_mgmt_powew;

	/* BSSID needed to identify session - same as in wequest */
	u8 bssid[ETH_AWEN];

} __packed;

stwuct wcn36xx_haw_pwocess_ptt_msg_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Actuaw FTM Command body */
	u8 ptt_msg[];
} __packed;

stwuct wcn36xx_haw_pwocess_ptt_msg_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* FTM Command wesponse status */
	u32 ptt_msg_wesp_status;
	/* Actuaw FTM Command body */
	u8 ptt_msg[];
} __packed;

stwuct update_edca_pawams_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/*BSS Index */
	u16 bss_index;

	/* Best Effowt */
	stwuct wcn36xx_haw_edca_pawam_wecowd acbe;

	/* Backgwound */
	stwuct wcn36xx_haw_edca_pawam_wecowd acbk;

	/* Video */
	stwuct wcn36xx_haw_edca_pawam_wecowd acvi;

	/* Voice */
	stwuct wcn36xx_haw_edca_pawam_wecowd acvo;
};

stwuct update_edca_pawams_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct dpu_stats_pawams {
	/* Index of STA to which the statistics */
	u16 sta_index;

	/* Encwyption mode */
	u8 enc_mode;

	/* status */
	u32 status;

	/* Statistics */
	u32 send_bwocks;
	u32 wecv_bwocks;
	u32 wepways;
	u8 mic_ewwow_cnt;
	u32 pwot_excw_cnt;
	u16 fowmat_eww_cnt;
	u16 un_decwyptabwe_cnt;
	u32 decwypt_eww_cnt;
	u32 decwypt_ok_cnt;
};

stwuct wcn36xx_haw_stats_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Vawid STA Idx fow pew STA stats wequest */
	u32 sta_id;

	/* Categowies of stats wequested as specified in eHawStatsMask */
	u32 stats_mask;
};

stwuct ani_summawy_stats_info {
	/* Totaw numbew of packets(pew AC) that wewe successfuwwy
	 * twansmitted with wetwies */
	u32 wetwy_cnt[4];

	/* The numbew of MSDU packets and MMPDU fwames pew AC that the
	 * 802.11 station successfuwwy twansmitted aftew mowe than one
	 * wetwansmission attempt */
	u32 muwtipwe_wetwy_cnt[4];

	/* Totaw numbew of packets(pew AC) that wewe successfuwwy
	 * twansmitted (with and without wetwies, incwuding muwti-cast,
	 * bwoadcast) */
	u32 tx_fwm_cnt[4];

	/* Totaw numbew of packets that wewe successfuwwy weceived (aftew
	 * appwopwiate fiwtew wuwes incwuding muwti-cast, bwoadcast) */
	u32 wx_fwm_cnt;

	/* Totaw numbew of dupwicate fwames weceived successfuwwy */
	u32 fwm_dup_cnt;

	/* Totaw numbew packets(pew AC) faiwed to twansmit */
	u32 faiw_cnt[4];

	/* Totaw numbew of WTS/CTS sequence faiwuwes fow twansmission of a
	 * packet */
	u32 wts_faiw_cnt;

	/* Totaw numbew packets faiwed twansmit because of no ACK fwom the
	 * wemote entity */
	u32 ack_faiw_cnt;

	/* Totaw numbew of WTS/CTS sequence success fow twansmission of a
	 * packet */
	u32 wts_succ_cnt;

	/* The sum of the weceive ewwow count and dwopped-weceive-buffew
	 * ewwow count. HAW wiww pwovide this as a sum of (FCS ewwow) +
	 * (Faiw get BD/PDU in HW) */
	u32 wx_discawd_cnt;

	/*
	 * The weceive ewwow count. HAW wiww pwovide the WxP FCS ewwow
	 * gwobaw countew. */
	u32 wx_ewwow_cnt;

	/* The sum of the twansmit-diwected byte count, twansmit-muwticast
	 * byte count and twansmit-bwoadcast byte count. HAW wiww sum TPE
	 * UC/MC/BCAST gwobaw countews to pwovide this. */
	u32 tx_byte_cnt;
};

/* defines tx_wate_fwags */
enum tx_wate_info {
	/* Wegacy wates */
	HAW_TX_WATE_WEGACY = 0x1,

	/* HT20 wates */
	HAW_TX_WATE_HT20 = 0x2,

	/* HT40 wates */
	HAW_TX_WATE_HT40 = 0x4,

	/* Wate with Showt guawd intewvaw */
	HAW_TX_WATE_SGI = 0x8,

	/* Wate with Wong guawd intewvaw */
	HAW_TX_WATE_WGI = 0x10,

	/* VHT wates */
	HAW_TX_WATE_VHT20  = 0x20,
	HAW_TX_WATE_VHT40  = 0x40,
	HAW_TX_WATE_VHT80  = 0x80,
};

stwuct ani_gwobaw_cwass_a_stats_info {
	/* The numbew of MPDU fwames weceived by the 802.11 station fow
	 * MSDU packets ow MMPDU fwames */
	u32 wx_fwag_cnt;

	/* The numbew of MPDU fwames weceived by the 802.11 station fow
	 * MSDU packets ow MMPDU fwames when a pwomiscuous packet fiwtew
	 * was enabwed */
	u32 pwomiscuous_wx_fwag_cnt;

	/* The weceivew input sensitivity wefewenced to a FEW of 8% at an
	 * MPDU wength of 1024 bytes at the antenna connectow. Each ewement
	 * of the awway shaww cowwespond to a suppowted wate and the owdew
	 * shaww be the same as the suppowteWates pawametew. */
	u32 wx_input_sensitivity;

	/* The maximum twansmit powew in dBm upto one decimaw. fow eg: if
	 * it is 10.5dBm, the vawue wouwd be 105 */
	u32 max_pww;

	/* Numbew of times the weceivew faiwed to synchwonize with the
	 * incoming signaw aftew detecting the sync in the pweambwe of the
	 * twansmitted PWCP pwotocow data unit. */
	u32 sync_faiw_cnt;

	/* Wegacy twansmit wate, in units of 500 kbit/sec, fow the most
	 * wecentwy twansmitted fwame */
	u32 tx_wate;

	/* mcs index fow HT20 and HT40 wates */
	u32 mcs_index;

	/* to diffewentiate between HT20 and HT40 wates; showt and wong
	 * guawd intewvaw */
	u32 tx_wate_fwags;
};

stwuct ani_gwobaw_secuwity_stats {
	/* The numbew of unencwypted weceived MPDU fwames that the MAC
	 * wayew discawded when the IEEE 802.11 dot11ExcwudeUnencwypted
	 * management infowmation base (MIB) object is enabwed */
	u32 wx_wep_unencwypted_fwm_cnt;

	/* The numbew of weceived MSDU packets that the 802.11 station
	 * discawded because of MIC faiwuwes */
	u32 wx_mic_faiw_cnt;

	/* The numbew of encwypted MPDU fwames that the 802.11 station
	 * faiwed to decwypt because of a TKIP ICV ewwow */
	u32 tkip_icv_eww;

	/* The numbew of weceived MPDU fwames that the 802.11 discawded
	 * because of an invawid AES-CCMP fowmat */
	u32 aes_ccmp_fowmat_eww;

	/* The numbew of weceived MPDU fwames that the 802.11 station
	 * discawded because of the AES-CCMP wepway pwotection pwoceduwe */
	u32 aes_ccmp_wepway_cnt;

	/* The numbew of weceived MPDU fwames that the 802.11 station
	 * discawded because of ewwows detected by the AES-CCMP decwyption
	 * awgowithm */
	u32 aes_ccmp_decwpt_eww;

	/* The numbew of encwypted MPDU fwames weceived fow which a WEP
	 * decwyption key was not avaiwabwe on the 802.11 station */
	u32 wep_undecwyptabwe_cnt;

	/* The numbew of encwypted MPDU fwames that the 802.11 station
	 * faiwed to decwypt because of a WEP ICV ewwow */
	u32 wep_icv_eww;

	/* The numbew of weceived encwypted packets that the 802.11 station
	 * successfuwwy decwypted */
	u32 wx_decwypt_succ_cnt;

	/* The numbew of encwypted packets that the 802.11 station faiwed
	 * to decwypt */
	u32 wx_decwypt_faiw_cnt;
};

stwuct ani_gwobaw_cwass_b_stats_info {
	stwuct ani_gwobaw_secuwity_stats uc_stats;
	stwuct ani_gwobaw_secuwity_stats mc_bc_stats;
};

stwuct ani_gwobaw_cwass_c_stats_info {
	/* This countew shaww be incwemented fow a weceived A-MSDU fwame
	 * with the stations MAC addwess in the addwess 1 fiewd ow an
	 * A-MSDU fwame with a gwoup addwess in the addwess 1 fiewd */
	u32 wx_amsdu_cnt;

	/* This countew shaww be incwemented when the MAC weceives an AMPDU
	 * fwom the PHY */
	u32 wx_ampdu_cnt;

	/* This countew shaww be incwemented when a Fwame is twansmitted
	 * onwy on the pwimawy channew */
	u32 tx_20_fwm_cnt;

	/* This countew shaww be incwemented when a Fwame is weceived onwy
	 * on the pwimawy channew */
	u32 wx_20_fwm_cnt;

	/* This countew shaww be incwemented by the numbew of MPDUs
	 * weceived in the A-MPDU when an A-MPDU is weceived */
	u32 wx_mpdu_in_ampdu_cnt;

	/* This countew shaww be incwemented when an MPDU dewimitew has a
	 * CWC ewwow when this is the fiwst CWC ewwow in the weceived AMPDU
	 * ow when the pwevious dewimitew has been decoded cowwectwy */
	u32 ampdu_dewimitew_cwc_eww;
};

stwuct ani_pew_sta_stats_info {
	/* The numbew of MPDU fwames that the 802.11 station twansmitted
	 * and acknowwedged thwough a weceived 802.11 ACK fwame */
	u32 tx_fwag_cnt[4];

	/* This countew shaww be incwemented when an A-MPDU is twansmitted */
	u32 tx_ampdu_cnt;

	/* This countew shaww incwement by the numbew of MPDUs in the AMPDU
	 * when an A-MPDU is twansmitted */
	u32 tx_mpdu_in_ampdu_cnt;
};

stwuct wcn36xx_haw_stats_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Success ow Faiwuwe */
	u32 status;

	/* STA Idx */
	u32 sta_index;

	/* Categowies of STATS being wetuwned as pew eHawStatsMask */
	u32 stats_mask;

	/* message type is same as the wequest type */
	u16 msg_type;

	/* wength of the entiwe wequest, incwudes the pStatsBuf wength too */
	u16 msg_wen;
};

stwuct wcn36xx_haw_set_wink_state_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 bssid[ETH_AWEN];
	enum wcn36xx_haw_wink_state state;
	u8 sewf_mac_addw[ETH_AWEN];

} __packed;

stwuct set_wink_state_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

/* TSPEC Pawams */
stwuct wcn36xx_haw_ts_info_tfc {
#ifndef ANI_WITTWE_BIT_ENDIAN
	u16 ackPowicy:2;
	u16 usewPwio:3;
	u16 psb:1;
	u16 aggwegation:1;
	u16 accessPowicy:2;
	u16 diwection:2;
	u16 tsid:4;
	u16 twafficType:1;
#ewse
	u16 twafficType:1;
	u16 tsid:4;
	u16 diwection:2;
	u16 accessPowicy:2;
	u16 aggwegation:1;
	u16 psb:1;
	u16 usewPwio:3;
	u16 ackPowicy:2;
#endif
};

/* Fwag to scheduwe the twaffic type */
stwuct wcn36xx_haw_ts_info_sch {
#ifndef ANI_WITTWE_BIT_ENDIAN
	u8 wsvd:7;
	u8 scheduwe:1;
#ewse
	u8 scheduwe:1;
	u8 wsvd:7;
#endif
};

/* Twaffic and scheduwing info */
stwuct wcn36xx_haw_ts_info {
	stwuct wcn36xx_haw_ts_info_tfc twaffic;
	stwuct wcn36xx_haw_ts_info_sch scheduwe;
};

/* Infowmation ewements */
stwuct wcn36xx_haw_tspec_ie {
	u8 type;
	u8 wength;
	stwuct wcn36xx_haw_ts_info ts_info;
	u16 nom_msdu_size;
	u16 max_msdu_size;
	u32 min_svc_intewvaw;
	u32 max_svc_intewvaw;
	u32 inact_intewvaw;
	u32 suspend_intewvaw;
	u32 svc_stawt_time;
	u32 min_data_wate;
	u32 mean_data_wate;
	u32 peak_data_wate;
	u32 max_buwst_sz;
	u32 deway_bound;
	u32 min_phy_wate;
	u16 suwpwus_bw;
	u16 medium_time;
};

stwuct add_ts_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Station Index */
	u16 sta_index;

	/* TSPEC handwew uniquewy identifying a TSPEC fow a STA in a BSS */
	u16 tspec_index;

	/* To pwogwam TPE with wequiwed pawametews */
	stwuct wcn36xx_haw_tspec_ie tspec;

	/* U-APSD Fwags: 1b pew AC.  Encoded as fowwows:
	   b7 b6 b5 b4 b3 b2 b1 b0 =
	   X  X  X  X  BE BK VI VO */
	u8 uapsd;

	/* These pawametews awe fow aww the access categowies */

	/* Sewvice Intewvaw */
	u32 sewvice_intewvaw[WCN36XX_HAW_MAX_AC];

	/* Suspend Intewvaw */
	u32 suspend_intewvaw[WCN36XX_HAW_MAX_AC];

	/* Deway Intewvaw */
	u32 deway_intewvaw[WCN36XX_HAW_MAX_AC];
};

stwuct add_ws_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct dew_ts_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Station Index */
	u16 sta_index;

	/* TSPEC identifiew uniquewy identifying a TSPEC fow a STA in a BSS */
	u16 tspec_index;

	/* To wookup station id using the mac addwess */
	u8 bssid[ETH_AWEN];
};

stwuct dew_ts_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

/* End of TSpec Pawametews */

/* Stawt of BWOCK ACK wewated Pawametews */

stwuct wcn36xx_haw_add_ba_session_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Station Index */
	u16 sta_index;

	/* Peew MAC Addwess */
	u8 mac_addw[ETH_AWEN];

	/* ADDBA Action Fwame diawog token
	   HAW wiww not intewpwet this object */
	u8 diawog_token;

	/* TID fow which the BA is being setup
	   This identifies the TC ow TS of intewest */
	u8 tid;

	/* 0 - Dewayed BA (Not suppowted)
	   1 - Immediate BA */
	u8 powicy;

	/* Indicates the numbew of buffews fow this TID (baTID)
	   NOTE - This is the wequested buffew size. When this
	   is pwocessed by HAW and subsequentwy by HDD, it is
	   possibwe that HDD may change this buffew size. Any
	   change in the buffew size shouwd be noted by PE and
	   advewtized appwopwiatewy in the ADDBA wesponse */
	u16 buffew_size;

	/* BA timeout in TU's 0 means no timeout wiww occuw */
	u16 timeout;

	/* b0..b3 - Fwagment Numbew - Awways set to 0
	   b4..b15 - Stawting Sequence Numbew of fiwst MSDU
	   fow which this BA is setup */
	u16 ssn;

	/* ADDBA diwection
	   1 - Owiginatow
	   0 - Wecipient */
	u8 diwection;
} __packed;

stwuct wcn36xx_haw_add_ba_session_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	/* Diawog token */
	u8 diawog_token;

	/* TID fow which the BA session has been setup */
	u8 ba_tid;

	/* BA Buffew Size awwocated fow the cuwwent BA session */
	u8 ba_buffew_size;

	u8 ba_session_id;

	/* Weowdewing Window buffew */
	u8 win_size;

	/* Station Index to id the sta */
	u8 sta_index;

	/* Stawting Sequence Numbew */
	u16 ssn;
} __packed;

stwuct wcn36xx_haw_add_ba_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Session Id */
	u8 session_id;

	/* Weowdew Window Size */
	u8 win_size;
/* Owd FW 1.2.2.4 does not suppowt this*/
#ifdef FEATUWE_ON_CHIP_WEOWDEWING
	u8 weowdewing_done_on_chip;
#endif
} __packed;

stwuct wcn36xx_haw_add_ba_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	/* Diawog token */
	u8 diawog_token;
} __packed;

stwuct add_ba_info {
	u16 ba_enabwe:1;
	u16 stawting_seq_num:12;
	u16 wesewved:3;
};

stwuct wcn36xx_haw_twiggew_ba_wsp_candidate {
	u8 sta_addw[ETH_AWEN];
	stwuct add_ba_info ba_info[STACFG_MAX_TC];
} __packed;

stwuct wcn36xx_haw_twiggew_ba_weq_candidate {
	u8 sta_index;
	u8 tid_bitmap;
} __packed;

stwuct wcn36xx_haw_twiggew_ba_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Session Id */
	u8 session_id;

	/* baCandidateCnt is fowwowed by twiggew BA
	 * Candidate Wist(tTwiggewBaCandidate)
	 */
	u16 candidate_cnt;

} __packed;

stwuct wcn36xx_haw_twiggew_ba_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* TO SUPPOWT BT-AMP */
	u8 bssid[ETH_AWEN];

	/* success ow faiwuwe */
	u32 status;

	/* baCandidateCnt is fowwowed by twiggew BA
	 * Wsp Candidate Wist(tTwiggewWspBaCandidate)
	 */
	u16 candidate_cnt;
} __packed;

stwuct wcn36xx_haw_dew_ba_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Station Index */
	u16 sta_index;

	/* TID fow which the BA session is being deweted */
	u8 tid;

	/* DEWBA diwection
	   1 - Owiginatow
	   0 - Wecipient */
	u8 diwection;
} __packed;

stwuct wcn36xx_haw_dew_ba_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
} __packed;

stwuct tsm_stats_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Twaffic Id */
	u8 tid;

	u8 bssid[ETH_AWEN];
};

stwuct tsm_stats_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/*success ow faiwuwe */
	u32 status;

	/* Upwink Packet Queue deway */
	u16 upwink_pkt_queue_deway;

	/* Upwink Packet Queue deway histogwam */
	u16 upwink_pkt_queue_deway_hist[4];

	/* Upwink Packet Twansmit deway */
	u32 upwink_pkt_tx_deway;

	/* Upwink Packet woss */
	u16 upwink_pkt_woss;

	/* Upwink Packet count */
	u16 upwink_pkt_count;

	/* Woaming count */
	u8 woaming_count;

	/* Woaming Deway */
	u16 woaming_deway;
};

stwuct set_key_done_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/*bssid of the keys */
	u8 bssidx;
	u8 enc_type;
};

stwuct wcn36xx_haw_nv_img_downwoad_weq_msg {
	/* Note: The wength specified in wcn36xx_haw_nv_img_downwoad_weq_msg
	 * messages shouwd be
	 * headew.wen = sizeof(wcn36xx_haw_nv_img_downwoad_weq_msg) +
	 * nv_img_buffew_size */
	stwuct wcn36xx_haw_msg_headew headew;

	/* Fwagment sequence numbew of the NV Image. Note that NV Image
	 * might not fit into one message due to size wimitation of the SMD
	 * channew FIFO. UMAC can hence choose to chop the NV bwob into
	 * muwtipwe fwagments stawting with seqeunce numbew 0, 1, 2 etc.
	 * The wast fwagment MUST be indicated by mawking the
	 * isWastFwagment fiewd to 1. Note that aww the NV bwobs wouwd be
	 * concatenated togethew by HAW without any padding bytes in
	 * between.*/
	u16 fwag_numbew;

	/* Is this the wast fwagment? When set to 1 it indicates that no
	 * mowe fwagments wiww be sent by UMAC and HAW can concatenate aww
	 * the NV bwobs wcvd & pwoceed with the pawsing. HAW wouwd genewate
	 * a WCN36XX_HAW_DOWNWOAD_NV_WSP to the WCN36XX_HAW_DOWNWOAD_NV_WEQ
	 * aftew it weceives each fwagment */
	u16 wast_fwagment;

	/* NV Image size (numbew of bytes) */
	u32 nv_img_buffew_size;

	/* Fowwowing the 'nv_img_buffew_size', thewe shouwd be
	 * nv_img_buffew_size bytes of NV Image i.e.
	 * u8[nv_img_buffew_size] */
} __packed;

stwuct wcn36xx_haw_nv_img_downwoad_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Success ow Faiwuwe. HAW wouwd genewate a
	 * WCN36XX_HAW_DOWNWOAD_NV_WSP aftew each fwagment */
	u32 status;
} __packed;

stwuct wcn36xx_haw_nv_stowe_ind {
	/* Note: The wength specified in tHawNvStoweInd messages shouwd be
	 * headew.msgWen = sizeof(tHawNvStoweInd) + nvBwobSize */
	stwuct wcn36xx_haw_msg_headew headew;

	/* NV Item */
	u32 tabwe_id;

	/* Size of NV Bwob */
	u32 nv_bwob_size;

	/* Fowwowing the 'nvBwobSize', thewe shouwd be nvBwobSize bytes of
	 * NV bwob i.e. u8[nvBwobSize] */
};

/* End of Bwock Ack Wewated Pawametews */

#define WCN36XX_HAW_CIPHEW_SEQ_CTW_SIZE 6

/* Definition fow MIC faiwuwe indication MAC wepowts this each time a MIC
 * faiwuwe occuwes on Wx TKIP packet
 */
stwuct mic_faiwuwe_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 bssid[ETH_AWEN];

	/* addwess used to compute MIC */
	u8 swc_addw[ETH_AWEN];

	/* twansmittew addwess */
	u8 ta_addw[ETH_AWEN];

	u8 dst_addw[ETH_AWEN];

	u8 muwticast;

	/* fiwst byte of IV */
	u8 iv1;

	/* second byte of IV */
	u8 key_id;

	/* sequence numbew */
	u8 tsc[WCN36XX_HAW_CIPHEW_SEQ_CTW_SIZE];

	/* weceive addwess */
	u8 wx_addw[ETH_AWEN];
};

stwuct update_vht_op_mode_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u16 op_mode;
	u16 sta_id;
};

stwuct update_vht_op_mode_pawams_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u32 status;
};

stwuct update_beacon_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 bss_index;

	/* showtPweambwe mode. HAW shouwd update aww the STA wates when it
	 * weceives this message */
	u8 showt_pweambwe;

	/* showt Swot time. */
	u8 showt_swot_time;

	/* Beacon Intewvaw */
	u16 beacon_intewvaw;

	/* Pwotection wewated */
	u8 wwa_coexist;
	u8 wwb_coexist;
	u8 wwg_coexist;
	u8 ht20_coexist;
	u8 wwn_non_gf_coexist;
	u8 wsig_tx_op_pwotection_fuww_suppowt;
	u8 wifs_mode;

	u16 pawam_change_bitmap;
};

stwuct update_beacon_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	u32 status;
};

stwuct wcn36xx_haw_send_beacon_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* wength of the tempwate + 6. Onwy qcom knows why */
	u32 beacon_wength6;

	/* wength of the tempwate. */
	u32 beacon_wength;

	/* Beacon data. */
	u8 beacon[BEACON_TEMPWATE_SIZE - sizeof(u32)];

	u8 bssid[ETH_AWEN];

	/* TIM IE offset fwom the beginning of the tempwate. */
	u32 tim_ie_offset;

	/* P2P IE offset fwom the begining of the tempwate */
	u16 p2p_ie_offset;
} __packed;

stwuct send_beacon_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	u32 status;
} __packed;

stwuct enabwe_wadaw_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 bssid[ETH_AWEN];
	u8 channew;
};

stwuct enabwe_wadaw_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Wink Pawametews */
	u8 bssid[ETH_AWEN];

	/* success ow faiwuwe */
	u32 status;
};

stwuct wadaw_detect_intw_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 wadaw_det_channew;
};

stwuct wadaw_detect_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* channew numbew in which the WADAW detected */
	u8 channew_numbew;

	/* WADAW puwse width in usecond */
	u16 wadaw_puwse_width;

	/* Numbew of WADAW puwses */
	u16 num_wadaw_puwse;
};

stwuct wcn36xx_haw_get_tpc_wepowt_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 sta[ETH_AWEN];
	u8 diawog_token;
	u8 txpowew;
};

stwuct wcn36xx_haw_get_tpc_wepowt_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_send_pwobe_wesp_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 pwobe_wesp_tempwate[BEACON_TEMPWATE_SIZE];
	u32 pwobe_wesp_tempwate_wen;
	u32 pwoxy_pwobe_weq_vawid_ie_bmap[8];
	u8 bssid[ETH_AWEN];
};

stwuct send_pwobe_wesp_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct send_unknown_fwame_wx_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_dewete_sta_context_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u16 aid;
	u16 sta_id;

	/* TO SUPPOWT BT-AMP */
	u8 bssid[ETH_AWEN];

	/* HAW copies bssid fwom the sta tabwe. */
	u8 addw2[ETH_AWEN];

	/* To unify the keepawive / unknown A2 / tim-based disa */
	u16 weason_code;
} __packed;

stwuct indicate_dew_sta {
	stwuct wcn36xx_haw_msg_headew headew;
	u8 aid;
	u8 sta_index;
	u8 bss_index;
	u8 weason_code;
	u32 status;
};

stwuct bt_amp_event_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	enum bt_amp_event_type btAmpEventType;
};

stwuct bt_amp_event_wsp {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct tw_haw_fwush_ac_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Station Index. owiginates fwom HAW */
	u8 sta_id;

	/* TID fow which the twansmit queue is being fwushed */
	u8 tid;
};

stwuct tw_haw_fwush_ac_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Station Index. owiginates fwom HAW */
	u8 sta_id;

	/* TID fow which the twansmit queue is being fwushed */
	u8 tid;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_entew_imps_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
} __packed;

stwuct wcn36xx_haw_exit_imps_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
} __packed;

stwuct wcn36xx_haw_entew_bmps_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 bss_index;

	/* TBTT vawue dewived fwom the wast beacon */
#ifndef BUIWD_QWPTTSTATIC
	u64 tbtt;
#endif
	u8 dtim_count;

	/* DTIM pewiod given to HAW duwing association may not be vawid, if
	 * association is based on PwobeWsp instead of beacon. */
	u8 dtim_pewiod;

	/* Fow CCX and 11W Woaming */
	u32 wssi_fiwtew_pewiod;

	u32 num_beacon_pew_wssi_avewage;
	u8 wssi_fiwtew_enabwe;
} __packed;

stwuct wcn36xx_haw_exit_bmps_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 send_data_nuww;
	u8 bss_index;
} __packed;

stwuct wcn36xx_haw_missed_beacon_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 bss_index;
} __packed;

/* Beacon Fiwtewing data stwuctuwes */

stwuct beacon_fiwtew_ie {
	u8 ewement_id;
	u8 check_ie_pwesence;
	u8 offset;
	u8 vawue;
	u8 bitmask;
	u8 wef;
} __packed;

#define WCN36XX_FIWTEW_CAPABIWITY_MASK		0x73cf
#define WCN36XX_FIWTEW_IE_DS_CHANNEW_MASK	0x00
#define WCN36XX_FIWTEW_IE_EWP_FIWTEW_MASK	0xF8
#define WCN36XX_FIWTEW_IE_EDCA_FIWTEW_MASK	0xF0
#define WCN36XX_FIWTEW_IE_QOS_FIWTEW_MASK	0xF0
#define WCN36XX_FIWTEW_IE_CHANNEW_SWITCH_MASK	0x00
#define WCN36XX_FIWTEW_IE_HT_BYTE0_FIWTEW_MASK	0x00
#define WCN36XX_FIWTEW_IE_HT_BYTE1_FIWTEW_MASK	0xF8
#define WCN36XX_FIWTEW_IE_HT_BYTE2_FIWTEW_MASK	0xEB
#define WCN36XX_FIWTEW_IE_HT_BYTE5_FIWTEW_MASK	0xFD
#define WCN36XX_FIWTEW_IE_PWW_CONSTWAINT_MASK	0x00
#define WCN36XX_FIWTEW_IE_OPMODE_NOTIF_MASK	0x00
#define WCN36XX_FIWTEW_IE_VHTOP_CHWIDTH_MASK	0xFC
#define WCN36XX_FIWTEW_IE_WSN_MASK		0x00
#define WCN36XX_FIWTEW_IE_VENDOW_MASK		0x00

/* The above stwuctuwe wouwd be fowwowed by muwtipwe of bewow mentioned
 * stwuctuwe
 */

stwuct wcn36xx_haw_add_bcn_fiwtew_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u16 capabiwity_info;
	u16 capabiwity_mask;
	u16 beacon_intewvaw;
	u16 ie_num;
	u8 bss_index;
	u8 wesewved;
} __packed;

stwuct wcn36xx_haw_wem_bcn_fiwtew_weq {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 ie_Count;
	u8 wem_ie_id[1];
} __packed;

#define WCN36XX_HAW_IPV4_AWP_WEPWY_OFFWOAD                  0
#define WCN36XX_HAW_IPV6_NEIGHBOW_DISCOVEWY_OFFWOAD         1
#define WCN36XX_HAW_IPV6_NS_OFFWOAD                         2
#define WCN36XX_HAW_IPV6_ADDW_WEN                           16
#define WCN36XX_HAW_OFFWOAD_DISABWE                         0
#define WCN36XX_HAW_OFFWOAD_ENABWE                          1
#define WCN36XX_HAW_OFFWOAD_BCAST_FIWTEW_ENABWE             0x2
#define WCN36XX_HAW_OFFWOAD_MCAST_FIWTEW_ENABWE             0x4
#define WCN36XX_HAW_OFFWOAD_NS_AND_MCAST_FIWTEW_ENABWE	\
	(WCN36XX_HAW_OFFWOAD_ENABWE | WCN36XX_HAW_OFFWOAD_MCAST_FIWTEW_ENABWE)
#define WCN36XX_HAW_OFFWOAD_AWP_AND_BCAST_FIWTEW_ENABWE	\
	(WCN36XX_HAW_OFFWOAD_ENABWE | WCN36XX_HAW_OFFWOAD_BCAST_FIWTEW_ENABWE)
#define WCN36XX_HAW_IPV6_OFFWOAD_ADDW_MAX		0x02

stwuct wcn36xx_haw_ns_offwoad_pawams {
	u8 swc_ipv6_addw[WCN36XX_HAW_IPV6_ADDW_WEN];
	u8 sewf_ipv6_addw[WCN36XX_HAW_IPV6_ADDW_WEN];

	/* Onwy suppowt 2 possibwe Netwowk Advewtisement IPv6 addwess */
	u8 tawget_ipv6_addw1[WCN36XX_HAW_IPV6_ADDW_WEN];
	u8 tawget_ipv6_addw2[WCN36XX_HAW_IPV6_ADDW_WEN];

	u8 sewf_addw[ETH_AWEN];
	u8 swc_ipv6_addw_vawid:1;
	u8 tawget_ipv6_addw1_vawid:1;
	u8 tawget_ipv6_addw2_vawid:1;
	u8 wesewved1:5;

	/* make it DWOWD awigned */
	u8 wesewved2;

	/* swot index fow this offwoad */
	u32 swot_index;
	u8 bss_index;
} __packed;

stwuct wcn36xx_haw_host_offwoad_weq {
	u8 offwoad_type;

	/* enabwe ow disabwe */
	u8 enabwe;

	union {
		u8 host_ipv4_addw[4];
		u8 host_ipv6_addw[WCN36XX_HAW_IPV6_ADDW_WEN];
	} u;
} __packed;

stwuct wcn36xx_haw_host_offwoad_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_host_offwoad_weq host_offwoad_pawams;
	stwuct wcn36xx_haw_ns_offwoad_pawams ns_offwoad_pawams;
} __packed;

/* Packet Types. */
#define WCN36XX_HAW_KEEP_AWIVE_NUWW_PKT              1
#define WCN36XX_HAW_KEEP_AWIVE_UNSOWICIT_AWP_WSP     2

/* Enabwe ow disabwe keep awive */
#define WCN36XX_HAW_KEEP_AWIVE_DISABWE   0
#define WCN36XX_HAW_KEEP_AWIVE_ENABWE    1
#define WCN36XX_KEEP_AWIVE_TIME_PEWIOD	 30 /* unit: s */

/* Keep Awive wequest. */
stwuct wcn36xx_haw_keep_awive_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 packet_type;
	u32 time_pewiod;
	u8 host_ipv4_addw[WCN36XX_HAW_IPV4_ADDW_WEN];
	u8 dest_ipv4_addw[WCN36XX_HAW_IPV4_ADDW_WEN];
	u8 dest_addw[ETH_AWEN];
	u8 bss_index;
} __packed;

stwuct wcn36xx_haw_wssi_thweshowd_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	s8 thweshowd1:8;
	s8 thweshowd2:8;
	s8 thweshowd3:8;
	u8 thwes1_pos_notify:1;
	u8 thwes1_neg_notify:1;
	u8 thwes2_pos_notify:1;
	u8 thwes2_neg_notify:1;
	u8 thwes3_pos_notify:1;
	u8 thwes3_neg_notify:1;
	u8 wesewved10:2;
};

stwuct wcn36xx_haw_entew_uapsd_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 bk_dewivewy:1;
	u8 be_dewivewy:1;
	u8 vi_dewivewy:1;
	u8 vo_dewivewy:1;
	u8 bk_twiggew:1;
	u8 be_twiggew:1;
	u8 vi_twiggew:1;
	u8 vo_twiggew:1;
	u8 bss_index;
};

stwuct wcn36xx_haw_exit_uapsd_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	u8 bss_index;
};

#define WCN36XX_HAW_WOWW_BCAST_PATTEWN_MAX_SIZE 128
#define WCN36XX_HAW_WOWW_BCAST_MAX_NUM_PATTEWNS 16

stwuct wcn36xx_haw_woww_add_bcast_ptwn_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Pattewn ID */
	u8 id;

	/* Pattewn byte offset fwom beginning of the 802.11 packet to stawt
	 * of the wake-up pattewn */
	u8 byte_Offset;

	/* Non-Zewo Pattewn size */
	u8 size;

	/* Pattewn */
	u8 pattewn[WCN36XX_HAW_WOWW_BCAST_PATTEWN_MAX_SIZE];

	/* Non-zewo pattewn mask size */
	u8 mask_size;

	/* Pattewn mask */
	u8 mask[WCN36XX_HAW_WOWW_BCAST_PATTEWN_MAX_SIZE];

	/* Extwa pattewn */
	u8 extwa[WCN36XX_HAW_WOWW_BCAST_PATTEWN_MAX_SIZE];

	/* Extwa pattewn mask */
	u8 mask_extwa[WCN36XX_HAW_WOWW_BCAST_PATTEWN_MAX_SIZE];

	u8 bss_index;
};

stwuct wcn36xx_haw_wow_dew_bcast_ptwn_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Pattewn ID of the wakeup pattewn to be deweted */
	u8 id;
	u8 bss_index;
};

stwuct wcn36xx_haw_woww_entew_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Enabwes/disabwes magic packet fiwtewing */
	u8 magic_packet_enabwe;

	/* Magic pattewn */
	u8 magic_pattewn[ETH_AWEN];

	/* Enabwes/disabwes packet pattewn fiwtewing in fiwmwawe. Enabwing
	 * this fwag enabwes bwoadcast pattewn matching in Fiwmwawe. If
	 * unicast pattewn matching is awso desiwed,
	 * ucUcastPattewnFiwtewingEnabwe fwag must be set tot twue as weww
	 */
	u8 pattewn_fiwtewing_enabwe;

	/* Enabwes/disabwes unicast packet pattewn fiwtewing. This fwag
	 * specifies whethew we want to do pattewn match on unicast packets
	 * as weww and not just bwoadcast packets. This fwag has no effect
	 * if the ucPattewnFiwtewingEnabwe (main contwowwing fwag) is set
	 * to fawse
	 */
	u8 ucast_pattewn_fiwtewing_enabwe;

	/* This configuwation is vawid onwy when magicPktEnabwe=1. It
	 * wequests hawdwawe to wake up when it weceives the Channew Switch
	 * Action Fwame.
	 */
	u8 wow_channew_switch_weceive;

	/* This configuwation is vawid onwy when magicPktEnabwe=1. It
	 * wequests hawdwawe to wake up when it weceives the
	 * Deauthentication Fwame.
	 */
	u8 wow_deauth_weceive;

	/* This configuwation is vawid onwy when magicPktEnabwe=1. It
	 * wequests hawdwawe to wake up when it weceives the Disassociation
	 * Fwame.
	 */
	u8 wow_disassoc_weceive;

	/* This configuwation is vawid onwy when magicPktEnabwe=1. It
	 * wequests hawdwawe to wake up when it has missed consecutive
	 * beacons. This is a hawdwawe wegistew configuwation (NOT a
	 * fiwmwawe configuwation).
	 */
	u8 wow_max_missed_beacons;

	/* This configuwation is vawid onwy when magicPktEnabwe=1. This is
	 * a timeout vawue in units of micwosec. It wequests hawdwawe to
	 * unconditionawwy wake up aftew it has stayed in WoWWAN mode fow
	 * some time. Set 0 to disabwe this featuwe.
	 */
	u8 wow_max_sweep;

	/* This configuwation diwects the WoW packet fiwtewing to wook fow
	 * EAP-ID wequests embedded in EAPOW fwames and use this as a wake
	 * souwce.
	 */
	u8 wow_eap_id_wequest_enabwe;

	/* This configuwation diwects the WoW packet fiwtewing to wook fow
	 * EAPOW-4WAY wequests and use this as a wake souwce.
	 */
	u8 wow_eapow_4way_enabwe;

	/* This configuwation awwows a host wakeup on an netwowk scan
	 * offwoad match.
	 */
	u8 wow_net_scan_offwoad_match;

	/* This configuwation awwows a host wakeup on any GTK wekeying
	 * ewwow.
	 */
	u8 wow_gtk_wekey_ewwow;

	/* This configuwation awwows a host wakeup on BSS connection woss.
	 */
	u8 wow_bss_connection_woss;

	u8 bss_index;
};

stwuct wcn36xx_haw_woww_exit_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 bss_index;
};

stwuct wcn36xx_haw_get_wssi_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
};

stwuct wcn36xx_haw_get_woam_wssi_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Vawid STA Idx fow pew STA stats wequest */
	u32 sta_id;
};

stwuct wcn36xx_haw_set_uapsd_ac_pawams_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* STA index */
	u8 sta_idx;

	/* Access Categowy */
	u8 ac;

	/* Usew Pwiowity */
	u8 up;

	/* Sewvice Intewvaw */
	u32 sewvice_intewvaw;

	/* Suspend Intewvaw */
	u32 suspend_intewvaw;

	/* Deway Intewvaw */
	u32 deway_intewvaw;
};

stwuct wcn36xx_haw_configuwe_wxp_fiwtew_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 set_mcst_bcst_fiwtew_setting;
	u8 set_mcst_bcst_fiwtew;
};

stwuct wcn36xx_haw_entew_imps_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_exit_imps_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_entew_bmps_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	u8 bss_index;
} __packed;

stwuct wcn36xx_haw_exit_bmps_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	u8 bss_index;
} __packed;

stwuct wcn36xx_haw_entew_uapsd_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	u8 bss_index;
};

stwuct wcn36xx_haw_exit_uapsd_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	u8 bss_index;
};

stwuct wcn36xx_haw_wssi_notification_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u32 wssi_thwes1_pos_cwoss:1;
	u32 wssi_thwes1_neg_cwoss:1;
	u32 wssi_thwes2_pos_cwoss:1;
	u32 wssi_thwes2_neg_cwoss:1;
	u32 wssi_thwes3_pos_cwoss:1;
	u32 wssi_thwes3_neg_cwoss:1;
	u32 avg_wssi:8;
	u32 wesewved:18;

};

stwuct wcn36xx_haw_get_wssio_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
	s8 wssi;

};

stwuct wcn36xx_haw_get_woam_wssi_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	u8 sta_id;
	s8 wssi;
};

stwuct wcn36xx_haw_woww_entew_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
	u8 bss_index;
};

stwuct wcn36xx_haw_woww_exit_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
	u8 bss_index;
};

stwuct wcn36xx_haw_add_bcn_fiwtew_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_wem_bcn_fiwtew_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_add_woww_bcast_ptwn_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
	u8 bss_index;
};

stwuct wcn36xx_haw_dew_woww_bcast_ptwn_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
	u8 bss_index;
};

stwuct wcn36xx_haw_host_offwoad_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_keep_awive_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_set_wssi_thwesh_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_set_uapsd_ac_pawams_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_configuwe_wxp_fiwtew_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct set_max_tx_pww_weq {
	stwuct wcn36xx_haw_msg_headew headew;

	/* BSSID is needed to identify which session issued this wequest.
	 * As the wequest has powew constwaints, this shouwd be appwied
	 * onwy to that session */
	u8 bssid[ETH_AWEN];

	u8 sewf_addw[ETH_AWEN];

	/* In wequest, powew == MaxTx powew to be used. */
	u8 powew;
};

stwuct set_max_tx_pww_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* powew == tx powew used fow management fwames */
	u8 powew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct set_tx_pww_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* TX Powew in miwwi watts */
	u32 tx_powew;

	u8 bss_index;
};

stwuct set_tx_pww_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct get_tx_pww_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 sta_id;
};

stwuct get_tx_pww_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	/* TX Powew in miwwi watts */
	u32 tx_powew;
};

stwuct set_p2p_gonoa_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 opp_ps;
	u32 ct_window;
	u8 count;
	u32 duwation;
	u32 intewvaw;
	u32 singwe_noa_duwation;
	u8 ps_sewection;
};

stwuct set_p2p_gonoa_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_add_sta_sewf_weq {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 sewf_addw[ETH_AWEN];
	u32 status;
} __packed;

stwuct wcn36xx_haw_add_sta_sewf_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	/* Sewf STA Index */
	u8 sewf_sta_index;

	/* DPU Index (IGTK, PTK, GTK aww same) */
	u8 dpu_index;

	/* DPU Signatuwe */
	u8 dpu_signatuwe;
} __packed;

stwuct wcn36xx_haw_dew_sta_sewf_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 sewf_addw[ETH_AWEN];
} __packed;

stwuct wcn36xx_haw_dew_sta_sewf_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/*success ow faiwuwe */
	u32 status;

	u8 sewf_addw[ETH_AWEN];
} __packed;

stwuct aggw_add_ts_weq {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Station Index */
	u16 sta_idx;

	/* TSPEC handwew uniquewy identifying a TSPEC fow a STA in a BSS.
	 * This wiww cawwy the bitmap with the bit positions wepwesenting
	 * diffewent AC.s */
	u16 tspec_index;

	/* Tspec info pew AC To pwogwam TPE with wequiwed pawametews */
	stwuct wcn36xx_haw_tspec_ie tspec[WCN36XX_HAW_MAX_AC];

	/* U-APSD Fwags: 1b pew AC.  Encoded as fowwows:
	   b7 b6 b5 b4 b3 b2 b1 b0 =
	   X  X  X  X  BE BK VI VO */
	u8 uapsd;

	/* These pawametews awe fow aww the access categowies */

	/* Sewvice Intewvaw */
	u32 sewvice_intewvaw[WCN36XX_HAW_MAX_AC];

	/* Suspend Intewvaw */
	u32 suspend_intewvaw[WCN36XX_HAW_MAX_AC];

	/* Deway Intewvaw */
	u32 deway_intewvaw[WCN36XX_HAW_MAX_AC];
};

stwuct aggw_add_ts_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status0;

	/* FIXME PWIMA fow futuwe use fow 11W */
	u32 status1;
};

stwuct wcn36xx_haw_configuwe_apps_cpu_wakeup_state_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 is_apps_cpu_awake;
};

stwuct wcn36xx_haw_configuwe_apps_cpu_wakeup_state_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_dump_cmd_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u32 awg1;
	u32 awg2;
	u32 awg3;
	u32 awg4;
	u32 awg5;
} __packed;

stwuct wcn36xx_haw_dump_cmd_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	/* Wength of the wesponce message */
	u32 wsp_wength;

	/* FIXME: Cuwwentwy considewing the wesponce wiww be wess than
	 * 100bytes */
	u8 wsp_buffew[DUMPCMD_WSP_BUFFEW];
} __packed;

#define WWAN_COEX_IND_DATA_SIZE (4)
#define WWAN_COEX_IND_TYPE_DISABWE_HB_MONITOW (0)
#define WWAN_COEX_IND_TYPE_ENABWE_HB_MONITOW (1)

stwuct coex_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Coex Indication Type */
	u32 type;

	/* Coex Indication Data */
	u32 data[WWAN_COEX_IND_DATA_SIZE];
};

stwuct wcn36xx_haw_tx_compw_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Tx Compwete Indication Success ow Faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_wwan_host_suspend_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u32 configuwed_mcst_bcst_fiwtew_setting;
	u32 active_session_count;
};

stwuct wcn36xx_haw_wwan_excwude_unencwpted_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 dot11_excwude_unencwypted;
	u8 bssid[ETH_AWEN];
};

stwuct noa_attw_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 index;
	u8 opp_ps_fwag;
	u16 ctwin;

	u16 noa1_intewvaw_count;
	u16 bss_index;
	u32 noa1_duwation;
	u32 noa1_intewvaw;
	u32 noa1_stawttime;

	u16 noa2_intewvaw_count;
	u16 wesewved2;
	u32 noa2_duwation;
	u32 noa2_intewvaw;
	u32 noa2_stawt_time;

	u32 status;
};

stwuct noa_stawt_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u32 status;
	u32 bss_index;
};

stwuct wcn36xx_haw_wwan_host_wesume_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 configuwed_mcst_bcst_fiwtew_setting;
};

stwuct wcn36xx_haw_host_wesume_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

stwuct wcn36xx_haw_dew_ba_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u16 sta_idx;

	/* Peew MAC Addwess, whose BA session has timed out */
	u8 peew_addw[ETH_AWEN];

	/* TID fow which a BA session timeout is being twiggewed */
	u8 ba_tid;

	/* DEWBA diwection
	 * 1 - Owiginatow
	 * 0 - Wecipient
	 */
	u8 diwection;

	u32 weason_code;

	/* TO SUPPOWT BT-AMP */
	u8 bssid[ETH_AWEN];
};

/* PNO Messages */

/* Max numbew of channews that a netwowk can be found on */
#define WCN36XX_HAW_PNO_MAX_NETW_CHANNEWS  26

/* Max numbew of channews that a netwowk can be found on */
#define WCN36XX_HAW_PNO_MAX_NETW_CHANNEWS_EX  60

/* Maximum numbews of netwowks suppowted by PNO */
#define WCN36XX_HAW_PNO_MAX_SUPP_NETWOWKS  16

/* The numbew of scan time intewvaws that can be pwogwammed into PNO */
#define WCN36XX_HAW_PNO_MAX_SCAN_TIMEWS    10

/* Maximum size of the pwobe tempwate */
#define WCN36XX_HAW_PNO_MAX_PWOBE_SIZE     450

/* Type of PNO enabwing:
 *
 * Immediate - scanning wiww stawt immediatewy and PNO pwoceduwe wiww be
 * wepeated based on timew
 *
 * Suspend - scanning wiww stawt at suspend
 *
 * Wesume - scanning wiww stawt on system wesume
 */
enum pno_mode {
	PNO_MODE_IMMEDIATE,
	PNO_MODE_ON_SUSPEND,
	PNO_MODE_ON_WESUME,
	PNO_MODE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

/* Authentication type */
enum auth_type {
	AUTH_TYPE_ANY = 0,
	AUTH_TYPE_OPEN_SYSTEM = 1,

	/* Uppew wayew authentication types */
	AUTH_TYPE_WPA = 2,
	AUTH_TYPE_WPA_PSK = 3,

	AUTH_TYPE_WSN = 4,
	AUTH_TYPE_WSN_PSK = 5,
	AUTH_TYPE_FT_WSN = 6,
	AUTH_TYPE_FT_WSN_PSK = 7,
	AUTH_TYPE_WAPI_WAI_CEWTIFICATE = 8,
	AUTH_TYPE_WAPI_WAI_PSK = 9,

	AUTH_TYPE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

/* Encwyption type */
enum ed_type {
	ED_ANY = 0,
	ED_NONE = 1,
	ED_WEP = 2,
	ED_TKIP = 3,
	ED_CCMP = 4,
	ED_WPI = 5,

	ED_TYPE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

/* SSID bwoadcast  type */
enum ssid_bcast_type {
	BCAST_UNKNOWN = 0,
	BCAST_NOWMAW = 1,
	BCAST_HIDDEN = 2,

	BCAST_TYPE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE
};

/* The netwowk descwiption fow which PNO wiww have to wook fow */
stwuct netwowk_type {
	/* SSID of the BSS */
	stwuct wcn36xx_haw_mac_ssid ssid;

	/* Authentication type fow the netwowk */
	enum auth_type authentication;

	/* Encwyption type fow the netwowk */
	enum ed_type encwyption;

	/* Indicate the channew on which the Netwowk can be found 0 - if
	 * aww channews */
	u8 channew_count;
	u8 channews[WCN36XX_HAW_PNO_MAX_NETW_CHANNEWS];

	/* Indicates the WSSI thweshowd fow the netwowk to be considewed */
	u8 wssi_thweshowd;
};

stwuct scan_timew {
	/* How much it shouwd wait */
	u32 vawue;

	/* How many times it shouwd wepeat that wait vawue 0 - keep using
	 * this timew untiw PNO is disabwed */
	u32 wepeat;

	/* e.g: 2 3 4 0 - it wiww wait 2s between consecutive scans fow 3
	 * times - aftew that it wiww wait 4s between consecutive scans
	 * untiw disabwed */
};

/* The netwowk pawametews to be sent to the PNO awgowithm */
stwuct scan_timews_type {
	/* set to 0 if you wish fow PNO to use its defauwt tewescopic timew */
	u8 count;

	/* A set vawue wepwesents the amount of time that PNO wiww wait
	 * between two consecutive scan pwoceduwes If the desiwed is fow a
	 * unifowm timew that fiwes awways at the exact same intewvaw - one
	 * singwe vawue is to be set If thewe is a desiwe fow a mowe
	 * compwex - tewescopic wike timew muwtipwe vawues can be set -
	 * once PNO weaches the end of the awway it wiww continue scanning
	 * at intewvaws pwesented by the wast vawue */
	stwuct scan_timew vawues[WCN36XX_HAW_PNO_MAX_SCAN_TIMEWS];
};

/* Pwefewwed netwowk wist wequest */
stwuct set_pwef_netw_wist_weq {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Enabwe PNO */
	u32 enabwe;

	/* Immediate,  On Suspend,   On Wesume */
	enum pno_mode mode;

	/* Numbew of netwowks sent fow PNO */
	u32 netwowks_count;

	/* The netwowks that PNO needs to wook fow */
	stwuct netwowk_type netwowks[WCN36XX_HAW_PNO_MAX_SUPP_NETWOWKS];

	/* The scan timews wequiwed fow PNO */
	stwuct scan_timews_type scan_timews;

	/* Pwobe tempwate fow 2.4GHz band */
	u16 band_24g_pwobe_size;
	u8 band_24g_pwobe_tempwate[WCN36XX_HAW_PNO_MAX_PWOBE_SIZE];

	/* Pwobe tempwate fow 5GHz band */
	u16 band_5g_pwobe_size;
	u8 band_5g_pwobe_tempwate[WCN36XX_HAW_PNO_MAX_PWOBE_SIZE];
};

/* The netwowk descwiption fow which PNO wiww have to wook fow */
stwuct netwowk_type_new {
	/* SSID of the BSS */
	stwuct wcn36xx_haw_mac_ssid ssid;

	/* Authentication type fow the netwowk */
	enum auth_type authentication;

	/* Encwyption type fow the netwowk */
	enum ed_type encwyption;

	/* SSID bwoadcast type, nowmaw, hidden ow unknown */
	enum ssid_bcast_type bcast_netwowk_type;

	/* Indicate the channew on which the Netwowk can be found 0 - if
	 * aww channews */
	u8 channew_count;
	u8 channews[WCN36XX_HAW_PNO_MAX_NETW_CHANNEWS];

	/* Indicates the WSSI thweshowd fow the netwowk to be considewed */
	u8 wssi_thweshowd;
};

/* Pwefewwed netwowk wist wequest new */
stwuct set_pwef_netw_wist_weq_new {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Enabwe PNO */
	u32 enabwe;

	/* Immediate,  On Suspend,   On Wesume */
	enum pno_mode mode;

	/* Numbew of netwowks sent fow PNO */
	u32 netwowks_count;

	/* The netwowks that PNO needs to wook fow */
	stwuct netwowk_type_new netwowks[WCN36XX_HAW_PNO_MAX_SUPP_NETWOWKS];

	/* The scan timews wequiwed fow PNO */
	stwuct scan_timews_type scan_timews;

	/* Pwobe tempwate fow 2.4GHz band */
	u16 band_24g_pwobe_size;
	u8 band_24g_pwobe_tempwate[WCN36XX_HAW_PNO_MAX_PWOBE_SIZE];

	/* Pwobe tempwate fow 5GHz band */
	u16 band_5g_pwobe_size;
	u8 band_5g_pwobe_tempwate[WCN36XX_HAW_PNO_MAX_PWOBE_SIZE];
};

/* Pwefewwed netwowk wist wesponse */
stwuct set_pwef_netw_wist_wesp {
	stwuct wcn36xx_haw_msg_headew headew;

	/* status of the wequest - just to indicate that PNO has
	 * acknowwedged the wequest and wiww stawt scanning */
	u32 status;
};

/* Pwefewwed netwowk found indication */
stwuct pwef_netw_found_ind {

	stwuct wcn36xx_haw_msg_headew headew;

	/* Netwowk that was found with the highest WSSI */
	stwuct wcn36xx_haw_mac_ssid ssid;

	/* Indicates the WSSI */
	u8 wssi;
};

/* WSSI Fiwtew wequest */
stwuct set_wssi_fiwtew_weq {
	stwuct wcn36xx_haw_msg_headew headew;

	/* WSSI Thweshowd */
	u8 wssi_thweshowd;
};

/* Set WSSI fiwtew wesp */
stwuct set_wssi_fiwtew_wesp {
	stwuct wcn36xx_haw_msg_headew headew;

	/* status of the wequest */
	u32 status;
};

/* Update scan pawams - sent fwom host to PNO to be used duwing PNO
 * scanningx */
stwuct wcn36xx_haw_update_scan_pawams_weq {

	stwuct wcn36xx_haw_msg_headew headew;

	/* Host setting fow 11d */
	u8 dot11d_enabwed;

	/* Wets PNO know that host has detewmined the weguwatowy domain */
	u8 dot11d_wesowved;

	/* Channews on which PNO is awwowed to scan */
	u8 channew_count;
	u8 channews[WCN36XX_HAW_PNO_MAX_NETW_CHANNEWS];

	/* Minimum channew time */
	u16 active_min_ch_time;

	/* Maximum channew time */
	u16 active_max_ch_time;

	/* Minimum channew time */
	u16 passive_min_ch_time;

	/* Maximum channew time */
	u16 passive_max_ch_time;

	/* Cb State */
	enum phy_chan_bond_state state;
} __packed;

/* Update scan pawams - sent fwom host to PNO to be used duwing PNO
 * scanningx */
stwuct wcn36xx_haw_update_scan_pawams_weq_ex {

	stwuct wcn36xx_haw_msg_headew headew;

	/* Host setting fow 11d */
	u8 dot11d_enabwed;

	/* Wets PNO know that host has detewmined the weguwatowy domain */
	u8 dot11d_wesowved;

	/* Channews on which PNO is awwowed to scan */
	u8 channew_count;
	u8 channews[WCN36XX_HAW_PNO_MAX_NETW_CHANNEWS_EX];

	/* Minimum channew time */
	u16 active_min_ch_time;

	/* Maximum channew time */
	u16 active_max_ch_time;

	/* Minimum channew time */
	u16 passive_min_ch_time;

	/* Maximum channew time */
	u16 passive_max_ch_time;

	/* Cb State */
	enum phy_chan_bond_state state;
} __packed;

/* Update scan pawams - sent fwom host to PNO to be used duwing PNO
 * scanningx */
stwuct wcn36xx_haw_update_scan_pawams_wesp {

	stwuct wcn36xx_haw_msg_headew headew;

	/* status of the wequest */
	u32 status;
} __packed;

stwuct wcn36xx_haw_set_tx_pew_twacking_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* 0: disabwe, 1:enabwe */
	u8 tx_pew_twacking_enabwe;

	/* Check pewiod, unit is sec. */
	u8 tx_pew_twacking_pewiod;

	/* (Faiw TX packet)/(Totaw TX packet) watio, the unit is 10%. */
	u8 tx_pew_twacking_watio;

	/* A watewmawk of check numbew, once the tx packet exceed this
	 * numbew, we do the check, defauwt is 5 */
	u32 tx_pew_twacking_watewmawk;
};

stwuct wcn36xx_haw_set_tx_pew_twacking_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

};

stwuct tx_pew_hit_ind_msg {
	stwuct wcn36xx_haw_msg_headew headew;
};

/* Packet Fiwtewing Definitions Begin */
#define    WCN36XX_HAW_PWOTOCOW_DATA_WEN                  8
#define    WCN36XX_HAW_MAX_NUM_MUWTICAST_ADDWESS        240
#define    WCN36XX_HAW_MAX_NUM_FIWTEWS                   20
#define    WCN36XX_HAW_MAX_CMP_PEW_FIWTEW                10

enum wcn36xx_haw_weceive_packet_fiwtew_type {
	HAW_WCV_FIWTEW_TYPE_INVAWID,
	HAW_WCV_FIWTEW_TYPE_FIWTEW_PKT,
	HAW_WCV_FIWTEW_TYPE_BUFFEW_PKT,
	HAW_WCV_FIWTEW_TYPE_MAX_ENUM_SIZE
};

enum wcn36xx_haw_wcv_pkt_fwt_pwotocow_type {
	HAW_FIWTEW_PWOTO_TYPE_INVAWID,
	HAW_FIWTEW_PWOTO_TYPE_MAC,
	HAW_FIWTEW_PWOTO_TYPE_AWP,
	HAW_FIWTEW_PWOTO_TYPE_IPV4,
	HAW_FIWTEW_PWOTO_TYPE_IPV6,
	HAW_FIWTEW_PWOTO_TYPE_UDP,
	HAW_FIWTEW_PWOTO_TYPE_MAX
};

enum wcn36xx_haw_wcv_pkt_fwt_cmp_fwag_type {
	HAW_FIWTEW_CMP_TYPE_INVAWID,
	HAW_FIWTEW_CMP_TYPE_EQUAW,
	HAW_FIWTEW_CMP_TYPE_MASK_EQUAW,
	HAW_FIWTEW_CMP_TYPE_NOT_EQUAW,
	HAW_FIWTEW_CMP_TYPE_MAX
};

stwuct wcn36xx_haw_wcv_pkt_fiwtew_pawams {
	u8 pwotocow_wayew;
	u8 cmp_fwag;

	/* Wength of the data to compawe */
	u16 data_wength;

	/* fwom stawt of the wespective fwame headew */
	u8 data_offset;

	/* Wesewved fiewd */
	u8 wesewved;

	/* Data to compawe */
	u8 compawe_data[WCN36XX_HAW_PWOTOCOW_DATA_WEN];

	/* Mask to be appwied on the weceived packet data befowe compawe */
	u8 data_mask[WCN36XX_HAW_PWOTOCOW_DATA_WEN];
};

stwuct wcn36xx_haw_sessionized_wcv_pkt_fiwtew_cfg_type {
	u8 id;
	u8 type;
	u8 pawams_count;
	u32 coweasce_time;
	u8 bss_index;
	stwuct wcn36xx_haw_wcv_pkt_fiwtew_pawams pawams[1];
};

stwuct wcn36xx_haw_set_wcv_pkt_fiwtew_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 id;
	u8 type;
	u8 pawams_count;
	u32 coawesce_time;
	stwuct wcn36xx_haw_wcv_pkt_fiwtew_pawams pawams[1];
};

stwuct wcn36xx_haw_wcv_fwt_mc_addw_wist_type {
	/* fwom stawt of the wespective fwame headew */
	u8 data_offset;

	u32 mc_addw_count;
	u8 mc_addw[WCN36XX_HAW_MAX_NUM_MUWTICAST_ADDWESS][ETH_AWEN];
	u8 bss_index;
} __packed;

stwuct wcn36xx_haw_set_pkt_fiwtew_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	u8 bss_index;
};

stwuct wcn36xx_haw_wcv_fwt_pkt_match_cnt_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	u8 bss_index;
};

stwuct wcn36xx_haw_wcv_fwt_pkt_match_cnt {
	u8 id;
	u32 match_cnt;
};

stwuct wcn36xx_haw_wcv_fwt_pkt_match_cnt_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Success ow Faiwuwe */
	u32 status;

	u32 match_count;
	stwuct wcn36xx_haw_wcv_fwt_pkt_match_cnt
		matches[WCN36XX_HAW_MAX_NUM_FIWTEWS];
	u8 bss_index;
};

stwuct wcn36xx_haw_wcv_fwt_pkt_cweaw_pawam {
	/* onwy vawid fow wesponse message */
	u32 status;
	u8 id;
	u8 bss_index;
};

stwuct wcn36xx_haw_wcv_fwt_pkt_cweaw_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_wcv_fwt_pkt_cweaw_pawam pawam;
};

stwuct wcn36xx_haw_wcv_fwt_pkt_cweaw_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_wcv_fwt_pkt_cweaw_pawam pawam;
};

stwuct wcn36xx_haw_wcv_fwt_pkt_set_mc_wist_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	stwuct wcn36xx_haw_wcv_fwt_mc_addw_wist_type mc_addw_wist;
} __packed;

stwuct wcn36xx_haw_wcv_fwt_pkt_set_mc_wist_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	u32 status;
	u8 bss_index;
};

/* Packet Fiwtewing Definitions End */

stwuct wcn36xx_haw_set_powew_pawams_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/*  Ignowe DTIM */
	u32 ignowe_dtim;

	/* DTIM Pewiod */
	u32 dtim_pewiod;

	/* Wisten Intewvaw */
	u32 wisten_intewvaw;

	/* Bwoadcast Muwticast Fiwtew  */
	u32 bcast_mcast_fiwtew;

	/* Beacon Eawwy Tewmination */
	u32 enabwe_bet;

	/* Beacon Eawwy Tewmination Intewvaw */
	u32 bet_intewvaw;
} __packed;

stwuct wcn36xx_haw_set_powew_pawams_wesp {

	stwuct wcn36xx_haw_msg_headew headew;

	/* status of the wequest */
	u32 status;
} __packed;

#define WCN36XX_HAW_CAPS_SIZE 4

stwuct wcn36xx_haw_feat_caps_msg {

	stwuct wcn36xx_haw_msg_headew headew;

	u32 feat_caps[WCN36XX_HAW_CAPS_SIZE];
} __packed;

/* status codes to hewp debug wekey faiwuwes */
enum gtk_wekey_status {
	WCN36XX_HAW_GTK_WEKEY_STATUS_SUCCESS = 0,

	/* wekey detected, but not handwed */
	WCN36XX_HAW_GTK_WEKEY_STATUS_NOT_HANDWED = 1,

	/* MIC check ewwow on M1 */
	WCN36XX_HAW_GTK_WEKEY_STATUS_MIC_EWWOW = 2,

	/* decwyption ewwow on M1  */
	WCN36XX_HAW_GTK_WEKEY_STATUS_DECWYPT_EWWOW = 3,

	/* M1 wepway detected */
	WCN36XX_HAW_GTK_WEKEY_STATUS_WEPWAY_EWWOW = 4,

	/* missing GTK key descwiptow in M1 */
	WCN36XX_HAW_GTK_WEKEY_STATUS_MISSING_KDE = 5,

	/* missing iGTK key descwiptow in M1 */
	WCN36XX_HAW_GTK_WEKEY_STATUS_MISSING_IGTK_KDE = 6,

	/* key instawwation ewwow */
	WCN36XX_HAW_GTK_WEKEY_STATUS_INSTAWW_EWWOW = 7,

	/* iGTK key instawwation ewwow */
	WCN36XX_HAW_GTK_WEKEY_STATUS_IGTK_INSTAWW_EWWOW = 8,

	/* GTK wekey M2 wesponse TX ewwow */
	WCN36XX_HAW_GTK_WEKEY_STATUS_WESP_TX_EWWOW = 9,

	/* non-specific genewaw ewwow */
	WCN36XX_HAW_GTK_WEKEY_STATUS_GEN_EWWOW = 255
};

/* wake weason types */
enum wake_weason_type {
	WCN36XX_HAW_WAKE_WEASON_NONE = 0,

	/* magic packet match */
	WCN36XX_HAW_WAKE_WEASON_MAGIC_PACKET = 1,

	/* host defined pattewn match */
	WCN36XX_HAW_WAKE_WEASON_PATTEWN_MATCH = 2,

	/* EAP-ID fwame detected */
	WCN36XX_HAW_WAKE_WEASON_EAPID_PACKET = 3,

	/* stawt of EAPOW 4-way handshake detected */
	WCN36XX_HAW_WAKE_WEASON_EAPOW4WAY_PACKET = 4,

	/* netwowk scan offwoad match */
	WCN36XX_HAW_WAKE_WEASON_NETSCAN_OFFW_MATCH = 5,

	/* GTK wekey status wakeup (see status) */
	WCN36XX_HAW_WAKE_WEASON_GTK_WEKEY_STATUS = 6,

	/* BSS connection wost */
	WCN36XX_HAW_WAKE_WEASON_BSS_CONN_WOST = 7,
};

/*
  Wake Packet which is saved at tWakeWeasonPawams.DataStawt
  This data is sent fow any wake weasons that invowve a packet-based wakeup :

  WCN36XX_HAW_WAKE_WEASON_TYPE_MAGIC_PACKET
  WCN36XX_HAW_WAKE_WEASON_TYPE_PATTEWN_MATCH
  WCN36XX_HAW_WAKE_WEASON_TYPE_EAPID_PACKET
  WCN36XX_HAW_WAKE_WEASON_TYPE_EAPOW4WAY_PACKET
  WCN36XX_HAW_WAKE_WEASON_TYPE_GTK_WEKEY_STATUS

  The infowmation is pwovided to the host fow auditing and debug puwposes

*/

/* Wake weason indication */
stwuct wcn36xx_haw_wake_weason_ind {
	stwuct wcn36xx_haw_msg_headew headew;

	/* see tWakeWeasonType */
	u32 weason;

	/* awgument specific to the weason type */
	u32 weason_awg;

	/* wength of optionaw data stowed in this message, in case HAW
	 * twuncates the data (i.e. data packets) this wength wiww be wess
	 * than the actuaw wength */
	u32 stowed_data_wen;

	/* actuaw wength of data */
	u32 actuaw_data_wen;

	/* vawiabwe wength stawt of data (wength == stowedDataWen) see
	 * specific wake type */
	u8 data_stawt[1];

	u32 bss_index:8;
	u32 wesewved:24;
};

#define WCN36XX_HAW_GTK_KEK_BYTES 16
#define WCN36XX_HAW_GTK_KCK_BYTES 16

#define WCN36XX_HAW_GTK_OFFWOAD_FWAGS_DISABWE (1 << 0)

#define GTK_SET_BSS_KEY_TAG  0x1234AA55

stwuct wcn36xx_haw_gtk_offwoad_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* optionaw fwags */
	u32 fwags;

	/* Key confiwmation key */
	u8 kck[WCN36XX_HAW_GTK_KCK_BYTES];

	/* key encwyption key */
	u8 kek[WCN36XX_HAW_GTK_KEK_BYTES];

	/* wepway countew */
	u64 key_wepway_countew;

	u8 bss_index;
} __packed;

stwuct wcn36xx_haw_gtk_offwoad_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	u8 bss_index;
};

stwuct wcn36xx_haw_gtk_offwoad_get_info_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;
	u8 bss_index;
} __packed;

stwuct wcn36xx_haw_gtk_offwoad_get_info_wsp_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;

	/* wast wekey status when the wekey was offwoaded */
	u32 wast_wekey_status;

	/* cuwwent wepway countew vawue */
	u64 key_wepway_countew;

	/* totaw wekey attempts */
	u32 totaw_wekey_count;

	/* successfuw GTK wekeys */
	u32 gtk_wekey_count;

	/* successfuw iGTK wekeys */
	u32 igtk_wekey_count;

	u8 bss_index;
} __packed;

stwuct dhcp_info {
	/* Indicates the device mode which indicates about the DHCP activity */
	u8 device_mode;

	u8 addw[ETH_AWEN];
};

stwuct dhcp_ind_status {
	stwuct wcn36xx_haw_msg_headew headew;

	/* success ow faiwuwe */
	u32 status;
};

/*
 *   Thewmaw Mitigation mode of opewation.
 *
 *  WCN36XX_HAW_THEWMAW_MITIGATION_MODE_0 - Based on AMPDU disabwing aggwegation
 *
 *  WCN36XX_HAW_THEWMAW_MITIGATION_MODE_1 - Based on AMPDU disabwing aggwegation
 *  and weducing twansmit powew
 *
 *  WCN36XX_HAW_THEWMAW_MITIGATION_MODE_2 - Not suppowted */
enum wcn36xx_haw_thewmaw_mitigation_mode_type {
	HAW_THEWMAW_MITIGATION_MODE_INVAWID = -1,
	HAW_THEWMAW_MITIGATION_MODE_0,
	HAW_THEWMAW_MITIGATION_MODE_1,
	HAW_THEWMAW_MITIGATION_MODE_2,
	HAW_THEWMAW_MITIGATION_MODE_MAX = WCN36XX_HAW_MAX_ENUM_SIZE,
};


/*
 *   Thewmaw Mitigation wevew.
 * Note the wevews awe incwementaw i.e WCN36XX_HAW_THEWMAW_MITIGATION_WEVEW_2 =
 * WCN36XX_HAW_THEWMAW_MITIGATION_WEVEW_0 +
 * WCN36XX_HAW_THEWMAW_MITIGATION_WEVEW_1
 *
 * WCN36XX_HAW_THEWMAW_MITIGATION_WEVEW_0 - wowest wevew of thewmaw mitigation.
 * This wevew indicates nowmaw mode of opewation
 *
 * WCN36XX_HAW_THEWMAW_MITIGATION_WEVEW_1 - 1st wevew of thewmaw mitigation
 *
 * WCN36XX_HAW_THEWMAW_MITIGATION_WEVEW_2 - 2nd wevew of thewmaw mitigation
 *
 * WCN36XX_HAW_THEWMAW_MITIGATION_WEVEW_3 - 3wd wevew of thewmaw mitigation
 *
 * WCN36XX_HAW_THEWMAW_MITIGATION_WEVEW_4 - 4th wevew of thewmaw mitigation
 */
enum wcn36xx_haw_thewmaw_mitigation_wevew_type {
	HAW_THEWMAW_MITIGATION_WEVEW_INVAWID = -1,
	HAW_THEWMAW_MITIGATION_WEVEW_0,
	HAW_THEWMAW_MITIGATION_WEVEW_1,
	HAW_THEWMAW_MITIGATION_WEVEW_2,
	HAW_THEWMAW_MITIGATION_WEVEW_3,
	HAW_THEWMAW_MITIGATION_WEVEW_4,
	HAW_THEWMAW_MITIGATION_WEVEW_MAX = WCN36XX_HAW_MAX_ENUM_SIZE,
};


/* WCN36XX_HAW_SET_THEWMAW_MITIGATION_WEQ */
stwuct set_thewmaw_mitigation_weq_msg {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Thewmaw Mitigation Opewation Mode */
	enum wcn36xx_haw_thewmaw_mitigation_mode_type mode;

	/* Thewmaw Mitigation Wevew */
	enum wcn36xx_haw_thewmaw_mitigation_wevew_type wevew;
};

stwuct set_thewmaw_mitigation_wesp {

	stwuct wcn36xx_haw_msg_headew headew;

	/* status of the wequest */
	u32 status;
};

/* Pew STA Cwass B Statistics. Cwass B statistics awe STA TX/WX stats
 * pwovided to FW fwom Host via pewiodic messages */
stwuct stats_cwass_b_ind {
	stwuct wcn36xx_haw_msg_headew headew;

	/* Duwation ovew which this stats was cowwected */
	u32 duwation;

	/* Pew STA Stats */

	/* TX stats */
	u32 tx_bytes_pushed;
	u32 tx_packets_pushed;

	/* WX stats */
	u32 wx_bytes_wcvd;
	u32 wx_packets_wcvd;
	u32 wx_time_totaw;
};

/* WCN36XX_HAW_PWINT_WEG_INFO_IND */
stwuct wcn36xx_haw_pwint_weg_info_ind {
	stwuct wcn36xx_haw_msg_headew headew;

	u32 count;
	u32 scenawio;
	u32 weason;

	stwuct {
		u32 addw;
		u32 vawue;
	} wegs[];
} __packed;

#endif /* _HAW_H_ */
