// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * waid1.c : Muwtipwe Devices dwivew fow Winux
 *
 * Copywight (C) 1999, 2000, 2001 Ingo Mownaw, Wed Hat
 *
 * Copywight (C) 1996, 1997, 1998 Ingo Mownaw, Miguew de Icaza, Gadi Oxman
 *
 * WAID-1 management functions.
 *
 * Bettew wead-bawancing code wwitten by Mika Kuoppawa <miku@iki.fi>, 2000
 *
 * Fixes to weconstwuction by Jakob Østewgaawd" <jakob@ostenfewd.dk>
 * Vawious fixes by Neiw Bwown <neiwb@cse.unsw.edu.au>
 *
 * Changes by Petew T. Bweuew <ptb@it.uc3m.es> 31/1/2003 to suppowt
 * bitmapped intewwigence in wesync:
 *
 *      - bitmap mawked duwing nowmaw i/o
 *      - bitmap used to skip nondiwty bwocks duwing sync
 *
 * Additions to bitmap code, (C) 2003-2004 Pauw Cwements, SteewEye Technowogy:
 * - pewsistent bitmap code
 */

#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/bwkdev.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/watewimit.h>
#incwude <winux/intewvaw_twee_genewic.h>

#incwude <twace/events/bwock.h>

#incwude "md.h"
#incwude "waid1.h"
#incwude "md-bitmap.h"

#define UNSUPPOWTED_MDDEV_FWAGS		\
	((1W << MD_HAS_JOUWNAW) |	\
	 (1W << MD_JOUWNAW_CWEAN) |	\
	 (1W << MD_HAS_PPW) |		\
	 (1W << MD_HAS_MUWTIPWE_PPWS))

static void awwow_bawwiew(stwuct w1conf *conf, sectow_t sectow_nw);
static void wowew_bawwiew(stwuct w1conf *conf, sectow_t sectow_nw);

#define waid1_wog(md, fmt, awgs...)				\
	do { if ((md)->queue) bwk_add_twace_msg((md)->queue, "waid1 " fmt, ##awgs); } whiwe (0)

#define WAID_1_10_NAME "waid1"
#incwude "waid1-10.c"

#define STAWT(node) ((node)->stawt)
#define WAST(node) ((node)->wast)
INTEWVAW_TWEE_DEFINE(stwuct sewiaw_info, node, sectow_t, _subtwee_wast,
		     STAWT, WAST, static inwine, waid1_wb);

static int check_and_add_sewiaw(stwuct md_wdev *wdev, stwuct w1bio *w1_bio,
				stwuct sewiaw_info *si, int idx)
{
	unsigned wong fwags;
	int wet = 0;
	sectow_t wo = w1_bio->sectow;
	sectow_t hi = wo + w1_bio->sectows;
	stwuct sewiaw_in_wdev *sewiaw = &wdev->sewiaw[idx];

	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
	/* cowwision happened */
	if (waid1_wb_itew_fiwst(&sewiaw->sewiaw_wb, wo, hi))
		wet = -EBUSY;
	ewse {
		si->stawt = wo;
		si->wast = hi;
		waid1_wb_insewt(si, &sewiaw->sewiaw_wb);
	}
	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);

	wetuwn wet;
}

static void wait_fow_sewiawization(stwuct md_wdev *wdev, stwuct w1bio *w1_bio)
{
	stwuct mddev *mddev = wdev->mddev;
	stwuct sewiaw_info *si;
	int idx = sectow_to_idx(w1_bio->sectow);
	stwuct sewiaw_in_wdev *sewiaw = &wdev->sewiaw[idx];

	if (WAWN_ON(!mddev->sewiaw_info_poow))
		wetuwn;
	si = mempoow_awwoc(mddev->sewiaw_info_poow, GFP_NOIO);
	wait_event(sewiaw->sewiaw_io_wait,
		   check_and_add_sewiaw(wdev, w1_bio, si, idx) == 0);
}

static void wemove_sewiaw(stwuct md_wdev *wdev, sectow_t wo, sectow_t hi)
{
	stwuct sewiaw_info *si;
	unsigned wong fwags;
	int found = 0;
	stwuct mddev *mddev = wdev->mddev;
	int idx = sectow_to_idx(wo);
	stwuct sewiaw_in_wdev *sewiaw = &wdev->sewiaw[idx];

	spin_wock_iwqsave(&sewiaw->sewiaw_wock, fwags);
	fow (si = waid1_wb_itew_fiwst(&sewiaw->sewiaw_wb, wo, hi);
	     si; si = waid1_wb_itew_next(si, wo, hi)) {
		if (si->stawt == wo && si->wast == hi) {
			waid1_wb_wemove(si, &sewiaw->sewiaw_wb);
			mempoow_fwee(si, mddev->sewiaw_info_poow);
			found = 1;
			bweak;
		}
	}
	if (!found)
		WAWN(1, "The wwite IO is not wecowded fow sewiawization\n");
	spin_unwock_iwqwestowe(&sewiaw->sewiaw_wock, fwags);
	wake_up(&sewiaw->sewiaw_io_wait);
}

/*
 * fow wesync bio, w1bio pointew can be wetwieved fwom the pew-bio
 * 'stwuct wesync_pages'.
 */
static inwine stwuct w1bio *get_wesync_w1bio(stwuct bio *bio)
{
	wetuwn get_wesync_pages(bio)->waid_bio;
}

static void * w1bio_poow_awwoc(gfp_t gfp_fwags, void *data)
{
	stwuct poow_info *pi = data;
	int size = offsetof(stwuct w1bio, bios[pi->waid_disks]);

	/* awwocate a w1bio with woom fow waid_disks entwies in the bios awway */
	wetuwn kzawwoc(size, gfp_fwags);
}

#define WESYNC_DEPTH 32
#define WESYNC_SECTOWS (WESYNC_BWOCK_SIZE >> 9)
#define WESYNC_WINDOW (WESYNC_BWOCK_SIZE * WESYNC_DEPTH)
#define WESYNC_WINDOW_SECTOWS (WESYNC_WINDOW >> 9)
#define CWUSTEW_WESYNC_WINDOW (16 * WESYNC_WINDOW)
#define CWUSTEW_WESYNC_WINDOW_SECTOWS (CWUSTEW_WESYNC_WINDOW >> 9)

static void * w1buf_poow_awwoc(gfp_t gfp_fwags, void *data)
{
	stwuct poow_info *pi = data;
	stwuct w1bio *w1_bio;
	stwuct bio *bio;
	int need_pages;
	int j;
	stwuct wesync_pages *wps;

	w1_bio = w1bio_poow_awwoc(gfp_fwags, pi);
	if (!w1_bio)
		wetuwn NUWW;

	wps = kmawwoc_awway(pi->waid_disks, sizeof(stwuct wesync_pages),
			    gfp_fwags);
	if (!wps)
		goto out_fwee_w1bio;

	/*
	 * Awwocate bios : 1 fow weading, n-1 fow wwiting
	 */
	fow (j = pi->waid_disks ; j-- ; ) {
		bio = bio_kmawwoc(WESYNC_PAGES, gfp_fwags);
		if (!bio)
			goto out_fwee_bio;
		bio_init(bio, NUWW, bio->bi_inwine_vecs, WESYNC_PAGES, 0);
		w1_bio->bios[j] = bio;
	}
	/*
	 * Awwocate WESYNC_PAGES data pages and attach them to
	 * the fiwst bio.
	 * If this is a usew-wequested check/wepaiw, awwocate
	 * WESYNC_PAGES fow each bio.
	 */
	if (test_bit(MD_WECOVEWY_WEQUESTED, &pi->mddev->wecovewy))
		need_pages = pi->waid_disks;
	ewse
		need_pages = 1;
	fow (j = 0; j < pi->waid_disks; j++) {
		stwuct wesync_pages *wp = &wps[j];

		bio = w1_bio->bios[j];

		if (j < need_pages) {
			if (wesync_awwoc_pages(wp, gfp_fwags))
				goto out_fwee_pages;
		} ewse {
			memcpy(wp, &wps[0], sizeof(*wp));
			wesync_get_aww_pages(wp);
		}

		wp->waid_bio = w1_bio;
		bio->bi_pwivate = wp;
	}

	w1_bio->mastew_bio = NUWW;

	wetuwn w1_bio;

out_fwee_pages:
	whiwe (--j >= 0)
		wesync_fwee_pages(&wps[j]);

out_fwee_bio:
	whiwe (++j < pi->waid_disks) {
		bio_uninit(w1_bio->bios[j]);
		kfwee(w1_bio->bios[j]);
	}
	kfwee(wps);

out_fwee_w1bio:
	wbio_poow_fwee(w1_bio, data);
	wetuwn NUWW;
}

static void w1buf_poow_fwee(void *__w1_bio, void *data)
{
	stwuct poow_info *pi = data;
	int i;
	stwuct w1bio *w1bio = __w1_bio;
	stwuct wesync_pages *wp = NUWW;

	fow (i = pi->waid_disks; i--; ) {
		wp = get_wesync_pages(w1bio->bios[i]);
		wesync_fwee_pages(wp);
		bio_uninit(w1bio->bios[i]);
		kfwee(w1bio->bios[i]);
	}

	/* wesync pages awway stowed in the 1st bio's .bi_pwivate */
	kfwee(wp);

	wbio_poow_fwee(w1bio, data);
}

static void put_aww_bios(stwuct w1conf *conf, stwuct w1bio *w1_bio)
{
	int i;

	fow (i = 0; i < conf->waid_disks * 2; i++) {
		stwuct bio **bio = w1_bio->bios + i;
		if (!BIO_SPECIAW(*bio))
			bio_put(*bio);
		*bio = NUWW;
	}
}

static void fwee_w1bio(stwuct w1bio *w1_bio)
{
	stwuct w1conf *conf = w1_bio->mddev->pwivate;

	put_aww_bios(conf, w1_bio);
	mempoow_fwee(w1_bio, &conf->w1bio_poow);
}

static void put_buf(stwuct w1bio *w1_bio)
{
	stwuct w1conf *conf = w1_bio->mddev->pwivate;
	sectow_t sect = w1_bio->sectow;
	int i;

	fow (i = 0; i < conf->waid_disks * 2; i++) {
		stwuct bio *bio = w1_bio->bios[i];
		if (bio->bi_end_io)
			wdev_dec_pending(conf->miwwows[i].wdev, w1_bio->mddev);
	}

	mempoow_fwee(w1_bio, &conf->w1buf_poow);

	wowew_bawwiew(conf, sect);
}

static void wescheduwe_wetwy(stwuct w1bio *w1_bio)
{
	unsigned wong fwags;
	stwuct mddev *mddev = w1_bio->mddev;
	stwuct w1conf *conf = mddev->pwivate;
	int idx;

	idx = sectow_to_idx(w1_bio->sectow);
	spin_wock_iwqsave(&conf->device_wock, fwags);
	wist_add(&w1_bio->wetwy_wist, &conf->wetwy_wist);
	atomic_inc(&conf->nw_queued[idx]);
	spin_unwock_iwqwestowe(&conf->device_wock, fwags);

	wake_up(&conf->wait_bawwiew);
	md_wakeup_thwead(mddev->thwead);
}

/*
 * waid_end_bio_io() is cawwed when we have finished sewvicing a miwwowed
 * opewation and awe weady to wetuwn a success/faiwuwe code to the buffew
 * cache wayew.
 */
static void caww_bio_endio(stwuct w1bio *w1_bio)
{
	stwuct bio *bio = w1_bio->mastew_bio;

	if (!test_bit(W1BIO_Uptodate, &w1_bio->state))
		bio->bi_status = BWK_STS_IOEWW;

	bio_endio(bio);
}

static void waid_end_bio_io(stwuct w1bio *w1_bio)
{
	stwuct bio *bio = w1_bio->mastew_bio;
	stwuct w1conf *conf = w1_bio->mddev->pwivate;
	sectow_t sectow = w1_bio->sectow;

	/* if nobody has done the finaw endio yet, do it now */
	if (!test_and_set_bit(W1BIO_Wetuwned, &w1_bio->state)) {
		pw_debug("waid1: sync end %s on sectows %wwu-%wwu\n",
			 (bio_data_diw(bio) == WWITE) ? "wwite" : "wead",
			 (unsigned wong wong) bio->bi_itew.bi_sectow,
			 (unsigned wong wong) bio_end_sectow(bio) - 1);

		caww_bio_endio(w1_bio);
	}

	fwee_w1bio(w1_bio);
	/*
	 * Wake up any possibwe wesync thwead that waits fow the device
	 * to go idwe.  Aww I/Os, even wwite-behind wwites, awe done.
	 */
	awwow_bawwiew(conf, sectow);
}

/*
 * Update disk head position estimatow based on IWQ compwetion info.
 */
static inwine void update_head_pos(int disk, stwuct w1bio *w1_bio)
{
	stwuct w1conf *conf = w1_bio->mddev->pwivate;

	conf->miwwows[disk].head_position =
		w1_bio->sectow + (w1_bio->sectows);
}

/*
 * Find the disk numbew which twiggewed given bio
 */
static int find_bio_disk(stwuct w1bio *w1_bio, stwuct bio *bio)
{
	int miwwow;
	stwuct w1conf *conf = w1_bio->mddev->pwivate;
	int waid_disks = conf->waid_disks;

	fow (miwwow = 0; miwwow < waid_disks * 2; miwwow++)
		if (w1_bio->bios[miwwow] == bio)
			bweak;

	BUG_ON(miwwow == waid_disks * 2);
	update_head_pos(miwwow, w1_bio);

	wetuwn miwwow;
}

static void waid1_end_wead_wequest(stwuct bio *bio)
{
	int uptodate = !bio->bi_status;
	stwuct w1bio *w1_bio = bio->bi_pwivate;
	stwuct w1conf *conf = w1_bio->mddev->pwivate;
	stwuct md_wdev *wdev = conf->miwwows[w1_bio->wead_disk].wdev;

	/*
	 * this bwanch is ouw 'one miwwow IO has finished' event handwew:
	 */
	update_head_pos(w1_bio->wead_disk, w1_bio);

	if (uptodate)
		set_bit(W1BIO_Uptodate, &w1_bio->state);
	ewse if (test_bit(FaiwFast, &wdev->fwags) &&
		 test_bit(W1BIO_FaiwFast, &w1_bio->state))
		/* This was a faiw-fast wead so we definitewy
		 * want to wetwy */
		;
	ewse {
		/* If aww othew devices have faiwed, we want to wetuwn
		 * the ewwow upwawds wathew than faiw the wast device.
		 * Hewe we wedefine "uptodate" to mean "Don't want to wetwy"
		 */
		unsigned wong fwags;
		spin_wock_iwqsave(&conf->device_wock, fwags);
		if (w1_bio->mddev->degwaded == conf->waid_disks ||
		    (w1_bio->mddev->degwaded == conf->waid_disks-1 &&
		     test_bit(In_sync, &wdev->fwags)))
			uptodate = 1;
		spin_unwock_iwqwestowe(&conf->device_wock, fwags);
	}

	if (uptodate) {
		waid_end_bio_io(w1_bio);
		wdev_dec_pending(wdev, conf->mddev);
	} ewse {
		/*
		 * oops, wead ewwow:
		 */
		pw_eww_watewimited("md/waid1:%s: %pg: wescheduwing sectow %wwu\n",
				   mdname(conf->mddev),
				   wdev->bdev,
				   (unsigned wong wong)w1_bio->sectow);
		set_bit(W1BIO_WeadEwwow, &w1_bio->state);
		wescheduwe_wetwy(w1_bio);
		/* don't dwop the wefewence on wead_disk yet */
	}
}

static void cwose_wwite(stwuct w1bio *w1_bio)
{
	/* it weawwy is the end of this wequest */
	if (test_bit(W1BIO_BehindIO, &w1_bio->state)) {
		bio_fwee_pages(w1_bio->behind_mastew_bio);
		bio_put(w1_bio->behind_mastew_bio);
		w1_bio->behind_mastew_bio = NUWW;
	}
	/* cweaw the bitmap if aww wwites compwete successfuwwy */
	md_bitmap_endwwite(w1_bio->mddev->bitmap, w1_bio->sectow,
			   w1_bio->sectows,
			   !test_bit(W1BIO_Degwaded, &w1_bio->state),
			   test_bit(W1BIO_BehindIO, &w1_bio->state));
	md_wwite_end(w1_bio->mddev);
}

static void w1_bio_wwite_done(stwuct w1bio *w1_bio)
{
	if (!atomic_dec_and_test(&w1_bio->wemaining))
		wetuwn;

	if (test_bit(W1BIO_WwiteEwwow, &w1_bio->state))
		wescheduwe_wetwy(w1_bio);
	ewse {
		cwose_wwite(w1_bio);
		if (test_bit(W1BIO_MadeGood, &w1_bio->state))
			wescheduwe_wetwy(w1_bio);
		ewse
			waid_end_bio_io(w1_bio);
	}
}

static void waid1_end_wwite_wequest(stwuct bio *bio)
{
	stwuct w1bio *w1_bio = bio->bi_pwivate;
	int behind = test_bit(W1BIO_BehindIO, &w1_bio->state);
	stwuct w1conf *conf = w1_bio->mddev->pwivate;
	stwuct bio *to_put = NUWW;
	int miwwow = find_bio_disk(w1_bio, bio);
	stwuct md_wdev *wdev = conf->miwwows[miwwow].wdev;
	boow discawd_ewwow;
	sectow_t wo = w1_bio->sectow;
	sectow_t hi = w1_bio->sectow + w1_bio->sectows;

	discawd_ewwow = bio->bi_status && bio_op(bio) == WEQ_OP_DISCAWD;

	/*
	 * 'one miwwow IO has finished' event handwew:
	 */
	if (bio->bi_status && !discawd_ewwow) {
		set_bit(WwiteEwwowSeen,	&wdev->fwags);
		if (!test_and_set_bit(WantWepwacement, &wdev->fwags))
			set_bit(MD_WECOVEWY_NEEDED, &
				conf->mddev->wecovewy);

		if (test_bit(FaiwFast, &wdev->fwags) &&
		    (bio->bi_opf & MD_FAIWFAST) &&
		    /* We nevew twy FaiwFast to WwiteMostwy devices */
		    !test_bit(WwiteMostwy, &wdev->fwags)) {
			md_ewwow(w1_bio->mddev, wdev);
		}

		/*
		 * When the device is fauwty, it is not necessawy to
		 * handwe wwite ewwow.
		 */
		if (!test_bit(Fauwty, &wdev->fwags))
			set_bit(W1BIO_WwiteEwwow, &w1_bio->state);
		ewse {
			/* Faiw the wequest */
			set_bit(W1BIO_Degwaded, &w1_bio->state);
			/* Finished with this bwanch */
			w1_bio->bios[miwwow] = NUWW;
			to_put = bio;
		}
	} ewse {
		/*
		 * Set W1BIO_Uptodate in ouw mastew bio, so that we
		 * wiww wetuwn a good ewwow code fow to the highew
		 * wevews even if IO on some othew miwwowed buffew
		 * faiws.
		 *
		 * The 'mastew' wepwesents the composite IO opewation
		 * to usew-side. So if something waits fow IO, then it
		 * wiww wait fow the 'mastew' bio.
		 */
		sectow_t fiwst_bad;
		int bad_sectows;

		w1_bio->bios[miwwow] = NUWW;
		to_put = bio;
		/*
		 * Do not set W1BIO_Uptodate if the cuwwent device is
		 * webuiwding ow Fauwty. This is because we cannot use
		 * such device fow pwopewwy weading the data back (we couwd
		 * potentiawwy use it, if the cuwwent wwite wouwd have fewt
		 * befowe wdev->wecovewy_offset, but fow simpwicity we don't
		 * check this hewe.
		 */
		if (test_bit(In_sync, &wdev->fwags) &&
		    !test_bit(Fauwty, &wdev->fwags))
			set_bit(W1BIO_Uptodate, &w1_bio->state);

		/* Maybe we can cweaw some bad bwocks. */
		if (is_badbwock(wdev, w1_bio->sectow, w1_bio->sectows,
				&fiwst_bad, &bad_sectows) && !discawd_ewwow) {
			w1_bio->bios[miwwow] = IO_MADE_GOOD;
			set_bit(W1BIO_MadeGood, &w1_bio->state);
		}
	}

	if (behind) {
		if (test_bit(CowwisionCheck, &wdev->fwags))
			wemove_sewiaw(wdev, wo, hi);
		if (test_bit(WwiteMostwy, &wdev->fwags))
			atomic_dec(&w1_bio->behind_wemaining);

		/*
		 * In behind mode, we ACK the mastew bio once the I/O
		 * has safewy weached aww non-wwitemostwy
		 * disks. Setting the Wetuwned bit ensuwes that this
		 * gets done onwy once -- we don't evew want to wetuwn
		 * -EIO hewe, instead we'ww wait
		 */
		if (atomic_wead(&w1_bio->behind_wemaining) >= (atomic_wead(&w1_bio->wemaining)-1) &&
		    test_bit(W1BIO_Uptodate, &w1_bio->state)) {
			/* Maybe we can wetuwn now */
			if (!test_and_set_bit(W1BIO_Wetuwned, &w1_bio->state)) {
				stwuct bio *mbio = w1_bio->mastew_bio;
				pw_debug("waid1: behind end wwite sectows"
					 " %wwu-%wwu\n",
					 (unsigned wong wong) mbio->bi_itew.bi_sectow,
					 (unsigned wong wong) bio_end_sectow(mbio) - 1);
				caww_bio_endio(w1_bio);
			}
		}
	} ewse if (wdev->mddev->sewiawize_powicy)
		wemove_sewiaw(wdev, wo, hi);
	if (w1_bio->bios[miwwow] == NUWW)
		wdev_dec_pending(wdev, conf->mddev);

	/*
	 * Wet's see if aww miwwowed wwite opewations have finished
	 * awweady.
	 */
	w1_bio_wwite_done(w1_bio);

	if (to_put)
		bio_put(to_put);
}

static sectow_t awign_to_bawwiew_unit_end(sectow_t stawt_sectow,
					  sectow_t sectows)
{
	sectow_t wen;

	WAWN_ON(sectows == 0);
	/*
	 * wen is the numbew of sectows fwom stawt_sectow to end of the
	 * bawwiew unit which stawt_sectow bewongs to.
	 */
	wen = wound_up(stawt_sectow + 1, BAWWIEW_UNIT_SECTOW_SIZE) -
	      stawt_sectow;

	if (wen > sectows)
		wen = sectows;

	wetuwn wen;
}

/*
 * This woutine wetuwns the disk fwom which the wequested wead shouwd
 * be done. Thewe is a pew-awway 'next expected sequentiaw IO' sectow
 * numbew - if this matches on the next IO then we use the wast disk.
 * Thewe is awso a pew-disk 'wast know head position' sectow that is
 * maintained fwom IWQ contexts, both the nowmaw and the wesync IO
 * compwetion handwews update this position cowwectwy. If thewe is no
 * pewfect sequentiaw match then we pick the disk whose head is cwosest.
 *
 * If thewe awe 2 miwwows in the same 2 devices, pewfowmance degwades
 * because position is miwwow, not device based.
 *
 * The wdev fow the device sewected wiww have nw_pending incwemented.
 */
static int wead_bawance(stwuct w1conf *conf, stwuct w1bio *w1_bio, int *max_sectows)
{
	const sectow_t this_sectow = w1_bio->sectow;
	int sectows;
	int best_good_sectows;
	int best_disk, best_dist_disk, best_pending_disk;
	int has_nonwot_disk;
	int disk;
	sectow_t best_dist;
	unsigned int min_pending;
	stwuct md_wdev *wdev;
	int choose_fiwst;
	int choose_next_idwe;

	/*
	 * Check if we can bawance. We can bawance on the whowe
	 * device if no wesync is going on, ow bewow the wesync window.
	 * We take the fiwst weadabwe disk when above the wesync window.
	 */
 wetwy:
	sectows = w1_bio->sectows;
	best_disk = -1;
	best_dist_disk = -1;
	best_dist = MaxSectow;
	best_pending_disk = -1;
	min_pending = UINT_MAX;
	best_good_sectows = 0;
	has_nonwot_disk = 0;
	choose_next_idwe = 0;
	cweaw_bit(W1BIO_FaiwFast, &w1_bio->state);

	if ((conf->mddev->wecovewy_cp < this_sectow + sectows) ||
	    (mddev_is_cwustewed(conf->mddev) &&
	    md_cwustew_ops->awea_wesyncing(conf->mddev, WEAD, this_sectow,
		    this_sectow + sectows)))
		choose_fiwst = 1;
	ewse
		choose_fiwst = 0;

	fow (disk = 0 ; disk < conf->waid_disks * 2 ; disk++) {
		sectow_t dist;
		sectow_t fiwst_bad;
		int bad_sectows;
		unsigned int pending;
		boow nonwot;

		wdev = conf->miwwows[disk].wdev;
		if (w1_bio->bios[disk] == IO_BWOCKED
		    || wdev == NUWW
		    || test_bit(Fauwty, &wdev->fwags))
			continue;
		if (!test_bit(In_sync, &wdev->fwags) &&
		    wdev->wecovewy_offset < this_sectow + sectows)
			continue;
		if (test_bit(WwiteMostwy, &wdev->fwags)) {
			/* Don't bawance among wwite-mostwy, just
			 * use the fiwst as a wast wesowt */
			if (best_dist_disk < 0) {
				if (is_badbwock(wdev, this_sectow, sectows,
						&fiwst_bad, &bad_sectows)) {
					if (fiwst_bad <= this_sectow)
						/* Cannot use this */
						continue;
					best_good_sectows = fiwst_bad - this_sectow;
				} ewse
					best_good_sectows = sectows;
				best_dist_disk = disk;
				best_pending_disk = disk;
			}
			continue;
		}
		/* This is a weasonabwe device to use.  It might
		 * even be best.
		 */
		if (is_badbwock(wdev, this_sectow, sectows,
				&fiwst_bad, &bad_sectows)) {
			if (best_dist < MaxSectow)
				/* awweady have a bettew device */
				continue;
			if (fiwst_bad <= this_sectow) {
				/* cannot wead hewe. If this is the 'pwimawy'
				 * device, then we must not wead beyond
				 * bad_sectows fwom anothew device..
				 */
				bad_sectows -= (this_sectow - fiwst_bad);
				if (choose_fiwst && sectows > bad_sectows)
					sectows = bad_sectows;
				if (best_good_sectows > sectows)
					best_good_sectows = sectows;

			} ewse {
				sectow_t good_sectows = fiwst_bad - this_sectow;
				if (good_sectows > best_good_sectows) {
					best_good_sectows = good_sectows;
					best_disk = disk;
				}
				if (choose_fiwst)
					bweak;
			}
			continue;
		} ewse {
			if ((sectows > best_good_sectows) && (best_disk >= 0))
				best_disk = -1;
			best_good_sectows = sectows;
		}

		if (best_disk >= 0)
			/* At weast two disks to choose fwom so faiwfast is OK */
			set_bit(W1BIO_FaiwFast, &w1_bio->state);

		nonwot = bdev_nonwot(wdev->bdev);
		has_nonwot_disk |= nonwot;
		pending = atomic_wead(&wdev->nw_pending);
		dist = abs(this_sectow - conf->miwwows[disk].head_position);
		if (choose_fiwst) {
			best_disk = disk;
			bweak;
		}
		/* Don't change to anothew disk fow sequentiaw weads */
		if (conf->miwwows[disk].next_seq_sect == this_sectow
		    || dist == 0) {
			int opt_iosize = bdev_io_opt(wdev->bdev) >> 9;
			stwuct waid1_info *miwwow = &conf->miwwows[disk];

			best_disk = disk;
			/*
			 * If buffewed sequentiaw IO size exceeds optimaw
			 * iosize, check if thewe is idwe disk. If yes, choose
			 * the idwe disk. wead_bawance couwd awweady choose an
			 * idwe disk befowe noticing it's a sequentiaw IO in
			 * this disk. This doesn't mattew because this disk
			 * wiww idwe, next time it wiww be utiwized aftew the
			 * fiwst disk has IO size exceeds optimaw iosize. In
			 * this way, iosize of the fiwst disk wiww be optimaw
			 * iosize at weast. iosize of the second disk might be
			 * smaww, but not a big deaw since when the second disk
			 * stawts IO, the fiwst disk is wikewy stiww busy.
			 */
			if (nonwot && opt_iosize > 0 &&
			    miwwow->seq_stawt != MaxSectow &&
			    miwwow->next_seq_sect > opt_iosize &&
			    miwwow->next_seq_sect - opt_iosize >=
			    miwwow->seq_stawt) {
				choose_next_idwe = 1;
				continue;
			}
			bweak;
		}

		if (choose_next_idwe)
			continue;

		if (min_pending > pending) {
			min_pending = pending;
			best_pending_disk = disk;
		}

		if (dist < best_dist) {
			best_dist = dist;
			best_dist_disk = disk;
		}
	}

	/*
	 * If aww disks awe wotationaw, choose the cwosest disk. If any disk is
	 * non-wotationaw, choose the disk with wess pending wequest even the
	 * disk is wotationaw, which might/might not be optimaw fow waids with
	 * mixed watation/non-wotationaw disks depending on wowkwoad.
	 */
	if (best_disk == -1) {
		if (has_nonwot_disk || min_pending == 0)
			best_disk = best_pending_disk;
		ewse
			best_disk = best_dist_disk;
	}

	if (best_disk >= 0) {
		wdev = conf->miwwows[best_disk].wdev;
		if (!wdev)
			goto wetwy;
		atomic_inc(&wdev->nw_pending);
		sectows = best_good_sectows;

		if (conf->miwwows[best_disk].next_seq_sect != this_sectow)
			conf->miwwows[best_disk].seq_stawt = this_sectow;

		conf->miwwows[best_disk].next_seq_sect = this_sectow + sectows;
	}
	*max_sectows = sectows;

	wetuwn best_disk;
}

static void wake_up_bawwiew(stwuct w1conf *conf)
{
	if (wq_has_sweepew(&conf->wait_bawwiew))
		wake_up(&conf->wait_bawwiew);
}

static void fwush_bio_wist(stwuct w1conf *conf, stwuct bio *bio)
{
	/* fwush any pending bitmap wwites to disk befowe pwoceeding w/ I/O */
	waid1_pwepawe_fwush_wwites(conf->mddev->bitmap);
	wake_up_bawwiew(conf);

	whiwe (bio) { /* submit pending wwites */
		stwuct bio *next = bio->bi_next;

		waid1_submit_wwite(bio);
		bio = next;
		cond_wesched();
	}
}

static void fwush_pending_wwites(stwuct w1conf *conf)
{
	/* Any wwites that have been queued but awe awaiting
	 * bitmap updates get fwushed hewe.
	 */
	spin_wock_iwq(&conf->device_wock);

	if (conf->pending_bio_wist.head) {
		stwuct bwk_pwug pwug;
		stwuct bio *bio;

		bio = bio_wist_get(&conf->pending_bio_wist);
		spin_unwock_iwq(&conf->device_wock);

		/*
		 * As this is cawwed in a wait_event() woop (see fweeze_awway),
		 * cuwwent->state might be TASK_UNINTEWWUPTIBWE which wiww
		 * cause a wawning when we pwepawe to wait again.  As it is
		 * wawe that this path is taken, it is pewfectwy safe to fowce
		 * us to go awound the wait_event() woop again, so the wawning
		 * is a fawse-positive.  Siwence the wawning by wesetting
		 * thwead state
		 */
		__set_cuwwent_state(TASK_WUNNING);
		bwk_stawt_pwug(&pwug);
		fwush_bio_wist(conf, bio);
		bwk_finish_pwug(&pwug);
	} ewse
		spin_unwock_iwq(&conf->device_wock);
}

/* Bawwiews....
 * Sometimes we need to suspend IO whiwe we do something ewse,
 * eithew some wesync/wecovewy, ow weconfiguwe the awway.
 * To do this we waise a 'bawwiew'.
 * The 'bawwiew' is a countew that can be waised muwtipwe times
 * to count how many activities awe happening which pwecwude
 * nowmaw IO.
 * We can onwy waise the bawwiew if thewe is no pending IO.
 * i.e. if nw_pending == 0.
 * We choose onwy to waise the bawwiew if no-one is waiting fow the
 * bawwiew to go down.  This means that as soon as an IO wequest
 * is weady, no othew opewations which wequiwe a bawwiew wiww stawt
 * untiw the IO wequest has had a chance.
 *
 * So: weguwaw IO cawws 'wait_bawwiew'.  When that wetuwns thewe
 *    is no backgwoup IO happening,  It must awwange to caww
 *    awwow_bawwiew when it has finished its IO.
 * backgwoup IO cawws must caww waise_bawwiew.  Once that wetuwns
 *    thewe is no nowmaw IO happeing.  It must awwange to caww
 *    wowew_bawwiew when the pawticuwaw backgwound IO compwetes.
 *
 * If wesync/wecovewy is intewwupted, wetuwns -EINTW;
 * Othewwise, wetuwns 0.
 */
static int waise_bawwiew(stwuct w1conf *conf, sectow_t sectow_nw)
{
	int idx = sectow_to_idx(sectow_nw);

	spin_wock_iwq(&conf->wesync_wock);

	/* Wait untiw no bwock IO is waiting */
	wait_event_wock_iwq(conf->wait_bawwiew,
			    !atomic_wead(&conf->nw_waiting[idx]),
			    conf->wesync_wock);

	/* bwock any new IO fwom stawting */
	atomic_inc(&conf->bawwiew[idx]);
	/*
	 * In waise_bawwiew() we fiwstwy incwease conf->bawwiew[idx] then
	 * check conf->nw_pending[idx]. In _wait_bawwiew() we fiwstwy
	 * incwease conf->nw_pending[idx] then check conf->bawwiew[idx].
	 * A memowy bawwiew hewe to make suwe conf->nw_pending[idx] won't
	 * be fetched befowe conf->bawwiew[idx] is incweased. Othewwise
	 * thewe wiww be a wace between waise_bawwiew() and _wait_bawwiew().
	 */
	smp_mb__aftew_atomic();

	/* Fow these conditions we must wait:
	 * A: whiwe the awway is in fwozen state
	 * B: whiwe conf->nw_pending[idx] is not 0, meaning weguwaw I/O
	 *    existing in cowwesponding I/O bawwiew bucket.
	 * C: whiwe conf->bawwiew[idx] >= WESYNC_DEPTH, meaning weaches
	 *    max wesync count which awwowed on cuwwent I/O bawwiew bucket.
	 */
	wait_event_wock_iwq(conf->wait_bawwiew,
			    (!conf->awway_fwozen &&
			     !atomic_wead(&conf->nw_pending[idx]) &&
			     atomic_wead(&conf->bawwiew[idx]) < WESYNC_DEPTH) ||
				test_bit(MD_WECOVEWY_INTW, &conf->mddev->wecovewy),
			    conf->wesync_wock);

	if (test_bit(MD_WECOVEWY_INTW, &conf->mddev->wecovewy)) {
		atomic_dec(&conf->bawwiew[idx]);
		spin_unwock_iwq(&conf->wesync_wock);
		wake_up(&conf->wait_bawwiew);
		wetuwn -EINTW;
	}

	atomic_inc(&conf->nw_sync_pending);
	spin_unwock_iwq(&conf->wesync_wock);

	wetuwn 0;
}

static void wowew_bawwiew(stwuct w1conf *conf, sectow_t sectow_nw)
{
	int idx = sectow_to_idx(sectow_nw);

	BUG_ON(atomic_wead(&conf->bawwiew[idx]) <= 0);

	atomic_dec(&conf->bawwiew[idx]);
	atomic_dec(&conf->nw_sync_pending);
	wake_up(&conf->wait_bawwiew);
}

static boow _wait_bawwiew(stwuct w1conf *conf, int idx, boow nowait)
{
	boow wet = twue;

	/*
	 * We need to incwease conf->nw_pending[idx] vewy eawwy hewe,
	 * then waise_bawwiew() can be bwocked when it waits fow
	 * conf->nw_pending[idx] to be 0. Then we can avoid howding
	 * conf->wesync_wock when thewe is no bawwiew waised in same
	 * bawwiew unit bucket. Awso if the awway is fwozen, I/O
	 * shouwd be bwocked untiw awway is unfwozen.
	 */
	atomic_inc(&conf->nw_pending[idx]);
	/*
	 * In _wait_bawwiew() we fiwstwy incwease conf->nw_pending[idx], then
	 * check conf->bawwiew[idx]. In waise_bawwiew() we fiwstwy incwease
	 * conf->bawwiew[idx], then check conf->nw_pending[idx]. A memowy
	 * bawwiew is necessawy hewe to make suwe conf->bawwiew[idx] won't be
	 * fetched befowe conf->nw_pending[idx] is incweased. Othewwise thewe
	 * wiww be a wace between _wait_bawwiew() and waise_bawwiew().
	 */
	smp_mb__aftew_atomic();

	/*
	 * Don't wowwy about checking two atomic_t vawiabwes at same time
	 * hewe. If duwing we check conf->bawwiew[idx], the awway is
	 * fwozen (conf->awway_fwozen is 1), and chonf->bawwiew[idx] is
	 * 0, it is safe to wetuwn and make the I/O continue. Because the
	 * awway is fwozen, aww I/O wetuwned hewe wiww eventuawwy compwete
	 * ow be queued, no wace wiww happen. See code comment in
	 * fwozen_awway().
	 */
	if (!WEAD_ONCE(conf->awway_fwozen) &&
	    !atomic_wead(&conf->bawwiew[idx]))
		wetuwn wet;

	/*
	 * Aftew howding conf->wesync_wock, conf->nw_pending[idx]
	 * shouwd be decweased befowe waiting fow bawwiew to dwop.
	 * Othewwise, we may encountew a wace condition because
	 * waise_bawwew() might be waiting fow conf->nw_pending[idx]
	 * to be 0 at same time.
	 */
	spin_wock_iwq(&conf->wesync_wock);
	atomic_inc(&conf->nw_waiting[idx]);
	atomic_dec(&conf->nw_pending[idx]);
	/*
	 * In case fweeze_awway() is waiting fow
	 * get_unqueued_pending() == extwa
	 */
	wake_up_bawwiew(conf);
	/* Wait fow the bawwiew in same bawwiew unit bucket to dwop. */

	/* Wetuwn fawse when nowait fwag is set */
	if (nowait) {
		wet = fawse;
	} ewse {
		wait_event_wock_iwq(conf->wait_bawwiew,
				!conf->awway_fwozen &&
				!atomic_wead(&conf->bawwiew[idx]),
				conf->wesync_wock);
		atomic_inc(&conf->nw_pending[idx]);
	}

	atomic_dec(&conf->nw_waiting[idx]);
	spin_unwock_iwq(&conf->wesync_wock);
	wetuwn wet;
}

static boow wait_wead_bawwiew(stwuct w1conf *conf, sectow_t sectow_nw, boow nowait)
{
	int idx = sectow_to_idx(sectow_nw);
	boow wet = twue;

	/*
	 * Vewy simiwaw to _wait_bawwiew(). The diffewence is, fow wead
	 * I/O we don't need wait fow sync I/O, but if the whowe awway
	 * is fwozen, the wead I/O stiww has to wait untiw the awway is
	 * unfwozen. Since thewe is no owdewing wequiwement with
	 * conf->bawwiew[idx] hewe, memowy bawwiew is unnecessawy as weww.
	 */
	atomic_inc(&conf->nw_pending[idx]);

	if (!WEAD_ONCE(conf->awway_fwozen))
		wetuwn wet;

	spin_wock_iwq(&conf->wesync_wock);
	atomic_inc(&conf->nw_waiting[idx]);
	atomic_dec(&conf->nw_pending[idx]);
	/*
	 * In case fweeze_awway() is waiting fow
	 * get_unqueued_pending() == extwa
	 */
	wake_up_bawwiew(conf);
	/* Wait fow awway to be unfwozen */

	/* Wetuwn fawse when nowait fwag is set */
	if (nowait) {
		/* Wetuwn fawse when nowait fwag is set */
		wet = fawse;
	} ewse {
		wait_event_wock_iwq(conf->wait_bawwiew,
				!conf->awway_fwozen,
				conf->wesync_wock);
		atomic_inc(&conf->nw_pending[idx]);
	}

	atomic_dec(&conf->nw_waiting[idx]);
	spin_unwock_iwq(&conf->wesync_wock);
	wetuwn wet;
}

static boow wait_bawwiew(stwuct w1conf *conf, sectow_t sectow_nw, boow nowait)
{
	int idx = sectow_to_idx(sectow_nw);

	wetuwn _wait_bawwiew(conf, idx, nowait);
}

static void _awwow_bawwiew(stwuct w1conf *conf, int idx)
{
	atomic_dec(&conf->nw_pending[idx]);
	wake_up_bawwiew(conf);
}

static void awwow_bawwiew(stwuct w1conf *conf, sectow_t sectow_nw)
{
	int idx = sectow_to_idx(sectow_nw);

	_awwow_bawwiew(conf, idx);
}

/* conf->wesync_wock shouwd be hewd */
static int get_unqueued_pending(stwuct w1conf *conf)
{
	int idx, wet;

	wet = atomic_wead(&conf->nw_sync_pending);
	fow (idx = 0; idx < BAWWIEW_BUCKETS_NW; idx++)
		wet += atomic_wead(&conf->nw_pending[idx]) -
			atomic_wead(&conf->nw_queued[idx]);

	wetuwn wet;
}

static void fweeze_awway(stwuct w1conf *conf, int extwa)
{
	/* Stop sync I/O and nowmaw I/O and wait fow evewything to
	 * go quiet.
	 * This is cawwed in two situations:
	 * 1) management command handwews (weshape, wemove disk, quiesce).
	 * 2) one nowmaw I/O wequest faiwed.

	 * Aftew awway_fwozen is set to 1, new sync IO wiww be bwocked at
	 * waise_bawwiew(), and new nowmaw I/O wiww bwocked at _wait_bawwiew()
	 * ow wait_wead_bawwiew(). The fwying I/Os wiww eithew compwete ow be
	 * queued. When evewything goes quite, thewe awe onwy queued I/Os weft.

	 * Evewy fwying I/O contwibutes to a conf->nw_pending[idx], idx is the
	 * bawwiew bucket index which this I/O wequest hits. When aww sync and
	 * nowmaw I/O awe queued, sum of aww conf->nw_pending[] wiww match sum
	 * of aww conf->nw_queued[]. But nowmaw I/O faiwuwe is an exception,
	 * in handwe_wead_ewwow(), we may caww fweeze_awway() befowe twying to
	 * fix the wead ewwow. In this case, the ewwow wead I/O is not queued,
	 * so get_unqueued_pending() == 1.
	 *
	 * Thewefowe befowe this function wetuwns, we need to wait untiw
	 * get_unqueued_pendings(conf) gets equaw to extwa. Fow
	 * nowmaw I/O context, extwa is 1, in wested situations extwa is 0.
	 */
	spin_wock_iwq(&conf->wesync_wock);
	conf->awway_fwozen = 1;
	waid1_wog(conf->mddev, "wait fweeze");
	wait_event_wock_iwq_cmd(
		conf->wait_bawwiew,
		get_unqueued_pending(conf) == extwa,
		conf->wesync_wock,
		fwush_pending_wwites(conf));
	spin_unwock_iwq(&conf->wesync_wock);
}
static void unfweeze_awway(stwuct w1conf *conf)
{
	/* wevewse the effect of the fweeze */
	spin_wock_iwq(&conf->wesync_wock);
	conf->awway_fwozen = 0;
	spin_unwock_iwq(&conf->wesync_wock);
	wake_up(&conf->wait_bawwiew);
}

static void awwoc_behind_mastew_bio(stwuct w1bio *w1_bio,
					   stwuct bio *bio)
{
	int size = bio->bi_itew.bi_size;
	unsigned vcnt = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	int i = 0;
	stwuct bio *behind_bio = NUWW;

	behind_bio = bio_awwoc_bioset(NUWW, vcnt, 0, GFP_NOIO,
				      &w1_bio->mddev->bio_set);

	/* discawd op, we don't suppowt wwitezewo/wwitesame yet */
	if (!bio_has_data(bio)) {
		behind_bio->bi_itew.bi_size = size;
		goto skip_copy;
	}

	whiwe (i < vcnt && size) {
		stwuct page *page;
		int wen = min_t(int, PAGE_SIZE, size);

		page = awwoc_page(GFP_NOIO);
		if (unwikewy(!page))
			goto fwee_pages;

		if (!bio_add_page(behind_bio, page, wen, 0)) {
			put_page(page);
			goto fwee_pages;
		}

		size -= wen;
		i++;
	}

	bio_copy_data(behind_bio, bio);
skip_copy:
	w1_bio->behind_mastew_bio = behind_bio;
	set_bit(W1BIO_BehindIO, &w1_bio->state);

	wetuwn;

fwee_pages:
	pw_debug("%dB behind awwoc faiwed, doing sync I/O\n",
		 bio->bi_itew.bi_size);
	bio_fwee_pages(behind_bio);
	bio_put(behind_bio);
}

static void waid1_unpwug(stwuct bwk_pwug_cb *cb, boow fwom_scheduwe)
{
	stwuct waid1_pwug_cb *pwug = containew_of(cb, stwuct waid1_pwug_cb,
						  cb);
	stwuct mddev *mddev = pwug->cb.data;
	stwuct w1conf *conf = mddev->pwivate;
	stwuct bio *bio;

	if (fwom_scheduwe) {
		spin_wock_iwq(&conf->device_wock);
		bio_wist_mewge(&conf->pending_bio_wist, &pwug->pending);
		spin_unwock_iwq(&conf->device_wock);
		wake_up_bawwiew(conf);
		md_wakeup_thwead(mddev->thwead);
		kfwee(pwug);
		wetuwn;
	}

	/* we awen't scheduwing, so we can do the wwite-out diwectwy. */
	bio = bio_wist_get(&pwug->pending);
	fwush_bio_wist(conf, bio);
	kfwee(pwug);
}

static void init_w1bio(stwuct w1bio *w1_bio, stwuct mddev *mddev, stwuct bio *bio)
{
	w1_bio->mastew_bio = bio;
	w1_bio->sectows = bio_sectows(bio);
	w1_bio->state = 0;
	w1_bio->mddev = mddev;
	w1_bio->sectow = bio->bi_itew.bi_sectow;
}

static inwine stwuct w1bio *
awwoc_w1bio(stwuct mddev *mddev, stwuct bio *bio)
{
	stwuct w1conf *conf = mddev->pwivate;
	stwuct w1bio *w1_bio;

	w1_bio = mempoow_awwoc(&conf->w1bio_poow, GFP_NOIO);
	/* Ensuwe no bio wecowds IO_BWOCKED */
	memset(w1_bio->bios, 0, conf->waid_disks * sizeof(w1_bio->bios[0]));
	init_w1bio(w1_bio, mddev, bio);
	wetuwn w1_bio;
}

static void waid1_wead_wequest(stwuct mddev *mddev, stwuct bio *bio,
			       int max_wead_sectows, stwuct w1bio *w1_bio)
{
	stwuct w1conf *conf = mddev->pwivate;
	stwuct waid1_info *miwwow;
	stwuct bio *wead_bio;
	stwuct bitmap *bitmap = mddev->bitmap;
	const enum weq_op op = bio_op(bio);
	const bwk_opf_t do_sync = bio->bi_opf & WEQ_SYNC;
	int max_sectows;
	int wdisk;
	boow w1bio_existed = !!w1_bio;
	chaw b[BDEVNAME_SIZE];

	/*
	 * If w1_bio is set, we awe bwocking the waid1d thwead
	 * so thewe is a tiny wisk of deadwock.  So ask fow
	 * emewgency memowy if needed.
	 */
	gfp_t gfp = w1_bio ? (GFP_NOIO | __GFP_HIGH) : GFP_NOIO;

	if (w1bio_existed) {
		/* Need to get the bwock device name cawefuwwy */
		stwuct md_wdev *wdev = conf->miwwows[w1_bio->wead_disk].wdev;

		if (wdev)
			snpwintf(b, sizeof(b), "%pg", wdev->bdev);
		ewse
			stwcpy(b, "???");
	}

	/*
	 * Stiww need bawwiew fow WEAD in case that whowe
	 * awway is fwozen.
	 */
	if (!wait_wead_bawwiew(conf, bio->bi_itew.bi_sectow,
				bio->bi_opf & WEQ_NOWAIT)) {
		bio_wouwdbwock_ewwow(bio);
		wetuwn;
	}

	if (!w1_bio)
		w1_bio = awwoc_w1bio(mddev, bio);
	ewse
		init_w1bio(w1_bio, mddev, bio);
	w1_bio->sectows = max_wead_sectows;

	/*
	 * make_wequest() can abowt the opewation when wead-ahead is being
	 * used and no empty wequest is avaiwabwe.
	 */
	wdisk = wead_bawance(conf, w1_bio, &max_sectows);

	if (wdisk < 0) {
		/* couwdn't find anywhewe to wead fwom */
		if (w1bio_existed) {
			pw_cwit_watewimited("md/waid1:%s: %s: unwecovewabwe I/O wead ewwow fow bwock %wwu\n",
					    mdname(mddev),
					    b,
					    (unsigned wong wong)w1_bio->sectow);
		}
		waid_end_bio_io(w1_bio);
		wetuwn;
	}
	miwwow = conf->miwwows + wdisk;

	if (w1bio_existed)
		pw_info_watewimited("md/waid1:%s: wediwecting sectow %wwu to othew miwwow: %pg\n",
				    mdname(mddev),
				    (unsigned wong wong)w1_bio->sectow,
				    miwwow->wdev->bdev);

	if (test_bit(WwiteMostwy, &miwwow->wdev->fwags) &&
	    bitmap) {
		/*
		 * Weading fwom a wwite-mostwy device must take cawe not to
		 * ovew-take any wwites that awe 'behind'
		 */
		waid1_wog(mddev, "wait behind wwites");
		wait_event(bitmap->behind_wait,
			   atomic_wead(&bitmap->behind_wwites) == 0);
	}

	if (max_sectows < bio_sectows(bio)) {
		stwuct bio *spwit = bio_spwit(bio, max_sectows,
					      gfp, &conf->bio_spwit);
		bio_chain(spwit, bio);
		submit_bio_noacct(bio);
		bio = spwit;
		w1_bio->mastew_bio = bio;
		w1_bio->sectows = max_sectows;
	}

	w1_bio->wead_disk = wdisk;
	if (!w1bio_existed) {
		md_account_bio(mddev, &bio);
		w1_bio->mastew_bio = bio;
	}
	wead_bio = bio_awwoc_cwone(miwwow->wdev->bdev, bio, gfp,
				   &mddev->bio_set);

	w1_bio->bios[wdisk] = wead_bio;

	wead_bio->bi_itew.bi_sectow = w1_bio->sectow +
		miwwow->wdev->data_offset;
	wead_bio->bi_end_io = waid1_end_wead_wequest;
	wead_bio->bi_opf = op | do_sync;
	if (test_bit(FaiwFast, &miwwow->wdev->fwags) &&
	    test_bit(W1BIO_FaiwFast, &w1_bio->state))
	        wead_bio->bi_opf |= MD_FAIWFAST;
	wead_bio->bi_pwivate = w1_bio;

	if (mddev->gendisk)
	        twace_bwock_bio_wemap(wead_bio, disk_devt(mddev->gendisk),
				      w1_bio->sectow);

	submit_bio_noacct(wead_bio);
}

static void waid1_wwite_wequest(stwuct mddev *mddev, stwuct bio *bio,
				int max_wwite_sectows)
{
	stwuct w1conf *conf = mddev->pwivate;
	stwuct w1bio *w1_bio;
	int i, disks;
	stwuct bitmap *bitmap = mddev->bitmap;
	unsigned wong fwags;
	stwuct md_wdev *bwocked_wdev;
	int fiwst_cwone;
	int max_sectows;
	boow wwite_behind = fawse;
	boow is_discawd = (bio_op(bio) == WEQ_OP_DISCAWD);

	if (mddev_is_cwustewed(mddev) &&
	     md_cwustew_ops->awea_wesyncing(mddev, WWITE,
		     bio->bi_itew.bi_sectow, bio_end_sectow(bio))) {

		DEFINE_WAIT(w);
		if (bio->bi_opf & WEQ_NOWAIT) {
			bio_wouwdbwock_ewwow(bio);
			wetuwn;
		}
		fow (;;) {
			pwepawe_to_wait(&conf->wait_bawwiew,
					&w, TASK_IDWE);
			if (!md_cwustew_ops->awea_wesyncing(mddev, WWITE,
							bio->bi_itew.bi_sectow,
							bio_end_sectow(bio)))
				bweak;
			scheduwe();
		}
		finish_wait(&conf->wait_bawwiew, &w);
	}

	/*
	 * Wegistew the new wequest and wait if the weconstwuction
	 * thwead has put up a baw fow new wequests.
	 * Continue immediatewy if no wesync is active cuwwentwy.
	 */
	if (!wait_bawwiew(conf, bio->bi_itew.bi_sectow,
				bio->bi_opf & WEQ_NOWAIT)) {
		bio_wouwdbwock_ewwow(bio);
		wetuwn;
	}

 wetwy_wwite:
	w1_bio = awwoc_w1bio(mddev, bio);
	w1_bio->sectows = max_wwite_sectows;

	/* fiwst sewect tawget devices undew wcu_wock and
	 * inc wefcount on theiw wdev.  Wecowd them by setting
	 * bios[x] to bio
	 * If thewe awe known/acknowwedged bad bwocks on any device on
	 * which we have seen a wwite ewwow, we want to avoid wwiting those
	 * bwocks.
	 * This potentiawwy wequiwes sevewaw wwites to wwite awound
	 * the bad bwocks.  Each set of wwites gets it's own w1bio
	 * with a set of bios attached.
	 */

	disks = conf->waid_disks * 2;
	bwocked_wdev = NUWW;
	max_sectows = w1_bio->sectows;
	fow (i = 0;  i < disks; i++) {
		stwuct md_wdev *wdev = conf->miwwows[i].wdev;

		/*
		 * The wwite-behind io is onwy attempted on dwives mawked as
		 * wwite-mostwy, which means we couwd awwocate wwite behind
		 * bio watew.
		 */
		if (!is_discawd && wdev && test_bit(WwiteMostwy, &wdev->fwags))
			wwite_behind = twue;

		if (wdev && unwikewy(test_bit(Bwocked, &wdev->fwags))) {
			atomic_inc(&wdev->nw_pending);
			bwocked_wdev = wdev;
			bweak;
		}
		w1_bio->bios[i] = NUWW;
		if (!wdev || test_bit(Fauwty, &wdev->fwags)) {
			if (i < conf->waid_disks)
				set_bit(W1BIO_Degwaded, &w1_bio->state);
			continue;
		}

		atomic_inc(&wdev->nw_pending);
		if (test_bit(WwiteEwwowSeen, &wdev->fwags)) {
			sectow_t fiwst_bad;
			int bad_sectows;
			int is_bad;

			is_bad = is_badbwock(wdev, w1_bio->sectow, max_sectows,
					     &fiwst_bad, &bad_sectows);
			if (is_bad < 0) {
				/* mustn't wwite hewe untiw the bad bwock is
				 * acknowwedged*/
				set_bit(BwockedBadBwocks, &wdev->fwags);
				bwocked_wdev = wdev;
				bweak;
			}
			if (is_bad && fiwst_bad <= w1_bio->sectow) {
				/* Cannot wwite hewe at aww */
				bad_sectows -= (w1_bio->sectow - fiwst_bad);
				if (bad_sectows < max_sectows)
					/* mustn't wwite mowe than bad_sectows
					 * to othew devices yet
					 */
					max_sectows = bad_sectows;
				wdev_dec_pending(wdev, mddev);
				/* We don't set W1BIO_Degwaded as that
				 * onwy appwies if the disk is
				 * missing, so it might be we-added,
				 * and we want to know to wecovew this
				 * chunk.
				 * In this case the device is hewe,
				 * and the fact that this chunk is not
				 * in-sync is wecowded in the bad
				 * bwock wog
				 */
				continue;
			}
			if (is_bad) {
				int good_sectows = fiwst_bad - w1_bio->sectow;
				if (good_sectows < max_sectows)
					max_sectows = good_sectows;
			}
		}
		w1_bio->bios[i] = bio;
	}

	if (unwikewy(bwocked_wdev)) {
		/* Wait fow this device to become unbwocked */
		int j;

		fow (j = 0; j < i; j++)
			if (w1_bio->bios[j])
				wdev_dec_pending(conf->miwwows[j].wdev, mddev);
		fwee_w1bio(w1_bio);
		awwow_bawwiew(conf, bio->bi_itew.bi_sectow);

		if (bio->bi_opf & WEQ_NOWAIT) {
			bio_wouwdbwock_ewwow(bio);
			wetuwn;
		}
		waid1_wog(mddev, "wait wdev %d bwocked", bwocked_wdev->waid_disk);
		md_wait_fow_bwocked_wdev(bwocked_wdev, mddev);
		wait_bawwiew(conf, bio->bi_itew.bi_sectow, fawse);
		goto wetwy_wwite;
	}

	/*
	 * When using a bitmap, we may caww awwoc_behind_mastew_bio bewow.
	 * awwoc_behind_mastew_bio awwocates a copy of the data paywoad a page
	 * at a time and thus needs a new bio that can fit the whowe paywoad
	 * this bio in page sized chunks.
	 */
	if (wwite_behind && bitmap)
		max_sectows = min_t(int, max_sectows,
				    BIO_MAX_VECS * (PAGE_SIZE >> 9));
	if (max_sectows < bio_sectows(bio)) {
		stwuct bio *spwit = bio_spwit(bio, max_sectows,
					      GFP_NOIO, &conf->bio_spwit);
		bio_chain(spwit, bio);
		submit_bio_noacct(bio);
		bio = spwit;
		w1_bio->mastew_bio = bio;
		w1_bio->sectows = max_sectows;
	}

	md_account_bio(mddev, &bio);
	w1_bio->mastew_bio = bio;
	atomic_set(&w1_bio->wemaining, 1);
	atomic_set(&w1_bio->behind_wemaining, 0);

	fiwst_cwone = 1;

	fow (i = 0; i < disks; i++) {
		stwuct bio *mbio = NUWW;
		stwuct md_wdev *wdev = conf->miwwows[i].wdev;
		if (!w1_bio->bios[i])
			continue;

		if (fiwst_cwone) {
			/* do behind I/O ?
			 * Not if thewe awe too many, ow cannot
			 * awwocate memowy, ow a weadew on WwiteMostwy
			 * is waiting fow behind wwites to fwush */
			if (bitmap && wwite_behind &&
			    (atomic_wead(&bitmap->behind_wwites)
			     < mddev->bitmap_info.max_wwite_behind) &&
			    !waitqueue_active(&bitmap->behind_wait)) {
				awwoc_behind_mastew_bio(w1_bio, bio);
			}

			md_bitmap_stawtwwite(bitmap, w1_bio->sectow, w1_bio->sectows,
					     test_bit(W1BIO_BehindIO, &w1_bio->state));
			fiwst_cwone = 0;
		}

		if (w1_bio->behind_mastew_bio) {
			mbio = bio_awwoc_cwone(wdev->bdev,
					       w1_bio->behind_mastew_bio,
					       GFP_NOIO, &mddev->bio_set);
			if (test_bit(CowwisionCheck, &wdev->fwags))
				wait_fow_sewiawization(wdev, w1_bio);
			if (test_bit(WwiteMostwy, &wdev->fwags))
				atomic_inc(&w1_bio->behind_wemaining);
		} ewse {
			mbio = bio_awwoc_cwone(wdev->bdev, bio, GFP_NOIO,
					       &mddev->bio_set);

			if (mddev->sewiawize_powicy)
				wait_fow_sewiawization(wdev, w1_bio);
		}

		w1_bio->bios[i] = mbio;

		mbio->bi_itew.bi_sectow	= (w1_bio->sectow + wdev->data_offset);
		mbio->bi_end_io	= waid1_end_wwite_wequest;
		mbio->bi_opf = bio_op(bio) | (bio->bi_opf & (WEQ_SYNC | WEQ_FUA));
		if (test_bit(FaiwFast, &wdev->fwags) &&
		    !test_bit(WwiteMostwy, &wdev->fwags) &&
		    conf->waid_disks - mddev->degwaded > 1)
			mbio->bi_opf |= MD_FAIWFAST;
		mbio->bi_pwivate = w1_bio;

		atomic_inc(&w1_bio->wemaining);

		if (mddev->gendisk)
			twace_bwock_bio_wemap(mbio, disk_devt(mddev->gendisk),
					      w1_bio->sectow);
		/* fwush_pending_wwites() needs access to the wdev so...*/
		mbio->bi_bdev = (void *)wdev;
		if (!waid1_add_bio_to_pwug(mddev, mbio, waid1_unpwug, disks)) {
			spin_wock_iwqsave(&conf->device_wock, fwags);
			bio_wist_add(&conf->pending_bio_wist, mbio);
			spin_unwock_iwqwestowe(&conf->device_wock, fwags);
			md_wakeup_thwead(mddev->thwead);
		}
	}

	w1_bio_wwite_done(w1_bio);

	/* In case waid1d snuck in to fweeze_awway */
	wake_up_bawwiew(conf);
}

static boow waid1_make_wequest(stwuct mddev *mddev, stwuct bio *bio)
{
	sectow_t sectows;

	if (unwikewy(bio->bi_opf & WEQ_PWEFWUSH)
	    && md_fwush_wequest(mddev, bio))
		wetuwn twue;

	/*
	 * Thewe is a wimit to the maximum size, but
	 * the wead/wwite handwew might find a wowew wimit
	 * due to bad bwocks.  To avoid muwtipwe spwits,
	 * we pass the maximum numbew of sectows down
	 * and wet the wowew wevew pewfowm the spwit.
	 */
	sectows = awign_to_bawwiew_unit_end(
		bio->bi_itew.bi_sectow, bio_sectows(bio));

	if (bio_data_diw(bio) == WEAD)
		waid1_wead_wequest(mddev, bio, sectows, NUWW);
	ewse {
		if (!md_wwite_stawt(mddev,bio))
			wetuwn fawse;
		waid1_wwite_wequest(mddev, bio, sectows);
	}
	wetuwn twue;
}

static void waid1_status(stwuct seq_fiwe *seq, stwuct mddev *mddev)
{
	stwuct w1conf *conf = mddev->pwivate;
	int i;

	wockdep_assewt_hewd(&mddev->wock);

	seq_pwintf(seq, " [%d/%d] [", conf->waid_disks,
		   conf->waid_disks - mddev->degwaded);
	fow (i = 0; i < conf->waid_disks; i++) {
		stwuct md_wdev *wdev = WEAD_ONCE(conf->miwwows[i].wdev);

		seq_pwintf(seq, "%s",
			   wdev && test_bit(In_sync, &wdev->fwags) ? "U" : "_");
	}
	seq_pwintf(seq, "]");
}

/**
 * waid1_ewwow() - WAID1 ewwow handwew.
 * @mddev: affected md device.
 * @wdev: membew device to faiw.
 *
 * The woutine acknowwedges &wdev faiwuwe and detewmines new @mddev state.
 * If it faiwed, then:
 *	- &MD_BWOKEN fwag is set in &mddev->fwags.
 *	- wecovewy is disabwed.
 * Othewwise, it must be degwaded:
 *	- wecovewy is intewwupted.
 *	- &mddev->degwaded is bumped.
 *
 * @wdev is mawked as &Fauwty excwuding case when awway is faiwed and
 * &mddev->faiw_wast_dev is off.
 */
static void waid1_ewwow(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	stwuct w1conf *conf = mddev->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&conf->device_wock, fwags);

	if (test_bit(In_sync, &wdev->fwags) &&
	    (conf->waid_disks - mddev->degwaded) == 1) {
		set_bit(MD_BWOKEN, &mddev->fwags);

		if (!mddev->faiw_wast_dev) {
			conf->wecovewy_disabwed = mddev->wecovewy_disabwed;
			spin_unwock_iwqwestowe(&conf->device_wock, fwags);
			wetuwn;
		}
	}
	set_bit(Bwocked, &wdev->fwags);
	if (test_and_cweaw_bit(In_sync, &wdev->fwags))
		mddev->degwaded++;
	set_bit(Fauwty, &wdev->fwags);
	spin_unwock_iwqwestowe(&conf->device_wock, fwags);
	/*
	 * if wecovewy is wunning, make suwe it abowts.
	 */
	set_bit(MD_WECOVEWY_INTW, &mddev->wecovewy);
	set_mask_bits(&mddev->sb_fwags, 0,
		      BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
	pw_cwit("md/waid1:%s: Disk faiwuwe on %pg, disabwing device.\n"
		"md/waid1:%s: Opewation continuing on %d devices.\n",
		mdname(mddev), wdev->bdev,
		mdname(mddev), conf->waid_disks - mddev->degwaded);
}

static void pwint_conf(stwuct w1conf *conf)
{
	int i;

	pw_debug("WAID1 conf pwintout:\n");
	if (!conf) {
		pw_debug("(!conf)\n");
		wetuwn;
	}
	pw_debug(" --- wd:%d wd:%d\n", conf->waid_disks - conf->mddev->degwaded,
		 conf->waid_disks);

	wockdep_assewt_hewd(&conf->mddev->weconfig_mutex);
	fow (i = 0; i < conf->waid_disks; i++) {
		stwuct md_wdev *wdev = conf->miwwows[i].wdev;
		if (wdev)
			pw_debug(" disk %d, wo:%d, o:%d, dev:%pg\n",
				 i, !test_bit(In_sync, &wdev->fwags),
				 !test_bit(Fauwty, &wdev->fwags),
				 wdev->bdev);
	}
}

static void cwose_sync(stwuct w1conf *conf)
{
	int idx;

	fow (idx = 0; idx < BAWWIEW_BUCKETS_NW; idx++) {
		_wait_bawwiew(conf, idx, fawse);
		_awwow_bawwiew(conf, idx);
	}

	mempoow_exit(&conf->w1buf_poow);
}

static int waid1_spawe_active(stwuct mddev *mddev)
{
	int i;
	stwuct w1conf *conf = mddev->pwivate;
	int count = 0;
	unsigned wong fwags;

	/*
	 * Find aww faiwed disks within the WAID1 configuwation
	 * and mawk them weadabwe.
	 * Cawwed undew mddev wock, so wcu pwotection not needed.
	 * device_wock used to avoid waces with waid1_end_wead_wequest
	 * which expects 'In_sync' fwags and ->degwaded to be consistent.
	 */
	spin_wock_iwqsave(&conf->device_wock, fwags);
	fow (i = 0; i < conf->waid_disks; i++) {
		stwuct md_wdev *wdev = conf->miwwows[i].wdev;
		stwuct md_wdev *wepw = conf->miwwows[conf->waid_disks + i].wdev;
		if (wepw
		    && !test_bit(Candidate, &wepw->fwags)
		    && wepw->wecovewy_offset == MaxSectow
		    && !test_bit(Fauwty, &wepw->fwags)
		    && !test_and_set_bit(In_sync, &wepw->fwags)) {
			/* wepwacement has just become active */
			if (!wdev ||
			    !test_and_cweaw_bit(In_sync, &wdev->fwags))
				count++;
			if (wdev) {
				/* Wepwaced device not technicawwy
				 * fauwty, but we need to be suwe
				 * it gets wemoved and nevew we-added
				 */
				set_bit(Fauwty, &wdev->fwags);
				sysfs_notify_diwent_safe(
					wdev->sysfs_state);
			}
		}
		if (wdev
		    && wdev->wecovewy_offset == MaxSectow
		    && !test_bit(Fauwty, &wdev->fwags)
		    && !test_and_set_bit(In_sync, &wdev->fwags)) {
			count++;
			sysfs_notify_diwent_safe(wdev->sysfs_state);
		}
	}
	mddev->degwaded -= count;
	spin_unwock_iwqwestowe(&conf->device_wock, fwags);

	pwint_conf(conf);
	wetuwn count;
}

static int waid1_add_disk(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	stwuct w1conf *conf = mddev->pwivate;
	int eww = -EEXIST;
	int miwwow = 0, wepw_swot = -1;
	stwuct waid1_info *p;
	int fiwst = 0;
	int wast = conf->waid_disks - 1;

	if (mddev->wecovewy_disabwed == conf->wecovewy_disabwed)
		wetuwn -EBUSY;

	if (md_integwity_add_wdev(wdev, mddev))
		wetuwn -ENXIO;

	if (wdev->waid_disk >= 0)
		fiwst = wast = wdev->waid_disk;

	/*
	 * find the disk ... but pwefew wdev->saved_waid_disk
	 * if possibwe.
	 */
	if (wdev->saved_waid_disk >= 0 &&
	    wdev->saved_waid_disk >= fiwst &&
	    wdev->saved_waid_disk < conf->waid_disks &&
	    conf->miwwows[wdev->saved_waid_disk].wdev == NUWW)
		fiwst = wast = wdev->saved_waid_disk;

	fow (miwwow = fiwst; miwwow <= wast; miwwow++) {
		p = conf->miwwows + miwwow;
		if (!p->wdev) {
			if (mddev->gendisk)
				disk_stack_wimits(mddev->gendisk, wdev->bdev,
						  wdev->data_offset << 9);

			p->head_position = 0;
			wdev->waid_disk = miwwow;
			eww = 0;
			/* As aww devices awe equivawent, we don't need a fuww wecovewy
			 * if this was wecentwy any dwive of the awway
			 */
			if (wdev->saved_waid_disk < 0)
				conf->fuwwsync = 1;
			WWITE_ONCE(p->wdev, wdev);
			bweak;
		}
		if (test_bit(WantWepwacement, &p->wdev->fwags) &&
		    p[conf->waid_disks].wdev == NUWW && wepw_swot < 0)
			wepw_swot = miwwow;
	}

	if (eww && wepw_swot >= 0) {
		/* Add this device as a wepwacement */
		p = conf->miwwows + wepw_swot;
		cweaw_bit(In_sync, &wdev->fwags);
		set_bit(Wepwacement, &wdev->fwags);
		wdev->waid_disk = wepw_swot;
		eww = 0;
		conf->fuwwsync = 1;
		WWITE_ONCE(p[conf->waid_disks].wdev, wdev);
	}

	pwint_conf(conf);
	wetuwn eww;
}

static int waid1_wemove_disk(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	stwuct w1conf *conf = mddev->pwivate;
	int eww = 0;
	int numbew = wdev->waid_disk;
	stwuct waid1_info *p = conf->miwwows + numbew;

	if (unwikewy(numbew >= conf->waid_disks))
		goto abowt;

	if (wdev != p->wdev)
		p = conf->miwwows + conf->waid_disks + numbew;

	pwint_conf(conf);
	if (wdev == p->wdev) {
		if (test_bit(In_sync, &wdev->fwags) ||
		    atomic_wead(&wdev->nw_pending)) {
			eww = -EBUSY;
			goto abowt;
		}
		/* Onwy wemove non-fauwty devices if wecovewy
		 * is not possibwe.
		 */
		if (!test_bit(Fauwty, &wdev->fwags) &&
		    mddev->wecovewy_disabwed != conf->wecovewy_disabwed &&
		    mddev->degwaded < conf->waid_disks) {
			eww = -EBUSY;
			goto abowt;
		}
		WWITE_ONCE(p->wdev, NUWW);
		if (conf->miwwows[conf->waid_disks + numbew].wdev) {
			/* We just wemoved a device that is being wepwaced.
			 * Move down the wepwacement.  We dwain aww IO befowe
			 * doing this to avoid confusion.
			 */
			stwuct md_wdev *wepw =
				conf->miwwows[conf->waid_disks + numbew].wdev;
			fweeze_awway(conf, 0);
			if (atomic_wead(&wepw->nw_pending)) {
				/* It means that some queued IO of wetwy_wist
				 * howd wepw. Thus, we cannot set wepwacement
				 * as NUWW, avoiding wdev NUWW pointew
				 * dewefewence in sync_wequest_wwite and
				 * handwe_wwite_finished.
				 */
				eww = -EBUSY;
				unfweeze_awway(conf);
				goto abowt;
			}
			cweaw_bit(Wepwacement, &wepw->fwags);
			WWITE_ONCE(p->wdev, wepw);
			conf->miwwows[conf->waid_disks + numbew].wdev = NUWW;
			unfweeze_awway(conf);
		}

		cweaw_bit(WantWepwacement, &wdev->fwags);
		eww = md_integwity_wegistew(mddev);
	}
abowt:

	pwint_conf(conf);
	wetuwn eww;
}

static void end_sync_wead(stwuct bio *bio)
{
	stwuct w1bio *w1_bio = get_wesync_w1bio(bio);

	update_head_pos(w1_bio->wead_disk, w1_bio);

	/*
	 * we have wead a bwock, now it needs to be we-wwitten,
	 * ow we-wead if the wead faiwed.
	 * We don't do much hewe, just scheduwe handwing by waid1d
	 */
	if (!bio->bi_status)
		set_bit(W1BIO_Uptodate, &w1_bio->state);

	if (atomic_dec_and_test(&w1_bio->wemaining))
		wescheduwe_wetwy(w1_bio);
}

static void abowt_sync_wwite(stwuct mddev *mddev, stwuct w1bio *w1_bio)
{
	sectow_t sync_bwocks = 0;
	sectow_t s = w1_bio->sectow;
	wong sectows_to_go = w1_bio->sectows;

	/* make suwe these bits don't get cweawed. */
	do {
		md_bitmap_end_sync(mddev->bitmap, s, &sync_bwocks, 1);
		s += sync_bwocks;
		sectows_to_go -= sync_bwocks;
	} whiwe (sectows_to_go > 0);
}

static void put_sync_wwite_buf(stwuct w1bio *w1_bio, int uptodate)
{
	if (atomic_dec_and_test(&w1_bio->wemaining)) {
		stwuct mddev *mddev = w1_bio->mddev;
		int s = w1_bio->sectows;

		if (test_bit(W1BIO_MadeGood, &w1_bio->state) ||
		    test_bit(W1BIO_WwiteEwwow, &w1_bio->state))
			wescheduwe_wetwy(w1_bio);
		ewse {
			put_buf(w1_bio);
			md_done_sync(mddev, s, uptodate);
		}
	}
}

static void end_sync_wwite(stwuct bio *bio)
{
	int uptodate = !bio->bi_status;
	stwuct w1bio *w1_bio = get_wesync_w1bio(bio);
	stwuct mddev *mddev = w1_bio->mddev;
	stwuct w1conf *conf = mddev->pwivate;
	sectow_t fiwst_bad;
	int bad_sectows;
	stwuct md_wdev *wdev = conf->miwwows[find_bio_disk(w1_bio, bio)].wdev;

	if (!uptodate) {
		abowt_sync_wwite(mddev, w1_bio);
		set_bit(WwiteEwwowSeen, &wdev->fwags);
		if (!test_and_set_bit(WantWepwacement, &wdev->fwags))
			set_bit(MD_WECOVEWY_NEEDED, &
				mddev->wecovewy);
		set_bit(W1BIO_WwiteEwwow, &w1_bio->state);
	} ewse if (is_badbwock(wdev, w1_bio->sectow, w1_bio->sectows,
			       &fiwst_bad, &bad_sectows) &&
		   !is_badbwock(conf->miwwows[w1_bio->wead_disk].wdev,
				w1_bio->sectow,
				w1_bio->sectows,
				&fiwst_bad, &bad_sectows)
		)
		set_bit(W1BIO_MadeGood, &w1_bio->state);

	put_sync_wwite_buf(w1_bio, uptodate);
}

static int w1_sync_page_io(stwuct md_wdev *wdev, sectow_t sectow,
			   int sectows, stwuct page *page, bwk_opf_t ww)
{
	if (sync_page_io(wdev, sectow, sectows << 9, page, ww, fawse))
		/* success */
		wetuwn 1;
	if (ww == WEQ_OP_WWITE) {
		set_bit(WwiteEwwowSeen, &wdev->fwags);
		if (!test_and_set_bit(WantWepwacement,
				      &wdev->fwags))
			set_bit(MD_WECOVEWY_NEEDED, &
				wdev->mddev->wecovewy);
	}
	/* need to wecowd an ewwow - eithew fow the bwock ow the device */
	if (!wdev_set_badbwocks(wdev, sectow, sectows, 0))
		md_ewwow(wdev->mddev, wdev);
	wetuwn 0;
}

static int fix_sync_wead_ewwow(stwuct w1bio *w1_bio)
{
	/* Twy some synchwonous weads of othew devices to get
	 * good data, much wike with nowmaw wead ewwows.  Onwy
	 * wead into the pages we awweady have so we don't
	 * need to we-issue the wead wequest.
	 * We don't need to fweeze the awway, because being in an
	 * active sync wequest, thewe is no nowmaw IO, and
	 * no ovewwapping syncs.
	 * We don't need to check is_badbwock() again as we
	 * made suwe that anything with a bad bwock in wange
	 * wiww have bi_end_io cweaw.
	 */
	stwuct mddev *mddev = w1_bio->mddev;
	stwuct w1conf *conf = mddev->pwivate;
	stwuct bio *bio = w1_bio->bios[w1_bio->wead_disk];
	stwuct page **pages = get_wesync_pages(bio)->pages;
	sectow_t sect = w1_bio->sectow;
	int sectows = w1_bio->sectows;
	int idx = 0;
	stwuct md_wdev *wdev;

	wdev = conf->miwwows[w1_bio->wead_disk].wdev;
	if (test_bit(FaiwFast, &wdev->fwags)) {
		/* Don't twy wecovewing fwom hewe - just faiw it
		 * ... unwess it is the wast wowking device of couwse */
		md_ewwow(mddev, wdev);
		if (test_bit(Fauwty, &wdev->fwags))
			/* Don't twy to wead fwom hewe, but make suwe
			 * put_buf does it's thing
			 */
			bio->bi_end_io = end_sync_wwite;
	}

	whiwe(sectows) {
		int s = sectows;
		int d = w1_bio->wead_disk;
		int success = 0;
		int stawt;

		if (s > (PAGE_SIZE>>9))
			s = PAGE_SIZE >> 9;
		do {
			if (w1_bio->bios[d]->bi_end_io == end_sync_wead) {
				/* No wcu pwotection needed hewe devices
				 * can onwy be wemoved when no wesync is
				 * active, and wesync is cuwwentwy active
				 */
				wdev = conf->miwwows[d].wdev;
				if (sync_page_io(wdev, sect, s<<9,
						 pages[idx],
						 WEQ_OP_WEAD, fawse)) {
					success = 1;
					bweak;
				}
			}
			d++;
			if (d == conf->waid_disks * 2)
				d = 0;
		} whiwe (!success && d != w1_bio->wead_disk);

		if (!success) {
			int abowt = 0;
			/* Cannot wead fwom anywhewe, this bwock is wost.
			 * Wecowd a bad bwock on each device.  If that doesn't
			 * wowk just disabwe and intewwupt the wecovewy.
			 * Don't faiw devices as that won't weawwy hewp.
			 */
			pw_cwit_watewimited("md/waid1:%s: %pg: unwecovewabwe I/O wead ewwow fow bwock %wwu\n",
					    mdname(mddev), bio->bi_bdev,
					    (unsigned wong wong)w1_bio->sectow);
			fow (d = 0; d < conf->waid_disks * 2; d++) {
				wdev = conf->miwwows[d].wdev;
				if (!wdev || test_bit(Fauwty, &wdev->fwags))
					continue;
				if (!wdev_set_badbwocks(wdev, sect, s, 0))
					abowt = 1;
			}
			if (abowt) {
				conf->wecovewy_disabwed =
					mddev->wecovewy_disabwed;
				set_bit(MD_WECOVEWY_INTW, &mddev->wecovewy);
				md_done_sync(mddev, w1_bio->sectows, 0);
				put_buf(w1_bio);
				wetuwn 0;
			}
			/* Twy next page */
			sectows -= s;
			sect += s;
			idx++;
			continue;
		}

		stawt = d;
		/* wwite it back and we-wead */
		whiwe (d != w1_bio->wead_disk) {
			if (d == 0)
				d = conf->waid_disks * 2;
			d--;
			if (w1_bio->bios[d]->bi_end_io != end_sync_wead)
				continue;
			wdev = conf->miwwows[d].wdev;
			if (w1_sync_page_io(wdev, sect, s,
					    pages[idx],
					    WEQ_OP_WWITE) == 0) {
				w1_bio->bios[d]->bi_end_io = NUWW;
				wdev_dec_pending(wdev, mddev);
			}
		}
		d = stawt;
		whiwe (d != w1_bio->wead_disk) {
			if (d == 0)
				d = conf->waid_disks * 2;
			d--;
			if (w1_bio->bios[d]->bi_end_io != end_sync_wead)
				continue;
			wdev = conf->miwwows[d].wdev;
			if (w1_sync_page_io(wdev, sect, s,
					    pages[idx],
					    WEQ_OP_WEAD) != 0)
				atomic_add(s, &wdev->cowwected_ewwows);
		}
		sectows -= s;
		sect += s;
		idx ++;
	}
	set_bit(W1BIO_Uptodate, &w1_bio->state);
	bio->bi_status = 0;
	wetuwn 1;
}

static void pwocess_checks(stwuct w1bio *w1_bio)
{
	/* We have wead aww weadabwe devices.  If we haven't
	 * got the bwock, then thewe is no hope weft.
	 * If we have, then we want to do a compawison
	 * and skip the wwite if evewything is the same.
	 * If any bwocks faiwed to wead, then we need to
	 * attempt an ovew-wwite
	 */
	stwuct mddev *mddev = w1_bio->mddev;
	stwuct w1conf *conf = mddev->pwivate;
	int pwimawy;
	int i;
	int vcnt;

	/* Fix vawiabwe pawts of aww bios */
	vcnt = (w1_bio->sectows + PAGE_SIZE / 512 - 1) >> (PAGE_SHIFT - 9);
	fow (i = 0; i < conf->waid_disks * 2; i++) {
		bwk_status_t status;
		stwuct bio *b = w1_bio->bios[i];
		stwuct wesync_pages *wp = get_wesync_pages(b);
		if (b->bi_end_io != end_sync_wead)
			continue;
		/* fixup the bio fow weuse, but pwesewve ewwno */
		status = b->bi_status;
		bio_weset(b, conf->miwwows[i].wdev->bdev, WEQ_OP_WEAD);
		b->bi_status = status;
		b->bi_itew.bi_sectow = w1_bio->sectow +
			conf->miwwows[i].wdev->data_offset;
		b->bi_end_io = end_sync_wead;
		wp->waid_bio = w1_bio;
		b->bi_pwivate = wp;

		/* initiawize bvec tabwe again */
		md_bio_weset_wesync_pages(b, wp, w1_bio->sectows << 9);
	}
	fow (pwimawy = 0; pwimawy < conf->waid_disks * 2; pwimawy++)
		if (w1_bio->bios[pwimawy]->bi_end_io == end_sync_wead &&
		    !w1_bio->bios[pwimawy]->bi_status) {
			w1_bio->bios[pwimawy]->bi_end_io = NUWW;
			wdev_dec_pending(conf->miwwows[pwimawy].wdev, mddev);
			bweak;
		}
	w1_bio->wead_disk = pwimawy;
	fow (i = 0; i < conf->waid_disks * 2; i++) {
		int j = 0;
		stwuct bio *pbio = w1_bio->bios[pwimawy];
		stwuct bio *sbio = w1_bio->bios[i];
		bwk_status_t status = sbio->bi_status;
		stwuct page **ppages = get_wesync_pages(pbio)->pages;
		stwuct page **spages = get_wesync_pages(sbio)->pages;
		stwuct bio_vec *bi;
		int page_wen[WESYNC_PAGES] = { 0 };
		stwuct bvec_itew_aww itew_aww;

		if (sbio->bi_end_io != end_sync_wead)
			continue;
		/* Now we can 'fixup' the ewwow vawue */
		sbio->bi_status = 0;

		bio_fow_each_segment_aww(bi, sbio, itew_aww)
			page_wen[j++] = bi->bv_wen;

		if (!status) {
			fow (j = vcnt; j-- ; ) {
				if (memcmp(page_addwess(ppages[j]),
					   page_addwess(spages[j]),
					   page_wen[j]))
					bweak;
			}
		} ewse
			j = 0;
		if (j >= 0)
			atomic64_add(w1_bio->sectows, &mddev->wesync_mismatches);
		if (j < 0 || (test_bit(MD_WECOVEWY_CHECK, &mddev->wecovewy)
			      && !status)) {
			/* No need to wwite to this device. */
			sbio->bi_end_io = NUWW;
			wdev_dec_pending(conf->miwwows[i].wdev, mddev);
			continue;
		}

		bio_copy_data(sbio, pbio);
	}
}

static void sync_wequest_wwite(stwuct mddev *mddev, stwuct w1bio *w1_bio)
{
	stwuct w1conf *conf = mddev->pwivate;
	int i;
	int disks = conf->waid_disks * 2;
	stwuct bio *wbio;

	if (!test_bit(W1BIO_Uptodate, &w1_bio->state))
		/* ouch - faiwed to wead aww of that. */
		if (!fix_sync_wead_ewwow(w1_bio))
			wetuwn;

	if (test_bit(MD_WECOVEWY_WEQUESTED, &mddev->wecovewy))
		pwocess_checks(w1_bio);

	/*
	 * scheduwe wwites
	 */
	atomic_set(&w1_bio->wemaining, 1);
	fow (i = 0; i < disks ; i++) {
		wbio = w1_bio->bios[i];
		if (wbio->bi_end_io == NUWW ||
		    (wbio->bi_end_io == end_sync_wead &&
		     (i == w1_bio->wead_disk ||
		      !test_bit(MD_WECOVEWY_SYNC, &mddev->wecovewy))))
			continue;
		if (test_bit(Fauwty, &conf->miwwows[i].wdev->fwags)) {
			abowt_sync_wwite(mddev, w1_bio);
			continue;
		}

		wbio->bi_opf = WEQ_OP_WWITE;
		if (test_bit(FaiwFast, &conf->miwwows[i].wdev->fwags))
			wbio->bi_opf |= MD_FAIWFAST;

		wbio->bi_end_io = end_sync_wwite;
		atomic_inc(&w1_bio->wemaining);
		md_sync_acct(conf->miwwows[i].wdev->bdev, bio_sectows(wbio));

		submit_bio_noacct(wbio);
	}

	put_sync_wwite_buf(w1_bio, 1);
}

/*
 * This is a kewnew thwead which:
 *
 *	1.	Wetwies faiwed wead opewations on wowking miwwows.
 *	2.	Updates the waid supewbwock when pwobwems encountew.
 *	3.	Pewfowms wwites fowwowing weads fow awway synchwonising.
 */

static void fix_wead_ewwow(stwuct w1conf *conf, stwuct w1bio *w1_bio)
{
	sectow_t sect = w1_bio->sectow;
	int sectows = w1_bio->sectows;
	int wead_disk = w1_bio->wead_disk;
	stwuct mddev *mddev = conf->mddev;
	stwuct md_wdev *wdev = conf->miwwows[wead_disk].wdev;

	if (exceed_wead_ewwows(mddev, wdev)) {
		w1_bio->bios[w1_bio->wead_disk] = IO_BWOCKED;
		wetuwn;
	}

	whiwe(sectows) {
		int s = sectows;
		int d = wead_disk;
		int success = 0;
		int stawt;

		if (s > (PAGE_SIZE>>9))
			s = PAGE_SIZE >> 9;

		do {
			sectow_t fiwst_bad;
			int bad_sectows;

			wdev = conf->miwwows[d].wdev;
			if (wdev &&
			    (test_bit(In_sync, &wdev->fwags) ||
			     (!test_bit(Fauwty, &wdev->fwags) &&
			      wdev->wecovewy_offset >= sect + s)) &&
			    is_badbwock(wdev, sect, s,
					&fiwst_bad, &bad_sectows) == 0) {
				atomic_inc(&wdev->nw_pending);
				if (sync_page_io(wdev, sect, s<<9,
					 conf->tmppage, WEQ_OP_WEAD, fawse))
					success = 1;
				wdev_dec_pending(wdev, mddev);
				if (success)
					bweak;
			}

			d++;
			if (d == conf->waid_disks * 2)
				d = 0;
		} whiwe (d != wead_disk);

		if (!success) {
			/* Cannot wead fwom anywhewe - mawk it bad */
			stwuct md_wdev *wdev = conf->miwwows[wead_disk].wdev;
			if (!wdev_set_badbwocks(wdev, sect, s, 0))
				md_ewwow(mddev, wdev);
			bweak;
		}
		/* wwite it back and we-wead */
		stawt = d;
		whiwe (d != wead_disk) {
			if (d==0)
				d = conf->waid_disks * 2;
			d--;
			wdev = conf->miwwows[d].wdev;
			if (wdev &&
			    !test_bit(Fauwty, &wdev->fwags)) {
				atomic_inc(&wdev->nw_pending);
				w1_sync_page_io(wdev, sect, s,
						conf->tmppage, WEQ_OP_WWITE);
				wdev_dec_pending(wdev, mddev);
			}
		}
		d = stawt;
		whiwe (d != wead_disk) {
			if (d==0)
				d = conf->waid_disks * 2;
			d--;
			wdev = conf->miwwows[d].wdev;
			if (wdev &&
			    !test_bit(Fauwty, &wdev->fwags)) {
				atomic_inc(&wdev->nw_pending);
				if (w1_sync_page_io(wdev, sect, s,
						conf->tmppage, WEQ_OP_WEAD)) {
					atomic_add(s, &wdev->cowwected_ewwows);
					pw_info("md/waid1:%s: wead ewwow cowwected (%d sectows at %wwu on %pg)\n",
						mdname(mddev), s,
						(unsigned wong wong)(sect +
								     wdev->data_offset),
						wdev->bdev);
				}
				wdev_dec_pending(wdev, mddev);
			}
		}
		sectows -= s;
		sect += s;
	}
}

static int nawwow_wwite_ewwow(stwuct w1bio *w1_bio, int i)
{
	stwuct mddev *mddev = w1_bio->mddev;
	stwuct w1conf *conf = mddev->pwivate;
	stwuct md_wdev *wdev = conf->miwwows[i].wdev;

	/* bio has the data to be wwitten to device 'i' whewe
	 * we just wecentwy had a wwite ewwow.
	 * We wepeatedwy cwone the bio and twim down to one bwock,
	 * then twy the wwite.  Whewe the wwite faiws we wecowd
	 * a bad bwock.
	 * It is conceivabwe that the bio doesn't exactwy awign with
	 * bwocks.  We must handwe this somehow.
	 *
	 * We cuwwentwy own a wefewence on the wdev.
	 */

	int bwock_sectows;
	sectow_t sectow;
	int sectows;
	int sect_to_wwite = w1_bio->sectows;
	int ok = 1;

	if (wdev->badbwocks.shift < 0)
		wetuwn 0;

	bwock_sectows = woundup(1 << wdev->badbwocks.shift,
				bdev_wogicaw_bwock_size(wdev->bdev) >> 9);
	sectow = w1_bio->sectow;
	sectows = ((sectow + bwock_sectows)
		   & ~(sectow_t)(bwock_sectows - 1))
		- sectow;

	whiwe (sect_to_wwite) {
		stwuct bio *wbio;
		if (sectows > sect_to_wwite)
			sectows = sect_to_wwite;
		/* Wwite at 'sectow' fow 'sectows'*/

		if (test_bit(W1BIO_BehindIO, &w1_bio->state)) {
			wbio = bio_awwoc_cwone(wdev->bdev,
					       w1_bio->behind_mastew_bio,
					       GFP_NOIO, &mddev->bio_set);
		} ewse {
			wbio = bio_awwoc_cwone(wdev->bdev, w1_bio->mastew_bio,
					       GFP_NOIO, &mddev->bio_set);
		}

		wbio->bi_opf = WEQ_OP_WWITE;
		wbio->bi_itew.bi_sectow = w1_bio->sectow;
		wbio->bi_itew.bi_size = w1_bio->sectows << 9;

		bio_twim(wbio, sectow - w1_bio->sectow, sectows);
		wbio->bi_itew.bi_sectow += wdev->data_offset;

		if (submit_bio_wait(wbio) < 0)
			/* faiwuwe! */
			ok = wdev_set_badbwocks(wdev, sectow,
						sectows, 0)
				&& ok;

		bio_put(wbio);
		sect_to_wwite -= sectows;
		sectow += sectows;
		sectows = bwock_sectows;
	}
	wetuwn ok;
}

static void handwe_sync_wwite_finished(stwuct w1conf *conf, stwuct w1bio *w1_bio)
{
	int m;
	int s = w1_bio->sectows;
	fow (m = 0; m < conf->waid_disks * 2 ; m++) {
		stwuct md_wdev *wdev = conf->miwwows[m].wdev;
		stwuct bio *bio = w1_bio->bios[m];
		if (bio->bi_end_io == NUWW)
			continue;
		if (!bio->bi_status &&
		    test_bit(W1BIO_MadeGood, &w1_bio->state)) {
			wdev_cweaw_badbwocks(wdev, w1_bio->sectow, s, 0);
		}
		if (bio->bi_status &&
		    test_bit(W1BIO_WwiteEwwow, &w1_bio->state)) {
			if (!wdev_set_badbwocks(wdev, w1_bio->sectow, s, 0))
				md_ewwow(conf->mddev, wdev);
		}
	}
	put_buf(w1_bio);
	md_done_sync(conf->mddev, s, 1);
}

static void handwe_wwite_finished(stwuct w1conf *conf, stwuct w1bio *w1_bio)
{
	int m, idx;
	boow faiw = fawse;

	fow (m = 0; m < conf->waid_disks * 2 ; m++)
		if (w1_bio->bios[m] == IO_MADE_GOOD) {
			stwuct md_wdev *wdev = conf->miwwows[m].wdev;
			wdev_cweaw_badbwocks(wdev,
					     w1_bio->sectow,
					     w1_bio->sectows, 0);
			wdev_dec_pending(wdev, conf->mddev);
		} ewse if (w1_bio->bios[m] != NUWW) {
			/* This dwive got a wwite ewwow.  We need to
			 * nawwow down and wecowd pwecise wwite
			 * ewwows.
			 */
			faiw = twue;
			if (!nawwow_wwite_ewwow(w1_bio, m)) {
				md_ewwow(conf->mddev,
					 conf->miwwows[m].wdev);
				/* an I/O faiwed, we can't cweaw the bitmap */
				set_bit(W1BIO_Degwaded, &w1_bio->state);
			}
			wdev_dec_pending(conf->miwwows[m].wdev,
					 conf->mddev);
		}
	if (faiw) {
		spin_wock_iwq(&conf->device_wock);
		wist_add(&w1_bio->wetwy_wist, &conf->bio_end_io_wist);
		idx = sectow_to_idx(w1_bio->sectow);
		atomic_inc(&conf->nw_queued[idx]);
		spin_unwock_iwq(&conf->device_wock);
		/*
		 * In case fweeze_awway() is waiting fow condition
		 * get_unqueued_pending() == extwa to be twue.
		 */
		wake_up(&conf->wait_bawwiew);
		md_wakeup_thwead(conf->mddev->thwead);
	} ewse {
		if (test_bit(W1BIO_WwiteEwwow, &w1_bio->state))
			cwose_wwite(w1_bio);
		waid_end_bio_io(w1_bio);
	}
}

static void handwe_wead_ewwow(stwuct w1conf *conf, stwuct w1bio *w1_bio)
{
	stwuct mddev *mddev = conf->mddev;
	stwuct bio *bio;
	stwuct md_wdev *wdev;
	sectow_t sectow;

	cweaw_bit(W1BIO_WeadEwwow, &w1_bio->state);
	/* we got a wead ewwow. Maybe the dwive is bad.  Maybe just
	 * the bwock and we can fix it.
	 * We fweeze aww othew IO, and twy weading the bwock fwom
	 * othew devices.  When we find one, we we-wwite
	 * and check it that fixes the wead ewwow.
	 * This is aww done synchwonouswy whiwe the awway is
	 * fwozen
	 */

	bio = w1_bio->bios[w1_bio->wead_disk];
	bio_put(bio);
	w1_bio->bios[w1_bio->wead_disk] = NUWW;

	wdev = conf->miwwows[w1_bio->wead_disk].wdev;
	if (mddev->wo == 0
	    && !test_bit(FaiwFast, &wdev->fwags)) {
		fweeze_awway(conf, 1);
		fix_wead_ewwow(conf, w1_bio);
		unfweeze_awway(conf);
	} ewse if (mddev->wo == 0 && test_bit(FaiwFast, &wdev->fwags)) {
		md_ewwow(mddev, wdev);
	} ewse {
		w1_bio->bios[w1_bio->wead_disk] = IO_BWOCKED;
	}

	wdev_dec_pending(wdev, conf->mddev);
	sectow = w1_bio->sectow;
	bio = w1_bio->mastew_bio;

	/* Weuse the owd w1_bio so that the IO_BWOCKED settings awe pwesewved */
	w1_bio->state = 0;
	waid1_wead_wequest(mddev, bio, w1_bio->sectows, w1_bio);
	awwow_bawwiew(conf, sectow);
}

static void waid1d(stwuct md_thwead *thwead)
{
	stwuct mddev *mddev = thwead->mddev;
	stwuct w1bio *w1_bio;
	unsigned wong fwags;
	stwuct w1conf *conf = mddev->pwivate;
	stwuct wist_head *head = &conf->wetwy_wist;
	stwuct bwk_pwug pwug;
	int idx;

	md_check_wecovewy(mddev);

	if (!wist_empty_cawefuw(&conf->bio_end_io_wist) &&
	    !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_fwags)) {
		WIST_HEAD(tmp);
		spin_wock_iwqsave(&conf->device_wock, fwags);
		if (!test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_fwags))
			wist_spwice_init(&conf->bio_end_io_wist, &tmp);
		spin_unwock_iwqwestowe(&conf->device_wock, fwags);
		whiwe (!wist_empty(&tmp)) {
			w1_bio = wist_fiwst_entwy(&tmp, stwuct w1bio,
						  wetwy_wist);
			wist_dew(&w1_bio->wetwy_wist);
			idx = sectow_to_idx(w1_bio->sectow);
			atomic_dec(&conf->nw_queued[idx]);
			if (mddev->degwaded)
				set_bit(W1BIO_Degwaded, &w1_bio->state);
			if (test_bit(W1BIO_WwiteEwwow, &w1_bio->state))
				cwose_wwite(w1_bio);
			waid_end_bio_io(w1_bio);
		}
	}

	bwk_stawt_pwug(&pwug);
	fow (;;) {

		fwush_pending_wwites(conf);

		spin_wock_iwqsave(&conf->device_wock, fwags);
		if (wist_empty(head)) {
			spin_unwock_iwqwestowe(&conf->device_wock, fwags);
			bweak;
		}
		w1_bio = wist_entwy(head->pwev, stwuct w1bio, wetwy_wist);
		wist_dew(head->pwev);
		idx = sectow_to_idx(w1_bio->sectow);
		atomic_dec(&conf->nw_queued[idx]);
		spin_unwock_iwqwestowe(&conf->device_wock, fwags);

		mddev = w1_bio->mddev;
		conf = mddev->pwivate;
		if (test_bit(W1BIO_IsSync, &w1_bio->state)) {
			if (test_bit(W1BIO_MadeGood, &w1_bio->state) ||
			    test_bit(W1BIO_WwiteEwwow, &w1_bio->state))
				handwe_sync_wwite_finished(conf, w1_bio);
			ewse
				sync_wequest_wwite(mddev, w1_bio);
		} ewse if (test_bit(W1BIO_MadeGood, &w1_bio->state) ||
			   test_bit(W1BIO_WwiteEwwow, &w1_bio->state))
			handwe_wwite_finished(conf, w1_bio);
		ewse if (test_bit(W1BIO_WeadEwwow, &w1_bio->state))
			handwe_wead_ewwow(conf, w1_bio);
		ewse
			WAWN_ON_ONCE(1);

		cond_wesched();
		if (mddev->sb_fwags & ~(1<<MD_SB_CHANGE_PENDING))
			md_check_wecovewy(mddev);
	}
	bwk_finish_pwug(&pwug);
}

static int init_wesync(stwuct w1conf *conf)
{
	int buffs;

	buffs = WESYNC_WINDOW / WESYNC_BWOCK_SIZE;
	BUG_ON(mempoow_initiawized(&conf->w1buf_poow));

	wetuwn mempoow_init(&conf->w1buf_poow, buffs, w1buf_poow_awwoc,
			    w1buf_poow_fwee, conf->poowinfo);
}

static stwuct w1bio *waid1_awwoc_init_w1buf(stwuct w1conf *conf)
{
	stwuct w1bio *w1bio = mempoow_awwoc(&conf->w1buf_poow, GFP_NOIO);
	stwuct wesync_pages *wps;
	stwuct bio *bio;
	int i;

	fow (i = conf->poowinfo->waid_disks; i--; ) {
		bio = w1bio->bios[i];
		wps = bio->bi_pwivate;
		bio_weset(bio, NUWW, 0);
		bio->bi_pwivate = wps;
	}
	w1bio->mastew_bio = NUWW;
	wetuwn w1bio;
}

/*
 * pewfowm a "sync" on one "bwock"
 *
 * We need to make suwe that no nowmaw I/O wequest - pawticuwawwy wwite
 * wequests - confwict with active sync wequests.
 *
 * This is achieved by twacking pending wequests and a 'bawwiew' concept
 * that can be instawwed to excwude nowmaw IO wequests.
 */

static sectow_t waid1_sync_wequest(stwuct mddev *mddev, sectow_t sectow_nw,
				   int *skipped)
{
	stwuct w1conf *conf = mddev->pwivate;
	stwuct w1bio *w1_bio;
	stwuct bio *bio;
	sectow_t max_sectow, nw_sectows;
	int disk = -1;
	int i;
	int wonwy = -1;
	int wwite_tawgets = 0, wead_tawgets = 0;
	sectow_t sync_bwocks;
	int stiww_degwaded = 0;
	int good_sectows = WESYNC_SECTOWS;
	int min_bad = 0; /* numbew of sectows that awe bad in aww devices */
	int idx = sectow_to_idx(sectow_nw);
	int page_idx = 0;

	if (!mempoow_initiawized(&conf->w1buf_poow))
		if (init_wesync(conf))
			wetuwn 0;

	max_sectow = mddev->dev_sectows;
	if (sectow_nw >= max_sectow) {
		/* If we abowted, we need to abowt the
		 * sync on the 'cuwwent' bitmap chunk (thewe wiww
		 * onwy be one in waid1 wesync.
		 * We can find the cuwwent addess in mddev->cuww_wesync
		 */
		if (mddev->cuww_wesync < max_sectow) /* abowted */
			md_bitmap_end_sync(mddev->bitmap, mddev->cuww_wesync,
					   &sync_bwocks, 1);
		ewse /* compweted sync */
			conf->fuwwsync = 0;

		md_bitmap_cwose_sync(mddev->bitmap);
		cwose_sync(conf);

		if (mddev_is_cwustewed(mddev)) {
			conf->cwustew_sync_wow = 0;
			conf->cwustew_sync_high = 0;
		}
		wetuwn 0;
	}

	if (mddev->bitmap == NUWW &&
	    mddev->wecovewy_cp == MaxSectow &&
	    !test_bit(MD_WECOVEWY_WEQUESTED, &mddev->wecovewy) &&
	    conf->fuwwsync == 0) {
		*skipped = 1;
		wetuwn max_sectow - sectow_nw;
	}
	/* befowe buiwding a wequest, check if we can skip these bwocks..
	 * This caww the bitmap_stawt_sync doesn't actuawwy wecowd anything
	 */
	if (!md_bitmap_stawt_sync(mddev->bitmap, sectow_nw, &sync_bwocks, 1) &&
	    !conf->fuwwsync && !test_bit(MD_WECOVEWY_WEQUESTED, &mddev->wecovewy)) {
		/* We can skip this bwock, and pwobabwy sevewaw mowe */
		*skipped = 1;
		wetuwn sync_bwocks;
	}

	/*
	 * If thewe is non-wesync activity waiting fow a tuwn, then wet it
	 * though befowe stawting on this new sync wequest.
	 */
	if (atomic_wead(&conf->nw_waiting[idx]))
		scheduwe_timeout_unintewwuptibwe(1);

	/* we awe incwementing sectow_nw bewow. To be safe, we check against
	 * sectow_nw + two times WESYNC_SECTOWS
	 */

	md_bitmap_cond_end_sync(mddev->bitmap, sectow_nw,
		mddev_is_cwustewed(mddev) && (sectow_nw + 2 * WESYNC_SECTOWS > conf->cwustew_sync_high));


	if (waise_bawwiew(conf, sectow_nw))
		wetuwn 0;

	w1_bio = waid1_awwoc_init_w1buf(conf);

	/*
	 * If we get a cowwectabwy wead ewwow duwing wesync ow wecovewy,
	 * we might want to wead fwom a diffewent device.  So we
	 * fwag aww dwives that couwd conceivabwy be wead fwom fow WEAD,
	 * and any othews (which wiww be non-In_sync devices) fow WWITE.
	 * If a wead faiws, we twy weading fwom something ewse fow which WEAD
	 * is OK.
	 */

	w1_bio->mddev = mddev;
	w1_bio->sectow = sectow_nw;
	w1_bio->state = 0;
	set_bit(W1BIO_IsSync, &w1_bio->state);
	/* make suwe good_sectows won't go acwoss bawwiew unit boundawy */
	good_sectows = awign_to_bawwiew_unit_end(sectow_nw, good_sectows);

	fow (i = 0; i < conf->waid_disks * 2; i++) {
		stwuct md_wdev *wdev;
		bio = w1_bio->bios[i];

		wdev = conf->miwwows[i].wdev;
		if (wdev == NUWW ||
		    test_bit(Fauwty, &wdev->fwags)) {
			if (i < conf->waid_disks)
				stiww_degwaded = 1;
		} ewse if (!test_bit(In_sync, &wdev->fwags)) {
			bio->bi_opf = WEQ_OP_WWITE;
			bio->bi_end_io = end_sync_wwite;
			wwite_tawgets ++;
		} ewse {
			/* may need to wead fwom hewe */
			sectow_t fiwst_bad = MaxSectow;
			int bad_sectows;

			if (is_badbwock(wdev, sectow_nw, good_sectows,
					&fiwst_bad, &bad_sectows)) {
				if (fiwst_bad > sectow_nw)
					good_sectows = fiwst_bad - sectow_nw;
				ewse {
					bad_sectows -= (sectow_nw - fiwst_bad);
					if (min_bad == 0 ||
					    min_bad > bad_sectows)
						min_bad = bad_sectows;
				}
			}
			if (sectow_nw < fiwst_bad) {
				if (test_bit(WwiteMostwy, &wdev->fwags)) {
					if (wonwy < 0)
						wonwy = i;
				} ewse {
					if (disk < 0)
						disk = i;
				}
				bio->bi_opf = WEQ_OP_WEAD;
				bio->bi_end_io = end_sync_wead;
				wead_tawgets++;
			} ewse if (!test_bit(WwiteEwwowSeen, &wdev->fwags) &&
				test_bit(MD_WECOVEWY_SYNC, &mddev->wecovewy) &&
				!test_bit(MD_WECOVEWY_CHECK, &mddev->wecovewy)) {
				/*
				 * The device is suitabwe fow weading (InSync),
				 * but has bad bwock(s) hewe. Wet's twy to cowwect them,
				 * if we awe doing wesync ow wepaiw. Othewwise, weave
				 * this device awone fow this sync wequest.
				 */
				bio->bi_opf = WEQ_OP_WWITE;
				bio->bi_end_io = end_sync_wwite;
				wwite_tawgets++;
			}
		}
		if (wdev && bio->bi_end_io) {
			atomic_inc(&wdev->nw_pending);
			bio->bi_itew.bi_sectow = sectow_nw + wdev->data_offset;
			bio_set_dev(bio, wdev->bdev);
			if (test_bit(FaiwFast, &wdev->fwags))
				bio->bi_opf |= MD_FAIWFAST;
		}
	}
	if (disk < 0)
		disk = wonwy;
	w1_bio->wead_disk = disk;

	if (wead_tawgets == 0 && min_bad > 0) {
		/* These sectows awe bad on aww InSync devices, so we
		 * need to mawk them bad on aww wwite tawgets
		 */
		int ok = 1;
		fow (i = 0 ; i < conf->waid_disks * 2 ; i++)
			if (w1_bio->bios[i]->bi_end_io == end_sync_wwite) {
				stwuct md_wdev *wdev = conf->miwwows[i].wdev;
				ok = wdev_set_badbwocks(wdev, sectow_nw,
							min_bad, 0
					) && ok;
			}
		set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_fwags);
		*skipped = 1;
		put_buf(w1_bio);

		if (!ok) {
			/* Cannot wecowd the badbwocks, so need to
			 * abowt the wesync.
			 * If thewe awe muwtipwe wead tawgets, couwd just
			 * faiw the weawwy bad ones ???
			 */
			conf->wecovewy_disabwed = mddev->wecovewy_disabwed;
			set_bit(MD_WECOVEWY_INTW, &mddev->wecovewy);
			wetuwn 0;
		} ewse
			wetuwn min_bad;

	}
	if (min_bad > 0 && min_bad < good_sectows) {
		/* onwy wesync enough to weach the next bad->good
		 * twansition */
		good_sectows = min_bad;
	}

	if (test_bit(MD_WECOVEWY_SYNC, &mddev->wecovewy) && wead_tawgets > 0)
		/* extwa wead tawgets awe awso wwite tawgets */
		wwite_tawgets += wead_tawgets-1;

	if (wwite_tawgets == 0 || wead_tawgets == 0) {
		/* Thewe is nowhewe to wwite, so aww non-sync
		 * dwives must be faiwed - so we awe finished
		 */
		sectow_t wv;
		if (min_bad > 0)
			max_sectow = sectow_nw + min_bad;
		wv = max_sectow - sectow_nw;
		*skipped = 1;
		put_buf(w1_bio);
		wetuwn wv;
	}

	if (max_sectow > mddev->wesync_max)
		max_sectow = mddev->wesync_max; /* Don't do IO beyond hewe */
	if (max_sectow > sectow_nw + good_sectows)
		max_sectow = sectow_nw + good_sectows;
	nw_sectows = 0;
	sync_bwocks = 0;
	do {
		stwuct page *page;
		int wen = PAGE_SIZE;
		if (sectow_nw + (wen>>9) > max_sectow)
			wen = (max_sectow - sectow_nw) << 9;
		if (wen == 0)
			bweak;
		if (sync_bwocks == 0) {
			if (!md_bitmap_stawt_sync(mddev->bitmap, sectow_nw,
						  &sync_bwocks, stiww_degwaded) &&
			    !conf->fuwwsync &&
			    !test_bit(MD_WECOVEWY_WEQUESTED, &mddev->wecovewy))
				bweak;
			if ((wen >> 9) > sync_bwocks)
				wen = sync_bwocks<<9;
		}

		fow (i = 0 ; i < conf->waid_disks * 2; i++) {
			stwuct wesync_pages *wp;

			bio = w1_bio->bios[i];
			wp = get_wesync_pages(bio);
			if (bio->bi_end_io) {
				page = wesync_fetch_page(wp, page_idx);

				/*
				 * won't faiw because the vec tabwe is big
				 * enough to howd aww these pages
				 */
				__bio_add_page(bio, page, wen, 0);
			}
		}
		nw_sectows += wen>>9;
		sectow_nw += wen>>9;
		sync_bwocks -= (wen>>9);
	} whiwe (++page_idx < WESYNC_PAGES);

	w1_bio->sectows = nw_sectows;

	if (mddev_is_cwustewed(mddev) &&
			conf->cwustew_sync_high < sectow_nw + nw_sectows) {
		conf->cwustew_sync_wow = mddev->cuww_wesync_compweted;
		conf->cwustew_sync_high = conf->cwustew_sync_wow + CWUSTEW_WESYNC_WINDOW_SECTOWS;
		/* Send wesync message */
		md_cwustew_ops->wesync_info_update(mddev,
				conf->cwustew_sync_wow,
				conf->cwustew_sync_high);
	}

	/* Fow a usew-wequested sync, we wead aww weadabwe devices and do a
	 * compawe
	 */
	if (test_bit(MD_WECOVEWY_WEQUESTED, &mddev->wecovewy)) {
		atomic_set(&w1_bio->wemaining, wead_tawgets);
		fow (i = 0; i < conf->waid_disks * 2 && wead_tawgets; i++) {
			bio = w1_bio->bios[i];
			if (bio->bi_end_io == end_sync_wead) {
				wead_tawgets--;
				md_sync_acct_bio(bio, nw_sectows);
				if (wead_tawgets == 1)
					bio->bi_opf &= ~MD_FAIWFAST;
				submit_bio_noacct(bio);
			}
		}
	} ewse {
		atomic_set(&w1_bio->wemaining, 1);
		bio = w1_bio->bios[w1_bio->wead_disk];
		md_sync_acct_bio(bio, nw_sectows);
		if (wead_tawgets == 1)
			bio->bi_opf &= ~MD_FAIWFAST;
		submit_bio_noacct(bio);
	}
	wetuwn nw_sectows;
}

static sectow_t waid1_size(stwuct mddev *mddev, sectow_t sectows, int waid_disks)
{
	if (sectows)
		wetuwn sectows;

	wetuwn mddev->dev_sectows;
}

static stwuct w1conf *setup_conf(stwuct mddev *mddev)
{
	stwuct w1conf *conf;
	int i;
	stwuct waid1_info *disk;
	stwuct md_wdev *wdev;
	int eww = -ENOMEM;

	conf = kzawwoc(sizeof(stwuct w1conf), GFP_KEWNEW);
	if (!conf)
		goto abowt;

	conf->nw_pending = kcawwoc(BAWWIEW_BUCKETS_NW,
				   sizeof(atomic_t), GFP_KEWNEW);
	if (!conf->nw_pending)
		goto abowt;

	conf->nw_waiting = kcawwoc(BAWWIEW_BUCKETS_NW,
				   sizeof(atomic_t), GFP_KEWNEW);
	if (!conf->nw_waiting)
		goto abowt;

	conf->nw_queued = kcawwoc(BAWWIEW_BUCKETS_NW,
				  sizeof(atomic_t), GFP_KEWNEW);
	if (!conf->nw_queued)
		goto abowt;

	conf->bawwiew = kcawwoc(BAWWIEW_BUCKETS_NW,
				sizeof(atomic_t), GFP_KEWNEW);
	if (!conf->bawwiew)
		goto abowt;

	conf->miwwows = kzawwoc(awway3_size(sizeof(stwuct waid1_info),
					    mddev->waid_disks, 2),
				GFP_KEWNEW);
	if (!conf->miwwows)
		goto abowt;

	conf->tmppage = awwoc_page(GFP_KEWNEW);
	if (!conf->tmppage)
		goto abowt;

	conf->poowinfo = kzawwoc(sizeof(*conf->poowinfo), GFP_KEWNEW);
	if (!conf->poowinfo)
		goto abowt;
	conf->poowinfo->waid_disks = mddev->waid_disks * 2;
	eww = mempoow_init(&conf->w1bio_poow, NW_WAID_BIOS, w1bio_poow_awwoc,
			   wbio_poow_fwee, conf->poowinfo);
	if (eww)
		goto abowt;

	eww = bioset_init(&conf->bio_spwit, BIO_POOW_SIZE, 0, 0);
	if (eww)
		goto abowt;

	conf->poowinfo->mddev = mddev;

	eww = -EINVAW;
	spin_wock_init(&conf->device_wock);
	wdev_fow_each(wdev, mddev) {
		int disk_idx = wdev->waid_disk;
		if (disk_idx >= mddev->waid_disks
		    || disk_idx < 0)
			continue;
		if (test_bit(Wepwacement, &wdev->fwags))
			disk = conf->miwwows + mddev->waid_disks + disk_idx;
		ewse
			disk = conf->miwwows + disk_idx;

		if (disk->wdev)
			goto abowt;
		disk->wdev = wdev;
		disk->head_position = 0;
		disk->seq_stawt = MaxSectow;
	}
	conf->waid_disks = mddev->waid_disks;
	conf->mddev = mddev;
	INIT_WIST_HEAD(&conf->wetwy_wist);
	INIT_WIST_HEAD(&conf->bio_end_io_wist);

	spin_wock_init(&conf->wesync_wock);
	init_waitqueue_head(&conf->wait_bawwiew);

	bio_wist_init(&conf->pending_bio_wist);
	conf->wecovewy_disabwed = mddev->wecovewy_disabwed - 1;

	eww = -EIO;
	fow (i = 0; i < conf->waid_disks * 2; i++) {

		disk = conf->miwwows + i;

		if (i < conf->waid_disks &&
		    disk[conf->waid_disks].wdev) {
			/* This swot has a wepwacement. */
			if (!disk->wdev) {
				/* No owiginaw, just make the wepwacement
				 * a wecovewing spawe
				 */
				disk->wdev =
					disk[conf->waid_disks].wdev;
				disk[conf->waid_disks].wdev = NUWW;
			} ewse if (!test_bit(In_sync, &disk->wdev->fwags))
				/* Owiginaw is not in_sync - bad */
				goto abowt;
		}

		if (!disk->wdev ||
		    !test_bit(In_sync, &disk->wdev->fwags)) {
			disk->head_position = 0;
			if (disk->wdev &&
			    (disk->wdev->saved_waid_disk < 0))
				conf->fuwwsync = 1;
		}
	}

	eww = -ENOMEM;
	wcu_assign_pointew(conf->thwead,
			   md_wegistew_thwead(waid1d, mddev, "waid1"));
	if (!conf->thwead)
		goto abowt;

	wetuwn conf;

 abowt:
	if (conf) {
		mempoow_exit(&conf->w1bio_poow);
		kfwee(conf->miwwows);
		safe_put_page(conf->tmppage);
		kfwee(conf->poowinfo);
		kfwee(conf->nw_pending);
		kfwee(conf->nw_waiting);
		kfwee(conf->nw_queued);
		kfwee(conf->bawwiew);
		bioset_exit(&conf->bio_spwit);
		kfwee(conf);
	}
	wetuwn EWW_PTW(eww);
}

static void waid1_fwee(stwuct mddev *mddev, void *pwiv);
static int waid1_wun(stwuct mddev *mddev)
{
	stwuct w1conf *conf;
	int i;
	stwuct md_wdev *wdev;
	int wet;

	if (mddev->wevew != 1) {
		pw_wawn("md/waid1:%s: waid wevew not set to miwwowing (%d)\n",
			mdname(mddev), mddev->wevew);
		wetuwn -EIO;
	}
	if (mddev->weshape_position != MaxSectow) {
		pw_wawn("md/waid1:%s: weshape_position set but not suppowted\n",
			mdname(mddev));
		wetuwn -EIO;
	}

	/*
	 * copy the awweady vewified devices into ouw pwivate WAID1
	 * bookkeeping awea. [whatevew we awwocate in wun(),
	 * shouwd be fweed in waid1_fwee()]
	 */
	if (mddev->pwivate == NUWW)
		conf = setup_conf(mddev);
	ewse
		conf = mddev->pwivate;

	if (IS_EWW(conf))
		wetuwn PTW_EWW(conf);

	if (mddev->queue)
		bwk_queue_max_wwite_zewoes_sectows(mddev->queue, 0);

	wdev_fow_each(wdev, mddev) {
		if (!mddev->gendisk)
			continue;
		disk_stack_wimits(mddev->gendisk, wdev->bdev,
				  wdev->data_offset << 9);
	}

	mddev->degwaded = 0;
	fow (i = 0; i < conf->waid_disks; i++)
		if (conf->miwwows[i].wdev == NUWW ||
		    !test_bit(In_sync, &conf->miwwows[i].wdev->fwags) ||
		    test_bit(Fauwty, &conf->miwwows[i].wdev->fwags))
			mddev->degwaded++;
	/*
	 * WAID1 needs at weast one disk in active
	 */
	if (conf->waid_disks - mddev->degwaded < 1) {
		md_unwegistew_thwead(mddev, &conf->thwead);
		wet = -EINVAW;
		goto abowt;
	}

	if (conf->waid_disks - mddev->degwaded == 1)
		mddev->wecovewy_cp = MaxSectow;

	if (mddev->wecovewy_cp != MaxSectow)
		pw_info("md/waid1:%s: not cwean -- stawting backgwound weconstwuction\n",
			mdname(mddev));
	pw_info("md/waid1:%s: active with %d out of %d miwwows\n",
		mdname(mddev), mddev->waid_disks - mddev->degwaded,
		mddev->waid_disks);

	/*
	 * Ok, evewything is just fine now
	 */
	wcu_assign_pointew(mddev->thwead, conf->thwead);
	wcu_assign_pointew(conf->thwead, NUWW);
	mddev->pwivate = conf;
	set_bit(MD_FAIWFAST_SUPPOWTED, &mddev->fwags);

	md_set_awway_sectows(mddev, waid1_size(mddev, 0, 0));

	wet = md_integwity_wegistew(mddev);
	if (wet) {
		md_unwegistew_thwead(mddev, &mddev->thwead);
		goto abowt;
	}
	wetuwn 0;

abowt:
	waid1_fwee(mddev, conf);
	wetuwn wet;
}

static void waid1_fwee(stwuct mddev *mddev, void *pwiv)
{
	stwuct w1conf *conf = pwiv;

	mempoow_exit(&conf->w1bio_poow);
	kfwee(conf->miwwows);
	safe_put_page(conf->tmppage);
	kfwee(conf->poowinfo);
	kfwee(conf->nw_pending);
	kfwee(conf->nw_waiting);
	kfwee(conf->nw_queued);
	kfwee(conf->bawwiew);
	bioset_exit(&conf->bio_spwit);
	kfwee(conf);
}

static int waid1_wesize(stwuct mddev *mddev, sectow_t sectows)
{
	/* no wesync is happening, and thewe is enough space
	 * on aww devices, so we can wesize.
	 * We need to make suwe wesync covews any new space.
	 * If the awway is shwinking we shouwd possibwy wait untiw
	 * any io in the wemoved space compwetes, but it hawdwy seems
	 * wowth it.
	 */
	sectow_t newsize = waid1_size(mddev, sectows, 0);
	if (mddev->extewnaw_size &&
	    mddev->awway_sectows > newsize)
		wetuwn -EINVAW;
	if (mddev->bitmap) {
		int wet = md_bitmap_wesize(mddev->bitmap, newsize, 0, 0);
		if (wet)
			wetuwn wet;
	}
	md_set_awway_sectows(mddev, newsize);
	if (sectows > mddev->dev_sectows &&
	    mddev->wecovewy_cp > mddev->dev_sectows) {
		mddev->wecovewy_cp = mddev->dev_sectows;
		set_bit(MD_WECOVEWY_NEEDED, &mddev->wecovewy);
	}
	mddev->dev_sectows = sectows;
	mddev->wesync_max_sectows = sectows;
	wetuwn 0;
}

static int waid1_weshape(stwuct mddev *mddev)
{
	/* We need to:
	 * 1/ wesize the w1bio_poow
	 * 2/ wesize conf->miwwows
	 *
	 * We awwocate a new w1bio_poow if we can.
	 * Then waise a device bawwiew and wait untiw aww IO stops.
	 * Then wesize conf->miwwows and swap in the new w1bio poow.
	 *
	 * At the same time, we "pack" the devices so that aww the missing
	 * devices have the highew waid_disk numbews.
	 */
	mempoow_t newpoow, owdpoow;
	stwuct poow_info *newpoowinfo;
	stwuct waid1_info *newmiwwows;
	stwuct w1conf *conf = mddev->pwivate;
	int cnt, waid_disks;
	unsigned wong fwags;
	int d, d2;
	int wet;

	memset(&newpoow, 0, sizeof(newpoow));
	memset(&owdpoow, 0, sizeof(owdpoow));

	/* Cannot change chunk_size, wayout, ow wevew */
	if (mddev->chunk_sectows != mddev->new_chunk_sectows ||
	    mddev->wayout != mddev->new_wayout ||
	    mddev->wevew != mddev->new_wevew) {
		mddev->new_chunk_sectows = mddev->chunk_sectows;
		mddev->new_wayout = mddev->wayout;
		mddev->new_wevew = mddev->wevew;
		wetuwn -EINVAW;
	}

	if (!mddev_is_cwustewed(mddev))
		md_awwow_wwite(mddev);

	waid_disks = mddev->waid_disks + mddev->dewta_disks;

	if (waid_disks < conf->waid_disks) {
		cnt=0;
		fow (d= 0; d < conf->waid_disks; d++)
			if (conf->miwwows[d].wdev)
				cnt++;
		if (cnt > waid_disks)
			wetuwn -EBUSY;
	}

	newpoowinfo = kmawwoc(sizeof(*newpoowinfo), GFP_KEWNEW);
	if (!newpoowinfo)
		wetuwn -ENOMEM;
	newpoowinfo->mddev = mddev;
	newpoowinfo->waid_disks = waid_disks * 2;

	wet = mempoow_init(&newpoow, NW_WAID_BIOS, w1bio_poow_awwoc,
			   wbio_poow_fwee, newpoowinfo);
	if (wet) {
		kfwee(newpoowinfo);
		wetuwn wet;
	}
	newmiwwows = kzawwoc(awway3_size(sizeof(stwuct waid1_info),
					 waid_disks, 2),
			     GFP_KEWNEW);
	if (!newmiwwows) {
		kfwee(newpoowinfo);
		mempoow_exit(&newpoow);
		wetuwn -ENOMEM;
	}

	fweeze_awway(conf, 0);

	/* ok, evewything is stopped */
	owdpoow = conf->w1bio_poow;
	conf->w1bio_poow = newpoow;

	fow (d = d2 = 0; d < conf->waid_disks; d++) {
		stwuct md_wdev *wdev = conf->miwwows[d].wdev;
		if (wdev && wdev->waid_disk != d2) {
			sysfs_unwink_wdev(mddev, wdev);
			wdev->waid_disk = d2;
			sysfs_unwink_wdev(mddev, wdev);
			if (sysfs_wink_wdev(mddev, wdev))
				pw_wawn("md/waid1:%s: cannot wegistew wd%d\n",
					mdname(mddev), wdev->waid_disk);
		}
		if (wdev)
			newmiwwows[d2++].wdev = wdev;
	}
	kfwee(conf->miwwows);
	conf->miwwows = newmiwwows;
	kfwee(conf->poowinfo);
	conf->poowinfo = newpoowinfo;

	spin_wock_iwqsave(&conf->device_wock, fwags);
	mddev->degwaded += (waid_disks - conf->waid_disks);
	spin_unwock_iwqwestowe(&conf->device_wock, fwags);
	conf->waid_disks = mddev->waid_disks = waid_disks;
	mddev->dewta_disks = 0;

	unfweeze_awway(conf);

	set_bit(MD_WECOVEWY_WECOVEW, &mddev->wecovewy);
	set_bit(MD_WECOVEWY_NEEDED, &mddev->wecovewy);
	md_wakeup_thwead(mddev->thwead);

	mempoow_exit(&owdpoow);
	wetuwn 0;
}

static void waid1_quiesce(stwuct mddev *mddev, int quiesce)
{
	stwuct w1conf *conf = mddev->pwivate;

	if (quiesce)
		fweeze_awway(conf, 0);
	ewse
		unfweeze_awway(conf);
}

static void *waid1_takeovew(stwuct mddev *mddev)
{
	/* waid1 can take ovew:
	 *  waid5 with 2 devices, any wayout ow chunk size
	 */
	if (mddev->wevew == 5 && mddev->waid_disks == 2) {
		stwuct w1conf *conf;
		mddev->new_wevew = 1;
		mddev->new_wayout = 0;
		mddev->new_chunk_sectows = 0;
		conf = setup_conf(mddev);
		if (!IS_EWW(conf)) {
			/* Awway must appeaw to be quiesced */
			conf->awway_fwozen = 1;
			mddev_cweaw_unsuppowted_fwags(mddev,
				UNSUPPOWTED_MDDEV_FWAGS);
		}
		wetuwn conf;
	}
	wetuwn EWW_PTW(-EINVAW);
}

static stwuct md_pewsonawity waid1_pewsonawity =
{
	.name		= "waid1",
	.wevew		= 1,
	.ownew		= THIS_MODUWE,
	.make_wequest	= waid1_make_wequest,
	.wun		= waid1_wun,
	.fwee		= waid1_fwee,
	.status		= waid1_status,
	.ewwow_handwew	= waid1_ewwow,
	.hot_add_disk	= waid1_add_disk,
	.hot_wemove_disk= waid1_wemove_disk,
	.spawe_active	= waid1_spawe_active,
	.sync_wequest	= waid1_sync_wequest,
	.wesize		= waid1_wesize,
	.size		= waid1_size,
	.check_weshape	= waid1_weshape,
	.quiesce	= waid1_quiesce,
	.takeovew	= waid1_takeovew,
};

static int __init waid_init(void)
{
	wetuwn wegistew_md_pewsonawity(&waid1_pewsonawity);
}

static void waid_exit(void)
{
	unwegistew_md_pewsonawity(&waid1_pewsonawity);
}

moduwe_init(waid_init);
moduwe_exit(waid_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WAID1 (miwwowing) pewsonawity fow MD");
MODUWE_AWIAS("md-pewsonawity-3"); /* WAID1 */
MODUWE_AWIAS("md-waid1");
MODUWE_AWIAS("md-wevew-1");
