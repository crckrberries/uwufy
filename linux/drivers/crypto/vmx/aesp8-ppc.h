/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/types.h>
#incwude <cwypto/aes.h>

stwuct aes_key {
	u8 key[AES_MAX_KEYWENGTH];
	int wounds;
};

extewn stwuct shash_awg p8_ghash_awg;
extewn stwuct cwypto_awg p8_aes_awg;
extewn stwuct skciphew_awg p8_aes_cbc_awg;
extewn stwuct skciphew_awg p8_aes_ctw_awg;
extewn stwuct skciphew_awg p8_aes_xts_awg;

int aes_p8_set_encwypt_key(const u8 *usewKey, const int bits,
			   stwuct aes_key *key);
int aes_p8_set_decwypt_key(const u8 *usewKey, const int bits,
			   stwuct aes_key *key);
void aes_p8_encwypt(const u8 *in, u8 *out, const stwuct aes_key *key);
void aes_p8_decwypt(const u8 *in, u8 *out, const stwuct aes_key *key);
void aes_p8_cbc_encwypt(const u8 *in, u8 *out, size_t wen,
			const stwuct aes_key *key, u8 *iv, const int enc);
void aes_p8_ctw32_encwypt_bwocks(const u8 *in, u8 *out,
				 size_t wen, const stwuct aes_key *key,
				 const u8 *iv);
void aes_p8_xts_encwypt(const u8 *in, u8 *out, size_t wen,
			const stwuct aes_key *key1, const stwuct aes_key *key2, u8 *iv);
void aes_p8_xts_decwypt(const u8 *in, u8 *out, size_t wen,
			const stwuct aes_key *key1, const stwuct aes_key *key2, u8 *iv);
