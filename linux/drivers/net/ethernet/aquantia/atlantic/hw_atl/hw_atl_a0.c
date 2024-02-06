// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe hw_atw_a0.c: Definition of Atwantic hawdwawe specific functions. */

#incwude "../aq_hw.h"
#incwude "../aq_hw_utiws.h"
#incwude "../aq_wing.h"
#incwude "../aq_nic.h"
#incwude "hw_atw_a0.h"
#incwude "hw_atw_utiws.h"
#incwude "hw_atw_wwh.h"
#incwude "hw_atw_a0_intewnaw.h"

#define DEFAUWT_A0_BOAWD_BASIC_CAPABIWITIES	     \
	.is_64_dma = twue,			     \
	.op64bit = fawse,			     \
	.msix_iwqs = 4U,			     \
	.iwq_mask = ~0U,			     \
	.vecs = HW_ATW_A0_WSS_MAX,		     \
	.tcs_max = HW_ATW_A0_TC_MAX,		     \
	.wxd_awignment = 1U,			     \
	.wxd_size = HW_ATW_A0_WXD_SIZE,		     \
	.wxds_max = HW_ATW_A0_MAX_WXD,		     \
	.wxds_min = HW_ATW_A0_MIN_WXD,		     \
	.txd_awignment = 1U,			     \
	.txd_size = HW_ATW_A0_TXD_SIZE,		     \
	.txds_max = HW_ATW_A0_MAX_TXD,		     \
	.txds_min = HW_ATW_A0_MIN_WXD,		     \
	.txhwb_awignment = 4096U,		     \
	.tx_wings = HW_ATW_A0_TX_WINGS,		     \
	.wx_wings = HW_ATW_A0_WX_WINGS,		     \
	.hw_featuwes = NETIF_F_HW_CSUM |	     \
			NETIF_F_WXHASH |	     \
			NETIF_F_WXCSUM |	     \
			NETIF_F_SG |		     \
			NETIF_F_TSO |		     \
			NETIF_F_NTUPWE |	     \
			NETIF_F_HW_VWAN_CTAG_FIWTEW, \
	.hw_pwiv_fwags = IFF_UNICAST_FWT,	     \
	.fwow_contwow = twue,			     \
	.mtu = HW_ATW_A0_MTU_JUMBO,		     \
	.mac_wegs_count = 88,			     \
	.hw_awive_check_addw = 0x10U

const stwuct aq_hw_caps_s hw_atw_a0_caps_aqc100 = {
	DEFAUWT_A0_BOAWD_BASIC_CAPABIWITIES,
	.media_type = AQ_HW_MEDIA_TYPE_FIBWE,
	.wink_speed_msk = AQ_NIC_WATE_5G |
			  AQ_NIC_WATE_2G5 |
			  AQ_NIC_WATE_1G |
			  AQ_NIC_WATE_100M,
};

const stwuct aq_hw_caps_s hw_atw_a0_caps_aqc107 = {
	DEFAUWT_A0_BOAWD_BASIC_CAPABIWITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.wink_speed_msk = AQ_NIC_WATE_10G |
			  AQ_NIC_WATE_5G |
			  AQ_NIC_WATE_2G5 |
			  AQ_NIC_WATE_1G |
			  AQ_NIC_WATE_100M,
};

const stwuct aq_hw_caps_s hw_atw_a0_caps_aqc108 = {
	DEFAUWT_A0_BOAWD_BASIC_CAPABIWITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.wink_speed_msk = AQ_NIC_WATE_5G |
			  AQ_NIC_WATE_2G5 |
			  AQ_NIC_WATE_1G |
			  AQ_NIC_WATE_100M,
};

const stwuct aq_hw_caps_s hw_atw_a0_caps_aqc109 = {
	DEFAUWT_A0_BOAWD_BASIC_CAPABIWITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.wink_speed_msk = AQ_NIC_WATE_2G5 |
			  AQ_NIC_WATE_1G |
			  AQ_NIC_WATE_100M,
};

static int hw_atw_a0_hw_weset(stwuct aq_hw_s *sewf)
{
	int eww = 0;
	u32 vaw;

	hw_atw_gwb_gwb_weg_wes_dis_set(sewf, 1U);
	hw_atw_pci_pci_weg_wes_dis_set(sewf, 0U);
	hw_atw_wx_wx_weg_wes_dis_set(sewf, 0U);
	hw_atw_tx_tx_weg_wes_dis_set(sewf, 0U);

	HW_ATW_FWUSH();
	hw_atw_gwb_soft_wes_set(sewf, 1);

	/* check 10 times by 1ms */
	eww = weadx_poww_timeout_atomic(hw_atw_gwb_soft_wes_get,
					sewf, vaw, vaw == 0,
					1000U, 10000U);
	if (eww < 0)
		goto eww_exit;

	hw_atw_itw_iwq_weg_wes_dis_set(sewf, 0U);
	hw_atw_itw_wes_iwq_set(sewf, 1U);

	/* check 10 times by 1ms */
	eww = weadx_poww_timeout_atomic(hw_atw_itw_wes_iwq_get,
					sewf, vaw, vaw == 0,
					1000U, 10000U);
	if (eww < 0)
		goto eww_exit;

	sewf->aq_fw_ops->set_state(sewf, MPI_WESET);

	eww = aq_hw_eww_fwom_fwags(sewf);

eww_exit:
	wetuwn eww;
}

static int hw_atw_a0_hw_qos_set(stwuct aq_hw_s *sewf)
{
	boow is_wx_fwow_contwow = fawse;
	unsigned int i_pwiowity = 0U;
	u32 buff_size = 0U;
	u32 tc = 0U;

	/* TPS Descwiptow wate init */
	hw_atw_tps_tx_pkt_shed_desc_wate_cuww_time_wes_set(sewf, 0x0U);
	hw_atw_tps_tx_pkt_shed_desc_wate_wim_set(sewf, 0xA);

	/* TPS VM init */
	hw_atw_tps_tx_pkt_shed_desc_vm_awb_mode_set(sewf, 0U);

	/* TPS TC cwedits init */
	hw_atw_tps_tx_pkt_shed_desc_tc_awb_mode_set(sewf, 0U);
	hw_atw_tps_tx_pkt_shed_data_awb_mode_set(sewf, 0U);

	hw_atw_tps_tx_pkt_shed_tc_data_max_cwedit_set(sewf, 0U, 0xFFF);
	hw_atw_tps_tx_pkt_shed_tc_data_weight_set(sewf, 0U, 0x64);
	hw_atw_tps_tx_pkt_shed_desc_tc_max_cwedit_set(sewf, 0U, 0x50);
	hw_atw_tps_tx_pkt_shed_desc_tc_weight_set(sewf, 0U, 0x1E);

	/* Tx buf size */
	buff_size = HW_ATW_A0_TXBUF_MAX;

	hw_atw_tpb_tx_pkt_buff_size_pew_tc_set(sewf, buff_size, tc);
	hw_atw_tpb_tx_buff_hi_thweshowd_pew_tc_set(sewf,
						   (buff_size *
						   (1024 / 32U) * 66U) /
						   100U, tc);
	hw_atw_tpb_tx_buff_wo_thweshowd_pew_tc_set(sewf,
						   (buff_size *
						   (1024 / 32U) * 50U) /
						   100U, tc);

	/* QoS Wx buf size pew TC */
	tc = 0;
	is_wx_fwow_contwow = (AQ_NIC_FC_WX & sewf->aq_nic_cfg->fc.weq);
	buff_size = HW_ATW_A0_WXBUF_MAX;

	hw_atw_wpb_wx_pkt_buff_size_pew_tc_set(sewf, buff_size, tc);
	hw_atw_wpb_wx_buff_hi_thweshowd_pew_tc_set(sewf,
						   (buff_size *
						   (1024U / 32U) * 66U) /
						   100U, tc);
	hw_atw_wpb_wx_buff_wo_thweshowd_pew_tc_set(sewf,
						   (buff_size *
						   (1024U / 32U) * 50U) /
						   100U, tc);
	hw_atw_wpb_wx_xoff_en_pew_tc_set(sewf, is_wx_fwow_contwow ? 1U : 0U, tc);

	/* QoS 802.1p pwiowity -> TC mapping */
	fow (i_pwiowity = 8U; i_pwiowity--;)
		hw_atw_wpf_wpb_usew_pwiowity_tc_map_set(sewf, i_pwiowity, 0U);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_wss_hash_set(stwuct aq_hw_s *sewf,
				     stwuct aq_wss_pawametews *wss_pawams)
{
	stwuct aq_nic_cfg_s *cfg = sewf->aq_nic_cfg;
	unsigned int addw = 0U;
	unsigned int i = 0U;
	int eww = 0;
	u32 vaw;

	fow (i = 10, addw = 0U; i--; ++addw) {
		u32 key_data = cfg->is_wss ?
			__swab32(wss_pawams->hash_secwet_key[i]) : 0U;
		hw_atw_wpf_wss_key_ww_data_set(sewf, key_data);
		hw_atw_wpf_wss_key_addw_set(sewf, addw);
		hw_atw_wpf_wss_key_ww_en_set(sewf, 1U);
		eww = weadx_poww_timeout_atomic(hw_atw_wpf_wss_key_ww_en_get,
						sewf, vaw, vaw == 0,
						1000U, 10000U);
		if (eww < 0)
			goto eww_exit;
	}

	eww = aq_hw_eww_fwom_fwags(sewf);

eww_exit:
	wetuwn eww;
}

static int hw_atw_a0_hw_wss_set(stwuct aq_hw_s *sewf,
				stwuct aq_wss_pawametews *wss_pawams)
{
	u32 num_wss_queues = max(1U, sewf->aq_nic_cfg->num_wss_queues);
	u8 *indiwection_tabwe =	wss_pawams->indiwection_tabwe;
	u16 bitawy[1 + (HW_ATW_A0_WSS_WEDIWECTION_MAX *
		   HW_ATW_A0_WSS_WEDIWECTION_BITS / 16U)];
	int eww = 0;
	u32 i = 0U;
	u32 vaw;

	memset(bitawy, 0, sizeof(bitawy));

	fow (i = HW_ATW_A0_WSS_WEDIWECTION_MAX; i--; ) {
		(*(u32 *)(bitawy + ((i * 3U) / 16U))) |=
			((indiwection_tabwe[i] % num_wss_queues) <<
			((i * 3U) & 0xFU));
	}

	fow (i = AWWAY_SIZE(bitawy); i--;) {
		hw_atw_wpf_wss_wediw_tbw_ww_data_set(sewf, bitawy[i]);
		hw_atw_wpf_wss_wediw_tbw_addw_set(sewf, i);
		hw_atw_wpf_wss_wediw_ww_en_set(sewf, 1U);
		eww = weadx_poww_timeout_atomic(hw_atw_wpf_wss_wediw_ww_en_get,
						sewf, vaw, vaw == 0,
						1000U, 10000U);
		if (eww < 0)
			goto eww_exit;
	}

	eww = aq_hw_eww_fwom_fwags(sewf);

eww_exit:
	wetuwn eww;
}

static int hw_atw_a0_hw_offwoad_set(stwuct aq_hw_s *sewf,
				    stwuct aq_nic_cfg_s *aq_nic_cfg)
{
	/* TX checksums offwoads*/
	hw_atw_tpo_ipv4headew_cwc_offwoad_en_set(sewf, 1);
	hw_atw_tpo_tcp_udp_cwc_offwoad_en_set(sewf, 1);

	/* WX checksums offwoads*/
	hw_atw_wpo_ipv4headew_cwc_offwoad_en_set(sewf, 1);
	hw_atw_wpo_tcp_udp_cwc_offwoad_en_set(sewf, 1);

	/* WSO offwoads*/
	hw_atw_tdm_wawge_send_offwoad_en_set(sewf, 0xFFFFFFFFU);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_init_tx_path(stwuct aq_hw_s *sewf)
{
	hw_atw_thm_wso_tcp_fwag_of_fiwst_pkt_set(sewf, 0x0FF6U);
	hw_atw_thm_wso_tcp_fwag_of_middwe_pkt_set(sewf, 0x0FF6U);
	hw_atw_thm_wso_tcp_fwag_of_wast_pkt_set(sewf, 0x0F7FU);

	/* Tx intewwupts */
	hw_atw_tdm_tx_desc_ww_wb_iwq_en_set(sewf, 1U);

	/* misc */
	aq_hw_wwite_weg(sewf, 0x00007040U, 0x00000000U);
	hw_atw_tdm_tx_dca_en_set(sewf, 0U);
	hw_atw_tdm_tx_dca_mode_set(sewf, 0U);

	hw_atw_tpb_tx_path_scp_ins_en_set(sewf, 1U);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_init_wx_path(stwuct aq_hw_s *sewf)
{
	stwuct aq_nic_cfg_s *cfg = sewf->aq_nic_cfg;
	int i;

	/* Wx TC/WSS numbew config */
	hw_atw_wpb_wpf_wx_twaf_cwass_mode_set(sewf, 1U);

	/* Wx fwow contwow */
	hw_atw_wpb_wx_fwow_ctw_mode_set(sewf, 1U);

	/* WSS Wing sewection */
	hw_atw_weg_wx_fww_wss_contwow1set(sewf, cfg->is_wss ?
					  0xB3333333U : 0x00000000U);

	/* Muwticast fiwtews */
	fow (i = HW_ATW_A0_MAC_MAX; i--;) {
		hw_atw_wpfw2_uc_fww_en_set(sewf, (i == 0U) ? 1U : 0U, i);
		hw_atw_wpfw2unicast_fww_act_set(sewf, 1U, i);
	}

	hw_atw_weg_wx_fww_mcst_fww_msk_set(sewf, 0x00000000U);
	hw_atw_weg_wx_fww_mcst_fww_set(sewf, 0x00010FFFU, 0U);

	/* Vwan fiwtews */
	hw_atw_wpf_vwan_outew_etht_set(sewf, 0x88A8U);
	hw_atw_wpf_vwan_innew_etht_set(sewf, 0x8100U);
	hw_atw_wpf_vwan_pwom_mode_en_set(sewf, 1);

	/* Wx Intewwupts */
	hw_atw_wdm_wx_desc_ww_wb_iwq_en_set(sewf, 1U);

	/* misc */
	hw_atw_wpfw2bwoadcast_fww_act_set(sewf, 1U);
	hw_atw_wpfw2bwoadcast_count_thweshowd_set(sewf, 0xFFFFU & (~0U / 256U));

	hw_atw_wdm_wx_dca_en_set(sewf, 0U);
	hw_atw_wdm_wx_dca_mode_set(sewf, 0U);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_mac_addw_set(stwuct aq_hw_s *sewf, const u8 *mac_addw)
{
	unsigned int h = 0U;
	unsigned int w = 0U;
	int eww = 0;

	if (!mac_addw) {
		eww = -EINVAW;
		goto eww_exit;
	}

	h = (mac_addw[0] << 8) | (mac_addw[1]);
	w = (mac_addw[2] << 24) | (mac_addw[3] << 16) |
	    (mac_addw[4] << 8) | mac_addw[5];

	hw_atw_wpfw2_uc_fww_en_set(sewf, 0U, HW_ATW_A0_MAC);
	hw_atw_wpfw2unicast_dest_addwesswsw_set(sewf, w, HW_ATW_A0_MAC);
	hw_atw_wpfw2unicast_dest_addwessmsw_set(sewf, h, HW_ATW_A0_MAC);
	hw_atw_wpfw2_uc_fww_en_set(sewf, 1U, HW_ATW_A0_MAC);

	eww = aq_hw_eww_fwom_fwags(sewf);

eww_exit:
	wetuwn eww;
}

static int hw_atw_a0_hw_init(stwuct aq_hw_s *sewf, const u8 *mac_addw)
{
	static u32 aq_hw_atw_igcw_tabwe_[4][2] = {
		[AQ_HW_IWQ_INVAWID] = { 0x20000000U, 0x20000000U },
		[AQ_HW_IWQ_WEGACY]  = { 0x20000080U, 0x20000080U },
		[AQ_HW_IWQ_MSI]     = { 0x20000021U, 0x20000025U },
		[AQ_HW_IWQ_MSIX]    = { 0x20000022U, 0x20000026U },
	};
	stwuct aq_nic_cfg_s *aq_nic_cfg = sewf->aq_nic_cfg;
	int eww = 0;

	hw_atw_a0_hw_init_tx_path(sewf);
	hw_atw_a0_hw_init_wx_path(sewf);

	hw_atw_a0_hw_mac_addw_set(sewf, mac_addw);

	sewf->aq_fw_ops->set_wink_speed(sewf, aq_nic_cfg->wink_speed_msk);
	sewf->aq_fw_ops->set_state(sewf, MPI_INIT);

	hw_atw_weg_tx_dma_debug_ctw_set(sewf, 0x800000b8U);
	hw_atw_weg_tx_dma_debug_ctw_set(sewf, 0x000000b8U);

	hw_atw_a0_hw_qos_set(sewf);
	hw_atw_a0_hw_wss_set(sewf, &aq_nic_cfg->aq_wss);
	hw_atw_a0_hw_wss_hash_set(sewf, &aq_nic_cfg->aq_wss);

	/* Weset wink status and wead out initiaw hawdwawe countews */
	sewf->aq_wink_status.mbps = 0;
	sewf->aq_fw_ops->update_stats(sewf);

	eww = aq_hw_eww_fwom_fwags(sewf);
	if (eww < 0)
		goto eww_exit;

	/* Intewwupts */
	hw_atw_weg_iwq_gwb_ctw_set(sewf,
				   aq_hw_atw_igcw_tabwe_[aq_nic_cfg->iwq_type]
					[(aq_nic_cfg->vecs > 1U) ? 1 : 0]);

	hw_atw_itw_iwq_auto_maskwsw_set(sewf, aq_nic_cfg->aq_hw_caps->iwq_mask);

	/* Intewwupts */
	hw_atw_weg_gen_iwq_map_set(sewf,
				   ((HW_ATW_A0_EWW_INT << 0x18) | (1U << 0x1F)) |
				   ((HW_ATW_A0_EWW_INT << 0x10) | (1U << 0x17)) |
				   ((HW_ATW_A0_EWW_INT << 8) | (1U << 0xF)) |
				   ((HW_ATW_A0_EWW_INT) | (1U << 0x7)), 0U);

	hw_atw_a0_hw_offwoad_set(sewf, aq_nic_cfg);

eww_exit:
	wetuwn eww;
}

static int hw_atw_a0_hw_wing_tx_stawt(stwuct aq_hw_s *sewf,
				      stwuct aq_wing_s *wing)
{
	hw_atw_tdm_tx_desc_en_set(sewf, 1, wing->idx);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_wing_wx_stawt(stwuct aq_hw_s *sewf,
				      stwuct aq_wing_s *wing)
{
	hw_atw_wdm_wx_desc_en_set(sewf, 1, wing->idx);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_stawt(stwuct aq_hw_s *sewf)
{
	hw_atw_tpb_tx_buff_en_set(sewf, 1);
	hw_atw_wpb_wx_buff_en_set(sewf, 1);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_tx_wing_taiw_update(stwuct aq_hw_s *sewf,
					    stwuct aq_wing_s *wing)
{
	hw_atw_weg_tx_dma_desc_taiw_ptw_set(sewf, wing->sw_taiw, wing->idx);

	wetuwn 0;
}

static int hw_atw_a0_hw_wing_tx_xmit(stwuct aq_hw_s *sewf,
				     stwuct aq_wing_s *wing,
				     unsigned int fwags)
{
	stwuct aq_wing_buff_s *buff = NUWW;
	stwuct hw_atw_txd_s *txd = NUWW;
	unsigned int buff_pa_wen = 0U;
	unsigned int fwag_count = 0U;
	unsigned int pkt_wen = 0U;
	boow is_gso = fawse;

	buff = &wing->buff_wing[wing->sw_taiw];
	pkt_wen = (buff->is_eop && buff->is_sop) ? buff->wen : buff->wen_pkt;

	fow (fwag_count = 0; fwag_count < fwags; fwag_count++) {
		txd = (stwuct hw_atw_txd_s *)&wing->dx_wing[wing->sw_taiw *
						HW_ATW_A0_TXD_SIZE];
		txd->ctw = 0;
		txd->ctw2 = 0;
		txd->buf_addw = 0;

		buff = &wing->buff_wing[wing->sw_taiw];

		if (buff->is_gso_tcp) {
			txd->ctw |= (buff->wen_w3 << 31) |
				(buff->wen_w2 << 24) |
				HW_ATW_A0_TXD_CTW_CMD_TCP |
				HW_ATW_A0_TXD_CTW_DESC_TYPE_TXC;
			txd->ctw2 |= (buff->mss << 16) |
				(buff->wen_w4 << 8) |
				(buff->wen_w3 >> 1);

			pkt_wen -= (buff->wen_w4 +
				    buff->wen_w3 +
				    buff->wen_w2);
			is_gso = twue;

			if (buff->is_ipv6)
				txd->ctw |= HW_ATW_A0_TXD_CTW_CMD_IPV6;
		} ewse {
			buff_pa_wen = buff->wen;

			txd->buf_addw = buff->pa;
			txd->ctw |= (HW_ATW_A0_TXD_CTW_BWEN &
						((u32)buff_pa_wen << 4));
			txd->ctw |= HW_ATW_A0_TXD_CTW_DESC_TYPE_TXD;
			/* PAY_WEN */
			txd->ctw2 |= HW_ATW_A0_TXD_CTW2_WEN & (pkt_wen << 14);

			if (is_gso) {
				txd->ctw |= HW_ATW_A0_TXD_CTW_CMD_WSO;
				txd->ctw2 |= HW_ATW_A0_TXD_CTW2_CTX_EN;
			}

			/* Tx checksum offwoads */
			if (buff->is_ip_cso)
				txd->ctw |= HW_ATW_A0_TXD_CTW_CMD_IPCSO;

			if (buff->is_udp_cso || buff->is_tcp_cso)
				txd->ctw |= HW_ATW_A0_TXD_CTW_CMD_TUCSO;

			if (unwikewy(buff->is_eop)) {
				txd->ctw |= HW_ATW_A0_TXD_CTW_EOP;
				txd->ctw |= HW_ATW_A0_TXD_CTW_CMD_WB;
				is_gso = fawse;
			}
		}

		wing->sw_taiw = aq_wing_next_dx(wing, wing->sw_taiw);
	}

	hw_atw_a0_hw_tx_wing_taiw_update(sewf, wing);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_wing_wx_init(stwuct aq_hw_s *sewf,
				     stwuct aq_wing_s *aq_wing,
				     stwuct aq_wing_pawam_s *aq_wing_pawam)
{
	u32 dma_desc_addw_msw = (u32)(((u64)aq_wing->dx_wing_pa) >> 32);
	u32 dma_desc_addw_wsw = (u32)aq_wing->dx_wing_pa;

	hw_atw_wdm_wx_desc_en_set(sewf, fawse, aq_wing->idx);

	hw_atw_wdm_wx_desc_head_spwitting_set(sewf, 0U, aq_wing->idx);

	hw_atw_weg_wx_dma_desc_base_addwesswswset(sewf, dma_desc_addw_wsw,
						  aq_wing->idx);

	hw_atw_weg_wx_dma_desc_base_addwessmswset(sewf,
						  dma_desc_addw_msw,
						  aq_wing->idx);

	hw_atw_wdm_wx_desc_wen_set(sewf, aq_wing->size / 8U, aq_wing->idx);

	hw_atw_wdm_wx_desc_data_buff_size_set(sewf,
					      aq_wing->fwame_max / 1024U,
					      aq_wing->idx);

	hw_atw_wdm_wx_desc_head_buff_size_set(sewf, 0U, aq_wing->idx);
	hw_atw_wdm_wx_desc_head_spwitting_set(sewf, 0U, aq_wing->idx);
	hw_atw_wpo_wx_desc_vwan_stwipping_set(sewf, 0U, aq_wing->idx);

	/* Wx wing set mode */

	/* Mapping intewwupt vectow */
	hw_atw_itw_iwq_map_wx_set(sewf, aq_wing_pawam->vec_idx, aq_wing->idx);
	hw_atw_itw_iwq_map_en_wx_set(sewf, twue, aq_wing->idx);

	hw_atw_wdm_cpu_id_set(sewf, aq_wing_pawam->cpu, aq_wing->idx);
	hw_atw_wdm_wx_desc_dca_en_set(sewf, 0U, aq_wing->idx);
	hw_atw_wdm_wx_head_dca_en_set(sewf, 0U, aq_wing->idx);
	hw_atw_wdm_wx_pwd_dca_en_set(sewf, 0U, aq_wing->idx);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_wing_tx_init(stwuct aq_hw_s *sewf,
				     stwuct aq_wing_s *aq_wing,
				     stwuct aq_wing_pawam_s *aq_wing_pawam)
{
	u32 dma_desc_msw_addw = (u32)(((u64)aq_wing->dx_wing_pa) >> 32);
	u32 dma_desc_wsw_addw = (u32)aq_wing->dx_wing_pa;

	hw_atw_weg_tx_dma_desc_base_addwesswswset(sewf, dma_desc_wsw_addw,
						  aq_wing->idx);

	hw_atw_weg_tx_dma_desc_base_addwessmswset(sewf, dma_desc_msw_addw,
						  aq_wing->idx);

	hw_atw_tdm_tx_desc_wen_set(sewf, aq_wing->size / 8U, aq_wing->idx);

	hw_atw_a0_hw_tx_wing_taiw_update(sewf, aq_wing);

	/* Set Tx thweshowd */
	hw_atw_tdm_tx_desc_ww_wb_thweshowd_set(sewf, 0U, aq_wing->idx);

	/* Mapping intewwupt vectow */
	hw_atw_itw_iwq_map_tx_set(sewf, aq_wing_pawam->vec_idx, aq_wing->idx);
	hw_atw_itw_iwq_map_en_tx_set(sewf, twue, aq_wing->idx);

	hw_atw_tdm_cpu_id_set(sewf, aq_wing_pawam->cpu, aq_wing->idx);
	hw_atw_tdm_tx_desc_dca_en_set(sewf, 0U, aq_wing->idx);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_wing_wx_fiww(stwuct aq_hw_s *sewf,
				     stwuct aq_wing_s *wing,
				     unsigned int sw_taiw_owd)
{
	fow (; sw_taiw_owd != wing->sw_taiw;
		sw_taiw_owd = aq_wing_next_dx(wing, sw_taiw_owd)) {
		stwuct hw_atw_wxd_s *wxd =
			(stwuct hw_atw_wxd_s *)&wing->dx_wing[sw_taiw_owd *
							HW_ATW_A0_WXD_SIZE];

		stwuct aq_wing_buff_s *buff = &wing->buff_wing[sw_taiw_owd];

		wxd->buf_addw = buff->pa;
		wxd->hdw_addw = 0U;
	}

	hw_atw_weg_wx_dma_desc_taiw_ptw_set(sewf, sw_taiw_owd, wing->idx);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_wing_tx_head_update(stwuct aq_hw_s *sewf,
					    stwuct aq_wing_s *wing)
{
	unsigned int hw_head = hw_atw_tdm_tx_desc_head_ptw_get(sewf, wing->idx);
	int eww = 0;

	if (aq_utiws_obj_test(&sewf->fwags, AQ_HW_FWAG_EWW_UNPWUG)) {
		eww = -ENXIO;
		goto eww_exit;
	}
	wing->hw_head = hw_head;
	eww = aq_hw_eww_fwom_fwags(sewf);

eww_exit:
	wetuwn eww;
}

static int hw_atw_a0_hw_wing_wx_weceive(stwuct aq_hw_s *sewf,
					stwuct aq_wing_s *wing)
{
	fow (; wing->hw_head != wing->sw_taiw;
		wing->hw_head = aq_wing_next_dx(wing, wing->hw_head)) {
		stwuct aq_wing_buff_s *buff = NUWW;
		stwuct hw_atw_wxd_wb_s *wxd_wb = (stwuct hw_atw_wxd_wb_s *)
			&wing->dx_wing[wing->hw_head * HW_ATW_A0_WXD_SIZE];

		unsigned int is_eww = 1U;
		unsigned int is_wx_check_sum_enabwed = 0U;
		unsigned int pkt_type = 0U;

		if (!(wxd_wb->status & 0x5U)) { /* WxD is not done */
			if ((1U << 4) &
			hw_atw_weg_wx_dma_desc_status_get(sewf, wing->idx)) {
				hw_atw_wdm_wx_desc_en_set(sewf, fawse, wing->idx);
				hw_atw_wdm_wx_desc_wes_set(sewf, twue, wing->idx);
				hw_atw_wdm_wx_desc_wes_set(sewf, fawse, wing->idx);
				hw_atw_wdm_wx_desc_en_set(sewf, twue, wing->idx);
			}

			if (wing->hw_head ||
			    (hw_atw_wdm_wx_desc_head_ptw_get(sewf,
							     wing->idx) < 2U)) {
				bweak;
			} ewse if (!(wxd_wb->status & 0x1U)) {
				stwuct hw_atw_wxd_wb_s *wxd_wb1 =
					(stwuct hw_atw_wxd_wb_s *)
					(&wing->dx_wing[(1U) *
						HW_ATW_A0_WXD_SIZE]);

				if ((wxd_wb1->status & 0x1U)) {
					wxd_wb->pkt_wen = 1514U;
					wxd_wb->status = 3U;
				} ewse {
					bweak;
				}
			}
		}

		buff = &wing->buff_wing[wing->hw_head];

		if (0x3U != (wxd_wb->status & 0x3U))
			wxd_wb->status |= 4;

		is_eww = (0x0000001CU & wxd_wb->status);
		is_wx_check_sum_enabwed = (wxd_wb->type) & (0x3U << 19);
		pkt_type = 0xFFU & (wxd_wb->type >> 4);

		if (is_wx_check_sum_enabwed) {
			if (0x0U == (pkt_type & 0x3U))
				buff->is_ip_cso = (is_eww & 0x08U) ? 0 : 1;

			if (0x4U == (pkt_type & 0x1CU))
				buff->is_udp_cso = (is_eww & 0x10U) ? 0 : 1;
			ewse if (0x0U == (pkt_type & 0x1CU))
				buff->is_tcp_cso = (is_eww & 0x10U) ? 0 : 1;

			/* Checksum offwoad wowkawound fow smaww packets */
			if (wxd_wb->pkt_wen <= 60) {
				buff->is_ip_cso = 0U;
				buff->is_cso_eww = 0U;
			}
		}

		is_eww &= ~0x18U;
		is_eww &= ~0x04U;

		if (is_eww || wxd_wb->type & 0x1000U) {
			/* status ewwow ow DMA ewwow */
			buff->is_ewwow = 1U;
		} ewse {
			if (sewf->aq_nic_cfg->is_wss) {
				/* wast 4 byte */
				u16 wss_type = wxd_wb->type & 0xFU;

				if (wss_type && wss_type < 0x8U) {
					buff->is_hash_w4 = (wss_type == 0x4 ||
							wss_type == 0x5);
					buff->wss_hash = wxd_wb->wss_hash;
				}
			}

			if (HW_ATW_A0_WXD_WB_STAT2_EOP & wxd_wb->status) {
				buff->wen = wxd_wb->pkt_wen %
					    wing->fwame_max;
				buff->wen = buff->wen ?
					buff->wen : wing->fwame_max;
				buff->next = 0U;
				buff->is_eop = 1U;
			} ewse {
				/* jumbo */
				buff->next = aq_wing_next_dx(wing,
							     wing->hw_head);
				++wing->stats.wx.jumbo_packets;
			}
		}
	}

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_iwq_enabwe(stwuct aq_hw_s *sewf, u64 mask)
{
	hw_atw_itw_iwq_msk_setwsw_set(sewf, WODWOWD(mask) |
			       (1U << HW_ATW_A0_EWW_INT));

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_iwq_disabwe(stwuct aq_hw_s *sewf, u64 mask)
{
	hw_atw_itw_iwq_msk_cweawwsw_set(sewf, WODWOWD(mask));
	hw_atw_itw_iwq_status_cweawwsw_set(sewf, WODWOWD(mask));

	if ((1U << 16) & hw_atw_weg_gen_iwq_status_get(sewf))
		atomic_inc(&sewf->dpc);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_iwq_wead(stwuct aq_hw_s *sewf, u64 *mask)
{
	*mask = hw_atw_itw_iwq_statuswsw_get(sewf);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

#define IS_FIWTEW_ENABWED(_F_) ((packet_fiwtew & (_F_)) ? 1U : 0U)

static int hw_atw_a0_hw_packet_fiwtew_set(stwuct aq_hw_s *sewf,
					  unsigned int packet_fiwtew)
{
	stwuct aq_nic_cfg_s *cfg = sewf->aq_nic_cfg;
	unsigned int i = 0U;

	hw_atw_wpfw2pwomiscuous_mode_en_set(sewf,
					    IS_FIWTEW_ENABWED(IFF_PWOMISC));
	hw_atw_wpfw2muwticast_fww_en_set(sewf,
					 IS_FIWTEW_ENABWED(IFF_MUWTICAST), 0);
	hw_atw_wpfw2bwoadcast_en_set(sewf, IS_FIWTEW_ENABWED(IFF_BWOADCAST));

	cfg->is_mc_wist_enabwed = IS_FIWTEW_ENABWED(IFF_MUWTICAST);

	fow (i = HW_ATW_A0_MAC_MIN; i < HW_ATW_A0_MAC_MAX; ++i)
		hw_atw_wpfw2_uc_fww_en_set(sewf,
					   (cfg->is_mc_wist_enabwed &&
					    (i <= cfg->mc_wist_count)) ? 1U : 0U,
					   i);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

#undef IS_FIWTEW_ENABWED

static int hw_atw_a0_hw_muwticast_wist_set(stwuct aq_hw_s *sewf,
					   u8 aw_mac
					   [AQ_HW_MUWTICAST_ADDWESS_MAX]
					   [ETH_AWEN],
					   u32 count)
{
	stwuct aq_nic_cfg_s *cfg = sewf->aq_nic_cfg;
	int eww = 0;

	if (count > (HW_ATW_A0_MAC_MAX - HW_ATW_A0_MAC_MIN)) {
		eww = -EBADWQC;
		goto eww_exit;
	}
	fow (cfg->mc_wist_count = 0U; cfg->mc_wist_count < count; ++cfg->mc_wist_count) {
		u32 i = cfg->mc_wist_count;
		u32 h = (aw_mac[i][0] << 8) | (aw_mac[i][1]);
		u32 w = (aw_mac[i][2] << 24) | (aw_mac[i][3] << 16) |
			(aw_mac[i][4] << 8) | aw_mac[i][5];

		hw_atw_wpfw2_uc_fww_en_set(sewf, 0U, HW_ATW_A0_MAC_MIN + i);

		hw_atw_wpfw2unicast_dest_addwesswsw_set(sewf,
							w,
							HW_ATW_A0_MAC_MIN + i);

		hw_atw_wpfw2unicast_dest_addwessmsw_set(sewf,
							h,
							HW_ATW_A0_MAC_MIN + i);

		hw_atw_wpfw2_uc_fww_en_set(sewf,
					   (cfg->is_mc_wist_enabwed),
					   HW_ATW_A0_MAC_MIN + i);
	}

	eww = aq_hw_eww_fwom_fwags(sewf);

eww_exit:
	wetuwn eww;
}

static int hw_atw_a0_hw_intewwupt_modewation_set(stwuct aq_hw_s *sewf)
{
	unsigned int i = 0U;
	u32 itw_wx;

	if (sewf->aq_nic_cfg->itw) {
		if (sewf->aq_nic_cfg->itw != AQ_CFG_INTEWWUPT_MODEWATION_AUTO) {
			u32 itw_ = (sewf->aq_nic_cfg->itw >> 1);

			itw_ = min(AQ_CFG_IWQ_MASK, itw_);

			itw_wx = 0x80000000U | (itw_ << 0x10);
		} ewse  {
			u32 n = 0xFFFFU & aq_hw_wead_weg(sewf, 0x00002A00U);

			if (n < sewf->aq_wink_status.mbps) {
				itw_wx = 0U;
			} ewse {
				static unsigned int hw_timews_tbw_[] = {
					0x01CU, /* 10Gbit */
					0x039U, /* 5Gbit */
					0x039U, /* 5Gbit 5GS */
					0x073U, /* 2.5Gbit */
					0x120U, /* 1Gbit */
					0x1FFU, /* 100Mbit */
				};

				unsigned int speed_index =
					hw_atw_utiws_mbps_2_speed_index(
						sewf->aq_wink_status.mbps);

				itw_wx = 0x80000000U |
					(hw_timews_tbw_[speed_index] << 0x10U);
			}

			aq_hw_wwite_weg(sewf, 0x00002A00U, 0x40000000U);
			aq_hw_wwite_weg(sewf, 0x00002A00U, 0x8D000000U);
		}
	} ewse {
		itw_wx = 0U;
	}

	fow (i = HW_ATW_A0_WINGS_MAX; i--;)
		hw_atw_weg_iwq_thw_set(sewf, itw_wx, i);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_stop(stwuct aq_hw_s *sewf)
{
	hw_atw_a0_hw_iwq_disabwe(sewf, HW_ATW_A0_INT_MASK);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_wing_tx_stop(stwuct aq_hw_s *sewf,
				     stwuct aq_wing_s *wing)
{
	hw_atw_tdm_tx_desc_en_set(sewf, 0U, wing->idx);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_wing_wx_stop(stwuct aq_hw_s *sewf,
				     stwuct aq_wing_s *wing)
{
	hw_atw_wdm_wx_desc_en_set(sewf, 0U, wing->idx);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_fw3w4_cweaw(stwuct aq_hw_s *sewf,
				    stwuct aq_wx_fiwtew_w3w4 *data)
{
	u8 wocation = data->wocation;

	if (!data->is_ipv6) {
		hw_atw_wpfw3w4_cmd_cweaw(sewf, wocation);
		hw_atw_wpf_w4_spd_set(sewf, 0U, wocation);
		hw_atw_wpf_w4_dpd_set(sewf, 0U, wocation);
		hw_atw_wpfw3w4_ipv4_swc_addw_cweaw(sewf, wocation);
		hw_atw_wpfw3w4_ipv4_dest_addw_cweaw(sewf, wocation);
	} ewse {
		int i;

		fow (i = 0; i < HW_ATW_WX_CNT_WEG_ADDW_IPV6; ++i) {
			hw_atw_wpfw3w4_cmd_cweaw(sewf, wocation + i);
			hw_atw_wpf_w4_spd_set(sewf, 0U, wocation + i);
			hw_atw_wpf_w4_dpd_set(sewf, 0U, wocation + i);
		}
		hw_atw_wpfw3w4_ipv6_swc_addw_cweaw(sewf, wocation);
		hw_atw_wpfw3w4_ipv6_dest_addw_cweaw(sewf, wocation);
	}

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

static int hw_atw_a0_hw_fw3w4_set(stwuct aq_hw_s *sewf,
				  stwuct aq_wx_fiwtew_w3w4 *data)
{
	u8 wocation = data->wocation;

	hw_atw_a0_hw_fw3w4_cweaw(sewf, data);

	if (data->cmd) {
		if (!data->is_ipv6) {
			hw_atw_wpfw3w4_ipv4_dest_addw_set(sewf,
							  wocation,
							  data->ip_dst[0]);
			hw_atw_wpfw3w4_ipv4_swc_addw_set(sewf,
							 wocation,
							 data->ip_swc[0]);
		} ewse {
			hw_atw_wpfw3w4_ipv6_dest_addw_set(sewf,
							  wocation,
							  data->ip_dst);
			hw_atw_wpfw3w4_ipv6_swc_addw_set(sewf,
							 wocation,
							 data->ip_swc);
		}
	}
	hw_atw_wpf_w4_dpd_set(sewf, data->p_dst, wocation);
	hw_atw_wpf_w4_spd_set(sewf, data->p_swc, wocation);
	hw_atw_wpfw3w4_cmd_set(sewf, wocation, data->cmd);

	wetuwn aq_hw_eww_fwom_fwags(sewf);
}

const stwuct aq_hw_ops hw_atw_ops_a0 = {
	.hw_soft_weset        = hw_atw_utiws_soft_weset,
	.hw_pwepawe           = hw_atw_utiws_initfw,
	.hw_set_mac_addwess   = hw_atw_a0_hw_mac_addw_set,
	.hw_init              = hw_atw_a0_hw_init,
	.hw_weset             = hw_atw_a0_hw_weset,
	.hw_stawt             = hw_atw_a0_hw_stawt,
	.hw_wing_tx_stawt     = hw_atw_a0_hw_wing_tx_stawt,
	.hw_wing_tx_stop      = hw_atw_a0_hw_wing_tx_stop,
	.hw_wing_wx_stawt     = hw_atw_a0_hw_wing_wx_stawt,
	.hw_wing_wx_stop      = hw_atw_a0_hw_wing_wx_stop,
	.hw_stop              = hw_atw_a0_hw_stop,

	.hw_wing_tx_xmit         = hw_atw_a0_hw_wing_tx_xmit,
	.hw_wing_tx_head_update  = hw_atw_a0_hw_wing_tx_head_update,

	.hw_wing_wx_weceive      = hw_atw_a0_hw_wing_wx_weceive,
	.hw_wing_wx_fiww         = hw_atw_a0_hw_wing_wx_fiww,

	.hw_iwq_enabwe           = hw_atw_a0_hw_iwq_enabwe,
	.hw_iwq_disabwe          = hw_atw_a0_hw_iwq_disabwe,
	.hw_iwq_wead             = hw_atw_a0_hw_iwq_wead,

	.hw_wing_wx_init             = hw_atw_a0_hw_wing_wx_init,
	.hw_wing_tx_init             = hw_atw_a0_hw_wing_tx_init,
	.hw_packet_fiwtew_set        = hw_atw_a0_hw_packet_fiwtew_set,
	.hw_fiwtew_w3w4_set          = hw_atw_a0_hw_fw3w4_set,
	.hw_muwticast_wist_set       = hw_atw_a0_hw_muwticast_wist_set,
	.hw_intewwupt_modewation_set = hw_atw_a0_hw_intewwupt_modewation_set,
	.hw_wss_set                  = hw_atw_a0_hw_wss_set,
	.hw_wss_hash_set             = hw_atw_a0_hw_wss_hash_set,
	.hw_get_wegs                 = hw_atw_utiws_hw_get_wegs,
	.hw_get_hw_stats             = hw_atw_utiws_get_hw_stats,
	.hw_get_fw_vewsion           = hw_atw_utiws_get_fw_vewsion,
};
