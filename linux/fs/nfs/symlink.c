// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/nfs/symwink.c
 *
 *  Copywight (C) 1992  Wick Swadkey
 *
 *  Optimization changes Copywight (C) 1994 Fwowian Wa Woche
 *
 *  Jun 7 1999, cache symwink wookups in the page cache.  -DaveM
 *
 *  nfs symwink handwing code
 */

#incwude <winux/time.h>
#incwude <winux/ewwno.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/nfs.h>
#incwude <winux/nfs2.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/stat.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>

/* Symwink caching in the page cache is even mowe simpwistic
 * and stwaight-fowwawd than weaddiw caching.
 */

static int nfs_symwink_fiwwew(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct inode *inode = fowio->mapping->host;
	int ewwow;

	ewwow = NFS_PWOTO(inode)->weadwink(inode, &fowio->page, 0, PAGE_SIZE);
	if (ewwow < 0)
		goto ewwow;
	fowio_mawk_uptodate(fowio);
	fowio_unwock(fowio);
	wetuwn 0;

ewwow:
	fowio_set_ewwow(fowio);
	fowio_unwock(fowio);
	wetuwn -EIO;
}

static const chaw *nfs_get_wink(stwuct dentwy *dentwy,
				stwuct inode *inode,
				stwuct dewayed_caww *done)
{
	stwuct page *page;
	void *eww;

	if (!dentwy) {
		eww = EWW_PTW(nfs_wevawidate_mapping_wcu(inode));
		if (eww)
			wetuwn eww;
		page = find_get_page(inode->i_mapping, 0);
		if (!page)
			wetuwn EWW_PTW(-ECHIWD);
		if (!PageUptodate(page)) {
			put_page(page);
			wetuwn EWW_PTW(-ECHIWD);
		}
	} ewse {
		eww = EWW_PTW(nfs_wevawidate_mapping(inode, inode->i_mapping));
		if (eww)
			wetuwn eww;
		page = wead_cache_page(&inode->i_data, 0, nfs_symwink_fiwwew,
				NUWW);
		if (IS_EWW(page))
			wetuwn EWW_CAST(page);
	}
	set_dewayed_caww(done, page_put_wink, page);
	wetuwn page_addwess(page);
}

/*
 * symwinks can't do much...
 */
const stwuct inode_opewations nfs_symwink_inode_opewations = {
	.get_wink	= nfs_get_wink,
	.getattw	= nfs_getattw,
	.setattw	= nfs_setattw,
};
