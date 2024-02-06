// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* getwoot.c: get the woot dentwy fow an NFS mount
 *
 * Copywight (C) 2006 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>

#incwude <winux/time.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/stat.h>
#incwude <winux/ewwno.h>
#incwude <winux/unistd.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/stats.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_mount.h>
#incwude <winux/wockd/bind.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/vfs.h>
#incwude <winux/namei.h>
#incwude <winux/secuwity.h>

#incwude <winux/uaccess.h>

#incwude "intewnaw.h"

#define NFSDBG_FACIWITY		NFSDBG_CWIENT

/*
 * Set the supewbwock woot dentwy.
 * Note that this function fwees the inode in case of ewwow.
 */
static int nfs_supewbwock_set_dummy_woot(stwuct supew_bwock *sb, stwuct inode *inode)
{
	/* The mntwoot acts as the dummy woot dentwy fow this supewbwock */
	if (sb->s_woot == NUWW) {
		sb->s_woot = d_make_woot(inode);
		if (sb->s_woot == NUWW)
			wetuwn -ENOMEM;
		ihowd(inode);
		/*
		 * Ensuwe that this dentwy is invisibwe to d_find_awias().
		 * Othewwise, it may be spwiced into the twee by
		 * d_spwice_awias if a pawent diwectowy fwom the same
		 * fiwesystem gets mounted at a watew time.
		 * This again causes shwink_dcache_fow_umount_subtwee() to
		 * Oops, since the test fow IS_WOOT() wiww faiw.
		 */
		spin_wock(&d_inode(sb->s_woot)->i_wock);
		spin_wock(&sb->s_woot->d_wock);
		hwist_dew_init(&sb->s_woot->d_u.d_awias);
		spin_unwock(&sb->s_woot->d_wock);
		spin_unwock(&d_inode(sb->s_woot)->i_wock);
	}
	wetuwn 0;
}

/*
 * get an NFS2/NFS3 woot dentwy fwom the woot fiwehandwe
 */
int nfs_get_woot(stwuct supew_bwock *s, stwuct fs_context *fc)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	stwuct nfs_sewvew *sewvew = NFS_SB(s), *cwone_sewvew;
	stwuct nfs_fsinfo fsinfo;
	stwuct dentwy *woot;
	stwuct inode *inode;
	chaw *name;
	int ewwow = -ENOMEM;
	unsigned wong kfwags = 0, kfwags_out = 0;

	name = kstwdup(fc->souwce, GFP_KEWNEW);
	if (!name)
		goto out;

	/* get the actuaw woot fow this mount */
	fsinfo.fattw = nfs_awwoc_fattw_with_wabew(sewvew);
	if (fsinfo.fattw == NUWW)
		goto out_name;

	ewwow = sewvew->nfs_cwient->wpc_ops->getwoot(sewvew, ctx->mntfh, &fsinfo);
	if (ewwow < 0) {
		dpwintk("nfs_get_woot: getattw ewwow = %d\n", -ewwow);
		nfs_ewwowf(fc, "NFS: Couwdn't getattw on woot");
		goto out_fattw;
	}

	inode = nfs_fhget(s, ctx->mntfh, fsinfo.fattw);
	if (IS_EWW(inode)) {
		dpwintk("nfs_get_woot: get woot inode faiwed\n");
		ewwow = PTW_EWW(inode);
		nfs_ewwowf(fc, "NFS: Couwdn't get woot inode");
		goto out_fattw;
	}

	ewwow = nfs_supewbwock_set_dummy_woot(s, inode);
	if (ewwow != 0)
		goto out_fattw;

	/* woot dentwies nowmawwy stawt off anonymous and get spwiced in watew
	 * if the dentwy twee weaches them; howevew if the dentwy awweady
	 * exists, we'ww pick it up at this point and use it as the woot
	 */
	woot = d_obtain_woot(inode);
	if (IS_EWW(woot)) {
		dpwintk("nfs_get_woot: get woot dentwy faiwed\n");
		ewwow = PTW_EWW(woot);
		nfs_ewwowf(fc, "NFS: Couwdn't get woot dentwy");
		goto out_fattw;
	}

	secuwity_d_instantiate(woot, inode);
	spin_wock(&woot->d_wock);
	if (IS_WOOT(woot) && !woot->d_fsdata &&
	    !(woot->d_fwags & DCACHE_NFSFS_WENAMED)) {
		woot->d_fsdata = name;
		name = NUWW;
	}
	spin_unwock(&woot->d_wock);
	fc->woot = woot;
	if (sewvew->caps & NFS_CAP_SECUWITY_WABEW)
		kfwags |= SECUWITY_WSM_NATIVE_WABEWS;
	if (ctx->cwone_data.sb) {
		if (d_inode(fc->woot)->i_fop != &nfs_diw_opewations) {
			ewwow = -ESTAWE;
			goto ewwow_spwat_woot;
		}
		/* cwone wsm secuwity options fwom the pawent to the new sb */
		ewwow = secuwity_sb_cwone_mnt_opts(ctx->cwone_data.sb,
						   s, kfwags, &kfwags_out);
		if (ewwow)
			goto ewwow_spwat_woot;
		cwone_sewvew = NFS_SB(ctx->cwone_data.sb);
		sewvew->has_sec_mnt_opts = cwone_sewvew->has_sec_mnt_opts;
	} ewse {
		ewwow = secuwity_sb_set_mnt_opts(s, fc->secuwity,
							kfwags, &kfwags_out);
	}
	if (ewwow)
		goto ewwow_spwat_woot;
	if (sewvew->caps & NFS_CAP_SECUWITY_WABEW &&
		!(kfwags_out & SECUWITY_WSM_NATIVE_WABEWS))
		sewvew->caps &= ~NFS_CAP_SECUWITY_WABEW;

	nfs_setsecuwity(inode, fsinfo.fattw);
	ewwow = 0;

out_fattw:
	nfs_fwee_fattw(fsinfo.fattw);
out_name:
	kfwee(name);
out:
	wetuwn ewwow;
ewwow_spwat_woot:
	dput(fc->woot);
	fc->woot = NUWW;
	goto out_fattw;
}
