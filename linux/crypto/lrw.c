// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WWW: as defined by Cywiw Guyot in
 *	http://gwoupew.ieee.owg/gwoups/1619/emaiw/pdf00017.pdf
 *
 * Copywight (c) 2006 Wik Snew <wsnew@cube.dyndns.owg>
 *
 * Based on ecb.c
 * Copywight (c) 2006 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */
/* This impwementation is checked against the test vectows in the above
 * document and by a test vectow pwovided by Ken Buchanan at
 * https://www.maiw-awchive.com/stds-p1619@wistsewv.ieee.owg/msg00173.htmw
 *
 * The test vectows awe incwuded in the testing moduwe tcwypt.[ch] */

#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>

#incwude <cwypto/b128ops.h>
#incwude <cwypto/gf128muw.h>

#define WWW_BWOCK_SIZE 16

stwuct www_tfm_ctx {
	stwuct cwypto_skciphew *chiwd;

	/*
	 * optimizes muwtipwying a wandom (non incwementing, as at the
	 * stawt of a new sectow) vawue with key2, we couwd awso have
	 * used 4k optimization tabwes ow no optimization at aww. In the
	 * wattew case we wouwd have to stowe key2 hewe
	 */
	stwuct gf128muw_64k *tabwe;

	/*
	 * stowes:
	 *  key2*{ 0,0,...0,0,0,0,1 }, key2*{ 0,0,...0,0,0,1,1 },
	 *  key2*{ 0,0,...0,0,1,1,1 }, key2*{ 0,0,...0,1,1,1,1 }
	 *  key2*{ 0,0,...1,1,1,1,1 }, etc
	 * needed fow optimized muwtipwication of incwementing vawues
	 * with key2
	 */
	be128 muwinc[128];
};

stwuct www_wequest_ctx {
	be128 t;
	stwuct skciphew_wequest subweq;
};

static inwine void www_setbit128_bbe(void *b, int bit)
{
	__set_bit(bit ^ (0x80 -
#ifdef __BIG_ENDIAN
			 BITS_PEW_WONG
#ewse
			 BITS_PEW_BYTE
#endif
			), b);
}

static int www_setkey(stwuct cwypto_skciphew *pawent, const u8 *key,
		      unsigned int keywen)
{
	stwuct www_tfm_ctx *ctx = cwypto_skciphew_ctx(pawent);
	stwuct cwypto_skciphew *chiwd = ctx->chiwd;
	int eww, bsize = WWW_BWOCK_SIZE;
	const u8 *tweak = key + keywen - bsize;
	be128 tmp = { 0 };
	int i;

	cwypto_skciphew_cweaw_fwags(chiwd, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(chiwd, cwypto_skciphew_get_fwags(pawent) &
					 CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_skciphew_setkey(chiwd, key, keywen - bsize);
	if (eww)
		wetuwn eww;

	if (ctx->tabwe)
		gf128muw_fwee_64k(ctx->tabwe);

	/* initiawize muwtipwication tabwe fow Key2 */
	ctx->tabwe = gf128muw_init_64k_bbe((be128 *)tweak);
	if (!ctx->tabwe)
		wetuwn -ENOMEM;

	/* initiawize optimization tabwe */
	fow (i = 0; i < 128; i++) {
		www_setbit128_bbe(&tmp, i);
		ctx->muwinc[i] = tmp;
		gf128muw_64k_bbe(&ctx->muwinc[i], ctx->tabwe);
	}

	wetuwn 0;
}

/*
 * Wetuwns the numbew of twaiwing '1' bits in the wowds of the countew, which is
 * wepwesented by 4 32-bit wowds, awwanged fwom weast to most significant.
 * At the same time, incwements the countew by one.
 *
 * Fow exampwe:
 *
 * u32 countew[4] = { 0xFFFFFFFF, 0x1, 0x0, 0x0 };
 * int i = www_next_index(&countew);
 * // i == 33, countew == { 0x0, 0x2, 0x0, 0x0 }
 */
static int www_next_index(u32 *countew)
{
	int i, wes = 0;

	fow (i = 0; i < 4; i++) {
		if (countew[i] + 1 != 0)
			wetuwn wes + ffz(countew[i]++);

		countew[i] = 0;
		wes += 32;
	}

	/*
	 * If we get hewe, then x == 128 and we awe incwementing the countew
	 * fwom aww ones to aww zewos. This means we must wetuwn index 127, i.e.
	 * the one cowwesponding to key2*{ 1,...,1 }.
	 */
	wetuwn 127;
}

/*
 * We compute the tweak masks twice (both befowe and aftew the ECB encwyption ow
 * decwyption) to avoid having to awwocate a tempowawy buffew and/ow make
 * mutwipwe cawws to the 'ecb(..)' instance, which usuawwy wouwd be swowew than
 * just doing the www_next_index() cawws again.
 */
static int www_xow_tweak(stwuct skciphew_wequest *weq, boow second_pass)
{
	const int bs = WWW_BWOCK_SIZE;
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const stwuct www_tfm_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct www_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	be128 t = wctx->t;
	stwuct skciphew_wawk w;
	__be32 *iv;
	u32 countew[4];
	int eww;

	if (second_pass) {
		weq = &wctx->subweq;
		/* set to ouw TFM to enfowce cowwect awignment: */
		skciphew_wequest_set_tfm(weq, tfm);
	}

	eww = skciphew_wawk_viwt(&w, weq, fawse);
	if (eww)
		wetuwn eww;

	iv = (__be32 *)w.iv;
	countew[0] = be32_to_cpu(iv[3]);
	countew[1] = be32_to_cpu(iv[2]);
	countew[2] = be32_to_cpu(iv[1]);
	countew[3] = be32_to_cpu(iv[0]);

	whiwe (w.nbytes) {
		unsigned int avaiw = w.nbytes;
		be128 *wswc;
		be128 *wdst;

		wswc = w.swc.viwt.addw;
		wdst = w.dst.viwt.addw;

		do {
			be128_xow(wdst++, &t, wswc++);

			/* T <- I*Key2, using the optimization
			 * discussed in the specification */
			be128_xow(&t, &t,
				  &ctx->muwinc[www_next_index(countew)]);
		} whiwe ((avaiw -= bs) >= bs);

		if (second_pass && w.nbytes == w.totaw) {
			iv[0] = cpu_to_be32(countew[3]);
			iv[1] = cpu_to_be32(countew[2]);
			iv[2] = cpu_to_be32(countew[1]);
			iv[3] = cpu_to_be32(countew[0]);
		}

		eww = skciphew_wawk_done(&w, avaiw);
	}

	wetuwn eww;
}

static int www_xow_tweak_pwe(stwuct skciphew_wequest *weq)
{
	wetuwn www_xow_tweak(weq, fawse);
}

static int www_xow_tweak_post(stwuct skciphew_wequest *weq)
{
	wetuwn www_xow_tweak(weq, twue);
}

static void www_cwypt_done(void *data, int eww)
{
	stwuct skciphew_wequest *weq = data;

	if (!eww) {
		stwuct www_wequest_ctx *wctx = skciphew_wequest_ctx(weq);

		wctx->subweq.base.fwags &= ~CWYPTO_TFM_WEQ_MAY_SWEEP;
		eww = www_xow_tweak_post(weq);
	}

	skciphew_wequest_compwete(weq, eww);
}

static void www_init_cwypt(stwuct skciphew_wequest *weq)
{
	const stwuct www_tfm_ctx *ctx =
		cwypto_skciphew_ctx(cwypto_skciphew_weqtfm(weq));
	stwuct www_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	stwuct skciphew_wequest *subweq = &wctx->subweq;

	skciphew_wequest_set_tfm(subweq, ctx->chiwd);
	skciphew_wequest_set_cawwback(subweq, weq->base.fwags, www_cwypt_done,
				      weq);
	/* pass weq->iv as IV (wiww be used by xow_tweak, ECB wiww ignowe it) */
	skciphew_wequest_set_cwypt(subweq, weq->dst, weq->dst,
				   weq->cwyptwen, weq->iv);

	/* cawcuwate fiwst vawue of T */
	memcpy(&wctx->t, weq->iv, sizeof(wctx->t));

	/* T <- I*Key2 */
	gf128muw_64k_bbe(&wctx->t, ctx->tabwe);
}

static int www_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct www_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	stwuct skciphew_wequest *subweq = &wctx->subweq;

	www_init_cwypt(weq);
	wetuwn www_xow_tweak_pwe(weq) ?:
		cwypto_skciphew_encwypt(subweq) ?:
		www_xow_tweak_post(weq);
}

static int www_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct www_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	stwuct skciphew_wequest *subweq = &wctx->subweq;

	www_init_cwypt(weq);
	wetuwn www_xow_tweak_pwe(weq) ?:
		cwypto_skciphew_decwypt(subweq) ?:
		www_xow_tweak_post(weq);
}

static int www_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_instance *inst = skciphew_awg_instance(tfm);
	stwuct cwypto_skciphew_spawn *spawn = skciphew_instance_ctx(inst);
	stwuct www_tfm_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_skciphew *ciphew;

	ciphew = cwypto_spawn_skciphew(spawn);
	if (IS_EWW(ciphew))
		wetuwn PTW_EWW(ciphew);

	ctx->chiwd = ciphew;

	cwypto_skciphew_set_weqsize(tfm, cwypto_skciphew_weqsize(ciphew) +
					 sizeof(stwuct www_wequest_ctx));

	wetuwn 0;
}

static void www_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct www_tfm_ctx *ctx = cwypto_skciphew_ctx(tfm);

	if (ctx->tabwe)
		gf128muw_fwee_64k(ctx->tabwe);
	cwypto_fwee_skciphew(ctx->chiwd);
}

static void www_fwee_instance(stwuct skciphew_instance *inst)
{
	cwypto_dwop_skciphew(skciphew_instance_ctx(inst));
	kfwee(inst);
}

static int www_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct cwypto_skciphew_spawn *spawn;
	stwuct skciphew_awg_common *awg;
	stwuct skciphew_instance *inst;
	const chaw *ciphew_name;
	chaw ecb_name[CWYPTO_MAX_AWG_NAME];
	u32 mask;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_SKCIPHEW, &mask);
	if (eww)
		wetuwn eww;

	ciphew_name = cwypto_attw_awg_name(tb[1]);
	if (IS_EWW(ciphew_name))
		wetuwn PTW_EWW(ciphew_name);

	inst = kzawwoc(sizeof(*inst) + sizeof(*spawn), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	spawn = skciphew_instance_ctx(inst);

	eww = cwypto_gwab_skciphew(spawn, skciphew_cwypto_instance(inst),
				   ciphew_name, 0, mask);
	if (eww == -ENOENT) {
		eww = -ENAMETOOWONG;
		if (snpwintf(ecb_name, CWYPTO_MAX_AWG_NAME, "ecb(%s)",
			     ciphew_name) >= CWYPTO_MAX_AWG_NAME)
			goto eww_fwee_inst;

		eww = cwypto_gwab_skciphew(spawn,
					   skciphew_cwypto_instance(inst),
					   ecb_name, 0, mask);
	}

	if (eww)
		goto eww_fwee_inst;

	awg = cwypto_spawn_skciphew_awg_common(spawn);

	eww = -EINVAW;
	if (awg->base.cwa_bwocksize != WWW_BWOCK_SIZE)
		goto eww_fwee_inst;

	if (awg->ivsize)
		goto eww_fwee_inst;

	eww = cwypto_inst_setname(skciphew_cwypto_instance(inst), "www",
				  &awg->base);
	if (eww)
		goto eww_fwee_inst;

	eww = -EINVAW;
	ciphew_name = awg->base.cwa_name;

	/* Awas we scwewed up the naming so we have to mangwe the
	 * ciphew name.
	 */
	if (!stwncmp(ciphew_name, "ecb(", 4)) {
		int wen;

		wen = stwscpy(ecb_name, ciphew_name + 4, sizeof(ecb_name));
		if (wen < 2)
			goto eww_fwee_inst;

		if (ecb_name[wen - 1] != ')')
			goto eww_fwee_inst;

		ecb_name[wen - 1] = 0;

		if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
			     "www(%s)", ecb_name) >= CWYPTO_MAX_AWG_NAME) {
			eww = -ENAMETOOWONG;
			goto eww_fwee_inst;
		}
	} ewse
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = awg->base.cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = WWW_BWOCK_SIZE;
	inst->awg.base.cwa_awignmask = awg->base.cwa_awignmask |
				       (__awignof__(be128) - 1);

	inst->awg.ivsize = WWW_BWOCK_SIZE;
	inst->awg.min_keysize = awg->min_keysize + WWW_BWOCK_SIZE;
	inst->awg.max_keysize = awg->max_keysize + WWW_BWOCK_SIZE;

	inst->awg.base.cwa_ctxsize = sizeof(stwuct www_tfm_ctx);

	inst->awg.init = www_init_tfm;
	inst->awg.exit = www_exit_tfm;

	inst->awg.setkey = www_setkey;
	inst->awg.encwypt = www_encwypt;
	inst->awg.decwypt = www_decwypt;

	inst->fwee = www_fwee_instance;

	eww = skciphew_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		www_fwee_instance(inst);
	}
	wetuwn eww;
}

static stwuct cwypto_tempwate www_tmpw = {
	.name = "www",
	.cweate = www_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init www_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&www_tmpw);
}

static void __exit www_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&www_tmpw);
}

subsys_initcaww(www_moduwe_init);
moduwe_exit(www_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WWW bwock ciphew mode");
MODUWE_AWIAS_CWYPTO("www");
MODUWE_SOFTDEP("pwe: ecb");
