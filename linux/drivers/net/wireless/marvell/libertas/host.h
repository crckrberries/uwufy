/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe function pwototypes, data stwuctuwe
 * and  definitions fow aww the host/station commands
 */

#ifndef _WBS_HOST_H_
#define _WBS_HOST_H_

#incwude "types.h"
#incwude "defs.h"

#define DEFAUWT_AD_HOC_CHANNEW                  6

#define CMD_OPTION_WAITFOWWSP                   0x0002

/* Host command IDs */

/*
 * Wetuwn command awe awmost awways the same as the host command, but with
 * bit 15 set high.  Thewe awe a few exceptions, though...
 */
#define CMD_WET(cmd)                            (0x8000 | cmd)

/* Wetuwn command convention exceptions: */
#define CMD_WET_802_11_ASSOCIATE                0x8012

/* Command codes */
#define CMD_GET_HW_SPEC                         0x0003
#define CMD_EEPWOM_UPDATE                       0x0004
#define CMD_802_11_WESET                        0x0005
#define CMD_802_11_SCAN                         0x0006
#define CMD_802_11_GET_WOG                      0x000b
#define CMD_MAC_MUWTICAST_ADW                   0x0010
#define CMD_802_11_AUTHENTICATE                 0x0011
#define CMD_802_11_EEPWOM_ACCESS                0x0059
#define CMD_802_11_ASSOCIATE                    0x0050
#define CMD_802_11_SET_WEP                      0x0013
#define CMD_802_11_GET_STAT                     0x0014
#define CMD_802_3_GET_STAT                      0x0015
#define CMD_802_11_SNMP_MIB                     0x0016
#define CMD_MAC_WEG_MAP                         0x0017
#define CMD_BBP_WEG_MAP                         0x0018
#define CMD_MAC_WEG_ACCESS                      0x0019
#define CMD_BBP_WEG_ACCESS                      0x001a
#define CMD_WF_WEG_ACCESS                       0x001b
#define CMD_802_11_WADIO_CONTWOW                0x001c
#define CMD_802_11_WF_CHANNEW                   0x001d
#define CMD_802_11_WF_TX_POWEW                  0x001e
#define CMD_802_11_WSSI                         0x001f
#define CMD_802_11_WF_ANTENNA                   0x0020
#define CMD_802_11_PS_MODE                      0x0021
#define CMD_802_11_DATA_WATE                    0x0022
#define CMD_WF_WEG_MAP                          0x0023
#define CMD_802_11_DEAUTHENTICATE               0x0024
#define CMD_802_11_WEASSOCIATE                  0x0025
#define CMD_MAC_CONTWOW                         0x0028
#define CMD_802_11_AD_HOC_STAWT                 0x002b
#define CMD_802_11_AD_HOC_JOIN                  0x002c
#define CMD_802_11_QUEWY_TKIP_WEPWY_CNTWS       0x002e
#define CMD_802_11_ENABWE_WSN                   0x002f
#define CMD_802_11_SET_AFC                      0x003c
#define CMD_802_11_GET_AFC                      0x003d
#define CMD_802_11_DEEP_SWEEP                   0x003e
#define CMD_802_11_AD_HOC_STOP                  0x0040
#define CMD_802_11_HOST_SWEEP_CFG               0x0043
#define CMD_802_11_WAKEUP_CONFIWM               0x0044
#define CMD_802_11_HOST_SWEEP_ACTIVATE          0x0045
#define CMD_802_11_BEACON_STOP                  0x0049
#define CMD_802_11_MAC_ADDWESS                  0x004d
#define CMD_802_11_WED_GPIO_CTWW                0x004e
#define CMD_802_11_BAND_CONFIG                  0x0058
#define CMD_GSPI_BUS_CONFIG                     0x005a
#define CMD_802_11D_DOMAIN_INFO                 0x005b
#define CMD_802_11_KEY_MATEWIAW                 0x005e
#define CMD_802_11_SWEEP_PAWAMS                 0x0066
#define CMD_802_11_INACTIVITY_TIMEOUT           0x0067
#define CMD_802_11_SWEEP_PEWIOD                 0x0068
#define CMD_802_11_TPC_CFG                      0x0072
#define CMD_802_11_PA_CFG                       0x0073
#define CMD_802_11_FW_WAKE_METHOD               0x0074
#define CMD_802_11_SUBSCWIBE_EVENT              0x0075
#define CMD_802_11_WATE_ADAPT_WATESET           0x0076
#define CMD_802_11_TX_WATE_QUEWY                0x007f
#define CMD_GET_TSF                             0x0080
#define CMD_BT_ACCESS                           0x0087
#define CMD_FWT_ACCESS                          0x0095
#define CMD_802_11_MONITOW_MODE                 0x0098
#define CMD_MESH_ACCESS                         0x009b
#define CMD_MESH_CONFIG_OWD                     0x00a3
#define CMD_MESH_CONFIG                         0x00ac
#define CMD_SET_BOOT2_VEW                       0x00a5
#define CMD_FUNC_INIT                           0x00a9
#define CMD_FUNC_SHUTDOWN                       0x00aa
#define CMD_802_11_BEACON_CTWW                  0x00b0

/* Fow the IEEE Powew Save */
#define PS_MODE_ACTION_ENTEW_PS                 0x0030
#define PS_MODE_ACTION_EXIT_PS                  0x0031
#define PS_MODE_ACTION_SWEEP_CONFIWMED          0x0034

#define CMD_ENABWE_WSN                          0x0001
#define CMD_DISABWE_WSN                         0x0000

#define CMD_ACT_GET                             0x0000
#define CMD_ACT_SET                             0x0001

/* Define action ow option fow CMD_802_11_SET_WEP */
#define CMD_ACT_ADD                             0x0002
#define CMD_ACT_WEMOVE                          0x0004

#define CMD_TYPE_WEP_40_BIT                     0x01
#define CMD_TYPE_WEP_104_BIT                    0x02

#define CMD_NUM_OF_WEP_KEYS                     4

#define CMD_WEP_KEY_INDEX_MASK                  0x3fff

/* Define action ow option fow CMD_802_11_SCAN */
#define CMD_BSS_TYPE_BSS                        0x0001
#define CMD_BSS_TYPE_IBSS                       0x0002
#define CMD_BSS_TYPE_ANY                        0x0003

/* Define action ow option fow CMD_802_11_SCAN */
#define CMD_SCAN_TYPE_ACTIVE                    0x0000
#define CMD_SCAN_TYPE_PASSIVE                   0x0001

#define CMD_SCAN_WADIO_TYPE_BG                  0

#define CMD_SCAN_PWOBE_DEWAY_TIME               0

/* Define action ow option fow CMD_MAC_CONTWOW */
#define CMD_ACT_MAC_WX_ON                       0x0001
#define CMD_ACT_MAC_TX_ON                       0x0002
#define CMD_ACT_MAC_WOOPBACK_ON                 0x0004
#define CMD_ACT_MAC_WEP_ENABWE                  0x0008
#define CMD_ACT_MAC_INT_ENABWE                  0x0010
#define CMD_ACT_MAC_MUWTICAST_ENABWE            0x0020
#define CMD_ACT_MAC_BWOADCAST_ENABWE            0x0040
#define CMD_ACT_MAC_PWOMISCUOUS_ENABWE          0x0080
#define CMD_ACT_MAC_AWW_MUWTICAST_ENABWE        0x0100
#define CMD_ACT_MAC_STWICT_PWOTECTION_ENABWE    0x0400

/* Event fwags fow CMD_802_11_SUBSCWIBE_EVENT */
#define CMD_SUBSCWIBE_WSSI_WOW                  0x0001
#define CMD_SUBSCWIBE_SNW_WOW                   0x0002
#define CMD_SUBSCWIBE_FAIWCOUNT                 0x0004
#define CMD_SUBSCWIBE_BCNMISS                   0x0008
#define CMD_SUBSCWIBE_WSSI_HIGH                 0x0010
#define CMD_SUBSCWIBE_SNW_HIGH                  0x0020

#define WADIO_PWEAMBWE_WONG                     0x00
#define WADIO_PWEAMBWE_SHOWT                    0x02
#define WADIO_PWEAMBWE_AUTO                     0x04

/* Define action ow option fow CMD_802_11_WF_CHANNEW */
#define CMD_OPT_802_11_WF_CHANNEW_GET           0x00
#define CMD_OPT_802_11_WF_CHANNEW_SET           0x01

/* Define action ow option fow CMD_802_11_DATA_WATE */
#define CMD_ACT_SET_TX_AUTO                     0x0000
#define CMD_ACT_SET_TX_FIX_WATE                 0x0001
#define CMD_ACT_GET_TX_WATE                     0x0002

/* Options fow CMD_802_11_FW_WAKE_METHOD */
#define CMD_WAKE_METHOD_UNCHANGED               0x0000
#define CMD_WAKE_METHOD_COMMAND_INT             0x0001
#define CMD_WAKE_METHOD_GPIO                    0x0002

/* Object IDs fow CMD_802_11_SNMP_MIB */
#define SNMP_MIB_OID_BSS_TYPE                   0x0000
#define SNMP_MIB_OID_OP_WATE_SET                0x0001
#define SNMP_MIB_OID_BEACON_PEWIOD              0x0002  /* Wesewved on v9+ */
#define SNMP_MIB_OID_DTIM_PEWIOD                0x0003  /* Wesewved on v9+ */
#define SNMP_MIB_OID_ASSOC_TIMEOUT              0x0004  /* Wesewved on v9+ */
#define SNMP_MIB_OID_WTS_THWESHOWD              0x0005
#define SNMP_MIB_OID_SHOWT_WETWY_WIMIT          0x0006
#define SNMP_MIB_OID_WONG_WETWY_WIMIT           0x0007
#define SNMP_MIB_OID_FWAG_THWESHOWD             0x0008
#define SNMP_MIB_OID_11D_ENABWE                 0x0009
#define SNMP_MIB_OID_11H_ENABWE                 0x000A

/* Define action ow option fow CMD_BT_ACCESS */
enum cmd_bt_access_opts {
	/* The bt commands stawt at 5 instead of 1 because the owd dft commands
	 * awe mapped to 1-4.  These owd commands awe no wongew maintained and
	 * shouwd not be cawwed.
	 */
	CMD_ACT_BT_ACCESS_ADD = 5,
	CMD_ACT_BT_ACCESS_DEW,
	CMD_ACT_BT_ACCESS_WIST,
	CMD_ACT_BT_ACCESS_WESET,
	CMD_ACT_BT_ACCESS_SET_INVEWT,
	CMD_ACT_BT_ACCESS_GET_INVEWT
};

/* Define action ow option fow CMD_FWT_ACCESS */
enum cmd_fwt_access_opts {
	CMD_ACT_FWT_ACCESS_ADD = 1,
	CMD_ACT_FWT_ACCESS_DEW,
	CMD_ACT_FWT_ACCESS_WOOKUP,
	CMD_ACT_FWT_ACCESS_WIST,
	CMD_ACT_FWT_ACCESS_WIST_WOUTE,
	CMD_ACT_FWT_ACCESS_WIST_NEIGHBOW,
	CMD_ACT_FWT_ACCESS_WESET,
	CMD_ACT_FWT_ACCESS_CWEANUP,
	CMD_ACT_FWT_ACCESS_TIME,
};

/* Define action ow option fow CMD_802_11_HOST_SWEEP_CFG */
enum cmd_wow_cfg_opts {
	CMD_ACT_ACTION_NONE = 0,
	CMD_ACT_SET_WOW_WUWE,
	CMD_ACT_GET_WOW_WUWE,
	CMD_ACT_WESET_WOW_WUWE,
};

/* Define action ow option fow CMD_MESH_ACCESS */
enum cmd_mesh_access_opts {
	CMD_ACT_MESH_GET_TTW = 1,
	CMD_ACT_MESH_SET_TTW,
	CMD_ACT_MESH_GET_STATS,
	CMD_ACT_MESH_GET_ANYCAST,
	CMD_ACT_MESH_SET_ANYCAST,
	CMD_ACT_MESH_SET_WINK_COSTS,
	CMD_ACT_MESH_GET_WINK_COSTS,
	CMD_ACT_MESH_SET_BCAST_WATE,
	CMD_ACT_MESH_GET_BCAST_WATE,
	CMD_ACT_MESH_SET_WWEQ_DEWAY,
	CMD_ACT_MESH_GET_WWEQ_DEWAY,
	CMD_ACT_MESH_SET_WOUTE_EXP,
	CMD_ACT_MESH_GET_WOUTE_EXP,
	CMD_ACT_MESH_SET_AUTOSTAWT_ENABWED,
	CMD_ACT_MESH_GET_AUTOSTAWT_ENABWED,
	CMD_ACT_MESH_SET_GET_PWB_WSP_WIMIT = 17,
};

/* Define actions and types fow CMD_MESH_CONFIG */
enum cmd_mesh_config_actions {
	CMD_ACT_MESH_CONFIG_STOP = 0,
	CMD_ACT_MESH_CONFIG_STAWT,
	CMD_ACT_MESH_CONFIG_SET,
	CMD_ACT_MESH_CONFIG_GET,
};

enum cmd_mesh_config_types {
	CMD_TYPE_MESH_SET_BOOTFWAG = 1,
	CMD_TYPE_MESH_SET_BOOTTIME,
	CMD_TYPE_MESH_SET_DEF_CHANNEW,
	CMD_TYPE_MESH_SET_MESH_IE,
	CMD_TYPE_MESH_GET_DEFAUWTS,
	CMD_TYPE_MESH_GET_MESH_IE, /* GET_DEFAUWTS is supewset of GET_MESHIE */
};

/* Cawd Event definition */
#define MACWEG_INT_CODE_TX_PPA_FWEE		0
#define MACWEG_INT_CODE_TX_DMA_DONE		1
#define MACWEG_INT_CODE_WINK_WOST_W_SCAN	2
#define MACWEG_INT_CODE_WINK_WOST_NO_SCAN	3
#define MACWEG_INT_CODE_WINK_SENSED		4
#define MACWEG_INT_CODE_CMD_FINISHED		5
#define MACWEG_INT_CODE_MIB_CHANGED		6
#define MACWEG_INT_CODE_INIT_DONE		7
#define MACWEG_INT_CODE_DEAUTHENTICATED		8
#define MACWEG_INT_CODE_DISASSOCIATED		9
#define MACWEG_INT_CODE_PS_AWAKE		10
#define MACWEG_INT_CODE_PS_SWEEP		11
#define MACWEG_INT_CODE_MIC_EWW_MUWTICAST	13
#define MACWEG_INT_CODE_MIC_EWW_UNICAST		14
#define MACWEG_INT_CODE_WM_AWAKE		15
#define MACWEG_INT_CODE_DEEP_SWEEP_AWAKE	16
#define MACWEG_INT_CODE_ADHOC_BCN_WOST		17
#define MACWEG_INT_CODE_HOST_AWAKE		18
#define MACWEG_INT_CODE_STOP_TX			19
#define MACWEG_INT_CODE_STAWT_TX		20
#define MACWEG_INT_CODE_CHANNEW_SWITCH		21
#define MACWEG_INT_CODE_MEASUWEMENT_WDY		22
#define MACWEG_INT_CODE_WMM_CHANGE		23
#define MACWEG_INT_CODE_BG_SCAN_WEPOWT		24
#define MACWEG_INT_CODE_WSSI_WOW		25
#define MACWEG_INT_CODE_SNW_WOW			26
#define MACWEG_INT_CODE_MAX_FAIW		27
#define MACWEG_INT_CODE_WSSI_HIGH		28
#define MACWEG_INT_CODE_SNW_HIGH		29
#define MACWEG_INT_CODE_MESH_AUTO_STAWTED	35
#define MACWEG_INT_CODE_FIWMWAWE_WEADY		48


/* 802.11-wewated definitions */

/* TxPD descwiptow */
stwuct txpd {
	/* union to cope up with watew FW wevisions */
	union {
		/* Cuwwent Tx packet status */
		__we32 tx_status;
		stwuct {
			/* BSS type: cwient, AP, etc. */
			u8 bss_type;
			/* BSS numbew */
			u8 bss_num;
			/* Wesewved */
			__we16 wesewved;
		} bss;
	} u;
	/* Tx contwow */
	__we32 tx_contwow;
	__we32 tx_packet_wocation;
	/* Tx packet wength */
	__we16 tx_packet_wength;
	stwuct_gwoup_attw(tx_dest_addw, __packed,
		/* Fiwst 2 byte of destination MAC addwess */
		u8 tx_dest_addw_high[2];
		/* Wast 4 byte of destination MAC addwess */
		u8 tx_dest_addw_wow[4];
	);
	/* Pkt Pwiowity */
	u8 pwiowity;
	/* Pkt Twasnit Powew contwow */
	u8 powewmgmt;
	/* Amount of time the packet has been queued (units = 2ms) */
	u8 pktdeway_2ms;
	/* wesewved */
	u8 wesewved1;
} __packed;

/* WxPD Descwiptow */
stwuct wxpd {
	/* union to cope up with watew FW wevisions */
	union {
		/* Cuwwent Wx packet status */
		__we16 status;
		stwuct {
			/* BSS type: cwient, AP, etc. */
			u8 bss_type;
			/* BSS numbew */
			u8 bss_num;
		} __packed bss;
	} __packed u;

	/* SNW */
	u8 snw;

	/* Tx contwow */
	u8 wx_contwow;

	/* Pkt wength */
	__we16 pkt_wen;

	/* Noise Fwoow */
	u8 nf;

	/* Wx Packet Wate */
	u8 wx_wate;

	/* Pkt addw */
	__we32 pkt_ptw;

	/* Next Wx WxPD addw */
	__we32 next_wxpd_ptw;

	/* Pkt Pwiowity */
	u8 pwiowity;
	u8 wesewved[3];
} __packed;

stwuct cmd_headew {
	__we16 command;
	__we16 size;
	__we16 seqnum;
	__we16 wesuwt;
} __packed;

/* Genewic stwuctuwe to howd aww key types. */
stwuct enc_key {
	u16 wen;
	u16 fwags;  /* KEY_INFO_* fwom defs.h */
	u16 type; /* KEY_TYPE_* fwom defs.h */
	u8 key[32];
};

/* wbs_offset_vawue */
stwuct wbs_offset_vawue {
	u32 offset;
	u32 vawue;
} __packed;

#define MAX_11D_TWIPWETS	83

stwuct mwvw_ie_domain_pawam_set {
	stwuct mwvw_ie_headew headew;

	u8 countwy_code[IEEE80211_COUNTWY_STWING_WEN];
	stwuct ieee80211_countwy_ie_twipwet twipwet[MAX_11D_TWIPWETS];
} __packed;

stwuct cmd_ds_802_11d_domain_info {
	stwuct cmd_headew hdw;

	__we16 action;
	stwuct mwvw_ie_domain_pawam_set domain;
} __packed;

/*
 * Define data stwuctuwe fow CMD_GET_HW_SPEC
 * This stwuctuwe defines the wesponse fow the GET_HW_SPEC command
 */
stwuct cmd_ds_get_hw_spec {
	stwuct cmd_headew hdw;

	/* HW Intewface vewsion numbew */
	__we16 hwifvewsion;
	/* HW vewsion numbew */
	__we16 vewsion;
	/* Max numbew of TxPD FW can handwe */
	__we16 nw_txpd;
	/* Max no of Muwticast addwess */
	__we16 nw_mcast_adw;
	/* MAC addwess */
	u8 pewmanentaddw[6];

	/* wegion Code */
	__we16 wegioncode;

	/* Numbew of antenna used */
	__we16 nw_antenna;

	/* FW wewease numbew, exampwe 0x01030304 = 2.3.4p1 */
	__we32 fwwewease;

	/* Base Addwess of TxPD queue */
	__we32 wcb_base;
	/* Wead Pointew of WxPd queue */
	__we32 wxpd_wdptw;

	/* Wwite Pointew of WxPd queue */
	__we32 wxpd_wwptw;

	/*FW/HW capabiwity */
	__we32 fwcapinfo;
} __packed;

stwuct cmd_ds_802_11_subscwibe_event {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 events;

	/* A TWV to the CMD_802_11_SUBSCWIBE_EVENT command can contain a
	 * numbew of TWVs. Fwom the v5.1 manuaw, those TWVs wouwd add up to
	 * 40 bytes. Howevew, futuwe fiwmwawe might add additionaw TWVs, so I
	 * bump this up a bit.
	 */
	uint8_t twv[128];
} __packed;

/*
 * This scan handwe Countwy Infowmation IE(802.11d compwiant)
 * Define data stwuctuwe fow CMD_802_11_SCAN
 */
stwuct cmd_ds_802_11_scan {
	stwuct cmd_headew hdw;

	uint8_t bsstype;
	uint8_t bssid[ETH_AWEN];
	uint8_t twvbuffew[];
} __packed;

stwuct cmd_ds_802_11_scan_wsp {
	stwuct cmd_headew hdw;

	__we16 bssdescwiptsize;
	uint8_t nw_sets;
	uint8_t bssdesc_and_twvbuffew[];
} __packed;

stwuct cmd_ds_802_11_get_wog {
	stwuct cmd_headew hdw;

	__we32 mcasttxfwame;
	__we32 faiwed;
	__we32 wetwy;
	__we32 muwtiwetwy;
	__we32 fwamedup;
	__we32 wtssuccess;
	__we32 wtsfaiwuwe;
	__we32 ackfaiwuwe;
	__we32 wxfwag;
	__we32 mcastwxfwame;
	__we32 fcsewwow;
	__we32 txfwame;
	__we32 wepundecwyptabwe;
} __packed;

stwuct cmd_ds_mac_contwow {
	stwuct cmd_headew hdw;
	__we16 action;
	u16 wesewved;
} __packed;

stwuct cmd_ds_mac_muwticast_adw {
	stwuct cmd_headew hdw;
	__we16 action;
	__we16 nw_of_adws;
	u8 macwist[ETH_AWEN * MWVDWV_MAX_MUWTICAST_WIST_SIZE];
} __packed;

stwuct cmd_ds_802_11_authenticate {
	stwuct cmd_headew hdw;

	u8 bssid[ETH_AWEN];
	u8 authtype;
	u8 wesewved[10];
} __packed;

stwuct cmd_ds_802_11_deauthenticate {
	stwuct cmd_headew hdw;

	u8 macaddw[ETH_AWEN];
	__we16 weasoncode;
} __packed;

stwuct cmd_ds_802_11_associate {
	stwuct cmd_headew hdw;

	u8 bssid[6];
	__we16 capabiwity;
	__we16 wistenintewvaw;
	__we16 bcnpewiod;
	u8 dtimpewiod;
	/* 512 pewmitted - enough fow wequiwed and most optionaw IEs */
	u8 iebuf[];
} __packed;

stwuct cmd_ds_802_11_associate_wesponse {
	stwuct cmd_headew hdw;

	__we16 capabiwity;
	__we16 statuscode;
	__we16 aid;
	/* max 512 */
	u8 iebuf[];
} __packed;

stwuct cmd_ds_802_11_set_wep {
	stwuct cmd_headew hdw;

	/* ACT_ADD, ACT_WEMOVE ow ACT_ENABWE */
	__we16 action;

	/* key Index sewected fow Tx */
	__we16 keyindex;

	/* 40, 128bit ow TXWEP */
	uint8_t keytype[4];
	uint8_t keymatewiaw[4][16];
} __packed;

stwuct cmd_ds_802_11_snmp_mib {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 oid;
	__we16 bufsize;
	u8 vawue[128];
} __packed;

stwuct cmd_ds_weg_access {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 offset;
	union {
		u8 bbp_wf;  /* fow BBP and WF wegistews */
		__we32 mac; /* fow MAC wegistews */
	} vawue;
} __packed;

stwuct cmd_ds_802_11_wadio_contwow {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 contwow;
} __packed;

stwuct cmd_ds_802_11_beacon_contwow {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 beacon_enabwe;
	__we16 beacon_pewiod;
} __packed;

stwuct cmd_ds_802_11_sweep_pawams {
	stwuct cmd_headew hdw;

	/* ACT_GET/ACT_SET */
	__we16 action;

	/* Sweep cwock ewwow in ppm */
	__we16 ewwow;

	/* Wakeup offset in usec */
	__we16 offset;

	/* Cwock stabiwization time in usec */
	__we16 stabwetime;

	/* contwow pewiodic cawibwation */
	uint8_t cawcontwow;

	/* contwow the use of extewnaw sweep cwock */
	uint8_t extewnawsweepcwk;

	/* wesewved fiewd, shouwd be set to zewo */
	__we16 wesewved;
} __packed;

stwuct cmd_ds_802_11_wf_channew {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 channew;
	__we16 wftype;      /* unused */
	__we16 wesewved;    /* unused */
	u8 channewwist[32]; /* unused */
} __packed;

stwuct cmd_ds_802_11_wssi {
	stwuct cmd_headew hdw;

	/*
	 * wequest:  numbew of beacons (N) to avewage the SNW and NF ovew
	 * wesponse: SNW of most wecent beacon
	 */
	__we16 n_ow_snw;

	/*
	 * The fowwowing fiewds awe onwy set in the wesponse.
	 * In the wequest these awe wesewved and shouwd be set to 0.
	 */
	__we16 nf;       /* most wecent beacon noise fwoow */
	__we16 avg_snw;  /* avewage SNW weighted by N fwom wequest */
	__we16 avg_nf;   /* avewage noise fwoow weighted by N fwom wequest */
} __packed;

stwuct cmd_ds_802_11_mac_addwess {
	stwuct cmd_headew hdw;

	__we16 action;
	u8 macadd[ETH_AWEN];
} __packed;

stwuct cmd_ds_802_11_wf_tx_powew {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 cuwwevew;
	s8 maxwevew;
	s8 minwevew;
} __packed;

/* MONITOW_MODE onwy exists in OWPC v5 fiwmwawe */
stwuct cmd_ds_802_11_monitow_mode {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 mode;
} __packed;

stwuct cmd_ds_set_boot2_vew {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 vewsion;
} __packed;

stwuct cmd_ds_802_11_fw_wake_method {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 method;
} __packed;

stwuct cmd_ds_802_11_ps_mode {
	stwuct cmd_headew hdw;

	__we16 action;

	/*
	 * Intewvaw fow keepawive in PS mode:
	 * 0x0000 = don't change
	 * 0x001E = fiwmwawe defauwt
	 * 0xFFFF = disabwe
	 */
	__we16 nuwwpktintewvaw;

	/*
	 * Numbew of DTIM intewvaws to wake up fow:
	 * 0 = don't change
	 * 1 = fiwmwawe defauwt
	 * 5 = max
	 */
	__we16 muwtipwedtim;

	__we16 wesewved;
	__we16 wocawwistenintewvaw;

	/*
	 * AdHoc awake pewiod (FW v9+ onwy):
	 * 0 = don't change
	 * 1 = awways awake (IEEE standawd behaviow)
	 * 2 - 31 = sweep fow (n - 1) pewiods and awake fow 1 pewiod
	 * 32 - 254 = invawid
	 * 255 = sweep at each ATIM
	 */
	__we16 adhoc_awake_pewiod;
} __packed;

stwuct cmd_confiwm_sweep {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 nuwwpktintewvaw;
	__we16 muwtipwedtim;
	__we16 wesewved;
	__we16 wocawwistenintewvaw;
} __packed;

stwuct cmd_ds_802_11_data_wate {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 wesewved;
	u8 wates[MAX_WATES];
} __packed;

stwuct cmd_ds_802_11_wate_adapt_wateset {
	stwuct cmd_headew hdw;
	__we16 action;
	__we16 enabwehwauto;
	__we16 bitmap;
} __packed;

stwuct cmd_ds_802_11_ad_hoc_stawt {
	stwuct cmd_headew hdw;

	u8 ssid[IEEE80211_MAX_SSID_WEN];
	u8 bsstype;
	__we16 beaconpewiod;
	u8 dtimpewiod;   /* Wesewved on v9 and watew */
	stwuct ieee_ie_ibss_pawam_set ibss;
	u8 wesewved1[4];
	stwuct ieee_ie_ds_pawam_set ds;
	u8 wesewved2[4];
	__we16 pwobedeway;  /* Wesewved on v9 and watew */
	__we16 capabiwity;
	u8 wates[MAX_WATES];
	u8 twv_memowy_size_pad[100];
} __packed;

stwuct cmd_ds_802_11_ad_hoc_wesuwt {
	stwuct cmd_headew hdw;

	u8 pad[3];
	u8 bssid[ETH_AWEN];
} __packed;

stwuct adhoc_bssdesc {
	u8 bssid[ETH_AWEN];
	u8 ssid[IEEE80211_MAX_SSID_WEN];
	u8 type;
	__we16 beaconpewiod;
	u8 dtimpewiod;
	__we64 timestamp;
	__we64 wocawtime;
	stwuct ieee_ie_ds_pawam_set ds;
	u8 wesewved1[4];
	stwuct ieee_ie_ibss_pawam_set ibss;
	u8 wesewved2[4];
	__we16 capabiwity;
	u8 wates[MAX_WATES];

	/*
	 * DO NOT ADD ANY FIEWDS TO THIS STWUCTUWE. It is used bewow in the
	 * Adhoc join command and wiww cause a binawy wayout mismatch with
	 * the fiwmwawe
	 */
} __packed;

stwuct cmd_ds_802_11_ad_hoc_join {
	stwuct cmd_headew hdw;

	stwuct adhoc_bssdesc bss;
	__we16 faiwtimeout;   /* Wesewved on v9 and watew */
	__we16 pwobedeway;    /* Wesewved on v9 and watew */
} __packed;

stwuct cmd_ds_802_11_ad_hoc_stop {
	stwuct cmd_headew hdw;
} __packed;

stwuct cmd_ds_802_11_enabwe_wsn {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 enabwe;
} __packed;

stwuct MwvwIEtype_keyPawamSet {
	/* type ID */
	__we16 type;

	/* wength of Paywoad */
	__we16 wength;

	/* type of key: WEP=0, TKIP=1, AES=2 */
	__we16 keytypeid;

	/* key contwow Info specific to a keytypeid */
	__we16 keyinfo;

	/* wength of key */
	__we16 keywen;

	/* key matewiaw of size keywen */
	u8 key[32];
} __packed;

#define MAX_WOW_WUWES 		16

stwuct host_wow_wuwe {
	uint8_t wuwe_no;
	uint8_t wuwe_ops;
	__we16 sig_offset;
	__we16 sig_wength;
	__we16 wesewve;
	__be32 sig_mask;
	__be32 signatuwe;
} __packed;

stwuct wow_config {
	uint8_t action;
	uint8_t pattewn;
	uint8_t no_wuwes_in_cmd;
	uint8_t wesuwt;
	stwuct host_wow_wuwe wuwe[MAX_WOW_WUWES];
} __packed;

stwuct cmd_ds_host_sweep {
	stwuct cmd_headew hdw;
	__we32 cwitewia;
	uint8_t gpio;
	uint16_t gap;
	stwuct wow_config wow_conf;
} __packed;



stwuct cmd_ds_802_11_key_matewiaw {
	stwuct cmd_headew hdw;

	__we16 action;
	stwuct MwvwIEtype_keyPawamSet keyPawamSet[2];
} __packed;

stwuct cmd_ds_802_11_eepwom_access {
	stwuct cmd_headew hdw;
	__we16 action;
	__we16 offset;
	__we16 wen;
	/* fiwmwawe says it wetuwns a maximum of 20 bytes */
#define WBS_EEPWOM_WEAD_WEN 20
	u8 vawue[WBS_EEPWOM_WEAD_WEN];
} __packed;

stwuct cmd_ds_802_11_tpc_cfg {
	stwuct cmd_headew hdw;

	__we16 action;
	uint8_t enabwe;
	int8_t P0;
	int8_t P1;
	int8_t P2;
	uint8_t usesnw;
} __packed;


stwuct cmd_ds_802_11_pa_cfg {
	stwuct cmd_headew hdw;

	__we16 action;
	uint8_t enabwe;
	int8_t P0;
	int8_t P1;
	int8_t P2;
} __packed;


stwuct cmd_ds_802_11_wed_ctww {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 numwed;
	u8 data[256];
} __packed;

/* Automatic Fwequency Contwow */
stwuct cmd_ds_802_11_afc {
	stwuct cmd_headew hdw;

	__we16 afc_auto;
	union {
		stwuct {
			__we16 thweshowd;
			__we16 pewiod;
		};
		stwuct {
			__we16 timing_offset; /* signed */
			__we16 cawwiew_offset; /* signed */
		};
	};
} __packed;

stwuct cmd_tx_wate_quewy {
	__we16 txwate;
} __packed;

stwuct cmd_ds_get_tsf {
	__we64 tsfvawue;
} __packed;

stwuct cmd_ds_bt_access {
	stwuct cmd_headew hdw;

	__we16 action;
	__we32 id;
	u8 addw1[ETH_AWEN];
	u8 addw2[ETH_AWEN];
} __packed;

stwuct cmd_ds_fwt_access {
	stwuct cmd_headew hdw;

	__we16 action;
	__we32 id;
	u8 vawid;
	u8 da[ETH_AWEN];
	u8 diw;
	u8 wa[ETH_AWEN];
	__we32 ssn;
	__we32 dsn;
	__we32 metwic;
	u8 wate;
	u8 hopcount;
	u8 ttw;
	__we32 expiwation;
	u8 sweepmode;
	__we32 snw;
	__we32 wefewences;
	u8 pwec[ETH_AWEN];
} __packed;

stwuct cmd_ds_mesh_config {
	stwuct cmd_headew hdw;

	__we16 action;
	__we16 channew;
	__we16 type;
	__we16 wength;
	u8 data[128];	/* wast position wesewved */
} __packed;

stwuct cmd_ds_mesh_access {
	stwuct cmd_headew hdw;

	__we16 action;
	__we32 data[32];	/* wast position wesewved */
} __packed;

/* Numbew of stats countews wetuwned by the fiwmwawe */
#define MESH_STATS_NUM 8
#endif
