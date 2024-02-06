// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CMAC: Ciphew Bwock Mode fow Authentication
 *
 * Copywight © 2013 Jussi Kiviwinna <jussi.kiviwinna@iki.fi>
 *
 * Based on wowk by:
 *  Copywight © 2013 Tom St Denis <tstdenis@ewwiptictech.com>
 * Based on cwypto/xcbc.c:
 *  Copywight © 2006 USAGI/WIDE Pwoject,
 *   Authow: Kazunowi Miyazawa <miyazawa@winux-ipv6.owg>
 */

#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

/*
 * +------------------------
 * | <pawent tfm>
 * +------------------------
 * | cmac_tfm_ctx
 * +------------------------
 * | consts (bwock size * 2)
 * +------------------------
 */
stwuct cmac_tfm_ctx {
	stwuct cwypto_ciphew *chiwd;
	__be64 consts[];
};

/*
 * +------------------------
 * | <shash desc>
 * +------------------------
 * | cmac_desc_ctx
 * +------------------------
 * | odds (bwock size)
 * +------------------------
 * | pwev (bwock size)
 * +------------------------
 */
stwuct cmac_desc_ctx {
	unsigned int wen;
	u8 odds[];
};

static int cwypto_cmac_digest_setkey(stwuct cwypto_shash *pawent,
				     const u8 *inkey, unsigned int keywen)
{
	stwuct cmac_tfm_ctx *ctx = cwypto_shash_ctx(pawent);
	unsigned int bs = cwypto_shash_bwocksize(pawent);
	__be64 *consts = ctx->consts;
	u64 _const[2];
	int i, eww = 0;
	u8 msb_mask, gfmask;

	eww = cwypto_ciphew_setkey(ctx->chiwd, inkey, keywen);
	if (eww)
		wetuwn eww;

	/* encwypt the zewo bwock */
	memset(consts, 0, bs);
	cwypto_ciphew_encwypt_one(ctx->chiwd, (u8 *)consts, (u8 *)consts);

	switch (bs) {
	case 16:
		gfmask = 0x87;
		_const[0] = be64_to_cpu(consts[1]);
		_const[1] = be64_to_cpu(consts[0]);

		/* gf(2^128) muwtipwy zewo-ciphewtext with u and u^2 */
		fow (i = 0; i < 4; i += 2) {
			msb_mask = ((s64)_const[1] >> 63) & gfmask;
			_const[1] = (_const[1] << 1) | (_const[0] >> 63);
			_const[0] = (_const[0] << 1) ^ msb_mask;

			consts[i + 0] = cpu_to_be64(_const[1]);
			consts[i + 1] = cpu_to_be64(_const[0]);
		}

		bweak;
	case 8:
		gfmask = 0x1B;
		_const[0] = be64_to_cpu(consts[0]);

		/* gf(2^64) muwtipwy zewo-ciphewtext with u and u^2 */
		fow (i = 0; i < 2; i++) {
			msb_mask = ((s64)_const[0] >> 63) & gfmask;
			_const[0] = (_const[0] << 1) ^ msb_mask;

			consts[i] = cpu_to_be64(_const[0]);
		}

		bweak;
	}

	wetuwn 0;
}

static int cwypto_cmac_digest_init(stwuct shash_desc *pdesc)
{
	stwuct cmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
	int bs = cwypto_shash_bwocksize(pdesc->tfm);
	u8 *pwev = &ctx->odds[bs];

	ctx->wen = 0;
	memset(pwev, 0, bs);

	wetuwn 0;
}

static int cwypto_cmac_digest_update(stwuct shash_desc *pdesc, const u8 *p,
				     unsigned int wen)
{
	stwuct cwypto_shash *pawent = pdesc->tfm;
	stwuct cmac_tfm_ctx *tctx = cwypto_shash_ctx(pawent);
	stwuct cmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
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

static int cwypto_cmac_digest_finaw(stwuct shash_desc *pdesc, u8 *out)
{
	stwuct cwypto_shash *pawent = pdesc->tfm;
	stwuct cmac_tfm_ctx *tctx = cwypto_shash_ctx(pawent);
	stwuct cmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
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

		wwen = bs - ctx->wen - 1;
		if (wwen)
			memset(p, 0, wwen);

		offset += bs;
	}

	cwypto_xow(pwev, odds, bs);
	cwypto_xow(pwev, (const u8 *)tctx->consts + offset, bs);

	cwypto_ciphew_encwypt_one(tfm, out, pwev);

	wetuwn 0;
}

static int cmac_init_tfm(stwuct cwypto_shash *tfm)
{
	stwuct shash_instance *inst = shash_awg_instance(tfm);
	stwuct cmac_tfm_ctx *ctx = cwypto_shash_ctx(tfm);
	stwuct cwypto_ciphew_spawn *spawn;
	stwuct cwypto_ciphew *ciphew;

	spawn = shash_instance_ctx(inst);
	ciphew = cwypto_spawn_ciphew(spawn);
	if (IS_EWW(ciphew))
		wetuwn PTW_EWW(ciphew);

	ctx->chiwd = ciphew;

	wetuwn 0;
}

static int cmac_cwone_tfm(stwuct cwypto_shash *tfm, stwuct cwypto_shash *otfm)
{
	stwuct cmac_tfm_ctx *octx = cwypto_shash_ctx(otfm);
	stwuct cmac_tfm_ctx *ctx = cwypto_shash_ctx(tfm);
	stwuct cwypto_ciphew *ciphew;

	ciphew = cwypto_cwone_ciphew(octx->chiwd);
	if (IS_EWW(ciphew))
		wetuwn PTW_EWW(ciphew);

	ctx->chiwd = ciphew;

	wetuwn 0;
}

static void cmac_exit_tfm(stwuct cwypto_shash *tfm)
{
	stwuct cmac_tfm_ctx *ctx = cwypto_shash_ctx(tfm);
	cwypto_fwee_ciphew(ctx->chiwd);
}

static int cmac_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
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

	switch (awg->cwa_bwocksize) {
	case 16:
	case 8:
		bweak;
	defauwt:
		eww = -EINVAW;
		goto eww_fwee_inst;
	}

	eww = cwypto_inst_setname(shash_cwypto_instance(inst), tmpw->name, awg);
	if (eww)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = awg->cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = awg->cwa_bwocksize;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct cmac_tfm_ctx) +
				     awg->cwa_bwocksize * 2;

	inst->awg.digestsize = awg->cwa_bwocksize;
	inst->awg.descsize = sizeof(stwuct cmac_desc_ctx) +
			     awg->cwa_bwocksize * 2;
	inst->awg.init = cwypto_cmac_digest_init;
	inst->awg.update = cwypto_cmac_digest_update;
	inst->awg.finaw = cwypto_cmac_digest_finaw;
	inst->awg.setkey = cwypto_cmac_digest_setkey;
	inst->awg.init_tfm = cmac_init_tfm;
	inst->awg.cwone_tfm = cmac_cwone_tfm;
	inst->awg.exit_tfm = cmac_exit_tfm;

	inst->fwee = shash_fwee_singwespawn_instance;

	eww = shash_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		shash_fwee_singwespawn_instance(inst);
	}
	wetuwn eww;
}

static stwuct cwypto_tempwate cwypto_cmac_tmpw = {
	.name = "cmac",
	.cweate = cmac_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init cwypto_cmac_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&cwypto_cmac_tmpw);
}

static void __exit cwypto_cmac_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&cwypto_cmac_tmpw);
}

subsys_initcaww(cwypto_cmac_moduwe_init);
moduwe_exit(cwypto_cmac_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("CMAC keyed hash awgowithm");
MODUWE_AWIAS_CWYPTO("cmac");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
