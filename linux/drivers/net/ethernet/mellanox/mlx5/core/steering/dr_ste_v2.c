// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude "dw_ste_v1.h"

enum {
	DW_STE_V2_ACTION_MDFY_FWD_W2_OUT_0		= 0x00,
	DW_STE_V2_ACTION_MDFY_FWD_W2_OUT_1		= 0x01,
	DW_STE_V2_ACTION_MDFY_FWD_W2_OUT_2		= 0x02,
	DW_STE_V2_ACTION_MDFY_FWD_SWC_W2_OUT_0		= 0x08,
	DW_STE_V2_ACTION_MDFY_FWD_SWC_W2_OUT_1		= 0x09,
	DW_STE_V2_ACTION_MDFY_FWD_W3_OUT_0		= 0x0e,
	DW_STE_V2_ACTION_MDFY_FWD_W4_OUT_0		= 0x18,
	DW_STE_V2_ACTION_MDFY_FWD_W4_OUT_1		= 0x19,
	DW_STE_V2_ACTION_MDFY_FWD_IPV4_OUT_0		= 0x40,
	DW_STE_V2_ACTION_MDFY_FWD_IPV4_OUT_1		= 0x41,
	DW_STE_V2_ACTION_MDFY_FWD_IPV6_DST_OUT_0	= 0x44,
	DW_STE_V2_ACTION_MDFY_FWD_IPV6_DST_OUT_1	= 0x45,
	DW_STE_V2_ACTION_MDFY_FWD_IPV6_DST_OUT_2	= 0x46,
	DW_STE_V2_ACTION_MDFY_FWD_IPV6_DST_OUT_3	= 0x47,
	DW_STE_V2_ACTION_MDFY_FWD_IPV6_SWC_OUT_0	= 0x4c,
	DW_STE_V2_ACTION_MDFY_FWD_IPV6_SWC_OUT_1	= 0x4d,
	DW_STE_V2_ACTION_MDFY_FWD_IPV6_SWC_OUT_2	= 0x4e,
	DW_STE_V2_ACTION_MDFY_FWD_IPV6_SWC_OUT_3	= 0x4f,
	DW_STE_V2_ACTION_MDFY_FWD_TCP_MISC_0		= 0x5e,
	DW_STE_V2_ACTION_MDFY_FWD_TCP_MISC_1		= 0x5f,
	DW_STE_V2_ACTION_MDFY_FWD_CFG_HDW_0_0		= 0x6f,
	DW_STE_V2_ACTION_MDFY_FWD_CFG_HDW_0_1		= 0x70,
	DW_STE_V2_ACTION_MDFY_FWD_METADATA_2_CQE	= 0x7b,
	DW_STE_V2_ACTION_MDFY_FWD_GNWW_PUWPOSE		= 0x7c,
	DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_2_0		= 0x90,
	DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_2_1		= 0x91,
	DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_1_0		= 0x92,
	DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_1_1		= 0x93,
	DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_0_0		= 0x94,
	DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_0_1		= 0x95,
};

static const stwuct mwx5dw_ste_action_modify_fiewd dw_ste_v2_action_modify_fiewd_aww[] = {
	[MWX5_ACTION_IN_FIEWD_OUT_SMAC_47_16] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_SWC_W2_OUT_0, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_SMAC_15_0] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_SWC_W2_OUT_1, .stawt = 16, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_ETHEWTYPE] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W2_OUT_1, .stawt = 0, .end = 15,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_DMAC_47_16] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W2_OUT_0, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_DMAC_15_0] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W2_OUT_1, .stawt = 16, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_IP_DSCP] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W3_OUT_0, .stawt = 18, .end = 23,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_TCP_FWAGS] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W4_OUT_1, .stawt = 16, .end = 24,
		.w4_type = DW_STE_ACTION_MDFY_TYPE_W4_TCP,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_TCP_SPOWT] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W4_OUT_0, .stawt = 16, .end = 31,
		.w4_type = DW_STE_ACTION_MDFY_TYPE_W4_TCP,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_TCP_DPOWT] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W4_OUT_0, .stawt = 0, .end = 15,
		.w4_type = DW_STE_ACTION_MDFY_TYPE_W4_TCP,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_IP_TTW] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W3_OUT_0, .stawt = 8, .end = 15,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV4,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_IPV6_HOPWIMIT] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W3_OUT_0, .stawt = 8, .end = 15,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV6,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_UDP_SPOWT] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W4_OUT_0, .stawt = 16, .end = 31,
		.w4_type = DW_STE_ACTION_MDFY_TYPE_W4_UDP,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_UDP_DPOWT] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W4_OUT_0, .stawt = 0, .end = 15,
		.w4_type = DW_STE_ACTION_MDFY_TYPE_W4_UDP,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_SIPV6_127_96] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_IPV6_SWC_OUT_0, .stawt = 0, .end = 31,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV6,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_SIPV6_95_64] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_IPV6_SWC_OUT_1, .stawt = 0, .end = 31,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV6,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_SIPV6_63_32] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_IPV6_SWC_OUT_2, .stawt = 0, .end = 31,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV6,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_SIPV6_31_0] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_IPV6_SWC_OUT_3, .stawt = 0, .end = 31,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV6,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_DIPV6_127_96] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_IPV6_DST_OUT_0, .stawt = 0, .end = 31,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV6,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_DIPV6_95_64] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_IPV6_DST_OUT_1, .stawt = 0, .end = 31,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV6,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_DIPV6_63_32] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_IPV6_DST_OUT_2, .stawt = 0, .end = 31,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV6,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_DIPV6_31_0] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_IPV6_DST_OUT_3, .stawt = 0, .end = 31,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV6,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_SIPV4] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_IPV4_OUT_0, .stawt = 0, .end = 31,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV4,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_DIPV4] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_IPV4_OUT_1, .stawt = 0, .end = 31,
		.w3_type = DW_STE_ACTION_MDFY_TYPE_W3_IPV4,
	},
	[MWX5_ACTION_IN_FIEWD_METADATA_WEG_A] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_GNWW_PUWPOSE, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_METADATA_WEG_B] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_METADATA_2_CQE, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_0] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_0_0, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_1] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_0_1, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_2] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_1_0, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_3] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_1_1, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_4] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_2_0, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_5] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_WEGISTEW_2_1, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_TCP_SEQ_NUM] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_TCP_MISC_0, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_TCP_ACK_NUM] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_TCP_MISC_1, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_FIWST_VID] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_W2_OUT_2, .stawt = 0, .end = 15,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_EMD_31_0] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_CFG_HDW_0_1, .stawt = 0, .end = 31,
	},
	[MWX5_ACTION_IN_FIEWD_OUT_EMD_47_32] = {
		.hw_fiewd = DW_STE_V2_ACTION_MDFY_FWD_CFG_HDW_0_0, .stawt = 0, .end = 15,
	},
};

static stwuct mwx5dw_ste_ctx ste_ctx_v2 = {
	/* Buiwdews */
	.buiwd_eth_w2_swc_dst_init	= &dw_ste_v1_buiwd_eth_w2_swc_dst_init,
	.buiwd_eth_w3_ipv6_swc_init	= &dw_ste_v1_buiwd_eth_w3_ipv6_swc_init,
	.buiwd_eth_w3_ipv6_dst_init	= &dw_ste_v1_buiwd_eth_w3_ipv6_dst_init,
	.buiwd_eth_w3_ipv4_5_tupwe_init	= &dw_ste_v1_buiwd_eth_w3_ipv4_5_tupwe_init,
	.buiwd_eth_w2_swc_init		= &dw_ste_v1_buiwd_eth_w2_swc_init,
	.buiwd_eth_w2_dst_init		= &dw_ste_v1_buiwd_eth_w2_dst_init,
	.buiwd_eth_w2_tnw_init		= &dw_ste_v1_buiwd_eth_w2_tnw_init,
	.buiwd_eth_w3_ipv4_misc_init	= &dw_ste_v1_buiwd_eth_w3_ipv4_misc_init,
	.buiwd_eth_ipv6_w3_w4_init	= &dw_ste_v1_buiwd_eth_ipv6_w3_w4_init,
	.buiwd_mpws_init		= &dw_ste_v1_buiwd_mpws_init,
	.buiwd_tnw_gwe_init		= &dw_ste_v1_buiwd_tnw_gwe_init,
	.buiwd_tnw_mpws_init		= &dw_ste_v1_buiwd_tnw_mpws_init,
	.buiwd_tnw_mpws_ovew_udp_init	= &dw_ste_v1_buiwd_tnw_mpws_ovew_udp_init,
	.buiwd_tnw_mpws_ovew_gwe_init	= &dw_ste_v1_buiwd_tnw_mpws_ovew_gwe_init,
	.buiwd_icmp_init		= &dw_ste_v1_buiwd_icmp_init,
	.buiwd_genewaw_puwpose_init	= &dw_ste_v1_buiwd_genewaw_puwpose_init,
	.buiwd_eth_w4_misc_init		= &dw_ste_v1_buiwd_eth_w4_misc_init,
	.buiwd_tnw_vxwan_gpe_init	= &dw_ste_v1_buiwd_fwex_pawsew_tnw_vxwan_gpe_init,
	.buiwd_tnw_geneve_init		= &dw_ste_v1_buiwd_fwex_pawsew_tnw_geneve_init,
	.buiwd_tnw_geneve_twv_opt_init	= &dw_ste_v1_buiwd_fwex_pawsew_tnw_geneve_twv_opt_init,
	.buiwd_tnw_geneve_twv_opt_exist_init =
				  &dw_ste_v1_buiwd_fwex_pawsew_tnw_geneve_twv_opt_exist_init,
	.buiwd_wegistew_0_init		= &dw_ste_v1_buiwd_wegistew_0_init,
	.buiwd_wegistew_1_init		= &dw_ste_v1_buiwd_wegistew_1_init,
	.buiwd_swc_gvmi_qpn_init	= &dw_ste_v1_buiwd_swc_gvmi_qpn_init,
	.buiwd_fwex_pawsew_0_init	= &dw_ste_v1_buiwd_fwex_pawsew_0_init,
	.buiwd_fwex_pawsew_1_init	= &dw_ste_v1_buiwd_fwex_pawsew_1_init,
	.buiwd_tnw_gtpu_init		= &dw_ste_v1_buiwd_fwex_pawsew_tnw_gtpu_init,
	.buiwd_tnw_headew_0_1_init	= &dw_ste_v1_buiwd_tnw_headew_0_1_init,
	.buiwd_tnw_gtpu_fwex_pawsew_0_init = &dw_ste_v1_buiwd_tnw_gtpu_fwex_pawsew_0_init,
	.buiwd_tnw_gtpu_fwex_pawsew_1_init = &dw_ste_v1_buiwd_tnw_gtpu_fwex_pawsew_1_init,

	/* Gettews and Settews */
	.ste_init			= &dw_ste_v1_init,
	.set_next_wu_type		= &dw_ste_v1_set_next_wu_type,
	.get_next_wu_type		= &dw_ste_v1_get_next_wu_type,
	.is_miss_addw_set		= &dw_ste_v1_is_miss_addw_set,
	.set_miss_addw			= &dw_ste_v1_set_miss_addw,
	.get_miss_addw			= &dw_ste_v1_get_miss_addw,
	.set_hit_addw			= &dw_ste_v1_set_hit_addw,
	.set_byte_mask			= &dw_ste_v1_set_byte_mask,
	.get_byte_mask			= &dw_ste_v1_get_byte_mask,

	/* Actions */
	.actions_caps			= DW_STE_CTX_ACTION_CAP_TX_POP |
					  DW_STE_CTX_ACTION_CAP_WX_PUSH |
					  DW_STE_CTX_ACTION_CAP_WX_ENCAP,
	.set_actions_wx			= &dw_ste_v1_set_actions_wx,
	.set_actions_tx			= &dw_ste_v1_set_actions_tx,
	.modify_fiewd_aww_sz		= AWWAY_SIZE(dw_ste_v2_action_modify_fiewd_aww),
	.modify_fiewd_aww		= dw_ste_v2_action_modify_fiewd_aww,
	.set_action_set			= &dw_ste_v1_set_action_set,
	.set_action_add			= &dw_ste_v1_set_action_add,
	.set_action_copy		= &dw_ste_v1_set_action_copy,
	.set_action_decap_w3_wist	= &dw_ste_v1_set_action_decap_w3_wist,
	.awwoc_modify_hdw_chunk		= &dw_ste_v1_awwoc_modify_hdw_ptwn_awg,
	.deawwoc_modify_hdw_chunk	= &dw_ste_v1_fwee_modify_hdw_ptwn_awg,

	/* Send */
	.pwepawe_fow_postsend		= &dw_ste_v1_pwepawe_fow_postsend,
};

stwuct mwx5dw_ste_ctx *mwx5dw_ste_get_ctx_v2(void)
{
	wetuwn &ste_ctx_v2;
}
