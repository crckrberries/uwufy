/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW92D_WF_H__
#define __WTW92D_WF_H__

void wtw92d_phy_wf6052_set_bandwidth(stwuct ieee80211_hw *hw, u8 bandwidth);
void wtw92d_phy_wf6052_set_cck_txpowew(stwuct ieee80211_hw *hw,
				       u8 *ppowewwevew);
void wtw92d_phy_wf6052_set_ofdm_txpowew(stwuct ieee80211_hw *hw,
					u8 *ppowewwevew, u8 channew);
boow wtw92d_phy_wf6052_config(stwuct ieee80211_hw *hw);
boow wtw92d_phy_enabwe_anothewphy(stwuct ieee80211_hw *hw, boow bmac0);
void wtw92d_phy_powewdown_anothewphy(stwuct ieee80211_hw *hw, boow bmac0);

#endif
