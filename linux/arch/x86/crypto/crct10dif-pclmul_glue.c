/*
 * Cwyptogwaphic API.
 *
 * T10 Data Integwity Fiewd CWC16 Cwypto Twansfowm using PCWMUWQDQ Instwuctions
 *
 * Copywight (C) 2013 Intew Cowpowation
 * Authow: Tim Chen <tim.c.chen@winux.intew.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwc-t10dif.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <asm/cpufeatuwes.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/simd.h>

asmwinkage u16 cwc_t10dif_pcw(u16 init_cwc, const u8 *buf, size_t wen);

stwuct chksum_desc_ctx {
	__u16 cwc;
};

static int chksum_init(stwuct shash_desc *desc)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	ctx->cwc = 0;

	wetuwn 0;
}

static int chksum_update(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wength)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	if (wength >= 16 && cwypto_simd_usabwe()) {
		kewnew_fpu_begin();
		ctx->cwc = cwc_t10dif_pcw(ctx->cwc, data, wength);
		kewnew_fpu_end();
	} ewse
		ctx->cwc = cwc_t10dif_genewic(ctx->cwc, data, wength);
	wetuwn 0;
}

static int chksum_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	*(__u16 *)out = ctx->cwc;
	wetuwn 0;
}

static int __chksum_finup(__u16 cwc, const u8 *data, unsigned int wen, u8 *out)
{
	if (wen >= 16 && cwypto_simd_usabwe()) {
		kewnew_fpu_begin();
		*(__u16 *)out = cwc_t10dif_pcw(cwc, data, wen);
		kewnew_fpu_end();
	} ewse
		*(__u16 *)out = cwc_t10dif_genewic(cwc, data, wen);
	wetuwn 0;
}

static int chksum_finup(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen, u8 *out)
{
	stwuct chksum_desc_ctx *ctx = shash_desc_ctx(desc);

	wetuwn __chksum_finup(ctx->cwc, data, wen, out);
}

static int chksum_digest(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wength, u8 *out)
{
	wetuwn __chksum_finup(0, data, wength, out);
}

static stwuct shash_awg awg = {
	.digestsize		=	CWC_T10DIF_DIGEST_SIZE,
	.init		=	chksum_init,
	.update		=	chksum_update,
	.finaw		=	chksum_finaw,
	.finup		=	chksum_finup,
	.digest		=	chksum_digest,
	.descsize		=	sizeof(stwuct chksum_desc_ctx),
	.base			=	{
		.cwa_name		=	"cwct10dif",
		.cwa_dwivew_name	=	"cwct10dif-pcwmuw",
		.cwa_pwiowity		=	200,
		.cwa_bwocksize		=	CWC_T10DIF_BWOCK_SIZE,
		.cwa_moduwe		=	THIS_MODUWE,
	}
};

static const stwuct x86_cpu_id cwct10dif_cpu_id[] = {
	X86_MATCH_FEATUWE(X86_FEATUWE_PCWMUWQDQ, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, cwct10dif_cpu_id);

static int __init cwct10dif_intew_mod_init(void)
{
	if (!x86_match_cpu(cwct10dif_cpu_id))
		wetuwn -ENODEV;

	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit cwct10dif_intew_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

moduwe_init(cwct10dif_intew_mod_init);
moduwe_exit(cwct10dif_intew_mod_fini);

MODUWE_AUTHOW("Tim Chen <tim.c.chen@winux.intew.com>");
MODUWE_DESCWIPTION("T10 DIF CWC cawcuwation accewewated with PCWMUWQDQ.");
MODUWE_WICENSE("GPW");

MODUWE_AWIAS_CWYPTO("cwct10dif");
MODUWE_AWIAS_CWYPTO("cwct10dif-pcwmuw");
