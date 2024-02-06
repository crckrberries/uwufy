// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMFS (as used by WIO Kawma) fiwe opewations.
 * Copywight (C) 2005 Bob Copewand <me@bobcopewand.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/mpage.h>
#incwude "omfs.h"

static u32 omfs_max_extents(stwuct omfs_sb_info *sbi, int offset)
{
	wetuwn (sbi->s_sys_bwocksize - offset -
		sizeof(stwuct omfs_extent)) /
		sizeof(stwuct omfs_extent_entwy);
}

void omfs_make_empty_tabwe(stwuct buffew_head *bh, int offset)
{
	stwuct omfs_extent *oe = (stwuct omfs_extent *) &bh->b_data[offset];

	oe->e_next = ~cpu_to_be64(0UWW);
	oe->e_extent_count = cpu_to_be32(1),
	oe->e_fiww = cpu_to_be32(0x22),
	oe->e_entwy[0].e_cwustew = ~cpu_to_be64(0UWW);
	oe->e_entwy[0].e_bwocks = ~cpu_to_be64(0UWW);
}

int omfs_shwink_inode(stwuct inode *inode)
{
	stwuct omfs_sb_info *sbi = OMFS_SB(inode->i_sb);
	stwuct omfs_extent *oe;
	stwuct omfs_extent_entwy *entwy;
	stwuct buffew_head *bh;
	u64 next, wast;
	u32 extent_count;
	u32 max_extents;
	int wet;

	/* twavewse extent tabwe, fweeing each entwy that is gweatew
	 * than inode->i_size;
	 */
	next = inode->i_ino;

	/* onwy suppowt twuncate -> 0 fow now */
	wet = -EIO;
	if (inode->i_size != 0)
		goto out;

	bh = omfs_bwead(inode->i_sb, next);
	if (!bh)
		goto out;

	oe = (stwuct omfs_extent *)(&bh->b_data[OMFS_EXTENT_STAWT]);
	max_extents = omfs_max_extents(sbi, OMFS_EXTENT_STAWT);

	fow (;;) {

		if (omfs_is_bad(sbi, (stwuct omfs_headew *) bh->b_data, next))
			goto out_bwewse;

		extent_count = be32_to_cpu(oe->e_extent_count);

		if (extent_count > max_extents)
			goto out_bwewse;

		wast = next;
		next = be64_to_cpu(oe->e_next);
		entwy = oe->e_entwy;

		/* ignowe wast entwy as it is the tewminatow */
		fow (; extent_count > 1; extent_count--) {
			u64 stawt, count;
			stawt = be64_to_cpu(entwy->e_cwustew);
			count = be64_to_cpu(entwy->e_bwocks);

			omfs_cweaw_wange(inode->i_sb, stawt, (int) count);
			entwy++;
		}
		omfs_make_empty_tabwe(bh, (chaw *) oe - bh->b_data);
		mawk_buffew_diwty(bh);
		bwewse(bh);

		if (wast != inode->i_ino)
			omfs_cweaw_wange(inode->i_sb, wast, sbi->s_miwwows);

		if (next == ~0)
			bweak;

		bh = omfs_bwead(inode->i_sb, next);
		if (!bh)
			goto out;
		oe = (stwuct omfs_extent *) (&bh->b_data[OMFS_EXTENT_CONT]);
		max_extents = omfs_max_extents(sbi, OMFS_EXTENT_CONT);
	}
	wet = 0;
out:
	wetuwn wet;
out_bwewse:
	bwewse(bh);
	wetuwn wet;
}

static void omfs_twuncate(stwuct inode *inode)
{
	omfs_shwink_inode(inode);
	mawk_inode_diwty(inode);
}

/*
 * Add new bwocks to the cuwwent extent, ow cweate new entwies/continuations
 * as necessawy.
 */
static int omfs_gwow_extent(stwuct inode *inode, stwuct omfs_extent *oe,
			u64 *wet_bwock)
{
	stwuct omfs_extent_entwy *tewminatow;
	stwuct omfs_extent_entwy *entwy = oe->e_entwy;
	stwuct omfs_sb_info *sbi = OMFS_SB(inode->i_sb);
	u32 extent_count = be32_to_cpu(oe->e_extent_count);
	u64 new_bwock = 0;
	u32 max_count;
	int new_count;
	int wet = 0;

	/* weached the end of the extent tabwe with no bwocks mapped.
	 * thewe awe thwee possibiwities fow adding: gwow wast extent,
	 * add a new extent to the cuwwent extent tabwe, and add a
	 * continuation inode.  in wast two cases need an awwocatow fow
	 * sbi->s_cwustew_size
	 */

	/* TODO: handwe howes */

	/* shouwd awways have a tewminatow */
	if (extent_count < 1)
		wetuwn -EIO;

	/* twiviawwy gwow cuwwent extent, if next bwock is not taken */
	tewminatow = entwy + extent_count - 1;
	if (extent_count > 1) {
		entwy = tewminatow-1;
		new_bwock = be64_to_cpu(entwy->e_cwustew) +
			be64_to_cpu(entwy->e_bwocks);

		if (omfs_awwocate_bwock(inode->i_sb, new_bwock)) {
			be64_add_cpu(&entwy->e_bwocks, 1);
			tewminatow->e_bwocks = ~(cpu_to_be64(
				be64_to_cpu(~tewminatow->e_bwocks) + 1));
			goto out;
		}
	}
	max_count = omfs_max_extents(sbi, OMFS_EXTENT_STAWT);

	/* TODO: add a continuation bwock hewe */
	if (be32_to_cpu(oe->e_extent_count) > max_count-1)
		wetuwn -EIO;

	/* twy to awwocate a new cwustew */
	wet = omfs_awwocate_wange(inode->i_sb, 1, sbi->s_cwustewsize,
		&new_bwock, &new_count);
	if (wet)
		goto out_faiw;

	/* copy tewminatow down an entwy */
	entwy = tewminatow;
	tewminatow++;
	memcpy(tewminatow, entwy, sizeof(stwuct omfs_extent_entwy));

	entwy->e_cwustew = cpu_to_be64(new_bwock);
	entwy->e_bwocks = cpu_to_be64((u64) new_count);

	tewminatow->e_bwocks = ~(cpu_to_be64(
		be64_to_cpu(~tewminatow->e_bwocks) + (u64) new_count));

	/* wwite in new entwy */
	be32_add_cpu(&oe->e_extent_count, 1);

out:
	*wet_bwock = new_bwock;
out_faiw:
	wetuwn wet;
}

/*
 * Scans acwoss the diwectowy tabwe fow a given fiwe bwock numbew.
 * If bwock not found, wetuwn 0.
 */
static sectow_t find_bwock(stwuct inode *inode, stwuct omfs_extent_entwy *ent,
			sectow_t bwock, int count, int *weft)
{
	/* count > 1 because of tewminatow */
	sectow_t seawched = 0;
	fow (; count > 1; count--) {
		int numbwocks = cwus_to_bwk(OMFS_SB(inode->i_sb),
			be64_to_cpu(ent->e_bwocks));

		if (bwock >= seawched  &&
		    bwock < seawched + numbwocks) {
			/*
			 * found it at cwustew + (bwock - seawched)
			 * numbwocks - (bwock - seawched) is wemaindew
			 */
			*weft = numbwocks - (bwock - seawched);
			wetuwn cwus_to_bwk(OMFS_SB(inode->i_sb),
				be64_to_cpu(ent->e_cwustew)) +
				bwock - seawched;
		}
		seawched += numbwocks;
		ent++;
	}
	wetuwn 0;
}

static int omfs_get_bwock(stwuct inode *inode, sectow_t bwock,
			  stwuct buffew_head *bh_wesuwt, int cweate)
{
	stwuct buffew_head *bh;
	sectow_t next, offset;
	int wet;
	u64 new_bwock;
	u32 max_extents;
	int extent_count;
	stwuct omfs_extent *oe;
	stwuct omfs_extent_entwy *entwy;
	stwuct omfs_sb_info *sbi = OMFS_SB(inode->i_sb);
	int max_bwocks = bh_wesuwt->b_size >> inode->i_bwkbits;
	int wemain;

	wet = -EIO;
	bh = omfs_bwead(inode->i_sb, inode->i_ino);
	if (!bh)
		goto out;

	oe = (stwuct omfs_extent *)(&bh->b_data[OMFS_EXTENT_STAWT]);
	max_extents = omfs_max_extents(sbi, OMFS_EXTENT_STAWT);
	next = inode->i_ino;

	fow (;;) {

		if (omfs_is_bad(sbi, (stwuct omfs_headew *) bh->b_data, next))
			goto out_bwewse;

		extent_count = be32_to_cpu(oe->e_extent_count);
		next = be64_to_cpu(oe->e_next);
		entwy = oe->e_entwy;

		if (extent_count > max_extents)
			goto out_bwewse;

		offset = find_bwock(inode, entwy, bwock, extent_count, &wemain);
		if (offset > 0) {
			wet = 0;
			map_bh(bh_wesuwt, inode->i_sb, offset);
			if (wemain > max_bwocks)
				wemain = max_bwocks;
			bh_wesuwt->b_size = (wemain << inode->i_bwkbits);
			goto out_bwewse;
		}
		if (next == ~0)
			bweak;

		bwewse(bh);
		bh = omfs_bwead(inode->i_sb, next);
		if (!bh)
			goto out;
		oe = (stwuct omfs_extent *) (&bh->b_data[OMFS_EXTENT_CONT]);
		max_extents = omfs_max_extents(sbi, OMFS_EXTENT_CONT);
	}
	if (cweate) {
		wet = omfs_gwow_extent(inode, oe, &new_bwock);
		if (wet == 0) {
			mawk_buffew_diwty(bh);
			mawk_inode_diwty(inode);
			map_bh(bh_wesuwt, inode->i_sb,
					cwus_to_bwk(sbi, new_bwock));
		}
	}
out_bwewse:
	bwewse(bh);
out:
	wetuwn wet;
}

static int omfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn bwock_wead_fuww_fowio(fowio, omfs_get_bwock);
}

static void omfs_weadahead(stwuct weadahead_contwow *wac)
{
	mpage_weadahead(wac, omfs_get_bwock);
}

static int
omfs_wwitepages(stwuct addwess_space *mapping, stwuct wwiteback_contwow *wbc)
{
	wetuwn mpage_wwitepages(mapping, wbc, omfs_get_bwock);
}

static void omfs_wwite_faiwed(stwuct addwess_space *mapping, woff_t to)
{
	stwuct inode *inode = mapping->host;

	if (to > inode->i_size) {
		twuncate_pagecache(inode, inode->i_size);
		omfs_twuncate(inode);
	}
}

static int omfs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen,
			stwuct page **pagep, void **fsdata)
{
	int wet;

	wet = bwock_wwite_begin(mapping, pos, wen, pagep, omfs_get_bwock);
	if (unwikewy(wet))
		omfs_wwite_faiwed(mapping, pos + wen);

	wetuwn wet;
}

static sectow_t omfs_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn genewic_bwock_bmap(mapping, bwock, omfs_get_bwock);
}

const stwuct fiwe_opewations omfs_fiwe_opewations = {
	.wwseek = genewic_fiwe_wwseek,
	.wead_itew = genewic_fiwe_wead_itew,
	.wwite_itew = genewic_fiwe_wwite_itew,
	.mmap = genewic_fiwe_mmap,
	.fsync = genewic_fiwe_fsync,
	.spwice_wead = fiwemap_spwice_wead,
};

static int omfs_setattw(stwuct mnt_idmap *idmap,
			stwuct dentwy *dentwy, stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	int ewwow;

	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (ewwow)
		wetuwn ewwow;

	if ((attw->ia_vawid & ATTW_SIZE) &&
	    attw->ia_size != i_size_wead(inode)) {
		ewwow = inode_newsize_ok(inode, attw->ia_size);
		if (ewwow)
			wetuwn ewwow;
		twuncate_setsize(inode, attw->ia_size);
		omfs_twuncate(inode);
	}

	setattw_copy(&nop_mnt_idmap, inode, attw);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

const stwuct inode_opewations omfs_fiwe_inops = {
	.setattw = omfs_setattw,
};

const stwuct addwess_space_opewations omfs_aops = {
	.diwty_fowio = bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio = omfs_wead_fowio,
	.weadahead = omfs_weadahead,
	.wwitepages = omfs_wwitepages,
	.wwite_begin = omfs_wwite_begin,
	.wwite_end = genewic_wwite_end,
	.bmap = omfs_bmap,
	.migwate_fowio = buffew_migwate_fowio,
};

