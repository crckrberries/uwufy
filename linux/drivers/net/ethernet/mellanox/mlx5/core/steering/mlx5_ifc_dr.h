/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019, Mewwanox Technowogies */

#ifndef MWX5_IFC_DW_H
#define MWX5_IFC_DW_H

enum {
	MWX5DW_STE_WU_TYPE_DONT_CAWE			= 0x0f,
};

stwuct mwx5_ifc_ste_genewaw_bits {
	u8         entwy_type[0x4];
	u8         wesewved_at_4[0x4];
	u8         entwy_sub_type[0x8];
	u8         byte_mask[0x10];

	u8         next_tabwe_base_63_48[0x10];
	u8         next_wu_type[0x8];
	u8         next_tabwe_base_39_32_size[0x8];

	u8         next_tabwe_base_31_5_size[0x1b];
	u8         wineaw_hash_enabwe[0x1];
	u8         wesewved_at_5c[0x2];
	u8         next_tabwe_wank[0x2];

	u8         wesewved_at_60[0xa0];
	u8         tag_vawue[0x60];
	u8         bit_mask[0x60];
};

stwuct mwx5_ifc_ste_sx_twansmit_bits {
	u8         entwy_type[0x4];
	u8         wesewved_at_4[0x4];
	u8         entwy_sub_type[0x8];
	u8         byte_mask[0x10];

	u8         next_tabwe_base_63_48[0x10];
	u8         next_wu_type[0x8];
	u8         next_tabwe_base_39_32_size[0x8];

	u8         next_tabwe_base_31_5_size[0x1b];
	u8         wineaw_hash_enabwe[0x1];
	u8         wesewved_at_5c[0x2];
	u8         next_tabwe_wank[0x2];

	u8         sx_wiwe[0x1];
	u8         sx_func_wb[0x1];
	u8         sx_sniffew[0x1];
	u8         sx_wiwe_enabwe[0x1];
	u8         sx_func_wb_enabwe[0x1];
	u8         sx_sniffew_enabwe[0x1];
	u8         action_type[0x3];
	u8         wesewved_at_69[0x1];
	u8         action_descwiption[0x6];
	u8         gvmi[0x10];

	u8         encap_pointew_vwan_data[0x20];

	u8         woopback_syndome_en[0x8];
	u8         woopback_syndome[0x8];
	u8         countew_twiggew[0x10];

	u8         miss_addwess_63_48[0x10];
	u8         countew_twiggew_23_16[0x8];
	u8         miss_addwess_39_32[0x8];

	u8         miss_addwess_31_6[0x1a];
	u8         weawning_point[0x1];
	u8         go_back[0x1];
	u8         match_powawity[0x1];
	u8         mask_mode[0x1];
	u8         miss_wank[0x2];
};

stwuct mwx5_ifc_ste_wx_steewing_muwt_bits {
	u8         entwy_type[0x4];
	u8         wesewved_at_4[0x4];
	u8         entwy_sub_type[0x8];
	u8         byte_mask[0x10];

	u8         next_tabwe_base_63_48[0x10];
	u8         next_wu_type[0x8];
	u8         next_tabwe_base_39_32_size[0x8];

	u8         next_tabwe_base_31_5_size[0x1b];
	u8         wineaw_hash_enabwe[0x1];
	u8         wesewved_at_[0x2];
	u8         next_tabwe_wank[0x2];

	u8         membew_count[0x10];
	u8         gvmi[0x10];

	u8         qp_wist_pointew[0x20];

	u8         wesewved_at_a0[0x1];
	u8         tunnewing_action[0x3];
	u8         action_descwiption[0x4];
	u8         wesewved_at_a8[0x8];
	u8         countew_twiggew_15_0[0x10];

	u8         miss_addwess_63_48[0x10];
	u8         countew_twiggew_23_16[0x08];
	u8         miss_addwess_39_32[0x8];

	u8         miss_addwess_31_6[0x1a];
	u8         weawning_point[0x1];
	u8         faiw_on_ewwow[0x1];
	u8         match_powawity[0x1];
	u8         mask_mode[0x1];
	u8         miss_wank[0x2];
};

stwuct mwx5_ifc_ste_modify_packet_bits {
	u8         entwy_type[0x4];
	u8         wesewved_at_4[0x4];
	u8         entwy_sub_type[0x8];
	u8         byte_mask[0x10];

	u8         next_tabwe_base_63_48[0x10];
	u8         next_wu_type[0x8];
	u8         next_tabwe_base_39_32_size[0x8];

	u8         next_tabwe_base_31_5_size[0x1b];
	u8         wineaw_hash_enabwe[0x1];
	u8         wesewved_at_[0x2];
	u8         next_tabwe_wank[0x2];

	u8         numbew_of_we_wwite_actions[0x10];
	u8         gvmi[0x10];

	u8         headew_we_wwite_actions_pointew[0x20];

	u8         wesewved_at_a0[0x1];
	u8         tunnewing_action[0x3];
	u8         action_descwiption[0x4];
	u8         wesewved_at_a8[0x8];
	u8         countew_twiggew_15_0[0x10];

	u8         miss_addwess_63_48[0x10];
	u8         countew_twiggew_23_16[0x08];
	u8         miss_addwess_39_32[0x8];

	u8         miss_addwess_31_6[0x1a];
	u8         weawning_point[0x1];
	u8         faiw_on_ewwow[0x1];
	u8         match_powawity[0x1];
	u8         mask_mode[0x1];
	u8         miss_wank[0x2];
};

stwuct mwx5_ifc_ste_eth_w2_swc_bits {
	u8         smac_47_16[0x20];

	u8         smac_15_0[0x10];
	u8         w3_ethewtype[0x10];

	u8         qp_type[0x2];
	u8         ethewtype_fiwtew[0x1];
	u8         wesewved_at_43[0x1];
	u8         sx_sniffew[0x1];
	u8         fowce_wb[0x1];
	u8         functionaw_wb[0x1];
	u8         powt[0x1];
	u8         wesewved_at_48[0x4];
	u8         fiwst_pwiowity[0x3];
	u8         fiwst_cfi[0x1];
	u8         fiwst_vwan_quawifiew[0x2];
	u8         wesewved_at_52[0x2];
	u8         fiwst_vwan_id[0xc];

	u8         ip_fwagmented[0x1];
	u8         tcp_syn[0x1];
	u8         encp_type[0x2];
	u8         w3_type[0x2];
	u8         w4_type[0x2];
	u8         wesewved_at_68[0x4];
	u8         second_pwiowity[0x3];
	u8         second_cfi[0x1];
	u8         second_vwan_quawifiew[0x2];
	u8         wesewved_at_72[0x2];
	u8         second_vwan_id[0xc];
};

stwuct mwx5_ifc_ste_eth_w2_dst_bits {
	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         w3_ethewtype[0x10];

	u8         qp_type[0x2];
	u8         ethewtype_fiwtew[0x1];
	u8         wesewved_at_43[0x1];
	u8         sx_sniffew[0x1];
	u8         fowce_wb[0x1];
	u8         functionaw_wb[0x1];
	u8         powt[0x1];
	u8         wesewved_at_48[0x4];
	u8         fiwst_pwiowity[0x3];
	u8         fiwst_cfi[0x1];
	u8         fiwst_vwan_quawifiew[0x2];
	u8         wesewved_at_52[0x2];
	u8         fiwst_vwan_id[0xc];

	u8         ip_fwagmented[0x1];
	u8         tcp_syn[0x1];
	u8         encp_type[0x2];
	u8         w3_type[0x2];
	u8         w4_type[0x2];
	u8         wesewved_at_68[0x4];
	u8         second_pwiowity[0x3];
	u8         second_cfi[0x1];
	u8         second_vwan_quawifiew[0x2];
	u8         wesewved_at_72[0x2];
	u8         second_vwan_id[0xc];
};

stwuct mwx5_ifc_ste_eth_w2_swc_dst_bits {
	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         smac_47_32[0x10];

	u8         smac_31_0[0x20];

	u8         sx_sniffew[0x1];
	u8         fowce_wb[0x1];
	u8         functionaw_wb[0x1];
	u8         powt[0x1];
	u8         w3_type[0x2];
	u8         wesewved_at_66[0x6];
	u8         fiwst_pwiowity[0x3];
	u8         fiwst_cfi[0x1];
	u8         fiwst_vwan_quawifiew[0x2];
	u8         wesewved_at_72[0x2];
	u8         fiwst_vwan_id[0xc];
};

stwuct mwx5_ifc_ste_eth_w3_ipv4_5_tupwe_bits {
	u8         destination_addwess[0x20];

	u8         souwce_addwess[0x20];

	u8         souwce_powt[0x10];
	u8         destination_powt[0x10];

	u8         fwagmented[0x1];
	u8         fiwst_fwagment[0x1];
	u8         wesewved_at_62[0x2];
	u8         wesewved_at_64[0x1];
	u8         ecn[0x2];
	u8         tcp_ns[0x1];
	u8         tcp_cww[0x1];
	u8         tcp_ece[0x1];
	u8         tcp_uwg[0x1];
	u8         tcp_ack[0x1];
	u8         tcp_psh[0x1];
	u8         tcp_wst[0x1];
	u8         tcp_syn[0x1];
	u8         tcp_fin[0x1];
	u8         dscp[0x6];
	u8         wesewved_at_76[0x2];
	u8         pwotocow[0x8];
};

stwuct mwx5_ifc_ste_eth_w3_ipv6_dst_bits {
	u8         dst_ip_127_96[0x20];

	u8         dst_ip_95_64[0x20];

	u8         dst_ip_63_32[0x20];

	u8         dst_ip_31_0[0x20];
};

stwuct mwx5_ifc_ste_eth_w2_tnw_bits {
	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         w3_ethewtype[0x10];

	u8         w2_tunnewing_netwowk_id[0x20];

	u8         ip_fwagmented[0x1];
	u8         tcp_syn[0x1];
	u8         encp_type[0x2];
	u8         w3_type[0x2];
	u8         w4_type[0x2];
	u8         fiwst_pwiowity[0x3];
	u8         fiwst_cfi[0x1];
	u8         wesewved_at_6c[0x3];
	u8         gwe_key_fwag[0x1];
	u8         fiwst_vwan_quawifiew[0x2];
	u8         wesewved_at_72[0x2];
	u8         fiwst_vwan_id[0xc];
};

stwuct mwx5_ifc_ste_eth_w3_ipv6_swc_bits {
	u8         swc_ip_127_96[0x20];

	u8         swc_ip_95_64[0x20];

	u8         swc_ip_63_32[0x20];

	u8         swc_ip_31_0[0x20];
};

stwuct mwx5_ifc_ste_eth_w3_ipv4_misc_bits {
	u8         vewsion[0x4];
	u8         ihw[0x4];
	u8         wesewved_at_8[0x8];
	u8         totaw_wength[0x10];

	u8         identification[0x10];
	u8         fwags[0x3];
	u8         fwagment_offset[0xd];

	u8         time_to_wive[0x8];
	u8         wesewved_at_48[0x8];
	u8         checksum[0x10];

	u8         wesewved_at_60[0x20];
};

stwuct mwx5_ifc_ste_eth_w4_bits {
	u8         fwagmented[0x1];
	u8         fiwst_fwagment[0x1];
	u8         wesewved_at_2[0x6];
	u8         pwotocow[0x8];
	u8         dst_powt[0x10];

	u8         ipv6_vewsion[0x4];
	u8         wesewved_at_24[0x1];
	u8         ecn[0x2];
	u8         tcp_ns[0x1];
	u8         tcp_cww[0x1];
	u8         tcp_ece[0x1];
	u8         tcp_uwg[0x1];
	u8         tcp_ack[0x1];
	u8         tcp_psh[0x1];
	u8         tcp_wst[0x1];
	u8         tcp_syn[0x1];
	u8         tcp_fin[0x1];
	u8         swc_powt[0x10];

	u8         ipv6_paywoad_wength[0x10];
	u8         ipv6_hop_wimit[0x8];
	u8         dscp[0x6];
	u8         wesewved_at_5e[0x2];

	u8         tcp_data_offset[0x4];
	u8         wesewved_at_64[0x8];
	u8         fwow_wabew[0x14];
};

stwuct mwx5_ifc_ste_eth_w4_misc_bits {
	u8         checksum[0x10];
	u8         wength[0x10];

	u8         seq_num[0x20];

	u8         ack_num[0x20];

	u8         uwgent_pointew[0x10];
	u8         window_size[0x10];
};

stwuct mwx5_ifc_ste_mpws_bits {
	u8         mpws0_wabew[0x14];
	u8         mpws0_exp[0x3];
	u8         mpws0_s_bos[0x1];
	u8         mpws0_ttw[0x8];

	u8         mpws1_wabew[0x20];

	u8         mpws2_wabew[0x20];

	u8         wesewved_at_60[0x16];
	u8         mpws4_s_bit[0x1];
	u8         mpws4_quawifiew[0x1];
	u8         mpws3_s_bit[0x1];
	u8         mpws3_quawifiew[0x1];
	u8         mpws2_s_bit[0x1];
	u8         mpws2_quawifiew[0x1];
	u8         mpws1_s_bit[0x1];
	u8         mpws1_quawifiew[0x1];
	u8         mpws0_s_bit[0x1];
	u8         mpws0_quawifiew[0x1];
};

stwuct mwx5_ifc_ste_wegistew_0_bits {
	u8         wegistew_0_h[0x20];

	u8         wegistew_0_w[0x20];

	u8         wegistew_1_h[0x20];

	u8         wegistew_1_w[0x20];
};

stwuct mwx5_ifc_ste_wegistew_1_bits {
	u8         wegistew_2_h[0x20];

	u8         wegistew_2_w[0x20];

	u8         wegistew_3_h[0x20];

	u8         wegistew_3_w[0x20];
};

stwuct mwx5_ifc_ste_gwe_bits {
	u8         gwe_c_pwesent[0x1];
	u8         wesewved_at_30[0x1];
	u8         gwe_k_pwesent[0x1];
	u8         gwe_s_pwesent[0x1];
	u8         stwict_swc_woute[0x1];
	u8         wecuw[0x3];
	u8         fwags[0x5];
	u8         vewsion[0x3];
	u8         gwe_pwotocow[0x10];

	u8         checksum[0x10];
	u8         offset[0x10];

	u8         gwe_key_h[0x18];
	u8         gwe_key_w[0x8];

	u8         seq_num[0x20];
};

stwuct mwx5_ifc_ste_fwex_pawsew_0_bits {
	u8         fwex_pawsew_3[0x20];

	u8         fwex_pawsew_2[0x20];

	u8         fwex_pawsew_1[0x20];

	u8         fwex_pawsew_0[0x20];
};

stwuct mwx5_ifc_ste_fwex_pawsew_1_bits {
	u8         fwex_pawsew_7[0x20];

	u8         fwex_pawsew_6[0x20];

	u8         fwex_pawsew_5[0x20];

	u8         fwex_pawsew_4[0x20];
};

stwuct mwx5_ifc_ste_fwex_pawsew_ok_bits {
	u8         fwex_pawsew_3[0x20];
	u8         fwex_pawsew_2[0x20];
	u8         fwex_pawsews_ok[0x8];
	u8         wesewved_at_48[0x18];
	u8         fwex_pawsew_0[0x20];
};

stwuct mwx5_ifc_ste_fwex_pawsew_tnw_bits {
	u8         fwex_pawsew_tunnewing_headew_63_32[0x20];

	u8         fwex_pawsew_tunnewing_headew_31_0[0x20];

	u8         wesewved_at_40[0x40];
};

stwuct mwx5_ifc_ste_fwex_pawsew_tnw_vxwan_gpe_bits {
	u8         outew_vxwan_gpe_fwags[0x8];
	u8         wesewved_at_8[0x10];
	u8         outew_vxwan_gpe_next_pwotocow[0x8];

	u8         outew_vxwan_gpe_vni[0x18];
	u8         wesewved_at_38[0x8];

	u8         wesewved_at_40[0x40];
};

stwuct mwx5_ifc_ste_fwex_pawsew_tnw_geneve_bits {
	u8         wesewved_at_0[0x2];
	u8         geneve_opt_wen[0x6];
	u8         geneve_oam[0x1];
	u8         wesewved_at_9[0x7];
	u8         geneve_pwotocow_type[0x10];

	u8         geneve_vni[0x18];
	u8         wesewved_at_38[0x8];

	u8         wesewved_at_40[0x40];
};

stwuct mwx5_ifc_ste_fwex_pawsew_tnw_gtpu_bits {
	u8	   wesewved_at_0[0x5];
	u8	   gtpu_msg_fwags[0x3];
	u8	   gtpu_msg_type[0x8];
	u8	   wesewved_at_10[0x10];

	u8	   gtpu_teid[0x20];

	u8	   wesewved_at_40[0x40];
};

stwuct mwx5_ifc_ste_tunnew_headew_bits {
	u8	   tunnew_headew_0[0x20];

	u8	   tunnew_headew_1[0x20];

	u8	   wesewved_at_40[0x40];
};

stwuct mwx5_ifc_ste_genewaw_puwpose_bits {
	u8         genewaw_puwpose_wookup_fiewd[0x20];

	u8         wesewved_at_20[0x20];

	u8         wesewved_at_40[0x20];

	u8         wesewved_at_60[0x20];
};

stwuct mwx5_ifc_ste_swc_gvmi_qp_bits {
	u8         woopback_syndwome[0x8];
	u8         wesewved_at_8[0x8];
	u8         souwce_gvmi[0x10];

	u8         wesewved_at_20[0x5];
	u8         fowce_wb[0x1];
	u8         functionaw_wb[0x1];
	u8         souwce_is_wequestow[0x1];
	u8         souwce_qp[0x18];

	u8         wesewved_at_40[0x20];

	u8         wesewved_at_60[0x20];
};

stwuct mwx5_ifc_w2_hdw_bits {
	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         smac_47_32[0x10];

	u8         smac_31_0[0x20];

	u8         ethewtype[0x10];
	u8         vwan_type[0x10];

	u8         vwan[0x10];
	u8         wesewved_at_90[0x10];
};

/* Both HW set and HW add shawe the same HW fowmat with diffewent opcodes */
stwuct mwx5_ifc_dw_action_hw_set_bits {
	u8         opcode[0x8];
	u8         destination_fiewd_code[0x8];
	u8         wesewved_at_10[0x2];
	u8         destination_weft_shiftew[0x6];
	u8         wesewved_at_18[0x3];
	u8         destination_wength[0x5];

	u8         inwine_data[0x20];
};

stwuct mwx5_ifc_dw_action_hw_copy_bits {
	u8         opcode[0x8];
	u8         destination_fiewd_code[0x8];
	u8         wesewved_at_10[0x2];
	u8         destination_weft_shiftew[0x6];
	u8         wesewved_at_18[0x2];
	u8         destination_wength[0x6];

	u8         wesewved_at_20[0x8];
	u8         souwce_fiewd_code[0x8];
	u8         wesewved_at_30[0x2];
	u8         souwce_weft_shiftew[0x6];
	u8         wesewved_at_38[0x8];
};

enum {
	MWX5DW_ASO_FWOW_METEW_NUM_PEW_OBJ = 2,
};

stwuct mwx5_ifc_ste_aso_fwow_metew_action_bits {
	u8         wesewved_at_0[0xc];
	u8         action[0x1];
	u8         initiaw_cowow[0x2];
	u8         wine_id[0x1];
};

stwuct mwx5_ifc_ste_doubwe_action_aso_v1_bits {
	u8         action_id[0x8];
	u8         aso_context_numbew[0x18];

	u8         dest_weg_id[0x2];
	u8         change_owdewing_tag[0x1];
	u8         aso_check_owdewing[0x1];
	u8         aso_context_type[0x4];
	u8         wesewved_at_28[0x8];
	union {
		u8 aso_fiewds[0x10];
		stwuct mwx5_ifc_ste_aso_fwow_metew_action_bits fwow_metew;
	};
};

#endif /* MWX5_IFC_DW_H */
