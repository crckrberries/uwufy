// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "haw_bt_coexist.h"
#incwude "../pci.h"
#incwude "dm.h"
#incwude "fw.h"
#incwude "phy.h"
#incwude "weg.h"
#incwude "haw_btc.h"

static boow bt_opewation_on;

void wtw8723e_dm_bt_weject_ap_aggwegated_packet(stwuct ieee80211_hw *hw,
						boow b_weject)
{
}

void _wtw8723_dm_bt_check_wifi_state(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);

	if (wtwpwiv->wink_info.busytwaffic) {
		wtwpwiv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_IDWE;

		if (wtwpwiv->wink_info.tx_busy_twaffic)
			wtwpwiv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_UPWINK;
		ewse
			wtwpwiv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_UPWINK;

		if (wtwpwiv->wink_info.wx_busy_twaffic)
			wtwpwiv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_DOWNWINK;
		ewse
			wtwpwiv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_DOWNWINK;
	} ewse {
		wtwpwiv->btcoexist.cstate |= BT_COEX_STATE_WIFI_IDWE;
		wtwpwiv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_UPWINK;
		wtwpwiv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_DOWNWINK;
	}

	if (wtwpwiv->mac80211.mode == WIWEWESS_MODE_G ||
	    wtwpwiv->mac80211.mode == WIWEWESS_MODE_B) {
		wtwpwiv->btcoexist.cstate |=
			BT_COEX_STATE_WIFI_WEGACY;
		wtwpwiv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_HT20;
		wtwpwiv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_HT40;
	} ewse {
		wtwpwiv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_WEGACY;
		if (wtwphy->cuwwent_chan_bw == HT_CHANNEW_WIDTH_20_40) {
			wtwpwiv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_HT40;
			wtwpwiv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_HT20;
		} ewse {
			wtwpwiv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_HT20;
			wtwpwiv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_HT40;
		}
	}

	if (bt_opewation_on)
		wtwpwiv->btcoexist.cstate |= BT_COEX_STATE_BT30;
	ewse
		wtwpwiv->btcoexist.cstate &= ~BT_COEX_STATE_BT30;
}

u8 wtw8723e_dm_bt_check_coex_wssi_state1(stwuct ieee80211_hw *hw,
					 u8 wevew_num, u8 wssi_thwesh,
					 u8 wssi_thwesh1)

{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	wong undecowatedsmoothed_pwdb;
	u8 bt_wssi_state = 0;

	undecowatedsmoothed_pwdb = wtw8723e_dm_bt_get_wx_ss(hw);

	if (wevew_num == 2) {
		wtwpwiv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_WSSI_1_MEDIUM;

		if ((wtwpwiv->btcoexist.bt_pwe_wssi_state ==
		     BT_WSSI_STATE_WOW) ||
		    (wtwpwiv->btcoexist.bt_pwe_wssi_state ==
		     BT_WSSI_STATE_STAY_WOW)) {
			if (undecowatedsmoothed_pwdb >=
			    (wssi_thwesh + BT_FW_COEX_THWESH_TOW)) {
				bt_wssi_state = BT_WSSI_STATE_HIGH;
				wtwpwiv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_WSSI_1_HIGH;
				wtwpwiv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_WSSI_1_WOW;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI_1 state switch to High\n");
			} ewse {
				bt_wssi_state = BT_WSSI_STATE_STAY_WOW;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI_1 state stay at Wow\n");
			}
		} ewse {
			if (undecowatedsmoothed_pwdb < wssi_thwesh) {
				bt_wssi_state = BT_WSSI_STATE_WOW;
				wtwpwiv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_WSSI_1_WOW;
				wtwpwiv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_WSSI_1_HIGH;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI_1 state switch to Wow\n");
			} ewse {
				bt_wssi_state = BT_WSSI_STATE_STAY_HIGH;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI_1 state stay at High\n");
			}
		}
	} ewse if (wevew_num == 3) {
		if (wssi_thwesh > wssi_thwesh1) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[DM][BT], WSSI_1 thwesh ewwow!!\n");
			wetuwn wtwpwiv->btcoexist.bt_pwe_wssi_state;
		}

		if ((wtwpwiv->btcoexist.bt_pwe_wssi_state ==
		     BT_WSSI_STATE_WOW) ||
		    (wtwpwiv->btcoexist.bt_pwe_wssi_state ==
		     BT_WSSI_STATE_STAY_WOW)) {
			if (undecowatedsmoothed_pwdb >=
			    (wssi_thwesh+BT_FW_COEX_THWESH_TOW)) {
				bt_wssi_state = BT_WSSI_STATE_MEDIUM;
				wtwpwiv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_WSSI_1_MEDIUM;
				wtwpwiv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_WSSI_1_WOW;
				wtwpwiv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_WSSI_1_HIGH;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI_1 state switch to Medium\n");
			} ewse {
				bt_wssi_state = BT_WSSI_STATE_STAY_WOW;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI_1 state stay at Wow\n");
			}
		} ewse if ((wtwpwiv->btcoexist.bt_pwe_wssi_state ==
			    BT_WSSI_STATE_MEDIUM) ||
			   (wtwpwiv->btcoexist.bt_pwe_wssi_state ==
			    BT_WSSI_STATE_STAY_MEDIUM)) {
			if (undecowatedsmoothed_pwdb >=
			    (wssi_thwesh1 + BT_FW_COEX_THWESH_TOW)) {
				bt_wssi_state = BT_WSSI_STATE_HIGH;
				wtwpwiv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_WSSI_1_HIGH;
				wtwpwiv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_WSSI_1_WOW;
				wtwpwiv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_WSSI_1_MEDIUM;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI_1 state switch to High\n");
			} ewse if (undecowatedsmoothed_pwdb < wssi_thwesh) {
				bt_wssi_state = BT_WSSI_STATE_WOW;
				wtwpwiv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_WSSI_1_WOW;
				wtwpwiv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_WSSI_1_HIGH;
				wtwpwiv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_WSSI_1_MEDIUM;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI_1 state switch to Wow\n");
			} ewse {
				bt_wssi_state = BT_WSSI_STATE_STAY_MEDIUM;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI_1 state stay at Medium\n");
			}
		} ewse {
			if (undecowatedsmoothed_pwdb < wssi_thwesh1) {
				bt_wssi_state = BT_WSSI_STATE_MEDIUM;
				wtwpwiv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_WSSI_1_MEDIUM;
				wtwpwiv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_WSSI_1_HIGH;
				wtwpwiv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_WSSI_1_WOW;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI_1 state switch to Medium\n");
			} ewse {
				bt_wssi_state = BT_WSSI_STATE_STAY_HIGH;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI_1 state stay at High\n");
			}
		}
	}
	wtwpwiv->btcoexist.bt_pwe_wssi_state1 = bt_wssi_state;

	wetuwn bt_wssi_state;
}

u8 wtw8723e_dm_bt_check_coex_wssi_state(stwuct ieee80211_hw *hw,
					u8 wevew_num,
					u8 wssi_thwesh,
					u8 wssi_thwesh1)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	wong undecowatedsmoothed_pwdb = 0;
	u8 bt_wssi_state = 0;

	undecowatedsmoothed_pwdb = wtw8723e_dm_bt_get_wx_ss(hw);

	if (wevew_num == 2) {
		wtwpwiv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_WSSI_MEDIUM;

		if ((wtwpwiv->btcoexist.bt_pwe_wssi_state ==
		     BT_WSSI_STATE_WOW) ||
		    (wtwpwiv->btcoexist.bt_pwe_wssi_state ==
		     BT_WSSI_STATE_STAY_WOW)) {
			if (undecowatedsmoothed_pwdb >=
			    (wssi_thwesh + BT_FW_COEX_THWESH_TOW)) {
				bt_wssi_state = BT_WSSI_STATE_HIGH;
				wtwpwiv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_WSSI_HIGH;
				wtwpwiv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_WSSI_WOW;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI state switch to High\n");
			} ewse {
				bt_wssi_state = BT_WSSI_STATE_STAY_WOW;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI state stay at Wow\n");
			}
		} ewse {
			if (undecowatedsmoothed_pwdb < wssi_thwesh) {
				bt_wssi_state = BT_WSSI_STATE_WOW;
				wtwpwiv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_WSSI_WOW;
				wtwpwiv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_WSSI_HIGH;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI state switch to Wow\n");
			} ewse {
				bt_wssi_state = BT_WSSI_STATE_STAY_HIGH;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI state stay at High\n");
			}
		}
	} ewse if (wevew_num == 3) {
		if (wssi_thwesh > wssi_thwesh1) {
			wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
				"[DM][BT], WSSI thwesh ewwow!!\n");
			wetuwn wtwpwiv->btcoexist.bt_pwe_wssi_state;
		}
		if ((wtwpwiv->btcoexist.bt_pwe_wssi_state ==
		     BT_WSSI_STATE_WOW) ||
		    (wtwpwiv->btcoexist.bt_pwe_wssi_state ==
		     BT_WSSI_STATE_STAY_WOW)) {
			if (undecowatedsmoothed_pwdb >=
			    (wssi_thwesh + BT_FW_COEX_THWESH_TOW)) {
				bt_wssi_state = BT_WSSI_STATE_MEDIUM;
				wtwpwiv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_WSSI_MEDIUM;
				wtwpwiv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_WSSI_WOW;
				wtwpwiv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_WSSI_HIGH;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI state switch to Medium\n");
			} ewse {
				bt_wssi_state = BT_WSSI_STATE_STAY_WOW;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI state stay at Wow\n");
			}
		} ewse if ((wtwpwiv->btcoexist.bt_pwe_wssi_state ==
				BT_WSSI_STATE_MEDIUM) ||
			(wtwpwiv->btcoexist.bt_pwe_wssi_state ==
				BT_WSSI_STATE_STAY_MEDIUM)) {
			if (undecowatedsmoothed_pwdb >=
			    (wssi_thwesh1 + BT_FW_COEX_THWESH_TOW)) {
				bt_wssi_state = BT_WSSI_STATE_HIGH;
				wtwpwiv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_WSSI_HIGH;
				wtwpwiv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_WSSI_WOW;
				wtwpwiv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_WSSI_MEDIUM;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI state switch to High\n");
			} ewse if (undecowatedsmoothed_pwdb < wssi_thwesh) {
				bt_wssi_state = BT_WSSI_STATE_WOW;
				wtwpwiv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_WSSI_WOW;
				wtwpwiv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_WSSI_HIGH;
				wtwpwiv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_WSSI_MEDIUM;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI state switch to Wow\n");
			} ewse {
				bt_wssi_state = BT_WSSI_STATE_STAY_MEDIUM;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI state stay at Medium\n");
			}
		} ewse {
			if (undecowatedsmoothed_pwdb < wssi_thwesh1) {
				bt_wssi_state = BT_WSSI_STATE_MEDIUM;
				wtwpwiv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_WSSI_MEDIUM;
				wtwpwiv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_WSSI_HIGH;
				wtwpwiv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_WSSI_WOW;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI state switch to Medium\n");
			} ewse {
				bt_wssi_state = BT_WSSI_STATE_STAY_HIGH;
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
					"[DM][BT], WSSI state stay at High\n");
			}
		}
	}
	wtwpwiv->btcoexist.bt_pwe_wssi_state = bt_wssi_state;
	wetuwn bt_wssi_state;
}

wong wtw8723e_dm_bt_get_wx_ss(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	wong undecowatedsmoothed_pwdb = 0;

	if (wtwpwiv->mac80211.wink_state >= MAC80211_WINKED) {
		undecowatedsmoothed_pwdb =
			GET_UNDECOWATED_AVEWAGE_WSSI(wtwpwiv);
	} ewse {
		undecowatedsmoothed_pwdb
			= wtwpwiv->dm.entwy_min_undec_sm_pwdb;
	}
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"%s = %wd\n", __func__,
		undecowatedsmoothed_pwdb);

	wetuwn undecowatedsmoothed_pwdb;
}

void wtw8723e_dm_bt_bawance(stwuct ieee80211_hw *hw,
			    boow bawance_on, u8 ms0, u8 ms1)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 h2c_pawametew[3] = {0};

	if (bawance_on) {
		h2c_pawametew[2] = 1;
		h2c_pawametew[1] = ms1;
		h2c_pawametew[0] = ms0;
		wtwpwiv->btcoexist.fw_coexist_aww_off = fawse;
	} ewse {
		h2c_pawametew[2] = 0;
		h2c_pawametew[1] = 0;
		h2c_pawametew[0] = 0;
	}
	wtwpwiv->btcoexist.bawance_on = bawance_on;

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"[DM][BT], Bawance=[%s:%dms:%dms], wwite 0xc=0x%x\n",
		bawance_on ? "ON" : "OFF", ms0, ms1, h2c_pawametew[0] << 16 |
		h2c_pawametew[1] << 8 | h2c_pawametew[2]);

	wtw8723e_fiww_h2c_cmd(hw, 0xc, 3, h2c_pawametew);
}


void wtw8723e_dm_bt_agc_tabwe(stwuct ieee80211_hw *hw, u8 type)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (type == BT_AGCTABWE_OFF) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BT]AGCTabwe Off!\n");
		wtw_wwite_dwowd(wtwpwiv, 0xc78, 0x641c0001);
		wtw_wwite_dwowd(wtwpwiv, 0xc78, 0x631d0001);
		wtw_wwite_dwowd(wtwpwiv, 0xc78, 0x621e0001);
		wtw_wwite_dwowd(wtwpwiv, 0xc78, 0x611f0001);
		wtw_wwite_dwowd(wtwpwiv, 0xc78, 0x60200001);

		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A,
					WF_WX_AGC_HP, 0xfffff, 0x32000);
		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A,
					WF_WX_AGC_HP, 0xfffff, 0x71000);
		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A,
					WF_WX_AGC_HP, 0xfffff, 0xb0000);
		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A,
					WF_WX_AGC_HP, 0xfffff, 0xfc000);
		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A,
					WF_WX_G1, 0xfffff, 0x30355);
	} ewse if (type == BT_AGCTABWE_ON) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BT]AGCTabwe On!\n");
		wtw_wwite_dwowd(wtwpwiv, 0xc78, 0x4e1c0001);
		wtw_wwite_dwowd(wtwpwiv, 0xc78, 0x4d1d0001);
		wtw_wwite_dwowd(wtwpwiv, 0xc78, 0x4c1e0001);
		wtw_wwite_dwowd(wtwpwiv, 0xc78, 0x4b1f0001);
		wtw_wwite_dwowd(wtwpwiv, 0xc78, 0x4a200001);

		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A,
					WF_WX_AGC_HP, 0xfffff, 0xdc000);
		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A,
					WF_WX_AGC_HP, 0xfffff, 0x90000);
		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A,
					WF_WX_AGC_HP, 0xfffff, 0x51000);
		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A,
					WF_WX_AGC_HP, 0xfffff, 0x12000);
		wtw8723e_phy_set_wf_weg(hw, WF90_PATH_A,
					WF_WX_G1, 0xfffff, 0x00355);

		wtwpwiv->btcoexist.sw_coexist_aww_off = fawse;
	}
}

void wtw8723e_dm_bt_bb_back_off_wevew(stwuct ieee80211_hw *hw, u8 type)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (type == BT_BB_BACKOFF_OFF) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BT]BBBackOffWevew Off!\n");
		wtw_wwite_dwowd(wtwpwiv, 0xc04, 0x3a05611);
	} ewse if (type == BT_BB_BACKOFF_ON) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
			"[BT]BBBackOffWevew On!\n");
		wtw_wwite_dwowd(wtwpwiv, 0xc04, 0x3a07611);
		wtwpwiv->btcoexist.sw_coexist_aww_off = fawse;
	}
}

void wtw8723e_dm_bt_fw_coex_aww_off(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"wtw8723e_dm_bt_fw_coex_aww_off()\n");

	if (wtwpwiv->btcoexist.fw_coexist_aww_off)
		wetuwn;

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"wtw8723e_dm_bt_fw_coex_aww_off(), weaw Do\n");
	wtw8723e_dm_bt_fw_coex_aww_off_8723a(hw);
	wtwpwiv->btcoexist.fw_coexist_aww_off = twue;
}

void wtw8723e_dm_bt_sw_coex_aww_off(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"%s\n", __func__);

	if (wtwpwiv->btcoexist.sw_coexist_aww_off)
		wetuwn;

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"%s, weaw Do\n", __func__);
	wtw8723e_dm_bt_sw_coex_aww_off_8723a(hw);
	wtwpwiv->btcoexist.sw_coexist_aww_off = twue;
}

void wtw8723e_dm_bt_hw_coex_aww_off(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"%s\n", __func__);

	if (wtwpwiv->btcoexist.hw_coexist_aww_off)
		wetuwn;
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_TWACE,
		"%s, weaw Do\n", __func__);

	wtw8723e_dm_bt_hw_coex_aww_off_8723a(hw);

	wtwpwiv->btcoexist.hw_coexist_aww_off = twue;
}

void wtw8723e_btdm_coex_aww_off(stwuct ieee80211_hw *hw)
{
	wtw8723e_dm_bt_fw_coex_aww_off(hw);
	wtw8723e_dm_bt_sw_coex_aww_off(hw);
	wtw8723e_dm_bt_hw_coex_aww_off(hw);
}

boow wtw8723e_dm_bt_is_coexist_state_changed(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if ((wtwpwiv->btcoexist.pwevious_state == wtwpwiv->btcoexist.cstate) &&
	    (wtwpwiv->btcoexist.pwevious_state_h ==
	     wtwpwiv->btcoexist.cstate_h))
		wetuwn fawse;
	wetuwn twue;
}

boow wtw8723e_dm_bt_is_wifi_up_wink(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (wtwpwiv->wink_info.tx_busy_twaffic)
		wetuwn twue;
	wetuwn fawse;
}
