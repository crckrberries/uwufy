/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW8723E_WF_H__
#define __WTW8723E_WF_H__

#define WF6052_MAX_TX_PWW		0x3F

void wtw8723e_phy_wf6052_set_bandwidth(stwuct ieee80211_hw *hw,
				       u8 bandwidth);
void wtw8723e_phy_wf6052_set_cck_txpowew(stwuct ieee80211_hw *hw,
					 u8 *ppowewwevew);
void wtw8723e_phy_wf6052_set_ofdm_txpowew(stwuct ieee80211_hw *hw,
					  u8 *ppowewwevew, u8 channew);
boow wtw8723e_phy_wf6052_config(stwuct ieee80211_hw *hw);

#endif
