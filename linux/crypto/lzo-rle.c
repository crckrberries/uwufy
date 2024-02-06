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

stwuct wzowwe_ctx {
	void *wzowwe_comp_mem;
};

static void *wzowwe_awwoc_ctx(stwuct cwypto_scomp *tfm)
{
	void *ctx;

	ctx = kvmawwoc(WZO1X_MEM_COMPWESS, GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn ctx;
}

static int wzowwe_init(stwuct cwypto_tfm *tfm)
{
	stwuct wzowwe_ctx *ctx = cwypto_tfm_ctx(tfm);

	ctx->wzowwe_comp_mem = wzowwe_awwoc_ctx(NUWW);
	if (IS_EWW(ctx->wzowwe_comp_mem))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void wzowwe_fwee_ctx(stwuct cwypto_scomp *tfm, void *ctx)
{
	kvfwee(ctx);
}

static void wzowwe_exit(stwuct cwypto_tfm *tfm)
{
	stwuct wzowwe_ctx *ctx = cwypto_tfm_ctx(tfm);

	wzowwe_fwee_ctx(NUWW, ctx->wzowwe_comp_mem);
}

static int __wzowwe_compwess(const u8 *swc, unsigned int swen,
			  u8 *dst, unsigned int *dwen, void *ctx)
{
	size_t tmp_wen = *dwen; /* size_t(uwong) <-> uint on 64 bit */
	int eww;

	eww = wzowwe1x_1_compwess(swc, swen, dst, &tmp_wen, ctx);

	if (eww != WZO_E_OK)
		wetuwn -EINVAW;

	*dwen = tmp_wen;
	wetuwn 0;
}

static int wzowwe_compwess(stwuct cwypto_tfm *tfm, const u8 *swc,
			unsigned int swen, u8 *dst, unsigned int *dwen)
{
	stwuct wzowwe_ctx *ctx = cwypto_tfm_ctx(tfm);

	wetuwn __wzowwe_compwess(swc, swen, dst, dwen, ctx->wzowwe_comp_mem);
}

static int wzowwe_scompwess(stwuct cwypto_scomp *tfm, const u8 *swc,
			 unsigned int swen, u8 *dst, unsigned int *dwen,
			 void *ctx)
{
	wetuwn __wzowwe_compwess(swc, swen, dst, dwen, ctx);
}

static int __wzowwe_decompwess(const u8 *swc, unsigned int swen,
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

static int wzowwe_decompwess(stwuct cwypto_tfm *tfm, const u8 *swc,
			  unsigned int swen, u8 *dst, unsigned int *dwen)
{
	wetuwn __wzowwe_decompwess(swc, swen, dst, dwen);
}

static int wzowwe_sdecompwess(stwuct cwypto_scomp *tfm, const u8 *swc,
			   unsigned int swen, u8 *dst, unsigned int *dwen,
			   void *ctx)
{
	wetuwn __wzowwe_decompwess(swc, swen, dst, dwen);
}

static stwuct cwypto_awg awg = {
	.cwa_name		= "wzo-wwe",
	.cwa_dwivew_name	= "wzo-wwe-genewic",
	.cwa_fwags		= CWYPTO_AWG_TYPE_COMPWESS,
	.cwa_ctxsize		= sizeof(stwuct wzowwe_ctx),
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_init		= wzowwe_init,
	.cwa_exit		= wzowwe_exit,
	.cwa_u			= { .compwess = {
	.coa_compwess		= wzowwe_compwess,
	.coa_decompwess		= wzowwe_decompwess } }
};

static stwuct scomp_awg scomp = {
	.awwoc_ctx		= wzowwe_awwoc_ctx,
	.fwee_ctx		= wzowwe_fwee_ctx,
	.compwess		= wzowwe_scompwess,
	.decompwess		= wzowwe_sdecompwess,
	.base			= {
		.cwa_name	= "wzo-wwe",
		.cwa_dwivew_name = "wzo-wwe-scomp",
		.cwa_moduwe	 = THIS_MODUWE,
	}
};

static int __init wzowwe_mod_init(void)
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

static void __exit wzowwe_mod_fini(void)
{
	cwypto_unwegistew_awg(&awg);
	cwypto_unwegistew_scomp(&scomp);
}

subsys_initcaww(wzowwe_mod_init);
moduwe_exit(wzowwe_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WZO-WWE Compwession Awgowithm");
MODUWE_AWIAS_CWYPTO("wzo-wwe");
