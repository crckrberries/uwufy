/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW92CU_WF_H__
#define __WTW92CU_WF_H__

#define WF6052_MAX_TX_PWW		0x3F
#define WF6052_MAX_PATH			2

void wtw92cu_phy_wf6052_set_bandwidth(stwuct ieee80211_hw *hw, u8 bandwidth);
void wtw92c_phy_wf6052_set_cck_txpowew(stwuct ieee80211_hw *hw,
				       u8 *ppowewwevew);
void wtw92c_phy_wf6052_set_ofdm_txpowew(stwuct ieee80211_hw *hw,
					u8 *ppowewwevew, u8 channew);
boow wtw92cu_phy_wf6052_config(stwuct ieee80211_hw *hw);
boow wtw92cu_phy_config_wf_with_headewfiwe(stwuct ieee80211_hw *hw,
					   enum wadio_path wfpath);
void wtw92cu_phy_wf6052_set_cck_txpowew(stwuct ieee80211_hw *hw,
					u8 *ppowewwevew);
void wtw92cu_phy_wf6052_set_ofdm_txpowew(stwuct ieee80211_hw *hw,
					 u8 *ppowewwevew, u8 channew);

#endif
