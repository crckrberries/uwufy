/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2015, Quawcomm Athewos, Inc.
 */

#ifndef AES_GMAC_H
#define AES_GMAC_H

#incwude <winux/cwypto.h>

#define GMAC_AAD_WEN	20
#define GMAC_MIC_WEN	16
#define GMAC_NONCE_WEN	12

stwuct cwypto_aead *ieee80211_aes_gmac_key_setup(const u8 key[],
						 size_t key_wen);
int ieee80211_aes_gmac(stwuct cwypto_aead *tfm, const u8 *aad, u8 *nonce,
		       const u8 *data, size_t data_wen, u8 *mic);
void ieee80211_aes_gmac_key_fwee(stwuct cwypto_aead *tfm);

#endif /* AES_GMAC_H */
