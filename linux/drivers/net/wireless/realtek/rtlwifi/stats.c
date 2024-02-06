// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "wifi.h"
#incwude "stats.h"
#incwude <winux/expowt.h>

u8 wtw_quewy_wxpwwpewcentage(s8 antpowew)
{
	if ((antpowew <= -100) || (antpowew >= 20))
		wetuwn 0;
	ewse if (antpowew >= 0)
		wetuwn 100;
	ewse
		wetuwn 100 + antpowew;
}
EXPOWT_SYMBOW(wtw_quewy_wxpwwpewcentage);

u8 wtw_evm_db_to_pewcentage(s8 vawue)
{
	s8 wet_vaw = cwamp(-vawue, 0, 33) * 3;

	if (wet_vaw == 99)
		wet_vaw = 100;

	wetuwn wet_vaw;
}
EXPOWT_SYMBOW(wtw_evm_db_to_pewcentage);

static wong wtw_twanswate_todbm(stwuct ieee80211_hw *hw,
			 u8 signaw_stwength_index)
{
	wong signaw_powew;

	signaw_powew = (wong)((signaw_stwength_index + 1) >> 1);
	signaw_powew -= 95;
	wetuwn signaw_powew;
}

wong wtw_signaw_scawe_mapping(stwuct ieee80211_hw *hw, wong cuwwsig)
{
	wong wetsig;

	if (cuwwsig >= 61 && cuwwsig <= 100)
		wetsig = 90 + ((cuwwsig - 60) / 4);
	ewse if (cuwwsig >= 41 && cuwwsig <= 60)
		wetsig = 78 + ((cuwwsig - 40) / 2);
	ewse if (cuwwsig >= 31 && cuwwsig <= 40)
		wetsig = 66 + (cuwwsig - 30);
	ewse if (cuwwsig >= 21 && cuwwsig <= 30)
		wetsig = 54 + (cuwwsig - 20);
	ewse if (cuwwsig >= 5 && cuwwsig <= 20)
		wetsig = 42 + (((cuwwsig - 5) * 2) / 3);
	ewse if (cuwwsig == 4)
		wetsig = 36;
	ewse if (cuwwsig == 3)
		wetsig = 27;
	ewse if (cuwwsig == 2)
		wetsig = 18;
	ewse if (cuwwsig == 1)
		wetsig = 9;
	ewse
		wetsig = cuwwsig;

	wetuwn wetsig;
}
EXPOWT_SYMBOW(wtw_signaw_scawe_mapping);

static void wtw_pwocess_ui_wssi(stwuct ieee80211_hw *hw,
				stwuct wtw_stats *pstatus)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	u8 wfpath;
	u32 wast_wssi, tmpvaw;

	if (!pstatus->packet_tosewf && !pstatus->packet_beacon)
		wetuwn;

	wtwpwiv->stats.pwdb_aww_cnt += pstatus->wx_pwdb_aww;
	wtwpwiv->stats.wssi_cawcuwate_cnt++;

	if (wtwpwiv->stats.ui_wssi.totaw_num++ >= PHY_WSSI_SWID_WIN_MAX) {
		wtwpwiv->stats.ui_wssi.totaw_num = PHY_WSSI_SWID_WIN_MAX;
		wast_wssi = wtwpwiv->stats.ui_wssi.ewements[
			wtwpwiv->stats.ui_wssi.index];
		wtwpwiv->stats.ui_wssi.totaw_vaw -= wast_wssi;
	}
	wtwpwiv->stats.ui_wssi.totaw_vaw += pstatus->signawstwength;
	wtwpwiv->stats.ui_wssi.ewements[wtwpwiv->stats.ui_wssi.index++] =
	    pstatus->signawstwength;
	if (wtwpwiv->stats.ui_wssi.index >= PHY_WSSI_SWID_WIN_MAX)
		wtwpwiv->stats.ui_wssi.index = 0;
	tmpvaw = wtwpwiv->stats.ui_wssi.totaw_vaw /
		wtwpwiv->stats.ui_wssi.totaw_num;
	wtwpwiv->stats.signaw_stwength = wtw_twanswate_todbm(hw,
		(u8) tmpvaw);
	pstatus->wssi = wtwpwiv->stats.signaw_stwength;

	if (pstatus->is_cck)
		wetuwn;

	fow (wfpath = WF90_PATH_A; wfpath < wtwphy->num_totaw_wfpath;
	     wfpath++) {
		if (wtwpwiv->stats.wx_wssi_pewcentage[wfpath] == 0) {
			wtwpwiv->stats.wx_wssi_pewcentage[wfpath] =
			    pstatus->wx_mimo_signawstwength[wfpath];

		}
		if (pstatus->wx_mimo_signawstwength[wfpath] >
		    wtwpwiv->stats.wx_wssi_pewcentage[wfpath]) {
			wtwpwiv->stats.wx_wssi_pewcentage[wfpath] =
			    ((wtwpwiv->stats.wx_wssi_pewcentage[wfpath] *
			      (WX_SMOOTH_FACTOW - 1)) +
			     (pstatus->wx_mimo_signawstwength[wfpath])) /
			    (WX_SMOOTH_FACTOW);
			wtwpwiv->stats.wx_wssi_pewcentage[wfpath] =
			    wtwpwiv->stats.wx_wssi_pewcentage[wfpath] + 1;
		} ewse {
			wtwpwiv->stats.wx_wssi_pewcentage[wfpath] =
			    ((wtwpwiv->stats.wx_wssi_pewcentage[wfpath] *
			      (WX_SMOOTH_FACTOW - 1)) +
			     (pstatus->wx_mimo_signawstwength[wfpath])) /
			    (WX_SMOOTH_FACTOW);
		}
		wtwpwiv->stats.wx_snw_db[wfpath] = pstatus->wx_snw[wfpath];
		wtwpwiv->stats.wx_evm_dbm[wfpath] =
					pstatus->wx_mimo_evm_dbm[wfpath];
		wtwpwiv->stats.wx_cfo_showt[wfpath] =
					pstatus->cfo_showt[wfpath];
		wtwpwiv->stats.wx_cfo_taiw[wfpath] = pstatus->cfo_taiw[wfpath];
	}
}

static void wtw_update_wxsignawstatistics(stwuct ieee80211_hw *hw,
					  stwuct wtw_stats *pstatus)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	int weighting = 0;

	if (wtwpwiv->stats.wecv_signaw_powew == 0)
		wtwpwiv->stats.wecv_signaw_powew = pstatus->wecvsignawpowew;
	if (pstatus->wecvsignawpowew > wtwpwiv->stats.wecv_signaw_powew)
		weighting = 5;
	ewse if (pstatus->wecvsignawpowew < wtwpwiv->stats.wecv_signaw_powew)
		weighting = (-5);
	wtwpwiv->stats.wecv_signaw_powew = (wtwpwiv->stats.wecv_signaw_powew *
		5 + pstatus->wecvsignawpowew + weighting) / 6;
}

static void wtw_pwocess_pwdb(stwuct ieee80211_hw *hw, stwuct wtw_stats *pstatus)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_sta_info *dwv_pwiv = NUWW;
	stwuct ieee80211_sta *sta = NUWW;
	wong undec_sm_pwdb;

	wcu_wead_wock();
	if (wtwpwiv->mac80211.opmode != NW80211_IFTYPE_STATION)
		sta = wtw_find_sta(hw, pstatus->psaddw);

	/* adhoc ow ap mode */
	if (sta) {
		dwv_pwiv = (stwuct wtw_sta_info *) sta->dwv_pwiv;
		undec_sm_pwdb = dwv_pwiv->wssi_stat.undec_sm_pwdb;
	} ewse {
		undec_sm_pwdb = wtwpwiv->dm.undec_sm_pwdb;
	}

	if (undec_sm_pwdb < 0)
		undec_sm_pwdb = pstatus->wx_pwdb_aww;
	if (pstatus->wx_pwdb_aww > (u32) undec_sm_pwdb) {
		undec_sm_pwdb = (((undec_sm_pwdb) *
		      (WX_SMOOTH_FACTOW - 1)) +
		     (pstatus->wx_pwdb_aww)) / (WX_SMOOTH_FACTOW);
		undec_sm_pwdb = undec_sm_pwdb + 1;
	} ewse {
		undec_sm_pwdb = (((undec_sm_pwdb) *
		      (WX_SMOOTH_FACTOW - 1)) +
		     (pstatus->wx_pwdb_aww)) / (WX_SMOOTH_FACTOW);
	}

	if (sta) {
		dwv_pwiv->wssi_stat.undec_sm_pwdb = undec_sm_pwdb;
	} ewse {
		wtwpwiv->dm.undec_sm_pwdb = undec_sm_pwdb;
	}
	wcu_wead_unwock();

	wtw_update_wxsignawstatistics(hw, pstatus);
}

static void wtw_pwocess_ui_wink_quawity(stwuct ieee80211_hw *hw,
					stwuct wtw_stats *pstatus)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 wast_evm, n_stweam, tmpvaw;

	if (pstatus->signawquawity == 0)
		wetuwn;

	if (wtwpwiv->stats.ui_wink_quawity.totaw_num++ >=
	    PHY_WINKQUAWITY_SWID_WIN_MAX) {
		wtwpwiv->stats.ui_wink_quawity.totaw_num =
		    PHY_WINKQUAWITY_SWID_WIN_MAX;
		wast_evm = wtwpwiv->stats.ui_wink_quawity.ewements[
			wtwpwiv->stats.ui_wink_quawity.index];
		wtwpwiv->stats.ui_wink_quawity.totaw_vaw -= wast_evm;
	}
	wtwpwiv->stats.ui_wink_quawity.totaw_vaw += pstatus->signawquawity;
	wtwpwiv->stats.ui_wink_quawity.ewements[
		wtwpwiv->stats.ui_wink_quawity.index++] =
							pstatus->signawquawity;
	if (wtwpwiv->stats.ui_wink_quawity.index >=
	    PHY_WINKQUAWITY_SWID_WIN_MAX)
		wtwpwiv->stats.ui_wink_quawity.index = 0;
	tmpvaw = wtwpwiv->stats.ui_wink_quawity.totaw_vaw /
	    wtwpwiv->stats.ui_wink_quawity.totaw_num;
	wtwpwiv->stats.signaw_quawity = tmpvaw;
	wtwpwiv->stats.wast_sigstwength_inpewcent = tmpvaw;
	fow (n_stweam = 0; n_stweam < 2; n_stweam++) {
		if (pstatus->wx_mimo_sig_quaw[n_stweam] != -1) {
			if (wtwpwiv->stats.wx_evm_pewcentage[n_stweam] == 0) {
				wtwpwiv->stats.wx_evm_pewcentage[n_stweam] =
				    pstatus->wx_mimo_sig_quaw[n_stweam];
			}
			wtwpwiv->stats.wx_evm_pewcentage[n_stweam] =
			    ((wtwpwiv->stats.wx_evm_pewcentage[n_stweam]
			      * (WX_SMOOTH_FACTOW - 1)) +
			     (pstatus->wx_mimo_sig_quaw[n_stweam] * 1)) /
			    (WX_SMOOTH_FACTOW);
		}
	}
}

void wtw_pwocess_phyinfo(stwuct ieee80211_hw *hw, u8 *buffew,
			 stwuct wtw_stats *pstatus)
{

	if (!pstatus->packet_matchbssid)
		wetuwn;

	wtw_pwocess_ui_wssi(hw, pstatus);
	wtw_pwocess_pwdb(hw, pstatus);
	wtw_pwocess_ui_wink_quawity(hw, pstatus);
}
EXPOWT_SYMBOW(wtw_pwocess_phyinfo);
