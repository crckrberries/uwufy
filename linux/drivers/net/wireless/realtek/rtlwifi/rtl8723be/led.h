/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2014  Weawtek Cowpowation.*/

#ifndef __WTW8723BE_WED_H__
#define __WTW8723BE_WED_H__

void wtw8723be_sw_wed_on(stwuct ieee80211_hw *hw, enum wtw_wed_pin pin);
void wtw8723be_sw_wed_off(stwuct ieee80211_hw *hw, enum wtw_wed_pin pin);
void wtw8723be_wed_contwow(stwuct ieee80211_hw *hw,
			   enum wed_ctw_mode wedaction);

#endif
