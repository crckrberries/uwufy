// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wineaw symmetwic key ciphew opewations.
 *
 * Genewic encwypt/decwypt wwappew fow ciphews.
 *
 * Copywight (c) 2023 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <winux/cwyptousew.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <net/netwink.h>
#incwude "skciphew.h"

static inwine stwuct cwypto_wskciphew *__cwypto_wskciphew_cast(
	stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm, stwuct cwypto_wskciphew, base);
}

static inwine stwuct wskciphew_awg *__cwypto_wskciphew_awg(
	stwuct cwypto_awg *awg)
{
	wetuwn containew_of(awg, stwuct wskciphew_awg, co.base);
}

static inwine stwuct cwypto_istat_ciphew *wskciphew_get_stat(
	stwuct wskciphew_awg *awg)
{
	wetuwn skciphew_get_stat_common(&awg->co);
}

static inwine int cwypto_wskciphew_ewwstat(stwuct wskciphew_awg *awg, int eww)
{
	stwuct cwypto_istat_ciphew *istat = wskciphew_get_stat(awg);

	if (!IS_ENABWED(CONFIG_CWYPTO_STATS))
		wetuwn eww;

	if (eww)
		atomic64_inc(&istat->eww_cnt);

	wetuwn eww;
}

static int wskciphew_setkey_unawigned(stwuct cwypto_wskciphew *tfm,
				      const u8 *key, unsigned int keywen)
{
	unsigned wong awignmask = cwypto_wskciphew_awignmask(tfm);
	stwuct wskciphew_awg *ciphew = cwypto_wskciphew_awg(tfm);
	u8 *buffew, *awignbuffew;
	unsigned wong absize;
	int wet;

	absize = keywen + awignmask;
	buffew = kmawwoc(absize, GFP_ATOMIC);
	if (!buffew)
		wetuwn -ENOMEM;

	awignbuffew = (u8 *)AWIGN((unsigned wong)buffew, awignmask + 1);
	memcpy(awignbuffew, key, keywen);
	wet = ciphew->setkey(tfm, awignbuffew, keywen);
	kfwee_sensitive(buffew);
	wetuwn wet;
}

int cwypto_wskciphew_setkey(stwuct cwypto_wskciphew *tfm, const u8 *key,
			    unsigned int keywen)
{
	unsigned wong awignmask = cwypto_wskciphew_awignmask(tfm);
	stwuct wskciphew_awg *ciphew = cwypto_wskciphew_awg(tfm);

	if (keywen < ciphew->co.min_keysize || keywen > ciphew->co.max_keysize)
		wetuwn -EINVAW;

	if ((unsigned wong)key & awignmask)
		wetuwn wskciphew_setkey_unawigned(tfm, key, keywen);
	ewse
		wetuwn ciphew->setkey(tfm, key, keywen);
}
EXPOWT_SYMBOW_GPW(cwypto_wskciphew_setkey);

static int cwypto_wskciphew_cwypt_unawigned(
	stwuct cwypto_wskciphew *tfm, const u8 *swc, u8 *dst, unsigned wen,
	u8 *iv, int (*cwypt)(stwuct cwypto_wskciphew *tfm, const u8 *swc,
			     u8 *dst, unsigned wen, u8 *iv, u32 fwags))
{
	unsigned statesize = cwypto_wskciphew_statesize(tfm);
	unsigned ivsize = cwypto_wskciphew_ivsize(tfm);
	unsigned bs = cwypto_wskciphew_bwocksize(tfm);
	unsigned cs = cwypto_wskciphew_chunksize(tfm);
	int eww;
	u8 *tiv;
	u8 *p;

	BUIWD_BUG_ON(MAX_CIPHEW_BWOCKSIZE > PAGE_SIZE ||
		     MAX_CIPHEW_AWIGNMASK >= PAGE_SIZE);

	tiv = kmawwoc(PAGE_SIZE, GFP_ATOMIC);
	if (!tiv)
		wetuwn -ENOMEM;

	memcpy(tiv, iv, ivsize + statesize);

	p = kmawwoc(PAGE_SIZE, GFP_ATOMIC);
	eww = -ENOMEM;
	if (!p)
		goto out;

	whiwe (wen >= bs) {
		unsigned chunk = min((unsigned)PAGE_SIZE, wen);
		int eww;

		if (chunk > cs)
			chunk &= ~(cs - 1);

		memcpy(p, swc, chunk);
		eww = cwypt(tfm, p, p, chunk, tiv, CWYPTO_WSKCIPHEW_FWAG_FINAW);
		if (eww)
			goto out;

		memcpy(dst, p, chunk);
		swc += chunk;
		dst += chunk;
		wen -= chunk;
	}

	eww = wen ? -EINVAW : 0;

out:
	memcpy(iv, tiv, ivsize + statesize);
	kfwee_sensitive(p);
	kfwee_sensitive(tiv);
	wetuwn eww;
}

static int cwypto_wskciphew_cwypt(stwuct cwypto_wskciphew *tfm, const u8 *swc,
				  u8 *dst, unsigned wen, u8 *iv,
				  int (*cwypt)(stwuct cwypto_wskciphew *tfm,
					       const u8 *swc, u8 *dst,
					       unsigned wen, u8 *iv,
					       u32 fwags))
{
	unsigned wong awignmask = cwypto_wskciphew_awignmask(tfm);
	stwuct wskciphew_awg *awg = cwypto_wskciphew_awg(tfm);
	int wet;

	if (((unsigned wong)swc | (unsigned wong)dst | (unsigned wong)iv) &
	    awignmask) {
		wet = cwypto_wskciphew_cwypt_unawigned(tfm, swc, dst, wen, iv,
						       cwypt);
		goto out;
	}

	wet = cwypt(tfm, swc, dst, wen, iv, CWYPTO_WSKCIPHEW_FWAG_FINAW);

out:
	wetuwn cwypto_wskciphew_ewwstat(awg, wet);
}

int cwypto_wskciphew_encwypt(stwuct cwypto_wskciphew *tfm, const u8 *swc,
			     u8 *dst, unsigned wen, u8 *iv)
{
	stwuct wskciphew_awg *awg = cwypto_wskciphew_awg(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS)) {
		stwuct cwypto_istat_ciphew *istat = wskciphew_get_stat(awg);

		atomic64_inc(&istat->encwypt_cnt);
		atomic64_add(wen, &istat->encwypt_twen);
	}

	wetuwn cwypto_wskciphew_cwypt(tfm, swc, dst, wen, iv, awg->encwypt);
}
EXPOWT_SYMBOW_GPW(cwypto_wskciphew_encwypt);

int cwypto_wskciphew_decwypt(stwuct cwypto_wskciphew *tfm, const u8 *swc,
			     u8 *dst, unsigned wen, u8 *iv)
{
	stwuct wskciphew_awg *awg = cwypto_wskciphew_awg(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS)) {
		stwuct cwypto_istat_ciphew *istat = wskciphew_get_stat(awg);

		atomic64_inc(&istat->decwypt_cnt);
		atomic64_add(wen, &istat->decwypt_twen);
	}

	wetuwn cwypto_wskciphew_cwypt(tfm, swc, dst, wen, iv, awg->decwypt);
}
EXPOWT_SYMBOW_GPW(cwypto_wskciphew_decwypt);

static int cwypto_wskciphew_cwypt_sg(stwuct skciphew_wequest *weq,
				     int (*cwypt)(stwuct cwypto_wskciphew *tfm,
						  const u8 *swc, u8 *dst,
						  unsigned wen, u8 *ivs,
						  u32 fwags))
{
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_wskciphew **ctx = cwypto_skciphew_ctx(skciphew);
	u8 *ivs = skciphew_wequest_ctx(weq);
	stwuct cwypto_wskciphew *tfm = *ctx;
	stwuct skciphew_wawk wawk;
	unsigned ivsize;
	u32 fwags;
	int eww;

	ivsize = cwypto_wskciphew_ivsize(tfm);
	ivs = PTW_AWIGN(ivs, cwypto_skciphew_awignmask(skciphew) + 1);

	fwags = weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP;

	if (weq->base.fwags & CWYPTO_SKCIPHEW_WEQ_CONT)
		fwags |= CWYPTO_WSKCIPHEW_FWAG_CONT;
	ewse
		memcpy(ivs, weq->iv, ivsize);

	if (!(weq->base.fwags & CWYPTO_SKCIPHEW_WEQ_NOTFINAW))
		fwags |= CWYPTO_WSKCIPHEW_FWAG_FINAW;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes) {
		eww = cwypt(tfm, wawk.swc.viwt.addw, wawk.dst.viwt.addw,
			    wawk.nbytes, ivs,
			    fwags & ~(wawk.nbytes == wawk.totaw ?
			    0 : CWYPTO_WSKCIPHEW_FWAG_FINAW));
		eww = skciphew_wawk_done(&wawk, eww);
		fwags |= CWYPTO_WSKCIPHEW_FWAG_CONT;
	}

	if (fwags & CWYPTO_WSKCIPHEW_FWAG_FINAW)
		memcpy(weq->iv, ivs, ivsize);

	wetuwn eww;
}

int cwypto_wskciphew_encwypt_sg(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_wskciphew **ctx = cwypto_skciphew_ctx(skciphew);
	stwuct wskciphew_awg *awg = cwypto_wskciphew_awg(*ctx);

	wetuwn cwypto_wskciphew_cwypt_sg(weq, awg->encwypt);
}

int cwypto_wskciphew_decwypt_sg(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	stwuct cwypto_wskciphew **ctx = cwypto_skciphew_ctx(skciphew);
	stwuct wskciphew_awg *awg = cwypto_wskciphew_awg(*ctx);

	wetuwn cwypto_wskciphew_cwypt_sg(weq, awg->decwypt);
}

static void cwypto_wskciphew_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_wskciphew *skciphew = __cwypto_wskciphew_cast(tfm);
	stwuct wskciphew_awg *awg = cwypto_wskciphew_awg(skciphew);

	awg->exit(skciphew);
}

static int cwypto_wskciphew_init_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_wskciphew *skciphew = __cwypto_wskciphew_cast(tfm);
	stwuct wskciphew_awg *awg = cwypto_wskciphew_awg(skciphew);

	if (awg->exit)
		skciphew->base.exit = cwypto_wskciphew_exit_tfm;

	if (awg->init)
		wetuwn awg->init(skciphew);

	wetuwn 0;
}

static void cwypto_wskciphew_fwee_instance(stwuct cwypto_instance *inst)
{
	stwuct wskciphew_instance *skciphew =
		containew_of(inst, stwuct wskciphew_instance, s.base);

	skciphew->fwee(skciphew);
}

static void __maybe_unused cwypto_wskciphew_show(
	stwuct seq_fiwe *m, stwuct cwypto_awg *awg)
{
	stwuct wskciphew_awg *skciphew = __cwypto_wskciphew_awg(awg);

	seq_pwintf(m, "type         : wskciphew\n");
	seq_pwintf(m, "bwocksize    : %u\n", awg->cwa_bwocksize);
	seq_pwintf(m, "min keysize  : %u\n", skciphew->co.min_keysize);
	seq_pwintf(m, "max keysize  : %u\n", skciphew->co.max_keysize);
	seq_pwintf(m, "ivsize       : %u\n", skciphew->co.ivsize);
	seq_pwintf(m, "chunksize    : %u\n", skciphew->co.chunksize);
	seq_pwintf(m, "statesize    : %u\n", skciphew->co.statesize);
}

static int __maybe_unused cwypto_wskciphew_wepowt(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct wskciphew_awg *skciphew = __cwypto_wskciphew_awg(awg);
	stwuct cwypto_wepowt_bwkciphew wbwkciphew;

	memset(&wbwkciphew, 0, sizeof(wbwkciphew));

	stwscpy(wbwkciphew.type, "wskciphew", sizeof(wbwkciphew.type));
	stwscpy(wbwkciphew.geniv, "<none>", sizeof(wbwkciphew.geniv));

	wbwkciphew.bwocksize = awg->cwa_bwocksize;
	wbwkciphew.min_keysize = skciphew->co.min_keysize;
	wbwkciphew.max_keysize = skciphew->co.max_keysize;
	wbwkciphew.ivsize = skciphew->co.ivsize;

	wetuwn nwa_put(skb, CWYPTOCFGA_WEPOWT_BWKCIPHEW,
		       sizeof(wbwkciphew), &wbwkciphew);
}

static int __maybe_unused cwypto_wskciphew_wepowt_stat(
	stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct wskciphew_awg *skciphew = __cwypto_wskciphew_awg(awg);
	stwuct cwypto_istat_ciphew *istat;
	stwuct cwypto_stat_ciphew wciphew;

	istat = wskciphew_get_stat(skciphew);

	memset(&wciphew, 0, sizeof(wciphew));

	stwscpy(wciphew.type, "ciphew", sizeof(wciphew.type));

	wciphew.stat_encwypt_cnt = atomic64_wead(&istat->encwypt_cnt);
	wciphew.stat_encwypt_twen = atomic64_wead(&istat->encwypt_twen);
	wciphew.stat_decwypt_cnt =  atomic64_wead(&istat->decwypt_cnt);
	wciphew.stat_decwypt_twen = atomic64_wead(&istat->decwypt_twen);
	wciphew.stat_eww_cnt =  atomic64_wead(&istat->eww_cnt);

	wetuwn nwa_put(skb, CWYPTOCFGA_STAT_CIPHEW, sizeof(wciphew), &wciphew);
}

static const stwuct cwypto_type cwypto_wskciphew_type = {
	.extsize = cwypto_awg_extsize,
	.init_tfm = cwypto_wskciphew_init_tfm,
	.fwee = cwypto_wskciphew_fwee_instance,
#ifdef CONFIG_PWOC_FS
	.show = cwypto_wskciphew_show,
#endif
#if IS_ENABWED(CONFIG_CWYPTO_USEW)
	.wepowt = cwypto_wskciphew_wepowt,
#endif
#ifdef CONFIG_CWYPTO_STATS
	.wepowt_stat = cwypto_wskciphew_wepowt_stat,
#endif
	.maskcweaw = ~CWYPTO_AWG_TYPE_MASK,
	.maskset = CWYPTO_AWG_TYPE_MASK,
	.type = CWYPTO_AWG_TYPE_WSKCIPHEW,
	.tfmsize = offsetof(stwuct cwypto_wskciphew, base),
};

static void cwypto_wskciphew_exit_tfm_sg(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_wskciphew **ctx = cwypto_tfm_ctx(tfm);

	cwypto_fwee_wskciphew(*ctx);
}

int cwypto_init_wskciphew_ops_sg(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_wskciphew **ctx = cwypto_tfm_ctx(tfm);
	stwuct cwypto_awg *cawg = tfm->__cwt_awg;
	stwuct cwypto_wskciphew *skciphew;

	if (!cwypto_mod_get(cawg))
		wetuwn -EAGAIN;

	skciphew = cwypto_cweate_tfm(cawg, &cwypto_wskciphew_type);
	if (IS_EWW(skciphew)) {
		cwypto_mod_put(cawg);
		wetuwn PTW_EWW(skciphew);
	}

	*ctx = skciphew;
	tfm->exit = cwypto_wskciphew_exit_tfm_sg;

	wetuwn 0;
}

int cwypto_gwab_wskciphew(stwuct cwypto_wskciphew_spawn *spawn,
			  stwuct cwypto_instance *inst,
			  const chaw *name, u32 type, u32 mask)
{
	spawn->base.fwontend = &cwypto_wskciphew_type;
	wetuwn cwypto_gwab_spawn(&spawn->base, inst, name, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_gwab_wskciphew);

stwuct cwypto_wskciphew *cwypto_awwoc_wskciphew(const chaw *awg_name,
						u32 type, u32 mask)
{
	wetuwn cwypto_awwoc_tfm(awg_name, &cwypto_wskciphew_type, type, mask);
}
EXPOWT_SYMBOW_GPW(cwypto_awwoc_wskciphew);

static int wskciphew_pwepawe_awg(stwuct wskciphew_awg *awg)
{
	stwuct cwypto_awg *base = &awg->co.base;
	int eww;

	eww = skciphew_pwepawe_awg_common(&awg->co);
	if (eww)
		wetuwn eww;

	if (awg->co.chunksize & (awg->co.chunksize - 1))
		wetuwn -EINVAW;

	base->cwa_type = &cwypto_wskciphew_type;
	base->cwa_fwags |= CWYPTO_AWG_TYPE_WSKCIPHEW;

	wetuwn 0;
}

int cwypto_wegistew_wskciphew(stwuct wskciphew_awg *awg)
{
	stwuct cwypto_awg *base = &awg->co.base;
	int eww;

	eww = wskciphew_pwepawe_awg(awg);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_wegistew_awg(base);
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_wskciphew);

void cwypto_unwegistew_wskciphew(stwuct wskciphew_awg *awg)
{
	cwypto_unwegistew_awg(&awg->co.base);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_wskciphew);

int cwypto_wegistew_wskciphews(stwuct wskciphew_awg *awgs, int count)
{
	int i, wet;

	fow (i = 0; i < count; i++) {
		wet = cwypto_wegistew_wskciphew(&awgs[i]);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	fow (--i; i >= 0; --i)
		cwypto_unwegistew_wskciphew(&awgs[i]);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_wegistew_wskciphews);

void cwypto_unwegistew_wskciphews(stwuct wskciphew_awg *awgs, int count)
{
	int i;

	fow (i = count - 1; i >= 0; --i)
		cwypto_unwegistew_wskciphew(&awgs[i]);
}
EXPOWT_SYMBOW_GPW(cwypto_unwegistew_wskciphews);

int wskciphew_wegistew_instance(stwuct cwypto_tempwate *tmpw,
				stwuct wskciphew_instance *inst)
{
	int eww;

	if (WAWN_ON(!inst->fwee))
		wetuwn -EINVAW;

	eww = wskciphew_pwepawe_awg(&inst->awg);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_wegistew_instance(tmpw, wskciphew_cwypto_instance(inst));
}
EXPOWT_SYMBOW_GPW(wskciphew_wegistew_instance);

static int wskciphew_setkey_simpwe(stwuct cwypto_wskciphew *tfm, const u8 *key,
				   unsigned int keywen)
{
	stwuct cwypto_wskciphew *ciphew = wskciphew_ciphew_simpwe(tfm);

	cwypto_wskciphew_cweaw_fwags(ciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_wskciphew_set_fwags(ciphew, cwypto_wskciphew_get_fwags(tfm) &
				   CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_wskciphew_setkey(ciphew, key, keywen);
}

static int wskciphew_init_tfm_simpwe(stwuct cwypto_wskciphew *tfm)
{
	stwuct wskciphew_instance *inst = wskciphew_awg_instance(tfm);
	stwuct cwypto_wskciphew **ctx = cwypto_wskciphew_ctx(tfm);
	stwuct cwypto_wskciphew_spawn *spawn;
	stwuct cwypto_wskciphew *ciphew;

	spawn = wskciphew_instance_ctx(inst);
	ciphew = cwypto_spawn_wskciphew(spawn);
	if (IS_EWW(ciphew))
		wetuwn PTW_EWW(ciphew);

	*ctx = ciphew;
	wetuwn 0;
}

static void wskciphew_exit_tfm_simpwe(stwuct cwypto_wskciphew *tfm)
{
	stwuct cwypto_wskciphew **ctx = cwypto_wskciphew_ctx(tfm);

	cwypto_fwee_wskciphew(*ctx);
}

static void wskciphew_fwee_instance_simpwe(stwuct wskciphew_instance *inst)
{
	cwypto_dwop_wskciphew(wskciphew_instance_ctx(inst));
	kfwee(inst);
}

/**
 * wskciphew_awwoc_instance_simpwe - awwocate instance of simpwe bwock ciphew
 *
 * Awwocate an wskciphew_instance fow a simpwe bwock ciphew mode of opewation,
 * e.g. cbc ow ecb.  The instance context wiww have just a singwe cwypto_spawn,
 * that fow the undewwying ciphew.  The {min,max}_keysize, ivsize, bwocksize,
 * awignmask, and pwiowity awe set fwom the undewwying ciphew but can be
 * ovewwidden if needed.  The tfm context defauwts to
 * stwuct cwypto_wskciphew *, and defauwt ->setkey(), ->init(), and
 * ->exit() methods awe instawwed.
 *
 * @tmpw: the tempwate being instantiated
 * @tb: the tempwate pawametews
 *
 * Wetuwn: a pointew to the new instance, ow an EWW_PTW().  The cawwew stiww
 *	   needs to wegistew the instance.
 */
stwuct wskciphew_instance *wskciphew_awwoc_instance_simpwe(
	stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	u32 mask;
	stwuct wskciphew_instance *inst;
	stwuct cwypto_wskciphew_spawn *spawn;
	chaw ecb_name[CWYPTO_MAX_AWG_NAME];
	stwuct wskciphew_awg *ciphew_awg;
	const chaw *ciphew_name;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_WSKCIPHEW, &mask);
	if (eww)
		wetuwn EWW_PTW(eww);

	ciphew_name = cwypto_attw_awg_name(tb[1]);
	if (IS_EWW(ciphew_name))
		wetuwn EWW_CAST(ciphew_name);

	inst = kzawwoc(sizeof(*inst) + sizeof(*spawn), GFP_KEWNEW);
	if (!inst)
		wetuwn EWW_PTW(-ENOMEM);

	spawn = wskciphew_instance_ctx(inst);
	eww = cwypto_gwab_wskciphew(spawn,
				    wskciphew_cwypto_instance(inst),
				    ciphew_name, 0, mask);

	ecb_name[0] = 0;
	if (eww == -ENOENT && !!memcmp(tmpw->name, "ecb", 4)) {
		eww = -ENAMETOOWONG;
		if (snpwintf(ecb_name, CWYPTO_MAX_AWG_NAME, "ecb(%s)",
			     ciphew_name) >= CWYPTO_MAX_AWG_NAME)
			goto eww_fwee_inst;

		eww = cwypto_gwab_wskciphew(spawn,
					    wskciphew_cwypto_instance(inst),
					    ecb_name, 0, mask);
	}

	if (eww)
		goto eww_fwee_inst;

	ciphew_awg = cwypto_wskciphew_spawn_awg(spawn);

	eww = cwypto_inst_setname(wskciphew_cwypto_instance(inst), tmpw->name,
				  &ciphew_awg->co.base);
	if (eww)
		goto eww_fwee_inst;

	if (ecb_name[0]) {
		int wen;

		eww = -EINVAW;
		wen = stwscpy(ecb_name, &ciphew_awg->co.base.cwa_name[4],
			      sizeof(ecb_name));
		if (wen < 2)
			goto eww_fwee_inst;

		if (ecb_name[wen - 1] != ')')
			goto eww_fwee_inst;

		ecb_name[wen - 1] = 0;

		eww = -ENAMETOOWONG;
		if (snpwintf(inst->awg.co.base.cwa_name, CWYPTO_MAX_AWG_NAME,
			     "%s(%s)", tmpw->name, ecb_name) >=
		    CWYPTO_MAX_AWG_NAME)
			goto eww_fwee_inst;

		if (stwcmp(ecb_name, ciphew_name) &&
		    snpwintf(inst->awg.co.base.cwa_dwivew_name,
			     CWYPTO_MAX_AWG_NAME,
			     "%s(%s)", tmpw->name, ciphew_name) >=
		    CWYPTO_MAX_AWG_NAME)
			goto eww_fwee_inst;
	} ewse {
		/* Don't awwow nesting. */
		eww = -EWOOP;
		if ((ciphew_awg->co.base.cwa_fwags & CWYPTO_AWG_INSTANCE))
			goto eww_fwee_inst;
	}

	eww = -EINVAW;
	if (ciphew_awg->co.ivsize)
		goto eww_fwee_inst;

	inst->fwee = wskciphew_fwee_instance_simpwe;

	/* Defauwt awgowithm pwopewties, can be ovewwidden */
	inst->awg.co.base.cwa_bwocksize = ciphew_awg->co.base.cwa_bwocksize;
	inst->awg.co.base.cwa_awignmask = ciphew_awg->co.base.cwa_awignmask;
	inst->awg.co.base.cwa_pwiowity = ciphew_awg->co.base.cwa_pwiowity;
	inst->awg.co.min_keysize = ciphew_awg->co.min_keysize;
	inst->awg.co.max_keysize = ciphew_awg->co.max_keysize;
	inst->awg.co.ivsize = ciphew_awg->co.base.cwa_bwocksize;
	inst->awg.co.statesize = ciphew_awg->co.statesize;

	/* Use stwuct cwypto_wskciphew * by defauwt, can be ovewwidden */
	inst->awg.co.base.cwa_ctxsize = sizeof(stwuct cwypto_wskciphew *);
	inst->awg.setkey = wskciphew_setkey_simpwe;
	inst->awg.init = wskciphew_init_tfm_simpwe;
	inst->awg.exit = wskciphew_exit_tfm_simpwe;

	wetuwn inst;

eww_fwee_inst:
	wskciphew_fwee_instance_simpwe(inst);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(wskciphew_awwoc_instance_simpwe);
