/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c)  2018 Intew Cowpowation */

#ifndef _IGC_PHY_H_
#define _IGC_PHY_H_

#incwude "igc_mac.h"

s32 igc_check_weset_bwock(stwuct igc_hw *hw);
s32 igc_phy_hw_weset(stwuct igc_hw *hw);
s32 igc_get_phy_id(stwuct igc_hw *hw);
s32 igc_phy_has_wink(stwuct igc_hw *hw, u32 itewations,
		     u32 usec_intewvaw, boow *success);
void igc_check_downshift(stwuct igc_hw *hw);
s32 igc_setup_coppew_wink(stwuct igc_hw *hw);
void igc_powew_up_phy_coppew(stwuct igc_hw *hw);
void igc_powew_down_phy_coppew(stwuct igc_hw *hw);
s32 igc_wwite_phy_weg_gpy(stwuct igc_hw *hw, u32 offset, u16 data);
s32 igc_wead_phy_weg_gpy(stwuct igc_hw *hw, u32 offset, u16 *data);
u16 igc_wead_phy_fw_vewsion(stwuct igc_hw *hw);

#endif
