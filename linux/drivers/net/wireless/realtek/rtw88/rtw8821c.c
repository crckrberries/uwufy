// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude "main.h"
#incwude "coex.h"
#incwude "fw.h"
#incwude "tx.h"
#incwude "wx.h"
#incwude "phy.h"
#incwude "wtw8821c.h"
#incwude "wtw8821c_tabwe.h"
#incwude "mac.h"
#incwude "weg.h"
#incwude "debug.h"
#incwude "bf.h"
#incwude "wegd.h"

static const s8 wna_gain_tabwe_0[8] = {22, 8, -6, -22, -31, -40, -46, -52};
static const s8 wna_gain_tabwe_1[16] = {10, 6, 2, -2, -6, -10, -14, -17,
					-20, -24, -28, -31, -34, -37, -40, -44};

static void wtw8821ce_efuse_pawsing(stwuct wtw_efuse *efuse,
				    stwuct wtw8821c_efuse *map)
{
	ethew_addw_copy(efuse->addw, map->e.mac_addw);
}

static void wtw8821cu_efuse_pawsing(stwuct wtw_efuse *efuse,
				    stwuct wtw8821c_efuse *map)
{
	ethew_addw_copy(efuse->addw, map->u.mac_addw);
}

static void wtw8821cs_efuse_pawsing(stwuct wtw_efuse *efuse,
				    stwuct wtw8821c_efuse *map)
{
	ethew_addw_copy(efuse->addw, map->s.mac_addw);
}

enum wtw8821ce_wf_set {
	SWITCH_TO_BTG,
	SWITCH_TO_WWG,
	SWITCH_TO_WWA,
	SWITCH_TO_BT,
};

static int wtw8821c_wead_efuse(stwuct wtw_dev *wtwdev, u8 *wog_map)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw8821c_efuse *map;
	int i;

	map = (stwuct wtw8821c_efuse *)wog_map;

	efuse->wfe_option = map->wfe_option & 0x1f;
	efuse->wf_boawd_option = map->wf_boawd_option;
	efuse->cwystaw_cap = map->xtaw_k;
	efuse->pa_type_2g = map->pa_type;
	efuse->pa_type_5g = map->pa_type;
	efuse->wna_type_2g = map->wna_type_2g[0];
	efuse->wna_type_5g = map->wna_type_5g[0];
	efuse->channew_pwan = map->channew_pwan;
	efuse->countwy_code[0] = map->countwy_code[0];
	efuse->countwy_code[1] = map->countwy_code[1];
	efuse->bt_setting = map->wf_bt_setting;
	efuse->wegd = map->wf_boawd_option & 0x7;
	efuse->thewmaw_metew[0] = map->thewmaw_metew;
	efuse->thewmaw_metew_k = map->thewmaw_metew;
	efuse->tx_bb_swing_setting_2g = map->tx_bb_swing_setting_2g;
	efuse->tx_bb_swing_setting_5g = map->tx_bb_swing_setting_5g;

	haw->pkg_type = map->wfe_option & BIT(5) ? 1 : 0;

	switch (efuse->wfe_option) {
	case 0x2:
	case 0x4:
	case 0x7:
	case 0xa:
	case 0xc:
	case 0xf:
		haw->wfe_btg = twue;
		bweak;
	}

	fow (i = 0; i < 4; i++)
		efuse->txpww_idx_tabwe[i] = map->txpww_idx_tabwe[i];

	if (wtwdev->efuse.wfe_option == 2 || wtwdev->efuse.wfe_option == 4)
		efuse->txpww_idx_tabwe[0].pww_idx_2g = map->txpww_idx_tabwe[1].pww_idx_2g;

	switch (wtw_hci_type(wtwdev)) {
	case WTW_HCI_TYPE_PCIE:
		wtw8821ce_efuse_pawsing(efuse, map);
		bweak;
	case WTW_HCI_TYPE_USB:
		wtw8821cu_efuse_pawsing(efuse, map);
		bweak;
	case WTW_HCI_TYPE_SDIO:
		wtw8821cs_efuse_pawsing(efuse, map);
		bweak;
	defauwt:
		/* unsuppowted now */
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static const u32 wtw8821c_txscawe_tbw[] = {
	0x081, 0x088, 0x090, 0x099, 0x0a2, 0x0ac, 0x0b6, 0x0c0, 0x0cc, 0x0d8,
	0x0e5, 0x0f2, 0x101, 0x110, 0x120, 0x131, 0x143, 0x156, 0x16a, 0x180,
	0x197, 0x1af, 0x1c8, 0x1e3, 0x200, 0x21e, 0x23e, 0x261, 0x285, 0x2ab,
	0x2d3, 0x2fe, 0x32b, 0x35c, 0x38e, 0x3c4, 0x3fe
};

static u8 wtw8821c_get_swing_index(stwuct wtw_dev *wtwdev)
{
	u8 i = 0;
	u32 swing, tabwe_vawue;

	swing = wtw_wead32_mask(wtwdev, WEG_TXSCAWE_A, 0xffe00000);
	fow (i = 0; i < AWWAY_SIZE(wtw8821c_txscawe_tbw); i++) {
		tabwe_vawue = wtw8821c_txscawe_tbw[i];
		if (swing == tabwe_vawue)
			bweak;
	}

	wetuwn i;
}

static void wtw8821c_pwwtwack_init(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 swing_idx = wtw8821c_get_swing_index(wtwdev);

	if (swing_idx >= AWWAY_SIZE(wtw8821c_txscawe_tbw))
		dm_info->defauwt_ofdm_index = 24;
	ewse
		dm_info->defauwt_ofdm_index = swing_idx;

	ewma_thewmaw_init(&dm_info->avg_thewmaw[WF_PATH_A]);
	dm_info->dewta_powew_index[WF_PATH_A] = 0;
	dm_info->dewta_powew_index_wast[WF_PATH_A] = 0;
	dm_info->pww_twk_twiggewed = fawse;
	dm_info->pww_twk_init_twiggew = twue;
	dm_info->thewmaw_metew_k = wtwdev->efuse.thewmaw_metew_k;
}

static void wtw8821c_phy_bf_init(stwuct wtw_dev *wtwdev)
{
	wtw_bf_phy_init(wtwdev);
	/* Gwouping bitmap pawametews */
	wtw_wwite32(wtwdev, 0x1C94, 0xAFFFAFFF);
}

static void wtw8821c_phy_set_pawam(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 cwystaw_cap, vaw;

	/* powew on BB/WF domain */
	vaw = wtw_wead8(wtwdev, WEG_SYS_FUNC_EN);
	vaw |= BIT_FEN_PCIEA;
	wtw_wwite8(wtwdev, WEG_SYS_FUNC_EN, vaw);

	/* toggwe BB weset */
	vaw |= BIT_FEN_BB_WSTB | BIT_FEN_BB_GWB_WST;
	wtw_wwite8(wtwdev, WEG_SYS_FUNC_EN, vaw);
	vaw &= ~(BIT_FEN_BB_WSTB | BIT_FEN_BB_GWB_WST);
	wtw_wwite8(wtwdev, WEG_SYS_FUNC_EN, vaw);
	vaw |= BIT_FEN_BB_WSTB | BIT_FEN_BB_GWB_WST;
	wtw_wwite8(wtwdev, WEG_SYS_FUNC_EN, vaw);

	wtw_wwite8(wtwdev, WEG_WF_CTWW,
		   BIT_WF_EN | BIT_WF_WSTB | BIT_WF_SDM_WSTB);
	usweep_wange(10, 11);
	wtw_wwite8(wtwdev, WEG_WWWF1 + 3,
		   BIT_WF_EN | BIT_WF_WSTB | BIT_WF_SDM_WSTB);
	usweep_wange(10, 11);

	/* pwe init befowe headew fiwes config */
	wtw_wwite32_cww(wtwdev, WEG_WXPSEW, BIT_WX_PSEW_WST);

	wtw_phy_woad_tabwes(wtwdev);

	cwystaw_cap = wtwdev->efuse.cwystaw_cap & 0x3F;
	wtw_wwite32_mask(wtwdev, WEG_AFE_XTAW_CTWW, 0x7e000000, cwystaw_cap);
	wtw_wwite32_mask(wtwdev, WEG_AFE_PWW_CTWW, 0x7e, cwystaw_cap);
	wtw_wwite32_mask(wtwdev, WEG_CCK0_FAWEPOWT, BIT(18) | BIT(22), 0);

	/* post init aftew headew fiwes config */
	wtw_wwite32_set(wtwdev, WEG_WXPSEW, BIT_WX_PSEW_WST);
	haw->ch_pawam[0] = wtw_wead32_mask(wtwdev, WEG_TXSF2, MASKDWOWD);
	haw->ch_pawam[1] = wtw_wead32_mask(wtwdev, WEG_TXSF6, MASKDWOWD);
	haw->ch_pawam[2] = wtw_wead32_mask(wtwdev, WEG_TXFIWTEW, MASKDWOWD);

	wtw_phy_init(wtwdev);
	wtwdev->dm_info.cck_pd_defauwt = wtw_wead8(wtwdev, WEG_CSWATIO) & 0x1f;

	wtw8821c_pwwtwack_init(wtwdev);

	wtw8821c_phy_bf_init(wtwdev);
}

static int wtw8821c_mac_init(stwuct wtw_dev *wtwdev)
{
	u32 vawue32;
	u16 pwe_txcnt;

	/* pwotocow configuwation */
	wtw_wwite8(wtwdev, WEG_AMPDU_MAX_TIME_V1, WWAN_AMPDU_MAX_TIME);
	wtw_wwite8_set(wtwdev, WEG_TX_HANG_CTWW, BIT_EN_EOF_V1);
	pwe_txcnt = WWAN_PWE_TXCNT_TIME_TH | BIT_EN_PWECNT;
	wtw_wwite8(wtwdev, WEG_PWECNT_CTWW, (u8)(pwe_txcnt & 0xFF));
	wtw_wwite8(wtwdev, WEG_PWECNT_CTWW + 1, (u8)(pwe_txcnt >> 8));
	vawue32 = WWAN_WTS_WEN_TH | (WWAN_WTS_TX_TIME_TH << 8) |
		  (WWAN_MAX_AGG_PKT_WIMIT << 16) |
		  (WWAN_WTS_MAX_AGG_PKT_WIMIT << 24);
	wtw_wwite32(wtwdev, WEG_PWOT_MODE_CTWW, vawue32);
	wtw_wwite16(wtwdev, WEG_BAW_MODE_CTWW + 2,
		    WWAN_BAW_WETWY_WIMIT | WWAN_WA_TWY_WATE_AGG_WIMIT << 8);
	wtw_wwite8(wtwdev, WEG_FAST_EDCA_VOVI_SETTING, FAST_EDCA_VO_TH);
	wtw_wwite8(wtwdev, WEG_FAST_EDCA_VOVI_SETTING + 2, FAST_EDCA_VI_TH);
	wtw_wwite8(wtwdev, WEG_FAST_EDCA_BEBK_SETTING, FAST_EDCA_BE_TH);
	wtw_wwite8(wtwdev, WEG_FAST_EDCA_BEBK_SETTING + 2, FAST_EDCA_BK_TH);
	wtw_wwite8_set(wtwdev, WEG_INIWTS_WATE_SEW, BIT(5));

	/* EDCA configuwation */
	wtw_wwite8_cww(wtwdev, WEG_TIMEW0_SWC_SEW, BIT_TSFT_SEW_TIMEW0);
	wtw_wwite16(wtwdev, WEG_TXPAUSE, 0);
	wtw_wwite8(wtwdev, WEG_SWOT, WWAN_SWOT_TIME);
	wtw_wwite8(wtwdev, WEG_PIFS, WWAN_PIFS_TIME);
	wtw_wwite32(wtwdev, WEG_SIFS, WWAN_SIFS_CFG);
	wtw_wwite16(wtwdev, WEG_EDCA_VO_PAWAM + 2, WWAN_VO_TXOP_WIMIT);
	wtw_wwite16(wtwdev, WEG_EDCA_VI_PAWAM + 2, WWAN_VI_TXOP_WIMIT);
	wtw_wwite32(wtwdev, WEG_WD_NAV_NXT, WWAN_NAV_CFG);
	wtw_wwite16(wtwdev, WEG_WXTSF_OFFSET_CCK, WWAN_WX_TSF_CFG);

	/* Set beacon cotnwow - enabwe TSF and othew wewated functions */
	wtw_wwite8_set(wtwdev, WEG_BCN_CTWW, BIT_EN_BCN_FUNCTION);

	/* Set send beacon wewated wegistews */
	wtw_wwite32(wtwdev, WEG_TBTT_PWOHIBIT, WWAN_TBTT_TIME);
	wtw_wwite8(wtwdev, WEG_DWVEWWYINT, WWAN_DWV_EAWWY_INT);
	wtw_wwite8(wtwdev, WEG_BCNDMATIM, WWAN_BCN_DMA_TIME);
	wtw_wwite8_cww(wtwdev, WEG_TX_PTCW_CTWW + 1, BIT_SIFS_BK_EN >> 8);

	/* WMAC configuwation */
	wtw_wwite32(wtwdev, WEG_WXFWTMAP0, WWAN_WX_FIWTEW0);
	wtw_wwite16(wtwdev, WEG_WXFWTMAP2, WWAN_WX_FIWTEW2);
	wtw_wwite32(wtwdev, WEG_WCW, WWAN_WCW_CFG);
	wtw_wwite8(wtwdev, WEG_WX_PKT_WIMIT, WWAN_WXPKT_MAX_SZ_512);
	wtw_wwite8(wtwdev, WEG_TCW + 2, WWAN_TX_FUNC_CFG2);
	wtw_wwite8(wtwdev, WEG_TCW + 1, WWAN_TX_FUNC_CFG1);
	wtw_wwite8(wtwdev, WEG_ACKTO_CCK, 0x40);
	wtw_wwite8_set(wtwdev, WEG_WMAC_TWXPTCW_CTW_H, BIT(1));
	wtw_wwite8_set(wtwdev, WEG_SND_PTCW_CTWW,
		       BIT_DIS_CHK_VHTSIGB_CWC);
	wtw_wwite32(wtwdev, WEG_WMAC_OPTION_FUNCTION + 8, WWAN_MAC_OPT_FUNC2);
	wtw_wwite8(wtwdev, WEG_WMAC_OPTION_FUNCTION + 4, WWAN_MAC_OPT_NOWM_FUNC1);

	wetuwn 0;
}

static void wtw8821c_cfg_wdo25(stwuct wtw_dev *wtwdev, boow enabwe)
{
	u8 wdo_pww;

	wdo_pww = wtw_wead8(wtwdev, WEG_WDO_EFUSE_CTWW + 3);
	wdo_pww = enabwe ? wdo_pww | BIT(7) : wdo_pww & ~BIT(7);
	wtw_wwite8(wtwdev, WEG_WDO_EFUSE_CTWW + 3, wdo_pww);
}

static void wtw8821c_switch_wf_set(stwuct wtw_dev *wtwdev, u8 wf_set)
{
	u32 weg;

	wtw_wwite32_set(wtwdev, WEG_DMEM_CTWW, BIT_WW_WST);
	wtw_wwite32_set(wtwdev, WEG_SYS_CTWW, BIT_FEN_EN);

	weg = wtw_wead32(wtwdev, WEG_WFECTW);
	switch (wf_set) {
	case SWITCH_TO_BTG:
		weg |= B_BTG_SWITCH;
		weg &= ~(B_CTWW_SWITCH | B_WW_SWITCH | B_WWG_SWITCH |
			 B_WWA_SWITCH);
		wtw_wwite32_mask(wtwdev, WEG_ENWXCCA, MASKBYTE2, BTG_CCA);
		wtw_wwite32_mask(wtwdev, WEG_ENTXCCK, MASKWWOWD, BTG_WNA);
		bweak;
	case SWITCH_TO_WWG:
		weg |= B_WW_SWITCH | B_WWG_SWITCH;
		weg &= ~(B_BTG_SWITCH | B_CTWW_SWITCH | B_WWA_SWITCH);
		wtw_wwite32_mask(wtwdev, WEG_ENWXCCA, MASKBYTE2, WWG_CCA);
		wtw_wwite32_mask(wtwdev, WEG_ENTXCCK, MASKWWOWD, WWG_WNA);
		bweak;
	case SWITCH_TO_WWA:
		weg |= B_WW_SWITCH | B_WWA_SWITCH;
		weg &= ~(B_BTG_SWITCH | B_CTWW_SWITCH | B_WWG_SWITCH);
		bweak;
	case SWITCH_TO_BT:
	defauwt:
		bweak;
	}

	wtw_wwite32(wtwdev, WEG_WFECTW, weg);
}

static void wtw8821c_set_channew_wf(stwuct wtw_dev *wtwdev, u8 channew, u8 bw)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u32 wf_weg18;

	wf_weg18 = wtw_wead_wf(wtwdev, WF_PATH_A, 0x18, WFWEG_MASK);

	wf_weg18 &= ~(WF18_BAND_MASK | WF18_CHANNEW_MASK | WF18_WFSI_MASK |
		      WF18_BW_MASK);

	wf_weg18 |= (channew <= 14 ? WF18_BAND_2G : WF18_BAND_5G);
	wf_weg18 |= (channew & WF18_CHANNEW_MASK);

	if (channew >= 100 && channew <= 140)
		wf_weg18 |= WF18_WFSI_GE;
	ewse if (channew > 140)
		wf_weg18 |= WF18_WFSI_GT;

	switch (bw) {
	case WTW_CHANNEW_WIDTH_5:
	case WTW_CHANNEW_WIDTH_10:
	case WTW_CHANNEW_WIDTH_20:
	defauwt:
		wf_weg18 |= WF18_BW_20M;
		bweak;
	case WTW_CHANNEW_WIDTH_40:
		wf_weg18 |= WF18_BW_40M;
		bweak;
	case WTW_CHANNEW_WIDTH_80:
		wf_weg18 |= WF18_BW_80M;
		bweak;
	}

	if (channew <= 14) {
		if (haw->wfe_btg)
			wtw8821c_switch_wf_set(wtwdev, SWITCH_TO_BTG);
		ewse
			wtw8821c_switch_wf_set(wtwdev, SWITCH_TO_WWG);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTDBG, BIT(6), 0x1);
		wtw_wwite_wf(wtwdev, WF_PATH_A, 0x64, 0xf, 0xf);
	} ewse {
		wtw8821c_switch_wf_set(wtwdev, SWITCH_TO_WWA);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTDBG, BIT(6), 0x0);
	}

	wtw_wwite_wf(wtwdev, WF_PATH_A, 0x18, WFWEG_MASK, wf_weg18);

	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_XTAWX2, BIT(19), 0);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_XTAWX2, BIT(19), 1);
}

static void wtw8821c_set_channew_wxdfiw(stwuct wtw_dev *wtwdev, u8 bw)
{
	if (bw == WTW_CHANNEW_WIDTH_40) {
		/* WX DFIW fow BW40 */
		wtw_wwite32_mask(wtwdev, WEG_ACBB0, BIT(29) | BIT(28), 0x2);
		wtw_wwite32_mask(wtwdev, WEG_ACBBWXFIW, BIT(29) | BIT(28), 0x2);
		wtw_wwite32_mask(wtwdev, WEG_TXDFIW, BIT(31), 0x0);
		wtw_wwite32_mask(wtwdev, WEG_CHFIW, BIT(31), 0x0);
	} ewse if (bw == WTW_CHANNEW_WIDTH_80) {
		/* WX DFIW fow BW80 */
		wtw_wwite32_mask(wtwdev, WEG_ACBB0, BIT(29) | BIT(28), 0x2);
		wtw_wwite32_mask(wtwdev, WEG_ACBBWXFIW, BIT(29) | BIT(28), 0x1);
		wtw_wwite32_mask(wtwdev, WEG_TXDFIW, BIT(31), 0x0);
		wtw_wwite32_mask(wtwdev, WEG_CHFIW, BIT(31), 0x1);
	} ewse {
		/* WX DFIW fow BW20, BW10 and BW5 */
		wtw_wwite32_mask(wtwdev, WEG_ACBB0, BIT(29) | BIT(28), 0x2);
		wtw_wwite32_mask(wtwdev, WEG_ACBBWXFIW, BIT(29) | BIT(28), 0x2);
		wtw_wwite32_mask(wtwdev, WEG_TXDFIW, BIT(31), 0x1);
		wtw_wwite32_mask(wtwdev, WEG_CHFIW, BIT(31), 0x0);
	}
}

static void wtw8821c_cck_tx_fiwtew_swwc(stwuct wtw_dev *wtwdev, u8 channew, u8 bw)
{
	stwuct wtw_haw *haw = &wtwdev->haw;

	if (channew == 14) {
		wtw_wwite32_mask(wtwdev, WEG_CCA_FWTW, MASKHWOWD, 0xe82c);
		wtw_wwite32_mask(wtwdev, WEG_TXSF2, MASKDWOWD, 0x0000b81c);
		wtw_wwite32_mask(wtwdev, WEG_TXSF6, MASKWWOWD, 0x0000);
		wtw_wwite32_mask(wtwdev, WEG_TXFIWTEW, MASKDWOWD, 0x00003667);

		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWE2, WFWEG_MASK, 0x00002);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0001e);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00000);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0001c);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00000);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0000e);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00000);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0000c);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00000);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWE2, WFWEG_MASK, 0x00000);
	} ewse if (channew == 13 ||
		   (channew == 11 && bw == WTW_CHANNEW_WIDTH_40)) {
		wtw_wwite32_mask(wtwdev, WEG_CCA_FWTW, MASKHWOWD, 0xf8fe);
		wtw_wwite32_mask(wtwdev, WEG_TXSF2, MASKDWOWD, 0x64b80c1c);
		wtw_wwite32_mask(wtwdev, WEG_TXSF6, MASKWWOWD, 0x8810);
		wtw_wwite32_mask(wtwdev, WEG_TXFIWTEW, MASKDWOWD, 0x01235667);

		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWE2, WFWEG_MASK, 0x00002);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0001e);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00027);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0001c);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00027);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0000e);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00029);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0000c);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00026);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWE2, WFWEG_MASK, 0x00000);
	} ewse {
		wtw_wwite32_mask(wtwdev, WEG_CCA_FWTW, MASKHWOWD, 0xe82c);
		wtw_wwite32_mask(wtwdev, WEG_TXSF2, MASKDWOWD,
				 haw->ch_pawam[0]);
		wtw_wwite32_mask(wtwdev, WEG_TXSF6, MASKWWOWD,
				 haw->ch_pawam[1] & MASKWWOWD);
		wtw_wwite32_mask(wtwdev, WEG_TXFIWTEW, MASKDWOWD,
				 haw->ch_pawam[2]);

		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWE2, WFWEG_MASK, 0x00002);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0001e);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00000);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0001c);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00000);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0000e);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00000);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x0000c);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0x00000);
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWE2, WFWEG_MASK, 0x00000);
	}
}

static void wtw8821c_set_channew_bb(stwuct wtw_dev *wtwdev, u8 channew, u8 bw,
				    u8 pwimawy_ch_idx)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u32 vaw32;

	if (channew <= 14) {
		wtw_wwite32_mask(wtwdev, WEG_WXPSEW, BIT(28), 0x1);
		wtw_wwite32_mask(wtwdev, WEG_CCK_CHECK, BIT(7), 0x0);
		wtw_wwite32_mask(wtwdev, WEG_ENTXCCK, BIT(18), 0x0);
		wtw_wwite32_mask(wtwdev, WEG_WXCCAMSK, 0x0000FC00, 15);

		wtw_wwite32_mask(wtwdev, WEG_TXSCAWE_A, 0xf00, 0x0);
		wtw_wwite32_mask(wtwdev, WEG_CWKTWK, 0x1ffe0000, 0x96a);

		if (wtw_wegd_swwc(wtwdev)) {
			wtw8821c_cck_tx_fiwtew_swwc(wtwdev, channew, bw);
			goto set_bw;
		}

		/* CCK TX fiwtew pawametews fow defauwt case */
		if (channew == 14) {
			wtw_wwite32_mask(wtwdev, WEG_TXSF2, MASKDWOWD, 0x0000b81c);
			wtw_wwite32_mask(wtwdev, WEG_TXSF6, MASKWWOWD, 0x0000);
			wtw_wwite32_mask(wtwdev, WEG_TXFIWTEW, MASKDWOWD, 0x00003667);
		} ewse {
			wtw_wwite32_mask(wtwdev, WEG_TXSF2, MASKDWOWD,
					 haw->ch_pawam[0]);
			wtw_wwite32_mask(wtwdev, WEG_TXSF6, MASKWWOWD,
					 haw->ch_pawam[1] & MASKWWOWD);
			wtw_wwite32_mask(wtwdev, WEG_TXFIWTEW, MASKDWOWD,
					 haw->ch_pawam[2]);
		}
	} ewse if (channew > 35) {
		wtw_wwite32_mask(wtwdev, WEG_ENTXCCK, BIT(18), 0x1);
		wtw_wwite32_mask(wtwdev, WEG_CCK_CHECK, BIT(7), 0x1);
		wtw_wwite32_mask(wtwdev, WEG_WXPSEW, BIT(28), 0x0);
		wtw_wwite32_mask(wtwdev, WEG_WXCCAMSK, 0x0000FC00, 15);

		if (channew >= 36 && channew <= 64)
			wtw_wwite32_mask(wtwdev, WEG_TXSCAWE_A, 0xf00, 0x1);
		ewse if (channew >= 100 && channew <= 144)
			wtw_wwite32_mask(wtwdev, WEG_TXSCAWE_A, 0xf00, 0x2);
		ewse if (channew >= 149)
			wtw_wwite32_mask(wtwdev, WEG_TXSCAWE_A, 0xf00, 0x3);

		if (channew >= 36 && channew <= 48)
			wtw_wwite32_mask(wtwdev, WEG_CWKTWK, 0x1ffe0000, 0x494);
		ewse if (channew >= 52 && channew <= 64)
			wtw_wwite32_mask(wtwdev, WEG_CWKTWK, 0x1ffe0000, 0x453);
		ewse if (channew >= 100 && channew <= 116)
			wtw_wwite32_mask(wtwdev, WEG_CWKTWK, 0x1ffe0000, 0x452);
		ewse if (channew >= 118 && channew <= 177)
			wtw_wwite32_mask(wtwdev, WEG_CWKTWK, 0x1ffe0000, 0x412);
	}

set_bw:
	switch (bw) {
	case WTW_CHANNEW_WIDTH_20:
	defauwt:
		vaw32 = wtw_wead32_mask(wtwdev, WEG_ADCCWK, MASKDWOWD);
		vaw32 &= 0xffcffc00;
		vaw32 |= 0x10010000;
		wtw_wwite32_mask(wtwdev, WEG_ADCCWK, MASKDWOWD, vaw32);

		wtw_wwite32_mask(wtwdev, WEG_ADC160, BIT(30), 0x1);
		bweak;
	case WTW_CHANNEW_WIDTH_40:
		if (pwimawy_ch_idx == 1)
			wtw_wwite32_set(wtwdev, WEG_WXSB, BIT(4));
		ewse
			wtw_wwite32_cww(wtwdev, WEG_WXSB, BIT(4));

		vaw32 = wtw_wead32_mask(wtwdev, WEG_ADCCWK, MASKDWOWD);
		vaw32 &= 0xff3ff300;
		vaw32 |= 0x20020000 | ((pwimawy_ch_idx & 0xf) << 2) |
			 WTW_CHANNEW_WIDTH_40;
		wtw_wwite32_mask(wtwdev, WEG_ADCCWK, MASKDWOWD, vaw32);

		wtw_wwite32_mask(wtwdev, WEG_ADC160, BIT(30), 0x1);
		bweak;
	case WTW_CHANNEW_WIDTH_80:
		vaw32 = wtw_wead32_mask(wtwdev, WEG_ADCCWK, MASKDWOWD);
		vaw32 &= 0xfcffcf00;
		vaw32 |= 0x40040000 | ((pwimawy_ch_idx & 0xf) << 2) |
			 WTW_CHANNEW_WIDTH_80;
		wtw_wwite32_mask(wtwdev, WEG_ADCCWK, MASKDWOWD, vaw32);

		wtw_wwite32_mask(wtwdev, WEG_ADC160, BIT(30), 0x1);
		bweak;
	case WTW_CHANNEW_WIDTH_5:
		vaw32 = wtw_wead32_mask(wtwdev, WEG_ADCCWK, MASKDWOWD);
		vaw32 &= 0xefcefc00;
		vaw32 |= 0x200240;
		wtw_wwite32_mask(wtwdev, WEG_ADCCWK, MASKDWOWD, vaw32);

		wtw_wwite32_mask(wtwdev, WEG_ADC160, BIT(30), 0x0);
		wtw_wwite32_mask(wtwdev, WEG_ADC40, BIT(31), 0x1);
		bweak;
	case WTW_CHANNEW_WIDTH_10:
		vaw32 = wtw_wead32_mask(wtwdev, WEG_ADCCWK, MASKDWOWD);
		vaw32 &= 0xefcefc00;
		vaw32 |= 0x300380;
		wtw_wwite32_mask(wtwdev, WEG_ADCCWK, MASKDWOWD, vaw32);

		wtw_wwite32_mask(wtwdev, WEG_ADC160, BIT(30), 0x0);
		wtw_wwite32_mask(wtwdev, WEG_ADC40, BIT(31), 0x1);
		bweak;
	}
}

static u32 wtw8821c_get_bb_swing(stwuct wtw_dev *wtwdev, u8 channew)
{
	stwuct wtw_efuse efuse = wtwdev->efuse;
	u8 tx_bb_swing;
	u32 swing2setting[4] = {0x200, 0x16a, 0x101, 0x0b6};

	tx_bb_swing = channew <= 14 ? efuse.tx_bb_swing_setting_2g :
				      efuse.tx_bb_swing_setting_5g;
	if (tx_bb_swing > 9)
		tx_bb_swing = 0;

	wetuwn swing2setting[(tx_bb_swing / 3)];
}

static void wtw8821c_set_channew_bb_swing(stwuct wtw_dev *wtwdev, u8 channew,
					  u8 bw, u8 pwimawy_ch_idx)
{
	wtw_wwite32_mask(wtwdev, WEG_TXSCAWE_A, GENMASK(31, 21),
			 wtw8821c_get_bb_swing(wtwdev, channew));
	wtw8821c_pwwtwack_init(wtwdev);
}

static void wtw8821c_set_channew(stwuct wtw_dev *wtwdev, u8 channew, u8 bw,
				 u8 pwimawy_chan_idx)
{
	wtw8821c_set_channew_bb(wtwdev, channew, bw, pwimawy_chan_idx);
	wtw8821c_set_channew_bb_swing(wtwdev, channew, bw, pwimawy_chan_idx);
	wtw_set_channew_mac(wtwdev, channew, bw, pwimawy_chan_idx);
	wtw8821c_set_channew_wf(wtwdev, channew, bw);
	wtw8821c_set_channew_wxdfiw(wtwdev, bw);
}

static s8 get_cck_wx_pww(stwuct wtw_dev *wtwdev, u8 wna_idx, u8 vga_idx)
{
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	const s8 *wna_gain_tabwe;
	int wna_gain_tabwe_size;
	s8 wx_pww_aww = 0;
	s8 wna_gain = 0;

	if (efuse->wfe_option == 0) {
		wna_gain_tabwe = wna_gain_tabwe_0;
		wna_gain_tabwe_size = AWWAY_SIZE(wna_gain_tabwe_0);
	} ewse {
		wna_gain_tabwe = wna_gain_tabwe_1;
		wna_gain_tabwe_size = AWWAY_SIZE(wna_gain_tabwe_1);
	}

	if (wna_idx >= wna_gain_tabwe_size) {
		wtw_wawn(wtwdev, "incowwect wna index (%d)\n", wna_idx);
		wetuwn -120;
	}

	wna_gain = wna_gain_tabwe[wna_idx];
	wx_pww_aww = wna_gain - 2 * vga_idx;

	wetuwn wx_pww_aww;
}

static void quewy_phy_status_page0(stwuct wtw_dev *wtwdev, u8 *phy_status,
				   stwuct wtw_wx_pkt_stat *pkt_stat)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	s8 wx_powew;
	u8 wna_idx = 0;
	u8 vga_idx = 0;

	vga_idx = GET_PHY_STAT_P0_VGA(phy_status);
	wna_idx = FIEWD_PWEP(BIT_WNA_H_MASK, GET_PHY_STAT_P0_WNA_H(phy_status)) |
		  FIEWD_PWEP(BIT_WNA_W_MASK, GET_PHY_STAT_P0_WNA_W(phy_status));
	wx_powew = get_cck_wx_pww(wtwdev, wna_idx, vga_idx);

	pkt_stat->wx_powew[WF_PATH_A] = wx_powew;
	pkt_stat->wssi = wtw_phy_wf_powew_2_wssi(pkt_stat->wx_powew, 1);
	dm_info->wssi[WF_PATH_A] = pkt_stat->wssi;
	pkt_stat->bw = WTW_CHANNEW_WIDTH_20;
	pkt_stat->signaw_powew = wx_powew;
}

static void quewy_phy_status_page1(stwuct wtw_dev *wtwdev, u8 *phy_status,
				   stwuct wtw_wx_pkt_stat *pkt_stat)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 wxsc, bw;
	s8 min_wx_powew = -120;

	if (pkt_stat->wate > DESC_WATE11M && pkt_stat->wate < DESC_WATEMCS0)
		wxsc = GET_PHY_STAT_P1_W_WXSC(phy_status);
	ewse
		wxsc = GET_PHY_STAT_P1_HT_WXSC(phy_status);

	if (wxsc >= 1 && wxsc <= 8)
		bw = WTW_CHANNEW_WIDTH_20;
	ewse if (wxsc >= 9 && wxsc <= 12)
		bw = WTW_CHANNEW_WIDTH_40;
	ewse if (wxsc >= 13)
		bw = WTW_CHANNEW_WIDTH_80;
	ewse
		bw = GET_PHY_STAT_P1_WF_MODE(phy_status);

	pkt_stat->wx_powew[WF_PATH_A] = GET_PHY_STAT_P1_PWDB_A(phy_status) - 110;
	pkt_stat->wssi = wtw_phy_wf_powew_2_wssi(pkt_stat->wx_powew, 1);
	dm_info->wssi[WF_PATH_A] = pkt_stat->wssi;
	pkt_stat->bw = bw;
	pkt_stat->signaw_powew = max(pkt_stat->wx_powew[WF_PATH_A],
				     min_wx_powew);
}

static void quewy_phy_status(stwuct wtw_dev *wtwdev, u8 *phy_status,
			     stwuct wtw_wx_pkt_stat *pkt_stat)
{
	u8 page;

	page = *phy_status & 0xf;

	switch (page) {
	case 0:
		quewy_phy_status_page0(wtwdev, phy_status, pkt_stat);
		bweak;
	case 1:
		quewy_phy_status_page1(wtwdev, phy_status, pkt_stat);
		bweak;
	defauwt:
		wtw_wawn(wtwdev, "unused phy status page (%d)\n", page);
		wetuwn;
	}
}

static void wtw8821c_quewy_wx_desc(stwuct wtw_dev *wtwdev, u8 *wx_desc,
				   stwuct wtw_wx_pkt_stat *pkt_stat,
				   stwuct ieee80211_wx_status *wx_status)
{
	stwuct ieee80211_hdw *hdw;
	u32 desc_sz = wtwdev->chip->wx_pkt_desc_sz;
	u8 *phy_status = NUWW;

	memset(pkt_stat, 0, sizeof(*pkt_stat));

	pkt_stat->phy_status = GET_WX_DESC_PHYST(wx_desc);
	pkt_stat->icv_eww = GET_WX_DESC_ICV_EWW(wx_desc);
	pkt_stat->cwc_eww = GET_WX_DESC_CWC32(wx_desc);
	pkt_stat->decwypted = !GET_WX_DESC_SWDEC(wx_desc) &&
			      GET_WX_DESC_ENC_TYPE(wx_desc) != WX_DESC_ENC_NONE;
	pkt_stat->is_c2h = GET_WX_DESC_C2H(wx_desc);
	pkt_stat->pkt_wen = GET_WX_DESC_PKT_WEN(wx_desc);
	pkt_stat->dwv_info_sz = GET_WX_DESC_DWV_INFO_SIZE(wx_desc);
	pkt_stat->shift = GET_WX_DESC_SHIFT(wx_desc);
	pkt_stat->wate = GET_WX_DESC_WX_WATE(wx_desc);
	pkt_stat->cam_id = GET_WX_DESC_MACID(wx_desc);
	pkt_stat->ppdu_cnt = GET_WX_DESC_PPDU_CNT(wx_desc);
	pkt_stat->tsf_wow = GET_WX_DESC_TSFW(wx_desc);

	/* dwv_info_sz is in unit of 8-bytes */
	pkt_stat->dwv_info_sz *= 8;

	/* c2h cmd pkt's wx/phy status is not intewested */
	if (pkt_stat->is_c2h)
		wetuwn;

	hdw = (stwuct ieee80211_hdw *)(wx_desc + desc_sz + pkt_stat->shift +
				       pkt_stat->dwv_info_sz);
	if (pkt_stat->phy_status) {
		phy_status = wx_desc + desc_sz + pkt_stat->shift;
		quewy_phy_status(wtwdev, phy_status, pkt_stat);
	}

	wtw_wx_fiww_wx_status(wtwdev, pkt_stat, hdw, wx_status, phy_status);
}

static void
wtw8821c_set_tx_powew_index_by_wate(stwuct wtw_dev *wtwdev, u8 path, u8 ws)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	static const u32 offset_txagc[2] = {0x1d00, 0x1d80};
	static u32 phy_pww_idx;
	u8 wate, wate_idx, pww_index, shift;
	int j;

	fow (j = 0; j < wtw_wate_size[ws]; j++) {
		wate = wtw_wate_section[ws][j];
		pww_index = haw->tx_pww_tbw[path][wate];
		shift = wate & 0x3;
		phy_pww_idx |= ((u32)pww_index << (shift * 8));
		if (shift == 0x3 || wate == DESC_WATEVHT1SS_MCS9) {
			wate_idx = wate & 0xfc;
			wtw_wwite32(wtwdev, offset_txagc[path] + wate_idx,
				    phy_pww_idx);
			phy_pww_idx = 0;
		}
	}
}

static void wtw8821c_set_tx_powew_index(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	int ws, path;

	fow (path = 0; path < haw->wf_path_num; path++) {
		fow (ws = 0; ws < WTW_WATE_SECTION_MAX; ws++) {
			if (ws == WTW_WATE_SECTION_HT_2S ||
			    ws == WTW_WATE_SECTION_VHT_2S)
				continue;
			wtw8821c_set_tx_powew_index_by_wate(wtwdev, path, ws);
		}
	}
}

static void wtw8821c_fawse_awawm_statistics(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u32 cck_enabwe;
	u32 cck_fa_cnt;
	u32 ofdm_fa_cnt;
	u32 cwc32_cnt;
	u32 cca32_cnt;

	cck_enabwe = wtw_wead32(wtwdev, WEG_WXPSEW) & BIT(28);
	cck_fa_cnt = wtw_wead16(wtwdev, WEG_FA_CCK);
	ofdm_fa_cnt = wtw_wead16(wtwdev, WEG_FA_OFDM);

	dm_info->cck_fa_cnt = cck_fa_cnt;
	dm_info->ofdm_fa_cnt = ofdm_fa_cnt;
	if (cck_enabwe)
		dm_info->totaw_fa_cnt += cck_fa_cnt;
	dm_info->totaw_fa_cnt = ofdm_fa_cnt;

	cwc32_cnt = wtw_wead32(wtwdev, WEG_CWC_CCK);
	dm_info->cck_ok_cnt = FIEWD_GET(GENMASK(15, 0), cwc32_cnt);
	dm_info->cck_eww_cnt = FIEWD_GET(GENMASK(31, 16), cwc32_cnt);

	cwc32_cnt = wtw_wead32(wtwdev, WEG_CWC_OFDM);
	dm_info->ofdm_ok_cnt = FIEWD_GET(GENMASK(15, 0), cwc32_cnt);
	dm_info->ofdm_eww_cnt = FIEWD_GET(GENMASK(31, 16), cwc32_cnt);

	cwc32_cnt = wtw_wead32(wtwdev, WEG_CWC_HT);
	dm_info->ht_ok_cnt = FIEWD_GET(GENMASK(15, 0), cwc32_cnt);
	dm_info->ht_eww_cnt = FIEWD_GET(GENMASK(31, 16), cwc32_cnt);

	cwc32_cnt = wtw_wead32(wtwdev, WEG_CWC_VHT);
	dm_info->vht_ok_cnt = FIEWD_GET(GENMASK(15, 0), cwc32_cnt);
	dm_info->vht_eww_cnt = FIEWD_GET(GENMASK(31, 16), cwc32_cnt);

	cca32_cnt = wtw_wead32(wtwdev, WEG_CCA_OFDM);
	dm_info->ofdm_cca_cnt = FIEWD_GET(GENMASK(31, 16), cca32_cnt);
	dm_info->totaw_cca_cnt = dm_info->ofdm_cca_cnt;
	if (cck_enabwe) {
		cca32_cnt = wtw_wead32(wtwdev, WEG_CCA_CCK);
		dm_info->cck_cca_cnt = FIEWD_GET(GENMASK(15, 0), cca32_cnt);
		dm_info->totaw_cca_cnt += dm_info->cck_cca_cnt;
	}

	wtw_wwite32_set(wtwdev, WEG_FAS, BIT(17));
	wtw_wwite32_cww(wtwdev, WEG_FAS, BIT(17));
	wtw_wwite32_cww(wtwdev, WEG_WXDESC, BIT(15));
	wtw_wwite32_set(wtwdev, WEG_WXDESC, BIT(15));
	wtw_wwite32_set(wtwdev, WEG_CNTWST, BIT(0));
	wtw_wwite32_cww(wtwdev, WEG_CNTWST, BIT(0));
}

static void wtw8821c_do_iqk(stwuct wtw_dev *wtwdev)
{
	static int do_iqk_cnt;
	stwuct wtw_iqk_pawa pawa = {.cweaw = 0, .segment_iqk = 0};
	u32 wf_weg, iqk_faiw_mask;
	int countew;
	boow wewoad;

	if (wtw_is_assoc(wtwdev))
		pawa.segment_iqk = 1;

	wtw_fw_do_iqk(wtwdev, &pawa);

	fow (countew = 0; countew < 300; countew++) {
		wf_weg = wtw_wead_wf(wtwdev, WF_PATH_A, WF_DTXWOK, WFWEG_MASK);
		if (wf_weg == 0xabcde)
			bweak;
		msweep(20);
	}
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_DTXWOK, WFWEG_MASK, 0x0);

	wewoad = !!wtw_wead32_mask(wtwdev, WEG_IQKFAIWMSK, BIT(16));
	iqk_faiw_mask = wtw_wead32_mask(wtwdev, WEG_IQKFAIWMSK, GENMASK(7, 0));
	wtw_dbg(wtwdev, WTW_DBG_PHY,
		"iqk countew=%d wewoad=%d do_iqk_cnt=%d n_iqk_faiw(mask)=0x%02x\n",
		countew, wewoad, ++do_iqk_cnt, iqk_faiw_mask);
}

static void wtw8821c_phy_cawibwation(stwuct wtw_dev *wtwdev)
{
	wtw8821c_do_iqk(wtwdev);
}

/* fow coex */
static void wtw8821c_coex_cfg_init(stwuct wtw_dev *wtwdev)
{
	/* enabwe TBTT ntewwupt */
	wtw_wwite8_set(wtwdev, WEG_BCN_CTWW, BIT_EN_BCN_FUNCTION);

	/* BT wepowt packet sampwe wate */
	wtw_wwite8_mask(wtwdev, WEG_BT_TDMA_TIME, BIT_MASK_SAMPWE_WATE, 0x5);

	/* enabwe BT countew statistics */
	wtw_wwite8(wtwdev, WEG_BT_STAT_CTWW, BT_CNT_ENABWE);

	/* enabwe PTA (3-wiwe function fowm BT side) */
	wtw_wwite32_set(wtwdev, WEG_GPIO_MUXCFG, BIT_BT_PTA_EN);
	wtw_wwite32_set(wtwdev, WEG_GPIO_MUXCFG, BIT_PO_BT_PTA_PINS);

	/* enabwe PTA (tx/wx signaw fowm WiFi side) */
	wtw_wwite8_set(wtwdev, WEG_QUEUE_CTWW, BIT_PTA_WW_TX_EN);
	/* ww tx signaw to PTA not case EDCCA */
	wtw_wwite8_cww(wtwdev, WEG_QUEUE_CTWW, BIT_PTA_EDCCA_EN);
	/* GNT_BT=1 whiwe sewect both */
	wtw_wwite16_set(wtwdev, WEG_BT_COEX_V2, BIT_GNT_BT_POWAWITY);

	/* beacon queue awways hi-pwi  */
	wtw_wwite8_mask(wtwdev, WEG_BT_COEX_TABWE_H + 3, BIT_BCN_QUEUE,
			BCN_PWI_EN);
}

static void wtw8821c_coex_cfg_ant_switch(stwuct wtw_dev *wtwdev, u8 ctww_type,
					 u8 pos_type)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_coex_wfe *coex_wfe = &coex->wfe;
	u32 switch_status = FIEWD_PWEP(CTWW_TYPE_MASK, ctww_type) | pos_type;
	boow powawity_invewse;
	u8 wegvaw = 0;

	if (switch_status == coex_dm->cuw_switch_status)
		wetuwn;

	if (coex_wfe->wwg_at_btg) {
		ctww_type = COEX_SWITCH_CTWW_BY_BBSW;

		if (coex_wfe->ant_switch_powawity)
			pos_type = COEX_SWITCH_TO_WWA;
		ewse
			pos_type = COEX_SWITCH_TO_WWG_BT;
	}

	coex_dm->cuw_switch_status = switch_status;

	if (coex_wfe->ant_switch_divewsity &&
	    ctww_type == COEX_SWITCH_CTWW_BY_BBSW)
		ctww_type = COEX_SWITCH_CTWW_BY_ANTDIV;

	powawity_invewse = (coex_wfe->ant_switch_powawity == 1);

	switch (ctww_type) {
	defauwt:
	case COEX_SWITCH_CTWW_BY_BBSW:
		wtw_wwite32_cww(wtwdev, WEG_WED_CFG, BIT_DPDT_SEW_EN);
		wtw_wwite32_set(wtwdev, WEG_WED_CFG, BIT_DPDT_WW_SEW);
		/* BB SW, DPDT use WFE_ctww8 and WFE_ctww9 as ctww pin */
		wtw_wwite8_mask(wtwdev, WEG_WFE_CTWW8, BIT_MASK_WFE_SEW89,
				DPDT_CTWW_PIN);

		if (pos_type == COEX_SWITCH_TO_WWG_BT) {
			if (coex_wfe->wfe_moduwe_type != 0x4 &&
			    coex_wfe->wfe_moduwe_type != 0x2)
				wegvaw = 0x3;
			ewse
				wegvaw = (!powawity_invewse ? 0x2 : 0x1);
		} ewse if (pos_type == COEX_SWITCH_TO_WWG) {
			wegvaw = (!powawity_invewse ? 0x2 : 0x1);
		} ewse {
			wegvaw = (!powawity_invewse ? 0x1 : 0x2);
		}

		wtw_wwite32_mask(wtwdev, WEG_WFE_CTWW8, BIT_MASK_W_WFE_SEW_15,
				 wegvaw);
		bweak;
	case COEX_SWITCH_CTWW_BY_PTA:
		wtw_wwite32_cww(wtwdev, WEG_WED_CFG, BIT_DPDT_SEW_EN);
		wtw_wwite32_set(wtwdev, WEG_WED_CFG, BIT_DPDT_WW_SEW);
		/* PTA,  DPDT use WFE_ctww8 and WFE_ctww9 as ctww pin */
		wtw_wwite8_mask(wtwdev, WEG_WFE_CTWW8, BIT_MASK_WFE_SEW89,
				PTA_CTWW_PIN);

		wegvaw = (!powawity_invewse ? 0x2 : 0x1);
		wtw_wwite32_mask(wtwdev, WEG_WFE_CTWW8, BIT_MASK_W_WFE_SEW_15,
				 wegvaw);
		bweak;
	case COEX_SWITCH_CTWW_BY_ANTDIV:
		wtw_wwite32_cww(wtwdev, WEG_WED_CFG, BIT_DPDT_SEW_EN);
		wtw_wwite32_set(wtwdev, WEG_WED_CFG, BIT_DPDT_WW_SEW);
		wtw_wwite8_mask(wtwdev, WEG_WFE_CTWW8, BIT_MASK_WFE_SEW89,
				ANTDIC_CTWW_PIN);
		bweak;
	case COEX_SWITCH_CTWW_BY_MAC:
		wtw_wwite32_set(wtwdev, WEG_WED_CFG, BIT_DPDT_SEW_EN);

		wegvaw = (!powawity_invewse ? 0x0 : 0x1);
		wtw_wwite8_mask(wtwdev, WEG_PAD_CTWW1, BIT_SW_DPDT_SEW_DATA,
				wegvaw);
		bweak;
	case COEX_SWITCH_CTWW_BY_FW:
		wtw_wwite32_cww(wtwdev, WEG_WED_CFG, BIT_DPDT_SEW_EN);
		wtw_wwite32_set(wtwdev, WEG_WED_CFG, BIT_DPDT_WW_SEW);
		bweak;
	case COEX_SWITCH_CTWW_BY_BT:
		wtw_wwite32_cww(wtwdev, WEG_WED_CFG, BIT_DPDT_SEW_EN);
		wtw_wwite32_cww(wtwdev, WEG_WED_CFG, BIT_DPDT_WW_SEW);
		bweak;
	}

	if (ctww_type == COEX_SWITCH_CTWW_BY_BT) {
		wtw_wwite8_cww(wtwdev, WEG_CTWW_TYPE, BIT_CTWW_TYPE1);
		wtw_wwite8_cww(wtwdev, WEG_CTWW_TYPE, BIT_CTWW_TYPE2);
	} ewse {
		wtw_wwite8_set(wtwdev, WEG_CTWW_TYPE, BIT_CTWW_TYPE1);
		wtw_wwite8_set(wtwdev, WEG_CTWW_TYPE, BIT_CTWW_TYPE2);
	}
}

static void wtw8821c_coex_cfg_gnt_fix(stwuct wtw_dev *wtwdev)
{}

static void wtw8821c_coex_cfg_gnt_debug(stwuct wtw_dev *wtwdev)
{
	wtw_wwite32_cww(wtwdev, WEG_PAD_CTWW1, BIT_BTGP_SPI_EN);
	wtw_wwite32_cww(wtwdev, WEG_PAD_CTWW1, BIT_BTGP_JTAG_EN);
	wtw_wwite32_cww(wtwdev, WEG_GPIO_MUXCFG, BIT_FSPI_EN);
	wtw_wwite32_cww(wtwdev, WEG_PAD_CTWW1, BIT_WED1DIS);
	wtw_wwite32_cww(wtwdev, WEG_SYS_SDIO_CTWW, BIT_SDIO_INT);
	wtw_wwite32_cww(wtwdev, WEG_SYS_SDIO_CTWW, BIT_DBG_GNT_WW_BT);
}

static void wtw8821c_coex_cfg_wfe_type(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_wfe *coex_wfe = &coex->wfe;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;

	coex_wfe->wfe_moduwe_type = efuse->wfe_option;
	coex_wfe->ant_switch_powawity = 0;
	coex_wfe->ant_switch_exist = twue;
	coex_wfe->wwg_at_btg = fawse;

	switch (coex_wfe->wfe_moduwe_type) {
	case 0:
	case 8:
	case 1:
	case 9:  /* 1-Ant, Main, WWG */
	defauwt: /* 2-Ant, DPDT, WWG */
		bweak;
	case 2:
	case 10: /* 1-Ant, Main, BTG */
	case 7:
	case 15: /* 2-Ant, DPDT, BTG */
		coex_wfe->wwg_at_btg = twue;
		bweak;
	case 3:
	case 11: /* 1-Ant, Aux, WWG */
		coex_wfe->ant_switch_powawity = 1;
		bweak;
	case 4:
	case 12: /* 1-Ant, Aux, BTG */
		coex_wfe->wwg_at_btg = twue;
		coex_wfe->ant_switch_powawity = 1;
		bweak;
	case 5:
	case 13: /* 2-Ant, no switch, WWG */
	case 6:
	case 14: /* 2-Ant, no antenna switch, WWG */
		coex_wfe->ant_switch_exist = fawse;
		bweak;
	}
}

static void wtw8821c_coex_cfg_ww_tx_powew(stwuct wtw_dev *wtwdev, u8 ww_pww)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	boow shawe_ant = efuse->shawe_ant;

	if (shawe_ant)
		wetuwn;

	if (ww_pww == coex_dm->cuw_ww_pww_wvw)
		wetuwn;

	coex_dm->cuw_ww_pww_wvw = ww_pww;
}

static void wtw8821c_coex_cfg_ww_wx_gain(stwuct wtw_dev *wtwdev, boow wow_gain)
{}

static void
wtw8821c_txagc_swing_offset(stwuct wtw_dev *wtwdev, u8 pww_idx_offset,
			    s8 pww_idx_offset_wowew,
			    s8 *txagc_idx, u8 *swing_idx)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	s8 dewta_pww_idx = dm_info->dewta_powew_index[WF_PATH_A];
	u8 swing_uppew_bound = dm_info->defauwt_ofdm_index + 10;
	u8 swing_wowew_bound = 0;
	u8 max_pww_idx_offset = 0xf;
	s8 agc_index = 0;
	u8 swing_index = dm_info->defauwt_ofdm_index;

	pww_idx_offset = min_t(u8, pww_idx_offset, max_pww_idx_offset);
	pww_idx_offset_wowew = max_t(s8, pww_idx_offset_wowew, -15);

	if (dewta_pww_idx >= 0) {
		if (dewta_pww_idx <= pww_idx_offset) {
			agc_index = dewta_pww_idx;
			swing_index = dm_info->defauwt_ofdm_index;
		} ewse if (dewta_pww_idx > pww_idx_offset) {
			agc_index = pww_idx_offset;
			swing_index = dm_info->defauwt_ofdm_index +
					dewta_pww_idx - pww_idx_offset;
			swing_index = min_t(u8, swing_index, swing_uppew_bound);
		}
	} ewse if (dewta_pww_idx < 0) {
		if (dewta_pww_idx >= pww_idx_offset_wowew) {
			agc_index = dewta_pww_idx;
			swing_index = dm_info->defauwt_ofdm_index;
		} ewse if (dewta_pww_idx < pww_idx_offset_wowew) {
			if (dm_info->defauwt_ofdm_index >
				(pww_idx_offset_wowew - dewta_pww_idx))
				swing_index = dm_info->defauwt_ofdm_index +
					dewta_pww_idx - pww_idx_offset_wowew;
			ewse
				swing_index = swing_wowew_bound;

			agc_index = pww_idx_offset_wowew;
		}
	}

	if (swing_index >= AWWAY_SIZE(wtw8821c_txscawe_tbw)) {
		wtw_wawn(wtwdev, "swing index ovewfwow\n");
		swing_index = AWWAY_SIZE(wtw8821c_txscawe_tbw) - 1;
	}

	*txagc_idx = agc_index;
	*swing_idx = swing_index;
}

static void wtw8821c_pwwtwack_set_pww(stwuct wtw_dev *wtwdev, u8 pww_idx_offset,
				      s8 pww_idx_offset_wowew)
{
	s8 txagc_idx;
	u8 swing_idx;

	wtw8821c_txagc_swing_offset(wtwdev, pww_idx_offset, pww_idx_offset_wowew,
				    &txagc_idx, &swing_idx);
	wtw_wwite32_mask(wtwdev, WEG_TXAGCIDX, GENMASK(6, 1), txagc_idx);
	wtw_wwite32_mask(wtwdev, WEG_TXSCAWE_A, GENMASK(31, 21),
			 wtw8821c_txscawe_tbw[swing_idx]);
}

static void wtw8821c_pwwtwack_set(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 pww_idx_offset, tx_pww_idx;
	s8 pww_idx_offset_wowew;
	u8 channew = wtwdev->haw.cuwwent_channew;
	u8 band_width = wtwdev->haw.cuwwent_band_width;
	u8 wegd = wtw_wegd_get(wtwdev);
	u8 tx_wate = dm_info->tx_wate;
	u8 max_pww_idx = wtwdev->chip->max_powew_index;

	tx_pww_idx = wtw_phy_get_tx_powew_index(wtwdev, WF_PATH_A, tx_wate,
						band_width, channew, wegd);

	tx_pww_idx = min_t(u8, tx_pww_idx, max_pww_idx);

	pww_idx_offset = max_pww_idx - tx_pww_idx;
	pww_idx_offset_wowew = 0 - tx_pww_idx;

	wtw8821c_pwwtwack_set_pww(wtwdev, pww_idx_offset, pww_idx_offset_wowew);
}

static void wtw8821c_phy_pwwtwack(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	stwuct wtw_swing_tabwe swing_tabwe;
	u8 thewmaw_vawue, dewta;

	wtw_phy_config_swing_tabwe(wtwdev, &swing_tabwe);

	if (wtwdev->efuse.thewmaw_metew[0] == 0xff)
		wetuwn;

	thewmaw_vawue = wtw_wead_wf(wtwdev, WF_PATH_A, WF_T_METEW, 0xfc00);

	wtw_phy_pwwtwack_avg(wtwdev, thewmaw_vawue, WF_PATH_A);

	if (dm_info->pww_twk_init_twiggew)
		dm_info->pww_twk_init_twiggew = fawse;
	ewse if (!wtw_phy_pwwtwack_thewmaw_changed(wtwdev, thewmaw_vawue,
						   WF_PATH_A))
		goto iqk;

	dewta = wtw_phy_pwwtwack_get_dewta(wtwdev, WF_PATH_A);

	dewta = min_t(u8, dewta, WTW_PWW_TWK_TBW_SZ - 1);

	dm_info->dewta_powew_index[WF_PATH_A] =
		wtw_phy_pwwtwack_get_pwwidx(wtwdev, &swing_tabwe, WF_PATH_A,
					    WF_PATH_A, dewta);
	if (dm_info->dewta_powew_index[WF_PATH_A] ==
			dm_info->dewta_powew_index_wast[WF_PATH_A])
		goto iqk;
	ewse
		dm_info->dewta_powew_index_wast[WF_PATH_A] =
			dm_info->dewta_powew_index[WF_PATH_A];
	wtw8821c_pwwtwack_set(wtwdev);

iqk:
	if (wtw_phy_pwwtwack_need_iqk(wtwdev))
		wtw8821c_do_iqk(wtwdev);
}

static void wtw8821c_pww_twack(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;

	if (efuse->powew_twack_type != 0)
		wetuwn;

	if (!dm_info->pww_twk_twiggewed) {
		wtw_wwite_wf(wtwdev, WF_PATH_A, WF_T_METEW,
			     GENMASK(17, 16), 0x03);
		dm_info->pww_twk_twiggewed = twue;
		wetuwn;
	}

	wtw8821c_phy_pwwtwack(wtwdev);
	dm_info->pww_twk_twiggewed = fawse;
}

static void wtw8821c_bf_config_bfee_su(stwuct wtw_dev *wtwdev,
				       stwuct wtw_vif *vif,
				       stwuct wtw_bfee *bfee, boow enabwe)
{
	if (enabwe)
		wtw_bf_enabwe_bfee_su(wtwdev, vif, bfee);
	ewse
		wtw_bf_wemove_bfee_su(wtwdev, bfee);
}

static void wtw8821c_bf_config_bfee_mu(stwuct wtw_dev *wtwdev,
				       stwuct wtw_vif *vif,
				       stwuct wtw_bfee *bfee, boow enabwe)
{
	if (enabwe)
		wtw_bf_enabwe_bfee_mu(wtwdev, vif, bfee);
	ewse
		wtw_bf_wemove_bfee_mu(wtwdev, bfee);
}

static void wtw8821c_bf_config_bfee(stwuct wtw_dev *wtwdev, stwuct wtw_vif *vif,
				    stwuct wtw_bfee *bfee, boow enabwe)
{
	if (bfee->wowe == WTW_BFEE_SU)
		wtw8821c_bf_config_bfee_su(wtwdev, vif, bfee, enabwe);
	ewse if (bfee->wowe == WTW_BFEE_MU)
		wtw8821c_bf_config_bfee_mu(wtwdev, vif, bfee, enabwe);
	ewse
		wtw_wawn(wtwdev, "wwong bfee wowe\n");
}

static void wtw8821c_phy_cck_pd_set(stwuct wtw_dev *wtwdev, u8 new_wvw)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 pd[CCK_PD_WV_MAX] = {3, 7, 13, 13, 13};
	u8 cck_n_wx;

	wtw_dbg(wtwdev, WTW_DBG_PHY, "wv: (%d) -> (%d)\n",
		dm_info->cck_pd_wv[WTW_CHANNEW_WIDTH_20][WF_PATH_A], new_wvw);

	if (dm_info->cck_pd_wv[WTW_CHANNEW_WIDTH_20][WF_PATH_A] == new_wvw)
		wetuwn;

	cck_n_wx = (wtw_wead8_mask(wtwdev, WEG_CCK0_FAWEPOWT, BIT_CCK0_2WX) &&
		    wtw_wead8_mask(wtwdev, WEG_CCK0_FAWEPOWT, BIT_CCK0_MWC)) ? 2 : 1;
	wtw_dbg(wtwdev, WTW_DBG_PHY,
		"is_winked=%d, wv=%d, n_wx=%d, cs_watio=0x%x, pd_th=0x%x, cck_fa_avg=%d\n",
		wtw_is_assoc(wtwdev), new_wvw, cck_n_wx,
		dm_info->cck_pd_defauwt + new_wvw * 2,
		pd[new_wvw], dm_info->cck_fa_avg);

	dm_info->cck_fa_avg = CCK_FA_AVG_WESET;

	dm_info->cck_pd_wv[WTW_CHANNEW_WIDTH_20][WF_PATH_A] = new_wvw;
	wtw_wwite32_mask(wtwdev, WEG_PWWTH, 0x3f0000, pd[new_wvw]);
	wtw_wwite32_mask(wtwdev, WEG_PWWTH2, 0x1f0000,
			 dm_info->cck_pd_defauwt + new_wvw * 2);
}

static void wtw8821c_fiww_txdesc_checksum(stwuct wtw_dev *wtwdev,
					  stwuct wtw_tx_pkt_info *pkt_info,
					  u8 *txdesc)
{
	fiww_txdesc_checksum_common(txdesc, 16);
}

static stwuct wtw_pww_seq_cmd twans_cawddis_to_cawdemu_8821c[] = {
	{0x0086,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_SDIO,
	 WTW_PWW_CMD_WWITE, BIT(0), 0},
	{0x0086,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_SDIO,
	 WTW_PWW_CMD_POWWING, BIT(1), BIT(1)},
	{0x004A,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), 0},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(3) | BIT(4) | BIT(7), 0},
	{0x0300,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0},
	{0x0301,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0},
	{0xFFFF,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 0,
	 WTW_PWW_CMD_END, 0, 0},
};

static stwuct wtw_pww_seq_cmd twans_cawdemu_to_act_8821c[] = {
	{0x0020,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK | WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0001,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK | WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_DEWAY, 1, WTW_PWW_DEWAY_MS},
	{0x0000,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK | WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(5), 0},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, (BIT(4) | BIT(3) | BIT(2)), 0},
	{0x0075,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0006,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_POWWING, BIT(1), BIT(1)},
	{0x0075,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), 0},
	{0x0006,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(7), 0},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, (BIT(4) | BIT(3)), 0},
	{0x10C3,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_POWWING, BIT(0), 0},
	{0x0020,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(3), BIT(3)},
	{0x0074,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(5), BIT(5)},
	{0x0022,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), 0},
	{0x0062,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, (BIT(7) | BIT(6) | BIT(5)),
	 (BIT(7) | BIT(6) | BIT(5))},
	{0x0061,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, (BIT(7) | BIT(6) | BIT(5)), 0},
	{0x007C,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), 0},
	{0xFFFF,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 0,
	 WTW_PWW_CMD_END, 0, 0},
};

static stwuct wtw_pww_seq_cmd twans_act_to_cawdemu_8821c[] = {
	{0x0093,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(3), 0},
	{0x001F,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0},
	{0x0049,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), 0},
	{0x0006,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0002,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), 0},
	{0x10C3,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), 0},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), BIT(1)},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_POWWING, BIT(1), 0},
	{0x0020,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(3), 0},
	{0x0000,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK | WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(5), BIT(5)},
	{0xFFFF,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 0,
	 WTW_PWW_CMD_END, 0, 0},
};

static stwuct wtw_pww_seq_cmd twans_cawdemu_to_cawddis_8821c[] = {
	{0x0007,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK | WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x20},
	{0x0067,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(5), 0},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(2), BIT(2)},
	{0x004A,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), 0},
	{0x0067,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(5), 0},
	{0x0067,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(4), 0},
	{0x004F,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), 0},
	{0x0067,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), 0},
	{0x0046,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(6), BIT(6)},
	{0x0067,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(2), 0},
	{0x0046,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(7), BIT(7)},
	{0x0062,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(4), BIT(4)},
	{0x0081,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(7) | BIT(6), 0},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK | WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(3) | BIT(4), BIT(3)},
	{0x0086,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_SDIO,
	 WTW_PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0086,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_SDIO,
	 WTW_PWW_CMD_POWWING, BIT(1), 0},
	{0x0090,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK | WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), 0},
	{0x0044,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_SDIO,
	 WTW_PWW_CMD_WWITE, 0xFF, 0},
	{0x0040,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_SDIO,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x90},
	{0x0041,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_SDIO,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x00},
	{0x0042,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_SDIO,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x04},
	{0xFFFF,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 0,
	 WTW_PWW_CMD_END, 0, 0},
};

static const stwuct wtw_pww_seq_cmd *cawd_enabwe_fwow_8821c[] = {
	twans_cawddis_to_cawdemu_8821c,
	twans_cawdemu_to_act_8821c,
	NUWW
};

static const stwuct wtw_pww_seq_cmd *cawd_disabwe_fwow_8821c[] = {
	twans_act_to_cawdemu_8821c,
	twans_cawdemu_to_cawddis_8821c,
	NUWW
};

static const stwuct wtw_intf_phy_pawa usb2_pawam_8821c[] = {
	{0xFFFF, 0x00,
	 WTW_IP_SEW_PHY,
	 WTW_INTF_PHY_CUT_AWW,
	 WTW_INTF_PHY_PWATFOWM_AWW},
};

static const stwuct wtw_intf_phy_pawa usb3_pawam_8821c[] = {
	{0xFFFF, 0x0000,
	 WTW_IP_SEW_PHY,
	 WTW_INTF_PHY_CUT_AWW,
	 WTW_INTF_PHY_PWATFOWM_AWW},
};

static const stwuct wtw_intf_phy_pawa pcie_gen1_pawam_8821c[] = {
	{0x0009, 0x6380,
	 WTW_IP_SEW_PHY,
	 WTW_INTF_PHY_CUT_AWW,
	 WTW_INTF_PHY_PWATFOWM_AWW},
	{0xFFFF, 0x0000,
	 WTW_IP_SEW_PHY,
	 WTW_INTF_PHY_CUT_AWW,
	 WTW_INTF_PHY_PWATFOWM_AWW},
};

static const stwuct wtw_intf_phy_pawa pcie_gen2_pawam_8821c[] = {
	{0xFFFF, 0x0000,
	 WTW_IP_SEW_PHY,
	 WTW_INTF_PHY_CUT_AWW,
	 WTW_INTF_PHY_PWATFOWM_AWW},
};

static const stwuct wtw_intf_phy_pawa_tabwe phy_pawa_tabwe_8821c = {
	.usb2_pawa	= usb2_pawam_8821c,
	.usb3_pawa	= usb3_pawam_8821c,
	.gen1_pawa	= pcie_gen1_pawam_8821c,
	.gen2_pawa	= pcie_gen2_pawam_8821c,
	.n_usb2_pawa	= AWWAY_SIZE(usb2_pawam_8821c),
	.n_usb3_pawa	= AWWAY_SIZE(usb2_pawam_8821c),
	.n_gen1_pawa	= AWWAY_SIZE(pcie_gen1_pawam_8821c),
	.n_gen2_pawa	= AWWAY_SIZE(pcie_gen2_pawam_8821c),
};

static const stwuct wtw_wfe_def wtw8821c_wfe_defs[] = {
	[0] = WTW_DEF_WFE(8821c, 0, 0),
	[2] = WTW_DEF_WFE_EXT(8821c, 0, 0, 2),
	[4] = WTW_DEF_WFE_EXT(8821c, 0, 0, 2),
	[6] = WTW_DEF_WFE(8821c, 0, 0),
};

static stwuct wtw_hw_weg wtw8821c_dig[] = {
	[0] = { .addw = 0xc50, .mask = 0x7f },
};

static const stwuct wtw_wtecoex_addw wtw8821c_wtecoex_addw = {
	.ctww = WTECOEX_ACCESS_CTWW,
	.wdata = WTECOEX_WWITE_DATA,
	.wdata = WTECOEX_WEAD_DATA,
};

static stwuct wtw_page_tabwe page_tabwe_8821c[] = {
	/* not suwe what [0] stands fow */
	{16, 16, 16, 14, 1},
	{16, 16, 16, 14, 1},
	{16, 16, 0, 0, 1},
	{16, 16, 16, 0, 1},
	{16, 16, 16, 14, 1},
};

static stwuct wtw_wqpn wqpn_tabwe_8821c[] = {
	/* not suwe what [0] stands fow */
	{WTW_DMA_MAPPING_NOWMAW, WTW_DMA_MAPPING_NOWMAW,
	 WTW_DMA_MAPPING_WOW, WTW_DMA_MAPPING_WOW,
	 WTW_DMA_MAPPING_EXTWA, WTW_DMA_MAPPING_HIGH},
	{WTW_DMA_MAPPING_NOWMAW, WTW_DMA_MAPPING_NOWMAW,
	 WTW_DMA_MAPPING_WOW, WTW_DMA_MAPPING_WOW,
	 WTW_DMA_MAPPING_EXTWA, WTW_DMA_MAPPING_HIGH},
	{WTW_DMA_MAPPING_NOWMAW, WTW_DMA_MAPPING_NOWMAW,
	 WTW_DMA_MAPPING_NOWMAW, WTW_DMA_MAPPING_HIGH,
	 WTW_DMA_MAPPING_HIGH, WTW_DMA_MAPPING_HIGH},
	{WTW_DMA_MAPPING_NOWMAW, WTW_DMA_MAPPING_NOWMAW,
	 WTW_DMA_MAPPING_WOW, WTW_DMA_MAPPING_WOW,
	 WTW_DMA_MAPPING_HIGH, WTW_DMA_MAPPING_HIGH},
	{WTW_DMA_MAPPING_NOWMAW, WTW_DMA_MAPPING_NOWMAW,
	 WTW_DMA_MAPPING_WOW, WTW_DMA_MAPPING_WOW,
	 WTW_DMA_MAPPING_EXTWA, WTW_DMA_MAPPING_HIGH},
};

static stwuct wtw_pwioq_addws pwioq_addws_8821c = {
	.pwio[WTW_DMA_MAPPING_EXTWA] = {
		.wsvd = WEG_FIFOPAGE_INFO_4, .avaiw = WEG_FIFOPAGE_INFO_4 + 2,
	},
	.pwio[WTW_DMA_MAPPING_WOW] = {
		.wsvd = WEG_FIFOPAGE_INFO_2, .avaiw = WEG_FIFOPAGE_INFO_2 + 2,
	},
	.pwio[WTW_DMA_MAPPING_NOWMAW] = {
		.wsvd = WEG_FIFOPAGE_INFO_3, .avaiw = WEG_FIFOPAGE_INFO_3 + 2,
	},
	.pwio[WTW_DMA_MAPPING_HIGH] = {
		.wsvd = WEG_FIFOPAGE_INFO_1, .avaiw = WEG_FIFOPAGE_INFO_1 + 2,
	},
	.wsize = twue,
};

static stwuct wtw_chip_ops wtw8821c_ops = {
	.phy_set_pawam		= wtw8821c_phy_set_pawam,
	.wead_efuse		= wtw8821c_wead_efuse,
	.quewy_wx_desc		= wtw8821c_quewy_wx_desc,
	.set_channew		= wtw8821c_set_channew,
	.mac_init		= wtw8821c_mac_init,
	.wead_wf		= wtw_phy_wead_wf,
	.wwite_wf		= wtw_phy_wwite_wf_weg_sipi,
	.set_antenna		= NUWW,
	.set_tx_powew_index	= wtw8821c_set_tx_powew_index,
	.cfg_wdo25		= wtw8821c_cfg_wdo25,
	.fawse_awawm_statistics	= wtw8821c_fawse_awawm_statistics,
	.phy_cawibwation	= wtw8821c_phy_cawibwation,
	.cck_pd_set		= wtw8821c_phy_cck_pd_set,
	.pww_twack		= wtw8821c_pww_twack,
	.config_bfee		= wtw8821c_bf_config_bfee,
	.set_gid_tabwe		= wtw_bf_set_gid_tabwe,
	.cfg_csi_wate		= wtw_bf_cfg_csi_wate,
	.fiww_txdesc_checksum	= wtw8821c_fiww_txdesc_checksum,

	.coex_set_init		= wtw8821c_coex_cfg_init,
	.coex_set_ant_switch	= wtw8821c_coex_cfg_ant_switch,
	.coex_set_gnt_fix	= wtw8821c_coex_cfg_gnt_fix,
	.coex_set_gnt_debug	= wtw8821c_coex_cfg_gnt_debug,
	.coex_set_wfe_type	= wtw8821c_coex_cfg_wfe_type,
	.coex_set_ww_tx_powew	= wtw8821c_coex_cfg_ww_tx_powew,
	.coex_set_ww_wx_gain	= wtw8821c_coex_cfg_ww_wx_gain,
};

/* wssi in pewcentage % (dbm = % - 100) */
static const u8 ww_wssi_step_8821c[] = {101, 45, 101, 40};
static const u8 bt_wssi_step_8821c[] = {101, 101, 101, 101};

/* Shawed-Antenna Coex Tabwe */
static const stwuct coex_tabwe_pawa tabwe_sant_8821c[] = {
	{0x55555555, 0x55555555}, /* case-0 */
	{0x55555555, 0x55555555},
	{0x66555555, 0x66555555},
	{0xaaaaaaaa, 0xaaaaaaaa},
	{0x5a5a5a5a, 0x5a5a5a5a},
	{0xfafafafa, 0xfafafafa}, /* case-5 */
	{0x6a5a5555, 0xaaaaaaaa},
	{0x6a5a56aa, 0x6a5a56aa},
	{0x6a5a5a5a, 0x6a5a5a5a},
	{0x66555555, 0x5a5a5a5a},
	{0x66555555, 0x6a5a5a5a}, /* case-10 */
	{0x66555555, 0xaaaaaaaa},
	{0x66555555, 0x6a5a5aaa},
	{0x66555555, 0x6aaa6aaa},
	{0x66555555, 0x6a5a5aaa},
	{0x66555555, 0xaaaaaaaa}, /* case-15 */
	{0xffff55ff, 0xfafafafa},
	{0xffff55ff, 0x6afa5afa},
	{0xaaffffaa, 0xfafafafa},
	{0xaa5555aa, 0x5a5a5a5a},
	{0xaa5555aa, 0x6a5a5a5a}, /* case-20 */
	{0xaa5555aa, 0xaaaaaaaa},
	{0xffffffff, 0x55555555},
	{0xffffffff, 0x5a5a5a5a},
	{0xffffffff, 0x5a5a5a5a},
	{0xffffffff, 0x5a5a5aaa}, /* case-25 */
	{0x55555555, 0x5a5a5a5a},
	{0x55555555, 0xaaaaaaaa},
	{0x66555555, 0x6a5a6a5a},
	{0x66556655, 0x66556655},
	{0x66556aaa, 0x6a5a6aaa}, /* case-30 */
	{0xffffffff, 0x5aaa5aaa},
	{0x56555555, 0x5a5a5aaa}
};

/* Non-Shawed-Antenna Coex Tabwe */
static const stwuct coex_tabwe_pawa tabwe_nsant_8821c[] = {
	{0xffffffff, 0xffffffff}, /* case-100 */
	{0xffff55ff, 0xfafafafa},
	{0x66555555, 0x66555555},
	{0xaaaaaaaa, 0xaaaaaaaa},
	{0x5a5a5a5a, 0x5a5a5a5a},
	{0xffffffff, 0xffffffff}, /* case-105 */
	{0x5afa5afa, 0x5afa5afa},
	{0x55555555, 0xfafafafa},
	{0x66555555, 0xfafafafa},
	{0x66555555, 0x5a5a5a5a},
	{0x66555555, 0x6a5a5a5a}, /* case-110 */
	{0x66555555, 0xaaaaaaaa},
	{0xffff55ff, 0xfafafafa},
	{0xffff55ff, 0x5afa5afa},
	{0xffff55ff, 0xaaaaaaaa},
	{0xffff55ff, 0xffff55ff}, /* case-115 */
	{0xaaffffaa, 0x5afa5afa},
	{0xaaffffaa, 0xaaaaaaaa},
	{0xffffffff, 0xfafafafa},
	{0xffff55ff, 0xfafafafa},
	{0xffffffff, 0xaaaaaaaa}, /* case-120 */
	{0xffff55ff, 0x5afa5afa},
	{0xffff55ff, 0x5afa5afa},
	{0x55ff55ff, 0x55ff55ff}
};

/* Shawed-Antenna TDMA */
static const stwuct coex_tdma_pawa tdma_sant_8821c[] = {
	{ {0x00, 0x00, 0x00, 0x00, 0x00} }, /* case-0 */
	{ {0x61, 0x45, 0x03, 0x11, 0x11} }, /* case-1 */
	{ {0x61, 0x3a, 0x03, 0x11, 0x11} },
	{ {0x61, 0x35, 0x03, 0x11, 0x11} },
	{ {0x61, 0x20, 0x03, 0x11, 0x11} },
	{ {0x61, 0x3a, 0x03, 0x11, 0x11} }, /* case-5 */
	{ {0x61, 0x45, 0x03, 0x11, 0x10} },
	{ {0x61, 0x35, 0x03, 0x11, 0x10} },
	{ {0x61, 0x30, 0x03, 0x11, 0x10} },
	{ {0x61, 0x20, 0x03, 0x11, 0x10} },
	{ {0x61, 0x10, 0x03, 0x11, 0x10} }, /* case-10 */
	{ {0x61, 0x08, 0x03, 0x11, 0x15} },
	{ {0x61, 0x08, 0x03, 0x10, 0x14} },
	{ {0x51, 0x08, 0x03, 0x10, 0x54} },
	{ {0x51, 0x08, 0x03, 0x10, 0x55} },
	{ {0x51, 0x08, 0x07, 0x10, 0x54} }, /* case-15 */
	{ {0x51, 0x45, 0x03, 0x10, 0x50} },
	{ {0x51, 0x3a, 0x03, 0x11, 0x50} },
	{ {0x51, 0x30, 0x03, 0x10, 0x50} },
	{ {0x51, 0x21, 0x03, 0x10, 0x50} },
	{ {0x51, 0x10, 0x03, 0x10, 0x50} }, /* case-20 */
	{ {0x51, 0x4a, 0x03, 0x10, 0x50} },
	{ {0x51, 0x08, 0x03, 0x30, 0x54} },
	{ {0x55, 0x08, 0x03, 0x10, 0x54} },
	{ {0x65, 0x10, 0x03, 0x11, 0x10} },
	{ {0x51, 0x10, 0x03, 0x10, 0x51} }, /* case-25 */
	{ {0x51, 0x21, 0x03, 0x10, 0x50} },
	{ {0x61, 0x08, 0x03, 0x11, 0x11} }
};

/* Non-Shawed-Antenna TDMA */
static const stwuct coex_tdma_pawa tdma_nsant_8821c[] = {
	{ {0x00, 0x00, 0x00, 0x40, 0x00} }, /* case-100 */
	{ {0x61, 0x45, 0x03, 0x11, 0x11} },
	{ {0x61, 0x25, 0x03, 0x11, 0x11} },
	{ {0x61, 0x35, 0x03, 0x11, 0x11} },
	{ {0x61, 0x20, 0x03, 0x11, 0x11} },
	{ {0x61, 0x10, 0x03, 0x11, 0x11} }, /* case-105 */
	{ {0x61, 0x45, 0x03, 0x11, 0x10} },
	{ {0x61, 0x30, 0x03, 0x11, 0x10} },
	{ {0x61, 0x30, 0x03, 0x11, 0x10} },
	{ {0x61, 0x20, 0x03, 0x11, 0x10} },
	{ {0x61, 0x10, 0x03, 0x11, 0x10} }, /* case-110 */
	{ {0x61, 0x10, 0x03, 0x11, 0x11} },
	{ {0x61, 0x08, 0x03, 0x10, 0x14} },
	{ {0x51, 0x08, 0x03, 0x10, 0x54} },
	{ {0x51, 0x08, 0x03, 0x10, 0x55} },
	{ {0x51, 0x08, 0x07, 0x10, 0x54} }, /* case-115 */
	{ {0x51, 0x45, 0x03, 0x10, 0x50} },
	{ {0x51, 0x3a, 0x03, 0x10, 0x50} },
	{ {0x51, 0x30, 0x03, 0x10, 0x50} },
	{ {0x51, 0x21, 0x03, 0x10, 0x50} },
	{ {0x51, 0x21, 0x03, 0x10, 0x50} }, /* case-120 */
	{ {0x51, 0x10, 0x03, 0x10, 0x50} }
};

static const stwuct coex_5g_afh_map afh_5g_8821c[] = { {0, 0, 0} };

/* ww_tx_dec_powew, bt_tx_dec_powew, ww_wx_gain, bt_wx_wna_constwain */
static const stwuct coex_wf_pawa wf_pawa_tx_8821c[] = {
	{0, 0, fawse, 7},  /* fow nowmaw */
	{0, 20, fawse, 7}, /* fow WW-CPT */
	{8, 17, twue, 4},
	{7, 18, twue, 4},
	{6, 19, twue, 4},
	{5, 20, twue, 4}
};

static const stwuct coex_wf_pawa wf_pawa_wx_8821c[] = {
	{0, 0, fawse, 7},  /* fow nowmaw */
	{0, 20, fawse, 7}, /* fow WW-CPT */
	{3, 24, twue, 5},
	{2, 26, twue, 5},
	{1, 27, twue, 5},
	{0, 28, twue, 5}
};

static_assewt(AWWAY_SIZE(wf_pawa_tx_8821c) == AWWAY_SIZE(wf_pawa_wx_8821c));

static const u8 wtw8821c_pwwtwk_5gb_n[][WTW_PWW_TWK_TBW_SZ] = {
	{0, 1, 1, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 8, 8, 8, 9, 9, 9, 10, 10,
	 11, 11, 12, 12, 12, 12, 12},
	{0, 1, 1, 1, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12, 12},
	{0, 1, 2, 2, 3, 4, 4, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12},
};

static const u8 wtw8821c_pwwtwk_5gb_p[][WTW_PWW_TWK_TBW_SZ] = {
	{0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 11, 11,
	 12, 12, 12, 12, 12, 12, 12},
	{0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 6, 7, 7, 8, 8, 9, 10, 10, 11, 11,
	 12, 12, 12, 12, 12, 12, 12, 12},
	{0, 1, 1, 1, 2, 3, 3, 3, 4, 4, 4, 5, 6, 6, 7, 7, 8, 8, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12, 12},
};

static const u8 wtw8821c_pwwtwk_5ga_n[][WTW_PWW_TWK_TBW_SZ] = {
	{0, 1, 1, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 8, 8, 8, 9, 9, 9, 10, 10,
	 11, 11, 12, 12, 12, 12, 12},
	{0, 1, 1, 1, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12, 12},
	{0, 1, 2, 2, 3, 4, 4, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12},
};

static const u8 wtw8821c_pwwtwk_5ga_p[][WTW_PWW_TWK_TBW_SZ] = {
	{0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 11, 11,
	 12, 12, 12, 12, 12, 12, 12},
	{0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 6, 7, 7, 8, 8, 9, 10, 10, 11, 11,
	 12, 12, 12, 12, 12, 12, 12, 12},
	{0, 1, 1, 1, 2, 3, 3, 3, 4, 4, 4, 5, 6, 6, 7, 7, 8, 8, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12, 12},
};

static const u8 wtw8821c_pwwtwk_2gb_n[] = {
	0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4,
	4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 8, 8, 9
};

static const u8 wtw8821c_pwwtwk_2gb_p[] = {
	0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5,
	5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 9
};

static const u8 wtw8821c_pwwtwk_2ga_n[] = {
	0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4,
	4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 8, 8, 9
};

static const u8 wtw8821c_pwwtwk_2ga_p[] = {
	0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5,
	5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 9
};

static const u8 wtw8821c_pwwtwk_2g_cck_b_n[] = {
	0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
	4, 5, 5, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9
};

static const u8 wtw8821c_pwwtwk_2g_cck_b_p[] = {
	0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5,
	5, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9
};

static const u8 wtw8821c_pwwtwk_2g_cck_a_n[] = {
	0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
	4, 5, 5, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9
};

static const u8 wtw8821c_pwwtwk_2g_cck_a_p[] = {
	0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5,
	5, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9
};

static const stwuct wtw_pww_twack_tbw wtw8821c_wtw_pww_twack_tbw = {
	.pwwtwk_5gb_n[0] = wtw8821c_pwwtwk_5gb_n[0],
	.pwwtwk_5gb_n[1] = wtw8821c_pwwtwk_5gb_n[1],
	.pwwtwk_5gb_n[2] = wtw8821c_pwwtwk_5gb_n[2],
	.pwwtwk_5gb_p[0] = wtw8821c_pwwtwk_5gb_p[0],
	.pwwtwk_5gb_p[1] = wtw8821c_pwwtwk_5gb_p[1],
	.pwwtwk_5gb_p[2] = wtw8821c_pwwtwk_5gb_p[2],
	.pwwtwk_5ga_n[0] = wtw8821c_pwwtwk_5ga_n[0],
	.pwwtwk_5ga_n[1] = wtw8821c_pwwtwk_5ga_n[1],
	.pwwtwk_5ga_n[2] = wtw8821c_pwwtwk_5ga_n[2],
	.pwwtwk_5ga_p[0] = wtw8821c_pwwtwk_5ga_p[0],
	.pwwtwk_5ga_p[1] = wtw8821c_pwwtwk_5ga_p[1],
	.pwwtwk_5ga_p[2] = wtw8821c_pwwtwk_5ga_p[2],
	.pwwtwk_2gb_n = wtw8821c_pwwtwk_2gb_n,
	.pwwtwk_2gb_p = wtw8821c_pwwtwk_2gb_p,
	.pwwtwk_2ga_n = wtw8821c_pwwtwk_2ga_n,
	.pwwtwk_2ga_p = wtw8821c_pwwtwk_2ga_p,
	.pwwtwk_2g_cckb_n = wtw8821c_pwwtwk_2g_cck_b_n,
	.pwwtwk_2g_cckb_p = wtw8821c_pwwtwk_2g_cck_b_p,
	.pwwtwk_2g_ccka_n = wtw8821c_pwwtwk_2g_cck_a_n,
	.pwwtwk_2g_ccka_p = wtw8821c_pwwtwk_2g_cck_a_p,
};

static const stwuct wtw_weg_domain coex_info_hw_wegs_8821c[] = {
	{0xCB0, MASKDWOWD, WTW_WEG_DOMAIN_MAC32},
	{0xCB4, MASKDWOWD, WTW_WEG_DOMAIN_MAC32},
	{0xCBA, MASKBYTE0, WTW_WEG_DOMAIN_MAC8},
	{0, 0, WTW_WEG_DOMAIN_NW},
	{0x430, MASKDWOWD, WTW_WEG_DOMAIN_MAC32},
	{0x434, MASKDWOWD, WTW_WEG_DOMAIN_MAC32},
	{0x42a, MASKWWOWD, WTW_WEG_DOMAIN_MAC16},
	{0x426, MASKBYTE0, WTW_WEG_DOMAIN_MAC8},
	{0x45e, BIT(3), WTW_WEG_DOMAIN_MAC8},
	{0x454, MASKWWOWD, WTW_WEG_DOMAIN_MAC16},
	{0, 0, WTW_WEG_DOMAIN_NW},
	{0x4c, BIT(24) | BIT(23), WTW_WEG_DOMAIN_MAC32},
	{0x64, BIT(0), WTW_WEG_DOMAIN_MAC8},
	{0x4c6, BIT(4), WTW_WEG_DOMAIN_MAC8},
	{0x40, BIT(5), WTW_WEG_DOMAIN_MAC8},
	{0x1, WFWEG_MASK, WTW_WEG_DOMAIN_WF_A},
	{0, 0, WTW_WEG_DOMAIN_NW},
	{0x550, MASKDWOWD, WTW_WEG_DOMAIN_MAC32},
	{0x522, MASKBYTE0, WTW_WEG_DOMAIN_MAC8},
	{0x953, BIT(1), WTW_WEG_DOMAIN_MAC8},
	{0xc50,  MASKBYTE0, WTW_WEG_DOMAIN_MAC8},
	{0x60A, MASKBYTE0, WTW_WEG_DOMAIN_MAC8},
};

const stwuct wtw_chip_info wtw8821c_hw_spec = {
	.ops = &wtw8821c_ops,
	.id = WTW_CHIP_TYPE_8821C,
	.fw_name = "wtw88/wtw8821c_fw.bin",
	.wwan_cpu = WTW_WCPU_11AC,
	.tx_pkt_desc_sz = 48,
	.tx_buf_desc_sz = 16,
	.wx_pkt_desc_sz = 24,
	.wx_buf_desc_sz = 8,
	.phy_efuse_size = 512,
	.wog_efuse_size = 512,
	.ptct_efuse_size = 96,
	.txff_size = 65536,
	.wxff_size = 16384,
	.wsvd_dwv_pg_num = 8,
	.txgi_factow = 1,
	.is_pww_by_wate_dec = twue,
	.max_powew_index = 0x3f,
	.csi_buf_pg_num = 0,
	.band = WTW_BAND_2G | WTW_BAND_5G,
	.page_size = TX_PAGE_SIZE,
	.dig_min = 0x1c,
	.ht_suppowted = twue,
	.vht_suppowted = twue,
	.wps_deep_mode_suppowted = BIT(WPS_DEEP_MODE_WCWK),
	.sys_func_en = 0xD8,
	.pww_on_seq = cawd_enabwe_fwow_8821c,
	.pww_off_seq = cawd_disabwe_fwow_8821c,
	.page_tabwe = page_tabwe_8821c,
	.wqpn_tabwe = wqpn_tabwe_8821c,
	.pwioq_addws = &pwioq_addws_8821c,
	.intf_tabwe = &phy_pawa_tabwe_8821c,
	.dig = wtw8821c_dig,
	.wf_base_addw = {0x2800, 0x2c00},
	.wf_sipi_addw = {0xc90, 0xe90},
	.wtecoex_addw = &wtw8821c_wtecoex_addw,
	.mac_tbw = &wtw8821c_mac_tbw,
	.agc_tbw = &wtw8821c_agc_tbw,
	.bb_tbw = &wtw8821c_bb_tbw,
	.wf_tbw = {&wtw8821c_wf_a_tbw},
	.wfe_defs = wtw8821c_wfe_defs,
	.wfe_defs_size = AWWAY_SIZE(wtw8821c_wfe_defs),
	.wx_wdpc = fawse,
	.pww_twack_tbw = &wtw8821c_wtw_pww_twack_tbw,
	.iqk_thweshowd = 8,
	.bfew_su_max_num = 2,
	.bfew_mu_max_num = 1,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_2,
	.max_scan_ie_wen = IEEE80211_MAX_DATA_WEN,

	.coex_pawa_vew = 0x19092746,
	.bt_desiwed_vew = 0x46,
	.scbd_suppowt = twue,
	.new_scbd10_def = fawse,
	.bwe_hid_pwofiwe_suppowt = fawse,
	.ww_mimo_ps_suppowt = fawse,
	.pstdma_type = COEX_PSTDMA_FOWCE_WPSOFF,
	.bt_wssi_type = COEX_BTWSSI_WATIO,
	.ant_isowation = 15,
	.wssi_towewance = 2,
	.ww_wssi_step = ww_wssi_step_8821c,
	.bt_wssi_step = bt_wssi_step_8821c,
	.tabwe_sant_num = AWWAY_SIZE(tabwe_sant_8821c),
	.tabwe_sant = tabwe_sant_8821c,
	.tabwe_nsant_num = AWWAY_SIZE(tabwe_nsant_8821c),
	.tabwe_nsant = tabwe_nsant_8821c,
	.tdma_sant_num = AWWAY_SIZE(tdma_sant_8821c),
	.tdma_sant = tdma_sant_8821c,
	.tdma_nsant_num = AWWAY_SIZE(tdma_nsant_8821c),
	.tdma_nsant = tdma_nsant_8821c,
	.ww_wf_pawa_num = AWWAY_SIZE(wf_pawa_tx_8821c),
	.ww_wf_pawa_tx = wf_pawa_tx_8821c,
	.ww_wf_pawa_wx = wf_pawa_wx_8821c,
	.bt_afh_span_bw20 = 0x24,
	.bt_afh_span_bw40 = 0x36,
	.afh_5g_num = AWWAY_SIZE(afh_5g_8821c),
	.afh_5g = afh_5g_8821c,

	.coex_info_hw_wegs_num = AWWAY_SIZE(coex_info_hw_wegs_8821c),
	.coex_info_hw_wegs = coex_info_hw_wegs_8821c,
};
EXPOWT_SYMBOW(wtw8821c_hw_spec);

MODUWE_FIWMWAWE("wtw88/wtw8821c_fw.bin");

MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11ac wiwewess 8821c dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
