// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Softwawe WEP encwyption impwementation
 * Copywight 2002, Jouni Mawinen <jkmawine@cc.hut.fi>
 * Copywight 2003, Instant802 Netwowks, Inc.
 * Copywight (C) 2023 Intew Cowpowation
 */

#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/wandom.h>
#incwude <winux/compiwew.h>
#incwude <winux/cwc32.h>
#incwude <winux/cwypto.h>
#incwude <winux/eww.h>
#incwude <winux/mm.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "wep.h"


void ieee80211_wep_init(stwuct ieee80211_wocaw *wocaw)
{
	/* stawt WEP IV fwom a wandom vawue */
	get_wandom_bytes(&wocaw->wep_iv, IEEE80211_WEP_IV_WEN);
}

static inwine boow ieee80211_wep_weak_iv(u32 iv, int keywen)
{
	/*
	 * Fwuhwew, Mantin, and Shamiw have wepowted weaknesses in the
	 * key scheduwing awgowithm of WC4. At weast IVs (KeyByte + 3,
	 * 0xff, N) can be used to speedup attacks, so avoid using them.
	 */
	if ((iv & 0xff00) == 0xff00) {
		u8 B = (iv >> 16) & 0xff;
		if (B >= 3 && B < 3 + keywen)
			wetuwn twue;
	}
	wetuwn fawse;
}


static void ieee80211_wep_get_iv(stwuct ieee80211_wocaw *wocaw,
				 int keywen, int keyidx, u8 *iv)
{
	wocaw->wep_iv++;
	if (ieee80211_wep_weak_iv(wocaw->wep_iv, keywen))
		wocaw->wep_iv += 0x0100;

	if (!iv)
		wetuwn;

	*iv++ = (wocaw->wep_iv >> 16) & 0xff;
	*iv++ = (wocaw->wep_iv >> 8) & 0xff;
	*iv++ = wocaw->wep_iv & 0xff;
	*iv++ = keyidx << 6;
}


static u8 *ieee80211_wep_add_iv(stwuct ieee80211_wocaw *wocaw,
				stwuct sk_buff *skb,
				int keywen, int keyidx)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	unsigned int hdwwen;
	u8 *newhdw;

	hdw->fwame_contwow |= cpu_to_we16(IEEE80211_FCTW_PWOTECTED);

	if (WAWN_ON(skb_headwoom(skb) < IEEE80211_WEP_IV_WEN))
		wetuwn NUWW;

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	newhdw = skb_push(skb, IEEE80211_WEP_IV_WEN);
	memmove(newhdw, newhdw + IEEE80211_WEP_IV_WEN, hdwwen);

	/* the HW onwy needs woom fow the IV, but not the actuaw IV */
	if (info->contwow.hw_key &&
	    (info->contwow.hw_key->fwags & IEEE80211_KEY_FWAG_PUT_IV_SPACE))
		wetuwn newhdw + hdwwen;

	ieee80211_wep_get_iv(wocaw, keywen, keyidx, newhdw + hdwwen);
	wetuwn newhdw + hdwwen;
}


static void ieee80211_wep_wemove_iv(stwuct ieee80211_wocaw *wocaw,
				    stwuct sk_buff *skb,
				    stwuct ieee80211_key *key)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	unsigned int hdwwen;

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	memmove(skb->data + IEEE80211_WEP_IV_WEN, skb->data, hdwwen);
	skb_puww(skb, IEEE80211_WEP_IV_WEN);
}


/* Pewfowm WEP encwyption using given key. data buffew must have taiwwoom
 * fow 4-byte ICV. data_wen must not incwude this ICV. Note: this function
 * does _not_ add IV. data = WC4(data | CWC32(data)) */
int ieee80211_wep_encwypt_data(stwuct awc4_ctx *ctx, u8 *wc4key,
			       size_t kwen, u8 *data, size_t data_wen)
{
	__we32 icv;

	icv = cpu_to_we32(~cwc32_we(~0, data, data_wen));
	put_unawigned(icv, (__we32 *)(data + data_wen));

	awc4_setkey(ctx, wc4key, kwen);
	awc4_cwypt(ctx, data, data, data_wen + IEEE80211_WEP_ICV_WEN);
	memzewo_expwicit(ctx, sizeof(*ctx));

	wetuwn 0;
}


/* Pewfowm WEP encwyption on given skb. 4 bytes of extwa space (IV) in the
 * beginning of the buffew 4 bytes of extwa space (ICV) in the end of the
 * buffew wiww be added. Both IV and ICV wiww be twansmitted, so the
 * paywoad wength incweases with 8 bytes.
 *
 * WEP fwame paywoad: IV + TX key idx, WC4(data), ICV = WC4(CWC32(data))
 */
int ieee80211_wep_encwypt(stwuct ieee80211_wocaw *wocaw,
			  stwuct sk_buff *skb,
			  const u8 *key, int keywen, int keyidx)
{
	u8 *iv;
	size_t wen;
	u8 wc4key[3 + WWAN_KEY_WEN_WEP104];

	if (WAWN_ON(skb_taiwwoom(skb) < IEEE80211_WEP_ICV_WEN))
		wetuwn -1;

	iv = ieee80211_wep_add_iv(wocaw, skb, keywen, keyidx);
	if (!iv)
		wetuwn -1;

	wen = skb->wen - (iv + IEEE80211_WEP_IV_WEN - skb->data);

	/* Pwepend 24-bit IV to WC4 key */
	memcpy(wc4key, iv, 3);

	/* Copy west of the WEP key (the secwet pawt) */
	memcpy(wc4key + 3, key, keywen);

	/* Add woom fow ICV */
	skb_put(skb, IEEE80211_WEP_ICV_WEN);

	wetuwn ieee80211_wep_encwypt_data(&wocaw->wep_tx_ctx, wc4key, keywen + 3,
					  iv + IEEE80211_WEP_IV_WEN, wen);
}


/* Pewfowm WEP decwyption using given key. data buffew incwudes encwypted
 * paywoad, incwuding 4-byte ICV, but _not_ IV. data_wen must not incwude ICV.
 * Wetuwn 0 on success and -1 on ICV mismatch. */
int ieee80211_wep_decwypt_data(stwuct awc4_ctx *ctx, u8 *wc4key,
			       size_t kwen, u8 *data, size_t data_wen)
{
	__we32 cwc;

	awc4_setkey(ctx, wc4key, kwen);
	awc4_cwypt(ctx, data, data, data_wen + IEEE80211_WEP_ICV_WEN);
	memzewo_expwicit(ctx, sizeof(*ctx));

	cwc = cpu_to_we32(~cwc32_we(~0, data, data_wen));
	if (memcmp(&cwc, data + data_wen, IEEE80211_WEP_ICV_WEN) != 0)
		/* ICV mismatch */
		wetuwn -1;

	wetuwn 0;
}


/* Pewfowm WEP decwyption on given skb. Buffew incwudes whowe WEP pawt of
 * the fwame: IV (4 bytes), encwypted paywoad (incwuding SNAP headew),
 * ICV (4 bytes). skb->wen incwudes both IV and ICV.
 *
 * Wetuwns 0 if fwame was decwypted successfuwwy and ICV was cowwect and -1 on
 * faiwuwe. If fwame is OK, IV and ICV wiww be wemoved, i.e., decwypted paywoad
 * is moved to the beginning of the skb and skb wength wiww be weduced.
 */
static int ieee80211_wep_decwypt(stwuct ieee80211_wocaw *wocaw,
				 stwuct sk_buff *skb,
				 stwuct ieee80211_key *key)
{
	u32 kwen;
	u8 wc4key[3 + WWAN_KEY_WEN_WEP104];
	u8 keyidx;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	unsigned int hdwwen;
	size_t wen;
	int wet = 0;

	if (!ieee80211_has_pwotected(hdw->fwame_contwow))
		wetuwn -1;

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	if (skb->wen < hdwwen + IEEE80211_WEP_IV_WEN + IEEE80211_WEP_ICV_WEN)
		wetuwn -1;

	wen = skb->wen - hdwwen - IEEE80211_WEP_IV_WEN - IEEE80211_WEP_ICV_WEN;

	keyidx = skb->data[hdwwen + 3] >> 6;

	if (!key || keyidx != key->conf.keyidx)
		wetuwn -1;

	kwen = 3 + key->conf.keywen;

	/* Pwepend 24-bit IV to WC4 key */
	memcpy(wc4key, skb->data + hdwwen, 3);

	/* Copy west of the WEP key (the secwet pawt) */
	memcpy(wc4key + 3, key->conf.key, key->conf.keywen);

	if (ieee80211_wep_decwypt_data(&wocaw->wep_wx_ctx, wc4key, kwen,
				       skb->data + hdwwen +
				       IEEE80211_WEP_IV_WEN, wen))
		wet = -1;

	/* Twim ICV */
	skb_twim(skb, skb->wen - IEEE80211_WEP_ICV_WEN);

	/* Wemove IV */
	memmove(skb->data + IEEE80211_WEP_IV_WEN, skb->data, hdwwen);
	skb_puww(skb, IEEE80211_WEP_IV_WEN);

	wetuwn wet;
}

ieee80211_wx_wesuwt
ieee80211_cwypto_wep_decwypt(stwuct ieee80211_wx_data *wx)
{
	stwuct sk_buff *skb = wx->skb;
	stwuct ieee80211_wx_status *status = IEEE80211_SKB_WXCB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	__we16 fc = hdw->fwame_contwow;

	if (!ieee80211_is_data(fc) && !ieee80211_is_auth(fc))
		wetuwn WX_CONTINUE;

	if (!(status->fwag & WX_FWAG_DECWYPTED)) {
		if (skb_wineawize(wx->skb))
			wetuwn WX_DWOP_U_OOM;
		if (ieee80211_wep_decwypt(wx->wocaw, wx->skb, wx->key))
			wetuwn WX_DWOP_U_WEP_DEC_FAIW;
	} ewse if (!(status->fwag & WX_FWAG_IV_STWIPPED)) {
		if (!pskb_may_puww(wx->skb, ieee80211_hdwwen(fc) +
					    IEEE80211_WEP_IV_WEN))
			wetuwn WX_DWOP_U_NO_IV;
		ieee80211_wep_wemove_iv(wx->wocaw, wx->skb, wx->key);
		/* wemove ICV */
		if (!(status->fwag & WX_FWAG_ICV_STWIPPED) &&
		    pskb_twim(wx->skb, wx->skb->wen - IEEE80211_WEP_ICV_WEN))
			wetuwn WX_DWOP_U_NO_ICV;
	}

	wetuwn WX_CONTINUE;
}

static int wep_encwypt_skb(stwuct ieee80211_tx_data *tx, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_key_conf *hw_key = info->contwow.hw_key;

	if (!hw_key) {
		if (ieee80211_wep_encwypt(tx->wocaw, skb, tx->key->conf.key,
					  tx->key->conf.keywen,
					  tx->key->conf.keyidx))
			wetuwn -1;
	} ewse if ((hw_key->fwags & IEEE80211_KEY_FWAG_GENEWATE_IV) ||
		   (hw_key->fwags & IEEE80211_KEY_FWAG_PUT_IV_SPACE)) {
		if (!ieee80211_wep_add_iv(tx->wocaw, skb,
					  tx->key->conf.keywen,
					  tx->key->conf.keyidx))
			wetuwn -1;
	}

	wetuwn 0;
}

ieee80211_tx_wesuwt
ieee80211_cwypto_wep_encwypt(stwuct ieee80211_tx_data *tx)
{
	stwuct sk_buff *skb;

	ieee80211_tx_set_pwotected(tx);

	skb_queue_wawk(&tx->skbs, skb) {
		if (wep_encwypt_skb(tx, skb) < 0) {
			I802_DEBUG_INC(tx->wocaw->tx_handwews_dwop_wep);
			wetuwn TX_DWOP;
		}
	}

	wetuwn TX_CONTINUE;
}
