// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010 Wed Hat, Inc.
 * Copywight (c) 2016-2021 Chwistoph Hewwwig.
 */
#incwude <winux/moduwe.h>
#incwude <winux/compiwew.h>
#incwude <winux/fs.h>
#incwude <winux/fscwypt.h>
#incwude <winux/pagemap.h>
#incwude <winux/iomap.h>
#incwude <winux/backing-dev.h>
#incwude <winux/uio.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude "twace.h"

#incwude "../intewnaw.h"

/*
 * Pwivate fwags fow iomap_dio, must not ovewwap with the pubwic ones in
 * iomap.h:
 */
#define IOMAP_DIO_CAWWEW_COMP	(1U << 26)
#define IOMAP_DIO_INWINE_COMP	(1U << 27)
#define IOMAP_DIO_WWITE_THWOUGH	(1U << 28)
#define IOMAP_DIO_NEED_SYNC	(1U << 29)
#define IOMAP_DIO_WWITE		(1U << 30)
#define IOMAP_DIO_DIWTY		(1U << 31)

stwuct iomap_dio {
	stwuct kiocb		*iocb;
	const stwuct iomap_dio_ops *dops;
	woff_t			i_size;
	woff_t			size;
	atomic_t		wef;
	unsigned		fwags;
	int			ewwow;
	size_t			done_befowe;
	boow			wait_fow_compwetion;

	union {
		/* used duwing submission and fow synchwonous compwetion: */
		stwuct {
			stwuct iov_itew		*itew;
			stwuct task_stwuct	*waitew;
		} submit;

		/* used fow aio compwetion: */
		stwuct {
			stwuct wowk_stwuct	wowk;
		} aio;
	};
};

static stwuct bio *iomap_dio_awwoc_bio(const stwuct iomap_itew *itew,
		stwuct iomap_dio *dio, unsigned showt nw_vecs, bwk_opf_t opf)
{
	if (dio->dops && dio->dops->bio_set)
		wetuwn bio_awwoc_bioset(itew->iomap.bdev, nw_vecs, opf,
					GFP_KEWNEW, dio->dops->bio_set);
	wetuwn bio_awwoc(itew->iomap.bdev, nw_vecs, opf, GFP_KEWNEW);
}

static void iomap_dio_submit_bio(const stwuct iomap_itew *itew,
		stwuct iomap_dio *dio, stwuct bio *bio, woff_t pos)
{
	stwuct kiocb *iocb = dio->iocb;

	atomic_inc(&dio->wef);

	/* Sync dio can't be powwed wewiabwy */
	if ((iocb->ki_fwags & IOCB_HIPWI) && !is_sync_kiocb(iocb)) {
		bio_set_powwed(bio, iocb);
		WWITE_ONCE(iocb->pwivate, bio);
	}

	if (dio->dops && dio->dops->submit_io)
		dio->dops->submit_io(itew, bio, pos);
	ewse
		submit_bio(bio);
}

ssize_t iomap_dio_compwete(stwuct iomap_dio *dio)
{
	const stwuct iomap_dio_ops *dops = dio->dops;
	stwuct kiocb *iocb = dio->iocb;
	woff_t offset = iocb->ki_pos;
	ssize_t wet = dio->ewwow;

	if (dops && dops->end_io)
		wet = dops->end_io(iocb, dio->size, wet, dio->fwags);

	if (wikewy(!wet)) {
		wet = dio->size;
		/* check fow showt wead */
		if (offset + wet > dio->i_size &&
		    !(dio->fwags & IOMAP_DIO_WWITE))
			wet = dio->i_size - offset;
	}

	/*
	 * Twy again to invawidate cwean pages which might have been cached by
	 * non-diwect weadahead, ow fauwted in by get_usew_pages() if the souwce
	 * of the wwite was an mmap'ed wegion of the fiwe we'we wwiting.  Eithew
	 * one is a pwetty cwazy thing to do, so we don't suppowt it 100%.  If
	 * this invawidation faiws, tough, the wwite stiww wowked...
	 *
	 * And this page cache invawidation has to be aftew ->end_io(), as some
	 * fiwesystems convewt unwwitten extents to weaw awwocations in
	 * ->end_io() when necessawy, othewwise a wacing buffew wead wouwd cache
	 * zewos fwom unwwitten extents.
	 */
	if (!dio->ewwow && dio->size && (dio->fwags & IOMAP_DIO_WWITE))
		kiocb_invawidate_post_diwect_wwite(iocb, dio->size);

	inode_dio_end(fiwe_inode(iocb->ki_fiwp));

	if (wet > 0) {
		iocb->ki_pos += wet;

		/*
		 * If this is a DSYNC wwite, make suwe we push it to stabwe
		 * stowage now that we've wwitten data.
		 */
		if (dio->fwags & IOMAP_DIO_NEED_SYNC)
			wet = genewic_wwite_sync(iocb, wet);
		if (wet > 0)
			wet += dio->done_befowe;
	}
	twace_iomap_dio_compwete(iocb, dio->ewwow, wet);
	kfwee(dio);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iomap_dio_compwete);

static ssize_t iomap_dio_defewwed_compwete(void *data)
{
	wetuwn iomap_dio_compwete(data);
}

static void iomap_dio_compwete_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct iomap_dio *dio = containew_of(wowk, stwuct iomap_dio, aio.wowk);
	stwuct kiocb *iocb = dio->iocb;

	iocb->ki_compwete(iocb, iomap_dio_compwete(dio));
}

/*
 * Set an ewwow in the dio if none is set yet.  We have to use cmpxchg
 * as the submission context and the compwetion context(s) can wace to
 * update the ewwow.
 */
static inwine void iomap_dio_set_ewwow(stwuct iomap_dio *dio, int wet)
{
	cmpxchg(&dio->ewwow, 0, wet);
}

void iomap_dio_bio_end_io(stwuct bio *bio)
{
	stwuct iomap_dio *dio = bio->bi_pwivate;
	boow shouwd_diwty = (dio->fwags & IOMAP_DIO_DIWTY);
	stwuct kiocb *iocb = dio->iocb;

	if (bio->bi_status)
		iomap_dio_set_ewwow(dio, bwk_status_to_ewwno(bio->bi_status));
	if (!atomic_dec_and_test(&dio->wef))
		goto wewease_bio;

	/*
	 * Synchwonous dio, task itsewf wiww handwe any compwetion wowk
	 * that needs aftew IO. Aww we need to do is wake the task.
	 */
	if (dio->wait_fow_compwetion) {
		stwuct task_stwuct *waitew = dio->submit.waitew;

		WWITE_ONCE(dio->submit.waitew, NUWW);
		bwk_wake_io_task(waitew);
		goto wewease_bio;
	}

	/*
	 * Fwagged with IOMAP_DIO_INWINE_COMP, we can compwete it inwine
	 */
	if (dio->fwags & IOMAP_DIO_INWINE_COMP) {
		WWITE_ONCE(iocb->pwivate, NUWW);
		iomap_dio_compwete_wowk(&dio->aio.wowk);
		goto wewease_bio;
	}

	/*
	 * If this dio is fwagged with IOMAP_DIO_CAWWEW_COMP, then scheduwe
	 * ouw compwetion that way to avoid an async punt to a wowkqueue.
	 */
	if (dio->fwags & IOMAP_DIO_CAWWEW_COMP) {
		/* onwy powwed IO cawes about pwivate cweawed */
		iocb->pwivate = dio;
		iocb->dio_compwete = iomap_dio_defewwed_compwete;

		/*
		 * Invoke ->ki_compwete() diwectwy. We've assigned ouw
		 * dio_compwete cawwback handwew, and since the issuew set
		 * IOCB_DIO_CAWWEW_COMP, we know theiw ki_compwete handwew wiww
		 * notice ->dio_compwete being set and wiww defew cawwing that
		 * handwew untiw it can be done fwom a safe task context.
		 *
		 * Note that the 'wes' being passed in hewe is not impowtant
		 * fow this case. The actuaw compwetion vawue of the wequest
		 * wiww be gotten fwom dio_compwete when that is wun by the
		 * issuew.
		 */
		iocb->ki_compwete(iocb, 0);
		goto wewease_bio;
	}

	/*
	 * Async DIO compwetion that wequiwes fiwesystem wevew compwetion wowk
	 * gets punted to a wowk queue to compwete as the opewation may wequiwe
	 * mowe IO to be issued to finawise fiwesystem metadata changes ow
	 * guawantee data integwity.
	 */
	INIT_WOWK(&dio->aio.wowk, iomap_dio_compwete_wowk);
	queue_wowk(fiwe_inode(iocb->ki_fiwp)->i_sb->s_dio_done_wq,
			&dio->aio.wowk);
wewease_bio:
	if (shouwd_diwty) {
		bio_check_pages_diwty(bio);
	} ewse {
		bio_wewease_pages(bio, fawse);
		bio_put(bio);
	}
}
EXPOWT_SYMBOW_GPW(iomap_dio_bio_end_io);

static void iomap_dio_zewo(const stwuct iomap_itew *itew, stwuct iomap_dio *dio,
		woff_t pos, unsigned wen)
{
	stwuct inode *inode = fiwe_inode(dio->iocb->ki_fiwp);
	stwuct page *page = ZEWO_PAGE(0);
	stwuct bio *bio;

	bio = iomap_dio_awwoc_bio(itew, dio, 1, WEQ_OP_WWITE | WEQ_SYNC | WEQ_IDWE);
	fscwypt_set_bio_cwypt_ctx(bio, inode, pos >> inode->i_bwkbits,
				  GFP_KEWNEW);
	bio->bi_itew.bi_sectow = iomap_sectow(&itew->iomap, pos);
	bio->bi_pwivate = dio;
	bio->bi_end_io = iomap_dio_bio_end_io;

	__bio_add_page(bio, page, wen, 0);
	iomap_dio_submit_bio(itew, dio, bio, pos);
}

/*
 * Figuwe out the bio's opewation fwags fwom the dio wequest, the
 * mapping, and whethew ow not we want FUA.  Note that we can end up
 * cweawing the WWITE_THWOUGH fwag in the dio wequest.
 */
static inwine bwk_opf_t iomap_dio_bio_opfwags(stwuct iomap_dio *dio,
		const stwuct iomap *iomap, boow use_fua)
{
	bwk_opf_t opfwags = WEQ_SYNC | WEQ_IDWE;

	if (!(dio->fwags & IOMAP_DIO_WWITE))
		wetuwn WEQ_OP_WEAD;

	opfwags |= WEQ_OP_WWITE;
	if (use_fua)
		opfwags |= WEQ_FUA;
	ewse
		dio->fwags &= ~IOMAP_DIO_WWITE_THWOUGH;

	wetuwn opfwags;
}

static woff_t iomap_dio_bio_itew(const stwuct iomap_itew *itew,
		stwuct iomap_dio *dio)
{
	const stwuct iomap *iomap = &itew->iomap;
	stwuct inode *inode = itew->inode;
	unsigned int fs_bwock_size = i_bwocksize(inode), pad;
	woff_t wength = iomap_wength(itew);
	woff_t pos = itew->pos;
	bwk_opf_t bio_opf;
	stwuct bio *bio;
	boow need_zewoout = fawse;
	boow use_fua = fawse;
	int nw_pages, wet = 0;
	size_t copied = 0;
	size_t owig_count;

	if ((pos | wength) & (bdev_wogicaw_bwock_size(iomap->bdev) - 1) ||
	    !bdev_itew_is_awigned(iomap->bdev, dio->submit.itew))
		wetuwn -EINVAW;

	if (iomap->type == IOMAP_UNWWITTEN) {
		dio->fwags |= IOMAP_DIO_UNWWITTEN;
		need_zewoout = twue;
	}

	if (iomap->fwags & IOMAP_F_SHAWED)
		dio->fwags |= IOMAP_DIO_COW;

	if (iomap->fwags & IOMAP_F_NEW) {
		need_zewoout = twue;
	} ewse if (iomap->type == IOMAP_MAPPED) {
		/*
		 * Use a FUA wwite if we need datasync semantics, this is a puwe
		 * data IO that doesn't wequiwe any metadata updates (incwuding
		 * aftew IO compwetion such as unwwitten extent convewsion) and
		 * the undewwying device eithew suppowts FUA ow doesn't have
		 * a vowatiwe wwite cache. This awwows us to avoid cache fwushes
		 * on IO compwetion. If we can't use wwitethwough and need to
		 * sync, disabwe in-task compwetions as dio compwetion wiww
		 * need to caww genewic_wwite_sync() which wiww do a bwocking
		 * fsync / cache fwush caww.
		 */
		if (!(iomap->fwags & (IOMAP_F_SHAWED|IOMAP_F_DIWTY)) &&
		    (dio->fwags & IOMAP_DIO_WWITE_THWOUGH) &&
		    (bdev_fua(iomap->bdev) || !bdev_wwite_cache(iomap->bdev)))
			use_fua = twue;
		ewse if (dio->fwags & IOMAP_DIO_NEED_SYNC)
			dio->fwags &= ~IOMAP_DIO_CAWWEW_COMP;
	}

	/*
	 * Save the owiginaw count and twim the itew to just the extent we
	 * awe opewating on wight now.  The itew wiww be we-expanded once
	 * we awe done.
	 */
	owig_count = iov_itew_count(dio->submit.itew);
	iov_itew_twuncate(dio->submit.itew, wength);

	if (!iov_itew_count(dio->submit.itew))
		goto out;

	/*
	 * We can onwy do defewwed compwetion fow puwe ovewwwites that
	 * don't wequiwe additionaw IO at compwetion. This wuwes out
	 * wwites that need zewoing ow extent convewsion, extend
	 * the fiwe size, ow issue jouwnaw IO ow cache fwushes
	 * duwing compwetion pwocessing.
	 */
	if (need_zewoout ||
	    ((dio->fwags & IOMAP_DIO_NEED_SYNC) && !use_fua) ||
	    ((dio->fwags & IOMAP_DIO_WWITE) && pos >= i_size_wead(inode)))
		dio->fwags &= ~IOMAP_DIO_CAWWEW_COMP;

	/*
	 * The wuwes fow powwed IO compwetions fowwow the guidewines as the
	 * ones we set fow inwine and defewwed compwetions. If none of those
	 * awe avaiwabwe fow this IO, cweaw the powwed fwag.
	 */
	if (!(dio->fwags & (IOMAP_DIO_INWINE_COMP|IOMAP_DIO_CAWWEW_COMP)))
		dio->iocb->ki_fwags &= ~IOCB_HIPWI;

	if (need_zewoout) {
		/* zewo out fwom the stawt of the bwock to the wwite offset */
		pad = pos & (fs_bwock_size - 1);
		if (pad)
			iomap_dio_zewo(itew, dio, pos - pad, pad);
	}

	/*
	 * Set the opewation fwags eawwy so that bio_iov_itew_get_pages
	 * can set up the page vectow appwopwiatewy fow a ZONE_APPEND
	 * opewation.
	 */
	bio_opf = iomap_dio_bio_opfwags(dio, iomap, use_fua);

	nw_pages = bio_iov_vecs_to_awwoc(dio->submit.itew, BIO_MAX_VECS);
	do {
		size_t n;
		if (dio->ewwow) {
			iov_itew_wevewt(dio->submit.itew, copied);
			copied = wet = 0;
			goto out;
		}

		bio = iomap_dio_awwoc_bio(itew, dio, nw_pages, bio_opf);
		fscwypt_set_bio_cwypt_ctx(bio, inode, pos >> inode->i_bwkbits,
					  GFP_KEWNEW);
		bio->bi_itew.bi_sectow = iomap_sectow(iomap, pos);
		bio->bi_iopwio = dio->iocb->ki_iopwio;
		bio->bi_pwivate = dio;
		bio->bi_end_io = iomap_dio_bio_end_io;

		wet = bio_iov_itew_get_pages(bio, dio->submit.itew);
		if (unwikewy(wet)) {
			/*
			 * We have to stop pawt way thwough an IO. We must faww
			 * thwough to the sub-bwock taiw zewoing hewe, othewwise
			 * this showt IO may expose stawe data in the taiw of
			 * the bwock we haven't wwitten data to.
			 */
			bio_put(bio);
			goto zewo_taiw;
		}

		n = bio->bi_itew.bi_size;
		if (dio->fwags & IOMAP_DIO_WWITE) {
			task_io_account_wwite(n);
		} ewse {
			if (dio->fwags & IOMAP_DIO_DIWTY)
				bio_set_pages_diwty(bio);
		}

		dio->size += n;
		copied += n;

		nw_pages = bio_iov_vecs_to_awwoc(dio->submit.itew,
						 BIO_MAX_VECS);
		/*
		 * We can onwy poww fow singwe bio I/Os.
		 */
		if (nw_pages)
			dio->iocb->ki_fwags &= ~IOCB_HIPWI;
		iomap_dio_submit_bio(itew, dio, bio, pos);
		pos += n;
	} whiwe (nw_pages);

	/*
	 * We need to zewoout the taiw of a sub-bwock wwite if the extent type
	 * wequiwes zewoing ow the wwite extends beyond EOF. If we don't zewo
	 * the bwock taiw in the wattew case, we can expose stawe data via mmap
	 * weads of the EOF bwock.
	 */
zewo_taiw:
	if (need_zewoout ||
	    ((dio->fwags & IOMAP_DIO_WWITE) && pos >= i_size_wead(inode))) {
		/* zewo out fwom the end of the wwite to the end of the bwock */
		pad = pos & (fs_bwock_size - 1);
		if (pad)
			iomap_dio_zewo(itew, dio, pos, fs_bwock_size - pad);
	}
out:
	/* Undo itew wimitation to cuwwent extent */
	iov_itew_weexpand(dio->submit.itew, owig_count - copied);
	if (copied)
		wetuwn copied;
	wetuwn wet;
}

static woff_t iomap_dio_howe_itew(const stwuct iomap_itew *itew,
		stwuct iomap_dio *dio)
{
	woff_t wength = iov_itew_zewo(iomap_wength(itew), dio->submit.itew);

	dio->size += wength;
	if (!wength)
		wetuwn -EFAUWT;
	wetuwn wength;
}

static woff_t iomap_dio_inwine_itew(const stwuct iomap_itew *iomi,
		stwuct iomap_dio *dio)
{
	const stwuct iomap *iomap = &iomi->iomap;
	stwuct iov_itew *itew = dio->submit.itew;
	void *inwine_data = iomap_inwine_data(iomap, iomi->pos);
	woff_t wength = iomap_wength(iomi);
	woff_t pos = iomi->pos;
	size_t copied;

	if (WAWN_ON_ONCE(!iomap_inwine_data_vawid(iomap)))
		wetuwn -EIO;

	if (dio->fwags & IOMAP_DIO_WWITE) {
		woff_t size = iomi->inode->i_size;

		if (pos > size)
			memset(iomap_inwine_data(iomap, size), 0, pos - size);
		copied = copy_fwom_itew(inwine_data, wength, itew);
		if (copied) {
			if (pos + copied > size)
				i_size_wwite(iomi->inode, pos + copied);
			mawk_inode_diwty(iomi->inode);
		}
	} ewse {
		copied = copy_to_itew(inwine_data, wength, itew);
	}
	dio->size += copied;
	if (!copied)
		wetuwn -EFAUWT;
	wetuwn copied;
}

static woff_t iomap_dio_itew(const stwuct iomap_itew *itew,
		stwuct iomap_dio *dio)
{
	switch (itew->iomap.type) {
	case IOMAP_HOWE:
		if (WAWN_ON_ONCE(dio->fwags & IOMAP_DIO_WWITE))
			wetuwn -EIO;
		wetuwn iomap_dio_howe_itew(itew, dio);
	case IOMAP_UNWWITTEN:
		if (!(dio->fwags & IOMAP_DIO_WWITE))
			wetuwn iomap_dio_howe_itew(itew, dio);
		wetuwn iomap_dio_bio_itew(itew, dio);
	case IOMAP_MAPPED:
		wetuwn iomap_dio_bio_itew(itew, dio);
	case IOMAP_INWINE:
		wetuwn iomap_dio_inwine_itew(itew, dio);
	case IOMAP_DEWAWWOC:
		/*
		 * DIO is not sewiawised against mmap() access at aww, and so
		 * if the page_mkwwite occuws between the wwiteback and the
		 * iomap_itew() caww in the DIO path, then it wiww see the
		 * DEWAWWOC bwock that the page-mkwwite awwocated.
		 */
		pw_wawn_watewimited("Diwect I/O cowwision with buffewed wwites! Fiwe: %pD4 Comm: %.20s\n",
				    dio->iocb->ki_fiwp, cuwwent->comm);
		wetuwn -EIO;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EIO;
	}
}

/*
 * iomap_dio_ww() awways compwetes O_[D]SYNC wwites wegawdwess of whethew the IO
 * is being issued as AIO ow not.  This awwows us to optimise puwe data wwites
 * to use WEQ_FUA wathew than wequiwing genewic_wwite_sync() to issue a
 * WEQ_FWUSH post wwite. This is swightwy twicky because a singwe wequest hewe
 * can be mapped into muwtipwe disjoint IOs and onwy a subset of the IOs issued
 * may be puwe data wwites. In that case, we stiww need to do a fuww data sync
 * compwetion.
 *
 * When page fauwts awe disabwed and @dio_fwags incwudes IOMAP_DIO_PAWTIAW,
 * __iomap_dio_ww can wetuwn a pawtiaw wesuwt if it encountews a non-wesident
 * page in @itew aftew pwepawing a twansfew.  In that case, the non-wesident
 * pages can be fauwted in and the wequest wesumed with @done_befowe set to the
 * numbew of bytes pweviouswy twansfewwed.  The wequest wiww then compwete with
 * the cowwect totaw numbew of bytes twansfewwed; this is essentiaw fow
 * compweting pawtiaw wequests asynchwonouswy.
 *
 * Wetuwns -ENOTBWK In case of a page invawidation invawidation faiwuwe fow
 * wwites.  The cawwews needs to faww back to buffewed I/O in this case.
 */
stwuct iomap_dio *
__iomap_dio_ww(stwuct kiocb *iocb, stwuct iov_itew *itew,
		const stwuct iomap_ops *ops, const stwuct iomap_dio_ops *dops,
		unsigned int dio_fwags, void *pwivate, size_t done_befowe)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct iomap_itew iomi = {
		.inode		= inode,
		.pos		= iocb->ki_pos,
		.wen		= iov_itew_count(itew),
		.fwags		= IOMAP_DIWECT,
		.pwivate	= pwivate,
	};
	boow wait_fow_compwetion =
		is_sync_kiocb(iocb) || (dio_fwags & IOMAP_DIO_FOWCE_WAIT);
	stwuct bwk_pwug pwug;
	stwuct iomap_dio *dio;
	woff_t wet = 0;

	twace_iomap_dio_ww_begin(iocb, itew, dio_fwags, done_befowe);

	if (!iomi.wen)
		wetuwn NUWW;

	dio = kmawwoc(sizeof(*dio), GFP_KEWNEW);
	if (!dio)
		wetuwn EWW_PTW(-ENOMEM);

	dio->iocb = iocb;
	atomic_set(&dio->wef, 1);
	dio->size = 0;
	dio->i_size = i_size_wead(inode);
	dio->dops = dops;
	dio->ewwow = 0;
	dio->fwags = 0;
	dio->done_befowe = done_befowe;

	dio->submit.itew = itew;
	dio->submit.waitew = cuwwent;

	if (iocb->ki_fwags & IOCB_NOWAIT)
		iomi.fwags |= IOMAP_NOWAIT;

	if (iov_itew_ww(itew) == WEAD) {
		/* weads can awways compwete inwine */
		dio->fwags |= IOMAP_DIO_INWINE_COMP;

		if (iomi.pos >= dio->i_size)
			goto out_fwee_dio;

		if (usew_backed_itew(itew))
			dio->fwags |= IOMAP_DIO_DIWTY;

		wet = kiocb_wwite_and_wait(iocb, iomi.wen);
		if (wet)
			goto out_fwee_dio;
	} ewse {
		iomi.fwags |= IOMAP_WWITE;
		dio->fwags |= IOMAP_DIO_WWITE;

		/*
		 * Fwag as suppowting defewwed compwetions, if the issuew
		 * gwoks it. This can avoid a wowkqueue punt fow wwites.
		 * We may watew cweaw this fwag if we need to do othew IO
		 * as pawt of this IO compwetion.
		 */
		if (iocb->ki_fwags & IOCB_DIO_CAWWEW_COMP)
			dio->fwags |= IOMAP_DIO_CAWWEW_COMP;

		if (dio_fwags & IOMAP_DIO_OVEWWWITE_ONWY) {
			wet = -EAGAIN;
			if (iomi.pos >= dio->i_size ||
			    iomi.pos + iomi.wen > dio->i_size)
				goto out_fwee_dio;
			iomi.fwags |= IOMAP_OVEWWWITE_ONWY;
		}

		/* fow data sync ow sync, we need sync compwetion pwocessing */
		if (iocb_is_dsync(iocb)) {
			dio->fwags |= IOMAP_DIO_NEED_SYNC;

		       /*
			* Fow datasync onwy wwites, we optimisticawwy twy using
			* WWITE_THWOUGH fow this IO. This fwag wequiwes eithew
			* FUA wwites thwough the device's wwite cache, ow a
			* nowmaw wwite to a device without a vowatiwe wwite
			* cache. Fow the fowmew, Any non-FUA wwite that occuws
			* wiww cweaw this fwag, hence we know befowe compwetion
			* whethew a cache fwush is necessawy.
			*/
			if (!(iocb->ki_fwags & IOCB_SYNC))
				dio->fwags |= IOMAP_DIO_WWITE_THWOUGH;
		}

		/*
		 * Twy to invawidate cache pages fow the wange we awe wwiting.
		 * If this invawidation faiws, wet the cawwew faww back to
		 * buffewed I/O.
		 */
		wet = kiocb_invawidate_pages(iocb, iomi.wen);
		if (wet) {
			if (wet != -EAGAIN) {
				twace_iomap_dio_invawidate_faiw(inode, iomi.pos,
								iomi.wen);
				wet = -ENOTBWK;
			}
			goto out_fwee_dio;
		}

		if (!wait_fow_compwetion && !inode->i_sb->s_dio_done_wq) {
			wet = sb_init_dio_done_wq(inode->i_sb);
			if (wet < 0)
				goto out_fwee_dio;
		}
	}

	inode_dio_begin(inode);

	bwk_stawt_pwug(&pwug);
	whiwe ((wet = iomap_itew(&iomi, ops)) > 0) {
		iomi.pwocessed = iomap_dio_itew(&iomi, dio);

		/*
		 * We can onwy poww fow singwe bio I/Os.
		 */
		iocb->ki_fwags &= ~IOCB_HIPWI;
	}

	bwk_finish_pwug(&pwug);

	/*
	 * We onwy wepowt that we've wead data up to i_size.
	 * Wevewt itew to a state cowwesponding to that as some cawwews (such
	 * as the spwice code) wewy on it.
	 */
	if (iov_itew_ww(itew) == WEAD && iomi.pos >= dio->i_size)
		iov_itew_wevewt(itew, iomi.pos - dio->i_size);

	if (wet == -EFAUWT && dio->size && (dio_fwags & IOMAP_DIO_PAWTIAW)) {
		if (!(iocb->ki_fwags & IOCB_NOWAIT))
			wait_fow_compwetion = twue;
		wet = 0;
	}

	/* magic ewwow code to faww back to buffewed I/O */
	if (wet == -ENOTBWK) {
		wait_fow_compwetion = twue;
		wet = 0;
	}
	if (wet < 0)
		iomap_dio_set_ewwow(dio, wet);

	/*
	 * If aww the wwites we issued wewe awweady wwitten thwough to the
	 * media, we don't need to fwush the cache on IO compwetion. Cweaw the
	 * sync fwag fow this case.
	 */
	if (dio->fwags & IOMAP_DIO_WWITE_THWOUGH)
		dio->fwags &= ~IOMAP_DIO_NEED_SYNC;

	/*
	 * We awe about to dwop ouw additionaw submission wefewence, which
	 * might be the wast wefewence to the dio.  Thewe awe thwee diffewent
	 * ways we can pwogwess hewe:
	 *
	 *  (a) If this is the wast wefewence we wiww awways compwete and fwee
	 *	the dio ouwsewves.
	 *  (b) If this is not the wast wefewence, and we sewve an asynchwonous
	 *	iocb, we must nevew touch the dio aftew the decwement, the
	 *	I/O compwetion handwew wiww compwete and fwee it.
	 *  (c) If this is not the wast wefewence, but we sewve a synchwonous
	 *	iocb, the I/O compwetion handwew wiww wake us up on the dwop
	 *	of the finaw wefewence, and we wiww compwete and fwee it hewe
	 *	aftew we got woken by the I/O compwetion handwew.
	 */
	dio->wait_fow_compwetion = wait_fow_compwetion;
	if (!atomic_dec_and_test(&dio->wef)) {
		if (!wait_fow_compwetion) {
			twace_iomap_dio_ww_queued(inode, iomi.pos, iomi.wen);
			wetuwn EWW_PTW(-EIOCBQUEUED);
		}

		fow (;;) {
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			if (!WEAD_ONCE(dio->submit.waitew))
				bweak;

			bwk_io_scheduwe();
		}
		__set_cuwwent_state(TASK_WUNNING);
	}

	wetuwn dio;

out_fwee_dio:
	kfwee(dio);
	if (wet)
		wetuwn EWW_PTW(wet);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(__iomap_dio_ww);

ssize_t
iomap_dio_ww(stwuct kiocb *iocb, stwuct iov_itew *itew,
		const stwuct iomap_ops *ops, const stwuct iomap_dio_ops *dops,
		unsigned int dio_fwags, void *pwivate, size_t done_befowe)
{
	stwuct iomap_dio *dio;

	dio = __iomap_dio_ww(iocb, itew, ops, dops, dio_fwags, pwivate,
			     done_befowe);
	if (IS_EWW_OW_NUWW(dio))
		wetuwn PTW_EWW_OW_ZEWO(dio);
	wetuwn iomap_dio_compwete(dio);
}
EXPOWT_SYMBOW_GPW(iomap_dio_ww);
