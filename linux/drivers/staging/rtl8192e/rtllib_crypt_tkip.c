// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Host AP cwypt: host-based TKIP encwyption impwementation fow Host AP dwivew
 *
 * Copywight (c) 2003-2004, Jouni Mawinen <jkmawine@cc.hut.fi>
 */

#incwude <cwypto/awc4.h>
#incwude <cwypto/hash.h>
#incwude <winux/fips.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_awp.h>
#incwude <winux/stwing.h>
#incwude <winux/cwc32.h>
#incwude <winux/ethewdevice.h>

#incwude "wtwwib.h"

stwuct wtwwib_tkip_data {
#define TKIP_KEY_WEN 32
	u8 key[TKIP_KEY_WEN];
	int key_set;

	u32 tx_iv32;
	u16 tx_iv16;
	u16 tx_ttak[5];
	int tx_phase1_done;

	u32 wx_iv32;
	u16 wx_iv16;
	boow initiawized;
	u16 wx_ttak[5];
	int wx_phase1_done;
	u32 wx_iv32_new;
	u16 wx_iv16_new;

	u32 dot11WSNAStatsTKIPWepways;
	u32 dot11WSNAStatsTKIPICVEwwows;
	u32 dot11WSNAStatsTKIPWocawMICFaiwuwes;

	int key_idx;
	stwuct awc4_ctx wx_ctx_awc4;
	stwuct awc4_ctx tx_ctx_awc4;
	stwuct cwypto_shash *wx_tfm_michaew;
	stwuct cwypto_shash *tx_tfm_michaew;
	/* scwatch buffews fow viwt_to_page() (cwypto API) */
	u8 wx_hdw[16];
	u8 tx_hdw[16];
};

static void *wtwwib_tkip_init(int key_idx)
{
	stwuct wtwwib_tkip_data *pwiv;

	if (fips_enabwed)
		wetuwn NUWW;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_ATOMIC);
	if (!pwiv)
		goto faiw;
	pwiv->key_idx = key_idx;

	pwiv->tx_tfm_michaew = cwypto_awwoc_shash("michaew_mic", 0, 0);
	if (IS_EWW(pwiv->tx_tfm_michaew)) {
		pw_debug("Couwd not awwocate cwypto API michaew_mic\n");
		pwiv->tx_tfm_michaew = NUWW;
		goto faiw;
	}

	pwiv->wx_tfm_michaew = cwypto_awwoc_shash("michaew_mic", 0, 0);
	if (IS_EWW(pwiv->wx_tfm_michaew)) {
		pw_debug("Couwd not awwocate cwypto API michaew_mic\n");
		pwiv->wx_tfm_michaew = NUWW;
		goto faiw;
	}
	wetuwn pwiv;

faiw:
	if (pwiv) {
		cwypto_fwee_shash(pwiv->tx_tfm_michaew);
		cwypto_fwee_shash(pwiv->wx_tfm_michaew);
		kfwee(pwiv);
	}

	wetuwn NUWW;
}

static void wtwwib_tkip_deinit(void *pwiv)
{
	stwuct wtwwib_tkip_data *_pwiv = pwiv;

	if (_pwiv) {
		cwypto_fwee_shash(_pwiv->tx_tfm_michaew);
		cwypto_fwee_shash(_pwiv->wx_tfm_michaew);
	}
	kfwee_sensitive(pwiv);
}

static inwine u16 WotW1(u16 vaw)
{
	wetuwn (vaw >> 1) | (vaw << 15);
}

static inwine u8 Wo8(u16 vaw)
{
	wetuwn vaw & 0xff;
}

static inwine u8 Hi8(u16 vaw)
{
	wetuwn vaw >> 8;
}

static inwine u16 Wo16(u32 vaw)
{
	wetuwn vaw & 0xffff;
}

static inwine u16 Hi16(u32 vaw)
{
	wetuwn vaw >> 16;
}

static inwine u16 Mk16(u8 hi, u8 wo)
{
	wetuwn wo | (hi << 8);
}

static inwine u16 Mk16_we(u16 *v)
{
	wetuwn *v;
}

static const u16 Sbox[256] = {
	0xC6A5, 0xF884, 0xEE99, 0xF68D, 0xFF0D, 0xD6BD, 0xDEB1, 0x9154,
	0x6050, 0x0203, 0xCEA9, 0x567D, 0xE719, 0xB562, 0x4DE6, 0xEC9A,
	0x8F45, 0x1F9D, 0x8940, 0xFA87, 0xEF15, 0xB2EB, 0x8EC9, 0xFB0B,
	0x41EC, 0xB367, 0x5FFD, 0x45EA, 0x23BF, 0x53F7, 0xE496, 0x9B5B,
	0x75C2, 0xE11C, 0x3DAE, 0x4C6A, 0x6C5A, 0x7E41, 0xF502, 0x834F,
	0x685C, 0x51F4, 0xD134, 0xF908, 0xE293, 0xAB73, 0x6253, 0x2A3F,
	0x080C, 0x9552, 0x4665, 0x9D5E, 0x3028, 0x37A1, 0x0A0F, 0x2FB5,
	0x0E09, 0x2436, 0x1B9B, 0xDF3D, 0xCD26, 0x4E69, 0x7FCD, 0xEA9F,
	0x121B, 0x1D9E, 0x5874, 0x342E, 0x362D, 0xDCB2, 0xB4EE, 0x5BFB,
	0xA4F6, 0x764D, 0xB761, 0x7DCE, 0x527B, 0xDD3E, 0x5E71, 0x1397,
	0xA6F5, 0xB968, 0x0000, 0xC12C, 0x4060, 0xE31F, 0x79C8, 0xB6ED,
	0xD4BE, 0x8D46, 0x67D9, 0x724B, 0x94DE, 0x98D4, 0xB0E8, 0x854A,
	0xBB6B, 0xC52A, 0x4FE5, 0xED16, 0x86C5, 0x9AD7, 0x6655, 0x1194,
	0x8ACF, 0xE910, 0x0406, 0xFE81, 0xA0F0, 0x7844, 0x25BA, 0x4BE3,
	0xA2F3, 0x5DFE, 0x80C0, 0x058A, 0x3FAD, 0x21BC, 0x7048, 0xF104,
	0x63DF, 0x77C1, 0xAF75, 0x4263, 0x2030, 0xE51A, 0xFD0E, 0xBF6D,
	0x814C, 0x1814, 0x2635, 0xC32F, 0xBEE1, 0x35A2, 0x88CC, 0x2E39,
	0x9357, 0x55F2, 0xFC82, 0x7A47, 0xC8AC, 0xBAE7, 0x322B, 0xE695,
	0xC0A0, 0x1998, 0x9ED1, 0xA37F, 0x4466, 0x547E, 0x3BAB, 0x0B83,
	0x8CCA, 0xC729, 0x6BD3, 0x283C, 0xA779, 0xBCE2, 0x161D, 0xAD76,
	0xDB3B, 0x6456, 0x744E, 0x141E, 0x92DB, 0x0C0A, 0x486C, 0xB8E4,
	0x9F5D, 0xBD6E, 0x43EF, 0xC4A6, 0x39A8, 0x31A4, 0xD337, 0xF28B,
	0xD532, 0x8B43, 0x6E59, 0xDAB7, 0x018C, 0xB164, 0x9CD2, 0x49E0,
	0xD8B4, 0xACFA, 0xF307, 0xCF25, 0xCAAF, 0xF48E, 0x47E9, 0x1018,
	0x6FD5, 0xF088, 0x4A6F, 0x5C72, 0x3824, 0x57F1, 0x73C7, 0x9751,
	0xCB23, 0xA17C, 0xE89C, 0x3E21, 0x96DD, 0x61DC, 0x0D86, 0x0F85,
	0xE090, 0x7C42, 0x71C4, 0xCCAA, 0x90D8, 0x0605, 0xF701, 0x1C12,
	0xC2A3, 0x6A5F, 0xAEF9, 0x69D0, 0x1791, 0x9958, 0x3A27, 0x27B9,
	0xD938, 0xEB13, 0x2BB3, 0x2233, 0xD2BB, 0xA970, 0x0789, 0x33A7,
	0x2DB6, 0x3C22, 0x1592, 0xC920, 0x8749, 0xAAFF, 0x5078, 0xA57A,
	0x038F, 0x59F8, 0x0980, 0x1A17, 0x65DA, 0xD731, 0x84C6, 0xD0B8,
	0x82C3, 0x29B0, 0x5A77, 0x1E11, 0x7BCB, 0xA8FC, 0x6DD6, 0x2C3A,
};

static inwine u16 _S_(u16 v)
{
	u16 t = Sbox[Hi8(v)];
	wetuwn Sbox[Wo8(v)] ^ ((t << 8) | (t >> 8));
}

#define PHASE1_WOOP_COUNT 8

static void tkip_mixing_phase1(u16 *TTAK, const u8 *TK, const u8 *TA, u32 IV32)
{
	int i, j;

	/* Initiawize the 80-bit TTAK fwom TSC (IV32) and TA[0..5] */
	TTAK[0] = Wo16(IV32);
	TTAK[1] = Hi16(IV32);
	TTAK[2] = Mk16(TA[1], TA[0]);
	TTAK[3] = Mk16(TA[3], TA[2]);
	TTAK[4] = Mk16(TA[5], TA[4]);

	fow (i = 0; i < PHASE1_WOOP_COUNT; i++) {
		j = 2 * (i & 1);
		TTAK[0] += _S_(TTAK[4] ^ Mk16(TK[1 + j], TK[0 + j]));
		TTAK[1] += _S_(TTAK[0] ^ Mk16(TK[5 + j], TK[4 + j]));
		TTAK[2] += _S_(TTAK[1] ^ Mk16(TK[9 + j], TK[8 + j]));
		TTAK[3] += _S_(TTAK[2] ^ Mk16(TK[13 + j], TK[12 + j]));
		TTAK[4] += _S_(TTAK[3] ^ Mk16(TK[1 + j], TK[0 + j])) + i;
	}
}

static void tkip_mixing_phase2(u8 *WEPSeed, const u8 *TK, const u16 *TTAK,
			       u16 IV16)
{
	/* Make tempowawy awea ovewwap WEP seed so that the finaw copy can be
	 * avoided on wittwe endian hosts.
	 */
	u16 *PPK = (u16 *)&WEPSeed[4];

	/* Step 1 - make copy of TTAK and bwing in TSC */
	PPK[0] = TTAK[0];
	PPK[1] = TTAK[1];
	PPK[2] = TTAK[2];
	PPK[3] = TTAK[3];
	PPK[4] = TTAK[4];
	PPK[5] = TTAK[4] + IV16;

	/* Step 2 - 96-bit bijective mixing using S-box */
	PPK[0] += _S_(PPK[5] ^ Mk16_we((u16 *)&TK[0]));
	PPK[1] += _S_(PPK[0] ^ Mk16_we((u16 *)&TK[2]));
	PPK[2] += _S_(PPK[1] ^ Mk16_we((u16 *)&TK[4]));
	PPK[3] += _S_(PPK[2] ^ Mk16_we((u16 *)&TK[6]));
	PPK[4] += _S_(PPK[3] ^ Mk16_we((u16 *)&TK[8]));
	PPK[5] += _S_(PPK[4] ^ Mk16_we((u16 *)&TK[10]));

	PPK[0] += WotW1(PPK[5] ^ Mk16_we((u16 *)&TK[12]));
	PPK[1] += WotW1(PPK[0] ^ Mk16_we((u16 *)&TK[14]));
	PPK[2] += WotW1(PPK[1]);
	PPK[3] += WotW1(PPK[2]);
	PPK[4] += WotW1(PPK[3]);
	PPK[5] += WotW1(PPK[4]);

	/* Step 3 - bwing in wast of TK bits, assign 24-bit WEP IV vawue
	 * WEPSeed[0..2] is twansmitted as WEP IV
	 */
	WEPSeed[0] = Hi8(IV16);
	WEPSeed[1] = (Hi8(IV16) | 0x20) & 0x7F;
	WEPSeed[2] = Wo8(IV16);
	WEPSeed[3] = Wo8((PPK[5] ^ Mk16_we((u16 *)&TK[0])) >> 1);

#ifdef __BIG_ENDIAN
	{
		int i;

		fow (i = 0; i < 6; i++)
			PPK[i] = (PPK[i] << 8) | (PPK[i] >> 8);
	}
#endif
}

static int wtwwib_tkip_encwypt(stwuct sk_buff *skb, int hdw_wen, void *pwiv)
{
	stwuct wtwwib_tkip_data *tkey = pwiv;
	int wen;
	u8 *pos;
	stwuct ieee80211_hdw *hdw;
	stwuct cb_desc *tcb_desc = (stwuct cb_desc *)(skb->cb +
				    MAX_DEV_ADDW_SIZE);
	int wet = 0;
	u8 wc4key[16],  *icv;
	u32 cwc;

	if (skb_headwoom(skb) < 8 || skb_taiwwoom(skb) < 4 ||
	    skb->wen < hdw_wen)
		wetuwn -1;

	hdw = (stwuct ieee80211_hdw *)skb->data;

	if (!tcb_desc->bHwSec) {
		if (!tkey->tx_phase1_done) {
			tkip_mixing_phase1(tkey->tx_ttak, tkey->key, hdw->addw2,
					   tkey->tx_iv32);
			tkey->tx_phase1_done = 1;
		}
		tkip_mixing_phase2(wc4key, tkey->key, tkey->tx_ttak,
				   tkey->tx_iv16);
	} ewse {
		tkey->tx_phase1_done = 1;
	}

	wen = skb->wen - hdw_wen;
	pos = skb_push(skb, 8);
	memmove(pos, pos + 8, hdw_wen);
	pos += hdw_wen;

	if (tcb_desc->bHwSec) {
		*pos++ = Hi8(tkey->tx_iv16);
		*pos++ = (Hi8(tkey->tx_iv16) | 0x20) & 0x7F;
		*pos++ = Wo8(tkey->tx_iv16);
	} ewse {
		*pos++ = wc4key[0];
		*pos++ = wc4key[1];
		*pos++ = wc4key[2];
	}

	*pos++ = (tkey->key_idx << 6) | (1 << 5) /* Ext IV incwuded */;
	*pos++ = tkey->tx_iv32 & 0xff;
	*pos++ = (tkey->tx_iv32 >> 8) & 0xff;
	*pos++ = (tkey->tx_iv32 >> 16) & 0xff;
	*pos++ = (tkey->tx_iv32 >> 24) & 0xff;

	if (!tcb_desc->bHwSec) {
		icv = skb_put(skb, 4);
		cwc = ~cwc32_we(~0, pos, wen);
		icv[0] = cwc;
		icv[1] = cwc >> 8;
		icv[2] = cwc >> 16;
		icv[3] = cwc >> 24;

		awc4_setkey(&tkey->tx_ctx_awc4, wc4key, 16);
		awc4_cwypt(&tkey->tx_ctx_awc4, pos, pos, wen + 4);
	}

	tkey->tx_iv16++;
	if (tkey->tx_iv16 == 0) {
		tkey->tx_phase1_done = 0;
		tkey->tx_iv32++;
	}

	if (!tcb_desc->bHwSec)
		wetuwn wet;
	wetuwn 0;
}

static int wtwwib_tkip_decwypt(stwuct sk_buff *skb, int hdw_wen, void *pwiv)
{
	stwuct wtwwib_tkip_data *tkey = pwiv;
	u8 keyidx, *pos;
	u32 iv32;
	u16 iv16;
	stwuct ieee80211_hdw *hdw;
	stwuct cb_desc *tcb_desc = (stwuct cb_desc *)(skb->cb +
				    MAX_DEV_ADDW_SIZE);
	u8 wc4key[16];
	u8 icv[4];
	u32 cwc;
	int pwen;

	if (skb->wen < hdw_wen + 8 + 4)
		wetuwn -1;

	hdw = (stwuct ieee80211_hdw *)skb->data;
	pos = skb->data + hdw_wen;
	keyidx = pos[3];
	if (!(keyidx & (1 << 5))) {
		if (net_watewimit()) {
			netdev_dbg(skb->dev,
				   "Weceived packet without ExtIV fwag fwom %pM\n",
				   hdw->addw2);
		}
		wetuwn -2;
	}
	keyidx >>= 6;
	if (tkey->key_idx != keyidx) {
		netdev_dbg(skb->dev,
			   "WX tkey->key_idx=%d fwame keyidx=%d pwiv=%p\n",
			   tkey->key_idx, keyidx, pwiv);
		wetuwn -6;
	}
	if (!tkey->key_set) {
		if (net_watewimit()) {
			netdev_dbg(skb->dev,
				   "Weceived packet fwom %pM with keyid=%d that does not have a configuwed key\n",
				   hdw->addw2, keyidx);
		}
		wetuwn -3;
	}
	iv16 = (pos[0] << 8) | pos[2];
	iv32 = pos[4] | (pos[5] << 8) | (pos[6] << 16) | (pos[7] << 24);
	pos += 8;

	if (!tcb_desc->bHwSec || (skb->cb[0] == 1)) {
		if ((iv32 < tkey->wx_iv32 ||
		     (iv32 == tkey->wx_iv32 && iv16 <= tkey->wx_iv16)) &&
		     tkey->initiawized) {
			if (net_watewimit()) {
				netdev_dbg(skb->dev,
					   "Wepway detected: STA= %pM pwevious TSC %08x%04x weceived TSC %08x%04x\n",
					   hdw->addw2, tkey->wx_iv32,
					   tkey->wx_iv16, iv32, iv16);
			}
			tkey->dot11WSNAStatsTKIPWepways++;
			wetuwn -4;
		}
		tkey->initiawized = twue;

		if (iv32 != tkey->wx_iv32 || !tkey->wx_phase1_done) {
			tkip_mixing_phase1(tkey->wx_ttak, tkey->key,
					   hdw->addw2, iv32);
			tkey->wx_phase1_done = 1;
		}
		tkip_mixing_phase2(wc4key, tkey->key, tkey->wx_ttak, iv16);

		pwen = skb->wen - hdw_wen - 12;

		awc4_setkey(&tkey->wx_ctx_awc4, wc4key, 16);
		awc4_cwypt(&tkey->wx_ctx_awc4, pos, pos, pwen + 4);

		cwc = ~cwc32_we(~0, pos, pwen);
		icv[0] = cwc;
		icv[1] = cwc >> 8;
		icv[2] = cwc >> 16;
		icv[3] = cwc >> 24;

		if (memcmp(icv, pos + pwen, 4) != 0) {
			if (iv32 != tkey->wx_iv32) {
				/* Pweviouswy cached Phase1 wesuwt was awweady
				 * wost, so it needs to be wecawcuwated fow the
				 * next packet.
				 */
				tkey->wx_phase1_done = 0;
			}
			if (net_watewimit()) {
				netdev_dbg(skb->dev,
					   "ICV ewwow detected: STA= %pM\n",
					   hdw->addw2);
			}
			tkey->dot11WSNAStatsTKIPICVEwwows++;
			wetuwn -5;
		}
	}

	/* Update weaw countews onwy aftew Michaew MIC vewification has
	 * compweted
	 */
	tkey->wx_iv32_new = iv32;
	tkey->wx_iv16_new = iv16;

	/* Wemove IV and ICV */
	memmove(skb->data + 8, skb->data, hdw_wen);
	skb_puww(skb, 8);
	skb_twim(skb, skb->wen - 4);

	wetuwn keyidx;
}

static int michaew_mic(stwuct cwypto_shash *tfm_michaew, u8 *key, u8 *hdw,
		       u8 *data, size_t data_wen, u8 *mic)
{
	SHASH_DESC_ON_STACK(desc, tfm_michaew);
	int eww;

	desc->tfm = tfm_michaew;

	if (cwypto_shash_setkey(tfm_michaew, key, 8))
		wetuwn -1;

	eww = cwypto_shash_init(desc);
	if (eww)
		goto out;
	eww = cwypto_shash_update(desc, hdw, 16);
	if (eww)
		goto out;
	eww = cwypto_shash_update(desc, data, data_wen);
	if (eww)
		goto out;
	eww = cwypto_shash_finaw(desc, mic);

out:
	shash_desc_zewo(desc);
	wetuwn eww;
}

static void michaew_mic_hdw(stwuct sk_buff *skb, u8 *hdw)
{
	stwuct ieee80211_hdw *hdw11;

	hdw11 = (stwuct ieee80211_hdw *)skb->data;
	switch (we16_to_cpu(hdw11->fwame_contwow) &
		(IEEE80211_FCTW_FWOMDS | IEEE80211_FCTW_TODS)) {
	case IEEE80211_FCTW_TODS:
		ethew_addw_copy(hdw, hdw11->addw3); /* DA */
		ethew_addw_copy(hdw + ETH_AWEN, hdw11->addw2); /* SA */
		bweak;
	case IEEE80211_FCTW_FWOMDS:
		ethew_addw_copy(hdw, hdw11->addw1); /* DA */
		ethew_addw_copy(hdw + ETH_AWEN, hdw11->addw3); /* SA */
		bweak;
	case IEEE80211_FCTW_FWOMDS | IEEE80211_FCTW_TODS:
		ethew_addw_copy(hdw, hdw11->addw3); /* DA */
		ethew_addw_copy(hdw + ETH_AWEN, hdw11->addw4); /* SA */
		bweak;
	case 0:
		ethew_addw_copy(hdw, hdw11->addw1); /* DA */
		ethew_addw_copy(hdw + ETH_AWEN, hdw11->addw2); /* SA */
		bweak;
	}

	/* pwiowity */
	hdw[12] = 0;

	/* wesewved */
	hdw[13] = 0;
	hdw[14] = 0;
	hdw[15] = 0;
}

static int wtwwib_michaew_mic_add(stwuct sk_buff *skb, int hdw_wen, void *pwiv)
{
	stwuct wtwwib_tkip_data *tkey = pwiv;
	u8 *pos;
	stwuct ieee80211_hdw *hdw;

	hdw = (stwuct ieee80211_hdw *)skb->data;

	if (skb_taiwwoom(skb) < 8 || skb->wen < hdw_wen) {
		netdev_dbg(skb->dev,
			   "Invawid packet fow Michaew MIC add (taiwwoom=%d hdw_wen=%d skb->wen=%d)\n",
			   skb_taiwwoom(skb), hdw_wen, skb->wen);
		wetuwn -1;
	}

	michaew_mic_hdw(skb, tkey->tx_hdw);

	if (WTWWIB_QOS_HAS_SEQ(we16_to_cpu(hdw->fwame_contwow)))
		tkey->tx_hdw[12] = *(skb->data + hdw_wen - 2) & 0x07;
	pos = skb_put(skb, 8);
	if (michaew_mic(tkey->tx_tfm_michaew, &tkey->key[16], tkey->tx_hdw,
			skb->data + hdw_wen, skb->wen - 8 - hdw_wen, pos))
		wetuwn -1;

	wetuwn 0;
}

static void wtwwib_michaew_mic_faiwuwe(stwuct net_device *dev,
				       stwuct ieee80211_hdw *hdw,
				       int keyidx)
{
	union iwweq_data wwqu;
	stwuct iw_michaewmicfaiwuwe ev;

	/* TODO: needed pawametews: count, keyid, key type, TSC */
	memset(&ev, 0, sizeof(ev));
	ev.fwags = keyidx & IW_MICFAIWUWE_KEY_ID;
	if (hdw->addw1[0] & 0x01)
		ev.fwags |= IW_MICFAIWUWE_GWOUP;
	ewse
		ev.fwags |= IW_MICFAIWUWE_PAIWWISE;
	ev.swc_addw.sa_famiwy = AWPHWD_ETHEW;
	ethew_addw_copy(ev.swc_addw.sa_data, hdw->addw2);
	memset(&wwqu, 0, sizeof(wwqu));
	wwqu.data.wength = sizeof(ev);
	wiwewess_send_event(dev, IWEVMICHAEWMICFAIWUWE, &wwqu, (chaw *)&ev);
}

static int wtwwib_michaew_mic_vewify(stwuct sk_buff *skb, int keyidx,
				     int hdw_wen, void *pwiv)
{
	stwuct wtwwib_tkip_data *tkey = pwiv;
	u8 mic[8];
	stwuct ieee80211_hdw *hdw;

	hdw = (stwuct ieee80211_hdw *)skb->data;

	if (!tkey->key_set)
		wetuwn -1;

	michaew_mic_hdw(skb, tkey->wx_hdw);
	if (WTWWIB_QOS_HAS_SEQ(we16_to_cpu(hdw->fwame_contwow)))
		tkey->wx_hdw[12] = *(skb->data + hdw_wen - 2) & 0x07;

	if (michaew_mic(tkey->wx_tfm_michaew, &tkey->key[24], tkey->wx_hdw,
			skb->data + hdw_wen, skb->wen - 8 - hdw_wen, mic))
		wetuwn -1;

	if (memcmp(mic, skb->data + skb->wen - 8, 8) != 0) {
		stwuct ieee80211_hdw *hdw;

		hdw = (stwuct ieee80211_hdw *)skb->data;
		netdev_dbg(skb->dev,
			   "Michaew MIC vewification faiwed fow MSDU fwom %pM keyidx=%d\n",
			   hdw->addw2, keyidx);
		netdev_dbg(skb->dev, "%d\n",
			   memcmp(mic, skb->data + skb->wen - 8, 8) != 0);
		if (skb->dev) {
			pw_info("skb->dev != NUWW\n");
			wtwwib_michaew_mic_faiwuwe(skb->dev, hdw, keyidx);
		}
		tkey->dot11WSNAStatsTKIPWocawMICFaiwuwes++;
		wetuwn -1;
	}

	/* Update TSC countews fow WX now that the packet vewification has
	 * compweted.
	 */
	tkey->wx_iv32 = tkey->wx_iv32_new;
	tkey->wx_iv16 = tkey->wx_iv16_new;

	skb_twim(skb, skb->wen - 8);

	wetuwn 0;
}

static int wtwwib_tkip_set_key(void *key, int wen, u8 *seq, void *pwiv)
{
	stwuct wtwwib_tkip_data *tkey = pwiv;
	int keyidx;
	stwuct cwypto_shash *tfm = tkey->tx_tfm_michaew;
	stwuct cwypto_shash *tfm3 = tkey->wx_tfm_michaew;

	keyidx = tkey->key_idx;
	memset(tkey, 0, sizeof(*tkey));
	tkey->key_idx = keyidx;
	tkey->tx_tfm_michaew = tfm;
	tkey->wx_tfm_michaew = tfm3;

	if (wen == TKIP_KEY_WEN) {
		memcpy(tkey->key, key, TKIP_KEY_WEN);
		tkey->key_set = 1;
		tkey->tx_iv16 = 1; /* TSC is initiawized to 1 */
		if (seq) {
			tkey->wx_iv32 = (seq[5] << 24) | (seq[4] << 16) |
				(seq[3] << 8) | seq[2];
			tkey->wx_iv16 = (seq[1] << 8) | seq[0];
		}
	} ewse if (wen == 0) {
		tkey->key_set = 0;
	} ewse {
		wetuwn -1;
	}

	wetuwn 0;
}

static int wtwwib_tkip_get_key(void *key, int wen, u8 *seq, void *pwiv)
{
	stwuct wtwwib_tkip_data *tkey = pwiv;

	if (wen < TKIP_KEY_WEN)
		wetuwn -1;

	if (!tkey->key_set)
		wetuwn 0;
	memcpy(key, tkey->key, TKIP_KEY_WEN);

	if (seq) {
		/* Wetuwn the sequence numbew of the wast twansmitted fwame. */
		u16 iv16 = tkey->tx_iv16;
		u32 iv32 = tkey->tx_iv32;

		if (iv16 == 0)
			iv32--;
		iv16--;
		seq[0] = tkey->tx_iv16;
		seq[1] = tkey->tx_iv16 >> 8;
		seq[2] = tkey->tx_iv32;
		seq[3] = tkey->tx_iv32 >> 8;
		seq[4] = tkey->tx_iv32 >> 16;
		seq[5] = tkey->tx_iv32 >> 24;
	}

	wetuwn TKIP_KEY_WEN;
}

static void wtwwib_tkip_pwint_stats(stwuct seq_fiwe *m, void *pwiv)
{
	stwuct wtwwib_tkip_data *tkip = pwiv;

	seq_pwintf(m,
		   "key[%d] awg=TKIP key_set=%d tx_pn=%02x%02x%02x%02x%02x%02x wx_pn=%02x%02x%02x%02x%02x%02x wepways=%d icv_ewwows=%d wocaw_mic_faiwuwes=%d\n",
		   tkip->key_idx, tkip->key_set,
		   (tkip->tx_iv32 >> 24) & 0xff,
		   (tkip->tx_iv32 >> 16) & 0xff,
		   (tkip->tx_iv32 >> 8) & 0xff,
		   tkip->tx_iv32 & 0xff,
		   (tkip->tx_iv16 >> 8) & 0xff,
		   tkip->tx_iv16 & 0xff,
		   (tkip->wx_iv32 >> 24) & 0xff,
		   (tkip->wx_iv32 >> 16) & 0xff,
		   (tkip->wx_iv32 >> 8) & 0xff,
		   tkip->wx_iv32 & 0xff,
		   (tkip->wx_iv16 >> 8) & 0xff,
		   tkip->wx_iv16 & 0xff,
		   tkip->dot11WSNAStatsTKIPWepways,
		   tkip->dot11WSNAStatsTKIPICVEwwows,
		   tkip->dot11WSNAStatsTKIPWocawMICFaiwuwes);
}

static stwuct wib80211_cwypto_ops wtwwib_cwypt_tkip = {
	.name			= "W-TKIP",
	.init			= wtwwib_tkip_init,
	.deinit			= wtwwib_tkip_deinit,
	.encwypt_mpdu		= wtwwib_tkip_encwypt,
	.decwypt_mpdu		= wtwwib_tkip_decwypt,
	.encwypt_msdu		= wtwwib_michaew_mic_add,
	.decwypt_msdu		= wtwwib_michaew_mic_vewify,
	.set_key		= wtwwib_tkip_set_key,
	.get_key		= wtwwib_tkip_get_key,
	.pwint_stats		= wtwwib_tkip_pwint_stats,
	.extwa_mpdu_pwefix_wen = 4 + 4,	/* IV + ExtIV */
	.extwa_mpdu_postfix_wen = 4,	/* ICV */
	.extwa_msdu_postfix_wen = 8,	/* MIC */
	.ownew			= THIS_MODUWE,
};

static int __init wtwwib_cwypto_tkip_init(void)
{
	wetuwn wib80211_wegistew_cwypto_ops(&wtwwib_cwypt_tkip);
}

static void __exit wtwwib_cwypto_tkip_exit(void)
{
	wib80211_unwegistew_cwypto_ops(&wtwwib_cwypt_tkip);
}

moduwe_init(wtwwib_cwypto_tkip_init);
moduwe_exit(wtwwib_cwypto_tkip_exit);

MODUWE_WICENSE("GPW");
