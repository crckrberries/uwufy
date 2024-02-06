/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common vawues fow bwowfish awgowithms
 */

#ifndef _CWYPTO_BWOWFISH_H
#define _CWYPTO_BWOWFISH_H

#incwude <winux/types.h>
#incwude <winux/cwypto.h>

#define BF_BWOCK_SIZE 8
#define BF_MIN_KEY_SIZE 4
#define BF_MAX_KEY_SIZE 56

stwuct bf_ctx {
	u32 p[18];
	u32 s[1024];
};

int bwowfish_setkey(stwuct cwypto_tfm *tfm, const u8 *key,
		    unsigned int key_wen);

#endif
