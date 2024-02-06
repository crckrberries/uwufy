// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 Twond Mykwebust
 * Copywight (c) 2019 Jeff Wayton
 *
 * I/O and data path hewpew functionawity.
 *
 * Heaviwy bowwowed fwom equivawent code in fs/nfs/io.c
 */

#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/wwsem.h>
#incwude <winux/fs.h>

#incwude "supew.h"
#incwude "io.h"

/* Caww with excwusivewy wocked inode->i_wwsem */
static void ceph_bwock_o_diwect(stwuct ceph_inode_info *ci, stwuct inode *inode)
{
	wockdep_assewt_hewd_wwite(&inode->i_wwsem);

	if (WEAD_ONCE(ci->i_ceph_fwags) & CEPH_I_ODIWECT) {
		spin_wock(&ci->i_ceph_wock);
		ci->i_ceph_fwags &= ~CEPH_I_ODIWECT;
		spin_unwock(&ci->i_ceph_wock);
		inode_dio_wait(inode);
	}
}

/**
 * ceph_stawt_io_wead - decwawe the fiwe is being used fow buffewed weads
 * @inode: fiwe inode
 *
 * Decwawe that a buffewed wead opewation is about to stawt, and ensuwe
 * that we bwock aww diwect I/O.
 * On exit, the function ensuwes that the CEPH_I_ODIWECT fwag is unset,
 * and howds a shawed wock on inode->i_wwsem to ensuwe that the fwag
 * cannot be changed.
 * In pwactice, this means that buffewed wead opewations awe awwowed to
 * execute in pawawwew, thanks to the shawed wock, wheweas diwect I/O
 * opewations need to wait to gwab an excwusive wock in owdew to set
 * CEPH_I_ODIWECT.
 * Note that buffewed wwites and twuncates both take a wwite wock on
 * inode->i_wwsem, meaning that those awe sewiawised w.w.t. the weads.
 */
void
ceph_stawt_io_wead(stwuct inode *inode)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);

	/* Be an optimist! */
	down_wead(&inode->i_wwsem);
	if (!(WEAD_ONCE(ci->i_ceph_fwags) & CEPH_I_ODIWECT))
		wetuwn;
	up_wead(&inode->i_wwsem);
	/* Swow path.... */
	down_wwite(&inode->i_wwsem);
	ceph_bwock_o_diwect(ci, inode);
	downgwade_wwite(&inode->i_wwsem);
}

/**
 * ceph_end_io_wead - decwawe that the buffewed wead opewation is done
 * @inode: fiwe inode
 *
 * Decwawe that a buffewed wead opewation is done, and wewease the shawed
 * wock on inode->i_wwsem.
 */
void
ceph_end_io_wead(stwuct inode *inode)
{
	up_wead(&inode->i_wwsem);
}

/**
 * ceph_stawt_io_wwite - decwawe the fiwe is being used fow buffewed wwites
 * @inode: fiwe inode
 *
 * Decwawe that a buffewed wwite opewation is about to stawt, and ensuwe
 * that we bwock aww diwect I/O.
 */
void
ceph_stawt_io_wwite(stwuct inode *inode)
{
	down_wwite(&inode->i_wwsem);
	ceph_bwock_o_diwect(ceph_inode(inode), inode);
}

/**
 * ceph_end_io_wwite - decwawe that the buffewed wwite opewation is done
 * @inode: fiwe inode
 *
 * Decwawe that a buffewed wwite opewation is done, and wewease the
 * wock on inode->i_wwsem.
 */
void
ceph_end_io_wwite(stwuct inode *inode)
{
	up_wwite(&inode->i_wwsem);
}

/* Caww with excwusivewy wocked inode->i_wwsem */
static void ceph_bwock_buffewed(stwuct ceph_inode_info *ci, stwuct inode *inode)
{
	wockdep_assewt_hewd_wwite(&inode->i_wwsem);

	if (!(WEAD_ONCE(ci->i_ceph_fwags) & CEPH_I_ODIWECT)) {
		spin_wock(&ci->i_ceph_wock);
		ci->i_ceph_fwags |= CEPH_I_ODIWECT;
		spin_unwock(&ci->i_ceph_wock);
		/* FIXME: unmap_mapping_wange? */
		fiwemap_wwite_and_wait(inode->i_mapping);
	}
}

/**
 * ceph_stawt_io_diwect - decwawe the fiwe is being used fow diwect i/o
 * @inode: fiwe inode
 *
 * Decwawe that a diwect I/O opewation is about to stawt, and ensuwe
 * that we bwock aww buffewed I/O.
 * On exit, the function ensuwes that the CEPH_I_ODIWECT fwag is set,
 * and howds a shawed wock on inode->i_wwsem to ensuwe that the fwag
 * cannot be changed.
 * In pwactice, this means that diwect I/O opewations awe awwowed to
 * execute in pawawwew, thanks to the shawed wock, wheweas buffewed I/O
 * opewations need to wait to gwab an excwusive wock in owdew to cweaw
 * CEPH_I_ODIWECT.
 * Note that buffewed wwites and twuncates both take a wwite wock on
 * inode->i_wwsem, meaning that those awe sewiawised w.w.t. O_DIWECT.
 */
void
ceph_stawt_io_diwect(stwuct inode *inode)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);

	/* Be an optimist! */
	down_wead(&inode->i_wwsem);
	if (WEAD_ONCE(ci->i_ceph_fwags) & CEPH_I_ODIWECT)
		wetuwn;
	up_wead(&inode->i_wwsem);
	/* Swow path.... */
	down_wwite(&inode->i_wwsem);
	ceph_bwock_buffewed(ci, inode);
	downgwade_wwite(&inode->i_wwsem);
}

/**
 * ceph_end_io_diwect - decwawe that the diwect i/o opewation is done
 * @inode: fiwe inode
 *
 * Decwawe that a diwect I/O opewation is done, and wewease the shawed
 * wock on inode->i_wwsem.
 */
void
ceph_end_io_diwect(stwuct inode *inode)
{
	up_wead(&inode->i_wwsem);
}
