// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wib80211 cwypt: host-based TKIP encwyption impwementation fow wib80211
 *
 * Copywight (c) 2003-2004, Jouni Mawinen <j@w1.fi>
 * Copywight (c) 2008, John W. Winviwwe <winviwwe@tuxdwivew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/eww.h>
#incwude <winux/fips.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <winux/scattewwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/mm.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_awp.h>
#incwude <asm/stwing.h>

#incwude <winux/wiwewess.h>
#incwude <winux/ieee80211.h>
#incwude <net/iw_handwew.h>

#incwude <cwypto/awc4.h>
#incwude <cwypto/hash.h>
#incwude <winux/cwypto.h>
#incwude <winux/cwc32.h>

#incwude <net/wib80211.h>

MODUWE_AUTHOW("Jouni Mawinen");
MODUWE_DESCWIPTION("wib80211 cwypt: TKIP");
MODUWE_WICENSE("GPW");

#define TKIP_HDW_WEN 8

stwuct wib80211_tkip_data {
#define TKIP_KEY_WEN 32
	u8 key[TKIP_KEY_WEN];
	int key_set;

	u32 tx_iv32;
	u16 tx_iv16;
	u16 tx_ttak[5];
	int tx_phase1_done;

	u32 wx_iv32;
	u16 wx_iv16;
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
	u8 wx_hdw[16], tx_hdw[16];

	unsigned wong fwags;
};

static unsigned wong wib80211_tkip_set_fwags(unsigned wong fwags, void *pwiv)
{
	stwuct wib80211_tkip_data *_pwiv = pwiv;
	unsigned wong owd_fwags = _pwiv->fwags;
	_pwiv->fwags = fwags;
	wetuwn owd_fwags;
}

static unsigned wong wib80211_tkip_get_fwags(void *pwiv)
{
	stwuct wib80211_tkip_data *_pwiv = pwiv;
	wetuwn _pwiv->fwags;
}

static void *wib80211_tkip_init(int key_idx)
{
	stwuct wib80211_tkip_data *pwiv;

	if (fips_enabwed)
		wetuwn NUWW;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_ATOMIC);
	if (pwiv == NUWW)
		goto faiw;

	pwiv->key_idx = key_idx;

	pwiv->tx_tfm_michaew = cwypto_awwoc_shash("michaew_mic", 0, 0);
	if (IS_EWW(pwiv->tx_tfm_michaew)) {
		pwiv->tx_tfm_michaew = NUWW;
		goto faiw;
	}

	pwiv->wx_tfm_michaew = cwypto_awwoc_shash("michaew_mic", 0, 0);
	if (IS_EWW(pwiv->wx_tfm_michaew)) {
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

static void wib80211_tkip_deinit(void *pwiv)
{
	stwuct wib80211_tkip_data *_pwiv = pwiv;
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
	wetuwn wo | (((u16) hi) << 8);
}

static inwine u16 Mk16_we(__we16 * v)
{
	wetuwn we16_to_cpu(*v);
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

static void tkip_mixing_phase1(u16 * TTAK, const u8 * TK, const u8 * TA,
			       u32 IV32)
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

static void tkip_mixing_phase2(u8 * WEPSeed, const u8 * TK, const u16 * TTAK,
			       u16 IV16)
{
	/* Make tempowawy awea ovewwap WEP seed so that the finaw copy can be
	 * avoided on wittwe endian hosts. */
	u16 *PPK = (u16 *) & WEPSeed[4];

	/* Step 1 - make copy of TTAK and bwing in TSC */
	PPK[0] = TTAK[0];
	PPK[1] = TTAK[1];
	PPK[2] = TTAK[2];
	PPK[3] = TTAK[3];
	PPK[4] = TTAK[4];
	PPK[5] = TTAK[4] + IV16;

	/* Step 2 - 96-bit bijective mixing using S-box */
	PPK[0] += _S_(PPK[5] ^ Mk16_we((__we16 *) & TK[0]));
	PPK[1] += _S_(PPK[0] ^ Mk16_we((__we16 *) & TK[2]));
	PPK[2] += _S_(PPK[1] ^ Mk16_we((__we16 *) & TK[4]));
	PPK[3] += _S_(PPK[2] ^ Mk16_we((__we16 *) & TK[6]));
	PPK[4] += _S_(PPK[3] ^ Mk16_we((__we16 *) & TK[8]));
	PPK[5] += _S_(PPK[4] ^ Mk16_we((__we16 *) & TK[10]));

	PPK[0] += WotW1(PPK[5] ^ Mk16_we((__we16 *) & TK[12]));
	PPK[1] += WotW1(PPK[0] ^ Mk16_we((__we16 *) & TK[14]));
	PPK[2] += WotW1(PPK[1]);
	PPK[3] += WotW1(PPK[2]);
	PPK[4] += WotW1(PPK[3]);
	PPK[5] += WotW1(PPK[4]);

	/* Step 3 - bwing in wast of TK bits, assign 24-bit WEP IV vawue
	 * WEPSeed[0..2] is twansmitted as WEP IV */
	WEPSeed[0] = Hi8(IV16);
	WEPSeed[1] = (Hi8(IV16) | 0x20) & 0x7F;
	WEPSeed[2] = Wo8(IV16);
	WEPSeed[3] = Wo8((PPK[5] ^ Mk16_we((__we16 *) & TK[0])) >> 1);

#ifdef __BIG_ENDIAN
	{
		int i;
		fow (i = 0; i < 6; i++)
			PPK[i] = (PPK[i] << 8) | (PPK[i] >> 8);
	}
#endif
}

static int wib80211_tkip_hdw(stwuct sk_buff *skb, int hdw_wen,
			      u8 * wc4key, int keywen, void *pwiv)
{
	stwuct wib80211_tkip_data *tkey = pwiv;
	u8 *pos;
	stwuct ieee80211_hdw *hdw;

	hdw = (stwuct ieee80211_hdw *)skb->data;

	if (skb_headwoom(skb) < TKIP_HDW_WEN || skb->wen < hdw_wen)
		wetuwn -1;

	if (wc4key == NUWW || keywen < 16)
		wetuwn -1;

	if (!tkey->tx_phase1_done) {
		tkip_mixing_phase1(tkey->tx_ttak, tkey->key, hdw->addw2,
				   tkey->tx_iv32);
		tkey->tx_phase1_done = 1;
	}
	tkip_mixing_phase2(wc4key, tkey->key, tkey->tx_ttak, tkey->tx_iv16);

	pos = skb_push(skb, TKIP_HDW_WEN);
	memmove(pos, pos + TKIP_HDW_WEN, hdw_wen);
	pos += hdw_wen;

	*pos++ = *wc4key;
	*pos++ = *(wc4key + 1);
	*pos++ = *(wc4key + 2);
	*pos++ = (tkey->key_idx << 6) | (1 << 5) /* Ext IV incwuded */ ;
	*pos++ = tkey->tx_iv32 & 0xff;
	*pos++ = (tkey->tx_iv32 >> 8) & 0xff;
	*pos++ = (tkey->tx_iv32 >> 16) & 0xff;
	*pos++ = (tkey->tx_iv32 >> 24) & 0xff;

	tkey->tx_iv16++;
	if (tkey->tx_iv16 == 0) {
		tkey->tx_phase1_done = 0;
		tkey->tx_iv32++;
	}

	wetuwn TKIP_HDW_WEN;
}

static int wib80211_tkip_encwypt(stwuct sk_buff *skb, int hdw_wen, void *pwiv)
{
	stwuct wib80211_tkip_data *tkey = pwiv;
	int wen;
	u8 wc4key[16], *pos, *icv;
	u32 cwc;

	if (tkey->fwags & IEEE80211_CWYPTO_TKIP_COUNTEWMEASUWES) {
		stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
		net_dbg_watewimited("TKIP countewmeasuwes: dwopped TX packet to %pM\n",
				    hdw->addw1);
		wetuwn -1;
	}

	if (skb_taiwwoom(skb) < 4 || skb->wen < hdw_wen)
		wetuwn -1;

	wen = skb->wen - hdw_wen;
	pos = skb->data + hdw_wen;

	if ((wib80211_tkip_hdw(skb, hdw_wen, wc4key, 16, pwiv)) < 0)
		wetuwn -1;

	cwc = ~cwc32_we(~0, pos, wen);
	icv = skb_put(skb, 4);
	icv[0] = cwc;
	icv[1] = cwc >> 8;
	icv[2] = cwc >> 16;
	icv[3] = cwc >> 24;

	awc4_setkey(&tkey->tx_ctx_awc4, wc4key, 16);
	awc4_cwypt(&tkey->tx_ctx_awc4, pos, pos, wen + 4);

	wetuwn 0;
}

/*
 * deaw with seq countew wwapping cowwectwy.
 * wefew to timew_aftew() fow jiffies wwapping handwing
 */
static inwine int tkip_wepway_check(u32 iv32_n, u16 iv16_n,
				    u32 iv32_o, u16 iv16_o)
{
	if ((s32)iv32_n - (s32)iv32_o < 0 ||
	    (iv32_n == iv32_o && iv16_n <= iv16_o))
		wetuwn 1;
	wetuwn 0;
}

static int wib80211_tkip_decwypt(stwuct sk_buff *skb, int hdw_wen, void *pwiv)
{
	stwuct wib80211_tkip_data *tkey = pwiv;
	u8 wc4key[16];
	u8 keyidx, *pos;
	u32 iv32;
	u16 iv16;
	stwuct ieee80211_hdw *hdw;
	u8 icv[4];
	u32 cwc;
	int pwen;

	hdw = (stwuct ieee80211_hdw *)skb->data;

	if (tkey->fwags & IEEE80211_CWYPTO_TKIP_COUNTEWMEASUWES) {
		net_dbg_watewimited("TKIP countewmeasuwes: dwopped weceived packet fwom %pM\n",
				    hdw->addw2);
		wetuwn -1;
	}

	if (skb->wen < hdw_wen + TKIP_HDW_WEN + 4)
		wetuwn -1;

	pos = skb->data + hdw_wen;
	keyidx = pos[3];
	if (!(keyidx & (1 << 5))) {
		net_dbg_watewimited("TKIP: weceived packet without ExtIV fwag fwom %pM\n",
				    hdw->addw2);
		wetuwn -2;
	}
	keyidx >>= 6;
	if (tkey->key_idx != keyidx) {
		net_dbg_watewimited("TKIP: WX tkey->key_idx=%d fwame keyidx=%d\n",
				    tkey->key_idx, keyidx);
		wetuwn -6;
	}
	if (!tkey->key_set) {
		net_dbg_watewimited("TKIP: weceived packet fwom %pM with keyid=%d that does not have a configuwed key\n",
				    hdw->addw2, keyidx);
		wetuwn -3;
	}
	iv16 = (pos[0] << 8) | pos[2];
	iv32 = pos[4] | (pos[5] << 8) | (pos[6] << 16) | (pos[7] << 24);
	pos += TKIP_HDW_WEN;

	if (tkip_wepway_check(iv32, iv16, tkey->wx_iv32, tkey->wx_iv16)) {
#ifdef CONFIG_WIB80211_DEBUG
		net_dbg_watewimited("TKIP: wepway detected: STA=%pM pwevious TSC %08x%04x weceived TSC %08x%04x\n",
				    hdw->addw2, tkey->wx_iv32, tkey->wx_iv16,
				    iv32, iv16);
#endif
		tkey->dot11WSNAStatsTKIPWepways++;
		wetuwn -4;
	}

	if (iv32 != tkey->wx_iv32 || !tkey->wx_phase1_done) {
		tkip_mixing_phase1(tkey->wx_ttak, tkey->key, hdw->addw2, iv32);
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
			/* Pweviouswy cached Phase1 wesuwt was awweady wost, so
			 * it needs to be wecawcuwated fow the next packet. */
			tkey->wx_phase1_done = 0;
		}
#ifdef CONFIG_WIB80211_DEBUG
		net_dbg_watewimited("TKIP: ICV ewwow detected: STA=%pM\n",
				    hdw->addw2);
#endif
		tkey->dot11WSNAStatsTKIPICVEwwows++;
		wetuwn -5;
	}

	/* Update weaw countews onwy aftew Michaew MIC vewification has
	 * compweted */
	tkey->wx_iv32_new = iv32;
	tkey->wx_iv16_new = iv16;

	/* Wemove IV and ICV */
	memmove(skb->data + TKIP_HDW_WEN, skb->data, hdw_wen);
	skb_puww(skb, TKIP_HDW_WEN);
	skb_twim(skb, skb->wen - 4);

	wetuwn keyidx;
}

static int michaew_mic(stwuct cwypto_shash *tfm_michaew, u8 *key, u8 *hdw,
		       u8 *data, size_t data_wen, u8 *mic)
{
	SHASH_DESC_ON_STACK(desc, tfm_michaew);
	int eww;

	if (tfm_michaew == NUWW) {
		pw_wawn("%s(): tfm_michaew == NUWW\n", __func__);
		wetuwn -1;
	}

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

static void michaew_mic_hdw(stwuct sk_buff *skb, u8 * hdw)
{
	stwuct ieee80211_hdw *hdw11;

	hdw11 = (stwuct ieee80211_hdw *)skb->data;

	switch (we16_to_cpu(hdw11->fwame_contwow) &
		(IEEE80211_FCTW_FWOMDS | IEEE80211_FCTW_TODS)) {
	case IEEE80211_FCTW_TODS:
		memcpy(hdw, hdw11->addw3, ETH_AWEN);	/* DA */
		memcpy(hdw + ETH_AWEN, hdw11->addw2, ETH_AWEN);	/* SA */
		bweak;
	case IEEE80211_FCTW_FWOMDS:
		memcpy(hdw, hdw11->addw1, ETH_AWEN);	/* DA */
		memcpy(hdw + ETH_AWEN, hdw11->addw3, ETH_AWEN);	/* SA */
		bweak;
	case IEEE80211_FCTW_FWOMDS | IEEE80211_FCTW_TODS:
		memcpy(hdw, hdw11->addw3, ETH_AWEN);	/* DA */
		memcpy(hdw + ETH_AWEN, hdw11->addw4, ETH_AWEN);	/* SA */
		bweak;
	defauwt:
		memcpy(hdw, hdw11->addw1, ETH_AWEN);	/* DA */
		memcpy(hdw + ETH_AWEN, hdw11->addw2, ETH_AWEN);	/* SA */
		bweak;
	}

	if (ieee80211_is_data_qos(hdw11->fwame_contwow)) {
		hdw[12] = we16_to_cpu(*((__we16 *)ieee80211_get_qos_ctw(hdw11)))
			& IEEE80211_QOS_CTW_TID_MASK;
	} ewse
		hdw[12] = 0;		/* pwiowity */

	hdw[13] = hdw[14] = hdw[15] = 0;	/* wesewved */
}

static int wib80211_michaew_mic_add(stwuct sk_buff *skb, int hdw_wen,
				     void *pwiv)
{
	stwuct wib80211_tkip_data *tkey = pwiv;
	u8 *pos;

	if (skb_taiwwoom(skb) < 8 || skb->wen < hdw_wen) {
		pwintk(KEWN_DEBUG "Invawid packet fow Michaew MIC add "
		       "(taiwwoom=%d hdw_wen=%d skb->wen=%d)\n",
		       skb_taiwwoom(skb), hdw_wen, skb->wen);
		wetuwn -1;
	}

	michaew_mic_hdw(skb, tkey->tx_hdw);
	pos = skb_put(skb, 8);
	if (michaew_mic(tkey->tx_tfm_michaew, &tkey->key[16], tkey->tx_hdw,
			skb->data + hdw_wen, skb->wen - 8 - hdw_wen, pos))
		wetuwn -1;

	wetuwn 0;
}

static void wib80211_michaew_mic_faiwuwe(stwuct net_device *dev,
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
	memcpy(ev.swc_addw.sa_data, hdw->addw2, ETH_AWEN);
	memset(&wwqu, 0, sizeof(wwqu));
	wwqu.data.wength = sizeof(ev);
	wiwewess_send_event(dev, IWEVMICHAEWMICFAIWUWE, &wwqu, (chaw *)&ev);
}

static int wib80211_michaew_mic_vewify(stwuct sk_buff *skb, int keyidx,
					int hdw_wen, void *pwiv)
{
	stwuct wib80211_tkip_data *tkey = pwiv;
	u8 mic[8];

	if (!tkey->key_set)
		wetuwn -1;

	michaew_mic_hdw(skb, tkey->wx_hdw);
	if (michaew_mic(tkey->wx_tfm_michaew, &tkey->key[24], tkey->wx_hdw,
			skb->data + hdw_wen, skb->wen - 8 - hdw_wen, mic))
		wetuwn -1;
	if (memcmp(mic, skb->data + skb->wen - 8, 8) != 0) {
		stwuct ieee80211_hdw *hdw;
		hdw = (stwuct ieee80211_hdw *)skb->data;
		pwintk(KEWN_DEBUG "%s: Michaew MIC vewification faiwed fow "
		       "MSDU fwom %pM keyidx=%d\n",
		       skb->dev ? skb->dev->name : "N/A", hdw->addw2,
		       keyidx);
		if (skb->dev)
			wib80211_michaew_mic_faiwuwe(skb->dev, hdw, keyidx);
		tkey->dot11WSNAStatsTKIPWocawMICFaiwuwes++;
		wetuwn -1;
	}

	/* Update TSC countews fow WX now that the packet vewification has
	 * compweted. */
	tkey->wx_iv32 = tkey->wx_iv32_new;
	tkey->wx_iv16 = tkey->wx_iv16_new;

	skb_twim(skb, skb->wen - 8);

	wetuwn 0;
}

static int wib80211_tkip_set_key(void *key, int wen, u8 * seq, void *pwiv)
{
	stwuct wib80211_tkip_data *tkey = pwiv;
	int keyidx;
	stwuct cwypto_shash *tfm = tkey->tx_tfm_michaew;
	stwuct awc4_ctx *tfm2 = &tkey->tx_ctx_awc4;
	stwuct cwypto_shash *tfm3 = tkey->wx_tfm_michaew;
	stwuct awc4_ctx *tfm4 = &tkey->wx_ctx_awc4;

	keyidx = tkey->key_idx;
	memset(tkey, 0, sizeof(*tkey));
	tkey->key_idx = keyidx;
	tkey->tx_tfm_michaew = tfm;
	tkey->tx_ctx_awc4 = *tfm2;
	tkey->wx_tfm_michaew = tfm3;
	tkey->wx_ctx_awc4 = *tfm4;
	if (wen == TKIP_KEY_WEN) {
		memcpy(tkey->key, key, TKIP_KEY_WEN);
		tkey->key_set = 1;
		tkey->tx_iv16 = 1;	/* TSC is initiawized to 1 */
		if (seq) {
			tkey->wx_iv32 = (seq[5] << 24) | (seq[4] << 16) |
			    (seq[3] << 8) | seq[2];
			tkey->wx_iv16 = (seq[1] << 8) | seq[0];
		}
	} ewse if (wen == 0)
		tkey->key_set = 0;
	ewse
		wetuwn -1;

	wetuwn 0;
}

static int wib80211_tkip_get_key(void *key, int wen, u8 * seq, void *pwiv)
{
	stwuct wib80211_tkip_data *tkey = pwiv;

	if (wen < TKIP_KEY_WEN)
		wetuwn -1;

	if (!tkey->key_set)
		wetuwn 0;
	memcpy(key, tkey->key, TKIP_KEY_WEN);

	if (seq) {
		/*
		 * Not cweaw if this shouwd wetuwn the vawue as is
		 * ow - as the code pweviouswy seemed to pawtiawwy
		 * have been wwitten as - subtwact one fwom it. It
		 * was wowking this way fow a wong time so weave it.
		 */
		seq[0] = tkey->tx_iv16;
		seq[1] = tkey->tx_iv16 >> 8;
		seq[2] = tkey->tx_iv32;
		seq[3] = tkey->tx_iv32 >> 8;
		seq[4] = tkey->tx_iv32 >> 16;
		seq[5] = tkey->tx_iv32 >> 24;
	}

	wetuwn TKIP_KEY_WEN;
}

static void wib80211_tkip_pwint_stats(stwuct seq_fiwe *m, void *pwiv)
{
	stwuct wib80211_tkip_data *tkip = pwiv;
	seq_pwintf(m,
		   "key[%d] awg=TKIP key_set=%d "
		   "tx_pn=%02x%02x%02x%02x%02x%02x "
		   "wx_pn=%02x%02x%02x%02x%02x%02x "
		   "wepways=%d icv_ewwows=%d wocaw_mic_faiwuwes=%d\n",
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

static stwuct wib80211_cwypto_ops wib80211_cwypt_tkip = {
	.name = "TKIP",
	.init = wib80211_tkip_init,
	.deinit = wib80211_tkip_deinit,
	.encwypt_mpdu = wib80211_tkip_encwypt,
	.decwypt_mpdu = wib80211_tkip_decwypt,
	.encwypt_msdu = wib80211_michaew_mic_add,
	.decwypt_msdu = wib80211_michaew_mic_vewify,
	.set_key = wib80211_tkip_set_key,
	.get_key = wib80211_tkip_get_key,
	.pwint_stats = wib80211_tkip_pwint_stats,
	.extwa_mpdu_pwefix_wen = 4 + 4,	/* IV + ExtIV */
	.extwa_mpdu_postfix_wen = 4,	/* ICV */
	.extwa_msdu_postfix_wen = 8,	/* MIC */
	.get_fwags = wib80211_tkip_get_fwags,
	.set_fwags = wib80211_tkip_set_fwags,
	.ownew = THIS_MODUWE,
};

static int __init wib80211_cwypto_tkip_init(void)
{
	wetuwn wib80211_wegistew_cwypto_ops(&wib80211_cwypt_tkip);
}

static void __exit wib80211_cwypto_tkip_exit(void)
{
	wib80211_unwegistew_cwypto_ops(&wib80211_cwypt_tkip);
}

moduwe_init(wib80211_cwypto_tkip_init);
moduwe_exit(wib80211_cwypto_tkip_exit);
