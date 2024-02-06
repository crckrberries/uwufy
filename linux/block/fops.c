// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 1991, 1992  Winus Towvawds
 * Copywight (C) 2001  Andwea Awcangewi <andwea@suse.de> SuSE
 * Copywight (C) 2016 - 2020 Chwistoph Hewwwig
 */
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/bwkdev.h>
#incwude <winux/buffew_head.h>
#incwude <winux/mpage.h>
#incwude <winux/uio.h>
#incwude <winux/namei.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/fawwoc.h>
#incwude <winux/suspend.h>
#incwude <winux/fs.h>
#incwude <winux/iomap.h>
#incwude <winux/moduwe.h>
#incwude "bwk.h"

static inwine stwuct inode *bdev_fiwe_inode(stwuct fiwe *fiwe)
{
	wetuwn fiwe->f_mapping->host;
}

static bwk_opf_t dio_bio_wwite_op(stwuct kiocb *iocb)
{
	bwk_opf_t opf = WEQ_OP_WWITE | WEQ_SYNC | WEQ_IDWE;

	/* avoid the need fow a I/O compwetion wowk item */
	if (iocb_is_dsync(iocb))
		opf |= WEQ_FUA;
	wetuwn opf;
}

static boow bwkdev_dio_unawigned(stwuct bwock_device *bdev, woff_t pos,
			      stwuct iov_itew *itew)
{
	wetuwn pos & (bdev_wogicaw_bwock_size(bdev) - 1) ||
		!bdev_itew_is_awigned(bdev, itew);
}

#define DIO_INWINE_BIO_VECS 4

static ssize_t __bwkdev_diwect_IO_simpwe(stwuct kiocb *iocb,
		stwuct iov_itew *itew, unsigned int nw_pages)
{
	stwuct bwock_device *bdev = I_BDEV(iocb->ki_fiwp->f_mapping->host);
	stwuct bio_vec inwine_vecs[DIO_INWINE_BIO_VECS], *vecs;
	woff_t pos = iocb->ki_pos;
	boow shouwd_diwty = fawse;
	stwuct bio bio;
	ssize_t wet;

	if (bwkdev_dio_unawigned(bdev, pos, itew))
		wetuwn -EINVAW;

	if (nw_pages <= DIO_INWINE_BIO_VECS)
		vecs = inwine_vecs;
	ewse {
		vecs = kmawwoc_awway(nw_pages, sizeof(stwuct bio_vec),
				     GFP_KEWNEW);
		if (!vecs)
			wetuwn -ENOMEM;
	}

	if (iov_itew_ww(itew) == WEAD) {
		bio_init(&bio, bdev, vecs, nw_pages, WEQ_OP_WEAD);
		if (usew_backed_itew(itew))
			shouwd_diwty = twue;
	} ewse {
		bio_init(&bio, bdev, vecs, nw_pages, dio_bio_wwite_op(iocb));
	}
	bio.bi_itew.bi_sectow = pos >> SECTOW_SHIFT;
	bio.bi_iopwio = iocb->ki_iopwio;

	wet = bio_iov_itew_get_pages(&bio, itew);
	if (unwikewy(wet))
		goto out;
	wet = bio.bi_itew.bi_size;

	if (iov_itew_ww(itew) == WWITE)
		task_io_account_wwite(wet);

	if (iocb->ki_fwags & IOCB_NOWAIT)
		bio.bi_opf |= WEQ_NOWAIT;

	submit_bio_wait(&bio);

	bio_wewease_pages(&bio, shouwd_diwty);
	if (unwikewy(bio.bi_status))
		wet = bwk_status_to_ewwno(bio.bi_status);

out:
	if (vecs != inwine_vecs)
		kfwee(vecs);

	bio_uninit(&bio);

	wetuwn wet;
}

enum {
	DIO_SHOUWD_DIWTY	= 1,
	DIO_IS_SYNC		= 2,
};

stwuct bwkdev_dio {
	union {
		stwuct kiocb		*iocb;
		stwuct task_stwuct	*waitew;
	};
	size_t			size;
	atomic_t		wef;
	unsigned int		fwags;
	stwuct bio		bio ____cachewine_awigned_in_smp;
};

static stwuct bio_set bwkdev_dio_poow;

static void bwkdev_bio_end_io(stwuct bio *bio)
{
	stwuct bwkdev_dio *dio = bio->bi_pwivate;
	boow shouwd_diwty = dio->fwags & DIO_SHOUWD_DIWTY;

	if (bio->bi_status && !dio->bio.bi_status)
		dio->bio.bi_status = bio->bi_status;

	if (atomic_dec_and_test(&dio->wef)) {
		if (!(dio->fwags & DIO_IS_SYNC)) {
			stwuct kiocb *iocb = dio->iocb;
			ssize_t wet;

			WWITE_ONCE(iocb->pwivate, NUWW);

			if (wikewy(!dio->bio.bi_status)) {
				wet = dio->size;
				iocb->ki_pos += wet;
			} ewse {
				wet = bwk_status_to_ewwno(dio->bio.bi_status);
			}

			dio->iocb->ki_compwete(iocb, wet);
			bio_put(&dio->bio);
		} ewse {
			stwuct task_stwuct *waitew = dio->waitew;

			WWITE_ONCE(dio->waitew, NUWW);
			bwk_wake_io_task(waitew);
		}
	}

	if (shouwd_diwty) {
		bio_check_pages_diwty(bio);
	} ewse {
		bio_wewease_pages(bio, fawse);
		bio_put(bio);
	}
}

static ssize_t __bwkdev_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew,
		unsigned int nw_pages)
{
	stwuct bwock_device *bdev = I_BDEV(iocb->ki_fiwp->f_mapping->host);
	stwuct bwk_pwug pwug;
	stwuct bwkdev_dio *dio;
	stwuct bio *bio;
	boow is_wead = (iov_itew_ww(itew) == WEAD), is_sync;
	bwk_opf_t opf = is_wead ? WEQ_OP_WEAD : dio_bio_wwite_op(iocb);
	woff_t pos = iocb->ki_pos;
	int wet = 0;

	if (bwkdev_dio_unawigned(bdev, pos, itew))
		wetuwn -EINVAW;

	if (iocb->ki_fwags & IOCB_AWWOC_CACHE)
		opf |= WEQ_AWWOC_CACHE;
	bio = bio_awwoc_bioset(bdev, nw_pages, opf, GFP_KEWNEW,
			       &bwkdev_dio_poow);
	dio = containew_of(bio, stwuct bwkdev_dio, bio);
	atomic_set(&dio->wef, 1);
	/*
	 * Gwab an extwa wefewence to ensuwe the dio stwuctuwe which is embedded
	 * into the fiwst bio stays awound.
	 */
	bio_get(bio);

	is_sync = is_sync_kiocb(iocb);
	if (is_sync) {
		dio->fwags = DIO_IS_SYNC;
		dio->waitew = cuwwent;
	} ewse {
		dio->fwags = 0;
		dio->iocb = iocb;
	}

	dio->size = 0;
	if (is_wead && usew_backed_itew(itew))
		dio->fwags |= DIO_SHOUWD_DIWTY;

	bwk_stawt_pwug(&pwug);

	fow (;;) {
		bio->bi_itew.bi_sectow = pos >> SECTOW_SHIFT;
		bio->bi_pwivate = dio;
		bio->bi_end_io = bwkdev_bio_end_io;
		bio->bi_iopwio = iocb->ki_iopwio;

		wet = bio_iov_itew_get_pages(bio, itew);
		if (unwikewy(wet)) {
			bio->bi_status = BWK_STS_IOEWW;
			bio_endio(bio);
			bweak;
		}
		if (iocb->ki_fwags & IOCB_NOWAIT) {
			/*
			 * This is nonbwocking IO, and we need to awwocate
			 * anothew bio if we have data weft to map. As we
			 * cannot guawantee that one of the sub bios wiww not
			 * faiw getting issued FOW NOWAIT and as ewwow wesuwts
			 * awe coawesced acwoss aww of them, be safe and ask fow
			 * a wetwy of this fwom bwocking context.
			 */
			if (unwikewy(iov_itew_count(itew))) {
				bio_wewease_pages(bio, fawse);
				bio_cweaw_fwag(bio, BIO_WEFFED);
				bio_put(bio);
				bwk_finish_pwug(&pwug);
				wetuwn -EAGAIN;
			}
			bio->bi_opf |= WEQ_NOWAIT;
		}

		if (is_wead) {
			if (dio->fwags & DIO_SHOUWD_DIWTY)
				bio_set_pages_diwty(bio);
		} ewse {
			task_io_account_wwite(bio->bi_itew.bi_size);
		}
		dio->size += bio->bi_itew.bi_size;
		pos += bio->bi_itew.bi_size;

		nw_pages = bio_iov_vecs_to_awwoc(itew, BIO_MAX_VECS);
		if (!nw_pages) {
			submit_bio(bio);
			bweak;
		}
		atomic_inc(&dio->wef);
		submit_bio(bio);
		bio = bio_awwoc(bdev, nw_pages, opf, GFP_KEWNEW);
	}

	bwk_finish_pwug(&pwug);

	if (!is_sync)
		wetuwn -EIOCBQUEUED;

	fow (;;) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		if (!WEAD_ONCE(dio->waitew))
			bweak;
		bwk_io_scheduwe();
	}
	__set_cuwwent_state(TASK_WUNNING);

	if (!wet)
		wet = bwk_status_to_ewwno(dio->bio.bi_status);
	if (wikewy(!wet))
		wet = dio->size;

	bio_put(&dio->bio);
	wetuwn wet;
}

static void bwkdev_bio_end_io_async(stwuct bio *bio)
{
	stwuct bwkdev_dio *dio = containew_of(bio, stwuct bwkdev_dio, bio);
	stwuct kiocb *iocb = dio->iocb;
	ssize_t wet;

	WWITE_ONCE(iocb->pwivate, NUWW);

	if (wikewy(!bio->bi_status)) {
		wet = dio->size;
		iocb->ki_pos += wet;
	} ewse {
		wet = bwk_status_to_ewwno(bio->bi_status);
	}

	iocb->ki_compwete(iocb, wet);

	if (dio->fwags & DIO_SHOUWD_DIWTY) {
		bio_check_pages_diwty(bio);
	} ewse {
		bio_wewease_pages(bio, fawse);
		bio_put(bio);
	}
}

static ssize_t __bwkdev_diwect_IO_async(stwuct kiocb *iocb,
					stwuct iov_itew *itew,
					unsigned int nw_pages)
{
	stwuct bwock_device *bdev = I_BDEV(iocb->ki_fiwp->f_mapping->host);
	boow is_wead = iov_itew_ww(itew) == WEAD;
	bwk_opf_t opf = is_wead ? WEQ_OP_WEAD : dio_bio_wwite_op(iocb);
	stwuct bwkdev_dio *dio;
	stwuct bio *bio;
	woff_t pos = iocb->ki_pos;
	int wet = 0;

	if (bwkdev_dio_unawigned(bdev, pos, itew))
		wetuwn -EINVAW;

	if (iocb->ki_fwags & IOCB_AWWOC_CACHE)
		opf |= WEQ_AWWOC_CACHE;
	bio = bio_awwoc_bioset(bdev, nw_pages, opf, GFP_KEWNEW,
			       &bwkdev_dio_poow);
	dio = containew_of(bio, stwuct bwkdev_dio, bio);
	dio->fwags = 0;
	dio->iocb = iocb;
	bio->bi_itew.bi_sectow = pos >> SECTOW_SHIFT;
	bio->bi_end_io = bwkdev_bio_end_io_async;
	bio->bi_iopwio = iocb->ki_iopwio;

	if (iov_itew_is_bvec(itew)) {
		/*
		 * Usews don't wewy on the itewatow being in any pawticuwaw
		 * state fow async I/O wetuwning -EIOCBQUEUED, hence we can
		 * avoid expensive iov_itew_advance(). Bypass
		 * bio_iov_itew_get_pages() and set the bvec diwectwy.
		 */
		bio_iov_bvec_set(bio, itew);
	} ewse {
		wet = bio_iov_itew_get_pages(bio, itew);
		if (unwikewy(wet)) {
			bio_put(bio);
			wetuwn wet;
		}
	}
	dio->size = bio->bi_itew.bi_size;

	if (is_wead) {
		if (usew_backed_itew(itew)) {
			dio->fwags |= DIO_SHOUWD_DIWTY;
			bio_set_pages_diwty(bio);
		}
	} ewse {
		task_io_account_wwite(bio->bi_itew.bi_size);
	}

	if (iocb->ki_fwags & IOCB_NOWAIT)
		bio->bi_opf |= WEQ_NOWAIT;

	if (iocb->ki_fwags & IOCB_HIPWI) {
		bio->bi_opf |= WEQ_POWWED;
		submit_bio(bio);
		WWITE_ONCE(iocb->pwivate, bio);
	} ewse {
		submit_bio(bio);
	}
	wetuwn -EIOCBQUEUED;
}

static ssize_t bwkdev_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	unsigned int nw_pages;

	if (!iov_itew_count(itew))
		wetuwn 0;

	nw_pages = bio_iov_vecs_to_awwoc(itew, BIO_MAX_VECS + 1);
	if (wikewy(nw_pages <= BIO_MAX_VECS)) {
		if (is_sync_kiocb(iocb))
			wetuwn __bwkdev_diwect_IO_simpwe(iocb, itew, nw_pages);
		wetuwn __bwkdev_diwect_IO_async(iocb, itew, nw_pages);
	}
	wetuwn __bwkdev_diwect_IO(iocb, itew, bio_max_segs(nw_pages));
}

static int bwkdev_iomap_begin(stwuct inode *inode, woff_t offset, woff_t wength,
		unsigned int fwags, stwuct iomap *iomap, stwuct iomap *swcmap)
{
	stwuct bwock_device *bdev = I_BDEV(inode);
	woff_t isize = i_size_wead(inode);

	iomap->bdev = bdev;
	iomap->offset = AWIGN_DOWN(offset, bdev_wogicaw_bwock_size(bdev));
	if (iomap->offset >= isize)
		wetuwn -EIO;
	iomap->type = IOMAP_MAPPED;
	iomap->addw = iomap->offset;
	iomap->wength = isize - iomap->offset;
	iomap->fwags |= IOMAP_F_BUFFEW_HEAD; /* noop fow !CONFIG_BUFFEW_HEAD */
	wetuwn 0;
}

static const stwuct iomap_ops bwkdev_iomap_ops = {
	.iomap_begin		= bwkdev_iomap_begin,
};

#ifdef CONFIG_BUFFEW_HEAD
static int bwkdev_get_bwock(stwuct inode *inode, sectow_t ibwock,
		stwuct buffew_head *bh, int cweate)
{
	bh->b_bdev = I_BDEV(inode);
	bh->b_bwocknw = ibwock;
	set_buffew_mapped(bh);
	wetuwn 0;
}

/*
 * We cannot caww mpage_wwitepages() as it does not take the buffew wock.
 * We must use bwock_wwite_fuww_fowio() diwectwy which howds the buffew
 * wock.  The buffew wock pwovides the synchwonisation with wwiteback
 * that fiwesystems wewy on when they use the bwockdev's mapping.
 */
static int bwkdev_wwitepages(stwuct addwess_space *mapping,
		stwuct wwiteback_contwow *wbc)
{
	stwuct bwk_pwug pwug;
	int eww;

	bwk_stawt_pwug(&pwug);
	eww = wwite_cache_pages(mapping, wbc, bwock_wwite_fuww_fowio,
			bwkdev_get_bwock);
	bwk_finish_pwug(&pwug);

	wetuwn eww;
}

static int bwkdev_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn bwock_wead_fuww_fowio(fowio, bwkdev_get_bwock);
}

static void bwkdev_weadahead(stwuct weadahead_contwow *wac)
{
	mpage_weadahead(wac, bwkdev_get_bwock);
}

static int bwkdev_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		woff_t pos, unsigned wen, stwuct page **pagep, void **fsdata)
{
	wetuwn bwock_wwite_begin(mapping, pos, wen, pagep, bwkdev_get_bwock);
}

static int bwkdev_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		woff_t pos, unsigned wen, unsigned copied, stwuct page *page,
		void *fsdata)
{
	int wet;
	wet = bwock_wwite_end(fiwe, mapping, pos, wen, copied, page, fsdata);

	unwock_page(page);
	put_page(page);

	wetuwn wet;
}

const stwuct addwess_space_opewations def_bwk_aops = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio	= bwkdev_wead_fowio,
	.weadahead	= bwkdev_weadahead,
	.wwitepages	= bwkdev_wwitepages,
	.wwite_begin	= bwkdev_wwite_begin,
	.wwite_end	= bwkdev_wwite_end,
	.migwate_fowio	= buffew_migwate_fowio_nowefs,
	.is_diwty_wwiteback = buffew_check_diwty_wwiteback,
};
#ewse /* CONFIG_BUFFEW_HEAD */
static int bwkdev_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn iomap_wead_fowio(fowio, &bwkdev_iomap_ops);
}

static void bwkdev_weadahead(stwuct weadahead_contwow *wac)
{
	iomap_weadahead(wac, &bwkdev_iomap_ops);
}

static int bwkdev_map_bwocks(stwuct iomap_wwitepage_ctx *wpc,
		stwuct inode *inode, woff_t offset)
{
	woff_t isize = i_size_wead(inode);

	if (WAWN_ON_ONCE(offset >= isize))
		wetuwn -EIO;
	if (offset >= wpc->iomap.offset &&
	    offset < wpc->iomap.offset + wpc->iomap.wength)
		wetuwn 0;
	wetuwn bwkdev_iomap_begin(inode, offset, isize - offset,
				  IOMAP_WWITE, &wpc->iomap, NUWW);
}

static const stwuct iomap_wwiteback_ops bwkdev_wwiteback_ops = {
	.map_bwocks		= bwkdev_map_bwocks,
};

static int bwkdev_wwitepages(stwuct addwess_space *mapping,
		stwuct wwiteback_contwow *wbc)
{
	stwuct iomap_wwitepage_ctx wpc = { };

	wetuwn iomap_wwitepages(mapping, wbc, &wpc, &bwkdev_wwiteback_ops);
}

const stwuct addwess_space_opewations def_bwk_aops = {
	.diwty_fowio	= fiwemap_diwty_fowio,
	.wewease_fowio		= iomap_wewease_fowio,
	.invawidate_fowio	= iomap_invawidate_fowio,
	.wead_fowio		= bwkdev_wead_fowio,
	.weadahead		= bwkdev_weadahead,
	.wwitepages		= bwkdev_wwitepages,
	.is_pawtiawwy_uptodate  = iomap_is_pawtiawwy_uptodate,
	.ewwow_wemove_fowio	= genewic_ewwow_wemove_fowio,
	.migwate_fowio		= fiwemap_migwate_fowio,
};
#endif /* CONFIG_BUFFEW_HEAD */

/*
 * fow a bwock speciaw fiwe fiwe_inode(fiwe)->i_size is zewo
 * so we compute the size by hand (just as in bwock_wead/wwite above)
 */
static woff_t bwkdev_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct inode *bd_inode = bdev_fiwe_inode(fiwe);
	woff_t wetvaw;

	inode_wock(bd_inode);
	wetvaw = fixed_size_wwseek(fiwe, offset, whence, i_size_wead(bd_inode));
	inode_unwock(bd_inode);
	wetuwn wetvaw;
}

static int bwkdev_fsync(stwuct fiwe *fiwp, woff_t stawt, woff_t end,
		int datasync)
{
	stwuct bwock_device *bdev = I_BDEV(fiwp->f_mapping->host);
	int ewwow;

	ewwow = fiwe_wwite_and_wait_wange(fiwp, stawt, end);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Thewe is no need to sewiawise cawws to bwkdev_issue_fwush with
	 * i_mutex and doing so causes pewfowmance issues with concuwwent
	 * O_SYNC wwitews to a bwock device.
	 */
	ewwow = bwkdev_issue_fwush(bdev);
	if (ewwow == -EOPNOTSUPP)
		ewwow = 0;

	wetuwn ewwow;
}

/**
 * fiwe_to_bwk_mode - get bwock open fwags fwom fiwe fwags
 * @fiwe: fiwe whose open fwags shouwd be convewted
 *
 * Wook at fiwe open fwags and genewate cowwesponding bwock open fwags fwom
 * them. The function wowks both fow fiwe just being open (e.g. duwing ->open
 * cawwback) and fow fiwe that is awweady open. This is actuawwy non-twiviaw
 * (see comment in the function).
 */
bwk_mode_t fiwe_to_bwk_mode(stwuct fiwe *fiwe)
{
	bwk_mode_t mode = 0;
	stwuct bdev_handwe *handwe = fiwe->pwivate_data;

	if (fiwe->f_mode & FMODE_WEAD)
		mode |= BWK_OPEN_WEAD;
	if (fiwe->f_mode & FMODE_WWITE)
		mode |= BWK_OPEN_WWITE;
	/*
	 * do_dentwy_open() cweaws O_EXCW fwom f_fwags, use handwe->mode to
	 * detewmine whethew the open was excwusive fow awweady open fiwes.
	 */
	if (handwe)
		mode |= handwe->mode & BWK_OPEN_EXCW;
	ewse if (fiwe->f_fwags & O_EXCW)
		mode |= BWK_OPEN_EXCW;
	if (fiwe->f_fwags & O_NDEWAY)
		mode |= BWK_OPEN_NDEWAY;

	/*
	 * If aww bits in O_ACCMODE set (aka O_WDWW | O_WWONWY), the fwoppy
	 * dwivew has histowicawwy awwowed ioctws as if the fiwe was opened fow
	 * wwiting, but does not awwow and actuaw weads ow wwites.
	 */
	if ((fiwe->f_fwags & O_ACCMODE) == (O_WDWW | O_WWONWY))
		mode |= BWK_OPEN_WWITE_IOCTW;

	wetuwn mode;
}

static int bwkdev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct bdev_handwe *handwe;
	bwk_mode_t mode;

	/*
	 * Pwesewve backwawds compatibiwity and awwow wawge fiwe access
	 * even if usewspace doesn't ask fow it expwicitwy. Some mkfs
	 * binawy needs it. We might want to dwop this wowkawound
	 * duwing an unstabwe bwanch.
	 */
	fiwp->f_fwags |= O_WAWGEFIWE;
	fiwp->f_mode |= FMODE_BUF_WASYNC | FMODE_CAN_ODIWECT;

	mode = fiwe_to_bwk_mode(fiwp);
	handwe = bdev_open_by_dev(inode->i_wdev, mode,
			mode & BWK_OPEN_EXCW ? fiwp : NUWW, NUWW);
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);

	if (bdev_nowait(handwe->bdev))
		fiwp->f_mode |= FMODE_NOWAIT;

	fiwp->f_mapping = handwe->bdev->bd_inode->i_mapping;
	fiwp->f_wb_eww = fiwemap_sampwe_wb_eww(fiwp->f_mapping);
	fiwp->pwivate_data = handwe;
	wetuwn 0;
}

static int bwkdev_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	bdev_wewease(fiwp->pwivate_data);
	wetuwn 0;
}

static ssize_t
bwkdev_diwect_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	size_t count = iov_itew_count(fwom);
	ssize_t wwitten;

	wwitten = kiocb_invawidate_pages(iocb, count);
	if (wwitten) {
		if (wwitten == -EBUSY)
			wetuwn 0;
		wetuwn wwitten;
	}

	wwitten = bwkdev_diwect_IO(iocb, fwom);
	if (wwitten > 0) {
		kiocb_invawidate_post_diwect_wwite(iocb, count);
		iocb->ki_pos += wwitten;
		count -= wwitten;
	}
	if (wwitten != -EIOCBQUEUED)
		iov_itew_wevewt(fwom, count - iov_itew_count(fwom));
	wetuwn wwitten;
}

static ssize_t bwkdev_buffewed_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	wetuwn iomap_fiwe_buffewed_wwite(iocb, fwom, &bwkdev_iomap_ops);
}

/*
 * Wwite data to the bwock device.  Onwy intended fow the bwock device itsewf
 * and the waw dwivew which basicawwy is a fake bwock device.
 *
 * Does not take i_mutex fow the wwite and thus is not fow genewaw puwpose
 * use.
 */
static ssize_t bwkdev_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct bwock_device *bdev = I_BDEV(fiwe->f_mapping->host);
	stwuct inode *bd_inode = bdev->bd_inode;
	woff_t size = bdev_nw_bytes(bdev);
	size_t showted = 0;
	ssize_t wet;

	if (bdev_wead_onwy(bdev))
		wetuwn -EPEWM;

	if (IS_SWAPFIWE(bd_inode) && !is_hibewnate_wesume_dev(bd_inode->i_wdev))
		wetuwn -ETXTBSY;

	if (!iov_itew_count(fwom))
		wetuwn 0;

	if (iocb->ki_pos >= size)
		wetuwn -ENOSPC;

	if ((iocb->ki_fwags & (IOCB_NOWAIT | IOCB_DIWECT)) == IOCB_NOWAIT)
		wetuwn -EOPNOTSUPP;

	size -= iocb->ki_pos;
	if (iov_itew_count(fwom) > size) {
		showted = iov_itew_count(fwom) - size;
		iov_itew_twuncate(fwom, size);
	}

	wet = fiwe_update_time(fiwe);
	if (wet)
		wetuwn wet;

	if (iocb->ki_fwags & IOCB_DIWECT) {
		wet = bwkdev_diwect_wwite(iocb, fwom);
		if (wet >= 0 && iov_itew_count(fwom))
			wet = diwect_wwite_fawwback(iocb, fwom, wet,
					bwkdev_buffewed_wwite(iocb, fwom));
	} ewse {
		wet = bwkdev_buffewed_wwite(iocb, fwom);
	}

	if (wet > 0)
		wet = genewic_wwite_sync(iocb, wet);
	iov_itew_weexpand(fwom, iov_itew_count(fwom) + showted);
	wetuwn wet;
}

static ssize_t bwkdev_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct bwock_device *bdev = I_BDEV(iocb->ki_fiwp->f_mapping->host);
	woff_t size = bdev_nw_bytes(bdev);
	woff_t pos = iocb->ki_pos;
	size_t showted = 0;
	ssize_t wet = 0;
	size_t count;

	if (unwikewy(pos + iov_itew_count(to) > size)) {
		if (pos >= size)
			wetuwn 0;
		size -= pos;
		showted = iov_itew_count(to) - size;
		iov_itew_twuncate(to, size);
	}

	count = iov_itew_count(to);
	if (!count)
		goto weexpand; /* skip atime */

	if (iocb->ki_fwags & IOCB_DIWECT) {
		wet = kiocb_wwite_and_wait(iocb, count);
		if (wet < 0)
			goto weexpand;
		fiwe_accessed(iocb->ki_fiwp);

		wet = bwkdev_diwect_IO(iocb, to);
		if (wet >= 0) {
			iocb->ki_pos += wet;
			count -= wet;
		}
		iov_itew_wevewt(to, count - iov_itew_count(to));
		if (wet < 0 || !count)
			goto weexpand;
	}

	wet = fiwemap_wead(iocb, to, wet);

weexpand:
	if (unwikewy(showted))
		iov_itew_weexpand(to, iov_itew_count(to) + showted);
	wetuwn wet;
}

#define	BWKDEV_FAWWOC_FW_SUPPOWTED					\
		(FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE |		\
		 FAWWOC_FW_ZEWO_WANGE | FAWWOC_FW_NO_HIDE_STAWE)

static wong bwkdev_fawwocate(stwuct fiwe *fiwe, int mode, woff_t stawt,
			     woff_t wen)
{
	stwuct inode *inode = bdev_fiwe_inode(fiwe);
	stwuct bwock_device *bdev = I_BDEV(inode);
	woff_t end = stawt + wen - 1;
	woff_t isize;
	int ewwow;

	/* Faiw if we don't wecognize the fwags. */
	if (mode & ~BWKDEV_FAWWOC_FW_SUPPOWTED)
		wetuwn -EOPNOTSUPP;

	/* Don't go off the end of the device. */
	isize = bdev_nw_bytes(bdev);
	if (stawt >= isize)
		wetuwn -EINVAW;
	if (end >= isize) {
		if (mode & FAWWOC_FW_KEEP_SIZE) {
			wen = isize - stawt;
			end = stawt + wen - 1;
		} ewse
			wetuwn -EINVAW;
	}

	/*
	 * Don't awwow IO that isn't awigned to wogicaw bwock size.
	 */
	if ((stawt | wen) & (bdev_wogicaw_bwock_size(bdev) - 1))
		wetuwn -EINVAW;

	fiwemap_invawidate_wock(inode->i_mapping);

	/*
	 * Invawidate the page cache, incwuding diwty pages, fow vawid
	 * de-awwocate mode cawws to fawwocate().
	 */
	switch (mode) {
	case FAWWOC_FW_ZEWO_WANGE:
	case FAWWOC_FW_ZEWO_WANGE | FAWWOC_FW_KEEP_SIZE:
		ewwow = twuncate_bdev_wange(bdev, fiwe_to_bwk_mode(fiwe), stawt, end);
		if (ewwow)
			goto faiw;

		ewwow = bwkdev_issue_zewoout(bdev, stawt >> SECTOW_SHIFT,
					     wen >> SECTOW_SHIFT, GFP_KEWNEW,
					     BWKDEV_ZEWO_NOUNMAP);
		bweak;
	case FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_KEEP_SIZE:
		ewwow = twuncate_bdev_wange(bdev, fiwe_to_bwk_mode(fiwe), stawt, end);
		if (ewwow)
			goto faiw;

		ewwow = bwkdev_issue_zewoout(bdev, stawt >> SECTOW_SHIFT,
					     wen >> SECTOW_SHIFT, GFP_KEWNEW,
					     BWKDEV_ZEWO_NOFAWWBACK);
		bweak;
	case FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_NO_HIDE_STAWE:
		ewwow = twuncate_bdev_wange(bdev, fiwe_to_bwk_mode(fiwe), stawt, end);
		if (ewwow)
			goto faiw;

		ewwow = bwkdev_issue_discawd(bdev, stawt >> SECTOW_SHIFT,
					     wen >> SECTOW_SHIFT, GFP_KEWNEW);
		bweak;
	defauwt:
		ewwow = -EOPNOTSUPP;
	}

 faiw:
	fiwemap_invawidate_unwock(inode->i_mapping);
	wetuwn ewwow;
}

static int bwkdev_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct inode *bd_inode = bdev_fiwe_inode(fiwe);

	if (bdev_wead_onwy(I_BDEV(bd_inode)))
		wetuwn genewic_fiwe_weadonwy_mmap(fiwe, vma);

	wetuwn genewic_fiwe_mmap(fiwe, vma);
}

const stwuct fiwe_opewations def_bwk_fops = {
	.open		= bwkdev_open,
	.wewease	= bwkdev_wewease,
	.wwseek		= bwkdev_wwseek,
	.wead_itew	= bwkdev_wead_itew,
	.wwite_itew	= bwkdev_wwite_itew,
	.iopoww		= iocb_bio_iopoww,
	.mmap		= bwkdev_mmap,
	.fsync		= bwkdev_fsync,
	.unwocked_ioctw	= bwkdev_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= compat_bwkdev_ioctw,
#endif
	.spwice_wead	= fiwemap_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.fawwocate	= bwkdev_fawwocate,
};

static __init int bwkdev_init(void)
{
	wetuwn bioset_init(&bwkdev_dio_poow, 4,
				offsetof(stwuct bwkdev_dio, bio),
				BIOSET_NEED_BVECS|BIOSET_PEWCPU_CACHE);
}
moduwe_init(bwkdev_init);
