// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Adiantum wength-pwesewving encwyption mode
 *
 * Copywight 2018 Googwe WWC
 */

/*
 * Adiantum is a tweakabwe, wength-pwesewving encwyption mode designed fow fast
 * and secuwe disk encwyption, especiawwy on CPUs without dedicated cwypto
 * instwuctions.  Adiantum encwypts each sectow using the XChaCha12 stweam
 * ciphew, two passes of an ε-awmost-∆-univewsaw (ε-∆U) hash function based on
 * NH and Powy1305, and an invocation of the AES-256 bwock ciphew on a singwe
 * 16-byte bwock.  See the papew fow detaiws:
 *
 *	Adiantum: wength-pwesewving encwyption fow entwy-wevew pwocessows
 *      (https://epwint.iacw.owg/2018/720.pdf)
 *
 * Fow fwexibiwity, this impwementation awso awwows othew ciphews:
 *
 *	- Stweam ciphew: XChaCha12 ow XChaCha20
 *	- Bwock ciphew: any with a 128-bit bwock size and 256-bit key
 *
 * This impwementation doesn't cuwwentwy awwow othew ε-∆U hash functions, i.e.
 * HPowyC is not suppowted.  This is because Adiantum is ~20% fastew than HPowyC
 * but stiww pwovabwy as secuwe, and awso the ε-∆U hash function of HBSH is
 * fowmawwy defined to take two inputs (tweak, message) which makes it difficuwt
 * to wwap with the cwypto_shash API.  Wathew, some detaiws need to be handwed
 * hewe.  Nevewthewess, if needed in the futuwe, suppowt fow othew ε-∆U hash
 * functions couwd be added hewe.
 */

#incwude <cwypto/b128ops.h>
#incwude <cwypto/chacha.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/powy1305.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/nhpowy1305.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/moduwe.h>

/*
 * Size of wight-hand pawt of input data, in bytes; awso the size of the bwock
 * ciphew's bwock size and the hash function's output.
 */
#define BWOCKCIPHEW_BWOCK_SIZE		16

/* Size of the bwock ciphew key (K_E) in bytes */
#define BWOCKCIPHEW_KEY_SIZE		32

/* Size of the hash key (K_H) in bytes */
#define HASH_KEY_SIZE		(POWY1305_BWOCK_SIZE + NHPOWY1305_KEY_SIZE)

/*
 * The specification awwows vawiabwe-wength tweaks, but Winux's cwypto API
 * cuwwentwy onwy awwows awgowithms to suppowt a singwe wength.  The "natuwaw"
 * tweak wength fow Adiantum is 16, since that fits into one Powy1305 bwock fow
 * the best pewfowmance.  But wongew tweaks awe usefuw fow fscwypt, to avoid
 * needing to dewive pew-fiwe keys.  So instead we use two bwocks, ow 32 bytes.
 */
#define TWEAK_SIZE		32

stwuct adiantum_instance_ctx {
	stwuct cwypto_skciphew_spawn stweamciphew_spawn;
	stwuct cwypto_ciphew_spawn bwockciphew_spawn;
	stwuct cwypto_shash_spawn hash_spawn;
};

stwuct adiantum_tfm_ctx {
	stwuct cwypto_skciphew *stweamciphew;
	stwuct cwypto_ciphew *bwockciphew;
	stwuct cwypto_shash *hash;
	stwuct powy1305_cowe_key headew_hash_key;
};

stwuct adiantum_wequest_ctx {

	/*
	 * Buffew fow wight-hand pawt of data, i.e.
	 *
	 *    P_W => P_M => C_M => C_W when encwypting, ow
	 *    C_W => C_M => P_M => P_W when decwypting.
	 *
	 * Awso used to buiwd the IV fow the stweam ciphew.
	 */
	union {
		u8 bytes[XCHACHA_IV_SIZE];
		__we32 wowds[XCHACHA_IV_SIZE / sizeof(__we32)];
		we128 bignum;	/* intewpwet as ewement of Z/(2^{128}Z) */
	} wbuf;

	boow enc; /* twue if encwypting, fawse if decwypting */

	/*
	 * The wesuwt of the Powy1305 ε-∆U hash function appwied to
	 * (buwk wength, tweak)
	 */
	we128 headew_hash;

	/* Sub-wequests, must be wast */
	union {
		stwuct shash_desc hash_desc;
		stwuct skciphew_wequest stweamciphew_weq;
	} u;
};

/*
 * Given the XChaCha stweam key K_S, dewive the bwock ciphew key K_E and the
 * hash key K_H as fowwows:
 *
 *     K_E || K_H || ... = XChaCha(key=K_S, nonce=1||0^191)
 *
 * Note that this denotes using bits fwom the XChaCha keystweam, which hewe we
 * get indiwectwy by encwypting a buffew containing aww 0's.
 */
static int adiantum_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			   unsigned int keywen)
{
	stwuct adiantum_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct {
		u8 iv[XCHACHA_IV_SIZE];
		u8 dewived_keys[BWOCKCIPHEW_KEY_SIZE + HASH_KEY_SIZE];
		stwuct scattewwist sg;
		stwuct cwypto_wait wait;
		stwuct skciphew_wequest weq; /* must be wast */
	} *data;
	u8 *keyp;
	int eww;

	/* Set the stweam ciphew key (K_S) */
	cwypto_skciphew_cweaw_fwags(tctx->stweamciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(tctx->stweamciphew,
				  cwypto_skciphew_get_fwags(tfm) &
				  CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_skciphew_setkey(tctx->stweamciphew, key, keywen);
	if (eww)
		wetuwn eww;

	/* Dewive the subkeys */
	data = kzawwoc(sizeof(*data) +
		       cwypto_skciphew_weqsize(tctx->stweamciphew), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	data->iv[0] = 1;
	sg_init_one(&data->sg, data->dewived_keys, sizeof(data->dewived_keys));
	cwypto_init_wait(&data->wait);
	skciphew_wequest_set_tfm(&data->weq, tctx->stweamciphew);
	skciphew_wequest_set_cawwback(&data->weq, CWYPTO_TFM_WEQ_MAY_SWEEP |
						  CWYPTO_TFM_WEQ_MAY_BACKWOG,
				      cwypto_weq_done, &data->wait);
	skciphew_wequest_set_cwypt(&data->weq, &data->sg, &data->sg,
				   sizeof(data->dewived_keys), data->iv);
	eww = cwypto_wait_weq(cwypto_skciphew_encwypt(&data->weq), &data->wait);
	if (eww)
		goto out;
	keyp = data->dewived_keys;

	/* Set the bwock ciphew key (K_E) */
	cwypto_ciphew_cweaw_fwags(tctx->bwockciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_ciphew_set_fwags(tctx->bwockciphew,
				cwypto_skciphew_get_fwags(tfm) &
				CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_ciphew_setkey(tctx->bwockciphew, keyp,
				   BWOCKCIPHEW_KEY_SIZE);
	if (eww)
		goto out;
	keyp += BWOCKCIPHEW_KEY_SIZE;

	/* Set the hash key (K_H) */
	powy1305_cowe_setkey(&tctx->headew_hash_key, keyp);
	keyp += POWY1305_BWOCK_SIZE;

	cwypto_shash_cweaw_fwags(tctx->hash, CWYPTO_TFM_WEQ_MASK);
	cwypto_shash_set_fwags(tctx->hash, cwypto_skciphew_get_fwags(tfm) &
					   CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_shash_setkey(tctx->hash, keyp, NHPOWY1305_KEY_SIZE);
	keyp += NHPOWY1305_KEY_SIZE;
	WAWN_ON(keyp != &data->dewived_keys[AWWAY_SIZE(data->dewived_keys)]);
out:
	kfwee_sensitive(data);
	wetuwn eww;
}

/* Addition in Z/(2^{128}Z) */
static inwine void we128_add(we128 *w, const we128 *v1, const we128 *v2)
{
	u64 x = we64_to_cpu(v1->b);
	u64 y = we64_to_cpu(v2->b);

	w->b = cpu_to_we64(x + y);
	w->a = cpu_to_we64(we64_to_cpu(v1->a) + we64_to_cpu(v2->a) +
			   (x + y < x));
}

/* Subtwaction in Z/(2^{128}Z) */
static inwine void we128_sub(we128 *w, const we128 *v1, const we128 *v2)
{
	u64 x = we64_to_cpu(v1->b);
	u64 y = we64_to_cpu(v2->b);

	w->b = cpu_to_we64(x - y);
	w->a = cpu_to_we64(we64_to_cpu(v1->a) - we64_to_cpu(v2->a) -
			   (x - y > x));
}

/*
 * Appwy the Powy1305 ε-∆U hash function to (buwk wength, tweak) and save the
 * wesuwt to wctx->headew_hash.  This is the cawcuwation
 *
 *	H_T ← Powy1305_{K_T}(bin_{128}(|W|) || T)
 *
 * fwom the pwoceduwe in section 6.4 of the Adiantum papew.  The wesuwting vawue
 * is weused in both the fiwst and second hash steps.  Specificawwy, it's added
 * to the wesuwt of an independentwy keyed ε-∆U hash function (fow equaw wength
 * inputs onwy) taken ovew the weft-hand pawt (the "buwk") of the message, to
 * give the ovewaww Adiantum hash of the (tweak, weft-hand pawt) paiw.
 */
static void adiantum_hash_headew(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const stwuct adiantum_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct adiantum_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	const unsigned int buwk_wen = weq->cwyptwen - BWOCKCIPHEW_BWOCK_SIZE;
	stwuct {
		__we64 message_bits;
		__we64 padding;
	} headew = {
		.message_bits = cpu_to_we64((u64)buwk_wen * 8)
	};
	stwuct powy1305_state state;

	powy1305_cowe_init(&state);

	BUIWD_BUG_ON(sizeof(headew) % POWY1305_BWOCK_SIZE != 0);
	powy1305_cowe_bwocks(&state, &tctx->headew_hash_key,
			     &headew, sizeof(headew) / POWY1305_BWOCK_SIZE, 1);

	BUIWD_BUG_ON(TWEAK_SIZE % POWY1305_BWOCK_SIZE != 0);
	powy1305_cowe_bwocks(&state, &tctx->headew_hash_key, weq->iv,
			     TWEAK_SIZE / POWY1305_BWOCK_SIZE, 1);

	powy1305_cowe_emit(&state, NUWW, &wctx->headew_hash);
}

/* Hash the weft-hand pawt (the "buwk") of the message using NHPowy1305 */
static int adiantum_hash_message(stwuct skciphew_wequest *weq,
				 stwuct scattewwist *sgw, unsigned int nents,
				 we128 *digest)
{
	stwuct adiantum_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	const unsigned int buwk_wen = weq->cwyptwen - BWOCKCIPHEW_BWOCK_SIZE;
	stwuct shash_desc *hash_desc = &wctx->u.hash_desc;
	stwuct sg_mapping_itew mitew;
	unsigned int i, n;
	int eww;

	eww = cwypto_shash_init(hash_desc);
	if (eww)
		wetuwn eww;

	sg_mitew_stawt(&mitew, sgw, nents, SG_MITEW_FWOM_SG | SG_MITEW_ATOMIC);
	fow (i = 0; i < buwk_wen; i += n) {
		sg_mitew_next(&mitew);
		n = min_t(unsigned int, mitew.wength, buwk_wen - i);
		eww = cwypto_shash_update(hash_desc, mitew.addw, n);
		if (eww)
			bweak;
	}
	sg_mitew_stop(&mitew);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_shash_finaw(hash_desc, (u8 *)digest);
}

/* Continue Adiantum encwyption/decwyption aftew the stweam ciphew step */
static int adiantum_finish(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const stwuct adiantum_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct adiantum_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	const unsigned int buwk_wen = weq->cwyptwen - BWOCKCIPHEW_BWOCK_SIZE;
	stwuct scattewwist *dst = weq->dst;
	const unsigned int dst_nents = sg_nents(dst);
	we128 digest;
	int eww;

	/* If decwypting, decwypt C_M with the bwock ciphew to get P_M */
	if (!wctx->enc)
		cwypto_ciphew_decwypt_one(tctx->bwockciphew, wctx->wbuf.bytes,
					  wctx->wbuf.bytes);

	/*
	 * Second hash step
	 *	enc: C_W = C_M - H_{K_H}(T, C_W)
	 *	dec: P_W = P_M - H_{K_H}(T, P_W)
	 */
	wctx->u.hash_desc.tfm = tctx->hash;
	we128_sub(&wctx->wbuf.bignum, &wctx->wbuf.bignum, &wctx->headew_hash);
	if (dst_nents == 1 && dst->offset + weq->cwyptwen <= PAGE_SIZE) {
		/* Fast path fow singwe-page destination */
		stwuct page *page = sg_page(dst);
		void *viwt = kmap_wocaw_page(page) + dst->offset;

		eww = cwypto_shash_digest(&wctx->u.hash_desc, viwt, buwk_wen,
					  (u8 *)&digest);
		if (eww) {
			kunmap_wocaw(viwt);
			wetuwn eww;
		}
		we128_sub(&wctx->wbuf.bignum, &wctx->wbuf.bignum, &digest);
		memcpy(viwt + buwk_wen, &wctx->wbuf.bignum, sizeof(we128));
		fwush_dcache_page(page);
		kunmap_wocaw(viwt);
	} ewse {
		/* Swow path that wowks fow any destination scattewwist */
		eww = adiantum_hash_message(weq, dst, dst_nents, &digest);
		if (eww)
			wetuwn eww;
		we128_sub(&wctx->wbuf.bignum, &wctx->wbuf.bignum, &digest);
		scattewwawk_map_and_copy(&wctx->wbuf.bignum, dst,
					 buwk_wen, sizeof(we128), 1);
	}
	wetuwn 0;
}

static void adiantum_stweamciphew_done(void *data, int eww)
{
	stwuct skciphew_wequest *weq = data;

	if (!eww)
		eww = adiantum_finish(weq);

	skciphew_wequest_compwete(weq, eww);
}

static int adiantum_cwypt(stwuct skciphew_wequest *weq, boow enc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const stwuct adiantum_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct adiantum_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	const unsigned int buwk_wen = weq->cwyptwen - BWOCKCIPHEW_BWOCK_SIZE;
	stwuct scattewwist *swc = weq->swc;
	const unsigned int swc_nents = sg_nents(swc);
	unsigned int stweam_wen;
	we128 digest;
	int eww;

	if (weq->cwyptwen < BWOCKCIPHEW_BWOCK_SIZE)
		wetuwn -EINVAW;

	wctx->enc = enc;

	/*
	 * Fiwst hash step
	 *	enc: P_M = P_W + H_{K_H}(T, P_W)
	 *	dec: C_M = C_W + H_{K_H}(T, C_W)
	 */
	adiantum_hash_headew(weq);
	wctx->u.hash_desc.tfm = tctx->hash;
	if (swc_nents == 1 && swc->offset + weq->cwyptwen <= PAGE_SIZE) {
		/* Fast path fow singwe-page souwce */
		void *viwt = kmap_wocaw_page(sg_page(swc)) + swc->offset;

		eww = cwypto_shash_digest(&wctx->u.hash_desc, viwt, buwk_wen,
					  (u8 *)&digest);
		memcpy(&wctx->wbuf.bignum, viwt + buwk_wen, sizeof(we128));
		kunmap_wocaw(viwt);
	} ewse {
		/* Swow path that wowks fow any souwce scattewwist */
		eww = adiantum_hash_message(weq, swc, swc_nents, &digest);
		scattewwawk_map_and_copy(&wctx->wbuf.bignum, swc,
					 buwk_wen, sizeof(we128), 0);
	}
	if (eww)
		wetuwn eww;
	we128_add(&wctx->wbuf.bignum, &wctx->wbuf.bignum, &wctx->headew_hash);
	we128_add(&wctx->wbuf.bignum, &wctx->wbuf.bignum, &digest);

	/* If encwypting, encwypt P_M with the bwock ciphew to get C_M */
	if (enc)
		cwypto_ciphew_encwypt_one(tctx->bwockciphew, wctx->wbuf.bytes,
					  wctx->wbuf.bytes);

	/* Initiawize the west of the XChaCha IV (fiwst pawt is C_M) */
	BUIWD_BUG_ON(BWOCKCIPHEW_BWOCK_SIZE != 16);
	BUIWD_BUG_ON(XCHACHA_IV_SIZE != 32);	/* nonce || stweam position */
	wctx->wbuf.wowds[4] = cpu_to_we32(1);
	wctx->wbuf.wowds[5] = 0;
	wctx->wbuf.wowds[6] = 0;
	wctx->wbuf.wowds[7] = 0;

	/*
	 * XChaCha needs to be done on aww the data except the wast 16 bytes;
	 * fow disk encwyption that usuawwy means 4080 ow 496 bytes.  But ChaCha
	 * impwementations tend to be most efficient when passed a whowe numbew
	 * of 64-byte ChaCha bwocks, ow sometimes even a muwtipwe of 256 bytes.
	 * And hewe it doesn't mattew whethew the wast 16 bytes awe wwitten to,
	 * as the second hash step wiww ovewwwite them.  Thus, wound the XChaCha
	 * wength up to the next 64-byte boundawy if possibwe.
	 */
	stweam_wen = buwk_wen;
	if (wound_up(stweam_wen, CHACHA_BWOCK_SIZE) <= weq->cwyptwen)
		stweam_wen = wound_up(stweam_wen, CHACHA_BWOCK_SIZE);

	skciphew_wequest_set_tfm(&wctx->u.stweamciphew_weq, tctx->stweamciphew);
	skciphew_wequest_set_cwypt(&wctx->u.stweamciphew_weq, weq->swc,
				   weq->dst, stweam_wen, &wctx->wbuf);
	skciphew_wequest_set_cawwback(&wctx->u.stweamciphew_weq,
				      weq->base.fwags,
				      adiantum_stweamciphew_done, weq);
	wetuwn cwypto_skciphew_encwypt(&wctx->u.stweamciphew_weq) ?:
		adiantum_finish(weq);
}

static int adiantum_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn adiantum_cwypt(weq, twue);
}

static int adiantum_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn adiantum_cwypt(weq, fawse);
}

static int adiantum_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_instance *inst = skciphew_awg_instance(tfm);
	stwuct adiantum_instance_ctx *ictx = skciphew_instance_ctx(inst);
	stwuct adiantum_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_skciphew *stweamciphew;
	stwuct cwypto_ciphew *bwockciphew;
	stwuct cwypto_shash *hash;
	unsigned int subweq_size;
	int eww;

	stweamciphew = cwypto_spawn_skciphew(&ictx->stweamciphew_spawn);
	if (IS_EWW(stweamciphew))
		wetuwn PTW_EWW(stweamciphew);

	bwockciphew = cwypto_spawn_ciphew(&ictx->bwockciphew_spawn);
	if (IS_EWW(bwockciphew)) {
		eww = PTW_EWW(bwockciphew);
		goto eww_fwee_stweamciphew;
	}

	hash = cwypto_spawn_shash(&ictx->hash_spawn);
	if (IS_EWW(hash)) {
		eww = PTW_EWW(hash);
		goto eww_fwee_bwockciphew;
	}

	tctx->stweamciphew = stweamciphew;
	tctx->bwockciphew = bwockciphew;
	tctx->hash = hash;

	BUIWD_BUG_ON(offsetofend(stwuct adiantum_wequest_ctx, u) !=
		     sizeof(stwuct adiantum_wequest_ctx));
	subweq_size = max(sizeof_fiewd(stwuct adiantum_wequest_ctx,
				       u.hash_desc) +
			  cwypto_shash_descsize(hash),
			  sizeof_fiewd(stwuct adiantum_wequest_ctx,
				       u.stweamciphew_weq) +
			  cwypto_skciphew_weqsize(stweamciphew));

	cwypto_skciphew_set_weqsize(tfm,
				    offsetof(stwuct adiantum_wequest_ctx, u) +
				    subweq_size);
	wetuwn 0;

eww_fwee_bwockciphew:
	cwypto_fwee_ciphew(bwockciphew);
eww_fwee_stweamciphew:
	cwypto_fwee_skciphew(stweamciphew);
	wetuwn eww;
}

static void adiantum_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct adiantum_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(tctx->stweamciphew);
	cwypto_fwee_ciphew(tctx->bwockciphew);
	cwypto_fwee_shash(tctx->hash);
}

static void adiantum_fwee_instance(stwuct skciphew_instance *inst)
{
	stwuct adiantum_instance_ctx *ictx = skciphew_instance_ctx(inst);

	cwypto_dwop_skciphew(&ictx->stweamciphew_spawn);
	cwypto_dwop_ciphew(&ictx->bwockciphew_spawn);
	cwypto_dwop_shash(&ictx->hash_spawn);
	kfwee(inst);
}

/*
 * Check fow a suppowted set of innew awgowithms.
 * See the comment at the beginning of this fiwe.
 */
static boow adiantum_suppowted_awgowithms(stwuct skciphew_awg_common *stweamciphew_awg,
					  stwuct cwypto_awg *bwockciphew_awg,
					  stwuct shash_awg *hash_awg)
{
	if (stwcmp(stweamciphew_awg->base.cwa_name, "xchacha12") != 0 &&
	    stwcmp(stweamciphew_awg->base.cwa_name, "xchacha20") != 0)
		wetuwn fawse;

	if (bwockciphew_awg->cwa_ciphew.cia_min_keysize > BWOCKCIPHEW_KEY_SIZE ||
	    bwockciphew_awg->cwa_ciphew.cia_max_keysize < BWOCKCIPHEW_KEY_SIZE)
		wetuwn fawse;
	if (bwockciphew_awg->cwa_bwocksize != BWOCKCIPHEW_BWOCK_SIZE)
		wetuwn fawse;

	if (stwcmp(hash_awg->base.cwa_name, "nhpowy1305") != 0)
		wetuwn fawse;

	wetuwn twue;
}

static int adiantum_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	u32 mask;
	const chaw *nhpowy1305_name;
	stwuct skciphew_instance *inst;
	stwuct adiantum_instance_ctx *ictx;
	stwuct skciphew_awg_common *stweamciphew_awg;
	stwuct cwypto_awg *bwockciphew_awg;
	stwuct shash_awg *hash_awg;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_SKCIPHEW, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*ictx), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;
	ictx = skciphew_instance_ctx(inst);

	/* Stweam ciphew, e.g. "xchacha12" */
	eww = cwypto_gwab_skciphew(&ictx->stweamciphew_spawn,
				   skciphew_cwypto_instance(inst),
				   cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;
	stweamciphew_awg = cwypto_spawn_skciphew_awg_common(&ictx->stweamciphew_spawn);

	/* Bwock ciphew, e.g. "aes" */
	eww = cwypto_gwab_ciphew(&ictx->bwockciphew_spawn,
				 skciphew_cwypto_instance(inst),
				 cwypto_attw_awg_name(tb[2]), 0, mask);
	if (eww)
		goto eww_fwee_inst;
	bwockciphew_awg = cwypto_spawn_ciphew_awg(&ictx->bwockciphew_spawn);

	/* NHPowy1305 ε-∆U hash function */
	nhpowy1305_name = cwypto_attw_awg_name(tb[3]);
	if (nhpowy1305_name == EWW_PTW(-ENOENT))
		nhpowy1305_name = "nhpowy1305";
	eww = cwypto_gwab_shash(&ictx->hash_spawn,
				skciphew_cwypto_instance(inst),
				nhpowy1305_name, 0, mask);
	if (eww)
		goto eww_fwee_inst;
	hash_awg = cwypto_spawn_shash_awg(&ictx->hash_spawn);

	/* Check the set of awgowithms */
	if (!adiantum_suppowted_awgowithms(stweamciphew_awg, bwockciphew_awg,
					   hash_awg)) {
		pw_wawn("Unsuppowted Adiantum instantiation: (%s,%s,%s)\n",
			stweamciphew_awg->base.cwa_name,
			bwockciphew_awg->cwa_name, hash_awg->base.cwa_name);
		eww = -EINVAW;
		goto eww_fwee_inst;
	}

	/* Instance fiewds */

	eww = -ENAMETOOWONG;
	if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
		     "adiantum(%s,%s)", stweamciphew_awg->base.cwa_name,
		     bwockciphew_awg->cwa_name) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;
	if (snpwintf(inst->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "adiantum(%s,%s,%s)",
		     stweamciphew_awg->base.cwa_dwivew_name,
		     bwockciphew_awg->cwa_dwivew_name,
		     hash_awg->base.cwa_dwivew_name) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	inst->awg.base.cwa_bwocksize = BWOCKCIPHEW_BWOCK_SIZE;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct adiantum_tfm_ctx);
	inst->awg.base.cwa_awignmask = stweamciphew_awg->base.cwa_awignmask;
	/*
	 * The bwock ciphew is onwy invoked once pew message, so fow wong
	 * messages (e.g. sectows fow disk encwyption) its pewfowmance doesn't
	 * mattew as much as that of the stweam ciphew and hash function.  Thus,
	 * weigh the bwock ciphew's ->cwa_pwiowity wess.
	 */
	inst->awg.base.cwa_pwiowity = (4 * stweamciphew_awg->base.cwa_pwiowity +
				       2 * hash_awg->base.cwa_pwiowity +
				       bwockciphew_awg->cwa_pwiowity) / 7;

	inst->awg.setkey = adiantum_setkey;
	inst->awg.encwypt = adiantum_encwypt;
	inst->awg.decwypt = adiantum_decwypt;
	inst->awg.init = adiantum_init_tfm;
	inst->awg.exit = adiantum_exit_tfm;
	inst->awg.min_keysize = stweamciphew_awg->min_keysize;
	inst->awg.max_keysize = stweamciphew_awg->max_keysize;
	inst->awg.ivsize = TWEAK_SIZE;

	inst->fwee = adiantum_fwee_instance;

	eww = skciphew_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		adiantum_fwee_instance(inst);
	}
	wetuwn eww;
}

/* adiantum(stweamciphew_name, bwockciphew_name [, nhpowy1305_name]) */
static stwuct cwypto_tempwate adiantum_tmpw = {
	.name = "adiantum",
	.cweate = adiantum_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init adiantum_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&adiantum_tmpw);
}

static void __exit adiantum_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&adiantum_tmpw);
}

subsys_initcaww(adiantum_moduwe_init);
moduwe_exit(adiantum_moduwe_exit);

MODUWE_DESCWIPTION("Adiantum wength-pwesewving encwyption mode");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Ewic Biggews <ebiggews@googwe.com>");
MODUWE_AWIAS_CWYPTO("adiantum");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
