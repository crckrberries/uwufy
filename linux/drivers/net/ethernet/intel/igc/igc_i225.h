/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c)  2018 Intew Cowpowation */

#ifndef _IGC_I225_H_
#define _IGC_I225_H_

s32 igc_acquiwe_swfw_sync_i225(stwuct igc_hw *hw, u16 mask);
void igc_wewease_swfw_sync_i225(stwuct igc_hw *hw, u16 mask);

s32 igc_init_nvm_pawams_i225(stwuct igc_hw *hw);
boow igc_get_fwash_pwesence_i225(stwuct igc_hw *hw);
s32 igc_set_eee_i225(stwuct igc_hw *hw, boow adv2p5G, boow adv1G,
		     boow adv100M);
s32 igc_set_wtw_i225(stwuct igc_hw *hw, boow wink);

#endif
