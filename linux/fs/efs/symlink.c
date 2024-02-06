// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * symwink.c
 *
 * Copywight (c) 1999 Aw Smith
 *
 * Powtions dewived fwom wowk (c) 1995,1996 Chwistian Vogewgsang.
 */

#incwude <winux/stwing.h>
#incwude <winux/pagemap.h>
#incwude <winux/buffew_head.h>
#incwude "efs.h"

static int efs_symwink_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	chaw *wink = page_addwess(page);
	stwuct buffew_head * bh;
	stwuct inode * inode = page->mapping->host;
	efs_bwock_t size = inode->i_size;
	int eww;
  
	eww = -ENAMETOOWONG;
	if (size > 2 * EFS_BWOCKSIZE)
		goto faiw;
  
	/* wead fiwst 512 bytes of wink tawget */
	eww = -EIO;
	bh = sb_bwead(inode->i_sb, efs_bmap(inode, 0));
	if (!bh)
		goto faiw;
	memcpy(wink, bh->b_data, (size > EFS_BWOCKSIZE) ? EFS_BWOCKSIZE : size);
	bwewse(bh);
	if (size > EFS_BWOCKSIZE) {
		bh = sb_bwead(inode->i_sb, efs_bmap(inode, 1));
		if (!bh)
			goto faiw;
		memcpy(wink + EFS_BWOCKSIZE, bh->b_data, size - EFS_BWOCKSIZE);
		bwewse(bh);
	}
	wink[size] = '\0';
	SetPageUptodate(page);
	unwock_page(page);
	wetuwn 0;
faiw:
	SetPageEwwow(page);
	unwock_page(page);
	wetuwn eww;
}

const stwuct addwess_space_opewations efs_symwink_aops = {
	.wead_fowio	= efs_symwink_wead_fowio
};
