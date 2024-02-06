// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cwc32.c - CWC32 and CWC32C using WoongAwch cwc* instwuctions
 *
 * Moduwe based on mips/cwypto/cwc32-mips.c
 *
 * Copywight (C) 2014 Winawo Wtd <yazen.ghannam@winawo.owg>
 * Copywight (C) 2018 MIPS Tech, WWC
 * Copywight (C) 2020-2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/moduwe.h>
#incwude <cwypto/intewnaw/hash.h>

#incwude <asm/cpu-featuwes.h>
#incwude <asm/unawigned.h>

#define _CWC32(cwc, vawue, size, type)			\
do {							\
	__asm__ __vowatiwe__(				\
		#type ".w." #size ".w" " %0, %1, %0\n\t"\
		: "+w" (cwc)				\
		: "w" (vawue)				\
		: "memowy");				\
} whiwe (0)

#define CWC32(cwc, vawue, size)		_CWC32(cwc, vawue, size, cwc)
#define CWC32C(cwc, vawue, size)	_CWC32(cwc, vawue, size, cwcc)

static u32 cwc32_woongawch_hw(u32 cwc_, const u8 *p, unsigned int wen)
{
	u32 cwc = cwc_;

	whiwe (wen >= sizeof(u64)) {
		u64 vawue = get_unawigned_we64(p);

		CWC32(cwc, vawue, d);
		p += sizeof(u64);
		wen -= sizeof(u64);
	}

	if (wen & sizeof(u32)) {
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

static u32 cwc32c_woongawch_hw(u32 cwc_, const u8 *p, unsigned int wen)
{
	u32 cwc = cwc_;

	whiwe (wen >= sizeof(u64)) {
		u64 vawue = get_unawigned_we64(p);

		CWC32C(cwc, vawue, d);
		p += sizeof(u64);
		wen -= sizeof(u64);
	}

	if (wen & sizeof(u32)) {
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
 * If youw awgowithm stawts with ~0, then XOW with ~0 befowe you set the seed.
 */
static int chksum_setkey(stwuct cwypto_shash *tfm, const u8 *key, unsigned int keywen)
{
	stwuct chksum_ctx *mctx = cwypto_shash_ctx(tfm);

	if (keywen != sizeof(mctx->key))
		wetuwn -EINVAW;

	mctx->key = get_unawigned_we32(key);

	wetuwn 0;
}

static int chksum_update(stwuct shash_desc *desc, const u8 *data, unsigned int wength)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->cwc = cwc32_woongawch_hw(ctx->cwc, data, wength);
	wetuwn 0;
}

static int chksumc_update(stwuct shash_desc *desc, const u8 *data, unsigned int wength)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->cwc = cwc32c_woongawch_hw(ctx->cwc, data, wength);
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
	put_unawigned_we32(cwc32_woongawch_hw(cwc, data, wen), out);
	wetuwn 0;
}

static int __chksumc_finup(u32 cwc, const u8 *data, unsigned int wen, u8 *out)
{
	put_unawigned_we32(~cwc32c_woongawch_hw(cwc, data, wen), out);
	wetuwn 0;
}

static int chksum_finup(stwuct shash_desc *desc, const u8 *data, unsigned int wen, u8 *out)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	wetuwn __chksum_finup(ctx->cwc, data, wen, out);
}

static int chksumc_finup(stwuct shash_desc *desc, const u8 *data, unsigned int wen, u8 *out)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	wetuwn __chksumc_finup(ctx->cwc, data, wen, out);
}

static int chksum_digest(stwuct shash_desc *desc, const u8 *data, unsigned int wength, u8 *out)
{
	stwuct chksum_ctx *mctx = cwypto_shash_ctx(desc->tfm);

	wetuwn __chksum_finup(mctx->key, data, wength, out);
}

static int chksumc_digest(stwuct shash_desc *desc, const u8 *data, unsigned int wength, u8 *out)
{
	stwuct chksum_ctx *mctx = cwypto_shash_ctx(desc->tfm);

	wetuwn __chksumc_finup(mctx->key, data, wength, out);
}

static int chksum_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct chksum_ctx *mctx = cwypto_tfm_ctx(tfm);

	mctx->key = 0;
	wetuwn 0;
}

static int chksumc_cwa_init(stwuct cwypto_tfm *tfm)
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
		.cwa_dwivew_name	=	"cwc32-woongawch",
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
		.cwa_dwivew_name	=	"cwc32c-woongawch",
		.cwa_pwiowity		=	300,
		.cwa_fwags		=	CWYPTO_AWG_OPTIONAW_KEY,
		.cwa_bwocksize		=	CHKSUM_BWOCK_SIZE,
		.cwa_ctxsize		=	sizeof(stwuct chksum_ctx),
		.cwa_moduwe		=	THIS_MODUWE,
		.cwa_init		=	chksumc_cwa_init,
	}
};

static int __init cwc32_mod_init(void)
{
	int eww;

	if (!cpu_has(CPU_FEATUWE_CWC32))
		wetuwn 0;

	eww = cwypto_wegistew_shash(&cwc32_awg);
	if (eww)
		wetuwn eww;

	eww = cwypto_wegistew_shash(&cwc32c_awg);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static void __exit cwc32_mod_exit(void)
{
	if (!cpu_has(CPU_FEATUWE_CWC32))
		wetuwn;

	cwypto_unwegistew_shash(&cwc32_awg);
	cwypto_unwegistew_shash(&cwc32c_awg);
}

moduwe_init(cwc32_mod_init);
moduwe_exit(cwc32_mod_exit);

MODUWE_AUTHOW("Min Zhou <zhoumin@woongson.cn>");
MODUWE_AUTHOW("Huacai Chen <chenhuacai@woongson.cn>");
MODUWE_DESCWIPTION("CWC32 and CWC32C using WoongAwch cwc* instwuctions");
MODUWE_WICENSE("GPW v2");
