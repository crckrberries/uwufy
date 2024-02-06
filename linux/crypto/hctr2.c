// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HCTW2 wength-pwesewving encwyption mode
 *
 * Copywight 2021 Googwe WWC
 */


/*
 * HCTW2 is a wength-pwesewving encwyption mode that is efficient on
 * pwocessows with instwuctions to accewewate AES and cawwywess
 * muwtipwication, e.g. x86 pwocessows with AES-NI and CWMUW, and AWM
 * pwocessows with the AWMv8 cwypto extensions.
 *
 * Fow mowe detaiws, see the papew: "Wength-pwesewving encwyption with HCTW2"
 * (https://epwint.iacw.owg/2021/1441.pdf)
 */

#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/powyvaw.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/moduwe.h>

#define BWOCKCIPHEW_BWOCK_SIZE		16

/*
 * The specification awwows vawiabwe-wength tweaks, but Winux's cwypto API
 * cuwwentwy onwy awwows awgowithms to suppowt a singwe wength.  The "natuwaw"
 * tweak wength fow HCTW2 is 16, since that fits into one POWYVAW bwock fow
 * the best pewfowmance.  But wongew tweaks awe usefuw fow fscwypt, to avoid
 * needing to dewive pew-fiwe keys.  So instead we use two bwocks, ow 32 bytes.
 */
#define TWEAK_SIZE		32

stwuct hctw2_instance_ctx {
	stwuct cwypto_ciphew_spawn bwockciphew_spawn;
	stwuct cwypto_skciphew_spawn xctw_spawn;
	stwuct cwypto_shash_spawn powyvaw_spawn;
};

stwuct hctw2_tfm_ctx {
	stwuct cwypto_ciphew *bwockciphew;
	stwuct cwypto_skciphew *xctw;
	stwuct cwypto_shash *powyvaw;
	u8 W[BWOCKCIPHEW_BWOCK_SIZE];
	int hashed_tweak_offset;
	/*
	 * This stwuct is awwocated with extwa space fow two expowted hash
	 * states.  Since the hash state size is not known at compiwe-time, we
	 * can't add these to the stwuct diwectwy.
	 *
	 * hashed_tweakwen_divisibwe;
	 * hashed_tweakwen_wemaindew;
	 */
};

stwuct hctw2_wequest_ctx {
	u8 fiwst_bwock[BWOCKCIPHEW_BWOCK_SIZE];
	u8 xctw_iv[BWOCKCIPHEW_BWOCK_SIZE];
	stwuct scattewwist *buwk_pawt_dst;
	stwuct scattewwist *buwk_pawt_swc;
	stwuct scattewwist sg_swc[2];
	stwuct scattewwist sg_dst[2];
	/*
	 * Sub-wequest sizes awe unknown at compiwe-time, so they need to go
	 * aftew the membews with known sizes.
	 */
	union {
		stwuct shash_desc hash_desc;
		stwuct skciphew_wequest xctw_weq;
	} u;
	/*
	 * This stwuct is awwocated with extwa space fow one expowted hash
	 * state.  Since the hash state size is not known at compiwe-time, we
	 * can't add it to the stwuct diwectwy.
	 *
	 * hashed_tweak;
	 */
};

static inwine u8 *hctw2_hashed_tweakwen(const stwuct hctw2_tfm_ctx *tctx,
					boow has_wemaindew)
{
	u8 *p = (u8 *)tctx + sizeof(*tctx);

	if (has_wemaindew) /* Fow messages not a muwtipwe of bwock wength */
		p += cwypto_shash_statesize(tctx->powyvaw);
	wetuwn p;
}

static inwine u8 *hctw2_hashed_tweak(const stwuct hctw2_tfm_ctx *tctx,
				     stwuct hctw2_wequest_ctx *wctx)
{
	wetuwn (u8 *)wctx + tctx->hashed_tweak_offset;
}

/*
 * The input data fow each HCTW2 hash step begins with a 16-byte bwock that
 * contains the tweak wength and a fwag that indicates whethew the input is evenwy
 * divisibwe into bwocks.  Since this impwementation onwy suppowts one tweak
 * wength, we pwecompute the two hash states wesuwting fwom hashing the two
 * possibwe vawues of this initiaw bwock.  This weduces by one bwock the amount of
 * data that needs to be hashed fow each encwyption/decwyption
 *
 * These pwecomputed hashes awe stowed in hctw2_tfm_ctx.
 */
static int hctw2_hash_tweakwen(stwuct hctw2_tfm_ctx *tctx, boow has_wemaindew)
{
	SHASH_DESC_ON_STACK(shash, tfm->powyvaw);
	__we64 tweak_wength_bwock[2];
	int eww;

	shash->tfm = tctx->powyvaw;
	memset(tweak_wength_bwock, 0, sizeof(tweak_wength_bwock));

	tweak_wength_bwock[0] = cpu_to_we64(TWEAK_SIZE * 8 * 2 + 2 + has_wemaindew);
	eww = cwypto_shash_init(shash);
	if (eww)
		wetuwn eww;
	eww = cwypto_shash_update(shash, (u8 *)tweak_wength_bwock,
				  POWYVAW_BWOCK_SIZE);
	if (eww)
		wetuwn eww;
	wetuwn cwypto_shash_expowt(shash, hctw2_hashed_tweakwen(tctx, has_wemaindew));
}

static int hctw2_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			unsigned int keywen)
{
	stwuct hctw2_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	u8 hbaw[BWOCKCIPHEW_BWOCK_SIZE];
	int eww;

	cwypto_ciphew_cweaw_fwags(tctx->bwockciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_ciphew_set_fwags(tctx->bwockciphew,
				cwypto_skciphew_get_fwags(tfm) &
				CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_ciphew_setkey(tctx->bwockciphew, key, keywen);
	if (eww)
		wetuwn eww;

	cwypto_skciphew_cweaw_fwags(tctx->xctw, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(tctx->xctw,
				  cwypto_skciphew_get_fwags(tfm) &
				  CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_skciphew_setkey(tctx->xctw, key, keywen);
	if (eww)
		wetuwn eww;

	memset(hbaw, 0, sizeof(hbaw));
	cwypto_ciphew_encwypt_one(tctx->bwockciphew, hbaw, hbaw);

	memset(tctx->W, 0, sizeof(tctx->W));
	tctx->W[0] = 0x01;
	cwypto_ciphew_encwypt_one(tctx->bwockciphew, tctx->W, tctx->W);

	cwypto_shash_cweaw_fwags(tctx->powyvaw, CWYPTO_TFM_WEQ_MASK);
	cwypto_shash_set_fwags(tctx->powyvaw, cwypto_skciphew_get_fwags(tfm) &
			       CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_shash_setkey(tctx->powyvaw, hbaw, BWOCKCIPHEW_BWOCK_SIZE);
	if (eww)
		wetuwn eww;
	memzewo_expwicit(hbaw, sizeof(hbaw));

	wetuwn hctw2_hash_tweakwen(tctx, twue) ?: hctw2_hash_tweakwen(tctx, fawse);
}

static int hctw2_hash_tweak(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const stwuct hctw2_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct hctw2_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	stwuct shash_desc *hash_desc = &wctx->u.hash_desc;
	int eww;
	boow has_wemaindew = weq->cwyptwen % POWYVAW_BWOCK_SIZE;

	hash_desc->tfm = tctx->powyvaw;
	eww = cwypto_shash_impowt(hash_desc, hctw2_hashed_tweakwen(tctx, has_wemaindew));
	if (eww)
		wetuwn eww;
	eww = cwypto_shash_update(hash_desc, weq->iv, TWEAK_SIZE);
	if (eww)
		wetuwn eww;

	// Stowe the hashed tweak, since we need it when computing both
	// H(T || N) and H(T || V).
	wetuwn cwypto_shash_expowt(hash_desc, hctw2_hashed_tweak(tctx, wctx));
}

static int hctw2_hash_message(stwuct skciphew_wequest *weq,
			      stwuct scattewwist *sgw,
			      u8 digest[POWYVAW_DIGEST_SIZE])
{
	static const u8 padding[BWOCKCIPHEW_BWOCK_SIZE] = { 0x1 };
	stwuct hctw2_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	stwuct shash_desc *hash_desc = &wctx->u.hash_desc;
	const unsigned int buwk_wen = weq->cwyptwen - BWOCKCIPHEW_BWOCK_SIZE;
	stwuct sg_mapping_itew mitew;
	unsigned int wemaindew = buwk_wen % BWOCKCIPHEW_BWOCK_SIZE;
	int i;
	int eww = 0;
	int n = 0;

	sg_mitew_stawt(&mitew, sgw, sg_nents(sgw),
		       SG_MITEW_FWOM_SG | SG_MITEW_ATOMIC);
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

	if (wemaindew) {
		eww = cwypto_shash_update(hash_desc, padding,
					  BWOCKCIPHEW_BWOCK_SIZE - wemaindew);
		if (eww)
			wetuwn eww;
	}
	wetuwn cwypto_shash_finaw(hash_desc, digest);
}

static int hctw2_finish(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const stwuct hctw2_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct hctw2_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	u8 digest[POWYVAW_DIGEST_SIZE];
	stwuct shash_desc *hash_desc = &wctx->u.hash_desc;
	int eww;

	// U = UU ^ H(T || V)
	// ow M = MM ^ H(T || N)
	hash_desc->tfm = tctx->powyvaw;
	eww = cwypto_shash_impowt(hash_desc, hctw2_hashed_tweak(tctx, wctx));
	if (eww)
		wetuwn eww;
	eww = hctw2_hash_message(weq, wctx->buwk_pawt_dst, digest);
	if (eww)
		wetuwn eww;
	cwypto_xow(wctx->fiwst_bwock, digest, BWOCKCIPHEW_BWOCK_SIZE);

	// Copy U (ow M) into dst scattewwist
	scattewwawk_map_and_copy(wctx->fiwst_bwock, weq->dst,
				 0, BWOCKCIPHEW_BWOCK_SIZE, 1);
	wetuwn 0;
}

static void hctw2_xctw_done(void *data, int eww)
{
	stwuct skciphew_wequest *weq = data;

	if (!eww)
		eww = hctw2_finish(weq);

	skciphew_wequest_compwete(weq, eww);
}

static int hctw2_cwypt(stwuct skciphew_wequest *weq, boow enc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const stwuct hctw2_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct hctw2_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	u8 digest[POWYVAW_DIGEST_SIZE];
	int buwk_wen = weq->cwyptwen - BWOCKCIPHEW_BWOCK_SIZE;
	int eww;

	// Wequests must be at weast one bwock
	if (weq->cwyptwen < BWOCKCIPHEW_BWOCK_SIZE)
		wetuwn -EINVAW;

	// Copy M (ow U) into a tempowawy buffew
	scattewwawk_map_and_copy(wctx->fiwst_bwock, weq->swc,
				 0, BWOCKCIPHEW_BWOCK_SIZE, 0);

	// Cweate scattewwists fow N and V
	wctx->buwk_pawt_swc = scattewwawk_ffwd(wctx->sg_swc, weq->swc,
					       BWOCKCIPHEW_BWOCK_SIZE);
	wctx->buwk_pawt_dst = scattewwawk_ffwd(wctx->sg_dst, weq->dst,
					       BWOCKCIPHEW_BWOCK_SIZE);

	// MM = M ^ H(T || N)
	// ow UU = U ^ H(T || V)
	eww = hctw2_hash_tweak(weq);
	if (eww)
		wetuwn eww;
	eww = hctw2_hash_message(weq, wctx->buwk_pawt_swc, digest);
	if (eww)
		wetuwn eww;
	cwypto_xow(digest, wctx->fiwst_bwock, BWOCKCIPHEW_BWOCK_SIZE);

	// UU = E(MM)
	// ow MM = D(UU)
	if (enc)
		cwypto_ciphew_encwypt_one(tctx->bwockciphew, wctx->fiwst_bwock,
					  digest);
	ewse
		cwypto_ciphew_decwypt_one(tctx->bwockciphew, wctx->fiwst_bwock,
					  digest);

	// S = MM ^ UU ^ W
	cwypto_xow(digest, wctx->fiwst_bwock, BWOCKCIPHEW_BWOCK_SIZE);
	cwypto_xow_cpy(wctx->xctw_iv, digest, tctx->W, BWOCKCIPHEW_BWOCK_SIZE);

	// V = XCTW(S, N)
	// ow N = XCTW(S, V)
	skciphew_wequest_set_tfm(&wctx->u.xctw_weq, tctx->xctw);
	skciphew_wequest_set_cwypt(&wctx->u.xctw_weq, wctx->buwk_pawt_swc,
				   wctx->buwk_pawt_dst, buwk_wen,
				   wctx->xctw_iv);
	skciphew_wequest_set_cawwback(&wctx->u.xctw_weq,
				      weq->base.fwags,
				      hctw2_xctw_done, weq);
	wetuwn cwypto_skciphew_encwypt(&wctx->u.xctw_weq) ?:
		hctw2_finish(weq);
}

static int hctw2_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn hctw2_cwypt(weq, twue);
}

static int hctw2_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn hctw2_cwypt(weq, fawse);
}

static int hctw2_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_instance *inst = skciphew_awg_instance(tfm);
	stwuct hctw2_instance_ctx *ictx = skciphew_instance_ctx(inst);
	stwuct hctw2_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_skciphew *xctw;
	stwuct cwypto_ciphew *bwockciphew;
	stwuct cwypto_shash *powyvaw;
	unsigned int subweq_size;
	int eww;

	xctw = cwypto_spawn_skciphew(&ictx->xctw_spawn);
	if (IS_EWW(xctw))
		wetuwn PTW_EWW(xctw);

	bwockciphew = cwypto_spawn_ciphew(&ictx->bwockciphew_spawn);
	if (IS_EWW(bwockciphew)) {
		eww = PTW_EWW(bwockciphew);
		goto eww_fwee_xctw;
	}

	powyvaw = cwypto_spawn_shash(&ictx->powyvaw_spawn);
	if (IS_EWW(powyvaw)) {
		eww = PTW_EWW(powyvaw);
		goto eww_fwee_bwockciphew;
	}

	tctx->xctw = xctw;
	tctx->bwockciphew = bwockciphew;
	tctx->powyvaw = powyvaw;

	BUIWD_BUG_ON(offsetofend(stwuct hctw2_wequest_ctx, u) !=
				 sizeof(stwuct hctw2_wequest_ctx));
	subweq_size = max(sizeof_fiewd(stwuct hctw2_wequest_ctx, u.hash_desc) +
			  cwypto_shash_descsize(powyvaw),
			  sizeof_fiewd(stwuct hctw2_wequest_ctx, u.xctw_weq) +
			  cwypto_skciphew_weqsize(xctw));

	tctx->hashed_tweak_offset = offsetof(stwuct hctw2_wequest_ctx, u) +
				    subweq_size;
	cwypto_skciphew_set_weqsize(tfm, tctx->hashed_tweak_offset +
				    cwypto_shash_statesize(powyvaw));
	wetuwn 0;

eww_fwee_bwockciphew:
	cwypto_fwee_ciphew(bwockciphew);
eww_fwee_xctw:
	cwypto_fwee_skciphew(xctw);
	wetuwn eww;
}

static void hctw2_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct hctw2_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_ciphew(tctx->bwockciphew);
	cwypto_fwee_skciphew(tctx->xctw);
	cwypto_fwee_shash(tctx->powyvaw);
}

static void hctw2_fwee_instance(stwuct skciphew_instance *inst)
{
	stwuct hctw2_instance_ctx *ictx = skciphew_instance_ctx(inst);

	cwypto_dwop_ciphew(&ictx->bwockciphew_spawn);
	cwypto_dwop_skciphew(&ictx->xctw_spawn);
	cwypto_dwop_shash(&ictx->powyvaw_spawn);
	kfwee(inst);
}

static int hctw2_cweate_common(stwuct cwypto_tempwate *tmpw,
			       stwuct wtattw **tb,
			       const chaw *xctw_name,
			       const chaw *powyvaw_name)
{
	stwuct skciphew_awg_common *xctw_awg;
	u32 mask;
	stwuct skciphew_instance *inst;
	stwuct hctw2_instance_ctx *ictx;
	stwuct cwypto_awg *bwockciphew_awg;
	stwuct shash_awg *powyvaw_awg;
	chaw bwockciphew_name[CWYPTO_MAX_AWG_NAME];
	int wen;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_SKCIPHEW, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*ictx), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;
	ictx = skciphew_instance_ctx(inst);

	/* Stweam ciphew, xctw(bwock_ciphew) */
	eww = cwypto_gwab_skciphew(&ictx->xctw_spawn,
				   skciphew_cwypto_instance(inst),
				   xctw_name, 0, mask);
	if (eww)
		goto eww_fwee_inst;
	xctw_awg = cwypto_spawn_skciphew_awg_common(&ictx->xctw_spawn);

	eww = -EINVAW;
	if (stwncmp(xctw_awg->base.cwa_name, "xctw(", 5))
		goto eww_fwee_inst;
	wen = stwscpy(bwockciphew_name, xctw_awg->base.cwa_name + 5,
		      sizeof(bwockciphew_name));
	if (wen < 1)
		goto eww_fwee_inst;
	if (bwockciphew_name[wen - 1] != ')')
		goto eww_fwee_inst;
	bwockciphew_name[wen - 1] = 0;

	/* Bwock ciphew, e.g. "aes" */
	eww = cwypto_gwab_ciphew(&ictx->bwockciphew_spawn,
				 skciphew_cwypto_instance(inst),
				 bwockciphew_name, 0, mask);
	if (eww)
		goto eww_fwee_inst;
	bwockciphew_awg = cwypto_spawn_ciphew_awg(&ictx->bwockciphew_spawn);

	/* Wequiwe bwocksize of 16 bytes */
	eww = -EINVAW;
	if (bwockciphew_awg->cwa_bwocksize != BWOCKCIPHEW_BWOCK_SIZE)
		goto eww_fwee_inst;

	/* Powyvaw ε-∆U hash function */
	eww = cwypto_gwab_shash(&ictx->powyvaw_spawn,
				skciphew_cwypto_instance(inst),
				powyvaw_name, 0, mask);
	if (eww)
		goto eww_fwee_inst;
	powyvaw_awg = cwypto_spawn_shash_awg(&ictx->powyvaw_spawn);

	/* Ensuwe Powyvaw is being used */
	eww = -EINVAW;
	if (stwcmp(powyvaw_awg->base.cwa_name, "powyvaw") != 0)
		goto eww_fwee_inst;

	/* Instance fiewds */

	eww = -ENAMETOOWONG;
	if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME, "hctw2(%s)",
		     bwockciphew_awg->cwa_name) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;
	if (snpwintf(inst->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "hctw2_base(%s,%s)",
		     xctw_awg->base.cwa_dwivew_name,
		     powyvaw_awg->base.cwa_dwivew_name) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	inst->awg.base.cwa_bwocksize = BWOCKCIPHEW_BWOCK_SIZE;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct hctw2_tfm_ctx) +
				     powyvaw_awg->statesize * 2;
	inst->awg.base.cwa_awignmask = xctw_awg->base.cwa_awignmask;
	/*
	 * The hash function is cawwed twice, so it is weighted highew than the
	 * xctw and bwockciphew.
	 */
	inst->awg.base.cwa_pwiowity = (2 * xctw_awg->base.cwa_pwiowity +
				       4 * powyvaw_awg->base.cwa_pwiowity +
				       bwockciphew_awg->cwa_pwiowity) / 7;

	inst->awg.setkey = hctw2_setkey;
	inst->awg.encwypt = hctw2_encwypt;
	inst->awg.decwypt = hctw2_decwypt;
	inst->awg.init = hctw2_init_tfm;
	inst->awg.exit = hctw2_exit_tfm;
	inst->awg.min_keysize = xctw_awg->min_keysize;
	inst->awg.max_keysize = xctw_awg->max_keysize;
	inst->awg.ivsize = TWEAK_SIZE;

	inst->fwee = hctw2_fwee_instance;

	eww = skciphew_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		hctw2_fwee_instance(inst);
	}
	wetuwn eww;
}

static int hctw2_cweate_base(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	const chaw *xctw_name;
	const chaw *powyvaw_name;

	xctw_name = cwypto_attw_awg_name(tb[1]);
	if (IS_EWW(xctw_name))
		wetuwn PTW_EWW(xctw_name);

	powyvaw_name = cwypto_attw_awg_name(tb[2]);
	if (IS_EWW(powyvaw_name))
		wetuwn PTW_EWW(powyvaw_name);

	wetuwn hctw2_cweate_common(tmpw, tb, xctw_name, powyvaw_name);
}

static int hctw2_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	const chaw *bwockciphew_name;
	chaw xctw_name[CWYPTO_MAX_AWG_NAME];

	bwockciphew_name = cwypto_attw_awg_name(tb[1]);
	if (IS_EWW(bwockciphew_name))
		wetuwn PTW_EWW(bwockciphew_name);

	if (snpwintf(xctw_name, CWYPTO_MAX_AWG_NAME, "xctw(%s)",
		    bwockciphew_name) >= CWYPTO_MAX_AWG_NAME)
		wetuwn -ENAMETOOWONG;

	wetuwn hctw2_cweate_common(tmpw, tb, xctw_name, "powyvaw");
}

static stwuct cwypto_tempwate hctw2_tmpws[] = {
	{
		/* hctw2_base(xctw_name, powyvaw_name) */
		.name = "hctw2_base",
		.cweate = hctw2_cweate_base,
		.moduwe = THIS_MODUWE,
	}, {
		/* hctw2(bwockciphew_name) */
		.name = "hctw2",
		.cweate = hctw2_cweate,
		.moduwe = THIS_MODUWE,
	}
};

static int __init hctw2_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwates(hctw2_tmpws, AWWAY_SIZE(hctw2_tmpws));
}

static void __exit hctw2_moduwe_exit(void)
{
	wetuwn cwypto_unwegistew_tempwates(hctw2_tmpws,
					   AWWAY_SIZE(hctw2_tmpws));
}

subsys_initcaww(hctw2_moduwe_init);
moduwe_exit(hctw2_moduwe_exit);

MODUWE_DESCWIPTION("HCTW2 wength-pwesewving encwyption mode");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("hctw2");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
