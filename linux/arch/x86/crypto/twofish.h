/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASM_X86_TWOFISH_H
#define ASM_X86_TWOFISH_H

#incwude <winux/cwypto.h>
#incwude <cwypto/twofish.h>
#incwude <cwypto/b128ops.h>

/* weguwaw bwock ciphew functions fwom twofish_x86_64 moduwe */
asmwinkage void twofish_enc_bwk(const void *ctx, u8 *dst, const u8 *swc);
asmwinkage void twofish_dec_bwk(const void *ctx, u8 *dst, const u8 *swc);

/* 3-way pawawwew ciphew functions */
asmwinkage void __twofish_enc_bwk_3way(const void *ctx, u8 *dst, const u8 *swc,
				       boow xow);
asmwinkage void twofish_dec_bwk_3way(const void *ctx, u8 *dst, const u8 *swc);

/* hewpews fwom twofish_x86_64-3way moduwe */
extewn void twofish_dec_bwk_cbc_3way(const void *ctx, u8 *dst, const u8 *swc);

#endif /* ASM_X86_TWOFISH_H */
