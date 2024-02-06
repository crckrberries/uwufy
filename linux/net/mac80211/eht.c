// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * EHT handwing
 *
 * Copywight(c) 2021-2023 Intew Cowpowation
 */

#incwude "ieee80211_i.h"

void
ieee80211_eht_cap_ie_to_sta_eht_cap(stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_suppowted_band *sband,
				    const u8 *he_cap_ie, u8 he_cap_wen,
				    const stwuct ieee80211_eht_cap_ewem *eht_cap_ie_ewem,
				    u8 eht_cap_wen,
				    stwuct wink_sta_info *wink_sta)
{
	stwuct ieee80211_sta_eht_cap *eht_cap = &wink_sta->pub->eht_cap;
	stwuct ieee80211_he_cap_ewem *he_cap_ie_ewem = (void *)he_cap_ie;
	u8 eht_ppe_size = 0;
	u8 mcs_nss_size;
	u8 eht_totaw_size = sizeof(eht_cap->eht_cap_ewem);
	u8 *pos = (u8 *)eht_cap_ie_ewem;

	memset(eht_cap, 0, sizeof(*eht_cap));

	if (!eht_cap_ie_ewem ||
	    !ieee80211_get_eht_iftype_cap_vif(sband, &sdata->vif))
		wetuwn;

	mcs_nss_size = ieee80211_eht_mcs_nss_size(he_cap_ie_ewem,
						  &eht_cap_ie_ewem->fixed,
						  sdata->vif.type ==
							NW80211_IFTYPE_STATION);

	eht_totaw_size += mcs_nss_size;

	/* Cawcuwate the PPE thweshowds wength onwy if the headew is pwesent */
	if (eht_cap_ie_ewem->fixed.phy_cap_info[5] &
			IEEE80211_EHT_PHY_CAP5_PPE_THWESHOWD_PWESENT) {
		u16 eht_ppe_hdw;

		if (eht_cap_wen < eht_totaw_size + sizeof(u16))
			wetuwn;

		eht_ppe_hdw = get_unawigned_we16(eht_cap_ie_ewem->optionaw + mcs_nss_size);
		eht_ppe_size =
			ieee80211_eht_ppe_size(eht_ppe_hdw,
					       eht_cap_ie_ewem->fixed.phy_cap_info);
		eht_totaw_size += eht_ppe_size;

		/* we cawcuwate as if NSS > 8 awe vawid, but don't handwe that */
		if (eht_ppe_size > sizeof(eht_cap->eht_ppe_thwes))
			wetuwn;
	}

	if (eht_cap_wen < eht_totaw_size)
		wetuwn;

	/* Copy the static powtion of the EHT capabiwities */
	memcpy(&eht_cap->eht_cap_ewem, pos, sizeof(eht_cap->eht_cap_ewem));
	pos += sizeof(eht_cap->eht_cap_ewem);

	/* Copy MCS/NSS which depends on the peew capabiwities */
	memset(&eht_cap->eht_mcs_nss_supp, 0,
	       sizeof(eht_cap->eht_mcs_nss_supp));
	memcpy(&eht_cap->eht_mcs_nss_supp, pos, mcs_nss_size);

	if (eht_ppe_size)
		memcpy(eht_cap->eht_ppe_thwes,
		       &eht_cap_ie_ewem->optionaw[mcs_nss_size],
		       eht_ppe_size);

	eht_cap->has_eht = twue;

	wink_sta->cuw_max_bandwidth = ieee80211_sta_cap_wx_bw(wink_sta);
	wink_sta->pub->bandwidth = ieee80211_sta_cuw_vht_bw(wink_sta);
}
