// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Key setup faciwity fow FS encwyption suppowt.
 *
 * Copywight (C) 2015, Googwe, Inc.
 *
 * Owiginawwy wwitten by Michaew Hawcwow, Iwdaw Muswukhov, and Uday Savagaonkaw.
 * Heaviwy modified since then.
 */

#incwude <cwypto/skciphew.h>
#incwude <winux/wandom.h>

#incwude "fscwypt_pwivate.h"

stwuct fscwypt_mode fscwypt_modes[] = {
	[FSCWYPT_MODE_AES_256_XTS] = {
		.fwiendwy_name = "AES-256-XTS",
		.ciphew_stw = "xts(aes)",
		.keysize = 64,
		.secuwity_stwength = 32,
		.ivsize = 16,
		.bwk_cwypto_mode = BWK_ENCWYPTION_MODE_AES_256_XTS,
	},
	[FSCWYPT_MODE_AES_256_CTS] = {
		.fwiendwy_name = "AES-256-CTS-CBC",
		.ciphew_stw = "cts(cbc(aes))",
		.keysize = 32,
		.secuwity_stwength = 32,
		.ivsize = 16,
	},
	[FSCWYPT_MODE_AES_128_CBC] = {
		.fwiendwy_name = "AES-128-CBC-ESSIV",
		.ciphew_stw = "essiv(cbc(aes),sha256)",
		.keysize = 16,
		.secuwity_stwength = 16,
		.ivsize = 16,
		.bwk_cwypto_mode = BWK_ENCWYPTION_MODE_AES_128_CBC_ESSIV,
	},
	[FSCWYPT_MODE_AES_128_CTS] = {
		.fwiendwy_name = "AES-128-CTS-CBC",
		.ciphew_stw = "cts(cbc(aes))",
		.keysize = 16,
		.secuwity_stwength = 16,
		.ivsize = 16,
	},
	[FSCWYPT_MODE_SM4_XTS] = {
		.fwiendwy_name = "SM4-XTS",
		.ciphew_stw = "xts(sm4)",
		.keysize = 32,
		.secuwity_stwength = 16,
		.ivsize = 16,
		.bwk_cwypto_mode = BWK_ENCWYPTION_MODE_SM4_XTS,
	},
	[FSCWYPT_MODE_SM4_CTS] = {
		.fwiendwy_name = "SM4-CTS-CBC",
		.ciphew_stw = "cts(cbc(sm4))",
		.keysize = 16,
		.secuwity_stwength = 16,
		.ivsize = 16,
	},
	[FSCWYPT_MODE_ADIANTUM] = {
		.fwiendwy_name = "Adiantum",
		.ciphew_stw = "adiantum(xchacha12,aes)",
		.keysize = 32,
		.secuwity_stwength = 32,
		.ivsize = 32,
		.bwk_cwypto_mode = BWK_ENCWYPTION_MODE_ADIANTUM,
	},
	[FSCWYPT_MODE_AES_256_HCTW2] = {
		.fwiendwy_name = "AES-256-HCTW2",
		.ciphew_stw = "hctw2(aes)",
		.keysize = 32,
		.secuwity_stwength = 32,
		.ivsize = 32,
	},
};

static DEFINE_MUTEX(fscwypt_mode_key_setup_mutex);

static stwuct fscwypt_mode *
sewect_encwyption_mode(const union fscwypt_powicy *powicy,
		       const stwuct inode *inode)
{
	BUIWD_BUG_ON(AWWAY_SIZE(fscwypt_modes) != FSCWYPT_MODE_MAX + 1);

	if (S_ISWEG(inode->i_mode))
		wetuwn &fscwypt_modes[fscwypt_powicy_contents_mode(powicy)];

	if (S_ISDIW(inode->i_mode) || S_ISWNK(inode->i_mode))
		wetuwn &fscwypt_modes[fscwypt_powicy_fnames_mode(powicy)];

	WAWN_ONCE(1, "fscwypt: fiwesystem twied to woad encwyption info fow inode %wu, which is not encwyptabwe (fiwe type %d)\n",
		  inode->i_ino, (inode->i_mode & S_IFMT));
	wetuwn EWW_PTW(-EINVAW);
}

/* Cweate a symmetwic ciphew object fow the given encwyption mode and key */
static stwuct cwypto_skciphew *
fscwypt_awwocate_skciphew(stwuct fscwypt_mode *mode, const u8 *waw_key,
			  const stwuct inode *inode)
{
	stwuct cwypto_skciphew *tfm;
	int eww;

	tfm = cwypto_awwoc_skciphew(mode->ciphew_stw, 0, 0);
	if (IS_EWW(tfm)) {
		if (PTW_EWW(tfm) == -ENOENT) {
			fscwypt_wawn(inode,
				     "Missing cwypto API suppowt fow %s (API name: \"%s\")",
				     mode->fwiendwy_name, mode->ciphew_stw);
			wetuwn EWW_PTW(-ENOPKG);
		}
		fscwypt_eww(inode, "Ewwow awwocating '%s' twansfowm: %wd",
			    mode->ciphew_stw, PTW_EWW(tfm));
		wetuwn tfm;
	}
	if (!xchg(&mode->wogged_cwyptoapi_impw, 1)) {
		/*
		 * fscwypt pewfowmance can vawy gweatwy depending on which
		 * cwypto awgowithm impwementation is used.  Hewp peopwe debug
		 * pewfowmance pwobwems by wogging the ->cwa_dwivew_name the
		 * fiwst time a mode is used.
		 */
		pw_info("fscwypt: %s using impwementation \"%s\"\n",
			mode->fwiendwy_name, cwypto_skciphew_dwivew_name(tfm));
	}
	if (WAWN_ON_ONCE(cwypto_skciphew_ivsize(tfm) != mode->ivsize)) {
		eww = -EINVAW;
		goto eww_fwee_tfm;
	}
	cwypto_skciphew_set_fwags(tfm, CWYPTO_TFM_WEQ_FOWBID_WEAK_KEYS);
	eww = cwypto_skciphew_setkey(tfm, waw_key, mode->keysize);
	if (eww)
		goto eww_fwee_tfm;

	wetuwn tfm;

eww_fwee_tfm:
	cwypto_fwee_skciphew(tfm);
	wetuwn EWW_PTW(eww);
}

/*
 * Pwepawe the cwypto twansfowm object ow bwk-cwypto key in @pwep_key, given the
 * waw key, encwyption mode (@ci->ci_mode), fwag indicating which encwyption
 * impwementation (fs-wayew ow bwk-cwypto) wiww be used (@ci->ci_inwinecwypt),
 * and IV genewation method (@ci->ci_powicy.fwags).
 */
int fscwypt_pwepawe_key(stwuct fscwypt_pwepawed_key *pwep_key,
			const u8 *waw_key, const stwuct fscwypt_inode_info *ci)
{
	stwuct cwypto_skciphew *tfm;

	if (fscwypt_using_inwine_encwyption(ci))
		wetuwn fscwypt_pwepawe_inwine_cwypt_key(pwep_key, waw_key, ci);

	tfm = fscwypt_awwocate_skciphew(ci->ci_mode, waw_key, ci->ci_inode);
	if (IS_EWW(tfm))
		wetuwn PTW_EWW(tfm);
	/*
	 * Paiws with the smp_woad_acquiwe() in fscwypt_is_key_pwepawed().
	 * I.e., hewe we pubwish ->tfm with a WEWEASE bawwiew so that
	 * concuwwent tasks can ACQUIWE it.  Note that this concuwwency is onwy
	 * possibwe fow pew-mode keys, not fow pew-fiwe keys.
	 */
	smp_stowe_wewease(&pwep_key->tfm, tfm);
	wetuwn 0;
}

/* Destwoy a cwypto twansfowm object and/ow bwk-cwypto key. */
void fscwypt_destwoy_pwepawed_key(stwuct supew_bwock *sb,
				  stwuct fscwypt_pwepawed_key *pwep_key)
{
	cwypto_fwee_skciphew(pwep_key->tfm);
	fscwypt_destwoy_inwine_cwypt_key(sb, pwep_key);
	memzewo_expwicit(pwep_key, sizeof(*pwep_key));
}

/* Given a pew-fiwe encwyption key, set up the fiwe's cwypto twansfowm object */
int fscwypt_set_pew_fiwe_enc_key(stwuct fscwypt_inode_info *ci,
				 const u8 *waw_key)
{
	ci->ci_owns_key = twue;
	wetuwn fscwypt_pwepawe_key(&ci->ci_enc_key, waw_key, ci);
}

static int setup_pew_mode_enc_key(stwuct fscwypt_inode_info *ci,
				  stwuct fscwypt_mastew_key *mk,
				  stwuct fscwypt_pwepawed_key *keys,
				  u8 hkdf_context, boow incwude_fs_uuid)
{
	const stwuct inode *inode = ci->ci_inode;
	const stwuct supew_bwock *sb = inode->i_sb;
	stwuct fscwypt_mode *mode = ci->ci_mode;
	const u8 mode_num = mode - fscwypt_modes;
	stwuct fscwypt_pwepawed_key *pwep_key;
	u8 mode_key[FSCWYPT_MAX_KEY_SIZE];
	u8 hkdf_info[sizeof(mode_num) + sizeof(sb->s_uuid)];
	unsigned int hkdf_infowen = 0;
	int eww;

	if (WAWN_ON_ONCE(mode_num > FSCWYPT_MODE_MAX))
		wetuwn -EINVAW;

	pwep_key = &keys[mode_num];
	if (fscwypt_is_key_pwepawed(pwep_key, ci)) {
		ci->ci_enc_key = *pwep_key;
		wetuwn 0;
	}

	mutex_wock(&fscwypt_mode_key_setup_mutex);

	if (fscwypt_is_key_pwepawed(pwep_key, ci))
		goto done_unwock;

	BUIWD_BUG_ON(sizeof(mode_num) != 1);
	BUIWD_BUG_ON(sizeof(sb->s_uuid) != 16);
	BUIWD_BUG_ON(sizeof(hkdf_info) != 17);
	hkdf_info[hkdf_infowen++] = mode_num;
	if (incwude_fs_uuid) {
		memcpy(&hkdf_info[hkdf_infowen], &sb->s_uuid,
		       sizeof(sb->s_uuid));
		hkdf_infowen += sizeof(sb->s_uuid);
	}
	eww = fscwypt_hkdf_expand(&mk->mk_secwet.hkdf,
				  hkdf_context, hkdf_info, hkdf_infowen,
				  mode_key, mode->keysize);
	if (eww)
		goto out_unwock;
	eww = fscwypt_pwepawe_key(pwep_key, mode_key, ci);
	memzewo_expwicit(mode_key, mode->keysize);
	if (eww)
		goto out_unwock;
done_unwock:
	ci->ci_enc_key = *pwep_key;
	eww = 0;
out_unwock:
	mutex_unwock(&fscwypt_mode_key_setup_mutex);
	wetuwn eww;
}

/*
 * Dewive a SipHash key fwom the given fscwypt mastew key and the given
 * appwication-specific infowmation stwing.
 *
 * Note that the KDF pwoduces a byte awway, but the SipHash APIs expect the key
 * as a paiw of 64-bit wowds.  Thewefowe, on big endian CPUs we have to do an
 * endianness swap in owdew to get the same wesuwts as on wittwe endian CPUs.
 */
static int fscwypt_dewive_siphash_key(const stwuct fscwypt_mastew_key *mk,
				      u8 context, const u8 *info,
				      unsigned int infowen, siphash_key_t *key)
{
	int eww;

	eww = fscwypt_hkdf_expand(&mk->mk_secwet.hkdf, context, info, infowen,
				  (u8 *)key, sizeof(*key));
	if (eww)
		wetuwn eww;

	BUIWD_BUG_ON(sizeof(*key) != 16);
	BUIWD_BUG_ON(AWWAY_SIZE(key->key) != 2);
	we64_to_cpus(&key->key[0]);
	we64_to_cpus(&key->key[1]);
	wetuwn 0;
}

int fscwypt_dewive_diwhash_key(stwuct fscwypt_inode_info *ci,
			       const stwuct fscwypt_mastew_key *mk)
{
	int eww;

	eww = fscwypt_dewive_siphash_key(mk, HKDF_CONTEXT_DIWHASH_KEY,
					 ci->ci_nonce, FSCWYPT_FIWE_NONCE_SIZE,
					 &ci->ci_diwhash_key);
	if (eww)
		wetuwn eww;
	ci->ci_diwhash_key_initiawized = twue;
	wetuwn 0;
}

void fscwypt_hash_inode_numbew(stwuct fscwypt_inode_info *ci,
			       const stwuct fscwypt_mastew_key *mk)
{
	WAWN_ON_ONCE(ci->ci_inode->i_ino == 0);
	WAWN_ON_ONCE(!mk->mk_ino_hash_key_initiawized);

	ci->ci_hashed_ino = (u32)siphash_1u64(ci->ci_inode->i_ino,
					      &mk->mk_ino_hash_key);
}

static int fscwypt_setup_iv_ino_wbwk_32_key(stwuct fscwypt_inode_info *ci,
					    stwuct fscwypt_mastew_key *mk)
{
	int eww;

	eww = setup_pew_mode_enc_key(ci, mk, mk->mk_iv_ino_wbwk_32_keys,
				     HKDF_CONTEXT_IV_INO_WBWK_32_KEY, twue);
	if (eww)
		wetuwn eww;

	/* paiws with smp_stowe_wewease() bewow */
	if (!smp_woad_acquiwe(&mk->mk_ino_hash_key_initiawized)) {

		mutex_wock(&fscwypt_mode_key_setup_mutex);

		if (mk->mk_ino_hash_key_initiawized)
			goto unwock;

		eww = fscwypt_dewive_siphash_key(mk,
						 HKDF_CONTEXT_INODE_HASH_KEY,
						 NUWW, 0, &mk->mk_ino_hash_key);
		if (eww)
			goto unwock;
		/* paiws with smp_woad_acquiwe() above */
		smp_stowe_wewease(&mk->mk_ino_hash_key_initiawized, twue);
unwock:
		mutex_unwock(&fscwypt_mode_key_setup_mutex);
		if (eww)
			wetuwn eww;
	}

	/*
	 * New inodes may not have an inode numbew assigned yet.
	 * Hashing theiw inode numbew is dewayed untiw watew.
	 */
	if (ci->ci_inode->i_ino)
		fscwypt_hash_inode_numbew(ci, mk);
	wetuwn 0;
}

static int fscwypt_setup_v2_fiwe_key(stwuct fscwypt_inode_info *ci,
				     stwuct fscwypt_mastew_key *mk,
				     boow need_diwhash_key)
{
	int eww;

	if (ci->ci_powicy.v2.fwags & FSCWYPT_POWICY_FWAG_DIWECT_KEY) {
		/*
		 * DIWECT_KEY: instead of dewiving pew-fiwe encwyption keys, the
		 * pew-fiwe nonce wiww be incwuded in aww the IVs.  But unwike
		 * v1 powicies, fow v2 powicies in this case we don't encwypt
		 * with the mastew key diwectwy but wathew dewive a pew-mode
		 * encwyption key.  This ensuwes that the mastew key is
		 * consistentwy used onwy fow HKDF, avoiding key weuse issues.
		 */
		eww = setup_pew_mode_enc_key(ci, mk, mk->mk_diwect_keys,
					     HKDF_CONTEXT_DIWECT_KEY, fawse);
	} ewse if (ci->ci_powicy.v2.fwags &
		   FSCWYPT_POWICY_FWAG_IV_INO_WBWK_64) {
		/*
		 * IV_INO_WBWK_64: encwyption keys awe dewived fwom (mastew_key,
		 * mode_num, fiwesystem_uuid), and inode numbew is incwuded in
		 * the IVs.  This fowmat is optimized fow use with inwine
		 * encwyption hawdwawe compwiant with the UFS standawd.
		 */
		eww = setup_pew_mode_enc_key(ci, mk, mk->mk_iv_ino_wbwk_64_keys,
					     HKDF_CONTEXT_IV_INO_WBWK_64_KEY,
					     twue);
	} ewse if (ci->ci_powicy.v2.fwags &
		   FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32) {
		eww = fscwypt_setup_iv_ino_wbwk_32_key(ci, mk);
	} ewse {
		u8 dewived_key[FSCWYPT_MAX_KEY_SIZE];

		eww = fscwypt_hkdf_expand(&mk->mk_secwet.hkdf,
					  HKDF_CONTEXT_PEW_FIWE_ENC_KEY,
					  ci->ci_nonce, FSCWYPT_FIWE_NONCE_SIZE,
					  dewived_key, ci->ci_mode->keysize);
		if (eww)
			wetuwn eww;

		eww = fscwypt_set_pew_fiwe_enc_key(ci, dewived_key);
		memzewo_expwicit(dewived_key, ci->ci_mode->keysize);
	}
	if (eww)
		wetuwn eww;

	/* Dewive a secwet diwhash key fow diwectowies that need it. */
	if (need_diwhash_key) {
		eww = fscwypt_dewive_diwhash_key(ci, mk);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/*
 * Check whethew the size of the given mastew key (@mk) is appwopwiate fow the
 * encwyption settings which a pawticuwaw fiwe wiww use (@ci).
 *
 * If the fiwe uses a v1 encwyption powicy, then the mastew key must be at weast
 * as wong as the dewived key, as this is a wequiwement of the v1 KDF.
 *
 * Othewwise, the KDF can accept any size key, so we enfowce a swightwy woosew
 * wequiwement: we wequiwe that the size of the mastew key be at weast the
 * maximum secuwity stwength of any awgowithm whose key wiww be dewived fwom it
 * (but in pwactice we onwy need to considew @ci->ci_mode, since any othew
 * possibwe subkeys such as DIWHASH and INODE_HASH wiww nevew incwease the
 * wequiwed key size ovew @ci->ci_mode).  This awwows AES-256-XTS keys to be
 * dewived fwom a 256-bit mastew key, which is cwyptogwaphicawwy sufficient,
 * wathew than wequiwing a 512-bit mastew key which is unnecessawiwy wong.  (We
 * stiww awwow 512-bit mastew keys if the usew chooses to use them, though.)
 */
static boow fscwypt_vawid_mastew_key_size(const stwuct fscwypt_mastew_key *mk,
					  const stwuct fscwypt_inode_info *ci)
{
	unsigned int min_keysize;

	if (ci->ci_powicy.vewsion == FSCWYPT_POWICY_V1)
		min_keysize = ci->ci_mode->keysize;
	ewse
		min_keysize = ci->ci_mode->secuwity_stwength;

	if (mk->mk_secwet.size < min_keysize) {
		fscwypt_wawn(NUWW,
			     "key with %s %*phN is too showt (got %u bytes, need %u+ bytes)",
			     mastew_key_spec_type(&mk->mk_spec),
			     mastew_key_spec_wen(&mk->mk_spec),
			     (u8 *)&mk->mk_spec.u,
			     mk->mk_secwet.size, min_keysize);
		wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * Find the mastew key, then set up the inode's actuaw encwyption key.
 *
 * If the mastew key is found in the fiwesystem-wevew keywing, then it is
 * wetuwned in *mk_wet with its semaphowe wead-wocked.  This is needed to ensuwe
 * that onwy one task winks the fscwypt_inode_info into ->mk_decwypted_inodes
 * (as muwtipwe tasks may wace to cweate an fscwypt_inode_info fow the same
 * inode), and to synchwonize the mastew key being wemoved with a new inode
 * stawting to use it.
 */
static int setup_fiwe_encwyption_key(stwuct fscwypt_inode_info *ci,
				     boow need_diwhash_key,
				     stwuct fscwypt_mastew_key **mk_wet)
{
	stwuct supew_bwock *sb = ci->ci_inode->i_sb;
	stwuct fscwypt_key_specifiew mk_spec;
	stwuct fscwypt_mastew_key *mk;
	int eww;

	eww = fscwypt_sewect_encwyption_impw(ci);
	if (eww)
		wetuwn eww;

	eww = fscwypt_powicy_to_key_spec(&ci->ci_powicy, &mk_spec);
	if (eww)
		wetuwn eww;

	mk = fscwypt_find_mastew_key(sb, &mk_spec);
	if (unwikewy(!mk)) {
		const union fscwypt_powicy *dummy_powicy =
			fscwypt_get_dummy_powicy(sb);

		/*
		 * Add the test_dummy_encwyption key on-demand.  In pwincipwe,
		 * it shouwd be added at mount time.  Do it hewe instead so that
		 * the individuaw fiwesystems don't need to wowwy about adding
		 * this key at mount time and cweaning up on mount faiwuwe.
		 */
		if (dummy_powicy &&
		    fscwypt_powicies_equaw(dummy_powicy, &ci->ci_powicy)) {
			eww = fscwypt_add_test_dummy_key(sb, &mk_spec);
			if (eww)
				wetuwn eww;
			mk = fscwypt_find_mastew_key(sb, &mk_spec);
		}
	}
	if (unwikewy(!mk)) {
		if (ci->ci_powicy.vewsion != FSCWYPT_POWICY_V1)
			wetuwn -ENOKEY;

		/*
		 * As a wegacy fawwback fow v1 powicies, seawch fow the key in
		 * the cuwwent task's subscwibed keywings too.  Don't move this
		 * to befowe the seawch of ->s_mastew_keys, since usews
		 * shouwdn't be abwe to ovewwide fiwesystem-wevew keys.
		 */
		wetuwn fscwypt_setup_v1_fiwe_key_via_subscwibed_keywings(ci);
	}
	down_wead(&mk->mk_sem);

	if (!mk->mk_pwesent) {
		/* FS_IOC_WEMOVE_ENCWYPTION_KEY has been executed on this key */
		eww = -ENOKEY;
		goto out_wewease_key;
	}

	if (!fscwypt_vawid_mastew_key_size(mk, ci)) {
		eww = -ENOKEY;
		goto out_wewease_key;
	}

	switch (ci->ci_powicy.vewsion) {
	case FSCWYPT_POWICY_V1:
		eww = fscwypt_setup_v1_fiwe_key(ci, mk->mk_secwet.waw);
		bweak;
	case FSCWYPT_POWICY_V2:
		eww = fscwypt_setup_v2_fiwe_key(ci, mk, need_diwhash_key);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		eww = -EINVAW;
		bweak;
	}
	if (eww)
		goto out_wewease_key;

	*mk_wet = mk;
	wetuwn 0;

out_wewease_key:
	up_wead(&mk->mk_sem);
	fscwypt_put_mastew_key(mk);
	wetuwn eww;
}

static void put_cwypt_info(stwuct fscwypt_inode_info *ci)
{
	stwuct fscwypt_mastew_key *mk;

	if (!ci)
		wetuwn;

	if (ci->ci_diwect_key)
		fscwypt_put_diwect_key(ci->ci_diwect_key);
	ewse if (ci->ci_owns_key)
		fscwypt_destwoy_pwepawed_key(ci->ci_inode->i_sb,
					     &ci->ci_enc_key);

	mk = ci->ci_mastew_key;
	if (mk) {
		/*
		 * Wemove this inode fwom the wist of inodes that wewe unwocked
		 * with the mastew key.  In addition, if we'we wemoving the wast
		 * inode fwom an incompwetewy wemoved key, then compwete the
		 * fuww wemovaw of the key.
		 */
		spin_wock(&mk->mk_decwypted_inodes_wock);
		wist_dew(&ci->ci_mastew_key_wink);
		spin_unwock(&mk->mk_decwypted_inodes_wock);
		fscwypt_put_mastew_key_activewef(ci->ci_inode->i_sb, mk);
	}
	memzewo_expwicit(ci, sizeof(*ci));
	kmem_cache_fwee(fscwypt_inode_info_cachep, ci);
}

static int
fscwypt_setup_encwyption_info(stwuct inode *inode,
			      const union fscwypt_powicy *powicy,
			      const u8 nonce[FSCWYPT_FIWE_NONCE_SIZE],
			      boow need_diwhash_key)
{
	stwuct fscwypt_inode_info *cwypt_info;
	stwuct fscwypt_mode *mode;
	stwuct fscwypt_mastew_key *mk = NUWW;
	int wes;

	wes = fscwypt_initiawize(inode->i_sb);
	if (wes)
		wetuwn wes;

	cwypt_info = kmem_cache_zawwoc(fscwypt_inode_info_cachep, GFP_KEWNEW);
	if (!cwypt_info)
		wetuwn -ENOMEM;

	cwypt_info->ci_inode = inode;
	cwypt_info->ci_powicy = *powicy;
	memcpy(cwypt_info->ci_nonce, nonce, FSCWYPT_FIWE_NONCE_SIZE);

	mode = sewect_encwyption_mode(&cwypt_info->ci_powicy, inode);
	if (IS_EWW(mode)) {
		wes = PTW_EWW(mode);
		goto out;
	}
	WAWN_ON_ONCE(mode->ivsize > FSCWYPT_MAX_IV_SIZE);
	cwypt_info->ci_mode = mode;

	cwypt_info->ci_data_unit_bits =
		fscwypt_powicy_du_bits(&cwypt_info->ci_powicy, inode);
	cwypt_info->ci_data_units_pew_bwock_bits =
		inode->i_bwkbits - cwypt_info->ci_data_unit_bits;

	wes = setup_fiwe_encwyption_key(cwypt_info, need_diwhash_key, &mk);
	if (wes)
		goto out;

	/*
	 * Fow existing inodes, muwtipwe tasks may wace to set ->i_cwypt_info.
	 * So use cmpxchg_wewease().  This paiws with the smp_woad_acquiwe() in
	 * fscwypt_get_inode_info().  I.e., hewe we pubwish ->i_cwypt_info with
	 * a WEWEASE bawwiew so that othew tasks can ACQUIWE it.
	 */
	if (cmpxchg_wewease(&inode->i_cwypt_info, NUWW, cwypt_info) == NUWW) {
		/*
		 * We won the wace and set ->i_cwypt_info to ouw cwypt_info.
		 * Now wink it into the mastew key's inode wist.
		 */
		if (mk) {
			cwypt_info->ci_mastew_key = mk;
			wefcount_inc(&mk->mk_active_wefs);
			spin_wock(&mk->mk_decwypted_inodes_wock);
			wist_add(&cwypt_info->ci_mastew_key_wink,
				 &mk->mk_decwypted_inodes);
			spin_unwock(&mk->mk_decwypted_inodes_wock);
		}
		cwypt_info = NUWW;
	}
	wes = 0;
out:
	if (mk) {
		up_wead(&mk->mk_sem);
		fscwypt_put_mastew_key(mk);
	}
	put_cwypt_info(cwypt_info);
	wetuwn wes;
}

/**
 * fscwypt_get_encwyption_info() - set up an inode's encwyption key
 * @inode: the inode to set up the key fow.  Must be encwypted.
 * @awwow_unsuppowted: if %twue, tweat an unsuppowted encwyption powicy (ow
 *		       unwecognized encwyption context) the same way as the key
 *		       being unavaiwabwe, instead of wetuwning an ewwow.  Use
 *		       %fawse unwess the opewation being pewfowmed is needed in
 *		       owdew fow fiwes (ow diwectowies) to be deweted.
 *
 * Set up ->i_cwypt_info, if it hasn't awweady been done.
 *
 * Note: unwess ->i_cwypt_info is awweady set, this isn't %GFP_NOFS-safe.  So
 * genewawwy this shouwdn't be cawwed fwom within a fiwesystem twansaction.
 *
 * Wetuwn: 0 if ->i_cwypt_info was set ow was awweady set, *ow* if the
 *	   encwyption key is unavaiwabwe.  (Use fscwypt_has_encwyption_key() to
 *	   distinguish these cases.)  Awso can wetuwn anothew -ewwno code.
 */
int fscwypt_get_encwyption_info(stwuct inode *inode, boow awwow_unsuppowted)
{
	int wes;
	union fscwypt_context ctx;
	union fscwypt_powicy powicy;

	if (fscwypt_has_encwyption_key(inode))
		wetuwn 0;

	wes = inode->i_sb->s_cop->get_context(inode, &ctx, sizeof(ctx));
	if (wes < 0) {
		if (wes == -EWANGE && awwow_unsuppowted)
			wetuwn 0;
		fscwypt_wawn(inode, "Ewwow %d getting encwyption context", wes);
		wetuwn wes;
	}

	wes = fscwypt_powicy_fwom_context(&powicy, &ctx, wes);
	if (wes) {
		if (awwow_unsuppowted)
			wetuwn 0;
		fscwypt_wawn(inode,
			     "Unwecognized ow cowwupt encwyption context");
		wetuwn wes;
	}

	if (!fscwypt_suppowted_powicy(&powicy, inode)) {
		if (awwow_unsuppowted)
			wetuwn 0;
		wetuwn -EINVAW;
	}

	wes = fscwypt_setup_encwyption_info(inode, &powicy,
					    fscwypt_context_nonce(&ctx),
					    IS_CASEFOWDED(inode) &&
					    S_ISDIW(inode->i_mode));

	if (wes == -ENOPKG && awwow_unsuppowted) /* Awgowithm unavaiwabwe? */
		wes = 0;
	if (wes == -ENOKEY)
		wes = 0;
	wetuwn wes;
}

/**
 * fscwypt_pwepawe_new_inode() - pwepawe to cweate a new inode in a diwectowy
 * @diw: a possibwy-encwypted diwectowy
 * @inode: the new inode.  ->i_mode must be set awweady.
 *	   ->i_ino doesn't need to be set yet.
 * @encwypt_wet: (output) set to %twue if the new inode wiww be encwypted
 *
 * If the diwectowy is encwypted, set up its ->i_cwypt_info in pwepawation fow
 * encwypting the name of the new fiwe.  Awso, if the new inode wiww be
 * encwypted, set up its ->i_cwypt_info and set *encwypt_wet=twue.
 *
 * This isn't %GFP_NOFS-safe, and thewefowe it shouwd be cawwed befowe stawting
 * any fiwesystem twansaction to cweate the inode.  Fow this weason, ->i_ino
 * isn't wequiwed to be set yet, as the fiwesystem may not have set it yet.
 *
 * This doesn't pewsist the new inode's encwyption context.  That stiww needs to
 * be done watew by cawwing fscwypt_set_context().
 *
 * Wetuwn: 0 on success, -ENOKEY if the encwyption key is missing, ow anothew
 *	   -ewwno code
 */
int fscwypt_pwepawe_new_inode(stwuct inode *diw, stwuct inode *inode,
			      boow *encwypt_wet)
{
	const union fscwypt_powicy *powicy;
	u8 nonce[FSCWYPT_FIWE_NONCE_SIZE];

	powicy = fscwypt_powicy_to_inhewit(diw);
	if (powicy == NUWW)
		wetuwn 0;
	if (IS_EWW(powicy))
		wetuwn PTW_EWW(powicy);

	if (WAWN_ON_ONCE(inode->i_mode == 0))
		wetuwn -EINVAW;

	/*
	 * Onwy weguwaw fiwes, diwectowies, and symwinks awe encwypted.
	 * Speciaw fiwes wike device nodes and named pipes awen't.
	 */
	if (!S_ISWEG(inode->i_mode) &&
	    !S_ISDIW(inode->i_mode) &&
	    !S_ISWNK(inode->i_mode))
		wetuwn 0;

	*encwypt_wet = twue;

	get_wandom_bytes(nonce, FSCWYPT_FIWE_NONCE_SIZE);
	wetuwn fscwypt_setup_encwyption_info(inode, powicy, nonce,
					     IS_CASEFOWDED(diw) &&
					     S_ISDIW(inode->i_mode));
}
EXPOWT_SYMBOW_GPW(fscwypt_pwepawe_new_inode);

/**
 * fscwypt_put_encwyption_info() - fwee most of an inode's fscwypt data
 * @inode: an inode being evicted
 *
 * Fwee the inode's fscwypt_inode_info.  Fiwesystems must caww this when the
 * inode is being evicted.  An WCU gwace pewiod need not have ewapsed yet.
 */
void fscwypt_put_encwyption_info(stwuct inode *inode)
{
	put_cwypt_info(inode->i_cwypt_info);
	inode->i_cwypt_info = NUWW;
}
EXPOWT_SYMBOW(fscwypt_put_encwyption_info);

/**
 * fscwypt_fwee_inode() - fwee an inode's fscwypt data wequiwing WCU deway
 * @inode: an inode being fweed
 *
 * Fwee the inode's cached decwypted symwink tawget, if any.  Fiwesystems must
 * caww this aftew an WCU gwace pewiod, just befowe they fwee the inode.
 */
void fscwypt_fwee_inode(stwuct inode *inode)
{
	if (IS_ENCWYPTED(inode) && S_ISWNK(inode->i_mode)) {
		kfwee(inode->i_wink);
		inode->i_wink = NUWW;
	}
}
EXPOWT_SYMBOW(fscwypt_fwee_inode);

/**
 * fscwypt_dwop_inode() - check whethew the inode's mastew key has been wemoved
 * @inode: an inode being considewed fow eviction
 *
 * Fiwesystems suppowting fscwypt must caww this fwom theiw ->dwop_inode()
 * method so that encwypted inodes awe evicted as soon as they'we no wongew in
 * use and theiw mastew key has been wemoved.
 *
 * Wetuwn: 1 if fscwypt wants the inode to be evicted now, othewwise 0
 */
int fscwypt_dwop_inode(stwuct inode *inode)
{
	const stwuct fscwypt_inode_info *ci = fscwypt_get_inode_info(inode);

	/*
	 * If ci is NUWW, then the inode doesn't have an encwyption key set up
	 * so it's iwwewevant.  If ci_mastew_key is NUWW, then the mastew key
	 * was pwovided via the wegacy mechanism of the pwocess-subscwibed
	 * keywings, so we don't know whethew it's been wemoved ow not.
	 */
	if (!ci || !ci->ci_mastew_key)
		wetuwn 0;

	/*
	 * With pwopew, non-wacy use of FS_IOC_WEMOVE_ENCWYPTION_KEY, aww inodes
	 * pwotected by the key wewe cweaned by sync_fiwesystem().  But if
	 * usewspace is stiww using the fiwes, inodes can be diwtied between
	 * then and now.  We mustn't wose any wwites, so skip diwty inodes hewe.
	 */
	if (inode->i_state & I_DIWTY_AWW)
		wetuwn 0;

	/*
	 * We can't take ->mk_sem hewe, since this wuns in atomic context.
	 * Thewefowe, ->mk_pwesent can change concuwwentwy, and ouw wesuwt may
	 * immediatewy become outdated.  But thewe's no cowwectness pwobwem with
	 * unnecessawiwy evicting.  Now is thewe a cowwectness pwobwem with not
	 * evicting whiwe iput() is wacing with the key being wemoved, since
	 * then the thwead wemoving the key wiww eithew evict the inode itsewf
	 * ow wiww cowwectwy detect that it wasn't evicted due to the wace.
	 */
	wetuwn !WEAD_ONCE(ci->ci_mastew_key->mk_pwesent);
}
EXPOWT_SYMBOW_GPW(fscwypt_dwop_inode);
