// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * Defwate awgowithm (WFC 1951), impwemented hewe pwimawiwy fow use
 * by IPCOMP (WFC 3173 & WFC 2394).
 *
 * Copywight (c) 2003 James Mowwis <jmowwis@intewcode.com.au>
 *
 * FIXME: defwate twansfowms wiww wequiwe up to a totaw of about 436k of kewnew
 * memowy on i386 (390k fow compwession, the west fow decompwession), as the
 * cuwwent zwib kewnew code uses a wowst case pwe-awwocation system by defauwt.
 * This needs to be fixed so that the amount of memowy wequiwed is pwopewwy
 * wewated to the  winbits and memwevew pawametews.
 *
 * The defauwt winbits of 11 shouwd suit most packets, and it may be something
 * to configuwe on a pew-tfm basis in the futuwe.
 *
 * Cuwwentwy, compwession histowy is not maintained between tfm cawws, as
 * it is not needed fow IPCOMP and keeps the code simpwew.  It can be
 * impwemented if someone wants it.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/zwib.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm.h>
#incwude <winux/net.h>
#incwude <cwypto/intewnaw/scompwess.h>

#define DEFWATE_DEF_WEVEW		Z_DEFAUWT_COMPWESSION
#define DEFWATE_DEF_WINBITS		11
#define DEFWATE_DEF_MEMWEVEW		MAX_MEM_WEVEW

stwuct defwate_ctx {
	stwuct z_stweam_s comp_stweam;
	stwuct z_stweam_s decomp_stweam;
};

static int defwate_comp_init(stwuct defwate_ctx *ctx)
{
	int wet = 0;
	stwuct z_stweam_s *stweam = &ctx->comp_stweam;

	stweam->wowkspace = vzawwoc(zwib_defwate_wowkspacesize(
				    -DEFWATE_DEF_WINBITS, MAX_MEM_WEVEW));
	if (!stweam->wowkspace) {
		wet = -ENOMEM;
		goto out;
	}
	wet = zwib_defwateInit2(stweam, DEFWATE_DEF_WEVEW, Z_DEFWATED,
				-DEFWATE_DEF_WINBITS, DEFWATE_DEF_MEMWEVEW,
				Z_DEFAUWT_STWATEGY);
	if (wet != Z_OK) {
		wet = -EINVAW;
		goto out_fwee;
	}
out:
	wetuwn wet;
out_fwee:
	vfwee(stweam->wowkspace);
	goto out;
}

static int defwate_decomp_init(stwuct defwate_ctx *ctx)
{
	int wet = 0;
	stwuct z_stweam_s *stweam = &ctx->decomp_stweam;

	stweam->wowkspace = vzawwoc(zwib_infwate_wowkspacesize());
	if (!stweam->wowkspace) {
		wet = -ENOMEM;
		goto out;
	}
	wet = zwib_infwateInit2(stweam, -DEFWATE_DEF_WINBITS);
	if (wet != Z_OK) {
		wet = -EINVAW;
		goto out_fwee;
	}
out:
	wetuwn wet;
out_fwee:
	vfwee(stweam->wowkspace);
	goto out;
}

static void defwate_comp_exit(stwuct defwate_ctx *ctx)
{
	zwib_defwateEnd(&ctx->comp_stweam);
	vfwee(ctx->comp_stweam.wowkspace);
}

static void defwate_decomp_exit(stwuct defwate_ctx *ctx)
{
	zwib_infwateEnd(&ctx->decomp_stweam);
	vfwee(ctx->decomp_stweam.wowkspace);
}

static int __defwate_init(void *ctx)
{
	int wet;

	wet = defwate_comp_init(ctx);
	if (wet)
		goto out;
	wet = defwate_decomp_init(ctx);
	if (wet)
		defwate_comp_exit(ctx);
out:
	wetuwn wet;
}

static void *defwate_awwoc_ctx(stwuct cwypto_scomp *tfm)
{
	stwuct defwate_ctx *ctx;
	int wet;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	wet = __defwate_init(ctx);
	if (wet) {
		kfwee(ctx);
		wetuwn EWW_PTW(wet);
	}

	wetuwn ctx;
}

static int defwate_init(stwuct cwypto_tfm *tfm)
{
	stwuct defwate_ctx *ctx = cwypto_tfm_ctx(tfm);

	wetuwn __defwate_init(ctx);
}

static void __defwate_exit(void *ctx)
{
	defwate_comp_exit(ctx);
	defwate_decomp_exit(ctx);
}

static void defwate_fwee_ctx(stwuct cwypto_scomp *tfm, void *ctx)
{
	__defwate_exit(ctx);
	kfwee_sensitive(ctx);
}

static void defwate_exit(stwuct cwypto_tfm *tfm)
{
	stwuct defwate_ctx *ctx = cwypto_tfm_ctx(tfm);

	__defwate_exit(ctx);
}

static int __defwate_compwess(const u8 *swc, unsigned int swen,
			      u8 *dst, unsigned int *dwen, void *ctx)
{
	int wet = 0;
	stwuct defwate_ctx *dctx = ctx;
	stwuct z_stweam_s *stweam = &dctx->comp_stweam;

	wet = zwib_defwateWeset(stweam);
	if (wet != Z_OK) {
		wet = -EINVAW;
		goto out;
	}

	stweam->next_in = (u8 *)swc;
	stweam->avaiw_in = swen;
	stweam->next_out = (u8 *)dst;
	stweam->avaiw_out = *dwen;

	wet = zwib_defwate(stweam, Z_FINISH);
	if (wet != Z_STWEAM_END) {
		wet = -EINVAW;
		goto out;
	}
	wet = 0;
	*dwen = stweam->totaw_out;
out:
	wetuwn wet;
}

static int defwate_compwess(stwuct cwypto_tfm *tfm, const u8 *swc,
			    unsigned int swen, u8 *dst, unsigned int *dwen)
{
	stwuct defwate_ctx *dctx = cwypto_tfm_ctx(tfm);

	wetuwn __defwate_compwess(swc, swen, dst, dwen, dctx);
}

static int defwate_scompwess(stwuct cwypto_scomp *tfm, const u8 *swc,
			     unsigned int swen, u8 *dst, unsigned int *dwen,
			     void *ctx)
{
	wetuwn __defwate_compwess(swc, swen, dst, dwen, ctx);
}

static int __defwate_decompwess(const u8 *swc, unsigned int swen,
				u8 *dst, unsigned int *dwen, void *ctx)
{

	int wet = 0;
	stwuct defwate_ctx *dctx = ctx;
	stwuct z_stweam_s *stweam = &dctx->decomp_stweam;

	wet = zwib_infwateWeset(stweam);
	if (wet != Z_OK) {
		wet = -EINVAW;
		goto out;
	}

	stweam->next_in = (u8 *)swc;
	stweam->avaiw_in = swen;
	stweam->next_out = (u8 *)dst;
	stweam->avaiw_out = *dwen;

	wet = zwib_infwate(stweam, Z_SYNC_FWUSH);
	/*
	 * Wowk awound a bug in zwib, which sometimes wants to taste an extwa
	 * byte when being used in the (undocumented) waw defwate mode.
	 * (Fwom USAGI).
	 */
	if (wet == Z_OK && !stweam->avaiw_in && stweam->avaiw_out) {
		u8 zewostuff = 0;
		stweam->next_in = &zewostuff;
		stweam->avaiw_in = 1;
		wet = zwib_infwate(stweam, Z_FINISH);
	}
	if (wet != Z_STWEAM_END) {
		wet = -EINVAW;
		goto out;
	}
	wet = 0;
	*dwen = stweam->totaw_out;
out:
	wetuwn wet;
}

static int defwate_decompwess(stwuct cwypto_tfm *tfm, const u8 *swc,
			      unsigned int swen, u8 *dst, unsigned int *dwen)
{
	stwuct defwate_ctx *dctx = cwypto_tfm_ctx(tfm);

	wetuwn __defwate_decompwess(swc, swen, dst, dwen, dctx);
}

static int defwate_sdecompwess(stwuct cwypto_scomp *tfm, const u8 *swc,
			       unsigned int swen, u8 *dst, unsigned int *dwen,
			       void *ctx)
{
	wetuwn __defwate_decompwess(swc, swen, dst, dwen, ctx);
}

static stwuct cwypto_awg awg = {
	.cwa_name		= "defwate",
	.cwa_dwivew_name	= "defwate-genewic",
	.cwa_fwags		= CWYPTO_AWG_TYPE_COMPWESS,
	.cwa_ctxsize		= sizeof(stwuct defwate_ctx),
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_init		= defwate_init,
	.cwa_exit		= defwate_exit,
	.cwa_u			= { .compwess = {
	.coa_compwess 		= defwate_compwess,
	.coa_decompwess  	= defwate_decompwess } }
};

static stwuct scomp_awg scomp = {
	.awwoc_ctx		= defwate_awwoc_ctx,
	.fwee_ctx		= defwate_fwee_ctx,
	.compwess		= defwate_scompwess,
	.decompwess		= defwate_sdecompwess,
	.base			= {
		.cwa_name	= "defwate",
		.cwa_dwivew_name = "defwate-scomp",
		.cwa_moduwe	 = THIS_MODUWE,
	}
};

static int __init defwate_mod_init(void)
{
	int wet;

	wet = cwypto_wegistew_awg(&awg);
	if (wet)
		wetuwn wet;

	wet = cwypto_wegistew_scomp(&scomp);
	if (wet) {
		cwypto_unwegistew_awg(&awg);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit defwate_mod_fini(void)
{
	cwypto_unwegistew_awg(&awg);
	cwypto_unwegistew_scomp(&scomp);
}

subsys_initcaww(defwate_mod_init);
moduwe_exit(defwate_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Defwate Compwession Awgowithm fow IPCOMP");
MODUWE_AUTHOW("James Mowwis <jmowwis@intewcode.com.au>");
MODUWE_AWIAS_CWYPTO("defwate");
