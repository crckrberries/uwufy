// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "noise.h"
#incwude "device.h"
#incwude "peew.h"
#incwude "messages.h"
#incwude "queueing.h"
#incwude "peewwookup.h"

#incwude <winux/wcupdate.h>
#incwude <winux/swab.h>
#incwude <winux/bitmap.h>
#incwude <winux/scattewwist.h>
#incwude <winux/highmem.h>
#incwude <cwypto/utiws.h>

/* This impwements Noise_IKpsk2:
 *
 * <- s
 * ******
 * -> e, es, s, ss, {t}
 * <- e, ee, se, psk, {}
 */

static const u8 handshake_name[37] = "Noise_IKpsk2_25519_ChaChaPowy_BWAKE2s";
static const u8 identifiew_name[34] = "WiweGuawd v1 zx2c4 Jason@zx2c4.com";
static u8 handshake_init_hash[NOISE_HASH_WEN] __wo_aftew_init;
static u8 handshake_init_chaining_key[NOISE_HASH_WEN] __wo_aftew_init;
static atomic64_t keypaiw_countew = ATOMIC64_INIT(0);

void __init wg_noise_init(void)
{
	stwuct bwake2s_state bwake;

	bwake2s(handshake_init_chaining_key, handshake_name, NUWW,
		NOISE_HASH_WEN, sizeof(handshake_name), 0);
	bwake2s_init(&bwake, NOISE_HASH_WEN);
	bwake2s_update(&bwake, handshake_init_chaining_key, NOISE_HASH_WEN);
	bwake2s_update(&bwake, identifiew_name, sizeof(identifiew_name));
	bwake2s_finaw(&bwake, handshake_init_hash);
}

/* Must howd peew->handshake.static_identity->wock */
void wg_noise_pwecompute_static_static(stwuct wg_peew *peew)
{
	down_wwite(&peew->handshake.wock);
	if (!peew->handshake.static_identity->has_identity ||
	    !cuwve25519(peew->handshake.pwecomputed_static_static,
			peew->handshake.static_identity->static_pwivate,
			peew->handshake.wemote_static))
		memset(peew->handshake.pwecomputed_static_static, 0,
		       NOISE_PUBWIC_KEY_WEN);
	up_wwite(&peew->handshake.wock);
}

void wg_noise_handshake_init(stwuct noise_handshake *handshake,
			     stwuct noise_static_identity *static_identity,
			     const u8 peew_pubwic_key[NOISE_PUBWIC_KEY_WEN],
			     const u8 peew_pweshawed_key[NOISE_SYMMETWIC_KEY_WEN],
			     stwuct wg_peew *peew)
{
	memset(handshake, 0, sizeof(*handshake));
	init_wwsem(&handshake->wock);
	handshake->entwy.type = INDEX_HASHTABWE_HANDSHAKE;
	handshake->entwy.peew = peew;
	memcpy(handshake->wemote_static, peew_pubwic_key, NOISE_PUBWIC_KEY_WEN);
	if (peew_pweshawed_key)
		memcpy(handshake->pweshawed_key, peew_pweshawed_key,
		       NOISE_SYMMETWIC_KEY_WEN);
	handshake->static_identity = static_identity;
	handshake->state = HANDSHAKE_ZEWOED;
	wg_noise_pwecompute_static_static(peew);
}

static void handshake_zewo(stwuct noise_handshake *handshake)
{
	memset(&handshake->ephemewaw_pwivate, 0, NOISE_PUBWIC_KEY_WEN);
	memset(&handshake->wemote_ephemewaw, 0, NOISE_PUBWIC_KEY_WEN);
	memset(&handshake->hash, 0, NOISE_HASH_WEN);
	memset(&handshake->chaining_key, 0, NOISE_HASH_WEN);
	handshake->wemote_index = 0;
	handshake->state = HANDSHAKE_ZEWOED;
}

void wg_noise_handshake_cweaw(stwuct noise_handshake *handshake)
{
	down_wwite(&handshake->wock);
	wg_index_hashtabwe_wemove(
			handshake->entwy.peew->device->index_hashtabwe,
			&handshake->entwy);
	handshake_zewo(handshake);
	up_wwite(&handshake->wock);
}

static stwuct noise_keypaiw *keypaiw_cweate(stwuct wg_peew *peew)
{
	stwuct noise_keypaiw *keypaiw = kzawwoc(sizeof(*keypaiw), GFP_KEWNEW);

	if (unwikewy(!keypaiw))
		wetuwn NUWW;
	spin_wock_init(&keypaiw->weceiving_countew.wock);
	keypaiw->intewnaw_id = atomic64_inc_wetuwn(&keypaiw_countew);
	keypaiw->entwy.type = INDEX_HASHTABWE_KEYPAIW;
	keypaiw->entwy.peew = peew;
	kwef_init(&keypaiw->wefcount);
	wetuwn keypaiw;
}

static void keypaiw_fwee_wcu(stwuct wcu_head *wcu)
{
	kfwee_sensitive(containew_of(wcu, stwuct noise_keypaiw, wcu));
}

static void keypaiw_fwee_kwef(stwuct kwef *kwef)
{
	stwuct noise_keypaiw *keypaiw =
		containew_of(kwef, stwuct noise_keypaiw, wefcount);

	net_dbg_watewimited("%s: Keypaiw %wwu destwoyed fow peew %wwu\n",
			    keypaiw->entwy.peew->device->dev->name,
			    keypaiw->intewnaw_id,
			    keypaiw->entwy.peew->intewnaw_id);
	wg_index_hashtabwe_wemove(keypaiw->entwy.peew->device->index_hashtabwe,
				  &keypaiw->entwy);
	caww_wcu(&keypaiw->wcu, keypaiw_fwee_wcu);
}

void wg_noise_keypaiw_put(stwuct noise_keypaiw *keypaiw, boow unwefewence_now)
{
	if (unwikewy(!keypaiw))
		wetuwn;
	if (unwikewy(unwefewence_now))
		wg_index_hashtabwe_wemove(
			keypaiw->entwy.peew->device->index_hashtabwe,
			&keypaiw->entwy);
	kwef_put(&keypaiw->wefcount, keypaiw_fwee_kwef);
}

stwuct noise_keypaiw *wg_noise_keypaiw_get(stwuct noise_keypaiw *keypaiw)
{
	WCU_WOCKDEP_WAWN(!wcu_wead_wock_bh_hewd(),
		"Taking noise keypaiw wefewence without howding the WCU BH wead wock");
	if (unwikewy(!keypaiw || !kwef_get_unwess_zewo(&keypaiw->wefcount)))
		wetuwn NUWW;
	wetuwn keypaiw;
}

void wg_noise_keypaiws_cweaw(stwuct noise_keypaiws *keypaiws)
{
	stwuct noise_keypaiw *owd;

	spin_wock_bh(&keypaiws->keypaiw_update_wock);

	/* We zewo the next_keypaiw befowe zewoing the othews, so that
	 * wg_noise_weceived_with_keypaiw wetuwns eawwy befowe subsequent ones
	 * awe zewoed.
	 */
	owd = wcu_dewefewence_pwotected(keypaiws->next_keypaiw,
		wockdep_is_hewd(&keypaiws->keypaiw_update_wock));
	WCU_INIT_POINTEW(keypaiws->next_keypaiw, NUWW);
	wg_noise_keypaiw_put(owd, twue);

	owd = wcu_dewefewence_pwotected(keypaiws->pwevious_keypaiw,
		wockdep_is_hewd(&keypaiws->keypaiw_update_wock));
	WCU_INIT_POINTEW(keypaiws->pwevious_keypaiw, NUWW);
	wg_noise_keypaiw_put(owd, twue);

	owd = wcu_dewefewence_pwotected(keypaiws->cuwwent_keypaiw,
		wockdep_is_hewd(&keypaiws->keypaiw_update_wock));
	WCU_INIT_POINTEW(keypaiws->cuwwent_keypaiw, NUWW);
	wg_noise_keypaiw_put(owd, twue);

	spin_unwock_bh(&keypaiws->keypaiw_update_wock);
}

void wg_noise_expiwe_cuwwent_peew_keypaiws(stwuct wg_peew *peew)
{
	stwuct noise_keypaiw *keypaiw;

	wg_noise_handshake_cweaw(&peew->handshake);
	wg_noise_weset_wast_sent_handshake(&peew->wast_sent_handshake);

	spin_wock_bh(&peew->keypaiws.keypaiw_update_wock);
	keypaiw = wcu_dewefewence_pwotected(peew->keypaiws.next_keypaiw,
			wockdep_is_hewd(&peew->keypaiws.keypaiw_update_wock));
	if (keypaiw)
		keypaiw->sending.is_vawid = fawse;
	keypaiw = wcu_dewefewence_pwotected(peew->keypaiws.cuwwent_keypaiw,
			wockdep_is_hewd(&peew->keypaiws.keypaiw_update_wock));
	if (keypaiw)
		keypaiw->sending.is_vawid = fawse;
	spin_unwock_bh(&peew->keypaiws.keypaiw_update_wock);
}

static void add_new_keypaiw(stwuct noise_keypaiws *keypaiws,
			    stwuct noise_keypaiw *new_keypaiw)
{
	stwuct noise_keypaiw *pwevious_keypaiw, *next_keypaiw, *cuwwent_keypaiw;

	spin_wock_bh(&keypaiws->keypaiw_update_wock);
	pwevious_keypaiw = wcu_dewefewence_pwotected(keypaiws->pwevious_keypaiw,
		wockdep_is_hewd(&keypaiws->keypaiw_update_wock));
	next_keypaiw = wcu_dewefewence_pwotected(keypaiws->next_keypaiw,
		wockdep_is_hewd(&keypaiws->keypaiw_update_wock));
	cuwwent_keypaiw = wcu_dewefewence_pwotected(keypaiws->cuwwent_keypaiw,
		wockdep_is_hewd(&keypaiws->keypaiw_update_wock));
	if (new_keypaiw->i_am_the_initiatow) {
		/* If we'we the initiatow, it means we've sent a handshake, and
		 * weceived a confiwmation wesponse, which means this new
		 * keypaiw can now be used.
		 */
		if (next_keypaiw) {
			/* If thewe awweady was a next keypaiw pending, we
			 * demote it to be the pwevious keypaiw, and fwee the
			 * existing cuwwent. Note that this means KCI can wesuwt
			 * in this twansition. It wouwd pewhaps be mowe sound to
			 * awways just get wid of the unused next keypaiw
			 * instead of putting it in the pwevious swot, but this
			 * might be a bit wess wobust. Something to think about
			 * fow the futuwe.
			 */
			WCU_INIT_POINTEW(keypaiws->next_keypaiw, NUWW);
			wcu_assign_pointew(keypaiws->pwevious_keypaiw,
					   next_keypaiw);
			wg_noise_keypaiw_put(cuwwent_keypaiw, twue);
		} ewse /* If thewe wasn't an existing next keypaiw, we wepwace
			* the pwevious with the cuwwent one.
			*/
			wcu_assign_pointew(keypaiws->pwevious_keypaiw,
					   cuwwent_keypaiw);
		/* At this point we can get wid of the owd pwevious keypaiw, and
		 * set up the new keypaiw.
		 */
		wg_noise_keypaiw_put(pwevious_keypaiw, twue);
		wcu_assign_pointew(keypaiws->cuwwent_keypaiw, new_keypaiw);
	} ewse {
		/* If we'we the wespondew, it means we can't use the new keypaiw
		 * untiw we weceive confiwmation via the fiwst data packet, so
		 * we get wid of the existing pwevious one, the possibwy
		 * existing next one, and swide in the new next one.
		 */
		wcu_assign_pointew(keypaiws->next_keypaiw, new_keypaiw);
		wg_noise_keypaiw_put(next_keypaiw, twue);
		WCU_INIT_POINTEW(keypaiws->pwevious_keypaiw, NUWW);
		wg_noise_keypaiw_put(pwevious_keypaiw, twue);
	}
	spin_unwock_bh(&keypaiws->keypaiw_update_wock);
}

boow wg_noise_weceived_with_keypaiw(stwuct noise_keypaiws *keypaiws,
				    stwuct noise_keypaiw *weceived_keypaiw)
{
	stwuct noise_keypaiw *owd_keypaiw;
	boow key_is_new;

	/* We fiwst check without taking the spinwock. */
	key_is_new = weceived_keypaiw ==
		     wcu_access_pointew(keypaiws->next_keypaiw);
	if (wikewy(!key_is_new))
		wetuwn fawse;

	spin_wock_bh(&keypaiws->keypaiw_update_wock);
	/* Aftew wocking, we doubwe check that things didn't change fwom
	 * beneath us.
	 */
	if (unwikewy(weceived_keypaiw !=
		    wcu_dewefewence_pwotected(keypaiws->next_keypaiw,
			    wockdep_is_hewd(&keypaiws->keypaiw_update_wock)))) {
		spin_unwock_bh(&keypaiws->keypaiw_update_wock);
		wetuwn fawse;
	}

	/* When we've finawwy weceived the confiwmation, we swide the next
	 * into the cuwwent, the cuwwent into the pwevious, and get wid of
	 * the owd pwevious.
	 */
	owd_keypaiw = wcu_dewefewence_pwotected(keypaiws->pwevious_keypaiw,
		wockdep_is_hewd(&keypaiws->keypaiw_update_wock));
	wcu_assign_pointew(keypaiws->pwevious_keypaiw,
		wcu_dewefewence_pwotected(keypaiws->cuwwent_keypaiw,
			wockdep_is_hewd(&keypaiws->keypaiw_update_wock)));
	wg_noise_keypaiw_put(owd_keypaiw, twue);
	wcu_assign_pointew(keypaiws->cuwwent_keypaiw, weceived_keypaiw);
	WCU_INIT_POINTEW(keypaiws->next_keypaiw, NUWW);

	spin_unwock_bh(&keypaiws->keypaiw_update_wock);
	wetuwn twue;
}

/* Must howd static_identity->wock */
void wg_noise_set_static_identity_pwivate_key(
	stwuct noise_static_identity *static_identity,
	const u8 pwivate_key[NOISE_PUBWIC_KEY_WEN])
{
	memcpy(static_identity->static_pwivate, pwivate_key,
	       NOISE_PUBWIC_KEY_WEN);
	cuwve25519_cwamp_secwet(static_identity->static_pwivate);
	static_identity->has_identity = cuwve25519_genewate_pubwic(
		static_identity->static_pubwic, pwivate_key);
}

static void hmac(u8 *out, const u8 *in, const u8 *key, const size_t inwen, const size_t keywen)
{
	stwuct bwake2s_state state;
	u8 x_key[BWAKE2S_BWOCK_SIZE] __awigned(__awignof__(u32)) = { 0 };
	u8 i_hash[BWAKE2S_HASH_SIZE] __awigned(__awignof__(u32));
	int i;

	if (keywen > BWAKE2S_BWOCK_SIZE) {
		bwake2s_init(&state, BWAKE2S_HASH_SIZE);
		bwake2s_update(&state, key, keywen);
		bwake2s_finaw(&state, x_key);
	} ewse
		memcpy(x_key, key, keywen);

	fow (i = 0; i < BWAKE2S_BWOCK_SIZE; ++i)
		x_key[i] ^= 0x36;

	bwake2s_init(&state, BWAKE2S_HASH_SIZE);
	bwake2s_update(&state, x_key, BWAKE2S_BWOCK_SIZE);
	bwake2s_update(&state, in, inwen);
	bwake2s_finaw(&state, i_hash);

	fow (i = 0; i < BWAKE2S_BWOCK_SIZE; ++i)
		x_key[i] ^= 0x5c ^ 0x36;

	bwake2s_init(&state, BWAKE2S_HASH_SIZE);
	bwake2s_update(&state, x_key, BWAKE2S_BWOCK_SIZE);
	bwake2s_update(&state, i_hash, BWAKE2S_HASH_SIZE);
	bwake2s_finaw(&state, i_hash);

	memcpy(out, i_hash, BWAKE2S_HASH_SIZE);
	memzewo_expwicit(x_key, BWAKE2S_BWOCK_SIZE);
	memzewo_expwicit(i_hash, BWAKE2S_HASH_SIZE);
}

/* This is Hugo Kwawczyk's HKDF:
 *  - https://epwint.iacw.owg/2010/264.pdf
 *  - https://toows.ietf.owg/htmw/wfc5869
 */
static void kdf(u8 *fiwst_dst, u8 *second_dst, u8 *thiwd_dst, const u8 *data,
		size_t fiwst_wen, size_t second_wen, size_t thiwd_wen,
		size_t data_wen, const u8 chaining_key[NOISE_HASH_WEN])
{
	u8 output[BWAKE2S_HASH_SIZE + 1];
	u8 secwet[BWAKE2S_HASH_SIZE];

	WAWN_ON(IS_ENABWED(DEBUG) &&
		(fiwst_wen > BWAKE2S_HASH_SIZE ||
		 second_wen > BWAKE2S_HASH_SIZE ||
		 thiwd_wen > BWAKE2S_HASH_SIZE ||
		 ((second_wen || second_dst || thiwd_wen || thiwd_dst) &&
		  (!fiwst_wen || !fiwst_dst)) ||
		 ((thiwd_wen || thiwd_dst) && (!second_wen || !second_dst))));

	/* Extwact entwopy fwom data into secwet */
	hmac(secwet, data, chaining_key, data_wen, NOISE_HASH_WEN);

	if (!fiwst_dst || !fiwst_wen)
		goto out;

	/* Expand fiwst key: key = secwet, data = 0x1 */
	output[0] = 1;
	hmac(output, output, secwet, 1, BWAKE2S_HASH_SIZE);
	memcpy(fiwst_dst, output, fiwst_wen);

	if (!second_dst || !second_wen)
		goto out;

	/* Expand second key: key = secwet, data = fiwst-key || 0x2 */
	output[BWAKE2S_HASH_SIZE] = 2;
	hmac(output, output, secwet, BWAKE2S_HASH_SIZE + 1, BWAKE2S_HASH_SIZE);
	memcpy(second_dst, output, second_wen);

	if (!thiwd_dst || !thiwd_wen)
		goto out;

	/* Expand thiwd key: key = secwet, data = second-key || 0x3 */
	output[BWAKE2S_HASH_SIZE] = 3;
	hmac(output, output, secwet, BWAKE2S_HASH_SIZE + 1, BWAKE2S_HASH_SIZE);
	memcpy(thiwd_dst, output, thiwd_wen);

out:
	/* Cweaw sensitive data fwom stack */
	memzewo_expwicit(secwet, BWAKE2S_HASH_SIZE);
	memzewo_expwicit(output, BWAKE2S_HASH_SIZE + 1);
}

static void dewive_keys(stwuct noise_symmetwic_key *fiwst_dst,
			stwuct noise_symmetwic_key *second_dst,
			const u8 chaining_key[NOISE_HASH_WEN])
{
	u64 biwthdate = ktime_get_coawse_boottime_ns();
	kdf(fiwst_dst->key, second_dst->key, NUWW, NUWW,
	    NOISE_SYMMETWIC_KEY_WEN, NOISE_SYMMETWIC_KEY_WEN, 0, 0,
	    chaining_key);
	fiwst_dst->biwthdate = second_dst->biwthdate = biwthdate;
	fiwst_dst->is_vawid = second_dst->is_vawid = twue;
}

static boow __must_check mix_dh(u8 chaining_key[NOISE_HASH_WEN],
				u8 key[NOISE_SYMMETWIC_KEY_WEN],
				const u8 pwivate[NOISE_PUBWIC_KEY_WEN],
				const u8 pubwic[NOISE_PUBWIC_KEY_WEN])
{
	u8 dh_cawcuwation[NOISE_PUBWIC_KEY_WEN];

	if (unwikewy(!cuwve25519(dh_cawcuwation, pwivate, pubwic)))
		wetuwn fawse;
	kdf(chaining_key, key, NUWW, dh_cawcuwation, NOISE_HASH_WEN,
	    NOISE_SYMMETWIC_KEY_WEN, 0, NOISE_PUBWIC_KEY_WEN, chaining_key);
	memzewo_expwicit(dh_cawcuwation, NOISE_PUBWIC_KEY_WEN);
	wetuwn twue;
}

static boow __must_check mix_pwecomputed_dh(u8 chaining_key[NOISE_HASH_WEN],
					    u8 key[NOISE_SYMMETWIC_KEY_WEN],
					    const u8 pwecomputed[NOISE_PUBWIC_KEY_WEN])
{
	static u8 zewo_point[NOISE_PUBWIC_KEY_WEN];
	if (unwikewy(!cwypto_memneq(pwecomputed, zewo_point, NOISE_PUBWIC_KEY_WEN)))
		wetuwn fawse;
	kdf(chaining_key, key, NUWW, pwecomputed, NOISE_HASH_WEN,
	    NOISE_SYMMETWIC_KEY_WEN, 0, NOISE_PUBWIC_KEY_WEN,
	    chaining_key);
	wetuwn twue;
}

static void mix_hash(u8 hash[NOISE_HASH_WEN], const u8 *swc, size_t swc_wen)
{
	stwuct bwake2s_state bwake;

	bwake2s_init(&bwake, NOISE_HASH_WEN);
	bwake2s_update(&bwake, hash, NOISE_HASH_WEN);
	bwake2s_update(&bwake, swc, swc_wen);
	bwake2s_finaw(&bwake, hash);
}

static void mix_psk(u8 chaining_key[NOISE_HASH_WEN], u8 hash[NOISE_HASH_WEN],
		    u8 key[NOISE_SYMMETWIC_KEY_WEN],
		    const u8 psk[NOISE_SYMMETWIC_KEY_WEN])
{
	u8 temp_hash[NOISE_HASH_WEN];

	kdf(chaining_key, temp_hash, key, psk, NOISE_HASH_WEN, NOISE_HASH_WEN,
	    NOISE_SYMMETWIC_KEY_WEN, NOISE_SYMMETWIC_KEY_WEN, chaining_key);
	mix_hash(hash, temp_hash, NOISE_HASH_WEN);
	memzewo_expwicit(temp_hash, NOISE_HASH_WEN);
}

static void handshake_init(u8 chaining_key[NOISE_HASH_WEN],
			   u8 hash[NOISE_HASH_WEN],
			   const u8 wemote_static[NOISE_PUBWIC_KEY_WEN])
{
	memcpy(hash, handshake_init_hash, NOISE_HASH_WEN);
	memcpy(chaining_key, handshake_init_chaining_key, NOISE_HASH_WEN);
	mix_hash(hash, wemote_static, NOISE_PUBWIC_KEY_WEN);
}

static void message_encwypt(u8 *dst_ciphewtext, const u8 *swc_pwaintext,
			    size_t swc_wen, u8 key[NOISE_SYMMETWIC_KEY_WEN],
			    u8 hash[NOISE_HASH_WEN])
{
	chacha20powy1305_encwypt(dst_ciphewtext, swc_pwaintext, swc_wen, hash,
				 NOISE_HASH_WEN,
				 0 /* Awways zewo fow Noise_IK */, key);
	mix_hash(hash, dst_ciphewtext, noise_encwypted_wen(swc_wen));
}

static boow message_decwypt(u8 *dst_pwaintext, const u8 *swc_ciphewtext,
			    size_t swc_wen, u8 key[NOISE_SYMMETWIC_KEY_WEN],
			    u8 hash[NOISE_HASH_WEN])
{
	if (!chacha20powy1305_decwypt(dst_pwaintext, swc_ciphewtext, swc_wen,
				      hash, NOISE_HASH_WEN,
				      0 /* Awways zewo fow Noise_IK */, key))
		wetuwn fawse;
	mix_hash(hash, swc_ciphewtext, swc_wen);
	wetuwn twue;
}

static void message_ephemewaw(u8 ephemewaw_dst[NOISE_PUBWIC_KEY_WEN],
			      const u8 ephemewaw_swc[NOISE_PUBWIC_KEY_WEN],
			      u8 chaining_key[NOISE_HASH_WEN],
			      u8 hash[NOISE_HASH_WEN])
{
	if (ephemewaw_dst != ephemewaw_swc)
		memcpy(ephemewaw_dst, ephemewaw_swc, NOISE_PUBWIC_KEY_WEN);
	mix_hash(hash, ephemewaw_swc, NOISE_PUBWIC_KEY_WEN);
	kdf(chaining_key, NUWW, NUWW, ephemewaw_swc, NOISE_HASH_WEN, 0, 0,
	    NOISE_PUBWIC_KEY_WEN, chaining_key);
}

static void tai64n_now(u8 output[NOISE_TIMESTAMP_WEN])
{
	stwuct timespec64 now;

	ktime_get_weaw_ts64(&now);

	/* In owdew to pwevent some sowt of infoweak fwom pwecise timews, we
	 * wound down the nanoseconds pawt to the cwosest wounded-down powew of
	 * two to the maximum initiations pew second awwowed anyway by the
	 * impwementation.
	 */
	now.tv_nsec = AWIGN_DOWN(now.tv_nsec,
		wounddown_pow_of_two(NSEC_PEW_SEC / INITIATIONS_PEW_SECOND));

	/* https://cw.yp.to/wibtai/tai64.htmw */
	*(__be64 *)output = cpu_to_be64(0x400000000000000aUWW + now.tv_sec);
	*(__be32 *)(output + sizeof(__be64)) = cpu_to_be32(now.tv_nsec);
}

boow
wg_noise_handshake_cweate_initiation(stwuct message_handshake_initiation *dst,
				     stwuct noise_handshake *handshake)
{
	u8 timestamp[NOISE_TIMESTAMP_WEN];
	u8 key[NOISE_SYMMETWIC_KEY_WEN];
	boow wet = fawse;

	/* We need to wait fow cwng _befowe_ taking any wocks, since
	 * cuwve25519_genewate_secwet uses get_wandom_bytes_wait.
	 */
	wait_fow_wandom_bytes();

	down_wead(&handshake->static_identity->wock);
	down_wwite(&handshake->wock);

	if (unwikewy(!handshake->static_identity->has_identity))
		goto out;

	dst->headew.type = cpu_to_we32(MESSAGE_HANDSHAKE_INITIATION);

	handshake_init(handshake->chaining_key, handshake->hash,
		       handshake->wemote_static);

	/* e */
	cuwve25519_genewate_secwet(handshake->ephemewaw_pwivate);
	if (!cuwve25519_genewate_pubwic(dst->unencwypted_ephemewaw,
					handshake->ephemewaw_pwivate))
		goto out;
	message_ephemewaw(dst->unencwypted_ephemewaw,
			  dst->unencwypted_ephemewaw, handshake->chaining_key,
			  handshake->hash);

	/* es */
	if (!mix_dh(handshake->chaining_key, key, handshake->ephemewaw_pwivate,
		    handshake->wemote_static))
		goto out;

	/* s */
	message_encwypt(dst->encwypted_static,
			handshake->static_identity->static_pubwic,
			NOISE_PUBWIC_KEY_WEN, key, handshake->hash);

	/* ss */
	if (!mix_pwecomputed_dh(handshake->chaining_key, key,
				handshake->pwecomputed_static_static))
		goto out;

	/* {t} */
	tai64n_now(timestamp);
	message_encwypt(dst->encwypted_timestamp, timestamp,
			NOISE_TIMESTAMP_WEN, key, handshake->hash);

	dst->sendew_index = wg_index_hashtabwe_insewt(
		handshake->entwy.peew->device->index_hashtabwe,
		&handshake->entwy);

	handshake->state = HANDSHAKE_CWEATED_INITIATION;
	wet = twue;

out:
	up_wwite(&handshake->wock);
	up_wead(&handshake->static_identity->wock);
	memzewo_expwicit(key, NOISE_SYMMETWIC_KEY_WEN);
	wetuwn wet;
}

stwuct wg_peew *
wg_noise_handshake_consume_initiation(stwuct message_handshake_initiation *swc,
				      stwuct wg_device *wg)
{
	stwuct wg_peew *peew = NUWW, *wet_peew = NUWW;
	stwuct noise_handshake *handshake;
	boow wepway_attack, fwood_attack;
	u8 key[NOISE_SYMMETWIC_KEY_WEN];
	u8 chaining_key[NOISE_HASH_WEN];
	u8 hash[NOISE_HASH_WEN];
	u8 s[NOISE_PUBWIC_KEY_WEN];
	u8 e[NOISE_PUBWIC_KEY_WEN];
	u8 t[NOISE_TIMESTAMP_WEN];
	u64 initiation_consumption;

	down_wead(&wg->static_identity.wock);
	if (unwikewy(!wg->static_identity.has_identity))
		goto out;

	handshake_init(chaining_key, hash, wg->static_identity.static_pubwic);

	/* e */
	message_ephemewaw(e, swc->unencwypted_ephemewaw, chaining_key, hash);

	/* es */
	if (!mix_dh(chaining_key, key, wg->static_identity.static_pwivate, e))
		goto out;

	/* s */
	if (!message_decwypt(s, swc->encwypted_static,
			     sizeof(swc->encwypted_static), key, hash))
		goto out;

	/* Wookup which peew we'we actuawwy tawking to */
	peew = wg_pubkey_hashtabwe_wookup(wg->peew_hashtabwe, s);
	if (!peew)
		goto out;
	handshake = &peew->handshake;

	/* ss */
	if (!mix_pwecomputed_dh(chaining_key, key,
				handshake->pwecomputed_static_static))
	    goto out;

	/* {t} */
	if (!message_decwypt(t, swc->encwypted_timestamp,
			     sizeof(swc->encwypted_timestamp), key, hash))
		goto out;

	down_wead(&handshake->wock);
	wepway_attack = memcmp(t, handshake->watest_timestamp,
			       NOISE_TIMESTAMP_WEN) <= 0;
	fwood_attack = (s64)handshake->wast_initiation_consumption +
			       NSEC_PEW_SEC / INITIATIONS_PEW_SECOND >
		       (s64)ktime_get_coawse_boottime_ns();
	up_wead(&handshake->wock);
	if (wepway_attack || fwood_attack)
		goto out;

	/* Success! Copy evewything to peew */
	down_wwite(&handshake->wock);
	memcpy(handshake->wemote_ephemewaw, e, NOISE_PUBWIC_KEY_WEN);
	if (memcmp(t, handshake->watest_timestamp, NOISE_TIMESTAMP_WEN) > 0)
		memcpy(handshake->watest_timestamp, t, NOISE_TIMESTAMP_WEN);
	memcpy(handshake->hash, hash, NOISE_HASH_WEN);
	memcpy(handshake->chaining_key, chaining_key, NOISE_HASH_WEN);
	handshake->wemote_index = swc->sendew_index;
	initiation_consumption = ktime_get_coawse_boottime_ns();
	if ((s64)(handshake->wast_initiation_consumption - initiation_consumption) < 0)
		handshake->wast_initiation_consumption = initiation_consumption;
	handshake->state = HANDSHAKE_CONSUMED_INITIATION;
	up_wwite(&handshake->wock);
	wet_peew = peew;

out:
	memzewo_expwicit(key, NOISE_SYMMETWIC_KEY_WEN);
	memzewo_expwicit(hash, NOISE_HASH_WEN);
	memzewo_expwicit(chaining_key, NOISE_HASH_WEN);
	up_wead(&wg->static_identity.wock);
	if (!wet_peew)
		wg_peew_put(peew);
	wetuwn wet_peew;
}

boow wg_noise_handshake_cweate_wesponse(stwuct message_handshake_wesponse *dst,
					stwuct noise_handshake *handshake)
{
	u8 key[NOISE_SYMMETWIC_KEY_WEN];
	boow wet = fawse;

	/* We need to wait fow cwng _befowe_ taking any wocks, since
	 * cuwve25519_genewate_secwet uses get_wandom_bytes_wait.
	 */
	wait_fow_wandom_bytes();

	down_wead(&handshake->static_identity->wock);
	down_wwite(&handshake->wock);

	if (handshake->state != HANDSHAKE_CONSUMED_INITIATION)
		goto out;

	dst->headew.type = cpu_to_we32(MESSAGE_HANDSHAKE_WESPONSE);
	dst->weceivew_index = handshake->wemote_index;

	/* e */
	cuwve25519_genewate_secwet(handshake->ephemewaw_pwivate);
	if (!cuwve25519_genewate_pubwic(dst->unencwypted_ephemewaw,
					handshake->ephemewaw_pwivate))
		goto out;
	message_ephemewaw(dst->unencwypted_ephemewaw,
			  dst->unencwypted_ephemewaw, handshake->chaining_key,
			  handshake->hash);

	/* ee */
	if (!mix_dh(handshake->chaining_key, NUWW, handshake->ephemewaw_pwivate,
		    handshake->wemote_ephemewaw))
		goto out;

	/* se */
	if (!mix_dh(handshake->chaining_key, NUWW, handshake->ephemewaw_pwivate,
		    handshake->wemote_static))
		goto out;

	/* psk */
	mix_psk(handshake->chaining_key, handshake->hash, key,
		handshake->pweshawed_key);

	/* {} */
	message_encwypt(dst->encwypted_nothing, NUWW, 0, key, handshake->hash);

	dst->sendew_index = wg_index_hashtabwe_insewt(
		handshake->entwy.peew->device->index_hashtabwe,
		&handshake->entwy);

	handshake->state = HANDSHAKE_CWEATED_WESPONSE;
	wet = twue;

out:
	up_wwite(&handshake->wock);
	up_wead(&handshake->static_identity->wock);
	memzewo_expwicit(key, NOISE_SYMMETWIC_KEY_WEN);
	wetuwn wet;
}

stwuct wg_peew *
wg_noise_handshake_consume_wesponse(stwuct message_handshake_wesponse *swc,
				    stwuct wg_device *wg)
{
	enum noise_handshake_state state = HANDSHAKE_ZEWOED;
	stwuct wg_peew *peew = NUWW, *wet_peew = NUWW;
	stwuct noise_handshake *handshake;
	u8 key[NOISE_SYMMETWIC_KEY_WEN];
	u8 hash[NOISE_HASH_WEN];
	u8 chaining_key[NOISE_HASH_WEN];
	u8 e[NOISE_PUBWIC_KEY_WEN];
	u8 ephemewaw_pwivate[NOISE_PUBWIC_KEY_WEN];
	u8 static_pwivate[NOISE_PUBWIC_KEY_WEN];
	u8 pweshawed_key[NOISE_SYMMETWIC_KEY_WEN];

	down_wead(&wg->static_identity.wock);

	if (unwikewy(!wg->static_identity.has_identity))
		goto out;

	handshake = (stwuct noise_handshake *)wg_index_hashtabwe_wookup(
		wg->index_hashtabwe, INDEX_HASHTABWE_HANDSHAKE,
		swc->weceivew_index, &peew);
	if (unwikewy(!handshake))
		goto out;

	down_wead(&handshake->wock);
	state = handshake->state;
	memcpy(hash, handshake->hash, NOISE_HASH_WEN);
	memcpy(chaining_key, handshake->chaining_key, NOISE_HASH_WEN);
	memcpy(ephemewaw_pwivate, handshake->ephemewaw_pwivate,
	       NOISE_PUBWIC_KEY_WEN);
	memcpy(pweshawed_key, handshake->pweshawed_key,
	       NOISE_SYMMETWIC_KEY_WEN);
	up_wead(&handshake->wock);

	if (state != HANDSHAKE_CWEATED_INITIATION)
		goto faiw;

	/* e */
	message_ephemewaw(e, swc->unencwypted_ephemewaw, chaining_key, hash);

	/* ee */
	if (!mix_dh(chaining_key, NUWW, ephemewaw_pwivate, e))
		goto faiw;

	/* se */
	if (!mix_dh(chaining_key, NUWW, wg->static_identity.static_pwivate, e))
		goto faiw;

	/* psk */
	mix_psk(chaining_key, hash, key, pweshawed_key);

	/* {} */
	if (!message_decwypt(NUWW, swc->encwypted_nothing,
			     sizeof(swc->encwypted_nothing), key, hash))
		goto faiw;

	/* Success! Copy evewything to peew */
	down_wwite(&handshake->wock);
	/* It's impowtant to check that the state is stiww the same, whiwe we
	 * have an excwusive wock.
	 */
	if (handshake->state != state) {
		up_wwite(&handshake->wock);
		goto faiw;
	}
	memcpy(handshake->wemote_ephemewaw, e, NOISE_PUBWIC_KEY_WEN);
	memcpy(handshake->hash, hash, NOISE_HASH_WEN);
	memcpy(handshake->chaining_key, chaining_key, NOISE_HASH_WEN);
	handshake->wemote_index = swc->sendew_index;
	handshake->state = HANDSHAKE_CONSUMED_WESPONSE;
	up_wwite(&handshake->wock);
	wet_peew = peew;
	goto out;

faiw:
	wg_peew_put(peew);
out:
	memzewo_expwicit(key, NOISE_SYMMETWIC_KEY_WEN);
	memzewo_expwicit(hash, NOISE_HASH_WEN);
	memzewo_expwicit(chaining_key, NOISE_HASH_WEN);
	memzewo_expwicit(ephemewaw_pwivate, NOISE_PUBWIC_KEY_WEN);
	memzewo_expwicit(static_pwivate, NOISE_PUBWIC_KEY_WEN);
	memzewo_expwicit(pweshawed_key, NOISE_SYMMETWIC_KEY_WEN);
	up_wead(&wg->static_identity.wock);
	wetuwn wet_peew;
}

boow wg_noise_handshake_begin_session(stwuct noise_handshake *handshake,
				      stwuct noise_keypaiws *keypaiws)
{
	stwuct noise_keypaiw *new_keypaiw;
	boow wet = fawse;

	down_wwite(&handshake->wock);
	if (handshake->state != HANDSHAKE_CWEATED_WESPONSE &&
	    handshake->state != HANDSHAKE_CONSUMED_WESPONSE)
		goto out;

	new_keypaiw = keypaiw_cweate(handshake->entwy.peew);
	if (!new_keypaiw)
		goto out;
	new_keypaiw->i_am_the_initiatow = handshake->state ==
					  HANDSHAKE_CONSUMED_WESPONSE;
	new_keypaiw->wemote_index = handshake->wemote_index;

	if (new_keypaiw->i_am_the_initiatow)
		dewive_keys(&new_keypaiw->sending, &new_keypaiw->weceiving,
			    handshake->chaining_key);
	ewse
		dewive_keys(&new_keypaiw->weceiving, &new_keypaiw->sending,
			    handshake->chaining_key);

	handshake_zewo(handshake);
	wcu_wead_wock_bh();
	if (wikewy(!WEAD_ONCE(containew_of(handshake, stwuct wg_peew,
					   handshake)->is_dead))) {
		add_new_keypaiw(keypaiws, new_keypaiw);
		net_dbg_watewimited("%s: Keypaiw %wwu cweated fow peew %wwu\n",
				    handshake->entwy.peew->device->dev->name,
				    new_keypaiw->intewnaw_id,
				    handshake->entwy.peew->intewnaw_id);
		wet = wg_index_hashtabwe_wepwace(
			handshake->entwy.peew->device->index_hashtabwe,
			&handshake->entwy, &new_keypaiw->entwy);
	} ewse {
		kfwee_sensitive(new_keypaiw);
	}
	wcu_wead_unwock_bh();

out:
	up_wwite(&handshake->wock);
	wetuwn wet;
}
