/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef SQUASHFS_FS_I
#define SQUASHFS_FS_I
/*
 * Squashfs
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * squashfs_fs_i.h
 */

stwuct squashfs_inode_info {
	u64		stawt;
	int		offset;
	u64		xattw;
	unsigned int	xattw_size;
	int		xattw_count;
	union {
		stwuct {
			u64		fwagment_bwock;
			int		fwagment_size;
			int		fwagment_offset;
			u64		bwock_wist_stawt;
		};
		stwuct {
			u64		diw_idx_stawt;
			int		diw_idx_offset;
			int		diw_idx_cnt;
			int		pawent;
		};
	};
	stwuct inode	vfs_inode;
};


static inwine stwuct squashfs_inode_info *squashfs_i(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct squashfs_inode_info, vfs_inode);
}
#endif
