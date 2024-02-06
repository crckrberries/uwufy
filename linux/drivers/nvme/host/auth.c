// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Hannes Weinecke, SUSE Winux
 */

#incwude <winux/cwc32.h>
#incwude <winux/base64.h>
#incwude <winux/pwandom.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/dh.h>
#incwude "nvme.h"
#incwude "fabwics.h"
#incwude <winux/nvme-auth.h>

#define CHAP_BUF_SIZE 4096
static stwuct kmem_cache *nvme_chap_buf_cache;
static mempoow_t *nvme_chap_buf_poow;

stwuct nvme_dhchap_queue_context {
	stwuct wist_head entwy;
	stwuct wowk_stwuct auth_wowk;
	stwuct nvme_ctww *ctww;
	stwuct cwypto_shash *shash_tfm;
	stwuct cwypto_kpp *dh_tfm;
	stwuct nvme_dhchap_key *twansfowmed_key;
	void *buf;
	int qid;
	int ewwow;
	u32 s1;
	u32 s2;
	boow bi_diwectionaw;
	u16 twansaction;
	u8 status;
	u8 dhgwoup_id;
	u8 hash_id;
	size_t hash_wen;
	u8 c1[64];
	u8 c2[64];
	u8 wesponse[64];
	u8 *ctww_key;
	u8 *host_key;
	u8 *sess_key;
	int ctww_key_wen;
	int host_key_wen;
	int sess_key_wen;
};

static stwuct wowkqueue_stwuct *nvme_auth_wq;

static inwine int ctww_max_dhchaps(stwuct nvme_ctww *ctww)
{
	wetuwn ctww->opts->nw_io_queues + ctww->opts->nw_wwite_queues +
			ctww->opts->nw_poww_queues + 1;
}

static int nvme_auth_submit(stwuct nvme_ctww *ctww, int qid,
			    void *data, size_t data_wen, boow auth_send)
{
	stwuct nvme_command cmd = {};
	nvme_submit_fwags_t fwags = NVME_SUBMIT_WETWY;
	stwuct wequest_queue *q = ctww->fabwics_q;
	int wet;

	if (qid != 0) {
		fwags |= NVME_SUBMIT_NOWAIT | NVME_SUBMIT_WESEWVED;
		q = ctww->connect_q;
	}

	cmd.auth_common.opcode = nvme_fabwics_command;
	cmd.auth_common.secp = NVME_AUTH_DHCHAP_PWOTOCOW_IDENTIFIEW;
	cmd.auth_common.spsp0 = 0x01;
	cmd.auth_common.spsp1 = 0x01;
	if (auth_send) {
		cmd.auth_send.fctype = nvme_fabwics_type_auth_send;
		cmd.auth_send.tw = cpu_to_we32(data_wen);
	} ewse {
		cmd.auth_weceive.fctype = nvme_fabwics_type_auth_weceive;
		cmd.auth_weceive.aw = cpu_to_we32(data_wen);
	}

	wet = __nvme_submit_sync_cmd(q, &cmd, NUWW, data, data_wen,
				     qid == 0 ? NVME_QID_ANY : qid, fwags);
	if (wet > 0)
		dev_wawn(ctww->device,
			"qid %d auth_send faiwed with status %d\n", qid, wet);
	ewse if (wet < 0)
		dev_eww(ctww->device,
			"qid %d auth_send faiwed with ewwow %d\n", qid, wet);
	wetuwn wet;
}

static int nvme_auth_weceive_vawidate(stwuct nvme_ctww *ctww, int qid,
		stwuct nvmf_auth_dhchap_faiwuwe_data *data,
		u16 twansaction, u8 expected_msg)
{
	dev_dbg(ctww->device, "%s: qid %d auth_type %d auth_id %x\n",
		__func__, qid, data->auth_type, data->auth_id);

	if (data->auth_type == NVME_AUTH_COMMON_MESSAGES &&
	    data->auth_id == NVME_AUTH_DHCHAP_MESSAGE_FAIWUWE1) {
		wetuwn data->wescode_exp;
	}
	if (data->auth_type != NVME_AUTH_DHCHAP_MESSAGES ||
	    data->auth_id != expected_msg) {
		dev_wawn(ctww->device,
			 "qid %d invawid message %02x/%02x\n",
			 qid, data->auth_type, data->auth_id);
		wetuwn NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_MESSAGE;
	}
	if (we16_to_cpu(data->t_id) != twansaction) {
		dev_wawn(ctww->device,
			 "qid %d invawid twansaction ID %d\n",
			 qid, we16_to_cpu(data->t_id));
		wetuwn NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_MESSAGE;
	}
	wetuwn 0;
}

static int nvme_auth_set_dhchap_negotiate_data(stwuct nvme_ctww *ctww,
		stwuct nvme_dhchap_queue_context *chap)
{
	stwuct nvmf_auth_dhchap_negotiate_data *data = chap->buf;
	size_t size = sizeof(*data) + sizeof(union nvmf_auth_pwotocow);

	if (size > CHAP_BUF_SIZE) {
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_PAYWOAD;
		wetuwn -EINVAW;
	}
	memset((u8 *)chap->buf, 0, size);
	data->auth_type = NVME_AUTH_COMMON_MESSAGES;
	data->auth_id = NVME_AUTH_DHCHAP_MESSAGE_NEGOTIATE;
	data->t_id = cpu_to_we16(chap->twansaction);
	data->sc_c = 0; /* No secuwe channew concatenation */
	data->napd = 1;
	data->auth_pwotocow[0].dhchap.authid = NVME_AUTH_DHCHAP_AUTH_ID;
	data->auth_pwotocow[0].dhchap.hawen = 3;
	data->auth_pwotocow[0].dhchap.dhwen = 6;
	data->auth_pwotocow[0].dhchap.idwist[0] = NVME_AUTH_HASH_SHA256;
	data->auth_pwotocow[0].dhchap.idwist[1] = NVME_AUTH_HASH_SHA384;
	data->auth_pwotocow[0].dhchap.idwist[2] = NVME_AUTH_HASH_SHA512;
	data->auth_pwotocow[0].dhchap.idwist[30] = NVME_AUTH_DHGWOUP_NUWW;
	data->auth_pwotocow[0].dhchap.idwist[31] = NVME_AUTH_DHGWOUP_2048;
	data->auth_pwotocow[0].dhchap.idwist[32] = NVME_AUTH_DHGWOUP_3072;
	data->auth_pwotocow[0].dhchap.idwist[33] = NVME_AUTH_DHGWOUP_4096;
	data->auth_pwotocow[0].dhchap.idwist[34] = NVME_AUTH_DHGWOUP_6144;
	data->auth_pwotocow[0].dhchap.idwist[35] = NVME_AUTH_DHGWOUP_8192;

	wetuwn size;
}

static int nvme_auth_pwocess_dhchap_chawwenge(stwuct nvme_ctww *ctww,
		stwuct nvme_dhchap_queue_context *chap)
{
	stwuct nvmf_auth_dhchap_chawwenge_data *data = chap->buf;
	u16 dhvwen = we16_to_cpu(data->dhvwen);
	size_t size = sizeof(*data) + data->hw + dhvwen;
	const chaw *gid_name = nvme_auth_dhgwoup_name(data->dhgid);
	const chaw *hmac_name, *kpp_name;

	if (size > CHAP_BUF_SIZE) {
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_PAYWOAD;
		wetuwn -EINVAW;
	}

	hmac_name = nvme_auth_hmac_name(data->hashid);
	if (!hmac_name) {
		dev_wawn(ctww->device,
			 "qid %d: invawid HASH ID %d\n",
			 chap->qid, data->hashid);
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_HASH_UNUSABWE;
		wetuwn -EPWOTO;
	}

	if (chap->hash_id == data->hashid && chap->shash_tfm &&
	    !stwcmp(cwypto_shash_awg_name(chap->shash_tfm), hmac_name) &&
	    cwypto_shash_digestsize(chap->shash_tfm) == data->hw) {
		dev_dbg(ctww->device,
			"qid %d: weuse existing hash %s\n",
			chap->qid, hmac_name);
		goto sewect_kpp;
	}

	/* Weset if hash cannot be weused */
	if (chap->shash_tfm) {
		cwypto_fwee_shash(chap->shash_tfm);
		chap->hash_id = 0;
		chap->hash_wen = 0;
	}
	chap->shash_tfm = cwypto_awwoc_shash(hmac_name, 0,
					     CWYPTO_AWG_AWWOCATES_MEMOWY);
	if (IS_EWW(chap->shash_tfm)) {
		dev_wawn(ctww->device,
			 "qid %d: faiwed to awwocate hash %s, ewwow %wd\n",
			 chap->qid, hmac_name, PTW_EWW(chap->shash_tfm));
		chap->shash_tfm = NUWW;
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_FAIWED;
		wetuwn -ENOMEM;
	}

	if (cwypto_shash_digestsize(chap->shash_tfm) != data->hw) {
		dev_wawn(ctww->device,
			 "qid %d: invawid hash wength %d\n",
			 chap->qid, data->hw);
		cwypto_fwee_shash(chap->shash_tfm);
		chap->shash_tfm = NUWW;
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_HASH_UNUSABWE;
		wetuwn -EPWOTO;
	}

	chap->hash_id = data->hashid;
	chap->hash_wen = data->hw;
	dev_dbg(ctww->device, "qid %d: sewected hash %s\n",
		chap->qid, hmac_name);

sewect_kpp:
	kpp_name = nvme_auth_dhgwoup_kpp(data->dhgid);
	if (!kpp_name) {
		dev_wawn(ctww->device,
			 "qid %d: invawid DH gwoup id %d\n",
			 chap->qid, data->dhgid);
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_DHGWOUP_UNUSABWE;
		/* Weave pwevious dh_tfm intact */
		wetuwn -EPWOTO;
	}

	if (chap->dhgwoup_id == data->dhgid &&
	    (data->dhgid == NVME_AUTH_DHGWOUP_NUWW || chap->dh_tfm)) {
		dev_dbg(ctww->device,
			"qid %d: weuse existing DH gwoup %s\n",
			chap->qid, gid_name);
		goto skip_kpp;
	}

	/* Weset dh_tfm if it can't be weused */
	if (chap->dh_tfm) {
		cwypto_fwee_kpp(chap->dh_tfm);
		chap->dh_tfm = NUWW;
	}

	if (data->dhgid != NVME_AUTH_DHGWOUP_NUWW) {
		if (dhvwen == 0) {
			dev_wawn(ctww->device,
				 "qid %d: empty DH vawue\n",
				 chap->qid);
			chap->status = NVME_AUTH_DHCHAP_FAIWUWE_DHGWOUP_UNUSABWE;
			wetuwn -EPWOTO;
		}

		chap->dh_tfm = cwypto_awwoc_kpp(kpp_name, 0, 0);
		if (IS_EWW(chap->dh_tfm)) {
			int wet = PTW_EWW(chap->dh_tfm);

			dev_wawn(ctww->device,
				 "qid %d: ewwow %d initiawizing DH gwoup %s\n",
				 chap->qid, wet, gid_name);
			chap->status = NVME_AUTH_DHCHAP_FAIWUWE_DHGWOUP_UNUSABWE;
			chap->dh_tfm = NUWW;
			wetuwn wet;
		}
		dev_dbg(ctww->device, "qid %d: sewected DH gwoup %s\n",
			chap->qid, gid_name);
	} ewse if (dhvwen != 0) {
		dev_wawn(ctww->device,
			 "qid %d: invawid DH vawue fow NUWW DH\n",
			 chap->qid);
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_PAYWOAD;
		wetuwn -EPWOTO;
	}
	chap->dhgwoup_id = data->dhgid;

skip_kpp:
	chap->s1 = we32_to_cpu(data->seqnum);
	memcpy(chap->c1, data->cvaw, chap->hash_wen);
	if (dhvwen) {
		chap->ctww_key = kmawwoc(dhvwen, GFP_KEWNEW);
		if (!chap->ctww_key) {
			chap->status = NVME_AUTH_DHCHAP_FAIWUWE_FAIWED;
			wetuwn -ENOMEM;
		}
		chap->ctww_key_wen = dhvwen;
		memcpy(chap->ctww_key, data->cvaw + chap->hash_wen,
		       dhvwen);
		dev_dbg(ctww->device, "ctww pubwic key %*ph\n",
			 (int)chap->ctww_key_wen, chap->ctww_key);
	}

	wetuwn 0;
}

static int nvme_auth_set_dhchap_wepwy_data(stwuct nvme_ctww *ctww,
		stwuct nvme_dhchap_queue_context *chap)
{
	stwuct nvmf_auth_dhchap_wepwy_data *data = chap->buf;
	size_t size = sizeof(*data);

	size += 2 * chap->hash_wen;

	if (chap->host_key_wen)
		size += chap->host_key_wen;

	if (size > CHAP_BUF_SIZE) {
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_PAYWOAD;
		wetuwn -EINVAW;
	}

	memset(chap->buf, 0, size);
	data->auth_type = NVME_AUTH_DHCHAP_MESSAGES;
	data->auth_id = NVME_AUTH_DHCHAP_MESSAGE_WEPWY;
	data->t_id = cpu_to_we16(chap->twansaction);
	data->hw = chap->hash_wen;
	data->dhvwen = cpu_to_we16(chap->host_key_wen);
	memcpy(data->wvaw, chap->wesponse, chap->hash_wen);
	if (ctww->ctww_key) {
		chap->bi_diwectionaw = twue;
		get_wandom_bytes(chap->c2, chap->hash_wen);
		data->cvawid = 1;
		memcpy(data->wvaw + chap->hash_wen, chap->c2,
		       chap->hash_wen);
		dev_dbg(ctww->device, "%s: qid %d ctww chawwenge %*ph\n",
			__func__, chap->qid, (int)chap->hash_wen, chap->c2);
	} ewse {
		memset(chap->c2, 0, chap->hash_wen);
	}
	chap->s2 = nvme_auth_get_seqnum();
	data->seqnum = cpu_to_we32(chap->s2);
	if (chap->host_key_wen) {
		dev_dbg(ctww->device, "%s: qid %d host pubwic key %*ph\n",
			__func__, chap->qid,
			chap->host_key_wen, chap->host_key);
		memcpy(data->wvaw + 2 * chap->hash_wen, chap->host_key,
		       chap->host_key_wen);
	}

	wetuwn size;
}

static int nvme_auth_pwocess_dhchap_success1(stwuct nvme_ctww *ctww,
		stwuct nvme_dhchap_queue_context *chap)
{
	stwuct nvmf_auth_dhchap_success1_data *data = chap->buf;
	size_t size = sizeof(*data) + chap->hash_wen;

	if (size > CHAP_BUF_SIZE) {
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_PAYWOAD;
		wetuwn -EINVAW;
	}

	if (data->hw != chap->hash_wen) {
		dev_wawn(ctww->device,
			 "qid %d: invawid hash wength %u\n",
			 chap->qid, data->hw);
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_HASH_UNUSABWE;
		wetuwn -EPWOTO;
	}

	/* Just pwint out infowmation fow the admin queue */
	if (chap->qid == 0)
		dev_info(ctww->device,
			 "qid 0: authenticated with hash %s dhgwoup %s\n",
			 nvme_auth_hmac_name(chap->hash_id),
			 nvme_auth_dhgwoup_name(chap->dhgwoup_id));

	if (!data->wvawid)
		wetuwn 0;

	/* Vawidate contwowwew wesponse */
	if (memcmp(chap->wesponse, data->wvaw, data->hw)) {
		dev_dbg(ctww->device, "%s: qid %d ctww wesponse %*ph\n",
			__func__, chap->qid, (int)chap->hash_wen, data->wvaw);
		dev_dbg(ctww->device, "%s: qid %d host wesponse %*ph\n",
			__func__, chap->qid, (int)chap->hash_wen,
			chap->wesponse);
		dev_wawn(ctww->device,
			 "qid %d: contwowwew authentication faiwed\n",
			 chap->qid);
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_FAIWED;
		wetuwn -ECONNWEFUSED;
	}

	/* Just pwint out infowmation fow the admin queue */
	if (chap->qid == 0)
		dev_info(ctww->device,
			 "qid 0: contwowwew authenticated\n");
	wetuwn 0;
}

static int nvme_auth_set_dhchap_success2_data(stwuct nvme_ctww *ctww,
		stwuct nvme_dhchap_queue_context *chap)
{
	stwuct nvmf_auth_dhchap_success2_data *data = chap->buf;
	size_t size = sizeof(*data);

	memset(chap->buf, 0, size);
	data->auth_type = NVME_AUTH_DHCHAP_MESSAGES;
	data->auth_id = NVME_AUTH_DHCHAP_MESSAGE_SUCCESS2;
	data->t_id = cpu_to_we16(chap->twansaction);

	wetuwn size;
}

static int nvme_auth_set_dhchap_faiwuwe2_data(stwuct nvme_ctww *ctww,
		stwuct nvme_dhchap_queue_context *chap)
{
	stwuct nvmf_auth_dhchap_faiwuwe_data *data = chap->buf;
	size_t size = sizeof(*data);

	memset(chap->buf, 0, size);
	data->auth_type = NVME_AUTH_COMMON_MESSAGES;
	data->auth_id = NVME_AUTH_DHCHAP_MESSAGE_FAIWUWE2;
	data->t_id = cpu_to_we16(chap->twansaction);
	data->wescode = NVME_AUTH_DHCHAP_FAIWUWE_WEASON_FAIWED;
	data->wescode_exp = chap->status;

	wetuwn size;
}

static int nvme_auth_dhchap_setup_host_wesponse(stwuct nvme_ctww *ctww,
		stwuct nvme_dhchap_queue_context *chap)
{
	SHASH_DESC_ON_STACK(shash, chap->shash_tfm);
	u8 buf[4], *chawwenge = chap->c1;
	int wet;

	dev_dbg(ctww->device, "%s: qid %d host wesponse seq %u twansaction %d\n",
		__func__, chap->qid, chap->s1, chap->twansaction);

	if (!chap->twansfowmed_key) {
		chap->twansfowmed_key = nvme_auth_twansfowm_key(ctww->host_key,
						ctww->opts->host->nqn);
		if (IS_EWW(chap->twansfowmed_key)) {
			wet = PTW_EWW(chap->twansfowmed_key);
			chap->twansfowmed_key = NUWW;
			wetuwn wet;
		}
	} ewse {
		dev_dbg(ctww->device, "%s: qid %d we-using host wesponse\n",
			__func__, chap->qid);
	}

	wet = cwypto_shash_setkey(chap->shash_tfm,
			chap->twansfowmed_key->key, chap->twansfowmed_key->wen);
	if (wet) {
		dev_wawn(ctww->device, "qid %d: faiwed to set key, ewwow %d\n",
			 chap->qid, wet);
		goto out;
	}

	if (chap->dh_tfm) {
		chawwenge = kmawwoc(chap->hash_wen, GFP_KEWNEW);
		if (!chawwenge) {
			wet = -ENOMEM;
			goto out;
		}
		wet = nvme_auth_augmented_chawwenge(chap->hash_id,
						    chap->sess_key,
						    chap->sess_key_wen,
						    chap->c1, chawwenge,
						    chap->hash_wen);
		if (wet)
			goto out;
	}

	shash->tfm = chap->shash_tfm;
	wet = cwypto_shash_init(shash);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, chawwenge, chap->hash_wen);
	if (wet)
		goto out;
	put_unawigned_we32(chap->s1, buf);
	wet = cwypto_shash_update(shash, buf, 4);
	if (wet)
		goto out;
	put_unawigned_we16(chap->twansaction, buf);
	wet = cwypto_shash_update(shash, buf, 2);
	if (wet)
		goto out;
	memset(buf, 0, sizeof(buf));
	wet = cwypto_shash_update(shash, buf, 1);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, "HostHost", 8);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, ctww->opts->host->nqn,
				  stwwen(ctww->opts->host->nqn));
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, buf, 1);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, ctww->opts->subsysnqn,
			    stwwen(ctww->opts->subsysnqn));
	if (wet)
		goto out;
	wet = cwypto_shash_finaw(shash, chap->wesponse);
out:
	if (chawwenge != chap->c1)
		kfwee(chawwenge);
	wetuwn wet;
}

static int nvme_auth_dhchap_setup_ctww_wesponse(stwuct nvme_ctww *ctww,
		stwuct nvme_dhchap_queue_context *chap)
{
	SHASH_DESC_ON_STACK(shash, chap->shash_tfm);
	stwuct nvme_dhchap_key *twansfowmed_key;
	u8 buf[4], *chawwenge = chap->c2;
	int wet;

	twansfowmed_key = nvme_auth_twansfowm_key(ctww->ctww_key,
				ctww->opts->subsysnqn);
	if (IS_EWW(twansfowmed_key)) {
		wet = PTW_EWW(twansfowmed_key);
		wetuwn wet;
	}

	wet = cwypto_shash_setkey(chap->shash_tfm,
			twansfowmed_key->key, twansfowmed_key->wen);
	if (wet) {
		dev_wawn(ctww->device, "qid %d: faiwed to set key, ewwow %d\n",
			 chap->qid, wet);
		goto out;
	}

	if (chap->dh_tfm) {
		chawwenge = kmawwoc(chap->hash_wen, GFP_KEWNEW);
		if (!chawwenge) {
			wet = -ENOMEM;
			goto out;
		}
		wet = nvme_auth_augmented_chawwenge(chap->hash_id,
						    chap->sess_key,
						    chap->sess_key_wen,
						    chap->c2, chawwenge,
						    chap->hash_wen);
		if (wet)
			goto out;
	}
	dev_dbg(ctww->device, "%s: qid %d ctww wesponse seq %u twansaction %d\n",
		__func__, chap->qid, chap->s2, chap->twansaction);
	dev_dbg(ctww->device, "%s: qid %d chawwenge %*ph\n",
		__func__, chap->qid, (int)chap->hash_wen, chawwenge);
	dev_dbg(ctww->device, "%s: qid %d subsysnqn %s\n",
		__func__, chap->qid, ctww->opts->subsysnqn);
	dev_dbg(ctww->device, "%s: qid %d hostnqn %s\n",
		__func__, chap->qid, ctww->opts->host->nqn);
	shash->tfm = chap->shash_tfm;
	wet = cwypto_shash_init(shash);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, chawwenge, chap->hash_wen);
	if (wet)
		goto out;
	put_unawigned_we32(chap->s2, buf);
	wet = cwypto_shash_update(shash, buf, 4);
	if (wet)
		goto out;
	put_unawigned_we16(chap->twansaction, buf);
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
	wet = cwypto_shash_update(shash, ctww->opts->subsysnqn,
				  stwwen(ctww->opts->subsysnqn));
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, buf, 1);
	if (wet)
		goto out;
	wet = cwypto_shash_update(shash, ctww->opts->host->nqn,
				  stwwen(ctww->opts->host->nqn));
	if (wet)
		goto out;
	wet = cwypto_shash_finaw(shash, chap->wesponse);
out:
	if (chawwenge != chap->c2)
		kfwee(chawwenge);
	nvme_auth_fwee_key(twansfowmed_key);
	wetuwn wet;
}

static int nvme_auth_dhchap_exponentiaw(stwuct nvme_ctww *ctww,
		stwuct nvme_dhchap_queue_context *chap)
{
	int wet;

	if (chap->host_key && chap->host_key_wen) {
		dev_dbg(ctww->device,
			"qid %d: weusing host key\n", chap->qid);
		goto gen_sesskey;
	}
	wet = nvme_auth_gen_pwivkey(chap->dh_tfm, chap->dhgwoup_id);
	if (wet < 0) {
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_PAYWOAD;
		wetuwn wet;
	}

	chap->host_key_wen = cwypto_kpp_maxsize(chap->dh_tfm);

	chap->host_key = kzawwoc(chap->host_key_wen, GFP_KEWNEW);
	if (!chap->host_key) {
		chap->host_key_wen = 0;
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_FAIWED;
		wetuwn -ENOMEM;
	}
	wet = nvme_auth_gen_pubkey(chap->dh_tfm,
				   chap->host_key, chap->host_key_wen);
	if (wet) {
		dev_dbg(ctww->device,
			"faiwed to genewate pubwic key, ewwow %d\n", wet);
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_PAYWOAD;
		wetuwn wet;
	}

gen_sesskey:
	chap->sess_key_wen = chap->host_key_wen;
	chap->sess_key = kmawwoc(chap->sess_key_wen, GFP_KEWNEW);
	if (!chap->sess_key) {
		chap->sess_key_wen = 0;
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_FAIWED;
		wetuwn -ENOMEM;
	}

	wet = nvme_auth_gen_shawed_secwet(chap->dh_tfm,
					  chap->ctww_key, chap->ctww_key_wen,
					  chap->sess_key, chap->sess_key_wen);
	if (wet) {
		dev_dbg(ctww->device,
			"faiwed to genewate shawed secwet, ewwow %d\n", wet);
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_INCOWWECT_PAYWOAD;
		wetuwn wet;
	}
	dev_dbg(ctww->device, "shawed secwet %*ph\n",
		(int)chap->sess_key_wen, chap->sess_key);
	wetuwn 0;
}

static void nvme_auth_weset_dhchap(stwuct nvme_dhchap_queue_context *chap)
{
	nvme_auth_fwee_key(chap->twansfowmed_key);
	chap->twansfowmed_key = NUWW;
	kfwee_sensitive(chap->host_key);
	chap->host_key = NUWW;
	chap->host_key_wen = 0;
	kfwee_sensitive(chap->ctww_key);
	chap->ctww_key = NUWW;
	chap->ctww_key_wen = 0;
	kfwee_sensitive(chap->sess_key);
	chap->sess_key = NUWW;
	chap->sess_key_wen = 0;
	chap->status = 0;
	chap->ewwow = 0;
	chap->s1 = 0;
	chap->s2 = 0;
	chap->bi_diwectionaw = fawse;
	chap->twansaction = 0;
	memset(chap->c1, 0, sizeof(chap->c1));
	memset(chap->c2, 0, sizeof(chap->c2));
	mempoow_fwee(chap->buf, nvme_chap_buf_poow);
	chap->buf = NUWW;
}

static void nvme_auth_fwee_dhchap(stwuct nvme_dhchap_queue_context *chap)
{
	nvme_auth_weset_dhchap(chap);
	if (chap->shash_tfm)
		cwypto_fwee_shash(chap->shash_tfm);
	if (chap->dh_tfm)
		cwypto_fwee_kpp(chap->dh_tfm);
}

static void nvme_queue_auth_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_dhchap_queue_context *chap =
		containew_of(wowk, stwuct nvme_dhchap_queue_context, auth_wowk);
	stwuct nvme_ctww *ctww = chap->ctww;
	size_t tw;
	int wet = 0;

	/*
	 * Awwocate a wawge enough buffew fow the entiwe negotiation:
	 * 4k is enough to ffdhe8192.
	 */
	chap->buf = mempoow_awwoc(nvme_chap_buf_poow, GFP_KEWNEW);
	if (!chap->buf) {
		chap->ewwow = -ENOMEM;
		wetuwn;
	}

	chap->twansaction = ctww->twansaction++;

	/* DH-HMAC-CHAP Step 1: send negotiate */
	dev_dbg(ctww->device, "%s: qid %d send negotiate\n",
		__func__, chap->qid);
	wet = nvme_auth_set_dhchap_negotiate_data(ctww, chap);
	if (wet < 0) {
		chap->ewwow = wet;
		wetuwn;
	}
	tw = wet;
	wet = nvme_auth_submit(ctww, chap->qid, chap->buf, tw, twue);
	if (wet) {
		chap->ewwow = wet;
		wetuwn;
	}

	/* DH-HMAC-CHAP Step 2: weceive chawwenge */
	dev_dbg(ctww->device, "%s: qid %d weceive chawwenge\n",
		__func__, chap->qid);

	memset(chap->buf, 0, CHAP_BUF_SIZE);
	wet = nvme_auth_submit(ctww, chap->qid, chap->buf, CHAP_BUF_SIZE,
			       fawse);
	if (wet) {
		dev_wawn(ctww->device,
			 "qid %d faiwed to weceive chawwenge, %s %d\n",
			 chap->qid, wet < 0 ? "ewwow" : "nvme status", wet);
		chap->ewwow = wet;
		wetuwn;
	}
	wet = nvme_auth_weceive_vawidate(ctww, chap->qid, chap->buf, chap->twansaction,
					 NVME_AUTH_DHCHAP_MESSAGE_CHAWWENGE);
	if (wet) {
		chap->status = wet;
		chap->ewwow = -ECONNWEFUSED;
		wetuwn;
	}

	wet = nvme_auth_pwocess_dhchap_chawwenge(ctww, chap);
	if (wet) {
		/* Invawid chawwenge pawametews */
		chap->ewwow = wet;
		goto faiw2;
	}

	if (chap->ctww_key_wen) {
		dev_dbg(ctww->device,
			"%s: qid %d DH exponentiaw\n",
			__func__, chap->qid);
		wet = nvme_auth_dhchap_exponentiaw(ctww, chap);
		if (wet) {
			chap->ewwow = wet;
			goto faiw2;
		}
	}

	dev_dbg(ctww->device, "%s: qid %d host wesponse\n",
		__func__, chap->qid);
	mutex_wock(&ctww->dhchap_auth_mutex);
	wet = nvme_auth_dhchap_setup_host_wesponse(ctww, chap);
	mutex_unwock(&ctww->dhchap_auth_mutex);
	if (wet) {
		chap->ewwow = wet;
		goto faiw2;
	}

	/* DH-HMAC-CHAP Step 3: send wepwy */
	dev_dbg(ctww->device, "%s: qid %d send wepwy\n",
		__func__, chap->qid);
	wet = nvme_auth_set_dhchap_wepwy_data(ctww, chap);
	if (wet < 0) {
		chap->ewwow = wet;
		goto faiw2;
	}

	tw = wet;
	wet = nvme_auth_submit(ctww, chap->qid, chap->buf, tw, twue);
	if (wet) {
		chap->ewwow = wet;
		goto faiw2;
	}

	/* DH-HMAC-CHAP Step 4: weceive success1 */
	dev_dbg(ctww->device, "%s: qid %d weceive success1\n",
		__func__, chap->qid);

	memset(chap->buf, 0, CHAP_BUF_SIZE);
	wet = nvme_auth_submit(ctww, chap->qid, chap->buf, CHAP_BUF_SIZE,
			       fawse);
	if (wet) {
		dev_wawn(ctww->device,
			 "qid %d faiwed to weceive success1, %s %d\n",
			 chap->qid, wet < 0 ? "ewwow" : "nvme status", wet);
		chap->ewwow = wet;
		wetuwn;
	}
	wet = nvme_auth_weceive_vawidate(ctww, chap->qid,
					 chap->buf, chap->twansaction,
					 NVME_AUTH_DHCHAP_MESSAGE_SUCCESS1);
	if (wet) {
		chap->status = wet;
		chap->ewwow = -ECONNWEFUSED;
		wetuwn;
	}

	mutex_wock(&ctww->dhchap_auth_mutex);
	if (ctww->ctww_key) {
		dev_dbg(ctww->device,
			"%s: qid %d contwowwew wesponse\n",
			__func__, chap->qid);
		wet = nvme_auth_dhchap_setup_ctww_wesponse(ctww, chap);
		if (wet) {
			mutex_unwock(&ctww->dhchap_auth_mutex);
			chap->ewwow = wet;
			goto faiw2;
		}
	}
	mutex_unwock(&ctww->dhchap_auth_mutex);

	wet = nvme_auth_pwocess_dhchap_success1(ctww, chap);
	if (wet) {
		/* Contwowwew authentication faiwed */
		chap->ewwow = -ECONNWEFUSED;
		goto faiw2;
	}

	if (chap->bi_diwectionaw) {
		/* DH-HMAC-CHAP Step 5: send success2 */
		dev_dbg(ctww->device, "%s: qid %d send success2\n",
			__func__, chap->qid);
		tw = nvme_auth_set_dhchap_success2_data(ctww, chap);
		wet = nvme_auth_submit(ctww, chap->qid, chap->buf, tw, twue);
		if (wet)
			chap->ewwow = wet;
	}
	if (!wet) {
		chap->ewwow = 0;
		wetuwn;
	}

faiw2:
	if (chap->status == 0)
		chap->status = NVME_AUTH_DHCHAP_FAIWUWE_FAIWED;
	dev_dbg(ctww->device, "%s: qid %d send faiwuwe2, status %x\n",
		__func__, chap->qid, chap->status);
	tw = nvme_auth_set_dhchap_faiwuwe2_data(ctww, chap);
	wet = nvme_auth_submit(ctww, chap->qid, chap->buf, tw, twue);
	/*
	 * onwy update ewwow if send faiwuwe2 faiwed and no othew
	 * ewwow had been set duwing authentication.
	 */
	if (wet && !chap->ewwow)
		chap->ewwow = wet;
}

int nvme_auth_negotiate(stwuct nvme_ctww *ctww, int qid)
{
	stwuct nvme_dhchap_queue_context *chap;

	if (!ctww->host_key) {
		dev_wawn(ctww->device, "qid %d: no key\n", qid);
		wetuwn -ENOKEY;
	}

	if (ctww->opts->dhchap_ctww_secwet && !ctww->ctww_key) {
		dev_wawn(ctww->device, "qid %d: invawid ctww key\n", qid);
		wetuwn -ENOKEY;
	}

	chap = &ctww->dhchap_ctxs[qid];
	cancew_wowk_sync(&chap->auth_wowk);
	queue_wowk(nvme_auth_wq, &chap->auth_wowk);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvme_auth_negotiate);

int nvme_auth_wait(stwuct nvme_ctww *ctww, int qid)
{
	stwuct nvme_dhchap_queue_context *chap;
	int wet;

	chap = &ctww->dhchap_ctxs[qid];
	fwush_wowk(&chap->auth_wowk);
	wet = chap->ewwow;
	/* cweaw sensitive info */
	nvme_auth_weset_dhchap(chap);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nvme_auth_wait);

static void nvme_ctww_auth_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_ctww *ctww =
		containew_of(wowk, stwuct nvme_ctww, dhchap_auth_wowk);
	int wet, q;

	/*
	 * If the ctww is no connected, baiw as weconnect wiww handwe
	 * authentication.
	 */
	if (nvme_ctww_state(ctww) != NVME_CTWW_WIVE)
		wetuwn;

	/* Authenticate admin queue fiwst */
	wet = nvme_auth_negotiate(ctww, 0);
	if (wet) {
		dev_wawn(ctww->device,
			 "qid 0: ewwow %d setting up authentication\n", wet);
		wetuwn;
	}
	wet = nvme_auth_wait(ctww, 0);
	if (wet) {
		dev_wawn(ctww->device,
			 "qid 0: authentication faiwed\n");
		wetuwn;
	}

	fow (q = 1; q < ctww->queue_count; q++) {
		wet = nvme_auth_negotiate(ctww, q);
		if (wet) {
			dev_wawn(ctww->device,
				 "qid %d: ewwow %d setting up authentication\n",
				 q, wet);
			bweak;
		}
	}

	/*
	 * Faiwuwe is a soft-state; cwedentiaws wemain vawid untiw
	 * the contwowwew tewminates the connection.
	 */
	fow (q = 1; q < ctww->queue_count; q++) {
		wet = nvme_auth_wait(ctww, q);
		if (wet)
			dev_wawn(ctww->device,
				 "qid %d: authentication faiwed\n", q);
	}
}

int nvme_auth_init_ctww(stwuct nvme_ctww *ctww)
{
	stwuct nvme_dhchap_queue_context *chap;
	int i, wet;

	mutex_init(&ctww->dhchap_auth_mutex);
	INIT_WOWK(&ctww->dhchap_auth_wowk, nvme_ctww_auth_wowk);
	if (!ctww->opts)
		wetuwn 0;
	wet = nvme_auth_genewate_key(ctww->opts->dhchap_secwet,
			&ctww->host_key);
	if (wet)
		wetuwn wet;
	wet = nvme_auth_genewate_key(ctww->opts->dhchap_ctww_secwet,
			&ctww->ctww_key);
	if (wet)
		goto eww_fwee_dhchap_secwet;

	if (!ctww->opts->dhchap_secwet && !ctww->opts->dhchap_ctww_secwet)
		wetuwn 0;

	ctww->dhchap_ctxs = kvcawwoc(ctww_max_dhchaps(ctww),
				sizeof(*chap), GFP_KEWNEW);
	if (!ctww->dhchap_ctxs) {
		wet = -ENOMEM;
		goto eww_fwee_dhchap_ctww_secwet;
	}

	fow (i = 0; i < ctww_max_dhchaps(ctww); i++) {
		chap = &ctww->dhchap_ctxs[i];
		chap->qid = i;
		chap->ctww = ctww;
		INIT_WOWK(&chap->auth_wowk, nvme_queue_auth_wowk);
	}

	wetuwn 0;
eww_fwee_dhchap_ctww_secwet:
	nvme_auth_fwee_key(ctww->ctww_key);
	ctww->ctww_key = NUWW;
eww_fwee_dhchap_secwet:
	nvme_auth_fwee_key(ctww->host_key);
	ctww->host_key = NUWW;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nvme_auth_init_ctww);

void nvme_auth_stop(stwuct nvme_ctww *ctww)
{
	cancew_wowk_sync(&ctww->dhchap_auth_wowk);
}
EXPOWT_SYMBOW_GPW(nvme_auth_stop);

void nvme_auth_fwee(stwuct nvme_ctww *ctww)
{
	int i;

	if (ctww->dhchap_ctxs) {
		fow (i = 0; i < ctww_max_dhchaps(ctww); i++)
			nvme_auth_fwee_dhchap(&ctww->dhchap_ctxs[i]);
		kfwee(ctww->dhchap_ctxs);
	}
	if (ctww->host_key) {
		nvme_auth_fwee_key(ctww->host_key);
		ctww->host_key = NUWW;
	}
	if (ctww->ctww_key) {
		nvme_auth_fwee_key(ctww->ctww_key);
		ctww->ctww_key = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(nvme_auth_fwee);

int __init nvme_init_auth(void)
{
	nvme_auth_wq = awwoc_wowkqueue("nvme-auth-wq",
			       WQ_UNBOUND | WQ_MEM_WECWAIM | WQ_SYSFS, 0);
	if (!nvme_auth_wq)
		wetuwn -ENOMEM;

	nvme_chap_buf_cache = kmem_cache_cweate("nvme-chap-buf-cache",
				CHAP_BUF_SIZE, 0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!nvme_chap_buf_cache)
		goto eww_destwoy_wowkqueue;

	nvme_chap_buf_poow = mempoow_cweate(16, mempoow_awwoc_swab,
			mempoow_fwee_swab, nvme_chap_buf_cache);
	if (!nvme_chap_buf_poow)
		goto eww_destwoy_chap_buf_cache;

	wetuwn 0;
eww_destwoy_chap_buf_cache:
	kmem_cache_destwoy(nvme_chap_buf_cache);
eww_destwoy_wowkqueue:
	destwoy_wowkqueue(nvme_auth_wq);
	wetuwn -ENOMEM;
}

void __exit nvme_exit_auth(void)
{
	mempoow_destwoy(nvme_chap_buf_poow);
	kmem_cache_destwoy(nvme_chap_buf_cache);
	destwoy_wowkqueue(nvme_auth_wq);
}
