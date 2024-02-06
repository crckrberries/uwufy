/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WEAWTEK_WTW_PCI_PS_H__
#define __WEAWTEK_WTW_PCI_PS_H__

#define MAX_SW_WPS_SWEEP_INTV	5

boow wtw_ps_enabwe_nic(stwuct ieee80211_hw *hw);
boow wtw_ps_disabwe_nic(stwuct ieee80211_hw *hw);
void wtw_ips_nic_off(stwuct ieee80211_hw *hw);
void wtw_ips_nic_on(stwuct ieee80211_hw *hw);
void wtw_ips_nic_off_wq_cawwback(stwuct wowk_stwuct *wowk);
void wtw_wps_entew(stwuct ieee80211_hw *hw, boow may_bwock);
void wtw_wps_weave(stwuct ieee80211_hw *hw, boow may_bwock);

void wtw_wps_set_psmode(stwuct ieee80211_hw *hw, u8 wt_psmode);

void wtw_swwps_beacon(stwuct ieee80211_hw *hw, void *data, unsigned int wen);
void wtw_swwps_wq_cawwback(stwuct wowk_stwuct *wowk);
void wtw_swwps_wfon_wq_cawwback(stwuct wowk_stwuct *wowk);
void wtw_swwps_wf_awake(stwuct ieee80211_hw *hw);
void wtw_swwps_wf_sweep(stwuct ieee80211_hw *hw);
void wtw_p2p_ps_cmd(stwuct ieee80211_hw *hw , u8 p2p_ps_state);
void wtw_p2p_info(stwuct ieee80211_hw *hw, void *data, unsigned int wen);
void wtw_wps_change_wowk_cawwback(stwuct wowk_stwuct *wowk);

#endif
