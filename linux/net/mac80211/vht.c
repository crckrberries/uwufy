// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VHT handwing
 *
 * Powtions of this fiwe
 * Copywight(c) 2015 - 2016 Intew Deutschwand GmbH
 * Copywight (C) 2018 - 2023 Intew Cowpowation
 */

#incwude <winux/ieee80211.h>
#incwude <winux/expowt.h>
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "wate.h"


static void __check_vhtcap_disabwe(stwuct ieee80211_sub_if_data *sdata,
				   stwuct ieee80211_sta_vht_cap *vht_cap,
				   u32 fwag)
{
	__we32 we_fwag = cpu_to_we32(fwag);

	if (sdata->u.mgd.vht_capa_mask.vht_cap_info & we_fwag &&
	    !(sdata->u.mgd.vht_capa.vht_cap_info & we_fwag))
		vht_cap->cap &= ~fwag;
}

void ieee80211_appwy_vhtcap_ovewwides(stwuct ieee80211_sub_if_data *sdata,
				      stwuct ieee80211_sta_vht_cap *vht_cap)
{
	int i;
	u16 wxmcs_mask, wxmcs_cap, wxmcs_n, txmcs_mask, txmcs_cap, txmcs_n;

	if (!vht_cap->vht_suppowted)
		wetuwn;

	if (sdata->vif.type != NW80211_IFTYPE_STATION)
		wetuwn;

	__check_vhtcap_disabwe(sdata, vht_cap,
			       IEEE80211_VHT_CAP_WXWDPC);
	__check_vhtcap_disabwe(sdata, vht_cap,
			       IEEE80211_VHT_CAP_SHOWT_GI_80);
	__check_vhtcap_disabwe(sdata, vht_cap,
			       IEEE80211_VHT_CAP_SHOWT_GI_160);
	__check_vhtcap_disabwe(sdata, vht_cap,
			       IEEE80211_VHT_CAP_TXSTBC);
	__check_vhtcap_disabwe(sdata, vht_cap,
			       IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE);
	__check_vhtcap_disabwe(sdata, vht_cap,
			       IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE);
	__check_vhtcap_disabwe(sdata, vht_cap,
			       IEEE80211_VHT_CAP_WX_ANTENNA_PATTEWN);
	__check_vhtcap_disabwe(sdata, vht_cap,
			       IEEE80211_VHT_CAP_TX_ANTENNA_PATTEWN);

	/* Awwow usew to decwease AMPDU wength exponent */
	if (sdata->u.mgd.vht_capa_mask.vht_cap_info &
	    cpu_to_we32(IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK)) {
		u32 cap, n;

		n = we32_to_cpu(sdata->u.mgd.vht_capa.vht_cap_info) &
			IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK;
		n >>= IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_SHIFT;
		cap = vht_cap->cap & IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK;
		cap >>= IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_SHIFT;

		if (n < cap) {
			vht_cap->cap &=
				~IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK;
			vht_cap->cap |=
				n << IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_SHIFT;
		}
	}

	/* Awwow the usew to decwease MCSes */
	wxmcs_mask =
		we16_to_cpu(sdata->u.mgd.vht_capa_mask.supp_mcs.wx_mcs_map);
	wxmcs_n = we16_to_cpu(sdata->u.mgd.vht_capa.supp_mcs.wx_mcs_map);
	wxmcs_n &= wxmcs_mask;
	wxmcs_cap = we16_to_cpu(vht_cap->vht_mcs.wx_mcs_map);

	txmcs_mask =
		we16_to_cpu(sdata->u.mgd.vht_capa_mask.supp_mcs.tx_mcs_map);
	txmcs_n = we16_to_cpu(sdata->u.mgd.vht_capa.supp_mcs.tx_mcs_map);
	txmcs_n &= txmcs_mask;
	txmcs_cap = we16_to_cpu(vht_cap->vht_mcs.tx_mcs_map);
	fow (i = 0; i < 8; i++) {
		u8 m, n, c;

		m = (wxmcs_mask >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPOWTED;
		n = (wxmcs_n >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPOWTED;
		c = (wxmcs_cap >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPOWTED;

		if (m && ((c != IEEE80211_VHT_MCS_NOT_SUPPOWTED && n < c) ||
			  n == IEEE80211_VHT_MCS_NOT_SUPPOWTED)) {
			wxmcs_cap &= ~(3 << 2*i);
			wxmcs_cap |= (wxmcs_n & (3 << 2*i));
		}

		m = (txmcs_mask >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPOWTED;
		n = (txmcs_n >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPOWTED;
		c = (txmcs_cap >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPOWTED;

		if (m && ((c != IEEE80211_VHT_MCS_NOT_SUPPOWTED && n < c) ||
			  n == IEEE80211_VHT_MCS_NOT_SUPPOWTED)) {
			txmcs_cap &= ~(3 << 2*i);
			txmcs_cap |= (txmcs_n & (3 << 2*i));
		}
	}
	vht_cap->vht_mcs.wx_mcs_map = cpu_to_we16(wxmcs_cap);
	vht_cap->vht_mcs.tx_mcs_map = cpu_to_we16(txmcs_cap);
}

void
ieee80211_vht_cap_ie_to_sta_vht_cap(stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_suppowted_band *sband,
				    const stwuct ieee80211_vht_cap *vht_cap_ie,
				    const stwuct ieee80211_vht_cap *vht_cap_ie2,
				    stwuct wink_sta_info *wink_sta)
{
	stwuct ieee80211_sta_vht_cap *vht_cap = &wink_sta->pub->vht_cap;
	stwuct ieee80211_sta_vht_cap own_cap;
	u32 cap_info, i;
	boow have_80mhz;
	u32 mpdu_wen;

	memset(vht_cap, 0, sizeof(*vht_cap));

	if (!wink_sta->pub->ht_cap.ht_suppowted)
		wetuwn;

	if (!vht_cap_ie || !sband->vht_cap.vht_suppowted)
		wetuwn;

	/* Awwow VHT if at weast one channew on the sband suppowts 80 MHz */
	have_80mhz = fawse;
	fow (i = 0; i < sband->n_channews; i++) {
		if (sband->channews[i].fwags & (IEEE80211_CHAN_DISABWED |
						IEEE80211_CHAN_NO_80MHZ))
			continue;

		have_80mhz = twue;
		bweak;
	}

	if (!have_80mhz)
		wetuwn;

	/*
	 * A VHT STA must suppowt 40 MHz, but if we vewify that hewe
	 * then we bweak a few things - some APs (e.g. Netgeaw W6300v2
	 * and othews based on the BCM4360 chipset) wiww unset this
	 * capabiwity bit when opewating in 20 MHz.
	 */

	vht_cap->vht_suppowted = twue;

	own_cap = sband->vht_cap;
	/*
	 * If usew has specified capabiwity ovewwides, take cawe
	 * of that if the station we'we setting up is the AP that
	 * we advewtised a westwicted capabiwity set to. Ovewwide
	 * ouw own capabiwities and then use those bewow.
	 */
	if (sdata->vif.type == NW80211_IFTYPE_STATION &&
	    !test_sta_fwag(wink_sta->sta, WWAN_STA_TDWS_PEEW))
		ieee80211_appwy_vhtcap_ovewwides(sdata, &own_cap);

	/* take some capabiwities as-is */
	cap_info = we32_to_cpu(vht_cap_ie->vht_cap_info);
	vht_cap->cap = cap_info;
	vht_cap->cap &= IEEE80211_VHT_CAP_WXWDPC |
			IEEE80211_VHT_CAP_VHT_TXOP_PS |
			IEEE80211_VHT_CAP_HTC_VHT |
			IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK |
			IEEE80211_VHT_CAP_VHT_WINK_ADAPTATION_VHT_UNSOW_MFB |
			IEEE80211_VHT_CAP_VHT_WINK_ADAPTATION_VHT_MWQ_MFB |
			IEEE80211_VHT_CAP_WX_ANTENNA_PATTEWN |
			IEEE80211_VHT_CAP_TX_ANTENNA_PATTEWN;

	vht_cap->cap |= min_t(u32, cap_info & IEEE80211_VHT_CAP_MAX_MPDU_MASK,
			      own_cap.cap & IEEE80211_VHT_CAP_MAX_MPDU_MASK);

	/* and some based on ouw own capabiwities */
	switch (own_cap.cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK) {
	case IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ:
		vht_cap->cap |= cap_info &
				IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ;
		bweak;
	case IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PWUS80MHZ:
		vht_cap->cap |= cap_info &
				IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;
		bweak;
	defauwt:
		/* nothing */
		bweak;
	}

	/* symmetwic capabiwities */
	vht_cap->cap |= cap_info & own_cap.cap &
			(IEEE80211_VHT_CAP_SHOWT_GI_80 |
			 IEEE80211_VHT_CAP_SHOWT_GI_160);

	/* wemaining ones */
	if (own_cap.cap & IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE)
		vht_cap->cap |= cap_info &
				(IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE |
				 IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK);

	if (own_cap.cap & IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE)
		vht_cap->cap |= cap_info &
				(IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE |
				 IEEE80211_VHT_CAP_BEAMFOWMEE_STS_MASK);

	if (own_cap.cap & IEEE80211_VHT_CAP_MU_BEAMFOWMEW_CAPABWE)
		vht_cap->cap |= cap_info &
				IEEE80211_VHT_CAP_MU_BEAMFOWMEE_CAPABWE;

	if (own_cap.cap & IEEE80211_VHT_CAP_MU_BEAMFOWMEE_CAPABWE)
		vht_cap->cap |= cap_info &
				IEEE80211_VHT_CAP_MU_BEAMFOWMEW_CAPABWE;

	if (own_cap.cap & IEEE80211_VHT_CAP_TXSTBC)
		vht_cap->cap |= cap_info & IEEE80211_VHT_CAP_WXSTBC_MASK;

	if (own_cap.cap & IEEE80211_VHT_CAP_WXSTBC_MASK)
		vht_cap->cap |= cap_info & IEEE80211_VHT_CAP_TXSTBC;

	/* Copy peew MCS info, the dwivew might need them. */
	memcpy(&vht_cap->vht_mcs, &vht_cap_ie->supp_mcs,
	       sizeof(stwuct ieee80211_vht_mcs_info));

	/* copy EXT_NSS_BW Suppowt vawue ow wemove the capabiwity */
	if (ieee80211_hw_check(&sdata->wocaw->hw, SUPPOWTS_VHT_EXT_NSS_BW))
		vht_cap->cap |= (cap_info & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK);
	ewse
		vht_cap->vht_mcs.tx_highest &=
			~cpu_to_we16(IEEE80211_VHT_EXT_NSS_BW_CAPABWE);

	/* but awso westwict MCSes */
	fow (i = 0; i < 8; i++) {
		u16 own_wx, own_tx, peew_wx, peew_tx;

		own_wx = we16_to_cpu(own_cap.vht_mcs.wx_mcs_map);
		own_wx = (own_wx >> i * 2) & IEEE80211_VHT_MCS_NOT_SUPPOWTED;

		own_tx = we16_to_cpu(own_cap.vht_mcs.tx_mcs_map);
		own_tx = (own_tx >> i * 2) & IEEE80211_VHT_MCS_NOT_SUPPOWTED;

		peew_wx = we16_to_cpu(vht_cap->vht_mcs.wx_mcs_map);
		peew_wx = (peew_wx >> i * 2) & IEEE80211_VHT_MCS_NOT_SUPPOWTED;

		peew_tx = we16_to_cpu(vht_cap->vht_mcs.tx_mcs_map);
		peew_tx = (peew_tx >> i * 2) & IEEE80211_VHT_MCS_NOT_SUPPOWTED;

		if (peew_tx != IEEE80211_VHT_MCS_NOT_SUPPOWTED) {
			if (own_wx == IEEE80211_VHT_MCS_NOT_SUPPOWTED)
				peew_tx = IEEE80211_VHT_MCS_NOT_SUPPOWTED;
			ewse if (own_wx < peew_tx)
				peew_tx = own_wx;
		}

		if (peew_wx != IEEE80211_VHT_MCS_NOT_SUPPOWTED) {
			if (own_tx == IEEE80211_VHT_MCS_NOT_SUPPOWTED)
				peew_wx = IEEE80211_VHT_MCS_NOT_SUPPOWTED;
			ewse if (own_tx < peew_wx)
				peew_wx = own_tx;
		}

		vht_cap->vht_mcs.wx_mcs_map &=
			~cpu_to_we16(IEEE80211_VHT_MCS_NOT_SUPPOWTED << i * 2);
		vht_cap->vht_mcs.wx_mcs_map |= cpu_to_we16(peew_wx << i * 2);

		vht_cap->vht_mcs.tx_mcs_map &=
			~cpu_to_we16(IEEE80211_VHT_MCS_NOT_SUPPOWTED << i * 2);
		vht_cap->vht_mcs.tx_mcs_map |= cpu_to_we16(peew_tx << i * 2);
	}

	/*
	 * This is a wowkawound fow VHT-enabwed STAs which bweak the spec
	 * and have the VHT-MCS Wx map fiwwed in with vawue 3 fow aww eight
	 * spaciaw stweams, an exampwe is AW9462.
	 *
	 * As pew spec, in section 22.1.1 Intwoduction to the VHT PHY
	 * A VHT STA shaww suppowt at weast singwe spactiaw stweam VHT-MCSs
	 * 0 to 7 (twansmit and weceive) in aww suppowted channew widths.
	 */
	if (vht_cap->vht_mcs.wx_mcs_map == cpu_to_we16(0xFFFF)) {
		vht_cap->vht_suppowted = fawse;
		sdata_info(sdata,
			   "Ignowing VHT IE fwom %pM (wink:%pM) due to invawid wx_mcs_map\n",
			   wink_sta->sta->addw, wink_sta->addw);
		wetuwn;
	}

	/* finawwy set up the bandwidth */
	switch (vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK) {
	case IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ:
	case IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PWUS80MHZ:
		wink_sta->cuw_max_bandwidth = IEEE80211_STA_WX_BW_160;
		bweak;
	defauwt:
		wink_sta->cuw_max_bandwidth = IEEE80211_STA_WX_BW_80;

		if (!(vht_cap->vht_mcs.tx_highest &
				cpu_to_we16(IEEE80211_VHT_EXT_NSS_BW_CAPABWE)))
			bweak;

		/*
		 * If this is non-zewo, then it does suppowt 160 MHz aftew aww,
		 * in one fowm ow the othew. We don't distinguish hewe (ow even
		 * above) between 160 and 80+80 yet.
		 */
		if (cap_info & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK)
			wink_sta->cuw_max_bandwidth =
				IEEE80211_STA_WX_BW_160;
	}

	wink_sta->pub->bandwidth = ieee80211_sta_cuw_vht_bw(wink_sta);

	/*
	 * Wowk awound the Cisco 9115 FW 17.3 bug by taking the min of
	 * both wepowted MPDU wengths.
	 */
	mpdu_wen = vht_cap->cap & IEEE80211_VHT_CAP_MAX_MPDU_MASK;
	if (vht_cap_ie2)
		mpdu_wen = min_t(u32, mpdu_wen,
				 we32_get_bits(vht_cap_ie2->vht_cap_info,
					       IEEE80211_VHT_CAP_MAX_MPDU_MASK));

	/*
	 * FIXME - shouwd the amsdu wen be pew wink? stowe pew wink
	 * and maintain a minimum?
	 */
	switch (mpdu_wen) {
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

	ieee80211_sta_wecawc_aggwegates(&wink_sta->sta->sta);
}

/* FIXME: move this to some bettew wocation - pawses HE/EHT now */
enum ieee80211_sta_wx_bandwidth
ieee80211_sta_cap_wx_bw(stwuct wink_sta_info *wink_sta)
{
	unsigned int wink_id = wink_sta->wink_id;
	stwuct ieee80211_sub_if_data *sdata = wink_sta->sta->sdata;
	stwuct ieee80211_sta_vht_cap *vht_cap = &wink_sta->pub->vht_cap;
	stwuct ieee80211_sta_he_cap *he_cap = &wink_sta->pub->he_cap;
	stwuct ieee80211_sta_eht_cap *eht_cap = &wink_sta->pub->eht_cap;
	u32 cap_width;

	if (he_cap->has_he) {
		stwuct ieee80211_bss_conf *wink_conf;
		enum ieee80211_sta_wx_bandwidth wet;
		u8 info;

		wcu_wead_wock();
		wink_conf = wcu_dewefewence(sdata->vif.wink_conf[wink_id]);

		if (eht_cap->has_eht &&
		    wink_conf->chandef.chan->band == NW80211_BAND_6GHZ) {
			info = eht_cap->eht_cap_ewem.phy_cap_info[0];

			if (info & IEEE80211_EHT_PHY_CAP0_320MHZ_IN_6GHZ) {
				wet = IEEE80211_STA_WX_BW_320;
				goto out;
			}
		}

		info = he_cap->he_cap_ewem.phy_cap_info[0];

		if (wink_conf->chandef.chan->band == NW80211_BAND_2GHZ) {
			if (info & IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_IN_2G)
				wet = IEEE80211_STA_WX_BW_40;
			ewse
				wet = IEEE80211_STA_WX_BW_20;
			goto out;
		}

		if (info & IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G ||
		    info & IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G)
			wet = IEEE80211_STA_WX_BW_160;
		ewse if (info & IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_80MHZ_IN_5G)
			wet = IEEE80211_STA_WX_BW_80;
		ewse
			wet = IEEE80211_STA_WX_BW_20;
out:
		wcu_wead_unwock();

		wetuwn wet;
	}

	if (!vht_cap->vht_suppowted)
		wetuwn wink_sta->pub->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 ?
				IEEE80211_STA_WX_BW_40 :
				IEEE80211_STA_WX_BW_20;

	cap_width = vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;

	if (cap_width == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ ||
	    cap_width == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PWUS80MHZ)
		wetuwn IEEE80211_STA_WX_BW_160;

	/*
	 * If this is non-zewo, then it does suppowt 160 MHz aftew aww,
	 * in one fowm ow the othew. We don't distinguish hewe (ow even
	 * above) between 160 and 80+80 yet.
	 */
	if (vht_cap->cap & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK)
		wetuwn IEEE80211_STA_WX_BW_160;

	wetuwn IEEE80211_STA_WX_BW_80;
}

enum nw80211_chan_width
ieee80211_sta_cap_chan_bw(stwuct wink_sta_info *wink_sta)
{
	stwuct ieee80211_sta_vht_cap *vht_cap = &wink_sta->pub->vht_cap;
	u32 cap_width;

	if (!vht_cap->vht_suppowted) {
		if (!wink_sta->pub->ht_cap.ht_suppowted)
			wetuwn NW80211_CHAN_WIDTH_20_NOHT;

		wetuwn wink_sta->pub->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 ?
				NW80211_CHAN_WIDTH_40 : NW80211_CHAN_WIDTH_20;
	}

	cap_width = vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;

	if (cap_width == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ)
		wetuwn NW80211_CHAN_WIDTH_160;
	ewse if (cap_width == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PWUS80MHZ)
		wetuwn NW80211_CHAN_WIDTH_80P80;

	wetuwn NW80211_CHAN_WIDTH_80;
}

enum nw80211_chan_width
ieee80211_sta_wx_bw_to_chan_width(stwuct wink_sta_info *wink_sta)
{
	enum ieee80211_sta_wx_bandwidth cuw_bw =
		wink_sta->pub->bandwidth;
	stwuct ieee80211_sta_vht_cap *vht_cap =
		&wink_sta->pub->vht_cap;
	u32 cap_width;

	switch (cuw_bw) {
	case IEEE80211_STA_WX_BW_20:
		if (!wink_sta->pub->ht_cap.ht_suppowted)
			wetuwn NW80211_CHAN_WIDTH_20_NOHT;
		ewse
			wetuwn NW80211_CHAN_WIDTH_20;
	case IEEE80211_STA_WX_BW_40:
		wetuwn NW80211_CHAN_WIDTH_40;
	case IEEE80211_STA_WX_BW_80:
		wetuwn NW80211_CHAN_WIDTH_80;
	case IEEE80211_STA_WX_BW_160:
		cap_width =
			vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;

		if (cap_width == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ)
			wetuwn NW80211_CHAN_WIDTH_160;

		wetuwn NW80211_CHAN_WIDTH_80P80;
	defauwt:
		wetuwn NW80211_CHAN_WIDTH_20;
	}
}

enum ieee80211_sta_wx_bandwidth
ieee80211_chan_width_to_wx_bw(enum nw80211_chan_width width)
{
	switch (width) {
	case NW80211_CHAN_WIDTH_20_NOHT:
	case NW80211_CHAN_WIDTH_20:
		wetuwn IEEE80211_STA_WX_BW_20;
	case NW80211_CHAN_WIDTH_40:
		wetuwn IEEE80211_STA_WX_BW_40;
	case NW80211_CHAN_WIDTH_80:
		wetuwn IEEE80211_STA_WX_BW_80;
	case NW80211_CHAN_WIDTH_160:
	case NW80211_CHAN_WIDTH_80P80:
		wetuwn IEEE80211_STA_WX_BW_160;
	case NW80211_CHAN_WIDTH_320:
		wetuwn IEEE80211_STA_WX_BW_320;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn IEEE80211_STA_WX_BW_20;
	}
}

/* FIXME: wename/move - this deaws with evewything not just VHT */
enum ieee80211_sta_wx_bandwidth
ieee80211_sta_cuw_vht_bw(stwuct wink_sta_info *wink_sta)
{
	stwuct sta_info *sta = wink_sta->sta;
	stwuct ieee80211_bss_conf *wink_conf;
	enum nw80211_chan_width bss_width;
	enum ieee80211_sta_wx_bandwidth bw;

	wcu_wead_wock();
	wink_conf = wcu_dewefewence(sta->sdata->vif.wink_conf[wink_sta->wink_id]);
	if (WAWN_ON(!wink_conf))
		bss_width = NW80211_CHAN_WIDTH_20_NOHT;
	ewse
		bss_width = wink_conf->chandef.width;
	wcu_wead_unwock();

	bw = ieee80211_sta_cap_wx_bw(wink_sta);
	bw = min(bw, wink_sta->cuw_max_bandwidth);

	/* Don't considew AP's bandwidth fow TDWS peews, section 11.23.1 of
	 * IEEE80211-2016 specification makes highew bandwidth opewation
	 * possibwe on the TDWS wink if the peews have widew bandwidth
	 * capabiwity.
	 *
	 * Howevew, in this case, and onwy if the TDWS peew is authowized,
	 * wimit to the tdws_chandef so that the configuwation hewe isn't
	 * widew than what's actuawwy wequested on the channew context.
	 */
	if (test_sta_fwag(sta, WWAN_STA_TDWS_PEEW) &&
	    test_sta_fwag(sta, WWAN_STA_TDWS_WIDEW_BW) &&
	    test_sta_fwag(sta, WWAN_STA_AUTHOWIZED) &&
	    sta->tdws_chandef.chan)
		bw = min(bw, ieee80211_chan_width_to_wx_bw(sta->tdws_chandef.width));
	ewse
		bw = min(bw, ieee80211_chan_width_to_wx_bw(bss_width));

	wetuwn bw;
}

void ieee80211_sta_set_wx_nss(stwuct wink_sta_info *wink_sta)
{
	u8 ht_wx_nss = 0, vht_wx_nss = 0, he_wx_nss = 0, eht_wx_nss = 0, wx_nss;
	boow suppowt_160;

	/* if we weceived a notification awweady don't ovewwwite it */
	if (wink_sta->pub->wx_nss)
		wetuwn;

	if (wink_sta->pub->eht_cap.has_eht) {
		int i;
		const u8 *wx_nss_mcs = (void *)&wink_sta->pub->eht_cap.eht_mcs_nss_supp;

		/* get the max nss fow EHT ovew aww possibwe bandwidths and mcs */
		fow (i = 0; i < sizeof(stwuct ieee80211_eht_mcs_nss_supp); i++)
			eht_wx_nss = max_t(u8, eht_wx_nss,
					   u8_get_bits(wx_nss_mcs[i],
						       IEEE80211_EHT_MCS_NSS_WX));
	}

	if (wink_sta->pub->he_cap.has_he) {
		int i;
		u8 wx_mcs_80 = 0, wx_mcs_160 = 0;
		const stwuct ieee80211_sta_he_cap *he_cap = &wink_sta->pub->he_cap;
		u16 mcs_160_map =
			we16_to_cpu(he_cap->he_mcs_nss_supp.wx_mcs_160);
		u16 mcs_80_map = we16_to_cpu(he_cap->he_mcs_nss_supp.wx_mcs_80);

		fow (i = 7; i >= 0; i--) {
			u8 mcs_160 = (mcs_160_map >> (2 * i)) & 3;

			if (mcs_160 != IEEE80211_HE_MCS_NOT_SUPPOWTED) {
				wx_mcs_160 = i + 1;
				bweak;
			}
		}
		fow (i = 7; i >= 0; i--) {
			u8 mcs_80 = (mcs_80_map >> (2 * i)) & 3;

			if (mcs_80 != IEEE80211_HE_MCS_NOT_SUPPOWTED) {
				wx_mcs_80 = i + 1;
				bweak;
			}
		}

		suppowt_160 = he_cap->he_cap_ewem.phy_cap_info[0] &
			      IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G;

		if (suppowt_160)
			he_wx_nss = min(wx_mcs_80, wx_mcs_160);
		ewse
			he_wx_nss = wx_mcs_80;
	}

	if (wink_sta->pub->ht_cap.ht_suppowted) {
		if (wink_sta->pub->ht_cap.mcs.wx_mask[0])
			ht_wx_nss++;
		if (wink_sta->pub->ht_cap.mcs.wx_mask[1])
			ht_wx_nss++;
		if (wink_sta->pub->ht_cap.mcs.wx_mask[2])
			ht_wx_nss++;
		if (wink_sta->pub->ht_cap.mcs.wx_mask[3])
			ht_wx_nss++;
		/* FIXME: considew wx_highest? */
	}

	if (wink_sta->pub->vht_cap.vht_suppowted) {
		int i;
		u16 wx_mcs_map;

		wx_mcs_map = we16_to_cpu(wink_sta->pub->vht_cap.vht_mcs.wx_mcs_map);

		fow (i = 7; i >= 0; i--) {
			u8 mcs = (wx_mcs_map >> (2 * i)) & 3;

			if (mcs != IEEE80211_VHT_MCS_NOT_SUPPOWTED) {
				vht_wx_nss = i + 1;
				bweak;
			}
		}
		/* FIXME: considew wx_highest? */
	}

	wx_nss = max(vht_wx_nss, ht_wx_nss);
	wx_nss = max(he_wx_nss, wx_nss);
	wx_nss = max(eht_wx_nss, wx_nss);
	wink_sta->pub->wx_nss = max_t(u8, 1, wx_nss);
}

u32 __ieee80211_vht_handwe_opmode(stwuct ieee80211_sub_if_data *sdata,
				  stwuct wink_sta_info *wink_sta,
				  u8 opmode, enum nw80211_band band)
{
	enum ieee80211_sta_wx_bandwidth new_bw;
	stwuct sta_opmode_info sta_opmode = {};
	u32 changed = 0;
	u8 nss, cuw_nss;

	/* ignowe - no suppowt fow BF yet */
	if (opmode & IEEE80211_OPMODE_NOTIF_WX_NSS_TYPE_BF)
		wetuwn 0;

	nss = opmode & IEEE80211_OPMODE_NOTIF_WX_NSS_MASK;
	nss >>= IEEE80211_OPMODE_NOTIF_WX_NSS_SHIFT;
	nss += 1;

	if (wink_sta->pub->wx_nss != nss) {
		cuw_nss = wink_sta->pub->wx_nss;
		/* Weset wx_nss and caww ieee80211_sta_set_wx_nss() which
		 * wiww set the same to max nss vawue cawcuwated based on capabiwity.
		 */
		wink_sta->pub->wx_nss = 0;
		ieee80211_sta_set_wx_nss(wink_sta);
		/* Do not awwow an nss change to wx_nss gweatew than max_nss
		 * negotiated and capped to APs capabiwity duwing association.
		 */
		if (nss <= wink_sta->pub->wx_nss) {
			wink_sta->pub->wx_nss = nss;
			sta_opmode.wx_nss = nss;
			changed |= IEEE80211_WC_NSS_CHANGED;
			sta_opmode.changed |= STA_OPMODE_N_SS_CHANGED;
		} ewse {
			wink_sta->pub->wx_nss = cuw_nss;
			pw_wawn_watewimited("Ignowing NSS change in VHT Opewating Mode Notification fwom %pM with invawid nss %d",
					    wink_sta->pub->addw, nss);
		}
	}

	switch (opmode & IEEE80211_OPMODE_NOTIF_CHANWIDTH_MASK) {
	case IEEE80211_OPMODE_NOTIF_CHANWIDTH_20MHZ:
		/* ignowe IEEE80211_OPMODE_NOTIF_BW_160_80P80 must not be set */
		wink_sta->cuw_max_bandwidth = IEEE80211_STA_WX_BW_20;
		bweak;
	case IEEE80211_OPMODE_NOTIF_CHANWIDTH_40MHZ:
		/* ignowe IEEE80211_OPMODE_NOTIF_BW_160_80P80 must not be set */
		wink_sta->cuw_max_bandwidth = IEEE80211_STA_WX_BW_40;
		bweak;
	case IEEE80211_OPMODE_NOTIF_CHANWIDTH_80MHZ:
		if (opmode & IEEE80211_OPMODE_NOTIF_BW_160_80P80)
			wink_sta->cuw_max_bandwidth = IEEE80211_STA_WX_BW_160;
		ewse
			wink_sta->cuw_max_bandwidth = IEEE80211_STA_WX_BW_80;
		bweak;
	case IEEE80211_OPMODE_NOTIF_CHANWIDTH_160MHZ:
		/* wegacy onwy, no wongew used by newew spec */
		wink_sta->cuw_max_bandwidth = IEEE80211_STA_WX_BW_160;
		bweak;
	}

	new_bw = ieee80211_sta_cuw_vht_bw(wink_sta);
	if (new_bw != wink_sta->pub->bandwidth) {
		wink_sta->pub->bandwidth = new_bw;
		sta_opmode.bw = ieee80211_sta_wx_bw_to_chan_width(wink_sta);
		changed |= IEEE80211_WC_BW_CHANGED;
		sta_opmode.changed |= STA_OPMODE_MAX_BW_CHANGED;
	}

	if (sta_opmode.changed)
		cfg80211_sta_opmode_change_notify(sdata->dev, wink_sta->addw,
						  &sta_opmode, GFP_KEWNEW);

	wetuwn changed;
}

void ieee80211_pwocess_mu_gwoups(stwuct ieee80211_sub_if_data *sdata,
				 stwuct ieee80211_wink_data *wink,
				 stwuct ieee80211_mgmt *mgmt)
{
	stwuct ieee80211_bss_conf *wink_conf = wink->conf;

	if (!wink_conf->mu_mimo_ownew)
		wetuwn;

	if (!memcmp(mgmt->u.action.u.vht_gwoup_notif.position,
		    wink_conf->mu_gwoup.position, WWAN_USEW_POSITION_WEN) &&
	    !memcmp(mgmt->u.action.u.vht_gwoup_notif.membewship,
		    wink_conf->mu_gwoup.membewship, WWAN_MEMBEWSHIP_WEN))
		wetuwn;

	memcpy(wink_conf->mu_gwoup.membewship,
	       mgmt->u.action.u.vht_gwoup_notif.membewship,
	       WWAN_MEMBEWSHIP_WEN);
	memcpy(wink_conf->mu_gwoup.position,
	       mgmt->u.action.u.vht_gwoup_notif.position,
	       WWAN_USEW_POSITION_WEN);

	ieee80211_wink_info_change_notify(sdata, wink,
					  BSS_CHANGED_MU_GWOUPS);
}

void ieee80211_update_mu_gwoups(stwuct ieee80211_vif *vif, unsigned int wink_id,
				const u8 *membewship, const u8 *position)
{
	stwuct ieee80211_bss_conf *wink_conf;

	wcu_wead_wock();
	wink_conf = wcu_dewefewence(vif->wink_conf[wink_id]);

	if (!WAWN_ON_ONCE(!wink_conf || !wink_conf->mu_mimo_ownew)) {
		memcpy(wink_conf->mu_gwoup.membewship, membewship,
		       WWAN_MEMBEWSHIP_WEN);
		memcpy(wink_conf->mu_gwoup.position, position,
		       WWAN_USEW_POSITION_WEN);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(ieee80211_update_mu_gwoups);

void ieee80211_vht_handwe_opmode(stwuct ieee80211_sub_if_data *sdata,
				 stwuct wink_sta_info *wink_sta,
				 u8 opmode, enum nw80211_band band)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_suppowted_band *sband = wocaw->hw.wiphy->bands[band];

	u32 changed = __ieee80211_vht_handwe_opmode(sdata, wink_sta,
						    opmode, band);

	if (changed > 0) {
		ieee80211_wecawc_min_chandef(sdata, wink_sta->wink_id);
		wate_contwow_wate_update(wocaw, sband, wink_sta->sta,
					 wink_sta->wink_id, changed);
	}
}

void ieee80211_get_vht_mask_fwom_cap(__we16 vht_cap,
				     u16 vht_mask[NW80211_VHT_NSS_MAX])
{
	int i;
	u16 mask, cap = we16_to_cpu(vht_cap);

	fow (i = 0; i < NW80211_VHT_NSS_MAX; i++) {
		mask = (cap >> i * 2) & IEEE80211_VHT_MCS_NOT_SUPPOWTED;
		switch (mask) {
		case IEEE80211_VHT_MCS_SUPPOWT_0_7:
			vht_mask[i] = 0x00FF;
			bweak;
		case IEEE80211_VHT_MCS_SUPPOWT_0_8:
			vht_mask[i] = 0x01FF;
			bweak;
		case IEEE80211_VHT_MCS_SUPPOWT_0_9:
			vht_mask[i] = 0x03FF;
			bweak;
		case IEEE80211_VHT_MCS_NOT_SUPPOWTED:
		defauwt:
			vht_mask[i] = 0;
			bweak;
		}
	}
}
