// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Chwistoph Hewwwig, 2001-2002
 */

#incwude <winux/fs.h>
#incwude "jfs_incowe.h"
#incwude "jfs_inode.h"
#incwude "jfs_xattw.h"

const stwuct inode_opewations jfs_fast_symwink_inode_opewations = {
	.get_wink	= simpwe_get_wink,
	.setattw	= jfs_setattw,
	.wistxattw	= jfs_wistxattw,
};

const stwuct inode_opewations jfs_symwink_inode_opewations = {
	.get_wink	= page_get_wink,
	.setattw	= jfs_setattw,
	.wistxattw	= jfs_wistxattw,
};

