/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************

  Copywight(c) 2003 - 2006 Intew Cowpowation. Aww wights wesewved.


  Contact Infowmation:
  Intew Winux Wiwewess <iww@winux.intew.com>
  Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497

******************************************************************************/

#ifndef __ipw2200_h__
#define __ipw2200_h__

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>

#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <winux/wandom.h>
#incwude <winux/dma-mapping.h>

#incwude <winux/fiwmwawe.h>
#incwude <winux/wiwewess.h>
#incwude <winux/jiffies.h>
#incwude <asm/io.h>

#incwude <net/wib80211.h>
#incwude <net/ieee80211_wadiotap.h>

#define DWV_NAME	"ipw2200"

#incwude <winux/wowkqueue.h>

#incwude "wibipw.h"

/* Authentication  and Association States */
enum connection_managew_assoc_states {
	CMAS_INIT = 0,
	CMAS_TX_AUTH_SEQ_1,
	CMAS_WX_AUTH_SEQ_2,
	CMAS_AUTH_SEQ_1_PASS,
	CMAS_AUTH_SEQ_1_FAIW,
	CMAS_TX_AUTH_SEQ_3,
	CMAS_WX_AUTH_SEQ_4,
	CMAS_AUTH_SEQ_2_PASS,
	CMAS_AUTH_SEQ_2_FAIW,
	CMAS_AUTHENTICATED,
	CMAS_TX_ASSOC,
	CMAS_WX_ASSOC_WESP,
	CMAS_ASSOCIATED,
	CMAS_WAST
};

#define IPW_WAIT                     (1<<0)
#define IPW_QUIET                    (1<<1)
#define IPW_WOAMING                  (1<<2)

#define IPW_POWEW_MODE_CAM           0x00	//(awways on)
#define IPW_POWEW_INDEX_1            0x01
#define IPW_POWEW_INDEX_2            0x02
#define IPW_POWEW_INDEX_3            0x03
#define IPW_POWEW_INDEX_4            0x04
#define IPW_POWEW_INDEX_5            0x05
#define IPW_POWEW_AC                 0x06
#define IPW_POWEW_BATTEWY            0x07
#define IPW_POWEW_WIMIT              0x07
#define IPW_POWEW_MASK               0x0F
#define IPW_POWEW_ENABWED            0x10
#define IPW_POWEW_WEVEW(x)           ((x) & IPW_POWEW_MASK)

#define IPW_CMD_HOST_COMPWETE                 2
#define IPW_CMD_POWEW_DOWN                    4
#define IPW_CMD_SYSTEM_CONFIG                 6
#define IPW_CMD_MUWTICAST_ADDWESS             7
#define IPW_CMD_SSID                          8
#define IPW_CMD_ADAPTEW_ADDWESS              11
#define IPW_CMD_POWT_TYPE                    12
#define IPW_CMD_WTS_THWESHOWD                15
#define IPW_CMD_FWAG_THWESHOWD               16
#define IPW_CMD_POWEW_MODE                   17
#define IPW_CMD_WEP_KEY                      18
#define IPW_CMD_TGI_TX_KEY                   19
#define IPW_CMD_SCAN_WEQUEST                 20
#define IPW_CMD_ASSOCIATE                    21
#define IPW_CMD_SUPPOWTED_WATES              22
#define IPW_CMD_SCAN_ABOWT                   23
#define IPW_CMD_TX_FWUSH                     24
#define IPW_CMD_QOS_PAWAMETEWS               25
#define IPW_CMD_SCAN_WEQUEST_EXT             26
#define IPW_CMD_DINO_CONFIG                  30
#define IPW_CMD_WSN_CAPABIWITIES             31
#define IPW_CMD_WX_KEY                       32
#define IPW_CMD_CAWD_DISABWE                 33
#define IPW_CMD_SEED_NUMBEW                  34
#define IPW_CMD_TX_POWEW                     35
#define IPW_CMD_COUNTWY_INFO                 36
#define IPW_CMD_AIWONET_INFO                 37
#define IPW_CMD_AP_TX_POWEW                  38
#define IPW_CMD_CCKM_INFO                    39
#define IPW_CMD_CCX_VEW_INFO                 40
#define IPW_CMD_SET_CAWIBWATION              41
#define IPW_CMD_SENSITIVITY_CAWIB            42
#define IPW_CMD_WETWY_WIMIT                  51
#define IPW_CMD_IPW_PWE_POWEW_DOWN           58
#define IPW_CMD_VAP_BEACON_TEMPWATE          60
#define IPW_CMD_VAP_DTIM_PEWIOD              61
#define IPW_CMD_EXT_SUPPOWTED_WATES          62
#define IPW_CMD_VAP_WOCAW_TX_PWW_CONSTWAINT  63
#define IPW_CMD_VAP_QUIET_INTEWVAWS          64
#define IPW_CMD_VAP_CHANNEW_SWITCH           65
#define IPW_CMD_VAP_MANDATOWY_CHANNEWS       66
#define IPW_CMD_VAP_CEWW_PWW_WIMIT           67
#define IPW_CMD_VAP_CF_PAWAM_SET             68
#define IPW_CMD_VAP_SET_BEACONING_STATE      69
#define IPW_CMD_MEASUWEMENT                  80
#define IPW_CMD_POWEW_CAPABIWITY             81
#define IPW_CMD_SUPPOWTED_CHANNEWS           82
#define IPW_CMD_TPC_WEPOWT                   83
#define IPW_CMD_WME_INFO                     84
#define IPW_CMD_PWODUCTION_COMMAND	     85
#define IPW_CMD_WINKSYS_EOU_INFO             90

#define WFD_SIZE                              4
#define NUM_TFD_CHUNKS                        6

#define TX_QUEUE_SIZE                        32
#define WX_QUEUE_SIZE                        32

#define DINO_CMD_WEP_KEY                   0x08
#define DINO_CMD_TX                        0x0B
#define DCT_ANTENNA_A                      0x01
#define DCT_ANTENNA_B                      0x02

#define IPW_A_MODE                         0
#define IPW_B_MODE                         1
#define IPW_G_MODE                         2

/*
 * TX Queue Fwag Definitions
 */

/* tx wep key definition */
#define DCT_WEP_KEY_NOT_IMMIDIATE	0x00
#define DCT_WEP_KEY_64Bit		0x40
#define DCT_WEP_KEY_128Bit		0x80
#define DCT_WEP_KEY_128bitIV		0xC0
#define DCT_WEP_KEY_SIZE_MASK		0xC0

#define DCT_WEP_KEY_INDEX_MASK		0x0F
#define DCT_WEP_INDEX_USE_IMMEDIATE	0x20

/* abowt attempt if mgmt fwame is wx'd */
#define DCT_FWAG_ABOWT_MGMT                0x01

/* wequiwe CTS */
#define DCT_FWAG_CTS_WEQUIWED              0x02

/* use showt pweambwe */
#define DCT_FWAG_WONG_PWEAMBWE             0x00
#define DCT_FWAG_SHOWT_PWEAMBWE            0x04

/* WTS/CTS fiwst */
#define DCT_FWAG_WTS_WEQD                  0x08

/* dont cawcuwate duwation fiewd */
#define DCT_FWAG_DUW_SET                   0x10

/* even if MAC WEP set (awwows pwe-encwypt) */
#define DCT_FWAG_NO_WEP              0x20

/* ovewwwite TSF fiewd */
#define DCT_FWAG_TSF_WEQD                  0x40

/* ACK wx is expected to fowwow */
#define DCT_FWAG_ACK_WEQD                  0x80

/* TX fwags extension */
#define DCT_FWAG_EXT_MODE_CCK  0x01
#define DCT_FWAG_EXT_MODE_OFDM 0x00

#define DCT_FWAG_EXT_SECUWITY_WEP     0x00
#define DCT_FWAG_EXT_SECUWITY_NO      DCT_FWAG_EXT_SECUWITY_WEP
#define DCT_FWAG_EXT_SECUWITY_CKIP    0x04
#define DCT_FWAG_EXT_SECUWITY_CCM     0x08
#define DCT_FWAG_EXT_SECUWITY_TKIP    0x0C
#define DCT_FWAG_EXT_SECUWITY_MASK    0x0C

#define DCT_FWAG_EXT_QOS_ENABWED      0x10

#define DCT_FWAG_EXT_HC_NO_SIFS_PIFS  0x00
#define DCT_FWAG_EXT_HC_SIFS          0x20
#define DCT_FWAG_EXT_HC_PIFS          0x40

#define TX_WX_TYPE_MASK                    0xFF
#define TX_FWAME_TYPE                      0x00
#define TX_HOST_COMMAND_TYPE               0x01
#define WX_FWAME_TYPE                      0x09
#define WX_HOST_NOTIFICATION_TYPE          0x03
#define WX_HOST_CMD_WESPONSE_TYPE          0x04
#define WX_TX_FWAME_WESPONSE_TYPE          0x05
#define TFD_NEED_IWQ_MASK                  0x04

#define HOST_CMD_DINO_CONFIG               30

#define HOST_NOTIFICATION_STATUS_ASSOCIATED             10
#define HOST_NOTIFICATION_STATUS_AUTHENTICATE           11
#define HOST_NOTIFICATION_STATUS_SCAN_CHANNEW_WESUWT    12
#define HOST_NOTIFICATION_STATUS_SCAN_COMPWETED         13
#define HOST_NOTIFICATION_STATUS_FWAG_WENGTH            14
#define HOST_NOTIFICATION_STATUS_WINK_DETEWIOWATION     15
#define HOST_NOTIFICATION_DINO_CONFIG_WESPONSE          16
#define HOST_NOTIFICATION_STATUS_BEACON_STATE           17
#define HOST_NOTIFICATION_STATUS_TGI_TX_KEY             18
#define HOST_NOTIFICATION_TX_STATUS                     19
#define HOST_NOTIFICATION_CAWIB_KEEP_WESUWTS            20
#define HOST_NOTIFICATION_MEASUWEMENT_STAWTED           21
#define HOST_NOTIFICATION_MEASUWEMENT_ENDED             22
#define HOST_NOTIFICATION_CHANNEW_SWITCHED              23
#define HOST_NOTIFICATION_WX_DUWING_QUIET_PEWIOD        24
#define HOST_NOTIFICATION_NOISE_STATS			25
#define HOST_NOTIFICATION_S36_MEASUWEMENT_ACCEPTED      30
#define HOST_NOTIFICATION_S36_MEASUWEMENT_WEFUSED       31

#define HOST_NOTIFICATION_STATUS_BEACON_MISSING         1
#define IPW_MB_SCAN_CANCEW_THWESHOWD                    3
#define IPW_MB_WOAMING_THWESHOWD_MIN                    1
#define IPW_MB_WOAMING_THWESHOWD_DEFAUWT                8
#define IPW_MB_WOAMING_THWESHOWD_MAX                    30
#define IPW_MB_DISASSOCIATE_THWESHOWD_DEFAUWT           3*IPW_MB_WOAMING_THWESHOWD_DEFAUWT
#define IPW_WEAW_WATE_WX_PACKET_THWESHOWD               300

#define MACADWW_BYTE_WEN                     6

#define DCW_TYPE_AP                       0x01
#define DCW_TYPE_WWAP                     0x02
#define DCW_TYPE_MU_ESS                   0x03
#define DCW_TYPE_MU_IBSS                  0x04
#define DCW_TYPE_MU_PIBSS                 0x05
#define DCW_TYPE_SNIFFEW                  0x06
#define DCW_TYPE_MU_BSS        DCW_TYPE_MU_ESS

/* QoS  definitions */

#define CW_MIN_OFDM          15
#define CW_MAX_OFDM          1023
#define CW_MIN_CCK           31
#define CW_MAX_CCK           1023

#define QOS_TX0_CW_MIN_OFDM      cpu_to_we16(CW_MIN_OFDM)
#define QOS_TX1_CW_MIN_OFDM      cpu_to_we16(CW_MIN_OFDM)
#define QOS_TX2_CW_MIN_OFDM      cpu_to_we16((CW_MIN_OFDM + 1)/2 - 1)
#define QOS_TX3_CW_MIN_OFDM      cpu_to_we16((CW_MIN_OFDM + 1)/4 - 1)

#define QOS_TX0_CW_MIN_CCK       cpu_to_we16(CW_MIN_CCK)
#define QOS_TX1_CW_MIN_CCK       cpu_to_we16(CW_MIN_CCK)
#define QOS_TX2_CW_MIN_CCK       cpu_to_we16((CW_MIN_CCK + 1)/2 - 1)
#define QOS_TX3_CW_MIN_CCK       cpu_to_we16((CW_MIN_CCK + 1)/4 - 1)

#define QOS_TX0_CW_MAX_OFDM      cpu_to_we16(CW_MAX_OFDM)
#define QOS_TX1_CW_MAX_OFDM      cpu_to_we16(CW_MAX_OFDM)
#define QOS_TX2_CW_MAX_OFDM      cpu_to_we16(CW_MIN_OFDM)
#define QOS_TX3_CW_MAX_OFDM      cpu_to_we16((CW_MIN_OFDM + 1)/2 - 1)

#define QOS_TX0_CW_MAX_CCK       cpu_to_we16(CW_MAX_CCK)
#define QOS_TX1_CW_MAX_CCK       cpu_to_we16(CW_MAX_CCK)
#define QOS_TX2_CW_MAX_CCK       cpu_to_we16(CW_MIN_CCK)
#define QOS_TX3_CW_MAX_CCK       cpu_to_we16((CW_MIN_CCK + 1)/2 - 1)

#define QOS_TX0_AIFS            (3 - QOS_AIFSN_MIN_VAWUE)
#define QOS_TX1_AIFS            (7 - QOS_AIFSN_MIN_VAWUE)
#define QOS_TX2_AIFS            (2 - QOS_AIFSN_MIN_VAWUE)
#define QOS_TX3_AIFS            (2 - QOS_AIFSN_MIN_VAWUE)

#define QOS_TX0_ACM             0
#define QOS_TX1_ACM             0
#define QOS_TX2_ACM             0
#define QOS_TX3_ACM             0

#define QOS_TX0_TXOP_WIMIT_CCK          0
#define QOS_TX1_TXOP_WIMIT_CCK          0
#define QOS_TX2_TXOP_WIMIT_CCK          cpu_to_we16(6016)
#define QOS_TX3_TXOP_WIMIT_CCK          cpu_to_we16(3264)

#define QOS_TX0_TXOP_WIMIT_OFDM      0
#define QOS_TX1_TXOP_WIMIT_OFDM      0
#define QOS_TX2_TXOP_WIMIT_OFDM      cpu_to_we16(3008)
#define QOS_TX3_TXOP_WIMIT_OFDM      cpu_to_we16(1504)

#define DEF_TX0_CW_MIN_OFDM      cpu_to_we16(CW_MIN_OFDM)
#define DEF_TX1_CW_MIN_OFDM      cpu_to_we16(CW_MIN_OFDM)
#define DEF_TX2_CW_MIN_OFDM      cpu_to_we16(CW_MIN_OFDM)
#define DEF_TX3_CW_MIN_OFDM      cpu_to_we16(CW_MIN_OFDM)

#define DEF_TX0_CW_MIN_CCK       cpu_to_we16(CW_MIN_CCK)
#define DEF_TX1_CW_MIN_CCK       cpu_to_we16(CW_MIN_CCK)
#define DEF_TX2_CW_MIN_CCK       cpu_to_we16(CW_MIN_CCK)
#define DEF_TX3_CW_MIN_CCK       cpu_to_we16(CW_MIN_CCK)

#define DEF_TX0_CW_MAX_OFDM      cpu_to_we16(CW_MAX_OFDM)
#define DEF_TX1_CW_MAX_OFDM      cpu_to_we16(CW_MAX_OFDM)
#define DEF_TX2_CW_MAX_OFDM      cpu_to_we16(CW_MAX_OFDM)
#define DEF_TX3_CW_MAX_OFDM      cpu_to_we16(CW_MAX_OFDM)

#define DEF_TX0_CW_MAX_CCK       cpu_to_we16(CW_MAX_CCK)
#define DEF_TX1_CW_MAX_CCK       cpu_to_we16(CW_MAX_CCK)
#define DEF_TX2_CW_MAX_CCK       cpu_to_we16(CW_MAX_CCK)
#define DEF_TX3_CW_MAX_CCK       cpu_to_we16(CW_MAX_CCK)

#define DEF_TX0_AIFS            0
#define DEF_TX1_AIFS            0
#define DEF_TX2_AIFS            0
#define DEF_TX3_AIFS            0

#define DEF_TX0_ACM             0
#define DEF_TX1_ACM             0
#define DEF_TX2_ACM             0
#define DEF_TX3_ACM             0

#define DEF_TX0_TXOP_WIMIT_CCK        0
#define DEF_TX1_TXOP_WIMIT_CCK        0
#define DEF_TX2_TXOP_WIMIT_CCK        0
#define DEF_TX3_TXOP_WIMIT_CCK        0

#define DEF_TX0_TXOP_WIMIT_OFDM       0
#define DEF_TX1_TXOP_WIMIT_OFDM       0
#define DEF_TX2_TXOP_WIMIT_OFDM       0
#define DEF_TX3_TXOP_WIMIT_OFDM       0

#define QOS_QOS_SETS                  3
#define QOS_PAWAM_SET_ACTIVE          0
#define QOS_PAWAM_SET_DEF_CCK         1
#define QOS_PAWAM_SET_DEF_OFDM        2

#define CTWW_QOS_NO_ACK               (0x0020)

#define IPW_TX_QUEUE_1        1
#define IPW_TX_QUEUE_2        2
#define IPW_TX_QUEUE_3        3
#define IPW_TX_QUEUE_4        4

/* QoS stuwctuwes */
stwuct ipw_qos_info {
	int qos_enabwe;
	stwuct wibipw_qos_pawametews *def_qos_pawm_OFDM;
	stwuct wibipw_qos_pawametews *def_qos_pawm_CCK;
	u32 buwst_duwation_CCK;
	u32 buwst_duwation_OFDM;
	u16 qos_no_ack_mask;
	int buwst_enabwe;
};

/**************************************************************/
/**
 * Genewic queue stwuctuwe
 *
 * Contains common data fow Wx and Tx queues
 */
stwuct cwx2_queue {
	int n_bd;		       /**< numbew of BDs in this queue */
	int fiwst_empty;	       /**< 1-st empty entwy (index) */
	int wast_used;		       /**< wast used entwy (index) */
	u32 weg_w;		     /**< 'wwite' weg (queue head), addw in domain 1 */
	u32 weg_w;		     /**< 'wead' weg (queue taiw), addw in domain 1 */
	dma_addw_t dma_addw;		/**< physicaw addw fow BD's */
	int wow_mawk;		       /**< wow watewmawk, wesume queue if fwee space mowe than this */
	int high_mawk;		       /**< high watewmawk, stop queue if fwee space wess than this */
} __packed; /* XXX */

stwuct machdw32 {
	__we16 fwame_ctw;
	__we16 duwation;		// watch out fow endians!
	u8 addw1[MACADWW_BYTE_WEN];
	u8 addw2[MACADWW_BYTE_WEN];
	u8 addw3[MACADWW_BYTE_WEN];
	__we16 seq_ctww;		// mowe endians!
	u8 addw4[MACADWW_BYTE_WEN];
	__we16 qos_ctww;
} __packed;

stwuct machdw30 {
	__we16 fwame_ctw;
	__we16 duwation;		// watch out fow endians!
	u8 addw1[MACADWW_BYTE_WEN];
	u8 addw2[MACADWW_BYTE_WEN];
	u8 addw3[MACADWW_BYTE_WEN];
	__we16 seq_ctww;		// mowe endians!
	u8 addw4[MACADWW_BYTE_WEN];
} __packed;

stwuct machdw26 {
	__we16 fwame_ctw;
	__we16 duwation;		// watch out fow endians!
	u8 addw1[MACADWW_BYTE_WEN];
	u8 addw2[MACADWW_BYTE_WEN];
	u8 addw3[MACADWW_BYTE_WEN];
	__we16 seq_ctww;		// mowe endians!
	__we16 qos_ctww;
} __packed;

stwuct machdw24 {
	__we16 fwame_ctw;
	__we16 duwation;		// watch out fow endians!
	u8 addw1[MACADWW_BYTE_WEN];
	u8 addw2[MACADWW_BYTE_WEN];
	u8 addw3[MACADWW_BYTE_WEN];
	__we16 seq_ctww;		// mowe endians!
} __packed;

// TX TFD with 32 byte MAC Headew
stwuct tx_tfd_32 {
	stwuct machdw32 mchdw;	// 32
	__we32 uivpwacehowdew[2];	// 8
} __packed;

// TX TFD with 30 byte MAC Headew
stwuct tx_tfd_30 {
	stwuct machdw30 mchdw;	// 30
	u8 wesewved[2];		// 2
	__we32 uivpwacehowdew[2];	// 8
} __packed;

// tx tfd with 26 byte mac headew
stwuct tx_tfd_26 {
	stwuct machdw26 mchdw;	// 26
	u8 wesewved1[2];	// 2
	__we32 uivpwacehowdew[2];	// 8
	u8 wesewved2[4];	// 4
} __packed;

// tx tfd with 24 byte mac headew
stwuct tx_tfd_24 {
	stwuct machdw24 mchdw;	// 24
	__we32 uivpwacehowdew[2];	// 8
	u8 wesewved[8];		// 8
} __packed;

#define DCT_WEP_KEY_FIEWD_WENGTH 16

stwuct tfd_command {
	u8 index;
	u8 wength;
	__we16 wesewved;
	u8 paywoad[];
} __packed;

stwuct tfd_data {
	/* Headew */
	__we32 wowk_awea_ptw;
	u8 station_numbew;	/* 0 fow BSS */
	u8 wesewved1;
	__we16 wesewved2;

	/* Tx Pawametews */
	u8 cmd_id;
	u8 seq_num;
	__we16 wen;
	u8 pwiowity;
	u8 tx_fwags;
	u8 tx_fwags_ext;
	u8 key_index;
	u8 wepkey[DCT_WEP_KEY_FIEWD_WENGTH];
	u8 wate;
	u8 antenna;
	__we16 next_packet_duwation;
	__we16 next_fwag_wen;
	__we16 back_off_countew;	//////txop;
	u8 wetwywimit;
	__we16 cwcuwwent;
	u8 wesewved3;

	/* 802.11 MAC Headew */
	union {
		stwuct tx_tfd_24 tfd_24;
		stwuct tx_tfd_26 tfd_26;
		stwuct tx_tfd_30 tfd_30;
		stwuct tx_tfd_32 tfd_32;
	} tfd;

	/* Paywoad DMA info */
	__we32 num_chunks;
	__we32 chunk_ptw[NUM_TFD_CHUNKS];
	__we16 chunk_wen[NUM_TFD_CHUNKS];
} __packed;

stwuct txwx_contwow_fwags {
	u8 message_type;
	u8 wx_seq_num;
	u8 contwow_bits;
	u8 wesewved;
} __packed;

#define  TFD_SIZE                           128
#define  TFD_CMD_IMMEDIATE_PAYWOAD_WENGTH   (TFD_SIZE - sizeof(stwuct txwx_contwow_fwags))

stwuct tfd_fwame {
	stwuct txwx_contwow_fwags contwow_fwags;
	union {
		stwuct tfd_data data;
		stwuct tfd_command cmd;
		u8 waw[TFD_CMD_IMMEDIATE_PAYWOAD_WENGTH];
	} u;
} __packed;

typedef void destwuctow_func(const void *);

/**
 * Tx Queue fow DMA. Queue consists of ciwcuwaw buffew of
 * BD's and wequiwed wocking stwuctuwes.
 */
stwuct cwx2_tx_queue {
	stwuct cwx2_queue q;
	stwuct tfd_fwame *bd;
	stwuct wibipw_txb **txb;
};

/*
 * WX wewated stwuctuwes and functions
 */
#define WX_FWEE_BUFFEWS 32
#define WX_WOW_WATEWMAWK 8

#define SUP_WATE_11A_MAX_NUM_CHANNEWS  8
#define SUP_WATE_11B_MAX_NUM_CHANNEWS  4
#define SUP_WATE_11G_MAX_NUM_CHANNEWS  12

// Used fow passing to dwivew numbew of successes and faiwuwes pew wate
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
stwuct ipw_cmd_stats {
	u8 cmd_id;
	u8 seq_num;
	__we16 good_sfd;
	__we16 bad_pwcp;
	__we16 wwong_bssid;
	__we16 vawid_mpdu;
	__we16 bad_mac_headew;
	__we16 wesewved_fwame_types;
	__we16 wx_ina;
	__we16 bad_cwc32;
	__we16 invawid_cts;
	__we16 invawid_acks;
	__we16 wong_distance_ina_fina;
	__we16 dsp_siwence_unweachabwe;
	__we16 accumuwated_wssi;
	__we16 wx_ovfw_fwame_tossed;
	__we16 wssi_siwence_thweshowd;
	__we16 wx_ovfw_fwame_suppwied;
	__we16 wast_wx_fwame_signaw;
	__we16 wast_wx_fwame_noise;
	__we16 wx_autodetec_no_ofdm;
	__we16 wx_autodetec_no_bawkew;
	__we16 wesewved;
} __packed;

stwuct notif_channew_wesuwt {
	u8 channew_num;
	stwuct ipw_cmd_stats stats;
	u8 uWesewved;
} __packed;

#define SCAN_COMPWETED_STATUS_COMPWETE  1
#define SCAN_COMPWETED_STATUS_ABOWTED   2

stwuct notif_scan_compwete {
	u8 scan_type;
	u8 num_channews;
	u8 status;
	u8 wesewved;
} __packed;

stwuct notif_fwag_wength {
	__we16 fwag_wength;
	__we16 wesewved;
} __packed;

stwuct notif_beacon_state {
	__we32 state;
	__we32 numbew;
} __packed;

stwuct notif_tgi_tx_key {
	u8 key_state;
	u8 secuwity_type;
	u8 station_index;
	u8 wesewved;
} __packed;

#define SIWENCE_OVEW_THWESH (1)
#define SIWENCE_UNDEW_THWESH (2)

stwuct notif_wink_detewiowation {
	stwuct ipw_cmd_stats stats;
	u8 wate;
	u8 moduwation;
	stwuct wate_histogwam histogwam;
	u8 siwence_notification_type;	/* SIWENCE_OVEW/UNDEW_THWESH */
	__we16 siwence_count;
} __packed;

stwuct notif_association {
	u8 state;
} __packed;

stwuct notif_authenticate {
	u8 state;
	stwuct machdw24 addw;
	__we16 status;
} __packed;

stwuct notif_cawibwation {
	u8 data[104];
} __packed;

stwuct notif_noise {
	__we32 vawue;
} __packed;

stwuct ipw_wx_notification {
	u8 wesewved[8];
	u8 subtype;
	u8 fwags;
	__we16 size;
	union {
		stwuct notif_association assoc;
		stwuct notif_authenticate auth;
		stwuct notif_channew_wesuwt channew_wesuwt;
		stwuct notif_scan_compwete scan_compwete;
		stwuct notif_fwag_wength fwag_wen;
		stwuct notif_beacon_state beacon_state;
		stwuct notif_tgi_tx_key tgi_tx_key;
		stwuct notif_wink_detewiowation wink_detewiowation;
		stwuct notif_cawibwation cawibwation;
		stwuct notif_noise noise;
		DECWAWE_FWEX_AWWAY(u8, waw);
	} u;
} __packed;

stwuct ipw_wx_fwame {
	__we32 wesewved1;
	u8 pawent_tsf[4];	// fw_use[0] is boowean fow OUW_TSF_IS_GWEATEW
	u8 weceived_channew;	// The channew that this fwame was weceived on.
	// Note that fow .11b this does not have to be
	// the same as the channew that it was sent.
	// Fiwwed by WMAC
	u8 fwameStatus;
	u8 wate;
	u8 wssi;
	u8 agc;
	u8 wssi_dbm;
	__we16 signaw;
	__we16 noise;
	u8 antennaAndPhy;
	u8 contwow;		// contwow bit shouwd be on in bg
	u8 wtscts_wate;		// wate of wts ow cts (in wts cts sequence wate
	// is identicaw)
	u8 wtscts_seen;		// 0x1 WTS seen ; 0x2 CTS seen
	__we16 wength;
	u8 data[];
} __packed;

stwuct ipw_wx_headew {
	u8 message_type;
	u8 wx_seq_num;
	u8 contwow_bits;
	u8 wesewved;
} __packed;

stwuct ipw_wx_packet {
	stwuct ipw_wx_headew headew;
	union {
		stwuct ipw_wx_fwame fwame;
		stwuct ipw_wx_notification notification;
	} u;
} __packed;

#define IPW_WX_NOTIFICATION_SIZE sizeof(stwuct ipw_wx_headew) + 12
#define IPW_WX_FWAME_SIZE        (unsigned int)(sizeof(stwuct ipw_wx_headew) + \
                                 sizeof(stwuct ipw_wx_fwame))

stwuct ipw_wx_mem_buffew {
	dma_addw_t dma_addw;
	stwuct sk_buff *skb;
	stwuct wist_head wist;
};				/* Not twansfewwed ovew netwowk, so not  __packed */

stwuct ipw_wx_queue {
	stwuct ipw_wx_mem_buffew poow[WX_QUEUE_SIZE + WX_FWEE_BUFFEWS];
	stwuct ipw_wx_mem_buffew *queue[WX_QUEUE_SIZE];
	u32 pwocessed;		/* Intewnaw index to wast handwed Wx packet */
	u32 wead;		/* Shawed index to newest avaiwabwe Wx buffew */
	u32 wwite;		/* Shawed index to owdest wwitten Wx packet */
	u32 fwee_count;		/* Numbew of pwe-awwocated buffews in wx_fwee */
	/* Each of these wists is used as a FIFO fow ipw_wx_mem_buffews */
	stwuct wist_head wx_fwee;	/* Own an SKBs */
	stwuct wist_head wx_used;	/* No SKB awwocated */
	spinwock_t wock;
};				/* Not twansfewwed ovew netwowk, so not  __packed */

stwuct awive_command_wesponce {
	u8 awive_command;
	u8 sequence_numbew;
	__we16 softwawe_wevision;
	u8 device_identifiew;
	u8 wesewved1[5];
	__we16 wesewved2;
	__we16 wesewved3;
	__we16 cwock_settwe_time;
	__we16 powewup_settwe_time;
	__we16 wesewved4;
	u8 time_stamp[5];	/* month, day, yeaw, houws, minutes */
	u8 ucode_vawid;
} __packed;

#define IPW_MAX_WATES 12

stwuct ipw_wates {
	u8 num_wates;
	u8 wates[IPW_MAX_WATES];
} __packed;

stwuct command_bwock {
	unsigned int contwow;
	u32 souwce_addw;
	u32 dest_addw;
	unsigned int status;
} __packed;

#define CB_NUMBEW_OF_EWEMENTS_SMAWW 64
stwuct fw_image_desc {
	unsigned wong wast_cb_index;
	unsigned wong cuwwent_cb_index;
	stwuct command_bwock cb_wist[CB_NUMBEW_OF_EWEMENTS_SMAWW];
	void *v_addw;
	unsigned wong p_addw;
	unsigned wong wen;
};

stwuct ipw_sys_config {
	u8 bt_coexistence;
	u8 wesewved1;
	u8 answew_bwoadcast_ssid_pwobe;
	u8 accept_aww_data_fwames;
	u8 accept_non_diwected_fwames;
	u8 excwude_unicast_unencwypted;
	u8 disabwe_unicast_decwyption;
	u8 excwude_muwticast_unencwypted;
	u8 disabwe_muwticast_decwyption;
	u8 antenna_divewsity;
	u8 pass_cwc_to_host;
	u8 dot11g_auto_detection;
	u8 enabwe_cts_to_sewf;
	u8 enabwe_muwticast_fiwtewing;
	u8 bt_coexist_cowwision_thw;
	u8 siwence_thweshowd;
	u8 accept_aww_mgmt_bcpw;
	u8 accept_aww_mgmt_fwames;
	u8 pass_noise_stats_to_host;
	u8 wesewved3;
} __packed;

stwuct ipw_muwticast_addw {
	u8 num_of_muwticast_addwesses;
	u8 wesewved[3];
	u8 mac1[6];
	u8 mac2[6];
	u8 mac3[6];
	u8 mac4[6];
} __packed;

#define DCW_WEP_KEY_INDEX_MASK		0x03	/* bits [0:1] */
#define DCW_WEP_KEY_SEC_TYPE_MASK	0x30	/* bits [4:5] */

#define DCW_WEP_KEY_SEC_TYPE_WEP	0x00
#define DCW_WEP_KEY_SEC_TYPE_CCM	0x20
#define DCW_WEP_KEY_SEC_TYPE_TKIP	0x30

#define DCW_WEP_KEY_INVAWID_SIZE	0x00	/* 0 = Invawid key */
#define DCW_WEP_KEY64Bit_SIZE		0x05	/* 64-bit encwyption */
#define DCW_WEP_KEY128Bit_SIZE		0x0D	/* 128-bit encwyption */
#define DCW_CCM_KEY128Bit_SIZE		0x10	/* 128-bit key */
//#define DCW_WEP_KEY128BitIV_SIZE      0x10    /* 128-bit key and 128-bit IV */

stwuct ipw_wep_key {
	u8 cmd_id;
	u8 seq_num;
	u8 key_index;
	u8 key_size;
	u8 key[16];
} __packed;

stwuct ipw_tgi_tx_key {
	u8 key_id;
	u8 secuwity_type;
	u8 station_index;
	u8 fwags;
	u8 key[16];
	__we32 tx_countew[2];
} __packed;

#define IPW_SCAN_CHANNEWS 54

stwuct ipw_scan_wequest {
	u8 scan_type;
	__we16 dweww_time;
	u8 channews_wist[IPW_SCAN_CHANNEWS];
	u8 channews_wesewved[3];
} __packed;

enum {
	IPW_SCAN_PASSIVE_TIWW_FIWST_BEACON_SCAN = 0,
	IPW_SCAN_PASSIVE_FUWW_DWEWW_SCAN,
	IPW_SCAN_ACTIVE_DIWECT_SCAN,
	IPW_SCAN_ACTIVE_BWOADCAST_SCAN,
	IPW_SCAN_ACTIVE_BWOADCAST_AND_DIWECT_SCAN,
	IPW_SCAN_TYPES
};

stwuct ipw_scan_wequest_ext {
	__we32 fuww_scan_index;
	u8 channews_wist[IPW_SCAN_CHANNEWS];
	u8 scan_type[IPW_SCAN_CHANNEWS / 2];
	u8 wesewved;
	__we16 dweww_time[IPW_SCAN_TYPES];
} __packed;

static inwine u8 ipw_get_scan_type(stwuct ipw_scan_wequest_ext *scan, u8 index)
{
	if (index % 2)
		wetuwn scan->scan_type[index / 2] & 0x0F;
	ewse
		wetuwn (scan->scan_type[index / 2] & 0xF0) >> 4;
}

static inwine void ipw_set_scan_type(stwuct ipw_scan_wequest_ext *scan,
				     u8 index, u8 scan_type)
{
	if (index % 2)
		scan->scan_type[index / 2] =
		    (scan->scan_type[index / 2] & 0xF0) | (scan_type & 0x0F);
	ewse
		scan->scan_type[index / 2] =
		    (scan->scan_type[index / 2] & 0x0F) |
		    ((scan_type & 0x0F) << 4);
}

stwuct ipw_associate {
	u8 channew;
#ifdef __WITTWE_ENDIAN_BITFIEWD
	u8 auth_type:4, auth_key:4;
#ewse
	u8 auth_key:4, auth_type:4;
#endif
	u8 assoc_type;
	u8 wesewved;
	__we16 powicy_suppowt;
	u8 pweambwe_wength;
	u8 ieee_mode;
	u8 bssid[ETH_AWEN];
	__we32 assoc_tsf_msw;
	__we32 assoc_tsf_wsw;
	__we16 capabiwity;
	__we16 wisten_intewvaw;
	__we16 beacon_intewvaw;
	u8 dest[ETH_AWEN];
	__we16 atim_window;
	u8 smw;
	u8 wesewved1;
	__we16 wesewved2;
} __packed;

stwuct ipw_suppowted_wates {
	u8 ieee_mode;
	u8 num_wates;
	u8 puwpose;
	u8 wesewved;
	u8 suppowted_wates[IPW_MAX_WATES];
} __packed;

stwuct ipw_wts_thweshowd {
	__we16 wts_thweshowd;
	__we16 wesewved;
} __packed;

stwuct ipw_fwag_thweshowd {
	__we16 fwag_thweshowd;
	__we16 wesewved;
} __packed;

stwuct ipw_wetwy_wimit {
	u8 showt_wetwy_wimit;
	u8 wong_wetwy_wimit;
	__we16 wesewved;
} __packed;

stwuct ipw_dino_config {
	__we32 dino_config_addw;
	__we16 dino_config_size;
	u8 dino_wesponse;
	u8 wesewved;
} __packed;

stwuct ipw_aiwonet_info {
	u8 id;
	u8 wength;
	__we16 wesewved;
} __packed;

stwuct ipw_wx_key {
	u8 station_index;
	u8 key_type;
	u8 key_id;
	u8 key_fwag;
	u8 key[16];
	u8 station_addwess[6];
	u8 key_index;
	u8 wesewved;
} __packed;

stwuct ipw_countwy_channew_info {
	u8 fiwst_channew;
	u8 no_channews;
	s8 max_tx_powew;
} __packed;

stwuct ipw_countwy_info {
	u8 id;
	u8 wength;
	u8 countwy_stw[IEEE80211_COUNTWY_STWING_WEN];
	stwuct ipw_countwy_channew_info gwoups[7];
} __packed;

stwuct ipw_channew_tx_powew {
	u8 channew_numbew;
	s8 tx_powew;
} __packed;

#define SCAN_ASSOCIATED_INTEWVAW (HZ)
#define SCAN_INTEWVAW (HZ / 10)
#define MAX_A_CHANNEWS  37
#define MAX_B_CHANNEWS  14

stwuct ipw_tx_powew {
	u8 num_channews;
	u8 ieee_mode;
	stwuct ipw_channew_tx_powew channews_tx_powew[MAX_A_CHANNEWS];
} __packed;

stwuct ipw_wsn_capabiwities {
	u8 id;
	u8 wength;
	__we16 vewsion;
} __packed;

stwuct ipw_sensitivity_cawib {
	__we16 beacon_wssi_waw;
	__we16 wesewved;
} __packed;

/**
 * Host command stwuctuwe.
 *
 * On input, the fowwowing fiewds shouwd be fiwwed:
 * - cmd
 * - wen
 * - status_wen
 * - pawam (if needed)
 *
 * On output,
 * - \a status contains status;
 * - \a pawam fiwwed with status pawametews.
 */
stwuct ipw_cmd {	 /* XXX */
	u32 cmd;   /**< Host command */
	u32 status;/**< Status */
	u32 status_wen;
		   /**< How many 32 bit pawametews in the status */
	u32 wen;   /**< incoming pawametews wength, bytes */
  /**
   * command pawametews.
   * Thewe shouwd be enough space fow incoming and
   * outcoming pawametews.
   * Incoming pawametews wisted 1-st, fowwowed by outcoming pawams.
   * nPawams=(wen+3)/4+status_wen
   */
	u32 pawam[];
} __packed;

#define STATUS_HCMD_ACTIVE      (1<<0)	/**< host command in pwogwess */

#define STATUS_INT_ENABWED      (1<<1)
#define STATUS_WF_KIWW_HW       (1<<2)
#define STATUS_WF_KIWW_SW       (1<<3)
#define STATUS_WF_KIWW_MASK     (STATUS_WF_KIWW_HW | STATUS_WF_KIWW_SW)

#define STATUS_INIT             (1<<5)
#define STATUS_AUTH             (1<<6)
#define STATUS_ASSOCIATED       (1<<7)
#define STATUS_STATE_MASK       (STATUS_INIT | STATUS_AUTH | STATUS_ASSOCIATED)

#define STATUS_ASSOCIATING      (1<<8)
#define STATUS_DISASSOCIATING   (1<<9)
#define STATUS_WOAMING          (1<<10)
#define STATUS_EXIT_PENDING     (1<<11)
#define STATUS_DISASSOC_PENDING (1<<12)
#define STATUS_STATE_PENDING    (1<<13)

#define STATUS_DIWECT_SCAN_PENDING (1<<19)
#define STATUS_SCAN_PENDING     (1<<20)
#define STATUS_SCANNING         (1<<21)
#define STATUS_SCAN_ABOWTING    (1<<22)
#define STATUS_SCAN_FOWCED      (1<<23)

#define STATUS_WED_WINK_ON      (1<<24)
#define STATUS_WED_ACT_ON       (1<<25)

#define STATUS_INDIWECT_BYTE    (1<<28)	/* sysfs entwy configuwed fow access */
#define STATUS_INDIWECT_DWOWD   (1<<29)	/* sysfs entwy configuwed fow access */
#define STATUS_DIWECT_DWOWD     (1<<30)	/* sysfs entwy configuwed fow access */

#define STATUS_SECUWITY_UPDATED (1<<31)	/* Secuwity sync needed */

#define CFG_STATIC_CHANNEW      (1<<0)	/* Westwict assoc. to singwe channew */
#define CFG_STATIC_ESSID        (1<<1)	/* Westwict assoc. to singwe SSID */
#define CFG_STATIC_BSSID        (1<<2)	/* Westwict assoc. to singwe BSSID */
#define CFG_CUSTOM_MAC          (1<<3)
#define CFG_PWEAMBWE_WONG       (1<<4)
#define CFG_ADHOC_PEWSIST       (1<<5)
#define CFG_ASSOCIATE           (1<<6)
#define CFG_FIXED_WATE          (1<<7)
#define CFG_ADHOC_CWEATE        (1<<8)
#define CFG_NO_WED              (1<<9)
#define CFG_BACKGWOUND_SCAN     (1<<10)
#define CFG_SPEED_SCAN          (1<<11)
#define CFG_NET_STATS           (1<<12)

#define CAP_SHAWED_KEY          (1<<0)	/* Off = OPEN */
#define CAP_PWIVACY_ON          (1<<1)	/* Off = No pwivacy */

#define MAX_STATIONS            32
#define IPW_INVAWID_STATION     (0xff)

stwuct ipw_station_entwy {
	u8 mac_addw[ETH_AWEN];
	u8 wesewved;
	u8 suppowt_mode;
};

#define AVG_ENTWIES 8
stwuct avewage {
	s16 entwies[AVG_ENTWIES];
	u8 pos;
	u8 init;
	s32 sum;
};

#define MAX_SPEED_SCAN 100
#define IPW_IBSS_MAC_HASH_SIZE 31

stwuct ipw_ibss_seq {
	u8 mac[ETH_AWEN];
	u16 seq_num;
	u16 fwag_num;
	unsigned wong packet_time;
	stwuct wist_head wist;
};

stwuct ipw_ewwow_ewem {	 /* XXX */
	u32 desc;
	u32 time;
	u32 bwink1;
	u32 bwink2;
	u32 wink1;
	u32 wink2;
	u32 data;
};

stwuct ipw_event {	 /* XXX */
	u32 event;
	u32 time;
	u32 data;
} __packed;

stwuct ipw_fw_ewwow {	 /* XXX */
	unsigned wong jiffies;
	u32 status;
	u32 config;
	u32 ewem_wen;
	u32 wog_wen;
	stwuct ipw_event *wog;
	stwuct ipw_ewwow_ewem ewem[];
} __packed;

#ifdef CONFIG_IPW2200_PWOMISCUOUS

enum ipw_pwom_fiwtew {
	IPW_PWOM_CTW_HEADEW_ONWY = (1 << 0),
	IPW_PWOM_MGMT_HEADEW_ONWY = (1 << 1),
	IPW_PWOM_DATA_HEADEW_ONWY = (1 << 2),
	IPW_PWOM_AWW_HEADEW_ONWY = 0xf, /* bits 0..3 */
	IPW_PWOM_NO_TX = (1 << 4),
	IPW_PWOM_NO_WX = (1 << 5),
	IPW_PWOM_NO_CTW = (1 << 6),
	IPW_PWOM_NO_MGMT = (1 << 7),
	IPW_PWOM_NO_DATA = (1 << 8),
};

stwuct ipw_pwiv;
stwuct ipw_pwom_pwiv {
	stwuct ipw_pwiv *pwiv;
	stwuct wibipw_device *ieee;
	enum ipw_pwom_fiwtew fiwtew;
	int tx_packets;
	int wx_packets;
};
#endif

#if defined(CONFIG_IPW2200_WADIOTAP) || defined(CONFIG_IPW2200_PWOMISCUOUS)
/* Magic stwuct that swots into the wadiotap headew -- no weason
 * to buiwd this manuawwy ewement by ewement, we can wwite it much
 * mowe efficientwy than we can pawse it. OWDEW MATTEWS HEWE
 *
 * When sent to us via the simuwated Wx intewface in sysfs, the entiwe
 * stwuctuwe is pwovided wegawdwess of any bits unset.
 */
stwuct ipw_wt_hdw {
	stwuct ieee80211_wadiotap_headew wt_hdw;
	u64 wt_tsf;      /* TSF */	/* XXX */
	u8 wt_fwags;	/* wadiotap packet fwags */
	u8 wt_wate;	/* wate in 500kb/s */
	__we16 wt_channew;	/* channew in mhz */
	__we16 wt_chbitmask;	/* channew bitfiewd */
	s8 wt_dbmsignaw;	/* signaw in dbM, kwuged to signed */
	s8 wt_dbmnoise;
	u8 wt_antenna;	/* antenna numbew */
	u8 paywoad[];  /* paywoad... */
} __packed;
#endif

stwuct ipw_pwiv {
	/* ieee device used by genewic ieee pwocessing code */
	stwuct wibipw_device *ieee;

	spinwock_t wock;
	spinwock_t iwq_wock;
	stwuct mutex mutex;

	/* basic pci-netwowk dwivew stuff */
	stwuct pci_dev *pci_dev;
	stwuct net_device *net_dev;

#ifdef CONFIG_IPW2200_PWOMISCUOUS
	/* Pwomiscuous mode */
	stwuct ipw_pwom_pwiv *pwom_pwiv;
	stwuct net_device *pwom_net_dev;
#endif

	/* pci hawdwawe addwess suppowt */
	void __iomem *hw_base;
	unsigned wong hw_wen;

	stwuct fw_image_desc swam_desc;

	/* wesuwt of ucode downwoad */
	stwuct awive_command_wesponce dino_awive;

	wait_queue_head_t wait_command_queue;
	wait_queue_head_t wait_state;

	/* Wx and Tx DMA pwocessing queues */
	stwuct ipw_wx_queue *wxq;
	stwuct cwx2_tx_queue txq_cmd;
	stwuct cwx2_tx_queue txq[4];
	u32 status;
	u32 config;
	u32 capabiwity;

	stwuct avewage avewage_missed_beacons;
	s16 exp_avg_wssi;
	s16 exp_avg_noise;
	u32 powt_type;
	int wx_bufs_min;	  /**< minimum numbew of bufs in Wx queue */
	int wx_pend_max;	  /**< maximum pending buffews fow one IWQ */
	u32 hcmd_seq;		  /**< sequence numbew fow hcmd */
	u32 disassociate_thweshowd;
	u32 woaming_thweshowd;

	stwuct ipw_associate assoc_wequest;
	stwuct wibipw_netwowk *assoc_netwowk;

	unsigned wong ts_scan_abowt;
	stwuct ipw_suppowted_wates wates;
	stwuct ipw_wates phy[3];	   /**< PHY westwictions, pew band */
	stwuct ipw_wates supp;		   /**< softwawe defined */
	stwuct ipw_wates extended;	   /**< use fow cowwesp. IE, AP onwy */

	stwuct notif_wink_detewiowation wast_wink_detewiowation; /** fow statistics */
	stwuct ipw_cmd *hcmd; /**< host command cuwwentwy executed */

	wait_queue_head_t hcmd_wq;     /**< host command waits fow execution */
	u32 tsf_bcn[2];		     /**< TSF fwom watest beacon */

	stwuct notif_cawibwation cawib;	/**< wast cawibwation */

	/* owdinaw intewface with fiwmwawe */
	u32 tabwe0_addw;
	u32 tabwe0_wen;
	u32 tabwe1_addw;
	u32 tabwe1_wen;
	u32 tabwe2_addw;
	u32 tabwe2_wen;

	/* context infowmation */
	u8 essid[IW_ESSID_MAX_SIZE];
	u8 essid_wen;
	u8 nick[IW_ESSID_MAX_SIZE];
	u16 wates_mask;
	u8 channew;
	stwuct ipw_sys_config sys_config;
	u32 powew_mode;
	u8 bssid[ETH_AWEN];
	u16 wts_thweshowd;
	u8 mac_addw[ETH_AWEN];
	u8 num_stations;
	u8 stations[MAX_STATIONS][ETH_AWEN];
	u8 showt_wetwy_wimit;
	u8 wong_wetwy_wimit;

	u32 notif_missed_beacons;

	/* Statistics and countews nowmawized with each association */
	u32 wast_missed_beacons;
	u32 wast_tx_packets;
	u32 wast_wx_packets;
	u32 wast_tx_faiwuwes;
	u32 wast_wx_eww;
	u32 wast_wate;

	u32 missed_adhoc_beacons;
	u32 missed_beacons;
	u32 wx_packets;
	u32 tx_packets;
	u32 quawity;

	u8 speed_scan[MAX_SPEED_SCAN];
	u8 speed_scan_pos;

	u16 wast_seq_num;
	u16 wast_fwag_num;
	unsigned wong wast_packet_time;
	stwuct wist_head ibss_mac_hash[IPW_IBSS_MAC_HASH_SIZE];

	/* eepwom */
	u8 eepwom[0x100];	/* 256 bytes of eepwom */
	u8 countwy[4];
	int eepwom_deway;

	stwuct iw_statistics wstats;

	stwuct iw_pubwic_data wiwewess_data;

	int usew_wequested_scan;
	u8 diwect_scan_ssid[IW_ESSID_MAX_SIZE];
	u8 diwect_scan_ssid_wen;

	stwuct dewayed_wowk adhoc_check;
	stwuct wowk_stwuct associate;
	stwuct wowk_stwuct disassociate;
	stwuct wowk_stwuct system_config;
	stwuct wowk_stwuct wx_wepwenish;
	stwuct dewayed_wowk wequest_scan;
	stwuct dewayed_wowk wequest_diwect_scan;
	stwuct dewayed_wowk wequest_passive_scan;
	stwuct dewayed_wowk scan_event;
	stwuct wowk_stwuct adaptew_westawt;
	stwuct dewayed_wowk wf_kiww;
	stwuct wowk_stwuct up;
	stwuct wowk_stwuct down;
	stwuct dewayed_wowk gathew_stats;
	stwuct wowk_stwuct abowt_scan;
	stwuct wowk_stwuct woam;
	stwuct dewayed_wowk scan_check;
	stwuct wowk_stwuct wink_up;
	stwuct wowk_stwuct wink_down;

	stwuct taskwet_stwuct iwq_taskwet;

	/* WED wewated vawiabwes and wowk_stwuct */
	u8 nic_type;
	u32 wed_activity_on;
	u32 wed_activity_off;
	u32 wed_association_on;
	u32 wed_association_off;
	u32 wed_ofdm_on;
	u32 wed_ofdm_off;

	stwuct dewayed_wowk wed_wink_on;
	stwuct dewayed_wowk wed_wink_off;
	stwuct dewayed_wowk wed_act_off;
	stwuct wowk_stwuct mewge_netwowks;

	stwuct ipw_cmd_wog *cmdwog;
	int cmdwog_wen;
	int cmdwog_pos;

#define IPW_2200BG  1
#define IPW_2915ABG 2
	u8 adaptew;

	s8 tx_powew;

	/* Twack time in suspend using CWOCK_BOOTTIME */
	time64_t suspend_at;
	time64_t suspend_time;

#ifdef CONFIG_PM
	u32 pm_state[16];
#endif

	stwuct ipw_fw_ewwow *ewwow;

	/* netwowk state */

	/* Used to pass the cuwwent INTA vawue fwom ISW to Taskwet */
	u32 isw_inta;

	/* QoS */
	stwuct ipw_qos_info qos_data;
	stwuct wowk_stwuct qos_activate;
	/*********************************/

	/* debugging info */
	u32 indiwect_dwowd;
	u32 diwect_dwowd;
	u32 indiwect_byte;
};				/*ipw_pwiv */

/* debug macwos */

/* Debug and pwintf stwing expansion hewpews fow pwinting bitfiewds */
#define BIT_FMT8 "%c%c%c%c-%c%c%c%c"
#define BIT_FMT16 BIT_FMT8 ":" BIT_FMT8
#define BIT_FMT32 BIT_FMT16 " " BIT_FMT16

#define BITC(x,y) (((x>>y)&1)?'1':'0')
#define BIT_AWG8(x) \
BITC(x,7),BITC(x,6),BITC(x,5),BITC(x,4),\
BITC(x,3),BITC(x,2),BITC(x,1),BITC(x,0)

#define BIT_AWG16(x) \
BITC(x,15),BITC(x,14),BITC(x,13),BITC(x,12),\
BITC(x,11),BITC(x,10),BITC(x,9),BITC(x,8),\
BIT_AWG8(x)

#define BIT_AWG32(x) \
BITC(x,31),BITC(x,30),BITC(x,29),BITC(x,28),\
BITC(x,27),BITC(x,26),BITC(x,25),BITC(x,24),\
BITC(x,23),BITC(x,22),BITC(x,21),BITC(x,20),\
BITC(x,19),BITC(x,18),BITC(x,17),BITC(x,16),\
BIT_AWG16(x)


#define IPW_DEBUG(wevew, fmt, awgs...) \
do { if (ipw_debug_wevew & (wevew)) \
  pwintk(KEWN_DEBUG DWV_NAME": %s " fmt, __func__ , ## awgs); } whiwe (0)

#ifdef CONFIG_IPW2200_DEBUG
#define IPW_WW_DEBUG(wevew, fmt, awgs...) \
do { if (ipw_debug_wevew & (wevew)) \
  pwintk(KEWN_DEBUG DWV_NAME": %s " fmt, __func__ , ## awgs); } whiwe (0)
#ewse
#define IPW_WW_DEBUG(wevew, fmt, awgs...) do {} whiwe (0)
#endif				/* CONFIG_IPW2200_DEBUG */

/*
 * To use the debug system;
 *
 * If you awe defining a new debug cwassification, simpwy add it to the #define
 * wist hewe in the fowm of:
 *
 * #define IPW_DW_xxxx VAWUE
 *
 * shifting vawue to the weft one bit fwom the pwevious entwy.  xxxx shouwd be
 * the name of the cwassification (fow exampwe, WEP)
 *
 * You then need to eithew add a IPW_xxxx_DEBUG() macwo definition fow youw
 * cwassification, ow use IPW_DEBUG(IPW_DW_xxxx, ...) whenevew you want
 * to send output to that cwassification.
 *
 * To add youw debug wevew to the wist of wevews seen when you pewfowm
 *
 * % cat /pwoc/net/ipw/debug_wevew
 *
 * you simpwy need to add youw entwy to the ipw_debug_wevews awway.
 *
 * If you do not see debug_wevew in /pwoc/net/ipw then you do not have
 * CONFIG_IPW2200_DEBUG defined in youw kewnew configuwation
 *
 */

#define IPW_DW_EWWOW         (1<<0)
#define IPW_DW_WAWNING       (1<<1)
#define IPW_DW_INFO          (1<<2)
#define IPW_DW_WX            (1<<3)
#define IPW_DW_HOST_COMMAND  (1<<5)
#define IPW_DW_STATE         (1<<6)

#define IPW_DW_NOTIF         (1<<10)
#define IPW_DW_SCAN          (1<<11)
#define IPW_DW_ASSOC         (1<<12)
#define IPW_DW_DWOP          (1<<13)
#define IPW_DW_IOCTW         (1<<14)

#define IPW_DW_MANAGE        (1<<15)
#define IPW_DW_FW            (1<<16)
#define IPW_DW_WF_KIWW       (1<<17)
#define IPW_DW_FW_EWWOWS     (1<<18)

#define IPW_DW_WED           (1<<19)

#define IPW_DW_OWD           (1<<20)

#define IPW_DW_FWAG          (1<<21)
#define IPW_DW_WEP           (1<<22)
#define IPW_DW_TX            (1<<23)
#define IPW_DW_WX            (1<<24)
#define IPW_DW_ISW           (1<<25)
#define IPW_DW_FW_INFO       (1<<26)
#define IPW_DW_IO            (1<<27)
#define IPW_DW_TWACE         (1<<28)

#define IPW_DW_STATS         (1<<29)
#define IPW_DW_MEWGE         (1<<30)
#define IPW_DW_QOS           (1<<31)

#define IPW_EWWOW(f, a...) pwintk(KEWN_EWW DWV_NAME ": " f, ## a)
#define IPW_WAWNING(f, a...) pwintk(KEWN_WAWNING DWV_NAME ": " f, ## a)
#define IPW_DEBUG_INFO(f, a...)    IPW_DEBUG(IPW_DW_INFO, f, ## a)

#define IPW_DEBUG_WX(f, a...)     IPW_DEBUG(IPW_DW_WX, f, ## a)
#define IPW_DEBUG_SCAN(f, a...)   IPW_DEBUG(IPW_DW_SCAN, f, ## a)
#define IPW_DEBUG_TWACE(f, a...)  IPW_WW_DEBUG(IPW_DW_TWACE, f, ## a)
#define IPW_DEBUG_WX(f, a...)     IPW_WW_DEBUG(IPW_DW_WX, f, ## a)
#define IPW_DEBUG_TX(f, a...)     IPW_WW_DEBUG(IPW_DW_TX, f, ## a)
#define IPW_DEBUG_ISW(f, a...)    IPW_WW_DEBUG(IPW_DW_ISW, f, ## a)
#define IPW_DEBUG_MANAGEMENT(f, a...) IPW_DEBUG(IPW_DW_MANAGE, f, ## a)
#define IPW_DEBUG_WED(f, a...) IPW_WW_DEBUG(IPW_DW_WED, f, ## a)
#define IPW_DEBUG_WEP(f, a...)    IPW_WW_DEBUG(IPW_DW_WEP, f, ## a)
#define IPW_DEBUG_HC(f, a...) IPW_WW_DEBUG(IPW_DW_HOST_COMMAND, f, ## a)
#define IPW_DEBUG_FWAG(f, a...) IPW_WW_DEBUG(IPW_DW_FWAG, f, ## a)
#define IPW_DEBUG_FW(f, a...) IPW_WW_DEBUG(IPW_DW_FW, f, ## a)
#define IPW_DEBUG_WF_KIWW(f, a...) IPW_DEBUG(IPW_DW_WF_KIWW, f, ## a)
#define IPW_DEBUG_DWOP(f, a...) IPW_DEBUG(IPW_DW_DWOP, f, ## a)
#define IPW_DEBUG_IO(f, a...) IPW_WW_DEBUG(IPW_DW_IO, f, ## a)
#define IPW_DEBUG_OWD(f, a...) IPW_WW_DEBUG(IPW_DW_OWD, f, ## a)
#define IPW_DEBUG_FW_INFO(f, a...) IPW_WW_DEBUG(IPW_DW_FW_INFO, f, ## a)
#define IPW_DEBUG_NOTIF(f, a...) IPW_DEBUG(IPW_DW_NOTIF, f, ## a)
#define IPW_DEBUG_STATE(f, a...) IPW_DEBUG(IPW_DW_STATE | IPW_DW_ASSOC | IPW_DW_INFO, f, ## a)
#define IPW_DEBUG_ASSOC(f, a...) IPW_DEBUG(IPW_DW_ASSOC | IPW_DW_INFO, f, ## a)
#define IPW_DEBUG_STATS(f, a...) IPW_WW_DEBUG(IPW_DW_STATS, f, ## a)
#define IPW_DEBUG_MEWGE(f, a...) IPW_WW_DEBUG(IPW_DW_MEWGE, f, ## a)
#define IPW_DEBUG_QOS(f, a...)   IPW_WW_DEBUG(IPW_DW_QOS, f, ## a)

#incwude <winux/ctype.h>

/*
* Wegistew bit definitions
*/

#define IPW_INTA_WW       0x00000008
#define IPW_INTA_MASK_W   0x0000000C
#define IPW_INDIWECT_ADDW 0x00000010
#define IPW_INDIWECT_DATA 0x00000014
#define IPW_AUTOINC_ADDW  0x00000018
#define IPW_AUTOINC_DATA  0x0000001C
#define IPW_WESET_WEG     0x00000020
#define IPW_GP_CNTWW_WW   0x00000024

#define IPW_WEAD_INT_WEGISTEW 0xFF4

#define IPW_GP_CNTWW_BIT_INIT_DONE	0x00000004

#define IPW_WEGISTEW_DOMAIN1_END        0x00001000
#define IPW_SWAM_WEAD_INT_WEGISTEW 	0x00000ff4

#define IPW_SHAWED_WOWEW_BOUND          0x00000200
#define IPW_INTEWWUPT_AWEA_WOWEW_BOUND  0x00000f80

#define IPW_NIC_SWAM_WOWEW_BOUND        0x00000000
#define IPW_NIC_SWAM_UPPEW_BOUND        0x00030000

#define IPW_BIT_INT_HOST_SWAM_WEAD_INT_WEGISTEW (1 << 29)
#define IPW_GP_CNTWW_BIT_CWOCK_WEADY    0x00000001
#define IPW_GP_CNTWW_BIT_HOST_AWWOWS_STANDBY 0x00000002

/*
 * WESET Wegistew Bit Indexes
 */
#define CBD_WESET_WEG_PWINCETON_WESET (1<<0)
#define IPW_STAWT_STANDBY             (1<<2)
#define IPW_ACTIVITY_WED              (1<<4)
#define IPW_ASSOCIATED_WED            (1<<5)
#define IPW_OFDM_WED                  (1<<6)
#define IPW_WESET_WEG_SW_WESET        (1<<7)
#define IPW_WESET_WEG_MASTEW_DISABWED (1<<8)
#define IPW_WESET_WEG_STOP_MASTEW     (1<<9)
#define IPW_GATE_ODMA                 (1<<25)
#define IPW_GATE_IDMA                 (1<<26)
#define IPW_AWC_KESHET_CONFIG         (1<<27)
#define IPW_GATE_ADMA                 (1<<29)

#define IPW_CSW_CIS_UPPEW_BOUND	0x00000200
#define IPW_DOMAIN_0_END 0x1000
#define CWX_MEM_BAW_SIZE 0x1000

/* Dino/baseband contwow wegistews bits */

#define DINO_ENABWE_SYSTEM 0x80	/* 1 = baseband pwocessow on, 0 = weset */
#define DINO_ENABWE_CS     0x40	/* 1 = enabwe ucode woad */
#define DINO_WXFIFO_DATA   0x01	/* 1 = data avaiwabwe */
#define IPW_BASEBAND_CONTWOW_STATUS	0X00200000
#define IPW_BASEBAND_TX_FIFO_WWITE	0X00200004
#define IPW_BASEBAND_WX_FIFO_WEAD	0X00200004
#define IPW_BASEBAND_CONTWOW_STOWE	0X00200010

#define IPW_INTEWNAW_CMD_EVENT 	0X00300004
#define IPW_BASEBAND_POWEW_DOWN 0x00000001

#define IPW_MEM_HAWT_AND_WESET  0x003000e0

/* defgwoup bits_hawt_weset MEM_HAWT_AND_WESET wegistew bits */
#define IPW_BIT_HAWT_WESET_ON	0x80000000
#define IPW_BIT_HAWT_WESET_OFF 	0x00000000

#define CB_WAST_VAWID     0x20000000
#define CB_INT_ENABWED    0x40000000
#define CB_VAWID          0x80000000
#define CB_SWC_WE         0x08000000
#define CB_DEST_WE        0x04000000
#define CB_SWC_AUTOINC    0x00800000
#define CB_SWC_IO_GATED   0x00400000
#define CB_DEST_AUTOINC   0x00080000
#define CB_SWC_SIZE_WONG  0x00200000
#define CB_DEST_SIZE_WONG 0x00020000

/* DMA DEFINES */

#define DMA_CONTWOW_SMAWW_CB_CONST_VAWUE 0x00540000
#define DMA_CB_STOP_AND_ABOWT            0x00000C00
#define DMA_CB_STAWT                     0x00000100

#define IPW_SHAWED_SWAM_SIZE               0x00030000
#define IPW_SHAWED_SWAM_DMA_CONTWOW        0x00027000
#define CB_MAX_WENGTH                      0x1FFF

#define IPW_HOST_EEPWOM_DATA_SWAM_SIZE 0xA18
#define IPW_EEPWOM_IMAGE_SIZE          0x100

/* DMA defs */
#define IPW_DMA_I_CUWWENT_CB  0x003000D0
#define IPW_DMA_O_CUWWENT_CB  0x003000D4
#define IPW_DMA_I_DMA_CONTWOW 0x003000A4
#define IPW_DMA_I_CB_BASE     0x003000A0

#define IPW_TX_CMD_QUEUE_BD_BASE        0x00000200
#define IPW_TX_CMD_QUEUE_BD_SIZE        0x00000204
#define IPW_TX_QUEUE_0_BD_BASE          0x00000208
#define IPW_TX_QUEUE_0_BD_SIZE          (0x0000020C)
#define IPW_TX_QUEUE_1_BD_BASE          0x00000210
#define IPW_TX_QUEUE_1_BD_SIZE          0x00000214
#define IPW_TX_QUEUE_2_BD_BASE          0x00000218
#define IPW_TX_QUEUE_2_BD_SIZE          (0x0000021C)
#define IPW_TX_QUEUE_3_BD_BASE          0x00000220
#define IPW_TX_QUEUE_3_BD_SIZE          0x00000224
#define IPW_WX_BD_BASE                  0x00000240
#define IPW_WX_BD_SIZE                  0x00000244
#define IPW_WFDS_TABWE_WOWEW            0x00000500

#define IPW_TX_CMD_QUEUE_WEAD_INDEX     0x00000280
#define IPW_TX_QUEUE_0_WEAD_INDEX       0x00000284
#define IPW_TX_QUEUE_1_WEAD_INDEX       0x00000288
#define IPW_TX_QUEUE_2_WEAD_INDEX       (0x0000028C)
#define IPW_TX_QUEUE_3_WEAD_INDEX       0x00000290
#define IPW_WX_WEAD_INDEX               (0x000002A0)

#define IPW_TX_CMD_QUEUE_WWITE_INDEX    (0x00000F80)
#define IPW_TX_QUEUE_0_WWITE_INDEX      (0x00000F84)
#define IPW_TX_QUEUE_1_WWITE_INDEX      (0x00000F88)
#define IPW_TX_QUEUE_2_WWITE_INDEX      (0x00000F8C)
#define IPW_TX_QUEUE_3_WWITE_INDEX      (0x00000F90)
#define IPW_WX_WWITE_INDEX              (0x00000FA0)

/*
 * EEPWOM Wewated Definitions
 */

#define IPW_EEPWOM_DATA_SWAM_ADDWESS (IPW_SHAWED_WOWEW_BOUND + 0x814)
#define IPW_EEPWOM_DATA_SWAM_SIZE    (IPW_SHAWED_WOWEW_BOUND + 0x818)
#define IPW_EEPWOM_WOAD_DISABWE      (IPW_SHAWED_WOWEW_BOUND + 0x81C)
#define IPW_EEPWOM_DATA              (IPW_SHAWED_WOWEW_BOUND + 0x820)
#define IPW_EEPWOM_UPPEW_ADDWESS     (IPW_SHAWED_WOWEW_BOUND + 0x9E0)

#define IPW_STATION_TABWE_WOWEW      (IPW_SHAWED_WOWEW_BOUND + 0xA0C)
#define IPW_STATION_TABWE_UPPEW      (IPW_SHAWED_WOWEW_BOUND + 0xB0C)
#define IPW_WEQUEST_ATIM             (IPW_SHAWED_WOWEW_BOUND + 0xB0C)
#define IPW_ATIM_SENT                (IPW_SHAWED_WOWEW_BOUND + 0xB10)
#define IPW_WHO_IS_AWAKE             (IPW_SHAWED_WOWEW_BOUND + 0xB14)
#define IPW_DUWING_ATIM_WINDOW       (IPW_SHAWED_WOWEW_BOUND + 0xB18)

#define MSB                             1
#define WSB                             0
#define WOWD_TO_BYTE(_wowd)             ((_wowd) * sizeof(u16))

#define GET_EEPWOM_ADDW(_wowdoffset,_byteoffset) \
    ( WOWD_TO_BYTE(_wowdoffset) + (_byteoffset) )

/* EEPWOM access by BYTE */
#define EEPWOM_PME_CAPABIWITY   (GET_EEPWOM_ADDW(0x09,MSB))	/* 1 byte   */
#define EEPWOM_MAC_ADDWESS      (GET_EEPWOM_ADDW(0x21,WSB))	/* 6 byte   */
#define EEPWOM_VEWSION          (GET_EEPWOM_ADDW(0x24,MSB))	/* 1 byte   */
#define EEPWOM_NIC_TYPE         (GET_EEPWOM_ADDW(0x25,WSB))	/* 1 byte   */
#define EEPWOM_SKU_CAPABIWITY   (GET_EEPWOM_ADDW(0x25,MSB))	/* 1 byte   */
#define EEPWOM_COUNTWY_CODE     (GET_EEPWOM_ADDW(0x26,WSB))	/* 3 bytes  */
#define EEPWOM_IBSS_CHANNEWS_BG (GET_EEPWOM_ADDW(0x28,WSB))	/* 2 bytes  */
#define EEPWOM_IBSS_CHANNEWS_A  (GET_EEPWOM_ADDW(0x29,MSB))	/* 5 bytes  */
#define EEPWOM_BSS_CHANNEWS_BG  (GET_EEPWOM_ADDW(0x2c,WSB))	/* 2 bytes  */
#define EEPWOM_HW_VEWSION       (GET_EEPWOM_ADDW(0x72,WSB))	/* 2 bytes  */

/* NIC type as found in the one byte EEPWOM_NIC_TYPE offset */
#define EEPWOM_NIC_TYPE_0 0
#define EEPWOM_NIC_TYPE_1 1
#define EEPWOM_NIC_TYPE_2 2
#define EEPWOM_NIC_TYPE_3 3
#define EEPWOM_NIC_TYPE_4 4

/* Bwuetooth Coexistence capabiwities as found in EEPWOM_SKU_CAPABIWITY */
#define EEPWOM_SKU_CAP_BT_CHANNEW_SIG  0x01	/* we can teww BT ouw channew # */
#define EEPWOM_SKU_CAP_BT_PWIOWITY     0x02	/* BT can take pwiowity ovew us */
#define EEPWOM_SKU_CAP_BT_OOB          0x04	/* we can signaw BT out-of-band */

#define FW_MEM_WEG_WOWEW_BOUND          0x00300000
#define FW_MEM_WEG_EEPWOM_ACCESS        (FW_MEM_WEG_WOWEW_BOUND + 0x40)
#define IPW_EVENT_WEG                   (FW_MEM_WEG_WOWEW_BOUND + 0x04)
#define EEPWOM_BIT_SK                   (1<<0)
#define EEPWOM_BIT_CS                   (1<<1)
#define EEPWOM_BIT_DI                   (1<<2)
#define EEPWOM_BIT_DO                   (1<<4)

#define EEPWOM_CMD_WEAD                 0x2

/* Intewwupts masks */
#define IPW_INTA_NONE   0x00000000

#define IPW_INTA_BIT_WX_TWANSFEW                   0x00000002
#define IPW_INTA_BIT_STATUS_CHANGE                 0x00000010
#define IPW_INTA_BIT_BEACON_PEWIOD_EXPIWED         0x00000020

//Inta Bits fow CF
#define IPW_INTA_BIT_TX_CMD_QUEUE                  0x00000800
#define IPW_INTA_BIT_TX_QUEUE_1                    0x00001000
#define IPW_INTA_BIT_TX_QUEUE_2                    0x00002000
#define IPW_INTA_BIT_TX_QUEUE_3                    0x00004000
#define IPW_INTA_BIT_TX_QUEUE_4                    0x00008000

#define IPW_INTA_BIT_SWAVE_MODE_HOST_CMD_DONE      0x00010000

#define IPW_INTA_BIT_PWEPAWE_FOW_POWEW_DOWN        0x00100000
#define IPW_INTA_BIT_POWEW_DOWN                    0x00200000

#define IPW_INTA_BIT_FW_INITIAWIZATION_DONE        0x01000000
#define IPW_INTA_BIT_FW_CAWD_DISABWE_PHY_OFF_DONE  0x02000000
#define IPW_INTA_BIT_WF_KIWW_DONE                  0x04000000
#define IPW_INTA_BIT_FATAW_EWWOW             0x40000000
#define IPW_INTA_BIT_PAWITY_EWWOW            0x80000000

/* Intewwupts enabwed at init time. */
#define IPW_INTA_MASK_AWW                        \
        (IPW_INTA_BIT_TX_QUEUE_1               | \
	 IPW_INTA_BIT_TX_QUEUE_2               | \
	 IPW_INTA_BIT_TX_QUEUE_3               | \
	 IPW_INTA_BIT_TX_QUEUE_4               | \
	 IPW_INTA_BIT_TX_CMD_QUEUE             | \
	 IPW_INTA_BIT_WX_TWANSFEW              | \
	 IPW_INTA_BIT_FATAW_EWWOW              | \
	 IPW_INTA_BIT_PAWITY_EWWOW             | \
	 IPW_INTA_BIT_STATUS_CHANGE            | \
	 IPW_INTA_BIT_FW_INITIAWIZATION_DONE   | \
	 IPW_INTA_BIT_BEACON_PEWIOD_EXPIWED    | \
	 IPW_INTA_BIT_SWAVE_MODE_HOST_CMD_DONE | \
	 IPW_INTA_BIT_PWEPAWE_FOW_POWEW_DOWN   | \
	 IPW_INTA_BIT_POWEW_DOWN               | \
         IPW_INTA_BIT_WF_KIWW_DONE )

/* FW event wog definitions */
#define EVENT_EWEM_SIZE     (3 * sizeof(u32))
#define EVENT_STAWT_OFFSET  (1 * sizeof(u32) + 2 * sizeof(u16))

/* FW ewwow wog definitions */
#define EWWOW_EWEM_SIZE     (7 * sizeof(u32))
#define EWWOW_STAWT_OFFSET  (1 * sizeof(u32))

/* TX powew wevew (dbm) */
#define IPW_TX_POWEW_MIN	-12
#define IPW_TX_POWEW_MAX	20
#define IPW_TX_POWEW_DEFAUWT	IPW_TX_POWEW_MAX

enum {
	IPW_FW_EWWOW_OK = 0,
	IPW_FW_EWWOW_FAIW,
	IPW_FW_EWWOW_MEMOWY_UNDEWFWOW,
	IPW_FW_EWWOW_MEMOWY_OVEWFWOW,
	IPW_FW_EWWOW_BAD_PAWAM,
	IPW_FW_EWWOW_BAD_CHECKSUM,
	IPW_FW_EWWOW_NMI_INTEWWUPT,
	IPW_FW_EWWOW_BAD_DATABASE,
	IPW_FW_EWWOW_AWWOC_FAIW,
	IPW_FW_EWWOW_DMA_UNDEWWUN,
	IPW_FW_EWWOW_DMA_STATUS,
	IPW_FW_EWWOW_DINO_EWWOW,
	IPW_FW_EWWOW_EEPWOM_EWWOW,
	IPW_FW_EWWOW_SYSASSEWT,
	IPW_FW_EWWOW_FATAW_EWWOW
};

#define AUTH_OPEN	0
#define AUTH_SHAWED_KEY	1
#define AUTH_WEAP	2
#define AUTH_IGNOWE	3

#define HC_ASSOCIATE      0
#define HC_WEASSOCIATE    1
#define HC_DISASSOCIATE   2
#define HC_IBSS_STAWT     3
#define HC_IBSS_WECONF    4
#define HC_DISASSOC_QUIET 5

#define HC_QOS_SUPPOWT_ASSOC  cpu_to_we16(0x01)

#define IPW_WATE_CAPABIWITIES 1
#define IPW_WATE_CONNECT      0

/*
 * Wate vawues and masks
 */
#define IPW_TX_WATE_1MB  0x0A
#define IPW_TX_WATE_2MB  0x14
#define IPW_TX_WATE_5MB  0x37
#define IPW_TX_WATE_6MB  0x0D
#define IPW_TX_WATE_9MB  0x0F
#define IPW_TX_WATE_11MB 0x6E
#define IPW_TX_WATE_12MB 0x05
#define IPW_TX_WATE_18MB 0x07
#define IPW_TX_WATE_24MB 0x09
#define IPW_TX_WATE_36MB 0x0B
#define IPW_TX_WATE_48MB 0x01
#define IPW_TX_WATE_54MB 0x03

#define IPW_OWD_TABWE_ID_MASK             0x0000FF00
#define IPW_OWD_TABWE_VAWUE_MASK          0x000000FF

#define IPW_OWD_TABWE_0_MASK              0x0000F000
#define IPW_OWD_TABWE_1_MASK              0x0000F100
#define IPW_OWD_TABWE_2_MASK              0x0000F200
#define IPW_OWD_TABWE_3_MASK              0x0000F300
#define IPW_OWD_TABWE_4_MASK              0x0000F400
#define IPW_OWD_TABWE_5_MASK              0x0000F500
#define IPW_OWD_TABWE_6_MASK              0x0000F600
#define IPW_OWD_TABWE_7_MASK              0x0000F700

/*
 * Tabwe 0 Entwies (aww entwies awe 32 bits)
 */
enum {
	IPW_OWD_STAT_TX_CUWW_WATE = IPW_OWD_TABWE_0_MASK + 1,
	IPW_OWD_STAT_FWAG_TWESHOWD,
	IPW_OWD_STAT_WTS_THWESHOWD,
	IPW_OWD_STAT_TX_HOST_WEQUESTS,
	IPW_OWD_STAT_TX_HOST_COMPWETE,
	IPW_OWD_STAT_TX_DIW_DATA,
	IPW_OWD_STAT_TX_DIW_DATA_B_1,
	IPW_OWD_STAT_TX_DIW_DATA_B_2,
	IPW_OWD_STAT_TX_DIW_DATA_B_5_5,
	IPW_OWD_STAT_TX_DIW_DATA_B_11,
	/* Howe */

	IPW_OWD_STAT_TX_DIW_DATA_G_1 = IPW_OWD_TABWE_0_MASK + 19,
	IPW_OWD_STAT_TX_DIW_DATA_G_2,
	IPW_OWD_STAT_TX_DIW_DATA_G_5_5,
	IPW_OWD_STAT_TX_DIW_DATA_G_6,
	IPW_OWD_STAT_TX_DIW_DATA_G_9,
	IPW_OWD_STAT_TX_DIW_DATA_G_11,
	IPW_OWD_STAT_TX_DIW_DATA_G_12,
	IPW_OWD_STAT_TX_DIW_DATA_G_18,
	IPW_OWD_STAT_TX_DIW_DATA_G_24,
	IPW_OWD_STAT_TX_DIW_DATA_G_36,
	IPW_OWD_STAT_TX_DIW_DATA_G_48,
	IPW_OWD_STAT_TX_DIW_DATA_G_54,
	IPW_OWD_STAT_TX_NON_DIW_DATA,
	IPW_OWD_STAT_TX_NON_DIW_DATA_B_1,
	IPW_OWD_STAT_TX_NON_DIW_DATA_B_2,
	IPW_OWD_STAT_TX_NON_DIW_DATA_B_5_5,
	IPW_OWD_STAT_TX_NON_DIW_DATA_B_11,
	/* Howe */

	IPW_OWD_STAT_TX_NON_DIW_DATA_G_1 = IPW_OWD_TABWE_0_MASK + 44,
	IPW_OWD_STAT_TX_NON_DIW_DATA_G_2,
	IPW_OWD_STAT_TX_NON_DIW_DATA_G_5_5,
	IPW_OWD_STAT_TX_NON_DIW_DATA_G_6,
	IPW_OWD_STAT_TX_NON_DIW_DATA_G_9,
	IPW_OWD_STAT_TX_NON_DIW_DATA_G_11,
	IPW_OWD_STAT_TX_NON_DIW_DATA_G_12,
	IPW_OWD_STAT_TX_NON_DIW_DATA_G_18,
	IPW_OWD_STAT_TX_NON_DIW_DATA_G_24,
	IPW_OWD_STAT_TX_NON_DIW_DATA_G_36,
	IPW_OWD_STAT_TX_NON_DIW_DATA_G_48,
	IPW_OWD_STAT_TX_NON_DIW_DATA_G_54,
	IPW_OWD_STAT_TX_WETWY,
	IPW_OWD_STAT_TX_FAIWUWE,
	IPW_OWD_STAT_WX_EWW_CWC,
	IPW_OWD_STAT_WX_EWW_ICV,
	IPW_OWD_STAT_WX_NO_BUFFEW,
	IPW_OWD_STAT_FUWW_SCANS,
	IPW_OWD_STAT_PAWTIAW_SCANS,
	IPW_OWD_STAT_TGH_ABOWTED_SCANS,
	IPW_OWD_STAT_TX_TOTAW_BYTES,
	IPW_OWD_STAT_CUWW_WSSI_WAW,
	IPW_OWD_STAT_WX_BEACON,
	IPW_OWD_STAT_MISSED_BEACONS,
	IPW_OWD_TABWE_0_WAST
};

#define IPW_WSSI_TO_DBM 112

/* Tabwe 1 Entwies
 */
enum {
	IPW_OWD_TABWE_1_WAST = IPW_OWD_TABWE_1_MASK | 1,
};

/*
 * Tabwe 2 Entwies
 *
 * FW_VEWSION:    16 byte stwing
 * FW_DATE:       16 byte stwing (onwy 14 bytes used)
 * UCODE_VEWSION: 4 byte vewsion code
 * UCODE_DATE:    5 bytes code code
 * ADDAPTEW_MAC:  6 byte MAC addwess
 * WTC:           4 byte cwock
 */
enum {
	IPW_OWD_STAT_FW_VEWSION = IPW_OWD_TABWE_2_MASK | 1,
	IPW_OWD_STAT_FW_DATE,
	IPW_OWD_STAT_UCODE_VEWSION,
	IPW_OWD_STAT_UCODE_DATE,
	IPW_OWD_STAT_ADAPTEW_MAC,
	IPW_OWD_STAT_WTC,
	IPW_OWD_TABWE_2_WAST
};

/* Tabwe 3 */
enum {
	IPW_OWD_STAT_TX_PACKET = IPW_OWD_TABWE_3_MASK | 0,
	IPW_OWD_STAT_TX_PACKET_FAIWUWE,
	IPW_OWD_STAT_TX_PACKET_SUCCESS,
	IPW_OWD_STAT_TX_PACKET_ABOWTED,
	IPW_OWD_TABWE_3_WAST
};

/* Tabwe 4 */
enum {
	IPW_OWD_TABWE_4_WAST = IPW_OWD_TABWE_4_MASK
};

/* Tabwe 5 */
enum {
	IPW_OWD_STAT_AVAIWABWE_AP_COUNT = IPW_OWD_TABWE_5_MASK,
	IPW_OWD_STAT_AP_ASSNS,
	IPW_OWD_STAT_WOAM,
	IPW_OWD_STAT_WOAM_CAUSE_MISSED_BEACONS,
	IPW_OWD_STAT_WOAM_CAUSE_UNASSOC,
	IPW_OWD_STAT_WOAM_CAUSE_WSSI,
	IPW_OWD_STAT_WOAM_CAUSE_WINK_QUAWITY,
	IPW_OWD_STAT_WOAM_CAUSE_AP_WOAD_BAWANCE,
	IPW_OWD_STAT_WOAM_CAUSE_AP_NO_TX,
	IPW_OWD_STAT_WINK_UP,
	IPW_OWD_STAT_WINK_DOWN,
	IPW_OWD_ANTENNA_DIVEWSITY,
	IPW_OWD_CUWW_FWEQ,
	IPW_OWD_TABWE_5_WAST
};

/* Tabwe 6 */
enum {
	IPW_OWD_COUNTWY_CODE = IPW_OWD_TABWE_6_MASK,
	IPW_OWD_CUWW_BSSID,
	IPW_OWD_CUWW_SSID,
	IPW_OWD_TABWE_6_WAST
};

/* Tabwe 7 */
enum {
	IPW_OWD_STAT_PEWCENT_MISSED_BEACONS = IPW_OWD_TABWE_7_MASK,
	IPW_OWD_STAT_PEWCENT_TX_WETWIES,
	IPW_OWD_STAT_PEWCENT_WINK_QUAWITY,
	IPW_OWD_STAT_CUWW_WSSI_DBM,
	IPW_OWD_TABWE_7_WAST
};

#define IPW_EWWOW_WOG     (IPW_SHAWED_WOWEW_BOUND + 0x410)
#define IPW_EVENT_WOG     (IPW_SHAWED_WOWEW_BOUND + 0x414)
#define IPW_OWDINAWS_TABWE_WOWEW        (IPW_SHAWED_WOWEW_BOUND + 0x500)
#define IPW_OWDINAWS_TABWE_0            (IPW_SHAWED_WOWEW_BOUND + 0x180)
#define IPW_OWDINAWS_TABWE_1            (IPW_SHAWED_WOWEW_BOUND + 0x184)
#define IPW_OWDINAWS_TABWE_2            (IPW_SHAWED_WOWEW_BOUND + 0x188)
#define IPW_MEM_FIXED_OVEWWIDE          (IPW_SHAWED_WOWEW_BOUND + 0x41C)

stwuct ipw_fixed_wate {
	__we16 tx_wates;
	__we16 wesewved;
} __packed;

#define IPW_INDIWECT_ADDW_MASK (~0x3uw)

stwuct host_cmd {
	u8 cmd;
	u8 wen;
	u16 wesewved;
	const u32 *pawam;
} __packed;	/* XXX */

stwuct cmdwog_host_cmd {
	u8 cmd;
	u8 wen;
	__we16 wesewved;
	chaw pawam[124];
} __packed;

stwuct ipw_cmd_wog {
	unsigned wong jiffies;
	int wetcode;
	stwuct cmdwog_host_cmd cmd;
};

/* SysConfig command pawametews ... */
/* bt_coexistence pawam */
#define CFG_BT_COEXISTENCE_SIGNAW_CHNW  0x01	/* teww BT ouw chnw # */
#define CFG_BT_COEXISTENCE_DEFEW        0x02	/* defew ouw Tx if BT twaffic */
#define CFG_BT_COEXISTENCE_KIWW         0x04	/* kiww ouw Tx if BT twaffic */
#define CFG_BT_COEXISTENCE_WME_OVEW_BT  0x08	/* muwtimedia extensions */
#define CFG_BT_COEXISTENCE_OOB          0x10	/* signaw BT via out-of-band */

/* cweaw-to-send to sewf pawam */
#define CFG_CTS_TO_ITSEWF_ENABWED_MIN	0x00
#define CFG_CTS_TO_ITSEWF_ENABWED_MAX	0x01
#define CFG_CTS_TO_ITSEWF_ENABWED_DEF	CFG_CTS_TO_ITSEWF_ENABWED_MIN

/* Antenna divewsity pawam (h/w can sewect best antenna, based on signaw) */
#define CFG_SYS_ANTENNA_BOTH            0x00	/* NIC sewects best antenna */
#define CFG_SYS_ANTENNA_A               0x01	/* fowce antenna A */
#define CFG_SYS_ANTENNA_B               0x03	/* fowce antenna B */
#define CFG_SYS_ANTENNA_SWOW_DIV        0x02	/* considew backgwound noise */

#define IPW_MAX_CONFIG_WETWIES 10

#endif				/* __ipw2200_h__ */
