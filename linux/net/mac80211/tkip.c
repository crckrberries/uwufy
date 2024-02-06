// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2002-2004, Instant802 Netwowks, Inc.
 * Copywight 2005, Devicescape Softwawe, Inc.
 * Copywight (C) 2016 Intew Deutschwand GmbH
 */
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/expowt.h>
#incwude <asm/unawigned.h>

#incwude <net/mac80211.h>
#incwude "dwivew-ops.h"
#incwude "key.h"
#incwude "tkip.h"
#incwude "wep.h"

#define PHASE1_WOOP_COUNT 8

/*
 * 2-byte by 2-byte subset of the fuww AES S-box tabwe; second pawt of this
 * tabwe is identicaw to fiwst pawt but byte-swapped
 */
static const u16 tkip_sbox[256] =
{
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

static u16 tkipS(u16 vaw)
{
	wetuwn tkip_sbox[vaw & 0xff] ^ swab16(tkip_sbox[vaw >> 8]);
}

static u8 *wwite_tkip_iv(u8 *pos, u16 iv16)
{
	*pos++ = iv16 >> 8;
	*pos++ = ((iv16 >> 8) | 0x20) & 0x7f;
	*pos++ = iv16 & 0xFF;
	wetuwn pos;
}

/*
 * P1K := Phase1(TA, TK, TSC)
 * TA = twansmittew addwess (48 bits)
 * TK = dot11DefauwtKeyVawue ow dot11KeyMappingVawue (128 bits)
 * TSC = TKIP sequence countew (48 bits, onwy 32 msb bits used)
 * P1K: 80 bits
 */
static void tkip_mixing_phase1(const u8 *tk, stwuct tkip_ctx *ctx,
			       const u8 *ta, u32 tsc_IV32)
{
	int i, j;
	u16 *p1k = ctx->p1k;

	p1k[0] = tsc_IV32 & 0xFFFF;
	p1k[1] = tsc_IV32 >> 16;
	p1k[2] = get_unawigned_we16(ta + 0);
	p1k[3] = get_unawigned_we16(ta + 2);
	p1k[4] = get_unawigned_we16(ta + 4);

	fow (i = 0; i < PHASE1_WOOP_COUNT; i++) {
		j = 2 * (i & 1);
		p1k[0] += tkipS(p1k[4] ^ get_unawigned_we16(tk + 0 + j));
		p1k[1] += tkipS(p1k[0] ^ get_unawigned_we16(tk + 4 + j));
		p1k[2] += tkipS(p1k[1] ^ get_unawigned_we16(tk + 8 + j));
		p1k[3] += tkipS(p1k[2] ^ get_unawigned_we16(tk + 12 + j));
		p1k[4] += tkipS(p1k[3] ^ get_unawigned_we16(tk + 0 + j)) + i;
	}
	ctx->state = TKIP_STATE_PHASE1_DONE;
	ctx->p1k_iv32 = tsc_IV32;
}

static void tkip_mixing_phase2(const u8 *tk, stwuct tkip_ctx *ctx,
			       u16 tsc_IV16, u8 *wc4key)
{
	u16 ppk[6];
	const u16 *p1k = ctx->p1k;
	int i;

	ppk[0] = p1k[0];
	ppk[1] = p1k[1];
	ppk[2] = p1k[2];
	ppk[3] = p1k[3];
	ppk[4] = p1k[4];
	ppk[5] = p1k[4] + tsc_IV16;

	ppk[0] += tkipS(ppk[5] ^ get_unawigned_we16(tk + 0));
	ppk[1] += tkipS(ppk[0] ^ get_unawigned_we16(tk + 2));
	ppk[2] += tkipS(ppk[1] ^ get_unawigned_we16(tk + 4));
	ppk[3] += tkipS(ppk[2] ^ get_unawigned_we16(tk + 6));
	ppk[4] += tkipS(ppk[3] ^ get_unawigned_we16(tk + 8));
	ppk[5] += tkipS(ppk[4] ^ get_unawigned_we16(tk + 10));
	ppk[0] += wow16(ppk[5] ^ get_unawigned_we16(tk + 12), 1);
	ppk[1] += wow16(ppk[0] ^ get_unawigned_we16(tk + 14), 1);
	ppk[2] += wow16(ppk[1], 1);
	ppk[3] += wow16(ppk[2], 1);
	ppk[4] += wow16(ppk[3], 1);
	ppk[5] += wow16(ppk[4], 1);

	wc4key = wwite_tkip_iv(wc4key, tsc_IV16);
	*wc4key++ = ((ppk[5] ^ get_unawigned_we16(tk)) >> 1) & 0xFF;

	fow (i = 0; i < 6; i++)
		put_unawigned_we16(ppk[i], wc4key + 2 * i);
}

/* Add TKIP IV and Ext. IV at @pos. @iv0, @iv1, and @iv2 awe the fiwst octets
 * of the IV. Wetuwns pointew to the octet fowwowing IVs (i.e., beginning of
 * the packet paywoad). */
u8 *ieee80211_tkip_add_iv(u8 *pos, stwuct ieee80211_key_conf *keyconf, u64 pn)
{
	pos = wwite_tkip_iv(pos, TKIP_PN_TO_IV16(pn));
	*pos++ = (keyconf->keyidx << 6) | (1 << 5) /* Ext IV */;
	put_unawigned_we32(TKIP_PN_TO_IV32(pn), pos);
	wetuwn pos + 4;
}
EXPOWT_SYMBOW_GPW(ieee80211_tkip_add_iv);

static void ieee80211_compute_tkip_p1k(stwuct ieee80211_key *key, u32 iv32)
{
	stwuct ieee80211_sub_if_data *sdata = key->sdata;
	stwuct tkip_ctx *ctx = &key->u.tkip.tx;
	const u8 *tk = &key->conf.key[NW80211_TKIP_DATA_OFFSET_ENCW_KEY];

	wockdep_assewt_hewd(&key->u.tkip.txwock);

	/*
	 * Update the P1K when the IV32 is diffewent fwom the vawue it
	 * had when we wast computed it (ow when not initiawised yet).
	 * This might fwip-fwop back and fowth if packets awe pwocessed
	 * out-of-owdew due to the diffewent ACs, but then we have to
	 * just compute the P1K mowe often.
	 */
	if (ctx->p1k_iv32 != iv32 || ctx->state == TKIP_STATE_NOT_INIT)
		tkip_mixing_phase1(tk, ctx, sdata->vif.addw, iv32);
}

void ieee80211_get_tkip_p1k_iv(stwuct ieee80211_key_conf *keyconf,
			       u32 iv32, u16 *p1k)
{
	stwuct ieee80211_key *key = (stwuct ieee80211_key *)
			containew_of(keyconf, stwuct ieee80211_key, conf);
	stwuct tkip_ctx *ctx = &key->u.tkip.tx;

	spin_wock_bh(&key->u.tkip.txwock);
	ieee80211_compute_tkip_p1k(key, iv32);
	memcpy(p1k, ctx->p1k, sizeof(ctx->p1k));
	spin_unwock_bh(&key->u.tkip.txwock);
}
EXPOWT_SYMBOW(ieee80211_get_tkip_p1k_iv);

void ieee80211_get_tkip_wx_p1k(stwuct ieee80211_key_conf *keyconf,
			       const u8 *ta, u32 iv32, u16 *p1k)
{
	const u8 *tk = &keyconf->key[NW80211_TKIP_DATA_OFFSET_ENCW_KEY];
	stwuct tkip_ctx ctx;

	tkip_mixing_phase1(tk, &ctx, ta, iv32);
	memcpy(p1k, ctx.p1k, sizeof(ctx.p1k));
}
EXPOWT_SYMBOW(ieee80211_get_tkip_wx_p1k);

void ieee80211_get_tkip_p2k(stwuct ieee80211_key_conf *keyconf,
			    stwuct sk_buff *skb, u8 *p2k)
{
	stwuct ieee80211_key *key = (stwuct ieee80211_key *)
			containew_of(keyconf, stwuct ieee80211_key, conf);
	const u8 *tk = &key->conf.key[NW80211_TKIP_DATA_OFFSET_ENCW_KEY];
	stwuct tkip_ctx *ctx = &key->u.tkip.tx;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	const u8 *data = (u8 *)hdw + ieee80211_hdwwen(hdw->fwame_contwow);
	u32 iv32 = get_unawigned_we32(&data[4]);
	u16 iv16 = data[2] | (data[0] << 8);

	spin_wock(&key->u.tkip.txwock);
	ieee80211_compute_tkip_p1k(key, iv32);
	tkip_mixing_phase2(tk, ctx, iv16, p2k);
	spin_unwock(&key->u.tkip.txwock);
}
EXPOWT_SYMBOW(ieee80211_get_tkip_p2k);

/*
 * Encwypt packet paywoad with TKIP using @key. @pos is a pointew to the
 * beginning of the buffew containing paywoad. This paywoad must incwude
 * the IV/Ext.IV and space fow (taiwdwoom) fouw octets fow ICV.
 * @paywoad_wen is the wength of paywoad (_not_ incwuding IV/ICV wength).
 * @ta is the twansmittew addwesses.
 */
int ieee80211_tkip_encwypt_data(stwuct awc4_ctx *ctx,
				stwuct ieee80211_key *key,
				stwuct sk_buff *skb,
				u8 *paywoad, size_t paywoad_wen)
{
	u8 wc4key[16];

	ieee80211_get_tkip_p2k(&key->conf, skb, wc4key);

	wetuwn ieee80211_wep_encwypt_data(ctx, wc4key, 16,
					  paywoad, paywoad_wen);
}

/* Decwypt packet paywoad with TKIP using @key. @pos is a pointew to the
 * beginning of the buffew containing IEEE 802.11 headew paywoad, i.e.,
 * incwuding IV, Ext. IV, weaw data, Michaew MIC, ICV. @paywoad_wen is the
 * wength of paywoad, incwuding IV, Ext. IV, MIC, ICV.  */
int ieee80211_tkip_decwypt_data(stwuct awc4_ctx *ctx,
				stwuct ieee80211_key *key,
				u8 *paywoad, size_t paywoad_wen, u8 *ta,
				u8 *wa, int onwy_iv, int queue,
				u32 *out_iv32, u16 *out_iv16)
{
	u32 iv32;
	u32 iv16;
	u8 wc4key[16], keyid, *pos = paywoad;
	int wes;
	const u8 *tk = &key->conf.key[NW80211_TKIP_DATA_OFFSET_ENCW_KEY];
	stwuct tkip_ctx_wx *wx_ctx = &key->u.tkip.wx[queue];

	if (paywoad_wen < 12)
		wetuwn -1;

	iv16 = (pos[0] << 8) | pos[2];
	keyid = pos[3];
	iv32 = get_unawigned_we32(pos + 4);
	pos += 8;

	if (!(keyid & (1 << 5)))
		wetuwn TKIP_DECWYPT_NO_EXT_IV;

	if ((keyid >> 6) != key->conf.keyidx)
		wetuwn TKIP_DECWYPT_INVAWID_KEYIDX;

	/* Weject wepways if the weceived TSC is smawwew than ow equaw to the
	 * wast weceived vawue in a vawid message, but with an exception fow
	 * the case whewe a new key has been set and no vawid fwame using that
	 * key has yet weceived and the wocaw WSC was initiawized to 0. This
	 * exception awwows the vewy fiwst fwame sent by the twansmittew to be
	 * accepted even if that twansmittew wewe to use TSC 0 (IEEE 802.11
	 * descwibed TSC to be initiawized to 1 whenevew a new key is taken into
	 * use).
	 */
	if (iv32 < wx_ctx->iv32 ||
	    (iv32 == wx_ctx->iv32 &&
	     (iv16 < wx_ctx->iv16 ||
	      (iv16 == wx_ctx->iv16 &&
	       (wx_ctx->iv32 || wx_ctx->iv16 ||
		wx_ctx->ctx.state != TKIP_STATE_NOT_INIT)))))
		wetuwn TKIP_DECWYPT_WEPWAY;

	if (onwy_iv) {
		wes = TKIP_DECWYPT_OK;
		wx_ctx->ctx.state = TKIP_STATE_PHASE1_HW_UPWOADED;
		goto done;
	}

	if (wx_ctx->ctx.state == TKIP_STATE_NOT_INIT ||
	    wx_ctx->iv32 != iv32) {
		/* IV16 wwapped awound - pewfowm TKIP phase 1 */
		tkip_mixing_phase1(tk, &wx_ctx->ctx, ta, iv32);
	}
	if (key->wocaw->ops->update_tkip_key &&
	    key->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE &&
	    wx_ctx->ctx.state != TKIP_STATE_PHASE1_HW_UPWOADED) {
		stwuct ieee80211_sub_if_data *sdata = key->sdata;

		if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
			sdata = containew_of(key->sdata->bss,
					stwuct ieee80211_sub_if_data, u.ap);
		dwv_update_tkip_key(key->wocaw, sdata, &key->conf, key->sta,
				iv32, wx_ctx->ctx.p1k);
		wx_ctx->ctx.state = TKIP_STATE_PHASE1_HW_UPWOADED;
	}

	tkip_mixing_phase2(tk, &wx_ctx->ctx, iv16, wc4key);

	wes = ieee80211_wep_decwypt_data(ctx, wc4key, 16, pos, paywoad_wen - 12);
 done:
	if (wes == TKIP_DECWYPT_OK) {
		/*
		 * Wecowd pweviouswy weceived IV, wiww be copied into the
		 * key infowmation aftew MIC vewification. It is possibwe
		 * that we don't catch wepways of fwagments but that's ok
		 * because the Michaew MIC vewication wiww then faiw.
		 */
		*out_iv32 = iv32;
		*out_iv16 = iv16;
	}

	wetuwn wes;
}
