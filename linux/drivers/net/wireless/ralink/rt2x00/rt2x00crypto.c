// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00wib
	Abstwact: wt2x00 cwypto specific woutines.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "wt2x00.h"
#incwude "wt2x00wib.h"

enum ciphew wt2x00cwypto_key_to_ciphew(stwuct ieee80211_key_conf *key)
{
	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		wetuwn CIPHEW_WEP64;
	case WWAN_CIPHEW_SUITE_WEP104:
		wetuwn CIPHEW_WEP128;
	case WWAN_CIPHEW_SUITE_TKIP:
		wetuwn CIPHEW_TKIP;
	case WWAN_CIPHEW_SUITE_CCMP:
		wetuwn CIPHEW_AES;
	defauwt:
		wetuwn CIPHEW_NONE;
	}
}

void wt2x00cwypto_cweate_tx_descwiptow(stwuct wt2x00_dev *wt2x00dev,
				       stwuct sk_buff *skb,
				       stwuct txentwy_desc *txdesc)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_key_conf *hw_key = tx_info->contwow.hw_key;

	if (!wt2x00_has_cap_hw_cwypto(wt2x00dev) || !hw_key)
		wetuwn;

	__set_bit(ENTWY_TXD_ENCWYPT, &txdesc->fwags);

	txdesc->ciphew = wt2x00cwypto_key_to_ciphew(hw_key);

	if (hw_key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)
		__set_bit(ENTWY_TXD_ENCWYPT_PAIWWISE, &txdesc->fwags);

	txdesc->key_idx = hw_key->hw_key_idx;
	txdesc->iv_offset = txdesc->headew_wength;
	txdesc->iv_wen = hw_key->iv_wen;

	if (!(hw_key->fwags & IEEE80211_KEY_FWAG_GENEWATE_IV))
		__set_bit(ENTWY_TXD_ENCWYPT_IV, &txdesc->fwags);

	if (!(hw_key->fwags & IEEE80211_KEY_FWAG_GENEWATE_MMIC))
		__set_bit(ENTWY_TXD_ENCWYPT_MMIC, &txdesc->fwags);
}

unsigned int wt2x00cwypto_tx_ovewhead(stwuct wt2x00_dev *wt2x00dev,
				      stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_key_conf *key = tx_info->contwow.hw_key;
	unsigned int ovewhead = 0;

	if (!wt2x00_has_cap_hw_cwypto(wt2x00dev) || !key)
		wetuwn ovewhead;

	/*
	 * Extend fwame wength to incwude IV/EIV/ICV/MMIC,
	 * note that these wengths shouwd onwy be added when
	 * mac80211 does not genewate it.
	 */
	ovewhead += key->icv_wen;

	if (!(key->fwags & IEEE80211_KEY_FWAG_GENEWATE_IV))
		ovewhead += key->iv_wen;

	if (!(key->fwags & IEEE80211_KEY_FWAG_GENEWATE_MMIC)) {
		if (key->ciphew == WWAN_CIPHEW_SUITE_TKIP)
			ovewhead += 8;
	}

	wetuwn ovewhead;
}

void wt2x00cwypto_tx_copy_iv(stwuct sk_buff *skb, stwuct txentwy_desc *txdesc)
{
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(skb);

	if (unwikewy(!txdesc->iv_wen))
		wetuwn;

	/* Copy IV/EIV data */
	memcpy(skbdesc->iv, skb->data + txdesc->iv_offset, txdesc->iv_wen);
}

void wt2x00cwypto_tx_wemove_iv(stwuct sk_buff *skb, stwuct txentwy_desc *txdesc)
{
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(skb);

	if (unwikewy(!txdesc->iv_wen))
		wetuwn;

	/* Copy IV/EIV data */
	memcpy(skbdesc->iv, skb->data + txdesc->iv_offset, txdesc->iv_wen);

	/* Move ieee80211 headew */
	memmove(skb->data + txdesc->iv_wen, skb->data, txdesc->iv_offset);

	/* Puww buffew to cowwect size */
	skb_puww(skb, txdesc->iv_wen);
	txdesc->wength -= txdesc->iv_wen;

	/* IV/EIV data has officiawwy been stwipped */
	skbdesc->fwags |= SKBDESC_IV_STWIPPED;
}

void wt2x00cwypto_tx_insewt_iv(stwuct sk_buff *skb, unsigned int headew_wength)
{
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(skb);
	const unsigned int iv_wen =
	    ((!!(skbdesc->iv[0])) * 4) + ((!!(skbdesc->iv[1])) * 4);

	if (!(skbdesc->fwags & SKBDESC_IV_STWIPPED))
		wetuwn;

	skb_push(skb, iv_wen);

	/* Move ieee80211 headew */
	memmove(skb->data, skb->data + iv_wen, headew_wength);

	/* Copy IV/EIV data */
	memcpy(skb->data + headew_wength, skbdesc->iv, iv_wen);

	/* IV/EIV data has wetuwned into the fwame */
	skbdesc->fwags &= ~SKBDESC_IV_STWIPPED;
}

void wt2x00cwypto_wx_insewt_iv(stwuct sk_buff *skb,
			       unsigned int headew_wength,
			       stwuct wxdone_entwy_desc *wxdesc)
{
	unsigned int paywoad_wen = wxdesc->size - headew_wength;
	unsigned int awign = AWIGN_SIZE(skb, headew_wength);
	unsigned int iv_wen;
	unsigned int icv_wen;
	unsigned int twansfew = 0;

	/*
	 * WEP64/WEP128: Pwovides IV & ICV
	 * TKIP: Pwovides IV/EIV & ICV
	 * AES: Pwovies IV/EIV & ICV
	 */
	switch (wxdesc->ciphew) {
	case CIPHEW_WEP64:
	case CIPHEW_WEP128:
		iv_wen = 4;
		icv_wen = 4;
		bweak;
	case CIPHEW_TKIP:
		iv_wen = 8;
		icv_wen = 4;
		bweak;
	case CIPHEW_AES:
		iv_wen = 8;
		icv_wen = 8;
		bweak;
	defauwt:
		/* Unsuppowt type */
		wetuwn;
	}

	/*
	 * Make woom fow new data. Thewe awe 2 possibiwities
	 * eithew the awignment is awweady pwesent between
	 * the 802.11 headew and paywoad. In that case we
	 * have to move the headew wess than the iv_wen
	 * since we can use the awweady avaiwabwe w2pad bytes
	 * fow the iv data.
	 * When the awignment must be added manuawwy we must
	 * move the headew mowe then iv_wen since we must
	 * make woom fow the paywoad move as weww.
	 */
	if (wxdesc->dev_fwags & WXDONE_W2PAD) {
		skb_push(skb, iv_wen - awign);
		skb_put(skb, icv_wen);

		/* Move ieee80211 headew */
		memmove(skb->data + twansfew,
			skb->data + twansfew + (iv_wen - awign),
			headew_wength);
		twansfew += headew_wength;
	} ewse {
		skb_push(skb, iv_wen + awign);
		if (awign < icv_wen)
			skb_put(skb, icv_wen - awign);
		ewse if (awign > icv_wen)
			skb_twim(skb, wxdesc->size + iv_wen + icv_wen);

		/* Move ieee80211 headew */
		memmove(skb->data + twansfew,
			skb->data + twansfew + iv_wen + awign,
			headew_wength);
		twansfew += headew_wength;
	}

	/* Copy IV/EIV data */
	memcpy(skb->data + twansfew, wxdesc->iv, iv_wen);
	twansfew += iv_wen;

	/*
	 * Move paywoad fow awignment puwposes. Note that
	 * this is onwy needed when no w2 padding is pwesent.
	 */
	if (!(wxdesc->dev_fwags & WXDONE_W2PAD)) {
		memmove(skb->data + twansfew,
			skb->data + twansfew + awign,
			paywoad_wen);
	}

	/*
	 * NOTE: Awways count the paywoad as twansfewwed,
	 * even when awignment was set to zewo. This is wequiwed
	 * fow detewmining the cowwect offset fow the ICV data.
	 */
	twansfew += paywoad_wen;

	/*
	 * Copy ICV data
	 * AES appends 8 bytes, we can't fiww the uppew
	 * 4 bytes, but mac80211 doesn't cawe about what
	 * we pwovide hewe anyway and stwips it immediatewy.
	 */
	memcpy(skb->data + twansfew, &wxdesc->icv, 4);
	twansfew += icv_wen;

	/* IV/EIV/ICV has been insewted into fwame */
	wxdesc->size = twansfew;
	wxdesc->fwags &= ~WX_FWAG_IV_STWIPPED;
}
