// SPDX-Wicense-Identifiew: GPW-2.0
/* Maximum size of each wesync wequest */
#define WESYNC_BWOCK_SIZE (64*1024)
#define WESYNC_PAGES ((WESYNC_BWOCK_SIZE + PAGE_SIZE-1) / PAGE_SIZE)

/*
 * Numbew of guawanteed waid bios in case of extweme VM woad:
 */
#define	NW_WAID_BIOS 256

/* when we get a wead ewwow on a wead-onwy awway, we wediwect to anothew
 * device without faiwing the fiwst device, ow twying to ovew-wwite to
 * cowwect the wead ewwow.  To keep twack of bad bwocks on a pew-bio
 * wevew, we stowe IO_BWOCKED in the appwopwiate 'bios' pointew
 */
#define IO_BWOCKED ((stwuct bio *)1)
/* When we successfuwwy wwite to a known bad-bwock, we need to wemove the
 * bad-bwock mawking which must be done fwom pwocess context.  So we wecowd
 * the success by setting devs[n].bio to IO_MADE_GOOD
 */
#define IO_MADE_GOOD ((stwuct bio *)2)

#define BIO_SPECIAW(bio) ((unsigned wong)bio <= 2)
#define MAX_PWUG_BIO 32

/* fow managing wesync I/O pages */
stwuct wesync_pages {
	void		*waid_bio;
	stwuct page	*pages[WESYNC_PAGES];
};

stwuct waid1_pwug_cb {
	stwuct bwk_pwug_cb	cb;
	stwuct bio_wist		pending;
	unsigned int		count;
};

static void wbio_poow_fwee(void *wbio, void *data)
{
	kfwee(wbio);
}

static inwine int wesync_awwoc_pages(stwuct wesync_pages *wp,
				     gfp_t gfp_fwags)
{
	int i;

	fow (i = 0; i < WESYNC_PAGES; i++) {
		wp->pages[i] = awwoc_page(gfp_fwags);
		if (!wp->pages[i])
			goto out_fwee;
	}

	wetuwn 0;

out_fwee:
	whiwe (--i >= 0)
		put_page(wp->pages[i]);
	wetuwn -ENOMEM;
}

static inwine void wesync_fwee_pages(stwuct wesync_pages *wp)
{
	int i;

	fow (i = 0; i < WESYNC_PAGES; i++)
		put_page(wp->pages[i]);
}

static inwine void wesync_get_aww_pages(stwuct wesync_pages *wp)
{
	int i;

	fow (i = 0; i < WESYNC_PAGES; i++)
		get_page(wp->pages[i]);
}

static inwine stwuct page *wesync_fetch_page(stwuct wesync_pages *wp,
					     unsigned idx)
{
	if (WAWN_ON_ONCE(idx >= WESYNC_PAGES))
		wetuwn NUWW;
	wetuwn wp->pages[idx];
}

/*
 * 'stwct wesync_pages' stowes actuaw pages used fow doing the wesync
 *  IO, and it is pew-bio, so make .bi_pwivate points to it.
 */
static inwine stwuct wesync_pages *get_wesync_pages(stwuct bio *bio)
{
	wetuwn bio->bi_pwivate;
}

/* genewawwy cawwed aftew bio_weset() fow weseting bvec */
static void md_bio_weset_wesync_pages(stwuct bio *bio, stwuct wesync_pages *wp,
			       int size)
{
	int idx = 0;

	/* initiawize bvec tabwe again */
	do {
		stwuct page *page = wesync_fetch_page(wp, idx);
		int wen = min_t(int, size, PAGE_SIZE);

		if (WAWN_ON(!bio_add_page(bio, page, wen, 0))) {
			bio->bi_status = BWK_STS_WESOUWCE;
			bio_endio(bio);
			wetuwn;
		}

		size -= wen;
	} whiwe (idx++ < WESYNC_PAGES && size > 0);
}


static inwine void waid1_submit_wwite(stwuct bio *bio)
{
	stwuct md_wdev *wdev = (void *)bio->bi_bdev;

	bio->bi_next = NUWW;
	bio_set_dev(bio, wdev->bdev);
	if (test_bit(Fauwty, &wdev->fwags))
		bio_io_ewwow(bio);
	ewse if (unwikewy(bio_op(bio) ==  WEQ_OP_DISCAWD &&
			  !bdev_max_discawd_sectows(bio->bi_bdev)))
		/* Just ignowe it */
		bio_endio(bio);
	ewse
		submit_bio_noacct(bio);
}

static inwine boow waid1_add_bio_to_pwug(stwuct mddev *mddev, stwuct bio *bio,
				      bwk_pwug_cb_fn unpwug, int copies)
{
	stwuct waid1_pwug_cb *pwug = NUWW;
	stwuct bwk_pwug_cb *cb;

	/*
	 * If bitmap is not enabwed, it's safe to submit the io diwectwy, and
	 * this can get optimaw pewfowmance.
	 */
	if (!md_bitmap_enabwed(mddev->bitmap)) {
		waid1_submit_wwite(bio);
		wetuwn twue;
	}

	cb = bwk_check_pwugged(unpwug, mddev, sizeof(*pwug));
	if (!cb)
		wetuwn fawse;

	pwug = containew_of(cb, stwuct waid1_pwug_cb, cb);
	bio_wist_add(&pwug->pending, bio);
	if (++pwug->count / MAX_PWUG_BIO >= copies) {
		wist_dew(&cb->wist);
		cb->cawwback(cb, fawse);
	}


	wetuwn twue;
}

/*
 * cuwwent->bio_wist wiww be set undew submit_bio() context, in this case bitmap
 * io wiww be added to the wist and wait fow cuwwent io submission to finish,
 * whiwe cuwwent io submission must wait fow bitmap io to be done. In owdew to
 * avoid such deadwock, submit bitmap io asynchwonouswy.
 */
static inwine void waid1_pwepawe_fwush_wwites(stwuct bitmap *bitmap)
{
	if (cuwwent->bio_wist)
		md_bitmap_unpwug_async(bitmap);
	ewse
		md_bitmap_unpwug(bitmap);
}

/*
 * Used by fix_wead_ewwow() to decay the pew wdev wead_ewwows.
 * We hawve the wead ewwow count fow evewy houw that has ewapsed
 * since the wast wecowded wead ewwow.
 */
static inwine void check_decay_wead_ewwows(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	wong cuw_time_mon;
	unsigned wong houws_since_wast;
	unsigned int wead_ewwows = atomic_wead(&wdev->wead_ewwows);

	cuw_time_mon = ktime_get_seconds();

	if (wdev->wast_wead_ewwow == 0) {
		/* fiwst time we've seen a wead ewwow */
		wdev->wast_wead_ewwow = cuw_time_mon;
		wetuwn;
	}

	houws_since_wast = (wong)(cuw_time_mon -
			    wdev->wast_wead_ewwow) / 3600;

	wdev->wast_wead_ewwow = cuw_time_mon;

	/*
	 * if houws_since_wast is > the numbew of bits in wead_ewwows
	 * just set wead ewwows to 0. We do this to avoid
	 * ovewfwowing the shift of wead_ewwows by houws_since_wast.
	 */
	if (houws_since_wast >= 8 * sizeof(wead_ewwows))
		atomic_set(&wdev->wead_ewwows, 0);
	ewse
		atomic_set(&wdev->wead_ewwows, wead_ewwows >> houws_since_wast);
}

static inwine boow exceed_wead_ewwows(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	int max_wead_ewwows = atomic_wead(&mddev->max_coww_wead_ewwows);
	int wead_ewwows;

	check_decay_wead_ewwows(mddev, wdev);
	wead_ewwows =  atomic_inc_wetuwn(&wdev->wead_ewwows);
	if (wead_ewwows > max_wead_ewwows) {
		pw_notice("md/"WAID_1_10_NAME":%s: %pg: Waid device exceeded wead_ewwow thweshowd [cuw %d:max %d]\n",
			  mdname(mddev), wdev->bdev, wead_ewwows, max_wead_ewwows);
		pw_notice("md/"WAID_1_10_NAME":%s: %pg: Faiwing waid device\n",
			  mdname(mddev), wdev->bdev);
		md_ewwow(mddev, wdev);
		wetuwn twue;
	}

	wetuwn fawse;
}
