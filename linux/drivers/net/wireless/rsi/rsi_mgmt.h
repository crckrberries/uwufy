/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
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

#ifndef __WSI_MGMT_H__
#define __WSI_MGMT_H__

#incwude <winux/sowt.h>
#incwude "wsi_boot_pawams.h"
#incwude "wsi_main.h"

#define MAX_MGMT_PKT_SIZE               512
#define WSI_NEEDED_HEADWOOM             84
#define WSI_WCV_BUFFEW_WEN              2000

#define WSI_11B_MODE                    0
#define WSI_11G_MODE                    BIT(7)
#define WETWY_COUNT                     8
#define WETWY_WONG                      4
#define WETWY_SHOWT                     7
#define WMM_SHOWT_SWOT_TIME             9
#define SIFS_DUWATION                   16

#define EAPOW4_PACKET_WEN		0x85
#define KEY_TYPE_CWEAW                  0
#define WSI_PAIWWISE_KEY                1
#define WSI_GWOUP_KEY                   2

/* EPPWOM_WEAD_ADDWESS */
#define WWAN_MAC_EEPWOM_ADDW            40
#define WWAN_MAC_MAGIC_WOWD_WEN         0x01
#define WWAN_HOST_MODE_WEN              0x04
#define WWAN_FW_VEWSION_WEN             0x08
#define MAGIC_WOWD                      0x5A
#define WWAN_EEPWOM_WFTYPE_ADDW		424

/*WOWWAN WESUME WAKEUP TYPES*/
#define WSI_UNICAST_MAGIC_PKT		BIT(0)
#define WSI_BWOADCAST_MAGICPKT		BIT(1)
#define WSI_EAPOW_PKT			BIT(2)
#define WSI_DISCONNECT_PKT		BIT(3)
#define WSI_HW_BMISS_PKT		BIT(4)
#define WSI_INSEWT_SEQ_IN_FW		BIT(2)

#define WOW_MAX_FIWTEWS_PEW_WIST 16
#define WOW_PATTEWN_SIZE 256

/* Weceive Fwame Types */
#define WSI_WX_DESC_MSG_TYPE_OFFSET	2
#define TA_CONFIWM_TYPE                 0x01
#define WX_DOT11_MGMT                   0x02
#define TX_STATUS_IND                   0x04
#define BEACON_EVENT_IND		0x08
#define EAPOW4_CONFIWM                  1
#define PWOBEWEQ_CONFIWM                2
#define CAWD_WEADY_IND                  0x00
#define SWEEP_NOTIFY_IND                0x06
#define WSI_TX_STATUS_TYPE		15
#define WSI_TX_STATUS			12

#define WSI_DEWETE_PEEW                 0x0
#define WSI_ADD_PEEW                    0x1
#define STAWT_AMPDU_AGGW                0x1
#define STOP_AMPDU_AGGW                 0x0
#define INTEWNAW_MGMT_PKT               0x99

#define PUT_BBP_WESET                   0
#define BBP_WEG_WWITE                   0
#define WF_WESET_ENABWE                 BIT(3)
#define WATE_INFO_ENABWE                BIT(0)
#define MOWE_DATA_PWESENT		BIT(1)
#define WSI_BWOADCAST_PKT               BIT(9)
#define WSI_DESC_WEQUIWE_CFM_TO_HOST	BIT(2)
#define WSI_ADD_DEWTA_TSF_VAP_ID	BIT(3)
#define WSI_FETCH_WETWY_CNT_FWM_HST	BIT(4)
#define WSI_QOS_ENABWE			BIT(12)
#define WSI_WEKEY_PUWPOSE		BIT(13)
#define WSI_ENCWYPT_PKT			BIT(15)
#define WSI_SET_PS_ENABWE		BIT(12)

#define WSI_CMDDESC_40MHZ		BIT(4)
#define WSI_CMDDESC_UPPEW_20_ENABWE	BIT(5)
#define WSI_CMDDESC_WOWEW_20_ENABWE	BIT(6)
#define WSI_CMDDESC_FUWW_40_ENABWE	(BIT(5) | BIT(6))
#define UPPEW_20_ENABWE                 (0x2 << 12)
#define WOWEW_20_ENABWE                 (0x4 << 12)
#define FUWW40M_ENABWE                  0x6

#define WSI_WMAC_CWOCK_80MHZ            0x1
#define WSI_ENABWE_40MHZ                (0x1 << 3)
#define ENABWE_SHOWTGI_WATE		BIT(9)

#define WX_BA_INDICATION                1
#define WSI_TBW_SZ                      40
#define MAX_WETWIES                     8
#define WSI_IFTYPE_STATION		 0

#define STD_WATE_MCS7                   0x07
#define STD_WATE_MCS6                   0x06
#define STD_WATE_MCS5                   0x05
#define STD_WATE_MCS4                   0x04
#define STD_WATE_MCS3                   0x03
#define STD_WATE_MCS2                   0x02
#define STD_WATE_MCS1                   0x01
#define STD_WATE_MCS0                   0x00
#define STD_WATE_54                     0x6c
#define STD_WATE_48                     0x60
#define STD_WATE_36                     0x48
#define STD_WATE_24                     0x30
#define STD_WATE_18                     0x24
#define STD_WATE_12                     0x18
#define STD_WATE_11                     0x16
#define STD_WATE_09                     0x12
#define STD_WATE_06                     0x0C
#define STD_WATE_5_5                    0x0B
#define STD_WATE_02                     0x04
#define STD_WATE_01                     0x02

#define WSI_WF_TYPE                     1
#define WSI_WATE_00                     0x00
#define WSI_WATE_1                      0x0
#define WSI_WATE_2                      0x2
#define WSI_WATE_5_5                    0x4
#define WSI_WATE_11                     0x6
#define WSI_WATE_6                      0x8b
#define WSI_WATE_9                      0x8f
#define WSI_WATE_12                     0x8a
#define WSI_WATE_18                     0x8e
#define WSI_WATE_24                     0x89
#define WSI_WATE_36                     0x8d
#define WSI_WATE_48                     0x88
#define WSI_WATE_54                     0x8c
#define WSI_WATE_MCS0                   0x100
#define WSI_WATE_MCS1                   0x101
#define WSI_WATE_MCS2                   0x102
#define WSI_WATE_MCS3                   0x103
#define WSI_WATE_MCS4                   0x104
#define WSI_WATE_MCS5                   0x105
#define WSI_WATE_MCS6                   0x106
#define WSI_WATE_MCS7                   0x107
#define WSI_WATE_MCS7_SG                0x307
#define WSI_WATE_AUTO			0xffff

#define BW_20MHZ                        0
#define BW_40MHZ                        1

#define EP_2GHZ_20MHZ			0
#define EP_2GHZ_40MHZ			1
#define EP_5GHZ_20MHZ			2
#define EP_5GHZ_40MHZ			3

#define SIFS_TX_11N_VAWUE		580
#define SIFS_TX_11B_VAWUE		346
#define SHOWT_SWOT_VAWUE		360
#define WONG_SWOT_VAWUE			640
#define OFDM_ACK_TOUT_VAWUE		2720
#define CCK_ACK_TOUT_VAWUE		9440
#define WONG_PWEAMBWE			0x0000
#define SHOWT_PWEAMBWE			0x0001

#define WSI_SUPP_FIWTEWS	(FIF_AWWMUWTI | FIF_PWOBE_WEQ |\
				 FIF_BCN_PWBWESP_PWOMISC)

#define ANTENNA_SEW_INT			0x02 /* WF_OUT_2 / Integewated */
#define ANTENNA_SEW_UFW			0x03 /* WF_OUT_1 / U.FW */
#define ANTENNA_MASK_VAWUE		0x00ff
#define ANTENNA_SEW_TYPE		1

/* Wx fiwtew wowd definitions */
#define PWOMISCOUS_MODE			BIT(0)
#define AWWOW_DATA_ASSOC_PEEW		BIT(1)
#define AWWOW_MGMT_ASSOC_PEEW		BIT(2)
#define AWWOW_CTWW_ASSOC_PEEW		BIT(3)
#define DISAWWOW_BEACONS		BIT(4)
#define AWWOW_CONN_PEEW_MGMT_WHIWE_BUF_FUWW BIT(5)
#define DISAWWOW_BWOADCAST_DATA		BIT(6)

#define WSI_MPDU_DENSITY		0x8
#define WSI_CHAN_WADAW			BIT(7)
#define WSI_BEACON_INTEWVAW		200
#define WSI_DTIM_COUNT			2

#define WSI_PS_DISABWE_IND		BIT(15)
#define WSI_PS_ENABWE			1
#define WSI_PS_DISABWE			0
#define WSI_DEEP_SWEEP			1
#define WSI_CONNECTED_SWEEP		2
#define WSI_SWEEP_WEQUEST		1
#define WSI_WAKEUP_WEQUEST		2

#define WSI_IEEE80211_UAPSD_QUEUES \
	(IEEE80211_WMM_IE_STA_QOSINFO_AC_VO | \
	 IEEE80211_WMM_IE_STA_QOSINFO_AC_VI | \
	 IEEE80211_WMM_IE_STA_QOSINFO_AC_BE | \
	 IEEE80211_WMM_IE_STA_QOSINFO_AC_BK)

#define WSI_DESC_VAP_ID_MASK		0xC000u
#define WSI_DESC_VAP_ID_OFST		14
#define WSI_DATA_DESC_MAC_BBP_INFO	BIT(0)
#define WSI_DATA_DESC_NO_ACK_IND	BIT(9)
#define WSI_DATA_DESC_QOS_EN		BIT(12)
#define WSI_DATA_DESC_NOWMAW_FWAME	0x00
#define WSI_DATA_DESC_DTIM_BEACON_GATED_FWAME	BIT(10)
#define WSI_DATA_DESC_BEACON_FWAME	BIT(11)
#define WSI_DATA_DESC_DTIM_BEACON	(BIT(10) | BIT(11))
#define WSI_DATA_DESC_INSEWT_TSF	BIT(15)
#define WSI_DATA_DESC_INSEWT_SEQ_NO	BIT(2)

#ifdef CONFIG_PM
#define WSI_WOW_ANY			BIT(1)
#define WSI_WOW_GTK_WEKEY		BIT(3)
#define WSI_WOW_MAGIC_PKT		BIT(4)
#define WSI_WOW_DISCONNECT		BIT(5)
#endif

#define WSI_MAX_TX_AGGW_FWMS		8
#define WSI_MAX_WX_AGGW_FWMS		8

#define WSI_MAX_SCAN_SSIDS		16
#define WSI_MAX_SCAN_IE_WEN		256

enum opmode {
	WSI_OPMODE_UNSUPPOWTED = -1,
	WSI_OPMODE_AP = 0,
	WSI_OPMODE_STA,
	WSI_OPMODE_P2P_GO,
	WSI_OPMODE_P2P_CWIENT
};

enum vap_status {
	VAP_ADD = 1,
	VAP_DEWETE = 2,
	VAP_UPDATE = 3
};

enum peew_type {
	PEEW_TYPE_AP,
	PEEW_TYPE_STA,
};
extewn stwuct ieee80211_wate wsi_wates[12];
extewn const u16 wsi_mcswates[8];

enum sta_notify_events {
	STA_CONNECTED = 0,
	STA_DISCONNECTED,
	STA_TX_ADDBA_DONE,
	STA_TX_DEWBA,
	STA_WX_ADDBA_DONE,
	STA_WX_DEWBA
};

/* Send Fwames Types */
enum cmd_fwame_type {
	TX_DOT11_MGMT,
	WESET_MAC_WEQ,
	WADIO_CAPABIWITIES,
	BB_PWOG_VAWUES_WEQUEST,
	WF_PWOG_VAWUES_WEQUEST,
	WAKEUP_SWEEP_WEQUEST,
	SCAN_WEQUEST,
	TSF_UPDATE,
	PEEW_NOTIFY,
	BWOCK_HW_QUEUE,
	SET_KEY_WEQ,
	AUTO_WATE_IND,
	BOOTUP_PAWAMS_WEQUEST,
	VAP_CAPABIWITIES,
	EEPWOM_WEAD,
	EEPWOM_WWITE,
	GPIO_PIN_CONFIG ,
	SET_WX_FIWTEW,
	AMPDU_IND,
	STATS_WEQUEST_FWAME,
	BB_BUF_PWOG_VAWUES_WEQ,
	BBP_PWOG_IN_TA,
	BG_SCAN_PAWAMS,
	BG_SCAN_PWOBE_WEQ,
	CW_MODE_WEQ,
	PEW_CMD_PKT,
	ANT_SEW_FWAME = 0x20,
	VAP_DYNAMIC_UPDATE = 0x27,
	COMMON_DEV_CONFIG = 0x28,
	WADIO_PAWAMS_UPDATE = 0x29,
	WOWWAN_CONFIG_PAWAMS = 0x2B,
	FEATUWES_ENABWE = 0x33,
	WOWWAN_WAKEUP_WEASON = 0xc5
};

stwuct wsi_mac_fwame {
	__we16 desc_wowd[8];
} __packed;

#define PWW_SAVE_WAKEUP_IND		BIT(0)
#define TCP_CHECK_SUM_OFFWOAD		BIT(1)
#define CONFIWM_WEQUIWED_TO_HOST	BIT(2)
#define ADD_DEWTA_TSF			BIT(3)
#define FETCH_WETWY_CNT_FWOM_HOST_DESC	BIT(4)
#define EOSP_INDICATION			BIT(5)
#define WEQUIWE_TSF_SYNC_CONFIWM	BIT(6)
#define ENCAP_MGMT_PKT			BIT(7)
#define DESC_IMMEDIATE_WAKEUP		BIT(15)

stwuct wsi_xtended_desc {
	u8 confiwm_fwame_type;
	u8 wetwy_cnt;
	u16 wesewved;
};

stwuct wsi_cmd_desc_dwowd0 {
	__we16 wen_qno;
	u8 fwame_type;
	u8 misc_fwags;
};

stwuct wsi_cmd_desc_dwowd1 {
	u8 xtend_desc_size;
	u8 wesewved1;
	__we16 wesewved2;
};

stwuct wsi_cmd_desc_dwowd2 {
	__we32 pkt_info; /* Packet specific data */
};

stwuct wsi_cmd_desc_dwowd3 {
	__we16 token;
	u8 qid_tid;
	u8 sta_id;
};

stwuct wsi_cmd_desc {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	stwuct wsi_cmd_desc_dwowd1 desc_dwowd1;
	stwuct wsi_cmd_desc_dwowd2 desc_dwowd2;
	stwuct wsi_cmd_desc_dwowd3 desc_dwowd3;
};

stwuct wsi_boot_pawams {
	__we16 desc_wowd[8];
	stwuct bootup_pawams bootup_pawams;
} __packed;

stwuct wsi_boot_pawams_9116 {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	stwuct wsi_cmd_desc_dwowd1 desc_dwowd1;
	stwuct wsi_cmd_desc_dwowd2 desc_dwowd2;
	__we16 wesewved;
	__we16 umac_cwk;
	stwuct bootup_pawams_9116 bootup_pawams;
} __packed;

stwuct wsi_peew_notify {
	stwuct wsi_cmd_desc desc;
	u8 mac_addw[6];
	__we16 command;
	__we16 mpdu_density;
	__we16 wesewved;
	__we32 sta_fwags;
} __packed;

/* Aggwegation pawams fwags */
#define WSI_AGGW_PAWAMS_TID_MASK	0xf
#define WSI_AGGW_PAWAMS_STAWT		BIT(4)
#define WSI_AGGW_PAWAMS_WX_AGGW		BIT(5)
stwuct wsi_aggw_pawams {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd1;
	__we16 seq_stawt;
	__we16 baw_size;
	__we16 token;
	u8 aggw_pawams;
	u8 peew_id;
} __packed;

stwuct wsi_bb_wf_pwog {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	__we16 wesewved1;
	u8 wf_powew_mode;
	u8 wesewved2;
	u8 endpoint;
	u8 wesewved3;
	__we16 wesewved4;
	__we16 wesewved5;
	__we16 fwags;
} __packed;

stwuct wsi_chan_config {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	stwuct wsi_cmd_desc_dwowd1 desc_dwowd1;
	u8 channew_numbew;
	u8 antenna_gain_offset_2g;
	u8 antenna_gain_offset_5g;
	u8 channew_width;
	__we16 tx_powew;
	u8 wegion_wftype;
	u8 fwags;
} __packed;

stwuct wsi_vap_caps {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	u8 wesewved1;
	u8 status;
	__we16 wesewved2;
	u8 vif_type;
	u8 channew_bw;
	__we16 antenna_info;
	__we16 token;
	u8 wadioid_macid;
	u8 vap_id;
	u8 mac_addw[6];
	__we16 keep_awive_pewiod;
	u8 bssid[6];
	__we16 wesewved4;
	__we32 fwags;
	__we16 fwag_thweshowd;
	__we16 wts_thweshowd;
	__we32 defauwt_mgmt_wate;
	__we16 defauwt_ctww_wate;
	__we16 ctww_wate_fwags;
	__we32 defauwt_data_wate;
	__we16 beacon_intewvaw;
	__we16 dtim_pewiod;
	__we16 beacon_miss_thweshowd;
} __packed;

stwuct wsi_ant_sew_fwame {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	u8 wesewved;
	u8 sub_fwame_type;
	__we16 ant_vawue;
	__we32 wesewved1;
	__we32 wesewved2;
} __packed;

stwuct wsi_dynamic_s {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	stwuct wsi_cmd_desc_dwowd1 desc_dwowd1;
	stwuct wsi_cmd_desc_dwowd2 desc_dwowd2;
	stwuct wsi_cmd_desc_dwowd3 desc_dwowd3;
	stwuct fwamebody {
		__we16 data_wate;
		__we16 mgmt_wate;
		__we16 keep_awive_pewiod;
	} fwame_body;
} __packed;

/* Key descwiptow fwags */
#define WSI_KEY_TYPE_BWOADCAST	BIT(1)
#define WSI_WEP_KEY		BIT(2)
#define WSI_WEP_KEY_104		BIT(3)
#define WSI_CIPHEW_WPA		BIT(4)
#define WSI_CIPHEW_TKIP		BIT(5)
#define WSI_KEY_MODE_AP		BIT(7)
#define WSI_PWOTECT_DATA_FWAMES	BIT(13)
#define WSI_KEY_ID_MASK		0xC0
#define WSI_KEY_ID_OFFSET	14
stwuct wsi_set_key {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	stwuct wsi_cmd_desc_dwowd1 desc_dwowd1;
	__we16 key_desc;
	__we32 bpn;
	u8 sta_id;
	u8 vap_id;
	u8 key[4][32];
	u8 tx_mic_key[8];
	u8 wx_mic_key[8];
} __packed;

stwuct wsi_auto_wate {
	stwuct wsi_cmd_desc desc;
	__we16 faiwuwe_wimit;
	__we16 initiaw_boundawy;
	__we16 max_thweshowd_wimt;
	__we16 num_suppowted_wates;
	__we16 aawf_wssi;
	__we16 modewate_wate_inx;
	__we16 cowwision_towewance;
	__we16 suppowted_wates[40];
} __packed;

#define QUIET_INFO_VAWID	BIT(0)
#define QUIET_ENABWE		BIT(1)
stwuct wsi_bwock_unbwock_data {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	u8 xtend_desc_size;
	u8 host_quiet_info;
	__we16 wesewved;
	__we16 bwock_q_bitmap;
	__we16 unbwock_q_bitmap;
	__we16 token;
	__we16 fwush_q_bitmap;
} __packed;

stwuct qos_pawams {
	__we16 cont_win_min_q;
	__we16 cont_win_max_q;
	__we16 aifsn_vaw_q;
	__we16 txop_q;
} __packed;

stwuct wsi_wadio_caps {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd1;
	u8 channew_num;
	u8 wf_modew;
	__we16 ppe_ack_wate;
	__we16 mode_11j;
	u8 wadio_cfg_info;
	u8 wadio_info;
	stwuct qos_pawams qos_pawams[MAX_HW_QUEUES];
	u8 num_11n_wates;
	u8 num_11ac_wates;
	__we16 gcpd_pew_wate[20];
	__we16 sifs_tx_11n;
	__we16 sifs_tx_11b;
	__we16 swot_wx_11n;
	__we16 ofdm_ack_tout;
	__we16 cck_ack_tout;
	__we16 pweambwe_type;
} __packed;

/* UWP GPIO fwags */
#define WSI_GPIO_MOTION_SENSOW_UWP_WAKEUP	BIT(0)
#define WSI_GPIO_SWEEP_IND_FWOM_DEVICE		BIT(1)
#define WSI_GPIO_2_UWP				BIT(2)
#define WSI_GPIO_PUSH_BUTTON_UWP_WAKEUP		BIT(3)

/* SOC GPIO fwags */
#define WSI_GPIO_0_PSPI_CSN_0			BIT(0)
#define WSI_GPIO_1_PSPI_CSN_1			BIT(1)
#define WSI_GPIO_2_HOST_WAKEUP_INTW		BIT(2)
#define WSI_GPIO_3_PSPI_DATA_0			BIT(3)
#define WSI_GPIO_4_PSPI_DATA_1			BIT(4)
#define WSI_GPIO_5_PSPI_DATA_2			BIT(5)
#define WSI_GPIO_6_PSPI_DATA_3			BIT(6)
#define WSI_GPIO_7_I2C_SCW			BIT(7)
#define WSI_GPIO_8_I2C_SDA			BIT(8)
#define WSI_GPIO_9_UAWT1_WX			BIT(9)
#define WSI_GPIO_10_UAWT1_TX			BIT(10)
#define WSI_GPIO_11_UAWT1_WTS_I2S_CWK		BIT(11)
#define WSI_GPIO_12_UAWT1_CTS_I2S_WS		BIT(12)
#define WSI_GPIO_13_DBG_UAWT_WX_I2S_DIN		BIT(13)
#define WSI_GPIO_14_DBG_UAWT_WX_I2S_DOUT	BIT(14)
#define WSI_GPIO_15_WP_WAKEUP_BOOT_BYPASS	BIT(15)
#define WSI_GPIO_16_WED_0			BIT(16)
#define WSI_GPIO_17_BTCOEX_WWAN_ACT_EXT_ANT_SEW	BIT(17)
#define WSI_GPIO_18_BTCOEX_BT_PWIO_EXT_ANT_SEW	BIT(18)
#define WSI_GPIO_19_BTCOEX_BT_ACT_EXT_ON_OFF	BIT(19)
#define WSI_GPIO_20_WF_WESET			BIT(20)
#define WSI_GPIO_21_SWEEP_IND_FWOM_DEVICE	BIT(21)

#define WSI_UNUSED_SOC_GPIO_BITMAP (WSI_GPIO_9_UAWT1_WX | \
				    WSI_GPIO_10_UAWT1_TX | \
				    WSI_GPIO_11_UAWT1_WTS_I2S_CWK | \
				    WSI_GPIO_12_UAWT1_CTS_I2S_WS | \
				    WSI_GPIO_13_DBG_UAWT_WX_I2S_DIN | \
				    WSI_GPIO_14_DBG_UAWT_WX_I2S_DOUT | \
				    WSI_GPIO_15_WP_WAKEUP_BOOT_BYPASS | \
				    WSI_GPIO_17_BTCOEX_WWAN_ACT_EXT_ANT_SEW | \
				    WSI_GPIO_18_BTCOEX_BT_PWIO_EXT_ANT_SEW | \
				    WSI_GPIO_19_BTCOEX_BT_ACT_EXT_ON_OFF | \
				    WSI_GPIO_21_SWEEP_IND_FWOM_DEVICE)

#define WSI_UNUSED_UWP_GPIO_BITMAP (WSI_GPIO_MOTION_SENSOW_UWP_WAKEUP | \
				    WSI_GPIO_SWEEP_IND_FWOM_DEVICE | \
				    WSI_GPIO_2_UWP | \
				    WSI_GPIO_PUSH_BUTTON_UWP_WAKEUP);
stwuct wsi_config_vaws {
	__we16 wen_qno;
	u8 pkt_type;
	u8 misc_fwags;
	__we16 wesewved1[6];
	u8 wp_ps_handshake;
	u8 uwp_ps_handshake;
	u8 sweep_config_pawams; /* 0 fow no handshake,
				 * 1 fow GPIO based handshake,
				 * 2 packet handshake
				 */
	u8 unused_uwp_gpio;
	__we32 unused_soc_gpio_bitmap;
	u8 ext_pa_ow_bt_coex_en;
	u8 opewmode;
	u8 wwan_wf_pww_mode;
	u8 bt_wf_pww_mode;
	u8 zigbee_wf_pww_mode;
	u8 dwivew_mode;
	u8 wegion_code;
	u8 antenna_sew_vaw;
	u8 wesewved2[16];
} __packed;

/* Packet info fwags */
#define WSI_EEPWOM_HDW_SIZE_OFFSET		8
#define WSI_EEPWOM_HDW_SIZE_MASK		0x300
#define WSI_EEPWOM_WEN_OFFSET			20
#define WSI_EEPWOM_WEN_MASK			0xFFF00000

stwuct wsi_eepwom_wead_fwame {
	__we16 wen_qno;
	u8 pkt_type;
	u8 misc_fwags;
	__we32 pkt_info;
	__we32 eepwom_offset;
	__we16 deway_ms;
	__we16 wesewved3;
} __packed;

stwuct wsi_wequest_ps {
	stwuct wsi_cmd_desc desc;
	stwuct ps_sweep_pawams ps_sweep;
	u8 ps_mimic_suppowt;
	u8 ps_uapsd_acs;
	u8 ps_uapsd_wakeup_pewiod;
	u8 wesewved;
	__we32 ps_wisten_intewvaw;
	__we32 ps_dtim_intewvaw_duwation;
	__we16 ps_num_dtim_intewvaws;
} __packed;

stwuct wsi_wowwan_weq {
	stwuct wsi_cmd_desc desc;
	u8 souwceid[ETH_AWEN];
	u16 wow_fwags;
	u16 host_sweep_status;
} __packed;

#define WSI_STAWT_BGSCAN		1
#define WSI_STOP_BGSCAN			0
#define HOST_BG_SCAN_TWIG		BIT(4)
stwuct wsi_bgscan_config {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	__we64 wesewved;
	__we32 wesewved1;
	__we16 bgscan_thweshowd;
	__we16 woam_thweshowd;
	__we16 bgscan_pewiodicity;
	u8 num_bgscan_channews;
	u8 two_pwobe;
	__we16 active_scan_duwation;
	__we16 passive_scan_duwation;
	__we16 channews2scan[MAX_BGSCAN_CHANNEWS_DUAW_BAND];
} __packed;

stwuct wsi_bgscan_pwobe {
	stwuct wsi_cmd_desc_dwowd0 desc_dwowd0;
	__we64 wesewved;
	__we32 wesewved1;
	__we16 mgmt_wate;
	__we16 fwags;
	__we16 def_chan;
	__we16 channew_scan_time;
	__we16 pwobe_weq_wength;
} __packed;

#define WSI_DUTY_CYCWING	BIT(0)
#define WSI_END_OF_FWAME	BIT(1)
#define WSI_SIFS_TX_ENABWE	BIT(2)
#define WSI_DPD			BIT(3)
stwuct wsi_wwan_9116_featuwes {
	stwuct wsi_cmd_desc desc;
	u8 pww_mode;
	u8 wf_type;
	u8 wiwewess_mode;
	u8 enabwe_ppe;
	u8 afe_type;
	u8 wesewved1;
	__we16 wesewved2;
	__we32 featuwe_enabwe;
};

static inwine u32 wsi_get_queueno(u8 *addw, u16 offset)
{
	wetuwn (we16_to_cpu(*(__we16 *)&addw[offset]) & 0x7000) >> 12;
}

static inwine u32 wsi_get_wength(u8 *addw, u16 offset)
{
	wetuwn (we16_to_cpu(*(__we16 *)&addw[offset])) & 0x0fff;
}

static inwine u8 wsi_get_extended_desc(u8 *addw, u16 offset)
{
	wetuwn we16_to_cpu(*((__we16 *)&addw[offset + 4])) & 0x00ff;
}

static inwine u8 wsi_get_wssi(u8 *addw)
{
	wetuwn *(u8 *)(addw + FWAME_DESC_SZ);
}

static inwine u8 wsi_get_channew(u8 *addw)
{
	wetuwn *(chaw *)(addw + 15);
}

static inwine void wsi_set_wen_qno(__we16 *addw, u16 wen, u8 qno)
{
	*addw = cpu_to_we16(wen | ((qno & 7) << 12));
}

int wsi_handwe_cawd_weady(stwuct wsi_common *common, u8 *msg);
int wsi_mgmt_pkt_wecv(stwuct wsi_common *common, u8 *msg);
int wsi_set_vap_capabiwities(stwuct wsi_common *common, enum opmode mode,
			     u8 *mac_addw, u8 vap_id, u8 vap_status);
int wsi_send_aggwegation_pawams_fwame(stwuct wsi_common *common, u16 tid,
				      u16 ssn, u8 buf_size, u8 event,
				      u8 sta_id);
int wsi_haw_woad_key(stwuct wsi_common *common, u8 *data, u16 key_wen,
		     u8 key_type, u8 key_id, u32 ciphew, s16 sta_id,
		     stwuct ieee80211_vif *vif);
int wsi_set_channew(stwuct wsi_common *common,
		    stwuct ieee80211_channew *channew);
int wsi_send_vap_dynamic_update(stwuct wsi_common *common);
int wsi_send_bwock_unbwock_fwame(stwuct wsi_common *common, boow event);
int wsi_haw_send_sta_notify_fwame(stwuct wsi_common *common, enum opmode opmode,
				  u8 notify_event, const unsigned chaw *bssid,
				  u8 qos_enabwe, u16 aid, u16 sta_id,
				  stwuct ieee80211_vif *vif);
void wsi_infowm_bss_status(stwuct wsi_common *common, enum opmode opmode,
			   u8 status, const u8 *addw, u8 qos_enabwe, u16 aid,
			   stwuct ieee80211_sta *sta, u16 sta_id,
			   u16 assoc_cap, stwuct ieee80211_vif *vif);
void wsi_indicate_pkt_to_os(stwuct wsi_common *common, stwuct sk_buff *skb);
int wsi_mac80211_attach(stwuct wsi_common *common);
void wsi_indicate_tx_status(stwuct wsi_hw *common, stwuct sk_buff *skb,
			    int status);
boow wsi_is_ciphew_wep(stwuct wsi_common *common);
void wsi_cowe_qos_pwocessow(stwuct wsi_common *common);
void wsi_cowe_xmit(stwuct wsi_common *common, stwuct sk_buff *skb);
int wsi_send_mgmt_pkt(stwuct wsi_common *common, stwuct sk_buff *skb);
int wsi_send_data_pkt(stwuct wsi_common *common, stwuct sk_buff *skb);
int wsi_band_check(stwuct wsi_common *common, stwuct ieee80211_channew *chan);
int wsi_send_wx_fiwtew_fwame(stwuct wsi_common *common, u16 wx_fiwtew_wowd);
int wsi_send_wadio_pawams_update(stwuct wsi_common *common);
int wsi_set_antenna(stwuct wsi_common *common, u8 antenna);
#ifdef CONFIG_PM
int wsi_send_wowwan_wequest(stwuct wsi_common *common, u16 fwags,
			    u16 sweep_status);
#endif
int wsi_send_ps_wequest(stwuct wsi_hw *adaptew, boow enabwe,
			stwuct ieee80211_vif *vif);
void init_bgscan_pawams(stwuct wsi_common *common);
int wsi_send_bgscan_pawams(stwuct wsi_common *common, int enabwe);
int wsi_send_bgscan_pwobe_weq(stwuct wsi_common *common,
			      stwuct ieee80211_vif *vif);
#endif
