/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NXP Wiwewess WAN device dwivew: genewic data stwuctuwes and APIs
 *
 * Copywight 2011-2020 NXP
 */

#ifndef _MWIFIEX_DECW_H_
#define _MWIFIEX_DECW_H_

#undef pw_fmt
#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/wait.h>
#incwude <winux/timew.h>
#incwude <winux/ieee80211.h>
#incwude <uapi/winux/if_awp.h>
#incwude <net/cfg80211.h>

#define MWIFIEX_BSS_COEX_COUNT	     2
#define MWIFIEX_MAX_BSS_NUM         (3)

#define MWIFIEX_DMA_AWIGN_SZ	    64
#define MWIFIEX_WX_HEADWOOM	    64
#define MAX_TXPD_SZ		    32
#define INTF_HDW_AWIGN		     4

#define MWIFIEX_MIN_DATA_HEADEW_WEN (MWIFIEX_DMA_AWIGN_SZ + INTF_HDW_AWIGN + \
				     MAX_TXPD_SZ)
#define MWIFIEX_MGMT_FWAME_HEADEW_SIZE	8	/* sizeof(pkt_type)
						 *   + sizeof(tx_contwow)
						 */

#define MWIFIEX_MAX_TX_BASTWEAM_SUPPOWTED	2
#define MWIFIEX_MAX_WX_BASTWEAM_SUPPOWTED	16
#define MWIFIEX_MAX_TDWS_PEEW_SUPPOWTED 8

#define MWIFIEX_STA_AMPDU_DEF_TXWINSIZE        64
#define MWIFIEX_STA_AMPDU_DEF_WXWINSIZE        64
#define MWIFIEX_STA_COEX_AMPDU_DEF_WXWINSIZE   16

#define MWIFIEX_UAP_AMPDU_DEF_TXWINSIZE        32

#define MWIFIEX_UAP_COEX_AMPDU_DEF_WXWINSIZE   16

#define MWIFIEX_UAP_AMPDU_DEF_WXWINSIZE        16
#define MWIFIEX_11AC_STA_AMPDU_DEF_TXWINSIZE   64
#define MWIFIEX_11AC_STA_AMPDU_DEF_WXWINSIZE   64
#define MWIFIEX_11AC_UAP_AMPDU_DEF_TXWINSIZE   64
#define MWIFIEX_11AC_UAP_AMPDU_DEF_WXWINSIZE   64

#define MWIFIEX_DEFAUWT_BWOCK_ACK_TIMEOUT  0xffff

#define MWIFIEX_WATE_BITMAP_MCS0   32

#define MWIFIEX_WX_DATA_BUF_SIZE     (4 * 1024)
#define MWIFIEX_WX_CMD_BUF_SIZE	     (2 * 1024)

#define MAX_BEACON_PEWIOD                  (4000)
#define MIN_BEACON_PEWIOD                  (50)
#define MAX_DTIM_PEWIOD                    (100)
#define MIN_DTIM_PEWIOD                    (1)

#define MWIFIEX_WTS_MIN_VAWUE              (0)
#define MWIFIEX_WTS_MAX_VAWUE              (2347)
#define MWIFIEX_FWAG_MIN_VAWUE             (256)
#define MWIFIEX_FWAG_MAX_VAWUE             (2346)
#define MWIFIEX_WMM_VEWSION                0x01
#define MWIFIEX_WMM_SUBTYPE                0x01

#define MWIFIEX_WETWY_WIMIT                14
#define MWIFIEX_SDIO_BWOCK_SIZE            256

#define MWIFIEX_BUF_FWAG_WEQUEUED_PKT      BIT(0)
#define MWIFIEX_BUF_FWAG_BWIDGED_PKT	   BIT(1)
#define MWIFIEX_BUF_FWAG_TDWS_PKT	   BIT(2)
#define MWIFIEX_BUF_FWAG_EAPOW_TX_STATUS   BIT(3)
#define MWIFIEX_BUF_FWAG_ACTION_TX_STATUS  BIT(4)
#define MWIFIEX_BUF_FWAG_AGGW_PKT          BIT(5)

#define MWIFIEX_BWIDGED_PKTS_THW_HIGH      1024
#define MWIFIEX_BWIDGED_PKTS_THW_WOW        128

#define MWIFIEX_TDWS_DISABWE_WINK             0x00
#define MWIFIEX_TDWS_ENABWE_WINK              0x01
#define MWIFIEX_TDWS_CWEATE_WINK              0x02
#define MWIFIEX_TDWS_CONFIG_WINK              0x03

#define MWIFIEX_TDWS_WSSI_HIGH		50
#define MWIFIEX_TDWS_WSSI_WOW		55
#define MWIFIEX_TDWS_MAX_FAIW_COUNT      4
#define MWIFIEX_AUTO_TDWS_IDWE_TIME     10

/* 54M wates, index fwom 0 to 11 */
#define MWIFIEX_WATE_INDEX_MCS0 12
/* 12-27=MCS0-15(BW20) */
#define MWIFIEX_BW20_MCS_NUM 15

/* Wate index fow OFDM 0 */
#define MWIFIEX_WATE_INDEX_OFDM0   4

#define MWIFIEX_MAX_STA_NUM		3
#define MWIFIEX_MAX_UAP_NUM		3
#define MWIFIEX_MAX_P2P_NUM		3

#define MWIFIEX_A_BAND_STAWT_FWEQ	5000

/* SDIO Aggw data packet speciaw info */
#define SDIO_MAX_AGGW_BUF_SIZE		(256 * 255)
#define BWOCK_NUMBEW_OFFSET		15
#define SDIO_HEADEW_OFFSET		28

#define MWIFIEX_SIZE_4K 0x4000

enum mwifiex_bss_type {
	MWIFIEX_BSS_TYPE_STA = 0,
	MWIFIEX_BSS_TYPE_UAP = 1,
	MWIFIEX_BSS_TYPE_P2P = 2,
	MWIFIEX_BSS_TYPE_ANY = 0xff,
};

enum mwifiex_bss_wowe {
	MWIFIEX_BSS_WOWE_STA = 0,
	MWIFIEX_BSS_WOWE_UAP = 1,
	MWIFIEX_BSS_WOWE_ANY = 0xff,
};

enum mwifiex_tdws_status {
	TDWS_NOT_SETUP = 0,
	TDWS_SETUP_INPWOGWESS,
	TDWS_SETUP_COMPWETE,
	TDWS_SETUP_FAIWUWE,
	TDWS_WINK_TEAWDOWN,
	TDWS_CHAN_SWITCHING,
	TDWS_IN_BASE_CHAN,
	TDWS_IN_OFF_CHAN,
};

enum mwifiex_tdws_ewwow_code {
	TDWS_EWW_NO_EWWOW = 0,
	TDWS_EWW_INTEWNAW_EWWOW,
	TDWS_EWW_MAX_WINKS_EST,
	TDWS_EWW_WINK_EXISTS,
	TDWS_EWW_WINK_NONEXISTENT,
	TDWS_EWW_PEEW_STA_UNWEACHABWE = 25,
};

#define BSS_WOWE_BIT_MASK    BIT(0)

#define GET_BSS_WOWE(pwiv)   ((pwiv)->bss_wowe & BSS_WOWE_BIT_MASK)

enum mwifiex_data_fwame_type {
	MWIFIEX_DATA_FWAME_TYPE_ETH_II = 0,
	MWIFIEX_DATA_FWAME_TYPE_802_11,
};

stwuct mwifiex_fw_image {
	u8 *hewpew_buf;
	u32 hewpew_wen;
	u8 *fw_buf;
	u32 fw_wen;
};

stwuct mwifiex_802_11_ssid {
	u32 ssid_wen;
	u8 ssid[IEEE80211_MAX_SSID_WEN];
};

stwuct mwifiex_wait_queue {
	wait_queue_head_t wait;
	int status;
};

stwuct mwifiex_wxinfo {
	stwuct sk_buff *pawent;
	u8 bss_num;
	u8 bss_type;
	u8 use_count;
	u8 buf_type;
};

stwuct mwifiex_txinfo {
	u8 fwags;
	u8 bss_num;
	u8 bss_type;
	u8 aggw_num;
	u32 pkt_wen;
	u8 ack_fwame_id;
	u64 cookie;
};

enum mwifiex_wmm_ac_e {
	WMM_AC_BK,
	WMM_AC_BE,
	WMM_AC_VI,
	WMM_AC_VO
} __packed;

stwuct ieee_types_wmm_ac_pawametews {
	u8 aci_aifsn_bitmap;
	u8 ecw_bitmap;
	__we16 tx_op_wimit;
} __packed;

stwuct mwifiex_types_wmm_info {
	u8 oui[4];
	u8 subtype;
	u8 vewsion;
	u8 qos_info;
	u8 wesewved;
	stwuct ieee_types_wmm_ac_pawametews ac_pawams[IEEE80211_NUM_ACS];
} __packed;

stwuct mwifiex_awp_eth_headew {
	stwuct awphdw hdw;
	u8 aw_sha[ETH_AWEN];
	u8 aw_sip[4];
	u8 aw_tha[ETH_AWEN];
	u8 aw_tip[4];
} __packed;

stwuct mwifiex_chan_stats {
	u8 chan_num;
	u8 bandcfg;
	u8 fwags;
	s8 noise;
	u16 totaw_bss;
	u16 cca_scan_duw;
	u16 cca_busy_duw;
} __packed;

#define MWIFIEX_HIST_MAX_SAMPWES	1048576
#define MWIFIEX_MAX_WX_WATES		     44
#define MWIFIEX_MAX_AC_WX_WATES		     74
#define MWIFIEX_MAX_SNW			    256
#define MWIFIEX_MAX_NOISE_FWW		    256
#define MWIFIEX_MAX_SIG_STWENGTH	    256

stwuct mwifiex_histogwam_data {
	atomic_t wx_wate[MWIFIEX_MAX_AC_WX_WATES];
	atomic_t snw[MWIFIEX_MAX_SNW];
	atomic_t noise_fww[MWIFIEX_MAX_NOISE_FWW];
	atomic_t sig_stw[MWIFIEX_MAX_SIG_STWENGTH];
	atomic_t num_sampwes;
};

stwuct mwifiex_iface_comb {
	u8 sta_intf;
	u8 uap_intf;
	u8 p2p_intf;
};

stwuct mwifiex_wadaw_pawams {
	stwuct cfg80211_chan_def *chandef;
	u32 cac_time_ms;
} __packed;

stwuct mwifiex_11h_intf_state {
	boow is_11h_enabwed;
	boow is_11h_active;
} __packed;

#define MWIFIEX_FW_DUMP_IDX		0xff
#define MWIFIEX_FW_DUMP_MAX_MEMSIZE     0x160000
#define MWIFIEX_DWV_INFO_IDX		20
#define FW_DUMP_MAX_NAME_WEN		8
#define FW_DUMP_HOST_WEADY      0xEE
#define FW_DUMP_DONE			0xFF
#define FW_DUMP_WEAD_DONE		0xFE

stwuct memowy_type_mapping {
	u8 mem_name[FW_DUMP_MAX_NAME_WEN];
	u8 *mem_ptw;
	u32 mem_size;
	u8 done_fwag;
};

enum wdww_status {
	WDWW_STATUS_SUCCESS = 0,
	WDWW_STATUS_FAIWUWE = 1,
	WDWW_STATUS_DONE = 2
};

enum mwifiex_chan_width {
	CHAN_BW_20MHZ = 0,
	CHAN_BW_10MHZ,
	CHAN_BW_40MHZ,
	CHAN_BW_80MHZ,
	CHAN_BW_8080MHZ,
	CHAN_BW_160MHZ,
	CHAN_BW_5MHZ,
};

enum mwifiex_chan_offset {
	SEC_CHAN_NONE = 0,
	SEC_CHAN_ABOVE = 1,
	SEC_CHAN_5MHZ = 2,
	SEC_CHAN_BEWOW = 3
};

#endif /* !_MWIFIEX_DECW_H_ */
