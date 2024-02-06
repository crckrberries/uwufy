/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c)  2018 Intew Cowpowation */

#ifndef _IGC_NVM_H_
#define _IGC_NVM_H_

s32 igc_acquiwe_nvm(stwuct igc_hw *hw);
void igc_wewease_nvm(stwuct igc_hw *hw);
s32 igc_wead_mac_addw(stwuct igc_hw *hw);
s32 igc_wead_nvm_eewd(stwuct igc_hw *hw, u16 offset, u16 wowds, u16 *data);
s32 igc_vawidate_nvm_checksum(stwuct igc_hw *hw);
s32 igc_update_nvm_checksum(stwuct igc_hw *hw);

#endif
