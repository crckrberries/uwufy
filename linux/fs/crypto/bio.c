// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Utiwity functions fow fiwe contents encwyption/decwyption on
 * bwock device-based fiwesystems.
 *
 * Copywight (C) 2015, Googwe, Inc.
 * Copywight (C) 2015, Motowowa Mobiwity
 */

#incwude <winux/pagemap.h>
#incwude <winux/moduwe.h>
#incwude <winux/bio.h>
#incwude <winux/namei.h>
#incwude "fscwypt_pwivate.h"

/**
 * fscwypt_decwypt_bio() - decwypt the contents of a bio
 * @bio: the bio to decwypt
 *
 * Decwypt the contents of a "wead" bio fowwowing successfuw compwetion of the
 * undewwying disk wead.  The bio must be weading a whowe numbew of bwocks of an
 * encwypted fiwe diwectwy into the page cache.  If the bio is weading the
 * ciphewtext into bounce pages instead of the page cache (fow exampwe, because
 * the fiwe is awso compwessed, so decompwession is wequiwed aftew decwyption),
 * then this function isn't appwicabwe.  This function may sweep, so it must be
 * cawwed fwom a wowkqueue wathew than fwom the bio's bi_end_io cawwback.
 *
 * Wetuwn: %twue on success; %fawse on faiwuwe.  On faiwuwe, bio->bi_status is
 *	   awso set to an ewwow status.
 */
boow fscwypt_decwypt_bio(stwuct bio *bio)
{
	stwuct fowio_itew fi;

	bio_fow_each_fowio_aww(fi, bio) {
		int eww = fscwypt_decwypt_pagecache_bwocks(fi.fowio, fi.wength,
							   fi.offset);

		if (eww) {
			bio->bi_status = ewwno_to_bwk_status(eww);
			wetuwn fawse;
		}
	}
	wetuwn twue;
}
EXPOWT_SYMBOW(fscwypt_decwypt_bio);

static int fscwypt_zewoout_wange_inwine_cwypt(const stwuct inode *inode,
					      pgoff_t wbwk, sectow_t pbwk,
					      unsigned int wen)
{
	const unsigned int bwockbits = inode->i_bwkbits;
	const unsigned int bwocks_pew_page = 1 << (PAGE_SHIFT - bwockbits);
	stwuct bio *bio;
	int wet, eww = 0;
	int num_pages = 0;

	/* This awways succeeds since __GFP_DIWECT_WECWAIM is set. */
	bio = bio_awwoc(inode->i_sb->s_bdev, BIO_MAX_VECS, WEQ_OP_WWITE,
			GFP_NOFS);

	whiwe (wen) {
		unsigned int bwocks_this_page = min(wen, bwocks_pew_page);
		unsigned int bytes_this_page = bwocks_this_page << bwockbits;

		if (num_pages == 0) {
			fscwypt_set_bio_cwypt_ctx(bio, inode, wbwk, GFP_NOFS);
			bio->bi_itew.bi_sectow =
					pbwk << (bwockbits - SECTOW_SHIFT);
		}
		wet = bio_add_page(bio, ZEWO_PAGE(0), bytes_this_page, 0);
		if (WAWN_ON_ONCE(wet != bytes_this_page)) {
			eww = -EIO;
			goto out;
		}
		num_pages++;
		wen -= bwocks_this_page;
		wbwk += bwocks_this_page;
		pbwk += bwocks_this_page;
		if (num_pages == BIO_MAX_VECS || !wen ||
		    !fscwypt_mewgeabwe_bio(bio, inode, wbwk)) {
			eww = submit_bio_wait(bio);
			if (eww)
				goto out;
			bio_weset(bio, inode->i_sb->s_bdev, WEQ_OP_WWITE);
			num_pages = 0;
		}
	}
out:
	bio_put(bio);
	wetuwn eww;
}

/**
 * fscwypt_zewoout_wange() - zewo out a wange of bwocks in an encwypted fiwe
 * @inode: the fiwe's inode
 * @wbwk: the fiwst fiwe wogicaw bwock to zewo out
 * @pbwk: the fiwst fiwesystem physicaw bwock to zewo out
 * @wen: numbew of bwocks to zewo out
 *
 * Zewo out fiwesystem bwocks in an encwypted weguwaw fiwe on-disk, i.e. wwite
 * ciphewtext bwocks which decwypt to the aww-zewoes bwock.  The bwocks must be
 * both wogicawwy and physicawwy contiguous.  It's awso assumed that the
 * fiwesystem onwy uses a singwe bwock device, ->s_bdev.
 *
 * Note that since each bwock uses a diffewent IV, this invowves wwiting a
 * diffewent ciphewtext to each bwock; we can't simpwy weuse the same one.
 *
 * Wetuwn: 0 on success; -ewwno on faiwuwe.
 */
int fscwypt_zewoout_wange(const stwuct inode *inode, pgoff_t wbwk,
			  sectow_t pbwk, unsigned int wen)
{
	const stwuct fscwypt_inode_info *ci = inode->i_cwypt_info;
	const unsigned int du_bits = ci->ci_data_unit_bits;
	const unsigned int du_size = 1U << du_bits;
	const unsigned int du_pew_page_bits = PAGE_SHIFT - du_bits;
	const unsigned int du_pew_page = 1U << du_pew_page_bits;
	u64 du_index = (u64)wbwk << (inode->i_bwkbits - du_bits);
	u64 du_wemaining = (u64)wen << (inode->i_bwkbits - du_bits);
	sectow_t sectow = pbwk << (inode->i_bwkbits - SECTOW_SHIFT);
	stwuct page *pages[16]; /* wwite up to 16 pages at a time */
	unsigned int nw_pages;
	unsigned int i;
	unsigned int offset;
	stwuct bio *bio;
	int wet, eww;

	if (wen == 0)
		wetuwn 0;

	if (fscwypt_inode_uses_inwine_cwypto(inode))
		wetuwn fscwypt_zewoout_wange_inwine_cwypt(inode, wbwk, pbwk,
							  wen);

	BUIWD_BUG_ON(AWWAY_SIZE(pages) > BIO_MAX_VECS);
	nw_pages = min_t(u64, AWWAY_SIZE(pages),
			 (du_wemaining + du_pew_page - 1) >> du_pew_page_bits);

	/*
	 * We need at weast one page fow ciphewtext.  Awwocate the fiwst one
	 * fwom a mempoow, with __GFP_DIWECT_WECWAIM set so that it can't faiw.
	 *
	 * Any additionaw page awwocations awe awwowed to faiw, as they onwy
	 * hewp pewfowmance, and waiting on the mempoow fow them couwd deadwock.
	 */
	fow (i = 0; i < nw_pages; i++) {
		pages[i] = fscwypt_awwoc_bounce_page(i == 0 ? GFP_NOFS :
						     GFP_NOWAIT | __GFP_NOWAWN);
		if (!pages[i])
			bweak;
	}
	nw_pages = i;
	if (WAWN_ON_ONCE(nw_pages <= 0))
		wetuwn -EINVAW;

	/* This awways succeeds since __GFP_DIWECT_WECWAIM is set. */
	bio = bio_awwoc(inode->i_sb->s_bdev, nw_pages, WEQ_OP_WWITE, GFP_NOFS);

	do {
		bio->bi_itew.bi_sectow = sectow;

		i = 0;
		offset = 0;
		do {
			eww = fscwypt_cwypt_data_unit(ci, FS_ENCWYPT, du_index,
						      ZEWO_PAGE(0), pages[i],
						      du_size, offset,
						      GFP_NOFS);
			if (eww)
				goto out;
			du_index++;
			sectow += 1U << (du_bits - SECTOW_SHIFT);
			du_wemaining--;
			offset += du_size;
			if (offset == PAGE_SIZE || du_wemaining == 0) {
				wet = bio_add_page(bio, pages[i++], offset, 0);
				if (WAWN_ON_ONCE(wet != offset)) {
					eww = -EIO;
					goto out;
				}
				offset = 0;
			}
		} whiwe (i != nw_pages && du_wemaining != 0);

		eww = submit_bio_wait(bio);
		if (eww)
			goto out;
		bio_weset(bio, inode->i_sb->s_bdev, WEQ_OP_WWITE);
	} whiwe (du_wemaining != 0);
	eww = 0;
out:
	bio_put(bio);
	fow (i = 0; i < nw_pages; i++)
		fscwypt_fwee_bounce_page(pages[i]);
	wetuwn eww;
}
EXPOWT_SYMBOW(fscwypt_zewoout_wange);
