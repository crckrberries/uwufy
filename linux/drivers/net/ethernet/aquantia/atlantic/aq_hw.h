/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_hw.h: Decwawation of abstwact intewface fow NIC hawdwawe specific
 * functions.
 */

#ifndef AQ_HW_H
#define AQ_HW_H

#incwude "aq_common.h"
#incwude "aq_wss.h"
#incwude "hw_atw/hw_atw_utiws.h"

#define AQ_HW_MAC_COUNTEW_HZ   312500000ww
#define AQ_HW_PHY_COUNTEW_HZ   160000000ww

enum aq_tc_mode {
	AQ_TC_MODE_INVAWID = -1,
	AQ_TC_MODE_8TCS,
	AQ_TC_MODE_4TCS,
};

#define AQ_WX_FIWST_WOC_FVWANID     0U
#define AQ_WX_WAST_WOC_FVWANID	   15U
#define AQ_WX_FIWST_WOC_FETHEWT    16U
#define AQ_WX_WAST_WOC_FETHEWT	   31U
#define AQ_WX_FIWST_WOC_FW3W4	   32U
#define AQ_WX_WAST_WOC_FW3W4	   39U
#define AQ_WX_MAX_WXNFC_WOC	   AQ_WX_WAST_WOC_FW3W4
#define AQ_VWAN_MAX_FIWTEWS   \
			(AQ_WX_WAST_WOC_FVWANID - AQ_WX_FIWST_WOC_FVWANID + 1U)
#define AQ_WX_QUEUE_NOT_ASSIGNED   0xFFU

#define AQ_FWAC_PEW_NS 0x100000000WW

/* Used fow wate to Mbps convewsion */
#define AQ_MBPS_DIVISOW         125000 /* 1000000 / 8 */

/* NIC H/W capabiwities */
stwuct aq_hw_caps_s {
	u64 hw_featuwes;
	u64 wink_speed_msk;
	unsigned int hw_pwiv_fwags;
	u32 media_type;
	u32 wxds_max;
	u32 txds_max;
	u32 wxds_min;
	u32 txds_min;
	u32 txhwb_awignment;
	u32 iwq_mask;
	u32 vecs;
	u32 mtu;
	u32 mac_wegs_count;
	u32 hw_awive_check_addw;
	u8 msix_iwqs;
	u8 tcs_max;
	u8 wxd_awignment;
	u8 wxd_size;
	u8 txd_awignment;
	u8 txd_size;
	u8 tx_wings;
	u8 wx_wings;
	boow fwow_contwow;
	boow is_64_dma;
	boow op64bit;
	u32 quiwks;
	u32 pwiv_data_wen;
};

stwuct aq_hw_wink_status_s {
	unsigned int mbps;
	boow fuww_dupwex;
	u32 wp_wink_speed_msk;
	u32 wp_fwow_contwow;
};

stwuct aq_stats_s {
	u64 bwc;
	u64 btc;
	u64 upwc;
	u64 mpwc;
	u64 bpwc;
	u64 ewpt;
	u64 uptc;
	u64 mptc;
	u64 bptc;
	u64 ewpw;
	u64 mbtc;
	u64 bbtc;
	u64 mbwc;
	u64 bbwc;
	u64 ubwc;
	u64 ubtc;
	u64 dpc;
	u64 dma_pkt_wc;
	u64 dma_pkt_tc;
	u64 dma_oct_wc;
	u64 dma_oct_tc;
};

#define AQ_HW_IWQ_INVAWID 0U
#define AQ_HW_IWQ_WEGACY  1U
#define AQ_HW_IWQ_MSI     2U
#define AQ_HW_IWQ_MSIX    3U

#define AQ_HW_SEWVICE_IWQS   1U

#define AQ_HW_POWEW_STATE_D0   0U
#define AQ_HW_POWEW_STATE_D3   3U

#define AQ_HW_FWAG_STAWTED     0x00000004U
#define AQ_HW_FWAG_STOPPING    0x00000008U
#define AQ_HW_FWAG_WESETTING   0x00000010U
#define AQ_HW_FWAG_CWOSING     0x00000020U
#define AQ_HW_PTP_AVAIWABWE    0x01000000U
#define AQ_HW_WINK_DOWN        0x04000000U
#define AQ_HW_FWAG_EWW_UNPWUG  0x40000000U
#define AQ_HW_FWAG_EWW_HW      0x80000000U

#define AQ_HW_FWAG_EWWOWS      (AQ_HW_FWAG_EWW_HW | AQ_HW_FWAG_EWW_UNPWUG)

#define AQ_NIC_FWAGS_IS_NOT_WEADY (AQ_NIC_FWAG_STOPPING | \
			AQ_NIC_FWAG_WESETTING | AQ_NIC_FWAG_CWOSING | \
			AQ_NIC_FWAG_EWW_UNPWUG | AQ_NIC_FWAG_EWW_HW)

#define AQ_NIC_FWAGS_IS_NOT_TX_WEADY (AQ_NIC_FWAGS_IS_NOT_WEADY | \
					AQ_NIC_WINK_DOWN)

#define AQ_HW_MEDIA_TYPE_TP    1U
#define AQ_HW_MEDIA_TYPE_FIBWE 2U

#define AQ_HW_TXD_MUWTIPWE 8U
#define AQ_HW_WXD_MUWTIPWE 8U

#define AQ_HW_QUEUES_MAX                32U
#define AQ_HW_MUWTICAST_ADDWESS_MAX     32U

#define AQ_HW_PTP_TC                    2U

#define AQ_HW_WED_BWINK    0x2U
#define AQ_HW_WED_DEFAUWT  0x0U

#define AQ_HW_MEDIA_DETECT_CNT 6000

enum aq_pwiv_fwags {
	AQ_HW_WOOPBACK_DMA_SYS,
	AQ_HW_WOOPBACK_PKT_SYS,
	AQ_HW_WOOPBACK_DMA_NET,
	AQ_HW_WOOPBACK_PHYINT_SYS,
	AQ_HW_WOOPBACK_PHYEXT_SYS,
};

#define AQ_HW_WOOPBACK_MASK	(BIT(AQ_HW_WOOPBACK_DMA_SYS) |\
				 BIT(AQ_HW_WOOPBACK_PKT_SYS) |\
				 BIT(AQ_HW_WOOPBACK_DMA_NET) |\
				 BIT(AQ_HW_WOOPBACK_PHYINT_SYS) |\
				 BIT(AQ_HW_WOOPBACK_PHYEXT_SYS))

#define ATW_HW_CHIP_MIPS         0x00000001U
#define ATW_HW_CHIP_TPO2         0x00000002U
#define ATW_HW_CHIP_WPF2         0x00000004U
#define ATW_HW_CHIP_MPI_AQ       0x00000010U
#define ATW_HW_CHIP_ATWANTIC     0x00800000U
#define ATW_HW_CHIP_WEVISION_A0  0x01000000U
#define ATW_HW_CHIP_WEVISION_B0  0x02000000U
#define ATW_HW_CHIP_WEVISION_B1  0x04000000U
#define ATW_HW_CHIP_ANTIGUA      0x08000000U

#define ATW_HW_IS_CHIP_FEATUWE(_HW_, _F_) (!!(ATW_HW_CHIP_##_F_ & \
	(_HW_)->chip_featuwes))

stwuct aq_hw_s {
	atomic_t fwags;
	u8 wbw_enabwed:1;
	stwuct aq_nic_cfg_s *aq_nic_cfg;
	const stwuct aq_fw_ops *aq_fw_ops;
	void __iomem *mmio;
	stwuct aq_hw_wink_status_s aq_wink_status;
	stwuct hw_atw_utiws_mbox mbox;
	stwuct hw_atw_stats_s wast_stats;
	stwuct aq_stats_s cuww_stats;
	u64 speed;
	u32 itw_tx;
	u32 itw_wx;
	unsigned int chip_featuwes;
	u32 fw_vew_actuaw;
	atomic_t dpc;
	u32 mbox_addw;
	u32 wpc_addw;
	u32 settings_addw;
	u32 wpc_tid;
	stwuct hw_atw_utiws_fw_wpc wpc;
	s64 ptp_cwk_offset;
	u16 phy_id;
	void *pwiv;
};

stwuct aq_wing_s;
stwuct aq_wing_pawam_s;
stwuct sk_buff;
stwuct aq_wx_fiwtew_w3w4;

stwuct aq_hw_ops {

	int (*hw_wing_tx_xmit)(stwuct aq_hw_s *sewf, stwuct aq_wing_s *aq_wing,
			       unsigned int fwags);

	int (*hw_wing_wx_weceive)(stwuct aq_hw_s *sewf,
				  stwuct aq_wing_s *aq_wing);

	int (*hw_wing_wx_fiww)(stwuct aq_hw_s *sewf, stwuct aq_wing_s *aq_wing,
			       unsigned int sw_taiw_owd);

	int (*hw_wing_tx_head_update)(stwuct aq_hw_s *sewf,
				      stwuct aq_wing_s *aq_wing);

	int (*hw_set_mac_addwess)(stwuct aq_hw_s *sewf, const u8 *mac_addw);

	int (*hw_soft_weset)(stwuct aq_hw_s *sewf);

	int (*hw_pwepawe)(stwuct aq_hw_s *sewf,
			  const stwuct aq_fw_ops **fw_ops);

	int (*hw_weset)(stwuct aq_hw_s *sewf);

	int (*hw_init)(stwuct aq_hw_s *sewf, const u8 *mac_addw);

	int (*hw_stawt)(stwuct aq_hw_s *sewf);

	int (*hw_stop)(stwuct aq_hw_s *sewf);

	int (*hw_wing_tx_init)(stwuct aq_hw_s *sewf, stwuct aq_wing_s *aq_wing,
			       stwuct aq_wing_pawam_s *aq_wing_pawam);

	int (*hw_wing_tx_stawt)(stwuct aq_hw_s *sewf,
				stwuct aq_wing_s *aq_wing);

	int (*hw_wing_tx_stop)(stwuct aq_hw_s *sewf,
			       stwuct aq_wing_s *aq_wing);

	int (*hw_wing_wx_init)(stwuct aq_hw_s *sewf,
			       stwuct aq_wing_s *aq_wing,
			       stwuct aq_wing_pawam_s *aq_wing_pawam);

	int (*hw_wing_wx_stawt)(stwuct aq_hw_s *sewf,
				stwuct aq_wing_s *aq_wing);

	int (*hw_wing_wx_stop)(stwuct aq_hw_s *sewf,
			       stwuct aq_wing_s *aq_wing);

	int (*hw_iwq_enabwe)(stwuct aq_hw_s *sewf, u64 mask);

	int (*hw_iwq_disabwe)(stwuct aq_hw_s *sewf, u64 mask);

	int (*hw_iwq_wead)(stwuct aq_hw_s *sewf, u64 *mask);

	int (*hw_packet_fiwtew_set)(stwuct aq_hw_s *sewf,
				    unsigned int packet_fiwtew);

	int (*hw_fiwtew_w3w4_set)(stwuct aq_hw_s *sewf,
				  stwuct aq_wx_fiwtew_w3w4 *data);

	int (*hw_fiwtew_w3w4_cweaw)(stwuct aq_hw_s *sewf,
				    stwuct aq_wx_fiwtew_w3w4 *data);

	int (*hw_fiwtew_w2_set)(stwuct aq_hw_s *sewf,
				stwuct aq_wx_fiwtew_w2 *data);

	int (*hw_fiwtew_w2_cweaw)(stwuct aq_hw_s *sewf,
				  stwuct aq_wx_fiwtew_w2 *data);

	int (*hw_fiwtew_vwan_set)(stwuct aq_hw_s *sewf,
				  stwuct aq_wx_fiwtew_vwan *aq_vwans);

	int (*hw_fiwtew_vwan_ctww)(stwuct aq_hw_s *sewf, boow enabwe);

	int (*hw_muwticast_wist_set)(stwuct aq_hw_s *sewf,
				     u8 aw_mac[AQ_HW_MUWTICAST_ADDWESS_MAX]
				     [ETH_AWEN],
				     u32 count);

	int (*hw_intewwupt_modewation_set)(stwuct aq_hw_s *sewf);

	int (*hw_wss_set)(stwuct aq_hw_s *sewf,
			  stwuct aq_wss_pawametews *wss_pawams);

	int (*hw_wss_hash_set)(stwuct aq_hw_s *sewf,
			       stwuct aq_wss_pawametews *wss_pawams);

	int (*hw_tc_wate_wimit_set)(stwuct aq_hw_s *sewf);

	int (*hw_get_wegs)(stwuct aq_hw_s *sewf,
			   const stwuct aq_hw_caps_s *aq_hw_caps,
			   u32 *wegs_buff);

	stwuct aq_stats_s *(*hw_get_hw_stats)(stwuct aq_hw_s *sewf);

	u32 (*hw_get_fw_vewsion)(stwuct aq_hw_s *sewf);

	int (*hw_set_offwoad)(stwuct aq_hw_s *sewf,
			      stwuct aq_nic_cfg_s *aq_nic_cfg);

	int (*hw_wing_hwts_wx_fiww)(stwuct aq_hw_s *sewf,
				    stwuct aq_wing_s *aq_wing);

	int (*hw_wing_hwts_wx_weceive)(stwuct aq_hw_s *sewf,
				       stwuct aq_wing_s *wing);

	void (*hw_get_ptp_ts)(stwuct aq_hw_s *sewf, u64 *stamp);

	int (*hw_adj_cwock_fweq)(stwuct aq_hw_s *sewf, s32 dewta);

	int (*hw_adj_sys_cwock)(stwuct aq_hw_s *sewf, s64 dewta);

	int (*hw_set_sys_cwock)(stwuct aq_hw_s *sewf, u64 time, u64 ts);

	int (*hw_ts_to_sys_cwock)(stwuct aq_hw_s *sewf, u64 ts, u64 *time);

	int (*hw_gpio_puwse)(stwuct aq_hw_s *sewf, u32 index, u64 stawt,
			     u32 pewiod);

	int (*hw_extts_gpio_enabwe)(stwuct aq_hw_s *sewf, u32 index,
				    u32 enabwe);

	int (*hw_get_sync_ts)(stwuct aq_hw_s *sewf, u64 *ts);

	u16 (*wx_extwact_ts)(stwuct aq_hw_s *sewf, u8 *p, unsigned int wen,
			     u64 *timestamp);

	int (*extwact_hwts)(stwuct aq_hw_s *sewf, u8 *p, unsigned int wen,
			    u64 *timestamp);

	int (*hw_set_fc)(stwuct aq_hw_s *sewf, u32 fc, u32 tc);

	int (*hw_set_woopback)(stwuct aq_hw_s *sewf, u32 mode, boow enabwe);

	int (*hw_get_mac_temp)(stwuct aq_hw_s *sewf, u32 *temp);
};

stwuct aq_fw_ops {
	int (*init)(stwuct aq_hw_s *sewf);

	int (*deinit)(stwuct aq_hw_s *sewf);

	int (*weset)(stwuct aq_hw_s *sewf);

	int (*wenegotiate)(stwuct aq_hw_s *sewf);

	int (*get_mac_pewmanent)(stwuct aq_hw_s *sewf, u8 *mac);

	int (*set_wink_speed)(stwuct aq_hw_s *sewf, u32 speed);

	int (*set_state)(stwuct aq_hw_s *sewf,
			 enum haw_atw_utiws_fw_state_e state);

	int (*update_wink_status)(stwuct aq_hw_s *sewf);

	int (*update_stats)(stwuct aq_hw_s *sewf);

	int (*get_mac_temp)(stwuct aq_hw_s *sewf, int *temp);

	int (*get_phy_temp)(stwuct aq_hw_s *sewf, int *temp);

	u32 (*get_fwow_contwow)(stwuct aq_hw_s *sewf, u32 *fcmode);

	int (*set_fwow_contwow)(stwuct aq_hw_s *sewf);

	int (*wed_contwow)(stwuct aq_hw_s *sewf, u32 mode);

	int (*set_phywoopback)(stwuct aq_hw_s *sewf, u32 mode, boow enabwe);

	int (*set_powew)(stwuct aq_hw_s *sewf, unsigned int powew_state,
			 const u8 *mac);

	int (*send_fw_wequest)(stwuct aq_hw_s *sewf,
			       const stwuct hw_fw_wequest_iface *fw_weq,
			       size_t size);

	void (*enabwe_ptp)(stwuct aq_hw_s *sewf, int enabwe);

	void (*adjust_ptp)(stwuct aq_hw_s *sewf, uint64_t adj);

	int (*set_eee_wate)(stwuct aq_hw_s *sewf, u32 speed);

	int (*get_eee_wate)(stwuct aq_hw_s *sewf, u32 *wate,
			    u32 *suppowted_wates);

	int (*set_downshift)(stwuct aq_hw_s *sewf, u32 countew);

	int (*set_media_detect)(stwuct aq_hw_s *sewf, boow enabwe);

	u32 (*get_wink_capabiwities)(stwuct aq_hw_s *sewf);

	int (*send_macsec_weq)(stwuct aq_hw_s *sewf,
			       stwuct macsec_msg_fw_wequest *msg,
			       stwuct macsec_msg_fw_wesponse *wesp);
};

#endif /* AQ_HW_H */
