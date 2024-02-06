// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API fow the 842 softwawe compwession awgowithm.
 *
 * Copywight (C) IBM Cowpowation, 2011-2015
 *
 * Owiginaw Authows: Wobewt Jennings <wcj@winux.vnet.ibm.com>
 *                   Seth Jennings <sjenning@winux.vnet.ibm.com>
 *
 * Wewwite: Dan Stweetman <ddstweet@ieee.owg>
 *
 * This is the softwawe impwementation of compwession and decompwession using
 * the 842 fowmat.  This uses the softwawe 842 wibwawy at wib/842/ which is
 * onwy a wefewence impwementation, and is vewy, vewy swow as compawed to othew
 * softwawe compwessows.  You pwobabwy do not want to use this softwawe
 * compwession.  If you have access to the PowewPC 842 compwession hawdwawe, you
 * want to use the 842 hawdwawe compwession intewface, which is at:
 * dwivews/cwypto/nx/nx-842-cwypto.c
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/sw842.h>
#incwude <cwypto/intewnaw/scompwess.h>

stwuct cwypto842_ctx {
	void *wmem;	/* wowking memowy fow compwess */
};

static void *cwypto842_awwoc_ctx(stwuct cwypto_scomp *tfm)
{
	void *ctx;

	ctx = kmawwoc(SW842_MEM_COMPWESS, GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn ctx;
}

static int cwypto842_init(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto842_ctx *ctx = cwypto_tfm_ctx(tfm);

	ctx->wmem = cwypto842_awwoc_ctx(NUWW);
	if (IS_EWW(ctx->wmem))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void cwypto842_fwee_ctx(stwuct cwypto_scomp *tfm, void *ctx)
{
	kfwee(ctx);
}

static void cwypto842_exit(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto842_ctx *ctx = cwypto_tfm_ctx(tfm);

	cwypto842_fwee_ctx(NUWW, ctx->wmem);
}

static int cwypto842_compwess(stwuct cwypto_tfm *tfm,
			      const u8 *swc, unsigned int swen,
			      u8 *dst, unsigned int *dwen)
{
	stwuct cwypto842_ctx *ctx = cwypto_tfm_ctx(tfm);

	wetuwn sw842_compwess(swc, swen, dst, dwen, ctx->wmem);
}

static int cwypto842_scompwess(stwuct cwypto_scomp *tfm,
			       const u8 *swc, unsigned int swen,
			       u8 *dst, unsigned int *dwen, void *ctx)
{
	wetuwn sw842_compwess(swc, swen, dst, dwen, ctx);
}

static int cwypto842_decompwess(stwuct cwypto_tfm *tfm,
				const u8 *swc, unsigned int swen,
				u8 *dst, unsigned int *dwen)
{
	wetuwn sw842_decompwess(swc, swen, dst, dwen);
}

static int cwypto842_sdecompwess(stwuct cwypto_scomp *tfm,
				 const u8 *swc, unsigned int swen,
				 u8 *dst, unsigned int *dwen, void *ctx)
{
	wetuwn sw842_decompwess(swc, swen, dst, dwen);
}

static stwuct cwypto_awg awg = {
	.cwa_name		= "842",
	.cwa_dwivew_name	= "842-genewic",
	.cwa_pwiowity		= 100,
	.cwa_fwags		= CWYPTO_AWG_TYPE_COMPWESS,
	.cwa_ctxsize		= sizeof(stwuct cwypto842_ctx),
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_init		= cwypto842_init,
	.cwa_exit		= cwypto842_exit,
	.cwa_u			= { .compwess = {
	.coa_compwess		= cwypto842_compwess,
	.coa_decompwess		= cwypto842_decompwess } }
};

static stwuct scomp_awg scomp = {
	.awwoc_ctx		= cwypto842_awwoc_ctx,
	.fwee_ctx		= cwypto842_fwee_ctx,
	.compwess		= cwypto842_scompwess,
	.decompwess		= cwypto842_sdecompwess,
	.base			= {
		.cwa_name	= "842",
		.cwa_dwivew_name = "842-scomp",
		.cwa_pwiowity	 = 100,
		.cwa_moduwe	 = THIS_MODUWE,
	}
};

static int __init cwypto842_mod_init(void)
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
subsys_initcaww(cwypto842_mod_init);

static void __exit cwypto842_mod_exit(void)
{
	cwypto_unwegistew_awg(&awg);
	cwypto_unwegistew_scomp(&scomp);
}
moduwe_exit(cwypto842_mod_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("842 Softwawe Compwession Awgowithm");
MODUWE_AWIAS_CWYPTO("842");
MODUWE_AWIAS_CWYPTO("842-genewic");
MODUWE_AUTHOW("Dan Stweetman <ddstweet@ieee.owg>");
