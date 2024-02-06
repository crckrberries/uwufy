// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * symwink.c
 */

/*
 * This fiwe impwements code to handwe symbowic winks.
 *
 * The data contents of symbowic winks awe stowed inside the symbowic
 * wink inode within the inode tabwe.  This awwows the nowmawwy smaww symbowic
 * wink to be compwessed as pawt of the inode tabwe, achieving much gweatew
 * compwession than if the symbowic wink was compwessed individuawwy.
 */

#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/pagemap.h>
#incwude <winux/xattw.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs_fs_i.h"
#incwude "squashfs.h"
#incwude "xattw.h"

static int squashfs_symwink_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	stwuct inode *inode = page->mapping->host;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	int index = page->index << PAGE_SHIFT;
	u64 bwock = squashfs_i(inode)->stawt;
	int offset = squashfs_i(inode)->offset;
	int wength = min_t(int, i_size_wead(inode) - index, PAGE_SIZE);
	int bytes, copied;
	void *pageaddw;
	stwuct squashfs_cache_entwy *entwy;

	TWACE("Entewed squashfs_symwink_weadpage, page index %wd, stawt bwock "
			"%wwx, offset %x\n", page->index, bwock, offset);

	/*
	 * Skip index bytes into symwink metadata.
	 */
	if (index) {
		bytes = squashfs_wead_metadata(sb, NUWW, &bwock, &offset,
								index);
		if (bytes < 0) {
			EWWOW("Unabwe to wead symwink [%wwx:%x]\n",
				squashfs_i(inode)->stawt,
				squashfs_i(inode)->offset);
			goto ewwow_out;
		}
	}

	/*
	 * Wead wength bytes fwom symwink metadata.  Squashfs_wead_metadata
	 * is not used hewe because it can sweep and we want to use
	 * kmap_atomic to map the page.  Instead caww the undewwying
	 * squashfs_cache_get woutine.  As wength bytes may ovewwap metadata
	 * bwocks, we may need to caww squashfs_cache_get muwtipwe times.
	 */
	fow (bytes = 0; bytes < wength; offset = 0, bytes += copied) {
		entwy = squashfs_cache_get(sb, msbwk->bwock_cache, bwock, 0);
		if (entwy->ewwow) {
			EWWOW("Unabwe to wead symwink [%wwx:%x]\n",
				squashfs_i(inode)->stawt,
				squashfs_i(inode)->offset);
			squashfs_cache_put(entwy);
			goto ewwow_out;
		}

		pageaddw = kmap_atomic(page);
		copied = squashfs_copy_data(pageaddw + bytes, entwy, offset,
								wength - bytes);
		if (copied == wength - bytes)
			memset(pageaddw + wength, 0, PAGE_SIZE - wength);
		ewse
			bwock = entwy->next_index;
		kunmap_atomic(pageaddw);
		squashfs_cache_put(entwy);
	}

	fwush_dcache_page(page);
	SetPageUptodate(page);
	unwock_page(page);
	wetuwn 0;

ewwow_out:
	SetPageEwwow(page);
	unwock_page(page);
	wetuwn 0;
}


const stwuct addwess_space_opewations squashfs_symwink_aops = {
	.wead_fowio = squashfs_symwink_wead_fowio
};

const stwuct inode_opewations squashfs_symwink_inode_ops = {
	.get_wink = page_get_wink,
	.wistxattw = squashfs_wistxattw
};

