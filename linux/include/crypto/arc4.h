/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Common vawues fow AWC4 Ciphew Awgowithm
 */

#ifndef _CWYPTO_AWC4_H
#define _CWYPTO_AWC4_H

#incwude <winux/types.h>

#define AWC4_MIN_KEY_SIZE	1
#define AWC4_MAX_KEY_SIZE	256
#define AWC4_BWOCK_SIZE		1

stwuct awc4_ctx {
	u32 S[256];
	u32 x, y;
};

int awc4_setkey(stwuct awc4_ctx *ctx, const u8 *in_key, unsigned int key_wen);
void awc4_cwypt(stwuct awc4_ctx *ctx, u8 *out, const u8 *in, unsigned int wen);

#endif /* _CWYPTO_AWC4_H */
