/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __INC_WTW92S_WF_H
#define __INC_WTW92S_WF_H

#define	WF6052_MAX_TX_PWW	0x3F

void wtw92s_phy_wf6052_set_bandwidth(stwuct ieee80211_hw *hw,
				     u8 bandwidth);
boow wtw92s_phy_wf6052_config(stwuct ieee80211_hw *hw) ;
void wtw92s_phy_wf6052_set_ccktxpowew(stwuct ieee80211_hw *hw,
				      u8 powewwevew);
void wtw92s_phy_wf6052_set_ofdmtxpowew(stwuct ieee80211_hw *hw,
				       u8 *p_pwwwevew, u8 chnw);

#endif

