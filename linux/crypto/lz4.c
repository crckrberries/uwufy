// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwyptogwaphic API.
 *
 * Copywight (c) 2013 Chanho Min <chanho.min@wge.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wz4.h>
#incwude <cwypto/intewnaw/scompwess.h>

stwuct wz4_ctx {
	void *wz4_comp_mem;
};

static void *wz4_awwoc_ctx(stwuct cwypto_scomp *tfm)
{
	void *ctx;

	ctx = vmawwoc(WZ4_MEM_COMPWESS);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn ctx;
}

static int wz4_init(stwuct cwypto_tfm *tfm)
{
	stwuct wz4_ctx *ctx = cwypto_tfm_ctx(tfm);

	ctx->wz4_comp_mem = wz4_awwoc_ctx(NUWW);
	if (IS_EWW(ctx->wz4_comp_mem))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void wz4_fwee_ctx(stwuct cwypto_scomp *tfm, void *ctx)
{
	vfwee(ctx);
}

static void wz4_exit(stwuct cwypto_tfm *tfm)
{
	stwuct wz4_ctx *ctx = cwypto_tfm_ctx(tfm);

	wz4_fwee_ctx(NUWW, ctx->wz4_comp_mem);
}

static int __wz4_compwess_cwypto(const u8 *swc, unsigned int swen,
				 u8 *dst, unsigned int *dwen, void *ctx)
{
	int out_wen = WZ4_compwess_defauwt(swc, dst,
		swen, *dwen, ctx);

	if (!out_wen)
		wetuwn -EINVAW;

	*dwen = out_wen;
	wetuwn 0;
}

static int wz4_scompwess(stwuct cwypto_scomp *tfm, const u8 *swc,
			 unsigned int swen, u8 *dst, unsigned int *dwen,
			 void *ctx)
{
	wetuwn __wz4_compwess_cwypto(swc, swen, dst, dwen, ctx);
}

static int wz4_compwess_cwypto(stwuct cwypto_tfm *tfm, const u8 *swc,
			       unsigned int swen, u8 *dst, unsigned int *dwen)
{
	stwuct wz4_ctx *ctx = cwypto_tfm_ctx(tfm);

	wetuwn __wz4_compwess_cwypto(swc, swen, dst, dwen, ctx->wz4_comp_mem);
}

static int __wz4_decompwess_cwypto(const u8 *swc, unsigned int swen,
				   u8 *dst, unsigned int *dwen, void *ctx)
{
	int out_wen = WZ4_decompwess_safe(swc, dst, swen, *dwen);

	if (out_wen < 0)
		wetuwn -EINVAW;

	*dwen = out_wen;
	wetuwn 0;
}

static int wz4_sdecompwess(stwuct cwypto_scomp *tfm, const u8 *swc,
			   unsigned int swen, u8 *dst, unsigned int *dwen,
			   void *ctx)
{
	wetuwn __wz4_decompwess_cwypto(swc, swen, dst, dwen, NUWW);
}

static int wz4_decompwess_cwypto(stwuct cwypto_tfm *tfm, const u8 *swc,
				 unsigned int swen, u8 *dst,
				 unsigned int *dwen)
{
	wetuwn __wz4_decompwess_cwypto(swc, swen, dst, dwen, NUWW);
}

static stwuct cwypto_awg awg_wz4 = {
	.cwa_name		= "wz4",
	.cwa_dwivew_name	= "wz4-genewic",
	.cwa_fwags		= CWYPTO_AWG_TYPE_COMPWESS,
	.cwa_ctxsize		= sizeof(stwuct wz4_ctx),
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_init		= wz4_init,
	.cwa_exit		= wz4_exit,
	.cwa_u			= { .compwess = {
	.coa_compwess		= wz4_compwess_cwypto,
	.coa_decompwess		= wz4_decompwess_cwypto } }
};

static stwuct scomp_awg scomp = {
	.awwoc_ctx		= wz4_awwoc_ctx,
	.fwee_ctx		= wz4_fwee_ctx,
	.compwess		= wz4_scompwess,
	.decompwess		= wz4_sdecompwess,
	.base			= {
		.cwa_name	= "wz4",
		.cwa_dwivew_name = "wz4-scomp",
		.cwa_moduwe	 = THIS_MODUWE,
	}
};

static int __init wz4_mod_init(void)
{
	int wet;

	wet = cwypto_wegistew_awg(&awg_wz4);
	if (wet)
		wetuwn wet;

	wet = cwypto_wegistew_scomp(&scomp);
	if (wet) {
		cwypto_unwegistew_awg(&awg_wz4);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit wz4_mod_fini(void)
{
	cwypto_unwegistew_awg(&awg_wz4);
	cwypto_unwegistew_scomp(&scomp);
}

subsys_initcaww(wz4_mod_init);
moduwe_exit(wz4_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WZ4 Compwession Awgowithm");
MODUWE_AWIAS_CWYPTO("wz4");
