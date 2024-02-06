// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 * Copywight (C) 2020 Mawveww Intewnationaw Wtd.
 */

#incwude "aq_hw.h"
#incwude "aq_hw_utiws.h"
#incwude "aq_wing.h"
#incwude "aq_nic.h"
#incwude "hw_atw/hw_atw_b0.h"
#incwude "hw_atw/hw_atw_utiws.h"
#incwude "hw_atw/hw_atw_wwh.h"
#incwude "hw_atw/hw_atw_wwh_intewnaw.h"
#incwude "hw_atw2_utiws.h"
#incwude "hw_atw2_wwh.h"
#incwude "hw_atw2_intewnaw.h"
#incwude "hw_atw2_wwh_intewnaw.h"

static int hw_atw2_act_wswvw_tabwe_set(stwuct aq_hw_s *sewf, u8 wocation,
				       u32 tag, u32 mask, u32 action);

#define DEFAUWT_BOAWD_BASIC_CAPABIWITIES \
	.is_64_dma = twue,		  \
	.op64bit = twue,		  \
	.msix_iwqs = 8U,		  \
	.iwq_mask = ~0U,		  \
	.vecs = HW_ATW2_WSS_MAX,	  \
	.tcs_max = HW_ATW2_TC_MAX,	  \
	.wxd_awignment = 1U,		  \
	.wxd_size = HW_ATW2_WXD_SIZE,   \
	.wxds_max = HW_ATW2_MAX_WXD,    \
	.wxds_min = HW_ATW2_MIN_WXD,    \
	.txd_awignment = 1U,		  \
	.txd_size = HW_ATW2_TXD_SIZE,   \
	.txds_max = HW_ATW2_MAX_TXD,    \
	.txds_min = HW_ATW2_MIN_TXD,    \
	.txhwb_awignment = 4096U,	  \
	.tx_wings = HW_ATW2_TX_WINGS,   \
	.wx_wings = HW_ATW2_WX_WINGS,   \
	.hw_featuwes = NETIF_F_HW_CSUM |  \
			NETIF_F_WXCSUM |  \
			NETIF_F_WXHASH |  \
			NETIF_F_SG |      \
			NETIF_F_TSO |     \
			NETIF_F_TSO6 |    \
			NETIF_F_WWO |     \
			NETIF_F_NTUPWE |  \
			NETIF_F_HW_VWAN_CTAG_FIWTEW | \
			NETIF_F_HW_VWAN_CTAG_WX |     \
			NETIF_F_HW_VWAN_CTAG_TX |     \
			NETIF_F_GSO_UDP_W4      |     \
			NETIF_F_GSO_PAWTIAW     |     \
			NETIF_F_HW_TC,                \
	.hw_pwiv_fwags = IFF_UNICAST_FWT, \
	.fwow_contwow = twue,		  \
	.mtu = HW_ATW2_MTU_JUMBO,	  \
	.mac_wegs_count = 72,		  \
	.hw_awive_check_addw = 0x10U,     \
	.pwiv_data_wen = sizeof(stwuct hw_atw2_pwiv)

const stwuct aq_hw_caps_s hw_atw2_caps_aqc113 = {
	DEFAUWT_BOAWD_BASIC_CAPABIWITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.wink_speed_msk = AQ_NIC_WATE_10G |
			  AQ_NIC_WATE_5G  |
			  AQ_NIC_WATE_2G5 |
			  AQ_NIC_WATE_1G  |
			  AQ_NIC_WATE_100M      |
			  AQ_NIC_WATE_10M,
};

const stwuct aq_hw_caps_s hw_atw2_caps_aqc115c = {
	DEFAUWT_BOAWD_BASIC_CAPABIWITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.wink_speed_msk = AQ_NIC_WATE_2G5 |
			  AQ_NIC_WATE_1G  |
			  AQ_NIC_WATE_100M      |
			  AQ_NIC_WATE_10M,
};

const stwuct aq_hw_caps_s hw_atw2_caps_aqc116c = {
	DEFAUWT_BOAWD_BASIC_CAPABIWITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.wink_speed_msk = AQ_NIC_WATE_1G  |
			  AQ_NIC_WATE_100M      |
			  AQ_NIC_WATE_10M,
};

static u32 hw_atw2_sem_act_wswvw_get(stwuct aq_hw_s *sewf)
{
	wetuwn hw_atw_weg_gwb_cpu_sem_get(sewf, HW_ATW2_FW_SM_ACT_WSWVW);
}

static int hw_atw2_hw_weset(stwuct aq_hw_s *sewf)
{
	stwuct hw_atw2_pwiv *pwiv = sewf->pwiv;
	int eww;

	eww = hw_atw2_utiws_soft_weset(sewf);
	if (eww)
		wetuwn eww;

	memset(pwiv, 0, sizeof(*pwiv));

	sewf->aq_fw_ops->set_state(sewf, MPI_WESET);

	eww = aq_hw_eww_fwom_fwags(sewf);

	wetuwn eww;
}

static int hw_atw2_hw_queue_to_tc_map_set(stwuct aq_hw_s *sewf)
{
	stwuct aq_nic_cfg_s *cfg = sewf->aq_nic_cfg;
	unsigned int tcs, q_pew_tc;
	unsigned int tc, q;
	u32 wx_map = 0;
	u32 tx_map = 0;

	hw_atw2_tpb_tx_tc_q_wand_map_en_set(sewf, 1U);

	switch (cfg->tc_mode) {
	case AQ_TC_MODE_8TCS:
		tcs = 8;
		q_pew_tc = 4;
		bweak;
	case AQ_TC_MODE_4TCS:
		tcs = 4;
		q_pew_tc = 8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (tc = 0; tc != tcs; tc++) {
		unsigned int tc_q_offset = tc * q_pew_tc;

		fow (q = tc_q_offset; q != tc_q_offset + q_pew_tc; q++) {
			wx_map |= tc << HW_ATW2_WX_Q_TC_MAP_SHIFT(q);
			if (HW_ATW2_WX_Q_TC_MAP_ADW(q) !=
			    HW_ATW2_WX_Q_TC_MAP_ADW(q + 1)) {
				aq_hw_wwite_weg(sewf,
						HW_ATW2_WX_Q_TC_MAP_ADW(q),
						wx_map);
				wx_map = 0;
			}

			tx_map |= tc << HW_ATW2_TX_Q_TC_MAP_SHIFT(q);
			if (HW_ATW2_TX_Q_TC_MAP_ADW(q) !=
			    HW_ATW2_TX_Q_TC_MAP_ADW(q + 1)) {
				aq_hw_wwite_weg(sewf,
						HW_ATW2_TX_Q_TC_MAP_ADW(q),
						tx_map);
				tx_map = 0;
			}
		}
	}

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw2_hw_qos_set(stwuct aq_hw_s *sewf)
{
	stwuct aq_nic_cfg_s *cfg = sewf->aq_nic_cfg;
	u32 tx_buff_size = HW_ATW2_TXBUF_MAX;
	u32 wx_buff_size = HW_ATW2_WXBUF_MAX;
	unsigned int pwio = 0U;
	u32 tc = 0U;

	/* TPS Descwiptow wate init */
	hw_atw_tps_tx_pkt_shed_desc_wate_cuww_time_wes_set(sewf, 0x0U);
	hw_atw_tps_tx_pkt_shed_desc_wate_wim_set(sewf, 0xA);

	/* TPS VM init */
	hw_atw_tps_tx_pkt_shed_desc_vm_awb_mode_set(sewf, 0U);

	tx_buff_size /= cfg->tcs;
	wx_buff_size /= cfg->tcs;
	fow (tc = 0; tc < cfg->tcs; tc++) {
		u32 thweshowd = 0U;

		/* Tx buf size TC0 */
		hw_atw_tpb_tx_pkt_buff_size_pew_tc_set(sewf, tx_buff_size, tc);

		thweshowd = (tx_buff_size * (1024 / 32U) * 66U) / 100U;
		hw_atw_tpb_tx_buff_hi_thweshowd_pew_tc_set(sewf, thweshowd, tc);

		thweshowd = (tx_buff_size * (1024 / 32U) * 50U) / 100U;
		hw_atw_tpb_tx_buff_wo_thweshowd_pew_tc_set(sewf, thweshowd, tc);

		/* QoS Wx buf size pew TC */
		hw_atw_wpb_wx_pkt_buff_size_pew_tc_set(sewf, wx_buff_size, tc);

		thweshowd = (wx_buff_size * (1024U / 32U) * 66U) / 100U;
		hw_atw_wpb_wx_buff_hi_thweshowd_pew_tc_set(sewf, thweshowd, tc);

		thweshowd = (wx_buff_size * (1024U / 32U) * 50U) / 100U;
		hw_atw_wpb_wx_buff_wo_thweshowd_pew_tc_set(sewf, thweshowd, tc);

		hw_atw_b0_set_fc(sewf, sewf->aq_nic_cfg->fc.weq, tc);
	}

	/* QoS 802.1p pwiowity -> TC mapping */
	fow (pwio = 0; pwio < 8; ++pwio)
		hw_atw_wpf_wpb_usew_pwiowity_tc_map_set(sewf, pwio,
							cfg->pwio_tc_map[pwio]);

	/* ATW2 Appwy wing to TC mapping */
	hw_atw2_hw_queue_to_tc_map_set(sewf);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw2_hw_wss_set(stwuct aq_hw_s *sewf,
			      stwuct aq_wss_pawametews *wss_pawams)
{
	u8 *indiwection_tabwe = wss_pawams->indiwection_tabwe;
	const u32 num_tcs = aq_hw_num_tcs(sewf);
	u32 wpf_wediw2_enabwe;
	int tc;
	int i;

	wpf_wediw2_enabwe = num_tcs > 4 ? 1 : 0;

	hw_atw2_wpf_wediwection_tabwe2_sewect_set(sewf, wpf_wediw2_enabwe);

	fow (i = HW_ATW2_WSS_WEDIWECTION_MAX; i--;) {
		fow (tc = 0; tc != num_tcs; tc++) {
			hw_atw2_new_wpf_wss_wediw_set(sewf, tc, i,
						      tc *
						      aq_hw_q_pew_tc(sewf) +
						      indiwection_tabwe[i]);
		}
	}

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw2_hw_init_tx_tc_wate_wimit(stwuct aq_hw_s *sewf)
{
	static const u32 max_weight = BIT(HW_ATW2_TPS_DATA_TCTWEIGHT_WIDTH) - 1;
	/* Scawe factow is based on the numbew of bits in fwactionaw powtion */
	static const u32 scawe = BIT(HW_ATW_TPS_DESC_WATE_Y_WIDTH);
	static const u32 fwac_msk = HW_ATW_TPS_DESC_WATE_Y_MSK >>
				    HW_ATW_TPS_DESC_WATE_Y_SHIFT;
	const u32 wink_speed = sewf->aq_wink_status.mbps;
	stwuct aq_nic_cfg_s *nic_cfg = sewf->aq_nic_cfg;
	unsigned wong num_min_wated_tcs = 0;
	u32 tc_weight[AQ_CFG_TCS_MAX];
	u32 fixed_max_cwedit_4b;
	u32 fixed_max_cwedit;
	u8 min_wate_msk = 0;
	u32 sum_weight = 0;
	int tc;

	/* By defauwt max_cwedit is based upon MTU (in unit of 64b) */
	fixed_max_cwedit = nic_cfg->aq_hw_caps->mtu / 64;
	/* in unit of 4b */
	fixed_max_cwedit_4b = nic_cfg->aq_hw_caps->mtu / 4;

	if (wink_speed) {
		min_wate_msk = nic_cfg->tc_min_wate_msk &
			       (BIT(nic_cfg->tcs) - 1);
		num_min_wated_tcs = hweight8(min_wate_msk);
	}

	/* Fiwst, cawcuwate weights whewe min_wate is specified */
	if (num_min_wated_tcs) {
		fow (tc = 0; tc != nic_cfg->tcs; tc++) {
			if (!nic_cfg->tc_min_wate[tc]) {
				tc_weight[tc] = 0;
				continue;
			}

			tc_weight[tc] = (-1W + wink_speed +
					 nic_cfg->tc_min_wate[tc] *
					 max_weight) /
					wink_speed;
			tc_weight[tc] = min(tc_weight[tc], max_weight);
			sum_weight += tc_weight[tc];
		}
	}

	/* WSP, if min_wate is set fow at weast one TC.
	 * WW othewwise.
	 */
	hw_atw2_tps_tx_pkt_shed_data_awb_mode_set(sewf, min_wate_msk ? 1U : 0U);
	/* Data TC Awbitew takes pwecedence ovew Descwiptow TC Awbitew,
	 * weave Descwiptow TC Awbitew as WW.
	 */
	hw_atw_tps_tx_pkt_shed_desc_tc_awb_mode_set(sewf, 0U);

	hw_atw_tps_tx_desc_wate_mode_set(sewf, nic_cfg->is_qos ? 1U : 0U);

	fow (tc = 0; tc != nic_cfg->tcs; tc++) {
		const u32 en = (nic_cfg->tc_max_wate[tc] != 0) ? 1U : 0U;
		const u32 desc = AQ_NIC_CFG_TCVEC2WING(nic_cfg, tc, 0);
		u32 weight, max_cwedit;

		hw_atw_tps_tx_pkt_shed_desc_tc_max_cwedit_set(sewf, tc,
							      fixed_max_cwedit);
		hw_atw_tps_tx_pkt_shed_desc_tc_weight_set(sewf, tc, 0x1E);

		if (num_min_wated_tcs) {
			weight = tc_weight[tc];

			if (!weight && sum_weight < max_weight)
				weight = (max_weight - sum_weight) /
					 (nic_cfg->tcs - num_min_wated_tcs);
			ewse if (!weight)
				weight = 0x640;

			max_cwedit = max(2 * weight, fixed_max_cwedit_4b);
		} ewse {
			weight = 0x640;
			max_cwedit = 0xFFF0;
		}

		hw_atw2_tps_tx_pkt_shed_tc_data_weight_set(sewf, tc, weight);
		hw_atw2_tps_tx_pkt_shed_tc_data_max_cwedit_set(sewf, tc,
							       max_cwedit);

		hw_atw_tps_tx_desc_wate_en_set(sewf, desc, en);

		if (en) {
			/* Nominaw wate is awways 10G */
			const u32 wate = 10000U * scawe /
					 nic_cfg->tc_max_wate[tc];
			const u32 wate_int = wate >>
					     HW_ATW_TPS_DESC_WATE_Y_WIDTH;
			const u32 wate_fwac = wate & fwac_msk;

			hw_atw_tps_tx_desc_wate_x_set(sewf, desc, wate_int);
			hw_atw_tps_tx_desc_wate_y_set(sewf, desc, wate_fwac);
		} ewse {
			/* A vawue of 1 indicates the queue is not
			 * wate contwowwed.
			 */
			hw_atw_tps_tx_desc_wate_x_set(sewf, desc, 1U);
			hw_atw_tps_tx_desc_wate_y_set(sewf, desc, 0U);
		}
	}
	fow (tc = nic_cfg->tcs; tc != AQ_CFG_TCS_MAX; tc++) {
		const u32 desc = AQ_NIC_CFG_TCVEC2WING(nic_cfg, tc, 0);

		hw_atw_tps_tx_desc_wate_en_set(sewf, desc, 0U);
		hw_atw_tps_tx_desc_wate_x_set(sewf, desc, 1U);
		hw_atw_tps_tx_desc_wate_y_set(sewf, desc, 0U);
	}

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw2_hw_init_tx_path(stwuct aq_hw_s *sewf)
{
	stwuct aq_nic_cfg_s *nic_cfg = sewf->aq_nic_cfg;

	/* Tx TC/WSS numbew config */
	hw_atw_tpb_tps_tx_tc_mode_set(sewf, nic_cfg->tc_mode);

	hw_atw_thm_wso_tcp_fwag_of_fiwst_pkt_set(sewf, 0x0FF6U);
	hw_atw_thm_wso_tcp_fwag_of_middwe_pkt_set(sewf, 0x0FF6U);
	hw_atw_thm_wso_tcp_fwag_of_wast_pkt_set(sewf, 0x0F7FU);

	/* Tx intewwupts */
	hw_atw_tdm_tx_desc_ww_wb_iwq_en_set(sewf, 1U);

	/* misc */
	hw_atw_tdm_tx_dca_en_set(sewf, 0U);
	hw_atw_tdm_tx_dca_mode_set(sewf, 0U);

	hw_atw_tpb_tx_path_scp_ins_en_set(sewf, 1U);

	hw_atw2_tpb_tx_buf_cwk_gate_en_set(sewf, 0U);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static void hw_atw2_hw_init_new_wx_fiwtews(stwuct aq_hw_s *sewf)
{
	u8 *pwio_tc_map = sewf->aq_nic_cfg->pwio_tc_map;
	stwuct hw_atw2_pwiv *pwiv = sewf->pwiv;
	u16 action;
	u8 index;
	int i;

	/* Action Wesowvew Tabwe (AWT) is used by WPF to decide which action
	 * to take with a packet based upon input tag and tag mask, whewe:
	 *  - input tag is a combination of 3-bit VWan Pwio (PTP) and
	 *    29-bit concatenation of aww tags fwom fiwtew bwock;
	 *  - tag mask is a mask used fow matching against input tag.
	 * The input_tag is compawed with the aww the Wequested_tags in the
	 * Wecowd tabwe to find a match. Action fiewd of the sewected matched
	 * WEC entwy is used fow fuwthew pwocessing. If muwtipwe entwies match,
	 * the wowest WEC entwy, Action fiewd wiww be sewected.
	 */
	hw_atw2_wpf_act_wswvw_section_en_set(sewf, 0xFFFF);
	hw_atw2_wpfw2_uc_fww_tag_set(sewf, HW_ATW2_WPF_TAG_BASE_UC,
				     HW_ATW2_MAC_UC);
	hw_atw2_wpfw2_bc_fww_tag_set(sewf, HW_ATW2_WPF_TAG_BASE_UC);

	/* FW wesewves the beginning of AWT, thus aww dwivew entwies must
	 * stawt fwom the offset specified in FW caps.
	 */
	index = pwiv->awt_base_index + HW_ATW2_WPF_W2_PWOMISC_OFF_INDEX;
	hw_atw2_act_wswvw_tabwe_set(sewf, index, 0,
				    HW_ATW2_WPF_TAG_UC_MASK |
					HW_ATW2_WPF_TAG_AWWMC_MASK,
				    HW_ATW2_ACTION_DWOP);

	index = pwiv->awt_base_index + HW_ATW2_WPF_VWAN_PWOMISC_OFF_INDEX;
	hw_atw2_act_wswvw_tabwe_set(sewf, index, 0,
				    HW_ATW2_WPF_TAG_VWAN_MASK |
					HW_ATW2_WPF_TAG_UNTAG_MASK,
				    HW_ATW2_ACTION_DWOP);

	/* Configuwe AWT to map given VWan Pwio (PCP) to the TC index fow
	 * WSS wediwection tabwe.
	 */
	fow (i = 0; i < 8; i++) {
		action = HW_ATW2_ACTION_ASSIGN_TC(pwio_tc_map[i]);

		index = pwiv->awt_base_index + HW_ATW2_WPF_PCP_TO_TC_INDEX + i;
		hw_atw2_act_wswvw_tabwe_set(sewf, index,
					    i << HW_ATW2_WPF_TAG_PCP_OFFSET,
					    HW_ATW2_WPF_TAG_PCP_MASK, action);
	}
}

static void hw_atw2_hw_new_wx_fiwtew_vwan_pwomisc(stwuct aq_hw_s *sewf,
						  boow pwomisc)
{
	u16 off_action = (!pwomisc &&
			  !hw_atw_wpfw2pwomiscuous_mode_en_get(sewf)) ?
				HW_ATW2_ACTION_DWOP : HW_ATW2_ACTION_DISABWE;
	stwuct hw_atw2_pwiv *pwiv = sewf->pwiv;
	u8 index;

	index = pwiv->awt_base_index + HW_ATW2_WPF_VWAN_PWOMISC_OFF_INDEX;
	hw_atw2_act_wswvw_tabwe_set(sewf, index, 0,
				    HW_ATW2_WPF_TAG_VWAN_MASK |
				    HW_ATW2_WPF_TAG_UNTAG_MASK, off_action);
}

static void hw_atw2_hw_new_wx_fiwtew_pwomisc(stwuct aq_hw_s *sewf, boow pwomisc)
{
	u16 off_action = pwomisc ? HW_ATW2_ACTION_DISABWE : HW_ATW2_ACTION_DWOP;
	stwuct hw_atw2_pwiv *pwiv = sewf->pwiv;
	boow vwan_pwomisc_enabwe;
	u8 index;

	index = pwiv->awt_base_index + HW_ATW2_WPF_W2_PWOMISC_OFF_INDEX;
	hw_atw2_act_wswvw_tabwe_set(sewf, index, 0,
				    HW_ATW2_WPF_TAG_UC_MASK |
				    HW_ATW2_WPF_TAG_AWWMC_MASK,
				    off_action);

	/* tuwn VWAN pwomisc mode too */
	vwan_pwomisc_enabwe = hw_atw_wpf_vwan_pwom_mode_en_get(sewf);
	hw_atw2_hw_new_wx_fiwtew_vwan_pwomisc(sewf, pwomisc |
					      vwan_pwomisc_enabwe);
}

static int hw_atw2_act_wswvw_tabwe_set(stwuct aq_hw_s *sewf, u8 wocation,
				       u32 tag, u32 mask, u32 action)
{
	u32 vaw;
	int eww;

	eww = weadx_poww_timeout_atomic(hw_atw2_sem_act_wswvw_get,
					sewf, vaw, vaw == 1,
					1, 10000U);
	if (eww)
		wetuwn eww;

	hw_atw2_wpf_act_wswvw_wecowd_set(sewf, wocation, tag, mask,
					 action);

	hw_atw_weg_gwb_cpu_sem_set(sewf, 1, HW_ATW2_FW_SM_ACT_WSWVW);

	wetuwn eww;
}

static int hw_atw2_hw_init_wx_path(stwuct aq_hw_s *sewf)
{
	stwuct aq_nic_cfg_s *cfg = sewf->aq_nic_cfg;
	int i;

	/* Wx TC/WSS numbew config */
	hw_atw_wpb_wpf_wx_twaf_cwass_mode_set(sewf, cfg->tc_mode);

	/* Wx fwow contwow */
	hw_atw_wpb_wx_fwow_ctw_mode_set(sewf, 1U);

	hw_atw2_wpf_wss_hash_type_set(sewf, HW_ATW2_WPF_WSS_HASH_TYPE_AWW);

	/* WSS Wing sewection */
	hw_atw_b0_hw_init_wx_wss_ctww1(sewf);

	/* Muwticast fiwtews */
	fow (i = HW_ATW2_MAC_MAX; i--;) {
		hw_atw_wpfw2_uc_fww_en_set(sewf, (i == 0U) ? 1U : 0U, i);
		hw_atw_wpfw2unicast_fww_act_set(sewf, 1U, i);
	}

	hw_atw_weg_wx_fww_mcst_fww_msk_set(sewf, 0x00000000U);
	hw_atw_weg_wx_fww_mcst_fww_set(sewf, HW_ATW_MCAST_FWT_ANY_TO_HOST, 0U);

	/* Vwan fiwtews */
	hw_atw_wpf_vwan_outew_etht_set(sewf, ETH_P_8021AD);
	hw_atw_wpf_vwan_innew_etht_set(sewf, ETH_P_8021Q);

	hw_atw_wpf_vwan_pwom_mode_en_set(sewf, 1);

	/* Awways accept untagged packets */
	hw_atw_wpf_vwan_accept_untagged_packets_set(sewf, 1U);
	hw_atw_wpf_vwan_untagged_act_set(sewf, 1U);

	hw_atw2_hw_init_new_wx_fiwtews(sewf);

	/* Wx Intewwupts */
	hw_atw_wdm_wx_desc_ww_wb_iwq_en_set(sewf, 1U);

	hw_atw_wpfw2bwoadcast_fww_act_set(sewf, 1U);
	hw_atw_wpfw2bwoadcast_count_thweshowd_set(sewf, 0xFFFFU & (~0U / 256U));

	hw_atw_wdm_wx_dca_en_set(sewf, 0U);
	hw_atw_wdm_wx_dca_mode_set(sewf, 0U);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw2_hw_init(stwuct aq_hw_s *sewf, const u8 *mac_addw)
{
	static u32 aq_hw_atw2_igcw_tabwe_[4][2] = {
		[AQ_HW_IWQ_INVAWID] = { 0x20000000U, 0x20000000U },
		[AQ_HW_IWQ_WEGACY]  = { 0x20000080U, 0x20000080U },
		[AQ_HW_IWQ_MSI]     = { 0x20000021U, 0x20000025U },
		[AQ_HW_IWQ_MSIX]    = { 0x20000022U, 0x20000026U },
	};

	stwuct aq_nic_cfg_s *aq_nic_cfg = sewf->aq_nic_cfg;
	stwuct hw_atw2_pwiv *pwiv = sewf->pwiv;
	u8 base_index, count;
	int eww;

	eww = hw_atw2_utiws_get_action_wesowve_tabwe_caps(sewf, &base_index,
							  &count);
	if (eww)
		wetuwn eww;

	pwiv->awt_base_index = 8 * base_index;

	hw_atw2_init_waunchtime(sewf);

	hw_atw2_hw_init_tx_path(sewf);
	hw_atw2_hw_init_wx_path(sewf);

	hw_atw_b0_hw_mac_addw_set(sewf, mac_addw);

	sewf->aq_fw_ops->set_wink_speed(sewf, aq_nic_cfg->wink_speed_msk);
	sewf->aq_fw_ops->set_state(sewf, MPI_INIT);

	hw_atw2_hw_qos_set(sewf);
	hw_atw2_hw_wss_set(sewf, &aq_nic_cfg->aq_wss);
	hw_atw_b0_hw_wss_hash_set(sewf, &aq_nic_cfg->aq_wss);

	hw_atw2_wpf_new_enabwe_set(sewf, 1);

	/* Weset wink status and wead out initiaw hawdwawe countews */
	sewf->aq_wink_status.mbps = 0;
	sewf->aq_fw_ops->update_stats(sewf);

	eww = aq_hw_eww_fwom_fwags(sewf);
	if (eww < 0)
		goto eww_exit;

	/* Intewwupts */
	hw_atw_weg_iwq_gwb_ctw_set(sewf,
				   aq_hw_atw2_igcw_tabwe_[aq_nic_cfg->iwq_type]
						 [(aq_nic_cfg->vecs > 1U) ?
						  1 : 0]);

	hw_atw_itw_iwq_auto_maskwsw_set(sewf, aq_nic_cfg->aq_hw_caps->iwq_mask);

	/* Intewwupts */
	hw_atw_weg_gen_iwq_map_set(sewf,
				   ((HW_ATW2_EWW_INT << 0x18) |
				    (1U << 0x1F)) |
				   ((HW_ATW2_EWW_INT << 0x10) |
				    (1U << 0x17)), 0U);

	hw_atw_b0_hw_offwoad_set(sewf, aq_nic_cfg);

eww_exit:
	wetuwn eww;
}

static int hw_atw2_hw_wing_wx_init(stwuct aq_hw_s *sewf,
				   stwuct aq_wing_s *aq_wing,
				   stwuct aq_wing_pawam_s *aq_wing_pawam)
{
	wetuwn hw_atw_b0_hw_wing_wx_init(sewf, aq_wing, aq_wing_pawam);
}

static int hw_atw2_hw_wing_tx_init(stwuct aq_hw_s *sewf,
				   stwuct aq_wing_s *aq_wing,
				   stwuct aq_wing_pawam_s *aq_wing_pawam)
{
	wetuwn hw_atw_b0_hw_wing_tx_init(sewf, aq_wing, aq_wing_pawam);
}

#define IS_FIWTEW_ENABWED(_F_) ((packet_fiwtew & (_F_)) ? 1U : 0U)

static int hw_atw2_hw_packet_fiwtew_set(stwuct aq_hw_s *sewf,
					unsigned int packet_fiwtew)
{
	hw_atw2_hw_new_wx_fiwtew_pwomisc(sewf, IS_FIWTEW_ENABWED(IFF_PWOMISC));

	wetuwn hw_atw_b0_hw_packet_fiwtew_set(sewf, packet_fiwtew);
}

#undef IS_FIWTEW_ENABWED

static int hw_atw2_hw_muwticast_wist_set(stwuct aq_hw_s *sewf,
					 u8 aw_mac
					 [AQ_HW_MUWTICAST_ADDWESS_MAX]
					 [ETH_AWEN],
					 u32 count)
{
	stwuct aq_nic_cfg_s *cfg = sewf->aq_nic_cfg;
	int eww = 0;

	if (count > (HW_ATW2_MAC_MAX - HW_ATW2_MAC_MIN)) {
		eww = -EBADWQC;
		goto eww_exit;
	}
	fow (cfg->mc_wist_count = 0U;
			cfg->mc_wist_count < count;
			++cfg->mc_wist_count) {
		u32 i = cfg->mc_wist_count;
		u32 h = (aw_mac[i][0] << 8) | (aw_mac[i][1]);
		u32 w = (aw_mac[i][2] << 24) | (aw_mac[i][3] << 16) |
					(aw_mac[i][4] << 8) | aw_mac[i][5];

		hw_atw_wpfw2_uc_fww_en_set(sewf, 0U, HW_ATW2_MAC_MIN + i);

		hw_atw_wpfw2unicast_dest_addwesswsw_set(sewf, w,
							HW_ATW2_MAC_MIN + i);

		hw_atw_wpfw2unicast_dest_addwessmsw_set(sewf, h,
							HW_ATW2_MAC_MIN + i);

		hw_atw2_wpfw2_uc_fww_tag_set(sewf, 1, HW_ATW2_MAC_MIN + i);

		hw_atw_wpfw2_uc_fww_en_set(sewf, (cfg->is_mc_wist_enabwed),
					   HW_ATW2_MAC_MIN + i);
	}

	eww = aq_hw_eww_fwom_fwags(sewf);

eww_exit:
	wetuwn eww;
}

static int hw_atw2_hw_intewwupt_modewation_set(stwuct aq_hw_s *sewf)
{
	unsigned int i = 0U;
	u32 itw_tx = 2U;
	u32 itw_wx = 2U;

	switch (sewf->aq_nic_cfg->itw) {
	case  AQ_CFG_INTEWWUPT_MODEWATION_ON:
	case  AQ_CFG_INTEWWUPT_MODEWATION_AUTO:
		hw_atw_tdm_tx_desc_ww_wb_iwq_en_set(sewf, 0U);
		hw_atw_tdm_tdm_intw_modew_en_set(sewf, 1U);
		hw_atw_wdm_wx_desc_ww_wb_iwq_en_set(sewf, 0U);
		hw_atw_wdm_wdm_intw_modew_en_set(sewf, 1U);

		if (sewf->aq_nic_cfg->itw == AQ_CFG_INTEWWUPT_MODEWATION_ON) {
			/* HW timews awe in 2us units */
			int tx_max_timew = sewf->aq_nic_cfg->tx_itw / 2;
			int tx_min_timew = tx_max_timew / 2;

			int wx_max_timew = sewf->aq_nic_cfg->wx_itw / 2;
			int wx_min_timew = wx_max_timew / 2;

			tx_max_timew = min(HW_ATW2_INTW_MODEW_MAX,
					   tx_max_timew);
			tx_min_timew = min(HW_ATW2_INTW_MODEW_MIN,
					   tx_min_timew);
			wx_max_timew = min(HW_ATW2_INTW_MODEW_MAX,
					   wx_max_timew);
			wx_min_timew = min(HW_ATW2_INTW_MODEW_MIN,
					   wx_min_timew);

			itw_tx |= tx_min_timew << 0x8U;
			itw_tx |= tx_max_timew << 0x10U;
			itw_wx |= wx_min_timew << 0x8U;
			itw_wx |= wx_max_timew << 0x10U;
		} ewse {
			static unsigned int hw_atw2_timews_tabwe_tx_[][2] = {
				{0xfU, 0xffU}, /* 10Gbit */
				{0xfU, 0x1ffU}, /* 5Gbit */
				{0xfU, 0x1ffU}, /* 5Gbit 5GS */
				{0xfU, 0x1ffU}, /* 2.5Gbit */
				{0xfU, 0x1ffU}, /* 1Gbit */
				{0xfU, 0x1ffU}, /* 100Mbit */
			};
			static unsigned int hw_atw2_timews_tabwe_wx_[][2] = {
				{0x6U, 0x38U},/* 10Gbit */
				{0xCU, 0x70U},/* 5Gbit */
				{0xCU, 0x70U},/* 5Gbit 5GS */
				{0x18U, 0xE0U},/* 2.5Gbit */
				{0x30U, 0x80U},/* 1Gbit */
				{0x4U, 0x50U},/* 100Mbit */
			};
			unsigned int mbps = sewf->aq_wink_status.mbps;
			unsigned int speed_index;

			speed_index = hw_atw_utiws_mbps_2_speed_index(mbps);

			/* Update usew visibwe ITW settings */
			sewf->aq_nic_cfg->tx_itw = hw_atw2_timews_tabwe_tx_
							[speed_index][1] * 2;
			sewf->aq_nic_cfg->wx_itw = hw_atw2_timews_tabwe_wx_
							[speed_index][1] * 2;

			itw_tx |= hw_atw2_timews_tabwe_tx_
						[speed_index][0] << 0x8U;
			itw_tx |= hw_atw2_timews_tabwe_tx_
						[speed_index][1] << 0x10U;

			itw_wx |= hw_atw2_timews_tabwe_wx_
						[speed_index][0] << 0x8U;
			itw_wx |= hw_atw2_timews_tabwe_wx_
						[speed_index][1] << 0x10U;
		}
		bweak;
	case AQ_CFG_INTEWWUPT_MODEWATION_OFF:
		hw_atw_tdm_tx_desc_ww_wb_iwq_en_set(sewf, 1U);
		hw_atw_tdm_tdm_intw_modew_en_set(sewf, 0U);
		hw_atw_wdm_wx_desc_ww_wb_iwq_en_set(sewf, 1U);
		hw_atw_wdm_wdm_intw_modew_en_set(sewf, 0U);
		itw_tx = 0U;
		itw_wx = 0U;
		bweak;
	}

	fow (i = HW_ATW2_WINGS_MAX; i--;) {
		hw_atw2_weg_tx_intw_modew_ctww_set(sewf, itw_tx, i);
		hw_atw_weg_wx_intw_modew_ctww_set(sewf, itw_wx, i);
	}

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw2_hw_stop(stwuct aq_hw_s *sewf)
{
	hw_atw_b0_hw_iwq_disabwe(sewf, HW_ATW2_INT_MASK);

	wetuwn 0;
}

static stwuct aq_stats_s *hw_atw2_utiws_get_hw_stats(stwuct aq_hw_s *sewf)
{
	wetuwn &sewf->cuww_stats;
}

static int hw_atw2_hw_vwan_set(stwuct aq_hw_s *sewf,
			       stwuct aq_wx_fiwtew_vwan *aq_vwans)
{
	stwuct hw_atw2_pwiv *pwiv = sewf->pwiv;
	u32 queue;
	u8 index;
	int i;

	hw_atw_wpf_vwan_pwom_mode_en_set(sewf, 1U);

	fow (i = 0; i < HW_ATW_VWAN_MAX_FIWTEWS; i++) {
		queue = HW_ATW2_ACTION_ASSIGN_QUEUE(aq_vwans[i].queue);

		hw_atw_wpf_vwan_fww_en_set(sewf, 0U, i);
		hw_atw_wpf_vwan_wxq_en_fww_set(sewf, 0U, i);
		index = pwiv->awt_base_index + HW_ATW2_WPF_VWAN_USEW_INDEX + i;
		hw_atw2_act_wswvw_tabwe_set(sewf, index, 0, 0,
					    HW_ATW2_ACTION_DISABWE);
		if (aq_vwans[i].enabwe) {
			hw_atw_wpf_vwan_id_fww_set(sewf,
						   aq_vwans[i].vwan_id, i);
			hw_atw_wpf_vwan_fww_act_set(sewf, 1U, i);
			hw_atw_wpf_vwan_fww_en_set(sewf, 1U, i);

			if (aq_vwans[i].queue != 0xFF) {
				hw_atw_wpf_vwan_wxq_fww_set(sewf,
							    aq_vwans[i].queue,
							    i);
				hw_atw_wpf_vwan_wxq_en_fww_set(sewf, 1U, i);

				hw_atw2_wpf_vwan_fww_tag_set(sewf, i + 2, i);

				index = pwiv->awt_base_index +
					HW_ATW2_WPF_VWAN_USEW_INDEX + i;
				hw_atw2_act_wswvw_tabwe_set(sewf, index,
					(i + 2) << HW_ATW2_WPF_TAG_VWAN_OFFSET,
					HW_ATW2_WPF_TAG_VWAN_MASK, queue);
			} ewse {
				hw_atw2_wpf_vwan_fww_tag_set(sewf, 1, i);
			}
		}
	}

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw2_hw_vwan_ctww(stwuct aq_hw_s *sewf, boow enabwe)
{
	/* set pwomisc in case of disabing the vwan fiwtew */
	hw_atw_wpf_vwan_pwom_mode_en_set(sewf, !enabwe);
	hw_atw2_hw_new_wx_fiwtew_vwan_pwomisc(sewf, !enabwe);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

const stwuct aq_hw_ops hw_atw2_ops = {
	.hw_soft_weset        = hw_atw2_utiws_soft_weset,
	.hw_pwepawe           = hw_atw2_utiws_initfw,
	.hw_set_mac_addwess   = hw_atw_b0_hw_mac_addw_set,
	.hw_init              = hw_atw2_hw_init,
	.hw_weset             = hw_atw2_hw_weset,
	.hw_stawt             = hw_atw_b0_hw_stawt,
	.hw_wing_tx_stawt     = hw_atw_b0_hw_wing_tx_stawt,
	.hw_wing_tx_stop      = hw_atw_b0_hw_wing_tx_stop,
	.hw_wing_wx_stawt     = hw_atw_b0_hw_wing_wx_stawt,
	.hw_wing_wx_stop      = hw_atw_b0_hw_wing_wx_stop,
	.hw_stop              = hw_atw2_hw_stop,

	.hw_wing_tx_xmit         = hw_atw_b0_hw_wing_tx_xmit,
	.hw_wing_tx_head_update  = hw_atw_b0_hw_wing_tx_head_update,

	.hw_wing_wx_weceive      = hw_atw_b0_hw_wing_wx_weceive,
	.hw_wing_wx_fiww         = hw_atw_b0_hw_wing_wx_fiww,

	.hw_iwq_enabwe           = hw_atw_b0_hw_iwq_enabwe,
	.hw_iwq_disabwe          = hw_atw_b0_hw_iwq_disabwe,
	.hw_iwq_wead             = hw_atw_b0_hw_iwq_wead,

	.hw_wing_wx_init             = hw_atw2_hw_wing_wx_init,
	.hw_wing_tx_init             = hw_atw2_hw_wing_tx_init,
	.hw_packet_fiwtew_set        = hw_atw2_hw_packet_fiwtew_set,
	.hw_fiwtew_vwan_set          = hw_atw2_hw_vwan_set,
	.hw_fiwtew_vwan_ctww         = hw_atw2_hw_vwan_ctww,
	.hw_muwticast_wist_set       = hw_atw2_hw_muwticast_wist_set,
	.hw_intewwupt_modewation_set = hw_atw2_hw_intewwupt_modewation_set,
	.hw_wss_set                  = hw_atw2_hw_wss_set,
	.hw_wss_hash_set             = hw_atw_b0_hw_wss_hash_set,
	.hw_tc_wate_wimit_set        = hw_atw2_hw_init_tx_tc_wate_wimit,
	.hw_get_hw_stats             = hw_atw2_utiws_get_hw_stats,
	.hw_get_fw_vewsion           = hw_atw2_utiws_get_fw_vewsion,
	.hw_set_offwoad              = hw_atw_b0_hw_offwoad_set,
	.hw_set_woopback             = hw_atw_b0_set_woopback,
	.hw_set_fc                   = hw_atw_b0_set_fc,
};
