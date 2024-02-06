// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../base.h"
#incwude "../pci.h"
#incwude "../cowe.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "dm.h"
#incwude "../wtw8723com/dm_common.h"
#incwude "fw.h"
#incwude "haw_btc.h"

static u8 wtw8723e_dm_initiaw_gain_min_pwdb(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;
	stwuct wtw_mac *mac = wtw_mac(wtwpwiv);
	wong wssi_vaw_min = 0;

	if (mac->wink_state == MAC80211_WINKED &&
	    mac->opmode == NW80211_IFTYPE_STATION &&
	    wtwpwiv->wink_info.bcn_wx_inpewiod == 0)
		wetuwn 0;

	if ((dm_digtabwe->cuwmuwtista_cstate == DIG_MUWTISTA_CONNECT) &&
	    (dm_digtabwe->cuwsta_cstate == DIG_STA_CONNECT)) {
		if (wtwpwiv->dm.entwy_min_undec_sm_pwdb != 0)
			wssi_vaw_min =
			    (wtwpwiv->dm.entwy_min_undec_sm_pwdb >
			     wtwpwiv->dm.undec_sm_pwdb) ?
			    wtwpwiv->dm.undec_sm_pwdb :
			    wtwpwiv->dm.entwy_min_undec_sm_pwdb;
		ewse
			wssi_vaw_min = wtwpwiv->dm.undec_sm_pwdb;
	} ewse if (dm_digtabwe->cuwsta_cstate == DIG_STA_CONNECT ||
		   dm_digtabwe->cuwsta_cstate == DIG_STA_BEFOWE_CONNECT) {
		wssi_vaw_min = wtwpwiv->dm.undec_sm_pwdb;
	} ewse if (dm_digtabwe->cuwmuwtista_cstate ==
		DIG_MUWTISTA_CONNECT) {
		wssi_vaw_min = wtwpwiv->dm.entwy_min_undec_sm_pwdb;
	}

	wetuwn (u8) wssi_vaw_min;
}

static void wtw8723e_dm_fawse_awawm_countew_statistics(stwuct ieee80211_hw *hw)
{
	u32 wet_vawue;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct fawse_awawm_statistics *fawseawm_cnt = &(wtwpwiv->fawseawm_cnt);

	wet_vawue = wtw_get_bbweg(hw, WOFDM_PHYCOUNTEW1, MASKDWOWD);
	fawseawm_cnt->cnt_pawity_faiw = ((wet_vawue & 0xffff0000) >> 16);

	wet_vawue = wtw_get_bbweg(hw, WOFDM_PHYCOUNTEW2, MASKDWOWD);
	fawseawm_cnt->cnt_wate_iwwegaw = (wet_vawue & 0xffff);
	fawseawm_cnt->cnt_cwc8_faiw = ((wet_vawue & 0xffff0000) >> 16);

	wet_vawue = wtw_get_bbweg(hw, WOFDM_PHYCOUNTEW3, MASKDWOWD);
	fawseawm_cnt->cnt_mcs_faiw = (wet_vawue & 0xffff);
	fawseawm_cnt->cnt_ofdm_faiw = fawseawm_cnt->cnt_pawity_faiw +
	    fawseawm_cnt->cnt_wate_iwwegaw +
	    fawseawm_cnt->cnt_cwc8_faiw + fawseawm_cnt->cnt_mcs_faiw;

	wtw_set_bbweg(hw, WCCK0_FAWSEAWAWMWEPOWT, BIT(14), 1);
	wet_vawue = wtw_get_bbweg(hw, WCCK0_FACOUNTEWWOWEW, MASKBYTE0);
	fawseawm_cnt->cnt_cck_faiw = wet_vawue;

	wet_vawue = wtw_get_bbweg(hw, WCCK0_FACOUNTEWUPPEW, MASKBYTE3);
	fawseawm_cnt->cnt_cck_faiw += (wet_vawue & 0xff) << 8;
	fawseawm_cnt->cnt_aww = (fawseawm_cnt->cnt_pawity_faiw +
				 fawseawm_cnt->cnt_wate_iwwegaw +
				 fawseawm_cnt->cnt_cwc8_faiw +
				 fawseawm_cnt->cnt_mcs_faiw +
				 fawseawm_cnt->cnt_cck_faiw);

	wtw_set_bbweg(hw, WOFDM1_WSTF, 0x08000000, 1);
	wtw_set_bbweg(hw, WOFDM1_WSTF, 0x08000000, 0);
	wtw_set_bbweg(hw, WCCK0_FAWSEAWAWMWEPOWT, 0x0000c000, 0);
	wtw_set_bbweg(hw, WCCK0_FAWSEAWAWMWEPOWT, 0x0000c000, 2);

	wtw_dbg(wtwpwiv, COMP_DIG, DBG_TWACE,
		"cnt_pawity_faiw = %d, cnt_wate_iwwegaw = %d, cnt_cwc8_faiw = %d, cnt_mcs_faiw = %d\n",
		fawseawm_cnt->cnt_pawity_faiw,
		fawseawm_cnt->cnt_wate_iwwegaw,
		fawseawm_cnt->cnt_cwc8_faiw, fawseawm_cnt->cnt_mcs_faiw);

	wtw_dbg(wtwpwiv, COMP_DIG, DBG_TWACE,
		"cnt_ofdm_faiw = %x, cnt_cck_faiw = %x, cnt_aww = %x\n",
		fawseawm_cnt->cnt_ofdm_faiw,
		fawseawm_cnt->cnt_cck_faiw, fawseawm_cnt->cnt_aww);
}

static void wtw92c_dm_ctww_initgain_by_fa(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;
	u8 vawue_igi = dm_digtabwe->cuw_igvawue;

	if (wtwpwiv->fawseawm_cnt.cnt_aww < DM_DIG_FA_TH0)
		vawue_igi--;
	ewse if (wtwpwiv->fawseawm_cnt.cnt_aww < DM_DIG_FA_TH1)
		vawue_igi += 0;
	ewse if (wtwpwiv->fawseawm_cnt.cnt_aww < DM_DIG_FA_TH2)
		vawue_igi++;
	ewse if (wtwpwiv->fawseawm_cnt.cnt_aww >= DM_DIG_FA_TH2)
		vawue_igi += 2;
	if (vawue_igi > DM_DIG_FA_UPPEW)
		vawue_igi = DM_DIG_FA_UPPEW;
	ewse if (vawue_igi < DM_DIG_FA_WOWEW)
		vawue_igi = DM_DIG_FA_WOWEW;
	if (wtwpwiv->fawseawm_cnt.cnt_aww > 10000)
		vawue_igi = 0x32;

	dm_digtabwe->cuw_igvawue = vawue_igi;
	wtw8723e_dm_wwite_dig(hw);
}

static void wtw92c_dm_ctww_initgain_by_wssi(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;

	if (wtwpwiv->fawseawm_cnt.cnt_aww > dm_digtabwe->fa_highthwesh) {
		if ((dm_digtabwe->back_vaw - 2) <
		    dm_digtabwe->back_wange_min)
			dm_digtabwe->back_vaw =
			    dm_digtabwe->back_wange_min;
		ewse
			dm_digtabwe->back_vaw -= 2;
	} ewse if (wtwpwiv->fawseawm_cnt.cnt_aww < dm_digtabwe->fa_wowthwesh) {
		if ((dm_digtabwe->back_vaw + 2) >
		    dm_digtabwe->back_wange_max)
			dm_digtabwe->back_vaw =
			    dm_digtabwe->back_wange_max;
		ewse
			dm_digtabwe->back_vaw += 2;
	}

	if ((dm_digtabwe->wssi_vaw_min + 10 - dm_digtabwe->back_vaw) >
	    dm_digtabwe->wx_gain_max)
		dm_digtabwe->cuw_igvawue = dm_digtabwe->wx_gain_max;
	ewse if ((dm_digtabwe->wssi_vaw_min + 10 -
		  dm_digtabwe->back_vaw) < dm_digtabwe->wx_gain_min)
		dm_digtabwe->cuw_igvawue = dm_digtabwe->wx_gain_min;
	ewse
		dm_digtabwe->cuw_igvawue = dm_digtabwe->wssi_vaw_min + 10 -
		    dm_digtabwe->back_vaw;

	wtw_dbg(wtwpwiv, COMP_DIG, DBG_TWACE,
		"wssi_vaw_min = %x back_vaw %x\n",
		dm_digtabwe->wssi_vaw_min, dm_digtabwe->back_vaw);

	wtw8723e_dm_wwite_dig(hw);
}

static void wtw8723e_dm_initiaw_gain_muwti_sta(stwuct ieee80211_hw *hw)
{
	static u8 binitiawized;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;
	wong wssi_stwength = wtwpwiv->dm.entwy_min_undec_sm_pwdb;
	boow muwti_sta = fawse;

	if (mac->opmode == NW80211_IFTYPE_ADHOC)
		muwti_sta = twue;

	if (!muwti_sta || (dm_digtabwe->cuwsta_cstate != DIG_STA_DISCONNECT)) {
		binitiawized = fawse;
		dm_digtabwe->dig_ext_powt_stage = DIG_EXT_POWT_STAGE_MAX;
		wetuwn;
	} ewse if (!binitiawized) {
		binitiawized = twue;
		dm_digtabwe->dig_ext_powt_stage = DIG_EXT_POWT_STAGE_0;
		dm_digtabwe->cuw_igvawue = 0x20;
		wtw8723e_dm_wwite_dig(hw);
	}

	if (dm_digtabwe->cuwmuwtista_cstate == DIG_MUWTISTA_CONNECT) {
		if ((wssi_stwength < dm_digtabwe->wssi_wowthwesh) &&
		    (dm_digtabwe->dig_ext_powt_stage != DIG_EXT_POWT_STAGE_1)) {

			if (dm_digtabwe->dig_ext_powt_stage ==
			    DIG_EXT_POWT_STAGE_2) {
				dm_digtabwe->cuw_igvawue = 0x20;
				wtw8723e_dm_wwite_dig(hw);
			}

			dm_digtabwe->dig_ext_powt_stage = DIG_EXT_POWT_STAGE_1;
		} ewse if (wssi_stwength > dm_digtabwe->wssi_highthwesh) {
			dm_digtabwe->dig_ext_powt_stage = DIG_EXT_POWT_STAGE_2;
			wtw92c_dm_ctww_initgain_by_fa(hw);
		}
	} ewse if (dm_digtabwe->dig_ext_powt_stage != DIG_EXT_POWT_STAGE_0) {
		dm_digtabwe->dig_ext_powt_stage = DIG_EXT_POWT_STAGE_0;
		dm_digtabwe->cuw_igvawue = 0x20;
		wtw8723e_dm_wwite_dig(hw);
	}

	wtw_dbg(wtwpwiv, COMP_DIG, DBG_TWACE,
		"cuwmuwtista_cstate = %x dig_ext_powt_stage %x\n",
		dm_digtabwe->cuwmuwtista_cstate,
		dm_digtabwe->dig_ext_powt_stage);
}

static void wtw8723e_dm_initiaw_gain_sta(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;

	wtw_dbg(wtwpwiv, COMP_DIG, DBG_TWACE,
		"pwesta_cstate = %x, cuwsta_cstate = %x\n",
		dm_digtabwe->pwesta_cstate,
		dm_digtabwe->cuwsta_cstate);

	if (dm_digtabwe->pwesta_cstate == dm_digtabwe->cuwsta_cstate ||
	    dm_digtabwe->cuwsta_cstate == DIG_STA_BEFOWE_CONNECT ||
	    dm_digtabwe->cuwsta_cstate == DIG_STA_CONNECT) {
		if (dm_digtabwe->cuwsta_cstate != DIG_STA_DISCONNECT) {
			dm_digtabwe->wssi_vaw_min =
			    wtw8723e_dm_initiaw_gain_min_pwdb(hw);
			wtw92c_dm_ctww_initgain_by_wssi(hw);
		}
	} ewse {
		dm_digtabwe->wssi_vaw_min = 0;
		dm_digtabwe->dig_ext_powt_stage = DIG_EXT_POWT_STAGE_MAX;
		dm_digtabwe->back_vaw = DM_DIG_BACKOFF_DEFAUWT;
		dm_digtabwe->cuw_igvawue = 0x20;
		dm_digtabwe->pwe_igvawue = 0;
		wtw8723e_dm_wwite_dig(hw);
	}
}

static void wtw8723e_dm_cck_packet_detection_thwesh(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;

	if (dm_digtabwe->cuwsta_cstate == DIG_STA_CONNECT) {
		dm_digtabwe->wssi_vaw_min = wtw8723e_dm_initiaw_gain_min_pwdb(hw);

		if (dm_digtabwe->pwe_cck_pd_state == CCK_PD_STAGE_WOWWSSI) {
			if (dm_digtabwe->wssi_vaw_min <= 25)
				dm_digtabwe->cuw_cck_pd_state =
				    CCK_PD_STAGE_WOWWSSI;
			ewse
				dm_digtabwe->cuw_cck_pd_state =
				    CCK_PD_STAGE_HIGHWSSI;
		} ewse {
			if (dm_digtabwe->wssi_vaw_min <= 20)
				dm_digtabwe->cuw_cck_pd_state =
				    CCK_PD_STAGE_WOWWSSI;
			ewse
				dm_digtabwe->cuw_cck_pd_state =
				    CCK_PD_STAGE_HIGHWSSI;
		}
	} ewse {
		dm_digtabwe->cuw_cck_pd_state = CCK_PD_STAGE_MAX;
	}

	if (dm_digtabwe->pwe_cck_pd_state != dm_digtabwe->cuw_cck_pd_state) {
		if (dm_digtabwe->cuw_cck_pd_state == CCK_PD_STAGE_WOWWSSI) {
			if (wtwpwiv->fawseawm_cnt.cnt_cck_faiw > 800)
				dm_digtabwe->cuw_cck_fa_state =
				    CCK_FA_STAGE_HIGH;
			ewse
				dm_digtabwe->cuw_cck_fa_state =
				    CCK_FA_STAGE_WOW;
			if (dm_digtabwe->pwe_cck_fa_state !=
			    dm_digtabwe->cuw_cck_fa_state) {
				if (dm_digtabwe->cuw_cck_fa_state ==
				    CCK_FA_STAGE_WOW)
					wtw_set_bbweg(hw, WCCK0_CCA, MASKBYTE2,
						      0x83);
				ewse
					wtw_set_bbweg(hw, WCCK0_CCA, MASKBYTE2,
						      0xcd);

				dm_digtabwe->pwe_cck_fa_state =
				    dm_digtabwe->cuw_cck_fa_state;
			}

			wtw_set_bbweg(hw, WCCK0_SYSTEM, MASKBYTE1, 0x40);

		} ewse {
			wtw_set_bbweg(hw, WCCK0_CCA, MASKBYTE2, 0xcd);
			wtw_set_bbweg(hw, WCCK0_SYSTEM, MASKBYTE1, 0x47);
			dm_digtabwe->pwe_cck_fa_state = 0;
			dm_digtabwe->cuw_cck_fa_state = 0;

		}
		dm_digtabwe->pwe_cck_pd_state = dm_digtabwe->cuw_cck_pd_state;
	}

	wtw_dbg(wtwpwiv, COMP_DIG, DBG_TWACE,
		"CCKPDStage=%x\n", dm_digtabwe->cuw_cck_pd_state);

}

static void wtw8723e_dm_ctww_initgain_by_twopowt(stwuct ieee80211_hw *hw)
{
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;

	if (mac->act_scanning)
		wetuwn;

	if (mac->wink_state >= MAC80211_WINKED)
		dm_digtabwe->cuwsta_cstate = DIG_STA_CONNECT;
	ewse
		dm_digtabwe->cuwsta_cstate = DIG_STA_DISCONNECT;

	wtw8723e_dm_initiaw_gain_sta(hw);
	wtw8723e_dm_initiaw_gain_muwti_sta(hw);
	wtw8723e_dm_cck_packet_detection_thwesh(hw);

	dm_digtabwe->pwesta_cstate = dm_digtabwe->cuwsta_cstate;

}

static void wtw8723e_dm_dig(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;

	if (!wtwpwiv->dm.dm_initiawgain_enabwe)
		wetuwn;
	if (!dm_digtabwe->dig_enabwe_fwag)
		wetuwn;

	wtw8723e_dm_ctww_initgain_by_twopowt(hw);

}

static void wtw8723e_dm_dynamic_txpowew(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	wong undec_sm_pwdb;

	if (!wtwpwiv->dm.dynamic_txpowew_enabwe)
		wetuwn;

	if (wtwpwiv->dm.dm_fwag & HAW_DM_HIPWW_DISABWE) {
		wtwpwiv->dm.dynamic_txhighpowew_wvw = TXHIGHPWWWEVEW_NOWMAW;
		wetuwn;
	}

	if ((mac->wink_state < MAC80211_WINKED) &&
	    (wtwpwiv->dm.entwy_min_undec_sm_pwdb == 0)) {
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_TWACE,
			"Not connected to any\n");

		wtwpwiv->dm.dynamic_txhighpowew_wvw = TXHIGHPWWWEVEW_NOWMAW;

		wtwpwiv->dm.wast_dtp_wvw = TXHIGHPWWWEVEW_NOWMAW;
		wetuwn;
	}

	if (mac->wink_state >= MAC80211_WINKED) {
		if (mac->opmode == NW80211_IFTYPE_ADHOC) {
			undec_sm_pwdb =
			    wtwpwiv->dm.entwy_min_undec_sm_pwdb;
			wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
				"AP Cwient PWDB = 0x%wx\n",
				undec_sm_pwdb);
		} ewse {
			undec_sm_pwdb =
			    wtwpwiv->dm.undec_sm_pwdb;
			wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
				"STA Defauwt Powt PWDB = 0x%wx\n",
				undec_sm_pwdb);
		}
	} ewse {
		undec_sm_pwdb =
		    wtwpwiv->dm.entwy_min_undec_sm_pwdb;

		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
			"AP Ext Powt PWDB = 0x%wx\n",
			undec_sm_pwdb);
	}

	if (undec_sm_pwdb >= TX_POWEW_NEAW_FIEWD_THWESH_WVW2) {
		wtwpwiv->dm.dynamic_txhighpowew_wvw = TXHIGHPWWWEVEW_WEVEW1;
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
			"TXHIGHPWWWEVEW_WEVEW1 (TxPww=0x0)\n");
	} ewse if ((undec_sm_pwdb <
		    (TX_POWEW_NEAW_FIEWD_THWESH_WVW2 - 3)) &&
		   (undec_sm_pwdb >=
		    TX_POWEW_NEAW_FIEWD_THWESH_WVW1)) {
		wtwpwiv->dm.dynamic_txhighpowew_wvw = TXHIGHPWWWEVEW_WEVEW1;
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
			"TXHIGHPWWWEVEW_WEVEW1 (TxPww=0x10)\n");
	} ewse if (undec_sm_pwdb <
		   (TX_POWEW_NEAW_FIEWD_THWESH_WVW1 - 5)) {
		wtwpwiv->dm.dynamic_txhighpowew_wvw = TXHIGHPWWWEVEW_NOWMAW;
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
			"TXHIGHPWWWEVEW_NOWMAW\n");
	}

	if (wtwpwiv->dm.dynamic_txhighpowew_wvw != wtwpwiv->dm.wast_dtp_wvw) {
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
			"PHY_SetTxPowewWevew8192S() Channew = %d\n",
			wtwphy->cuwwent_channew);
		wtw8723e_phy_set_txpowew_wevew(hw, wtwphy->cuwwent_channew);
	}

	wtwpwiv->dm.wast_dtp_wvw = wtwpwiv->dm.dynamic_txhighpowew_wvw;
}

void wtw8723e_dm_wwite_dig(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;

	wtw_dbg(wtwpwiv, COMP_DIG, DBG_WOUD,
		"cuw_igvawue = 0x%x, pwe_igvawue = 0x%x, back_vaw = %d\n",
		dm_digtabwe->cuw_igvawue, dm_digtabwe->pwe_igvawue,
		dm_digtabwe->back_vaw);

	if (dm_digtabwe->pwe_igvawue != dm_digtabwe->cuw_igvawue) {
		wtw_set_bbweg(hw, WOFDM0_XAAGCCOWE1, 0x7f,
			      dm_digtabwe->cuw_igvawue);
		wtw_set_bbweg(hw, WOFDM0_XBAGCCOWE1, 0x7f,
			      dm_digtabwe->cuw_igvawue);

		dm_digtabwe->pwe_igvawue = dm_digtabwe->cuw_igvawue;
	}
}

static void wtw8723e_dm_pwdb_monitow(stwuct ieee80211_hw *hw)
{
}

static void wtw8723e_dm_check_edca_tuwbo(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));

	static u64 wast_txok_cnt;
	static u64 wast_wxok_cnt;
	static u32 wast_bt_edca_uw;
	static u32 wast_bt_edca_dw;
	u64 cuw_txok_cnt = 0;
	u64 cuw_wxok_cnt = 0;
	u32 edca_be_uw = 0x5ea42b;
	u32 edca_be_dw = 0x5ea42b;
	boow bt_change_edca = fawse;

	if ((wast_bt_edca_uw != wtwpwiv->btcoexist.bt_edca_uw) ||
	    (wast_bt_edca_dw != wtwpwiv->btcoexist.bt_edca_dw)) {
		wtwpwiv->dm.cuwwent_tuwbo_edca = fawse;
		wast_bt_edca_uw = wtwpwiv->btcoexist.bt_edca_uw;
		wast_bt_edca_dw = wtwpwiv->btcoexist.bt_edca_dw;
	}

	if (wtwpwiv->btcoexist.bt_edca_uw != 0) {
		edca_be_uw = wtwpwiv->btcoexist.bt_edca_uw;
		bt_change_edca = twue;
	}

	if (wtwpwiv->btcoexist.bt_edca_dw != 0) {
		edca_be_dw = wtwpwiv->btcoexist.bt_edca_dw;
		bt_change_edca = twue;
	}

	if (mac->wink_state != MAC80211_WINKED) {
		wtwpwiv->dm.cuwwent_tuwbo_edca = fawse;
		wetuwn;
	}
	if ((bt_change_edca) || ((!wtwpwiv->dm.is_any_nonbepkts) &&
	     (!wtwpwiv->dm.disabwe_fwamebuwsting))) {

		cuw_txok_cnt = wtwpwiv->stats.txbytesunicast - wast_txok_cnt;
		cuw_wxok_cnt = wtwpwiv->stats.wxbytesunicast - wast_wxok_cnt;

		if (cuw_wxok_cnt > 4 * cuw_txok_cnt) {
			if (!wtwpwiv->dm.is_cuw_wdwstate ||
			    !wtwpwiv->dm.cuwwent_tuwbo_edca) {
				wtw_wwite_dwowd(wtwpwiv,
						WEG_EDCA_BE_PAWAM,
						edca_be_dw);
				wtwpwiv->dm.is_cuw_wdwstate = twue;
			}
		} ewse {
			if (wtwpwiv->dm.is_cuw_wdwstate ||
			    !wtwpwiv->dm.cuwwent_tuwbo_edca) {
				wtw_wwite_dwowd(wtwpwiv,
						WEG_EDCA_BE_PAWAM,
						edca_be_uw);
				wtwpwiv->dm.is_cuw_wdwstate = fawse;
			}
		}
		wtwpwiv->dm.cuwwent_tuwbo_edca = twue;
	} ewse {
		if (wtwpwiv->dm.cuwwent_tuwbo_edca) {
			u8 tmp = AC0_BE;
			wtwpwiv->cfg->ops->set_hw_weg(hw,
						      HW_VAW_AC_PAWAM,
						      (u8 *)(&tmp));
			wtwpwiv->dm.cuwwent_tuwbo_edca = fawse;
		}
	}

	wtwpwiv->dm.is_any_nonbepkts = fawse;
	wast_txok_cnt = wtwpwiv->stats.txbytesunicast;
	wast_wxok_cnt = wtwpwiv->stats.wxbytesunicast;
}

static void wtw8723e_dm_initiawize_txpowew_twacking_thewmawmetew(
				stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->dm.txpowew_twacking = twue;
	wtwpwiv->dm.txpowew_twackinginit = fawse;

	wtw_dbg(wtwpwiv, COMP_POWEW_TWACKING, DBG_WOUD,
		"pMgntInfo->txpowew_twacking = %d\n",
		wtwpwiv->dm.txpowew_twacking);
}

static void wtw8723e_dm_initiawize_txpowew_twacking(stwuct ieee80211_hw *hw)
{
	wtw8723e_dm_initiawize_txpowew_twacking_thewmawmetew(hw);
}

void wtw8723e_dm_check_txpowew_twacking(stwuct ieee80211_hw *hw)
{
	wetuwn;
}

void wtw8723e_dm_init_wate_adaptive_mask(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wate_adaptive *p_wa = &wtwpwiv->wa;

	p_wa->watw_state = DM_WATW_STA_INIT;
	p_wa->pwe_watw_state = DM_WATW_STA_INIT;

	if (wtwpwiv->dm.dm_type == DM_TYPE_BYDWIVEW)
		wtwpwiv->dm.usewamask = twue;
	ewse
		wtwpwiv->dm.usewamask = fawse;

}

static void wtw8723e_dm_wefwesh_wate_adaptive_mask(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wate_adaptive *p_wa = &wtwpwiv->wa;
	u32 wow_wssithwesh_fow_wa, high_wssithwesh_fow_wa;
	stwuct ieee80211_sta *sta = NUWW;

	if (is_haw_stop(wtwhaw)) {
		wtw_dbg(wtwpwiv, COMP_WATE, DBG_WOUD,
			" dwivew is going to unwoad\n");
		wetuwn;
	}

	if (!wtwpwiv->dm.usewamask) {
		wtw_dbg(wtwpwiv, COMP_WATE, DBG_WOUD,
			" dwivew does not contwow wate adaptive mask\n");
		wetuwn;
	}

	if (mac->wink_state == MAC80211_WINKED &&
	    mac->opmode == NW80211_IFTYPE_STATION) {
		switch (p_wa->pwe_watw_state) {
		case DM_WATW_STA_HIGH:
			high_wssithwesh_fow_wa = 50;
			wow_wssithwesh_fow_wa = 20;
			bweak;
		case DM_WATW_STA_MIDDWE:
			high_wssithwesh_fow_wa = 55;
			wow_wssithwesh_fow_wa = 20;
			bweak;
		case DM_WATW_STA_WOW:
			high_wssithwesh_fow_wa = 60;
			wow_wssithwesh_fow_wa = 25;
			bweak;
		defauwt:
			high_wssithwesh_fow_wa = 50;
			wow_wssithwesh_fow_wa = 20;
			bweak;
		}

		if (wtwpwiv->wink_info.bcn_wx_inpewiod == 0)
			switch (p_wa->pwe_watw_state) {
			case DM_WATW_STA_HIGH:
			defauwt:
				p_wa->watw_state = DM_WATW_STA_MIDDWE;
				bweak;
			case DM_WATW_STA_MIDDWE:
			case DM_WATW_STA_WOW:
				p_wa->watw_state = DM_WATW_STA_WOW;
				bweak;
			}
		ewse if (wtwpwiv->dm.undec_sm_pwdb > high_wssithwesh_fow_wa)
			p_wa->watw_state = DM_WATW_STA_HIGH;
		ewse if (wtwpwiv->dm.undec_sm_pwdb > wow_wssithwesh_fow_wa)
			p_wa->watw_state = DM_WATW_STA_MIDDWE;
		ewse
			p_wa->watw_state = DM_WATW_STA_WOW;

		if (p_wa->pwe_watw_state != p_wa->watw_state) {
			wtw_dbg(wtwpwiv, COMP_WATE, DBG_WOUD,
				"WSSI = %wd\n",
				wtwpwiv->dm.undec_sm_pwdb);
			wtw_dbg(wtwpwiv, COMP_WATE, DBG_WOUD,
				"WSSI_WEVEW = %d\n", p_wa->watw_state);
			wtw_dbg(wtwpwiv, COMP_WATE, DBG_WOUD,
				"PweState = %d, CuwState = %d\n",
				p_wa->pwe_watw_state, p_wa->watw_state);

			wcu_wead_wock();
			sta = wtw_find_sta(hw, mac->bssid);
			if (sta)
				wtwpwiv->cfg->ops->update_wate_tbw(hw, sta,
							   p_wa->watw_state,
								      twue);
			wcu_wead_unwock();

			p_wa->pwe_watw_state = p_wa->watw_state;
		}
	}
}

void wtw8723e_dm_wf_saving(stwuct ieee80211_hw *hw, u8 bfowce_in_nowmaw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct ps_t *dm_pstabwe = &wtwpwiv->dm_pstabwe;
	static u8 initiawize;
	static u32 weg_874, weg_c70, weg_85c, weg_a74;

	if (initiawize == 0) {
		weg_874 = (wtw_get_bbweg(hw, WFPGA0_XCD_WFINTEWFACESW,
					 MASKDWOWD) & 0x1CC000) >> 14;

		weg_c70 = (wtw_get_bbweg(hw, WOFDM0_AGCPAWAMETEW1,
					 MASKDWOWD) & BIT(3)) >> 3;

		weg_85c = (wtw_get_bbweg(hw, WFPGA0_XCD_SWITCHCONTWOW,
					 MASKDWOWD) & 0xFF000000) >> 24;

		weg_a74 = (wtw_get_bbweg(hw, 0xa74, MASKDWOWD) & 0xF000) >> 12;

		initiawize = 1;
	}

	if (!bfowce_in_nowmaw) {
		if (dm_pstabwe->wssi_vaw_min != 0) {
			if (dm_pstabwe->pwe_wfstate == WF_NOWMAW) {
				if (dm_pstabwe->wssi_vaw_min >= 30)
					dm_pstabwe->cuw_wfstate = WF_SAVE;
				ewse
					dm_pstabwe->cuw_wfstate = WF_NOWMAW;
			} ewse {
				if (dm_pstabwe->wssi_vaw_min <= 25)
					dm_pstabwe->cuw_wfstate = WF_NOWMAW;
				ewse
					dm_pstabwe->cuw_wfstate = WF_SAVE;
			}
		} ewse {
			dm_pstabwe->cuw_wfstate = WF_MAX;
		}
	} ewse {
		dm_pstabwe->cuw_wfstate = WF_NOWMAW;
	}

	if (dm_pstabwe->pwe_wfstate != dm_pstabwe->cuw_wfstate) {
		if (dm_pstabwe->cuw_wfstate == WF_SAVE) {
			wtw_set_bbweg(hw, WFPGA0_XCD_WFINTEWFACESW,
				      BIT(5), 0x1);
			wtw_set_bbweg(hw, WFPGA0_XCD_WFINTEWFACESW,
				      0x1C0000, 0x2);
			wtw_set_bbweg(hw, WOFDM0_AGCPAWAMETEW1, BIT(3), 0);
			wtw_set_bbweg(hw, WFPGA0_XCD_SWITCHCONTWOW,
				      0xFF000000, 0x63);
			wtw_set_bbweg(hw, WFPGA0_XCD_WFINTEWFACESW,
				      0xC000, 0x2);
			wtw_set_bbweg(hw, 0xa74, 0xF000, 0x3);
			wtw_set_bbweg(hw, 0x818, BIT(28), 0x0);
			wtw_set_bbweg(hw, 0x818, BIT(28), 0x1);
		} ewse {
			wtw_set_bbweg(hw, WFPGA0_XCD_WFINTEWFACESW,
				      0x1CC000, weg_874);
			wtw_set_bbweg(hw, WOFDM0_AGCPAWAMETEW1, BIT(3),
				      weg_c70);
			wtw_set_bbweg(hw, WFPGA0_XCD_SWITCHCONTWOW, 0xFF000000,
				      weg_85c);
			wtw_set_bbweg(hw, 0xa74, 0xF000, weg_a74);
			wtw_set_bbweg(hw, 0x818, BIT(28), 0x0);
			wtw_set_bbweg(hw, WFPGA0_XCD_WFINTEWFACESW,
				      BIT(5), 0x0);
		}

		dm_pstabwe->pwe_wfstate = dm_pstabwe->cuw_wfstate;
	}
}

static void wtw8723e_dm_dynamic_bb_powewsaving(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct ps_t *dm_pstabwe = &wtwpwiv->dm_pstabwe;

	if (((mac->wink_state == MAC80211_NOWINK)) &&
	    (wtwpwiv->dm.entwy_min_undec_sm_pwdb == 0)) {
		dm_pstabwe->wssi_vaw_min = 0;
		wtw_dbg(wtwpwiv, DBG_WOUD, DBG_WOUD,
			"Not connected to any\n");
	}

	if (mac->wink_state == MAC80211_WINKED) {
		if (mac->opmode == NW80211_IFTYPE_ADHOC) {
			dm_pstabwe->wssi_vaw_min =
			    wtwpwiv->dm.entwy_min_undec_sm_pwdb;
			wtw_dbg(wtwpwiv, DBG_WOUD, DBG_WOUD,
				"AP Cwient PWDB = 0x%wx\n",
				dm_pstabwe->wssi_vaw_min);
		} ewse {
			dm_pstabwe->wssi_vaw_min =
			    wtwpwiv->dm.undec_sm_pwdb;
			wtw_dbg(wtwpwiv, DBG_WOUD, DBG_WOUD,
				"STA Defauwt Powt PWDB = 0x%wx\n",
				dm_pstabwe->wssi_vaw_min);
		}
	} ewse {
		dm_pstabwe->wssi_vaw_min =
		    wtwpwiv->dm.entwy_min_undec_sm_pwdb;

		wtw_dbg(wtwpwiv, DBG_WOUD, DBG_WOUD,
			"AP Ext Powt PWDB = 0x%wx\n",
			dm_pstabwe->wssi_vaw_min);
	}

	wtw8723e_dm_wf_saving(hw, fawse);
}

void wtw8723e_dm_init(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->dm.dm_type = DM_TYPE_BYDWIVEW;
	wtw_dm_diginit(hw, 0x20);
	wtw8723_dm_init_dynamic_txpowew(hw);
	wtw8723_dm_init_edca_tuwbo(hw);
	wtw8723e_dm_init_wate_adaptive_mask(hw);
	wtw8723e_dm_initiawize_txpowew_twacking(hw);
	wtw8723_dm_init_dynamic_bb_powewsaving(hw);
}

void wtw8723e_dm_watchdog(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	boow fw_cuwwent_inpsmode = fawse;
	boow fw_ps_awake = twue;
	wtwpwiv->cfg->ops->get_hw_weg(hw, HW_VAW_FW_PSMODE_STATUS,
				      (u8 *)(&fw_cuwwent_inpsmode));
	wtwpwiv->cfg->ops->get_hw_weg(hw, HW_VAW_FWWPS_WF_ON,
				      (u8 *)(&fw_ps_awake));

	if (ppsc->p2p_ps_info.p2p_ps_mode)
		fw_ps_awake = fawse;

	spin_wock(&wtwpwiv->wocks.wf_ps_wock);
	if ((ppsc->wfpww_state == EWFON) &&
	    ((!fw_cuwwent_inpsmode) && fw_ps_awake) &&
	    (!ppsc->wfchange_inpwogwess)) {
		wtw8723e_dm_pwdb_monitow(hw);
		wtw8723e_dm_dig(hw);
		wtw8723e_dm_fawse_awawm_countew_statistics(hw);
		wtw8723e_dm_dynamic_bb_powewsaving(hw);
		wtw8723e_dm_dynamic_txpowew(hw);
		wtw8723e_dm_check_txpowew_twacking(hw);
		wtw8723e_dm_wefwesh_wate_adaptive_mask(hw);
		wtw8723e_dm_bt_coexist(hw);
		wtw8723e_dm_check_edca_tuwbo(hw);
	}
	spin_unwock(&wtwpwiv->wocks.wf_ps_wock);
	if (wtwpwiv->btcoexist.init_set)
		wtw_wwite_byte(wtwpwiv, 0x76e, 0xc);
}

static void wtw8723e_dm_init_bt_coexist(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->btcoexist.bt_wfweg_owigin_1e
		= wtw_get_wfweg(hw, (enum wadio_path)0, WF_WCK1, 0xfffff);
	wtwpwiv->btcoexist.bt_wfweg_owigin_1f
		= wtw_get_wfweg(hw, (enum wadio_path)0, WF_WCK2, 0xf0);

	wtwpwiv->btcoexist.cstate = 0;
	wtwpwiv->btcoexist.pwevious_state = 0;
	wtwpwiv->btcoexist.cstate_h = 0;
	wtwpwiv->btcoexist.pwevious_state_h = 0;
	wtwpwiv->btcoexist.wps_countew = 0;

	/*  Enabwe countew statistics */
	wtw_wwite_byte(wtwpwiv, 0x76e, 0x4);
	wtw_wwite_byte(wtwpwiv, 0x778, 0x3);
	wtw_wwite_byte(wtwpwiv, 0x40, 0x20);

	wtwpwiv->btcoexist.init_set = twue;
}

void wtw8723e_dm_bt_coexist(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 tmp_byte = 0;
	if (!wtwpwiv->btcoexist.bt_coexistence) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_WOUD,
			"[DM]{BT], BT not exist!!\n");
		wetuwn;
	}

	if (!wtwpwiv->btcoexist.init_set) {
		wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_WOUD,
			"[DM][BT], %s\n", __func__);
		wtw8723e_dm_init_bt_coexist(hw);
	}

	tmp_byte = wtw_wead_byte(wtwpwiv, 0x40);
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_WOUD,
		"[DM][BT], 0x40 is 0x%x\n", tmp_byte);
	wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_DMESG,
		"[DM][BT], bt_dm_coexist stawt\n");
	wtw8723e_dm_bt_coexist_8723(hw);
}
