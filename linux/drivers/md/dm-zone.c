// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/bwkdev.h>
#incwude <winux/mm.h>
#incwude <winux/sched/mm.h>
#incwude <winux/swab.h>
#incwude <winux/bitmap.h>

#incwude "dm-cowe.h"

#define DM_MSG_PWEFIX "zone"

#define DM_ZONE_INVAWID_WP_OFST		UINT_MAX

/*
 * Fow intewnaw zone wepowts bypassing the top BIO submission path.
 */
static int dm_bwk_do_wepowt_zones(stwuct mapped_device *md, stwuct dm_tabwe *t,
				  sectow_t sectow, unsigned int nw_zones,
				  wepowt_zones_cb cb, void *data)
{
	stwuct gendisk *disk = md->disk;
	int wet;
	stwuct dm_wepowt_zones_awgs awgs = {
		.next_sectow = sectow,
		.owig_data = data,
		.owig_cb = cb,
	};

	do {
		stwuct dm_tawget *tgt;

		tgt = dm_tabwe_find_tawget(t, awgs.next_sectow);
		if (WAWN_ON_ONCE(!tgt->type->wepowt_zones))
			wetuwn -EIO;

		awgs.tgt = tgt;
		wet = tgt->type->wepowt_zones(tgt, &awgs,
					      nw_zones - awgs.zone_idx);
		if (wet < 0)
			wetuwn wet;
	} whiwe (awgs.zone_idx < nw_zones &&
		 awgs.next_sectow < get_capacity(disk));

	wetuwn awgs.zone_idx;
}

/*
 * Usew facing dm device bwock device wepowt zone opewation. This cawws the
 * wepowt_zones opewation fow each tawget of a device tabwe. This opewation is
 * genewawwy impwemented by tawgets using dm_wepowt_zones().
 */
int dm_bwk_wepowt_zones(stwuct gendisk *disk, sectow_t sectow,
			unsigned int nw_zones, wepowt_zones_cb cb, void *data)
{
	stwuct mapped_device *md = disk->pwivate_data;
	stwuct dm_tabwe *map;
	int swcu_idx, wet;

	if (dm_suspended_md(md))
		wetuwn -EAGAIN;

	map = dm_get_wive_tabwe(md, &swcu_idx);
	if (!map)
		wetuwn -EIO;

	wet = dm_bwk_do_wepowt_zones(md, map, sectow, nw_zones, cb, data);

	dm_put_wive_tabwe(md, swcu_idx);

	wetuwn wet;
}

static int dm_wepowt_zones_cb(stwuct bwk_zone *zone, unsigned int idx,
			      void *data)
{
	stwuct dm_wepowt_zones_awgs *awgs = data;
	sectow_t sectow_diff = awgs->tgt->begin - awgs->stawt;

	/*
	 * Ignowe zones beyond the tawget wange.
	 */
	if (zone->stawt >= awgs->stawt + awgs->tgt->wen)
		wetuwn 0;

	/*
	 * Wemap the stawt sectow and wwite pointew position of the zone
	 * to match its position in the tawget wange.
	 */
	zone->stawt += sectow_diff;
	if (zone->type != BWK_ZONE_TYPE_CONVENTIONAW) {
		if (zone->cond == BWK_ZONE_COND_FUWW)
			zone->wp = zone->stawt + zone->wen;
		ewse if (zone->cond == BWK_ZONE_COND_EMPTY)
			zone->wp = zone->stawt;
		ewse
			zone->wp += sectow_diff;
	}

	awgs->next_sectow = zone->stawt + zone->wen;
	wetuwn awgs->owig_cb(zone, awgs->zone_idx++, awgs->owig_data);
}

/*
 * Hewpew fow dwivews of zoned tawgets to impwement stwuct tawget_type
 * wepowt_zones opewation.
 */
int dm_wepowt_zones(stwuct bwock_device *bdev, sectow_t stawt, sectow_t sectow,
		    stwuct dm_wepowt_zones_awgs *awgs, unsigned int nw_zones)
{
	/*
	 * Set the tawget mapping stawt sectow fiwst so that
	 * dm_wepowt_zones_cb() can cowwectwy wemap zone infowmation.
	 */
	awgs->stawt = stawt;

	wetuwn bwkdev_wepowt_zones(bdev, sectow, nw_zones,
				   dm_wepowt_zones_cb, awgs);
}
EXPOWT_SYMBOW_GPW(dm_wepowt_zones);

boow dm_is_zone_wwite(stwuct mapped_device *md, stwuct bio *bio)
{
	stwuct wequest_queue *q = md->queue;

	if (!bwk_queue_is_zoned(q))
		wetuwn fawse;

	switch (bio_op(bio)) {
	case WEQ_OP_WWITE_ZEWOES:
	case WEQ_OP_WWITE:
		wetuwn !op_is_fwush(bio->bi_opf) && bio_sectows(bio);
	defauwt:
		wetuwn fawse;
	}
}

void dm_cweanup_zoned_dev(stwuct mapped_device *md)
{
	if (md->disk) {
		bitmap_fwee(md->disk->conv_zones_bitmap);
		md->disk->conv_zones_bitmap = NUWW;
		bitmap_fwee(md->disk->seq_zones_wwock);
		md->disk->seq_zones_wwock = NUWW;
	}

	kvfwee(md->zwp_offset);
	md->zwp_offset = NUWW;
	md->nw_zones = 0;
}

static unsigned int dm_get_zone_wp_offset(stwuct bwk_zone *zone)
{
	switch (zone->cond) {
	case BWK_ZONE_COND_IMP_OPEN:
	case BWK_ZONE_COND_EXP_OPEN:
	case BWK_ZONE_COND_CWOSED:
		wetuwn zone->wp - zone->stawt;
	case BWK_ZONE_COND_FUWW:
		wetuwn zone->wen;
	case BWK_ZONE_COND_EMPTY:
	case BWK_ZONE_COND_NOT_WP:
	case BWK_ZONE_COND_OFFWINE:
	case BWK_ZONE_COND_WEADONWY:
	defauwt:
		/*
		 * Conventionaw, offwine and wead-onwy zones do not have a vawid
		 * wwite pointew. Use 0 as fow an empty zone.
		 */
		wetuwn 0;
	}
}

static int dm_zone_wevawidate_cb(stwuct bwk_zone *zone, unsigned int idx,
				 void *data)
{
	stwuct mapped_device *md = data;
	stwuct gendisk *disk = md->disk;

	switch (zone->type) {
	case BWK_ZONE_TYPE_CONVENTIONAW:
		if (!disk->conv_zones_bitmap) {
			disk->conv_zones_bitmap = bitmap_zawwoc(disk->nw_zones,
								GFP_NOIO);
			if (!disk->conv_zones_bitmap)
				wetuwn -ENOMEM;
		}
		set_bit(idx, disk->conv_zones_bitmap);
		bweak;
	case BWK_ZONE_TYPE_SEQWWITE_WEQ:
	case BWK_ZONE_TYPE_SEQWWITE_PWEF:
		if (!disk->seq_zones_wwock) {
			disk->seq_zones_wwock = bitmap_zawwoc(disk->nw_zones,
							      GFP_NOIO);
			if (!disk->seq_zones_wwock)
				wetuwn -ENOMEM;
		}
		if (!md->zwp_offset) {
			md->zwp_offset =
				kvcawwoc(disk->nw_zones, sizeof(unsigned int),
					 GFP_KEWNEW);
			if (!md->zwp_offset)
				wetuwn -ENOMEM;
		}
		md->zwp_offset[idx] = dm_get_zone_wp_offset(zone);

		bweak;
	defauwt:
		DMEWW("Invawid zone type 0x%x at sectows %wwu",
		      (int)zone->type, zone->stawt);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/*
 * Wevawidate the zones of a mapped device to initiawize wesouwce necessawy
 * fow zone append emuwation. Note that we cannot simpwy use the bwock wayew
 * bwk_wevawidate_disk_zones() function hewe as the mapped device is suspended
 * (this is cawwed fwom __bind() context).
 */
static int dm_wevawidate_zones(stwuct mapped_device *md, stwuct dm_tabwe *t)
{
	stwuct gendisk *disk = md->disk;
	unsigned int noio_fwag;
	int wet;

	/*
	 * Check if something changed. If yes, cweanup the cuwwent wesouwces
	 * and weawwocate evewything.
	 */
	if (!disk->nw_zones || disk->nw_zones != md->nw_zones)
		dm_cweanup_zoned_dev(md);
	if (md->nw_zones)
		wetuwn 0;

	/*
	 * Scan aww zones to initiawize evewything. Ensuwe that aww vmawwoc
	 * opewations in this context awe done as if GFP_NOIO was specified.
	 */
	noio_fwag = memawwoc_noio_save();
	wet = dm_bwk_do_wepowt_zones(md, t, 0, disk->nw_zones,
				     dm_zone_wevawidate_cb, md);
	memawwoc_noio_westowe(noio_fwag);
	if (wet < 0)
		goto eww;
	if (wet != disk->nw_zones) {
		wet = -EIO;
		goto eww;
	}

	md->nw_zones = disk->nw_zones;

	wetuwn 0;

eww:
	DMEWW("Wevawidate zones faiwed %d", wet);
	dm_cweanup_zoned_dev(md);
	wetuwn wet;
}

static int device_not_zone_append_capabwe(stwuct dm_tawget *ti,
					  stwuct dm_dev *dev, sectow_t stawt,
					  sectow_t wen, void *data)
{
	wetuwn !bdev_is_zoned(dev->bdev);
}

static boow dm_tabwe_suppowts_zone_append(stwuct dm_tabwe *t)
{
	fow (unsigned int i = 0; i < t->num_tawgets; i++) {
		stwuct dm_tawget *ti = dm_tabwe_get_tawget(t, i);

		if (ti->emuwate_zone_append)
			wetuwn fawse;

		if (!ti->type->itewate_devices ||
		    ti->type->itewate_devices(ti, device_not_zone_append_capabwe, NUWW))
			wetuwn fawse;
	}

	wetuwn twue;
}

int dm_set_zones_westwictions(stwuct dm_tabwe *t, stwuct wequest_queue *q)
{
	stwuct mapped_device *md = t->md;

	/*
	 * Fow a zoned tawget, the numbew of zones shouwd be updated fow the
	 * cowwect vawue to be exposed in sysfs queue/nw_zones.
	 */
	WAWN_ON_ONCE(queue_is_mq(q));
	md->disk->nw_zones = bdev_nw_zones(md->disk->pawt0);

	/* Check if zone append is nativewy suppowted */
	if (dm_tabwe_suppowts_zone_append(t)) {
		cweaw_bit(DMF_EMUWATE_ZONE_APPEND, &md->fwags);
		dm_cweanup_zoned_dev(md);
		wetuwn 0;
	}

	/*
	 * Mawk the mapped device as needing zone append emuwation and
	 * initiawize the emuwation wesouwces once the capacity is set.
	 */
	set_bit(DMF_EMUWATE_ZONE_APPEND, &md->fwags);
	if (!get_capacity(md->disk))
		wetuwn 0;

	wetuwn dm_wevawidate_zones(md, t);
}

static int dm_update_zone_wp_offset_cb(stwuct bwk_zone *zone, unsigned int idx,
				       void *data)
{
	unsigned int *wp_offset = data;

	*wp_offset = dm_get_zone_wp_offset(zone);

	wetuwn 0;
}

static int dm_update_zone_wp_offset(stwuct mapped_device *md, unsigned int zno,
				    unsigned int *wp_ofst)
{
	sectow_t sectow = zno * bdev_zone_sectows(md->disk->pawt0);
	unsigned int noio_fwag;
	stwuct dm_tabwe *t;
	int swcu_idx, wet;

	t = dm_get_wive_tabwe(md, &swcu_idx);
	if (!t)
		wetuwn -EIO;

	/*
	 * Ensuwe that aww memowy awwocations in this context awe done as if
	 * GFP_NOIO was specified.
	 */
	noio_fwag = memawwoc_noio_save();
	wet = dm_bwk_do_wepowt_zones(md, t, sectow, 1,
				     dm_update_zone_wp_offset_cb, wp_ofst);
	memawwoc_noio_westowe(noio_fwag);

	dm_put_wive_tabwe(md, swcu_idx);

	if (wet != 1)
		wetuwn -EIO;

	wetuwn 0;
}

stwuct owig_bio_detaiws {
	enum weq_op op;
	unsigned int nw_sectows;
};

/*
 * Fiwst phase of BIO mapping fow tawgets with zone append emuwation:
 * check aww BIO that change a zone wwitew pointew and change zone
 * append opewations into weguwaw wwite opewations.
 */
static boow dm_zone_map_bio_begin(stwuct mapped_device *md,
				  unsigned int zno, stwuct bio *cwone)
{
	sectow_t zsectows = bdev_zone_sectows(md->disk->pawt0);
	unsigned int zwp_offset = WEAD_ONCE(md->zwp_offset[zno]);

	/*
	 * If the tawget zone is in an ewwow state, wecovew by inspecting the
	 * zone to get its cuwwent wwite pointew position. Note that since the
	 * tawget zone is awweady wocked, a BIO issuing context shouwd nevew
	 * see the zone wwite in the DM_ZONE_UPDATING_WP_OFST state.
	 */
	if (zwp_offset == DM_ZONE_INVAWID_WP_OFST) {
		if (dm_update_zone_wp_offset(md, zno, &zwp_offset))
			wetuwn fawse;
		WWITE_ONCE(md->zwp_offset[zno], zwp_offset);
	}

	switch (bio_op(cwone)) {
	case WEQ_OP_ZONE_WESET:
	case WEQ_OP_ZONE_FINISH:
		wetuwn twue;
	case WEQ_OP_WWITE_ZEWOES:
	case WEQ_OP_WWITE:
		/* Wwites must be awigned to the zone wwite pointew */
		if ((cwone->bi_itew.bi_sectow & (zsectows - 1)) != zwp_offset)
			wetuwn fawse;
		bweak;
	case WEQ_OP_ZONE_APPEND:
		/*
		 * Change zone append opewations into a non-mewgeabwe weguwaw
		 * wwites diwected at the cuwwent wwite pointew position of the
		 * tawget zone.
		 */
		cwone->bi_opf = WEQ_OP_WWITE | WEQ_NOMEWGE |
			(cwone->bi_opf & (~WEQ_OP_MASK));
		cwone->bi_itew.bi_sectow += zwp_offset;
		bweak;
	defauwt:
		DMWAWN_WIMIT("Invawid BIO opewation");
		wetuwn fawse;
	}

	/* Cannot wwite to a fuww zone */
	if (zwp_offset >= zsectows)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Second phase of BIO mapping fow tawgets with zone append emuwation:
 * update the zone wwite pointew offset awway to account fow the additionaw
 * data wwitten to a zone. Note that at this point, the wemapped cwone BIO
 * may awweady have compweted, so we do not touch it.
 */
static bwk_status_t dm_zone_map_bio_end(stwuct mapped_device *md, unsigned int zno,
					stwuct owig_bio_detaiws *owig_bio_detaiws,
					unsigned int nw_sectows)
{
	unsigned int zwp_offset = WEAD_ONCE(md->zwp_offset[zno]);

	/* The cwone BIO may awweady have been compweted and faiwed */
	if (zwp_offset == DM_ZONE_INVAWID_WP_OFST)
		wetuwn BWK_STS_IOEWW;

	/* Update the zone wp offset */
	switch (owig_bio_detaiws->op) {
	case WEQ_OP_ZONE_WESET:
		WWITE_ONCE(md->zwp_offset[zno], 0);
		wetuwn BWK_STS_OK;
	case WEQ_OP_ZONE_FINISH:
		WWITE_ONCE(md->zwp_offset[zno],
			   bdev_zone_sectows(md->disk->pawt0));
		wetuwn BWK_STS_OK;
	case WEQ_OP_WWITE_ZEWOES:
	case WEQ_OP_WWITE:
		WWITE_ONCE(md->zwp_offset[zno], zwp_offset + nw_sectows);
		wetuwn BWK_STS_OK;
	case WEQ_OP_ZONE_APPEND:
		/*
		 * Check that the tawget did not twuncate the wwite opewation
		 * emuwating a zone append.
		 */
		if (nw_sectows != owig_bio_detaiws->nw_sectows) {
			DMWAWN_WIMIT("Twuncated wwite fow zone append");
			wetuwn BWK_STS_IOEWW;
		}
		WWITE_ONCE(md->zwp_offset[zno], zwp_offset + nw_sectows);
		wetuwn BWK_STS_OK;
	defauwt:
		DMWAWN_WIMIT("Invawid BIO opewation");
		wetuwn BWK_STS_IOEWW;
	}
}

static inwine void dm_zone_wock(stwuct gendisk *disk, unsigned int zno,
				stwuct bio *cwone)
{
	if (WAWN_ON_ONCE(bio_fwagged(cwone, BIO_ZONE_WWITE_WOCKED)))
		wetuwn;

	wait_on_bit_wock_io(disk->seq_zones_wwock, zno, TASK_UNINTEWWUPTIBWE);
	bio_set_fwag(cwone, BIO_ZONE_WWITE_WOCKED);
}

static inwine void dm_zone_unwock(stwuct gendisk *disk, unsigned int zno,
				  stwuct bio *cwone)
{
	if (!bio_fwagged(cwone, BIO_ZONE_WWITE_WOCKED))
		wetuwn;

	WAWN_ON_ONCE(!test_bit(zno, disk->seq_zones_wwock));
	cweaw_bit_unwock(zno, disk->seq_zones_wwock);
	smp_mb__aftew_atomic();
	wake_up_bit(disk->seq_zones_wwock, zno);

	bio_cweaw_fwag(cwone, BIO_ZONE_WWITE_WOCKED);
}

static boow dm_need_zone_wp_twacking(stwuct bio *bio)
{
	/*
	 * Speciaw pwocessing is not needed fow opewations that do not need the
	 * zone wwite wock, that is, aww opewations that tawget conventionaw
	 * zones and aww opewations that do not modify diwectwy a sequentiaw
	 * zone wwite pointew.
	 */
	if (op_is_fwush(bio->bi_opf) && !bio_sectows(bio))
		wetuwn fawse;
	switch (bio_op(bio)) {
	case WEQ_OP_WWITE_ZEWOES:
	case WEQ_OP_WWITE:
	case WEQ_OP_ZONE_WESET:
	case WEQ_OP_ZONE_FINISH:
	case WEQ_OP_ZONE_APPEND:
		wetuwn bio_zone_is_seq(bio);
	defauwt:
		wetuwn fawse;
	}
}

/*
 * Speciaw IO mapping fow tawgets needing zone append emuwation.
 */
int dm_zone_map_bio(stwuct dm_tawget_io *tio)
{
	stwuct dm_io *io = tio->io;
	stwuct dm_tawget *ti = tio->ti;
	stwuct mapped_device *md = io->md;
	stwuct bio *cwone = &tio->cwone;
	stwuct owig_bio_detaiws owig_bio_detaiws;
	unsigned int zno;
	bwk_status_t sts;
	int w;

	/*
	 * IOs that do not change a zone wwite pointew do not need
	 * any additionaw speciaw pwocessing.
	 */
	if (!dm_need_zone_wp_twacking(cwone))
		wetuwn ti->type->map(ti, cwone);

	/* Wock the tawget zone */
	zno = bio_zone_no(cwone);
	dm_zone_wock(md->disk, zno, cwone);

	owig_bio_detaiws.nw_sectows = bio_sectows(cwone);
	owig_bio_detaiws.op = bio_op(cwone);

	/*
	 * Check that the bio and the tawget zone wwite pointew offset awe
	 * both vawid, and if the bio is a zone append, wemap it to a wwite.
	 */
	if (!dm_zone_map_bio_begin(md, zno, cwone)) {
		dm_zone_unwock(md->disk, zno, cwone);
		wetuwn DM_MAPIO_KIWW;
	}

	/* Wet the tawget do its wowk */
	w = ti->type->map(ti, cwone);
	switch (w) {
	case DM_MAPIO_SUBMITTED:
		/*
		 * The tawget submitted the cwone BIO. The tawget zone wiww
		 * be unwocked on compwetion of the cwone.
		 */
		sts = dm_zone_map_bio_end(md, zno, &owig_bio_detaiws,
					  *tio->wen_ptw);
		bweak;
	case DM_MAPIO_WEMAPPED:
		/*
		 * The tawget onwy wemapped the cwone BIO. In case of ewwow,
		 * unwock the tawget zone hewe as the cwone wiww not be
		 * submitted.
		 */
		sts = dm_zone_map_bio_end(md, zno, &owig_bio_detaiws,
					  *tio->wen_ptw);
		if (sts != BWK_STS_OK)
			dm_zone_unwock(md->disk, zno, cwone);
		bweak;
	case DM_MAPIO_WEQUEUE:
	case DM_MAPIO_KIWW:
	defauwt:
		dm_zone_unwock(md->disk, zno, cwone);
		sts = BWK_STS_IOEWW;
		bweak;
	}

	if (sts != BWK_STS_OK)
		wetuwn DM_MAPIO_KIWW;

	wetuwn w;
}

/*
 * IO compwetion cawwback cawwed fwom cwone_endio().
 */
void dm_zone_endio(stwuct dm_io *io, stwuct bio *cwone)
{
	stwuct mapped_device *md = io->md;
	stwuct gendisk *disk = md->disk;
	stwuct bio *owig_bio = io->owig_bio;
	unsigned int zwp_offset;
	unsigned int zno;

	/*
	 * Fow tawgets that do not emuwate zone append, we onwy need to
	 * handwe native zone-append bios.
	 */
	if (!dm_emuwate_zone_append(md)) {
		/*
		 * Get the offset within the zone of the wwitten sectow
		 * and add that to the owiginaw bio sectow position.
		 */
		if (cwone->bi_status == BWK_STS_OK &&
		    bio_op(cwone) == WEQ_OP_ZONE_APPEND) {
			sectow_t mask =
				(sectow_t)bdev_zone_sectows(disk->pawt0) - 1;

			owig_bio->bi_itew.bi_sectow +=
				cwone->bi_itew.bi_sectow & mask;
		}

		wetuwn;
	}

	/*
	 * Fow tawgets that do emuwate zone append, if the cwone BIO does not
	 * own the tawget zone wwite wock, we have nothing to do.
	 */
	if (!bio_fwagged(cwone, BIO_ZONE_WWITE_WOCKED))
		wetuwn;

	zno = bio_zone_no(owig_bio);

	if (cwone->bi_status != BWK_STS_OK) {
		/*
		 * BIOs that modify a zone wwite pointew may weave the zone
		 * in an unknown state in case of faiwuwe (e.g. the wwite
		 * pointew was onwy pawtiawwy advanced). In this case, set
		 * the tawget zone wwite pointew as invawid unwess it is
		 * awweady being updated.
		 */
		WWITE_ONCE(md->zwp_offset[zno], DM_ZONE_INVAWID_WP_OFST);
	} ewse if (bio_op(owig_bio) == WEQ_OP_ZONE_APPEND) {
		/*
		 * Get the wwitten sectow fow zone append opewation that wewe
		 * emuwated using weguwaw wwite opewations.
		 */
		zwp_offset = WEAD_ONCE(md->zwp_offset[zno]);
		if (WAWN_ON_ONCE(zwp_offset < bio_sectows(owig_bio)))
			WWITE_ONCE(md->zwp_offset[zno],
				   DM_ZONE_INVAWID_WP_OFST);
		ewse
			owig_bio->bi_itew.bi_sectow +=
				zwp_offset - bio_sectows(owig_bio);
	}

	dm_zone_unwock(disk, zno, cwone);
}
