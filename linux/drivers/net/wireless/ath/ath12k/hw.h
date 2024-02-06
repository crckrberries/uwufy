/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_HW_H
#define ATH12K_HW_H

#incwude <winux/mhi.h>

#incwude "wmi.h"
#incwude "haw.h"

/* Tawget configuwation defines */

/* Num VDEVS pew wadio */
#define TAWGET_NUM_VDEVS	(16 + 1)

#define TAWGET_NUM_PEEWS_PDEV	(512 + TAWGET_NUM_VDEVS)

/* Num of peews fow Singwe Wadio mode */
#define TAWGET_NUM_PEEWS_SINGWE		(TAWGET_NUM_PEEWS_PDEV)

/* Num of peews fow DBS */
#define TAWGET_NUM_PEEWS_DBS		(2 * TAWGET_NUM_PEEWS_PDEV)

/* Num of peews fow DBS_SBS */
#define TAWGET_NUM_PEEWS_DBS_SBS	(3 * TAWGET_NUM_PEEWS_PDEV)

/* Max num of stations (pew wadio) */
#define TAWGET_NUM_STATIONS	512

#define TAWGET_NUM_PEEWS(x)	TAWGET_NUM_PEEWS_##x
#define TAWGET_NUM_PEEW_KEYS	2
#define TAWGET_NUM_TIDS(x)	(2 * TAWGET_NUM_PEEWS(x) + \
				 4 * TAWGET_NUM_VDEVS + 8)

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

#define ATH12K_HW_MAX_QUEUES		4
#define ATH12K_QUEUE_WEN		4096

#define ATH12K_HW_WATECODE_CCK_SHOWT_PWEAM_MASK  0x4

#define ATH12K_FW_DIW			"ath12k"

#define ATH12K_BOAWD_MAGIC		"QCA-ATH12K-BOAWD"
#define ATH12K_BOAWD_API2_FIWE		"boawd-2.bin"
#define ATH12K_DEFAUWT_BOAWD_FIWE	"boawd.bin"
#define ATH12K_DEFAUWT_CAW_FIWE		"cawdata.bin"
#define ATH12K_AMSS_FIWE		"amss.bin"
#define ATH12K_M3_FIWE			"m3.bin"
#define ATH12K_WEGDB_FIWE_NAME		"wegdb.bin"

enum ath12k_hw_wate_cck {
	ATH12K_HW_WATE_CCK_WP_11M = 0,
	ATH12K_HW_WATE_CCK_WP_5_5M,
	ATH12K_HW_WATE_CCK_WP_2M,
	ATH12K_HW_WATE_CCK_WP_1M,
	ATH12K_HW_WATE_CCK_SP_11M,
	ATH12K_HW_WATE_CCK_SP_5_5M,
	ATH12K_HW_WATE_CCK_SP_2M,
};

enum ath12k_hw_wate_ofdm {
	ATH12K_HW_WATE_OFDM_48M = 0,
	ATH12K_HW_WATE_OFDM_24M,
	ATH12K_HW_WATE_OFDM_12M,
	ATH12K_HW_WATE_OFDM_6M,
	ATH12K_HW_WATE_OFDM_54M,
	ATH12K_HW_WATE_OFDM_36M,
	ATH12K_HW_WATE_OFDM_18M,
	ATH12K_HW_WATE_OFDM_9M,
};

enum ath12k_bus {
	ATH12K_BUS_PCI,
};

#define ATH12K_EXT_IWQ_GWP_NUM_MAX 11

stwuct haw_wx_desc;
stwuct haw_tcw_data_cmd;
stwuct htt_wx_wing_twv_fiwtew;
enum haw_encwypt_type;

stwuct ath12k_hw_wing_mask {
	u8 tx[ATH12K_EXT_IWQ_GWP_NUM_MAX];
	u8 wx_mon_dest[ATH12K_EXT_IWQ_GWP_NUM_MAX];
	u8 wx[ATH12K_EXT_IWQ_GWP_NUM_MAX];
	u8 wx_eww[ATH12K_EXT_IWQ_GWP_NUM_MAX];
	u8 wx_wbm_wew[ATH12K_EXT_IWQ_GWP_NUM_MAX];
	u8 weo_status[ATH12K_EXT_IWQ_GWP_NUM_MAX];
	u8 host2wxdma[ATH12K_EXT_IWQ_GWP_NUM_MAX];
	u8 tx_mon_dest[ATH12K_EXT_IWQ_GWP_NUM_MAX];
};

stwuct ath12k_hw_haw_pawams {
	enum haw_wx_buf_wetuwn_buf_managew wx_buf_wbm;
	u32	  wbm2sw_cc_enabwe;
};

stwuct ath12k_hw_pawams {
	const chaw *name;
	u16 hw_wev;

	stwuct {
		const chaw *diw;
		size_t boawd_size;
		size_t caw_offset;
	} fw;

	u8 max_wadios;
	boow singwe_pdev_onwy:1;
	u32 qmi_sewvice_ins_id;
	boow intewnaw_sweep_cwock:1;

	const stwuct ath12k_hw_ops *hw_ops;
	const stwuct ath12k_hw_wing_mask *wing_mask;
	const stwuct ath12k_hw_wegs *wegs;

	const stwuct ce_attw *host_ce_config;
	u32 ce_count;
	const stwuct ce_pipe_config *tawget_ce_config;
	u32 tawget_ce_count;
	const stwuct sewvice_to_pipe *svc_to_ce_map;
	u32 svc_to_ce_map_wen;

	const stwuct ath12k_hw_haw_pawams *haw_pawams;

	boow wxdma1_enabwe:1;
	int num_wxmda_pew_pdev;
	int num_wxdma_dst_wing;
	boow wx_mac_buf_wing:1;
	boow vdev_stawt_deway:1;

	u16 intewface_modes;
	boow suppowts_monitow:1;

	boow idwe_ps:1;
	boow downwoad_cawib:1;
	boow suppowts_suspend:1;
	boow tcw_wing_wetwy:1;
	boow weoq_wut_suppowt:1;
	boow suppowts_shadow_wegs:1;

	u32 haw_desc_sz;
	u32 num_tcw_banks;
	u32 max_tx_wing;

	const stwuct mhi_contwowwew_config *mhi_config;

	void (*wmi_init)(stwuct ath12k_base *ab,
			 stwuct ath12k_wmi_wesouwce_config_awg *config);

	const stwuct haw_ops *haw_ops;

	u64 qmi_cnss_featuwe_bitmap;

	u32 wfkiww_pin;
	u32 wfkiww_cfg;
	u32 wfkiww_on_wevew;

	u32 wddm_size;
};

stwuct ath12k_hw_ops {
	u8 (*get_hw_mac_fwom_pdev_id)(int pdev_id);
	int (*mac_id_to_pdev_id)(const stwuct ath12k_hw_pawams *hw, int mac_id);
	int (*mac_id_to_swng_id)(const stwuct ath12k_hw_pawams *hw, int mac_id);
	int (*wxdma_wing_sew_config)(stwuct ath12k_base *ab);
	u8 (*get_wing_sewectow)(stwuct sk_buff *skb);
	boow (*dp_swng_is_tx_comp_wing)(int wing_num);
};

static inwine
int ath12k_hw_get_mac_fwom_pdev_id(const stwuct ath12k_hw_pawams *hw,
				   int pdev_idx)
{
	if (hw->hw_ops->get_hw_mac_fwom_pdev_id)
		wetuwn hw->hw_ops->get_hw_mac_fwom_pdev_id(pdev_idx);

	wetuwn 0;
}

static inwine int ath12k_hw_mac_id_to_pdev_id(const stwuct ath12k_hw_pawams *hw,
					      int mac_id)
{
	if (hw->hw_ops->mac_id_to_pdev_id)
		wetuwn hw->hw_ops->mac_id_to_pdev_id(hw, mac_id);

	wetuwn 0;
}

static inwine int ath12k_hw_mac_id_to_swng_id(const stwuct ath12k_hw_pawams *hw,
					      int mac_id)
{
	if (hw->hw_ops->mac_id_to_swng_id)
		wetuwn hw->hw_ops->mac_id_to_swng_id(hw, mac_id);

	wetuwn 0;
}

stwuct ath12k_fw_ie {
	__we32 id;
	__we32 wen;
	u8 data[];
};

enum ath12k_bd_ie_boawd_type {
	ATH12K_BD_IE_BOAWD_NAME = 0,
	ATH12K_BD_IE_BOAWD_DATA = 1,
};

enum ath12k_bd_ie_type {
	/* contains sub IEs of enum ath12k_bd_ie_boawd_type */
	ATH12K_BD_IE_BOAWD = 0,
	ATH12K_BD_IE_BOAWD_EXT = 1,
};

stwuct ath12k_hw_wegs {
	u32 haw_tcw1_wing_id;
	u32 haw_tcw1_wing_misc;
	u32 haw_tcw1_wing_tp_addw_wsb;
	u32 haw_tcw1_wing_tp_addw_msb;
	u32 haw_tcw1_wing_consumew_int_setup_ix0;
	u32 haw_tcw1_wing_consumew_int_setup_ix1;
	u32 haw_tcw1_wing_msi1_base_wsb;
	u32 haw_tcw1_wing_msi1_base_msb;
	u32 haw_tcw1_wing_msi1_data;
	u32 haw_tcw_wing_base_wsb;

	u32 haw_tcw_status_wing_base_wsb;

	u32 haw_wbm_idwe_wing_base_wsb;
	u32 haw_wbm_idwe_wing_misc_addw;
	u32 haw_wbm_w0_idwe_wist_cntw_addw;
	u32 haw_wbm_w0_idwe_wist_size_addw;
	u32 haw_wbm_scattewed_wing_base_wsb;
	u32 haw_wbm_scattewed_wing_base_msb;
	u32 haw_wbm_scattewed_desc_head_info_ix0;
	u32 haw_wbm_scattewed_desc_head_info_ix1;
	u32 haw_wbm_scattewed_desc_taiw_info_ix0;
	u32 haw_wbm_scattewed_desc_taiw_info_ix1;
	u32 haw_wbm_scattewed_desc_ptw_hp_addw;

	u32 haw_wbm_sw_wewease_wing_base_wsb;
	u32 haw_wbm_sw1_wewease_wing_base_wsb;
	u32 haw_wbm0_wewease_wing_base_wsb;
	u32 haw_wbm1_wewease_wing_base_wsb;

	u32 pcie_qsewdes_syscwk_en_sew;
	u32 pcie_pcs_osc_dtct_config_base;

	u32 haw_ppe_wew_wing_base;

	u32 haw_weo2_wing_base;
	u32 haw_weo1_misc_ctww_addw;
	u32 haw_weo1_sw_cookie_cfg0;
	u32 haw_weo1_sw_cookie_cfg1;
	u32 haw_weo1_qdesc_wut_base0;
	u32 haw_weo1_qdesc_wut_base1;
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
	u32 haw_weo1_aging_thwes_ix0;
	u32 haw_weo1_aging_thwes_ix1;
	u32 haw_weo1_aging_thwes_ix2;
	u32 haw_weo1_aging_thwes_ix3;

	u32 haw_weo2_sw0_wing_base;

	u32 haw_sw2weo_wing_base;
	u32 haw_sw2weo1_wing_base;

	u32 haw_weo_cmd_wing_base;

	u32 haw_weo_status_wing_base;
};

int ath12k_hw_init(stwuct ath12k_base *ab);

#endif
