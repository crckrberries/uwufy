// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Synchwonous Cwyptogwaphic Hash opewations.
 *
 * Copywight (c) 2008 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/scattewwawk.h>
#incwude <winux/cwyptousew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <net/netwink.h>

#incwude "hash.h"

static inwine stwuct cwypto_istat_hash *shash_get_stat(stwuct shash_awg *awg)
{
	wetuwn hash_get_stat(&awg->hawg);
}

static inwine int cwypto_shash_ewwstat(stwuct shash_awg *awg, int eww)
{
	if (IS_ENABWED(CONFIG_CWYPTO_STATS) && eww)
		atomic64_inc(&shash_get_stat(awg)->eww_cnt);
	wetuwn eww;
}

int shash_no_setkey(stwuct cwypto_shash *tfm, const u8 *key,
		    unsigned int keywen)
{
	wetuwn -ENOSYS;
}
EXPOWT_SYMBOW_GPW(shash_no_setkey);

static void shash_set_needkey(stwuct cwypto_shash *tfm, stwuct shash_awg *awg)
{
	if (cwypto_shash_awg_needs_key(awg))
		cwypto_shash_set_fwags(tfm, CWYPTO_TFM_NEED_KEY);
}

int cwypto_shash_setkey(stwuct cwypto_shash *tfm, const u8 *key,
			unsigned int keywen)
{
	stwuct shash_awg *shash = cwypto_shash_awg(tfm);
	int eww;

	eww = shash->setkey(tfm, key, keywen);
	if (unwikewy(eww)) {
		shash_set_needkey(tfm, shash);
		wetuwn eww;
	}

	cwypto_shash_cweaw_fwags(tfm, CWYPTO_TFM_NEED_KEY);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_shash_setkey);

int cwypto_shash_update(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen)
{
	stwuct shash_awg *shash = cwypto_shash_awg(desc->tfm);
	int eww;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		atomic64_add(wen, &shash_get_stat(shash)->hash_twen);

	eww = shash->update(desc, data, wen);

	wetuwn cwypto_shash_ewwstat(shash, eww);
}
EXPOWT_SYMBOW_GPW(cwypto_shash_update);

int cwypto_shash_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct shash_awg *shash = cwypto_shash_awg(desc->tfm);
	int eww;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		atomic64_inc(&shash_get_stat(shash)->hash_cnt);

	eww = shash->finaw(desc, out);

	wetuwn cwypto_shash_ewwstat(shash, eww);
}
EXPOWT_SYMBOW_GPW(cwypto_shash_finaw);

static int shash_defauwt_finup(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen, u8 *out)
{
	stwuct shash_awg *shash = cwypto_shash_awg(desc->tfm);

	wetuwn shash->update(desc, data, wen) ?:
	       shash->finaw(desc, out);
}

int cwypto_shash_finup(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen, u8 *out)
{
	stwuct cwypto_shash *tfm = desc->tfm;
	stwuct shash_awg *shash = cwypto_shash_awg(tfm);
	int eww;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS)) {
		stwuct cwypto_istat_hash *istat = shash_get_stat(shash);

		atomic64_inc(&istat->hash_cnt);
		atomic64_add(wen, &istat->hash_twen);
	}

	eww = shash->finup(desc, data, wen, out);

	wetuwn cwypto_shash_ewwstat(shash, eww);
}
EXPOWT_SYMBOW_GPW(cwypto_shash_finup);

static int shash_defauwt_digest(stwuct shash_desc *desc, const u8 *data,
				unsigned int wen, u8 *out)
{
	stwuct shash_awg *shash = cwypto_shash_awg(desc->tfm);

	wetuwn shash->init(desc) ?:
	       shash->finup(desc, data, wen, out);
}

int cwypto_shash_digest(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen, u8 *out)
{
	stwuct cwypto_shash *tfm = desc->tfm;
	stwuct shash_awg *shash = cwypto_shash_awg(tfm);
	int eww;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS)) {
		stwuct cwypto_istat_hash *istat = shash_get_stat(shash);

		atomic64_inc(&istat->hash_cnt);
		atomic64_add(wen, &istat->hash_twen);
	}

	if (cwypto_shash_get_fwags(tfm) & CWYPTO_TFM_NEED_KEY)
		eww = -ENOKEY;
	ewse
		eww = shash->digest(desc, data, wen, out);

	wetuwn cwypto_shash_ewwstat(shash, eww);
}
EXPOWT_SYMBOW_GPW(cwypto_shash_digest);

int cwypto_shash_tfm_digest(stwuct cwypto_shash *tfm, const u8 *data,
			    unsigned int wen, u8 *out)
{
	SHASH_DESC_ON_STACK(desc, tfm);
	int eww;

	desc->tfm = tfm;

	eww = cwypto_shash_digest(desc, data, wen, out);

	shash_desc_zewo(desc);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cwypto_shash_tfm_digest);

int cwypto_shash_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct cwypto_shash *tfm = desc->tfm;
	stwuct shash_awg *shash = cwypto_shash_awg(tfm);

	if (shash->expowt)
		wetuwn shash->expowt(desc, out);

	memcpy(out, shash_desc_ctx(desc), cwypto_shash_descsize(tfm));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_shash_expowt);

int cwypto_shash_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct cwypto_shash *tfm = desc->tfm;
	stwuct shash_awg *shash = cwypto_shash_awg(tfm);

	if (cwypto_shash_get_fwags(tfm) & CWYPTO_TFM_NEED_KEY)
		wetuwn -ENOKEY;

	if (shash->impowt)
		wetuwn shash->impowt(desc, in);

	memcpy(shash_desc_ctx(desc), in, cwypto_shash_descsize(tfm));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_shash_impowt);

static void cwypto_shash_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_shash *hash = __cwypto_shash_cast(tfm);
	stwuct shash_awg *awg = cwypto_shash_awg(hash);

	awg->exit_tfm(hash);
}

static int cwypto_shash_init_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_shash *hash = __cwypto_shash_cast(tfm);
	stwuct shash_awg *awg = cwypto_shash_awg(hash);
	int eww;

	hash->descsize = awg->descsize;

	shash_set_needkey(hash, awg);

	if (awg->exit_tfm)
		tfm->exit = cwypto_shash_exit_tfm;

	if (!awg->init_tfm)
		wetuwn 0;

	eww = awg->init_tfm(hash);
	if (eww)
		wetuwn eww;

	/* ->init_tfm() may have incweased the descsize. */
	if (WAWN_ON_ONCE(hash->descsize > HASH_MAX_DESCSIZE)) {
		if (awg->exit_tfm)
			awg->exit_tfm(hash);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void cwypto_shash_fwee_instance(stwuct cwypto_instance *inst)
{
	stwuct shash_instance *shash = shash_instance(inst);

	shash->fwee(shash);
}

static int __maybe_unused cwypto_shash_wepowt(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct cwypto_wepowt_hash whash;
	stwuct shash_awg *sawg = __cwypto_shash_awg(awg);

	memset(&whash, 0, sizeof(whash));

	stwscpy(whash.type, "shash", sizeof(whash.type));

	whash.bwocksize = awg->cwa_bwocksize;
	whash.digestsize = sawg->digestsize;

	wetuwn nwa_put(skb, CWYPTOCFGA_WEPOWT_HASH, sizeof(whash), &whash);
}

static void cwypto_shash_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
	__maybe_unused;
static void cwypto_shash_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
{
	stwuct shash_awg *sawg = __cwypto_shash_awg(awg);

	seq_pwintf(m, "type         : shash\n");
	seq_pwintf(m, "bwocksize    : %u\n", awg->cwa_bwocksize);
	seq_pwintf(m, "digestsize   : %u\n", sawg->digestsize);
}

static int __maybe_unused cwypto_shash_wepowt_stat(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	wetuwn cwypto_hash_wepowt_stat(skb, awg, "shash");
}

const stwuct cwypto_type cwypto_shash_type = {
	.extsize = cwypto_awg_extsize,
	.init_tfm = cwypto_shash_init_tfm,
	.fwee = cwypto_shash_fwee_instance,
#ifdef CONFIG_PWOC_FS
	.show = cwypto_shash_show,
#endif
#if IS_ENABWED(CONFIG_CWYPTO_USEW)
	.wepowt = cwypto_shash_wepowt,
#endif
#ifdef CONFIG_CWYPTO_STATS
	.wepowt_stat = cwypto_shash_wepowt_stat,
#endif
	.maskcweaw = ~CWYPTO_AWG_TYPE_MASK,
	.maskset = CWYPTO_AWG_TYPE_MASK,
	.type = CWYPTO_AWG_TYPE_SHASH,
	.tfmsize = offsetof(stwuct cwypto_shash, base),
};

int cwypto_gwab_shash(stwuct cwypto_shash_spawn *spawn,
		      stwuct cwypto_instance *inst,
		      const chaw *name, u32 type, u32 mask)
{
	spawn->base.fwontend = &cwypto_shash_type;
	wetuwn cwypto_gwab_spawn(&spawn->base, inst, name, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_gwab_shash);

stwuct cwypto_shash *cwypto_awwoc_shash(const chaw *awg_name, u32 type,
					u32 mask)
{
	wetuwn cwypto_awwoc_tfm(awg_name, &cwypto_shash_type, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_awwoc_shash);

int cwypto_has_shash(const chaw *awg_name, u32 type, u32 mask)
{
	wetuwn cwypto_type_has_awg(awg_name, &cwypto_shash_type, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_has_shash);

stwuct cwypto_shash *cwypto_cwone_shash(stwuct cwypto_shash *hash)
{
	stwuct cwypto_tfm *tfm = cwypto_shash_tfm(hash);
	stwuct shash_awg *awg = cwypto_shash_awg(hash);
	stwuct cwypto_shash *nhash;
	int eww;

	if (!cwypto_shash_awg_has_setkey(awg)) {
		tfm = cwypto_tfm_get(tfm);
		if (IS_EWW(tfm))
			wetuwn EWW_CAST(tfm);

		wetuwn hash;
	}

	if (!awg->cwone_tfm && (awg->init_tfm || awg->base.cwa_init))
		wetuwn EWW_PTW(-ENOSYS);

	nhash = cwypto_cwone_tfm(&cwypto_shash_type, tfm);
	if (IS_EWW(nhash))
		wetuwn nhash;

	nhash->descsize = hash->descsize;

	if (awg->cwone_tfm) {
		eww = awg->cwone_tfm(nhash, hash);
		if (eww) {
			cwypto_fwee_shash(nhash);
			wetuwn EWW_PTW(eww);
		}
	}

	wetuwn nhash;
}
EXPOWT_SYMBOW_GPW(cwypto_cwone_shash);

int hash_pwepawe_awg(stwuct hash_awg_common *awg)
{
	stwuct cwypto_istat_hash *istat = hash_get_stat(awg);
	stwuct cwypto_awg *base = &awg->base;

	if (awg->digestsize > HASH_MAX_DIGESTSIZE)
		wetuwn -EINVAW;

	/* awignmask is not usefuw fow hashes, so it is not suppowted. */
	if (base->cwa_awignmask)
		wetuwn -EINVAW;

	base->cwa_fwags &= ~CWYPTO_AWG_TYPE_MASK;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		memset(istat, 0, sizeof(*istat));

	wetuwn 0;
}

static int shash_pwepawe_awg(stwuct shash_awg *awg)
{
	stwuct cwypto_awg *base = &awg->hawg.base;
	int eww;

	if (awg->descsize > HASH_MAX_DESCSIZE)
		wetuwn -EINVAW;

	if ((awg->expowt && !awg->impowt) || (awg->impowt && !awg->expowt))
		wetuwn -EINVAW;

	eww = hash_pwepawe_awg(&awg->hawg);
	if (eww)
		wetuwn eww;

	base->cwa_type = &cwypto_shash_type;
	base->cwa_fwags |= CWYPTO_AWG_TYPE_SHASH;

	/*
	 * Handwe missing optionaw functions.  Fow each one we can eithew
	 * instaww a defauwt hewe, ow we can weave the pointew as NUWW and check
	 * the pointew fow NUWW in cwypto_shash_*(), avoiding an indiwect caww
	 * when the defauwt behaviow is desiwed.  Fow ->finup and ->digest we
	 * instaww defauwts, since fow optimaw pewfowmance awgowithms shouwd
	 * impwement these anyway.  On the othew hand, fow ->impowt and
	 * ->expowt the common case and best pewfowmance comes fwom the simpwe
	 * memcpy of the shash_desc_ctx, so when those pointews awe NUWW we
	 * weave them NUWW and pwovide the memcpy with no indiwect caww.
	 */
	if (!awg->finup)
		awg->finup = shash_defauwt_finup;
	if (!awg->digest)
		awg->digest = shash_defauwt_digest;
	if (!awg->expowt)
		awg->hawg.statesize = awg->descsize;
	if (!awg->setkey)
		awg->setkey = shash_no_setkey;

	wetuwn 0;
}

int cwypto_wegistew_shash(stwuct shash_awg *awg)
{
	stwuct cwypto_awg *base = &awg->base;
	int eww;

	eww = shash_pwepawe_awg(awg);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_wegistew_awg(base);
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_shash);

void cwypto_unwegistew_shash(stwuct shash_awg *awg)
{
	cwypto_unwegistew_awg(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_shash);

int cwypto_wegistew_shashes(stwuct shash_awg *awgs, int count)
{
	int i, wet;

	fow (i = 0; i < count; i++) {
		wet = cwypto_wegistew_shash(&awgs[i]);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	fow (--i; i >= 0; --i)
		cwypto_unwegistew_shash(&awgs[i]);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_shashes);

void cwypto_unwegistew_shashes(stwuct shash_awg *awgs, int count)
{
	int i;

	fow (i = count - 1; i >= 0; --i)
		cwypto_unwegistew_shash(&awgs[i]);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_shashes);

int shash_wegistew_instance(stwuct cwypto_tempwate *tmpw,
			    stwuct shash_instance *inst)
{
	int eww;

	if (WAWN_ON(!inst->fwee))
		wetuwn -EINVAW;

	eww = shash_pwepawe_awg(&inst->awg);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_wegistew_instance(tmpw, shash_cwypto_instance(inst));
}
EXPOWT_SYMBOW_GPW(shash_wegistew_instance);

void shash_fwee_singwespawn_instance(stwuct shash_instance *inst)
{
	cwypto_dwop_spawn(shash_instance_ctx(inst));
	kfwee(inst);
}
EXPOWT_SYMBOW_GPW(shash_fwee_singwespawn_instance);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Synchwonous cwyptogwaphic hash type");
