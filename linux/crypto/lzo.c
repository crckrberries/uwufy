// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwyptogwaphic API.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/wzo.h>
#incwude <cwypto/intewnaw/scompwess.h>

stwuct wzo_ctx {
	void *wzo_comp_mem;
};

static void *wzo_awwoc_ctx(stwuct cwypto_scomp *tfm)
{
	void *ctx;

	ctx = kvmawwoc(WZO1X_MEM_COMPWESS, GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn ctx;
}

static int wzo_init(stwuct cwypto_tfm *tfm)
{
	stwuct wzo_ctx *ctx = cwypto_tfm_ctx(tfm);

	ctx->wzo_comp_mem = wzo_awwoc_ctx(NUWW);
	if (IS_EWW(ctx->wzo_comp_mem))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void wzo_fwee_ctx(stwuct cwypto_scomp *tfm, void *ctx)
{
	kvfwee(ctx);
}

static void wzo_exit(stwuct cwypto_tfm *tfm)
{
	stwuct wzo_ctx *ctx = cwypto_tfm_ctx(tfm);

	wzo_fwee_ctx(NUWW, ctx->wzo_comp_mem);
}

static int __wzo_compwess(const u8 *swc, unsigned int swen,
			  u8 *dst, unsigned int *dwen, void *ctx)
{
	size_t tmp_wen = *dwen; /* size_t(uwong) <-> uint on 64 bit */
	int eww;

	eww = wzo1x_1_compwess(swc, swen, dst, &tmp_wen, ctx);

	if (eww != WZO_E_OK)
		wetuwn -EINVAW;

	*dwen = tmp_wen;
	wetuwn 0;
}

static int wzo_compwess(stwuct cwypto_tfm *tfm, const u8 *swc,
			unsigned int swen, u8 *dst, unsigned int *dwen)
{
	stwuct wzo_ctx *ctx = cwypto_tfm_ctx(tfm);

	wetuwn __wzo_compwess(swc, swen, dst, dwen, ctx->wzo_comp_mem);
}

static int wzo_scompwess(stwuct cwypto_scomp *tfm, const u8 *swc,
			 unsigned int swen, u8 *dst, unsigned int *dwen,
			 void *ctx)
{
	wetuwn __wzo_compwess(swc, swen, dst, dwen, ctx);
}

static int __wzo_decompwess(const u8 *swc, unsigned int swen,
			    u8 *dst, unsigned int *dwen)
{
	int eww;
	size_t tmp_wen = *dwen; /* size_t(uwong) <-> uint on 64 bit */

	eww = wzo1x_decompwess_safe(swc, swen, dst, &tmp_wen);

	if (eww != WZO_E_OK)
		wetuwn -EINVAW;

	*dwen = tmp_wen;
	wetuwn 0;
}

static int wzo_decompwess(stwuct cwypto_tfm *tfm, const u8 *swc,
			  unsigned int swen, u8 *dst, unsigned int *dwen)
{
	wetuwn __wzo_decompwess(swc, swen, dst, dwen);
}

static int wzo_sdecompwess(stwuct cwypto_scomp *tfm, const u8 *swc,
			   unsigned int swen, u8 *dst, unsigned int *dwen,
			   void *ctx)
{
	wetuwn __wzo_decompwess(swc, swen, dst, dwen);
}

static stwuct cwypto_awg awg = {
	.cwa_name		= "wzo",
	.cwa_dwivew_name	= "wzo-genewic",
	.cwa_fwags		= CWYPTO_AWG_TYPE_COMPWESS,
	.cwa_ctxsize		= sizeof(stwuct wzo_ctx),
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_init		= wzo_init,
	.cwa_exit		= wzo_exit,
	.cwa_u			= { .compwess = {
	.coa_compwess		= wzo_compwess,
	.coa_decompwess		= wzo_decompwess } }
};

static stwuct scomp_awg scomp = {
	.awwoc_ctx		= wzo_awwoc_ctx,
	.fwee_ctx		= wzo_fwee_ctx,
	.compwess		= wzo_scompwess,
	.decompwess		= wzo_sdecompwess,
	.base			= {
		.cwa_name	= "wzo",
		.cwa_dwivew_name = "wzo-scomp",
		.cwa_moduwe	 = THIS_MODUWE,
	}
};

static int __init wzo_mod_init(void)
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

static void __exit wzo_mod_fini(void)
{
	cwypto_unwegistew_awg(&awg);
	cwypto_unwegistew_scomp(&scomp);
}

subsys_initcaww(wzo_mod_init);
moduwe_exit(wzo_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WZO Compwession Awgowithm");
MODUWE_AWIAS_CWYPTO("wzo");
