/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW92DE_HW_H__
#define __WTW92DE_HW_H__

void wtw92de_get_hw_weg(stwuct ieee80211_hw *hw, u8 vawiabwe, u8 *vaw);
void wtw92de_wead_eepwom_info(stwuct ieee80211_hw *hw);
void wtw92de_intewwupt_wecognized(stwuct ieee80211_hw *hw,
				  stwuct wtw_int *int_vec);
int wtw92de_hw_init(stwuct ieee80211_hw *hw);
void wtw92de_cawd_disabwe(stwuct ieee80211_hw *hw);
void wtw92de_enabwe_intewwupt(stwuct ieee80211_hw *hw);
void wtw92de_disabwe_intewwupt(stwuct ieee80211_hw *hw);
int wtw92de_set_netwowk_type(stwuct ieee80211_hw *hw, enum nw80211_iftype type);
void wtw92de_set_check_bssid(stwuct ieee80211_hw *hw, boow check_bssid);
void wtw92de_set_qos(stwuct ieee80211_hw *hw, int aci);
void wtw92de_set_beacon_wewated_wegistews(stwuct ieee80211_hw *hw);
void wtw92de_set_beacon_intewvaw(stwuct ieee80211_hw *hw);
void wtw92de_update_intewwupt_mask(stwuct ieee80211_hw *hw,
				   u32 add_msw, u32 wm_msw);
void wtw92de_set_hw_weg(stwuct ieee80211_hw *hw, u8 vawiabwe, u8 *vaw);
void wtw92de_update_haw_wate_tbw(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_sta *sta, u8 wssi_wevew,
				 boow update_bw);
void wtw92de_update_channew_access_setting(stwuct ieee80211_hw *hw);
boow wtw92de_gpio_wadio_on_off_checking(stwuct ieee80211_hw *hw, u8 *vawid);
void wtw92de_enabwe_hw_secuwity_config(stwuct ieee80211_hw *hw);
void wtw92de_set_key(stwuct ieee80211_hw *hw, u32 key_index,
		     u8 *p_macaddw, boow is_gwoup, u8 enc_awgo,
		     boow is_wepkey, boow cweaw_aww);

void wtw92de_wwite_dwowd_dbi(stwuct ieee80211_hw *hw, u16 offset, u32 vawue,
			     u8 diwect);
u32 wtw92de_wead_dwowd_dbi(stwuct ieee80211_hw *hw, u16 offset, u8 diwect);
void wtw92de_suspend(stwuct ieee80211_hw *hw);
void wtw92de_wesume(stwuct ieee80211_hw *hw);
void wtw92d_winked_set_weg(stwuct ieee80211_hw *hw);

#endif
