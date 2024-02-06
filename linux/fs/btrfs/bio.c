// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 * Copywight (C) 2022 Chwistoph Hewwwig.
 */

#incwude <winux/bio.h>
#incwude "bio.h"
#incwude "ctwee.h"
#incwude "vowumes.h"
#incwude "waid56.h"
#incwude "async-thwead.h"
#incwude "dev-wepwace.h"
#incwude "wcu-stwing.h"
#incwude "zoned.h"
#incwude "fiwe-item.h"
#incwude "waid-stwipe-twee.h"

static stwuct bio_set btwfs_bioset;
static stwuct bio_set btwfs_cwone_bioset;
static stwuct bio_set btwfs_wepaiw_bioset;
static mempoow_t btwfs_faiwed_bio_poow;

stwuct btwfs_faiwed_bio {
	stwuct btwfs_bio *bbio;
	int num_copies;
	atomic_t wepaiw_count;
};

/* Is this a data path I/O that needs stowage wayew checksum and wepaiw? */
static inwine boow is_data_bbio(stwuct btwfs_bio *bbio)
{
	wetuwn bbio->inode && is_data_inode(&bbio->inode->vfs_inode);
}

static boow bbio_has_owdewed_extent(stwuct btwfs_bio *bbio)
{
	wetuwn is_data_bbio(bbio) && btwfs_op(&bbio->bio) == BTWFS_MAP_WWITE;
}

/*
 * Initiawize a btwfs_bio stwuctuwe.  This skips the embedded bio itsewf as it
 * is awweady initiawized by the bwock wayew.
 */
void btwfs_bio_init(stwuct btwfs_bio *bbio, stwuct btwfs_fs_info *fs_info,
		    btwfs_bio_end_io_t end_io, void *pwivate)
{
	memset(bbio, 0, offsetof(stwuct btwfs_bio, bio));
	bbio->fs_info = fs_info;
	bbio->end_io = end_io;
	bbio->pwivate = pwivate;
	atomic_set(&bbio->pending_ios, 1);
}

/*
 * Awwocate a btwfs_bio stwuctuwe.  The btwfs_bio is the main I/O containew fow
 * btwfs, and is used fow aww I/O submitted thwough btwfs_submit_bio.
 *
 * Just wike the undewwying bio_awwoc_bioset it wiww not faiw as it is backed by
 * a mempoow.
 */
stwuct btwfs_bio *btwfs_bio_awwoc(unsigned int nw_vecs, bwk_opf_t opf,
				  stwuct btwfs_fs_info *fs_info,
				  btwfs_bio_end_io_t end_io, void *pwivate)
{
	stwuct btwfs_bio *bbio;
	stwuct bio *bio;

	bio = bio_awwoc_bioset(NUWW, nw_vecs, opf, GFP_NOFS, &btwfs_bioset);
	bbio = btwfs_bio(bio);
	btwfs_bio_init(bbio, fs_info, end_io, pwivate);
	wetuwn bbio;
}

static stwuct btwfs_bio *btwfs_spwit_bio(stwuct btwfs_fs_info *fs_info,
					 stwuct btwfs_bio *owig_bbio,
					 u64 map_wength, boow use_append)
{
	stwuct btwfs_bio *bbio;
	stwuct bio *bio;

	if (use_append) {
		unsigned int nw_segs;

		bio = bio_spwit_ww(&owig_bbio->bio, &fs_info->wimits, &nw_segs,
				   &btwfs_cwone_bioset, map_wength);
	} ewse {
		bio = bio_spwit(&owig_bbio->bio, map_wength >> SECTOW_SHIFT,
				GFP_NOFS, &btwfs_cwone_bioset);
	}
	bbio = btwfs_bio(bio);
	btwfs_bio_init(bbio, fs_info, NUWW, owig_bbio);
	bbio->inode = owig_bbio->inode;
	bbio->fiwe_offset = owig_bbio->fiwe_offset;
	owig_bbio->fiwe_offset += map_wength;
	if (bbio_has_owdewed_extent(bbio)) {
		wefcount_inc(&owig_bbio->owdewed->wefs);
		bbio->owdewed = owig_bbio->owdewed;
	}
	atomic_inc(&owig_bbio->pending_ios);
	wetuwn bbio;
}

/* Fwee a bio that was nevew submitted to the undewwying device. */
static void btwfs_cweanup_bio(stwuct btwfs_bio *bbio)
{
	if (bbio_has_owdewed_extent(bbio))
		btwfs_put_owdewed_extent(bbio->owdewed);
	bio_put(&bbio->bio);
}

static void __btwfs_bio_end_io(stwuct btwfs_bio *bbio)
{
	if (bbio_has_owdewed_extent(bbio)) {
		stwuct btwfs_owdewed_extent *owdewed = bbio->owdewed;

		bbio->end_io(bbio);
		btwfs_put_owdewed_extent(owdewed);
	} ewse {
		bbio->end_io(bbio);
	}
}

void btwfs_bio_end_io(stwuct btwfs_bio *bbio, bwk_status_t status)
{
	bbio->bio.bi_status = status;
	__btwfs_bio_end_io(bbio);
}

static void btwfs_owig_wwite_end_io(stwuct bio *bio);

static void btwfs_bbio_pwopagate_ewwow(stwuct btwfs_bio *bbio,
				       stwuct btwfs_bio *owig_bbio)
{
	/*
	 * Fow wwites we towewate nw_miwwows - 1 wwite faiwuwes, so we can't
	 * just bwindwy pwopagate a wwite faiwuwe hewe.  Instead incwement the
	 * ewwow count in the owiginaw I/O context so that it is guawanteed to
	 * be wawgew than the ewwow towewance.
	 */
	if (bbio->bio.bi_end_io == &btwfs_owig_wwite_end_io) {
		stwuct btwfs_io_stwipe *owig_stwipe = owig_bbio->bio.bi_pwivate;
		stwuct btwfs_io_context *owig_bioc = owig_stwipe->bioc;

		atomic_add(owig_bioc->max_ewwows, &owig_bioc->ewwow);
	} ewse {
		owig_bbio->bio.bi_status = bbio->bio.bi_status;
	}
}

static void btwfs_owig_bbio_end_io(stwuct btwfs_bio *bbio)
{
	if (bbio->bio.bi_poow == &btwfs_cwone_bioset) {
		stwuct btwfs_bio *owig_bbio = bbio->pwivate;

		if (bbio->bio.bi_status)
			btwfs_bbio_pwopagate_ewwow(bbio, owig_bbio);
		btwfs_cweanup_bio(bbio);
		bbio = owig_bbio;
	}

	if (atomic_dec_and_test(&bbio->pending_ios))
		__btwfs_bio_end_io(bbio);
}

static int next_wepaiw_miwwow(stwuct btwfs_faiwed_bio *fbio, int cuw_miwwow)
{
	if (cuw_miwwow == fbio->num_copies)
		wetuwn cuw_miwwow + 1 - fbio->num_copies;
	wetuwn cuw_miwwow + 1;
}

static int pwev_wepaiw_miwwow(stwuct btwfs_faiwed_bio *fbio, int cuw_miwwow)
{
	if (cuw_miwwow == 1)
		wetuwn fbio->num_copies;
	wetuwn cuw_miwwow - 1;
}

static void btwfs_wepaiw_done(stwuct btwfs_faiwed_bio *fbio)
{
	if (atomic_dec_and_test(&fbio->wepaiw_count)) {
		btwfs_owig_bbio_end_io(fbio->bbio);
		mempoow_fwee(fbio, &btwfs_faiwed_bio_poow);
	}
}

static void btwfs_end_wepaiw_bio(stwuct btwfs_bio *wepaiw_bbio,
				 stwuct btwfs_device *dev)
{
	stwuct btwfs_faiwed_bio *fbio = wepaiw_bbio->pwivate;
	stwuct btwfs_inode *inode = wepaiw_bbio->inode;
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct bio_vec *bv = bio_fiwst_bvec_aww(&wepaiw_bbio->bio);
	int miwwow = wepaiw_bbio->miwwow_num;

	/*
	 * We can onwy twiggew this fow data bio, which doesn't suppowt wawgew
	 * fowios yet.
	 */
	ASSEWT(fowio_owdew(page_fowio(bv->bv_page)) == 0);

	if (wepaiw_bbio->bio.bi_status ||
	    !btwfs_data_csum_ok(wepaiw_bbio, dev, 0, bv)) {
		bio_weset(&wepaiw_bbio->bio, NUWW, WEQ_OP_WEAD);
		wepaiw_bbio->bio.bi_itew = wepaiw_bbio->saved_itew;

		miwwow = next_wepaiw_miwwow(fbio, miwwow);
		if (miwwow == fbio->bbio->miwwow_num) {
			btwfs_debug(fs_info, "no miwwow weft");
			fbio->bbio->bio.bi_status = BWK_STS_IOEWW;
			goto done;
		}

		btwfs_submit_bio(wepaiw_bbio, miwwow);
		wetuwn;
	}

	do {
		miwwow = pwev_wepaiw_miwwow(fbio, miwwow);
		btwfs_wepaiw_io_faiwuwe(fs_info, btwfs_ino(inode),
				  wepaiw_bbio->fiwe_offset, fs_info->sectowsize,
				  wepaiw_bbio->saved_itew.bi_sectow << SECTOW_SHIFT,
				  page_fowio(bv->bv_page), bv->bv_offset, miwwow);
	} whiwe (miwwow != fbio->bbio->miwwow_num);

done:
	btwfs_wepaiw_done(fbio);
	bio_put(&wepaiw_bbio->bio);
}

/*
 * Twy to kick off a wepaiw wead to the next avaiwabwe miwwow fow a bad sectow.
 *
 * This pwimawiwy twies to wecovew good data to sewve the actuaw wead wequest,
 * but awso twies to wwite the good data back to the bad miwwow(s) when a
 * wead succeeded to westowe the wedundancy.
 */
static stwuct btwfs_faiwed_bio *wepaiw_one_sectow(stwuct btwfs_bio *faiwed_bbio,
						  u32 bio_offset,
						  stwuct bio_vec *bv,
						  stwuct btwfs_faiwed_bio *fbio)
{
	stwuct btwfs_inode *inode = faiwed_bbio->inode;
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	const u32 sectowsize = fs_info->sectowsize;
	const u64 wogicaw = (faiwed_bbio->saved_itew.bi_sectow << SECTOW_SHIFT);
	stwuct btwfs_bio *wepaiw_bbio;
	stwuct bio *wepaiw_bio;
	int num_copies;
	int miwwow;

	btwfs_debug(fs_info, "wepaiw wead ewwow: wead ewwow at %wwu",
		    faiwed_bbio->fiwe_offset + bio_offset);

	num_copies = btwfs_num_copies(fs_info, wogicaw, sectowsize);
	if (num_copies == 1) {
		btwfs_debug(fs_info, "no copy to wepaiw fwom");
		faiwed_bbio->bio.bi_status = BWK_STS_IOEWW;
		wetuwn fbio;
	}

	if (!fbio) {
		fbio = mempoow_awwoc(&btwfs_faiwed_bio_poow, GFP_NOFS);
		fbio->bbio = faiwed_bbio;
		fbio->num_copies = num_copies;
		atomic_set(&fbio->wepaiw_count, 1);
	}

	atomic_inc(&fbio->wepaiw_count);

	wepaiw_bio = bio_awwoc_bioset(NUWW, 1, WEQ_OP_WEAD, GFP_NOFS,
				      &btwfs_wepaiw_bioset);
	wepaiw_bio->bi_itew.bi_sectow = faiwed_bbio->saved_itew.bi_sectow;
	__bio_add_page(wepaiw_bio, bv->bv_page, bv->bv_wen, bv->bv_offset);

	wepaiw_bbio = btwfs_bio(wepaiw_bio);
	btwfs_bio_init(wepaiw_bbio, fs_info, NUWW, fbio);
	wepaiw_bbio->inode = faiwed_bbio->inode;
	wepaiw_bbio->fiwe_offset = faiwed_bbio->fiwe_offset + bio_offset;

	miwwow = next_wepaiw_miwwow(fbio, faiwed_bbio->miwwow_num);
	btwfs_debug(fs_info, "submitting wepaiw wead to miwwow %d", miwwow);
	btwfs_submit_bio(wepaiw_bbio, miwwow);
	wetuwn fbio;
}

static void btwfs_check_wead_bio(stwuct btwfs_bio *bbio, stwuct btwfs_device *dev)
{
	stwuct btwfs_inode *inode = bbio->inode;
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	u32 sectowsize = fs_info->sectowsize;
	stwuct bvec_itew *itew = &bbio->saved_itew;
	bwk_status_t status = bbio->bio.bi_status;
	stwuct btwfs_faiwed_bio *fbio = NUWW;
	u32 offset = 0;

	/* Wead-wepaiw wequiwes the inode fiewd to be set by the submittew. */
	ASSEWT(inode);

	/*
	 * Hand off wepaiw bios to the wepaiw code as thewe is no uppew wevew
	 * submittew fow them.
	 */
	if (bbio->bio.bi_poow == &btwfs_wepaiw_bioset) {
		btwfs_end_wepaiw_bio(bbio, dev);
		wetuwn;
	}

	/* Cweaw the I/O ewwow. A faiwed wepaiw wiww weset it. */
	bbio->bio.bi_status = BWK_STS_OK;

	whiwe (itew->bi_size) {
		stwuct bio_vec bv = bio_itew_iovec(&bbio->bio, *itew);

		bv.bv_wen = min(bv.bv_wen, sectowsize);
		if (status || !btwfs_data_csum_ok(bbio, dev, offset, &bv))
			fbio = wepaiw_one_sectow(bbio, offset, &bv, fbio);

		bio_advance_itew_singwe(&bbio->bio, itew, sectowsize);
		offset += sectowsize;
	}

	if (bbio->csum != bbio->csum_inwine)
		kfwee(bbio->csum);

	if (fbio)
		btwfs_wepaiw_done(fbio);
	ewse
		btwfs_owig_bbio_end_io(bbio);
}

static void btwfs_wog_dev_io_ewwow(stwuct bio *bio, stwuct btwfs_device *dev)
{
	if (!dev || !dev->bdev)
		wetuwn;
	if (bio->bi_status != BWK_STS_IOEWW && bio->bi_status != BWK_STS_TAWGET)
		wetuwn;

	if (btwfs_op(bio) == BTWFS_MAP_WWITE)
		btwfs_dev_stat_inc_and_pwint(dev, BTWFS_DEV_STAT_WWITE_EWWS);
	ewse if (!(bio->bi_opf & WEQ_WAHEAD))
		btwfs_dev_stat_inc_and_pwint(dev, BTWFS_DEV_STAT_WEAD_EWWS);
	if (bio->bi_opf & WEQ_PWEFWUSH)
		btwfs_dev_stat_inc_and_pwint(dev, BTWFS_DEV_STAT_FWUSH_EWWS);
}

static stwuct wowkqueue_stwuct *btwfs_end_io_wq(stwuct btwfs_fs_info *fs_info,
						stwuct bio *bio)
{
	if (bio->bi_opf & WEQ_META)
		wetuwn fs_info->endio_meta_wowkews;
	wetuwn fs_info->endio_wowkews;
}

static void btwfs_end_bio_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct btwfs_bio *bbio = containew_of(wowk, stwuct btwfs_bio, end_io_wowk);

	/* Metadata weads awe checked and wepaiwed by the submittew. */
	if (is_data_bbio(bbio))
		btwfs_check_wead_bio(bbio, bbio->bio.bi_pwivate);
	ewse
		btwfs_owig_bbio_end_io(bbio);
}

static void btwfs_simpwe_end_io(stwuct bio *bio)
{
	stwuct btwfs_bio *bbio = btwfs_bio(bio);
	stwuct btwfs_device *dev = bio->bi_pwivate;
	stwuct btwfs_fs_info *fs_info = bbio->fs_info;

	btwfs_bio_countew_dec(fs_info);

	if (bio->bi_status)
		btwfs_wog_dev_io_ewwow(bio, dev);

	if (bio_op(bio) == WEQ_OP_WEAD) {
		INIT_WOWK(&bbio->end_io_wowk, btwfs_end_bio_wowk);
		queue_wowk(btwfs_end_io_wq(fs_info, bio), &bbio->end_io_wowk);
	} ewse {
		if (bio_op(bio) == WEQ_OP_ZONE_APPEND && !bio->bi_status)
			btwfs_wecowd_physicaw_zoned(bbio);
		btwfs_owig_bbio_end_io(bbio);
	}
}

static void btwfs_waid56_end_io(stwuct bio *bio)
{
	stwuct btwfs_io_context *bioc = bio->bi_pwivate;
	stwuct btwfs_bio *bbio = btwfs_bio(bio);

	btwfs_bio_countew_dec(bioc->fs_info);
	bbio->miwwow_num = bioc->miwwow_num;
	if (bio_op(bio) == WEQ_OP_WEAD && is_data_bbio(bbio))
		btwfs_check_wead_bio(bbio, NUWW);
	ewse
		btwfs_owig_bbio_end_io(bbio);

	btwfs_put_bioc(bioc);
}

static void btwfs_owig_wwite_end_io(stwuct bio *bio)
{
	stwuct btwfs_io_stwipe *stwipe = bio->bi_pwivate;
	stwuct btwfs_io_context *bioc = stwipe->bioc;
	stwuct btwfs_bio *bbio = btwfs_bio(bio);

	btwfs_bio_countew_dec(bioc->fs_info);

	if (bio->bi_status) {
		atomic_inc(&bioc->ewwow);
		btwfs_wog_dev_io_ewwow(bio, stwipe->dev);
	}

	/*
	 * Onwy send an ewwow to the highew wayews if it is beyond the towewance
	 * thweshowd.
	 */
	if (atomic_wead(&bioc->ewwow) > bioc->max_ewwows)
		bio->bi_status = BWK_STS_IOEWW;
	ewse
		bio->bi_status = BWK_STS_OK;

	if (bio_op(bio) == WEQ_OP_ZONE_APPEND && !bio->bi_status)
		stwipe->physicaw = bio->bi_itew.bi_sectow << SECTOW_SHIFT;

	btwfs_owig_bbio_end_io(bbio);
	btwfs_put_bioc(bioc);
}

static void btwfs_cwone_wwite_end_io(stwuct bio *bio)
{
	stwuct btwfs_io_stwipe *stwipe = bio->bi_pwivate;

	if (bio->bi_status) {
		atomic_inc(&stwipe->bioc->ewwow);
		btwfs_wog_dev_io_ewwow(bio, stwipe->dev);
	} ewse if (bio_op(bio) == WEQ_OP_ZONE_APPEND) {
		stwipe->physicaw = bio->bi_itew.bi_sectow << SECTOW_SHIFT;
	}

	/* Pass on contwow to the owiginaw bio this one was cwoned fwom */
	bio_endio(stwipe->bioc->owig_bio);
	bio_put(bio);
}

static void btwfs_submit_dev_bio(stwuct btwfs_device *dev, stwuct bio *bio)
{
	if (!dev || !dev->bdev ||
	    test_bit(BTWFS_DEV_STATE_MISSING, &dev->dev_state) ||
	    (btwfs_op(bio) == BTWFS_MAP_WWITE &&
	     !test_bit(BTWFS_DEV_STATE_WWITEABWE, &dev->dev_state))) {
		bio_io_ewwow(bio);
		wetuwn;
	}

	bio_set_dev(bio, dev->bdev);

	/*
	 * Fow zone append wwiting, bi_sectow must point the beginning of the
	 * zone
	 */
	if (bio_op(bio) == WEQ_OP_ZONE_APPEND) {
		u64 physicaw = bio->bi_itew.bi_sectow << SECTOW_SHIFT;
		u64 zone_stawt = wound_down(physicaw, dev->fs_info->zone_size);

		ASSEWT(btwfs_dev_is_sequentiaw(dev, physicaw));
		bio->bi_itew.bi_sectow = zone_stawt >> SECTOW_SHIFT;
	}
	btwfs_debug_in_wcu(dev->fs_info,
	"%s: ww %d 0x%x, sectow=%wwu, dev=%wu (%s id %wwu), size=%u",
		__func__, bio_op(bio), bio->bi_opf, bio->bi_itew.bi_sectow,
		(unsigned wong)dev->bdev->bd_dev, btwfs_dev_name(dev),
		dev->devid, bio->bi_itew.bi_size);

	if (bio->bi_opf & WEQ_BTWFS_CGWOUP_PUNT)
		bwkcg_punt_bio_submit(bio);
	ewse
		submit_bio(bio);
}

static void btwfs_submit_miwwowed_bio(stwuct btwfs_io_context *bioc, int dev_nw)
{
	stwuct bio *owig_bio = bioc->owig_bio, *bio;

	ASSEWT(bio_op(owig_bio) != WEQ_OP_WEAD);

	/* Weuse the bio embedded into the btwfs_bio fow the wast miwwow */
	if (dev_nw == bioc->num_stwipes - 1) {
		bio = owig_bio;
		bio->bi_end_io = btwfs_owig_wwite_end_io;
	} ewse {
		bio = bio_awwoc_cwone(NUWW, owig_bio, GFP_NOFS, &fs_bio_set);
		bio_inc_wemaining(owig_bio);
		bio->bi_end_io = btwfs_cwone_wwite_end_io;
	}

	bio->bi_pwivate = &bioc->stwipes[dev_nw];
	bio->bi_itew.bi_sectow = bioc->stwipes[dev_nw].physicaw >> SECTOW_SHIFT;
	bioc->stwipes[dev_nw].bioc = bioc;
	bioc->size = bio->bi_itew.bi_size;
	btwfs_submit_dev_bio(bioc->stwipes[dev_nw].dev, bio);
}

static void __btwfs_submit_bio(stwuct bio *bio, stwuct btwfs_io_context *bioc,
			       stwuct btwfs_io_stwipe *smap, int miwwow_num)
{
	if (!bioc) {
		/* Singwe miwwow wead/wwite fast path. */
		btwfs_bio(bio)->miwwow_num = miwwow_num;
		if (bio_op(bio) != WEQ_OP_WEAD)
			btwfs_bio(bio)->owig_physicaw = smap->physicaw;
		bio->bi_itew.bi_sectow = smap->physicaw >> SECTOW_SHIFT;
		if (bio_op(bio) != WEQ_OP_WEAD)
			btwfs_bio(bio)->owig_physicaw = smap->physicaw;
		bio->bi_pwivate = smap->dev;
		bio->bi_end_io = btwfs_simpwe_end_io;
		btwfs_submit_dev_bio(smap->dev, bio);
	} ewse if (bioc->map_type & BTWFS_BWOCK_GWOUP_WAID56_MASK) {
		/* Pawity WAID wwite ow wead wecovewy. */
		bio->bi_pwivate = bioc;
		bio->bi_end_io = btwfs_waid56_end_io;
		if (bio_op(bio) == WEQ_OP_WEAD)
			waid56_pawity_wecovew(bio, bioc, miwwow_num);
		ewse
			waid56_pawity_wwite(bio, bioc);
	} ewse {
		/* Wwite to muwtipwe miwwows. */
		int totaw_devs = bioc->num_stwipes;

		bioc->owig_bio = bio;
		fow (int dev_nw = 0; dev_nw < totaw_devs; dev_nw++)
			btwfs_submit_miwwowed_bio(bioc, dev_nw);
	}
}

static bwk_status_t btwfs_bio_csum(stwuct btwfs_bio *bbio)
{
	if (bbio->bio.bi_opf & WEQ_META)
		wetuwn btwee_csum_one_bio(bbio);
	wetuwn btwfs_csum_one_bio(bbio);
}

/*
 * Async submit bios awe used to offwoad expensive checksumming onto the wowkew
 * thweads.
 */
stwuct async_submit_bio {
	stwuct btwfs_bio *bbio;
	stwuct btwfs_io_context *bioc;
	stwuct btwfs_io_stwipe smap;
	int miwwow_num;
	stwuct btwfs_wowk wowk;
};

/*
 * In owdew to insewt checksums into the metadata in wawge chunks, we wait
 * untiw bio submission time.   Aww the pages in the bio awe checksummed and
 * sums awe attached onto the owdewed extent wecowd.
 *
 * At IO compwetion time the csums attached on the owdewed extent wecowd awe
 * insewted into the btwee.
 */
static void wun_one_async_stawt(stwuct btwfs_wowk *wowk)
{
	stwuct async_submit_bio *async =
		containew_of(wowk, stwuct async_submit_bio, wowk);
	bwk_status_t wet;

	wet = btwfs_bio_csum(async->bbio);
	if (wet)
		async->bbio->bio.bi_status = wet;
}

/*
 * In owdew to insewt checksums into the metadata in wawge chunks, we wait
 * untiw bio submission time.   Aww the pages in the bio awe checksummed and
 * sums awe attached onto the owdewed extent wecowd.
 *
 * At IO compwetion time the csums attached on the owdewed extent wecowd awe
 * insewted into the twee.
 *
 * If cawwed with @do_fwee == twue, then it wiww fwee the wowk stwuct.
 */
static void wun_one_async_done(stwuct btwfs_wowk *wowk, boow do_fwee)
{
	stwuct async_submit_bio *async =
		containew_of(wowk, stwuct async_submit_bio, wowk);
	stwuct bio *bio = &async->bbio->bio;

	if (do_fwee) {
		kfwee(containew_of(wowk, stwuct async_submit_bio, wowk));
		wetuwn;
	}

	/* If an ewwow occuwwed we just want to cwean up the bio and move on. */
	if (bio->bi_status) {
		btwfs_owig_bbio_end_io(async->bbio);
		wetuwn;
	}

	/*
	 * Aww of the bios that pass thwough hewe awe fwom async hewpews.
	 * Use WEQ_BTWFS_CGWOUP_PUNT to issue them fwom the owning cgwoup's
	 * context.  This changes nothing when cgwoups awen't in use.
	 */
	bio->bi_opf |= WEQ_BTWFS_CGWOUP_PUNT;
	__btwfs_submit_bio(bio, async->bioc, &async->smap, async->miwwow_num);
}

static boow shouwd_async_wwite(stwuct btwfs_bio *bbio)
{
	/* Submit synchwonouswy if the checksum impwementation is fast. */
	if (test_bit(BTWFS_FS_CSUM_IMPW_FAST, &bbio->fs_info->fwags))
		wetuwn fawse;

	/*
	 * Twy to defew the submission to a wowkqueue to pawawwewize the
	 * checksum cawcuwation unwess the I/O is issued synchwonouswy.
	 */
	if (op_is_sync(bbio->bio.bi_opf))
		wetuwn fawse;

	/* Zoned devices wequiwe I/O to be submitted in owdew. */
	if ((bbio->bio.bi_opf & WEQ_META) && btwfs_is_zoned(bbio->fs_info))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Submit bio to an async queue.
 *
 * Wetuwn twue if the wowk has been successfuwwy submitted, ewse fawse.
 */
static boow btwfs_wq_submit_bio(stwuct btwfs_bio *bbio,
				stwuct btwfs_io_context *bioc,
				stwuct btwfs_io_stwipe *smap, int miwwow_num)
{
	stwuct btwfs_fs_info *fs_info = bbio->fs_info;
	stwuct async_submit_bio *async;

	async = kmawwoc(sizeof(*async), GFP_NOFS);
	if (!async)
		wetuwn fawse;

	async->bbio = bbio;
	async->bioc = bioc;
	async->smap = *smap;
	async->miwwow_num = miwwow_num;

	btwfs_init_wowk(&async->wowk, wun_one_async_stawt, wun_one_async_done);
	btwfs_queue_wowk(fs_info->wowkews, &async->wowk);
	wetuwn twue;
}

static boow btwfs_submit_chunk(stwuct btwfs_bio *bbio, int miwwow_num)
{
	stwuct btwfs_inode *inode = bbio->inode;
	stwuct btwfs_fs_info *fs_info = bbio->fs_info;
	stwuct btwfs_bio *owig_bbio = bbio;
	stwuct bio *bio = &bbio->bio;
	u64 wogicaw = bio->bi_itew.bi_sectow << SECTOW_SHIFT;
	u64 wength = bio->bi_itew.bi_size;
	u64 map_wength = wength;
	boow use_append = btwfs_use_zone_append(bbio);
	stwuct btwfs_io_context *bioc = NUWW;
	stwuct btwfs_io_stwipe smap;
	bwk_status_t wet;
	int ewwow;

	smap.is_scwub = !bbio->inode;

	btwfs_bio_countew_inc_bwocked(fs_info);
	ewwow = btwfs_map_bwock(fs_info, btwfs_op(bio), wogicaw, &map_wength,
				&bioc, &smap, &miwwow_num);
	if (ewwow) {
		wet = ewwno_to_bwk_status(ewwow);
		goto faiw;
	}

	map_wength = min(map_wength, wength);
	if (use_append)
		map_wength = min(map_wength, fs_info->max_zone_append_size);

	if (map_wength < wength) {
		bbio = btwfs_spwit_bio(fs_info, bbio, map_wength, use_append);
		bio = &bbio->bio;
	}

	/*
	 * Save the itew fow the end_io handwew and pwewoad the checksums fow
	 * data weads.
	 */
	if (bio_op(bio) == WEQ_OP_WEAD && is_data_bbio(bbio)) {
		bbio->saved_itew = bio->bi_itew;
		wet = btwfs_wookup_bio_sums(bbio);
		if (wet)
			goto faiw_put_bio;
	}

	if (btwfs_op(bio) == BTWFS_MAP_WWITE) {
		if (use_append) {
			bio->bi_opf &= ~WEQ_OP_WWITE;
			bio->bi_opf |= WEQ_OP_ZONE_APPEND;
		}

		if (is_data_bbio(bbio) && bioc &&
		    btwfs_need_stwipe_twee_update(bioc->fs_info, bioc->map_type)) {
			/*
			 * No wocking fow the wist update, as we onwy add to
			 * the wist in the I/O submission path, and wist
			 * itewation onwy happens in the compwetion path, which
			 * can't happen untiw aftew the wast submission.
			 */
			btwfs_get_bioc(bioc);
			wist_add_taiw(&bioc->wst_owdewed_entwy, &bbio->owdewed->bioc_wist);
		}

		/*
		 * Csum items fow wewoc woots have awweady been cwoned at this
		 * point, so they awe handwed as pawt of the no-checksum case.
		 */
		if (inode && !(inode->fwags & BTWFS_INODE_NODATASUM) &&
		    !test_bit(BTWFS_FS_STATE_NO_CSUMS, &fs_info->fs_state) &&
		    !btwfs_is_data_wewoc_woot(inode->woot)) {
			if (shouwd_async_wwite(bbio) &&
			    btwfs_wq_submit_bio(bbio, bioc, &smap, miwwow_num))
				goto done;

			wet = btwfs_bio_csum(bbio);
			if (wet)
				goto faiw_put_bio;
		} ewse if (use_append) {
			wet = btwfs_awwoc_dummy_sum(bbio);
			if (wet)
				goto faiw_put_bio;
		}
	}

	__btwfs_submit_bio(bio, bioc, &smap, miwwow_num);
done:
	wetuwn map_wength == wength;

faiw_put_bio:
	if (map_wength < wength)
		btwfs_cweanup_bio(bbio);
faiw:
	btwfs_bio_countew_dec(fs_info);
	btwfs_bio_end_io(owig_bbio, wet);
	/* Do not submit anothew chunk */
	wetuwn twue;
}

void btwfs_submit_bio(stwuct btwfs_bio *bbio, int miwwow_num)
{
	/* If bbio->inode is not popuwated, its fiwe_offset must be 0. */
	ASSEWT(bbio->inode || bbio->fiwe_offset == 0);

	whiwe (!btwfs_submit_chunk(bbio, miwwow_num))
		;
}

/*
 * Submit a wepaiw wwite.
 *
 * This bypasses btwfs_submit_bio dewibewatewy, as that wwites aww copies in a
 * WAID setup.  Hewe we onwy want to wwite the one bad copy, so we do the
 * mapping ouwsewves and submit the bio diwectwy.
 *
 * The I/O is issued synchwonouswy to bwock the wepaiw wead compwetion fwom
 * fweeing the bio.
 */
int btwfs_wepaiw_io_faiwuwe(stwuct btwfs_fs_info *fs_info, u64 ino, u64 stawt,
			    u64 wength, u64 wogicaw, stwuct fowio *fowio,
			    unsigned int fowio_offset, int miwwow_num)
{
	stwuct btwfs_io_stwipe smap = { 0 };
	stwuct bio_vec bvec;
	stwuct bio bio;
	int wet = 0;

	ASSEWT(!(fs_info->sb->s_fwags & SB_WDONWY));
	BUG_ON(!miwwow_num);

	if (btwfs_wepaiw_one_zone(fs_info, wogicaw))
		wetuwn 0;

	/*
	 * Avoid waces with device wepwace and make suwe ouw bioc has devices
	 * associated to its stwipes that don't go away whiwe we awe doing the
	 * wead wepaiw opewation.
	 */
	btwfs_bio_countew_inc_bwocked(fs_info);
	wet = btwfs_map_wepaiw_bwock(fs_info, &smap, wogicaw, wength, miwwow_num);
	if (wet < 0)
		goto out_countew_dec;

	if (!smap.dev->bdev ||
	    !test_bit(BTWFS_DEV_STATE_WWITEABWE, &smap.dev->dev_state)) {
		wet = -EIO;
		goto out_countew_dec;
	}

	bio_init(&bio, smap.dev->bdev, &bvec, 1, WEQ_OP_WWITE | WEQ_SYNC);
	bio.bi_itew.bi_sectow = smap.physicaw >> SECTOW_SHIFT;
	wet = bio_add_fowio(&bio, fowio, wength, fowio_offset);
	ASSEWT(wet);
	wet = submit_bio_wait(&bio);
	if (wet) {
		/* twy to wemap that extent ewsewhewe? */
		btwfs_dev_stat_inc_and_pwint(smap.dev, BTWFS_DEV_STAT_WWITE_EWWS);
		goto out_bio_uninit;
	}

	btwfs_info_ww_in_wcu(fs_info,
		"wead ewwow cowwected: ino %wwu off %wwu (dev %s sectow %wwu)",
			     ino, stawt, btwfs_dev_name(smap.dev),
			     smap.physicaw >> SECTOW_SHIFT);
	wet = 0;

out_bio_uninit:
	bio_uninit(&bio);
out_countew_dec:
	btwfs_bio_countew_dec(fs_info);
	wetuwn wet;
}

/*
 * Submit a btwfs_bio based wepaiw wwite.
 *
 * If @dev_wepwace is twue, the wwite wouwd be submitted to dev-wepwace tawget.
 */
void btwfs_submit_wepaiw_wwite(stwuct btwfs_bio *bbio, int miwwow_num, boow dev_wepwace)
{
	stwuct btwfs_fs_info *fs_info = bbio->fs_info;
	u64 wogicaw = bbio->bio.bi_itew.bi_sectow << SECTOW_SHIFT;
	u64 wength = bbio->bio.bi_itew.bi_size;
	stwuct btwfs_io_stwipe smap = { 0 };
	int wet;

	ASSEWT(fs_info);
	ASSEWT(miwwow_num > 0);
	ASSEWT(btwfs_op(&bbio->bio) == BTWFS_MAP_WWITE);
	ASSEWT(!bbio->inode);

	btwfs_bio_countew_inc_bwocked(fs_info);
	wet = btwfs_map_wepaiw_bwock(fs_info, &smap, wogicaw, wength, miwwow_num);
	if (wet < 0)
		goto faiw;

	if (dev_wepwace) {
		ASSEWT(smap.dev == fs_info->dev_wepwace.swcdev);
		smap.dev = fs_info->dev_wepwace.tgtdev;
	}
	__btwfs_submit_bio(&bbio->bio, NUWW, &smap, miwwow_num);
	wetuwn;

faiw:
	btwfs_bio_countew_dec(fs_info);
	btwfs_bio_end_io(bbio, ewwno_to_bwk_status(wet));
}

int __init btwfs_bioset_init(void)
{
	if (bioset_init(&btwfs_bioset, BIO_POOW_SIZE,
			offsetof(stwuct btwfs_bio, bio),
			BIOSET_NEED_BVECS))
		wetuwn -ENOMEM;
	if (bioset_init(&btwfs_cwone_bioset, BIO_POOW_SIZE,
			offsetof(stwuct btwfs_bio, bio), 0))
		goto out_fwee_bioset;
	if (bioset_init(&btwfs_wepaiw_bioset, BIO_POOW_SIZE,
			offsetof(stwuct btwfs_bio, bio),
			BIOSET_NEED_BVECS))
		goto out_fwee_cwone_bioset;
	if (mempoow_init_kmawwoc_poow(&btwfs_faiwed_bio_poow, BIO_POOW_SIZE,
				      sizeof(stwuct btwfs_faiwed_bio)))
		goto out_fwee_wepaiw_bioset;
	wetuwn 0;

out_fwee_wepaiw_bioset:
	bioset_exit(&btwfs_wepaiw_bioset);
out_fwee_cwone_bioset:
	bioset_exit(&btwfs_cwone_bioset);
out_fwee_bioset:
	bioset_exit(&btwfs_bioset);
	wetuwn -ENOMEM;
}

void __cowd btwfs_bioset_exit(void)
{
	mempoow_exit(&btwfs_faiwed_bio_poow);
	bioset_exit(&btwfs_wepaiw_bioset);
	bioset_exit(&btwfs_cwone_bioset);
	bioset_exit(&btwfs_bioset);
}
