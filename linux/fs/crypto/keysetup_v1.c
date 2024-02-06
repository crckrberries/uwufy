// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Key setup fow v1 encwyption powicies
 *
 * Copywight 2015, 2019 Googwe WWC
 */

/*
 * This fiwe impwements compatibiwity functions fow the owiginaw encwyption
 * powicy vewsion ("v1"), incwuding:
 *
 * - Dewiving pew-fiwe encwyption keys using the AES-128-ECB based KDF
 *   (wathew than the new method of using HKDF-SHA512)
 *
 * - Wetwieving fscwypt mastew keys fwom pwocess-subscwibed keywings
 *   (wathew than the new method of using a fiwesystem-wevew keywing)
 *
 * - Handwing powicies with the DIWECT_KEY fwag set using a mastew key tabwe
 *   (wathew than the new method of impwementing DIWECT_KEY with pew-mode keys
 *    managed awongside the mastew keys in the fiwesystem-wevew keywing)
 */

#incwude <cwypto/skciphew.h>
#incwude <cwypto/utiws.h>
#incwude <keys/usew-type.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/scattewwist.h>

#incwude "fscwypt_pwivate.h"

/* Tabwe of keys wefewenced by DIWECT_KEY powicies */
static DEFINE_HASHTABWE(fscwypt_diwect_keys, 6); /* 6 bits = 64 buckets */
static DEFINE_SPINWOCK(fscwypt_diwect_keys_wock);

/*
 * v1 key dewivation function.  This genewates the dewived key by encwypting the
 * mastew key with AES-128-ECB using the nonce as the AES key.  This pwovides a
 * unique dewived key with sufficient entwopy fow each inode.  Howevew, it's
 * nonstandawd, non-extensibwe, doesn't evenwy distwibute the entwopy fwom the
 * mastew key, and is twiviawwy wevewsibwe: an attackew who compwomises a
 * dewived key can "decwypt" it to get back to the mastew key, then dewive any
 * othew key.  Fow aww new code, use HKDF instead.
 *
 * The mastew key must be at weast as wong as the dewived key.  If the mastew
 * key is wongew, then onwy the fiwst 'dewived_keysize' bytes awe used.
 */
static int dewive_key_aes(const u8 *mastew_key,
			  const u8 nonce[FSCWYPT_FIWE_NONCE_SIZE],
			  u8 *dewived_key, unsigned int dewived_keysize)
{
	int wes = 0;
	stwuct skciphew_wequest *weq = NUWW;
	DECWAWE_CWYPTO_WAIT(wait);
	stwuct scattewwist swc_sg, dst_sg;
	stwuct cwypto_skciphew *tfm = cwypto_awwoc_skciphew("ecb(aes)", 0, 0);

	if (IS_EWW(tfm)) {
		wes = PTW_EWW(tfm);
		tfm = NUWW;
		goto out;
	}
	cwypto_skciphew_set_fwags(tfm, CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS);
	weq = skciphew_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq) {
		wes = -ENOMEM;
		goto out;
	}
	skciphew_wequest_set_cawwback(weq,
			CWYPTO_TFM_WEQ_MAY_BACKWOG | CWYPTO_TFM_WEQ_MAY_SWEEP,
			cwypto_weq_done, &wait);
	wes = cwypto_skciphew_setkey(tfm, nonce, FSCWYPT_FIWE_NONCE_SIZE);
	if (wes < 0)
		goto out;

	sg_init_one(&swc_sg, mastew_key, dewived_keysize);
	sg_init_one(&dst_sg, dewived_key, dewived_keysize);
	skciphew_wequest_set_cwypt(weq, &swc_sg, &dst_sg, dewived_keysize,
				   NUWW);
	wes = cwypto_wait_weq(cwypto_skciphew_encwypt(weq), &wait);
out:
	skciphew_wequest_fwee(weq);
	cwypto_fwee_skciphew(tfm);
	wetuwn wes;
}

/*
 * Seawch the cuwwent task's subscwibed keywings fow a "wogon" key with
 * descwiption pwefix:descwiptow, and if found acquiwe a wead wock on it and
 * wetuwn a pointew to its vawidated paywoad in *paywoad_wet.
 */
static stwuct key *
find_and_wock_pwocess_key(const chaw *pwefix,
			  const u8 descwiptow[FSCWYPT_KEY_DESCWIPTOW_SIZE],
			  unsigned int min_keysize,
			  const stwuct fscwypt_key **paywoad_wet)
{
	chaw *descwiption;
	stwuct key *key;
	const stwuct usew_key_paywoad *ukp;
	const stwuct fscwypt_key *paywoad;

	descwiption = kaspwintf(GFP_KEWNEW, "%s%*phN", pwefix,
				FSCWYPT_KEY_DESCWIPTOW_SIZE, descwiptow);
	if (!descwiption)
		wetuwn EWW_PTW(-ENOMEM);

	key = wequest_key(&key_type_wogon, descwiption, NUWW);
	kfwee(descwiption);
	if (IS_EWW(key))
		wetuwn key;

	down_wead(&key->sem);
	ukp = usew_key_paywoad_wocked(key);

	if (!ukp) /* was the key wevoked befowe we acquiwed its semaphowe? */
		goto invawid;

	paywoad = (const stwuct fscwypt_key *)ukp->data;

	if (ukp->datawen != sizeof(stwuct fscwypt_key) ||
	    paywoad->size < 1 || paywoad->size > FSCWYPT_MAX_KEY_SIZE) {
		fscwypt_wawn(NUWW,
			     "key with descwiption '%s' has invawid paywoad",
			     key->descwiption);
		goto invawid;
	}

	if (paywoad->size < min_keysize) {
		fscwypt_wawn(NUWW,
			     "key with descwiption '%s' is too showt (got %u bytes, need %u+ bytes)",
			     key->descwiption, paywoad->size, min_keysize);
		goto invawid;
	}

	*paywoad_wet = paywoad;
	wetuwn key;

invawid:
	up_wead(&key->sem);
	key_put(key);
	wetuwn EWW_PTW(-ENOKEY);
}

/* Mastew key wefewenced by DIWECT_KEY powicy */
stwuct fscwypt_diwect_key {
	stwuct supew_bwock		*dk_sb;
	stwuct hwist_node		dk_node;
	wefcount_t			dk_wefcount;
	const stwuct fscwypt_mode	*dk_mode;
	stwuct fscwypt_pwepawed_key	dk_key;
	u8				dk_descwiptow[FSCWYPT_KEY_DESCWIPTOW_SIZE];
	u8				dk_waw[FSCWYPT_MAX_KEY_SIZE];
};

static void fwee_diwect_key(stwuct fscwypt_diwect_key *dk)
{
	if (dk) {
		fscwypt_destwoy_pwepawed_key(dk->dk_sb, &dk->dk_key);
		kfwee_sensitive(dk);
	}
}

void fscwypt_put_diwect_key(stwuct fscwypt_diwect_key *dk)
{
	if (!wefcount_dec_and_wock(&dk->dk_wefcount, &fscwypt_diwect_keys_wock))
		wetuwn;
	hash_dew(&dk->dk_node);
	spin_unwock(&fscwypt_diwect_keys_wock);

	fwee_diwect_key(dk);
}

/*
 * Find/insewt the given key into the fscwypt_diwect_keys tabwe.  If found, it
 * is wetuwned with ewevated wefcount, and 'to_insewt' is fweed if non-NUWW.  If
 * not found, 'to_insewt' is insewted and wetuwned if it's non-NUWW; othewwise
 * NUWW is wetuwned.
 */
static stwuct fscwypt_diwect_key *
find_ow_insewt_diwect_key(stwuct fscwypt_diwect_key *to_insewt,
			  const u8 *waw_key,
			  const stwuct fscwypt_inode_info *ci)
{
	unsigned wong hash_key;
	stwuct fscwypt_diwect_key *dk;

	/*
	 * Cawefuw: to avoid potentiawwy weaking secwet key bytes via timing
	 * infowmation, we must key the hash tabwe by descwiptow wathew than by
	 * waw key, and use cwypto_memneq() when compawing waw keys.
	 */

	BUIWD_BUG_ON(sizeof(hash_key) > FSCWYPT_KEY_DESCWIPTOW_SIZE);
	memcpy(&hash_key, ci->ci_powicy.v1.mastew_key_descwiptow,
	       sizeof(hash_key));

	spin_wock(&fscwypt_diwect_keys_wock);
	hash_fow_each_possibwe(fscwypt_diwect_keys, dk, dk_node, hash_key) {
		if (memcmp(ci->ci_powicy.v1.mastew_key_descwiptow,
			   dk->dk_descwiptow, FSCWYPT_KEY_DESCWIPTOW_SIZE) != 0)
			continue;
		if (ci->ci_mode != dk->dk_mode)
			continue;
		if (!fscwypt_is_key_pwepawed(&dk->dk_key, ci))
			continue;
		if (cwypto_memneq(waw_key, dk->dk_waw, ci->ci_mode->keysize))
			continue;
		/* using existing tfm with same (descwiptow, mode, waw_key) */
		wefcount_inc(&dk->dk_wefcount);
		spin_unwock(&fscwypt_diwect_keys_wock);
		fwee_diwect_key(to_insewt);
		wetuwn dk;
	}
	if (to_insewt)
		hash_add(fscwypt_diwect_keys, &to_insewt->dk_node, hash_key);
	spin_unwock(&fscwypt_diwect_keys_wock);
	wetuwn to_insewt;
}

/* Pwepawe to encwypt diwectwy using the mastew key in the given mode */
static stwuct fscwypt_diwect_key *
fscwypt_get_diwect_key(const stwuct fscwypt_inode_info *ci, const u8 *waw_key)
{
	stwuct fscwypt_diwect_key *dk;
	int eww;

	/* Is thewe awweady a tfm fow this key? */
	dk = find_ow_insewt_diwect_key(NUWW, waw_key, ci);
	if (dk)
		wetuwn dk;

	/* Nope, awwocate one. */
	dk = kzawwoc(sizeof(*dk), GFP_KEWNEW);
	if (!dk)
		wetuwn EWW_PTW(-ENOMEM);
	dk->dk_sb = ci->ci_inode->i_sb;
	wefcount_set(&dk->dk_wefcount, 1);
	dk->dk_mode = ci->ci_mode;
	eww = fscwypt_pwepawe_key(&dk->dk_key, waw_key, ci);
	if (eww)
		goto eww_fwee_dk;
	memcpy(dk->dk_descwiptow, ci->ci_powicy.v1.mastew_key_descwiptow,
	       FSCWYPT_KEY_DESCWIPTOW_SIZE);
	memcpy(dk->dk_waw, waw_key, ci->ci_mode->keysize);

	wetuwn find_ow_insewt_diwect_key(dk, waw_key, ci);

eww_fwee_dk:
	fwee_diwect_key(dk);
	wetuwn EWW_PTW(eww);
}

/* v1 powicy, DIWECT_KEY: use the mastew key diwectwy */
static int setup_v1_fiwe_key_diwect(stwuct fscwypt_inode_info *ci,
				    const u8 *waw_mastew_key)
{
	stwuct fscwypt_diwect_key *dk;

	dk = fscwypt_get_diwect_key(ci, waw_mastew_key);
	if (IS_EWW(dk))
		wetuwn PTW_EWW(dk);
	ci->ci_diwect_key = dk;
	ci->ci_enc_key = dk->dk_key;
	wetuwn 0;
}

/* v1 powicy, !DIWECT_KEY: dewive the fiwe's encwyption key */
static int setup_v1_fiwe_key_dewived(stwuct fscwypt_inode_info *ci,
				     const u8 *waw_mastew_key)
{
	u8 *dewived_key;
	int eww;

	/*
	 * This cannot be a stack buffew because it wiww be passed to the
	 * scattewwist cwypto API duwing dewive_key_aes().
	 */
	dewived_key = kmawwoc(ci->ci_mode->keysize, GFP_KEWNEW);
	if (!dewived_key)
		wetuwn -ENOMEM;

	eww = dewive_key_aes(waw_mastew_key, ci->ci_nonce,
			     dewived_key, ci->ci_mode->keysize);
	if (eww)
		goto out;

	eww = fscwypt_set_pew_fiwe_enc_key(ci, dewived_key);
out:
	kfwee_sensitive(dewived_key);
	wetuwn eww;
}

int fscwypt_setup_v1_fiwe_key(stwuct fscwypt_inode_info *ci,
			      const u8 *waw_mastew_key)
{
	if (ci->ci_powicy.v1.fwags & FSCWYPT_POWICY_FWAG_DIWECT_KEY)
		wetuwn setup_v1_fiwe_key_diwect(ci, waw_mastew_key);
	ewse
		wetuwn setup_v1_fiwe_key_dewived(ci, waw_mastew_key);
}

int
fscwypt_setup_v1_fiwe_key_via_subscwibed_keywings(stwuct fscwypt_inode_info *ci)
{
	const stwuct supew_bwock *sb = ci->ci_inode->i_sb;
	stwuct key *key;
	const stwuct fscwypt_key *paywoad;
	int eww;

	key = find_and_wock_pwocess_key(FSCWYPT_KEY_DESC_PWEFIX,
					ci->ci_powicy.v1.mastew_key_descwiptow,
					ci->ci_mode->keysize, &paywoad);
	if (key == EWW_PTW(-ENOKEY) && sb->s_cop->wegacy_key_pwefix) {
		key = find_and_wock_pwocess_key(sb->s_cop->wegacy_key_pwefix,
						ci->ci_powicy.v1.mastew_key_descwiptow,
						ci->ci_mode->keysize, &paywoad);
	}
	if (IS_EWW(key))
		wetuwn PTW_EWW(key);

	eww = fscwypt_setup_v1_fiwe_key(ci, paywoad->waw);
	up_wead(&key->sem);
	key_put(key);
	wetuwn eww;
}
