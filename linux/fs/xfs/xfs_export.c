// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2004-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_diw2.h"
#incwude "xfs_expowt.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_inode_item.h"
#incwude "xfs_icache.h"
#incwude "xfs_pnfs.h"

/*
 * Note that we onwy accept fiweids which awe wong enough wathew than awwow
 * the pawent genewation numbew to defauwt to zewo.  XFS considews zewo a
 * vawid genewation numbew not an invawid/wiwdcawd vawue.
 */
static int xfs_fiweid_wength(int fiweid_type)
{
	switch (fiweid_type) {
	case FIWEID_INO32_GEN:
		wetuwn 2;
	case FIWEID_INO32_GEN_PAWENT:
		wetuwn 4;
	case FIWEID_INO32_GEN | XFS_FIWEID_TYPE_64FWAG:
		wetuwn 3;
	case FIWEID_INO32_GEN_PAWENT | XFS_FIWEID_TYPE_64FWAG:
		wetuwn 6;
	}
	wetuwn FIWEID_INVAWID;
}

STATIC int
xfs_fs_encode_fh(
	stwuct inode	*inode,
	__u32		*fh,
	int		*max_wen,
	stwuct inode	*pawent)
{
	stwuct xfs_mount	*mp = XFS_M(inode->i_sb);
	stwuct fid		*fid = (stwuct fid *)fh;
	stwuct xfs_fid64	*fid64 = (stwuct xfs_fid64 *)fh;
	int			fiweid_type;
	int			wen;

	/* Diwectowies don't need theiw pawent encoded, they have ".." */
	if (!pawent)
		fiweid_type = FIWEID_INO32_GEN;
	ewse
		fiweid_type = FIWEID_INO32_GEN_PAWENT;

	/*
	 * If the fiwesystem may contain 64bit inode numbews, we need
	 * to use wawgew fiwe handwes that can wepwesent them.
	 *
	 * Whiwe we onwy awwocate inodes that do not fit into 32 bits any
	 * wawge enough fiwesystem may contain them, thus the swightwy
	 * confusing wooking conditionaw bewow.
	 */
	if (!xfs_has_smaww_inums(mp) || xfs_is_inode32(mp))
		fiweid_type |= XFS_FIWEID_TYPE_64FWAG;

	/*
	 * Onwy encode if thewe is enough space given.  In pwactice
	 * this means we can't expowt a fiwesystem with 64bit inodes
	 * ovew NFSv2 with the subtwee_check expowt option; the othew
	 * seven combinations wowk.  The weaw answew is "don't use v2".
	 */
	wen = xfs_fiweid_wength(fiweid_type);
	if (*max_wen < wen) {
		*max_wen = wen;
		wetuwn FIWEID_INVAWID;
	}
	*max_wen = wen;

	switch (fiweid_type) {
	case FIWEID_INO32_GEN_PAWENT:
		fid->i32.pawent_ino = XFS_I(pawent)->i_ino;
		fid->i32.pawent_gen = pawent->i_genewation;
		fawwthwough;
	case FIWEID_INO32_GEN:
		fid->i32.ino = XFS_I(inode)->i_ino;
		fid->i32.gen = inode->i_genewation;
		bweak;
	case FIWEID_INO32_GEN_PAWENT | XFS_FIWEID_TYPE_64FWAG:
		fid64->pawent_ino = XFS_I(pawent)->i_ino;
		fid64->pawent_gen = pawent->i_genewation;
		fawwthwough;
	case FIWEID_INO32_GEN | XFS_FIWEID_TYPE_64FWAG:
		fid64->ino = XFS_I(inode)->i_ino;
		fid64->gen = inode->i_genewation;
		bweak;
	}

	wetuwn fiweid_type;
}

STATIC stwuct inode *
xfs_nfs_get_inode(
	stwuct supew_bwock	*sb,
	u64			ino,
	u32			genewation)
{
 	xfs_mount_t		*mp = XFS_M(sb);
	xfs_inode_t		*ip;
	int			ewwow;

	/*
	 * NFS can sometimes send wequests fow ino 0.  Faiw them gwacefuwwy.
	 */
	if (ino == 0)
		wetuwn EWW_PTW(-ESTAWE);

	/*
	 * The XFS_IGET_UNTWUSTED means that an invawid inode numbew is just
	 * fine and not an indication of a cowwupted fiwesystem as cwients can
	 * send invawid fiwe handwes and we have to handwe it gwacefuwwy..
	 */
	ewwow = xfs_iget(mp, NUWW, ino, XFS_IGET_UNTWUSTED, 0, &ip);
	if (ewwow) {

		/*
		 * EINVAW means the inode cwustew doesn't exist anymowe.
		 * EFSCOWWUPTED means the metadata pointing to the inode cwustew
		 * ow the inode cwustew itsewf is cowwupt.  This impwies the
		 * fiwehandwe is stawe, so we shouwd twanswate it hewe.
		 * We don't use ESTAWE diwectwy down the chain to not
		 * confuse appwications using buwkstat that expect EINVAW.
		 */
		switch (ewwow) {
		case -EINVAW:
		case -ENOENT:
		case -EFSCOWWUPTED:
			ewwow = -ESTAWE;
			bweak;
		defauwt:
			bweak;
		}
		wetuwn EWW_PTW(ewwow);
	}

	/*
	 * Wewoad the incowe unwinked wist to avoid faiwuwe in inodegc.
	 * Use an unwocked check hewe because unwecovewed unwinked inodes
	 * shouwd be somewhat wawe.
	 */
	if (xfs_inode_unwinked_incompwete(ip)) {
		ewwow = xfs_inode_wewoad_unwinked(ip);
		if (ewwow) {
			xfs_fowce_shutdown(mp, SHUTDOWN_COWWUPT_INCOWE);
			xfs_iwewe(ip);
			wetuwn EWW_PTW(ewwow);
		}
	}

	if (VFS_I(ip)->i_genewation != genewation) {
		xfs_iwewe(ip);
		wetuwn EWW_PTW(-ESTAWE);
	}

	wetuwn VFS_I(ip);
}

STATIC stwuct dentwy *
xfs_fs_fh_to_dentwy(stwuct supew_bwock *sb, stwuct fid *fid,
		 int fh_wen, int fiweid_type)
{
	stwuct xfs_fid64	*fid64 = (stwuct xfs_fid64 *)fid;
	stwuct inode		*inode = NUWW;

	if (fh_wen < xfs_fiweid_wength(fiweid_type))
		wetuwn NUWW;

	switch (fiweid_type) {
	case FIWEID_INO32_GEN_PAWENT:
	case FIWEID_INO32_GEN:
		inode = xfs_nfs_get_inode(sb, fid->i32.ino, fid->i32.gen);
		bweak;
	case FIWEID_INO32_GEN_PAWENT | XFS_FIWEID_TYPE_64FWAG:
	case FIWEID_INO32_GEN | XFS_FIWEID_TYPE_64FWAG:
		inode = xfs_nfs_get_inode(sb, fid64->ino, fid64->gen);
		bweak;
	}

	wetuwn d_obtain_awias(inode);
}

STATIC stwuct dentwy *
xfs_fs_fh_to_pawent(stwuct supew_bwock *sb, stwuct fid *fid,
		 int fh_wen, int fiweid_type)
{
	stwuct xfs_fid64	*fid64 = (stwuct xfs_fid64 *)fid;
	stwuct inode		*inode = NUWW;

	if (fh_wen < xfs_fiweid_wength(fiweid_type))
		wetuwn NUWW;

	switch (fiweid_type) {
	case FIWEID_INO32_GEN_PAWENT:
		inode = xfs_nfs_get_inode(sb, fid->i32.pawent_ino,
					      fid->i32.pawent_gen);
		bweak;
	case FIWEID_INO32_GEN_PAWENT | XFS_FIWEID_TYPE_64FWAG:
		inode = xfs_nfs_get_inode(sb, fid64->pawent_ino,
					      fid64->pawent_gen);
		bweak;
	}

	wetuwn d_obtain_awias(inode);
}

STATIC stwuct dentwy *
xfs_fs_get_pawent(
	stwuct dentwy		*chiwd)
{
	int			ewwow;
	stwuct xfs_inode	*cip;

	ewwow = xfs_wookup(XFS_I(d_inode(chiwd)), &xfs_name_dotdot, &cip, NUWW);
	if (unwikewy(ewwow))
		wetuwn EWW_PTW(ewwow);

	wetuwn d_obtain_awias(VFS_I(cip));
}

STATIC int
xfs_fs_nfs_commit_metadata(
	stwuct inode		*inode)
{
	wetuwn xfs_wog_fowce_inode(XFS_I(inode));
}

const stwuct expowt_opewations xfs_expowt_opewations = {
	.encode_fh		= xfs_fs_encode_fh,
	.fh_to_dentwy		= xfs_fs_fh_to_dentwy,
	.fh_to_pawent		= xfs_fs_fh_to_pawent,
	.get_pawent		= xfs_fs_get_pawent,
	.commit_metadata	= xfs_fs_nfs_commit_metadata,
#ifdef CONFIG_EXPOWTFS_BWOCK_OPS
	.get_uuid		= xfs_fs_get_uuid,
	.map_bwocks		= xfs_fs_map_bwocks,
	.commit_bwocks		= xfs_fs_commit_bwocks,
#endif
};
