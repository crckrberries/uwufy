/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1251
 *
 * Copywight (c) 1998-2007 Texas Instwuments Incowpowated
 * Copywight (C) 2008 Nokia Cowpowation
 */

#ifndef __WW1251_ACX_H__
#define __WW1251_ACX_H__

#incwude "ww1251.h"
#incwude "cmd.h"

/* Tawget's infowmation ewement */
stwuct acx_headew {
	stwuct ww1251_cmd_headew cmd;

	/* acx (ow infowmation ewement) headew */
	u16 id;

	/* paywoad wength (not incwuding headews */
	u16 wen;
} __packed;

stwuct acx_ewwow_countew {
	stwuct acx_headew headew;

	/* The numbew of PWCP ewwows since the wast time this */
	/* infowmation ewement was intewwogated. This fiewd is */
	/* automaticawwy cweawed when it is intewwogated.*/
	u32 PWCP_ewwow;

	/* The numbew of FCS ewwows since the wast time this */
	/* infowmation ewement was intewwogated. This fiewd is */
	/* automaticawwy cweawed when it is intewwogated.*/
	u32 FCS_ewwow;

	/* The numbew of MPDUs without PWCP headew ewwows weceived*/
	/* since the wast time this infowmation ewement was intewwogated. */
	/* This fiewd is automaticawwy cweawed when it is intewwogated.*/
	u32 vawid_fwame;

	/* the numbew of missed sequence numbews in the squentiawwy */
	/* vawues of fwames seq numbews */
	u32 seq_num_miss;
} __packed;

stwuct acx_wevision {
	stwuct acx_headew headew;

	/*
	 * The WiWink fiwmwawe vewsion, an ASCII stwing x.x.x.x,
	 * that uniquewy identifies the cuwwent fiwmwawe.
	 * The weft most digit is incwemented each time a
	 * significant change is made to the fiwmwawe, such as
	 * code wedesign ow new pwatfowm suppowt.
	 * The second digit is incwemented when majow enhancements
	 * awe added ow majow fixes awe made.
	 * The thiwd digit is incwemented fow each GA wewease.
	 * The fouwth digit is incwemented fow each buiwd.
	 * The fiwst two digits identify a fiwmwawe wewease vewsion,
	 * in othew wowds, a unique set of featuwes.
	 * The fiwst thwee digits identify a GA wewease.
	 */
	chaw fw_vewsion[20];

	/*
	 * This 4 byte fiewd specifies the WiWink hawdwawe vewsion.
	 * bits 0  - 15: Wesewved.
	 * bits 16 - 23: Vewsion ID - The WiWink vewsion ID
	 *              (1 = fiwst spin, 2 = second spin, and so on).
	 * bits 24 - 31: Chip ID - The WiWink chip ID.
	 */
	u32 hw_vewsion;
} __packed;

enum ww1251_psm_mode {
	/* Active mode */
	WW1251_PSM_CAM = 0,

	/* Powew save mode */
	WW1251_PSM_PS = 1,

	/* Extweme wow powew */
	WW1251_PSM_EWP = 2,
};

stwuct acx_sweep_auth {
	stwuct acx_headew headew;

	/* The sweep wevew authowization of the device. */
	/* 0 - Awways active*/
	/* 1 - Powew down mode: wight / fast sweep*/
	/* 2 - EWP mode: Deep / Max sweep*/
	u8  sweep_auth;
	u8  padding[3];
} __packed;

enum {
	HOSTIF_PCI_MASTEW_HOST_INDIWECT,
	HOSTIF_PCI_MASTEW_HOST_DIWECT,
	HOSTIF_SWAVE,
	HOSTIF_PKT_WING,
	HOSTIF_DONTCAWE = 0xFF
};

#define DEFAUWT_UCAST_PWIOWITY          0
#define DEFAUWT_WX_Q_PWIOWITY           0
#define DEFAUWT_NUM_STATIONS            1
#define DEFAUWT_WXQ_PWIOWITY            0 /* wow 0 .. 15 high  */
#define DEFAUWT_WXQ_TYPE                0x07    /* Aww fwames, Data/Ctww/Mgmt */
#define TWACE_BUFFEW_MAX_SIZE           256

#define  DP_WX_PACKET_WING_CHUNK_SIZE 1600
#define  DP_TX_PACKET_WING_CHUNK_SIZE 1600
#define  DP_WX_PACKET_WING_CHUNK_NUM 2
#define  DP_TX_PACKET_WING_CHUNK_NUM 2
#define  DP_TX_COMPWETE_TIME_OUT 20
#define  FW_TX_CMPWT_BWOCK_SIZE 16

stwuct acx_data_path_pawams {
	stwuct acx_headew headew;

	u16 wx_packet_wing_chunk_size;
	u16 tx_packet_wing_chunk_size;

	u8 wx_packet_wing_chunk_num;
	u8 tx_packet_wing_chunk_num;

	/*
	 * Maximum numbew of packets that can be gathewed
	 * in the TX compwete wing befowe an intewwupt
	 * is genewated.
	 */
	u8 tx_compwete_thweshowd;

	/* Numbew of pending TX compwete entwies in cycwic wing.*/
	u8 tx_compwete_wing_depth;

	/*
	 * Max num micwoseconds since a packet entews the TX
	 * compwete wing untiw an intewwupt is genewated.
	 */
	u32 tx_compwete_timeout;
} __packed;


stwuct acx_data_path_pawams_wesp {
	stwuct acx_headew headew;

	u16 wx_packet_wing_chunk_size;
	u16 tx_packet_wing_chunk_size;

	u8 wx_packet_wing_chunk_num;
	u8 tx_packet_wing_chunk_num;

	u8 pad[2];

	u32 wx_packet_wing_addw;
	u32 tx_packet_wing_addw;

	u32 wx_contwow_addw;
	u32 tx_contwow_addw;

	u32 tx_compwete_addw;
} __packed;

#define TX_MSDU_WIFETIME_MIN       0
#define TX_MSDU_WIFETIME_MAX       3000
#define TX_MSDU_WIFETIME_DEF       512
#define WX_MSDU_WIFETIME_MIN       0
#define WX_MSDU_WIFETIME_MAX       0xFFFFFFFF
#define WX_MSDU_WIFETIME_DEF       512000

stwuct acx_wx_msdu_wifetime {
	stwuct acx_headew headew;

	/*
	 * The maximum amount of time, in TU, befowe the
	 * fiwmwawe discawds the MSDU.
	 */
	u32 wifetime;
} __packed;

/*
 * WX Config Options Tabwe
 * Bit		Definition
 * ===		==========
 * 31:14		Wesewved
 * 13		Copy WX Status - when set, wwite thwee weceive status wowds
 * 	 	to top of wx'd MPDUs.
 * 		When cweawed, do not wwite thwee status wowds (added wev 1.5)
 * 12		Wesewved
 * 11		WX Compwete upon FCS ewwow - when set, give wx compwete
 *	 	intewwupt fow FCS ewwows, aftew the wx fiwtewing, e.g. unicast
 *	 	fwames not to us with FCS ewwow wiww not genewate an intewwupt.
 * 10		SSID Fiwtew Enabwe - When set, the WiWink discawds aww beacon,
 *	        pwobe wequest, and pwobe wesponse fwames with an SSID that does
 *		not match the SSID specified by the host in the STAWT/JOIN
 *		command.
 *		When cweaw, the WiWink weceives fwames with any SSID.
 * 9		Bwoadcast Fiwtew Enabwe - When set, the WiWink discawds aww
 * 	 	bwoadcast fwames. When cweaw, the WiWink weceives aww weceived
 *		bwoadcast fwames.
 * 8:6		Wesewved
 * 5		BSSID Fiwtew Enabwe - When set, the WiWink discawds any fwames
 * 	 	with a BSSID that does not match the BSSID specified by the
 *		host.
 *		When cweaw, the WiWink weceives fwames fwom any BSSID.
 * 4		MAC Addw Fiwtew - When set, the WiWink discawds any fwames
 * 	 	with a destination addwess that does not match the MAC addwess
 *		of the adaptow.
 *		When cweaw, the WiWink weceives fwames destined to any MAC
 *		addwess.
 * 3		Pwomiscuous - When set, the WiWink weceives aww vawid fwames
 * 	 	(i.e., aww fwames that pass the FCS check).
 *		When cweaw, onwy fwames that pass the othew fiwtews specified
 *		awe weceived.
 * 2		FCS - When set, the WiWink incwudes the FCS with the weceived
 *	 	fwame.
 *		When cweawed, the FCS is discawded.
 * 1		PWCP headew - When set, wwite aww data fwom baseband to fwame
 * 	 	buffew incwuding PHY headew.
 * 0		Wesewved - Awways equaw to 0.
 *
 * WX Fiwtew Options Tabwe
 * Bit		Definition
 * ===		==========
 * 31:12		Wesewved - Awways equaw to 0.
 * 11		Association - When set, the WiWink weceives aww association
 * 	 	wewated fwames (association wequest/wesponse, weassocation
 *		wequest/wesponse, and disassociation). When cweaw, these fwames
 *		awe discawded.
 * 10		Auth/De auth - When set, the WiWink weceives aww authentication
 * 	 	and de-authentication fwames. When cweaw, these fwames awe
 *		discawded.
 * 9		Beacon - When set, the WiWink weceives aww beacon fwames.
 * 	 	When cweaw, these fwames awe discawded.
 * 8		Contention Fwee - When set, the WiWink weceives aww contention
 * 	 	fwee fwames.
 *		When cweaw, these fwames awe discawded.
 * 7		Contwow - When set, the WiWink weceives aww contwow fwames.
 * 	 	When cweaw, these fwames awe discawded.
 * 6		Data - When set, the WiWink weceives aww data fwames.
 * 	 	When cweaw, these fwames awe discawded.
 * 5		FCS Ewwow - When set, the WiWink weceives fwames that have FCS
 *	 	ewwows.
 *		When cweaw, these fwames awe discawded.
 * 4		Management - When set, the WiWink weceives aww management
 *		fwames.
 * 	 	When cweaw, these fwames awe discawded.
 * 3		Pwobe Wequest - When set, the WiWink weceives aww pwobe wequest
 * 	 	fwames.
 *		When cweaw, these fwames awe discawded.
 * 2		Pwobe Wesponse - When set, the WiWink weceives aww pwobe
 * 		wesponse fwames.
 *		When cweaw, these fwames awe discawded.
 * 1		WTS/CTS/ACK - When set, the WiWink weceives aww WTS, CTS and ACK
 * 	 	fwames.
 *		When cweaw, these fwames awe discawded.
 * 0		Wsvd Type/Sub Type - When set, the WiWink weceives aww fwames
 * 	 	that have wesewved fwame types and sub types as defined by the
 *		802.11 specification.
 *		When cweaw, these fwames awe discawded.
 */
stwuct acx_wx_config {
	stwuct acx_headew headew;

	u32 config_options;
	u32 fiwtew_options;
} __packed;

enum {
	QOS_AC_BE = 0,
	QOS_AC_BK,
	QOS_AC_VI,
	QOS_AC_VO,
	QOS_HIGHEST_AC_INDEX = QOS_AC_VO,
};

#define MAX_NUM_OF_AC             (QOS_HIGHEST_AC_INDEX+1)
#define FIWST_AC_INDEX            QOS_AC_BE
#define MAX_NUM_OF_802_1d_TAGS    8
#define AC_PAWAMS_MAX_TSID        15
#define MAX_APSD_CONF             0xffff

#define  QOS_TX_HIGH_MIN      (0)
#define  QOS_TX_HIGH_MAX      (100)

#define  QOS_TX_HIGH_BK_DEF   (25)
#define  QOS_TX_HIGH_BE_DEF   (35)
#define  QOS_TX_HIGH_VI_DEF   (35)
#define  QOS_TX_HIGH_VO_DEF   (35)

#define  QOS_TX_WOW_BK_DEF    (15)
#define  QOS_TX_WOW_BE_DEF    (25)
#define  QOS_TX_WOW_VI_DEF    (25)
#define  QOS_TX_WOW_VO_DEF    (25)

stwuct acx_tx_queue_qos_config {
	stwuct acx_headew headew;

	u8 qid;
	u8 pad[3];

	/* Max numbew of bwocks awwowd in the queue */
	u16 high_thweshowd;

	/* Wowest memowy bwocks guawanteed fow this queue */
	u16 wow_thweshowd;
} __packed;

stwuct acx_packet_detection {
	stwuct acx_headew headew;

	u32 thweshowd;
} __packed;


enum acx_swot_type {
	SWOT_TIME_WONG = 0,
	SWOT_TIME_SHOWT = 1,
	DEFAUWT_SWOT_TIME = SWOT_TIME_SHOWT,
	MAX_SWOT_TIMES = 0xFF
};

#define STATION_WONE_INDEX 0

stwuct acx_swot {
	stwuct acx_headew headew;

	u8 wone_index; /* Wesewved */
	u8 swot_time;
	u8 wesewved[6];
} __packed;


#define ACX_MC_ADDWESS_GWOUP_MAX	(8)
#define ACX_MC_ADDWESS_GWOUP_MAX_WEN	(ETH_AWEN * ACX_MC_ADDWESS_GWOUP_MAX)

stwuct acx_dot11_gwp_addw_tbw {
	stwuct acx_headew headew;

	u8 enabwed;
	u8 num_gwoups;
	u8 pad[2];
	u8 mac_tabwe[ACX_MC_ADDWESS_GWOUP_MAX_WEN];
} __packed;


#define  WX_TIMEOUT_PS_POWW_MIN    0
#define  WX_TIMEOUT_PS_POWW_MAX    (200000)
#define  WX_TIMEOUT_PS_POWW_DEF    (15)
#define  WX_TIMEOUT_UPSD_MIN       0
#define  WX_TIMEOUT_UPSD_MAX       (200000)
#define  WX_TIMEOUT_UPSD_DEF       (15)

stwuct acx_wx_timeout {
	stwuct acx_headew headew;

	/*
	 * The wongest time the STA wiww wait to weceive
	 * twaffic fwom the AP aftew a PS-poww has been
	 * twansmitted.
	 */
	u16 ps_poww_timeout;

	/*
	 * The wongest time the STA wiww wait to weceive
	 * twaffic fwom the AP aftew a fwame has been sent
	 * fwom an UPSD enabwed queue.
	 */
	u16 upsd_timeout;
} __packed;

#define WTS_THWESHOWD_MIN              0
#define WTS_THWESHOWD_MAX              4096
#define WTS_THWESHOWD_DEF              2347

stwuct acx_wts_thweshowd {
	stwuct acx_headew headew;

	u16 thweshowd;
	u8 pad[2];
} __packed;

enum ww1251_acx_wow_wssi_type {
	/*
	 * The event is a "Wevew" indication which keeps twiggewing
	 * as wong as the avewage WSSI is bewow the thweshowd.
	 */
	WW1251_ACX_WOW_WSSI_TYPE_WEVEW = 0,

	/*
	 * The event is an "Edge" indication which twiggews
	 * onwy when the WSSI thweshowd is cwossed fwom above.
	 */
	WW1251_ACX_WOW_WSSI_TYPE_EDGE = 1,
};

stwuct acx_wow_wssi {
	stwuct acx_headew headew;

	/*
	 * The thweshowd (in dBm) bewow (ow above aftew wow wssi
	 * indication) which the fiwmwawe genewates an intewwupt to the
	 * host. This pawametew is signed.
	 */
	s8 thweshowd;

	/*
	 * The weight of the cuwwent WSSI sampwe, befowe adding the new
	 * sampwe, that is used to cawcuwate the avewage WSSI.
	 */
	u8 weight;

	/*
	 * The numbew of Beacons/Pwobe wesponse fwames that wiww be
	 * weceived befowe issuing the Wow ow Wegained WSSI event.
	 */
	u8 depth;

	/*
	 * Configuwes how the Wow WSSI Event is twiggewed. Wefew to
	 * enum ww1251_acx_wow_wssi_type fow mowe.
	 */
	u8 type;
} __packed;

stwuct acx_beacon_fiwtew_option {
	stwuct acx_headew headew;

	u8 enabwe;

	/*
	 * The numbew of beacons without the unicast TIM
	 * bit set that the fiwmwawe buffews befowe
	 * signawing the host about weady fwames.
	 * When set to 0 and the fiwtew is enabwed, beacons
	 * without the unicast TIM bit set awe dwopped.
	 */
	u8 max_num_beacons;
	u8 pad[2];
} __packed;

/*
 * ACXBeaconFiwtewEntwy (not 221)
 * Byte Offset     Size (Bytes)    Definition
 * ===========     ============    ==========
 * 0				1               IE identifiew
 * 1               1               Tweatment bit mask
 *
 * ACXBeaconFiwtewEntwy (221)
 * Byte Offset     Size (Bytes)    Definition
 * ===========     ============    ==========
 * 0               1               IE identifiew
 * 1               1               Tweatment bit mask
 * 2               3               OUI
 * 5               1               Type
 * 6               2               Vewsion
 *
 *
 * Tweatment bit mask - The infowmation ewement handwing:
 * bit 0 - The infowmation ewement is compawed and twansfewwed
 * in case of change.
 * bit 1 - The infowmation ewement is twansfewwed to the host
 * with each appeawance ow disappeawance.
 * Note that both bits can be set at the same time.
 */
#define	BEACON_FIWTEW_TABWE_MAX_IE_NUM		       (32)
#define BEACON_FIWTEW_TABWE_MAX_VENDOW_SPECIFIC_IE_NUM (6)
#define BEACON_FIWTEW_TABWE_IE_ENTWY_SIZE	       (2)
#define BEACON_FIWTEW_TABWE_EXTWA_VENDOW_SPECIFIC_IE_SIZE (6)
#define BEACON_FIWTEW_TABWE_MAX_SIZE ((BEACON_FIWTEW_TABWE_MAX_IE_NUM * \
			    BEACON_FIWTEW_TABWE_IE_ENTWY_SIZE) + \
			   (BEACON_FIWTEW_TABWE_MAX_VENDOW_SPECIFIC_IE_NUM * \
			    BEACON_FIWTEW_TABWE_EXTWA_VENDOW_SPECIFIC_IE_SIZE))

#define BEACON_WUWE_PASS_ON_CHANGE                     BIT(0)
#define BEACON_WUWE_PASS_ON_APPEAWANCE                 BIT(1)

#define BEACON_FIWTEW_IE_ID_CHANNEW_SWITCH_ANN         (37)

stwuct acx_beacon_fiwtew_ie_tabwe {
	stwuct acx_headew headew;

	u8 num_ie;
	u8 pad[3];
	u8 tabwe[BEACON_FIWTEW_TABWE_MAX_SIZE];
} __packed;

#define SYNCH_FAIW_DEFAUWT_THWESHOWD    10     /* numbew of beacons */
#define NO_BEACON_DEFAUWT_TIMEOUT       (500) /* in micwoseconds */

stwuct acx_conn_monit_pawams {
	stwuct acx_headew headew;

	u32 synch_faiw_thowd; /* numbew of beacons missed */
	u32 bss_wose_timeout; /* numbew of TU's fwom synch faiw */
} __packed;

enum {
	SG_ENABWE = 0,
	SG_DISABWE,
	SG_SENSE_NO_ACTIVITY,
	SG_SENSE_ACTIVE
};

stwuct acx_bt_wwan_coex {
	stwuct acx_headew headew;

	/*
	 * 0 -> PTA enabwed
	 * 1 -> PTA disabwed
	 * 2 -> sense no active mode, i.e.
	 *      an intewwupt is sent upon
	 *      BT activity.
	 * 3 -> PTA is switched on in wesponse
	 *      to the intewwupt sending.
	 */
	u8 enabwe;
	u8 pad[3];
} __packed;

#define PTA_ANTENNA_TYPE_DEF		  (0)
#define PTA_BT_HP_MAXTIME_DEF		  (2000)
#define PTA_WWAN_HP_MAX_TIME_DEF	  (5000)
#define PTA_SENSE_DISABWE_TIMEW_DEF	  (1350)
#define PTA_PWOTECTIVE_WX_TIME_DEF	  (1500)
#define PTA_PWOTECTIVE_TX_TIME_DEF	  (1500)
#define PTA_TIMEOUT_NEXT_BT_WP_PACKET_DEF (3000)
#define PTA_SIGNAWING_TYPE_DEF		  (1)
#define PTA_AFH_WEVEWAGE_ON_DEF		  (0)
#define PTA_NUMBEW_QUIET_CYCWE_DEF	  (0)
#define PTA_MAX_NUM_CTS_DEF		  (3)
#define PTA_NUMBEW_OF_WWAN_PACKETS_DEF	  (2)
#define PTA_NUMBEW_OF_BT_PACKETS_DEF	  (2)
#define PTA_PWOTECTIVE_WX_TIME_FAST_DEF	  (1500)
#define PTA_PWOTECTIVE_TX_TIME_FAST_DEF	  (3000)
#define PTA_CYCWE_TIME_FAST_DEF		  (8700)
#define PTA_WX_FOW_AVAWANCHE_DEF	  (5)
#define PTA_EWP_HP_DEF			  (0)
#define PTA_ANTI_STAWVE_PEWIOD_DEF	  (500)
#define PTA_ANTI_STAWVE_NUM_CYCWE_DEF	  (4)
#define PTA_AWWOW_PA_SD_DEF		  (1)
#define PTA_TIME_BEFOWE_BEACON_DEF	  (6300)
#define PTA_HPDM_MAX_TIME_DEF		  (1600)
#define PTA_TIME_OUT_NEXT_WWAN_DEF	  (2550)
#define PTA_AUTO_MODE_NO_CTS_DEF	  (0)
#define PTA_BT_HP_WESPECTED_DEF		  (3)
#define PTA_WWAN_WX_MIN_WATE_DEF	  (24)
#define PTA_ACK_MODE_DEF		  (1)

stwuct acx_bt_wwan_coex_pawam {
	stwuct acx_headew headew;

	/*
	 * The minimum wate of a weceived WWAN packet in the STA,
	 * duwing pwotective mode, of which a new BT-HP wequest
	 * duwing this Wx wiww awways be wespected and gain the antenna.
	 */
	u32 min_wate;

	/* Max time the BT HP wiww be wespected. */
	u16 bt_hp_max_time;

	/* Max time the WWAN HP wiww be wespected. */
	u16 wwan_hp_max_time;

	/*
	 * The time between the wast BT activity
	 * and the moment when the sense mode wetuwns
	 * to SENSE_INACTIVE.
	 */
	u16 sense_disabwe_timew;

	/* Time befowe the next BT HP instance */
	u16 wx_time_bt_hp;
	u16 tx_time_bt_hp;

	/* wange: 10-20000    defauwt: 1500 */
	u16 wx_time_bt_hp_fast;
	u16 tx_time_bt_hp_fast;

	/* wange: 2000-65535  defauwt: 8700 */
	u16 wwan_cycwe_fast;

	/* wange: 0 - 15000 (Msec) defauwt: 1000 */
	u16 bt_anti_stawvation_pewiod;

	/* wange 400-10000(Usec) defauwt: 3000 */
	u16 next_bt_wp_packet;

	/* Deafuwt: wowst case fow BT DH5 twaffic */
	u16 wake_up_beacon;

	/* wange: 0-50000(Usec) defauwt: 1050 */
	u16 hp_dm_max_guawd_time;

	/*
	 * This is to pwevent both BT & WWAN antenna
	 * stawvation.
	 * Wange: 100-50000(Usec) defauwt:2550
	 */
	u16 next_wwan_packet;

	/* 0 -> shawed antenna */
	u8 antenna_type;

	/*
	 * 0 -> TI wegacy
	 * 1 -> Pawau
	 */
	u8 signaw_type;

	/*
	 * BT AFH status
	 * 0 -> no AFH
	 * 1 -> fwom dedicated GPIO
	 * 2 -> AFH on (fwom host)
	 */
	u8 afh_wevewage_on;

	/*
	 * The numbew of cycwes duwing which no
	 * TX wiww be sent aftew 1 cycwe of WX
	 * twansaction in pwotective mode
	 */
	u8 quiet_cycwe_num;

	/*
	 * The maximum numbew of CTSs that wiww
	 * be sent fow weceiving WX packet in
	 * pwotective mode
	 */
	u8 max_cts;

	/*
	 * The numbew of WWAN packets
	 * twansfewwed in common mode befowe
	 * switching to BT.
	 */
	u8 wwan_packets_num;

	/*
	 * The numbew of BT packets
	 * twansfewwed in common mode befowe
	 * switching to WWAN.
	 */
	u8 bt_packets_num;

	/* wange: 1-255  defauwt: 5 */
	u8 missed_wx_avawanche;

	/* wange: 0-1    defauwt: 1 */
	u8 wwan_ewp_hp;

	/* wange: 0 - 15  defauwt: 4 */
	u8 bt_anti_stawvation_cycwes;

	u8 ack_mode_duaw_ant;

	/*
	 * Awwow PA_SD assewtion/de-assewtion
	 * duwing enabwed BT activity.
	 */
	u8 pa_sd_enabwe;

	/*
	 * Enabwe/Disabwe PTA in auto mode:
	 * Suppowt Both Active & P.S modes
	 */
	u8 pta_auto_mode_enabwe;

	/* wange: 0 - 20  defauwt: 1 */
	u8 bt_hp_wespected_num;
} __packed;

#define CCA_THWSH_ENABWE_ENEWGY_D       0x140A
#define CCA_THWSH_DISABWE_ENEWGY_D      0xFFEF

stwuct acx_enewgy_detection {
	stwuct acx_headew headew;

	/* The WX Cweaw Channew Assessment thweshowd in the PHY */
	u16 wx_cca_thweshowd;
	u8 tx_enewgy_detection;
	u8 pad;
} __packed;

#define BCN_WX_TIMEOUT_DEF_VAWUE        10000
#define BWOADCAST_WX_TIMEOUT_DEF_VAWUE  20000
#define WX_BWOADCAST_IN_PS_DEF_VAWUE    1
#define CONSECUTIVE_PS_POWW_FAIWUWE_DEF 4

stwuct acx_beacon_bwoadcast {
	stwuct acx_headew headew;

	u16 beacon_wx_timeout;
	u16 bwoadcast_timeout;

	/* Enabwes weceiving of bwoadcast packets in PS mode */
	u8 wx_bwoadcast_in_ps;

	/* Consecutive PS Poww faiwuwes befowe updating the host */
	u8 ps_poww_thweshowd;
	u8 pad[2];
} __packed;

stwuct acx_event_mask {
	stwuct acx_headew headew;

	u32 event_mask;
	u32 high_event_mask; /* Unused */
} __packed;

#define CFG_WX_FCS		BIT(2)
#define CFG_WX_AWW_GOOD		BIT(3)
#define CFG_UNI_FIWTEW_EN	BIT(4)
#define CFG_BSSID_FIWTEW_EN	BIT(5)
#define CFG_MC_FIWTEW_EN	BIT(6)
#define CFG_MC_ADDW0_EN		BIT(7)
#define CFG_MC_ADDW1_EN		BIT(8)
#define CFG_BC_WEJECT_EN	BIT(9)
#define CFG_SSID_FIWTEW_EN	BIT(10)
#define CFG_WX_INT_FCS_EWWOW	BIT(11)
#define CFG_WX_INT_ENCWYPTED	BIT(12)
#define CFG_WX_WW_WX_STATUS	BIT(13)
#define CFG_WX_FIWTEW_NUWTI	BIT(14)
#define CFG_WX_WESEWVE		BIT(15)
#define CFG_WX_TIMESTAMP_TSF	BIT(16)

#define CFG_WX_WSV_EN		BIT(0)
#define CFG_WX_WCTS_ACK		BIT(1)
#define CFG_WX_PWSP_EN		BIT(2)
#define CFG_WX_PWEQ_EN		BIT(3)
#define CFG_WX_MGMT_EN		BIT(4)
#define CFG_WX_FCS_EWWOW	BIT(5)
#define CFG_WX_DATA_EN		BIT(6)
#define CFG_WX_CTW_EN		BIT(7)
#define CFG_WX_CF_EN		BIT(8)
#define CFG_WX_BCN_EN		BIT(9)
#define CFG_WX_AUTH_EN		BIT(10)
#define CFG_WX_ASSOC_EN		BIT(11)

#define SCAN_PASSIVE		BIT(0)
#define SCAN_5GHZ_BAND		BIT(1)
#define SCAN_TWIGGEWED		BIT(2)
#define SCAN_PWIOWITY_HIGH	BIT(3)

stwuct acx_fw_gen_fwame_wates {
	stwuct acx_headew headew;

	u8 tx_ctww_fwame_wate; /* WATE_* */
	u8 tx_ctww_fwame_mod; /* CCK_* ow PBCC_* */
	u8 tx_mgt_fwame_wate;
	u8 tx_mgt_fwame_mod;
} __packed;

/* STA MAC */
stwuct acx_dot11_station_id {
	stwuct acx_headew headew;

	u8 mac[ETH_AWEN];
	u8 pad[2];
} __packed;

stwuct acx_featuwe_config {
	stwuct acx_headew headew;

	u32 options;
	u32 data_fwow_options;
} __packed;

stwuct acx_cuwwent_tx_powew {
	stwuct acx_headew headew;

	u8  cuwwent_tx_powew;
	u8  padding[3];
} __packed;

stwuct acx_dot11_defauwt_key {
	stwuct acx_headew headew;

	u8 id;
	u8 pad[3];
} __packed;

stwuct acx_tsf_info {
	stwuct acx_headew headew;

	u32 cuwwent_tsf_msb;
	u32 cuwwent_tsf_wsb;
	u32 wast_TBTT_msb;
	u32 wast_TBTT_wsb;
	u8 wast_dtim_count;
	u8 pad[3];
} __packed;

enum acx_wake_up_event {
	WAKE_UP_EVENT_BEACON_BITMAP	= 0x01, /* Wake on evewy Beacon*/
	WAKE_UP_EVENT_DTIM_BITMAP	= 0x02,	/* Wake on evewy DTIM*/
	WAKE_UP_EVENT_N_DTIM_BITMAP	= 0x04, /* Wake on evewy Nth DTIM */
	WAKE_UP_EVENT_N_BEACONS_BITMAP	= 0x08, /* Wake on evewy Nth Beacon */
	WAKE_UP_EVENT_BITS_MASK		= 0x0F
};

stwuct acx_wake_up_condition {
	stwuct acx_headew headew;

	u8 wake_up_event; /* Onwy one bit can be set */
	u8 wisten_intewvaw;
	u8 pad[2];
} __packed;

stwuct acx_aid {
	stwuct acx_headew headew;

	/*
	 * To be set when associated with an AP.
	 */
	u16 aid;
	u8 pad[2];
} __packed;

enum acx_pweambwe_type {
	ACX_PWEAMBWE_WONG = 0,
	ACX_PWEAMBWE_SHOWT = 1
};

stwuct acx_pweambwe {
	stwuct acx_headew headew;

	/*
	 * When set, the WiWink twansmits the fwames with a showt pweambwe and
	 * when cweawed, the WiWink twansmits the fwames with a wong pweambwe.
	 */
	u8 pweambwe;
	u8 padding[3];
} __packed;

enum acx_ctspwotect_type {
	CTSPWOTECT_DISABWE = 0,
	CTSPWOTECT_ENABWE = 1
};

stwuct acx_ctspwotect {
	stwuct acx_headew headew;
	u8 ctspwotect;
	u8 padding[3];
} __packed;

stwuct acx_tx_statistics {
	u32 intewnaw_desc_ovewfwow;
}  __packed;

stwuct acx_wx_statistics {
	u32 out_of_mem;
	u32 hdw_ovewfwow;
	u32 hw_stuck;
	u32 dwopped;
	u32 fcs_eww;
	u32 xfw_hint_twig;
	u32 path_weset;
	u32 weset_countew;
} __packed;

stwuct acx_dma_statistics {
	u32 wx_wequested;
	u32 wx_ewwows;
	u32 tx_wequested;
	u32 tx_ewwows;
}  __packed;

stwuct acx_isw_statistics {
	/* host command compwete */
	u32 cmd_cmpwt;

	/* fiqisw() */
	u32 fiqs;

	/* (INT_STS_ND & INT_TWIG_WX_HEADEW) */
	u32 wx_headews;

	/* (INT_STS_ND & INT_TWIG_WX_CMPWT) */
	u32 wx_compwetes;

	/* (INT_STS_ND & INT_TWIG_NO_WX_BUF) */
	u32 wx_mem_ovewfwow;

	/* (INT_STS_ND & INT_TWIG_S_WX_WDY) */
	u32 wx_wdys;

	/* iwqisw() */
	u32 iwqs;

	/* (INT_STS_ND & INT_TWIG_TX_PWOC) */
	u32 tx_pwocs;

	/* (INT_STS_ND & INT_TWIG_DECWYPT_DONE) */
	u32 decwypt_done;

	/* (INT_STS_ND & INT_TWIG_DMA0) */
	u32 dma0_done;

	/* (INT_STS_ND & INT_TWIG_DMA1) */
	u32 dma1_done;

	/* (INT_STS_ND & INT_TWIG_TX_EXC_CMPWT) */
	u32 tx_exch_compwete;

	/* (INT_STS_ND & INT_TWIG_COMMAND) */
	u32 commands;

	/* (INT_STS_ND & INT_TWIG_WX_PWOC) */
	u32 wx_pwocs;

	/* (INT_STS_ND & INT_TWIG_PM_802) */
	u32 hw_pm_mode_changes;

	/* (INT_STS_ND & INT_TWIG_ACKNOWWEDGE) */
	u32 host_acknowwedges;

	/* (INT_STS_ND & INT_TWIG_PM_PCI) */
	u32 pci_pm;

	/* (INT_STS_ND & INT_TWIG_ACM_WAKEUP) */
	u32 wakeups;

	/* (INT_STS_ND & INT_TWIG_WOW_WSSI) */
	u32 wow_wssi;
} __packed;

stwuct acx_wep_statistics {
	/* WEP addwess keys configuwed */
	u32 addw_key_count;

	/* defauwt keys configuwed */
	u32 defauwt_key_count;

	u32 wesewved;

	/* numbew of times that WEP key not found on wookup */
	u32 key_not_found;

	/* numbew of times that WEP key decwyption faiwed */
	u32 decwypt_faiw;

	/* WEP packets decwypted */
	u32 packets;

	/* WEP decwypt intewwupts */
	u32 intewwupt;
} __packed;

#define ACX_MISSED_BEACONS_SPWEAD 10

stwuct acx_pww_statistics {
	/* the amount of entews into powew save mode (both PD & EWP) */
	u32 ps_entew;

	/* the amount of entews into EWP mode */
	u32 ewp_entew;

	/* the amount of missing beacon intewwupts to the host */
	u32 missing_bcns;

	/* the amount of wake on host-access times */
	u32 wake_on_host;

	/* the amount of wake on timew-expiwe */
	u32 wake_on_timew_exp;

	/* the numbew of packets that wewe twansmitted with PS bit set */
	u32 tx_with_ps;

	/* the numbew of packets that wewe twansmitted with PS bit cweaw */
	u32 tx_without_ps;

	/* the numbew of weceived beacons */
	u32 wcvd_beacons;

	/* the numbew of entewing into PowewOn (powew save off) */
	u32 powew_save_off;

	/* the numbew of entwies into powew save mode */
	u16 enabwe_ps;

	/*
	 * the numbew of exits fwom powew save, not incwuding faiwed PS
	 * twansitions
	 */
	u16 disabwe_ps;

	/*
	 * the numbew of times the TSF countew was adjusted because
	 * of dwift
	 */
	u32 fix_tsf_ps;

	/* Gives statistics about the spwead continuous missed beacons.
	 * The 16 WSB awe dedicated fow the PS mode.
	 * The 16 MSB awe dedicated fow the PS mode.
	 * cont_miss_bcns_spwead[0] - singwe missed beacon.
	 * cont_miss_bcns_spwead[1] - two continuous missed beacons.
	 * cont_miss_bcns_spwead[2] - thwee continuous missed beacons.
	 * ...
	 * cont_miss_bcns_spwead[9] - ten and mowe continuous missed beacons.
	*/
	u32 cont_miss_bcns_spwead[ACX_MISSED_BEACONS_SPWEAD];

	/* the numbew of beacons in awake mode */
	u32 wcvd_awake_beacons;
} __packed;

stwuct acx_mic_statistics {
	u32 wx_pkts;
	u32 cawc_faiwuwe;
} __packed;

stwuct acx_aes_statistics {
	u32 encwypt_faiw;
	u32 decwypt_faiw;
	u32 encwypt_packets;
	u32 decwypt_packets;
	u32 encwypt_intewwupt;
	u32 decwypt_intewwupt;
} __packed;

stwuct acx_event_statistics {
	u32 heawt_beat;
	u32 cawibwation;
	u32 wx_mismatch;
	u32 wx_mem_empty;
	u32 wx_poow;
	u32 oom_wate;
	u32 phy_twansmit_ewwow;
	u32 tx_stuck;
} __packed;

stwuct acx_ps_statistics {
	u32 pspoww_timeouts;
	u32 upsd_timeouts;
	u32 upsd_max_sptime;
	u32 upsd_max_aptuwn;
	u32 pspoww_max_aptuwn;
	u32 pspoww_utiwization;
	u32 upsd_utiwization;
} __packed;

stwuct acx_wxpipe_statistics {
	u32 wx_pwep_beacon_dwop;
	u32 descw_host_int_twig_wx_data;
	u32 beacon_buffew_thwes_host_int_twig_wx_data;
	u32 missed_beacon_host_int_twig_wx_data;
	u32 tx_xfw_host_int_twig_wx_data;
} __packed;

stwuct acx_statistics {
	stwuct acx_headew headew;

	stwuct acx_tx_statistics tx;
	stwuct acx_wx_statistics wx;
	stwuct acx_dma_statistics dma;
	stwuct acx_isw_statistics isw;
	stwuct acx_wep_statistics wep;
	stwuct acx_pww_statistics pww;
	stwuct acx_aes_statistics aes;
	stwuct acx_mic_statistics mic;
	stwuct acx_event_statistics event;
	stwuct acx_ps_statistics ps;
	stwuct acx_wxpipe_statistics wxpipe;
} __packed;

#define ACX_MAX_WATE_CWASSES       8
#define ACX_WATE_MASK_UNSPECIFIED  0
#define ACX_WATE_WETWY_WIMIT      10

stwuct acx_wate_cwass {
	u32 enabwed_wates;
	u8 showt_wetwy_wimit;
	u8 wong_wetwy_wimit;
	u8 afwags;
	u8 wesewved;
} __packed;

stwuct acx_wate_powicy {
	stwuct acx_headew headew;

	u32 wate_cwass_cnt;
	stwuct acx_wate_cwass wate_cwass[ACX_MAX_WATE_CWASSES];
} __packed;

stwuct ww1251_acx_memowy {
	__we16 num_stations; /* numbew of STAs to be suppowted. */
	u16 wesewved_1;

	/*
	 * Nmbew of memowy buffews fow the WX mem poow.
	 * The actuaw numbew may be wess if thewe awe
	 * not enough bwocks weft fow the minimum num
	 * of TX ones.
	 */
	u8 wx_mem_bwock_num;
	u8 wesewved_2;
	u8 num_tx_queues; /* Fwom 1 to 16 */
	u8 host_if_options; /* HOST_IF* */
	u8 tx_min_mem_bwock_num;
	u8 num_ssid_pwofiwes;
	__we16 debug_buffew_size;
} __packed;


#define ACX_WX_DESC_MIN                1
#define ACX_WX_DESC_MAX                127
#define ACX_WX_DESC_DEF                32
stwuct ww1251_acx_wx_queue_config {
	u8 num_descs;
	u8 pad;
	u8 type;
	u8 pwiowity;
	__we32 dma_addwess;
} __packed;

#define ACX_TX_DESC_MIN                1
#define ACX_TX_DESC_MAX                127
#define ACX_TX_DESC_DEF                16
stwuct ww1251_acx_tx_queue_config {
    u8 num_descs;
    u8 pad[2];
    u8 attwibutes;
} __packed;

#define MAX_TX_QUEUE_CONFIGS 5
#define MAX_TX_QUEUES 4
stwuct ww1251_acx_config_memowy {
	stwuct acx_headew headew;

	stwuct ww1251_acx_memowy mem_config;
	stwuct ww1251_acx_wx_queue_config wx_queue_config;
	stwuct ww1251_acx_tx_queue_config tx_queue_config[MAX_TX_QUEUE_CONFIGS];
} __packed;

stwuct ww1251_acx_mem_map {
	stwuct acx_headew headew;

	void *code_stawt;
	void *code_end;

	void *wep_defkey_stawt;
	void *wep_defkey_end;

	void *sta_tabwe_stawt;
	void *sta_tabwe_end;

	void *packet_tempwate_stawt;
	void *packet_tempwate_end;

	void *queue_memowy_stawt;
	void *queue_memowy_end;

	void *packet_memowy_poow_stawt;
	void *packet_memowy_poow_end;

	void *debug_buffew1_stawt;
	void *debug_buffew1_end;

	void *debug_buffew2_stawt;
	void *debug_buffew2_end;

	/* Numbew of bwocks FW awwocated fow TX packets */
	u32 num_tx_mem_bwocks;

	/* Numbew of bwocks FW awwocated fow WX packets */
	u32 num_wx_mem_bwocks;
} __packed;


stwuct ww1251_acx_ww_tbtt_and_dtim {

	stwuct acx_headew headew;

	/* Time in TUs between two consecutive beacons */
	u16 tbtt;

	/*
	 * DTIM pewiod
	 * Fow BSS: Numbew of TBTTs in a DTIM pewiod (wange: 1-10)
	 * Fow IBSS: vawue shaww be set to 1
	*/
	u8  dtim;
	u8  padding;
} __packed;

enum ww1251_acx_bet_mode {
	WW1251_ACX_BET_DISABWE = 0,
	WW1251_ACX_BET_ENABWE = 1,
};

stwuct ww1251_acx_bet_enabwe {
	stwuct acx_headew headew;

	/*
	 * Specifies if beacon eawwy tewmination pwoceduwe is enabwed ow
	 * disabwed, see enum ww1251_acx_bet_mode.
	 */
	u8 enabwe;

	/*
	 * Specifies the maximum numbew of consecutive beacons that may be
	 * eawwy tewminated. Aftew this numbew is weached at weast one fuww
	 * beacon must be cowwectwy weceived in FW befowe beacon ET
	 * wesumes. Wange 0 - 255.
	 */
	u8 max_consecutive;

	u8 padding[2];
} __packed;

#define ACX_IPV4_VEWSION 4
#define ACX_IPV6_VEWSION 6
#define ACX_IPV4_ADDW_SIZE 4
stwuct ww1251_acx_awp_fiwtew {
	stwuct acx_headew headew;
	u8 vewsion;	/* The IP vewsion: 4 - IPv4, 6 - IPv6.*/
	u8 enabwe;	/* 1 - AWP fiwtewing is enabwed, 0 - disabwed */
	u8 padding[2];
	u8 addwess[16];	/* The IP addwess used to fiwtew AWP packets.
			   AWP packets that do not match this addwess awe
			   dwopped. When the IP Vewsion is 4, the wast 12
			   bytes of the addwess awe ignowed. */
} __attwibute__((packed));

stwuct ww1251_acx_ac_cfg {
	stwuct acx_headew headew;

	/*
	 * Access Categowy - The TX queue's access categowy
	 * (wefew to AccessCategowy_enum)
	 */
	u8 ac;

	/*
	 * The contention window minimum size (in swots) fow
	 * the access cwass.
	 */
	u8 cw_min;

	/*
	 * The contention window maximum size (in swots) fow
	 * the access cwass.
	 */
	u16 cw_max;

	/* The AIF vawue (in swots) fow the access cwass. */
	u8 aifsn;

	u8 wesewved;

	/* The TX Op Wimit (in micwoseconds) fow the access cwass. */
	u16 txop_wimit;
} __packed;


enum ww1251_acx_channew_type {
	CHANNEW_TYPE_DCF	= 0,
	CHANNEW_TYPE_EDCF	= 1,
	CHANNEW_TYPE_HCCA	= 2,
};

enum ww1251_acx_ps_scheme {
	/* weguwaw ps: simpwe sending of packets */
	WW1251_ACX_PS_SCHEME_WEGACY	= 0,

	/* sending a packet twiggews a unscheduwed apsd downstweam */
	WW1251_ACX_PS_SCHEME_UPSD_TWIGGEW	= 1,

	/* a pspoww packet wiww be sent befowe evewy data packet */
	WW1251_ACX_PS_SCHEME_WEGACY_PSPOWW	= 2,

	/* scheduwed apsd mode */
	WW1251_ACX_PS_SCHEME_SAPSD		= 3,
};

enum ww1251_acx_ack_powicy {
	WW1251_ACX_ACK_POWICY_WEGACY	= 0,
	WW1251_ACX_ACK_POWICY_NO_ACK	= 1,
	WW1251_ACX_ACK_POWICY_BWOCK	= 2,
};

stwuct ww1251_acx_tid_cfg {
	stwuct acx_headew headew;

	/* tx queue id numbew (0-7) */
	u8 queue;

	/* channew access type fow the queue, enum ww1251_acx_channew_type */
	u8 type;

	/* EDCA: ac index (0-3), HCCA: twaffic stweam id (8-15) */
	u8 tsid;

	/* ps scheme of the specified queue, enum ww1251_acx_ps_scheme */
	u8 ps_scheme;

	/* the tx queue ack powicy, enum ww1251_acx_ack_powicy */
	u8 ack_powicy;

	u8 padding[3];

	/* not suppowted */
	u32 apsdconf[2];
} __packed;

/*************************************************************************

    Host Intewwupt Wegistew (WiWink -> Host)

**************************************************************************/

/* WX packet is weady in Xfew buffew #0 */
#define WW1251_ACX_INTW_WX0_DATA      BIT(0)

/* TX wesuwt(s) awe in the TX compwete buffew */
#define WW1251_ACX_INTW_TX_WESUWT	BIT(1)

/* OBSOWETE */
#define WW1251_ACX_INTW_TX_XFW		BIT(2)

/* WX packet is weady in Xfew buffew #1 */
#define WW1251_ACX_INTW_WX1_DATA	BIT(3)

/* Event was entewed to Event MBOX #A */
#define WW1251_ACX_INTW_EVENT_A		BIT(4)

/* Event was entewed to Event MBOX #B */
#define WW1251_ACX_INTW_EVENT_B		BIT(5)

/* OBSOWETE */
#define WW1251_ACX_INTW_WAKE_ON_HOST	BIT(6)

/* Twace message on MBOX #A */
#define WW1251_ACX_INTW_TWACE_A		BIT(7)

/* Twace message on MBOX #B */
#define WW1251_ACX_INTW_TWACE_B		BIT(8)

/* Command pwocessing compwetion */
#define WW1251_ACX_INTW_CMD_COMPWETE	BIT(9)

/* Init sequence is done */
#define WW1251_ACX_INTW_INIT_COMPWETE	BIT(14)

#define WW1251_ACX_INTW_AWW           0xFFFFFFFF

enum {
	ACX_WAKE_UP_CONDITIONS      = 0x0002,
	ACX_MEM_CFG                 = 0x0003,
	ACX_SWOT                    = 0x0004,
	ACX_QUEUE_HEAD              = 0x0005, /* fow MASTEW mode onwy */
	ACX_AC_CFG                  = 0x0007,
	ACX_MEM_MAP                 = 0x0008,
	ACX_AID                     = 0x000A,
	ACX_WADIO_PAWAM             = 0x000B, /* Not used */
	ACX_CFG                     = 0x000C, /* Not used */
	ACX_FW_WEV                  = 0x000D,
	ACX_MEDIUM_USAGE            = 0x000F,
	ACX_WX_CFG                  = 0x0010,
	ACX_TX_QUEUE_CFG            = 0x0011, /* FIXME: onwy used by ww1251 */
	ACX_BSS_IN_PS               = 0x0012, /* fow AP onwy */
	ACX_STATISTICS              = 0x0013, /* Debug API */
	ACX_FEATUWE_CFG             = 0x0015,
	ACX_MISC_CFG                = 0x0017, /* Not used */
	ACX_TID_CFG                 = 0x001A,
	ACX_BEACON_FIWTEW_OPT       = 0x001F,
	ACX_WOW_WSSI                = 0x0020,
	ACX_NOISE_HIST              = 0x0021,
	ACX_HDK_VEWSION             = 0x0022, /* ??? */
	ACX_PD_THWESHOWD            = 0x0023,
	ACX_DATA_PATH_PAWAMS        = 0x0024, /* WO */
	ACX_DATA_PATH_WESP_PAWAMS   = 0x0024, /* WO */
	ACX_CCA_THWESHOWD           = 0x0025,
	ACX_EVENT_MBOX_MASK         = 0x0026,
#ifdef FW_WUNNING_AS_AP
	ACX_DTIM_PEWIOD             = 0x0027, /* fow AP onwy */
#ewse
	ACX_WW_TBTT_AND_DTIM        = 0x0027, /* STA onwy */
#endif
	ACX_ACI_OPTION_CFG          = 0x0029, /* OBSOWETE (fow 1251)*/
	ACX_GPIO_CFG                = 0x002A, /* Not used */
	ACX_GPIO_SET                = 0x002B, /* Not used */
	ACX_PM_CFG                  = 0x002C, /* To Be Documented */
	ACX_CONN_MONIT_PAWAMS       = 0x002D,
	ACX_AVEWAGE_WSSI            = 0x002E, /* Not used */
	ACX_CONS_TX_FAIWUWE         = 0x002F,
	ACX_BCN_DTIM_OPTIONS        = 0x0031,
	ACX_SG_ENABWE               = 0x0032,
	ACX_SG_CFG                  = 0x0033,
	ACX_ANTENNA_DIVEWSITY_CFG   = 0x0035, /* To Be Documented */
	ACX_WOW_SNW		    = 0x0037, /* To Be Documented */
	ACX_BEACON_FIWTEW_TABWE     = 0x0038,
	ACX_AWP_IP_FIWTEW           = 0x0039,
	ACX_WOAMING_STATISTICS_TBW  = 0x003B,
	ACX_WATE_POWICY             = 0x003D,
	ACX_CTS_PWOTECTION          = 0x003E,
	ACX_SWEEP_AUTH              = 0x003F,
	ACX_PWEAMBWE_TYPE	    = 0x0040,
	ACX_EWWOW_CNT               = 0x0041,
	ACX_FW_GEN_FWAME_WATES      = 0x0042,
	ACX_IBSS_FIWTEW		    = 0x0044,
	ACX_SEWVICE_PEWIOD_TIMEOUT  = 0x0045,
	ACX_TSF_INFO                = 0x0046,
	ACX_CONFIG_PS_WMM           = 0x0049,
	ACX_ENABWE_WX_DATA_FIWTEW   = 0x004A,
	ACX_SET_WX_DATA_FIWTEW      = 0x004B,
	ACX_GET_DATA_FIWTEW_STATISTICS = 0x004C,
	ACX_POWEW_WEVEW_TABWE       = 0x004D,
	ACX_BET_ENABWE              = 0x0050,
	DOT11_STATION_ID            = 0x1001,
	DOT11_WX_MSDU_WIFE_TIME     = 0x1004,
	DOT11_CUW_TX_PWW            = 0x100D,
	DOT11_DEFAUWT_KEY           = 0x1010,
	DOT11_WX_DOT11_MODE         = 0x1012,
	DOT11_WTS_THWESHOWD         = 0x1013,
	DOT11_GWOUP_ADDWESS_TBW     = 0x1014,

	MAX_DOT11_IE = DOT11_GWOUP_ADDWESS_TBW,

	MAX_IE = 0xFFFF
};


int ww1251_acx_fwame_wates(stwuct ww1251 *ww, u8 ctww_wate, u8 ctww_mod,
			   u8 mgt_wate, u8 mgt_mod);
int ww1251_acx_station_id(stwuct ww1251 *ww);
int ww1251_acx_defauwt_key(stwuct ww1251 *ww, u8 key_id);
int ww1251_acx_wake_up_conditions(stwuct ww1251 *ww, u8 wake_up_event,
				  u8 wisten_intewvaw);
int ww1251_acx_sweep_auth(stwuct ww1251 *ww, u8 sweep_auth);
int ww1251_acx_fw_vewsion(stwuct ww1251 *ww, chaw *buf, size_t wen);
int ww1251_acx_tx_powew(stwuct ww1251 *ww, int powew);
int ww1251_acx_featuwe_cfg(stwuct ww1251 *ww, u32 data_fwow_options);
int ww1251_acx_mem_map(stwuct ww1251 *ww,
		       stwuct acx_headew *mem_map, size_t wen);
int ww1251_acx_data_path_pawams(stwuct ww1251 *ww,
				stwuct acx_data_path_pawams_wesp *data_path);
int ww1251_acx_wx_msdu_wife_time(stwuct ww1251 *ww, u32 wife_time);
int ww1251_acx_wx_config(stwuct ww1251 *ww, u32 config, u32 fiwtew);
int ww1251_acx_pd_thweshowd(stwuct ww1251 *ww);
int ww1251_acx_swot(stwuct ww1251 *ww, enum acx_swot_type swot_time);
int ww1251_acx_gwoup_addwess_tbw(stwuct ww1251 *ww, boow enabwe,
				 void *mc_wist, u32 mc_wist_wen);
int ww1251_acx_sewvice_pewiod_timeout(stwuct ww1251 *ww);
int ww1251_acx_wts_thweshowd(stwuct ww1251 *ww, u16 wts_thweshowd);
int ww1251_acx_beacon_fiwtew_opt(stwuct ww1251 *ww, boow enabwe_fiwtew);
int ww1251_acx_beacon_fiwtew_tabwe(stwuct ww1251 *ww);
int ww1251_acx_conn_monit_pawams(stwuct ww1251 *ww);
int ww1251_acx_sg_enabwe(stwuct ww1251 *ww);
int ww1251_acx_sg_cfg(stwuct ww1251 *ww);
int ww1251_acx_cca_thweshowd(stwuct ww1251 *ww);
int ww1251_acx_bcn_dtim_options(stwuct ww1251 *ww);
int ww1251_acx_aid(stwuct ww1251 *ww, u16 aid);
int ww1251_acx_event_mbox_mask(stwuct ww1251 *ww, u32 event_mask);
int ww1251_acx_wow_wssi(stwuct ww1251 *ww, s8 thweshowd, u8 weight,
			u8 depth, enum ww1251_acx_wow_wssi_type type);
int ww1251_acx_set_pweambwe(stwuct ww1251 *ww, enum acx_pweambwe_type pweambwe);
int ww1251_acx_cts_pwotect(stwuct ww1251 *ww,
			    enum acx_ctspwotect_type ctspwotect);
int ww1251_acx_statistics(stwuct ww1251 *ww, stwuct acx_statistics *stats);
int ww1251_acx_tsf_info(stwuct ww1251 *ww, u64 *mactime);
int ww1251_acx_wate_powicies(stwuct ww1251 *ww);
int ww1251_acx_mem_cfg(stwuct ww1251 *ww);
int ww1251_acx_ww_tbtt_and_dtim(stwuct ww1251 *ww, u16 tbtt, u8 dtim);
int ww1251_acx_bet_enabwe(stwuct ww1251 *ww, enum ww1251_acx_bet_mode mode,
			  u8 max_consecutive);
int ww1251_acx_awp_ip_fiwtew(stwuct ww1251 *ww, boow enabwe, __be32 addwess);
int ww1251_acx_ac_cfg(stwuct ww1251 *ww, u8 ac, u8 cw_min, u16 cw_max,
		      u8 aifs, u16 txop);
int ww1251_acx_tid_cfg(stwuct ww1251 *ww, u8 queue,
		       enum ww1251_acx_channew_type type,
		       u8 tsid, enum ww1251_acx_ps_scheme ps_scheme,
		       enum ww1251_acx_ack_powicy ack_powicy);

#endif /* __WW1251_ACX_H__ */
