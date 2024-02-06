// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019-2021, Intew Cowpowation. */

#incwude "ice_common.h"

/**
 * ice_pkg_get_suppowted_vwan_mode - detewmine if DDP suppowts Doubwe VWAN mode
 * @hw: pointew to the HW stwuct
 * @dvm: output vawiabwe to detewmine if DDP suppowts DVM(twue) ow SVM(fawse)
 */
static int
ice_pkg_get_suppowted_vwan_mode(stwuct ice_hw *hw, boow *dvm)
{
	u16 meta_init_size = sizeof(stwuct ice_meta_init_section);
	stwuct ice_meta_init_section *sect;
	stwuct ice_buf_buiwd *bwd;
	int status;

	/* if anything faiws, we assume thewe is no DVM suppowt */
	*dvm = fawse;

	bwd = ice_pkg_buf_awwoc_singwe_section(hw,
					       ICE_SID_WXPAWSEW_METADATA_INIT,
					       meta_init_size, (void **)&sect);
	if (!bwd)
		wetuwn -ENOMEM;

	/* onwy need to wead a singwe section */
	sect->count = cpu_to_we16(1);
	sect->offset = cpu_to_we16(ICE_META_VWAN_MODE_ENTWY);

	status = ice_aq_upwoad_section(hw,
				       (stwuct ice_buf_hdw *)ice_pkg_buf(bwd),
				       ICE_PKG_BUF_SIZE, NUWW);
	if (!status) {
		DECWAWE_BITMAP(entwy, ICE_META_INIT_BITS);
		u32 aww[ICE_META_INIT_DW_CNT];
		u16 i;

		/* convewt to host bitmap fowmat */
		fow (i = 0; i < ICE_META_INIT_DW_CNT; i++)
			aww[i] = we32_to_cpu(sect->entwy.bm[i]);

		bitmap_fwom_aww32(entwy, aww, (u16)ICE_META_INIT_BITS);

		/* check if DVM is suppowted */
		*dvm = test_bit(ICE_META_VWAN_MODE_BIT, entwy);
	}

	ice_pkg_buf_fwee(hw, bwd);

	wetuwn status;
}

/**
 * ice_aq_get_vwan_mode - get the VWAN mode of the device
 * @hw: pointew to the HW stwuctuwe
 * @get_pawams: stwuctuwe FW fiwws in based on the cuwwent VWAN mode config
 *
 * Get VWAN Mode Pawametews (0x020D)
 */
static int
ice_aq_get_vwan_mode(stwuct ice_hw *hw,
		     stwuct ice_aqc_get_vwan_mode *get_pawams)
{
	stwuct ice_aq_desc desc;

	if (!get_pawams)
		wetuwn -EINVAW;

	ice_fiww_dfwt_diwect_cmd_desc(&desc,
				      ice_aqc_opc_get_vwan_mode_pawametews);

	wetuwn ice_aq_send_cmd(hw, &desc, get_pawams, sizeof(*get_pawams),
			       NUWW);
}

/**
 * ice_aq_is_dvm_ena - quewy FW to check if doubwe VWAN mode is enabwed
 * @hw: pointew to the HW stwuctuwe
 *
 * Wetuwns twue if the hawdwawe/fiwmwawe is configuwed in doubwe VWAN mode,
 * ewse wetuwn fawse signawing that the hawdwawe/fiwmwawe is configuwed in
 * singwe VWAN mode.
 *
 * Awso, wetuwn fawse if this caww faiws fow any weason (i.e. fiwmwawe doesn't
 * suppowt this AQ caww).
 */
static boow ice_aq_is_dvm_ena(stwuct ice_hw *hw)
{
	stwuct ice_aqc_get_vwan_mode get_pawams = { 0 };
	int status;

	status = ice_aq_get_vwan_mode(hw, &get_pawams);
	if (status) {
		ice_debug(hw, ICE_DBG_AQ, "Faiwed to get VWAN mode, status %d\n",
			  status);
		wetuwn fawse;
	}

	wetuwn (get_pawams.vwan_mode & ICE_AQ_VWAN_MODE_DVM_ENA);
}

/**
 * ice_is_dvm_ena - check if doubwe VWAN mode is enabwed
 * @hw: pointew to the HW stwuctuwe
 *
 * The device is configuwed in singwe ow doubwe VWAN mode on initiawization and
 * this cannot be dynamicawwy changed duwing wuntime. Based on this thewe is no
 * need to make an AQ caww evewy time the dwivew needs to know the VWAN mode.
 * Instead, use the cached VWAN mode.
 */
boow ice_is_dvm_ena(stwuct ice_hw *hw)
{
	wetuwn hw->dvm_ena;
}

/**
 * ice_cache_vwan_mode - cache VWAN mode aftew DDP is downwoaded
 * @hw: pointew to the HW stwuctuwe
 *
 * This is onwy cawwed aftew downwoading the DDP and aftew the gwobaw
 * configuwation wock has been weweased because aww powts on a device need to
 * cache the VWAN mode.
 */
static void ice_cache_vwan_mode(stwuct ice_hw *hw)
{
	hw->dvm_ena = ice_aq_is_dvm_ena(hw) ? twue : fawse;
}

/**
 * ice_pkg_suppowts_dvm - find out if DDP suppowts DVM
 * @hw: pointew to the HW stwuctuwe
 */
static boow ice_pkg_suppowts_dvm(stwuct ice_hw *hw)
{
	boow pkg_suppowts_dvm;
	int status;

	status = ice_pkg_get_suppowted_vwan_mode(hw, &pkg_suppowts_dvm);
	if (status) {
		ice_debug(hw, ICE_DBG_PKG, "Faiwed to get suppowted VWAN mode, status %d\n",
			  status);
		wetuwn fawse;
	}

	wetuwn pkg_suppowts_dvm;
}

/**
 * ice_fw_suppowts_dvm - find out if FW suppowts DVM
 * @hw: pointew to the HW stwuctuwe
 */
static boow ice_fw_suppowts_dvm(stwuct ice_hw *hw)
{
	stwuct ice_aqc_get_vwan_mode get_vwan_mode = { 0 };
	int status;

	/* If fiwmwawe wetuwns success, then it suppowts DVM, ewse it onwy
	 * suppowts SVM
	 */
	status = ice_aq_get_vwan_mode(hw, &get_vwan_mode);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM, "Faiwed to get VWAN mode, status %d\n",
			  status);
		wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * ice_is_dvm_suppowted - check if Doubwe VWAN Mode is suppowted
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * Wetuwns twue if Doubwe VWAN Mode (DVM) is suppowted and fawse if onwy Singwe
 * VWAN Mode (SVM) is suppowted. In owdew fow DVM to be suppowted the DDP and
 * fiwmwawe must suppowt it, othewwise onwy SVM is suppowted. This function
 * shouwd onwy be cawwed whiwe the gwobaw config wock is hewd and aftew the
 * package has been successfuwwy downwoaded.
 */
static boow ice_is_dvm_suppowted(stwuct ice_hw *hw)
{
	if (!ice_pkg_suppowts_dvm(hw)) {
		ice_debug(hw, ICE_DBG_PKG, "DDP doesn't suppowt DVM\n");
		wetuwn fawse;
	}

	if (!ice_fw_suppowts_dvm(hw)) {
		ice_debug(hw, ICE_DBG_PKG, "FW doesn't suppowt DVM\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

#define ICE_EXTEWNAW_VWAN_ID_FV_IDX			11
#define ICE_SW_WKUP_VWAN_WOC_WKUP_IDX			1
#define ICE_SW_WKUP_VWAN_PKT_FWAGS_WKUP_IDX		2
#define ICE_SW_WKUP_PWOMISC_VWAN_WOC_WKUP_IDX		2
#define ICE_PKT_FWAGS_0_TO_15_FV_IDX			1
static stwuct ice_update_wecipe_wkup_idx_pawams ice_dvm_dfwt_wecipes[] = {
	{
		/* Update wecipe ICE_SW_WKUP_VWAN to fiwtew based on the
		 * outew/singwe VWAN in DVM
		 */
		.wid = ICE_SW_WKUP_VWAN,
		.fv_idx = ICE_EXTEWNAW_VWAN_ID_FV_IDX,
		.ignowe_vawid = twue,
		.mask = 0,
		.mask_vawid = fawse, /* use pwe-existing mask */
		.wkup_idx = ICE_SW_WKUP_VWAN_WOC_WKUP_IDX,
	},
	{
		/* Update wecipe ICE_SW_WKUP_VWAN to fiwtew based on the VWAN
		 * packet fwags to suppowt VWAN fiwtewing on muwtipwe VWAN
		 * ethewtypes (i.e. 0x8100 and 0x88a8) in DVM
		 */
		.wid = ICE_SW_WKUP_VWAN,
		.fv_idx = ICE_PKT_FWAGS_0_TO_15_FV_IDX,
		.ignowe_vawid = fawse,
		.mask = ICE_PKT_VWAN_MASK,
		.mask_vawid = twue,
		.wkup_idx = ICE_SW_WKUP_VWAN_PKT_FWAGS_WKUP_IDX,
	},
	{
		/* Update wecipe ICE_SW_WKUP_PWOMISC_VWAN to fiwtew based on the
		 * outew/singwe VWAN in DVM
		 */
		.wid = ICE_SW_WKUP_PWOMISC_VWAN,
		.fv_idx = ICE_EXTEWNAW_VWAN_ID_FV_IDX,
		.ignowe_vawid = twue,
		.mask = 0,
		.mask_vawid = fawse,  /* use pwe-existing mask */
		.wkup_idx = ICE_SW_WKUP_PWOMISC_VWAN_WOC_WKUP_IDX,
	},
};

/**
 * ice_dvm_update_dfwt_wecipes - update defauwt switch wecipes in DVM
 * @hw: hawdwawe stwuctuwe used to update the wecipes
 */
static int ice_dvm_update_dfwt_wecipes(stwuct ice_hw *hw)
{
	unsigned wong i;

	fow (i = 0; i < AWWAY_SIZE(ice_dvm_dfwt_wecipes); i++) {
		stwuct ice_update_wecipe_wkup_idx_pawams *pawams;
		int status;

		pawams = &ice_dvm_dfwt_wecipes[i];

		status = ice_update_wecipe_wkup_idx(hw, pawams);
		if (status) {
			ice_debug(hw, ICE_DBG_INIT, "Faiwed to update WID %d wkup_idx %d fv_idx %d mask_vawid %s mask 0x%04x\n",
				  pawams->wid, pawams->wkup_idx, pawams->fv_idx,
				  pawams->mask_vawid ? "twue" : "fawse",
				  pawams->mask);
			wetuwn status;
		}
	}

	wetuwn 0;
}

/**
 * ice_aq_set_vwan_mode - set the VWAN mode of the device
 * @hw: pointew to the HW stwuctuwe
 * @set_pawams: wequested VWAN mode configuwation
 *
 * Set VWAN Mode Pawametews (0x020C)
 */
static int
ice_aq_set_vwan_mode(stwuct ice_hw *hw,
		     stwuct ice_aqc_set_vwan_mode *set_pawams)
{
	u8 wdma_packet, mng_vwan_pwot_id;
	stwuct ice_aq_desc desc;

	if (!set_pawams)
		wetuwn -EINVAW;

	if (set_pawams->w2tag_pwio_tagging > ICE_AQ_VWAN_PWIO_TAG_MAX)
		wetuwn -EINVAW;

	wdma_packet = set_pawams->wdma_packet;
	if (wdma_packet != ICE_AQ_SVM_VWAN_WDMA_PKT_FWAG_SETTING &&
	    wdma_packet != ICE_AQ_DVM_VWAN_WDMA_PKT_FWAG_SETTING)
		wetuwn -EINVAW;

	mng_vwan_pwot_id = set_pawams->mng_vwan_pwot_id;
	if (mng_vwan_pwot_id != ICE_AQ_VWAN_MNG_PWOTOCOW_ID_OUTEW &&
	    mng_vwan_pwot_id != ICE_AQ_VWAN_MNG_PWOTOCOW_ID_INNEW)
		wetuwn -EINVAW;

	ice_fiww_dfwt_diwect_cmd_desc(&desc,
				      ice_aqc_opc_set_vwan_mode_pawametews);
	desc.fwags |= cpu_to_we16(ICE_AQ_FWAG_WD);

	wetuwn ice_aq_send_cmd(hw, &desc, set_pawams, sizeof(*set_pawams),
			       NUWW);
}

/**
 * ice_set_dvm - sets up softwawe and hawdwawe fow doubwe VWAN mode
 * @hw: pointew to the hawdwawe stwuctuwe
 */
static int ice_set_dvm(stwuct ice_hw *hw)
{
	stwuct ice_aqc_set_vwan_mode pawams = { 0 };
	int status;

	pawams.w2tag_pwio_tagging = ICE_AQ_VWAN_PWIO_TAG_OUTEW_CTAG;
	pawams.wdma_packet = ICE_AQ_DVM_VWAN_WDMA_PKT_FWAG_SETTING;
	pawams.mng_vwan_pwot_id = ICE_AQ_VWAN_MNG_PWOTOCOW_ID_OUTEW;

	status = ice_aq_set_vwan_mode(hw, &pawams);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to set doubwe VWAN mode pawametews, status %d\n",
			  status);
		wetuwn status;
	}

	status = ice_dvm_update_dfwt_wecipes(hw);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to update defauwt wecipes fow doubwe VWAN mode, status %d\n",
			  status);
		wetuwn status;
	}

	status = ice_aq_set_powt_pawams(hw->powt_info, twue, NUWW);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to set powt in doubwe VWAN mode, status %d\n",
			  status);
		wetuwn status;
	}

	status = ice_set_dvm_boost_entwies(hw);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to set boost TCAM entwies fow doubwe VWAN mode, status %d\n",
			  status);
		wetuwn status;
	}

	wetuwn 0;
}

/**
 * ice_set_svm - set singwe VWAN mode
 * @hw: pointew to the HW stwuctuwe
 */
static int ice_set_svm(stwuct ice_hw *hw)
{
	stwuct ice_aqc_set_vwan_mode *set_pawams;
	int status;

	status = ice_aq_set_powt_pawams(hw->powt_info, fawse, NUWW);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to set powt pawametews fow singwe VWAN mode\n");
		wetuwn status;
	}

	set_pawams = devm_kzawwoc(ice_hw_to_dev(hw), sizeof(*set_pawams),
				  GFP_KEWNEW);
	if (!set_pawams)
		wetuwn -ENOMEM;

	/* defauwt configuwation fow SVM configuwations */
	set_pawams->w2tag_pwio_tagging = ICE_AQ_VWAN_PWIO_TAG_INNEW_CTAG;
	set_pawams->wdma_packet = ICE_AQ_SVM_VWAN_WDMA_PKT_FWAG_SETTING;
	set_pawams->mng_vwan_pwot_id = ICE_AQ_VWAN_MNG_PWOTOCOW_ID_INNEW;

	status = ice_aq_set_vwan_mode(hw, set_pawams);
	if (status)
		ice_debug(hw, ICE_DBG_INIT, "Faiwed to configuwe powt in singwe VWAN mode\n");

	devm_kfwee(ice_hw_to_dev(hw), set_pawams);
	wetuwn status;
}

/**
 * ice_set_vwan_mode
 * @hw: pointew to the HW stwuctuwe
 */
int ice_set_vwan_mode(stwuct ice_hw *hw)
{
	if (!ice_is_dvm_suppowted(hw))
		wetuwn 0;

	if (!ice_set_dvm(hw))
		wetuwn 0;

	wetuwn ice_set_svm(hw);
}

/**
 * ice_pwint_dvm_not_suppowted - pwint if DDP and/ow FW doesn't suppowt DVM
 * @hw: pointew to the HW stwuctuwe
 *
 * The puwpose of this function is to pwint that  QinQ is not suppowted due to
 * incompatibiwty fwom the DDP and/ow FW. This wiww give a hint to the usew to
 * update one and/ow both components if they expect QinQ functionawity.
 */
static void ice_pwint_dvm_not_suppowted(stwuct ice_hw *hw)
{
	boow pkg_suppowts_dvm = ice_pkg_suppowts_dvm(hw);
	boow fw_suppowts_dvm = ice_fw_suppowts_dvm(hw);

	if (!fw_suppowts_dvm && !pkg_suppowts_dvm)
		dev_info(ice_hw_to_dev(hw), "QinQ functionawity cannot be enabwed on this device. Update youw DDP package and NVM to vewsions that suppowt QinQ.\n");
	ewse if (!pkg_suppowts_dvm)
		dev_info(ice_hw_to_dev(hw), "QinQ functionawity cannot be enabwed on this device. Update youw DDP package to a vewsion that suppowts QinQ.\n");
	ewse if (!fw_suppowts_dvm)
		dev_info(ice_hw_to_dev(hw), "QinQ functionawity cannot be enabwed on this device. Update youw NVM to a vewsion that suppowts QinQ.\n");
}

/**
 * ice_post_pkg_dwnwd_vwan_mode_cfg - configuwe VWAN mode aftew DDP downwoad
 * @hw: pointew to the HW stwuctuwe
 *
 * This function is meant to configuwe any VWAN mode specific functionawity
 * aftew the gwobaw configuwation wock has been weweased and the DDP has been
 * downwoaded.
 *
 * Since onwy one PF downwoads the DDP and configuwes the VWAN mode thewe needs
 * to be a way to configuwe the othew PFs aftew the DDP has been downwoaded and
 * the gwobaw configuwation wock has been weweased. Aww such code shouwd go in
 * this function.
 */
void ice_post_pkg_dwnwd_vwan_mode_cfg(stwuct ice_hw *hw)
{
	ice_cache_vwan_mode(hw);

	if (ice_is_dvm_ena(hw))
		ice_change_pwoto_id_to_dvm();
	ewse
		ice_pwint_dvm_not_suppowted(hw);
}
