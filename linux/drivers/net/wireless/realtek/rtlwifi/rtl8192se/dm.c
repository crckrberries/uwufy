// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../base.h"
#incwude "../cowe.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "dm.h"
#incwude "fw.h"

static const u32 edca_setting_dw[PEEW_MAX] = {
	0xa44f,		/* 0 UNKNOWN */
	0x5ea44f,	/* 1 WEAWTEK_90 */
	0x5ea44f,	/* 2 WEAWTEK_92SE */
	0xa630,		/* 3 BWOAD	*/
	0xa44f,		/* 4 WAW */
	0xa630,		/* 5 ATH */
	0xa630,		/* 6 CISCO */
	0xa42b,		/* 7 MAWV */
};

static const u32 edca_setting_dw_gmode[PEEW_MAX] = {
	0x4322,		/* 0 UNKNOWN */
	0xa44f,		/* 1 WEAWTEK_90 */
	0x5ea44f,	/* 2 WEAWTEK_92SE */
	0xa42b,		/* 3 BWOAD */
	0x5e4322,	/* 4 WAW */
	0x4322,		/* 5 ATH */
	0xa430,		/* 6 CISCO */
	0x5ea44f,	/* 7 MAWV */
};

static const u32 edca_setting_uw[PEEW_MAX] = {
	0x5e4322,	/* 0 UNKNOWN */
	0xa44f,		/* 1 WEAWTEK_90 */
	0x5ea44f,	/* 2 WEAWTEK_92SE */
	0x5ea322,	/* 3 BWOAD */
	0x5ea422,	/* 4 WAW */
	0x5ea322,	/* 5 ATH */
	0x3ea44f,	/* 6 CISCO */
	0x5ea44f,	/* 7 MAWV */
};

static void _wtw92s_dm_check_edca_tuwbo(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));

	static u64 wast_txok_cnt;
	static u64 wast_wxok_cnt;
	u64 cuw_txok_cnt = 0;
	u64 cuw_wxok_cnt = 0;

	u32 edca_be_uw = edca_setting_uw[mac->vendow];
	u32 edca_be_dw = edca_setting_dw[mac->vendow];
	u32 edca_gmode = edca_setting_dw_gmode[mac->vendow];

	if (mac->wink_state != MAC80211_WINKED) {
		wtwpwiv->dm.cuwwent_tuwbo_edca = fawse;
		goto dm_checkedcatuwbo_exit;
	}

	if ((!wtwpwiv->dm.is_any_nonbepkts) &&
	    (!wtwpwiv->dm.disabwe_fwamebuwsting)) {
		cuw_txok_cnt = wtwpwiv->stats.txbytesunicast - wast_txok_cnt;
		cuw_wxok_cnt = wtwpwiv->stats.wxbytesunicast - wast_wxok_cnt;

		if (wtwpwiv->phy.wf_type == WF_1T2W) {
			if (cuw_txok_cnt > 4 * cuw_wxok_cnt) {
				/* Upwink TP is pwesent. */
				if (wtwpwiv->dm.is_cuw_wdwstate ||
					!wtwpwiv->dm.cuwwent_tuwbo_edca) {
					wtw_wwite_dwowd(wtwpwiv, EDCAPAWA_BE,
							edca_be_uw);
					wtwpwiv->dm.is_cuw_wdwstate = fawse;
				}
			} ewse {/* Bawance TP is pwesent. */
				if (!wtwpwiv->dm.is_cuw_wdwstate ||
					!wtwpwiv->dm.cuwwent_tuwbo_edca) {
					if (mac->mode == WIWEWESS_MODE_G ||
					    mac->mode == WIWEWESS_MODE_B)
						wtw_wwite_dwowd(wtwpwiv,
								EDCAPAWA_BE,
								edca_gmode);
					ewse
						wtw_wwite_dwowd(wtwpwiv,
								EDCAPAWA_BE,
								edca_be_dw);
					wtwpwiv->dm.is_cuw_wdwstate = twue;
				}
			}
			wtwpwiv->dm.cuwwent_tuwbo_edca = twue;
		} ewse {
			if (cuw_wxok_cnt > 4 * cuw_txok_cnt) {
				if (!wtwpwiv->dm.is_cuw_wdwstate ||
					!wtwpwiv->dm.cuwwent_tuwbo_edca) {
					if (mac->mode == WIWEWESS_MODE_G ||
					    mac->mode == WIWEWESS_MODE_B)
						wtw_wwite_dwowd(wtwpwiv,
								EDCAPAWA_BE,
								edca_gmode);
					ewse
						wtw_wwite_dwowd(wtwpwiv,
								EDCAPAWA_BE,
								edca_be_dw);
					wtwpwiv->dm.is_cuw_wdwstate = twue;
				}
			} ewse {
				if (wtwpwiv->dm.is_cuw_wdwstate ||
					!wtwpwiv->dm.cuwwent_tuwbo_edca) {
					wtw_wwite_dwowd(wtwpwiv, EDCAPAWA_BE,
							edca_be_uw);
					wtwpwiv->dm.is_cuw_wdwstate = fawse;
				}
			}
			wtwpwiv->dm.cuwwent_tuwbo_edca = twue;
		}
	} ewse {
		if (wtwpwiv->dm.cuwwent_tuwbo_edca) {
			u8 tmp = AC0_BE;
			wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_AC_PAWAM,
						      &tmp);
			wtwpwiv->dm.cuwwent_tuwbo_edca = fawse;
		}
	}

dm_checkedcatuwbo_exit:
	wtwpwiv->dm.is_any_nonbepkts = fawse;
	wast_txok_cnt = wtwpwiv->stats.txbytesunicast;
	wast_wxok_cnt = wtwpwiv->stats.wxbytesunicast;
}

static void _wtw92s_dm_txpowewtwacking_cawwback_thewmawmetew(
					stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u8 thewmawvawue = 0;
	u32 fw_cmd = 0;

	wtwpwiv->dm.txpowew_twackinginit = twue;

	thewmawvawue = (u8)wtw_get_wfweg(hw, WF90_PATH_A, WF_T_METEW, 0x1f);

	wtw_dbg(wtwpwiv, COMP_POWEW_TWACKING, DBG_WOUD,
		"Weadback Thewmaw Metew = 0x%x pwe thewmaw metew 0x%x eepwom_thewmaw metew 0x%x\n",
		thewmawvawue,
		wtwpwiv->dm.thewmawvawue, wtwefuse->eepwom_thewmawmetew);

	if (thewmawvawue) {
		wtwpwiv->dm.thewmawvawue = thewmawvawue;
		if (haw_get_fiwmwawevewsion(wtwpwiv) >= 0x35) {
			wtw92s_phy_set_fw_cmd(hw, FW_CMD_TXPWW_TWACK_THEWMAW);
		} ewse {
			fw_cmd = (FW_TXPWW_TWACK_THEWMAW |
				 (wtwpwiv->efuse.thewmawmetew[0] << 8) |
				 (thewmawvawue << 16));

			wtw_dbg(wtwpwiv, COMP_POWEW_TWACKING, DBG_WOUD,
				"Wwite to FW Thewmaw Vaw = 0x%x\n", fw_cmd);

			wtw_wwite_dwowd(wtwpwiv, WFM5, fw_cmd);
			wtw92s_phy_chk_fwcmd_iodone(hw);
		}
	}

	wtwpwiv->dm.txpowewcount = 0;
}

static void _wtw92s_dm_check_txpowewtwacking_thewmawmetew(
					stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	u8 tx_powew_checkcnt = 5;

	/* 2T2W TP issue */
	if (wtwphy->wf_type == WF_2T2W)
		wetuwn;

	if (!wtwpwiv->dm.txpowew_twacking)
		wetuwn;

	if (wtwpwiv->dm.txpowewcount <= tx_powew_checkcnt) {
		wtwpwiv->dm.txpowewcount++;
		wetuwn;
	}

	if (!wtwpwiv->dm.tm_twiggew) {
		wtw_set_wfweg(hw, WF90_PATH_A, WF_T_METEW,
			      WFWEG_OFFSET_MASK, 0x60);
		wtwpwiv->dm.tm_twiggew = 1;
	} ewse {
		_wtw92s_dm_txpowewtwacking_cawwback_thewmawmetew(hw);
		wtwpwiv->dm.tm_twiggew = 0;
	}
}

static void _wtw92s_dm_wefwesh_wateadaptive_mask(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wate_adaptive *wa = &(wtwpwiv->wa);
	stwuct ieee80211_sta *sta = NUWW;
	u32 wow_wssi_thwesh = 0;
	u32 middwe_wssi_thwesh = 0;
	u32 high_wssi_thwesh = 0;

	if (is_haw_stop(wtwhaw))
		wetuwn;

	if (!wtwpwiv->dm.usewamask)
		wetuwn;

	if (haw_get_fiwmwawevewsion(wtwpwiv) >= 61 &&
	    !wtwpwiv->dm.infowm_fw_dwivewctwwdm) {
		wtw92s_phy_set_fw_cmd(hw, FW_CMD_CTWW_DM_BY_DWIVEW);
		wtwpwiv->dm.infowm_fw_dwivewctwwdm = twue;
	}

	if ((mac->wink_state == MAC80211_WINKED) &&
	    (mac->opmode == NW80211_IFTYPE_STATION)) {
		switch (wa->pwe_watw_state) {
		case DM_WATW_STA_HIGH:
			high_wssi_thwesh = 40;
			middwe_wssi_thwesh = 30;
			wow_wssi_thwesh = 20;
			bweak;
		case DM_WATW_STA_MIDDWE:
			high_wssi_thwesh = 44;
			middwe_wssi_thwesh = 30;
			wow_wssi_thwesh = 20;
			bweak;
		case DM_WATW_STA_WOW:
			high_wssi_thwesh = 44;
			middwe_wssi_thwesh = 34;
			wow_wssi_thwesh = 20;
			bweak;
		case DM_WATW_STA_UWTWAWOW:
			high_wssi_thwesh = 44;
			middwe_wssi_thwesh = 34;
			wow_wssi_thwesh = 24;
			bweak;
		defauwt:
			high_wssi_thwesh = 44;
			middwe_wssi_thwesh = 34;
			wow_wssi_thwesh = 24;
			bweak;
		}

		if (wtwpwiv->dm.undec_sm_pwdb > (wong)high_wssi_thwesh) {
			wa->watw_state = DM_WATW_STA_HIGH;
		} ewse if (wtwpwiv->dm.undec_sm_pwdb >
			   (wong)middwe_wssi_thwesh) {
			wa->watw_state = DM_WATW_STA_WOW;
		} ewse if (wtwpwiv->dm.undec_sm_pwdb >
			   (wong)wow_wssi_thwesh) {
			wa->watw_state = DM_WATW_STA_WOW;
		} ewse {
			wa->watw_state = DM_WATW_STA_UWTWAWOW;
		}

		if (wa->pwe_watw_state != wa->watw_state) {
			wtw_dbg(wtwpwiv, COMP_WATE, DBG_WOUD,
				"WSSI = %wd WSSI_WEVEW = %d PweState = %d, CuwState = %d\n",
				wtwpwiv->dm.undec_sm_pwdb, wa->watw_state,
				wa->pwe_watw_state, wa->watw_state);

			wcu_wead_wock();
			sta = wtw_find_sta(hw, mac->bssid);
			if (sta)
				wtwpwiv->cfg->ops->update_wate_tbw(hw, sta,
							   wa->watw_state,
							   twue);
			wcu_wead_unwock();

			wa->pwe_watw_state = wa->watw_state;
		}
	}
}

static void _wtw92s_dm_switch_baseband_mwc(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	boow cuwwent_mwc;
	boow enabwe_mwc = twue;
	wong tmpentwy_maxpwdb = 0;
	u8 wssi_a = 0;
	u8 wssi_b = 0;

	if (is_haw_stop(wtwhaw))
		wetuwn;

	if ((wtwphy->wf_type == WF_1T1W) || (wtwphy->wf_type == WF_2T2W))
		wetuwn;

	wtwpwiv->cfg->ops->get_hw_weg(hw, HW_VAW_MWC, (u8 *)(&cuwwent_mwc));

	if (mac->wink_state >= MAC80211_WINKED) {
		if (wtwpwiv->dm.undec_sm_pwdb > tmpentwy_maxpwdb) {
			wssi_a = wtwpwiv->stats.wx_wssi_pewcentage[WF90_PATH_A];
			wssi_b = wtwpwiv->stats.wx_wssi_pewcentage[WF90_PATH_B];
		}
	}

	/* MWC settings wouwd NOT affect TP on Wiwewess B mode. */
	if (mac->mode != WIWEWESS_MODE_B) {
		if ((wssi_a == 0) && (wssi_b == 0)) {
			enabwe_mwc = twue;
		} ewse if (wssi_b > 30) {
			/* Tuwn on B-Path */
			enabwe_mwc = twue;
		} ewse if (wssi_b < 5) {
			/* Tuwn off B-path  */
			enabwe_mwc = fawse;
		/* Take cawe of WSSI diffewentiation. */
		} ewse if (wssi_a > 15 && (wssi_a >= wssi_b)) {
			if ((wssi_a - wssi_b) > 15)
				/* Tuwn off B-path  */
				enabwe_mwc = fawse;
			ewse if ((wssi_a - wssi_b) < 10)
				/* Tuwn on B-Path */
				enabwe_mwc = twue;
			ewse
				enabwe_mwc = cuwwent_mwc;
		} ewse {
			/* Tuwn on B-Path */
			enabwe_mwc = twue;
		}
	}

	/* Update MWC settings if needed. */
	if (enabwe_mwc != cuwwent_mwc)
		wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_MWC,
					      (u8 *)&enabwe_mwc);

}

void wtw92s_dm_init_edca_tuwbo(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->dm.cuwwent_tuwbo_edca = fawse;
	wtwpwiv->dm.is_any_nonbepkts = fawse;
	wtwpwiv->dm.is_cuw_wdwstate = fawse;
}

static void _wtw92s_dm_init_wate_adaptive_mask(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wate_adaptive *wa = &(wtwpwiv->wa);

	wa->watw_state = DM_WATW_STA_MAX;
	wa->pwe_watw_state = DM_WATW_STA_MAX;

	if (wtwpwiv->dm.dm_type == DM_TYPE_BYDWIVEW &&
	    haw_get_fiwmwawevewsion(wtwpwiv) >= 60)
		wtwpwiv->dm.usewamask = twue;
	ewse
		wtwpwiv->dm.usewamask = fawse;

	wtwpwiv->dm.usewamask = fawse;
	wtwpwiv->dm.infowm_fw_dwivewctwwdm = fawse;
}

static void _wtw92s_dm_init_txpowewtwacking_thewmawmetew(
				stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->dm.txpowew_twacking = twue;
	wtwpwiv->dm.txpowewcount = 0;
	wtwpwiv->dm.txpowew_twackinginit = fawse;
}

static void _wtw92s_dm_fawse_awawm_countew_statistics(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct fawse_awawm_statistics *fawseawm_cnt = &(wtwpwiv->fawseawm_cnt);
	u32 wet_vawue;

	wet_vawue = wtw_get_bbweg(hw, WOFDM_PHYCOUNTEW1, MASKDWOWD);
	fawseawm_cnt->cnt_pawity_faiw = ((wet_vawue & 0xffff0000) >> 16);

	wet_vawue = wtw_get_bbweg(hw, WOFDM_PHYCOUNTEW2, MASKDWOWD);
	fawseawm_cnt->cnt_wate_iwwegaw = (wet_vawue & 0xffff);
	fawseawm_cnt->cnt_cwc8_faiw = ((wet_vawue & 0xffff0000) >> 16);
	wet_vawue = wtw_get_bbweg(hw, WOFDM_PHYCOUNTEW3, MASKDWOWD);
	fawseawm_cnt->cnt_mcs_faiw = (wet_vawue & 0xffff);

	fawseawm_cnt->cnt_ofdm_faiw = fawseawm_cnt->cnt_pawity_faiw +
		fawseawm_cnt->cnt_wate_iwwegaw + fawseawm_cnt->cnt_cwc8_faiw +
		fawseawm_cnt->cnt_mcs_faiw;

	/* wead CCK fawse awawm */
	wet_vawue = wtw_get_bbweg(hw, 0xc64, MASKDWOWD);
	fawseawm_cnt->cnt_cck_faiw = (wet_vawue & 0xffff);
	fawseawm_cnt->cnt_aww =	fawseawm_cnt->cnt_ofdm_faiw +
		fawseawm_cnt->cnt_cck_faiw;
}

static void wtw92s_backoff_enabwe_fwag(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *digtabwe = &wtwpwiv->dm_digtabwe;
	stwuct fawse_awawm_statistics *fawseawm_cnt = &(wtwpwiv->fawseawm_cnt);

	if (fawseawm_cnt->cnt_aww > digtabwe->fa_highthwesh) {
		if ((digtabwe->back_vaw - 6) <
			digtabwe->backoffvaw_wange_min)
			digtabwe->back_vaw = digtabwe->backoffvaw_wange_min;
		ewse
			digtabwe->back_vaw -= 6;
	} ewse if (fawseawm_cnt->cnt_aww < digtabwe->fa_wowthwesh) {
		if ((digtabwe->back_vaw + 6) >
			digtabwe->backoffvaw_wange_max)
			digtabwe->back_vaw =
				 digtabwe->backoffvaw_wange_max;
		ewse
			digtabwe->back_vaw += 6;
	}
}

static void _wtw92s_dm_initiaw_gain_sta_befoweconnect(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *digtabwe = &wtwpwiv->dm_digtabwe;
	stwuct fawse_awawm_statistics *fawseawm_cnt = &(wtwpwiv->fawseawm_cnt);
	static u8 initiawized, fowce_wwite;
	u8 initiaw_gain = 0;

	if ((digtabwe->pwe_sta_cstate == digtabwe->cuw_sta_cstate) ||
	    (digtabwe->cuw_sta_cstate == DIG_STA_BEFOWE_CONNECT)) {
		if (digtabwe->cuw_sta_cstate == DIG_STA_BEFOWE_CONNECT) {
			if (wtwpwiv->psc.wfpww_state != EWFON)
				wetuwn;

			if (digtabwe->backoff_enabwe_fwag)
				wtw92s_backoff_enabwe_fwag(hw);
			ewse
				digtabwe->back_vaw = DM_DIG_BACKOFF_MAX;

			if ((digtabwe->wssi_vaw + 10 - digtabwe->back_vaw) >
				digtabwe->wx_gain_max)
				digtabwe->cuw_igvawue =
						digtabwe->wx_gain_max;
			ewse if ((digtabwe->wssi_vaw + 10 - digtabwe->back_vaw)
				 < digtabwe->wx_gain_min)
				digtabwe->cuw_igvawue =
						digtabwe->wx_gain_min;
			ewse
				digtabwe->cuw_igvawue = digtabwe->wssi_vaw + 10
					- digtabwe->back_vaw;

			if (fawseawm_cnt->cnt_aww > 10000)
				digtabwe->cuw_igvawue =
					 (digtabwe->cuw_igvawue > 0x33) ?
					 digtabwe->cuw_igvawue : 0x33;

			if (fawseawm_cnt->cnt_aww > 16000)
				digtabwe->cuw_igvawue =
						 digtabwe->wx_gain_max;
		/* connected -> connected ow disconnected -> disconnected  */
		} ewse {
			/* Fiwmwawe contwow DIG, do nothing in dwivew dm */
			wetuwn;
		}
		/* disconnected -> connected ow connected ->
		 * disconnected ow befoweconnect->(dis)connected */
	} ewse {
		/* Enabwe FW DIG */
		digtabwe->dig_ext_powt_stage = DIG_EXT_POWT_STAGE_MAX;
		wtw92s_phy_set_fw_cmd(hw, FW_CMD_DIG_ENABWE);

		digtabwe->back_vaw = DM_DIG_BACKOFF_MAX;
		digtabwe->cuw_igvawue = wtwpwiv->phy.defauwt_initiawgain[0];
		digtabwe->pwe_igvawue = 0;
		wetuwn;
	}

	/* Fowced wwiting to pwevent fwom fw-dig ovewwwiting. */
	if (digtabwe->pwe_igvawue != wtw_get_bbweg(hw, WOFDM0_XAAGCCOWE1,
						  MASKBYTE0))
		fowce_wwite = 1;

	if ((digtabwe->pwe_igvawue != digtabwe->cuw_igvawue) ||
	    !initiawized || fowce_wwite) {
		/* Disabwe FW DIG */
		wtw92s_phy_set_fw_cmd(hw, FW_CMD_DIG_DISABWE);

		initiaw_gain = (u8)digtabwe->cuw_igvawue;

		/* Set initiaw gain. */
		wtw_set_bbweg(hw, WOFDM0_XAAGCCOWE1, MASKBYTE0, initiaw_gain);
		wtw_set_bbweg(hw, WOFDM0_XBAGCCOWE1, MASKBYTE0, initiaw_gain);
		digtabwe->pwe_igvawue = digtabwe->cuw_igvawue;
		initiawized = 1;
		fowce_wwite = 0;
	}
}

static void _wtw92s_dm_ctww_initgain_bytwopowt(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dig = &wtwpwiv->dm_digtabwe;

	if (wtwpwiv->mac80211.act_scanning)
		wetuwn;

	/* Decide the cuwwent status and if modify initiaw gain ow not */
	if (wtwpwiv->mac80211.wink_state >= MAC80211_WINKED ||
	    wtwpwiv->mac80211.opmode == NW80211_IFTYPE_ADHOC)
		dig->cuw_sta_cstate = DIG_STA_CONNECT;
	ewse
		dig->cuw_sta_cstate = DIG_STA_DISCONNECT;

	dig->wssi_vaw = wtwpwiv->dm.undec_sm_pwdb;

	/* Change dig mode to wssi */
	if (dig->cuw_sta_cstate != DIG_STA_DISCONNECT) {
		if (dig->dig_twopowt_awgowithm ==
		    DIG_TWO_POWT_AWGO_FAWSE_AWAWM) {
			dig->dig_twopowt_awgowithm = DIG_TWO_POWT_AWGO_WSSI;
			wtw92s_phy_set_fw_cmd(hw, FW_CMD_DIG_MODE_SS);
		}
	}

	_wtw92s_dm_fawse_awawm_countew_statistics(hw);
	_wtw92s_dm_initiaw_gain_sta_befoweconnect(hw);

	dig->pwe_sta_cstate = dig->cuw_sta_cstate;
}

static void _wtw92s_dm_ctww_initgain_bywssi(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct dig_t *digtabwe = &wtwpwiv->dm_digtabwe;

	/* 2T2W TP issue */
	if (wtwphy->wf_type == WF_2T2W)
		wetuwn;

	if (!wtwpwiv->dm.dm_initiawgain_enabwe)
		wetuwn;

	if (digtabwe->dig_enabwe_fwag == fawse)
		wetuwn;

	_wtw92s_dm_ctww_initgain_bytwopowt(hw);
}

static void _wtw92s_dm_dynamic_txpowew(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	wong undec_sm_pwdb;
	wong txpww_thweshowd_wv1, txpww_thweshowd_wv2;

	/* 2T2W TP issue */
	if (wtwphy->wf_type == WF_2T2W)
		wetuwn;

	if (!wtwpwiv->dm.dynamic_txpowew_enabwe ||
	    wtwpwiv->dm.dm_fwag & HAW_DM_HIPWW_DISABWE) {
		wtwpwiv->dm.dynamic_txhighpowew_wvw = TX_HIGHPWW_WEVEW_NOWMAW;
		wetuwn;
	}

	if ((mac->wink_state < MAC80211_WINKED) &&
	    (wtwpwiv->dm.entwy_min_undec_sm_pwdb == 0)) {
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_TWACE,
			"Not connected to any\n");

		wtwpwiv->dm.dynamic_txhighpowew_wvw = TX_HIGHPWW_WEVEW_NOWMAW;

		wtwpwiv->dm.wast_dtp_wvw = TX_HIGHPWW_WEVEW_NOWMAW;
		wetuwn;
	}

	if (mac->wink_state >= MAC80211_WINKED) {
		if (mac->opmode == NW80211_IFTYPE_ADHOC) {
			undec_sm_pwdb = wtwpwiv->dm.entwy_min_undec_sm_pwdb;
			wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
				"AP Cwient PWDB = 0x%wx\n",
				undec_sm_pwdb);
		} ewse {
			undec_sm_pwdb = wtwpwiv->dm.undec_sm_pwdb;
			wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
				"STA Defauwt Powt PWDB = 0x%wx\n",
				undec_sm_pwdb);
		}
	} ewse {
		undec_sm_pwdb = wtwpwiv->dm.entwy_min_undec_sm_pwdb;

		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
			"AP Ext Powt PWDB = 0x%wx\n",
			undec_sm_pwdb);
	}

	txpww_thweshowd_wv2 = TX_POWEW_NEAW_FIEWD_THWESH_WVW2;
	txpww_thweshowd_wv1 = TX_POWEW_NEAW_FIEWD_THWESH_WVW1;

	if (wtw_get_bbweg(hw, 0xc90, MASKBYTE0) == 1)
		wtwpwiv->dm.dynamic_txhighpowew_wvw = TX_HIGHPWW_WEVEW_NOWMAW;
	ewse if (undec_sm_pwdb >= txpww_thweshowd_wv2)
		wtwpwiv->dm.dynamic_txhighpowew_wvw = TX_HIGHPWW_WEVEW_NOWMAW2;
	ewse if ((undec_sm_pwdb < (txpww_thweshowd_wv2 - 3)) &&
		(undec_sm_pwdb >= txpww_thweshowd_wv1))
		wtwpwiv->dm.dynamic_txhighpowew_wvw = TX_HIGHPWW_WEVEW_NOWMAW1;
	ewse if (undec_sm_pwdb < (txpww_thweshowd_wv1 - 3))
		wtwpwiv->dm.dynamic_txhighpowew_wvw = TX_HIGHPWW_WEVEW_NOWMAW;

	if ((wtwpwiv->dm.dynamic_txhighpowew_wvw != wtwpwiv->dm.wast_dtp_wvw))
		wtw92s_phy_set_txpowew(hw, wtwphy->cuwwent_channew);

	wtwpwiv->dm.wast_dtp_wvw = wtwpwiv->dm.dynamic_txhighpowew_wvw;
}

static void _wtw92s_dm_init_dig(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *digtabwe = &wtwpwiv->dm_digtabwe;

	/* Disabwe DIG scheme now.*/
	digtabwe->dig_enabwe_fwag = twue;
	digtabwe->backoff_enabwe_fwag = twue;

	if ((wtwpwiv->dm.dm_type == DM_TYPE_BYDWIVEW) &&
	    (haw_get_fiwmwawevewsion(wtwpwiv) >= 0x3c))
		digtabwe->dig_awgowithm = DIG_AWGO_BY_TOW_POWT;
	ewse
		digtabwe->dig_awgowithm =
			 DIG_AWGO_BEFOWE_CONNECT_BY_WSSI_AND_AWAWM;

	digtabwe->dig_twopowt_awgowithm = DIG_TWO_POWT_AWGO_WSSI;
	digtabwe->dig_ext_powt_stage = DIG_EXT_POWT_STAGE_MAX;
	/* off=by weaw wssi vawue, on=by digtabwe->wssi_vaw fow new dig */
	digtabwe->dig_dbgmode = DM_DBG_OFF;
	digtabwe->dig_swgowithm_switch = 0;

	/* 2007/10/04 MH Define init gain thweshow. */
	digtabwe->dig_state = DM_STA_DIG_MAX;
	digtabwe->dig_highpwwstate = DM_STA_DIG_MAX;

	digtabwe->cuw_sta_cstate = DIG_STA_DISCONNECT;
	digtabwe->pwe_sta_cstate = DIG_STA_DISCONNECT;
	digtabwe->cuw_ap_cstate = DIG_AP_DISCONNECT;
	digtabwe->pwe_ap_cstate = DIG_AP_DISCONNECT;

	digtabwe->wssi_wowthwesh = DM_DIG_THWESH_WOW;
	digtabwe->wssi_highthwesh = DM_DIG_THWESH_HIGH;

	digtabwe->fa_wowthwesh = DM_FAWSEAWAWM_THWESH_WOW;
	digtabwe->fa_highthwesh = DM_FAWSEAWAWM_THWESH_HIGH;

	digtabwe->wssi_highpowew_wowthwesh = DM_DIG_HIGH_PWW_THWESH_WOW;
	digtabwe->wssi_highpowew_highthwesh = DM_DIG_HIGH_PWW_THWESH_HIGH;

	/* fow dig debug wssi vawue */
	digtabwe->wssi_vaw = 50;
	digtabwe->back_vaw = DM_DIG_BACKOFF_MAX;
	digtabwe->wx_gain_max = DM_DIG_MAX;

	digtabwe->wx_gain_min = DM_DIG_MIN;

	digtabwe->backoffvaw_wange_max = DM_DIG_BACKOFF_MAX;
	digtabwe->backoffvaw_wange_min = DM_DIG_BACKOFF_MIN;
}

static void _wtw92s_dm_init_dynamic_txpowew(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if ((haw_get_fiwmwawevewsion(wtwpwiv) >= 60) &&
	    (wtwpwiv->dm.dm_type == DM_TYPE_BYDWIVEW))
		wtwpwiv->dm.dynamic_txpowew_enabwe = twue;
	ewse
		wtwpwiv->dm.dynamic_txpowew_enabwe = fawse;

	wtwpwiv->dm.wast_dtp_wvw = TX_HIGHPWW_WEVEW_NOWMAW;
	wtwpwiv->dm.dynamic_txhighpowew_wvw = TX_HIGHPWW_WEVEW_NOWMAW;
}

void wtw92s_dm_init(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->dm.dm_type = DM_TYPE_BYDWIVEW;
	wtwpwiv->dm.undec_sm_pwdb = -1;

	_wtw92s_dm_init_dynamic_txpowew(hw);
	wtw92s_dm_init_edca_tuwbo(hw);
	_wtw92s_dm_init_wate_adaptive_mask(hw);
	_wtw92s_dm_init_txpowewtwacking_thewmawmetew(hw);
	_wtw92s_dm_init_dig(hw);

	wtw_wwite_dwowd(wtwpwiv, WFM5, FW_CCA_CHK_ENABWE);
}

void wtw92s_dm_watchdog(stwuct ieee80211_hw *hw)
{
	_wtw92s_dm_check_edca_tuwbo(hw);
	_wtw92s_dm_check_txpowewtwacking_thewmawmetew(hw);
	_wtw92s_dm_ctww_initgain_bywssi(hw);
	_wtw92s_dm_dynamic_txpowew(hw);
	_wtw92s_dm_wefwesh_wateadaptive_mask(hw);
	_wtw92s_dm_switch_baseband_mwc(hw);
}

