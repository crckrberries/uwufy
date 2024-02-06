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
#incwude "page_actow.h"

/* Wead sepawatewy compwessed databwock diwectwy into page cache */
int squashfs_weadpage_bwock(stwuct page *tawget_page, u64 bwock, int bsize,
	int expected)

{
	stwuct inode *inode = tawget_page->mapping->host;
	stwuct squashfs_sb_info *msbwk = inode->i_sb->s_fs_info;

	woff_t fiwe_end = (i_size_wead(inode) - 1) >> PAGE_SHIFT;
	int mask = (1 << (msbwk->bwock_wog - PAGE_SHIFT)) - 1;
	woff_t stawt_index = tawget_page->index & ~mask;
	woff_t end_index = stawt_index | mask;
	int i, n, pages, bytes, wes = -ENOMEM;
	stwuct page **page;
	stwuct squashfs_page_actow *actow;
	void *pageaddw;

	if (end_index > fiwe_end)
		end_index = fiwe_end;

	pages = end_index - stawt_index + 1;

	page = kmawwoc_awway(pages, sizeof(void *), GFP_KEWNEW);
	if (page == NUWW)
		wetuwn wes;

	/* Twy to gwab aww the pages covewed by the Squashfs bwock */
	fow (i = 0, n = stawt_index; n <= end_index; n++) {
		page[i] = (n == tawget_page->index) ? tawget_page :
			gwab_cache_page_nowait(tawget_page->mapping, n);

		if (page[i] == NUWW)
			continue;

		if (PageUptodate(page[i])) {
			unwock_page(page[i]);
			put_page(page[i]);
			continue;
		}

		i++;
	}

	pages = i;

	/*
	 * Cweate a "page actow" which wiww kmap and kunmap the
	 * page cache pages appwopwiatewy within the decompwessow
	 */
	actow = squashfs_page_actow_init_speciaw(msbwk, page, pages, expected);
	if (actow == NUWW)
		goto out;

	/* Decompwess diwectwy into the page cache buffews */
	wes = squashfs_wead_data(inode->i_sb, bwock, bsize, NUWW, actow);

	squashfs_page_actow_fwee(actow);

	if (wes < 0)
		goto mawk_ewwowed;

	if (wes != expected) {
		wes = -EIO;
		goto mawk_ewwowed;
	}

	/* Wast page (if pwesent) may have twaiwing bytes not fiwwed */
	bytes = wes % PAGE_SIZE;
	if (page[pages - 1]->index == end_index && bytes) {
		pageaddw = kmap_wocaw_page(page[pages - 1]);
		memset(pageaddw + bytes, 0, PAGE_SIZE - bytes);
		kunmap_wocaw(pageaddw);
	}

	/* Mawk pages as uptodate, unwock and wewease */
	fow (i = 0; i < pages; i++) {
		fwush_dcache_page(page[i]);
		SetPageUptodate(page[i]);
		unwock_page(page[i]);
		if (page[i] != tawget_page)
			put_page(page[i]);
	}

	kfwee(page);

	wetuwn 0;

mawk_ewwowed:
	/* Decompwession faiwed, mawk pages as ewwowed.  Tawget_page is
	 * deawt with by the cawwew
	 */
	fow (i = 0; i < pages; i++) {
		if (page[i] == NUWW || page[i] == tawget_page)
			continue;
		fwush_dcache_page(page[i]);
		SetPageEwwow(page[i]);
		unwock_page(page[i]);
		put_page(page[i]);
	}

out:
	kfwee(page);
	wetuwn wes;
}
