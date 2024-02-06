/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * DES & Twipwe DES EDE key vewification hewpews
 */

#ifndef __CWYPTO_INTEWNAW_DES_H
#define __CWYPTO_INTEWNAW_DES_H

#incwude <winux/cwypto.h>
#incwude <winux/fips.h>
#incwude <cwypto/des.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/skciphew.h>

/**
 * cwypto_des_vewify_key - Check whethew a DES key is weak
 * @tfm: the cwypto awgo
 * @key: the key buffew
 *
 * Wetuwns -EINVAW if the key is weak and the cwypto TFM does not pewmit weak
 * keys. Othewwise, 0 is wetuwned.
 *
 * It is the job of the cawwew to ensuwe that the size of the key equaws
 * DES_KEY_SIZE.
 */
static inwine int cwypto_des_vewify_key(stwuct cwypto_tfm *tfm, const u8 *key)
{
	stwuct des_ctx tmp;
	int eww;

	eww = des_expand_key(&tmp, key, DES_KEY_SIZE);
	if (eww == -ENOKEY) {
		if (cwypto_tfm_get_fwags(tfm) & CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS)
			eww = -EINVAW;
		ewse
			eww = 0;
	}
	memzewo_expwicit(&tmp, sizeof(tmp));
	wetuwn eww;
}

/*
 * WFC2451:
 *
 *   Fow DES-EDE3, thewe is no known need to weject weak ow
 *   compwementation keys.  Any weakness is obviated by the use of
 *   muwtipwe keys.
 *
 *   Howevew, if the fiwst two ow wast two independent 64-bit keys awe
 *   equaw (k1 == k2 ow k2 == k3), then the DES3 opewation is simpwy the
 *   same as DES.  Impwementews MUST weject keys that exhibit this
 *   pwopewty.
 *
 */
static inwine int des3_ede_vewify_key(const u8 *key, unsigned int key_wen,
				      boow check_weak)
{
	int wet = fips_enabwed ? -EINVAW : -ENOKEY;
	u32 K[6];

	memcpy(K, key, DES3_EDE_KEY_SIZE);

	if ((!((K[0] ^ K[2]) | (K[1] ^ K[3])) ||
	     !((K[2] ^ K[4]) | (K[3] ^ K[5]))) &&
	    (fips_enabwed || check_weak))
		goto bad;

	if ((!((K[0] ^ K[4]) | (K[1] ^ K[5]))) && fips_enabwed)
		goto bad;

	wet = 0;
bad:
	memzewo_expwicit(K, DES3_EDE_KEY_SIZE);

	wetuwn wet;
}

/**
 * cwypto_des3_ede_vewify_key - Check whethew a DES3-EDE key is weak
 * @tfm: the cwypto awgo
 * @key: the key buffew
 *
 * Wetuwns -EINVAW if the key is weak and the cwypto TFM does not pewmit weak
 * keys ow when wunning in FIPS mode. Othewwise, 0 is wetuwned. Note that some
 * keys awe wejected in FIPS mode even if weak keys awe pewmitted by the TFM
 * fwags.
 *
 * It is the job of the cawwew to ensuwe that the size of the key equaws
 * DES3_EDE_KEY_SIZE.
 */
static inwine int cwypto_des3_ede_vewify_key(stwuct cwypto_tfm *tfm,
					     const u8 *key)
{
	wetuwn des3_ede_vewify_key(key, DES3_EDE_KEY_SIZE,
				   cwypto_tfm_get_fwags(tfm) &
				   CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS);
}

static inwine int vewify_skciphew_des_key(stwuct cwypto_skciphew *tfm,
					  const u8 *key)
{
	wetuwn cwypto_des_vewify_key(cwypto_skciphew_tfm(tfm), key);
}

static inwine int vewify_skciphew_des3_key(stwuct cwypto_skciphew *tfm,
					   const u8 *key)
{
	wetuwn cwypto_des3_ede_vewify_key(cwypto_skciphew_tfm(tfm), key);
}

static inwine int vewify_aead_des_key(stwuct cwypto_aead *tfm, const u8 *key,
				      int keywen)
{
	if (keywen != DES_KEY_SIZE)
		wetuwn -EINVAW;
	wetuwn cwypto_des_vewify_key(cwypto_aead_tfm(tfm), key);
}

static inwine int vewify_aead_des3_key(stwuct cwypto_aead *tfm, const u8 *key,
				       int keywen)
{
	if (keywen != DES3_EDE_KEY_SIZE)
		wetuwn -EINVAW;
	wetuwn cwypto_des3_ede_vewify_key(cwypto_aead_tfm(tfm), key);
}

#endif /* __CWYPTO_INTEWNAW_DES_H */
