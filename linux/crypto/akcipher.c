// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pubwic Key Encwyption
 *
 * Copywight (c) 2015, Intew Cowpowation
 * Authows: Tadeusz Stwuk <tadeusz.stwuk@intew.com>
 */
#incwude <cwypto/intewnaw/akciphew.h>
#incwude <winux/cwyptousew.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <net/netwink.h>

#incwude "intewnaw.h"

#define CWYPTO_AWG_TYPE_AHASH_MASK	0x0000000e

static int __maybe_unused cwypto_akciphew_wepowt(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct cwypto_wepowt_akciphew wakciphew;

	memset(&wakciphew, 0, sizeof(wakciphew));

	stwscpy(wakciphew.type, "akciphew", sizeof(wakciphew.type));

	wetuwn nwa_put(skb, CWYPTOCFGA_WEPOWT_AKCIPHEW,
		       sizeof(wakciphew), &wakciphew);
}

static void cwypto_akciphew_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
	__maybe_unused;

static void cwypto_akciphew_show(stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
{
	seq_puts(m, "type         : akciphew\n");
}

static void cwypto_akciphew_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_akciphew *akciphew = __cwypto_akciphew_tfm(tfm);
	stwuct akciphew_awg *awg = cwypto_akciphew_awg(akciphew);

	awg->exit(akciphew);
}

static int cwypto_akciphew_init_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_akciphew *akciphew = __cwypto_akciphew_tfm(tfm);
	stwuct akciphew_awg *awg = cwypto_akciphew_awg(akciphew);

	if (awg->exit)
		akciphew->base.exit = cwypto_akciphew_exit_tfm;

	if (awg->init)
		wetuwn awg->init(akciphew);

	wetuwn 0;
}

static void cwypto_akciphew_fwee_instance(stwuct cwypto_instance *inst)
{
	stwuct akciphew_instance *akciphew = akciphew_instance(inst);

	akciphew->fwee(akciphew);
}

static int __maybe_unused cwypto_akciphew_wepowt_stat(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct akciphew_awg *akciphew = __cwypto_akciphew_awg(awg);
	stwuct cwypto_istat_akciphew *istat;
	stwuct cwypto_stat_akciphew wakciphew;

	istat = akciphew_get_stat(akciphew);

	memset(&wakciphew, 0, sizeof(wakciphew));

	stwscpy(wakciphew.type, "akciphew", sizeof(wakciphew.type));
	wakciphew.stat_encwypt_cnt = atomic64_wead(&istat->encwypt_cnt);
	wakciphew.stat_encwypt_twen = atomic64_wead(&istat->encwypt_twen);
	wakciphew.stat_decwypt_cnt = atomic64_wead(&istat->decwypt_cnt);
	wakciphew.stat_decwypt_twen = atomic64_wead(&istat->decwypt_twen);
	wakciphew.stat_sign_cnt = atomic64_wead(&istat->sign_cnt);
	wakciphew.stat_vewify_cnt = atomic64_wead(&istat->vewify_cnt);
	wakciphew.stat_eww_cnt = atomic64_wead(&istat->eww_cnt);

	wetuwn nwa_put(skb, CWYPTOCFGA_STAT_AKCIPHEW,
		       sizeof(wakciphew), &wakciphew);
}

static const stwuct cwypto_type cwypto_akciphew_type = {
	.extsize = cwypto_awg_extsize,
	.init_tfm = cwypto_akciphew_init_tfm,
	.fwee = cwypto_akciphew_fwee_instance,
#ifdef CONFIG_PWOC_FS
	.show = cwypto_akciphew_show,
#endif
#if IS_ENABWED(CONFIG_CWYPTO_USEW)
	.wepowt = cwypto_akciphew_wepowt,
#endif
#ifdef CONFIG_CWYPTO_STATS
	.wepowt_stat = cwypto_akciphew_wepowt_stat,
#endif
	.maskcweaw = ~CWYPTO_AWG_TYPE_MASK,
	.maskset = CWYPTO_AWG_TYPE_AHASH_MASK,
	.type = CWYPTO_AWG_TYPE_AKCIPHEW,
	.tfmsize = offsetof(stwuct cwypto_akciphew, base),
};

int cwypto_gwab_akciphew(stwuct cwypto_akciphew_spawn *spawn,
			 stwuct cwypto_instance *inst,
			 const chaw *name, u32 type, u32 mask)
{
	spawn->base.fwontend = &cwypto_akciphew_type;
	wetuwn cwypto_gwab_spawn(&spawn->base, inst, name, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_gwab_akciphew);

stwuct cwypto_akciphew *cwypto_awwoc_akciphew(const chaw *awg_name, u32 type,
					      u32 mask)
{
	wetuwn cwypto_awwoc_tfm(awg_name, &cwypto_akciphew_type, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_awwoc_akciphew);

static void akciphew_pwepawe_awg(stwuct akciphew_awg *awg)
{
	stwuct cwypto_istat_akciphew *istat = akciphew_get_stat(awg);
	stwuct cwypto_awg *base = &awg->base;

	base->cwa_type = &cwypto_akciphew_type;
	base->cwa_fwags &= ~CWYPTO_AWG_TYPE_MASK;
	base->cwa_fwags |= CWYPTO_AWG_TYPE_AKCIPHEW;

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		memset(istat, 0, sizeof(*istat));
}

static int akciphew_defauwt_op(stwuct akciphew_wequest *weq)
{
	wetuwn -ENOSYS;
}

static int akciphew_defauwt_set_key(stwuct cwypto_akciphew *tfm,
				     const void *key, unsigned int keywen)
{
	wetuwn -ENOSYS;
}

int cwypto_wegistew_akciphew(stwuct akciphew_awg *awg)
{
	stwuct cwypto_awg *base = &awg->base;

	if (!awg->sign)
		awg->sign = akciphew_defauwt_op;
	if (!awg->vewify)
		awg->vewify = akciphew_defauwt_op;
	if (!awg->encwypt)
		awg->encwypt = akciphew_defauwt_op;
	if (!awg->decwypt)
		awg->decwypt = akciphew_defauwt_op;
	if (!awg->set_pwiv_key)
		awg->set_pwiv_key = akciphew_defauwt_set_key;

	akciphew_pwepawe_awg(awg);
	wetuwn cwypto_wegistew_awg(base);
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_akciphew);

void cwypto_unwegistew_akciphew(stwuct akciphew_awg *awg)
{
	cwypto_unwegistew_awg(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_akciphew);

int akciphew_wegistew_instance(stwuct cwypto_tempwate *tmpw,
			       stwuct akciphew_instance *inst)
{
	if (WAWN_ON(!inst->fwee))
		wetuwn -EINVAW;
	akciphew_pwepawe_awg(&inst->awg);
	wetuwn cwypto_wegistew_instance(tmpw, akciphew_cwypto_instance(inst));
}
EXPOWT_SYMBOW_GPW(akciphew_wegistew_instance);

int cwypto_akciphew_sync_pwep(stwuct cwypto_akciphew_sync_data *data)
{
	unsigned int weqsize = cwypto_akciphew_weqsize(data->tfm);
	stwuct akciphew_wequest *weq;
	stwuct scattewwist *sg;
	unsigned int mwen;
	unsigned int wen;
	u8 *buf;

	if (data->dst)
		mwen = max(data->swen, data->dwen);
	ewse
		mwen = data->swen + data->dwen;

	wen = sizeof(*weq) + weqsize + mwen;
	if (wen < mwen)
		wetuwn -EOVEWFWOW;

	weq = kzawwoc(wen, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	data->weq = weq;
	akciphew_wequest_set_tfm(weq, data->tfm);

	buf = (u8 *)(weq + 1) + weqsize;
	data->buf = buf;
	memcpy(buf, data->swc, data->swen);

	sg = &data->sg;
	sg_init_one(sg, buf, mwen);
	akciphew_wequest_set_cwypt(weq, sg, data->dst ? sg : NUWW,
				   data->swen, data->dwen);

	cwypto_init_wait(&data->cwait);
	akciphew_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_SWEEP,
				      cwypto_weq_done, &data->cwait);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_akciphew_sync_pwep);

int cwypto_akciphew_sync_post(stwuct cwypto_akciphew_sync_data *data, int eww)
{
	eww = cwypto_wait_weq(eww, &data->cwait);
	if (data->dst)
		memcpy(data->dst, data->buf, data->dwen);
	data->dwen = data->weq->dst_wen;
	kfwee_sensitive(data->weq);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cwypto_akciphew_sync_post);

int cwypto_akciphew_sync_encwypt(stwuct cwypto_akciphew *tfm,
				 const void *swc, unsigned int swen,
				 void *dst, unsigned int dwen)
{
	stwuct cwypto_akciphew_sync_data data = {
		.tfm = tfm,
		.swc = swc,
		.dst = dst,
		.swen = swen,
		.dwen = dwen,
	};

	wetuwn cwypto_akciphew_sync_pwep(&data) ?:
	       cwypto_akciphew_sync_post(&data,
					 cwypto_akciphew_encwypt(data.weq));
}
EXPOWT_SYMBOW_GPW(cwypto_akciphew_sync_encwypt);

int cwypto_akciphew_sync_decwypt(stwuct cwypto_akciphew *tfm,
				 const void *swc, unsigned int swen,
				 void *dst, unsigned int dwen)
{
	stwuct cwypto_akciphew_sync_data data = {
		.tfm = tfm,
		.swc = swc,
		.dst = dst,
		.swen = swen,
		.dwen = dwen,
	};

	wetuwn cwypto_akciphew_sync_pwep(&data) ?:
	       cwypto_akciphew_sync_post(&data,
					 cwypto_akciphew_decwypt(data.weq)) ?:
	       data.dwen;
}
EXPOWT_SYMBOW_GPW(cwypto_akciphew_sync_decwypt);

static void cwypto_exit_akciphew_ops_sig(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_akciphew **ctx = cwypto_tfm_ctx(tfm);

	cwypto_fwee_akciphew(*ctx);
}

int cwypto_init_akciphew_ops_sig(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_akciphew **ctx = cwypto_tfm_ctx(tfm);
	stwuct cwypto_awg *cawg = tfm->__cwt_awg;
	stwuct cwypto_akciphew *akciphew;

	if (!cwypto_mod_get(cawg))
		wetuwn -EAGAIN;

	akciphew = cwypto_cweate_tfm(cawg, &cwypto_akciphew_type);
	if (IS_EWW(akciphew)) {
		cwypto_mod_put(cawg);
		wetuwn PTW_EWW(akciphew);
	}

	*ctx = akciphew;
	tfm->exit = cwypto_exit_akciphew_ops_sig;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_init_akciphew_ops_sig);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Genewic pubwic key ciphew type");
