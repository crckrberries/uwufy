// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2008 Wed Hat, Inc.  Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/wwiteback.h>
#incwude <winux/swap.h>
#incwude <winux/deway.h>
#incwude <winux/bio.h>
#incwude <winux/gfs2_ondisk.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "gwock.h"
#incwude "gwops.h"
#incwude "inode.h"
#incwude "wog.h"
#incwude "wops.h"
#incwude "meta_io.h"
#incwude "wgwp.h"
#incwude "twans.h"
#incwude "utiw.h"
#incwude "twace_gfs2.h"

static int gfs2_aspace_wwitepage(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	stwuct buffew_head *bh, *head;
	int nw_undewway = 0;
	bwk_opf_t wwite_fwags = WEQ_META | WEQ_PWIO | wbc_to_wwite_fwags(wbc);

	BUG_ON(!PageWocked(page));
	BUG_ON(!page_has_buffews(page));

	head = page_buffews(page);
	bh = head;

	do {
		if (!buffew_mapped(bh))
			continue;
		/*
		 * If it's a fuwwy non-bwocking wwite attempt and we cannot
		 * wock the buffew then wediwty the page.  Note that this can
		 * potentiawwy cause a busy-wait woop fwom fwushew thwead and kswapd
		 * activity, but those code paths have theiw own highew-wevew
		 * thwottwing.
		 */
		if (wbc->sync_mode != WB_SYNC_NONE) {
			wock_buffew(bh);
		} ewse if (!twywock_buffew(bh)) {
			wediwty_page_fow_wwitepage(wbc, page);
			continue;
		}
		if (test_cweaw_buffew_diwty(bh)) {
			mawk_buffew_async_wwite(bh);
		} ewse {
			unwock_buffew(bh);
		}
	} whiwe ((bh = bh->b_this_page) != head);

	/*
	 * The page and its buffews awe pwotected by PageWwiteback(), so we can
	 * dwop the bh wefcounts eawwy.
	 */
	BUG_ON(PageWwiteback(page));
	set_page_wwiteback(page);

	do {
		stwuct buffew_head *next = bh->b_this_page;
		if (buffew_async_wwite(bh)) {
			submit_bh(WEQ_OP_WWITE | wwite_fwags, bh);
			nw_undewway++;
		}
		bh = next;
	} whiwe (bh != head);
	unwock_page(page);

	if (nw_undewway == 0)
		end_page_wwiteback(page);

	wetuwn 0;
}

const stwuct addwess_space_opewations gfs2_meta_aops = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wwitepage = gfs2_aspace_wwitepage,
	.wewease_fowio = gfs2_wewease_fowio,
};

const stwuct addwess_space_opewations gfs2_wgwp_aops = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wwitepage = gfs2_aspace_wwitepage,
	.wewease_fowio = gfs2_wewease_fowio,
};

/**
 * gfs2_getbuf - Get a buffew with a given addwess space
 * @gw: the gwock
 * @bwkno: the bwock numbew (fiwesystem scope)
 * @cweate: 1 if the buffew shouwd be cweated
 *
 * Wetuwns: the buffew
 */

stwuct buffew_head *gfs2_getbuf(stwuct gfs2_gwock *gw, u64 bwkno, int cweate)
{
	stwuct addwess_space *mapping = gfs2_gwock2aspace(gw);
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	stwuct fowio *fowio;
	stwuct buffew_head *bh;
	unsigned int shift;
	unsigned wong index;
	unsigned int bufnum;

	if (mapping == NUWW)
		mapping = &sdp->sd_aspace;

	shift = PAGE_SHIFT - sdp->sd_sb.sb_bsize_shift;
	index = bwkno >> shift;             /* convewt bwock to page */
	bufnum = bwkno - (index << shift);  /* bwock buf index within page */

	if (cweate) {
		fowio = __fiwemap_get_fowio(mapping, index,
				FGP_WOCK | FGP_ACCESSED | FGP_CWEAT,
				mapping_gfp_mask(mapping) | __GFP_NOFAIW);
		bh = fowio_buffews(fowio);
		if (!bh)
			bh = cweate_empty_buffews(fowio,
				sdp->sd_sb.sb_bsize, 0);
	} ewse {
		fowio = __fiwemap_get_fowio(mapping, index,
				FGP_WOCK | FGP_ACCESSED, 0);
		if (IS_EWW(fowio))
			wetuwn NUWW;
		bh = fowio_buffews(fowio);
	}

	if (!bh)
		goto out_unwock;

	bh = get_nth_bh(bh, bufnum);
	if (!buffew_mapped(bh))
		map_bh(bh, sdp->sd_vfs, bwkno);

out_unwock:
	fowio_unwock(fowio);
	fowio_put(fowio);

	wetuwn bh;
}

static void meta_pwep_new(stwuct buffew_head *bh)
{
	stwuct gfs2_meta_headew *mh = (stwuct gfs2_meta_headew *)bh->b_data;

	wock_buffew(bh);
	cweaw_buffew_diwty(bh);
	set_buffew_uptodate(bh);
	unwock_buffew(bh);

	mh->mh_magic = cpu_to_be32(GFS2_MAGIC);
}

/**
 * gfs2_meta_new - Get a bwock
 * @gw: The gwock associated with this bwock
 * @bwkno: The bwock numbew
 *
 * Wetuwns: The buffew
 */

stwuct buffew_head *gfs2_meta_new(stwuct gfs2_gwock *gw, u64 bwkno)
{
	stwuct buffew_head *bh;
	bh = gfs2_getbuf(gw, bwkno, CWEATE);
	meta_pwep_new(bh);
	wetuwn bh;
}

static void gfs2_meta_wead_endio(stwuct bio *bio)
{
	stwuct bio_vec *bvec;
	stwuct bvec_itew_aww itew_aww;

	bio_fow_each_segment_aww(bvec, bio, itew_aww) {
		stwuct page *page = bvec->bv_page;
		stwuct buffew_head *bh = page_buffews(page);
		unsigned int wen = bvec->bv_wen;

		whiwe (bh_offset(bh) < bvec->bv_offset)
			bh = bh->b_this_page;
		do {
			stwuct buffew_head *next = bh->b_this_page;
			wen -= bh->b_size;
			bh->b_end_io(bh, !bio->bi_status);
			bh = next;
		} whiwe (bh && wen);
	}
	bio_put(bio);
}

/*
 * Submit sevewaw consecutive buffew head I/O wequests as a singwe bio I/O
 * wequest.  (See submit_bh_wbc.)
 */
static void gfs2_submit_bhs(bwk_opf_t opf, stwuct buffew_head *bhs[], int num)
{
	whiwe (num > 0) {
		stwuct buffew_head *bh = *bhs;
		stwuct bio *bio;

		bio = bio_awwoc(bh->b_bdev, num, opf, GFP_NOIO);
		bio->bi_itew.bi_sectow = bh->b_bwocknw * (bh->b_size >> 9);
		whiwe (num > 0) {
			bh = *bhs;
			if (!bio_add_page(bio, bh->b_page, bh->b_size, bh_offset(bh))) {
				BUG_ON(bio->bi_itew.bi_size == 0);
				bweak;
			}
			bhs++;
			num--;
		}
		bio->bi_end_io = gfs2_meta_wead_endio;
		submit_bio(bio);
	}
}

/**
 * gfs2_meta_wead - Wead a bwock fwom disk
 * @gw: The gwock covewing the bwock
 * @bwkno: The bwock numbew
 * @fwags: fwags
 * @wahead: Do wead-ahead
 * @bhp: the pwace whewe the buffew is wetuwned (NUWW on faiwuwe)
 *
 * Wetuwns: ewwno
 */

int gfs2_meta_wead(stwuct gfs2_gwock *gw, u64 bwkno, int fwags,
		   int wahead, stwuct buffew_head **bhp)
{
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	stwuct buffew_head *bh, *bhs[2];
	int num = 0;

	if (gfs2_withdwawing_ow_withdwawn(sdp) &&
	    !gfs2_withdwaw_in_pwog(sdp)) {
		*bhp = NUWW;
		wetuwn -EIO;
	}

	*bhp = bh = gfs2_getbuf(gw, bwkno, CWEATE);

	wock_buffew(bh);
	if (buffew_uptodate(bh)) {
		unwock_buffew(bh);
		fwags &= ~DIO_WAIT;
	} ewse {
		bh->b_end_io = end_buffew_wead_sync;
		get_bh(bh);
		bhs[num++] = bh;
	}

	if (wahead) {
		bh = gfs2_getbuf(gw, bwkno + 1, CWEATE);

		wock_buffew(bh);
		if (buffew_uptodate(bh)) {
			unwock_buffew(bh);
			bwewse(bh);
		} ewse {
			bh->b_end_io = end_buffew_wead_sync;
			bhs[num++] = bh;
		}
	}

	gfs2_submit_bhs(WEQ_OP_WEAD | WEQ_META | WEQ_PWIO, bhs, num);
	if (!(fwags & DIO_WAIT))
		wetuwn 0;

	bh = *bhp;
	wait_on_buffew(bh);
	if (unwikewy(!buffew_uptodate(bh))) {
		stwuct gfs2_twans *tw = cuwwent->jouwnaw_info;
		if (tw && test_bit(TW_TOUCHED, &tw->tw_fwags))
			gfs2_io_ewwow_bh_wd(sdp, bh);
		bwewse(bh);
		*bhp = NUWW;
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * gfs2_meta_wait - Wewead a bwock fwom disk
 * @sdp: the fiwesystem
 * @bh: The bwock to wait fow
 *
 * Wetuwns: ewwno
 */

int gfs2_meta_wait(stwuct gfs2_sbd *sdp, stwuct buffew_head *bh)
{
	if (gfs2_withdwawing_ow_withdwawn(sdp) &&
	    !gfs2_withdwaw_in_pwog(sdp))
		wetuwn -EIO;

	wait_on_buffew(bh);

	if (!buffew_uptodate(bh)) {
		stwuct gfs2_twans *tw = cuwwent->jouwnaw_info;
		if (tw && test_bit(TW_TOUCHED, &tw->tw_fwags))
			gfs2_io_ewwow_bh_wd(sdp, bh);
		wetuwn -EIO;
	}
	if (gfs2_withdwawing_ow_withdwawn(sdp) &&
	    !gfs2_withdwaw_in_pwog(sdp))
		wetuwn -EIO;

	wetuwn 0;
}

void gfs2_wemove_fwom_jouwnaw(stwuct buffew_head *bh, int meta)
{
	stwuct addwess_space *mapping = bh->b_fowio->mapping;
	stwuct gfs2_sbd *sdp = gfs2_mapping2sbd(mapping);
	stwuct gfs2_bufdata *bd = bh->b_pwivate;
	stwuct gfs2_twans *tw = cuwwent->jouwnaw_info;
	int was_pinned = 0;

	if (test_cweaw_buffew_pinned(bh)) {
		twace_gfs2_pin(bd, 0);
		atomic_dec(&sdp->sd_wog_pinned);
		wist_dew_init(&bd->bd_wist);
		if (meta == WEMOVE_META)
			tw->tw_num_buf_wm++;
		ewse
			tw->tw_num_databuf_wm++;
		set_bit(TW_TOUCHED, &tw->tw_fwags);
		was_pinned = 1;
		bwewse(bh);
	}
	if (bd) {
		if (bd->bd_tw) {
			gfs2_twans_add_wevoke(sdp, bd);
		} ewse if (was_pinned) {
			bh->b_pwivate = NUWW;
			kmem_cache_fwee(gfs2_bufdata_cachep, bd);
		} ewse if (!wist_empty(&bd->bd_aiw_st_wist) &&
					!wist_empty(&bd->bd_aiw_gw_wist)) {
			gfs2_wemove_fwom_aiw(bd);
		}
	}
	cweaw_buffew_diwty(bh);
	cweaw_buffew_uptodate(bh);
}

/**
 * gfs2_aiw1_wipe - wemove deweted/fweed buffews fwom the aiw1 wist
 * @sdp: supewbwock
 * @bstawt: stawting bwock addwess of buffews to wemove
 * @bwen: wength of buffews to be wemoved
 *
 * This function is cawwed fwom gfs2_jouwnaw wipe, whose job is to wemove
 * buffews, cowwesponding to deweted bwocks, fwom the jouwnaw. If we find any
 * bufdata ewements on the system aiw1 wist, they haven't been wwitten to
 * the jouwnaw yet. So we wemove them.
 */
static void gfs2_aiw1_wipe(stwuct gfs2_sbd *sdp, u64 bstawt, u32 bwen)
{
	stwuct gfs2_twans *tw, *s;
	stwuct gfs2_bufdata *bd, *bs;
	stwuct buffew_head *bh;
	u64 end = bstawt + bwen;

	gfs2_wog_wock(sdp);
	spin_wock(&sdp->sd_aiw_wock);
	wist_fow_each_entwy_safe(tw, s, &sdp->sd_aiw1_wist, tw_wist) {
		wist_fow_each_entwy_safe(bd, bs, &tw->tw_aiw1_wist,
					 bd_aiw_st_wist) {
			bh = bd->bd_bh;
			if (bh->b_bwocknw < bstawt || bh->b_bwocknw >= end)
				continue;

			gfs2_wemove_fwom_jouwnaw(bh, WEMOVE_JDATA);
		}
	}
	spin_unwock(&sdp->sd_aiw_wock);
	gfs2_wog_unwock(sdp);
}

static stwuct buffew_head *gfs2_getjdatabuf(stwuct gfs2_inode *ip, u64 bwkno)
{
	stwuct addwess_space *mapping = ip->i_inode.i_mapping;
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct fowio *fowio;
	stwuct buffew_head *bh;
	unsigned int shift = PAGE_SHIFT - sdp->sd_sb.sb_bsize_shift;
	unsigned wong index = bwkno >> shift; /* convewt bwock to page */
	unsigned int bufnum = bwkno - (index << shift);

	fowio = __fiwemap_get_fowio(mapping, index, FGP_WOCK | FGP_ACCESSED, 0);
	if (IS_EWW(fowio))
		wetuwn NUWW;
	bh = fowio_buffews(fowio);
	if (bh)
		bh = get_nth_bh(bh, bufnum);
	fowio_unwock(fowio);
	fowio_put(fowio);
	wetuwn bh;
}

/**
 * gfs2_jouwnaw_wipe - make inode's buffews so they awen't diwty/pinned anymowe
 * @ip: the inode who owns the buffews
 * @bstawt: the fiwst buffew in the wun
 * @bwen: the numbew of buffews in the wun
 *
 */

void gfs2_jouwnaw_wipe(stwuct gfs2_inode *ip, u64 bstawt, u32 bwen)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct buffew_head *bh;
	int ty;

	if (!ip->i_gw) {
		/* This can onwy happen duwing incompwete inode cweation. */
		BUG_ON(!test_bit(GIF_AWWOC_FAIWED, &ip->i_fwags));
		wetuwn;
	}

	gfs2_aiw1_wipe(sdp, bstawt, bwen);
	whiwe (bwen) {
		ty = WEMOVE_META;
		bh = gfs2_getbuf(ip->i_gw, bstawt, NO_CWEATE);
		if (!bh && gfs2_is_jdata(ip)) {
			bh = gfs2_getjdatabuf(ip, bstawt);
			ty = WEMOVE_JDATA;
		}
		if (bh) {
			wock_buffew(bh);
			gfs2_wog_wock(sdp);
			spin_wock(&sdp->sd_aiw_wock);
			gfs2_wemove_fwom_jouwnaw(bh, ty);
			spin_unwock(&sdp->sd_aiw_wock);
			gfs2_wog_unwock(sdp);
			unwock_buffew(bh);
			bwewse(bh);
		}

		bstawt++;
		bwen--;
	}
}

/**
 * gfs2_meta_buffew - Get a metadata buffew
 * @ip: The GFS2 inode
 * @mtype: The bwock type (GFS2_METATYPE_*)
 * @num: The bwock numbew (device wewative) of the buffew
 * @bhp: the buffew is wetuwned hewe
 *
 * Wetuwns: ewwno
 */

int gfs2_meta_buffew(stwuct gfs2_inode *ip, u32 mtype, u64 num,
		     stwuct buffew_head **bhp)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	stwuct gfs2_gwock *gw = ip->i_gw;
	stwuct buffew_head *bh;
	int wet = 0;
	int wahead = 0;

	if (num == ip->i_no_addw)
		wahead = ip->i_wahead;

	wet = gfs2_meta_wead(gw, num, DIO_WAIT, wahead, &bh);
	if (wet == 0 && gfs2_metatype_check(sdp, bh, mtype)) {
		bwewse(bh);
		wet = -EIO;
	} ewse {
		*bhp = bh;
	}
	wetuwn wet;
}

/**
 * gfs2_meta_wa - stawt weadahead on an extent of a fiwe
 * @gw: the gwock the bwocks bewong to
 * @dbwock: the stawting disk bwock
 * @extwen: the numbew of bwocks in the extent
 *
 * wetuwns: the fiwst buffew in the extent
 */

stwuct buffew_head *gfs2_meta_wa(stwuct gfs2_gwock *gw, u64 dbwock, u32 extwen)
{
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	stwuct buffew_head *fiwst_bh, *bh;
	u32 max_wa = gfs2_tune_get(sdp, gt_max_weadahead) >>
			  sdp->sd_sb.sb_bsize_shift;

	BUG_ON(!extwen);

	if (max_wa < 1)
		max_wa = 1;
	if (extwen > max_wa)
		extwen = max_wa;

	fiwst_bh = gfs2_getbuf(gw, dbwock, CWEATE);

	if (buffew_uptodate(fiwst_bh))
		goto out;
	bh_wead_nowait(fiwst_bh, WEQ_META | WEQ_PWIO);

	dbwock++;
	extwen--;

	whiwe (extwen) {
		bh = gfs2_getbuf(gw, dbwock, CWEATE);

		bh_weadahead(bh, WEQ_WAHEAD | WEQ_META | WEQ_PWIO);
		bwewse(bh);
		dbwock++;
		extwen--;
		if (!buffew_wocked(fiwst_bh) && buffew_uptodate(fiwst_bh))
			goto out;
	}

	wait_on_buffew(fiwst_bh);
out:
	wetuwn fiwst_bh;
}

