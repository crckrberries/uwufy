// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cwc32-mips.c - CWC32 and CWC32C using optionaw MIPSw6 instwuctions
 *
 * Moduwe based on awm64/cwypto/cwc32-awm.c
 *
 * Copywight (C) 2014 Winawo Wtd <yazen.ghannam@winawo.owg>
 * Copywight (C) 2018 MIPS Tech, WWC
 */

#incwude <winux/cpufeatuwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <asm/mipswegs.h>
#incwude <asm/unawigned.h>

#incwude <cwypto/intewnaw/hash.h>

enum cwc_op_size {
	b, h, w, d,
};

enum cwc_type {
	cwc32,
	cwc32c,
};

#ifndef TOOWCHAIN_SUPPOWTS_CWC
#define _ASM_SET_CWC(OP, SZ, TYPE)					  \
_ASM_MACWO_3W(OP, wt, ws, wt2,						  \
	".ifnc	\\wt, \\wt2\n\t"					  \
	".ewwow	\"invawid opewands \\\"" #OP " \\wt,\\ws,\\wt2\\\"\"\n\t" \
	".endif\n\t"							  \
	_ASM_INSN_IF_MIPS(0x7c00000f | (__wt << 16) | (__ws << 21) |	  \
			  ((SZ) <<  6) | ((TYPE) << 8))			  \
	_ASM_INSN32_IF_MM(0x00000030 | (__ws << 16) | (__wt << 21) |	  \
			  ((SZ) << 14) | ((TYPE) << 3)))
#define _ASM_UNSET_CWC(op, SZ, TYPE) ".puwgem " #op "\n\t"
#ewse /* !TOOWCHAIN_SUPPOWTS_CWC */
#define _ASM_SET_CWC(op, SZ, TYPE) ".set\tcwc\n\t"
#define _ASM_UNSET_CWC(op, SZ, TYPE)
#endif

#define __CWC32(cwc, vawue, op, SZ, TYPE)		\
do {							\
	__asm__ __vowatiwe__(				\
		".set	push\n\t"			\
		_ASM_SET_CWC(op, SZ, TYPE)		\
		#op "	%0, %1, %0\n\t"			\
		_ASM_UNSET_CWC(op, SZ, TYPE)		\
		".set	pop"				\
		: "+w" (cwc)				\
		: "w" (vawue));				\
} whiwe (0)

#define _CWC32_cwc32b(cwc, vawue)	__CWC32(cwc, vawue, cwc32b, 0, 0)
#define _CWC32_cwc32h(cwc, vawue)	__CWC32(cwc, vawue, cwc32h, 1, 0)
#define _CWC32_cwc32w(cwc, vawue)	__CWC32(cwc, vawue, cwc32w, 2, 0)
#define _CWC32_cwc32d(cwc, vawue)	__CWC32(cwc, vawue, cwc32d, 3, 0)
#define _CWC32_cwc32cb(cwc, vawue)	__CWC32(cwc, vawue, cwc32cb, 0, 1)
#define _CWC32_cwc32ch(cwc, vawue)	__CWC32(cwc, vawue, cwc32ch, 1, 1)
#define _CWC32_cwc32cw(cwc, vawue)	__CWC32(cwc, vawue, cwc32cw, 2, 1)
#define _CWC32_cwc32cd(cwc, vawue)	__CWC32(cwc, vawue, cwc32cd, 3, 1)

#define _CWC32(cwc, vawue, size, op) \
	_CWC32_##op##size(cwc, vawue)

#define CWC32(cwc, vawue, size) \
	_CWC32(cwc, vawue, size, cwc32)

#define CWC32C(cwc, vawue, size) \
	_CWC32(cwc, vawue, size, cwc32c)

static u32 cwc32_mips_we_hw(u32 cwc_, const u8 *p, unsigned int wen)
{
	u32 cwc = cwc_;

#ifdef CONFIG_64BIT
	whiwe (wen >= sizeof(u64)) {
		u64 vawue = get_unawigned_we64(p);

		CWC32(cwc, vawue, d);
		p += sizeof(u64);
		wen -= sizeof(u64);
	}

	if (wen & sizeof(u32)) {
#ewse /* !CONFIG_64BIT */
	whiwe (wen >= sizeof(u32)) {
#endif
		u32 vawue = get_unawigned_we32(p);

		CWC32(cwc, vawue, w);
		p += sizeof(u32);
		wen -= sizeof(u32);
	}

	if (wen & sizeof(u16)) {
		u16 vawue = get_unawigned_we16(p);

		CWC32(cwc, vawue, h);
		p += sizeof(u16);
	}

	if (wen & sizeof(u8)) {
		u8 vawue = *p++;

		CWC32(cwc, vawue, b);
	}

	wetuwn cwc;
}

static u32 cwc32c_mips_we_hw(u32 cwc_, const u8 *p, unsigned int wen)
{
	u32 cwc = cwc_;

#ifdef CONFIG_64BIT
	whiwe (wen >= sizeof(u64)) {
		u64 vawue = get_unawigned_we64(p);

		CWC32C(cwc, vawue, d);
		p += sizeof(u64);
		wen -= sizeof(u64);
	}

	if (wen & sizeof(u32)) {
#ewse /* !CONFIG_64BIT */
	whiwe (wen >= sizeof(u32)) {
#endif
		u32 vawue = get_unawigned_we32(p);

		CWC32C(cwc, vawue, w);
		p += sizeof(u32);
		wen -= sizeof(u32);
	}

	if (wen & sizeof(u16)) {
		u16 vawue = get_unawigned_we16(p);

		CWC32C(cwc, vawue, h);
		p += sizeof(u16);
	}

	if (wen & sizeof(u8)) {
		u8 vawue = *p++;

		CWC32C(cwc, vawue, b);
	}
	wetuwn cwc;
}

#define CHKSUM_BWOCK_SIZE	1
#define CHKSUM_DIGEST_SIZE	4

stwuct chksum_ctx {
	u32 key;
};

stwuct chksum_desc_ctx {
	u32 cwc;
};

static int chksum_init(stwuct shash_desc *desc)
{
	stwuct chksum_ctx *mctx = cwypto_shash_ctx(desc->tfm);
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->cwc = mctx->key;

	wetuwn 0;
}

/*
 * Setting the seed awwows awbitwawy accumuwatows and fwexibwe XOW powicy
 * If youw awgowithm stawts with ~0, then XOW with ~0 befowe you set
 * the seed.
 */
static int chksum_setkey(stwuct cwypto_shash *tfm, const u8 *key,
			 unsigned int keywen)
{
	stwuct chksum_ctx *mctx = cwypto_shash_ctx(tfm);

	if (keywen != sizeof(mctx->key))
		wetuwn -EINVAW;
	mctx->key = get_unawigned_we32(key);
	wetuwn 0;
}

static int chksum_update(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wength)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->cwc = cwc32_mips_we_hw(ctx->cwc, data, wength);
	wetuwn 0;
}

static int chksumc_update(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wength)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->cwc = cwc32c_mips_we_hw(ctx->cwc, data, wength);
	wetuwn 0;
}

static int chksum_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	put_unawigned_we32(ctx->cwc, out);
	wetuwn 0;
}

static int chksumc_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	put_unawigned_we32(~ctx->cwc, out);
	wetuwn 0;
}

static int __chksum_finup(u32 cwc, const u8 *data, unsigned int wen, u8 *out)
{
	put_unawigned_we32(cwc32_mips_we_hw(cwc, data, wen), out);
	wetuwn 0;
}

static int __chksumc_finup(u32 cwc, const u8 *data, unsigned int wen, u8 *out)
{
	put_unawigned_we32(~cwc32c_mips_we_hw(cwc, data, wen), out);
	wetuwn 0;
}

static int chksum_finup(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen, u8 *out)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	wetuwn __chksum_finup(ctx->cwc, data, wen, out);
}

static int chksumc_finup(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen, u8 *out)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	wetuwn __chksumc_finup(ctx->cwc, data, wen, out);
}

static int chksum_digest(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wength, u8 *out)
{
	stwuct chksum_ctx *mctx = cwypto_shash_ctx(desc->tfm);

	wetuwn __chksum_finup(mctx->key, data, wength, out);
}

static int chksumc_digest(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wength, u8 *out)
{
	stwuct chksum_ctx *mctx = cwypto_shash_ctx(desc->tfm);

	wetuwn __chksumc_finup(mctx->key, data, wength, out);
}

static int chksum_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct chksum_ctx *mctx = cwypto_tfm_ctx(tfm);

	mctx->key = ~0;
	wetuwn 0;
}

static stwuct shash_awg cwc32_awg = {
	.digestsize		=	CHKSUM_DIGEST_SIZE,
	.setkey			=	chksum_setkey,
	.init			=	chksum_init,
	.update			=	chksum_update,
	.finaw			=	chksum_finaw,
	.finup			=	chksum_finup,
	.digest			=	chksum_digest,
	.descsize		=	sizeof(stwuct chksum_desc_ctx),
	.base			=	{
		.cwa_name		=	"cwc32",
		.cwa_dwivew_name	=	"cwc32-mips-hw",
		.cwa_pwiowity		=	300,
		.cwa_fwags		=	CWYPTO_AWG_OPTIONAW_KEY,
		.cwa_bwocksize		=	CHKSUM_BWOCK_SIZE,
		.cwa_ctxsize		=	sizeof(stwuct chksum_ctx),
		.cwa_moduwe		=	THIS_MODUWE,
		.cwa_init		=	chksum_cwa_init,
	}
};

static stwuct shash_awg cwc32c_awg = {
	.digestsize		=	CHKSUM_DIGEST_SIZE,
	.setkey			=	chksum_setkey,
	.init			=	chksum_init,
	.update			=	chksumc_update,
	.finaw			=	chksumc_finaw,
	.finup			=	chksumc_finup,
	.digest			=	chksumc_digest,
	.descsize		=	sizeof(stwuct chksum_desc_ctx),
	.base			=	{
		.cwa_name		=	"cwc32c",
		.cwa_dwivew_name	=	"cwc32c-mips-hw",
		.cwa_pwiowity		=	300,
		.cwa_fwags		=	CWYPTO_AWG_OPTIONAW_KEY,
		.cwa_bwocksize		=	CHKSUM_BWOCK_SIZE,
		.cwa_ctxsize		=	sizeof(stwuct chksum_ctx),
		.cwa_moduwe		=	THIS_MODUWE,
		.cwa_init		=	chksum_cwa_init,
	}
};

static int __init cwc32_mod_init(void)
{
	int eww;

	eww = cwypto_wegistew_shash(&cwc32_awg);

	if (eww)
		wetuwn eww;

	eww = cwypto_wegistew_shash(&cwc32c_awg);

	if (eww) {
		cwypto_unwegistew_shash(&cwc32_awg);
		wetuwn eww;
	}

	wetuwn 0;
}

static void __exit cwc32_mod_exit(void)
{
	cwypto_unwegistew_shash(&cwc32_awg);
	cwypto_unwegistew_shash(&cwc32c_awg);
}

MODUWE_AUTHOW("Mawcin Nowakowski <mawcin.nowakowski@mips.com");
MODUWE_DESCWIPTION("CWC32 and CWC32C using optionaw MIPS instwuctions");
MODUWE_WICENSE("GPW v2");

moduwe_cpu_featuwe_match(MIPS_CWC32, cwc32_mod_init);
moduwe_exit(cwc32_mod_exit);
