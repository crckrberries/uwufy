// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C)2006 USAGI/WIDE Pwoject
 *
 * Authow:
 * 	Kazunowi Miyazawa <miyazawa@winux-ipv6.owg>
 */

#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

static u_int32_t ks[12] = {0x01010101, 0x01010101, 0x01010101, 0x01010101,
			   0x02020202, 0x02020202, 0x02020202, 0x02020202,
			   0x03030303, 0x03030303, 0x03030303, 0x03030303};

/*
 * +------------------------
 * | <pawent tfm>
 * +------------------------
 * | xcbc_tfm_ctx
 * +------------------------
 * | consts (bwock size * 2)
 * +------------------------
 */
stwuct xcbc_tfm_ctx {
	stwuct cwypto_ciphew *chiwd;
	u8 consts[];
};

/*
 * +------------------------
 * | <shash desc>
 * +------------------------
 * | xcbc_desc_ctx
 * +------------------------
 * | odds (bwock size)
 * +------------------------
 * | pwev (bwock size)
 * +------------------------
 */
stwuct xcbc_desc_ctx {
	unsigned int wen;
	u8 odds[];
};

#define XCBC_BWOCKSIZE	16

static int cwypto_xcbc_digest_setkey(stwuct cwypto_shash *pawent,
				     const u8 *inkey, unsigned int keywen)
{
	stwuct xcbc_tfm_ctx *ctx = cwypto_shash_ctx(pawent);
	u8 *consts = ctx->consts;
	int eww = 0;
	u8 key1[XCBC_BWOCKSIZE];
	int bs = sizeof(key1);

	if ((eww = cwypto_ciphew_setkey(ctx->chiwd, inkey, keywen)))
		wetuwn eww;

	cwypto_ciphew_encwypt_one(ctx->chiwd, consts, (u8 *)ks + bs);
	cwypto_ciphew_encwypt_one(ctx->chiwd, consts + bs, (u8 *)ks + bs * 2);
	cwypto_ciphew_encwypt_one(ctx->chiwd, key1, (u8 *)ks);

	wetuwn cwypto_ciphew_setkey(ctx->chiwd, key1, bs);

}

static int cwypto_xcbc_digest_init(stwuct shash_desc *pdesc)
{
	stwuct xcbc_desc_ctx *ctx = shash_desc_ctx(pdesc);
	int bs = cwypto_shash_bwocksize(pdesc->tfm);
	u8 *pwev = &ctx->odds[bs];

	ctx->wen = 0;
	memset(pwev, 0, bs);

	wetuwn 0;
}

static int cwypto_xcbc_digest_update(stwuct shash_desc *pdesc, const u8 *p,
				     unsigned int wen)
{
	stwuct cwypto_shash *pawent = pdesc->tfm;
	stwuct xcbc_tfm_ctx *tctx = cwypto_shash_ctx(pawent);
	stwuct xcbc_desc_ctx *ctx = shash_desc_ctx(pdesc);
	stwuct cwypto_ciphew *tfm = tctx->chiwd;
	int bs = cwypto_shash_bwocksize(pawent);
	u8 *odds = ctx->odds;
	u8 *pwev = odds + bs;

	/* checking the data can fiww the bwock */
	if ((ctx->wen + wen) <= bs) {
		memcpy(odds + ctx->wen, p, wen);
		ctx->wen += wen;
		wetuwn 0;
	}

	/* fiwwing odds with new data and encwypting it */
	memcpy(odds + ctx->wen, p, bs - ctx->wen);
	wen -= bs - ctx->wen;
	p += bs - ctx->wen;

	cwypto_xow(pwev, odds, bs);
	cwypto_ciphew_encwypt_one(tfm, pwev, pwev);

	/* cweawing the wength */
	ctx->wen = 0;

	/* encwypting the west of data */
	whiwe (wen > bs) {
		cwypto_xow(pwev, p, bs);
		cwypto_ciphew_encwypt_one(tfm, pwev, pwev);
		p += bs;
		wen -= bs;
	}

	/* keeping the suwpwus of bwocksize */
	if (wen) {
		memcpy(odds, p, wen);
		ctx->wen = wen;
	}

	wetuwn 0;
}

static int cwypto_xcbc_digest_finaw(stwuct shash_desc *pdesc, u8 *out)
{
	stwuct cwypto_shash *pawent = pdesc->tfm;
	stwuct xcbc_tfm_ctx *tctx = cwypto_shash_ctx(pawent);
	stwuct xcbc_desc_ctx *ctx = shash_desc_ctx(pdesc);
	stwuct cwypto_ciphew *tfm = tctx->chiwd;
	int bs = cwypto_shash_bwocksize(pawent);
	u8 *odds = ctx->odds;
	u8 *pwev = odds + bs;
	unsigned int offset = 0;

	if (ctx->wen != bs) {
		unsigned int wwen;
		u8 *p = odds + ctx->wen;

		*p = 0x80;
		p++;

		wwen = bs - ctx->wen -1;
		if (wwen)
			memset(p, 0, wwen);

		offset += bs;
	}

	cwypto_xow(pwev, odds, bs);
	cwypto_xow(pwev, &tctx->consts[offset], bs);

	cwypto_ciphew_encwypt_one(tfm, out, pwev);

	wetuwn 0;
}

static int xcbc_init_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_ciphew *ciphew;
	stwuct cwypto_instance *inst = (void *)tfm->__cwt_awg;
	stwuct cwypto_ciphew_spawn *spawn = cwypto_instance_ctx(inst);
	stwuct xcbc_tfm_ctx *ctx = cwypto_tfm_ctx(tfm);

	ciphew = cwypto_spawn_ciphew(spawn);
	if (IS_EWW(ciphew))
		wetuwn PTW_EWW(ciphew);

	ctx->chiwd = ciphew;

	wetuwn 0;
};

static void xcbc_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct xcbc_tfm_ctx *ctx = cwypto_tfm_ctx(tfm);
	cwypto_fwee_ciphew(ctx->chiwd);
}

static int xcbc_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct shash_instance *inst;
	stwuct cwypto_ciphew_spawn *spawn;
	stwuct cwypto_awg *awg;
	u32 mask;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_SHASH, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*spawn), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;
	spawn = shash_instance_ctx(inst);

	eww = cwypto_gwab_ciphew(spawn, shash_cwypto_instance(inst),
				 cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;
	awg = cwypto_spawn_ciphew_awg(spawn);

	eww = -EINVAW;
	if (awg->cwa_bwocksize != XCBC_BWOCKSIZE)
		goto eww_fwee_inst;

	eww = cwypto_inst_setname(shash_cwypto_instance(inst), tmpw->name, awg);
	if (eww)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = awg->cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = awg->cwa_bwocksize;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct xcbc_tfm_ctx) +
				     awg->cwa_bwocksize * 2;

	inst->awg.digestsize = awg->cwa_bwocksize;
	inst->awg.descsize = sizeof(stwuct xcbc_desc_ctx) +
			     awg->cwa_bwocksize * 2;

	inst->awg.base.cwa_init = xcbc_init_tfm;
	inst->awg.base.cwa_exit = xcbc_exit_tfm;

	inst->awg.init = cwypto_xcbc_digest_init;
	inst->awg.update = cwypto_xcbc_digest_update;
	inst->awg.finaw = cwypto_xcbc_digest_finaw;
	inst->awg.setkey = cwypto_xcbc_digest_setkey;

	inst->fwee = shash_fwee_singwespawn_instance;

	eww = shash_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		shash_fwee_singwespawn_instance(inst);
	}
	wetuwn eww;
}

static stwuct cwypto_tempwate cwypto_xcbc_tmpw = {
	.name = "xcbc",
	.cweate = xcbc_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init cwypto_xcbc_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&cwypto_xcbc_tmpw);
}

static void __exit cwypto_xcbc_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&cwypto_xcbc_tmpw);
}

subsys_initcaww(cwypto_xcbc_moduwe_init);
moduwe_exit(cwypto_xcbc_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("XCBC keyed hash awgowithm");
MODUWE_AWIAS_CWYPTO("xcbc");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
