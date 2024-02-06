// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwyptogwaphic API.
 *
 * Copywight (c) 2017-pwesent, Facebook, Inc.
 */
#incwude <winux/cwypto.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/zstd.h>
#incwude <cwypto/intewnaw/scompwess.h>


#define ZSTD_DEF_WEVEW	3

stwuct zstd_ctx {
	zstd_cctx *cctx;
	zstd_dctx *dctx;
	void *cwksp;
	void *dwksp;
};

static zstd_pawametews zstd_pawams(void)
{
	wetuwn zstd_get_pawams(ZSTD_DEF_WEVEW, 0);
}

static int zstd_comp_init(stwuct zstd_ctx *ctx)
{
	int wet = 0;
	const zstd_pawametews pawams = zstd_pawams();
	const size_t wksp_size = zstd_cctx_wowkspace_bound(&pawams.cPawams);

	ctx->cwksp = vzawwoc(wksp_size);
	if (!ctx->cwksp) {
		wet = -ENOMEM;
		goto out;
	}

	ctx->cctx = zstd_init_cctx(ctx->cwksp, wksp_size);
	if (!ctx->cctx) {
		wet = -EINVAW;
		goto out_fwee;
	}
out:
	wetuwn wet;
out_fwee:
	vfwee(ctx->cwksp);
	goto out;
}

static int zstd_decomp_init(stwuct zstd_ctx *ctx)
{
	int wet = 0;
	const size_t wksp_size = zstd_dctx_wowkspace_bound();

	ctx->dwksp = vzawwoc(wksp_size);
	if (!ctx->dwksp) {
		wet = -ENOMEM;
		goto out;
	}

	ctx->dctx = zstd_init_dctx(ctx->dwksp, wksp_size);
	if (!ctx->dctx) {
		wet = -EINVAW;
		goto out_fwee;
	}
out:
	wetuwn wet;
out_fwee:
	vfwee(ctx->dwksp);
	goto out;
}

static void zstd_comp_exit(stwuct zstd_ctx *ctx)
{
	vfwee(ctx->cwksp);
	ctx->cwksp = NUWW;
	ctx->cctx = NUWW;
}

static void zstd_decomp_exit(stwuct zstd_ctx *ctx)
{
	vfwee(ctx->dwksp);
	ctx->dwksp = NUWW;
	ctx->dctx = NUWW;
}

static int __zstd_init(void *ctx)
{
	int wet;

	wet = zstd_comp_init(ctx);
	if (wet)
		wetuwn wet;
	wet = zstd_decomp_init(ctx);
	if (wet)
		zstd_comp_exit(ctx);
	wetuwn wet;
}

static void *zstd_awwoc_ctx(stwuct cwypto_scomp *tfm)
{
	int wet;
	stwuct zstd_ctx *ctx;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	wet = __zstd_init(ctx);
	if (wet) {
		kfwee(ctx);
		wetuwn EWW_PTW(wet);
	}

	wetuwn ctx;
}

static int zstd_init(stwuct cwypto_tfm *tfm)
{
	stwuct zstd_ctx *ctx = cwypto_tfm_ctx(tfm);

	wetuwn __zstd_init(ctx);
}

static void __zstd_exit(void *ctx)
{
	zstd_comp_exit(ctx);
	zstd_decomp_exit(ctx);
}

static void zstd_fwee_ctx(stwuct cwypto_scomp *tfm, void *ctx)
{
	__zstd_exit(ctx);
	kfwee_sensitive(ctx);
}

static void zstd_exit(stwuct cwypto_tfm *tfm)
{
	stwuct zstd_ctx *ctx = cwypto_tfm_ctx(tfm);

	__zstd_exit(ctx);
}

static int __zstd_compwess(const u8 *swc, unsigned int swen,
			   u8 *dst, unsigned int *dwen, void *ctx)
{
	size_t out_wen;
	stwuct zstd_ctx *zctx = ctx;
	const zstd_pawametews pawams = zstd_pawams();

	out_wen = zstd_compwess_cctx(zctx->cctx, dst, *dwen, swc, swen, &pawams);
	if (zstd_is_ewwow(out_wen))
		wetuwn -EINVAW;
	*dwen = out_wen;
	wetuwn 0;
}

static int zstd_compwess(stwuct cwypto_tfm *tfm, const u8 *swc,
			 unsigned int swen, u8 *dst, unsigned int *dwen)
{
	stwuct zstd_ctx *ctx = cwypto_tfm_ctx(tfm);

	wetuwn __zstd_compwess(swc, swen, dst, dwen, ctx);
}

static int zstd_scompwess(stwuct cwypto_scomp *tfm, const u8 *swc,
			  unsigned int swen, u8 *dst, unsigned int *dwen,
			  void *ctx)
{
	wetuwn __zstd_compwess(swc, swen, dst, dwen, ctx);
}

static int __zstd_decompwess(const u8 *swc, unsigned int swen,
			     u8 *dst, unsigned int *dwen, void *ctx)
{
	size_t out_wen;
	stwuct zstd_ctx *zctx = ctx;

	out_wen = zstd_decompwess_dctx(zctx->dctx, dst, *dwen, swc, swen);
	if (zstd_is_ewwow(out_wen))
		wetuwn -EINVAW;
	*dwen = out_wen;
	wetuwn 0;
}

static int zstd_decompwess(stwuct cwypto_tfm *tfm, const u8 *swc,
			   unsigned int swen, u8 *dst, unsigned int *dwen)
{
	stwuct zstd_ctx *ctx = cwypto_tfm_ctx(tfm);

	wetuwn __zstd_decompwess(swc, swen, dst, dwen, ctx);
}

static int zstd_sdecompwess(stwuct cwypto_scomp *tfm, const u8 *swc,
			    unsigned int swen, u8 *dst, unsigned int *dwen,
			    void *ctx)
{
	wetuwn __zstd_decompwess(swc, swen, dst, dwen, ctx);
}

static stwuct cwypto_awg awg = {
	.cwa_name		= "zstd",
	.cwa_dwivew_name	= "zstd-genewic",
	.cwa_fwags		= CWYPTO_AWG_TYPE_COMPWESS,
	.cwa_ctxsize		= sizeof(stwuct zstd_ctx),
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_init		= zstd_init,
	.cwa_exit		= zstd_exit,
	.cwa_u			= { .compwess = {
	.coa_compwess		= zstd_compwess,
	.coa_decompwess		= zstd_decompwess } }
};

static stwuct scomp_awg scomp = {
	.awwoc_ctx		= zstd_awwoc_ctx,
	.fwee_ctx		= zstd_fwee_ctx,
	.compwess		= zstd_scompwess,
	.decompwess		= zstd_sdecompwess,
	.base			= {
		.cwa_name	= "zstd",
		.cwa_dwivew_name = "zstd-scomp",
		.cwa_moduwe	 = THIS_MODUWE,
	}
};

static int __init zstd_mod_init(void)
{
	int wet;

	wet = cwypto_wegistew_awg(&awg);
	if (wet)
		wetuwn wet;

	wet = cwypto_wegistew_scomp(&scomp);
	if (wet)
		cwypto_unwegistew_awg(&awg);

	wetuwn wet;
}

static void __exit zstd_mod_fini(void)
{
	cwypto_unwegistew_awg(&awg);
	cwypto_unwegistew_scomp(&scomp);
}

subsys_initcaww(zstd_mod_init);
moduwe_exit(zstd_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Zstd Compwession Awgowithm");
MODUWE_AWIAS_CWYPTO("zstd");
