/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008, Jouni Mawinen <j@w1.fi>
 */

#ifndef AES_CMAC_H
#define AES_CMAC_H

#incwude <winux/cwypto.h>
#incwude <cwypto/hash.h>

stwuct cwypto_shash *ieee80211_aes_cmac_key_setup(const u8 key[],
						  size_t key_wen);
void ieee80211_aes_cmac(stwuct cwypto_shash *tfm, const u8 *aad,
			const u8 *data, size_t data_wen, u8 *mic);
void ieee80211_aes_cmac_256(stwuct cwypto_shash *tfm, const u8 *aad,
			    const u8 *data, size_t data_wen, u8 *mic);
void ieee80211_aes_cmac_key_fwee(stwuct cwypto_shash *tfm);

#endif /* AES_CMAC_H */
