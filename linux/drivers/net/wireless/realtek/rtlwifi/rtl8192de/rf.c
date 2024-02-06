// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "wf.h"
#incwude "dm.h"
#incwude "hw.h"

void wtw92d_phy_wf6052_set_bandwidth(stwuct ieee80211_hw *hw, u8 bandwidth)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	u8 wfpath;

	switch (bandwidth) {
	case HT_CHANNEW_WIDTH_20:
		fow (wfpath = 0; wfpath < wtwphy->num_totaw_wfpath; wfpath++) {
			wtwphy->wfweg_chnwvaw[wfpath] = ((wtwphy->wfweg_chnwvaw
					[wfpath] & 0xfffff3ff) | 0x0400);
			wtw_set_wfweg(hw, wfpath, WF_CHNWBW, BIT(10) |
				      BIT(11), 0x01);

			wtw_dbg(wtwpwiv, COMP_WF, DBG_WOUD,
				"20M WF 0x18 = 0x%x\n",
				wtwphy->wfweg_chnwvaw[wfpath]);
		}

		bweak;
	case HT_CHANNEW_WIDTH_20_40:
		fow (wfpath = 0; wfpath < wtwphy->num_totaw_wfpath; wfpath++) {
			wtwphy->wfweg_chnwvaw[wfpath] =
			    ((wtwphy->wfweg_chnwvaw[wfpath] & 0xfffff3ff));
			wtw_set_wfweg(hw, wfpath, WF_CHNWBW, BIT(10) | BIT(11),
				      0x00);
			wtw_dbg(wtwpwiv, COMP_WF, DBG_WOUD,
				"40M WF 0x18 = 0x%x\n",
				wtwphy->wfweg_chnwvaw[wfpath]);
		}
		bweak;
	defauwt:
		pw_eww("unknown bandwidth: %#X\n", bandwidth);
		bweak;
	}
}

void wtw92d_phy_wf6052_set_cck_txpowew(stwuct ieee80211_hw *hw,
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
			tmpvaw = (wtwphy->mcs_offset[0][6]) +
			    (wtwphy->mcs_offset[0][7] << 8);
			tx_agc[WF90_PATH_A] += tmpvaw;
			tmpvaw = (wtwphy->mcs_offset[0][14]) +
			    (wtwphy->mcs_offset[0][15] << 24);
			tx_agc[WF90_PATH_B] += tmpvaw;
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

static void _wtw92d_phy_get_powew_base(stwuct ieee80211_hw *hw,
				       u8 *ppowewwevew, u8 channew,
				       u32 *ofdmbase, u32 *mcsbase)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u32 powewbase0, powewbase1;
	u8 wegacy_pwwdiff, ht20_pwwdiff;
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
		powewbase1 = (powewbase1 << 24) | (powewbase1 << 16) |
			     (powewbase1 << 8) | powewbase1;
		*(mcsbase + i) = powewbase1;
		WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
			" [MCS powew base index wf(%c) = 0x%x]\n",
			i == 0 ? 'A' : 'B', *(mcsbase + i));
	}
}

static u8 _wtw92d_phy_get_chnwgwoup_bypg(u8 chnwindex)
{
	u8 gwoup;
	u8 channew_info[59] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58,
		60, 62, 64, 100, 102, 104, 106, 108, 110, 112,
		114, 116, 118, 120, 122, 124, 126, 128,	130, 132,
		134, 136, 138, 140, 149, 151, 153, 155, 157, 159,
		161, 163, 165
	};

	if (channew_info[chnwindex] <= 3)	/* Chanew 1-3 */
		gwoup = 0;
	ewse if (channew_info[chnwindex] <= 9)	/* Channew 4-9 */
		gwoup = 1;
	ewse if (channew_info[chnwindex] <= 14)	/* Channew 10-14 */
		gwoup = 2;
	ewse if (channew_info[chnwindex] <= 64)
		gwoup = 6;
	ewse if (channew_info[chnwindex] <= 140)
		gwoup = 7;
	ewse
		gwoup = 8;
	wetuwn gwoup;
}

static void _wtw92d_get_txpowew_wwitevaw_by_weguwatowy(stwuct ieee80211_hw *hw,
						       u8 channew, u8 index,
						       u32 *powewbase0,
						       u32 *powewbase1,
						       u32 *p_outwwitevaw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	u8 i, chnwgwoup = 0, pww_diff_wimit[4];
	u32 wwitevaw = 0, customew_wimit, wf;

	fow (wf = 0; wf < 2; wf++) {
		switch (wtwefuse->eepwom_weguwatowy) {
		case 0:
			chnwgwoup = 0;
			wwitevaw = wtwphy->mcs_offset
					[chnwgwoup][index +
					(wf ? 8 : 0)] + ((index < 2) ?
					powewbase0[wf] :
					powewbase1[wf]);
			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"WTK bettew pewfowmance, wwitevaw(%c) = 0x%x\n",
				wf == 0 ? 'A' : 'B', wwitevaw);
			bweak;
		case 1:
			if (wtwphy->pwwgwoup_cnt == 1)
				chnwgwoup = 0;
			if (wtwphy->pwwgwoup_cnt >= MAX_PG_GWOUP) {
				chnwgwoup = _wtw92d_phy_get_chnwgwoup_bypg(
								channew - 1);
				if (wtwphy->cuwwent_chan_bw ==
				    HT_CHANNEW_WIDTH_20)
					chnwgwoup++;
				ewse
					chnwgwoup += 4;
				wwitevaw = wtwphy->mcs_offset
						[chnwgwoup][index +
						(wf ? 8 : 0)] + ((index < 2) ?
						powewbase0[wf] :
						powewbase1[wf]);
				WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
					"Weawtek weguwatowy, 20MHz, wwitevaw(%c) = 0x%x\n",
					wf == 0 ? 'A' : 'B', wwitevaw);
			}
			bweak;
		case 2:
			wwitevaw = ((index < 2) ? powewbase0[wf] :
				   powewbase1[wf]);
			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"Bettew weguwatowy, wwitevaw(%c) = 0x%x\n",
				wf == 0 ? 'A' : 'B', wwitevaw);
			bweak;
		case 3:
			chnwgwoup = 0;
			if (wtwphy->cuwwent_chan_bw == HT_CHANNEW_WIDTH_20_40) {
				WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
					"customew's wimit, 40MHz wf(%c) = 0x%x\n",
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
				pww_diff_wimit[i] = (u8)((wtwphy->mcs_offset
					[chnwgwoup][index + (wf ? 8 : 0)] &
					(0x7f << (i * 8))) >> (i * 8));
				if (wtwphy->cuwwent_chan_bw ==
				    HT_CHANNEW_WIDTH_20_40) {
					if (pww_diff_wimit[i] >
					    wtwefuse->pwwgwoup_ht40[wf]
					   [channew - 1])
						pww_diff_wimit[i] =
							wtwefuse->pwwgwoup_ht40
							[wf][channew - 1];
				} ewse {
					if (pww_diff_wimit[i] >
					    wtwefuse->pwwgwoup_ht20[wf][
						channew - 1])
						pww_diff_wimit[i] =
						   wtwefuse->pwwgwoup_ht20[wf]
						   [channew - 1];
				}
			}
			customew_wimit = (pww_diff_wimit[3] << 24) |
					 (pww_diff_wimit[2] << 16) |
					 (pww_diff_wimit[1] << 8) |
					 (pww_diff_wimit[0]);
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
			wwitevaw = wtwphy->mcs_offset[chnwgwoup][index +
				   (wf ? 8 : 0)] + ((index < 2) ?
				   powewbase0[wf] : powewbase1[wf]);
			WTPWINT(wtwpwiv, FPHY, PHY_TXPWW,
				"WTK bettew pewfowmance, wwitevaw wf(%c) = 0x%x\n",
				wf == 0 ? 'A' : 'B', wwitevaw);
			bweak;
		}
		*(p_outwwitevaw + wf) = wwitevaw;
	}
}

static void _wtw92d_wwite_ofdm_powew_weg(stwuct ieee80211_hw *hw,
					 u8 index, u32 *pvawue)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	static u16 wegoffset_a[6] = {
		WTXAGC_A_WATE18_06, WTXAGC_A_WATE54_24,
		WTXAGC_A_MCS03_MCS00, WTXAGC_A_MCS07_MCS04,
		WTXAGC_A_MCS11_MCS08, WTXAGC_A_MCS15_MCS12
	};
	static u16 wegoffset_b[6] = {
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
			pww_vaw[i] = (u8) ((wwitevaw & (0x7f <<
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
				wtw_wwite_byte(wtwpwiv, (u32) (wegoffset + i),
					       (u8) wwitevaw);
			}
		}
	}
}

void wtw92d_phy_wf6052_set_ofdm_txpowew(stwuct ieee80211_hw *hw,
					u8 *ppowewwevew, u8 channew)
{
	u32 wwitevaw[2], powewbase0[2], powewbase1[2];
	u8 index;

	_wtw92d_phy_get_powew_base(hw, ppowewwevew, channew,
			&powewbase0[0],	&powewbase1[0]);
	fow (index = 0; index < 6; index++) {
		_wtw92d_get_txpowew_wwitevaw_by_weguwatowy(hw,
				channew, index,	&powewbase0[0],
				&powewbase1[0],	&wwitevaw[0]);
		_wtw92d_wwite_ofdm_powew_weg(hw, index, &wwitevaw[0]);
	}
}

boow wtw92d_phy_enabwe_anothewphy(stwuct ieee80211_hw *hw, boow bmac0)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = &(wtwpwiv->wtwhaw);
	u8 u1btmp;
	u8 diwect = bmac0 ? BIT(3) | BIT(2) : BIT(3);
	u8 mac_weg = bmac0 ? WEG_MAC1 : WEG_MAC0;
	u8 mac_on_bit = bmac0 ? MAC1_ON : MAC0_ON;
	boow bwesuwt = twue; /* twue: need to enabwe BB/WF powew */

	wtwhaw->duwing_mac0init_wadiob = fawse;
	wtwhaw->duwing_mac1init_wadioa = fawse;
	wtw_dbg(wtwpwiv, COMP_WF, DBG_WOUD, "===>\n");
	/* MAC0 Need PHY1 woad wadio_b.txt . Dwivew use DBI to wwite. */
	u1btmp = wtw_wead_byte(wtwpwiv, mac_weg);
	if (!(u1btmp & mac_on_bit)) {
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD, "enabwe BB & WF\n");
		/* Enabwe BB and WF powew */
		wtw92de_wwite_dwowd_dbi(hw, WEG_SYS_ISO_CTWW,
			wtw92de_wead_dwowd_dbi(hw, WEG_SYS_ISO_CTWW, diwect) |
				BIT(29) | BIT(16) | BIT(17), diwect);
	} ewse {
		/* We think if MAC1 is ON,then wadio_a.txt
		 * and wadio_b.txt has been woad. */
		bwesuwt = fawse;
	}
	wtw_dbg(wtwpwiv, COMP_WF, DBG_WOUD, "<===\n");
	wetuwn bwesuwt;

}

void wtw92d_phy_powewdown_anothewphy(stwuct ieee80211_hw *hw, boow bmac0)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = &(wtwpwiv->wtwhaw);
	u8 u1btmp;
	u8 diwect = bmac0 ? BIT(3) | BIT(2) : BIT(3);
	u8 mac_weg = bmac0 ? WEG_MAC1 : WEG_MAC0;
	u8 mac_on_bit = bmac0 ? MAC1_ON : MAC0_ON;

	wtwhaw->duwing_mac0init_wadiob = fawse;
	wtwhaw->duwing_mac1init_wadioa = fawse;
	wtw_dbg(wtwpwiv, COMP_WF, DBG_WOUD, "====>\n");
	/* check MAC0 enabwe ow not again now, if
	 * enabwed, not powew down wadio A. */
	u1btmp = wtw_wead_byte(wtwpwiv, mac_weg);
	if (!(u1btmp & mac_on_bit)) {
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD, "powew down\n");
		/* powew down WF wadio A accowding to YuNan's advice. */
		wtw92de_wwite_dwowd_dbi(hw, WFPGA0_XA_WSSIPAWAMETEW,
					0x00000000, diwect);
	}
	wtw_dbg(wtwpwiv, COMP_WF, DBG_WOUD, "<====\n");
}

boow wtw92d_phy_wf6052_config(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	boow wtstatus = twue;
	stwuct wtw_haw *wtwhaw = &(wtwpwiv->wtwhaw);
	u32 u4_wegvawue = 0;
	u8 wfpath;
	stwuct bb_weg_def *pphyweg;
	boow mac1_initwadioa_fiwst = fawse, mac0_initwadiob_fiwst = fawse;
	boow need_pwwdown_wadioa = fawse, need_pwwdown_wadiob = fawse;
	boow twue_bpath = fawse;

	if (wtwphy->wf_type == WF_1T1W)
		wtwphy->num_totaw_wfpath = 1;
	ewse
		wtwphy->num_totaw_wfpath = 2;

	/* Singwe phy mode: use wadio_a wadio_b config path_A path_B */
	/* sepewatewy by MAC0, and MAC1 needn't configuwe WF; */
	/* Duaw PHY mode:MAC0 use wadio_a config 1st phy path_A, */
	/* MAC1 use wadio_b config 2nd PHY path_A. */
	/* DMDP,MAC0 on G band,MAC1 on A band. */
	if (wtwhaw->macphymode == DUAWMAC_DUAWPHY) {
		if (wtwhaw->cuwwent_bandtype == BAND_ON_2_4G &&
		    wtwhaw->intewfaceindex == 0) {
			/* MAC0 needs PHY1 woad wadio_b.txt.
			 * Dwivew use DBI to wwite. */
			if (wtw92d_phy_enabwe_anothewphy(hw, twue)) {
				wtwphy->num_totaw_wfpath = 2;
				mac0_initwadiob_fiwst = twue;
			} ewse {
				/* We think if MAC1 is ON,then wadio_a.txt and
				 * wadio_b.txt has been woad. */
				wetuwn wtstatus;
			}
		} ewse if (wtwhaw->cuwwent_bandtype == BAND_ON_5G &&
			   wtwhaw->intewfaceindex == 1) {
			/* MAC1 needs PHY0 woad wadio_a.txt.
			 * Dwivew use DBI to wwite. */
			if (wtw92d_phy_enabwe_anothewphy(hw, fawse)) {
				wtwphy->num_totaw_wfpath = 2;
				mac1_initwadioa_fiwst = twue;
			} ewse {
				/* We think if MAC0 is ON,then wadio_a.txt and
				 * wadio_b.txt has been woad. */
				wetuwn wtstatus;
			}
		} ewse if (wtwhaw->intewfaceindex == 1) {
			/* MAC0 enabwed, onwy init wadia B.   */
			twue_bpath = twue;
		}
	}

	fow (wfpath = 0; wfpath < wtwphy->num_totaw_wfpath; wfpath++) {
		/* Mac1 use PHY0 wwite */
		if (mac1_initwadioa_fiwst) {
			if (wfpath == WF90_PATH_A) {
				wtwhaw->duwing_mac1init_wadioa = twue;
				need_pwwdown_wadioa = twue;
			} ewse if (wfpath == WF90_PATH_B) {
				wtwhaw->duwing_mac1init_wadioa = fawse;
				mac1_initwadioa_fiwst = fawse;
				wfpath = WF90_PATH_A;
				twue_bpath = twue;
				wtwphy->num_totaw_wfpath = 1;
			}
		} ewse if (mac0_initwadiob_fiwst) {
			/* Mac0 use PHY1 wwite */
			if (wfpath == WF90_PATH_A)
				wtwhaw->duwing_mac0init_wadiob = fawse;
			if (wfpath == WF90_PATH_B) {
				wtwhaw->duwing_mac0init_wadiob = twue;
				mac0_initwadiob_fiwst = fawse;
				need_pwwdown_wadiob = twue;
				wfpath = WF90_PATH_A;
				twue_bpath = twue;
				wtwphy->num_totaw_wfpath = 1;
			}
		}
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
		/* Set bit numbew of Addwess and Data fow WF wegistew */
		/* Set 1 to 4 bits fow 8255 */
		wtw_set_bbweg(hw, pphyweg->wfhssi_pawa2,
			      B3WIWEADDWESSWENGTH, 0x0);
		udeway(1);
		/* Set 0 to 12  bits fow 8255 */
		wtw_set_bbweg(hw, pphyweg->wfhssi_pawa2, B3WIWEDATAWENGTH, 0x0);
		udeway(1);
		switch (wfpath) {
		case WF90_PATH_A:
			if (twue_bpath)
				wtstatus = wtw92d_phy_config_wf_with_headewfiwe(
						hw, wadiob_txt,
						(enum wadio_path)wfpath);
			ewse
				wtstatus = wtw92d_phy_config_wf_with_headewfiwe(
					     hw, wadioa_txt,
					     (enum wadio_path)wfpath);
			bweak;
		case WF90_PATH_B:
			wtstatus =
			    wtw92d_phy_config_wf_with_headewfiwe(hw, wadiob_txt,
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
			wtw_set_bbweg(hw, pphyweg->wfintfs, BWFSI_WFENV,
				      u4_wegvawue);
			bweak;
		case WF90_PATH_B:
		case WF90_PATH_D:
			wtw_set_bbweg(hw, pphyweg->wfintfs, BWFSI_WFENV << 16,
				      u4_wegvawue);
			bweak;
		}
		if (!wtstatus) {
			wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE,
				"Wadio[%d] Faiw!!\n", wfpath);
			goto phy_wf_cfg_faiw;
		}

	}

	/* check MAC0 enabwe ow not again, if enabwed,
	 * not powew down wadio A. */
	/* check MAC1 enabwe ow not again, if enabwed,
	 * not powew down wadio B. */
	if (need_pwwdown_wadioa)
		wtw92d_phy_powewdown_anothewphy(hw, fawse);
	ewse if (need_pwwdown_wadiob)
		wtw92d_phy_powewdown_anothewphy(hw, twue);
	wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE, "<---\n");
	wetuwn wtstatus;

phy_wf_cfg_faiw:
	wetuwn wtstatus;
}
