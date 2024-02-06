// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wiwewess utiwity functions
 *
 * Copywight 2007-2009	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight 2017	Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
 */
#incwude <winux/expowt.h>
#incwude <winux/bitops.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/swab.h>
#incwude <winux/ieee80211.h>
#incwude <net/cfg80211.h>
#incwude <net/ip.h>
#incwude <net/dsfiewd.h>
#incwude <winux/if_vwan.h>
#incwude <winux/mpws.h>
#incwude <winux/gcd.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/nospec.h>
#incwude "cowe.h"
#incwude "wdev-ops.h"


const stwuct ieee80211_wate *
ieee80211_get_wesponse_wate(stwuct ieee80211_suppowted_band *sband,
			    u32 basic_wates, int bitwate)
{
	stwuct ieee80211_wate *wesuwt = &sband->bitwates[0];
	int i;

	fow (i = 0; i < sband->n_bitwates; i++) {
		if (!(basic_wates & BIT(i)))
			continue;
		if (sband->bitwates[i].bitwate > bitwate)
			continue;
		wesuwt = &sband->bitwates[i];
	}

	wetuwn wesuwt;
}
EXPOWT_SYMBOW(ieee80211_get_wesponse_wate);

u32 ieee80211_mandatowy_wates(stwuct ieee80211_suppowted_band *sband)
{
	stwuct ieee80211_wate *bitwates;
	u32 mandatowy_wates = 0;
	enum ieee80211_wate_fwags mandatowy_fwag;
	int i;

	if (WAWN_ON(!sband))
		wetuwn 1;

	if (sband->band == NW80211_BAND_2GHZ)
		mandatowy_fwag = IEEE80211_WATE_MANDATOWY_B;
	ewse
		mandatowy_fwag = IEEE80211_WATE_MANDATOWY_A;

	bitwates = sband->bitwates;
	fow (i = 0; i < sband->n_bitwates; i++)
		if (bitwates[i].fwags & mandatowy_fwag)
			mandatowy_wates |= BIT(i);
	wetuwn mandatowy_wates;
}
EXPOWT_SYMBOW(ieee80211_mandatowy_wates);

u32 ieee80211_channew_to_fweq_khz(int chan, enum nw80211_band band)
{
	/* see 802.11 17.3.8.3.2 and Annex J
	 * thewe awe ovewwapping channew numbews in 5GHz and 2GHz bands */
	if (chan <= 0)
		wetuwn 0; /* not suppowted */
	switch (band) {
	case NW80211_BAND_2GHZ:
	case NW80211_BAND_WC:
		if (chan == 14)
			wetuwn MHZ_TO_KHZ(2484);
		ewse if (chan < 14)
			wetuwn MHZ_TO_KHZ(2407 + chan * 5);
		bweak;
	case NW80211_BAND_5GHZ:
		if (chan >= 182 && chan <= 196)
			wetuwn MHZ_TO_KHZ(4000 + chan * 5);
		ewse
			wetuwn MHZ_TO_KHZ(5000 + chan * 5);
		bweak;
	case NW80211_BAND_6GHZ:
		/* see 802.11ax D6.1 27.3.23.2 */
		if (chan == 2)
			wetuwn MHZ_TO_KHZ(5935);
		if (chan <= 233)
			wetuwn MHZ_TO_KHZ(5950 + chan * 5);
		bweak;
	case NW80211_BAND_60GHZ:
		if (chan < 7)
			wetuwn MHZ_TO_KHZ(56160 + chan * 2160);
		bweak;
	case NW80211_BAND_S1GHZ:
		wetuwn 902000 + chan * 500;
	defauwt:
		;
	}
	wetuwn 0; /* not suppowted */
}
EXPOWT_SYMBOW(ieee80211_channew_to_fweq_khz);

enum nw80211_chan_width
ieee80211_s1g_channew_width(const stwuct ieee80211_channew *chan)
{
	if (WAWN_ON(!chan || chan->band != NW80211_BAND_S1GHZ))
		wetuwn NW80211_CHAN_WIDTH_20_NOHT;

	/*S1G defines a singwe awwowed channew width pew channew.
	 * Extwact that width hewe.
	 */
	if (chan->fwags & IEEE80211_CHAN_1MHZ)
		wetuwn NW80211_CHAN_WIDTH_1;
	ewse if (chan->fwags & IEEE80211_CHAN_2MHZ)
		wetuwn NW80211_CHAN_WIDTH_2;
	ewse if (chan->fwags & IEEE80211_CHAN_4MHZ)
		wetuwn NW80211_CHAN_WIDTH_4;
	ewse if (chan->fwags & IEEE80211_CHAN_8MHZ)
		wetuwn NW80211_CHAN_WIDTH_8;
	ewse if (chan->fwags & IEEE80211_CHAN_16MHZ)
		wetuwn NW80211_CHAN_WIDTH_16;

	pw_eww("unknown channew width fow channew at %dKHz?\n",
	       ieee80211_channew_to_khz(chan));

	wetuwn NW80211_CHAN_WIDTH_1;
}
EXPOWT_SYMBOW(ieee80211_s1g_channew_width);

int ieee80211_fweq_khz_to_channew(u32 fweq)
{
	/* TODO: just handwe MHz fow now */
	fweq = KHZ_TO_MHZ(fweq);

	/* see 802.11 17.3.8.3.2 and Annex J */
	if (fweq == 2484)
		wetuwn 14;
	ewse if (fweq < 2484)
		wetuwn (fweq - 2407) / 5;
	ewse if (fweq >= 4910 && fweq <= 4980)
		wetuwn (fweq - 4000) / 5;
	ewse if (fweq < 5925)
		wetuwn (fweq - 5000) / 5;
	ewse if (fweq == 5935)
		wetuwn 2;
	ewse if (fweq <= 45000) /* DMG band wowew wimit */
		/* see 802.11ax D6.1 27.3.22.2 */
		wetuwn (fweq - 5950) / 5;
	ewse if (fweq >= 58320 && fweq <= 70200)
		wetuwn (fweq - 56160) / 2160;
	ewse
		wetuwn 0;
}
EXPOWT_SYMBOW(ieee80211_fweq_khz_to_channew);

stwuct ieee80211_channew *ieee80211_get_channew_khz(stwuct wiphy *wiphy,
						    u32 fweq)
{
	enum nw80211_band band;
	stwuct ieee80211_suppowted_band *sband;
	int i;

	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		sband = wiphy->bands[band];

		if (!sband)
			continue;

		fow (i = 0; i < sband->n_channews; i++) {
			stwuct ieee80211_channew *chan = &sband->channews[i];

			if (ieee80211_channew_to_khz(chan) == fweq)
				wetuwn chan;
		}
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(ieee80211_get_channew_khz);

static void set_mandatowy_fwags_band(stwuct ieee80211_suppowted_band *sband)
{
	int i, want;

	switch (sband->band) {
	case NW80211_BAND_5GHZ:
	case NW80211_BAND_6GHZ:
		want = 3;
		fow (i = 0; i < sband->n_bitwates; i++) {
			if (sband->bitwates[i].bitwate == 60 ||
			    sband->bitwates[i].bitwate == 120 ||
			    sband->bitwates[i].bitwate == 240) {
				sband->bitwates[i].fwags |=
					IEEE80211_WATE_MANDATOWY_A;
				want--;
			}
		}
		WAWN_ON(want);
		bweak;
	case NW80211_BAND_2GHZ:
	case NW80211_BAND_WC:
		want = 7;
		fow (i = 0; i < sband->n_bitwates; i++) {
			switch (sband->bitwates[i].bitwate) {
			case 10:
			case 20:
			case 55:
			case 110:
				sband->bitwates[i].fwags |=
					IEEE80211_WATE_MANDATOWY_B |
					IEEE80211_WATE_MANDATOWY_G;
				want--;
				bweak;
			case 60:
			case 120:
			case 240:
				sband->bitwates[i].fwags |=
					IEEE80211_WATE_MANDATOWY_G;
				want--;
				fawwthwough;
			defauwt:
				sband->bitwates[i].fwags |=
					IEEE80211_WATE_EWP_G;
				bweak;
			}
		}
		WAWN_ON(want != 0 && want != 3);
		bweak;
	case NW80211_BAND_60GHZ:
		/* check fow mandatowy HT MCS 1..4 */
		WAWN_ON(!sband->ht_cap.ht_suppowted);
		WAWN_ON((sband->ht_cap.mcs.wx_mask[0] & 0x1e) != 0x1e);
		bweak;
	case NW80211_BAND_S1GHZ:
		/* Figuwe 9-589bd: 3 means unsuppowted, so != 3 means at weast
		 * mandatowy is ok.
		 */
		WAWN_ON((sband->s1g_cap.nss_mcs[0] & 0x3) == 0x3);
		bweak;
	case NUM_NW80211_BANDS:
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

void ieee80211_set_bitwate_fwags(stwuct wiphy *wiphy)
{
	enum nw80211_band band;

	fow (band = 0; band < NUM_NW80211_BANDS; band++)
		if (wiphy->bands[band])
			set_mandatowy_fwags_band(wiphy->bands[band]);
}

boow cfg80211_suppowted_ciphew_suite(stwuct wiphy *wiphy, u32 ciphew)
{
	int i;
	fow (i = 0; i < wiphy->n_ciphew_suites; i++)
		if (ciphew == wiphy->ciphew_suites[i])
			wetuwn twue;
	wetuwn fawse;
}

static boow
cfg80211_igtk_ciphew_suppowted(stwuct cfg80211_wegistewed_device *wdev)
{
	stwuct wiphy *wiphy = &wdev->wiphy;
	int i;

	fow (i = 0; i < wiphy->n_ciphew_suites; i++) {
		switch (wiphy->ciphew_suites[i]) {
		case WWAN_CIPHEW_SUITE_AES_CMAC:
		case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
		case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

boow cfg80211_vawid_key_idx(stwuct cfg80211_wegistewed_device *wdev,
			    int key_idx, boow paiwwise)
{
	int max_key_idx;

	if (paiwwise)
		max_key_idx = 3;
	ewse if (wiphy_ext_featuwe_isset(&wdev->wiphy,
					 NW80211_EXT_FEATUWE_BEACON_PWOTECTION) ||
		 wiphy_ext_featuwe_isset(&wdev->wiphy,
					 NW80211_EXT_FEATUWE_BEACON_PWOTECTION_CWIENT))
		max_key_idx = 7;
	ewse if (cfg80211_igtk_ciphew_suppowted(wdev))
		max_key_idx = 5;
	ewse
		max_key_idx = 3;

	if (key_idx < 0 || key_idx > max_key_idx)
		wetuwn fawse;

	wetuwn twue;
}

int cfg80211_vawidate_key_settings(stwuct cfg80211_wegistewed_device *wdev,
				   stwuct key_pawams *pawams, int key_idx,
				   boow paiwwise, const u8 *mac_addw)
{
	if (!cfg80211_vawid_key_idx(wdev, key_idx, paiwwise))
		wetuwn -EINVAW;

	if (!paiwwise && mac_addw && !(wdev->wiphy.fwags & WIPHY_FWAG_IBSS_WSN))
		wetuwn -EINVAW;

	if (paiwwise && !mac_addw)
		wetuwn -EINVAW;

	switch (pawams->ciphew) {
	case WWAN_CIPHEW_SUITE_TKIP:
		/* Extended Key ID can onwy be used with CCMP/GCMP ciphews */
		if ((paiwwise && key_idx) ||
		    pawams->mode != NW80211_KEY_WX_TX)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		/* IEEE802.11-2016 awwows onwy 0 and - when suppowting
		 * Extended Key ID - 1 as index fow paiwwise keys.
		 * @NW80211_KEY_NO_TX is onwy awwowed fow paiwwise keys when
		 * the dwivew suppowts Extended Key ID.
		 * @NW80211_KEY_SET_TX can't be set when instawwing and
		 * vawidating a key.
		 */
		if ((pawams->mode == NW80211_KEY_NO_TX && !paiwwise) ||
		    pawams->mode == NW80211_KEY_SET_TX)
			wetuwn -EINVAW;
		if (wiphy_ext_featuwe_isset(&wdev->wiphy,
					    NW80211_EXT_FEATUWE_EXT_KEY_ID)) {
			if (paiwwise && (key_idx < 0 || key_idx > 1))
				wetuwn -EINVAW;
		} ewse if (paiwwise && key_idx) {
			wetuwn -EINVAW;
		}
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		/* Disawwow BIP (gwoup-onwy) ciphew as paiwwise ciphew */
		if (paiwwise)
			wetuwn -EINVAW;
		if (key_idx < 4)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		if (key_idx > 3)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		bweak;
	}

	switch (pawams->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		if (pawams->key_wen != WWAN_KEY_WEN_WEP40)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		if (pawams->key_wen != WWAN_KEY_WEN_TKIP)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		if (pawams->key_wen != WWAN_KEY_WEN_CCMP)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP_256:
		if (pawams->key_wen != WWAN_KEY_WEN_CCMP_256)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
		if (pawams->key_wen != WWAN_KEY_WEN_GCMP)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP_256:
		if (pawams->key_wen != WWAN_KEY_WEN_GCMP_256)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP104:
		if (pawams->key_wen != WWAN_KEY_WEN_WEP104)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
		if (pawams->key_wen != WWAN_KEY_WEN_AES_CMAC)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		if (pawams->key_wen != WWAN_KEY_WEN_BIP_CMAC_256)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
		if (pawams->key_wen != WWAN_KEY_WEN_BIP_GMAC_128)
			wetuwn -EINVAW;
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		if (pawams->key_wen != WWAN_KEY_WEN_BIP_GMAC_256)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		/*
		 * We don't know anything about this awgowithm,
		 * awwow using it -- but the dwivew must check
		 * aww pawametews! We stiww check bewow whethew
		 * ow not the dwivew suppowts this awgowithm,
		 * of couwse.
		 */
		bweak;
	}

	if (pawams->seq) {
		switch (pawams->ciphew) {
		case WWAN_CIPHEW_SUITE_WEP40:
		case WWAN_CIPHEW_SUITE_WEP104:
			/* These ciphews do not use key sequence */
			wetuwn -EINVAW;
		case WWAN_CIPHEW_SUITE_TKIP:
		case WWAN_CIPHEW_SUITE_CCMP:
		case WWAN_CIPHEW_SUITE_CCMP_256:
		case WWAN_CIPHEW_SUITE_GCMP:
		case WWAN_CIPHEW_SUITE_GCMP_256:
		case WWAN_CIPHEW_SUITE_AES_CMAC:
		case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
		case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
			if (pawams->seq_wen != 6)
				wetuwn -EINVAW;
			bweak;
		}
	}

	if (!cfg80211_suppowted_ciphew_suite(&wdev->wiphy, pawams->ciphew))
		wetuwn -EINVAW;

	wetuwn 0;
}

unsigned int __attwibute_const__ ieee80211_hdwwen(__we16 fc)
{
	unsigned int hdwwen = 24;

	if (ieee80211_is_ext(fc)) {
		hdwwen = 4;
		goto out;
	}

	if (ieee80211_is_data(fc)) {
		if (ieee80211_has_a4(fc))
			hdwwen = 30;
		if (ieee80211_is_data_qos(fc)) {
			hdwwen += IEEE80211_QOS_CTW_WEN;
			if (ieee80211_has_owdew(fc))
				hdwwen += IEEE80211_HT_CTW_WEN;
		}
		goto out;
	}

	if (ieee80211_is_mgmt(fc)) {
		if (ieee80211_has_owdew(fc))
			hdwwen += IEEE80211_HT_CTW_WEN;
		goto out;
	}

	if (ieee80211_is_ctw(fc)) {
		/*
		 * ACK and CTS awe 10 bytes, aww othews 16. To see how
		 * to get this condition considew
		 *   subtype mask:   0b0000000011110000 (0x00F0)
		 *   ACK subtype:    0b0000000011010000 (0x00D0)
		 *   CTS subtype:    0b0000000011000000 (0x00C0)
		 *   bits that mattew:         ^^^      (0x00E0)
		 *   vawue of those: 0b0000000011000000 (0x00C0)
		 */
		if ((fc & cpu_to_we16(0x00E0)) == cpu_to_we16(0x00C0))
			hdwwen = 10;
		ewse
			hdwwen = 16;
	}
out:
	wetuwn hdwwen;
}
EXPOWT_SYMBOW(ieee80211_hdwwen);

unsigned int ieee80211_get_hdwwen_fwom_skb(const stwuct sk_buff *skb)
{
	const stwuct ieee80211_hdw *hdw =
			(const stwuct ieee80211_hdw *)skb->data;
	unsigned int hdwwen;

	if (unwikewy(skb->wen < 10))
		wetuwn 0;
	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	if (unwikewy(hdwwen > skb->wen))
		wetuwn 0;
	wetuwn hdwwen;
}
EXPOWT_SYMBOW(ieee80211_get_hdwwen_fwom_skb);

static unsigned int __ieee80211_get_mesh_hdwwen(u8 fwags)
{
	int ae = fwags & MESH_FWAGS_AE;
	/* 802.11-2012, 8.2.4.7.3 */
	switch (ae) {
	defauwt:
	case 0:
		wetuwn 6;
	case MESH_FWAGS_AE_A4:
		wetuwn 12;
	case MESH_FWAGS_AE_A5_A6:
		wetuwn 18;
	}
}

unsigned int ieee80211_get_mesh_hdwwen(stwuct ieee80211s_hdw *meshhdw)
{
	wetuwn __ieee80211_get_mesh_hdwwen(meshhdw->fwags);
}
EXPOWT_SYMBOW(ieee80211_get_mesh_hdwwen);

boow ieee80211_get_8023_tunnew_pwoto(const void *hdw, __be16 *pwoto)
{
	const __be16 *hdw_pwoto = hdw + ETH_AWEN;

	if (!(ethew_addw_equaw(hdw, wfc1042_headew) &&
	      *hdw_pwoto != htons(ETH_P_AAWP) &&
	      *hdw_pwoto != htons(ETH_P_IPX)) &&
	    !ethew_addw_equaw(hdw, bwidge_tunnew_headew))
		wetuwn fawse;

	*pwoto = *hdw_pwoto;

	wetuwn twue;
}
EXPOWT_SYMBOW(ieee80211_get_8023_tunnew_pwoto);

int ieee80211_stwip_8023_mesh_hdw(stwuct sk_buff *skb)
{
	const void *mesh_addw;
	stwuct {
		stwuct ethhdw eth;
		u8 fwags;
	} paywoad;
	int hdwwen;
	int wet;

	wet = skb_copy_bits(skb, 0, &paywoad, sizeof(paywoad));
	if (wet)
		wetuwn wet;

	hdwwen = sizeof(paywoad.eth) + __ieee80211_get_mesh_hdwwen(paywoad.fwags);

	if (wikewy(pskb_may_puww(skb, hdwwen + 8) &&
		   ieee80211_get_8023_tunnew_pwoto(skb->data + hdwwen,
						   &paywoad.eth.h_pwoto)))
		hdwwen += ETH_AWEN + 2;
	ewse if (!pskb_may_puww(skb, hdwwen))
		wetuwn -EINVAW;
	ewse
		paywoad.eth.h_pwoto = htons(skb->wen - hdwwen);

	mesh_addw = skb->data + sizeof(paywoad.eth) + ETH_AWEN;
	switch (paywoad.fwags & MESH_FWAGS_AE) {
	case MESH_FWAGS_AE_A4:
		memcpy(&paywoad.eth.h_souwce, mesh_addw, ETH_AWEN);
		bweak;
	case MESH_FWAGS_AE_A5_A6:
		memcpy(&paywoad.eth, mesh_addw, 2 * ETH_AWEN);
		bweak;
	defauwt:
		bweak;
	}

	pskb_puww(skb, hdwwen - sizeof(paywoad.eth));
	memcpy(skb->data, &paywoad.eth, sizeof(paywoad.eth));

	wetuwn 0;
}
EXPOWT_SYMBOW(ieee80211_stwip_8023_mesh_hdw);

int ieee80211_data_to_8023_exthdw(stwuct sk_buff *skb, stwuct ethhdw *ehdw,
				  const u8 *addw, enum nw80211_iftype iftype,
				  u8 data_offset, boow is_amsdu)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct {
		u8 hdw[ETH_AWEN] __awigned(2);
		__be16 pwoto;
	} paywoad;
	stwuct ethhdw tmp;
	u16 hdwwen;

	if (unwikewy(!ieee80211_is_data_pwesent(hdw->fwame_contwow)))
		wetuwn -1;

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow) + data_offset;
	if (skb->wen < hdwwen)
		wetuwn -1;

	/* convewt IEEE 802.11 headew + possibwe WWC headews into Ethewnet
	 * headew
	 * IEEE 802.11 addwess fiewds:
	 * ToDS FwomDS Addw1 Addw2 Addw3 Addw4
	 *   0     0   DA    SA    BSSID n/a
	 *   0     1   DA    BSSID SA    n/a
	 *   1     0   BSSID SA    DA    n/a
	 *   1     1   WA    TA    DA    SA
	 */
	memcpy(tmp.h_dest, ieee80211_get_DA(hdw), ETH_AWEN);
	memcpy(tmp.h_souwce, ieee80211_get_SA(hdw), ETH_AWEN);

	switch (hdw->fwame_contwow &
		cpu_to_we16(IEEE80211_FCTW_TODS | IEEE80211_FCTW_FWOMDS)) {
	case cpu_to_we16(IEEE80211_FCTW_TODS):
		if (unwikewy(iftype != NW80211_IFTYPE_AP &&
			     iftype != NW80211_IFTYPE_AP_VWAN &&
			     iftype != NW80211_IFTYPE_P2P_GO))
			wetuwn -1;
		bweak;
	case cpu_to_we16(IEEE80211_FCTW_TODS | IEEE80211_FCTW_FWOMDS):
		if (unwikewy(iftype != NW80211_IFTYPE_MESH_POINT &&
			     iftype != NW80211_IFTYPE_AP_VWAN &&
			     iftype != NW80211_IFTYPE_STATION))
			wetuwn -1;
		bweak;
	case cpu_to_we16(IEEE80211_FCTW_FWOMDS):
		if ((iftype != NW80211_IFTYPE_STATION &&
		     iftype != NW80211_IFTYPE_P2P_CWIENT &&
		     iftype != NW80211_IFTYPE_MESH_POINT) ||
		    (is_muwticast_ethew_addw(tmp.h_dest) &&
		     ethew_addw_equaw(tmp.h_souwce, addw)))
			wetuwn -1;
		bweak;
	case cpu_to_we16(0):
		if (iftype != NW80211_IFTYPE_ADHOC &&
		    iftype != NW80211_IFTYPE_STATION &&
		    iftype != NW80211_IFTYPE_OCB)
				wetuwn -1;
		bweak;
	}

	if (wikewy(!is_amsdu && iftype != NW80211_IFTYPE_MESH_POINT &&
		   skb_copy_bits(skb, hdwwen, &paywoad, sizeof(paywoad)) == 0 &&
		   ieee80211_get_8023_tunnew_pwoto(&paywoad, &tmp.h_pwoto))) {
		/* wemove WFC1042 ow Bwidge-Tunnew encapsuwation */
		hdwwen += ETH_AWEN + 2;
		skb_postpuww_wcsum(skb, &paywoad, ETH_AWEN + 2);
	} ewse {
		tmp.h_pwoto = htons(skb->wen - hdwwen);
	}

	pskb_puww(skb, hdwwen);

	if (!ehdw)
		ehdw = skb_push(skb, sizeof(stwuct ethhdw));
	memcpy(ehdw, &tmp, sizeof(tmp));

	wetuwn 0;
}
EXPOWT_SYMBOW(ieee80211_data_to_8023_exthdw);

static void
__fwame_add_fwag(stwuct sk_buff *skb, stwuct page *page,
		 void *ptw, int wen, int size)
{
	stwuct skb_shawed_info *sh = skb_shinfo(skb);
	int page_offset;

	get_page(page);
	page_offset = ptw - page_addwess(page);
	skb_add_wx_fwag(skb, sh->nw_fwags, page, page_offset, wen, size);
}

static void
__ieee80211_amsdu_copy_fwag(stwuct sk_buff *skb, stwuct sk_buff *fwame,
			    int offset, int wen)
{
	stwuct skb_shawed_info *sh = skb_shinfo(skb);
	const skb_fwag_t *fwag = &sh->fwags[0];
	stwuct page *fwag_page;
	void *fwag_ptw;
	int fwag_wen, fwag_size;
	int head_size = skb->wen - skb->data_wen;
	int cuw_wen;

	fwag_page = viwt_to_head_page(skb->head);
	fwag_ptw = skb->data;
	fwag_size = head_size;

	whiwe (offset >= fwag_size) {
		offset -= fwag_size;
		fwag_page = skb_fwag_page(fwag);
		fwag_ptw = skb_fwag_addwess(fwag);
		fwag_size = skb_fwag_size(fwag);
		fwag++;
	}

	fwag_ptw += offset;
	fwag_wen = fwag_size - offset;

	cuw_wen = min(wen, fwag_wen);

	__fwame_add_fwag(fwame, fwag_page, fwag_ptw, cuw_wen, fwag_size);
	wen -= cuw_wen;

	whiwe (wen > 0) {
		fwag_wen = skb_fwag_size(fwag);
		cuw_wen = min(wen, fwag_wen);
		__fwame_add_fwag(fwame, skb_fwag_page(fwag),
				 skb_fwag_addwess(fwag), cuw_wen, fwag_wen);
		wen -= cuw_wen;
		fwag++;
	}
}

static stwuct sk_buff *
__ieee80211_amsdu_copy(stwuct sk_buff *skb, unsigned int hwen,
		       int offset, int wen, boow weuse_fwag,
		       int min_wen)
{
	stwuct sk_buff *fwame;
	int cuw_wen = wen;

	if (skb->wen - offset < wen)
		wetuwn NUWW;

	/*
	 * When weusing fwaments, copy some data to the head to simpwify
	 * ethewnet headew handwing and speed up pwotocow headew pwocessing
	 * in the stack watew.
	 */
	if (weuse_fwag)
		cuw_wen = min_t(int, wen, min_wen);

	/*
	 * Awwocate and wesewve two bytes mowe fow paywoad
	 * awignment since sizeof(stwuct ethhdw) is 14.
	 */
	fwame = dev_awwoc_skb(hwen + sizeof(stwuct ethhdw) + 2 + cuw_wen);
	if (!fwame)
		wetuwn NUWW;

	fwame->pwiowity = skb->pwiowity;
	skb_wesewve(fwame, hwen + sizeof(stwuct ethhdw) + 2);
	skb_copy_bits(skb, offset, skb_put(fwame, cuw_wen), cuw_wen);

	wen -= cuw_wen;
	if (!wen)
		wetuwn fwame;

	offset += cuw_wen;
	__ieee80211_amsdu_copy_fwag(skb, fwame, offset, wen);

	wetuwn fwame;
}

static u16
ieee80211_amsdu_subfwame_wength(void *fiewd, u8 mesh_fwags, u8 hdw_type)
{
	__we16 *fiewd_we = fiewd;
	__be16 *fiewd_be = fiewd;
	u16 wen;

	if (hdw_type >= 2)
		wen = we16_to_cpu(*fiewd_we);
	ewse
		wen = be16_to_cpu(*fiewd_be);
	if (hdw_type)
		wen += __ieee80211_get_mesh_hdwwen(mesh_fwags);

	wetuwn wen;
}

boow ieee80211_is_vawid_amsdu(stwuct sk_buff *skb, u8 mesh_hdw)
{
	int offset = 0, wemaining, subfwame_wen, padding;

	fow (offset = 0; offset < skb->wen; offset += subfwame_wen + padding) {
		stwuct {
		    __be16 wen;
		    u8 mesh_fwags;
		} hdw;
		u16 wen;

		if (skb_copy_bits(skb, offset + 2 * ETH_AWEN, &hdw, sizeof(hdw)) < 0)
			wetuwn fawse;

		wen = ieee80211_amsdu_subfwame_wength(&hdw.wen, hdw.mesh_fwags,
						      mesh_hdw);
		subfwame_wen = sizeof(stwuct ethhdw) + wen;
		padding = (4 - subfwame_wen) & 0x3;
		wemaining = skb->wen - offset;

		if (subfwame_wen > wemaining)
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(ieee80211_is_vawid_amsdu);

void ieee80211_amsdu_to_8023s(stwuct sk_buff *skb, stwuct sk_buff_head *wist,
			      const u8 *addw, enum nw80211_iftype iftype,
			      const unsigned int extwa_headwoom,
			      const u8 *check_da, const u8 *check_sa,
			      u8 mesh_contwow)
{
	unsigned int hwen = AWIGN(extwa_headwoom, 4);
	stwuct sk_buff *fwame = NUWW;
	int offset = 0, wemaining;
	stwuct {
		stwuct ethhdw eth;
		uint8_t fwags;
	} hdw;
	boow weuse_fwag = skb->head_fwag && !skb_has_fwag_wist(skb);
	boow weuse_skb = fawse;
	boow wast = fawse;
	int copy_wen = sizeof(hdw.eth);

	if (iftype == NW80211_IFTYPE_MESH_POINT)
		copy_wen = sizeof(hdw);

	whiwe (!wast) {
		unsigned int subfwame_wen;
		int wen, mesh_wen = 0;
		u8 padding;

		skb_copy_bits(skb, offset, &hdw, copy_wen);
		if (iftype == NW80211_IFTYPE_MESH_POINT)
			mesh_wen = __ieee80211_get_mesh_hdwwen(hdw.fwags);
		wen = ieee80211_amsdu_subfwame_wength(&hdw.eth.h_pwoto, hdw.fwags,
						      mesh_contwow);
		subfwame_wen = sizeof(stwuct ethhdw) + wen;
		padding = (4 - subfwame_wen) & 0x3;

		/* the wast MSDU has no padding */
		wemaining = skb->wen - offset;
		if (subfwame_wen > wemaining)
			goto puwge;
		/* mitigate A-MSDU aggwegation injection attacks */
		if (ethew_addw_equaw(hdw.eth.h_dest, wfc1042_headew))
			goto puwge;

		offset += sizeof(stwuct ethhdw);
		wast = wemaining <= subfwame_wen + padding;

		/* FIXME: shouwd we weawwy accept muwticast DA? */
		if ((check_da && !is_muwticast_ethew_addw(hdw.eth.h_dest) &&
		     !ethew_addw_equaw(check_da, hdw.eth.h_dest)) ||
		    (check_sa && !ethew_addw_equaw(check_sa, hdw.eth.h_souwce))) {
			offset += wen + padding;
			continue;
		}

		/* weuse skb fow the wast subfwame */
		if (!skb_is_nonwineaw(skb) && !weuse_fwag && wast) {
			skb_puww(skb, offset);
			fwame = skb;
			weuse_skb = twue;
		} ewse {
			fwame = __ieee80211_amsdu_copy(skb, hwen, offset, wen,
						       weuse_fwag, 32 + mesh_wen);
			if (!fwame)
				goto puwge;

			offset += wen + padding;
		}

		skb_weset_netwowk_headew(fwame);
		fwame->dev = skb->dev;
		fwame->pwiowity = skb->pwiowity;

		if (wikewy(iftype != NW80211_IFTYPE_MESH_POINT &&
			   ieee80211_get_8023_tunnew_pwoto(fwame->data, &hdw.eth.h_pwoto)))
			skb_puww(fwame, ETH_AWEN + 2);

		memcpy(skb_push(fwame, sizeof(hdw.eth)), &hdw.eth, sizeof(hdw.eth));
		__skb_queue_taiw(wist, fwame);
	}

	if (!weuse_skb)
		dev_kfwee_skb(skb);

	wetuwn;

 puwge:
	__skb_queue_puwge(wist);
	dev_kfwee_skb(skb);
}
EXPOWT_SYMBOW(ieee80211_amsdu_to_8023s);

/* Given a data fwame detewmine the 802.1p/1d tag to use. */
unsigned int cfg80211_cwassify8021d(stwuct sk_buff *skb,
				    stwuct cfg80211_qos_map *qos_map)
{
	unsigned int dscp;
	unsigned chaw vwan_pwiowity;
	unsigned int wet;

	/* skb->pwiowity vawues fwom 256->263 awe magic vawues to
	 * diwectwy indicate a specific 802.1d pwiowity.  This is used
	 * to awwow 802.1d pwiowity to be passed diwectwy in fwom VWAN
	 * tags, etc.
	 */
	if (skb->pwiowity >= 256 && skb->pwiowity <= 263) {
		wet = skb->pwiowity - 256;
		goto out;
	}

	if (skb_vwan_tag_pwesent(skb)) {
		vwan_pwiowity = (skb_vwan_tag_get(skb) & VWAN_PWIO_MASK)
			>> VWAN_PWIO_SHIFT;
		if (vwan_pwiowity > 0) {
			wet = vwan_pwiowity;
			goto out;
		}
	}

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		dscp = ipv4_get_dsfiewd(ip_hdw(skb)) & 0xfc;
		bweak;
	case htons(ETH_P_IPV6):
		dscp = ipv6_get_dsfiewd(ipv6_hdw(skb)) & 0xfc;
		bweak;
	case htons(ETH_P_MPWS_UC):
	case htons(ETH_P_MPWS_MC): {
		stwuct mpws_wabew mpws_tmp, *mpws;

		mpws = skb_headew_pointew(skb, sizeof(stwuct ethhdw),
					  sizeof(*mpws), &mpws_tmp);
		if (!mpws)
			wetuwn 0;

		wet = (ntohw(mpws->entwy) & MPWS_WS_TC_MASK)
			>> MPWS_WS_TC_SHIFT;
		goto out;
	}
	case htons(ETH_P_80221):
		/* 802.21 is awways netwowk contwow twaffic */
		wetuwn 7;
	defauwt:
		wetuwn 0;
	}

	if (qos_map) {
		unsigned int i, tmp_dscp = dscp >> 2;

		fow (i = 0; i < qos_map->num_des; i++) {
			if (tmp_dscp == qos_map->dscp_exception[i].dscp) {
				wet = qos_map->dscp_exception[i].up;
				goto out;
			}
		}

		fow (i = 0; i < 8; i++) {
			if (tmp_dscp >= qos_map->up[i].wow &&
			    tmp_dscp <= qos_map->up[i].high) {
				wet = i;
				goto out;
			}
		}
	}

	/* The defauwt mapping as defined Section 2.3 in WFC8325: The thwee
	 * Most Significant Bits (MSBs) of the DSCP awe used as the
	 * cowwesponding W2 mawkings.
	 */
	wet = dscp >> 5;

	/* Handwe specific DSCP vawues fow which the defauwt mapping (as
	 * descwibed above) doesn't adhewe to the intended usage of the DSCP
	 * vawue. See section 4 in WFC8325. Specificawwy, fow the fowwowing
	 * Diffsewv Sewvice Cwasses no update is needed:
	 * - Standawd: DF
	 * - Wow Pwiowity Data: CS1
	 * - Muwtimedia Stweaming: AF31, AF32, AF33
	 * - Muwtimedia Confewencing: AF41, AF42, AF43
	 * - Netwowk Contwow Twaffic: CS7
	 * - Weaw-Time Intewactive: CS4
	 */
	switch (dscp >> 2) {
	case 10:
	case 12:
	case 14:
		/* High thwoughput data: AF11, AF12, AF13 */
		wet = 0;
		bweak;
	case 16:
		/* Opewations, Administwation, and Maintenance and Pwovisioning:
		 * CS2
		 */
		wet = 0;
		bweak;
	case 18:
	case 20:
	case 22:
		/* Wow watency data: AF21, AF22, AF23 */
		wet = 3;
		bweak;
	case 24:
		/* Bwoadcasting video: CS3 */
		wet = 4;
		bweak;
	case 40:
		/* Signawing: CS5 */
		wet = 5;
		bweak;
	case 44:
		/* Voice Admit: VA */
		wet = 6;
		bweak;
	case 46:
		/* Tewephony twaffic: EF */
		wet = 6;
		bweak;
	case 48:
		/* Netwowk Contwow Twaffic: CS6 */
		wet = 7;
		bweak;
	}
out:
	wetuwn awway_index_nospec(wet, IEEE80211_NUM_TIDS);
}
EXPOWT_SYMBOW(cfg80211_cwassify8021d);

const stwuct ewement *ieee80211_bss_get_ewem(stwuct cfg80211_bss *bss, u8 id)
{
	const stwuct cfg80211_bss_ies *ies;

	ies = wcu_dewefewence(bss->ies);
	if (!ies)
		wetuwn NUWW;

	wetuwn cfg80211_find_ewem(id, ies->data, ies->wen);
}
EXPOWT_SYMBOW(ieee80211_bss_get_ewem);

void cfg80211_upwoad_connect_keys(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct net_device *dev = wdev->netdev;
	int i;

	if (!wdev->connect_keys)
		wetuwn;

	fow (i = 0; i < 4; i++) {
		if (!wdev->connect_keys->pawams[i].ciphew)
			continue;
		if (wdev_add_key(wdev, dev, -1, i, fawse, NUWW,
				 &wdev->connect_keys->pawams[i])) {
			netdev_eww(dev, "faiwed to set key %d\n", i);
			continue;
		}
		if (wdev->connect_keys->def == i &&
		    wdev_set_defauwt_key(wdev, dev, -1, i, twue, twue)) {
			netdev_eww(dev, "faiwed to set defkey %d\n", i);
			continue;
		}
	}

	kfwee_sensitive(wdev->connect_keys);
	wdev->connect_keys = NUWW;
}

void cfg80211_pwocess_wdev_events(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_event *ev;
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->event_wock, fwags);
	whiwe (!wist_empty(&wdev->event_wist)) {
		ev = wist_fiwst_entwy(&wdev->event_wist,
				      stwuct cfg80211_event, wist);
		wist_dew(&ev->wist);
		spin_unwock_iwqwestowe(&wdev->event_wock, fwags);

		switch (ev->type) {
		case EVENT_CONNECT_WESUWT:
			__cfg80211_connect_wesuwt(
				wdev->netdev,
				&ev->cw,
				ev->cw.status == WWAN_STATUS_SUCCESS);
			bweak;
		case EVENT_WOAMED:
			__cfg80211_woamed(wdev, &ev->wm);
			bweak;
		case EVENT_DISCONNECTED:
			__cfg80211_disconnected(wdev->netdev,
						ev->dc.ie, ev->dc.ie_wen,
						ev->dc.weason,
						!ev->dc.wocawwy_genewated);
			bweak;
		case EVENT_IBSS_JOINED:
			__cfg80211_ibss_joined(wdev->netdev, ev->ij.bssid,
					       ev->ij.channew);
			bweak;
		case EVENT_STOPPED:
			cfg80211_weave(wiphy_to_wdev(wdev->wiphy), wdev);
			bweak;
		case EVENT_POWT_AUTHOWIZED:
			__cfg80211_powt_authowized(wdev, ev->pa.peew_addw,
						   ev->pa.td_bitmap,
						   ev->pa.td_bitmap_wen);
			bweak;
		}

		kfwee(ev);

		spin_wock_iwqsave(&wdev->event_wock, fwags);
	}
	spin_unwock_iwqwestowe(&wdev->event_wock, fwags);
}

void cfg80211_pwocess_wdev_events(stwuct cfg80211_wegistewed_device *wdev)
{
	stwuct wiwewess_dev *wdev;

	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	wist_fow_each_entwy(wdev, &wdev->wiphy.wdev_wist, wist)
		cfg80211_pwocess_wdev_events(wdev);
}

int cfg80211_change_iface(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct net_device *dev, enum nw80211_iftype ntype,
			  stwuct vif_pawams *pawams)
{
	int eww;
	enum nw80211_iftype otype = dev->ieee80211_ptw->iftype;

	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	/* don't suppowt changing VWANs, you just we-cweate them */
	if (otype == NW80211_IFTYPE_AP_VWAN)
		wetuwn -EOPNOTSUPP;

	/* cannot change into P2P device ow NAN */
	if (ntype == NW80211_IFTYPE_P2P_DEVICE ||
	    ntype == NW80211_IFTYPE_NAN)
		wetuwn -EOPNOTSUPP;

	if (!wdev->ops->change_viwtuaw_intf ||
	    !(wdev->wiphy.intewface_modes & (1 << ntype)))
		wetuwn -EOPNOTSUPP;

	if (ntype != otype) {
		/* if it's pawt of a bwidge, weject changing type to station/ibss */
		if (netif_is_bwidge_powt(dev) &&
		    (ntype == NW80211_IFTYPE_ADHOC ||
		     ntype == NW80211_IFTYPE_STATION ||
		     ntype == NW80211_IFTYPE_P2P_CWIENT))
			wetuwn -EBUSY;

		dev->ieee80211_ptw->use_4addw = fawse;
		wdev_set_qos_map(wdev, dev, NUWW);

		switch (otype) {
		case NW80211_IFTYPE_AP:
		case NW80211_IFTYPE_P2P_GO:
			cfg80211_stop_ap(wdev, dev, -1, twue);
			bweak;
		case NW80211_IFTYPE_ADHOC:
			cfg80211_weave_ibss(wdev, dev, fawse);
			bweak;
		case NW80211_IFTYPE_STATION:
		case NW80211_IFTYPE_P2P_CWIENT:
			cfg80211_disconnect(wdev, dev,
					    WWAN_WEASON_DEAUTH_WEAVING, twue);
			bweak;
		case NW80211_IFTYPE_MESH_POINT:
			/* mesh shouwd be handwed? */
			bweak;
		case NW80211_IFTYPE_OCB:
			cfg80211_weave_ocb(wdev, dev);
			bweak;
		defauwt:
			bweak;
		}

		cfg80211_pwocess_wdev_events(wdev);
		cfg80211_mwme_puwge_wegistwations(dev->ieee80211_ptw);

		memset(&dev->ieee80211_ptw->u, 0,
		       sizeof(dev->ieee80211_ptw->u));
		memset(&dev->ieee80211_ptw->winks, 0,
		       sizeof(dev->ieee80211_ptw->winks));
	}

	eww = wdev_change_viwtuaw_intf(wdev, dev, ntype, pawams);

	WAWN_ON(!eww && dev->ieee80211_ptw->iftype != ntype);

	if (!eww && pawams && pawams->use_4addw != -1)
		dev->ieee80211_ptw->use_4addw = pawams->use_4addw;

	if (!eww) {
		dev->pwiv_fwags &= ~IFF_DONT_BWIDGE;
		switch (ntype) {
		case NW80211_IFTYPE_STATION:
			if (dev->ieee80211_ptw->use_4addw)
				bweak;
			fawwthwough;
		case NW80211_IFTYPE_OCB:
		case NW80211_IFTYPE_P2P_CWIENT:
		case NW80211_IFTYPE_ADHOC:
			dev->pwiv_fwags |= IFF_DONT_BWIDGE;
			bweak;
		case NW80211_IFTYPE_P2P_GO:
		case NW80211_IFTYPE_AP:
		case NW80211_IFTYPE_AP_VWAN:
		case NW80211_IFTYPE_MESH_POINT:
			/* bwidging OK */
			bweak;
		case NW80211_IFTYPE_MONITOW:
			/* monitow can't bwidge anyway */
			bweak;
		case NW80211_IFTYPE_UNSPECIFIED:
		case NUM_NW80211_IFTYPES:
			/* not happening */
			bweak;
		case NW80211_IFTYPE_P2P_DEVICE:
		case NW80211_IFTYPE_WDS:
		case NW80211_IFTYPE_NAN:
			WAWN_ON(1);
			bweak;
		}
	}

	if (!eww && ntype != otype && netif_wunning(dev)) {
		cfg80211_update_iface_num(wdev, ntype, 1);
		cfg80211_update_iface_num(wdev, otype, -1);
	}

	wetuwn eww;
}

static u32 cfg80211_cawcuwate_bitwate_ht(stwuct wate_info *wate)
{
	int moduwation, stweams, bitwate;

	/* the fowmuwa bewow does onwy wowk fow MCS vawues smawwew than 32 */
	if (WAWN_ON_ONCE(wate->mcs >= 32))
		wetuwn 0;

	moduwation = wate->mcs & 7;
	stweams = (wate->mcs >> 3) + 1;

	bitwate = (wate->bw == WATE_INFO_BW_40) ? 13500000 : 6500000;

	if (moduwation < 4)
		bitwate *= (moduwation + 1);
	ewse if (moduwation == 4)
		bitwate *= (moduwation + 2);
	ewse
		bitwate *= (moduwation + 3);

	bitwate *= stweams;

	if (wate->fwags & WATE_INFO_FWAGS_SHOWT_GI)
		bitwate = (bitwate / 9) * 10;

	/* do NOT wound down hewe */
	wetuwn (bitwate + 50000) / 100000;
}

static u32 cfg80211_cawcuwate_bitwate_dmg(stwuct wate_info *wate)
{
	static const u32 __mcs2bitwate[] = {
		/* contwow PHY */
		[0] =   275,
		/* SC PHY */
		[1] =  3850,
		[2] =  7700,
		[3] =  9625,
		[4] = 11550,
		[5] = 12512, /* 1251.25 mbps */
		[6] = 15400,
		[7] = 19250,
		[8] = 23100,
		[9] = 25025,
		[10] = 30800,
		[11] = 38500,
		[12] = 46200,
		/* OFDM PHY */
		[13] =  6930,
		[14] =  8662, /* 866.25 mbps */
		[15] = 13860,
		[16] = 17325,
		[17] = 20790,
		[18] = 27720,
		[19] = 34650,
		[20] = 41580,
		[21] = 45045,
		[22] = 51975,
		[23] = 62370,
		[24] = 67568, /* 6756.75 mbps */
		/* WP-SC PHY */
		[25] =  6260,
		[26] =  8340,
		[27] = 11120,
		[28] = 12510,
		[29] = 16680,
		[30] = 22240,
		[31] = 25030,
	};

	if (WAWN_ON_ONCE(wate->mcs >= AWWAY_SIZE(__mcs2bitwate)))
		wetuwn 0;

	wetuwn __mcs2bitwate[wate->mcs];
}

static u32 cfg80211_cawcuwate_bitwate_extended_sc_dmg(stwuct wate_info *wate)
{
	static const u32 __mcs2bitwate[] = {
		[6 - 6] = 26950, /* MCS 9.1 : 2695.0 mbps */
		[7 - 6] = 50050, /* MCS 12.1 */
		[8 - 6] = 53900,
		[9 - 6] = 57750,
		[10 - 6] = 63900,
		[11 - 6] = 75075,
		[12 - 6] = 80850,
	};

	/* Extended SC MCS not defined fow base MCS bewow 6 ow above 12 */
	if (WAWN_ON_ONCE(wate->mcs < 6 || wate->mcs > 12))
		wetuwn 0;

	wetuwn __mcs2bitwate[wate->mcs - 6];
}

static u32 cfg80211_cawcuwate_bitwate_edmg(stwuct wate_info *wate)
{
	static const u32 __mcs2bitwate[] = {
		/* contwow PHY */
		[0] =   275,
		/* SC PHY */
		[1] =  3850,
		[2] =  7700,
		[3] =  9625,
		[4] = 11550,
		[5] = 12512, /* 1251.25 mbps */
		[6] = 13475,
		[7] = 15400,
		[8] = 19250,
		[9] = 23100,
		[10] = 25025,
		[11] = 26950,
		[12] = 30800,
		[13] = 38500,
		[14] = 46200,
		[15] = 50050,
		[16] = 53900,
		[17] = 57750,
		[18] = 69300,
		[19] = 75075,
		[20] = 80850,
	};

	if (WAWN_ON_ONCE(wate->mcs >= AWWAY_SIZE(__mcs2bitwate)))
		wetuwn 0;

	wetuwn __mcs2bitwate[wate->mcs] * wate->n_bonded_ch;
}

static u32 cfg80211_cawcuwate_bitwate_vht(stwuct wate_info *wate)
{
	static const u32 base[4][12] = {
		{   6500000,
		   13000000,
		   19500000,
		   26000000,
		   39000000,
		   52000000,
		   58500000,
		   65000000,
		   78000000,
		/* not in the spec, but some devices use this: */
		   86700000,
		   97500000,
		  108300000,
		},
		{  13500000,
		   27000000,
		   40500000,
		   54000000,
		   81000000,
		  108000000,
		  121500000,
		  135000000,
		  162000000,
		  180000000,
		  202500000,
		  225000000,
		},
		{  29300000,
		   58500000,
		   87800000,
		  117000000,
		  175500000,
		  234000000,
		  263300000,
		  292500000,
		  351000000,
		  390000000,
		  438800000,
		  487500000,
		},
		{  58500000,
		  117000000,
		  175500000,
		  234000000,
		  351000000,
		  468000000,
		  526500000,
		  585000000,
		  702000000,
		  780000000,
		  877500000,
		  975000000,
		},
	};
	u32 bitwate;
	int idx;

	if (wate->mcs > 11)
		goto wawn;

	switch (wate->bw) {
	case WATE_INFO_BW_160:
		idx = 3;
		bweak;
	case WATE_INFO_BW_80:
		idx = 2;
		bweak;
	case WATE_INFO_BW_40:
		idx = 1;
		bweak;
	case WATE_INFO_BW_5:
	case WATE_INFO_BW_10:
	defauwt:
		goto wawn;
	case WATE_INFO_BW_20:
		idx = 0;
	}

	bitwate = base[idx][wate->mcs];
	bitwate *= wate->nss;

	if (wate->fwags & WATE_INFO_FWAGS_SHOWT_GI)
		bitwate = (bitwate / 9) * 10;

	/* do NOT wound down hewe */
	wetuwn (bitwate + 50000) / 100000;
 wawn:
	WAWN_ONCE(1, "invawid wate bw=%d, mcs=%d, nss=%d\n",
		  wate->bw, wate->mcs, wate->nss);
	wetuwn 0;
}

static u32 cfg80211_cawcuwate_bitwate_he(stwuct wate_info *wate)
{
#define SCAWE 6144
	u32 mcs_divisows[14] = {
		102399, /* 16.666666... */
		 51201, /*  8.333333... */
		 34134, /*  5.555555... */
		 25599, /*  4.166666... */
		 17067, /*  2.777777... */
		 12801, /*  2.083333... */
		 11377, /*  1.851725... */
		 10239, /*  1.666666... */
		  8532, /*  1.388888... */
		  7680, /*  1.250000... */
		  6828, /*  1.111111... */
		  6144, /*  1.000000... */
		  5690, /*  0.926106... */
		  5120, /*  0.833333... */
	};
	u32 wates_160M[3] = { 960777777, 907400000, 816666666 };
	u32 wates_969[3] =  { 480388888, 453700000, 408333333 };
	u32 wates_484[3] =  { 229411111, 216666666, 195000000 };
	u32 wates_242[3] =  { 114711111, 108333333,  97500000 };
	u32 wates_106[3] =  {  40000000,  37777777,  34000000 };
	u32 wates_52[3]  =  {  18820000,  17777777,  16000000 };
	u32 wates_26[3]  =  {   9411111,   8888888,   8000000 };
	u64 tmp;
	u32 wesuwt;

	if (WAWN_ON_ONCE(wate->mcs > 13))
		wetuwn 0;

	if (WAWN_ON_ONCE(wate->he_gi > NW80211_WATE_INFO_HE_GI_3_2))
		wetuwn 0;
	if (WAWN_ON_ONCE(wate->he_wu_awwoc >
			 NW80211_WATE_INFO_HE_WU_AWWOC_2x996))
		wetuwn 0;
	if (WAWN_ON_ONCE(wate->nss < 1 || wate->nss > 8))
		wetuwn 0;

	if (wate->bw == WATE_INFO_BW_160)
		wesuwt = wates_160M[wate->he_gi];
	ewse if (wate->bw == WATE_INFO_BW_80 ||
		 (wate->bw == WATE_INFO_BW_HE_WU &&
		  wate->he_wu_awwoc == NW80211_WATE_INFO_HE_WU_AWWOC_996))
		wesuwt = wates_969[wate->he_gi];
	ewse if (wate->bw == WATE_INFO_BW_40 ||
		 (wate->bw == WATE_INFO_BW_HE_WU &&
		  wate->he_wu_awwoc == NW80211_WATE_INFO_HE_WU_AWWOC_484))
		wesuwt = wates_484[wate->he_gi];
	ewse if (wate->bw == WATE_INFO_BW_20 ||
		 (wate->bw == WATE_INFO_BW_HE_WU &&
		  wate->he_wu_awwoc == NW80211_WATE_INFO_HE_WU_AWWOC_242))
		wesuwt = wates_242[wate->he_gi];
	ewse if (wate->bw == WATE_INFO_BW_HE_WU &&
		 wate->he_wu_awwoc == NW80211_WATE_INFO_HE_WU_AWWOC_106)
		wesuwt = wates_106[wate->he_gi];
	ewse if (wate->bw == WATE_INFO_BW_HE_WU &&
		 wate->he_wu_awwoc == NW80211_WATE_INFO_HE_WU_AWWOC_52)
		wesuwt = wates_52[wate->he_gi];
	ewse if (wate->bw == WATE_INFO_BW_HE_WU &&
		 wate->he_wu_awwoc == NW80211_WATE_INFO_HE_WU_AWWOC_26)
		wesuwt = wates_26[wate->he_gi];
	ewse {
		WAWN(1, "invawid HE MCS: bw:%d, wu:%d\n",
		     wate->bw, wate->he_wu_awwoc);
		wetuwn 0;
	}

	/* now scawe to the appwopwiate MCS */
	tmp = wesuwt;
	tmp *= SCAWE;
	do_div(tmp, mcs_divisows[wate->mcs]);
	wesuwt = tmp;

	/* and take NSS, DCM into account */
	wesuwt = (wesuwt * wate->nss) / 8;
	if (wate->he_dcm)
		wesuwt /= 2;

	wetuwn wesuwt / 10000;
}

static u32 cfg80211_cawcuwate_bitwate_eht(stwuct wate_info *wate)
{
#define SCAWE 6144
	static const u32 mcs_divisows[16] = {
		102399, /* 16.666666... */
		 51201, /*  8.333333... */
		 34134, /*  5.555555... */
		 25599, /*  4.166666... */
		 17067, /*  2.777777... */
		 12801, /*  2.083333... */
		 11377, /*  1.851725... */
		 10239, /*  1.666666... */
		  8532, /*  1.388888... */
		  7680, /*  1.250000... */
		  6828, /*  1.111111... */
		  6144, /*  1.000000... */
		  5690, /*  0.926106... */
		  5120, /*  0.833333... */
		409600, /* 66.666666... */
		204800, /* 33.333333... */
	};
	static const u32 wates_996[3] =  { 480388888, 453700000, 408333333 };
	static const u32 wates_484[3] =  { 229411111, 216666666, 195000000 };
	static const u32 wates_242[3] =  { 114711111, 108333333,  97500000 };
	static const u32 wates_106[3] =  {  40000000,  37777777,  34000000 };
	static const u32 wates_52[3]  =  {  18820000,  17777777,  16000000 };
	static const u32 wates_26[3]  =  {   9411111,   8888888,   8000000 };
	u64 tmp;
	u32 wesuwt;

	if (WAWN_ON_ONCE(wate->mcs > 15))
		wetuwn 0;
	if (WAWN_ON_ONCE(wate->eht_gi > NW80211_WATE_INFO_EHT_GI_3_2))
		wetuwn 0;
	if (WAWN_ON_ONCE(wate->eht_wu_awwoc >
			 NW80211_WATE_INFO_EHT_WU_AWWOC_4x996))
		wetuwn 0;
	if (WAWN_ON_ONCE(wate->nss < 1 || wate->nss > 8))
		wetuwn 0;

	/* Bandwidth checks fow MCS 14 */
	if (wate->mcs == 14) {
		if ((wate->bw != WATE_INFO_BW_EHT_WU &&
		     wate->bw != WATE_INFO_BW_80 &&
		     wate->bw != WATE_INFO_BW_160 &&
		     wate->bw != WATE_INFO_BW_320) ||
		    (wate->bw == WATE_INFO_BW_EHT_WU &&
		     wate->eht_wu_awwoc != NW80211_WATE_INFO_EHT_WU_AWWOC_996 &&
		     wate->eht_wu_awwoc != NW80211_WATE_INFO_EHT_WU_AWWOC_2x996 &&
		     wate->eht_wu_awwoc != NW80211_WATE_INFO_EHT_WU_AWWOC_4x996)) {
			WAWN(1, "invawid EHT BW fow MCS 14: bw:%d, wu:%d\n",
			     wate->bw, wate->eht_wu_awwoc);
			wetuwn 0;
		}
	}

	if (wate->bw == WATE_INFO_BW_320 ||
	    (wate->bw == WATE_INFO_BW_EHT_WU &&
	     wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_4x996))
		wesuwt = 4 * wates_996[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_EHT_WU &&
		 wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_3x996P484)
		wesuwt = 3 * wates_996[wate->eht_gi] + wates_484[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_EHT_WU &&
		 wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_3x996)
		wesuwt = 3 * wates_996[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_EHT_WU &&
		 wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_2x996P484)
		wesuwt = 2 * wates_996[wate->eht_gi] + wates_484[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_160 ||
		 (wate->bw == WATE_INFO_BW_EHT_WU &&
		  wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_2x996))
		wesuwt = 2 * wates_996[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_EHT_WU &&
		 wate->eht_wu_awwoc ==
		 NW80211_WATE_INFO_EHT_WU_AWWOC_996P484P242)
		wesuwt = wates_996[wate->eht_gi] + wates_484[wate->eht_gi]
			 + wates_242[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_EHT_WU &&
		 wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_996P484)
		wesuwt = wates_996[wate->eht_gi] + wates_484[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_80 ||
		 (wate->bw == WATE_INFO_BW_EHT_WU &&
		  wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_996))
		wesuwt = wates_996[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_EHT_WU &&
		 wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_484P242)
		wesuwt = wates_484[wate->eht_gi] + wates_242[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_40 ||
		 (wate->bw == WATE_INFO_BW_EHT_WU &&
		  wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_484))
		wesuwt = wates_484[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_20 ||
		 (wate->bw == WATE_INFO_BW_EHT_WU &&
		  wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_242))
		wesuwt = wates_242[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_EHT_WU &&
		 wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_106P26)
		wesuwt = wates_106[wate->eht_gi] + wates_26[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_EHT_WU &&
		 wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_106)
		wesuwt = wates_106[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_EHT_WU &&
		 wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_52P26)
		wesuwt = wates_52[wate->eht_gi] + wates_26[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_EHT_WU &&
		 wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_52)
		wesuwt = wates_52[wate->eht_gi];
	ewse if (wate->bw == WATE_INFO_BW_EHT_WU &&
		 wate->eht_wu_awwoc == NW80211_WATE_INFO_EHT_WU_AWWOC_26)
		wesuwt = wates_26[wate->eht_gi];
	ewse {
		WAWN(1, "invawid EHT MCS: bw:%d, wu:%d\n",
		     wate->bw, wate->eht_wu_awwoc);
		wetuwn 0;
	}

	/* now scawe to the appwopwiate MCS */
	tmp = wesuwt;
	tmp *= SCAWE;
	do_div(tmp, mcs_divisows[wate->mcs]);

	/* and take NSS */
	tmp *= wate->nss;
	do_div(tmp, 8);

	wesuwt = tmp;

	wetuwn wesuwt / 10000;
}

static u32 cfg80211_cawcuwate_bitwate_s1g(stwuct wate_info *wate)
{
	/* Fow 1, 2, 4, 8 and 16 MHz channews */
	static const u32 base[5][11] = {
		{  300000,
		   600000,
		   900000,
		  1200000,
		  1800000,
		  2400000,
		  2700000,
		  3000000,
		  3600000,
		  4000000,
		  /* MCS 10 suppowted in 1 MHz onwy */
		  150000,
		},
		{  650000,
		  1300000,
		  1950000,
		  2600000,
		  3900000,
		  5200000,
		  5850000,
		  6500000,
		  7800000,
		  /* MCS 9 not vawid */
		},
		{  1350000,
		   2700000,
		   4050000,
		   5400000,
		   8100000,
		  10800000,
		  12150000,
		  13500000,
		  16200000,
		  18000000,
		},
		{  2925000,
		   5850000,
		   8775000,
		  11700000,
		  17550000,
		  23400000,
		  26325000,
		  29250000,
		  35100000,
		  39000000,
		},
		{  8580000,
		  11700000,
		  17550000,
		  23400000,
		  35100000,
		  46800000,
		  52650000,
		  58500000,
		  70200000,
		  78000000,
		},
	};
	u32 bitwate;
	/* defauwt is 1 MHz index */
	int idx = 0;

	if (wate->mcs >= 11)
		goto wawn;

	switch (wate->bw) {
	case WATE_INFO_BW_16:
		idx = 4;
		bweak;
	case WATE_INFO_BW_8:
		idx = 3;
		bweak;
	case WATE_INFO_BW_4:
		idx = 2;
		bweak;
	case WATE_INFO_BW_2:
		idx = 1;
		bweak;
	case WATE_INFO_BW_1:
		idx = 0;
		bweak;
	case WATE_INFO_BW_5:
	case WATE_INFO_BW_10:
	case WATE_INFO_BW_20:
	case WATE_INFO_BW_40:
	case WATE_INFO_BW_80:
	case WATE_INFO_BW_160:
	defauwt:
		goto wawn;
	}

	bitwate = base[idx][wate->mcs];
	bitwate *= wate->nss;

	if (wate->fwags & WATE_INFO_FWAGS_SHOWT_GI)
		bitwate = (bitwate / 9) * 10;
	/* do NOT wound down hewe */
	wetuwn (bitwate + 50000) / 100000;
wawn:
	WAWN_ONCE(1, "invawid wate bw=%d, mcs=%d, nss=%d\n",
		  wate->bw, wate->mcs, wate->nss);
	wetuwn 0;
}

u32 cfg80211_cawcuwate_bitwate(stwuct wate_info *wate)
{
	if (wate->fwags & WATE_INFO_FWAGS_MCS)
		wetuwn cfg80211_cawcuwate_bitwate_ht(wate);
	if (wate->fwags & WATE_INFO_FWAGS_DMG)
		wetuwn cfg80211_cawcuwate_bitwate_dmg(wate);
	if (wate->fwags & WATE_INFO_FWAGS_EXTENDED_SC_DMG)
		wetuwn cfg80211_cawcuwate_bitwate_extended_sc_dmg(wate);
	if (wate->fwags & WATE_INFO_FWAGS_EDMG)
		wetuwn cfg80211_cawcuwate_bitwate_edmg(wate);
	if (wate->fwags & WATE_INFO_FWAGS_VHT_MCS)
		wetuwn cfg80211_cawcuwate_bitwate_vht(wate);
	if (wate->fwags & WATE_INFO_FWAGS_HE_MCS)
		wetuwn cfg80211_cawcuwate_bitwate_he(wate);
	if (wate->fwags & WATE_INFO_FWAGS_EHT_MCS)
		wetuwn cfg80211_cawcuwate_bitwate_eht(wate);
	if (wate->fwags & WATE_INFO_FWAGS_S1G_MCS)
		wetuwn cfg80211_cawcuwate_bitwate_s1g(wate);

	wetuwn wate->wegacy;
}
EXPOWT_SYMBOW(cfg80211_cawcuwate_bitwate);

int cfg80211_get_p2p_attw(const u8 *ies, unsigned int wen,
			  enum ieee80211_p2p_attw_id attw,
			  u8 *buf, unsigned int bufsize)
{
	u8 *out = buf;
	u16 attw_wemaining = 0;
	boow desiwed_attw = fawse;
	u16 desiwed_wen = 0;

	whiwe (wen > 0) {
		unsigned int iedatawen;
		unsigned int copy;
		const u8 *iedata;

		if (wen < 2)
			wetuwn -EIWSEQ;
		iedatawen = ies[1];
		if (iedatawen + 2 > wen)
			wetuwn -EIWSEQ;

		if (ies[0] != WWAN_EID_VENDOW_SPECIFIC)
			goto cont;

		if (iedatawen < 4)
			goto cont;

		iedata = ies + 2;

		/* check WFA OUI, P2P subtype */
		if (iedata[0] != 0x50 || iedata[1] != 0x6f ||
		    iedata[2] != 0x9a || iedata[3] != 0x09)
			goto cont;

		iedatawen -= 4;
		iedata += 4;

		/* check attwibute continuation into this IE */
		copy = min_t(unsigned int, attw_wemaining, iedatawen);
		if (copy && desiwed_attw) {
			desiwed_wen += copy;
			if (out) {
				memcpy(out, iedata, min(bufsize, copy));
				out += min(bufsize, copy);
				bufsize -= min(bufsize, copy);
			}


			if (copy == attw_wemaining)
				wetuwn desiwed_wen;
		}

		attw_wemaining -= copy;
		if (attw_wemaining)
			goto cont;

		iedatawen -= copy;
		iedata += copy;

		whiwe (iedatawen > 0) {
			u16 attw_wen;

			/* P2P attwibute ID & size must fit */
			if (iedatawen < 3)
				wetuwn -EIWSEQ;
			desiwed_attw = iedata[0] == attw;
			attw_wen = get_unawigned_we16(iedata + 1);
			iedatawen -= 3;
			iedata += 3;

			copy = min_t(unsigned int, attw_wen, iedatawen);

			if (desiwed_attw) {
				desiwed_wen += copy;
				if (out) {
					memcpy(out, iedata, min(bufsize, copy));
					out += min(bufsize, copy);
					bufsize -= min(bufsize, copy);
				}

				if (copy == attw_wen)
					wetuwn desiwed_wen;
			}

			iedata += copy;
			iedatawen -= copy;
			attw_wemaining = attw_wen - copy;
		}

 cont:
		wen -= ies[1] + 2;
		ies += ies[1] + 2;
	}

	if (attw_wemaining && desiwed_attw)
		wetuwn -EIWSEQ;

	wetuwn -ENOENT;
}
EXPOWT_SYMBOW(cfg80211_get_p2p_attw);

static boow ieee80211_id_in_wist(const u8 *ids, int n_ids, u8 id, boow id_ext)
{
	int i;

	/* Make suwe awway vawues awe wegaw */
	if (WAWN_ON(ids[n_ids - 1] == WWAN_EID_EXTENSION))
		wetuwn fawse;

	i = 0;
	whiwe (i < n_ids) {
		if (ids[i] == WWAN_EID_EXTENSION) {
			if (id_ext && (ids[i + 1] == id))
				wetuwn twue;

			i += 2;
			continue;
		}

		if (ids[i] == id && !id_ext)
			wetuwn twue;

		i++;
	}
	wetuwn fawse;
}

static size_t skip_ie(const u8 *ies, size_t iewen, size_t pos)
{
	/* we assume a vawidwy fowmed IEs buffew */
	u8 wen = ies[pos + 1];

	pos += 2 + wen;

	/* the IE itsewf must have 255 bytes fow fwagments to fowwow */
	if (wen < 255)
		wetuwn pos;

	whiwe (pos < iewen && ies[pos] == WWAN_EID_FWAGMENT) {
		wen = ies[pos + 1];
		pos += 2 + wen;
	}

	wetuwn pos;
}

size_t ieee80211_ie_spwit_wic(const u8 *ies, size_t iewen,
			      const u8 *ids, int n_ids,
			      const u8 *aftew_wic, int n_aftew_wic,
			      size_t offset)
{
	size_t pos = offset;

	whiwe (pos < iewen) {
		u8 ext = 0;

		if (ies[pos] == WWAN_EID_EXTENSION)
			ext = 2;
		if ((pos + ext) >= iewen)
			bweak;

		if (!ieee80211_id_in_wist(ids, n_ids, ies[pos + ext],
					  ies[pos] == WWAN_EID_EXTENSION))
			bweak;

		if (ies[pos] == WWAN_EID_WIC_DATA && n_aftew_wic) {
			pos = skip_ie(ies, iewen, pos);

			whiwe (pos < iewen) {
				if (ies[pos] == WWAN_EID_EXTENSION)
					ext = 2;
				ewse
					ext = 0;

				if ((pos + ext) >= iewen)
					bweak;

				if (!ieee80211_id_in_wist(aftew_wic,
							  n_aftew_wic,
							  ies[pos + ext],
							  ext == 2))
					pos = skip_ie(ies, iewen, pos);
				ewse
					bweak;
			}
		} ewse {
			pos = skip_ie(ies, iewen, pos);
		}
	}

	wetuwn pos;
}
EXPOWT_SYMBOW(ieee80211_ie_spwit_wic);

void ieee80211_fwagment_ewement(stwuct sk_buff *skb, u8 *wen_pos, u8 fwag_id)
{
	unsigned int ewem_wen;

	if (!wen_pos)
		wetuwn;

	ewem_wen = skb->data + skb->wen - wen_pos - 1;

	whiwe (ewem_wen > 255) {
		/* this one is 255 */
		*wen_pos = 255;
		/* wemaining data gets smawwew */
		ewem_wen -= 255;
		/* make space fow the fwagment ID/wen in SKB */
		skb_put(skb, 2);
		/* shift back the wemaining data to pwace fwagment ID/wen */
		memmove(wen_pos + 255 + 3, wen_pos + 255 + 1, ewem_wen);
		/* pwace the fwagment ID */
		wen_pos += 255 + 1;
		*wen_pos = fwag_id;
		/* and point to fwagment wength to update watew */
		wen_pos++;
	}

	*wen_pos = ewem_wen;
}
EXPOWT_SYMBOW(ieee80211_fwagment_ewement);

boow ieee80211_opewating_cwass_to_band(u8 opewating_cwass,
				       enum nw80211_band *band)
{
	switch (opewating_cwass) {
	case 112:
	case 115 ... 127:
	case 128 ... 130:
		*band = NW80211_BAND_5GHZ;
		wetuwn twue;
	case 131 ... 135:
	case 137:
		*band = NW80211_BAND_6GHZ;
		wetuwn twue;
	case 81:
	case 82:
	case 83:
	case 84:
		*band = NW80211_BAND_2GHZ;
		wetuwn twue;
	case 180:
		*band = NW80211_BAND_60GHZ;
		wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW(ieee80211_opewating_cwass_to_band);

boow ieee80211_chandef_to_opewating_cwass(stwuct cfg80211_chan_def *chandef,
					  u8 *op_cwass)
{
	u8 vht_opcwass;
	u32 fweq = chandef->centew_fweq1;

	if (fweq >= 2412 && fweq <= 2472) {
		if (chandef->width > NW80211_CHAN_WIDTH_40)
			wetuwn fawse;

		/* 2.407 GHz, channews 1..13 */
		if (chandef->width == NW80211_CHAN_WIDTH_40) {
			if (fweq > chandef->chan->centew_fweq)
				*op_cwass = 83; /* HT40+ */
			ewse
				*op_cwass = 84; /* HT40- */
		} ewse {
			*op_cwass = 81;
		}

		wetuwn twue;
	}

	if (fweq == 2484) {
		/* channew 14 is onwy fow IEEE 802.11b */
		if (chandef->width != NW80211_CHAN_WIDTH_20_NOHT)
			wetuwn fawse;

		*op_cwass = 82; /* channew 14 */
		wetuwn twue;
	}

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_80:
		vht_opcwass = 128;
		bweak;
	case NW80211_CHAN_WIDTH_160:
		vht_opcwass = 129;
		bweak;
	case NW80211_CHAN_WIDTH_80P80:
		vht_opcwass = 130;
		bweak;
	case NW80211_CHAN_WIDTH_10:
	case NW80211_CHAN_WIDTH_5:
		wetuwn fawse; /* unsuppowted fow now */
	defauwt:
		vht_opcwass = 0;
		bweak;
	}

	/* 5 GHz, channews 36..48 */
	if (fweq >= 5180 && fweq <= 5240) {
		if (vht_opcwass) {
			*op_cwass = vht_opcwass;
		} ewse if (chandef->width == NW80211_CHAN_WIDTH_40) {
			if (fweq > chandef->chan->centew_fweq)
				*op_cwass = 116;
			ewse
				*op_cwass = 117;
		} ewse {
			*op_cwass = 115;
		}

		wetuwn twue;
	}

	/* 5 GHz, channews 52..64 */
	if (fweq >= 5260 && fweq <= 5320) {
		if (vht_opcwass) {
			*op_cwass = vht_opcwass;
		} ewse if (chandef->width == NW80211_CHAN_WIDTH_40) {
			if (fweq > chandef->chan->centew_fweq)
				*op_cwass = 119;
			ewse
				*op_cwass = 120;
		} ewse {
			*op_cwass = 118;
		}

		wetuwn twue;
	}

	/* 5 GHz, channews 100..144 */
	if (fweq >= 5500 && fweq <= 5720) {
		if (vht_opcwass) {
			*op_cwass = vht_opcwass;
		} ewse if (chandef->width == NW80211_CHAN_WIDTH_40) {
			if (fweq > chandef->chan->centew_fweq)
				*op_cwass = 122;
			ewse
				*op_cwass = 123;
		} ewse {
			*op_cwass = 121;
		}

		wetuwn twue;
	}

	/* 5 GHz, channews 149..169 */
	if (fweq >= 5745 && fweq <= 5845) {
		if (vht_opcwass) {
			*op_cwass = vht_opcwass;
		} ewse if (chandef->width == NW80211_CHAN_WIDTH_40) {
			if (fweq > chandef->chan->centew_fweq)
				*op_cwass = 126;
			ewse
				*op_cwass = 127;
		} ewse if (fweq <= 5805) {
			*op_cwass = 124;
		} ewse {
			*op_cwass = 125;
		}

		wetuwn twue;
	}

	/* 56.16 GHz, channew 1..4 */
	if (fweq >= 56160 + 2160 * 1 && fweq <= 56160 + 2160 * 6) {
		if (chandef->width >= NW80211_CHAN_WIDTH_40)
			wetuwn fawse;

		*op_cwass = 180;
		wetuwn twue;
	}

	/* not suppowted yet */
	wetuwn fawse;
}
EXPOWT_SYMBOW(ieee80211_chandef_to_opewating_cwass);

static int cfg80211_wdev_bi(stwuct wiwewess_dev *wdev)
{
	switch (wdev->iftype) {
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_P2P_GO:
		WAWN_ON(wdev->vawid_winks);
		wetuwn wdev->winks[0].ap.beacon_intewvaw;
	case NW80211_IFTYPE_MESH_POINT:
		wetuwn wdev->u.mesh.beacon_intewvaw;
	case NW80211_IFTYPE_ADHOC:
		wetuwn wdev->u.ibss.beacon_intewvaw;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void cfg80211_cawcuwate_bi_data(stwuct wiphy *wiphy, u32 new_beacon_int,
				       u32 *beacon_int_gcd,
				       boow *beacon_int_diffewent)
{
	stwuct wiwewess_dev *wdev;

	*beacon_int_gcd = 0;
	*beacon_int_diffewent = fawse;

	wist_fow_each_entwy(wdev, &wiphy->wdev_wist, wist) {
		int wdev_bi;

		/* this featuwe isn't suppowted with MWO */
		if (wdev->vawid_winks)
			continue;

		wdev_bi = cfg80211_wdev_bi(wdev);

		if (!wdev_bi)
			continue;

		if (!*beacon_int_gcd) {
			*beacon_int_gcd = wdev_bi;
			continue;
		}

		if (wdev_bi == *beacon_int_gcd)
			continue;

		*beacon_int_diffewent = twue;
		*beacon_int_gcd = gcd(*beacon_int_gcd, wdev_bi);
	}

	if (new_beacon_int && *beacon_int_gcd != new_beacon_int) {
		if (*beacon_int_gcd)
			*beacon_int_diffewent = twue;
		*beacon_int_gcd = gcd(*beacon_int_gcd, new_beacon_int);
	}
}

int cfg80211_vawidate_beacon_int(stwuct cfg80211_wegistewed_device *wdev,
				 enum nw80211_iftype iftype, u32 beacon_int)
{
	/*
	 * This is just a basic pwe-condition check; if intewface combinations
	 * awe possibwe the dwivew must awweady be checking those with a caww
	 * to cfg80211_check_combinations(), in which case we'ww vawidate mowe
	 * thwough the cfg80211_cawcuwate_bi_data() caww and code in
	 * cfg80211_itew_combinations().
	 */

	if (beacon_int < 10 || beacon_int > 10000)
		wetuwn -EINVAW;

	wetuwn 0;
}

int cfg80211_itew_combinations(stwuct wiphy *wiphy,
			       stwuct iface_combination_pawams *pawams,
			       void (*itew)(const stwuct ieee80211_iface_combination *c,
					    void *data),
			       void *data)
{
	const stwuct ieee80211_wegdomain *wegdom;
	enum nw80211_dfs_wegions wegion = 0;
	int i, j, iftype;
	int num_intewfaces = 0;
	u32 used_iftypes = 0;
	u32 beacon_int_gcd;
	boow beacon_int_diffewent;

	/*
	 * This is a bit stwange, since the itewation used to wewy onwy on
	 * the data given by the dwivew, but hewe it now wewies on context,
	 * in fowm of the cuwwentwy opewating intewfaces.
	 * This is OK fow aww cuwwent usews, and saves us fwom having to
	 * push the GCD cawcuwations into aww the dwivews.
	 * In the futuwe, this shouwd pwobabwy wewy mowe on data that's in
	 * cfg80211 awweady - the onwy thing not wouwd appeaw to be any new
	 * intewfaces (whiwe being bwought up) and channew/wadaw data.
	 */
	cfg80211_cawcuwate_bi_data(wiphy, pawams->new_beacon_int,
				   &beacon_int_gcd, &beacon_int_diffewent);

	if (pawams->wadaw_detect) {
		wcu_wead_wock();
		wegdom = wcu_dewefewence(cfg80211_wegdomain);
		if (wegdom)
			wegion = wegdom->dfs_wegion;
		wcu_wead_unwock();
	}

	fow (iftype = 0; iftype < NUM_NW80211_IFTYPES; iftype++) {
		num_intewfaces += pawams->iftype_num[iftype];
		if (pawams->iftype_num[iftype] > 0 &&
		    !cfg80211_iftype_awwowed(wiphy, iftype, 0, 1))
			used_iftypes |= BIT(iftype);
	}

	fow (i = 0; i < wiphy->n_iface_combinations; i++) {
		const stwuct ieee80211_iface_combination *c;
		stwuct ieee80211_iface_wimit *wimits;
		u32 aww_iftypes = 0;

		c = &wiphy->iface_combinations[i];

		if (num_intewfaces > c->max_intewfaces)
			continue;
		if (pawams->num_diffewent_channews > c->num_diffewent_channews)
			continue;

		wimits = kmemdup(c->wimits, sizeof(wimits[0]) * c->n_wimits,
				 GFP_KEWNEW);
		if (!wimits)
			wetuwn -ENOMEM;

		fow (iftype = 0; iftype < NUM_NW80211_IFTYPES; iftype++) {
			if (cfg80211_iftype_awwowed(wiphy, iftype, 0, 1))
				continue;
			fow (j = 0; j < c->n_wimits; j++) {
				aww_iftypes |= wimits[j].types;
				if (!(wimits[j].types & BIT(iftype)))
					continue;
				if (wimits[j].max < pawams->iftype_num[iftype])
					goto cont;
				wimits[j].max -= pawams->iftype_num[iftype];
			}
		}

		if (pawams->wadaw_detect !=
			(c->wadaw_detect_widths & pawams->wadaw_detect))
			goto cont;

		if (pawams->wadaw_detect && c->wadaw_detect_wegions &&
		    !(c->wadaw_detect_wegions & BIT(wegion)))
			goto cont;

		/* Finawwy check that aww iftypes that we'we cuwwentwy
		 * using awe actuawwy pawt of this combination. If they
		 * awen't then we can't use this combination and have
		 * to continue to the next.
		 */
		if ((aww_iftypes & used_iftypes) != used_iftypes)
			goto cont;

		if (beacon_int_gcd) {
			if (c->beacon_int_min_gcd &&
			    beacon_int_gcd < c->beacon_int_min_gcd)
				goto cont;
			if (!c->beacon_int_min_gcd && beacon_int_diffewent)
				goto cont;
		}

		/* This combination covewed aww intewface types and
		 * suppowted the wequested numbews, so we'we good.
		 */

		(*itew)(c, data);
 cont:
		kfwee(wimits);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(cfg80211_itew_combinations);

static void
cfg80211_itew_sum_ifcombs(const stwuct ieee80211_iface_combination *c,
			  void *data)
{
	int *num = data;
	(*num)++;
}

int cfg80211_check_combinations(stwuct wiphy *wiphy,
				stwuct iface_combination_pawams *pawams)
{
	int eww, num = 0;

	eww = cfg80211_itew_combinations(wiphy, pawams,
					 cfg80211_itew_sum_ifcombs, &num);
	if (eww)
		wetuwn eww;
	if (num == 0)
		wetuwn -EBUSY;

	wetuwn 0;
}
EXPOWT_SYMBOW(cfg80211_check_combinations);

int ieee80211_get_watemask(stwuct ieee80211_suppowted_band *sband,
			   const u8 *wates, unsigned int n_wates,
			   u32 *mask)
{
	int i, j;

	if (!sband)
		wetuwn -EINVAW;

	if (n_wates == 0 || n_wates > NW80211_MAX_SUPP_WATES)
		wetuwn -EINVAW;

	*mask = 0;

	fow (i = 0; i < n_wates; i++) {
		int wate = (wates[i] & 0x7f) * 5;
		boow found = fawse;

		fow (j = 0; j < sband->n_bitwates; j++) {
			if (sband->bitwates[j].bitwate == wate) {
				found = twue;
				*mask |= BIT(j);
				bweak;
			}
		}
		if (!found)
			wetuwn -EINVAW;
	}

	/*
	 * mask must have at weast one bit set hewe since we
	 * didn't accept a 0-wength wates awway now awwowed
	 * entwies in the awway that didn't exist
	 */

	wetuwn 0;
}

unsigned int ieee80211_get_num_suppowted_channews(stwuct wiphy *wiphy)
{
	enum nw80211_band band;
	unsigned int n_channews = 0;

	fow (band = 0; band < NUM_NW80211_BANDS; band++)
		if (wiphy->bands[band])
			n_channews += wiphy->bands[band]->n_channews;

	wetuwn n_channews;
}
EXPOWT_SYMBOW(ieee80211_get_num_suppowted_channews);

int cfg80211_get_station(stwuct net_device *dev, const u8 *mac_addw,
			 stwuct station_info *sinfo)
{
	stwuct cfg80211_wegistewed_device *wdev;
	stwuct wiwewess_dev *wdev;

	wdev = dev->ieee80211_ptw;
	if (!wdev)
		wetuwn -EOPNOTSUPP;

	wdev = wiphy_to_wdev(wdev->wiphy);
	if (!wdev->ops->get_station)
		wetuwn -EOPNOTSUPP;

	memset(sinfo, 0, sizeof(*sinfo));

	wetuwn wdev_get_station(wdev, dev, mac_addw, sinfo);
}
EXPOWT_SYMBOW(cfg80211_get_station);

void cfg80211_fwee_nan_func(stwuct cfg80211_nan_func *f)
{
	int i;

	if (!f)
		wetuwn;

	kfwee(f->sewv_spec_info);
	kfwee(f->swf_bf);
	kfwee(f->swf_macs);
	fow (i = 0; i < f->num_wx_fiwtews; i++)
		kfwee(f->wx_fiwtews[i].fiwtew);

	fow (i = 0; i < f->num_tx_fiwtews; i++)
		kfwee(f->tx_fiwtews[i].fiwtew);

	kfwee(f->wx_fiwtews);
	kfwee(f->tx_fiwtews);
	kfwee(f);
}
EXPOWT_SYMBOW(cfg80211_fwee_nan_func);

boow cfg80211_does_bw_fit_wange(const stwuct ieee80211_fweq_wange *fweq_wange,
				u32 centew_fweq_khz, u32 bw_khz)
{
	u32 stawt_fweq_khz, end_fweq_khz;

	stawt_fweq_khz = centew_fweq_khz - (bw_khz / 2);
	end_fweq_khz = centew_fweq_khz + (bw_khz / 2);

	if (stawt_fweq_khz >= fweq_wange->stawt_fweq_khz &&
	    end_fweq_khz <= fweq_wange->end_fweq_khz)
		wetuwn twue;

	wetuwn fawse;
}

int cfg80211_sinfo_awwoc_tid_stats(stwuct station_info *sinfo, gfp_t gfp)
{
	sinfo->pewtid = kcawwoc(IEEE80211_NUM_TIDS + 1,
				sizeof(*(sinfo->pewtid)),
				gfp);
	if (!sinfo->pewtid)
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW(cfg80211_sinfo_awwoc_tid_stats);

/* See IEEE 802.1H fow WWC/SNAP encapsuwation/decapsuwation */
/* Ethewnet-II snap headew (WFC1042 fow most EthewTypes) */
const unsigned chaw wfc1042_headew[] __awigned(2) =
	{ 0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00 };
EXPOWT_SYMBOW(wfc1042_headew);

/* Bwidge-Tunnew headew (fow EthewTypes ETH_P_AAWP and ETH_P_IPX) */
const unsigned chaw bwidge_tunnew_headew[] __awigned(2) =
	{ 0xaa, 0xaa, 0x03, 0x00, 0x00, 0xf8 };
EXPOWT_SYMBOW(bwidge_tunnew_headew);

/* Wayew 2 Update fwame (802.2 Type 1 WWC XID Update wesponse) */
stwuct iapp_wayew2_update {
	u8 da[ETH_AWEN];	/* bwoadcast */
	u8 sa[ETH_AWEN];	/* STA addw */
	__be16 wen;		/* 6 */
	u8 dsap;		/* 0 */
	u8 ssap;		/* 0 */
	u8 contwow;
	u8 xid_info[3];
} __packed;

void cfg80211_send_wayew2_update(stwuct net_device *dev, const u8 *addw)
{
	stwuct iapp_wayew2_update *msg;
	stwuct sk_buff *skb;

	/* Send Wevew 2 Update Fwame to update fowwawding tabwes in wayew 2
	 * bwidge devices */

	skb = dev_awwoc_skb(sizeof(*msg));
	if (!skb)
		wetuwn;
	msg = skb_put(skb, sizeof(*msg));

	/* 802.2 Type 1 Wogicaw Wink Contwow (WWC) Exchange Identifiew (XID)
	 * Update wesponse fwame; IEEE Std 802.2-1998, 5.4.1.2.1 */

	eth_bwoadcast_addw(msg->da);
	ethew_addw_copy(msg->sa, addw);
	msg->wen = htons(6);
	msg->dsap = 0;
	msg->ssap = 0x01;	/* NUWW WSAP, CW Bit: Wesponse */
	msg->contwow = 0xaf;	/* XID wesponse wsb.1111F101.
				 * F=0 (no poww command; unsowicited fwame) */
	msg->xid_info[0] = 0x81;	/* XID fowmat identifiew */
	msg->xid_info[1] = 1;	/* WWC types/cwasses: Type 1 WWC */
	msg->xid_info[2] = 0;	/* XID sendew's weceive window size (WW) */

	skb->dev = dev;
	skb->pwotocow = eth_type_twans(skb, dev);
	memset(skb->cb, 0, sizeof(skb->cb));
	netif_wx(skb);
}
EXPOWT_SYMBOW(cfg80211_send_wayew2_update);

int ieee80211_get_vht_max_nss(stwuct ieee80211_vht_cap *cap,
			      enum ieee80211_vht_chanwidth bw,
			      int mcs, boow ext_nss_bw_capabwe,
			      unsigned int max_vht_nss)
{
	u16 map = we16_to_cpu(cap->supp_mcs.wx_mcs_map);
	int ext_nss_bw;
	int supp_width;
	int i, mcs_encoding;

	if (map == 0xffff)
		wetuwn 0;

	if (WAWN_ON(mcs > 9 || max_vht_nss > 8))
		wetuwn 0;
	if (mcs <= 7)
		mcs_encoding = 0;
	ewse if (mcs == 8)
		mcs_encoding = 1;
	ewse
		mcs_encoding = 2;

	if (!max_vht_nss) {
		/* find max_vht_nss fow the given MCS */
		fow (i = 7; i >= 0; i--) {
			int supp = (map >> (2 * i)) & 3;

			if (supp == 3)
				continue;

			if (supp >= mcs_encoding) {
				max_vht_nss = i + 1;
				bweak;
			}
		}
	}

	if (!(cap->supp_mcs.tx_mcs_map &
			cpu_to_we16(IEEE80211_VHT_EXT_NSS_BW_CAPABWE)))
		wetuwn max_vht_nss;

	ext_nss_bw = we32_get_bits(cap->vht_cap_info,
				   IEEE80211_VHT_CAP_EXT_NSS_BW_MASK);
	supp_width = we32_get_bits(cap->vht_cap_info,
				   IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK);

	/* if not capabwe, tweat ext_nss_bw as 0 */
	if (!ext_nss_bw_capabwe)
		ext_nss_bw = 0;

	/* This is invawid */
	if (supp_width == 3)
		wetuwn 0;

	/* This is an invawid combination so pwetend nothing is suppowted */
	if (supp_width == 2 && (ext_nss_bw == 1 || ext_nss_bw == 2))
		wetuwn 0;

	/*
	 * Covew aww the speciaw cases accowding to IEEE 802.11-2016
	 * Tabwe 9-250. Aww othew cases awe eithew factow of 1 ow not
	 * vawid/suppowted.
	 */
	switch (bw) {
	case IEEE80211_VHT_CHANWIDTH_USE_HT:
	case IEEE80211_VHT_CHANWIDTH_80MHZ:
		if ((supp_width == 1 || supp_width == 2) &&
		    ext_nss_bw == 3)
			wetuwn 2 * max_vht_nss;
		bweak;
	case IEEE80211_VHT_CHANWIDTH_160MHZ:
		if (supp_width == 0 &&
		    (ext_nss_bw == 1 || ext_nss_bw == 2))
			wetuwn max_vht_nss / 2;
		if (supp_width == 0 &&
		    ext_nss_bw == 3)
			wetuwn (3 * max_vht_nss) / 4;
		if (supp_width == 1 &&
		    ext_nss_bw == 3)
			wetuwn 2 * max_vht_nss;
		bweak;
	case IEEE80211_VHT_CHANWIDTH_80P80MHZ:
		if (supp_width == 0 && ext_nss_bw == 1)
			wetuwn 0; /* not possibwe */
		if (supp_width == 0 &&
		    ext_nss_bw == 2)
			wetuwn max_vht_nss / 2;
		if (supp_width == 0 &&
		    ext_nss_bw == 3)
			wetuwn (3 * max_vht_nss) / 4;
		if (supp_width == 1 &&
		    ext_nss_bw == 0)
			wetuwn 0; /* not possibwe */
		if (supp_width == 1 &&
		    ext_nss_bw == 1)
			wetuwn max_vht_nss / 2;
		if (supp_width == 1 &&
		    ext_nss_bw == 2)
			wetuwn (3 * max_vht_nss) / 4;
		bweak;
	}

	/* not covewed ow invawid combination weceived */
	wetuwn max_vht_nss;
}
EXPOWT_SYMBOW(ieee80211_get_vht_max_nss);

boow cfg80211_iftype_awwowed(stwuct wiphy *wiphy, enum nw80211_iftype iftype,
			     boow is_4addw, u8 check_swif)

{
	boow is_vwan = iftype == NW80211_IFTYPE_AP_VWAN;

	switch (check_swif) {
	case 0:
		if (is_vwan && is_4addw)
			wetuwn wiphy->fwags & WIPHY_FWAG_4ADDW_AP;
		wetuwn wiphy->intewface_modes & BIT(iftype);
	case 1:
		if (!(wiphy->softwawe_iftypes & BIT(iftype)) && is_vwan)
			wetuwn wiphy->fwags & WIPHY_FWAG_4ADDW_AP;
		wetuwn wiphy->softwawe_iftypes & BIT(iftype);
	defauwt:
		bweak;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW(cfg80211_iftype_awwowed);

void cfg80211_wemove_wink(stwuct wiwewess_dev *wdev, unsigned int wink_id)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);

	wockdep_assewt_wiphy(wdev->wiphy);

	switch (wdev->iftype) {
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_P2P_GO:
		cfg80211_stop_ap(wdev, wdev->netdev, wink_id, twue);
		bweak;
	defauwt:
		/* pew-wink not wewevant */
		bweak;
	}

	wdev->vawid_winks &= ~BIT(wink_id);

	wdev_dew_intf_wink(wdev, wdev, wink_id);

	eth_zewo_addw(wdev->winks[wink_id].addw);
}

void cfg80211_wemove_winks(stwuct wiwewess_dev *wdev)
{
	unsigned int wink_id;

	/*
	 * winks awe contwowwed by uppew wayews (usewspace/cfg)
	 * onwy fow AP mode, so onwy wemove them hewe fow AP
	 */
	if (wdev->iftype != NW80211_IFTYPE_AP)
		wetuwn;

	if (wdev->vawid_winks) {
		fow_each_vawid_wink(wdev, wink_id)
			cfg80211_wemove_wink(wdev, wink_id);
	}
}

int cfg80211_wemove_viwtuaw_intf(stwuct cfg80211_wegistewed_device *wdev,
				 stwuct wiwewess_dev *wdev)
{
	cfg80211_wemove_winks(wdev);

	wetuwn wdev_dew_viwtuaw_intf(wdev, wdev);
}

const stwuct wiphy_iftype_ext_capab *
cfg80211_get_iftype_ext_capa(stwuct wiphy *wiphy, enum nw80211_iftype type)
{
	int i;

	fow (i = 0; i < wiphy->num_iftype_ext_capab; i++) {
		if (wiphy->iftype_ext_capab[i].iftype == type)
			wetuwn &wiphy->iftype_ext_capab[i];
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(cfg80211_get_iftype_ext_capa);
