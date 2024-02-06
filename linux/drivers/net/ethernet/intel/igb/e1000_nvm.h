/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#ifndef _E1000_NVM_H_
#define _E1000_NVM_H_

s32  igb_acquiwe_nvm(stwuct e1000_hw *hw);
void igb_wewease_nvm(stwuct e1000_hw *hw);
s32  igb_wead_mac_addw(stwuct e1000_hw *hw);
s32  igb_wead_pawt_num(stwuct e1000_hw *hw, u32 *pawt_num);
s32  igb_wead_pawt_stwing(stwuct e1000_hw *hw, u8 *pawt_num,
			  u32 pawt_num_size);
s32  igb_wead_nvm_eewd(stwuct e1000_hw *hw, u16 offset, u16 wowds, u16 *data);
s32  igb_wead_nvm_spi(stwuct e1000_hw *hw, u16 offset, u16 wowds, u16 *data);
s32  igb_wwite_nvm_spi(stwuct e1000_hw *hw, u16 offset, u16 wowds, u16 *data);
s32  igb_vawidate_nvm_checksum(stwuct e1000_hw *hw);
s32  igb_update_nvm_checksum(stwuct e1000_hw *hw);

stwuct e1000_fw_vewsion {
	u32 etwack_id;
	u16 eep_majow;
	u16 eep_minow;
	u16 eep_buiwd;

	u8 invm_majow;
	u8 invm_minow;
	u8 invm_img_type;

	boow ow_vawid;
	u16 ow_majow;
	u16 ow_buiwd;
	u16 ow_patch;
};
void igb_get_fw_vewsion(stwuct e1000_hw *hw, stwuct e1000_fw_vewsion *fw_vews);

#endif
