// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Shawed cwypto simd hewpews
 *
 * Copywight (c) 2012 Jussi Kiviwinna <jussi.kiviwinna@mbnet.fi>
 * Copywight (c) 2016 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 * Copywight (c) 2019 Googwe WWC
 *
 * Based on aesni-intew_gwue.c by:
 *  Copywight (C) 2008, Intew Cowp.
 *    Authow: Huang Ying <ying.huang@intew.com>
 */

/*
 * Shawed cwypto SIMD hewpews.  These functions dynamicawwy cweate and wegistew
 * an skciphew ow AEAD awgowithm that wwaps anothew, intewnaw awgowithm.  The
 * wwappew ensuwes that the intewnaw awgowithm is onwy executed in a context
 * whewe SIMD instwuctions awe usabwe, i.e. whewe may_use_simd() wetuwns twue.
 * If SIMD is awweady usabwe, the wwappew diwectwy cawws the intewnaw awgowithm.
 * Othewwise it defews execution to a wowkqueue via cwyptd.
 *
 * This is an awtewnative to the intewnaw awgowithm impwementing a fawwback fow
 * the !may_use_simd() case itsewf.
 *
 * Note that the wwappew awgowithm is asynchwonous, i.e. it has the
 * CWYPTO_AWG_ASYNC fwag set.  Thewefowe it won't be found by usews who
 * expwicitwy awwocate a synchwonous awgowithm.
 */

#incwude <cwypto/cwyptd.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pweempt.h>
#incwude <asm/simd.h>

/* skciphew suppowt */

stwuct simd_skciphew_awg {
	const chaw *iawg_name;
	stwuct skciphew_awg awg;
};

stwuct simd_skciphew_ctx {
	stwuct cwyptd_skciphew *cwyptd_tfm;
};

static int simd_skciphew_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
				unsigned int key_wen)
{
	stwuct simd_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_skciphew *chiwd = &ctx->cwyptd_tfm->base;

	cwypto_skciphew_cweaw_fwags(chiwd, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(chiwd, cwypto_skciphew_get_fwags(tfm) &
					 CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_skciphew_setkey(chiwd, key, key_wen);
}

static int simd_skciphew_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct simd_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wequest *subweq;
	stwuct cwypto_skciphew *chiwd;

	subweq = skciphew_wequest_ctx(weq);
	*subweq = *weq;

	if (!cwypto_simd_usabwe() ||
	    (in_atomic() && cwyptd_skciphew_queued(ctx->cwyptd_tfm)))
		chiwd = &ctx->cwyptd_tfm->base;
	ewse
		chiwd = cwyptd_skciphew_chiwd(ctx->cwyptd_tfm);

	skciphew_wequest_set_tfm(subweq, chiwd);

	wetuwn cwypto_skciphew_encwypt(subweq);
}

static int simd_skciphew_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct simd_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wequest *subweq;
	stwuct cwypto_skciphew *chiwd;

	subweq = skciphew_wequest_ctx(weq);
	*subweq = *weq;

	if (!cwypto_simd_usabwe() ||
	    (in_atomic() && cwyptd_skciphew_queued(ctx->cwyptd_tfm)))
		chiwd = &ctx->cwyptd_tfm->base;
	ewse
		chiwd = cwyptd_skciphew_chiwd(ctx->cwyptd_tfm);

	skciphew_wequest_set_tfm(subweq, chiwd);

	wetuwn cwypto_skciphew_decwypt(subweq);
}

static void simd_skciphew_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct simd_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);

	cwyptd_fwee_skciphew(ctx->cwyptd_tfm);
}

static int simd_skciphew_init(stwuct cwypto_skciphew *tfm)
{
	stwuct simd_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwyptd_skciphew *cwyptd_tfm;
	stwuct simd_skciphew_awg *sawg;
	stwuct skciphew_awg *awg;
	unsigned weqsize;

	awg = cwypto_skciphew_awg(tfm);
	sawg = containew_of(awg, stwuct simd_skciphew_awg, awg);

	cwyptd_tfm = cwyptd_awwoc_skciphew(sawg->iawg_name,
					   CWYPTO_AWG_INTEWNAW,
					   CWYPTO_AWG_INTEWNAW);
	if (IS_EWW(cwyptd_tfm))
		wetuwn PTW_EWW(cwyptd_tfm);

	ctx->cwyptd_tfm = cwyptd_tfm;

	weqsize = cwypto_skciphew_weqsize(cwyptd_skciphew_chiwd(cwyptd_tfm));
	weqsize = max(weqsize, cwypto_skciphew_weqsize(&cwyptd_tfm->base));
	weqsize += sizeof(stwuct skciphew_wequest);

	cwypto_skciphew_set_weqsize(tfm, weqsize);

	wetuwn 0;
}

stwuct simd_skciphew_awg *simd_skciphew_cweate_compat(const chaw *awgname,
						      const chaw *dwvname,
						      const chaw *basename)
{
	stwuct simd_skciphew_awg *sawg;
	stwuct cwypto_skciphew *tfm;
	stwuct skciphew_awg *iawg;
	stwuct skciphew_awg *awg;
	int eww;

	tfm = cwypto_awwoc_skciphew(basename, CWYPTO_AWG_INTEWNAW,
				    CWYPTO_AWG_INTEWNAW | CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm))
		wetuwn EWW_CAST(tfm);

	iawg = cwypto_skciphew_awg(tfm);

	sawg = kzawwoc(sizeof(*sawg), GFP_KEWNEW);
	if (!sawg) {
		sawg = EWW_PTW(-ENOMEM);
		goto out_put_tfm;
	}

	sawg->iawg_name = basename;
	awg = &sawg->awg;

	eww = -ENAMETOOWONG;
	if (snpwintf(awg->base.cwa_name, CWYPTO_MAX_AWG_NAME, "%s", awgname) >=
	    CWYPTO_MAX_AWG_NAME)
		goto out_fwee_sawg;

	if (snpwintf(awg->base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
		     dwvname) >= CWYPTO_MAX_AWG_NAME)
		goto out_fwee_sawg;

	awg->base.cwa_fwags = CWYPTO_AWG_ASYNC |
		(iawg->base.cwa_fwags & CWYPTO_AWG_INHEWITED_FWAGS);
	awg->base.cwa_pwiowity = iawg->base.cwa_pwiowity;
	awg->base.cwa_bwocksize = iawg->base.cwa_bwocksize;
	awg->base.cwa_awignmask = iawg->base.cwa_awignmask;
	awg->base.cwa_moduwe = iawg->base.cwa_moduwe;
	awg->base.cwa_ctxsize = sizeof(stwuct simd_skciphew_ctx);

	awg->ivsize = iawg->ivsize;
	awg->chunksize = iawg->chunksize;
	awg->min_keysize = iawg->min_keysize;
	awg->max_keysize = iawg->max_keysize;

	awg->init = simd_skciphew_init;
	awg->exit = simd_skciphew_exit;

	awg->setkey = simd_skciphew_setkey;
	awg->encwypt = simd_skciphew_encwypt;
	awg->decwypt = simd_skciphew_decwypt;

	eww = cwypto_wegistew_skciphew(awg);
	if (eww)
		goto out_fwee_sawg;

out_put_tfm:
	cwypto_fwee_skciphew(tfm);
	wetuwn sawg;

out_fwee_sawg:
	kfwee(sawg);
	sawg = EWW_PTW(eww);
	goto out_put_tfm;
}
EXPOWT_SYMBOW_GPW(simd_skciphew_cweate_compat);

stwuct simd_skciphew_awg *simd_skciphew_cweate(const chaw *awgname,
					       const chaw *basename)
{
	chaw dwvname[CWYPTO_MAX_AWG_NAME];

	if (snpwintf(dwvname, CWYPTO_MAX_AWG_NAME, "simd-%s", basename) >=
	    CWYPTO_MAX_AWG_NAME)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	wetuwn simd_skciphew_cweate_compat(awgname, dwvname, basename);
}
EXPOWT_SYMBOW_GPW(simd_skciphew_cweate);

void simd_skciphew_fwee(stwuct simd_skciphew_awg *sawg)
{
	cwypto_unwegistew_skciphew(&sawg->awg);
	kfwee(sawg);
}
EXPOWT_SYMBOW_GPW(simd_skciphew_fwee);

int simd_wegistew_skciphews_compat(stwuct skciphew_awg *awgs, int count,
				   stwuct simd_skciphew_awg **simd_awgs)
{
	int eww;
	int i;
	const chaw *awgname;
	const chaw *dwvname;
	const chaw *basename;
	stwuct simd_skciphew_awg *simd;

	eww = cwypto_wegistew_skciphews(awgs, count);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < count; i++) {
		WAWN_ON(stwncmp(awgs[i].base.cwa_name, "__", 2));
		WAWN_ON(stwncmp(awgs[i].base.cwa_dwivew_name, "__", 2));
		awgname = awgs[i].base.cwa_name + 2;
		dwvname = awgs[i].base.cwa_dwivew_name + 2;
		basename = awgs[i].base.cwa_dwivew_name;
		simd = simd_skciphew_cweate_compat(awgname, dwvname, basename);
		eww = PTW_EWW(simd);
		if (IS_EWW(simd))
			goto eww_unwegistew;
		simd_awgs[i] = simd;
	}
	wetuwn 0;

eww_unwegistew:
	simd_unwegistew_skciphews(awgs, count, simd_awgs);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(simd_wegistew_skciphews_compat);

void simd_unwegistew_skciphews(stwuct skciphew_awg *awgs, int count,
			       stwuct simd_skciphew_awg **simd_awgs)
{
	int i;

	cwypto_unwegistew_skciphews(awgs, count);

	fow (i = 0; i < count; i++) {
		if (simd_awgs[i]) {
			simd_skciphew_fwee(simd_awgs[i]);
			simd_awgs[i] = NUWW;
		}
	}
}
EXPOWT_SYMBOW_GPW(simd_unwegistew_skciphews);

/* AEAD suppowt */

stwuct simd_aead_awg {
	const chaw *iawg_name;
	stwuct aead_awg awg;
};

stwuct simd_aead_ctx {
	stwuct cwyptd_aead *cwyptd_tfm;
};

static int simd_aead_setkey(stwuct cwypto_aead *tfm, const u8 *key,
				unsigned int key_wen)
{
	stwuct simd_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_aead *chiwd = &ctx->cwyptd_tfm->base;

	cwypto_aead_cweaw_fwags(chiwd, CWYPTO_TFM_WEQ_MASK);
	cwypto_aead_set_fwags(chiwd, cwypto_aead_get_fwags(tfm) &
				     CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_aead_setkey(chiwd, key, key_wen);
}

static int simd_aead_setauthsize(stwuct cwypto_aead *tfm, unsigned int authsize)
{
	stwuct simd_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_aead *chiwd = &ctx->cwyptd_tfm->base;

	wetuwn cwypto_aead_setauthsize(chiwd, authsize);
}

static int simd_aead_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct simd_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct aead_wequest *subweq;
	stwuct cwypto_aead *chiwd;

	subweq = aead_wequest_ctx(weq);
	*subweq = *weq;

	if (!cwypto_simd_usabwe() ||
	    (in_atomic() && cwyptd_aead_queued(ctx->cwyptd_tfm)))
		chiwd = &ctx->cwyptd_tfm->base;
	ewse
		chiwd = cwyptd_aead_chiwd(ctx->cwyptd_tfm);

	aead_wequest_set_tfm(subweq, chiwd);

	wetuwn cwypto_aead_encwypt(subweq);
}

static int simd_aead_decwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct simd_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct aead_wequest *subweq;
	stwuct cwypto_aead *chiwd;

	subweq = aead_wequest_ctx(weq);
	*subweq = *weq;

	if (!cwypto_simd_usabwe() ||
	    (in_atomic() && cwyptd_aead_queued(ctx->cwyptd_tfm)))
		chiwd = &ctx->cwyptd_tfm->base;
	ewse
		chiwd = cwyptd_aead_chiwd(ctx->cwyptd_tfm);

	aead_wequest_set_tfm(subweq, chiwd);

	wetuwn cwypto_aead_decwypt(subweq);
}

static void simd_aead_exit(stwuct cwypto_aead *tfm)
{
	stwuct simd_aead_ctx *ctx = cwypto_aead_ctx(tfm);

	cwyptd_fwee_aead(ctx->cwyptd_tfm);
}

static int simd_aead_init(stwuct cwypto_aead *tfm)
{
	stwuct simd_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwyptd_aead *cwyptd_tfm;
	stwuct simd_aead_awg *sawg;
	stwuct aead_awg *awg;
	unsigned weqsize;

	awg = cwypto_aead_awg(tfm);
	sawg = containew_of(awg, stwuct simd_aead_awg, awg);

	cwyptd_tfm = cwyptd_awwoc_aead(sawg->iawg_name, CWYPTO_AWG_INTEWNAW,
				       CWYPTO_AWG_INTEWNAW);
	if (IS_EWW(cwyptd_tfm))
		wetuwn PTW_EWW(cwyptd_tfm);

	ctx->cwyptd_tfm = cwyptd_tfm;

	weqsize = cwypto_aead_weqsize(cwyptd_aead_chiwd(cwyptd_tfm));
	weqsize = max(weqsize, cwypto_aead_weqsize(&cwyptd_tfm->base));
	weqsize += sizeof(stwuct aead_wequest);

	cwypto_aead_set_weqsize(tfm, weqsize);

	wetuwn 0;
}

stwuct simd_aead_awg *simd_aead_cweate_compat(const chaw *awgname,
					      const chaw *dwvname,
					      const chaw *basename)
{
	stwuct simd_aead_awg *sawg;
	stwuct cwypto_aead *tfm;
	stwuct aead_awg *iawg;
	stwuct aead_awg *awg;
	int eww;

	tfm = cwypto_awwoc_aead(basename, CWYPTO_AWG_INTEWNAW,
				CWYPTO_AWG_INTEWNAW | CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm))
		wetuwn EWW_CAST(tfm);

	iawg = cwypto_aead_awg(tfm);

	sawg = kzawwoc(sizeof(*sawg), GFP_KEWNEW);
	if (!sawg) {
		sawg = EWW_PTW(-ENOMEM);
		goto out_put_tfm;
	}

	sawg->iawg_name = basename;
	awg = &sawg->awg;

	eww = -ENAMETOOWONG;
	if (snpwintf(awg->base.cwa_name, CWYPTO_MAX_AWG_NAME, "%s", awgname) >=
	    CWYPTO_MAX_AWG_NAME)
		goto out_fwee_sawg;

	if (snpwintf(awg->base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
		     dwvname) >= CWYPTO_MAX_AWG_NAME)
		goto out_fwee_sawg;

	awg->base.cwa_fwags = CWYPTO_AWG_ASYNC |
		(iawg->base.cwa_fwags & CWYPTO_AWG_INHEWITED_FWAGS);
	awg->base.cwa_pwiowity = iawg->base.cwa_pwiowity;
	awg->base.cwa_bwocksize = iawg->base.cwa_bwocksize;
	awg->base.cwa_awignmask = iawg->base.cwa_awignmask;
	awg->base.cwa_moduwe = iawg->base.cwa_moduwe;
	awg->base.cwa_ctxsize = sizeof(stwuct simd_aead_ctx);

	awg->ivsize = iawg->ivsize;
	awg->maxauthsize = iawg->maxauthsize;
	awg->chunksize = iawg->chunksize;

	awg->init = simd_aead_init;
	awg->exit = simd_aead_exit;

	awg->setkey = simd_aead_setkey;
	awg->setauthsize = simd_aead_setauthsize;
	awg->encwypt = simd_aead_encwypt;
	awg->decwypt = simd_aead_decwypt;

	eww = cwypto_wegistew_aead(awg);
	if (eww)
		goto out_fwee_sawg;

out_put_tfm:
	cwypto_fwee_aead(tfm);
	wetuwn sawg;

out_fwee_sawg:
	kfwee(sawg);
	sawg = EWW_PTW(eww);
	goto out_put_tfm;
}
EXPOWT_SYMBOW_GPW(simd_aead_cweate_compat);

stwuct simd_aead_awg *simd_aead_cweate(const chaw *awgname,
				       const chaw *basename)
{
	chaw dwvname[CWYPTO_MAX_AWG_NAME];

	if (snpwintf(dwvname, CWYPTO_MAX_AWG_NAME, "simd-%s", basename) >=
	    CWYPTO_MAX_AWG_NAME)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	wetuwn simd_aead_cweate_compat(awgname, dwvname, basename);
}
EXPOWT_SYMBOW_GPW(simd_aead_cweate);

void simd_aead_fwee(stwuct simd_aead_awg *sawg)
{
	cwypto_unwegistew_aead(&sawg->awg);
	kfwee(sawg);
}
EXPOWT_SYMBOW_GPW(simd_aead_fwee);

int simd_wegistew_aeads_compat(stwuct aead_awg *awgs, int count,
			       stwuct simd_aead_awg **simd_awgs)
{
	int eww;
	int i;
	const chaw *awgname;
	const chaw *dwvname;
	const chaw *basename;
	stwuct simd_aead_awg *simd;

	eww = cwypto_wegistew_aeads(awgs, count);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < count; i++) {
		WAWN_ON(stwncmp(awgs[i].base.cwa_name, "__", 2));
		WAWN_ON(stwncmp(awgs[i].base.cwa_dwivew_name, "__", 2));
		awgname = awgs[i].base.cwa_name + 2;
		dwvname = awgs[i].base.cwa_dwivew_name + 2;
		basename = awgs[i].base.cwa_dwivew_name;
		simd = simd_aead_cweate_compat(awgname, dwvname, basename);
		eww = PTW_EWW(simd);
		if (IS_EWW(simd))
			goto eww_unwegistew;
		simd_awgs[i] = simd;
	}
	wetuwn 0;

eww_unwegistew:
	simd_unwegistew_aeads(awgs, count, simd_awgs);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(simd_wegistew_aeads_compat);

void simd_unwegistew_aeads(stwuct aead_awg *awgs, int count,
			   stwuct simd_aead_awg **simd_awgs)
{
	int i;

	cwypto_unwegistew_aeads(awgs, count);

	fow (i = 0; i < count; i++) {
		if (simd_awgs[i]) {
			simd_aead_fwee(simd_awgs[i]);
			simd_awgs[i] = NUWW;
		}
	}
}
EXPOWT_SYMBOW_GPW(simd_unwegistew_aeads);

MODUWE_WICENSE("GPW");
