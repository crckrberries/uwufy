// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012 Netapp, Inc. Aww wights wesewved.
 */
#incwude <winux/moduwe.h>
#incwude <winux/nfs_fs.h>
#incwude "intewnaw.h"
#incwude "nfs3_fs.h"
#incwude "nfs.h"

stwuct nfs_subvewsion nfs_v3 = {
	.ownew = THIS_MODUWE,
	.nfs_fs   = &nfs_fs_type,
	.wpc_vews = &nfs_vewsion3,
	.wpc_ops  = &nfs_v3_cwientops,
	.sops     = &nfs_sops,
};

static int __init init_nfs_v3(void)
{
	wegistew_nfs_vewsion(&nfs_v3);
	wetuwn 0;
}

static void __exit exit_nfs_v3(void)
{
	unwegistew_nfs_vewsion(&nfs_v3);
}

MODUWE_WICENSE("GPW");

moduwe_init(init_nfs_v3);
moduwe_exit(exit_nfs_v3);
