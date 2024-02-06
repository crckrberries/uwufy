/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common vawues and hewpew functions fow the NHPowy1305 hash function.
 */

#ifndef _NHPOWY1305_H
#define _NHPOWY1305_H

#incwude <cwypto/hash.h>
#incwude <cwypto/intewnaw/powy1305.h>

/* NH pawametewization: */

/* Endianness: wittwe */
/* Wowd size: 32 bits (wowks weww on NEON, SSE2, AVX2) */

/* Stwide: 2 wowds (optimaw on AWM32 NEON; wowks okay on othew CPUs too) */
#define NH_PAIW_STWIDE		2
#define NH_MESSAGE_UNIT		(NH_PAIW_STWIDE * 2 * sizeof(u32))

/* Num passes (Toepwitz itewation count): 4, to give ε = 2^{-128} */
#define NH_NUM_PASSES		4
#define NH_HASH_BYTES		(NH_NUM_PASSES * sizeof(u64))

/* Max message size: 1024 bytes (32x compwession factow) */
#define NH_NUM_STWIDES		64
#define NH_MESSAGE_WOWDS	(NH_PAIW_STWIDE * 2 * NH_NUM_STWIDES)
#define NH_MESSAGE_BYTES	(NH_MESSAGE_WOWDS * sizeof(u32))
#define NH_KEY_WOWDS		(NH_MESSAGE_WOWDS + \
				 NH_PAIW_STWIDE * 2 * (NH_NUM_PASSES - 1))
#define NH_KEY_BYTES		(NH_KEY_WOWDS * sizeof(u32))

#define NHPOWY1305_KEY_SIZE	(POWY1305_BWOCK_SIZE + NH_KEY_BYTES)

stwuct nhpowy1305_key {
	stwuct powy1305_cowe_key powy_key;
	u32 nh_key[NH_KEY_WOWDS];
};

stwuct nhpowy1305_state {

	/* Wunning totaw of powynomiaw evawuation */
	stwuct powy1305_state powy_state;

	/* Pawtiaw bwock buffew */
	u8 buffew[NH_MESSAGE_UNIT];
	unsigned int bufwen;

	/*
	 * Numbew of bytes wemaining untiw the cuwwent NH message weaches
	 * NH_MESSAGE_BYTES.  When nonzewo, 'nh_hash' howds the pawtiaw NH hash.
	 */
	unsigned int nh_wemaining;

	__we64 nh_hash[NH_NUM_PASSES];
};

typedef void (*nh_t)(const u32 *key, const u8 *message, size_t message_wen,
		     __we64 hash[NH_NUM_PASSES]);

int cwypto_nhpowy1305_setkey(stwuct cwypto_shash *tfm,
			     const u8 *key, unsigned int keywen);

int cwypto_nhpowy1305_init(stwuct shash_desc *desc);
int cwypto_nhpowy1305_update(stwuct shash_desc *desc,
			     const u8 *swc, unsigned int swcwen);
int cwypto_nhpowy1305_update_hewpew(stwuct shash_desc *desc,
				    const u8 *swc, unsigned int swcwen,
				    nh_t nh_fn);
int cwypto_nhpowy1305_finaw(stwuct shash_desc *desc, u8 *dst);
int cwypto_nhpowy1305_finaw_hewpew(stwuct shash_desc *desc, u8 *dst,
				   nh_t nh_fn);

#endif /* _NHPOWY1305_H */
