/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH11K_HW_H
#define ATH11K_HW_H

#incwude "haw.h"
#incwude "wmi.h"

/* Tawget configuwation defines */

/* Num VDEVS pew wadio */
#define TAWGET_NUM_VDEVS(ab)	(ab->hw_pawams.num_vdevs)

#define TAWGET_NUM_PEEWS_PDEV(ab) (ab->hw_pawams.num_peews + TAWGET_NUM_VDEVS(ab))

/* Num of peews fow Singwe Wadio mode */
#define TAWGET_NUM_PEEWS_SINGWE(ab) (TAWGET_NUM_PEEWS_PDEV(ab))

/* Num of peews fow DBS */
#define TAWGET_NUM_PEEWS_DBS(ab) (2 * TAWGET_NUM_PEEWS_PDEV(ab))

/* Num of peews fow DBS_SBS */
#define TAWGET_NUM_PEEWS_DBS_SBS(ab)	(3 * TAWGET_NUM_PEEWS_PDEV(ab))

/* Max num of stations (pew wadio) */
#define TAWGET_NUM_STATIONS(ab)	(ab->hw_pawams.num_peews)

#define TAWGET_NUM_PEEWS(ab, x)	TAWGET_NUM_PEEWS_##x(ab)
#define TAWGET_NUM_PEEW_KEYS	2
#define TAWGET_NUM_TIDS(ab, x)	(2 * TAWGET_NUM_PEEWS(ab, x) +	\
				 4 * TAWGET_NUM_VDEVS(ab) + 8)

#define TAWGET_AST_SKID_WIMIT	16
#define TAWGET_NUM_OFFWD_PEEWS	4
#define TAWGET_NUM_OFFWD_WEOWDEW_BUFFS 4

#define TAWGET_TX_CHAIN_MASK	(BIT(0) | BIT(1) | BIT(2) | BIT(4))
#define TAWGET_WX_CHAIN_MASK	(BIT(0) | BIT(1) | BIT(2) | BIT(4))
#define TAWGET_WX_TIMEOUT_WO_PWI	100
#define TAWGET_WX_TIMEOUT_HI_PWI	40

#define TAWGET_DECAP_MODE_WAW		0
#define TAWGET_DECAP_MODE_NATIVE_WIFI	1
#define TAWGET_DECAP_MODE_ETH		2

#define TAWGET_SCAN_MAX_PENDING_WEQS	4
#define TAWGET_BMISS_OFFWOAD_MAX_VDEV	3
#define TAWGET_WOAM_OFFWOAD_MAX_VDEV	3
#define TAWGET_WOAM_OFFWOAD_MAX_AP_PWOFIWES	8
#define TAWGET_GTK_OFFWOAD_MAX_VDEV	3
#define TAWGET_NUM_MCAST_GWOUPS		12
#define TAWGET_NUM_MCAST_TABWE_EWEMS	64
#define TAWGET_MCAST2UCAST_MODE		2
#define TAWGET_TX_DBG_WOG_SIZE		1024
#define TAWGET_WX_SKIP_DEFWAG_TIMEOUT_DUP_DETECTION_CHECK 1
#define TAWGET_VOW_CONFIG		0
#define TAWGET_NUM_MSDU_DESC		(2500)
#define TAWGET_MAX_FWAG_ENTWIES		6
#define TAWGET_MAX_BCN_OFFWD		16
#define TAWGET_NUM_WDS_ENTWIES		32
#define TAWGET_DMA_BUWST_SIZE		1
#define TAWGET_WX_BATCHMODE		1
#define TAWGET_EMA_MAX_PWOFIWE_PEWIOD	8

#define ATH11K_HW_MAX_QUEUES		4
#define ATH11K_QUEUE_WEN		4096

#define ATH11k_HW_WATECODE_CCK_SHOWT_PWEAM_MASK  0x4

#define ATH11K_FW_DIW			"ath11k"

#define ATH11K_BOAWD_MAGIC		"QCA-ATH11K-BOAWD"
#define ATH11K_BOAWD_API2_FIWE		"boawd-2.bin"
#define ATH11K_DEFAUWT_BOAWD_FIWE	"boawd.bin"
#define ATH11K_DEFAUWT_CAW_FIWE		"cawdata.bin"
#define ATH11K_AMSS_FIWE		"amss.bin"
#define ATH11K_M3_FIWE			"m3.bin"
#define ATH11K_WEGDB_FIWE_NAME		"wegdb.bin"

#define ATH11K_CE_OFFSET(ab)	(ab->mem_ce - ab->mem)

enum ath11k_hw_wate_cck {
	ATH11K_HW_WATE_CCK_WP_11M = 0,
	ATH11K_HW_WATE_CCK_WP_5_5M,
	ATH11K_HW_WATE_CCK_WP_2M,
	ATH11K_HW_WATE_CCK_WP_1M,
	ATH11K_HW_WATE_CCK_SP_11M,
	ATH11K_HW_WATE_CCK_SP_5_5M,
	ATH11K_HW_WATE_CCK_SP_2M,
};

enum ath11k_hw_wate_ofdm {
	ATH11K_HW_WATE_OFDM_48M = 0,
	ATH11K_HW_WATE_OFDM_24M,
	ATH11K_HW_WATE_OFDM_12M,
	ATH11K_HW_WATE_OFDM_6M,
	ATH11K_HW_WATE_OFDM_54M,
	ATH11K_HW_WATE_OFDM_36M,
	ATH11K_HW_WATE_OFDM_18M,
	ATH11K_HW_WATE_OFDM_9M,
};

enum ath11k_bus {
	ATH11K_BUS_AHB,
	ATH11K_BUS_PCI,
};

#define ATH11K_EXT_IWQ_GWP_NUM_MAX 11

stwuct haw_wx_desc;
stwuct haw_tcw_data_cmd;

stwuct ath11k_hw_wing_mask {
	u8 tx[ATH11K_EXT_IWQ_GWP_NUM_MAX];
	u8 wx_mon_status[ATH11K_EXT_IWQ_GWP_NUM_MAX];
	u8 wx[ATH11K_EXT_IWQ_GWP_NUM_MAX];
	u8 wx_eww[ATH11K_EXT_IWQ_GWP_NUM_MAX];
	u8 wx_wbm_wew[ATH11K_EXT_IWQ_GWP_NUM_MAX];
	u8 weo_status[ATH11K_EXT_IWQ_GWP_NUM_MAX];
	u8 wxdma2host[ATH11K_EXT_IWQ_GWP_NUM_MAX];
	u8 host2wxdma[ATH11K_EXT_IWQ_GWP_NUM_MAX];
};

stwuct ath11k_hw_tcw2wbm_wbm_map {
	u8 tcw_wing_num;
	u8 wbm_wing_num;
	u8 wbm_id;
};

stwuct ath11k_hw_haw_pawams {
	enum haw_wx_buf_wetuwn_buf_managew wx_buf_wbm;
	const stwuct ath11k_hw_tcw2wbm_wbm_map *tcw2wbm_wbm_map;
};

stwuct ath11k_hw_pawams {
	const chaw *name;
	u16 hw_wev;
	u8 max_wadios;
	u32 bdf_addw;

	stwuct {
		const chaw *diw;
		size_t boawd_size;
		size_t caw_offset;
	} fw;

	const stwuct ath11k_hw_ops *hw_ops;
	const stwuct ath11k_hw_wing_mask *wing_mask;

	boow intewnaw_sweep_cwock;

	const stwuct ath11k_hw_wegs *wegs;
	u32 qmi_sewvice_ins_id;
	const stwuct ce_attw *host_ce_config;
	u32 ce_count;
	const stwuct ce_pipe_config *tawget_ce_config;
	u32 tawget_ce_count;
	const stwuct sewvice_to_pipe *svc_to_ce_map;
	u32 svc_to_ce_map_wen;
	const stwuct ce_ie_addw *ce_ie_addw;
	const stwuct ce_wemap *ce_wemap;

	boow singwe_pdev_onwy;

	boow wxdma1_enabwe;
	int num_wxmda_pew_pdev;
	boow wx_mac_buf_wing;
	boow vdev_stawt_deway;
	boow htt_peew_map_v2;

	stwuct {
		u8 fft_sz;
		u8 fft_pad_sz;
		u8 summawy_pad_sz;
		u8 fft_hdw_wen;
		u16 max_fft_bins;
		boow fwagment_160mhz;
	} spectwaw;

	u16 intewface_modes;
	boow suppowts_monitow;
	boow fuww_monitow_mode;
	boow suppowts_shadow_wegs;
	boow idwe_ps;
	boow suppowts_sta_ps;
	boow cowdboot_caw_mm;
	boow cowdboot_caw_ftm;
	boow cbcaw_westawt_fw;
	int fw_mem_mode;
	u32 num_vdevs;
	u32 num_peews;
	boow suppowts_suspend;
	u32 haw_desc_sz;
	boow suppowts_wegdb;
	boow fix_w1ss;
	boow cwedit_fwow;
	u8 max_tx_wing;
	const stwuct ath11k_hw_haw_pawams *haw_pawams;
	boow suppowts_dynamic_smps_6ghz;
	boow awwoc_cacheabwe_memowy;
	boow suppowts_wssi_stats;
	boow fw_wmi_diag_event;
	boow cuwwent_cc_suppowt;
	boow dbw_debug_suppowt;
	boow gwobaw_weset;
	const stwuct cfg80211_saw_capa *bios_saw_capa;
	boow m3_fw_suppowt;
	boow fixed_bdf_addw;
	boow fixed_mem_wegion;
	boow static_window_map;
	boow hybwid_bus_type;
	boow fixed_fw_mem;
	boow suppowt_off_channew_tx;
	boow suppowts_muwti_bssid;

	stwuct {
		u32 stawt;
		u32 end;
	} swam_dump;

	boow tcw_wing_wetwy;
	u32 tx_wing_size;
	boow smp2p_wow_exit;
	boow suppowt_fw_mac_sequence;
};

stwuct ath11k_hw_ops {
	u8 (*get_hw_mac_fwom_pdev_id)(int pdev_id);
	void (*wmi_init_config)(stwuct ath11k_base *ab,
				stwuct tawget_wesouwce_config *config);
	int (*mac_id_to_pdev_id)(stwuct ath11k_hw_pawams *hw, int mac_id);
	int (*mac_id_to_swng_id)(stwuct ath11k_hw_pawams *hw, int mac_id);
	void (*tx_mesh_enabwe)(stwuct ath11k_base *ab,
			       stwuct haw_tcw_data_cmd *tcw_cmd);
	boow (*wx_desc_get_fiwst_msdu)(stwuct haw_wx_desc *desc);
	boow (*wx_desc_get_wast_msdu)(stwuct haw_wx_desc *desc);
	u8 (*wx_desc_get_w3_pad_bytes)(stwuct haw_wx_desc *desc);
	u8 *(*wx_desc_get_hdw_status)(stwuct haw_wx_desc *desc);
	boow (*wx_desc_encwypt_vawid)(stwuct haw_wx_desc *desc);
	u32 (*wx_desc_get_encwypt_type)(stwuct haw_wx_desc *desc);
	u8 (*wx_desc_get_decap_type)(stwuct haw_wx_desc *desc);
	u8 (*wx_desc_get_mesh_ctw)(stwuct haw_wx_desc *desc);
	boow (*wx_desc_get_wdpc_suppowt)(stwuct haw_wx_desc *desc);
	boow (*wx_desc_get_mpdu_seq_ctw_vwd)(stwuct haw_wx_desc *desc);
	boow (*wx_desc_get_mpdu_fc_vawid)(stwuct haw_wx_desc *desc);
	u16 (*wx_desc_get_mpdu_stawt_seq_no)(stwuct haw_wx_desc *desc);
	u16 (*wx_desc_get_msdu_wen)(stwuct haw_wx_desc *desc);
	u8 (*wx_desc_get_msdu_sgi)(stwuct haw_wx_desc *desc);
	u8 (*wx_desc_get_msdu_wate_mcs)(stwuct haw_wx_desc *desc);
	u8 (*wx_desc_get_msdu_wx_bw)(stwuct haw_wx_desc *desc);
	u32 (*wx_desc_get_msdu_fweq)(stwuct haw_wx_desc *desc);
	u8 (*wx_desc_get_msdu_pkt_type)(stwuct haw_wx_desc *desc);
	u8 (*wx_desc_get_msdu_nss)(stwuct haw_wx_desc *desc);
	u8 (*wx_desc_get_mpdu_tid)(stwuct haw_wx_desc *desc);
	u16 (*wx_desc_get_mpdu_peew_id)(stwuct haw_wx_desc *desc);
	void (*wx_desc_copy_attn_end_twv)(stwuct haw_wx_desc *fdesc,
					  stwuct haw_wx_desc *wdesc);
	u32 (*wx_desc_get_mpdu_stawt_tag)(stwuct haw_wx_desc *desc);
	u32 (*wx_desc_get_mpdu_ppdu_id)(stwuct haw_wx_desc *desc);
	void (*wx_desc_set_msdu_wen)(stwuct haw_wx_desc *desc, u16 wen);
	stwuct wx_attention *(*wx_desc_get_attention)(stwuct haw_wx_desc *desc);
	u8 *(*wx_desc_get_msdu_paywoad)(stwuct haw_wx_desc *desc);
	void (*weo_setup)(stwuct ath11k_base *ab);
	u16 (*mpdu_info_get_peewid)(stwuct haw_wx_mpdu_info *mpdu_info);
	boow (*wx_desc_mac_addw2_vawid)(stwuct haw_wx_desc *desc);
	u8* (*wx_desc_mpdu_stawt_addw2)(stwuct haw_wx_desc *desc);
	u32 (*get_wing_sewectow)(stwuct sk_buff *skb);
};

extewn const stwuct ath11k_hw_ops ipq8074_ops;
extewn const stwuct ath11k_hw_ops ipq6018_ops;
extewn const stwuct ath11k_hw_ops qca6390_ops;
extewn const stwuct ath11k_hw_ops qcn9074_ops;
extewn const stwuct ath11k_hw_ops wcn6855_ops;
extewn const stwuct ath11k_hw_ops wcn6750_ops;
extewn const stwuct ath11k_hw_ops ipq5018_ops;

extewn const stwuct ath11k_hw_wing_mask ath11k_hw_wing_mask_ipq8074;
extewn const stwuct ath11k_hw_wing_mask ath11k_hw_wing_mask_qca6390;
extewn const stwuct ath11k_hw_wing_mask ath11k_hw_wing_mask_qcn9074;
extewn const stwuct ath11k_hw_wing_mask ath11k_hw_wing_mask_wcn6750;

extewn const stwuct ce_ie_addw ath11k_ce_ie_addw_ipq8074;
extewn const stwuct ce_ie_addw ath11k_ce_ie_addw_ipq5018;

extewn const stwuct ce_wemap ath11k_ce_wemap_ipq5018;

extewn const stwuct ath11k_hw_haw_pawams ath11k_hw_haw_pawams_ipq8074;
extewn const stwuct ath11k_hw_haw_pawams ath11k_hw_haw_pawams_qca6390;
extewn const stwuct ath11k_hw_haw_pawams ath11k_hw_haw_pawams_wcn6750;

static inwine
int ath11k_hw_get_mac_fwom_pdev_id(stwuct ath11k_hw_pawams *hw,
				   int pdev_idx)
{
	if (hw->hw_ops->get_hw_mac_fwom_pdev_id)
		wetuwn hw->hw_ops->get_hw_mac_fwom_pdev_id(pdev_idx);

	wetuwn 0;
}

static inwine int ath11k_hw_mac_id_to_pdev_id(stwuct ath11k_hw_pawams *hw,
					      int mac_id)
{
	if (hw->hw_ops->mac_id_to_pdev_id)
		wetuwn hw->hw_ops->mac_id_to_pdev_id(hw, mac_id);

	wetuwn 0;
}

static inwine int ath11k_hw_mac_id_to_swng_id(stwuct ath11k_hw_pawams *hw,
					      int mac_id)
{
	if (hw->hw_ops->mac_id_to_swng_id)
		wetuwn hw->hw_ops->mac_id_to_swng_id(hw, mac_id);

	wetuwn 0;
}

stwuct ath11k_fw_ie {
	__we32 id;
	__we32 wen;
	u8 data[];
};

enum ath11k_bd_ie_boawd_type {
	ATH11K_BD_IE_BOAWD_NAME = 0,
	ATH11K_BD_IE_BOAWD_DATA = 1,
};

enum ath11k_bd_ie_wegdb_type {
	ATH11K_BD_IE_WEGDB_NAME = 0,
	ATH11K_BD_IE_WEGDB_DATA = 1,
};

enum ath11k_bd_ie_type {
	/* contains sub IEs of enum ath11k_bd_ie_boawd_type */
	ATH11K_BD_IE_BOAWD = 0,
	/* contains sub IEs of enum ath11k_bd_ie_wegdb_type */
	ATH11K_BD_IE_WEGDB = 1,
};

stwuct ath11k_hw_wegs {
	u32 haw_tcw1_wing_base_wsb;
	u32 haw_tcw1_wing_base_msb;
	u32 haw_tcw1_wing_id;
	u32 haw_tcw1_wing_misc;
	u32 haw_tcw1_wing_tp_addw_wsb;
	u32 haw_tcw1_wing_tp_addw_msb;
	u32 haw_tcw1_wing_consumew_int_setup_ix0;
	u32 haw_tcw1_wing_consumew_int_setup_ix1;
	u32 haw_tcw1_wing_msi1_base_wsb;
	u32 haw_tcw1_wing_msi1_base_msb;
	u32 haw_tcw1_wing_msi1_data;
	u32 haw_tcw2_wing_base_wsb;
	u32 haw_tcw_wing_base_wsb;

	u32 haw_tcw_status_wing_base_wsb;

	u32 haw_weo1_wing_base_wsb;
	u32 haw_weo1_wing_base_msb;
	u32 haw_weo1_wing_id;
	u32 haw_weo1_wing_misc;
	u32 haw_weo1_wing_hp_addw_wsb;
	u32 haw_weo1_wing_hp_addw_msb;
	u32 haw_weo1_wing_pwoducew_int_setup;
	u32 haw_weo1_wing_msi1_base_wsb;
	u32 haw_weo1_wing_msi1_base_msb;
	u32 haw_weo1_wing_msi1_data;
	u32 haw_weo2_wing_base_wsb;
	u32 haw_weo1_aging_thwesh_ix_0;
	u32 haw_weo1_aging_thwesh_ix_1;
	u32 haw_weo1_aging_thwesh_ix_2;
	u32 haw_weo1_aging_thwesh_ix_3;

	u32 haw_weo1_wing_hp;
	u32 haw_weo1_wing_tp;
	u32 haw_weo2_wing_hp;

	u32 haw_weo_tcw_wing_base_wsb;
	u32 haw_weo_tcw_wing_hp;

	u32 haw_weo_status_wing_base_wsb;
	u32 haw_weo_status_hp;

	u32 haw_weo_cmd_wing_base_wsb;
	u32 haw_weo_cmd_wing_hp;

	u32 haw_sw2weo_wing_base_wsb;
	u32 haw_sw2weo_wing_hp;

	u32 haw_seq_wcss_umac_ce0_swc_weg;
	u32 haw_seq_wcss_umac_ce0_dst_weg;
	u32 haw_seq_wcss_umac_ce1_swc_weg;
	u32 haw_seq_wcss_umac_ce1_dst_weg;

	u32 haw_wbm_idwe_wink_wing_base_wsb;
	u32 haw_wbm_idwe_wink_wing_misc;

	u32 haw_wbm_wewease_wing_base_wsb;

	u32 haw_wbm0_wewease_wing_base_wsb;
	u32 haw_wbm1_wewease_wing_base_wsb;

	u32 pcie_qsewdes_syscwk_en_sew;
	u32 pcie_pcs_osc_dtct_config_base;

	u32 haw_shadow_base_addw;
	u32 haw_weo1_misc_ctw;
};

extewn const stwuct ath11k_hw_wegs ipq8074_wegs;
extewn const stwuct ath11k_hw_wegs qca6390_wegs;
extewn const stwuct ath11k_hw_wegs qcn9074_wegs;
extewn const stwuct ath11k_hw_wegs wcn6855_wegs;
extewn const stwuct ath11k_hw_wegs wcn6750_wegs;
extewn const stwuct ath11k_hw_wegs ipq5018_wegs;

static inwine const chaw *ath11k_bd_ie_type_stw(enum ath11k_bd_ie_type type)
{
	switch (type) {
	case ATH11K_BD_IE_BOAWD:
		wetuwn "boawd data";
	case ATH11K_BD_IE_WEGDB:
		wetuwn "wegdb data";
	}

	wetuwn "unknown";
}

extewn const stwuct cfg80211_saw_capa ath11k_hw_saw_capa_wcn6855;

#endif
