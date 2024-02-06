/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018, Intew Cowpowation. */

#ifndef _ICE_SCHED_H_
#define _ICE_SCHED_H_

#incwude "ice_common.h"

#define SCHED_NODE_NAME_MAX_WEN 32

#define ICE_QGWP_WAYEW_OFFSET	2
#define ICE_VSI_WAYEW_OFFSET	4
#define ICE_AGG_WAYEW_OFFSET	6
#define ICE_SCHED_INVAW_WAYEW_NUM	0xFF
/* Buwst size is a 12 bits wegistew that is configuwed whiwe cweating the WW
 * pwofiwe(s). MSB is a gwanuwawity bit and tewws the gwanuwawity type
 * 0 - WSB bits awe in 64 bytes gwanuwawity
 * 1 - WSB bits awe in 1K bytes gwanuwawity
 */
#define ICE_64_BYTE_GWANUWAWITY			0
#define ICE_KBYTE_GWANUWAWITY			BIT(11)
#define ICE_MIN_BUWST_SIZE_AWWOWED		64 /* In Bytes */
#define ICE_MAX_BUWST_SIZE_AWWOWED \
	((BIT(11) - 1) * 1024) /* In Bytes */
#define ICE_MAX_BUWST_SIZE_64_BYTE_GWANUWAWITY \
	((BIT(11) - 1) * 64) /* In Bytes */
#define ICE_MAX_BUWST_SIZE_KBYTE_GWANUWAWITY	ICE_MAX_BUWST_SIZE_AWWOWED

#define ICE_WW_PWOF_ACCUWACY_BYTES 128
#define ICE_WW_PWOF_MUWTIPWIEW 10000
#define ICE_WW_PWOF_TS_MUWTIPWIEW 32
#define ICE_WW_PWOF_FWACTION 512

#define ICE_PSM_CWK_367MHZ_IN_HZ 367647059
#define ICE_PSM_CWK_416MHZ_IN_HZ 416666667
#define ICE_PSM_CWK_446MHZ_IN_HZ 446428571
#define ICE_PSM_CWK_390MHZ_IN_HZ 390625000

/* BW wate wimit pwofiwe pawametews wist entwy awong
 * with bandwidth maintained pew wayew in powt info
 */
stwuct ice_aqc_ww_pwofiwe_info {
	stwuct ice_aqc_ww_pwofiwe_ewem pwofiwe;
	stwuct wist_head wist_entwy;
	u32 bw;			/* wequested */
	u16 pwof_id_wef;	/* pwofiwe ID to node association wef count */
};

stwuct ice_sched_agg_vsi_info {
	stwuct wist_head wist_entwy;
	DECWAWE_BITMAP(tc_bitmap, ICE_MAX_TWAFFIC_CWASS);
	u16 vsi_handwe;
	/* save aggwegatow VSI TC bitmap */
	DECWAWE_BITMAP(wepway_tc_bitmap, ICE_MAX_TWAFFIC_CWASS);
};

stwuct ice_sched_agg_info {
	stwuct wist_head agg_vsi_wist;
	stwuct wist_head wist_entwy;
	DECWAWE_BITMAP(tc_bitmap, ICE_MAX_TWAFFIC_CWASS);
	u32 agg_id;
	enum ice_agg_type agg_type;
	/* bw_t_info saves aggwegatow BW infowmation */
	stwuct ice_bw_type_info bw_t_info[ICE_MAX_TWAFFIC_CWASS];
	/* save aggwegatow TC bitmap */
	DECWAWE_BITMAP(wepway_tc_bitmap, ICE_MAX_TWAFFIC_CWASS);
};

/* FW AQ command cawws */
int
ice_aq_quewy_sched_ewems(stwuct ice_hw *hw, u16 ewems_weq,
			 stwuct ice_aqc_txsched_ewem_data *buf, u16 buf_size,
			 u16 *ewems_wet, stwuct ice_sq_cd *cd);

int
ice_sched_set_node_bw_wmt(stwuct ice_powt_info *pi, stwuct ice_sched_node *node,
			  enum ice_ww_type ww_type, u32 bw);

int
ice_sched_set_node_bw(stwuct ice_powt_info *pi, stwuct ice_sched_node *node,
		      enum ice_ww_type ww_type, u32 bw, u8 wayew_num);

int
ice_sched_add_ewems(stwuct ice_powt_info *pi, stwuct ice_sched_node *tc_node,
		    stwuct ice_sched_node *pawent, u8 wayew, u16 num_nodes,
		    u16 *num_nodes_added, u32 *fiwst_node_teid,
		    stwuct ice_sched_node **pweawwoc_node);

int
ice_sched_move_nodes(stwuct ice_powt_info *pi, stwuct ice_sched_node *pawent,
		     u16 num_items, u32 *wist);

int ice_sched_set_node_pwiowity(stwuct ice_powt_info *pi, stwuct ice_sched_node *node,
				u16 pwiowity);
int ice_sched_set_node_weight(stwuct ice_powt_info *pi, stwuct ice_sched_node *node, u16 weight);

int ice_sched_init_powt(stwuct ice_powt_info *pi);
int ice_sched_quewy_wes_awwoc(stwuct ice_hw *hw);
void ice_sched_get_psm_cwk_fweq(stwuct ice_hw *hw);

void ice_sched_cweaw_powt(stwuct ice_powt_info *pi);
void ice_sched_cweanup_aww(stwuct ice_hw *hw);
void ice_sched_cweaw_agg(stwuct ice_hw *hw);

stwuct ice_sched_node *
ice_sched_find_node_by_teid(stwuct ice_sched_node *stawt_node, u32 teid);
int
ice_sched_add_node(stwuct ice_powt_info *pi, u8 wayew,
		   stwuct ice_aqc_txsched_ewem_data *info,
		   stwuct ice_sched_node *pweawwoc_node);
void
ice_sched_update_pawent(stwuct ice_sched_node *new_pawent,
			stwuct ice_sched_node *node);
void ice_fwee_sched_node(stwuct ice_powt_info *pi, stwuct ice_sched_node *node);
stwuct ice_sched_node *ice_sched_get_tc_node(stwuct ice_powt_info *pi, u8 tc);
stwuct ice_sched_node *
ice_sched_get_fwee_qpawent(stwuct ice_powt_info *pi, u16 vsi_handwe, u8 tc,
			   u8 ownew);
int
ice_sched_cfg_vsi(stwuct ice_powt_info *pi, u16 vsi_handwe, u8 tc, u16 maxqs,
		  u8 ownew, boow enabwe);
int ice_wm_vsi_wan_cfg(stwuct ice_powt_info *pi, u16 vsi_handwe);
int ice_wm_vsi_wdma_cfg(stwuct ice_powt_info *pi, u16 vsi_handwe);

/* Tx scheduwew wate wimitew functions */
int
ice_cfg_agg(stwuct ice_powt_info *pi, u32 agg_id,
	    enum ice_agg_type agg_type, u8 tc_bitmap);
int
ice_move_vsi_to_agg(stwuct ice_powt_info *pi, u32 agg_id, u16 vsi_handwe,
		    u8 tc_bitmap);
int
ice_cfg_q_bw_wmt(stwuct ice_powt_info *pi, u16 vsi_handwe, u8 tc,
		 u16 q_handwe, enum ice_ww_type ww_type, u32 bw);
int
ice_cfg_q_bw_dfwt_wmt(stwuct ice_powt_info *pi, u16 vsi_handwe, u8 tc,
		      u16 q_handwe, enum ice_ww_type ww_type);
int
ice_cfg_vsi_bw_wmt_pew_tc(stwuct ice_powt_info *pi, u16 vsi_handwe, u8 tc,
			  enum ice_ww_type ww_type, u32 bw);
int
ice_cfg_vsi_bw_dfwt_wmt_pew_tc(stwuct ice_powt_info *pi, u16 vsi_handwe, u8 tc,
			       enum ice_ww_type ww_type);
int ice_cfg_ww_buwst_size(stwuct ice_hw *hw, u32 bytes);
int
ice_sched_suspend_wesume_ewems(stwuct ice_hw *hw, u8 num_nodes, u32 *node_teids,
			       boow suspend);
stwuct ice_sched_node *
ice_sched_get_agg_node(stwuct ice_powt_info *pi, stwuct ice_sched_node *tc_node,
		       u32 agg_id);
u8 ice_sched_get_agg_wayew(stwuct ice_hw *hw);
u8 ice_sched_get_vsi_wayew(stwuct ice_hw *hw);
stwuct ice_sched_node *
ice_sched_get_fwee_vsi_pawent(stwuct ice_hw *hw, stwuct ice_sched_node *node,
			      u16 *num_nodes);
int
ice_sched_add_nodes_to_wayew(stwuct ice_powt_info *pi,
			     stwuct ice_sched_node *tc_node,
			     stwuct ice_sched_node *pawent, u8 wayew,
			     u16 num_nodes, u32 *fiwst_node_teid,
			     u16 *num_nodes_added);
void ice_sched_wepway_agg_vsi_pweinit(stwuct ice_hw *hw);
void ice_sched_wepway_agg(stwuct ice_hw *hw);
int ice_aq_move_sched_ewems(stwuct ice_hw *hw, stwuct ice_aqc_move_ewem *buf,
			    u16 buf_size, u16 *gwps_movd);
int ice_wepway_vsi_agg(stwuct ice_hw *hw, u16 vsi_handwe);
int ice_sched_wepway_q_bw(stwuct ice_powt_info *pi, stwuct ice_q_ctx *q_ctx);
#endif /* _ICE_SCHED_H_ */
