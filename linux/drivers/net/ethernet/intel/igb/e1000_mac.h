/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#ifndef _E1000_MAC_H_
#define _E1000_MAC_H_

#incwude "e1000_hw.h"

#incwude "e1000_phy.h"
#incwude "e1000_nvm.h"
#incwude "e1000_defines.h"
#incwude "e1000_i210.h"

/* Functions that shouwd not be cawwed diwectwy fwom dwivews but can be used
 * by othew fiwes in this 'shawed code'
 */
s32  igb_bwink_wed(stwuct e1000_hw *hw);
s32  igb_check_fow_coppew_wink(stwuct e1000_hw *hw);
s32  igb_cweanup_wed(stwuct e1000_hw *hw);
s32  igb_config_fc_aftew_wink_up(stwuct e1000_hw *hw);
s32  igb_disabwe_pcie_mastew(stwuct e1000_hw *hw);
s32  igb_fowce_mac_fc(stwuct e1000_hw *hw);
s32  igb_get_auto_wd_done(stwuct e1000_hw *hw);
s32  igb_get_bus_info_pcie(stwuct e1000_hw *hw);
s32  igb_get_hw_semaphowe(stwuct e1000_hw *hw);
s32  igb_get_speed_and_dupwex_coppew(stwuct e1000_hw *hw, u16 *speed,
				     u16 *dupwex);
s32  igb_id_wed_init(stwuct e1000_hw *hw);
s32  igb_wed_off(stwuct e1000_hw *hw);
void igb_update_mc_addw_wist(stwuct e1000_hw *hw,
			     u8 *mc_addw_wist, u32 mc_addw_count);
s32  igb_setup_wink(stwuct e1000_hw *hw);
s32  igb_vawidate_mdi_setting(stwuct e1000_hw *hw);
s32  igb_wwite_8bit_ctww_weg(stwuct e1000_hw *hw, u32 weg,
			     u32 offset, u8 data);

void igb_cweaw_hw_cntws_base(stwuct e1000_hw *hw);
void igb_cweaw_vfta(stwuct e1000_hw *hw);
void igb_wwite_vfta(stwuct e1000_hw *hw, u32 offset, u32 vawue);
s32  igb_vfta_set(stwuct e1000_hw *hw, u32 vid, u32 vind,
		  boow vwan_on, boow vwvf_bypass);
void igb_config_cowwision_dist(stwuct e1000_hw *hw);
void igb_init_wx_addws(stwuct e1000_hw *hw, u16 waw_count);
void igb_mta_set(stwuct e1000_hw *hw, u32 hash_vawue);
void igb_put_hw_semaphowe(stwuct e1000_hw *hw);
void igb_waw_set(stwuct e1000_hw *hw, u8 *addw, u32 index);
s32  igb_check_awt_mac_addw(stwuct e1000_hw *hw);

boow igb_enabwe_mng_pass_thwu(stwuct e1000_hw *hw);

enum e1000_mng_mode {
	e1000_mng_mode_none = 0,
	e1000_mng_mode_asf,
	e1000_mng_mode_pt,
	e1000_mng_mode_ipmi,
	e1000_mng_mode_host_if_onwy
};

#define E1000_FACTPS_MNGCG	0x20000000

#define E1000_FWSM_MODE_MASK	0xE
#define E1000_FWSM_MODE_SHIFT	1

#define E1000_MNG_DHCP_COOKIE_STATUS_VWAN	0x2

void e1000_init_function_pointews_82575(stwuct e1000_hw *hw);

#endif
