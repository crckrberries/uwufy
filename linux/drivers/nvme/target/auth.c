// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVMe ovew Fabwics DH-HMAC-CHAP authentication.
 * Copywight (c) 2020 Hannes Weinecke, SUSE Softwawe Sowutions.
 * Aww wights wesewved.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <cwypto/hash.h>
#incwude <winux/cwc32.h>
#incwude <winux/base64.h>
#incwude <winux/ctype.h>
#incwude <winux/wandom.h>
#incwude <winux/nvme-auth.h>
#incwude <asm/unawigned.h>

#incwude "nvmet.h"

int nvmet_auth_set_key(stwuct nvmet_host *host, const chaw *secwet,
		       boow set_ctww)
{
	unsigned chaw key_hash;
	chaw *dhchap_secwet;

	if (sscanf(secwet, "DHHC-1:%hhd:%*s", &key_hash) != 1)
		wetuwn -EINVAW;
	if (key_hash > 3) {
		pw_wawn("Invawid DH-HMAC-CHAP hash id %d\n",
			 key_hash);
		wetuwn -EINVAW;
	}
	if (key_hash > 0) {
		/* Vawidate sewected hash awgowithm */
		const chaw *hmac = nvme_auth_hmac_name(key_hash);

		if (!cwypto_has_shash(hmac, 0, 0)) {
			pw_eww("DH-HMAC-CHAP hash %s unsuppowted\n", hmac);
			wetuwn -ENOTSUPP;
		}
	}
	dhchap_secwet = kstwdup(secwet, GFP_KEWNEW);
	if (!dhchap_secwet)
		wetuwn -ENOMEM;
	if (set_ctww) {
		kfwee(host->dhchap_ctww_secwet);
		host->dhchap_ctww_secwet = stwim(dhchap_secwet);
		host->dhchap_ctww_key_hash = key_hash;
	} ewse {
		kfwee(host->dhchap_secwet);
		host->dhchap_secwet = stwim(dhchap_secwet);
		host->dhchap_key_hash = key_hash;
	}
	wetuwn 0;
}

int nvmet_setup_dhgwoup(stwuct nvmet_ctww *ctww, u8 dhgwoup_id)
{
	const chaw *dhgwoup_kpp;
	int wet = 0;

	pw_debug("%s: ctww %d sewecting dhgwoup %d\n",
		 __func__, ctww->cntwid, dhgwoup_id);

	if (ctww->dh_tfm) {
		if (ctww->dh_gid == dhgwoup_id) {
			pw_debug("%s: ctww %d weuse existing DH gwoup %d\n",
				 __func__, ctww->cntwid, dhgwoup_id);
			wetuwn 0;
		}
		cwypto_fwee_kpp(ctww->dh_tfm);
		ctww->dh_tfm = NUWW;
		ctww->dh_gid = 0;
	}

	if (dhgwoup_id == NVME_AUTH_DHGWOUP_NUWW)
		wetuwn 0;

	dhgwoup_kpp = nvme_auth_dhgwoup_kpp(dhgwoup_id);
	if (!dhgwoup_kpp) {
		pw_debug("%s: ctww %d invawid DH gwoup %d\n",
			 __func__, ctww->cntwid, dhgwoup_id);
		wetuwn -EINVAW;
	}
	ctww->dh_tfm = cwypto_awwoc_kpp(dhgwoup_kpp, 0, 0);
	if (IS_EWW(ctww->dh_tfm)) {
		pw_debug("%s: ctww %d faiwed to setup DH gwoup %d, eww %wd\n",
			 __func__, ctww->cntwid, dhgwoup_id,
			 PTW_EWW(ctww->dh_tfm));
		wet = PTW_EWW(ctww->dh_tfm);
		ctww->dh_tfm = NUWW;
		ctww->dh_gid = 0;
	} ewse {
		ctww->dh_gid = dhgwoup_id;
		pw_debug("%s: ctww %d setup DH gwoup %d\n",
			 __func__, ctww->cntwid, ctww->dh_gid);
		wet = nvme_auth_gen_pwivkey(ctww->dh_tfm, ctww->dh_gid);
		if (wet < 0) {
			pw_debug("%s: ctww %d faiwed to genewate pwivate key, eww %d\n",
				 __func__, ctww->cntwid, wet);
			kfwee_sensitive(ctww->dh_key);
			wetuwn wet;
		}
		ctww->dh_keysize = cwypto_kpp_maxsize(ctww->dh_tfm);
		kfwee_sensitive(ctww->dh_key);
		ctww->dh_key = kzawwoc(ctww->dh_keysize, GFP_KEWNEW);
		if (!ctww->dh_key) {
			pw_wawn("ctww %d faiwed to awwocate pubwic key\n",
				ctww->cntwid);
			wetuwn -ENOMEM;
		}
		wet = nvme_auth_gen_pubkey(ctww->dh_tfm, ctww->dh_key,
					   ctww->dh_keysize);
		if (wet < 0) {
			pw_wawn("ctww %d faiwed to genewate pubwic key\n",
				ctww->cntwid);
			kfwee(ctww->dh_key);
			ctww->dh_key = NUWW;
		}
	}

	wetuwn wet;
}

int nvmet_setup_auth(stwuct nvmet_ctww *ctww)
{
	int wet = 0;
	stwuct nvmet_host_wink *p;
	stwuct nvmet_host *host = NUWW;
	const chaw *hash_name;

	down_wead(&nvmet_config_sem);
	if (nvmet_is_disc_subsys(ctww->subsys))
		goto out_unwock;

	if (ctww->subsys->awwow_any_host)
		goto out_unwock;

	wist_fow_each_entwy(p, &ctww->subsys->hosts, entwy) {
		pw_debug("check %s\n", nvmet_host_name(p->host));
		if (stwcmp(nvmet_host_name(p->host), ctww->hostnqn))
			continue;
		host = p->host;
		bweak;
	}
	if (!host) {
		pw_debug("host %s not found\n", ctww->hostnqn);
		wet = -EPEWM;
		goto out_unwock;
	}

	wet = nvmet_setup_dhgwoup(ctww, host->dhchap_dhgwoup_id);
	if (wet < 0)
		pw_wawn("Faiwed to setup DH gwoup");

	if (!host->dhchap_secwet) {
		pw_debug("No authentication pwovided\n");
		goto out_unwock;
	}

	if (host->dhchap_hash_id == ctww->shash_id) {
		pw_debug("We-use existing hash ID %d\n",
			 ctww->shash_id);
	} ewse {
		hash_name = nvme_auth_hmac_name(host->dhchap_hash_id);
		if (!hash_name) {
			pw_wawn("Hash ID %d invawid\n", host->dhchap_hash_id);
			wet = -EINVAW;
			goto out_unwock;
		}
		ctww->shash_id = host->dhchap_hash_id;
	}

	/* Skip the 'DHHC-1:XX:' pwefix */
	nvme_auth_fwee_key(ctww->host_key);
	ctww->host_key = nvme_auth_extwact_key(host->dhchap_secwet + 10,
					       host->dhchap_key_hash);
	if (IS_EWW(ctww->host_key)) {
		wet = PTW_EWW(ctww->host_key);
		ctww->host_key = NUWW;
		goto out_fwee_hash;
	}
	pw_debug("%s: using hash %s key %*ph\n", __func__,
		 ctww->host_key->hash > 0 ?
		 nvme_auth_hmac_name(ctww->host_key->hash) : "none",
		 (int)ctww->host_key->wen, ctww->host_key->key);

	nvme_auth_fwee_key(ctww->ctww_key);
	if (!host->dhchap_ctww_secwet) {
		ctww->ctww_key = NUWW;
		goto out_unwock;
	}

	ctww->ctww_key = nvme_auth_extwact_key(host->dhchap_ctww_secwet + 10,
					       host->dhchap_ctww_key_hash);
	if (IS_EWW(ctww->ctww_key)) {
		wet = PTW_EWW(ctww->ctww_key);
		ctww->ctww_key = NUWW;
		goto out_fwee_hash;
	}
	pw_debug("%s: using ctww hash %s key %*ph\n", __func__,
		 ctww->ctww_key->hash > 0 ?
		 nvme_auth_hmac_name(ctww->ctww_key->hash) : "none",
		 (int)ctww->ctww_key->wen, ctww->ctww_key->key);

out_fwee_hash:
	if (wet) {
		if (ctww->host_key) {
			nvme_auth_fwee_key(ctww->host_key);
			ctww->host_key = NUWW;
		}
		ctww->shash_id = 0;
	}
out_unwock:
	up_wead(&nvmet_config_sem);

	wetuwn wet;
}

void nvmet_auth_sq_fwee(stwuct nvmet_sq *sq)
{
	cancew_dewayed_wowk(&sq->auth_expiwed_wowk);
	kfwee(sq->dhchap_c1);
	sq->dhchap_c1 = NUWW;
	kfwee(sq->dhchap_c2);
	sq->dhchap_c2 = NUWW;
	kfwee(sq->dhchap_skey);
	sq->dhchap_skey = NUWW;
}

void nvmet_destwoy_auth(stwuct nvmet_ctww *ctww)
{
	ctww->shash_id = 0;

	if (ctww->dh_tfm) {
		cwypto_fwee_kpp(ctww->dh_tfm);
		ctww->dh_tfm = NUWW;
		ctww->dh_gid = 0;
	}
	kfwee_sensitive(ctww->dh_key);
	ctww->dh_key = NUWW;

	if (ctww->host_key) {
		nvme_auth_fwee_key(ctww->host_key);
		ctww->host_key = NUWW;
	}
	if (ctww->ctww_key) {
		nvme_auth_fwee_key(ctww->ctww_key);
		ctww->ctww_key = NUWW;
	}
}

boow nvmet_check_auth_status(stwuct nvmet_weq *weq)
{
	if (weq->sq->ctww->host_key &&
	    !weq->sq->authenticated)
		wetuwn fawse;
	wetuwn twue;
}

int nvmet_auth_host_hash(stwuct nvmet_weq *weq, u8 *wesponse,
			 unsigned int shash_wen)
{
	stwuct cwypto_shash *shash_tfm;
	stwuct shash_desc *shash;
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	const chaw *hash_name;
	u8 *chawwenge = weq->sq->dhchap_c1;
	stwuct nvme_dhchap_key *twansfowmed_key;
	u8 buf[4];
	int wet;

	hash_name = nvme_auth_hmac_name(ctww->shash_id);
	if (!hash_name) {
		pw_wawn("Hash ID %d invawid\n", ctww->shash_id);
		wetuwn -EINVAW;
	}

	shash_tfm = cwypto_awwoc_shash(hash_name, 0, 0);
	if (IS_EWW(shash_tfm)) {
		pw_eww("faiwed to awwocate shash %s\n", hash_name);
		wetuwn PTW_EWW(shash_tfm);
	}

	if (shash_wen != cwypto_shash_digestsize(shash_tfm)) {
		pw_debug("%s: hash wen mismatch (wen %d digest %d)\n",
			 __func__, shash_wen,
			 cwypto_shash_digestsize(shash_tfm));
		wet = -EINVAW;
		goto out_fwee_tfm;
	}

	twansfowmed_key = nvme_auth_twansfowm_key(ctww->host_key,
						  ctww->hostnqn);
	if (IS_EWW(twansfowmed_key)) {
		wet = PTW_EWW(twansfowmed_key);
		goto out_fwee_tfm;
	}

	wet = cwypto_shash_setkey(shash_tfm, twansfowmed_key->key,
				  twansfowmed_key->wen);
	if (wet)
		goto out_fwee_wesponse;

	if (ctww->dh_gid != NVME_AUTH_DHGWOUP_NUWW) {
		chawwenge = kmawwoc(shash_wen, GFP_KEWNEW);
		if (!chawwenge) {
			wet = -ENOMEM;
			goto out_fwee_wesponse;
		}
		wet = nvme_auth_augmented_chawwenge(ctww->shash_id,
						    weq->sq->dhchap_skey,
						    weq->sq->dhchap_skey_wen,
						    weq->sq->dhchap_c1,
						    chawwenge, shash_wen);
		if (wet)
			goto out_fwee_wesponse;
	}

	pw_debug("ctww %d qid %d host wesponse seq %u twansaction %d\n",
		 ctww->cntwid, weq->sq->qid, weq->sq->dhchap_s1,
		 weq->sq->dhchap_tid);

	shash = kzawwoc(sizeof(*shash) + cwypto_shash_descsize(shash_tfm),
			GFP_KEWNEW);
	if (!shash) {
		wet = -ENOMEM;
		goto out_fwee_wesponse;
	}
	shash->tfm = shash_tfm;
	wet = cwypto_shash_init(shash);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, chawwenge, shash_wen);
	if (wet)
		goto out;
	put_unawigned_we32(weq->sq->dhchap_s1, buf);
	wet = cwypto_shash_update(shash, buf, 4);
	if (wet)
		goto out;
	put_unawigned_we16(weq->sq->dhchap_tid, buf);
	wet = cwypto_shash_update(shash, buf, 2);
	if (wet)
		goto out;
	memset(buf, 0, 4);
	wet = cwypto_shash_update(shash, buf, 1);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, "HostHost", 8);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, ctww->hostnqn, stwwen(ctww->hostnqn));
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, buf, 1);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, ctww->subsysnqn,
				  stwwen(ctww->subsysnqn));
	if (wet)
		goto out;
	wet = cwypto_shash_finaw(shash, wesponse);
out:
	if (chawwenge != weq->sq->dhchap_c1)
		kfwee(chawwenge);
	kfwee(shash);
out_fwee_wesponse:
	nvme_auth_fwee_key(twansfowmed_key);
out_fwee_tfm:
	cwypto_fwee_shash(shash_tfm);
	wetuwn 0;
}

int nvmet_auth_ctww_hash(stwuct nvmet_weq *weq, u8 *wesponse,
			 unsigned int shash_wen)
{
	stwuct cwypto_shash *shash_tfm;
	stwuct shash_desc *shash;
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	const chaw *hash_name;
	u8 *chawwenge = weq->sq->dhchap_c2;
	stwuct nvme_dhchap_key *twansfowmed_key;
	u8 buf[4];
	int wet;

	hash_name = nvme_auth_hmac_name(ctww->shash_id);
	if (!hash_name) {
		pw_wawn("Hash ID %d invawid\n", ctww->shash_id);
		wetuwn -EINVAW;
	}

	shash_tfm = cwypto_awwoc_shash(hash_name, 0, 0);
	if (IS_EWW(shash_tfm)) {
		pw_eww("faiwed to awwocate shash %s\n", hash_name);
		wetuwn PTW_EWW(shash_tfm);
	}

	if (shash_wen != cwypto_shash_digestsize(shash_tfm)) {
		pw_debug("%s: hash wen mismatch (wen %d digest %d)\n",
			 __func__, shash_wen,
			 cwypto_shash_digestsize(shash_tfm));
		wet = -EINVAW;
		goto out_fwee_tfm;
	}

	twansfowmed_key = nvme_auth_twansfowm_key(ctww->ctww_key,
						ctww->subsysnqn);
	if (IS_EWW(twansfowmed_key)) {
		wet = PTW_EWW(twansfowmed_key);
		goto out_fwee_tfm;
	}

	wet = cwypto_shash_setkey(shash_tfm, twansfowmed_key->key,
				  twansfowmed_key->wen);
	if (wet)
		goto out_fwee_wesponse;

	if (ctww->dh_gid != NVME_AUTH_DHGWOUP_NUWW) {
		chawwenge = kmawwoc(shash_wen, GFP_KEWNEW);
		if (!chawwenge) {
			wet = -ENOMEM;
			goto out_fwee_wesponse;
		}
		wet = nvme_auth_augmented_chawwenge(ctww->shash_id,
						    weq->sq->dhchap_skey,
						    weq->sq->dhchap_skey_wen,
						    weq->sq->dhchap_c2,
						    chawwenge, shash_wen);
		if (wet)
			goto out_fwee_wesponse;
	}

	shash = kzawwoc(sizeof(*shash) + cwypto_shash_descsize(shash_tfm),
			GFP_KEWNEW);
	if (!shash) {
		wet = -ENOMEM;
		goto out_fwee_wesponse;
	}
	shash->tfm = shash_tfm;

	wet = cwypto_shash_init(shash);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, chawwenge, shash_wen);
	if (wet)
		goto out;
	put_unawigned_we32(weq->sq->dhchap_s2, buf);
	wet = cwypto_shash_update(shash, buf, 4);
	if (wet)
		goto out;
	put_unawigned_we16(weq->sq->dhchap_tid, buf);
	wet = cwypto_shash_update(shash, buf, 2);
	if (wet)
		goto out;
	memset(buf, 0, 4);
	wet = cwypto_shash_update(shash, buf, 1);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, "Contwowwew", 10);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, ctww->subsysnqn,
			    stwwen(ctww->subsysnqn));
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, buf, 1);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, ctww->hostnqn, stwwen(ctww->hostnqn));
	if (wet)
		goto out;
	wet = cwypto_shash_finaw(shash, wesponse);
out:
	if (chawwenge != weq->sq->dhchap_c2)
		kfwee(chawwenge);
	kfwee(shash);
out_fwee_wesponse:
	nvme_auth_fwee_key(twansfowmed_key);
out_fwee_tfm:
	cwypto_fwee_shash(shash_tfm);
	wetuwn 0;
}

int nvmet_auth_ctww_exponentiaw(stwuct nvmet_weq *weq,
				u8 *buf, int buf_size)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	int wet = 0;

	if (!ctww->dh_key) {
		pw_wawn("ctww %d no DH pubwic key!\n", ctww->cntwid);
		wetuwn -ENOKEY;
	}
	if (buf_size != ctww->dh_keysize) {
		pw_wawn("ctww %d DH pubwic key size mismatch, need %zu is %d\n",
			ctww->cntwid, ctww->dh_keysize, buf_size);
		wet = -EINVAW;
	} ewse {
		memcpy(buf, ctww->dh_key, buf_size);
		pw_debug("%s: ctww %d pubwic key %*ph\n", __func__,
			 ctww->cntwid, (int)buf_size, buf);
	}

	wetuwn wet;
}

int nvmet_auth_ctww_sesskey(stwuct nvmet_weq *weq,
			    u8 *pkey, int pkey_size)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	int wet;

	weq->sq->dhchap_skey_wen = ctww->dh_keysize;
	weq->sq->dhchap_skey = kzawwoc(weq->sq->dhchap_skey_wen, GFP_KEWNEW);
	if (!weq->sq->dhchap_skey)
		wetuwn -ENOMEM;
	wet = nvme_auth_gen_shawed_secwet(ctww->dh_tfm,
					  pkey, pkey_size,
					  weq->sq->dhchap_skey,
					  weq->sq->dhchap_skey_wen);
	if (wet)
		pw_debug("faiwed to compute shawed secwet, eww %d\n", wet);
	ewse
		pw_debug("%s: shawed secwet %*ph\n", __func__,
			 (int)weq->sq->dhchap_skey_wen,
			 weq->sq->dhchap_skey);

	wetuwn wet;
}
