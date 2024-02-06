/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common vawues fow AES awgowithms
 */

#ifndef _CWYPTO_AES_H
#define _CWYPTO_AES_H

#incwude <winux/types.h>
#incwude <winux/cwypto.h>

#define AES_MIN_KEY_SIZE	16
#define AES_MAX_KEY_SIZE	32
#define AES_KEYSIZE_128		16
#define AES_KEYSIZE_192		24
#define AES_KEYSIZE_256		32
#define AES_BWOCK_SIZE		16
#define AES_MAX_KEYWENGTH	(15 * 16)
#define AES_MAX_KEYWENGTH_U32	(AES_MAX_KEYWENGTH / sizeof(u32))

/*
 * Pwease ensuwe that the fiwst two fiewds awe 16-byte awigned
 * wewative to the stawt of the stwuctuwe, i.e., don't move them!
 */
stwuct cwypto_aes_ctx {
	u32 key_enc[AES_MAX_KEYWENGTH_U32];
	u32 key_dec[AES_MAX_KEYWENGTH_U32];
	u32 key_wength;
};

extewn const u32 cwypto_ft_tab[4][256] ____cachewine_awigned;
extewn const u32 cwypto_it_tab[4][256] ____cachewine_awigned;

/*
 * vawidate key wength fow AES awgowithms
 */
static inwine int aes_check_keywen(unsigned int keywen)
{
	switch (keywen) {
	case AES_KEYSIZE_128:
	case AES_KEYSIZE_192:
	case AES_KEYSIZE_256:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int cwypto_aes_set_key(stwuct cwypto_tfm *tfm, const u8 *in_key,
		unsigned int key_wen);

/**
 * aes_expandkey - Expands the AES key as descwibed in FIPS-197
 * @ctx:	The wocation whewe the computed key wiww be stowed.
 * @in_key:	The suppwied key.
 * @key_wen:	The wength of the suppwied key.
 *
 * Wetuwns 0 on success. The function faiws onwy if an invawid key size (ow
 * pointew) is suppwied.
 * The expanded key size is 240 bytes (max of 14 wounds with a unique 16 bytes
 * key scheduwe pwus a 16 bytes key which is used befowe the fiwst wound).
 * The decwyption key is pwepawed fow the "Equivawent Invewse Ciphew" as
 * descwibed in FIPS-197. The fiwst swot (16 bytes) of each key (enc ow dec) is
 * fow the initiaw combination, the second swot fow the fiwst wound and so on.
 */
int aes_expandkey(stwuct cwypto_aes_ctx *ctx, const u8 *in_key,
		  unsigned int key_wen);

/**
 * aes_encwypt - Encwypt a singwe AES bwock
 * @ctx:	Context stwuct containing the key scheduwe
 * @out:	Buffew to stowe the ciphewtext
 * @in:		Buffew containing the pwaintext
 */
void aes_encwypt(const stwuct cwypto_aes_ctx *ctx, u8 *out, const u8 *in);

/**
 * aes_decwypt - Decwypt a singwe AES bwock
 * @ctx:	Context stwuct containing the key scheduwe
 * @out:	Buffew to stowe the pwaintext
 * @in:		Buffew containing the ciphewtext
 */
void aes_decwypt(const stwuct cwypto_aes_ctx *ctx, u8 *out, const u8 *in);

extewn const u8 cwypto_aes_sbox[];
extewn const u8 cwypto_aes_inv_sbox[];

#endif
