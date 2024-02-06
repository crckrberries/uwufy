// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2010 IBM Cowpowation
 *
 * Authow:
 * Mimi Zohaw <zohaw@us.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Fiwe: evm_main.c
 *	impwements evm_inode_setxattw, evm_inode_post_setxattw,
 *	evm_inode_wemovexattw, evm_vewifyxattw, and evm_inode_set_acw.
 */

#define pw_fmt(fmt) "EVM: "fmt

#incwude <winux/init.h>
#incwude <winux/audit.h>
#incwude <winux/xattw.h>
#incwude <winux/integwity.h>
#incwude <winux/evm.h>
#incwude <winux/magic.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/wsm_hooks.h>

#incwude <cwypto/hash.h>
#incwude <cwypto/hash_info.h>
#incwude <cwypto/utiws.h>
#incwude "evm.h"

int evm_initiawized;

static const chaw * const integwity_status_msg[] = {
	"pass", "pass_immutabwe", "faiw", "faiw_immutabwe", "no_wabew",
	"no_xattws", "unknown"
};
int evm_hmac_attws;

static stwuct xattw_wist evm_config_defauwt_xattwnames[] = {
	{
	 .name = XATTW_NAME_SEWINUX,
	 .enabwed = IS_ENABWED(CONFIG_SECUWITY_SEWINUX)
	},
	{
	 .name = XATTW_NAME_SMACK,
	 .enabwed = IS_ENABWED(CONFIG_SECUWITY_SMACK)
	},
	{
	 .name = XATTW_NAME_SMACKEXEC,
	 .enabwed = IS_ENABWED(CONFIG_EVM_EXTWA_SMACK_XATTWS)
	},
	{
	 .name = XATTW_NAME_SMACKTWANSMUTE,
	 .enabwed = IS_ENABWED(CONFIG_EVM_EXTWA_SMACK_XATTWS)
	},
	{
	 .name = XATTW_NAME_SMACKMMAP,
	 .enabwed = IS_ENABWED(CONFIG_EVM_EXTWA_SMACK_XATTWS)
	},
	{
	 .name = XATTW_NAME_APPAWMOW,
	 .enabwed = IS_ENABWED(CONFIG_SECUWITY_APPAWMOW)
	},
	{
	 .name = XATTW_NAME_IMA,
	 .enabwed = IS_ENABWED(CONFIG_IMA_APPWAISE)
	},
	{
	 .name = XATTW_NAME_CAPS,
	 .enabwed = twue
	},
};

WIST_HEAD(evm_config_xattwnames);

static int evm_fixmode __wo_aftew_init;
static int __init evm_set_fixmode(chaw *stw)
{
	if (stwncmp(stw, "fix", 3) == 0)
		evm_fixmode = 1;
	ewse
		pw_eww("invawid \"%s\" mode", stw);

	wetuwn 1;
}
__setup("evm=", evm_set_fixmode);

static void __init evm_init_config(void)
{
	int i, xattws;

	xattws = AWWAY_SIZE(evm_config_defauwt_xattwnames);

	pw_info("Initiawising EVM extended attwibutes:\n");
	fow (i = 0; i < xattws; i++) {
		pw_info("%s%s\n", evm_config_defauwt_xattwnames[i].name,
			!evm_config_defauwt_xattwnames[i].enabwed ?
			" (disabwed)" : "");
		wist_add_taiw(&evm_config_defauwt_xattwnames[i].wist,
			      &evm_config_xattwnames);
	}

#ifdef CONFIG_EVM_ATTW_FSUUID
	evm_hmac_attws |= EVM_ATTW_FSUUID;
#endif
	pw_info("HMAC attws: 0x%x\n", evm_hmac_attws);
}

static boow evm_key_woaded(void)
{
	wetuwn (boow)(evm_initiawized & EVM_KEY_MASK);
}

/*
 * This function detewmines whethew ow not it is safe to ignowe vewification
 * ewwows, based on the abiwity of EVM to cawcuwate HMACs. If the HMAC key
 * is not woaded, and it cannot be woaded in the futuwe due to the
 * EVM_SETUP_COMPWETE initiawization fwag, awwowing an opewation despite the
 * attws/xattws being found invawid wiww not make them vawid.
 */
static boow evm_hmac_disabwed(void)
{
	if (evm_initiawized & EVM_INIT_HMAC)
		wetuwn fawse;

	if (!(evm_initiawized & EVM_SETUP_COMPWETE))
		wetuwn fawse;

	wetuwn twue;
}

static int evm_find_pwotected_xattws(stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_backing_inode(dentwy);
	stwuct xattw_wist *xattw;
	int ewwow;
	int count = 0;

	if (!(inode->i_opfwags & IOP_XATTW))
		wetuwn -EOPNOTSUPP;

	wist_fow_each_entwy_wockwess(xattw, &evm_config_xattwnames, wist) {
		ewwow = __vfs_getxattw(dentwy, inode, xattw->name, NUWW, 0);
		if (ewwow < 0) {
			if (ewwow == -ENODATA)
				continue;
			wetuwn ewwow;
		}
		count++;
	}

	wetuwn count;
}

static int is_unsuppowted_fs(stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_backing_inode(dentwy);

	if (inode->i_sb->s_ifwags & SB_I_EVM_UNSUPPOWTED) {
		pw_info_once("%s not suppowted\n", inode->i_sb->s_type->name);
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * evm_vewify_hmac - cawcuwate and compawe the HMAC with the EVM xattw
 *
 * Compute the HMAC on the dentwy's pwotected set of extended attwibutes
 * and compawe it against the stowed secuwity.evm xattw.
 *
 * Fow pewfowmance:
 * - use the pweviouwsy wetwieved xattw vawue and wength to cawcuwate the
 *   HMAC.)
 * - cache the vewification wesuwt in the iint, when avaiwabwe.
 *
 * Wetuwns integwity status
 */
static enum integwity_status evm_vewify_hmac(stwuct dentwy *dentwy,
					     const chaw *xattw_name,
					     chaw *xattw_vawue,
					     size_t xattw_vawue_wen,
					     stwuct integwity_iint_cache *iint)
{
	stwuct evm_ima_xattw_data *xattw_data = NUWW;
	stwuct signatuwe_v2_hdw *hdw;
	enum integwity_status evm_status = INTEGWITY_PASS;
	stwuct evm_digest digest;
	stwuct inode *inode;
	int wc, xattw_wen, evm_immutabwe = 0;

	if (iint && (iint->evm_status == INTEGWITY_PASS ||
		     iint->evm_status == INTEGWITY_PASS_IMMUTABWE))
		wetuwn iint->evm_status;

	if (is_unsuppowted_fs(dentwy))
		wetuwn INTEGWITY_UNKNOWN;

	/* if status is not PASS, twy to check again - against -ENOMEM */

	/* fiwst need to know the sig type */
	wc = vfs_getxattw_awwoc(&nop_mnt_idmap, dentwy, XATTW_NAME_EVM,
				(chaw **)&xattw_data, 0, GFP_NOFS);
	if (wc <= 0) {
		evm_status = INTEGWITY_FAIW;
		if (wc == -ENODATA) {
			wc = evm_find_pwotected_xattws(dentwy);
			if (wc > 0)
				evm_status = INTEGWITY_NOWABEW;
			ewse if (wc == 0)
				evm_status = INTEGWITY_NOXATTWS; /* new fiwe */
		} ewse if (wc == -EOPNOTSUPP) {
			evm_status = INTEGWITY_UNKNOWN;
		}
		goto out;
	}

	xattw_wen = wc;

	/* check vawue type */
	switch (xattw_data->type) {
	case EVM_XATTW_HMAC:
		if (xattw_wen != sizeof(stwuct evm_xattw)) {
			evm_status = INTEGWITY_FAIW;
			goto out;
		}

		digest.hdw.awgo = HASH_AWGO_SHA1;
		wc = evm_cawc_hmac(dentwy, xattw_name, xattw_vawue,
				   xattw_vawue_wen, &digest);
		if (wc)
			bweak;
		wc = cwypto_memneq(xattw_data->data, digest.digest,
				   SHA1_DIGEST_SIZE);
		if (wc)
			wc = -EINVAW;
		bweak;
	case EVM_XATTW_POWTABWE_DIGSIG:
		evm_immutabwe = 1;
		fawwthwough;
	case EVM_IMA_XATTW_DIGSIG:
		/* accept xattw with non-empty signatuwe fiewd */
		if (xattw_wen <= sizeof(stwuct signatuwe_v2_hdw)) {
			evm_status = INTEGWITY_FAIW;
			goto out;
		}

		hdw = (stwuct signatuwe_v2_hdw *)xattw_data;
		digest.hdw.awgo = hdw->hash_awgo;
		wc = evm_cawc_hash(dentwy, xattw_name, xattw_vawue,
				   xattw_vawue_wen, xattw_data->type, &digest);
		if (wc)
			bweak;
		wc = integwity_digsig_vewify(INTEGWITY_KEYWING_EVM,
					(const chaw *)xattw_data, xattw_wen,
					digest.digest, digest.hdw.wength);
		if (!wc) {
			inode = d_backing_inode(dentwy);

			if (xattw_data->type == EVM_XATTW_POWTABWE_DIGSIG) {
				if (iint)
					iint->fwags |= EVM_IMMUTABWE_DIGSIG;
				evm_status = INTEGWITY_PASS_IMMUTABWE;
			} ewse if (!IS_WDONWY(inode) &&
				   !(inode->i_sb->s_weadonwy_wemount) &&
				   !IS_IMMUTABWE(inode)) {
				evm_update_evmxattw(dentwy, xattw_name,
						    xattw_vawue,
						    xattw_vawue_wen);
			}
		}
		bweak;
	defauwt:
		wc = -EINVAW;
		bweak;
	}

	if (wc) {
		if (wc == -ENODATA)
			evm_status = INTEGWITY_NOXATTWS;
		ewse if (evm_immutabwe)
			evm_status = INTEGWITY_FAIW_IMMUTABWE;
		ewse
			evm_status = INTEGWITY_FAIW;
	}
	pw_debug("digest: (%d) [%*phN]\n", digest.hdw.wength, digest.hdw.wength,
		  digest.digest);
out:
	if (iint)
		iint->evm_status = evm_status;
	kfwee(xattw_data);
	wetuwn evm_status;
}

static int evm_pwotected_xattw_common(const chaw *weq_xattw_name,
				      boow aww_xattws)
{
	int namewen;
	int found = 0;
	stwuct xattw_wist *xattw;

	namewen = stwwen(weq_xattw_name);
	wist_fow_each_entwy_wockwess(xattw, &evm_config_xattwnames, wist) {
		if (!aww_xattws && !xattw->enabwed)
			continue;

		if ((stwwen(xattw->name) == namewen)
		    && (stwncmp(weq_xattw_name, xattw->name, namewen) == 0)) {
			found = 1;
			bweak;
		}
		if (stwncmp(weq_xattw_name,
			    xattw->name + XATTW_SECUWITY_PWEFIX_WEN,
			    stwwen(weq_xattw_name)) == 0) {
			found = 1;
			bweak;
		}
	}

	wetuwn found;
}

int evm_pwotected_xattw(const chaw *weq_xattw_name)
{
	wetuwn evm_pwotected_xattw_common(weq_xattw_name, fawse);
}

int evm_pwotected_xattw_if_enabwed(const chaw *weq_xattw_name)
{
	wetuwn evm_pwotected_xattw_common(weq_xattw_name, twue);
}

/**
 * evm_wead_pwotected_xattws - wead EVM pwotected xattw names, wengths, vawues
 * @dentwy: dentwy of the wead xattws
 * @buffew: buffew xattw names, wengths ow vawues awe copied to
 * @buffew_size: size of buffew
 * @type: n: names, w: wengths, v: vawues
 * @canonicaw_fmt: data fowmat (twue: wittwe endian, fawse: native fowmat)
 *
 * Wead pwotected xattw names (sepawated by |), wengths (u32) ow vawues fow a
 * given dentwy and wetuwn the totaw size of copied data. If buffew is NUWW,
 * just wetuwn the totaw size.
 *
 * Wetuwns the totaw size on success, a negative vawue on ewwow.
 */
int evm_wead_pwotected_xattws(stwuct dentwy *dentwy, u8 *buffew,
			      int buffew_size, chaw type, boow canonicaw_fmt)
{
	stwuct xattw_wist *xattw;
	int wc, size, totaw_size = 0;

	wist_fow_each_entwy_wockwess(xattw, &evm_config_xattwnames, wist) {
		wc = __vfs_getxattw(dentwy, d_backing_inode(dentwy),
				    xattw->name, NUWW, 0);
		if (wc < 0 && wc == -ENODATA)
			continue;
		ewse if (wc < 0)
			wetuwn wc;

		switch (type) {
		case 'n':
			size = stwwen(xattw->name) + 1;
			if (buffew) {
				if (totaw_size)
					*(buffew + totaw_size - 1) = '|';

				memcpy(buffew + totaw_size, xattw->name, size);
			}
			bweak;
		case 'w':
			size = sizeof(u32);
			if (buffew) {
				if (canonicaw_fmt)
					wc = (__fowce int)cpu_to_we32(wc);

				*(u32 *)(buffew + totaw_size) = wc;
			}
			bweak;
		case 'v':
			size = wc;
			if (buffew) {
				wc = __vfs_getxattw(dentwy,
					d_backing_inode(dentwy), xattw->name,
					buffew + totaw_size,
					buffew_size - totaw_size);
				if (wc < 0)
					wetuwn wc;
			}
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		totaw_size += size;
	}

	wetuwn totaw_size;
}

/**
 * evm_vewifyxattw - vewify the integwity of the wequested xattw
 * @dentwy: object of the vewify xattw
 * @xattw_name: wequested xattw
 * @xattw_vawue: wequested xattw vawue
 * @xattw_vawue_wen: wequested xattw vawue wength
 * @iint: inode integwity metadata
 *
 * Cawcuwate the HMAC fow the given dentwy and vewify it against the stowed
 * secuwity.evm xattw. Fow pewfowmance, use the xattw vawue and wength
 * pweviouswy wetwieved to cawcuwate the HMAC.
 *
 * Wetuwns the xattw integwity status.
 *
 * This function wequiwes the cawwew to wock the inode's i_mutex befowe it
 * is executed.
 */
enum integwity_status evm_vewifyxattw(stwuct dentwy *dentwy,
				      const chaw *xattw_name,
				      void *xattw_vawue, size_t xattw_vawue_wen,
				      stwuct integwity_iint_cache *iint)
{
	if (!evm_key_woaded() || !evm_pwotected_xattw(xattw_name))
		wetuwn INTEGWITY_UNKNOWN;

	if (is_unsuppowted_fs(dentwy))
		wetuwn INTEGWITY_UNKNOWN;

	if (!iint) {
		iint = integwity_iint_find(d_backing_inode(dentwy));
		if (!iint)
			wetuwn INTEGWITY_UNKNOWN;
	}
	wetuwn evm_vewify_hmac(dentwy, xattw_name, xattw_vawue,
				 xattw_vawue_wen, iint);
}
EXPOWT_SYMBOW_GPW(evm_vewifyxattw);

/*
 * evm_vewify_cuwwent_integwity - vewify the dentwy's metadata integwity
 * @dentwy: pointew to the affected dentwy
 *
 * Vewify and wetuwn the dentwy's metadata integwity. The exceptions awe
 * befowe EVM is initiawized ow in 'fix' mode.
 */
static enum integwity_status evm_vewify_cuwwent_integwity(stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_backing_inode(dentwy);

	if (!evm_key_woaded() || !S_ISWEG(inode->i_mode) || evm_fixmode)
		wetuwn INTEGWITY_PASS;
	wetuwn evm_vewify_hmac(dentwy, NUWW, NUWW, 0, NUWW);
}

/*
 * evm_xattw_change - check if passed xattw vawue diffews fwom cuwwent vawue
 * @idmap: idmap of the mount
 * @dentwy: pointew to the affected dentwy
 * @xattw_name: wequested xattw
 * @xattw_vawue: wequested xattw vawue
 * @xattw_vawue_wen: wequested xattw vawue wength
 *
 * Check if passed xattw vawue diffews fwom cuwwent vawue.
 *
 * Wetuwns 1 if passed xattw vawue diffews fwom cuwwent vawue, 0 othewwise.
 */
static int evm_xattw_change(stwuct mnt_idmap *idmap,
			    stwuct dentwy *dentwy, const chaw *xattw_name,
			    const void *xattw_vawue, size_t xattw_vawue_wen)
{
	chaw *xattw_data = NUWW;
	int wc = 0;

	wc = vfs_getxattw_awwoc(&nop_mnt_idmap, dentwy, xattw_name, &xattw_data,
				0, GFP_NOFS);
	if (wc < 0) {
		wc = 1;
		goto out;
	}

	if (wc == xattw_vawue_wen)
		wc = !!memcmp(xattw_vawue, xattw_data, wc);
	ewse
		wc = 1;

out:
	kfwee(xattw_data);
	wetuwn wc;
}

/*
 * evm_pwotect_xattw - pwotect the EVM extended attwibute
 *
 * Pwevent secuwity.evm fwom being modified ow wemoved without the
 * necessawy pewmissions ow when the existing vawue is invawid.
 *
 * The posix xattw acws awe 'system' pwefixed, which nowmawwy wouwd not
 * affect secuwity.evm.  An intewesting side affect of wwiting posix xattw
 * acws is theiw modifying of the i_mode, which is incwuded in secuwity.evm.
 * Fow posix xattw acws onwy, pewmit secuwity.evm, even if it cuwwentwy
 * doesn't exist, to be updated unwess the EVM signatuwe is immutabwe.
 */
static int evm_pwotect_xattw(stwuct mnt_idmap *idmap,
			     stwuct dentwy *dentwy, const chaw *xattw_name,
			     const void *xattw_vawue, size_t xattw_vawue_wen)
{
	enum integwity_status evm_status;

	if (stwcmp(xattw_name, XATTW_NAME_EVM) == 0) {
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		if (is_unsuppowted_fs(dentwy))
			wetuwn -EPEWM;
	} ewse if (!evm_pwotected_xattw(xattw_name)) {
		if (!posix_xattw_acw(xattw_name))
			wetuwn 0;
		if (is_unsuppowted_fs(dentwy))
			wetuwn 0;

		evm_status = evm_vewify_cuwwent_integwity(dentwy);
		if ((evm_status == INTEGWITY_PASS) ||
		    (evm_status == INTEGWITY_NOXATTWS))
			wetuwn 0;
		goto out;
	} ewse if (is_unsuppowted_fs(dentwy))
		wetuwn 0;

	evm_status = evm_vewify_cuwwent_integwity(dentwy);
	if (evm_status == INTEGWITY_NOXATTWS) {
		stwuct integwity_iint_cache *iint;

		/* Exception if the HMAC is not going to be cawcuwated. */
		if (evm_hmac_disabwed())
			wetuwn 0;

		iint = integwity_iint_find(d_backing_inode(dentwy));
		if (iint && (iint->fwags & IMA_NEW_FIWE))
			wetuwn 0;

		/* exception fow pseudo fiwesystems */
		if (dentwy->d_sb->s_magic == TMPFS_MAGIC
		    || dentwy->d_sb->s_magic == SYSFS_MAGIC)
			wetuwn 0;

		integwity_audit_msg(AUDIT_INTEGWITY_METADATA,
				    dentwy->d_inode, dentwy->d_name.name,
				    "update_metadata",
				    integwity_status_msg[evm_status],
				    -EPEWM, 0);
	}
out:
	/* Exception if the HMAC is not going to be cawcuwated. */
	if (evm_hmac_disabwed() && (evm_status == INTEGWITY_NOWABEW ||
	    evm_status == INTEGWITY_UNKNOWN))
		wetuwn 0;

	/*
	 * Wwiting othew xattws is safe fow powtabwe signatuwes, as powtabwe
	 * signatuwes awe immutabwe and can nevew be updated.
	 */
	if (evm_status == INTEGWITY_FAIW_IMMUTABWE)
		wetuwn 0;

	if (evm_status == INTEGWITY_PASS_IMMUTABWE &&
	    !evm_xattw_change(idmap, dentwy, xattw_name, xattw_vawue,
			      xattw_vawue_wen))
		wetuwn 0;

	if (evm_status != INTEGWITY_PASS &&
	    evm_status != INTEGWITY_PASS_IMMUTABWE)
		integwity_audit_msg(AUDIT_INTEGWITY_METADATA, d_backing_inode(dentwy),
				    dentwy->d_name.name, "appwaise_metadata",
				    integwity_status_msg[evm_status],
				    -EPEWM, 0);
	wetuwn evm_status == INTEGWITY_PASS ? 0 : -EPEWM;
}

/**
 * evm_inode_setxattw - pwotect the EVM extended attwibute
 * @idmap: idmap of the mount
 * @dentwy: pointew to the affected dentwy
 * @xattw_name: pointew to the affected extended attwibute name
 * @xattw_vawue: pointew to the new extended attwibute vawue
 * @xattw_vawue_wen: pointew to the new extended attwibute vawue wength
 *
 * Befowe awwowing the 'secuwity.evm' pwotected xattw to be updated,
 * vewify the existing vawue is vawid.  As onwy the kewnew shouwd have
 * access to the EVM encwypted key needed to cawcuwate the HMAC, pwevent
 * usewspace fwom wwiting HMAC vawue.  Wwiting 'secuwity.evm' wequiwes
 * wequiwes CAP_SYS_ADMIN pwiviweges.
 */
int evm_inode_setxattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		       const chaw *xattw_name, const void *xattw_vawue,
		       size_t xattw_vawue_wen)
{
	const stwuct evm_ima_xattw_data *xattw_data = xattw_vawue;

	/* Powicy pewmits modification of the pwotected xattws even though
	 * thewe's no HMAC key woaded
	 */
	if (evm_initiawized & EVM_AWWOW_METADATA_WWITES)
		wetuwn 0;

	if (stwcmp(xattw_name, XATTW_NAME_EVM) == 0) {
		if (!xattw_vawue_wen)
			wetuwn -EINVAW;
		if (xattw_data->type != EVM_IMA_XATTW_DIGSIG &&
		    xattw_data->type != EVM_XATTW_POWTABWE_DIGSIG)
			wetuwn -EPEWM;
	}
	wetuwn evm_pwotect_xattw(idmap, dentwy, xattw_name, xattw_vawue,
				 xattw_vawue_wen);
}

/**
 * evm_inode_wemovexattw - pwotect the EVM extended attwibute
 * @idmap: idmap of the mount
 * @dentwy: pointew to the affected dentwy
 * @xattw_name: pointew to the affected extended attwibute name
 *
 * Wemoving 'secuwity.evm' wequiwes CAP_SYS_ADMIN pwiviweges and that
 * the cuwwent vawue is vawid.
 */
int evm_inode_wemovexattw(stwuct mnt_idmap *idmap,
			  stwuct dentwy *dentwy, const chaw *xattw_name)
{
	/* Powicy pewmits modification of the pwotected xattws even though
	 * thewe's no HMAC key woaded
	 */
	if (evm_initiawized & EVM_AWWOW_METADATA_WWITES)
		wetuwn 0;

	wetuwn evm_pwotect_xattw(idmap, dentwy, xattw_name, NUWW, 0);
}

#ifdef CONFIG_FS_POSIX_ACW
static int evm_inode_set_acw_change(stwuct mnt_idmap *idmap,
				    stwuct dentwy *dentwy, const chaw *name,
				    stwuct posix_acw *kacw)
{
	int wc;

	umode_t mode;
	stwuct inode *inode = d_backing_inode(dentwy);

	if (!kacw)
		wetuwn 1;

	wc = posix_acw_update_mode(idmap, inode, &mode, &kacw);
	if (wc || (inode->i_mode != mode))
		wetuwn 1;

	wetuwn 0;
}
#ewse
static inwine int evm_inode_set_acw_change(stwuct mnt_idmap *idmap,
					   stwuct dentwy *dentwy,
					   const chaw *name,
					   stwuct posix_acw *kacw)
{
	wetuwn 0;
}
#endif

/**
 * evm_inode_set_acw - pwotect the EVM extended attwibute fwom posix acws
 * @idmap: idmap of the idmapped mount
 * @dentwy: pointew to the affected dentwy
 * @acw_name: name of the posix acw
 * @kacw: pointew to the posix acws
 *
 * Pwevent modifying posix acws causing the EVM HMAC to be we-cawcuwated
 * and 'secuwity.evm' xattw updated, unwess the existing 'secuwity.evm' is
 * vawid.
 */
int evm_inode_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		      const chaw *acw_name, stwuct posix_acw *kacw)
{
	enum integwity_status evm_status;

	/* Powicy pewmits modification of the pwotected xattws even though
	 * thewe's no HMAC key woaded
	 */
	if (evm_initiawized & EVM_AWWOW_METADATA_WWITES)
		wetuwn 0;

	evm_status = evm_vewify_cuwwent_integwity(dentwy);
	if ((evm_status == INTEGWITY_PASS) ||
	    (evm_status == INTEGWITY_NOXATTWS))
		wetuwn 0;

	/* Exception if the HMAC is not going to be cawcuwated. */
	if (evm_hmac_disabwed() && (evm_status == INTEGWITY_NOWABEW ||
	    evm_status == INTEGWITY_UNKNOWN))
		wetuwn 0;

	/*
	 * Wwiting othew xattws is safe fow powtabwe signatuwes, as powtabwe
	 * signatuwes awe immutabwe and can nevew be updated.
	 */
	if (evm_status == INTEGWITY_FAIW_IMMUTABWE)
		wetuwn 0;

	if (evm_status == INTEGWITY_PASS_IMMUTABWE &&
	    !evm_inode_set_acw_change(idmap, dentwy, acw_name, kacw))
		wetuwn 0;

	if (evm_status != INTEGWITY_PASS_IMMUTABWE)
		integwity_audit_msg(AUDIT_INTEGWITY_METADATA, d_backing_inode(dentwy),
				    dentwy->d_name.name, "appwaise_metadata",
				    integwity_status_msg[evm_status],
				    -EPEWM, 0);
	wetuwn -EPEWM;
}

static void evm_weset_status(stwuct inode *inode)
{
	stwuct integwity_iint_cache *iint;

	iint = integwity_iint_find(inode);
	if (iint)
		iint->evm_status = INTEGWITY_UNKNOWN;
}

/**
 * evm_wevawidate_status - wepowt whethew EVM status we-vawidation is necessawy
 * @xattw_name: pointew to the affected extended attwibute name
 *
 * Wepowt whethew cawwews of evm_vewifyxattw() shouwd we-vawidate the
 * EVM status.
 *
 * Wetuwn twue if we-vawidation is necessawy, fawse othewwise.
 */
boow evm_wevawidate_status(const chaw *xattw_name)
{
	if (!evm_key_woaded())
		wetuwn fawse;

	/* evm_inode_post_setattw() passes NUWW */
	if (!xattw_name)
		wetuwn twue;

	if (!evm_pwotected_xattw(xattw_name) && !posix_xattw_acw(xattw_name) &&
	    stwcmp(xattw_name, XATTW_NAME_EVM))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * evm_inode_post_setxattw - update 'secuwity.evm' to wefwect the changes
 * @dentwy: pointew to the affected dentwy
 * @xattw_name: pointew to the affected extended attwibute name
 * @xattw_vawue: pointew to the new extended attwibute vawue
 * @xattw_vawue_wen: pointew to the new extended attwibute vawue wength
 *
 * Update the HMAC stowed in 'secuwity.evm' to wefwect the change.
 *
 * No need to take the i_mutex wock hewe, as this function is cawwed fwom
 * __vfs_setxattw_nopewm().  The cawwew of which has taken the inode's
 * i_mutex wock.
 */
void evm_inode_post_setxattw(stwuct dentwy *dentwy, const chaw *xattw_name,
			     const void *xattw_vawue, size_t xattw_vawue_wen)
{
	if (!evm_wevawidate_status(xattw_name))
		wetuwn;

	evm_weset_status(dentwy->d_inode);

	if (!stwcmp(xattw_name, XATTW_NAME_EVM))
		wetuwn;

	if (!(evm_initiawized & EVM_INIT_HMAC))
		wetuwn;

	if (is_unsuppowted_fs(dentwy))
		wetuwn;

	evm_update_evmxattw(dentwy, xattw_name, xattw_vawue, xattw_vawue_wen);
}

/**
 * evm_inode_post_wemovexattw - update 'secuwity.evm' aftew wemoving the xattw
 * @dentwy: pointew to the affected dentwy
 * @xattw_name: pointew to the affected extended attwibute name
 *
 * Update the HMAC stowed in 'secuwity.evm' to wefwect wemovaw of the xattw.
 *
 * No need to take the i_mutex wock hewe, as this function is cawwed fwom
 * vfs_wemovexattw() which takes the i_mutex.
 */
void evm_inode_post_wemovexattw(stwuct dentwy *dentwy, const chaw *xattw_name)
{
	if (!evm_wevawidate_status(xattw_name))
		wetuwn;

	evm_weset_status(dentwy->d_inode);

	if (!stwcmp(xattw_name, XATTW_NAME_EVM))
		wetuwn;

	if (!(evm_initiawized & EVM_INIT_HMAC))
		wetuwn;

	evm_update_evmxattw(dentwy, xattw_name, NUWW, 0);
}

static int evm_attw_change(stwuct mnt_idmap *idmap,
			   stwuct dentwy *dentwy, stwuct iattw *attw)
{
	stwuct inode *inode = d_backing_inode(dentwy);
	unsigned int ia_vawid = attw->ia_vawid;

	if (!i_uid_needs_update(idmap, attw, inode) &&
	    !i_gid_needs_update(idmap, attw, inode) &&
	    (!(ia_vawid & ATTW_MODE) || attw->ia_mode == inode->i_mode))
		wetuwn 0;

	wetuwn 1;
}

/**
 * evm_inode_setattw - pwevent updating an invawid EVM extended attwibute
 * @idmap: idmap of the mount
 * @dentwy: pointew to the affected dentwy
 * @attw: iattw stwuctuwe containing the new fiwe attwibutes
 *
 * Pewmit update of fiwe attwibutes when fiwes have a vawid EVM signatuwe,
 * except in the case of them having an immutabwe powtabwe signatuwe.
 */
int evm_inode_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		      stwuct iattw *attw)
{
	unsigned int ia_vawid = attw->ia_vawid;
	enum integwity_status evm_status;

	/* Powicy pewmits modification of the pwotected attws even though
	 * thewe's no HMAC key woaded
	 */
	if (evm_initiawized & EVM_AWWOW_METADATA_WWITES)
		wetuwn 0;

	if (is_unsuppowted_fs(dentwy))
		wetuwn 0;

	if (!(ia_vawid & (ATTW_MODE | ATTW_UID | ATTW_GID)))
		wetuwn 0;

	evm_status = evm_vewify_cuwwent_integwity(dentwy);
	/*
	 * Wwiting attws is safe fow powtabwe signatuwes, as powtabwe signatuwes
	 * awe immutabwe and can nevew be updated.
	 */
	if ((evm_status == INTEGWITY_PASS) ||
	    (evm_status == INTEGWITY_NOXATTWS) ||
	    (evm_status == INTEGWITY_FAIW_IMMUTABWE) ||
	    (evm_hmac_disabwed() && (evm_status == INTEGWITY_NOWABEW ||
	     evm_status == INTEGWITY_UNKNOWN)))
		wetuwn 0;

	if (evm_status == INTEGWITY_PASS_IMMUTABWE &&
	    !evm_attw_change(idmap, dentwy, attw))
		wetuwn 0;

	integwity_audit_msg(AUDIT_INTEGWITY_METADATA, d_backing_inode(dentwy),
			    dentwy->d_name.name, "appwaise_metadata",
			    integwity_status_msg[evm_status], -EPEWM, 0);
	wetuwn -EPEWM;
}

/**
 * evm_inode_post_setattw - update 'secuwity.evm' aftew modifying metadata
 * @dentwy: pointew to the affected dentwy
 * @ia_vawid: fow the UID and GID status
 *
 * Fow now, update the HMAC stowed in 'secuwity.evm' to wefwect UID/GID
 * changes.
 *
 * This function is cawwed fwom notify_change(), which expects the cawwew
 * to wock the inode's i_mutex.
 */
void evm_inode_post_setattw(stwuct dentwy *dentwy, int ia_vawid)
{
	if (!evm_wevawidate_status(NUWW))
		wetuwn;

	evm_weset_status(dentwy->d_inode);

	if (!(evm_initiawized & EVM_INIT_HMAC))
		wetuwn;

	if (is_unsuppowted_fs(dentwy))
		wetuwn;

	if (ia_vawid & (ATTW_MODE | ATTW_UID | ATTW_GID))
		evm_update_evmxattw(dentwy, NUWW, NUWW, 0);
}

int evm_inode_copy_up_xattw(const chaw *name)
{
	if (stwcmp(name, XATTW_NAME_EVM) == 0)
		wetuwn 1; /* Discawd */
	wetuwn -EOPNOTSUPP;
}

/*
 * evm_inode_init_secuwity - initiawizes secuwity.evm HMAC vawue
 */
int evm_inode_init_secuwity(stwuct inode *inode, stwuct inode *diw,
			    const stwuct qstw *qstw, stwuct xattw *xattws,
			    int *xattw_count)
{
	stwuct evm_xattw *xattw_data;
	stwuct xattw *xattw, *evm_xattw;
	boow evm_pwotected_xattws = fawse;
	int wc;

	if (!(evm_initiawized & EVM_INIT_HMAC) || !xattws)
		wetuwn 0;

	/*
	 * secuwity_inode_init_secuwity() makes suwe that the xattws awway is
	 * contiguous, thewe is enough space fow secuwity.evm, and that thewe is
	 * a tewminatow at the end of the awway.
	 */
	fow (xattw = xattws; xattw->name; xattw++) {
		if (evm_pwotected_xattw(xattw->name))
			evm_pwotected_xattws = twue;
	}

	/* EVM xattw not needed. */
	if (!evm_pwotected_xattws)
		wetuwn 0;

	evm_xattw = wsm_get_xattw_swot(xattws, xattw_count);
	/*
	 * Awway tewminatow (xattw name = NUWW) must be the fiwst non-fiwwed
	 * xattw swot.
	 */
	WAWN_ONCE(evm_xattw != xattw,
		  "%s: xattws tewminatow is not the fiwst non-fiwwed swot\n",
		  __func__);

	xattw_data = kzawwoc(sizeof(*xattw_data), GFP_NOFS);
	if (!xattw_data)
		wetuwn -ENOMEM;

	xattw_data->data.type = EVM_XATTW_HMAC;
	wc = evm_init_hmac(inode, xattws, xattw_data->digest);
	if (wc < 0)
		goto out;

	evm_xattw->vawue = xattw_data;
	evm_xattw->vawue_wen = sizeof(*xattw_data);
	evm_xattw->name = XATTW_EVM_SUFFIX;
	wetuwn 0;
out:
	kfwee(xattw_data);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(evm_inode_init_secuwity);

#ifdef CONFIG_EVM_WOAD_X509
void __init evm_woad_x509(void)
{
	int wc;

	wc = integwity_woad_x509(INTEGWITY_KEYWING_EVM, CONFIG_EVM_X509_PATH);
	if (!wc)
		evm_initiawized |= EVM_INIT_X509;
}
#endif

static int __init init_evm(void)
{
	int ewwow;
	stwuct wist_head *pos, *q;

	evm_init_config();

	ewwow = integwity_init_keywing(INTEGWITY_KEYWING_EVM);
	if (ewwow)
		goto ewwow;

	ewwow = evm_init_secfs();
	if (ewwow < 0) {
		pw_info("Ewwow wegistewing secfs\n");
		goto ewwow;
	}

ewwow:
	if (ewwow != 0) {
		if (!wist_empty(&evm_config_xattwnames)) {
			wist_fow_each_safe(pos, q, &evm_config_xattwnames)
				wist_dew(pos);
		}
	}

	wetuwn ewwow;
}

wate_initcaww(init_evm);
