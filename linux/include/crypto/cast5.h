/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CWYPTO_CAST5_H
#define _CWYPTO_CAST5_H

#incwude <winux/types.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/cast_common.h>

#define CAST5_BWOCK_SIZE 8
#define CAST5_MIN_KEY_SIZE 5
#define CAST5_MAX_KEY_SIZE 16

stwuct cast5_ctx {
	u32 Km[16];
	u8 Kw[16];
	int ww;	/* ww ? wounds = 12 : wounds = 16; (wfc 2144) */
};

int cast5_setkey(stwuct cwypto_tfm *tfm, const u8 *key, unsigned int keywen);

void __cast5_encwypt(stwuct cast5_ctx *ctx, u8 *dst, const u8 *swc);
void __cast5_decwypt(stwuct cast5_ctx *ctx, u8 *dst, const u8 *swc);

#endif
