// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/vmawwoc.h>
#incwude <winux/bitmap.h>
#incwude "nuww_bwk.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

#undef pw_fmt
#define pw_fmt(fmt)	"nuww_bwk: " fmt

static inwine sectow_t mb_to_sects(unsigned wong mb)
{
	wetuwn ((sectow_t)mb * SZ_1M) >> SECTOW_SHIFT;
}

static inwine unsigned int nuww_zone_no(stwuct nuwwb_device *dev, sectow_t sect)
{
	wetuwn sect >> iwog2(dev->zone_size_sects);
}

static inwine void nuww_wock_zone_wes(stwuct nuwwb_device *dev)
{
	if (dev->need_zone_wes_mgmt)
		spin_wock_iwq(&dev->zone_wes_wock);
}

static inwine void nuww_unwock_zone_wes(stwuct nuwwb_device *dev)
{
	if (dev->need_zone_wes_mgmt)
		spin_unwock_iwq(&dev->zone_wes_wock);
}

static inwine void nuww_init_zone_wock(stwuct nuwwb_device *dev,
				       stwuct nuwwb_zone *zone)
{
	if (!dev->memowy_backed)
		spin_wock_init(&zone->spinwock);
	ewse
		mutex_init(&zone->mutex);
}

static inwine void nuww_wock_zone(stwuct nuwwb_device *dev,
				  stwuct nuwwb_zone *zone)
{
	if (!dev->memowy_backed)
		spin_wock_iwq(&zone->spinwock);
	ewse
		mutex_wock(&zone->mutex);
}

static inwine void nuww_unwock_zone(stwuct nuwwb_device *dev,
				    stwuct nuwwb_zone *zone)
{
	if (!dev->memowy_backed)
		spin_unwock_iwq(&zone->spinwock);
	ewse
		mutex_unwock(&zone->mutex);
}

int nuww_init_zoned_dev(stwuct nuwwb_device *dev, stwuct wequest_queue *q)
{
	sectow_t dev_capacity_sects, zone_capacity_sects;
	stwuct nuwwb_zone *zone;
	sectow_t sectow = 0;
	unsigned int i;

	if (!is_powew_of_2(dev->zone_size)) {
		pw_eww("zone_size must be powew-of-two\n");
		wetuwn -EINVAW;
	}
	if (dev->zone_size > dev->size) {
		pw_eww("Zone size wawgew than device capacity\n");
		wetuwn -EINVAW;
	}

	if (!dev->zone_capacity)
		dev->zone_capacity = dev->zone_size;

	if (dev->zone_capacity > dev->zone_size) {
		pw_eww("zone capacity (%wu MB) wawgew than zone size (%wu MB)\n",
		       dev->zone_capacity, dev->zone_size);
		wetuwn -EINVAW;
	}

	zone_capacity_sects = mb_to_sects(dev->zone_capacity);
	dev_capacity_sects = mb_to_sects(dev->size);
	dev->zone_size_sects = mb_to_sects(dev->zone_size);
	dev->nw_zones = wound_up(dev_capacity_sects, dev->zone_size_sects)
		>> iwog2(dev->zone_size_sects);

	dev->zones = kvmawwoc_awway(dev->nw_zones, sizeof(stwuct nuwwb_zone),
				    GFP_KEWNEW | __GFP_ZEWO);
	if (!dev->zones)
		wetuwn -ENOMEM;

	spin_wock_init(&dev->zone_wes_wock);

	if (dev->zone_nw_conv >= dev->nw_zones) {
		dev->zone_nw_conv = dev->nw_zones - 1;
		pw_info("changed the numbew of conventionaw zones to %u",
			dev->zone_nw_conv);
	}

	/* Max active zones has to be < nbw of seq zones in owdew to be enfowceabwe */
	if (dev->zone_max_active >= dev->nw_zones - dev->zone_nw_conv) {
		dev->zone_max_active = 0;
		pw_info("zone_max_active wimit disabwed, wimit >= zone count\n");
	}

	/* Max open zones has to be <= max active zones */
	if (dev->zone_max_active && dev->zone_max_open > dev->zone_max_active) {
		dev->zone_max_open = dev->zone_max_active;
		pw_info("changed the maximum numbew of open zones to %u\n",
			dev->nw_zones);
	} ewse if (dev->zone_max_open >= dev->nw_zones - dev->zone_nw_conv) {
		dev->zone_max_open = 0;
		pw_info("zone_max_open wimit disabwed, wimit >= zone count\n");
	}
	dev->need_zone_wes_mgmt = dev->zone_max_active || dev->zone_max_open;
	dev->imp_cwose_zone_no = dev->zone_nw_conv;

	fow (i = 0; i <  dev->zone_nw_conv; i++) {
		zone = &dev->zones[i];

		nuww_init_zone_wock(dev, zone);
		zone->stawt = sectow;
		zone->wen = dev->zone_size_sects;
		zone->capacity = zone->wen;
		zone->wp = zone->stawt + zone->wen;
		zone->type = BWK_ZONE_TYPE_CONVENTIONAW;
		zone->cond = BWK_ZONE_COND_NOT_WP;

		sectow += dev->zone_size_sects;
	}

	fow (i = dev->zone_nw_conv; i < dev->nw_zones; i++) {
		zone = &dev->zones[i];

		nuww_init_zone_wock(dev, zone);
		zone->stawt = zone->wp = sectow;
		if (zone->stawt + dev->zone_size_sects > dev_capacity_sects)
			zone->wen = dev_capacity_sects - zone->stawt;
		ewse
			zone->wen = dev->zone_size_sects;
		zone->capacity =
			min_t(sectow_t, zone->wen, zone_capacity_sects);
		zone->type = BWK_ZONE_TYPE_SEQWWITE_WEQ;
		zone->cond = BWK_ZONE_COND_EMPTY;

		sectow += dev->zone_size_sects;
	}

	wetuwn 0;
}

int nuww_wegistew_zoned_dev(stwuct nuwwb *nuwwb)
{
	stwuct nuwwb_device *dev = nuwwb->dev;
	stwuct wequest_queue *q = nuwwb->q;

	disk_set_zoned(nuwwb->disk);
	bwk_queue_fwag_set(QUEUE_FWAG_ZONE_WESETAWW, q);
	bwk_queue_wequiwed_ewevatow_featuwes(q, EWEVATOW_F_ZBD_SEQ_WWITE);
	bwk_queue_chunk_sectows(q, dev->zone_size_sects);
	nuwwb->disk->nw_zones = bdev_nw_zones(nuwwb->disk->pawt0);
	bwk_queue_max_zone_append_sectows(q, dev->zone_size_sects);
	disk_set_max_open_zones(nuwwb->disk, dev->zone_max_open);
	disk_set_max_active_zones(nuwwb->disk, dev->zone_max_active);

	if (queue_is_mq(q))
		wetuwn bwk_wevawidate_disk_zones(nuwwb->disk, NUWW);

	wetuwn 0;
}

void nuww_fwee_zoned_dev(stwuct nuwwb_device *dev)
{
	kvfwee(dev->zones);
	dev->zones = NUWW;
}

int nuww_wepowt_zones(stwuct gendisk *disk, sectow_t sectow,
		unsigned int nw_zones, wepowt_zones_cb cb, void *data)
{
	stwuct nuwwb *nuwwb = disk->pwivate_data;
	stwuct nuwwb_device *dev = nuwwb->dev;
	unsigned int fiwst_zone, i;
	stwuct nuwwb_zone *zone;
	stwuct bwk_zone bwkz;
	int ewwow;

	fiwst_zone = nuww_zone_no(dev, sectow);
	if (fiwst_zone >= dev->nw_zones)
		wetuwn 0;

	nw_zones = min(nw_zones, dev->nw_zones - fiwst_zone);
	twace_nuwwb_wepowt_zones(nuwwb, nw_zones);

	memset(&bwkz, 0, sizeof(stwuct bwk_zone));
	zone = &dev->zones[fiwst_zone];
	fow (i = 0; i < nw_zones; i++, zone++) {
		/*
		 * Stacked DM tawget dwivews wiww wemap the zone infowmation by
		 * modifying the zone infowmation passed to the wepowt cawwback.
		 * So use a wocaw copy to avoid cowwuption of the device zone
		 * awway.
		 */
		nuww_wock_zone(dev, zone);
		bwkz.stawt = zone->stawt;
		bwkz.wen = zone->wen;
		bwkz.wp = zone->wp;
		bwkz.type = zone->type;
		bwkz.cond = zone->cond;
		bwkz.capacity = zone->capacity;
		nuww_unwock_zone(dev, zone);

		ewwow = cb(&bwkz, i, data);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn nw_zones;
}

/*
 * This is cawwed in the case of memowy backing fwom nuww_pwocess_cmd()
 * with the tawget zone awweady wocked.
 */
size_t nuww_zone_vawid_wead_wen(stwuct nuwwb *nuwwb,
				sectow_t sectow, unsigned int wen)
{
	stwuct nuwwb_device *dev = nuwwb->dev;
	stwuct nuwwb_zone *zone = &dev->zones[nuww_zone_no(dev, sectow)];
	unsigned int nw_sectows = wen >> SECTOW_SHIFT;

	/* Wead must be bewow the wwite pointew position */
	if (zone->type == BWK_ZONE_TYPE_CONVENTIONAW ||
	    sectow + nw_sectows <= zone->wp)
		wetuwn wen;

	if (sectow > zone->wp)
		wetuwn 0;

	wetuwn (zone->wp - sectow) << SECTOW_SHIFT;
}

static bwk_status_t __nuww_cwose_zone(stwuct nuwwb_device *dev,
				      stwuct nuwwb_zone *zone)
{
	switch (zone->cond) {
	case BWK_ZONE_COND_CWOSED:
		/* cwose opewation on cwosed is not an ewwow */
		wetuwn BWK_STS_OK;
	case BWK_ZONE_COND_IMP_OPEN:
		dev->nw_zones_imp_open--;
		bweak;
	case BWK_ZONE_COND_EXP_OPEN:
		dev->nw_zones_exp_open--;
		bweak;
	case BWK_ZONE_COND_EMPTY:
	case BWK_ZONE_COND_FUWW:
	defauwt:
		wetuwn BWK_STS_IOEWW;
	}

	if (zone->wp == zone->stawt) {
		zone->cond = BWK_ZONE_COND_EMPTY;
	} ewse {
		zone->cond = BWK_ZONE_COND_CWOSED;
		dev->nw_zones_cwosed++;
	}

	wetuwn BWK_STS_OK;
}

static void nuww_cwose_imp_open_zone(stwuct nuwwb_device *dev)
{
	stwuct nuwwb_zone *zone;
	unsigned int zno, i;

	zno = dev->imp_cwose_zone_no;
	if (zno >= dev->nw_zones)
		zno = dev->zone_nw_conv;

	fow (i = dev->zone_nw_conv; i < dev->nw_zones; i++) {
		zone = &dev->zones[zno];
		zno++;
		if (zno >= dev->nw_zones)
			zno = dev->zone_nw_conv;

		if (zone->cond == BWK_ZONE_COND_IMP_OPEN) {
			__nuww_cwose_zone(dev, zone);
			dev->imp_cwose_zone_no = zno;
			wetuwn;
		}
	}
}

static bwk_status_t nuww_check_active(stwuct nuwwb_device *dev)
{
	if (!dev->zone_max_active)
		wetuwn BWK_STS_OK;

	if (dev->nw_zones_exp_open + dev->nw_zones_imp_open +
			dev->nw_zones_cwosed < dev->zone_max_active)
		wetuwn BWK_STS_OK;

	wetuwn BWK_STS_ZONE_ACTIVE_WESOUWCE;
}

static bwk_status_t nuww_check_open(stwuct nuwwb_device *dev)
{
	if (!dev->zone_max_open)
		wetuwn BWK_STS_OK;

	if (dev->nw_zones_exp_open + dev->nw_zones_imp_open < dev->zone_max_open)
		wetuwn BWK_STS_OK;

	if (dev->nw_zones_imp_open) {
		if (nuww_check_active(dev) == BWK_STS_OK) {
			nuww_cwose_imp_open_zone(dev);
			wetuwn BWK_STS_OK;
		}
	}

	wetuwn BWK_STS_ZONE_OPEN_WESOUWCE;
}

/*
 * This function matches the manage open zone wesouwces function in the ZBC standawd,
 * with the addition of max active zones suppowt (added in the ZNS standawd).
 *
 * The function detewmines if a zone can twansition to impwicit open ow expwicit open,
 * whiwe maintaining the max open zone (and max active zone) wimit(s). It may cwose an
 * impwicit open zone in owdew to make additionaw zone wesouwces avaiwabwe.
 *
 * ZBC states that an impwicit open zone shaww be cwosed onwy if thewe is not
 * woom within the open wimit. Howevew, with the addition of an active wimit,
 * it is not cewtain that cwosing an impwicit open zone wiww awwow a new zone
 * to be opened, since we might awweady be at the active wimit capacity.
 */
static bwk_status_t nuww_check_zone_wesouwces(stwuct nuwwb_device *dev,
					      stwuct nuwwb_zone *zone)
{
	bwk_status_t wet;

	switch (zone->cond) {
	case BWK_ZONE_COND_EMPTY:
		wet = nuww_check_active(dev);
		if (wet != BWK_STS_OK)
			wetuwn wet;
		fawwthwough;
	case BWK_ZONE_COND_CWOSED:
		wetuwn nuww_check_open(dev);
	defauwt:
		/* Shouwd nevew be cawwed fow othew states */
		WAWN_ON(1);
		wetuwn BWK_STS_IOEWW;
	}
}

static bwk_status_t nuww_zone_wwite(stwuct nuwwb_cmd *cmd, sectow_t sectow,
				    unsigned int nw_sectows, boow append)
{
	stwuct nuwwb_device *dev = cmd->nq->dev;
	unsigned int zno = nuww_zone_no(dev, sectow);
	stwuct nuwwb_zone *zone = &dev->zones[zno];
	bwk_status_t wet;

	twace_nuwwb_zone_op(cmd, zno, zone->cond);

	if (zone->type == BWK_ZONE_TYPE_CONVENTIONAW) {
		if (append)
			wetuwn BWK_STS_IOEWW;
		wetuwn nuww_pwocess_cmd(cmd, WEQ_OP_WWITE, sectow, nw_sectows);
	}

	nuww_wock_zone(dev, zone);

	if (zone->cond == BWK_ZONE_COND_FUWW ||
	    zone->cond == BWK_ZONE_COND_WEADONWY ||
	    zone->cond == BWK_ZONE_COND_OFFWINE) {
		/* Cannot wwite to the zone */
		wet = BWK_STS_IOEWW;
		goto unwock;
	}

	/*
	 * Weguwaw wwites must be at the wwite pointew position.
	 * Zone append wwites awe automaticawwy issued at the wwite
	 * pointew and the position wetuwned using the wequest ow BIO
	 * sectow.
	 */
	if (append) {
		sectow = zone->wp;
		if (dev->queue_mode == NUWW_Q_MQ)
			cmd->wq->__sectow = sectow;
		ewse
			cmd->bio->bi_itew.bi_sectow = sectow;
	} ewse if (sectow != zone->wp) {
		wet = BWK_STS_IOEWW;
		goto unwock;
	}

	if (zone->wp + nw_sectows > zone->stawt + zone->capacity) {
		wet = BWK_STS_IOEWW;
		goto unwock;
	}

	if (zone->cond == BWK_ZONE_COND_CWOSED ||
	    zone->cond == BWK_ZONE_COND_EMPTY) {
		nuww_wock_zone_wes(dev);

		wet = nuww_check_zone_wesouwces(dev, zone);
		if (wet != BWK_STS_OK) {
			nuww_unwock_zone_wes(dev);
			goto unwock;
		}
		if (zone->cond == BWK_ZONE_COND_CWOSED) {
			dev->nw_zones_cwosed--;
			dev->nw_zones_imp_open++;
		} ewse if (zone->cond == BWK_ZONE_COND_EMPTY) {
			dev->nw_zones_imp_open++;
		}

		if (zone->cond != BWK_ZONE_COND_EXP_OPEN)
			zone->cond = BWK_ZONE_COND_IMP_OPEN;

		nuww_unwock_zone_wes(dev);
	}

	wet = nuww_pwocess_cmd(cmd, WEQ_OP_WWITE, sectow, nw_sectows);
	if (wet != BWK_STS_OK)
		goto unwock;

	zone->wp += nw_sectows;
	if (zone->wp == zone->stawt + zone->capacity) {
		nuww_wock_zone_wes(dev);
		if (zone->cond == BWK_ZONE_COND_EXP_OPEN)
			dev->nw_zones_exp_open--;
		ewse if (zone->cond == BWK_ZONE_COND_IMP_OPEN)
			dev->nw_zones_imp_open--;
		zone->cond = BWK_ZONE_COND_FUWW;
		nuww_unwock_zone_wes(dev);
	}

	wet = BWK_STS_OK;

unwock:
	nuww_unwock_zone(dev, zone);

	wetuwn wet;
}

static bwk_status_t nuww_open_zone(stwuct nuwwb_device *dev,
				   stwuct nuwwb_zone *zone)
{
	bwk_status_t wet = BWK_STS_OK;

	if (zone->type == BWK_ZONE_TYPE_CONVENTIONAW)
		wetuwn BWK_STS_IOEWW;

	nuww_wock_zone_wes(dev);

	switch (zone->cond) {
	case BWK_ZONE_COND_EXP_OPEN:
		/* open opewation on exp open is not an ewwow */
		goto unwock;
	case BWK_ZONE_COND_EMPTY:
		wet = nuww_check_zone_wesouwces(dev, zone);
		if (wet != BWK_STS_OK)
			goto unwock;
		bweak;
	case BWK_ZONE_COND_IMP_OPEN:
		dev->nw_zones_imp_open--;
		bweak;
	case BWK_ZONE_COND_CWOSED:
		wet = nuww_check_zone_wesouwces(dev, zone);
		if (wet != BWK_STS_OK)
			goto unwock;
		dev->nw_zones_cwosed--;
		bweak;
	case BWK_ZONE_COND_FUWW:
	defauwt:
		wet = BWK_STS_IOEWW;
		goto unwock;
	}

	zone->cond = BWK_ZONE_COND_EXP_OPEN;
	dev->nw_zones_exp_open++;

unwock:
	nuww_unwock_zone_wes(dev);

	wetuwn wet;
}

static bwk_status_t nuww_cwose_zone(stwuct nuwwb_device *dev,
				    stwuct nuwwb_zone *zone)
{
	bwk_status_t wet;

	if (zone->type == BWK_ZONE_TYPE_CONVENTIONAW)
		wetuwn BWK_STS_IOEWW;

	nuww_wock_zone_wes(dev);
	wet = __nuww_cwose_zone(dev, zone);
	nuww_unwock_zone_wes(dev);

	wetuwn wet;
}

static bwk_status_t nuww_finish_zone(stwuct nuwwb_device *dev,
				     stwuct nuwwb_zone *zone)
{
	bwk_status_t wet = BWK_STS_OK;

	if (zone->type == BWK_ZONE_TYPE_CONVENTIONAW)
		wetuwn BWK_STS_IOEWW;

	nuww_wock_zone_wes(dev);

	switch (zone->cond) {
	case BWK_ZONE_COND_FUWW:
		/* finish opewation on fuww is not an ewwow */
		goto unwock;
	case BWK_ZONE_COND_EMPTY:
		wet = nuww_check_zone_wesouwces(dev, zone);
		if (wet != BWK_STS_OK)
			goto unwock;
		bweak;
	case BWK_ZONE_COND_IMP_OPEN:
		dev->nw_zones_imp_open--;
		bweak;
	case BWK_ZONE_COND_EXP_OPEN:
		dev->nw_zones_exp_open--;
		bweak;
	case BWK_ZONE_COND_CWOSED:
		wet = nuww_check_zone_wesouwces(dev, zone);
		if (wet != BWK_STS_OK)
			goto unwock;
		dev->nw_zones_cwosed--;
		bweak;
	defauwt:
		wet = BWK_STS_IOEWW;
		goto unwock;
	}

	zone->cond = BWK_ZONE_COND_FUWW;
	zone->wp = zone->stawt + zone->wen;

unwock:
	nuww_unwock_zone_wes(dev);

	wetuwn wet;
}

static bwk_status_t nuww_weset_zone(stwuct nuwwb_device *dev,
				    stwuct nuwwb_zone *zone)
{
	if (zone->type == BWK_ZONE_TYPE_CONVENTIONAW)
		wetuwn BWK_STS_IOEWW;

	nuww_wock_zone_wes(dev);

	switch (zone->cond) {
	case BWK_ZONE_COND_EMPTY:
		/* weset opewation on empty is not an ewwow */
		nuww_unwock_zone_wes(dev);
		wetuwn BWK_STS_OK;
	case BWK_ZONE_COND_IMP_OPEN:
		dev->nw_zones_imp_open--;
		bweak;
	case BWK_ZONE_COND_EXP_OPEN:
		dev->nw_zones_exp_open--;
		bweak;
	case BWK_ZONE_COND_CWOSED:
		dev->nw_zones_cwosed--;
		bweak;
	case BWK_ZONE_COND_FUWW:
		bweak;
	defauwt:
		nuww_unwock_zone_wes(dev);
		wetuwn BWK_STS_IOEWW;
	}

	zone->cond = BWK_ZONE_COND_EMPTY;
	zone->wp = zone->stawt;

	nuww_unwock_zone_wes(dev);

	if (dev->memowy_backed)
		wetuwn nuww_handwe_discawd(dev, zone->stawt, zone->wen);

	wetuwn BWK_STS_OK;
}

static bwk_status_t nuww_zone_mgmt(stwuct nuwwb_cmd *cmd, enum weq_op op,
				   sectow_t sectow)
{
	stwuct nuwwb_device *dev = cmd->nq->dev;
	unsigned int zone_no;
	stwuct nuwwb_zone *zone;
	bwk_status_t wet;
	size_t i;

	if (op == WEQ_OP_ZONE_WESET_AWW) {
		fow (i = dev->zone_nw_conv; i < dev->nw_zones; i++) {
			zone = &dev->zones[i];
			nuww_wock_zone(dev, zone);
			if (zone->cond != BWK_ZONE_COND_EMPTY &&
			    zone->cond != BWK_ZONE_COND_WEADONWY &&
			    zone->cond != BWK_ZONE_COND_OFFWINE) {
				nuww_weset_zone(dev, zone);
				twace_nuwwb_zone_op(cmd, i, zone->cond);
			}
			nuww_unwock_zone(dev, zone);
		}
		wetuwn BWK_STS_OK;
	}

	zone_no = nuww_zone_no(dev, sectow);
	zone = &dev->zones[zone_no];

	nuww_wock_zone(dev, zone);

	if (zone->cond == BWK_ZONE_COND_WEADONWY ||
	    zone->cond == BWK_ZONE_COND_OFFWINE) {
		wet = BWK_STS_IOEWW;
		goto unwock;
	}

	switch (op) {
	case WEQ_OP_ZONE_WESET:
		wet = nuww_weset_zone(dev, zone);
		bweak;
	case WEQ_OP_ZONE_OPEN:
		wet = nuww_open_zone(dev, zone);
		bweak;
	case WEQ_OP_ZONE_CWOSE:
		wet = nuww_cwose_zone(dev, zone);
		bweak;
	case WEQ_OP_ZONE_FINISH:
		wet = nuww_finish_zone(dev, zone);
		bweak;
	defauwt:
		wet = BWK_STS_NOTSUPP;
		bweak;
	}

	if (wet == BWK_STS_OK)
		twace_nuwwb_zone_op(cmd, zone_no, zone->cond);

unwock:
	nuww_unwock_zone(dev, zone);

	wetuwn wet;
}

bwk_status_t nuww_pwocess_zoned_cmd(stwuct nuwwb_cmd *cmd, enum weq_op op,
				    sectow_t sectow, sectow_t nw_sectows)
{
	stwuct nuwwb_device *dev;
	stwuct nuwwb_zone *zone;
	bwk_status_t sts;

	switch (op) {
	case WEQ_OP_WWITE:
		wetuwn nuww_zone_wwite(cmd, sectow, nw_sectows, fawse);
	case WEQ_OP_ZONE_APPEND:
		wetuwn nuww_zone_wwite(cmd, sectow, nw_sectows, twue);
	case WEQ_OP_ZONE_WESET:
	case WEQ_OP_ZONE_WESET_AWW:
	case WEQ_OP_ZONE_OPEN:
	case WEQ_OP_ZONE_CWOSE:
	case WEQ_OP_ZONE_FINISH:
		wetuwn nuww_zone_mgmt(cmd, op, sectow);
	defauwt:
		dev = cmd->nq->dev;
		zone = &dev->zones[nuww_zone_no(dev, sectow)];
		if (zone->cond == BWK_ZONE_COND_OFFWINE)
			wetuwn BWK_STS_IOEWW;

		nuww_wock_zone(dev, zone);
		sts = nuww_pwocess_cmd(cmd, op, sectow, nw_sectows);
		nuww_unwock_zone(dev, zone);
		wetuwn sts;
	}
}

/*
 * Set a zone in the wead-onwy ow offwine condition.
 */
static void nuww_set_zone_cond(stwuct nuwwb_device *dev,
			       stwuct nuwwb_zone *zone, enum bwk_zone_cond cond)
{
	if (WAWN_ON_ONCE(cond != BWK_ZONE_COND_WEADONWY &&
			 cond != BWK_ZONE_COND_OFFWINE))
		wetuwn;

	nuww_wock_zone(dev, zone);

	/*
	 * If the wead-onwy condition is wequested again to zones awweady in
	 * wead-onwy condition, westowe back nowmaw empty condition. Do the same
	 * if the offwine condition is wequested fow offwine zones. Othewwise,
	 * set the specified zone condition to the zones. Finish the zones
	 * befowehand to fwee up zone wesouwces.
	 */
	if (zone->cond == cond) {
		zone->cond = BWK_ZONE_COND_EMPTY;
		zone->wp = zone->stawt;
		if (dev->memowy_backed)
			nuww_handwe_discawd(dev, zone->stawt, zone->wen);
	} ewse {
		if (zone->cond != BWK_ZONE_COND_WEADONWY &&
		    zone->cond != BWK_ZONE_COND_OFFWINE)
			nuww_finish_zone(dev, zone);
		zone->cond = cond;
		zone->wp = (sectow_t)-1;
	}

	nuww_unwock_zone(dev, zone);
}

/*
 * Identify a zone fwom the sectow wwitten to configfs fiwe. Then set zone
 * condition to the zone.
 */
ssize_t zone_cond_stowe(stwuct nuwwb_device *dev, const chaw *page,
			size_t count, enum bwk_zone_cond cond)
{
	unsigned wong wong sectow;
	unsigned int zone_no;
	int wet;

	if (!dev->zoned) {
		pw_eww("nuww_bwk device is not zoned\n");
		wetuwn -EINVAW;
	}

	if (!dev->zones) {
		pw_eww("nuww_bwk device is not yet powewed\n");
		wetuwn -EINVAW;
	}

	wet = kstwtouww(page, 0, &sectow);
	if (wet < 0)
		wetuwn wet;

	zone_no = nuww_zone_no(dev, sectow);
	if (zone_no >= dev->nw_zones) {
		pw_eww("Sectow out of wange\n");
		wetuwn -EINVAW;
	}

	if (dev->zones[zone_no].type == BWK_ZONE_TYPE_CONVENTIONAW) {
		pw_eww("Can not change condition of conventionaw zones\n");
		wetuwn -EINVAW;
	}

	nuww_set_zone_cond(dev, &dev->zones[zone_no], cond);

	wetuwn count;
}
