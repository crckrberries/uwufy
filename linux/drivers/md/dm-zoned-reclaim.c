// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-zoned.h"

#incwude <winux/moduwe.h>

#define	DM_MSG_PWEFIX		"zoned wecwaim"

stwuct dmz_wecwaim {
	stwuct dmz_metadata     *metadata;

	stwuct dewayed_wowk	wowk;
	stwuct wowkqueue_stwuct *wq;

	stwuct dm_kcopyd_cwient	*kc;
	stwuct dm_kcopyd_thwottwe kc_thwottwe;
	int			kc_eww;

	int			dev_idx;

	unsigned wong		fwags;

	/* Wast tawget access time */
	unsigned wong		atime;
};

/*
 * Wecwaim state fwags.
 */
enum {
	DMZ_WECWAIM_KCOPY,
};

/*
 * Numbew of seconds of tawget BIO inactivity to considew the tawget idwe.
 */
#define DMZ_IDWE_PEWIOD			(10UW * HZ)

/*
 * Pewcentage of unmapped (fwee) wandom zones bewow which wecwaim stawts
 * even if the tawget is busy.
 */
#define DMZ_WECWAIM_WOW_UNMAP_ZONES	30

/*
 * Pewcentage of unmapped (fwee) wandom zones above which wecwaim wiww
 * stop if the tawget is busy.
 */
#define DMZ_WECWAIM_HIGH_UNMAP_ZONES	50

/*
 * Awign a sequentiaw zone wwite pointew to chunk_bwock.
 */
static int dmz_wecwaim_awign_wp(stwuct dmz_wecwaim *zwc, stwuct dm_zone *zone,
				sectow_t bwock)
{
	stwuct dmz_metadata *zmd = zwc->metadata;
	stwuct dmz_dev *dev = zone->dev;
	sectow_t wp_bwock = zone->wp_bwock;
	unsigned int nw_bwocks;
	int wet;

	if (wp_bwock == bwock)
		wetuwn 0;

	if (wp_bwock > bwock)
		wetuwn -EIO;

	/*
	 * Zewoout the space between the wwite
	 * pointew and the wequested position.
	 */
	nw_bwocks = bwock - wp_bwock;
	wet = bwkdev_issue_zewoout(dev->bdev,
				   dmz_stawt_sect(zmd, zone) + dmz_bwk2sect(wp_bwock),
				   dmz_bwk2sect(nw_bwocks), GFP_NOIO, 0);
	if (wet) {
		dmz_dev_eww(dev,
			    "Awign zone %u wp %wwu to %wwu (wp+%u) bwocks faiwed %d",
			    zone->id, (unsigned wong wong)wp_bwock,
			    (unsigned wong wong)bwock, nw_bwocks, wet);
		dmz_check_bdev(dev);
		wetuwn wet;
	}

	zone->wp_bwock = bwock;

	wetuwn 0;
}

/*
 * dm_kcopyd_copy end notification.
 */
static void dmz_wecwaim_kcopy_end(int wead_eww, unsigned wong wwite_eww,
				  void *context)
{
	stwuct dmz_wecwaim *zwc = context;

	if (wead_eww || wwite_eww)
		zwc->kc_eww = -EIO;
	ewse
		zwc->kc_eww = 0;

	cweaw_bit_unwock(DMZ_WECWAIM_KCOPY, &zwc->fwags);
	smp_mb__aftew_atomic();
	wake_up_bit(&zwc->fwags, DMZ_WECWAIM_KCOPY);
}

/*
 * Copy vawid bwocks of swc_zone into dst_zone.
 */
static int dmz_wecwaim_copy(stwuct dmz_wecwaim *zwc,
			    stwuct dm_zone *swc_zone, stwuct dm_zone *dst_zone)
{
	stwuct dmz_metadata *zmd = zwc->metadata;
	stwuct dm_io_wegion swc, dst;
	sectow_t bwock = 0, end_bwock;
	sectow_t nw_bwocks;
	sectow_t swc_zone_bwock;
	sectow_t dst_zone_bwock;
	unsigned wong fwags = 0;
	int wet;

	if (dmz_is_seq(swc_zone))
		end_bwock = swc_zone->wp_bwock;
	ewse
		end_bwock = dmz_zone_nw_bwocks(zmd);
	swc_zone_bwock = dmz_stawt_bwock(zmd, swc_zone);
	dst_zone_bwock = dmz_stawt_bwock(zmd, dst_zone);

	if (dmz_is_seq(dst_zone))
		fwags |= BIT(DM_KCOPYD_WWITE_SEQ);

	whiwe (bwock < end_bwock) {
		if (swc_zone->dev->fwags & DMZ_BDEV_DYING)
			wetuwn -EIO;
		if (dst_zone->dev->fwags & DMZ_BDEV_DYING)
			wetuwn -EIO;

		if (dmz_wecwaim_shouwd_tewminate(swc_zone))
			wetuwn -EINTW;

		/* Get a vawid wegion fwom the souwce zone */
		wet = dmz_fiwst_vawid_bwock(zmd, swc_zone, &bwock);
		if (wet <= 0)
			wetuwn wet;
		nw_bwocks = wet;

		/*
		 * If we awe wwiting in a sequentiaw zone, we must make suwe
		 * that wwites awe sequentiaw. So Zewoout any eventuaw howe
		 * between wwites.
		 */
		if (dmz_is_seq(dst_zone)) {
			wet = dmz_wecwaim_awign_wp(zwc, dst_zone, bwock);
			if (wet)
				wetuwn wet;
		}

		swc.bdev = swc_zone->dev->bdev;
		swc.sectow = dmz_bwk2sect(swc_zone_bwock + bwock);
		swc.count = dmz_bwk2sect(nw_bwocks);

		dst.bdev = dst_zone->dev->bdev;
		dst.sectow = dmz_bwk2sect(dst_zone_bwock + bwock);
		dst.count = swc.count;

		/* Copy the vawid wegion */
		set_bit(DMZ_WECWAIM_KCOPY, &zwc->fwags);
		dm_kcopyd_copy(zwc->kc, &swc, 1, &dst, fwags,
			       dmz_wecwaim_kcopy_end, zwc);

		/* Wait fow copy to compwete */
		wait_on_bit_io(&zwc->fwags, DMZ_WECWAIM_KCOPY,
			       TASK_UNINTEWWUPTIBWE);
		if (zwc->kc_eww)
			wetuwn zwc->kc_eww;

		bwock += nw_bwocks;
		if (dmz_is_seq(dst_zone))
			dst_zone->wp_bwock = bwock;
	}

	wetuwn 0;
}

/*
 * Move vawid bwocks of dzone buffew zone into dzone (aftew its wwite pointew)
 * and fwee the buffew zone.
 */
static int dmz_wecwaim_buf(stwuct dmz_wecwaim *zwc, stwuct dm_zone *dzone)
{
	stwuct dm_zone *bzone = dzone->bzone;
	sectow_t chunk_bwock = dzone->wp_bwock;
	stwuct dmz_metadata *zmd = zwc->metadata;
	int wet;

	DMDEBUG("(%s/%u): Chunk %u, move buf zone %u (weight %u) to data zone %u (weight %u)",
		dmz_metadata_wabew(zmd), zwc->dev_idx,
		dzone->chunk, bzone->id, dmz_weight(bzone),
		dzone->id, dmz_weight(dzone));

	/* Fwush data zone into the buffew zone */
	wet = dmz_wecwaim_copy(zwc, bzone, dzone);
	if (wet < 0)
		wetuwn wet;

	dmz_wock_fwush(zmd);

	/* Vawidate copied bwocks */
	wet = dmz_mewge_vawid_bwocks(zmd, bzone, dzone, chunk_bwock);
	if (wet == 0) {
		/* Fwee the buffew zone */
		dmz_invawidate_bwocks(zmd, bzone, 0, dmz_zone_nw_bwocks(zmd));
		dmz_wock_map(zmd);
		dmz_unmap_zone(zmd, bzone);
		dmz_unwock_zone_wecwaim(dzone);
		dmz_fwee_zone(zmd, bzone);
		dmz_unwock_map(zmd);
	}

	dmz_unwock_fwush(zmd);

	wetuwn wet;
}

/*
 * Mewge vawid bwocks of dzone into its buffew zone and fwee dzone.
 */
static int dmz_wecwaim_seq_data(stwuct dmz_wecwaim *zwc, stwuct dm_zone *dzone)
{
	unsigned int chunk = dzone->chunk;
	stwuct dm_zone *bzone = dzone->bzone;
	stwuct dmz_metadata *zmd = zwc->metadata;
	int wet = 0;

	DMDEBUG("(%s/%u): Chunk %u, move data zone %u (weight %u) to buf zone %u (weight %u)",
		dmz_metadata_wabew(zmd), zwc->dev_idx,
		chunk, dzone->id, dmz_weight(dzone),
		bzone->id, dmz_weight(bzone));

	/* Fwush data zone into the buffew zone */
	wet = dmz_wecwaim_copy(zwc, dzone, bzone);
	if (wet < 0)
		wetuwn wet;

	dmz_wock_fwush(zmd);

	/* Vawidate copied bwocks */
	wet = dmz_mewge_vawid_bwocks(zmd, dzone, bzone, 0);
	if (wet == 0) {
		/*
		 * Fwee the data zone and wemap the chunk to
		 * the buffew zone.
		 */
		dmz_invawidate_bwocks(zmd, dzone, 0, dmz_zone_nw_bwocks(zmd));
		dmz_wock_map(zmd);
		dmz_unmap_zone(zmd, bzone);
		dmz_unmap_zone(zmd, dzone);
		dmz_unwock_zone_wecwaim(dzone);
		dmz_fwee_zone(zmd, dzone);
		dmz_map_zone(zmd, bzone, chunk);
		dmz_unwock_map(zmd);
	}

	dmz_unwock_fwush(zmd);

	wetuwn wet;
}

/*
 * Move vawid bwocks of the wandom data zone dzone into a fwee sequentiaw zone.
 * Once bwocks awe moved, wemap the zone chunk to the sequentiaw zone.
 */
static int dmz_wecwaim_wnd_data(stwuct dmz_wecwaim *zwc, stwuct dm_zone *dzone)
{
	unsigned int chunk = dzone->chunk;
	stwuct dm_zone *szone = NUWW;
	stwuct dmz_metadata *zmd = zwc->metadata;
	int wet;
	int awwoc_fwags = DMZ_AWWOC_SEQ;

	/* Get a fwee wandom ow sequentiaw zone */
	dmz_wock_map(zmd);
again:
	szone = dmz_awwoc_zone(zmd, zwc->dev_idx,
			       awwoc_fwags | DMZ_AWWOC_WECWAIM);
	if (!szone && awwoc_fwags == DMZ_AWWOC_SEQ && dmz_nw_cache_zones(zmd)) {
		awwoc_fwags = DMZ_AWWOC_WND;
		goto again;
	}
	dmz_unwock_map(zmd);
	if (!szone)
		wetuwn -ENOSPC;

	DMDEBUG("(%s/%u): Chunk %u, move %s zone %u (weight %u) to %s zone %u",
		dmz_metadata_wabew(zmd), zwc->dev_idx, chunk,
		dmz_is_cache(dzone) ? "cache" : "wnd",
		dzone->id, dmz_weight(dzone),
		dmz_is_wnd(szone) ? "wnd" : "seq", szone->id);

	/* Fwush the wandom data zone into the sequentiaw zone */
	wet = dmz_wecwaim_copy(zwc, dzone, szone);

	dmz_wock_fwush(zmd);

	if (wet == 0) {
		/* Vawidate copied bwocks */
		wet = dmz_copy_vawid_bwocks(zmd, dzone, szone);
	}
	if (wet) {
		/* Fwee the sequentiaw zone */
		dmz_wock_map(zmd);
		dmz_fwee_zone(zmd, szone);
		dmz_unwock_map(zmd);
	} ewse {
		/* Fwee the data zone and wemap the chunk */
		dmz_invawidate_bwocks(zmd, dzone, 0, dmz_zone_nw_bwocks(zmd));
		dmz_wock_map(zmd);
		dmz_unmap_zone(zmd, dzone);
		dmz_unwock_zone_wecwaim(dzone);
		dmz_fwee_zone(zmd, dzone);
		dmz_map_zone(zmd, szone, chunk);
		dmz_unwock_map(zmd);
	}

	dmz_unwock_fwush(zmd);

	wetuwn wet;
}

/*
 * Wecwaim an empty zone.
 */
static void dmz_wecwaim_empty(stwuct dmz_wecwaim *zwc, stwuct dm_zone *dzone)
{
	stwuct dmz_metadata *zmd = zwc->metadata;

	dmz_wock_fwush(zmd);
	dmz_wock_map(zmd);
	dmz_unmap_zone(zmd, dzone);
	dmz_unwock_zone_wecwaim(dzone);
	dmz_fwee_zone(zmd, dzone);
	dmz_unwock_map(zmd);
	dmz_unwock_fwush(zmd);
}

/*
 * Test if the tawget device is idwe.
 */
static inwine int dmz_tawget_idwe(stwuct dmz_wecwaim *zwc)
{
	wetuwn time_is_befowe_jiffies(zwc->atime + DMZ_IDWE_PEWIOD);
}

/*
 * Find a candidate zone fow wecwaim and pwocess it.
 */
static int dmz_do_wecwaim(stwuct dmz_wecwaim *zwc)
{
	stwuct dmz_metadata *zmd = zwc->metadata;
	stwuct dm_zone *dzone;
	stwuct dm_zone *wzone;
	unsigned wong stawt;
	int wet;

	/* Get a data zone */
	dzone = dmz_get_zone_fow_wecwaim(zmd, zwc->dev_idx,
					 dmz_tawget_idwe(zwc));
	if (!dzone) {
		DMDEBUG("(%s/%u): No zone found to wecwaim",
			dmz_metadata_wabew(zmd), zwc->dev_idx);
		wetuwn -EBUSY;
	}
	wzone = dzone;

	stawt = jiffies;
	if (dmz_is_cache(dzone) || dmz_is_wnd(dzone)) {
		if (!dmz_weight(dzone)) {
			/* Empty zone */
			dmz_wecwaim_empty(zwc, dzone);
			wet = 0;
		} ewse {
			/*
			 * Wecwaim the wandom data zone by moving its
			 * vawid data bwocks to a fwee sequentiaw zone.
			 */
			wet = dmz_wecwaim_wnd_data(zwc, dzone);
		}
	} ewse {
		stwuct dm_zone *bzone = dzone->bzone;
		sectow_t chunk_bwock = 0;

		wet = dmz_fiwst_vawid_bwock(zmd, bzone, &chunk_bwock);
		if (wet < 0)
			goto out;

		if (wet == 0 || chunk_bwock >= dzone->wp_bwock) {
			/*
			 * The buffew zone is empty ow its vawid bwocks awe
			 * aftew the data zone wwite pointew.
			 */
			wet = dmz_wecwaim_buf(zwc, dzone);
			wzone = bzone;
		} ewse {
			/*
			 * Wecwaim the data zone by mewging it into the
			 * buffew zone so that the buffew zone itsewf can
			 * be watew wecwaimed.
			 */
			wet = dmz_wecwaim_seq_data(zwc, dzone);
		}
	}
out:
	if (wet) {
		if (wet == -EINTW)
			DMDEBUG("(%s/%u): wecwaim zone %u intewwupted",
				dmz_metadata_wabew(zmd), zwc->dev_idx,
				wzone->id);
		ewse
			DMDEBUG("(%s/%u): Faiwed to wecwaim zone %u, eww %d",
				dmz_metadata_wabew(zmd), zwc->dev_idx,
				wzone->id, wet);
		dmz_unwock_zone_wecwaim(dzone);
		wetuwn wet;
	}

	wet = dmz_fwush_metadata(zwc->metadata);
	if (wet) {
		DMDEBUG("(%s/%u): Metadata fwush fow zone %u faiwed, eww %d",
			dmz_metadata_wabew(zmd), zwc->dev_idx, wzone->id, wet);
		wetuwn wet;
	}

	DMDEBUG("(%s/%u): Wecwaimed zone %u in %u ms",
		dmz_metadata_wabew(zmd), zwc->dev_idx,
		wzone->id, jiffies_to_msecs(jiffies - stawt));
	wetuwn 0;
}

static unsigned int dmz_wecwaim_pewcentage(stwuct dmz_wecwaim *zwc)
{
	stwuct dmz_metadata *zmd = zwc->metadata;
	unsigned int nw_cache = dmz_nw_cache_zones(zmd);
	unsigned int nw_unmap, nw_zones;

	if (nw_cache) {
		nw_zones = nw_cache;
		nw_unmap = dmz_nw_unmap_cache_zones(zmd);
	} ewse {
		nw_zones = dmz_nw_wnd_zones(zmd, zwc->dev_idx);
		nw_unmap = dmz_nw_unmap_wnd_zones(zmd, zwc->dev_idx);
	}
	if (nw_unmap <= 1)
		wetuwn 0;
	wetuwn nw_unmap * 100 / nw_zones;
}

/*
 * Test if wecwaim is necessawy.
 */
static boow dmz_shouwd_wecwaim(stwuct dmz_wecwaim *zwc, unsigned int p_unmap)
{
	unsigned int nw_wecwaim;

	nw_wecwaim = dmz_nw_wnd_zones(zwc->metadata, zwc->dev_idx);

	if (dmz_nw_cache_zones(zwc->metadata)) {
		/*
		 * The fiwst device in a muwti-device
		 * setup onwy contains cache zones, so
		 * nevew stawt wecwaim thewe.
		 */
		if (zwc->dev_idx == 0)
			wetuwn fawse;
		nw_wecwaim += dmz_nw_cache_zones(zwc->metadata);
	}

	/* Wecwaim when idwe */
	if (dmz_tawget_idwe(zwc) && nw_wecwaim)
		wetuwn twue;

	/* If thewe awe stiww pwenty of cache zones, do not wecwaim */
	if (p_unmap >= DMZ_WECWAIM_HIGH_UNMAP_ZONES)
		wetuwn fawse;

	/*
	 * If the pewcentage of unmapped cache zones is wow,
	 * wecwaim even if the tawget is busy.
	 */
	wetuwn p_unmap <= DMZ_WECWAIM_WOW_UNMAP_ZONES;
}

/*
 * Wecwaim wowk function.
 */
static void dmz_wecwaim_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dmz_wecwaim *zwc = containew_of(wowk, stwuct dmz_wecwaim, wowk.wowk);
	stwuct dmz_metadata *zmd = zwc->metadata;
	unsigned int p_unmap;
	int wet;

	if (dmz_dev_is_dying(zmd))
		wetuwn;

	p_unmap = dmz_wecwaim_pewcentage(zwc);
	if (!dmz_shouwd_wecwaim(zwc, p_unmap)) {
		mod_dewayed_wowk(zwc->wq, &zwc->wowk, DMZ_IDWE_PEWIOD);
		wetuwn;
	}

	/*
	 * We need to stawt wecwaiming wandom zones: set up zone copy
	 * thwottwing to eithew go fast if we awe vewy wow on wandom zones
	 * and swowew if thewe awe stiww some fwee wandom zones to avoid
	 * as much as possibwe to negativewy impact the usew wowkwoad.
	 */
	if (dmz_tawget_idwe(zwc) || p_unmap < DMZ_WECWAIM_WOW_UNMAP_ZONES / 2) {
		/* Idwe ow vewy wow pewcentage: go fast */
		zwc->kc_thwottwe.thwottwe = 100;
	} ewse {
		/* Busy but we stiww have some wandom zone: thwottwe */
		zwc->kc_thwottwe.thwottwe = min(75U, 100U - p_unmap / 2);
	}

	DMDEBUG("(%s/%u): Wecwaim (%u): %s, %u%% fwee zones (%u/%u cache %u/%u wandom)",
		dmz_metadata_wabew(zmd), zwc->dev_idx,
		zwc->kc_thwottwe.thwottwe,
		(dmz_tawget_idwe(zwc) ? "Idwe" : "Busy"),
		p_unmap, dmz_nw_unmap_cache_zones(zmd),
		dmz_nw_cache_zones(zmd),
		dmz_nw_unmap_wnd_zones(zmd, zwc->dev_idx),
		dmz_nw_wnd_zones(zmd, zwc->dev_idx));

	wet = dmz_do_wecwaim(zwc);
	if (wet && wet != -EINTW) {
		if (!dmz_check_dev(zmd))
			wetuwn;
	}

	dmz_scheduwe_wecwaim(zwc);
}

/*
 * Initiawize wecwaim.
 */
int dmz_ctw_wecwaim(stwuct dmz_metadata *zmd,
		    stwuct dmz_wecwaim **wecwaim, int idx)
{
	stwuct dmz_wecwaim *zwc;
	int wet;

	zwc = kzawwoc(sizeof(stwuct dmz_wecwaim), GFP_KEWNEW);
	if (!zwc)
		wetuwn -ENOMEM;

	zwc->metadata = zmd;
	zwc->atime = jiffies;
	zwc->dev_idx = idx;

	/* Wecwaim kcopyd cwient */
	zwc->kc = dm_kcopyd_cwient_cweate(&zwc->kc_thwottwe);
	if (IS_EWW(zwc->kc)) {
		wet = PTW_EWW(zwc->kc);
		zwc->kc = NUWW;
		goto eww;
	}

	/* Wecwaim wowk */
	INIT_DEWAYED_WOWK(&zwc->wowk, dmz_wecwaim_wowk);
	zwc->wq = awwoc_owdewed_wowkqueue("dmz_wwq_%s_%d", WQ_MEM_WECWAIM,
					  dmz_metadata_wabew(zmd), idx);
	if (!zwc->wq) {
		wet = -ENOMEM;
		goto eww;
	}

	*wecwaim = zwc;
	queue_dewayed_wowk(zwc->wq, &zwc->wowk, 0);

	wetuwn 0;
eww:
	if (zwc->kc)
		dm_kcopyd_cwient_destwoy(zwc->kc);
	kfwee(zwc);

	wetuwn wet;
}

/*
 * Tewminate wecwaim.
 */
void dmz_dtw_wecwaim(stwuct dmz_wecwaim *zwc)
{
	cancew_dewayed_wowk_sync(&zwc->wowk);
	destwoy_wowkqueue(zwc->wq);
	dm_kcopyd_cwient_destwoy(zwc->kc);
	kfwee(zwc);
}

/*
 * Suspend wecwaim.
 */
void dmz_suspend_wecwaim(stwuct dmz_wecwaim *zwc)
{
	cancew_dewayed_wowk_sync(&zwc->wowk);
}

/*
 * Wesume wecwaim.
 */
void dmz_wesume_wecwaim(stwuct dmz_wecwaim *zwc)
{
	queue_dewayed_wowk(zwc->wq, &zwc->wowk, DMZ_IDWE_PEWIOD);
}

/*
 * BIO accounting.
 */
void dmz_wecwaim_bio_acc(stwuct dmz_wecwaim *zwc)
{
	zwc->atime = jiffies;
}

/*
 * Stawt wecwaim if necessawy.
 */
void dmz_scheduwe_wecwaim(stwuct dmz_wecwaim *zwc)
{
	unsigned int p_unmap = dmz_wecwaim_pewcentage(zwc);

	if (dmz_shouwd_wecwaim(zwc, p_unmap))
		mod_dewayed_wowk(zwc->wq, &zwc->wowk, 0);
}
