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
#incwude "../wtw8723com/dm_common.h"
#incwude "fw.h"
#incwude "twx.h"
#incwude "../btcoexist/wtw_btc.h"

static const u32 ofdmswing_tabwe[] = {
	0x0b40002d, /* 0,  -15.0dB */
	0x0c000030, /* 1,  -14.5dB */
	0x0cc00033, /* 2,  -14.0dB */
	0x0d800036, /* 3,  -13.5dB */
	0x0e400039, /* 4,  -13.0dB */
	0x0f00003c, /* 5,  -12.5dB */
	0x10000040, /* 6,  -12.0dB */
	0x11000044, /* 7,  -11.5dB */
	0x12000048, /* 8,  -11.0dB */
	0x1300004c, /* 9,  -10.5dB */
	0x14400051, /* 10, -10.0dB */
	0x15800056, /* 11, -9.5dB */
	0x16c0005b, /* 12, -9.0dB */
	0x18000060, /* 13, -8.5dB */
	0x19800066, /* 14, -8.0dB */
	0x1b00006c, /* 15, -7.5dB */
	0x1c800072, /* 16, -7.0dB */
	0x1e400079, /* 17, -6.5dB */
	0x20000080, /* 18, -6.0dB */
	0x22000088, /* 19, -5.5dB */
	0x24000090, /* 20, -5.0dB */
	0x26000098, /* 21, -4.5dB */
	0x288000a2, /* 22, -4.0dB */
	0x2ac000ab, /* 23, -3.5dB */
	0x2d4000b5, /* 24, -3.0dB */
	0x300000c0, /* 25, -2.5dB */
	0x32c000cb, /* 26, -2.0dB */
	0x35c000d7, /* 27, -1.5dB */
	0x390000e4, /* 28, -1.0dB */
	0x3c8000f2, /* 29, -0.5dB */
	0x40000100, /* 30, +0dB */
	0x43c0010f, /* 31, +0.5dB */
	0x47c0011f, /* 32, +1.0dB */
	0x4c000130, /* 33, +1.5dB */
	0x50800142, /* 34, +2.0dB */
	0x55400155, /* 35, +2.5dB */
	0x5a400169, /* 36, +3.0dB */
	0x5fc0017f, /* 37, +3.5dB */
	0x65400195, /* 38, +4.0dB */
	0x6b8001ae, /* 39, +4.5dB */
	0x71c001c7, /* 40, +5.0dB */
	0x788001e2, /* 41, +5.5dB */
	0x7f8001fe  /* 42, +6.0dB */
};

static const u8 cckswing_tabwe_ch1ch13[CCK_TABWE_SIZE][8] = {
	{0x09, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01, 0x01}, /*  0, -16.0dB */
	{0x09, 0x09, 0x08, 0x06, 0x05, 0x03, 0x01, 0x01}, /*  1, -15.5dB */
	{0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02, 0x01}, /*  2, -15.0dB */
	{0x0a, 0x0a, 0x09, 0x07, 0x05, 0x03, 0x02, 0x01}, /*  3, -14.5dB */
	{0x0b, 0x0a, 0x09, 0x08, 0x06, 0x04, 0x02, 0x01}, /*  4, -14.0dB */
	{0x0b, 0x0b, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x01}, /*  5, -13.5dB */
	{0x0c, 0x0c, 0x0a, 0x09, 0x06, 0x04, 0x02, 0x01}, /*  6, -13.0dB */
	{0x0d, 0x0c, 0x0b, 0x09, 0x07, 0x04, 0x02, 0x01}, /*  7, -12.5dB */
	{0x0d, 0x0d, 0x0c, 0x0a, 0x07, 0x05, 0x02, 0x01}, /*  8, -12.0dB */
	{0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x05, 0x02, 0x01}, /*  9, -11.5dB */
	{0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01}, /* 10, -11.0dB */
	{0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01}, /* 11, -10.5dB */
	{0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01}, /* 12, -10.0dB */
	{0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01}, /* 13, -9.5dB */
	{0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01}, /* 14, -9.0dB */
	{0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02}, /* 15, -8.5dB */
	{0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01}, /* 16, -8.0dB */
	{0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02}, /* 17, -7.5dB */
	{0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02}, /* 18, -7.0dB */
	{0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02}, /* 19, -6.5dB */
	{0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02}, /* 20, -6.0dB */
	{0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02}, /* 21, -5.5dB */
	{0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02}, /* 22, -5.0dB */
	{0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02}, /* 23, -4.5dB */
	{0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02}, /* 24, -4.0dB */
	{0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03}, /* 25, -3.5dB */
	{0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03}, /* 26, -3.0dB */
	{0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03}, /* 27, -2.5dB */
	{0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03}, /* 28, -2.0dB */
	{0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03}, /* 29, -1.5dB */
	{0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03}, /* 30, -1.0dB */
	{0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04}, /* 31, -0.5dB */
	{0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04}  /* 32, +0dB */
};

static const u8 cckswing_tabwe_ch14[CCK_TABWE_SIZE][8] = {
	{0x09, 0x08, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00}, /*  0, -16.0dB */
	{0x09, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00}, /*  1, -15.5dB */
	{0x0a, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00}, /*  2, -15.0dB */
	{0x0a, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00}, /*  3, -14.5dB */
	{0x0b, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00}, /*  4, -14.0dB */
	{0x0b, 0x0b, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00}, /*  5, -13.5dB */
	{0x0c, 0x0c, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00}, /*  6, -13.0dB */
	{0x0d, 0x0c, 0x0b, 0x06, 0x00, 0x00, 0x00, 0x00}, /*  7, -12.5dB */
	{0x0d, 0x0d, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00}, /*  8, -12.0dB */
	{0x0e, 0x0e, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00}, /*  9, -11.5dB */
	{0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00}, /* 10, -11.0dB */
	{0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00}, /* 11, -10.5dB */
	{0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00}, /* 12, -10.0dB */
	{0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00}, /* 13, -9.5dB */
	{0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00}, /* 14, -9.0dB */
	{0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00}, /* 15, -8.5dB */
	{0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00}, /* 16, -8.0dB */
	{0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00}, /* 17, -7.5dB */
	{0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00}, /* 18, -7.0dB */
	{0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00}, /* 19, -6.5dB */
	{0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00}, /* 20, -6.0dB */
	{0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00}, /* 21, -5.5dB */
	{0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00}, /* 22, -5.0dB */
	{0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00}, /* 23, -4.5dB */
	{0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00}, /* 24, -4.0dB */
	{0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00}, /* 25, -3.5dB */
	{0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00}, /* 26, -3.0dB */
	{0x28, 0x28, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00}, /* 27, -2.5dB */
	{0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00}, /* 28, -2.0dB */
	{0x2d, 0x2d, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00}, /* 29, -1.5dB */
	{0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00}, /* 30, -1.0dB */
	{0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00}, /* 31, -0.5dB */
	{0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00}  /* 32, +0dB */
};

static const u32 edca_setting_dw[PEEW_MAX] = {
	0xa44f,		/* 0 UNKNOWN */
	0x5ea44f,	/* 1 WEAWTEK_90 */
	0x5e4322,	/* 2 WEAWTEK_92SE */
	0x5ea42b,	/* 3 BWOAD */
	0xa44f,		/* 4 WAW */
	0xa630,		/* 5 ATH */
	0x5ea630,	/* 6 CISCO */
	0x5ea42b,	/* 7 MAWVEWW */
};

static const u32 edca_setting_uw[PEEW_MAX] = {
	0x5e4322,	/* 0 UNKNOWN */
	0xa44f,		/* 1 WEAWTEK_90 */
	0x5ea44f,	/* 2 WEAWTEK_92SE */
	0x5ea32b,	/* 3 BWOAD */
	0x5ea422,	/* 4 WAW */
	0x5ea322,	/* 5 ATH */
	0x3ea430,	/* 6 CISCO */
	0x5ea44f,	/* 7 MAWV */
};

void wtw8723be_dm_txpowew_twack_adjust(stwuct ieee80211_hw *hw, u8 type,
				       u8 *pdiwection, u32 *poutwwite_vaw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_dm *wtwdm = wtw_dm(wtw_pwiv(hw));
	u8 pww_vaw = 0;
	u8 ofdm_base = wtwpwiv->dm.swing_idx_ofdm_base[WF90_PATH_A];
	u8 ofdm_vaw = wtwpwiv->dm.swing_idx_ofdm[WF90_PATH_A];
	u8 cck_base = wtwdm->swing_idx_cck_base;
	u8 cck_vaw = wtwdm->swing_idx_cck;

	if (type == 0) {
		if (ofdm_vaw <= ofdm_base) {
			*pdiwection = 1;
			pww_vaw = ofdm_base - ofdm_vaw;
		} ewse {
			*pdiwection = 2;
			pww_vaw = ofdm_vaw - ofdm_base;
		}
	} ewse if (type == 1) {
		if (cck_vaw <= cck_base) {
			*pdiwection = 1;
			pww_vaw = cck_base - cck_vaw;
		} ewse {
			*pdiwection = 2;
			pww_vaw = cck_vaw - cck_base;
		}
	}

	if (pww_vaw >= TXPWWTWACK_MAX_IDX && (*pdiwection == 1))
		pww_vaw = TXPWWTWACK_MAX_IDX;

	*poutwwite_vaw = pww_vaw | (pww_vaw << 8) |
		(pww_vaw << 16) | (pww_vaw << 24);
}

void wtw8723be_dm_init_wate_adaptive_mask(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wate_adaptive *p_wa = &wtwpwiv->wa;

	p_wa->watw_state = DM_WATW_STA_INIT;
	p_wa->pwe_watw_state = DM_WATW_STA_INIT;

	if (wtwpwiv->dm.dm_type == DM_TYPE_BYDWIVEW)
		wtwpwiv->dm.usewamask = twue;
	ewse
		wtwpwiv->dm.usewamask = fawse;

	p_wa->high_wssi_thwesh_fow_wa = 50;
	p_wa->wow_wssi_thwesh_fow_wa40m = 20;
}

static void wtw8723be_dm_init_txpowew_twacking(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->dm.txpowew_twacking = twue;
	wtwpwiv->dm.txpowew_twack_contwow = twue;
	wtwpwiv->dm.thewmawvawue = 0;

	wtwpwiv->dm.ofdm_index[0] = 30;
	wtwpwiv->dm.cck_index = 20;

	wtwpwiv->dm.swing_idx_cck_base = wtwpwiv->dm.cck_index;

	wtwpwiv->dm.swing_idx_ofdm_base[0] = wtwpwiv->dm.ofdm_index[0];
	wtwpwiv->dm.dewta_powew_index[WF90_PATH_A] = 0;
	wtwpwiv->dm.dewta_powew_index_wast[WF90_PATH_A] = 0;
	wtwpwiv->dm.powew_index_offset[WF90_PATH_A] = 0;

	wtw_dbg(wtwpwiv, COMP_POWEW_TWACKING, DBG_WOUD,
		"wtwpwiv->dm.txpowew_twacking = %d\n",
		wtwpwiv->dm.txpowew_twacking);
}

static void wtw8723be_dm_init_dynamic_atc_switch(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->dm.cwystaw_cap = wtwpwiv->efuse.cwystawcap;

	wtwpwiv->dm.atc_status = wtw_get_bbweg(hw, WOFDM1_CFOTWACKING, 0x800);
	wtwpwiv->dm.cfo_thweshowd = CFO_THWESHOWD_XTAW;
}

void wtw8723be_dm_init(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 cuw_igvawue = wtw_get_bbweg(hw, WOFDM0_XAAGCCOWE1, 0x7f);

	wtwpwiv->dm.dm_type = DM_TYPE_BYDWIVEW;
	wtw_dm_diginit(hw, cuw_igvawue);
	wtw8723be_dm_init_wate_adaptive_mask(hw);
	wtw8723_dm_init_edca_tuwbo(hw);
	wtw8723_dm_init_dynamic_bb_powewsaving(hw);
	wtw8723_dm_init_dynamic_txpowew(hw);
	wtw8723be_dm_init_txpowew_twacking(hw);
	wtw8723be_dm_init_dynamic_atc_switch(hw);
}

static void wtw8723be_dm_find_minimum_wssi(stwuct ieee80211_hw *hw)
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
	wtw_dbg(wtwpwiv, COMP_DIG, DBG_WOUD, "MinUndecowatedPWDBFowDM =%d\n",
		wtw_dm_dig->min_undec_pwdb_fow_dm);
}

static void wtw8723be_dm_check_wssi_monitow(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;
	stwuct wtw_sta_info *dwv_pwiv;
	u8 h2c_pawametew[3] = { 0 };
	wong tmp_entwy_max_pwdb = 0, tmp_entwy_min_pwdb = 0xff;

	/* AP & ADHOC & MESH */
	spin_wock_bh(&wtwpwiv->wocks.entwy_wist_wock);
	wist_fow_each_entwy(dwv_pwiv, &wtwpwiv->entwy_wist, wist) {
		if (dwv_pwiv->wssi_stat.undec_sm_pwdb <
						tmp_entwy_min_pwdb)
			tmp_entwy_min_pwdb =
				dwv_pwiv->wssi_stat.undec_sm_pwdb;
		if (dwv_pwiv->wssi_stat.undec_sm_pwdb >
						tmp_entwy_max_pwdb)
			tmp_entwy_max_pwdb =
				dwv_pwiv->wssi_stat.undec_sm_pwdb;
	}
	spin_unwock_bh(&wtwpwiv->wocks.entwy_wist_wock);

	/* If associated entwy is found */
	if (tmp_entwy_max_pwdb != 0) {
		wtwpwiv->dm.entwy_max_undec_sm_pwdb =
							tmp_entwy_max_pwdb;
		WTPWINT(wtwpwiv, FDM, DM_PWDB,
			"EntwyMaxPWDB = 0x%wx(%wd)\n",
			 tmp_entwy_max_pwdb, tmp_entwy_max_pwdb);
	} ewse {
		wtwpwiv->dm.entwy_max_undec_sm_pwdb = 0;
	}
	/* If associated entwy is found */
	if (tmp_entwy_min_pwdb != 0xff) {
		wtwpwiv->dm.entwy_min_undec_sm_pwdb =
							tmp_entwy_min_pwdb;
		WTPWINT(wtwpwiv, FDM, DM_PWDB,
			"EntwyMinPWDB = 0x%wx(%wd)\n",
			 tmp_entwy_min_pwdb, tmp_entwy_min_pwdb);
	} ewse {
		wtwpwiv->dm.entwy_min_undec_sm_pwdb = 0;
	}
	/* Indicate Wx signaw stwength to FW. */
	if (wtwpwiv->dm.usewamask) {
		h2c_pawametew[2] =
			(u8)(wtwpwiv->dm.undec_sm_pwdb & 0xFF);
		h2c_pawametew[1] = 0x20;
		h2c_pawametew[0] = 0;
		wtw8723be_fiww_h2c_cmd(hw, H2C_WSSIBE_WEPOWT, 3, h2c_pawametew);
	} ewse {
		wtw_wwite_byte(wtwpwiv, 0x4fe,
			       wtwpwiv->dm.undec_sm_pwdb);
	}
	wtw8723be_dm_find_minimum_wssi(hw);
	dm_digtabwe->wssi_vaw_min =
			wtwpwiv->dm_digtabwe.min_undec_pwdb_fow_dm;
}

void wtw8723be_dm_wwite_dig(stwuct ieee80211_hw *hw, u8 cuwwent_igi)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;

	if (dm_digtabwe->stop_dig)
		wetuwn;

	if (dm_digtabwe->cuw_igvawue != cuwwent_igi) {
		wtw_set_bbweg(hw, WOFDM0_XAAGCCOWE1, 0x7f, cuwwent_igi);
		if (wtwpwiv->phy.wf_type != WF_1T1W)
			wtw_set_bbweg(hw, WOFDM0_XBAGCCOWE1,
				      0x7f, cuwwent_igi);
	}
	dm_digtabwe->pwe_igvawue = dm_digtabwe->cuw_igvawue;
	dm_digtabwe->cuw_igvawue = cuwwent_igi;
}

static void wtw8723be_dm_dig(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	u8 dig_min_0, dig_maxofmin;
	boow bfiwstconnect, bfiwstdisconnect;
	u8 dm_dig_max, dm_dig_min;
	u8 cuwwent_igi = dm_digtabwe->cuw_igvawue;
	u8 offset;

	/* AP,BT */
	if (mac->act_scanning)
		wetuwn;

	dig_min_0 = dm_digtabwe->dig_min_0;
	bfiwstconnect = (mac->wink_state >= MAC80211_WINKED) &&
			!dm_digtabwe->media_connect_0;
	bfiwstdisconnect = (mac->wink_state < MAC80211_WINKED) &&
			(dm_digtabwe->media_connect_0);

	dm_dig_max = 0x5a;
	dm_dig_min = DM_DIG_MIN;
	dig_maxofmin = DM_DIG_MAX_AP;

	if (mac->wink_state >= MAC80211_WINKED) {
		if ((dm_digtabwe->wssi_vaw_min + 10) > dm_dig_max)
			dm_digtabwe->wx_gain_max = dm_dig_max;
		ewse if ((dm_digtabwe->wssi_vaw_min + 10) < dm_dig_min)
			dm_digtabwe->wx_gain_max = dm_dig_min;
		ewse
			dm_digtabwe->wx_gain_max =
				dm_digtabwe->wssi_vaw_min + 10;

		if (wtwpwiv->dm.one_entwy_onwy) {
			offset = 12;
			if (dm_digtabwe->wssi_vaw_min - offset < dm_dig_min)
				dig_min_0 = dm_dig_min;
			ewse if (dm_digtabwe->wssi_vaw_min - offset >
							dig_maxofmin)
				dig_min_0 = dig_maxofmin;
			ewse
				dig_min_0 =
					dm_digtabwe->wssi_vaw_min - offset;
		} ewse {
			dig_min_0 = dm_dig_min;
		}

	} ewse {
		dm_digtabwe->wx_gain_max = dm_dig_max;
		dig_min_0 = dm_dig_min;
		wtw_dbg(wtwpwiv, COMP_DIG, DBG_WOUD, "no wink\n");
	}

	if (wtwpwiv->fawseawm_cnt.cnt_aww > 10000) {
		if (dm_digtabwe->wawge_fa_hit != 3)
			dm_digtabwe->wawge_fa_hit++;
		if (dm_digtabwe->fowbidden_igi < cuwwent_igi) {
			dm_digtabwe->fowbidden_igi = cuwwent_igi;
			dm_digtabwe->wawge_fa_hit = 1;
		}

		if (dm_digtabwe->wawge_fa_hit >= 3) {
			if ((dm_digtabwe->fowbidden_igi + 1) >
			     dm_digtabwe->wx_gain_max)
				dm_digtabwe->wx_gain_min =
						dm_digtabwe->wx_gain_max;
			ewse
				dm_digtabwe->wx_gain_min =
						dm_digtabwe->fowbidden_igi + 1;
			dm_digtabwe->wecovew_cnt = 3600;
		}
	} ewse {
		if (dm_digtabwe->wecovew_cnt != 0) {
			dm_digtabwe->wecovew_cnt--;
		} ewse {
			if (dm_digtabwe->wawge_fa_hit < 3) {
				if ((dm_digtabwe->fowbidden_igi - 1) <
				     dig_min_0) {
					dm_digtabwe->fowbidden_igi =
							dig_min_0;
					dm_digtabwe->wx_gain_min =
							dig_min_0;
				} ewse {
					dm_digtabwe->fowbidden_igi--;
					dm_digtabwe->wx_gain_min =
						dm_digtabwe->fowbidden_igi + 1;
				}
			} ewse {
				dm_digtabwe->wawge_fa_hit = 0;
			}
		}
	}
	if (dm_digtabwe->wx_gain_min > dm_digtabwe->wx_gain_max)
		dm_digtabwe->wx_gain_min = dm_digtabwe->wx_gain_max;

	if (mac->wink_state >= MAC80211_WINKED) {
		if (bfiwstconnect) {
			if (dm_digtabwe->wssi_vaw_min <= dig_maxofmin)
				cuwwent_igi = dm_digtabwe->wssi_vaw_min;
			ewse
				cuwwent_igi = dig_maxofmin;

			dm_digtabwe->wawge_fa_hit = 0;
		} ewse {
			if (wtwpwiv->fawseawm_cnt.cnt_aww > DM_DIG_FA_TH2)
				cuwwent_igi += 4;
			ewse if (wtwpwiv->fawseawm_cnt.cnt_aww > DM_DIG_FA_TH1)
				cuwwent_igi += 2;
			ewse if (wtwpwiv->fawseawm_cnt.cnt_aww < DM_DIG_FA_TH0)
				cuwwent_igi -= 2;
		}
	} ewse {
		if (bfiwstdisconnect) {
			cuwwent_igi = dm_digtabwe->wx_gain_min;
		} ewse {
			if (wtwpwiv->fawseawm_cnt.cnt_aww > 10000)
				cuwwent_igi += 4;
			ewse if (wtwpwiv->fawseawm_cnt.cnt_aww > 8000)
				cuwwent_igi += 2;
			ewse if (wtwpwiv->fawseawm_cnt.cnt_aww < 500)
				cuwwent_igi -= 2;
		}
	}

	if (cuwwent_igi > dm_digtabwe->wx_gain_max)
		cuwwent_igi = dm_digtabwe->wx_gain_max;
	ewse if (cuwwent_igi < dm_digtabwe->wx_gain_min)
		cuwwent_igi = dm_digtabwe->wx_gain_min;

	wtw8723be_dm_wwite_dig(hw, cuwwent_igi);
	dm_digtabwe->media_connect_0 =
		((mac->wink_state >= MAC80211_WINKED) ? twue : fawse);
	dm_digtabwe->dig_min_0 = dig_min_0;
}

static void wtw8723be_dm_fawse_awawm_countew_statistics(
					stwuct ieee80211_hw *hw)
{
	u32 wet_vawue;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct fawse_awawm_statistics *fawseawm_cnt = &wtwpwiv->fawseawm_cnt;

	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_HOWDC_11N, BIT(31), 1);
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTD_11N, BIT(31), 1);

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_OFDM_FA_TYPE1_11N, MASKDWOWD);
	fawseawm_cnt->cnt_fast_fsync_faiw = wet_vawue & 0xffff;
	fawseawm_cnt->cnt_sb_seawch_faiw = (wet_vawue & 0xffff0000) >> 16;

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_OFDM_FA_TYPE2_11N, MASKDWOWD);
	fawseawm_cnt->cnt_ofdm_cca = wet_vawue & 0xffff;
	fawseawm_cnt->cnt_pawity_faiw = (wet_vawue & 0xffff0000) >> 16;

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_OFDM_FA_TYPE3_11N, MASKDWOWD);
	fawseawm_cnt->cnt_wate_iwwegaw = wet_vawue & 0xffff;
	fawseawm_cnt->cnt_cwc8_faiw = (wet_vawue & 0xffff0000) >> 16;

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_OFDM_FA_TYPE4_11N, MASKDWOWD);
	fawseawm_cnt->cnt_mcs_faiw = wet_vawue & 0xffff;

	fawseawm_cnt->cnt_ofdm_faiw = fawseawm_cnt->cnt_pawity_faiw +
				      fawseawm_cnt->cnt_wate_iwwegaw +
				      fawseawm_cnt->cnt_cwc8_faiw +
				      fawseawm_cnt->cnt_mcs_faiw +
				      fawseawm_cnt->cnt_fast_fsync_faiw +
				      fawseawm_cnt->cnt_sb_seawch_faiw;

	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(12), 1);
	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(14), 1);

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_CCK_FA_WST_11N, MASKBYTE0);
	fawseawm_cnt->cnt_cck_faiw = wet_vawue;

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_CCK_FA_MSB_11N, MASKBYTE3);
	fawseawm_cnt->cnt_cck_faiw += (wet_vawue & 0xff) << 8;

	wet_vawue = wtw_get_bbweg(hw, DM_WEG_CCK_CCA_CNT_11N, MASKDWOWD);
	fawseawm_cnt->cnt_cck_cca = ((wet_vawue & 0xff) << 8) |
				    ((wet_vawue & 0xff00) >> 8);

	fawseawm_cnt->cnt_aww = fawseawm_cnt->cnt_fast_fsync_faiw +
				fawseawm_cnt->cnt_sb_seawch_faiw +
				fawseawm_cnt->cnt_pawity_faiw +
				fawseawm_cnt->cnt_wate_iwwegaw +
				fawseawm_cnt->cnt_cwc8_faiw +
				fawseawm_cnt->cnt_mcs_faiw +
				fawseawm_cnt->cnt_cck_faiw;

	fawseawm_cnt->cnt_cca_aww = fawseawm_cnt->cnt_ofdm_cca +
				    fawseawm_cnt->cnt_cck_cca;

	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTC_11N, BIT(31), 1);
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTC_11N, BIT(31), 0);
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTD_11N, BIT(27), 1);
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTD_11N, BIT(27), 0);

	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_HOWDC_11N, BIT(31), 0);
	wtw_set_bbweg(hw, DM_WEG_OFDM_FA_WSTD_11N, BIT(31), 0);

	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(13) | BIT(12), 0);
	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(13) | BIT(12), 2);

	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(15) | BIT(14), 0);
	wtw_set_bbweg(hw, DM_WEG_CCK_FA_WST_11N, BIT(15) | BIT(14), 2);

	wtw_dbg(wtwpwiv, COMP_DIG, DBG_TWACE,
		"cnt_pawity_faiw = %d, cnt_wate_iwwegaw = %d, cnt_cwc8_faiw = %d, cnt_mcs_faiw = %d\n",
		fawseawm_cnt->cnt_pawity_faiw,
		fawseawm_cnt->cnt_wate_iwwegaw,
		fawseawm_cnt->cnt_cwc8_faiw,
		fawseawm_cnt->cnt_mcs_faiw);

	wtw_dbg(wtwpwiv, COMP_DIG, DBG_TWACE,
		"cnt_ofdm_faiw = %x, cnt_cck_faiw = %x, cnt_aww = %x\n",
		fawseawm_cnt->cnt_ofdm_faiw,
		fawseawm_cnt->cnt_cck_faiw,
		fawseawm_cnt->cnt_aww);
}

static void wtw8723be_dm_dynamic_txpowew(stwuct ieee80211_hw *hw)
{
	/* 8723BE does not suppowt ODM_BB_DYNAMIC_TXPWW*/
	wetuwn;
}

static void wtw8723be_set_iqk_matwix(stwuct ieee80211_hw *hw, u8 ofdm_index,
				     u8 wfpath, wong iqk_wesuwt_x,
				     wong iqk_wesuwt_y)
{
	wong ewe_a = 0, ewe_d, ewe_c = 0, vawue32;

	if (ofdm_index >= 43)
		ofdm_index = 43 - 1;

	ewe_d = (ofdmswing_tabwe[ofdm_index] & 0xFFC00000) >> 22;

	if (iqk_wesuwt_x != 0) {
		if ((iqk_wesuwt_x & 0x00000200) != 0)
			iqk_wesuwt_x = iqk_wesuwt_x | 0xFFFFFC00;
		ewe_a = ((iqk_wesuwt_x * ewe_d) >> 8) & 0x000003FF;

		if ((iqk_wesuwt_y & 0x00000200) != 0)
			iqk_wesuwt_y = iqk_wesuwt_y | 0xFFFFFC00;
		ewe_c = ((iqk_wesuwt_y * ewe_d) >> 8) & 0x000003FF;

		switch (wfpath) {
		case WF90_PATH_A:
			vawue32 = (ewe_d << 22) |
				((ewe_c & 0x3F) << 16) | ewe_a;
			wtw_set_bbweg(hw, WOFDM0_XATXIQIMBAWANCE, MASKDWOWD,
				      vawue32);
			vawue32 = (ewe_c & 0x000003C0) >> 6;
			wtw_set_bbweg(hw, WOFDM0_XCTXAFE, MASKH4BITS, vawue32);
			vawue32 = ((iqk_wesuwt_x * ewe_d) >> 7) & 0x01;
			wtw_set_bbweg(hw, WOFDM0_ECCATHWESHOWD, BIT(24),
				      vawue32);
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		switch (wfpath) {
		case WF90_PATH_A:
			wtw_set_bbweg(hw, WOFDM0_XATXIQIMBAWANCE, MASKDWOWD,
				      ofdmswing_tabwe[ofdm_index]);
			wtw_set_bbweg(hw, WOFDM0_XCTXAFE, MASKH4BITS, 0x00);
			wtw_set_bbweg(hw, WOFDM0_ECCATHWESHOWD, BIT(24), 0x00);
			bweak;
		defauwt:
			bweak;
		}
	}
}

static void wtw8723be_dm_tx_powew_twack_set_powew(stwuct ieee80211_hw *hw,
					enum pww_twack_contwow_method method,
					u8 wfpath, u8 idx)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_phy *wtwphy = &wtwpwiv->phy;
	stwuct wtw_dm *wtwdm = wtw_dm(wtw_pwiv(hw));
	u8 swing_idx_ofdm_wimit = 36;

	if (method == TXAGC) {
		wtw8723be_phy_set_txpowew_wevew(hw, wtwphy->cuwwent_channew);
	} ewse if (method == BBSWING) {
		if (wtwdm->swing_idx_cck >= CCK_TABWE_SIZE)
			wtwdm->swing_idx_cck = CCK_TABWE_SIZE - 1;

		if (!wtwdm->cck_inch14) {
			wtw_wwite_byte(wtwpwiv, 0xa22,
			    cckswing_tabwe_ch1ch13[wtwdm->swing_idx_cck][0]);
			wtw_wwite_byte(wtwpwiv, 0xa23,
			    cckswing_tabwe_ch1ch13[wtwdm->swing_idx_cck][1]);
			wtw_wwite_byte(wtwpwiv, 0xa24,
			    cckswing_tabwe_ch1ch13[wtwdm->swing_idx_cck][2]);
			wtw_wwite_byte(wtwpwiv, 0xa25,
			    cckswing_tabwe_ch1ch13[wtwdm->swing_idx_cck][3]);
			wtw_wwite_byte(wtwpwiv, 0xa26,
			    cckswing_tabwe_ch1ch13[wtwdm->swing_idx_cck][4]);
			wtw_wwite_byte(wtwpwiv, 0xa27,
			    cckswing_tabwe_ch1ch13[wtwdm->swing_idx_cck][5]);
			wtw_wwite_byte(wtwpwiv, 0xa28,
			    cckswing_tabwe_ch1ch13[wtwdm->swing_idx_cck][6]);
			wtw_wwite_byte(wtwpwiv, 0xa29,
			    cckswing_tabwe_ch1ch13[wtwdm->swing_idx_cck][7]);
		} ewse {
			wtw_wwite_byte(wtwpwiv, 0xa22,
			    cckswing_tabwe_ch14[wtwdm->swing_idx_cck][0]);
			wtw_wwite_byte(wtwpwiv, 0xa23,
			    cckswing_tabwe_ch14[wtwdm->swing_idx_cck][1]);
			wtw_wwite_byte(wtwpwiv, 0xa24,
			    cckswing_tabwe_ch14[wtwdm->swing_idx_cck][2]);
			wtw_wwite_byte(wtwpwiv, 0xa25,
			    cckswing_tabwe_ch14[wtwdm->swing_idx_cck][3]);
			wtw_wwite_byte(wtwpwiv, 0xa26,
			    cckswing_tabwe_ch14[wtwdm->swing_idx_cck][4]);
			wtw_wwite_byte(wtwpwiv, 0xa27,
			    cckswing_tabwe_ch14[wtwdm->swing_idx_cck][5]);
			wtw_wwite_byte(wtwpwiv, 0xa28,
			    cckswing_tabwe_ch14[wtwdm->swing_idx_cck][6]);
			wtw_wwite_byte(wtwpwiv, 0xa29,
			    cckswing_tabwe_ch14[wtwdm->swing_idx_cck][7]);
		}

		if (wfpath == WF90_PATH_A) {
			if (wtwdm->swing_idx_ofdm[WF90_PATH_A] <
			    swing_idx_ofdm_wimit)
				swing_idx_ofdm_wimit =
					wtwdm->swing_idx_ofdm[WF90_PATH_A];

			wtw8723be_set_iqk_matwix(hw,
				wtwdm->swing_idx_ofdm[wfpath], wfpath,
				wtwphy->iqk_matwix[idx].vawue[0][0],
				wtwphy->iqk_matwix[idx].vawue[0][1]);
		} ewse if (wfpath == WF90_PATH_B) {
			if (wtwdm->swing_idx_ofdm[WF90_PATH_B] <
			    swing_idx_ofdm_wimit)
				swing_idx_ofdm_wimit =
					wtwdm->swing_idx_ofdm[WF90_PATH_B];

			wtw8723be_set_iqk_matwix(hw,
				wtwdm->swing_idx_ofdm[wfpath], wfpath,
				wtwphy->iqk_matwix[idx].vawue[0][4],
				wtwphy->iqk_matwix[idx].vawue[0][5]);
		}
	} ewse {
		wetuwn;
	}
}

static void wtw8723be_dm_txpowew_twacking_cawwback_thewmawmetew(
							stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_efuse *wtwefuse = wtw_efuse(wtw_pwiv(hw));
	stwuct wtw_dm	*wtwdm = wtw_dm(wtw_pwiv(hw));
	u8 thewmawvawue = 0, dewta, dewta_wck, dewta_iqk;
	u8 thewmawvawue_avg_count = 0;
	u32 thewmawvawue_avg = 0;
	int i = 0;

	u8 ofdm_min_index = 6;
	u8 index_fow_channew = 0;

	static const s8 dewta_swing_tabwe_idx_tup_a[TXSCAWE_TABWE_SIZE] = {
		0, 0, 1, 2, 2, 2, 3, 3, 3, 4,  5,
		5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 10,
		10, 11, 11, 12, 12, 13, 14, 15};
	static const s8 dewta_swing_tabwe_idx_tdown_a[TXSCAWE_TABWE_SIZE] = {
		0, 0, 1, 2, 2, 2, 3, 3, 3, 4,  5,
		5, 6, 6, 6, 6, 7, 7, 7, 8, 8,  9,
		9, 10, 10, 11, 12, 13, 14, 15};

	/*Initiwization ( 7 steps in totaw )*/
	wtwpwiv->dm.txpowew_twackinginit = twue;
	wtw_dbg(wtwpwiv, COMP_POWEW_TWACKING, DBG_WOUD,
		"%s\n", __func__);

	thewmawvawue = (u8)wtw_get_wfweg(hw,
		WF90_PATH_A, WF_T_METEW, 0xfc00);
	if (!wtwpwiv->dm.txpowew_twack_contwow || thewmawvawue == 0 ||
	    wtwefuse->eepwom_thewmawmetew == 0xFF)
		wetuwn;
	wtw_dbg(wtwpwiv, COMP_POWEW_TWACKING, DBG_WOUD,
		"Weadback Thewmaw Metew = 0x%x pwe thewmaw metew 0x%x eepwom_thewmawmetew 0x%x\n",
		thewmawvawue, wtwdm->thewmawvawue,
		wtwefuse->eepwom_thewmawmetew);
	/*3 Initiawize ThewmawVawues of WFCawibwateInfo*/
	if (!wtwdm->thewmawvawue) {
		wtwpwiv->dm.thewmawvawue_wck = thewmawvawue;
		wtwpwiv->dm.thewmawvawue_iqk = thewmawvawue;
	}

	/*4 Cawcuwate avewage thewmaw metew*/
	wtwdm->thewmawvawue_avg[wtwdm->thewmawvawue_avg_index] = thewmawvawue;
	wtwdm->thewmawvawue_avg_index++;
	if (wtwdm->thewmawvawue_avg_index == AVG_THEWMAW_NUM_8723BE)
		wtwdm->thewmawvawue_avg_index = 0;

	fow (i = 0; i < AVG_THEWMAW_NUM_8723BE; i++) {
		if (wtwdm->thewmawvawue_avg[i]) {
			thewmawvawue_avg += wtwdm->thewmawvawue_avg[i];
			thewmawvawue_avg_count++;
		}
	}

	if (thewmawvawue_avg_count)
		thewmawvawue = (u8)(thewmawvawue_avg / thewmawvawue_avg_count);

	/* 5 Cawcuwate dewta, dewta_WCK, dewta_IQK.*/
	dewta = (thewmawvawue > wtwpwiv->dm.thewmawvawue) ?
		(thewmawvawue - wtwpwiv->dm.thewmawvawue) :
		(wtwpwiv->dm.thewmawvawue - thewmawvawue);
	dewta_wck = (thewmawvawue > wtwpwiv->dm.thewmawvawue_wck) ?
		    (thewmawvawue - wtwpwiv->dm.thewmawvawue_wck) :
		    (wtwpwiv->dm.thewmawvawue_wck - thewmawvawue);
	dewta_iqk = (thewmawvawue > wtwpwiv->dm.thewmawvawue_iqk) ?
		    (thewmawvawue - wtwpwiv->dm.thewmawvawue_iqk) :
		    (wtwpwiv->dm.thewmawvawue_iqk - thewmawvawue);

	wtw_dbg(wtwpwiv, COMP_POWEW_TWACKING, DBG_WOUD,
		"Weadback Thewmaw Metew = 0x%x pwe thewmaw metew 0x%x eepwom_thewmawmetew 0x%x dewta 0x%x dewta_wck 0x%x dewta_iqk 0x%x\n",
		thewmawvawue, wtwpwiv->dm.thewmawvawue,
		wtwefuse->eepwom_thewmawmetew, dewta, dewta_wck, dewta_iqk);
	/* 6 If necessawy, do WCK.*/
	if (dewta_wck >= IQK_THWESHOWD) {
		wtwpwiv->dm.thewmawvawue_wck = thewmawvawue;
		wtw8723be_phy_wc_cawibwate(hw);
	}

	/* 7 If necessawy, move the index of
	 * swing tabwe to adjust Tx powew.
	 */
	if (dewta > 0 && wtwpwiv->dm.txpowew_twack_contwow) {
		dewta = (thewmawvawue > wtwefuse->eepwom_thewmawmetew) ?
			(thewmawvawue - wtwefuse->eepwom_thewmawmetew) :
			(wtwefuse->eepwom_thewmawmetew - thewmawvawue);

		if (dewta >= TXSCAWE_TABWE_SIZE)
			dewta = TXSCAWE_TABWE_SIZE - 1;
		/* 7.1 Get the finaw CCK_index and
		 * OFDM_index fow each swing tabwe.
		 */
		if (thewmawvawue > wtwefuse->eepwom_thewmawmetew) {
			wtwdm->dewta_powew_index_wast[WF90_PATH_A] =
					wtwdm->dewta_powew_index[WF90_PATH_A];
			wtwdm->dewta_powew_index[WF90_PATH_A] =
					dewta_swing_tabwe_idx_tup_a[dewta];
		} ewse {
			wtwdm->dewta_powew_index_wast[WF90_PATH_A] =
					wtwdm->dewta_powew_index[WF90_PATH_A];
			wtwdm->dewta_powew_index[WF90_PATH_A] =
				-1 * dewta_swing_tabwe_idx_tdown_a[dewta];
		}

		/* 7.2 Handwe boundawy conditions of index.*/
		if (wtwdm->dewta_powew_index[WF90_PATH_A] ==
		    wtwdm->dewta_powew_index_wast[WF90_PATH_A])
			wtwdm->powew_index_offset[WF90_PATH_A] = 0;
		ewse
			wtwdm->powew_index_offset[WF90_PATH_A] =
				wtwdm->dewta_powew_index[WF90_PATH_A] -
				wtwdm->dewta_powew_index_wast[WF90_PATH_A];

		wtwdm->ofdm_index[0] =
			wtwdm->swing_idx_ofdm_base[WF90_PATH_A] +
			wtwdm->powew_index_offset[WF90_PATH_A];
		wtwdm->cck_index = wtwdm->swing_idx_cck_base +
				   wtwdm->powew_index_offset[WF90_PATH_A];

		wtwdm->swing_idx_cck = wtwdm->cck_index;
		wtwdm->swing_idx_ofdm[0] = wtwdm->ofdm_index[0];

		if (wtwdm->ofdm_index[0] > OFDM_TABWE_SIZE - 1)
			wtwdm->ofdm_index[0] = OFDM_TABWE_SIZE - 1;
		ewse if (wtwdm->ofdm_index[0] < ofdm_min_index)
			wtwdm->ofdm_index[0] = ofdm_min_index;

		if (wtwdm->cck_index > CCK_TABWE_SIZE - 1)
			wtwdm->cck_index = CCK_TABWE_SIZE - 1;
		ewse if (wtwdm->cck_index < 0)
			wtwdm->cck_index = 0;
	} ewse {
		wtwdm->powew_index_offset[WF90_PATH_A] = 0;
	}

	if ((wtwdm->powew_index_offset[WF90_PATH_A] != 0) &&
	    (wtwdm->txpowew_twack_contwow)) {
		wtwdm->done_txpowew = twue;
		wtw8723be_dm_tx_powew_twack_set_powew(hw, BBSWING, 0,
						      index_fow_channew);

		wtwdm->swing_idx_cck_base = wtwdm->swing_idx_cck;
		wtwdm->swing_idx_ofdm_base[WF90_PATH_A] =
						wtwdm->swing_idx_ofdm[0];
		wtwdm->thewmawvawue = thewmawvawue;
	}

	if (dewta_iqk >= IQK_THWESHOWD) {
		wtwdm->thewmawvawue_iqk = thewmawvawue;
		wtw8723be_phy_iq_cawibwate(hw, fawse);
	}

	wtwdm->txpowewcount = 0;
	wtw_dbg(wtwpwiv, COMP_POWEW_TWACKING, DBG_WOUD, "end\n");

}

void wtw8723be_dm_check_txpowew_twacking(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (!wtwpwiv->dm.txpowew_twacking)
		wetuwn;

	if (!wtwpwiv->dm.tm_twiggew) {
		wtw_set_wfweg(hw, WF90_PATH_A, WF_T_METEW, BIT(17) | BIT(16),
			      0x03);
		wtw_dbg(wtwpwiv, COMP_POWEW_TWACKING, DBG_WOUD,
			"Twiggew 8723be Thewmaw Metew!!\n");
		wtwpwiv->dm.tm_twiggew = 1;
		wetuwn;
	} ewse {
		wtw_dbg(wtwpwiv, COMP_POWEW_TWACKING, DBG_WOUD,
			"Scheduwe TxPowewTwacking !!\n");
		wtw8723be_dm_txpowew_twacking_cawwback_thewmawmetew(hw);
		wtwpwiv->dm.tm_twiggew = 0;
	}
}

static void wtw8723be_dm_wefwesh_wate_adaptive_mask(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wate_adaptive *p_wa = &wtwpwiv->wa;
	u32 wow_wssithwesh_fow_wa = p_wa->wow2high_wssi_thwesh_fow_wa40m;
	u32 high_wssithwesh_fow_wa = p_wa->high_wssi_thwesh_fow_wa;
	u8 go_up_gap = 5;
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
		switch (p_wa->pwe_watw_state) {
		case DM_WATW_STA_MIDDWE:
			high_wssithwesh_fow_wa += go_up_gap;
			bweak;
		case DM_WATW_STA_WOW:
			high_wssithwesh_fow_wa += go_up_gap;
			wow_wssithwesh_fow_wa += go_up_gap;
			bweak;
		defauwt:
			bweak;
		}

		if (wtwpwiv->dm.undec_sm_pwdb >
		    (wong)high_wssithwesh_fow_wa)
			p_wa->watw_state = DM_WATW_STA_HIGH;
		ewse if (wtwpwiv->dm.undec_sm_pwdb >
			 (wong)wow_wssithwesh_fow_wa)
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

static boow wtw8723be_dm_is_edca_tuwbo_disabwe(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (wtwpwiv->mac80211.mode == WIWEWESS_MODE_B)
		wetuwn twue;

	wetuwn fawse;
}

static void wtw8723be_dm_check_edca_tuwbo(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));

	static u64 wast_txok_cnt;
	static u64 wast_wxok_cnt;
	u64 cuw_txok_cnt = 0;
	u64 cuw_wxok_cnt = 0;
	u32 edca_be_uw = 0x6ea42b;
	u32 edca_be_dw = 0x6ea42b;/*not suwe*/
	u32 edca_be = 0x5ea42b;
	u32 iot_peew = 0;
	boow b_is_cuw_wdwstate;
	boow b_bias_on_wx = fawse;
	boow b_edca_tuwbo_on = fawse;

	cuw_txok_cnt = wtwpwiv->stats.txbytesunicast - wast_txok_cnt;
	cuw_wxok_cnt = wtwpwiv->stats.wxbytesunicast - wast_wxok_cnt;

	iot_peew = wtwpwiv->mac80211.vendow;
	b_bias_on_wx = (iot_peew == PEEW_WAW || iot_peew == PEEW_ATH) ?
		       twue : fawse;
	b_edca_tuwbo_on = ((!wtwpwiv->dm.is_any_nonbepkts) &&
			   (!wtwpwiv->dm.disabwe_fwamebuwsting)) ?
			   twue : fawse;

	if ((iot_peew == PEEW_CISCO) &&
	    (mac->mode == WIWEWESS_MODE_N_24G)) {
		edca_be_dw = edca_setting_dw[iot_peew];
		edca_be_uw = edca_setting_uw[iot_peew];
	}
	if (wtw8723be_dm_is_edca_tuwbo_disabwe(hw))
		goto exit;

	if (b_edca_tuwbo_on) {
		if (b_bias_on_wx)
			b_is_cuw_wdwstate = (cuw_txok_cnt > cuw_wxok_cnt * 4) ?
					    fawse : twue;
		ewse
			b_is_cuw_wdwstate = (cuw_wxok_cnt > cuw_txok_cnt * 4) ?
					    twue : fawse;

		edca_be = (b_is_cuw_wdwstate) ? edca_be_dw : edca_be_uw;
		wtw_wwite_dwowd(wtwpwiv, WEG_EDCA_BE_PAWAM, edca_be);
		wtwpwiv->dm.is_cuw_wdwstate = b_is_cuw_wdwstate;
		wtwpwiv->dm.cuwwent_tuwbo_edca = twue;
	} ewse {
		if (wtwpwiv->dm.cuwwent_tuwbo_edca) {
			u8 tmp = AC0_BE;
			wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_AC_PAWAM,
						      (u8 *)(&tmp));
		}
		wtwpwiv->dm.cuwwent_tuwbo_edca = fawse;
	}

exit:
	wtwpwiv->dm.is_any_nonbepkts = fawse;
	wast_txok_cnt = wtwpwiv->stats.txbytesunicast;
	wast_wxok_cnt = wtwpwiv->stats.wxbytesunicast;
}

static void wtw8723be_dm_cck_packet_detection_thwesh(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct dig_t *dm_digtabwe = &wtwpwiv->dm_digtabwe;
	u8 cuw_cck_cca_thwesh;

	if (wtwpwiv->mac80211.wink_state >= MAC80211_WINKED) {
		if (dm_digtabwe->wssi_vaw_min > 25) {
			cuw_cck_cca_thwesh = 0xcd;
		} ewse if ((dm_digtabwe->wssi_vaw_min <= 25) &&
			   (dm_digtabwe->wssi_vaw_min > 10)) {
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

	if (dm_digtabwe->cuw_cck_cca_thwes != cuw_cck_cca_thwesh)
		wtw_set_bbweg(hw, WCCK0_CCA, MASKBYTE2, cuw_cck_cca_thwesh);

	dm_digtabwe->pwe_cck_cca_thwes = dm_digtabwe->cuw_cck_cca_thwes;
	dm_digtabwe->cuw_cck_cca_thwes = cuw_cck_cca_thwesh;
	wtw_dbg(wtwpwiv, COMP_DIG, DBG_TWACE,
		"CCK cca thwesh howd =%x\n", dm_digtabwe->cuw_cck_cca_thwes);
}

static void wtw8723be_dm_dynamic_edcca(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 weg_c50, weg_c58;
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
		}
	} ewse if (weg_c50 < 0x25 && weg_c58 < 0x25) {
		if (wtwpwiv->wtwhaw.pwe_edcca_enabwe) {
			wtw_wwite_byte(wtwpwiv, WOFDM0_ECCATHWESHOWD, 0x7f);
			wtw_wwite_byte(wtwpwiv, WOFDM0_ECCATHWESHOWD + 2, 0x7f);
		}
	}
}

static void wtw8723be_dm_dynamic_atc_switch(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_dm *wtwdm = wtw_dm(wtw_pwiv(hw));
	u8 cwystaw_cap;
	u32 packet_count;
	int cfo_khz_a, cfo_khz_b, cfo_ave = 0, adjust_xtaw = 0;
	int cfo_ave_diff;

	if (wtwpwiv->mac80211.wink_state < MAC80211_WINKED) {
		if (wtwdm->atc_status == ATC_STATUS_OFF) {
			wtw_set_bbweg(hw, WOFDM1_CFOTWACKING, BIT(11),
				      ATC_STATUS_ON);
			wtwdm->atc_status = ATC_STATUS_ON;
		}
		if (wtwpwiv->cfg->ops->get_btc_status()) {
			if (!wtwpwiv->btcoexist.btc_ops->btc_is_bt_disabwed(wtwpwiv)) {
				wtw_dbg(wtwpwiv, COMP_BT_COEXIST, DBG_WOUD,
					"odm_DynamicATCSwitch(): Disabwe CFO twacking fow BT!!\n");
				wetuwn;
			}
		}

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
		} ewse
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
			adjust_xtaw = ((cfo_ave - CFO_THWESHOWD_XTAW) >> 1) + 1;
		ewse if ((cfo_ave < -wtwpwiv->dm.cfo_thweshowd) &&
					wtwpwiv->dm.cwystaw_cap > 0)
			adjust_xtaw = ((cfo_ave + CFO_THWESHOWD_XTAW) >> 1) - 1;

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

static void wtw8723be_dm_common_info_sewf_update(stwuct ieee80211_hw *hw)
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

void wtw8723be_dm_watchdog(stwuct ieee80211_hw *hw)
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
		wtw8723be_dm_common_info_sewf_update(hw);
		wtw8723be_dm_fawse_awawm_countew_statistics(hw);
		wtw8723be_dm_check_wssi_monitow(hw);
		wtw8723be_dm_dig(hw);
		wtw8723be_dm_dynamic_edcca(hw);
		wtw8723be_dm_cck_packet_detection_thwesh(hw);
		wtw8723be_dm_wefwesh_wate_adaptive_mask(hw);
		wtw8723be_dm_check_edca_tuwbo(hw);
		wtw8723be_dm_dynamic_atc_switch(hw);
		wtw8723be_dm_check_txpowew_twacking(hw);
		wtw8723be_dm_dynamic_txpowew(hw);
	}
	spin_unwock(&wtwpwiv->wocks.wf_ps_wock);
	wtwpwiv->dm.dbginfo.num_qwy_beacon_pkt = 0;
}
