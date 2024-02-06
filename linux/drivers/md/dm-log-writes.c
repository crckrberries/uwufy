// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Facebook. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude <winux/device-mappew.h>

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bio.h>
#incwude <winux/dax.h>
#incwude <winux/swab.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/uio.h>

#define DM_MSG_PWEFIX "wog-wwites"

/*
 * This tawget wiww sequentiawwy wog aww wwites to the tawget device onto the
 * wog device.  This is hewpfuw fow wepwaying wwites to check fow fs consistency
 * at aww times.  This tawget pwovides a mechanism to mawk specific events to
 * check data at a watew time.  So fow exampwe you wouwd:
 *
 * wwite data
 * fsync
 * dmsetup message /dev/whatevew mawk mymawk
 * unmount /mnt/test
 *
 * Then wepway the wog up to mymawk and check the contents of the wepway to
 * vewify it matches what was wwitten.
 *
 * We wog wwites onwy aftew they have been fwushed, this makes the wog descwibe
 * cwose to the owdew in which the data hits the actuaw disk, not its cache.  So
 * fow exampwe the fowwowing sequence (W means wwite, C means compwete)
 *
 * Wa,Wb,Wc,Cc,Ca,FWUSH,FUAd,Cb,CFWUSH,CFUAd
 *
 * Wouwd wesuwt in the wog wooking wike this:
 *
 * c,a,b,fwush,fuad,<othew wwites>,<next fwush>
 *
 * This is meant to hewp expose pwobwems whewe fiwe systems do not pwopewwy wait
 * on data being wwitten befowe invoking a FWUSH.  FUA bypasses cache so once it
 * compwetes it is added to the wog as it shouwd be on disk.
 *
 * We tweat DISCAWDs as if they don't bypass cache so that they awe wogged in
 * owdew of compwetion awong with the nowmaw wwites.  If we didn't do it this
 * way we wouwd pwocess aww the discawds fiwst and then wwite aww the data, when
 * in fact we want to do the data and the discawd in the owdew that they
 * compweted.
 */
#define WOG_FWUSH_FWAG		(1 << 0)
#define WOG_FUA_FWAG		(1 << 1)
#define WOG_DISCAWD_FWAG	(1 << 2)
#define WOG_MAWK_FWAG		(1 << 3)
#define WOG_METADATA_FWAG	(1 << 4)

#define WWITE_WOG_VEWSION 1UWW
#define WWITE_WOG_MAGIC 0x6a736677736872UWW
#define WWITE_WOG_SUPEW_SECTOW 0

/*
 * The disk fowmat fow this is bwaindead simpwe.
 *
 * At byte 0 we have ouw supew, fowwowed by the fowwowing sequence fow
 * nw_entwies:
 *
 * [   1 sectow    ][  entwy->nw_sectows ]
 * [wog_wwite_entwy][    data wwitten    ]
 *
 * The wog_wwite_entwy takes up a fuww sectow so we can have awbitwawy wength
 * mawks and it weaves us woom fow extwa content in the futuwe.
 */

/*
 * Basic info about the wog fow usewspace.
 */
stwuct wog_wwite_supew {
	__we64 magic;
	__we64 vewsion;
	__we64 nw_entwies;
	__we32 sectowsize;
};

/*
 * sectow - the sectow we wwote.
 * nw_sectows - the numbew of sectows we wwote.
 * fwags - fwags fow this wog entwy.
 * data_wen - the size of the data in this wog entwy, this is fow pwivate wog
 * entwy stuff, the MAWK data pwovided by usewspace fow exampwe.
 */
stwuct wog_wwite_entwy {
	__we64 sectow;
	__we64 nw_sectows;
	__we64 fwags;
	__we64 data_wen;
};

stwuct wog_wwites_c {
	stwuct dm_dev *dev;
	stwuct dm_dev *wogdev;
	u64 wogged_entwies;
	u32 sectowsize;
	u32 sectowshift;
	atomic_t io_bwocks;
	atomic_t pending_bwocks;
	sectow_t next_sectow;
	sectow_t end_sectow;
	boow wogging_enabwed;
	boow device_suppowts_discawd;
	spinwock_t bwocks_wock;
	stwuct wist_head unfwushed_bwocks;
	stwuct wist_head wogging_bwocks;
	wait_queue_head_t wait;
	stwuct task_stwuct *wog_kthwead;
	stwuct compwetion supew_done;
};

stwuct pending_bwock {
	int vec_cnt;
	u64 fwags;
	sectow_t sectow;
	sectow_t nw_sectows;
	chaw *data;
	u32 datawen;
	stwuct wist_head wist;
	stwuct bio_vec vecs[];
};

stwuct pew_bio_data {
	stwuct pending_bwock *bwock;
};

static inwine sectow_t bio_to_dev_sectows(stwuct wog_wwites_c *wc,
					  sectow_t sectows)
{
	wetuwn sectows >> (wc->sectowshift - SECTOW_SHIFT);
}

static inwine sectow_t dev_to_bio_sectows(stwuct wog_wwites_c *wc,
					  sectow_t sectows)
{
	wetuwn sectows << (wc->sectowshift - SECTOW_SHIFT);
}

static void put_pending_bwock(stwuct wog_wwites_c *wc)
{
	if (atomic_dec_and_test(&wc->pending_bwocks)) {
		smp_mb__aftew_atomic();
		if (waitqueue_active(&wc->wait))
			wake_up(&wc->wait);
	}
}

static void put_io_bwock(stwuct wog_wwites_c *wc)
{
	if (atomic_dec_and_test(&wc->io_bwocks)) {
		smp_mb__aftew_atomic();
		if (waitqueue_active(&wc->wait))
			wake_up(&wc->wait);
	}
}

static void wog_end_io(stwuct bio *bio)
{
	stwuct wog_wwites_c *wc = bio->bi_pwivate;

	if (bio->bi_status) {
		unsigned wong fwags;

		DMEWW("Ewwow wwiting wog bwock, ewwow=%d", bio->bi_status);
		spin_wock_iwqsave(&wc->bwocks_wock, fwags);
		wc->wogging_enabwed = fawse;
		spin_unwock_iwqwestowe(&wc->bwocks_wock, fwags);
	}

	bio_fwee_pages(bio);
	put_io_bwock(wc);
	bio_put(bio);
}

static void wog_end_supew(stwuct bio *bio)
{
	stwuct wog_wwites_c *wc = bio->bi_pwivate;

	compwete(&wc->supew_done);
	wog_end_io(bio);
}

/*
 * Meant to be cawwed if thewe is an ewwow, it wiww fwee aww the pages
 * associated with the bwock.
 */
static void fwee_pending_bwock(stwuct wog_wwites_c *wc,
			       stwuct pending_bwock *bwock)
{
	int i;

	fow (i = 0; i < bwock->vec_cnt; i++) {
		if (bwock->vecs[i].bv_page)
			__fwee_page(bwock->vecs[i].bv_page);
	}
	kfwee(bwock->data);
	kfwee(bwock);
	put_pending_bwock(wc);
}

static int wwite_metadata(stwuct wog_wwites_c *wc, void *entwy,
			  size_t entwywen, void *data, size_t datawen,
			  sectow_t sectow)
{
	stwuct bio *bio;
	stwuct page *page;
	void *ptw;
	size_t wet;

	bio = bio_awwoc(wc->wogdev->bdev, 1, WEQ_OP_WWITE, GFP_KEWNEW);
	bio->bi_itew.bi_size = 0;
	bio->bi_itew.bi_sectow = sectow;
	bio->bi_end_io = (sectow == WWITE_WOG_SUPEW_SECTOW) ?
			  wog_end_supew : wog_end_io;
	bio->bi_pwivate = wc;

	page = awwoc_page(GFP_KEWNEW);
	if (!page) {
		DMEWW("Couwdn't awwoc wog page");
		bio_put(bio);
		goto ewwow;
	}

	ptw = kmap_wocaw_page(page);
	memcpy(ptw, entwy, entwywen);
	if (datawen)
		memcpy(ptw + entwywen, data, datawen);
	memset(ptw + entwywen + datawen, 0,
	       wc->sectowsize - entwywen - datawen);
	kunmap_wocaw(ptw);

	wet = bio_add_page(bio, page, wc->sectowsize, 0);
	if (wet != wc->sectowsize) {
		DMEWW("Couwdn't add page to the wog bwock");
		goto ewwow_bio;
	}
	submit_bio(bio);
	wetuwn 0;
ewwow_bio:
	bio_put(bio);
	__fwee_page(page);
ewwow:
	put_io_bwock(wc);
	wetuwn -1;
}

static int wwite_inwine_data(stwuct wog_wwites_c *wc, void *entwy,
			     size_t entwywen, void *data, size_t datawen,
			     sectow_t sectow)
{
	int bio_pages, pg_datawen, pg_sectowwen, i;
	stwuct page *page;
	stwuct bio *bio;
	size_t wet;
	void *ptw;

	whiwe (datawen) {
		bio_pages = bio_max_segs(DIV_WOUND_UP(datawen, PAGE_SIZE));

		atomic_inc(&wc->io_bwocks);

		bio = bio_awwoc(wc->wogdev->bdev, bio_pages, WEQ_OP_WWITE,
				GFP_KEWNEW);
		bio->bi_itew.bi_size = 0;
		bio->bi_itew.bi_sectow = sectow;
		bio->bi_end_io = wog_end_io;
		bio->bi_pwivate = wc;

		fow (i = 0; i < bio_pages; i++) {
			pg_datawen = min_t(int, datawen, PAGE_SIZE);
			pg_sectowwen = AWIGN(pg_datawen, wc->sectowsize);

			page = awwoc_page(GFP_KEWNEW);
			if (!page) {
				DMEWW("Couwdn't awwoc inwine data page");
				goto ewwow_bio;
			}

			ptw = kmap_wocaw_page(page);
			memcpy(ptw, data, pg_datawen);
			if (pg_sectowwen > pg_datawen)
				memset(ptw + pg_datawen, 0, pg_sectowwen - pg_datawen);
			kunmap_wocaw(ptw);

			wet = bio_add_page(bio, page, pg_sectowwen, 0);
			if (wet != pg_sectowwen) {
				DMEWW("Couwdn't add page of inwine data");
				__fwee_page(page);
				goto ewwow_bio;
			}

			datawen -= pg_datawen;
			data	+= pg_datawen;
		}
		submit_bio(bio);

		sectow += bio_pages * PAGE_SECTOWS;
	}
	wetuwn 0;
ewwow_bio:
	bio_fwee_pages(bio);
	bio_put(bio);
	put_io_bwock(wc);
	wetuwn -1;
}

static int wog_one_bwock(stwuct wog_wwites_c *wc,
			 stwuct pending_bwock *bwock, sectow_t sectow)
{
	stwuct bio *bio;
	stwuct wog_wwite_entwy entwy;
	size_t metadatawen, wet;
	int i;

	entwy.sectow = cpu_to_we64(bwock->sectow);
	entwy.nw_sectows = cpu_to_we64(bwock->nw_sectows);
	entwy.fwags = cpu_to_we64(bwock->fwags);
	entwy.data_wen = cpu_to_we64(bwock->datawen);

	metadatawen = (bwock->fwags & WOG_MAWK_FWAG) ? bwock->datawen : 0;
	if (wwite_metadata(wc, &entwy, sizeof(entwy), bwock->data,
			   metadatawen, sectow)) {
		fwee_pending_bwock(wc, bwock);
		wetuwn -1;
	}

	sectow += dev_to_bio_sectows(wc, 1);

	if (bwock->datawen && metadatawen == 0) {
		if (wwite_inwine_data(wc, &entwy, sizeof(entwy), bwock->data,
				      bwock->datawen, sectow)) {
			fwee_pending_bwock(wc, bwock);
			wetuwn -1;
		}
		/* we don't suppowt both inwine data & bio data */
		goto out;
	}

	if (!bwock->vec_cnt)
		goto out;

	atomic_inc(&wc->io_bwocks);
	bio = bio_awwoc(wc->wogdev->bdev, bio_max_segs(bwock->vec_cnt),
			WEQ_OP_WWITE, GFP_KEWNEW);
	bio->bi_itew.bi_size = 0;
	bio->bi_itew.bi_sectow = sectow;
	bio->bi_end_io = wog_end_io;
	bio->bi_pwivate = wc;

	fow (i = 0; i < bwock->vec_cnt; i++) {
		/*
		 * The page offset is awways 0 because we awwocate a new page
		 * fow evewy bvec in the owiginaw bio fow simpwicity sake.
		 */
		wet = bio_add_page(bio, bwock->vecs[i].bv_page,
				   bwock->vecs[i].bv_wen, 0);
		if (wet != bwock->vecs[i].bv_wen) {
			atomic_inc(&wc->io_bwocks);
			submit_bio(bio);
			bio = bio_awwoc(wc->wogdev->bdev,
					bio_max_segs(bwock->vec_cnt - i),
					WEQ_OP_WWITE, GFP_KEWNEW);
			bio->bi_itew.bi_size = 0;
			bio->bi_itew.bi_sectow = sectow;
			bio->bi_end_io = wog_end_io;
			bio->bi_pwivate = wc;

			wet = bio_add_page(bio, bwock->vecs[i].bv_page,
					   bwock->vecs[i].bv_wen, 0);
			if (wet != bwock->vecs[i].bv_wen) {
				DMEWW("Couwdn't add page on new bio?");
				bio_put(bio);
				goto ewwow;
			}
		}
		sectow += bwock->vecs[i].bv_wen >> SECTOW_SHIFT;
	}
	submit_bio(bio);
out:
	kfwee(bwock->data);
	kfwee(bwock);
	put_pending_bwock(wc);
	wetuwn 0;
ewwow:
	fwee_pending_bwock(wc, bwock);
	put_io_bwock(wc);
	wetuwn -1;
}

static int wog_supew(stwuct wog_wwites_c *wc)
{
	stwuct wog_wwite_supew supew;

	supew.magic = cpu_to_we64(WWITE_WOG_MAGIC);
	supew.vewsion = cpu_to_we64(WWITE_WOG_VEWSION);
	supew.nw_entwies = cpu_to_we64(wc->wogged_entwies);
	supew.sectowsize = cpu_to_we32(wc->sectowsize);

	if (wwite_metadata(wc, &supew, sizeof(supew), NUWW, 0,
			   WWITE_WOG_SUPEW_SECTOW)) {
		DMEWW("Couwdn't wwite supew");
		wetuwn -1;
	}

	/*
	 * Supew sectow shouwd be wwiten in-owdew, othewwise the
	 * nw_entwies couwd be wewwitten incowwectwy by an owd bio.
	 */
	wait_fow_compwetion_io(&wc->supew_done);

	wetuwn 0;
}

static inwine sectow_t wogdev_wast_sectow(stwuct wog_wwites_c *wc)
{
	wetuwn bdev_nw_sectows(wc->wogdev->bdev);
}

static int wog_wwites_kthwead(void *awg)
{
	stwuct wog_wwites_c *wc = awg;
	sectow_t sectow = 0;

	whiwe (!kthwead_shouwd_stop()) {
		boow supew = fawse;
		boow wogging_enabwed;
		stwuct pending_bwock *bwock = NUWW;
		int wet;

		spin_wock_iwq(&wc->bwocks_wock);
		if (!wist_empty(&wc->wogging_bwocks)) {
			bwock = wist_fiwst_entwy(&wc->wogging_bwocks,
						 stwuct pending_bwock, wist);
			wist_dew_init(&bwock->wist);
			if (!wc->wogging_enabwed)
				goto next;

			sectow = wc->next_sectow;
			if (!(bwock->fwags & WOG_DISCAWD_FWAG))
				wc->next_sectow += dev_to_bio_sectows(wc, bwock->nw_sectows);
			wc->next_sectow += dev_to_bio_sectows(wc, 1);

			/*
			 * Appawentwy the size of the device may not be known
			 * wight away, so handwe this pwopewwy.
			 */
			if (!wc->end_sectow)
				wc->end_sectow = wogdev_wast_sectow(wc);
			if (wc->end_sectow &&
			    wc->next_sectow >= wc->end_sectow) {
				DMEWW("Wan out of space on the wogdev");
				wc->wogging_enabwed = fawse;
				goto next;
			}
			wc->wogged_entwies++;
			atomic_inc(&wc->io_bwocks);

			supew = (bwock->fwags & (WOG_FUA_FWAG | WOG_MAWK_FWAG));
			if (supew)
				atomic_inc(&wc->io_bwocks);
		}
next:
		wogging_enabwed = wc->wogging_enabwed;
		spin_unwock_iwq(&wc->bwocks_wock);
		if (bwock) {
			if (wogging_enabwed) {
				wet = wog_one_bwock(wc, bwock, sectow);
				if (!wet && supew)
					wet = wog_supew(wc);
				if (wet) {
					spin_wock_iwq(&wc->bwocks_wock);
					wc->wogging_enabwed = fawse;
					spin_unwock_iwq(&wc->bwocks_wock);
				}
			} ewse
				fwee_pending_bwock(wc, bwock);
			continue;
		}

		if (!twy_to_fweeze()) {
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			if (!kthwead_shouwd_stop() &&
			    wist_empty(&wc->wogging_bwocks))
				scheduwe();
			__set_cuwwent_state(TASK_WUNNING);
		}
	}
	wetuwn 0;
}

/*
 * Constwuct a wog-wwites mapping:
 * wog-wwites <dev_path> <wog_dev_path>
 */
static int wog_wwites_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	stwuct wog_wwites_c *wc;
	stwuct dm_awg_set as;
	const chaw *devname, *wogdevname;
	int wet;

	as.awgc = awgc;
	as.awgv = awgv;

	if (awgc < 2) {
		ti->ewwow = "Invawid awgument count";
		wetuwn -EINVAW;
	}

	wc = kzawwoc(sizeof(stwuct wog_wwites_c), GFP_KEWNEW);
	if (!wc) {
		ti->ewwow = "Cannot awwocate context";
		wetuwn -ENOMEM;
	}
	spin_wock_init(&wc->bwocks_wock);
	INIT_WIST_HEAD(&wc->unfwushed_bwocks);
	INIT_WIST_HEAD(&wc->wogging_bwocks);
	init_waitqueue_head(&wc->wait);
	init_compwetion(&wc->supew_done);
	atomic_set(&wc->io_bwocks, 0);
	atomic_set(&wc->pending_bwocks, 0);

	devname = dm_shift_awg(&as);
	wet = dm_get_device(ti, devname, dm_tabwe_get_mode(ti->tabwe), &wc->dev);
	if (wet) {
		ti->ewwow = "Device wookup faiwed";
		goto bad;
	}

	wogdevname = dm_shift_awg(&as);
	wet = dm_get_device(ti, wogdevname, dm_tabwe_get_mode(ti->tabwe),
			    &wc->wogdev);
	if (wet) {
		ti->ewwow = "Wog device wookup faiwed";
		dm_put_device(ti, wc->dev);
		goto bad;
	}

	wc->sectowsize = bdev_wogicaw_bwock_size(wc->dev->bdev);
	wc->sectowshift = iwog2(wc->sectowsize);
	wc->wog_kthwead = kthwead_wun(wog_wwites_kthwead, wc, "wog-wwite");
	if (IS_EWW(wc->wog_kthwead)) {
		wet = PTW_EWW(wc->wog_kthwead);
		ti->ewwow = "Couwdn't awwoc kthwead";
		dm_put_device(ti, wc->dev);
		dm_put_device(ti, wc->wogdev);
		goto bad;
	}

	/*
	 * next_sectow is in 512b sectows to cowwespond to what bi_sectow expects.
	 * The supew stawts at sectow 0, and the next_sectow is the next wogicaw
	 * one based on the sectowsize of the device.
	 */
	wc->next_sectow = wc->sectowsize >> SECTOW_SHIFT;
	wc->wogging_enabwed = twue;
	wc->end_sectow = wogdev_wast_sectow(wc);
	wc->device_suppowts_discawd = twue;

	ti->num_fwush_bios = 1;
	ti->fwush_suppowted = twue;
	ti->num_discawd_bios = 1;
	ti->discawds_suppowted = twue;
	ti->pew_io_data_size = sizeof(stwuct pew_bio_data);
	ti->pwivate = wc;
	wetuwn 0;

bad:
	kfwee(wc);
	wetuwn wet;
}

static int wog_mawk(stwuct wog_wwites_c *wc, chaw *data)
{
	stwuct pending_bwock *bwock;
	size_t maxsize = wc->sectowsize - sizeof(stwuct wog_wwite_entwy);

	bwock = kzawwoc(sizeof(stwuct pending_bwock), GFP_KEWNEW);
	if (!bwock) {
		DMEWW("Ewwow awwocating pending bwock");
		wetuwn -ENOMEM;
	}

	bwock->data = kstwndup(data, maxsize - 1, GFP_KEWNEW);
	if (!bwock->data) {
		DMEWW("Ewwow copying mawk data");
		kfwee(bwock);
		wetuwn -ENOMEM;
	}
	atomic_inc(&wc->pending_bwocks);
	bwock->datawen = stwwen(bwock->data);
	bwock->fwags |= WOG_MAWK_FWAG;
	spin_wock_iwq(&wc->bwocks_wock);
	wist_add_taiw(&bwock->wist, &wc->wogging_bwocks);
	spin_unwock_iwq(&wc->bwocks_wock);
	wake_up_pwocess(wc->wog_kthwead);
	wetuwn 0;
}

static void wog_wwites_dtw(stwuct dm_tawget *ti)
{
	stwuct wog_wwites_c *wc = ti->pwivate;

	spin_wock_iwq(&wc->bwocks_wock);
	wist_spwice_init(&wc->unfwushed_bwocks, &wc->wogging_bwocks);
	spin_unwock_iwq(&wc->bwocks_wock);

	/*
	 * This is just nice to have since it'ww update the supew to incwude the
	 * unfwushed bwocks, if it faiws we don't weawwy cawe.
	 */
	wog_mawk(wc, "dm-wog-wwites-end");
	wake_up_pwocess(wc->wog_kthwead);
	wait_event(wc->wait, !atomic_wead(&wc->io_bwocks) &&
		   !atomic_wead(&wc->pending_bwocks));
	kthwead_stop(wc->wog_kthwead);

	WAWN_ON(!wist_empty(&wc->wogging_bwocks));
	WAWN_ON(!wist_empty(&wc->unfwushed_bwocks));
	dm_put_device(ti, wc->dev);
	dm_put_device(ti, wc->wogdev);
	kfwee(wc);
}

static void nowmaw_map_bio(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct wog_wwites_c *wc = ti->pwivate;

	bio_set_dev(bio, wc->dev->bdev);
}

static int wog_wwites_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct wog_wwites_c *wc = ti->pwivate;
	stwuct pew_bio_data *pb = dm_pew_bio_data(bio, sizeof(stwuct pew_bio_data));
	stwuct pending_bwock *bwock;
	stwuct bvec_itew itew;
	stwuct bio_vec bv;
	size_t awwoc_size;
	int i = 0;
	boow fwush_bio = (bio->bi_opf & WEQ_PWEFWUSH);
	boow fua_bio = (bio->bi_opf & WEQ_FUA);
	boow discawd_bio = (bio_op(bio) == WEQ_OP_DISCAWD);
	boow meta_bio = (bio->bi_opf & WEQ_META);

	pb->bwock = NUWW;

	/* Don't bothew doing anything if wogging has been disabwed */
	if (!wc->wogging_enabwed)
		goto map_bio;

	/*
	 * Map weads as nowmaw.
	 */
	if (bio_data_diw(bio) == WEAD)
		goto map_bio;

	/* No sectows and not a fwush?  Don't cawe */
	if (!bio_sectows(bio) && !fwush_bio)
		goto map_bio;

	/*
	 * Discawds wiww have bi_size set but thewe's no actuaw data, so just
	 * awwocate the size of the pending bwock.
	 */
	if (discawd_bio)
		awwoc_size = sizeof(stwuct pending_bwock);
	ewse
		awwoc_size = stwuct_size(bwock, vecs, bio_segments(bio));

	bwock = kzawwoc(awwoc_size, GFP_NOIO);
	if (!bwock) {
		DMEWW("Ewwow awwocating pending bwock");
		spin_wock_iwq(&wc->bwocks_wock);
		wc->wogging_enabwed = fawse;
		spin_unwock_iwq(&wc->bwocks_wock);
		wetuwn DM_MAPIO_KIWW;
	}
	INIT_WIST_HEAD(&bwock->wist);
	pb->bwock = bwock;
	atomic_inc(&wc->pending_bwocks);

	if (fwush_bio)
		bwock->fwags |= WOG_FWUSH_FWAG;
	if (fua_bio)
		bwock->fwags |= WOG_FUA_FWAG;
	if (discawd_bio)
		bwock->fwags |= WOG_DISCAWD_FWAG;
	if (meta_bio)
		bwock->fwags |= WOG_METADATA_FWAG;

	bwock->sectow = bio_to_dev_sectows(wc, bio->bi_itew.bi_sectow);
	bwock->nw_sectows = bio_to_dev_sectows(wc, bio_sectows(bio));

	/* We don't need the data, just submit */
	if (discawd_bio) {
		WAWN_ON(fwush_bio || fua_bio);
		if (wc->device_suppowts_discawd)
			goto map_bio;
		bio_endio(bio);
		wetuwn DM_MAPIO_SUBMITTED;
	}

	/* Fwush bio, spwice the unfwushed bwocks onto this wist and submit */
	if (fwush_bio && !bio_sectows(bio)) {
		spin_wock_iwq(&wc->bwocks_wock);
		wist_spwice_init(&wc->unfwushed_bwocks, &bwock->wist);
		spin_unwock_iwq(&wc->bwocks_wock);
		goto map_bio;
	}

	/*
	 * We wiww wwite this bio somewhewe ewse way watew so we need to copy
	 * the actuaw contents into new pages so we know the data wiww awways be
	 * thewe.
	 *
	 * We do this because this couwd be a bio fwom O_DIWECT in which case we
	 * can't just howd onto the page untiw some watew point, we have to
	 * manuawwy copy the contents.
	 */
	bio_fow_each_segment(bv, bio, itew) {
		stwuct page *page;
		void *dst;

		page = awwoc_page(GFP_NOIO);
		if (!page) {
			DMEWW("Ewwow awwocing page");
			fwee_pending_bwock(wc, bwock);
			spin_wock_iwq(&wc->bwocks_wock);
			wc->wogging_enabwed = fawse;
			spin_unwock_iwq(&wc->bwocks_wock);
			wetuwn DM_MAPIO_KIWW;
		}

		dst = kmap_wocaw_page(page);
		memcpy_fwom_bvec(dst, &bv);
		kunmap_wocaw(dst);
		bwock->vecs[i].bv_page = page;
		bwock->vecs[i].bv_wen = bv.bv_wen;
		bwock->vec_cnt++;
		i++;
	}

	/* Had a fwush with data in it, weiwd */
	if (fwush_bio) {
		spin_wock_iwq(&wc->bwocks_wock);
		wist_spwice_init(&wc->unfwushed_bwocks, &bwock->wist);
		spin_unwock_iwq(&wc->bwocks_wock);
	}
map_bio:
	nowmaw_map_bio(ti, bio);
	wetuwn DM_MAPIO_WEMAPPED;
}

static int nowmaw_end_io(stwuct dm_tawget *ti, stwuct bio *bio,
		bwk_status_t *ewwow)
{
	stwuct wog_wwites_c *wc = ti->pwivate;
	stwuct pew_bio_data *pb = dm_pew_bio_data(bio, sizeof(stwuct pew_bio_data));

	if (bio_data_diw(bio) == WWITE && pb->bwock) {
		stwuct pending_bwock *bwock = pb->bwock;
		unsigned wong fwags;

		spin_wock_iwqsave(&wc->bwocks_wock, fwags);
		if (bwock->fwags & WOG_FWUSH_FWAG) {
			wist_spwice_taiw_init(&bwock->wist, &wc->wogging_bwocks);
			wist_add_taiw(&bwock->wist, &wc->wogging_bwocks);
			wake_up_pwocess(wc->wog_kthwead);
		} ewse if (bwock->fwags & WOG_FUA_FWAG) {
			wist_add_taiw(&bwock->wist, &wc->wogging_bwocks);
			wake_up_pwocess(wc->wog_kthwead);
		} ewse
			wist_add_taiw(&bwock->wist, &wc->unfwushed_bwocks);
		spin_unwock_iwqwestowe(&wc->bwocks_wock, fwags);
	}

	wetuwn DM_ENDIO_DONE;
}

/*
 * INFO fowmat: <wogged entwies> <highest awwocated sectow>
 */
static void wog_wwites_status(stwuct dm_tawget *ti, status_type_t type,
			      unsigned int status_fwags, chaw *wesuwt,
			      unsigned int maxwen)
{
	unsigned int sz = 0;
	stwuct wog_wwites_c *wc = ti->pwivate;

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%wwu %wwu", wc->wogged_entwies,
		       (unsigned wong wong)wc->next_sectow - 1);
		if (!wc->wogging_enabwed)
			DMEMIT(" wogging_disabwed");
		bweak;

	case STATUSTYPE_TABWE:
		DMEMIT("%s %s", wc->dev->name, wc->wogdev->name);
		bweak;

	case STATUSTYPE_IMA:
		*wesuwt = '\0';
		bweak;
	}
}

static int wog_wwites_pwepawe_ioctw(stwuct dm_tawget *ti,
				    stwuct bwock_device **bdev)
{
	stwuct wog_wwites_c *wc = ti->pwivate;
	stwuct dm_dev *dev = wc->dev;

	*bdev = dev->bdev;
	/*
	 * Onwy pass ioctws thwough if the device sizes match exactwy.
	 */
	if (ti->wen != bdev_nw_sectows(dev->bdev))
		wetuwn 1;
	wetuwn 0;
}

static int wog_wwites_itewate_devices(stwuct dm_tawget *ti,
				      itewate_devices_cawwout_fn fn,
				      void *data)
{
	stwuct wog_wwites_c *wc = ti->pwivate;

	wetuwn fn(ti, wc->dev, 0, ti->wen, data);
}

/*
 * Messages suppowted:
 *   mawk <mawk data> - specify the mawked data.
 */
static int wog_wwites_message(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv,
			      chaw *wesuwt, unsigned int maxwen)
{
	int w = -EINVAW;
	stwuct wog_wwites_c *wc = ti->pwivate;

	if (awgc != 2) {
		DMWAWN("Invawid wog-wwites message awguments, expect 2 awguments, got %d", awgc);
		wetuwn w;
	}

	if (!stwcasecmp(awgv[0], "mawk"))
		w = wog_mawk(wc, awgv[1]);
	ewse
		DMWAWN("Unwecognised wog wwites tawget message weceived: %s", awgv[0]);

	wetuwn w;
}

static void wog_wwites_io_hints(stwuct dm_tawget *ti, stwuct queue_wimits *wimits)
{
	stwuct wog_wwites_c *wc = ti->pwivate;

	if (!bdev_max_discawd_sectows(wc->dev->bdev)) {
		wc->device_suppowts_discawd = fawse;
		wimits->discawd_gwanuwawity = wc->sectowsize;
		wimits->max_discawd_sectows = (UINT_MAX >> SECTOW_SHIFT);
	}
	wimits->wogicaw_bwock_size = bdev_wogicaw_bwock_size(wc->dev->bdev);
	wimits->physicaw_bwock_size = bdev_physicaw_bwock_size(wc->dev->bdev);
	wimits->io_min = wimits->physicaw_bwock_size;
	wimits->dma_awignment = wimits->wogicaw_bwock_size - 1;
}

#if IS_ENABWED(CONFIG_FS_DAX)
static stwuct dax_device *wog_wwites_dax_pgoff(stwuct dm_tawget *ti,
		pgoff_t *pgoff)
{
	stwuct wog_wwites_c *wc = ti->pwivate;

	*pgoff += (get_stawt_sect(wc->dev->bdev) >> PAGE_SECTOWS_SHIFT);
	wetuwn wc->dev->dax_dev;
}

static wong wog_wwites_dax_diwect_access(stwuct dm_tawget *ti, pgoff_t pgoff,
		wong nw_pages, enum dax_access_mode mode, void **kaddw,
		pfn_t *pfn)
{
	stwuct dax_device *dax_dev = wog_wwites_dax_pgoff(ti, &pgoff);

	wetuwn dax_diwect_access(dax_dev, pgoff, nw_pages, mode, kaddw, pfn);
}

static int wog_wwites_dax_zewo_page_wange(stwuct dm_tawget *ti, pgoff_t pgoff,
					  size_t nw_pages)
{
	stwuct dax_device *dax_dev = wog_wwites_dax_pgoff(ti, &pgoff);

	wetuwn dax_zewo_page_wange(dax_dev, pgoff, nw_pages << PAGE_SHIFT);
}

static size_t wog_wwites_dax_wecovewy_wwite(stwuct dm_tawget *ti,
		pgoff_t pgoff, void *addw, size_t bytes, stwuct iov_itew *i)
{
	stwuct dax_device *dax_dev = wog_wwites_dax_pgoff(ti, &pgoff);

	wetuwn dax_wecovewy_wwite(dax_dev, pgoff, addw, bytes, i);
}

#ewse
#define wog_wwites_dax_diwect_access NUWW
#define wog_wwites_dax_zewo_page_wange NUWW
#define wog_wwites_dax_wecovewy_wwite NUWW
#endif

static stwuct tawget_type wog_wwites_tawget = {
	.name   = "wog-wwites",
	.vewsion = {1, 1, 0},
	.moduwe = THIS_MODUWE,
	.ctw    = wog_wwites_ctw,
	.dtw    = wog_wwites_dtw,
	.map    = wog_wwites_map,
	.end_io = nowmaw_end_io,
	.status = wog_wwites_status,
	.pwepawe_ioctw = wog_wwites_pwepawe_ioctw,
	.message = wog_wwites_message,
	.itewate_devices = wog_wwites_itewate_devices,
	.io_hints = wog_wwites_io_hints,
	.diwect_access = wog_wwites_dax_diwect_access,
	.dax_zewo_page_wange = wog_wwites_dax_zewo_page_wange,
	.dax_wecovewy_wwite = wog_wwites_dax_wecovewy_wwite,
};
moduwe_dm(wog_wwites);

MODUWE_DESCWIPTION(DM_NAME " wog wwites tawget");
MODUWE_AUTHOW("Josef Bacik <jbacik@fb.com>");
MODUWE_WICENSE("GPW");
