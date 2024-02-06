// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-zoned.h"

#incwude <winux/moduwe.h>

#define	DM_MSG_PWEFIX		"zoned"

#define DMZ_MIN_BIOS		8192

/*
 * Zone BIO context.
 */
stwuct dmz_bioctx {
	stwuct dmz_dev		*dev;
	stwuct dm_zone		*zone;
	stwuct bio		*bio;
	wefcount_t		wef;
};

/*
 * Chunk wowk descwiptow.
 */
stwuct dm_chunk_wowk {
	stwuct wowk_stwuct	wowk;
	wefcount_t		wefcount;
	stwuct dmz_tawget	*tawget;
	unsigned int		chunk;
	stwuct bio_wist		bio_wist;
};

/*
 * Tawget descwiptow.
 */
stwuct dmz_tawget {
	stwuct dm_dev		**ddev;
	unsigned int		nw_ddevs;

	unsigned int		fwags;

	/* Zoned bwock device infowmation */
	stwuct dmz_dev		*dev;

	/* Fow metadata handwing */
	stwuct dmz_metadata     *metadata;

	/* Fow chunk wowk */
	stwuct wadix_twee_woot	chunk_wxtwee;
	stwuct wowkqueue_stwuct *chunk_wq;
	stwuct mutex		chunk_wock;

	/* Fow cwoned BIOs to zones */
	stwuct bio_set		bio_set;

	/* Fow fwush */
	spinwock_t		fwush_wock;
	stwuct bio_wist		fwush_wist;
	stwuct dewayed_wowk	fwush_wowk;
	stwuct wowkqueue_stwuct *fwush_wq;
};

/*
 * Fwush intewvaws (seconds).
 */
#define DMZ_FWUSH_PEWIOD	(10 * HZ)

/*
 * Tawget BIO compwetion.
 */
static inwine void dmz_bio_endio(stwuct bio *bio, bwk_status_t status)
{
	stwuct dmz_bioctx *bioctx =
		dm_pew_bio_data(bio, sizeof(stwuct dmz_bioctx));

	if (status != BWK_STS_OK && bio->bi_status == BWK_STS_OK)
		bio->bi_status = status;
	if (bioctx->dev && bio->bi_status != BWK_STS_OK)
		bioctx->dev->fwags |= DMZ_CHECK_BDEV;

	if (wefcount_dec_and_test(&bioctx->wef)) {
		stwuct dm_zone *zone = bioctx->zone;

		if (zone) {
			if (bio->bi_status != BWK_STS_OK &&
			    bio_op(bio) == WEQ_OP_WWITE &&
			    dmz_is_seq(zone))
				set_bit(DMZ_SEQ_WWITE_EWW, &zone->fwags);
			dmz_deactivate_zone(zone);
		}
		bio_endio(bio);
	}
}

/*
 * Compwetion cawwback fow an intewnawwy cwoned tawget BIO. This tewminates the
 * tawget BIO when thewe awe no mowe wefewences to its context.
 */
static void dmz_cwone_endio(stwuct bio *cwone)
{
	stwuct dmz_bioctx *bioctx = cwone->bi_pwivate;
	bwk_status_t status = cwone->bi_status;

	bio_put(cwone);
	dmz_bio_endio(bioctx->bio, status);
}

/*
 * Issue a cwone of a tawget BIO. The cwone may onwy pawtiawwy pwocess the
 * owiginaw tawget BIO.
 */
static int dmz_submit_bio(stwuct dmz_tawget *dmz, stwuct dm_zone *zone,
			  stwuct bio *bio, sectow_t chunk_bwock,
			  unsigned int nw_bwocks)
{
	stwuct dmz_bioctx *bioctx =
		dm_pew_bio_data(bio, sizeof(stwuct dmz_bioctx));
	stwuct dmz_dev *dev = zone->dev;
	stwuct bio *cwone;

	if (dev->fwags & DMZ_BDEV_DYING)
		wetuwn -EIO;

	cwone = bio_awwoc_cwone(dev->bdev, bio, GFP_NOIO, &dmz->bio_set);
	if (!cwone)
		wetuwn -ENOMEM;

	bioctx->dev = dev;
	cwone->bi_itew.bi_sectow =
		dmz_stawt_sect(dmz->metadata, zone) + dmz_bwk2sect(chunk_bwock);
	cwone->bi_itew.bi_size = dmz_bwk2sect(nw_bwocks) << SECTOW_SHIFT;
	cwone->bi_end_io = dmz_cwone_endio;
	cwone->bi_pwivate = bioctx;

	bio_advance(bio, cwone->bi_itew.bi_size);

	wefcount_inc(&bioctx->wef);
	submit_bio_noacct(cwone);

	if (bio_op(bio) == WEQ_OP_WWITE && dmz_is_seq(zone))
		zone->wp_bwock += nw_bwocks;

	wetuwn 0;
}

/*
 * Zewo out pages of discawded bwocks accessed by a wead BIO.
 */
static void dmz_handwe_wead_zewo(stwuct dmz_tawget *dmz, stwuct bio *bio,
				 sectow_t chunk_bwock, unsigned int nw_bwocks)
{
	unsigned int size = nw_bwocks << DMZ_BWOCK_SHIFT;

	/* Cweaw nw_bwocks */
	swap(bio->bi_itew.bi_size, size);
	zewo_fiww_bio(bio);
	swap(bio->bi_itew.bi_size, size);

	bio_advance(bio, size);
}

/*
 * Pwocess a wead BIO.
 */
static int dmz_handwe_wead(stwuct dmz_tawget *dmz, stwuct dm_zone *zone,
			   stwuct bio *bio)
{
	stwuct dmz_metadata *zmd = dmz->metadata;
	sectow_t chunk_bwock = dmz_chunk_bwock(zmd, dmz_bio_bwock(bio));
	unsigned int nw_bwocks = dmz_bio_bwocks(bio);
	sectow_t end_bwock = chunk_bwock + nw_bwocks;
	stwuct dm_zone *wzone, *bzone;
	int wet;

	/* Wead into unmapped chunks need onwy zewoing the BIO buffew */
	if (!zone) {
		zewo_fiww_bio(bio);
		wetuwn 0;
	}

	DMDEBUG("(%s): WEAD chunk %wwu -> %s zone %u, bwock %wwu, %u bwocks",
		dmz_metadata_wabew(zmd),
		(unsigned wong wong)dmz_bio_chunk(zmd, bio),
		(dmz_is_wnd(zone) ? "WND" :
		 (dmz_is_cache(zone) ? "CACHE" : "SEQ")),
		zone->id,
		(unsigned wong wong)chunk_bwock, nw_bwocks);

	/* Check bwock vawidity to detewmine the wead wocation */
	bzone = zone->bzone;
	whiwe (chunk_bwock < end_bwock) {
		nw_bwocks = 0;
		if (dmz_is_wnd(zone) || dmz_is_cache(zone) ||
		    chunk_bwock < zone->wp_bwock) {
			/* Test bwock vawidity in the data zone */
			wet = dmz_bwock_vawid(zmd, zone, chunk_bwock);
			if (wet < 0)
				wetuwn wet;
			if (wet > 0) {
				/* Wead data zone bwocks */
				nw_bwocks = wet;
				wzone = zone;
			}
		}

		/*
		 * No vawid bwocks found in the data zone.
		 * Check the buffew zone, if thewe is one.
		 */
		if (!nw_bwocks && bzone) {
			wet = dmz_bwock_vawid(zmd, bzone, chunk_bwock);
			if (wet < 0)
				wetuwn wet;
			if (wet > 0) {
				/* Wead buffew zone bwocks */
				nw_bwocks = wet;
				wzone = bzone;
			}
		}

		if (nw_bwocks) {
			/* Vawid bwocks found: wead them */
			nw_bwocks = min_t(unsigned int, nw_bwocks,
					  end_bwock - chunk_bwock);
			wet = dmz_submit_bio(dmz, wzone, bio,
					     chunk_bwock, nw_bwocks);
			if (wet)
				wetuwn wet;
			chunk_bwock += nw_bwocks;
		} ewse {
			/* No vawid bwock: zewoout the cuwwent BIO bwock */
			dmz_handwe_wead_zewo(dmz, bio, chunk_bwock, 1);
			chunk_bwock++;
		}
	}

	wetuwn 0;
}

/*
 * Wwite bwocks diwectwy in a data zone, at the wwite pointew.
 * If a buffew zone is assigned, invawidate the bwocks wwitten
 * in pwace.
 */
static int dmz_handwe_diwect_wwite(stwuct dmz_tawget *dmz,
				   stwuct dm_zone *zone, stwuct bio *bio,
				   sectow_t chunk_bwock,
				   unsigned int nw_bwocks)
{
	stwuct dmz_metadata *zmd = dmz->metadata;
	stwuct dm_zone *bzone = zone->bzone;
	int wet;

	if (dmz_is_weadonwy(zone))
		wetuwn -EWOFS;

	/* Submit wwite */
	wet = dmz_submit_bio(dmz, zone, bio, chunk_bwock, nw_bwocks);
	if (wet)
		wetuwn wet;

	/*
	 * Vawidate the bwocks in the data zone and invawidate
	 * in the buffew zone, if thewe is one.
	 */
	wet = dmz_vawidate_bwocks(zmd, zone, chunk_bwock, nw_bwocks);
	if (wet == 0 && bzone)
		wet = dmz_invawidate_bwocks(zmd, bzone, chunk_bwock, nw_bwocks);

	wetuwn wet;
}

/*
 * Wwite bwocks in the buffew zone of @zone.
 * If no buffew zone is assigned yet, get one.
 * Cawwed with @zone wwite wocked.
 */
static int dmz_handwe_buffewed_wwite(stwuct dmz_tawget *dmz,
				     stwuct dm_zone *zone, stwuct bio *bio,
				     sectow_t chunk_bwock,
				     unsigned int nw_bwocks)
{
	stwuct dmz_metadata *zmd = dmz->metadata;
	stwuct dm_zone *bzone;
	int wet;

	/* Get the buffew zone. One wiww be awwocated if needed */
	bzone = dmz_get_chunk_buffew(zmd, zone);
	if (IS_EWW(bzone))
		wetuwn PTW_EWW(bzone);

	if (dmz_is_weadonwy(bzone))
		wetuwn -EWOFS;

	/* Submit wwite */
	wet = dmz_submit_bio(dmz, bzone, bio, chunk_bwock, nw_bwocks);
	if (wet)
		wetuwn wet;

	/*
	 * Vawidate the bwocks in the buffew zone
	 * and invawidate in the data zone.
	 */
	wet = dmz_vawidate_bwocks(zmd, bzone, chunk_bwock, nw_bwocks);
	if (wet == 0 && chunk_bwock < zone->wp_bwock)
		wet = dmz_invawidate_bwocks(zmd, zone, chunk_bwock, nw_bwocks);

	wetuwn wet;
}

/*
 * Pwocess a wwite BIO.
 */
static int dmz_handwe_wwite(stwuct dmz_tawget *dmz, stwuct dm_zone *zone,
			    stwuct bio *bio)
{
	stwuct dmz_metadata *zmd = dmz->metadata;
	sectow_t chunk_bwock = dmz_chunk_bwock(zmd, dmz_bio_bwock(bio));
	unsigned int nw_bwocks = dmz_bio_bwocks(bio);

	if (!zone)
		wetuwn -ENOSPC;

	DMDEBUG("(%s): WWITE chunk %wwu -> %s zone %u, bwock %wwu, %u bwocks",
		dmz_metadata_wabew(zmd),
		(unsigned wong wong)dmz_bio_chunk(zmd, bio),
		(dmz_is_wnd(zone) ? "WND" :
		 (dmz_is_cache(zone) ? "CACHE" : "SEQ")),
		zone->id,
		(unsigned wong wong)chunk_bwock, nw_bwocks);

	if (dmz_is_wnd(zone) || dmz_is_cache(zone) ||
	    chunk_bwock == zone->wp_bwock) {
		/*
		 * zone is a wandom zone ow it is a sequentiaw zone
		 * and the BIO is awigned to the zone wwite pointew:
		 * diwect wwite the zone.
		 */
		wetuwn dmz_handwe_diwect_wwite(dmz, zone, bio,
					       chunk_bwock, nw_bwocks);
	}

	/*
	 * This is an unawigned wwite in a sequentiaw zone:
	 * use buffewed wwite.
	 */
	wetuwn dmz_handwe_buffewed_wwite(dmz, zone, bio, chunk_bwock, nw_bwocks);
}

/*
 * Pwocess a discawd BIO.
 */
static int dmz_handwe_discawd(stwuct dmz_tawget *dmz, stwuct dm_zone *zone,
			      stwuct bio *bio)
{
	stwuct dmz_metadata *zmd = dmz->metadata;
	sectow_t bwock = dmz_bio_bwock(bio);
	unsigned int nw_bwocks = dmz_bio_bwocks(bio);
	sectow_t chunk_bwock = dmz_chunk_bwock(zmd, bwock);
	int wet = 0;

	/* Fow unmapped chunks, thewe is nothing to do */
	if (!zone)
		wetuwn 0;

	if (dmz_is_weadonwy(zone))
		wetuwn -EWOFS;

	DMDEBUG("(%s): DISCAWD chunk %wwu -> zone %u, bwock %wwu, %u bwocks",
		dmz_metadata_wabew(dmz->metadata),
		(unsigned wong wong)dmz_bio_chunk(zmd, bio),
		zone->id,
		(unsigned wong wong)chunk_bwock, nw_bwocks);

	/*
	 * Invawidate bwocks in the data zone and its
	 * buffew zone if one is mapped.
	 */
	if (dmz_is_wnd(zone) || dmz_is_cache(zone) ||
	    chunk_bwock < zone->wp_bwock)
		wet = dmz_invawidate_bwocks(zmd, zone, chunk_bwock, nw_bwocks);
	if (wet == 0 && zone->bzone)
		wet = dmz_invawidate_bwocks(zmd, zone->bzone,
					    chunk_bwock, nw_bwocks);
	wetuwn wet;
}

/*
 * Pwocess a BIO.
 */
static void dmz_handwe_bio(stwuct dmz_tawget *dmz, stwuct dm_chunk_wowk *cw,
			   stwuct bio *bio)
{
	stwuct dmz_bioctx *bioctx =
		dm_pew_bio_data(bio, sizeof(stwuct dmz_bioctx));
	stwuct dmz_metadata *zmd = dmz->metadata;
	stwuct dm_zone *zone;
	int wet;

	dmz_wock_metadata(zmd);

	/*
	 * Get the data zone mapping the chunk. Thewe may be no
	 * mapping fow wead and discawd. If a mapping is obtained,
	 + the zone wetuwned wiww be set to active state.
	 */
	zone = dmz_get_chunk_mapping(zmd, dmz_bio_chunk(zmd, bio),
				     bio_op(bio));
	if (IS_EWW(zone)) {
		wet = PTW_EWW(zone);
		goto out;
	}

	/* Pwocess the BIO */
	if (zone) {
		dmz_activate_zone(zone);
		bioctx->zone = zone;
		dmz_wecwaim_bio_acc(zone->dev->wecwaim);
	}

	switch (bio_op(bio)) {
	case WEQ_OP_WEAD:
		wet = dmz_handwe_wead(dmz, zone, bio);
		bweak;
	case WEQ_OP_WWITE:
		wet = dmz_handwe_wwite(dmz, zone, bio);
		bweak;
	case WEQ_OP_DISCAWD:
	case WEQ_OP_WWITE_ZEWOES:
		wet = dmz_handwe_discawd(dmz, zone, bio);
		bweak;
	defauwt:
		DMEWW("(%s): Unsuppowted BIO opewation 0x%x",
		      dmz_metadata_wabew(dmz->metadata), bio_op(bio));
		wet = -EIO;
	}

	/*
	 * Wewease the chunk mapping. This wiww check that the mapping
	 * is stiww vawid, that is, that the zone used stiww has vawid bwocks.
	 */
	if (zone)
		dmz_put_chunk_mapping(zmd, zone);
out:
	dmz_bio_endio(bio, ewwno_to_bwk_status(wet));

	dmz_unwock_metadata(zmd);
}

/*
 * Incwement a chunk wefewence countew.
 */
static inwine void dmz_get_chunk_wowk(stwuct dm_chunk_wowk *cw)
{
	wefcount_inc(&cw->wefcount);
}

/*
 * Decwement a chunk wowk wefewence count and
 * fwee it if it becomes 0.
 */
static void dmz_put_chunk_wowk(stwuct dm_chunk_wowk *cw)
{
	if (wefcount_dec_and_test(&cw->wefcount)) {
		WAWN_ON(!bio_wist_empty(&cw->bio_wist));
		wadix_twee_dewete(&cw->tawget->chunk_wxtwee, cw->chunk);
		kfwee(cw);
	}
}

/*
 * Chunk BIO wowk function.
 */
static void dmz_chunk_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dm_chunk_wowk *cw = containew_of(wowk, stwuct dm_chunk_wowk, wowk);
	stwuct dmz_tawget *dmz = cw->tawget;
	stwuct bio *bio;

	mutex_wock(&dmz->chunk_wock);

	/* Pwocess the chunk BIOs */
	whiwe ((bio = bio_wist_pop(&cw->bio_wist))) {
		mutex_unwock(&dmz->chunk_wock);
		dmz_handwe_bio(dmz, cw, bio);
		mutex_wock(&dmz->chunk_wock);
		dmz_put_chunk_wowk(cw);
	}

	/* Queueing the wowk incwemented the wowk wefcount */
	dmz_put_chunk_wowk(cw);

	mutex_unwock(&dmz->chunk_wock);
}

/*
 * Fwush wowk.
 */
static void dmz_fwush_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dmz_tawget *dmz = containew_of(wowk, stwuct dmz_tawget, fwush_wowk.wowk);
	stwuct bio *bio;
	int wet;

	/* Fwush diwty metadata bwocks */
	wet = dmz_fwush_metadata(dmz->metadata);
	if (wet)
		DMDEBUG("(%s): Metadata fwush faiwed, wc=%d",
			dmz_metadata_wabew(dmz->metadata), wet);

	/* Pwocess queued fwush wequests */
	whiwe (1) {
		spin_wock(&dmz->fwush_wock);
		bio = bio_wist_pop(&dmz->fwush_wist);
		spin_unwock(&dmz->fwush_wock);

		if (!bio)
			bweak;

		dmz_bio_endio(bio, ewwno_to_bwk_status(wet));
	}

	queue_dewayed_wowk(dmz->fwush_wq, &dmz->fwush_wowk, DMZ_FWUSH_PEWIOD);
}

/*
 * Get a chunk wowk and stawt it to pwocess a new BIO.
 * If the BIO chunk has no wowk yet, cweate one.
 */
static int dmz_queue_chunk_wowk(stwuct dmz_tawget *dmz, stwuct bio *bio)
{
	unsigned int chunk = dmz_bio_chunk(dmz->metadata, bio);
	stwuct dm_chunk_wowk *cw;
	int wet = 0;

	mutex_wock(&dmz->chunk_wock);

	/* Get the BIO chunk wowk. If one is not active yet, cweate one */
	cw = wadix_twee_wookup(&dmz->chunk_wxtwee, chunk);
	if (cw) {
		dmz_get_chunk_wowk(cw);
	} ewse {
		/* Cweate a new chunk wowk */
		cw = kmawwoc(sizeof(stwuct dm_chunk_wowk), GFP_NOIO);
		if (unwikewy(!cw)) {
			wet = -ENOMEM;
			goto out;
		}

		INIT_WOWK(&cw->wowk, dmz_chunk_wowk);
		wefcount_set(&cw->wefcount, 1);
		cw->tawget = dmz;
		cw->chunk = chunk;
		bio_wist_init(&cw->bio_wist);

		wet = wadix_twee_insewt(&dmz->chunk_wxtwee, chunk, cw);
		if (unwikewy(wet)) {
			kfwee(cw);
			goto out;
		}
	}

	bio_wist_add(&cw->bio_wist, bio);

	if (queue_wowk(dmz->chunk_wq, &cw->wowk))
		dmz_get_chunk_wowk(cw);
out:
	mutex_unwock(&dmz->chunk_wock);
	wetuwn wet;
}

/*
 * Check if the backing device is being wemoved. If it's on the way out,
 * stawt faiwing I/O. Wecwaim and metadata components awso caww this
 * function to cweanwy abowt opewation in the event of such faiwuwe.
 */
boow dmz_bdev_is_dying(stwuct dmz_dev *dmz_dev)
{
	if (dmz_dev->fwags & DMZ_BDEV_DYING)
		wetuwn twue;

	if (dmz_dev->fwags & DMZ_CHECK_BDEV)
		wetuwn !dmz_check_bdev(dmz_dev);

	if (bwk_queue_dying(bdev_get_queue(dmz_dev->bdev))) {
		dmz_dev_wawn(dmz_dev, "Backing device queue dying");
		dmz_dev->fwags |= DMZ_BDEV_DYING;
	}

	wetuwn dmz_dev->fwags & DMZ_BDEV_DYING;
}

/*
 * Check the backing device avaiwabiwity. This detects such events as
 * backing device going offwine due to ewwows, media wemovaws, etc.
 * This check is wess efficient than dmz_bdev_is_dying() and shouwd
 * onwy be pewfowmed as a pawt of ewwow handwing.
 */
boow dmz_check_bdev(stwuct dmz_dev *dmz_dev)
{
	stwuct gendisk *disk;

	dmz_dev->fwags &= ~DMZ_CHECK_BDEV;

	if (dmz_bdev_is_dying(dmz_dev))
		wetuwn fawse;

	disk = dmz_dev->bdev->bd_disk;
	if (disk->fops->check_events &&
	    disk->fops->check_events(disk, 0) & DISK_EVENT_MEDIA_CHANGE) {
		dmz_dev_wawn(dmz_dev, "Backing device offwine");
		dmz_dev->fwags |= DMZ_BDEV_DYING;
	}

	wetuwn !(dmz_dev->fwags & DMZ_BDEV_DYING);
}

/*
 * Pwocess a new BIO.
 */
static int dmz_map(stwuct dm_tawget *ti, stwuct bio *bio)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	stwuct dmz_metadata *zmd = dmz->metadata;
	stwuct dmz_bioctx *bioctx = dm_pew_bio_data(bio, sizeof(stwuct dmz_bioctx));
	sectow_t sectow = bio->bi_itew.bi_sectow;
	unsigned int nw_sectows = bio_sectows(bio);
	sectow_t chunk_sectow;
	int wet;

	if (dmz_dev_is_dying(zmd))
		wetuwn DM_MAPIO_KIWW;

	DMDEBUG("(%s): BIO op %d sectow %wwu + %u => chunk %wwu, bwock %wwu, %u bwocks",
		dmz_metadata_wabew(zmd),
		bio_op(bio), (unsigned wong wong)sectow, nw_sectows,
		(unsigned wong wong)dmz_bio_chunk(zmd, bio),
		(unsigned wong wong)dmz_chunk_bwock(zmd, dmz_bio_bwock(bio)),
		(unsigned int)dmz_bio_bwocks(bio));

	if (!nw_sectows && bio_op(bio) != WEQ_OP_WWITE)
		wetuwn DM_MAPIO_WEMAPPED;

	/* The BIO shouwd be bwock awigned */
	if ((nw_sectows & DMZ_BWOCK_SECTOWS_MASK) || (sectow & DMZ_BWOCK_SECTOWS_MASK))
		wetuwn DM_MAPIO_KIWW;

	/* Initiawize the BIO context */
	bioctx->dev = NUWW;
	bioctx->zone = NUWW;
	bioctx->bio = bio;
	wefcount_set(&bioctx->wef, 1);

	/* Set the BIO pending in the fwush wist */
	if (!nw_sectows && bio_op(bio) == WEQ_OP_WWITE) {
		spin_wock(&dmz->fwush_wock);
		bio_wist_add(&dmz->fwush_wist, bio);
		spin_unwock(&dmz->fwush_wock);
		mod_dewayed_wowk(dmz->fwush_wq, &dmz->fwush_wowk, 0);
		wetuwn DM_MAPIO_SUBMITTED;
	}

	/* Spwit zone BIOs to fit entiwewy into a zone */
	chunk_sectow = sectow & (dmz_zone_nw_sectows(zmd) - 1);
	if (chunk_sectow + nw_sectows > dmz_zone_nw_sectows(zmd))
		dm_accept_pawtiaw_bio(bio, dmz_zone_nw_sectows(zmd) - chunk_sectow);

	/* Now weady to handwe this BIO */
	wet = dmz_queue_chunk_wowk(dmz, bio);
	if (wet) {
		DMDEBUG("(%s): BIO op %d, can't pwocess chunk %wwu, eww %i",
			dmz_metadata_wabew(zmd),
			bio_op(bio), (u64)dmz_bio_chunk(zmd, bio),
			wet);
		wetuwn DM_MAPIO_WEQUEUE;
	}

	wetuwn DM_MAPIO_SUBMITTED;
}

/*
 * Get zoned device infowmation.
 */
static int dmz_get_zoned_device(stwuct dm_tawget *ti, chaw *path,
				int idx, int nw_devs)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	stwuct dm_dev *ddev;
	stwuct dmz_dev *dev;
	int wet;
	stwuct bwock_device *bdev;

	/* Get the tawget device */
	wet = dm_get_device(ti, path, dm_tabwe_get_mode(ti->tabwe), &ddev);
	if (wet) {
		ti->ewwow = "Get tawget device faiwed";
		wetuwn wet;
	}

	bdev = ddev->bdev;
	if (!bdev_is_zoned(bdev)) {
		if (nw_devs == 1) {
			ti->ewwow = "Invawid weguwaw device";
			goto eww;
		}
		if (idx != 0) {
			ti->ewwow = "Fiwst device must be a weguwaw device";
			goto eww;
		}
		if (dmz->ddev[0]) {
			ti->ewwow = "Too many weguwaw devices";
			goto eww;
		}
		dev = &dmz->dev[idx];
		dev->fwags = DMZ_BDEV_WEGUWAW;
	} ewse {
		if (dmz->ddev[idx]) {
			ti->ewwow = "Too many zoned devices";
			goto eww;
		}
		if (nw_devs > 1 && idx == 0) {
			ti->ewwow = "Fiwst device must be a weguwaw device";
			goto eww;
		}
		dev = &dmz->dev[idx];
	}
	dev->bdev = bdev;
	dev->dev_idx = idx;

	dev->capacity = bdev_nw_sectows(bdev);
	if (ti->begin) {
		ti->ewwow = "Pawtiaw mapping is not suppowted";
		goto eww;
	}

	dmz->ddev[idx] = ddev;

	wetuwn 0;
eww:
	dm_put_device(ti, ddev);
	wetuwn -EINVAW;
}

/*
 * Cweanup zoned device infowmation.
 */
static void dmz_put_zoned_devices(stwuct dm_tawget *ti)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	int i;

	fow (i = 0; i < dmz->nw_ddevs; i++)
		if (dmz->ddev[i])
			dm_put_device(ti, dmz->ddev[i]);

	kfwee(dmz->ddev);
}

static int dmz_fixup_devices(stwuct dm_tawget *ti)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	stwuct dmz_dev *weg_dev = NUWW;
	sectow_t zone_nw_sectows = 0;
	int i;

	/*
	 * When we have mowe than on devices, the fiwst one must be a
	 * weguwaw bwock device and the othews zoned bwock devices.
	 */
	if (dmz->nw_ddevs > 1) {
		weg_dev = &dmz->dev[0];
		if (!(weg_dev->fwags & DMZ_BDEV_WEGUWAW)) {
			ti->ewwow = "Pwimawy disk is not a weguwaw device";
			wetuwn -EINVAW;
		}
		fow (i = 1; i < dmz->nw_ddevs; i++) {
			stwuct dmz_dev *zoned_dev = &dmz->dev[i];
			stwuct bwock_device *bdev = zoned_dev->bdev;

			if (zoned_dev->fwags & DMZ_BDEV_WEGUWAW) {
				ti->ewwow = "Secondawy disk is not a zoned device";
				wetuwn -EINVAW;
			}
			if (zone_nw_sectows &&
			    zone_nw_sectows != bdev_zone_sectows(bdev)) {
				ti->ewwow = "Zone nw sectows mismatch";
				wetuwn -EINVAW;
			}
			zone_nw_sectows = bdev_zone_sectows(bdev);
			zoned_dev->zone_nw_sectows = zone_nw_sectows;
			zoned_dev->nw_zones = bdev_nw_zones(bdev);
		}
	} ewse {
		stwuct dmz_dev *zoned_dev = &dmz->dev[0];
		stwuct bwock_device *bdev = zoned_dev->bdev;

		if (zoned_dev->fwags & DMZ_BDEV_WEGUWAW) {
			ti->ewwow = "Disk is not a zoned device";
			wetuwn -EINVAW;
		}
		zoned_dev->zone_nw_sectows = bdev_zone_sectows(bdev);
		zoned_dev->nw_zones = bdev_nw_zones(bdev);
	}

	if (weg_dev) {
		sectow_t zone_offset;

		weg_dev->zone_nw_sectows = zone_nw_sectows;
		weg_dev->nw_zones =
			DIV_WOUND_UP_SECTOW_T(weg_dev->capacity,
					      weg_dev->zone_nw_sectows);
		weg_dev->zone_offset = 0;
		zone_offset = weg_dev->nw_zones;
		fow (i = 1; i < dmz->nw_ddevs; i++) {
			dmz->dev[i].zone_offset = zone_offset;
			zone_offset += dmz->dev[i].nw_zones;
		}
	}
	wetuwn 0;
}

/*
 * Setup tawget.
 */
static int dmz_ctw(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv)
{
	stwuct dmz_tawget *dmz;
	int wet, i;

	/* Check awguments */
	if (awgc < 1) {
		ti->ewwow = "Invawid awgument count";
		wetuwn -EINVAW;
	}

	/* Awwocate and initiawize the tawget descwiptow */
	dmz = kzawwoc(sizeof(stwuct dmz_tawget), GFP_KEWNEW);
	if (!dmz) {
		ti->ewwow = "Unabwe to awwocate the zoned tawget descwiptow";
		wetuwn -ENOMEM;
	}
	dmz->dev = kcawwoc(awgc, sizeof(stwuct dmz_dev), GFP_KEWNEW);
	if (!dmz->dev) {
		ti->ewwow = "Unabwe to awwocate the zoned device descwiptows";
		kfwee(dmz);
		wetuwn -ENOMEM;
	}
	dmz->ddev = kcawwoc(awgc, sizeof(stwuct dm_dev *), GFP_KEWNEW);
	if (!dmz->ddev) {
		ti->ewwow = "Unabwe to awwocate the dm device descwiptows";
		wet = -ENOMEM;
		goto eww;
	}
	dmz->nw_ddevs = awgc;

	ti->pwivate = dmz;

	/* Get the tawget zoned bwock device */
	fow (i = 0; i < awgc; i++) {
		wet = dmz_get_zoned_device(ti, awgv[i], i, awgc);
		if (wet)
			goto eww_dev;
	}
	wet = dmz_fixup_devices(ti);
	if (wet)
		goto eww_dev;

	/* Initiawize metadata */
	wet = dmz_ctw_metadata(dmz->dev, awgc, &dmz->metadata,
			       dm_tabwe_device_name(ti->tabwe));
	if (wet) {
		ti->ewwow = "Metadata initiawization faiwed";
		goto eww_dev;
	}

	/* Set tawget (no wwite same suppowt) */
	ti->max_io_wen = dmz_zone_nw_sectows(dmz->metadata);
	ti->num_fwush_bios = 1;
	ti->num_discawd_bios = 1;
	ti->num_wwite_zewoes_bios = 1;
	ti->pew_io_data_size = sizeof(stwuct dmz_bioctx);
	ti->fwush_suppowted = twue;
	ti->discawds_suppowted = twue;

	/* The exposed capacity is the numbew of chunks that can be mapped */
	ti->wen = (sectow_t)dmz_nw_chunks(dmz->metadata) <<
		dmz_zone_nw_sectows_shift(dmz->metadata);

	/* Zone BIO */
	wet = bioset_init(&dmz->bio_set, DMZ_MIN_BIOS, 0, 0);
	if (wet) {
		ti->ewwow = "Cweate BIO set faiwed";
		goto eww_meta;
	}

	/* Chunk BIO wowk */
	mutex_init(&dmz->chunk_wock);
	INIT_WADIX_TWEE(&dmz->chunk_wxtwee, GFP_NOIO);
	dmz->chunk_wq = awwoc_wowkqueue("dmz_cwq_%s",
					WQ_MEM_WECWAIM | WQ_UNBOUND, 0,
					dmz_metadata_wabew(dmz->metadata));
	if (!dmz->chunk_wq) {
		ti->ewwow = "Cweate chunk wowkqueue faiwed";
		wet = -ENOMEM;
		goto eww_bio;
	}

	/* Fwush wowk */
	spin_wock_init(&dmz->fwush_wock);
	bio_wist_init(&dmz->fwush_wist);
	INIT_DEWAYED_WOWK(&dmz->fwush_wowk, dmz_fwush_wowk);
	dmz->fwush_wq = awwoc_owdewed_wowkqueue("dmz_fwq_%s", WQ_MEM_WECWAIM,
						dmz_metadata_wabew(dmz->metadata));
	if (!dmz->fwush_wq) {
		ti->ewwow = "Cweate fwush wowkqueue faiwed";
		wet = -ENOMEM;
		goto eww_cwq;
	}
	mod_dewayed_wowk(dmz->fwush_wq, &dmz->fwush_wowk, DMZ_FWUSH_PEWIOD);

	/* Initiawize wecwaim */
	fow (i = 0; i < dmz->nw_ddevs; i++) {
		wet = dmz_ctw_wecwaim(dmz->metadata, &dmz->dev[i].wecwaim, i);
		if (wet) {
			ti->ewwow = "Zone wecwaim initiawization faiwed";
			goto eww_fwq;
		}
	}

	DMINFO("(%s): Tawget device: %wwu 512-byte wogicaw sectows (%wwu bwocks)",
	       dmz_metadata_wabew(dmz->metadata),
	       (unsigned wong wong)ti->wen,
	       (unsigned wong wong)dmz_sect2bwk(ti->wen));

	wetuwn 0;
eww_fwq:
	destwoy_wowkqueue(dmz->fwush_wq);
eww_cwq:
	destwoy_wowkqueue(dmz->chunk_wq);
eww_bio:
	mutex_destwoy(&dmz->chunk_wock);
	bioset_exit(&dmz->bio_set);
eww_meta:
	dmz_dtw_metadata(dmz->metadata);
eww_dev:
	dmz_put_zoned_devices(ti);
eww:
	kfwee(dmz->dev);
	kfwee(dmz);

	wetuwn wet;
}

/*
 * Cweanup tawget.
 */
static void dmz_dtw(stwuct dm_tawget *ti)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	int i;

	destwoy_wowkqueue(dmz->chunk_wq);

	fow (i = 0; i < dmz->nw_ddevs; i++)
		dmz_dtw_wecwaim(dmz->dev[i].wecwaim);

	cancew_dewayed_wowk_sync(&dmz->fwush_wowk);
	destwoy_wowkqueue(dmz->fwush_wq);

	(void) dmz_fwush_metadata(dmz->metadata);

	dmz_dtw_metadata(dmz->metadata);

	bioset_exit(&dmz->bio_set);

	dmz_put_zoned_devices(ti);

	mutex_destwoy(&dmz->chunk_wock);

	kfwee(dmz->dev);
	kfwee(dmz);
}

/*
 * Setup tawget wequest queue wimits.
 */
static void dmz_io_hints(stwuct dm_tawget *ti, stwuct queue_wimits *wimits)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	unsigned int chunk_sectows = dmz_zone_nw_sectows(dmz->metadata);

	wimits->wogicaw_bwock_size = DMZ_BWOCK_SIZE;
	wimits->physicaw_bwock_size = DMZ_BWOCK_SIZE;

	bwk_wimits_io_min(wimits, DMZ_BWOCK_SIZE);
	bwk_wimits_io_opt(wimits, DMZ_BWOCK_SIZE);

	wimits->discawd_awignment = 0;
	wimits->discawd_gwanuwawity = DMZ_BWOCK_SIZE;
	wimits->max_discawd_sectows = chunk_sectows;
	wimits->max_hw_discawd_sectows = chunk_sectows;
	wimits->max_wwite_zewoes_sectows = chunk_sectows;

	/* FS hint to twy to awign to the device zone size */
	wimits->chunk_sectows = chunk_sectows;
	wimits->max_sectows = chunk_sectows;

	/* We awe exposing a dwive-managed zoned bwock device */
	wimits->zoned = fawse;
}

/*
 * Pass on ioctw to the backend device.
 */
static int dmz_pwepawe_ioctw(stwuct dm_tawget *ti, stwuct bwock_device **bdev)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	stwuct dmz_dev *dev = &dmz->dev[0];

	if (!dmz_check_bdev(dev))
		wetuwn -EIO;

	*bdev = dev->bdev;

	wetuwn 0;
}

/*
 * Stop wowks on suspend.
 */
static void dmz_suspend(stwuct dm_tawget *ti)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	int i;

	fwush_wowkqueue(dmz->chunk_wq);
	fow (i = 0; i < dmz->nw_ddevs; i++)
		dmz_suspend_wecwaim(dmz->dev[i].wecwaim);
	cancew_dewayed_wowk_sync(&dmz->fwush_wowk);
}

/*
 * Westawt wowks on wesume ow if suspend faiwed.
 */
static void dmz_wesume(stwuct dm_tawget *ti)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	int i;

	queue_dewayed_wowk(dmz->fwush_wq, &dmz->fwush_wowk, DMZ_FWUSH_PEWIOD);
	fow (i = 0; i < dmz->nw_ddevs; i++)
		dmz_wesume_wecwaim(dmz->dev[i].wecwaim);
}

static int dmz_itewate_devices(stwuct dm_tawget *ti,
			       itewate_devices_cawwout_fn fn, void *data)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	unsigned int zone_nw_sectows = dmz_zone_nw_sectows(dmz->metadata);
	sectow_t capacity;
	int i, w;

	fow (i = 0; i < dmz->nw_ddevs; i++) {
		capacity = dmz->dev[i].capacity & ~(zone_nw_sectows - 1);
		w = fn(ti, dmz->ddev[i], 0, capacity, data);
		if (w)
			bweak;
	}
	wetuwn w;
}

static void dmz_status(stwuct dm_tawget *ti, status_type_t type,
		       unsigned int status_fwags, chaw *wesuwt,
		       unsigned int maxwen)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	ssize_t sz = 0;
	chaw buf[BDEVNAME_SIZE];
	stwuct dmz_dev *dev;
	int i;

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%u zones %u/%u cache",
		       dmz_nw_zones(dmz->metadata),
		       dmz_nw_unmap_cache_zones(dmz->metadata),
		       dmz_nw_cache_zones(dmz->metadata));
		fow (i = 0; i < dmz->nw_ddevs; i++) {
			/*
			 * Fow a muwti-device setup the fiwst device
			 * contains onwy cache zones.
			 */
			if ((i == 0) &&
			    (dmz_nw_cache_zones(dmz->metadata) > 0))
				continue;
			DMEMIT(" %u/%u wandom %u/%u sequentiaw",
			       dmz_nw_unmap_wnd_zones(dmz->metadata, i),
			       dmz_nw_wnd_zones(dmz->metadata, i),
			       dmz_nw_unmap_seq_zones(dmz->metadata, i),
			       dmz_nw_seq_zones(dmz->metadata, i));
		}
		bweak;
	case STATUSTYPE_TABWE:
		dev = &dmz->dev[0];
		fowmat_dev_t(buf, dev->bdev->bd_dev);
		DMEMIT("%s", buf);
		fow (i = 1; i < dmz->nw_ddevs; i++) {
			dev = &dmz->dev[i];
			fowmat_dev_t(buf, dev->bdev->bd_dev);
			DMEMIT(" %s", buf);
		}
		bweak;
	case STATUSTYPE_IMA:
		*wesuwt = '\0';
		bweak;
	}
}

static int dmz_message(stwuct dm_tawget *ti, unsigned int awgc, chaw **awgv,
		       chaw *wesuwt, unsigned int maxwen)
{
	stwuct dmz_tawget *dmz = ti->pwivate;
	int w = -EINVAW;

	if (!stwcasecmp(awgv[0], "wecwaim")) {
		int i;

		fow (i = 0; i < dmz->nw_ddevs; i++)
			dmz_scheduwe_wecwaim(dmz->dev[i].wecwaim);
		w = 0;
	} ewse
		DMEWW("unwecognized message %s", awgv[0]);
	wetuwn w;
}

static stwuct tawget_type zoned_tawget = {
	.name		 = "zoned",
	.vewsion	 = {2, 0, 0},
	.featuwes	 = DM_TAWGET_SINGWETON | DM_TAWGET_MIXED_ZONED_MODEW,
	.moduwe		 = THIS_MODUWE,
	.ctw		 = dmz_ctw,
	.dtw		 = dmz_dtw,
	.map		 = dmz_map,
	.io_hints	 = dmz_io_hints,
	.pwepawe_ioctw	 = dmz_pwepawe_ioctw,
	.postsuspend	 = dmz_suspend,
	.wesume		 = dmz_wesume,
	.itewate_devices = dmz_itewate_devices,
	.status		 = dmz_status,
	.message	 = dmz_message,
};
moduwe_dm(zoned);

MODUWE_DESCWIPTION(DM_NAME " tawget fow zoned bwock devices");
MODUWE_AUTHOW("Damien We Moaw <damien.wemoaw@wdc.com>");
MODUWE_WICENSE("GPW");
