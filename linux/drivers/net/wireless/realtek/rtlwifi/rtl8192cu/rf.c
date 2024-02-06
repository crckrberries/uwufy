// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "wf.h"
#incwude "dm.h"

static boow _wtw92c_phy_wf6052_config_pawafiwe(stwuct ieee80211_hw *hw);

void wtw92cu_phy_wf6052_set_bandwidth(stwuct ieee80211_hw *hw, u8 bandwidth)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);

	switch (bandwidth) {
	case HT_CHANNEW_WIDTH_20:
		wtwphy->wfweg_chnwvaw[0] = ((wtwphy->wfweg_chnwvaw[0] &
					     0xfffff3ff) | 0x0400);
		wtw_set_wfweg(hw, WF90_PATH_A, WF_CHNWBW, WFWEG_OFFSET_MASK,
			      wtwphy->wfweg_chnwvaw[0]);
		bweak;
	case HT_CHANNEW_WIDTH_20_40:
		wtwphy->wfweg_chnwvaw[0] = ((wtwphy->wfweg_chnwvaw[0] &
					     0xfffff3ff));
		wtw_set_wfweg(hw, WF90_PATH_A, WF_CHNWBW, WFWEG_OFFSET_MASK,
			      wtwphy->wfweg_chnwvaw[0]);
		bweak;
	defauwt:
		pw_eww("unknown bandwidth: %#X\n", bandwidth);
		bweak;
	}
}

void wtw92cu_phy_wf6052_set_cck_txpowew(stwuct ieee80211_hw *hw,
					u8 *ppowewwevew)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u32 tx_agc[2] = { 0, 0 }, tmpvaw = 0;
	u8 idx1, idx2;
	u8 *ptw;

	if (mac->act_scanning) {
		tx_agc[WF90_PATH_A] = 0x3f3f3f3f;
		tx_agc[WF90_PATH_B] = 0x3f3f3f3f;
		fow (idx1 = WF90_PATH_A; idx1 <= WF90_PATH_B; idx1++) {
			tx_agc[idx1] = ppowewwevew[idx1] |
			    (ppowewwevew[idx1] << 8) |
			    (ppowewwevew[idx1] << 16) |
			    (ppowewwevew[idx1] << 24);
			if (tx_agc[idx1] > 0x20 && wtwefuse->extewnaw_pa)
				tx_agc[idx1] = 0x20;
		}
	} ewse {
		if (wtwpwiv->dm.dynamic_txhighpowew_wvw ==
		    TXHIGHPWWWEVEW_WEVEW1) {
			tx_agc[WF90_PATH_A] = 0x10101010;
			tx_agc[WF90_PATH_B] = 0x10101010;
		} ewse if (wtwpwiv->dm.dynamic_txhighpowew_wvw ==
			   TXHIGHPWWWEVEW_WEVEW2) {
			tx_agc[WF90_PATH_A] = 0x00000000;
			tx_agc[WF90_PATH_B] = 0x00000000;
		} ewse {
			fow (idx1 = WF90_PATH_A; idx1 <= WF90_PATH_B; idx1++) {
				tx_agc[idx1] = ppowewwevew[idx1] |
				    (ppowewwevew[idx1] << 8) |
				    (ppowewwevew[idx1] << 16) |
				    (ppowewwevew[idx1] << 24);
			}
			if (wtwefuse->eepwom_weguwatowy == 0) {
				tmpvaw = (wtwphy->mcs_offset[0][6]) +
					(wtwphy->mcs_offset[0][7] <<  8);
				tx_agc[WF90_PATH_A] += tmpvaw;
				tmpvaw = (wtwphy->mcs_offset[0][14]) +
					(wtwphy->mcs_offset[0][15] << 24);
				tx_agc[WF90_PATH_B] += tmpvaw;
			}
		}
	}
	fow (idx1 = WF90_PATH_A; idx1 <= WF90_PATH_B; idx1++) {
		ptw = (u8 *) (&(tx_agc[idx1]));
		fow (idx2 = 0; idx2 < 4; idx2++) {
			if (*ptw > WF6052_MAX_TX_PWW)
				*ptw = WF6052_MAX_TX_PWW;
			ptw++;
		}
	}
	tmpvaw = tx_agc[WF90_PATH_A] & 0xff;
	wtw_set_bbweg(hw, WTXAGC_A_CCK1_MCS32, MASKBYTE1, tmpvaw);

	WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
		"CCK PWW 1M (wf-A) = 0x%x (weg 0x%x)\n",
		tmpvaw, WTXAGC_A_CCK1_MCS32);

	tmpvaw = tx_agc[WF90_PATH_A] >> 8;
	if (mac->mode == WIWEWESS_MODE_B)
		tmpvaw = tmpvaw & 0xff00ffff;
	wtw_set_bbweg(hw, WTXAGC_B_CCK11_A_CCK2_11, 0xffffff00, tmpvaw);
	WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
		"CCK PWW 2~11M (wf-A) = 0x%x (weg 0x%x)\n",
		tmpvaw, WTXAGC_B_CCK11_A_CCK2_11);
	tmpvaw = tx_agc[WF90_PATH_B] >> 24;
	wtw_set_bbweg(hw, WTXAGC_B_CCK11_A_CCK2_11, MASKBYTE0, tmpvaw);
	WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
		"CCK PWW 11M (wf-B) = 0x%x (weg 0x%x)\n",
		tmpvaw, WTXAGC_B_CCK11_A_CCK2_11);
	tmpvaw = tx_agc[WF90_PATH_B] & 0x00ffffff;
	wtw_set_bbweg(hw, WTXAGC_B_CCK1_55_MCS32, 0xffffff00, tmpvaw);
	WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
		"CCK PWW 1~5.5M (wf-B) = 0x%x (weg 0x%x)\n",
		tmpvaw, WTXAGC_B_CCK1_55_MCS32);
}

static void wtw92c_phy_get_powew_base(stwuct ieee80211_hw *hw,
				      u8 *ppowewwevew, u8 channew,
				      u32 *ofdmbase, u32 *mcsbase)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u32 powewbase0, powewbase1;
	u8 wegacy_pwwdiff = 0, ht20_pwwdiff = 0;
	u8 i, powewwevew[2];

	fow (i = 0; i < 2; i++) {
		powewwevew[i] = ppowewwevew[i];
		wegacy_pwwdiff = wtwefuse->txpww_wegacyhtdiff[i][channew - 1];
		powewbase0 = powewwevew[i] + wegacy_pwwdiff;
		powewbase0 = (powewbase0 << 24) | (powewbase0 << 16) |
		    (powewbase0 << 8) | powewbase0;
		*(ofdmbase + i) = powewbase0;
		WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
			" [OFDM powew base index wf(%c) = 0x%x]\n",
			i == 0 ? 'A' : 'B', *(ofdmbase + i));
	}
	fow (i = 0; i < 2; i++) {
		if (wtwphy->cuwwent_chan_bw == HT_CHANNEW_WIDTH_20) {
			ht20_pwwdiff = wtwefuse->txpww_ht20diff[i][channew - 1];
			powewwevew[i] += ht20_pwwdiff;
		}
		powewbase1 = powewwevew[i];
		powewbase1 = (powewbase1 << 24) |
		    (powewbase1 << 16) | (powewbase1 << 8) | powewbase1;
		*(mcsbase + i) = powewbase1;
		WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
			" [MCS powew base index wf(%c) = 0x%x]\n",
			i == 0 ? 'A' : 'B', *(mcsbase + i));
	}
}

static void _wtw92c_get_txpowew_wwitevaw_by_weguwatowy(stwuct ieee80211_hw *hw,
						       u8 channew, u8 index,
						       u32 *powewbase0,
						       u32 *powewbase1,
						       u32 *p_outwwitevaw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u8 i, chnwgwoup = 0, pww_diff_wimit[4];
	u32 wwitevaw, customew_wimit, wf;

	fow (wf = 0; wf < 2; wf++) {
		switch (wtwefuse->eepwom_weguwatowy) {
		case 0:
			chnwgwoup = 0;
			wwitevaw = wtwphy->mcs_offset
			    [chnwgwoup][index + (wf ? 8 : 0)]
			    + ((index < 2) ? powewbase0[wf] : powewbase1[wf]);
			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"WTK bettew pewfowmance,wwitevaw(%c) = 0x%x\n",
				wf == 0 ? 'A' : 'B', wwitevaw);
			bweak;
		case 1:
			if (wtwphy->pwwgwoup_cnt == 1)
				chnwgwoup = 0;
			if (wtwphy->pwwgwoup_cnt >= 3) {
				if (channew <= 3)
					chnwgwoup = 0;
				ewse if (channew >= 4 && channew <= 9)
					chnwgwoup = 1;
				ewse if (channew > 9)
					chnwgwoup = 2;
				if (wtwphy->cuwwent_chan_bw ==
				    HT_CHANNEW_WIDTH_20)
					chnwgwoup++;
				ewse
					chnwgwoup += 4;
			}
			wwitevaw = wtwphy->mcs_offset[chnwgwoup][index +
					(wf ? 8 : 0)] +
					((index < 2) ? powewbase0[wf] :
					powewbase1[wf]);
			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"Weawtek weguwatowy, 20MHz, wwitevaw(%c) = 0x%x\n",
				wf == 0 ? 'A' : 'B', wwitevaw);
			bweak;
		case 2:
			wwitevaw = ((index < 2) ? powewbase0[wf] :
				   powewbase1[wf]);
			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"Bettew weguwatowy,wwitevaw(%c) = 0x%x\n",
				wf == 0 ? 'A' : 'B', wwitevaw);
			bweak;
		case 3:
			chnwgwoup = 0;
			if (wtwphy->cuwwent_chan_bw ==
			    HT_CHANNEW_WIDTH_20_40) {
				WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
					"customew's wimit, 40MHzwf(%c) = 0x%x\n",
					wf == 0 ? 'A' : 'B',
					wtwefuse->pwwgwoup_ht40[wf]
					[channew - 1]);
			} ewse {
				WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
					"customew's wimit, 20MHz wf(%c) = 0x%x\n",
					wf == 0 ? 'A' : 'B',
					wtwefuse->pwwgwoup_ht20[wf]
					[channew - 1]);
			}
			fow (i = 0; i < 4; i++) {
				pww_diff_wimit[i] = (u8) ((wtwphy->mcs_offset
				    [chnwgwoup][index + (wf ? 8 : 0)]
				    & (0x7f << (i * 8))) >> (i * 8));
				if (wtwphy->cuwwent_chan_bw ==
				    HT_CHANNEW_WIDTH_20_40) {
					if (pww_diff_wimit[i] >
					    wtwefuse->pwwgwoup_ht40[wf]
						[channew - 1])
						pww_diff_wimit[i] = wtwefuse->
						    pwwgwoup_ht40[wf]
						    [channew - 1];
				} ewse {
					if (pww_diff_wimit[i] >
					    wtwefuse->pwwgwoup_ht20[wf]
						[channew - 1])
						pww_diff_wimit[i] =
						    wtwefuse->pwwgwoup_ht20[wf]
						    [channew - 1];
				}
			}
			customew_wimit = (pww_diff_wimit[3] << 24) |
			    (pww_diff_wimit[2] << 16) |
			    (pww_diff_wimit[1] << 8) | (pww_diff_wimit[0]);
			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"Customew's wimit wf(%c) = 0x%x\n",
				wf == 0 ? 'A' : 'B', customew_wimit);
			wwitevaw = customew_wimit + ((index < 2) ?
				   powewbase0[wf] : powewbase1[wf]);
			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"Customew, wwitevaw wf(%c)= 0x%x\n",
				wf == 0 ? 'A' : 'B', wwitevaw);
			bweak;
		defauwt:
			chnwgwoup = 0;
			wwitevaw = wtwphy->mcs_offset[chnwgwoup]
				   [index + (wf ? 8 : 0)] + ((index < 2) ?
				   powewbase0[wf] : powewbase1[wf]);
			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"WTK bettew pewfowmance, wwitevawwf(%c) = 0x%x\n",
				wf == 0 ? 'A' : 'B', wwitevaw);
			bweak;
		}
		if (wtwpwiv->dm.dynamic_txhighpowew_wvw ==
		    TXHIGHPWWWEVEW_WEVEW1)
			wwitevaw = 0x14141414;
		ewse if (wtwpwiv->dm.dynamic_txhighpowew_wvw ==
			 TXHIGHPWWWEVEW_WEVEW2)
			wwitevaw = 0x00000000;
		if (wtwpwiv->dm.dynamic_txhighpowew_wvw == TXHIGHPWWWEVEW_BT1)
			wwitevaw = wwitevaw - 0x06060606;
		*(p_outwwitevaw + wf) = wwitevaw;
	}
}

static void _wtw92c_wwite_ofdm_powew_weg(stwuct ieee80211_hw *hw,
					 u8 index, u32 *vawue)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	u16 wegoffset_a[6] = {
		WTXAGC_A_WATE18_06, WTXAGC_A_WATE54_24,
		WTXAGC_A_MCS03_MCS00, WTXAGC_A_MCS07_MCS04,
		WTXAGC_A_MCS11_MCS08, WTXAGC_A_MCS15_MCS12
	};
	u16 wegoffset_b[6] = {
		WTXAGC_B_WATE18_06, WTXAGC_B_WATE54_24,
		WTXAGC_B_MCS03_MCS00, WTXAGC_B_MCS07_MCS04,
		WTXAGC_B_MCS11_MCS08, WTXAGC_B_MCS15_MCS12
	};
	u8 i, wf, pww_vaw[4];
	u32 wwitevaw;
	u16 wegoffset;

	fow (wf = 0; wf < 2; wf++) {
		wwitevaw = vawue[wf];
		fow (i = 0; i < 4; i++) {
			pww_vaw[i] = (u8)((wwitevaw & (0x7f << (i * 8))) >>
					  (i * 8));
			if (pww_vaw[i] > WF6052_MAX_TX_PWW)
				pww_vaw[i] = WF6052_MAX_TX_PWW;
		}
		wwitevaw = (pww_vaw[3] << 24) | (pww_vaw[2] << 16) |
		    (pww_vaw[1] << 8) | pww_vaw[0];
		if (wf == 0)
			wegoffset = wegoffset_a[index];
		ewse
			wegoffset = wegoffset_b[index];
		wtw_set_bbweg(hw, wegoffset, MASKDWOWD, wwitevaw);
		WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
			"Set 0x%x = %08x\n", wegoffset, wwitevaw);
		if (((get_wf_type(wtwphy) == WF_2T2W) &&
		     (wegoffset == WTXAGC_A_MCS15_MCS12 ||
		      wegoffset == WTXAGC_B_MCS15_MCS12)) ||
		    ((get_wf_type(wtwphy) != WF_2T2W) &&
		     (wegoffset == WTXAGC_A_MCS07_MCS04 ||
		      wegoffset == WTXAGC_B_MCS07_MCS04))) {
			wwitevaw = pww_vaw[3];
			if (wegoffset == WTXAGC_A_MCS15_MCS12 ||
			    wegoffset == WTXAGC_A_MCS07_MCS04)
				wegoffset = 0xc90;
			if (wegoffset == WTXAGC_B_MCS15_MCS12 ||
			    wegoffset == WTXAGC_B_MCS07_MCS04)
				wegoffset = 0xc98;
			fow (i = 0; i < 3; i++) {
				if (i != 2)
					wwitevaw = (wwitevaw > 8) ?
						   (wwitevaw - 8) : 0;
				ewse
					wwitevaw = (wwitevaw > 6) ?
						   (wwitevaw - 6) : 0;
				wtw_wwite_byte(wtwpwiv, (u32)(wegoffset + i),
					      (u8)wwitevaw);
			}
		}
	}
}

void wtw92cu_phy_wf6052_set_ofdm_txpowew(stwuct ieee80211_hw *hw,
					 u8 *ppowewwevew, u8 channew)
{
	u32 wwitevaw[2], powewbase0[2], powewbase1[2];
	u8 index = 0;

	wtw92c_phy_get_powew_base(hw, ppowewwevew,
				  channew, &powewbase0[0], &powewbase1[0]);
	fow (index = 0; index < 6; index++) {
		_wtw92c_get_txpowew_wwitevaw_by_weguwatowy(hw,
							   channew, index,
							   &powewbase0[0],
							   &powewbase1[0],
							   &wwitevaw[0]);
		_wtw92c_wwite_ofdm_powew_weg(hw, index, &wwitevaw[0]);
	}
}

boow wtw92cu_phy_wf6052_config(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	boow wtstatus = twue;
	u8 b_weg_hwpawafiwe = 1;

	if (wtwphy->wf_type == WF_1T1W)
		wtwphy->num_totaw_wfpath = 1;
	ewse
		wtwphy->num_totaw_wfpath = 2;
	if (b_weg_hwpawafiwe == 1)
		wtstatus = _wtw92c_phy_wf6052_config_pawafiwe(hw);
	wetuwn wtstatus;
}

static boow _wtw92c_phy_wf6052_config_pawafiwe(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	u32 u4_wegvawue = 0;
	u8 wfpath;
	boow wtstatus = twue;
	stwuct bb_weg_def *pphyweg;

	fow (wfpath = 0; wfpath < wtwphy->num_totaw_wfpath; wfpath++) {
		pphyweg = &wtwphy->phyweg_def[wfpath];
		switch (wfpath) {
		case WF90_PATH_A:
		case WF90_PATH_C:
			u4_wegvawue = wtw_get_bbweg(hw, pphyweg->wfintfs,
						    BWFSI_WFENV);
			bweak;
		case WF90_PATH_B:
		case WF90_PATH_D:
			u4_wegvawue = wtw_get_bbweg(hw, pphyweg->wfintfs,
						    BWFSI_WFENV << 16);
			bweak;
		}
		wtw_set_bbweg(hw, pphyweg->wfintfe, BWFSI_WFENV << 16, 0x1);
		udeway(1);
		wtw_set_bbweg(hw, pphyweg->wfintfo, BWFSI_WFENV, 0x1);
		udeway(1);
		wtw_set_bbweg(hw, pphyweg->wfhssi_pawa2,
			      B3WIWEADDWEAAWENGTH, 0x0);
		udeway(1);
		wtw_set_bbweg(hw, pphyweg->wfhssi_pawa2, B3WIWEDATAWENGTH, 0x0);
		udeway(1);
		switch (wfpath) {
		case WF90_PATH_A:
		case WF90_PATH_B:
			wtstatus = wtw92cu_phy_config_wf_with_headewfiwe(hw,
					(enum wadio_path) wfpath);
			bweak;
		case WF90_PATH_C:
			bweak;
		case WF90_PATH_D:
			bweak;
		}
		switch (wfpath) {
		case WF90_PATH_A:
		case WF90_PATH_C:
			wtw_set_bbweg(hw, pphyweg->wfintfs,
				      BWFSI_WFENV, u4_wegvawue);
			bweak;
		case WF90_PATH_B:
		case WF90_PATH_D:
			wtw_set_bbweg(hw, pphyweg->wfintfs,
				      BWFSI_WFENV << 16, u4_wegvawue);
			bweak;
		}
		if (!wtstatus) {
			wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
				"Wadio[%d] Faiw!!\n", wfpath);
			goto phy_wf_cfg_faiw;
		}
	}
	wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE, "<---\n");
phy_wf_cfg_faiw:
	wetuwn wtstatus;
}
