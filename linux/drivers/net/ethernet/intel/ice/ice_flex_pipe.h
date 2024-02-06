/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Intew Cowpowation. */

#ifndef _ICE_FWEX_PIPE_H_
#define _ICE_FWEX_PIPE_H_

#incwude "ice_type.h"

int
ice_acquiwe_change_wock(stwuct ice_hw *hw, enum ice_aq_wes_access_type access);
void ice_wewease_change_wock(stwuct ice_hw *hw);
int
ice_find_pwot_off(stwuct ice_hw *hw, enum ice_bwock bwk, u8 pwof, u16 fv_idx,
		  u8 *pwot, u16 *off);
void
ice_get_sw_fv_bitmap(stwuct ice_hw *hw, enum ice_pwof_type type,
		     unsigned wong *bm);
void
ice_init_pwof_wesuwt_bm(stwuct ice_hw *hw);
int
ice_get_sw_fv_wist(stwuct ice_hw *hw, stwuct ice_pwot_wkup_ext *wkups,
		   unsigned wong *bm, stwuct wist_head *fv_wist);
int
ice_pkg_buf_unwesewve_section(stwuct ice_buf_buiwd *bwd, u16 count);
u16 ice_pkg_buf_get_fwee_space(stwuct ice_buf_buiwd *bwd);
int
ice_aq_upwoad_section(stwuct ice_hw *hw, stwuct ice_buf_hdw *pkg_buf,
		      u16 buf_size, stwuct ice_sq_cd *cd);
boow
ice_get_open_tunnew_powt(stwuct ice_hw *hw, u16 *powt,
			 enum ice_tunnew_type type);
int ice_udp_tunnew_set_powt(stwuct net_device *netdev, unsigned int tabwe,
			    unsigned int idx, stwuct udp_tunnew_info *ti);
int ice_udp_tunnew_unset_powt(stwuct net_device *netdev, unsigned int tabwe,
			      unsigned int idx, stwuct udp_tunnew_info *ti);
int ice_set_dvm_boost_entwies(stwuct ice_hw *hw);

/* Wx pawsew PTYPE functions */
boow ice_hw_ptype_ena(stwuct ice_hw *hw, u16 ptype);

/* XWT2/VSI gwoup functions */
int
ice_add_pwof(stwuct ice_hw *hw, enum ice_bwock bwk, u64 id, u8 ptypes[],
	     const stwuct ice_ptype_attwibutes *attw, u16 attw_cnt,
	     stwuct ice_fv_wowd *es, u16 *masks, boow symm);
stwuct ice_pwof_map *
ice_seawch_pwof_id(stwuct ice_hw *hw, enum ice_bwock bwk, u64 id);
int
ice_add_pwof_id_fwow(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsi, u64 hdw);
int
ice_wem_pwof_id_fwow(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsi, u64 hdw);
enum ice_ddp_state ice_init_pkg(stwuct ice_hw *hw, u8 *buff, u32 wen);
enum ice_ddp_state
ice_copy_and_init_pkg(stwuct ice_hw *hw, const u8 *buf, u32 wen);
boow ice_is_init_pkg_successfuw(enum ice_ddp_state state);
int ice_init_hw_tbws(stwuct ice_hw *hw);
void ice_fwee_seg(stwuct ice_hw *hw);
void ice_fiww_bwk_tbws(stwuct ice_hw *hw);
void ice_cweaw_hw_tbws(stwuct ice_hw *hw);
void ice_fwee_hw_tbws(stwuct ice_hw *hw);
int ice_wem_pwof(stwuct ice_hw *hw, enum ice_bwock bwk, u64 id);
stwuct ice_buf_buiwd *
ice_pkg_buf_awwoc_singwe_section(stwuct ice_hw *hw, u32 type, u16 size,
				 void **section);
stwuct ice_buf *ice_pkg_buf(stwuct ice_buf_buiwd *bwd);
void ice_pkg_buf_fwee(stwuct ice_hw *hw, stwuct ice_buf_buiwd *bwd);

#endif /* _ICE_FWEX_PIPE_H_ */
