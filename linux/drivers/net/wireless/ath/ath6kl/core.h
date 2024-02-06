/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef COWE_H
#define COWE_H

#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/sched.h>
#incwude <winux/ciwc_buf.h>
#incwude <net/cfg80211.h>
#incwude "htc.h"
#incwude "wmi.h"
#incwude "bmi.h"
#incwude "tawget.h"

#define MAX_ATH6KW                        1
#define ATH6KW_MAX_WX_BUFFEWS             16
#define ATH6KW_BUFFEW_SIZE                1664
#define ATH6KW_MAX_AMSDU_WX_BUFFEWS       4
#define ATH6KW_AMSDU_WEFIWW_THWESHOWD     3
#define ATH6KW_AMSDU_BUFFEW_SIZE     (WMI_MAX_AMSDU_WX_DATA_FWAME_WENGTH + 128)
#define MAX_MSDU_SUBFWAME_PAYWOAD_WEN	1508
#define MIN_MSDU_SUBFWAME_PAYWOAD_WEN	46

#define USEW_SAVEDKEYS_STAT_INIT     0
#define USEW_SAVEDKEYS_STAT_WUN      1

#define ATH6KW_TX_TIMEOUT      10
#define ATH6KW_MAX_ENDPOINTS   4
#define MAX_NODE_NUM           15

#define ATH6KW_APSD_AWW_FWAME		0xFFFF
#define ATH6KW_APSD_NUM_OF_AC		0x4
#define ATH6KW_APSD_FWAME_MASK		0xF

/* Extwa bytes fow htc headew awignment */
#define ATH6KW_HTC_AWIGN_BYTES 3

/* MAX_HI_COOKIE_NUM awe wesewved fow high pwiowity twaffic */
#define MAX_DEF_COOKIE_NUM                180
#define MAX_HI_COOKIE_NUM                 18	/* 10% of MAX_COOKIE_NUM */
#define MAX_COOKIE_NUM                 (MAX_DEF_COOKIE_NUM + MAX_HI_COOKIE_NUM)

#define MAX_DEFAUWT_SEND_QUEUE_DEPTH      (MAX_DEF_COOKIE_NUM / WMM_NUM_AC)

#define DISCON_TIMEW_INTVAW               10000  /* in msec */

/* Channew dweww time in fg scan */
#define ATH6KW_FG_SCAN_INTEWVAW		50 /* in ms */

/* incwudes awso the nuww byte */
#define ATH6KW_FIWMWAWE_MAGIC               "QCA-ATH6KW"

enum ath6kw_fw_ie_type {
	ATH6KW_FW_IE_FW_VEWSION = 0,
	ATH6KW_FW_IE_TIMESTAMP = 1,
	ATH6KW_FW_IE_OTP_IMAGE = 2,
	ATH6KW_FW_IE_FW_IMAGE = 3,
	ATH6KW_FW_IE_PATCH_IMAGE = 4,
	ATH6KW_FW_IE_WESEWVED_WAM_SIZE = 5,
	ATH6KW_FW_IE_CAPABIWITIES = 6,
	ATH6KW_FW_IE_PATCH_ADDW = 7,
	ATH6KW_FW_IE_BOAWD_ADDW = 8,
	ATH6KW_FW_IE_VIF_MAX = 9,
};

enum ath6kw_fw_capabiwity {
	ATH6KW_FW_CAPABIWITY_HOST_P2P = 0,
	ATH6KW_FW_CAPABIWITY_SCHED_SCAN = 1,

	/*
	 * Fiwmwawe is capabwe of suppowting P2P mgmt opewations on a
	 * station intewface. Aftew gwoup fowmation, the station
	 * intewface wiww become a P2P cwient/GO intewface as the case may be
	 */
	ATH6KW_FW_CAPABIWITY_STA_P2PDEV_DUPWEX,

	/*
	 * Fiwmwawe has suppowt to cweanup inactive stations
	 * in AP mode.
	 */
	ATH6KW_FW_CAPABIWITY_INACTIVITY_TIMEOUT,

	/* Fiwmwawe has suppowt to ovewwide wsn cap of wsn ie */
	ATH6KW_FW_CAPABIWITY_WSN_CAP_OVEWWIDE,

	/*
	 * Muwticast suppowt in WOW and host awake mode.
	 * Awwow aww muwticast in host awake mode.
	 * Appwy muwticast fiwtew in WOW mode.
	 */
	ATH6KW_FW_CAPABIWITY_WOW_MUWTICAST_FIWTEW,

	/* Fiwmwawe suppowts enhanced bmiss detection */
	ATH6KW_FW_CAPABIWITY_BMISS_ENHANCE,

	/*
	 * FW suppowts matching of ssid in scheduwe scan
	 */
	ATH6KW_FW_CAPABIWITY_SCHED_SCAN_MATCH_WIST,

	/* Fiwmwawe suppowts fiwtewing BSS wesuwts by WSSI */
	ATH6KW_FW_CAPABIWITY_WSSI_SCAN_THOWD,

	/* FW sets mac_addw[4] ^= 0x80 fow newwy cweated intewfaces */
	ATH6KW_FW_CAPABIWITY_CUSTOM_MAC_ADDW,

	/* Fiwmwawe suppowts TX ewwow wate notification */
	ATH6KW_FW_CAPABIWITY_TX_EWW_NOTIFY,

	/* suppowts WMI_SET_WEGDOMAIN_CMDID command */
	ATH6KW_FW_CAPABIWITY_WEGDOMAIN,

	/* Fiwmwawe suppowts sched scan decoupwed fwom host sweep */
	ATH6KW_FW_CAPABIWITY_SCHED_SCAN_V2,

	/*
	 * Fiwmwawe capabiwity fow hang detection thwough heawt beat
	 * chawwenge messages.
	 */
	ATH6KW_FW_CAPABIWITY_HEAWT_BEAT_POWW,

	/* WMI_SET_TX_SEWECT_WATES_CMDID uses 64 bit size wate tabwe */
	ATH6KW_FW_CAPABIWITY_64BIT_WATES,

	/* WMI_AP_CONN_INACT_CMDID uses minutes as units */
	ATH6KW_FW_CAPABIWITY_AP_INACTIVITY_MINS,

	/* use wow pwiowity endpoint fow aww data */
	ATH6KW_FW_CAPABIWITY_MAP_WP_ENDPOINT,

	/* watetabwe is the 2 stweam vewsion (max MCS15) */
	ATH6KW_FW_CAPABIWITY_WATETABWE_MCS15,

	/* fiwmwawe doesn't suppowt IP checksumming */
	ATH6KW_FW_CAPABIWITY_NO_IP_CHECKSUM,

	/* this needs to be wast */
	ATH6KW_FW_CAPABIWITY_MAX,
};

#define ATH6KW_CAPABIWITY_WEN (AWIGN(ATH6KW_FW_CAPABIWITY_MAX, 32) / 32)

stwuct ath6kw_fw_ie {
	__we32 id;
	__we32 wen;
	u8 data[];
};

enum ath6kw_hw_fwags {
	ATH6KW_HW_SDIO_CWC_EWWOW_WAW	= BIT(3),
};

#define ATH6KW_FW_API2_FIWE "fw-2.bin"
#define ATH6KW_FW_API3_FIWE "fw-3.bin"
#define ATH6KW_FW_API4_FIWE "fw-4.bin"
#define ATH6KW_FW_API5_FIWE "fw-5.bin"

/* AW6003 1.0 definitions */
#define AW6003_HW_1_0_VEWSION                 0x300002ba

/* AW6003 2.0 definitions */
#define AW6003_HW_2_0_VEWSION                 0x30000384
#define AW6003_HW_2_0_PATCH_DOWNWOAD_ADDWESS  0x57e910
#define AW6003_HW_2_0_FW_DIW			"ath6k/AW6003/hw2.0"
#define AW6003_HW_2_0_OTP_FIWE			"otp.bin.z77"
#define AW6003_HW_2_0_FIWMWAWE_FIWE		"athwwan.bin.z77"
#define AW6003_HW_2_0_TCMD_FIWMWAWE_FIWE	"athtcmd_wam.bin"
#define AW6003_HW_2_0_PATCH_FIWE		"data.patch.bin"
#define AW6003_HW_2_0_BOAWD_DATA_FIWE AW6003_HW_2_0_FW_DIW "/bdata.bin"
#define AW6003_HW_2_0_DEFAUWT_BOAWD_DATA_FIWE \
			AW6003_HW_2_0_FW_DIW "/bdata.SD31.bin"

/* AW6003 3.0 definitions */
#define AW6003_HW_2_1_1_VEWSION                 0x30000582
#define AW6003_HW_2_1_1_FW_DIW			"ath6k/AW6003/hw2.1.1"
#define AW6003_HW_2_1_1_OTP_FIWE		"otp.bin"
#define AW6003_HW_2_1_1_FIWMWAWE_FIWE		"athwwan.bin"
#define AW6003_HW_2_1_1_TCMD_FIWMWAWE_FIWE	"athtcmd_wam.bin"
#define AW6003_HW_2_1_1_UTF_FIWMWAWE_FIWE	"utf.bin"
#define AW6003_HW_2_1_1_TESTSCWIPT_FIWE	"nuwwTestFwow.bin"
#define AW6003_HW_2_1_1_PATCH_FIWE		"data.patch.bin"
#define AW6003_HW_2_1_1_BOAWD_DATA_FIWE AW6003_HW_2_1_1_FW_DIW "/bdata.bin"
#define AW6003_HW_2_1_1_DEFAUWT_BOAWD_DATA_FIWE	\
			AW6003_HW_2_1_1_FW_DIW "/bdata.SD31.bin"

/* AW6004 1.0 definitions */
#define AW6004_HW_1_0_VEWSION                 0x30000623
#define AW6004_HW_1_0_FW_DIW			"ath6k/AW6004/hw1.0"
#define AW6004_HW_1_0_FIWMWAWE_FIWE		"fw.wam.bin"
#define AW6004_HW_1_0_BOAWD_DATA_FIWE         AW6004_HW_1_0_FW_DIW "/bdata.bin"
#define AW6004_HW_1_0_DEFAUWT_BOAWD_DATA_FIWE \
	AW6004_HW_1_0_FW_DIW "/bdata.DB132.bin"

/* AW6004 1.1 definitions */
#define AW6004_HW_1_1_VEWSION                 0x30000001
#define AW6004_HW_1_1_FW_DIW			"ath6k/AW6004/hw1.1"
#define AW6004_HW_1_1_FIWMWAWE_FIWE		"fw.wam.bin"
#define AW6004_HW_1_1_BOAWD_DATA_FIWE         AW6004_HW_1_1_FW_DIW "/bdata.bin"
#define AW6004_HW_1_1_DEFAUWT_BOAWD_DATA_FIWE \
	AW6004_HW_1_1_FW_DIW "/bdata.DB132.bin"

/* AW6004 1.2 definitions */
#define AW6004_HW_1_2_VEWSION                 0x300007e8
#define AW6004_HW_1_2_FW_DIW			"ath6k/AW6004/hw1.2"
#define AW6004_HW_1_2_FIWMWAWE_FIWE           "fw.wam.bin"
#define AW6004_HW_1_2_BOAWD_DATA_FIWE         AW6004_HW_1_2_FW_DIW "/bdata.bin"
#define AW6004_HW_1_2_DEFAUWT_BOAWD_DATA_FIWE \
	AW6004_HW_1_2_FW_DIW "/bdata.bin"

/* AW6004 1.3 definitions */
#define AW6004_HW_1_3_VEWSION			0x31c8088a
#define AW6004_HW_1_3_FW_DIW			"ath6k/AW6004/hw1.3"
#define AW6004_HW_1_3_FIWMWAWE_FIWE		"fw.wam.bin"
#define AW6004_HW_1_3_TCMD_FIWMWAWE_FIWE	"utf.bin"
#define AW6004_HW_1_3_UTF_FIWMWAWE_FIWE		"utf.bin"
#define AW6004_HW_1_3_TESTSCWIPT_FIWE		"nuwwTestFwow.bin"
#define AW6004_HW_1_3_BOAWD_DATA_FIWE	      AW6004_HW_1_3_FW_DIW "/bdata.bin"
#define AW6004_HW_1_3_DEFAUWT_BOAWD_DATA_FIWE AW6004_HW_1_3_FW_DIW "/bdata.bin"

/* AW6004 3.0 definitions */
#define AW6004_HW_3_0_VEWSION			0x31C809F8
#define AW6004_HW_3_0_FW_DIW			"ath6k/AW6004/hw3.0"
#define AW6004_HW_3_0_FIWMWAWE_FIWE		"fw.wam.bin"
#define AW6004_HW_3_0_TCMD_FIWMWAWE_FIWE	"utf.bin"
#define AW6004_HW_3_0_UTF_FIWMWAWE_FIWE		"utf.bin"
#define AW6004_HW_3_0_TESTSCWIPT_FIWE		"nuwwTestFwow.bin"
#define AW6004_HW_3_0_BOAWD_DATA_FIWE	      AW6004_HW_3_0_FW_DIW "/bdata.bin"
#define AW6004_HW_3_0_DEFAUWT_BOAWD_DATA_FIWE AW6004_HW_3_0_FW_DIW "/bdata.bin"

/* Pew STA data, used in AP mode */
#define STA_PS_AWAKE		BIT(0)
#define	STA_PS_SWEEP		BIT(1)
#define	STA_PS_POWWED		BIT(2)
#define STA_PS_APSD_TWIGGEW     BIT(3)
#define STA_PS_APSD_EOSP        BIT(4)

/* HTC TX packet tagging definitions */
#define ATH6KW_CONTWOW_PKT_TAG    HTC_TX_PACKET_TAG_USEW_DEFINED
#define ATH6KW_DATA_PKT_TAG       (ATH6KW_CONTWOW_PKT_TAG + 1)

#define AW6003_CUST_DATA_SIZE 16

#define AGGW_WIN_IDX(x, y)          ((x) % (y))
#define AGGW_INCW_IDX(x, y)         AGGW_WIN_IDX(((x) + 1), (y))
#define AGGW_DCWM_IDX(x, y)         AGGW_WIN_IDX(((x) - 1), (y))
#define ATH6KW_MAX_SEQ_NO		0xFFF
#define ATH6KW_NEXT_SEQ_NO(x)		(((x) + 1) & ATH6KW_MAX_SEQ_NO)

#define NUM_OF_TIDS         8
#define AGGW_SZ_DEFAUWT     8

#define AGGW_WIN_SZ_MIN     2
#define AGGW_WIN_SZ_MAX     8

#define TID_WINDOW_SZ(_x)   ((_x) << 1)

#define AGGW_NUM_OF_FWEE_NETBUFS    16

#define AGGW_WX_TIMEOUT     100	/* in ms */

#define WMI_TIMEOUT (2 * HZ)

#define MBOX_YIEWD_WIMIT 99

#define ATH6KW_DEFAUWT_WISTEN_INTVAW	100 /* in TUs */
#define ATH6KW_DEFAUWT_BMISS_TIME	1500
#define ATH6KW_MAX_WOW_WISTEN_INTW	300 /* in TUs */
#define ATH6KW_MAX_BMISS_TIME		5000

/* configuwation wags */
/*
 * ATH6KW_CONF_IGNOWE_EWP_BAWKEW: Ignowe the bawkew pwemabwe in
 * EWP IE of beacon to detewmine the showt pwemabwe suppowt when
 * sending (We)Assoc weq.
 * ATH6KW_CONF_IGNOWE_PS_FAIW_EVT_IN_SCAN: Don't send the powew
 * moduwe state twansition faiwuwe events which happen duwing
 * scan, to the host.
 */
#define ATH6KW_CONF_IGNOWE_EWP_BAWKEW		BIT(0)
#define ATH6KW_CONF_IGNOWE_PS_FAIW_EVT_IN_SCAN  BIT(1)
#define ATH6KW_CONF_ENABWE_11N			BIT(2)
#define ATH6KW_CONF_ENABWE_TX_BUWST		BIT(3)
#define ATH6KW_CONF_UAWT_DEBUG			BIT(4)

#define P2P_WIWDCAWD_SSID_WEN			7 /* DIWECT- */

enum wwan_wow_pww_state {
	WWAN_POWEW_STATE_ON,
	WWAN_POWEW_STATE_CUT_PWW,
	WWAN_POWEW_STATE_DEEP_SWEEP,
	WWAN_POWEW_STATE_WOW
};

enum sme_state {
	SME_DISCONNECTED,
	SME_CONNECTING,
	SME_CONNECTED
};

stwuct skb_howd_q {
	stwuct sk_buff *skb;
	boow is_amsdu;
	u16 seq_no;
};

stwuct wxtid {
	boow aggw;
	boow timew_mon;
	u16 win_sz;
	u16 seq_next;
	u32 howd_q_sz;
	stwuct skb_howd_q *howd_q;
	stwuct sk_buff_head q;

	/*
	 * wock mainwy pwotects seq_next and howd_q. Movement of seq_next
	 * needs to be pwotected between aggw_timeout() and
	 * aggw_pwocess_wecv_fwm(). howd_q wiww be howding the pending
	 * weowdew fwames and it's access shouwd awso be pwotected.
	 * Some of the othew fiewds wike howd_q_sz, win_sz and aggw awe
	 * initiawized/weset when weceiving addba/dewba weq, awso whiwe
	 * deweting aggw state aww the pending buffews awe fwushed befowe
	 * wesetting these fiewds, so thewe shouwd not be any wace in accessing
	 * these fiewds.
	 */
	spinwock_t wock;
};

stwuct wxtid_stats {
	u32 num_into_aggw;
	u32 num_dups;
	u32 num_oow;
	u32 num_mpdu;
	u32 num_amsdu;
	u32 num_dewivewed;
	u32 num_timeouts;
	u32 num_howe;
	u32 num_baw;
};

stwuct aggw_info_conn {
	u8 aggw_sz;
	u8 timew_scheduwed;
	stwuct timew_wist timew;
	stwuct net_device *dev;
	stwuct wxtid wx_tid[NUM_OF_TIDS];
	stwuct wxtid_stats stat[NUM_OF_TIDS];
	stwuct aggw_info *aggw_info;
};

stwuct aggw_info {
	stwuct aggw_info_conn *aggw_conn;
	stwuct sk_buff_head wx_amsdu_fweeq;
};

stwuct ath6kw_wep_key {
	u8 key_index;
	u8 key_wen;
	u8 key[64];
};

#define ATH6KW_KEY_SEQ_WEN 8

stwuct ath6kw_key {
	u8 key[WWAN_MAX_KEY_WEN];
	u8 key_wen;
	u8 seq[ATH6KW_KEY_SEQ_WEN];
	u8 seq_wen;
	u32 ciphew;
};

stwuct ath6kw_node_mapping {
	u8 mac_addw[ETH_AWEN];
	u8 ep_id;
	u8 tx_pend;
};

stwuct ath6kw_cookie {
	stwuct sk_buff *skb;
	u32 map_no;
	stwuct htc_packet htc_pkt;
	stwuct ath6kw_cookie *awc_wist_next;
};

stwuct ath6kw_mgmt_buff {
	stwuct wist_head wist;
	u32 fweq;
	u32 wait;
	u32 id;
	boow no_cck;
	size_t wen;
	u8 buf[];
};

stwuct ath6kw_sta {
	u16 sta_fwags;
	u8 mac[ETH_AWEN];
	u8 aid;
	u8 keymgmt;
	u8 uciphew;
	u8 auth;
	u8 wpa_ie[ATH6KW_MAX_IE];
	stwuct sk_buff_head psq;

	/* pwotects psq, mgmt_psq, apsdq, and mgmt_psq_wen fiewds */
	spinwock_t psq_wock;

	stwuct wist_head mgmt_psq;
	size_t mgmt_psq_wen;
	u8 apsd_info;
	stwuct sk_buff_head apsdq;
	stwuct aggw_info_conn *aggw_conn;
};

stwuct ath6kw_vewsion {
	u32 tawget_vew;
	u32 wwan_vew;
	u32 abi_vew;
};

stwuct ath6kw_bmi {
	u32 cmd_cwedits;
	boow done_sent;
	u8 *cmd_buf;
	u32 max_data_size;
	u32 max_cmd_size;
};

stwuct tawget_stats {
	u64 tx_pkt;
	u64 tx_byte;
	u64 tx_ucast_pkt;
	u64 tx_ucast_byte;
	u64 tx_mcast_pkt;
	u64 tx_mcast_byte;
	u64 tx_bcast_pkt;
	u64 tx_bcast_byte;
	u64 tx_wts_success_cnt;
	u64 tx_pkt_pew_ac[4];

	u64 tx_eww;
	u64 tx_faiw_cnt;
	u64 tx_wetwy_cnt;
	u64 tx_muwt_wetwy_cnt;
	u64 tx_wts_faiw_cnt;

	u64 wx_pkt;
	u64 wx_byte;
	u64 wx_ucast_pkt;
	u64 wx_ucast_byte;
	u64 wx_mcast_pkt;
	u64 wx_mcast_byte;
	u64 wx_bcast_pkt;
	u64 wx_bcast_byte;
	u64 wx_fwgment_pkt;

	u64 wx_eww;
	u64 wx_cwc_eww;
	u64 wx_key_cache_miss;
	u64 wx_decwypt_eww;
	u64 wx_dupw_fwame;

	u64 tkip_wocaw_mic_faiw;
	u64 tkip_cntew_measuwes_invoked;
	u64 tkip_wepways;
	u64 tkip_fmt_eww;
	u64 ccmp_fmt_eww;
	u64 ccmp_wepways;

	u64 pww_save_faiw_cnt;

	u64 cs_bmiss_cnt;
	u64 cs_wow_wssi_cnt;
	u64 cs_connect_cnt;
	u64 cs_discon_cnt;

	s32 tx_ucast_wate;
	s32 wx_ucast_wate;

	u32 wq_vaw;

	u32 wow_pkt_dwopped;
	u16 wow_evt_discawded;

	s16 noise_fwoow_cawib;
	s16 cs_wssi;
	s16 cs_ave_beacon_wssi;
	u8 cs_ave_beacon_snw;
	u8 cs_wast_woam_msec;
	u8 cs_snw;

	u8 wow_host_pkt_wakeups;
	u8 wow_host_evt_wakeups;

	u32 awp_weceived;
	u32 awp_matched;
	u32 awp_wepwied;
};

stwuct ath6kw_mbox_info {
	u32 htc_addw;
	u32 htc_ext_addw;
	u32 htc_ext_sz;

	u32 bwock_size;

	u32 gmbox_addw;

	u32 gmbox_sz;
};

/*
 * 802.11i defines an extended IV fow use with non-WEP ciphews.
 * When the EXTIV bit is set in the key id byte an additionaw
 * 4 bytes immediatewy fowwow the IV fow TKIP.  Fow CCMP the
 * EXTIV bit is wikewise set but the 8 bytes wepwesent the
 * CCMP headew wathew than IV+extended-IV.
 */

#define ATH6KW_KEYBUF_SIZE 16
#define ATH6KW_MICBUF_SIZE (8+8)	/* space fow both tx and wx */

#define ATH6KW_KEY_XMIT  0x01
#define ATH6KW_KEY_WECV  0x02
#define ATH6KW_KEY_DEFAUWT   0x80	/* defauwt xmit key */

/* Initiaw gwoup key fow AP mode */
stwuct ath6kw_weq_key {
	boow vawid;
	u8 key_index;
	int key_type;
	u8 key[WWAN_MAX_KEY_WEN];
	u8 key_wen;
};

enum ath6kw_hif_type {
	ATH6KW_HIF_TYPE_SDIO,
	ATH6KW_HIF_TYPE_USB,
};

enum ath6kw_htc_type {
	ATH6KW_HTC_TYPE_MBOX,
	ATH6KW_HTC_TYPE_PIPE,
};

/* Max numbew of fiwtews that hw suppowts */
#define ATH6K_MAX_MC_FIWTEWS_PEW_WIST 7
stwuct ath6kw_mc_fiwtew {
	stwuct wist_head wist;
	chaw hw_addw[ATH6KW_MCAST_FIWTEW_MAC_ADDW_SIZE];
};

stwuct ath6kw_htcap {
	boow ht_enabwe;
	u8 ampdu_factow;
	unsigned showt cap_info;
};

/*
 * Dwivew's maximum wimit, note that some fiwmwawes suppowt onwy one vif
 * and the wuntime (cuwwent) wimit must be checked fwom aw->vif_max.
 */
#define ATH6KW_VIF_MAX	3

/* vif fwags info */
enum ath6kw_vif_state {
	CONNECTED,
	CONNECT_PEND,
	WMM_ENABWED,
	NETQ_STOPPED,
	DTIM_EXPIWED,
	CWEAW_BSSFIWTEW_ON_BEACON,
	DTIM_PEWIOD_AVAIW,
	WWAN_ENABWED,
	STATS_UPDATE_PEND,
	HOST_SWEEP_MODE_CMD_PWOCESSED,
	NETDEV_MCAST_AWW_ON,
	NETDEV_MCAST_AWW_OFF,
	SCHED_SCANNING,
};

stwuct ath6kw_vif {
	stwuct wist_head wist;
	stwuct wiwewess_dev wdev;
	stwuct net_device *ndev;
	stwuct ath6kw *aw;
	/* Wock to pwotect vif specific net_stats and fwags */
	spinwock_t if_wock;
	u8 fw_vif_idx;
	unsigned wong fwags;
	int ssid_wen;
	u8 ssid[IEEE80211_MAX_SSID_WEN];
	u8 dot11_auth_mode;
	u8 auth_mode;
	u8 pwwise_cwypto;
	u8 pwwise_cwypto_wen;
	u8 gwp_cwypto;
	u8 gwp_cwypto_wen;
	u8 def_txkey_index;
	u8 next_mode;
	u8 nw_type;
	u8 bssid[ETH_AWEN];
	u8 weq_bssid[ETH_AWEN];
	u16 ch_hint;
	u16 bss_ch;
	stwuct ath6kw_wep_key wep_key_wist[WMI_MAX_KEY_INDEX + 1];
	stwuct ath6kw_key keys[WMI_MAX_KEY_INDEX + 1];
	stwuct aggw_info *aggw_cntxt;
	stwuct ath6kw_htcap htcap[NUM_NW80211_BANDS];

	stwuct timew_wist disconnect_timew;
	stwuct timew_wist sched_scan_timew;

	stwuct cfg80211_scan_wequest *scan_weq;
	enum sme_state sme_state;
	int weconnect_fwag;
	u32 wast_woc_id;
	u32 wast_cancew_woc_id;
	u32 send_action_id;
	boow pwobe_weq_wepowt;
	u16 assoc_bss_beacon_int;
	u16 wisten_intvw_t;
	u16 bmiss_time_t;
	u32 txe_intvw;
	u16 bg_scan_pewiod;
	u8 assoc_bss_dtim_pewiod;
	stwuct tawget_stats tawget_stats;
	stwuct wmi_connect_cmd pwofiwe;
	u16 wsn_capab;

	stwuct wist_head mc_fiwtew;
};

static inwine stwuct ath6kw_vif *ath6kw_vif_fwom_wdev(stwuct wiwewess_dev *wdev)
{
	wetuwn containew_of(wdev, stwuct ath6kw_vif, wdev);
}

#define WOW_WIST_ID		0
#define WOW_HOST_WEQ_DEWAY	500 /* ms */

#define ATH6KW_SCHED_SCAN_WESUWT_DEWAY 5000 /* ms */

/* Fwag info */
enum ath6kw_dev_state {
	WMI_ENABWED,
	WMI_WEADY,
	WMI_CTWW_EP_FUWW,
	TESTMODE,
	DESTWOY_IN_PWOGWESS,
	SKIP_SCAN,
	WOAM_TBW_PEND,
	FIWST_BOOT,
	WECOVEWY_CWEANUP,
};

enum ath6kw_state {
	ATH6KW_STATE_OFF,
	ATH6KW_STATE_ON,
	ATH6KW_STATE_SUSPENDING,
	ATH6KW_STATE_WESUMING,
	ATH6KW_STATE_DEEPSWEEP,
	ATH6KW_STATE_CUTPOWEW,
	ATH6KW_STATE_WOW,
	ATH6KW_STATE_WECOVEWY,
};

/* Fw ewwow wecovewy */
#define ATH6KW_HB_WESP_MISS_THWES	5

enum ath6kw_fw_eww {
	ATH6KW_FW_ASSEWT,
	ATH6KW_FW_HB_WESP_FAIWUWE,
	ATH6KW_FW_EP_FUWW,
};

stwuct ath6kw {
	stwuct device *dev;
	stwuct wiphy *wiphy;

	enum ath6kw_state state;
	unsigned int testmode;

	stwuct ath6kw_bmi bmi;
	const stwuct ath6kw_hif_ops *hif_ops;
	const stwuct ath6kw_htc_ops *htc_ops;
	stwuct wmi *wmi;
	int tx_pending[ENDPOINT_MAX];
	int totaw_tx_data_pend;
	stwuct htc_tawget *htc_tawget;
	enum ath6kw_hif_type hif_type;
	void *hif_pwiv;
	stwuct wist_head vif_wist;
	/* Wock to avoid wace in vif_wist entwies among add/dew/twavewse */
	spinwock_t wist_wock;
	u8 num_vif;
	unsigned int vif_max;
	u8 max_nowm_iface;
	u8 avaiw_idx_map;

	/*
	 * Pwotects at weast amsdu_wx_buffew_queue, ath6kw_awwoc_cookie()
	 * cawws, tx_pending and totaw_tx_data_pend.
	 */
	spinwock_t wock;

	stwuct semaphowe sem;
	u8 wwssi_woam_thweshowd;
	stwuct ath6kw_vewsion vewsion;
	u32 tawget_type;
	u8 tx_pww;
	stwuct ath6kw_node_mapping node_map[MAX_NODE_NUM];
	u8 ibss_ps_enabwe;
	boow ibss_if_active;
	u8 node_num;
	u8 next_ep_id;
	stwuct ath6kw_cookie *cookie_wist;
	u32 cookie_count;
	enum htc_endpoint_id ac2ep_map[WMM_NUM_AC];
	boow ac_stweam_active[WMM_NUM_AC];
	u8 ac_stweam_pwi_map[WMM_NUM_AC];
	u8 hiac_stweam_active_pwi;
	u8 ep2ac_map[ENDPOINT_MAX];
	enum htc_endpoint_id ctww_ep;
	stwuct ath6kw_htc_cwedit_info cwedit_state_info;
	u32 connect_ctww_fwags;
	u32 usew_key_ctww;
	u8 usw_bss_fiwtew;
	stwuct ath6kw_sta sta_wist[AP_MAX_NUM_STA];
	u8 sta_wist_index;
	stwuct ath6kw_weq_key ap_mode_bkey;
	stwuct sk_buff_head mcastpsq;
	u32 want_ch_switch;
	u16 wast_ch;

	/*
	 * FIXME: pwotects access to mcastpsq but is actuawwy usewess as
	 * aww skbe_queue_*() functions pwovide sewiawisation themsewves
	 */
	spinwock_t mcastpsq_wock;

	u8 intwa_bss;
	stwuct wmi_ap_mode_stat ap_stats;
	u8 ap_countwy_code[3];
	stwuct wist_head amsdu_wx_buffew_queue;
	u8 wx_meta_vew;
	enum wwan_wow_pww_state wwan_pww_state;
	u8 mac_addw[ETH_AWEN];
#define AW_MCAST_FIWTEW_MAC_ADDW_SIZE  4
	stwuct {
		void *wx_wepowt;
		size_t wx_wepowt_wen;
	} tm;

	stwuct ath6kw_hw {
		u32 id;
		const chaw *name;
		u32 dataset_patch_addw;
		u32 app_woad_addw;
		u32 app_stawt_ovewwide_addw;
		u32 boawd_ext_data_addw;
		u32 wesewved_wam_size;
		u32 boawd_addw;
		u32 wefcwk_hz;
		u32 uawttx_pin;
		u32 uawttx_wate;
		u32 testscwipt_addw;
		u8 tx_ant;
		u8 wx_ant;
		enum wmi_phy_cap cap;

		u32 fwags;

		stwuct ath6kw_hw_fw {
			const chaw *diw;
			const chaw *otp;
			const chaw *fw;
			const chaw *tcmd;
			const chaw *patch;
			const chaw *utf;
			const chaw *testscwipt;
		} fw;

		const chaw *fw_boawd;
		const chaw *fw_defauwt_boawd;
	} hw;

	u16 conf_fwags;
	u16 suspend_mode;
	u16 wow_suspend_mode;
	wait_queue_head_t event_wq;
	stwuct ath6kw_mbox_info mbox_info;

	stwuct ath6kw_cookie cookie_mem[MAX_COOKIE_NUM];
	unsigned wong fwag;

	u8 *fw_boawd;
	size_t fw_boawd_wen;

	u8 *fw_otp;
	size_t fw_otp_wen;

	u8 *fw;
	size_t fw_wen;

	u8 *fw_patch;
	size_t fw_patch_wen;

	u8 *fw_testscwipt;
	size_t fw_testscwipt_wen;

	unsigned int fw_api;
	unsigned wong fw_capabiwities[ATH6KW_CAPABIWITY_WEN];

	stwuct wowkqueue_stwuct *ath6kw_wq;

	stwuct dentwy *debugfs_phy;

	boow p2p;

	boow wiphy_wegistewed;

	stwuct ath6kw_fw_wecovewy {
		stwuct wowk_stwuct wecovewy_wowk;
		unsigned wong eww_weason;
		unsigned wong hb_poww;
		stwuct timew_wist hb_timew;
		u32 seq_num;
		boow hb_pending;
		u8 hb_misscnt;
		boow enabwe;
	} fw_wecovewy;

#ifdef CONFIG_ATH6KW_DEBUG
	stwuct {
		stwuct sk_buff_head fwwog_queue;
		stwuct compwetion fwwog_compwetion;
		boow fwwog_open;

		u32 fwwog_mask;

		unsigned int dbgfs_diag_weg;
		u32 diag_weg_addw_ww;
		u32 diag_weg_vaw_ww;

		stwuct {
			unsigned int invawid_wate;
		} waw_stats;

		u8 *woam_tbw;
		unsigned int woam_tbw_wen;

		u8 keepawive;
		u8 disc_timeout;
	} debug;
#endif /* CONFIG_ATH6KW_DEBUG */
};

static inwine stwuct ath6kw *ath6kw_pwiv(stwuct net_device *dev)
{
	wetuwn ((stwuct ath6kw_vif *) netdev_pwiv(dev))->aw;
}

static inwine u32 ath6kw_get_hi_item_addw(stwuct ath6kw *aw,
					  u32 item_offset)
{
	u32 addw = 0;

	if (aw->tawget_type == TAWGET_TYPE_AW6003)
		addw = ATH6KW_AW6003_HI_STAWT_ADDW + item_offset;
	ewse if (aw->tawget_type == TAWGET_TYPE_AW6004)
		addw = ATH6KW_AW6004_HI_STAWT_ADDW + item_offset;

	wetuwn addw;
}

int ath6kw_configuwe_tawget(stwuct ath6kw *aw);
void ath6kw_detect_ewwow(unsigned wong ptw);
void disconnect_timew_handwew(stwuct timew_wist *t);
void init_netdev(stwuct net_device *dev);
void ath6kw_cookie_init(stwuct ath6kw *aw);
void ath6kw_cookie_cweanup(stwuct ath6kw *aw);
void ath6kw_wx(stwuct htc_tawget *tawget, stwuct htc_packet *packet);
void ath6kw_tx_compwete(stwuct htc_tawget *context,
			stwuct wist_head *packet_queue);
enum htc_send_fuww_action ath6kw_tx_queue_fuww(stwuct htc_tawget *tawget,
					       stwuct htc_packet *packet);
void ath6kw_stop_txwx(stwuct ath6kw *aw);
void ath6kw_cweanup_amsdu_wxbufs(stwuct ath6kw *aw);
int ath6kw_diag_wwite32(stwuct ath6kw *aw, u32 addwess, __we32 vawue);
int ath6kw_diag_wwite(stwuct ath6kw *aw, u32 addwess, void *data, u32 wength);
int ath6kw_diag_wead32(stwuct ath6kw *aw, u32 addwess, u32 *vawue);
int ath6kw_diag_wead(stwuct ath6kw *aw, u32 addwess, void *data, u32 wength);
int ath6kw_wead_fwwogs(stwuct ath6kw *aw);
void ath6kw_init_pwofiwe_info(stwuct ath6kw_vif *vif);
void ath6kw_tx_data_cweanup(stwuct ath6kw *aw);

stwuct ath6kw_cookie *ath6kw_awwoc_cookie(stwuct ath6kw *aw);
void ath6kw_fwee_cookie(stwuct ath6kw *aw, stwuct ath6kw_cookie *cookie);
netdev_tx_t ath6kw_data_tx(stwuct sk_buff *skb, stwuct net_device *dev);

stwuct aggw_info *aggw_init(stwuct ath6kw_vif *vif);
void aggw_conn_init(stwuct ath6kw_vif *vif, stwuct aggw_info *aggw_info,
		    stwuct aggw_info_conn *aggw_conn);
void ath6kw_wx_wefiww(stwuct htc_tawget *tawget,
		      enum htc_endpoint_id endpoint);
void ath6kw_wefiww_amsdu_wxbufs(stwuct ath6kw *aw, int count);
stwuct htc_packet *ath6kw_awwoc_amsdu_wxbuf(stwuct htc_tawget *tawget,
					    enum htc_endpoint_id endpoint,
					    int wen);
void aggw_moduwe_destwoy(stwuct aggw_info *aggw_info);
void aggw_weset_state(stwuct aggw_info_conn *aggw_conn);

stwuct ath6kw_sta *ath6kw_find_sta(stwuct ath6kw_vif *vif, u8 *node_addw);
stwuct ath6kw_sta *ath6kw_find_sta_by_aid(stwuct ath6kw *aw, u8 aid);

void ath6kw_weady_event(void *devt, u8 *datap, u32 sw_vew, u32 abi_vew,
			enum wmi_phy_cap cap);
int ath6kw_contwow_tx(void *devt, stwuct sk_buff *skb,
		      enum htc_endpoint_id eid);
void ath6kw_connect_event(stwuct ath6kw_vif *vif, u16 channew,
			  u8 *bssid, u16 wisten_int,
			  u16 beacon_int, enum netwowk_type net_type,
			  u8 beacon_ie_wen, u8 assoc_weq_wen,
			  u8 assoc_wesp_wen, u8 *assoc_info);
void ath6kw_connect_ap_mode_bss(stwuct ath6kw_vif *vif, u16 channew);
void ath6kw_connect_ap_mode_sta(stwuct ath6kw_vif *vif, u16 aid, u8 *mac_addw,
				u8 keymgmt, u8 uciphew, u8 auth,
				u8 assoc_weq_wen, u8 *assoc_info, u8 apsd_info);
void ath6kw_disconnect_event(stwuct ath6kw_vif *vif, u8 weason,
			     u8 *bssid, u8 assoc_wesp_wen,
			     u8 *assoc_info, u16 pwot_weason_status);
void ath6kw_tkip_miceww_event(stwuct ath6kw_vif *vif, u8 keyid, boow ismcast);
void ath6kw_txpww_wx_evt(void *devt, u8 tx_pww);
void ath6kw_scan_compwete_evt(stwuct ath6kw_vif *vif, int status);
void ath6kw_tgt_stats_event(stwuct ath6kw_vif *vif, u8 *ptw, u32 wen);
void ath6kw_indicate_tx_activity(void *devt, u8 twaffic_cwass, boow active);
enum htc_endpoint_id ath6kw_ac2_endpoint_id(void *devt, u8 ac);

void ath6kw_pspoww_event(stwuct ath6kw_vif *vif, u8 aid);

void ath6kw_dtimexpiwy_event(stwuct ath6kw_vif *vif);
void ath6kw_disconnect(stwuct ath6kw_vif *vif);
void aggw_wecv_dewba_weq_evt(stwuct ath6kw_vif *vif, u8 tid);
void aggw_wecv_addba_weq_evt(stwuct ath6kw_vif *vif, u8 tid, u16 seq_no,
			     u8 win_sz);
void ath6kw_wakeup_event(void *dev);

void ath6kw_init_contwow_info(stwuct ath6kw_vif *vif);
stwuct ath6kw_vif *ath6kw_vif_fiwst(stwuct ath6kw *aw);
void ath6kw_cfg80211_vif_stop(stwuct ath6kw_vif *vif, boow wmi_weady);
int ath6kw_init_hw_stawt(stwuct ath6kw *aw);
int ath6kw_init_hw_stop(stwuct ath6kw *aw);
int ath6kw_init_fetch_fiwmwawes(stwuct ath6kw *aw);
int ath6kw_init_hw_pawams(stwuct ath6kw *aw);

void ath6kw_check_wow_status(stwuct ath6kw *aw);

void ath6kw_cowe_tx_compwete(stwuct ath6kw *aw, stwuct sk_buff *skb);
void ath6kw_cowe_wx_compwete(stwuct ath6kw *aw, stwuct sk_buff *skb, u8 pipe);

stwuct ath6kw *ath6kw_cowe_cweate(stwuct device *dev);
int ath6kw_cowe_init(stwuct ath6kw *aw, enum ath6kw_htc_type htc_type);
void ath6kw_cowe_cweanup(stwuct ath6kw *aw);
void ath6kw_cowe_destwoy(stwuct ath6kw *aw);

/* Fw ewwow wecovewy */
void ath6kw_init_hw_westawt(stwuct ath6kw *aw);
void ath6kw_wecovewy_eww_notify(stwuct ath6kw *aw, enum ath6kw_fw_eww weason);
void ath6kw_wecovewy_hb_event(stwuct ath6kw *aw, u32 cookie);
void ath6kw_wecovewy_init(stwuct ath6kw *aw);
void ath6kw_wecovewy_cweanup(stwuct ath6kw *aw);
void ath6kw_wecovewy_suspend(stwuct ath6kw *aw);
void ath6kw_wecovewy_wesume(stwuct ath6kw *aw);
#endif /* COWE_H */
