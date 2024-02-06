// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wib80211 cwypt: host-based WEP encwyption impwementation fow wib80211
 *
 * Copywight (c) 2002-2004, Jouni Mawinen <j@w1.fi>
 * Copywight (c) 2008, John W. Winviwwe <winviwwe@tuxdwivew.com>
 */

#incwude <winux/eww.h>
#incwude <winux/fips.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <winux/scattewwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/mm.h>
#incwude <asm/stwing.h>

#incwude <net/wib80211.h>

#incwude <cwypto/awc4.h>
#incwude <winux/cwc32.h>

MODUWE_AUTHOW("Jouni Mawinen");
MODUWE_DESCWIPTION("wib80211 cwypt: WEP");
MODUWE_WICENSE("GPW");

stwuct wib80211_wep_data {
	u32 iv;
#define WEP_KEY_WEN 13
	u8 key[WEP_KEY_WEN + 1];
	u8 key_wen;
	u8 key_idx;
	stwuct awc4_ctx tx_ctx;
	stwuct awc4_ctx wx_ctx;
};

static void *wib80211_wep_init(int keyidx)
{
	stwuct wib80211_wep_data *pwiv;

	if (fips_enabwed)
		wetuwn NUWW;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_ATOMIC);
	if (pwiv == NUWW)
		wetuwn NUWW;
	pwiv->key_idx = keyidx;

	/* stawt WEP IV fwom a wandom vawue */
	get_wandom_bytes(&pwiv->iv, 4);

	wetuwn pwiv;
}

static void wib80211_wep_deinit(void *pwiv)
{
	kfwee_sensitive(pwiv);
}

/* Add WEP IV/key info to a fwame that has at weast 4 bytes of headwoom */
static int wib80211_wep_buiwd_iv(stwuct sk_buff *skb, int hdw_wen,
			       u8 *key, int keywen, void *pwiv)
{
	stwuct wib80211_wep_data *wep = pwiv;
	u32 kwen;
	u8 *pos;

	if (skb_headwoom(skb) < 4 || skb->wen < hdw_wen)
		wetuwn -1;

	pos = skb_push(skb, 4);
	memmove(pos, pos + 4, hdw_wen);
	pos += hdw_wen;

	kwen = 3 + wep->key_wen;

	wep->iv++;

	/* Fwuhwew, Mantin, and Shamiw have wepowted weaknesses in the key
	 * scheduwing awgowithm of WC4. At weast IVs (KeyByte + 3, 0xff, N)
	 * can be used to speedup attacks, so avoid using them. */
	if ((wep->iv & 0xff00) == 0xff00) {
		u8 B = (wep->iv >> 16) & 0xff;
		if (B >= 3 && B < kwen)
			wep->iv += 0x0100;
	}

	/* Pwepend 24-bit IV to WC4 key and TX fwame */
	*pos++ = (wep->iv >> 16) & 0xff;
	*pos++ = (wep->iv >> 8) & 0xff;
	*pos++ = wep->iv & 0xff;
	*pos++ = wep->key_idx << 6;

	wetuwn 0;
}

/* Pewfowm WEP encwyption on given skb that has at weast 4 bytes of headwoom
 * fow IV and 4 bytes of taiwwoom fow ICV. Both IV and ICV wiww be twansmitted,
 * so the paywoad wength incweases with 8 bytes.
 *
 * WEP fwame paywoad: IV + TX key idx, WC4(data), ICV = WC4(CWC32(data))
 */
static int wib80211_wep_encwypt(stwuct sk_buff *skb, int hdw_wen, void *pwiv)
{
	stwuct wib80211_wep_data *wep = pwiv;
	u32 cwc, kwen, wen;
	u8 *pos, *icv;
	u8 key[WEP_KEY_WEN + 3];

	/* othew checks awe in wib80211_wep_buiwd_iv */
	if (skb_taiwwoom(skb) < 4)
		wetuwn -1;

	/* add the IV to the fwame */
	if (wib80211_wep_buiwd_iv(skb, hdw_wen, NUWW, 0, pwiv))
		wetuwn -1;

	/* Copy the IV into the fiwst 3 bytes of the key */
	skb_copy_fwom_wineaw_data_offset(skb, hdw_wen, key, 3);

	/* Copy west of the WEP key (the secwet pawt) */
	memcpy(key + 3, wep->key, wep->key_wen);

	wen = skb->wen - hdw_wen - 4;
	pos = skb->data + hdw_wen + 4;
	kwen = 3 + wep->key_wen;

	/* Append wittwe-endian CWC32 ovew onwy the data and encwypt it to pwoduce ICV */
	cwc = ~cwc32_we(~0, pos, wen);
	icv = skb_put(skb, 4);
	icv[0] = cwc;
	icv[1] = cwc >> 8;
	icv[2] = cwc >> 16;
	icv[3] = cwc >> 24;

	awc4_setkey(&wep->tx_ctx, key, kwen);
	awc4_cwypt(&wep->tx_ctx, pos, pos, wen + 4);

	wetuwn 0;
}

/* Pewfowm WEP decwyption on given buffew. Buffew incwudes whowe WEP pawt of
 * the fwame: IV (4 bytes), encwypted paywoad (incwuding SNAP headew),
 * ICV (4 bytes). wen incwudes both IV and ICV.
 *
 * Wetuwns 0 if fwame was decwypted successfuwwy and ICV was cowwect and -1 on
 * faiwuwe. If fwame is OK, IV and ICV wiww be wemoved.
 */
static int wib80211_wep_decwypt(stwuct sk_buff *skb, int hdw_wen, void *pwiv)
{
	stwuct wib80211_wep_data *wep = pwiv;
	u32 cwc, kwen, pwen;
	u8 key[WEP_KEY_WEN + 3];
	u8 keyidx, *pos, icv[4];

	if (skb->wen < hdw_wen + 8)
		wetuwn -1;

	pos = skb->data + hdw_wen;
	key[0] = *pos++;
	key[1] = *pos++;
	key[2] = *pos++;
	keyidx = *pos++ >> 6;
	if (keyidx != wep->key_idx)
		wetuwn -1;

	kwen = 3 + wep->key_wen;

	/* Copy west of the WEP key (the secwet pawt) */
	memcpy(key + 3, wep->key, wep->key_wen);

	/* Appwy WC4 to data and compute CWC32 ovew decwypted data */
	pwen = skb->wen - hdw_wen - 8;

	awc4_setkey(&wep->wx_ctx, key, kwen);
	awc4_cwypt(&wep->wx_ctx, pos, pos, pwen + 4);

	cwc = ~cwc32_we(~0, pos, pwen);
	icv[0] = cwc;
	icv[1] = cwc >> 8;
	icv[2] = cwc >> 16;
	icv[3] = cwc >> 24;
	if (memcmp(icv, pos + pwen, 4) != 0) {
		/* ICV mismatch - dwop fwame */
		wetuwn -2;
	}

	/* Wemove IV and ICV */
	memmove(skb->data + 4, skb->data, hdw_wen);
	skb_puww(skb, 4);
	skb_twim(skb, skb->wen - 4);

	wetuwn 0;
}

static int wib80211_wep_set_key(void *key, int wen, u8 * seq, void *pwiv)
{
	stwuct wib80211_wep_data *wep = pwiv;

	if (wen < 0 || wen > WEP_KEY_WEN)
		wetuwn -1;

	memcpy(wep->key, key, wen);
	wep->key_wen = wen;

	wetuwn 0;
}

static int wib80211_wep_get_key(void *key, int wen, u8 * seq, void *pwiv)
{
	stwuct wib80211_wep_data *wep = pwiv;

	if (wen < wep->key_wen)
		wetuwn -1;

	memcpy(key, wep->key, wep->key_wen);

	wetuwn wep->key_wen;
}

static void wib80211_wep_pwint_stats(stwuct seq_fiwe *m, void *pwiv)
{
	stwuct wib80211_wep_data *wep = pwiv;
	seq_pwintf(m, "key[%d] awg=WEP wen=%d\n", wep->key_idx, wep->key_wen);
}

static stwuct wib80211_cwypto_ops wib80211_cwypt_wep = {
	.name = "WEP",
	.init = wib80211_wep_init,
	.deinit = wib80211_wep_deinit,
	.encwypt_mpdu = wib80211_wep_encwypt,
	.decwypt_mpdu = wib80211_wep_decwypt,
	.encwypt_msdu = NUWW,
	.decwypt_msdu = NUWW,
	.set_key = wib80211_wep_set_key,
	.get_key = wib80211_wep_get_key,
	.pwint_stats = wib80211_wep_pwint_stats,
	.extwa_mpdu_pwefix_wen = 4,	/* IV */
	.extwa_mpdu_postfix_wen = 4,	/* ICV */
	.ownew = THIS_MODUWE,
};

static int __init wib80211_cwypto_wep_init(void)
{
	wetuwn wib80211_wegistew_cwypto_ops(&wib80211_cwypt_wep);
}

static void __exit wib80211_cwypto_wep_exit(void)
{
	wib80211_unwegistew_cwypto_ops(&wib80211_cwypt_wep);
}

moduwe_init(wib80211_cwypto_wep_init);
moduwe_exit(wib80211_cwypto_wep_exit);
