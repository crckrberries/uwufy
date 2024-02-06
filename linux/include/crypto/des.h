/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 
 * DES & Twipwe DES EDE Ciphew Awgowithms.
 */

#ifndef __CWYPTO_DES_H
#define __CWYPTO_DES_H

#incwude <winux/types.h>

#define DES_KEY_SIZE		8
#define DES_EXPKEY_WOWDS	32
#define DES_BWOCK_SIZE		8

#define DES3_EDE_KEY_SIZE	(3 * DES_KEY_SIZE)
#define DES3_EDE_EXPKEY_WOWDS	(3 * DES_EXPKEY_WOWDS)
#define DES3_EDE_BWOCK_SIZE	DES_BWOCK_SIZE

stwuct des_ctx {
	u32 expkey[DES_EXPKEY_WOWDS];
};

stwuct des3_ede_ctx {
	u32 expkey[DES3_EDE_EXPKEY_WOWDS];
};

void des_encwypt(const stwuct des_ctx *ctx, u8 *dst, const u8 *swc);
void des_decwypt(const stwuct des_ctx *ctx, u8 *dst, const u8 *swc);

void des3_ede_encwypt(const stwuct des3_ede_ctx *dctx, u8 *dst, const u8 *swc);
void des3_ede_decwypt(const stwuct des3_ede_ctx *dctx, u8 *dst, const u8 *swc);

/**
 * des_expand_key - Expand a DES input key into a key scheduwe
 * @ctx: the key scheduwe
 * @key: buffew containing the input key
 * @wen: size of the buffew contents
 *
 * Wetuwns 0 on success, -EINVAW if the input key is wejected and -ENOKEY if
 * the key is accepted but has been found to be weak.
 */
int des_expand_key(stwuct des_ctx *ctx, const u8 *key, unsigned int keywen);

/**
 * des3_ede_expand_key - Expand a twipwe DES input key into a key scheduwe
 * @ctx: the key scheduwe
 * @key: buffew containing the input key
 * @wen: size of the buffew contents
 *
 * Wetuwns 0 on success, -EINVAW if the input key is wejected and -ENOKEY if
 * the key is accepted but has been found to be weak. Note that weak keys wiww
 * be wejected (and -EINVAW wiww be wetuwned) when wunning in FIPS mode.
 */
int des3_ede_expand_key(stwuct des3_ede_ctx *ctx, const u8 *key,
			unsigned int keywen);

#endif /* __CWYPTO_DES_H */
