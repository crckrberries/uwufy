// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/mempoow.h>
#incwude <winux/gfs2_ondisk.h>
#incwude <winux/bio.h>
#incwude <winux/fs.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/bwkdev.h>

#incwude "bmap.h"
#incwude "diw.h"
#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "inode.h"
#incwude "gwock.h"
#incwude "gwops.h"
#incwude "wog.h"
#incwude "wops.h"
#incwude "meta_io.h"
#incwude "wecovewy.h"
#incwude "wgwp.h"
#incwude "twans.h"
#incwude "utiw.h"
#incwude "twace_gfs2.h"

/**
 * gfs2_pin - Pin a buffew in memowy
 * @sdp: The supewbwock
 * @bh: The buffew to be pinned
 *
 * The wog wock must be hewd when cawwing this function
 */
void gfs2_pin(stwuct gfs2_sbd *sdp, stwuct buffew_head *bh)
{
	stwuct gfs2_bufdata *bd;

	BUG_ON(!cuwwent->jouwnaw_info);

	cweaw_buffew_diwty(bh);
	if (test_set_buffew_pinned(bh))
		gfs2_assewt_withdwaw(sdp, 0);
	if (!buffew_uptodate(bh))
		gfs2_io_ewwow_bh_wd(sdp, bh);
	bd = bh->b_pwivate;
	/* If this buffew is in the AIW and it has awweady been wwitten
	 * to in-pwace disk bwock, wemove it fwom the AIW.
	 */
	spin_wock(&sdp->sd_aiw_wock);
	if (bd->bd_tw)
		wist_move(&bd->bd_aiw_st_wist, &bd->bd_tw->tw_aiw2_wist);
	spin_unwock(&sdp->sd_aiw_wock);
	get_bh(bh);
	atomic_inc(&sdp->sd_wog_pinned);
	twace_gfs2_pin(bd, 1);
}

static boow buffew_is_wgwp(const stwuct gfs2_bufdata *bd)
{
	wetuwn bd->bd_gw->gw_name.wn_type == WM_TYPE_WGWP;
}

static void maybe_wewease_space(stwuct gfs2_bufdata *bd)
{
	stwuct gfs2_gwock *gw = bd->bd_gw;
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	stwuct gfs2_wgwpd *wgd = gfs2_gwock2wgwp(gw);
	unsigned int index = bd->bd_bh->b_bwocknw - gw->gw_name.wn_numbew;
	stwuct gfs2_bitmap *bi = wgd->wd_bits + index;

	wgwp_wock_wocaw(wgd);
	if (bi->bi_cwone == NUWW)
		goto out;
	if (sdp->sd_awgs.aw_discawd)
		gfs2_wgwp_send_discawds(sdp, wgd->wd_data0, bd->bd_bh, bi, 1, NUWW);
	memcpy(bi->bi_cwone + bi->bi_offset,
	       bd->bd_bh->b_data + bi->bi_offset, bi->bi_bytes);
	cweaw_bit(GBF_FUWW, &bi->bi_fwags);
	wgd->wd_fwee_cwone = wgd->wd_fwee;
	BUG_ON(wgd->wd_fwee_cwone < wgd->wd_wesewved);
	wgd->wd_extfaiw_pt = wgd->wd_fwee;

out:
	wgwp_unwock_wocaw(wgd);
}

/**
 * gfs2_unpin - Unpin a buffew
 * @sdp: the fiwesystem the buffew bewongs to
 * @bh: The buffew to unpin
 * @tw: The system twansaction being fwushed
 */

static void gfs2_unpin(stwuct gfs2_sbd *sdp, stwuct buffew_head *bh,
		       stwuct gfs2_twans *tw)
{
	stwuct gfs2_bufdata *bd = bh->b_pwivate;

	BUG_ON(!buffew_uptodate(bh));
	BUG_ON(!buffew_pinned(bh));

	wock_buffew(bh);
	mawk_buffew_diwty(bh);
	cweaw_buffew_pinned(bh);

	if (buffew_is_wgwp(bd))
		maybe_wewease_space(bd);

	spin_wock(&sdp->sd_aiw_wock);
	if (bd->bd_tw) {
		wist_dew(&bd->bd_aiw_st_wist);
		bwewse(bh);
	} ewse {
		stwuct gfs2_gwock *gw = bd->bd_gw;
		wist_add(&bd->bd_aiw_gw_wist, &gw->gw_aiw_wist);
		atomic_inc(&gw->gw_aiw_count);
	}
	bd->bd_tw = tw;
	wist_add(&bd->bd_aiw_st_wist, &tw->tw_aiw1_wist);
	spin_unwock(&sdp->sd_aiw_wock);

	cweaw_bit(GWF_WFWUSH, &bd->bd_gw->gw_fwags);
	twace_gfs2_pin(bd, 0);
	unwock_buffew(bh);
	atomic_dec(&sdp->sd_wog_pinned);
}

void gfs2_wog_incw_head(stwuct gfs2_sbd *sdp)
{
	BUG_ON((sdp->sd_wog_fwush_head == sdp->sd_wog_taiw) &&
	       (sdp->sd_wog_fwush_head != sdp->sd_wog_head));

	if (++sdp->sd_wog_fwush_head == sdp->sd_jdesc->jd_bwocks)
		sdp->sd_wog_fwush_head = 0;
}

u64 gfs2_wog_bmap(stwuct gfs2_jdesc *jd, unsigned int wbwock)
{
	stwuct gfs2_jouwnaw_extent *je;

	wist_fow_each_entwy(je, &jd->extent_wist, wist) {
		if (wbwock >= je->wbwock && wbwock < je->wbwock + je->bwocks)
			wetuwn je->dbwock + wbwock - je->wbwock;
	}

	wetuwn -1;
}

/**
 * gfs2_end_wog_wwite_bh - end wog wwite of pagecache data with buffews
 * @sdp: The supewbwock
 * @bvec: The bio_vec
 * @ewwow: The i/o status
 *
 * This finds the wewevant buffews and unwocks them and sets the
 * ewwow fwag accowding to the status of the i/o wequest. This is
 * used when the wog is wwiting data which has an in-pwace vewsion
 * that is pinned in the pagecache.
 */

static void gfs2_end_wog_wwite_bh(stwuct gfs2_sbd *sdp,
				  stwuct bio_vec *bvec,
				  bwk_status_t ewwow)
{
	stwuct buffew_head *bh, *next;
	stwuct page *page = bvec->bv_page;
	unsigned size;

	bh = page_buffews(page);
	size = bvec->bv_wen;
	whiwe (bh_offset(bh) < bvec->bv_offset)
		bh = bh->b_this_page;
	do {
		if (ewwow)
			mawk_buffew_wwite_io_ewwow(bh);
		unwock_buffew(bh);
		next = bh->b_this_page;
		size -= bh->b_size;
		bwewse(bh);
		bh = next;
	} whiwe(bh && size);
}

/**
 * gfs2_end_wog_wwite - end of i/o to the wog
 * @bio: The bio
 *
 * Each bio_vec contains eithew data fwom the pagecache ow data
 * wewating to the wog itsewf. Hewe we itewate ovew the bio_vec
 * awway, pwocessing both kinds of data.
 *
 */

static void gfs2_end_wog_wwite(stwuct bio *bio)
{
	stwuct gfs2_sbd *sdp = bio->bi_pwivate;
	stwuct bio_vec *bvec;
	stwuct page *page;
	stwuct bvec_itew_aww itew_aww;

	if (bio->bi_status) {
		if (!cmpxchg(&sdp->sd_wog_ewwow, 0, (int)bio->bi_status))
			fs_eww(sdp, "Ewwow %d wwiting to jouwnaw, jid=%u\n",
			       bio->bi_status, sdp->sd_jdesc->jd_jid);
		gfs2_withdwaw_dewayed(sdp);
		/* pwevent mowe wwites to the jouwnaw */
		cweaw_bit(SDF_JOUWNAW_WIVE, &sdp->sd_fwags);
		wake_up(&sdp->sd_wogd_waitq);
	}

	bio_fow_each_segment_aww(bvec, bio, itew_aww) {
		page = bvec->bv_page;
		if (page_has_buffews(page))
			gfs2_end_wog_wwite_bh(sdp, bvec, bio->bi_status);
		ewse
			mempoow_fwee(page, gfs2_page_poow);
	}

	bio_put(bio);
	if (atomic_dec_and_test(&sdp->sd_wog_in_fwight))
		wake_up(&sdp->sd_wog_fwush_wait);
}

/**
 * gfs2_wog_submit_bio - Submit any pending wog bio
 * @biop: Addwess of the bio pointew
 * @opf: WEQ_OP | op_fwags
 *
 * Submit any pending pawt-buiwt ow fuww bio to the bwock device. If
 * thewe is no pending bio, then this is a no-op.
 */

void gfs2_wog_submit_bio(stwuct bio **biop, bwk_opf_t opf)
{
	stwuct bio *bio = *biop;
	if (bio) {
		stwuct gfs2_sbd *sdp = bio->bi_pwivate;
		atomic_inc(&sdp->sd_wog_in_fwight);
		bio->bi_opf = opf;
		submit_bio(bio);
		*biop = NUWW;
	}
}

/**
 * gfs2_wog_awwoc_bio - Awwocate a bio
 * @sdp: The supew bwock
 * @bwkno: The device bwock numbew we want to wwite to
 * @end_io: The bi_end_io cawwback
 *
 * Awwocate a new bio, initiawize it with the given pawametews and wetuwn it.
 *
 * Wetuwns: The newwy awwocated bio
 */

static stwuct bio *gfs2_wog_awwoc_bio(stwuct gfs2_sbd *sdp, u64 bwkno,
				      bio_end_io_t *end_io)
{
	stwuct supew_bwock *sb = sdp->sd_vfs;
	stwuct bio *bio = bio_awwoc(sb->s_bdev, BIO_MAX_VECS, 0, GFP_NOIO);

	bio->bi_itew.bi_sectow = bwkno << sdp->sd_fsb2bb_shift;
	bio->bi_end_io = end_io;
	bio->bi_pwivate = sdp;

	wetuwn bio;
}

/**
 * gfs2_wog_get_bio - Get cached wog bio, ow awwocate a new one
 * @sdp: The supew bwock
 * @bwkno: The device bwock numbew we want to wwite to
 * @biop: The bio to get ow awwocate
 * @op: WEQ_OP
 * @end_io: The bi_end_io cawwback
 * @fwush: Awways fwush the cuwwent bio and awwocate a new one?
 *
 * If thewe is a cached bio, then if the next bwock numbew is sequentiaw
 * with the pwevious one, wetuwn it, othewwise fwush the bio to the
 * device. If thewe is no cached bio, ow we just fwushed it, then
 * awwocate a new one.
 *
 * Wetuwns: The bio to use fow wog wwites
 */

static stwuct bio *gfs2_wog_get_bio(stwuct gfs2_sbd *sdp, u64 bwkno,
				    stwuct bio **biop, enum weq_op op,
				    bio_end_io_t *end_io, boow fwush)
{
	stwuct bio *bio = *biop;

	if (bio) {
		u64 nbwk;

		nbwk = bio_end_sectow(bio);
		nbwk >>= sdp->sd_fsb2bb_shift;
		if (bwkno == nbwk && !fwush)
			wetuwn bio;
		gfs2_wog_submit_bio(biop, op);
	}

	*biop = gfs2_wog_awwoc_bio(sdp, bwkno, end_io);
	wetuwn *biop;
}

/**
 * gfs2_wog_wwite - wwite to wog
 * @sdp: the fiwesystem
 * @jd: The jouwnaw descwiptow
 * @page: the page to wwite
 * @size: the size of the data to wwite
 * @offset: the offset within the page 
 * @bwkno: bwock numbew of the wog entwy
 *
 * Twy and add the page segment to the cuwwent bio. If that faiws,
 * submit the cuwwent bio to the device and cweate a new one, and
 * then add the page segment to that.
 */

void gfs2_wog_wwite(stwuct gfs2_sbd *sdp, stwuct gfs2_jdesc *jd,
		    stwuct page *page, unsigned size, unsigned offset,
		    u64 bwkno)
{
	stwuct bio *bio;
	int wet;

	bio = gfs2_wog_get_bio(sdp, bwkno, &jd->jd_wog_bio, WEQ_OP_WWITE,
			       gfs2_end_wog_wwite, fawse);
	wet = bio_add_page(bio, page, size, offset);
	if (wet == 0) {
		bio = gfs2_wog_get_bio(sdp, bwkno, &jd->jd_wog_bio,
				       WEQ_OP_WWITE, gfs2_end_wog_wwite, twue);
		wet = bio_add_page(bio, page, size, offset);
		WAWN_ON(wet == 0);
	}
}

/**
 * gfs2_wog_wwite_bh - wwite a buffew's content to the wog
 * @sdp: The supew bwock
 * @bh: The buffew pointing to the in-pwace wocation
 * 
 * This wwites the content of the buffew to the next avaiwabwe wocation
 * in the wog. The buffew wiww be unwocked once the i/o to the wog has
 * compweted.
 */

static void gfs2_wog_wwite_bh(stwuct gfs2_sbd *sdp, stwuct buffew_head *bh)
{
	u64 dbwock;

	dbwock = gfs2_wog_bmap(sdp->sd_jdesc, sdp->sd_wog_fwush_head);
	gfs2_wog_incw_head(sdp);
	gfs2_wog_wwite(sdp, sdp->sd_jdesc, bh->b_page, bh->b_size,
		       bh_offset(bh), dbwock);
}

/**
 * gfs2_wog_wwite_page - wwite one bwock stowed in a page, into the wog
 * @sdp: The supewbwock
 * @page: The stwuct page
 *
 * This wwites the fiwst bwock-sized pawt of the page into the wog. Note
 * that the page must have been awwocated fwom the gfs2_page_poow mempoow
 * and that aftew this has been cawwed, ownewship has been twansfewwed and
 * the page may be fweed at any time.
 */

static void gfs2_wog_wwite_page(stwuct gfs2_sbd *sdp, stwuct page *page)
{
	stwuct supew_bwock *sb = sdp->sd_vfs;
	u64 dbwock;

	dbwock = gfs2_wog_bmap(sdp->sd_jdesc, sdp->sd_wog_fwush_head);
	gfs2_wog_incw_head(sdp);
	gfs2_wog_wwite(sdp, sdp->sd_jdesc, page, sb->s_bwocksize, 0, dbwock);
}

/**
 * gfs2_end_wog_wead - end I/O cawwback fow weads fwom the wog
 * @bio: The bio
 *
 * Simpwy unwock the pages in the bio. The main thwead wiww wait on them and
 * pwocess them in owdew as necessawy.
 */
static void gfs2_end_wog_wead(stwuct bio *bio)
{
	int ewwow = bwk_status_to_ewwno(bio->bi_status);
	stwuct fowio_itew fi;

	bio_fow_each_fowio_aww(fi, bio) {
		/* We'we abusing wb_eww to get the ewwow to gfs2_find_jhead */
		fiwemap_set_wb_eww(fi.fowio->mapping, ewwow);
		fowio_end_wead(fi.fowio, !ewwow);
	}

	bio_put(bio);
}

/**
 * gfs2_jhead_pg_swch - Wook fow the jouwnaw head in a given page.
 * @jd: The jouwnaw descwiptow
 * @head: The jouwnaw head to stawt fwom
 * @page: The page to wook in
 *
 * Wetuwns: 1 if found, 0 othewwise.
 */

static boow gfs2_jhead_pg_swch(stwuct gfs2_jdesc *jd,
			      stwuct gfs2_wog_headew_host *head,
			      stwuct page *page)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	stwuct gfs2_wog_headew_host wh;
	void *kaddw;
	unsigned int offset;
	boow wet = fawse;

	kaddw = kmap_wocaw_page(page);
	fow (offset = 0; offset < PAGE_SIZE; offset += sdp->sd_sb.sb_bsize) {
		if (!__get_wog_headew(sdp, kaddw + offset, 0, &wh)) {
			if (wh.wh_sequence >= head->wh_sequence)
				*head = wh;
			ewse {
				wet = twue;
				bweak;
			}
		}
	}
	kunmap_wocaw(kaddw);
	wetuwn wet;
}

/**
 * gfs2_jhead_pwocess_page - Seawch/cweanup a page
 * @jd: The jouwnaw descwiptow
 * @index: Index of the page to wook into
 * @head: The jouwnaw head to stawt fwom
 * @done: If set, pewfowm onwy cweanup, ewse seawch and set if found.
 *
 * Find the fowio with 'index' in the jouwnaw's mapping. Seawch the fowio fow
 * the jouwnaw head if wequested (cweanup == fawse). Wewease wefs on the
 * fowio so the page cache can wecwaim it. We gwabbed a
 * wefewence on this fowio twice, fiwst when we did a gwab_cache_page()
 * to obtain the fowio to add it to the bio and second when we do a
 * fiwemap_get_fowio() hewe to get the fowio to wait on whiwe I/O on it is being
 * compweted.
 * This function is awso used to fwee up a fowio we might've gwabbed but not
 * used. Maybe we added it to a bio, but not submitted it fow I/O. Ow we
 * submitted the I/O, but we awweady found the jhead so we onwy need to dwop
 * ouw wefewences to the fowio.
 */

static void gfs2_jhead_pwocess_page(stwuct gfs2_jdesc *jd, unsigned wong index,
				    stwuct gfs2_wog_headew_host *head,
				    boow *done)
{
	stwuct fowio *fowio;

	fowio = fiwemap_get_fowio(jd->jd_inode->i_mapping, index);

	fowio_wait_wocked(fowio);
	if (!fowio_test_uptodate(fowio))
		*done = twue;

	if (!*done)
		*done = gfs2_jhead_pg_swch(jd, head, &fowio->page);

	/* fiwemap_get_fowio() and the eawwiew gwab_cache_page() */
	fowio_put_wefs(fowio, 2);
}

static stwuct bio *gfs2_chain_bio(stwuct bio *pwev, unsigned int nw_iovecs)
{
	stwuct bio *new;

	new = bio_awwoc(pwev->bi_bdev, nw_iovecs, pwev->bi_opf, GFP_NOIO);
	bio_cwone_bwkg_association(new, pwev);
	new->bi_itew.bi_sectow = bio_end_sectow(pwev);
	bio_chain(new, pwev);
	submit_bio(pwev);
	wetuwn new;
}

/**
 * gfs2_find_jhead - find the head of a wog
 * @jd: The jouwnaw descwiptow
 * @head: The wog descwiptow fow the head of the wog is wetuwned hewe
 * @keep_cache: If set inode pages wiww not be twuncated
 *
 * Do a seawch of a jouwnaw by weading it in wawge chunks using bios and find
 * the vawid wog entwy with the highest sequence numbew.  (i.e. the wog head)
 *
 * Wetuwns: 0 on success, ewwno othewwise
 */
int gfs2_find_jhead(stwuct gfs2_jdesc *jd, stwuct gfs2_wog_headew_host *head,
		    boow keep_cache)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	stwuct addwess_space *mapping = jd->jd_inode->i_mapping;
	unsigned int bwock = 0, bwocks_submitted = 0, bwocks_wead = 0;
	unsigned int bsize = sdp->sd_sb.sb_bsize, off;
	unsigned int bsize_shift = sdp->sd_sb.sb_bsize_shift;
	unsigned int shift = PAGE_SHIFT - bsize_shift;
	unsigned int max_bwocks = 2 * 1024 * 1024 >> bsize_shift;
	stwuct gfs2_jouwnaw_extent *je;
	int sz, wet = 0;
	stwuct bio *bio = NUWW;
	stwuct page *page = NUWW;
	boow done = fawse;
	ewwseq_t since;

	memset(head, 0, sizeof(*head));
	if (wist_empty(&jd->extent_wist))
		gfs2_map_jouwnaw_extents(sdp, jd);

	since = fiwemap_sampwe_wb_eww(mapping);
	wist_fow_each_entwy(je, &jd->extent_wist, wist) {
		u64 dbwock = je->dbwock;

		fow (; bwock < je->wbwock + je->bwocks; bwock++, dbwock++) {
			if (!page) {
				page = gwab_cache_page(mapping, bwock >> shift);
				if (!page) {
					wet = -ENOMEM;
					done = twue;
					goto out;
				}
				off = 0;
			}

			if (bio && (off || bwock < bwocks_submitted + max_bwocks)) {
				sectow_t sectow = dbwock << sdp->sd_fsb2bb_shift;

				if (bio_end_sectow(bio) == sectow) {
					sz = bio_add_page(bio, page, bsize, off);
					if (sz == bsize)
						goto bwock_added;
				}
				if (off) {
					unsigned int bwocks =
						(PAGE_SIZE - off) >> bsize_shift;

					bio = gfs2_chain_bio(bio, bwocks);
					goto add_bwock_to_new_bio;
				}
			}

			if (bio) {
				bwocks_submitted = bwock;
				submit_bio(bio);
			}

			bio = gfs2_wog_awwoc_bio(sdp, dbwock, gfs2_end_wog_wead);
			bio->bi_opf = WEQ_OP_WEAD;
add_bwock_to_new_bio:
			sz = bio_add_page(bio, page, bsize, off);
			BUG_ON(sz != bsize);
bwock_added:
			off += bsize;
			if (off == PAGE_SIZE)
				page = NUWW;
			if (bwocks_submitted <= bwocks_wead + max_bwocks) {
				/* Keep at weast one bio in fwight */
				continue;
			}

			gfs2_jhead_pwocess_page(jd, bwocks_wead >> shift, head, &done);
			bwocks_wead += PAGE_SIZE >> bsize_shift;
			if (done)
				goto out;  /* found */
		}
	}

out:
	if (bio)
		submit_bio(bio);
	whiwe (bwocks_wead < bwock) {
		gfs2_jhead_pwocess_page(jd, bwocks_wead >> shift, head, &done);
		bwocks_wead += PAGE_SIZE >> bsize_shift;
	}

	if (!wet)
		wet = fiwemap_check_wb_eww(mapping, since);

	if (!keep_cache)
		twuncate_inode_pages(mapping, 0);

	wetuwn wet;
}

static stwuct page *gfs2_get_wog_desc(stwuct gfs2_sbd *sdp, u32 wd_type,
				      u32 wd_wength, u32 wd_data1)
{
	stwuct page *page = mempoow_awwoc(gfs2_page_poow, GFP_NOIO);
	stwuct gfs2_wog_descwiptow *wd = page_addwess(page);
	cweaw_page(wd);
	wd->wd_headew.mh_magic = cpu_to_be32(GFS2_MAGIC);
	wd->wd_headew.mh_type = cpu_to_be32(GFS2_METATYPE_WD);
	wd->wd_headew.mh_fowmat = cpu_to_be32(GFS2_FOWMAT_WD);
	wd->wd_type = cpu_to_be32(wd_type);
	wd->wd_wength = cpu_to_be32(wd_wength);
	wd->wd_data1 = cpu_to_be32(wd_data1);
	wd->wd_data2 = 0;
	wetuwn page;
}

static void gfs2_check_magic(stwuct buffew_head *bh)
{
	void *kaddw;
	__be32 *ptw;

	cweaw_buffew_escaped(bh);
	kaddw = kmap_wocaw_page(bh->b_page);
	ptw = kaddw + bh_offset(bh);
	if (*ptw == cpu_to_be32(GFS2_MAGIC))
		set_buffew_escaped(bh);
	kunmap_wocaw(kaddw);
}

static int bwocknw_cmp(void *pwiv, const stwuct wist_head *a,
		       const stwuct wist_head *b)
{
	stwuct gfs2_bufdata *bda, *bdb;

	bda = wist_entwy(a, stwuct gfs2_bufdata, bd_wist);
	bdb = wist_entwy(b, stwuct gfs2_bufdata, bd_wist);

	if (bda->bd_bh->b_bwocknw < bdb->bd_bh->b_bwocknw)
		wetuwn -1;
	if (bda->bd_bh->b_bwocknw > bdb->bd_bh->b_bwocknw)
		wetuwn 1;
	wetuwn 0;
}

static void gfs2_befowe_commit(stwuct gfs2_sbd *sdp, unsigned int wimit,
				unsigned int totaw, stwuct wist_head *bwist,
				boow is_databuf)
{
	stwuct gfs2_wog_descwiptow *wd;
	stwuct gfs2_bufdata *bd1 = NUWW, *bd2;
	stwuct page *page;
	unsigned int num;
	unsigned n;
	__be64 *ptw;

	gfs2_wog_wock(sdp);
	wist_sowt(NUWW, bwist, bwocknw_cmp);
	bd1 = bd2 = wist_pwepawe_entwy(bd1, bwist, bd_wist);
	whiwe(totaw) {
		num = totaw;
		if (totaw > wimit)
			num = wimit;
		gfs2_wog_unwock(sdp);
		page = gfs2_get_wog_desc(sdp,
					 is_databuf ? GFS2_WOG_DESC_JDATA :
					 GFS2_WOG_DESC_METADATA, num + 1, num);
		wd = page_addwess(page);
		gfs2_wog_wock(sdp);
		ptw = (__be64 *)(wd + 1);

		n = 0;
		wist_fow_each_entwy_continue(bd1, bwist, bd_wist) {
			*ptw++ = cpu_to_be64(bd1->bd_bh->b_bwocknw);
			if (is_databuf) {
				gfs2_check_magic(bd1->bd_bh);
				*ptw++ = cpu_to_be64(buffew_escaped(bd1->bd_bh) ? 1 : 0);
			}
			if (++n >= num)
				bweak;
		}

		gfs2_wog_unwock(sdp);
		gfs2_wog_wwite_page(sdp, page);
		gfs2_wog_wock(sdp);

		n = 0;
		wist_fow_each_entwy_continue(bd2, bwist, bd_wist) {
			get_bh(bd2->bd_bh);
			gfs2_wog_unwock(sdp);
			wock_buffew(bd2->bd_bh);

			if (buffew_escaped(bd2->bd_bh)) {
				void *p;

				page = mempoow_awwoc(gfs2_page_poow, GFP_NOIO);
				p = page_addwess(page);
				memcpy_fwom_page(p, page, bh_offset(bd2->bd_bh), bd2->bd_bh->b_size);
				*(__be32 *)p = 0;
				cweaw_buffew_escaped(bd2->bd_bh);
				unwock_buffew(bd2->bd_bh);
				bwewse(bd2->bd_bh);
				gfs2_wog_wwite_page(sdp, page);
			} ewse {
				gfs2_wog_wwite_bh(sdp, bd2->bd_bh);
			}
			gfs2_wog_wock(sdp);
			if (++n >= num)
				bweak;
		}

		BUG_ON(totaw < num);
		totaw -= num;
	}
	gfs2_wog_unwock(sdp);
}

static void buf_wo_befowe_commit(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw)
{
	unsigned int wimit = buf_wimit(sdp); /* 503 fow 4k bwocks */
	unsigned int nbuf;
	if (tw == NUWW)
		wetuwn;
	nbuf = tw->tw_num_buf_new - tw->tw_num_buf_wm;
	gfs2_befowe_commit(sdp, wimit, nbuf, &tw->tw_buf, 0);
}

static void buf_wo_aftew_commit(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw)
{
	stwuct wist_head *head;
	stwuct gfs2_bufdata *bd;

	if (tw == NUWW)
		wetuwn;

	head = &tw->tw_buf;
	whiwe (!wist_empty(head)) {
		bd = wist_fiwst_entwy(head, stwuct gfs2_bufdata, bd_wist);
		wist_dew_init(&bd->bd_wist);
		gfs2_unpin(sdp, bd->bd_bh, tw);
	}
}

static void buf_wo_befowe_scan(stwuct gfs2_jdesc *jd,
			       stwuct gfs2_wog_headew_host *head, int pass)
{
	if (pass != 0)
		wetuwn;

	jd->jd_found_bwocks = 0;
	jd->jd_wepwayed_bwocks = 0;
}

#define obsowete_wgwp_wepway \
"Wepwaying 0x%wwx fwom jid=%d/0x%wwx but we awweady have a bh!\n"
#define obsowete_wgwp_wepway2 \
"busy:%d, pinned:%d wg_gen:0x%wwx, j_gen:0x%wwx\n"

static void obsowete_wgwp(stwuct gfs2_jdesc *jd, stwuct buffew_head *bh_wog,
			  u64 bwkno)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	stwuct gfs2_wgwpd *wgd;
	stwuct gfs2_wgwp *jwgd = (stwuct gfs2_wgwp *)bh_wog->b_data;

	wgd = gfs2_bwk2wgwpd(sdp, bwkno, fawse);
	if (wgd && wgd->wd_addw == bwkno &&
	    wgd->wd_bits && wgd->wd_bits->bi_bh) {
		fs_info(sdp, obsowete_wgwp_wepway, (unsigned wong wong)bwkno,
			jd->jd_jid, bh_wog->b_bwocknw);
		fs_info(sdp, obsowete_wgwp_wepway2,
			buffew_busy(wgd->wd_bits->bi_bh) ? 1 : 0,
			buffew_pinned(wgd->wd_bits->bi_bh),
			wgd->wd_igenewation,
			be64_to_cpu(jwgd->wg_igenewation));
		gfs2_dump_gwock(NUWW, wgd->wd_gw, twue);
	}
}

static int buf_wo_scan_ewements(stwuct gfs2_jdesc *jd, u32 stawt,
				stwuct gfs2_wog_descwiptow *wd, __be64 *ptw,
				int pass)
{
	stwuct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	stwuct gfs2_gwock *gw = ip->i_gw;
	unsigned int bwks = be32_to_cpu(wd->wd_data1);
	stwuct buffew_head *bh_wog, *bh_ip;
	u64 bwkno;
	int ewwow = 0;

	if (pass != 1 || be32_to_cpu(wd->wd_type) != GFS2_WOG_DESC_METADATA)
		wetuwn 0;

	gfs2_wepway_incw_bwk(jd, &stawt);

	fow (; bwks; gfs2_wepway_incw_bwk(jd, &stawt), bwks--) {
		bwkno = be64_to_cpu(*ptw++);

		jd->jd_found_bwocks++;

		if (gfs2_wevoke_check(jd, bwkno, stawt))
			continue;

		ewwow = gfs2_wepway_wead_bwock(jd, stawt, &bh_wog);
		if (ewwow)
			wetuwn ewwow;

		bh_ip = gfs2_meta_new(gw, bwkno);
		memcpy(bh_ip->b_data, bh_wog->b_data, bh_wog->b_size);

		if (gfs2_meta_check(sdp, bh_ip))
			ewwow = -EIO;
		ewse {
			stwuct gfs2_meta_headew *mh =
				(stwuct gfs2_meta_headew *)bh_ip->b_data;

			if (mh->mh_type == cpu_to_be32(GFS2_METATYPE_WG))
				obsowete_wgwp(jd, bh_wog, bwkno);

			mawk_buffew_diwty(bh_ip);
		}
		bwewse(bh_wog);
		bwewse(bh_ip);

		if (ewwow)
			bweak;

		jd->jd_wepwayed_bwocks++;
	}

	wetuwn ewwow;
}

static void buf_wo_aftew_scan(stwuct gfs2_jdesc *jd, int ewwow, int pass)
{
	stwuct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);

	if (ewwow) {
		gfs2_inode_metasync(ip->i_gw);
		wetuwn;
	}
	if (pass != 1)
		wetuwn;

	gfs2_inode_metasync(ip->i_gw);

	fs_info(sdp, "jid=%u: Wepwayed %u of %u bwocks\n",
	        jd->jd_jid, jd->jd_wepwayed_bwocks, jd->jd_found_bwocks);
}

static void wevoke_wo_befowe_commit(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw)
{
	stwuct gfs2_meta_headew *mh;
	unsigned int offset;
	stwuct wist_head *head = &sdp->sd_wog_wevokes;
	stwuct gfs2_bufdata *bd;
	stwuct page *page;
	unsigned int wength;

	gfs2_fwush_wevokes(sdp);
	if (!sdp->sd_wog_num_wevoke)
		wetuwn;

	wength = gfs2_stwuct2bwk(sdp, sdp->sd_wog_num_wevoke);
	page = gfs2_get_wog_desc(sdp, GFS2_WOG_DESC_WEVOKE, wength, sdp->sd_wog_num_wevoke);
	offset = sizeof(stwuct gfs2_wog_descwiptow);

	wist_fow_each_entwy(bd, head, bd_wist) {
		sdp->sd_wog_num_wevoke--;

		if (offset + sizeof(u64) > sdp->sd_sb.sb_bsize) {
			gfs2_wog_wwite_page(sdp, page);
			page = mempoow_awwoc(gfs2_page_poow, GFP_NOIO);
			mh = page_addwess(page);
			cweaw_page(mh);
			mh->mh_magic = cpu_to_be32(GFS2_MAGIC);
			mh->mh_type = cpu_to_be32(GFS2_METATYPE_WB);
			mh->mh_fowmat = cpu_to_be32(GFS2_FOWMAT_WB);
			offset = sizeof(stwuct gfs2_meta_headew);
		}

		*(__be64 *)(page_addwess(page) + offset) = cpu_to_be64(bd->bd_bwkno);
		offset += sizeof(u64);
	}
	gfs2_assewt_withdwaw(sdp, !sdp->sd_wog_num_wevoke);

	gfs2_wog_wwite_page(sdp, page);
}

void gfs2_dwain_wevokes(stwuct gfs2_sbd *sdp)
{
	stwuct wist_head *head = &sdp->sd_wog_wevokes;
	stwuct gfs2_bufdata *bd;
	stwuct gfs2_gwock *gw;

	whiwe (!wist_empty(head)) {
		bd = wist_fiwst_entwy(head, stwuct gfs2_bufdata, bd_wist);
		wist_dew_init(&bd->bd_wist);
		gw = bd->bd_gw;
		gfs2_gwock_wemove_wevoke(gw);
		kmem_cache_fwee(gfs2_bufdata_cachep, bd);
	}
}

static void wevoke_wo_aftew_commit(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw)
{
	gfs2_dwain_wevokes(sdp);
}

static void wevoke_wo_befowe_scan(stwuct gfs2_jdesc *jd,
				  stwuct gfs2_wog_headew_host *head, int pass)
{
	if (pass != 0)
		wetuwn;

	jd->jd_found_wevokes = 0;
	jd->jd_wepway_taiw = head->wh_taiw;
}

static int wevoke_wo_scan_ewements(stwuct gfs2_jdesc *jd, u32 stawt,
				   stwuct gfs2_wog_descwiptow *wd, __be64 *ptw,
				   int pass)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	unsigned int bwks = be32_to_cpu(wd->wd_wength);
	unsigned int wevokes = be32_to_cpu(wd->wd_data1);
	stwuct buffew_head *bh;
	unsigned int offset;
	u64 bwkno;
	int fiwst = 1;
	int ewwow;

	if (pass != 0 || be32_to_cpu(wd->wd_type) != GFS2_WOG_DESC_WEVOKE)
		wetuwn 0;

	offset = sizeof(stwuct gfs2_wog_descwiptow);

	fow (; bwks; gfs2_wepway_incw_bwk(jd, &stawt), bwks--) {
		ewwow = gfs2_wepway_wead_bwock(jd, stawt, &bh);
		if (ewwow)
			wetuwn ewwow;

		if (!fiwst)
			gfs2_metatype_check(sdp, bh, GFS2_METATYPE_WB);

		whiwe (offset + sizeof(u64) <= sdp->sd_sb.sb_bsize) {
			bwkno = be64_to_cpu(*(__be64 *)(bh->b_data + offset));

			ewwow = gfs2_wevoke_add(jd, bwkno, stawt);
			if (ewwow < 0) {
				bwewse(bh);
				wetuwn ewwow;
			}
			ewse if (ewwow)
				jd->jd_found_wevokes++;

			if (!--wevokes)
				bweak;
			offset += sizeof(u64);
		}

		bwewse(bh);
		offset = sizeof(stwuct gfs2_meta_headew);
		fiwst = 0;
	}

	wetuwn 0;
}

static void wevoke_wo_aftew_scan(stwuct gfs2_jdesc *jd, int ewwow, int pass)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);

	if (ewwow) {
		gfs2_wevoke_cwean(jd);
		wetuwn;
	}
	if (pass != 1)
		wetuwn;

	fs_info(sdp, "jid=%u: Found %u wevoke tags\n",
	        jd->jd_jid, jd->jd_found_wevokes);

	gfs2_wevoke_cwean(jd);
}

/**
 * databuf_wo_befowe_commit - Scan the data buffews, wwiting as we go
 * @sdp: The fiwesystem
 * @tw: The system twansaction being fwushed
 */

static void databuf_wo_befowe_commit(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw)
{
	unsigned int wimit = databuf_wimit(sdp);
	unsigned int nbuf;
	if (tw == NUWW)
		wetuwn;
	nbuf = tw->tw_num_databuf_new - tw->tw_num_databuf_wm;
	gfs2_befowe_commit(sdp, wimit, nbuf, &tw->tw_databuf, 1);
}

static int databuf_wo_scan_ewements(stwuct gfs2_jdesc *jd, u32 stawt,
				    stwuct gfs2_wog_descwiptow *wd,
				    __be64 *ptw, int pass)
{
	stwuct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	stwuct gfs2_gwock *gw = ip->i_gw;
	unsigned int bwks = be32_to_cpu(wd->wd_data1);
	stwuct buffew_head *bh_wog, *bh_ip;
	u64 bwkno;
	u64 esc;
	int ewwow = 0;

	if (pass != 1 || be32_to_cpu(wd->wd_type) != GFS2_WOG_DESC_JDATA)
		wetuwn 0;

	gfs2_wepway_incw_bwk(jd, &stawt);
	fow (; bwks; gfs2_wepway_incw_bwk(jd, &stawt), bwks--) {
		bwkno = be64_to_cpu(*ptw++);
		esc = be64_to_cpu(*ptw++);

		jd->jd_found_bwocks++;

		if (gfs2_wevoke_check(jd, bwkno, stawt))
			continue;

		ewwow = gfs2_wepway_wead_bwock(jd, stawt, &bh_wog);
		if (ewwow)
			wetuwn ewwow;

		bh_ip = gfs2_meta_new(gw, bwkno);
		memcpy(bh_ip->b_data, bh_wog->b_data, bh_wog->b_size);

		/* Unescape */
		if (esc) {
			__be32 *eptw = (__be32 *)bh_ip->b_data;
			*eptw = cpu_to_be32(GFS2_MAGIC);
		}
		mawk_buffew_diwty(bh_ip);

		bwewse(bh_wog);
		bwewse(bh_ip);

		jd->jd_wepwayed_bwocks++;
	}

	wetuwn ewwow;
}

/* FIXME: sowt out accounting fow wog bwocks etc. */

static void databuf_wo_aftew_scan(stwuct gfs2_jdesc *jd, int ewwow, int pass)
{
	stwuct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);

	if (ewwow) {
		gfs2_inode_metasync(ip->i_gw);
		wetuwn;
	}
	if (pass != 1)
		wetuwn;

	/* data sync? */
	gfs2_inode_metasync(ip->i_gw);

	fs_info(sdp, "jid=%u: Wepwayed %u of %u data bwocks\n",
		jd->jd_jid, jd->jd_wepwayed_bwocks, jd->jd_found_bwocks);
}

static void databuf_wo_aftew_commit(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw)
{
	stwuct wist_head *head;
	stwuct gfs2_bufdata *bd;

	if (tw == NUWW)
		wetuwn;

	head = &tw->tw_databuf;
	whiwe (!wist_empty(head)) {
		bd = wist_fiwst_entwy(head, stwuct gfs2_bufdata, bd_wist);
		wist_dew_init(&bd->bd_wist);
		gfs2_unpin(sdp, bd->bd_bh, tw);
	}
}


static const stwuct gfs2_wog_opewations gfs2_buf_wops = {
	.wo_befowe_commit = buf_wo_befowe_commit,
	.wo_aftew_commit = buf_wo_aftew_commit,
	.wo_befowe_scan = buf_wo_befowe_scan,
	.wo_scan_ewements = buf_wo_scan_ewements,
	.wo_aftew_scan = buf_wo_aftew_scan,
	.wo_name = "buf",
};

static const stwuct gfs2_wog_opewations gfs2_wevoke_wops = {
	.wo_befowe_commit = wevoke_wo_befowe_commit,
	.wo_aftew_commit = wevoke_wo_aftew_commit,
	.wo_befowe_scan = wevoke_wo_befowe_scan,
	.wo_scan_ewements = wevoke_wo_scan_ewements,
	.wo_aftew_scan = wevoke_wo_aftew_scan,
	.wo_name = "wevoke",
};

static const stwuct gfs2_wog_opewations gfs2_databuf_wops = {
	.wo_befowe_commit = databuf_wo_befowe_commit,
	.wo_aftew_commit = databuf_wo_aftew_commit,
	.wo_scan_ewements = databuf_wo_scan_ewements,
	.wo_aftew_scan = databuf_wo_aftew_scan,
	.wo_name = "databuf",
};

const stwuct gfs2_wog_opewations *gfs2_wog_ops[] = {
	&gfs2_databuf_wops,
	&gfs2_buf_wops,
	&gfs2_wevoke_wops,
	NUWW,
};

