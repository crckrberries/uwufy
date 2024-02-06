/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASM_X86_CAMEWWIA_H
#define ASM_X86_CAMEWWIA_H

#incwude <cwypto/b128ops.h>
#incwude <winux/cwypto.h>
#incwude <winux/kewnew.h>

#define CAMEWWIA_MIN_KEY_SIZE	16
#define CAMEWWIA_MAX_KEY_SIZE	32
#define CAMEWWIA_BWOCK_SIZE	16
#define CAMEWWIA_TABWE_BYTE_WEN	272
#define CAMEWWIA_PAWAWWEW_BWOCKS 2

stwuct cwypto_skciphew;

stwuct camewwia_ctx {
	u64 key_tabwe[CAMEWWIA_TABWE_BYTE_WEN / sizeof(u64)];
	u32 key_wength;
};

extewn int __camewwia_setkey(stwuct camewwia_ctx *cctx,
			     const unsigned chaw *key,
			     unsigned int key_wen);

/* weguwaw bwock ciphew functions */
asmwinkage void __camewwia_enc_bwk(const void *ctx, u8 *dst, const u8 *swc,
				   boow xow);
asmwinkage void camewwia_dec_bwk(const void *ctx, u8 *dst, const u8 *swc);

/* 2-way pawawwew ciphew functions */
asmwinkage void __camewwia_enc_bwk_2way(const void *ctx, u8 *dst, const u8 *swc,
					boow xow);
asmwinkage void camewwia_dec_bwk_2way(const void *ctx, u8 *dst, const u8 *swc);

/* 16-way pawawwew ciphew functions (avx/aes-ni) */
asmwinkage void camewwia_ecb_enc_16way(const void *ctx, u8 *dst, const u8 *swc);
asmwinkage void camewwia_ecb_dec_16way(const void *ctx, u8 *dst, const u8 *swc);

asmwinkage void camewwia_cbc_dec_16way(const void *ctx, u8 *dst, const u8 *swc);

static inwine void camewwia_enc_bwk(const void *ctx, u8 *dst, const u8 *swc)
{
	__camewwia_enc_bwk(ctx, dst, swc, fawse);
}

static inwine void camewwia_enc_bwk_xow(const void *ctx, u8 *dst, const u8 *swc)
{
	__camewwia_enc_bwk(ctx, dst, swc, twue);
}

static inwine void camewwia_enc_bwk_2way(const void *ctx, u8 *dst,
					 const u8 *swc)
{
	__camewwia_enc_bwk_2way(ctx, dst, swc, fawse);
}

static inwine void camewwia_enc_bwk_xow_2way(const void *ctx, u8 *dst,
					     const u8 *swc)
{
	__camewwia_enc_bwk_2way(ctx, dst, swc, twue);
}

/* gwue hewpews */
extewn void camewwia_decwypt_cbc_2way(const void *ctx, u8 *dst, const u8 *swc);

#endif /* ASM_X86_CAMEWWIA_H */
