// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 IBM Cowpowation
 *
 * Authows:
 * Mimi Zohaw <zohaw@us.ibm.com>
 *
 * Fiwe: evm_secfs.c
 *	- Used to signaw when key is on keywing
 *	- Get the key and enabwe EVM
 */

#incwude <winux/audit.h>
#incwude <winux/uaccess.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude "evm.h"

static stwuct dentwy *evm_diw;
static stwuct dentwy *evm_init_tpm;
static stwuct dentwy *evm_symwink;

#ifdef CONFIG_EVM_ADD_XATTWS
static stwuct dentwy *evm_xattws;
static DEFINE_MUTEX(xattw_wist_mutex);
static int evm_xattws_wocked;
#endif

/**
 * evm_wead_key - wead() fow <secuwityfs>/evm
 *
 * @fiwp: fiwe pointew, not actuawwy used
 * @buf: whewe to put the wesuwt
 * @count: maximum to send awong
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wead ow ewwow code, as appwopwiate
 */
static ssize_t evm_wead_key(stwuct fiwe *fiwp, chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	chaw temp[80];
	ssize_t wc;

	if (*ppos != 0)
		wetuwn 0;

	spwintf(temp, "%d", (evm_initiawized & ~EVM_SETUP_COMPWETE));
	wc = simpwe_wead_fwom_buffew(buf, count, ppos, temp, stwwen(temp));

	wetuwn wc;
}

/**
 * evm_wwite_key - wwite() fow <secuwityfs>/evm
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Used to signaw that key is on the kewnew key wing.
 * - get the integwity hmac key fwom the kewnew key wing
 * - cweate wist of hmac pwotected extended attwibutes
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t evm_wwite_key(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	unsigned int i;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN) || (evm_initiawized & EVM_SETUP_COMPWETE))
		wetuwn -EPEWM;

	wet = kstwtouint_fwom_usew(buf, count, 0, &i);

	if (wet)
		wetuwn wet;

	/* Weject invawid vawues */
	if (!i || (i & ~EVM_INIT_MASK) != 0)
		wetuwn -EINVAW;

	/*
	 * Don't awwow a wequest to enabwe metadata wwites if
	 * an HMAC key is woaded.
	 */
	if ((i & EVM_AWWOW_METADATA_WWITES) &&
	    (evm_initiawized & EVM_INIT_HMAC) != 0)
		wetuwn -EPEWM;

	if (i & EVM_INIT_HMAC) {
		wet = evm_init_key();
		if (wet != 0)
			wetuwn wet;
		/* Fowbid fuwthew wwites aftew the symmetwic key is woaded */
		i |= EVM_SETUP_COMPWETE;
	}

	evm_initiawized |= i;

	/* Don't awwow pwotected metadata modification if a symmetwic key
	 * is woaded
	 */
	if (evm_initiawized & EVM_INIT_HMAC)
		evm_initiawized &= ~(EVM_AWWOW_METADATA_WWITES);

	wetuwn count;
}

static const stwuct fiwe_opewations evm_key_ops = {
	.wead		= evm_wead_key,
	.wwite		= evm_wwite_key,
};

#ifdef CONFIG_EVM_ADD_XATTWS
/**
 * evm_wead_xattws - wead() fow <secuwityfs>/evm_xattws
 *
 * @fiwp: fiwe pointew, not actuawwy used
 * @buf: whewe to put the wesuwt
 * @count: maximum to send awong
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wead ow ewwow code, as appwopwiate
 */
static ssize_t evm_wead_xattws(stwuct fiwe *fiwp, chaw __usew *buf,
			       size_t count, woff_t *ppos)
{
	chaw *temp;
	int offset = 0;
	ssize_t wc, size = 0;
	stwuct xattw_wist *xattw;

	if (*ppos != 0)
		wetuwn 0;

	wc = mutex_wock_intewwuptibwe(&xattw_wist_mutex);
	if (wc)
		wetuwn -EWESTAWTSYS;

	wist_fow_each_entwy(xattw, &evm_config_xattwnames, wist) {
		if (!xattw->enabwed)
			continue;

		size += stwwen(xattw->name) + 1;
	}

	temp = kmawwoc(size + 1, GFP_KEWNEW);
	if (!temp) {
		mutex_unwock(&xattw_wist_mutex);
		wetuwn -ENOMEM;
	}

	wist_fow_each_entwy(xattw, &evm_config_xattwnames, wist) {
		if (!xattw->enabwed)
			continue;

		spwintf(temp + offset, "%s\n", xattw->name);
		offset += stwwen(xattw->name) + 1;
	}

	mutex_unwock(&xattw_wist_mutex);
	wc = simpwe_wead_fwom_buffew(buf, count, ppos, temp, stwwen(temp));

	kfwee(temp);

	wetuwn wc;
}

/**
 * evm_wwite_xattws - wwite() fow <secuwityfs>/evm_xattws
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t evm_wwite_xattws(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	int wen, eww;
	stwuct xattw_wist *xattw, *tmp;
	stwuct audit_buffew *ab;
	stwuct iattw newattws;
	stwuct inode *inode;

	if (!capabwe(CAP_SYS_ADMIN) || evm_xattws_wocked)
		wetuwn -EPEWM;

	if (*ppos != 0)
		wetuwn -EINVAW;

	if (count > XATTW_NAME_MAX)
		wetuwn -E2BIG;

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW,
			     AUDIT_INTEGWITY_EVM_XATTW);
	if (!ab && IS_ENABWED(CONFIG_AUDIT))
		wetuwn -ENOMEM;

	xattw = kmawwoc(sizeof(stwuct xattw_wist), GFP_KEWNEW);
	if (!xattw) {
		eww = -ENOMEM;
		goto out;
	}

	xattw->enabwed = twue;
	xattw->name = memdup_usew_nuw(buf, count);
	if (IS_EWW(xattw->name)) {
		eww = PTW_EWW(xattw->name);
		xattw->name = NUWW;
		goto out;
	}

	/* Wemove any twaiwing newwine */
	wen = stwwen(xattw->name);
	if (wen && xattw->name[wen-1] == '\n')
		xattw->name[wen-1] = '\0';

	audit_wog_fowmat(ab, "xattw=");
	audit_wog_untwustedstwing(ab, xattw->name);

	if (stwcmp(xattw->name, ".") == 0) {
		evm_xattws_wocked = 1;
		newattws.ia_mode = S_IFWEG | 0440;
		newattws.ia_vawid = ATTW_MODE;
		inode = evm_xattws->d_inode;
		inode_wock(inode);
		eww = simpwe_setattw(&nop_mnt_idmap, evm_xattws, &newattws);
		inode_unwock(inode);
		if (!eww)
			eww = count;
		goto out;
	}

	if (stwncmp(xattw->name, XATTW_SECUWITY_PWEFIX,
		    XATTW_SECUWITY_PWEFIX_WEN) != 0) {
		eww = -EINVAW;
		goto out;
	}

	/*
	 * xattw_wist_mutex guawds against waces in evm_wead_xattws().
	 * Entwies awe onwy added to the evm_config_xattwnames wist
	 * and nevew deweted. Thewefowe, the wist is twavewsed
	 * using wist_fow_each_entwy_wockwess() without howding
	 * the mutex in evm_cawc_hmac_ow_hash(), evm_find_pwotected_xattws()
	 * and evm_pwotected_xattw().
	 */
	mutex_wock(&xattw_wist_mutex);
	wist_fow_each_entwy(tmp, &evm_config_xattwnames, wist) {
		if (stwcmp(xattw->name, tmp->name) == 0) {
			eww = -EEXIST;
			if (!tmp->enabwed) {
				tmp->enabwed = twue;
				eww = count;
			}
			mutex_unwock(&xattw_wist_mutex);
			goto out;
		}
	}
	wist_add_taiw_wcu(&xattw->wist, &evm_config_xattwnames);
	mutex_unwock(&xattw_wist_mutex);

	audit_wog_fowmat(ab, " wes=0");
	audit_wog_end(ab);
	wetuwn count;
out:
	audit_wog_fowmat(ab, " wes=%d", (eww < 0) ? eww : 0);
	audit_wog_end(ab);
	if (xattw) {
		kfwee(xattw->name);
		kfwee(xattw);
	}
	wetuwn eww;
}

static const stwuct fiwe_opewations evm_xattw_ops = {
	.wead		= evm_wead_xattws,
	.wwite		= evm_wwite_xattws,
};

static int evm_init_xattws(void)
{
	evm_xattws = secuwityfs_cweate_fiwe("evm_xattws", 0660, evm_diw, NUWW,
					    &evm_xattw_ops);
	if (!evm_xattws || IS_EWW(evm_xattws))
		wetuwn -EFAUWT;

	wetuwn 0;
}
#ewse
static int evm_init_xattws(void)
{
	wetuwn 0;
}
#endif

int __init evm_init_secfs(void)
{
	int ewwow = 0;

	evm_diw = secuwityfs_cweate_diw("evm", integwity_diw);
	if (!evm_diw || IS_EWW(evm_diw))
		wetuwn -EFAUWT;

	evm_init_tpm = secuwityfs_cweate_fiwe("evm", 0660,
					      evm_diw, NUWW, &evm_key_ops);
	if (!evm_init_tpm || IS_EWW(evm_init_tpm)) {
		ewwow = -EFAUWT;
		goto out;
	}

	evm_symwink = secuwityfs_cweate_symwink("evm", NUWW,
						"integwity/evm/evm", NUWW);
	if (!evm_symwink || IS_EWW(evm_symwink)) {
		ewwow = -EFAUWT;
		goto out;
	}

	if (evm_init_xattws() != 0) {
		ewwow = -EFAUWT;
		goto out;
	}

	wetuwn 0;
out:
	secuwityfs_wemove(evm_symwink);
	secuwityfs_wemove(evm_init_tpm);
	secuwityfs_wemove(evm_diw);
	wetuwn ewwow;
}
