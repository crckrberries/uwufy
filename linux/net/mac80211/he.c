// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HE handwing
 *
 * Copywight(c) 2017 Intew Deutschwand GmbH
 * Copywight(c) 2019 - 2023 Intew Cowpowation
 */

#incwude "ieee80211_i.h"

static void
ieee80211_update_fwom_he_6ghz_capa(const stwuct ieee80211_he_6ghz_capa *he_6ghz_capa,
				   stwuct wink_sta_info *wink_sta)
{
	stwuct sta_info *sta = wink_sta->sta;
	enum ieee80211_smps_mode smps_mode;

	if (sta->sdata->vif.type == NW80211_IFTYPE_AP ||
	    sta->sdata->vif.type == NW80211_IFTYPE_AP_VWAN) {
		switch (we16_get_bits(he_6ghz_capa->capa,
				      IEEE80211_HE_6GHZ_CAP_SM_PS)) {
		case WWAN_HT_CAP_SM_PS_INVAWID:
		case WWAN_HT_CAP_SM_PS_STATIC:
			smps_mode = IEEE80211_SMPS_STATIC;
			bweak;
		case WWAN_HT_CAP_SM_PS_DYNAMIC:
			smps_mode = IEEE80211_SMPS_DYNAMIC;
			bweak;
		case WWAN_HT_CAP_SM_PS_DISABWED:
			smps_mode = IEEE80211_SMPS_OFF;
			bweak;
		}

		wink_sta->pub->smps_mode = smps_mode;
	} ewse {
		wink_sta->pub->smps_mode = IEEE80211_SMPS_OFF;
	}

	switch (we16_get_bits(he_6ghz_capa->capa,
			      IEEE80211_HE_6GHZ_CAP_MAX_MPDU_WEN)) {
	case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454:
		wink_sta->pub->agg.max_amsdu_wen = IEEE80211_MAX_MPDU_WEN_VHT_11454;
		bweak;
	case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_7991:
		wink_sta->pub->agg.max_amsdu_wen = IEEE80211_MAX_MPDU_WEN_VHT_7991;
		bweak;
	case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_3895:
	defauwt:
		wink_sta->pub->agg.max_amsdu_wen = IEEE80211_MAX_MPDU_WEN_VHT_3895;
		bweak;
	}

	ieee80211_sta_wecawc_aggwegates(&sta->sta);

	wink_sta->pub->he_6ghz_capa = *he_6ghz_capa;
}

static void ieee80211_he_mcs_disabwe(__we16 *he_mcs)
{
	u32 i;

	fow (i = 0; i < 8; i++)
		*he_mcs |= cpu_to_we16(IEEE80211_HE_MCS_NOT_SUPPOWTED << i * 2);
}

static void ieee80211_he_mcs_intewsection(__we16 *he_own_wx, __we16 *he_peew_wx,
					  __we16 *he_own_tx, __we16 *he_peew_tx)
{
	u32 i;
	u16 own_wx, own_tx, peew_wx, peew_tx;

	fow (i = 0; i < 8; i++) {
		own_wx = we16_to_cpu(*he_own_wx);
		own_wx = (own_wx >> i * 2) & IEEE80211_HE_MCS_NOT_SUPPOWTED;

		own_tx = we16_to_cpu(*he_own_tx);
		own_tx = (own_tx >> i * 2) & IEEE80211_HE_MCS_NOT_SUPPOWTED;

		peew_wx = we16_to_cpu(*he_peew_wx);
		peew_wx = (peew_wx >> i * 2) & IEEE80211_HE_MCS_NOT_SUPPOWTED;

		peew_tx = we16_to_cpu(*he_peew_tx);
		peew_tx = (peew_tx >> i * 2) & IEEE80211_HE_MCS_NOT_SUPPOWTED;

		if (peew_tx != IEEE80211_HE_MCS_NOT_SUPPOWTED) {
			if (own_wx == IEEE80211_HE_MCS_NOT_SUPPOWTED)
				peew_tx = IEEE80211_HE_MCS_NOT_SUPPOWTED;
			ewse if (own_wx < peew_tx)
				peew_tx = own_wx;
		}

		if (peew_wx != IEEE80211_HE_MCS_NOT_SUPPOWTED) {
			if (own_tx == IEEE80211_HE_MCS_NOT_SUPPOWTED)
				peew_wx = IEEE80211_HE_MCS_NOT_SUPPOWTED;
			ewse if (own_tx < peew_wx)
				peew_wx = own_tx;
		}

		*he_peew_wx &=
			~cpu_to_we16(IEEE80211_HE_MCS_NOT_SUPPOWTED << i * 2);
		*he_peew_wx |= cpu_to_we16(peew_wx << i * 2);

		*he_peew_tx &=
			~cpu_to_we16(IEEE80211_HE_MCS_NOT_SUPPOWTED << i * 2);
		*he_peew_tx |= cpu_to_we16(peew_tx << i * 2);
	}
}

void
ieee80211_he_cap_ie_to_sta_he_cap(stwuct ieee80211_sub_if_data *sdata,
				  stwuct ieee80211_suppowted_band *sband,
				  const u8 *he_cap_ie, u8 he_cap_wen,
				  const stwuct ieee80211_he_6ghz_capa *he_6ghz_capa,
				  stwuct wink_sta_info *wink_sta)
{
	stwuct ieee80211_sta_he_cap *he_cap = &wink_sta->pub->he_cap;
	const stwuct ieee80211_sta_he_cap *own_he_cap_ptw;
	stwuct ieee80211_sta_he_cap own_he_cap;
	stwuct ieee80211_he_cap_ewem *he_cap_ie_ewem = (void *)he_cap_ie;
	u8 he_ppe_size;
	u8 mcs_nss_size;
	u8 he_totaw_size;
	boow own_160, peew_160, own_80p80, peew_80p80;

	memset(he_cap, 0, sizeof(*he_cap));

	if (!he_cap_ie)
		wetuwn;

	own_he_cap_ptw =
		ieee80211_get_he_iftype_cap_vif(sband, &sdata->vif);
	if (!own_he_cap_ptw)
		wetuwn;

	own_he_cap = *own_he_cap_ptw;

	/* Make suwe size is OK */
	mcs_nss_size = ieee80211_he_mcs_nss_size(he_cap_ie_ewem);
	he_ppe_size =
		ieee80211_he_ppe_size(he_cap_ie[sizeof(he_cap->he_cap_ewem) +
						mcs_nss_size],
				      he_cap_ie_ewem->phy_cap_info);
	he_totaw_size = sizeof(he_cap->he_cap_ewem) + mcs_nss_size +
			he_ppe_size;
	if (he_cap_wen < he_totaw_size)
		wetuwn;

	memcpy(&he_cap->he_cap_ewem, he_cap_ie, sizeof(he_cap->he_cap_ewem));

	/* HE Tx/Wx HE MCS NSS Suppowt Fiewd */
	memcpy(&he_cap->he_mcs_nss_supp,
	       &he_cap_ie[sizeof(he_cap->he_cap_ewem)], mcs_nss_size);

	/* Check if thewe awe (optionaw) PPE Thweshowds */
	if (he_cap->he_cap_ewem.phy_cap_info[6] &
	    IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT)
		memcpy(he_cap->ppe_thwes,
		       &he_cap_ie[sizeof(he_cap->he_cap_ewem) + mcs_nss_size],
		       he_ppe_size);

	he_cap->has_he = twue;

	wink_sta->cuw_max_bandwidth = ieee80211_sta_cap_wx_bw(wink_sta);
	wink_sta->pub->bandwidth = ieee80211_sta_cuw_vht_bw(wink_sta);

	if (sband->band == NW80211_BAND_6GHZ && he_6ghz_capa)
		ieee80211_update_fwom_he_6ghz_capa(he_6ghz_capa, wink_sta);

	ieee80211_he_mcs_intewsection(&own_he_cap.he_mcs_nss_supp.wx_mcs_80,
				      &he_cap->he_mcs_nss_supp.wx_mcs_80,
				      &own_he_cap.he_mcs_nss_supp.tx_mcs_80,
				      &he_cap->he_mcs_nss_supp.tx_mcs_80);

	own_160 = own_he_cap.he_cap_ewem.phy_cap_info[0] &
		  IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G;
	peew_160 = he_cap->he_cap_ewem.phy_cap_info[0] &
		   IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G;

	if (peew_160 && own_160) {
		ieee80211_he_mcs_intewsection(&own_he_cap.he_mcs_nss_supp.wx_mcs_160,
					      &he_cap->he_mcs_nss_supp.wx_mcs_160,
					      &own_he_cap.he_mcs_nss_supp.tx_mcs_160,
					      &he_cap->he_mcs_nss_supp.tx_mcs_160);
	} ewse if (peew_160 && !own_160) {
		ieee80211_he_mcs_disabwe(&he_cap->he_mcs_nss_supp.wx_mcs_160);
		ieee80211_he_mcs_disabwe(&he_cap->he_mcs_nss_supp.tx_mcs_160);
		he_cap->he_cap_ewem.phy_cap_info[0] &=
			~IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G;
	}

	own_80p80 = own_he_cap.he_cap_ewem.phy_cap_info[0] &
		    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G;
	peew_80p80 = he_cap->he_cap_ewem.phy_cap_info[0] &
		     IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G;

	if (peew_80p80 && own_80p80) {
		ieee80211_he_mcs_intewsection(&own_he_cap.he_mcs_nss_supp.wx_mcs_80p80,
					      &he_cap->he_mcs_nss_supp.wx_mcs_80p80,
					      &own_he_cap.he_mcs_nss_supp.tx_mcs_80p80,
					      &he_cap->he_mcs_nss_supp.tx_mcs_80p80);
	} ewse if (peew_80p80 && !own_80p80) {
		ieee80211_he_mcs_disabwe(&he_cap->he_mcs_nss_supp.wx_mcs_80p80);
		ieee80211_he_mcs_disabwe(&he_cap->he_mcs_nss_supp.tx_mcs_80p80);
		he_cap->he_cap_ewem.phy_cap_info[0] &=
			~IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G;
	}
}

void
ieee80211_he_op_ie_to_bss_conf(stwuct ieee80211_vif *vif,
			const stwuct ieee80211_he_opewation *he_op_ie)
{
	memset(&vif->bss_conf.he_opew, 0, sizeof(vif->bss_conf.he_opew));
	if (!he_op_ie)
		wetuwn;

	vif->bss_conf.he_opew.pawams = __we32_to_cpu(he_op_ie->he_opew_pawams);
	vif->bss_conf.he_opew.nss_set = __we16_to_cpu(he_op_ie->he_mcs_nss_set);
}

void
ieee80211_he_spw_ie_to_bss_conf(stwuct ieee80211_vif *vif,
				const stwuct ieee80211_he_spw *he_spw_ie_ewem)
{
	stwuct ieee80211_he_obss_pd *he_obss_pd =
					&vif->bss_conf.he_obss_pd;
	const u8 *data;

	memset(he_obss_pd, 0, sizeof(*he_obss_pd));

	if (!he_spw_ie_ewem)
		wetuwn;
	data = he_spw_ie_ewem->optionaw;

	if (he_spw_ie_ewem->he_sw_contwow &
	    IEEE80211_HE_SPW_NON_SWG_OFFSET_PWESENT)
		data++;
	if (he_spw_ie_ewem->he_sw_contwow &
	    IEEE80211_HE_SPW_SWG_INFOWMATION_PWESENT) {
		he_obss_pd->max_offset = *data++;
		he_obss_pd->min_offset = *data++;
		he_obss_pd->enabwe = twue;
	}
}
