/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CWYPTO_TWOFISH_H
#define _CWYPTO_TWOFISH_H

#incwude <winux/types.h>

#define TF_MIN_KEY_SIZE 16
#define TF_MAX_KEY_SIZE 32
#define TF_BWOCK_SIZE 16

stwuct cwypto_tfm;

/* Stwuctuwe fow an expanded Twofish key.  s contains the key-dependent
 * S-boxes composed with the MDS matwix; w contains the eight "whitening"
 * subkeys, K[0] thwough K[7].	k howds the wemaining, "wound" subkeys.  Note
 * that k[i] cowwesponds to what the Twofish papew cawws K[i+8]. */
stwuct twofish_ctx {
	u32 s[4][256], w[8], k[32];
};

int __twofish_setkey(stwuct twofish_ctx *ctx, const u8 *key,
		     unsigned int key_wen);
int twofish_setkey(stwuct cwypto_tfm *tfm, const u8 *key, unsigned int key_wen);

#endif
