// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * echainiv: Encwypted Chain IV Genewatow
 *
 * This genewatow genewates an IV based on a sequence numbew by muwtipwying
 * it with a sawt and then encwypting it with the same key as used to encwypt
 * the pwain text.  This awgowithm wequiwes that the bwock size be equaw
 * to the IV size.  It is mainwy usefuw fow CBC.
 *
 * This genewatow can onwy be used by awgowithms whewe authentication
 * is pewfowmed aftew encwyption (i.e., authenc).
 *
 * Copywight (c) 2015 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
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

static int echainiv_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *geniv = cwypto_aead_weqtfm(weq);
	stwuct aead_geniv_ctx *ctx = cwypto_aead_ctx(geniv);
	stwuct aead_wequest *subweq = aead_wequest_ctx(weq);
	__be64 nseqno;
	u64 seqno;
	u8 *info;
	unsigned int ivsize = cwypto_aead_ivsize(geniv);
	int eww;

	if (weq->cwyptwen < ivsize)
		wetuwn -EINVAW;

	aead_wequest_set_tfm(subweq, ctx->chiwd);

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

	aead_wequest_set_cawwback(subweq, weq->base.fwags,
				  weq->base.compwete, weq->base.data);
	aead_wequest_set_cwypt(subweq, weq->dst, weq->dst,
			       weq->cwyptwen, info);
	aead_wequest_set_ad(subweq, weq->assocwen);

	memcpy(&nseqno, info + ivsize - 8, 8);
	seqno = be64_to_cpu(nseqno);
	memset(info, 0, ivsize);

	scattewwawk_map_and_copy(info, weq->dst, weq->assocwen, ivsize, 1);

	do {
		u64 a;

		memcpy(&a, ctx->sawt + ivsize - 8, 8);

		a |= 1;
		a *= seqno;

		memcpy(info + ivsize - 8, &a, 8);
	} whiwe ((ivsize -= 8));

	wetuwn cwypto_aead_encwypt(subweq);
}

static int echainiv_decwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *geniv = cwypto_aead_weqtfm(weq);
	stwuct aead_geniv_ctx *ctx = cwypto_aead_ctx(geniv);
	stwuct aead_wequest *subweq = aead_wequest_ctx(weq);
	cwypto_compwetion_t compw;
	void *data;
	unsigned int ivsize = cwypto_aead_ivsize(geniv);

	if (weq->cwyptwen < ivsize)
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

static int echainiv_aead_cweate(stwuct cwypto_tempwate *tmpw,
				stwuct wtattw **tb)
{
	stwuct aead_instance *inst;
	int eww;

	inst = aead_geniv_awwoc(tmpw, tb);

	if (IS_EWW(inst))
		wetuwn PTW_EWW(inst);

	eww = -EINVAW;
	if (inst->awg.ivsize & (sizeof(u64) - 1) || !inst->awg.ivsize)
		goto fwee_inst;

	inst->awg.encwypt = echainiv_encwypt;
	inst->awg.decwypt = echainiv_decwypt;

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

static stwuct cwypto_tempwate echainiv_tmpw = {
	.name = "echainiv",
	.cweate = echainiv_aead_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init echainiv_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&echainiv_tmpw);
}

static void __exit echainiv_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&echainiv_tmpw);
}

subsys_initcaww(echainiv_moduwe_init);
moduwe_exit(echainiv_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Encwypted Chain IV Genewatow");
MODUWE_AWIAS_CWYPTO("echainiv");
