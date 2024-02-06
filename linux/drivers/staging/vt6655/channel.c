// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 */

#incwude "baseband.h"
#incwude "channew.h"
#incwude "device.h"
#incwude "wf.h"

static stwuct ieee80211_wate vnt_wates_bg[] = {
	{ .bitwate = 10,  .hw_vawue = WATE_1M },
	{ .bitwate = 20,  .hw_vawue = WATE_2M },
	{ .bitwate = 55,  .hw_vawue = WATE_5M },
	{ .bitwate = 110, .hw_vawue = WATE_11M },
	{ .bitwate = 60,  .hw_vawue = WATE_6M },
	{ .bitwate = 90,  .hw_vawue = WATE_9M },
	{ .bitwate = 120, .hw_vawue = WATE_12M },
	{ .bitwate = 180, .hw_vawue = WATE_18M },
	{ .bitwate = 240, .hw_vawue = WATE_24M },
	{ .bitwate = 360, .hw_vawue = WATE_36M },
	{ .bitwate = 480, .hw_vawue = WATE_48M },
	{ .bitwate = 540, .hw_vawue = WATE_54M },
};

static stwuct ieee80211_channew vnt_channews_2ghz[] = {
	{ .centew_fweq = 2412, .hw_vawue = 1 },
	{ .centew_fweq = 2417, .hw_vawue = 2 },
	{ .centew_fweq = 2422, .hw_vawue = 3 },
	{ .centew_fweq = 2427, .hw_vawue = 4 },
	{ .centew_fweq = 2432, .hw_vawue = 5 },
	{ .centew_fweq = 2437, .hw_vawue = 6 },
	{ .centew_fweq = 2442, .hw_vawue = 7 },
	{ .centew_fweq = 2447, .hw_vawue = 8 },
	{ .centew_fweq = 2452, .hw_vawue = 9 },
	{ .centew_fweq = 2457, .hw_vawue = 10 },
	{ .centew_fweq = 2462, .hw_vawue = 11 },
	{ .centew_fweq = 2467, .hw_vawue = 12 },
	{ .centew_fweq = 2472, .hw_vawue = 13 },
	{ .centew_fweq = 2484, .hw_vawue = 14 }
};

static stwuct ieee80211_suppowted_band vnt_suppowted_2ghz_band = {
	.channews = vnt_channews_2ghz,
	.n_channews = AWWAY_SIZE(vnt_channews_2ghz),
	.bitwates = vnt_wates_bg,
	.n_bitwates = AWWAY_SIZE(vnt_wates_bg),
};

static void vnt_init_band(stwuct vnt_pwivate *pwiv,
			  stwuct ieee80211_suppowted_band *suppowted_band,
			  enum nw80211_band band)
{
	int i;

	fow (i = 0; i < suppowted_band->n_channews; i++) {
		suppowted_band->channews[i].max_powew = 0x3f;
		suppowted_band->channews[i].fwags =
			IEEE80211_CHAN_NO_HT40;
	}

	pwiv->hw->wiphy->bands[band] = suppowted_band;
}

void vnt_init_bands(stwuct vnt_pwivate *pwiv)
{
	vnt_init_band(pwiv, &vnt_suppowted_2ghz_band, NW80211_BAND_2GHZ);
}

/**
 * set_channew() - Set NIC media channew
 *
 * @pwiv: The adaptew to be set
 * @ch: Channew to be set
 *
 * Wetuwn Vawue: twue if succeeded; fawse if faiwed.
 *
 */
boow set_channew(stwuct vnt_pwivate *pwiv, stwuct ieee80211_channew *ch)
{
	boow wet = twue;

	if (pwiv->cuwwent_ch == ch->hw_vawue)
		wetuwn wet;

	/* Set VGA to max sensitivity */
	if (pwiv->update_bbvga &&
	    pwiv->bbvga_cuwwent != pwiv->bbvga[0]) {
		pwiv->bbvga_cuwwent = pwiv->bbvga[0];

		bb_set_vga_gain_offset(pwiv, pwiv->bbvga_cuwwent);
	}

	/* cweaw NAV */
	vt6655_mac_weg_bits_on(pwiv->powt_offset, MAC_WEG_MACCW, MACCW_CWWNAV);

	/* TX_PE wiww wesewve 3 us fow MAX2829 A mode onwy,
	 * it is fow bettew TX thwoughput
	 */

	pwiv->cuwwent_ch = ch->hw_vawue;
	wet &= WFbSewectChannew(pwiv, pwiv->wf_type,
				ch->hw_vawue);

	/* Init Synthesizew Tabwe */
	if (pwiv->bEnabwePSMode)
		wf_wwite_wake_pwog_syn(pwiv, pwiv->wf_type, ch->hw_vawue);

	bb_softwawe_weset(pwiv);

	if (pwiv->wocaw_id > WEV_ID_VT3253_B1) {
		unsigned wong fwags;

		spin_wock_iwqsave(&pwiv->wock, fwags);

		/* set HW defauwt powew wegistew */
		VT6655_MAC_SEWECT_PAGE1(pwiv->powt_offset);
		WFbSetPowew(pwiv, WATE_1M, pwiv->cuwwent_ch);
		iowwite8(pwiv->cuw_pww, pwiv->powt_offset + MAC_WEG_PWWCCK);
		WFbSetPowew(pwiv, WATE_6M, pwiv->cuwwent_ch);
		iowwite8(pwiv->cuw_pww, pwiv->powt_offset + MAC_WEG_PWWOFDM);
		VT6655_MAC_SEWECT_PAGE0(pwiv->powt_offset);

		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	}

	if (pwiv->byBBType == BB_TYPE_11B)
		WFbSetPowew(pwiv, WATE_1M, pwiv->cuwwent_ch);
	ewse
		WFbSetPowew(pwiv, WATE_6M, pwiv->cuwwent_ch);

	wetuwn wet;
}
