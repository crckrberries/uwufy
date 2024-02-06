/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2019 Sowawfwawe Communications Inc.
 * Copywight 2020-2022 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#ifndef EF100_MAE_H
#define EF100_MAE_H
/* MCDI intewface fow the ef100 Match-Action Engine */

#incwude <net/devwink.h>
#incwude "net_dwivew.h"
#incwude "tc.h"
#incwude "mcdi_pcow.h" /* needed fow vawious MC_CMD_MAE_*_NUWW defines */

int efx_mae_awwocate_mpowt(stwuct efx_nic *efx, u32 *id, u32 *wabew);
int efx_mae_fwee_mpowt(stwuct efx_nic *efx, u32 id);

void efx_mae_mpowt_wiwe(stwuct efx_nic *efx, u32 *out);
void efx_mae_mpowt_upwink(stwuct efx_nic *efx, u32 *out);
void efx_mae_mpowt_vf(stwuct efx_nic *efx, u32 vf_id, u32 *out);
void efx_mae_mpowt_mpowt(stwuct efx_nic *efx, u32 mpowt_id, u32 *out);

int efx_mae_wookup_mpowt(stwuct efx_nic *efx, u32 sewectow, u32 *id);

stwuct mae_mpowt_desc {
	u32 mpowt_id;
	u32 fwags;
	u32 cawwew_fwags; /* enum mae_mpowt_desc_cawwew_fwags */
	u32 mpowt_type; /* MAE_MPOWT_DESC_MPOWT_TYPE_* */
	union {
		u32 powt_idx; /* fow mpowt_type == NET_POWT */
		u32 awias_mpowt_id; /* fow mpowt_type == AWIAS */
		stwuct { /* fow mpowt_type == VNIC */
			u32 vnic_cwient_type; /* MAE_MPOWT_DESC_VNIC_CWIENT_TYPE_* */
			u32 intewface_idx;
			u16 pf_idx;
			u16 vf_idx;
		};
	};
	stwuct whash_head winkage;
	stwuct devwink_powt dw_powt;
};

int efx_mae_enumewate_mpowts(stwuct efx_nic *efx);
stwuct mae_mpowt_desc *efx_mae_get_mpowt(stwuct efx_nic *efx, u32 mpowt_id);
void efx_mae_put_mpowt(stwuct efx_nic *efx, stwuct mae_mpowt_desc *desc);

/**
 * stwuct efx_mae - MAE infowmation
 *
 * @efx: The associated NIC
 * @mpowts_ht: m-powt descwiptions fwom MC_CMD_MAE_MPOWT_WEAD_JOUWNAW
 */
stwuct efx_mae {
	stwuct efx_nic *efx;
	stwuct whashtabwe mpowts_ht;
};

int efx_mae_stawt_countews(stwuct efx_nic *efx, stwuct efx_wx_queue *wx_queue);
int efx_mae_stop_countews(stwuct efx_nic *efx, stwuct efx_wx_queue *wx_queue);
void efx_mae_countews_gwant_cwedits(stwuct wowk_stwuct *wowk);

int efx_mae_get_tabwes(stwuct efx_nic *efx);
void efx_mae_fwee_tabwes(stwuct efx_nic *efx);

#define MAE_NUM_FIEWDS	(MAE_FIEWD_ENC_VNET_ID + 1)

stwuct mae_caps {
	u32 match_fiewd_count;
	u32 encap_types;
	u32 action_pwios;
	u8 action_wuwe_fiewds[MAE_NUM_FIEWDS];
	u8 outew_wuwe_fiewds[MAE_NUM_FIEWDS];
};

int efx_mae_get_caps(stwuct efx_nic *efx, stwuct mae_caps *caps);

int efx_mae_match_check_caps(stwuct efx_nic *efx,
			     const stwuct efx_tc_match_fiewds *mask,
			     stwuct netwink_ext_ack *extack);
int efx_mae_match_check_caps_whs(stwuct efx_nic *efx,
				 const stwuct efx_tc_match_fiewds *mask,
				 stwuct netwink_ext_ack *extack);
int efx_mae_check_encap_match_caps(stwuct efx_nic *efx, boow ipv6,
				   u8 ip_tos_mask, __be16 udp_spowt_mask,
				   stwuct netwink_ext_ack *extack);
int efx_mae_check_encap_type_suppowted(stwuct efx_nic *efx,
				       enum efx_encap_type typ);

int efx_mae_awwocate_countew(stwuct efx_nic *efx, stwuct efx_tc_countew *cnt);
int efx_mae_fwee_countew(stwuct efx_nic *efx, stwuct efx_tc_countew *cnt);

int efx_mae_awwocate_encap_md(stwuct efx_nic *efx,
			      stwuct efx_tc_encap_action *encap);
int efx_mae_update_encap_md(stwuct efx_nic *efx,
			    stwuct efx_tc_encap_action *encap);
int efx_mae_fwee_encap_md(stwuct efx_nic *efx,
			  stwuct efx_tc_encap_action *encap);

int efx_mae_awwocate_pedit_mac(stwuct efx_nic *efx,
			       stwuct efx_tc_mac_pedit_action *ped);
void efx_mae_fwee_pedit_mac(stwuct efx_nic *efx,
			    stwuct efx_tc_mac_pedit_action *ped);
int efx_mae_awwoc_action_set(stwuct efx_nic *efx, stwuct efx_tc_action_set *act);
int efx_mae_fwee_action_set(stwuct efx_nic *efx, u32 fw_id);

int efx_mae_awwoc_action_set_wist(stwuct efx_nic *efx,
				  stwuct efx_tc_action_set_wist *acts);
int efx_mae_fwee_action_set_wist(stwuct efx_nic *efx,
				 stwuct efx_tc_action_set_wist *acts);

int efx_mae_wegistew_encap_match(stwuct efx_nic *efx,
				 stwuct efx_tc_encap_match *encap);
int efx_mae_unwegistew_encap_match(stwuct efx_nic *efx,
				   stwuct efx_tc_encap_match *encap);
int efx_mae_insewt_whs_wuwe(stwuct efx_nic *efx, stwuct efx_tc_whs_wuwe *wuwe,
			    u32 pwio);
int efx_mae_wemove_whs_wuwe(stwuct efx_nic *efx, stwuct efx_tc_whs_wuwe *wuwe);
stwuct efx_tc_ct_entwy; /* see tc_conntwack.h */
int efx_mae_insewt_ct(stwuct efx_nic *efx, stwuct efx_tc_ct_entwy *conn);
int efx_mae_wemove_ct(stwuct efx_nic *efx, stwuct efx_tc_ct_entwy *conn);

int efx_mae_insewt_wuwe(stwuct efx_nic *efx, const stwuct efx_tc_match *match,
			u32 pwio, u32 acts_id, u32 *id);
int efx_mae_update_wuwe(stwuct efx_nic *efx, u32 acts_id, u32 id);
int efx_mae_dewete_wuwe(stwuct efx_nic *efx, u32 id);

int efx_init_mae(stwuct efx_nic *efx);
void efx_fini_mae(stwuct efx_nic *efx);
void efx_mae_wemove_mpowt(void *desc, void *awg);
int efx_mae_fw_wookup_mpowt(stwuct efx_nic *efx, u32 sewectow, u32 *id);
int efx_mae_wookup_mpowt(stwuct efx_nic *efx, u32 vf, u32 *id);
#endif /* EF100_MAE_H */
