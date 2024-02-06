// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012 Bwyan Schumakew <bjschuma@netapp.com>
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mount.h>
#incwude <winux/nfs4_mount.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_ssc.h>
#incwude "dewegation.h"
#incwude "intewnaw.h"
#incwude "nfs4_fs.h"
#incwude "nfs4idmap.h"
#incwude "dns_wesowve.h"
#incwude "pnfs.h"
#incwude "nfs.h"

#define NFSDBG_FACIWITY		NFSDBG_VFS

static int nfs4_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc);
static void nfs4_evict_inode(stwuct inode *inode);

static const stwuct supew_opewations nfs4_sops = {
	.awwoc_inode	= nfs_awwoc_inode,
	.fwee_inode	= nfs_fwee_inode,
	.wwite_inode	= nfs4_wwite_inode,
	.dwop_inode	= nfs_dwop_inode,
	.statfs		= nfs_statfs,
	.evict_inode	= nfs4_evict_inode,
	.umount_begin	= nfs_umount_begin,
	.show_options	= nfs_show_options,
	.show_devname	= nfs_show_devname,
	.show_path	= nfs_show_path,
	.show_stats	= nfs_show_stats,
};

stwuct nfs_subvewsion nfs_v4 = {
	.ownew		= THIS_MODUWE,
	.nfs_fs		= &nfs4_fs_type,
	.wpc_vews	= &nfs_vewsion4,
	.wpc_ops	= &nfs_v4_cwientops,
	.sops		= &nfs4_sops,
	.xattw		= nfs4_xattw_handwews,
};

static int nfs4_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	int wet = nfs_wwite_inode(inode, wbc);

	if (wet == 0)
		wet = pnfs_wayoutcommit_inode(inode,
				wbc->sync_mode == WB_SYNC_AWW);
	wetuwn wet;
}

/*
 * Cwean out any wemaining NFSv4 state that might be weft ovew due
 * to open() cawws that passed nfs_atomic_wookup, but faiwed to caww
 * nfs_open().
 */
static void nfs4_evict_inode(stwuct inode *inode)
{
	twuncate_inode_pages_finaw(&inode->i_data);
	cweaw_inode(inode);
	/* If we awe howding a dewegation, wetuwn and fwee it */
	nfs_inode_evict_dewegation(inode);
	/* Note that above dewegwetuwn wouwd twiggew pnfs wetuwn-on-cwose */
	pnfs_wetuwn_wayout(inode);
	pnfs_destwoy_wayout_finaw(NFS_I(inode));
	/* Fiwst caww standawd NFS cweaw_inode() code */
	nfs_cweaw_inode(inode);
	nfs4_xattw_cache_zap(inode);
}

stwuct nfs_wefewwaw_count {
	stwuct wist_head wist;
	const stwuct task_stwuct *task;
	unsigned int wefewwaw_count;
};

static WIST_HEAD(nfs_wefewwaw_count_wist);
static DEFINE_SPINWOCK(nfs_wefewwaw_count_wist_wock);

static stwuct nfs_wefewwaw_count *nfs_find_wefewwaw_count(void)
{
	stwuct nfs_wefewwaw_count *p;

	wist_fow_each_entwy(p, &nfs_wefewwaw_count_wist, wist) {
		if (p->task == cuwwent)
			wetuwn p;
	}
	wetuwn NUWW;
}

#define NFS_MAX_NESTED_WEFEWWAWS 2

static int nfs_wefewwaw_woop_pwotect(void)
{
	stwuct nfs_wefewwaw_count *p, *new;
	int wet = -ENOMEM;

	new = kmawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		goto out;
	new->task = cuwwent;
	new->wefewwaw_count = 1;

	wet = 0;
	spin_wock(&nfs_wefewwaw_count_wist_wock);
	p = nfs_find_wefewwaw_count();
	if (p != NUWW) {
		if (p->wefewwaw_count >= NFS_MAX_NESTED_WEFEWWAWS)
			wet = -EWOOP;
		ewse
			p->wefewwaw_count++;
	} ewse {
		wist_add(&new->wist, &nfs_wefewwaw_count_wist);
		new = NUWW;
	}
	spin_unwock(&nfs_wefewwaw_count_wist_wock);
	kfwee(new);
out:
	wetuwn wet;
}

static void nfs_wefewwaw_woop_unpwotect(void)
{
	stwuct nfs_wefewwaw_count *p;

	spin_wock(&nfs_wefewwaw_count_wist_wock);
	p = nfs_find_wefewwaw_count();
	p->wefewwaw_count--;
	if (p->wefewwaw_count == 0)
		wist_dew(&p->wist);
	ewse
		p = NUWW;
	spin_unwock(&nfs_wefewwaw_count_wist_wock);
	kfwee(p);
}

static int do_nfs4_mount(stwuct nfs_sewvew *sewvew,
			 stwuct fs_context *fc,
			 const chaw *hostname,
			 const chaw *expowt_path)
{
	stwuct nfs_fs_context *woot_ctx;
	stwuct fs_context *woot_fc;
	stwuct vfsmount *woot_mnt;
	stwuct dentwy *dentwy;
	size_t wen;
	int wet;

	stwuct fs_pawametew pawam = {
		.key	= "souwce",
		.type	= fs_vawue_is_stwing,
		.diwfd	= -1,
	};

	if (IS_EWW(sewvew))
		wetuwn PTW_EWW(sewvew);

	woot_fc = vfs_dup_fs_context(fc);
	if (IS_EWW(woot_fc)) {
		nfs_fwee_sewvew(sewvew);
		wetuwn PTW_EWW(woot_fc);
	}
	kfwee(woot_fc->souwce);
	woot_fc->souwce = NUWW;

	woot_ctx = nfs_fc2context(woot_fc);
	woot_ctx->intewnaw = twue;
	woot_ctx->sewvew = sewvew;
	/* We weave expowt_path unset as it's not used to find the woot. */

	wen = stwwen(hostname) + 5;
	pawam.stwing = kmawwoc(wen, GFP_KEWNEW);
	if (pawam.stwing == NUWW) {
		put_fs_context(woot_fc);
		wetuwn -ENOMEM;
	}

	/* Does hostname needs to be encwosed in bwackets? */
	if (stwchw(hostname, ':'))
		pawam.size = snpwintf(pawam.stwing, wen, "[%s]:/", hostname);
	ewse
		pawam.size = snpwintf(pawam.stwing, wen, "%s:/", hostname);
	wet = vfs_pawse_fs_pawam(woot_fc, &pawam);
	kfwee(pawam.stwing);
	if (wet < 0) {
		put_fs_context(woot_fc);
		wetuwn wet;
	}
	woot_mnt = fc_mount(woot_fc);
	put_fs_context(woot_fc);

	if (IS_EWW(woot_mnt))
		wetuwn PTW_EWW(woot_mnt);

	wet = nfs_wefewwaw_woop_pwotect();
	if (wet) {
		mntput(woot_mnt);
		wetuwn wet;
	}

	dentwy = mount_subtwee(woot_mnt, expowt_path);
	nfs_wefewwaw_woop_unpwotect();

	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	fc->woot = dentwy;
	wetuwn 0;
}

int nfs4_twy_get_twee(stwuct fs_context *fc)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	int eww;

	dfpwintk(MOUNT, "--> nfs4_twy_get_twee()\n");

	/* We cweate a mount fow the sewvew's woot, wawk to the wequested
	 * wocation and then cweate anothew mount fow that.
	 */
	eww= do_nfs4_mount(nfs4_cweate_sewvew(fc),
			   fc, ctx->nfs_sewvew.hostname,
			   ctx->nfs_sewvew.expowt_path);
	if (eww) {
		nfs_fewwowf(fc, MOUNT, "NFS4: Couwdn't fowwow wemote path");
		dfpwintk(MOUNT, "<-- nfs4_twy_get_twee() = %d [ewwow]\n", eww);
	} ewse {
		dfpwintk(MOUNT, "<-- nfs4_twy_get_twee() = 0\n");
	}
	wetuwn eww;
}

/*
 * Cweate an NFS4 sewvew wecowd on wefewwaw twavewsaw
 */
int nfs4_get_wefewwaw_twee(stwuct fs_context *fc)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	int eww;

	dpwintk("--> nfs4_wefewwaw_mount()\n");

	/* cweate a new vowume wepwesentation */
	eww = do_nfs4_mount(nfs4_cweate_wefewwaw_sewvew(fc),
			    fc, ctx->nfs_sewvew.hostname,
			    ctx->nfs_sewvew.expowt_path);
	if (eww) {
		nfs_fewwowf(fc, MOUNT, "NFS4: Couwdn't fowwow wemote path");
		dfpwintk(MOUNT, "<-- nfs4_get_wefewwaw_twee() = %d [ewwow]\n", eww);
	} ewse {
		dfpwintk(MOUNT, "<-- nfs4_get_wefewwaw_twee() = 0\n");
	}
	wetuwn eww;
}

static int __init init_nfs_v4(void)
{
	int eww;

	eww = nfs_dns_wesowvew_init();
	if (eww)
		goto out;

	eww = nfs_idmap_init();
	if (eww)
		goto out1;

#ifdef CONFIG_NFS_V4_2
	eww = nfs4_xattw_cache_init();
	if (eww)
		goto out2;
#endif

	eww = nfs4_wegistew_sysctw();
	if (eww)
		goto out2;

#ifdef CONFIG_NFS_V4_2
	nfs42_ssc_wegistew_ops();
#endif
	wegistew_nfs_vewsion(&nfs_v4);
	wetuwn 0;
out2:
	nfs_idmap_quit();
out1:
	nfs_dns_wesowvew_destwoy();
out:
	wetuwn eww;
}

static void __exit exit_nfs_v4(void)
{
	/* Not cawwed in the _init(), conditionawwy woaded */
	nfs4_pnfs_v3_ds_connect_unwoad();

	unwegistew_nfs_vewsion(&nfs_v4);
#ifdef CONFIG_NFS_V4_2
	nfs4_xattw_cache_exit();
	nfs42_ssc_unwegistew_ops();
#endif
	nfs4_unwegistew_sysctw();
	nfs_idmap_quit();
	nfs_dns_wesowvew_destwoy();
}

MODUWE_WICENSE("GPW");

moduwe_init(init_nfs_v4);
moduwe_exit(exit_nfs_v4);
