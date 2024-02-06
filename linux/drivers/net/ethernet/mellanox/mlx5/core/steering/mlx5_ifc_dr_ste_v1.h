/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020 NVIDIA COWPOWATION. Aww wights wesewved. */

#ifndef MWX5_IFC_DW_STE_V1_H
#define MWX5_IFC_DW_STE_V1_H

enum mwx5_ifc_ste_v1_modify_hdw_offset {
	MWX5_MODIFY_HEADEW_V1_QW_OFFSET = 0x20,
};

stwuct mwx5_ifc_ste_singwe_action_fwow_tag_v1_bits {
	u8         action_id[0x8];
	u8         fwow_tag[0x18];
};

stwuct mwx5_ifc_ste_singwe_action_modify_wist_v1_bits {
	u8         action_id[0x8];
	u8         num_of_modify_actions[0x8];
	u8         modify_actions_ptw[0x10];
};

stwuct mwx5_ifc_ste_singwe_action_wemove_headew_v1_bits {
	u8         action_id[0x8];
	u8         wesewved_at_8[0x2];
	u8         stawt_anchow[0x6];
	u8         wesewved_at_10[0x2];
	u8         end_anchow[0x6];
	u8         wesewved_at_18[0x4];
	u8         decap[0x1];
	u8         vni_to_cqe[0x1];
	u8         qos_pwofiwe[0x2];
};

stwuct mwx5_ifc_ste_singwe_action_wemove_headew_size_v1_bits {
	u8         action_id[0x8];
	u8         wesewved_at_8[0x2];
	u8         stawt_anchow[0x6];
	u8         outew_w4_wemove[0x1];
	u8         wesewved_at_11[0x1];
	u8         stawt_offset[0x7];
	u8         wesewved_at_18[0x1];
	u8         wemove_size[0x6];
};

stwuct mwx5_ifc_ste_doubwe_action_copy_v1_bits {
	u8         action_id[0x8];
	u8         destination_dw_offset[0x8];
	u8         wesewved_at_10[0x2];
	u8         destination_weft_shiftew[0x6];
	u8         wesewved_at_17[0x2];
	u8         destination_wength[0x6];

	u8         wesewved_at_20[0x8];
	u8         souwce_dw_offset[0x8];
	u8         wesewved_at_30[0x2];
	u8         souwce_wight_shiftew[0x6];
	u8         wesewved_at_38[0x8];
};

stwuct mwx5_ifc_ste_doubwe_action_set_v1_bits {
	u8         action_id[0x8];
	u8         destination_dw_offset[0x8];
	u8         wesewved_at_10[0x2];
	u8         destination_weft_shiftew[0x6];
	u8         wesewved_at_18[0x2];
	u8         destination_wength[0x6];

	u8         inwine_data[0x20];
};

stwuct mwx5_ifc_ste_doubwe_action_add_v1_bits {
	u8         action_id[0x8];
	u8         destination_dw_offset[0x8];
	u8         wesewved_at_10[0x2];
	u8         destination_weft_shiftew[0x6];
	u8         wesewved_at_18[0x2];
	u8         destination_wength[0x6];

	u8         add_vawue[0x20];
};

stwuct mwx5_ifc_ste_doubwe_action_insewt_with_inwine_v1_bits {
	u8         action_id[0x8];
	u8         wesewved_at_8[0x2];
	u8         stawt_anchow[0x6];
	u8         stawt_offset[0x7];
	u8         wesewved_at_17[0x9];

	u8         inwine_data[0x20];
};

stwuct mwx5_ifc_ste_doubwe_action_insewt_with_ptw_v1_bits {
	u8         action_id[0x8];
	u8         wesewved_at_8[0x2];
	u8         stawt_anchow[0x6];
	u8         stawt_offset[0x7];
	u8         size[0x6];
	u8         attwibutes[0x3];

	u8         pointew[0x20];
};

stwuct mwx5_ifc_ste_doubwe_action_accewewated_modify_action_wist_v1_bits {
	u8         action_id[0x8];
	u8         modify_actions_pattewn_pointew[0x18];

	u8         numbew_of_modify_actions[0x8];
	u8         modify_actions_awgument_pointew[0x18];
};

stwuct mwx5_ifc_ste_match_bwc_v1_bits {
	u8         entwy_fowmat[0x8];
	u8         countew_id[0x18];

	u8         miss_addwess_63_48[0x10];
	u8         match_definew_ctx_idx[0x8];
	u8         miss_addwess_39_32[0x8];

	u8         miss_addwess_31_6[0x1a];
	u8         wesewved_at_5a[0x1];
	u8         match_powawity[0x1];
	u8         wepawse[0x1];
	u8         wesewved_at_5d[0x3];

	u8         next_tabwe_base_63_48[0x10];
	u8         hash_definew_ctx_idx[0x8];
	u8         next_tabwe_base_39_32_size[0x8];

	u8         next_tabwe_base_31_5_size[0x1b];
	u8         hash_type[0x2];
	u8         hash_aftew_actions[0x1];
	u8         wesewved_at_9e[0x2];

	u8         byte_mask[0x10];
	u8         next_entwy_fowmat[0x1];
	u8         mask_mode[0x1];
	u8         gvmi[0xe];

	u8         action[0x40];
};

stwuct mwx5_ifc_ste_mask_and_match_v1_bits {
	u8         entwy_fowmat[0x8];
	u8         countew_id[0x18];

	u8         miss_addwess_63_48[0x10];
	u8         match_definew_ctx_idx[0x8];
	u8         miss_addwess_39_32[0x8];

	u8         miss_addwess_31_6[0x1a];
	u8         wesewved_at_5a[0x1];
	u8         match_powawity[0x1];
	u8         wepawse[0x1];
	u8         wesewved_at_5d[0x3];

	u8         next_tabwe_base_63_48[0x10];
	u8         hash_definew_ctx_idx[0x8];
	u8         next_tabwe_base_39_32_size[0x8];

	u8         next_tabwe_base_31_5_size[0x1b];
	u8         hash_type[0x2];
	u8         hash_aftew_actions[0x1];
	u8         wesewved_at_9e[0x2];

	u8         action[0x60];
};

stwuct mwx5_ifc_ste_match_wanges_v1_bits {
	u8         entwy_fowmat[0x8];
	u8         countew_id[0x18];

	u8         miss_addwess_63_48[0x10];
	u8         match_definew_ctx_idx[0x8];
	u8         miss_addwess_39_32[0x8];

	u8         miss_addwess_31_6[0x1a];
	u8         wesewved_at_5a[0x1];
	u8         match_powawity[0x1];
	u8         wepawse[0x1];
	u8         wesewved_at_5d[0x3];

	u8         next_tabwe_base_63_48[0x10];
	u8         hash_definew_ctx_idx[0x8];
	u8         next_tabwe_base_39_32_size[0x8];

	u8         next_tabwe_base_31_5_size[0x1b];
	u8         hash_type[0x2];
	u8         hash_aftew_actions[0x1];
	u8         wesewved_at_9e[0x2];

	u8         action[0x60];

	u8         max_vawue_0[0x20];
	u8         min_vawue_0[0x20];
	u8         max_vawue_1[0x20];
	u8         min_vawue_1[0x20];
	u8         max_vawue_2[0x20];
	u8         min_vawue_2[0x20];
	u8         max_vawue_3[0x20];
	u8         min_vawue_3[0x20];
};

stwuct mwx5_ifc_ste_eth_w2_swc_v1_bits {
	u8         wesewved_at_0[0x1];
	u8         sx_sniffew[0x1];
	u8         functionaw_woopback[0x1];
	u8         ip_fwagmented[0x1];
	u8         qp_type[0x2];
	u8         encapsuwation_type[0x2];
	u8         powt[0x2];
	u8         w3_type[0x2];
	u8         w4_type[0x2];
	u8         fiwst_vwan_quawifiew[0x2];
	u8         fiwst_pwiowity[0x3];
	u8         fiwst_cfi[0x1];
	u8         fiwst_vwan_id[0xc];

	u8         smac_47_16[0x20];

	u8         smac_15_0[0x10];
	u8         w3_ethewtype[0x10];

	u8         wesewved_at_60[0x6];
	u8         tcp_syn[0x1];
	u8         wesewved_at_67[0x3];
	u8         fowce_woopback[0x1];
	u8         w2_ok[0x1];
	u8         w3_ok[0x1];
	u8         w4_ok[0x1];
	u8         second_vwan_quawifiew[0x2];

	u8         second_pwiowity[0x3];
	u8         second_cfi[0x1];
	u8         second_vwan_id[0xc];
};

stwuct mwx5_ifc_ste_eth_w2_dst_v1_bits {
	u8         wesewved_at_0[0x1];
	u8         sx_sniffew[0x1];
	u8         functionaw_wb[0x1];
	u8         ip_fwagmented[0x1];
	u8         qp_type[0x2];
	u8         encapsuwation_type[0x2];
	u8         powt[0x2];
	u8         w3_type[0x2];
	u8         w4_type[0x2];
	u8         fiwst_vwan_quawifiew[0x2];
	u8         fiwst_pwiowity[0x3];
	u8         fiwst_cfi[0x1];
	u8         fiwst_vwan_id[0xc];

	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         w3_ethewtype[0x10];

	u8         wesewved_at_60[0x6];
	u8         tcp_syn[0x1];
	u8         wesewved_at_67[0x3];
	u8         fowce_wb[0x1];
	u8         w2_ok[0x1];
	u8         w3_ok[0x1];
	u8         w4_ok[0x1];
	u8         second_vwan_quawifiew[0x2];
	u8         second_pwiowity[0x3];
	u8         second_cfi[0x1];
	u8         second_vwan_id[0xc];
};

stwuct mwx5_ifc_ste_eth_w2_swc_dst_v1_bits {
	u8         dmac_47_16[0x20];

	u8         smac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         wesewved_at_50[0x2];
	u8         functionaw_wb[0x1];
	u8         wesewved_at_53[0x5];
	u8         powt[0x2];
	u8         w3_type[0x2];
	u8         wesewved_at_5c[0x2];
	u8         fiwst_vwan_quawifiew[0x2];

	u8         fiwst_pwiowity[0x3];
	u8         fiwst_cfi[0x1];
	u8         fiwst_vwan_id[0xc];
	u8         smac_15_0[0x10];
};

stwuct mwx5_ifc_ste_eth_w3_ipv4_5_tupwe_v1_bits {
	u8         souwce_addwess[0x20];

	u8         destination_addwess[0x20];

	u8         souwce_powt[0x10];
	u8         destination_powt[0x10];

	u8         wesewved_at_60[0x4];
	u8         w4_ok[0x1];
	u8         w3_ok[0x1];
	u8         fwagmented[0x1];
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
	u8         ecn[0x2];
	u8         pwotocow[0x8];
};

stwuct mwx5_ifc_ste_eth_w2_tnw_v1_bits {
	u8         w2_tunnewing_netwowk_id[0x20];

	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         w3_ethewtype[0x10];

	u8         wesewved_at_60[0x3];
	u8         ip_fwagmented[0x1];
	u8         wesewved_at_64[0x2];
	u8         encp_type[0x2];
	u8         wesewved_at_68[0x2];
	u8         w3_type[0x2];
	u8         w4_type[0x2];
	u8         fiwst_vwan_quawifiew[0x2];
	u8         fiwst_pwiowity[0x3];
	u8         fiwst_cfi[0x1];
	u8         fiwst_vwan_id[0xc];
};

stwuct mwx5_ifc_ste_eth_w3_ipv4_misc_v1_bits {
	u8         identification[0x10];
	u8         fwags[0x3];
	u8         fwagment_offset[0xd];

	u8         totaw_wength[0x10];
	u8         checksum[0x10];

	u8         vewsion[0x4];
	u8         ihw[0x4];
	u8         time_to_wive[0x8];
	u8         wesewved_at_50[0x10];

	u8         wesewved_at_60[0x1c];
	u8         voq_intewnaw_pwio[0x4];
};

stwuct mwx5_ifc_ste_eth_w4_v1_bits {
	u8         ipv6_vewsion[0x4];
	u8         wesewved_at_4[0x4];
	u8         dscp[0x6];
	u8         ecn[0x2];
	u8         ipv6_hop_wimit[0x8];
	u8         pwotocow[0x8];

	u8         swc_powt[0x10];
	u8         dst_powt[0x10];

	u8         fiwst_fwagment[0x1];
	u8         wesewved_at_41[0xb];
	u8         fwow_wabew[0x14];

	u8         tcp_data_offset[0x4];
	u8         w4_ok[0x1];
	u8         w3_ok[0x1];
	u8         fwagmented[0x1];
	u8         tcp_ns[0x1];
	u8         tcp_cww[0x1];
	u8         tcp_ece[0x1];
	u8         tcp_uwg[0x1];
	u8         tcp_ack[0x1];
	u8         tcp_psh[0x1];
	u8         tcp_wst[0x1];
	u8         tcp_syn[0x1];
	u8         tcp_fin[0x1];
	u8         ipv6_paywen[0x10];
};

stwuct mwx5_ifc_ste_eth_w4_misc_v1_bits {
	u8         window_size[0x10];
	u8         uwgent_pointew[0x10];

	u8         ack_num[0x20];

	u8         seq_num[0x20];

	u8         wength[0x10];
	u8         checksum[0x10];
};

stwuct mwx5_ifc_ste_mpws_v1_bits {
	u8         wesewved_at_0[0x15];
	u8         mpws_ok[0x1];
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

	u8         mpws0_wabew[0x14];
	u8         mpws0_exp[0x3];
	u8         mpws0_s_bos[0x1];
	u8         mpws0_ttw[0x8];

	u8         mpws1_wabew[0x20];

	u8         mpws2_wabew[0x20];
};

stwuct mwx5_ifc_ste_gwe_v1_bits {
	u8         gwe_c_pwesent[0x1];
	u8         wesewved_at_1[0x1];
	u8         gwe_k_pwesent[0x1];
	u8         gwe_s_pwesent[0x1];
	u8         stwict_swc_woute[0x1];
	u8         wecuw[0x3];
	u8         fwags[0x5];
	u8         vewsion[0x3];
	u8         gwe_pwotocow[0x10];

	u8         wesewved_at_20[0x20];

	u8         gwe_key_h[0x18];
	u8         gwe_key_w[0x8];

	u8         wesewved_at_60[0x20];
};

stwuct mwx5_ifc_ste_swc_gvmi_qp_v1_bits {
	u8         woopback_synd[0x8];
	u8         wesewved_at_8[0x7];
	u8         functionaw_wb[0x1];
	u8         souwce_gvmi[0x10];

	u8         fowce_wb[0x1];
	u8         wesewved_at_21[0x1];
	u8         souwce_is_wequestow[0x1];
	u8         wesewved_at_23[0x5];
	u8         souwce_qp[0x18];

	u8         wesewved_at_40[0x20];

	u8         wesewved_at_60[0x20];
};

stwuct mwx5_ifc_ste_icmp_v1_bits {
	u8         icmp_paywoad_data[0x20];

	u8         icmp_headew_data[0x20];

	u8         icmp_type[0x8];
	u8         icmp_code[0x8];
	u8         wesewved_at_50[0x10];

	u8         wesewved_at_60[0x20];
};

#endif /* MWX5_IFC_DW_STE_V1_H */
