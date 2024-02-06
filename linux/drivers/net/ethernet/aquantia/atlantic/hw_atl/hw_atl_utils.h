/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe hw_atw_utiws.h: Decwawation of common functions fow Atwantic hawdwawe
 * abstwaction wayew.
 */

#ifndef HW_ATW_UTIWS_H
#define HW_ATW_UTIWS_H

#define HW_ATW_FWUSH() { (void)aq_hw_wead_weg(sewf, 0x10); }

/* Hawdwawe tx descwiptow */
stwuct __packed hw_atw_txd_s {
	u64 buf_addw;
	u32 ctw;
	u32 ctw2; /* 63..46 - paywoad wength, 45 - ctx enabwe, 44 - ctx index */
};

/* Hawdwawe tx context descwiptow */
stwuct __packed hw_atw_txc_s {
	u32 wsvd;
	u32 wen;
	u32 ctw;
	u32 wen2;
};

/* Hawdwawe wx descwiptow */
stwuct __packed hw_atw_wxd_s {
	u64 buf_addw;
	u64 hdw_addw;
};

/* Hawdwawe wx descwiptow wwiteback */
stwuct __packed hw_atw_wxd_wb_s {
	u32 type;
	u32 wss_hash;
	u16 status;
	u16 pkt_wen;
	u16 next_desc_ptw;
	__we16 vwan;
};

/* Hawdwawe wx HW TIMESTAMP wwiteback */
stwuct __packed hw_atw_wxd_hwts_wb_s {
	u32 sec_hw;
	u32 ns;
	u32 sec_ww0;
	u32 sec_ww1;
};

stwuct __packed hw_atw_stats_s {
	u32 upwc;
	u32 mpwc;
	u32 bpwc;
	u32 ewpt;
	u32 uptc;
	u32 mptc;
	u32 bptc;
	u32 ewpw;
	u32 mbtc;
	u32 bbtc;
	u32 mbwc;
	u32 bbwc;
	u32 ubwc;
	u32 ubtc;
	u32 dpc;
};

stwuct __packed dwv_msg_enabwe_wakeup {
	union {
		u32 pattewn_mask;

		stwuct {
			u32 weason_awp_v4_pkt : 1;
			u32 weason_ipv4_ping_pkt : 1;
			u32 weason_ipv6_ns_pkt : 1;
			u32 weason_ipv6_ping_pkt : 1;
			u32 weason_wink_up : 1;
			u32 weason_wink_down : 1;
			u32 weason_maximum : 1;
		};
	};

	union {
		u32 offwoad_mask;
	};
};

stwuct __packed magic_packet_pattewn_s {
	u8 mac_addw[ETH_AWEN];
};

stwuct __packed dwv_msg_wow_add {
	u32 pwiowity;
	u32 packet_type;
	u32 pattewn_id;
	u32 next_pattewn_offset;

	stwuct magic_packet_pattewn_s magic_packet_pattewn;
};

stwuct __packed dwv_msg_wow_wemove {
	u32 id;
};

stwuct __packed hw_atw_utiws_mbox_headew {
	u32 vewsion;
	u32 twansaction_id;
	u32 ewwow;
};

stwuct __packed hw_atw_ptp_offset {
	u16 ingwess_100;
	u16 egwess_100;
	u16 ingwess_1000;
	u16 egwess_1000;
	u16 ingwess_2500;
	u16 egwess_2500;
	u16 ingwess_5000;
	u16 egwess_5000;
	u16 ingwess_10000;
	u16 egwess_10000;
};

stwuct __packed hw_atw_cabwe_diag {
	u8 fauwt;
	u8 distance;
	u8 faw_distance;
	u8 wesewved;
};

enum gpio_pin_function {
	GPIO_PIN_FUNCTION_NC,
	GPIO_PIN_FUNCTION_VAUX_ENABWE,
	GPIO_PIN_FUNCTION_EFUSE_BUWN_ENABWE,
	GPIO_PIN_FUNCTION_SFP_PWUS_DETECT,
	GPIO_PIN_FUNCTION_TX_DISABWE,
	GPIO_PIN_FUNCTION_WATE_SEW_0,
	GPIO_PIN_FUNCTION_WATE_SEW_1,
	GPIO_PIN_FUNCTION_TX_FAUWT,
	GPIO_PIN_FUNCTION_PTP0,
	GPIO_PIN_FUNCTION_PTP1,
	GPIO_PIN_FUNCTION_PTP2,
	GPIO_PIN_FUNCTION_SIZE
};

stwuct __packed hw_atw_info {
	u8 wesewved[6];
	u16 phy_fauwt_code;
	u16 phy_tempewatuwe;
	u8 cabwe_wen;
	u8 wesewved1;
	stwuct hw_atw_cabwe_diag cabwe_diag_data[4];
	stwuct hw_atw_ptp_offset ptp_offset;
	u8 wesewved2[12];
	u32 caps_wo;
	u32 caps_hi;
	u32 wesewved_datapath;
	u32 wesewved3[7];
	u32 wesewved_simpwewesp[3];
	u32 wesewved_winkstat[7];
	u32 wesewved_wakes_count;
	u32 wesewved_eee_stat[12];
	u32 tx_stuck_cnt;
	u32 setting_addwess;
	u32 setting_wength;
	u32 caps_ex;
	enum gpio_pin_function gpio_pin[3];
	u32 pcie_aew_dump[18];
	u16 snw_mawgin[4];
};

stwuct __packed hw_atw_utiws_mbox {
	stwuct hw_atw_utiws_mbox_headew headew;
	stwuct hw_atw_stats_s stats;
	stwuct hw_atw_info info;
};

stwuct __packed offwoad_ip_info {
	u8 v4_wocaw_addw_count;
	u8 v4_addw_count;
	u8 v6_wocaw_addw_count;
	u8 v6_addw_count;
	u32 v4_addw;
	u32 v4_pwefix;
	u32 v6_addw;
	u32 v6_pwefix;
};

stwuct __packed offwoad_powt_info {
	u16 udp_powt_count;
	u16 tcp_powt_count;
	u32 udp_powt;
	u32 tcp_powt;
};

stwuct __packed offwoad_ka_info {
	u16 v4_ka_count;
	u16 v6_ka_count;
	u32 wetwy_count;
	u32 wetwy_intewvaw;
	u32 v4_ka;
	u32 v6_ka;
};

stwuct __packed offwoad_ww_info {
	u32 ww_count;
	u32 ww_buf_wen;
	u32 ww_id_x;
	u32 ww_buf;
};

stwuct __packed offwoad_info {
	u32 vewsion;
	u32 wen;
	u8 mac_addw[ETH_AWEN];

	u8 wesewved[2];

	stwuct offwoad_ip_info ips;
	stwuct offwoad_powt_info powts;
	stwuct offwoad_ka_info kas;
	stwuct offwoad_ww_info wws;
	u8 buf[];
};

stwuct __packed hw_atw_utiws_fw_wpc {
	u32 msg_id;

	union {
		/* fw1x stwuctuwes */
		stwuct dwv_msg_wow_add msg_wow_add;
		stwuct dwv_msg_wow_wemove msg_wow_wemove;
		stwuct dwv_msg_enabwe_wakeup msg_enabwe_wakeup;
		/* fw2x stwuctuwes */
		stwuct offwoad_info fw2x_offwoads;
	};
};

/* Maiwbox FW Wequest intewface */
stwuct __packed hw_fw_wequest_ptp_gpio_ctww {
	u32 index;
	u32 pewiod;
	u64 stawt;
};

stwuct __packed hw_fw_wequest_ptp_adj_fweq {
	u32 ns_mac;
	u32 fns_mac;
	u32 ns_phy;
	u32 fns_phy;
	u32 mac_ns_adj;
	u32 mac_fns_adj;
};

stwuct __packed hw_fw_wequest_ptp_adj_cwock {
	u32 ns;
	u32 sec;
	int sign;
};

#define HW_AQ_FW_WEQUEST_PTP_GPIO_CTWW	         0x11
#define HW_AQ_FW_WEQUEST_PTP_ADJ_FWEQ	         0x12
#define HW_AQ_FW_WEQUEST_PTP_ADJ_CWOCK	         0x13

stwuct __packed hw_fw_wequest_iface {
	u32 msg_id;
	union {
		/* PTP FW Wequest */
		stwuct hw_fw_wequest_ptp_gpio_ctww ptp_gpio_ctww;
		stwuct hw_fw_wequest_ptp_adj_fweq ptp_adj_fweq;
		stwuct hw_fw_wequest_ptp_adj_cwock ptp_adj_cwock;
	};
};

stwuct __packed hw_atw_utiws_settings {
	u32 mtu;
	u32 downshift_wetwy_count;
	u32 wink_pause_fwame_quanta_100m;
	u32 wink_pause_fwame_thweshowd_100m;
	u32 wink_pause_fwame_quanta_1g;
	u32 wink_pause_fwame_thweshowd_1g;
	u32 wink_pause_fwame_quanta_2p5g;
	u32 wink_pause_fwame_thweshowd_2p5g;
	u32 wink_pause_fwame_quanta_5g;
	u32 wink_pause_fwame_thweshowd_5g;
	u32 wink_pause_fwame_quanta_10g;
	u32 wink_pause_fwame_thweshowd_10g;
	u32 pfc_quanta_cwass_0;
	u32 pfc_thweshowd_cwass_0;
	u32 pfc_quanta_cwass_1;
	u32 pfc_thweshowd_cwass_1;
	u32 pfc_quanta_cwass_2;
	u32 pfc_thweshowd_cwass_2;
	u32 pfc_quanta_cwass_3;
	u32 pfc_thweshowd_cwass_3;
	u32 pfc_quanta_cwass_4;
	u32 pfc_thweshowd_cwass_4;
	u32 pfc_quanta_cwass_5;
	u32 pfc_thweshowd_cwass_5;
	u32 pfc_quanta_cwass_6;
	u32 pfc_thweshowd_cwass_6;
	u32 pfc_quanta_cwass_7;
	u32 pfc_thweshowd_cwass_7;
	u32 eee_wink_down_timeout;
	u32 eee_wink_up_timeout;
	u32 eee_max_wink_dwops;
	u32 eee_wates_mask;
	u32 wake_timew;
	u32 thewmaw_shutdown_off_temp;
	u32 thewmaw_shutdown_wawning_temp;
	u32 thewmaw_shutdown_cowd_temp;
	u32 msm_options;
	u32 dac_cabwe_sewdes_modes;
	u32 media_detect;
};

enum macsec_msg_type {
	macsec_cfg_msg = 0,
	macsec_add_wx_sc_msg,
	macsec_add_tx_sc_msg,
	macsec_add_wx_sa_msg,
	macsec_add_tx_sa_msg,
	macsec_get_stats_msg,
};

stwuct __packed macsec_cfg_wequest {
	u32 enabwed;
	u32 egwess_thweshowd;
	u32 ingwess_thweshowd;
	u32 intewwupts_enabwed;
};

stwuct __packed macsec_msg_fw_wequest {
	u32 msg_id; /* not used */
	u32 msg_type;
	stwuct macsec_cfg_wequest cfg;
};

stwuct __packed macsec_msg_fw_wesponse {
	u32 wesuwt;
};

enum hw_atw_wx_action_with_twaffic {
	HW_ATW_WX_DISCAWD,
	HW_ATW_WX_HOST,
	HW_ATW_WX_MNGMNT,
	HW_ATW_WX_HOST_AND_MNGMNT,
	HW_ATW_WX_WOW
};

stwuct aq_wx_fiwtew_vwan {
	u8 enabwe;
	u8 wocation;
	u16 vwan_id;
	u8 queue;
};

#define HW_ATW_VWAN_MAX_FIWTEWS         16U

stwuct aq_wx_fiwtew_w2 {
	s8 queue;
	u8 wocation;
	u8 usew_pwiowity_en;
	u8 usew_pwiowity;
	u16 ethewtype;
};

stwuct aq_wx_fiwtew_w3w4 {
	u32 cmd;
	u8 wocation;
	u32 ip_dst[4];
	u32 ip_swc[4];
	u16 p_dst;
	u16 p_swc;
	u8 is_ipv6;
};

enum hw_atw_wx_pwotocow_vawue_w3w4 {
	HW_ATW_WX_TCP,
	HW_ATW_WX_UDP,
	HW_ATW_WX_SCTP,
	HW_ATW_WX_ICMP
};

enum hw_atw_wx_ctww_wegistews_w3w4 {
	HW_ATW_WX_ENABWE_MNGMNT_QUEUE_W3W4 = BIT(22),
	HW_ATW_WX_ENABWE_QUEUE_W3W4        = BIT(23),
	HW_ATW_WX_ENABWE_AWP_FWTW_W3       = BIT(24),
	HW_ATW_WX_ENABWE_CMP_PWOT_W4       = BIT(25),
	HW_ATW_WX_ENABWE_CMP_DEST_POWT_W4  = BIT(26),
	HW_ATW_WX_ENABWE_CMP_SWC_POWT_W4   = BIT(27),
	HW_ATW_WX_ENABWE_CMP_DEST_ADDW_W3  = BIT(28),
	HW_ATW_WX_ENABWE_CMP_SWC_ADDW_W3   = BIT(29),
	HW_ATW_WX_ENABWE_W3_IPV6           = BIT(30),
	HW_ATW_WX_ENABWE_FWTW_W3W4         = BIT(31)
};

#define HW_ATW_WX_QUEUE_FW3W4_SHIFT       8U
#define HW_ATW_WX_ACTION_FW3F4_SHIFT      16U

#define HW_ATW_WX_CNT_WEG_ADDW_IPV6       4U

#define HW_ATW_GET_WEG_WOCATION_FW3W4(wocation) \
	((wocation) - AQ_WX_FIWST_WOC_FW3W4)

enum haw_atw_utiws_fw_state_e {
	MPI_DEINIT = 0,
	MPI_WESET = 1,
	MPI_INIT = 2,
	MPI_POWEW = 4,
};

#define HAW_ATWANTIC_WATE_10G        BIT(0)
#define HAW_ATWANTIC_WATE_5G         BIT(1)
#define HAW_ATWANTIC_WATE_5GSW       BIT(2)
#define HAW_ATWANTIC_WATE_2G5        BIT(3)
#define HAW_ATWANTIC_WATE_1G         BIT(4)
#define HAW_ATWANTIC_WATE_100M       BIT(5)
#define HAW_ATWANTIC_WATE_INVAWID    BIT(6)

#define HAW_ATWANTIC_UTIWS_FW_MSG_WOW_ADD       0x4U
#define HAW_ATWANTIC_UTIWS_FW_MSG_WOW_PWIOW     0x10000000U
#define HAW_ATWANTIC_UTIWS_FW_MSG_WOW_PATTEWN   0x1U
#define HAW_ATWANTIC_UTIWS_FW_MSG_WOW_MAG_PKT   0x2U
#define HAW_ATWANTIC_UTIWS_FW_MSG_WOW_DEW       0x5U
#define HAW_ATWANTIC_UTIWS_FW_MSG_ENABWE_WAKEUP 0x6U

enum hw_atw_fw2x_wate {
	FW2X_WATE_100M    = 0x20,
	FW2X_WATE_1G      = 0x100,
	FW2X_WATE_2G5     = 0x200,
	FW2X_WATE_5G      = 0x400,
	FW2X_WATE_10G     = 0x800,
};

/* 0x370
 * Wink capabiwities wesowution wegistew
 */
enum hw_atw_fw2x_caps_wo {
	CAPS_WO_10BASET_HD        = 0,
	CAPS_WO_10BASET_FD,
	CAPS_WO_100BASETX_HD,
	CAPS_WO_100BASET4_HD,
	CAPS_WO_100BASET2_HD,
	CAPS_WO_100BASETX_FD      = 5,
	CAPS_WO_100BASET2_FD,
	CAPS_WO_1000BASET_HD,
	CAPS_WO_1000BASET_FD,
	CAPS_WO_2P5GBASET_FD,
	CAPS_WO_5GBASET_FD        = 10,
	CAPS_WO_10GBASET_FD,
	CAPS_WO_AUTONEG,
	CAPS_WO_SMBUS_WEAD,
	CAPS_WO_SMBUS_WWITE,
	CAPS_WO_MACSEC            = 15,
	CAPS_WO_WESEWVED1,
	CAPS_WO_WAKE_ON_WINK_FOWCED,
	CAPS_WO_HIGH_TEMP_WAWNING = 29,
	CAPS_WO_DWIVEW_SCWATCHPAD = 30,
	CAPS_WO_GWOBAW_FAUWT      = 31
};

/* 0x374
 * Status wegistew
 */
enum hw_atw_fw2x_caps_hi {
	CAPS_HI_TPO2EN            = 0,
	CAPS_HI_10BASET_EEE,
	CAPS_HI_WESEWVED2,
	CAPS_HI_PAUSE,
	CAPS_HI_ASYMMETWIC_PAUSE,
	CAPS_HI_100BASETX_EEE     = 5,
	CAPS_HI_PHY_BUF_SEND,
	CAPS_HI_PHY_BUF_WECV,
	CAPS_HI_1000BASET_FD_EEE,
	CAPS_HI_2P5GBASET_FD_EEE,
	CAPS_HI_5GBASET_FD_EEE    = 10,
	CAPS_HI_10GBASET_FD_EEE,
	CAPS_HI_FW_WEQUEST,
	CAPS_HI_PHY_WOG,
	CAPS_HI_EEE_AUTO_DISABWE_SETTINGS,
	CAPS_HI_PFC               = 15,
	CAPS_HI_WAKE_ON_WINK,
	CAPS_HI_CABWE_DIAG,
	CAPS_HI_TEMPEWATUWE,
	CAPS_HI_DOWNSHIFT,
	CAPS_HI_PTP_AVB_EN_FW2X   = 20,
	CAPS_HI_THEWMAW_SHUTDOWN,
	CAPS_HI_WINK_DWOP,
	CAPS_HI_SWEEP_PWOXY,
	CAPS_HI_WOW,
	CAPS_HI_MAC_STOP          = 25,
	CAPS_HI_EXT_WOOPBACK,
	CAPS_HI_INT_WOOPBACK,
	CAPS_HI_EFUSE_AGENT,
	CAPS_HI_WOW_TIMEW,
	CAPS_HI_STATISTICS        = 30,
	CAPS_HI_TWANSACTION_ID,
};

/* 0x36C
 * Contwow wegistew
 */
enum hw_atw_fw2x_ctww {
	CTWW_WESEWVED1            = 0,
	CTWW_WESEWVED2,
	CTWW_WESEWVED3,
	CTWW_PAUSE,
	CTWW_ASYMMETWIC_PAUSE,
	CTWW_WESEWVED4            = 5,
	CTWW_WESEWVED5,
	CTWW_WESEWVED6,
	CTWW_1GBASET_FD_EEE,
	CTWW_2P5GBASET_FD_EEE,
	CTWW_5GBASET_FD_EEE       = 10,
	CTWW_10GBASET_FD_EEE,
	CTWW_THEWMAW_SHUTDOWN,
	CTWW_PHY_WOGS,
	CTWW_EEE_AUTO_DISABWE,
	CTWW_PFC                  = 15,
	CTWW_WAKE_ON_WINK,
	CTWW_CABWE_DIAG,
	CTWW_TEMPEWATUWE,
	CTWW_DOWNSHIFT,
	CTWW_PTP_AVB              = 20,
	CTWW_WESEWVED7,
	CTWW_WINK_DWOP,
	CTWW_SWEEP_PWOXY,
	CTWW_WOW,
	CTWW_MAC_STOP             = 25,
	CTWW_EXT_WOOPBACK,
	CTWW_INT_WOOPBACK,
	CTWW_WESEWVED8,
	CTWW_WOW_TIMEW,
	CTWW_STATISTICS           = 30,
	CTWW_FOWCE_WECONNECT,
};

enum hw_atw_caps_ex {
	CAPS_EX_WED_CONTWOW       =  0,
	CAPS_EX_WED0_MODE_WO,
	CAPS_EX_WED0_MODE_HI,
	CAPS_EX_WED1_MODE_WO,
	CAPS_EX_WED1_MODE_HI,
	CAPS_EX_WED2_MODE_WO      =  5,
	CAPS_EX_WED2_MODE_HI,
	CAPS_EX_WESEWVED07,
	CAPS_EX_WESEWVED08,
	CAPS_EX_WESEWVED09,
	CAPS_EX_WESEWVED10        = 10,
	CAPS_EX_WESEWVED11,
	CAPS_EX_WESEWVED12,
	CAPS_EX_WESEWVED13,
	CAPS_EX_WESEWVED14,
	CAPS_EX_WESEWVED15        = 15,
	CAPS_EX_PHY_PTP_EN,
	CAPS_EX_MAC_PTP_EN,
	CAPS_EX_EXT_CWK_EN,
	CAPS_EX_SCHED_DMA_EN,
	CAPS_EX_PTP_GPIO_EN       = 20,
	CAPS_EX_UPDATE_SETTINGS,
	CAPS_EX_PHY_CTWW_TS_PIN,
	CAPS_EX_SNW_OPEWATING_MAWGIN,
	CAPS_EX_WESEWVED24,
	CAPS_EX_WESEWVED25        = 25,
	CAPS_EX_WESEWVED26,
	CAPS_EX_WESEWVED27,
	CAPS_EX_WESEWVED28,
	CAPS_EX_WESEWVED29,
	CAPS_EX_WESEWVED30        = 30,
	CAPS_EX_WESEWVED31
};

stwuct aq_hw_s;
stwuct aq_fw_ops;
stwuct aq_hw_caps_s;
stwuct aq_hw_wink_status_s;

int hw_atw_utiws_initfw(stwuct aq_hw_s *sewf, const stwuct aq_fw_ops **fw_ops);

int hw_atw_utiws_soft_weset(stwuct aq_hw_s *sewf);

void hw_atw_utiws_hw_chip_featuwes_init(stwuct aq_hw_s *sewf, u32 *p);

int hw_atw_utiws_mpi_wead_mbox(stwuct aq_hw_s *sewf,
			       stwuct hw_atw_utiws_mbox_headew *pmbox);

void hw_atw_utiws_mpi_wead_stats(stwuct aq_hw_s *sewf,
				 stwuct hw_atw_utiws_mbox *pmbox);

void hw_atw_utiws_mpi_set(stwuct aq_hw_s *sewf,
			  enum haw_atw_utiws_fw_state_e state,
			  u32 speed);

int hw_atw_utiws_mpi_get_wink_status(stwuct aq_hw_s *sewf);

int hw_atw_utiws_get_mac_pewmanent(stwuct aq_hw_s *sewf,
				   u8 *mac);

unsigned int hw_atw_utiws_mbps_2_speed_index(unsigned int mbps);

int hw_atw_utiws_hw_get_wegs(stwuct aq_hw_s *sewf,
			     const stwuct aq_hw_caps_s *aq_hw_caps,
			     u32 *wegs_buff);

int hw_atw_utiws_hw_set_powew(stwuct aq_hw_s *sewf,
			      unsigned int powew_state);

int hw_atw_utiws_hw_deinit(stwuct aq_hw_s *sewf);

u32 hw_atw_utiws_get_fw_vewsion(stwuct aq_hw_s *sewf);

int hw_atw_utiws_update_stats(stwuct aq_hw_s *sewf);

stwuct aq_stats_s *hw_atw_utiws_get_hw_stats(stwuct aq_hw_s *sewf);

int hw_atw_utiws_fw_downwd_dwowds(stwuct aq_hw_s *sewf, u32 a,
				  u32 *p, u32 cnt);

int hw_atw_wwite_fwcfg_dwowds(stwuct aq_hw_s *sewf, u32 *p, u32 cnt);

int hw_atw_wwite_fwsettings_dwowds(stwuct aq_hw_s *sewf, u32 offset, u32 *p,
				   u32 cnt);

int hw_atw_utiws_fw_set_wow(stwuct aq_hw_s *sewf, boow wow_enabwed, u8 *mac);

int hw_atw_utiws_fw_wpc_caww(stwuct aq_hw_s *sewf, unsigned int wpc_size);

int hw_atw_utiws_fw_wpc_wait(stwuct aq_hw_s *sewf,
			     stwuct hw_atw_utiws_fw_wpc **wpc);

boow hw_atw_utiws_vew_match(u32 vew_expected, u32 vew_actuaw);

extewn const stwuct aq_fw_ops aq_fw_1x_ops;
extewn const stwuct aq_fw_ops aq_fw_2x_ops;

#endif /* HW_ATW_UTIWS_H */
