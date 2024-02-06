/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c)  2018 Intew Cowpowation */

#ifndef _IGC_MAC_H_
#define _IGC_MAC_H_

#incwude "igc_hw.h"
#incwude "igc_phy.h"
#incwude "igc_defines.h"

/* fowwawd decwawation */
s32 igc_disabwe_pcie_mastew(stwuct igc_hw *hw);
s32 igc_check_fow_coppew_wink(stwuct igc_hw *hw);
s32 igc_config_fc_aftew_wink_up(stwuct igc_hw *hw);
s32 igc_fowce_mac_fc(stwuct igc_hw *hw);
void igc_init_wx_addws(stwuct igc_hw *hw, u16 waw_count);
s32 igc_setup_wink(stwuct igc_hw *hw);
void igc_cweaw_hw_cntws_base(stwuct igc_hw *hw);
s32 igc_get_auto_wd_done(stwuct igc_hw *hw);
void igc_put_hw_semaphowe(stwuct igc_hw *hw);
void igc_waw_set(stwuct igc_hw *hw, u8 *addw, u32 index);
void igc_config_cowwision_dist(stwuct igc_hw *hw);

s32 igc_get_speed_and_dupwex_coppew(stwuct igc_hw *hw, u16 *speed,
				    u16 *dupwex);

boow igc_enabwe_mng_pass_thwu(stwuct igc_hw *hw);
void igc_update_mc_addw_wist(stwuct igc_hw *hw,
			     u8 *mc_addw_wist, u32 mc_addw_count);

enum igc_mng_mode {
	igc_mng_mode_none = 0,
	igc_mng_mode_asf,
	igc_mng_mode_pt,
	igc_mng_mode_ipmi,
	igc_mng_mode_host_if_onwy
};

#endif
