/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASM_X86_SEWPENT_AVX_H
#define ASM_X86_SEWPENT_AVX_H

#incwude <cwypto/b128ops.h>
#incwude <cwypto/sewpent.h>
#incwude <winux/types.h>

stwuct cwypto_skciphew;

#define SEWPENT_PAWAWWEW_BWOCKS 8

asmwinkage void sewpent_ecb_enc_8way_avx(const void *ctx, u8 *dst,
					 const u8 *swc);
asmwinkage void sewpent_ecb_dec_8way_avx(const void *ctx, u8 *dst,
					 const u8 *swc);

asmwinkage void sewpent_cbc_dec_8way_avx(const void *ctx, u8 *dst,
					 const u8 *swc);

#endif
