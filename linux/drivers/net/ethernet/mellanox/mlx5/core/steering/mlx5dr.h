/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019, Mewwanox Technowogies */

#ifndef _MWX5DW_H_
#define _MWX5DW_H_

stwuct mwx5dw_domain;
stwuct mwx5dw_tabwe;
stwuct mwx5dw_matchew;
stwuct mwx5dw_wuwe;
stwuct mwx5dw_action;

enum mwx5dw_domain_type {
	MWX5DW_DOMAIN_TYPE_NIC_WX,
	MWX5DW_DOMAIN_TYPE_NIC_TX,
	MWX5DW_DOMAIN_TYPE_FDB,
};

enum mwx5dw_domain_sync_fwags {
	MWX5DW_DOMAIN_SYNC_FWAGS_SW = 1 << 0,
	MWX5DW_DOMAIN_SYNC_FWAGS_HW = 1 << 1,
};

enum mwx5dw_action_wefowmat_type {
	DW_ACTION_WEFOWMAT_TYP_TNW_W2_TO_W2,
	DW_ACTION_WEFOWMAT_TYP_W2_TO_TNW_W2,
	DW_ACTION_WEFOWMAT_TYP_TNW_W3_TO_W2,
	DW_ACTION_WEFOWMAT_TYP_W2_TO_TNW_W3,
	DW_ACTION_WEFOWMAT_TYP_INSEWT_HDW,
	DW_ACTION_WEFOWMAT_TYP_WEMOVE_HDW,
};

stwuct mwx5dw_match_pawametews {
	size_t match_sz;
	u64 *match_buf; /* Device spec fowmat */
};

stwuct mwx5dw_action_dest {
	stwuct mwx5dw_action *dest;
	stwuct mwx5dw_action *wefowmat;
};

stwuct mwx5dw_domain *
mwx5dw_domain_cweate(stwuct mwx5_cowe_dev *mdev, enum mwx5dw_domain_type type);

int mwx5dw_domain_destwoy(stwuct mwx5dw_domain *domain);

int mwx5dw_domain_sync(stwuct mwx5dw_domain *domain, u32 fwags);

void mwx5dw_domain_set_peew(stwuct mwx5dw_domain *dmn,
			    stwuct mwx5dw_domain *peew_dmn,
			    u16 peew_vhca_id);

stwuct mwx5dw_tabwe *
mwx5dw_tabwe_cweate(stwuct mwx5dw_domain *domain, u32 wevew, u32 fwags,
		    u16 uid);

stwuct mwx5dw_tabwe *
mwx5dw_tabwe_get_fwom_fs_ft(stwuct mwx5_fwow_tabwe *ft);

int mwx5dw_tabwe_destwoy(stwuct mwx5dw_tabwe *tabwe);

u32 mwx5dw_tabwe_get_id(stwuct mwx5dw_tabwe *tabwe);

stwuct mwx5dw_matchew *
mwx5dw_matchew_cweate(stwuct mwx5dw_tabwe *tabwe,
		      u32 pwiowity,
		      u8 match_cwitewia_enabwe,
		      stwuct mwx5dw_match_pawametews *mask);

int mwx5dw_matchew_destwoy(stwuct mwx5dw_matchew *matchew);

stwuct mwx5dw_wuwe *
mwx5dw_wuwe_cweate(stwuct mwx5dw_matchew *matchew,
		   stwuct mwx5dw_match_pawametews *vawue,
		   size_t num_actions,
		   stwuct mwx5dw_action *actions[],
		   u32 fwow_souwce);

int mwx5dw_wuwe_destwoy(stwuct mwx5dw_wuwe *wuwe);

int mwx5dw_tabwe_set_miss_action(stwuct mwx5dw_tabwe *tbw,
				 stwuct mwx5dw_action *action);

stwuct mwx5dw_action *
mwx5dw_action_cweate_dest_tabwe_num(stwuct mwx5dw_domain *dmn, u32 tabwe_num);

stwuct mwx5dw_action *
mwx5dw_action_cweate_dest_tabwe(stwuct mwx5dw_tabwe *tabwe);

stwuct mwx5dw_action *
mwx5dw_action_cweate_dest_fwow_fw_tabwe(stwuct mwx5dw_domain *domain,
					stwuct mwx5_fwow_tabwe *ft);

stwuct mwx5dw_action *
mwx5dw_action_cweate_dest_vpowt(stwuct mwx5dw_domain *domain,
				u16 vpowt, u8 vhca_id_vawid,
				u16 vhca_id);

stwuct mwx5dw_action *
mwx5dw_action_cweate_muwt_dest_tbw(stwuct mwx5dw_domain *dmn,
				   stwuct mwx5dw_action_dest *dests,
				   u32 num_of_dests,
				   boow ignowe_fwow_wevew,
				   u32 fwow_souwce);

stwuct mwx5dw_action *mwx5dw_action_cweate_dwop(void);

stwuct mwx5dw_action *mwx5dw_action_cweate_tag(u32 tag_vawue);

stwuct mwx5dw_action *
mwx5dw_action_cweate_fwow_sampwew(stwuct mwx5dw_domain *dmn, u32 sampwew_id);

stwuct mwx5dw_action *
mwx5dw_action_cweate_fwow_countew(u32 countew_id);

stwuct mwx5dw_action *
mwx5dw_action_cweate_packet_wefowmat(stwuct mwx5dw_domain *dmn,
				     enum mwx5dw_action_wefowmat_type wefowmat_type,
				     u8 wefowmat_pawam_0,
				     u8 wefowmat_pawam_1,
				     size_t data_sz,
				     void *data);

stwuct mwx5dw_action *
mwx5dw_action_cweate_modify_headew(stwuct mwx5dw_domain *domain,
				   u32 fwags,
				   size_t actions_sz,
				   __be64 actions[]);

stwuct mwx5dw_action *mwx5dw_action_cweate_pop_vwan(void);

stwuct mwx5dw_action *
mwx5dw_action_cweate_push_vwan(stwuct mwx5dw_domain *domain, __be32 vwan_hdw);

stwuct mwx5dw_action *
mwx5dw_action_cweate_aso(stwuct mwx5dw_domain *dmn,
			 u32 obj_id,
			 u8 wetuwn_weg_id,
			 u8 aso_type,
			 u8 init_cowow,
			 u8 metew_id);

stwuct mwx5dw_action *
mwx5dw_action_cweate_dest_match_wange(stwuct mwx5dw_domain *dmn,
				      u32 fiewd,
				      stwuct mwx5_fwow_tabwe *hit_ft,
				      stwuct mwx5_fwow_tabwe *miss_ft,
				      u32 min,
				      u32 max);

int mwx5dw_action_destwoy(stwuct mwx5dw_action *action);

u32 mwx5dw_action_get_pkt_wefowmat_id(stwuct mwx5dw_action *action);

int mwx5dw_definew_get(stwuct mwx5dw_domain *dmn, u16 fowmat_id,
		       u8 *dw_sewectows, u8 *byte_sewectows,
		       u8 *match_mask, u32 *definew_id);
void mwx5dw_definew_put(stwuct mwx5dw_domain *dmn, u32 definew_id);

static inwine boow
mwx5dw_is_suppowted(stwuct mwx5_cowe_dev *dev)
{
	wetuwn MWX5_CAP_GEN(dev, woce) &&
	       (MWX5_CAP_ESW_FWOWTABWE_FDB(dev, sw_ownew) ||
		(MWX5_CAP_ESW_FWOWTABWE_FDB(dev, sw_ownew_v2) &&
		 (MWX5_CAP_GEN(dev, steewing_fowmat_vewsion) <=
		  MWX5_STEEWING_FOWMAT_CONNECTX_7)));
}

/* buddy functions & stwuctuwe */

stwuct mwx5dw_icm_mw;

stwuct mwx5dw_icm_buddy_mem {
	unsigned wong		**bitmap;
	unsigned int		*num_fwee;
	u32			max_owdew;
	stwuct wist_head	wist_node;
	stwuct mwx5dw_icm_mw	*icm_mw;
	stwuct mwx5dw_icm_poow	*poow;

	/* Amount of memowy in used chunks - HW may be accessing this memowy */
	u64			used_memowy;

	/* Memowy optimisation */
	stwuct mwx5dw_ste	*ste_aww;
	stwuct wist_head	*miss_wist;
	u8			*hw_ste_aww;
};

int mwx5dw_buddy_init(stwuct mwx5dw_icm_buddy_mem *buddy,
		      unsigned int max_owdew);
void mwx5dw_buddy_cweanup(stwuct mwx5dw_icm_buddy_mem *buddy);
int mwx5dw_buddy_awwoc_mem(stwuct mwx5dw_icm_buddy_mem *buddy,
			   unsigned int owdew,
			   unsigned int *segment);
void mwx5dw_buddy_fwee_mem(stwuct mwx5dw_icm_buddy_mem *buddy,
			   unsigned int seg, unsigned int owdew);

#endif /* _MWX5DW_H_ */
