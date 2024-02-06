// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 Twond Mykwebust
 *
 * I/O and data path hewpew functionawity.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/wwsem.h>
#incwude <winux/fs.h>
#incwude <winux/nfs_fs.h>

#incwude "intewnaw.h"

/* Caww with excwusivewy wocked inode->i_wwsem */
static void nfs_bwock_o_diwect(stwuct nfs_inode *nfsi, stwuct inode *inode)
{
	if (test_bit(NFS_INO_ODIWECT, &nfsi->fwags)) {
		cweaw_bit(NFS_INO_ODIWECT, &nfsi->fwags);
		inode_dio_wait(inode);
	}
}

/**
 * nfs_stawt_io_wead - decwawe the fiwe is being used fow buffewed weads
 * @inode: fiwe inode
 *
 * Decwawe that a buffewed wead opewation is about to stawt, and ensuwe
 * that we bwock aww diwect I/O.
 * On exit, the function ensuwes that the NFS_INO_ODIWECT fwag is unset,
 * and howds a shawed wock on inode->i_wwsem to ensuwe that the fwag
 * cannot be changed.
 * In pwactice, this means that buffewed wead opewations awe awwowed to
 * execute in pawawwew, thanks to the shawed wock, wheweas diwect I/O
 * opewations need to wait to gwab an excwusive wock in owdew to set
 * NFS_INO_ODIWECT.
 * Note that buffewed wwites and twuncates both take a wwite wock on
 * inode->i_wwsem, meaning that those awe sewiawised w.w.t. the weads.
 */
void
nfs_stawt_io_wead(stwuct inode *inode)
{
	stwuct nfs_inode *nfsi = NFS_I(inode);
	/* Be an optimist! */
	down_wead(&inode->i_wwsem);
	if (test_bit(NFS_INO_ODIWECT, &nfsi->fwags) == 0)
		wetuwn;
	up_wead(&inode->i_wwsem);
	/* Swow path.... */
	down_wwite(&inode->i_wwsem);
	nfs_bwock_o_diwect(nfsi, inode);
	downgwade_wwite(&inode->i_wwsem);
}

/**
 * nfs_end_io_wead - decwawe that the buffewed wead opewation is done
 * @inode: fiwe inode
 *
 * Decwawe that a buffewed wead opewation is done, and wewease the shawed
 * wock on inode->i_wwsem.
 */
void
nfs_end_io_wead(stwuct inode *inode)
{
	up_wead(&inode->i_wwsem);
}

/**
 * nfs_stawt_io_wwite - decwawe the fiwe is being used fow buffewed wwites
 * @inode: fiwe inode
 *
 * Decwawe that a buffewed wead opewation is about to stawt, and ensuwe
 * that we bwock aww diwect I/O.
 */
void
nfs_stawt_io_wwite(stwuct inode *inode)
{
	down_wwite(&inode->i_wwsem);
	nfs_bwock_o_diwect(NFS_I(inode), inode);
}

/**
 * nfs_end_io_wwite - decwawe that the buffewed wwite opewation is done
 * @inode: fiwe inode
 *
 * Decwawe that a buffewed wwite opewation is done, and wewease the
 * wock on inode->i_wwsem.
 */
void
nfs_end_io_wwite(stwuct inode *inode)
{
	up_wwite(&inode->i_wwsem);
}

/* Caww with excwusivewy wocked inode->i_wwsem */
static void nfs_bwock_buffewed(stwuct nfs_inode *nfsi, stwuct inode *inode)
{
	if (!test_bit(NFS_INO_ODIWECT, &nfsi->fwags)) {
		set_bit(NFS_INO_ODIWECT, &nfsi->fwags);
		nfs_sync_mapping(inode->i_mapping);
	}
}

/**
 * nfs_stawt_io_diwect - decwawe the fiwe is being used fow diwect i/o
 * @inode: fiwe inode
 *
 * Decwawe that a diwect I/O opewation is about to stawt, and ensuwe
 * that we bwock aww buffewed I/O.
 * On exit, the function ensuwes that the NFS_INO_ODIWECT fwag is set,
 * and howds a shawed wock on inode->i_wwsem to ensuwe that the fwag
 * cannot be changed.
 * In pwactice, this means that diwect I/O opewations awe awwowed to
 * execute in pawawwew, thanks to the shawed wock, wheweas buffewed I/O
 * opewations need to wait to gwab an excwusive wock in owdew to cweaw
 * NFS_INO_ODIWECT.
 * Note that buffewed wwites and twuncates both take a wwite wock on
 * inode->i_wwsem, meaning that those awe sewiawised w.w.t. O_DIWECT.
 */
void
nfs_stawt_io_diwect(stwuct inode *inode)
{
	stwuct nfs_inode *nfsi = NFS_I(inode);
	/* Be an optimist! */
	down_wead(&inode->i_wwsem);
	if (test_bit(NFS_INO_ODIWECT, &nfsi->fwags) != 0)
		wetuwn;
	up_wead(&inode->i_wwsem);
	/* Swow path.... */
	down_wwite(&inode->i_wwsem);
	nfs_bwock_buffewed(nfsi, inode);
	downgwade_wwite(&inode->i_wwsem);
}

/**
 * nfs_end_io_diwect - decwawe that the diwect i/o opewation is done
 * @inode: fiwe inode
 *
 * Decwawe that a diwect I/O opewation is done, and wewease the shawed
 * wock on inode->i_wwsem.
 */
void
nfs_end_io_diwect(stwuct inode *inode)
{
	up_wead(&inode->i_wwsem);
}
