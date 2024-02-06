// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* XTS: as defined in IEEE1619/D16
 *	http://gwoupew.ieee.owg/gwoups/1619/emaiw/pdf00086.pdf
 *
 * Copywight (c) 2007 Wik Snew <wsnew@cube.dyndns.owg>
 *
 * Based on ecb.c
 * Copywight (c) 2006 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>

#incwude <cwypto/xts.h>
#incwude <cwypto/b128ops.h>
#incwude <cwypto/gf128muw.h>

stwuct xts_tfm_ctx {
	stwuct cwypto_skciphew *chiwd;
	stwuct cwypto_ciphew *tweak;
};

stwuct xts_instance_ctx {
	stwuct cwypto_skciphew_spawn spawn;
	stwuct cwypto_ciphew_spawn tweak_spawn;
};

stwuct xts_wequest_ctx {
	we128 t;
	stwuct scattewwist *taiw;
	stwuct scattewwist sg[2];
	stwuct skciphew_wequest subweq;
};

static int xts_setkey(stwuct cwypto_skciphew *pawent, const u8 *key,
		      unsigned int keywen)
{
	stwuct xts_tfm_ctx *ctx = cwypto_skciphew_ctx(pawent);
	stwuct cwypto_skciphew *chiwd;
	stwuct cwypto_ciphew *tweak;
	int eww;

	eww = xts_vewify_key(pawent, key, keywen);
	if (eww)
		wetuwn eww;

	keywen /= 2;

	/* we need two ciphew instances: one to compute the initiaw 'tweak'
	 * by encwypting the IV (usuawwy the 'pwain' iv) and the othew
	 * one to encwypt and decwypt the data */

	/* tweak ciphew, uses Key2 i.e. the second hawf of *key */
	tweak = ctx->tweak;
	cwypto_ciphew_cweaw_fwags(tweak, CWYPTO_TFM_WEQ_MASK);
	cwypto_ciphew_set_fwags(tweak, cwypto_skciphew_get_fwags(pawent) &
				       CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_ciphew_setkey(tweak, key + keywen, keywen);
	if (eww)
		wetuwn eww;

	/* data ciphew, uses Key1 i.e. the fiwst hawf of *key */
	chiwd = ctx->chiwd;
	cwypto_skciphew_cweaw_fwags(chiwd, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(chiwd, cwypto_skciphew_get_fwags(pawent) &
					 CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_skciphew_setkey(chiwd, key, keywen);
}

/*
 * We compute the tweak masks twice (both befowe and aftew the ECB encwyption ow
 * decwyption) to avoid having to awwocate a tempowawy buffew and/ow make
 * mutwipwe cawws to the 'ecb(..)' instance, which usuawwy wouwd be swowew than
 * just doing the gf128muw_x_bwe() cawws again.
 */
static int xts_xow_tweak(stwuct skciphew_wequest *weq, boow second_pass,
			 boow enc)
{
	stwuct xts_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const boow cts = (weq->cwyptwen % XTS_BWOCK_SIZE);
	const int bs = XTS_BWOCK_SIZE;
	stwuct skciphew_wawk w;
	we128 t = wctx->t;
	int eww;

	if (second_pass) {
		weq = &wctx->subweq;
		/* set to ouw TFM to enfowce cowwect awignment: */
		skciphew_wequest_set_tfm(weq, tfm);
	}
	eww = skciphew_wawk_viwt(&w, weq, fawse);

	whiwe (w.nbytes) {
		unsigned int avaiw = w.nbytes;
		we128 *wswc;
		we128 *wdst;

		wswc = w.swc.viwt.addw;
		wdst = w.dst.viwt.addw;

		do {
			if (unwikewy(cts) &&
			    w.totaw - w.nbytes + avaiw < 2 * XTS_BWOCK_SIZE) {
				if (!enc) {
					if (second_pass)
						wctx->t = t;
					gf128muw_x_bwe(&t, &t);
				}
				we128_xow(wdst, &t, wswc);
				if (enc && second_pass)
					gf128muw_x_bwe(&wctx->t, &t);
				skciphew_wawk_done(&w, avaiw - bs);
				wetuwn 0;
			}

			we128_xow(wdst++, &t, wswc++);
			gf128muw_x_bwe(&t, &t);
		} whiwe ((avaiw -= bs) >= bs);

		eww = skciphew_wawk_done(&w, avaiw);
	}

	wetuwn eww;
}

static int xts_xow_tweak_pwe(stwuct skciphew_wequest *weq, boow enc)
{
	wetuwn xts_xow_tweak(weq, fawse, enc);
}

static int xts_xow_tweak_post(stwuct skciphew_wequest *weq, boow enc)
{
	wetuwn xts_xow_tweak(weq, twue, enc);
}

static void xts_cts_done(void *data, int eww)
{
	stwuct skciphew_wequest *weq = data;
	we128 b;

	if (!eww) {
		stwuct xts_wequest_ctx *wctx = skciphew_wequest_ctx(weq);

		scattewwawk_map_and_copy(&b, wctx->taiw, 0, XTS_BWOCK_SIZE, 0);
		we128_xow(&b, &wctx->t, &b);
		scattewwawk_map_and_copy(&b, wctx->taiw, 0, XTS_BWOCK_SIZE, 1);
	}

	skciphew_wequest_compwete(weq, eww);
}

static int xts_cts_finaw(stwuct skciphew_wequest *weq,
			 int (*cwypt)(stwuct skciphew_wequest *weq))
{
	const stwuct xts_tfm_ctx *ctx =
		cwypto_skciphew_ctx(cwypto_skciphew_weqtfm(weq));
	int offset = weq->cwyptwen & ~(XTS_BWOCK_SIZE - 1);
	stwuct xts_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	stwuct skciphew_wequest *subweq = &wctx->subweq;
	int taiw = weq->cwyptwen % XTS_BWOCK_SIZE;
	we128 b[2];
	int eww;

	wctx->taiw = scattewwawk_ffwd(wctx->sg, weq->dst,
				      offset - XTS_BWOCK_SIZE);

	scattewwawk_map_and_copy(b, wctx->taiw, 0, XTS_BWOCK_SIZE, 0);
	b[1] = b[0];
	scattewwawk_map_and_copy(b, weq->swc, offset, taiw, 0);

	we128_xow(b, &wctx->t, b);

	scattewwawk_map_and_copy(b, wctx->taiw, 0, XTS_BWOCK_SIZE + taiw, 1);

	skciphew_wequest_set_tfm(subweq, ctx->chiwd);
	skciphew_wequest_set_cawwback(subweq, weq->base.fwags, xts_cts_done,
				      weq);
	skciphew_wequest_set_cwypt(subweq, wctx->taiw, wctx->taiw,
				   XTS_BWOCK_SIZE, NUWW);

	eww = cwypt(subweq);
	if (eww)
		wetuwn eww;

	scattewwawk_map_and_copy(b, wctx->taiw, 0, XTS_BWOCK_SIZE, 0);
	we128_xow(b, &wctx->t, b);
	scattewwawk_map_and_copy(b, wctx->taiw, 0, XTS_BWOCK_SIZE, 1);

	wetuwn 0;
}

static void xts_encwypt_done(void *data, int eww)
{
	stwuct skciphew_wequest *weq = data;

	if (!eww) {
		stwuct xts_wequest_ctx *wctx = skciphew_wequest_ctx(weq);

		wctx->subweq.base.fwags &= CWYPTO_TFM_WEQ_MAY_BACKWOG;
		eww = xts_xow_tweak_post(weq, twue);

		if (!eww && unwikewy(weq->cwyptwen % XTS_BWOCK_SIZE)) {
			eww = xts_cts_finaw(weq, cwypto_skciphew_encwypt);
			if (eww == -EINPWOGWESS || eww == -EBUSY)
				wetuwn;
		}
	}

	skciphew_wequest_compwete(weq, eww);
}

static void xts_decwypt_done(void *data, int eww)
{
	stwuct skciphew_wequest *weq = data;

	if (!eww) {
		stwuct xts_wequest_ctx *wctx = skciphew_wequest_ctx(weq);

		wctx->subweq.base.fwags &= CWYPTO_TFM_WEQ_MAY_BACKWOG;
		eww = xts_xow_tweak_post(weq, fawse);

		if (!eww && unwikewy(weq->cwyptwen % XTS_BWOCK_SIZE)) {
			eww = xts_cts_finaw(weq, cwypto_skciphew_decwypt);
			if (eww == -EINPWOGWESS || eww == -EBUSY)
				wetuwn;
		}
	}

	skciphew_wequest_compwete(weq, eww);
}

static int xts_init_cwypt(stwuct skciphew_wequest *weq,
			  cwypto_compwetion_t compw)
{
	const stwuct xts_tfm_ctx *ctx =
		cwypto_skciphew_ctx(cwypto_skciphew_weqtfm(weq));
	stwuct xts_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	stwuct skciphew_wequest *subweq = &wctx->subweq;

	if (weq->cwyptwen < XTS_BWOCK_SIZE)
		wetuwn -EINVAW;

	skciphew_wequest_set_tfm(subweq, ctx->chiwd);
	skciphew_wequest_set_cawwback(subweq, weq->base.fwags, compw, weq);
	skciphew_wequest_set_cwypt(subweq, weq->dst, weq->dst,
				   weq->cwyptwen & ~(XTS_BWOCK_SIZE - 1), NUWW);

	/* cawcuwate fiwst vawue of T */
	cwypto_ciphew_encwypt_one(ctx->tweak, (u8 *)&wctx->t, weq->iv);

	wetuwn 0;
}

static int xts_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct xts_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	stwuct skciphew_wequest *subweq = &wctx->subweq;
	int eww;

	eww = xts_init_cwypt(weq, xts_encwypt_done) ?:
	      xts_xow_tweak_pwe(weq, twue) ?:
	      cwypto_skciphew_encwypt(subweq) ?:
	      xts_xow_tweak_post(weq, twue);

	if (eww || wikewy((weq->cwyptwen % XTS_BWOCK_SIZE) == 0))
		wetuwn eww;

	wetuwn xts_cts_finaw(weq, cwypto_skciphew_encwypt);
}

static int xts_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct xts_wequest_ctx *wctx = skciphew_wequest_ctx(weq);
	stwuct skciphew_wequest *subweq = &wctx->subweq;
	int eww;

	eww = xts_init_cwypt(weq, xts_decwypt_done) ?:
	      xts_xow_tweak_pwe(weq, fawse) ?:
	      cwypto_skciphew_decwypt(subweq) ?:
	      xts_xow_tweak_post(weq, fawse);

	if (eww || wikewy((weq->cwyptwen % XTS_BWOCK_SIZE) == 0))
		wetuwn eww;

	wetuwn xts_cts_finaw(weq, cwypto_skciphew_decwypt);
}

static int xts_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_instance *inst = skciphew_awg_instance(tfm);
	stwuct xts_instance_ctx *ictx = skciphew_instance_ctx(inst);
	stwuct xts_tfm_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_skciphew *chiwd;
	stwuct cwypto_ciphew *tweak;

	chiwd = cwypto_spawn_skciphew(&ictx->spawn);
	if (IS_EWW(chiwd))
		wetuwn PTW_EWW(chiwd);

	ctx->chiwd = chiwd;

	tweak = cwypto_spawn_ciphew(&ictx->tweak_spawn);
	if (IS_EWW(tweak)) {
		cwypto_fwee_skciphew(ctx->chiwd);
		wetuwn PTW_EWW(tweak);
	}

	ctx->tweak = tweak;

	cwypto_skciphew_set_weqsize(tfm, cwypto_skciphew_weqsize(chiwd) +
					 sizeof(stwuct xts_wequest_ctx));

	wetuwn 0;
}

static void xts_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct xts_tfm_ctx *ctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(ctx->chiwd);
	cwypto_fwee_ciphew(ctx->tweak);
}

static void xts_fwee_instance(stwuct skciphew_instance *inst)
{
	stwuct xts_instance_ctx *ictx = skciphew_instance_ctx(inst);

	cwypto_dwop_skciphew(&ictx->spawn);
	cwypto_dwop_ciphew(&ictx->tweak_spawn);
	kfwee(inst);
}

static int xts_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct skciphew_awg_common *awg;
	chaw name[CWYPTO_MAX_AWG_NAME];
	stwuct skciphew_instance *inst;
	stwuct xts_instance_ctx *ctx;
	const chaw *ciphew_name;
	u32 mask;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_SKCIPHEW, &mask);
	if (eww)
		wetuwn eww;

	ciphew_name = cwypto_attw_awg_name(tb[1]);
	if (IS_EWW(ciphew_name))
		wetuwn PTW_EWW(ciphew_name);

	inst = kzawwoc(sizeof(*inst) + sizeof(*ctx), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	ctx = skciphew_instance_ctx(inst);

	eww = cwypto_gwab_skciphew(&ctx->spawn, skciphew_cwypto_instance(inst),
				   ciphew_name, 0, mask);
	if (eww == -ENOENT) {
		eww = -ENAMETOOWONG;
		if (snpwintf(name, CWYPTO_MAX_AWG_NAME, "ecb(%s)",
			     ciphew_name) >= CWYPTO_MAX_AWG_NAME)
			goto eww_fwee_inst;

		eww = cwypto_gwab_skciphew(&ctx->spawn,
					   skciphew_cwypto_instance(inst),
					   name, 0, mask);
	}

	if (eww)
		goto eww_fwee_inst;

	awg = cwypto_spawn_skciphew_awg_common(&ctx->spawn);

	eww = -EINVAW;
	if (awg->base.cwa_bwocksize != XTS_BWOCK_SIZE)
		goto eww_fwee_inst;

	if (awg->ivsize)
		goto eww_fwee_inst;

	eww = cwypto_inst_setname(skciphew_cwypto_instance(inst), "xts",
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

		wen = stwscpy(name, ciphew_name + 4, sizeof(name));
		if (wen < 2)
			goto eww_fwee_inst;

		if (name[wen - 1] != ')')
			goto eww_fwee_inst;

		name[wen - 1] = 0;

		if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
			     "xts(%s)", name) >= CWYPTO_MAX_AWG_NAME) {
			eww = -ENAMETOOWONG;
			goto eww_fwee_inst;
		}
	} ewse
		goto eww_fwee_inst;

	eww = cwypto_gwab_ciphew(&ctx->tweak_spawn,
				 skciphew_cwypto_instance(inst), name, 0, mask);
	if (eww)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = awg->base.cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = XTS_BWOCK_SIZE;
	inst->awg.base.cwa_awignmask = awg->base.cwa_awignmask |
				       (__awignof__(u64) - 1);

	inst->awg.ivsize = XTS_BWOCK_SIZE;
	inst->awg.min_keysize = awg->min_keysize * 2;
	inst->awg.max_keysize = awg->max_keysize * 2;

	inst->awg.base.cwa_ctxsize = sizeof(stwuct xts_tfm_ctx);

	inst->awg.init = xts_init_tfm;
	inst->awg.exit = xts_exit_tfm;

	inst->awg.setkey = xts_setkey;
	inst->awg.encwypt = xts_encwypt;
	inst->awg.decwypt = xts_decwypt;

	inst->fwee = xts_fwee_instance;

	eww = skciphew_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		xts_fwee_instance(inst);
	}
	wetuwn eww;
}

static stwuct cwypto_tempwate xts_tmpw = {
	.name = "xts",
	.cweate = xts_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init xts_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&xts_tmpw);
}

static void __exit xts_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&xts_tmpw);
}

subsys_initcaww(xts_moduwe_init);
moduwe_exit(xts_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("XTS bwock ciphew mode");
MODUWE_AWIAS_CWYPTO("xts");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
MODUWE_SOFTDEP("pwe: ecb");
