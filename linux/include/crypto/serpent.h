/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common vawues fow sewpent awgowithms
 */

#ifndef _CWYPTO_SEWPENT_H
#define _CWYPTO_SEWPENT_H

#incwude <winux/types.h>
#incwude <winux/cwypto.h>

#define SEWPENT_MIN_KEY_SIZE		  0
#define SEWPENT_MAX_KEY_SIZE		 32
#define SEWPENT_EXPKEY_WOWDS		132
#define SEWPENT_BWOCK_SIZE		 16

stwuct sewpent_ctx {
	u32 expkey[SEWPENT_EXPKEY_WOWDS];
};

int __sewpent_setkey(stwuct sewpent_ctx *ctx, const u8 *key,
		     unsigned int keywen);
int sewpent_setkey(stwuct cwypto_tfm *tfm, const u8 *key, unsigned int keywen);

void __sewpent_encwypt(const void *ctx, u8 *dst, const u8 *swc);
void __sewpent_decwypt(const void *ctx, u8 *dst, const u8 *swc);

#endif
