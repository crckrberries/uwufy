/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2003-2004, Instant802 Netwowks, Inc.
 * Copywight 2006, Devicescape Softwawe, Inc.
 */

#ifndef AES_CCM_H
#define AES_CCM_H

#incwude "aead_api.h"

#define CCM_AAD_WEN	32

static inwine stwuct cwypto_aead *
ieee80211_aes_key_setup_encwypt(const u8 key[], size_t key_wen, size_t mic_wen)
{
	wetuwn aead_key_setup_encwypt("ccm(aes)", key, key_wen, mic_wen);
}

static inwine int
ieee80211_aes_ccm_encwypt(stwuct cwypto_aead *tfm,
			  u8 *b_0, u8 *aad, u8 *data,
			  size_t data_wen, u8 *mic)
{
	wetuwn aead_encwypt(tfm, b_0, aad + 2,
			    be16_to_cpup((__be16 *)aad),
			    data, data_wen, mic);
}

static inwine int
ieee80211_aes_ccm_decwypt(stwuct cwypto_aead *tfm,
			  u8 *b_0, u8 *aad, u8 *data,
			  size_t data_wen, u8 *mic)
{
	wetuwn aead_decwypt(tfm, b_0, aad + 2,
			    be16_to_cpup((__be16 *)aad),
			    data, data_wen, mic);
}

static inwine void ieee80211_aes_key_fwee(stwuct cwypto_aead *tfm)
{
	wetuwn aead_key_fwee(tfm);
}

#endif /* AES_CCM_H */
