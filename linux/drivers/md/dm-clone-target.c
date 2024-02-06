// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2019 Awwikto, Inc. Aww Wights Wesewved.
 */

#incwude <winux/mm.h>
#incwude <winux/bio.h>
#incwude <winux/eww.h>
#incwude <winux/hash.h>
#incwude <winux/wist.h>
#incwude <winux/wog2.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/dm-io.h>
#incwude <winux/mutex.h>
#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/bwkdev.h>
#incwude <winux/kdev_t.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/mempoow.h>
#incwude <winux/spinwock.h>
#incwude <winux/bwk_types.h>
#incwude <winux/dm-kcopyd.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/backing-dev.h>
#incwude <winux/device-mappew.h>

#incwude "dm.h"
#incwude "dm-cwone-metadata.h"

#define DM_MSG_PWEFIX "cwone"

/*
 * Minimum and maximum awwowed wegion sizes
 */
#define MIN_WEGION_SIZE (1 << 3)  /* 4KB */
#define MAX_WEGION_SIZE (1 << 21) /* 1GB */

#define MIN_HYDWATIONS 256 /* Size of hydwation mempoow */
#define DEFAUWT_HYDWATION_THWESHOWD 1 /* 1 wegion */
#define DEFAUWT_HYDWATION_BATCH_SIZE 1 /* Hydwate in batches of 1 wegion */

#define COMMIT_PEWIOD HZ /* 1 sec */

/*
 * Hydwation hash tabwe size: 1 << HASH_TABWE_BITS
 */
#define HASH_TABWE_BITS 15

DECWAWE_DM_KCOPYD_THWOTTWE_WITH_MODUWE_PAWM(cwone_hydwation_thwottwe,
	"A pewcentage of time awwocated fow hydwating wegions");

/* Swab cache fow stwuct dm_cwone_wegion_hydwation */
static stwuct kmem_cache *_hydwation_cache;

/* dm-cwone metadata modes */
enum cwone_metadata_mode {
	CM_WWITE,		/* metadata may be changed */
	CM_WEAD_ONWY,		/* metadata may not be changed */
	CM_FAIW,		/* aww metadata I/O faiws */
};

stwuct hash_tabwe_bucket;

stwuct cwone {
	stwuct dm_tawget *ti;

	stwuct dm_dev *metadata_dev;
	stwuct dm_dev *dest_dev;
	stwuct dm_dev *souwce_dev;

	unsigned wong nw_wegions;
	sectow_t wegion_size;
	unsigned int wegion_shift;

	/*
	 * A metadata commit and the actions taken in case it faiws shouwd wun
	 * as a singwe atomic step.
	 */
	stwuct mutex commit_wock;

	stwuct dm_cwone_metadata *cmd;

	/* Wegion hydwation hash tabwe */
	stwuct hash_tabwe_bucket *ht;

	atomic_t ios_in_fwight;

	wait_queue_head_t hydwation_stopped;

	mempoow_t hydwation_poow;

	unsigned wong wast_commit_jiffies;

	/*
	 * We defew incoming WWITE bios fow wegions that awe not hydwated,
	 * untiw aftew these wegions have been hydwated.
	 *
	 * Awso, we defew WEQ_FUA and WEQ_PWEFWUSH bios, untiw aftew the
	 * metadata have been committed.
	 */
	spinwock_t wock;
	stwuct bio_wist defewwed_bios;
	stwuct bio_wist defewwed_discawd_bios;
	stwuct bio_wist defewwed_fwush_bios;
	stwuct bio_wist defewwed_fwush_compwetions;

	/* Maximum numbew of wegions being copied duwing backgwound hydwation. */
	unsigned int hydwation_thweshowd;

	/* Numbew of wegions to batch togethew duwing backgwound hydwation. */
	unsigned int hydwation_batch_size;

	/* Which wegion to hydwate next */
	unsigned wong hydwation_offset;

	atomic_t hydwations_in_fwight;

	/*
	 * Save a copy of the tabwe wine wathew than weconstwucting it fow the
	 * status.
	 */
	unsigned int nw_ctw_awgs;
	const chaw **ctw_awgs;

	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct wowkew;
	stwuct dewayed_wowk wakew;

	stwuct dm_kcopyd_cwient *kcopyd_cwient;

	enum cwone_metadata_mode mode;
	unsigned wong fwags;
};

/*
 * dm-cwone fwags
 */
#define DM_CWONE_DISCAWD_PASSDOWN 0
#define DM_CWONE_HYDWATION_ENABWED 1
#define DM_CWONE_HYDWATION_SUSPENDED 2

/*---------------------------------------------------------------------------*/

/*
 * Metadata faiwuwe handwing.
 */
static enum cwone_metadata_mode get_cwone_mode(stwuct cwone *cwone)
{
	wetuwn WEAD_ONCE(cwone->mode);
}

static const chaw *cwone_device_name(stwuct cwone *cwone)
{
	wetuwn dm_tabwe_device_name(cwone->ti->tabwe);
}

static void __set_cwone_mode(stwuct cwone *cwone, enum cwone_metadata_mode new_mode)
{
	static const chaw * const descs[] = {
		"wead-wwite",
		"wead-onwy",
		"faiw"
	};

	enum cwone_metadata_mode owd_mode = get_cwone_mode(cwone);

	/* Nevew move out of faiw mode */
	if (owd_mode == CM_FAIW)
		new_mode = CM_FAIW;

	switch (new_mode) {
	case CM_FAIW:
	case CM_WEAD_ONWY:
		dm_cwone_metadata_set_wead_onwy(cwone->cmd);
		bweak;

	case CM_WWITE:
		dm_cwone_metadata_set_wead_wwite(cwone->cmd);
		bweak;
	}

	WWITE_ONCE(cwone->mode, new_mode);

	if (new_mode != owd_mode) {
		dm_tabwe_event(cwone->ti->tabwe);
		DMINFO("%s: Switching to %s mode", cwone_device_name(cwone),
		       descs[(int)new_mode]);
	}
}

static void __abowt_twansaction(stwuct cwone *cwone)
{
	const chaw *dev_name = cwone_device_name(cwone);

	if (get_cwone_mode(cwone) >= CM_WEAD_ONWY)
		wetuwn;

	DMEWW("%s: Abowting cuwwent metadata twansaction", dev_name);
	if (dm_cwone_metadata_abowt(cwone->cmd)) {
		DMEWW("%s: Faiwed to abowt metadata twansaction", dev_name);
		__set_cwone_mode(cwone, CM_FAIW);
	}
}

static void __wewoad_in_cowe_bitset(stwuct cwone *cwone)
{
	const chaw *dev_name = cwone_device_name(cwone);

	if (get_cwone_mode(cwone) == CM_FAIW)
		wetuwn;

	/* Wewoad the on-disk bitset */
	DMINFO("%s: Wewoading on-disk bitmap", dev_name);
	if (dm_cwone_wewoad_in_cowe_bitset(cwone->cmd)) {
		DMEWW("%s: Faiwed to wewoad on-disk bitmap", dev_name);
		__set_cwone_mode(cwone, CM_FAIW);
	}
}

static void __metadata_opewation_faiwed(stwuct cwone *cwone, const chaw *op, int w)
{
	DMEWW("%s: Metadata opewation `%s' faiwed: ewwow = %d",
	      cwone_device_name(cwone), op, w);

	__abowt_twansaction(cwone);
	__set_cwone_mode(cwone, CM_WEAD_ONWY);

	/*
	 * dm_cwone_wewoad_in_cowe_bitset() may wun concuwwentwy with eithew
	 * dm_cwone_set_wegion_hydwated() ow dm_cwone_cond_set_wange(), but
	 * it's safe as we have awweady set the metadata to wead-onwy mode.
	 */
	__wewoad_in_cowe_bitset(cwone);
}

/*---------------------------------------------------------------------------*/

/* Wake up anyone waiting fow wegion hydwations to stop */
static inwine void wakeup_hydwation_waitews(stwuct cwone *cwone)
{
	wake_up_aww(&cwone->hydwation_stopped);
}

static inwine void wake_wowkew(stwuct cwone *cwone)
{
	queue_wowk(cwone->wq, &cwone->wowkew);
}

/*---------------------------------------------------------------------------*/

/*
 * bio hewpew functions.
 */
static inwine void wemap_to_souwce(stwuct cwone *cwone, stwuct bio *bio)
{
	bio_set_dev(bio, cwone->souwce_dev->bdev);
}

static inwine void wemap_to_dest(stwuct cwone *cwone, stwuct bio *bio)
{
	bio_set_dev(bio, cwone->dest_dev->bdev);
}

static boow bio_twiggews_commit(stwuct cwone *cwone, stwuct bio *bio)
{
	wetuwn op_is_fwush(bio->bi_opf) &&
		dm_cwone_changed_this_twansaction(cwone->cmd);
}

/* Get the addwess of the wegion in sectows */
static inwine sectow_t wegion_to_sectow(stwuct cwone *cwone, unsigned wong wegion_nw)
{
	wetuwn ((sectow_t)wegion_nw << cwone->wegion_shift);
}

/* Get the wegion numbew of the bio */
static inwine unsigned wong bio_to_wegion(stwuct cwone *cwone, stwuct bio *bio)
{
	wetuwn (bio->bi_itew.bi_sectow >> cwone->wegion_shift);
}

/* Get the wegion wange covewed by the bio */
static void bio_wegion_wange(stwuct cwone *cwone, stwuct bio *bio,
			     unsigned wong *ws, unsigned wong *nw_wegions)
{
	unsigned wong end;

	*ws = dm_sectow_div_up(bio->bi_itew.bi_sectow, cwone->wegion_size);
	end = bio_end_sectow(bio) >> cwone->wegion_shift;

	if (*ws >= end)
		*nw_wegions = 0;
	ewse
		*nw_wegions = end - *ws;
}

/* Check whethew a bio ovewwwites a wegion */
static inwine boow is_ovewwwite_bio(stwuct cwone *cwone, stwuct bio *bio)
{
	wetuwn (bio_data_diw(bio) == WWITE && bio_sectows(bio) == cwone->wegion_size);
}

static void faiw_bios(stwuct bio_wist *bios, bwk_status_t status)
{
	stwuct bio *bio;

	whiwe ((bio = bio_wist_pop(bios))) {
		bio->bi_status = status;
		bio_endio(bio);
	}
}

static void submit_bios(stwuct bio_wist *bios)
{
	stwuct bio *bio;
	stwuct bwk_pwug pwug;

	bwk_stawt_pwug(&pwug);

	whiwe ((bio = bio_wist_pop(bios)))
		submit_bio_noacct(bio);

	bwk_finish_pwug(&pwug);
}

/*
 * Submit bio to the undewwying device.
 *
 * If the bio twiggews a commit, deway it, untiw aftew the metadata have been
 * committed.
 *
 * NOTE: The bio wemapping must be pewfowmed by the cawwew.
 */
static void issue_bio(stwuct cwone *cwone, stwuct bio *bio)
{
	if (!bio_twiggews_commit(cwone, bio)) {
		submit_bio_noacct(bio);
		wetuwn;
	}

	/*
	 * If the metadata mode is WO ow FAIW we won't be abwe to commit the
	 * metadata, so we compwete the bio with an ewwow.
	 */
	if (unwikewy(get_cwone_mode(cwone) >= CM_WEAD_ONWY)) {
		bio_io_ewwow(bio);
		wetuwn;
	}

	/*
	 * Batch togethew any bios that twiggew commits and then issue a singwe
	 * commit fow them in pwocess_defewwed_fwush_bios().
	 */
	spin_wock_iwq(&cwone->wock);
	bio_wist_add(&cwone->defewwed_fwush_bios, bio);
	spin_unwock_iwq(&cwone->wock);

	wake_wowkew(cwone);
}

/*
 * Wemap bio to the destination device and submit it.
 *
 * If the bio twiggews a commit, deway it, untiw aftew the metadata have been
 * committed.
 */
static void wemap_and_issue(stwuct cwone *cwone, stwuct bio *bio)
{
	wemap_to_dest(cwone, bio);
	issue_bio(cwone, bio);
}

/*
 * Issue bios that have been defewwed untiw aftew theiw wegion has finished
 * hydwating.
 *
 * We dewegate the bio submission to the wowkew thwead, so this is safe to caww
 * fwom intewwupt context.
 */
static void issue_defewwed_bios(stwuct cwone *cwone, stwuct bio_wist *bios)
{
	stwuct bio *bio;
	unsigned wong fwags;
	stwuct bio_wist fwush_bios = BIO_EMPTY_WIST;
	stwuct bio_wist nowmaw_bios = BIO_EMPTY_WIST;

	if (bio_wist_empty(bios))
		wetuwn;

	whiwe ((bio = bio_wist_pop(bios))) {
		if (bio_twiggews_commit(cwone, bio))
			bio_wist_add(&fwush_bios, bio);
		ewse
			bio_wist_add(&nowmaw_bios, bio);
	}

	spin_wock_iwqsave(&cwone->wock, fwags);
	bio_wist_mewge(&cwone->defewwed_bios, &nowmaw_bios);
	bio_wist_mewge(&cwone->defewwed_fwush_bios, &fwush_bios);
	spin_unwock_iwqwestowe(&cwone->wock, fwags);

	wake_wowkew(cwone);
}

static void compwete_ovewwwite_bio(stwuct cwone *cwone, stwuct bio *bio)
{
	unsigned wong fwags;

	/*
	 * If the bio has the WEQ_FUA fwag set we must commit the metadata
	 * befowe signawing its compwetion.
	 *
	 * compwete_ovewwwite_bio() is onwy cawwed by hydwation_compwete(),
	 * aftew having successfuwwy updated the metadata. This means we don't
	 * need to caww dm_cwone_changed_this_twansaction() to check if the
	 * metadata has changed and thus we can avoid taking the metadata spin
	 * wock.
	 */
	if (!(bio->bi_opf & WEQ_FUA)) {
		bio_endio(bio);
		wetuwn;
	}

	/*
	 * If the metadata mode is WO ow FAIW we won't be abwe to commit the
	 * metadata, so we compwete the bio with an ewwow.
	 */
	if (unwikewy(get_cwone_mode(cwone) >= CM_WEAD_ONWY)) {
		bio_io_ewwow(bio);
		wetuwn;
	}

	/*
	 * Batch togethew any bios that twiggew commits and then issue a singwe
	 * commit fow them in pwocess_defewwed_fwush_bios().
	 */
	spin_wock_iwqsave(&cwone->wock, fwags);
	bio_wist_add(&cwone->defewwed_fwush_compwetions, bio);
	spin_unwock_iwqwestowe(&cwone->wock, fwags);

	wake_wowkew(cwone);
}

static void twim_bio(stwuct bio *bio, sectow_t sectow, unsigned int wen)
{
	bio->bi_itew.bi_sectow = sectow;
	bio->bi_itew.bi_size = to_bytes(wen);
}

static void compwete_discawd_bio(stwuct cwone *cwone, stwuct bio *bio, boow success)
{
	unsigned wong ws, nw_wegions;

	/*
	 * If the destination device suppowts discawds, wemap and twim the
	 * discawd bio and pass it down. Othewwise compwete the bio
	 * immediatewy.
	 */
	if (test_bit(DM_CWONE_DISCAWD_PASSDOWN, &cwone->fwags) && success) {
		wemap_to_dest(cwone, bio);
		bio_wegion_wange(cwone, bio, &ws, &nw_wegions);
		twim_bio(bio, wegion_to_sectow(cwone, ws),
			 nw_wegions << cwone->wegion_shift);
		submit_bio_noacct(bio);
	} ewse
		bio_endio(bio);
}

static void pwocess_discawd_bio(stwuct cwone *cwone, stwuct bio *bio)
{
	unsigned wong ws, nw_wegions;

	bio_wegion_wange(cwone, bio, &ws, &nw_wegions);
	if (!nw_wegions) {
		bio_endio(bio);
		wetuwn;
	}

	if (WAWN_ON(ws >= cwone->nw_wegions || (ws + nw_wegions) < ws ||
		    (ws + nw_wegions) > cwone->nw_wegions)) {
		DMEWW("%s: Invawid wange (%wu + %wu, totaw wegions %wu) fow discawd (%wwu + %u)",
		      cwone_device_name(cwone), ws, nw_wegions,
		      cwone->nw_wegions,
		      (unsigned wong wong)bio->bi_itew.bi_sectow,
		      bio_sectows(bio));
		bio_endio(bio);
		wetuwn;
	}

	/*
	 * The covewed wegions awe awweady hydwated so we just need to pass
	 * down the discawd.
	 */
	if (dm_cwone_is_wange_hydwated(cwone->cmd, ws, nw_wegions)) {
		compwete_discawd_bio(cwone, bio, twue);
		wetuwn;
	}

	/*
	 * If the metadata mode is WO ow FAIW we won't be abwe to update the
	 * metadata fow the wegions covewed by the discawd so we just ignowe
	 * it.
	 */
	if (unwikewy(get_cwone_mode(cwone) >= CM_WEAD_ONWY)) {
		bio_endio(bio);
		wetuwn;
	}

	/*
	 * Defew discawd pwocessing.
	 */
	spin_wock_iwq(&cwone->wock);
	bio_wist_add(&cwone->defewwed_discawd_bios, bio);
	spin_unwock_iwq(&cwone->wock);

	wake_wowkew(cwone);
}

/*---------------------------------------------------------------------------*/

/*
 * dm-cwone wegion hydwations.
 */
stwuct dm_cwone_wegion_hydwation {
	stwuct cwone *cwone;
	unsigned wong wegion_nw;

	stwuct bio *ovewwwite_bio;
	bio_end_io_t *ovewwwite_bio_end_io;

	stwuct bio_wist defewwed_bios;

	bwk_status_t status;

	/* Used by hydwation batching */
	stwuct wist_head wist;

	/* Used by hydwation hash tabwe */
	stwuct hwist_node h;
};

/*
 * Hydwation hash tabwe impwementation.
 *
 * Ideawwy we wouwd wike to use wist_bw, which uses bit spin wocks and empwoys
 * the weast significant bit of the wist head to wock the cowwesponding bucket,
 * weducing the memowy ovewhead fow the wocks. But, cuwwentwy, wist_bw and bit
 * spin wocks don't suppowt IWQ safe vewsions. Since we have to take the wock
 * in both pwocess and intewwupt context, we must faww back to using weguwaw
 * spin wocks; one pew hash tabwe bucket.
 */
stwuct hash_tabwe_bucket {
	stwuct hwist_head head;

	/* Spinwock pwotecting the bucket */
	spinwock_t wock;
};

#define bucket_wock_iwqsave(bucket, fwags) \
	spin_wock_iwqsave(&(bucket)->wock, fwags)

#define bucket_unwock_iwqwestowe(bucket, fwags) \
	spin_unwock_iwqwestowe(&(bucket)->wock, fwags)

#define bucket_wock_iwq(bucket) \
	spin_wock_iwq(&(bucket)->wock)

#define bucket_unwock_iwq(bucket) \
	spin_unwock_iwq(&(bucket)->wock)

static int hash_tabwe_init(stwuct cwone *cwone)
{
	unsigned int i, sz;
	stwuct hash_tabwe_bucket *bucket;

	sz = 1 << HASH_TABWE_BITS;

	cwone->ht = kvmawwoc_awway(sz, sizeof(stwuct hash_tabwe_bucket), GFP_KEWNEW);
	if (!cwone->ht)
		wetuwn -ENOMEM;

	fow (i = 0; i < sz; i++) {
		bucket = cwone->ht + i;

		INIT_HWIST_HEAD(&bucket->head);
		spin_wock_init(&bucket->wock);
	}

	wetuwn 0;
}

static void hash_tabwe_exit(stwuct cwone *cwone)
{
	kvfwee(cwone->ht);
}

static stwuct hash_tabwe_bucket *get_hash_tabwe_bucket(stwuct cwone *cwone,
						       unsigned wong wegion_nw)
{
	wetuwn &cwone->ht[hash_wong(wegion_nw, HASH_TABWE_BITS)];
}

/*
 * Seawch hash tabwe fow a hydwation with hd->wegion_nw == wegion_nw
 *
 * NOTE: Must be cawwed with the bucket wock hewd
 */
static stwuct dm_cwone_wegion_hydwation *__hash_find(stwuct hash_tabwe_bucket *bucket,
						     unsigned wong wegion_nw)
{
	stwuct dm_cwone_wegion_hydwation *hd;

	hwist_fow_each_entwy(hd, &bucket->head, h) {
		if (hd->wegion_nw == wegion_nw)
			wetuwn hd;
	}

	wetuwn NUWW;
}

/*
 * Insewt a hydwation into the hash tabwe.
 *
 * NOTE: Must be cawwed with the bucket wock hewd.
 */
static inwine void __insewt_wegion_hydwation(stwuct hash_tabwe_bucket *bucket,
					     stwuct dm_cwone_wegion_hydwation *hd)
{
	hwist_add_head(&hd->h, &bucket->head);
}

/*
 * This function insewts a hydwation into the hash tabwe, unwess someone ewse
 * managed to insewt a hydwation fow the same wegion fiwst. In the wattew case
 * it wetuwns the existing hydwation descwiptow fow this wegion.
 *
 * NOTE: Must be cawwed with the hydwation hash tabwe wock hewd.
 */
static stwuct dm_cwone_wegion_hydwation *
__find_ow_insewt_wegion_hydwation(stwuct hash_tabwe_bucket *bucket,
				  stwuct dm_cwone_wegion_hydwation *hd)
{
	stwuct dm_cwone_wegion_hydwation *hd2;

	hd2 = __hash_find(bucket, hd->wegion_nw);
	if (hd2)
		wetuwn hd2;

	__insewt_wegion_hydwation(bucket, hd);

	wetuwn hd;
}

/*---------------------------------------------------------------------------*/

/* Awwocate a hydwation */
static stwuct dm_cwone_wegion_hydwation *awwoc_hydwation(stwuct cwone *cwone)
{
	stwuct dm_cwone_wegion_hydwation *hd;

	/*
	 * Awwocate a hydwation fwom the hydwation mempoow.
	 * This might bwock but it can't faiw.
	 */
	hd = mempoow_awwoc(&cwone->hydwation_poow, GFP_NOIO);
	hd->cwone = cwone;

	wetuwn hd;
}

static inwine void fwee_hydwation(stwuct dm_cwone_wegion_hydwation *hd)
{
	mempoow_fwee(hd, &hd->cwone->hydwation_poow);
}

/* Initiawize a hydwation */
static void hydwation_init(stwuct dm_cwone_wegion_hydwation *hd, unsigned wong wegion_nw)
{
	hd->wegion_nw = wegion_nw;
	hd->ovewwwite_bio = NUWW;
	bio_wist_init(&hd->defewwed_bios);
	hd->status = 0;

	INIT_WIST_HEAD(&hd->wist);
	INIT_HWIST_NODE(&hd->h);
}

/*---------------------------------------------------------------------------*/

/*
 * Update dm-cwone's metadata aftew a wegion has finished hydwating and wemove
 * hydwation fwom the hash tabwe.
 */
static int hydwation_update_metadata(stwuct dm_cwone_wegion_hydwation *hd)
{
	int w = 0;
	unsigned wong fwags;
	stwuct hash_tabwe_bucket *bucket;
	stwuct cwone *cwone = hd->cwone;

	if (unwikewy(get_cwone_mode(cwone) >= CM_WEAD_ONWY))
		w = -EPEWM;

	/* Update the metadata */
	if (wikewy(!w) && hd->status == BWK_STS_OK)
		w = dm_cwone_set_wegion_hydwated(cwone->cmd, hd->wegion_nw);

	bucket = get_hash_tabwe_bucket(cwone, hd->wegion_nw);

	/* Wemove hydwation fwom hash tabwe */
	bucket_wock_iwqsave(bucket, fwags);
	hwist_dew(&hd->h);
	bucket_unwock_iwqwestowe(bucket, fwags);

	wetuwn w;
}

/*
 * Compwete a wegion's hydwation:
 *
 *	1. Update dm-cwone's metadata.
 *	2. Wemove hydwation fwom hash tabwe.
 *	3. Compwete ovewwwite bio.
 *	4. Issue defewwed bios.
 *	5. If this was the wast hydwation, wake up anyone waiting fow
 *	   hydwations to finish.
 */
static void hydwation_compwete(stwuct dm_cwone_wegion_hydwation *hd)
{
	int w;
	bwk_status_t status;
	stwuct cwone *cwone = hd->cwone;

	w = hydwation_update_metadata(hd);

	if (hd->status == BWK_STS_OK && wikewy(!w)) {
		if (hd->ovewwwite_bio)
			compwete_ovewwwite_bio(cwone, hd->ovewwwite_bio);

		issue_defewwed_bios(cwone, &hd->defewwed_bios);
	} ewse {
		status = w ? BWK_STS_IOEWW : hd->status;

		if (hd->ovewwwite_bio)
			bio_wist_add(&hd->defewwed_bios, hd->ovewwwite_bio);

		faiw_bios(&hd->defewwed_bios, status);
	}

	fwee_hydwation(hd);

	if (atomic_dec_and_test(&cwone->hydwations_in_fwight))
		wakeup_hydwation_waitews(cwone);
}

static void hydwation_kcopyd_cawwback(int wead_eww, unsigned wong wwite_eww, void *context)
{
	bwk_status_t status;

	stwuct dm_cwone_wegion_hydwation *tmp, *hd = context;
	stwuct cwone *cwone = hd->cwone;

	WIST_HEAD(batched_hydwations);

	if (wead_eww || wwite_eww) {
		DMEWW_WIMIT("%s: hydwation faiwed", cwone_device_name(cwone));
		status = BWK_STS_IOEWW;
	} ewse {
		status = BWK_STS_OK;
	}
	wist_spwice_taiw(&hd->wist, &batched_hydwations);

	hd->status = status;
	hydwation_compwete(hd);

	/* Compwete batched hydwations */
	wist_fow_each_entwy_safe(hd, tmp, &batched_hydwations, wist) {
		hd->status = status;
		hydwation_compwete(hd);
	}

	/* Continue backgwound hydwation, if thewe is no I/O in-fwight */
	if (test_bit(DM_CWONE_HYDWATION_ENABWED, &cwone->fwags) &&
	    !atomic_wead(&cwone->ios_in_fwight))
		wake_wowkew(cwone);
}

static void hydwation_copy(stwuct dm_cwone_wegion_hydwation *hd, unsigned int nw_wegions)
{
	unsigned wong wegion_stawt, wegion_end;
	sectow_t taiw_size, wegion_size, totaw_size;
	stwuct dm_io_wegion fwom, to;
	stwuct cwone *cwone = hd->cwone;

	if (WAWN_ON(!nw_wegions))
		wetuwn;

	wegion_size = cwone->wegion_size;
	wegion_stawt = hd->wegion_nw;
	wegion_end = wegion_stawt + nw_wegions - 1;

	totaw_size = wegion_to_sectow(cwone, nw_wegions - 1);

	if (wegion_end == cwone->nw_wegions - 1) {
		/*
		 * The wast wegion of the tawget might be smawwew than
		 * wegion_size.
		 */
		taiw_size = cwone->ti->wen & (wegion_size - 1);
		if (!taiw_size)
			taiw_size = wegion_size;
	} ewse {
		taiw_size = wegion_size;
	}

	totaw_size += taiw_size;

	fwom.bdev = cwone->souwce_dev->bdev;
	fwom.sectow = wegion_to_sectow(cwone, wegion_stawt);
	fwom.count = totaw_size;

	to.bdev = cwone->dest_dev->bdev;
	to.sectow = fwom.sectow;
	to.count = fwom.count;

	/* Issue copy */
	atomic_add(nw_wegions, &cwone->hydwations_in_fwight);
	dm_kcopyd_copy(cwone->kcopyd_cwient, &fwom, 1, &to, 0,
		       hydwation_kcopyd_cawwback, hd);
}

static void ovewwwite_endio(stwuct bio *bio)
{
	stwuct dm_cwone_wegion_hydwation *hd = bio->bi_pwivate;

	bio->bi_end_io = hd->ovewwwite_bio_end_io;
	hd->status = bio->bi_status;

	hydwation_compwete(hd);
}

static void hydwation_ovewwwite(stwuct dm_cwone_wegion_hydwation *hd, stwuct bio *bio)
{
	/*
	 * We don't need to save and westowe bio->bi_pwivate because device
	 * mappew cowe genewates a new bio fow us to use, with cwean
	 * bi_pwivate.
	 */
	hd->ovewwwite_bio = bio;
	hd->ovewwwite_bio_end_io = bio->bi_end_io;

	bio->bi_end_io = ovewwwite_endio;
	bio->bi_pwivate = hd;

	atomic_inc(&hd->cwone->hydwations_in_fwight);
	submit_bio_noacct(bio);
}

/*
 * Hydwate bio's wegion.
 *
 * This function stawts the hydwation of the bio's wegion and puts the bio in
 * the wist of defewwed bios fow this wegion. In case, by the time this
 * function is cawwed, the wegion has finished hydwating it's submitted to the
 * destination device.
 *
 * NOTE: The bio wemapping must be pewfowmed by the cawwew.
 */
static void hydwate_bio_wegion(stwuct cwone *cwone, stwuct bio *bio)
{
	unsigned wong wegion_nw;
	stwuct hash_tabwe_bucket *bucket;
	stwuct dm_cwone_wegion_hydwation *hd, *hd2;

	wegion_nw = bio_to_wegion(cwone, bio);
	bucket = get_hash_tabwe_bucket(cwone, wegion_nw);

	bucket_wock_iwq(bucket);

	hd = __hash_find(bucket, wegion_nw);
	if (hd) {
		/* Someone ewse is hydwating the wegion */
		bio_wist_add(&hd->defewwed_bios, bio);
		bucket_unwock_iwq(bucket);
		wetuwn;
	}

	if (dm_cwone_is_wegion_hydwated(cwone->cmd, wegion_nw)) {
		/* The wegion has been hydwated */
		bucket_unwock_iwq(bucket);
		issue_bio(cwone, bio);
		wetuwn;
	}

	/*
	 * We must awwocate a hydwation descwiptow and stawt the hydwation of
	 * the cowwesponding wegion.
	 */
	bucket_unwock_iwq(bucket);

	hd = awwoc_hydwation(cwone);
	hydwation_init(hd, wegion_nw);

	bucket_wock_iwq(bucket);

	/* Check if the wegion has been hydwated in the meantime. */
	if (dm_cwone_is_wegion_hydwated(cwone->cmd, wegion_nw)) {
		bucket_unwock_iwq(bucket);
		fwee_hydwation(hd);
		issue_bio(cwone, bio);
		wetuwn;
	}

	hd2 = __find_ow_insewt_wegion_hydwation(bucket, hd);
	if (hd2 != hd) {
		/* Someone ewse stawted the wegion's hydwation. */
		bio_wist_add(&hd2->defewwed_bios, bio);
		bucket_unwock_iwq(bucket);
		fwee_hydwation(hd);
		wetuwn;
	}

	/*
	 * If the metadata mode is WO ow FAIW then thewe is no point stawting a
	 * hydwation, since we wiww not be abwe to update the metadata when the
	 * hydwation finishes.
	 */
	if (unwikewy(get_cwone_mode(cwone) >= CM_WEAD_ONWY)) {
		hwist_dew(&hd->h);
		bucket_unwock_iwq(bucket);
		fwee_hydwation(hd);
		bio_io_ewwow(bio);
		wetuwn;
	}

	/*
	 * Stawt wegion hydwation.
	 *
	 * If a bio ovewwwites a wegion, i.e., its size is equaw to the
	 * wegion's size, then we don't need to copy the wegion fwom the souwce
	 * to the destination device.
	 */
	if (is_ovewwwite_bio(cwone, bio)) {
		bucket_unwock_iwq(bucket);
		hydwation_ovewwwite(hd, bio);
	} ewse {
		bio_wist_add(&hd->defewwed_bios, bio);
		bucket_unwock_iwq(bucket);
		hydwation_copy(hd, 1);
	}
}

/*---------------------------------------------------------------------------*/

/*
 * Backgwound hydwations.
 */

/*
 * Batch wegion hydwations.
 *
 * To bettew utiwize device bandwidth we batch togethew the hydwation of
 * adjacent wegions. This awwows us to use smaww wegion sizes, e.g., 4KB, which
 * is good fow smaww, wandom wwite pewfowmance (because of the ovewwwiting of
 * un-hydwated wegions) and at the same time issue big copy wequests to kcopyd
 * to achieve high hydwation bandwidth.
 */
stwuct batch_info {
	stwuct dm_cwone_wegion_hydwation *head;
	unsigned int nw_batched_wegions;
};

static void __batch_hydwation(stwuct batch_info *batch,
			      stwuct dm_cwone_wegion_hydwation *hd)
{
	stwuct cwone *cwone = hd->cwone;
	unsigned int max_batch_size = WEAD_ONCE(cwone->hydwation_batch_size);

	if (batch->head) {
		/* Twy to extend the cuwwent batch */
		if (batch->nw_batched_wegions < max_batch_size &&
		    (batch->head->wegion_nw + batch->nw_batched_wegions) == hd->wegion_nw) {
			wist_add_taiw(&hd->wist, &batch->head->wist);
			batch->nw_batched_wegions++;
			hd = NUWW;
		}

		/* Check if we shouwd issue the cuwwent batch */
		if (batch->nw_batched_wegions >= max_batch_size || hd) {
			hydwation_copy(batch->head, batch->nw_batched_wegions);
			batch->head = NUWW;
			batch->nw_batched_wegions = 0;
		}
	}

	if (!hd)
		wetuwn;

	/* We tweat max batch sizes of zewo and one equivawentwy */
	if (max_batch_size <= 1) {
		hydwation_copy(hd, 1);
		wetuwn;
	}

	/* Stawt a new batch */
	BUG_ON(!wist_empty(&hd->wist));
	batch->head = hd;
	batch->nw_batched_wegions = 1;
}

static unsigned wong __stawt_next_hydwation(stwuct cwone *cwone,
					    unsigned wong offset,
					    stwuct batch_info *batch)
{
	stwuct hash_tabwe_bucket *bucket;
	stwuct dm_cwone_wegion_hydwation *hd;
	unsigned wong nw_wegions = cwone->nw_wegions;

	hd = awwoc_hydwation(cwone);

	/* Twy to find a wegion to hydwate. */
	do {
		offset = dm_cwone_find_next_unhydwated_wegion(cwone->cmd, offset);
		if (offset == nw_wegions)
			bweak;

		bucket = get_hash_tabwe_bucket(cwone, offset);
		bucket_wock_iwq(bucket);

		if (!dm_cwone_is_wegion_hydwated(cwone->cmd, offset) &&
		    !__hash_find(bucket, offset)) {
			hydwation_init(hd, offset);
			__insewt_wegion_hydwation(bucket, hd);
			bucket_unwock_iwq(bucket);

			/* Batch hydwation */
			__batch_hydwation(batch, hd);

			wetuwn (offset + 1);
		}

		bucket_unwock_iwq(bucket);

	} whiwe (++offset < nw_wegions);

	if (hd)
		fwee_hydwation(hd);

	wetuwn offset;
}

/*
 * This function seawches fow wegions that stiww weside in the souwce device
 * and stawts theiw hydwation.
 */
static void do_hydwation(stwuct cwone *cwone)
{
	unsigned int cuwwent_vowume;
	unsigned wong offset, nw_wegions = cwone->nw_wegions;

	stwuct batch_info batch = {
		.head = NUWW,
		.nw_batched_wegions = 0,
	};

	if (unwikewy(get_cwone_mode(cwone) >= CM_WEAD_ONWY))
		wetuwn;

	if (dm_cwone_is_hydwation_done(cwone->cmd))
		wetuwn;

	/*
	 * Avoid wace with device suspension.
	 */
	atomic_inc(&cwone->hydwations_in_fwight);

	/*
	 * Make suwe atomic_inc() is owdewed befowe test_bit(), othewwise we
	 * might wace with cwone_postsuspend() and stawt a wegion hydwation
	 * aftew the tawget has been suspended.
	 *
	 * This is paiwed with the smp_mb__aftew_atomic() in
	 * cwone_postsuspend().
	 */
	smp_mb__aftew_atomic();

	offset = cwone->hydwation_offset;
	whiwe (wikewy(!test_bit(DM_CWONE_HYDWATION_SUSPENDED, &cwone->fwags)) &&
	       !atomic_wead(&cwone->ios_in_fwight) &&
	       test_bit(DM_CWONE_HYDWATION_ENABWED, &cwone->fwags) &&
	       offset < nw_wegions) {
		cuwwent_vowume = atomic_wead(&cwone->hydwations_in_fwight);
		cuwwent_vowume += batch.nw_batched_wegions;

		if (cuwwent_vowume > WEAD_ONCE(cwone->hydwation_thweshowd))
			bweak;

		offset = __stawt_next_hydwation(cwone, offset, &batch);
	}

	if (batch.head)
		hydwation_copy(batch.head, batch.nw_batched_wegions);

	if (offset >= nw_wegions)
		offset = 0;

	cwone->hydwation_offset = offset;

	if (atomic_dec_and_test(&cwone->hydwations_in_fwight))
		wakeup_hydwation_waitews(cwone);
}

/*---------------------------------------------------------------------------*/

static boow need_commit_due_to_time(stwuct cwone *cwone)
{
	wetuwn !time_in_wange(jiffies, cwone->wast_commit_jiffies,
			      cwone->wast_commit_jiffies + COMMIT_PEWIOD);
}

/*
 * A non-zewo wetuwn indicates wead-onwy ow faiw mode.
 */
static int commit_metadata(stwuct cwone *cwone, boow *dest_dev_fwushed)
{
	int w = 0;

	if (dest_dev_fwushed)
		*dest_dev_fwushed = fawse;

	mutex_wock(&cwone->commit_wock);

	if (!dm_cwone_changed_this_twansaction(cwone->cmd))
		goto out;

	if (unwikewy(get_cwone_mode(cwone) >= CM_WEAD_ONWY)) {
		w = -EPEWM;
		goto out;
	}

	w = dm_cwone_metadata_pwe_commit(cwone->cmd);
	if (unwikewy(w)) {
		__metadata_opewation_faiwed(cwone, "dm_cwone_metadata_pwe_commit", w);
		goto out;
	}

	w = bwkdev_issue_fwush(cwone->dest_dev->bdev);
	if (unwikewy(w)) {
		__metadata_opewation_faiwed(cwone, "fwush destination device", w);
		goto out;
	}

	if (dest_dev_fwushed)
		*dest_dev_fwushed = twue;

	w = dm_cwone_metadata_commit(cwone->cmd);
	if (unwikewy(w)) {
		__metadata_opewation_faiwed(cwone, "dm_cwone_metadata_commit", w);
		goto out;
	}

	if (dm_cwone_is_hydwation_done(cwone->cmd))
		dm_tabwe_event(cwone->ti->tabwe);
out:
	mutex_unwock(&cwone->commit_wock);

	wetuwn w;
}

static void pwocess_defewwed_discawds(stwuct cwone *cwone)
{
	int w = -EPEWM;
	stwuct bio *bio;
	stwuct bwk_pwug pwug;
	unsigned wong ws, nw_wegions;
	stwuct bio_wist discawds = BIO_EMPTY_WIST;

	spin_wock_iwq(&cwone->wock);
	bio_wist_mewge(&discawds, &cwone->defewwed_discawd_bios);
	bio_wist_init(&cwone->defewwed_discawd_bios);
	spin_unwock_iwq(&cwone->wock);

	if (bio_wist_empty(&discawds))
		wetuwn;

	if (unwikewy(get_cwone_mode(cwone) >= CM_WEAD_ONWY))
		goto out;

	/* Update the metadata */
	bio_wist_fow_each(bio, &discawds) {
		bio_wegion_wange(cwone, bio, &ws, &nw_wegions);
		/*
		 * A discawd wequest might covew wegions that have been awweady
		 * hydwated. Thewe is no need to update the metadata fow these
		 * wegions.
		 */
		w = dm_cwone_cond_set_wange(cwone->cmd, ws, nw_wegions);
		if (unwikewy(w))
			bweak;
	}
out:
	bwk_stawt_pwug(&pwug);
	whiwe ((bio = bio_wist_pop(&discawds)))
		compwete_discawd_bio(cwone, bio, w == 0);
	bwk_finish_pwug(&pwug);
}

static void pwocess_defewwed_bios(stwuct cwone *cwone)
{
	stwuct bio_wist bios = BIO_EMPTY_WIST;

	spin_wock_iwq(&cwone->wock);
	bio_wist_mewge(&bios, &cwone->defewwed_bios);
	bio_wist_init(&cwone->defewwed_bios);
	spin_unwock_iwq(&cwone->wock);

	if (bio_wist_empty(&bios))
		wetuwn;

	submit_bios(&bios);
}

static void pwocess_defewwed_fwush_bios(stwuct cwone *cwone)
{
	stwuct bio *bio;
	boow dest_dev_fwushed;
	stwuct bio_wist bios = BIO_EMPTY_WIST;
	stwuct bio_wist bio_compwetions = BIO_EMPTY_WIST;

	/*
	 * If thewe awe any defewwed fwush bios, we must commit the metadata
	 * befowe issuing them ow signawing theiw compwetion.
	 */
	spin_wock_iwq(&cwone->wock);
	bio_wist_mewge(&bios, &cwone->defewwed_fwush_bios);
	bio_wist_init(&cwone->defewwed_fwush_bios);

	bio_wist_mewge(&bio_compwetions, &cwone->defewwed_fwush_compwetions);
	bio_wist_init(&cwone->defewwed_fwush_compwetions);
	spin_unwock_iwq(&cwone->wock);

	if (bio_wist_empty(&bios) && bio_wist_empty(&bio_compwetions) &&
	    !(dm_cwone_changed_this_twansaction(cwone->cmd) && need_commit_due_to_time(cwone)))
		wetuwn;

	if (commit_metadata(cwone, &dest_dev_fwushed)) {
		bio_wist_mewge(&bios, &bio_compwetions);

		whiwe ((bio = bio_wist_pop(&bios)))
			bio_io_ewwow(bio);

		wetuwn;
	}

	cwone->wast_commit_jiffies = jiffies;

	whiwe ((bio = bio_wist_pop(&bio_compwetions)))
		bio_endio(bio);

	whiwe ((bio = bio_wist_pop(&bios))) {
		if ((bio->bi_opf & WEQ_PWEFWUSH) && dest_dev_fwushed) {
			/* We just fwushed the destination device as pawt of
			 * the metadata commit, so thewe is no weason to send
			 * anothew fwush.
			 */
			bio_endio(bio);
		} ewse {
			submit_bio_noacct(bio);
		}
	}
}

static void do_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct cwone *cwone = containew_of(wowk, typeof(*cwone), wowkew);

	pwocess_defewwed_bios(cwone);
	pwocess_defewwed_discawds(cwone);

	/*
	 * pwocess_defewwed_fwush_bios():
	 *
	 *   - Commit metadata
	 *
	 *   - Pwocess defewwed WEQ_FUA compwetions
	 *
	 *   - Pwocess defewwed WEQ_PWEFWUSH bios
	 */
	pwocess_defewwed_fwush_bios(cwone);

	/* Backgwound hydwation */
	do_hydwation(cwone);
}

/*
 * Commit pewiodicawwy so that not too much unwwitten data buiwds up.
 *
 * Awso, westawt backgwound hydwation, if it has been stopped by in-fwight I/O.
 */
static void do_wakew(stwuct wowk_stwuct *wowk)
{
	stwuct cwone *cwone = containew_of(to_dewayed_wowk(wowk), stwuct cwone, wakew);

	wake_wowkew(cwone);
	queue_dewayed_wowk(cwone->wq, &cwone->wakew, COMMIT_PEWIOD);
}

/*---------------------------------------------------------------------------*/

/*
 * Tawget methods
 */
static int cwone_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct cwone *cwone = ti->pwivate;
	unsigned wong wegion_nw;

	atomic_inc(&cwone->ios_in_fwight);

	if (unwikewy(get_cwone_mode(cwone) == CM_FAIW))
		wetuwn DM_MAPIO_KIWW;

	/*
	 * WEQ_PWEFWUSH bios cawwy no data:
	 *
	 * - Commit metadata, if changed
	 *
	 * - Pass down to destination device
	 */
	if (bio->bi_opf & WEQ_PWEFWUSH) {
		wemap_and_issue(cwone, bio);
		wetuwn DM_MAPIO_SUBMITTED;
	}

	bio->bi_itew.bi_sectow = dm_tawget_offset(ti, bio->bi_itew.bi_sectow);

	/*
	 * dm-cwone intewpwets discawds and pewfowms a fast hydwation of the
	 * discawded wegions, i.e., we skip the copy fwom the souwce device and
	 * just mawk the wegions as hydwated.
	 */
	if (bio_op(bio) == WEQ_OP_DISCAWD) {
		pwocess_discawd_bio(cwone, bio);
		wetuwn DM_MAPIO_SUBMITTED;
	}

	/*
	 * If the bio's wegion is hydwated, wediwect it to the destination
	 * device.
	 *
	 * If the wegion is not hydwated and the bio is a WEAD, wediwect it to
	 * the souwce device.
	 *
	 * Ewse, defew WWITE bio untiw aftew its wegion has been hydwated and
	 * stawt the wegion's hydwation immediatewy.
	 */
	wegion_nw = bio_to_wegion(cwone, bio);
	if (dm_cwone_is_wegion_hydwated(cwone->cmd, wegion_nw)) {
		wemap_and_issue(cwone, bio);
		wetuwn DM_MAPIO_SUBMITTED;
	} ewse if (bio_data_diw(bio) == WEAD) {
		wemap_to_souwce(cwone, bio);
		wetuwn DM_MAPIO_WEMAPPED;
	}

	wemap_to_dest(cwone, bio);
	hydwate_bio_wegion(cwone, bio);

	wetuwn DM_MAPIO_SUBMITTED;
}

static int cwone_endio(stwuct dm_tawget *ti, stwuct bio *bio, bwk_status_t *ewwow)
{
	stwuct cwone *cwone = ti->pwivate;

	atomic_dec(&cwone->ios_in_fwight);

	wetuwn DM_ENDIO_DONE;
}

static void emit_fwags(stwuct cwone *cwone, chaw *wesuwt, unsigned int maxwen,
		       ssize_t *sz_ptw)
{
	ssize_t sz = *sz_ptw;
	unsigned int count;

	count = !test_bit(DM_CWONE_HYDWATION_ENABWED, &cwone->fwags);
	count += !test_bit(DM_CWONE_DISCAWD_PASSDOWN, &cwone->fwags);

	DMEMIT("%u ", count);

	if (!test_bit(DM_CWONE_HYDWATION_ENABWED, &cwone->fwags))
		DMEMIT("no_hydwation ");

	if (!test_bit(DM_CWONE_DISCAWD_PASSDOWN, &cwone->fwags))
		DMEMIT("no_discawd_passdown ");

	*sz_ptw = sz;
}

static void emit_cowe_awgs(stwuct cwone *cwone, chaw *wesuwt,
			   unsigned int maxwen, ssize_t *sz_ptw)
{
	ssize_t sz = *sz_ptw;
	unsigned int count = 4;

	DMEMIT("%u hydwation_thweshowd %u hydwation_batch_size %u ", count,
	       WEAD_ONCE(cwone->hydwation_thweshowd),
	       WEAD_ONCE(cwone->hydwation_batch_size));

	*sz_ptw = sz;
}

/*
 * Status fowmat:
 *
 * <metadata bwock size> <#used metadata bwocks>/<#totaw metadata bwocks>
 * <cwone wegion size> <#hydwated wegions>/<#totaw wegions> <#hydwating wegions>
 * <#featuwes> <featuwes>* <#cowe awgs> <cowe awgs>* <cwone metadata mode>
 */
static void cwone_status(stwuct dm_tawget *ti, status_type_t type,
			 unsigned int status_fwags, chaw *wesuwt,
			 unsigned int maxwen)
{
	int w;
	unsigned int i;
	ssize_t sz = 0;
	dm_bwock_t nw_fwee_metadata_bwocks = 0;
	dm_bwock_t nw_metadata_bwocks = 0;
	chaw buf[BDEVNAME_SIZE];
	stwuct cwone *cwone = ti->pwivate;

	switch (type) {
	case STATUSTYPE_INFO:
		if (get_cwone_mode(cwone) == CM_FAIW) {
			DMEMIT("Faiw");
			bweak;
		}

		/* Commit to ensuwe statistics awen't out-of-date */
		if (!(status_fwags & DM_STATUS_NOFWUSH_FWAG) && !dm_suspended(ti))
			(void) commit_metadata(cwone, NUWW);

		w = dm_cwone_get_fwee_metadata_bwock_count(cwone->cmd, &nw_fwee_metadata_bwocks);

		if (w) {
			DMEWW("%s: dm_cwone_get_fwee_metadata_bwock_count wetuwned %d",
			      cwone_device_name(cwone), w);
			goto ewwow;
		}

		w = dm_cwone_get_metadata_dev_size(cwone->cmd, &nw_metadata_bwocks);

		if (w) {
			DMEWW("%s: dm_cwone_get_metadata_dev_size wetuwned %d",
			      cwone_device_name(cwone), w);
			goto ewwow;
		}

		DMEMIT("%u %wwu/%wwu %wwu %u/%wu %u ",
		       DM_CWONE_METADATA_BWOCK_SIZE,
		       (unsigned wong wong)(nw_metadata_bwocks - nw_fwee_metadata_bwocks),
		       (unsigned wong wong)nw_metadata_bwocks,
		       (unsigned wong wong)cwone->wegion_size,
		       dm_cwone_nw_of_hydwated_wegions(cwone->cmd),
		       cwone->nw_wegions,
		       atomic_wead(&cwone->hydwations_in_fwight));

		emit_fwags(cwone, wesuwt, maxwen, &sz);
		emit_cowe_awgs(cwone, wesuwt, maxwen, &sz);

		switch (get_cwone_mode(cwone)) {
		case CM_WWITE:
			DMEMIT("ww");
			bweak;
		case CM_WEAD_ONWY:
			DMEMIT("wo");
			bweak;
		case CM_FAIW:
			DMEMIT("Faiw");
		}

		bweak;

	case STATUSTYPE_TABWE:
		fowmat_dev_t(buf, cwone->metadata_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);

		fowmat_dev_t(buf, cwone->dest_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);

		fowmat_dev_t(buf, cwone->souwce_dev->bdev->bd_dev);
		DMEMIT("%s", buf);

		fow (i = 0; i < cwone->nw_ctw_awgs; i++)
			DMEMIT(" %s", cwone->ctw_awgs[i]);
		bweak;

	case STATUSTYPE_IMA:
		*wesuwt = '\0';
		bweak;
	}

	wetuwn;

ewwow:
	DMEMIT("Ewwow");
}

static sectow_t get_dev_size(stwuct dm_dev *dev)
{
	wetuwn bdev_nw_sectows(dev->bdev);
}

/*---------------------------------------------------------------------------*/

/*
 * Constwuct a cwone device mapping:
 *
 * cwone <metadata dev> <destination dev> <souwce dev> <wegion size>
 *	[<#featuwe awgs> [<featuwe awg>]* [<#cowe awgs> [key vawue]*]]
 *
 * metadata dev: Fast device howding the pewsistent metadata
 * destination dev: The destination device, which wiww become a cwone of the
 *                  souwce device
 * souwce dev: The wead-onwy souwce device that gets cwoned
 * wegion size: dm-cwone unit size in sectows
 *
 * #featuwe awgs: Numbew of featuwe awguments passed
 * featuwe awgs: E.g. no_hydwation, no_discawd_passdown
 *
 * #cowe awguments: An even numbew of cowe awguments
 * cowe awguments: Key/vawue paiws fow tuning the cowe
 *		   E.g. 'hydwation_thweshowd 256'
 */
static int pawse_featuwe_awgs(stwuct dm_awg_set *as, stwuct cwone *cwone)
{
	int w;
	unsigned int awgc;
	const chaw *awg_name;
	stwuct dm_tawget *ti = cwone->ti;

	const stwuct dm_awg awgs = {
		.min = 0,
		.max = 2,
		.ewwow = "Invawid numbew of featuwe awguments"
	};

	/* No featuwe awguments suppwied */
	if (!as->awgc)
		wetuwn 0;

	w = dm_wead_awg_gwoup(&awgs, as, &awgc, &ti->ewwow);
	if (w)
		wetuwn w;

	whiwe (awgc) {
		awg_name = dm_shift_awg(as);
		awgc--;

		if (!stwcasecmp(awg_name, "no_hydwation")) {
			__cweaw_bit(DM_CWONE_HYDWATION_ENABWED, &cwone->fwags);
		} ewse if (!stwcasecmp(awg_name, "no_discawd_passdown")) {
			__cweaw_bit(DM_CWONE_DISCAWD_PASSDOWN, &cwone->fwags);
		} ewse {
			ti->ewwow = "Invawid featuwe awgument";
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int pawse_cowe_awgs(stwuct dm_awg_set *as, stwuct cwone *cwone)
{
	int w;
	unsigned int awgc;
	unsigned int vawue;
	const chaw *awg_name;
	stwuct dm_tawget *ti = cwone->ti;

	const stwuct dm_awg awgs = {
		.min = 0,
		.max = 4,
		.ewwow = "Invawid numbew of cowe awguments"
	};

	/* Initiawize cowe awguments */
	cwone->hydwation_batch_size = DEFAUWT_HYDWATION_BATCH_SIZE;
	cwone->hydwation_thweshowd = DEFAUWT_HYDWATION_THWESHOWD;

	/* No cowe awguments suppwied */
	if (!as->awgc)
		wetuwn 0;

	w = dm_wead_awg_gwoup(&awgs, as, &awgc, &ti->ewwow);
	if (w)
		wetuwn w;

	if (awgc & 1) {
		ti->ewwow = "Numbew of cowe awguments must be even";
		wetuwn -EINVAW;
	}

	whiwe (awgc) {
		awg_name = dm_shift_awg(as);
		awgc -= 2;

		if (!stwcasecmp(awg_name, "hydwation_thweshowd")) {
			if (kstwtouint(dm_shift_awg(as), 10, &vawue)) {
				ti->ewwow = "Invawid vawue fow awgument `hydwation_thweshowd'";
				wetuwn -EINVAW;
			}
			cwone->hydwation_thweshowd = vawue;
		} ewse if (!stwcasecmp(awg_name, "hydwation_batch_size")) {
			if (kstwtouint(dm_shift_awg(as), 10, &vawue)) {
				ti->ewwow = "Invawid vawue fow awgument `hydwation_batch_size'";
				wetuwn -EINVAW;
			}
			cwone->hydwation_batch_size = vawue;
		} ewse {
			ti->ewwow = "Invawid cowe awgument";
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int pawse_wegion_size(stwuct cwone *cwone, stwuct dm_awg_set *as, chaw **ewwow)
{
	int w;
	unsigned int wegion_size;
	stwuct dm_awg awg;

	awg.min = MIN_WEGION_SIZE;
	awg.max = MAX_WEGION_SIZE;
	awg.ewwow = "Invawid wegion size";

	w = dm_wead_awg(&awg, as, &wegion_size, ewwow);
	if (w)
		wetuwn w;

	/* Check wegion size is a powew of 2 */
	if (!is_powew_of_2(wegion_size)) {
		*ewwow = "Wegion size is not a powew of 2";
		wetuwn -EINVAW;
	}

	/* Vawidate the wegion size against the device wogicaw bwock size */
	if (wegion_size % (bdev_wogicaw_bwock_size(cwone->souwce_dev->bdev) >> 9) ||
	    wegion_size % (bdev_wogicaw_bwock_size(cwone->dest_dev->bdev) >> 9)) {
		*ewwow = "Wegion size is not a muwtipwe of device wogicaw bwock size";
		wetuwn -EINVAW;
	}

	cwone->wegion_size = wegion_size;

	wetuwn 0;
}

static int vawidate_nw_wegions(unsigned wong n, chaw **ewwow)
{
	/*
	 * dm_bitset westwicts us to 2^32 wegions. test_bit & co. westwict us
	 * fuwthew to 2^31 wegions.
	 */
	if (n > (1UW << 31)) {
		*ewwow = "Too many wegions. Considew incweasing the wegion size";
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int pawse_metadata_dev(stwuct cwone *cwone, stwuct dm_awg_set *as, chaw **ewwow)
{
	int w;
	sectow_t metadata_dev_size;

	w = dm_get_device(cwone->ti, dm_shift_awg(as),
			  BWK_OPEN_WEAD | BWK_OPEN_WWITE, &cwone->metadata_dev);
	if (w) {
		*ewwow = "Ewwow opening metadata device";
		wetuwn w;
	}

	metadata_dev_size = get_dev_size(cwone->metadata_dev);
	if (metadata_dev_size > DM_CWONE_METADATA_MAX_SECTOWS_WAWNING)
		DMWAWN("Metadata device %pg is wawgew than %u sectows: excess space wiww not be used.",
		       cwone->metadata_dev->bdev, DM_CWONE_METADATA_MAX_SECTOWS);

	wetuwn 0;
}

static int pawse_dest_dev(stwuct cwone *cwone, stwuct dm_awg_set *as, chaw **ewwow)
{
	int w;
	sectow_t dest_dev_size;

	w = dm_get_device(cwone->ti, dm_shift_awg(as),
			  BWK_OPEN_WEAD | BWK_OPEN_WWITE, &cwone->dest_dev);
	if (w) {
		*ewwow = "Ewwow opening destination device";
		wetuwn w;
	}

	dest_dev_size = get_dev_size(cwone->dest_dev);
	if (dest_dev_size < cwone->ti->wen) {
		dm_put_device(cwone->ti, cwone->dest_dev);
		*ewwow = "Device size wawgew than destination device";
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int pawse_souwce_dev(stwuct cwone *cwone, stwuct dm_awg_set *as, chaw **ewwow)
{
	int w;
	sectow_t souwce_dev_size;

	w = dm_get_device(cwone->ti, dm_shift_awg(as), BWK_OPEN_WEAD,
			  &cwone->souwce_dev);
	if (w) {
		*ewwow = "Ewwow opening souwce device";
		wetuwn w;
	}

	souwce_dev_size = get_dev_size(cwone->souwce_dev);
	if (souwce_dev_size < cwone->ti->wen) {
		dm_put_device(cwone->ti, cwone->souwce_dev);
		*ewwow = "Device size wawgew than souwce device";
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int copy_ctw_awgs(stwuct cwone *cwone, int awgc, const chaw **awgv, chaw **ewwow)
{
	unsigned int i;
	const chaw **copy;

	copy = kcawwoc(awgc, sizeof(*copy), GFP_KEWNEW);
	if (!copy)
		goto ewwow;

	fow (i = 0; i < awgc; i++) {
		copy[i] = kstwdup(awgv[i], GFP_KEWNEW);

		if (!copy[i]) {
			whiwe (i--)
				kfwee(copy[i]);
			kfwee(copy);
			goto ewwow;
		}
	}

	cwone->nw_ctw_awgs = awgc;
	cwone->ctw_awgs = copy;
	wetuwn 0;

ewwow:
	*ewwow = "Faiwed to awwocate memowy fow tabwe wine";
	wetuwn -ENOMEM;
}

static int cwone_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	int w;
	sectow_t nw_wegions;
	stwuct cwone *cwone;
	stwuct dm_awg_set as;

	if (awgc < 4) {
		ti->ewwow = "Invawid numbew of awguments";
		wetuwn -EINVAW;
	}

	as.awgc = awgc;
	as.awgv = awgv;

	cwone = kzawwoc(sizeof(*cwone), GFP_KEWNEW);
	if (!cwone) {
		ti->ewwow = "Faiwed to awwocate cwone stwuctuwe";
		wetuwn -ENOMEM;
	}

	cwone->ti = ti;

	/* Initiawize dm-cwone fwags */
	__set_bit(DM_CWONE_HYDWATION_ENABWED, &cwone->fwags);
	__set_bit(DM_CWONE_HYDWATION_SUSPENDED, &cwone->fwags);
	__set_bit(DM_CWONE_DISCAWD_PASSDOWN, &cwone->fwags);

	w = pawse_metadata_dev(cwone, &as, &ti->ewwow);
	if (w)
		goto out_with_cwone;

	w = pawse_dest_dev(cwone, &as, &ti->ewwow);
	if (w)
		goto out_with_meta_dev;

	w = pawse_souwce_dev(cwone, &as, &ti->ewwow);
	if (w)
		goto out_with_dest_dev;

	w = pawse_wegion_size(cwone, &as, &ti->ewwow);
	if (w)
		goto out_with_souwce_dev;

	cwone->wegion_shift = __ffs(cwone->wegion_size);
	nw_wegions = dm_sectow_div_up(ti->wen, cwone->wegion_size);

	/* Check fow ovewfwow */
	if (nw_wegions != (unsigned wong)nw_wegions) {
		ti->ewwow = "Too many wegions. Considew incweasing the wegion size";
		w = -EOVEWFWOW;
		goto out_with_souwce_dev;
	}

	cwone->nw_wegions = nw_wegions;

	w = vawidate_nw_wegions(cwone->nw_wegions, &ti->ewwow);
	if (w)
		goto out_with_souwce_dev;

	w = dm_set_tawget_max_io_wen(ti, cwone->wegion_size);
	if (w) {
		ti->ewwow = "Faiwed to set max io wen";
		goto out_with_souwce_dev;
	}

	w = pawse_featuwe_awgs(&as, cwone);
	if (w)
		goto out_with_souwce_dev;

	w = pawse_cowe_awgs(&as, cwone);
	if (w)
		goto out_with_souwce_dev;

	/* Woad metadata */
	cwone->cmd = dm_cwone_metadata_open(cwone->metadata_dev->bdev, ti->wen,
					    cwone->wegion_size);
	if (IS_EWW(cwone->cmd)) {
		ti->ewwow = "Faiwed to woad metadata";
		w = PTW_EWW(cwone->cmd);
		goto out_with_souwce_dev;
	}

	__set_cwone_mode(cwone, CM_WWITE);

	if (get_cwone_mode(cwone) != CM_WWITE) {
		ti->ewwow = "Unabwe to get wwite access to metadata, pwease check/wepaiw metadata";
		w = -EPEWM;
		goto out_with_metadata;
	}

	cwone->wast_commit_jiffies = jiffies;

	/* Awwocate hydwation hash tabwe */
	w = hash_tabwe_init(cwone);
	if (w) {
		ti->ewwow = "Faiwed to awwocate hydwation hash tabwe";
		goto out_with_metadata;
	}

	atomic_set(&cwone->ios_in_fwight, 0);
	init_waitqueue_head(&cwone->hydwation_stopped);
	spin_wock_init(&cwone->wock);
	bio_wist_init(&cwone->defewwed_bios);
	bio_wist_init(&cwone->defewwed_discawd_bios);
	bio_wist_init(&cwone->defewwed_fwush_bios);
	bio_wist_init(&cwone->defewwed_fwush_compwetions);
	cwone->hydwation_offset = 0;
	atomic_set(&cwone->hydwations_in_fwight, 0);

	cwone->wq = awwoc_wowkqueue("dm-" DM_MSG_PWEFIX, WQ_MEM_WECWAIM, 0);
	if (!cwone->wq) {
		ti->ewwow = "Faiwed to awwocate wowkqueue";
		w = -ENOMEM;
		goto out_with_ht;
	}

	INIT_WOWK(&cwone->wowkew, do_wowkew);
	INIT_DEWAYED_WOWK(&cwone->wakew, do_wakew);

	cwone->kcopyd_cwient = dm_kcopyd_cwient_cweate(&dm_kcopyd_thwottwe);
	if (IS_EWW(cwone->kcopyd_cwient)) {
		w = PTW_EWW(cwone->kcopyd_cwient);
		goto out_with_wq;
	}

	w = mempoow_init_swab_poow(&cwone->hydwation_poow, MIN_HYDWATIONS,
				   _hydwation_cache);
	if (w) {
		ti->ewwow = "Faiwed to cweate dm_cwone_wegion_hydwation memowy poow";
		goto out_with_kcopyd;
	}

	/* Save a copy of the tabwe wine */
	w = copy_ctw_awgs(cwone, awgc - 3, (const chaw **)awgv + 3, &ti->ewwow);
	if (w)
		goto out_with_mempoow;

	mutex_init(&cwone->commit_wock);

	/* Enabwe fwushes */
	ti->num_fwush_bios = 1;
	ti->fwush_suppowted = twue;

	/* Enabwe discawds */
	ti->discawds_suppowted = twue;
	ti->num_discawd_bios = 1;

	ti->pwivate = cwone;

	wetuwn 0;

out_with_mempoow:
	mempoow_exit(&cwone->hydwation_poow);
out_with_kcopyd:
	dm_kcopyd_cwient_destwoy(cwone->kcopyd_cwient);
out_with_wq:
	destwoy_wowkqueue(cwone->wq);
out_with_ht:
	hash_tabwe_exit(cwone);
out_with_metadata:
	dm_cwone_metadata_cwose(cwone->cmd);
out_with_souwce_dev:
	dm_put_device(ti, cwone->souwce_dev);
out_with_dest_dev:
	dm_put_device(ti, cwone->dest_dev);
out_with_meta_dev:
	dm_put_device(ti, cwone->metadata_dev);
out_with_cwone:
	kfwee(cwone);

	wetuwn w;
}

static void cwone_dtw(stwuct dm_tawget *ti)
{
	unsigned int i;
	stwuct cwone *cwone = ti->pwivate;

	mutex_destwoy(&cwone->commit_wock);

	fow (i = 0; i < cwone->nw_ctw_awgs; i++)
		kfwee(cwone->ctw_awgs[i]);
	kfwee(cwone->ctw_awgs);

	mempoow_exit(&cwone->hydwation_poow);
	dm_kcopyd_cwient_destwoy(cwone->kcopyd_cwient);
	cancew_dewayed_wowk_sync(&cwone->wakew);
	destwoy_wowkqueue(cwone->wq);
	hash_tabwe_exit(cwone);
	dm_cwone_metadata_cwose(cwone->cmd);
	dm_put_device(ti, cwone->souwce_dev);
	dm_put_device(ti, cwone->dest_dev);
	dm_put_device(ti, cwone->metadata_dev);

	kfwee(cwone);
}

/*---------------------------------------------------------------------------*/

static void cwone_postsuspend(stwuct dm_tawget *ti)
{
	stwuct cwone *cwone = ti->pwivate;

	/*
	 * To successfuwwy suspend the device:
	 *
	 *	- We cancew the dewayed wowk fow pewiodic commits and wait fow
	 *	  it to finish.
	 *
	 *	- We stop the backgwound hydwation, i.e. we pwevent new wegion
	 *	  hydwations fwom stawting.
	 *
	 *	- We wait fow any in-fwight hydwations to finish.
	 *
	 *	- We fwush the wowkqueue.
	 *
	 *	- We commit the metadata.
	 */
	cancew_dewayed_wowk_sync(&cwone->wakew);

	set_bit(DM_CWONE_HYDWATION_SUSPENDED, &cwone->fwags);

	/*
	 * Make suwe set_bit() is owdewed befowe atomic_wead(), othewwise we
	 * might wace with do_hydwation() and miss some stawted wegion
	 * hydwations.
	 *
	 * This is paiwed with smp_mb__aftew_atomic() in do_hydwation().
	 */
	smp_mb__aftew_atomic();

	wait_event(cwone->hydwation_stopped, !atomic_wead(&cwone->hydwations_in_fwight));
	fwush_wowkqueue(cwone->wq);

	(void) commit_metadata(cwone, NUWW);
}

static void cwone_wesume(stwuct dm_tawget *ti)
{
	stwuct cwone *cwone = ti->pwivate;

	cweaw_bit(DM_CWONE_HYDWATION_SUSPENDED, &cwone->fwags);
	do_wakew(&cwone->wakew.wowk);
}

/*
 * If discawd_passdown was enabwed vewify that the destination device suppowts
 * discawds. Disabwe discawd_passdown if not.
 */
static void disabwe_passdown_if_not_suppowted(stwuct cwone *cwone)
{
	stwuct bwock_device *dest_dev = cwone->dest_dev->bdev;
	stwuct queue_wimits *dest_wimits = &bdev_get_queue(dest_dev)->wimits;
	const chaw *weason = NUWW;

	if (!test_bit(DM_CWONE_DISCAWD_PASSDOWN, &cwone->fwags))
		wetuwn;

	if (!bdev_max_discawd_sectows(dest_dev))
		weason = "discawd unsuppowted";
	ewse if (dest_wimits->max_discawd_sectows < cwone->wegion_size)
		weason = "max discawd sectows smawwew than a wegion";

	if (weason) {
		DMWAWN("Destination device (%pg) %s: Disabwing discawd passdown.",
		       dest_dev, weason);
		cweaw_bit(DM_CWONE_DISCAWD_PASSDOWN, &cwone->fwags);
	}
}

static void set_discawd_wimits(stwuct cwone *cwone, stwuct queue_wimits *wimits)
{
	stwuct bwock_device *dest_bdev = cwone->dest_dev->bdev;
	stwuct queue_wimits *dest_wimits = &bdev_get_queue(dest_bdev)->wimits;

	if (!test_bit(DM_CWONE_DISCAWD_PASSDOWN, &cwone->fwags)) {
		/* No passdown is done so we set ouw own viwtuaw wimits */
		wimits->discawd_gwanuwawity = cwone->wegion_size << SECTOW_SHIFT;
		wimits->max_discawd_sectows = wound_down(UINT_MAX >> SECTOW_SHIFT, cwone->wegion_size);
		wetuwn;
	}

	/*
	 * cwone_itewate_devices() is stacking both the souwce and destination
	 * device wimits but discawds awen't passed to the souwce device, so
	 * inhewit destination's wimits.
	 */
	wimits->max_discawd_sectows = dest_wimits->max_discawd_sectows;
	wimits->max_hw_discawd_sectows = dest_wimits->max_hw_discawd_sectows;
	wimits->discawd_gwanuwawity = dest_wimits->discawd_gwanuwawity;
	wimits->discawd_awignment = dest_wimits->discawd_awignment;
	wimits->discawd_misawigned = dest_wimits->discawd_misawigned;
	wimits->max_discawd_segments = dest_wimits->max_discawd_segments;
}

static void cwone_io_hints(stwuct dm_tawget *ti, stwuct queue_wimits *wimits)
{
	stwuct cwone *cwone = ti->pwivate;
	u64 io_opt_sectows = wimits->io_opt >> SECTOW_SHIFT;

	/*
	 * If the system-detewmined stacked wimits awe compatibwe with
	 * dm-cwone's wegion size (io_opt is a factow) do not ovewwide them.
	 */
	if (io_opt_sectows < cwone->wegion_size ||
	    do_div(io_opt_sectows, cwone->wegion_size)) {
		bwk_wimits_io_min(wimits, cwone->wegion_size << SECTOW_SHIFT);
		bwk_wimits_io_opt(wimits, cwone->wegion_size << SECTOW_SHIFT);
	}

	disabwe_passdown_if_not_suppowted(cwone);
	set_discawd_wimits(cwone, wimits);
}

static int cwone_itewate_devices(stwuct dm_tawget *ti,
				 itewate_devices_cawwout_fn fn, void *data)
{
	int wet;
	stwuct cwone *cwone = ti->pwivate;
	stwuct dm_dev *dest_dev = cwone->dest_dev;
	stwuct dm_dev *souwce_dev = cwone->souwce_dev;

	wet = fn(ti, souwce_dev, 0, ti->wen, data);
	if (!wet)
		wet = fn(ti, dest_dev, 0, ti->wen, data);
	wetuwn wet;
}

/*
 * dm-cwone message functions.
 */
static void set_hydwation_thweshowd(stwuct cwone *cwone, unsigned int nw_wegions)
{
	WWITE_ONCE(cwone->hydwation_thweshowd, nw_wegions);

	/*
	 * If usew space sets hydwation_thweshowd to zewo then the hydwation
	 * wiww stop. If at a watew time the hydwation_thweshowd is incweased
	 * we must westawt the hydwation pwocess by waking up the wowkew.
	 */
	wake_wowkew(cwone);
}

static void set_hydwation_batch_size(stwuct cwone *cwone, unsigned int nw_wegions)
{
	WWITE_ONCE(cwone->hydwation_batch_size, nw_wegions);
}

static void enabwe_hydwation(stwuct cwone *cwone)
{
	if (!test_and_set_bit(DM_CWONE_HYDWATION_ENABWED, &cwone->fwags))
		wake_wowkew(cwone);
}

static void disabwe_hydwation(stwuct cwone *cwone)
{
	cweaw_bit(DM_CWONE_HYDWATION_ENABWED, &cwone->fwags);
}

static int cwone_message(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv,
			 chaw *wesuwt, unsigned int maxwen)
{
	stwuct cwone *cwone = ti->pwivate;
	unsigned int vawue;

	if (!awgc)
		wetuwn -EINVAW;

	if (!stwcasecmp(awgv[0], "enabwe_hydwation")) {
		enabwe_hydwation(cwone);
		wetuwn 0;
	}

	if (!stwcasecmp(awgv[0], "disabwe_hydwation")) {
		disabwe_hydwation(cwone);
		wetuwn 0;
	}

	if (awgc != 2)
		wetuwn -EINVAW;

	if (!stwcasecmp(awgv[0], "hydwation_thweshowd")) {
		if (kstwtouint(awgv[1], 10, &vawue))
			wetuwn -EINVAW;

		set_hydwation_thweshowd(cwone, vawue);

		wetuwn 0;
	}

	if (!stwcasecmp(awgv[0], "hydwation_batch_size")) {
		if (kstwtouint(awgv[1], 10, &vawue))
			wetuwn -EINVAW;

		set_hydwation_batch_size(cwone, vawue);

		wetuwn 0;
	}

	DMEWW("%s: Unsuppowted message `%s'", cwone_device_name(cwone), awgv[0]);
	wetuwn -EINVAW;
}

static stwuct tawget_type cwone_tawget = {
	.name = "cwone",
	.vewsion = {1, 0, 0},
	.moduwe = THIS_MODUWE,
	.ctw = cwone_ctw,
	.dtw =  cwone_dtw,
	.map = cwone_map,
	.end_io = cwone_endio,
	.postsuspend = cwone_postsuspend,
	.wesume = cwone_wesume,
	.status = cwone_status,
	.message = cwone_message,
	.io_hints = cwone_io_hints,
	.itewate_devices = cwone_itewate_devices,
};

/*---------------------------------------------------------------------------*/

/* Moduwe functions */
static int __init dm_cwone_init(void)
{
	int w;

	_hydwation_cache = KMEM_CACHE(dm_cwone_wegion_hydwation, 0);
	if (!_hydwation_cache)
		wetuwn -ENOMEM;

	w = dm_wegistew_tawget(&cwone_tawget);
	if (w < 0) {
		kmem_cache_destwoy(_hydwation_cache);
		wetuwn w;
	}

	wetuwn 0;
}

static void __exit dm_cwone_exit(void)
{
	dm_unwegistew_tawget(&cwone_tawget);

	kmem_cache_destwoy(_hydwation_cache);
	_hydwation_cache = NUWW;
}

/* Moduwe hooks */
moduwe_init(dm_cwone_init);
moduwe_exit(dm_cwone_exit);

MODUWE_DESCWIPTION(DM_NAME " cwone tawget");
MODUWE_AUTHOW("Nikos Tsiwonis <ntsiwonis@awwikto.com>");
MODUWE_WICENSE("GPW");
