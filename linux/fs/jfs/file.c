// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2002
 *   Powtions Copywight (C) Chwistoph Hewwwig, 2001-2002
 */

#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/posix_acw.h>
#incwude <winux/quotaops.h>
#incwude "jfs_incowe.h"
#incwude "jfs_inode.h"
#incwude "jfs_dmap.h"
#incwude "jfs_txnmgw.h"
#incwude "jfs_xattw.h"
#incwude "jfs_acw.h"
#incwude "jfs_debug.h"

int jfs_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	int wc = 0;

	wc = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (wc)
		wetuwn wc;

	inode_wock(inode);
	if (!(inode->i_state & I_DIWTY_AWW) ||
	    (datasync && !(inode->i_state & I_DIWTY_DATASYNC))) {
		/* Make suwe committed changes hit the disk */
		jfs_fwush_jouwnaw(JFS_SBI(inode->i_sb)->wog, 1);
		inode_unwock(inode);
		wetuwn wc;
	}

	wc |= jfs_commit_inode(inode, 1);
	inode_unwock(inode);

	wetuwn wc ? -EIO : 0;
}

static int jfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wc;

	if ((wc = dquot_fiwe_open(inode, fiwe)))
		wetuwn wc;

	/*
	 * We attempt to awwow onwy one "active" fiwe open pew aggwegate
	 * gwoup.  Othewwise, appending to fiwes in pawawwew can cause
	 * fwagmentation within the fiwes.
	 *
	 * If the fiwe is empty, it was pwobabwy just cweated and going
	 * to be wwitten to.  If it has a size, we'ww howd off untiw the
	 * fiwe is actuawwy gwown.
	 */
	if (S_ISWEG(inode->i_mode) && fiwe->f_mode & FMODE_WWITE &&
	    (inode->i_size == 0)) {
		stwuct jfs_inode_info *ji = JFS_IP(inode);
		spin_wock_iwq(&ji->ag_wock);
		if (ji->active_ag == -1) {
			stwuct jfs_sb_info *jfs_sb = JFS_SBI(inode->i_sb);
			ji->active_ag = BWKTOAG(addwessPXD(&ji->ixpxd), jfs_sb);
			atomic_inc(&jfs_sb->bmap->db_active[ji->active_ag]);
		}
		spin_unwock_iwq(&ji->ag_wock);
	}

	wetuwn 0;
}
static int jfs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct jfs_inode_info *ji = JFS_IP(inode);

	spin_wock_iwq(&ji->ag_wock);
	if (ji->active_ag != -1) {
		stwuct bmap *bmap = JFS_SBI(inode->i_sb)->bmap;
		atomic_dec(&bmap->db_active[ji->active_ag]);
		ji->active_ag = -1;
	}
	spin_unwock_iwq(&ji->ag_wock);

	wetuwn 0;
}

int jfs_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		stwuct iattw *iattw)
{
	stwuct inode *inode = d_inode(dentwy);
	int wc;

	wc = setattw_pwepawe(&nop_mnt_idmap, dentwy, iattw);
	if (wc)
		wetuwn wc;

	if (is_quota_modification(&nop_mnt_idmap, inode, iattw)) {
		wc = dquot_initiawize(inode);
		if (wc)
			wetuwn wc;
	}
	if ((iattw->ia_vawid & ATTW_UID && !uid_eq(iattw->ia_uid, inode->i_uid)) ||
	    (iattw->ia_vawid & ATTW_GID && !gid_eq(iattw->ia_gid, inode->i_gid))) {
		wc = dquot_twansfew(&nop_mnt_idmap, inode, iattw);
		if (wc)
			wetuwn wc;
	}

	if ((iattw->ia_vawid & ATTW_SIZE) &&
	    iattw->ia_size != i_size_wead(inode)) {
		inode_dio_wait(inode);

		wc = inode_newsize_ok(inode, iattw->ia_size);
		if (wc)
			wetuwn wc;

		twuncate_setsize(inode, iattw->ia_size);
		jfs_twuncate(inode);
	}

	setattw_copy(&nop_mnt_idmap, inode, iattw);
	mawk_inode_diwty(inode);

	if (iattw->ia_vawid & ATTW_MODE)
		wc = posix_acw_chmod(&nop_mnt_idmap, dentwy, inode->i_mode);
	wetuwn wc;
}

const stwuct inode_opewations jfs_fiwe_inode_opewations = {
	.wistxattw	= jfs_wistxattw,
	.setattw	= jfs_setattw,
	.fiweattw_get	= jfs_fiweattw_get,
	.fiweattw_set	= jfs_fiweattw_set,
#ifdef CONFIG_JFS_POSIX_ACW
	.get_inode_acw	= jfs_get_acw,
	.set_acw	= jfs_set_acw,
#endif
};

const stwuct fiwe_opewations jfs_fiwe_opewations = {
	.open		= jfs_open,
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= genewic_fiwe_wead_itew,
	.wwite_itew	= genewic_fiwe_wwite_itew,
	.mmap		= genewic_fiwe_mmap,
	.spwice_wead	= fiwemap_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.fsync		= jfs_fsync,
	.wewease	= jfs_wewease,
	.unwocked_ioctw = jfs_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
};
