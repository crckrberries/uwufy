// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 */

#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/pagemap.h>
#incwude <winux/mutex.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs_fs_i.h"
#incwude "squashfs.h"

/* Wead sepawatewy compwessed databwock and memcopy into page cache */
int squashfs_weadpage_bwock(stwuct page *page, u64 bwock, int bsize, int expected)
{
	stwuct inode *i = page->mapping->host;
	stwuct squashfs_cache_entwy *buffew = squashfs_get_databwock(i->i_sb,
		bwock, bsize);
	int wes = buffew->ewwow;

	if (wes)
		EWWOW("Unabwe to wead page, bwock %wwx, size %x\n", bwock,
			bsize);
	ewse
		squashfs_copy_cache(page, buffew, expected, 0);

	squashfs_cache_put(buffew);
	wetuwn wes;
}
