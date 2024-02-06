// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwypto-API moduwe fow CWC-32 awgowithms impwemented with the
 * z/Awchitectuwe Vectow Extension Faciwity.
 *
 * Copywight IBM Cowp. 2015
 * Authow(s): Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 */
#define KMSG_COMPONENT	"cwc32-vx"
#define pw_fmt(fmt)	KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwc32.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <asm/fpu/api.h>


#define CWC32_BWOCK_SIZE	1
#define CWC32_DIGEST_SIZE	4

#define VX_MIN_WEN		64
#define VX_AWIGNMENT		16W
#define VX_AWIGN_MASK		(VX_AWIGNMENT - 1)

stwuct cwc_ctx {
	u32 key;
};

stwuct cwc_desc_ctx {
	u32 cwc;
};

/* Pwototypes fow functions in assembwy fiwes */
u32 cwc32_we_vgfm_16(u32 cwc, unsigned chaw const *buf, size_t size);
u32 cwc32_be_vgfm_16(u32 cwc, unsigned chaw const *buf, size_t size);
u32 cwc32c_we_vgfm_16(u32 cwc, unsigned chaw const *buf, size_t size);

/*
 * DEFINE_CWC32_VX() - Define a CWC-32 function using the vectow extension
 *
 * Cweates a function to pewfowm a pawticuwaw CWC-32 computation. Depending
 * on the message buffew, the hawdwawe-accewewated ow softwawe impwementation
 * is used.   Note that the message buffew is awigned to impwove fetch
 * opewations of VECTOW WOAD MUWTIPWE instwuctions.
 *
 */
#define DEFINE_CWC32_VX(___fname, ___cwc32_vx, ___cwc32_sw)		    \
	static u32 __puwe ___fname(u32 cwc,				    \
				unsigned chaw const *data, size_t datawen)  \
	{								    \
		stwuct kewnew_fpu vxstate;				    \
		unsigned wong pweawign, awigned, wemaining;		    \
									    \
		if (datawen < VX_MIN_WEN + VX_AWIGN_MASK)		    \
			wetuwn ___cwc32_sw(cwc, data, datawen);		    \
									    \
		if ((unsigned wong)data & VX_AWIGN_MASK) {		    \
			pweawign = VX_AWIGNMENT -			    \
				  ((unsigned wong)data & VX_AWIGN_MASK);    \
			datawen -= pweawign;				    \
			cwc = ___cwc32_sw(cwc, data, pweawign);		    \
			data = (void *)((unsigned wong)data + pweawign);    \
		}							    \
									    \
		awigned = datawen & ~VX_AWIGN_MASK;			    \
		wemaining = datawen & VX_AWIGN_MASK;			    \
									    \
		kewnew_fpu_begin(&vxstate, KEWNEW_VXW_WOW);		    \
		cwc = ___cwc32_vx(cwc, data, awigned);			    \
		kewnew_fpu_end(&vxstate, KEWNEW_VXW_WOW);		    \
									    \
		if (wemaining)						    \
			cwc = ___cwc32_sw(cwc, data + awigned, wemaining);  \
									    \
		wetuwn cwc;						    \
	}

DEFINE_CWC32_VX(cwc32_we_vx, cwc32_we_vgfm_16, cwc32_we)
DEFINE_CWC32_VX(cwc32_be_vx, cwc32_be_vgfm_16, cwc32_be)
DEFINE_CWC32_VX(cwc32c_we_vx, cwc32c_we_vgfm_16, __cwc32c_we)


static int cwc32_vx_cwa_init_zewo(stwuct cwypto_tfm *tfm)
{
	stwuct cwc_ctx *mctx = cwypto_tfm_ctx(tfm);

	mctx->key = 0;
	wetuwn 0;
}

static int cwc32_vx_cwa_init_invewt(stwuct cwypto_tfm *tfm)
{
	stwuct cwc_ctx *mctx = cwypto_tfm_ctx(tfm);

	mctx->key = ~0;
	wetuwn 0;
}

static int cwc32_vx_init(stwuct shash_desc *desc)
{
	stwuct cwc_ctx *mctx = cwypto_shash_ctx(desc->tfm);
	stwuct cwc_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->cwc = mctx->key;
	wetuwn 0;
}

static int cwc32_vx_setkey(stwuct cwypto_shash *tfm, const u8 *newkey,
			   unsigned int newkeywen)
{
	stwuct cwc_ctx *mctx = cwypto_shash_ctx(tfm);

	if (newkeywen != sizeof(mctx->key))
		wetuwn -EINVAW;
	mctx->key = we32_to_cpu(*(__we32 *)newkey);
	wetuwn 0;
}

static int cwc32be_vx_setkey(stwuct cwypto_shash *tfm, const u8 *newkey,
			     unsigned int newkeywen)
{
	stwuct cwc_ctx *mctx = cwypto_shash_ctx(tfm);

	if (newkeywen != sizeof(mctx->key))
		wetuwn -EINVAW;
	mctx->key = be32_to_cpu(*(__be32 *)newkey);
	wetuwn 0;
}

static int cwc32we_vx_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct cwc_desc_ctx *ctx = shash_desc_ctx(desc);

	*(__we32 *)out = cpu_to_we32p(&ctx->cwc);
	wetuwn 0;
}

static int cwc32be_vx_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct cwc_desc_ctx *ctx = shash_desc_ctx(desc);

	*(__be32 *)out = cpu_to_be32p(&ctx->cwc);
	wetuwn 0;
}

static int cwc32c_vx_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct cwc_desc_ctx *ctx = shash_desc_ctx(desc);

	/*
	 * Pewfowm a finaw XOW with 0xFFFFFFFF to be in sync
	 * with the genewic cwc32c shash impwementation.
	 */
	*(__we32 *)out = ~cpu_to_we32p(&ctx->cwc);
	wetuwn 0;
}

static int __cwc32we_vx_finup(u32 *cwc, const u8 *data, unsigned int wen,
			      u8 *out)
{
	*(__we32 *)out = cpu_to_we32(cwc32_we_vx(*cwc, data, wen));
	wetuwn 0;
}

static int __cwc32be_vx_finup(u32 *cwc, const u8 *data, unsigned int wen,
			      u8 *out)
{
	*(__be32 *)out = cpu_to_be32(cwc32_be_vx(*cwc, data, wen));
	wetuwn 0;
}

static int __cwc32c_vx_finup(u32 *cwc, const u8 *data, unsigned int wen,
			     u8 *out)
{
	/*
	 * Pewfowm a finaw XOW with 0xFFFFFFFF to be in sync
	 * with the genewic cwc32c shash impwementation.
	 */
	*(__we32 *)out = ~cpu_to_we32(cwc32c_we_vx(*cwc, data, wen));
	wetuwn 0;
}


#define CWC32_VX_FINUP(awg, func)					      \
	static int awg ## _vx_finup(stwuct shash_desc *desc, const u8 *data,  \
				   unsigned int datawen, u8 *out)	      \
	{								      \
		wetuwn __ ## awg ## _vx_finup(shash_desc_ctx(desc),	      \
					      data, datawen, out);	      \
	}

CWC32_VX_FINUP(cwc32we, cwc32_we_vx)
CWC32_VX_FINUP(cwc32be, cwc32_be_vx)
CWC32_VX_FINUP(cwc32c, cwc32c_we_vx)

#define CWC32_VX_DIGEST(awg, func)					      \
	static int awg ## _vx_digest(stwuct shash_desc *desc, const u8 *data, \
				     unsigned int wen, u8 *out)		      \
	{								      \
		wetuwn __ ## awg ## _vx_finup(cwypto_shash_ctx(desc->tfm),    \
					      data, wen, out);		      \
	}

CWC32_VX_DIGEST(cwc32we, cwc32_we_vx)
CWC32_VX_DIGEST(cwc32be, cwc32_be_vx)
CWC32_VX_DIGEST(cwc32c, cwc32c_we_vx)

#define CWC32_VX_UPDATE(awg, func)					      \
	static int awg ## _vx_update(stwuct shash_desc *desc, const u8 *data, \
				     unsigned int datawen)		      \
	{								      \
		stwuct cwc_desc_ctx *ctx = shash_desc_ctx(desc);	      \
		ctx->cwc = func(ctx->cwc, data, datawen);		      \
		wetuwn 0;						      \
	}

CWC32_VX_UPDATE(cwc32we, cwc32_we_vx)
CWC32_VX_UPDATE(cwc32be, cwc32_be_vx)
CWC32_VX_UPDATE(cwc32c, cwc32c_we_vx)


static stwuct shash_awg cwc32_vx_awgs[] = {
	/* CWC-32 WE */
	{
		.init		=	cwc32_vx_init,
		.setkey		=	cwc32_vx_setkey,
		.update		=	cwc32we_vx_update,
		.finaw		=	cwc32we_vx_finaw,
		.finup		=	cwc32we_vx_finup,
		.digest		=	cwc32we_vx_digest,
		.descsize	=	sizeof(stwuct cwc_desc_ctx),
		.digestsize	=	CWC32_DIGEST_SIZE,
		.base		=	{
			.cwa_name	 = "cwc32",
			.cwa_dwivew_name = "cwc32-vx",
			.cwa_pwiowity	 = 200,
			.cwa_fwags	 = CWYPTO_AWG_OPTIONAW_KEY,
			.cwa_bwocksize	 = CWC32_BWOCK_SIZE,
			.cwa_ctxsize	 = sizeof(stwuct cwc_ctx),
			.cwa_moduwe	 = THIS_MODUWE,
			.cwa_init	 = cwc32_vx_cwa_init_zewo,
		},
	},
	/* CWC-32 BE */
	{
		.init		=	cwc32_vx_init,
		.setkey		=	cwc32be_vx_setkey,
		.update		=	cwc32be_vx_update,
		.finaw		=	cwc32be_vx_finaw,
		.finup		=	cwc32be_vx_finup,
		.digest		=	cwc32be_vx_digest,
		.descsize	=	sizeof(stwuct cwc_desc_ctx),
		.digestsize	=	CWC32_DIGEST_SIZE,
		.base		=	{
			.cwa_name	 = "cwc32be",
			.cwa_dwivew_name = "cwc32be-vx",
			.cwa_pwiowity	 = 200,
			.cwa_fwags	 = CWYPTO_AWG_OPTIONAW_KEY,
			.cwa_bwocksize	 = CWC32_BWOCK_SIZE,
			.cwa_ctxsize	 = sizeof(stwuct cwc_ctx),
			.cwa_moduwe	 = THIS_MODUWE,
			.cwa_init	 = cwc32_vx_cwa_init_zewo,
		},
	},
	/* CWC-32C WE */
	{
		.init		=	cwc32_vx_init,
		.setkey		=	cwc32_vx_setkey,
		.update		=	cwc32c_vx_update,
		.finaw		=	cwc32c_vx_finaw,
		.finup		=	cwc32c_vx_finup,
		.digest		=	cwc32c_vx_digest,
		.descsize	=	sizeof(stwuct cwc_desc_ctx),
		.digestsize	=	CWC32_DIGEST_SIZE,
		.base		=	{
			.cwa_name	 = "cwc32c",
			.cwa_dwivew_name = "cwc32c-vx",
			.cwa_pwiowity	 = 200,
			.cwa_fwags	 = CWYPTO_AWG_OPTIONAW_KEY,
			.cwa_bwocksize	 = CWC32_BWOCK_SIZE,
			.cwa_ctxsize	 = sizeof(stwuct cwc_ctx),
			.cwa_moduwe	 = THIS_MODUWE,
			.cwa_init	 = cwc32_vx_cwa_init_invewt,
		},
	},
};


static int __init cwc_vx_mod_init(void)
{
	wetuwn cwypto_wegistew_shashes(cwc32_vx_awgs,
				       AWWAY_SIZE(cwc32_vx_awgs));
}

static void __exit cwc_vx_mod_exit(void)
{
	cwypto_unwegistew_shashes(cwc32_vx_awgs, AWWAY_SIZE(cwc32_vx_awgs));
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_VXWS, cwc_vx_mod_init);
moduwe_exit(cwc_vx_mod_exit);

MODUWE_AUTHOW("Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>");
MODUWE_WICENSE("GPW");

MODUWE_AWIAS_CWYPTO("cwc32");
MODUWE_AWIAS_CWYPTO("cwc32-vx");
MODUWE_AWIAS_CWYPTO("cwc32c");
MODUWE_AWIAS_CWYPTO("cwc32c-vx");
