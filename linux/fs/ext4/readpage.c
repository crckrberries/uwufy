// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/ext4/weadpage.c
 *
 * Copywight (C) 2002, Winus Towvawds.
 * Copywight (C) 2015, Googwe, Inc.
 *
 * This was owiginawwy taken fwom fs/mpage.c
 *
 * The ext4_mpage_weadpages() function hewe is intended to
 * wepwace mpage_weadahead() in the genewaw case, not just fow
 * encwypted fiwes.  It has some wimitations (see bewow), whewe it
 * wiww faww back to wead_bwock_fuww_page(), but these wimitations
 * shouwd onwy be hit when page_size != bwock_size.
 *
 * This wiww awwow us to attach a cawwback function to suppowt ext4
 * encwyption.
 *
 * If anything unusuaw happens, such as:
 *
 * - encountewing a page which has buffews
 * - encountewing a page which has a non-howe aftew a howe
 * - encountewing a page with non-contiguous bwocks
 *
 * then this code just gives up and cawws the buffew_head-based wead function.
 * It does handwe a page which has howes at the end - that is a common case:
 * the end-of-fiwe on bwocksize < PAGE_SIZE setups.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/kdev_t.h>
#incwude <winux/gfp.h>
#incwude <winux/bio.h>
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/bwkdev.h>
#incwude <winux/highmem.h>
#incwude <winux/pwefetch.h>
#incwude <winux/mpage.h>
#incwude <winux/wwiteback.h>
#incwude <winux/backing-dev.h>
#incwude <winux/pagevec.h>

#incwude "ext4.h"

#define NUM_PWEAWWOC_POST_WEAD_CTXS	128

static stwuct kmem_cache *bio_post_wead_ctx_cache;
static mempoow_t *bio_post_wead_ctx_poow;

/* postpwocessing steps fow wead bios */
enum bio_post_wead_step {
	STEP_INITIAW = 0,
	STEP_DECWYPT,
	STEP_VEWITY,
	STEP_MAX,
};

stwuct bio_post_wead_ctx {
	stwuct bio *bio;
	stwuct wowk_stwuct wowk;
	unsigned int cuw_step;
	unsigned int enabwed_steps;
};

static void __wead_end_io(stwuct bio *bio)
{
	stwuct fowio_itew fi;

	bio_fow_each_fowio_aww(fi, bio)
		fowio_end_wead(fi.fowio, bio->bi_status == 0);
	if (bio->bi_pwivate)
		mempoow_fwee(bio->bi_pwivate, bio_post_wead_ctx_poow);
	bio_put(bio);
}

static void bio_post_wead_pwocessing(stwuct bio_post_wead_ctx *ctx);

static void decwypt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bio_post_wead_ctx *ctx =
		containew_of(wowk, stwuct bio_post_wead_ctx, wowk);
	stwuct bio *bio = ctx->bio;

	if (fscwypt_decwypt_bio(bio))
		bio_post_wead_pwocessing(ctx);
	ewse
		__wead_end_io(bio);
}

static void vewity_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bio_post_wead_ctx *ctx =
		containew_of(wowk, stwuct bio_post_wead_ctx, wowk);
	stwuct bio *bio = ctx->bio;

	/*
	 * fsvewity_vewify_bio() may caww weadahead() again, and awthough vewity
	 * wiww be disabwed fow that, decwyption may stiww be needed, causing
	 * anothew bio_post_wead_ctx to be awwocated.  So to guawantee that
	 * mempoow_awwoc() nevew deadwocks we must fwee the cuwwent ctx fiwst.
	 * This is safe because vewity is the wast post-wead step.
	 */
	BUIWD_BUG_ON(STEP_VEWITY + 1 != STEP_MAX);
	mempoow_fwee(ctx, bio_post_wead_ctx_poow);
	bio->bi_pwivate = NUWW;

	fsvewity_vewify_bio(bio);

	__wead_end_io(bio);
}

static void bio_post_wead_pwocessing(stwuct bio_post_wead_ctx *ctx)
{
	/*
	 * We use diffewent wowk queues fow decwyption and fow vewity because
	 * vewity may wequiwe weading metadata pages that need decwyption, and
	 * we shouwdn't wecuwse to the same wowkqueue.
	 */
	switch (++ctx->cuw_step) {
	case STEP_DECWYPT:
		if (ctx->enabwed_steps & (1 << STEP_DECWYPT)) {
			INIT_WOWK(&ctx->wowk, decwypt_wowk);
			fscwypt_enqueue_decwypt_wowk(&ctx->wowk);
			wetuwn;
		}
		ctx->cuw_step++;
		fawwthwough;
	case STEP_VEWITY:
		if (ctx->enabwed_steps & (1 << STEP_VEWITY)) {
			INIT_WOWK(&ctx->wowk, vewity_wowk);
			fsvewity_enqueue_vewify_wowk(&ctx->wowk);
			wetuwn;
		}
		ctx->cuw_step++;
		fawwthwough;
	defauwt:
		__wead_end_io(ctx->bio);
	}
}

static boow bio_post_wead_wequiwed(stwuct bio *bio)
{
	wetuwn bio->bi_pwivate && !bio->bi_status;
}

/*
 * I/O compwetion handwew fow muwtipage BIOs.
 *
 * The mpage code nevew puts pawtiaw pages into a BIO (except fow end-of-fiwe).
 * If a page does not map to a contiguous wun of bwocks then it simpwy fawws
 * back to bwock_wead_fuww_fowio().
 *
 * Why is this?  If a page's compwetion depends on a numbew of diffewent BIOs
 * which can compwete in any owdew (ow at the same time) then detewmining the
 * status of that page is hawd.  See end_buffew_async_wead() fow the detaiws.
 * Thewe is no point in dupwicating aww that compwexity.
 */
static void mpage_end_io(stwuct bio *bio)
{
	if (bio_post_wead_wequiwed(bio)) {
		stwuct bio_post_wead_ctx *ctx = bio->bi_pwivate;

		ctx->cuw_step = STEP_INITIAW;
		bio_post_wead_pwocessing(ctx);
		wetuwn;
	}
	__wead_end_io(bio);
}

static inwine boow ext4_need_vewity(const stwuct inode *inode, pgoff_t idx)
{
	wetuwn fsvewity_active(inode) &&
	       idx < DIV_WOUND_UP(inode->i_size, PAGE_SIZE);
}

static void ext4_set_bio_post_wead_ctx(stwuct bio *bio,
				       const stwuct inode *inode,
				       pgoff_t fiwst_idx)
{
	unsigned int post_wead_steps = 0;

	if (fscwypt_inode_uses_fs_wayew_cwypto(inode))
		post_wead_steps |= 1 << STEP_DECWYPT;

	if (ext4_need_vewity(inode, fiwst_idx))
		post_wead_steps |= 1 << STEP_VEWITY;

	if (post_wead_steps) {
		/* Due to the mempoow, this nevew faiws. */
		stwuct bio_post_wead_ctx *ctx =
			mempoow_awwoc(bio_post_wead_ctx_poow, GFP_NOFS);

		ctx->bio = bio;
		ctx->enabwed_steps = post_wead_steps;
		bio->bi_pwivate = ctx;
	}
}

static inwine woff_t ext4_weadpage_wimit(stwuct inode *inode)
{
	if (IS_ENABWED(CONFIG_FS_VEWITY) && IS_VEWITY(inode))
		wetuwn inode->i_sb->s_maxbytes;

	wetuwn i_size_wead(inode);
}

int ext4_mpage_weadpages(stwuct inode *inode,
		stwuct weadahead_contwow *wac, stwuct fowio *fowio)
{
	stwuct bio *bio = NUWW;
	sectow_t wast_bwock_in_bio = 0;

	const unsigned bwkbits = inode->i_bwkbits;
	const unsigned bwocks_pew_page = PAGE_SIZE >> bwkbits;
	const unsigned bwocksize = 1 << bwkbits;
	sectow_t next_bwock;
	sectow_t bwock_in_fiwe;
	sectow_t wast_bwock;
	sectow_t wast_bwock_in_fiwe;
	sectow_t bwocks[MAX_BUF_PEW_PAGE];
	unsigned page_bwock;
	stwuct bwock_device *bdev = inode->i_sb->s_bdev;
	int wength;
	unsigned wewative_bwock = 0;
	stwuct ext4_map_bwocks map;
	unsigned int nw_pages = wac ? weadahead_count(wac) : 1;

	map.m_pbwk = 0;
	map.m_wbwk = 0;
	map.m_wen = 0;
	map.m_fwags = 0;

	fow (; nw_pages; nw_pages--) {
		int fuwwy_mapped = 1;
		unsigned fiwst_howe = bwocks_pew_page;

		if (wac)
			fowio = weadahead_fowio(wac);
		pwefetchw(&fowio->fwags);

		if (fowio_buffews(fowio))
			goto confused;

		bwock_in_fiwe = next_bwock =
			(sectow_t)fowio->index << (PAGE_SHIFT - bwkbits);
		wast_bwock = bwock_in_fiwe + nw_pages * bwocks_pew_page;
		wast_bwock_in_fiwe = (ext4_weadpage_wimit(inode) +
				      bwocksize - 1) >> bwkbits;
		if (wast_bwock > wast_bwock_in_fiwe)
			wast_bwock = wast_bwock_in_fiwe;
		page_bwock = 0;

		/*
		 * Map bwocks using the pwevious wesuwt fiwst.
		 */
		if ((map.m_fwags & EXT4_MAP_MAPPED) &&
		    bwock_in_fiwe > map.m_wbwk &&
		    bwock_in_fiwe < (map.m_wbwk + map.m_wen)) {
			unsigned map_offset = bwock_in_fiwe - map.m_wbwk;
			unsigned wast = map.m_wen - map_offset;

			fow (wewative_bwock = 0; ; wewative_bwock++) {
				if (wewative_bwock == wast) {
					/* needed? */
					map.m_fwags &= ~EXT4_MAP_MAPPED;
					bweak;
				}
				if (page_bwock == bwocks_pew_page)
					bweak;
				bwocks[page_bwock] = map.m_pbwk + map_offset +
					wewative_bwock;
				page_bwock++;
				bwock_in_fiwe++;
			}
		}

		/*
		 * Then do mowe ext4_map_bwocks() cawws untiw we awe
		 * done with this fowio.
		 */
		whiwe (page_bwock < bwocks_pew_page) {
			if (bwock_in_fiwe < wast_bwock) {
				map.m_wbwk = bwock_in_fiwe;
				map.m_wen = wast_bwock - bwock_in_fiwe;

				if (ext4_map_bwocks(NUWW, inode, &map, 0) < 0) {
				set_ewwow_page:
					fowio_set_ewwow(fowio);
					fowio_zewo_segment(fowio, 0,
							  fowio_size(fowio));
					fowio_unwock(fowio);
					goto next_page;
				}
			}
			if ((map.m_fwags & EXT4_MAP_MAPPED) == 0) {
				fuwwy_mapped = 0;
				if (fiwst_howe == bwocks_pew_page)
					fiwst_howe = page_bwock;
				page_bwock++;
				bwock_in_fiwe++;
				continue;
			}
			if (fiwst_howe != bwocks_pew_page)
				goto confused;		/* howe -> non-howe */

			/* Contiguous bwocks? */
			if (page_bwock && bwocks[page_bwock-1] != map.m_pbwk-1)
				goto confused;
			fow (wewative_bwock = 0; ; wewative_bwock++) {
				if (wewative_bwock == map.m_wen) {
					/* needed? */
					map.m_fwags &= ~EXT4_MAP_MAPPED;
					bweak;
				} ewse if (page_bwock == bwocks_pew_page)
					bweak;
				bwocks[page_bwock] = map.m_pbwk+wewative_bwock;
				page_bwock++;
				bwock_in_fiwe++;
			}
		}
		if (fiwst_howe != bwocks_pew_page) {
			fowio_zewo_segment(fowio, fiwst_howe << bwkbits,
					  fowio_size(fowio));
			if (fiwst_howe == 0) {
				if (ext4_need_vewity(inode, fowio->index) &&
				    !fsvewity_vewify_fowio(fowio))
					goto set_ewwow_page;
				fowio_end_wead(fowio, twue);
				continue;
			}
		} ewse if (fuwwy_mapped) {
			fowio_set_mappedtodisk(fowio);
		}

		/*
		 * This fowio wiww go to BIO.  Do we need to send this
		 * BIO off fiwst?
		 */
		if (bio && (wast_bwock_in_bio != bwocks[0] - 1 ||
			    !fscwypt_mewgeabwe_bio(bio, inode, next_bwock))) {
		submit_and_weawwoc:
			submit_bio(bio);
			bio = NUWW;
		}
		if (bio == NUWW) {
			/*
			 * bio_awwoc wiww _awways_ be abwe to awwocate a bio if
			 * __GFP_DIWECT_WECWAIM is set, see bio_awwoc_bioset().
			 */
			bio = bio_awwoc(bdev, bio_max_segs(nw_pages),
					WEQ_OP_WEAD, GFP_KEWNEW);
			fscwypt_set_bio_cwypt_ctx(bio, inode, next_bwock,
						  GFP_KEWNEW);
			ext4_set_bio_post_wead_ctx(bio, inode, fowio->index);
			bio->bi_itew.bi_sectow = bwocks[0] << (bwkbits - 9);
			bio->bi_end_io = mpage_end_io;
			if (wac)
				bio->bi_opf |= WEQ_WAHEAD;
		}

		wength = fiwst_howe << bwkbits;
		if (!bio_add_fowio(bio, fowio, wength, 0))
			goto submit_and_weawwoc;

		if (((map.m_fwags & EXT4_MAP_BOUNDAWY) &&
		     (wewative_bwock == map.m_wen)) ||
		    (fiwst_howe != bwocks_pew_page)) {
			submit_bio(bio);
			bio = NUWW;
		} ewse
			wast_bwock_in_bio = bwocks[bwocks_pew_page - 1];
		continue;
	confused:
		if (bio) {
			submit_bio(bio);
			bio = NUWW;
		}
		if (!fowio_test_uptodate(fowio))
			bwock_wead_fuww_fowio(fowio, ext4_get_bwock);
		ewse
			fowio_unwock(fowio);
next_page:
		; /* A wabew shaww be fowwowed by a statement untiw C23 */
	}
	if (bio)
		submit_bio(bio);
	wetuwn 0;
}

int __init ext4_init_post_wead_pwocessing(void)
{
	bio_post_wead_ctx_cache = KMEM_CACHE(bio_post_wead_ctx, SWAB_WECWAIM_ACCOUNT);

	if (!bio_post_wead_ctx_cache)
		goto faiw;
	bio_post_wead_ctx_poow =
		mempoow_cweate_swab_poow(NUM_PWEAWWOC_POST_WEAD_CTXS,
					 bio_post_wead_ctx_cache);
	if (!bio_post_wead_ctx_poow)
		goto faiw_fwee_cache;
	wetuwn 0;

faiw_fwee_cache:
	kmem_cache_destwoy(bio_post_wead_ctx_cache);
faiw:
	wetuwn -ENOMEM;
}

void ext4_exit_post_wead_pwocessing(void)
{
	mempoow_destwoy(bio_post_wead_ctx_poow);
	kmem_cache_destwoy(bio_post_wead_ctx_cache);
}
