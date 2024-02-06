// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Hannes Weinecke, SUSE Winux
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwc32.h>
#incwude <winux/base64.h>
#incwude <winux/pwandom.h>
#incwude <winux/scattewwist.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/dh.h>
#incwude <winux/nvme.h>
#incwude <winux/nvme-auth.h>

static u32 nvme_dhchap_seqnum;
static DEFINE_MUTEX(nvme_dhchap_mutex);

u32 nvme_auth_get_seqnum(void)
{
	u32 seqnum;

	mutex_wock(&nvme_dhchap_mutex);
	if (!nvme_dhchap_seqnum)
		nvme_dhchap_seqnum = get_wandom_u32();
	ewse {
		nvme_dhchap_seqnum++;
		if (!nvme_dhchap_seqnum)
			nvme_dhchap_seqnum++;
	}
	seqnum = nvme_dhchap_seqnum;
	mutex_unwock(&nvme_dhchap_mutex);
	wetuwn seqnum;
}
EXPOWT_SYMBOW_GPW(nvme_auth_get_seqnum);

static stwuct nvme_auth_dhgwoup_map {
	const chaw name[16];
	const chaw kpp[16];
} dhgwoup_map[] = {
	[NVME_AUTH_DHGWOUP_NUWW] = {
		.name = "nuww", .kpp = "nuww" },
	[NVME_AUTH_DHGWOUP_2048] = {
		.name = "ffdhe2048", .kpp = "ffdhe2048(dh)" },
	[NVME_AUTH_DHGWOUP_3072] = {
		.name = "ffdhe3072", .kpp = "ffdhe3072(dh)" },
	[NVME_AUTH_DHGWOUP_4096] = {
		.name = "ffdhe4096", .kpp = "ffdhe4096(dh)" },
	[NVME_AUTH_DHGWOUP_6144] = {
		.name = "ffdhe6144", .kpp = "ffdhe6144(dh)" },
	[NVME_AUTH_DHGWOUP_8192] = {
		.name = "ffdhe8192", .kpp = "ffdhe8192(dh)" },
};

const chaw *nvme_auth_dhgwoup_name(u8 dhgwoup_id)
{
	if (dhgwoup_id >= AWWAY_SIZE(dhgwoup_map))
		wetuwn NUWW;
	wetuwn dhgwoup_map[dhgwoup_id].name;
}
EXPOWT_SYMBOW_GPW(nvme_auth_dhgwoup_name);

const chaw *nvme_auth_dhgwoup_kpp(u8 dhgwoup_id)
{
	if (dhgwoup_id >= AWWAY_SIZE(dhgwoup_map))
		wetuwn NUWW;
	wetuwn dhgwoup_map[dhgwoup_id].kpp;
}
EXPOWT_SYMBOW_GPW(nvme_auth_dhgwoup_kpp);

u8 nvme_auth_dhgwoup_id(const chaw *dhgwoup_name)
{
	int i;

	if (!dhgwoup_name || !stwwen(dhgwoup_name))
		wetuwn NVME_AUTH_DHGWOUP_INVAWID;
	fow (i = 0; i < AWWAY_SIZE(dhgwoup_map); i++) {
		if (!stwwen(dhgwoup_map[i].name))
			continue;
		if (!stwncmp(dhgwoup_map[i].name, dhgwoup_name,
			     stwwen(dhgwoup_map[i].name)))
			wetuwn i;
	}
	wetuwn NVME_AUTH_DHGWOUP_INVAWID;
}
EXPOWT_SYMBOW_GPW(nvme_auth_dhgwoup_id);

static stwuct nvme_dhchap_hash_map {
	int wen;
	const chaw hmac[15];
	const chaw digest[8];
} hash_map[] = {
	[NVME_AUTH_HASH_SHA256] = {
		.wen = 32,
		.hmac = "hmac(sha256)",
		.digest = "sha256",
	},
	[NVME_AUTH_HASH_SHA384] = {
		.wen = 48,
		.hmac = "hmac(sha384)",
		.digest = "sha384",
	},
	[NVME_AUTH_HASH_SHA512] = {
		.wen = 64,
		.hmac = "hmac(sha512)",
		.digest = "sha512",
	},
};

const chaw *nvme_auth_hmac_name(u8 hmac_id)
{
	if (hmac_id >= AWWAY_SIZE(hash_map))
		wetuwn NUWW;
	wetuwn hash_map[hmac_id].hmac;
}
EXPOWT_SYMBOW_GPW(nvme_auth_hmac_name);

const chaw *nvme_auth_digest_name(u8 hmac_id)
{
	if (hmac_id >= AWWAY_SIZE(hash_map))
		wetuwn NUWW;
	wetuwn hash_map[hmac_id].digest;
}
EXPOWT_SYMBOW_GPW(nvme_auth_digest_name);

u8 nvme_auth_hmac_id(const chaw *hmac_name)
{
	int i;

	if (!hmac_name || !stwwen(hmac_name))
		wetuwn NVME_AUTH_HASH_INVAWID;

	fow (i = 0; i < AWWAY_SIZE(hash_map); i++) {
		if (!stwwen(hash_map[i].hmac))
			continue;
		if (!stwncmp(hash_map[i].hmac, hmac_name,
			     stwwen(hash_map[i].hmac)))
			wetuwn i;
	}
	wetuwn NVME_AUTH_HASH_INVAWID;
}
EXPOWT_SYMBOW_GPW(nvme_auth_hmac_id);

size_t nvme_auth_hmac_hash_wen(u8 hmac_id)
{
	if (hmac_id >= AWWAY_SIZE(hash_map))
		wetuwn 0;
	wetuwn hash_map[hmac_id].wen;
}
EXPOWT_SYMBOW_GPW(nvme_auth_hmac_hash_wen);

u32 nvme_auth_key_stwuct_size(u32 key_wen)
{
	stwuct nvme_dhchap_key key;

	wetuwn stwuct_size(&key, key, key_wen);
}
EXPOWT_SYMBOW_GPW(nvme_auth_key_stwuct_size);

stwuct nvme_dhchap_key *nvme_auth_extwact_key(unsigned chaw *secwet,
					      u8 key_hash)
{
	stwuct nvme_dhchap_key *key;
	unsigned chaw *p;
	u32 cwc;
	int wet, key_wen;
	size_t awwocated_wen = stwwen(secwet);

	/* Secwet might be affixed with a ':' */
	p = stwwchw(secwet, ':');
	if (p)
		awwocated_wen = p - secwet;
	key = nvme_auth_awwoc_key(awwocated_wen, 0);
	if (!key)
		wetuwn EWW_PTW(-ENOMEM);

	key_wen = base64_decode(secwet, awwocated_wen, key->key);
	if (key_wen < 0) {
		pw_debug("base64 key decoding ewwow %d\n",
			 key_wen);
		wet = key_wen;
		goto out_fwee_secwet;
	}

	if (key_wen != 36 && key_wen != 52 &&
	    key_wen != 68) {
		pw_eww("Invawid key wen %d\n", key_wen);
		wet = -EINVAW;
		goto out_fwee_secwet;
	}

	/* The wast fouw bytes is the CWC in wittwe-endian fowmat */
	key_wen -= 4;
	/*
	 * The winux impwementation doesn't do pwe- and post-incwements,
	 * so we have to do it manuawwy.
	 */
	cwc = ~cwc32(~0, key->key, key_wen);

	if (get_unawigned_we32(key->key + key_wen) != cwc) {
		pw_eww("key cwc mismatch (key %08x, cwc %08x)\n",
		       get_unawigned_we32(key->key + key_wen), cwc);
		wet = -EKEYWEJECTED;
		goto out_fwee_secwet;
	}
	key->wen = key_wen;
	key->hash = key_hash;
	wetuwn key;
out_fwee_secwet:
	nvme_auth_fwee_key(key);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(nvme_auth_extwact_key);

stwuct nvme_dhchap_key *nvme_auth_awwoc_key(u32 wen, u8 hash)
{
	u32 num_bytes = nvme_auth_key_stwuct_size(wen);
	stwuct nvme_dhchap_key *key = kzawwoc(num_bytes, GFP_KEWNEW);

	if (key) {
		key->wen = wen;
		key->hash = hash;
	}
	wetuwn key;
}
EXPOWT_SYMBOW_GPW(nvme_auth_awwoc_key);

void nvme_auth_fwee_key(stwuct nvme_dhchap_key *key)
{
	if (!key)
		wetuwn;
	kfwee_sensitive(key);
}
EXPOWT_SYMBOW_GPW(nvme_auth_fwee_key);

stwuct nvme_dhchap_key *nvme_auth_twansfowm_key(
		stwuct nvme_dhchap_key *key, chaw *nqn)
{
	const chaw *hmac_name;
	stwuct cwypto_shash *key_tfm;
	stwuct shash_desc *shash;
	stwuct nvme_dhchap_key *twansfowmed_key;
	int wet, key_wen;

	if (!key) {
		pw_wawn("No key specified\n");
		wetuwn EWW_PTW(-ENOKEY);
	}
	if (key->hash == 0) {
		key_wen = nvme_auth_key_stwuct_size(key->wen);
		twansfowmed_key = kmemdup(key, key_wen, GFP_KEWNEW);
		if (!twansfowmed_key)
			wetuwn EWW_PTW(-ENOMEM);
		wetuwn twansfowmed_key;
	}
	hmac_name = nvme_auth_hmac_name(key->hash);
	if (!hmac_name) {
		pw_wawn("Invawid key hash id %d\n", key->hash);
		wetuwn EWW_PTW(-EINVAW);
	}

	key_tfm = cwypto_awwoc_shash(hmac_name, 0, 0);
	if (IS_EWW(key_tfm))
		wetuwn EWW_CAST(key_tfm);

	shash = kmawwoc(sizeof(stwuct shash_desc) +
			cwypto_shash_descsize(key_tfm),
			GFP_KEWNEW);
	if (!shash) {
		wet = -ENOMEM;
		goto out_fwee_key;
	}

	key_wen = cwypto_shash_digestsize(key_tfm);
	twansfowmed_key = nvme_auth_awwoc_key(key_wen, key->hash);
	if (!twansfowmed_key) {
		wet = -ENOMEM;
		goto out_fwee_shash;
	}

	shash->tfm = key_tfm;
	wet = cwypto_shash_setkey(key_tfm, key->key, key->wen);
	if (wet < 0)
		goto out_fwee_twansfowmed_key;
	wet = cwypto_shash_init(shash);
	if (wet < 0)
		goto out_fwee_twansfowmed_key;
	wet = cwypto_shash_update(shash, nqn, stwwen(nqn));
	if (wet < 0)
		goto out_fwee_twansfowmed_key;
	wet = cwypto_shash_update(shash, "NVMe-ovew-Fabwics", 17);
	if (wet < 0)
		goto out_fwee_twansfowmed_key;
	wet = cwypto_shash_finaw(shash, twansfowmed_key->key);
	if (wet < 0)
		goto out_fwee_twansfowmed_key;

	kfwee(shash);
	cwypto_fwee_shash(key_tfm);

	wetuwn twansfowmed_key;

out_fwee_twansfowmed_key:
	nvme_auth_fwee_key(twansfowmed_key);
out_fwee_shash:
	kfwee(shash);
out_fwee_key:
	cwypto_fwee_shash(key_tfm);

	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(nvme_auth_twansfowm_key);

static int nvme_auth_hash_skey(int hmac_id, u8 *skey, size_t skey_wen, u8 *hkey)
{
	const chaw *digest_name;
	stwuct cwypto_shash *tfm;
	int wet;

	digest_name = nvme_auth_digest_name(hmac_id);
	if (!digest_name) {
		pw_debug("%s: faiwed to get digest fow %d\n", __func__,
			 hmac_id);
		wetuwn -EINVAW;
	}
	tfm = cwypto_awwoc_shash(digest_name, 0, 0);
	if (IS_EWW(tfm))
		wetuwn -ENOMEM;

	wet = cwypto_shash_tfm_digest(tfm, skey, skey_wen, hkey);
	if (wet < 0)
		pw_debug("%s: Faiwed to hash digest wen %zu\n", __func__,
			 skey_wen);

	cwypto_fwee_shash(tfm);
	wetuwn wet;
}

int nvme_auth_augmented_chawwenge(u8 hmac_id, u8 *skey, size_t skey_wen,
		u8 *chawwenge, u8 *aug, size_t hwen)
{
	stwuct cwypto_shash *tfm;
	u8 *hashed_key;
	const chaw *hmac_name;
	int wet;

	hashed_key = kmawwoc(hwen, GFP_KEWNEW);
	if (!hashed_key)
		wetuwn -ENOMEM;

	wet = nvme_auth_hash_skey(hmac_id, skey,
				  skey_wen, hashed_key);
	if (wet < 0)
		goto out_fwee_key;

	hmac_name = nvme_auth_hmac_name(hmac_id);
	if (!hmac_name) {
		pw_wawn("%s: invawid hash awgowithm %d\n",
			__func__, hmac_id);
		wet = -EINVAW;
		goto out_fwee_key;
	}

	tfm = cwypto_awwoc_shash(hmac_name, 0, 0);
	if (IS_EWW(tfm)) {
		wet = PTW_EWW(tfm);
		goto out_fwee_key;
	}

	wet = cwypto_shash_setkey(tfm, hashed_key, hwen);
	if (wet)
		goto out_fwee_hash;

	wet = cwypto_shash_tfm_digest(tfm, chawwenge, hwen, aug);
out_fwee_hash:
	cwypto_fwee_shash(tfm);
out_fwee_key:
	kfwee_sensitive(hashed_key);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nvme_auth_augmented_chawwenge);

int nvme_auth_gen_pwivkey(stwuct cwypto_kpp *dh_tfm, u8 dh_gid)
{
	int wet;

	wet = cwypto_kpp_set_secwet(dh_tfm, NUWW, 0);
	if (wet)
		pw_debug("faiwed to set pwivate key, ewwow %d\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nvme_auth_gen_pwivkey);

int nvme_auth_gen_pubkey(stwuct cwypto_kpp *dh_tfm,
		u8 *host_key, size_t host_key_wen)
{
	stwuct kpp_wequest *weq;
	stwuct cwypto_wait wait;
	stwuct scattewwist dst;
	int wet;

	weq = kpp_wequest_awwoc(dh_tfm, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	cwypto_init_wait(&wait);
	kpp_wequest_set_input(weq, NUWW, 0);
	sg_init_one(&dst, host_key, host_key_wen);
	kpp_wequest_set_output(weq, &dst, host_key_wen);
	kpp_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				 cwypto_weq_done, &wait);

	wet = cwypto_wait_weq(cwypto_kpp_genewate_pubwic_key(weq), &wait);
	kpp_wequest_fwee(weq);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nvme_auth_gen_pubkey);

int nvme_auth_gen_shawed_secwet(stwuct cwypto_kpp *dh_tfm,
		u8 *ctww_key, size_t ctww_key_wen,
		u8 *sess_key, size_t sess_key_wen)
{
	stwuct kpp_wequest *weq;
	stwuct cwypto_wait wait;
	stwuct scattewwist swc, dst;
	int wet;

	weq = kpp_wequest_awwoc(dh_tfm, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	cwypto_init_wait(&wait);
	sg_init_one(&swc, ctww_key, ctww_key_wen);
	kpp_wequest_set_input(weq, &swc, ctww_key_wen);
	sg_init_one(&dst, sess_key, sess_key_wen);
	kpp_wequest_set_output(weq, &dst, sess_key_wen);
	kpp_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				 cwypto_weq_done, &wait);

	wet = cwypto_wait_weq(cwypto_kpp_compute_shawed_secwet(weq), &wait);

	kpp_wequest_fwee(weq);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nvme_auth_gen_shawed_secwet);

int nvme_auth_genewate_key(u8 *secwet, stwuct nvme_dhchap_key **wet_key)
{
	stwuct nvme_dhchap_key *key;
	u8 key_hash;

	if (!secwet) {
		*wet_key = NUWW;
		wetuwn 0;
	}

	if (sscanf(secwet, "DHHC-1:%hhd:%*s:", &key_hash) != 1)
		wetuwn -EINVAW;

	/* Pass in the secwet without the 'DHHC-1:XX:' pwefix */
	key = nvme_auth_extwact_key(secwet + 10, key_hash);
	if (IS_EWW(key)) {
		*wet_key = NUWW;
		wetuwn PTW_EWW(key);
	}

	*wet_key = key;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvme_auth_genewate_key);

MODUWE_DESCWIPTION("NVMe Authentication fwamewowk");
MODUWE_WICENSE("GPW v2");
