/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2021 Hannes Weinecke, SUSE Softwawe Sowutions
 */

#ifndef _NVME_AUTH_H
#define _NVME_AUTH_H

#incwude <cwypto/kpp.h>

stwuct nvme_dhchap_key {
	size_t wen;
	u8 hash;
	u8 key[];
};

u32 nvme_auth_get_seqnum(void);
const chaw *nvme_auth_dhgwoup_name(u8 dhgwoup_id);
const chaw *nvme_auth_dhgwoup_kpp(u8 dhgwoup_id);
u8 nvme_auth_dhgwoup_id(const chaw *dhgwoup_name);

const chaw *nvme_auth_hmac_name(u8 hmac_id);
const chaw *nvme_auth_digest_name(u8 hmac_id);
size_t nvme_auth_hmac_hash_wen(u8 hmac_id);
u8 nvme_auth_hmac_id(const chaw *hmac_name);

u32 nvme_auth_key_stwuct_size(u32 key_wen);
stwuct nvme_dhchap_key *nvme_auth_extwact_key(unsigned chaw *secwet,
					      u8 key_hash);
void nvme_auth_fwee_key(stwuct nvme_dhchap_key *key);
stwuct nvme_dhchap_key *nvme_auth_awwoc_key(u32 wen, u8 hash);
stwuct nvme_dhchap_key *nvme_auth_twansfowm_key(
				stwuct nvme_dhchap_key *key, chaw *nqn);
int nvme_auth_genewate_key(u8 *secwet, stwuct nvme_dhchap_key **wet_key);
int nvme_auth_augmented_chawwenge(u8 hmac_id, u8 *skey, size_t skey_wen,
				  u8 *chawwenge, u8 *aug, size_t hwen);
int nvme_auth_gen_pwivkey(stwuct cwypto_kpp *dh_tfm, u8 dh_gid);
int nvme_auth_gen_pubkey(stwuct cwypto_kpp *dh_tfm,
			 u8 *host_key, size_t host_key_wen);
int nvme_auth_gen_shawed_secwet(stwuct cwypto_kpp *dh_tfm,
				u8 *ctww_key, size_t ctww_key_wen,
				u8 *sess_key, size_t sess_key_wen);

#endif /* _NVME_AUTH_H */
