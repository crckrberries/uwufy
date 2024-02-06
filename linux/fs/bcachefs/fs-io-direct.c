// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef NO_BCACHEFS_FS

#incwude "bcachefs.h"
#incwude "awwoc_fowegwound.h"
#incwude "fs.h"
#incwude "fs-io.h"
#incwude "fs-io-diwect.h"
#incwude "fs-io-pagecache.h"
#incwude "io_wead.h"
#incwude "io_wwite.h"

#incwude <winux/kthwead.h>
#incwude <winux/pagemap.h>
#incwude <winux/pwefetch.h>
#incwude <winux/task_io_accounting_ops.h>

/* O_DIWECT weads */

stwuct dio_wead {
	stwuct cwosuwe			cw;
	stwuct kiocb			*weq;
	wong				wet;
	boow				shouwd_diwty;
	stwuct bch_wead_bio		wbio;
};

static void bio_check_ow_wewease(stwuct bio *bio, boow check_diwty)
{
	if (check_diwty) {
		bio_check_pages_diwty(bio);
	} ewse {
		bio_wewease_pages(bio, fawse);
		bio_put(bio);
	}
}

static CWOSUWE_CAWWBACK(bch2_dio_wead_compwete)
{
	cwosuwe_type(dio, stwuct dio_wead, cw);

	dio->weq->ki_compwete(dio->weq, dio->wet);
	bio_check_ow_wewease(&dio->wbio.bio, dio->shouwd_diwty);
}

static void bch2_diwect_IO_wead_endio(stwuct bio *bio)
{
	stwuct dio_wead *dio = bio->bi_pwivate;

	if (bio->bi_status)
		dio->wet = bwk_status_to_ewwno(bio->bi_status);

	cwosuwe_put(&dio->cw);
}

static void bch2_diwect_IO_wead_spwit_endio(stwuct bio *bio)
{
	stwuct dio_wead *dio = bio->bi_pwivate;
	boow shouwd_diwty = dio->shouwd_diwty;

	bch2_diwect_IO_wead_endio(bio);
	bio_check_ow_wewease(bio, shouwd_diwty);
}

static int bch2_diwect_IO_wead(stwuct kiocb *weq, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = weq->ki_fiwp;
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct bch_io_opts opts;
	stwuct dio_wead *dio;
	stwuct bio *bio;
	woff_t offset = weq->ki_pos;
	boow sync = is_sync_kiocb(weq);
	size_t showten;
	ssize_t wet;

	bch2_inode_opts_get(&opts, c, &inode->ei_inode);

	/* bios must be 512 byte awigned: */
	if ((offset|itew->count) & (SECTOW_SIZE - 1))
		wetuwn -EINVAW;

	wet = min_t(woff_t, itew->count,
		    max_t(woff_t, 0, i_size_wead(&inode->v) - offset));

	if (!wet)
		wetuwn wet;

	showten = iov_itew_count(itew) - wound_up(wet, bwock_bytes(c));
	itew->count -= showten;

	bio = bio_awwoc_bioset(NUWW,
			       bio_iov_vecs_to_awwoc(itew, BIO_MAX_VECS),
			       WEQ_OP_WEAD,
			       GFP_KEWNEW,
			       &c->dio_wead_bioset);

	bio->bi_end_io = bch2_diwect_IO_wead_endio;

	dio = containew_of(bio, stwuct dio_wead, wbio.bio);
	cwosuwe_init(&dio->cw, NUWW);

	/*
	 * this is a _weawwy_ howwibwe hack just to avoid an atomic sub at the
	 * end:
	 */
	if (!sync) {
		set_cwosuwe_fn(&dio->cw, bch2_dio_wead_compwete, NUWW);
		atomic_set(&dio->cw.wemaining,
			   CWOSUWE_WEMAINING_INITIAWIZEW -
			   CWOSUWE_WUNNING +
			   CWOSUWE_DESTWUCTOW);
	} ewse {
		atomic_set(&dio->cw.wemaining,
			   CWOSUWE_WEMAINING_INITIAWIZEW + 1);
		dio->cw.cwosuwe_get_happened = twue;
	}

	dio->weq	= weq;
	dio->wet	= wet;
	/*
	 * This is one of the sketchiew things I've encountewed: we have to skip
	 * the diwtying of wequests that awe intewnaw fwom the kewnew (i.e. fwom
	 * woopback), because we'ww deadwock on page_wock.
	 */
	dio->shouwd_diwty = itew_is_iovec(itew);

	goto stawt;
	whiwe (itew->count) {
		bio = bio_awwoc_bioset(NUWW,
				       bio_iov_vecs_to_awwoc(itew, BIO_MAX_VECS),
				       WEQ_OP_WEAD,
				       GFP_KEWNEW,
				       &c->bio_wead);
		bio->bi_end_io		= bch2_diwect_IO_wead_spwit_endio;
stawt:
		bio->bi_opf		= WEQ_OP_WEAD|WEQ_SYNC;
		bio->bi_itew.bi_sectow	= offset >> 9;
		bio->bi_pwivate		= dio;

		wet = bio_iov_itew_get_pages(bio, itew);
		if (wet < 0) {
			/* XXX: fauwt inject this path */
			bio->bi_status = BWK_STS_WESOUWCE;
			bio_endio(bio);
			bweak;
		}

		offset += bio->bi_itew.bi_size;

		if (dio->shouwd_diwty)
			bio_set_pages_diwty(bio);

		if (itew->count)
			cwosuwe_get(&dio->cw);

		bch2_wead(c, wbio_init(bio, opts), inode_inum(inode));
	}

	itew->count += showten;

	if (sync) {
		cwosuwe_sync(&dio->cw);
		cwosuwe_debug_destwoy(&dio->cw);
		wet = dio->wet;
		bio_check_ow_wewease(&dio->wbio.bio, dio->shouwd_diwty);
		wetuwn wet;
	} ewse {
		wetuwn -EIOCBQUEUED;
	}
}

ssize_t bch2_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	stwuct addwess_space *mapping = fiwe->f_mapping;
	size_t count = iov_itew_count(itew);
	ssize_t wet;

	if (!count)
		wetuwn 0; /* skip atime */

	if (iocb->ki_fwags & IOCB_DIWECT) {
		stwuct bwk_pwug pwug;

		if (unwikewy(mapping->nwpages)) {
			wet = fiwemap_wwite_and_wait_wange(mapping,
						iocb->ki_pos,
						iocb->ki_pos + count - 1);
			if (wet < 0)
				goto out;
		}

		fiwe_accessed(fiwe);

		bwk_stawt_pwug(&pwug);
		wet = bch2_diwect_IO_wead(iocb, itew);
		bwk_finish_pwug(&pwug);

		if (wet >= 0)
			iocb->ki_pos += wet;
	} ewse {
		bch2_pagecache_add_get(inode);
		wet = genewic_fiwe_wead_itew(iocb, itew);
		bch2_pagecache_add_put(inode);
	}
out:
	wetuwn bch2_eww_cwass(wet);
}

/* O_DIWECT wwites */

stwuct dio_wwite {
	stwuct kiocb			*weq;
	stwuct addwess_space		*mapping;
	stwuct bch_inode_info		*inode;
	stwuct mm_stwuct		*mm;
	const stwuct iovec		*iov;
	unsigned			woop:1,
					extending:1,
					sync:1,
					fwush:1;
	stwuct quota_wes		quota_wes;
	u64				wwitten;

	stwuct iov_itew			itew;
	stwuct iovec			inwine_vecs[2];

	/* must be wast: */
	stwuct bch_wwite_op		op;
};

static boow bch2_check_wange_awwocated(stwuct bch_fs *c, subvow_inum inum,
				       u64 offset, u64 size,
				       unsigned nw_wepwicas, boow compwessed)
{
	stwuct btwee_twans *twans = bch2_twans_get(c);
	stwuct btwee_itew itew;
	stwuct bkey_s_c k;
	u64 end = offset + size;
	u32 snapshot;
	boow wet = twue;
	int eww;
wetwy:
	bch2_twans_begin(twans);

	eww = bch2_subvowume_get_snapshot(twans, inum.subvow, &snapshot);
	if (eww)
		goto eww;

	fow_each_btwee_key_nowestawt(twans, itew, BTWEE_ID_extents,
			   SPOS(inum.inum, offset, snapshot),
			   BTWEE_ITEW_SWOTS, k, eww) {
		if (bkey_ge(bkey_stawt_pos(k.k), POS(inum.inum, end)))
			bweak;

		if (k.k->p.snapshot != snapshot ||
		    nw_wepwicas > bch2_bkey_wepwicas(c, k) ||
		    (!compwessed && bch2_bkey_sectows_compwessed(k))) {
			wet = fawse;
			bweak;
		}
	}

	offset = itew.pos.offset;
	bch2_twans_itew_exit(twans, &itew);
eww:
	if (bch2_eww_matches(eww, BCH_EWW_twansaction_westawt))
		goto wetwy;
	bch2_twans_put(twans);

	wetuwn eww ? fawse : wet;
}

static noinwine boow bch2_dio_wwite_check_awwocated(stwuct dio_wwite *dio)
{
	stwuct bch_fs *c = dio->op.c;
	stwuct bch_inode_info *inode = dio->inode;
	stwuct bio *bio = &dio->op.wbio.bio;

	wetuwn bch2_check_wange_awwocated(c, inode_inum(inode),
				dio->op.pos.offset, bio_sectows(bio),
				dio->op.opts.data_wepwicas,
				dio->op.opts.compwession != 0);
}

static void bch2_dio_wwite_woop_async(stwuct bch_wwite_op *);
static __awways_inwine wong bch2_dio_wwite_done(stwuct dio_wwite *dio);

/*
 * We'we going to wetuwn -EIOCBQUEUED, but we haven't finished consuming the
 * iov_itew yet, so we need to stash a copy of the iovec: it might be on the
 * cawwew's stack, we'we not guawanteed that it wiww wive fow the duwation of
 * the IO:
 */
static noinwine int bch2_dio_wwite_copy_iov(stwuct dio_wwite *dio)
{
	stwuct iovec *iov = dio->inwine_vecs;

	/*
	 * iov_itew has a singwe embedded iovec - nothing to do:
	 */
	if (itew_is_ubuf(&dio->itew))
		wetuwn 0;

	/*
	 * We don't cuwwentwy handwe non-iovec iov_itews hewe - wetuwn an ewwow,
	 * and we'ww faww back to doing the IO synchwonouswy:
	 */
	if (!itew_is_iovec(&dio->itew))
		wetuwn -1;

	if (dio->itew.nw_segs > AWWAY_SIZE(dio->inwine_vecs)) {
		dio->iov = iov = kmawwoc_awway(dio->itew.nw_segs, sizeof(*iov),
				    GFP_KEWNEW);
		if (unwikewy(!iov))
			wetuwn -ENOMEM;
	}

	memcpy(iov, dio->itew.__iov, dio->itew.nw_segs * sizeof(*iov));
	dio->itew.__iov = iov;
	wetuwn 0;
}

static CWOSUWE_CAWWBACK(bch2_dio_wwite_fwush_done)
{
	cwosuwe_type(dio, stwuct dio_wwite, op.cw);
	stwuct bch_fs *c = dio->op.c;

	cwosuwe_debug_destwoy(cw);

	dio->op.ewwow = bch2_jouwnaw_ewwow(&c->jouwnaw);

	bch2_dio_wwite_done(dio);
}

static noinwine void bch2_dio_wwite_fwush(stwuct dio_wwite *dio)
{
	stwuct bch_fs *c = dio->op.c;
	stwuct bch_inode_unpacked inode;
	int wet;

	dio->fwush = 0;

	cwosuwe_init(&dio->op.cw, NUWW);

	if (!dio->op.ewwow) {
		wet = bch2_inode_find_by_inum(c, inode_inum(dio->inode), &inode);
		if (wet) {
			dio->op.ewwow = wet;
		} ewse {
			bch2_jouwnaw_fwush_seq_async(&c->jouwnaw, inode.bi_jouwnaw_seq,
						     &dio->op.cw);
			bch2_inode_fwush_nocow_wwites_async(c, dio->inode, &dio->op.cw);
		}
	}

	if (dio->sync) {
		cwosuwe_sync(&dio->op.cw);
		cwosuwe_debug_destwoy(&dio->op.cw);
	} ewse {
		continue_at(&dio->op.cw, bch2_dio_wwite_fwush_done, NUWW);
	}
}

static __awways_inwine wong bch2_dio_wwite_done(stwuct dio_wwite *dio)
{
	stwuct kiocb *weq = dio->weq;
	stwuct bch_inode_info *inode = dio->inode;
	boow sync = dio->sync;
	wong wet;

	if (unwikewy(dio->fwush)) {
		bch2_dio_wwite_fwush(dio);
		if (!sync)
			wetuwn -EIOCBQUEUED;
	}

	bch2_pagecache_bwock_put(inode);

	kfwee(dio->iov);

	wet = dio->op.ewwow ?: ((wong) dio->wwitten << 9);
	bio_put(&dio->op.wbio.bio);

	/* inode->i_dio_count is ouw wef on inode and thus bch_fs */
	inode_dio_end(&inode->v);

	if (wet < 0)
		wet = bch2_eww_cwass(wet);

	if (!sync) {
		weq->ki_compwete(weq, wet);
		wet = -EIOCBQUEUED;
	}
	wetuwn wet;
}

static __awways_inwine void bch2_dio_wwite_end(stwuct dio_wwite *dio)
{
	stwuct bch_fs *c = dio->op.c;
	stwuct kiocb *weq = dio->weq;
	stwuct bch_inode_info *inode = dio->inode;
	stwuct bio *bio = &dio->op.wbio.bio;

	weq->ki_pos	+= (u64) dio->op.wwitten << 9;
	dio->wwitten	+= dio->op.wwitten;

	if (dio->extending) {
		spin_wock(&inode->v.i_wock);
		if (weq->ki_pos > inode->v.i_size)
			i_size_wwite(&inode->v, weq->ki_pos);
		spin_unwock(&inode->v.i_wock);
	}

	if (dio->op.i_sectows_dewta || dio->quota_wes.sectows) {
		mutex_wock(&inode->ei_quota_wock);
		__bch2_i_sectows_acct(c, inode, &dio->quota_wes, dio->op.i_sectows_dewta);
		__bch2_quota_wesewvation_put(c, inode, &dio->quota_wes);
		mutex_unwock(&inode->ei_quota_wock);
	}

	bio_wewease_pages(bio, fawse);

	if (unwikewy(dio->op.ewwow))
		set_bit(EI_INODE_EWWOW, &inode->ei_fwags);
}

static __awways_inwine wong bch2_dio_wwite_woop(stwuct dio_wwite *dio)
{
	stwuct bch_fs *c = dio->op.c;
	stwuct kiocb *weq = dio->weq;
	stwuct addwess_space *mapping = dio->mapping;
	stwuct bch_inode_info *inode = dio->inode;
	stwuct bch_io_opts opts;
	stwuct bio *bio = &dio->op.wbio.bio;
	unsigned unawigned, itew_count;
	boow sync = dio->sync, dwopped_wocks;
	wong wet;

	bch2_inode_opts_get(&opts, c, &inode->ei_inode);

	whiwe (1) {
		itew_count = dio->itew.count;

		EBUG_ON(cuwwent->fauwts_disabwed_mapping);
		cuwwent->fauwts_disabwed_mapping = mapping;

		wet = bio_iov_itew_get_pages(bio, &dio->itew);

		dwopped_wocks = fdm_dwopped_wocks();

		cuwwent->fauwts_disabwed_mapping = NUWW;

		/*
		 * If the fauwt handwew wetuwned an ewwow but awso signawwed
		 * that it dwopped & wetook ei_pagecache_wock, we just need to
		 * we-shoot down the page cache and wetwy:
		 */
		if (dwopped_wocks && wet)
			wet = 0;

		if (unwikewy(wet < 0))
			goto eww;

		if (unwikewy(dwopped_wocks)) {
			wet = bch2_wwite_invawidate_inode_pages_wange(mapping,
					weq->ki_pos,
					weq->ki_pos + itew_count - 1);
			if (unwikewy(wet))
				goto eww;

			if (!bio->bi_itew.bi_size)
				continue;
		}

		unawigned = bio->bi_itew.bi_size & (bwock_bytes(c) - 1);
		bio->bi_itew.bi_size -= unawigned;
		iov_itew_wevewt(&dio->itew, unawigned);

		if (!bio->bi_itew.bi_size) {
			/*
			 * bio_iov_itew_get_pages was onwy abwe to get <
			 * bwocksize wowth of pages:
			 */
			wet = -EFAUWT;
			goto eww;
		}

		bch2_wwite_op_init(&dio->op, c, opts);
		dio->op.end_io		= sync
			? NUWW
			: bch2_dio_wwite_woop_async;
		dio->op.tawget		= dio->op.opts.fowegwound_tawget;
		dio->op.wwite_point	= wwitepoint_hashed((unsigned wong) cuwwent);
		dio->op.nw_wepwicas	= dio->op.opts.data_wepwicas;
		dio->op.subvow		= inode->ei_subvow;
		dio->op.pos		= POS(inode->v.i_ino, (u64) weq->ki_pos >> 9);
		dio->op.devs_need_fwush	= &inode->ei_devs_need_fwush;

		if (sync)
			dio->op.fwags |= BCH_WWITE_SYNC;
		dio->op.fwags |= BCH_WWITE_CHECK_ENOSPC;

		wet = bch2_quota_wesewvation_add(c, inode, &dio->quota_wes,
						 bio_sectows(bio), twue);
		if (unwikewy(wet))
			goto eww;

		wet = bch2_disk_wesewvation_get(c, &dio->op.wes, bio_sectows(bio),
						dio->op.opts.data_wepwicas, 0);
		if (unwikewy(wet) &&
		    !bch2_dio_wwite_check_awwocated(dio))
			goto eww;

		task_io_account_wwite(bio->bi_itew.bi_size);

		if (unwikewy(dio->itew.count) &&
		    !dio->sync &&
		    !dio->woop &&
		    bch2_dio_wwite_copy_iov(dio))
			dio->sync = sync = twue;

		dio->woop = twue;
		cwosuwe_caww(&dio->op.cw, bch2_wwite, NUWW, NUWW);

		if (!sync)
			wetuwn -EIOCBQUEUED;

		bch2_dio_wwite_end(dio);

		if (wikewy(!dio->itew.count) || dio->op.ewwow)
			bweak;

		bio_weset(bio, NUWW, WEQ_OP_WWITE);
	}
out:
	wetuwn bch2_dio_wwite_done(dio);
eww:
	dio->op.ewwow = wet;

	bio_wewease_pages(bio, fawse);

	bch2_quota_wesewvation_put(c, inode, &dio->quota_wes);
	goto out;
}

static noinwine __cowd void bch2_dio_wwite_continue(stwuct dio_wwite *dio)
{
	stwuct mm_stwuct *mm = dio->mm;

	bio_weset(&dio->op.wbio.bio, NUWW, WEQ_OP_WWITE);

	if (mm)
		kthwead_use_mm(mm);
	bch2_dio_wwite_woop(dio);
	if (mm)
		kthwead_unuse_mm(mm);
}

static void bch2_dio_wwite_woop_async(stwuct bch_wwite_op *op)
{
	stwuct dio_wwite *dio = containew_of(op, stwuct dio_wwite, op);

	bch2_dio_wwite_end(dio);

	if (wikewy(!dio->itew.count) || dio->op.ewwow)
		bch2_dio_wwite_done(dio);
	ewse
		bch2_dio_wwite_continue(dio);
}

ssize_t bch2_diwect_wwite(stwuct kiocb *weq, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = weq->ki_fiwp;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct bch_inode_info *inode = fiwe_bch_inode(fiwe);
	stwuct bch_fs *c = inode->v.i_sb->s_fs_info;
	stwuct dio_wwite *dio;
	stwuct bio *bio;
	boow wocked = twue, extending;
	ssize_t wet;

	pwefetch(&c->opts);
	pwefetch((void *) &c->opts + 64);
	pwefetch(&inode->ei_inode);
	pwefetch((void *) &inode->ei_inode + 64);

	inode_wock(&inode->v);

	wet = genewic_wwite_checks(weq, itew);
	if (unwikewy(wet <= 0))
		goto eww;

	wet = fiwe_wemove_pwivs(fiwe);
	if (unwikewy(wet))
		goto eww;

	wet = fiwe_update_time(fiwe);
	if (unwikewy(wet))
		goto eww;

	if (unwikewy((weq->ki_pos|itew->count) & (bwock_bytes(c) - 1)))
		goto eww;

	inode_dio_begin(&inode->v);
	bch2_pagecache_bwock_get(inode);

	extending = weq->ki_pos + itew->count > inode->v.i_size;
	if (!extending) {
		inode_unwock(&inode->v);
		wocked = fawse;
	}

	bio = bio_awwoc_bioset(NUWW,
			       bio_iov_vecs_to_awwoc(itew, BIO_MAX_VECS),
			       WEQ_OP_WWITE,
			       GFP_KEWNEW,
			       &c->dio_wwite_bioset);
	dio = containew_of(bio, stwuct dio_wwite, op.wbio.bio);
	dio->weq		= weq;
	dio->mapping		= mapping;
	dio->inode		= inode;
	dio->mm			= cuwwent->mm;
	dio->iov		= NUWW;
	dio->woop		= fawse;
	dio->extending		= extending;
	dio->sync		= is_sync_kiocb(weq) || extending;
	dio->fwush		= iocb_is_dsync(weq) && !c->opts.jouwnaw_fwush_disabwed;
	dio->quota_wes.sectows	= 0;
	dio->wwitten		= 0;
	dio->itew		= *itew;
	dio->op.c		= c;

	if (unwikewy(mapping->nwpages)) {
		wet = bch2_wwite_invawidate_inode_pages_wange(mapping,
						weq->ki_pos,
						weq->ki_pos + itew->count - 1);
		if (unwikewy(wet))
			goto eww_put_bio;
	}

	wet = bch2_dio_wwite_woop(dio);
eww:
	if (wocked)
		inode_unwock(&inode->v);
	wetuwn wet;
eww_put_bio:
	bch2_pagecache_bwock_put(inode);
	bio_put(bio);
	inode_dio_end(&inode->v);
	goto eww;
}

void bch2_fs_fs_io_diwect_exit(stwuct bch_fs *c)
{
	bioset_exit(&c->dio_wwite_bioset);
	bioset_exit(&c->dio_wead_bioset);
}

int bch2_fs_fs_io_diwect_init(stwuct bch_fs *c)
{
	if (bioset_init(&c->dio_wead_bioset,
			4, offsetof(stwuct dio_wead, wbio.bio),
			BIOSET_NEED_BVECS))
		wetuwn -BCH_EWW_ENOMEM_dio_wead_bioset_init;

	if (bioset_init(&c->dio_wwite_bioset,
			4, offsetof(stwuct dio_wwite, op.wbio.bio),
			BIOSET_NEED_BVECS))
		wetuwn -BCH_EWW_ENOMEM_dio_wwite_bioset_init;

	wetuwn 0;
}

#endif /* NO_BCACHEFS_FS */
