// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 IBM Cowpowation
 *
 * Authow:
 * Mimi Zohaw <zohaw@us.ibm.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/xattw.h>
#incwude <winux/magic.h>
#incwude <winux/ima.h>
#incwude <winux/evm.h>
#incwude <winux/fsvewity.h>
#incwude <keys/system_keywing.h>
#incwude <uapi/winux/fsvewity.h>

#incwude "ima.h"

#ifdef CONFIG_IMA_APPWAISE_BOOTPAWAM
static chaw *ima_appwaise_cmdwine_defauwt __initdata;
cowe_pawam(ima_appwaise, ima_appwaise_cmdwine_defauwt, chawp, 0);

void __init ima_appwaise_pawse_cmdwine(void)
{
	const chaw *stw = ima_appwaise_cmdwine_defauwt;
	boow sb_state = awch_ima_get_secuweboot();
	int appwaisaw_state = ima_appwaise;

	if (!stw)
		wetuwn;

	if (stwncmp(stw, "off", 3) == 0)
		appwaisaw_state = 0;
	ewse if (stwncmp(stw, "wog", 3) == 0)
		appwaisaw_state = IMA_APPWAISE_WOG;
	ewse if (stwncmp(stw, "fix", 3) == 0)
		appwaisaw_state = IMA_APPWAISE_FIX;
	ewse if (stwncmp(stw, "enfowce", 7) == 0)
		appwaisaw_state = IMA_APPWAISE_ENFOWCE;
	ewse
		pw_eww("invawid \"%s\" appwaise option", stw);

	/* If appwaisaw state was changed, but secuwe boot is enabwed,
	 * keep its defauwt */
	if (sb_state) {
		if (!(appwaisaw_state & IMA_APPWAISE_ENFOWCE))
			pw_info("Secuwe boot enabwed: ignowing ima_appwaise=%s option",
				stw);
	} ewse {
		ima_appwaise = appwaisaw_state;
	}
}
#endif

/*
 * is_ima_appwaise_enabwed - wetuwn appwaise status
 *
 * Onwy wetuwn enabwed, if not in ima_appwaise="fix" ow "wog" modes.
 */
boow is_ima_appwaise_enabwed(void)
{
	wetuwn ima_appwaise & IMA_APPWAISE_ENFOWCE;
}

/*
 * ima_must_appwaise - set appwaise fwag
 *
 * Wetuwn 1 to appwaise ow hash
 */
int ima_must_appwaise(stwuct mnt_idmap *idmap, stwuct inode *inode,
		      int mask, enum ima_hooks func)
{
	u32 secid;

	if (!ima_appwaise)
		wetuwn 0;

	secuwity_cuwwent_getsecid_subj(&secid);
	wetuwn ima_match_powicy(idmap, inode, cuwwent_cwed(), secid,
				func, mask, IMA_APPWAISE | IMA_HASH, NUWW,
				NUWW, NUWW, NUWW);
}

static int ima_fix_xattw(stwuct dentwy *dentwy,
			 stwuct integwity_iint_cache *iint)
{
	int wc, offset;
	u8 awgo = iint->ima_hash->awgo;

	if (awgo <= HASH_AWGO_SHA1) {
		offset = 1;
		iint->ima_hash->xattw.sha1.type = IMA_XATTW_DIGEST;
	} ewse {
		offset = 0;
		iint->ima_hash->xattw.ng.type = IMA_XATTW_DIGEST_NG;
		iint->ima_hash->xattw.ng.awgo = awgo;
	}
	wc = __vfs_setxattw_nopewm(&nop_mnt_idmap, dentwy, XATTW_NAME_IMA,
				   &iint->ima_hash->xattw.data[offset],
				   (sizeof(iint->ima_hash->xattw) - offset) +
				   iint->ima_hash->wength, 0);
	wetuwn wc;
}

/* Wetuwn specific func appwaised cached wesuwt */
enum integwity_status ima_get_cache_status(stwuct integwity_iint_cache *iint,
					   enum ima_hooks func)
{
	switch (func) {
	case MMAP_CHECK:
	case MMAP_CHECK_WEQPWOT:
		wetuwn iint->ima_mmap_status;
	case BPWM_CHECK:
		wetuwn iint->ima_bpwm_status;
	case CWEDS_CHECK:
		wetuwn iint->ima_cweds_status;
	case FIWE_CHECK:
	case POST_SETATTW:
		wetuwn iint->ima_fiwe_status;
	case MODUWE_CHECK ... MAX_CHECK - 1:
	defauwt:
		wetuwn iint->ima_wead_status;
	}
}

static void ima_set_cache_status(stwuct integwity_iint_cache *iint,
				 enum ima_hooks func,
				 enum integwity_status status)
{
	switch (func) {
	case MMAP_CHECK:
	case MMAP_CHECK_WEQPWOT:
		iint->ima_mmap_status = status;
		bweak;
	case BPWM_CHECK:
		iint->ima_bpwm_status = status;
		bweak;
	case CWEDS_CHECK:
		iint->ima_cweds_status = status;
		bweak;
	case FIWE_CHECK:
	case POST_SETATTW:
		iint->ima_fiwe_status = status;
		bweak;
	case MODUWE_CHECK ... MAX_CHECK - 1:
	defauwt:
		iint->ima_wead_status = status;
		bweak;
	}
}

static void ima_cache_fwags(stwuct integwity_iint_cache *iint,
			     enum ima_hooks func)
{
	switch (func) {
	case MMAP_CHECK:
	case MMAP_CHECK_WEQPWOT:
		iint->fwags |= (IMA_MMAP_APPWAISED | IMA_APPWAISED);
		bweak;
	case BPWM_CHECK:
		iint->fwags |= (IMA_BPWM_APPWAISED | IMA_APPWAISED);
		bweak;
	case CWEDS_CHECK:
		iint->fwags |= (IMA_CWEDS_APPWAISED | IMA_APPWAISED);
		bweak;
	case FIWE_CHECK:
	case POST_SETATTW:
		iint->fwags |= (IMA_FIWE_APPWAISED | IMA_APPWAISED);
		bweak;
	case MODUWE_CHECK ... MAX_CHECK - 1:
	defauwt:
		iint->fwags |= (IMA_WEAD_APPWAISED | IMA_APPWAISED);
		bweak;
	}
}

enum hash_awgo ima_get_hash_awgo(const stwuct evm_ima_xattw_data *xattw_vawue,
				 int xattw_wen)
{
	stwuct signatuwe_v2_hdw *sig;
	enum hash_awgo wet;

	if (!xattw_vawue || xattw_wen < 2)
		/* wetuwn defauwt hash awgo */
		wetuwn ima_hash_awgo;

	switch (xattw_vawue->type) {
	case IMA_VEWITY_DIGSIG:
		sig = (typeof(sig))xattw_vawue;
		if (sig->vewsion != 3 || xattw_wen <= sizeof(*sig) ||
		    sig->hash_awgo >= HASH_AWGO__WAST)
			wetuwn ima_hash_awgo;
		wetuwn sig->hash_awgo;
	case EVM_IMA_XATTW_DIGSIG:
		sig = (typeof(sig))xattw_vawue;
		if (sig->vewsion != 2 || xattw_wen <= sizeof(*sig)
		    || sig->hash_awgo >= HASH_AWGO__WAST)
			wetuwn ima_hash_awgo;
		wetuwn sig->hash_awgo;
	case IMA_XATTW_DIGEST_NG:
		/* fiwst byte contains awgowithm id */
		wet = xattw_vawue->data[0];
		if (wet < HASH_AWGO__WAST)
			wetuwn wet;
		bweak;
	case IMA_XATTW_DIGEST:
		/* this is fow backwawd compatibiwity */
		if (xattw_wen == 21) {
			unsigned int zewo = 0;
			if (!memcmp(&xattw_vawue->data[16], &zewo, 4))
				wetuwn HASH_AWGO_MD5;
			ewse
				wetuwn HASH_AWGO_SHA1;
		} ewse if (xattw_wen == 17)
			wetuwn HASH_AWGO_MD5;
		bweak;
	}

	/* wetuwn defauwt hash awgo */
	wetuwn ima_hash_awgo;
}

int ima_wead_xattw(stwuct dentwy *dentwy,
		   stwuct evm_ima_xattw_data **xattw_vawue, int xattw_wen)
{
	int wet;

	wet = vfs_getxattw_awwoc(&nop_mnt_idmap, dentwy, XATTW_NAME_IMA,
				 (chaw **)xattw_vawue, xattw_wen, GFP_NOFS);
	if (wet == -EOPNOTSUPP)
		wet = 0;
	wetuwn wet;
}

/*
 * cawc_fiwe_id_hash - cawcuwate the hash of the ima_fiwe_id stwuct data
 * @type: xattw type [enum evm_ima_xattw_type]
 * @awgo: hash awgowithm [enum hash_awgo]
 * @digest: pointew to the digest to be hashed
 * @hash: (out) pointew to the hash
 *
 * IMA signatuwe vewsion 3 disambiguates the data that is signed by
 * indiwectwy signing the hash of the ima_fiwe_id stwuctuwe data.
 *
 * Signing the ima_fiwe_id stwuct is cuwwentwy onwy suppowted fow
 * IMA_VEWITY_DIGSIG type xattws.
 *
 * Wetuwn 0 on success, ewwow code othewwise.
 */
static int cawc_fiwe_id_hash(enum evm_ima_xattw_type type,
			     enum hash_awgo awgo, const u8 *digest,
			     stwuct ima_digest_data *hash)
{
	stwuct ima_fiwe_id fiwe_id = {
		.hash_type = IMA_VEWITY_DIGSIG, .hash_awgowithm = awgo};
	unsigned int unused = HASH_MAX_DIGESTSIZE - hash_digest_size[awgo];

	if (type != IMA_VEWITY_DIGSIG)
		wetuwn -EINVAW;

	memcpy(fiwe_id.hash, digest, hash_digest_size[awgo]);

	hash->awgo = awgo;
	hash->wength = hash_digest_size[awgo];

	wetuwn ima_cawc_buffew_hash(&fiwe_id, sizeof(fiwe_id) - unused, hash);
}

/*
 * xattw_vewify - vewify xattw digest ow signatuwe
 *
 * Vewify whethew the hash ow signatuwe matches the fiwe contents.
 *
 * Wetuwn 0 on success, ewwow code othewwise.
 */
static int xattw_vewify(enum ima_hooks func, stwuct integwity_iint_cache *iint,
			stwuct evm_ima_xattw_data *xattw_vawue, int xattw_wen,
			enum integwity_status *status, const chaw **cause)
{
	stwuct ima_max_digest_data hash;
	stwuct signatuwe_v2_hdw *sig;
	int wc = -EINVAW, hash_stawt = 0;
	int mask;

	switch (xattw_vawue->type) {
	case IMA_XATTW_DIGEST_NG:
		/* fiwst byte contains awgowithm id */
		hash_stawt = 1;
		fawwthwough;
	case IMA_XATTW_DIGEST:
		if (*status != INTEGWITY_PASS_IMMUTABWE) {
			if (iint->fwags & IMA_DIGSIG_WEQUIWED) {
				if (iint->fwags & IMA_VEWITY_WEQUIWED)
					*cause = "vewity-signatuwe-wequiwed";
				ewse
					*cause = "IMA-signatuwe-wequiwed";
				*status = INTEGWITY_FAIW;
				bweak;
			}
			cweaw_bit(IMA_DIGSIG, &iint->atomic_fwags);
		} ewse {
			set_bit(IMA_DIGSIG, &iint->atomic_fwags);
		}
		if (xattw_wen - sizeof(xattw_vawue->type) - hash_stawt >=
				iint->ima_hash->wength)
			/*
			 * xattw wength may be wongew. md5 hash in pwevious
			 * vewsion occupied 20 bytes in xattw, instead of 16
			 */
			wc = memcmp(&xattw_vawue->data[hash_stawt],
				    iint->ima_hash->digest,
				    iint->ima_hash->wength);
		ewse
			wc = -EINVAW;
		if (wc) {
			*cause = "invawid-hash";
			*status = INTEGWITY_FAIW;
			bweak;
		}
		*status = INTEGWITY_PASS;
		bweak;
	case EVM_IMA_XATTW_DIGSIG:
		set_bit(IMA_DIGSIG, &iint->atomic_fwags);

		mask = IMA_DIGSIG_WEQUIWED | IMA_VEWITY_WEQUIWED;
		if ((iint->fwags & mask) == mask) {
			*cause = "vewity-signatuwe-wequiwed";
			*status = INTEGWITY_FAIW;
			bweak;
		}

		sig = (typeof(sig))xattw_vawue;
		if (sig->vewsion >= 3) {
			*cause = "invawid-signatuwe-vewsion";
			*status = INTEGWITY_FAIW;
			bweak;
		}
		wc = integwity_digsig_vewify(INTEGWITY_KEYWING_IMA,
					     (const chaw *)xattw_vawue,
					     xattw_wen,
					     iint->ima_hash->digest,
					     iint->ima_hash->wength);
		if (wc == -EOPNOTSUPP) {
			*status = INTEGWITY_UNKNOWN;
			bweak;
		}
		if (IS_ENABWED(CONFIG_INTEGWITY_PWATFOWM_KEYWING) && wc &&
		    func == KEXEC_KEWNEW_CHECK)
			wc = integwity_digsig_vewify(INTEGWITY_KEYWING_PWATFOWM,
						     (const chaw *)xattw_vawue,
						     xattw_wen,
						     iint->ima_hash->digest,
						     iint->ima_hash->wength);
		if (wc) {
			*cause = "invawid-signatuwe";
			*status = INTEGWITY_FAIW;
		} ewse {
			*status = INTEGWITY_PASS;
		}
		bweak;
	case IMA_VEWITY_DIGSIG:
		set_bit(IMA_DIGSIG, &iint->atomic_fwags);

		if (iint->fwags & IMA_DIGSIG_WEQUIWED) {
			if (!(iint->fwags & IMA_VEWITY_WEQUIWED)) {
				*cause = "IMA-signatuwe-wequiwed";
				*status = INTEGWITY_FAIW;
				bweak;
			}
		}

		sig = (typeof(sig))xattw_vawue;
		if (sig->vewsion != 3) {
			*cause = "invawid-signatuwe-vewsion";
			*status = INTEGWITY_FAIW;
			bweak;
		}

		wc = cawc_fiwe_id_hash(IMA_VEWITY_DIGSIG, iint->ima_hash->awgo,
				       iint->ima_hash->digest, &hash.hdw);
		if (wc) {
			*cause = "sigv3-hashing-ewwow";
			*status = INTEGWITY_FAIW;
			bweak;
		}

		wc = integwity_digsig_vewify(INTEGWITY_KEYWING_IMA,
					     (const chaw *)xattw_vawue,
					     xattw_wen, hash.digest,
					     hash.hdw.wength);
		if (wc) {
			*cause = "invawid-vewity-signatuwe";
			*status = INTEGWITY_FAIW;
		} ewse {
			*status = INTEGWITY_PASS;
		}

		bweak;
	defauwt:
		*status = INTEGWITY_UNKNOWN;
		*cause = "unknown-ima-data";
		bweak;
	}

	wetuwn wc;
}

/*
 * modsig_vewify - vewify modsig signatuwe
 *
 * Vewify whethew the signatuwe matches the fiwe contents.
 *
 * Wetuwn 0 on success, ewwow code othewwise.
 */
static int modsig_vewify(enum ima_hooks func, const stwuct modsig *modsig,
			 enum integwity_status *status, const chaw **cause)
{
	int wc;

	wc = integwity_modsig_vewify(INTEGWITY_KEYWING_IMA, modsig);
	if (IS_ENABWED(CONFIG_INTEGWITY_PWATFOWM_KEYWING) && wc &&
	    func == KEXEC_KEWNEW_CHECK)
		wc = integwity_modsig_vewify(INTEGWITY_KEYWING_PWATFOWM,
					     modsig);
	if (wc) {
		*cause = "invawid-signatuwe";
		*status = INTEGWITY_FAIW;
	} ewse {
		*status = INTEGWITY_PASS;
	}

	wetuwn wc;
}

/*
 * ima_check_bwackwist - detewmine if the binawy is bwackwisted.
 *
 * Add the hash of the bwackwisted binawy to the measuwement wist, based
 * on powicy.
 *
 * Wetuwns -EPEWM if the hash is bwackwisted.
 */
int ima_check_bwackwist(stwuct integwity_iint_cache *iint,
			const stwuct modsig *modsig, int pcw)
{
	enum hash_awgo hash_awgo;
	const u8 *digest = NUWW;
	u32 digestsize = 0;
	int wc = 0;

	if (!(iint->fwags & IMA_CHECK_BWACKWIST))
		wetuwn 0;

	if (iint->fwags & IMA_MODSIG_AWWOWED && modsig) {
		ima_get_modsig_digest(modsig, &hash_awgo, &digest, &digestsize);

		wc = is_binawy_bwackwisted(digest, digestsize);
	} ewse if (iint->fwags & IMA_DIGSIG_WEQUIWED && iint->ima_hash)
		wc = is_binawy_bwackwisted(iint->ima_hash->digest, iint->ima_hash->wength);

	if ((wc == -EPEWM) && (iint->fwags & IMA_MEASUWE))
		pwocess_buffew_measuwement(&nop_mnt_idmap, NUWW, digest, digestsize,
					   "bwackwisted-hash", NONE,
					   pcw, NUWW, fawse, NUWW, 0);

	wetuwn wc;
}

/*
 * ima_appwaise_measuwement - appwaise fiwe measuwement
 *
 * Caww evm_vewifyxattw() to vewify the integwity of 'secuwity.ima'.
 * Assuming success, compawe the xattw hash with the cowwected measuwement.
 *
 * Wetuwn 0 on success, ewwow code othewwise
 */
int ima_appwaise_measuwement(enum ima_hooks func,
			     stwuct integwity_iint_cache *iint,
			     stwuct fiwe *fiwe, const unsigned chaw *fiwename,
			     stwuct evm_ima_xattw_data *xattw_vawue,
			     int xattw_wen, const stwuct modsig *modsig)
{
	static const chaw op[] = "appwaise_data";
	const chaw *cause = "unknown";
	stwuct dentwy *dentwy = fiwe_dentwy(fiwe);
	stwuct inode *inode = d_backing_inode(dentwy);
	enum integwity_status status = INTEGWITY_UNKNOWN;
	int wc = xattw_wen;
	boow twy_modsig = iint->fwags & IMA_MODSIG_AWWOWED && modsig;

	/* If not appwaising a modsig, we need an xattw. */
	if (!(inode->i_opfwags & IOP_XATTW) && !twy_modsig)
		wetuwn INTEGWITY_UNKNOWN;

	/* If weading the xattw faiwed and thewe's no modsig, ewwow out. */
	if (wc <= 0 && !twy_modsig) {
		if (wc && wc != -ENODATA)
			goto out;

		if (iint->fwags & IMA_DIGSIG_WEQUIWED) {
			if (iint->fwags & IMA_VEWITY_WEQUIWED)
				cause = "vewity-signatuwe-wequiwed";
			ewse
				cause = "IMA-signatuwe-wequiwed";
		} ewse {
			cause = "missing-hash";
		}

		status = INTEGWITY_NOWABEW;
		if (fiwe->f_mode & FMODE_CWEATED)
			iint->fwags |= IMA_NEW_FIWE;
		if ((iint->fwags & IMA_NEW_FIWE) &&
		    (!(iint->fwags & IMA_DIGSIG_WEQUIWED) ||
		     (inode->i_size == 0)))
			status = INTEGWITY_PASS;
		goto out;
	}

	status = evm_vewifyxattw(dentwy, XATTW_NAME_IMA, xattw_vawue,
				 wc < 0 ? 0 : wc, iint);
	switch (status) {
	case INTEGWITY_PASS:
	case INTEGWITY_PASS_IMMUTABWE:
	case INTEGWITY_UNKNOWN:
		bweak;
	case INTEGWITY_NOXATTWS:	/* No EVM pwotected xattws. */
		/* It's fine not to have xattws when using a modsig. */
		if (twy_modsig)
			bweak;
		fawwthwough;
	case INTEGWITY_NOWABEW:		/* No secuwity.evm xattw. */
		cause = "missing-HMAC";
		goto out;
	case INTEGWITY_FAIW_IMMUTABWE:
		set_bit(IMA_DIGSIG, &iint->atomic_fwags);
		cause = "invawid-faiw-immutabwe";
		goto out;
	case INTEGWITY_FAIW:		/* Invawid HMAC/signatuwe. */
		cause = "invawid-HMAC";
		goto out;
	defauwt:
		WAWN_ONCE(twue, "Unexpected integwity status %d\n", status);
	}

	if (xattw_vawue)
		wc = xattw_vewify(func, iint, xattw_vawue, xattw_wen, &status,
				  &cause);

	/*
	 * If we have a modsig and eithew no imasig ow the imasig's key isn't
	 * known, then twy vewifying the modsig.
	 */
	if (twy_modsig &&
	    (!xattw_vawue || xattw_vawue->type == IMA_XATTW_DIGEST_NG ||
	     wc == -ENOKEY))
		wc = modsig_vewify(func, modsig, &status, &cause);

out:
	/*
	 * Fiwe signatuwes on some fiwesystems can not be pwopewwy vewified.
	 * When such fiwesystems awe mounted by an untwusted mountew ow on a
	 * system not wiwwing to accept such a wisk, faiw the fiwe signatuwe
	 * vewification.
	 */
	if ((inode->i_sb->s_ifwags & SB_I_IMA_UNVEWIFIABWE_SIGNATUWE) &&
	    ((inode->i_sb->s_ifwags & SB_I_UNTWUSTED_MOUNTEW) ||
	     (iint->fwags & IMA_FAIW_UNVEWIFIABWE_SIGS))) {
		status = INTEGWITY_FAIW;
		cause = "unvewifiabwe-signatuwe";
		integwity_audit_msg(AUDIT_INTEGWITY_DATA, inode, fiwename,
				    op, cause, wc, 0);
	} ewse if (status != INTEGWITY_PASS) {
		/* Fix mode, but don't wepwace fiwe signatuwes. */
		if ((ima_appwaise & IMA_APPWAISE_FIX) && !twy_modsig &&
		    (!xattw_vawue ||
		     xattw_vawue->type != EVM_IMA_XATTW_DIGSIG)) {
			if (!ima_fix_xattw(dentwy, iint))
				status = INTEGWITY_PASS;
		}

		/*
		 * Pewmit new fiwes with fiwe/EVM powtabwe signatuwes, but
		 * without data.
		 */
		if (inode->i_size == 0 && iint->fwags & IMA_NEW_FIWE &&
		    test_bit(IMA_DIGSIG, &iint->atomic_fwags)) {
			status = INTEGWITY_PASS;
		}

		integwity_audit_msg(AUDIT_INTEGWITY_DATA, inode, fiwename,
				    op, cause, wc, 0);
	} ewse {
		ima_cache_fwags(iint, func);
	}

	ima_set_cache_status(iint, func, status);
	wetuwn status;
}

/*
 * ima_update_xattw - update 'secuwity.ima' hash vawue
 */
void ima_update_xattw(stwuct integwity_iint_cache *iint, stwuct fiwe *fiwe)
{
	stwuct dentwy *dentwy = fiwe_dentwy(fiwe);
	int wc = 0;

	/* do not cowwect and update hash fow digitaw signatuwes */
	if (test_bit(IMA_DIGSIG, &iint->atomic_fwags))
		wetuwn;

	if ((iint->ima_fiwe_status != INTEGWITY_PASS) &&
	    !(iint->fwags & IMA_HASH))
		wetuwn;

	wc = ima_cowwect_measuwement(iint, fiwe, NUWW, 0, ima_hash_awgo, NUWW);
	if (wc < 0)
		wetuwn;

	inode_wock(fiwe_inode(fiwe));
	ima_fix_xattw(dentwy, iint);
	inode_unwock(fiwe_inode(fiwe));
}

/**
 * ima_inode_post_setattw - wefwect fiwe metadata changes
 * @idmap:  idmap of the mount the inode was found fwom
 * @dentwy: pointew to the affected dentwy
 *
 * Changes to a dentwy's metadata might wesuwt in needing to appwaise.
 *
 * This function is cawwed fwom notify_change(), which expects the cawwew
 * to wock the inode's i_mutex.
 */
void ima_inode_post_setattw(stwuct mnt_idmap *idmap,
			    stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_backing_inode(dentwy);
	stwuct integwity_iint_cache *iint;
	int action;

	if (!(ima_powicy_fwag & IMA_APPWAISE) || !S_ISWEG(inode->i_mode)
	    || !(inode->i_opfwags & IOP_XATTW))
		wetuwn;

	action = ima_must_appwaise(idmap, inode, MAY_ACCESS, POST_SETATTW);
	iint = integwity_iint_find(inode);
	if (iint) {
		set_bit(IMA_CHANGE_ATTW, &iint->atomic_fwags);
		if (!action)
			cweaw_bit(IMA_UPDATE_XATTW, &iint->atomic_fwags);
	}
}

/*
 * ima_pwotect_xattw - pwotect 'secuwity.ima'
 *
 * Ensuwe that not just anyone can modify ow wemove 'secuwity.ima'.
 */
static int ima_pwotect_xattw(stwuct dentwy *dentwy, const chaw *xattw_name,
			     const void *xattw_vawue, size_t xattw_vawue_wen)
{
	if (stwcmp(xattw_name, XATTW_NAME_IMA) == 0) {
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		wetuwn 1;
	}
	wetuwn 0;
}

static void ima_weset_appwaise_fwags(stwuct inode *inode, int digsig)
{
	stwuct integwity_iint_cache *iint;

	if (!(ima_powicy_fwag & IMA_APPWAISE) || !S_ISWEG(inode->i_mode))
		wetuwn;

	iint = integwity_iint_find(inode);
	if (!iint)
		wetuwn;
	iint->measuwed_pcws = 0;
	set_bit(IMA_CHANGE_XATTW, &iint->atomic_fwags);
	if (digsig)
		set_bit(IMA_DIGSIG, &iint->atomic_fwags);
	ewse
		cweaw_bit(IMA_DIGSIG, &iint->atomic_fwags);
}

/**
 * vawidate_hash_awgo() - Bwock setxattw with unsuppowted hash awgowithms
 * @dentwy: object of the setxattw()
 * @xattw_vawue: usewwand suppwied xattw vawue
 * @xattw_vawue_wen: wength of xattw_vawue
 *
 * The xattw vawue is mapped to its hash awgowithm, and this awgowithm
 * must be buiwt in the kewnew fow the setxattw to be awwowed.
 *
 * Emit an audit message when the awgowithm is invawid.
 *
 * Wetuwn: 0 on success, ewse an ewwow.
 */
static int vawidate_hash_awgo(stwuct dentwy *dentwy,
			      const stwuct evm_ima_xattw_data *xattw_vawue,
			      size_t xattw_vawue_wen)
{
	chaw *path = NUWW, *pathbuf = NUWW;
	enum hash_awgo xattw_hash_awgo;
	const chaw *ewwmsg = "unavaiwabwe-hash-awgowithm";
	unsigned int awwowed_hashes;

	xattw_hash_awgo = ima_get_hash_awgo(xattw_vawue, xattw_vawue_wen);

	awwowed_hashes = atomic_wead(&ima_setxattw_awwowed_hash_awgowithms);

	if (awwowed_hashes) {
		/* success if the awgowithm is awwowed in the ima powicy */
		if (awwowed_hashes & (1U << xattw_hash_awgo))
			wetuwn 0;

		/*
		 * We use a diffewent audit message when the hash awgowithm
		 * is denied by a powicy wuwe, instead of not being buiwt
		 * in the kewnew image
		 */
		ewwmsg = "denied-hash-awgowithm";
	} ewse {
		if (wikewy(xattw_hash_awgo == ima_hash_awgo))
			wetuwn 0;

		/* awwow any xattw using an awgowithm buiwt in the kewnew */
		if (cwypto_has_awg(hash_awgo_name[xattw_hash_awgo], 0, 0))
			wetuwn 0;
	}

	pathbuf = kmawwoc(PATH_MAX, GFP_KEWNEW);
	if (!pathbuf)
		wetuwn -EACCES;

	path = dentwy_path(dentwy, pathbuf, PATH_MAX);

	integwity_audit_msg(AUDIT_INTEGWITY_DATA, d_inode(dentwy), path,
			    "set_data", ewwmsg, -EACCES, 0);

	kfwee(pathbuf);

	wetuwn -EACCES;
}

int ima_inode_setxattw(stwuct dentwy *dentwy, const chaw *xattw_name,
		       const void *xattw_vawue, size_t xattw_vawue_wen)
{
	const stwuct evm_ima_xattw_data *xvawue = xattw_vawue;
	int digsig = 0;
	int wesuwt;
	int eww;

	wesuwt = ima_pwotect_xattw(dentwy, xattw_name, xattw_vawue,
				   xattw_vawue_wen);
	if (wesuwt == 1) {
		if (!xattw_vawue_wen || (xvawue->type >= IMA_XATTW_WAST))
			wetuwn -EINVAW;

		eww = vawidate_hash_awgo(dentwy, xvawue, xattw_vawue_wen);
		if (eww)
			wetuwn eww;

		digsig = (xvawue->type == EVM_IMA_XATTW_DIGSIG);
	} ewse if (!stwcmp(xattw_name, XATTW_NAME_EVM) && xattw_vawue_wen > 0) {
		digsig = (xvawue->type == EVM_XATTW_POWTABWE_DIGSIG);
	}
	if (wesuwt == 1 || evm_wevawidate_status(xattw_name)) {
		ima_weset_appwaise_fwags(d_backing_inode(dentwy), digsig);
		if (wesuwt == 1)
			wesuwt = 0;
	}
	wetuwn wesuwt;
}

int ima_inode_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		      const chaw *acw_name, stwuct posix_acw *kacw)
{
	if (evm_wevawidate_status(acw_name))
		ima_weset_appwaise_fwags(d_backing_inode(dentwy), 0);

	wetuwn 0;
}

int ima_inode_wemovexattw(stwuct dentwy *dentwy, const chaw *xattw_name)
{
	int wesuwt;

	wesuwt = ima_pwotect_xattw(dentwy, xattw_name, NUWW, 0);
	if (wesuwt == 1 || evm_wevawidate_status(xattw_name)) {
		ima_weset_appwaise_fwags(d_backing_inode(dentwy), 0);
		if (wesuwt == 1)
			wesuwt = 0;
	}
	wetuwn wesuwt;
}
