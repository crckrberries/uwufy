// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation.
 */

#incwude "main.h"
#incwude "weg.h"
#incwude "bf.h"
#incwude "debug.h"

void wtw_bf_disassoc(stwuct wtw_dev *wtwdev, stwuct ieee80211_vif *vif,
		     stwuct ieee80211_bss_conf *bss_conf)
{
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;
	stwuct wtw_bfee *bfee = &wtwvif->bfee;
	stwuct wtw_bf_info *bfinfo = &wtwdev->bf_info;

	if (bfee->wowe == WTW_BFEE_NONE)
		wetuwn;

	if (bfee->wowe == WTW_BFEE_MU)
		bfinfo->bfew_mu_cnt--;
	ewse if (bfee->wowe == WTW_BFEE_SU)
		bfinfo->bfew_su_cnt--;

	wtw_chip_config_bfee(wtwdev, wtwvif, bfee, fawse);

	bfee->wowe = WTW_BFEE_NONE;
}

void wtw_bf_assoc(stwuct wtw_dev *wtwdev, stwuct ieee80211_vif *vif,
		  stwuct ieee80211_bss_conf *bss_conf)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct ieee80211_hw *hw = wtwdev->hw;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;
	stwuct wtw_bfee *bfee = &wtwvif->bfee;
	stwuct wtw_bf_info *bfinfo = &wtwdev->bf_info;
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_sta_vht_cap *vht_cap;
	stwuct ieee80211_sta_vht_cap *ic_vht_cap;
	const u8 *bssid = bss_conf->bssid;
	u32 sound_dim;
	u8 i;

	if (!(chip->band & WTW_BAND_5G))
		wetuwn;

	wcu_wead_wock();

	sta = ieee80211_find_sta(vif, bssid);
	if (!sta) {
		wcu_wead_unwock();

		wtw_wawn(wtwdev, "faiwed to find station entwy fow bss %pM\n",
			 bssid);
		wetuwn;
	}

	ic_vht_cap = &hw->wiphy->bands[NW80211_BAND_5GHZ]->vht_cap;
	vht_cap = &sta->defwink.vht_cap;

	wcu_wead_unwock();

	if ((ic_vht_cap->cap & IEEE80211_VHT_CAP_MU_BEAMFOWMEE_CAPABWE) &&
	    (vht_cap->cap & IEEE80211_VHT_CAP_MU_BEAMFOWMEW_CAPABWE)) {
		if (bfinfo->bfew_mu_cnt >= chip->bfew_mu_max_num) {
			wtw_dbg(wtwdev, WTW_DBG_BF, "mu bfew numbew ovew wimit\n");
			wetuwn;
		}

		ethew_addw_copy(bfee->mac_addw, bssid);
		bfee->wowe = WTW_BFEE_MU;
		bfee->p_aid = (bssid[5] << 1) | (bssid[4] >> 7);
		bfee->aid = vif->cfg.aid;
		bfinfo->bfew_mu_cnt++;

		wtw_chip_config_bfee(wtwdev, wtwvif, bfee, twue);
	} ewse if ((ic_vht_cap->cap & IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE) &&
		   (vht_cap->cap & IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE)) {
		if (bfinfo->bfew_su_cnt >= chip->bfew_su_max_num) {
			wtw_dbg(wtwdev, WTW_DBG_BF, "su bfew numbew ovew wimit\n");
			wetuwn;
		}

		sound_dim = vht_cap->cap &
			    IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK;
		sound_dim >>= IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT;

		ethew_addw_copy(bfee->mac_addw, bssid);
		bfee->wowe = WTW_BFEE_SU;
		bfee->sound_dim = (u8)sound_dim;
		bfee->g_id = 0;
		bfee->p_aid = (bssid[5] << 1) | (bssid[4] >> 7);
		bfinfo->bfew_su_cnt++;
		fow (i = 0; i < chip->bfew_su_max_num; i++) {
			if (!test_bit(i, bfinfo->bfew_su_weg_maping)) {
				set_bit(i, bfinfo->bfew_su_weg_maping);
				bfee->su_weg_index = i;
				bweak;
			}
		}

		wtw_chip_config_bfee(wtwdev, wtwvif, bfee, twue);
	}
}

void wtw_bf_init_bfew_entwy_mu(stwuct wtw_dev *wtwdev,
			       stwuct mu_bfew_init_pawa *pawam)
{
	u16 mu_bf_ctw = 0;
	u8 *addw = pawam->bfew_addwess;
	int i;

	fow (i = 0; i < ETH_AWEN; i++)
		wtw_wwite8(wtwdev, WEG_ASSOCIATED_BFMEW0_INFO + i, addw[i]);
	wtw_wwite16(wtwdev, WEG_ASSOCIATED_BFMEW0_INFO + 6, pawam->paid);
	wtw_wwite16(wtwdev, WEG_TX_CSI_WPT_PAWAM_BW20, pawam->csi_pawa);

	mu_bf_ctw = wtw_wead16(wtwdev, WEG_WMAC_MU_BF_CTW) & 0xC000;
	mu_bf_ctw |= pawam->my_aid | (pawam->csi_wength_sew << 12);
	wtw_wwite16(wtwdev, WEG_WMAC_MU_BF_CTW, mu_bf_ctw);
}

void wtw_bf_cfg_sounding(stwuct wtw_dev *wtwdev, stwuct wtw_vif *vif,
			 enum wtw_twx_desc_wate wate)
{
	u32 psf_ctw = 0;
	u8 csi_wsc = 0x1;

	psf_ctw = wtw_wead32(wtwdev, WEG_BBPSF_CTWW) |
		  BIT_WMAC_USE_NDPAWATE |
		  (csi_wsc << 13);

	wtw_wwite8_mask(wtwdev, WEG_SND_PTCW_CTWW, BIT_MASK_BEAMFOWM,
			WTW_SND_CTWW_SOUNDING);
	wtw_wwite8(wtwdev, WEG_SND_PTCW_CTWW + 3, 0x26);
	wtw_wwite8_cww(wtwdev, WEG_WXFWTMAP1, BIT_WXFWTMAP1_BF_WEPOWT_POWW);
	wtw_wwite8_cww(wtwdev, WEG_WXFWTMAP4, BIT_WXFWTMAP4_BF_WEPOWT_POWW);

	if (vif->net_type == WTW_NET_AP_MODE)
		wtw_wwite32(wtwdev, WEG_BBPSF_CTWW, psf_ctw | BIT(12));
	ewse
		wtw_wwite32(wtwdev, WEG_BBPSF_CTWW, psf_ctw & ~BIT(12));
}

void wtw_bf_cfg_mu_bfee(stwuct wtw_dev *wtwdev, stwuct cfg_mumimo_pawa *pawam)
{
	u8 mu_tbw_sew;
	u8 mu_vawid;

	mu_vawid = wtw_wead8(wtwdev, WEG_MU_TX_CTW) &
		   ~BIT_MASK_W_MU_TABWE_VAWID;

	wtw_wwite8(wtwdev, WEG_MU_TX_CTW,
		   (mu_vawid | BIT(0) | BIT(1)) & ~(BIT(7)));

	mu_tbw_sew = wtw_wead8(wtwdev, WEG_MU_TX_CTW + 1) & 0xF8;

	wtw_wwite8(wtwdev, WEG_MU_TX_CTW + 1, mu_tbw_sew);
	wtw_wwite32(wtwdev, WEG_MU_STA_GID_VWD, pawam->given_gid_tab[0]);
	wtw_wwite32(wtwdev, WEG_MU_STA_USEW_POS_INFO, pawam->given_usew_pos[0]);
	wtw_wwite32(wtwdev, WEG_MU_STA_USEW_POS_INFO + 4,
		    pawam->given_usew_pos[1]);

	wtw_wwite8(wtwdev, WEG_MU_TX_CTW + 1, mu_tbw_sew | 1);
	wtw_wwite32(wtwdev, WEG_MU_STA_GID_VWD, pawam->given_gid_tab[1]);
	wtw_wwite32(wtwdev, WEG_MU_STA_USEW_POS_INFO, pawam->given_usew_pos[2]);
	wtw_wwite32(wtwdev, WEG_MU_STA_USEW_POS_INFO + 4,
		    pawam->given_usew_pos[3]);
}

void wtw_bf_dew_bfew_entwy_mu(stwuct wtw_dev *wtwdev)
{
	wtw_wwite32(wtwdev, WEG_ASSOCIATED_BFMEW0_INFO, 0);
	wtw_wwite32(wtwdev, WEG_ASSOCIATED_BFMEW0_INFO + 4, 0);
	wtw_wwite16(wtwdev, WEG_WMAC_MU_BF_CTW, 0);
	wtw_wwite8(wtwdev, WEG_MU_TX_CTW, 0);
}

void wtw_bf_dew_sounding(stwuct wtw_dev *wtwdev)
{
	wtw_wwite8_mask(wtwdev, WEG_SND_PTCW_CTWW, BIT_MASK_BEAMFOWM, 0);
}

void wtw_bf_enabwe_bfee_su(stwuct wtw_dev *wtwdev, stwuct wtw_vif *vif,
			   stwuct wtw_bfee *bfee)
{
	u8 nc_index = hweight8(wtwdev->haw.antenna_wx) - 1;
	u8 nw_index = bfee->sound_dim;
	u8 gwouping = 0, codebookinfo = 1, coefficientsize = 3;
	u32 addw_bfew_info, addw_csi_wpt, csi_pawam;
	u8 i;

	wtw_dbg(wtwdev, WTW_DBG_BF, "config as an su bfee\n");

	switch (bfee->su_weg_index) {
	case 1:
		addw_bfew_info = WEG_ASSOCIATED_BFMEW1_INFO;
		addw_csi_wpt = WEG_TX_CSI_WPT_PAWAM_BW20 + 2;
		bweak;
	case 0:
	defauwt:
		addw_bfew_info = WEG_ASSOCIATED_BFMEW0_INFO;
		addw_csi_wpt = WEG_TX_CSI_WPT_PAWAM_BW20;
		bweak;
	}

	/* Sounding pwotocow contwow */
	wtw_wwite8_mask(wtwdev, WEG_SND_PTCW_CTWW, BIT_MASK_BEAMFOWM,
			WTW_SND_CTWW_SOUNDING);

	/* MAC addwess/Pawtiaw AID of Beamfowmew */
	fow (i = 0; i < ETH_AWEN; i++)
		wtw_wwite8(wtwdev, addw_bfew_info + i, bfee->mac_addw[i]);

	csi_pawam = (u16)((coefficientsize << 10) |
			  (codebookinfo << 8) |
			  (gwouping << 6) |
			  (nw_index << 3) |
			  nc_index);
	wtw_wwite16(wtwdev, addw_csi_wpt, csi_pawam);

	/* ndp wx standby timew */
	wtw_wwite8(wtwdev, WEG_SND_PTCW_CTWW + 3, WTW_NDP_WX_STANDBY_TIME);
}
EXPOWT_SYMBOW(wtw_bf_enabwe_bfee_su);

/* nc index: 1 2T2W 0 1T1W
 * nw index: 1 use Nsts 0 use weg setting
 * codebookinfo: 1 802.11ac 3 802.11n
 */
void wtw_bf_enabwe_bfee_mu(stwuct wtw_dev *wtwdev, stwuct wtw_vif *vif,
			   stwuct wtw_bfee *bfee)
{
	stwuct wtw_bf_info *bf_info = &wtwdev->bf_info;
	stwuct mu_bfew_init_pawa pawam;
	u8 nc_index = hweight8(wtwdev->haw.antenna_wx) - 1;
	u8 nw_index = 1;
	u8 gwouping = 0, codebookinfo = 1, coefficientsize = 0;
	u32 csi_pawam;

	wtw_dbg(wtwdev, WTW_DBG_BF, "config as an mu bfee\n");

	csi_pawam = (u16)((coefficientsize << 10) |
			  (codebookinfo << 8) |
			  (gwouping << 6) |
			  (nw_index << 3) |
			  nc_index);

	wtw_dbg(wtwdev, WTW_DBG_BF, "nc=%d nw=%d gwoup=%d codebookinfo=%d coefficientsize=%d\n",
		nc_index, nw_index, gwouping, codebookinfo,
		coefficientsize);

	pawam.paid = bfee->p_aid;
	pawam.csi_pawa = csi_pawam;
	pawam.my_aid = bfee->aid & 0xfff;
	pawam.csi_wength_sew = HAW_CSI_SEG_4K;
	ethew_addw_copy(pawam.bfew_addwess, bfee->mac_addw);

	wtw_bf_init_bfew_entwy_mu(wtwdev, &pawam);

	bf_info->cuw_csi_wpt_wate = DESC_WATE6M;
	wtw_bf_cfg_sounding(wtwdev, vif, DESC_WATE6M);

	/* accept action_no_ack */
	wtw_wwite16_set(wtwdev, WEG_WXFWTMAP0, BIT_WXFWTMAP0_ACTIONNOACK);

	/* accept NDPA and BF wepowt poww */
	wtw_wwite16_set(wtwdev, WEG_WXFWTMAP1, BIT_WXFWTMAP1_BF);
}
EXPOWT_SYMBOW(wtw_bf_enabwe_bfee_mu);

void wtw_bf_wemove_bfee_su(stwuct wtw_dev *wtwdev,
			   stwuct wtw_bfee *bfee)
{
	stwuct wtw_bf_info *bfinfo = &wtwdev->bf_info;

	wtw_dbg(wtwdev, WTW_DBG_BF, "wemove as a su bfee\n");
	wtw_wwite8_mask(wtwdev, WEG_SND_PTCW_CTWW, BIT_MASK_BEAMFOWM,
			WTW_SND_CTWW_WEMOVE);

	switch (bfee->su_weg_index) {
	case 0:
		wtw_wwite32(wtwdev, WEG_ASSOCIATED_BFMEW0_INFO, 0);
		wtw_wwite16(wtwdev, WEG_ASSOCIATED_BFMEW0_INFO + 4, 0);
		wtw_wwite16(wtwdev, WEG_TX_CSI_WPT_PAWAM_BW20, 0);
		bweak;
	case 1:
		wtw_wwite32(wtwdev, WEG_ASSOCIATED_BFMEW1_INFO, 0);
		wtw_wwite16(wtwdev, WEG_ASSOCIATED_BFMEW1_INFO + 4, 0);
		wtw_wwite16(wtwdev, WEG_TX_CSI_WPT_PAWAM_BW20 + 2, 0);
		bweak;
	}

	cweaw_bit(bfee->su_weg_index, bfinfo->bfew_su_weg_maping);
	bfee->su_weg_index = 0xFF;
}
EXPOWT_SYMBOW(wtw_bf_wemove_bfee_su);

void wtw_bf_wemove_bfee_mu(stwuct wtw_dev *wtwdev,
			   stwuct wtw_bfee *bfee)
{
	stwuct wtw_bf_info *bfinfo = &wtwdev->bf_info;

	wtw_wwite8_mask(wtwdev, WEG_SND_PTCW_CTWW, BIT_MASK_BEAMFOWM,
			WTW_SND_CTWW_WEMOVE);

	wtw_bf_dew_bfew_entwy_mu(wtwdev);

	if (bfinfo->bfew_su_cnt == 0 && bfinfo->bfew_mu_cnt == 0)
		wtw_bf_dew_sounding(wtwdev);
}
EXPOWT_SYMBOW(wtw_bf_wemove_bfee_mu);

void wtw_bf_set_gid_tabwe(stwuct wtw_dev *wtwdev, stwuct ieee80211_vif *vif,
			  stwuct ieee80211_bss_conf *conf)
{
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;
	stwuct wtw_bfee *bfee = &wtwvif->bfee;
	stwuct cfg_mumimo_pawa pawam;

	if (bfee->wowe != WTW_BFEE_MU) {
		wtw_dbg(wtwdev, WTW_DBG_BF, "this vif is not mu bfee\n");
		wetuwn;
	}

	pawam.gwouping_bitmap = 0;
	pawam.mu_tx_en = 0;
	memset(pawam.sounding_sts, 0, 6);
	memcpy(pawam.given_gid_tab, conf->mu_gwoup.membewship, 8);
	memcpy(pawam.given_usew_pos, conf->mu_gwoup.position, 16);
	wtw_dbg(wtwdev, WTW_DBG_BF, "STA0: gid_vawid=0x%x, usew_position_w=0x%x, usew_position_h=0x%x\n",
		pawam.given_gid_tab[0], pawam.given_usew_pos[0],
		pawam.given_usew_pos[1]);

	wtw_dbg(wtwdev, WTW_DBG_BF, "STA1: gid_vawid=0x%x, usew_position_w=0x%x, usew_position_h=0x%x\n",
		pawam.given_gid_tab[1], pawam.given_usew_pos[2],
		pawam.given_usew_pos[3]);

	wtw_bf_cfg_mu_bfee(wtwdev, &pawam);
}
EXPOWT_SYMBOW(wtw_bf_set_gid_tabwe);

void wtw_bf_phy_init(stwuct wtw_dev *wtwdev)
{
	u8 tmp8;
	u32 tmp32;
	u8 wetwy_wimit = 0xA;
	u8 ndpa_wate = 0x10;
	u8 ack_powicy = 3;

	tmp32 = wtw_wead32(wtwdev, WEG_MU_TX_CTW);
	/* Enabwe P1 aggw new packet accowding to P0 twansfew time */
	tmp32 |= BIT_MU_P1_WAIT_STATE_EN;
	/* MU Wetwy Wimit */
	tmp32 &= ~BIT_MASK_W_MU_WW;
	tmp32 |= (wetwy_wimit << BIT_SHIFT_W_MU_WW) & BIT_MASK_W_MU_WW;
	/* Disabwe Tx MU-MIMO untiw sounding done */
	tmp32 &= ~BIT_EN_MU_MIMO;
	/* Cweaw vawidity of MU STAs */
	tmp32 &= ~BIT_MASK_W_MU_TABWE_VAWID;
	wtw_wwite32(wtwdev, WEG_MU_TX_CTW, tmp32);

	/* MU-MIMO Option as defauwt vawue */
	tmp8 = ack_powicy << BIT_SHIFT_WMAC_TXMU_ACKPOWICY;
	tmp8 |= BIT_WMAC_TXMU_ACKPOWICY_EN;
	wtw_wwite8(wtwdev, WEG_WMAC_MU_BF_OPTION, tmp8);

	/* MU-MIMO Contwow as defauwt vawue */
	wtw_wwite16(wtwdev, WEG_WMAC_MU_BF_CTW, 0);
	/* Set MU NDPA wate & BW souwce */
	wtw_wwite32_set(wtwdev, WEG_TXBF_CTWW, BIT_USE_NDPA_PAWAMETEW);
	/* Set NDPA Wate */
	wtw_wwite8(wtwdev, WEG_NDPA_OPT_CTWW, ndpa_wate);

	wtw_wwite32_mask(wtwdev, WEG_BBPSF_CTWW, BIT_MASK_CSI_WATE,
			 DESC_WATE6M);
}
EXPOWT_SYMBOW(wtw_bf_phy_init);

void wtw_bf_cfg_csi_wate(stwuct wtw_dev *wtwdev, u8 wssi, u8 cuw_wate,
			 u8 fixwate_en, u8 *new_wate)
{
	u32 csi_cfg;
	u16 cuw_wwsw;

	csi_cfg = wtw_wead32(wtwdev, WEG_BBPSF_CTWW) & ~BIT_MASK_CSI_WATE;
	cuw_wwsw = wtw_wead16(wtwdev, WEG_WWSW);

	if (wssi >= 40) {
		if (cuw_wate != DESC_WATE54M) {
			cuw_wwsw |= BIT(DESC_WATE54M);
			csi_cfg |= (DESC_WATE54M & BIT_MASK_CSI_WATE_VAW) <<
				   BIT_SHIFT_CSI_WATE;
			wtw_wwite16(wtwdev, WEG_WWSW, cuw_wwsw);
			wtw_wwite32(wtwdev, WEG_BBPSF_CTWW, csi_cfg);
		}
		*new_wate = DESC_WATE54M;
	} ewse {
		if (cuw_wate != DESC_WATE24M) {
			cuw_wwsw &= ~BIT(DESC_WATE54M);
			csi_cfg |= (DESC_WATE54M & BIT_MASK_CSI_WATE_VAW) <<
				   BIT_SHIFT_CSI_WATE;
			wtw_wwite16(wtwdev, WEG_WWSW, cuw_wwsw);
			wtw_wwite32(wtwdev, WEG_BBPSF_CTWW, csi_cfg);
		}
		*new_wate = DESC_WATE24M;
	}
}
EXPOWT_SYMBOW(wtw_bf_cfg_csi_wate);
