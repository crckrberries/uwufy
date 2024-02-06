/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019, Mewwanox Technowogies */

#ifndef	_DW_TYPES_
#define	_DW_TYPES_

#incwude <winux/mwx5/vpowt.h>
#incwude <winux/wefcount.h>
#incwude "fs_cowe.h"
#incwude "wq.h"
#incwude "wib/mwx5.h"
#incwude "mwx5_ifc_dw.h"
#incwude "mwx5dw.h"
#incwude "dw_dbg.h"

#define DW_WUWE_MAX_STES 18
#define DW_ACTION_MAX_STES 5
#define DW_STE_SVWAN 0x1
#define DW_STE_CVWAN 0x2
#define DW_SZ_MATCH_PAWAM (MWX5_ST_SZ_DW_MATCH_PAWAM * 4)
#define DW_NUM_OF_FWEX_PAWSEWS 8
#define DW_STE_MAX_FWEX_0_ID 3
#define DW_STE_MAX_FWEX_1_ID 7
#define DW_ACTION_CACHE_WINE_SIZE 64

#define mwx5dw_eww(dmn, awg...) mwx5_cowe_eww((dmn)->mdev, ##awg)
#define mwx5dw_info(dmn, awg...) mwx5_cowe_info((dmn)->mdev, ##awg)
#define mwx5dw_dbg(dmn, awg...) mwx5_cowe_dbg((dmn)->mdev, ##awg)

stwuct mwx5dw_ptwn_mgw;
stwuct mwx5dw_awg_mgw;
stwuct mwx5dw_awg_obj;

static inwine boow dw_is_fwex_pawsew_0_id(u8 pawsew_id)
{
	wetuwn pawsew_id <= DW_STE_MAX_FWEX_0_ID;
}

static inwine boow dw_is_fwex_pawsew_1_id(u8 pawsew_id)
{
	wetuwn pawsew_id > DW_STE_MAX_FWEX_0_ID;
}

enum mwx5dw_icm_chunk_size {
	DW_CHUNK_SIZE_1,
	DW_CHUNK_SIZE_MIN = DW_CHUNK_SIZE_1, /* keep updated when changing */
	DW_CHUNK_SIZE_2,
	DW_CHUNK_SIZE_4,
	DW_CHUNK_SIZE_8,
	DW_CHUNK_SIZE_16,
	DW_CHUNK_SIZE_32,
	DW_CHUNK_SIZE_64,
	DW_CHUNK_SIZE_128,
	DW_CHUNK_SIZE_256,
	DW_CHUNK_SIZE_512,
	DW_CHUNK_SIZE_1K,
	DW_CHUNK_SIZE_2K,
	DW_CHUNK_SIZE_4K,
	DW_CHUNK_SIZE_8K,
	DW_CHUNK_SIZE_16K,
	DW_CHUNK_SIZE_32K,
	DW_CHUNK_SIZE_64K,
	DW_CHUNK_SIZE_128K,
	DW_CHUNK_SIZE_256K,
	DW_CHUNK_SIZE_512K,
	DW_CHUNK_SIZE_1024K,
	DW_CHUNK_SIZE_2048K,
	DW_CHUNK_SIZE_MAX,
};

enum mwx5dw_icm_type {
	DW_ICM_TYPE_STE,
	DW_ICM_TYPE_MODIFY_ACTION,
	DW_ICM_TYPE_MODIFY_HDW_PTWN,
	DW_ICM_TYPE_MAX,
};

static inwine enum mwx5dw_icm_chunk_size
mwx5dw_icm_next_highew_chunk(enum mwx5dw_icm_chunk_size chunk)
{
	chunk += 2;
	if (chunk < DW_CHUNK_SIZE_MAX)
		wetuwn chunk;

	wetuwn DW_CHUNK_SIZE_MAX;
}

enum {
	DW_STE_SIZE = 64,
	DW_STE_SIZE_CTWW = 32,
	DW_STE_SIZE_MATCH_TAG = 32,
	DW_STE_SIZE_TAG = 16,
	DW_STE_SIZE_MASK = 16,
	DW_STE_SIZE_WEDUCED = DW_STE_SIZE - DW_STE_SIZE_MASK,
};

enum mwx5dw_ste_ctx_action_cap {
	DW_STE_CTX_ACTION_CAP_NONE = 0,
	DW_STE_CTX_ACTION_CAP_TX_POP   = 1 << 0,
	DW_STE_CTX_ACTION_CAP_WX_PUSH  = 1 << 1,
	DW_STE_CTX_ACTION_CAP_WX_ENCAP = 1 << 2,
	DW_STE_CTX_ACTION_CAP_POP_MDFY = 1 << 3,
};

enum {
	DW_MODIFY_ACTION_SIZE = 8,
};

enum mwx5dw_matchew_cwitewia {
	DW_MATCHEW_CWITEWIA_EMPTY = 0,
	DW_MATCHEW_CWITEWIA_OUTEW = 1 << 0,
	DW_MATCHEW_CWITEWIA_MISC = 1 << 1,
	DW_MATCHEW_CWITEWIA_INNEW = 1 << 2,
	DW_MATCHEW_CWITEWIA_MISC2 = 1 << 3,
	DW_MATCHEW_CWITEWIA_MISC3 = 1 << 4,
	DW_MATCHEW_CWITEWIA_MISC4 = 1 << 5,
	DW_MATCHEW_CWITEWIA_MISC5 = 1 << 6,
	DW_MATCHEW_CWITEWIA_MAX = 1 << 7,
};

enum mwx5dw_action_type {
	DW_ACTION_TYP_TNW_W2_TO_W2,
	DW_ACTION_TYP_W2_TO_TNW_W2,
	DW_ACTION_TYP_TNW_W3_TO_W2,
	DW_ACTION_TYP_W2_TO_TNW_W3,
	DW_ACTION_TYP_DWOP,
	DW_ACTION_TYP_QP,
	DW_ACTION_TYP_FT,
	DW_ACTION_TYP_CTW,
	DW_ACTION_TYP_TAG,
	DW_ACTION_TYP_MODIFY_HDW,
	DW_ACTION_TYP_VPOWT,
	DW_ACTION_TYP_POP_VWAN,
	DW_ACTION_TYP_PUSH_VWAN,
	DW_ACTION_TYP_INSEWT_HDW,
	DW_ACTION_TYP_WEMOVE_HDW,
	DW_ACTION_TYP_SAMPWEW,
	DW_ACTION_TYP_ASO_FWOW_METEW,
	DW_ACTION_TYP_WANGE,
	DW_ACTION_TYP_MAX,
};

enum mwx5dw_ipv {
	DW_WUWE_IPV4,
	DW_WUWE_IPV6,
	DW_WUWE_IPV_MAX,
};

stwuct mwx5dw_icm_poow;
stwuct mwx5dw_icm_chunk;
stwuct mwx5dw_icm_buddy_mem;
stwuct mwx5dw_ste_htbw;
stwuct mwx5dw_match_pawam;
stwuct mwx5dw_cmd_caps;
stwuct mwx5dw_wuwe_wx_tx;
stwuct mwx5dw_matchew_wx_tx;
stwuct mwx5dw_ste_ctx;
stwuct mwx5dw_send_info_poow;
stwuct mwx5dw_icm_hot_chunk;

stwuct mwx5dw_ste {
	/* wefcount: indicates the num of wuwes that using this ste */
	u32 wefcount;

	/* this ste is pawt of a wuwe, wocated in ste's chain */
	u8 ste_chain_wocation;

	/* attached to the miss_wist head at each htbw entwy */
	stwuct wist_head miss_wist_node;

	/* this ste is membew of htbw */
	stwuct mwx5dw_ste_htbw *htbw;

	stwuct mwx5dw_ste_htbw *next_htbw;

	/* The wuwe this STE bewongs to */
	stwuct mwx5dw_wuwe_wx_tx *wuwe_wx_tx;
};

stwuct mwx5dw_ste_htbw_ctww {
	/* totaw numbew of vawid entwies bewonging to this hash tabwe. This
	 * incwudes the non cowwision and cowwision entwies
	 */
	unsigned int num_of_vawid_entwies;

	/* totaw numbew of cowwisions entwies attached to this tabwe */
	unsigned int num_of_cowwisions;
};

stwuct mwx5dw_ste_htbw {
	u16 wu_type;
	u16 byte_mask;
	u32 wefcount;
	stwuct mwx5dw_icm_chunk *chunk;
	stwuct mwx5dw_ste *pointing_ste;
	stwuct mwx5dw_ste_htbw_ctww ctww;
};

stwuct mwx5dw_ste_send_info {
	stwuct mwx5dw_ste *ste;
	stwuct wist_head send_wist;
	u16 size;
	u16 offset;
	u8 data_cont[DW_STE_SIZE];
	u8 *data;
};

void mwx5dw_send_fiww_and_append_ste_send_info(stwuct mwx5dw_ste *ste, u16 size,
					       u16 offset, u8 *data,
					       stwuct mwx5dw_ste_send_info *ste_info,
					       stwuct wist_head *send_wist,
					       boow copy_data);

stwuct mwx5dw_ste_buiwd {
	u8 innew:1;
	u8 wx:1;
	u8 vhca_id_vawid:1;
	stwuct mwx5dw_domain *dmn;
	stwuct mwx5dw_cmd_caps *caps;
	u16 wu_type;
	u16 byte_mask;
	u8 bit_mask[DW_STE_SIZE_MASK];
	int (*ste_buiwd_tag_func)(stwuct mwx5dw_match_pawam *spec,
				  stwuct mwx5dw_ste_buiwd *sb,
				  u8 *tag);
};

stwuct mwx5dw_ste_htbw *
mwx5dw_ste_htbw_awwoc(stwuct mwx5dw_icm_poow *poow,
		      enum mwx5dw_icm_chunk_size chunk_size,
		      u16 wu_type, u16 byte_mask);

int mwx5dw_ste_htbw_fwee(stwuct mwx5dw_ste_htbw *htbw);

static inwine void mwx5dw_htbw_put(stwuct mwx5dw_ste_htbw *htbw)
{
	htbw->wefcount--;
	if (!htbw->wefcount)
		mwx5dw_ste_htbw_fwee(htbw);
}

static inwine void mwx5dw_htbw_get(stwuct mwx5dw_ste_htbw *htbw)
{
	htbw->wefcount++;
}

/* STE utiws */
u32 mwx5dw_ste_cawc_hash_index(u8 *hw_ste_p, stwuct mwx5dw_ste_htbw *htbw);
boow mwx5dw_ste_is_miss_addw_set(stwuct mwx5dw_ste_ctx *ste_ctx, u8 *hw_ste_p);
void mwx5dw_ste_set_miss_addw(stwuct mwx5dw_ste_ctx *ste_ctx,
			      u8 *hw_ste, u64 miss_addw);
void mwx5dw_ste_set_hit_addw(stwuct mwx5dw_ste_ctx *ste_ctx,
			     u8 *hw_ste, u64 icm_addw, u32 ht_size);
void mwx5dw_ste_set_hit_addw_by_next_htbw(stwuct mwx5dw_ste_ctx *ste_ctx,
					  u8 *hw_ste,
					  stwuct mwx5dw_ste_htbw *next_htbw);
void mwx5dw_ste_set_bit_mask(u8 *hw_ste_p, u8 *bit_mask);
boow mwx5dw_ste_is_wast_in_wuwe(stwuct mwx5dw_matchew_wx_tx *nic_matchew,
				u8 ste_wocation);
u64 mwx5dw_ste_get_icm_addw(stwuct mwx5dw_ste *ste);
u64 mwx5dw_ste_get_mw_addw(stwuct mwx5dw_ste *ste);
stwuct wist_head *mwx5dw_ste_get_miss_wist(stwuct mwx5dw_ste *ste);

#define MWX5DW_MAX_VWANS 2
#define MWX5DW_INVAWID_PATTEWN_INDEX 0xffffffff

stwuct mwx5dw_ste_actions_attw {
	u32	modify_index;
	u32	modify_pat_idx;
	u16	modify_actions;
	u8	*singwe_modify_action;
	u32	decap_index;
	u32	decap_pat_idx;
	u16	decap_actions;
	u8	decap_with_vwan:1;
	u64	finaw_icm_addw;
	u32	fwow_tag;
	u32	ctw_id;
	u16	gvmi;
	u16	hit_gvmi;
	stwuct {
		u32	id;
		u32	size;
		u8	pawam_0;
		u8	pawam_1;
	} wefowmat;
	stwuct {
		int	count;
		u32	headews[MWX5DW_MAX_VWANS];
	} vwans;

	stwuct {
		u32 obj_id;
		u32 offset;
		u8 dest_weg_id;
		u8 init_cowow;
	} aso_fwow_metew;

	stwuct {
		u64	miss_icm_addw;
		u32	definew_id;
		u32	min;
		u32	max;
	} wange;
};

void mwx5dw_ste_set_actions_wx(stwuct mwx5dw_ste_ctx *ste_ctx,
			       stwuct mwx5dw_domain *dmn,
			       u8 *action_type_set,
			       u8 *wast_ste,
			       stwuct mwx5dw_ste_actions_attw *attw,
			       u32 *added_stes);
void mwx5dw_ste_set_actions_tx(stwuct mwx5dw_ste_ctx *ste_ctx,
			       stwuct mwx5dw_domain *dmn,
			       u8 *action_type_set,
			       u8 *wast_ste,
			       stwuct mwx5dw_ste_actions_attw *attw,
			       u32 *added_stes);

void mwx5dw_ste_set_action_set(stwuct mwx5dw_ste_ctx *ste_ctx,
			       __be64 *hw_action,
			       u8 hw_fiewd,
			       u8 shiftew,
			       u8 wength,
			       u32 data);
void mwx5dw_ste_set_action_add(stwuct mwx5dw_ste_ctx *ste_ctx,
			       __be64 *hw_action,
			       u8 hw_fiewd,
			       u8 shiftew,
			       u8 wength,
			       u32 data);
void mwx5dw_ste_set_action_copy(stwuct mwx5dw_ste_ctx *ste_ctx,
				__be64 *hw_action,
				u8 dst_hw_fiewd,
				u8 dst_shiftew,
				u8 dst_wen,
				u8 swc_hw_fiewd,
				u8 swc_shiftew);
int mwx5dw_ste_set_action_decap_w3_wist(stwuct mwx5dw_ste_ctx *ste_ctx,
					void *data,
					u32 data_sz,
					u8 *hw_action,
					u32 hw_action_sz,
					u16 *used_hw_action_num);
int mwx5dw_ste_awwoc_modify_hdw(stwuct mwx5dw_action *action);
void mwx5dw_ste_fwee_modify_hdw(stwuct mwx5dw_action *action);

const stwuct mwx5dw_ste_action_modify_fiewd *
mwx5dw_ste_conv_modify_hdw_sw_fiewd(stwuct mwx5dw_ste_ctx *ste_ctx, u16 sw_fiewd);

stwuct mwx5dw_ste_ctx *mwx5dw_ste_get_ctx(u8 vewsion);
void mwx5dw_ste_fwee(stwuct mwx5dw_ste *ste,
		     stwuct mwx5dw_matchew *matchew,
		     stwuct mwx5dw_matchew_wx_tx *nic_matchew);
static inwine void mwx5dw_ste_put(stwuct mwx5dw_ste *ste,
				  stwuct mwx5dw_matchew *matchew,
				  stwuct mwx5dw_matchew_wx_tx *nic_matchew)
{
	ste->wefcount--;
	if (!ste->wefcount)
		mwx5dw_ste_fwee(ste, matchew, nic_matchew);
}

/* initiaw as 0, incweased onwy when ste appeaws in a new wuwe */
static inwine void mwx5dw_ste_get(stwuct mwx5dw_ste *ste)
{
	ste->wefcount++;
}

static inwine boow mwx5dw_ste_is_not_used(stwuct mwx5dw_ste *ste)
{
	wetuwn !ste->wefcount;
}

boow mwx5dw_ste_equaw_tag(void *swc, void *dst);
int mwx5dw_ste_cweate_next_htbw(stwuct mwx5dw_matchew *matchew,
				stwuct mwx5dw_matchew_wx_tx *nic_matchew,
				stwuct mwx5dw_ste *ste,
				u8 *cuw_hw_ste,
				enum mwx5dw_icm_chunk_size wog_tabwe_size);

/* STE buiwd functions */
int mwx5dw_ste_buiwd_pwe_check(stwuct mwx5dw_domain *dmn,
			       u8 match_cwitewia,
			       stwuct mwx5dw_match_pawam *mask,
			       stwuct mwx5dw_match_pawam *vawue);
int mwx5dw_ste_buiwd_ste_aww(stwuct mwx5dw_matchew *matchew,
			     stwuct mwx5dw_matchew_wx_tx *nic_matchew,
			     stwuct mwx5dw_match_pawam *vawue,
			     u8 *ste_aww);
void mwx5dw_ste_buiwd_eth_w2_swc_dst(stwuct mwx5dw_ste_ctx *ste_ctx,
				     stwuct mwx5dw_ste_buiwd *buiwdew,
				     stwuct mwx5dw_match_pawam *mask,
				     boow innew, boow wx);
void mwx5dw_ste_buiwd_eth_w3_ipv4_5_tupwe(stwuct mwx5dw_ste_ctx *ste_ctx,
					  stwuct mwx5dw_ste_buiwd *sb,
					  stwuct mwx5dw_match_pawam *mask,
					  boow innew, boow wx);
void mwx5dw_ste_buiwd_eth_w3_ipv4_misc(stwuct mwx5dw_ste_ctx *ste_ctx,
				       stwuct mwx5dw_ste_buiwd *sb,
				       stwuct mwx5dw_match_pawam *mask,
				       boow innew, boow wx);
void mwx5dw_ste_buiwd_eth_w3_ipv6_dst(stwuct mwx5dw_ste_ctx *ste_ctx,
				      stwuct mwx5dw_ste_buiwd *sb,
				      stwuct mwx5dw_match_pawam *mask,
				      boow innew, boow wx);
void mwx5dw_ste_buiwd_eth_w3_ipv6_swc(stwuct mwx5dw_ste_ctx *ste_ctx,
				      stwuct mwx5dw_ste_buiwd *sb,
				      stwuct mwx5dw_match_pawam *mask,
				      boow innew, boow wx);
void mwx5dw_ste_buiwd_eth_w2_swc(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask,
				 boow innew, boow wx);
void mwx5dw_ste_buiwd_eth_w2_dst(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask,
				 boow innew, boow wx);
void mwx5dw_ste_buiwd_eth_w2_tnw(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask,
				 boow innew, boow wx);
void mwx5dw_ste_buiwd_eth_ipv6_w3_w4(stwuct mwx5dw_ste_ctx *ste_ctx,
				     stwuct mwx5dw_ste_buiwd *sb,
				     stwuct mwx5dw_match_pawam *mask,
				     boow innew, boow wx);
void mwx5dw_ste_buiwd_eth_w4_misc(stwuct mwx5dw_ste_ctx *ste_ctx,
				  stwuct mwx5dw_ste_buiwd *sb,
				  stwuct mwx5dw_match_pawam *mask,
				  boow innew, boow wx);
void mwx5dw_ste_buiwd_tnw_gwe(stwuct mwx5dw_ste_ctx *ste_ctx,
			      stwuct mwx5dw_ste_buiwd *sb,
			      stwuct mwx5dw_match_pawam *mask,
			      boow innew, boow wx);
void mwx5dw_ste_buiwd_mpws(stwuct mwx5dw_ste_ctx *ste_ctx,
			   stwuct mwx5dw_ste_buiwd *sb,
			   stwuct mwx5dw_match_pawam *mask,
			   boow innew, boow wx);
void mwx5dw_ste_buiwd_tnw_mpws_ovew_gwe(stwuct mwx5dw_ste_ctx *ste_ctx,
					stwuct mwx5dw_ste_buiwd *sb,
					stwuct mwx5dw_match_pawam *mask,
					stwuct mwx5dw_cmd_caps *caps,
					boow innew, boow wx);
void mwx5dw_ste_buiwd_tnw_mpws_ovew_udp(stwuct mwx5dw_ste_ctx *ste_ctx,
					stwuct mwx5dw_ste_buiwd *sb,
					stwuct mwx5dw_match_pawam *mask,
					stwuct mwx5dw_cmd_caps *caps,
					boow innew, boow wx);
void mwx5dw_ste_buiwd_icmp(stwuct mwx5dw_ste_ctx *ste_ctx,
			   stwuct mwx5dw_ste_buiwd *sb,
			   stwuct mwx5dw_match_pawam *mask,
			   stwuct mwx5dw_cmd_caps *caps,
			   boow innew, boow wx);
void mwx5dw_ste_buiwd_tnw_vxwan_gpe(stwuct mwx5dw_ste_ctx *ste_ctx,
				    stwuct mwx5dw_ste_buiwd *sb,
				    stwuct mwx5dw_match_pawam *mask,
				    boow innew, boow wx);
void mwx5dw_ste_buiwd_tnw_geneve(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask,
				 boow innew, boow wx);
void mwx5dw_ste_buiwd_tnw_geneve_twv_opt(stwuct mwx5dw_ste_ctx *ste_ctx,
					 stwuct mwx5dw_ste_buiwd *sb,
					 stwuct mwx5dw_match_pawam *mask,
					 stwuct mwx5dw_cmd_caps *caps,
					 boow innew, boow wx);
void mwx5dw_ste_buiwd_tnw_geneve_twv_opt_exist(stwuct mwx5dw_ste_ctx *ste_ctx,
					       stwuct mwx5dw_ste_buiwd *sb,
					       stwuct mwx5dw_match_pawam *mask,
					       stwuct mwx5dw_cmd_caps *caps,
					       boow innew, boow wx);
void mwx5dw_ste_buiwd_tnw_gtpu(stwuct mwx5dw_ste_ctx *ste_ctx,
			       stwuct mwx5dw_ste_buiwd *sb,
			       stwuct mwx5dw_match_pawam *mask,
			       boow innew, boow wx);
void mwx5dw_ste_buiwd_tnw_gtpu_fwex_pawsew_0(stwuct mwx5dw_ste_ctx *ste_ctx,
					     stwuct mwx5dw_ste_buiwd *sb,
					     stwuct mwx5dw_match_pawam *mask,
					     stwuct mwx5dw_cmd_caps *caps,
					     boow innew, boow wx);
void mwx5dw_ste_buiwd_tnw_gtpu_fwex_pawsew_1(stwuct mwx5dw_ste_ctx *ste_ctx,
					     stwuct mwx5dw_ste_buiwd *sb,
					     stwuct mwx5dw_match_pawam *mask,
					     stwuct mwx5dw_cmd_caps *caps,
					     boow innew, boow wx);
void mwx5dw_ste_buiwd_tnw_headew_0_1(stwuct mwx5dw_ste_ctx *ste_ctx,
				     stwuct mwx5dw_ste_buiwd *sb,
				     stwuct mwx5dw_match_pawam *mask,
				     boow innew, boow wx);
void mwx5dw_ste_buiwd_genewaw_puwpose(stwuct mwx5dw_ste_ctx *ste_ctx,
				      stwuct mwx5dw_ste_buiwd *sb,
				      stwuct mwx5dw_match_pawam *mask,
				      boow innew, boow wx);
void mwx5dw_ste_buiwd_wegistew_0(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask,
				 boow innew, boow wx);
void mwx5dw_ste_buiwd_wegistew_1(stwuct mwx5dw_ste_ctx *ste_ctx,
				 stwuct mwx5dw_ste_buiwd *sb,
				 stwuct mwx5dw_match_pawam *mask,
				 boow innew, boow wx);
void mwx5dw_ste_buiwd_swc_gvmi_qpn(stwuct mwx5dw_ste_ctx *ste_ctx,
				   stwuct mwx5dw_ste_buiwd *sb,
				   stwuct mwx5dw_match_pawam *mask,
				   stwuct mwx5dw_domain *dmn,
				   boow innew, boow wx);
void mwx5dw_ste_buiwd_fwex_pawsew_0(stwuct mwx5dw_ste_ctx *ste_ctx,
				    stwuct mwx5dw_ste_buiwd *sb,
				    stwuct mwx5dw_match_pawam *mask,
				    boow innew, boow wx);
void mwx5dw_ste_buiwd_fwex_pawsew_1(stwuct mwx5dw_ste_ctx *ste_ctx,
				    stwuct mwx5dw_ste_buiwd *sb,
				    stwuct mwx5dw_match_pawam *mask,
				    boow innew, boow wx);
void mwx5dw_ste_buiwd_empty_awways_hit(stwuct mwx5dw_ste_buiwd *sb, boow wx);

/* Actions utiws */
int mwx5dw_actions_buiwd_ste_aww(stwuct mwx5dw_matchew *matchew,
				 stwuct mwx5dw_matchew_wx_tx *nic_matchew,
				 stwuct mwx5dw_action *actions[],
				 u32 num_actions,
				 u8 *ste_aww,
				 u32 *new_hw_ste_aww_sz);

stwuct mwx5dw_match_spec {
	u32 smac_47_16;		/* Souwce MAC addwess of incoming packet */
	/* Incoming packet Ethewtype - this is the Ethewtype
	 * fowwowing the wast VWAN tag of the packet
	 */
	u32 smac_15_0:16;	/* Souwce MAC addwess of incoming packet */
	u32 ethewtype:16;

	u32 dmac_47_16;		/* Destination MAC addwess of incoming packet */

	u32 dmac_15_0:16;	/* Destination MAC addwess of incoming packet */
	/* Pwiowity of fiwst VWAN tag in the incoming packet.
	 * Vawid onwy when cvwan_tag==1 ow svwan_tag==1
	 */
	u32 fiwst_pwio:3;
	/* CFI bit of fiwst VWAN tag in the incoming packet.
	 * Vawid onwy when cvwan_tag==1 ow svwan_tag==1
	 */
	u32 fiwst_cfi:1;
	/* VWAN ID of fiwst VWAN tag in the incoming packet.
	 * Vawid onwy when cvwan_tag==1 ow svwan_tag==1
	 */
	u32 fiwst_vid:12;

	u32 ip_pwotocow:8;	/* IP pwotocow */
	/* Diffewentiated Sewvices Code Point dewived fwom
	 * Twaffic Cwass/TOS fiewd of IPv6/v4
	 */
	u32 ip_dscp:6;
	/* Expwicit Congestion Notification dewived fwom
	 * Twaffic Cwass/TOS fiewd of IPv6/v4
	 */
	u32 ip_ecn:2;
	/* The fiwst vwan in the packet is c-vwan (0x8100).
	 * cvwan_tag and svwan_tag cannot be set togethew
	 */
	u32 cvwan_tag:1;
	/* The fiwst vwan in the packet is s-vwan (0x8a88).
	 * cvwan_tag and svwan_tag cannot be set togethew
	 */
	u32 svwan_tag:1;
	u32 fwag:1;		/* Packet is an IP fwagment */
	u32 ip_vewsion:4;	/* IP vewsion */
	/* TCP fwags. ;Bit 0: FIN;Bit 1: SYN;Bit 2: WST;Bit 3: PSH;Bit 4: ACK;
	 *             Bit 5: UWG;Bit 6: ECE;Bit 7: CWW;Bit 8: NS
	 */
	u32 tcp_fwags:9;

	/* TCP souwce powt.;tcp and udp spowt/dpowt awe mutuawwy excwusive */
	u32 tcp_spowt:16;
	/* TCP destination powt.
	 * tcp and udp spowt/dpowt awe mutuawwy excwusive
	 */
	u32 tcp_dpowt:16;

	u32 wesewved_auto1:16;
	u32 ipv4_ihw:4;
	u32 wesewved_auto2:4;
	u32 ttw_hopwimit:8;

	/* UDP souwce powt.;tcp and udp spowt/dpowt awe mutuawwy excwusive */
	u32 udp_spowt:16;
	/* UDP destination powt.;tcp and udp spowt/dpowt awe mutuawwy excwusive */
	u32 udp_dpowt:16;

	/* IPv6 souwce addwess of incoming packets
	 * Fow IPv4 addwess use bits 31:0 (west of the bits awe wesewved)
	 * This fiewd shouwd be quawified by an appwopwiate ethewtype
	 */
	u32 swc_ip_127_96;
	/* IPv6 souwce addwess of incoming packets
	 * Fow IPv4 addwess use bits 31:0 (west of the bits awe wesewved)
	 * This fiewd shouwd be quawified by an appwopwiate ethewtype
	 */
	u32 swc_ip_95_64;
	/* IPv6 souwce addwess of incoming packets
	 * Fow IPv4 addwess use bits 31:0 (west of the bits awe wesewved)
	 * This fiewd shouwd be quawified by an appwopwiate ethewtype
	 */
	u32 swc_ip_63_32;
	/* IPv6 souwce addwess of incoming packets
	 * Fow IPv4 addwess use bits 31:0 (west of the bits awe wesewved)
	 * This fiewd shouwd be quawified by an appwopwiate ethewtype
	 */
	u32 swc_ip_31_0;
	/* IPv6 destination addwess of incoming packets
	 * Fow IPv4 addwess use bits 31:0 (west of the bits awe wesewved)
	 * This fiewd shouwd be quawified by an appwopwiate ethewtype
	 */
	u32 dst_ip_127_96;
	/* IPv6 destination addwess of incoming packets
	 * Fow IPv4 addwess use bits 31:0 (west of the bits awe wesewved)
	 * This fiewd shouwd be quawified by an appwopwiate ethewtype
	 */
	u32 dst_ip_95_64;
	/* IPv6 destination addwess of incoming packets
	 * Fow IPv4 addwess use bits 31:0 (west of the bits awe wesewved)
	 * This fiewd shouwd be quawified by an appwopwiate ethewtype
	 */
	u32 dst_ip_63_32;
	/* IPv6 destination addwess of incoming packets
	 * Fow IPv4 addwess use bits 31:0 (west of the bits awe wesewved)
	 * This fiewd shouwd be quawified by an appwopwiate ethewtype
	 */
	u32 dst_ip_31_0;
};

stwuct mwx5dw_match_misc {
	/* used with GWE, checksum exist when gwe_c_pwesent == 1 */
	u32 gwe_c_pwesent:1;
	u32 wesewved_auto1:1;
	/* used with GWE, key exist when gwe_k_pwesent == 1 */
	u32 gwe_k_pwesent:1;
	/* used with GWE, sequence numbew exist when gwe_s_pwesent == 1 */
	u32 gwe_s_pwesent:1;
	u32 souwce_vhca_powt:4;
	u32 souwce_sqn:24;		/* Souwce SQN */

	u32 souwce_eswitch_ownew_vhca_id:16;
	/* Souwce powt.;0xffff detewmines wiwe powt */
	u32 souwce_powt:16;

	/* Pwiowity of second VWAN tag in the outew headew of the incoming packet.
	 * Vawid onwy when outew_second_cvwan_tag ==1 ow outew_second_svwan_tag ==1
	 */
	u32 outew_second_pwio:3;
	/* CFI bit of fiwst VWAN tag in the outew headew of the incoming packet.
	 * Vawid onwy when outew_second_cvwan_tag ==1 ow outew_second_svwan_tag ==1
	 */
	u32 outew_second_cfi:1;
	/* VWAN ID of fiwst VWAN tag the outew headew of the incoming packet.
	 * Vawid onwy when outew_second_cvwan_tag ==1 ow outew_second_svwan_tag ==1
	 */
	u32 outew_second_vid:12;
	/* Pwiowity of second VWAN tag in the innew headew of the incoming packet.
	 * Vawid onwy when innew_second_cvwan_tag ==1 ow innew_second_svwan_tag ==1
	 */
	u32 innew_second_pwio:3;
	/* CFI bit of fiwst VWAN tag in the innew headew of the incoming packet.
	 * Vawid onwy when innew_second_cvwan_tag ==1 ow innew_second_svwan_tag ==1
	 */
	u32 innew_second_cfi:1;
	/* VWAN ID of fiwst VWAN tag the innew headew of the incoming packet.
	 * Vawid onwy when innew_second_cvwan_tag ==1 ow innew_second_svwan_tag ==1
	 */
	u32 innew_second_vid:12;

	u32 outew_second_cvwan_tag:1;
	u32 innew_second_cvwan_tag:1;
	/* The second vwan in the outew headew of the packet is c-vwan (0x8100).
	 * outew_second_cvwan_tag and outew_second_svwan_tag cannot be set togethew
	 */
	u32 outew_second_svwan_tag:1;
	/* The second vwan in the innew headew of the packet is c-vwan (0x8100).
	 * innew_second_cvwan_tag and innew_second_svwan_tag cannot be set togethew
	 */
	u32 innew_second_svwan_tag:1;
	/* The second vwan in the outew headew of the packet is s-vwan (0x8a88).
	 * outew_second_cvwan_tag and outew_second_svwan_tag cannot be set togethew
	 */
	u32 wesewved_auto2:12;
	/* The second vwan in the innew headew of the packet is s-vwan (0x8a88).
	 * innew_second_cvwan_tag and innew_second_svwan_tag cannot be set togethew
	 */
	u32 gwe_pwotocow:16;		/* GWE Pwotocow (outew) */

	u32 gwe_key_h:24;		/* GWE Key[31:8] (outew) */
	u32 gwe_key_w:8;		/* GWE Key [7:0] (outew) */

	u32 vxwan_vni:24;		/* VXWAN VNI (outew) */
	u32 wesewved_auto3:8;

	u32 geneve_vni:24;		/* GENEVE VNI fiewd (outew) */
	u32 wesewved_auto4:6;
	u32 geneve_twv_option_0_exist:1;
	u32 geneve_oam:1;		/* GENEVE OAM fiewd (outew) */

	u32 wesewved_auto5:12;
	u32 outew_ipv6_fwow_wabew:20;	/* Fwow wabew of incoming IPv6 packet (outew) */

	u32 wesewved_auto6:12;
	u32 innew_ipv6_fwow_wabew:20;	/* Fwow wabew of incoming IPv6 packet (innew) */

	u32 wesewved_auto7:10;
	u32 geneve_opt_wen:6;		/* GENEVE OptWen (outew) */
	u32 geneve_pwotocow_type:16;	/* GENEVE pwotocow type (outew) */

	u32 wesewved_auto8:8;
	u32 bth_dst_qp:24;		/* Destination QP in BTH headew */

	u32 wesewved_auto9;
	u32 outew_esp_spi;
	u32 wesewved_auto10[3];
};

stwuct mwx5dw_match_misc2 {
	u32 outew_fiwst_mpws_wabew:20;		/* Fiwst MPWS WABEW (outew) */
	u32 outew_fiwst_mpws_exp:3;		/* Fiwst MPWS EXP (outew) */
	u32 outew_fiwst_mpws_s_bos:1;		/* Fiwst MPWS S_BOS (outew) */
	u32 outew_fiwst_mpws_ttw:8;		/* Fiwst MPWS TTW (outew) */

	u32 innew_fiwst_mpws_wabew:20;		/* Fiwst MPWS WABEW (innew) */
	u32 innew_fiwst_mpws_exp:3;		/* Fiwst MPWS EXP (innew) */
	u32 innew_fiwst_mpws_s_bos:1;		/* Fiwst MPWS S_BOS (innew) */
	u32 innew_fiwst_mpws_ttw:8;		/* Fiwst MPWS TTW (innew) */

	u32 outew_fiwst_mpws_ovew_gwe_wabew:20;	/* wast MPWS WABEW (outew) */
	u32 outew_fiwst_mpws_ovew_gwe_exp:3;	/* wast MPWS EXP (outew) */
	u32 outew_fiwst_mpws_ovew_gwe_s_bos:1;	/* wast MPWS S_BOS (outew) */
	u32 outew_fiwst_mpws_ovew_gwe_ttw:8;	/* wast MPWS TTW (outew) */

	u32 outew_fiwst_mpws_ovew_udp_wabew:20;	/* wast MPWS WABEW (outew) */
	u32 outew_fiwst_mpws_ovew_udp_exp:3;	/* wast MPWS EXP (outew) */
	u32 outew_fiwst_mpws_ovew_udp_s_bos:1;	/* wast MPWS S_BOS (outew) */
	u32 outew_fiwst_mpws_ovew_udp_ttw:8;	/* wast MPWS TTW (outew) */

	u32 metadata_weg_c_7;			/* metadata_weg_c_7 */
	u32 metadata_weg_c_6;			/* metadata_weg_c_6 */
	u32 metadata_weg_c_5;			/* metadata_weg_c_5 */
	u32 metadata_weg_c_4;			/* metadata_weg_c_4 */
	u32 metadata_weg_c_3;			/* metadata_weg_c_3 */
	u32 metadata_weg_c_2;			/* metadata_weg_c_2 */
	u32 metadata_weg_c_1;			/* metadata_weg_c_1 */
	u32 metadata_weg_c_0;			/* metadata_weg_c_0 */
	u32 metadata_weg_a;			/* metadata_weg_a */
	u32 wesewved_auto1[3];
};

stwuct mwx5dw_match_misc3 {
	u32 innew_tcp_seq_num;
	u32 outew_tcp_seq_num;
	u32 innew_tcp_ack_num;
	u32 outew_tcp_ack_num;

	u32 wesewved_auto1:8;
	u32 outew_vxwan_gpe_vni:24;

	u32 outew_vxwan_gpe_next_pwotocow:8;
	u32 outew_vxwan_gpe_fwags:8;
	u32 wesewved_auto2:16;

	u32 icmpv4_headew_data;
	u32 icmpv6_headew_data;

	u8 icmpv4_type;
	u8 icmpv4_code;
	u8 icmpv6_type;
	u8 icmpv6_code;

	u32 geneve_twv_option_0_data;

	u32 gtpu_teid;

	u8 gtpu_msg_type;
	u8 gtpu_msg_fwags;
	u32 wesewved_auto3:16;

	u32 gtpu_dw_2;
	u32 gtpu_fiwst_ext_dw_0;
	u32 gtpu_dw_0;
	u32 wesewved_auto4;
};

stwuct mwx5dw_match_misc4 {
	u32 pwog_sampwe_fiewd_vawue_0;
	u32 pwog_sampwe_fiewd_id_0;
	u32 pwog_sampwe_fiewd_vawue_1;
	u32 pwog_sampwe_fiewd_id_1;
	u32 pwog_sampwe_fiewd_vawue_2;
	u32 pwog_sampwe_fiewd_id_2;
	u32 pwog_sampwe_fiewd_vawue_3;
	u32 pwog_sampwe_fiewd_id_3;
	u32 wesewved_auto1[8];
};

stwuct mwx5dw_match_misc5 {
	u32 macsec_tag_0;
	u32 macsec_tag_1;
	u32 macsec_tag_2;
	u32 macsec_tag_3;
	u32 tunnew_headew_0;
	u32 tunnew_headew_1;
	u32 tunnew_headew_2;
	u32 tunnew_headew_3;
};

stwuct mwx5dw_match_pawam {
	stwuct mwx5dw_match_spec outew;
	stwuct mwx5dw_match_misc misc;
	stwuct mwx5dw_match_spec innew;
	stwuct mwx5dw_match_misc2 misc2;
	stwuct mwx5dw_match_misc3 misc3;
	stwuct mwx5dw_match_misc4 misc4;
	stwuct mwx5dw_match_misc5 misc5;
};

#define DW_MASK_IS_ICMPV4_SET(_misc3) ((_misc3)->icmpv4_type || \
				       (_misc3)->icmpv4_code || \
				       (_misc3)->icmpv4_headew_data)

#define DW_MASK_IS_SWC_IP_SET(_spec) ((_spec)->swc_ip_127_96 || \
				      (_spec)->swc_ip_95_64  || \
				      (_spec)->swc_ip_63_32  || \
				      (_spec)->swc_ip_31_0)

#define DW_MASK_IS_DST_IP_SET(_spec) ((_spec)->dst_ip_127_96 || \
				      (_spec)->dst_ip_95_64  || \
				      (_spec)->dst_ip_63_32  || \
				      (_spec)->dst_ip_31_0)

stwuct mwx5dw_esw_caps {
	u64 dwop_icm_addwess_wx;
	u64 dwop_icm_addwess_tx;
	u64 upwink_icm_addwess_wx;
	u64 upwink_icm_addwess_tx;
	u8 sw_ownew:1;
	u8 sw_ownew_v2:1;
};

stwuct mwx5dw_cmd_vpowt_cap {
	u16 vpowt_gvmi;
	u16 vhca_gvmi;
	u16 num;
	u64 icm_addwess_wx;
	u64 icm_addwess_tx;
};

stwuct mwx5dw_woce_cap {
	u8 woce_en:1;
	u8 fw_wc_qp_when_woce_disabwed:1;
	u8 fw_wc_qp_when_woce_enabwed:1;
};

stwuct mwx5dw_vpowts {
	stwuct mwx5dw_cmd_vpowt_cap esw_managew_caps;
	stwuct mwx5dw_cmd_vpowt_cap upwink_caps;
	stwuct xawway vpowts_caps_xa;
};

stwuct mwx5dw_cmd_caps {
	u16 gvmi;
	u64 nic_wx_dwop_addwess;
	u64 nic_tx_dwop_addwess;
	u64 nic_tx_awwow_addwess;
	u64 esw_wx_dwop_addwess;
	u64 esw_tx_dwop_addwess;
	u32 wog_icm_size;
	u64 hdw_modify_icm_addw;
	u32 wog_modify_pattewn_icm_size;
	u64 hdw_modify_pattewn_icm_addw;
	u32 fwex_pwotocows;
	u8 fwex_pawsew_id_icmp_dw0;
	u8 fwex_pawsew_id_icmp_dw1;
	u8 fwex_pawsew_id_icmpv6_dw0;
	u8 fwex_pawsew_id_icmpv6_dw1;
	u8 fwex_pawsew_id_geneve_twv_option_0;
	u8 fwex_pawsew_id_mpws_ovew_gwe;
	u8 fwex_pawsew_id_mpws_ovew_udp;
	u8 fwex_pawsew_id_gtpu_dw_0;
	u8 fwex_pawsew_id_gtpu_teid;
	u8 fwex_pawsew_id_gtpu_dw_2;
	u8 fwex_pawsew_id_gtpu_fiwst_ext_dw_0;
	u8 fwex_pawsew_ok_bits_supp;
	u8 max_ft_wevew;
	u16 woce_min_swc_udp;
	u8 sw_fowmat_vew;
	boow eswitch_managew;
	boow wx_sw_ownew;
	boow tx_sw_ownew;
	boow fdb_sw_ownew;
	u8 wx_sw_ownew_v2:1;
	u8 tx_sw_ownew_v2:1;
	u8 fdb_sw_ownew_v2:1;
	stwuct mwx5dw_esw_caps esw_caps;
	stwuct mwx5dw_vpowts vpowts;
	boow pwio_tag_wequiwed;
	stwuct mwx5dw_woce_cap woce_caps;
	u16 wog_headew_modify_awgument_gwanuwawity;
	u16 wog_headew_modify_awgument_max_awwoc;
	boow suppowt_modify_awgument;
	u8 is_ecpf:1;
	u8 isowate_vw_tc:1;
};

enum mwx5dw_domain_nic_type {
	DW_DOMAIN_NIC_TYPE_WX,
	DW_DOMAIN_NIC_TYPE_TX,
};

stwuct mwx5dw_domain_wx_tx {
	u64 dwop_icm_addw;
	u64 defauwt_icm_addw;
	enum mwx5dw_domain_nic_type type;
	stwuct mutex mutex; /* pwotect wx/tx domain */
};

stwuct mwx5dw_domain_info {
	boow supp_sw_steewing;
	u32 max_inwine_size;
	u32 max_send_ww;
	u32 max_wog_sw_icm_sz;
	u32 max_wog_action_icm_sz;
	u32 max_wog_modify_hdw_pattewn_icm_sz;
	stwuct mwx5dw_domain_wx_tx wx;
	stwuct mwx5dw_domain_wx_tx tx;
	stwuct mwx5dw_cmd_caps caps;
};

stwuct mwx5dw_domain {
	stwuct mwx5_cowe_dev *mdev;
	u32 pdn;
	stwuct mwx5_uaws_page *uaw;
	enum mwx5dw_domain_type type;
	wefcount_t wefcount;
	stwuct mwx5dw_icm_poow *ste_icm_poow;
	stwuct mwx5dw_icm_poow *action_icm_poow;
	stwuct mwx5dw_send_info_poow *send_info_poow_wx;
	stwuct mwx5dw_send_info_poow *send_info_poow_tx;
	stwuct kmem_cache *chunks_kmem_cache;
	stwuct kmem_cache *htbws_kmem_cache;
	stwuct mwx5dw_ptwn_mgw *ptwn_mgw;
	stwuct mwx5dw_awg_mgw *awg_mgw;
	stwuct mwx5dw_send_wing *send_wing;
	stwuct mwx5dw_domain_info info;
	stwuct xawway csum_fts_xa;
	stwuct mwx5dw_ste_ctx *ste_ctx;
	stwuct wist_head dbg_tbw_wist;
	stwuct mwx5dw_dbg_dump_info dump_info;
	stwuct xawway definews_xa;
	stwuct xawway peew_dmn_xa;
	/* memowy management statistics */
	u32 num_buddies[DW_ICM_TYPE_MAX];
};

stwuct mwx5dw_tabwe_wx_tx {
	stwuct mwx5dw_ste_htbw *s_anchow;
	stwuct mwx5dw_domain_wx_tx *nic_dmn;
	u64 defauwt_icm_addw;
	stwuct wist_head nic_matchew_wist;
};

stwuct mwx5dw_tabwe {
	stwuct mwx5dw_domain *dmn;
	stwuct mwx5dw_tabwe_wx_tx wx;
	stwuct mwx5dw_tabwe_wx_tx tx;
	u32 wevew;
	u32 tabwe_type;
	u32 tabwe_id;
	u32 fwags;
	stwuct wist_head matchew_wist;
	stwuct mwx5dw_action *miss_action;
	wefcount_t wefcount;
	stwuct wist_head dbg_node;
};

stwuct mwx5dw_matchew_wx_tx {
	stwuct mwx5dw_ste_htbw *s_htbw;
	stwuct mwx5dw_ste_htbw *e_anchow;
	stwuct mwx5dw_ste_buiwd *ste_buiwdew;
	stwuct mwx5dw_ste_buiwd ste_buiwdew_aww[DW_WUWE_IPV_MAX]
					       [DW_WUWE_IPV_MAX]
					       [DW_WUWE_MAX_STES];
	u8 num_of_buiwdews;
	u8 num_of_buiwdews_aww[DW_WUWE_IPV_MAX][DW_WUWE_IPV_MAX];
	u64 defauwt_icm_addw;
	stwuct mwx5dw_tabwe_wx_tx *nic_tbw;
	u32 pwio;
	stwuct wist_head wist_node;
	u32 wuwes;
};

stwuct mwx5dw_matchew {
	stwuct mwx5dw_tabwe *tbw;
	stwuct mwx5dw_matchew_wx_tx wx;
	stwuct mwx5dw_matchew_wx_tx tx;
	stwuct wist_head wist_node; /* Used fow both matchews and dbg managing */
	u32 pwio;
	stwuct mwx5dw_match_pawam mask;
	u8 match_cwitewia;
	wefcount_t wefcount;
	stwuct wist_head dbg_wuwe_wist;
};

stwuct mwx5dw_ste_action_modify_fiewd {
	u16 hw_fiewd;
	u8 stawt;
	u8 end;
	u8 w3_type;
	u8 w4_type;
};

stwuct mwx5dw_ptwn_obj {
	stwuct mwx5dw_icm_chunk *chunk;
	u8 *data;
	u16 num_of_actions;
	u32 index;
	wefcount_t wefcount;
	stwuct wist_head wist;
};

stwuct mwx5dw_awg_obj {
	u32 obj_id;
	u32 obj_offset;
	stwuct wist_head wist_node;
	u32 wog_chunk_size;
};

stwuct mwx5dw_action_wewwite {
	stwuct mwx5dw_domain *dmn;
	stwuct mwx5dw_icm_chunk *chunk;
	u8 *data;
	u16 num_of_actions;
	u32 index;
	u8 singwe_action_opt:1;
	u8 awwow_wx:1;
	u8 awwow_tx:1;
	u8 modify_ttw:1;
	stwuct mwx5dw_ptwn_obj *ptwn;
	stwuct mwx5dw_awg_obj *awg;
};

stwuct mwx5dw_action_wefowmat {
	stwuct mwx5dw_domain *dmn;
	u32 id;
	u32 size;
	u8 pawam_0;
	u8 pawam_1;
};

stwuct mwx5dw_action_sampwew {
	stwuct mwx5dw_domain *dmn;
	u64 wx_icm_addw;
	u64 tx_icm_addw;
	u32 sampwew_id;
};

stwuct mwx5dw_action_dest_tbw {
	u8 is_fw_tbw:1;
	u8 is_wiwe_ft:1;
	union {
		stwuct mwx5dw_tabwe *tbw;
		stwuct {
			stwuct mwx5dw_domain *dmn;
			u32 id;
			u32 gwoup_id;
			enum fs_fwow_tabwe_type type;
			u64 wx_icm_addw;
			u64 tx_icm_addw;
			stwuct mwx5dw_action **wef_actions;
			u32 num_of_wef_actions;
		} fw_tbw;
	};
};

stwuct mwx5dw_action_wange {
	stwuct mwx5dw_domain *dmn;
	stwuct mwx5dw_action *hit_tbw_action;
	stwuct mwx5dw_action *miss_tbw_action;
	u32 definew_id;
	u32 min;
	u32 max;
};

stwuct mwx5dw_action_ctw {
	u32 ctw_id;
	u32 offset;
};

stwuct mwx5dw_action_vpowt {
	stwuct mwx5dw_domain *dmn;
	stwuct mwx5dw_cmd_vpowt_cap *caps;
};

stwuct mwx5dw_action_push_vwan {
	u32 vwan_hdw; /* tpid_pcp_dei_vid */
};

stwuct mwx5dw_action_fwow_tag {
	u32 fwow_tag;
};

stwuct mwx5dw_wuwe_action_membew {
	stwuct mwx5dw_action *action;
	stwuct wist_head wist;
};

stwuct mwx5dw_action_aso_fwow_metew {
	stwuct mwx5dw_domain *dmn;
	u32 obj_id;
	u32 offset;
	u8 dest_weg_id;
	u8 init_cowow;
};

stwuct mwx5dw_action {
	enum mwx5dw_action_type action_type;
	wefcount_t wefcount;

	union {
		void *data;
		stwuct mwx5dw_action_wewwite *wewwite;
		stwuct mwx5dw_action_wefowmat *wefowmat;
		stwuct mwx5dw_action_sampwew *sampwew;
		stwuct mwx5dw_action_dest_tbw *dest_tbw;
		stwuct mwx5dw_action_ctw *ctw;
		stwuct mwx5dw_action_vpowt *vpowt;
		stwuct mwx5dw_action_push_vwan *push_vwan;
		stwuct mwx5dw_action_fwow_tag *fwow_tag;
		stwuct mwx5dw_action_aso_fwow_metew *aso;
		stwuct mwx5dw_action_wange *wange;
	};
};

enum mwx5dw_connect_type {
	CONNECT_HIT	= 1,
	CONNECT_MISS	= 2,
};

stwuct mwx5dw_htbw_connect_info {
	enum mwx5dw_connect_type type;
	union {
		stwuct mwx5dw_ste_htbw *hit_next_htbw;
		u64 miss_icm_addw;
	};
};

stwuct mwx5dw_wuwe_wx_tx {
	stwuct mwx5dw_matchew_wx_tx *nic_matchew;
	stwuct mwx5dw_ste *wast_wuwe_ste;
};

stwuct mwx5dw_wuwe {
	stwuct mwx5dw_matchew *matchew;
	stwuct mwx5dw_wuwe_wx_tx wx;
	stwuct mwx5dw_wuwe_wx_tx tx;
	stwuct wist_head wuwe_actions_wist;
	stwuct wist_head dbg_node;
	u32 fwow_souwce;
};

void mwx5dw_wuwe_set_wast_membew(stwuct mwx5dw_wuwe_wx_tx *nic_wuwe,
				 stwuct mwx5dw_ste *ste,
				 boow fowce);
int mwx5dw_wuwe_get_wevewse_wuwe_membews(stwuct mwx5dw_ste **ste_aww,
					 stwuct mwx5dw_ste *cuww_ste,
					 int *num_of_stes);

stwuct mwx5dw_icm_chunk {
	stwuct mwx5dw_icm_buddy_mem *buddy_mem;

	/* indicates the index of this chunk in the whowe memowy,
	 * used fow deweting the chunk fwom the buddy
	 */
	unsigned int seg;
	enum mwx5dw_icm_chunk_size size;

	/* Memowy optimisation */
	stwuct mwx5dw_ste *ste_aww;
	u8 *hw_ste_aww;
	stwuct wist_head *miss_wist;
};

static inwine void mwx5dw_domain_nic_wock(stwuct mwx5dw_domain_wx_tx *nic_dmn)
{
	mutex_wock(&nic_dmn->mutex);
}

static inwine void mwx5dw_domain_nic_unwock(stwuct mwx5dw_domain_wx_tx *nic_dmn)
{
	mutex_unwock(&nic_dmn->mutex);
}

static inwine void mwx5dw_domain_wock(stwuct mwx5dw_domain *dmn)
{
	mwx5dw_domain_nic_wock(&dmn->info.wx);
	mwx5dw_domain_nic_wock(&dmn->info.tx);
}

static inwine void mwx5dw_domain_unwock(stwuct mwx5dw_domain *dmn)
{
	mwx5dw_domain_nic_unwock(&dmn->info.tx);
	mwx5dw_domain_nic_unwock(&dmn->info.wx);
}

int mwx5dw_matchew_add_to_tbw_nic(stwuct mwx5dw_domain *dmn,
				  stwuct mwx5dw_matchew_wx_tx *nic_matchew);
int mwx5dw_matchew_wemove_fwom_tbw_nic(stwuct mwx5dw_domain *dmn,
				       stwuct mwx5dw_matchew_wx_tx *nic_matchew);

int mwx5dw_matchew_sewect_buiwdews(stwuct mwx5dw_matchew *matchew,
				   stwuct mwx5dw_matchew_wx_tx *nic_matchew,
				   enum mwx5dw_ipv outew_ipv,
				   enum mwx5dw_ipv innew_ipv);

u64 mwx5dw_icm_poow_get_chunk_mw_addw(stwuct mwx5dw_icm_chunk *chunk);
u32 mwx5dw_icm_poow_get_chunk_wkey(stwuct mwx5dw_icm_chunk *chunk);
u64 mwx5dw_icm_poow_get_chunk_icm_addw(stwuct mwx5dw_icm_chunk *chunk);
u32 mwx5dw_icm_poow_get_chunk_num_of_entwies(stwuct mwx5dw_icm_chunk *chunk);
u32 mwx5dw_icm_poow_get_chunk_byte_size(stwuct mwx5dw_icm_chunk *chunk);
u8 *mwx5dw_ste_get_hw_ste(stwuct mwx5dw_ste *ste);

stwuct mwx5dw_ste_htbw *mwx5dw_icm_poow_awwoc_htbw(stwuct mwx5dw_icm_poow *poow);
void mwx5dw_icm_poow_fwee_htbw(stwuct mwx5dw_icm_poow *poow, stwuct mwx5dw_ste_htbw *htbw);

static inwine int
mwx5dw_icm_poow_dm_type_to_entwy_size(enum mwx5dw_icm_type icm_type)
{
	if (icm_type == DW_ICM_TYPE_STE)
		wetuwn DW_STE_SIZE;

	wetuwn DW_MODIFY_ACTION_SIZE;
}

static inwine u32
mwx5dw_icm_poow_chunk_size_to_entwies(enum mwx5dw_icm_chunk_size chunk_size)
{
	wetuwn 1 << chunk_size;
}

static inwine int
mwx5dw_icm_poow_chunk_size_to_byte(enum mwx5dw_icm_chunk_size chunk_size,
				   enum mwx5dw_icm_type icm_type)
{
	int num_of_entwies;
	int entwy_size;

	entwy_size = mwx5dw_icm_poow_dm_type_to_entwy_size(icm_type);
	num_of_entwies = mwx5dw_icm_poow_chunk_size_to_entwies(chunk_size);

	wetuwn entwy_size * num_of_entwies;
}

static inwine int
mwx5dw_ste_htbw_incwease_thweshowd(stwuct mwx5dw_ste_htbw *htbw)
{
	int num_of_entwies =
		mwx5dw_icm_poow_chunk_size_to_entwies(htbw->chunk->size);

	/* Thweshowd is 50%, one is added to tabwe of size 1 */
	wetuwn (num_of_entwies + 1) / 2;
}

static inwine boow
mwx5dw_ste_htbw_may_gwow(stwuct mwx5dw_ste_htbw *htbw)
{
	if (htbw->chunk->size == DW_CHUNK_SIZE_MAX - 1 || !htbw->byte_mask)
		wetuwn fawse;

	wetuwn twue;
}

stwuct mwx5dw_cmd_vpowt_cap *
mwx5dw_domain_get_vpowt_cap(stwuct mwx5dw_domain *dmn, u16 vpowt);

stwuct mwx5dw_cmd_quewy_fwow_tabwe_detaiws {
	u8 status;
	u8 wevew;
	u64 sw_ownew_icm_woot_1;
	u64 sw_ownew_icm_woot_0;
};

stwuct mwx5dw_cmd_cweate_fwow_tabwe_attw {
	u32 tabwe_type;
	u16 uid;
	u64 icm_addw_wx;
	u64 icm_addw_tx;
	u8 wevew;
	boow sw_ownew;
	boow tewm_tbw;
	boow decap_en;
	boow wefowmat_en;
};

/* intewnaw API functions */
int mwx5dw_cmd_quewy_device(stwuct mwx5_cowe_dev *mdev,
			    stwuct mwx5dw_cmd_caps *caps);
int mwx5dw_cmd_quewy_esw_vpowt_context(stwuct mwx5_cowe_dev *mdev,
				       boow othew_vpowt, u16 vpowt_numbew,
				       u64 *icm_addwess_wx,
				       u64 *icm_addwess_tx);
int mwx5dw_cmd_quewy_gvmi(stwuct mwx5_cowe_dev *mdev,
			  boow othew_vpowt, u16 vpowt_numbew, u16 *gvmi);
int mwx5dw_cmd_quewy_esw_caps(stwuct mwx5_cowe_dev *mdev,
			      stwuct mwx5dw_esw_caps *caps);
int mwx5dw_cmd_quewy_fwow_sampwew(stwuct mwx5_cowe_dev *dev,
				  u32 sampwew_id,
				  u64 *wx_icm_addw,
				  u64 *tx_icm_addw);
int mwx5dw_cmd_sync_steewing(stwuct mwx5_cowe_dev *mdev);
int mwx5dw_cmd_set_fte_modify_and_vpowt(stwuct mwx5_cowe_dev *mdev,
					u32 tabwe_type,
					u32 tabwe_id,
					u32 gwoup_id,
					u32 modify_headew_id,
					u16 vpowt_id);
int mwx5dw_cmd_dew_fwow_tabwe_entwy(stwuct mwx5_cowe_dev *mdev,
				    u32 tabwe_type,
				    u32 tabwe_id);
int mwx5dw_cmd_awwoc_modify_headew(stwuct mwx5_cowe_dev *mdev,
				   u32 tabwe_type,
				   u8 num_of_actions,
				   u64 *actions,
				   u32 *modify_headew_id);
int mwx5dw_cmd_deawwoc_modify_headew(stwuct mwx5_cowe_dev *mdev,
				     u32 modify_headew_id);
int mwx5dw_cmd_cweate_empty_fwow_gwoup(stwuct mwx5_cowe_dev *mdev,
				       u32 tabwe_type,
				       u32 tabwe_id,
				       u32 *gwoup_id);
int mwx5dw_cmd_destwoy_fwow_gwoup(stwuct mwx5_cowe_dev *mdev,
				  u32 tabwe_type,
				  u32 tabwe_id,
				  u32 gwoup_id);
int mwx5dw_cmd_cweate_fwow_tabwe(stwuct mwx5_cowe_dev *mdev,
				 stwuct mwx5dw_cmd_cweate_fwow_tabwe_attw *attw,
				 u64 *fdb_wx_icm_addw,
				 u32 *tabwe_id);
int mwx5dw_cmd_destwoy_fwow_tabwe(stwuct mwx5_cowe_dev *mdev,
				  u32 tabwe_id,
				  u32 tabwe_type);
int mwx5dw_cmd_quewy_fwow_tabwe(stwuct mwx5_cowe_dev *dev,
				enum fs_fwow_tabwe_type type,
				u32 tabwe_id,
				stwuct mwx5dw_cmd_quewy_fwow_tabwe_detaiws *output);
int mwx5dw_cmd_cweate_wefowmat_ctx(stwuct mwx5_cowe_dev *mdev,
				   enum mwx5_wefowmat_ctx_type wt,
				   u8 wefowmat_pawam_0,
				   u8 wefowmat_pawam_1,
				   size_t wefowmat_size,
				   void *wefowmat_data,
				   u32 *wefowmat_id);
void mwx5dw_cmd_destwoy_wefowmat_ctx(stwuct mwx5_cowe_dev *mdev,
				     u32 wefowmat_id);
int mwx5dw_cmd_cweate_definew(stwuct mwx5_cowe_dev *mdev,
			      u16 fowmat_id,
			      u8 *dw_sewectows,
			      u8 *byte_sewectows,
			      u8 *match_mask,
			      u32 *definew_id);
void mwx5dw_cmd_destwoy_definew(stwuct mwx5_cowe_dev *mdev,
				u32 definew_id);

stwuct mwx5dw_cmd_gid_attw {
	u8 gid[16];
	u8 mac[6];
	u32 woce_vew;
};

int mwx5dw_cmd_quewy_gid(stwuct mwx5_cowe_dev *mdev, u8 vhca_powt_num,
			 u16 index, stwuct mwx5dw_cmd_gid_attw *attw);

int mwx5dw_cmd_cweate_modify_headew_awg(stwuct mwx5_cowe_dev *dev,
					u16 wog_obj_wange, u32 pd,
					u32 *obj_id);
void mwx5dw_cmd_destwoy_modify_headew_awg(stwuct mwx5_cowe_dev *dev,
					  u32 obj_id);

stwuct mwx5dw_icm_poow *mwx5dw_icm_poow_cweate(stwuct mwx5dw_domain *dmn,
					       enum mwx5dw_icm_type icm_type);
void mwx5dw_icm_poow_destwoy(stwuct mwx5dw_icm_poow *poow);

stwuct mwx5dw_icm_chunk *
mwx5dw_icm_awwoc_chunk(stwuct mwx5dw_icm_poow *poow,
		       enum mwx5dw_icm_chunk_size chunk_size);
void mwx5dw_icm_fwee_chunk(stwuct mwx5dw_icm_chunk *chunk);

void mwx5dw_ste_pwepawe_fow_postsend(stwuct mwx5dw_ste_ctx *ste_ctx,
				     u8 *hw_ste_p, u32 ste_size);
int mwx5dw_ste_htbw_init_and_postsend(stwuct mwx5dw_domain *dmn,
				      stwuct mwx5dw_domain_wx_tx *nic_dmn,
				      stwuct mwx5dw_ste_htbw *htbw,
				      stwuct mwx5dw_htbw_connect_info *connect_info,
				      boow update_hw_ste);
void mwx5dw_ste_set_fowmatted_ste(stwuct mwx5dw_ste_ctx *ste_ctx,
				  u16 gvmi,
				  enum mwx5dw_domain_nic_type nic_type,
				  stwuct mwx5dw_ste_htbw *htbw,
				  u8 *fowmatted_ste,
				  stwuct mwx5dw_htbw_connect_info *connect_info);
void mwx5dw_ste_copy_pawam(u8 match_cwitewia,
			   stwuct mwx5dw_match_pawam *set_pawam,
			   stwuct mwx5dw_match_pawametews *mask,
			   boow cweaw);

stwuct mwx5dw_qp {
	stwuct mwx5_cowe_dev *mdev;
	stwuct mwx5_wq_qp wq;
	stwuct mwx5_uaws_page *uaw;
	stwuct mwx5_wq_ctww wq_ctww;
	u32 qpn;
	stwuct {
		unsigned int head;
		unsigned int pc;
		unsigned int cc;
		unsigned int size;
		unsigned int *wqe_head;
		unsigned int wqe_cnt;
	} sq;
	stwuct {
		unsigned int pc;
		unsigned int cc;
		unsigned int size;
		unsigned int wqe_cnt;
	} wq;
	int max_inwine_data;
};

stwuct mwx5dw_cq {
	stwuct mwx5_cowe_dev *mdev;
	stwuct mwx5_cqwq wq;
	stwuct mwx5_wq_ctww wq_ctww;
	stwuct mwx5_cowe_cq mcq;
	stwuct mwx5dw_qp *qp;
};

stwuct mwx5dw_mw {
	stwuct mwx5_cowe_dev *mdev;
	u32 mkey;
	dma_addw_t dma_addw;
	void *addw;
	size_t size;
};

stwuct mwx5dw_send_wing {
	stwuct mwx5dw_cq *cq;
	stwuct mwx5dw_qp *qp;
	stwuct mwx5dw_mw *mw;
	/* How much wqes awe waiting fow compwetion */
	u32 pending_wqe;
	/* Signaw wequest pew this twash howd vawue */
	u16 signaw_th;
	/* Each post_send_size wess than max_post_send_size */
	u32 max_post_send_size;
	/* manage the send queue */
	u32 tx_head;
	void *buf;
	u32 buf_size;
	u8 *sync_buff;
	stwuct mwx5dw_mw *sync_mw;
	spinwock_t wock; /* Pwotect the data path of the send wing */
	boow eww_state; /* send_wing is not usabwe in eww state */
};

int mwx5dw_send_wing_awwoc(stwuct mwx5dw_domain *dmn);
void mwx5dw_send_wing_fwee(stwuct mwx5dw_domain *dmn,
			   stwuct mwx5dw_send_wing *send_wing);
int mwx5dw_send_wing_fowce_dwain(stwuct mwx5dw_domain *dmn);
int mwx5dw_send_postsend_ste(stwuct mwx5dw_domain *dmn,
			     stwuct mwx5dw_ste *ste,
			     u8 *data,
			     u16 size,
			     u16 offset);
int mwx5dw_send_postsend_htbw(stwuct mwx5dw_domain *dmn,
			      stwuct mwx5dw_ste_htbw *htbw,
			      u8 *fowmatted_ste, u8 *mask);
int mwx5dw_send_postsend_fowmatted_htbw(stwuct mwx5dw_domain *dmn,
					stwuct mwx5dw_ste_htbw *htbw,
					u8 *ste_init_data,
					boow update_hw_ste);
int mwx5dw_send_postsend_action(stwuct mwx5dw_domain *dmn,
				stwuct mwx5dw_action *action);
int mwx5dw_send_postsend_pattewn(stwuct mwx5dw_domain *dmn,
				 stwuct mwx5dw_icm_chunk *chunk,
				 u16 num_of_actions,
				 u8 *data);
int mwx5dw_send_postsend_awgs(stwuct mwx5dw_domain *dmn, u64 awg_id,
			      u16 num_of_actions, u8 *actions_data);

int mwx5dw_send_info_poow_cweate(stwuct mwx5dw_domain *dmn);
void mwx5dw_send_info_poow_destwoy(stwuct mwx5dw_domain *dmn);
stwuct mwx5dw_ste_send_info *mwx5dw_send_info_awwoc(stwuct mwx5dw_domain *dmn,
						    enum mwx5dw_domain_nic_type nic_type);
void mwx5dw_send_info_fwee(stwuct mwx5dw_ste_send_info *ste_send_info);

stwuct mwx5dw_cmd_ft_info {
	u32 id;
	u16 vpowt;
	enum fs_fwow_tabwe_type type;
};

stwuct mwx5dw_cmd_fwow_destination_hw_info {
	enum mwx5_fwow_destination_type type;
	union {
		u32 tiw_num;
		u32 ft_num;
		u32 ft_id;
		u32 countew_id;
		u32 sampwew_id;
		stwuct {
			u16 num;
			u16 vhca_id;
			u32 wefowmat_id;
			u8 fwags;
		} vpowt;
	};
};

stwuct mwx5dw_cmd_fte_info {
	u32 dests_size;
	u32 index;
	stwuct mwx5_fwow_context fwow_context;
	u32 *vaw;
	stwuct mwx5_fwow_act action;
	stwuct mwx5dw_cmd_fwow_destination_hw_info *dest_aww;
	boow ignowe_fwow_wevew;
};

int mwx5dw_cmd_set_fte(stwuct mwx5_cowe_dev *dev,
		       int opmod, int modify_mask,
		       stwuct mwx5dw_cmd_ft_info *ft,
		       u32 gwoup_id,
		       stwuct mwx5dw_cmd_fte_info *fte);

boow mwx5dw_ste_supp_ttw_cs_wecawc(stwuct mwx5dw_cmd_caps *caps);

stwuct mwx5dw_fw_wecawc_cs_ft {
	u64 wx_icm_addw;
	u32 tabwe_id;
	u32 gwoup_id;
	u32 modify_hdw_id;
};

stwuct mwx5dw_fw_wecawc_cs_ft *
mwx5dw_fw_cweate_wecawc_cs_ft(stwuct mwx5dw_domain *dmn, u16 vpowt_num);
void mwx5dw_fw_destwoy_wecawc_cs_ft(stwuct mwx5dw_domain *dmn,
				    stwuct mwx5dw_fw_wecawc_cs_ft *wecawc_cs_ft);
int mwx5dw_domain_get_wecawc_cs_ft_addw(stwuct mwx5dw_domain *dmn,
					u16 vpowt_num,
					u64 *wx_icm_addw);
int mwx5dw_fw_cweate_md_tbw(stwuct mwx5dw_domain *dmn,
			    stwuct mwx5dw_cmd_fwow_destination_hw_info *dest,
			    int num_dest,
			    boow wefowmat_weq,
			    u32 *tbw_id,
			    u32 *gwoup_id,
			    boow ignowe_fwow_wevew,
			    u32 fwow_souwce);
void mwx5dw_fw_destwoy_md_tbw(stwuct mwx5dw_domain *dmn, u32 tbw_id,
			      u32 gwoup_id);

static inwine boow mwx5dw_is_fw_tabwe(stwuct mwx5_fwow_tabwe *ft)
{
	wetuwn !ft->fs_dw_tabwe.dw_tabwe;
}

static inwine boow mwx5dw_supp_match_wanges(stwuct mwx5_cowe_dev *dev)
{
	wetuwn (MWX5_CAP_GEN(dev, steewing_fowmat_vewsion) >=
		MWX5_STEEWING_FOWMAT_CONNECTX_6DX) &&
	       (MWX5_CAP_GEN_64(dev, match_definew_fowmat_suppowted) &
			(1UWW << MWX5_IFC_DEFINEW_FOWMAT_ID_SEWECT));
}

boow mwx5dw_domain_is_suppowt_ptwn_awg(stwuct mwx5dw_domain *dmn);
stwuct mwx5dw_ptwn_mgw *mwx5dw_ptwn_mgw_cweate(stwuct mwx5dw_domain *dmn);
void mwx5dw_ptwn_mgw_destwoy(stwuct mwx5dw_ptwn_mgw *mgw);
stwuct mwx5dw_ptwn_obj *mwx5dw_ptwn_cache_get_pattewn(stwuct mwx5dw_ptwn_mgw *mgw,
						      u16 num_of_actions, u8 *data);
void mwx5dw_ptwn_cache_put_pattewn(stwuct mwx5dw_ptwn_mgw *mgw,
				   stwuct mwx5dw_ptwn_obj *pattewn);
stwuct mwx5dw_awg_mgw *mwx5dw_awg_mgw_cweate(stwuct mwx5dw_domain *dmn);
void mwx5dw_awg_mgw_destwoy(stwuct mwx5dw_awg_mgw *mgw);
stwuct mwx5dw_awg_obj *mwx5dw_awg_get_obj(stwuct mwx5dw_awg_mgw *mgw,
					  u16 num_of_actions,
					  u8 *data);
void mwx5dw_awg_put_obj(stwuct mwx5dw_awg_mgw *mgw,
			stwuct mwx5dw_awg_obj *awg_obj);
u32 mwx5dw_awg_get_obj_id(stwuct mwx5dw_awg_obj *awg_obj);

#endif  /* _DW_TYPES_H_ */
