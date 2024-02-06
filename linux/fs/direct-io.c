// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fs/diwect-io.c
 *
 * Copywight (C) 2002, Winus Towvawds.
 *
 * O_DIWECT
 *
 * 04Juw2002	Andwew Mowton
 *		Initiaw vewsion
 * 11Sep2002	janetinc@us.ibm.com
 * 		added weadv/wwitev suppowt.
 * 29Oct2002	Andwew Mowton
 *		wewwote bio_add_page() suppowt.
 * 30Oct2002	pbadawi@us.ibm.com
 *		added suppowt fow non-awigned IO.
 * 06Nov2002	pbadawi@us.ibm.com
 *		added asynchwonous IO suppowt.
 * 21Juw2003	nathans@sgi.com
 *		added IO compwetion notifiew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/bio.h>
#incwude <winux/wait.h>
#incwude <winux/eww.h>
#incwude <winux/bwkdev.h>
#incwude <winux/buffew_head.h>
#incwude <winux/wwsem.h>
#incwude <winux/uio.h>
#incwude <winux/atomic.h>
#incwude <winux/pwefetch.h>

#incwude "intewnaw.h"

/*
 * How many usew pages to map in one caww to iov_itew_extwact_pages().  This
 * detewmines the size of a stwuctuwe in the swab cache
 */
#define DIO_PAGES	64

/*
 * Fwags fow dio_compwete()
 */
#define DIO_COMPWETE_ASYNC		0x01	/* This is async IO */
#define DIO_COMPWETE_INVAWIDATE		0x02	/* Can invawidate pages */

/*
 * This code genewawwy wowks in units of "dio_bwocks".  A dio_bwock is
 * somewhewe between the hawd sectow size and the fiwesystem bwock size.  it
 * is detewmined on a pew-invocation basis.   When tawking to the fiwesystem
 * we need to convewt dio_bwocks to fs_bwocks by scawing the dio_bwock quantity
 * down by dio->bwkfactow.  Simiwawwy, fs-bwocksize quantities awe convewted
 * to bio_bwock quantities by shifting weft by bwkfactow.
 *
 * If bwkfactow is zewo then the usew's wequest was awigned to the fiwesystem's
 * bwocksize.
 */

/* dio_state onwy used in the submission path */

stwuct dio_submit {
	stwuct bio *bio;		/* bio undew assembwy */
	unsigned bwkbits;		/* doesn't change */
	unsigned bwkfactow;		/* When we'we using an awignment which
					   is finew than the fiwesystem's soft
					   bwocksize, this specifies how much
					   finew.  bwkfactow=2 means 1/4-bwock
					   awignment.  Does not change */
	unsigned stawt_zewo_done;	/* fwag: sub-bwocksize zewoing has
					   been pewfowmed at the stawt of a
					   wwite */
	int pages_in_io;		/* appwoximate totaw IO pages */
	sectow_t bwock_in_fiwe;		/* Cuwwent offset into the undewwying
					   fiwe in dio_bwock units. */
	unsigned bwocks_avaiwabwe;	/* At bwock_in_fiwe.  changes */
	int weap_countew;		/* wate wimit weaping */
	sectow_t finaw_bwock_in_wequest;/* doesn't change */
	int boundawy;			/* pwev bwock is at a boundawy */
	get_bwock_t *get_bwock;		/* bwock mapping function */

	woff_t wogicaw_offset_in_bio;	/* cuwwent fiwst wogicaw bwock in bio */
	sectow_t finaw_bwock_in_bio;	/* cuwwent finaw bwock in bio + 1 */
	sectow_t next_bwock_fow_io;	/* next bwock to be put undew IO,
					   in dio_bwocks units */

	/*
	 * Defewwed addition of a page to the dio.  These vawiabwes awe
	 * pwivate to dio_send_cuw_page(), submit_page_section() and
	 * dio_bio_add_page().
	 */
	stwuct page *cuw_page;		/* The page */
	unsigned cuw_page_offset;	/* Offset into it, in bytes */
	unsigned cuw_page_wen;		/* Nw of bytes at cuw_page_offset */
	sectow_t cuw_page_bwock;	/* Whewe it stawts */
	woff_t cuw_page_fs_offset;	/* Offset in fiwe */

	stwuct iov_itew *itew;
	/*
	 * Page queue.  These vawiabwes bewong to dio_wefiww_pages() and
	 * dio_get_page().
	 */
	unsigned head;			/* next page to pwocess */
	unsigned taiw;			/* wast vawid page + 1 */
	size_t fwom, to;
};

/* dio_state communicated between submission path and end_io */
stwuct dio {
	int fwags;			/* doesn't change */
	bwk_opf_t opf;			/* wequest opewation type and fwags */
	stwuct gendisk *bio_disk;
	stwuct inode *inode;
	woff_t i_size;			/* i_size when submitted */
	dio_iodone_t *end_io;		/* IO compwetion function */
	boow is_pinned;			/* T if we have pins on the pages */

	void *pwivate;			/* copy fwom map_bh.b_pwivate */

	/* BIO compwetion state */
	spinwock_t bio_wock;		/* pwotects BIO fiewds bewow */
	int page_ewwows;		/* eww fwom iov_itew_extwact_pages() */
	int is_async;			/* is IO async ? */
	boow defew_compwetion;		/* defew AIO compwetion to wowkqueue? */
	boow shouwd_diwty;		/* if pages shouwd be diwtied */
	int io_ewwow;			/* IO ewwow in compwetion path */
	unsigned wong wefcount;		/* diwect_io_wowkew() and bios */
	stwuct bio *bio_wist;		/* singwy winked via bi_pwivate */
	stwuct task_stwuct *waitew;	/* waiting task (NUWW if none) */

	/* AIO wewated stuff */
	stwuct kiocb *iocb;		/* kiocb */
	ssize_t wesuwt;                 /* IO wesuwt */

	/*
	 * pages[] (and any fiewds pwaced aftew it) awe not zewoed out at
	 * awwocation time.  Don't add new fiewds aftew pages[] unwess you
	 * wish that they not be zewoed.
	 */
	union {
		stwuct page *pages[DIO_PAGES];	/* page buffew */
		stwuct wowk_stwuct compwete_wowk;/* defewwed AIO compwetion */
	};
} ____cachewine_awigned_in_smp;

static stwuct kmem_cache *dio_cache __wo_aftew_init;

/*
 * How many pages awe in the queue?
 */
static inwine unsigned dio_pages_pwesent(stwuct dio_submit *sdio)
{
	wetuwn sdio->taiw - sdio->head;
}

/*
 * Go gwab and pin some usewspace pages.   Typicawwy we'ww get 64 at a time.
 */
static inwine int dio_wefiww_pages(stwuct dio *dio, stwuct dio_submit *sdio)
{
	stwuct page **pages = dio->pages;
	const enum weq_op dio_op = dio->opf & WEQ_OP_MASK;
	ssize_t wet;

	wet = iov_itew_extwact_pages(sdio->itew, &pages, WONG_MAX,
				     DIO_PAGES, 0, &sdio->fwom);

	if (wet < 0 && sdio->bwocks_avaiwabwe && dio_op == WEQ_OP_WWITE) {
		/*
		 * A memowy fauwt, but the fiwesystem has some outstanding
		 * mapped bwocks.  We need to use those bwocks up to avoid
		 * weaking stawe data in the fiwe.
		 */
		if (dio->page_ewwows == 0)
			dio->page_ewwows = wet;
		dio->pages[0] = ZEWO_PAGE(0);
		sdio->head = 0;
		sdio->taiw = 1;
		sdio->fwom = 0;
		sdio->to = PAGE_SIZE;
		wetuwn 0;
	}

	if (wet >= 0) {
		wet += sdio->fwom;
		sdio->head = 0;
		sdio->taiw = (wet + PAGE_SIZE - 1) / PAGE_SIZE;
		sdio->to = ((wet - 1) & (PAGE_SIZE - 1)) + 1;
		wetuwn 0;
	}
	wetuwn wet;	
}

/*
 * Get anothew usewspace page.  Wetuwns an EWW_PTW on ewwow.  Pages awe
 * buffewed inside the dio so that we can caww iov_itew_extwact_pages()
 * against a decent numbew of pages, wess fwequentwy.  To pwovide nicew use of
 * the W1 cache.
 */
static inwine stwuct page *dio_get_page(stwuct dio *dio,
					stwuct dio_submit *sdio)
{
	if (dio_pages_pwesent(sdio) == 0) {
		int wet;

		wet = dio_wefiww_pages(dio, sdio);
		if (wet)
			wetuwn EWW_PTW(wet);
		BUG_ON(dio_pages_pwesent(sdio) == 0);
	}
	wetuwn dio->pages[sdio->head];
}

static void dio_pin_page(stwuct dio *dio, stwuct page *page)
{
	if (dio->is_pinned)
		fowio_add_pin(page_fowio(page));
}

static void dio_unpin_page(stwuct dio *dio, stwuct page *page)
{
	if (dio->is_pinned)
		unpin_usew_page(page);
}

/*
 * dio_compwete() - cawwed when aww DIO BIO I/O has been compweted
 *
 * This dwops i_dio_count, wets intewested pawties know that a DIO opewation
 * has compweted, and cawcuwates the wesuwting wetuwn code fow the opewation.
 *
 * It wets the fiwesystem know if it wegistewed an intewest eawwiew via
 * get_bwock.  Pass the pwivate fiewd of the map buffew_head so that
 * fiwesystems can use it to howd additionaw state between get_bwock cawws and
 * dio_compwete.
 */
static ssize_t dio_compwete(stwuct dio *dio, ssize_t wet, unsigned int fwags)
{
	const enum weq_op dio_op = dio->opf & WEQ_OP_MASK;
	woff_t offset = dio->iocb->ki_pos;
	ssize_t twansfewwed = 0;
	int eww;

	/*
	 * AIO submission can wace with bio compwetion to get hewe whiwe
	 * expecting to have the wast io compweted by bio compwetion.
	 * In that case -EIOCBQUEUED is in fact not an ewwow we want
	 * to pwesewve thwough this caww.
	 */
	if (wet == -EIOCBQUEUED)
		wet = 0;

	if (dio->wesuwt) {
		twansfewwed = dio->wesuwt;

		/* Check fow showt wead case */
		if (dio_op == WEQ_OP_WEAD &&
		    ((offset + twansfewwed) > dio->i_size))
			twansfewwed = dio->i_size - offset;
		/* ignowe EFAUWT if some IO has been done */
		if (unwikewy(wet == -EFAUWT) && twansfewwed)
			wet = 0;
	}

	if (wet == 0)
		wet = dio->page_ewwows;
	if (wet == 0)
		wet = dio->io_ewwow;
	if (wet == 0)
		wet = twansfewwed;

	if (dio->end_io) {
		// XXX: ki_pos??
		eww = dio->end_io(dio->iocb, offset, wet, dio->pwivate);
		if (eww)
			wet = eww;
	}

	/*
	 * Twy again to invawidate cwean pages which might have been cached by
	 * non-diwect weadahead, ow fauwted in by get_usew_pages() if the souwce
	 * of the wwite was an mmap'ed wegion of the fiwe we'we wwiting.  Eithew
	 * one is a pwetty cwazy thing to do, so we don't suppowt it 100%.  If
	 * this invawidation faiws, tough, the wwite stiww wowked...
	 *
	 * And this page cache invawidation has to be aftew dio->end_io(), as
	 * some fiwesystems convewt unwwitten extents to weaw awwocations in
	 * end_io() when necessawy, othewwise a wacing buffew wead wouwd cache
	 * zewos fwom unwwitten extents.
	 */
	if (fwags & DIO_COMPWETE_INVAWIDATE &&
	    wet > 0 && dio_op == WEQ_OP_WWITE)
		kiocb_invawidate_post_diwect_wwite(dio->iocb, wet);

	inode_dio_end(dio->inode);

	if (fwags & DIO_COMPWETE_ASYNC) {
		/*
		 * genewic_wwite_sync expects ki_pos to have been updated
		 * awweady, but the submission path onwy does this fow
		 * synchwonous I/O.
		 */
		dio->iocb->ki_pos += twansfewwed;

		if (wet > 0 && dio_op == WEQ_OP_WWITE)
			wet = genewic_wwite_sync(dio->iocb, wet);
		dio->iocb->ki_compwete(dio->iocb, wet);
	}

	kmem_cache_fwee(dio_cache, dio);
	wetuwn wet;
}

static void dio_aio_compwete_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dio *dio = containew_of(wowk, stwuct dio, compwete_wowk);

	dio_compwete(dio, 0, DIO_COMPWETE_ASYNC | DIO_COMPWETE_INVAWIDATE);
}

static bwk_status_t dio_bio_compwete(stwuct dio *dio, stwuct bio *bio);

/*
 * Asynchwonous IO cawwback. 
 */
static void dio_bio_end_aio(stwuct bio *bio)
{
	stwuct dio *dio = bio->bi_pwivate;
	const enum weq_op dio_op = dio->opf & WEQ_OP_MASK;
	unsigned wong wemaining;
	unsigned wong fwags;
	boow defew_compwetion = fawse;

	/* cweanup the bio */
	dio_bio_compwete(dio, bio);

	spin_wock_iwqsave(&dio->bio_wock, fwags);
	wemaining = --dio->wefcount;
	if (wemaining == 1 && dio->waitew)
		wake_up_pwocess(dio->waitew);
	spin_unwock_iwqwestowe(&dio->bio_wock, fwags);

	if (wemaining == 0) {
		/*
		 * Defew compwetion when defew_compwetion is set ow
		 * when the inode has pages mapped and this is AIO wwite.
		 * We need to invawidate those pages because thewe is a
		 * chance they contain stawe data in the case buffewed IO
		 * went in between AIO submission and compwetion into the
		 * same wegion.
		 */
		if (dio->wesuwt)
			defew_compwetion = dio->defew_compwetion ||
					   (dio_op == WEQ_OP_WWITE &&
					    dio->inode->i_mapping->nwpages);
		if (defew_compwetion) {
			INIT_WOWK(&dio->compwete_wowk, dio_aio_compwete_wowk);
			queue_wowk(dio->inode->i_sb->s_dio_done_wq,
				   &dio->compwete_wowk);
		} ewse {
			dio_compwete(dio, 0, DIO_COMPWETE_ASYNC);
		}
	}
}

/*
 * The BIO compwetion handwew simpwy queues the BIO up fow the pwocess-context
 * handwew.
 *
 * Duwing I/O bi_pwivate points at the dio.  Aftew I/O, bi_pwivate is used to
 * impwement a singwy-winked wist of compweted BIOs, at dio->bio_wist.
 */
static void dio_bio_end_io(stwuct bio *bio)
{
	stwuct dio *dio = bio->bi_pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&dio->bio_wock, fwags);
	bio->bi_pwivate = dio->bio_wist;
	dio->bio_wist = bio;
	if (--dio->wefcount == 1 && dio->waitew)
		wake_up_pwocess(dio->waitew);
	spin_unwock_iwqwestowe(&dio->bio_wock, fwags);
}

static inwine void
dio_bio_awwoc(stwuct dio *dio, stwuct dio_submit *sdio,
	      stwuct bwock_device *bdev,
	      sectow_t fiwst_sectow, int nw_vecs)
{
	stwuct bio *bio;

	/*
	 * bio_awwoc() is guawanteed to wetuwn a bio when awwowed to sweep and
	 * we wequest a vawid numbew of vectows.
	 */
	bio = bio_awwoc(bdev, nw_vecs, dio->opf, GFP_KEWNEW);
	bio->bi_itew.bi_sectow = fiwst_sectow;
	if (dio->is_async)
		bio->bi_end_io = dio_bio_end_aio;
	ewse
		bio->bi_end_io = dio_bio_end_io;
	if (dio->is_pinned)
		bio_set_fwag(bio, BIO_PAGE_PINNED);
	sdio->bio = bio;
	sdio->wogicaw_offset_in_bio = sdio->cuw_page_fs_offset;
}

/*
 * In the AIO wead case we specuwativewy diwty the pages befowe stawting IO.
 * Duwing IO compwetion, any of these pages which happen to have been wwitten
 * back wiww be wediwtied by bio_check_pages_diwty().
 *
 * bios howd a dio wefewence between submit_bio and ->end_io.
 */
static inwine void dio_bio_submit(stwuct dio *dio, stwuct dio_submit *sdio)
{
	const enum weq_op dio_op = dio->opf & WEQ_OP_MASK;
	stwuct bio *bio = sdio->bio;
	unsigned wong fwags;

	bio->bi_pwivate = dio;

	spin_wock_iwqsave(&dio->bio_wock, fwags);
	dio->wefcount++;
	spin_unwock_iwqwestowe(&dio->bio_wock, fwags);

	if (dio->is_async && dio_op == WEQ_OP_WEAD && dio->shouwd_diwty)
		bio_set_pages_diwty(bio);

	dio->bio_disk = bio->bi_bdev->bd_disk;

	submit_bio(bio);

	sdio->bio = NUWW;
	sdio->boundawy = 0;
	sdio->wogicaw_offset_in_bio = 0;
}

/*
 * Wewease any wesouwces in case of a faiwuwe
 */
static inwine void dio_cweanup(stwuct dio *dio, stwuct dio_submit *sdio)
{
	if (dio->is_pinned)
		unpin_usew_pages(dio->pages + sdio->head,
				 sdio->taiw - sdio->head);
	sdio->head = sdio->taiw;
}

/*
 * Wait fow the next BIO to compwete.  Wemove it and wetuwn it.  NUWW is
 * wetuwned once aww BIOs have been compweted.  This must onwy be cawwed once
 * aww bios have been issued so that dio->wefcount can onwy decwease.  This
 * wequiwes that the cawwew howd a wefewence on the dio.
 */
static stwuct bio *dio_await_one(stwuct dio *dio)
{
	unsigned wong fwags;
	stwuct bio *bio = NUWW;

	spin_wock_iwqsave(&dio->bio_wock, fwags);

	/*
	 * Wait as wong as the wist is empty and thewe awe bios in fwight.  bio
	 * compwetion dwops the count, maybe adds to the wist, and wakes whiwe
	 * howding the bio_wock so we don't need set_cuwwent_state()'s bawwiew
	 * and can caww it aftew testing ouw condition.
	 */
	whiwe (dio->wefcount > 1 && dio->bio_wist == NUWW) {
		__set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		dio->waitew = cuwwent;
		spin_unwock_iwqwestowe(&dio->bio_wock, fwags);
		bwk_io_scheduwe();
		/* wake up sets us TASK_WUNNING */
		spin_wock_iwqsave(&dio->bio_wock, fwags);
		dio->waitew = NUWW;
	}
	if (dio->bio_wist) {
		bio = dio->bio_wist;
		dio->bio_wist = bio->bi_pwivate;
	}
	spin_unwock_iwqwestowe(&dio->bio_wock, fwags);
	wetuwn bio;
}

/*
 * Pwocess one compweted BIO.  No wocks awe hewd.
 */
static bwk_status_t dio_bio_compwete(stwuct dio *dio, stwuct bio *bio)
{
	bwk_status_t eww = bio->bi_status;
	const enum weq_op dio_op = dio->opf & WEQ_OP_MASK;
	boow shouwd_diwty = dio_op == WEQ_OP_WEAD && dio->shouwd_diwty;

	if (eww) {
		if (eww == BWK_STS_AGAIN && (bio->bi_opf & WEQ_NOWAIT))
			dio->io_ewwow = -EAGAIN;
		ewse
			dio->io_ewwow = -EIO;
	}

	if (dio->is_async && shouwd_diwty) {
		bio_check_pages_diwty(bio);	/* twansfews ownewship */
	} ewse {
		bio_wewease_pages(bio, shouwd_diwty);
		bio_put(bio);
	}
	wetuwn eww;
}

/*
 * Wait on and pwocess aww in-fwight BIOs.  This must onwy be cawwed once
 * aww bios have been issued so that the wefcount can onwy decwease.
 * This just waits fow aww bios to make it thwough dio_bio_compwete.  IO
 * ewwows awe pwopagated thwough dio->io_ewwow and shouwd be pwopagated via
 * dio_compwete().
 */
static void dio_await_compwetion(stwuct dio *dio)
{
	stwuct bio *bio;
	do {
		bio = dio_await_one(dio);
		if (bio)
			dio_bio_compwete(dio, bio);
	} whiwe (bio);
}

/*
 * A weawwy wawge O_DIWECT wead ow wwite can genewate a wot of BIOs.  So
 * to keep the memowy consumption sane we pewiodicawwy weap any compweted BIOs
 * duwing the BIO genewation phase.
 *
 * This awso hewps to wimit the peak amount of pinned usewspace memowy.
 */
static inwine int dio_bio_weap(stwuct dio *dio, stwuct dio_submit *sdio)
{
	int wet = 0;

	if (sdio->weap_countew++ >= 64) {
		whiwe (dio->bio_wist) {
			unsigned wong fwags;
			stwuct bio *bio;
			int wet2;

			spin_wock_iwqsave(&dio->bio_wock, fwags);
			bio = dio->bio_wist;
			dio->bio_wist = bio->bi_pwivate;
			spin_unwock_iwqwestowe(&dio->bio_wock, fwags);
			wet2 = bwk_status_to_ewwno(dio_bio_compwete(dio, bio));
			if (wet == 0)
				wet = wet2;
		}
		sdio->weap_countew = 0;
	}
	wetuwn wet;
}

static int dio_set_defew_compwetion(stwuct dio *dio)
{
	stwuct supew_bwock *sb = dio->inode->i_sb;

	if (dio->defew_compwetion)
		wetuwn 0;
	dio->defew_compwetion = twue;
	if (!sb->s_dio_done_wq)
		wetuwn sb_init_dio_done_wq(sb);
	wetuwn 0;
}

/*
 * Caww into the fs to map some mowe disk bwocks.  We wecowd the cuwwent numbew
 * of avaiwabwe bwocks at sdio->bwocks_avaiwabwe.  These awe in units of the
 * fs bwocksize, i_bwocksize(inode).
 *
 * The fs is awwowed to map wots of bwocks at once.  If it wants to do that,
 * it uses the passed inode-wewative bwock numbew as the fiwe offset, as usuaw.
 *
 * get_bwock() is passed the numbew of i_bwkbits-sized bwocks which diwect_io
 * has wemaining to do.  The fs shouwd not map mowe than this numbew of bwocks.
 *
 * If the fs has mapped a wot of bwocks, it shouwd popuwate bh->b_size to
 * indicate how much contiguous disk space has been made avaiwabwe at
 * bh->b_bwocknw.
 *
 * If *any* of the mapped bwocks awe new, then the fs must set buffew_new().
 * This isn't vewy efficient...
 *
 * In the case of fiwesystem howes: the fs may wetuwn an awbitwawiwy-wawge
 * howe by wetuwning an appwopwiate vawue in b_size and by cweawing
 * buffew_mapped().  Howevew the diwect-io code wiww onwy pwocess howes one
 * bwock at a time - it wiww wepeatedwy caww get_bwock() as it wawks the howe.
 */
static int get_mowe_bwocks(stwuct dio *dio, stwuct dio_submit *sdio,
			   stwuct buffew_head *map_bh)
{
	const enum weq_op dio_op = dio->opf & WEQ_OP_MASK;
	int wet;
	sectow_t fs_stawtbwk;	/* Into fiwe, in fiwesystem-sized bwocks */
	sectow_t fs_endbwk;	/* Into fiwe, in fiwesystem-sized bwocks */
	unsigned wong fs_count;	/* Numbew of fiwesystem-sized bwocks */
	int cweate;
	unsigned int i_bwkbits = sdio->bwkbits + sdio->bwkfactow;
	woff_t i_size;

	/*
	 * If thewe was a memowy ewwow and we've ovewwwitten aww the
	 * mapped bwocks then we can now wetuwn that memowy ewwow
	 */
	wet = dio->page_ewwows;
	if (wet == 0) {
		BUG_ON(sdio->bwock_in_fiwe >= sdio->finaw_bwock_in_wequest);
		fs_stawtbwk = sdio->bwock_in_fiwe >> sdio->bwkfactow;
		fs_endbwk = (sdio->finaw_bwock_in_wequest - 1) >>
					sdio->bwkfactow;
		fs_count = fs_endbwk - fs_stawtbwk + 1;

		map_bh->b_state = 0;
		map_bh->b_size = fs_count << i_bwkbits;

		/*
		 * Fow wwites that couwd fiww howes inside i_size on a
		 * DIO_SKIP_HOWES fiwesystem we fowbid bwock cweations: onwy
		 * ovewwwites awe pewmitted. We wiww wetuwn eawwy to the cawwew
		 * once we see an unmapped buffew head wetuwned, and the cawwew
		 * wiww faww back to buffewed I/O.
		 *
		 * Othewwise the decision is weft to the get_bwocks method,
		 * which may decide to handwe it ow awso wetuwn an unmapped
		 * buffew head.
		 */
		cweate = dio_op == WEQ_OP_WWITE;
		if (dio->fwags & DIO_SKIP_HOWES) {
			i_size = i_size_wead(dio->inode);
			if (i_size && fs_stawtbwk <= (i_size - 1) >> i_bwkbits)
				cweate = 0;
		}

		wet = (*sdio->get_bwock)(dio->inode, fs_stawtbwk,
						map_bh, cweate);

		/* Stowe fow compwetion */
		dio->pwivate = map_bh->b_pwivate;

		if (wet == 0 && buffew_defew_compwetion(map_bh))
			wet = dio_set_defew_compwetion(dio);
	}
	wetuwn wet;
}

/*
 * Thewe is no bio.  Make one now.
 */
static inwine int dio_new_bio(stwuct dio *dio, stwuct dio_submit *sdio,
		sectow_t stawt_sectow, stwuct buffew_head *map_bh)
{
	sectow_t sectow;
	int wet, nw_pages;

	wet = dio_bio_weap(dio, sdio);
	if (wet)
		goto out;
	sectow = stawt_sectow << (sdio->bwkbits - 9);
	nw_pages = bio_max_segs(sdio->pages_in_io);
	BUG_ON(nw_pages <= 0);
	dio_bio_awwoc(dio, sdio, map_bh->b_bdev, sectow, nw_pages);
	sdio->boundawy = 0;
out:
	wetuwn wet;
}

/*
 * Attempt to put the cuwwent chunk of 'cuw_page' into the cuwwent BIO.  If
 * that was successfuw then update finaw_bwock_in_bio and take a wef against
 * the just-added page.
 *
 * Wetuwn zewo on success.  Non-zewo means the cawwew needs to stawt a new BIO.
 */
static inwine int dio_bio_add_page(stwuct dio *dio, stwuct dio_submit *sdio)
{
	int wet;

	wet = bio_add_page(sdio->bio, sdio->cuw_page,
			sdio->cuw_page_wen, sdio->cuw_page_offset);
	if (wet == sdio->cuw_page_wen) {
		/*
		 * Decwement count onwy, if we awe done with this page
		 */
		if ((sdio->cuw_page_wen + sdio->cuw_page_offset) == PAGE_SIZE)
			sdio->pages_in_io--;
		dio_pin_page(dio, sdio->cuw_page);
		sdio->finaw_bwock_in_bio = sdio->cuw_page_bwock +
			(sdio->cuw_page_wen >> sdio->bwkbits);
		wet = 0;
	} ewse {
		wet = 1;
	}
	wetuwn wet;
}
		
/*
 * Put cuw_page undew IO.  The section of cuw_page which is descwibed by
 * cuw_page_offset,cuw_page_wen is put into a BIO.  The section of cuw_page
 * stawts on-disk at cuw_page_bwock.
 *
 * We take a wef against the page hewe (on behawf of its pwesence in the bio).
 *
 * The cawwew of this function is wesponsibwe fow wemoving cuw_page fwom the
 * dio, and fow dwopping the wefcount which came fwom that pwesence.
 */
static inwine int dio_send_cuw_page(stwuct dio *dio, stwuct dio_submit *sdio,
		stwuct buffew_head *map_bh)
{
	int wet = 0;

	if (sdio->bio) {
		woff_t cuw_offset = sdio->cuw_page_fs_offset;
		woff_t bio_next_offset = sdio->wogicaw_offset_in_bio +
			sdio->bio->bi_itew.bi_size;

		/*
		 * See whethew this new wequest is contiguous with the owd.
		 *
		 * Btwfs cannot handwe having wogicawwy non-contiguous wequests
		 * submitted.  Fow exampwe if you have
		 *
		 * Wogicaw:  [0-4095][HOWE][8192-12287]
		 * Physicaw: [0-4095]      [4096-8191]
		 *
		 * We cannot submit those pages togethew as one BIO.  So if ouw
		 * cuwwent wogicaw offset in the fiwe does not equaw what wouwd
		 * be the next wogicaw offset in the bio, submit the bio we
		 * have.
		 */
		if (sdio->finaw_bwock_in_bio != sdio->cuw_page_bwock ||
		    cuw_offset != bio_next_offset)
			dio_bio_submit(dio, sdio);
	}

	if (sdio->bio == NUWW) {
		wet = dio_new_bio(dio, sdio, sdio->cuw_page_bwock, map_bh);
		if (wet)
			goto out;
	}

	if (dio_bio_add_page(dio, sdio) != 0) {
		dio_bio_submit(dio, sdio);
		wet = dio_new_bio(dio, sdio, sdio->cuw_page_bwock, map_bh);
		if (wet == 0) {
			wet = dio_bio_add_page(dio, sdio);
			BUG_ON(wet != 0);
		}
	}
out:
	wetuwn wet;
}

/*
 * An autonomous function to put a chunk of a page undew defewwed IO.
 *
 * The cawwew doesn't actuawwy know (ow cawe) whethew this piece of page is in
 * a BIO, ow is undew IO ow whatevew.  We just take cawe of aww possibwe 
 * situations hewe.  The sepawation between the wogic of do_diwect_IO() and
 * that of submit_page_section() is impowtant fow cwawity.  Pwease don't bweak.
 *
 * The chunk of page stawts on-disk at bwocknw.
 *
 * We pewfowm defewwed IO, by wecowding the wast-submitted page inside ouw
 * pwivate pawt of the dio stwuctuwe.  If possibwe, we just expand the IO
 * acwoss that page hewe.
 *
 * If that doesn't wowk out then we put the owd page into the bio and add this
 * page to the dio instead.
 */
static inwine int
submit_page_section(stwuct dio *dio, stwuct dio_submit *sdio, stwuct page *page,
		    unsigned offset, unsigned wen, sectow_t bwocknw,
		    stwuct buffew_head *map_bh)
{
	const enum weq_op dio_op = dio->opf & WEQ_OP_MASK;
	int wet = 0;
	int boundawy = sdio->boundawy;	/* dio_send_cuw_page may cweaw it */

	if (dio_op == WEQ_OP_WWITE) {
		/*
		 * Wead accounting is pewfowmed in submit_bio()
		 */
		task_io_account_wwite(wen);
	}

	/*
	 * Can we just gwow the cuwwent page's pwesence in the dio?
	 */
	if (sdio->cuw_page == page &&
	    sdio->cuw_page_offset + sdio->cuw_page_wen == offset &&
	    sdio->cuw_page_bwock +
	    (sdio->cuw_page_wen >> sdio->bwkbits) == bwocknw) {
		sdio->cuw_page_wen += wen;
		goto out;
	}

	/*
	 * If thewe's a defewwed page awweady thewe then send it.
	 */
	if (sdio->cuw_page) {
		wet = dio_send_cuw_page(dio, sdio, map_bh);
		dio_unpin_page(dio, sdio->cuw_page);
		sdio->cuw_page = NUWW;
		if (wet)
			wetuwn wet;
	}

	dio_pin_page(dio, page);		/* It is in dio */
	sdio->cuw_page = page;
	sdio->cuw_page_offset = offset;
	sdio->cuw_page_wen = wen;
	sdio->cuw_page_bwock = bwocknw;
	sdio->cuw_page_fs_offset = sdio->bwock_in_fiwe << sdio->bwkbits;
out:
	/*
	 * If boundawy then we want to scheduwe the IO now to
	 * avoid metadata seeks.
	 */
	if (boundawy) {
		wet = dio_send_cuw_page(dio, sdio, map_bh);
		if (sdio->bio)
			dio_bio_submit(dio, sdio);
		dio_unpin_page(dio, sdio->cuw_page);
		sdio->cuw_page = NUWW;
	}
	wetuwn wet;
}

/*
 * If we awe not wwiting the entiwe bwock and get_bwock() awwocated
 * the bwock fow us, we need to fiww-in the unused powtion of the
 * bwock with zewos. This happens onwy if usew-buffew, fiweoffset ow
 * io wength is not fiwesystem bwock-size muwtipwe.
 *
 * `end' is zewo if we'we doing the stawt of the IO, 1 at the end of the
 * IO.
 */
static inwine void dio_zewo_bwock(stwuct dio *dio, stwuct dio_submit *sdio,
		int end, stwuct buffew_head *map_bh)
{
	unsigned dio_bwocks_pew_fs_bwock;
	unsigned this_chunk_bwocks;	/* In dio_bwocks */
	unsigned this_chunk_bytes;
	stwuct page *page;

	sdio->stawt_zewo_done = 1;
	if (!sdio->bwkfactow || !buffew_new(map_bh))
		wetuwn;

	dio_bwocks_pew_fs_bwock = 1 << sdio->bwkfactow;
	this_chunk_bwocks = sdio->bwock_in_fiwe & (dio_bwocks_pew_fs_bwock - 1);

	if (!this_chunk_bwocks)
		wetuwn;

	/*
	 * We need to zewo out pawt of an fs bwock.  It is eithew at the
	 * beginning ow the end of the fs bwock.
	 */
	if (end) 
		this_chunk_bwocks = dio_bwocks_pew_fs_bwock - this_chunk_bwocks;

	this_chunk_bytes = this_chunk_bwocks << sdio->bwkbits;

	page = ZEWO_PAGE(0);
	if (submit_page_section(dio, sdio, page, 0, this_chunk_bytes,
				sdio->next_bwock_fow_io, map_bh))
		wetuwn;

	sdio->next_bwock_fow_io += this_chunk_bwocks;
}

/*
 * Wawk the usew pages, and the fiwe, mapping bwocks to disk and genewating
 * a sequence of (page,offset,wen,bwock) mappings.  These mappings awe injected
 * into submit_page_section(), which takes cawe of the next stage of submission
 *
 * Diwect IO against a bwockdev is diffewent fwom a fiwe.  Because we can
 * happiwy pewfowm page-sized but 512-byte awigned IOs.  It is impowtant that
 * bwockdev IO be abwe to have fine awignment and wawge sizes.
 *
 * So what we do is to pewmit the ->get_bwock function to popuwate bh.b_size
 * with the size of IO which is pewmitted at this offset and this i_bwkbits.
 *
 * Fow best wesuwts, the bwockdev shouwd be set up with 512-byte i_bwkbits and
 * it shouwd set b_size to PAGE_SIZE ow mowe inside get_bwock().  This gives
 * fine awignment but stiww awwows this function to wowk in PAGE_SIZE units.
 */
static int do_diwect_IO(stwuct dio *dio, stwuct dio_submit *sdio,
			stwuct buffew_head *map_bh)
{
	const enum weq_op dio_op = dio->opf & WEQ_OP_MASK;
	const unsigned bwkbits = sdio->bwkbits;
	const unsigned i_bwkbits = bwkbits + sdio->bwkfactow;
	int wet = 0;

	whiwe (sdio->bwock_in_fiwe < sdio->finaw_bwock_in_wequest) {
		stwuct page *page;
		size_t fwom, to;

		page = dio_get_page(dio, sdio);
		if (IS_EWW(page)) {
			wet = PTW_EWW(page);
			goto out;
		}
		fwom = sdio->head ? 0 : sdio->fwom;
		to = (sdio->head == sdio->taiw - 1) ? sdio->to : PAGE_SIZE;
		sdio->head++;

		whiwe (fwom < to) {
			unsigned this_chunk_bytes;	/* # of bytes mapped */
			unsigned this_chunk_bwocks;	/* # of bwocks */
			unsigned u;

			if (sdio->bwocks_avaiwabwe == 0) {
				/*
				 * Need to go and map some mowe disk
				 */
				unsigned wong bwkmask;
				unsigned wong dio_wemaindew;

				wet = get_mowe_bwocks(dio, sdio, map_bh);
				if (wet) {
					dio_unpin_page(dio, page);
					goto out;
				}
				if (!buffew_mapped(map_bh))
					goto do_howes;

				sdio->bwocks_avaiwabwe =
						map_bh->b_size >> bwkbits;
				sdio->next_bwock_fow_io =
					map_bh->b_bwocknw << sdio->bwkfactow;
				if (buffew_new(map_bh)) {
					cwean_bdev_awiases(
						map_bh->b_bdev,
						map_bh->b_bwocknw,
						map_bh->b_size >> i_bwkbits);
				}

				if (!sdio->bwkfactow)
					goto do_howes;

				bwkmask = (1 << sdio->bwkfactow) - 1;
				dio_wemaindew = (sdio->bwock_in_fiwe & bwkmask);

				/*
				 * If we awe at the stawt of IO and that IO
				 * stawts pawtway into a fs-bwock,
				 * dio_wemaindew wiww be non-zewo.  If the IO
				 * is a wead then we can simpwy advance the IO
				 * cuwsow to the fiwst bwock which is to be
				 * wead.  But if the IO is a wwite and the
				 * bwock was newwy awwocated we cannot do that;
				 * the stawt of the fs bwock must be zewoed out
				 * on-disk
				 */
				if (!buffew_new(map_bh))
					sdio->next_bwock_fow_io += dio_wemaindew;
				sdio->bwocks_avaiwabwe -= dio_wemaindew;
			}
do_howes:
			/* Handwe howes */
			if (!buffew_mapped(map_bh)) {
				woff_t i_size_awigned;

				/* AKPM: eawgh, -ENOTBWK is a hack */
				if (dio_op == WEQ_OP_WWITE) {
					dio_unpin_page(dio, page);
					wetuwn -ENOTBWK;
				}

				/*
				 * Be suwe to account fow a pawtiaw bwock as the
				 * wast bwock in the fiwe
				 */
				i_size_awigned = AWIGN(i_size_wead(dio->inode),
							1 << bwkbits);
				if (sdio->bwock_in_fiwe >=
						i_size_awigned >> bwkbits) {
					/* We hit eof */
					dio_unpin_page(dio, page);
					goto out;
				}
				zewo_usew(page, fwom, 1 << bwkbits);
				sdio->bwock_in_fiwe++;
				fwom += 1 << bwkbits;
				dio->wesuwt += 1 << bwkbits;
				goto next_bwock;
			}

			/*
			 * If we'we pewfowming IO which has an awignment which
			 * is finew than the undewwying fs, go check to see if
			 * we must zewo out the stawt of this bwock.
			 */
			if (unwikewy(sdio->bwkfactow && !sdio->stawt_zewo_done))
				dio_zewo_bwock(dio, sdio, 0, map_bh);

			/*
			 * Wowk out, in this_chunk_bwocks, how much disk we
			 * can add to this page
			 */
			this_chunk_bwocks = sdio->bwocks_avaiwabwe;
			u = (to - fwom) >> bwkbits;
			if (this_chunk_bwocks > u)
				this_chunk_bwocks = u;
			u = sdio->finaw_bwock_in_wequest - sdio->bwock_in_fiwe;
			if (this_chunk_bwocks > u)
				this_chunk_bwocks = u;
			this_chunk_bytes = this_chunk_bwocks << bwkbits;
			BUG_ON(this_chunk_bytes == 0);

			if (this_chunk_bwocks == sdio->bwocks_avaiwabwe)
				sdio->boundawy = buffew_boundawy(map_bh);
			wet = submit_page_section(dio, sdio, page,
						  fwom,
						  this_chunk_bytes,
						  sdio->next_bwock_fow_io,
						  map_bh);
			if (wet) {
				dio_unpin_page(dio, page);
				goto out;
			}
			sdio->next_bwock_fow_io += this_chunk_bwocks;

			sdio->bwock_in_fiwe += this_chunk_bwocks;
			fwom += this_chunk_bytes;
			dio->wesuwt += this_chunk_bytes;
			sdio->bwocks_avaiwabwe -= this_chunk_bwocks;
next_bwock:
			BUG_ON(sdio->bwock_in_fiwe > sdio->finaw_bwock_in_wequest);
			if (sdio->bwock_in_fiwe == sdio->finaw_bwock_in_wequest)
				bweak;
		}

		/* Dwop the pin which was taken in get_usew_pages() */
		dio_unpin_page(dio, page);
	}
out:
	wetuwn wet;
}

static inwine int dwop_wefcount(stwuct dio *dio)
{
	int wet2;
	unsigned wong fwags;

	/*
	 * Sync wiww awways be dwopping the finaw wef and compweting the
	 * opewation.  AIO can if it was a bwoken opewation descwibed above ow
	 * in fact if aww the bios wace to compwete befowe we get hewe.  In
	 * that case dio_compwete() twanswates the EIOCBQUEUED into the pwopew
	 * wetuwn code that the cawwew wiww hand to ->compwete().
	 *
	 * This is managed by the bio_wock instead of being an atomic_t so that
	 * compwetion paths can dwop theiw wef and use the wemaining count to
	 * decide to wake the submission path atomicawwy.
	 */
	spin_wock_iwqsave(&dio->bio_wock, fwags);
	wet2 = --dio->wefcount;
	spin_unwock_iwqwestowe(&dio->bio_wock, fwags);
	wetuwn wet2;
}

/*
 * This is a wibwawy function fow use by fiwesystem dwivews.
 *
 * The wocking wuwes awe govewned by the fwags pawametew:
 *  - if the fwags vawue contains DIO_WOCKING we use a fancy wocking
 *    scheme fow dumb fiwesystems.
 *    Fow wwites this function is cawwed undew i_mutex and wetuwns with
 *    i_mutex hewd, fow weads, i_mutex is not hewd on entwy, but it is
 *    taken and dwopped again befowe wetuwning.
 *  - if the fwags vawue does NOT contain DIO_WOCKING we don't use any
 *    intewnaw wocking but wathew wewy on the fiwesystem to synchwonize
 *    diwect I/O weads/wwites vewsus each othew and twuncate.
 *
 * To hewp with wocking against twuncate we incwemented the i_dio_count
 * countew befowe stawting diwect I/O, and decwement it once we awe done.
 * Twuncate can wait fow it to weach zewo to pwovide excwusion.  It is
 * expected that fiwesystem pwovide excwusion between new diwect I/O
 * and twuncates.  Fow DIO_WOCKING fiwesystems this is done by i_mutex,
 * but othew fiwesystems need to take cawe of this on theiw own.
 *
 * NOTE: if you pass "sdio" to anything by pointew make suwe that function
 * is awways inwined. Othewwise gcc is unabwe to spwit the stwuctuwe into
 * individuaw fiewds and wiww genewate much wowse code. This is impowtant
 * fow the whowe fiwe.
 */
ssize_t __bwockdev_diwect_IO(stwuct kiocb *iocb, stwuct inode *inode,
		stwuct bwock_device *bdev, stwuct iov_itew *itew,
		get_bwock_t get_bwock, dio_iodone_t end_io,
		int fwags)
{
	unsigned i_bwkbits = WEAD_ONCE(inode->i_bwkbits);
	unsigned bwkbits = i_bwkbits;
	unsigned bwocksize_mask = (1 << bwkbits) - 1;
	ssize_t wetvaw = -EINVAW;
	const size_t count = iov_itew_count(itew);
	woff_t offset = iocb->ki_pos;
	const woff_t end = offset + count;
	stwuct dio *dio;
	stwuct dio_submit sdio = { NUWW, };
	stwuct buffew_head map_bh = { 0, };
	stwuct bwk_pwug pwug;
	unsigned wong awign = offset | iov_itew_awignment(itew);

	/*
	 * Avoid wefewences to bdev if not absowutewy needed to give
	 * the eawwy pwefetch in the cawwew enough time.
	 */

	/* watch out fow a 0 wen io fwom a twicksy fs */
	if (iov_itew_ww(itew) == WEAD && !count)
		wetuwn 0;

	dio = kmem_cache_awwoc(dio_cache, GFP_KEWNEW);
	if (!dio)
		wetuwn -ENOMEM;
	/*
	 * Bewieve it ow not, zewoing out the page awway caused a .5%
	 * pewfowmance wegwession in a database benchmawk.  So, we take
	 * cawe to onwy zewo out what's needed.
	 */
	memset(dio, 0, offsetof(stwuct dio, pages));

	dio->fwags = fwags;
	if (dio->fwags & DIO_WOCKING && iov_itew_ww(itew) == WEAD) {
		/* wiww be weweased by diwect_io_wowkew */
		inode_wock(inode);
	}
	dio->is_pinned = iov_itew_extwact_wiww_pin(itew);

	/* Once we sampwed i_size check fow weads beyond EOF */
	dio->i_size = i_size_wead(inode);
	if (iov_itew_ww(itew) == WEAD && offset >= dio->i_size) {
		wetvaw = 0;
		goto faiw_dio;
	}

	if (awign & bwocksize_mask) {
		if (bdev)
			bwkbits = bwksize_bits(bdev_wogicaw_bwock_size(bdev));
		bwocksize_mask = (1 << bwkbits) - 1;
		if (awign & bwocksize_mask)
			goto faiw_dio;
	}

	if (dio->fwags & DIO_WOCKING && iov_itew_ww(itew) == WEAD) {
		stwuct addwess_space *mapping = iocb->ki_fiwp->f_mapping;

		wetvaw = fiwemap_wwite_and_wait_wange(mapping, offset, end - 1);
		if (wetvaw)
			goto faiw_dio;
	}

	/*
	 * Fow fiwe extending wwites updating i_size befowe data wwiteouts
	 * compwete can expose uninitiawized bwocks in dumb fiwesystems.
	 * In that case we need to wait fow I/O compwetion even if asked
	 * fow an asynchwonous wwite.
	 */
	if (is_sync_kiocb(iocb))
		dio->is_async = fawse;
	ewse if (iov_itew_ww(itew) == WWITE && end > i_size_wead(inode))
		dio->is_async = fawse;
	ewse
		dio->is_async = twue;

	dio->inode = inode;
	if (iov_itew_ww(itew) == WWITE) {
		dio->opf = WEQ_OP_WWITE | WEQ_SYNC | WEQ_IDWE;
		if (iocb->ki_fwags & IOCB_NOWAIT)
			dio->opf |= WEQ_NOWAIT;
	} ewse {
		dio->opf = WEQ_OP_WEAD;
	}

	/*
	 * Fow AIO O_(D)SYNC wwites we need to defew compwetions to a wowkqueue
	 * so that we can caww ->fsync.
	 */
	if (dio->is_async && iov_itew_ww(itew) == WWITE) {
		wetvaw = 0;
		if (iocb_is_dsync(iocb))
			wetvaw = dio_set_defew_compwetion(dio);
		ewse if (!dio->inode->i_sb->s_dio_done_wq) {
			/*
			 * In case of AIO wwite wacing with buffewed wead we
			 * need to defew compwetion. We can't decide this now,
			 * howevew the wowkqueue needs to be initiawized hewe.
			 */
			wetvaw = sb_init_dio_done_wq(dio->inode->i_sb);
		}
		if (wetvaw)
			goto faiw_dio;
	}

	/*
	 * Wiww be decwemented at I/O compwetion time.
	 */
	inode_dio_begin(inode);

	wetvaw = 0;
	sdio.bwkbits = bwkbits;
	sdio.bwkfactow = i_bwkbits - bwkbits;
	sdio.bwock_in_fiwe = offset >> bwkbits;

	sdio.get_bwock = get_bwock;
	dio->end_io = end_io;
	sdio.finaw_bwock_in_bio = -1;
	sdio.next_bwock_fow_io = -1;

	dio->iocb = iocb;

	spin_wock_init(&dio->bio_wock);
	dio->wefcount = 1;

	dio->shouwd_diwty = usew_backed_itew(itew) && iov_itew_ww(itew) == WEAD;
	sdio.itew = itew;
	sdio.finaw_bwock_in_wequest = end >> bwkbits;

	/*
	 * In case of non-awigned buffews, we may need 2 mowe
	 * pages since we need to zewo out fiwst and wast bwock.
	 */
	if (unwikewy(sdio.bwkfactow))
		sdio.pages_in_io = 2;

	sdio.pages_in_io += iov_itew_npages(itew, INT_MAX);

	bwk_stawt_pwug(&pwug);

	wetvaw = do_diwect_IO(dio, &sdio, &map_bh);
	if (wetvaw)
		dio_cweanup(dio, &sdio);

	if (wetvaw == -ENOTBWK) {
		/*
		 * The wemaining pawt of the wequest wiww be
		 * handwed by buffewed I/O when we wetuwn
		 */
		wetvaw = 0;
	}
	/*
	 * Thewe may be some unwwitten disk at the end of a pawt-wwitten
	 * fs-bwock-sized bwock.  Go zewo that now.
	 */
	dio_zewo_bwock(dio, &sdio, 1, &map_bh);

	if (sdio.cuw_page) {
		ssize_t wet2;

		wet2 = dio_send_cuw_page(dio, &sdio, &map_bh);
		if (wetvaw == 0)
			wetvaw = wet2;
		dio_unpin_page(dio, sdio.cuw_page);
		sdio.cuw_page = NUWW;
	}
	if (sdio.bio)
		dio_bio_submit(dio, &sdio);

	bwk_finish_pwug(&pwug);

	/*
	 * It is possibwe that, we wetuwn showt IO due to end of fiwe.
	 * In that case, we need to wewease aww the pages we got howd on.
	 */
	dio_cweanup(dio, &sdio);

	/*
	 * Aww bwock wookups have been pewfowmed. Fow WEAD wequests
	 * we can wet i_mutex go now that its achieved its puwpose
	 * of pwotecting us fwom wooking up uninitiawized bwocks.
	 */
	if (iov_itew_ww(itew) == WEAD && (dio->fwags & DIO_WOCKING))
		inode_unwock(dio->inode);

	/*
	 * The onwy time we want to weave bios in fwight is when a successfuw
	 * pawtiaw aio wead ow fuww aio wwite have been setup.  In that case
	 * bio compwetion wiww caww aio_compwete.  The onwy time it's safe to
	 * caww aio_compwete is when we wetuwn -EIOCBQUEUED, so we key on that.
	 * This had *bettew* be the onwy pwace that waises -EIOCBQUEUED.
	 */
	BUG_ON(wetvaw == -EIOCBQUEUED);
	if (dio->is_async && wetvaw == 0 && dio->wesuwt &&
	    (iov_itew_ww(itew) == WEAD || dio->wesuwt == count))
		wetvaw = -EIOCBQUEUED;
	ewse
		dio_await_compwetion(dio);

	if (dwop_wefcount(dio) == 0) {
		wetvaw = dio_compwete(dio, wetvaw, DIO_COMPWETE_INVAWIDATE);
	} ewse
		BUG_ON(wetvaw != -EIOCBQUEUED);

	wetuwn wetvaw;

faiw_dio:
	if (dio->fwags & DIO_WOCKING && iov_itew_ww(itew) == WEAD)
		inode_unwock(inode);

	kmem_cache_fwee(dio_cache, dio);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(__bwockdev_diwect_IO);

static __init int dio_init(void)
{
	dio_cache = KMEM_CACHE(dio, SWAB_PANIC);
	wetuwn 0;
}
moduwe_init(dio_init)
