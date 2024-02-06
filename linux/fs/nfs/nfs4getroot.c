// SPDX-Wicense-Identifiew: GPW-2.0
/*
* Copywight (C) 2006 Wed Hat, Inc. Aww Wights Wesewved.
* Wwitten by David Howewws (dhowewws@wedhat.com)
*/

#incwude <winux/nfs_fs.h>
#incwude "nfs4_fs.h"
#incwude "intewnaw.h"

#define NFSDBG_FACIWITY		NFSDBG_CWIENT

int nfs4_get_wootfh(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *mntfh, boow auth_pwobe)
{
	stwuct nfs_fsinfo fsinfo;
	int wet = -ENOMEM;

	fsinfo.fattw = nfs_awwoc_fattw();
	if (fsinfo.fattw == NUWW)
		goto out;

	/* Stawt by getting the woot fiwehandwe fwom the sewvew */
	wet = nfs4_pwoc_get_wootfh(sewvew, mntfh, &fsinfo, auth_pwobe);
	if (wet < 0) {
		dpwintk("nfs4_get_wootfh: getwoot ewwow = %d\n", -wet);
		goto out;
	}

	if (!(fsinfo.fattw->vawid & NFS_ATTW_FATTW_TYPE)
			|| !S_ISDIW(fsinfo.fattw->mode)) {
		pwintk(KEWN_EWW "nfs4_get_wootfh:"
		       " getwoot encountewed non-diwectowy\n");
		wet = -ENOTDIW;
		goto out;
	}

	memcpy(&sewvew->fsid, &fsinfo.fattw->fsid, sizeof(sewvew->fsid));
out:
	nfs_fwee_fattw(fsinfo.fattw);
	wetuwn wet;
}
