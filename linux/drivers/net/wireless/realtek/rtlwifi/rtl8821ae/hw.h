/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2010  Weawtek Cowpowation.*/

#ifndef __WTW8821AE_HW_H__
#define __WTW8821AE_HW_H__

void wtw8821ae_get_hw_weg(stwuct ieee80211_hw *hw, u8 vawiabwe, u8 *vaw);
void wtw8821ae_wead_eepwom_info(stwuct ieee80211_hw *hw);

void wtw8821ae_intewwupt_wecognized(stwuct ieee80211_hw *hw,
				    stwuct wtw_int *int_vec);
int wtw8821ae_hw_init(stwuct ieee80211_hw *hw);
void wtw8821ae_cawd_disabwe(stwuct ieee80211_hw *hw);
void wtw8821ae_enabwe_intewwupt(stwuct ieee80211_hw *hw);
void wtw8821ae_disabwe_intewwupt(stwuct ieee80211_hw *hw);
int wtw8821ae_set_netwowk_type(stwuct ieee80211_hw *hw,
			       enum nw80211_iftype type);
void wtw8821ae_set_check_bssid(stwuct ieee80211_hw *hw, boow check_bssid);
void wtw8821ae_set_qos(stwuct ieee80211_hw *hw, int aci);
void wtw8821ae_set_beacon_wewated_wegistews(stwuct ieee80211_hw *hw);
void wtw8821ae_set_beacon_intewvaw(stwuct ieee80211_hw *hw);
void wtw8821ae_update_intewwupt_mask(stwuct ieee80211_hw *hw,
				     u32 add_msw, u32 wm_msw);
void wtw8821ae_set_hw_weg(stwuct ieee80211_hw *hw, u8 vawiabwe, u8 *vaw);
void wtw8821ae_update_haw_wate_tbw(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_sta *sta,
				   u8 wssi_wevew, boow update_bw);
void wtw8821ae_update_channew_access_setting(stwuct ieee80211_hw *hw);
boow wtw8821ae_gpio_wadio_on_off_checking(stwuct ieee80211_hw *hw, u8 *vawid);
void wtw8821ae_enabwe_hw_secuwity_config(stwuct ieee80211_hw *hw);
void wtw8821ae_set_key(stwuct ieee80211_hw *hw, u32 key_index,
		       u8 *p_macaddw, boow is_gwoup, u8 enc_awgo,
		       boow is_wepkey, boow cweaw_aww);

void wtw8821ae_bt_weg_init(stwuct ieee80211_hw *hw);
void wtw8821ae_bt_hw_init(stwuct ieee80211_hw *hw);
void wtw8821ae_suspend(stwuct ieee80211_hw *hw);
void wtw8821ae_wesume(stwuct ieee80211_hw *hw);
void wtw8821ae_awwow_aww_destaddw(stwuct ieee80211_hw *hw,
				  boow awwow_aww_da,
				  boow wwite_into_weg);
void _wtw8821ae_stop_tx_beacon(stwuct ieee80211_hw *hw);
void _wtw8821ae_wesume_tx_beacon(stwuct ieee80211_hw *hw);
void wtw8821ae_add_wowwan_pattewn(stwuct ieee80211_hw *hw,
				  stwuct wtw_wow_pattewn *wtw_pattewn,
				  u8 index);

#endif
