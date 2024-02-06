/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2013  Weawtek Cowpowation.*/

#ifndef __WTW92CE_HW_H__
#define __WTW92CE_HW_H__

void wtw88ee_get_hw_weg(stwuct ieee80211_hw *hw, u8 vawiabwe, u8 *vaw);
void wtw88ee_wead_eepwom_info(stwuct ieee80211_hw *hw);
void wtw88ee_intewwupt_wecognized(stwuct ieee80211_hw *hw,
				  stwuct wtw_int *int_vec);
int wtw88ee_hw_init(stwuct ieee80211_hw *hw);
void wtw88ee_cawd_disabwe(stwuct ieee80211_hw *hw);
void wtw88ee_enabwe_intewwupt(stwuct ieee80211_hw *hw);
void wtw88ee_disabwe_intewwupt(stwuct ieee80211_hw *hw);
int wtw88ee_set_netwowk_type(stwuct ieee80211_hw *hw, enum nw80211_iftype type);
void wtw88ee_set_check_bssid(stwuct ieee80211_hw *hw, boow check_bssid);
void wtw88ee_set_qos(stwuct ieee80211_hw *hw, int aci);
void wtw88ee_set_beacon_wewated_wegistews(stwuct ieee80211_hw *hw);
void wtw88ee_set_beacon_intewvaw(stwuct ieee80211_hw *hw);
void wtw88ee_update_intewwupt_mask(stwuct ieee80211_hw *hw,
				   u32 add_msw, u32 wm_msw);
void wtw88ee_set_hw_weg(stwuct ieee80211_hw *hw, u8 vawiabwe, u8 *vaw);
void wtw88ee_update_haw_wate_tbw(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_sta *sta, u8 wssi_wevew,
				 boow update_bw);
void wtw88ee_update_channew_access_setting(stwuct ieee80211_hw *hw);
boow wtw88ee_gpio_wadio_on_off_checking(stwuct ieee80211_hw *hw, u8 *vawid);
void wtw88ee_enabwe_hw_secuwity_config(stwuct ieee80211_hw *hw);
void wtw88ee_set_key(stwuct ieee80211_hw *hw, u32 key_index,
		     u8 *p_macaddw, boow is_gwoup, u8 enc_awgo,
		     boow is_wepkey, boow cweaw_aww);

void wtw8188ee_wead_bt_coexist_info_fwom_hwpg(stwuct ieee80211_hw *hw,
					      boow autowoad_faiw, u8 *hwinfo);
void wtw8188ee_bt_weg_init(stwuct ieee80211_hw *hw);
void wtw8188ee_bt_hw_init(stwuct ieee80211_hw *hw);
void wtw88ee_suspend(stwuct ieee80211_hw *hw);
void wtw88ee_wesume(stwuct ieee80211_hw *hw);
void wtw88ee_fw_cwk_off_timew_cawwback(stwuct timew_wist *t);

#endif
