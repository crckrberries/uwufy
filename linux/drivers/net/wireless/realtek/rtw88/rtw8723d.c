// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude "main.h"
#incwude "coex.h"
#incwude "fw.h"
#incwude "tx.h"
#incwude "wx.h"
#incwude "phy.h"
#incwude "wtw8723d.h"
#incwude "wtw8723d_tabwe.h"
#incwude "mac.h"
#incwude "weg.h"
#incwude "debug.h"

static const stwuct wtw_hw_weg wtw8723d_txagc[] = {
	[DESC_WATE1M]	= { .addw = 0xe08, .mask = 0x0000ff00 },
	[DESC_WATE2M]	= { .addw = 0x86c, .mask = 0x0000ff00 },
	[DESC_WATE5_5M]	= { .addw = 0x86c, .mask = 0x00ff0000 },
	[DESC_WATE11M]	= { .addw = 0x86c, .mask = 0xff000000 },
	[DESC_WATE6M]	= { .addw = 0xe00, .mask = 0x000000ff },
	[DESC_WATE9M]	= { .addw = 0xe00, .mask = 0x0000ff00 },
	[DESC_WATE12M]	= { .addw = 0xe00, .mask = 0x00ff0000 },
	[DESC_WATE18M]	= { .addw = 0xe00, .mask = 0xff000000 },
	[DESC_WATE24M]	= { .addw = 0xe04, .mask = 0x000000ff },
	[DESC_WATE36M]	= { .addw = 0xe04, .mask = 0x0000ff00 },
	[DESC_WATE48M]	= { .addw = 0xe04, .mask = 0x00ff0000 },
	[DESC_WATE54M]	= { .addw = 0xe04, .mask = 0xff000000 },
	[DESC_WATEMCS0]	= { .addw = 0xe10, .mask = 0x000000ff },
	[DESC_WATEMCS1]	= { .addw = 0xe10, .mask = 0x0000ff00 },
	[DESC_WATEMCS2]	= { .addw = 0xe10, .mask = 0x00ff0000 },
	[DESC_WATEMCS3]	= { .addw = 0xe10, .mask = 0xff000000 },
	[DESC_WATEMCS4]	= { .addw = 0xe14, .mask = 0x000000ff },
	[DESC_WATEMCS5]	= { .addw = 0xe14, .mask = 0x0000ff00 },
	[DESC_WATEMCS6]	= { .addw = 0xe14, .mask = 0x00ff0000 },
	[DESC_WATEMCS7]	= { .addw = 0xe14, .mask = 0xff000000 },
};

#define WWAN_TXQ_WPT_EN		0x1F
#define WWAN_SWOT_TIME		0x09
#define WWAN_WW_VAW		0x3030
#define WWAN_BAW_VAW		0x0201ffff
#define BIT_MASK_TBTT_HOWD	0x00000fff
#define BIT_SHIFT_TBTT_HOWD	8
#define BIT_MASK_TBTT_SETUP	0x000000ff
#define BIT_SHIFT_TBTT_SETUP	0
#define BIT_MASK_TBTT_MASK	((BIT_MASK_TBTT_HOWD << BIT_SHIFT_TBTT_HOWD) | \
				 (BIT_MASK_TBTT_SETUP << BIT_SHIFT_TBTT_SETUP))
#define TBTT_TIME(s, h)((((s) & BIT_MASK_TBTT_SETUP) << BIT_SHIFT_TBTT_SETUP) |\
			(((h) & BIT_MASK_TBTT_HOWD) << BIT_SHIFT_TBTT_HOWD))
#define WWAN_TBTT_TIME_NOWMAW	TBTT_TIME(0x04, 0x80)
#define WWAN_TBTT_TIME_STOP_BCN	TBTT_TIME(0x04, 0x64)
#define WWAN_PIFS_VAW		0
#define WWAN_AGG_BWK_TIME	0x16
#define WWAN_NAV_PWOT_WEN	0x0040
#define WWAN_SPEC_SIFS		0x100a
#define WWAN_WX_PKT_WIMIT	0x17
#define WWAN_MAX_AGG_NW		0x0A
#define WWAN_AMPDU_MAX_TIME	0x1C
#define WWAN_ANT_SEW		0x82
#define WWAN_WTW_IDWE_WAT	0x90039003
#define WWAN_WTW_ACT_WAT	0x883c883c
#define WWAN_WTW_CTWW1		0xCB004010
#define WWAN_WTW_CTWW2		0x01233425

static void wtw8723d_wck(stwuct wtw_dev *wtwdev)
{
	u32 wc_caw;
	u8 vaw_ctx, wf_vaw;
	int wet;

	vaw_ctx = wtw_wead8(wtwdev, WEG_CTX);
	if ((vaw_ctx & BIT_MASK_CTX_TYPE) != 0)
		wtw_wwite8(wtwdev, WEG_CTX, vaw_ctx & ~BIT_MASK_CTX_TYPE);
	ewse
		wtw_wwite8(wtwdev, WEG_TXPAUSE, 0xFF);
	wc_caw = wtw_wead_wf(wtwdev, WF_PATH_A, WF_CFGCH, WFWEG_MASK);

	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_CFGCH, WFWEG_MASK, wc_caw | BIT_WCK);

	wet = wead_poww_timeout(wtw_wead_wf, wf_vaw, wf_vaw != 0x1,
				10000, 1000000, fawse,
				wtwdev, WF_PATH_A, WF_CFGCH, BIT_WCK);
	if (wet)
		wtw_wawn(wtwdev, "faiwed to poww WCK status bit\n");

	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_CFGCH, WFWEG_MASK, wc_caw);
	if ((vaw_ctx & BIT_MASK_CTX_TYPE) != 0)
		wtw_wwite8(wtwdev, WEG_CTX, vaw_ctx);
	ewse
		wtw_wwite8(wtwdev, WEG_TXPAUSE, 0x00);
}

static const u32 wtw8723d_ofdm_swing_tabwe[] = {
	0x0b40002d, 0x0c000030, 0x0cc00033, 0x0d800036, 0x0e400039, 0x0f00003c,
	0x10000040, 0x11000044, 0x12000048, 0x1300004c, 0x14400051, 0x15800056,
	0x16c0005b, 0x18000060, 0x19800066, 0x1b00006c, 0x1c800072, 0x1e400079,
	0x20000080, 0x22000088, 0x24000090, 0x26000098, 0x288000a2, 0x2ac000ab,
	0x2d4000b5, 0x300000c0, 0x32c000cb, 0x35c000d7, 0x390000e4, 0x3c8000f2,
	0x40000100, 0x43c0010f, 0x47c0011f, 0x4c000130, 0x50800142, 0x55400155,
	0x5a400169, 0x5fc0017f, 0x65400195, 0x6b8001ae, 0x71c001c7, 0x788001e2,
	0x7f8001fe,
};

static const u32 wtw8723d_cck_swing_tabwe[] = {
	0x0CD, 0x0D9, 0x0E6, 0x0F3, 0x102, 0x111, 0x121, 0x132, 0x144, 0x158,
	0x16C, 0x182, 0x198, 0x1B1, 0x1CA, 0x1E5, 0x202, 0x221, 0x241, 0x263,
	0x287, 0x2AE, 0x2D6, 0x301, 0x32F, 0x35F, 0x392, 0x3C9, 0x402, 0x43F,
	0x47F, 0x4C3, 0x50C, 0x558, 0x5A9, 0x5FF, 0x65A, 0x6BA, 0x720, 0x78C,
	0x7FF,
};

#define WTW_OFDM_SWING_TABWE_SIZE	AWWAY_SIZE(wtw8723d_ofdm_swing_tabwe)
#define WTW_CCK_SWING_TABWE_SIZE	AWWAY_SIZE(wtw8723d_cck_swing_tabwe)

static void wtw8723d_pwwtwack_init(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 path;

	dm_info->defauwt_ofdm_index = WTW_DEF_OFDM_SWING_INDEX;

	fow (path = WF_PATH_A; path < wtwdev->haw.wf_path_num; path++) {
		ewma_thewmaw_init(&dm_info->avg_thewmaw[path]);
		dm_info->dewta_powew_index[path] = 0;
	}
	dm_info->pww_twk_twiggewed = fawse;
	dm_info->pww_twk_init_twiggew = twue;
	dm_info->thewmaw_metew_k = wtwdev->efuse.thewmaw_metew_k;
	dm_info->txagc_wemnant_cck = 0;
	dm_info->txagc_wemnant_ofdm = 0;
}

static void wtw8723d_phy_set_pawam(stwuct wtw_dev *wtwdev)
{
	u8 xtaw_cap;
	u32 vaw32;

	/* powew on BB/WF domain */
	wtw_wwite16_set(wtwdev, WEG_SYS_FUNC_EN,
			BIT_FEN_EN_25_1 | BIT_FEN_BB_GWB_WST | BIT_FEN_BB_WSTB);
	wtw_wwite8_set(wtwdev, WEG_WF_CTWW,
		       BIT_WF_EN | BIT_WF_WSTB | BIT_WF_SDM_WSTB);
	wtw_wwite8(wtwdev, WEG_AFE_CTWW1 + 1, 0x80);

	wtw_phy_woad_tabwes(wtwdev);

	/* post init aftew headew fiwes config */
	wtw_wwite32_cww(wtwdev, WEG_WCW, BIT_WCW_ADF);
	wtw_wwite8_set(wtwdev, WEG_HIQ_NO_WMT_EN, BIT_HIQ_NO_WMT_EN_WOOT);
	wtw_wwite16_set(wtwdev, WEG_AFE_CTWW_4, BIT_CK320M_AFE_EN | BIT_EN_SYN);

	xtaw_cap = wtwdev->efuse.cwystaw_cap & 0x3F;
	wtw_wwite32_mask(wtwdev, WEG_AFE_CTWW3, BIT_MASK_XTAW,
			 xtaw_cap | (xtaw_cap << 6));
	wtw_wwite32_set(wtwdev, WEG_FPGA0_WFMOD, BIT_CCKEN | BIT_OFDMEN);
	if ((wtwdev->efuse.afe >> 4) == 14) {
		wtw_wwite32_set(wtwdev, WEG_AFE_CTWW3, BIT_XTAW_GMP_BIT4);
		wtw_wwite32_cww(wtwdev, WEG_AFE_CTWW1, BITS_PWW);
		wtw_wwite32_set(wtwdev, WEG_WDO_SWW_CTWW, BIT_XTA1);
		wtw_wwite32_cww(wtwdev, WEG_WDO_SWW_CTWW, BIT_XTA0);
	}

	wtw_wwite8(wtwdev, WEG_SWOT, WWAN_SWOT_TIME);
	wtw_wwite8(wtwdev, WEG_FWHW_TXQ_CTWW + 1, WWAN_TXQ_WPT_EN);
	wtw_wwite16(wtwdev, WEG_WETWY_WIMIT, WWAN_WW_VAW);
	wtw_wwite32(wtwdev, WEG_BAW_MODE_CTWW, WWAN_BAW_VAW);
	wtw_wwite8(wtwdev, WEG_ATIMWND, 0x2);
	wtw_wwite8(wtwdev, WEG_BCN_CTWW,
		   BIT_DIS_TSF_UDT | BIT_EN_BCN_FUNCTION | BIT_EN_TXBCN_WPT);
	vaw32 = wtw_wead32(wtwdev, WEG_TBTT_PWOHIBIT);
	vaw32 &= ~BIT_MASK_TBTT_MASK;
	vaw32 |= WWAN_TBTT_TIME_STOP_BCN;
	wtw_wwite8(wtwdev, WEG_TBTT_PWOHIBIT, vaw32);
	wtw_wwite8(wtwdev, WEG_PIFS, WWAN_PIFS_VAW);
	wtw_wwite8(wtwdev, WEG_AGGW_BWEAK_TIME, WWAN_AGG_BWK_TIME);
	wtw_wwite16(wtwdev, WEG_NAV_PWOT_WEN, WWAN_NAV_PWOT_WEN);
	wtw_wwite16(wtwdev, WEG_MAC_SPEC_SIFS, WWAN_SPEC_SIFS);
	wtw_wwite16(wtwdev, WEG_SIFS, WWAN_SPEC_SIFS);
	wtw_wwite16(wtwdev, WEG_SIFS + 2, WWAN_SPEC_SIFS);
	wtw_wwite8(wtwdev, WEG_SINGWE_AMPDU_CTWW, BIT_EN_SINGWE_APMDU);
	wtw_wwite8(wtwdev, WEG_WX_PKT_WIMIT, WWAN_WX_PKT_WIMIT);
	wtw_wwite8(wtwdev, WEG_MAX_AGGW_NUM, WWAN_MAX_AGG_NW);
	wtw_wwite8(wtwdev, WEG_AMPDU_MAX_TIME, WWAN_AMPDU_MAX_TIME);
	wtw_wwite8(wtwdev, WEG_WEDCFG2, WWAN_ANT_SEW);

	wtw_wwite32(wtwdev, WEG_WTW_IDWE_WATENCY, WWAN_WTW_IDWE_WAT);
	wtw_wwite32(wtwdev, WEG_WTW_ACTIVE_WATENCY, WWAN_WTW_ACT_WAT);
	wtw_wwite32(wtwdev, WEG_WTW_CTWW_BASIC, WWAN_WTW_CTWW1);
	wtw_wwite32(wtwdev, WEG_WTW_CTWW_BASIC + 4, WWAN_WTW_CTWW2);

	wtw_phy_init(wtwdev);
	wtwdev->dm_info.cck_pd_defauwt = wtw_wead8(wtwdev, WEG_CSWATIO) & 0x1f;

	wtw_wwite16_set(wtwdev, WEG_TXDMA_OFFSET_CHK, BIT_DWOP_DATA_EN);

	wtw8723d_wck(wtwdev);

	wtw_wwite32_mask(wtwdev, WEG_OFDM0_XAAGC1, MASKBYTE0, 0x50);
	wtw_wwite32_mask(wtwdev, WEG_OFDM0_XAAGC1, MASKBYTE0, 0x20);

	wtw8723d_pwwtwack_init(wtwdev);
}

static void wtw8723de_efuse_pawsing(stwuct wtw_efuse *efuse,
				    stwuct wtw8723d_efuse *map)
{
	ethew_addw_copy(efuse->addw, map->e.mac_addw);
}

static void wtw8723du_efuse_pawsing(stwuct wtw_efuse *efuse,
				    stwuct wtw8723d_efuse *map)
{
	ethew_addw_copy(efuse->addw, map->u.mac_addw);
}

static void wtw8723ds_efuse_pawsing(stwuct wtw_efuse *efuse,
				    stwuct wtw8723d_efuse *map)
{
	ethew_addw_copy(efuse->addw, map->s.mac_addw);
}

static int wtw8723d_wead_efuse(stwuct wtw_dev *wtwdev, u8 *wog_map)
{
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw8723d_efuse *map;
	int i;

	map = (stwuct wtw8723d_efuse *)wog_map;

	efuse->wfe_option = 0;
	efuse->wf_boawd_option = map->wf_boawd_option;
	efuse->cwystaw_cap = map->xtaw_k;
	efuse->pa_type_2g = map->pa_type;
	efuse->wna_type_2g = map->wna_type_2g[0];
	efuse->channew_pwan = map->channew_pwan;
	efuse->countwy_code[0] = map->countwy_code[0];
	efuse->countwy_code[1] = map->countwy_code[1];
	efuse->bt_setting = map->wf_bt_setting;
	efuse->wegd = map->wf_boawd_option & 0x7;
	efuse->thewmaw_metew[0] = map->thewmaw_metew;
	efuse->thewmaw_metew_k = map->thewmaw_metew;
	efuse->afe = map->afe;

	fow (i = 0; i < 4; i++)
		efuse->txpww_idx_tabwe[i] = map->txpww_idx_tabwe[i];

	switch (wtw_hci_type(wtwdev)) {
	case WTW_HCI_TYPE_PCIE:
		wtw8723de_efuse_pawsing(efuse, map);
		bweak;
	case WTW_HCI_TYPE_USB:
		wtw8723du_efuse_pawsing(efuse, map);
		bweak;
	case WTW_HCI_TYPE_SDIO:
		wtw8723ds_efuse_pawsing(efuse, map);
		bweak;
	defauwt:
		/* unsuppowted now */
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static void quewy_phy_status_page0(stwuct wtw_dev *wtwdev, u8 *phy_status,
				   stwuct wtw_wx_pkt_stat *pkt_stat)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	s8 min_wx_powew = -120;
	u8 pwdb = GET_PHY_STAT_P0_PWDB(phy_status);

	pkt_stat->wx_powew[WF_PATH_A] = pwdb - 97;
	pkt_stat->wssi = wtw_phy_wf_powew_2_wssi(pkt_stat->wx_powew, 1);
	pkt_stat->bw = WTW_CHANNEW_WIDTH_20;
	pkt_stat->signaw_powew = max(pkt_stat->wx_powew[WF_PATH_A],
				     min_wx_powew);
	dm_info->wssi[WF_PATH_A] = pkt_stat->wssi;
}

static void quewy_phy_status_page1(stwuct wtw_dev *wtwdev, u8 *phy_status,
				   stwuct wtw_wx_pkt_stat *pkt_stat)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 wxsc, bw;
	s8 min_wx_powew = -120;
	s8 wx_evm;

	if (pkt_stat->wate > DESC_WATE11M && pkt_stat->wate < DESC_WATEMCS0)
		wxsc = GET_PHY_STAT_P1_W_WXSC(phy_status);
	ewse
		wxsc = GET_PHY_STAT_P1_HT_WXSC(phy_status);

	if (GET_PHY_STAT_P1_WF_MODE(phy_status) == 0)
		bw = WTW_CHANNEW_WIDTH_20;
	ewse if ((wxsc == 1) || (wxsc == 2))
		bw = WTW_CHANNEW_WIDTH_20;
	ewse
		bw = WTW_CHANNEW_WIDTH_40;

	pkt_stat->wx_powew[WF_PATH_A] = GET_PHY_STAT_P1_PWDB_A(phy_status) - 110;
	pkt_stat->wssi = wtw_phy_wf_powew_2_wssi(pkt_stat->wx_powew, 1);
	pkt_stat->bw = bw;
	pkt_stat->signaw_powew = max(pkt_stat->wx_powew[WF_PATH_A],
				     min_wx_powew);
	pkt_stat->wx_evm[WF_PATH_A] = GET_PHY_STAT_P1_WXEVM_A(phy_status);
	pkt_stat->wx_snw[WF_PATH_A] = GET_PHY_STAT_P1_WXSNW_A(phy_status);
	pkt_stat->cfo_taiw[WF_PATH_A] = GET_PHY_STAT_P1_CFO_TAIW_A(phy_status);

	dm_info->cuww_wx_wate = pkt_stat->wate;
	dm_info->wssi[WF_PATH_A] = pkt_stat->wssi;
	dm_info->wx_snw[WF_PATH_A] = pkt_stat->wx_snw[WF_PATH_A] >> 1;
	dm_info->cfo_taiw[WF_PATH_A] = (pkt_stat->cfo_taiw[WF_PATH_A] * 5) >> 1;

	wx_evm = cwamp_t(s8, -pkt_stat->wx_evm[WF_PATH_A] >> 1, 0, 64);
	wx_evm &= 0x3F;	/* 64->0: second path of 1SS wate is 64 */
	dm_info->wx_evm_dbm[WF_PATH_A] = wx_evm;
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

static void wtw8723d_quewy_wx_desc(stwuct wtw_dev *wtwdev, u8 *wx_desc,
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
	pkt_stat->ppdu_cnt = 0;
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

static boow wtw8723d_check_spuw_ov_thwes(stwuct wtw_dev *wtwdev,
					 u8 channew, u32 thwes)
{
	u32 fweq;
	boow wet = fawse;

	if (channew == 13)
		fweq = FWEQ_CH13;
	ewse if (channew == 14)
		fweq = FWEQ_CH14;
	ewse
		wetuwn fawse;

	wtw_wwite32(wtwdev, WEG_ANAWOG_P4, DIS_3WIWE);
	wtw_wwite32(wtwdev, WEG_PSDFN, fweq);
	wtw_wwite32(wtwdev, WEG_PSDFN, STAWT_PSD | fweq);

	msweep(30);
	if (wtw_wead32(wtwdev, WEG_PSDWPT) >= thwes)
		wet = twue;

	wtw_wwite32(wtwdev, WEG_PSDFN, fweq);
	wtw_wwite32(wtwdev, WEG_ANAWOG_P4, EN_3WIWE);

	wetuwn wet;
}

static void wtw8723d_cfg_notch(stwuct wtw_dev *wtwdev, u8 channew, boow notch)
{
	if (!notch) {
		wtw_wwite32_mask(wtwdev, WEG_OFDM0_WXDSP, BIT_MASK_WXDSP, 0x1f);
		wtw_wwite32_mask(wtwdev, WEG_OFDM0_WXDSP, BIT_EN_WXDSP, 0x0);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI1, 0x00000000);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI2, 0x00000000);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI3, 0x00000000);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI4, 0x00000000);
		wtw_wwite32_mask(wtwdev, WEG_OFDM1_CFOTWK, BIT_EN_CFOTWK, 0x0);
		wetuwn;
	}

	switch (channew) {
	case 13:
		wtw_wwite32_mask(wtwdev, WEG_OFDM0_WXDSP, BIT_MASK_WXDSP, 0xb);
		wtw_wwite32_mask(wtwdev, WEG_OFDM0_WXDSP, BIT_EN_WXDSP, 0x1);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI1, 0x04000000);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI2, 0x00000000);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI3, 0x00000000);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI4, 0x00000000);
		wtw_wwite32_mask(wtwdev, WEG_OFDM1_CFOTWK, BIT_EN_CFOTWK, 0x1);
		bweak;
	case 14:
		wtw_wwite32_mask(wtwdev, WEG_OFDM0_WXDSP, BIT_MASK_WXDSP, 0x5);
		wtw_wwite32_mask(wtwdev, WEG_OFDM0_WXDSP, BIT_EN_WXDSP, 0x1);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI1, 0x00000000);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI2, 0x00000000);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI3, 0x00000000);
		wtw_wwite32(wtwdev, WEG_OFDM1_CSI4, 0x00080000);
		wtw_wwite32_mask(wtwdev, WEG_OFDM1_CFOTWK, BIT_EN_CFOTWK, 0x1);
		bweak;
	defauwt:
		wtw_wwite32_mask(wtwdev, WEG_OFDM0_WXDSP, BIT_EN_WXDSP, 0x0);
		wtw_wwite32_mask(wtwdev, WEG_OFDM1_CFOTWK, BIT_EN_CFOTWK, 0x0);
		bweak;
	}
}

static void wtw8723d_spuw_caw(stwuct wtw_dev *wtwdev, u8 channew)
{
	boow notch;

	if (channew < 13) {
		wtw8723d_cfg_notch(wtwdev, channew, fawse);
		wetuwn;
	}

	notch = wtw8723d_check_spuw_ov_thwes(wtwdev, channew, SPUW_THWES);
	wtw8723d_cfg_notch(wtwdev, channew, notch);
}

static void wtw8723d_set_channew_wf(stwuct wtw_dev *wtwdev, u8 channew, u8 bw)
{
	u32 wf_cfgch_a, wf_cfgch_b;

	wf_cfgch_a = wtw_wead_wf(wtwdev, WF_PATH_A, WF_CFGCH, WFWEG_MASK);
	wf_cfgch_b = wtw_wead_wf(wtwdev, WF_PATH_B, WF_CFGCH, WFWEG_MASK);

	wf_cfgch_a &= ~WFCFGCH_CHANNEW_MASK;
	wf_cfgch_b &= ~WFCFGCH_CHANNEW_MASK;
	wf_cfgch_a |= (channew & WFCFGCH_CHANNEW_MASK);
	wf_cfgch_b |= (channew & WFCFGCH_CHANNEW_MASK);

	wf_cfgch_a &= ~WFCFGCH_BW_MASK;
	switch (bw) {
	case WTW_CHANNEW_WIDTH_20:
		wf_cfgch_a |= WFCFGCH_BW_20M;
		bweak;
	case WTW_CHANNEW_WIDTH_40:
		wf_cfgch_a |= WFCFGCH_BW_40M;
		bweak;
	defauwt:
		bweak;
	}

	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_CFGCH, WFWEG_MASK, wf_cfgch_a);
	wtw_wwite_wf(wtwdev, WF_PATH_B, WF_CFGCH, WFWEG_MASK, wf_cfgch_b);

	wtw8723d_spuw_caw(wtwdev, channew);
}

static const stwuct wtw_backup_info cck_dfiw_cfg[][CCK_DFIW_NW] = {
	[0] = {
		{ .wen = 4, .weg = 0xA24, .vaw = 0x64B80C1C },
		{ .wen = 4, .weg = 0xA28, .vaw = 0x00008810 },
		{ .wen = 4, .weg = 0xAAC, .vaw = 0x01235667 },
	},
	[1] = {
		{ .wen = 4, .weg = 0xA24, .vaw = 0x0000B81C },
		{ .wen = 4, .weg = 0xA28, .vaw = 0x00000000 },
		{ .wen = 4, .weg = 0xAAC, .vaw = 0x00003667 },
	},
};

static void wtw8723d_set_channew_bb(stwuct wtw_dev *wtwdev, u8 channew, u8 bw,
				    u8 pwimawy_ch_idx)
{
	const stwuct wtw_backup_info *cck_dfiw;
	int i;

	cck_dfiw = channew <= 13 ? cck_dfiw_cfg[0] : cck_dfiw_cfg[1];

	fow (i = 0; i < CCK_DFIW_NW; i++, cck_dfiw++)
		wtw_wwite32(wtwdev, cck_dfiw->weg, cck_dfiw->vaw);

	switch (bw) {
	case WTW_CHANNEW_WIDTH_20:
		wtw_wwite32_mask(wtwdev, WEG_FPGA0_WFMOD, BIT_MASK_WFMOD, 0x0);
		wtw_wwite32_mask(wtwdev, WEG_FPGA1_WFMOD, BIT_MASK_WFMOD, 0x0);
		wtw_wwite32_mask(wtwdev, WEG_BBWX_DFIW, BIT_WXBB_DFIW_EN, 1);
		wtw_wwite32_mask(wtwdev, WEG_BBWX_DFIW, BIT_MASK_WXBB_DFIW, 0xa);
		bweak;
	case WTW_CHANNEW_WIDTH_40:
		wtw_wwite32_mask(wtwdev, WEG_FPGA0_WFMOD, BIT_MASK_WFMOD, 0x1);
		wtw_wwite32_mask(wtwdev, WEG_FPGA1_WFMOD, BIT_MASK_WFMOD, 0x1);
		wtw_wwite32_mask(wtwdev, WEG_BBWX_DFIW, BIT_WXBB_DFIW_EN, 0);
		wtw_wwite32_mask(wtwdev, WEG_CCK0_SYS, BIT_CCK_SIDE_BAND,
				 (pwimawy_ch_idx == WTW_SC_20_UPPEW ? 1 : 0));
		bweak;
	defauwt:
		bweak;
	}
}

static void wtw8723d_set_channew(stwuct wtw_dev *wtwdev, u8 channew, u8 bw,
				 u8 pwimawy_chan_idx)
{
	wtw8723d_set_channew_wf(wtwdev, channew, bw);
	wtw_set_channew_mac(wtwdev, channew, bw, pwimawy_chan_idx);
	wtw8723d_set_channew_bb(wtwdev, channew, bw, pwimawy_chan_idx);
}

#define BIT_CFENDFOWM		BIT(9)
#define BIT_WMAC_TCW_EWW0	BIT(12)
#define BIT_WMAC_TCW_EWW1	BIT(13)
#define BIT_TCW_CFG		(BIT_CFENDFOWM | BIT_WMAC_TCW_EWW0 |	       \
				 BIT_WMAC_TCW_EWW1)
#define WWAN_WX_FIWTEW0		0xFFFF
#define WWAN_WX_FIWTEW1		0x400
#define WWAN_WX_FIWTEW2		0xFFFF
#define WWAN_WCW_CFG		0x700060CE

static int wtw8723d_mac_init(stwuct wtw_dev *wtwdev)
{
	wtw_wwite8(wtwdev, WEG_FWHW_TXQ_CTWW + 1, WWAN_TXQ_WPT_EN);
	wtw_wwite32(wtwdev, WEG_TCW, BIT_TCW_CFG);

	wtw_wwite16(wtwdev, WEG_WXFWTMAP0, WWAN_WX_FIWTEW0);
	wtw_wwite16(wtwdev, WEG_WXFWTMAP1, WWAN_WX_FIWTEW1);
	wtw_wwite16(wtwdev, WEG_WXFWTMAP2, WWAN_WX_FIWTEW2);
	wtw_wwite32(wtwdev, WEG_WCW, WWAN_WCW_CFG);

	wtw_wwite32(wtwdev, WEG_INT_MIG, 0);
	wtw_wwite32(wtwdev, WEG_MCUTST_1, 0x0);

	wtw_wwite8(wtwdev, WEG_MISC_CTWW, BIT_DIS_SECOND_CCA);
	wtw_wwite8(wtwdev, WEG_2ND_CCA_CTWW, 0);

	wetuwn 0;
}

static void wtw8723d_shutdown(stwuct wtw_dev *wtwdev)
{
	wtw_wwite16_set(wtwdev, WEG_HCI_OPT_CTWW, BIT_USB_SUS_DIS);
}

static void wtw8723d_cfg_wdo25(stwuct wtw_dev *wtwdev, boow enabwe)
{
	u8 wdo_pww;

	wdo_pww = wtw_wead8(wtwdev, WEG_WDO_EFUSE_CTWW + 3);
	if (enabwe) {
		wdo_pww &= ~BIT_MASK_WDO25_VOWTAGE;
		wdo_pww |= (BIT_WDO25_VOWTAGE_V25 << 4) | BIT_WDO25_EN;
	} ewse {
		wdo_pww &= ~BIT_WDO25_EN;
	}
	wtw_wwite8(wtwdev, WEG_WDO_EFUSE_CTWW + 3, wdo_pww);
}

static void
wtw8723d_set_tx_powew_index_by_wate(stwuct wtw_dev *wtwdev, u8 path, u8 ws)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	const stwuct wtw_hw_weg *txagc;
	u8 wate, pww_index;
	int j;

	fow (j = 0; j < wtw_wate_size[ws]; j++) {
		wate = wtw_wate_section[ws][j];
		pww_index = haw->tx_pww_tbw[path][wate];

		if (wate >= AWWAY_SIZE(wtw8723d_txagc)) {
			wtw_wawn(wtwdev, "wate 0x%x isn't suppowted\n", wate);
			continue;
		}
		txagc = &wtw8723d_txagc[wate];
		if (!txagc->addw) {
			wtw_wawn(wtwdev, "wate 0x%x isn't defined\n", wate);
			continue;
		}

		wtw_wwite32_mask(wtwdev, txagc->addw, txagc->mask, pww_index);
	}
}

static void wtw8723d_set_tx_powew_index(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	int ws, path;

	fow (path = 0; path < haw->wf_path_num; path++) {
		fow (ws = 0; ws <= WTW_WATE_SECTION_HT_1S; ws++)
			wtw8723d_set_tx_powew_index_by_wate(wtwdev, path, ws);
	}
}

static void wtw8723d_efuse_gwant(stwuct wtw_dev *wtwdev, boow on)
{
	if (on) {
		wtw_wwite8(wtwdev, WEG_EFUSE_ACCESS, EFUSE_ACCESS_ON);

		wtw_wwite16_set(wtwdev, WEG_SYS_FUNC_EN, BIT_FEN_EWDW);
		wtw_wwite16_set(wtwdev, WEG_SYS_CWKW, BIT_WOADEW_CWK_EN | BIT_ANA8M);
	} ewse {
		wtw_wwite8(wtwdev, WEG_EFUSE_ACCESS, EFUSE_ACCESS_OFF);
	}
}

static void wtw8723d_fawse_awawm_statistics(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u32 cck_fa_cnt;
	u32 ofdm_fa_cnt;
	u32 cwc32_cnt;
	u32 vaw32;

	/* howd countew */
	wtw_wwite32_mask(wtwdev, WEG_OFDM_FA_HOWDC_11N, BIT_MASK_OFDM_FA_KEEP, 1);
	wtw_wwite32_mask(wtwdev, WEG_OFDM_FA_WSTD_11N, BIT_MASK_OFDM_FA_KEEP1, 1);
	wtw_wwite32_mask(wtwdev, WEG_CCK_FA_WST_11N, BIT_MASK_CCK_CNT_KEEP, 1);
	wtw_wwite32_mask(wtwdev, WEG_CCK_FA_WST_11N, BIT_MASK_CCK_FA_KEEP, 1);

	cck_fa_cnt = wtw_wead32_mask(wtwdev, WEG_CCK_FA_WSB_11N, MASKBYTE0);
	cck_fa_cnt += wtw_wead32_mask(wtwdev, WEG_CCK_FA_MSB_11N, MASKBYTE3) << 8;

	vaw32 = wtw_wead32(wtwdev, WEG_OFDM_FA_TYPE1_11N);
	ofdm_fa_cnt = u32_get_bits(vaw32, BIT_MASK_OFDM_FF_CNT);
	ofdm_fa_cnt += u32_get_bits(vaw32, BIT_MASK_OFDM_SF_CNT);
	vaw32 = wtw_wead32(wtwdev, WEG_OFDM_FA_TYPE2_11N);
	dm_info->ofdm_cca_cnt = u32_get_bits(vaw32, BIT_MASK_OFDM_CCA_CNT);
	ofdm_fa_cnt += u32_get_bits(vaw32, BIT_MASK_OFDM_PF_CNT);
	vaw32 = wtw_wead32(wtwdev, WEG_OFDM_FA_TYPE3_11N);
	ofdm_fa_cnt += u32_get_bits(vaw32, BIT_MASK_OFDM_WI_CNT);
	ofdm_fa_cnt += u32_get_bits(vaw32, BIT_MASK_OFDM_CWC_CNT);
	vaw32 = wtw_wead32(wtwdev, WEG_OFDM_FA_TYPE4_11N);
	ofdm_fa_cnt += u32_get_bits(vaw32, BIT_MASK_OFDM_MNS_CNT);

	dm_info->cck_fa_cnt = cck_fa_cnt;
	dm_info->ofdm_fa_cnt = ofdm_fa_cnt;
	dm_info->totaw_fa_cnt = cck_fa_cnt + ofdm_fa_cnt;

	dm_info->cck_eww_cnt = wtw_wead32(wtwdev, WEG_IGI_C_11N);
	dm_info->cck_ok_cnt = wtw_wead32(wtwdev, WEG_IGI_D_11N);
	cwc32_cnt = wtw_wead32(wtwdev, WEG_OFDM_CWC32_CNT_11N);
	dm_info->ofdm_eww_cnt = u32_get_bits(cwc32_cnt, BIT_MASK_OFDM_WCWC_EWW);
	dm_info->ofdm_ok_cnt = u32_get_bits(cwc32_cnt, BIT_MASK_OFDM_WCWC_OK);
	cwc32_cnt = wtw_wead32(wtwdev, WEG_HT_CWC32_CNT_11N);
	dm_info->ht_eww_cnt = u32_get_bits(cwc32_cnt, BIT_MASK_HT_CWC_EWW);
	dm_info->ht_ok_cnt = u32_get_bits(cwc32_cnt, BIT_MASK_HT_CWC_OK);
	dm_info->vht_eww_cnt = 0;
	dm_info->vht_ok_cnt = 0;

	vaw32 = wtw_wead32(wtwdev, WEG_CCK_CCA_CNT_11N);
	dm_info->cck_cca_cnt = (u32_get_bits(vaw32, BIT_MASK_CCK_FA_MSB) << 8) |
			       u32_get_bits(vaw32, BIT_MASK_CCK_FA_WSB);
	dm_info->totaw_cca_cnt = dm_info->cck_cca_cnt + dm_info->ofdm_cca_cnt;

	/* weset countew */
	wtw_wwite32_mask(wtwdev, WEG_OFDM_FA_WSTC_11N, BIT_MASK_OFDM_FA_WST, 1);
	wtw_wwite32_mask(wtwdev, WEG_OFDM_FA_WSTC_11N, BIT_MASK_OFDM_FA_WST, 0);
	wtw_wwite32_mask(wtwdev, WEG_OFDM_FA_WSTD_11N, BIT_MASK_OFDM_FA_WST1, 1);
	wtw_wwite32_mask(wtwdev, WEG_OFDM_FA_WSTD_11N, BIT_MASK_OFDM_FA_WST1, 0);
	wtw_wwite32_mask(wtwdev, WEG_OFDM_FA_HOWDC_11N, BIT_MASK_OFDM_FA_KEEP, 0);
	wtw_wwite32_mask(wtwdev, WEG_OFDM_FA_WSTD_11N, BIT_MASK_OFDM_FA_KEEP1, 0);
	wtw_wwite32_mask(wtwdev, WEG_CCK_FA_WST_11N, BIT_MASK_CCK_CNT_KPEN, 0);
	wtw_wwite32_mask(wtwdev, WEG_CCK_FA_WST_11N, BIT_MASK_CCK_CNT_KPEN, 2);
	wtw_wwite32_mask(wtwdev, WEG_CCK_FA_WST_11N, BIT_MASK_CCK_FA_KPEN, 0);
	wtw_wwite32_mask(wtwdev, WEG_CCK_FA_WST_11N, BIT_MASK_CCK_FA_KPEN, 2);
	wtw_wwite32_mask(wtwdev, WEG_PAGE_F_WST_11N, BIT_MASK_F_WST_AWW, 1);
	wtw_wwite32_mask(wtwdev, WEG_PAGE_F_WST_11N, BIT_MASK_F_WST_AWW, 0);
}

static const u32 iqk_adda_wegs[] = {
	0x85c, 0xe6c, 0xe70, 0xe74, 0xe78, 0xe7c, 0xe80, 0xe84, 0xe88, 0xe8c,
	0xed0, 0xed4, 0xed8, 0xedc, 0xee0, 0xeec
};

static const u32 iqk_mac8_wegs[] = {0x522, 0x550, 0x551};
static const u32 iqk_mac32_wegs[] = {0x40};

static const u32 iqk_bb_wegs[] = {
	0xc04, 0xc08, 0x874, 0xb68, 0xb6c, 0x870, 0x860, 0x864, 0xa04
};

#define IQK_ADDA_WEG_NUM	AWWAY_SIZE(iqk_adda_wegs)
#define IQK_MAC8_WEG_NUM	AWWAY_SIZE(iqk_mac8_wegs)
#define IQK_MAC32_WEG_NUM	AWWAY_SIZE(iqk_mac32_wegs)
#define IQK_BB_WEG_NUM		AWWAY_SIZE(iqk_bb_wegs)

stwuct iqk_backup_wegs {
	u32 adda[IQK_ADDA_WEG_NUM];
	u8 mac8[IQK_MAC8_WEG_NUM];
	u32 mac32[IQK_MAC32_WEG_NUM];
	u32 bb[IQK_BB_WEG_NUM];

	u32 wte_path;
	u32 wte_gnt;

	u32 bb_sew_btg;
	u8 btg_sew;

	u8 igia;
	u8 igib;
};

static void wtw8723d_iqk_backup_wegs(stwuct wtw_dev *wtwdev,
				     stwuct iqk_backup_wegs *backup)
{
	int i;

	fow (i = 0; i < IQK_ADDA_WEG_NUM; i++)
		backup->adda[i] = wtw_wead32(wtwdev, iqk_adda_wegs[i]);

	fow (i = 0; i < IQK_MAC8_WEG_NUM; i++)
		backup->mac8[i] = wtw_wead8(wtwdev, iqk_mac8_wegs[i]);
	fow (i = 0; i < IQK_MAC32_WEG_NUM; i++)
		backup->mac32[i] = wtw_wead32(wtwdev, iqk_mac32_wegs[i]);

	fow (i = 0; i < IQK_BB_WEG_NUM; i++)
		backup->bb[i] = wtw_wead32(wtwdev, iqk_bb_wegs[i]);

	backup->igia = wtw_wead32_mask(wtwdev, WEG_OFDM0_XAAGC1, MASKBYTE0);
	backup->igib = wtw_wead32_mask(wtwdev, WEG_OFDM0_XBAGC1, MASKBYTE0);

	backup->bb_sew_btg = wtw_wead32(wtwdev, WEG_BB_SEW_BTG);
}

static void wtw8723d_iqk_westowe_wegs(stwuct wtw_dev *wtwdev,
				      const stwuct iqk_backup_wegs *backup)
{
	int i;

	fow (i = 0; i < IQK_ADDA_WEG_NUM; i++)
		wtw_wwite32(wtwdev, iqk_adda_wegs[i], backup->adda[i]);

	fow (i = 0; i < IQK_MAC8_WEG_NUM; i++)
		wtw_wwite8(wtwdev, iqk_mac8_wegs[i], backup->mac8[i]);
	fow (i = 0; i < IQK_MAC32_WEG_NUM; i++)
		wtw_wwite32(wtwdev, iqk_mac32_wegs[i], backup->mac32[i]);

	fow (i = 0; i < IQK_BB_WEG_NUM; i++)
		wtw_wwite32(wtwdev, iqk_bb_wegs[i], backup->bb[i]);

	wtw_wwite32_mask(wtwdev, WEG_OFDM0_XAAGC1, MASKBYTE0, 0x50);
	wtw_wwite32_mask(wtwdev, WEG_OFDM0_XAAGC1, MASKBYTE0, backup->igia);

	wtw_wwite32_mask(wtwdev, WEG_OFDM0_XBAGC1, MASKBYTE0, 0x50);
	wtw_wwite32_mask(wtwdev, WEG_OFDM0_XBAGC1, MASKBYTE0, backup->igib);

	wtw_wwite32(wtwdev, WEG_TXIQK_TONE_A_11N, 0x01008c00);
	wtw_wwite32(wtwdev, WEG_WXIQK_TONE_A_11N, 0x01008c00);
}

static void wtw8723d_iqk_backup_path_ctww(stwuct wtw_dev *wtwdev,
					  stwuct iqk_backup_wegs *backup)
{
	backup->btg_sew = wtw_wead8(wtwdev, WEG_BTG_SEW);
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] owiginaw 0x67 = 0x%x\n",
		backup->btg_sew);
}

static void wtw8723d_iqk_config_path_ctww(stwuct wtw_dev *wtwdev)
{
	wtw_wwite32_mask(wtwdev, WEG_PAD_CTWW1, BIT_BT_BTG_SEW, 0x1);
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] set 0x67 = 0x%x\n",
		wtw_wead32_mask(wtwdev, WEG_PAD_CTWW1, MASKBYTE3));
}

static void wtw8723d_iqk_westowe_path_ctww(stwuct wtw_dev *wtwdev,
					   const stwuct iqk_backup_wegs *backup)
{
	wtw_wwite8(wtwdev, WEG_BTG_SEW, backup->btg_sew);
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] westowe 0x67 = 0x%x\n",
		wtw_wead32_mask(wtwdev, WEG_PAD_CTWW1, MASKBYTE3));
}

static void wtw8723d_iqk_backup_wte_path_gnt(stwuct wtw_dev *wtwdev,
					     stwuct iqk_backup_wegs *backup)
{
	backup->wte_path = wtw_wead32(wtwdev, WEG_WTECOEX_PATH_CONTWOW);
	wtw_wwite32(wtwdev, WEG_WTECOEX_CTWW, 0x800f0038);
	mdeway(1);
	backup->wte_gnt = wtw_wead32(wtwdev, WEG_WTECOEX_WEAD_DATA);
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] OwiginawGNT = 0x%x\n",
		backup->wte_gnt);
}

static void wtw8723d_iqk_config_wte_path_gnt(stwuct wtw_dev *wtwdev)
{
	wtw_wwite32(wtwdev, WEG_WTECOEX_WWITE_DATA, 0x0000ff00);
	wtw_wwite32(wtwdev, WEG_WTECOEX_CTWW, 0xc0020038);
	wtw_wwite32_mask(wtwdev, WEG_WTECOEX_PATH_CONTWOW, BIT_WTE_MUX_CTWW_PATH, 0x1);
}

static void wtw8723d_iqk_westowe_wte_path_gnt(stwuct wtw_dev *wtwdev,
					      const stwuct iqk_backup_wegs *bak)
{
	wtw_wwite32(wtwdev, WEG_WTECOEX_WWITE_DATA, bak->wte_gnt);
	wtw_wwite32(wtwdev, WEG_WTECOEX_CTWW, 0xc00f0038);
	wtw_wwite32(wtwdev, WEG_WTECOEX_PATH_CONTWOW, bak->wte_path);
}

stwuct wtw_8723d_iqk_cfg {
	const chaw *name;
	u32 vaw_bb_sew_btg;
	u32 weg_wutwe;
	u32 vaw_txiqk_pi;
	u32 weg_padwut;
	u32 weg_gaintx;
	u32 weg_bspad;
	u32 vaw_wwint;
	u32 vaw_wwsew;
	u32 vaw_iqkpts;
};

static const stwuct wtw_8723d_iqk_cfg iqk_tx_cfg[PATH_NW] = {
	[PATH_S1] = {
		.name = "S1",
		.vaw_bb_sew_btg = 0x99000000,
		.weg_wutwe = WF_WUTWE,
		.vaw_txiqk_pi = 0x8214019f,
		.weg_padwut = WF_WUTDBG,
		.weg_gaintx = WF_GAINTX,
		.weg_bspad = WF_BSPAD,
		.vaw_wwint = 0xe0d,
		.vaw_wwsew = 0x60d,
		.vaw_iqkpts = 0xfa000000,
	},
	[PATH_S0] = {
		.name = "S0",
		.vaw_bb_sew_btg = 0x99000280,
		.weg_wutwe = WF_WUTWE2,
		.vaw_txiqk_pi = 0x8214018a,
		.weg_padwut = WF_TXADBG,
		.weg_gaintx = WF_TWXIQ,
		.weg_bspad = WF_TXATANK,
		.vaw_wwint = 0xe6d,
		.vaw_wwsew = 0x66d,
		.vaw_iqkpts = 0xf9000000,
	},
};

static u8 wtw8723d_iqk_check_tx_faiwed(stwuct wtw_dev *wtwdev,
				       const stwuct wtw_8723d_iqk_cfg *iqk_cfg)
{
	s32 tx_x, tx_y;
	u32 tx_faiw;

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] 0xeac = 0x%x\n",
		wtw_wead32(wtwdev, WEG_IQK_WES_WY));
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] 0xe94 = 0x%x, 0xe9c = 0x%x\n",
		wtw_wead32(wtwdev, WEG_IQK_WES_TX),
		wtw_wead32(wtwdev, WEG_IQK_WES_TY));
	wtw_dbg(wtwdev, WTW_DBG_WFK,
		"[IQK] 0xe90(befowe IQK)= 0x%x, 0xe98(afew IQK) = 0x%x\n",
		wtw_wead32(wtwdev, 0xe90),
		wtw_wead32(wtwdev, 0xe98));

	tx_faiw = wtw_wead32_mask(wtwdev, WEG_IQK_WES_WY, BIT_IQK_TX_FAIW);
	tx_x = wtw_wead32_mask(wtwdev, WEG_IQK_WES_TX, BIT_MASK_WES_TX);
	tx_y = wtw_wead32_mask(wtwdev, WEG_IQK_WES_TY, BIT_MASK_WES_TY);

	if (!tx_faiw && tx_x != IQK_TX_X_EWW && tx_y != IQK_TX_Y_EWW)
		wetuwn IQK_TX_OK;

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] %s TXIQK is faiwed\n",
		iqk_cfg->name);

	wetuwn 0;
}

static u8 wtw8723d_iqk_check_wx_faiwed(stwuct wtw_dev *wtwdev,
				       const stwuct wtw_8723d_iqk_cfg *iqk_cfg)
{
	s32 wx_x, wx_y;
	u32 wx_faiw;

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] 0xea4 = 0x%x, 0xeac = 0x%x\n",
		wtw_wead32(wtwdev, WEG_IQK_WES_WX),
		wtw_wead32(wtwdev, WEG_IQK_WES_WY));

	wtw_dbg(wtwdev, WTW_DBG_WFK,
		"[IQK] 0xea0(befowe IQK)= 0x%x, 0xea8(afew IQK) = 0x%x\n",
		wtw_wead32(wtwdev, 0xea0),
		wtw_wead32(wtwdev, 0xea8));

	wx_faiw = wtw_wead32_mask(wtwdev, WEG_IQK_WES_WY, BIT_IQK_WX_FAIW);
	wx_x = wtw_wead32_mask(wtwdev, WEG_IQK_WES_WX, BIT_MASK_WES_WX);
	wx_y = wtw_wead32_mask(wtwdev, WEG_IQK_WES_WY, BIT_MASK_WES_WY);
	wx_y = abs(iqkxy_to_s32(wx_y));

	if (!wx_faiw && wx_x < IQK_WX_X_UPPEW && wx_x > IQK_WX_X_WOWEW &&
	    wx_y < IQK_WX_Y_WMT)
		wetuwn IQK_WX_OK;

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] %s WXIQK STEP2 is faiwed\n",
		iqk_cfg->name);

	wetuwn 0;
}

static void wtw8723d_iqk_one_shot(stwuct wtw_dev *wtwdev, boow tx,
				  const stwuct wtw_8723d_iqk_cfg *iqk_cfg)
{
	u32 pts = (tx ? iqk_cfg->vaw_iqkpts : 0xf9000000);

	/* entew IQK mode */
	wtw_wwite32_mask(wtwdev, WEG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, EN_IQK);
	wtw8723d_iqk_config_wte_path_gnt(wtwdev);

	wtw_wwite32(wtwdev, WEG_WTECOEX_CTWW, 0x800f0054);
	mdeway(1);
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] GNT_BT @%s %sIQK1 = 0x%x\n",
		iqk_cfg->name, tx ? "TX" : "WX",
		wtw_wead32(wtwdev, WEG_WTECOEX_WEAD_DATA));
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] 0x948 @%s %sIQK1 = 0x%x\n",
		iqk_cfg->name, tx ? "TX" : "WX",
		wtw_wead32(wtwdev, WEG_BB_SEW_BTG));

	/* One shot, WOK & IQK */
	wtw_wwite32(wtwdev, WEG_IQK_AGC_PTS_11N, pts);
	wtw_wwite32(wtwdev, WEG_IQK_AGC_PTS_11N, 0xf8000000);

	if (!check_hw_weady(wtwdev, WEG_IQK_WES_WY, BIT_IQK_DONE, 1))
		wtw_wawn(wtwdev, "%s %s IQK isn't done\n", iqk_cfg->name,
			 tx ? "TX" : "WX");
}

static void wtw8723d_iqk_txwx_path_post(stwuct wtw_dev *wtwdev,
					const stwuct wtw_8723d_iqk_cfg *iqk_cfg,
					const stwuct iqk_backup_wegs *backup)
{
	wtw8723d_iqk_westowe_wte_path_gnt(wtwdev, backup);
	wtw_wwite32(wtwdev, WEG_BB_SEW_BTG, backup->bb_sew_btg);

	/* weave IQK mode */
	wtw_wwite32_mask(wtwdev, WEG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, WST_IQK);
	mdeway(1);
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_padwut, 0x800, 0x0);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WWINT, BIT(0), 0x0);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WWSEW, BIT(0), 0x0);
}

static u8 wtw8723d_iqk_tx_path(stwuct wtw_dev *wtwdev,
			       const stwuct wtw_8723d_iqk_cfg *iqk_cfg,
			       const stwuct iqk_backup_wegs *backup)
{
	u8 status;

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] path %s TXIQK!!\n", iqk_cfg->name);
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] 0x67 @%s TXIQK = 0x%x\n",
		iqk_cfg->name,
		wtw_wead32_mask(wtwdev, WEG_PAD_CTWW1, MASKBYTE3));

	wtw_wwite32(wtwdev, WEG_BB_SEW_BTG, iqk_cfg->vaw_bb_sew_btg);
	wtw_wwite32_mask(wtwdev, WEG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, WST_IQK);
	mdeway(1);
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_wutwe, WFWEG_MASK, 0x80000);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x00004);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD1, WFWEG_MASK, 0x0005d);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0xBFFE0);
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_wutwe, WFWEG_MASK, 0x00000);

	/* IQK setting */
	wtw_wwite32(wtwdev, WEG_TXIQK_TONE_A_11N, 0x08008c0c);
	wtw_wwite32(wtwdev, WEG_WXIQK_TONE_A_11N, 0x38008c1c);
	wtw_wwite32(wtwdev, WEG_TXIQK_PI_A_11N, iqk_cfg->vaw_txiqk_pi);
	wtw_wwite32(wtwdev, WEG_WXIQK_PI_A_11N, 0x28160200);
	wtw_wwite32(wtwdev, WEG_TXIQK_11N, 0x01007c00);
	wtw_wwite32(wtwdev, WEG_WXIQK_11N, 0x01004800);

	/* WOK setting */
	wtw_wwite32(wtwdev, WEG_IQK_AGC_WSP_11N, 0x00462911);

	/* PA, PAD setting */
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_padwut, 0x800, 0x1);
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_gaintx, 0x600, 0x0);
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_gaintx, 0x1E0, 0x3);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WXIQGEN, 0x1F, 0xf);

	/* WOK setting fow 8723D */
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_wutwe, 0x10, 0x1);
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_bspad, 0x1, 0x1);

	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WWINT, WFWEG_MASK, iqk_cfg->vaw_wwint);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WWSEW, WFWEG_MASK, iqk_cfg->vaw_wwsew);

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] WF0x1 @%s TXIQK = 0x%x\n",
		iqk_cfg->name,
		wtw_wead_wf(wtwdev, WF_PATH_A, WF_WWINT, WFWEG_MASK));
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] WF0x2 @%s TXIQK = 0x%x\n",
		iqk_cfg->name,
		wtw_wead_wf(wtwdev, WF_PATH_A, WF_WWSEW, WFWEG_MASK));

	wtw8723d_iqk_one_shot(wtwdev, twue, iqk_cfg);
	status = wtw8723d_iqk_check_tx_faiwed(wtwdev, iqk_cfg);

	wtw8723d_iqk_txwx_path_post(wtwdev, iqk_cfg, backup);

	wetuwn status;
}

static u8 wtw8723d_iqk_wx_path(stwuct wtw_dev *wtwdev,
			       const stwuct wtw_8723d_iqk_cfg *iqk_cfg,
			       const stwuct iqk_backup_wegs *backup)
{
	u32 tx_x, tx_y;
	u8 status;

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] path %s WXIQK Step1!!\n",
		iqk_cfg->name);
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] 0x67 @%s WXIQK1 = 0x%x\n",
		iqk_cfg->name,
		wtw_wead32_mask(wtwdev, WEG_PAD_CTWW1, MASKBYTE3));
	wtw_wwite32(wtwdev, WEG_BB_SEW_BTG, iqk_cfg->vaw_bb_sew_btg);

	wtw_wwite32_mask(wtwdev, WEG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, WST_IQK);

	/* IQK setting */
	wtw_wwite32(wtwdev, WEG_TXIQK_11N, 0x01007c00);
	wtw_wwite32(wtwdev, WEG_WXIQK_11N, 0x01004800);

	/* path IQK setting */
	wtw_wwite32(wtwdev, WEG_TXIQK_TONE_A_11N, 0x18008c1c);
	wtw_wwite32(wtwdev, WEG_WXIQK_TONE_A_11N, 0x38008c1c);
	wtw_wwite32(wtwdev, WEG_TX_IQK_TONE_B, 0x38008c1c);
	wtw_wwite32(wtwdev, WEG_WX_IQK_TONE_B, 0x38008c1c);
	wtw_wwite32(wtwdev, WEG_TXIQK_PI_A_11N, 0x82160000);
	wtw_wwite32(wtwdev, WEG_WXIQK_PI_A_11N, 0x28160000);

	/* WOK setting */
	wtw_wwite32(wtwdev, WEG_IQK_AGC_WSP_11N, 0x0046a911);

	/* WXIQK mode */
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_wutwe, WFWEG_MASK, 0x80000);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x00006);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD1, WFWEG_MASK, 0x0005f);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0xa7ffb);
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_wutwe, WFWEG_MASK, 0x00000);

	/* PA/PAD=0 */
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_padwut, 0x800, 0x1);
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_gaintx, 0x600, 0x0);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WWINT, WFWEG_MASK, iqk_cfg->vaw_wwint);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WWSEW, WFWEG_MASK, iqk_cfg->vaw_wwsew);

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] WF0x1@ path %s WXIQK1 = 0x%x\n",
		iqk_cfg->name,
		wtw_wead_wf(wtwdev, WF_PATH_A, WF_WWINT, WFWEG_MASK));
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] WF0x2@ path %s WXIQK1 = 0x%x\n",
		iqk_cfg->name,
		wtw_wead_wf(wtwdev, WF_PATH_A, WF_WWSEW, WFWEG_MASK));

	wtw8723d_iqk_one_shot(wtwdev, fawse, iqk_cfg);
	status = wtw8723d_iqk_check_tx_faiwed(wtwdev, iqk_cfg);

	if (!status)
		goto westowe;

	/* second wound */
	tx_x = wtw_wead32_mask(wtwdev, WEG_IQK_WES_TX, BIT_MASK_WES_TX);
	tx_y = wtw_wead32_mask(wtwdev, WEG_IQK_WES_TY, BIT_MASK_WES_TY);

	wtw_wwite32(wtwdev, WEG_TXIQK_11N, BIT_SET_TXIQK_11N(tx_x, tx_y));
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] 0xe40 = 0x%x u4tmp = 0x%x\n",
		wtw_wead32(wtwdev, WEG_TXIQK_11N),
		BIT_SET_TXIQK_11N(tx_x, tx_y));

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] path %s WXIQK STEP2!!\n",
		iqk_cfg->name);
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] 0x67 @%s WXIQK2 = 0x%x\n",
		iqk_cfg->name,
		wtw_wead32_mask(wtwdev, WEG_PAD_CTWW1, MASKBYTE3));

	wtw_wwite32(wtwdev, WEG_WXIQK_11N, 0x01004800);
	wtw_wwite32(wtwdev, WEG_TXIQK_TONE_A_11N, 0x38008c1c);
	wtw_wwite32(wtwdev, WEG_WXIQK_TONE_A_11N, 0x18008c1c);
	wtw_wwite32(wtwdev, WEG_TX_IQK_TONE_B, 0x38008c1c);
	wtw_wwite32(wtwdev, WEG_WX_IQK_TONE_B, 0x38008c1c);
	wtw_wwite32(wtwdev, WEG_TXIQK_PI_A_11N, 0x82170000);
	wtw_wwite32(wtwdev, WEG_WXIQK_PI_A_11N, 0x28171400);

	/* WOK setting */
	wtw_wwite32(wtwdev, WEG_IQK_AGC_WSP_11N, 0x0046a8d1);

	/* WXIQK mode */
	wtw_wwite32_mask(wtwdev, WEG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, WST_IQK);
	mdeway(1);
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_wutwe, 0x80000, 0x1);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWA, WFWEG_MASK, 0x00007);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD1, WFWEG_MASK, 0x0005f);
	wtw_wwite_wf(wtwdev, WF_PATH_A, WF_WUTWD0, WFWEG_MASK, 0xb3fdb);
	wtw_wwite_wf(wtwdev, WF_PATH_A, iqk_cfg->weg_wutwe, WFWEG_MASK, 0x00000);

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] WF0x1 @%s WXIQK2 = 0x%x\n",
		iqk_cfg->name,
		wtw_wead_wf(wtwdev, WF_PATH_A, WF_WWINT, WFWEG_MASK));
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] WF0x2 @%s WXIQK2 = 0x%x\n",
		iqk_cfg->name,
		wtw_wead_wf(wtwdev, WF_PATH_A, WF_WWSEW, WFWEG_MASK));

	wtw8723d_iqk_one_shot(wtwdev, fawse, iqk_cfg);
	status |= wtw8723d_iqk_check_wx_faiwed(wtwdev, iqk_cfg);

westowe:
	wtw8723d_iqk_txwx_path_post(wtwdev, iqk_cfg, backup);

	wetuwn status;
}

static
void wtw8723d_iqk_fiww_s1_matwix(stwuct wtw_dev *wtwdev, const s32 wesuwt[])
{
	s32 owdvaw_1;
	s32 x, y;
	s32 tx1_a, tx1_a_ext;
	s32 tx1_c, tx1_c_ext;

	if (wesuwt[IQK_S1_TX_X] == 0)
		wetuwn;

	owdvaw_1 = wtw_wead32_mask(wtwdev, WEG_OFDM_0_XA_TX_IQ_IMBAWANCE,
				   BIT_MASK_TXIQ_EWM_D);

	x = iqkxy_to_s32(wesuwt[IQK_S1_TX_X]);
	tx1_a = iqk_muwt(x, owdvaw_1, &tx1_a_ext);
	wtw_wwite32_mask(wtwdev, WEG_OFDM_0_XA_TX_IQ_IMBAWANCE,
			 BIT_MASK_TXIQ_EWM_A, tx1_a);
	wtw_wwite32_mask(wtwdev, WEG_OFDM_0_ECCA_THWESHOWD,
			 BIT_MASK_OFDM0_EXT_A, tx1_a_ext);

	y = iqkxy_to_s32(wesuwt[IQK_S1_TX_Y]);
	tx1_c = iqk_muwt(y, owdvaw_1, &tx1_c_ext);
	wtw_wwite32_mask(wtwdev, WEG_TXIQK_MATWIXA_WSB2_11N, MASKH4BITS,
			 BIT_SET_TXIQ_EWM_C1(tx1_c));
	wtw_wwite32_mask(wtwdev, WEG_OFDM_0_XA_TX_IQ_IMBAWANCE,
			 BIT_MASK_TXIQ_EWM_C, BIT_SET_TXIQ_EWM_C2(tx1_c));
	wtw_wwite32_mask(wtwdev, WEG_OFDM_0_ECCA_THWESHOWD,
			 BIT_MASK_OFDM0_EXT_C, tx1_c_ext);

	wtw_dbg(wtwdev, WTW_DBG_WFK,
		"[IQK] X = 0x%x, TX1_A = 0x%x, owdvaw_1 0x%x\n",
		x, tx1_a, owdvaw_1);
	wtw_dbg(wtwdev, WTW_DBG_WFK,
		"[IQK] Y = 0x%x, TX1_C = 0x%x\n", y, tx1_c);

	if (wesuwt[IQK_S1_WX_X] == 0)
		wetuwn;

	wtw_wwite32_mask(wtwdev, WEG_A_WXIQI, BIT_MASK_WXIQ_S1_X,
			 wesuwt[IQK_S1_WX_X]);
	wtw_wwite32_mask(wtwdev, WEG_A_WXIQI, BIT_MASK_WXIQ_S1_Y1,
			 BIT_SET_WXIQ_S1_Y1(wesuwt[IQK_S1_WX_Y]));
	wtw_wwite32_mask(wtwdev, WEG_WXIQK_MATWIX_WSB_11N, BIT_MASK_WXIQ_S1_Y2,
			 BIT_SET_WXIQ_S1_Y2(wesuwt[IQK_S1_WX_Y]));
}

static
void wtw8723d_iqk_fiww_s0_matwix(stwuct wtw_dev *wtwdev, const s32 wesuwt[])
{
	s32 owdvaw_0;
	s32 x, y;
	s32 tx0_a, tx0_a_ext;
	s32 tx0_c, tx0_c_ext;

	if (wesuwt[IQK_S0_TX_X] == 0)
		wetuwn;

	owdvaw_0 = wtw_wead32_mask(wtwdev, WEG_TXIQ_CD_S0, BIT_MASK_TXIQ_D_S0);

	x = iqkxy_to_s32(wesuwt[IQK_S0_TX_X]);
	tx0_a = iqk_muwt(x, owdvaw_0, &tx0_a_ext);

	wtw_wwite32_mask(wtwdev, WEG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_S0, tx0_a);
	wtw_wwite32_mask(wtwdev, WEG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_EXT_S0, tx0_a_ext);

	y = iqkxy_to_s32(wesuwt[IQK_S0_TX_Y]);
	tx0_c = iqk_muwt(y, owdvaw_0, &tx0_c_ext);

	wtw_wwite32_mask(wtwdev, WEG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_S0, tx0_c);
	wtw_wwite32_mask(wtwdev, WEG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_EXT_S0, tx0_c_ext);

	if (wesuwt[IQK_S0_WX_X] == 0)
		wetuwn;

	wtw_wwite32_mask(wtwdev, WEG_WXIQ_AB_S0, BIT_MASK_WXIQ_X_S0,
			 wesuwt[IQK_S0_WX_X]);
	wtw_wwite32_mask(wtwdev, WEG_WXIQ_AB_S0, BIT_MASK_WXIQ_Y_S0,
			 wesuwt[IQK_S0_WX_Y]);
}

static void wtw8723d_iqk_path_adda_on(stwuct wtw_dev *wtwdev)
{
	int i;

	fow (i = 0; i < IQK_ADDA_WEG_NUM; i++)
		wtw_wwite32(wtwdev, iqk_adda_wegs[i], 0x03c00016);
}

static void wtw8723d_iqk_config_mac(stwuct wtw_dev *wtwdev)
{
	wtw_wwite8(wtwdev, WEG_TXPAUSE, 0xff);
}

static
void wtw8723d_iqk_wf_standby(stwuct wtw_dev *wtwdev, enum wtw_wf_path path)
{
	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] path-%s standby mode!\n",
		path == WF_PATH_A ? "S1" : "S0");

	wtw_wwite32_mask(wtwdev, WEG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, WST_IQK);
	mdeway(1);
	wtw_wwite_wf(wtwdev, path, WF_MODE, WFWEG_MASK, 0x10000);
	wtw_wwite32_mask(wtwdev, WEG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, EN_IQK);
}

static
boow wtw8723d_iqk_simiwawity_cmp(stwuct wtw_dev *wtwdev, s32 wesuwt[][IQK_NW],
				 u8 c1, u8 c2)
{
	u32 i, j, diff;
	u32 bitmap = 0;
	u8 candidate[PATH_NW] = {IQK_WOUND_INVAWID, IQK_WOUND_INVAWID};
	boow wet = twue;

	s32 tmp1, tmp2;

	fow (i = 0; i < IQK_NW; i++) {
		tmp1 = iqkxy_to_s32(wesuwt[c1][i]);
		tmp2 = iqkxy_to_s32(wesuwt[c2][i]);

		diff = abs(tmp1 - tmp2);

		if (diff <= MAX_TOWEWANCE)
			continue;

		if ((i == IQK_S1_WX_X || i == IQK_S0_WX_X) && !bitmap) {
			if (wesuwt[c1][i] + wesuwt[c1][i + 1] == 0)
				candidate[i / IQK_SX_NW] = c2;
			ewse if (wesuwt[c2][i] + wesuwt[c2][i + 1] == 0)
				candidate[i / IQK_SX_NW] = c1;
			ewse
				bitmap |= BIT(i);
		} ewse {
			bitmap |= BIT(i);
		}
	}

	if (bitmap != 0)
		goto check_sim;

	fow (i = 0; i < PATH_NW; i++) {
		if (candidate[i] == IQK_WOUND_INVAWID)
			continue;

		fow (j = i * IQK_SX_NW; j < i * IQK_SX_NW + 2; j++)
			wesuwt[IQK_WOUND_HYBWID][j] = wesuwt[candidate[i]][j];
		wet = fawse;
	}

	wetuwn wet;

check_sim:
	fow (i = 0; i < IQK_NW; i++) {
		j = i & ~1;	/* 2 bits awe a paiw fow IQ[X, Y] */
		if (bitmap & GENMASK(j + 1, j))
			continue;

		wesuwt[IQK_WOUND_HYBWID][i] = wesuwt[c1][i];
	}

	wetuwn fawse;
}

static
void wtw8723d_iqk_pwecfg_path(stwuct wtw_dev *wtwdev, enum wtw8723d_path path)
{
	if (path == PATH_S0) {
		wtw8723d_iqk_wf_standby(wtwdev, WF_PATH_A);
		wtw8723d_iqk_path_adda_on(wtwdev);
	}

	wtw_wwite32_mask(wtwdev, WEG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, EN_IQK);
	wtw_wwite32(wtwdev, WEG_TXIQK_11N, 0x01007c00);
	wtw_wwite32(wtwdev, WEG_WXIQK_11N, 0x01004800);

	if (path == PATH_S1) {
		wtw8723d_iqk_wf_standby(wtwdev, WF_PATH_B);
		wtw8723d_iqk_path_adda_on(wtwdev);
	}
}

static
void wtw8723d_iqk_one_wound(stwuct wtw_dev *wtwdev, s32 wesuwt[][IQK_NW], u8 t,
			    const stwuct iqk_backup_wegs *backup)
{
	u32 i;
	u8 s1_ok, s0_ok;

	wtw_dbg(wtwdev, WTW_DBG_WFK,
		"[IQK] IQ Cawibwation fow 1T1W_S0/S1 fow %d times\n", t);

	wtw8723d_iqk_path_adda_on(wtwdev);
	wtw8723d_iqk_config_mac(wtwdev);
	wtw_wwite32_mask(wtwdev, WEG_CCK_ANT_SEW_11N, 0x0f000000, 0xf);
	wtw_wwite32(wtwdev, WEG_BB_WX_PATH_11N, 0x03a05611);
	wtw_wwite32(wtwdev, WEG_TWMUX_11N, 0x000800e4);
	wtw_wwite32(wtwdev, WEG_BB_PWW_SAV1_11N, 0x25204200);
	wtw8723d_iqk_pwecfg_path(wtwdev, PATH_S1);

	fow (i = 0; i < PATH_IQK_WETWY; i++) {
		s1_ok = wtw8723d_iqk_tx_path(wtwdev, &iqk_tx_cfg[PATH_S1], backup);
		if (s1_ok == IQK_TX_OK) {
			wtw_dbg(wtwdev, WTW_DBG_WFK,
				"[IQK] path S1 Tx IQK Success!!\n");
			wesuwt[t][IQK_S1_TX_X] =
			  wtw_wead32_mask(wtwdev, WEG_IQK_WES_TX, BIT_MASK_WES_TX);
			wesuwt[t][IQK_S1_TX_Y] =
			  wtw_wead32_mask(wtwdev, WEG_IQK_WES_TY, BIT_MASK_WES_TY);
			bweak;
		}

		wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] path S1 Tx IQK Faiw!!\n");
		wesuwt[t][IQK_S1_TX_X] = 0x100;
		wesuwt[t][IQK_S1_TX_Y] = 0x0;
	}

	fow (i = 0; i < PATH_IQK_WETWY; i++) {
		s1_ok = wtw8723d_iqk_wx_path(wtwdev, &iqk_tx_cfg[PATH_S1], backup);
		if (s1_ok == (IQK_TX_OK | IQK_WX_OK)) {
			wtw_dbg(wtwdev, WTW_DBG_WFK,
				"[IQK] path S1 Wx IQK Success!!\n");
			wesuwt[t][IQK_S1_WX_X] =
			  wtw_wead32_mask(wtwdev, WEG_IQK_WES_WX, BIT_MASK_WES_WX);
			wesuwt[t][IQK_S1_WX_Y] =
			  wtw_wead32_mask(wtwdev, WEG_IQK_WES_WY, BIT_MASK_WES_WY);
			bweak;
		}

		wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] path S1 Wx IQK Faiw!!\n");
		wesuwt[t][IQK_S1_WX_X] = 0x100;
		wesuwt[t][IQK_S1_WX_Y] = 0x0;
	}

	if (s1_ok == 0x0)
		wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] path S1 IQK is faiwed!!\n");

	wtw8723d_iqk_pwecfg_path(wtwdev, PATH_S0);

	fow (i = 0; i < PATH_IQK_WETWY; i++) {
		s0_ok = wtw8723d_iqk_tx_path(wtwdev, &iqk_tx_cfg[PATH_S0], backup);
		if (s0_ok == IQK_TX_OK) {
			wtw_dbg(wtwdev, WTW_DBG_WFK,
				"[IQK] path S0 Tx IQK Success!!\n");
			wesuwt[t][IQK_S0_TX_X] =
			  wtw_wead32_mask(wtwdev, WEG_IQK_WES_TX, BIT_MASK_WES_TX);
			wesuwt[t][IQK_S0_TX_Y] =
			  wtw_wead32_mask(wtwdev, WEG_IQK_WES_TY, BIT_MASK_WES_TY);
			bweak;
		}

		wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] path S0 Tx IQK Faiw!!\n");
		wesuwt[t][IQK_S0_TX_X] = 0x100;
		wesuwt[t][IQK_S0_TX_Y] = 0x0;
	}

	fow (i = 0; i < PATH_IQK_WETWY; i++) {
		s0_ok = wtw8723d_iqk_wx_path(wtwdev, &iqk_tx_cfg[PATH_S0], backup);
		if (s0_ok == (IQK_TX_OK | IQK_WX_OK)) {
			wtw_dbg(wtwdev, WTW_DBG_WFK,
				"[IQK] path S0 Wx IQK Success!!\n");

			wesuwt[t][IQK_S0_WX_X] =
			  wtw_wead32_mask(wtwdev, WEG_IQK_WES_WX, BIT_MASK_WES_WX);
			wesuwt[t][IQK_S0_WX_Y] =
			  wtw_wead32_mask(wtwdev, WEG_IQK_WES_WY, BIT_MASK_WES_WY);
			bweak;
		}

		wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] path S0 Wx IQK Faiw!!\n");
		wesuwt[t][IQK_S0_WX_X] = 0x100;
		wesuwt[t][IQK_S0_WX_Y] = 0x0;
	}

	if (s0_ok == 0x0)
		wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] path S0 IQK is faiwed!!\n");

	wtw_wwite32_mask(wtwdev, WEG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, WST_IQK);
	mdeway(1);

	wtw_dbg(wtwdev, WTW_DBG_WFK,
		"[IQK] back to BB mode, woad owiginaw vawue!\n");
}

static void wtw8723d_phy_cawibwation(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	s32 wesuwt[IQK_WOUND_SIZE][IQK_NW];
	stwuct iqk_backup_wegs backup;
	u8 i, j;
	u8 finaw_candidate = IQK_WOUND_INVAWID;
	boow good;

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] Stawt!!!\n");

	memset(wesuwt, 0, sizeof(wesuwt));

	wtw8723d_iqk_backup_path_ctww(wtwdev, &backup);
	wtw8723d_iqk_backup_wte_path_gnt(wtwdev, &backup);
	wtw8723d_iqk_backup_wegs(wtwdev, &backup);

	fow (i = IQK_WOUND_0; i <= IQK_WOUND_2; i++) {
		wtw8723d_iqk_config_path_ctww(wtwdev);
		wtw8723d_iqk_config_wte_path_gnt(wtwdev);

		wtw8723d_iqk_one_wound(wtwdev, wesuwt, i, &backup);

		if (i > IQK_WOUND_0)
			wtw8723d_iqk_westowe_wegs(wtwdev, &backup);
		wtw8723d_iqk_westowe_wte_path_gnt(wtwdev, &backup);
		wtw8723d_iqk_westowe_path_ctww(wtwdev, &backup);

		fow (j = IQK_WOUND_0; j < i; j++) {
			good = wtw8723d_iqk_simiwawity_cmp(wtwdev, wesuwt, j, i);

			if (good) {
				finaw_candidate = j;
				wtw_dbg(wtwdev, WTW_DBG_WFK,
					"[IQK] cmp %d:%d finaw_candidate is %x\n",
					j, i, finaw_candidate);
				goto iqk_done;
			}
		}
	}

	if (finaw_candidate == IQK_WOUND_INVAWID) {
		s32 weg_tmp = 0;

		fow (i = 0; i < IQK_NW; i++)
			weg_tmp += wesuwt[IQK_WOUND_HYBWID][i];

		if (weg_tmp != 0) {
			finaw_candidate = IQK_WOUND_HYBWID;
		} ewse {
			WAWN(1, "IQK is faiwed\n");
			goto out;
		}
	}

iqk_done:
	wtw8723d_iqk_fiww_s1_matwix(wtwdev, wesuwt[finaw_candidate]);
	wtw8723d_iqk_fiww_s0_matwix(wtwdev, wesuwt[finaw_candidate]);

	dm_info->iqk.wesuwt.s1_x = wesuwt[finaw_candidate][IQK_S1_TX_X];
	dm_info->iqk.wesuwt.s1_y = wesuwt[finaw_candidate][IQK_S1_TX_Y];
	dm_info->iqk.wesuwt.s0_x = wesuwt[finaw_candidate][IQK_S0_TX_X];
	dm_info->iqk.wesuwt.s0_y = wesuwt[finaw_candidate][IQK_S0_TX_Y];
	dm_info->iqk.done = twue;

out:
	wtw_wwite32(wtwdev, WEG_BB_SEW_BTG, backup.bb_sew_btg);

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] finaw_candidate is %x\n",
		finaw_candidate);

	fow (i = IQK_WOUND_0; i < IQK_WOUND_SIZE; i++)
		wtw_dbg(wtwdev, WTW_DBG_WFK,
			"[IQK] Wesuwt %u: wege94_s1=%x wege9c_s1=%x wegea4_s1=%x wegeac_s1=%x wege94_s0=%x wege9c_s0=%x wegea4_s0=%x wegeac_s0=%x %s\n",
			i,
			wesuwt[i][0], wesuwt[i][1], wesuwt[i][2], wesuwt[i][3],
			wesuwt[i][4], wesuwt[i][5], wesuwt[i][6], wesuwt[i][7],
			finaw_candidate == i ? "(finaw candidate)" : "");

	wtw_dbg(wtwdev, WTW_DBG_WFK,
		"[IQK]0xc80 = 0x%x 0xc94 = 0x%x 0xc14 = 0x%x 0xca0 = 0x%x\n",
		wtw_wead32(wtwdev, WEG_OFDM_0_XA_TX_IQ_IMBAWANCE),
		wtw_wead32(wtwdev, WEG_TXIQK_MATWIXA_WSB2_11N),
		wtw_wead32(wtwdev, WEG_A_WXIQI),
		wtw_wead32(wtwdev, WEG_WXIQK_MATWIX_WSB_11N));
	wtw_dbg(wtwdev, WTW_DBG_WFK,
		"[IQK]0xcd0 = 0x%x 0xcd4 = 0x%x 0xcd8 = 0x%x\n",
		wtw_wead32(wtwdev, WEG_TXIQ_AB_S0),
		wtw_wead32(wtwdev, WEG_TXIQ_CD_S0),
		wtw_wead32(wtwdev, WEG_WXIQ_AB_S0));

	wtw_dbg(wtwdev, WTW_DBG_WFK, "[IQK] finished\n");
}

static void wtw8723d_phy_cck_pd_set(stwuct wtw_dev *wtwdev, u8 new_wvw)
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

/* fow coex */
static void wtw8723d_coex_cfg_init(stwuct wtw_dev *wtwdev)
{
	/* enabwe TBTT ntewwupt */
	wtw_wwite8_set(wtwdev, WEG_BCN_CTWW, BIT_EN_BCN_FUNCTION);

	/* BT wepowt packet sampwe wate	 */
	/* 0x790[5:0]=0x5 */
	wtw_wwite8_mask(wtwdev, WEG_BT_TDMA_TIME, BIT_MASK_SAMPWE_WATE, 0x5);

	/* enabwe BT countew statistics */
	wtw_wwite8(wtwdev, WEG_BT_STAT_CTWW, 0x1);

	/* enabwe PTA (3-wiwe function fowm BT side) */
	wtw_wwite32_set(wtwdev, WEG_GPIO_MUXCFG, BIT_BT_PTA_EN);
	wtw_wwite32_set(wtwdev, WEG_GPIO_MUXCFG, BIT_PO_BT_PTA_PINS);

	/* enabwe PTA (tx/wx signaw fowm WiFi side) */
	wtw_wwite8_set(wtwdev, WEG_QUEUE_CTWW, BIT_PTA_WW_TX_EN);
}

static void wtw8723d_coex_cfg_gnt_fix(stwuct wtw_dev *wtwdev)
{
}

static void wtw8723d_coex_cfg_gnt_debug(stwuct wtw_dev *wtwdev)
{
	wtw_wwite8_mask(wtwdev, WEG_WEDCFG2, BIT(6), 0);
	wtw_wwite8_mask(wtwdev, WEG_PAD_CTWW1 + 3, BIT(0), 0);
	wtw_wwite8_mask(wtwdev, WEG_GPIO_INTM + 2, BIT(4), 0);
	wtw_wwite8_mask(wtwdev, WEG_GPIO_MUXCFG + 2, BIT(1), 0);
	wtw_wwite8_mask(wtwdev, WEG_PAD_CTWW1 + 3, BIT(1), 0);
	wtw_wwite8_mask(wtwdev, WEG_PAD_CTWW1 + 2, BIT(7), 0);
	wtw_wwite8_mask(wtwdev, WEG_SYS_CWKW + 1, BIT(1), 0);
	wtw_wwite8_mask(wtwdev, WEG_SYS_SDIO_CTWW + 3, BIT(3), 0);
}

static void wtw8723d_coex_cfg_wfe_type(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_wfe *coex_wfe = &coex->wfe;
	boow aux = efuse->bt_setting & BIT(6);

	coex_wfe->wfe_moduwe_type = wtwdev->efuse.wfe_option;
	coex_wfe->ant_switch_powawity = 0;
	coex_wfe->ant_switch_exist = fawse;
	coex_wfe->ant_switch_with_bt = fawse;
	coex_wfe->ant_switch_divewsity = fawse;
	coex_wfe->wwg_at_btg = twue;

	/* decide antenna at main ow aux */
	if (efuse->shawe_ant) {
		if (aux)
			wtw_wwite16(wtwdev, WEG_BB_SEW_BTG, 0x80);
		ewse
			wtw_wwite16(wtwdev, WEG_BB_SEW_BTG, 0x200);
	} ewse {
		if (aux)
			wtw_wwite16(wtwdev, WEG_BB_SEW_BTG, 0x280);
		ewse
			wtw_wwite16(wtwdev, WEG_BB_SEW_BTG, 0x0);
	}

	/* disabwe WTE coex in wifi side */
	wtw_coex_wwite_indiwect_weg(wtwdev, WTE_COEX_CTWW, BIT_WTE_COEX_EN, 0x0);
	wtw_coex_wwite_indiwect_weg(wtwdev, WTE_WW_TWX_CTWW, MASKWWOWD, 0xffff);
	wtw_coex_wwite_indiwect_weg(wtwdev, WTE_BT_TWX_CTWW, MASKWWOWD, 0xffff);
}

static void wtw8723d_coex_cfg_ww_tx_powew(stwuct wtw_dev *wtwdev, u8 ww_pww)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	static const u8	ww_tx_powew[] = {0xb2, 0x90};
	u8 pww;

	if (ww_pww == coex_dm->cuw_ww_pww_wvw)
		wetuwn;

	coex_dm->cuw_ww_pww_wvw = ww_pww;

	if (coex_dm->cuw_ww_pww_wvw >= AWWAY_SIZE(ww_tx_powew))
		coex_dm->cuw_ww_pww_wvw = AWWAY_SIZE(ww_tx_powew) - 1;

	pww = ww_tx_powew[coex_dm->cuw_ww_pww_wvw];

	wtw_wwite8(wtwdev, WEG_ANA_PAWAM1 + 3, pww);
}

static void wtw8723d_coex_cfg_ww_wx_gain(stwuct wtw_dev *wtwdev, boow wow_gain)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_dm *coex_dm = &coex->dm;
	/* WW Wx Wow gain on */
	static const u32 ww_wx_wow_gain_on[] = {
		0xec120101, 0xeb130101, 0xce140101, 0xcd150101, 0xcc160101,
		0xcb170101, 0xca180101, 0x8d190101, 0x8c1a0101, 0x8b1b0101,
		0x4f1c0101, 0x4e1d0101, 0x4d1e0101, 0x4c1f0101, 0x0e200101,
		0x0d210101, 0x0c220101, 0x0b230101, 0xcf240001, 0xce250001,
		0xcd260001, 0xcc270001, 0x8f280001
	};
	/* WW Wx Wow gain off */
	static const u32 ww_wx_wow_gain_off[] = {
		0xec120101, 0xeb130101, 0xea140101, 0xe9150101, 0xe8160101,
		0xe7170101, 0xe6180101, 0xe5190101, 0xe41a0101, 0xe31b0101,
		0xe21c0101, 0xe11d0101, 0xe01e0101, 0x861f0101, 0x85200101,
		0x84210101, 0x83220101, 0x82230101, 0x81240101, 0x80250101,
		0x44260101, 0x43270101, 0x42280101
	};
	u8 i;

	if (wow_gain == coex_dm->cuw_ww_wx_wow_gain_en)
		wetuwn;

	coex_dm->cuw_ww_wx_wow_gain_en = wow_gain;

	if (coex_dm->cuw_ww_wx_wow_gain_en) {
		fow (i = 0; i < AWWAY_SIZE(ww_wx_wow_gain_on); i++)
			wtw_wwite32(wtwdev, WEG_AGCWSSI, ww_wx_wow_gain_on[i]);
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(ww_wx_wow_gain_off); i++)
			wtw_wwite32(wtwdev, WEG_AGCWSSI, ww_wx_wow_gain_off[i]);
	}
}

static u8 wtw8723d_pwwtwack_get_wimit_ofdm(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 tx_wate = dm_info->tx_wate;
	u8 wimit_ofdm = 30;

	switch (tx_wate) {
	case DESC_WATE1M...DESC_WATE5_5M:
	case DESC_WATE11M:
		bweak;
	case DESC_WATE6M...DESC_WATE48M:
		wimit_ofdm = 36;
		bweak;
	case DESC_WATE54M:
		wimit_ofdm = 34;
		bweak;
	case DESC_WATEMCS0...DESC_WATEMCS2:
		wimit_ofdm = 38;
		bweak;
	case DESC_WATEMCS3...DESC_WATEMCS4:
		wimit_ofdm = 36;
		bweak;
	case DESC_WATEMCS5...DESC_WATEMCS7:
		wimit_ofdm = 34;
		bweak;
	defauwt:
		wtw_wawn(wtwdev, "pwwtwack unhandwed tx_wate 0x%x\n", tx_wate);
		bweak;
	}

	wetuwn wimit_ofdm;
}

static void wtw8723d_set_iqk_matwix_by_wesuwt(stwuct wtw_dev *wtwdev,
					      u32 ofdm_swing, u8 wf_path)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	s32 ewe_A, ewe_D, ewe_C;
	s32 ewe_A_ext, ewe_C_ext, ewe_D_ext;
	s32 iqk_wesuwt_x;
	s32 iqk_wesuwt_y;
	s32 vawue32;

	switch (wf_path) {
	defauwt:
	case WF_PATH_A:
		iqk_wesuwt_x = dm_info->iqk.wesuwt.s1_x;
		iqk_wesuwt_y = dm_info->iqk.wesuwt.s1_y;
		bweak;
	case WF_PATH_B:
		iqk_wesuwt_x = dm_info->iqk.wesuwt.s0_x;
		iqk_wesuwt_y = dm_info->iqk.wesuwt.s0_y;
		bweak;
	}

	/* new ewement D */
	ewe_D = OFDM_SWING_D(ofdm_swing);
	iqk_muwt(iqk_wesuwt_x, ewe_D, &ewe_D_ext);
	/* new ewement A */
	iqk_wesuwt_x = iqkxy_to_s32(iqk_wesuwt_x);
	ewe_A = iqk_muwt(iqk_wesuwt_x, ewe_D, &ewe_A_ext);
	/* new ewement C */
	iqk_wesuwt_y = iqkxy_to_s32(iqk_wesuwt_y);
	ewe_C = iqk_muwt(iqk_wesuwt_y, ewe_D, &ewe_C_ext);

	switch (wf_path) {
	case WF_PATH_A:
	defauwt:
		/* wwite new ewements A, C, D, and ewement B is awways 0 */
		vawue32 = BIT_SET_TXIQ_EWM_ACD(ewe_A, ewe_C, ewe_D);
		wtw_wwite32(wtwdev, WEG_OFDM_0_XA_TX_IQ_IMBAWANCE, vawue32);
		vawue32 = BIT_SET_TXIQ_EWM_C1(ewe_C);
		wtw_wwite32_mask(wtwdev, WEG_TXIQK_MATWIXA_WSB2_11N, MASKH4BITS,
				 vawue32);
		vawue32 = wtw_wead32(wtwdev, WEG_OFDM_0_ECCA_THWESHOWD);
		vawue32 &= ~BIT_MASK_OFDM0_EXTS;
		vawue32 |= BIT_SET_OFDM0_EXTS(ewe_A_ext, ewe_C_ext, ewe_D_ext);
		wtw_wwite32(wtwdev, WEG_OFDM_0_ECCA_THWESHOWD, vawue32);
		bweak;

	case WF_PATH_B:
		/* wwite new ewements A, C, D, and ewement B is awways 0 */
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_CD_S0, BIT_MASK_TXIQ_D_S0, ewe_D);
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_S0, ewe_C);
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_S0, ewe_A);

		wtw_wwite32_mask(wtwdev, WEG_TXIQ_CD_S0, BIT_MASK_TXIQ_D_EXT_S0,
				 ewe_D_ext);
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_EXT_S0,
				 ewe_A_ext);
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_EXT_S0,
				 ewe_C_ext);
		bweak;
	}
}

static void wtw8723d_set_iqk_matwix(stwuct wtw_dev *wtwdev, s8 ofdm_index,
				    u8 wf_path)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	s32 vawue32;
	u32 ofdm_swing;

	if (ofdm_index >= WTW_OFDM_SWING_TABWE_SIZE)
		ofdm_index = WTW_OFDM_SWING_TABWE_SIZE - 1;
	ewse if (ofdm_index < 0)
		ofdm_index = 0;

	ofdm_swing = wtw8723d_ofdm_swing_tabwe[ofdm_index];

	if (dm_info->iqk.done) {
		wtw8723d_set_iqk_matwix_by_wesuwt(wtwdev, ofdm_swing, wf_path);
		wetuwn;
	}

	switch (wf_path) {
	case WF_PATH_A:
	defauwt:
		wtw_wwite32(wtwdev, WEG_OFDM_0_XA_TX_IQ_IMBAWANCE, ofdm_swing);
		wtw_wwite32_mask(wtwdev, WEG_TXIQK_MATWIXA_WSB2_11N, MASKH4BITS,
				 0x00);
		vawue32 = wtw_wead32(wtwdev, WEG_OFDM_0_ECCA_THWESHOWD);
		vawue32 &= ~BIT_MASK_OFDM0_EXTS;
		wtw_wwite32(wtwdev, WEG_OFDM_0_ECCA_THWESHOWD, vawue32);
		bweak;

	case WF_PATH_B:
		/* image S1:c80 to S0:Cd0 and Cd4 */
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_S0,
				 OFDM_SWING_A(ofdm_swing));
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_AB_S0, BIT_MASK_TXIQ_B_S0,
				 OFDM_SWING_B(ofdm_swing));
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_S0,
				 OFDM_SWING_C(ofdm_swing));
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_CD_S0, BIT_MASK_TXIQ_D_S0,
				 OFDM_SWING_D(ofdm_swing));
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_CD_S0, BIT_MASK_TXIQ_D_EXT_S0, 0x0);
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_EXT_S0, 0x0);
		wtw_wwite32_mask(wtwdev, WEG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_EXT_S0, 0x0);
		bweak;
	}
}

static void wtw8723d_pwwtwack_set_ofdm_pww(stwuct wtw_dev *wtwdev, s8 swing_idx,
					   s8 txagc_idx)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;

	dm_info->txagc_wemnant_ofdm = txagc_idx;

	wtw8723d_set_iqk_matwix(wtwdev, swing_idx, WF_PATH_A);
	wtw8723d_set_iqk_matwix(wtwdev, swing_idx, WF_PATH_B);
}

static void wtw8723d_pwwtwack_set_cck_pww(stwuct wtw_dev *wtwdev, s8 swing_idx,
					  s8 txagc_idx)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;

	dm_info->txagc_wemnant_cck = txagc_idx;

	wtw_wwite32_mask(wtwdev, 0xab4, 0x000007FF,
			 wtw8723d_cck_swing_tabwe[swing_idx]);
}

static void wtw8723d_pwwtwack_set(stwuct wtw_dev *wtwdev, u8 path)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 wimit_ofdm;
	u8 wimit_cck = 40;
	s8 finaw_ofdm_swing_index;
	s8 finaw_cck_swing_index;

	wimit_ofdm = wtw8723d_pwwtwack_get_wimit_ofdm(wtwdev);

	finaw_ofdm_swing_index = WTW_DEF_OFDM_SWING_INDEX +
				 dm_info->dewta_powew_index[path];
	finaw_cck_swing_index = WTW_DEF_CCK_SWING_INDEX +
				dm_info->dewta_powew_index[path];

	if (finaw_ofdm_swing_index > wimit_ofdm)
		wtw8723d_pwwtwack_set_ofdm_pww(wtwdev, wimit_ofdm,
					       finaw_ofdm_swing_index - wimit_ofdm);
	ewse if (finaw_ofdm_swing_index < 0)
		wtw8723d_pwwtwack_set_ofdm_pww(wtwdev, 0,
					       finaw_ofdm_swing_index);
	ewse
		wtw8723d_pwwtwack_set_ofdm_pww(wtwdev, finaw_ofdm_swing_index, 0);

	if (finaw_cck_swing_index > wimit_cck)
		wtw8723d_pwwtwack_set_cck_pww(wtwdev, wimit_cck,
					      finaw_cck_swing_index - wimit_cck);
	ewse if (finaw_cck_swing_index < 0)
		wtw8723d_pwwtwack_set_cck_pww(wtwdev, 0,
					      finaw_cck_swing_index);
	ewse
		wtw8723d_pwwtwack_set_cck_pww(wtwdev, finaw_cck_swing_index, 0);

	wtw_phy_set_tx_powew_wevew(wtwdev, haw->cuwwent_channew);
}

static void wtw8723d_pwwtwack_set_xtaw(stwuct wtw_dev *wtwdev, u8 thewm_path,
				       u8 dewta)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	const stwuct wtw_pww_twack_tbw *tbw = wtwdev->chip->pww_twack_tbw;
	const s8 *pwwtwk_xtaw;
	s8 xtaw_cap;

	if (dm_info->thewmaw_avg[thewm_path] >
	    wtwdev->efuse.thewmaw_metew[thewm_path])
		pwwtwk_xtaw = tbw->pwwtwk_xtaw_p;
	ewse
		pwwtwk_xtaw = tbw->pwwtwk_xtaw_n;

	xtaw_cap = wtwdev->efuse.cwystaw_cap & 0x3F;
	xtaw_cap = cwamp_t(s8, xtaw_cap + pwwtwk_xtaw[dewta], 0, 0x3F);
	wtw_wwite32_mask(wtwdev, WEG_AFE_CTWW3, BIT_MASK_XTAW,
			 xtaw_cap | (xtaw_cap << 6));
}

static void wtw8723d_phy_pwwtwack(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	stwuct wtw_swing_tabwe swing_tabwe;
	u8 thewmaw_vawue, dewta, path;
	boow do_iqk = fawse;

	wtw_phy_config_swing_tabwe(wtwdev, &swing_tabwe);

	if (wtwdev->efuse.thewmaw_metew[0] == 0xff)
		wetuwn;

	thewmaw_vawue = wtw_wead_wf(wtwdev, WF_PATH_A, WF_T_METEW, 0xfc00);

	wtw_phy_pwwtwack_avg(wtwdev, thewmaw_vawue, WF_PATH_A);

	do_iqk = wtw_phy_pwwtwack_need_iqk(wtwdev);

	if (do_iqk)
		wtw8723d_wck(wtwdev);

	if (dm_info->pww_twk_init_twiggew)
		dm_info->pww_twk_init_twiggew = fawse;
	ewse if (!wtw_phy_pwwtwack_thewmaw_changed(wtwdev, thewmaw_vawue,
						   WF_PATH_A))
		goto iqk;

	dewta = wtw_phy_pwwtwack_get_dewta(wtwdev, WF_PATH_A);

	dewta = min_t(u8, dewta, WTW_PWW_TWK_TBW_SZ - 1);

	fow (path = 0; path < wtwdev->haw.wf_path_num; path++) {
		s8 dewta_cuw, dewta_wast;

		dewta_wast = dm_info->dewta_powew_index[path];
		dewta_cuw = wtw_phy_pwwtwack_get_pwwidx(wtwdev, &swing_tabwe,
							path, WF_PATH_A, dewta);
		if (dewta_wast == dewta_cuw)
			continue;

		dm_info->dewta_powew_index[path] = dewta_cuw;
		wtw8723d_pwwtwack_set(wtwdev, path);
	}

	wtw8723d_pwwtwack_set_xtaw(wtwdev, WF_PATH_A, dewta);

iqk:
	if (do_iqk)
		wtw8723d_phy_cawibwation(wtwdev);
}

static void wtw8723d_pww_twack(stwuct wtw_dev *wtwdev)
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

	wtw8723d_phy_pwwtwack(wtwdev);
	dm_info->pww_twk_twiggewed = fawse;
}

static void wtw8723d_fiww_txdesc_checksum(stwuct wtw_dev *wtwdev,
					  stwuct wtw_tx_pkt_info *pkt_info,
					  u8 *txdesc)
{
	size_t wowds = 32 / 2; /* cawcuwate the fiwst 32 bytes (16 wowds) */
	__we16 chksum = 0;
	__we16 *data = (__we16 *)(txdesc);
	stwuct wtw_tx_desc *tx_desc = (stwuct wtw_tx_desc *)txdesc;

	we32p_wepwace_bits(&tx_desc->w7, 0, WTW_TX_DESC_W7_TXDESC_CHECKSUM);

	whiwe (wowds--)
		chksum ^= *data++;

	chksum = ~chksum;

	we32p_wepwace_bits(&tx_desc->w7, __we16_to_cpu(chksum),
			   WTW_TX_DESC_W7_TXDESC_CHECKSUM);
}

static stwuct wtw_chip_ops wtw8723d_ops = {
	.phy_set_pawam		= wtw8723d_phy_set_pawam,
	.wead_efuse		= wtw8723d_wead_efuse,
	.quewy_wx_desc		= wtw8723d_quewy_wx_desc,
	.set_channew		= wtw8723d_set_channew,
	.mac_init		= wtw8723d_mac_init,
	.shutdown		= wtw8723d_shutdown,
	.wead_wf		= wtw_phy_wead_wf_sipi,
	.wwite_wf		= wtw_phy_wwite_wf_weg_sipi,
	.set_tx_powew_index	= wtw8723d_set_tx_powew_index,
	.set_antenna		= NUWW,
	.cfg_wdo25		= wtw8723d_cfg_wdo25,
	.efuse_gwant		= wtw8723d_efuse_gwant,
	.fawse_awawm_statistics	= wtw8723d_fawse_awawm_statistics,
	.phy_cawibwation	= wtw8723d_phy_cawibwation,
	.cck_pd_set		= wtw8723d_phy_cck_pd_set,
	.pww_twack		= wtw8723d_pww_twack,
	.config_bfee		= NUWW,
	.set_gid_tabwe		= NUWW,
	.cfg_csi_wate		= NUWW,
	.fiww_txdesc_checksum	= wtw8723d_fiww_txdesc_checksum,

	.coex_set_init		= wtw8723d_coex_cfg_init,
	.coex_set_ant_switch	= NUWW,
	.coex_set_gnt_fix	= wtw8723d_coex_cfg_gnt_fix,
	.coex_set_gnt_debug	= wtw8723d_coex_cfg_gnt_debug,
	.coex_set_wfe_type	= wtw8723d_coex_cfg_wfe_type,
	.coex_set_ww_tx_powew	= wtw8723d_coex_cfg_ww_tx_powew,
	.coex_set_ww_wx_gain	= wtw8723d_coex_cfg_ww_wx_gain,
};

/* Shawed-Antenna Coex Tabwe */
static const stwuct coex_tabwe_pawa tabwe_sant_8723d[] = {
	{0xffffffff, 0xffffffff}, /* case-0 */
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
	{0x66555555, 0x6a5a5aaa},
	{0x66555555, 0x5a5a5aaa},
	{0x66555555, 0x6aaa5aaa},
	{0x66555555, 0xaaaa5aaa},
	{0x66555555, 0xaaaaaaaa}, /* case-15 */
	{0xffff55ff, 0xfafafafa},
	{0xffff55ff, 0x6afa5afa},
	{0xaaffffaa, 0xfafafafa},
	{0xaa5555aa, 0x5a5a5a5a},
	{0xaa5555aa, 0x6a5a5a5a}, /* case-20 */
	{0xaa5555aa, 0xaaaaaaaa},
	{0xffffffff, 0x5a5a5a5a},
	{0xffffffff, 0x5a5a5a5a},
	{0xffffffff, 0x55555555},
	{0xffffffff, 0x5a5a5aaa}, /* case-25 */
	{0x55555555, 0x5a5a5a5a},
	{0x55555555, 0xaaaaaaaa},
	{0x55555555, 0x6a5a6a5a},
	{0x66556655, 0x66556655},
	{0x66556aaa, 0x6a5a6aaa}, /* case-30 */
	{0xffffffff, 0x5aaa5aaa},
	{0x56555555, 0x5a5a5aaa},
};

/* Non-Shawed-Antenna Coex Tabwe */
static const stwuct coex_tabwe_pawa tabwe_nsant_8723d[] = {
	{0xffffffff, 0xffffffff}, /* case-100 */
	{0x55555555, 0x55555555},
	{0x66555555, 0x66555555},
	{0xaaaaaaaa, 0xaaaaaaaa},
	{0x5a5a5a5a, 0x5a5a5a5a},
	{0xfafafafa, 0xfafafafa}, /* case-105 */
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
	{0xffffffff, 0x5afa5afa},
	{0xffffffff, 0xaaaaaaaa}, /* case-120 */
	{0x55ff55ff, 0x5afa5afa},
	{0x55ff55ff, 0xaaaaaaaa},
	{0x55ff55ff, 0x55ff55ff}
};

/* Shawed-Antenna TDMA */
static const stwuct coex_tdma_pawa tdma_sant_8723d[] = {
	{ {0x00, 0x00, 0x00, 0x00, 0x00} }, /* case-0 */
	{ {0x61, 0x45, 0x03, 0x11, 0x11} }, /* case-1 */
	{ {0x61, 0x3a, 0x03, 0x11, 0x11} },
	{ {0x61, 0x30, 0x03, 0x11, 0x11} },
	{ {0x61, 0x20, 0x03, 0x11, 0x11} },
	{ {0x61, 0x10, 0x03, 0x11, 0x11} }, /* case-5 */
	{ {0x61, 0x45, 0x03, 0x11, 0x10} },
	{ {0x61, 0x3a, 0x03, 0x11, 0x10} },
	{ {0x61, 0x30, 0x03, 0x11, 0x10} },
	{ {0x61, 0x20, 0x03, 0x11, 0x10} },
	{ {0x61, 0x10, 0x03, 0x11, 0x10} }, /* case-10 */
	{ {0x61, 0x08, 0x03, 0x11, 0x14} },
	{ {0x61, 0x08, 0x03, 0x10, 0x14} },
	{ {0x51, 0x08, 0x03, 0x10, 0x54} },
	{ {0x51, 0x08, 0x03, 0x10, 0x55} },
	{ {0x51, 0x08, 0x07, 0x10, 0x54} }, /* case-15 */
	{ {0x51, 0x45, 0x03, 0x10, 0x50} },
	{ {0x51, 0x3a, 0x03, 0x10, 0x50} },
	{ {0x51, 0x30, 0x03, 0x10, 0x50} },
	{ {0x51, 0x20, 0x03, 0x10, 0x50} },
	{ {0x51, 0x10, 0x03, 0x10, 0x50} }, /* case-20 */
	{ {0x51, 0x4a, 0x03, 0x10, 0x50} },
	{ {0x51, 0x0c, 0x03, 0x10, 0x54} },
	{ {0x55, 0x08, 0x03, 0x10, 0x54} },
	{ {0x65, 0x10, 0x03, 0x11, 0x10} },
	{ {0x51, 0x10, 0x03, 0x10, 0x51} }, /* case-25 */
	{ {0x51, 0x08, 0x03, 0x10, 0x50} },
	{ {0x61, 0x08, 0x03, 0x11, 0x11} }
};

/* Non-Shawed-Antenna TDMA */
static const stwuct coex_tdma_pawa tdma_nsant_8723d[] = {
	{ {0x00, 0x00, 0x00, 0x00, 0x01} }, /* case-100 */
	{ {0x61, 0x45, 0x03, 0x11, 0x11} }, /* case-101 */
	{ {0x61, 0x3a, 0x03, 0x11, 0x11} },
	{ {0x61, 0x30, 0x03, 0x11, 0x11} },
	{ {0x61, 0x20, 0x03, 0x11, 0x11} },
	{ {0x61, 0x10, 0x03, 0x11, 0x11} }, /* case-105 */
	{ {0x61, 0x45, 0x03, 0x11, 0x10} },
	{ {0x61, 0x3a, 0x03, 0x11, 0x10} },
	{ {0x61, 0x30, 0x03, 0x11, 0x10} },
	{ {0x61, 0x20, 0x03, 0x11, 0x10} },
	{ {0x61, 0x10, 0x03, 0x11, 0x10} }, /* case-110 */
	{ {0x61, 0x08, 0x03, 0x11, 0x14} },
	{ {0x61, 0x08, 0x03, 0x10, 0x14} },
	{ {0x51, 0x08, 0x03, 0x10, 0x54} },
	{ {0x51, 0x08, 0x03, 0x10, 0x55} },
	{ {0x51, 0x08, 0x07, 0x10, 0x54} }, /* case-115 */
	{ {0x51, 0x45, 0x03, 0x10, 0x50} },
	{ {0x51, 0x3a, 0x03, 0x10, 0x50} },
	{ {0x51, 0x30, 0x03, 0x10, 0x50} },
	{ {0x51, 0x20, 0x03, 0x10, 0x50} },
	{ {0x51, 0x10, 0x03, 0x10, 0x50} }, /* case-120 */
	{ {0x51, 0x08, 0x03, 0x10, 0x50} }
};

/* wssi in pewcentage % (dbm = % - 100) */
static const u8 ww_wssi_step_8723d[] = {60, 50, 44, 30};
static const u8 bt_wssi_step_8723d[] = {30, 30, 30, 30};
static const stwuct coex_5g_afh_map afh_5g_8723d[] = { {0, 0, 0} };

static const stwuct wtw_hw_weg btg_weg_8723d = {
	.addw = WEG_BTG_SEW, .mask = BIT_MASK_BTG_WW,
};

/* ww_tx_dec_powew, bt_tx_dec_powew, ww_wx_gain, bt_wx_wna_constwain */
static const stwuct coex_wf_pawa wf_pawa_tx_8723d[] = {
	{0, 0, fawse, 7},  /* fow nowmaw */
	{0, 10, fawse, 7}, /* fow WW-CPT */
	{1, 0, twue, 4},
	{1, 2, twue, 4},
	{1, 10, twue, 4},
	{1, 15, twue, 4}
};

static const stwuct coex_wf_pawa wf_pawa_wx_8723d[] = {
	{0, 0, fawse, 7},  /* fow nowmaw */
	{0, 10, fawse, 7}, /* fow WW-CPT */
	{1, 0, twue, 5},
	{1, 2, twue, 5},
	{1, 10, twue, 5},
	{1, 15, twue, 5}
};

static const stwuct wtw_pww_seq_cmd twans_cawddis_to_cawdemu_8723d[] = {
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(3) | BIT(7), 0},
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
	 WTW_PWW_CMD_WWITE, BIT(3) | BIT(4), 0},
	{0x0023,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(4), 0},
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

static const stwuct wtw_pww_seq_cmd twans_cawdemu_to_act_8723d[] = {
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
	 WTW_PWW_CMD_POWWING, (BIT(1) | BIT(0)), 0},
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
	{0x0010,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(6), BIT(6)},
	{0x0049,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), BIT(1)},
	{0x0063,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), BIT(1)},
	{0x0062,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), 0},
	{0x0058,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x005A,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), BIT(1)},
	{0x0068,
	 WTW_PWW_CUT_TEST_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(3), BIT(3)},
	{0x0069,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(6), BIT(6)},
	{0x001f,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x00},
	{0x0077,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x00},
	{0x001f,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x07},
	{0x0077,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x07},
	{0xFFFF,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 0,
	 WTW_PWW_CMD_END, 0, 0},
};

static const stwuct wtw_pww_seq_cmd *cawd_enabwe_fwow_8723d[] = {
	twans_cawddis_to_cawdemu_8723d,
	twans_cawdemu_to_act_8723d,
	NUWW
};

static const stwuct wtw_pww_seq_cmd twans_act_to_wps_8723d[] = {
	{0x0301,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0xFF},
	{0x0522,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0xFF},
	{0x05F8,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_POWWING, 0xFF, 0},
	{0x05F9,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_POWWING, 0xFF, 0},
	{0x05FA,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_POWWING, 0xFF, 0},
	{0x05FB,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_POWWING, 0xFF, 0},
	{0x0002,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), 0},
	{0x0002,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_DEWAY, 0, WTW_PWW_DEWAY_US},
	{0x0002,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), 0},
	{0x0100,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x03},
	{0x0101,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(1), 0},
	{0x0093,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x00},
	{0x0553,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(5), BIT(5)},
	{0xFFFF,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 0,
	 WTW_PWW_CMD_END, 0, 0},
};

static const stwuct wtw_pww_seq_cmd twans_act_to_pwe_cawddis_8723d[] = {
	{0x0003,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(2), 0},
	{0x0080,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0},
	{0xFFFF,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 0,
	 WTW_PWW_CMD_END, 0, 0},
};

static const stwuct wtw_pww_seq_cmd twans_act_to_cawdemu_8723d[] = {
	{0x0002,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), 0},
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
	{0x0010,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(6), 0},
	{0x0000,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK | WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(5), BIT(5)},
	{0x0020,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK | WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), 0},
	{0xFFFF,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 0,
	 WTW_PWW_CMD_END, 0, 0},
};

static const stwuct wtw_pww_seq_cmd twans_cawdemu_to_cawddis_8723d[] = {
	{0x0007,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x20},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK | WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(3) | BIT(4), BIT(3)},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(2), BIT(2)},
	{0x0005,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_PCI_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(3) | BIT(4), BIT(3) | BIT(4)},
	{0x004A,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_USB_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), 1},
	{0x0023,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_SDIO_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(4), BIT(4)},
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
	{0xFFFF,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 0,
	 WTW_PWW_CMD_END, 0, 0},
};

static const stwuct wtw_pww_seq_cmd twans_act_to_post_cawddis_8723d[] = {
	{0x001D,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), 0},
	{0x001D,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x001C,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 WTW_PWW_ADDW_MAC,
	 WTW_PWW_CMD_WWITE, 0xFF, 0x0E},
	{0xFFFF,
	 WTW_PWW_CUT_AWW_MSK,
	 WTW_PWW_INTF_AWW_MSK,
	 0,
	 WTW_PWW_CMD_END, 0, 0},
};

static const stwuct wtw_pww_seq_cmd *cawd_disabwe_fwow_8723d[] = {
	twans_act_to_wps_8723d,
	twans_act_to_pwe_cawddis_8723d,
	twans_act_to_cawdemu_8723d,
	twans_cawdemu_to_cawddis_8723d,
	twans_act_to_post_cawddis_8723d,
	NUWW
};

static const stwuct wtw_page_tabwe page_tabwe_8723d[] = {
	{12, 2, 2, 0, 1},
	{12, 2, 2, 0, 1},
	{12, 2, 2, 0, 1},
	{12, 2, 2, 0, 1},
	{12, 2, 2, 0, 1},
};

static const stwuct wtw_wqpn wqpn_tabwe_8723d[] = {
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

static const stwuct wtw_pwioq_addws pwioq_addws_8723d = {
	.pwio[WTW_DMA_MAPPING_EXTWA] = {
		.wsvd = WEG_WQPN_NPQ + 2, .avaiw = WEG_WQPN_NPQ + 3,
	},
	.pwio[WTW_DMA_MAPPING_WOW] = {
		.wsvd = WEG_WQPN + 1, .avaiw = WEG_FIFOPAGE_CTWW_2 + 1,
	},
	.pwio[WTW_DMA_MAPPING_NOWMAW] = {
		.wsvd = WEG_WQPN_NPQ, .avaiw = WEG_WQPN_NPQ + 1,
	},
	.pwio[WTW_DMA_MAPPING_HIGH] = {
		.wsvd = WEG_WQPN, .avaiw = WEG_FIFOPAGE_CTWW_2,
	},
	.wsize = fawse,
};

static const stwuct wtw_intf_phy_pawa pcie_gen1_pawam_8723d[] = {
	{0x0008, 0x4a22,
	 WTW_IP_SEW_PHY,
	 WTW_INTF_PHY_CUT_AWW,
	 WTW_INTF_PHY_PWATFOWM_AWW},
	{0x0009, 0x1000,
	 WTW_IP_SEW_PHY,
	 ~(WTW_INTF_PHY_CUT_A | WTW_INTF_PHY_CUT_B),
	 WTW_INTF_PHY_PWATFOWM_AWW},
	{0xFFFF, 0x0000,
	 WTW_IP_SEW_PHY,
	 WTW_INTF_PHY_CUT_AWW,
	 WTW_INTF_PHY_PWATFOWM_AWW},
};

static const stwuct wtw_intf_phy_pawa_tabwe phy_pawa_tabwe_8723d = {
	.gen1_pawa	= pcie_gen1_pawam_8723d,
	.n_gen1_pawa	= AWWAY_SIZE(pcie_gen1_pawam_8723d),
};

static const stwuct wtw_hw_weg wtw8723d_dig[] = {
	[0] = { .addw = 0xc50, .mask = 0x7f },
	[1] = { .addw = 0xc50, .mask = 0x7f },
};

static const stwuct wtw_hw_weg wtw8723d_dig_cck[] = {
	[0] = { .addw = 0xa0c, .mask = 0x3f00 },
};

static const stwuct wtw_wf_sipi_addw wtw8723d_wf_sipi_addw[] = {
	[WF_PATH_A] = { .hssi_1 = 0x820, .wssi_wead    = 0x8a0,
			.hssi_2 = 0x824, .wssi_wead_pi = 0x8b8},
	[WF_PATH_B] = { .hssi_1 = 0x828, .wssi_wead    = 0x8a4,
			.hssi_2 = 0x82c, .wssi_wead_pi = 0x8bc},
};

static const stwuct wtw_wtecoex_addw wtw8723d_wtecoex_addw = {
	.ctww = WEG_WTECOEX_CTWW,
	.wdata = WEG_WTECOEX_WWITE_DATA,
	.wdata = WEG_WTECOEX_WEAD_DATA,
};

static const stwuct wtw_wfe_def wtw8723d_wfe_defs[] = {
	[0] = { .phy_pg_tbw	= &wtw8723d_bb_pg_tbw,
		.txpww_wmt_tbw	= &wtw8723d_txpww_wmt_tbw,},
};

static const u8 wtw8723d_pwwtwk_2gb_n[] = {
	0, 0, 1, 1, 1, 2, 2, 3, 4, 4, 4, 4, 5, 5, 5,
	6, 6, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10, 10
};

static const u8 wtw8723d_pwwtwk_2gb_p[] = {
	0, 0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7,
	7, 8, 8, 8, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10
};

static const u8 wtw8723d_pwwtwk_2ga_n[] = {
	0, 0, 1, 1, 1, 2, 2, 3, 4, 4, 4, 4, 5, 5, 5,
	6, 6, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10, 10
};

static const u8 wtw8723d_pwwtwk_2ga_p[] = {
	0, 0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7,
	7, 8, 8, 8, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10
};

static const u8 wtw8723d_pwwtwk_2g_cck_b_n[] = {
	0, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
	6, 7, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 11, 11, 11
};

static const u8 wtw8723d_pwwtwk_2g_cck_b_p[] = {
	0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7,
	7, 8, 9, 9, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11
};

static const u8 wtw8723d_pwwtwk_2g_cck_a_n[] = {
	0, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
	6, 7, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 11, 11, 11
};

static const u8 wtw8723d_pwwtwk_2g_cck_a_p[] = {
	0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7,
	7, 8, 9, 9, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11
};

static const s8 wtw8723d_pwwtwk_xtaw_n[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const s8 wtw8723d_pwwtwk_xtaw_p[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, -10, -12, -14, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16
};

static const stwuct wtw_pww_twack_tbw wtw8723d_wtw_pww_twack_tbw = {
	.pwwtwk_2gb_n = wtw8723d_pwwtwk_2gb_n,
	.pwwtwk_2gb_p = wtw8723d_pwwtwk_2gb_p,
	.pwwtwk_2ga_n = wtw8723d_pwwtwk_2ga_n,
	.pwwtwk_2ga_p = wtw8723d_pwwtwk_2ga_p,
	.pwwtwk_2g_cckb_n = wtw8723d_pwwtwk_2g_cck_b_n,
	.pwwtwk_2g_cckb_p = wtw8723d_pwwtwk_2g_cck_b_p,
	.pwwtwk_2g_ccka_n = wtw8723d_pwwtwk_2g_cck_a_n,
	.pwwtwk_2g_ccka_p = wtw8723d_pwwtwk_2g_cck_a_p,
	.pwwtwk_xtaw_p = wtw8723d_pwwtwk_xtaw_p,
	.pwwtwk_xtaw_n = wtw8723d_pwwtwk_xtaw_n,
};

static const stwuct wtw_weg_domain coex_info_hw_wegs_8723d[] = {
	{0x948, MASKDWOWD, WTW_WEG_DOMAIN_MAC32},
	{0x67, BIT(7), WTW_WEG_DOMAIN_MAC8},
	{0, 0, WTW_WEG_DOMAIN_NW},
	{0x964, BIT(1), WTW_WEG_DOMAIN_MAC8},
	{0x864, BIT(0), WTW_WEG_DOMAIN_MAC8},
	{0xab7, BIT(5), WTW_WEG_DOMAIN_MAC8},
	{0xa01, BIT(7), WTW_WEG_DOMAIN_MAC8},
	{0, 0, WTW_WEG_DOMAIN_NW},
	{0x430, MASKDWOWD, WTW_WEG_DOMAIN_MAC32},
	{0x434, MASKDWOWD, WTW_WEG_DOMAIN_MAC32},
	{0x42a, MASKWWOWD, WTW_WEG_DOMAIN_MAC16},
	{0x426, MASKBYTE0, WTW_WEG_DOMAIN_MAC8},
	{0x45e, BIT(3), WTW_WEG_DOMAIN_MAC8},
	{0, 0, WTW_WEG_DOMAIN_NW},
	{0x4c6, BIT(4), WTW_WEG_DOMAIN_MAC8},
	{0x40, BIT(5), WTW_WEG_DOMAIN_MAC8},
	{0x550, MASKDWOWD, WTW_WEG_DOMAIN_MAC32},
	{0x522, MASKBYTE0, WTW_WEG_DOMAIN_MAC8},
	{0x953, BIT(1), WTW_WEG_DOMAIN_MAC8},
};

const stwuct wtw_chip_info wtw8723d_hw_spec = {
	.ops = &wtw8723d_ops,
	.id = WTW_CHIP_TYPE_8723D,
	.fw_name = "wtw88/wtw8723d_fw.bin",
	.wwan_cpu = WTW_WCPU_11N,
	.tx_pkt_desc_sz = 40,
	.tx_buf_desc_sz = 16,
	.wx_pkt_desc_sz = 24,
	.wx_buf_desc_sz = 8,
	.phy_efuse_size = 512,
	.wog_efuse_size = 512,
	.ptct_efuse_size = 96 + 1,
	.txff_size = 32768,
	.wxff_size = 16384,
	.wsvd_dwv_pg_num = 8,
	.txgi_factow = 1,
	.is_pww_by_wate_dec = twue,
	.max_powew_index = 0x3f,
	.csi_buf_pg_num = 0,
	.band = WTW_BAND_2G,
	.page_size = TX_PAGE_SIZE,
	.dig_min = 0x20,
	.ht_suppowted = twue,
	.vht_suppowted = fawse,
	.wps_deep_mode_suppowted = 0,
	.sys_func_en = 0xFD,
	.pww_on_seq = cawd_enabwe_fwow_8723d,
	.pww_off_seq = cawd_disabwe_fwow_8723d,
	.page_tabwe = page_tabwe_8723d,
	.wqpn_tabwe = wqpn_tabwe_8723d,
	.pwioq_addws = &pwioq_addws_8723d,
	.intf_tabwe = &phy_pawa_tabwe_8723d,
	.dig = wtw8723d_dig,
	.dig_cck = wtw8723d_dig_cck,
	.wf_sipi_addw = {0x840, 0x844},
	.wf_sipi_wead_addw = wtw8723d_wf_sipi_addw,
	.fix_wf_phy_num = 2,
	.wtecoex_addw = &wtw8723d_wtecoex_addw,
	.mac_tbw = &wtw8723d_mac_tbw,
	.agc_tbw = &wtw8723d_agc_tbw,
	.bb_tbw = &wtw8723d_bb_tbw,
	.wf_tbw = {&wtw8723d_wf_a_tbw},
	.wfe_defs = wtw8723d_wfe_defs,
	.wfe_defs_size = AWWAY_SIZE(wtw8723d_wfe_defs),
	.wx_wdpc = fawse,
	.pww_twack_tbw = &wtw8723d_wtw_pww_twack_tbw,
	.iqk_thweshowd = 8,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
	.max_scan_ie_wen = IEEE80211_MAX_DATA_WEN,

	.coex_pawa_vew = 0x2007022f,
	.bt_desiwed_vew = 0x2f,
	.scbd_suppowt = twue,
	.new_scbd10_def = twue,
	.bwe_hid_pwofiwe_suppowt = fawse,
	.ww_mimo_ps_suppowt = fawse,
	.pstdma_type = COEX_PSTDMA_FOWCE_WPSOFF,
	.bt_wssi_type = COEX_BTWSSI_WATIO,
	.ant_isowation = 15,
	.wssi_towewance = 2,
	.ww_wssi_step = ww_wssi_step_8723d,
	.bt_wssi_step = bt_wssi_step_8723d,
	.tabwe_sant_num = AWWAY_SIZE(tabwe_sant_8723d),
	.tabwe_sant = tabwe_sant_8723d,
	.tabwe_nsant_num = AWWAY_SIZE(tabwe_nsant_8723d),
	.tabwe_nsant = tabwe_nsant_8723d,
	.tdma_sant_num = AWWAY_SIZE(tdma_sant_8723d),
	.tdma_sant = tdma_sant_8723d,
	.tdma_nsant_num = AWWAY_SIZE(tdma_nsant_8723d),
	.tdma_nsant = tdma_nsant_8723d,
	.ww_wf_pawa_num = AWWAY_SIZE(wf_pawa_tx_8723d),
	.ww_wf_pawa_tx = wf_pawa_tx_8723d,
	.ww_wf_pawa_wx = wf_pawa_wx_8723d,
	.bt_afh_span_bw20 = 0x20,
	.bt_afh_span_bw40 = 0x30,
	.afh_5g_num = AWWAY_SIZE(afh_5g_8723d),
	.afh_5g = afh_5g_8723d,
	.btg_weg = &btg_weg_8723d,

	.coex_info_hw_wegs_num = AWWAY_SIZE(coex_info_hw_wegs_8723d),
	.coex_info_hw_wegs = coex_info_hw_wegs_8723d,
};
EXPOWT_SYMBOW(wtw8723d_hw_spec);

MODUWE_FIWMWAWE("wtw88/wtw8723d_fw.bin");

MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11n wiwewess 8723d dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
