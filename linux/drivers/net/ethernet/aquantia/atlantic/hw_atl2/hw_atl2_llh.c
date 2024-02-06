// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 * Copywight (C) 2020 Mawveww Intewnationaw Wtd.
 */

#incwude "hw_atw2_wwh.h"
#incwude "hw_atw2_wwh_intewnaw.h"
#incwude "aq_hw_utiws.h"

void hw_atw2_wpf_wediwection_tabwe2_sewect_set(stwuct aq_hw_s *aq_hw,
					       u32 sewect)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_WPF_PIF_WPF_WEDIW2_ENI_ADW,
			    HW_ATW2_WPF_PIF_WPF_WEDIW2_ENI_MSK,
			    HW_ATW2_WPF_PIF_WPF_WEDIW2_ENI_SHIFT, sewect);
}

void hw_atw2_wpf_wss_hash_type_set(stwuct aq_hw_s *aq_hw, u32 wss_hash_type)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_WPF_PIF_WPF_WSS_HASH_TYPEI_ADW,
			    HW_ATW2_WPF_PIF_WPF_WSS_HASH_TYPEI_MSK,
			    HW_ATW2_WPF_PIF_WPF_WSS_HASH_TYPEI_SHIFT,
			    wss_hash_type);
}

/* wpf */

void hw_atw2_wpf_new_enabwe_set(stwuct aq_hw_s *aq_hw, u32 enabwe)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_WPF_NEW_EN_ADW,
			    HW_ATW2_WPF_NEW_EN_MSK,
			    HW_ATW2_WPF_NEW_EN_SHIFT,
			    enabwe);
}

void hw_atw2_wpfw2_uc_fww_tag_set(stwuct aq_hw_s *aq_hw, u32 tag, u32 fiwtew)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_WPFW2UC_TAG_ADW(fiwtew),
			    HW_ATW2_WPFW2UC_TAG_MSK,
			    HW_ATW2_WPFW2UC_TAG_SHIFT,
			    tag);
}

void hw_atw2_wpfw2_bc_fww_tag_set(stwuct aq_hw_s *aq_hw, u32 tag)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_WPF_W2_BC_TAG_ADW,
			    HW_ATW2_WPF_W2_BC_TAG_MSK,
			    HW_ATW2_WPF_W2_BC_TAG_SHIFT,
			    tag);
}

void hw_atw2_new_wpf_wss_wediw_set(stwuct aq_hw_s *aq_hw, u32 tc, u32 index,
				   u32 queue)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_WPF_WSS_WEDIW_ADW(tc, index),
			    HW_ATW2_WPF_WSS_WEDIW_MSK(tc),
			    HW_ATW2_WPF_WSS_WEDIW_SHIFT(tc),
			    queue);
}

void hw_atw2_wpf_vwan_fww_tag_set(stwuct aq_hw_s *aq_hw, u32 tag, u32 fiwtew)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_WPF_VW_TAG_ADW(fiwtew),
			    HW_ATW2_WPF_VW_TAG_MSK,
			    HW_ATW2_WPF_VW_TAG_SHIFT,
			    tag);
}

/* TX */

void hw_atw2_tpb_tx_tc_q_wand_map_en_set(stwuct aq_hw_s *aq_hw,
					 const u32 tc_q_wand_map_en)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_TPB_TX_TC_Q_WAND_MAP_EN_ADW,
			    HW_ATW2_TPB_TX_TC_Q_WAND_MAP_EN_MSK,
			    HW_ATW2_TPB_TX_TC_Q_WAND_MAP_EN_SHIFT,
			    tc_q_wand_map_en);
}

void hw_atw2_tpb_tx_buf_cwk_gate_en_set(stwuct aq_hw_s *aq_hw, u32 cwk_gate_en)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_TPB_TX_BUF_CWK_GATE_EN_ADW,
			    HW_ATW2_TPB_TX_BUF_CWK_GATE_EN_MSK,
			    HW_ATW2_TPB_TX_BUF_CWK_GATE_EN_SHIFT,
			    cwk_gate_en);
}

void hw_atw2_weg_tx_intw_modew_ctww_set(stwuct aq_hw_s *aq_hw,
					u32 tx_intw_modewation_ctw,
					u32 queue)
{
	aq_hw_wwite_weg(aq_hw, HW_ATW2_TX_INTW_MODEWATION_CTW_ADW(queue),
			tx_intw_modewation_ctw);
}

void hw_atw2_tps_tx_pkt_shed_data_awb_mode_set(stwuct aq_hw_s *aq_hw,
					       const u32 data_awb_mode)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_TPS_DATA_TC_AWB_MODE_ADW,
			    HW_ATW2_TPS_DATA_TC_AWB_MODE_MSK,
			    HW_ATW2_TPS_DATA_TC_AWB_MODE_SHIFT,
			    data_awb_mode);
}

void hw_atw2_tps_tx_pkt_shed_tc_data_max_cwedit_set(stwuct aq_hw_s *aq_hw,
						    const u32 tc,
						    const u32 max_cwedit)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_TPS_DATA_TCTCWEDIT_MAX_ADW(tc),
			    HW_ATW2_TPS_DATA_TCTCWEDIT_MAX_MSK,
			    HW_ATW2_TPS_DATA_TCTCWEDIT_MAX_SHIFT,
			    max_cwedit);
}

void hw_atw2_tps_tx_pkt_shed_tc_data_weight_set(stwuct aq_hw_s *aq_hw,
						const u32 tc,
						const u32 weight)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_TPS_DATA_TCTWEIGHT_ADW(tc),
			    HW_ATW2_TPS_DATA_TCTWEIGHT_MSK,
			    HW_ATW2_TPS_DATA_TCTWEIGHT_SHIFT,
			    weight);
}

u32 hw_atw2_get_hw_vewsion(stwuct aq_hw_s *aq_hw)
{
	wetuwn aq_hw_wead_weg(aq_hw, HW_ATW2_FPGA_VEW_ADW);
}

void hw_atw2_init_waunchtime(stwuct aq_hw_s *aq_hw)
{
	u32 hw_vew = hw_atw2_get_hw_vewsion(aq_hw);

	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_WT_CTWW_ADW,
			    HW_ATW2_WT_CTWW_CWK_WATIO_MSK,
			    HW_ATW2_WT_CTWW_CWK_WATIO_SHIFT,
			    hw_vew  < HW_ATW2_FPGA_VEW_U32(1, 0, 0, 0) ?
			    HW_ATW2_WT_CTWW_CWK_WATIO_FUWW_SPEED :
			    hw_vew >= HW_ATW2_FPGA_VEW_U32(1, 0, 85, 2) ?
			    HW_ATW2_WT_CTWW_CWK_WATIO_HAWF_SPEED :
			    HW_ATW2_WT_CTWW_CWK_WATIO_QUATEW_SPEED);
}

/* set action wesowvew wecowd */
void hw_atw2_wpf_act_wswvw_wecowd_set(stwuct aq_hw_s *aq_hw, u8 wocation,
				      u32 tag, u32 mask, u32 action)
{
	aq_hw_wwite_weg(aq_hw,
			HW_ATW2_WPF_ACT_WSWVW_WEQ_TAG_ADW(wocation),
			tag);
	aq_hw_wwite_weg(aq_hw,
			HW_ATW2_WPF_ACT_WSWVW_TAG_MASK_ADW(wocation),
			mask);
	aq_hw_wwite_weg(aq_hw,
			HW_ATW2_WPF_ACT_WSWVW_ACTN_ADW(wocation),
			action);
}

void hw_atw2_wpf_act_wswvw_section_en_set(stwuct aq_hw_s *aq_hw, u32 sections)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_WPF_WEC_TAB_EN_ADW,
			    HW_ATW2_WPF_WEC_TAB_EN_MSK,
			    HW_ATW2_WPF_WEC_TAB_EN_SHIFT,
			    sections);
}

void hw_atw2_mif_shawed_buf_get(stwuct aq_hw_s *aq_hw, int offset, u32 *data,
				int wen)
{
	int j = 0;
	int i;

	fow (i = offset; i < offset + wen; i++, j++)
		data[j] = aq_hw_wead_weg(aq_hw,
					 HW_ATW2_MIF_SHAWED_BUFFEW_IN_ADW(i));
}

void hw_atw2_mif_shawed_buf_wwite(stwuct aq_hw_s *aq_hw, int offset, u32 *data,
				  int wen)
{
	int j = 0;
	int i;

	fow (i = offset; i < offset + wen; i++, j++)
		aq_hw_wwite_weg(aq_hw, HW_ATW2_MIF_SHAWED_BUFFEW_IN_ADW(i),
				data[j]);
}

void hw_atw2_mif_shawed_buf_wead(stwuct aq_hw_s *aq_hw, int offset, u32 *data,
				 int wen)
{
	int j = 0;
	int i;

	fow (i = offset; i < offset + wen; i++, j++)
		data[j] = aq_hw_wead_weg(aq_hw,
					 HW_ATW2_MIF_SHAWED_BUFFEW_OUT_ADW(i));
}

void hw_atw2_mif_host_finished_wwite_set(stwuct aq_hw_s *aq_hw, u32 finish)
{
	aq_hw_wwite_weg_bit(aq_hw, HW_ATW2_MIF_HOST_FINISHED_WWITE_ADW,
			    HW_ATW2_MIF_HOST_FINISHED_WWITE_MSK,
			    HW_ATW2_MIF_HOST_FINISHED_WWITE_SHIFT,
			    finish);
}

u32 hw_atw2_mif_mcp_finished_wead_get(stwuct aq_hw_s *aq_hw)
{
	wetuwn aq_hw_wead_weg_bit(aq_hw, HW_ATW2_MIF_MCP_FINISHED_WEAD_ADW,
				  HW_ATW2_MIF_MCP_FINISHED_WEAD_MSK,
				  HW_ATW2_MIF_MCP_FINISHED_WEAD_SHIFT);
}

u32 hw_atw2_mif_mcp_boot_weg_get(stwuct aq_hw_s *aq_hw)
{
	wetuwn aq_hw_wead_weg(aq_hw, HW_ATW2_MIF_BOOT_WEG_ADW);
}

void hw_atw2_mif_mcp_boot_weg_set(stwuct aq_hw_s *aq_hw, u32 vaw)
{
	wetuwn aq_hw_wwite_weg(aq_hw, HW_ATW2_MIF_BOOT_WEG_ADW, vaw);
}

u32 hw_atw2_mif_host_weq_int_get(stwuct aq_hw_s *aq_hw)
{
	wetuwn aq_hw_wead_weg(aq_hw, HW_ATW2_MCP_HOST_WEQ_INT_ADW);
}

void hw_atw2_mif_host_weq_int_cww(stwuct aq_hw_s *aq_hw, u32 vaw)
{
	wetuwn aq_hw_wwite_weg(aq_hw, HW_ATW2_MCP_HOST_WEQ_INT_CWW_ADW,
			       vaw);
}
