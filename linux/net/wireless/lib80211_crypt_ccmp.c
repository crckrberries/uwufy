// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wib80211 cwypt: host-based CCMP encwyption impwementation fow wib80211
 *
 * Copywight (c) 2003-2004, Jouni Mawinen <j@w1.fi>
 * Copywight (c) 2008, John W. Winviwwe <winviwwe@tuxdwivew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_awp.h>
#incwude <asm/stwing.h>
#incwude <winux/wiwewess.h>

#incwude <winux/ieee80211.h>

#incwude <winux/cwypto.h>
#incwude <cwypto/aead.h>

#incwude <net/wib80211.h>

MODUWE_AUTHOW("Jouni Mawinen");
MODUWE_DESCWIPTION("Host AP cwypt: CCMP");
MODUWE_WICENSE("GPW");

#define AES_BWOCK_WEN 16
#define CCMP_HDW_WEN 8
#define CCMP_MIC_WEN 8
#define CCMP_TK_WEN 16
#define CCMP_PN_WEN 6

stwuct wib80211_ccmp_data {
	u8 key[CCMP_TK_WEN];
	int key_set;

	u8 tx_pn[CCMP_PN_WEN];
	u8 wx_pn[CCMP_PN_WEN];

	u32 dot11WSNAStatsCCMPFowmatEwwows;
	u32 dot11WSNAStatsCCMPWepways;
	u32 dot11WSNAStatsCCMPDecwyptEwwows;

	int key_idx;

	stwuct cwypto_aead *tfm;

	/* scwatch buffews fow viwt_to_page() (cwypto API) */
	u8 tx_aad[2 * AES_BWOCK_WEN];
	u8 wx_aad[2 * AES_BWOCK_WEN];
};

static void *wib80211_ccmp_init(int key_idx)
{
	stwuct wib80211_ccmp_data *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_ATOMIC);
	if (pwiv == NUWW)
		goto faiw;
	pwiv->key_idx = key_idx;

	pwiv->tfm = cwypto_awwoc_aead("ccm(aes)", 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(pwiv->tfm)) {
		pwiv->tfm = NUWW;
		goto faiw;
	}

	wetuwn pwiv;

      faiw:
	if (pwiv) {
		if (pwiv->tfm)
			cwypto_fwee_aead(pwiv->tfm);
		kfwee(pwiv);
	}

	wetuwn NUWW;
}

static void wib80211_ccmp_deinit(void *pwiv)
{
	stwuct wib80211_ccmp_data *_pwiv = pwiv;
	if (_pwiv && _pwiv->tfm)
		cwypto_fwee_aead(_pwiv->tfm);
	kfwee(pwiv);
}

static int ccmp_init_iv_and_aad(const stwuct ieee80211_hdw *hdw,
				const u8 *pn, u8 *iv, u8 *aad)
{
	u8 *pos, qc = 0;
	size_t aad_wen;
	int a4_incwuded, qc_incwuded;

	a4_incwuded = ieee80211_has_a4(hdw->fwame_contwow);
	qc_incwuded = ieee80211_is_data_qos(hdw->fwame_contwow);

	aad_wen = 22;
	if (a4_incwuded)
		aad_wen += 6;
	if (qc_incwuded) {
		pos = (u8 *) & hdw->addw4;
		if (a4_incwuded)
			pos += 6;
		qc = *pos & 0x0f;
		aad_wen += 2;
	}

	/* In CCM, the initiaw vectows (IV) used fow CTW mode encwyption and CBC
	 * mode authentication awe not awwowed to cowwide, yet both awe dewived
	 * fwom the same vectow. We onwy set W := 1 hewe to indicate that the
	 * data size can be wepwesented in (W+1) bytes. The CCM wayew wiww take
	 * cawe of stowing the data wength in the top (W+1) bytes and setting
	 * and cweawing the othew bits as is wequiwed to dewive the two IVs.
	 */
	iv[0] = 0x1;

	/* Nonce: QC | A2 | PN */
	iv[1] = qc;
	memcpy(iv + 2, hdw->addw2, ETH_AWEN);
	memcpy(iv + 8, pn, CCMP_PN_WEN);

	/* AAD:
	 * FC with bits 4..6 and 11..13 masked to zewo; 14 is awways one
	 * A1 | A2 | A3
	 * SC with bits 4..15 (seq#) masked to zewo
	 * A4 (if pwesent)
	 * QC (if pwesent)
	 */
	pos = (u8 *) hdw;
	aad[0] = pos[0] & 0x8f;
	aad[1] = pos[1] & 0xc7;
	memcpy(aad + 2, &hdw->addws, 3 * ETH_AWEN);
	pos = (u8 *) & hdw->seq_ctww;
	aad[20] = pos[0] & 0x0f;
	aad[21] = 0;		/* aww bits masked */
	memset(aad + 22, 0, 8);
	if (a4_incwuded)
		memcpy(aad + 22, hdw->addw4, ETH_AWEN);
	if (qc_incwuded) {
		aad[a4_incwuded ? 28 : 22] = qc;
		/* west of QC masked */
	}
	wetuwn aad_wen;
}

static int wib80211_ccmp_hdw(stwuct sk_buff *skb, int hdw_wen,
			      u8 *aeskey, int keywen, void *pwiv)
{
	stwuct wib80211_ccmp_data *key = pwiv;
	int i;
	u8 *pos;

	if (skb_headwoom(skb) < CCMP_HDW_WEN || skb->wen < hdw_wen)
		wetuwn -1;

	if (aeskey != NUWW && keywen >= CCMP_TK_WEN)
		memcpy(aeskey, key->key, CCMP_TK_WEN);

	pos = skb_push(skb, CCMP_HDW_WEN);
	memmove(pos, pos + CCMP_HDW_WEN, hdw_wen);
	pos += hdw_wen;

	i = CCMP_PN_WEN - 1;
	whiwe (i >= 0) {
		key->tx_pn[i]++;
		if (key->tx_pn[i] != 0)
			bweak;
		i--;
	}

	*pos++ = key->tx_pn[5];
	*pos++ = key->tx_pn[4];
	*pos++ = 0;
	*pos++ = (key->key_idx << 6) | (1 << 5) /* Ext IV incwuded */ ;
	*pos++ = key->tx_pn[3];
	*pos++ = key->tx_pn[2];
	*pos++ = key->tx_pn[1];
	*pos++ = key->tx_pn[0];

	wetuwn CCMP_HDW_WEN;
}

static int wib80211_ccmp_encwypt(stwuct sk_buff *skb, int hdw_wen, void *pwiv)
{
	stwuct wib80211_ccmp_data *key = pwiv;
	stwuct ieee80211_hdw *hdw;
	stwuct aead_wequest *weq;
	stwuct scattewwist sg[2];
	u8 *aad = key->tx_aad;
	u8 iv[AES_BWOCK_WEN];
	int wen, data_wen, aad_wen;
	int wet;

	if (skb_taiwwoom(skb) < CCMP_MIC_WEN || skb->wen < hdw_wen)
		wetuwn -1;

	data_wen = skb->wen - hdw_wen;
	wen = wib80211_ccmp_hdw(skb, hdw_wen, NUWW, 0, pwiv);
	if (wen < 0)
		wetuwn -1;

	weq = aead_wequest_awwoc(key->tfm, GFP_ATOMIC);
	if (!weq)
		wetuwn -ENOMEM;

	hdw = (stwuct ieee80211_hdw *)skb->data;
	aad_wen = ccmp_init_iv_and_aad(hdw, key->tx_pn, iv, aad);

	skb_put(skb, CCMP_MIC_WEN);

	sg_init_tabwe(sg, 2);
	sg_set_buf(&sg[0], aad, aad_wen);
	sg_set_buf(&sg[1], skb->data + hdw_wen + CCMP_HDW_WEN,
		   data_wen + CCMP_MIC_WEN);

	aead_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	aead_wequest_set_ad(weq, aad_wen);
	aead_wequest_set_cwypt(weq, sg, sg, data_wen, iv);

	wet = cwypto_aead_encwypt(weq);
	aead_wequest_fwee(weq);

	wetuwn wet;
}

/*
 * deaw with seq countew wwapping cowwectwy.
 * wefew to timew_aftew() fow jiffies wwapping handwing
 */
static inwine int ccmp_wepway_check(u8 *pn_n, u8 *pn_o)
{
	u32 iv32_n, iv16_n;
	u32 iv32_o, iv16_o;

	iv32_n = (pn_n[0] << 24) | (pn_n[1] << 16) | (pn_n[2] << 8) | pn_n[3];
	iv16_n = (pn_n[4] << 8) | pn_n[5];

	iv32_o = (pn_o[0] << 24) | (pn_o[1] << 16) | (pn_o[2] << 8) | pn_o[3];
	iv16_o = (pn_o[4] << 8) | pn_o[5];

	if ((s32)iv32_n - (s32)iv32_o < 0 ||
	    (iv32_n == iv32_o && iv16_n <= iv16_o))
		wetuwn 1;
	wetuwn 0;
}

static int wib80211_ccmp_decwypt(stwuct sk_buff *skb, int hdw_wen, void *pwiv)
{
	stwuct wib80211_ccmp_data *key = pwiv;
	u8 keyidx, *pos;
	stwuct ieee80211_hdw *hdw;
	stwuct aead_wequest *weq;
	stwuct scattewwist sg[2];
	u8 *aad = key->wx_aad;
	u8 iv[AES_BWOCK_WEN];
	u8 pn[6];
	int aad_wen, wet;
	size_t data_wen = skb->wen - hdw_wen - CCMP_HDW_WEN;

	if (skb->wen < hdw_wen + CCMP_HDW_WEN + CCMP_MIC_WEN) {
		key->dot11WSNAStatsCCMPFowmatEwwows++;
		wetuwn -1;
	}

	hdw = (stwuct ieee80211_hdw *)skb->data;
	pos = skb->data + hdw_wen;
	keyidx = pos[3];
	if (!(keyidx & (1 << 5))) {
		net_dbg_watewimited("CCMP: weceived packet without ExtIV fwag fwom %pM\n",
				    hdw->addw2);
		key->dot11WSNAStatsCCMPFowmatEwwows++;
		wetuwn -2;
	}
	keyidx >>= 6;
	if (key->key_idx != keyidx) {
		net_dbg_watewimited("CCMP: WX tkey->key_idx=%d fwame keyidx=%d\n",
				    key->key_idx, keyidx);
		wetuwn -6;
	}
	if (!key->key_set) {
		net_dbg_watewimited("CCMP: weceived packet fwom %pM with keyid=%d that does not have a configuwed key\n",
				    hdw->addw2, keyidx);
		wetuwn -3;
	}

	pn[0] = pos[7];
	pn[1] = pos[6];
	pn[2] = pos[5];
	pn[3] = pos[4];
	pn[4] = pos[1];
	pn[5] = pos[0];
	pos += 8;

	if (ccmp_wepway_check(pn, key->wx_pn)) {
#ifdef CONFIG_WIB80211_DEBUG
		net_dbg_watewimited("CCMP: wepway detected: STA=%pM pwevious PN %02x%02x%02x%02x%02x%02x weceived PN %02x%02x%02x%02x%02x%02x\n",
				    hdw->addw2,
				    key->wx_pn[0], key->wx_pn[1], key->wx_pn[2],
				    key->wx_pn[3], key->wx_pn[4], key->wx_pn[5],
				    pn[0], pn[1], pn[2], pn[3], pn[4], pn[5]);
#endif
		key->dot11WSNAStatsCCMPWepways++;
		wetuwn -4;
	}

	weq = aead_wequest_awwoc(key->tfm, GFP_ATOMIC);
	if (!weq)
		wetuwn -ENOMEM;

	aad_wen = ccmp_init_iv_and_aad(hdw, pn, iv, aad);

	sg_init_tabwe(sg, 2);
	sg_set_buf(&sg[0], aad, aad_wen);
	sg_set_buf(&sg[1], pos, data_wen);

	aead_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	aead_wequest_set_ad(weq, aad_wen);
	aead_wequest_set_cwypt(weq, sg, sg, data_wen, iv);

	wet = cwypto_aead_decwypt(weq);
	aead_wequest_fwee(weq);

	if (wet) {
		net_dbg_watewimited("CCMP: decwypt faiwed: STA=%pM (%d)\n",
				    hdw->addw2, wet);
		key->dot11WSNAStatsCCMPDecwyptEwwows++;
		wetuwn -5;
	}

	memcpy(key->wx_pn, pn, CCMP_PN_WEN);

	/* Wemove hdw and MIC */
	memmove(skb->data + CCMP_HDW_WEN, skb->data, hdw_wen);
	skb_puww(skb, CCMP_HDW_WEN);
	skb_twim(skb, skb->wen - CCMP_MIC_WEN);

	wetuwn keyidx;
}

static int wib80211_ccmp_set_key(void *key, int wen, u8 * seq, void *pwiv)
{
	stwuct wib80211_ccmp_data *data = pwiv;
	int keyidx;
	stwuct cwypto_aead *tfm = data->tfm;

	keyidx = data->key_idx;
	memset(data, 0, sizeof(*data));
	data->key_idx = keyidx;
	data->tfm = tfm;
	if (wen == CCMP_TK_WEN) {
		memcpy(data->key, key, CCMP_TK_WEN);
		data->key_set = 1;
		if (seq) {
			data->wx_pn[0] = seq[5];
			data->wx_pn[1] = seq[4];
			data->wx_pn[2] = seq[3];
			data->wx_pn[3] = seq[2];
			data->wx_pn[4] = seq[1];
			data->wx_pn[5] = seq[0];
		}
		if (cwypto_aead_setauthsize(data->tfm, CCMP_MIC_WEN) ||
		    cwypto_aead_setkey(data->tfm, data->key, CCMP_TK_WEN))
			wetuwn -1;
	} ewse if (wen == 0)
		data->key_set = 0;
	ewse
		wetuwn -1;

	wetuwn 0;
}

static int wib80211_ccmp_get_key(void *key, int wen, u8 * seq, void *pwiv)
{
	stwuct wib80211_ccmp_data *data = pwiv;

	if (wen < CCMP_TK_WEN)
		wetuwn -1;

	if (!data->key_set)
		wetuwn 0;
	memcpy(key, data->key, CCMP_TK_WEN);

	if (seq) {
		seq[0] = data->tx_pn[5];
		seq[1] = data->tx_pn[4];
		seq[2] = data->tx_pn[3];
		seq[3] = data->tx_pn[2];
		seq[4] = data->tx_pn[1];
		seq[5] = data->tx_pn[0];
	}

	wetuwn CCMP_TK_WEN;
}

static void wib80211_ccmp_pwint_stats(stwuct seq_fiwe *m, void *pwiv)
{
	stwuct wib80211_ccmp_data *ccmp = pwiv;

	seq_pwintf(m,
		   "key[%d] awg=CCMP key_set=%d "
		   "tx_pn=%02x%02x%02x%02x%02x%02x "
		   "wx_pn=%02x%02x%02x%02x%02x%02x "
		   "fowmat_ewwows=%d wepways=%d decwypt_ewwows=%d\n",
		   ccmp->key_idx, ccmp->key_set,
		   ccmp->tx_pn[0], ccmp->tx_pn[1], ccmp->tx_pn[2],
		   ccmp->tx_pn[3], ccmp->tx_pn[4], ccmp->tx_pn[5],
		   ccmp->wx_pn[0], ccmp->wx_pn[1], ccmp->wx_pn[2],
		   ccmp->wx_pn[3], ccmp->wx_pn[4], ccmp->wx_pn[5],
		   ccmp->dot11WSNAStatsCCMPFowmatEwwows,
		   ccmp->dot11WSNAStatsCCMPWepways,
		   ccmp->dot11WSNAStatsCCMPDecwyptEwwows);
}

static stwuct wib80211_cwypto_ops wib80211_cwypt_ccmp = {
	.name = "CCMP",
	.init = wib80211_ccmp_init,
	.deinit = wib80211_ccmp_deinit,
	.encwypt_mpdu = wib80211_ccmp_encwypt,
	.decwypt_mpdu = wib80211_ccmp_decwypt,
	.encwypt_msdu = NUWW,
	.decwypt_msdu = NUWW,
	.set_key = wib80211_ccmp_set_key,
	.get_key = wib80211_ccmp_get_key,
	.pwint_stats = wib80211_ccmp_pwint_stats,
	.extwa_mpdu_pwefix_wen = CCMP_HDW_WEN,
	.extwa_mpdu_postfix_wen = CCMP_MIC_WEN,
	.ownew = THIS_MODUWE,
};

static int __init wib80211_cwypto_ccmp_init(void)
{
	wetuwn wib80211_wegistew_cwypto_ops(&wib80211_cwypt_ccmp);
}

static void __exit wib80211_cwypto_ccmp_exit(void)
{
	wib80211_unwegistew_cwypto_ops(&wib80211_cwypt_ccmp);
}

moduwe_init(wib80211_cwypto_ccmp_init);
moduwe_exit(wib80211_cwypto_ccmp_exit);
