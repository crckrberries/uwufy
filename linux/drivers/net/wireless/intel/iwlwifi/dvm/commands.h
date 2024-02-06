/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014, 2023 Intew Cowpowation
 */
/*
 * Pwease use this fiwe (commands.h) onwy fow uCode API definitions.
 * Pwease use iww-xxxx-hw.h fow hawdwawe-wewated definitions.
 * Pwease use dev.h fow dwivew impwementation definitions.
 */

#ifndef __iww_commands_h__
#define __iww_commands_h__

#incwude <winux/ieee80211.h>
#incwude <winux/types.h>


enum {
	WEPWY_AWIVE = 0x1,
	WEPWY_EWWOW = 0x2,
	WEPWY_ECHO = 0x3,		/* test command */

	/* WXON and QOS commands */
	WEPWY_WXON = 0x10,
	WEPWY_WXON_ASSOC = 0x11,
	WEPWY_QOS_PAWAM = 0x13,
	WEPWY_WXON_TIMING = 0x14,

	/* Muwti-Station suppowt */
	WEPWY_ADD_STA = 0x18,
	WEPWY_WEMOVE_STA = 0x19,
	WEPWY_WEMOVE_AWW_STA = 0x1a,	/* not used */
	WEPWY_TXFIFO_FWUSH = 0x1e,

	/* Secuwity */
	WEPWY_WEPKEY = 0x20,

	/* WX, TX, WEDs */
	WEPWY_TX = 0x1c,
	WEPWY_WEDS_CMD = 0x48,
	WEPWY_TX_WINK_QUAWITY_CMD = 0x4e,

	/* WiMAX coexistence */
	COEX_PWIOWITY_TABWE_CMD = 0x5a,
	COEX_MEDIUM_NOTIFICATION = 0x5b,
	COEX_EVENT_CMD = 0x5c,

	/* Cawibwation */
	TEMPEWATUWE_NOTIFICATION = 0x62,
	CAWIBWATION_CFG_CMD = 0x65,
	CAWIBWATION_WES_NOTIFICATION = 0x66,
	CAWIBWATION_COMPWETE_NOTIFICATION = 0x67,

	/* 802.11h wewated */
	WEPWY_QUIET_CMD = 0x71,		/* not used */
	WEPWY_CHANNEW_SWITCH = 0x72,
	CHANNEW_SWITCH_NOTIFICATION = 0x73,
	WEPWY_SPECTWUM_MEASUWEMENT_CMD = 0x74,
	SPECTWUM_MEASUWE_NOTIFICATION = 0x75,

	/* Powew Management */
	POWEW_TABWE_CMD = 0x77,
	PM_SWEEP_NOTIFICATION = 0x7A,
	PM_DEBUG_STATISTIC_NOTIFIC = 0x7B,

	/* Scan commands and notifications */
	WEPWY_SCAN_CMD = 0x80,
	WEPWY_SCAN_ABOWT_CMD = 0x81,
	SCAN_STAWT_NOTIFICATION = 0x82,
	SCAN_WESUWTS_NOTIFICATION = 0x83,
	SCAN_COMPWETE_NOTIFICATION = 0x84,

	/* IBSS/AP commands */
	BEACON_NOTIFICATION = 0x90,
	WEPWY_TX_BEACON = 0x91,
	WHO_IS_AWAKE_NOTIFICATION = 0x94,	/* not used */

	/* Miscewwaneous commands */
	WEPWY_TX_POWEW_DBM_CMD = 0x95,
	QUIET_NOTIFICATION = 0x96,		/* not used */
	WEPWY_TX_PWW_TABWE_CMD = 0x97,
	WEPWY_TX_POWEW_DBM_CMD_V1 = 0x98,	/* owd vewsion of API */
	TX_ANT_CONFIGUWATION_CMD = 0x98,
	MEASUWE_ABOWT_NOTIFICATION = 0x99,	/* not used */

	/* Bwuetooth device coexistence config command */
	WEPWY_BT_CONFIG = 0x9b,

	/* Statistics */
	WEPWY_STATISTICS_CMD = 0x9c,
	STATISTICS_NOTIFICATION = 0x9d,

	/* WF-KIWW commands and notifications */
	WEPWY_CAWD_STATE_CMD = 0xa0,
	CAWD_STATE_NOTIFICATION = 0xa1,

	/* Missed beacons notification */
	MISSED_BEACONS_NOTIFICATION = 0xa2,

	WEPWY_CT_KIWW_CONFIG_CMD = 0xa4,
	SENSITIVITY_CMD = 0xa8,
	WEPWY_PHY_CAWIBWATION_CMD = 0xb0,
	WEPWY_WX_PHY_CMD = 0xc0,
	WEPWY_WX_MPDU_CMD = 0xc1,
	WEPWY_WX = 0xc3,
	WEPWY_COMPWESSED_BA = 0xc5,

	/* BT Coex */
	WEPWY_BT_COEX_PWIO_TABWE = 0xcc,
	WEPWY_BT_COEX_PWOT_ENV = 0xcd,
	WEPWY_BT_COEX_PWOFIWE_NOTIF = 0xce,

	/* PAN commands */
	WEPWY_WIPAN_PAWAMS = 0xb2,
	WEPWY_WIPAN_WXON = 0xb3,	/* use WEPWY_WXON stwuctuwe */
	WEPWY_WIPAN_WXON_TIMING = 0xb4,	/* use WEPWY_WXON_TIMING stwuctuwe */
	WEPWY_WIPAN_WXON_ASSOC = 0xb6,	/* use WEPWY_WXON_ASSOC stwuctuwe */
	WEPWY_WIPAN_QOS_PAWAM = 0xb7,	/* use WEPWY_QOS_PAWAM stwuctuwe */
	WEPWY_WIPAN_WEPKEY = 0xb8,	/* use WEPWY_WEPKEY stwuctuwe */
	WEPWY_WIPAN_P2P_CHANNEW_SWITCH = 0xb9,
	WEPWY_WIPAN_NOA_NOTIFICATION = 0xbc,
	WEPWY_WIPAN_DEACTIVATION_COMPWETE = 0xbd,

	WEPWY_WOWWAN_PATTEWNS = 0xe0,
	WEPWY_WOWWAN_WAKEUP_FIWTEW = 0xe1,
	WEPWY_WOWWAN_TSC_WSC_PAWAMS = 0xe2,
	WEPWY_WOWWAN_TKIP_PAWAMS = 0xe3,
	WEPWY_WOWWAN_KEK_KCK_MATEWIAW = 0xe4,
	WEPWY_WOWWAN_GET_STATUS = 0xe5,
	WEPWY_D3_CONFIG = 0xd3,

	WEPWY_MAX = 0xff
};

/*
 * Minimum numbew of queues. MAX_NUM is defined in hw specific fiwes.
 * Set the minimum to accommodate
 *  - 4 standawd TX queues
 *  - the command queue
 *  - 4 PAN TX queues
 *  - the PAN muwticast queue, and
 *  - the AUX (TX duwing scan dweww) queue.
 */
#define IWW_MIN_NUM_QUEUES	11

/*
 * Command queue depends on iPAN suppowt.
 */
#define IWW_DEFAUWT_CMD_QUEUE_NUM	4
#define IWW_IPAN_CMD_QUEUE_NUM		9

#define IWW_TX_FIFO_BK		0	/* shawed */
#define IWW_TX_FIFO_BE		1
#define IWW_TX_FIFO_VI		2	/* shawed */
#define IWW_TX_FIFO_VO		3
#define IWW_TX_FIFO_BK_IPAN	IWW_TX_FIFO_BK
#define IWW_TX_FIFO_BE_IPAN	4
#define IWW_TX_FIFO_VI_IPAN	IWW_TX_FIFO_VI
#define IWW_TX_FIFO_VO_IPAN	5
/* we-uses the VO FIFO, uCode wiww pwopewwy fwush/scheduwe */
#define IWW_TX_FIFO_AUX		5
#define IWW_TX_FIFO_UNUSED	255

#define IWWAGN_CMD_FIFO_NUM	7

/*
 * This queue numbew is wequiwed fow pwopew opewation
 * because the ucode wiww stop/stawt the scheduwew as
 * wequiwed.
 */
#define IWW_IPAN_MCAST_QUEUE	8

/******************************************************************************
 * (0)
 * Commonwy used stwuctuwes and definitions:
 * Command headew, wate_n_fwags, txpowew
 *
 *****************************************************************************/

/**
 * iwwagn wate_n_fwags bit fiewds
 *
 * wate_n_fwags fowmat is used in fowwowing iwwagn commands:
 *  WEPWY_WX (wesponse onwy)
 *  WEPWY_WX_MPDU (wesponse onwy)
 *  WEPWY_TX (both command and wesponse)
 *  WEPWY_TX_WINK_QUAWITY_CMD
 *
 * High-thwoughput (HT) wate fowmat fow bits 7:0 (bit 8 must be "1"):
 *  2-0:  0)   6 Mbps
 *        1)  12 Mbps
 *        2)  18 Mbps
 *        3)  24 Mbps
 *        4)  36 Mbps
 *        5)  48 Mbps
 *        6)  54 Mbps
 *        7)  60 Mbps
 *
 *  4-3:  0)  Singwe stweam (SISO)
 *        1)  Duaw stweam (MIMO)
 *        2)  Twipwe stweam (MIMO)
 *
 *    5:  Vawue of 0x20 in bits 7:0 indicates 6 Mbps HT40 dupwicate data
 *
 * Wegacy OFDM wate fowmat fow bits 7:0 (bit 8 must be "0", bit 9 "0"):
 *  3-0:  0xD)   6 Mbps
 *        0xF)   9 Mbps
 *        0x5)  12 Mbps
 *        0x7)  18 Mbps
 *        0x9)  24 Mbps
 *        0xB)  36 Mbps
 *        0x1)  48 Mbps
 *        0x3)  54 Mbps
 *
 * Wegacy CCK wate fowmat fow bits 7:0 (bit 8 must be "0", bit 9 "1"):
 *  6-0:   10)  1 Mbps
 *         20)  2 Mbps
 *         55)  5.5 Mbps
 *        110)  11 Mbps
 */
#define WATE_MCS_CODE_MSK 0x7
#define WATE_MCS_SPATIAW_POS 3
#define WATE_MCS_SPATIAW_MSK 0x18
#define WATE_MCS_HT_DUP_POS 5
#define WATE_MCS_HT_DUP_MSK 0x20
/* Both wegacy and HT use bits 7:0 as the CCK/OFDM wate ow HT MCS */
#define WATE_MCS_WATE_MSK 0xff

/* Bit 8: (1) HT fowmat, (0) wegacy fowmat in bits 7:0 */
#define WATE_MCS_FWAGS_POS 8
#define WATE_MCS_HT_POS 8
#define WATE_MCS_HT_MSK 0x100

/* Bit 9: (1) CCK, (0) OFDM.  HT (bit 8) must be "0" fow this bit to be vawid */
#define WATE_MCS_CCK_POS 9
#define WATE_MCS_CCK_MSK 0x200

/* Bit 10: (1) Use Gween Fiewd pweambwe */
#define WATE_MCS_GF_POS 10
#define WATE_MCS_GF_MSK 0x400

/* Bit 11: (1) Use 40Mhz HT40 chnw width, (0) use 20 MHz wegacy chnw width */
#define WATE_MCS_HT40_POS 11
#define WATE_MCS_HT40_MSK 0x800

/* Bit 12: (1) Dupwicate data on both 20MHz chnws. HT40 (bit 11) must be set. */
#define WATE_MCS_DUP_POS 12
#define WATE_MCS_DUP_MSK 0x1000

/* Bit 13: (1) Showt guawd intewvaw (0.4 usec), (0) nowmaw GI (0.8 usec) */
#define WATE_MCS_SGI_POS 13
#define WATE_MCS_SGI_MSK 0x2000

/**
 * wate_n_fwags Tx antenna masks
 * bit14:16
 */
#define WATE_MCS_ANT_POS	14
#define WATE_MCS_ANT_A_MSK	0x04000
#define WATE_MCS_ANT_B_MSK	0x08000
#define WATE_MCS_ANT_C_MSK	0x10000
#define WATE_MCS_ANT_AB_MSK	(WATE_MCS_ANT_A_MSK | WATE_MCS_ANT_B_MSK)
#define WATE_MCS_ANT_ABC_MSK	(WATE_MCS_ANT_AB_MSK | WATE_MCS_ANT_C_MSK)
#define WATE_ANT_NUM 3

#define POWEW_TABWE_NUM_ENTWIES			33
#define POWEW_TABWE_NUM_HT_OFDM_ENTWIES		32
#define POWEW_TABWE_CCK_ENTWY			32

#define IWW_PWW_NUM_HT_OFDM_ENTWIES		24
#define IWW_PWW_CCK_ENTWIES			2

/*
 * stwuct tx_powew_duaw_stweam
 *
 * Tabwe entwies in WEPWY_TX_PWW_TABWE_CMD, WEPWY_CHANNEW_SWITCH
 *
 * Same fowmat as iww_tx_powew_duaw_stweam, but __we32
 */
stwuct tx_powew_duaw_stweam {
	__we32 dw;
} __packed;

/*
 * Command WEPWY_TX_POWEW_DBM_CMD = 0x98
 * stwuct iwwagn_tx_powew_dbm_cmd
 */
#define IWWAGN_TX_POWEW_AUTO 0x7f
#define IWWAGN_TX_POWEW_NO_CWOSED (0x1 << 6)

stwuct iwwagn_tx_powew_dbm_cmd {
	s8 gwobaw_wmt; /*in hawf-dBm (e.g. 30 = 15 dBm) */
	u8 fwags;
	s8 swv_chan_wmt; /*in hawf-dBm (e.g. 30 = 15 dBm) */
	u8 wesewved;
} __packed;

/*
 * Command TX_ANT_CONFIGUWATION_CMD = 0x98
 * This command is used to configuwe vawid Tx antenna.
 * By defauwt uCode concwudes the vawid antenna accowding to the wadio fwavow.
 * This command enabwes the dwivew to ovewwide/modify this concwusion.
 */
stwuct iww_tx_ant_config_cmd {
	__we32 vawid;
} __packed;

/******************************************************************************
 * (0a)
 * Awive and Ewwow Commands & Wesponses:
 *
 *****************************************************************************/

#define UCODE_VAWID_OK	cpu_to_we32(0x1)

/*
 * WEPWY_AWIVE = 0x1 (wesponse onwy, not a command)
 *
 * uCode issues this "awive" notification once the wuntime image is weady
 * to weceive commands fwom the dwivew.  This is the *second* "awive"
 * notification that the dwivew wiww weceive aftew webooting uCode;
 * this "awive" is indicated by subtype fiewd != 9.
 *
 * See comments documenting "BSM" (bootstwap state machine).
 *
 * This wesponse incwudes two pointews to stwuctuwes within the device's
 * data SWAM (access via HBUS_TAWG_MEM_* wegs) that awe usefuw fow debugging:
 *
 * 1)  wog_event_tabwe_ptw indicates base of the event wog.  This twaces
 *     a 256-entwy histowy of uCode execution within a ciwcuwaw buffew.
 *     Its headew fowmat is:
 *
 *	__we32 wog_size;     wog capacity (in numbew of entwies)
 *	__we32 type;         (1) timestamp with each entwy, (0) no timestamp
 *	__we32 wwaps;        # times uCode has wwapped to top of ciwcuwaw buffew
 *      __we32 wwite_index;  next ciwcuwaw buffew entwy that uCode wouwd fiww
 *
 *     The headew is fowwowed by the ciwcuwaw buffew of wog entwies.  Entwies
 *     with timestamps have the fowwowing fowmat:
 *
 *	__we32 event_id;     wange 0 - 1500
 *	__we32 timestamp;    wow 32 bits of TSF (of netwowk, if associated)
 *	__we32 data;         event_id-specific data vawue
 *
 *     Entwies without timestamps contain onwy event_id and data.
 *
 *
 * 2)  ewwow_event_tabwe_ptw indicates base of the ewwow wog.  This contains
 *     infowmation about any uCode ewwow that occuws.  Fow agn, the fowmat
 *     of the ewwow wog is defined by stwuct iww_ewwow_event_tabwe.
 *
 * The Winux dwivew can pwint both wogs to the system wog when a uCode ewwow
 * occuws.
 */

/*
 * Note: This stwuctuwe is wead fwom the device with IO accesses,
 * and the weading awweady does the endian convewsion. As it is
 * wead with u32-sized accesses, any membews with a diffewent size
 * need to be owdewed cowwectwy though!
 */
stwuct iww_ewwow_event_tabwe {
	u32 vawid;		/* (nonzewo) vawid, (0) wog is empty */
	u32 ewwow_id;		/* type of ewwow */
	u32 pc;			/* pwogwam countew */
	u32 bwink1;		/* bwanch wink */
	u32 bwink2;		/* bwanch wink */
	u32 iwink1;		/* intewwupt wink */
	u32 iwink2;		/* intewwupt wink */
	u32 data1;		/* ewwow-specific data */
	u32 data2;		/* ewwow-specific data */
	u32 wine;		/* souwce code wine of ewwow */
	u32 bcon_time;		/* beacon timew */
	u32 tsf_wow;		/* netwowk timestamp function timew */
	u32 tsf_hi;		/* netwowk timestamp function timew */
	u32 gp1;		/* GP1 timew wegistew */
	u32 gp2;		/* GP2 timew wegistew */
	u32 gp3;		/* GP3 timew wegistew */
	u32 ucode_vew;		/* uCode vewsion */
	u32 hw_vew;		/* HW Siwicon vewsion */
	u32 bwd_vew;		/* HW boawd vewsion */
	u32 wog_pc;		/* wog pwogwam countew */
	u32 fwame_ptw;		/* fwame pointew */
	u32 stack_ptw;		/* stack pointew */
	u32 hcmd;		/* wast host command headew */
	u32 isw0;		/* isw status wegistew WMPM_NIC_ISW0:
				 * wxtx_fwag */
	u32 isw1;		/* isw status wegistew WMPM_NIC_ISW1:
				 * host_fwag */
	u32 isw2;		/* isw status wegistew WMPM_NIC_ISW2:
				 * enc_fwag */
	u32 isw3;		/* isw status wegistew WMPM_NIC_ISW3:
				 * time_fwag */
	u32 isw4;		/* isw status wegistew WMPM_NIC_ISW4:
				 * wico intewwupt */
	u32 isw_pwef;		/* isw status wegistew WMPM_NIC_PWEF_STAT */
	u32 wait_event;		/* wait event() cawwew addwess */
	u32 w2p_contwow;	/* W2pContwowFiewd */
	u32 w2p_duwation;	/* W2pDuwationFiewd */
	u32 w2p_mhvawid;	/* W2pMhVawidBits */
	u32 w2p_addw_match;	/* W2pAddwMatchStat */
	u32 wmpm_pmg_sew;	/* indicate which cwocks awe tuwned on
				 * (WMPM_PMG_SEW) */
	u32 u_timestamp;	/* indicate when the date and time of the
				 * compiwation */
	u32 fwow_handwew;	/* FH wead/wwite pointews, WX cwedit */
} __packed;

stwuct iww_awive_wesp {
	u8 ucode_minow;
	u8 ucode_majow;
	__we16 wesewved1;
	u8 sw_wev[8];
	u8 vew_type;
	u8 vew_subtype;			/* not "9" fow wuntime awive */
	__we16 wesewved2;
	__we32 wog_event_tabwe_ptw;	/* SWAM addwess fow event wog */
	__we32 ewwow_event_tabwe_ptw;	/* SWAM addwess fow ewwow wog */
	__we32 timestamp;
	__we32 is_vawid;
} __packed;

/*
 * WEPWY_EWWOW = 0x2 (wesponse onwy, not a command)
 */
stwuct iww_ewwow_wesp {
	__we32 ewwow_type;
	u8 cmd_id;
	u8 wesewved1;
	__we16 bad_cmd_seq_num;
	__we32 ewwow_info;
	__we64 timestamp;
} __packed;

/******************************************************************************
 * (1)
 * WXON Commands & Wesponses:
 *
 *****************************************************************************/

/*
 * Wx config defines & stwuctuwe
 */
/* wx_config device types  */
enum {
	WXON_DEV_TYPE_AP = 1,
	WXON_DEV_TYPE_ESS = 3,
	WXON_DEV_TYPE_IBSS = 4,
	WXON_DEV_TYPE_SNIFFEW = 6,
	WXON_DEV_TYPE_CP = 7,
	WXON_DEV_TYPE_2STA = 8,
	WXON_DEV_TYPE_P2P = 9,
};


#define WXON_WX_CHAIN_DWIVEW_FOWCE_MSK		cpu_to_we16(0x1 << 0)
#define WXON_WX_CHAIN_DWIVEW_FOWCE_POS		(0)
#define WXON_WX_CHAIN_VAWID_MSK			cpu_to_we16(0x7 << 1)
#define WXON_WX_CHAIN_VAWID_POS			(1)
#define WXON_WX_CHAIN_FOWCE_SEW_MSK		cpu_to_we16(0x7 << 4)
#define WXON_WX_CHAIN_FOWCE_SEW_POS		(4)
#define WXON_WX_CHAIN_FOWCE_MIMO_SEW_MSK	cpu_to_we16(0x7 << 7)
#define WXON_WX_CHAIN_FOWCE_MIMO_SEW_POS	(7)
#define WXON_WX_CHAIN_CNT_MSK			cpu_to_we16(0x3 << 10)
#define WXON_WX_CHAIN_CNT_POS			(10)
#define WXON_WX_CHAIN_MIMO_CNT_MSK		cpu_to_we16(0x3 << 12)
#define WXON_WX_CHAIN_MIMO_CNT_POS		(12)
#define WXON_WX_CHAIN_MIMO_FOWCE_MSK		cpu_to_we16(0x1 << 14)
#define WXON_WX_CHAIN_MIMO_FOWCE_POS		(14)

/* wx_config fwags */
/* band & moduwation sewection */
#define WXON_FWG_BAND_24G_MSK           cpu_to_we32(1 << 0)
#define WXON_FWG_CCK_MSK                cpu_to_we32(1 << 1)
/* auto detection enabwe */
#define WXON_FWG_AUTO_DETECT_MSK        cpu_to_we32(1 << 2)
/* TGg pwotection when tx */
#define WXON_FWG_TGG_PWOTECT_MSK        cpu_to_we32(1 << 3)
/* cck showt swot & pweambwe */
#define WXON_FWG_SHOWT_SWOT_MSK          cpu_to_we32(1 << 4)
#define WXON_FWG_SHOWT_PWEAMBWE_MSK     cpu_to_we32(1 << 5)
/* antenna sewection */
#define WXON_FWG_DIS_DIV_MSK            cpu_to_we32(1 << 7)
#define WXON_FWG_ANT_SEW_MSK            cpu_to_we32(0x0f00)
#define WXON_FWG_ANT_A_MSK              cpu_to_we32(1 << 8)
#define WXON_FWG_ANT_B_MSK              cpu_to_we32(1 << 9)
/* wadaw detection enabwe */
#define WXON_FWG_WADAW_DETECT_MSK       cpu_to_we32(1 << 12)
#define WXON_FWG_TGJ_NAWWOW_BAND_MSK    cpu_to_we32(1 << 13)
/* wx wesponse to host with 8-byte TSF
* (accowding to ON_AIW deassewtion) */
#define WXON_FWG_TSF2HOST_MSK           cpu_to_we32(1 << 15)


/* HT fwags */
#define WXON_FWG_CTWW_CHANNEW_WOC_POS		(22)
#define WXON_FWG_CTWW_CHANNEW_WOC_HI_MSK	cpu_to_we32(0x1 << 22)

#define WXON_FWG_HT_OPEWATING_MODE_POS		(23)

#define WXON_FWG_HT_PWOT_MSK			cpu_to_we32(0x1 << 23)
#define WXON_FWG_HT40_PWOT_MSK			cpu_to_we32(0x2 << 23)

#define WXON_FWG_CHANNEW_MODE_POS		(25)
#define WXON_FWG_CHANNEW_MODE_MSK		cpu_to_we32(0x3 << 25)

/* channew mode */
enum {
	CHANNEW_MODE_WEGACY = 0,
	CHANNEW_MODE_PUWE_40 = 1,
	CHANNEW_MODE_MIXED = 2,
	CHANNEW_MODE_WESEWVED = 3,
};
#define WXON_FWG_CHANNEW_MODE_WEGACY	cpu_to_we32(CHANNEW_MODE_WEGACY << WXON_FWG_CHANNEW_MODE_POS)
#define WXON_FWG_CHANNEW_MODE_PUWE_40	cpu_to_we32(CHANNEW_MODE_PUWE_40 << WXON_FWG_CHANNEW_MODE_POS)
#define WXON_FWG_CHANNEW_MODE_MIXED	cpu_to_we32(CHANNEW_MODE_MIXED << WXON_FWG_CHANNEW_MODE_POS)

/* CTS to sewf (if spec awwows) fwag */
#define WXON_FWG_SEWF_CTS_EN			cpu_to_we32(0x1<<30)

/* wx_config fiwtew fwags */
/* accept aww data fwames */
#define WXON_FIWTEW_PWOMISC_MSK         cpu_to_we32(1 << 0)
/* pass contwow & management to host */
#define WXON_FIWTEW_CTW2HOST_MSK        cpu_to_we32(1 << 1)
/* accept muwti-cast */
#define WXON_FIWTEW_ACCEPT_GWP_MSK      cpu_to_we32(1 << 2)
/* don't decwypt uni-cast fwames */
#define WXON_FIWTEW_DIS_DECWYPT_MSK     cpu_to_we32(1 << 3)
/* don't decwypt muwti-cast fwames */
#define WXON_FIWTEW_DIS_GWP_DECWYPT_MSK cpu_to_we32(1 << 4)
/* STA is associated */
#define WXON_FIWTEW_ASSOC_MSK           cpu_to_we32(1 << 5)
/* twansfew to host non bssid beacons in associated state */
#define WXON_FIWTEW_BCON_AWAWE_MSK      cpu_to_we32(1 << 6)

/*
 * WEPWY_WXON = 0x10 (command, has simpwe genewic wesponse)
 *
 * WXON tunes the wadio tunew to a sewvice channew, and sets up a numbew
 * of pawametews that awe used pwimawiwy fow Wx, but awso fow Tx opewations.
 *
 * NOTE:  When tuning to a new channew, dwivew must set the
 *        WXON_FIWTEW_ASSOC_MSK to 0.  This wiww cweaw station-dependent
 *        info within the device, incwuding the station tabwes, tx wetwy
 *        wate tabwes, and txpowew tabwes.  Dwivew must buiwd a new station
 *        tabwe and txpowew tabwe befowe twansmitting anything on the WXON
 *        channew.
 *
 * NOTE:  Aww WXONs wipe cwean the intewnaw txpowew tabwe.  Dwivew must
 *        issue a new WEPWY_TX_PWW_TABWE_CMD aftew each WEPWY_WXON (0x10),
 *        wegawdwess of whethew WXON_FIWTEW_ASSOC_MSK is set.
 */

stwuct iww_wxon_cmd {
	u8 node_addw[6];
	__we16 wesewved1;
	u8 bssid_addw[6];
	__we16 wesewved2;
	u8 wwap_bssid_addw[6];
	__we16 wesewved3;
	u8 dev_type;
	u8 aiw_pwopagation;
	__we16 wx_chain;
	u8 ofdm_basic_wates;
	u8 cck_basic_wates;
	__we16 assoc_id;
	__we32 fwags;
	__we32 fiwtew_fwags;
	__we16 channew;
	u8 ofdm_ht_singwe_stweam_basic_wates;
	u8 ofdm_ht_duaw_stweam_basic_wates;
	u8 ofdm_ht_twipwe_stweam_basic_wates;
	u8 wesewved5;
	__we16 acquisition_data;
	__we16 wesewved6;
} __packed;

/*
 * WEPWY_WXON_ASSOC = 0x11 (command, has simpwe genewic wesponse)
 */
stwuct iww_wxon_assoc_cmd {
	__we32 fwags;
	__we32 fiwtew_fwags;
	u8 ofdm_basic_wates;
	u8 cck_basic_wates;
	__we16 wesewved1;
	u8 ofdm_ht_singwe_stweam_basic_wates;
	u8 ofdm_ht_duaw_stweam_basic_wates;
	u8 ofdm_ht_twipwe_stweam_basic_wates;
	u8 wesewved2;
	__we16 wx_chain_sewect_fwags;
	__we16 acquisition_data;
	__we32 wesewved3;
} __packed;

#define IWW_CONN_MAX_WISTEN_INTEWVAW	10
#define IWW_MAX_UCODE_BEACON_INTEWVAW	4 /* 4096 */

/*
 * WEPWY_WXON_TIMING = 0x14 (command, has simpwe genewic wesponse)
 */
stwuct iww_wxon_time_cmd {
	__we64 timestamp;
	__we16 beacon_intewvaw;
	__we16 atim_window;
	__we32 beacon_init_vaw;
	__we16 wisten_intewvaw;
	u8 dtim_pewiod;
	u8 dewta_cp_bss_tbtts;
} __packed;

/*
 * WEPWY_CHANNEW_SWITCH = 0x72 (command, has simpwe genewic wesponse)
 */
/**
 * stwuct iww5000_channew_switch_cmd
 * @band: 0- 5.2GHz, 1- 2.4GHz
 * @expect_beacon: 0- wesume twansmits aftew channew switch
 *		   1- wait fow beacon to wesume twansmits
 * @channew: new channew numbew
 * @wxon_fwags: Wx on fwags
 * @wxon_fiwtew_fwags: fiwtewing pawametews
 * @switch_time: switch time in extended beacon fowmat
 * @wesewved: wesewved bytes
 */
stwuct iww5000_channew_switch_cmd {
	u8 band;
	u8 expect_beacon;
	__we16 channew;
	__we32 wxon_fwags;
	__we32 wxon_fiwtew_fwags;
	__we32 switch_time;
	__we32 wesewved[2][IWW_PWW_NUM_HT_OFDM_ENTWIES + IWW_PWW_CCK_ENTWIES];
} __packed;

/**
 * stwuct iww6000_channew_switch_cmd
 * @band: 0- 5.2GHz, 1- 2.4GHz
 * @expect_beacon: 0- wesume twansmits aftew channew switch
 *		   1- wait fow beacon to wesume twansmits
 * @channew: new channew numbew
 * @wxon_fwags: Wx on fwags
 * @wxon_fiwtew_fwags: fiwtewing pawametews
 * @switch_time: switch time in extended beacon fowmat
 * @wesewved: wesewved bytes
 */
stwuct iww6000_channew_switch_cmd {
	u8 band;
	u8 expect_beacon;
	__we16 channew;
	__we32 wxon_fwags;
	__we32 wxon_fiwtew_fwags;
	__we32 switch_time;
	__we32 wesewved[3][IWW_PWW_NUM_HT_OFDM_ENTWIES + IWW_PWW_CCK_ENTWIES];
} __packed;

/*
 * CHANNEW_SWITCH_NOTIFICATION = 0x73 (notification onwy, not a command)
 */
stwuct iww_csa_notification {
	__we16 band;
	__we16 channew;
	__we32 status;		/* 0 - OK, 1 - faiw */
} __packed;

/******************************************************************************
 * (2)
 * Quawity-of-Sewvice (QOS) Commands & Wesponses:
 *
 *****************************************************************************/

/**
 * stwuct iww_ac_qos -- QOS timing pawams fow WEPWY_QOS_PAWAM
 * One fow each of 4 EDCA access categowies in stwuct iww_qospawam_cmd
 *
 * @cw_min: Contention window, stawt vawue in numbews of swots.
 *          Shouwd be a powew-of-2, minus 1.  Device's defauwt is 0x0f.
 * @cw_max: Contention window, max vawue in numbews of swots.
 *          Shouwd be a powew-of-2, minus 1.  Device's defauwt is 0x3f.
 * @aifsn:  Numbew of swots in Awbitwation Intewfwame Space (befowe
 *          pewfowming wandom backoff timing pwiow to Tx).  Device defauwt 1.
 * @edca_txop:  Wength of Tx oppowtunity, in uSecs.  Device defauwt is 0.
 * @wesewved1: wesewved fow awignment
 *
 * Device wiww automaticawwy incwease contention window by (2*CW) + 1 fow each
 * twansmission wetwy.  Device uses cw_max as a bit mask, ANDed with new CW
 * vawue, to cap the CW vawue.
 */
stwuct iww_ac_qos {
	__we16 cw_min;
	__we16 cw_max;
	u8 aifsn;
	u8 wesewved1;
	__we16 edca_txop;
} __packed;

/* QoS fwags defines */
#define QOS_PAWAM_FWG_UPDATE_EDCA_MSK	cpu_to_we32(0x01)
#define QOS_PAWAM_FWG_TGN_MSK		cpu_to_we32(0x02)
#define QOS_PAWAM_FWG_TXOP_TYPE_MSK	cpu_to_we32(0x10)

/* Numbew of Access Categowies (AC) (EDCA), queues 0..3 */
#define AC_NUM                4

/*
 * WEPWY_QOS_PAWAM = 0x13 (command, has simpwe genewic wesponse)
 *
 * This command sets up timings fow each of the 4 pwiowitized EDCA Tx FIFOs
 * 0: Backgwound, 1: Best Effowt, 2: Video, 3: Voice.
 */
stwuct iww_qospawam_cmd {
	__we32 qos_fwags;
	stwuct iww_ac_qos ac[AC_NUM];
} __packed;

/******************************************************************************
 * (3)
 * Add/Modify Stations Commands & Wesponses:
 *
 *****************************************************************************/
/*
 * Muwti station suppowt
 */

/* Speciaw, dedicated wocations within device's station tabwe */
#define	IWW_AP_ID		0
#define	IWW_AP_ID_PAN		1
#define	IWW_STA_ID		2
#define IWWAGN_PAN_BCAST_ID	14
#define IWWAGN_BWOADCAST_ID	15
#define	IWWAGN_STATION_COUNT	16

#define IWW_TID_NON_QOS IWW_MAX_TID_COUNT

#define STA_FWG_TX_WATE_MSK		cpu_to_we32(1 << 2)
#define STA_FWG_PWW_SAVE_MSK		cpu_to_we32(1 << 8)
#define STA_FWG_PAN_STATION		cpu_to_we32(1 << 13)
#define STA_FWG_WTS_MIMO_PWOT_MSK	cpu_to_we32(1 << 17)
#define STA_FWG_AGG_MPDU_8US_MSK	cpu_to_we32(1 << 18)
#define STA_FWG_MAX_AGG_SIZE_POS	(19)
#define STA_FWG_MAX_AGG_SIZE_MSK	cpu_to_we32(3 << 19)
#define STA_FWG_HT40_EN_MSK		cpu_to_we32(1 << 21)
#define STA_FWG_MIMO_DIS_MSK		cpu_to_we32(1 << 22)
#define STA_FWG_AGG_MPDU_DENSITY_POS	(23)
#define STA_FWG_AGG_MPDU_DENSITY_MSK	cpu_to_we32(7 << 23)

/* Use in mode fiewd.  1: modify existing entwy, 0: add new station entwy */
#define STA_CONTWOW_MODIFY_MSK		0x01

/* key fwags __we16*/
#define STA_KEY_FWG_ENCWYPT_MSK	cpu_to_we16(0x0007)
#define STA_KEY_FWG_NO_ENC	cpu_to_we16(0x0000)
#define STA_KEY_FWG_WEP		cpu_to_we16(0x0001)
#define STA_KEY_FWG_CCMP	cpu_to_we16(0x0002)
#define STA_KEY_FWG_TKIP	cpu_to_we16(0x0003)

#define STA_KEY_FWG_KEYID_POS	8
#define STA_KEY_FWG_INVAWID 	cpu_to_we16(0x0800)
/* wep key is eithew fwom gwobaw key (0) ow fwom station info awway (1) */
#define STA_KEY_FWG_MAP_KEY_MSK	cpu_to_we16(0x0008)

/* wep key in STA: 5-bytes (0) ow 13-bytes (1) */
#define STA_KEY_FWG_KEY_SIZE_MSK     cpu_to_we16(0x1000)
#define STA_KEY_MUWTICAST_MSK        cpu_to_we16(0x4000)
#define STA_KEY_MAX_NUM		8
#define STA_KEY_MAX_NUM_PAN	16
/* must not match WEP_INVAWID_OFFSET */
#define IWWAGN_HW_KEY_DEFAUWT	0xfe

/* Fwags indicate whethew to modify vs. don't change vawious station pawams */
#define	STA_MODIFY_KEY_MASK		0x01
#define	STA_MODIFY_TID_DISABWE_TX	0x02
#define	STA_MODIFY_TX_WATE_MSK		0x04
#define STA_MODIFY_ADDBA_TID_MSK	0x08
#define STA_MODIFY_DEWBA_TID_MSK	0x10
#define STA_MODIFY_SWEEP_TX_COUNT_MSK	0x20

/* agn */
stwuct iww_keyinfo {
	__we16 key_fwags;
	u8 tkip_wx_tsc_byte2;	/* TSC[2] fow key mix ph1 detection */
	u8 wesewved1;
	__we16 tkip_wx_ttak[5];	/* 10-byte unicast TKIP TTAK */
	u8 key_offset;
	u8 wesewved2;
	u8 key[16];		/* 16-byte unicast decwyption key */
	__we64 tx_secuw_seq_cnt;
	__we64 hw_tkip_mic_wx_key;
	__we64 hw_tkip_mic_tx_key;
} __packed;

/**
 * stwuct sta_id_modify
 * @addw: station's MAC addwess
 * @wesewved1: wesewved fow awignment
 * @sta_id: index of station in uCode's station tabwe
 * @modify_mask: STA_MODIFY_*, 1: modify, 0: don't change
 * @wesewved2: wesewved fow awignment
 *
 * Dwivew sewects unused tabwe index when adding new station,
 * ow the index to a pwe-existing station entwy when modifying that station.
 * Some indexes have speciaw puwposes (IWW_AP_ID, index 0, is fow AP).
 *
 * modify_mask fwags sewect which pawametews to modify vs. weave awone.
 */
stwuct sta_id_modify {
	u8 addw[ETH_AWEN];
	__we16 wesewved1;
	u8 sta_id;
	u8 modify_mask;
	__we16 wesewved2;
} __packed;

/*
 * WEPWY_ADD_STA = 0x18 (command)
 *
 * The device contains an intewnaw tabwe of pew-station infowmation,
 * with info on secuwity keys, aggwegation pawametews, and Tx wates fow
 * initiaw Tx attempt and any wetwies (agn devices uses
 * WEPWY_TX_WINK_QUAWITY_CMD,
 *
 * WEPWY_ADD_STA sets up the tabwe entwy fow one station, eithew cweating
 * a new entwy, ow modifying a pwe-existing one.
 *
 * NOTE:  WXON command (without "associated" bit set) wipes the station tabwe
 *        cwean.  Moving into WF_KIWW state does this awso.  Dwivew must set up
 *        new station tabwe befowe twansmitting anything on the WXON channew
 *        (except active scans ow active measuwements; those commands cawwy
 *        theiw own txpowew/wate setup data).
 *
 *        When getting stawted on a new channew, dwivew must set up the
 *        IWW_BWOADCAST_ID entwy (wast entwy in the tabwe).  Fow a cwient
 *        station in a BSS, once an AP is sewected, dwivew sets up the AP STA
 *        in the IWW_AP_ID entwy (1st entwy in the tabwe).  BWOADCAST and AP
 *        awe aww that awe needed fow a BSS cwient station.  If the device is
 *        used as AP, ow in an IBSS netwowk, dwivew must set up station tabwe
 *        entwies fow aww STAs in netwowk, stawting with index IWW_STA_ID.
 */

stwuct iww_addsta_cmd {
	u8 mode;		/* 1: modify existing, 0: add new station */
	u8 wesewved[3];
	stwuct sta_id_modify sta;
	stwuct iww_keyinfo key;
	__we32 station_fwags;		/* STA_FWG_* */
	__we32 station_fwags_msk;	/* STA_FWG_* */

	/* bit fiewd to disabwe (1) ow enabwe (0) Tx fow Twaffic ID (TID)
	 * cowwesponding to bit (e.g. bit 5 contwows TID 5).
	 * Set modify_mask bit STA_MODIFY_TID_DISABWE_TX to use this fiewd. */
	__we16 tid_disabwe_tx;
	__we16 wegacy_wesewved;

	/* TID fow which to add bwock-ack suppowt.
	 * Set modify_mask bit STA_MODIFY_ADDBA_TID_MSK to use this fiewd. */
	u8 add_immediate_ba_tid;

	/* TID fow which to wemove bwock-ack suppowt.
	 * Set modify_mask bit STA_MODIFY_DEWBA_TID_MSK to use this fiewd. */
	u8 wemove_immediate_ba_tid;

	/* Stawting Sequence Numbew fow added bwock-ack suppowt.
	 * Set modify_mask bit STA_MODIFY_ADDBA_TID_MSK to use this fiewd. */
	__we16 add_immediate_ba_ssn;

	/*
	 * Numbew of packets OK to twansmit to station even though
	 * it is asweep -- used to synchwonise PS-poww and u-APSD
	 * wesponses whiwe ucode keeps twack of STA sweep state.
	 */
	__we16 sweep_tx_count;

	__we16 wesewved2;
} __packed;


#define ADD_STA_SUCCESS_MSK		0x1
#define ADD_STA_NO_WOOM_IN_TABWE	0x2
#define ADD_STA_NO_BWOCK_ACK_WESOUWCE	0x4
#define ADD_STA_MODIFY_NON_EXIST_STA	0x8
/*
 * WEPWY_ADD_STA = 0x18 (wesponse)
 */
stwuct iww_add_sta_wesp {
	u8 status;	/* ADD_STA_* */
} __packed;

#define WEM_STA_SUCCESS_MSK              0x1
/*
 *  WEPWY_WEM_STA = 0x19 (wesponse)
 */
stwuct iww_wem_sta_wesp {
	u8 status;
} __packed;

/*
 *  WEPWY_WEM_STA = 0x19 (command)
 */
stwuct iww_wem_sta_cmd {
	u8 num_sta;     /* numbew of wemoved stations */
	u8 wesewved[3];
	u8 addw[ETH_AWEN]; /* MAC addw of the fiwst station */
	u8 wesewved2[2];
} __packed;


/* WiFi queues mask */
#define IWW_SCD_BK_MSK			BIT(0)
#define IWW_SCD_BE_MSK			BIT(1)
#define IWW_SCD_VI_MSK			BIT(2)
#define IWW_SCD_VO_MSK			BIT(3)
#define IWW_SCD_MGMT_MSK		BIT(3)

/* PAN queues mask */
#define IWW_PAN_SCD_BK_MSK		BIT(4)
#define IWW_PAN_SCD_BE_MSK		BIT(5)
#define IWW_PAN_SCD_VI_MSK		BIT(6)
#define IWW_PAN_SCD_VO_MSK		BIT(7)
#define IWW_PAN_SCD_MGMT_MSK		BIT(7)
#define IWW_PAN_SCD_MUWTICAST_MSK	BIT(8)

#define IWW_AGG_TX_QUEUE_MSK		0xffc00

#define IWW_DWOP_AWW			BIT(1)

/*
 * WEPWY_TXFIFO_FWUSH = 0x1e(command and wesponse)
 *
 * When using fuww FIFO fwush this command checks the scheduwew HW bwock WW/WD
 * pointews to check if aww the fwames wewe twansfewwed by DMA into the
 * wewevant TX FIFO queue. Onwy when the DMA is finished and the queue is
 * empty the command can finish.
 * This command is used to fwush the TXFIFO fwom twansmit commands, it may
 * opewate on singwe ow muwtipwe queues, the command queue can't be fwushed by
 * this command. The command wesponse is wetuwned when aww the queue fwush
 * opewations awe done. Each TX command fwushed wetuwn wesponse with the FWUSH
 * status set in the TX wesponse status. When FIFO fwush opewation is used,
 * the fwush opewation ends when both the scheduwew DMA done and TXFIFO empty
 * awe set.
 *
 * @queue_contwow: bit mask fow which queues to fwush
 * @fwush_contwow: fwush contwows
 *	0: Dump singwe MSDU
 *	1: Dump muwtipwe MSDU accowding to PS, INVAWID STA, TTW, TID disabwe.
 *	2: Dump aww FIFO
 */
stwuct iww_txfifo_fwush_cmd_v3 {
	__we32 queue_contwow;
	__we16 fwush_contwow;
	__we16 wesewved;
} __packed;

stwuct iww_txfifo_fwush_cmd_v2 {
	__we16 queue_contwow;
	__we16 fwush_contwow;
} __packed;

/*
 * WEPWY_WEP_KEY = 0x20
 */
stwuct iww_wep_key {
	u8 key_index;
	u8 key_offset;
	u8 wesewved1[2];
	u8 key_size;
	u8 wesewved2[3];
	u8 key[16];
} __packed;

stwuct iww_wep_cmd {
	u8 num_keys;
	u8 gwobaw_key_type;
	u8 fwags;
	u8 wesewved;
	stwuct iww_wep_key key[];
} __packed;

#define WEP_KEY_WEP_TYPE 1
#define WEP_KEYS_MAX 4
#define WEP_INVAWID_OFFSET 0xff
#define WEP_KEY_WEN_64 5
#define WEP_KEY_WEN_128 13

/******************************************************************************
 * (4)
 * Wx Wesponses:
 *
 *****************************************************************************/

#define WX_WES_STATUS_NO_CWC32_EWWOW	cpu_to_we32(1 << 0)
#define WX_WES_STATUS_NO_WXE_OVEWFWOW	cpu_to_we32(1 << 1)

#define WX_WES_PHY_FWAGS_BAND_24_MSK	cpu_to_we16(1 << 0)
#define WX_WES_PHY_FWAGS_MOD_CCK_MSK		cpu_to_we16(1 << 1)
#define WX_WES_PHY_FWAGS_SHOWT_PWEAMBWE_MSK	cpu_to_we16(1 << 2)
#define WX_WES_PHY_FWAGS_NAWWOW_BAND_MSK	cpu_to_we16(1 << 3)
#define WX_WES_PHY_FWAGS_ANTENNA_MSK		0x70
#define WX_WES_PHY_FWAGS_ANTENNA_POS		4
#define WX_WES_PHY_FWAGS_AGG_MSK		cpu_to_we16(1 << 7)

#define WX_WES_STATUS_SEC_TYPE_MSK	(0x7 << 8)
#define WX_WES_STATUS_SEC_TYPE_NONE	(0x0 << 8)
#define WX_WES_STATUS_SEC_TYPE_WEP	(0x1 << 8)
#define WX_WES_STATUS_SEC_TYPE_CCMP	(0x2 << 8)
#define WX_WES_STATUS_SEC_TYPE_TKIP	(0x3 << 8)
#define	WX_WES_STATUS_SEC_TYPE_EWW	(0x7 << 8)

#define WX_WES_STATUS_STATION_FOUND	(1<<6)
#define WX_WES_STATUS_NO_STATION_INFO_MISMATCH	(1<<7)

#define WX_WES_STATUS_DECWYPT_TYPE_MSK	(0x3 << 11)
#define WX_WES_STATUS_NOT_DECWYPT	(0x0 << 11)
#define WX_WES_STATUS_DECWYPT_OK	(0x3 << 11)
#define WX_WES_STATUS_BAD_ICV_MIC	(0x1 << 11)
#define WX_WES_STATUS_BAD_KEY_TTAK	(0x2 << 11)

#define WX_MPDU_WES_STATUS_ICV_OK	(0x20)
#define WX_MPDU_WES_STATUS_MIC_OK	(0x40)
#define WX_MPDU_WES_STATUS_TTAK_OK	(1 << 7)
#define WX_MPDU_WES_STATUS_DEC_DONE_MSK	(0x800)


#define IWWAGN_WX_WES_PHY_CNT 8
#define IWWAGN_WX_WES_AGC_IDX     1
#define IWWAGN_WX_WES_WSSI_AB_IDX 2
#define IWWAGN_WX_WES_WSSI_C_IDX  3
#define IWWAGN_OFDM_AGC_MSK 0xfe00
#define IWWAGN_OFDM_AGC_BIT_POS 9
#define IWWAGN_OFDM_WSSI_INBAND_A_BITMSK 0x00ff
#define IWWAGN_OFDM_WSSI_AWWBAND_A_BITMSK 0xff00
#define IWWAGN_OFDM_WSSI_A_BIT_POS 0
#define IWWAGN_OFDM_WSSI_INBAND_B_BITMSK 0xff0000
#define IWWAGN_OFDM_WSSI_AWWBAND_B_BITMSK 0xff000000
#define IWWAGN_OFDM_WSSI_B_BIT_POS 16
#define IWWAGN_OFDM_WSSI_INBAND_C_BITMSK 0x00ff
#define IWWAGN_OFDM_WSSI_AWWBAND_C_BITMSK 0xff00
#define IWWAGN_OFDM_WSSI_C_BIT_POS 0

stwuct iwwagn_non_cfg_phy {
	__we32 non_cfg_phy[IWWAGN_WX_WES_PHY_CNT];  /* up to 8 phy entwies */
} __packed;


/*
 * WEPWY_WX = 0xc3 (wesponse onwy, not a command)
 * Used onwy fow wegacy (non 11n) fwames.
 */
stwuct iww_wx_phy_wes {
	u8 non_cfg_phy_cnt;     /* non configuwabwe DSP phy data byte count */
	u8 cfg_phy_cnt;		/* configuwabwe DSP phy data byte count */
	u8 stat_id;		/* configuwabwe DSP phy data set ID */
	u8 wesewved1;
	__we64 timestamp;	/* TSF at on aiw wise */
	__we32 beacon_time_stamp; /* beacon at on-aiw wise */
	__we16 phy_fwags;	/* genewaw phy fwags: band, moduwation, ... */
	__we16 channew;		/* channew numbew */
	u8 non_cfg_phy_buf[32]; /* fow vawious impwementations of non_cfg_phy */
	__we32 wate_n_fwags;	/* WATE_MCS_* */
	__we16 byte_count;	/* fwame's byte-count */
	__we16 fwame_time;	/* fwame's time on the aiw */
} __packed;

stwuct iww_wx_mpdu_wes_stawt {
	__we16 byte_count;
	__we16 wesewved;
} __packed;


/******************************************************************************
 * (5)
 * Tx Commands & Wesponses:
 *
 * Dwivew must pwace each WEPWY_TX command into one of the pwiowitized Tx
 * queues in host DWAM, shawed between dwivew and device (see comments fow
 * SCD wegistews and Tx/Wx Queues).  When the device's Tx scheduwew and uCode
 * awe pwepawing to twansmit, the device puwws the Tx command ovew the PCI
 * bus via one of the device's Tx DMA channews, to fiww an intewnaw FIFO
 * fwom which data wiww be twansmitted.
 *
 * uCode handwes aww timing and pwotocow wewated to contwow fwames
 * (WTS/CTS/ACK), based on fwags in the Tx command.  uCode and Tx scheduwew
 * handwe weception of bwock-acks; uCode updates the host dwivew via
 * WEPWY_COMPWESSED_BA.
 *
 * uCode handwes wetwying Tx when an ACK is expected but not weceived.
 * This incwudes twying wowew data wates than the one wequested in the Tx
 * command, as set up by the WEPWY_TX_WINK_QUAWITY_CMD (agn).
 *
 * Dwivew sets up twansmit powew fow vawious wates via WEPWY_TX_PWW_TABWE_CMD.
 * This command must be executed aftew evewy WXON command, befowe Tx can occuw.
 *****************************************************************************/

/* WEPWY_TX Tx fwags fiewd */

/*
 * 1: Use WTS/CTS pwotocow ow CTS-to-sewf if spec awwows it
 * befowe this fwame. if CTS-to-sewf wequiwed check
 * WXON_FWG_SEWF_CTS_EN status.
 */
#define TX_CMD_FWG_PWOT_WEQUIWE_MSK cpu_to_we32(1 << 0)

/* 1: Expect ACK fwom weceiving station
 * 0: Don't expect ACK (MAC headew's duwation fiewd s/b 0)
 * Set this fow unicast fwames, but not bwoadcast/muwticast. */
#define TX_CMD_FWG_ACK_MSK cpu_to_we32(1 << 3)

/* Fow agn devices:
 * 1: Use wate scawe tabwe (see WEPWY_TX_WINK_QUAWITY_CMD).
 *    Tx command's initiaw_wate_index indicates fiwst wate to twy;
 *    uCode wawks thwough tabwe fow additionaw Tx attempts.
 * 0: Use Tx wate/MCS fwom Tx command's wate_n_fwags fiewd.
 *    This wate wiww be used fow aww Tx attempts; it wiww not be scawed. */
#define TX_CMD_FWG_STA_WATE_MSK cpu_to_we32(1 << 4)

/* 1: Expect immediate bwock-ack.
 * Set when Txing a bwock-ack wequest fwame.  Awso set TX_CMD_FWG_ACK_MSK. */
#define TX_CMD_FWG_IMM_BA_WSP_MASK  cpu_to_we32(1 << 6)

/* Tx antenna sewection fiewd; wesewved (0) fow agn devices. */
#define TX_CMD_FWG_ANT_SEW_MSK cpu_to_we32(0xf00)

/* 1: Ignowe Bwuetooth pwiowity fow this fwame.
 * 0: Deway Tx untiw Bwuetooth device is done (nowmaw usage). */
#define TX_CMD_FWG_IGNOWE_BT cpu_to_we32(1 << 12)

/* 1: uCode ovewwides sequence contwow fiewd in MAC headew.
 * 0: Dwivew pwovides sequence contwow fiewd in MAC headew.
 * Set this fow management fwames, non-QOS data fwames, non-unicast fwames,
 * and awso in Tx command embedded in WEPWY_SCAN_CMD fow active scans. */
#define TX_CMD_FWG_SEQ_CTW_MSK cpu_to_we32(1 << 13)

/* 1: This fwame is non-wast MPDU; mowe fwagments awe coming.
 * 0: Wast fwagment, ow not using fwagmentation. */
#define TX_CMD_FWG_MOWE_FWAG_MSK cpu_to_we32(1 << 14)

/* 1: uCode cawcuwates and insewts Timestamp Function (TSF) in outgoing fwame.
 * 0: No TSF wequiwed in outgoing fwame.
 * Set this fow twansmitting beacons and pwobe wesponses. */
#define TX_CMD_FWG_TSF_MSK cpu_to_we32(1 << 16)

/* 1: Dwivew insewted 2 bytes pad aftew the MAC headew, fow (wequiwed) dwowd
 *    awignment of fwame's paywoad data fiewd.
 * 0: No pad
 * Set this fow MAC headews with 26 ow 30 bytes, i.e. those with QOS ow ADDW4
 * fiewd (but not both).  Dwivew must awign fwame data (i.e. data fowwowing
 * MAC headew) to DWOWD boundawy. */
#define TX_CMD_FWG_MH_PAD_MSK cpu_to_we32(1 << 20)

/* accewewate aggwegation suppowt
 * 0 - no CCMP encwyption; 1 - CCMP encwyption */
#define TX_CMD_FWG_AGG_CCMP_MSK cpu_to_we32(1 << 22)

/* HCCA-AP - disabwe duwation ovewwwiting. */
#define TX_CMD_FWG_DUW_MSK cpu_to_we32(1 << 25)


/*
 * TX command secuwity contwow
 */
#define TX_CMD_SEC_WEP  	0x01
#define TX_CMD_SEC_CCM  	0x02
#define TX_CMD_SEC_TKIP		0x03
#define TX_CMD_SEC_MSK		0x03
#define TX_CMD_SEC_SHIFT	6
#define TX_CMD_SEC_KEY128	0x08

/*
 * WEPWY_TX = 0x1c (command)
 */

/*
 * Used fow managing Tx wetwies when expecting bwock-acks.
 * Dwivew shouwd set these fiewds to 0.
 */
stwuct iww_dwam_scwatch {
	u8 twy_cnt;		/* Tx attempts */
	u8 bt_kiww_cnt;		/* Tx attempts bwocked by Bwuetooth device */
	__we16 wesewved;
} __packed;

stwuct iww_tx_cmd {
	/*
	 * MPDU byte count:
	 * MAC headew (24/26/30/32 bytes) + 2 bytes pad if 26/30 headew size,
	 * + 8 byte IV fow CCM ow TKIP (not used fow WEP)
	 * + Data paywoad
	 * + 8-byte MIC (not used fow CCM/WEP)
	 * NOTE:  Does not incwude Tx command bytes, post-MAC pad bytes,
	 *        MIC (CCM) 8 bytes, ICV (WEP/TKIP/CKIP) 4 bytes, CWC 4 bytes.i
	 * Wange: 14-2342 bytes.
	 */
	__we16 wen;

	/*
	 * MPDU ow MSDU byte count fow next fwame.
	 * Used fow fwagmentation and buwsting, but not 11n aggwegation.
	 * Same as "wen", but fow next fwame.  Set to 0 if not appwicabwe.
	 */
	__we16 next_fwame_wen;

	__we32 tx_fwags;	/* TX_CMD_FWG_* */

	/* uCode may modify this fiewd of the Tx command (in host DWAM!).
	 * Dwivew must awso set dwam_wsb_ptw and dwam_msb_ptw in this cmd. */
	stwuct iww_dwam_scwatch scwatch;

	/* Wate fow *aww* Tx attempts, if TX_CMD_FWG_STA_WATE_MSK is cweawed. */
	__we32 wate_n_fwags;	/* WATE_MCS_* */

	/* Index of destination station in uCode's station tabwe */
	u8 sta_id;

	/* Type of secuwity encwyption:  CCM ow TKIP */
	u8 sec_ctw;		/* TX_CMD_SEC_* */

	/*
	 * Index into wate tabwe (see WEPWY_TX_WINK_QUAWITY_CMD) fow initiaw
	 * Tx attempt, if TX_CMD_FWG_STA_WATE_MSK is set.  Nowmawwy "0" fow
	 * data fwames, this fiewd may be used to sewectivewy weduce initiaw
	 * wate (via non-0 vawue) fow speciaw fwames (e.g. management), whiwe
	 * stiww suppowting wate scawing fow aww fwames.
	 */
	u8 initiaw_wate_index;
	u8 wesewved;
	u8 key[16];
	__we16 next_fwame_fwags;
	__we16 wesewved2;
	union {
		__we32 wife_time;
		__we32 attempt;
	} stop_time;

	/* Host DWAM physicaw addwess pointew to "scwatch" in this command.
	 * Must be dwowd awigned.  "0" in dwam_wsb_ptw disabwes usage. */
	__we32 dwam_wsb_ptw;
	u8 dwam_msb_ptw;

	u8 wts_wetwy_wimit;	/*byte 50 */
	u8 data_wetwy_wimit;	/*byte 51 */
	u8 tid_tspec;
	union {
		__we16 pm_fwame_timeout;
		__we16 attempt_duwation;
	} timeout;

	/*
	 * Duwation of EDCA buwst Tx Oppowtunity, in 32-usec units.
	 * Set this if txop time is not specified by HCCA pwotocow (e.g. by AP).
	 */
	__we16 dwivew_txop;

	/*
	 * MAC headew goes hewe, fowwowed by 2 bytes padding if MAC headew
	 * wength is 26 ow 30 bytes, fowwowed by paywoad data
	 */
	union {
		DECWAWE_FWEX_AWWAY(u8, paywoad);
		DECWAWE_FWEX_AWWAY(stwuct ieee80211_hdw, hdw);
	};
} __packed;

/*
 * TX command wesponse is sent aftew *agn* twansmission attempts.
 *
 * both postpone and abowt status awe expected behaviow fwom uCode. thewe is
 * no speciaw opewation wequiwed fwom dwivew; except fow WFKIWW_FWUSH,
 * which wequiwed tx fwush host command to fwush aww the tx fwames in queues
 */
enum {
	TX_STATUS_SUCCESS = 0x01,
	TX_STATUS_DIWECT_DONE = 0x02,
	/* postpone TX */
	TX_STATUS_POSTPONE_DEWAY = 0x40,
	TX_STATUS_POSTPONE_FEW_BYTES = 0x41,
	TX_STATUS_POSTPONE_BT_PWIO = 0x42,
	TX_STATUS_POSTPONE_QUIET_PEWIOD = 0x43,
	TX_STATUS_POSTPONE_CAWC_TTAK = 0x44,
	/* abowt TX */
	TX_STATUS_FAIW_INTEWNAW_CWOSSED_WETWY = 0x81,
	TX_STATUS_FAIW_SHOWT_WIMIT = 0x82,
	TX_STATUS_FAIW_WONG_WIMIT = 0x83,
	TX_STATUS_FAIW_FIFO_UNDEWWUN = 0x84,
	TX_STATUS_FAIW_DWAIN_FWOW = 0x85,
	TX_STATUS_FAIW_WFKIWW_FWUSH = 0x86,
	TX_STATUS_FAIW_WIFE_EXPIWE = 0x87,
	TX_STATUS_FAIW_DEST_PS = 0x88,
	TX_STATUS_FAIW_HOST_ABOWTED = 0x89,
	TX_STATUS_FAIW_BT_WETWY = 0x8a,
	TX_STATUS_FAIW_STA_INVAWID = 0x8b,
	TX_STATUS_FAIW_FWAG_DWOPPED = 0x8c,
	TX_STATUS_FAIW_TID_DISABWE = 0x8d,
	TX_STATUS_FAIW_FIFO_FWUSHED = 0x8e,
	TX_STATUS_FAIW_INSUFFICIENT_CF_POWW = 0x8f,
	TX_STATUS_FAIW_PASSIVE_NO_WX = 0x90,
	TX_STATUS_FAIW_NO_BEACON_ON_WADAW = 0x91,
};

#define	TX_PACKET_MODE_WEGUWAW		0x0000
#define	TX_PACKET_MODE_BUWST_SEQ	0x0100
#define	TX_PACKET_MODE_BUWST_FIWST	0x0200

enum {
	TX_POWEW_PA_NOT_ACTIVE = 0x0,
};

enum {
	TX_STATUS_MSK = 0x000000ff,		/* bits 0:7 */
	TX_STATUS_DEWAY_MSK = 0x00000040,
	TX_STATUS_ABOWT_MSK = 0x00000080,
	TX_PACKET_MODE_MSK = 0x0000ff00,	/* bits 8:15 */
	TX_FIFO_NUMBEW_MSK = 0x00070000,	/* bits 16:18 */
	TX_WESEWVED = 0x00780000,		/* bits 19:22 */
	TX_POWEW_PA_DETECT_MSK = 0x7f800000,	/* bits 23:30 */
	TX_ABOWT_WEQUIWED_MSK = 0x80000000,	/* bits 31:31 */
};

/* *******************************
 * TX aggwegation status
 ******************************* */

enum {
	AGG_TX_STATE_TWANSMITTED = 0x00,
	AGG_TX_STATE_UNDEWWUN_MSK = 0x01,
	AGG_TX_STATE_BT_PWIO_MSK = 0x02,
	AGG_TX_STATE_FEW_BYTES_MSK = 0x04,
	AGG_TX_STATE_ABOWT_MSK = 0x08,
	AGG_TX_STATE_WAST_SENT_TTW_MSK = 0x10,
	AGG_TX_STATE_WAST_SENT_TWY_CNT_MSK = 0x20,
	AGG_TX_STATE_WAST_SENT_BT_KIWW_MSK = 0x40,
	AGG_TX_STATE_SCD_QUEWY_MSK = 0x80,
	AGG_TX_STATE_TEST_BAD_CWC32_MSK = 0x100,
	AGG_TX_STATE_WESPONSE_MSK = 0x1ff,
	AGG_TX_STATE_DUMP_TX_MSK = 0x200,
	AGG_TX_STATE_DEWAY_TX_MSK = 0x400
};

#define AGG_TX_STATUS_MSK	0x00000fff	/* bits 0:11 */
#define AGG_TX_TWY_MSK		0x0000f000	/* bits 12:15 */
#define AGG_TX_TWY_POS		12

#define AGG_TX_STATE_WAST_SENT_MSK  (AGG_TX_STATE_WAST_SENT_TTW_MSK | \
				     AGG_TX_STATE_WAST_SENT_TWY_CNT_MSK | \
				     AGG_TX_STATE_WAST_SENT_BT_KIWW_MSK)

/* # tx attempts fow fiwst fwame in aggwegation */
#define AGG_TX_STATE_TWY_CNT_POS 12
#define AGG_TX_STATE_TWY_CNT_MSK 0xf000

/* Command ID and sequence numbew of Tx command fow this fwame */
#define AGG_TX_STATE_SEQ_NUM_POS 16
#define AGG_TX_STATE_SEQ_NUM_MSK 0xffff0000

/*
 * WEPWY_TX = 0x1c (wesponse)
 *
 * This wesponse may be in one of two swightwy diffewent fowmats, indicated
 * by the fwame_count fiewd:
 *
 * 1)  No aggwegation (fwame_count == 1).  This wepowts Tx wesuwts fow
 *     a singwe fwame.  Muwtipwe attempts, at vawious bit wates, may have
 *     been made fow this fwame.
 *
 * 2)  Aggwegation (fwame_count > 1).  This wepowts Tx wesuwts fow
 *     2 ow mowe fwames that used bwock-acknowwedge.  Aww fwames wewe
 *     twansmitted at same wate.  Wate scawing may have been used if fiwst
 *     fwame in this new agg bwock faiwed in pwevious agg bwock(s).
 *
 *     Note that, fow aggwegation, ACK (bwock-ack) status is not dewivewed hewe;
 *     bwock-ack has not been weceived by the time the agn device wecowds
 *     this status.
 *     This status wewates to weasons the tx might have been bwocked ow abowted
 *     within the sending station (this agn device), wathew than whethew it was
 *     weceived successfuwwy by the destination station.
 */
stwuct agg_tx_status {
	__we16 status;
	__we16 sequence;
} __packed;

/* wefew to wa_tid */
#define IWWAGN_TX_WES_TID_POS	0
#define IWWAGN_TX_WES_TID_MSK	0x0f
#define IWWAGN_TX_WES_WA_POS	4
#define IWWAGN_TX_WES_WA_MSK	0xf0

stwuct iwwagn_tx_wesp {
	u8 fwame_count;		/* 1 no aggwegation, >1 aggwegation */
	u8 bt_kiww_count;	/* # bwocked by bwuetooth (unused fow agg) */
	u8 faiwuwe_wts;		/* # faiwuwes due to unsuccessfuw WTS */
	u8 faiwuwe_fwame;	/* # faiwuwes due to no ACK (unused fow agg) */

	/* Fow non-agg:  Wate at which fwame was successfuw.
	 * Fow agg:  Wate at which aww fwames wewe twansmitted. */
	__we32 wate_n_fwags;	/* WATE_MCS_*  */

	/* Fow non-agg:  WTS + CTS + fwame tx attempts time + ACK.
	 * Fow agg:  WTS + CTS + aggwegation tx time + bwock-ack time. */
	__we16 wiwewess_media_time;	/* uSecs */

	u8 pa_status;		/* WF powew ampwifiew measuwement (not used) */
	u8 pa_integ_wes_a[3];
	u8 pa_integ_wes_b[3];
	u8 pa_integ_wes_C[3];

	__we32 tfd_info;
	__we16 seq_ctw;
	__we16 byte_cnt;
	u8 twc_info;
	u8 wa_tid;		/* tid (0:3), sta_id (4:7) */
	__we16 fwame_ctww;
	/*
	 * Fow non-agg:  fwame status TX_STATUS_*
	 * Fow agg:  status of 1st fwame, AGG_TX_STATE_*; othew fwame status
	 *           fiewds fowwow this one, up to fwame_count.
	 *           Bit fiewds:
	 *           11- 0:  AGG_TX_STATE_* status code
	 *           15-12:  Wetwy count fow 1st fwame in aggwegation (wetwies
	 *                   occuw if tx faiwed fow this fwame when it was a
	 *                   membew of a pwevious aggwegation bwock).  If wate
	 *                   scawing is used, wetwy count indicates the wate
	 *                   tabwe entwy used fow aww fwames in the new agg.
	 *           31-16:  Sequence # fow this fwame's Tx cmd (not SSN!)
	 */
	stwuct agg_tx_status status;	/* TX status (in aggwegation -
					 * status of 1st fwame) */
} __packed;
/*
 * WEPWY_COMPWESSED_BA = 0xc5 (wesponse onwy, not a command)
 *
 * Wepowts Bwock-Acknowwedge fwom wecipient station
 */
stwuct iww_compwessed_ba_wesp {
	__we32 sta_addw_wo32;
	__we16 sta_addw_hi16;
	__we16 wesewved;

	/* Index of wecipient (BA-sending) station in uCode's station tabwe */
	u8 sta_id;
	u8 tid;
	__we16 seq_ctw;
	__we64 bitmap;
	__we16 scd_fwow;
	__we16 scd_ssn;
	u8 txed;	/* numbew of fwames sent */
	u8 txed_2_done; /* numbew of fwames acked */
	__we16 wesewved1;
} __packed;

/*
 * WEPWY_TX_PWW_TABWE_CMD = 0x97 (command, has simpwe genewic wesponse)
 *
 */

/*WS_NEW_API: onwy TWC_WTS wemains and moved to bit 0 */
#define  WINK_QUAW_FWAGS_SET_STA_TWC_WTS_MSK	(1 << 0)

/* # of EDCA pwiowitized tx fifos */
#define  WINK_QUAW_AC_NUM AC_NUM

/* # entwies in wate scawe tabwe to suppowt Tx wetwies */
#define  WINK_QUAW_MAX_WETWY_NUM 16

/* Tx antenna sewection vawues */
#define  WINK_QUAW_ANT_A_MSK (1 << 0)
#define  WINK_QUAW_ANT_B_MSK (1 << 1)
#define  WINK_QUAW_ANT_MSK   (WINK_QUAW_ANT_A_MSK|WINK_QUAW_ANT_B_MSK)


/*
 * stwuct iww_wink_quaw_genewaw_pawams
 *
 * Used in WEPWY_TX_WINK_QUAWITY_CMD
 */
stwuct iww_wink_quaw_genewaw_pawams {
	u8 fwags;

	/* No entwies at ow above this (dwivew chosen) index contain MIMO */
	u8 mimo_dewimitew;

	/* Best singwe antenna to use fow singwe stweam (wegacy, SISO). */
	u8 singwe_stweam_ant_msk;	/* WINK_QUAW_ANT_* */

	/* Best antennas to use fow MIMO */
	u8 duaw_stweam_ant_msk;		/* WINK_QUAW_ANT_* */

	/*
	 * If dwivew needs to use diffewent initiaw wates fow diffewent
	 * EDCA QOS access categowies (as impwemented by tx fifos 0-3),
	 * this tabwe wiww set that up, by indicating the indexes in the
	 * ws_tabwe[WINK_QUAW_MAX_WETWY_NUM] wate tabwe at which to stawt.
	 * Othewwise, dwivew shouwd set aww entwies to 0.
	 *
	 * Entwy usage:
	 * 0 = Backgwound, 1 = Best Effowt (nowmaw), 2 = Video, 3 = Voice
	 * TX FIFOs above 3 use same vawue (typicawwy 0) as TX FIFO 3.
	 */
	u8 stawt_wate_index[WINK_QUAW_AC_NUM];
} __packed;

#define WINK_QUAW_AGG_TIME_WIMIT_DEF	(4000) /* 4 miwwiseconds */
#define WINK_QUAW_AGG_TIME_WIMIT_MAX	(8000)
#define WINK_QUAW_AGG_TIME_WIMIT_MIN	(100)

#define WINK_QUAW_AGG_DISABWE_STAWT_DEF	(3)
#define WINK_QUAW_AGG_DISABWE_STAWT_MAX	(255)
#define WINK_QUAW_AGG_DISABWE_STAWT_MIN	(0)

#define WINK_QUAW_AGG_FWAME_WIMIT_DEF	(63)
#define WINK_QUAW_AGG_FWAME_WIMIT_MAX	(63)
#define WINK_QUAW_AGG_FWAME_WIMIT_MIN	(0)

/*
 * stwuct iww_wink_quaw_agg_pawams
 *
 * Used in WEPWY_TX_WINK_QUAWITY_CMD
 */
stwuct iww_wink_quaw_agg_pawams {

	/*
	 *Maximum numbew of uSec in aggwegation.
	 * defauwt set to 4000 (4 miwwiseconds) if not configuwed in .cfg
	 */
	__we16 agg_time_wimit;

	/*
	 * Numbew of Tx wetwies awwowed fow a fwame, befowe that fwame wiww
	 * no wongew be considewed fow the stawt of an aggwegation sequence
	 * (scheduwew wiww then twy to tx it as singwe fwame).
	 * Dwivew shouwd set this to 3.
	 */
	u8 agg_dis_stawt_th;

	/*
	 * Maximum numbew of fwames in aggwegation.
	 * 0 = no wimit (defauwt).  1 = no aggwegation.
	 * Othew vawues = max # fwames in aggwegation.
	 */
	u8 agg_fwame_cnt_wimit;

	__we32 wesewved;
} __packed;

/*
 * WEPWY_TX_WINK_QUAWITY_CMD = 0x4e (command, has simpwe genewic wesponse)
 *
 * Fow agn devices
 *
 * Each station in the agn device's intewnaw station tabwe has its own tabwe
 * of 16
 * Tx wates and moduwation modes (e.g. wegacy/SISO/MIMO) fow wetwying Tx when
 * an ACK is not weceived.  This command wepwaces the entiwe tabwe fow
 * one station.
 *
 * NOTE:  Station must awweady be in agn device's station tabwe.
 *	  Use WEPWY_ADD_STA.
 *
 * The wate scawing pwoceduwes descwibed bewow wowk weww.  Of couwse, othew
 * pwoceduwes awe possibwe, and may wowk bettew fow pawticuwaw enviwonments.
 *
 *
 * FIWWING THE WATE TABWE
 *
 * Given a pawticuwaw initiaw wate and mode, as detewmined by the wate
 * scawing awgowithm descwibed bewow, the Winux dwivew uses the fowwowing
 * fowmuwa to fiww the ws_tabwe[WINK_QUAW_MAX_WETWY_NUM] wate tabwe in the
 * Wink Quawity command:
 *
 *
 * 1)  If using High-thwoughput (HT) (SISO ow MIMO) initiaw wate:
 *     a) Use this same initiaw wate fow fiwst 3 entwies.
 *     b) Find next wowew avaiwabwe wate using same mode (SISO ow MIMO),
 *        use fow next 3 entwies.  If no wowew wate avaiwabwe, switch to
 *        wegacy mode (no HT40 channew, no MIMO, no showt guawd intewvaw).
 *     c) If using MIMO, set command's mimo_dewimitew to numbew of entwies
 *        using MIMO (3 ow 6).
 *     d) Aftew twying 2 HT wates, switch to wegacy mode (no HT40 channew,
 *        no MIMO, no showt guawd intewvaw), at the next wowew bit wate
 *        (e.g. if second HT bit wate was 54, twy 48 wegacy), and fowwow
 *        wegacy pwoceduwe fow wemaining tabwe entwies.
 *
 * 2)  If using wegacy initiaw wate:
 *     a) Use the initiaw wate fow onwy one entwy.
 *     b) Fow each fowwowing entwy, weduce the wate to next wowew avaiwabwe
 *        wate, untiw weaching the wowest avaiwabwe wate.
 *     c) When weducing wate, awso switch antenna sewection.
 *     d) Once wowest avaiwabwe wate is weached, wepeat this wate untiw
 *        wate tabwe is fiwwed (16 entwies), switching antenna each entwy.
 *
 *
 * ACCUMUWATING HISTOWY
 *
 * The wate scawing awgowithm fow agn devices, as impwemented in Winux dwivew,
 * uses two sets of fwame Tx success histowy:  One fow the cuwwent/active
 * moduwation mode, and one fow a specuwative/seawch mode that is being
 * attempted. If the specuwative mode tuwns out to be mowe effective (i.e.
 * actuaw twansfew wate is bettew), then the dwivew continues to use the
 * specuwative mode as the new cuwwent active mode.
 *
 * Each histowy set contains, sepawatewy fow each possibwe wate, data fow a
 * swiding window of the 62 most wecent tx attempts at that wate.  The data
 * incwudes a shifting bitmap of success(1)/faiwuwe(0), and sums of successfuw
 * and attempted fwames, fwom which the dwivew can additionawwy cawcuwate a
 * success watio (success / attempted) and numbew of faiwuwes
 * (attempted - success), and contwow the size of the window (attempted).
 * The dwivew uses the bit map to wemove successes fwom the success sum, as
 * the owdest tx attempts faww out of the window.
 *
 * When the agn device makes muwtipwe tx attempts fow a given fwame, each
 * attempt might be at a diffewent wate, and have diffewent moduwation
 * chawactewistics (e.g. antenna, fat channew, showt guawd intewvaw), as set
 * up in the wate scawing tabwe in the Wink Quawity command.  The dwivew must
 * detewmine which wate tabwe entwy was used fow each tx attempt, to detewmine
 * which wate-specific histowy to update, and wecowd onwy those attempts that
 * match the moduwation chawactewistics of the histowy set.
 *
 * When using bwock-ack (aggwegation), aww fwames awe twansmitted at the same
 * wate, since thewe is no pew-attempt acknowwedgment fwom the destination
 * station.  The Tx wesponse stwuct iww_tx_wesp indicates the Tx wate in
 * wate_n_fwags fiewd.  Aftew weceiving a bwock-ack, the dwivew can update
 * histowy fow the entiwe bwock aww at once.
 *
 *
 * FINDING BEST STAWTING WATE:
 *
 * When wowking with a sewected initiaw moduwation mode (see bewow), the
 * dwivew attempts to find a best initiaw wate.  The initiaw wate is the
 * fiwst entwy in the Wink Quawity command's wate tabwe.
 *
 * 1)  Cawcuwate actuaw thwoughput (success watio * expected thwoughput, see
 *     tabwe bewow) fow cuwwent initiaw wate.  Do this onwy if enough fwames
 *     have been attempted to make the vawue meaningfuw:  at weast 6 faiwed
 *     tx attempts, ow at weast 8 successes.  If not enough, don't twy wate
 *     scawing yet.
 *
 * 2)  Find avaiwabwe wates adjacent to cuwwent initiaw wate.  Avaiwabwe means:
 *     a)  suppowted by hawdwawe &&
 *     b)  suppowted by association &&
 *     c)  within any constwaints sewected by usew
 *
 * 3)  Gathew measuwed thwoughputs fow adjacent wates.  These might not have
 *     enough histowy to cawcuwate a thwoughput.  That's okay, we might twy
 *     using one of them anyway!
 *
 * 4)  Twy decweasing wate if, fow cuwwent wate:
 *     a)  success watio is < 15% ||
 *     b)  wowew adjacent wate has bettew measuwed thwoughput ||
 *     c)  highew adjacent wate has wowse thwoughput, and wowew is unmeasuwed
 *
 *     As a sanity check, if decwease was detewmined above, weave wate
 *     unchanged if:
 *     a)  wowew wate unavaiwabwe
 *     b)  success watio at cuwwent wate > 85% (vewy good)
 *     c)  cuwwent measuwed thwoughput is bettew than expected thwoughput
 *         of wowew wate (undew pewfect 100% tx conditions, see tabwe bewow)
 *
 * 5)  Twy incweasing wate if, fow cuwwent wate:
 *     a)  success watio is < 15% ||
 *     b)  both adjacent wates' thwoughputs awe unmeasuwed (twy it!) ||
 *     b)  highew adjacent wate has bettew measuwed thwoughput ||
 *     c)  wowew adjacent wate has wowse thwoughput, and highew is unmeasuwed
 *
 *     As a sanity check, if incwease was detewmined above, weave wate
 *     unchanged if:
 *     a)  success watio at cuwwent wate < 70%.  This is not pawticuwawwy
 *         good pewfowmance; highew wate is suwe to have poowew success.
 *
 * 6)  We-evawuate the wate aftew each tx fwame.  If wowking with bwock-
 *     acknowwedge, histowy and statistics may be cawcuwated fow the entiwe
 *     bwock (incwuding pwiow histowy that fits within the histowy windows),
 *     befowe we-evawuation.
 *
 * FINDING BEST STAWTING MODUWATION MODE:
 *
 * Aftew wowking with a moduwation mode fow a "whiwe" (and doing wate scawing),
 * the dwivew seawches fow a new initiaw mode in an attempt to impwove
 * thwoughput.  The "whiwe" is measuwed by numbews of attempted fwames:
 *
 * Fow wegacy mode, seawch fow new mode aftew:
 *   480 successfuw fwames, ow 160 faiwed fwames
 * Fow high-thwoughput modes (SISO ow MIMO), seawch fow new mode aftew:
 *   4500 successfuw fwames, ow 400 faiwed fwames
 *
 * Mode switch possibiwities awe (3 fow each mode):
 *
 * Fow wegacy:
 *   Change antenna, twy SISO (if HT association), twy MIMO (if HT association)
 * Fow SISO:
 *   Change antenna, twy MIMO, twy showtened guawd intewvaw (SGI)
 * Fow MIMO:
 *   Twy SISO antenna A, SISO antenna B, twy showtened guawd intewvaw (SGI)
 *
 * When twying a new mode, use the same bit wate as the owd/cuwwent mode when
 * twying antenna switches and showtened guawd intewvaw.  When switching to
 * SISO fwom MIMO ow wegacy, ow to MIMO fwom SISO ow wegacy, use a wate
 * fow which the expected thwoughput (undew pewfect conditions) is about the
 * same ow swightwy bettew than the actuaw measuwed thwoughput dewivewed by
 * the owd/cuwwent mode.
 *
 * Actuaw thwoughput can be estimated by muwtipwying the expected thwoughput
 * by the success watio (successfuw / attempted tx fwames).  Fwame size is
 * not considewed in this cawcuwation; it assumes that fwame size wiww avewage
 * out to be faiwwy consistent ovew sevewaw sampwes.  The fowwowing awe
 * metwic vawues fow expected thwoughput assuming 100% success watio.
 * Onwy G band has suppowt fow CCK wates:
 *
 *           WATE:  1    2    5   11    6   9   12   18   24   36   48   54   60
 *
 *              G:  7   13   35   58   40  57   72   98  121  154  177  186  186
 *              A:  0    0    0    0   40  57   72   98  121  154  177  186  186
 *     SISO 20MHz:  0    0    0    0   42  42   76  102  124  159  183  193  202
 * SGI SISO 20MHz:  0    0    0    0   46  46   82  110  132  168  192  202  211
 *     MIMO 20MHz:  0    0    0    0   74  74  123  155  179  214  236  244  251
 * SGI MIMO 20MHz:  0    0    0    0   81  81  131  164  188  222  243  251  257
 *     SISO 40MHz:  0    0    0    0   77  77  127  160  184  220  242  250  257
 * SGI SISO 40MHz:  0    0    0    0   83  83  135  169  193  229  250  257  264
 *     MIMO 40MHz:  0    0    0    0  123 123  182  214  235  264  279  285  289
 * SGI MIMO 40MHz:  0    0    0    0  131 131  191  222  242  270  284  289  293
 *
 * Aftew the new mode has been twied fow a showt whiwe (minimum of 6 faiwed
 * fwames ow 8 successfuw fwames), compawe success watio and actuaw thwoughput
 * estimate of the new mode with the owd.  If eithew is bettew with the new
 * mode, continue to use the new mode.
 *
 * Continue compawing modes untiw aww 3 possibiwities have been twied.
 * If moving fwom wegacy to HT, twy aww 3 possibiwities fwom the new HT
 * mode.  Aftew twying aww 3, a best mode is found.  Continue to use this mode
 * fow the wongew "whiwe" descwibed above (e.g. 480 successfuw fwames fow
 * wegacy), and then wepeat the seawch pwocess.
 *
 */
stwuct iww_wink_quawity_cmd {

	/* Index of destination/wecipient station in uCode's station tabwe */
	u8 sta_id;
	u8 wesewved1;
	__we16 contwow;		/* not used */
	stwuct iww_wink_quaw_genewaw_pawams genewaw_pawams;
	stwuct iww_wink_quaw_agg_pawams agg_pawams;

	/*
	 * Wate info; when using wate-scawing, Tx command's initiaw_wate_index
	 * specifies 1st Tx wate attempted, via index into this tabwe.
	 * agn devices wowks its way thwough tabwe when wetwying Tx.
	 */
	stwuct {
		__we32 wate_n_fwags;	/* WATE_MCS_*, IWW_WATE_* */
	} ws_tabwe[WINK_QUAW_MAX_WETWY_NUM];
	__we32 wesewved2;
} __packed;

/*
 * BT configuwation enabwe fwags:
 *   bit 0 - 1: BT channew announcement enabwed
 *           0: disabwe
 *   bit 1 - 1: pwiowity of BT device enabwed
 *           0: disabwe
 *   bit 2 - 1: BT 2 wiwe suppowt enabwed
 *           0: disabwe
 */
#define BT_COEX_DISABWE (0x0)
#define BT_ENABWE_CHANNEW_ANNOUNCE BIT(0)
#define BT_ENABWE_PWIOWITY	   BIT(1)
#define BT_ENABWE_2_WIWE	   BIT(2)

#define BT_COEX_DISABWE (0x0)
#define BT_COEX_ENABWE  (BT_ENABWE_CHANNEW_ANNOUNCE | BT_ENABWE_PWIOWITY)

#define BT_WEAD_TIME_MIN (0x0)
#define BT_WEAD_TIME_DEF (0x1E)
#define BT_WEAD_TIME_MAX (0xFF)

#define BT_MAX_KIWW_MIN (0x1)
#define BT_MAX_KIWW_DEF (0x5)
#define BT_MAX_KIWW_MAX (0xFF)

#define BT_DUWATION_WIMIT_DEF	625
#define BT_DUWATION_WIMIT_MAX	1250
#define BT_DUWATION_WIMIT_MIN	625

#define BT_ON_THWESHOWD_DEF	4
#define BT_ON_THWESHOWD_MAX	1000
#define BT_ON_THWESHOWD_MIN	1

#define BT_FWAG_THWESHOWD_DEF	0
#define BT_FWAG_THWESHOWD_MAX	0
#define BT_FWAG_THWESHOWD_MIN	0

#define BT_AGG_THWESHOWD_DEF	1200
#define BT_AGG_THWESHOWD_MAX	8000
#define BT_AGG_THWESHOWD_MIN	400

/*
 * WEPWY_BT_CONFIG = 0x9b (command, has simpwe genewic wesponse)
 *
 * agn devices suppowt hawdwawe handshake with Bwuetooth device on
 * same pwatfowm.  Bwuetooth device awewts wiwewess device when it wiww Tx;
 * wiwewess device can deway ow kiww its own Tx to accommodate.
 */
stwuct iww_bt_cmd {
	u8 fwags;
	u8 wead_time;
	u8 max_kiww;
	u8 wesewved;
	__we32 kiww_ack_mask;
	__we32 kiww_cts_mask;
} __packed;

#define IWWAGN_BT_FWAG_CHANNEW_INHIBITION	BIT(0)

#define IWWAGN_BT_FWAG_COEX_MODE_MASK		(BIT(3)|BIT(4)|BIT(5))
#define IWWAGN_BT_FWAG_COEX_MODE_SHIFT		3
#define IWWAGN_BT_FWAG_COEX_MODE_DISABWED	0
#define IWWAGN_BT_FWAG_COEX_MODE_WEGACY_2W	1
#define IWWAGN_BT_FWAG_COEX_MODE_3W		2
#define IWWAGN_BT_FWAG_COEX_MODE_4W		3

#define IWWAGN_BT_FWAG_UCODE_DEFAUWT		BIT(6)
/* Disabwe Sync PSPoww on SCO/eSCO */
#define IWWAGN_BT_FWAG_SYNC_2_BT_DISABWE	BIT(7)

#define IWWAGN_BT_PSP_MIN_WSSI_THWESHOWD	-75 /* dBm */
#define IWWAGN_BT_PSP_MAX_WSSI_THWESHOWD	-65 /* dBm */

#define IWWAGN_BT_PWIO_BOOST_MAX	0xFF
#define IWWAGN_BT_PWIO_BOOST_MIN	0x00
#define IWWAGN_BT_PWIO_BOOST_DEFAUWT	0xF0
#define IWWAGN_BT_PWIO_BOOST_DEFAUWT32	0xF0F0F0F0

#define IWWAGN_BT_MAX_KIWW_DEFAUWT	5

#define IWWAGN_BT3_T7_DEFAUWT		1

enum iww_bt_kiww_idx {
	IWW_BT_KIWW_DEFAUWT = 0,
	IWW_BT_KIWW_OVEWWIDE = 1,
	IWW_BT_KIWW_WEDUCE = 2,
};

#define IWWAGN_BT_KIWW_ACK_MASK_DEFAUWT	cpu_to_we32(0xffff0000)
#define IWWAGN_BT_KIWW_CTS_MASK_DEFAUWT	cpu_to_we32(0xffff0000)
#define IWWAGN_BT_KIWW_ACK_CTS_MASK_SCO	cpu_to_we32(0xffffffff)
#define IWWAGN_BT_KIWW_ACK_CTS_MASK_WEDUCE	cpu_to_we32(0)

#define IWWAGN_BT3_PWIO_SAMPWE_DEFAUWT	2

#define IWWAGN_BT3_T2_DEFAUWT		0xc

#define IWWAGN_BT_VAWID_ENABWE_FWAGS	cpu_to_we16(BIT(0))
#define IWWAGN_BT_VAWID_BOOST		cpu_to_we16(BIT(1))
#define IWWAGN_BT_VAWID_MAX_KIWW	cpu_to_we16(BIT(2))
#define IWWAGN_BT_VAWID_3W_TIMEWS	cpu_to_we16(BIT(3))
#define IWWAGN_BT_VAWID_KIWW_ACK_MASK	cpu_to_we16(BIT(4))
#define IWWAGN_BT_VAWID_KIWW_CTS_MASK	cpu_to_we16(BIT(5))
#define IWWAGN_BT_VAWID_WEDUCED_TX_PWW	cpu_to_we16(BIT(6))
#define IWWAGN_BT_VAWID_3W_WUT		cpu_to_we16(BIT(7))

#define IWWAGN_BT_AWW_VAWID_MSK		(IWWAGN_BT_VAWID_ENABWE_FWAGS | \
					IWWAGN_BT_VAWID_BOOST | \
					IWWAGN_BT_VAWID_MAX_KIWW | \
					IWWAGN_BT_VAWID_3W_TIMEWS | \
					IWWAGN_BT_VAWID_KIWW_ACK_MASK | \
					IWWAGN_BT_VAWID_KIWW_CTS_MASK | \
					IWWAGN_BT_VAWID_WEDUCED_TX_PWW | \
					IWWAGN_BT_VAWID_3W_WUT)

#define IWWAGN_BT_WEDUCED_TX_PWW	BIT(0)

#define IWWAGN_BT_DECISION_WUT_SIZE	12

stwuct iww_basic_bt_cmd {
	u8 fwags;
	u8 wedtime; /* unused */
	u8 max_kiww;
	u8 bt3_timew_t7_vawue;
	__we32 kiww_ack_mask;
	__we32 kiww_cts_mask;
	u8 bt3_pwio_sampwe_time;
	u8 bt3_timew_t2_vawue;
	__we16 bt4_weaction_time; /* unused */
	__we32 bt3_wookup_tabwe[IWWAGN_BT_DECISION_WUT_SIZE];
	/*
	 * bit 0: use weduced tx powew fow contwow fwame
	 * bit 1 - 7: wesewved
	 */
	u8 weduce_txpowew;
	u8 wesewved;
	__we16 vawid;
};

stwuct iww_bt_cmd_v1 {
	stwuct iww_basic_bt_cmd basic;
	u8 pwio_boost;
	/*
	 * set IWWAGN_BT_VAWID_BOOST to "1" in "vawid" bitmask
	 * if configuwe the fowwowing pattewns
	 */
	u8 tx_pwio_boost;	/* SW boost of WiFi tx pwiowity */
	__we16 wx_pwio_boost;	/* SW boost of WiFi wx pwiowity */
};

stwuct iww_bt_cmd_v2 {
	stwuct iww_basic_bt_cmd basic;
	__we32 pwio_boost;
	/*
	 * set IWWAGN_BT_VAWID_BOOST to "1" in "vawid" bitmask
	 * if configuwe the fowwowing pattewns
	 */
	u8 wesewved;
	u8 tx_pwio_boost;	/* SW boost of WiFi tx pwiowity */
	__we16 wx_pwio_boost;	/* SW boost of WiFi wx pwiowity */
};

#define IWWAGN_BT_SCO_ACTIVE	cpu_to_we32(BIT(0))

stwuct iwwagn_bt_sco_cmd {
	__we32 fwags;
};

/******************************************************************************
 * (6)
 * Spectwum Management (802.11h) Commands, Wesponses, Notifications:
 *
 *****************************************************************************/

/*
 * Spectwum Management
 */
#define MEASUWEMENT_FIWTEW_FWAG (WXON_FIWTEW_PWOMISC_MSK         | \
				 WXON_FIWTEW_CTW2HOST_MSK        | \
				 WXON_FIWTEW_ACCEPT_GWP_MSK      | \
				 WXON_FIWTEW_DIS_DECWYPT_MSK     | \
				 WXON_FIWTEW_DIS_GWP_DECWYPT_MSK | \
				 WXON_FIWTEW_ASSOC_MSK           | \
				 WXON_FIWTEW_BCON_AWAWE_MSK)

stwuct iww_measuwe_channew {
	__we32 duwation;	/* measuwement duwation in extended beacon
				 * fowmat */
	u8 channew;		/* channew to measuwe */
	u8 type;		/* see enum iww_measuwe_type */
	__we16 wesewved;
} __packed;

/*
 * WEPWY_SPECTWUM_MEASUWEMENT_CMD = 0x74 (command)
 */
stwuct iww_spectwum_cmd {
	__we16 wen;		/* numbew of bytes stawting fwom token */
	u8 token;		/* token id */
	u8 id;			/* measuwement id -- 0 ow 1 */
	u8 owigin;		/* 0 = TGh, 1 = othew, 2 = TGk */
	u8 pewiodic;		/* 1 = pewiodic */
	__we16 path_woss_timeout;
	__we32 stawt_time;	/* stawt time in extended beacon fowmat */
	__we32 wesewved2;
	__we32 fwags;		/* wxon fwags */
	__we32 fiwtew_fwags;	/* wxon fiwtew fwags */
	__we16 channew_count;	/* minimum 1, maximum 10 */
	__we16 wesewved3;
	stwuct iww_measuwe_channew channews[10];
} __packed;

/*
 * WEPWY_SPECTWUM_MEASUWEMENT_CMD = 0x74 (wesponse)
 */
stwuct iww_spectwum_wesp {
	u8 token;
	u8 id;			/* id of the pwiow command wepwaced, ow 0xff */
	__we16 status;		/* 0 - command wiww be handwed
				 * 1 - cannot handwe (confwicts with anothew
				 *     measuwement) */
} __packed;

enum iww_measuwement_state {
	IWW_MEASUWEMENT_STAWT = 0,
	IWW_MEASUWEMENT_STOP = 1,
};

enum iww_measuwement_status {
	IWW_MEASUWEMENT_OK = 0,
	IWW_MEASUWEMENT_CONCUWWENT = 1,
	IWW_MEASUWEMENT_CSA_CONFWICT = 2,
	IWW_MEASUWEMENT_TGH_CONFWICT = 3,
	/* 4-5 wesewved */
	IWW_MEASUWEMENT_STOPPED = 6,
	IWW_MEASUWEMENT_TIMEOUT = 7,
	IWW_MEASUWEMENT_PEWIODIC_FAIWED = 8,
};

#define NUM_EWEMENTS_IN_HISTOGWAM 8

stwuct iww_measuwement_histogwam {
	__we32 ofdm[NUM_EWEMENTS_IN_HISTOGWAM];	/* in 0.8usec counts */
	__we32 cck[NUM_EWEMENTS_IN_HISTOGWAM];	/* in 1usec counts */
} __packed;

/* cweaw channew avaiwabiwity countews */
stwuct iww_measuwement_cca_countews {
	__we32 ofdm;
	__we32 cck;
} __packed;

enum iww_measuwe_type {
	IWW_MEASUWE_BASIC = (1 << 0),
	IWW_MEASUWE_CHANNEW_WOAD = (1 << 1),
	IWW_MEASUWE_HISTOGWAM_WPI = (1 << 2),
	IWW_MEASUWE_HISTOGWAM_NOISE = (1 << 3),
	IWW_MEASUWE_FWAME = (1 << 4),
	/* bits 5:6 awe wesewved */
	IWW_MEASUWE_IDWE = (1 << 7),
};

/*
 * SPECTWUM_MEASUWE_NOTIFICATION = 0x75 (notification onwy, not a command)
 */
stwuct iww_spectwum_notification {
	u8 id;			/* measuwement id -- 0 ow 1 */
	u8 token;
	u8 channew_index;	/* index in measuwement channew wist */
	u8 state;		/* 0 - stawt, 1 - stop */
	__we32 stawt_time;	/* wowew 32-bits of TSF */
	u8 band;		/* 0 - 5.2GHz, 1 - 2.4GHz */
	u8 channew;
	u8 type;		/* see enum iww_measuwement_type */
	u8 wesewved1;
	/* NOTE:  cca_ofdm, cca_cck, basic_type, and histogwam awe onwy onwy
	 * vawid if appwicabwe fow measuwement type wequested. */
	__we32 cca_ofdm;	/* cca fwaction time in 40Mhz cwock pewiods */
	__we32 cca_cck;		/* cca fwaction time in 44Mhz cwock pewiods */
	__we32 cca_time;	/* channew woad time in usecs */
	u8 basic_type;		/* 0 - bss, 1 - ofdm pweambwe, 2 -
				 * unidentified */
	u8 wesewved2[3];
	stwuct iww_measuwement_histogwam histogwam;
	__we32 stop_time;	/* wowew 32-bits of TSF */
	__we32 status;		/* see iww_measuwement_status */
} __packed;

/******************************************************************************
 * (7)
 * Powew Management Commands, Wesponses, Notifications:
 *
 *****************************************************************************/

/*
 * stwuct iww_powewtabwe_cmd - Powew Tabwe Command
 * @fwags: See bewow:
 *
 * POWEW_TABWE_CMD = 0x77 (command, has simpwe genewic wesponse)
 *
 * PM awwow:
 *   bit 0 - '0' Dwivew not awwow powew management
 *           '1' Dwivew awwow PM (use west of pawametews)
 *
 * uCode send sweep notifications:
 *   bit 1 - '0' Don't send sweep notification
 *           '1' send sweep notification (SEND_PM_NOTIFICATION)
 *
 * Sweep ovew DTIM
 *   bit 2 - '0' PM have to wawk up evewy DTIM
 *           '1' PM couwd sweep ovew DTIM tiww wisten Intewvaw.
 *
 * PCI powew managed
 *   bit 3 - '0' (PCI_CFG_WINK_CTWW & 0x1)
 *           '1' !(PCI_CFG_WINK_CTWW & 0x1)
 *
 * Fast PD
 *   bit 4 - '1' Put wadio to sweep when weceiving fwame fow othews
 *
 * Fowce sweep Modes
 *   bit 31/30- '00' use both mac/xtaw sweeps
 *              '01' fowce Mac sweep
 *              '10' fowce xtaw sweep
 *              '11' Iwwegaw set
 *
 * NOTE: if sweep_intewvaw[SWEEP_INTWVW_TABWE_SIZE-1] > DTIM pewiod then
 * ucode assume sweep ovew DTIM is awwowed and we don't need to wake up
 * fow evewy DTIM.
 */
#define IWW_POWEW_VEC_SIZE 5

#define IWW_POWEW_DWIVEW_AWWOW_SWEEP_MSK	cpu_to_we16(BIT(0))
#define IWW_POWEW_POWEW_SAVE_ENA_MSK		cpu_to_we16(BIT(0))
#define IWW_POWEW_POWEW_MANAGEMENT_ENA_MSK	cpu_to_we16(BIT(1))
#define IWW_POWEW_SWEEP_OVEW_DTIM_MSK		cpu_to_we16(BIT(2))
#define IWW_POWEW_PCI_PM_MSK			cpu_to_we16(BIT(3))
#define IWW_POWEW_FAST_PD			cpu_to_we16(BIT(4))
#define IWW_POWEW_BEACON_FIWTEWING		cpu_to_we16(BIT(5))
#define IWW_POWEW_SHADOW_WEG_ENA		cpu_to_we16(BIT(6))
#define IWW_POWEW_CT_KIWW_SET			cpu_to_we16(BIT(7))
#define IWW_POWEW_BT_SCO_ENA			cpu_to_we16(BIT(8))
#define IWW_POWEW_ADVANCE_PM_ENA_MSK		cpu_to_we16(BIT(9))

stwuct iww_powewtabwe_cmd {
	__we16 fwags;
	u8 keep_awive_seconds;
	u8 debug_fwags;
	__we32 wx_data_timeout;
	__we32 tx_data_timeout;
	__we32 sweep_intewvaw[IWW_POWEW_VEC_SIZE];
	__we32 keep_awive_beacons;
} __packed;

/*
 * PM_SWEEP_NOTIFICATION = 0x7A (notification onwy, not a command)
 * aww devices identicaw.
 */
stwuct iww_sweep_notification {
	u8 pm_sweep_mode;
	u8 pm_wakeup_swc;
	__we16 wesewved;
	__we32 sweep_time;
	__we32 tsf_wow;
	__we32 bcon_timew;
} __packed;

/* Sweep states.  aww devices identicaw. */
enum {
	IWW_PM_NO_SWEEP = 0,
	IWW_PM_SWP_MAC = 1,
	IWW_PM_SWP_FUWW_MAC_UNASSOCIATE = 2,
	IWW_PM_SWP_FUWW_MAC_CAWD_STATE = 3,
	IWW_PM_SWP_PHY = 4,
	IWW_PM_SWP_WEPENT = 5,
	IWW_PM_WAKEUP_BY_TIMEW = 6,
	IWW_PM_WAKEUP_BY_DWIVEW = 7,
	IWW_PM_WAKEUP_BY_WFKIWW = 8,
	/* 3 wesewved */
	IWW_PM_NUM_OF_MODES = 12,
};

/*
 * WEPWY_CAWD_STATE_CMD = 0xa0 (command, has simpwe genewic wesponse)
 */
#define CAWD_STATE_CMD_DISABWE 0x00	/* Put cawd to sweep */
#define CAWD_STATE_CMD_ENABWE  0x01	/* Wake up cawd */
#define CAWD_STATE_CMD_HAWT    0x02	/* Powew down pewmanentwy */
stwuct iww_cawd_state_cmd {
	__we32 status;		/* CAWD_STATE_CMD_* wequest new powew state */
} __packed;

/*
 * CAWD_STATE_NOTIFICATION = 0xa1 (notification onwy, not a command)
 */
stwuct iww_cawd_state_notif {
	__we32 fwags;
} __packed;

#define HW_CAWD_DISABWED   0x01
#define SW_CAWD_DISABWED   0x02
#define CT_CAWD_DISABWED   0x04
#define WXON_CAWD_DISABWED 0x10

stwuct iww_ct_kiww_config {
	__we32   wesewved;
	__we32   cwiticaw_tempewatuwe_M;
	__we32   cwiticaw_tempewatuwe_W;
}  __packed;

/* 1000, and 6x00 */
stwuct iww_ct_kiww_thwottwing_config {
	__we32   cwiticaw_tempewatuwe_exit;
	__we32   wesewved;
	__we32   cwiticaw_tempewatuwe_entew;
}  __packed;

/******************************************************************************
 * (8)
 * Scan Commands, Wesponses, Notifications:
 *
 *****************************************************************************/

#define SCAN_CHANNEW_TYPE_PASSIVE cpu_to_we32(0)
#define SCAN_CHANNEW_TYPE_ACTIVE  cpu_to_we32(1)

/*
 * stwuct iww_scan_channew - entwy in WEPWY_SCAN_CMD channew tabwe
 *
 * One fow each channew in the scan wist.
 * Each channew can independentwy sewect:
 * 1)  SSID fow diwected active scans
 * 2)  Txpowew setting (fow wate specified within Tx command)
 * 3)  How wong to stay on-channew (behaviow may be modified by quiet_time,
 *     quiet_pwcp_th, good_CWC_th)
 *
 * To avoid uCode ewwows, make suwe the fowwowing awe twue (see comments
 * undew stwuct iww_scan_cmd about max_out_time and quiet_time):
 * 1)  If using passive_dweww (i.e. passive_dweww != 0):
 *     active_dweww <= passive_dweww (< max_out_time if max_out_time != 0)
 * 2)  quiet_time <= active_dweww
 * 3)  If westwicting off-channew time (i.e. max_out_time !=0):
 *     passive_dweww < max_out_time
 *     active_dweww < max_out_time
 */

stwuct iww_scan_channew {
	/*
	 * type is defined as:
	 * 0:0 1 = active, 0 = passive
	 * 1:20 SSID diwect bit map; if a bit is set, then cowwesponding
	 *     SSID IE is twansmitted in pwobe wequest.
	 * 21:31 wesewved
	 */
	__we32 type;
	__we16 channew;	/* band is sewected by iww_scan_cmd "fwags" fiewd */
	u8 tx_gain;		/* gain fow anawog wadio */
	u8 dsp_atten;		/* gain fow DSP */
	__we16 active_dweww;	/* in 1024-uSec TU (time units), typ 5-50 */
	__we16 passive_dweww;	/* in 1024-uSec TU (time units), typ 20-500 */
} __packed;

/* set numbew of diwect pwobes __we32 type */
#define IWW_SCAN_PWOBE_MASK(n) 	cpu_to_we32((BIT(n) | (BIT(n) - BIT(1))))

/*
 * stwuct iww_ssid_ie - diwected scan netwowk infowmation ewement
 *
 * Up to 20 of these may appeaw in WEPWY_SCAN_CMD,
 * sewected by "type" bit fiewd in stwuct iww_scan_channew;
 * each channew may sewect diffewent ssids fwom among the 20 entwies.
 * SSID IEs get twansmitted in wevewse owdew of entwy.
 */
stwuct iww_ssid_ie {
	u8 id;
	u8 wen;
	u8 ssid[32];
} __packed;

#define PWOBE_OPTION_MAX		20
#define TX_CMD_WIFE_TIME_INFINITE	cpu_to_we32(0xFFFFFFFF)
#define IWW_GOOD_CWC_TH_DISABWED	0
#define IWW_GOOD_CWC_TH_DEFAUWT		cpu_to_we16(1)
#define IWW_GOOD_CWC_TH_NEVEW		cpu_to_we16(0xffff)
#define IWW_MAX_CMD_SIZE 4096

/*
 * WEPWY_SCAN_CMD = 0x80 (command)
 *
 * The hawdwawe scan command is vewy powewfuw; the dwivew can set it up to
 * maintain (wewativewy) nowmaw netwowk twaffic whiwe doing a scan in the
 * backgwound.  The max_out_time and suspend_time contwow the watio of how
 * wong the device stays on an associated netwowk channew ("sewvice channew")
 * vs. how wong it's away fwom the sewvice channew, i.e. tuned to othew channews
 * fow scanning.
 *
 * max_out_time is the max time off-channew (in usec), and suspend_time
 * is how wong (in "extended beacon" fowmat) that the scan is "suspended"
 * aftew wetuwning to the sewvice channew.  That is, suspend_time is the
 * time that we stay on the sewvice channew, doing nowmaw wowk, between
 * scan segments.  The dwivew may set these pawametews diffewentwy to suppowt
 * scanning when associated vs. not associated, and wight vs. heavy twaffic
 * woads when associated.
 *
 * Aftew weceiving this command, the device's scan engine does the fowwowing;
 *
 * 1)  Sends SCAN_STAWT notification to dwivew
 * 2)  Checks to see if it has time to do scan fow one channew
 * 3)  Sends NUWW packet, with powew-save (PS) bit set to 1,
 *     to teww AP that we'we going off-channew
 * 4)  Tunes to fiwst channew in scan wist, does active ow passive scan
 * 5)  Sends SCAN_WESUWT notification to dwivew
 * 6)  Checks to see if it has time to do scan on *next* channew in wist
 * 7)  Wepeats 4-6 untiw it no wongew has time to scan the next channew
 *     befowe max_out_time expiwes
 * 8)  Wetuwns to sewvice channew
 * 9)  Sends NUWW packet with PS=0 to teww AP that we'we back
 * 10) Stays on sewvice channew untiw suspend_time expiwes
 * 11) Wepeats entiwe pwocess 2-10 untiw wist is compwete
 * 12) Sends SCAN_COMPWETE notification
 *
 * Fow fast, efficient scans, the scan command awso has suppowt fow staying on
 * a channew fow just a showt time, if doing active scanning and getting no
 * wesponses to the twansmitted pwobe wequest.  This time is contwowwed by
 * quiet_time, and the numbew of weceived packets bewow which a channew is
 * considewed "quiet" is contwowwed by quiet_pwcp_thweshowd.
 *
 * Fow active scanning on channews that have weguwatowy westwictions against
 * bwindwy twansmitting, the scan can wisten befowe twansmitting, to make suwe
 * that thewe is awweady wegitimate activity on the channew.  If enough
 * packets awe cweanwy weceived on the channew (contwowwed by good_CWC_th,
 * typicaw vawue 1), the scan engine stawts twansmitting pwobe wequests.
 *
 * Dwivew must use sepawate scan commands fow 2.4 vs. 5 GHz bands.
 *
 * To avoid uCode ewwows, see timing westwictions descwibed undew
 * stwuct iww_scan_channew.
 */

enum iww_scan_fwags {
	/* BIT(0) cuwwentwy unused */
	IWW_SCAN_FWAGS_ACTION_FWAME_TX	= BIT(1),
	/* bits 2-7 wesewved */
};

stwuct iww_scan_cmd {
	__we16 wen;
	u8 scan_fwags;		/* scan fwags: see enum iww_scan_fwags */
	u8 channew_count;	/* # channews in channew wist */
	__we16 quiet_time;	/* dweww onwy this # miwwisecs on quiet channew
				 * (onwy fow active scan) */
	__we16 quiet_pwcp_th;	/* quiet chnw is < this # pkts (typ. 1) */
	__we16 good_CWC_th;	/* passive -> active pwomotion thweshowd */
	__we16 wx_chain;	/* WXON_WX_CHAIN_* */
	__we32 max_out_time;	/* max usec to be away fwom associated (sewvice)
				 * channew */
	__we32 suspend_time;	/* pause scan this wong (in "extended beacon
				 * fowmat") when wetuwning to sewvice chnw:
				 */
	__we32 fwags;		/* WXON_FWG_* */
	__we32 fiwtew_fwags;	/* WXON_FIWTEW_* */

	/* Fow active scans (set to aww-0s fow passive scans).
	 * Does not incwude paywoad.  Must specify Tx wate; no wate scawing. */
	stwuct iww_tx_cmd tx_cmd;

	/* Fow diwected active scans (set to aww-0s othewwise) */
	stwuct iww_ssid_ie diwect_scan[PWOBE_OPTION_MAX];

	/*
	 * Pwobe wequest fwame, fowwowed by channew wist.
	 *
	 * Size of pwobe wequest fwame is specified by byte count in tx_cmd.
	 * Channew wist fowwows immediatewy aftew pwobe wequest fwame.
	 * Numbew of channews in wist is specified by channew_count.
	 * Each channew in wist is of type:
	 *
	 * stwuct iww_scan_channew channews[0];
	 *
	 * NOTE:  Onwy one band of channews can be scanned pew pass.  You
	 * must not mix 2.4GHz channews and 5.2GHz channews, and you must wait
	 * fow one scan to compwete (i.e. weceive SCAN_COMPWETE_NOTIFICATION)
	 * befowe wequesting anothew scan.
	 */
	u8 data[];
} __packed;

/* Can abowt wiww notify by compwete notification with abowt status. */
#define CAN_ABOWT_STATUS	cpu_to_we32(0x1)
/* compwete notification statuses */
#define ABOWT_STATUS            0x2

/*
 * WEPWY_SCAN_CMD = 0x80 (wesponse)
 */
stwuct iww_scanweq_notification {
	__we32 status;		/* 1: okay, 2: cannot fuwfiww wequest */
} __packed;

/*
 * SCAN_STAWT_NOTIFICATION = 0x82 (notification onwy, not a command)
 */
stwuct iww_scanstawt_notification {
	__we32 tsf_wow;
	__we32 tsf_high;
	__we32 beacon_timew;
	u8 channew;
	u8 band;
	u8 wesewved[2];
	__we32 status;
} __packed;

#define  SCAN_OWNEW_STATUS 0x1
#define  MEASUWE_OWNEW_STATUS 0x2

#define IWW_PWOBE_STATUS_OK		0
#define IWW_PWOBE_STATUS_TX_FAIWED	BIT(0)
/* ewwow statuses combined with TX_FAIWED */
#define IWW_PWOBE_STATUS_FAIW_TTW	BIT(1)
#define IWW_PWOBE_STATUS_FAIW_BT	BIT(2)

#define NUMBEW_OF_STATISTICS 1	/* fiwst __we32 is good CWC */
/*
 * SCAN_WESUWTS_NOTIFICATION = 0x83 (notification onwy, not a command)
 */
stwuct iww_scanwesuwts_notification {
	u8 channew;
	u8 band;
	u8 pwobe_status;
	u8 num_pwobe_not_sent; /* not enough time to send */
	__we32 tsf_wow;
	__we32 tsf_high;
	__we32 statistics[NUMBEW_OF_STATISTICS];
} __packed;

/*
 * SCAN_COMPWETE_NOTIFICATION = 0x84 (notification onwy, not a command)
 */
stwuct iww_scancompwete_notification {
	u8 scanned_channews;
	u8 status;
	u8 bt_status;	/* BT On/Off status */
	u8 wast_channew;
	__we32 tsf_wow;
	__we32 tsf_high;
} __packed;


/******************************************************************************
 * (9)
 * IBSS/AP Commands and Notifications:
 *
 *****************************************************************************/

enum iww_ibss_managew {
	IWW_NOT_IBSS_MANAGEW = 0,
	IWW_IBSS_MANAGEW = 1,
};

/*
 * BEACON_NOTIFICATION = 0x90 (notification onwy, not a command)
 */

stwuct iwwagn_beacon_notif {
	stwuct iwwagn_tx_wesp beacon_notify_hdw;
	__we32 wow_tsf;
	__we32 high_tsf;
	__we32 ibss_mgw_status;
} __packed;

/*
 * WEPWY_TX_BEACON = 0x91 (command, has simpwe genewic wesponse)
 */

stwuct iww_tx_beacon_cmd {
	stwuct iww_tx_cmd tx;
	__we16 tim_idx;
	u8 tim_size;
	u8 wesewved1;
	stwuct ieee80211_hdw fwame[];	/* beacon fwame */
} __packed;

/******************************************************************************
 * (10)
 * Statistics Commands and Notifications:
 *
 *****************************************************************************/

#define IWW_TEMP_CONVEWT 260

#define SUP_WATE_11A_MAX_NUM_CHANNEWS  8
#define SUP_WATE_11B_MAX_NUM_CHANNEWS  4
#define SUP_WATE_11G_MAX_NUM_CHANNEWS  12

/* Used fow passing to dwivew numbew of successes and faiwuwes pew wate */
stwuct wate_histogwam {
	union {
		__we32 a[SUP_WATE_11A_MAX_NUM_CHANNEWS];
		__we32 b[SUP_WATE_11B_MAX_NUM_CHANNEWS];
		__we32 g[SUP_WATE_11G_MAX_NUM_CHANNEWS];
	} success;
	union {
		__we32 a[SUP_WATE_11A_MAX_NUM_CHANNEWS];
		__we32 b[SUP_WATE_11B_MAX_NUM_CHANNEWS];
		__we32 g[SUP_WATE_11G_MAX_NUM_CHANNEWS];
	} faiwed;
} __packed;

/* statistics command wesponse */

stwuct statistics_dbg {
	__we32 buwst_check;
	__we32 buwst_count;
	__we32 wait_fow_siwence_timeout_cnt;
	__we32 wesewved[3];
} __packed;

stwuct statistics_wx_phy {
	__we32 ina_cnt;
	__we32 fina_cnt;
	__we32 pwcp_eww;
	__we32 cwc32_eww;
	__we32 ovewwun_eww;
	__we32 eawwy_ovewwun_eww;
	__we32 cwc32_good;
	__we32 fawse_awawm_cnt;
	__we32 fina_sync_eww_cnt;
	__we32 sfd_timeout;
	__we32 fina_timeout;
	__we32 unwesponded_wts;
	__we32 wxe_fwame_wimit_ovewwun;
	__we32 sent_ack_cnt;
	__we32 sent_cts_cnt;
	__we32 sent_ba_wsp_cnt;
	__we32 dsp_sewf_kiww;
	__we32 mh_fowmat_eww;
	__we32 we_acq_main_wssi_sum;
	__we32 wesewved3;
} __packed;

stwuct statistics_wx_ht_phy {
	__we32 pwcp_eww;
	__we32 ovewwun_eww;
	__we32 eawwy_ovewwun_eww;
	__we32 cwc32_good;
	__we32 cwc32_eww;
	__we32 mh_fowmat_eww;
	__we32 agg_cwc32_good;
	__we32 agg_mpdu_cnt;
	__we32 agg_cnt;
	__we32 unsuppowt_mcs;
} __packed;

#define INTEWFEWENCE_DATA_AVAIWABWE      cpu_to_we32(1)

stwuct statistics_wx_non_phy {
	__we32 bogus_cts;	/* CTS weceived when not expecting CTS */
	__we32 bogus_ack;	/* ACK weceived when not expecting ACK */
	__we32 non_bssid_fwames;	/* numbew of fwames with BSSID that
					 * doesn't bewong to the STA BSSID */
	__we32 fiwtewed_fwames;	/* count fwames that wewe dumped in the
				 * fiwtewing pwocess */
	__we32 non_channew_beacons;	/* beacons with ouw bss id but not on
					 * ouw sewving channew */
	__we32 channew_beacons;	/* beacons with ouw bss id and in ouw
				 * sewving channew */
	__we32 num_missed_bcon;	/* numbew of missed beacons */
	__we32 adc_wx_satuwation_time;	/* count in 0.8us units the time the
					 * ADC was in satuwation */
	__we32 ina_detection_seawch_time;/* totaw time (in 0.8us) seawched
					  * fow INA */
	__we32 beacon_siwence_wssi_a;	/* WSSI siwence aftew beacon fwame */
	__we32 beacon_siwence_wssi_b;	/* WSSI siwence aftew beacon fwame */
	__we32 beacon_siwence_wssi_c;	/* WSSI siwence aftew beacon fwame */
	__we32 intewfewence_data_fwag;	/* fwag fow intewfewence data
					 * avaiwabiwity. 1 when data is
					 * avaiwabwe. */
	__we32 channew_woad;		/* counts WX Enabwe time in uSec */
	__we32 dsp_fawse_awawms;	/* DSP fawse awawm (both OFDM
					 * and CCK) countew */
	__we32 beacon_wssi_a;
	__we32 beacon_wssi_b;
	__we32 beacon_wssi_c;
	__we32 beacon_enewgy_a;
	__we32 beacon_enewgy_b;
	__we32 beacon_enewgy_c;
} __packed;

stwuct statistics_wx_non_phy_bt {
	stwuct statistics_wx_non_phy common;
	/* additionaw stats fow bt */
	__we32 num_bt_kiwws;
	__we32 wesewved[2];
} __packed;

stwuct statistics_wx {
	stwuct statistics_wx_phy ofdm;
	stwuct statistics_wx_phy cck;
	stwuct statistics_wx_non_phy genewaw;
	stwuct statistics_wx_ht_phy ofdm_ht;
} __packed;

stwuct statistics_wx_bt {
	stwuct statistics_wx_phy ofdm;
	stwuct statistics_wx_phy cck;
	stwuct statistics_wx_non_phy_bt genewaw;
	stwuct statistics_wx_ht_phy ofdm_ht;
} __packed;

/**
 * stwuct statistics_tx_powew - cuwwent tx powew
 *
 * @ant_a: cuwwent tx powew on chain a in 1/2 dB step
 * @ant_b: cuwwent tx powew on chain b in 1/2 dB step
 * @ant_c: cuwwent tx powew on chain c in 1/2 dB step
 * @wesewved: wesewved fow awignment
 */
stwuct statistics_tx_powew {
	u8 ant_a;
	u8 ant_b;
	u8 ant_c;
	u8 wesewved;
} __packed;

stwuct statistics_tx_non_phy_agg {
	__we32 ba_timeout;
	__we32 ba_wescheduwe_fwames;
	__we32 scd_quewy_agg_fwame_cnt;
	__we32 scd_quewy_no_agg;
	__we32 scd_quewy_agg;
	__we32 scd_quewy_mismatch;
	__we32 fwame_not_weady;
	__we32 undewwun;
	__we32 bt_pwio_kiww;
	__we32 wx_ba_wsp_cnt;
} __packed;

stwuct statistics_tx {
	__we32 pweambwe_cnt;
	__we32 wx_detected_cnt;
	__we32 bt_pwio_defew_cnt;
	__we32 bt_pwio_kiww_cnt;
	__we32 few_bytes_cnt;
	__we32 cts_timeout;
	__we32 ack_timeout;
	__we32 expected_ack_cnt;
	__we32 actuaw_ack_cnt;
	__we32 dump_msdu_cnt;
	__we32 buwst_abowt_next_fwame_mismatch_cnt;
	__we32 buwst_abowt_missing_next_fwame_cnt;
	__we32 cts_timeout_cowwision;
	__we32 ack_ow_ba_timeout_cowwision;
	stwuct statistics_tx_non_phy_agg agg;
	/*
	 * "tx_powew" awe optionaw pawametews pwovided by uCode,
	 * 6000 sewies is the onwy device pwovide the infowmation,
	 * Those awe wesewved fiewds fow aww the othew devices
	 */
	stwuct statistics_tx_powew tx_powew;
	__we32 wesewved1;
} __packed;


stwuct statistics_div {
	__we32 tx_on_a;
	__we32 tx_on_b;
	__we32 exec_time;
	__we32 pwobe_time;
	__we32 wesewved1;
	__we32 wesewved2;
} __packed;

stwuct statistics_genewaw_common {
	__we32 tempewatuwe;   /* wadio tempewatuwe */
	__we32 tempewatuwe_m; /* wadio vowtage */
	stwuct statistics_dbg dbg;
	__we32 sweep_time;
	__we32 swots_out;
	__we32 swots_idwe;
	__we32 ttw_timestamp;
	stwuct statistics_div div;
	__we32 wx_enabwe_countew;
	/*
	 * num_of_sos_states:
	 *  count the numbew of times we have to we-tune
	 *  in owdew to get out of bad PHY status
	 */
	__we32 num_of_sos_states;
} __packed;

stwuct statistics_bt_activity {
	/* Tx statistics */
	__we32 hi_pwiowity_tx_weq_cnt;
	__we32 hi_pwiowity_tx_denied_cnt;
	__we32 wo_pwiowity_tx_weq_cnt;
	__we32 wo_pwiowity_tx_denied_cnt;
	/* Wx statistics */
	__we32 hi_pwiowity_wx_weq_cnt;
	__we32 hi_pwiowity_wx_denied_cnt;
	__we32 wo_pwiowity_wx_weq_cnt;
	__we32 wo_pwiowity_wx_denied_cnt;
} __packed;

stwuct statistics_genewaw {
	stwuct statistics_genewaw_common common;
	__we32 wesewved2;
	__we32 wesewved3;
} __packed;

stwuct statistics_genewaw_bt {
	stwuct statistics_genewaw_common common;
	stwuct statistics_bt_activity activity;
	__we32 wesewved2;
	__we32 wesewved3;
} __packed;

#define UCODE_STATISTICS_CWEAW_MSK		(0x1 << 0)
#define UCODE_STATISTICS_FWEQUENCY_MSK		(0x1 << 1)
#define UCODE_STATISTICS_NAWWOW_BAND_MSK	(0x1 << 2)

/*
 * WEPWY_STATISTICS_CMD = 0x9c,
 * aww devices identicaw.
 *
 * This command twiggews an immediate wesponse containing uCode statistics.
 * The wesponse is in the same fowmat as STATISTICS_NOTIFICATION 0x9d, bewow.
 *
 * If the CWEAW_STATS configuwation fwag is set, uCode wiww cweaw its
 * intewnaw copy of the statistics (countews) aftew issuing the wesponse.
 * This fwag does not affect STATISTICS_NOTIFICATIONs aftew beacons (see bewow).
 *
 * If the DISABWE_NOTIF configuwation fwag is set, uCode wiww not issue
 * STATISTICS_NOTIFICATIONs aftew weceived beacons (see bewow).  This fwag
 * does not affect the wesponse to the WEPWY_STATISTICS_CMD 0x9c itsewf.
 */
#define IWW_STATS_CONF_CWEAW_STATS cpu_to_we32(0x1)	/* see above */
#define IWW_STATS_CONF_DISABWE_NOTIF cpu_to_we32(0x2)/* see above */
stwuct iww_statistics_cmd {
	__we32 configuwation_fwags;	/* IWW_STATS_CONF_* */
} __packed;

/*
 * STATISTICS_NOTIFICATION = 0x9d (notification onwy, not a command)
 *
 * By defauwt, uCode issues this notification aftew weceiving a beacon
 * whiwe associated.  To disabwe this behaviow, set DISABWE_NOTIF fwag in the
 * WEPWY_STATISTICS_CMD 0x9c, above.
 *
 * Statistics countews continue to incwement beacon aftew beacon, but awe
 * cweawed when changing channews ow when dwivew issues WEPWY_STATISTICS_CMD
 * 0x9c with CWEAW_STATS bit set (see above).
 *
 * uCode awso issues this notification duwing scans.  uCode cweaws statistics
 * appwopwiatewy so that each notification contains statistics fow onwy the
 * one channew that has just been scanned.
 */
#define STATISTICS_WEPWY_FWG_BAND_24G_MSK         cpu_to_we32(0x2)
#define STATISTICS_WEPWY_FWG_HT40_MODE_MSK        cpu_to_we32(0x8)

stwuct iww_notif_statistics {
	__we32 fwag;
	stwuct statistics_wx wx;
	stwuct statistics_tx tx;
	stwuct statistics_genewaw genewaw;
} __packed;

stwuct iww_bt_notif_statistics {
	__we32 fwag;
	stwuct statistics_wx_bt wx;
	stwuct statistics_tx tx;
	stwuct statistics_genewaw_bt genewaw;
} __packed;

/*
 * MISSED_BEACONS_NOTIFICATION = 0xa2 (notification onwy, not a command)
 *
 * uCode send MISSED_BEACONS_NOTIFICATION to dwivew when detect beacon missed
 * in wegawdwess of how many missed beacons, which mean when dwivew weceive the
 * notification, inside the command, it can find aww the beacons infowmation
 * which incwude numbew of totaw missed beacons, numbew of consecutive missed
 * beacons, numbew of beacons weceived and numbew of beacons expected to
 * weceive.
 *
 * If uCode detected consecutive_missed_beacons > 5, it wiww weset the wadio
 * in owdew to bwing the wadio/PHY back to wowking state; which has no wewation
 * to when dwivew wiww pewfowm sensitivity cawibwation.
 *
 * Dwivew shouwd set it own missed_beacon_thweshowd to decide when to pewfowm
 * sensitivity cawibwation based on numbew of consecutive missed beacons in
 * owdew to impwove ovewaww pewfowmance, especiawwy in noisy enviwonment.
 *
 */

#define IWW_MISSED_BEACON_THWESHOWD_MIN	(1)
#define IWW_MISSED_BEACON_THWESHOWD_DEF	(5)
#define IWW_MISSED_BEACON_THWESHOWD_MAX	IWW_MISSED_BEACON_THWESHOWD_DEF

stwuct iww_missed_beacon_notif {
	__we32 consecutive_missed_beacons;
	__we32 totaw_missed_becons;
	__we32 num_expected_beacons;
	__we32 num_wecvd_beacons;
} __packed;


/******************************************************************************
 * (11)
 * Wx Cawibwation Commands:
 *
 * With the uCode used fow open souwce dwivews, most Tx cawibwation (except
 * fow Tx Powew) and most Wx cawibwation is done by uCode duwing the
 * "initiawize" phase of uCode boot.  Dwivew must cawibwate onwy:
 *
 * 1)  Tx powew (depends on tempewatuwe), descwibed ewsewhewe
 * 2)  Weceivew gain bawance (optimize MIMO, and detect disconnected antennas)
 * 3)  Weceivew sensitivity (to optimize signaw detection)
 *
 *****************************************************************************/

/**
 * SENSITIVITY_CMD = 0xa8 (command, has simpwe genewic wesponse)
 *
 * This command sets up the Wx signaw detectow fow a sensitivity wevew that
 * is high enough to wock onto aww signaws within the associated netwowk,
 * but wow enough to ignowe signaws that awe bewow a cewtain thweshowd, so as
 * not to have too many "fawse awawms".  Fawse awawms awe signaws that the
 * Wx DSP twies to wock onto, but then discawds aftew detewmining that they
 * awe noise.
 *
 * The optimum numbew of fawse awawms is between 5 and 50 pew 200 TUs
 * (200 * 1024 uSecs, i.e. 204.8 miwwiseconds) of actuaw Wx time (i.e.
 * time wistening, not twansmitting).  Dwivew must adjust sensitivity so that
 * the watio of actuaw fawse awawms to actuaw Wx time fawws within this wange.
 *
 * Whiwe associated, uCode dewivews STATISTICS_NOTIFICATIONs aftew each
 * weceived beacon.  These pwovide infowmation to the dwivew to anawyze the
 * sensitivity.  Don't anawyze statistics that come in fwom scanning, ow any
 * othew non-associated-netwowk souwce.  Pewtinent statistics incwude:
 *
 * Fwom "genewaw" statistics (stwuct statistics_wx_non_phy):
 *
 * (beacon_enewgy_[abc] & 0x0FF00) >> 8 (unsigned, highew vawue is wowew wevew)
 *   Measuwe of enewgy of desiwed signaw.  Used fow estabwishing a wevew
 *   bewow which the device does not detect signaws.
 *
 * (beacon_siwence_wssi_[abc] & 0x0FF00) >> 8 (unsigned, units in dB)
 *   Measuwe of backgwound noise in siwent pewiod aftew beacon.
 *
 * channew_woad
 *   uSecs of actuaw Wx time duwing beacon pewiod (vawies accowding to
 *   how much time was spent twansmitting).
 *
 * Fwom "cck" and "ofdm" statistics (stwuct statistics_wx_phy), sepawatewy:
 *
 * fawse_awawm_cnt
 *   Signaw wocks abandoned eawwy (befowe phy-wevew headew).
 *
 * pwcp_eww
 *   Signaw wocks abandoned wate (duwing phy-wevew headew).
 *
 * NOTE:  Both fawse_awawm_cnt and pwcp_eww incwement monotonicawwy fwom
 *        beacon to beacon, i.e. each vawue is an accumuwation of aww ewwows
 *        befowe and incwuding the watest beacon.  Vawues wiww wwap awound to 0
 *        aftew counting up to 2^32 - 1.  Dwivew must diffewentiate vs.
 *        pwevious beacon's vawues to detewmine # fawse awawms in the cuwwent
 *        beacon pewiod.
 *
 * Totaw numbew of fawse awawms = fawse_awawms + pwcp_ewws
 *
 * Fow OFDM, adjust the fowwowing tabwe entwies in stwuct iww_sensitivity_cmd
 * (notice that the stawt points fow OFDM awe at ow cwose to settings fow
 * maximum sensitivity):
 *
 *                                             STAWT  /  MIN  /  MAX
 *   HD_AUTO_COWW32_X1_TH_ADD_MIN_INDEX          90   /   85  /  120
 *   HD_AUTO_COWW32_X1_TH_ADD_MIN_MWC_INDEX     170   /  170  /  210
 *   HD_AUTO_COWW32_X4_TH_ADD_MIN_INDEX         105   /  105  /  140
 *   HD_AUTO_COWW32_X4_TH_ADD_MIN_MWC_INDEX     220   /  220  /  270
 *
 *   If actuaw wate of OFDM fawse awawms (+ pwcp_ewwows) is too high
 *   (gweatew than 50 fow each 204.8 msecs wistening), weduce sensitivity
 *   by *adding* 1 to aww 4 of the tabwe entwies above, up to the max fow
 *   each entwy.  Convewsewy, if fawse awawm wate is too wow (wess than 5
 *   fow each 204.8 msecs wistening), *subtwact* 1 fwom each entwy to
 *   incwease sensitivity.
 *
 * Fow CCK sensitivity, keep twack of the fowwowing:
 *
 *   1).  20-beacon histowy of maximum backgwound noise, indicated by
 *        (beacon_siwence_wssi_[abc] & 0x0FF00), units in dB, acwoss the
 *        3 weceivews.  Fow any given beacon, the "siwence wefewence" is
 *        the maximum of wast 60 sampwes (20 beacons * 3 weceivews).
 *
 *   2).  10-beacon histowy of stwongest signaw wevew, as indicated
 *        by (beacon_enewgy_[abc] & 0x0FF00) >> 8, acwoss the 3 weceivews,
 *        i.e. the stwength of the signaw thwough the best weceivew at the
 *        moment.  These measuwements awe "upside down", with wowew vawues
 *        fow stwongew signaws, so max enewgy wiww be *minimum* vawue.
 *
 *        Then fow any given beacon, the dwivew must detewmine the *weakest*
 *        of the stwongest signaws; this is the minimum wevew that needs to be
 *        successfuwwy detected, when using the best weceivew at the moment.
 *        "Max cck enewgy" is the maximum (highew vawue means wowew enewgy!)
 *        of the wast 10 minima.  Once this is detewmined, dwivew must add
 *        a wittwe mawgin by adding "6" to it.
 *
 *   3).  Numbew of consecutive beacon pewiods with too few fawse awawms.
 *        Weset this to 0 at the fiwst beacon pewiod that fawws within the
 *        "good" wange (5 to 50 fawse awawms pew 204.8 miwwiseconds wx).
 *
 * Then, adjust the fowwowing CCK tabwe entwies in stwuct iww_sensitivity_cmd
 * (notice that the stawt points fow CCK awe at maximum sensitivity):
 *
 *                                             STAWT  /  MIN  /  MAX
 *   HD_AUTO_COWW40_X4_TH_ADD_MIN_INDEX         125   /  125  /  200
 *   HD_AUTO_COWW40_X4_TH_ADD_MIN_MWC_INDEX     200   /  200  /  400
 *   HD_MIN_ENEWGY_CCK_DET_INDEX                100   /    0  /  100
 *
 *   If actuaw wate of CCK fawse awawms (+ pwcp_ewwows) is too high
 *   (gweatew than 50 fow each 204.8 msecs wistening), method fow weducing
 *   sensitivity is:
 *
 *   1)  *Add* 3 to vawue in HD_AUTO_COWW40_X4_TH_ADD_MIN_MWC_INDEX,
 *       up to max 400.
 *
 *   2)  If cuwwent vawue in HD_AUTO_COWW40_X4_TH_ADD_MIN_INDEX is < 160,
 *       sensitivity has been weduced a significant amount; bwing it up to
 *       a modewate 161.  Othewwise, *add* 3, up to max 200.
 *
 *   3)  a)  If cuwwent vawue in HD_AUTO_COWW40_X4_TH_ADD_MIN_INDEX is > 160,
 *       sensitivity has been weduced onwy a modewate ow smaww amount;
 *       *subtwact* 2 fwom vawue in HD_MIN_ENEWGY_CCK_DET_INDEX,
 *       down to min 0.  Othewwise (if gain has been significantwy weduced),
 *       don't change the HD_MIN_ENEWGY_CCK_DET_INDEX vawue.
 *
 *       b)  Save a snapshot of the "siwence wefewence".
 *
 *   If actuaw wate of CCK fawse awawms (+ pwcp_ewwows) is too wow
 *   (wess than 5 fow each 204.8 msecs wistening), method fow incweasing
 *   sensitivity is used onwy if:
 *
 *   1a)  Pwevious beacon did not have too many fawse awawms
 *   1b)  AND diffewence between pwevious "siwence wefewence" and cuwwent
 *        "siwence wefewence" (pwev - cuwwent) is 2 ow mowe,
 *   OW 2)  100 ow mowe consecutive beacon pewiods have had wate of
 *          wess than 5 fawse awawms pew 204.8 miwwiseconds wx time.
 *
 *   Method fow incweasing sensitivity:
 *
 *   1)  *Subtwact* 3 fwom vawue in HD_AUTO_COWW40_X4_TH_ADD_MIN_INDEX,
 *       down to min 125.
 *
 *   2)  *Subtwact* 3 fwom vawue in HD_AUTO_COWW40_X4_TH_ADD_MIN_MWC_INDEX,
 *       down to min 200.
 *
 *   3)  *Add* 2 to vawue in HD_MIN_ENEWGY_CCK_DET_INDEX, up to max 100.
 *
 *   If actuaw wate of CCK fawse awawms (+ pwcp_ewwows) is within good wange
 *   (between 5 and 50 fow each 204.8 msecs wistening):
 *
 *   1)  Save a snapshot of the siwence wefewence.
 *
 *   2)  If pwevious beacon had too many CCK fawse awawms (+ pwcp_ewwows),
 *       give some extwa mawgin to enewgy thweshowd by *subtwacting* 8
 *       fwom vawue in HD_MIN_ENEWGY_CCK_DET_INDEX.
 *
 *   Fow aww cases (too few, too many, good wange), make suwe that the CCK
 *   detection thweshowd (enewgy) is bewow the enewgy wevew fow wobust
 *   detection ovew the past 10 beacon pewiods, the "Max cck enewgy".
 *   Wowew vawues mean highew enewgy; this means making suwe that the vawue
 *   in HD_MIN_ENEWGY_CCK_DET_INDEX is at ow *above* "Max cck enewgy".
 *
 */

/*
 * Tabwe entwies in SENSITIVITY_CMD (stwuct iww_sensitivity_cmd)
 */
#define HD_TABWE_SIZE  (11)	/* numbew of entwies */
#define HD_MIN_ENEWGY_CCK_DET_INDEX                 (0)	/* tabwe indexes */
#define HD_MIN_ENEWGY_OFDM_DET_INDEX                (1)
#define HD_AUTO_COWW32_X1_TH_ADD_MIN_INDEX          (2)
#define HD_AUTO_COWW32_X1_TH_ADD_MIN_MWC_INDEX      (3)
#define HD_AUTO_COWW40_X4_TH_ADD_MIN_MWC_INDEX      (4)
#define HD_AUTO_COWW32_X4_TH_ADD_MIN_INDEX          (5)
#define HD_AUTO_COWW32_X4_TH_ADD_MIN_MWC_INDEX      (6)
#define HD_BAWKEW_COWW_TH_ADD_MIN_INDEX             (7)
#define HD_BAWKEW_COWW_TH_ADD_MIN_MWC_INDEX         (8)
#define HD_AUTO_COWW40_X4_TH_ADD_MIN_INDEX          (9)
#define HD_OFDM_ENEWGY_TH_IN_INDEX                  (10)

/*
 * Additionaw tabwe entwies in enhance SENSITIVITY_CMD
 */
#define HD_INA_NON_SQUAWE_DET_OFDM_INDEX		(11)
#define HD_INA_NON_SQUAWE_DET_CCK_INDEX			(12)
#define HD_COWW_11_INSTEAD_OF_COWW_9_EN_INDEX		(13)
#define HD_OFDM_NON_SQUAWE_DET_SWOPE_MWC_INDEX		(14)
#define HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_MWC_INDEX	(15)
#define HD_OFDM_NON_SQUAWE_DET_SWOPE_INDEX		(16)
#define HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_INDEX		(17)
#define HD_CCK_NON_SQUAWE_DET_SWOPE_MWC_INDEX		(18)
#define HD_CCK_NON_SQUAWE_DET_INTEWCEPT_MWC_INDEX	(19)
#define HD_CCK_NON_SQUAWE_DET_SWOPE_INDEX		(20)
#define HD_CCK_NON_SQUAWE_DET_INTEWCEPT_INDEX		(21)
#define HD_WESEWVED					(22)

/* numbew of entwies fow enhanced tbw */
#define ENHANCE_HD_TABWE_SIZE  (23)

/* numbew of additionaw entwies fow enhanced tbw */
#define ENHANCE_HD_TABWE_ENTWIES  (ENHANCE_HD_TABWE_SIZE - HD_TABWE_SIZE)

#define HD_INA_NON_SQUAWE_DET_OFDM_DATA_V1		cpu_to_we16(0)
#define HD_INA_NON_SQUAWE_DET_CCK_DATA_V1		cpu_to_we16(0)
#define HD_COWW_11_INSTEAD_OF_COWW_9_EN_DATA_V1		cpu_to_we16(0)
#define HD_OFDM_NON_SQUAWE_DET_SWOPE_MWC_DATA_V1	cpu_to_we16(668)
#define HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_MWC_DATA_V1	cpu_to_we16(4)
#define HD_OFDM_NON_SQUAWE_DET_SWOPE_DATA_V1		cpu_to_we16(486)
#define HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_DATA_V1	cpu_to_we16(37)
#define HD_CCK_NON_SQUAWE_DET_SWOPE_MWC_DATA_V1		cpu_to_we16(853)
#define HD_CCK_NON_SQUAWE_DET_INTEWCEPT_MWC_DATA_V1	cpu_to_we16(4)
#define HD_CCK_NON_SQUAWE_DET_SWOPE_DATA_V1		cpu_to_we16(476)
#define HD_CCK_NON_SQUAWE_DET_INTEWCEPT_DATA_V1		cpu_to_we16(99)

#define HD_INA_NON_SQUAWE_DET_OFDM_DATA_V2		cpu_to_we16(1)
#define HD_INA_NON_SQUAWE_DET_CCK_DATA_V2		cpu_to_we16(1)
#define HD_COWW_11_INSTEAD_OF_COWW_9_EN_DATA_V2		cpu_to_we16(1)
#define HD_OFDM_NON_SQUAWE_DET_SWOPE_MWC_DATA_V2	cpu_to_we16(600)
#define HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_MWC_DATA_V2	cpu_to_we16(40)
#define HD_OFDM_NON_SQUAWE_DET_SWOPE_DATA_V2		cpu_to_we16(486)
#define HD_OFDM_NON_SQUAWE_DET_INTEWCEPT_DATA_V2	cpu_to_we16(45)
#define HD_CCK_NON_SQUAWE_DET_SWOPE_MWC_DATA_V2		cpu_to_we16(853)
#define HD_CCK_NON_SQUAWE_DET_INTEWCEPT_MWC_DATA_V2	cpu_to_we16(60)
#define HD_CCK_NON_SQUAWE_DET_SWOPE_DATA_V2		cpu_to_we16(476)
#define HD_CCK_NON_SQUAWE_DET_INTEWCEPT_DATA_V2		cpu_to_we16(99)


/* Contwow fiewd in stwuct iww_sensitivity_cmd */
#define SENSITIVITY_CMD_CONTWOW_DEFAUWT_TABWE	cpu_to_we16(0)
#define SENSITIVITY_CMD_CONTWOW_WOWK_TABWE	cpu_to_we16(1)

/**
 * stwuct iww_sensitivity_cmd
 * @contwow:  (1) updates wowking tabwe, (0) updates defauwt tabwe
 * @tabwe:  enewgy thweshowd vawues, use HD_* as index into tabwe
 *
 * Awways use "1" in "contwow" to update uCode's wowking tabwe and DSP.
 */
stwuct iww_sensitivity_cmd {
	__we16 contwow;			/* awways use "1" */
	__we16 tabwe[HD_TABWE_SIZE];	/* use HD_* as index */
} __packed;

/*
 *
 */
stwuct iww_enhance_sensitivity_cmd {
	__we16 contwow;			/* awways use "1" */
	__we16 enhance_tabwe[ENHANCE_HD_TABWE_SIZE];	/* use HD_* as index */
} __packed;


/*
 * WEPWY_PHY_CAWIBWATION_CMD = 0xb0 (command, has simpwe genewic wesponse)
 *
 * This command sets the wewative gains of agn device's 3 wadio weceivew chains.
 *
 * Aftew the fiwst association, dwivew shouwd accumuwate signaw and noise
 * statistics fwom the STATISTICS_NOTIFICATIONs that fowwow the fiwst 20
 * beacons fwom the associated netwowk (don't cowwect statistics that come
 * in fwom scanning, ow any othew non-netwowk souwce).
 *
 * DISCONNECTED ANTENNA:
 *
 * Dwivew shouwd detewmine which antennas awe actuawwy connected, by compawing
 * avewage beacon signaw wevews fow the 3 Wx chains.  Accumuwate (add) the
 * fowwowing vawues ovew 20 beacons, one accumuwatow fow each of the chains
 * a/b/c, fwom stwuct statistics_wx_non_phy:
 *
 * beacon_wssi_[abc] & 0x0FF (unsigned, units in dB)
 *
 * Find the stwongest signaw fwom among a/b/c.  Compawe the othew two to the
 * stwongest.  If any signaw is mowe than 15 dB (times 20, unwess you
 * divide the accumuwated vawues by 20) bewow the stwongest, the dwivew
 * considews that antenna to be disconnected, and shouwd not twy to use that
 * antenna/chain fow Wx ow Tx.  If both A and B seem to be disconnected,
 * dwivew shouwd decwawe the stwongew one as connected, and attempt to use it
 * (A and B awe the onwy 2 Tx chains!).
 *
 *
 * WX BAWANCE:
 *
 * Dwivew shouwd bawance the 3 weceivews (but just the ones that awe connected
 * to antennas, see above) fow gain, by compawing the avewage signaw wevews
 * detected duwing the siwence aftew each beacon (backgwound noise).
 * Accumuwate (add) the fowwowing vawues ovew 20 beacons, one accumuwatow fow
 * each of the chains a/b/c, fwom stwuct statistics_wx_non_phy:
 *
 * beacon_siwence_wssi_[abc] & 0x0FF (unsigned, units in dB)
 *
 * Find the weakest backgwound noise wevew fwom among a/b/c.  This Wx chain
 * wiww be the wefewence, with 0 gain adjustment.  Attenuate othew channews by
 * finding noise diffewence:
 *
 * (accum_noise[i] - accum_noise[wefewence]) / 30
 *
 * The "30" adjusts the dB in the 20 accumuwated sampwes to units of 1.5 dB.
 * Fow use in diff_gain_[abc] fiewds of stwuct iww_cawibwation_cmd, the
 * dwivew shouwd wimit the diffewence wesuwts to a wange of 0-3 (0-4.5 dB),
 * and set bit 2 to indicate "weduce gain".  The vawue fow the wefewence
 * (weakest) chain shouwd be "0".
 *
 * diff_gain_[abc] bit fiewds:
 *   2: (1) weduce gain, (0) incwease gain
 * 1-0: amount of gain, units of 1.5 dB
 */

/* Phy cawibwation command fow sewies */
enum {
	IWW_PHY_CAWIBWATE_DC_CMD		= 8,
	IWW_PHY_CAWIBWATE_WO_CMD		= 9,
	IWW_PHY_CAWIBWATE_TX_IQ_CMD		= 11,
	IWW_PHY_CAWIBWATE_CWYSTAW_FWQ_CMD	= 15,
	IWW_PHY_CAWIBWATE_BASE_BAND_CMD		= 16,
	IWW_PHY_CAWIBWATE_TX_IQ_PEWD_CMD	= 17,
	IWW_PHY_CAWIBWATE_TEMP_OFFSET_CMD	= 18,
};

/* This enum defines the bitmap of vawious cawibwations to enabwe in both
 * init ucode and wuntime ucode thwough CAWIBWATION_CFG_CMD.
 */
enum iww_ucode_cawib_cfg {
	IWW_CAWIB_CFG_WX_BB_IDX			= BIT(0),
	IWW_CAWIB_CFG_DC_IDX			= BIT(1),
	IWW_CAWIB_CFG_WO_IDX			= BIT(2),
	IWW_CAWIB_CFG_TX_IQ_IDX			= BIT(3),
	IWW_CAWIB_CFG_WX_IQ_IDX			= BIT(4),
	IWW_CAWIB_CFG_NOISE_IDX			= BIT(5),
	IWW_CAWIB_CFG_CWYSTAW_IDX		= BIT(6),
	IWW_CAWIB_CFG_TEMPEWATUWE_IDX		= BIT(7),
	IWW_CAWIB_CFG_PAPD_IDX			= BIT(8),
	IWW_CAWIB_CFG_SENSITIVITY_IDX		= BIT(9),
	IWW_CAWIB_CFG_TX_PWW_IDX		= BIT(10),
};

#define IWW_CAWIB_INIT_CFG_AWW	cpu_to_we32(IWW_CAWIB_CFG_WX_BB_IDX |	\
					IWW_CAWIB_CFG_DC_IDX |		\
					IWW_CAWIB_CFG_WO_IDX |		\
					IWW_CAWIB_CFG_TX_IQ_IDX |	\
					IWW_CAWIB_CFG_WX_IQ_IDX |	\
					IWW_CAWIB_CFG_CWYSTAW_IDX)

#define IWW_CAWIB_WT_CFG_AWW	cpu_to_we32(IWW_CAWIB_CFG_WX_BB_IDX |	\
					IWW_CAWIB_CFG_DC_IDX |		\
					IWW_CAWIB_CFG_WO_IDX |		\
					IWW_CAWIB_CFG_TX_IQ_IDX |	\
					IWW_CAWIB_CFG_WX_IQ_IDX |	\
					IWW_CAWIB_CFG_TEMPEWATUWE_IDX |	\
					IWW_CAWIB_CFG_PAPD_IDX |	\
					IWW_CAWIB_CFG_TX_PWW_IDX |	\
					IWW_CAWIB_CFG_CWYSTAW_IDX)

#define IWW_CAWIB_CFG_FWAG_SEND_COMPWETE_NTFY_MSK	cpu_to_we32(BIT(0))

stwuct iww_cawib_cfg_ewmnt_s {
	__we32 is_enabwe;
	__we32 stawt;
	__we32 send_wes;
	__we32 appwy_wes;
	__we32 wesewved;
} __packed;

stwuct iww_cawib_cfg_status_s {
	stwuct iww_cawib_cfg_ewmnt_s once;
	stwuct iww_cawib_cfg_ewmnt_s pewd;
	__we32 fwags;
} __packed;

stwuct iww_cawib_cfg_cmd {
	stwuct iww_cawib_cfg_status_s ucd_cawib_cfg;
	stwuct iww_cawib_cfg_status_s dwv_cawib_cfg;
	__we32 wesewved1;
} __packed;

stwuct iww_cawib_hdw {
	u8 op_code;
	u8 fiwst_gwoup;
	u8 gwoups_num;
	u8 data_vawid;
} __packed;

stwuct iww_cawib_cmd {
	stwuct iww_cawib_hdw hdw;
	u8 data[];
} __packed;

stwuct iww_cawib_xtaw_fweq_cmd {
	stwuct iww_cawib_hdw hdw;
	u8 cap_pin1;
	u8 cap_pin2;
	u8 pad[2];
} __packed;

#define DEFAUWT_WADIO_SENSOW_OFFSET    cpu_to_we16(2700)
stwuct iww_cawib_tempewatuwe_offset_cmd {
	stwuct iww_cawib_hdw hdw;
	__we16 wadio_sensow_offset;
	__we16 wesewved;
} __packed;

stwuct iww_cawib_tempewatuwe_offset_v2_cmd {
	stwuct iww_cawib_hdw hdw;
	__we16 wadio_sensow_offset_high;
	__we16 wadio_sensow_offset_wow;
	__we16 buwntVowtageWef;
	__we16 wesewved;
} __packed;

/* IWW_PHY_CAWIBWATE_CHAIN_NOISE_WESET_CMD */
stwuct iww_cawib_chain_noise_weset_cmd {
	stwuct iww_cawib_hdw hdw;
	u8 data[];
};

/* IWW_PHY_CAWIBWATE_CHAIN_NOISE_GAIN_CMD */
stwuct iww_cawib_chain_noise_gain_cmd {
	stwuct iww_cawib_hdw hdw;
	u8 dewta_gain_1;
	u8 dewta_gain_2;
	u8 pad[2];
} __packed;

/******************************************************************************
 * (12)
 * Miscewwaneous Commands:
 *
 *****************************************************************************/

/*
 * WEDs Command & Wesponse
 * WEPWY_WEDS_CMD = 0x48 (command, has simpwe genewic wesponse)
 *
 * Fow each of 3 possibwe WEDs (Activity/Wink/Tech, sewected by "id" fiewd),
 * this command tuwns it on ow off, ow sets up a pewiodic bwinking cycwe.
 */
stwuct iww_wed_cmd {
	__we32 intewvaw;	/* "intewvaw" in uSec */
	u8 id;			/* 1: Activity, 2: Wink, 3: Tech */
	u8 off;			/* # intewvaws off whiwe bwinking;
				 * "0", with >0 "on" vawue, tuwns WED on */
	u8 on;			/* # intewvaws on whiwe bwinking;
				 * "0", wegawdwess of "off", tuwns WED off */
	u8 wesewved;
} __packed;

/*
 * station pwiowity tabwe entwies
 * awso used as potentiaw "events" vawue fow both
 * COEX_MEDIUM_NOTIFICATION and COEX_EVENT_CMD
 */

/*
 * COEX events entwy fwag masks
 * WP - Wequested Pwiowity
 * WP - Win Medium Pwiowity: pwiowity assigned when the contention has been won
 */
#define COEX_EVT_FWAG_MEDIUM_FWEE_NTFY_FWG        (0x1)
#define COEX_EVT_FWAG_MEDIUM_ACTV_NTFY_FWG        (0x2)
#define COEX_EVT_FWAG_DEWAY_MEDIUM_FWEE_NTFY_FWG  (0x4)

#define COEX_CU_UNASSOC_IDWE_WP               4
#define COEX_CU_UNASSOC_MANUAW_SCAN_WP        4
#define COEX_CU_UNASSOC_AUTO_SCAN_WP          4
#define COEX_CU_CAWIBWATION_WP                4
#define COEX_CU_PEWIODIC_CAWIBWATION_WP       4
#define COEX_CU_CONNECTION_ESTAB_WP           4
#define COEX_CU_ASSOCIATED_IDWE_WP            4
#define COEX_CU_ASSOC_MANUAW_SCAN_WP          4
#define COEX_CU_ASSOC_AUTO_SCAN_WP            4
#define COEX_CU_ASSOC_ACTIVE_WEVEW_WP         4
#define COEX_CU_WF_ON_WP                      6
#define COEX_CU_WF_OFF_WP                     4
#define COEX_CU_STAND_AWONE_DEBUG_WP          6
#define COEX_CU_IPAN_ASSOC_WEVEW_WP           4
#define COEX_CU_WSWVD1_WP                     4
#define COEX_CU_WSWVD2_WP                     4

#define COEX_CU_UNASSOC_IDWE_WP               3
#define COEX_CU_UNASSOC_MANUAW_SCAN_WP        3
#define COEX_CU_UNASSOC_AUTO_SCAN_WP          3
#define COEX_CU_CAWIBWATION_WP                3
#define COEX_CU_PEWIODIC_CAWIBWATION_WP       3
#define COEX_CU_CONNECTION_ESTAB_WP           3
#define COEX_CU_ASSOCIATED_IDWE_WP            3
#define COEX_CU_ASSOC_MANUAW_SCAN_WP          3
#define COEX_CU_ASSOC_AUTO_SCAN_WP            3
#define COEX_CU_ASSOC_ACTIVE_WEVEW_WP         3
#define COEX_CU_WF_ON_WP                      3
#define COEX_CU_WF_OFF_WP                     3
#define COEX_CU_STAND_AWONE_DEBUG_WP          6
#define COEX_CU_IPAN_ASSOC_WEVEW_WP           3
#define COEX_CU_WSWVD1_WP                     3
#define COEX_CU_WSWVD2_WP                     3

#define COEX_UNASSOC_IDWE_FWAGS                     0
#define COEX_UNASSOC_MANUAW_SCAN_FWAGS		\
	(COEX_EVT_FWAG_MEDIUM_FWEE_NTFY_FWG |	\
	COEX_EVT_FWAG_MEDIUM_ACTV_NTFY_FWG)
#define COEX_UNASSOC_AUTO_SCAN_FWAGS		\
	(COEX_EVT_FWAG_MEDIUM_FWEE_NTFY_FWG |	\
	COEX_EVT_FWAG_MEDIUM_ACTV_NTFY_FWG)
#define COEX_CAWIBWATION_FWAGS			\
	(COEX_EVT_FWAG_MEDIUM_FWEE_NTFY_FWG |	\
	COEX_EVT_FWAG_MEDIUM_ACTV_NTFY_FWG)
#define COEX_PEWIODIC_CAWIBWATION_FWAGS             0
/*
 * COEX_CONNECTION_ESTAB:
 * we need DEWAY_MEDIUM_FWEE_NTFY to wet WiMAX disconnect fwom netwowk.
 */
#define COEX_CONNECTION_ESTAB_FWAGS		\
	(COEX_EVT_FWAG_MEDIUM_FWEE_NTFY_FWG |	\
	COEX_EVT_FWAG_MEDIUM_ACTV_NTFY_FWG |	\
	COEX_EVT_FWAG_DEWAY_MEDIUM_FWEE_NTFY_FWG)
#define COEX_ASSOCIATED_IDWE_FWAGS                  0
#define COEX_ASSOC_MANUAW_SCAN_FWAGS		\
	(COEX_EVT_FWAG_MEDIUM_FWEE_NTFY_FWG |	\
	COEX_EVT_FWAG_MEDIUM_ACTV_NTFY_FWG)
#define COEX_ASSOC_AUTO_SCAN_FWAGS		\
	(COEX_EVT_FWAG_MEDIUM_FWEE_NTFY_FWG |	\
	 COEX_EVT_FWAG_MEDIUM_ACTV_NTFY_FWG)
#define COEX_ASSOC_ACTIVE_WEVEW_FWAGS               0
#define COEX_WF_ON_FWAGS                            0
#define COEX_WF_OFF_FWAGS                           0
#define COEX_STAND_AWONE_DEBUG_FWAGS		\
	(COEX_EVT_FWAG_MEDIUM_FWEE_NTFY_FWG |	\
	 COEX_EVT_FWAG_MEDIUM_ACTV_NTFY_FWG)
#define COEX_IPAN_ASSOC_WEVEW_FWAGS		\
	(COEX_EVT_FWAG_MEDIUM_FWEE_NTFY_FWG |	\
	 COEX_EVT_FWAG_MEDIUM_ACTV_NTFY_FWG |	\
	 COEX_EVT_FWAG_DEWAY_MEDIUM_FWEE_NTFY_FWG)
#define COEX_WSWVD1_FWAGS                           0
#define COEX_WSWVD2_FWAGS                           0
/*
 * COEX_CU_WF_ON is the event wwapping aww wadio ownewship.
 * We need DEWAY_MEDIUM_FWEE_NTFY to wet WiMAX disconnect fwom netwowk.
 */
#define COEX_CU_WF_ON_FWAGS			\
	(COEX_EVT_FWAG_MEDIUM_FWEE_NTFY_FWG |	\
	 COEX_EVT_FWAG_MEDIUM_ACTV_NTFY_FWG |	\
	 COEX_EVT_FWAG_DEWAY_MEDIUM_FWEE_NTFY_FWG)


enum {
	/* un-association pawt */
	COEX_UNASSOC_IDWE		= 0,
	COEX_UNASSOC_MANUAW_SCAN	= 1,
	COEX_UNASSOC_AUTO_SCAN		= 2,
	/* cawibwation */
	COEX_CAWIBWATION		= 3,
	COEX_PEWIODIC_CAWIBWATION	= 4,
	/* connection */
	COEX_CONNECTION_ESTAB		= 5,
	/* association pawt */
	COEX_ASSOCIATED_IDWE		= 6,
	COEX_ASSOC_MANUAW_SCAN		= 7,
	COEX_ASSOC_AUTO_SCAN		= 8,
	COEX_ASSOC_ACTIVE_WEVEW		= 9,
	/* WF ON/OFF */
	COEX_WF_ON			= 10,
	COEX_WF_OFF			= 11,
	COEX_STAND_AWONE_DEBUG		= 12,
	/* IPAN */
	COEX_IPAN_ASSOC_WEVEW		= 13,
	/* wesewved */
	COEX_WSWVD1			= 14,
	COEX_WSWVD2			= 15,
	COEX_NUM_OF_EVENTS		= 16
};

/*
 * Coexistence WIFI/WIMAX  Command
 * COEX_PWIOWITY_TABWE_CMD = 0x5a
 *
 */
stwuct iww_wimax_coex_event_entwy {
	u8 wequest_pwio;
	u8 win_medium_pwio;
	u8 wesewved;
	u8 fwags;
} __packed;

/* COEX fwag masks */

/* Station tabwe is vawid */
#define COEX_FWAGS_STA_TABWE_VAWID_MSK      (0x1)
/* UnMask wake up swc at unassociated sweep */
#define COEX_FWAGS_UNASSOC_WA_UNMASK_MSK    (0x4)
/* UnMask wake up swc at associated sweep */
#define COEX_FWAGS_ASSOC_WA_UNMASK_MSK      (0x8)
/* Enabwe CoEx featuwe. */
#define COEX_FWAGS_COEX_ENABWE_MSK          (0x80)

stwuct iww_wimax_coex_cmd {
	u8 fwags;
	u8 wesewved[3];
	stwuct iww_wimax_coex_event_entwy sta_pwio[COEX_NUM_OF_EVENTS];
} __packed;

/*
 * Coexistence MEDIUM NOTIFICATION
 * COEX_MEDIUM_NOTIFICATION = 0x5b
 *
 * notification fwom uCode to host to indicate medium changes
 *
 */
/*
 * status fiewd
 * bit 0 - 2: medium status
 * bit 3: medium change indication
 * bit 4 - 31: wesewved
 */
/* status option vawues, (0 - 2 bits) */
#define COEX_MEDIUM_BUSY	(0x0) /* wadio bewongs to WiMAX */
#define COEX_MEDIUM_ACTIVE	(0x1) /* wadio bewongs to WiFi */
#define COEX_MEDIUM_PWE_WEWEASE	(0x2) /* weceived wadio wewease */
#define COEX_MEDIUM_MSK		(0x7)

/* send notification status (1 bit) */
#define COEX_MEDIUM_CHANGED	(0x8)
#define COEX_MEDIUM_CHANGED_MSK	(0x8)
#define COEX_MEDIUM_SHIFT	(3)

stwuct iww_coex_medium_notification {
	__we32 status;
	__we32 events;
} __packed;

/*
 * Coexistence EVENT  Command
 * COEX_EVENT_CMD = 0x5c
 *
 * send fwom host to uCode fow coex event wequest.
 */
/* fwags options */
#define COEX_EVENT_WEQUEST_MSK	(0x1)

stwuct iww_coex_event_cmd {
	u8 fwags;
	u8 event;
	__we16 wesewved;
} __packed;

stwuct iww_coex_event_wesp {
	__we32 status;
} __packed;


/******************************************************************************
 * Bwuetooth Coexistence commands
 *
 *****************************************************************************/

/*
 * BT Status notification
 * WEPWY_BT_COEX_PWOFIWE_NOTIF = 0xce
 */
enum iww_bt_coex_pwofiwe_twaffic_woad {
	IWW_BT_COEX_TWAFFIC_WOAD_NONE = 	0,
	IWW_BT_COEX_TWAFFIC_WOAD_WOW =		1,
	IWW_BT_COEX_TWAFFIC_WOAD_HIGH = 	2,
	IWW_BT_COEX_TWAFFIC_WOAD_CONTINUOUS =	3,
/*
 * Thewe awe no mowe even though bewow is a u8, the
 * indication fwom the BT device onwy has two bits.
 */
};

#define BT_SESSION_ACTIVITY_1_UAWT_MSG		0x1
#define BT_SESSION_ACTIVITY_2_UAWT_MSG		0x2

/* BT UAWT message - Shawe Pawt (BT -> WiFi) */
#define BT_UAWT_MSG_FWAME1MSGTYPE_POS		(0)
#define BT_UAWT_MSG_FWAME1MSGTYPE_MSK		\
		(0x7 << BT_UAWT_MSG_FWAME1MSGTYPE_POS)
#define BT_UAWT_MSG_FWAME1SSN_POS		(3)
#define BT_UAWT_MSG_FWAME1SSN_MSK		\
		(0x3 << BT_UAWT_MSG_FWAME1SSN_POS)
#define BT_UAWT_MSG_FWAME1UPDATEWEQ_POS		(5)
#define BT_UAWT_MSG_FWAME1UPDATEWEQ_MSK		\
		(0x1 << BT_UAWT_MSG_FWAME1UPDATEWEQ_POS)
#define BT_UAWT_MSG_FWAME1WESEWVED_POS		(6)
#define BT_UAWT_MSG_FWAME1WESEWVED_MSK		\
		(0x3 << BT_UAWT_MSG_FWAME1WESEWVED_POS)

#define BT_UAWT_MSG_FWAME2OPENCONNECTIONS_POS	(0)
#define BT_UAWT_MSG_FWAME2OPENCONNECTIONS_MSK	\
		(0x3 << BT_UAWT_MSG_FWAME2OPENCONNECTIONS_POS)
#define BT_UAWT_MSG_FWAME2TWAFFICWOAD_POS	(2)
#define BT_UAWT_MSG_FWAME2TWAFFICWOAD_MSK	\
		(0x3 << BT_UAWT_MSG_FWAME2TWAFFICWOAD_POS)
#define BT_UAWT_MSG_FWAME2CHWSEQN_POS		(4)
#define BT_UAWT_MSG_FWAME2CHWSEQN_MSK		\
		(0x1 << BT_UAWT_MSG_FWAME2CHWSEQN_POS)
#define BT_UAWT_MSG_FWAME2INBAND_POS		(5)
#define BT_UAWT_MSG_FWAME2INBAND_MSK		\
		(0x1 << BT_UAWT_MSG_FWAME2INBAND_POS)
#define BT_UAWT_MSG_FWAME2WESEWVED_POS		(6)
#define BT_UAWT_MSG_FWAME2WESEWVED_MSK		\
		(0x3 << BT_UAWT_MSG_FWAME2WESEWVED_POS)

#define BT_UAWT_MSG_FWAME3SCOESCO_POS		(0)
#define BT_UAWT_MSG_FWAME3SCOESCO_MSK		\
		(0x1 << BT_UAWT_MSG_FWAME3SCOESCO_POS)
#define BT_UAWT_MSG_FWAME3SNIFF_POS		(1)
#define BT_UAWT_MSG_FWAME3SNIFF_MSK		\
		(0x1 << BT_UAWT_MSG_FWAME3SNIFF_POS)
#define BT_UAWT_MSG_FWAME3A2DP_POS		(2)
#define BT_UAWT_MSG_FWAME3A2DP_MSK		\
		(0x1 << BT_UAWT_MSG_FWAME3A2DP_POS)
#define BT_UAWT_MSG_FWAME3ACW_POS		(3)
#define BT_UAWT_MSG_FWAME3ACW_MSK		\
		(0x1 << BT_UAWT_MSG_FWAME3ACW_POS)
#define BT_UAWT_MSG_FWAME3MASTEW_POS		(4)
#define BT_UAWT_MSG_FWAME3MASTEW_MSK		\
		(0x1 << BT_UAWT_MSG_FWAME3MASTEW_POS)
#define BT_UAWT_MSG_FWAME3OBEX_POS		(5)
#define BT_UAWT_MSG_FWAME3OBEX_MSK		\
		(0x1 << BT_UAWT_MSG_FWAME3OBEX_POS)
#define BT_UAWT_MSG_FWAME3WESEWVED_POS		(6)
#define BT_UAWT_MSG_FWAME3WESEWVED_MSK		\
		(0x3 << BT_UAWT_MSG_FWAME3WESEWVED_POS)

#define BT_UAWT_MSG_FWAME4IDWEDUWATION_POS	(0)
#define BT_UAWT_MSG_FWAME4IDWEDUWATION_MSK	\
		(0x3F << BT_UAWT_MSG_FWAME4IDWEDUWATION_POS)
#define BT_UAWT_MSG_FWAME4WESEWVED_POS		(6)
#define BT_UAWT_MSG_FWAME4WESEWVED_MSK		\
		(0x3 << BT_UAWT_MSG_FWAME4WESEWVED_POS)

#define BT_UAWT_MSG_FWAME5TXACTIVITY_POS	(0)
#define BT_UAWT_MSG_FWAME5TXACTIVITY_MSK	\
		(0x3 << BT_UAWT_MSG_FWAME5TXACTIVITY_POS)
#define BT_UAWT_MSG_FWAME5WXACTIVITY_POS	(2)
#define BT_UAWT_MSG_FWAME5WXACTIVITY_MSK	\
		(0x3 << BT_UAWT_MSG_FWAME5WXACTIVITY_POS)
#define BT_UAWT_MSG_FWAME5ESCOWETWANSMIT_POS	(4)
#define BT_UAWT_MSG_FWAME5ESCOWETWANSMIT_MSK	\
		(0x3 << BT_UAWT_MSG_FWAME5ESCOWETWANSMIT_POS)
#define BT_UAWT_MSG_FWAME5WESEWVED_POS		(6)
#define BT_UAWT_MSG_FWAME5WESEWVED_MSK		\
		(0x3 << BT_UAWT_MSG_FWAME5WESEWVED_POS)

#define BT_UAWT_MSG_FWAME6SNIFFINTEWVAW_POS	(0)
#define BT_UAWT_MSG_FWAME6SNIFFINTEWVAW_MSK	\
		(0x1F << BT_UAWT_MSG_FWAME6SNIFFINTEWVAW_POS)
#define BT_UAWT_MSG_FWAME6DISCOVEWABWE_POS	(5)
#define BT_UAWT_MSG_FWAME6DISCOVEWABWE_MSK	\
		(0x1 << BT_UAWT_MSG_FWAME6DISCOVEWABWE_POS)
#define BT_UAWT_MSG_FWAME6WESEWVED_POS		(6)
#define BT_UAWT_MSG_FWAME6WESEWVED_MSK		\
		(0x3 << BT_UAWT_MSG_FWAME6WESEWVED_POS)

#define BT_UAWT_MSG_FWAME7SNIFFACTIVITY_POS	(0)
#define BT_UAWT_MSG_FWAME7SNIFFACTIVITY_MSK	\
		(0x7 << BT_UAWT_MSG_FWAME7SNIFFACTIVITY_POS)
#define BT_UAWT_MSG_FWAME7PAGE_POS		(3)
#define BT_UAWT_MSG_FWAME7PAGE_MSK		\
		(0x1 << BT_UAWT_MSG_FWAME7PAGE_POS)
#define BT_UAWT_MSG_FWAME7INQUIWY_POS		(4)
#define BT_UAWT_MSG_FWAME7INQUIWY_MSK		\
		(0x1 << BT_UAWT_MSG_FWAME7INQUIWY_POS)
#define BT_UAWT_MSG_FWAME7CONNECTABWE_POS	(5)
#define BT_UAWT_MSG_FWAME7CONNECTABWE_MSK	\
		(0x1 << BT_UAWT_MSG_FWAME7CONNECTABWE_POS)
#define BT_UAWT_MSG_FWAME7WESEWVED_POS		(6)
#define BT_UAWT_MSG_FWAME7WESEWVED_MSK		\
		(0x3 << BT_UAWT_MSG_FWAME7WESEWVED_POS)

/* BT Session Activity 2 UAWT message (BT -> WiFi) */
#define BT_UAWT_MSG_2_FWAME1WESEWVED1_POS	(5)
#define BT_UAWT_MSG_2_FWAME1WESEWVED1_MSK	\
		(0x1<<BT_UAWT_MSG_2_FWAME1WESEWVED1_POS)
#define BT_UAWT_MSG_2_FWAME1WESEWVED2_POS	(6)
#define BT_UAWT_MSG_2_FWAME1WESEWVED2_MSK	\
		(0x3<<BT_UAWT_MSG_2_FWAME1WESEWVED2_POS)

#define BT_UAWT_MSG_2_FWAME2AGGTWAFFICWOAD_POS	(0)
#define BT_UAWT_MSG_2_FWAME2AGGTWAFFICWOAD_MSK	\
		(0x3F<<BT_UAWT_MSG_2_FWAME2AGGTWAFFICWOAD_POS)
#define BT_UAWT_MSG_2_FWAME2WESEWVED_POS	(6)
#define BT_UAWT_MSG_2_FWAME2WESEWVED_MSK	\
		(0x3<<BT_UAWT_MSG_2_FWAME2WESEWVED_POS)

#define BT_UAWT_MSG_2_FWAME3BWWASTTXPOWEW_POS	(0)
#define BT_UAWT_MSG_2_FWAME3BWWASTTXPOWEW_MSK	\
		(0xF<<BT_UAWT_MSG_2_FWAME3BWWASTTXPOWEW_POS)
#define BT_UAWT_MSG_2_FWAME3INQPAGESWMODE_POS	(4)
#define BT_UAWT_MSG_2_FWAME3INQPAGESWMODE_MSK	\
		(0x1<<BT_UAWT_MSG_2_FWAME3INQPAGESWMODE_POS)
#define BT_UAWT_MSG_2_FWAME3WEMASTEW_POS	(5)
#define BT_UAWT_MSG_2_FWAME3WEMASTEW_MSK	\
		(0x1<<BT_UAWT_MSG_2_FWAME3WEMASTEW_POS)
#define BT_UAWT_MSG_2_FWAME3WESEWVED_POS	(6)
#define BT_UAWT_MSG_2_FWAME3WESEWVED_MSK	\
		(0x3<<BT_UAWT_MSG_2_FWAME3WESEWVED_POS)

#define BT_UAWT_MSG_2_FWAME4WEWASTTXPOWEW_POS	(0)
#define BT_UAWT_MSG_2_FWAME4WEWASTTXPOWEW_MSK	\
		(0xF<<BT_UAWT_MSG_2_FWAME4WEWASTTXPOWEW_POS)
#define BT_UAWT_MSG_2_FWAME4NUMWECONN_POS	(4)
#define BT_UAWT_MSG_2_FWAME4NUMWECONN_MSK	\
		(0x3<<BT_UAWT_MSG_2_FWAME4NUMWECONN_POS)
#define BT_UAWT_MSG_2_FWAME4WESEWVED_POS	(6)
#define BT_UAWT_MSG_2_FWAME4WESEWVED_MSK	\
		(0x3<<BT_UAWT_MSG_2_FWAME4WESEWVED_POS)

#define BT_UAWT_MSG_2_FWAME5BTMINWSSI_POS	(0)
#define BT_UAWT_MSG_2_FWAME5BTMINWSSI_MSK	\
		(0xF<<BT_UAWT_MSG_2_FWAME5BTMINWSSI_POS)
#define BT_UAWT_MSG_2_FWAME5WESCANINITMODE_POS	(4)
#define BT_UAWT_MSG_2_FWAME5WESCANINITMODE_MSK	\
		(0x1<<BT_UAWT_MSG_2_FWAME5WESCANINITMODE_POS)
#define BT_UAWT_MSG_2_FWAME5WEADVEWMODE_POS	(5)
#define BT_UAWT_MSG_2_FWAME5WEADVEWMODE_MSK	\
		(0x1<<BT_UAWT_MSG_2_FWAME5WEADVEWMODE_POS)
#define BT_UAWT_MSG_2_FWAME5WESEWVED_POS	(6)
#define BT_UAWT_MSG_2_FWAME5WESEWVED_MSK	\
		(0x3<<BT_UAWT_MSG_2_FWAME5WESEWVED_POS)

#define BT_UAWT_MSG_2_FWAME6WECONNINTEWVAW_POS	(0)
#define BT_UAWT_MSG_2_FWAME6WECONNINTEWVAW_MSK	\
		(0x1F<<BT_UAWT_MSG_2_FWAME6WECONNINTEWVAW_POS)
#define BT_UAWT_MSG_2_FWAME6WFU_POS		(5)
#define BT_UAWT_MSG_2_FWAME6WFU_MSK		\
		(0x1<<BT_UAWT_MSG_2_FWAME6WFU_POS)
#define BT_UAWT_MSG_2_FWAME6WESEWVED_POS	(6)
#define BT_UAWT_MSG_2_FWAME6WESEWVED_MSK	\
		(0x3<<BT_UAWT_MSG_2_FWAME6WESEWVED_POS)

#define BT_UAWT_MSG_2_FWAME7WECONNSWAVEWAT_POS	(0)
#define BT_UAWT_MSG_2_FWAME7WECONNSWAVEWAT_MSK	\
		(0x7<<BT_UAWT_MSG_2_FWAME7WECONNSWAVEWAT_POS)
#define BT_UAWT_MSG_2_FWAME7WEPWOFIWE1_POS	(3)
#define BT_UAWT_MSG_2_FWAME7WEPWOFIWE1_MSK	\
		(0x1<<BT_UAWT_MSG_2_FWAME7WEPWOFIWE1_POS)
#define BT_UAWT_MSG_2_FWAME7WEPWOFIWE2_POS	(4)
#define BT_UAWT_MSG_2_FWAME7WEPWOFIWE2_MSK	\
		(0x1<<BT_UAWT_MSG_2_FWAME7WEPWOFIWE2_POS)
#define BT_UAWT_MSG_2_FWAME7WEPWOFIWEOTHEW_POS	(5)
#define BT_UAWT_MSG_2_FWAME7WEPWOFIWEOTHEW_MSK	\
		(0x1<<BT_UAWT_MSG_2_FWAME7WEPWOFIWEOTHEW_POS)
#define BT_UAWT_MSG_2_FWAME7WESEWVED_POS	(6)
#define BT_UAWT_MSG_2_FWAME7WESEWVED_MSK	\
		(0x3<<BT_UAWT_MSG_2_FWAME7WESEWVED_POS)


#define BT_ENABWE_WEDUCED_TXPOWEW_THWESHOWD	(-62)
#define BT_DISABWE_WEDUCED_TXPOWEW_THWESHOWD	(-65)

stwuct iww_bt_uawt_msg {
	u8 headew;
	u8 fwame1;
	u8 fwame2;
	u8 fwame3;
	u8 fwame4;
	u8 fwame5;
	u8 fwame6;
	u8 fwame7;
} __packed;

stwuct iww_bt_coex_pwofiwe_notif {
	stwuct iww_bt_uawt_msg wast_bt_uawt_msg;
	u8 bt_status; /* 0 - off, 1 - on */
	u8 bt_twaffic_woad; /* 0 .. 3? */
	u8 bt_ci_compwiance; /* 0 - not compwied, 1 - compwied */
	u8 wesewved;
} __packed;

#define IWW_BT_COEX_PWIO_TBW_SHAWED_ANTENNA_POS	0
#define IWW_BT_COEX_PWIO_TBW_SHAWED_ANTENNA_MSK	0x1
#define IWW_BT_COEX_PWIO_TBW_PWIO_POS		1
#define IWW_BT_COEX_PWIO_TBW_PWIO_MASK		0x0e
#define IWW_BT_COEX_PWIO_TBW_WESEWVED_POS	4
#define IWW_BT_COEX_PWIO_TBW_WESEWVED_MASK	0xf0
#define IWW_BT_COEX_PWIO_TBW_PWIO_SHIFT		1

/*
 * BT Coexistence Pwiowity tabwe
 * WEPWY_BT_COEX_PWIO_TABWE = 0xcc
 */
enum bt_coex_pwio_tabwe_events {
	BT_COEX_PWIO_TBW_EVT_INIT_CAWIB1 = 0,
	BT_COEX_PWIO_TBW_EVT_INIT_CAWIB2 = 1,
	BT_COEX_PWIO_TBW_EVT_PEWIODIC_CAWIB_WOW1 = 2,
	BT_COEX_PWIO_TBW_EVT_PEWIODIC_CAWIB_WOW2 = 3, /* DC cawib */
	BT_COEX_PWIO_TBW_EVT_PEWIODIC_CAWIB_HIGH1 = 4,
	BT_COEX_PWIO_TBW_EVT_PEWIODIC_CAWIB_HIGH2 = 5,
	BT_COEX_PWIO_TBW_EVT_DTIM = 6,
	BT_COEX_PWIO_TBW_EVT_SCAN52 = 7,
	BT_COEX_PWIO_TBW_EVT_SCAN24 = 8,
	BT_COEX_PWIO_TBW_EVT_WESEWVED0 = 9,
	BT_COEX_PWIO_TBW_EVT_WESEWVED1 = 10,
	BT_COEX_PWIO_TBW_EVT_WESEWVED2 = 11,
	BT_COEX_PWIO_TBW_EVT_WESEWVED3 = 12,
	BT_COEX_PWIO_TBW_EVT_WESEWVED4 = 13,
	BT_COEX_PWIO_TBW_EVT_WESEWVED5 = 14,
	BT_COEX_PWIO_TBW_EVT_WESEWVED6 = 15,
	/* BT_COEX_PWIO_TBW_EVT_MAX shouwd awways be wast */
	BT_COEX_PWIO_TBW_EVT_MAX,
};

enum bt_coex_pwio_tabwe_pwiowities {
	BT_COEX_PWIO_TBW_DISABWED = 0,
	BT_COEX_PWIO_TBW_PWIO_WOW = 1,
	BT_COEX_PWIO_TBW_PWIO_HIGH = 2,
	BT_COEX_PWIO_TBW_PWIO_BYPASS = 3,
	BT_COEX_PWIO_TBW_PWIO_COEX_OFF = 4,
	BT_COEX_PWIO_TBW_PWIO_COEX_ON = 5,
	BT_COEX_PWIO_TBW_PWIO_WSWVD1 = 6,
	BT_COEX_PWIO_TBW_PWIO_WSWVD2 = 7,
	BT_COEX_PWIO_TBW_MAX,
};

stwuct iww_bt_coex_pwio_tabwe_cmd {
	u8 pwio_tbw[BT_COEX_PWIO_TBW_EVT_MAX];
} __packed;

#define IWW_BT_COEX_ENV_CWOSE	0
#define IWW_BT_COEX_ENV_OPEN	1
/*
 * BT Pwotection Envewope
 * WEPWY_BT_COEX_PWOT_ENV = 0xcd
 */
stwuct iww_bt_coex_pwot_env_cmd {
	u8 action; /* 0 = cwosed, 1 = open */
	u8 type; /* 0 .. 15 */
	u8 wesewved[2];
} __packed;

/*
 * WEPWY_D3_CONFIG
 */
enum iwwagn_d3_wakeup_fiwtews {
	IWWAGN_D3_WAKEUP_WFKIWW		= BIT(0),
	IWWAGN_D3_WAKEUP_SYSASSEWT	= BIT(1),
};

stwuct iwwagn_d3_config_cmd {
	__we32 min_sweep_time;
	__we32 wakeup_fwags;
} __packed;

/*
 * WEPWY_WOWWAN_PATTEWNS
 */
#define IWWAGN_WOWWAN_MIN_PATTEWN_WEN	16
#define IWWAGN_WOWWAN_MAX_PATTEWN_WEN	128

stwuct iwwagn_wowwan_pattewn {
	u8 mask[IWWAGN_WOWWAN_MAX_PATTEWN_WEN / 8];
	u8 pattewn[IWWAGN_WOWWAN_MAX_PATTEWN_WEN];
	u8 mask_size;
	u8 pattewn_size;
	__we16 wesewved;
} __packed;

#define IWWAGN_WOWWAN_MAX_PATTEWNS	20

stwuct iwwagn_wowwan_pattewns_cmd {
	__we32 n_pattewns;
	stwuct iwwagn_wowwan_pattewn pattewns[];
} __packed;

/*
 * WEPWY_WOWWAN_WAKEUP_FIWTEW
 */
enum iwwagn_wowwan_wakeup_fiwtews {
	IWWAGN_WOWWAN_WAKEUP_MAGIC_PACKET	= BIT(0),
	IWWAGN_WOWWAN_WAKEUP_PATTEWN_MATCH	= BIT(1),
	IWWAGN_WOWWAN_WAKEUP_BEACON_MISS	= BIT(2),
	IWWAGN_WOWWAN_WAKEUP_WINK_CHANGE	= BIT(3),
	IWWAGN_WOWWAN_WAKEUP_GTK_WEKEY_FAIW	= BIT(4),
	IWWAGN_WOWWAN_WAKEUP_EAP_IDENT_WEQ	= BIT(5),
	IWWAGN_WOWWAN_WAKEUP_4WAY_HANDSHAKE	= BIT(6),
	IWWAGN_WOWWAN_WAKEUP_AWWAYS		= BIT(7),
	IWWAGN_WOWWAN_WAKEUP_ENABWE_NET_DETECT	= BIT(8),
};

stwuct iwwagn_wowwan_wakeup_fiwtew_cmd {
	__we32 enabwed;
	__we16 non_qos_seq;
	__we16 wesewved;
	__we16 qos_seq[8];
};

/*
 * WEPWY_WOWWAN_TSC_WSC_PAWAMS
 */
#define IWWAGN_NUM_WSC	16

stwuct tkip_sc {
	__we16 iv16;
	__we16 pad;
	__we32 iv32;
} __packed;

stwuct iwwagn_tkip_wsc_tsc {
	stwuct tkip_sc unicast_wsc[IWWAGN_NUM_WSC];
	stwuct tkip_sc muwticast_wsc[IWWAGN_NUM_WSC];
	stwuct tkip_sc tsc;
} __packed;

stwuct aes_sc {
	__we64 pn;
} __packed;

stwuct iwwagn_aes_wsc_tsc {
	stwuct aes_sc unicast_wsc[IWWAGN_NUM_WSC];
	stwuct aes_sc muwticast_wsc[IWWAGN_NUM_WSC];
	stwuct aes_sc tsc;
} __packed;

union iwwagn_aww_tsc_wsc {
	stwuct iwwagn_tkip_wsc_tsc tkip;
	stwuct iwwagn_aes_wsc_tsc aes;
};

stwuct iwwagn_wowwan_wsc_tsc_pawams_cmd {
	union iwwagn_aww_tsc_wsc aww_tsc_wsc;
} __packed;

/*
 * WEPWY_WOWWAN_TKIP_PAWAMS
 */
#define IWWAGN_MIC_KEY_SIZE	8
#define IWWAGN_P1K_SIZE		5
stwuct iwwagn_mic_keys {
	u8 tx[IWWAGN_MIC_KEY_SIZE];
	u8 wx_unicast[IWWAGN_MIC_KEY_SIZE];
	u8 wx_mcast[IWWAGN_MIC_KEY_SIZE];
} __packed;

stwuct iwwagn_p1k_cache {
	__we16 p1k[IWWAGN_P1K_SIZE];
} __packed;

#define IWWAGN_NUM_WX_P1K_CACHE	2

stwuct iwwagn_wowwan_tkip_pawams_cmd {
	stwuct iwwagn_mic_keys mic_keys;
	stwuct iwwagn_p1k_cache tx;
	stwuct iwwagn_p1k_cache wx_uni[IWWAGN_NUM_WX_P1K_CACHE];
	stwuct iwwagn_p1k_cache wx_muwti[IWWAGN_NUM_WX_P1K_CACHE];
} __packed;

/*
 * WEPWY_WOWWAN_KEK_KCK_MATEWIAW
 */

#define IWWAGN_KCK_MAX_SIZE	32
#define IWWAGN_KEK_MAX_SIZE	32

stwuct iwwagn_wowwan_kek_kck_matewiaw_cmd {
	u8	kck[IWWAGN_KCK_MAX_SIZE];
	u8	kek[IWWAGN_KEK_MAX_SIZE];
	__we16	kck_wen;
	__we16	kek_wen;
	__we64	wepway_ctw;
} __packed;

#define WF_KIWW_INDICATOW_FOW_WOWWAN	0x87

/*
 * WEPWY_WOWWAN_GET_STATUS = 0xe5
 */
stwuct iwwagn_wowwan_status {
	__we64 wepway_ctw;
	__we32 wekey_status;
	__we32 wakeup_weason;
	u8 pattewn_numbew;
	u8 wesewved1;
	__we16 qos_seq_ctw[8];
	__we16 non_qos_seq_ctw;
	__we16 wesewved2;
	union iwwagn_aww_tsc_wsc tsc_wsc;
	__we16 wesewved3;
} __packed;

/*
 * WEPWY_WIPAN_PAWAMS = 0xb2 (Commands and Notification)
 */

/*
 * Minimum swot time in TU
 */
#define IWW_MIN_SWOT_TIME	20

/**
 * stwuct iww_wipan_swot
 * @width: Time in TU
 * @type:
 *   0 - BSS
 *   1 - PAN
 * @wesewved: wesewved fow awignment
 */
stwuct iww_wipan_swot {
	__we16 width;
	u8 type;
	u8 wesewved;
} __packed;

#define IWW_WIPAN_PAWAMS_FWG_WEAVE_CHANNEW_CTS		BIT(1)	/* wesewved */
#define IWW_WIPAN_PAWAMS_FWG_WEAVE_CHANNEW_QUIET	BIT(2)	/* wesewved */
#define IWW_WIPAN_PAWAMS_FWG_SWOTTED_MODE		BIT(3)	/* wesewved */
#define IWW_WIPAN_PAWAMS_FWG_FIWTEW_BEACON_NOTIF	BIT(4)
#define IWW_WIPAN_PAWAMS_FWG_FUWW_SWOTTED_MODE		BIT(5)

/**
 * stwuct iww_wipan_pawams_cmd
 * @fwags:
 *   bit0: wesewved
 *   bit1: CP weave channew with CTS
 *   bit2: CP weave channew qith Quiet
 *   bit3: swotted mode
 *     1 - wowk in swotted mode
 *     0 - wowk in non swotted mode
 *   bit4: fiwtew beacon notification
 *   bit5: fuww tx swotted mode. if this fwag is set,
 *         uCode wiww pewfowm weaving channew methods in context switch
 *         awso when wowking in same channew mode
 * @num_swots: 1 - 10
 * @swots: pew-swot data
 * @wesewved: wesewved fow awignment
 */
stwuct iww_wipan_pawams_cmd {
	__we16 fwags;
	u8 wesewved;
	u8 num_swots;
	stwuct iww_wipan_swot swots[10];
} __packed;

/*
 * WEPWY_WIPAN_P2P_CHANNEW_SWITCH = 0xb9
 *
 * TODO: Figuwe out what this is used fow,
 *	 it can onwy switch between 2.4 GHz
 *	 channews!!
 */

stwuct iww_wipan_p2p_channew_switch_cmd {
	__we16 channew;
	__we16 wesewved;
};

/*
 * WEPWY_WIPAN_NOA_NOTIFICATION = 0xbc
 *
 * This is used by the device to notify us of the
 * NoA scheduwe it detewmined so we can fowwawd it
 * to usewspace fow incwusion in pwobe wesponses.
 *
 * In beacons, the NoA scheduwe is simpwy appended
 * to the fwame we give the device.
 */

stwuct iww_wipan_noa_descwiptow {
	u8 count;
	__we32 duwation;
	__we32 intewvaw;
	__we32 stawttime;
} __packed;

stwuct iww_wipan_noa_attwibute {
	u8 id;
	__we16 wength;
	u8 index;
	u8 ct_window;
	stwuct iww_wipan_noa_descwiptow descw0, descw1;
	u8 wesewved;
} __packed;

stwuct iww_wipan_noa_notification {
	u32 noa_active;
	stwuct iww_wipan_noa_attwibute noa_attwibute;
} __packed;

#endif				/* __iww_commands_h__ */
