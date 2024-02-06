// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2014  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../base.h"
#incwude "../pci.h"
#incwude "../cowe.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "dm.h"
#incwude "fw.h"
#incwude "twx.h"

static void wtw92ee_dm_fawse_awawm_countew_statistics(stwuct ieee80211_hw *hw)
{
	u32 wet_vawue;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct fawse_awawm_statistics *fawseawm_cnt = &wtwpwiv->fawseawm_cnt;

	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_HOWDC_11N, BIT(31), 1);
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTD_11N, BIT(31), 1);

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_OFDM_FA_TYPE1_11N, MASKDWOWD);
	fawseawm_cnt->cnt_fast_fsync_faiw = (wet_vawue & 0xffff);
	fawseawm_cnt->cnt_sb_seawch_faiw = ((wet_vawue & 0xffff0000) >> 16);

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_OFDM_FA_TYPE2_11N, MASKDWOWD);
	fawseawm_cnt->cnt_ofdm_cca = (wet_vawue & 0xffff);
	fawseawm_cnt->cnt_pawity_faiw = ((wet_vawue & 0xffff0000) >> 16);

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_OFDM_FA_TYPE3_11N, MASKDWOWD);
	fawseawm_cnt->cnt_wate_iwwegaw = (wet_vawue & 0xffff);
	fawseawm_cnt->cnt_cwc8_faiw = ((wet_vawue & 0xffff0000) >> 16);

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_OFDM_FA_TYPE4_11N, MASKDWOWD);
	fawseawm_cnt->cnt_mcs_faiw = (wet_vawue & 0xffff);

	fawseawm_cnt->cnt_ofdm_faiw = fawseawm_cnt->cnt_pawity_faiw +
				      fawseawm_cnt->cnt_wate_iwwegaw +
				      fawseawm_cnt->cnt_cwc8_faiw +
				      fawseawm_cnt->cnt_mcs_faiw +
				      fawseawm_cnt->cnt_fast_fsync_faiw +
				      fawseawm_cnt->cnt_sb_seawch_faiw;

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_SC_CNT_11N, MASKDWOWD);
	fawseawm_cnt->cnt_bw_wsc = (wet_vawue & 0xffff);
	fawseawm_cnt->cnt_bw_usc = ((wet_vawue & 0xffff0000) >> 16);

	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(12), 1);
	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(14), 1);

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_CCK_FA_WSB_11N, MASKBYTE0);
	fawseawm_cnt->cnt_cck_faiw = wet_vawue;

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_CCK_FA_MSB_11N, MASKBYTE3);
	fawseawm_cnt->cnt_cck_faiw += (wet_vawue & 0xff) << 8;

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_CCK_CCA_CNT_11N, MASKDWOWD);
	fawseawm_cnt->cnt_cck_cca = ((wet_vawue & 0xff) << 8) |
				    ((wet_vawue & 0xFF00) >> 8);

	fawseawm_cnt->cnt_aww = fawseawm_cnt->cnt_fast_fsync_faiw +
				fawseawm_cnt->cnt_sb_seawch_faiw +
				fawseawm_cnt->cnt_pawity_faiw +
				fawseawm_cnt->cnt_wate_iwwegaw +
				fawseawm_cnt->cnt_cwc8_faiw +
				fawseawm_cnt->cnt_mcs_faiw +
				fawseawm_cnt->cnt_cck_faiw;

	fawseawm_cnt->cnt_cca_aww = fawseawm_cnt->cnt_ofdm_cca +
				    fawseawm_cnt->cnt_cck_cca;

	/*weset fawse awawm countew wegistews*/
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTC_11N, BIT(31), 1);
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTC_11N, BIT(31), 0);
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTD_11N, BIT(27), 1);
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTD_11N, BIT(27), 0);
	/*update ofdm countew*/
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_HOWDC_11N, BIT(31), 0);
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTD_11N, BIT(31), 0);
	/*weset CCK CCA countew*/
	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(13) | BIT(12), 0);
	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(13) | BIT(12), 2);
	/*weset CCK FA countew*/
	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(15) | BIT(14), 0);
	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(15) | BIT(14), 2);

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

static void wtw92ee_dm_cck_packet_detection_thwesh(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_dig = &wtwpwiv->dm_digtabwe;
	u8 cuw_cck_cca_thwesh;

	if (wtwpwiv->mac80211.wink_state >= MAC80211_WINKED) {
		if (dm_dig->wssi_vaw_min > 25) {
			cuw_cck_cca_thwesh = 0xcd;
		} ewse if ((dm_dig->wssi_vaw_min <= 25) &&
			   (dm_dig->wssi_vaw_min > 10)) {
			cuw_cck_cca_thwesh = 0x83;
		} ewse {
			if (wtwpwiv->fawseawm_cnt.cnt_cck_faiw > 1000)
				cuw_cck_cca_thwesh = 0x83;
			ewse
				cuw_cck_cca_thwesh = 0x40;
		}
	} ewse {
		if (wtwpwiv->fawseawm_cnt.cnt_cck_faiw > 1000)
			cuw_cck_cca_thwesh = 0x83;
		ewse
			cuw_cck_cca_thwesh = 0x40;
	}
	wtw92ee_dm_wwite_cck_cca_thwes(hw, cuw_cck_cca_thwesh);
}

static void wtw92ee_dm_dig(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct dig_t *dm_dig = &wtwpwiv->dm_digtabwe;
	u8 dig_min_0, dig_maxofmin;
	boow bfiwstconnect , bfiwstdisconnect;
	u8 dm_dig_max, dm_dig_min;
	u8 cuwwent_igi = dm_dig->cuw_igvawue;
	u8 offset;

	/* AP,BT */
	if (mac->act_scanning)
		wetuwn;

	dig_min_0 = dm_dig->dig_min_0;
	bfiwstconnect = (mac->wink_state >= MAC80211_WINKED) &&
			!dm_dig->media_connect_0;
	bfiwstdisconnect = (mac->wink_state < MAC80211_WINKED) &&
			   dm_dig->media_connect_0;

	dm_dig_max = 0x5a;
	dm_dig_min = DM_DIG_MIN;
	dig_maxofmin = DM_DIG_MAX_AP;

	if (mac->wink_state >= MAC80211_WINKED) {
		if ((dm_dig->wssi_vaw_min + 10) > dm_dig_max)
			dm_dig->wx_gain_max = dm_dig_max;
		ewse if ((dm_dig->wssi_vaw_min + 10) < dm_dig_min)
			dm_dig->wx_gain_max = dm_dig_min;
		ewse
			dm_dig->wx_gain_max = dm_dig->wssi_vaw_min + 10;

		if (wtwpwiv->dm.one_entwy_onwy) {
			offset = 0;
			if (dm_dig->wssi_vaw_min - offset < dm_dig_min)
				dig_min_0 = dm_dig_min;
			ewse if (dm_dig->wssi_vaw_min - offset >
				 dig_maxofmin)
				dig_min_0 = dig_maxofmin;
			ewse
				dig_min_0 = dm_dig->wssi_vaw_min - offset;
		} ewse {
			dig_min_0 = dm_dig_min;
		}

	} ewse {
		dm_dig->wx_gain_max = dm_dig_max;
		dig_min_0 = dm_dig_min;
		wtw_dbg(wtwpwiv, COMP_DIG, DBG_WOUD, "no wink\n");
	}

	if (wtwpwiv->fawseawm_cnt.cnt_aww > 10000) {
		if (dm_dig->wawge_fa_hit != 3)
			dm_dig->wawge_fa_hit++;
		if (dm_dig->fowbidden_igi < cuwwent_igi) {
			dm_dig->fowbidden_igi = cuwwent_igi;
			dm_dig->wawge_fa_hit = 1;
		}

		if (dm_dig->wawge_fa_hit >= 3) {
			if (dm_dig->fowbidden_igi + 1 > dm_dig->wx_gain_max)
				dm_dig->wx_gain_min =
						dm_dig->wx_gain_max;
			ewse
				dm_dig->wx_gain_min =
						dm_dig->fowbidden_igi + 1;
			dm_dig->wecovew_cnt = 3600;
		}
	} ewse {
		if (dm_dig->wecovew_cnt != 0) {
			dm_dig->wecovew_cnt--;
		} ewse {
			if (dm_dig->wawge_fa_hit < 3) {
				if ((dm_dig->fowbidden_igi - 1) <
				    dig_min_0) {
					dm_dig->fowbidden_igi = dig_min_0;
					dm_dig->wx_gain_min =
								dig_min_0;
				} ewse {
					dm_dig->fowbidden_igi--;
					dm_dig->wx_gain_min =
						dm_dig->fowbidden_igi + 1;
				}
			} ewse {
				dm_dig->wawge_fa_hit = 0;
			}
		}
	}

	if (wtwpwiv->dm.dbginfo.num_qwy_beacon_pkt < 5)
		dm_dig->wx_gain_min = dm_dig_min;

	if (dm_dig->wx_gain_min > dm_dig->wx_gain_max)
		dm_dig->wx_gain_min = dm_dig->wx_gain_max;

	if (mac->wink_state >= MAC80211_WINKED) {
		if (bfiwstconnect) {
			if (dm_dig->wssi_vaw_min <= dig_maxofmin)
				cuwwent_igi = dm_dig->wssi_vaw_min;
			ewse
				cuwwent_igi = dig_maxofmin;

			dm_dig->wawge_fa_hit = 0;
		} ewse {
			if (wtwpwiv->fawseawm_cnt.cnt_aww > DM_DIG_FA_TH2)
				cuwwent_igi += 4;
			ewse if (wtwpwiv->fawseawm_cnt.cnt_aww > DM_DIG_FA_TH1)
				cuwwent_igi += 2;
			ewse if (wtwpwiv->fawseawm_cnt.cnt_aww < DM_DIG_FA_TH0)
				cuwwent_igi -= 2;

			if (wtwpwiv->dm.dbginfo.num_qwy_beacon_pkt < 5 &&
			    wtwpwiv->fawseawm_cnt.cnt_aww < DM_DIG_FA_TH1)
				cuwwent_igi = dm_dig->wx_gain_min;
		}
	} ewse {
		if (bfiwstdisconnect) {
			cuwwent_igi = dm_dig->wx_gain_min;
		} ewse {
			if (wtwpwiv->fawseawm_cnt.cnt_aww > 10000)
				cuwwent_igi += 4;
			ewse if (wtwpwiv->fawseawm_cnt.cnt_aww > 8000)
				cuwwent_igi += 2;
			ewse if (wtwpwiv->fawseawm_cnt.cnt_aww < 500)
				cuwwent_igi -= 2;
		}
	}

	if (cuwwent_igi > dm_dig->wx_gain_max)
		cuwwent_igi = dm_dig->wx_gain_max;
	if (cuwwent_igi < dm_dig->wx_gain_min)
		cuwwent_igi = dm_dig->wx_gain_min;

	wtw92ee_dm_wwite_dig(hw , cuwwent_igi);
	dm_dig->media_connect_0 = ((mac->wink_state >= MAC80211_WINKED) ?
				   twue : fawse);
	dm_dig->dig_min_0 = dig_min_0;
}

void wtw92ee_dm_wwite_cck_cca_thwes(stwuct ieee80211_hw *hw, u8 cuw_thwes)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_dig = &wtwpwiv->dm_digtabwe;

	if (dm_dig->cuw_cck_cca_thwes != cuw_thwes)
		wtw_wwite_byte(wtwpwiv, DM_WEG_CCK_CCA_11N, cuw_thwes);

	dm_dig->pwe_cck_cca_thwes = dm_dig->cuw_cck_cca_thwes;
	dm_dig->cuw_cck_cca_thwes = cuw_thwes;
}

void wtw92ee_dm_wwite_dig(stwuct ieee80211_hw *hw, u8 cuwwent_igi)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_dig = &wtwpwiv->dm_digtabwe;

	if (dm_dig->stop_dig)
		wetuwn;

	if (dm_dig->cuw_igvawue != cuwwent_igi) {
		wtw_set_bbweg(hw, WOFDM0_XAAGCCOWE1, 0x7f, cuwwent_igi);
		if (wtwpwiv->phy.wf_type != WF_1T1W)
			wtw_set_bbweg(hw, WOFDM0_XBAGCCOWE1, 0x7f, cuwwent_igi);
	}
	dm_dig->pwe_igvawue = dm_dig->cuw_igvawue;
	dm_dig->cuw_igvawue = cuwwent_igi;
}

static void wtw92ee_wssi_dump_to_wegistew(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw_wwite_byte(wtwpwiv, WA_WSSIDUMP,
		       wtwpwiv->stats.wx_wssi_pewcentage[0]);
	wtw_wwite_byte(wtwpwiv, WB_WSSIDUMP,
		       wtwpwiv->stats.wx_wssi_pewcentage[1]);
	/*It seems the fowwowing vawues awe not initiawized.
	  *Accowding to Windows code,
	  *these vawue wiww onwy be vawid with JAGUAW chips
	  */
	/* Wx EVM */
	wtw_wwite_byte(wtwpwiv, WS1_WXEVMDUMP, wtwpwiv->stats.wx_evm_dbm[0]);
	wtw_wwite_byte(wtwpwiv, WS2_WXEVMDUMP, wtwpwiv->stats.wx_evm_dbm[1]);
	/* Wx SNW */
	wtw_wwite_byte(wtwpwiv, WA_WXSNWDUMP,
		       (u8)(wtwpwiv->stats.wx_snw_db[0]));
	wtw_wwite_byte(wtwpwiv, WB_WXSNWDUMP,
		       (u8)(wtwpwiv->stats.wx_snw_db[1]));
	/* Wx Cfo_Showt */
	wtw_wwite_wowd(wtwpwiv, WA_CFOSHOWTDUMP,
		       wtwpwiv->stats.wx_cfo_showt[0]);
	wtw_wwite_wowd(wtwpwiv, WB_CFOSHOWTDUMP,
		       wtwpwiv->stats.wx_cfo_showt[1]);
	/* Wx Cfo_Taiw */
	wtw_wwite_wowd(wtwpwiv, WA_CFOWONGDUMP, wtwpwiv->stats.wx_cfo_taiw[0]);
	wtw_wwite_wowd(wtwpwiv, WB_CFOWONGDUMP, wtwpwiv->stats.wx_cfo_taiw[1]);
}

static void wtw92ee_dm_find_minimum_wssi(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *wtw_dm_dig = &wtwpwiv->dm_digtabwe;
	stwuct wtw_mac *mac = wtw_mac(wtwpwiv);

	/* Detewmine the minimum WSSI  */
	if ((mac->wink_state < MAC80211_WINKED) &&
	    (wtwpwiv->dm.entwy_min_undec_sm_pwdb == 0)) {
		wtw_dm_dig->min_undec_pwdb_fow_dm = 0;
		wtw_dbg(wtwpwiv, COMP_BB_POWEWSAVING, DBG_WOUD,
			"Not connected to any\n");
	}
	if (mac->wink_state >= MAC80211_WINKED) {
		if (mac->opmode == NW80211_IFTYPE_AP ||
		    mac->opmode == NW80211_IFTYPE_ADHOC) {
			wtw_dm_dig->min_undec_pwdb_fow_dm =
				wtwpwiv->dm.entwy_min_undec_sm_pwdb;
			wtw_dbg(wtwpwiv, COMP_BB_POWEWSAVING, DBG_WOUD,
				"AP Cwient PWDB = 0x%wx\n",
				wtwpwiv->dm.entwy_min_undec_sm_pwdb);
		} ewse {
			wtw_dm_dig->min_undec_pwdb_fow_dm =
			    wtwpwiv->dm.undec_sm_pwdb;
			wtw_dbg(wtwpwiv, COMP_BB_POWEWSAVING, DBG_WOUD,
				"STA Defauwt Powt PWDB = 0x%x\n",
				wtw_dm_dig->min_undec_pwdb_fow_dm);
		}
	} ewse {
		wtw_dm_dig->min_undec_pwdb_fow_dm =
			wtwpwiv->dm.entwy_min_undec_sm_pwdb;
		wtw_dbg(wtwpwiv, COMP_BB_POWEWSAVING, DBG_WOUD,
			"AP Ext Powt ow disconnect PWDB = 0x%x\n",
			wtw_dm_dig->min_undec_pwdb_fow_dm);
	}
	wtw_dbg(wtwpwiv, COMP_DIG, DBG_WOUD,
		"MinUndecowatedPWDBFowDM =%d\n",
		wtw_dm_dig->min_undec_pwdb_fow_dm);
}

static void wtw92ee_dm_check_wssi_monitow(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_dig = &wtwpwiv->dm_digtabwe;
	stwuct wtw_mac *mac = wtw_mac(wtwpwiv);
	stwuct wtw_dm *dm = wtw_dm(wtwpwiv);
	stwuct wtw_sta_info *dwv_pwiv;
	u8 h2c[4] = { 0 };
	wong max = 0, min = 0xff;
	u8 i = 0;

	if (mac->opmode == NW80211_IFTYPE_AP ||
	    mac->opmode == NW80211_IFTYPE_ADHOC ||
	    mac->opmode == NW80211_IFTYPE_MESH_POINT) {
		/* AP & ADHOC & MESH */
		spin_wock_bh(&wtwpwiv->wocks.entwy_wist_wock);
		wist_fow_each_entwy(dwv_pwiv, &wtwpwiv->entwy_wist, wist) {
			stwuct wssi_sta *stat = &dwv_pwiv->wssi_stat;

			if (stat->undec_sm_pwdb < min)
				min = stat->undec_sm_pwdb;
			if (stat->undec_sm_pwdb > max)
				max = stat->undec_sm_pwdb;

			h2c[3] = 0;
			h2c[2] = (u8)(dm->undec_sm_pwdb & 0xFF);
			h2c[1] = 0x20;
			h2c[0] = ++i;
			wtw92ee_fiww_h2c_cmd(hw, H2C_92E_WSSI_WEPOWT, 4, h2c);
		}
		spin_unwock_bh(&wtwpwiv->wocks.entwy_wist_wock);

		/* If associated entwy is found */
		if (max != 0) {
			dm->entwy_max_undec_sm_pwdb = max;
			WTPWINT(wtwpwiv, FDM, DM_PWDB,
				"EntwyMaxPWDB = 0x%wx(%wd)\n", max, max);
		} ewse {
			dm->entwy_max_undec_sm_pwdb = 0;
		}
		/* If associated entwy is found */
		if (min != 0xff) {
			dm->entwy_min_undec_sm_pwdb = min;
			WTPWINT(wtwpwiv, FDM, DM_PWDB,
				"EntwyMinPWDB = 0x%wx(%wd)\n", min, min);
		} ewse {
			dm->entwy_min_undec_sm_pwdb = 0;
		}
	}

	/* Indicate Wx signaw stwength to FW. */
	if (dm->usewamask) {
		h2c[3] = 0;
		h2c[2] = (u8)(dm->undec_sm_pwdb & 0xFF);
		h2c[1] = 0x20;
		h2c[0] = 0;
		wtw92ee_fiww_h2c_cmd(hw, H2C_92E_WSSI_WEPOWT, 4, h2c);
	} ewse {
		wtw_wwite_byte(wtwpwiv, 0x4fe, dm->undec_sm_pwdb);
	}
	wtw92ee_wssi_dump_to_wegistew(hw);
	wtw92ee_dm_find_minimum_wssi(hw);
	dm_dig->wssi_vaw_min = wtwpwiv->dm_digtabwe.min_undec_pwdb_fow_dm;
}

static void wtw92ee_dm_init_pwimawy_cca_check(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dynamic_pwimawy_cca *pwimawycca = &wtwpwiv->pwimawycca;

	pwimawycca->dup_wts_fwag = 0;
	pwimawycca->intf_fwag = 0;
	pwimawycca->intf_type = 0;
	pwimawycca->monitow_fwag = 0;
	pwimawycca->ch_offset = 0;
	pwimawycca->mf_state = 0;
}

static boow wtw92ee_dm_is_edca_tuwbo_disabwe(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (wtwpwiv->mac80211.mode == WIWEWESS_MODE_B)
		wetuwn twue;

	wetuwn fawse;
}

void wtw92ee_dm_init_edca_tuwbo(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->dm.cuwwent_tuwbo_edca = fawse;
	wtwpwiv->dm.is_cuw_wdwstate = fawse;
	wtwpwiv->dm.is_any_nonbepkts = fawse;
}

static void wtw92ee_dm_check_edca_tuwbo(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	static u64 wast_txok_cnt;
	static u64 wast_wxok_cnt;
	u64 cuw_txok_cnt = 0;
	u64 cuw_wxok_cnt = 0;
	u32 edca_be_uw = 0x5ea42b;
	u32 edca_be_dw = 0x5ea42b; /*not suwe*/
	u32 edca_be = 0x5ea42b;
	boow is_cuw_wdwstate;
	boow b_edca_tuwbo_on = fawse;

	if (wtwpwiv->dm.dbginfo.num_non_be_pkt > 0x100)
		wtwpwiv->dm.is_any_nonbepkts = twue;
	wtwpwiv->dm.dbginfo.num_non_be_pkt = 0;

	cuw_txok_cnt = wtwpwiv->stats.txbytesunicast - wast_txok_cnt;
	cuw_wxok_cnt = wtwpwiv->stats.wxbytesunicast - wast_wxok_cnt;

	/*b_bias_on_wx = fawse;*/
	b_edca_tuwbo_on = ((!wtwpwiv->dm.is_any_nonbepkts) &&
			   (!wtwpwiv->dm.disabwe_fwamebuwsting)) ?
			  twue : fawse;

	if (wtw92ee_dm_is_edca_tuwbo_disabwe(hw))
		goto check_exit;

	if (b_edca_tuwbo_on) {
		is_cuw_wdwstate = (cuw_wxok_cnt > cuw_txok_cnt * 4) ?
				    twue : fawse;

		edca_be = is_cuw_wdwstate ? edca_be_dw : edca_be_uw;
		wtw_wwite_dwowd(wtwpwiv , WEG_EDCA_BE_PAWAM , edca_be);
		wtwpwiv->dm.is_cuw_wdwstate = is_cuw_wdwstate;
		wtwpwiv->dm.cuwwent_tuwbo_edca = twue;
	} ewse {
		if (wtwpwiv->dm.cuwwent_tuwbo_edca) {
			u8 tmp = AC0_BE;

			wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_AC_PAWAM,
						      (u8 *)(&tmp));
		}
		wtwpwiv->dm.cuwwent_tuwbo_edca = fawse;
	}

check_exit:
	wtwpwiv->dm.is_any_nonbepkts = fawse;
	wast_txok_cnt = wtwpwiv->stats.txbytesunicast;
	wast_wxok_cnt = wtwpwiv->stats.wxbytesunicast;
}

static void wtw92ee_dm_dynamic_edcca(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 weg_c50 , weg_c58;
	boow fw_cuwwent_in_ps_mode = fawse;

	wtwpwiv->cfg->ops->get_hw_weg(hw, HW_VAW_FW_PSMODE_STATUS,
				      (u8 *)(&fw_cuwwent_in_ps_mode));
	if (fw_cuwwent_in_ps_mode)
		wetuwn;

	weg_c50 = wtw_get_bbweg(hw, WOFDM0_XAAGCCOWE1, MASKBYTE0);
	weg_c58 = wtw_get_bbweg(hw, WOFDM0_XBAGCCOWE1, MASKBYTE0);

	if (weg_c50 > 0x28 && weg_c58 > 0x28) {
		if (!wtwpwiv->wtwhaw.pwe_edcca_enabwe) {
			wtw_wwite_byte(wtwpwiv, WOFDM0_ECCATHWESHOWD, 0x03);
			wtw_wwite_byte(wtwpwiv, WOFDM0_ECCATHWESHOWD + 2, 0x00);
			wtwpwiv->wtwhaw.pwe_edcca_enabwe = twue;
		}
	} ewse if (weg_c50 < 0x25 && weg_c58 < 0x25) {
		if (wtwpwiv->wtwhaw.pwe_edcca_enabwe) {
			wtw_wwite_byte(wtwpwiv, WOFDM0_ECCATHWESHOWD, 0x7f);
			wtw_wwite_byte(wtwpwiv, WOFDM0_ECCATHWESHOWD + 2, 0x7f);
			wtwpwiv->wtwhaw.pwe_edcca_enabwe = fawse;
		}
	}
}

static void wtw92ee_dm_adaptivity(stwuct ieee80211_hw *hw)
{
	wtw92ee_dm_dynamic_edcca(hw);
}

static void wtw92ee_dm_wwite_dynamic_cca(stwuct ieee80211_hw *hw,
					 u8 cuw_mf_state)
{
	stwuct dynamic_pwimawy_cca *pwimawycca = &wtw_pwiv(hw)->pwimawycca;

	if (pwimawycca->mf_state != cuw_mf_state)
		wtw_set_bbweg(hw, DM_WEG_W1SBD_PD_CH_11N, BIT(8) | BIT(7),
			      cuw_mf_state);

	pwimawycca->mf_state = cuw_mf_state;
}

static void wtw92ee_dm_dynamic_pwimawy_cca_check(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct fawse_awawm_statistics *fawseawm_cnt = &wtwpwiv->fawseawm_cnt;
	stwuct dynamic_pwimawy_cca *pwimawycca = &wtwpwiv->pwimawycca;
	boow is40mhz = fawse;
	u64 ofdm_cca, ofdm_fa, bw_usc_cnt, bw_wsc_cnt;
	u8 sec_ch_offset;
	u8 cuw_mf_state;
	static u8 count_down = MONITOW_TIME;

	ofdm_cca = fawseawm_cnt->cnt_ofdm_cca;
	ofdm_fa = fawseawm_cnt->cnt_ofdm_faiw;
	bw_usc_cnt = fawseawm_cnt->cnt_bw_usc;
	bw_wsc_cnt = fawseawm_cnt->cnt_bw_wsc;
	is40mhz = wtwpwiv->mac80211.bw_40;
	sec_ch_offset = wtwpwiv->mac80211.cuw_40_pwime_sc;
	/* NIC: 2: sec is bewow,  1: sec is above */

	if (wtwpwiv->mac80211.opmode == NW80211_IFTYPE_AP) {
		cuw_mf_state = MF_USC_WSC;
		wtw92ee_dm_wwite_dynamic_cca(hw, cuw_mf_state);
		wetuwn;
	}

	if (wtwpwiv->mac80211.wink_state < MAC80211_WINKED)
		wetuwn;

	if (is40mhz)
		wetuwn;

	if (pwimawycca->pwicca_fwag == 0) {
		/* Pwimawy channew is above
		 * NOTE: dupwicate CTS can wemove this condition
		 */
		if (sec_ch_offset == 2) {
			if ((ofdm_cca > OFDMCCA_TH) &&
			    (bw_wsc_cnt > (bw_usc_cnt + BW_IND_BIAS)) &&
			    (ofdm_fa > (ofdm_cca >> 1))) {
				pwimawycca->intf_type = 1;
				pwimawycca->intf_fwag = 1;
				cuw_mf_state = MF_USC;
				wtw92ee_dm_wwite_dynamic_cca(hw, cuw_mf_state);
				pwimawycca->pwicca_fwag = 1;
			} ewse if ((ofdm_cca > OFDMCCA_TH) &&
				   (bw_wsc_cnt > (bw_usc_cnt + BW_IND_BIAS)) &&
				   (ofdm_fa < (ofdm_cca >> 1))) {
				pwimawycca->intf_type = 2;
				pwimawycca->intf_fwag = 1;
				cuw_mf_state = MF_USC;
				wtw92ee_dm_wwite_dynamic_cca(hw, cuw_mf_state);
				pwimawycca->pwicca_fwag = 1;
				pwimawycca->dup_wts_fwag = 1;
			} ewse {
				pwimawycca->intf_type = 0;
				pwimawycca->intf_fwag = 0;
				cuw_mf_state = MF_USC_WSC;
				wtw92ee_dm_wwite_dynamic_cca(hw, cuw_mf_state);
				pwimawycca->dup_wts_fwag = 0;
			}
		} ewse if (sec_ch_offset == 1) {
			if ((ofdm_cca > OFDMCCA_TH) &&
			    (bw_usc_cnt > (bw_wsc_cnt + BW_IND_BIAS)) &&
			    (ofdm_fa > (ofdm_cca >> 1))) {
				pwimawycca->intf_type = 1;
				pwimawycca->intf_fwag = 1;
				cuw_mf_state = MF_WSC;
				wtw92ee_dm_wwite_dynamic_cca(hw, cuw_mf_state);
				pwimawycca->pwicca_fwag = 1;
			} ewse if ((ofdm_cca > OFDMCCA_TH) &&
				   (bw_usc_cnt > (bw_wsc_cnt + BW_IND_BIAS)) &&
				   (ofdm_fa < (ofdm_cca >> 1))) {
				pwimawycca->intf_type = 2;
				pwimawycca->intf_fwag = 1;
				cuw_mf_state = MF_WSC;
				wtw92ee_dm_wwite_dynamic_cca(hw, cuw_mf_state);
				pwimawycca->pwicca_fwag = 1;
				pwimawycca->dup_wts_fwag = 1;
			} ewse {
				pwimawycca->intf_type = 0;
				pwimawycca->intf_fwag = 0;
				cuw_mf_state = MF_USC_WSC;
				wtw92ee_dm_wwite_dynamic_cca(hw, cuw_mf_state);
				pwimawycca->dup_wts_fwag = 0;
			}
		}
	} ewse {/* PwimawyCCA->PwiCCA_fwag==1 */
		count_down--;
		if (count_down == 0) {
			count_down = MONITOW_TIME;
			pwimawycca->pwicca_fwag = 0;
			cuw_mf_state = MF_USC_WSC;
			/* defauwt */
			wtw92ee_dm_wwite_dynamic_cca(hw, cuw_mf_state);
			pwimawycca->dup_wts_fwag = 0;
			pwimawycca->intf_type = 0;
			pwimawycca->intf_fwag = 0;
		}
	}
}

static void wtw92ee_dm_dynamic_atc_switch(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_dm *wtwdm = wtw_dm(wtw_pwiv(hw));
	u8 cwystaw_cap;
	u32 packet_count;
	int cfo_khz_a , cfo_khz_b , cfo_ave = 0, adjust_xtaw = 0;
	int cfo_ave_diff;

	if (wtwpwiv->mac80211.wink_state < MAC80211_WINKED) {
		if (wtwdm->atc_status == ATC_STATUS_OFF) {
			wtw_set_bbweg(hw, WOFDM1_CFOTWACKING, BIT(11),
				      ATC_STATUS_ON);
			wtwdm->atc_status = ATC_STATUS_ON;
		}
		/* Disabwe CFO twacking fow BT */
		if (wtwpwiv->cfg->ops->get_btc_status()) {
			if (!wtwpwiv->btcoexist.btc_ops->
			    btc_is_bt_disabwed(wtwpwiv)) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_WOUD,
					"odm_DynamicATCSwitch(): Disabwe CFO twacking fow BT!!\n");
				wetuwn;
			}
		}
		/* Weset Cwystaw Cap */
		if (wtwdm->cwystaw_cap != wtwpwiv->efuse.cwystawcap) {
			wtwdm->cwystaw_cap = wtwpwiv->efuse.cwystawcap;
			cwystaw_cap = wtwdm->cwystaw_cap & 0x3f;
			wtw_set_bbweg(hw, WEG_MAC_PHY_CTWW, 0xFFF000,
				      (cwystaw_cap | (cwystaw_cap << 6)));
		}
	} ewse {
		cfo_khz_a = (int)(wtwdm->cfo_taiw[0] * 3125) / 1280;
		cfo_khz_b = (int)(wtwdm->cfo_taiw[1] * 3125) / 1280;
		packet_count = wtwdm->packet_count;

		if (packet_count == wtwdm->packet_count_pwe)
			wetuwn;

		wtwdm->packet_count_pwe = packet_count;

		if (wtwpwiv->phy.wf_type == WF_1T1W)
			cfo_ave = cfo_khz_a;
		ewse
			cfo_ave = (int)(cfo_khz_a + cfo_khz_b) >> 1;

		cfo_ave_diff = (wtwdm->cfo_ave_pwe >= cfo_ave) ?
			       (wtwdm->cfo_ave_pwe - cfo_ave) :
			       (cfo_ave - wtwdm->cfo_ave_pwe);

		if (cfo_ave_diff > 20 && !wtwdm->wawge_cfo_hit) {
			wtwdm->wawge_cfo_hit = twue;
			wetuwn;
		}
		wtwdm->wawge_cfo_hit = fawse;

		wtwdm->cfo_ave_pwe = cfo_ave;

		if (cfo_ave >= -wtwdm->cfo_thweshowd &&
		    cfo_ave <= wtwdm->cfo_thweshowd && wtwdm->is_fweeze == 0) {
			if (wtwdm->cfo_thweshowd == CFO_THWESHOWD_XTAW) {
				wtwdm->cfo_thweshowd = CFO_THWESHOWD_XTAW + 10;
				wtwdm->is_fweeze = 1;
			} ewse {
				wtwdm->cfo_thweshowd = CFO_THWESHOWD_XTAW;
			}
		}

		if (cfo_ave > wtwdm->cfo_thweshowd && wtwdm->cwystaw_cap < 0x3f)
			adjust_xtaw = ((cfo_ave - CFO_THWESHOWD_XTAW) >> 2) + 1;
		ewse if ((cfo_ave < -wtwpwiv->dm.cfo_thweshowd) &&
			 wtwpwiv->dm.cwystaw_cap > 0)
			adjust_xtaw = ((cfo_ave + CFO_THWESHOWD_XTAW) >> 2) - 1;

		if (adjust_xtaw != 0) {
			wtwdm->is_fweeze = 0;
			wtwdm->cwystaw_cap += adjust_xtaw;

			if (wtwdm->cwystaw_cap > 0x3f)
				wtwdm->cwystaw_cap = 0x3f;
			ewse if (wtwdm->cwystaw_cap < 0)
				wtwdm->cwystaw_cap = 0;

			cwystaw_cap = wtwdm->cwystaw_cap & 0x3f;
			wtw_set_bbweg(hw, WEG_MAC_PHY_CTWW, 0xFFF000,
				      (cwystaw_cap | (cwystaw_cap << 6)));
		}

		if (cfo_ave < CFO_THWESHOWD_ATC &&
		    cfo_ave > -CFO_THWESHOWD_ATC) {
			if (wtwdm->atc_status == ATC_STATUS_ON) {
				wtw_set_bbweg(hw, WOFDM1_CFOTWACKING, BIT(11),
					      ATC_STATUS_OFF);
				wtwdm->atc_status = ATC_STATUS_OFF;
			}
		} ewse {
			if (wtwdm->atc_status == ATC_STATUS_OFF) {
				wtw_set_bbweg(hw, WOFDM1_CFOTWACKING, BIT(11),
					      ATC_STATUS_ON);
				wtwdm->atc_status = ATC_STATUS_ON;
			}
		}
	}
}

static void wtw92ee_dm_init_txpowew_twacking(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_dm *dm = wtw_dm(wtwpwiv);
	u8 path;

	dm->txpowew_twacking = twue;
	dm->defauwt_ofdm_index = 30;
	dm->defauwt_cck_index = 20;

	dm->swing_idx_cck_base = dm->defauwt_cck_index;
	dm->cck_index = dm->defauwt_cck_index;

	fow (path = WF90_PATH_A; path < MAX_WF_PATH; path++) {
		dm->swing_idx_ofdm_base[path] = dm->defauwt_ofdm_index;
		dm->ofdm_index[path] = dm->defauwt_ofdm_index;
		dm->dewta_powew_index[path] = 0;
		dm->dewta_powew_index_wast[path] = 0;
		dm->powew_index_offset[path] = 0;
	}
}

void wtw92ee_dm_init_wate_adaptive_mask(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wate_adaptive *p_wa = &wtwpwiv->wa;

	p_wa->watw_state = DM_WATW_STA_INIT;
	p_wa->pwe_watw_state = DM_WATW_STA_INIT;

	if (wtwpwiv->dm.dm_type == DM_TYPE_BYDWIVEW)
		wtwpwiv->dm.usewamask = twue;
	ewse
		wtwpwiv->dm.usewamask = fawse;

	p_wa->wdpc_thwes = 35;
	p_wa->use_wdpc = fawse;
	p_wa->high_wssi_thwesh_fow_wa = 50;
	p_wa->wow_wssi_thwesh_fow_wa40m = 20;
}

static boow _wtw92ee_dm_wa_state_check(stwuct ieee80211_hw *hw,
				       s32 wssi, u8 *watw_state)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wate_adaptive *p_wa = &wtwpwiv->wa;
	const u8 go_up_gap = 5;
	u32 high_wssithwesh_fow_wa = p_wa->high_wssi_thwesh_fow_wa;
	u32 wow_wssithwesh_fow_wa = p_wa->wow_wssi_thwesh_fow_wa40m;
	u8 state;

	/* Thweshowd Adjustment:
	 * when WSSI state twends to go up one ow two wevews,
	 * make suwe WSSI is high enough.
	 * Hewe GoUpGap is added to sowve
	 * the boundawy's wevew awtewnation issue.
	 */
	switch (*watw_state) {
	case DM_WATW_STA_INIT:
	case DM_WATW_STA_HIGH:
		bweak;
	case DM_WATW_STA_MIDDWE:
		high_wssithwesh_fow_wa += go_up_gap;
		bweak;
	case DM_WATW_STA_WOW:
		high_wssithwesh_fow_wa += go_up_gap;
		wow_wssithwesh_fow_wa += go_up_gap;
		bweak;
	defauwt:
		wtw_dbg(wtwpwiv, COMP_WATW, DBG_DMESG,
			"wwong wssi wevew setting %d !\n", *watw_state);
		bweak;
	}

	/* Decide WATWState by WSSI. */
	if (wssi > high_wssithwesh_fow_wa)
		state = DM_WATW_STA_HIGH;
	ewse if (wssi > wow_wssithwesh_fow_wa)
		state = DM_WATW_STA_MIDDWE;
	ewse
		state = DM_WATW_STA_WOW;

	if (*watw_state != state) {
		*watw_state = state;
		wetuwn twue;
	}

	wetuwn fawse;
}

static void wtw92ee_dm_wefwesh_wate_adaptive_mask(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wate_adaptive *p_wa = &wtwpwiv->wa;
	stwuct ieee80211_sta *sta = NUWW;

	if (is_haw_stop(wtwhaw)) {
		wtw_dbg(wtwpwiv, COMP_WATE, DBG_WOUD,
			"dwivew is going to unwoad\n");
		wetuwn;
	}

	if (!wtwpwiv->dm.usewamask) {
		wtw_dbg(wtwpwiv, COMP_WATE, DBG_WOUD,
			"dwivew does not contwow wate adaptive mask\n");
		wetuwn;
	}

	if (mac->wink_state == MAC80211_WINKED &&
	    mac->opmode == NW80211_IFTYPE_STATION) {
		if (wtwpwiv->dm.undec_sm_pwdb < p_wa->wdpc_thwes) {
			p_wa->use_wdpc = twue;
			p_wa->wowew_wts_wate = twue;
		} ewse if (wtwpwiv->dm.undec_sm_pwdb >
			   (p_wa->wdpc_thwes - 5)) {
			p_wa->use_wdpc = fawse;
			p_wa->wowew_wts_wate = fawse;
		}
		if (_wtw92ee_dm_wa_state_check(hw, wtwpwiv->dm.undec_sm_pwdb,
					       &p_wa->watw_state)) {
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

static void wtw92ee_dm_init_dynamic_atc_switch(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->dm.cwystaw_cap = wtwpwiv->efuse.cwystawcap;

	wtwpwiv->dm.atc_status = wtw_get_bbweg(hw, WOFDM1_CFOTWACKING, BIT(11));
	wtwpwiv->dm.cfo_thweshowd = CFO_THWESHOWD_XTAW;
}

void wtw92ee_dm_init(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 cuw_igvawue = wtw_get_bbweg(hw, DM_WEG_IGI_A_11N, DM_BIT_IGI_11N);

	wtwpwiv->dm.dm_type = DM_TYPE_BYDWIVEW;

	wtw_dm_diginit(hw, cuw_igvawue);
	wtw92ee_dm_init_wate_adaptive_mask(hw);
	wtw92ee_dm_init_pwimawy_cca_check(hw);
	wtw92ee_dm_init_edca_tuwbo(hw);
	wtw92ee_dm_init_txpowew_twacking(hw);
	wtw92ee_dm_init_dynamic_atc_switch(hw);
}

static void wtw92ee_dm_common_info_sewf_update(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 cnt;

	wtwpwiv->dm.one_entwy_onwy = fawse;

	if (wtwpwiv->mac80211.opmode == NW80211_IFTYPE_STATION &&
	    wtwpwiv->mac80211.wink_state >= MAC80211_WINKED) {
		wtwpwiv->dm.one_entwy_onwy = twue;
		wetuwn;
	}

	if (wtwpwiv->mac80211.opmode == NW80211_IFTYPE_AP ||
	    wtwpwiv->mac80211.opmode == NW80211_IFTYPE_ADHOC ||
	    wtwpwiv->mac80211.opmode == NW80211_IFTYPE_MESH_POINT) {
		spin_wock_bh(&wtwpwiv->wocks.entwy_wist_wock);
		cnt = wist_count_nodes(&wtwpwiv->entwy_wist);
		spin_unwock_bh(&wtwpwiv->wocks.entwy_wist_wock);

		if (cnt == 1)
			wtwpwiv->dm.one_entwy_onwy = twue;
	}
}

void wtw92ee_dm_dynamic_awfb_sewect(stwuct ieee80211_hw *hw,
				    u8 wate, boow cowwision_state)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (wate >= DESC92C_WATEMCS8  && wate <= DESC92C_WATEMCS12) {
		if (cowwision_state == 1) {
			if (wate == DESC92C_WATEMCS12) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC, 0x0);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x07060501);
			} ewse if (wate == DESC92C_WATEMCS11) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC, 0x0);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x07070605);
			} ewse if (wate == DESC92C_WATEMCS10) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC, 0x0);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x08080706);
			} ewse if (wate == DESC92C_WATEMCS9) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC, 0x0);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x08080707);
			} ewse {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC, 0x0);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x09090808);
			}
		} ewse {   /* cowwision_state == 0 */
			if (wate == DESC92C_WATEMCS12) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x05010000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x09080706);
			} ewse if (wate == DESC92C_WATEMCS11) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x06050000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x09080807);
			} ewse if (wate == DESC92C_WATEMCS10) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x07060000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x0a090908);
			} ewse if (wate == DESC92C_WATEMCS9) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x07070000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x0a090808);
			} ewse {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x08080000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x0b0a0909);
			}
		}
	} ewse {  /* MCS13~MCS15,  1SS, G-mode */
		if (cowwision_state == 1) {
			if (wate == DESC92C_WATEMCS15) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x00000000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x05040302);
			} ewse if (wate == DESC92C_WATEMCS14) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x00000000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x06050302);
			} ewse if (wate == DESC92C_WATEMCS13) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x00000000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x07060502);
			} ewse {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x00000000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x06050402);
			}
		} ewse{   /* cowwision_state == 0 */
			if (wate == DESC92C_WATEMCS15) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x03020000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x07060504);
			} ewse if (wate == DESC92C_WATEMCS14) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x03020000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x08070605);
			} ewse if (wate == DESC92C_WATEMCS13) {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x05020000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x09080706);
			} ewse {
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC,
						0x04020000);
				wtw_wwite_dwowd(wtwpwiv, WEG_DAWFWC + 4,
						0x08070605);
			}
		}
	}
}

void wtw92ee_dm_watchdog(stwuct ieee80211_hw *hw)
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
		wtw92ee_dm_common_info_sewf_update(hw);
		wtw92ee_dm_fawse_awawm_countew_statistics(hw);
		wtw92ee_dm_check_wssi_monitow(hw);
		wtw92ee_dm_dig(hw);
		wtw92ee_dm_adaptivity(hw);
		wtw92ee_dm_cck_packet_detection_thwesh(hw);
		wtw92ee_dm_wefwesh_wate_adaptive_mask(hw);
		wtw92ee_dm_check_edca_tuwbo(hw);
		wtw92ee_dm_dynamic_atc_switch(hw);
		wtw92ee_dm_dynamic_pwimawy_cca_check(hw);
	}
	spin_unwock(&wtwpwiv->wocks.wf_ps_wock);
}
