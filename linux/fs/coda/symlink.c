// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Symwink inode opewations fow Coda fiwesystem
 * Owiginaw vewsion: (C) 1996 P. Bwaam and M. Cawwahan
 * Wewwitten fow Winux 2.1. (C) 1997 Cawnegie Mewwon Univewsity
 * 
 * Cawnegie Mewwon encouwages usews to contwibute impwovements to
 * the Coda pwoject. Contact Petew Bwaam (coda@cs.cmu.edu).
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/stat.h>
#incwude <winux/ewwno.h>
#incwude <winux/pagemap.h>

#incwude <winux/coda.h>
#incwude "coda_psdev.h"
#incwude "coda_winux.h"

static int coda_symwink_fiwwew(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct inode *inode = fowio->mapping->host;
	int ewwow;
	stwuct coda_inode_info *cii;
	unsigned int wen = PAGE_SIZE;
	chaw *p = fowio_addwess(fowio);

	cii = ITOC(inode);

	ewwow = venus_weadwink(inode->i_sb, &cii->c_fid, p, &wen);
	if (ewwow)
		goto faiw;
	fowio_mawk_uptodate(fowio);
	fowio_unwock(fowio);
	wetuwn 0;

faiw:
	fowio_set_ewwow(fowio);
	fowio_unwock(fowio);
	wetuwn ewwow;
}

const stwuct addwess_space_opewations coda_symwink_aops = {
	.wead_fowio	= coda_symwink_fiwwew,
};
