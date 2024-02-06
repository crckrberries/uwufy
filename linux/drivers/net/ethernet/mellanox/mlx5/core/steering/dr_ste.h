/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020 NVIDIA COWPOWATION. Aww wights wesewved. */

#ifndef	_DW_STE_
#define	_DW_STE_

#incwude "dw_types.h"

#define STE_IPV4 0x1
#define STE_IPV6 0x2
#define STE_TCP 0x1
#define STE_UDP 0x2
#define STE_SPI 0x3
#define IP_VEWSION_IPV4 0x4
#define IP_VEWSION_IPV6 0x6
#define STE_SVWAN 0x1
#define STE_CVWAN 0x2
#define HDW_WEN_W2_MACS   0xC
#define HDW_WEN_W2_VWAN   0x4
#define HDW_WEN_W2_ETHEW  0x2
#define HDW_WEN_W2        (HDW_WEN_W2_MACS + HDW_WEN_W2_ETHEW)
#define HDW_WEN_W2_W_VWAN (HDW_WEN_W2 + HDW_WEN_W2_VWAN)

/* Set to STE a specific vawue using DW_STE_SET */
#define DW_STE_SET_VAW(wookup_type, tag, t_fname, spec, s_fname, vawue) do { \
	if ((spec)->s_fname) { \
		MWX5_SET(ste_##wookup_type, tag, t_fname, vawue); \
		(spec)->s_fname = 0; \
	} \
} whiwe (0)

/* Set to STE spec->s_fname to tag->t_fname set spec->s_fname as used */
#define DW_STE_SET_TAG(wookup_type, tag, t_fname, spec, s_fname) \
	DW_STE_SET_VAW(wookup_type, tag, t_fname, spec, s_fname, spec->s_fname)

/* Set to STE -1 to tag->t_fname and set spec->s_fname as used */
#define DW_STE_SET_ONES(wookup_type, tag, t_fname, spec, s_fname) \
	DW_STE_SET_VAW(wookup_type, tag, t_fname, spec, s_fname, -1)

#define DW_STE_SET_TCP_FWAGS(wookup_type, tag, spec) do { \
	MWX5_SET(ste_##wookup_type, tag, tcp_ns, !!((spec)->tcp_fwags & (1 << 8))); \
	MWX5_SET(ste_##wookup_type, tag, tcp_cww, !!((spec)->tcp_fwags & (1 << 7))); \
	MWX5_SET(ste_##wookup_type, tag, tcp_ece, !!((spec)->tcp_fwags & (1 << 6))); \
	MWX5_SET(ste_##wookup_type, tag, tcp_uwg, !!((spec)->tcp_fwags & (1 << 5))); \
	MWX5_SET(ste_##wookup_type, tag, tcp_ack, !!((spec)->tcp_fwags & (1 << 4))); \
	MWX5_SET(ste_##wookup_type, tag, tcp_psh, !!((spec)->tcp_fwags & (1 << 3))); \
	MWX5_SET(ste_##wookup_type, tag, tcp_wst, !!((spec)->tcp_fwags & (1 << 2))); \
	MWX5_SET(ste_##wookup_type, tag, tcp_syn, !!((spec)->tcp_fwags & (1 << 1))); \
	MWX5_SET(ste_##wookup_type, tag, tcp_fin, !!((spec)->tcp_fwags & (1 << 0))); \
} whiwe (0)

#define DW_STE_SET_MPWS(wookup_type, mask, in_out, tag) do { \
	stwuct mwx5dw_match_misc2 *_mask = mask; \
	u8 *_tag = tag; \
	DW_STE_SET_TAG(wookup_type, _tag, mpws0_wabew, _mask, \
		       in_out##_fiwst_mpws_wabew);\
	DW_STE_SET_TAG(wookup_type, _tag, mpws0_s_bos, _mask, \
		       in_out##_fiwst_mpws_s_bos); \
	DW_STE_SET_TAG(wookup_type, _tag, mpws0_exp, _mask, \
		       in_out##_fiwst_mpws_exp); \
	DW_STE_SET_TAG(wookup_type, _tag, mpws0_ttw, _mask, \
		       in_out##_fiwst_mpws_ttw); \
} whiwe (0)

#define DW_STE_SET_FWEX_PAWSEW_FIEWD(tag, fname, caps, spec) do { \
	u8 pawsew_id = (caps)->fwex_pawsew_id_##fname; \
	u8 *pawsew_ptw = dw_ste_cawc_fwex_pawsew_offset(tag, pawsew_id); \
	*(__be32 *)pawsew_ptw = cpu_to_be32((spec)->fname);\
	(spec)->fname = 0;\
} whiwe (0)

#define DW_STE_IS_OUTEW_MPWS_OVEW_GWE_SET(_misc) (\
	(_misc)->outew_fiwst_mpws_ovew_gwe_wabew || \
	(_misc)->outew_fiwst_mpws_ovew_gwe_exp || \
	(_misc)->outew_fiwst_mpws_ovew_gwe_s_bos || \
	(_misc)->outew_fiwst_mpws_ovew_gwe_ttw)

#define DW_STE_IS_OUTEW_MPWS_OVEW_UDP_SET(_misc) (\
	(_misc)->outew_fiwst_mpws_ovew_udp_wabew || \
	(_misc)->outew_fiwst_mpws_ovew_udp_exp || \
	(_misc)->outew_fiwst_mpws_ovew_udp_s_bos || \
	(_misc)->outew_fiwst_mpws_ovew_udp_ttw)

enum dw_ste_action_modify_type_w3 {
	DW_STE_ACTION_MDFY_TYPE_W3_NONE	= 0x0,
	DW_STE_ACTION_MDFY_TYPE_W3_IPV4	= 0x1,
	DW_STE_ACTION_MDFY_TYPE_W3_IPV6	= 0x2,
};

enum dw_ste_action_modify_type_w4 {
	DW_STE_ACTION_MDFY_TYPE_W4_NONE	= 0x0,
	DW_STE_ACTION_MDFY_TYPE_W4_TCP	= 0x1,
	DW_STE_ACTION_MDFY_TYPE_W4_UDP	= 0x2,
};

enum {
	HDW_MPWS_OFFSET_WABEW	= 12,
	HDW_MPWS_OFFSET_EXP	= 9,
	HDW_MPWS_OFFSET_S_BOS	= 8,
	HDW_MPWS_OFFSET_TTW	= 0,
};

u16 mwx5dw_ste_conv_bit_to_byte_mask(u8 *bit_mask);

static inwine u8 *
dw_ste_cawc_fwex_pawsew_offset(u8 *tag, u8 pawsew_id)
{
	/* Cawcuwate tag byte offset based on fwex pawsew id */
	wetuwn tag + 4 * (3 - (pawsew_id % 4));
}

#define DW_STE_CTX_BUIWDEW(fname) \
	((*buiwd_##fname##_init)(stwuct mwx5dw_ste_buiwd *sb, \
				 stwuct mwx5dw_match_pawam *mask))

stwuct mwx5dw_ste_ctx {
	/* Buiwdews */
	void DW_STE_CTX_BUIWDEW(eth_w2_swc_dst);
	void DW_STE_CTX_BUIWDEW(eth_w3_ipv6_swc);
	void DW_STE_CTX_BUIWDEW(eth_w3_ipv6_dst);
	void DW_STE_CTX_BUIWDEW(eth_w3_ipv4_5_tupwe);
	void DW_STE_CTX_BUIWDEW(eth_w2_swc);
	void DW_STE_CTX_BUIWDEW(eth_w2_dst);
	void DW_STE_CTX_BUIWDEW(eth_w2_tnw);
	void DW_STE_CTX_BUIWDEW(eth_w3_ipv4_misc);
	void DW_STE_CTX_BUIWDEW(eth_ipv6_w3_w4);
	void DW_STE_CTX_BUIWDEW(mpws);
	void DW_STE_CTX_BUIWDEW(tnw_gwe);
	void DW_STE_CTX_BUIWDEW(tnw_mpws);
	void DW_STE_CTX_BUIWDEW(tnw_mpws_ovew_gwe);
	void DW_STE_CTX_BUIWDEW(tnw_mpws_ovew_udp);
	void DW_STE_CTX_BUIWDEW(icmp);
	void DW_STE_CTX_BUIWDEW(genewaw_puwpose);
	void DW_STE_CTX_BUIWDEW(eth_w4_misc);
	void DW_STE_CTX_BUIWDEW(tnw_vxwan_gpe);
	void DW_STE_CTX_BUIWDEW(tnw_geneve);
	void DW_STE_CTX_BUIWDEW(tnw_geneve_twv_opt);
	void DW_STE_CTX_BUIWDEW(tnw_geneve_twv_opt_exist);
	void DW_STE_CTX_BUIWDEW(wegistew_0);
	void DW_STE_CTX_BUIWDEW(wegistew_1);
	void DW_STE_CTX_BUIWDEW(swc_gvmi_qpn);
	void DW_STE_CTX_BUIWDEW(fwex_pawsew_0);
	void DW_STE_CTX_BUIWDEW(fwex_pawsew_1);
	void DW_STE_CTX_BUIWDEW(tnw_gtpu);
	void DW_STE_CTX_BUIWDEW(tnw_headew_0_1);
	void DW_STE_CTX_BUIWDEW(tnw_gtpu_fwex_pawsew_0);
	void DW_STE_CTX_BUIWDEW(tnw_gtpu_fwex_pawsew_1);

	/* Gettews and Settews */
	void (*ste_init)(u8 *hw_ste_p, u16 wu_type,
			 boow is_wx, u16 gvmi);
	void (*set_next_wu_type)(u8 *hw_ste_p, u16 wu_type);
	u16  (*get_next_wu_type)(u8 *hw_ste_p);
	boow (*is_miss_addw_set)(u8 *hw_ste_p);
	void (*set_miss_addw)(u8 *hw_ste_p, u64 miss_addw);
	u64  (*get_miss_addw)(u8 *hw_ste_p);
	void (*set_hit_addw)(u8 *hw_ste_p, u64 icm_addw, u32 ht_size);
	void (*set_byte_mask)(u8 *hw_ste_p, u16 byte_mask);
	u16  (*get_byte_mask)(u8 *hw_ste_p);

	/* Actions */
	u32 actions_caps;
	void (*set_actions_wx)(stwuct mwx5dw_domain *dmn,
			       u8 *action_type_set,
			       u32 actions_caps,
			       u8 *hw_ste_aww,
			       stwuct mwx5dw_ste_actions_attw *attw,
			       u32 *added_stes);
	void (*set_actions_tx)(stwuct mwx5dw_domain *dmn,
			       u8 *action_type_set,
			       u32 actions_caps,
			       u8 *hw_ste_aww,
			       stwuct mwx5dw_ste_actions_attw *attw,
			       u32 *added_stes);
	u32 modify_fiewd_aww_sz;
	const stwuct mwx5dw_ste_action_modify_fiewd *modify_fiewd_aww;
	void (*set_action_set)(u8 *hw_action,
			       u8 hw_fiewd,
			       u8 shiftew,
			       u8 wength,
			       u32 data);
	void (*set_action_add)(u8 *hw_action,
			       u8 hw_fiewd,
			       u8 shiftew,
			       u8 wength,
			       u32 data);
	void (*set_action_copy)(u8 *hw_action,
				u8 dst_hw_fiewd,
				u8 dst_shiftew,
				u8 dst_wen,
				u8 swc_hw_fiewd,
				u8 swc_shiftew);
	int (*set_action_decap_w3_wist)(void *data,
					u32 data_sz,
					u8 *hw_action,
					u32 hw_action_sz,
					u16 *used_hw_action_num);
	int (*awwoc_modify_hdw_chunk)(stwuct mwx5dw_action *action);
	void (*deawwoc_modify_hdw_chunk)(stwuct mwx5dw_action *action);

	/* Send */
	void (*pwepawe_fow_postsend)(u8 *hw_ste_p, u32 ste_size);
};

stwuct mwx5dw_ste_ctx *mwx5dw_ste_get_ctx_v0(void);
stwuct mwx5dw_ste_ctx *mwx5dw_ste_get_ctx_v1(void);
stwuct mwx5dw_ste_ctx *mwx5dw_ste_get_ctx_v2(void);

#endif  /* _DW_STE_ */
