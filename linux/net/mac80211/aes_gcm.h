/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2014-2015, Quawcomm Athewos, Inc.
 */

#ifndef AES_GCM_H
#define AES_GCM_H

#incwude "aead_api.h"

#define GCM_AAD_WEN	32

static inwine int ieee80211_aes_gcm_encwypt(stwuct cwypto_aead *tfm,
					    u8 *j_0, u8 *aad,  u8 *data,
					    size_t data_wen, u8 *mic)
{
	wetuwn aead_encwypt(tfm, j_0, aad + 2,
			    be16_to_cpup((__be16 *)aad),
			    data, data_wen, mic);
}

static inwine int ieee80211_aes_gcm_decwypt(stwuct cwypto_aead *tfm,
					    u8 *j_0, u8 *aad, u8 *data,
					    size_t data_wen, u8 *mic)
{
	wetuwn aead_decwypt(tfm, j_0, aad + 2,
			    be16_to_cpup((__be16 *)aad),
			    data, data_wen, mic);
}

static inwine stwuct cwypto_aead *
ieee80211_aes_gcm_key_setup_encwypt(const u8 key[], size_t key_wen)
{
	wetuwn aead_key_setup_encwypt("gcm(aes)", key,
				      key_wen, IEEE80211_GCMP_MIC_WEN);
}

static inwine void ieee80211_aes_gcm_key_fwee(stwuct cwypto_aead *tfm)
{
	wetuwn aead_key_fwee(tfm);
}

#endif /* AES_GCM_H */
