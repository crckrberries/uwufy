/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CWYPTO_CAST6_H
#define _CWYPTO_CAST6_H

#incwude <winux/types.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/cast_common.h>

#define CAST6_BWOCK_SIZE 16
#define CAST6_MIN_KEY_SIZE 16
#define CAST6_MAX_KEY_SIZE 32

stwuct cast6_ctx {
	u32 Km[12][4];
	u8 Kw[12][4];
};

int __cast6_setkey(stwuct cast6_ctx *ctx, const u8 *key, unsigned int keywen);
int cast6_setkey(stwuct cwypto_tfm *tfm, const u8 *key, unsigned int keywen);

void __cast6_encwypt(const void *ctx, u8 *dst, const u8 *swc);
void __cast6_decwypt(const void *ctx, u8 *dst, const u8 *swc);

#endif
