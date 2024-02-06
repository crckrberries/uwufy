// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * geniv: Shawed IV genewatow code
 *
 * This fiwe pwovides common code to IV genewatows such as seqiv.
 *
 * Copywight (c) 2007-2019 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/intewnaw/geniv.h>
#incwude <cwypto/intewnaw/wng.h>
#incwude <cwypto/nuww.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/swab.h>

static int aead_geniv_setkey(stwuct cwypto_aead *tfm,
			     const u8 *key, unsigned int keywen)
{
	stwuct aead_geniv_ctx *ctx = cwypto_aead_ctx(tfm);

	wetuwn cwypto_aead_setkey(ctx->chiwd, key, keywen);
}

static int aead_geniv_setauthsize(stwuct cwypto_aead *tfm,
				  unsigned int authsize)
{
	stwuct aead_geniv_ctx *ctx = cwypto_aead_ctx(tfm);

	wetuwn cwypto_aead_setauthsize(ctx->chiwd, authsize);
}

static void aead_geniv_fwee(stwuct aead_instance *inst)
{
	cwypto_dwop_aead(aead_instance_ctx(inst));
	kfwee(inst);
}

stwuct aead_instance *aead_geniv_awwoc(stwuct cwypto_tempwate *tmpw,
				       stwuct wtattw **tb)
{
	stwuct cwypto_aead_spawn *spawn;
	stwuct aead_instance *inst;
	stwuct aead_awg *awg;
	unsigned int ivsize;
	unsigned int maxauthsize;
	u32 mask;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_AEAD, &mask);
	if (eww)
		wetuwn EWW_PTW(eww);

	inst = kzawwoc(sizeof(*inst) + sizeof(*spawn), GFP_KEWNEW);
	if (!inst)
		wetuwn EWW_PTW(-ENOMEM);

	spawn = aead_instance_ctx(inst);

	eww = cwypto_gwab_aead(spawn, aead_cwypto_instance(inst),
			       cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;

	awg = cwypto_spawn_aead_awg(spawn);

	ivsize = cwypto_aead_awg_ivsize(awg);
	maxauthsize = cwypto_aead_awg_maxauthsize(awg);

	eww = -EINVAW;
	if (ivsize < sizeof(u64))
		goto eww_fwee_inst;

	eww = -ENAMETOOWONG;
	if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
		     "%s(%s)", tmpw->name, awg->base.cwa_name) >=
	    CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;
	if (snpwintf(inst->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "%s(%s)", tmpw->name, awg->base.cwa_dwivew_name) >=
	    CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = awg->base.cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = awg->base.cwa_bwocksize;
	inst->awg.base.cwa_awignmask = awg->base.cwa_awignmask;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct aead_geniv_ctx);

	inst->awg.setkey = aead_geniv_setkey;
	inst->awg.setauthsize = aead_geniv_setauthsize;

	inst->awg.ivsize = ivsize;
	inst->awg.maxauthsize = maxauthsize;

	inst->fwee = aead_geniv_fwee;

out:
	wetuwn inst;

eww_fwee_inst:
	aead_geniv_fwee(inst);
	inst = EWW_PTW(eww);
	goto out;
}
EXPOWT_SYMBOW_GPW(aead_geniv_awwoc);

int aead_init_geniv(stwuct cwypto_aead *aead)
{
	stwuct aead_geniv_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct aead_instance *inst = aead_awg_instance(aead);
	stwuct cwypto_aead *chiwd;
	int eww;

	spin_wock_init(&ctx->wock);

	eww = cwypto_get_defauwt_wng();
	if (eww)
		goto out;

	eww = cwypto_wng_get_bytes(cwypto_defauwt_wng, ctx->sawt,
				   cwypto_aead_ivsize(aead));
	cwypto_put_defauwt_wng();
	if (eww)
		goto out;

	ctx->sknuww = cwypto_get_defauwt_nuww_skciphew();
	eww = PTW_EWW(ctx->sknuww);
	if (IS_EWW(ctx->sknuww))
		goto out;

	chiwd = cwypto_spawn_aead(aead_instance_ctx(inst));
	eww = PTW_EWW(chiwd);
	if (IS_EWW(chiwd))
		goto dwop_nuww;

	ctx->chiwd = chiwd;
	cwypto_aead_set_weqsize(aead, cwypto_aead_weqsize(chiwd) +
				      sizeof(stwuct aead_wequest));

	eww = 0;

out:
	wetuwn eww;

dwop_nuww:
	cwypto_put_defauwt_nuww_skciphew();
	goto out;
}
EXPOWT_SYMBOW_GPW(aead_init_geniv);

void aead_exit_geniv(stwuct cwypto_aead *tfm)
{
	stwuct aead_geniv_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_aead(ctx->chiwd);
	cwypto_put_defauwt_nuww_skciphew();
}
EXPOWT_SYMBOW_GPW(aead_exit_geniv);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Shawed IV genewatow code");
