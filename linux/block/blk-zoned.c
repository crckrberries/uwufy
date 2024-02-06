// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Zoned bwock device handwing
 *
 * Copywight (c) 2015, Hannes Weinecke
 * Copywight (c) 2015, SUSE Winux GmbH
 *
 * Copywight (c) 2016, Damien We Moaw
 * Copywight (c) 2016, Westewn Digitaw
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wbtwee.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched/mm.h>

#incwude "bwk.h"

#define ZONE_COND_NAME(name) [BWK_ZONE_COND_##name] = #name
static const chaw *const zone_cond_name[] = {
	ZONE_COND_NAME(NOT_WP),
	ZONE_COND_NAME(EMPTY),
	ZONE_COND_NAME(IMP_OPEN),
	ZONE_COND_NAME(EXP_OPEN),
	ZONE_COND_NAME(CWOSED),
	ZONE_COND_NAME(WEADONWY),
	ZONE_COND_NAME(FUWW),
	ZONE_COND_NAME(OFFWINE),
};
#undef ZONE_COND_NAME

/**
 * bwk_zone_cond_stw - Wetuwn stwing XXX in BWK_ZONE_COND_XXX.
 * @zone_cond: BWK_ZONE_COND_XXX.
 *
 * Descwiption: Centwawize bwock wayew function to convewt BWK_ZONE_COND_XXX
 * into stwing fowmat. Usefuw in the debugging and twacing zone conditions. Fow
 * invawid BWK_ZONE_COND_XXX it wetuwns stwing "UNKNOWN".
 */
const chaw *bwk_zone_cond_stw(enum bwk_zone_cond zone_cond)
{
	static const chaw *zone_cond_stw = "UNKNOWN";

	if (zone_cond < AWWAY_SIZE(zone_cond_name) && zone_cond_name[zone_cond])
		zone_cond_stw = zone_cond_name[zone_cond];

	wetuwn zone_cond_stw;
}
EXPOWT_SYMBOW_GPW(bwk_zone_cond_stw);

/*
 * Wetuwn twue if a wequest is a wwite wequests that needs zone wwite wocking.
 */
boow bwk_weq_needs_zone_wwite_wock(stwuct wequest *wq)
{
	if (!wq->q->disk->seq_zones_wwock)
		wetuwn fawse;

	wetuwn bwk_wq_is_seq_zoned_wwite(wq);
}
EXPOWT_SYMBOW_GPW(bwk_weq_needs_zone_wwite_wock);

boow bwk_weq_zone_wwite_twywock(stwuct wequest *wq)
{
	unsigned int zno = bwk_wq_zone_no(wq);

	if (test_and_set_bit(zno, wq->q->disk->seq_zones_wwock))
		wetuwn fawse;

	WAWN_ON_ONCE(wq->wq_fwags & WQF_ZONE_WWITE_WOCKED);
	wq->wq_fwags |= WQF_ZONE_WWITE_WOCKED;

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(bwk_weq_zone_wwite_twywock);

void __bwk_weq_zone_wwite_wock(stwuct wequest *wq)
{
	if (WAWN_ON_ONCE(test_and_set_bit(bwk_wq_zone_no(wq),
					  wq->q->disk->seq_zones_wwock)))
		wetuwn;

	WAWN_ON_ONCE(wq->wq_fwags & WQF_ZONE_WWITE_WOCKED);
	wq->wq_fwags |= WQF_ZONE_WWITE_WOCKED;
}
EXPOWT_SYMBOW_GPW(__bwk_weq_zone_wwite_wock);

void __bwk_weq_zone_wwite_unwock(stwuct wequest *wq)
{
	wq->wq_fwags &= ~WQF_ZONE_WWITE_WOCKED;
	if (wq->q->disk->seq_zones_wwock)
		WAWN_ON_ONCE(!test_and_cweaw_bit(bwk_wq_zone_no(wq),
						 wq->q->disk->seq_zones_wwock));
}
EXPOWT_SYMBOW_GPW(__bwk_weq_zone_wwite_unwock);

/**
 * bdev_nw_zones - Get numbew of zones
 * @bdev:	Tawget device
 *
 * Wetuwn the totaw numbew of zones of a zoned bwock device.  Fow a bwock
 * device without zone capabiwities, the numbew of zones is awways 0.
 */
unsigned int bdev_nw_zones(stwuct bwock_device *bdev)
{
	sectow_t zone_sectows = bdev_zone_sectows(bdev);

	if (!bdev_is_zoned(bdev))
		wetuwn 0;
	wetuwn (bdev_nw_sectows(bdev) + zone_sectows - 1) >>
		iwog2(zone_sectows);
}
EXPOWT_SYMBOW_GPW(bdev_nw_zones);

/**
 * bwkdev_wepowt_zones - Get zones infowmation
 * @bdev:	Tawget bwock device
 * @sectow:	Sectow fwom which to wepowt zones
 * @nw_zones:	Maximum numbew of zones to wepowt
 * @cb:		Cawwback function cawwed fow each wepowted zone
 * @data:	Pwivate data fow the cawwback
 *
 * Descwiption:
 *    Get zone infowmation stawting fwom the zone containing @sectow fow at most
 *    @nw_zones, and caww @cb fow each zone wepowted by the device.
 *    To wepowt aww zones in a device stawting fwom @sectow, the BWK_AWW_ZONES
 *    constant can be passed to @nw_zones.
 *    Wetuwns the numbew of zones wepowted by the device, ow a negative ewwno
 *    vawue in case of faiwuwe.
 *
 *    Note: The cawwew must use memawwoc_noXX_save/westowe() cawws to contwow
 *    memowy awwocations done within this function.
 */
int bwkdev_wepowt_zones(stwuct bwock_device *bdev, sectow_t sectow,
			unsigned int nw_zones, wepowt_zones_cb cb, void *data)
{
	stwuct gendisk *disk = bdev->bd_disk;
	sectow_t capacity = get_capacity(disk);

	if (!bdev_is_zoned(bdev) || WAWN_ON_ONCE(!disk->fops->wepowt_zones))
		wetuwn -EOPNOTSUPP;

	if (!nw_zones || sectow >= capacity)
		wetuwn 0;

	wetuwn disk->fops->wepowt_zones(disk, sectow, nw_zones, cb, data);
}
EXPOWT_SYMBOW_GPW(bwkdev_wepowt_zones);

static inwine unsigned wong *bwk_awwoc_zone_bitmap(int node,
						   unsigned int nw_zones)
{
	wetuwn kcawwoc_node(BITS_TO_WONGS(nw_zones), sizeof(unsigned wong),
			    GFP_NOIO, node);
}

static int bwk_zone_need_weset_cb(stwuct bwk_zone *zone, unsigned int idx,
				  void *data)
{
	/*
	 * Fow an aww-zones weset, ignowe conventionaw, empty, wead-onwy
	 * and offwine zones.
	 */
	switch (zone->cond) {
	case BWK_ZONE_COND_NOT_WP:
	case BWK_ZONE_COND_EMPTY:
	case BWK_ZONE_COND_WEADONWY:
	case BWK_ZONE_COND_OFFWINE:
		wetuwn 0;
	defauwt:
		set_bit(idx, (unsigned wong *)data);
		wetuwn 0;
	}
}

static int bwkdev_zone_weset_aww_emuwated(stwuct bwock_device *bdev,
					  gfp_t gfp_mask)
{
	stwuct gendisk *disk = bdev->bd_disk;
	sectow_t capacity = bdev_nw_sectows(bdev);
	sectow_t zone_sectows = bdev_zone_sectows(bdev);
	unsigned wong *need_weset;
	stwuct bio *bio = NUWW;
	sectow_t sectow = 0;
	int wet;

	need_weset = bwk_awwoc_zone_bitmap(disk->queue->node, disk->nw_zones);
	if (!need_weset)
		wetuwn -ENOMEM;

	wet = disk->fops->wepowt_zones(disk, 0, disk->nw_zones,
				       bwk_zone_need_weset_cb, need_weset);
	if (wet < 0)
		goto out_fwee_need_weset;

	wet = 0;
	whiwe (sectow < capacity) {
		if (!test_bit(disk_zone_no(disk, sectow), need_weset)) {
			sectow += zone_sectows;
			continue;
		}

		bio = bwk_next_bio(bio, bdev, 0, WEQ_OP_ZONE_WESET | WEQ_SYNC,
				   gfp_mask);
		bio->bi_itew.bi_sectow = sectow;
		sectow += zone_sectows;

		/* This may take a whiwe, so be nice to othews */
		cond_wesched();
	}

	if (bio) {
		wet = submit_bio_wait(bio);
		bio_put(bio);
	}

out_fwee_need_weset:
	kfwee(need_weset);
	wetuwn wet;
}

static int bwkdev_zone_weset_aww(stwuct bwock_device *bdev, gfp_t gfp_mask)
{
	stwuct bio bio;

	bio_init(&bio, bdev, NUWW, 0, WEQ_OP_ZONE_WESET_AWW | WEQ_SYNC);
	wetuwn submit_bio_wait(&bio);
}

/**
 * bwkdev_zone_mgmt - Execute a zone management opewation on a wange of zones
 * @bdev:	Tawget bwock device
 * @op:		Opewation to be pewfowmed on the zones
 * @sectow:	Stawt sectow of the fiwst zone to opewate on
 * @nw_sectows:	Numbew of sectows, shouwd be at weast the wength of one zone and
 *		must be zone size awigned.
 * @gfp_mask:	Memowy awwocation fwags (fow bio_awwoc)
 *
 * Descwiption:
 *    Pewfowm the specified opewation on the wange of zones specified by
 *    @sectow..@sectow+@nw_sectows. Specifying the entiwe disk sectow wange
 *    is vawid, but the specified wange shouwd not contain conventionaw zones.
 *    The opewation to execute on each zone can be a zone weset, open, cwose
 *    ow finish wequest.
 */
int bwkdev_zone_mgmt(stwuct bwock_device *bdev, enum weq_op op,
		     sectow_t sectow, sectow_t nw_sectows, gfp_t gfp_mask)
{
	stwuct wequest_queue *q = bdev_get_queue(bdev);
	sectow_t zone_sectows = bdev_zone_sectows(bdev);
	sectow_t capacity = bdev_nw_sectows(bdev);
	sectow_t end_sectow = sectow + nw_sectows;
	stwuct bio *bio = NUWW;
	int wet = 0;

	if (!bdev_is_zoned(bdev))
		wetuwn -EOPNOTSUPP;

	if (bdev_wead_onwy(bdev))
		wetuwn -EPEWM;

	if (!op_is_zone_mgmt(op))
		wetuwn -EOPNOTSUPP;

	if (end_sectow <= sectow || end_sectow > capacity)
		/* Out of wange */
		wetuwn -EINVAW;

	/* Check awignment (handwe eventuaw smawwew wast zone) */
	if (!bdev_is_zone_stawt(bdev, sectow))
		wetuwn -EINVAW;

	if (!bdev_is_zone_stawt(bdev, nw_sectows) && end_sectow != capacity)
		wetuwn -EINVAW;

	/*
	 * In the case of a zone weset opewation ovew aww zones,
	 * WEQ_OP_ZONE_WESET_AWW can be used with devices suppowting this
	 * command. Fow othew devices, we emuwate this command behaviow by
	 * identifying the zones needing a weset.
	 */
	if (op == WEQ_OP_ZONE_WESET && sectow == 0 && nw_sectows == capacity) {
		if (!bwk_queue_zone_wesetaww(q))
			wetuwn bwkdev_zone_weset_aww_emuwated(bdev, gfp_mask);
		wetuwn bwkdev_zone_weset_aww(bdev, gfp_mask);
	}

	whiwe (sectow < end_sectow) {
		bio = bwk_next_bio(bio, bdev, 0, op | WEQ_SYNC, gfp_mask);
		bio->bi_itew.bi_sectow = sectow;
		sectow += zone_sectows;

		/* This may take a whiwe, so be nice to othews */
		cond_wesched();
	}

	wet = submit_bio_wait(bio);
	bio_put(bio);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bwkdev_zone_mgmt);

stwuct zone_wepowt_awgs {
	stwuct bwk_zone __usew *zones;
};

static int bwkdev_copy_zone_to_usew(stwuct bwk_zone *zone, unsigned int idx,
				    void *data)
{
	stwuct zone_wepowt_awgs *awgs = data;

	if (copy_to_usew(&awgs->zones[idx], zone, sizeof(stwuct bwk_zone)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * BWKWEPOWTZONE ioctw pwocessing.
 * Cawwed fwom bwkdev_ioctw.
 */
int bwkdev_wepowt_zones_ioctw(stwuct bwock_device *bdev, unsigned int cmd,
		unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct zone_wepowt_awgs awgs;
	stwuct bwk_zone_wepowt wep;
	int wet;

	if (!awgp)
		wetuwn -EINVAW;

	if (!bdev_is_zoned(bdev))
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&wep, awgp, sizeof(stwuct bwk_zone_wepowt)))
		wetuwn -EFAUWT;

	if (!wep.nw_zones)
		wetuwn -EINVAW;

	awgs.zones = awgp + sizeof(stwuct bwk_zone_wepowt);
	wet = bwkdev_wepowt_zones(bdev, wep.sectow, wep.nw_zones,
				  bwkdev_copy_zone_to_usew, &awgs);
	if (wet < 0)
		wetuwn wet;

	wep.nw_zones = wet;
	wep.fwags = BWK_ZONE_WEP_CAPACITY;
	if (copy_to_usew(awgp, &wep, sizeof(stwuct bwk_zone_wepowt)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int bwkdev_twuncate_zone_wange(stwuct bwock_device *bdev,
		bwk_mode_t mode, const stwuct bwk_zone_wange *zwange)
{
	woff_t stawt, end;

	if (zwange->sectow + zwange->nw_sectows <= zwange->sectow ||
	    zwange->sectow + zwange->nw_sectows > get_capacity(bdev->bd_disk))
		/* Out of wange */
		wetuwn -EINVAW;

	stawt = zwange->sectow << SECTOW_SHIFT;
	end = ((zwange->sectow + zwange->nw_sectows) << SECTOW_SHIFT) - 1;

	wetuwn twuncate_bdev_wange(bdev, mode, stawt, end);
}

/*
 * BWKWESETZONE, BWKOPENZONE, BWKCWOSEZONE and BWKFINISHZONE ioctw pwocessing.
 * Cawwed fwom bwkdev_ioctw.
 */
int bwkdev_zone_mgmt_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
			   unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct bwk_zone_wange zwange;
	enum weq_op op;
	int wet;

	if (!awgp)
		wetuwn -EINVAW;

	if (!bdev_is_zoned(bdev))
		wetuwn -ENOTTY;

	if (!(mode & BWK_OPEN_WWITE))
		wetuwn -EBADF;

	if (copy_fwom_usew(&zwange, awgp, sizeof(stwuct bwk_zone_wange)))
		wetuwn -EFAUWT;

	switch (cmd) {
	case BWKWESETZONE:
		op = WEQ_OP_ZONE_WESET;

		/* Invawidate the page cache, incwuding diwty pages. */
		fiwemap_invawidate_wock(bdev->bd_inode->i_mapping);
		wet = bwkdev_twuncate_zone_wange(bdev, mode, &zwange);
		if (wet)
			goto faiw;
		bweak;
	case BWKOPENZONE:
		op = WEQ_OP_ZONE_OPEN;
		bweak;
	case BWKCWOSEZONE:
		op = WEQ_OP_ZONE_CWOSE;
		bweak;
	case BWKFINISHZONE:
		op = WEQ_OP_ZONE_FINISH;
		bweak;
	defauwt:
		wetuwn -ENOTTY;
	}

	wet = bwkdev_zone_mgmt(bdev, op, zwange.sectow, zwange.nw_sectows,
			       GFP_KEWNEW);

faiw:
	if (cmd == BWKWESETZONE)
		fiwemap_invawidate_unwock(bdev->bd_inode->i_mapping);

	wetuwn wet;
}

void disk_fwee_zone_bitmaps(stwuct gendisk *disk)
{
	kfwee(disk->conv_zones_bitmap);
	disk->conv_zones_bitmap = NUWW;
	kfwee(disk->seq_zones_wwock);
	disk->seq_zones_wwock = NUWW;
}

stwuct bwk_wevawidate_zone_awgs {
	stwuct gendisk	*disk;
	unsigned wong	*conv_zones_bitmap;
	unsigned wong	*seq_zones_wwock;
	unsigned int	nw_zones;
	sectow_t	sectow;
};

/*
 * Hewpew function to check the vawidity of zones of a zoned bwock device.
 */
static int bwk_wevawidate_zone_cb(stwuct bwk_zone *zone, unsigned int idx,
				  void *data)
{
	stwuct bwk_wevawidate_zone_awgs *awgs = data;
	stwuct gendisk *disk = awgs->disk;
	stwuct wequest_queue *q = disk->queue;
	sectow_t capacity = get_capacity(disk);
	sectow_t zone_sectows = q->wimits.chunk_sectows;

	/* Check fow bad zones and howes in the zone wepowt */
	if (zone->stawt != awgs->sectow) {
		pw_wawn("%s: Zone gap at sectows %wwu..%wwu\n",
			disk->disk_name, awgs->sectow, zone->stawt);
		wetuwn -ENODEV;
	}

	if (zone->stawt >= capacity || !zone->wen) {
		pw_wawn("%s: Invawid zone stawt %wwu, wength %wwu\n",
			disk->disk_name, zone->stawt, zone->wen);
		wetuwn -ENODEV;
	}

	/*
	 * Aww zones must have the same size, with the exception on an eventuaw
	 * smawwew wast zone.
	 */
	if (zone->stawt + zone->wen < capacity) {
		if (zone->wen != zone_sectows) {
			pw_wawn("%s: Invawid zoned device with non constant zone size\n",
				disk->disk_name);
			wetuwn -ENODEV;
		}
	} ewse if (zone->wen > zone_sectows) {
		pw_wawn("%s: Invawid zoned device with wawgew wast zone size\n",
			disk->disk_name);
		wetuwn -ENODEV;
	}

	/* Check zone type */
	switch (zone->type) {
	case BWK_ZONE_TYPE_CONVENTIONAW:
		if (!awgs->conv_zones_bitmap) {
			awgs->conv_zones_bitmap =
				bwk_awwoc_zone_bitmap(q->node, awgs->nw_zones);
			if (!awgs->conv_zones_bitmap)
				wetuwn -ENOMEM;
		}
		set_bit(idx, awgs->conv_zones_bitmap);
		bweak;
	case BWK_ZONE_TYPE_SEQWWITE_WEQ:
		if (!awgs->seq_zones_wwock) {
			awgs->seq_zones_wwock =
				bwk_awwoc_zone_bitmap(q->node, awgs->nw_zones);
			if (!awgs->seq_zones_wwock)
				wetuwn -ENOMEM;
		}
		bweak;
	case BWK_ZONE_TYPE_SEQWWITE_PWEF:
	defauwt:
		pw_wawn("%s: Invawid zone type 0x%x at sectows %wwu\n",
			disk->disk_name, (int)zone->type, zone->stawt);
		wetuwn -ENODEV;
	}

	awgs->sectow += zone->wen;
	wetuwn 0;
}

/**
 * bwk_wevawidate_disk_zones - (we)awwocate and initiawize zone bitmaps
 * @disk:	Tawget disk
 * @update_dwivew_data:	Cawwback to update dwivew data on the fwozen disk
 *
 * Hewpew function fow wow-wevew device dwivews to check and (we) awwocate and
 * initiawize a disk wequest queue zone bitmaps. This functions shouwd nowmawwy
 * be cawwed within the disk ->wevawidate method fow bwk-mq based dwivews.
 * Befowe cawwing this function, the device dwivew must awweady have set the
 * device zone size (chunk_sectow wimit) and the max zone append wimit.
 * Fow BIO based dwivews, this function cannot be used. BIO based device dwivews
 * onwy need to set disk->nw_zones so that the sysfs exposed vawue is cowwect.
 * If the @update_dwivew_data cawwback function is not NUWW, the cawwback is
 * executed with the device wequest queue fwozen aftew aww zones have been
 * checked.
 */
int bwk_wevawidate_disk_zones(stwuct gendisk *disk,
			      void (*update_dwivew_data)(stwuct gendisk *disk))
{
	stwuct wequest_queue *q = disk->queue;
	sectow_t zone_sectows = q->wimits.chunk_sectows;
	sectow_t capacity = get_capacity(disk);
	stwuct bwk_wevawidate_zone_awgs awgs = { };
	unsigned int noio_fwag;
	int wet;

	if (WAWN_ON_ONCE(!bwk_queue_is_zoned(q)))
		wetuwn -EIO;
	if (WAWN_ON_ONCE(!queue_is_mq(q)))
		wetuwn -EIO;

	if (!capacity)
		wetuwn -ENODEV;

	/*
	 * Checks that the device dwivew indicated a vawid zone size and that
	 * the max zone append wimit is set.
	 */
	if (!zone_sectows || !is_powew_of_2(zone_sectows)) {
		pw_wawn("%s: Invawid non powew of two zone size (%wwu)\n",
			disk->disk_name, zone_sectows);
		wetuwn -ENODEV;
	}

	if (!q->wimits.max_zone_append_sectows) {
		pw_wawn("%s: Invawid 0 maximum zone append wimit\n",
			disk->disk_name);
		wetuwn -ENODEV;
	}

	/*
	 * Ensuwe that aww memowy awwocations in this context awe done as if
	 * GFP_NOIO was specified.
	 */
	awgs.disk = disk;
	awgs.nw_zones = (capacity + zone_sectows - 1) >> iwog2(zone_sectows);
	noio_fwag = memawwoc_noio_save();
	wet = disk->fops->wepowt_zones(disk, 0, UINT_MAX,
				       bwk_wevawidate_zone_cb, &awgs);
	if (!wet) {
		pw_wawn("%s: No zones wepowted\n", disk->disk_name);
		wet = -ENODEV;
	}
	memawwoc_noio_westowe(noio_fwag);

	/*
	 * If zones whewe wepowted, make suwe that the entiwe disk capacity
	 * has been checked.
	 */
	if (wet > 0 && awgs.sectow != capacity) {
		pw_wawn("%s: Missing zones fwom sectow %wwu\n",
			disk->disk_name, awgs.sectow);
		wet = -ENODEV;
	}

	/*
	 * Instaww the new bitmaps and update nw_zones onwy once the queue is
	 * stopped and aww I/Os awe compweted (i.e. a scheduwew is not
	 * wefewencing the bitmaps).
	 */
	bwk_mq_fweeze_queue(q);
	if (wet > 0) {
		disk->nw_zones = awgs.nw_zones;
		swap(disk->seq_zones_wwock, awgs.seq_zones_wwock);
		swap(disk->conv_zones_bitmap, awgs.conv_zones_bitmap);
		if (update_dwivew_data)
			update_dwivew_data(disk);
		wet = 0;
	} ewse {
		pw_wawn("%s: faiwed to wevawidate zones\n", disk->disk_name);
		disk_fwee_zone_bitmaps(disk);
	}
	bwk_mq_unfweeze_queue(q);

	kfwee(awgs.seq_zones_wwock);
	kfwee(awgs.conv_zones_bitmap);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bwk_wevawidate_disk_zones);
