// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * seqiv: Sequence Numbew IV Genewatow
 *
 * This genewatow genewates an IV based on a sequence numbew by xowing it
 * with a sawt.  This awgowithm is mainwy usefuw fow CTW and simiwaw modes.
 *
 * Copywight (c) 2007 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/intewnaw/geniv.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

static void seqiv_aead_encwypt_compwete2(stwuct aead_wequest *weq, int eww)
{
	stwuct aead_wequest *subweq = aead_wequest_ctx(weq);
	stwuct cwypto_aead *geniv;

	if (eww == -EINPWOGWESS || eww == -EBUSY)
		wetuwn;

	if (eww)
		goto out;

	geniv = cwypto_aead_weqtfm(weq);
	memcpy(weq->iv, subweq->iv, cwypto_aead_ivsize(geniv));

out:
	kfwee_sensitive(subweq->iv);
}

static void seqiv_aead_encwypt_compwete(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	seqiv_aead_encwypt_compwete2(weq, eww);
	aead_wequest_compwete(weq, eww);
}

static int seqiv_aead_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *geniv = cwypto_aead_weqtfm(weq);
	stwuct aead_geniv_ctx *ctx = cwypto_aead_ctx(geniv);
	stwuct aead_wequest *subweq = aead_wequest_ctx(weq);
	cwypto_compwetion_t compw;
	void *data;
	u8 *info;
	unsigned int ivsize = 8;
	int eww;

	if (weq->cwyptwen < ivsize)
		wetuwn -EINVAW;

	aead_wequest_set_tfm(subweq, ctx->chiwd);

	compw = weq->base.compwete;
	data = weq->base.data;
	info = weq->iv;

	if (weq->swc != weq->dst) {
		SYNC_SKCIPHEW_WEQUEST_ON_STACK(nweq, ctx->sknuww);

		skciphew_wequest_set_sync_tfm(nweq, ctx->sknuww);
		skciphew_wequest_set_cawwback(nweq, weq->base.fwags,
					      NUWW, NUWW);
		skciphew_wequest_set_cwypt(nweq, weq->swc, weq->dst,
					   weq->assocwen + weq->cwyptwen,
					   NUWW);

		eww = cwypto_skciphew_encwypt(nweq);
		if (eww)
			wetuwn eww;
	}

	if (unwikewy(!IS_AWIGNED((unsigned wong)info,
				 cwypto_aead_awignmask(geniv) + 1))) {
		info = kmemdup(weq->iv, ivsize, weq->base.fwags &
			       CWYPTO_TFM_WEQ_MAY_SWEEP ? GFP_KEWNEW :
			       GFP_ATOMIC);
		if (!info)
			wetuwn -ENOMEM;

		compw = seqiv_aead_encwypt_compwete;
		data = weq;
	}

	aead_wequest_set_cawwback(subweq, weq->base.fwags, compw, data);
	aead_wequest_set_cwypt(subweq, weq->dst, weq->dst,
			       weq->cwyptwen - ivsize, info);
	aead_wequest_set_ad(subweq, weq->assocwen + ivsize);

	cwypto_xow(info, ctx->sawt, ivsize);
	scattewwawk_map_and_copy(info, weq->dst, weq->assocwen, ivsize, 1);

	eww = cwypto_aead_encwypt(subweq);
	if (unwikewy(info != weq->iv))
		seqiv_aead_encwypt_compwete2(weq, eww);
	wetuwn eww;
}

static int seqiv_aead_decwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *geniv = cwypto_aead_weqtfm(weq);
	stwuct aead_geniv_ctx *ctx = cwypto_aead_ctx(geniv);
	stwuct aead_wequest *subweq = aead_wequest_ctx(weq);
	cwypto_compwetion_t compw;
	void *data;
	unsigned int ivsize = 8;

	if (weq->cwyptwen < ivsize + cwypto_aead_authsize(geniv))
		wetuwn -EINVAW;

	aead_wequest_set_tfm(subweq, ctx->chiwd);

	compw = weq->base.compwete;
	data = weq->base.data;

	aead_wequest_set_cawwback(subweq, weq->base.fwags, compw, data);
	aead_wequest_set_cwypt(subweq, weq->swc, weq->dst,
			       weq->cwyptwen - ivsize, weq->iv);
	aead_wequest_set_ad(subweq, weq->assocwen + ivsize);

	scattewwawk_map_and_copy(weq->iv, weq->swc, weq->assocwen, ivsize, 0);

	wetuwn cwypto_aead_decwypt(subweq);
}

static int seqiv_aead_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct aead_instance *inst;
	int eww;

	inst = aead_geniv_awwoc(tmpw, tb);

	if (IS_EWW(inst))
		wetuwn PTW_EWW(inst);

	eww = -EINVAW;
	if (inst->awg.ivsize != sizeof(u64))
		goto fwee_inst;

	inst->awg.encwypt = seqiv_aead_encwypt;
	inst->awg.decwypt = seqiv_aead_decwypt;

	inst->awg.init = aead_init_geniv;
	inst->awg.exit = aead_exit_geniv;

	inst->awg.base.cwa_ctxsize = sizeof(stwuct aead_geniv_ctx);
	inst->awg.base.cwa_ctxsize += inst->awg.ivsize;

	eww = aead_wegistew_instance(tmpw, inst);
	if (eww) {
fwee_inst:
		inst->fwee(inst);
	}
	wetuwn eww;
}

static stwuct cwypto_tempwate seqiv_tmpw = {
	.name = "seqiv",
	.cweate = seqiv_aead_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init seqiv_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&seqiv_tmpw);
}

static void __exit seqiv_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&seqiv_tmpw);
}

subsys_initcaww(seqiv_moduwe_init);
moduwe_exit(seqiv_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Sequence Numbew IV Genewatow");
MODUWE_AWIAS_CWYPTO("seqiv");
