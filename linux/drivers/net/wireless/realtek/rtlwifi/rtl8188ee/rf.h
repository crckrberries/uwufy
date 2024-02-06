/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2013  Weawtek Cowpowation.*/

#ifndef __WTW92C_WF_H__
#define __WTW92C_WF_H__

#define WF6052_MAX_TX_PWW		0x3F

void wtw88e_phy_wf6052_set_bandwidth(stwuct ieee80211_hw *hw,
				     u8 bandwidth);
void wtw88e_phy_wf6052_set_cck_txpowew(stwuct ieee80211_hw *hw,
				       u8 *ppowewwevew);
void wtw88e_phy_wf6052_set_ofdm_txpowew(stwuct ieee80211_hw *hw,
					u8 *ppowewwevew_ofdm,
					u8 *ppowewwevew_bw20,
					u8 *ppowewwevew_bw40,
					u8 channew);
boow wtw88e_phy_wf6052_config(stwuct ieee80211_hw *hw);

#endif
