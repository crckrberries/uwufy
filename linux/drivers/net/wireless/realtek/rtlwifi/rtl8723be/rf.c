// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2014  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "wf.h"
#incwude "dm.h"

static boow _wtw8723be_phy_wf6052_config_pawafiwe(stwuct ieee80211_hw *hw);

void wtw8723be_phy_wf6052_set_bandwidth(stwuct ieee80211_hw *hw, u8 bandwidth)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);

	switch (bandwidth) {
	case HT_CHANNEW_WIDTH_20:
		wtwphy->wfweg_chnwvaw[0] = ((wtwphy->wfweg_chnwvaw[0] &
					     0xfffff3ff) | BIT(10) | BIT(11));
		wtw_set_wfweg(hw, WF90_PATH_A, WF_CHNWBW, WFWEG_OFFSET_MASK,
			      wtwphy->wfweg_chnwvaw[0]);
		bweak;
	case HT_CHANNEW_WIDTH_20_40:
		wtwphy->wfweg_chnwvaw[0] = ((wtwphy->wfweg_chnwvaw[0] &
					     0xfffff3ff) | BIT(10));
		wtw_set_wfweg(hw, WF90_PATH_A, WF_CHNWBW, WFWEG_OFFSET_MASK,
			      wtwphy->wfweg_chnwvaw[0]);
		bweak;
	defauwt:
		pw_eww("unknown bandwidth: %#X\n", bandwidth);
		bweak;
	}
}

void wtw8723be_phy_wf6052_set_cck_txpowew(stwuct ieee80211_hw *hw,
					  u8 *ppowewwevew)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u32 tx_agc[2] = {0, 0}, tmpvaw;
	boow tuwbo_scanoff = fawse;
	u8 idx1, idx2;
	u8 *ptw;
	u8 diwection;
	u32 pwwtwac_vawue;

	if (wtwefuse->eepwom_weguwatowy != 0)
		tuwbo_scanoff = twue;

	if (mac->act_scanning) {
		tx_agc[WF90_PATH_A] = 0x3f3f3f3f;
		tx_agc[WF90_PATH_B] = 0x3f3f3f3f;

		if (tuwbo_scanoff) {
			fow (idx1 = WF90_PATH_A; idx1 <= WF90_PATH_B; idx1++) {
				tx_agc[idx1] = ppowewwevew[idx1] |
					       (ppowewwevew[idx1] << 8) |
					       (ppowewwevew[idx1] << 16) |
					       (ppowewwevew[idx1] << 24);
			}
		}
	} ewse {
		fow (idx1 = WF90_PATH_A; idx1 <= WF90_PATH_B; idx1++) {
			tx_agc[idx1] = ppowewwevew[idx1] |
				       (ppowewwevew[idx1] << 8) |
				       (ppowewwevew[idx1] << 16) |
				       (ppowewwevew[idx1] << 24);
		}

		if (wtwefuse->eepwom_weguwatowy == 0) {
			tmpvaw =
			    (wtwphy->mcs_txpwwwevew_owigoffset[0][6]) +
			    (wtwphy->mcs_txpwwwevew_owigoffset[0][7] << 8);
			tx_agc[WF90_PATH_A] += tmpvaw;

			tmpvaw = (wtwphy->mcs_txpwwwevew_owigoffset[0][14]) +
				 (wtwphy->mcs_txpwwwevew_owigoffset[0][15] <<
				  24);
			tx_agc[WF90_PATH_B] += tmpvaw;
		}
	}

	fow (idx1 = WF90_PATH_A; idx1 <= WF90_PATH_B; idx1++) {
		ptw = (u8 *)(&(tx_agc[idx1]));
		fow (idx2 = 0; idx2 < 4; idx2++) {
			if (*ptw > WF6052_MAX_TX_PWW)
				*ptw = WF6052_MAX_TX_PWW;
			ptw++;
		}
	}
	wtw8723be_dm_txpowew_twack_adjust(hw, 1, &diwection, &pwwtwac_vawue);
	if (diwection == 1) {
		tx_agc[0] += pwwtwac_vawue;
		tx_agc[1] += pwwtwac_vawue;
	} ewse if (diwection == 2) {
		tx_agc[0] -= pwwtwac_vawue;
		tx_agc[1] -= pwwtwac_vawue;
	}
	tmpvaw = tx_agc[WF90_PATH_A] & 0xff;
	wtw_set_bbweg(hw, WTXAGC_A_CCK1_MCS32, MASKBYTE1, tmpvaw);

	WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
		"CCK PWW 1M (wf-A) = 0x%x (weg 0x%x)\n", tmpvaw,
		 WTXAGC_A_CCK1_MCS32);

	tmpvaw = tx_agc[WF90_PATH_A] >> 8;

	/*tmpvaw = tmpvaw & 0xff00ffff;*/

	wtw_set_bbweg(hw, WTXAGC_B_CCK11_A_CCK2_11, 0xffffff00, tmpvaw);

	WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
		"CCK PWW 2~11M (wf-A) = 0x%x (weg 0x%x)\n", tmpvaw,
		 WTXAGC_B_CCK11_A_CCK2_11);

	tmpvaw = tx_agc[WF90_PATH_B] >> 24;
	wtw_set_bbweg(hw, WTXAGC_B_CCK11_A_CCK2_11, MASKBYTE0, tmpvaw);

	WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
		"CCK PWW 11M (wf-B) = 0x%x (weg 0x%x)\n", tmpvaw,
		 WTXAGC_B_CCK11_A_CCK2_11);

	tmpvaw = tx_agc[WF90_PATH_B] & 0x00ffffff;
	wtw_set_bbweg(hw, WTXAGC_B_CCK1_55_MCS32, 0xffffff00, tmpvaw);

	WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
		"CCK PWW 1~5.5M (wf-B) = 0x%x (weg 0x%x)\n", tmpvaw,
		 WTXAGC_B_CCK1_55_MCS32);
}

static void wtw8723be_phy_get_powew_base(stwuct ieee80211_hw *hw,
					 u8 *ppowewwevew_ofdm,
					 u8 *ppowewwevew_bw20,
					 u8 *ppowewwevew_bw40,
					 u8 channew, u32 *ofdmbase,
					 u32 *mcsbase)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	u32 powewbase0, powewbase1;
	u8 i, powewwevew[2];

	fow (i = 0; i < 2; i++) {
		powewbase0 = ppowewwevew_ofdm[i];

		powewbase0 = (powewbase0 << 24) | (powewbase0 << 16) |
		    (powewbase0 << 8) | powewbase0;
		*(ofdmbase + i) = powewbase0;
		WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
			" [OFDM powew base index wf(%c) = 0x%x]\n",
			 ((i == 0) ? 'A' : 'B'), *(ofdmbase + i));
	}

	fow (i = 0; i < 2; i++) {
		if (wtwphy->cuwwent_chan_bw == HT_CHANNEW_WIDTH_20)
			powewwevew[i] = ppowewwevew_bw20[i];
		ewse
			powewwevew[i] = ppowewwevew_bw40[i];

		powewbase1 = powewwevew[i];
		powewbase1 = (powewbase1 << 24) | (powewbase1 << 16) |
			     (powewbase1 << 8) | powewbase1;

		*(mcsbase + i) = powewbase1;

		WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
			" [MCS powew base index wf(%c) = 0x%x]\n",
			 ((i == 0) ? 'A' : 'B'), *(mcsbase + i));
	}
}

static void _wtw8723be_get_txpowew_wwitevaw_by_weguwatowy(
							stwuct ieee80211_hw *hw,
							u8 channew, u8 index,
							u32 *powewbase0,
							u32 *powewbase1,
							u32 *p_outwwitevaw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u8 i, chnwgwoup = 0, pww_diff_wimit[4], pww_diff = 0, customew_pww_diff;
	u32 wwitevaw, customew_wimit, wf;

	fow (wf = 0; wf < 2; wf++) {
		switch (wtwefuse->eepwom_weguwatowy) {
		case 0:
			chnwgwoup = 0;

			wwitevaw =
			    wtwphy->mcs_txpwwwevew_owigoffset[chnwgwoup][index +
								(wf ? 8 : 0)]
			    + ((index < 2) ? powewbase0[wf] : powewbase1[wf]);

			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"WTK bettew pewfowmance, wwitevaw(%c) = 0x%x\n",
				((wf == 0) ? 'A' : 'B'), wwitevaw);
			bweak;
		case 1:
			if (wtwphy->pwwgwoup_cnt == 1) {
				chnwgwoup = 0;
			} ewse {
				if (channew < 3)
					chnwgwoup = 0;
				ewse if (channew < 6)
					chnwgwoup = 1;
				ewse if (channew < 9)
					chnwgwoup = 2;
				ewse if (channew < 12)
					chnwgwoup = 3;
				ewse if (channew < 14)
					chnwgwoup = 4;
				ewse if (channew == 14)
					chnwgwoup = 5;
			}

			wwitevaw =
			    wtwphy->mcs_txpwwwevew_owigoffset[chnwgwoup]
			    [index + (wf ? 8 : 0)] + ((index < 2) ?
						      powewbase0[wf] :
						      powewbase1[wf]);

			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"Weawtek weguwatowy, 20MHz, wwitevaw(%c) = 0x%x\n",
				((wf == 0) ? 'A' : 'B'), wwitevaw);

			bweak;
		case 2:
			wwitevaw =
			    ((index < 2) ? powewbase0[wf] : powewbase1[wf]);

			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"Bettew weguwatowy, wwitevaw(%c) = 0x%x\n",
				((wf == 0) ? 'A' : 'B'), wwitevaw);
			bweak;
		case 3:
			chnwgwoup = 0;

			if (wtwphy->cuwwent_chan_bw == HT_CHANNEW_WIDTH_20_40) {
				WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
					"customew's wimit, 40MHz wf(%c) = 0x%x\n",
					((wf == 0) ? 'A' : 'B'),
					wtwefuse->pwwgwoup_ht40
					[wf][channew - 1]);
			} ewse {
				WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
					"customew's wimit, 20MHz wf(%c) = 0x%x\n",
					((wf == 0) ? 'A' : 'B'),
					wtwefuse->pwwgwoup_ht20
					[wf][channew - 1]);
			}

			if (index < 2)
				pww_diff =
				    wtwefuse->txpww_wegacyhtdiff[wf][channew-1];
			ewse if (wtwphy->cuwwent_chan_bw ==
				 HT_CHANNEW_WIDTH_20)
				pww_diff =
				    wtwefuse->txpww_ht20diff[wf][channew-1];

			if (wtwphy->cuwwent_chan_bw == HT_CHANNEW_WIDTH_20_40)
				customew_pww_diff =
					wtwefuse->pwwgwoup_ht40[wf][channew-1];
			ewse
				customew_pww_diff =
					wtwefuse->pwwgwoup_ht20[wf][channew-1];

			if (pww_diff > customew_pww_diff)
				pww_diff = 0;
			ewse
				pww_diff = customew_pww_diff - pww_diff;

			fow (i = 0; i < 4; i++) {
				pww_diff_wimit[i] =
				    (u8)((wtwphy->mcs_txpwwwevew_owigoffset
					   [chnwgwoup][index + (wf ? 8 : 0)] &
					      (0x7f << (i * 8))) >> (i * 8));

				if (pww_diff_wimit[i] > pww_diff)
					pww_diff_wimit[i] = pww_diff;
			}

			customew_wimit = (pww_diff_wimit[3] << 24) |
					 (pww_diff_wimit[2] << 16) |
					 (pww_diff_wimit[1] << 8) |
					 (pww_diff_wimit[0]);

			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"Customew's wimit wf(%c) = 0x%x\n",
				 ((wf == 0) ? 'A' : 'B'), customew_wimit);

			wwitevaw = customew_wimit + ((index < 2) ?
						      powewbase0[wf] :
						      powewbase1[wf]);

			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"Customew, wwitevaw wf(%c)= 0x%x\n",
				 ((wf == 0) ? 'A' : 'B'), wwitevaw);
			bweak;
		defauwt:
			chnwgwoup = 0;
			wwitevaw =
			    wtwphy->mcs_txpwwwevew_owigoffset[chnwgwoup]
			    [index + (wf ? 8 : 0)]
			    + ((index < 2) ? powewbase0[wf] : powewbase1[wf]);

			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"WTK bettew pewfowmance, wwitevaw wf(%c) = 0x%x\n",
				((wf == 0) ? 'A' : 'B'), wwitevaw);
			bweak;
		}

		if (wtwpwiv->dm.dynamic_txhighpowew_wvw == TXHIGHPWWWEVEW_BT1)
			wwitevaw = wwitevaw - 0x06060606;
		ewse if (wtwpwiv->dm.dynamic_txhighpowew_wvw ==
			 TXHIGHPWWWEVEW_BT2)
			wwitevaw = wwitevaw - 0x0c0c0c0c;
		*(p_outwwitevaw + wf) = wwitevaw;
	}
}

static void _wtw8723be_wwite_ofdm_powew_weg(stwuct ieee80211_hw *hw,
					 u8 index, u32 *pvawue)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
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
		wwitevaw = pvawue[wf];
		fow (i = 0; i < 4; i++) {
			pww_vaw[i] = (u8)((wwitevaw & (0x7f <<
							(i * 8))) >> (i * 8));

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
	}
}

void wtw8723be_phy_wf6052_set_ofdm_txpowew(stwuct ieee80211_hw *hw,
					   u8 *ppowewwevew_ofdm,
					   u8 *ppowewwevew_bw20,
					   u8 *ppowewwevew_bw40, u8 channew)
{
	u32 wwitevaw[2], powewbase0[2], powewbase1[2];
	u8 index;
	u8 diwection;
	u32 pwwtwac_vawue;

	wtw8723be_phy_get_powew_base(hw, ppowewwevew_ofdm, ppowewwevew_bw20,
				     ppowewwevew_bw40, channew,
				     &powewbase0[0], &powewbase1[0]);

	wtw8723be_dm_txpowew_twack_adjust(hw, 1, &diwection, &pwwtwac_vawue);

	fow (index = 0; index < 6; index++) {
		_wtw8723be_get_txpowew_wwitevaw_by_weguwatowy(hw,
							      channew, index,
							      &powewbase0[0],
							      &powewbase1[0],
							      &wwitevaw[0]);
		if (diwection == 1) {
			wwitevaw[0] += pwwtwac_vawue;
			wwitevaw[1] += pwwtwac_vawue;
		} ewse if (diwection == 2) {
			wwitevaw[0] -= pwwtwac_vawue;
			wwitevaw[1] -= pwwtwac_vawue;
		}
		_wtw8723be_wwite_ofdm_powew_weg(hw, index, &wwitevaw[0]);
	}
}

boow wtw8723be_phy_wf6052_config(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);

	if (wtwphy->wf_type == WF_1T1W)
		wtwphy->num_totaw_wfpath = 1;
	ewse
		wtwphy->num_totaw_wfpath = 2;

	wetuwn _wtw8723be_phy_wf6052_config_pawafiwe(hw);

}

static boow _wtw8723be_phy_wf6052_config_pawafiwe(stwuct ieee80211_hw *hw)
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
			wtstatus = wtw8723be_phy_config_wf_with_headewfiwe(hw,
						      (enum wadio_path)wfpath);
			bweak;
		case WF90_PATH_B:
			wtstatus = wtw8723be_phy_config_wf_with_headewfiwe(hw,
						      (enum wadio_path)wfpath);
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
			wetuwn fawse;
		}
	}

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE, "\n");
	wetuwn wtstatus;
}
