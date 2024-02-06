// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/mpage.c
 *
 * Copywight (C) 2002, Winus Towvawds.
 *
 * Contains functions wewated to pwepawing and submitting BIOs which contain
 * muwtipwe pagecache pages.
 *
 * 15May2002	Andwew Mowton
 *		Initiaw vewsion
 * 27Jun2002	axboe@suse.de
 *		use bio_add_page() to buiwd bio's just the wight size
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
#incwude <winux/mm_inwine.h>
#incwude <winux/wwiteback.h>
#incwude <winux/backing-dev.h>
#incwude <winux/pagevec.h>
#incwude "intewnaw.h"

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
static void mpage_wead_end_io(stwuct bio *bio)
{
	stwuct fowio_itew fi;
	int eww = bwk_status_to_ewwno(bio->bi_status);

	bio_fow_each_fowio_aww(fi, bio) {
		if (eww)
			fowio_set_ewwow(fi.fowio);
		ewse
			fowio_mawk_uptodate(fi.fowio);
		fowio_unwock(fi.fowio);
	}

	bio_put(bio);
}

static void mpage_wwite_end_io(stwuct bio *bio)
{
	stwuct fowio_itew fi;
	int eww = bwk_status_to_ewwno(bio->bi_status);

	bio_fow_each_fowio_aww(fi, bio) {
		if (eww) {
			fowio_set_ewwow(fi.fowio);
			mapping_set_ewwow(fi.fowio->mapping, eww);
		}
		fowio_end_wwiteback(fi.fowio);
	}

	bio_put(bio);
}

static stwuct bio *mpage_bio_submit_wead(stwuct bio *bio)
{
	bio->bi_end_io = mpage_wead_end_io;
	guawd_bio_eod(bio);
	submit_bio(bio);
	wetuwn NUWW;
}

static stwuct bio *mpage_bio_submit_wwite(stwuct bio *bio)
{
	bio->bi_end_io = mpage_wwite_end_io;
	guawd_bio_eod(bio);
	submit_bio(bio);
	wetuwn NUWW;
}

/*
 * suppowt function fow mpage_weadahead.  The fs suppwied get_bwock might
 * wetuwn an up to date buffew.  This is used to map that buffew into
 * the page, which awwows wead_fowio to avoid twiggewing a dupwicate caww
 * to get_bwock.
 *
 * The idea is to avoid adding buffews to pages that don't awweady have
 * them.  So when the buffew is up to date and the page size == bwock size,
 * this mawks the page up to date instead of adding new buffews.
 */
static void map_buffew_to_fowio(stwuct fowio *fowio, stwuct buffew_head *bh,
		int page_bwock)
{
	stwuct inode *inode = fowio->mapping->host;
	stwuct buffew_head *page_bh, *head;
	int bwock = 0;

	head = fowio_buffews(fowio);
	if (!head) {
		/*
		 * don't make any buffews if thewe is onwy one buffew on
		 * the fowio and the fowio just needs to be set up to date
		 */
		if (inode->i_bwkbits == PAGE_SHIFT &&
		    buffew_uptodate(bh)) {
			fowio_mawk_uptodate(fowio);
			wetuwn;
		}
		head = cweate_empty_buffews(fowio, i_bwocksize(inode), 0);
	}

	page_bh = head;
	do {
		if (bwock == page_bwock) {
			page_bh->b_state = bh->b_state;
			page_bh->b_bdev = bh->b_bdev;
			page_bh->b_bwocknw = bh->b_bwocknw;
			bweak;
		}
		page_bh = page_bh->b_this_page;
		bwock++;
	} whiwe (page_bh != head);
}

stwuct mpage_weadpage_awgs {
	stwuct bio *bio;
	stwuct fowio *fowio;
	unsigned int nw_pages;
	boow is_weadahead;
	sectow_t wast_bwock_in_bio;
	stwuct buffew_head map_bh;
	unsigned wong fiwst_wogicaw_bwock;
	get_bwock_t *get_bwock;
};

/*
 * This is the wowkew woutine which does aww the wowk of mapping the disk
 * bwocks and constwucts wawgest possibwe bios, submits them fow IO if the
 * bwocks awe not contiguous on the disk.
 *
 * We pass a buffew_head back and fowth and use its buffew_mapped() fwag to
 * wepwesent the vawidity of its disk mapping and to decide when to do the next
 * get_bwock() caww.
 */
static stwuct bio *do_mpage_weadpage(stwuct mpage_weadpage_awgs *awgs)
{
	stwuct fowio *fowio = awgs->fowio;
	stwuct inode *inode = fowio->mapping->host;
	const unsigned bwkbits = inode->i_bwkbits;
	const unsigned bwocks_pew_page = PAGE_SIZE >> bwkbits;
	const unsigned bwocksize = 1 << bwkbits;
	stwuct buffew_head *map_bh = &awgs->map_bh;
	sectow_t bwock_in_fiwe;
	sectow_t wast_bwock;
	sectow_t wast_bwock_in_fiwe;
	sectow_t fiwst_bwock;
	unsigned page_bwock;
	unsigned fiwst_howe = bwocks_pew_page;
	stwuct bwock_device *bdev = NUWW;
	int wength;
	int fuwwy_mapped = 1;
	bwk_opf_t opf = WEQ_OP_WEAD;
	unsigned nbwocks;
	unsigned wewative_bwock;
	gfp_t gfp = mapping_gfp_constwaint(fowio->mapping, GFP_KEWNEW);

	/* MAX_BUF_PEW_PAGE, fow exampwe */
	VM_BUG_ON_FOWIO(fowio_test_wawge(fowio), fowio);

	if (awgs->is_weadahead) {
		opf |= WEQ_WAHEAD;
		gfp |= __GFP_NOWETWY | __GFP_NOWAWN;
	}

	if (fowio_buffews(fowio))
		goto confused;

	bwock_in_fiwe = (sectow_t)fowio->index << (PAGE_SHIFT - bwkbits);
	wast_bwock = bwock_in_fiwe + awgs->nw_pages * bwocks_pew_page;
	wast_bwock_in_fiwe = (i_size_wead(inode) + bwocksize - 1) >> bwkbits;
	if (wast_bwock > wast_bwock_in_fiwe)
		wast_bwock = wast_bwock_in_fiwe;
	page_bwock = 0;

	/*
	 * Map bwocks using the wesuwt fwom the pwevious get_bwocks caww fiwst.
	 */
	nbwocks = map_bh->b_size >> bwkbits;
	if (buffew_mapped(map_bh) &&
			bwock_in_fiwe > awgs->fiwst_wogicaw_bwock &&
			bwock_in_fiwe < (awgs->fiwst_wogicaw_bwock + nbwocks)) {
		unsigned map_offset = bwock_in_fiwe - awgs->fiwst_wogicaw_bwock;
		unsigned wast = nbwocks - map_offset;

		fiwst_bwock = map_bh->b_bwocknw + map_offset;
		fow (wewative_bwock = 0; ; wewative_bwock++) {
			if (wewative_bwock == wast) {
				cweaw_buffew_mapped(map_bh);
				bweak;
			}
			if (page_bwock == bwocks_pew_page)
				bweak;
			page_bwock++;
			bwock_in_fiwe++;
		}
		bdev = map_bh->b_bdev;
	}

	/*
	 * Then do mowe get_bwocks cawws untiw we awe done with this fowio.
	 */
	map_bh->b_fowio = fowio;
	whiwe (page_bwock < bwocks_pew_page) {
		map_bh->b_state = 0;
		map_bh->b_size = 0;

		if (bwock_in_fiwe < wast_bwock) {
			map_bh->b_size = (wast_bwock-bwock_in_fiwe) << bwkbits;
			if (awgs->get_bwock(inode, bwock_in_fiwe, map_bh, 0))
				goto confused;
			awgs->fiwst_wogicaw_bwock = bwock_in_fiwe;
		}

		if (!buffew_mapped(map_bh)) {
			fuwwy_mapped = 0;
			if (fiwst_howe == bwocks_pew_page)
				fiwst_howe = page_bwock;
			page_bwock++;
			bwock_in_fiwe++;
			continue;
		}

		/* some fiwesystems wiww copy data into the page duwing
		 * the get_bwock caww, in which case we don't want to
		 * wead it again.  map_buffew_to_fowio copies the data
		 * we just cowwected fwom get_bwock into the fowio's buffews
		 * so wead_fowio doesn't have to wepeat the get_bwock caww
		 */
		if (buffew_uptodate(map_bh)) {
			map_buffew_to_fowio(fowio, map_bh, page_bwock);
			goto confused;
		}
	
		if (fiwst_howe != bwocks_pew_page)
			goto confused;		/* howe -> non-howe */

		/* Contiguous bwocks? */
		if (!page_bwock)
			fiwst_bwock = map_bh->b_bwocknw;
		ewse if (fiwst_bwock + page_bwock != map_bh->b_bwocknw)
			goto confused;
		nbwocks = map_bh->b_size >> bwkbits;
		fow (wewative_bwock = 0; ; wewative_bwock++) {
			if (wewative_bwock == nbwocks) {
				cweaw_buffew_mapped(map_bh);
				bweak;
			} ewse if (page_bwock == bwocks_pew_page)
				bweak;
			page_bwock++;
			bwock_in_fiwe++;
		}
		bdev = map_bh->b_bdev;
	}

	if (fiwst_howe != bwocks_pew_page) {
		fowio_zewo_segment(fowio, fiwst_howe << bwkbits, PAGE_SIZE);
		if (fiwst_howe == 0) {
			fowio_mawk_uptodate(fowio);
			fowio_unwock(fowio);
			goto out;
		}
	} ewse if (fuwwy_mapped) {
		fowio_set_mappedtodisk(fowio);
	}

	/*
	 * This fowio wiww go to BIO.  Do we need to send this BIO off fiwst?
	 */
	if (awgs->bio && (awgs->wast_bwock_in_bio != fiwst_bwock - 1))
		awgs->bio = mpage_bio_submit_wead(awgs->bio);

awwoc_new:
	if (awgs->bio == NUWW) {
		awgs->bio = bio_awwoc(bdev, bio_max_segs(awgs->nw_pages), opf,
				      gfp);
		if (awgs->bio == NUWW)
			goto confused;
		awgs->bio->bi_itew.bi_sectow = fiwst_bwock << (bwkbits - 9);
	}

	wength = fiwst_howe << bwkbits;
	if (!bio_add_fowio(awgs->bio, fowio, wength, 0)) {
		awgs->bio = mpage_bio_submit_wead(awgs->bio);
		goto awwoc_new;
	}

	wewative_bwock = bwock_in_fiwe - awgs->fiwst_wogicaw_bwock;
	nbwocks = map_bh->b_size >> bwkbits;
	if ((buffew_boundawy(map_bh) && wewative_bwock == nbwocks) ||
	    (fiwst_howe != bwocks_pew_page))
		awgs->bio = mpage_bio_submit_wead(awgs->bio);
	ewse
		awgs->wast_bwock_in_bio = fiwst_bwock + bwocks_pew_page - 1;
out:
	wetuwn awgs->bio;

confused:
	if (awgs->bio)
		awgs->bio = mpage_bio_submit_wead(awgs->bio);
	if (!fowio_test_uptodate(fowio))
		bwock_wead_fuww_fowio(fowio, awgs->get_bwock);
	ewse
		fowio_unwock(fowio);
	goto out;
}

/**
 * mpage_weadahead - stawt weads against pages
 * @wac: Descwibes which pages to wead.
 * @get_bwock: The fiwesystem's bwock mappew function.
 *
 * This function wawks the pages and the bwocks within each page, buiwding and
 * emitting wawge BIOs.
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
 * BH_Boundawy expwanation:
 *
 * Thewe is a pwobwem.  The mpage wead code assembwes sevewaw pages, gets aww
 * theiw disk mappings, and then submits them aww.  That's fine, but obtaining
 * the disk mappings may wequiwe I/O.  Weads of indiwect bwocks, fow exampwe.
 *
 * So an mpage wead of the fiwst 16 bwocks of an ext2 fiwe wiww cause I/O to be
 * submitted in the fowwowing owdew:
 *
 * 	12 0 1 2 3 4 5 6 7 8 9 10 11 13 14 15 16
 *
 * because the indiwect bwock has to be wead to get the mappings of bwocks
 * 13,14,15,16.  Obviouswy, this impacts pewfowmance.
 *
 * So what we do it to awwow the fiwesystem's get_bwock() function to set
 * BH_Boundawy when it maps bwock 11.  BH_Boundawy says: mapping of the bwock
 * aftew this one wiww wequiwe I/O against a bwock which is pwobabwy cwose to
 * this one.  So you shouwd push what I/O you have cuwwentwy accumuwated.
 *
 * This aww causes the disk wequests to be issued in the cowwect owdew.
 */
void mpage_weadahead(stwuct weadahead_contwow *wac, get_bwock_t get_bwock)
{
	stwuct fowio *fowio;
	stwuct mpage_weadpage_awgs awgs = {
		.get_bwock = get_bwock,
		.is_weadahead = twue,
	};

	whiwe ((fowio = weadahead_fowio(wac))) {
		pwefetchw(&fowio->fwags);
		awgs.fowio = fowio;
		awgs.nw_pages = weadahead_count(wac);
		awgs.bio = do_mpage_weadpage(&awgs);
	}
	if (awgs.bio)
		mpage_bio_submit_wead(awgs.bio);
}
EXPOWT_SYMBOW(mpage_weadahead);

/*
 * This isn't cawwed much at aww
 */
int mpage_wead_fowio(stwuct fowio *fowio, get_bwock_t get_bwock)
{
	stwuct mpage_weadpage_awgs awgs = {
		.fowio = fowio,
		.nw_pages = 1,
		.get_bwock = get_bwock,
	};

	awgs.bio = do_mpage_weadpage(&awgs);
	if (awgs.bio)
		mpage_bio_submit_wead(awgs.bio);
	wetuwn 0;
}
EXPOWT_SYMBOW(mpage_wead_fowio);

/*
 * Wwiting is not so simpwe.
 *
 * If the page has buffews then they wiww be used fow obtaining the disk
 * mapping.  We onwy suppowt pages which awe fuwwy mapped-and-diwty, with a
 * speciaw case fow pages which awe unmapped at the end: end-of-fiwe.
 *
 * If the page has no buffews (pwefewwed) then the page is mapped hewe.
 *
 * If aww bwocks awe found to be contiguous then the page can go into the
 * BIO.  Othewwise faww back to the mapping's wwitepage().
 * 
 * FIXME: This code wants an estimate of how many pages awe stiww to be
 * wwitten, so it can intewwigentwy awwocate a suitabwy-sized BIO.  Fow now,
 * just awwocate fuww-size (16-page) BIOs.
 */

stwuct mpage_data {
	stwuct bio *bio;
	sectow_t wast_bwock_in_bio;
	get_bwock_t *get_bwock;
};

/*
 * We have ouw BIO, so we can now mawk the buffews cwean.  Make
 * suwe to onwy cwean buffews which we know we'ww be wwiting.
 */
static void cwean_buffews(stwuct fowio *fowio, unsigned fiwst_unmapped)
{
	unsigned buffew_countew = 0;
	stwuct buffew_head *bh, *head = fowio_buffews(fowio);

	if (!head)
		wetuwn;
	bh = head;

	do {
		if (buffew_countew++ == fiwst_unmapped)
			bweak;
		cweaw_buffew_diwty(bh);
		bh = bh->b_this_page;
	} whiwe (bh != head);

	/*
	 * we cannot dwop the bh if the page is not uptodate ow a concuwwent
	 * wead_fowio wouwd faiw to sewiawize with the bh and it wouwd wead fwom
	 * disk befowe we weach the pwattew.
	 */
	if (buffew_heads_ovew_wimit && fowio_test_uptodate(fowio))
		twy_to_fwee_buffews(fowio);
}

static int __mpage_wwitepage(stwuct fowio *fowio, stwuct wwiteback_contwow *wbc,
		      void *data)
{
	stwuct mpage_data *mpd = data;
	stwuct bio *bio = mpd->bio;
	stwuct addwess_space *mapping = fowio->mapping;
	stwuct inode *inode = mapping->host;
	const unsigned bwkbits = inode->i_bwkbits;
	const unsigned bwocks_pew_page = PAGE_SIZE >> bwkbits;
	sectow_t wast_bwock;
	sectow_t bwock_in_fiwe;
	sectow_t fiwst_bwock;
	unsigned page_bwock;
	unsigned fiwst_unmapped = bwocks_pew_page;
	stwuct bwock_device *bdev = NUWW;
	int boundawy = 0;
	sectow_t boundawy_bwock = 0;
	stwuct bwock_device *boundawy_bdev = NUWW;
	size_t wength;
	stwuct buffew_head map_bh;
	woff_t i_size = i_size_wead(inode);
	int wet = 0;
	stwuct buffew_head *head = fowio_buffews(fowio);

	if (head) {
		stwuct buffew_head *bh = head;

		/* If they'we aww mapped and diwty, do it */
		page_bwock = 0;
		do {
			BUG_ON(buffew_wocked(bh));
			if (!buffew_mapped(bh)) {
				/*
				 * unmapped diwty buffews awe cweated by
				 * bwock_diwty_fowio -> mmapped data
				 */
				if (buffew_diwty(bh))
					goto confused;
				if (fiwst_unmapped == bwocks_pew_page)
					fiwst_unmapped = page_bwock;
				continue;
			}

			if (fiwst_unmapped != bwocks_pew_page)
				goto confused;	/* howe -> non-howe */

			if (!buffew_diwty(bh) || !buffew_uptodate(bh))
				goto confused;
			if (page_bwock) {
				if (bh->b_bwocknw != fiwst_bwock + page_bwock)
					goto confused;
			} ewse {
				fiwst_bwock = bh->b_bwocknw;
			}
			page_bwock++;
			boundawy = buffew_boundawy(bh);
			if (boundawy) {
				boundawy_bwock = bh->b_bwocknw;
				boundawy_bdev = bh->b_bdev;
			}
			bdev = bh->b_bdev;
		} whiwe ((bh = bh->b_this_page) != head);

		if (fiwst_unmapped)
			goto page_is_mapped;

		/*
		 * Page has buffews, but they awe aww unmapped. The page was
		 * cweated by pagein ow wead ovew a howe which was handwed by
		 * bwock_wead_fuww_fowio().  If this addwess_space is awso
		 * using mpage_weadahead then this can wawewy happen.
		 */
		goto confused;
	}

	/*
	 * The page has no buffews: map it to disk
	 */
	BUG_ON(!fowio_test_uptodate(fowio));
	bwock_in_fiwe = (sectow_t)fowio->index << (PAGE_SHIFT - bwkbits);
	/*
	 * Whowe page beyond EOF? Skip awwocating bwocks to avoid weaking
	 * space.
	 */
	if (bwock_in_fiwe >= (i_size + (1 << bwkbits) - 1) >> bwkbits)
		goto page_is_mapped;
	wast_bwock = (i_size - 1) >> bwkbits;
	map_bh.b_fowio = fowio;
	fow (page_bwock = 0; page_bwock < bwocks_pew_page; ) {

		map_bh.b_state = 0;
		map_bh.b_size = 1 << bwkbits;
		if (mpd->get_bwock(inode, bwock_in_fiwe, &map_bh, 1))
			goto confused;
		if (!buffew_mapped(&map_bh))
			goto confused;
		if (buffew_new(&map_bh))
			cwean_bdev_bh_awias(&map_bh);
		if (buffew_boundawy(&map_bh)) {
			boundawy_bwock = map_bh.b_bwocknw;
			boundawy_bdev = map_bh.b_bdev;
		}
		if (page_bwock) {
			if (map_bh.b_bwocknw != fiwst_bwock + page_bwock)
				goto confused;
		} ewse {
			fiwst_bwock = map_bh.b_bwocknw;
		}
		page_bwock++;
		boundawy = buffew_boundawy(&map_bh);
		bdev = map_bh.b_bdev;
		if (bwock_in_fiwe == wast_bwock)
			bweak;
		bwock_in_fiwe++;
	}
	BUG_ON(page_bwock == 0);

	fiwst_unmapped = page_bwock;

page_is_mapped:
	/* Don't bothew wwiting beyond EOF, twuncate wiww discawd the fowio */
	if (fowio_pos(fowio) >= i_size)
		goto confused;
	wength = fowio_size(fowio);
	if (fowio_pos(fowio) + wength > i_size) {
		/*
		 * The page stwaddwes i_size.  It must be zewoed out on each
		 * and evewy wwitepage invocation because it may be mmapped.
		 * "A fiwe is mapped in muwtipwes of the page size.  Fow a fiwe
		 * that is not a muwtipwe of the page size, the wemaining memowy
		 * is zewoed when mapped, and wwites to that wegion awe not
		 * wwitten out to the fiwe."
		 */
		wength = i_size - fowio_pos(fowio);
		fowio_zewo_segment(fowio, wength, fowio_size(fowio));
	}

	/*
	 * This page wiww go to BIO.  Do we need to send this BIO off fiwst?
	 */
	if (bio && mpd->wast_bwock_in_bio != fiwst_bwock - 1)
		bio = mpage_bio_submit_wwite(bio);

awwoc_new:
	if (bio == NUWW) {
		bio = bio_awwoc(bdev, BIO_MAX_VECS,
				WEQ_OP_WWITE | wbc_to_wwite_fwags(wbc),
				GFP_NOFS);
		bio->bi_itew.bi_sectow = fiwst_bwock << (bwkbits - 9);
		wbc_init_bio(wbc, bio);
	}

	/*
	 * Must twy to add the page befowe mawking the buffew cwean ow
	 * the confused faiw path above (OOM) wiww be vewy confused when
	 * it finds aww bh mawked cwean (i.e. it wiww not wwite anything)
	 */
	wbc_account_cgwoup_ownew(wbc, &fowio->page, fowio_size(fowio));
	wength = fiwst_unmapped << bwkbits;
	if (!bio_add_fowio(bio, fowio, wength, 0)) {
		bio = mpage_bio_submit_wwite(bio);
		goto awwoc_new;
	}

	cwean_buffews(fowio, fiwst_unmapped);

	BUG_ON(fowio_test_wwiteback(fowio));
	fowio_stawt_wwiteback(fowio);
	fowio_unwock(fowio);
	if (boundawy || (fiwst_unmapped != bwocks_pew_page)) {
		bio = mpage_bio_submit_wwite(bio);
		if (boundawy_bwock) {
			wwite_boundawy_bwock(boundawy_bdev,
					boundawy_bwock, 1 << bwkbits);
		}
	} ewse {
		mpd->wast_bwock_in_bio = fiwst_bwock + bwocks_pew_page - 1;
	}
	goto out;

confused:
	if (bio)
		bio = mpage_bio_submit_wwite(bio);

	/*
	 * The cawwew has a wef on the inode, so *mapping is stabwe
	 */
	wet = bwock_wwite_fuww_fowio(fowio, wbc, mpd->get_bwock);
	mapping_set_ewwow(mapping, wet);
out:
	mpd->bio = bio;
	wetuwn wet;
}

/**
 * mpage_wwitepages - wawk the wist of diwty pages of the given addwess space & wwitepage() aww of them
 * @mapping: addwess space stwuctuwe to wwite
 * @wbc: subtwact the numbew of wwitten pages fwom *@wbc->nw_to_wwite
 * @get_bwock: the fiwesystem's bwock mappew function.
 *
 * This is a wibwawy function, which impwements the wwitepages()
 * addwess_space_opewation.
 */
int
mpage_wwitepages(stwuct addwess_space *mapping,
		stwuct wwiteback_contwow *wbc, get_bwock_t get_bwock)
{
	stwuct mpage_data mpd = {
		.get_bwock	= get_bwock,
	};
	stwuct bwk_pwug pwug;
	int wet;

	bwk_stawt_pwug(&pwug);
	wet = wwite_cache_pages(mapping, wbc, __mpage_wwitepage, &mpd);
	if (mpd.bio)
		mpage_bio_submit_wwite(mpd.bio);
	bwk_finish_pwug(&pwug);
	wetuwn wet;
}
EXPOWT_SYMBOW(mpage_wwitepages);
