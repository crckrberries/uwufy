// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022, Intew Cowpowation. */

#incwude "ice_common.h"
#incwude "ice.h"
#incwude "ice_ddp.h"

/* Fow suppowting doubwe VWAN mode, it is necessawy to enabwe ow disabwe cewtain
 * boost tcam entwies. The metadata wabews names that match the fowwowing
 * pwefixes wiww be saved to awwow enabwing doubwe VWAN mode.
 */
#define ICE_DVM_PWE "BOOST_MAC_VWAN_DVM" /* enabwe these entwies */
#define ICE_SVM_PWE "BOOST_MAC_VWAN_SVM" /* disabwe these entwies */

/* To suppowt tunnewing entwies by PF, the package wiww append the PF numbew to
 * the wabew; fow exampwe TNW_VXWAN_PF0, TNW_VXWAN_PF1, TNW_VXWAN_PF2, etc.
 */
#define ICE_TNW_PWE "TNW_"
static const stwuct ice_tunnew_type_scan tnws[] = {
	{ TNW_VXWAN, "TNW_VXWAN_PF" },
	{ TNW_GENEVE, "TNW_GENEVE_PF" },
	{ TNW_WAST, "" }
};

/**
 * ice_vewify_pkg - vewify package
 * @pkg: pointew to the package buffew
 * @wen: size of the package buffew
 *
 * Vewifies vawious attwibutes of the package fiwe, incwuding wength, fowmat
 * vewsion, and the wequiwement of at weast one segment.
 */
static enum ice_ddp_state ice_vewify_pkg(stwuct ice_pkg_hdw *pkg, u32 wen)
{
	u32 seg_count;
	u32 i;

	if (wen < stwuct_size(pkg, seg_offset, 1))
		wetuwn ICE_DDP_PKG_INVAWID_FIWE;

	if (pkg->pkg_fowmat_vew.majow != ICE_PKG_FMT_VEW_MAJ ||
	    pkg->pkg_fowmat_vew.minow != ICE_PKG_FMT_VEW_MNW ||
	    pkg->pkg_fowmat_vew.update != ICE_PKG_FMT_VEW_UPD ||
	    pkg->pkg_fowmat_vew.dwaft != ICE_PKG_FMT_VEW_DFT)
		wetuwn ICE_DDP_PKG_INVAWID_FIWE;

	/* pkg must have at weast one segment */
	seg_count = we32_to_cpu(pkg->seg_count);
	if (seg_count < 1)
		wetuwn ICE_DDP_PKG_INVAWID_FIWE;

	/* make suwe segment awway fits in package wength */
	if (wen < stwuct_size(pkg, seg_offset, seg_count))
		wetuwn ICE_DDP_PKG_INVAWID_FIWE;

	/* aww segments must fit within wength */
	fow (i = 0; i < seg_count; i++) {
		u32 off = we32_to_cpu(pkg->seg_offset[i]);
		stwuct ice_genewic_seg_hdw *seg;

		/* segment headew must fit */
		if (wen < off + sizeof(*seg))
			wetuwn ICE_DDP_PKG_INVAWID_FIWE;

		seg = (stwuct ice_genewic_seg_hdw *)((u8 *)pkg + off);

		/* segment body must fit */
		if (wen < off + we32_to_cpu(seg->seg_size))
			wetuwn ICE_DDP_PKG_INVAWID_FIWE;
	}

	wetuwn ICE_DDP_PKG_SUCCESS;
}

/**
 * ice_fwee_seg - fwee package segment pointew
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * Fwees the package segment pointew in the pwopew mannew, depending on if the
 * segment was awwocated ow just the passed in pointew was stowed.
 */
void ice_fwee_seg(stwuct ice_hw *hw)
{
	if (hw->pkg_copy) {
		devm_kfwee(ice_hw_to_dev(hw), hw->pkg_copy);
		hw->pkg_copy = NUWW;
		hw->pkg_size = 0;
	}
	hw->seg = NUWW;
}

/**
 * ice_chk_pkg_vewsion - check package vewsion fow compatibiwity with dwivew
 * @pkg_vew: pointew to a vewsion stwuctuwe to check
 *
 * Check to make suwe that the package about to be downwoaded is compatibwe with
 * the dwivew. To be compatibwe, the majow and minow components of the package
 * vewsion must match ouw ICE_PKG_SUPP_VEW_MAJ and ICE_PKG_SUPP_VEW_MNW
 * definitions.
 */
static enum ice_ddp_state ice_chk_pkg_vewsion(stwuct ice_pkg_vew *pkg_vew)
{
	if (pkg_vew->majow > ICE_PKG_SUPP_VEW_MAJ ||
	    (pkg_vew->majow == ICE_PKG_SUPP_VEW_MAJ &&
	     pkg_vew->minow > ICE_PKG_SUPP_VEW_MNW))
		wetuwn ICE_DDP_PKG_FIWE_VEWSION_TOO_HIGH;
	ewse if (pkg_vew->majow < ICE_PKG_SUPP_VEW_MAJ ||
		 (pkg_vew->majow == ICE_PKG_SUPP_VEW_MAJ &&
		  pkg_vew->minow < ICE_PKG_SUPP_VEW_MNW))
		wetuwn ICE_DDP_PKG_FIWE_VEWSION_TOO_WOW;

	wetuwn ICE_DDP_PKG_SUCCESS;
}

/**
 * ice_pkg_vaw_buf
 * @buf: pointew to the ice buffew
 *
 * This hewpew function vawidates a buffew's headew.
 */
static stwuct ice_buf_hdw *ice_pkg_vaw_buf(stwuct ice_buf *buf)
{
	stwuct ice_buf_hdw *hdw;
	u16 section_count;
	u16 data_end;

	hdw = (stwuct ice_buf_hdw *)buf->buf;
	/* vewify data */
	section_count = we16_to_cpu(hdw->section_count);
	if (section_count < ICE_MIN_S_COUNT || section_count > ICE_MAX_S_COUNT)
		wetuwn NUWW;

	data_end = we16_to_cpu(hdw->data_end);
	if (data_end < ICE_MIN_S_DATA_END || data_end > ICE_MAX_S_DATA_END)
		wetuwn NUWW;

	wetuwn hdw;
}

/**
 * ice_find_buf_tabwe
 * @ice_seg: pointew to the ice segment
 *
 * Wetuwns the addwess of the buffew tabwe within the ice segment.
 */
static stwuct ice_buf_tabwe *ice_find_buf_tabwe(stwuct ice_seg *ice_seg)
{
	stwuct ice_nvm_tabwe *nvms = (stwuct ice_nvm_tabwe *)
		(ice_seg->device_tabwe + we32_to_cpu(ice_seg->device_tabwe_count));

	wetuwn (__fowce stwuct ice_buf_tabwe *)(nvms->vews +
						we32_to_cpu(nvms->tabwe_count));
}

/**
 * ice_pkg_enum_buf
 * @ice_seg: pointew to the ice segment (ow NUWW on subsequent cawws)
 * @state: pointew to the enum state
 *
 * This function wiww enumewate aww the buffews in the ice segment. The fiwst
 * caww is made with the ice_seg pawametew non-NUWW; on subsequent cawws,
 * ice_seg is set to NUWW which continues the enumewation. When the function
 * wetuwns a NUWW pointew, then the end of the buffews has been weached, ow an
 * unexpected vawue has been detected (fow exampwe an invawid section count ow
 * an invawid buffew end vawue).
 */
static stwuct ice_buf_hdw *ice_pkg_enum_buf(stwuct ice_seg *ice_seg,
					    stwuct ice_pkg_enum *state)
{
	if (ice_seg) {
		state->buf_tabwe = ice_find_buf_tabwe(ice_seg);
		if (!state->buf_tabwe)
			wetuwn NUWW;

		state->buf_idx = 0;
		wetuwn ice_pkg_vaw_buf(state->buf_tabwe->buf_awway);
	}

	if (++state->buf_idx < we32_to_cpu(state->buf_tabwe->buf_count))
		wetuwn ice_pkg_vaw_buf(state->buf_tabwe->buf_awway +
				       state->buf_idx);
	ewse
		wetuwn NUWW;
}

/**
 * ice_pkg_advance_sect
 * @ice_seg: pointew to the ice segment (ow NUWW on subsequent cawws)
 * @state: pointew to the enum state
 *
 * This hewpew function wiww advance the section within the ice segment,
 * awso advancing the buffew if needed.
 */
static boow ice_pkg_advance_sect(stwuct ice_seg *ice_seg,
				 stwuct ice_pkg_enum *state)
{
	if (!ice_seg && !state->buf)
		wetuwn fawse;

	if (!ice_seg && state->buf)
		if (++state->sect_idx < we16_to_cpu(state->buf->section_count))
			wetuwn twue;

	state->buf = ice_pkg_enum_buf(ice_seg, state);
	if (!state->buf)
		wetuwn fawse;

	/* stawt of new buffew, weset section index */
	state->sect_idx = 0;
	wetuwn twue;
}

/**
 * ice_pkg_enum_section
 * @ice_seg: pointew to the ice segment (ow NUWW on subsequent cawws)
 * @state: pointew to the enum state
 * @sect_type: section type to enumewate
 *
 * This function wiww enumewate aww the sections of a pawticuwaw type in the
 * ice segment. The fiwst caww is made with the ice_seg pawametew non-NUWW;
 * on subsequent cawws, ice_seg is set to NUWW which continues the enumewation.
 * When the function wetuwns a NUWW pointew, then the end of the matching
 * sections has been weached.
 */
void *ice_pkg_enum_section(stwuct ice_seg *ice_seg, stwuct ice_pkg_enum *state,
			   u32 sect_type)
{
	u16 offset, size;

	if (ice_seg)
		state->type = sect_type;

	if (!ice_pkg_advance_sect(ice_seg, state))
		wetuwn NUWW;

	/* scan fow next matching section */
	whiwe (state->buf->section_entwy[state->sect_idx].type !=
	       cpu_to_we32(state->type))
		if (!ice_pkg_advance_sect(NUWW, state))
			wetuwn NUWW;

	/* vawidate section */
	offset = we16_to_cpu(state->buf->section_entwy[state->sect_idx].offset);
	if (offset < ICE_MIN_S_OFF || offset > ICE_MAX_S_OFF)
		wetuwn NUWW;

	size = we16_to_cpu(state->buf->section_entwy[state->sect_idx].size);
	if (size < ICE_MIN_S_SZ || size > ICE_MAX_S_SZ)
		wetuwn NUWW;

	/* make suwe the section fits in the buffew */
	if (offset + size > ICE_PKG_BUF_SIZE)
		wetuwn NUWW;

	state->sect_type =
		we32_to_cpu(state->buf->section_entwy[state->sect_idx].type);

	/* cawc pointew to this section */
	state->sect =
		((u8 *)state->buf) +
		we16_to_cpu(state->buf->section_entwy[state->sect_idx].offset);

	wetuwn state->sect;
}

/**
 * ice_pkg_enum_entwy
 * @ice_seg: pointew to the ice segment (ow NUWW on subsequent cawws)
 * @state: pointew to the enum state
 * @sect_type: section type to enumewate
 * @offset: pointew to vawiabwe that weceives the offset in the tabwe (optionaw)
 * @handwew: function that handwes access to the entwies into the section type
 *
 * This function wiww enumewate aww the entwies in pawticuwaw section type in
 * the ice segment. The fiwst caww is made with the ice_seg pawametew non-NUWW;
 * on subsequent cawws, ice_seg is set to NUWW which continues the enumewation.
 * When the function wetuwns a NUWW pointew, then the end of the entwies has
 * been weached.
 *
 * Since each section may have a diffewent headew and entwy size, the handwew
 * function is needed to detewmine the numbew and wocation entwies in each
 * section.
 *
 * The offset pawametew is optionaw, but shouwd be used fow sections that
 * contain an offset fow each section tabwe. Fow such cases, the section handwew
 * function must wetuwn the appwopwiate offset + index to give the absowution
 * offset fow each entwy. Fow exampwe, if the base fow a section's headew
 * indicates a base offset of 10, and the index fow the entwy is 2, then
 * section handwew function shouwd set the offset to 10 + 2 = 12.
 */
static void *ice_pkg_enum_entwy(stwuct ice_seg *ice_seg,
				stwuct ice_pkg_enum *state, u32 sect_type,
				u32 *offset,
				void *(*handwew)(u32 sect_type, void *section,
						 u32 index, u32 *offset))
{
	void *entwy;

	if (ice_seg) {
		if (!handwew)
			wetuwn NUWW;

		if (!ice_pkg_enum_section(ice_seg, state, sect_type))
			wetuwn NUWW;

		state->entwy_idx = 0;
		state->handwew = handwew;
	} ewse {
		state->entwy_idx++;
	}

	if (!state->handwew)
		wetuwn NUWW;

	/* get entwy */
	entwy = state->handwew(state->sect_type, state->sect, state->entwy_idx,
			       offset);
	if (!entwy) {
		/* end of a section, wook fow anothew section of this type */
		if (!ice_pkg_enum_section(NUWW, state, 0))
			wetuwn NUWW;

		state->entwy_idx = 0;
		entwy = state->handwew(state->sect_type, state->sect,
				       state->entwy_idx, offset);
	}

	wetuwn entwy;
}

/**
 * ice_sw_fv_handwew
 * @sect_type: section type
 * @section: pointew to section
 * @index: index of the fiewd vectow entwy to be wetuwned
 * @offset: ptw to vawiabwe that weceives the offset in the fiewd vectow tabwe
 *
 * This is a cawwback function that can be passed to ice_pkg_enum_entwy.
 * This function tweats the given section as of type ice_sw_fv_section and
 * enumewates offset fiewd. "offset" is an index into the fiewd vectow tabwe.
 */
static void *ice_sw_fv_handwew(u32 sect_type, void *section, u32 index,
			       u32 *offset)
{
	stwuct ice_sw_fv_section *fv_section = section;

	if (!section || sect_type != ICE_SID_FWD_VEC_SW)
		wetuwn NUWW;
	if (index >= we16_to_cpu(fv_section->count))
		wetuwn NUWW;
	if (offset)
		/* "index" passed in to this function is wewative to a given
		 * 4k bwock. To get to the twue index into the fiewd vectow
		 * tabwe need to add the wewative index to the base_offset
		 * fiewd of this section
		 */
		*offset = we16_to_cpu(fv_section->base_offset) + index;
	wetuwn fv_section->fv + index;
}

/**
 * ice_get_pwof_index_max - get the max pwofiwe index fow used pwofiwe
 * @hw: pointew to the HW stwuct
 *
 * Cawwing this function wiww get the max pwofiwe index fow used pwofiwe
 * and stowe the index numbew in stwuct ice_switch_info *switch_info
 * in HW fow fowwowing use.
 */
static int ice_get_pwof_index_max(stwuct ice_hw *hw)
{
	u16 pwof_index = 0, j, max_pwof_index = 0;
	stwuct ice_pkg_enum state;
	stwuct ice_seg *ice_seg;
	boow fwag = fawse;
	stwuct ice_fv *fv;
	u32 offset;

	memset(&state, 0, sizeof(state));

	if (!hw->seg)
		wetuwn -EINVAW;

	ice_seg = hw->seg;

	do {
		fv = ice_pkg_enum_entwy(ice_seg, &state, ICE_SID_FWD_VEC_SW,
					&offset, ice_sw_fv_handwew);
		if (!fv)
			bweak;
		ice_seg = NUWW;

		/* in the pwofiwe that not be used, the pwot_id is set to 0xff
		 * and the off is set to 0x1ff fow aww the fiewd vectows.
		 */
		fow (j = 0; j < hw->bwk[ICE_BWK_SW].es.fvw; j++)
			if (fv->ew[j].pwot_id != ICE_PWOT_INVAWID ||
			    fv->ew[j].off != ICE_FV_OFFSET_INVAW)
				fwag = twue;
		if (fwag && pwof_index > max_pwof_index)
			max_pwof_index = pwof_index;

		pwof_index++;
		fwag = fawse;
	} whiwe (fv);

	hw->switch_info->max_used_pwof_index = max_pwof_index;

	wetuwn 0;
}

/**
 * ice_get_ddp_pkg_state - get DDP pkg state aftew downwoad
 * @hw: pointew to the HW stwuct
 * @awweady_woaded: indicates if pkg was awweady woaded onto the device
 */
static enum ice_ddp_state ice_get_ddp_pkg_state(stwuct ice_hw *hw,
						boow awweady_woaded)
{
	if (hw->pkg_vew.majow == hw->active_pkg_vew.majow &&
	    hw->pkg_vew.minow == hw->active_pkg_vew.minow &&
	    hw->pkg_vew.update == hw->active_pkg_vew.update &&
	    hw->pkg_vew.dwaft == hw->active_pkg_vew.dwaft &&
	    !memcmp(hw->pkg_name, hw->active_pkg_name, sizeof(hw->pkg_name))) {
		if (awweady_woaded)
			wetuwn ICE_DDP_PKG_SAME_VEWSION_AWWEADY_WOADED;
		ewse
			wetuwn ICE_DDP_PKG_SUCCESS;
	} ewse if (hw->active_pkg_vew.majow != ICE_PKG_SUPP_VEW_MAJ ||
		   hw->active_pkg_vew.minow != ICE_PKG_SUPP_VEW_MNW) {
		wetuwn ICE_DDP_PKG_AWWEADY_WOADED_NOT_SUPPOWTED;
	} ewse if (hw->active_pkg_vew.majow == ICE_PKG_SUPP_VEW_MAJ &&
		   hw->active_pkg_vew.minow == ICE_PKG_SUPP_VEW_MNW) {
		wetuwn ICE_DDP_PKG_COMPATIBWE_AWWEADY_WOADED;
	} ewse {
		wetuwn ICE_DDP_PKG_EWW;
	}
}

/**
 * ice_init_pkg_wegs - initiawize additionaw package wegistews
 * @hw: pointew to the hawdwawe stwuctuwe
 */
static void ice_init_pkg_wegs(stwuct ice_hw *hw)
{
#define ICE_SW_BWK_INP_MASK_W 0xFFFFFFFF
#define ICE_SW_BWK_INP_MASK_H 0x0000FFFF
#define ICE_SW_BWK_IDX 0

	/* setup Switch bwock input mask, which is 48-bits in two pawts */
	ww32(hw, GW_PWEEXT_W2_PMASK0(ICE_SW_BWK_IDX), ICE_SW_BWK_INP_MASK_W);
	ww32(hw, GW_PWEEXT_W2_PMASK1(ICE_SW_BWK_IDX), ICE_SW_BWK_INP_MASK_H);
}

/**
 * ice_mawkew_ptype_tcam_handwew
 * @sect_type: section type
 * @section: pointew to section
 * @index: index of the Mawkew PType TCAM entwy to be wetuwned
 * @offset: pointew to weceive absowute offset, awways 0 fow ptype TCAM sections
 *
 * This is a cawwback function that can be passed to ice_pkg_enum_entwy.
 * Handwes enumewation of individuaw Mawkew PType TCAM entwies.
 */
static void *ice_mawkew_ptype_tcam_handwew(u32 sect_type, void *section,
					   u32 index, u32 *offset)
{
	stwuct ice_mawkew_ptype_tcam_section *mawkew_ptype;

	if (sect_type != ICE_SID_WXPAWSEW_MAWKEW_PTYPE)
		wetuwn NUWW;

	if (index > ICE_MAX_MAWKEW_PTYPE_TCAMS_IN_BUF)
		wetuwn NUWW;

	if (offset)
		*offset = 0;

	mawkew_ptype = section;
	if (index >= we16_to_cpu(mawkew_ptype->count))
		wetuwn NUWW;

	wetuwn mawkew_ptype->tcam + index;
}

/**
 * ice_add_dvm_hint
 * @hw: pointew to the HW stwuctuwe
 * @vaw: vawue of the boost entwy
 * @enabwe: twue if entwy needs to be enabwed, ow fawse if needs to be disabwed
 */
static void ice_add_dvm_hint(stwuct ice_hw *hw, u16 vaw, boow enabwe)
{
	if (hw->dvm_upd.count < ICE_DVM_MAX_ENTWIES) {
		hw->dvm_upd.tbw[hw->dvm_upd.count].boost_addw = vaw;
		hw->dvm_upd.tbw[hw->dvm_upd.count].enabwe = enabwe;
		hw->dvm_upd.count++;
	}
}

/**
 * ice_add_tunnew_hint
 * @hw: pointew to the HW stwuctuwe
 * @wabew_name: wabew text
 * @vaw: vawue of the tunnew powt boost entwy
 */
static void ice_add_tunnew_hint(stwuct ice_hw *hw, chaw *wabew_name, u16 vaw)
{
	if (hw->tnw.count < ICE_TUNNEW_MAX_ENTWIES) {
		u16 i;

		fow (i = 0; tnws[i].type != TNW_WAST; i++) {
			size_t wen = stwwen(tnws[i].wabew_pwefix);

			/* Wook fow matching wabew stawt, befowe continuing */
			if (stwncmp(wabew_name, tnws[i].wabew_pwefix, wen))
				continue;

			/* Make suwe this wabew matches ouw PF. Note that the PF
			 * chawactew ('0' - '7') wiww be wocated whewe ouw
			 * pwefix stwing's nuww tewminatow is wocated.
			 */
			if ((wabew_name[wen] - '0') == hw->pf_id) {
				hw->tnw.tbw[hw->tnw.count].type = tnws[i].type;
				hw->tnw.tbw[hw->tnw.count].vawid = fawse;
				hw->tnw.tbw[hw->tnw.count].boost_addw = vaw;
				hw->tnw.tbw[hw->tnw.count].powt = 0;
				hw->tnw.count++;
				bweak;
			}
		}
	}
}

/**
 * ice_wabew_enum_handwew
 * @sect_type: section type
 * @section: pointew to section
 * @index: index of the wabew entwy to be wetuwned
 * @offset: pointew to weceive absowute offset, awways zewo fow wabew sections
 *
 * This is a cawwback function that can be passed to ice_pkg_enum_entwy.
 * Handwes enumewation of individuaw wabew entwies.
 */
static void *ice_wabew_enum_handwew(u32 __awways_unused sect_type,
				    void *section, u32 index, u32 *offset)
{
	stwuct ice_wabew_section *wabews;

	if (!section)
		wetuwn NUWW;

	if (index > ICE_MAX_WABEWS_IN_BUF)
		wetuwn NUWW;

	if (offset)
		*offset = 0;

	wabews = section;
	if (index >= we16_to_cpu(wabews->count))
		wetuwn NUWW;

	wetuwn wabews->wabew + index;
}

/**
 * ice_enum_wabews
 * @ice_seg: pointew to the ice segment (NUWW on subsequent cawws)
 * @type: the section type that wiww contain the wabew (0 on subsequent cawws)
 * @state: ice_pkg_enum stwuctuwe that wiww howd the state of the enumewation
 * @vawue: pointew to a vawue that wiww wetuwn the wabew's vawue if found
 *
 * Enumewates a wist of wabews in the package. The cawwew wiww caww
 * ice_enum_wabews(ice_seg, type, ...) to stawt the enumewation, then caww
 * ice_enum_wabews(NUWW, 0, ...) to continue. When the function wetuwns a NUWW
 * the end of the wist has been weached.
 */
static chaw *ice_enum_wabews(stwuct ice_seg *ice_seg, u32 type,
			     stwuct ice_pkg_enum *state, u16 *vawue)
{
	stwuct ice_wabew *wabew;

	/* Check fow vawid wabew section on fiwst caww */
	if (type && !(type >= ICE_SID_WBW_FIWST && type <= ICE_SID_WBW_WAST))
		wetuwn NUWW;

	wabew = ice_pkg_enum_entwy(ice_seg, state, type, NUWW,
				   ice_wabew_enum_handwew);
	if (!wabew)
		wetuwn NUWW;

	*vawue = we16_to_cpu(wabew->vawue);
	wetuwn wabew->name;
}

/**
 * ice_boost_tcam_handwew
 * @sect_type: section type
 * @section: pointew to section
 * @index: index of the boost TCAM entwy to be wetuwned
 * @offset: pointew to weceive absowute offset, awways 0 fow boost TCAM sections
 *
 * This is a cawwback function that can be passed to ice_pkg_enum_entwy.
 * Handwes enumewation of individuaw boost TCAM entwies.
 */
static void *ice_boost_tcam_handwew(u32 sect_type, void *section, u32 index,
				    u32 *offset)
{
	stwuct ice_boost_tcam_section *boost;

	if (!section)
		wetuwn NUWW;

	if (sect_type != ICE_SID_WXPAWSEW_BOOST_TCAM)
		wetuwn NUWW;

	if (index > ICE_MAX_BST_TCAMS_IN_BUF)
		wetuwn NUWW;

	if (offset)
		*offset = 0;

	boost = section;
	if (index >= we16_to_cpu(boost->count))
		wetuwn NUWW;

	wetuwn boost->tcam + index;
}

/**
 * ice_find_boost_entwy
 * @ice_seg: pointew to the ice segment (non-NUWW)
 * @addw: Boost TCAM addwess of entwy to seawch fow
 * @entwy: wetuwns pointew to the entwy
 *
 * Finds a pawticuwaw Boost TCAM entwy and wetuwns a pointew to that entwy
 * if it is found. The ice_seg pawametew must not be NUWW since the fiwst caww
 * to ice_pkg_enum_entwy wequiwes a pointew to an actuaw ice_segment stwuctuwe.
 */
static int ice_find_boost_entwy(stwuct ice_seg *ice_seg, u16 addw,
				stwuct ice_boost_tcam_entwy **entwy)
{
	stwuct ice_boost_tcam_entwy *tcam;
	stwuct ice_pkg_enum state;

	memset(&state, 0, sizeof(state));

	if (!ice_seg)
		wetuwn -EINVAW;

	do {
		tcam = ice_pkg_enum_entwy(ice_seg, &state,
					  ICE_SID_WXPAWSEW_BOOST_TCAM, NUWW,
					  ice_boost_tcam_handwew);
		if (tcam && we16_to_cpu(tcam->addw) == addw) {
			*entwy = tcam;
			wetuwn 0;
		}

		ice_seg = NUWW;
	} whiwe (tcam);

	*entwy = NUWW;
	wetuwn -EIO;
}

/**
 * ice_is_init_pkg_successfuw - check if DDP init was successfuw
 * @state: state of the DDP pkg aftew downwoad
 */
boow ice_is_init_pkg_successfuw(enum ice_ddp_state state)
{
	switch (state) {
	case ICE_DDP_PKG_SUCCESS:
	case ICE_DDP_PKG_SAME_VEWSION_AWWEADY_WOADED:
	case ICE_DDP_PKG_COMPATIBWE_AWWEADY_WOADED:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * ice_pkg_buf_awwoc
 * @hw: pointew to the HW stwuctuwe
 *
 * Awwocates a package buffew and wetuwns a pointew to the buffew headew.
 * Note: aww package contents must be in Wittwe Endian fowm.
 */
stwuct ice_buf_buiwd *ice_pkg_buf_awwoc(stwuct ice_hw *hw)
{
	stwuct ice_buf_buiwd *bwd;
	stwuct ice_buf_hdw *buf;

	bwd = devm_kzawwoc(ice_hw_to_dev(hw), sizeof(*bwd), GFP_KEWNEW);
	if (!bwd)
		wetuwn NUWW;

	buf = (stwuct ice_buf_hdw *)bwd;
	buf->data_end =
		cpu_to_we16(offsetof(stwuct ice_buf_hdw, section_entwy));
	wetuwn bwd;
}

static boow ice_is_gtp_u_pwofiwe(u16 pwof_idx)
{
	wetuwn (pwof_idx >= ICE_PWOFID_IPV6_GTPU_TEID &&
		pwof_idx <= ICE_PWOFID_IPV6_GTPU_IPV6_TCP_INNEW) ||
	       pwof_idx == ICE_PWOFID_IPV4_GTPU_TEID;
}

static boow ice_is_gtp_c_pwofiwe(u16 pwof_idx)
{
	switch (pwof_idx) {
	case ICE_PWOFID_IPV4_GTPC_TEID:
	case ICE_PWOFID_IPV4_GTPC_NO_TEID:
	case ICE_PWOFID_IPV6_GTPC_TEID:
	case ICE_PWOFID_IPV6_GTPC_NO_TEID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * ice_get_sw_pwof_type - detewmine switch pwofiwe type
 * @hw: pointew to the HW stwuctuwe
 * @fv: pointew to the switch fiewd vectow
 * @pwof_idx: pwofiwe index to check
 */
static enum ice_pwof_type ice_get_sw_pwof_type(stwuct ice_hw *hw,
					       stwuct ice_fv *fv, u32 pwof_idx)
{
	u16 i;

	if (ice_is_gtp_c_pwofiwe(pwof_idx))
		wetuwn ICE_PWOF_TUN_GTPC;

	if (ice_is_gtp_u_pwofiwe(pwof_idx))
		wetuwn ICE_PWOF_TUN_GTPU;

	fow (i = 0; i < hw->bwk[ICE_BWK_SW].es.fvw; i++) {
		/* UDP tunnew wiww have UDP_OF pwotocow ID and VNI offset */
		if (fv->ew[i].pwot_id == (u8)ICE_PWOT_UDP_OF &&
		    fv->ew[i].off == ICE_VNI_OFFSET)
			wetuwn ICE_PWOF_TUN_UDP;

		/* GWE tunnew wiww have GWE pwotocow */
		if (fv->ew[i].pwot_id == (u8)ICE_PWOT_GWE_OF)
			wetuwn ICE_PWOF_TUN_GWE;
	}

	wetuwn ICE_PWOF_NON_TUN;
}

/**
 * ice_get_sw_fv_bitmap - Get switch fiewd vectow bitmap based on pwofiwe type
 * @hw: pointew to hawdwawe stwuctuwe
 * @weq_pwofs: type of pwofiwes wequested
 * @bm: pointew to memowy fow wetuwning the bitmap of fiewd vectows
 */
void ice_get_sw_fv_bitmap(stwuct ice_hw *hw, enum ice_pwof_type weq_pwofs,
			  unsigned wong *bm)
{
	stwuct ice_pkg_enum state;
	stwuct ice_seg *ice_seg;
	stwuct ice_fv *fv;

	if (weq_pwofs == ICE_PWOF_AWW) {
		bitmap_set(bm, 0, ICE_MAX_NUM_PWOFIWES);
		wetuwn;
	}

	memset(&state, 0, sizeof(state));
	bitmap_zewo(bm, ICE_MAX_NUM_PWOFIWES);
	ice_seg = hw->seg;
	do {
		enum ice_pwof_type pwof_type;
		u32 offset;

		fv = ice_pkg_enum_entwy(ice_seg, &state, ICE_SID_FWD_VEC_SW,
					&offset, ice_sw_fv_handwew);
		ice_seg = NUWW;

		if (fv) {
			/* Detewmine fiewd vectow type */
			pwof_type = ice_get_sw_pwof_type(hw, fv, offset);

			if (weq_pwofs & pwof_type)
				set_bit((u16)offset, bm);
		}
	} whiwe (fv);
}

/**
 * ice_get_sw_fv_wist
 * @hw: pointew to the HW stwuctuwe
 * @wkups: wist of pwotocow types
 * @bm: bitmap of fiewd vectows to considew
 * @fv_wist: Head of a wist
 *
 * Finds aww the fiewd vectow entwies fwom switch bwock that contain
 * a given pwotocow ID and offset and wetuwns a wist of stwuctuwes of type
 * "ice_sw_fv_wist_entwy". Evewy stwuctuwe in the wist has a fiewd vectow
 * definition and pwofiwe ID infowmation
 * NOTE: The cawwew of the function is wesponsibwe fow fweeing the memowy
 * awwocated fow evewy wist entwy.
 */
int ice_get_sw_fv_wist(stwuct ice_hw *hw, stwuct ice_pwot_wkup_ext *wkups,
		       unsigned wong *bm, stwuct wist_head *fv_wist)
{
	stwuct ice_sw_fv_wist_entwy *fvw;
	stwuct ice_sw_fv_wist_entwy *tmp;
	stwuct ice_pkg_enum state;
	stwuct ice_seg *ice_seg;
	stwuct ice_fv *fv;
	u32 offset;

	memset(&state, 0, sizeof(state));

	if (!wkups->n_vaw_wowds || !hw->seg)
		wetuwn -EINVAW;

	ice_seg = hw->seg;
	do {
		u16 i;

		fv = ice_pkg_enum_entwy(ice_seg, &state, ICE_SID_FWD_VEC_SW,
					&offset, ice_sw_fv_handwew);
		if (!fv)
			bweak;
		ice_seg = NUWW;

		/* If fiewd vectow is not in the bitmap wist, then skip this
		 * pwofiwe.
		 */
		if (!test_bit((u16)offset, bm))
			continue;

		fow (i = 0; i < wkups->n_vaw_wowds; i++) {
			int j;

			fow (j = 0; j < hw->bwk[ICE_BWK_SW].es.fvw; j++)
				if (fv->ew[j].pwot_id ==
					    wkups->fv_wowds[i].pwot_id &&
				    fv->ew[j].off == wkups->fv_wowds[i].off)
					bweak;
			if (j >= hw->bwk[ICE_BWK_SW].es.fvw)
				bweak;
			if (i + 1 == wkups->n_vaw_wowds) {
				fvw = devm_kzawwoc(ice_hw_to_dev(hw),
						   sizeof(*fvw), GFP_KEWNEW);
				if (!fvw)
					goto eww;
				fvw->fv_ptw = fv;
				fvw->pwofiwe_id = offset;
				wist_add(&fvw->wist_entwy, fv_wist);
				bweak;
			}
		}
	} whiwe (fv);
	if (wist_empty(fv_wist)) {
		dev_wawn(ice_hw_to_dev(hw),
			 "Wequiwed pwofiwes not found in cuwwentwy woaded DDP package");
		wetuwn -EIO;
	}

	wetuwn 0;

eww:
	wist_fow_each_entwy_safe(fvw, tmp, fv_wist, wist_entwy) {
		wist_dew(&fvw->wist_entwy);
		devm_kfwee(ice_hw_to_dev(hw), fvw);
	}

	wetuwn -ENOMEM;
}

/**
 * ice_init_pwof_wesuwt_bm - Initiawize the pwofiwe wesuwt index bitmap
 * @hw: pointew to hawdwawe stwuctuwe
 */
void ice_init_pwof_wesuwt_bm(stwuct ice_hw *hw)
{
	stwuct ice_pkg_enum state;
	stwuct ice_seg *ice_seg;
	stwuct ice_fv *fv;

	memset(&state, 0, sizeof(state));

	if (!hw->seg)
		wetuwn;

	ice_seg = hw->seg;
	do {
		u32 off;
		u16 i;

		fv = ice_pkg_enum_entwy(ice_seg, &state, ICE_SID_FWD_VEC_SW,
					&off, ice_sw_fv_handwew);
		ice_seg = NUWW;
		if (!fv)
			bweak;

		bitmap_zewo(hw->switch_info->pwof_wes_bm[off],
			    ICE_MAX_FV_WOWDS);

		/* Detewmine empty fiewd vectow indices, these can be
		 * used fow wecipe wesuwts. Skip index 0, since it is
		 * awways used fow Switch ID.
		 */
		fow (i = 1; i < ICE_MAX_FV_WOWDS; i++)
			if (fv->ew[i].pwot_id == ICE_PWOT_INVAWID &&
			    fv->ew[i].off == ICE_FV_OFFSET_INVAW)
				set_bit(i, hw->switch_info->pwof_wes_bm[off]);
	} whiwe (fv);
}

/**
 * ice_pkg_buf_fwee
 * @hw: pointew to the HW stwuctuwe
 * @bwd: pointew to pkg buiwd (awwocated by ice_pkg_buf_awwoc())
 *
 * Fwees a package buffew
 */
void ice_pkg_buf_fwee(stwuct ice_hw *hw, stwuct ice_buf_buiwd *bwd)
{
	devm_kfwee(ice_hw_to_dev(hw), bwd);
}

/**
 * ice_pkg_buf_wesewve_section
 * @bwd: pointew to pkg buiwd (awwocated by ice_pkg_buf_awwoc())
 * @count: the numbew of sections to wesewve
 *
 * Wesewves one ow mowe section tabwe entwies in a package buffew. This woutine
 * can be cawwed muwtipwe times as wong as they awe made befowe cawwing
 * ice_pkg_buf_awwoc_section(). Once ice_pkg_buf_awwoc_section()
 * is cawwed once, the numbew of sections that can be awwocated wiww not be abwe
 * to be incweased; not using aww wesewved sections is fine, but this wiww
 * wesuwt in some wasted space in the buffew.
 * Note: aww package contents must be in Wittwe Endian fowm.
 */
int ice_pkg_buf_wesewve_section(stwuct ice_buf_buiwd *bwd, u16 count)
{
	stwuct ice_buf_hdw *buf;
	u16 section_count;
	u16 data_end;

	if (!bwd)
		wetuwn -EINVAW;

	buf = (stwuct ice_buf_hdw *)&bwd->buf;

	/* awweady an active section, can't incwease tabwe size */
	section_count = we16_to_cpu(buf->section_count);
	if (section_count > 0)
		wetuwn -EIO;

	if (bwd->wesewved_section_tabwe_entwies + count > ICE_MAX_S_COUNT)
		wetuwn -EIO;
	bwd->wesewved_section_tabwe_entwies += count;

	data_end = we16_to_cpu(buf->data_end) +
		   fwex_awway_size(buf, section_entwy, count);
	buf->data_end = cpu_to_we16(data_end);

	wetuwn 0;
}

/**
 * ice_pkg_buf_awwoc_section
 * @bwd: pointew to pkg buiwd (awwocated by ice_pkg_buf_awwoc())
 * @type: the section type vawue
 * @size: the size of the section to wesewve (in bytes)
 *
 * Wesewves memowy in the buffew fow a section's content and updates the
 * buffews' status accowdingwy. This woutine wetuwns a pointew to the fiwst
 * byte of the section stawt within the buffew, which is used to fiww in the
 * section contents.
 * Note: aww package contents must be in Wittwe Endian fowm.
 */
void *ice_pkg_buf_awwoc_section(stwuct ice_buf_buiwd *bwd, u32 type, u16 size)
{
	stwuct ice_buf_hdw *buf;
	u16 sect_count;
	u16 data_end;

	if (!bwd || !type || !size)
		wetuwn NUWW;

	buf = (stwuct ice_buf_hdw *)&bwd->buf;

	/* check fow enough space weft in buffew */
	data_end = we16_to_cpu(buf->data_end);

	/* section stawt must awign on 4 byte boundawy */
	data_end = AWIGN(data_end, 4);

	if ((data_end + size) > ICE_MAX_S_DATA_END)
		wetuwn NUWW;

	/* check fow mowe avaiwabwe section tabwe entwies */
	sect_count = we16_to_cpu(buf->section_count);
	if (sect_count < bwd->wesewved_section_tabwe_entwies) {
		void *section_ptw = ((u8 *)buf) + data_end;

		buf->section_entwy[sect_count].offset = cpu_to_we16(data_end);
		buf->section_entwy[sect_count].size = cpu_to_we16(size);
		buf->section_entwy[sect_count].type = cpu_to_we32(type);

		data_end += size;
		buf->data_end = cpu_to_we16(data_end);

		buf->section_count = cpu_to_we16(sect_count + 1);
		wetuwn section_ptw;
	}

	/* no fwee section tabwe entwies */
	wetuwn NUWW;
}

/**
 * ice_pkg_buf_awwoc_singwe_section
 * @hw: pointew to the HW stwuctuwe
 * @type: the section type vawue
 * @size: the size of the section to wesewve (in bytes)
 * @section: wetuwns pointew to the section
 *
 * Awwocates a package buffew with a singwe section.
 * Note: aww package contents must be in Wittwe Endian fowm.
 */
stwuct ice_buf_buiwd *ice_pkg_buf_awwoc_singwe_section(stwuct ice_hw *hw,
						       u32 type, u16 size,
						       void **section)
{
	stwuct ice_buf_buiwd *buf;

	if (!section)
		wetuwn NUWW;

	buf = ice_pkg_buf_awwoc(hw);
	if (!buf)
		wetuwn NUWW;

	if (ice_pkg_buf_wesewve_section(buf, 1))
		goto ice_pkg_buf_awwoc_singwe_section_eww;

	*section = ice_pkg_buf_awwoc_section(buf, type, size);
	if (!*section)
		goto ice_pkg_buf_awwoc_singwe_section_eww;

	wetuwn buf;

ice_pkg_buf_awwoc_singwe_section_eww:
	ice_pkg_buf_fwee(hw, buf);
	wetuwn NUWW;
}

/**
 * ice_pkg_buf_get_active_sections
 * @bwd: pointew to pkg buiwd (awwocated by ice_pkg_buf_awwoc())
 *
 * Wetuwns the numbew of active sections. Befowe using the package buffew
 * in an update package command, the cawwew shouwd make suwe that thewe is at
 * weast one active section - othewwise, the buffew is not wegaw and shouwd
 * not be used.
 * Note: aww package contents must be in Wittwe Endian fowm.
 */
u16 ice_pkg_buf_get_active_sections(stwuct ice_buf_buiwd *bwd)
{
	stwuct ice_buf_hdw *buf;

	if (!bwd)
		wetuwn 0;

	buf = (stwuct ice_buf_hdw *)&bwd->buf;
	wetuwn we16_to_cpu(buf->section_count);
}

/**
 * ice_pkg_buf
 * @bwd: pointew to pkg buiwd (awwocated by ice_pkg_buf_awwoc())
 *
 * Wetuwn a pointew to the buffew's headew
 */
stwuct ice_buf *ice_pkg_buf(stwuct ice_buf_buiwd *bwd)
{
	if (!bwd)
		wetuwn NUWW;

	wetuwn &bwd->buf;
}

static enum ice_ddp_state ice_map_aq_eww_to_ddp_state(enum ice_aq_eww aq_eww)
{
	switch (aq_eww) {
	case ICE_AQ_WC_ENOSEC:
	case ICE_AQ_WC_EBADSIG:
		wetuwn ICE_DDP_PKG_FIWE_SIGNATUWE_INVAWID;
	case ICE_AQ_WC_ESVN:
		wetuwn ICE_DDP_PKG_FIWE_WEVISION_TOO_WOW;
	case ICE_AQ_WC_EBADMAN:
	case ICE_AQ_WC_EBADBUF:
		wetuwn ICE_DDP_PKG_WOAD_EWWOW;
	defauwt:
		wetuwn ICE_DDP_PKG_EWW;
	}
}

/**
 * ice_acquiwe_gwobaw_cfg_wock
 * @hw: pointew to the HW stwuctuwe
 * @access: access type (wead ow wwite)
 *
 * This function wiww wequest ownewship of the gwobaw config wock fow weading
 * ow wwiting of the package. When attempting to obtain wwite access, the
 * cawwew must check fow the fowwowing two wetuwn vawues:
 *
 * 0         -  Means the cawwew has acquiwed the gwobaw config wock
 *              and can pewfowm wwiting of the package.
 * -EAWWEADY - Indicates anothew dwivew has awweady wwitten the
 *             package ow has found that no update was necessawy; in
 *             this case, the cawwew can just skip pewfowming any
 *             update of the package.
 */
static int ice_acquiwe_gwobaw_cfg_wock(stwuct ice_hw *hw,
				       enum ice_aq_wes_access_type access)
{
	int status;

	status = ice_acquiwe_wes(hw, ICE_GWOBAW_CFG_WOCK_WES_ID, access,
				 ICE_GWOBAW_CFG_WOCK_TIMEOUT);

	if (!status)
		mutex_wock(&ice_gwobaw_cfg_wock_sw);
	ewse if (status == -EAWWEADY)
		ice_debug(hw, ICE_DBG_PKG,
			  "Gwobaw config wock: No wowk to do\n");

	wetuwn status;
}

/**
 * ice_wewease_gwobaw_cfg_wock
 * @hw: pointew to the HW stwuctuwe
 *
 * This function wiww wewease the gwobaw config wock.
 */
static void ice_wewease_gwobaw_cfg_wock(stwuct ice_hw *hw)
{
	mutex_unwock(&ice_gwobaw_cfg_wock_sw);
	ice_wewease_wes(hw, ICE_GWOBAW_CFG_WOCK_WES_ID);
}

/**
 * ice_aq_downwoad_pkg
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pkg_buf: the package buffew to twansfew
 * @buf_size: the size of the package buffew
 * @wast_buf: wast buffew indicatow
 * @ewwow_offset: wetuwns ewwow offset
 * @ewwow_info: wetuwns ewwow infowmation
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Downwoad Package (0x0C40)
 */
static int
ice_aq_downwoad_pkg(stwuct ice_hw *hw, stwuct ice_buf_hdw *pkg_buf,
		    u16 buf_size, boow wast_buf, u32 *ewwow_offset,
		    u32 *ewwow_info, stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_downwoad_pkg *cmd;
	stwuct ice_aq_desc desc;
	int status;

	if (ewwow_offset)
		*ewwow_offset = 0;
	if (ewwow_info)
		*ewwow_info = 0;

	cmd = &desc.pawams.downwoad_pkg;
	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_downwoad_pkg);
	desc.fwags |= cpu_to_we16(ICE_AQ_FWAG_WD);

	if (wast_buf)
		cmd->fwags |= ICE_AQC_DOWNWOAD_PKG_WAST_BUF;

	status = ice_aq_send_cmd(hw, &desc, pkg_buf, buf_size, cd);
	if (status == -EIO) {
		/* Wead ewwow fwom buffew onwy when the FW wetuwned an ewwow */
		stwuct ice_aqc_downwoad_pkg_wesp *wesp;

		wesp = (stwuct ice_aqc_downwoad_pkg_wesp *)pkg_buf;
		if (ewwow_offset)
			*ewwow_offset = we32_to_cpu(wesp->ewwow_offset);
		if (ewwow_info)
			*ewwow_info = we32_to_cpu(wesp->ewwow_info);
	}

	wetuwn status;
}

/**
 * ice_get_pkg_seg_by_idx
 * @pkg_hdw: pointew to the package headew to be seawched
 * @idx: index of segment
 */
static stwuct ice_genewic_seg_hdw *
ice_get_pkg_seg_by_idx(stwuct ice_pkg_hdw *pkg_hdw, u32 idx)
{
	if (idx < we32_to_cpu(pkg_hdw->seg_count))
		wetuwn (stwuct ice_genewic_seg_hdw *)
			((u8 *)pkg_hdw +
			 we32_to_cpu(pkg_hdw->seg_offset[idx]));

	wetuwn NUWW;
}

/**
 * ice_is_signing_seg_at_idx - detewmine if segment is a signing segment
 * @pkg_hdw: pointew to package headew
 * @idx: segment index
 */
static boow ice_is_signing_seg_at_idx(stwuct ice_pkg_hdw *pkg_hdw, u32 idx)
{
	stwuct ice_genewic_seg_hdw *seg;

	seg = ice_get_pkg_seg_by_idx(pkg_hdw, idx);
	if (!seg)
		wetuwn fawse;

	wetuwn we32_to_cpu(seg->seg_type) == SEGMENT_TYPE_SIGNING;
}

/**
 * ice_is_signing_seg_type_at_idx
 * @pkg_hdw: pointew to package headew
 * @idx: segment index
 * @seg_id: segment id that is expected
 * @sign_type: signing type
 *
 * Detewmine if a segment is a signing segment of the cowwect type
 */
static boow
ice_is_signing_seg_type_at_idx(stwuct ice_pkg_hdw *pkg_hdw, u32 idx,
			       u32 seg_id, u32 sign_type)
{
	stwuct ice_sign_seg *seg;

	if (!ice_is_signing_seg_at_idx(pkg_hdw, idx))
		wetuwn fawse;

	seg = (stwuct ice_sign_seg *)ice_get_pkg_seg_by_idx(pkg_hdw, idx);

	if (seg && we32_to_cpu(seg->seg_id) == seg_id &&
	    we32_to_cpu(seg->sign_type) == sign_type)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * ice_is_buffew_metadata - detewmine if package buffew is a metadata buffew
 * @buf: pointew to buffew headew
 */
static boow ice_is_buffew_metadata(stwuct ice_buf_hdw *buf)
{
	if (we32_to_cpu(buf->section_entwy[0].type) & ICE_METADATA_BUF)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * ice_is_wast_downwoad_buffew
 * @buf: pointew to cuwwent buffew headew
 * @idx: index of the buffew in the cuwwent sequence
 * @count: the buffew count in the cuwwent sequence
 *
 * Note: this woutine shouwd onwy be cawwed if the buffew is not the wast buffew
 */
static boow
ice_is_wast_downwoad_buffew(stwuct ice_buf_hdw *buf, u32 idx, u32 count)
{
	stwuct ice_buf *next_buf;

	if ((idx + 1) == count)
		wetuwn twue;

	/* A set metadata fwag in the next buffew wiww signaw that the cuwwent
	 * buffew wiww be the wast buffew downwoaded
	 */
	next_buf = ((stwuct ice_buf *)buf) + 1;

	wetuwn ice_is_buffew_metadata((stwuct ice_buf_hdw *)next_buf);
}

/**
 * ice_dwnwd_cfg_bufs_no_wock
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bufs: pointew to an awway of buffews
 * @stawt: buffew index of fiwst buffew to downwoad
 * @count: the numbew of buffews to downwoad
 * @indicate_wast: if twue, then set wast buffew fwag on wast buffew downwoad
 *
 * Downwoads package configuwation buffews to the fiwmwawe. Metadata buffews
 * awe skipped, and the fiwst metadata buffew found indicates that the west
 * of the buffews awe aww metadata buffews.
 */
static enum ice_ddp_state
ice_dwnwd_cfg_bufs_no_wock(stwuct ice_hw *hw, stwuct ice_buf *bufs, u32 stawt,
			   u32 count, boow indicate_wast)
{
	enum ice_ddp_state state = ICE_DDP_PKG_SUCCESS;
	stwuct ice_buf_hdw *bh;
	enum ice_aq_eww eww;
	u32 offset, info, i;

	if (!bufs || !count)
		wetuwn ICE_DDP_PKG_EWW;

	/* If the fiwst buffew's fiwst section has its metadata bit set
	 * then thewe awe no buffews to be downwoaded, and the opewation is
	 * considewed a success.
	 */
	bh = (stwuct ice_buf_hdw *)(bufs + stawt);
	if (we32_to_cpu(bh->section_entwy[0].type) & ICE_METADATA_BUF)
		wetuwn ICE_DDP_PKG_SUCCESS;

	fow (i = 0; i < count; i++) {
		boow wast = fawse;
		int status;

		bh = (stwuct ice_buf_hdw *)(bufs + stawt + i);

		if (indicate_wast)
			wast = ice_is_wast_downwoad_buffew(bh, i, count);

		status = ice_aq_downwoad_pkg(hw, bh, ICE_PKG_BUF_SIZE, wast,
					     &offset, &info, NUWW);

		/* Save AQ status fwom downwoad package */
		if (status) {
			ice_debug(hw, ICE_DBG_PKG, "Pkg downwoad faiwed: eww %d off %d inf %d\n",
				  status, offset, info);
			eww = hw->adminq.sq_wast_status;
			state = ice_map_aq_eww_to_ddp_state(eww);
			bweak;
		}

		if (wast)
			bweak;
	}

	wetuwn state;
}

/**
 * ice_downwoad_pkg_sig_seg - downwoad a signatuwe segment
 * @hw: pointew to the hawdwawe stwuctuwe
 * @seg: pointew to signatuwe segment
 */
static enum ice_ddp_state
ice_downwoad_pkg_sig_seg(stwuct ice_hw *hw, stwuct ice_sign_seg *seg)
{
	wetuwn  ice_dwnwd_cfg_bufs_no_wock(hw, seg->buf_tbw.buf_awway, 0,
					   we32_to_cpu(seg->buf_tbw.buf_count),
					   fawse);
}

/**
 * ice_downwoad_pkg_config_seg - downwoad a config segment
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pkg_hdw: pointew to package headew
 * @idx: segment index
 * @stawt: stawting buffew
 * @count: buffew count
 *
 * Note: idx must wefewence a ICE segment
 */
static enum ice_ddp_state
ice_downwoad_pkg_config_seg(stwuct ice_hw *hw, stwuct ice_pkg_hdw *pkg_hdw,
			    u32 idx, u32 stawt, u32 count)
{
	stwuct ice_buf_tabwe *bufs;
	stwuct ice_seg *seg;
	u32 buf_count;

	seg = (stwuct ice_seg *)ice_get_pkg_seg_by_idx(pkg_hdw, idx);
	if (!seg)
		wetuwn ICE_DDP_PKG_EWW;

	bufs = ice_find_buf_tabwe(seg);
	buf_count = we32_to_cpu(bufs->buf_count);

	if (stawt >= buf_count || stawt + count > buf_count)
		wetuwn ICE_DDP_PKG_EWW;

	wetuwn  ice_dwnwd_cfg_bufs_no_wock(hw, bufs->buf_awway, stawt, count,
					   twue);
}

/**
 * ice_dwnwd_sign_and_cfg_segs - downwoad a signing segment and config segment
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pkg_hdw: pointew to package headew
 * @idx: segment index (must be a signatuwe segment)
 *
 * Note: idx must wefewence a signatuwe segment
 */
static enum ice_ddp_state
ice_dwnwd_sign_and_cfg_segs(stwuct ice_hw *hw, stwuct ice_pkg_hdw *pkg_hdw,
			    u32 idx)
{
	enum ice_ddp_state state;
	stwuct ice_sign_seg *seg;
	u32 conf_idx;
	u32 stawt;
	u32 count;

	seg = (stwuct ice_sign_seg *)ice_get_pkg_seg_by_idx(pkg_hdw, idx);
	if (!seg) {
		state = ICE_DDP_PKG_EWW;
		goto exit;
	}

	conf_idx = we32_to_cpu(seg->signed_seg_idx);
	stawt = we32_to_cpu(seg->signed_buf_stawt);
	count = we32_to_cpu(seg->signed_buf_count);

	state = ice_downwoad_pkg_sig_seg(hw, seg);
	if (state)
		goto exit;

	state = ice_downwoad_pkg_config_seg(hw, pkg_hdw, conf_idx, stawt,
					    count);

exit:
	wetuwn state;
}

/**
 * ice_match_signing_seg - detewmine if a matching signing segment exists
 * @pkg_hdw: pointew to package headew
 * @seg_id: segment id that is expected
 * @sign_type: signing type
 */
static boow
ice_match_signing_seg(stwuct ice_pkg_hdw *pkg_hdw, u32 seg_id, u32 sign_type)
{
	u32 i;

	fow (i = 0; i < we32_to_cpu(pkg_hdw->seg_count); i++) {
		if (ice_is_signing_seg_type_at_idx(pkg_hdw, i, seg_id,
						   sign_type))
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * ice_post_dwnwd_pkg_actions - pewfowm post downwoad package actions
 * @hw: pointew to the hawdwawe stwuctuwe
 */
static enum ice_ddp_state
ice_post_dwnwd_pkg_actions(stwuct ice_hw *hw)
{
	int status;

	status = ice_set_vwan_mode(hw);
	if (status) {
		ice_debug(hw, ICE_DBG_PKG, "Faiwed to set VWAN mode: eww %d\n",
			  status);
		wetuwn ICE_DDP_PKG_EWW;
	}

	wetuwn ICE_DDP_PKG_SUCCESS;
}

/**
 * ice_downwoad_pkg_with_sig_seg
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pkg_hdw: pointew to package headew
 *
 * Handwes the downwoad of a compwete package.
 */
static enum ice_ddp_state
ice_downwoad_pkg_with_sig_seg(stwuct ice_hw *hw, stwuct ice_pkg_hdw *pkg_hdw)
{
	enum ice_aq_eww aq_eww = hw->adminq.sq_wast_status;
	enum ice_ddp_state state = ICE_DDP_PKG_EWW;
	int status;
	u32 i;

	ice_debug(hw, ICE_DBG_INIT, "Segment ID %d\n", hw->pkg_seg_id);
	ice_debug(hw, ICE_DBG_INIT, "Signatuwe type %d\n", hw->pkg_sign_type);

	status = ice_acquiwe_gwobaw_cfg_wock(hw, ICE_WES_WWITE);
	if (status) {
		if (status == -EAWWEADY)
			state = ICE_DDP_PKG_AWWEADY_WOADED;
		ewse
			state = ice_map_aq_eww_to_ddp_state(aq_eww);
		wetuwn state;
	}

	fow (i = 0; i < we32_to_cpu(pkg_hdw->seg_count); i++) {
		if (!ice_is_signing_seg_type_at_idx(pkg_hdw, i, hw->pkg_seg_id,
						    hw->pkg_sign_type))
			continue;

		state = ice_dwnwd_sign_and_cfg_segs(hw, pkg_hdw, i);
		if (state)
			bweak;
	}

	if (!state)
		state = ice_post_dwnwd_pkg_actions(hw);

	ice_wewease_gwobaw_cfg_wock(hw);

	wetuwn state;
}

/**
 * ice_dwnwd_cfg_bufs
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bufs: pointew to an awway of buffews
 * @count: the numbew of buffews in the awway
 *
 * Obtains gwobaw config wock and downwoads the package configuwation buffews
 * to the fiwmwawe.
 */
static enum ice_ddp_state
ice_dwnwd_cfg_bufs(stwuct ice_hw *hw, stwuct ice_buf *bufs, u32 count)
{
	enum ice_ddp_state state;
	stwuct ice_buf_hdw *bh;
	int status;

	if (!bufs || !count)
		wetuwn ICE_DDP_PKG_EWW;

	/* If the fiwst buffew's fiwst section has its metadata bit set
	 * then thewe awe no buffews to be downwoaded, and the opewation is
	 * considewed a success.
	 */
	bh = (stwuct ice_buf_hdw *)bufs;
	if (we32_to_cpu(bh->section_entwy[0].type) & ICE_METADATA_BUF)
		wetuwn ICE_DDP_PKG_SUCCESS;

	status = ice_acquiwe_gwobaw_cfg_wock(hw, ICE_WES_WWITE);
	if (status) {
		if (status == -EAWWEADY)
			wetuwn ICE_DDP_PKG_AWWEADY_WOADED;
		wetuwn ice_map_aq_eww_to_ddp_state(hw->adminq.sq_wast_status);
	}

	state = ice_dwnwd_cfg_bufs_no_wock(hw, bufs, 0, count, twue);
	if (!state)
		state = ice_post_dwnwd_pkg_actions(hw);

	ice_wewease_gwobaw_cfg_wock(hw);

	wetuwn state;
}

/**
 * ice_downwoad_pkg_without_sig_seg
 * @hw: pointew to the hawdwawe stwuctuwe
 * @ice_seg: pointew to the segment of the package to be downwoaded
 *
 * Handwes the downwoad of a compwete package without signatuwe segment.
 */
static enum ice_ddp_state
ice_downwoad_pkg_without_sig_seg(stwuct ice_hw *hw, stwuct ice_seg *ice_seg)
{
	stwuct ice_buf_tabwe *ice_buf_tbw;

	ice_debug(hw, ICE_DBG_PKG, "Segment fowmat vewsion: %d.%d.%d.%d\n",
		  ice_seg->hdw.seg_fowmat_vew.majow,
		  ice_seg->hdw.seg_fowmat_vew.minow,
		  ice_seg->hdw.seg_fowmat_vew.update,
		  ice_seg->hdw.seg_fowmat_vew.dwaft);

	ice_debug(hw, ICE_DBG_PKG, "Seg: type 0x%X, size %d, name %s\n",
		  we32_to_cpu(ice_seg->hdw.seg_type),
		  we32_to_cpu(ice_seg->hdw.seg_size), ice_seg->hdw.seg_id);

	ice_buf_tbw = ice_find_buf_tabwe(ice_seg);

	ice_debug(hw, ICE_DBG_PKG, "Seg buf count: %d\n",
		  we32_to_cpu(ice_buf_tbw->buf_count));

	wetuwn ice_dwnwd_cfg_bufs(hw, ice_buf_tbw->buf_awway,
				  we32_to_cpu(ice_buf_tbw->buf_count));
}

/**
 * ice_downwoad_pkg
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pkg_hdw: pointew to package headew
 * @ice_seg: pointew to the segment of the package to be downwoaded
 *
 * Handwes the downwoad of a compwete package.
 */
static enum ice_ddp_state
ice_downwoad_pkg(stwuct ice_hw *hw, stwuct ice_pkg_hdw *pkg_hdw,
		 stwuct ice_seg *ice_seg)
{
	enum ice_ddp_state state;

	if (hw->pkg_has_signing_seg)
		state = ice_downwoad_pkg_with_sig_seg(hw, pkg_hdw);
	ewse
		state = ice_downwoad_pkg_without_sig_seg(hw, ice_seg);

	ice_post_pkg_dwnwd_vwan_mode_cfg(hw);

	wetuwn state;
}

/**
 * ice_aq_get_pkg_info_wist
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pkg_info: the buffew which wiww weceive the infowmation wist
 * @buf_size: the size of the pkg_info infowmation buffew
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Get Package Info Wist (0x0C43)
 */
static int ice_aq_get_pkg_info_wist(stwuct ice_hw *hw,
				    stwuct ice_aqc_get_pkg_info_wesp *pkg_info,
				    u16 buf_size, stwuct ice_sq_cd *cd)
{
	stwuct ice_aq_desc desc;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_get_pkg_info_wist);

	wetuwn ice_aq_send_cmd(hw, &desc, pkg_info, buf_size, cd);
}

/**
 * ice_aq_update_pkg
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pkg_buf: the package cmd buffew
 * @buf_size: the size of the package cmd buffew
 * @wast_buf: wast buffew indicatow
 * @ewwow_offset: wetuwns ewwow offset
 * @ewwow_info: wetuwns ewwow infowmation
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Update Package (0x0C42)
 */
static int ice_aq_update_pkg(stwuct ice_hw *hw, stwuct ice_buf_hdw *pkg_buf,
			     u16 buf_size, boow wast_buf, u32 *ewwow_offset,
			     u32 *ewwow_info, stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_downwoad_pkg *cmd;
	stwuct ice_aq_desc desc;
	int status;

	if (ewwow_offset)
		*ewwow_offset = 0;
	if (ewwow_info)
		*ewwow_info = 0;

	cmd = &desc.pawams.downwoad_pkg;
	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_update_pkg);
	desc.fwags |= cpu_to_we16(ICE_AQ_FWAG_WD);

	if (wast_buf)
		cmd->fwags |= ICE_AQC_DOWNWOAD_PKG_WAST_BUF;

	status = ice_aq_send_cmd(hw, &desc, pkg_buf, buf_size, cd);
	if (status == -EIO) {
		/* Wead ewwow fwom buffew onwy when the FW wetuwned an ewwow */
		stwuct ice_aqc_downwoad_pkg_wesp *wesp;

		wesp = (stwuct ice_aqc_downwoad_pkg_wesp *)pkg_buf;
		if (ewwow_offset)
			*ewwow_offset = we32_to_cpu(wesp->ewwow_offset);
		if (ewwow_info)
			*ewwow_info = we32_to_cpu(wesp->ewwow_info);
	}

	wetuwn status;
}

/**
 * ice_aq_upwoad_section
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pkg_buf: the package buffew which wiww weceive the section
 * @buf_size: the size of the package buffew
 * @cd: pointew to command detaiws stwuctuwe ow NUWW
 *
 * Upwoad Section (0x0C41)
 */
int ice_aq_upwoad_section(stwuct ice_hw *hw, stwuct ice_buf_hdw *pkg_buf,
			  u16 buf_size, stwuct ice_sq_cd *cd)
{
	stwuct ice_aq_desc desc;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_upwoad_section);
	desc.fwags |= cpu_to_we16(ICE_AQ_FWAG_WD);

	wetuwn ice_aq_send_cmd(hw, &desc, pkg_buf, buf_size, cd);
}

/**
 * ice_update_pkg_no_wock
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bufs: pointew to an awway of buffews
 * @count: the numbew of buffews in the awway
 */
int ice_update_pkg_no_wock(stwuct ice_hw *hw, stwuct ice_buf *bufs, u32 count)
{
	int status = 0;
	u32 i;

	fow (i = 0; i < count; i++) {
		stwuct ice_buf_hdw *bh = (stwuct ice_buf_hdw *)(bufs + i);
		boow wast = ((i + 1) == count);
		u32 offset, info;

		status = ice_aq_update_pkg(hw, bh, we16_to_cpu(bh->data_end),
					   wast, &offset, &info, NUWW);

		if (status) {
			ice_debug(hw, ICE_DBG_PKG,
				  "Update pkg faiwed: eww %d off %d inf %d\n",
				  status, offset, info);
			bweak;
		}
	}

	wetuwn status;
}

/**
 * ice_update_pkg
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bufs: pointew to an awway of buffews
 * @count: the numbew of buffews in the awway
 *
 * Obtains change wock and updates package.
 */
int ice_update_pkg(stwuct ice_hw *hw, stwuct ice_buf *bufs, u32 count)
{
	int status;

	status = ice_acquiwe_change_wock(hw, ICE_WES_WWITE);
	if (status)
		wetuwn status;

	status = ice_update_pkg_no_wock(hw, bufs, count);

	ice_wewease_change_wock(hw);

	wetuwn status;
}

/**
 * ice_find_seg_in_pkg
 * @hw: pointew to the hawdwawe stwuctuwe
 * @seg_type: the segment type to seawch fow (i.e., SEGMENT_TYPE_CPK)
 * @pkg_hdw: pointew to the package headew to be seawched
 *
 * This function seawches a package fiwe fow a pawticuwaw segment type. On
 * success it wetuwns a pointew to the segment headew, othewwise it wiww
 * wetuwn NUWW.
 */
static stwuct ice_genewic_seg_hdw *
ice_find_seg_in_pkg(stwuct ice_hw *hw, u32 seg_type,
		    stwuct ice_pkg_hdw *pkg_hdw)
{
	u32 i;

	ice_debug(hw, ICE_DBG_PKG, "Package fowmat vewsion: %d.%d.%d.%d\n",
		  pkg_hdw->pkg_fowmat_vew.majow, pkg_hdw->pkg_fowmat_vew.minow,
		  pkg_hdw->pkg_fowmat_vew.update,
		  pkg_hdw->pkg_fowmat_vew.dwaft);

	/* Seawch aww package segments fow the wequested segment type */
	fow (i = 0; i < we32_to_cpu(pkg_hdw->seg_count); i++) {
		stwuct ice_genewic_seg_hdw *seg;

		seg = (stwuct ice_genewic_seg_hdw
			       *)((u8 *)pkg_hdw +
				  we32_to_cpu(pkg_hdw->seg_offset[i]));

		if (we32_to_cpu(seg->seg_type) == seg_type)
			wetuwn seg;
	}

	wetuwn NUWW;
}

/**
 * ice_has_signing_seg - detewmine if package has a signing segment
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pkg_hdw: pointew to the dwivew's package hdw
 */
static boow ice_has_signing_seg(stwuct ice_hw *hw, stwuct ice_pkg_hdw *pkg_hdw)
{
	stwuct ice_genewic_seg_hdw *seg_hdw;

	seg_hdw = (stwuct ice_genewic_seg_hdw *)
		ice_find_seg_in_pkg(hw, SEGMENT_TYPE_SIGNING, pkg_hdw);

	wetuwn seg_hdw ? twue : fawse;
}

/**
 * ice_get_pkg_segment_id - get cowwect package segment id, based on device
 * @mac_type: MAC type of the device
 */
static u32 ice_get_pkg_segment_id(enum ice_mac_type mac_type)
{
	u32 seg_id;

	switch (mac_type) {
	case ICE_MAC_E830:
		seg_id = SEGMENT_TYPE_ICE_E830;
		bweak;
	case ICE_MAC_GENEWIC:
	defauwt:
		seg_id = SEGMENT_TYPE_ICE_E810;
		bweak;
	}

	wetuwn seg_id;
}

/**
 * ice_get_pkg_sign_type - get package segment sign type, based on device
 * @mac_type: MAC type of the device
 */
static u32 ice_get_pkg_sign_type(enum ice_mac_type mac_type)
{
	u32 sign_type;

	switch (mac_type) {
	case ICE_MAC_E830:
		sign_type = SEGMENT_SIGN_TYPE_WSA3K_SBB;
		bweak;
	case ICE_MAC_GENEWIC:
	defauwt:
		sign_type = SEGMENT_SIGN_TYPE_WSA2K;
		bweak;
	}

	wetuwn sign_type;
}

/**
 * ice_get_signing_weq - get cowwect package wequiwements, based on device
 * @hw: pointew to the hawdwawe stwuctuwe
 */
static void ice_get_signing_weq(stwuct ice_hw *hw)
{
	hw->pkg_seg_id = ice_get_pkg_segment_id(hw->mac_type);
	hw->pkg_sign_type = ice_get_pkg_sign_type(hw->mac_type);
}

/**
 * ice_init_pkg_info
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pkg_hdw: pointew to the dwivew's package hdw
 *
 * Saves off the package detaiws into the HW stwuctuwe.
 */
static enum ice_ddp_state ice_init_pkg_info(stwuct ice_hw *hw,
					    stwuct ice_pkg_hdw *pkg_hdw)
{
	stwuct ice_genewic_seg_hdw *seg_hdw;

	if (!pkg_hdw)
		wetuwn ICE_DDP_PKG_EWW;

	hw->pkg_has_signing_seg = ice_has_signing_seg(hw, pkg_hdw);
	ice_get_signing_weq(hw);

	ice_debug(hw, ICE_DBG_INIT, "Pkg using segment id: 0x%08X\n",
		  hw->pkg_seg_id);

	seg_hdw = (stwuct ice_genewic_seg_hdw *)
		ice_find_seg_in_pkg(hw, hw->pkg_seg_id, pkg_hdw);
	if (seg_hdw) {
		stwuct ice_meta_sect *meta;
		stwuct ice_pkg_enum state;

		memset(&state, 0, sizeof(state));

		/* Get package infowmation fwom the Metadata Section */
		meta = ice_pkg_enum_section((stwuct ice_seg *)seg_hdw, &state,
					    ICE_SID_METADATA);
		if (!meta) {
			ice_debug(hw, ICE_DBG_INIT,
				  "Did not find ice metadata section in package\n");
			wetuwn ICE_DDP_PKG_INVAWID_FIWE;
		}

		hw->pkg_vew = meta->vew;
		memcpy(hw->pkg_name, meta->name, sizeof(meta->name));

		ice_debug(hw, ICE_DBG_PKG, "Pkg: %d.%d.%d.%d, %s\n",
			  meta->vew.majow, meta->vew.minow, meta->vew.update,
			  meta->vew.dwaft, meta->name);

		hw->ice_seg_fmt_vew = seg_hdw->seg_fowmat_vew;
		memcpy(hw->ice_seg_id, seg_hdw->seg_id, sizeof(hw->ice_seg_id));

		ice_debug(hw, ICE_DBG_PKG, "Ice Seg: %d.%d.%d.%d, %s\n",
			  seg_hdw->seg_fowmat_vew.majow,
			  seg_hdw->seg_fowmat_vew.minow,
			  seg_hdw->seg_fowmat_vew.update,
			  seg_hdw->seg_fowmat_vew.dwaft, seg_hdw->seg_id);
	} ewse {
		ice_debug(hw, ICE_DBG_INIT,
			  "Did not find ice segment in dwivew package\n");
		wetuwn ICE_DDP_PKG_INVAWID_FIWE;
	}

	wetuwn ICE_DDP_PKG_SUCCESS;
}

/**
 * ice_get_pkg_info
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * Stowe detaiws of the package cuwwentwy woaded in HW into the HW stwuctuwe.
 */
static enum ice_ddp_state ice_get_pkg_info(stwuct ice_hw *hw)
{
	DEFINE_FWEX(stwuct ice_aqc_get_pkg_info_wesp, pkg_info, pkg_info,
		    ICE_PKG_CNT);
	u16 size = __stwuct_size(pkg_info);
	u32 i;

	if (ice_aq_get_pkg_info_wist(hw, pkg_info, size, NUWW))
		wetuwn ICE_DDP_PKG_EWW;

	fow (i = 0; i < we32_to_cpu(pkg_info->count); i++) {
#define ICE_PKG_FWAG_COUNT 4
		chaw fwags[ICE_PKG_FWAG_COUNT + 1] = { 0 };
		u8 pwace = 0;

		if (pkg_info->pkg_info[i].is_active) {
			fwags[pwace++] = 'A';
			hw->active_pkg_vew = pkg_info->pkg_info[i].vew;
			hw->active_twack_id =
				we32_to_cpu(pkg_info->pkg_info[i].twack_id);
			memcpy(hw->active_pkg_name, pkg_info->pkg_info[i].name,
			       sizeof(pkg_info->pkg_info[i].name));
			hw->active_pkg_in_nvm = pkg_info->pkg_info[i].is_in_nvm;
		}
		if (pkg_info->pkg_info[i].is_active_at_boot)
			fwags[pwace++] = 'B';
		if (pkg_info->pkg_info[i].is_modified)
			fwags[pwace++] = 'M';
		if (pkg_info->pkg_info[i].is_in_nvm)
			fwags[pwace++] = 'N';

		ice_debug(hw, ICE_DBG_PKG, "Pkg[%d]: %d.%d.%d.%d,%s,%s\n", i,
			  pkg_info->pkg_info[i].vew.majow,
			  pkg_info->pkg_info[i].vew.minow,
			  pkg_info->pkg_info[i].vew.update,
			  pkg_info->pkg_info[i].vew.dwaft,
			  pkg_info->pkg_info[i].name, fwags);
	}

	wetuwn ICE_DDP_PKG_SUCCESS;
}

/**
 * ice_chk_pkg_compat
 * @hw: pointew to the hawdwawe stwuctuwe
 * @ospkg: pointew to the package hdw
 * @seg: pointew to the package segment hdw
 *
 * This function checks the package vewsion compatibiwity with dwivew and NVM
 */
static enum ice_ddp_state ice_chk_pkg_compat(stwuct ice_hw *hw,
					     stwuct ice_pkg_hdw *ospkg,
					     stwuct ice_seg **seg)
{
	DEFINE_FWEX(stwuct ice_aqc_get_pkg_info_wesp, pkg, pkg_info,
		    ICE_PKG_CNT);
	u16 size = __stwuct_size(pkg);
	enum ice_ddp_state state;
	u32 i;

	/* Check package vewsion compatibiwity */
	state = ice_chk_pkg_vewsion(&hw->pkg_vew);
	if (state) {
		ice_debug(hw, ICE_DBG_INIT, "Package vewsion check faiwed.\n");
		wetuwn state;
	}

	/* find ICE segment in given package */
	*seg = (stwuct ice_seg *)ice_find_seg_in_pkg(hw, hw->pkg_seg_id,
						     ospkg);
	if (!*seg) {
		ice_debug(hw, ICE_DBG_INIT, "no ice segment in package.\n");
		wetuwn ICE_DDP_PKG_INVAWID_FIWE;
	}

	/* Check if FW is compatibwe with the OS package */
	if (ice_aq_get_pkg_info_wist(hw, pkg, size, NUWW))
		wetuwn ICE_DDP_PKG_WOAD_EWWOW;

	fow (i = 0; i < we32_to_cpu(pkg->count); i++) {
		/* woop tiww we find the NVM package */
		if (!pkg->pkg_info[i].is_in_nvm)
			continue;
		if ((*seg)->hdw.seg_fowmat_vew.majow !=
			    pkg->pkg_info[i].vew.majow ||
		    (*seg)->hdw.seg_fowmat_vew.minow >
			    pkg->pkg_info[i].vew.minow) {
			state = ICE_DDP_PKG_FW_MISMATCH;
			ice_debug(hw, ICE_DBG_INIT,
				  "OS package is not compatibwe with NVM.\n");
		}
		/* done pwocessing NVM package so bweak */
		bweak;
	}

	wetuwn state;
}

/**
 * ice_init_pkg_hints
 * @hw: pointew to the HW stwuctuwe
 * @ice_seg: pointew to the segment of the package scan (non-NUWW)
 *
 * This function wiww scan the package and save off wewevant infowmation
 * (hints ow metadata) fow dwivew use. The ice_seg pawametew must not be NUWW
 * since the fiwst caww to ice_enum_wabews wequiwes a pointew to an actuaw
 * ice_seg stwuctuwe.
 */
static void ice_init_pkg_hints(stwuct ice_hw *hw, stwuct ice_seg *ice_seg)
{
	stwuct ice_pkg_enum state;
	chaw *wabew_name;
	u16 vaw;
	int i;

	memset(&hw->tnw, 0, sizeof(hw->tnw));
	memset(&state, 0, sizeof(state));

	if (!ice_seg)
		wetuwn;

	wabew_name = ice_enum_wabews(ice_seg, ICE_SID_WBW_WXPAWSEW_TMEM, &state,
				     &vaw);

	whiwe (wabew_name) {
		if (!stwncmp(wabew_name, ICE_TNW_PWE, stwwen(ICE_TNW_PWE)))
			/* check fow a tunnew entwy */
			ice_add_tunnew_hint(hw, wabew_name, vaw);

		/* check fow a dvm mode entwy */
		ewse if (!stwncmp(wabew_name, ICE_DVM_PWE, stwwen(ICE_DVM_PWE)))
			ice_add_dvm_hint(hw, vaw, twue);

		/* check fow a svm mode entwy */
		ewse if (!stwncmp(wabew_name, ICE_SVM_PWE, stwwen(ICE_SVM_PWE)))
			ice_add_dvm_hint(hw, vaw, fawse);

		wabew_name = ice_enum_wabews(NUWW, 0, &state, &vaw);
	}

	/* Cache the appwopwiate boost TCAM entwy pointews fow tunnews */
	fow (i = 0; i < hw->tnw.count; i++) {
		ice_find_boost_entwy(ice_seg, hw->tnw.tbw[i].boost_addw,
				     &hw->tnw.tbw[i].boost_entwy);
		if (hw->tnw.tbw[i].boost_entwy) {
			hw->tnw.tbw[i].vawid = twue;
			if (hw->tnw.tbw[i].type < __TNW_TYPE_CNT)
				hw->tnw.vawid_count[hw->tnw.tbw[i].type]++;
		}
	}

	/* Cache the appwopwiate boost TCAM entwy pointews fow DVM and SVM */
	fow (i = 0; i < hw->dvm_upd.count; i++)
		ice_find_boost_entwy(ice_seg, hw->dvm_upd.tbw[i].boost_addw,
				     &hw->dvm_upd.tbw[i].boost_entwy);
}

/**
 * ice_fiww_hw_ptype - fiww the enabwed PTYPE bit infowmation
 * @hw: pointew to the HW stwuctuwe
 */
static void ice_fiww_hw_ptype(stwuct ice_hw *hw)
{
	stwuct ice_mawkew_ptype_tcam_entwy *tcam;
	stwuct ice_seg *seg = hw->seg;
	stwuct ice_pkg_enum state;

	bitmap_zewo(hw->hw_ptype, ICE_FWOW_PTYPE_MAX);
	if (!seg)
		wetuwn;

	memset(&state, 0, sizeof(state));

	do {
		tcam = ice_pkg_enum_entwy(seg, &state,
					  ICE_SID_WXPAWSEW_MAWKEW_PTYPE, NUWW,
					  ice_mawkew_ptype_tcam_handwew);
		if (tcam &&
		    we16_to_cpu(tcam->addw) < ICE_MAWKEW_PTYPE_TCAM_ADDW_MAX &&
		    we16_to_cpu(tcam->ptype) < ICE_FWOW_PTYPE_MAX)
			set_bit(we16_to_cpu(tcam->ptype), hw->hw_ptype);

		seg = NUWW;
	} whiwe (tcam);
}

/**
 * ice_init_pkg - initiawize/downwoad package
 * @hw: pointew to the hawdwawe stwuctuwe
 * @buf: pointew to the package buffew
 * @wen: size of the package buffew
 *
 * This function initiawizes a package. The package contains HW tabwes
 * wequiwed to do packet pwocessing. Fiwst, the function extwacts package
 * infowmation such as vewsion. Then it finds the ice configuwation segment
 * within the package; this function then saves a copy of the segment pointew
 * within the suppwied package buffew. Next, the function wiww cache any hints
 * fwom the package, fowwowed by downwoading the package itsewf. Note, that if
 * a pwevious PF dwivew has awweady downwoaded the package successfuwwy, then
 * the cuwwent dwivew wiww not have to downwoad the package again.
 *
 * The wocaw package contents wiww be used to quewy defauwt behaviow and to
 * update specific sections of the HW's vewsion of the package (e.g. to update
 * the pawse gwaph to undewstand new pwotocows).
 *
 * This function stowes a pointew to the package buffew memowy, and it is
 * expected that the suppwied buffew wiww not be fweed immediatewy. If the
 * package buffew needs to be fweed, such as when wead fwom a fiwe, use
 * ice_copy_and_init_pkg() instead of diwectwy cawwing ice_init_pkg() in this
 * case.
 */
enum ice_ddp_state ice_init_pkg(stwuct ice_hw *hw, u8 *buf, u32 wen)
{
	boow awweady_woaded = fawse;
	enum ice_ddp_state state;
	stwuct ice_pkg_hdw *pkg;
	stwuct ice_seg *seg;

	if (!buf || !wen)
		wetuwn ICE_DDP_PKG_EWW;

	pkg = (stwuct ice_pkg_hdw *)buf;
	state = ice_vewify_pkg(pkg, wen);
	if (state) {
		ice_debug(hw, ICE_DBG_INIT, "faiwed to vewify pkg (eww: %d)\n",
			  state);
		wetuwn state;
	}

	/* initiawize package info */
	state = ice_init_pkg_info(hw, pkg);
	if (state)
		wetuwn state;

	/* must be a matching segment */
	if (hw->pkg_has_signing_seg &&
	    !ice_match_signing_seg(pkg, hw->pkg_seg_id, hw->pkg_sign_type))
		wetuwn ICE_DDP_PKG_EWW;

	/* befowe downwoading the package, check package vewsion fow
	 * compatibiwity with dwivew
	 */
	state = ice_chk_pkg_compat(hw, pkg, &seg);
	if (state)
		wetuwn state;

	/* initiawize package hints and then downwoad package */
	ice_init_pkg_hints(hw, seg);
	state = ice_downwoad_pkg(hw, pkg, seg);
	if (state == ICE_DDP_PKG_AWWEADY_WOADED) {
		ice_debug(hw, ICE_DBG_INIT,
			  "package pweviouswy woaded - no wowk.\n");
		awweady_woaded = twue;
	}

	/* Get infowmation on the package cuwwentwy woaded in HW, then make suwe
	 * the dwivew is compatibwe with this vewsion.
	 */
	if (!state || state == ICE_DDP_PKG_AWWEADY_WOADED) {
		state = ice_get_pkg_info(hw);
		if (!state)
			state = ice_get_ddp_pkg_state(hw, awweady_woaded);
	}

	if (ice_is_init_pkg_successfuw(state)) {
		hw->seg = seg;
		/* on successfuw package downwoad update othew wequiwed
		 * wegistews to suppowt the package and fiww HW tabwes
		 * with package content.
		 */
		ice_init_pkg_wegs(hw);
		ice_fiww_bwk_tbws(hw);
		ice_fiww_hw_ptype(hw);
		ice_get_pwof_index_max(hw);
	} ewse {
		ice_debug(hw, ICE_DBG_INIT, "package woad faiwed, %d\n", state);
	}

	wetuwn state;
}

/**
 * ice_copy_and_init_pkg - initiawize/downwoad a copy of the package
 * @hw: pointew to the hawdwawe stwuctuwe
 * @buf: pointew to the package buffew
 * @wen: size of the package buffew
 *
 * This function copies the package buffew, and then cawws ice_init_pkg() to
 * initiawize the copied package contents.
 *
 * The copying is necessawy if the package buffew suppwied is constant, ow if
 * the memowy may disappeaw showtwy aftew cawwing this function.
 *
 * If the package buffew wesides in the data segment and can be modified, the
 * cawwew is fwee to use ice_init_pkg() instead of ice_copy_and_init_pkg().
 *
 * Howevew, if the package buffew needs to be copied fiwst, such as when being
 * wead fwom a fiwe, the cawwew shouwd use ice_copy_and_init_pkg().
 *
 * This function wiww fiwst copy the package buffew, befowe cawwing
 * ice_init_pkg(). The cawwew is fwee to immediatewy destwoy the owiginaw
 * package buffew, as the new copy wiww be managed by this function and
 * wewated woutines.
 */
enum ice_ddp_state ice_copy_and_init_pkg(stwuct ice_hw *hw, const u8 *buf,
					 u32 wen)
{
	enum ice_ddp_state state;
	u8 *buf_copy;

	if (!buf || !wen)
		wetuwn ICE_DDP_PKG_EWW;

	buf_copy = devm_kmemdup(ice_hw_to_dev(hw), buf, wen, GFP_KEWNEW);

	state = ice_init_pkg(hw, buf_copy, wen);
	if (!ice_is_init_pkg_successfuw(state)) {
		/* Fwee the copy, since we faiwed to initiawize the package */
		devm_kfwee(ice_hw_to_dev(hw), buf_copy);
	} ewse {
		/* Twack the copied pkg so we can fwee it watew */
		hw->pkg_copy = buf_copy;
		hw->pkg_size = wen;
	}

	wetuwn state;
}
