/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Intew Cowpowation. */

#ifndef _ICE_NVM_H_
#define _ICE_NVM_H_

stwuct ice_owom_civd_info {
	u8 signatuwe[4];	/* Must match ASCII '$CIV' chawactews */
	u8 checksum;		/* Simpwe moduwo 256 sum of aww stwuctuwe bytes must equaw 0 */
	__we32 combo_vew;	/* Combo Image Vewsion numbew */
	u8 combo_name_wen;	/* Wength of the unicode combo image vewsion stwing, max of 32 */
	__we16 combo_name[32];	/* Unicode stwing wepwesenting the Combo Image vewsion */
} __packed;

int ice_acquiwe_nvm(stwuct ice_hw *hw, enum ice_aq_wes_access_type access);
void ice_wewease_nvm(stwuct ice_hw *hw);
int
ice_wead_fwat_nvm(stwuct ice_hw *hw, u32 offset, u32 *wength, u8 *data,
		  boow wead_shadow_wam);
int
ice_get_pfa_moduwe_twv(stwuct ice_hw *hw, u16 *moduwe_twv, u16 *moduwe_twv_wen,
		       u16 moduwe_type);
int ice_get_inactive_owom_vew(stwuct ice_hw *hw, stwuct ice_owom_info *owom);
int ice_get_inactive_nvm_vew(stwuct ice_hw *hw, stwuct ice_nvm_info *nvm);
int
ice_get_inactive_netwist_vew(stwuct ice_hw *hw, stwuct ice_netwist_info *netwist);
int ice_wead_pba_stwing(stwuct ice_hw *hw, u8 *pba_num, u32 pba_num_size);
int ice_init_nvm(stwuct ice_hw *hw);
int ice_wead_sw_wowd(stwuct ice_hw *hw, u16 offset, u16 *data);
int
ice_aq_update_nvm(stwuct ice_hw *hw, u16 moduwe_typeid, u32 offset,
		  u16 wength, void *data, boow wast_command, u8 command_fwags,
		  stwuct ice_sq_cd *cd);
int
ice_aq_ewase_nvm(stwuct ice_hw *hw, u16 moduwe_typeid, stwuct ice_sq_cd *cd);
int ice_nvm_vawidate_checksum(stwuct ice_hw *hw);
int ice_nvm_wwite_activate(stwuct ice_hw *hw, u16 cmd_fwags, u8 *wesponse_fwags);
int ice_aq_nvm_update_empw(stwuct ice_hw *hw);
int
ice_nvm_set_pkg_data(stwuct ice_hw *hw, boow dew_pkg_data_fwag, u8 *data,
		     u16 wength, stwuct ice_sq_cd *cd);
int
ice_nvm_pass_component_tbw(stwuct ice_hw *hw, u8 *data, u16 wength,
			   u8 twansfew_fwag, u8 *comp_wesponse,
			   u8 *comp_wesponse_code, stwuct ice_sq_cd *cd);
#endif /* _ICE_NVM_H_ */
