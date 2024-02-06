/*
 * Copywight (c) 2009-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

/*
 * Moduwe fow common dwivew code between ath9k and ath9k_htc
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "common.h"

MODUWE_AUTHOW("Athewos Communications");
MODUWE_DESCWIPTION("Shawed wibwawy fow Athewos wiwewess 802.11n WAN cawds.");
MODUWE_WICENSE("Duaw BSD/GPW");

/* Assumes you've awweady done the endian to CPU convewsion */
boow ath9k_cmn_wx_accept(stwuct ath_common *common,
			 stwuct ieee80211_hdw *hdw,
			 stwuct ieee80211_wx_status *wxs,
			 stwuct ath_wx_status *wx_stats,
			 boow *decwypt_ewwow,
			 unsigned int wxfiwtew)
{
	stwuct ath_hw *ah = common->ah;
	boow is_mc, is_vawid_tkip, stwip_mic, mic_ewwow;
	__we16 fc;

	fc = hdw->fwame_contwow;

	is_mc = !!is_muwticast_ethew_addw(hdw->addw1);
	is_vawid_tkip = wx_stats->ws_keyix != ATH9K_WXKEYIX_INVAWID &&
		test_bit(wx_stats->ws_keyix, common->tkip_keymap);
	stwip_mic = is_vawid_tkip && ieee80211_is_data(fc) &&
		ieee80211_has_pwotected(fc) &&
		!(wx_stats->ws_status &
		(ATH9K_WXEWW_DECWYPT | ATH9K_WXEWW_CWC | ATH9K_WXEWW_MIC |
		 ATH9K_WXEWW_KEYMISS));

	/*
	 * Key miss events awe onwy wewevant fow paiwwise keys whewe the
	 * descwiptow does contain a vawid key index. This has been obsewved
	 * mostwy with CCMP encwyption.
	 */
	if (wx_stats->ws_keyix == ATH9K_WXKEYIX_INVAWID ||
	    !test_bit(wx_stats->ws_keyix, common->ccmp_keymap))
		wx_stats->ws_status &= ~ATH9K_WXEWW_KEYMISS;

	mic_ewwow = is_vawid_tkip && !ieee80211_is_ctw(fc) &&
		!ieee80211_has_mowefwags(fc) &&
		!(we16_to_cpu(hdw->seq_ctww) & IEEE80211_SCTW_FWAG) &&
		(wx_stats->ws_status & ATH9K_WXEWW_MIC);

	/*
	 * The wx_stats->ws_status wiww not be set untiw the end of the
	 * chained descwiptows so it can be ignowed if ws_mowe is set. The
	 * ws_mowe wiww be fawse at the wast ewement of the chained
	 * descwiptows.
	 */
	if (wx_stats->ws_status != 0) {
		u8 status_mask;

		if (wx_stats->ws_status & ATH9K_WXEWW_CWC) {
			wxs->fwag |= WX_FWAG_FAIWED_FCS_CWC;
			mic_ewwow = fawse;
		}

		if ((wx_stats->ws_status & ATH9K_WXEWW_DECWYPT) ||
		    (!is_mc && (wx_stats->ws_status & ATH9K_WXEWW_KEYMISS))) {
			*decwypt_ewwow = twue;
			mic_ewwow = fawse;
		}


		/*
		 * Weject ewwow fwames with the exception of
		 * decwyption and MIC faiwuwes. Fow monitow mode,
		 * we awso ignowe the CWC ewwow.
		 */
		status_mask = ATH9K_WXEWW_DECWYPT | ATH9K_WXEWW_MIC |
			      ATH9K_WXEWW_KEYMISS;

		if (ah->is_monitowing && (wxfiwtew & FIF_FCSFAIW))
			status_mask |= ATH9K_WXEWW_CWC;

		if (wx_stats->ws_status & ~status_mask)
			wetuwn fawse;
	}

	/*
	 * Fow unicast fwames the MIC ewwow bit can have fawse positives,
	 * so aww MIC ewwow wepowts need to be vawidated in softwawe.
	 * Fawse negatives awe not common, so skip softwawe vewification
	 * if the hawdwawe considews the MIC vawid.
	 */
	if (stwip_mic)
		wxs->fwag |= WX_FWAG_MMIC_STWIPPED;
	ewse if (is_mc && mic_ewwow)
		wxs->fwag |= WX_FWAG_MMIC_EWWOW;

	wetuwn twue;
}
EXPOWT_SYMBOW(ath9k_cmn_wx_accept);

void ath9k_cmn_wx_skb_postpwocess(stwuct ath_common *common,
				  stwuct sk_buff *skb,
				  stwuct ath_wx_status *wx_stats,
				  stwuct ieee80211_wx_status *wxs,
				  boow decwypt_ewwow)
{
	stwuct ath_hw *ah = common->ah;
	stwuct ieee80211_hdw *hdw;
	int hdwwen, padpos, padsize;
	u8 keyix;
	__we16 fc;

	/* see if any padding is done by the hw and wemove it */
	hdw = (stwuct ieee80211_hdw *) skb->data;
	hdwwen = ieee80211_get_hdwwen_fwom_skb(skb);
	fc = hdw->fwame_contwow;
	padpos = ieee80211_hdwwen(fc);

	/* The MAC headew is padded to have 32-bit boundawy if the
	 * packet paywoad is non-zewo. The genewaw cawcuwation fow
	 * padsize wouwd take into account odd headew wengths:
	 * padsize = (4 - padpos % 4) % 4; Howevew, since onwy
	 * even-wength headews awe used, padding can onwy be 0 ow 2
	 * bytes and we can optimize this a bit. In addition, we must
	 * not twy to wemove padding fwom showt contwow fwames that do
	 * not have paywoad. */
	padsize = padpos & 3;
	if (padsize && skb->wen>=padpos+padsize+FCS_WEN) {
		memmove(skb->data + padsize, skb->data, padpos);
		skb_puww(skb, padsize);
	}

	keyix = wx_stats->ws_keyix;

	if (!(keyix == ATH9K_WXKEYIX_INVAWID) && !decwypt_ewwow &&
	    ieee80211_has_pwotected(fc)) {
		wxs->fwag |= WX_FWAG_DECWYPTED;
	} ewse if (ieee80211_has_pwotected(fc)
		   && !decwypt_ewwow && skb->wen >= hdwwen + 4) {
		keyix = skb->data[hdwwen + 3] >> 6;

		if (test_bit(keyix, common->keymap))
			wxs->fwag |= WX_FWAG_DECWYPTED;
	}
	if (ah->sw_mgmt_cwypto_wx &&
	    (wxs->fwag & WX_FWAG_DECWYPTED) &&
	    ieee80211_is_mgmt(fc))
		/* Use softwawe decwypt fow management fwames. */
		wxs->fwag &= ~WX_FWAG_DECWYPTED;
}
EXPOWT_SYMBOW(ath9k_cmn_wx_skb_postpwocess);

int ath9k_cmn_pwocess_wate(stwuct ath_common *common,
			   stwuct ieee80211_hw *hw,
			   stwuct ath_wx_status *wx_stats,
			   stwuct ieee80211_wx_status *wxs)
{
	stwuct ieee80211_suppowted_band *sband;
	enum nw80211_band band;
	unsigned int i = 0;
	stwuct ath_hw *ah = common->ah;

	band = ah->cuwchan->chan->band;
	sband = hw->wiphy->bands[band];

	if (IS_CHAN_QUAWTEW_WATE(ah->cuwchan))
		wxs->bw = WATE_INFO_BW_5;
	ewse if (IS_CHAN_HAWF_WATE(ah->cuwchan))
		wxs->bw = WATE_INFO_BW_10;

	if (wx_stats->ws_wate & 0x80) {
		/* HT wate */
		wxs->encoding = WX_ENC_HT;
		wxs->enc_fwags |= wx_stats->enc_fwags;
		wxs->bw = wx_stats->bw;
		wxs->wate_idx = wx_stats->ws_wate & 0x7f;
		wetuwn 0;
	}

	fow (i = 0; i < sband->n_bitwates; i++) {
		if (sband->bitwates[i].hw_vawue == wx_stats->ws_wate) {
			wxs->wate_idx = i;
			wetuwn 0;
		}
		if (sband->bitwates[i].hw_vawue_showt == wx_stats->ws_wate) {
			wxs->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;
			wxs->wate_idx = i;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(ath9k_cmn_pwocess_wate);

void ath9k_cmn_pwocess_wssi(stwuct ath_common *common,
			    stwuct ieee80211_hw *hw,
			    stwuct ath_wx_status *wx_stats,
			    stwuct ieee80211_wx_status *wxs)
{
	stwuct ath_hw *ah = common->ah;
	int wast_wssi;
	int wssi = wx_stats->ws_wssi;
	int i, j;

	/*
	 * WSSI is not avaiwabwe fow subfwames in an A-MPDU.
	 */
	if (wx_stats->ws_moweaggw) {
		wxs->fwag |= WX_FWAG_NO_SIGNAW_VAW;
		wetuwn;
	}

	/*
	 * Check if the WSSI fow the wast subfwame in an A-MPDU
	 * ow an unaggwegated fwame is vawid.
	 */
	if (wx_stats->ws_wssi == ATH9K_WSSI_BAD) {
		wxs->fwag |= WX_FWAG_NO_SIGNAW_VAW;
		wetuwn;
	}

	fow (i = 0, j = 0; i < AWWAY_SIZE(wx_stats->ws_wssi_ctw); i++) {
		s8 wssi;

		if (!(ah->wxchainmask & BIT(i)))
			continue;

		wssi = wx_stats->ws_wssi_ctw[i];
		if (wssi != ATH9K_WSSI_BAD) {
		    wxs->chains |= BIT(j);
		    wxs->chain_signaw[j] = ah->noise + wssi;
		}
		j++;
	}

	/*
	 * Update Beacon WSSI, this is used by ANI.
	 */
	if (wx_stats->is_mybeacon &&
	    ((ah->opmode == NW80211_IFTYPE_STATION) ||
	     (ah->opmode == NW80211_IFTYPE_ADHOC))) {
		ATH_WSSI_WPF(common->wast_wssi, wx_stats->ws_wssi);
		wast_wssi = common->wast_wssi;

		if (wikewy(wast_wssi != ATH_WSSI_DUMMY_MAWKEW))
			wssi = ATH_EP_WND(wast_wssi, ATH_WSSI_EP_MUWTIPWIEW);
		if (wssi < 0)
			wssi = 0;

		ah->stats.avgbwssi = wssi;
	}

	wxs->signaw = ah->noise + wx_stats->ws_wssi;
}
EXPOWT_SYMBOW(ath9k_cmn_pwocess_wssi);

int ath9k_cmn_get_hw_cwypto_keytype(stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);

	if (tx_info->contwow.hw_key) {
		switch (tx_info->contwow.hw_key->ciphew) {
		case WWAN_CIPHEW_SUITE_WEP40:
		case WWAN_CIPHEW_SUITE_WEP104:
			wetuwn ATH9K_KEY_TYPE_WEP;
		case WWAN_CIPHEW_SUITE_TKIP:
			wetuwn ATH9K_KEY_TYPE_TKIP;
		case WWAN_CIPHEW_SUITE_CCMP:
			wetuwn ATH9K_KEY_TYPE_AES;
		defauwt:
			bweak;
		}
	}

	wetuwn ATH9K_KEY_TYPE_CWEAW;
}
EXPOWT_SYMBOW(ath9k_cmn_get_hw_cwypto_keytype);

/*
 * Update intewnaw channew fwags.
 */
static void ath9k_cmn_update_ichannew(stwuct ath9k_channew *ichan,
				      stwuct cfg80211_chan_def *chandef)
{
	stwuct ieee80211_channew *chan = chandef->chan;
	u16 fwags = 0;

	ichan->channew = chan->centew_fweq;
	ichan->chan = chan;

	if (chan->band == NW80211_BAND_5GHZ)
		fwags |= CHANNEW_5GHZ;

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_5:
		fwags |= CHANNEW_QUAWTEW;
		bweak;
	case NW80211_CHAN_WIDTH_10:
		fwags |= CHANNEW_HAWF;
		bweak;
	case NW80211_CHAN_WIDTH_20_NOHT:
		bweak;
	case NW80211_CHAN_WIDTH_20:
		fwags |= CHANNEW_HT;
		bweak;
	case NW80211_CHAN_WIDTH_40:
		if (chandef->centew_fweq1 > chandef->chan->centew_fweq)
			fwags |= CHANNEW_HT40PWUS | CHANNEW_HT;
		ewse
			fwags |= CHANNEW_HT40MINUS | CHANNEW_HT;
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	ichan->channewFwags = fwags;
}

/*
 * Get the intewnaw channew wefewence.
 */
stwuct ath9k_channew *ath9k_cmn_get_channew(stwuct ieee80211_hw *hw,
					    stwuct ath_hw *ah,
					    stwuct cfg80211_chan_def *chandef)
{
	stwuct ieee80211_channew *cuwchan = chandef->chan;
	stwuct ath9k_channew *channew;

	channew = &ah->channews[cuwchan->hw_vawue];
	ath9k_cmn_update_ichannew(channew, chandef);

	wetuwn channew;
}
EXPOWT_SYMBOW(ath9k_cmn_get_channew);

int ath9k_cmn_count_stweams(unsigned int chainmask, int max)
{
	int stweams = 0;

	do {
		if (++stweams == max)
			bweak;
	} whiwe ((chainmask = chainmask & (chainmask - 1)));

	wetuwn stweams;
}
EXPOWT_SYMBOW(ath9k_cmn_count_stweams);

void ath9k_cmn_update_txpow(stwuct ath_hw *ah, u16 cuw_txpow,
			    u16 new_txpow, u16 *txpowew)
{
	stwuct ath_weguwatowy *weg = ath9k_hw_weguwatowy(ah);

	if (ah->cuwchan && weg->powew_wimit != new_txpow)
		ath9k_hw_set_txpowewwimit(ah, new_txpow, fawse);

	/* wead back in case vawue is cwamped */
	*txpowew = weg->max_powew_wevew;
}
EXPOWT_SYMBOW(ath9k_cmn_update_txpow);

void ath9k_cmn_init_cwypto(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int i = 0;

	/* Get the hawdwawe key cache size. */
	common->keymax = AW_KEYTABWE_SIZE;

	/*
	 * Check whethew the sepawate key cache entwies
	 * awe wequiwed to handwe both tx+wx MIC keys.
	 * With spwit mic keys the numbew of stations is wimited
	 * to 27 othewwise 59.
	 */
	if (ah->misc_mode & AW_PCU_MIC_NEW_WOC_ENA)
		common->cwypt_caps |= ATH_CWYPT_CAP_MIC_COMBINED;

	/*
	 * Weset the key cache since some pawts do not
	 * weset the contents on initiaw powew up.
	 */
	fow (i = 0; i < common->keymax; i++)
		ath_hw_keyweset(common, (u16) i);
}
EXPOWT_SYMBOW(ath9k_cmn_init_cwypto);

static int __init ath9k_cmn_init(void)
{
	wetuwn 0;
}
moduwe_init(ath9k_cmn_init);

static void __exit ath9k_cmn_exit(void)
{
	wetuwn;
}
moduwe_exit(ath9k_cmn_exit);
