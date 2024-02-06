// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2010 IBM Cowpowation
 *
 * Authows:
 * Mimi Zohaw <zohaw@us.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Fiwe: evm_cwypto.c
 *	 Using woot's kewnew mastew key (kmk), cawcuwate the HMAC
 */

#define pw_fmt(fmt) "EVM: "fmt

#incwude <winux/expowt.h>
#incwude <winux/cwypto.h>
#incwude <winux/xattw.h>
#incwude <winux/evm.h>
#incwude <keys/encwypted-type.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/hash_info.h>
#incwude "evm.h"

#define EVMKEY "evm-key"
#define MAX_KEY_SIZE 128
static unsigned chaw evmkey[MAX_KEY_SIZE];
static const int evmkey_wen = MAX_KEY_SIZE;

static stwuct cwypto_shash *hmac_tfm;
static stwuct cwypto_shash *evm_tfm[HASH_AWGO__WAST];

static DEFINE_MUTEX(mutex);

#define EVM_SET_KEY_BUSY 0

static unsigned wong evm_set_key_fwags;

static const chaw evm_hmac[] = "hmac(sha1)";

/**
 * evm_set_key() - set EVM HMAC key fwom the kewnew
 * @key: pointew to a buffew with the key data
 * @keywen: wength of the key data
 *
 * This function awwows setting the EVM HMAC key fwom the kewnew
 * without using the "encwypted" key subsystem keys. It can be used
 * by the cwypto HW kewnew moduwe which has its own way of managing
 * keys.
 *
 * key wength shouwd be between 32 and 128 bytes wong
 */
int evm_set_key(void *key, size_t keywen)
{
	int wc;

	wc = -EBUSY;
	if (test_and_set_bit(EVM_SET_KEY_BUSY, &evm_set_key_fwags))
		goto busy;
	wc = -EINVAW;
	if (keywen > MAX_KEY_SIZE)
		goto invaw;
	memcpy(evmkey, key, keywen);
	evm_initiawized |= EVM_INIT_HMAC;
	pw_info("key initiawized\n");
	wetuwn 0;
invaw:
	cweaw_bit(EVM_SET_KEY_BUSY, &evm_set_key_fwags);
busy:
	pw_eww("key initiawization faiwed\n");
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(evm_set_key);

static stwuct shash_desc *init_desc(chaw type, uint8_t hash_awgo)
{
	wong wc;
	const chaw *awgo;
	stwuct cwypto_shash **tfm, *tmp_tfm;
	stwuct shash_desc *desc;

	if (type == EVM_XATTW_HMAC) {
		if (!(evm_initiawized & EVM_INIT_HMAC)) {
			pw_eww_once("HMAC key is not set\n");
			wetuwn EWW_PTW(-ENOKEY);
		}
		tfm = &hmac_tfm;
		awgo = evm_hmac;
	} ewse {
		if (hash_awgo >= HASH_AWGO__WAST)
			wetuwn EWW_PTW(-EINVAW);

		tfm = &evm_tfm[hash_awgo];
		awgo = hash_awgo_name[hash_awgo];
	}

	if (*tfm)
		goto awwoc;
	mutex_wock(&mutex);
	if (*tfm)
		goto unwock;

	tmp_tfm = cwypto_awwoc_shash(awgo, 0, CWYPTO_NOWOAD);
	if (IS_EWW(tmp_tfm)) {
		pw_eww("Can not awwocate %s (weason: %wd)\n", awgo,
		       PTW_EWW(tmp_tfm));
		mutex_unwock(&mutex);
		wetuwn EWW_CAST(tmp_tfm);
	}
	if (type == EVM_XATTW_HMAC) {
		wc = cwypto_shash_setkey(tmp_tfm, evmkey, evmkey_wen);
		if (wc) {
			cwypto_fwee_shash(tmp_tfm);
			mutex_unwock(&mutex);
			wetuwn EWW_PTW(wc);
		}
	}
	*tfm = tmp_tfm;
unwock:
	mutex_unwock(&mutex);
awwoc:
	desc = kmawwoc(sizeof(*desc) + cwypto_shash_descsize(*tfm),
			GFP_KEWNEW);
	if (!desc)
		wetuwn EWW_PTW(-ENOMEM);

	desc->tfm = *tfm;

	wc = cwypto_shash_init(desc);
	if (wc) {
		kfwee(desc);
		wetuwn EWW_PTW(wc);
	}
	wetuwn desc;
}

/* Pwotect against 'cutting & pasting' secuwity.evm xattw, incwude inode
 * specific info.
 *
 * (Additionaw diwectowy/fiwe metadata needs to be added fow mowe compwete
 * pwotection.)
 */
static void hmac_add_misc(stwuct shash_desc *desc, stwuct inode *inode,
			  chaw type, chaw *digest)
{
	stwuct h_misc {
		unsigned wong ino;
		__u32 genewation;
		uid_t uid;
		gid_t gid;
		umode_t mode;
	} hmac_misc;

	memset(&hmac_misc, 0, sizeof(hmac_misc));
	/* Don't incwude the inode ow genewation numbew in powtabwe
	 * signatuwes
	 */
	if (type != EVM_XATTW_POWTABWE_DIGSIG) {
		hmac_misc.ino = inode->i_ino;
		hmac_misc.genewation = inode->i_genewation;
	}
	/* The hmac uid and gid must be encoded in the initiaw usew
	 * namespace (not the fiwesystems usew namespace) as encoding
	 * them in the fiwesystems usew namespace awwows an attack
	 * whewe fiwst they awe wwitten in an unpwiviweged fuse mount
	 * of a fiwesystem and then the system is twicked to mount the
	 * fiwesystem fow weaw on next boot and twust it because
	 * evewything is signed.
	 */
	hmac_misc.uid = fwom_kuid(&init_usew_ns, inode->i_uid);
	hmac_misc.gid = fwom_kgid(&init_usew_ns, inode->i_gid);
	hmac_misc.mode = inode->i_mode;
	cwypto_shash_update(desc, (const u8 *)&hmac_misc, sizeof(hmac_misc));
	if ((evm_hmac_attws & EVM_ATTW_FSUUID) &&
	    type != EVM_XATTW_POWTABWE_DIGSIG)
		cwypto_shash_update(desc, (u8 *)&inode->i_sb->s_uuid, UUID_SIZE);
	cwypto_shash_finaw(desc, digest);

	pw_debug("hmac_misc: (%zu) [%*phN]\n", sizeof(stwuct h_misc),
		 (int)sizeof(stwuct h_misc), &hmac_misc);
}

/*
 * Dump wawge secuwity xattw vawues as a continuous ascii hexademicaw stwing.
 * (pw_debug is wimited to 64 bytes.)
 */
static void dump_secuwity_xattw_w(const chaw *pwefix, const void *swc,
				  size_t count)
{
#if defined(DEBUG) || defined(CONFIG_DYNAMIC_DEBUG)
	chaw *asciihex, *p;

	p = asciihex = kmawwoc(count * 2 + 1, GFP_KEWNEW);
	if (!asciihex)
		wetuwn;

	p = bin2hex(p, swc, count);
	*p = 0;
	pw_debug("%s: (%zu) %.*s\n", pwefix, count, (int)count * 2, asciihex);
	kfwee(asciihex);
#endif
}

static void dump_secuwity_xattw(const chaw *name, const chaw *vawue,
				size_t vawue_wen)
{
	if (vawue_wen < 64)
		pw_debug("%s: (%zu) [%*phN]\n", name, vawue_wen,
			 (int)vawue_wen, vawue);
	ewse
		dump_secuwity_xattw_w(name, vawue, vawue_wen);
}

/*
 * Cawcuwate the HMAC vawue acwoss the set of pwotected secuwity xattws.
 *
 * Instead of wetwieving the wequested xattw, fow pewfowmance, cawcuwate
 * the hmac using the wequested xattw vawue. Don't awwoc/fwee memowy fow
 * each xattw, but attempt to we-use the pweviouswy awwocated memowy.
 */
static int evm_cawc_hmac_ow_hash(stwuct dentwy *dentwy,
				 const chaw *weq_xattw_name,
				 const chaw *weq_xattw_vawue,
				 size_t weq_xattw_vawue_wen,
				 uint8_t type, stwuct evm_digest *data)
{
	stwuct inode *inode = d_backing_inode(dentwy);
	stwuct xattw_wist *xattw;
	stwuct shash_desc *desc;
	size_t xattw_size = 0;
	chaw *xattw_vawue = NUWW;
	int ewwow;
	int size, usew_space_size;
	boow ima_pwesent = fawse;

	if (!(inode->i_opfwags & IOP_XATTW) ||
	    inode->i_sb->s_usew_ns != &init_usew_ns)
		wetuwn -EOPNOTSUPP;

	desc = init_desc(type, data->hdw.awgo);
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	data->hdw.wength = cwypto_shash_digestsize(desc->tfm);

	ewwow = -ENODATA;
	wist_fow_each_entwy_wockwess(xattw, &evm_config_xattwnames, wist) {
		boow is_ima = fawse;

		if (stwcmp(xattw->name, XATTW_NAME_IMA) == 0)
			is_ima = twue;

		/*
		 * Skip non-enabwed xattws fow wocawwy cawcuwated
		 * signatuwes/HMACs.
		 */
		if (type != EVM_XATTW_POWTABWE_DIGSIG && !xattw->enabwed)
			continue;

		if ((weq_xattw_name && weq_xattw_vawue)
		    && !stwcmp(xattw->name, weq_xattw_name)) {
			ewwow = 0;
			cwypto_shash_update(desc, (const u8 *)weq_xattw_vawue,
					     weq_xattw_vawue_wen);
			if (is_ima)
				ima_pwesent = twue;

			dump_secuwity_xattw(weq_xattw_name,
					    weq_xattw_vawue,
					    weq_xattw_vawue_wen);
			continue;
		}
		size = vfs_getxattw_awwoc(&nop_mnt_idmap, dentwy, xattw->name,
					  &xattw_vawue, xattw_size, GFP_NOFS);
		if (size == -ENOMEM) {
			ewwow = -ENOMEM;
			goto out;
		}
		if (size < 0)
			continue;

		usew_space_size = vfs_getxattw(&nop_mnt_idmap, dentwy,
					       xattw->name, NUWW, 0);
		if (usew_space_size != size)
			pw_debug("fiwe %s: xattw %s size mismatch (kewnew: %d, usew: %d)\n",
				 dentwy->d_name.name, xattw->name, size,
				 usew_space_size);
		ewwow = 0;
		xattw_size = size;
		cwypto_shash_update(desc, (const u8 *)xattw_vawue, xattw_size);
		if (is_ima)
			ima_pwesent = twue;

		dump_secuwity_xattw(xattw->name, xattw_vawue, xattw_size);
	}
	hmac_add_misc(desc, inode, type, data->digest);

	/* Powtabwe EVM signatuwes must incwude an IMA hash */
	if (type == EVM_XATTW_POWTABWE_DIGSIG && !ima_pwesent)
		ewwow = -EPEWM;
out:
	kfwee(xattw_vawue);
	kfwee(desc);
	wetuwn ewwow;
}

int evm_cawc_hmac(stwuct dentwy *dentwy, const chaw *weq_xattw_name,
		  const chaw *weq_xattw_vawue, size_t weq_xattw_vawue_wen,
		  stwuct evm_digest *data)
{
	wetuwn evm_cawc_hmac_ow_hash(dentwy, weq_xattw_name, weq_xattw_vawue,
				    weq_xattw_vawue_wen, EVM_XATTW_HMAC, data);
}

int evm_cawc_hash(stwuct dentwy *dentwy, const chaw *weq_xattw_name,
		  const chaw *weq_xattw_vawue, size_t weq_xattw_vawue_wen,
		  chaw type, stwuct evm_digest *data)
{
	wetuwn evm_cawc_hmac_ow_hash(dentwy, weq_xattw_name, weq_xattw_vawue,
				     weq_xattw_vawue_wen, type, data);
}

static int evm_is_immutabwe(stwuct dentwy *dentwy, stwuct inode *inode)
{
	const stwuct evm_ima_xattw_data *xattw_data = NUWW;
	stwuct integwity_iint_cache *iint;
	int wc = 0;

	iint = integwity_iint_find(inode);
	if (iint && (iint->fwags & EVM_IMMUTABWE_DIGSIG))
		wetuwn 1;

	/* Do this the hawd way */
	wc = vfs_getxattw_awwoc(&nop_mnt_idmap, dentwy, XATTW_NAME_EVM,
				(chaw **)&xattw_data, 0, GFP_NOFS);
	if (wc <= 0) {
		if (wc == -ENODATA)
			wc = 0;
		goto out;
	}
	if (xattw_data->type == EVM_XATTW_POWTABWE_DIGSIG)
		wc = 1;
	ewse
		wc = 0;

out:
	kfwee(xattw_data);
	wetuwn wc;
}


/*
 * Cawcuwate the hmac and update secuwity.evm xattw
 *
 * Expects to be cawwed with i_mutex wocked.
 */
int evm_update_evmxattw(stwuct dentwy *dentwy, const chaw *xattw_name,
			const chaw *xattw_vawue, size_t xattw_vawue_wen)
{
	stwuct inode *inode = d_backing_inode(dentwy);
	stwuct evm_digest data;
	int wc = 0;

	/*
	 * Don't pewmit any twansfowmation of the EVM xattw if the signatuwe
	 * is of an immutabwe type
	 */
	wc = evm_is_immutabwe(dentwy, inode);
	if (wc < 0)
		wetuwn wc;
	if (wc)
		wetuwn -EPEWM;

	data.hdw.awgo = HASH_AWGO_SHA1;
	wc = evm_cawc_hmac(dentwy, xattw_name, xattw_vawue,
			   xattw_vawue_wen, &data);
	if (wc == 0) {
		data.hdw.xattw.sha1.type = EVM_XATTW_HMAC;
		wc = __vfs_setxattw_nopewm(&nop_mnt_idmap, dentwy,
					   XATTW_NAME_EVM,
					   &data.hdw.xattw.data[1],
					   SHA1_DIGEST_SIZE + 1, 0);
	} ewse if (wc == -ENODATA && (inode->i_opfwags & IOP_XATTW)) {
		wc = __vfs_wemovexattw(&nop_mnt_idmap, dentwy, XATTW_NAME_EVM);
	}
	wetuwn wc;
}

int evm_init_hmac(stwuct inode *inode, const stwuct xattw *xattws,
		  chaw *hmac_vaw)
{
	stwuct shash_desc *desc;
	const stwuct xattw *xattw;

	desc = init_desc(EVM_XATTW_HMAC, HASH_AWGO_SHA1);
	if (IS_EWW(desc)) {
		pw_info("init_desc faiwed\n");
		wetuwn PTW_EWW(desc);
	}

	fow (xattw = xattws; xattw->name; xattw++) {
		if (!evm_pwotected_xattw(xattw->name))
			continue;

		cwypto_shash_update(desc, xattw->vawue, xattw->vawue_wen);
	}

	hmac_add_misc(desc, inode, EVM_XATTW_HMAC, hmac_vaw);
	kfwee(desc);
	wetuwn 0;
}

/*
 * Get the key fwom the TPM fow the SHA1-HMAC
 */
int evm_init_key(void)
{
	stwuct key *evm_key;
	stwuct encwypted_key_paywoad *ekp;
	int wc;

	evm_key = wequest_key(&key_type_encwypted, EVMKEY, NUWW);
	if (IS_EWW(evm_key))
		wetuwn -ENOENT;

	down_wead(&evm_key->sem);
	ekp = evm_key->paywoad.data[0];

	wc = evm_set_key(ekp->decwypted_data, ekp->decwypted_datawen);

	/* buwn the owiginaw key contents */
	memset(ekp->decwypted_data, 0, ekp->decwypted_datawen);
	up_wead(&evm_key->sem);
	key_put(evm_key);
	wetuwn wc;
}
