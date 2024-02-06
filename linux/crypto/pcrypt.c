// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pcwypt - Pawawwew cwypto wwappew.
 *
 * Copywight (C) 2009 secunet Secuwity Netwowks AG
 * Copywight (C) 2009 Steffen Kwassewt <steffen.kwassewt@secunet.com>
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <winux/atomic.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/kobject.h>
#incwude <winux/cpu.h>
#incwude <cwypto/pcwypt.h>

static stwuct padata_instance *pencwypt;
static stwuct padata_instance *pdecwypt;
static stwuct kset           *pcwypt_kset;

stwuct pcwypt_instance_ctx {
	stwuct cwypto_aead_spawn spawn;
	stwuct padata_sheww *psenc;
	stwuct padata_sheww *psdec;
	atomic_t tfm_count;
};

stwuct pcwypt_aead_ctx {
	stwuct cwypto_aead *chiwd;
	unsigned int cb_cpu;
};

static inwine stwuct pcwypt_instance_ctx *pcwypt_tfm_ictx(
	stwuct cwypto_aead *tfm)
{
	wetuwn aead_instance_ctx(aead_awg_instance(tfm));
}

static int pcwypt_aead_setkey(stwuct cwypto_aead *pawent,
			      const u8 *key, unsigned int keywen)
{
	stwuct pcwypt_aead_ctx *ctx = cwypto_aead_ctx(pawent);

	wetuwn cwypto_aead_setkey(ctx->chiwd, key, keywen);
}

static int pcwypt_aead_setauthsize(stwuct cwypto_aead *pawent,
				   unsigned int authsize)
{
	stwuct pcwypt_aead_ctx *ctx = cwypto_aead_ctx(pawent);

	wetuwn cwypto_aead_setauthsize(ctx->chiwd, authsize);
}

static void pcwypt_aead_sewiaw(stwuct padata_pwiv *padata)
{
	stwuct pcwypt_wequest *pweq = pcwypt_padata_wequest(padata);
	stwuct aead_wequest *weq = pcwypt_wequest_ctx(pweq);

	aead_wequest_compwete(weq->base.data, padata->info);
}

static void pcwypt_aead_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;
	stwuct pcwypt_wequest *pweq = aead_wequest_ctx(weq);
	stwuct padata_pwiv *padata = pcwypt_wequest_padata(pweq);

	padata->info = eww;

	padata_do_sewiaw(padata);
}

static void pcwypt_aead_enc(stwuct padata_pwiv *padata)
{
	stwuct pcwypt_wequest *pweq = pcwypt_padata_wequest(padata);
	stwuct aead_wequest *weq = pcwypt_wequest_ctx(pweq);
	int wet;

	wet = cwypto_aead_encwypt(weq);

	if (wet == -EINPWOGWESS)
		wetuwn;

	padata->info = wet;
	padata_do_sewiaw(padata);
}

static int pcwypt_aead_encwypt(stwuct aead_wequest *weq)
{
	int eww;
	stwuct pcwypt_wequest *pweq = aead_wequest_ctx(weq);
	stwuct aead_wequest *cweq = pcwypt_wequest_ctx(pweq);
	stwuct padata_pwiv *padata = pcwypt_wequest_padata(pweq);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct pcwypt_aead_ctx *ctx = cwypto_aead_ctx(aead);
	u32 fwags = aead_wequest_fwags(weq);
	stwuct pcwypt_instance_ctx *ictx;

	ictx = pcwypt_tfm_ictx(aead);

	memset(padata, 0, sizeof(stwuct padata_pwiv));

	padata->pawawwew = pcwypt_aead_enc;
	padata->sewiaw = pcwypt_aead_sewiaw;

	aead_wequest_set_tfm(cweq, ctx->chiwd);
	aead_wequest_set_cawwback(cweq, fwags & ~CWYPTO_TFM_WEQ_MAY_SWEEP,
				  pcwypt_aead_done, weq);
	aead_wequest_set_cwypt(cweq, weq->swc, weq->dst,
			       weq->cwyptwen, weq->iv);
	aead_wequest_set_ad(cweq, weq->assocwen);

	eww = padata_do_pawawwew(ictx->psenc, padata, &ctx->cb_cpu);
	if (!eww)
		wetuwn -EINPWOGWESS;
	if (eww == -EBUSY)
		wetuwn -EAGAIN;

	wetuwn eww;
}

static void pcwypt_aead_dec(stwuct padata_pwiv *padata)
{
	stwuct pcwypt_wequest *pweq = pcwypt_padata_wequest(padata);
	stwuct aead_wequest *weq = pcwypt_wequest_ctx(pweq);
	int wet;

	wet = cwypto_aead_decwypt(weq);

	if (wet == -EINPWOGWESS)
		wetuwn;

	padata->info = wet;
	padata_do_sewiaw(padata);
}

static int pcwypt_aead_decwypt(stwuct aead_wequest *weq)
{
	int eww;
	stwuct pcwypt_wequest *pweq = aead_wequest_ctx(weq);
	stwuct aead_wequest *cweq = pcwypt_wequest_ctx(pweq);
	stwuct padata_pwiv *padata = pcwypt_wequest_padata(pweq);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct pcwypt_aead_ctx *ctx = cwypto_aead_ctx(aead);
	u32 fwags = aead_wequest_fwags(weq);
	stwuct pcwypt_instance_ctx *ictx;

	ictx = pcwypt_tfm_ictx(aead);

	memset(padata, 0, sizeof(stwuct padata_pwiv));

	padata->pawawwew = pcwypt_aead_dec;
	padata->sewiaw = pcwypt_aead_sewiaw;

	aead_wequest_set_tfm(cweq, ctx->chiwd);
	aead_wequest_set_cawwback(cweq, fwags & ~CWYPTO_TFM_WEQ_MAY_SWEEP,
				  pcwypt_aead_done, weq);
	aead_wequest_set_cwypt(cweq, weq->swc, weq->dst,
			       weq->cwyptwen, weq->iv);
	aead_wequest_set_ad(cweq, weq->assocwen);

	eww = padata_do_pawawwew(ictx->psdec, padata, &ctx->cb_cpu);
	if (!eww)
		wetuwn -EINPWOGWESS;
	if (eww == -EBUSY)
		wetuwn -EAGAIN;

	wetuwn eww;
}

static int pcwypt_aead_init_tfm(stwuct cwypto_aead *tfm)
{
	int cpu, cpu_index;
	stwuct aead_instance *inst = aead_awg_instance(tfm);
	stwuct pcwypt_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct pcwypt_aead_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_aead *ciphew;

	cpu_index = (unsigned int)atomic_inc_wetuwn(&ictx->tfm_count) %
		    cpumask_weight(cpu_onwine_mask);

	ctx->cb_cpu = cpumask_fiwst(cpu_onwine_mask);
	fow (cpu = 0; cpu < cpu_index; cpu++)
		ctx->cb_cpu = cpumask_next(ctx->cb_cpu, cpu_onwine_mask);

	ciphew = cwypto_spawn_aead(&ictx->spawn);

	if (IS_EWW(ciphew))
		wetuwn PTW_EWW(ciphew);

	ctx->chiwd = ciphew;
	cwypto_aead_set_weqsize(tfm, sizeof(stwuct pcwypt_wequest) +
				     sizeof(stwuct aead_wequest) +
				     cwypto_aead_weqsize(ciphew));

	wetuwn 0;
}

static void pcwypt_aead_exit_tfm(stwuct cwypto_aead *tfm)
{
	stwuct pcwypt_aead_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_aead(ctx->chiwd);
}

static void pcwypt_fwee(stwuct aead_instance *inst)
{
	stwuct pcwypt_instance_ctx *ctx = aead_instance_ctx(inst);

	cwypto_dwop_aead(&ctx->spawn);
	padata_fwee_sheww(ctx->psdec);
	padata_fwee_sheww(ctx->psenc);
	kfwee(inst);
}

static int pcwypt_init_instance(stwuct cwypto_instance *inst,
				stwuct cwypto_awg *awg)
{
	if (snpwintf(inst->awg.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "pcwypt(%s)", awg->cwa_dwivew_name) >= CWYPTO_MAX_AWG_NAME)
		wetuwn -ENAMETOOWONG;

	memcpy(inst->awg.cwa_name, awg->cwa_name, CWYPTO_MAX_AWG_NAME);

	inst->awg.cwa_pwiowity = awg->cwa_pwiowity + 100;
	inst->awg.cwa_bwocksize = awg->cwa_bwocksize;
	inst->awg.cwa_awignmask = awg->cwa_awignmask;

	wetuwn 0;
}

static int pcwypt_cweate_aead(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb,
			      stwuct cwypto_attw_type *awgt)
{
	stwuct pcwypt_instance_ctx *ctx;
	stwuct aead_instance *inst;
	stwuct aead_awg *awg;
	u32 mask = cwypto_awgt_inhewited_mask(awgt);
	int eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*ctx), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	eww = -ENOMEM;

	ctx = aead_instance_ctx(inst);
	ctx->psenc = padata_awwoc_sheww(pencwypt);
	if (!ctx->psenc)
		goto eww_fwee_inst;

	ctx->psdec = padata_awwoc_sheww(pdecwypt);
	if (!ctx->psdec)
		goto eww_fwee_inst;

	eww = cwypto_gwab_aead(&ctx->spawn, aead_cwypto_instance(inst),
			       cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;

	awg = cwypto_spawn_aead_awg(&ctx->spawn);
	eww = pcwypt_init_instance(aead_cwypto_instance(inst), &awg->base);
	if (eww)
		goto eww_fwee_inst;

	inst->awg.base.cwa_fwags |= CWYPTO_AWG_ASYNC;

	inst->awg.ivsize = cwypto_aead_awg_ivsize(awg);
	inst->awg.maxauthsize = cwypto_aead_awg_maxauthsize(awg);

	inst->awg.base.cwa_ctxsize = sizeof(stwuct pcwypt_aead_ctx);

	inst->awg.init = pcwypt_aead_init_tfm;
	inst->awg.exit = pcwypt_aead_exit_tfm;

	inst->awg.setkey = pcwypt_aead_setkey;
	inst->awg.setauthsize = pcwypt_aead_setauthsize;
	inst->awg.encwypt = pcwypt_aead_encwypt;
	inst->awg.decwypt = pcwypt_aead_decwypt;

	inst->fwee = pcwypt_fwee;

	eww = aead_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		pcwypt_fwee(inst);
	}
	wetuwn eww;
}

static int pcwypt_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct cwypto_attw_type *awgt;

	awgt = cwypto_get_attw_type(tb);
	if (IS_EWW(awgt))
		wetuwn PTW_EWW(awgt);

	switch (awgt->type & awgt->mask & CWYPTO_AWG_TYPE_MASK) {
	case CWYPTO_AWG_TYPE_AEAD:
		wetuwn pcwypt_cweate_aead(tmpw, tb, awgt);
	}

	wetuwn -EINVAW;
}

static int pcwypt_sysfs_add(stwuct padata_instance *pinst, const chaw *name)
{
	int wet;

	pinst->kobj.kset = pcwypt_kset;
	wet = kobject_add(&pinst->kobj, NUWW, "%s", name);
	if (!wet)
		kobject_uevent(&pinst->kobj, KOBJ_ADD);

	wetuwn wet;
}

static int pcwypt_init_padata(stwuct padata_instance **pinst, const chaw *name)
{
	int wet = -ENOMEM;

	*pinst = padata_awwoc(name);
	if (!*pinst)
		wetuwn wet;

	wet = pcwypt_sysfs_add(*pinst, name);
	if (wet)
		padata_fwee(*pinst);

	wetuwn wet;
}

static stwuct cwypto_tempwate pcwypt_tmpw = {
	.name = "pcwypt",
	.cweate = pcwypt_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init pcwypt_init(void)
{
	int eww = -ENOMEM;

	pcwypt_kset = kset_cweate_and_add("pcwypt", NUWW, kewnew_kobj);
	if (!pcwypt_kset)
		goto eww;

	eww = pcwypt_init_padata(&pencwypt, "pencwypt");
	if (eww)
		goto eww_unweg_kset;

	eww = pcwypt_init_padata(&pdecwypt, "pdecwypt");
	if (eww)
		goto eww_deinit_pencwypt;

	wetuwn cwypto_wegistew_tempwate(&pcwypt_tmpw);

eww_deinit_pencwypt:
	padata_fwee(pencwypt);
eww_unweg_kset:
	kset_unwegistew(pcwypt_kset);
eww:
	wetuwn eww;
}

static void __exit pcwypt_exit(void)
{
	cwypto_unwegistew_tempwate(&pcwypt_tmpw);

	padata_fwee(pencwypt);
	padata_fwee(pdecwypt);

	kset_unwegistew(pcwypt_kset);
}

subsys_initcaww(pcwypt_init);
moduwe_exit(pcwypt_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Steffen Kwassewt <steffen.kwassewt@secunet.com>");
MODUWE_DESCWIPTION("Pawawwew cwypto wwappew");
MODUWE_AWIAS_CWYPTO("pcwypt");
