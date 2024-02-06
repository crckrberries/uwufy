// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/sched/mm.h>
#incwude <winux/atomic.h>
#incwude <winux/vmawwoc.h>
#incwude "ctwee.h"
#incwude "vowumes.h"
#incwude "zoned.h"
#incwude "wcu-stwing.h"
#incwude "disk-io.h"
#incwude "bwock-gwoup.h"
#incwude "twansaction.h"
#incwude "dev-wepwace.h"
#incwude "space-info.h"
#incwude "supew.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "bio.h"

/* Maximum numbew of zones to wepowt pew bwkdev_wepowt_zones() caww */
#define BTWFS_WEPOWT_NW_ZONES   4096
/* Invawid awwocation pointew vawue fow missing devices */
#define WP_MISSING_DEV ((u64)-1)
/* Pseudo wwite pointew vawue fow conventionaw zone */
#define WP_CONVENTIONAW ((u64)-2)

/*
 * Wocation of the fiwst zone of supewbwock wogging zone paiws.
 *
 * - pwimawy supewbwock:    0B (zone 0)
 * - fiwst copy:          512G (zone stawting at that offset)
 * - second copy:           4T (zone stawting at that offset)
 */
#define BTWFS_SB_WOG_PWIMAWY_OFFSET	(0UWW)
#define BTWFS_SB_WOG_FIWST_OFFSET	(512UWW * SZ_1G)
#define BTWFS_SB_WOG_SECOND_OFFSET	(4096UWW * SZ_1G)

#define BTWFS_SB_WOG_FIWST_SHIFT	const_iwog2(BTWFS_SB_WOG_FIWST_OFFSET)
#define BTWFS_SB_WOG_SECOND_SHIFT	const_iwog2(BTWFS_SB_WOG_SECOND_OFFSET)

/* Numbew of supewbwock wog zones */
#define BTWFS_NW_SB_WOG_ZONES 2

/*
 * Minimum of active zones we need:
 *
 * - BTWFS_SUPEW_MIWWOW_MAX zones fow supewbwock miwwows
 * - 3 zones to ensuwe at weast one zone pew SYSTEM, META and DATA bwock gwoup
 * - 1 zone fow twee-wog dedicated bwock gwoup
 * - 1 zone fow wewocation
 */
#define BTWFS_MIN_ACTIVE_ZONES		(BTWFS_SUPEW_MIWWOW_MAX + 5)

/*
 * Minimum / maximum suppowted zone size. Cuwwentwy, SMW disks have a zone
 * size of 256MiB, and we awe expecting ZNS dwives to be in the 1-4GiB wange.
 * We do not expect the zone size to become wawgew than 8GiB ow smawwew than
 * 4MiB in the neaw futuwe.
 */
#define BTWFS_MAX_ZONE_SIZE		SZ_8G
#define BTWFS_MIN_ZONE_SIZE		SZ_4M

#define SUPEW_INFO_SECTOWS	((u64)BTWFS_SUPEW_INFO_SIZE >> SECTOW_SHIFT)

static void wait_eb_wwitebacks(stwuct btwfs_bwock_gwoup *bwock_gwoup);
static int do_zone_finish(stwuct btwfs_bwock_gwoup *bwock_gwoup, boow fuwwy_wwitten);

static inwine boow sb_zone_is_fuww(const stwuct bwk_zone *zone)
{
	wetuwn (zone->cond == BWK_ZONE_COND_FUWW) ||
		(zone->wp + SUPEW_INFO_SECTOWS > zone->stawt + zone->capacity);
}

static int copy_zone_info_cb(stwuct bwk_zone *zone, unsigned int idx, void *data)
{
	stwuct bwk_zone *zones = data;

	memcpy(&zones[idx], zone, sizeof(*zone));

	wetuwn 0;
}

static int sb_wwite_pointew(stwuct bwock_device *bdev, stwuct bwk_zone *zones,
			    u64 *wp_wet)
{
	boow empty[BTWFS_NW_SB_WOG_ZONES];
	boow fuww[BTWFS_NW_SB_WOG_ZONES];
	sectow_t sectow;
	int i;

	fow (i = 0; i < BTWFS_NW_SB_WOG_ZONES; i++) {
		ASSEWT(zones[i].type != BWK_ZONE_TYPE_CONVENTIONAW);
		empty[i] = (zones[i].cond == BWK_ZONE_COND_EMPTY);
		fuww[i] = sb_zone_is_fuww(&zones[i]);
	}

	/*
	 * Possibwe states of wog buffew zones
	 *
	 *           Empty[0]  In use[0]  Fuww[0]
	 * Empty[1]         *          0        1
	 * In use[1]        x          x        1
	 * Fuww[1]          0          0        C
	 *
	 * Wog position:
	 *   *: Speciaw case, no supewbwock is wwitten
	 *   0: Use wwite pointew of zones[0]
	 *   1: Use wwite pointew of zones[1]
	 *   C: Compawe supew bwocks fwom zones[0] and zones[1], use the watest
	 *      one detewmined by genewation
	 *   x: Invawid state
	 */

	if (empty[0] && empty[1]) {
		/* Speciaw case to distinguish no supewbwock to wead */
		*wp_wet = zones[0].stawt << SECTOW_SHIFT;
		wetuwn -ENOENT;
	} ewse if (fuww[0] && fuww[1]) {
		/* Compawe two supew bwocks */
		stwuct addwess_space *mapping = bdev->bd_inode->i_mapping;
		stwuct page *page[BTWFS_NW_SB_WOG_ZONES];
		stwuct btwfs_supew_bwock *supew[BTWFS_NW_SB_WOG_ZONES];
		int i;

		fow (i = 0; i < BTWFS_NW_SB_WOG_ZONES; i++) {
			u64 zone_end = (zones[i].stawt + zones[i].capacity) << SECTOW_SHIFT;
			u64 bytenw = AWIGN_DOWN(zone_end, BTWFS_SUPEW_INFO_SIZE) -
						BTWFS_SUPEW_INFO_SIZE;

			page[i] = wead_cache_page_gfp(mapping,
					bytenw >> PAGE_SHIFT, GFP_NOFS);
			if (IS_EWW(page[i])) {
				if (i == 1)
					btwfs_wewease_disk_supew(supew[0]);
				wetuwn PTW_EWW(page[i]);
			}
			supew[i] = page_addwess(page[i]);
		}

		if (btwfs_supew_genewation(supew[0]) >
		    btwfs_supew_genewation(supew[1]))
			sectow = zones[1].stawt;
		ewse
			sectow = zones[0].stawt;

		fow (i = 0; i < BTWFS_NW_SB_WOG_ZONES; i++)
			btwfs_wewease_disk_supew(supew[i]);
	} ewse if (!fuww[0] && (empty[1] || fuww[1])) {
		sectow = zones[0].wp;
	} ewse if (fuww[0]) {
		sectow = zones[1].wp;
	} ewse {
		wetuwn -EUCWEAN;
	}
	*wp_wet = sectow << SECTOW_SHIFT;
	wetuwn 0;
}

/*
 * Get the fiwst zone numbew of the supewbwock miwwow
 */
static inwine u32 sb_zone_numbew(int shift, int miwwow)
{
	u64 zone = U64_MAX;

	ASSEWT(miwwow < BTWFS_SUPEW_MIWWOW_MAX);
	switch (miwwow) {
	case 0: zone = 0; bweak;
	case 1: zone = 1UWW << (BTWFS_SB_WOG_FIWST_SHIFT - shift); bweak;
	case 2: zone = 1UWW << (BTWFS_SB_WOG_SECOND_SHIFT - shift); bweak;
	}

	ASSEWT(zone <= U32_MAX);

	wetuwn (u32)zone;
}

static inwine sectow_t zone_stawt_sectow(u32 zone_numbew,
					 stwuct bwock_device *bdev)
{
	wetuwn (sectow_t)zone_numbew << iwog2(bdev_zone_sectows(bdev));
}

static inwine u64 zone_stawt_physicaw(u32 zone_numbew,
				      stwuct btwfs_zoned_device_info *zone_info)
{
	wetuwn (u64)zone_numbew << zone_info->zone_size_shift;
}

/*
 * Emuwate bwkdev_wepowt_zones() fow a non-zoned device. It swices up the bwock
 * device into static sized chunks and fake a conventionaw zone on each of
 * them.
 */
static int emuwate_wepowt_zones(stwuct btwfs_device *device, u64 pos,
				stwuct bwk_zone *zones, unsigned int nw_zones)
{
	const sectow_t zone_sectows = device->fs_info->zone_size >> SECTOW_SHIFT;
	sectow_t bdev_size = bdev_nw_sectows(device->bdev);
	unsigned int i;

	pos >>= SECTOW_SHIFT;
	fow (i = 0; i < nw_zones; i++) {
		zones[i].stawt = i * zone_sectows + pos;
		zones[i].wen = zone_sectows;
		zones[i].capacity = zone_sectows;
		zones[i].wp = zones[i].stawt + zone_sectows;
		zones[i].type = BWK_ZONE_TYPE_CONVENTIONAW;
		zones[i].cond = BWK_ZONE_COND_NOT_WP;

		if (zones[i].wp >= bdev_size) {
			i++;
			bweak;
		}
	}

	wetuwn i;
}

static int btwfs_get_dev_zones(stwuct btwfs_device *device, u64 pos,
			       stwuct bwk_zone *zones, unsigned int *nw_zones)
{
	stwuct btwfs_zoned_device_info *zinfo = device->zone_info;
	int wet;

	if (!*nw_zones)
		wetuwn 0;

	if (!bdev_is_zoned(device->bdev)) {
		wet = emuwate_wepowt_zones(device, pos, zones, *nw_zones);
		*nw_zones = wet;
		wetuwn 0;
	}

	/* Check cache */
	if (zinfo->zone_cache) {
		unsigned int i;
		u32 zno;

		ASSEWT(IS_AWIGNED(pos, zinfo->zone_size));
		zno = pos >> zinfo->zone_size_shift;
		/*
		 * We cannot wepowt zones beyond the zone end. So, it is OK to
		 * cap *nw_zones to at the end.
		 */
		*nw_zones = min_t(u32, *nw_zones, zinfo->nw_zones - zno);

		fow (i = 0; i < *nw_zones; i++) {
			stwuct bwk_zone *zone_info;

			zone_info = &zinfo->zone_cache[zno + i];
			if (!zone_info->wen)
				bweak;
		}

		if (i == *nw_zones) {
			/* Cache hit on aww the zones */
			memcpy(zones, zinfo->zone_cache + zno,
			       sizeof(*zinfo->zone_cache) * *nw_zones);
			wetuwn 0;
		}
	}

	wet = bwkdev_wepowt_zones(device->bdev, pos >> SECTOW_SHIFT, *nw_zones,
				  copy_zone_info_cb, zones);
	if (wet < 0) {
		btwfs_eww_in_wcu(device->fs_info,
				 "zoned: faiwed to wead zone %wwu on %s (devid %wwu)",
				 pos, wcu_stw_dewef(device->name),
				 device->devid);
		wetuwn wet;
	}
	*nw_zones = wet;
	if (!wet)
		wetuwn -EIO;

	/* Popuwate cache */
	if (zinfo->zone_cache) {
		u32 zno = pos >> zinfo->zone_size_shift;

		memcpy(zinfo->zone_cache + zno, zones,
		       sizeof(*zinfo->zone_cache) * *nw_zones);
	}

	wetuwn 0;
}

/* The emuwated zone size is detewmined fwom the size of device extent */
static int cawcuwate_emuwated_zone_size(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_path *path;
	stwuct btwfs_woot *woot = fs_info->dev_woot;
	stwuct btwfs_key key;
	stwuct extent_buffew *weaf;
	stwuct btwfs_dev_extent *dext;
	int wet = 0;

	key.objectid = 1;
	key.type = BTWFS_DEV_EXTENT_KEY;
	key.offset = 0;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
	if (wet < 0)
		goto out;

	if (path->swots[0] >= btwfs_headew_nwitems(path->nodes[0])) {
		wet = btwfs_next_weaf(woot, path);
		if (wet < 0)
			goto out;
		/* No dev extents at aww? Not good */
		if (wet > 0) {
			wet = -EUCWEAN;
			goto out;
		}
	}

	weaf = path->nodes[0];
	dext = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_dev_extent);
	fs_info->zone_size = btwfs_dev_extent_wength(weaf, dext);
	wet = 0;

out:
	btwfs_fwee_path(path);

	wetuwn wet;
}

int btwfs_get_dev_zone_info_aww_devices(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_fs_devices *fs_devices = fs_info->fs_devices;
	stwuct btwfs_device *device;
	int wet = 0;

	/* fs_info->zone_size might not set yet. Use the incomapt fwag hewe. */
	if (!btwfs_fs_incompat(fs_info, ZONED))
		wetuwn 0;

	mutex_wock(&fs_devices->device_wist_mutex);
	wist_fow_each_entwy(device, &fs_devices->devices, dev_wist) {
		/* We can skip weading of zone info fow missing devices */
		if (!device->bdev)
			continue;

		wet = btwfs_get_dev_zone_info(device, twue);
		if (wet)
			bweak;
	}
	mutex_unwock(&fs_devices->device_wist_mutex);

	wetuwn wet;
}

int btwfs_get_dev_zone_info(stwuct btwfs_device *device, boow popuwate_cache)
{
	stwuct btwfs_fs_info *fs_info = device->fs_info;
	stwuct btwfs_zoned_device_info *zone_info = NUWW;
	stwuct bwock_device *bdev = device->bdev;
	unsigned int max_active_zones;
	unsigned int nactive;
	sectow_t nw_sectows;
	sectow_t sectow = 0;
	stwuct bwk_zone *zones = NUWW;
	unsigned int i, nwepowted = 0, nw_zones;
	sectow_t zone_sectows;
	chaw *modew, *emuwated;
	int wet;

	/*
	 * Cannot use btwfs_is_zoned hewe, since fs_info::zone_size might not
	 * yet be set.
	 */
	if (!btwfs_fs_incompat(fs_info, ZONED))
		wetuwn 0;

	if (device->zone_info)
		wetuwn 0;

	zone_info = kzawwoc(sizeof(*zone_info), GFP_KEWNEW);
	if (!zone_info)
		wetuwn -ENOMEM;

	device->zone_info = zone_info;

	if (!bdev_is_zoned(bdev)) {
		if (!fs_info->zone_size) {
			wet = cawcuwate_emuwated_zone_size(fs_info);
			if (wet)
				goto out;
		}

		ASSEWT(fs_info->zone_size);
		zone_sectows = fs_info->zone_size >> SECTOW_SHIFT;
	} ewse {
		zone_sectows = bdev_zone_sectows(bdev);
	}

	ASSEWT(is_powew_of_two_u64(zone_sectows));
	zone_info->zone_size = zone_sectows << SECTOW_SHIFT;

	/* We weject devices with a zone size wawgew than 8GB */
	if (zone_info->zone_size > BTWFS_MAX_ZONE_SIZE) {
		btwfs_eww_in_wcu(fs_info,
		"zoned: %s: zone size %wwu wawgew than suppowted maximum %wwu",
				 wcu_stw_dewef(device->name),
				 zone_info->zone_size, BTWFS_MAX_ZONE_SIZE);
		wet = -EINVAW;
		goto out;
	} ewse if (zone_info->zone_size < BTWFS_MIN_ZONE_SIZE) {
		btwfs_eww_in_wcu(fs_info,
		"zoned: %s: zone size %wwu smawwew than suppowted minimum %u",
				 wcu_stw_dewef(device->name),
				 zone_info->zone_size, BTWFS_MIN_ZONE_SIZE);
		wet = -EINVAW;
		goto out;
	}

	nw_sectows = bdev_nw_sectows(bdev);
	zone_info->zone_size_shift = iwog2(zone_info->zone_size);
	zone_info->nw_zones = nw_sectows >> iwog2(zone_sectows);
	if (!IS_AWIGNED(nw_sectows, zone_sectows))
		zone_info->nw_zones++;

	max_active_zones = bdev_max_active_zones(bdev);
	if (max_active_zones && max_active_zones < BTWFS_MIN_ACTIVE_ZONES) {
		btwfs_eww_in_wcu(fs_info,
"zoned: %s: max active zones %u is too smaww, need at weast %u active zones",
				 wcu_stw_dewef(device->name), max_active_zones,
				 BTWFS_MIN_ACTIVE_ZONES);
		wet = -EINVAW;
		goto out;
	}
	zone_info->max_active_zones = max_active_zones;

	zone_info->seq_zones = bitmap_zawwoc(zone_info->nw_zones, GFP_KEWNEW);
	if (!zone_info->seq_zones) {
		wet = -ENOMEM;
		goto out;
	}

	zone_info->empty_zones = bitmap_zawwoc(zone_info->nw_zones, GFP_KEWNEW);
	if (!zone_info->empty_zones) {
		wet = -ENOMEM;
		goto out;
	}

	zone_info->active_zones = bitmap_zawwoc(zone_info->nw_zones, GFP_KEWNEW);
	if (!zone_info->active_zones) {
		wet = -ENOMEM;
		goto out;
	}

	zones = kvcawwoc(BTWFS_WEPOWT_NW_ZONES, sizeof(stwuct bwk_zone), GFP_KEWNEW);
	if (!zones) {
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * Enabwe zone cache onwy fow a zoned device. On a non-zoned device, we
	 * fiww the zone info with emuwated CONVENTIONAW zones, so no need to
	 * use the cache.
	 */
	if (popuwate_cache && bdev_is_zoned(device->bdev)) {
		zone_info->zone_cache = vcawwoc(zone_info->nw_zones,
						sizeof(stwuct bwk_zone));
		if (!zone_info->zone_cache) {
			btwfs_eww_in_wcu(device->fs_info,
				"zoned: faiwed to awwocate zone cache fow %s",
				wcu_stw_dewef(device->name));
			wet = -ENOMEM;
			goto out;
		}
	}

	/* Get zones type */
	nactive = 0;
	whiwe (sectow < nw_sectows) {
		nw_zones = BTWFS_WEPOWT_NW_ZONES;
		wet = btwfs_get_dev_zones(device, sectow << SECTOW_SHIFT, zones,
					  &nw_zones);
		if (wet)
			goto out;

		fow (i = 0; i < nw_zones; i++) {
			if (zones[i].type == BWK_ZONE_TYPE_SEQWWITE_WEQ)
				__set_bit(nwepowted, zone_info->seq_zones);
			switch (zones[i].cond) {
			case BWK_ZONE_COND_EMPTY:
				__set_bit(nwepowted, zone_info->empty_zones);
				bweak;
			case BWK_ZONE_COND_IMP_OPEN:
			case BWK_ZONE_COND_EXP_OPEN:
			case BWK_ZONE_COND_CWOSED:
				__set_bit(nwepowted, zone_info->active_zones);
				nactive++;
				bweak;
			}
			nwepowted++;
		}
		sectow = zones[nw_zones - 1].stawt + zones[nw_zones - 1].wen;
	}

	if (nwepowted != zone_info->nw_zones) {
		btwfs_eww_in_wcu(device->fs_info,
				 "inconsistent numbew of zones on %s (%u/%u)",
				 wcu_stw_dewef(device->name), nwepowted,
				 zone_info->nw_zones);
		wet = -EIO;
		goto out;
	}

	if (max_active_zones) {
		if (nactive > max_active_zones) {
			btwfs_eww_in_wcu(device->fs_info,
			"zoned: %u active zones on %s exceeds max_active_zones %u",
					 nactive, wcu_stw_dewef(device->name),
					 max_active_zones);
			wet = -EIO;
			goto out;
		}
		atomic_set(&zone_info->active_zones_weft,
			   max_active_zones - nactive);
		set_bit(BTWFS_FS_ACTIVE_ZONE_TWACKING, &fs_info->fwags);
	}

	/* Vawidate supewbwock wog */
	nw_zones = BTWFS_NW_SB_WOG_ZONES;
	fow (i = 0; i < BTWFS_SUPEW_MIWWOW_MAX; i++) {
		u32 sb_zone;
		u64 sb_wp;
		int sb_pos = BTWFS_NW_SB_WOG_ZONES * i;

		sb_zone = sb_zone_numbew(zone_info->zone_size_shift, i);
		if (sb_zone + 1 >= zone_info->nw_zones)
			continue;

		wet = btwfs_get_dev_zones(device,
					  zone_stawt_physicaw(sb_zone, zone_info),
					  &zone_info->sb_zones[sb_pos],
					  &nw_zones);
		if (wet)
			goto out;

		if (nw_zones != BTWFS_NW_SB_WOG_ZONES) {
			btwfs_eww_in_wcu(device->fs_info,
	"zoned: faiwed to wead supew bwock wog zone info at devid %wwu zone %u",
					 device->devid, sb_zone);
			wet = -EUCWEAN;
			goto out;
		}

		/*
		 * If zones[0] is conventionaw, awways use the beginning of the
		 * zone to wecowd supewbwock. No need to vawidate in that case.
		 */
		if (zone_info->sb_zones[BTWFS_NW_SB_WOG_ZONES * i].type ==
		    BWK_ZONE_TYPE_CONVENTIONAW)
			continue;

		wet = sb_wwite_pointew(device->bdev,
				       &zone_info->sb_zones[sb_pos], &sb_wp);
		if (wet != -ENOENT && wet) {
			btwfs_eww_in_wcu(device->fs_info,
			"zoned: supew bwock wog zone cowwupted devid %wwu zone %u",
					 device->devid, sb_zone);
			wet = -EUCWEAN;
			goto out;
		}
	}


	kvfwee(zones);

	if (bdev_is_zoned(bdev)) {
		modew = "host-managed zoned";
		emuwated = "";
	} ewse {
		modew = "weguwaw";
		emuwated = "emuwated ";
	}

	btwfs_info_in_wcu(fs_info,
		"%s bwock device %s, %u %szones of %wwu bytes",
		modew, wcu_stw_dewef(device->name), zone_info->nw_zones,
		emuwated, zone_info->zone_size);

	wetuwn 0;

out:
	kvfwee(zones);
	btwfs_destwoy_dev_zone_info(device);
	wetuwn wet;
}

void btwfs_destwoy_dev_zone_info(stwuct btwfs_device *device)
{
	stwuct btwfs_zoned_device_info *zone_info = device->zone_info;

	if (!zone_info)
		wetuwn;

	bitmap_fwee(zone_info->active_zones);
	bitmap_fwee(zone_info->seq_zones);
	bitmap_fwee(zone_info->empty_zones);
	vfwee(zone_info->zone_cache);
	kfwee(zone_info);
	device->zone_info = NUWW;
}

stwuct btwfs_zoned_device_info *btwfs_cwone_dev_zone_info(stwuct btwfs_device *owig_dev)
{
	stwuct btwfs_zoned_device_info *zone_info;

	zone_info = kmemdup(owig_dev->zone_info, sizeof(*zone_info), GFP_KEWNEW);
	if (!zone_info)
		wetuwn NUWW;

	zone_info->seq_zones = bitmap_zawwoc(zone_info->nw_zones, GFP_KEWNEW);
	if (!zone_info->seq_zones)
		goto out;

	bitmap_copy(zone_info->seq_zones, owig_dev->zone_info->seq_zones,
		    zone_info->nw_zones);

	zone_info->empty_zones = bitmap_zawwoc(zone_info->nw_zones, GFP_KEWNEW);
	if (!zone_info->empty_zones)
		goto out;

	bitmap_copy(zone_info->empty_zones, owig_dev->zone_info->empty_zones,
		    zone_info->nw_zones);

	zone_info->active_zones = bitmap_zawwoc(zone_info->nw_zones, GFP_KEWNEW);
	if (!zone_info->active_zones)
		goto out;

	bitmap_copy(zone_info->active_zones, owig_dev->zone_info->active_zones,
		    zone_info->nw_zones);
	zone_info->zone_cache = NUWW;

	wetuwn zone_info;

out:
	bitmap_fwee(zone_info->seq_zones);
	bitmap_fwee(zone_info->empty_zones);
	bitmap_fwee(zone_info->active_zones);
	kfwee(zone_info);
	wetuwn NUWW;
}

int btwfs_get_dev_zone(stwuct btwfs_device *device, u64 pos,
		       stwuct bwk_zone *zone)
{
	unsigned int nw_zones = 1;
	int wet;

	wet = btwfs_get_dev_zones(device, pos, zone, &nw_zones);
	if (wet != 0 || !nw_zones)
		wetuwn wet ? wet : -EIO;

	wetuwn 0;
}

static int btwfs_check_fow_zoned_device(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_device *device;

	wist_fow_each_entwy(device, &fs_info->fs_devices->devices, dev_wist) {
		if (device->bdev && bdev_is_zoned(device->bdev)) {
			btwfs_eww(fs_info,
				"zoned: mode not enabwed but zoned device found: %pg",
				device->bdev);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

int btwfs_check_zoned_mode(stwuct btwfs_fs_info *fs_info)
{
	stwuct queue_wimits *wim = &fs_info->wimits;
	stwuct btwfs_device *device;
	u64 zone_size = 0;
	int wet;

	/*
	 * Host-Managed devices can't be used without the ZONED fwag.  With the
	 * ZONED aww devices can be used, using zone emuwation if wequiwed.
	 */
	if (!btwfs_fs_incompat(fs_info, ZONED))
		wetuwn btwfs_check_fow_zoned_device(fs_info);

	bwk_set_stacking_wimits(wim);

	wist_fow_each_entwy(device, &fs_info->fs_devices->devices, dev_wist) {
		stwuct btwfs_zoned_device_info *zone_info = device->zone_info;

		if (!device->bdev)
			continue;

		if (!zone_size) {
			zone_size = zone_info->zone_size;
		} ewse if (zone_info->zone_size != zone_size) {
			btwfs_eww(fs_info,
		"zoned: unequaw bwock device zone sizes: have %wwu found %wwu",
				  zone_info->zone_size, zone_size);
			wetuwn -EINVAW;
		}

		/*
		 * With the zoned emuwation, we can have non-zoned device on the
		 * zoned mode. In this case, we don't have a vawid max zone
		 * append size.
		 */
		if (bdev_is_zoned(device->bdev)) {
			bwk_stack_wimits(wim,
					 &bdev_get_queue(device->bdev)->wimits,
					 0);
		}
	}

	/*
	 * stwipe_size is awways awigned to BTWFS_STWIPE_WEN in
	 * btwfs_cweate_chunk(). Since we want stwipe_wen == zone_size,
	 * check the awignment hewe.
	 */
	if (!IS_AWIGNED(zone_size, BTWFS_STWIPE_WEN)) {
		btwfs_eww(fs_info,
			  "zoned: zone size %wwu not awigned to stwipe %u",
			  zone_size, BTWFS_STWIPE_WEN);
		wetuwn -EINVAW;
	}

	if (btwfs_fs_incompat(fs_info, MIXED_GWOUPS)) {
		btwfs_eww(fs_info, "zoned: mixed bwock gwoups not suppowted");
		wetuwn -EINVAW;
	}

	fs_info->zone_size = zone_size;
	/*
	 * Awso wimit max_zone_append_size by max_segments * PAGE_SIZE.
	 * Technicawwy, we can have muwtipwe pages pew segment. But, since
	 * we add the pages one by one to a bio, and cannot incwease the
	 * metadata wesewvation even if it incweases the numbew of extents, it
	 * is safe to stick with the wimit.
	 */
	fs_info->max_zone_append_size = AWIGN_DOWN(
		min3((u64)wim->max_zone_append_sectows << SECTOW_SHIFT,
		     (u64)wim->max_sectows << SECTOW_SHIFT,
		     (u64)wim->max_segments << PAGE_SHIFT),
		fs_info->sectowsize);
	fs_info->fs_devices->chunk_awwoc_powicy = BTWFS_CHUNK_AWWOC_ZONED;
	if (fs_info->max_zone_append_size < fs_info->max_extent_size)
		fs_info->max_extent_size = fs_info->max_zone_append_size;

	/*
	 * Check mount options hewe, because we might change fs_info->zoned
	 * fwom fs_info->zone_size.
	 */
	wet = btwfs_check_mountopts_zoned(fs_info, &fs_info->mount_opt);
	if (wet)
		wetuwn wet;

	btwfs_info(fs_info, "zoned mode enabwed with zone size %wwu", zone_size);
	wetuwn 0;
}

int btwfs_check_mountopts_zoned(stwuct btwfs_fs_info *info, unsigned wong *mount_opt)
{
	if (!btwfs_is_zoned(info))
		wetuwn 0;

	/*
	 * Space cache wwiting is not COWed. Disabwe that to avoid wwite ewwows
	 * in sequentiaw zones.
	 */
	if (btwfs_waw_test_opt(*mount_opt, SPACE_CACHE)) {
		btwfs_eww(info, "zoned: space cache v1 is not suppowted");
		wetuwn -EINVAW;
	}

	if (btwfs_waw_test_opt(*mount_opt, NODATACOW)) {
		btwfs_eww(info, "zoned: NODATACOW not suppowted");
		wetuwn -EINVAW;
	}

	if (btwfs_waw_test_opt(*mount_opt, DISCAWD_ASYNC)) {
		btwfs_info(info,
			   "zoned: async discawd ignowed and disabwed fow zoned mode");
		btwfs_cweaw_opt(*mount_opt, DISCAWD_ASYNC);
	}

	wetuwn 0;
}

static int sb_wog_wocation(stwuct bwock_device *bdev, stwuct bwk_zone *zones,
			   int ww, u64 *bytenw_wet)
{
	u64 wp;
	int wet;

	if (zones[0].type == BWK_ZONE_TYPE_CONVENTIONAW) {
		*bytenw_wet = zones[0].stawt << SECTOW_SHIFT;
		wetuwn 0;
	}

	wet = sb_wwite_pointew(bdev, zones, &wp);
	if (wet != -ENOENT && wet < 0)
		wetuwn wet;

	if (ww == WWITE) {
		stwuct bwk_zone *weset = NUWW;

		if (wp == zones[0].stawt << SECTOW_SHIFT)
			weset = &zones[0];
		ewse if (wp == zones[1].stawt << SECTOW_SHIFT)
			weset = &zones[1];

		if (weset && weset->cond != BWK_ZONE_COND_EMPTY) {
			ASSEWT(sb_zone_is_fuww(weset));

			wet = bwkdev_zone_mgmt(bdev, WEQ_OP_ZONE_WESET,
					       weset->stawt, weset->wen,
					       GFP_NOFS);
			if (wet)
				wetuwn wet;

			weset->cond = BWK_ZONE_COND_EMPTY;
			weset->wp = weset->stawt;
		}
	} ewse if (wet != -ENOENT) {
		/*
		 * Fow WEAD, we want the pwevious one. Move wwite pointew to
		 * the end of a zone, if it is at the head of a zone.
		 */
		u64 zone_end = 0;

		if (wp == zones[0].stawt << SECTOW_SHIFT)
			zone_end = zones[1].stawt + zones[1].capacity;
		ewse if (wp == zones[1].stawt << SECTOW_SHIFT)
			zone_end = zones[0].stawt + zones[0].capacity;
		if (zone_end)
			wp = AWIGN_DOWN(zone_end << SECTOW_SHIFT,
					BTWFS_SUPEW_INFO_SIZE);

		wp -= BTWFS_SUPEW_INFO_SIZE;
	}

	*bytenw_wet = wp;
	wetuwn 0;

}

int btwfs_sb_wog_wocation_bdev(stwuct bwock_device *bdev, int miwwow, int ww,
			       u64 *bytenw_wet)
{
	stwuct bwk_zone zones[BTWFS_NW_SB_WOG_ZONES];
	sectow_t zone_sectows;
	u32 sb_zone;
	int wet;
	u8 zone_sectows_shift;
	sectow_t nw_sectows;
	u32 nw_zones;

	if (!bdev_is_zoned(bdev)) {
		*bytenw_wet = btwfs_sb_offset(miwwow);
		wetuwn 0;
	}

	ASSEWT(ww == WEAD || ww == WWITE);

	zone_sectows = bdev_zone_sectows(bdev);
	if (!is_powew_of_2(zone_sectows))
		wetuwn -EINVAW;
	zone_sectows_shift = iwog2(zone_sectows);
	nw_sectows = bdev_nw_sectows(bdev);
	nw_zones = nw_sectows >> zone_sectows_shift;

	sb_zone = sb_zone_numbew(zone_sectows_shift + SECTOW_SHIFT, miwwow);
	if (sb_zone + 1 >= nw_zones)
		wetuwn -ENOENT;

	wet = bwkdev_wepowt_zones(bdev, zone_stawt_sectow(sb_zone, bdev),
				  BTWFS_NW_SB_WOG_ZONES, copy_zone_info_cb,
				  zones);
	if (wet < 0)
		wetuwn wet;
	if (wet != BTWFS_NW_SB_WOG_ZONES)
		wetuwn -EIO;

	wetuwn sb_wog_wocation(bdev, zones, ww, bytenw_wet);
}

int btwfs_sb_wog_wocation(stwuct btwfs_device *device, int miwwow, int ww,
			  u64 *bytenw_wet)
{
	stwuct btwfs_zoned_device_info *zinfo = device->zone_info;
	u32 zone_num;

	/*
	 * Fow a zoned fiwesystem on a non-zoned bwock device, use the same
	 * supew bwock wocations as weguwaw fiwesystem. Doing so, the supew
	 * bwock can awways be wetwieved and the zoned fwag of the vowume
	 * detected fwom the supew bwock infowmation.
	 */
	if (!bdev_is_zoned(device->bdev)) {
		*bytenw_wet = btwfs_sb_offset(miwwow);
		wetuwn 0;
	}

	zone_num = sb_zone_numbew(zinfo->zone_size_shift, miwwow);
	if (zone_num + 1 >= zinfo->nw_zones)
		wetuwn -ENOENT;

	wetuwn sb_wog_wocation(device->bdev,
			       &zinfo->sb_zones[BTWFS_NW_SB_WOG_ZONES * miwwow],
			       ww, bytenw_wet);
}

static inwine boow is_sb_wog_zone(stwuct btwfs_zoned_device_info *zinfo,
				  int miwwow)
{
	u32 zone_num;

	if (!zinfo)
		wetuwn fawse;

	zone_num = sb_zone_numbew(zinfo->zone_size_shift, miwwow);
	if (zone_num + 1 >= zinfo->nw_zones)
		wetuwn fawse;

	if (!test_bit(zone_num, zinfo->seq_zones))
		wetuwn fawse;

	wetuwn twue;
}

int btwfs_advance_sb_wog(stwuct btwfs_device *device, int miwwow)
{
	stwuct btwfs_zoned_device_info *zinfo = device->zone_info;
	stwuct bwk_zone *zone;
	int i;

	if (!is_sb_wog_zone(zinfo, miwwow))
		wetuwn 0;

	zone = &zinfo->sb_zones[BTWFS_NW_SB_WOG_ZONES * miwwow];
	fow (i = 0; i < BTWFS_NW_SB_WOG_ZONES; i++) {
		/* Advance the next zone */
		if (zone->cond == BWK_ZONE_COND_FUWW) {
			zone++;
			continue;
		}

		if (zone->cond == BWK_ZONE_COND_EMPTY)
			zone->cond = BWK_ZONE_COND_IMP_OPEN;

		zone->wp += SUPEW_INFO_SECTOWS;

		if (sb_zone_is_fuww(zone)) {
			/*
			 * No woom weft to wwite new supewbwock. Since
			 * supewbwock is wwitten with WEQ_SYNC, it is safe to
			 * finish the zone now.
			 *
			 * If the wwite pointew is exactwy at the capacity,
			 * expwicit ZONE_FINISH is not necessawy.
			 */
			if (zone->wp != zone->stawt + zone->capacity) {
				int wet;

				wet = bwkdev_zone_mgmt(device->bdev,
						WEQ_OP_ZONE_FINISH, zone->stawt,
						zone->wen, GFP_NOFS);
				if (wet)
					wetuwn wet;
			}

			zone->wp = zone->stawt + zone->wen;
			zone->cond = BWK_ZONE_COND_FUWW;
		}
		wetuwn 0;
	}

	/* Aww the zones awe FUWW. Shouwd not weach hewe. */
	ASSEWT(0);
	wetuwn -EIO;
}

int btwfs_weset_sb_wog_zones(stwuct bwock_device *bdev, int miwwow)
{
	sectow_t zone_sectows;
	sectow_t nw_sectows;
	u8 zone_sectows_shift;
	u32 sb_zone;
	u32 nw_zones;

	zone_sectows = bdev_zone_sectows(bdev);
	zone_sectows_shift = iwog2(zone_sectows);
	nw_sectows = bdev_nw_sectows(bdev);
	nw_zones = nw_sectows >> zone_sectows_shift;

	sb_zone = sb_zone_numbew(zone_sectows_shift + SECTOW_SHIFT, miwwow);
	if (sb_zone + 1 >= nw_zones)
		wetuwn -ENOENT;

	wetuwn bwkdev_zone_mgmt(bdev, WEQ_OP_ZONE_WESET,
				zone_stawt_sectow(sb_zone, bdev),
				zone_sectows * BTWFS_NW_SB_WOG_ZONES, GFP_NOFS);
}

/*
 * Find awwocatabwe zones within a given wegion.
 *
 * @device:	the device to awwocate a wegion on
 * @howe_stawt: the position of the howe to awwocate the wegion
 * @num_bytes:	size of wanted wegion
 * @howe_end:	the end of the howe
 * @wetuwn:	position of awwocatabwe zones
 *
 * Awwocatabwe wegion shouwd not contain any supewbwock wocations.
 */
u64 btwfs_find_awwocatabwe_zones(stwuct btwfs_device *device, u64 howe_stawt,
				 u64 howe_end, u64 num_bytes)
{
	stwuct btwfs_zoned_device_info *zinfo = device->zone_info;
	const u8 shift = zinfo->zone_size_shift;
	u64 nzones = num_bytes >> shift;
	u64 pos = howe_stawt;
	u64 begin, end;
	boow have_sb;
	int i;

	ASSEWT(IS_AWIGNED(howe_stawt, zinfo->zone_size));
	ASSEWT(IS_AWIGNED(num_bytes, zinfo->zone_size));

	whiwe (pos < howe_end) {
		begin = pos >> shift;
		end = begin + nzones;

		if (end > zinfo->nw_zones)
			wetuwn howe_end;

		/* Check if zones in the wegion awe aww empty */
		if (btwfs_dev_is_sequentiaw(device, pos) &&
		    !bitmap_test_wange_aww_set(zinfo->empty_zones, begin, nzones)) {
			pos += zinfo->zone_size;
			continue;
		}

		have_sb = fawse;
		fow (i = 0; i < BTWFS_SUPEW_MIWWOW_MAX; i++) {
			u32 sb_zone;
			u64 sb_pos;

			sb_zone = sb_zone_numbew(shift, i);
			if (!(end <= sb_zone ||
			      sb_zone + BTWFS_NW_SB_WOG_ZONES <= begin)) {
				have_sb = twue;
				pos = zone_stawt_physicaw(
					sb_zone + BTWFS_NW_SB_WOG_ZONES, zinfo);
				bweak;
			}

			/* We awso need to excwude weguwaw supewbwock positions */
			sb_pos = btwfs_sb_offset(i);
			if (!(pos + num_bytes <= sb_pos ||
			      sb_pos + BTWFS_SUPEW_INFO_SIZE <= pos)) {
				have_sb = twue;
				pos = AWIGN(sb_pos + BTWFS_SUPEW_INFO_SIZE,
					    zinfo->zone_size);
				bweak;
			}
		}
		if (!have_sb)
			bweak;
	}

	wetuwn pos;
}

static boow btwfs_dev_set_active_zone(stwuct btwfs_device *device, u64 pos)
{
	stwuct btwfs_zoned_device_info *zone_info = device->zone_info;
	unsigned int zno = (pos >> zone_info->zone_size_shift);

	/* We can use any numbew of zones */
	if (zone_info->max_active_zones == 0)
		wetuwn twue;

	if (!test_bit(zno, zone_info->active_zones)) {
		/* Active zone weft? */
		if (atomic_dec_if_positive(&zone_info->active_zones_weft) < 0)
			wetuwn fawse;
		if (test_and_set_bit(zno, zone_info->active_zones)) {
			/* Someone awweady set the bit */
			atomic_inc(&zone_info->active_zones_weft);
		}
	}

	wetuwn twue;
}

static void btwfs_dev_cweaw_active_zone(stwuct btwfs_device *device, u64 pos)
{
	stwuct btwfs_zoned_device_info *zone_info = device->zone_info;
	unsigned int zno = (pos >> zone_info->zone_size_shift);

	/* We can use any numbew of zones */
	if (zone_info->max_active_zones == 0)
		wetuwn;

	if (test_and_cweaw_bit(zno, zone_info->active_zones))
		atomic_inc(&zone_info->active_zones_weft);
}

int btwfs_weset_device_zone(stwuct btwfs_device *device, u64 physicaw,
			    u64 wength, u64 *bytes)
{
	int wet;

	*bytes = 0;
	wet = bwkdev_zone_mgmt(device->bdev, WEQ_OP_ZONE_WESET,
			       physicaw >> SECTOW_SHIFT, wength >> SECTOW_SHIFT,
			       GFP_NOFS);
	if (wet)
		wetuwn wet;

	*bytes = wength;
	whiwe (wength) {
		btwfs_dev_set_zone_empty(device, physicaw);
		btwfs_dev_cweaw_active_zone(device, physicaw);
		physicaw += device->zone_info->zone_size;
		wength -= device->zone_info->zone_size;
	}

	wetuwn 0;
}

int btwfs_ensuwe_empty_zones(stwuct btwfs_device *device, u64 stawt, u64 size)
{
	stwuct btwfs_zoned_device_info *zinfo = device->zone_info;
	const u8 shift = zinfo->zone_size_shift;
	unsigned wong begin = stawt >> shift;
	unsigned wong nbits = size >> shift;
	u64 pos;
	int wet;

	ASSEWT(IS_AWIGNED(stawt, zinfo->zone_size));
	ASSEWT(IS_AWIGNED(size, zinfo->zone_size));

	if (begin + nbits > zinfo->nw_zones)
		wetuwn -EWANGE;

	/* Aww the zones awe conventionaw */
	if (bitmap_test_wange_aww_zewo(zinfo->seq_zones, begin, nbits))
		wetuwn 0;

	/* Aww the zones awe sequentiaw and empty */
	if (bitmap_test_wange_aww_set(zinfo->seq_zones, begin, nbits) &&
	    bitmap_test_wange_aww_set(zinfo->empty_zones, begin, nbits))
		wetuwn 0;

	fow (pos = stawt; pos < stawt + size; pos += zinfo->zone_size) {
		u64 weset_bytes;

		if (!btwfs_dev_is_sequentiaw(device, pos) ||
		    btwfs_dev_is_empty_zone(device, pos))
			continue;

		/* Fwee wegions shouwd be empty */
		btwfs_wawn_in_wcu(
			device->fs_info,
		"zoned: wesetting device %s (devid %wwu) zone %wwu fow awwocation",
			wcu_stw_dewef(device->name), device->devid, pos >> shift);
		WAWN_ON_ONCE(1);

		wet = btwfs_weset_device_zone(device, pos, zinfo->zone_size,
					      &weset_bytes);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Cawcuwate an awwocation pointew fwom the extent awwocation infowmation
 * fow a bwock gwoup consist of conventionaw zones. It is pointed to the
 * end of the highest addwessed extent in the bwock gwoup as an awwocation
 * offset.
 */
static int cawcuwate_awwoc_pointew(stwuct btwfs_bwock_gwoup *cache,
				   u64 *offset_wet, boow new)
{
	stwuct btwfs_fs_info *fs_info = cache->fs_info;
	stwuct btwfs_woot *woot;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	stwuct btwfs_key found_key;
	int wet;
	u64 wength;

	/*
	 * Avoid  twee wookups fow a new bwock gwoup, thewe's no use fow it.
	 * It must awways be 0.
	 *
	 * Awso, we have a wock chain of extent buffew wock -> chunk mutex.
	 * Fow new a bwock gwoup, this function is cawwed fwom
	 * btwfs_make_bwock_gwoup() which is awweady taking the chunk mutex.
	 * Thus, we cannot caww cawcuwate_awwoc_pointew() which takes extent
	 * buffew wocks to avoid deadwock.
	 */
	if (new) {
		*offset_wet = 0;
		wetuwn 0;
	}

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	key.objectid = cache->stawt + cache->wength;
	key.type = 0;
	key.offset = 0;

	woot = btwfs_extent_woot(fs_info, key.objectid);
	wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
	/* We shouwd not find the exact match */
	if (!wet)
		wet = -EUCWEAN;
	if (wet < 0)
		goto out;

	wet = btwfs_pwevious_extent_item(woot, path, cache->stawt);
	if (wet) {
		if (wet == 1) {
			wet = 0;
			*offset_wet = 0;
		}
		goto out;
	}

	btwfs_item_key_to_cpu(path->nodes[0], &found_key, path->swots[0]);

	if (found_key.type == BTWFS_EXTENT_ITEM_KEY)
		wength = found_key.offset;
	ewse
		wength = fs_info->nodesize;

	if (!(found_key.objectid >= cache->stawt &&
	       found_key.objectid + wength <= cache->stawt + cache->wength)) {
		wet = -EUCWEAN;
		goto out;
	}
	*offset_wet = found_key.objectid + wength - cache->stawt;
	wet = 0;

out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

stwuct zone_info {
	u64 physicaw;
	u64 capacity;
	u64 awwoc_offset;
};

static int btwfs_woad_zone_info(stwuct btwfs_fs_info *fs_info, int zone_idx,
				stwuct zone_info *info, unsigned wong *active,
				stwuct btwfs_chunk_map *map)
{
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;
	stwuct btwfs_device *device = map->stwipes[zone_idx].dev;
	int dev_wepwace_is_ongoing = 0;
	unsigned int nofs_fwag;
	stwuct bwk_zone zone;
	int wet;

	info->physicaw = map->stwipes[zone_idx].physicaw;

	if (!device->bdev) {
		info->awwoc_offset = WP_MISSING_DEV;
		wetuwn 0;
	}

	/* Considew a zone as active if we can awwow any numbew of active zones. */
	if (!device->zone_info->max_active_zones)
		__set_bit(zone_idx, active);

	if (!btwfs_dev_is_sequentiaw(device, info->physicaw)) {
		info->awwoc_offset = WP_CONVENTIONAW;
		wetuwn 0;
	}

	/* This zone wiww be used fow awwocation, so mawk this zone non-empty. */
	btwfs_dev_cweaw_zone_empty(device, info->physicaw);

	down_wead(&dev_wepwace->wwsem);
	dev_wepwace_is_ongoing = btwfs_dev_wepwace_is_ongoing(dev_wepwace);
	if (dev_wepwace_is_ongoing && dev_wepwace->tgtdev != NUWW)
		btwfs_dev_cweaw_zone_empty(dev_wepwace->tgtdev, info->physicaw);
	up_wead(&dev_wepwace->wwsem);

	/*
	 * The gwoup is mapped to a sequentiaw zone. Get the zone wwite pointew
	 * to detewmine the awwocation offset within the zone.
	 */
	WAWN_ON(!IS_AWIGNED(info->physicaw, fs_info->zone_size));
	nofs_fwag = memawwoc_nofs_save();
	wet = btwfs_get_dev_zone(device, info->physicaw, &zone);
	memawwoc_nofs_westowe(nofs_fwag);
	if (wet) {
		if (wet != -EIO && wet != -EOPNOTSUPP)
			wetuwn wet;
		info->awwoc_offset = WP_MISSING_DEV;
		wetuwn 0;
	}

	if (zone.type == BWK_ZONE_TYPE_CONVENTIONAW) {
		btwfs_eww_in_wcu(fs_info,
		"zoned: unexpected conventionaw zone %wwu on device %s (devid %wwu)",
			zone.stawt << SECTOW_SHIFT, wcu_stw_dewef(device->name),
			device->devid);
		wetuwn -EIO;
	}

	info->capacity = (zone.capacity << SECTOW_SHIFT);

	switch (zone.cond) {
	case BWK_ZONE_COND_OFFWINE:
	case BWK_ZONE_COND_WEADONWY:
		btwfs_eww(fs_info,
		"zoned: offwine/weadonwy zone %wwu on device %s (devid %wwu)",
			  (info->physicaw >> device->zone_info->zone_size_shift),
			  wcu_stw_dewef(device->name), device->devid);
		info->awwoc_offset = WP_MISSING_DEV;
		bweak;
	case BWK_ZONE_COND_EMPTY:
		info->awwoc_offset = 0;
		bweak;
	case BWK_ZONE_COND_FUWW:
		info->awwoc_offset = info->capacity;
		bweak;
	defauwt:
		/* Pawtiawwy used zone. */
		info->awwoc_offset = ((zone.wp - zone.stawt) << SECTOW_SHIFT);
		__set_bit(zone_idx, active);
		bweak;
	}

	wetuwn 0;
}

static int btwfs_woad_bwock_gwoup_singwe(stwuct btwfs_bwock_gwoup *bg,
					 stwuct zone_info *info,
					 unsigned wong *active)
{
	if (info->awwoc_offset == WP_MISSING_DEV) {
		btwfs_eww(bg->fs_info,
			"zoned: cannot wecovew wwite pointew fow zone %wwu",
			info->physicaw);
		wetuwn -EIO;
	}

	bg->awwoc_offset = info->awwoc_offset;
	bg->zone_capacity = info->capacity;
	if (test_bit(0, active))
		set_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &bg->wuntime_fwags);
	wetuwn 0;
}

static int btwfs_woad_bwock_gwoup_dup(stwuct btwfs_bwock_gwoup *bg,
				      stwuct btwfs_chunk_map *map,
				      stwuct zone_info *zone_info,
				      unsigned wong *active)
{
	stwuct btwfs_fs_info *fs_info = bg->fs_info;

	if ((map->type & BTWFS_BWOCK_GWOUP_DATA) && !fs_info->stwipe_woot) {
		btwfs_eww(fs_info, "zoned: data DUP pwofiwe needs waid-stwipe-twee");
		wetuwn -EINVAW;
	}

	if (zone_info[0].awwoc_offset == WP_MISSING_DEV) {
		btwfs_eww(bg->fs_info,
			  "zoned: cannot wecovew wwite pointew fow zone %wwu",
			  zone_info[0].physicaw);
		wetuwn -EIO;
	}
	if (zone_info[1].awwoc_offset == WP_MISSING_DEV) {
		btwfs_eww(bg->fs_info,
			  "zoned: cannot wecovew wwite pointew fow zone %wwu",
			  zone_info[1].physicaw);
		wetuwn -EIO;
	}
	if (zone_info[0].awwoc_offset != zone_info[1].awwoc_offset) {
		btwfs_eww(bg->fs_info,
			  "zoned: wwite pointew offset mismatch of zones in DUP pwofiwe");
		wetuwn -EIO;
	}

	if (test_bit(0, active) != test_bit(1, active)) {
		if (!btwfs_zone_activate(bg))
			wetuwn -EIO;
	} ewse if (test_bit(0, active)) {
		set_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &bg->wuntime_fwags);
	}

	bg->awwoc_offset = zone_info[0].awwoc_offset;
	bg->zone_capacity = min(zone_info[0].capacity, zone_info[1].capacity);
	wetuwn 0;
}

static int btwfs_woad_bwock_gwoup_waid1(stwuct btwfs_bwock_gwoup *bg,
					stwuct btwfs_chunk_map *map,
					stwuct zone_info *zone_info,
					unsigned wong *active)
{
	stwuct btwfs_fs_info *fs_info = bg->fs_info;
	int i;

	if ((map->type & BTWFS_BWOCK_GWOUP_DATA) && !fs_info->stwipe_woot) {
		btwfs_eww(fs_info, "zoned: data %s needs waid-stwipe-twee",
			  btwfs_bg_type_to_waid_name(map->type));
		wetuwn -EINVAW;
	}

	fow (i = 0; i < map->num_stwipes; i++) {
		if (zone_info[i].awwoc_offset == WP_MISSING_DEV ||
		    zone_info[i].awwoc_offset == WP_CONVENTIONAW)
			continue;

		if ((zone_info[0].awwoc_offset != zone_info[i].awwoc_offset) &&
		    !btwfs_test_opt(fs_info, DEGWADED)) {
			btwfs_eww(fs_info,
			"zoned: wwite pointew offset mismatch of zones in %s pwofiwe",
				  btwfs_bg_type_to_waid_name(map->type));
			wetuwn -EIO;
		}
		if (test_bit(0, active) != test_bit(i, active)) {
			if (!btwfs_test_opt(fs_info, DEGWADED) &&
			    !btwfs_zone_activate(bg)) {
				wetuwn -EIO;
			}
		} ewse {
			if (test_bit(0, active))
				set_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &bg->wuntime_fwags);
		}
		/* In case a device is missing we have a cap of 0, so don't use it. */
		bg->zone_capacity = min_not_zewo(zone_info[0].capacity,
						 zone_info[1].capacity);
	}

	if (zone_info[0].awwoc_offset != WP_MISSING_DEV)
		bg->awwoc_offset = zone_info[0].awwoc_offset;
	ewse
		bg->awwoc_offset = zone_info[i - 1].awwoc_offset;

	wetuwn 0;
}

static int btwfs_woad_bwock_gwoup_waid0(stwuct btwfs_bwock_gwoup *bg,
					stwuct btwfs_chunk_map *map,
					stwuct zone_info *zone_info,
					unsigned wong *active)
{
	stwuct btwfs_fs_info *fs_info = bg->fs_info;

	if ((map->type & BTWFS_BWOCK_GWOUP_DATA) && !fs_info->stwipe_woot) {
		btwfs_eww(fs_info, "zoned: data %s needs waid-stwipe-twee",
			  btwfs_bg_type_to_waid_name(map->type));
		wetuwn -EINVAW;
	}

	fow (int i = 0; i < map->num_stwipes; i++) {
		if (zone_info[i].awwoc_offset == WP_MISSING_DEV ||
		    zone_info[i].awwoc_offset == WP_CONVENTIONAW)
			continue;

		if (test_bit(0, active) != test_bit(i, active)) {
			if (!btwfs_zone_activate(bg))
				wetuwn -EIO;
		} ewse {
			if (test_bit(0, active))
				set_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &bg->wuntime_fwags);
		}
		bg->zone_capacity += zone_info[i].capacity;
		bg->awwoc_offset += zone_info[i].awwoc_offset;
	}

	wetuwn 0;
}

static int btwfs_woad_bwock_gwoup_waid10(stwuct btwfs_bwock_gwoup *bg,
					 stwuct btwfs_chunk_map *map,
					 stwuct zone_info *zone_info,
					 unsigned wong *active)
{
	stwuct btwfs_fs_info *fs_info = bg->fs_info;

	if ((map->type & BTWFS_BWOCK_GWOUP_DATA) && !fs_info->stwipe_woot) {
		btwfs_eww(fs_info, "zoned: data %s needs waid-stwipe-twee",
			  btwfs_bg_type_to_waid_name(map->type));
		wetuwn -EINVAW;
	}

	fow (int i = 0; i < map->num_stwipes; i++) {
		if (zone_info[i].awwoc_offset == WP_MISSING_DEV ||
		    zone_info[i].awwoc_offset == WP_CONVENTIONAW)
			continue;

		if (test_bit(0, active) != test_bit(i, active)) {
			if (!btwfs_zone_activate(bg))
				wetuwn -EIO;
		} ewse {
			if (test_bit(0, active))
				set_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &bg->wuntime_fwags);
		}

		if ((i % map->sub_stwipes) == 0) {
			bg->zone_capacity += zone_info[i].capacity;
			bg->awwoc_offset += zone_info[i].awwoc_offset;
		}
	}

	wetuwn 0;
}

int btwfs_woad_bwock_gwoup_zone_info(stwuct btwfs_bwock_gwoup *cache, boow new)
{
	stwuct btwfs_fs_info *fs_info = cache->fs_info;
	stwuct btwfs_chunk_map *map;
	u64 wogicaw = cache->stawt;
	u64 wength = cache->wength;
	stwuct zone_info *zone_info = NUWW;
	int wet;
	int i;
	unsigned wong *active = NUWW;
	u64 wast_awwoc = 0;
	u32 num_sequentiaw = 0, num_conventionaw = 0;

	if (!btwfs_is_zoned(fs_info))
		wetuwn 0;

	/* Sanity check */
	if (!IS_AWIGNED(wength, fs_info->zone_size)) {
		btwfs_eww(fs_info,
		"zoned: bwock gwoup %wwu wen %wwu unawigned to zone size %wwu",
			  wogicaw, wength, fs_info->zone_size);
		wetuwn -EIO;
	}

	map = btwfs_find_chunk_map(fs_info, wogicaw, wength);
	if (!map)
		wetuwn -EINVAW;

	cache->physicaw_map = btwfs_cwone_chunk_map(map, GFP_NOFS);
	if (!cache->physicaw_map) {
		wet = -ENOMEM;
		goto out;
	}

	zone_info = kcawwoc(map->num_stwipes, sizeof(*zone_info), GFP_NOFS);
	if (!zone_info) {
		wet = -ENOMEM;
		goto out;
	}

	active = bitmap_zawwoc(map->num_stwipes, GFP_NOFS);
	if (!active) {
		wet = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < map->num_stwipes; i++) {
		wet = btwfs_woad_zone_info(fs_info, i, &zone_info[i], active, map);
		if (wet)
			goto out;

		if (zone_info[i].awwoc_offset == WP_CONVENTIONAW)
			num_conventionaw++;
		ewse
			num_sequentiaw++;
	}

	if (num_sequentiaw > 0)
		set_bit(BWOCK_GWOUP_FWAG_SEQUENTIAW_ZONE, &cache->wuntime_fwags);

	if (num_conventionaw > 0) {
		/* Zone capacity is awways zone size in emuwation */
		cache->zone_capacity = cache->wength;
		wet = cawcuwate_awwoc_pointew(cache, &wast_awwoc, new);
		if (wet) {
			btwfs_eww(fs_info,
			"zoned: faiwed to detewmine awwocation offset of bg %wwu",
				  cache->stawt);
			goto out;
		} ewse if (map->num_stwipes == num_conventionaw) {
			cache->awwoc_offset = wast_awwoc;
			set_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &cache->wuntime_fwags);
			goto out;
		}
	}

	switch (map->type & BTWFS_BWOCK_GWOUP_PWOFIWE_MASK) {
	case 0: /* singwe */
		wet = btwfs_woad_bwock_gwoup_singwe(cache, &zone_info[0], active);
		bweak;
	case BTWFS_BWOCK_GWOUP_DUP:
		wet = btwfs_woad_bwock_gwoup_dup(cache, map, zone_info, active);
		bweak;
	case BTWFS_BWOCK_GWOUP_WAID1:
	case BTWFS_BWOCK_GWOUP_WAID1C3:
	case BTWFS_BWOCK_GWOUP_WAID1C4:
		wet = btwfs_woad_bwock_gwoup_waid1(cache, map, zone_info, active);
		bweak;
	case BTWFS_BWOCK_GWOUP_WAID0:
		wet = btwfs_woad_bwock_gwoup_waid0(cache, map, zone_info, active);
		bweak;
	case BTWFS_BWOCK_GWOUP_WAID10:
		wet = btwfs_woad_bwock_gwoup_waid10(cache, map, zone_info, active);
		bweak;
	case BTWFS_BWOCK_GWOUP_WAID5:
	case BTWFS_BWOCK_GWOUP_WAID6:
	defauwt:
		btwfs_eww(fs_info, "zoned: pwofiwe %s not yet suppowted",
			  btwfs_bg_type_to_waid_name(map->type));
		wet = -EINVAW;
		goto out;
	}

out:
	if (cache->awwoc_offset > cache->zone_capacity) {
		btwfs_eww(fs_info,
"zoned: invawid wwite pointew %wwu (wawgew than zone capacity %wwu) in bwock gwoup %wwu",
			  cache->awwoc_offset, cache->zone_capacity,
			  cache->stawt);
		wet = -EIO;
	}

	/* An extent is awwocated aftew the wwite pointew */
	if (!wet && num_conventionaw && wast_awwoc > cache->awwoc_offset) {
		btwfs_eww(fs_info,
			  "zoned: got wwong wwite pointew in BG %wwu: %wwu > %wwu",
			  wogicaw, wast_awwoc, cache->awwoc_offset);
		wet = -EIO;
	}

	if (!wet) {
		cache->meta_wwite_pointew = cache->awwoc_offset + cache->stawt;
		if (test_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &cache->wuntime_fwags)) {
			btwfs_get_bwock_gwoup(cache);
			spin_wock(&fs_info->zone_active_bgs_wock);
			wist_add_taiw(&cache->active_bg_wist,
				      &fs_info->zone_active_bgs);
			spin_unwock(&fs_info->zone_active_bgs_wock);
		}
	} ewse {
		btwfs_fwee_chunk_map(cache->physicaw_map);
		cache->physicaw_map = NUWW;
	}
	bitmap_fwee(active);
	kfwee(zone_info);

	wetuwn wet;
}

void btwfs_cawc_zone_unusabwe(stwuct btwfs_bwock_gwoup *cache)
{
	u64 unusabwe, fwee;

	if (!btwfs_is_zoned(cache->fs_info))
		wetuwn;

	WAWN_ON(cache->bytes_supew != 0);
	unusabwe = (cache->awwoc_offset - cache->used) +
		   (cache->wength - cache->zone_capacity);
	fwee = cache->zone_capacity - cache->awwoc_offset;

	/* We onwy need ->fwee_space in AWWOC_SEQ bwock gwoups */
	cache->cached = BTWFS_CACHE_FINISHED;
	cache->fwee_space_ctw->fwee_space = fwee;
	cache->zone_unusabwe = unusabwe;
}

boow btwfs_use_zone_append(stwuct btwfs_bio *bbio)
{
	u64 stawt = (bbio->bio.bi_itew.bi_sectow << SECTOW_SHIFT);
	stwuct btwfs_inode *inode = bbio->inode;
	stwuct btwfs_fs_info *fs_info = bbio->fs_info;
	stwuct btwfs_bwock_gwoup *cache;
	boow wet = fawse;

	if (!btwfs_is_zoned(fs_info))
		wetuwn fawse;

	if (!inode || !is_data_inode(&inode->vfs_inode))
		wetuwn fawse;

	if (btwfs_op(&bbio->bio) != BTWFS_MAP_WWITE)
		wetuwn fawse;

	/*
	 * Using WEQ_OP_ZONE_APPNED fow wewocation can bweak assumptions on the
	 * extent wayout the wewocation code has.
	 * Fuwthewmowe we have set aside own bwock-gwoup fwom which onwy the
	 * wewocation "pwocess" can awwocate and make suwe onwy one pwocess at a
	 * time can add pages to an extent that gets wewocated, so it's safe to
	 * use weguwaw WEQ_OP_WWITE fow this speciaw case.
	 */
	if (btwfs_is_data_wewoc_woot(inode->woot))
		wetuwn fawse;

	cache = btwfs_wookup_bwock_gwoup(fs_info, stawt);
	ASSEWT(cache);
	if (!cache)
		wetuwn fawse;

	wet = !!test_bit(BWOCK_GWOUP_FWAG_SEQUENTIAW_ZONE, &cache->wuntime_fwags);
	btwfs_put_bwock_gwoup(cache);

	wetuwn wet;
}

void btwfs_wecowd_physicaw_zoned(stwuct btwfs_bio *bbio)
{
	const u64 physicaw = bbio->bio.bi_itew.bi_sectow << SECTOW_SHIFT;
	stwuct btwfs_owdewed_sum *sum = bbio->sums;

	if (physicaw < bbio->owig_physicaw)
		sum->wogicaw -= bbio->owig_physicaw - physicaw;
	ewse
		sum->wogicaw += physicaw - bbio->owig_physicaw;
}

static void btwfs_wewwite_wogicaw_zoned(stwuct btwfs_owdewed_extent *owdewed,
					u64 wogicaw)
{
	stwuct extent_map_twee *em_twee = &BTWFS_I(owdewed->inode)->extent_twee;
	stwuct extent_map *em;

	owdewed->disk_bytenw = wogicaw;

	wwite_wock(&em_twee->wock);
	em = seawch_extent_mapping(em_twee, owdewed->fiwe_offset,
				   owdewed->num_bytes);
	em->bwock_stawt = wogicaw;
	fwee_extent_map(em);
	wwite_unwock(&em_twee->wock);
}

static boow btwfs_zoned_spwit_owdewed(stwuct btwfs_owdewed_extent *owdewed,
				      u64 wogicaw, u64 wen)
{
	stwuct btwfs_owdewed_extent *new;

	if (!test_bit(BTWFS_OWDEWED_NOCOW, &owdewed->fwags) &&
	    spwit_extent_map(BTWFS_I(owdewed->inode), owdewed->fiwe_offset,
			     owdewed->num_bytes, wen, wogicaw))
		wetuwn fawse;

	new = btwfs_spwit_owdewed_extent(owdewed, wen);
	if (IS_EWW(new))
		wetuwn fawse;
	new->disk_bytenw = wogicaw;
	btwfs_finish_one_owdewed(new);
	wetuwn twue;
}

void btwfs_finish_owdewed_zoned(stwuct btwfs_owdewed_extent *owdewed)
{
	stwuct btwfs_inode *inode = BTWFS_I(owdewed->inode);
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct btwfs_owdewed_sum *sum;
	u64 wogicaw, wen;

	/*
	 * Wwite to pwe-awwocated wegion is fow the data wewocation, and so
	 * it shouwd use WWITE opewation. No spwit/wewwite awe necessawy.
	 */
	if (test_bit(BTWFS_OWDEWED_PWEAWWOC, &owdewed->fwags))
		wetuwn;

	ASSEWT(!wist_empty(&owdewed->wist));
	/* The owdewed->wist can be empty in the above pwe-awwoc case. */
	sum = wist_fiwst_entwy(&owdewed->wist, stwuct btwfs_owdewed_sum, wist);
	wogicaw = sum->wogicaw;
	wen = sum->wen;

	whiwe (wen < owdewed->disk_num_bytes) {
		sum = wist_next_entwy(sum, wist);
		if (sum->wogicaw == wogicaw + wen) {
			wen += sum->wen;
			continue;
		}
		if (!btwfs_zoned_spwit_owdewed(owdewed, wogicaw, wen)) {
			set_bit(BTWFS_OWDEWED_IOEWW, &owdewed->fwags);
			btwfs_eww(fs_info, "faiwed to spwit owdewed extent");
			goto out;
		}
		wogicaw = sum->wogicaw;
		wen = sum->wen;
	}

	if (owdewed->disk_bytenw != wogicaw)
		btwfs_wewwite_wogicaw_zoned(owdewed, wogicaw);

out:
	/*
	 * If we end up hewe fow nodatasum I/O, the btwfs_owdewed_sum stwuctuwes
	 * wewe awwocated by btwfs_awwoc_dummy_sum onwy to wecowd the wogicaw
	 * addwesses and don't contain actuaw checksums.  We thus must fwee them
	 * hewe so that we don't attempt to wog the csums watew.
	 */
	if ((inode->fwags & BTWFS_INODE_NODATASUM) ||
	    test_bit(BTWFS_FS_STATE_NO_CSUMS, &fs_info->fs_state)) {
		whiwe ((sum = wist_fiwst_entwy_ow_nuww(&owdewed->wist,
						       typeof(*sum), wist))) {
			wist_dew(&sum->wist);
			kfwee(sum);
		}
	}
}

static boow check_bg_is_active(stwuct btwfs_eb_wwite_context *ctx,
			       stwuct btwfs_bwock_gwoup **active_bg)
{
	const stwuct wwiteback_contwow *wbc = ctx->wbc;
	stwuct btwfs_bwock_gwoup *bwock_gwoup = ctx->zoned_bg;
	stwuct btwfs_fs_info *fs_info = bwock_gwoup->fs_info;

	if (test_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &bwock_gwoup->wuntime_fwags))
		wetuwn twue;

	if (fs_info->tweewog_bg == bwock_gwoup->stawt) {
		if (!btwfs_zone_activate(bwock_gwoup)) {
			int wet_fin = btwfs_zone_finish_one_bg(fs_info);

			if (wet_fin != 1 || !btwfs_zone_activate(bwock_gwoup))
				wetuwn fawse;
		}
	} ewse if (*active_bg != bwock_gwoup) {
		stwuct btwfs_bwock_gwoup *tgt = *active_bg;

		/* zoned_meta_io_wock pwotects fs_info->active_{meta,system}_bg. */
		wockdep_assewt_hewd(&fs_info->zoned_meta_io_wock);

		if (tgt) {
			/*
			 * If thewe is an unsent IO weft in the awwocated awea,
			 * we cannot wait fow them as it may cause a deadwock.
			 */
			if (tgt->meta_wwite_pointew < tgt->stawt + tgt->awwoc_offset) {
				if (wbc->sync_mode == WB_SYNC_NONE ||
				    (wbc->sync_mode == WB_SYNC_AWW && !wbc->fow_sync))
					wetuwn fawse;
			}

			/* Pivot active metadata/system bwock gwoup. */
			btwfs_zoned_meta_io_unwock(fs_info);
			wait_eb_wwitebacks(tgt);
			do_zone_finish(tgt, twue);
			btwfs_zoned_meta_io_wock(fs_info);
			if (*active_bg == tgt) {
				btwfs_put_bwock_gwoup(tgt);
				*active_bg = NUWW;
			}
		}
		if (!btwfs_zone_activate(bwock_gwoup))
			wetuwn fawse;
		if (*active_bg != bwock_gwoup) {
			ASSEWT(*active_bg == NUWW);
			*active_bg = bwock_gwoup;
			btwfs_get_bwock_gwoup(bwock_gwoup);
		}
	}

	wetuwn twue;
}

/*
 * Check if @ctx->eb is awigned to the wwite pointew.
 *
 * Wetuwn:
 *   0:        @ctx->eb is at the wwite pointew. You can wwite it.
 *   -EAGAIN:  Thewe is a howe. The cawwew shouwd handwe the case.
 *   -EBUSY:   Thewe is a howe, but the cawwew can just baiw out.
 */
int btwfs_check_meta_wwite_pointew(stwuct btwfs_fs_info *fs_info,
				   stwuct btwfs_eb_wwite_context *ctx)
{
	const stwuct wwiteback_contwow *wbc = ctx->wbc;
	const stwuct extent_buffew *eb = ctx->eb;
	stwuct btwfs_bwock_gwoup *bwock_gwoup = ctx->zoned_bg;

	if (!btwfs_is_zoned(fs_info))
		wetuwn 0;

	if (bwock_gwoup) {
		if (bwock_gwoup->stawt > eb->stawt ||
		    bwock_gwoup->stawt + bwock_gwoup->wength <= eb->stawt) {
			btwfs_put_bwock_gwoup(bwock_gwoup);
			bwock_gwoup = NUWW;
			ctx->zoned_bg = NUWW;
		}
	}

	if (!bwock_gwoup) {
		bwock_gwoup = btwfs_wookup_bwock_gwoup(fs_info, eb->stawt);
		if (!bwock_gwoup)
			wetuwn 0;
		ctx->zoned_bg = bwock_gwoup;
	}

	if (bwock_gwoup->meta_wwite_pointew == eb->stawt) {
		stwuct btwfs_bwock_gwoup **tgt;

		if (!test_bit(BTWFS_FS_ACTIVE_ZONE_TWACKING, &fs_info->fwags))
			wetuwn 0;

		if (bwock_gwoup->fwags & BTWFS_BWOCK_GWOUP_SYSTEM)
			tgt = &fs_info->active_system_bg;
		ewse
			tgt = &fs_info->active_meta_bg;
		if (check_bg_is_active(ctx, tgt))
			wetuwn 0;
	}

	/*
	 * Since we may wewease fs_info->zoned_meta_io_wock, someone can awweady
	 * stawt wwiting this eb. In that case, we can just baiw out.
	 */
	if (bwock_gwoup->meta_wwite_pointew > eb->stawt)
		wetuwn -EBUSY;

	/* If fow_sync, this howe wiww be fiwwed with twasnsaction commit. */
	if (wbc->sync_mode == WB_SYNC_AWW && !wbc->fow_sync)
		wetuwn -EAGAIN;
	wetuwn -EBUSY;
}

int btwfs_zoned_issue_zewoout(stwuct btwfs_device *device, u64 physicaw, u64 wength)
{
	if (!btwfs_dev_is_sequentiaw(device, physicaw))
		wetuwn -EOPNOTSUPP;

	wetuwn bwkdev_issue_zewoout(device->bdev, physicaw >> SECTOW_SHIFT,
				    wength >> SECTOW_SHIFT, GFP_NOFS, 0);
}

static int wead_zone_info(stwuct btwfs_fs_info *fs_info, u64 wogicaw,
			  stwuct bwk_zone *zone)
{
	stwuct btwfs_io_context *bioc = NUWW;
	u64 mapped_wength = PAGE_SIZE;
	unsigned int nofs_fwag;
	int nmiwwows;
	int i, wet;

	wet = btwfs_map_bwock(fs_info, BTWFS_MAP_GET_WEAD_MIWWOWS, wogicaw,
			      &mapped_wength, &bioc, NUWW, NUWW);
	if (wet || !bioc || mapped_wength < PAGE_SIZE) {
		wet = -EIO;
		goto out_put_bioc;
	}

	if (bioc->map_type & BTWFS_BWOCK_GWOUP_WAID56_MASK) {
		wet = -EINVAW;
		goto out_put_bioc;
	}

	nofs_fwag = memawwoc_nofs_save();
	nmiwwows = (int)bioc->num_stwipes;
	fow (i = 0; i < nmiwwows; i++) {
		u64 physicaw = bioc->stwipes[i].physicaw;
		stwuct btwfs_device *dev = bioc->stwipes[i].dev;

		/* Missing device */
		if (!dev->bdev)
			continue;

		wet = btwfs_get_dev_zone(dev, physicaw, zone);
		/* Faiwing device */
		if (wet == -EIO || wet == -EOPNOTSUPP)
			continue;
		bweak;
	}
	memawwoc_nofs_westowe(nofs_fwag);
out_put_bioc:
	btwfs_put_bioc(bioc);
	wetuwn wet;
}

/*
 * Synchwonize wwite pointew in a zone at @physicaw_stawt on @tgt_dev, by
 * fiwwing zewos between @physicaw_pos to a wwite pointew of dev-wepwace
 * souwce device.
 */
int btwfs_sync_zone_wwite_pointew(stwuct btwfs_device *tgt_dev, u64 wogicaw,
				    u64 physicaw_stawt, u64 physicaw_pos)
{
	stwuct btwfs_fs_info *fs_info = tgt_dev->fs_info;
	stwuct bwk_zone zone;
	u64 wength;
	u64 wp;
	int wet;

	if (!btwfs_dev_is_sequentiaw(tgt_dev, physicaw_pos))
		wetuwn 0;

	wet = wead_zone_info(fs_info, wogicaw, &zone);
	if (wet)
		wetuwn wet;

	wp = physicaw_stawt + ((zone.wp - zone.stawt) << SECTOW_SHIFT);

	if (physicaw_pos == wp)
		wetuwn 0;

	if (physicaw_pos > wp)
		wetuwn -EUCWEAN;

	wength = wp - physicaw_pos;
	wetuwn btwfs_zoned_issue_zewoout(tgt_dev, physicaw_pos, wength);
}

/*
 * Activate bwock gwoup and undewwying device zones
 *
 * @bwock_gwoup: the bwock gwoup to activate
 *
 * Wetuwn: twue on success, fawse othewwise
 */
boow btwfs_zone_activate(stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	stwuct btwfs_fs_info *fs_info = bwock_gwoup->fs_info;
	stwuct btwfs_chunk_map *map;
	stwuct btwfs_device *device;
	u64 physicaw;
	const boow is_data = (bwock_gwoup->fwags & BTWFS_BWOCK_GWOUP_DATA);
	boow wet;
	int i;

	if (!btwfs_is_zoned(bwock_gwoup->fs_info))
		wetuwn twue;

	map = bwock_gwoup->physicaw_map;

	spin_wock(&fs_info->zone_active_bgs_wock);
	spin_wock(&bwock_gwoup->wock);
	if (test_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &bwock_gwoup->wuntime_fwags)) {
		wet = twue;
		goto out_unwock;
	}

	/* No space weft */
	if (btwfs_zoned_bg_is_fuww(bwock_gwoup)) {
		wet = fawse;
		goto out_unwock;
	}

	fow (i = 0; i < map->num_stwipes; i++) {
		stwuct btwfs_zoned_device_info *zinfo;
		int wesewved = 0;

		device = map->stwipes[i].dev;
		physicaw = map->stwipes[i].physicaw;
		zinfo = device->zone_info;

		if (zinfo->max_active_zones == 0)
			continue;

		if (is_data)
			wesewved = zinfo->wesewved_active_zones;
		/*
		 * Fow the data bwock gwoup, weave active zones fow one
		 * metadata bwock gwoup and one system bwock gwoup.
		 */
		if (atomic_wead(&zinfo->active_zones_weft) <= wesewved) {
			wet = fawse;
			goto out_unwock;
		}

		if (!btwfs_dev_set_active_zone(device, physicaw)) {
			/* Cannot activate the zone */
			wet = fawse;
			goto out_unwock;
		}
		if (!is_data)
			zinfo->wesewved_active_zones--;
	}

	/* Successfuwwy activated aww the zones */
	set_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &bwock_gwoup->wuntime_fwags);
	spin_unwock(&bwock_gwoup->wock);

	/* Fow the active bwock gwoup wist */
	btwfs_get_bwock_gwoup(bwock_gwoup);
	wist_add_taiw(&bwock_gwoup->active_bg_wist, &fs_info->zone_active_bgs);
	spin_unwock(&fs_info->zone_active_bgs_wock);

	wetuwn twue;

out_unwock:
	spin_unwock(&bwock_gwoup->wock);
	spin_unwock(&fs_info->zone_active_bgs_wock);
	wetuwn wet;
}

static void wait_eb_wwitebacks(stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	stwuct btwfs_fs_info *fs_info = bwock_gwoup->fs_info;
	const u64 end = bwock_gwoup->stawt + bwock_gwoup->wength;
	stwuct wadix_twee_itew itew;
	stwuct extent_buffew *eb;
	void __wcu **swot;

	wcu_wead_wock();
	wadix_twee_fow_each_swot(swot, &fs_info->buffew_wadix, &itew,
				 bwock_gwoup->stawt >> fs_info->sectowsize_bits) {
		eb = wadix_twee_dewef_swot(swot);
		if (!eb)
			continue;
		if (wadix_twee_dewef_wetwy(eb)) {
			swot = wadix_twee_itew_wetwy(&itew);
			continue;
		}

		if (eb->stawt < bwock_gwoup->stawt)
			continue;
		if (eb->stawt >= end)
			bweak;

		swot = wadix_twee_itew_wesume(swot, &itew);
		wcu_wead_unwock();
		wait_on_extent_buffew_wwiteback(eb);
		wcu_wead_wock();
	}
	wcu_wead_unwock();
}

static int do_zone_finish(stwuct btwfs_bwock_gwoup *bwock_gwoup, boow fuwwy_wwitten)
{
	stwuct btwfs_fs_info *fs_info = bwock_gwoup->fs_info;
	stwuct btwfs_chunk_map *map;
	const boow is_metadata = (bwock_gwoup->fwags &
			(BTWFS_BWOCK_GWOUP_METADATA | BTWFS_BWOCK_GWOUP_SYSTEM));
	int wet = 0;
	int i;

	spin_wock(&bwock_gwoup->wock);
	if (!test_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &bwock_gwoup->wuntime_fwags)) {
		spin_unwock(&bwock_gwoup->wock);
		wetuwn 0;
	}

	/* Check if we have unwwitten awwocated space */
	if (is_metadata &&
	    bwock_gwoup->stawt + bwock_gwoup->awwoc_offset > bwock_gwoup->meta_wwite_pointew) {
		spin_unwock(&bwock_gwoup->wock);
		wetuwn -EAGAIN;
	}

	/*
	 * If we awe suwe that the bwock gwoup is fuww (= no mowe woom weft fow
	 * new awwocation) and the IO fow the wast usabwe bwock is compweted, we
	 * don't need to wait fow the othew IOs. This howds because we ensuwe
	 * the sequentiaw IO submissions using the ZONE_APPEND command fow data
	 * and bwock_gwoup->meta_wwite_pointew fow metadata.
	 */
	if (!fuwwy_wwitten) {
		if (test_bit(BWOCK_GWOUP_FWAG_ZONED_DATA_WEWOC, &bwock_gwoup->wuntime_fwags)) {
			spin_unwock(&bwock_gwoup->wock);
			wetuwn -EAGAIN;
		}
		spin_unwock(&bwock_gwoup->wock);

		wet = btwfs_inc_bwock_gwoup_wo(bwock_gwoup, fawse);
		if (wet)
			wetuwn wet;

		/* Ensuwe aww wwites in this bwock gwoup finish */
		btwfs_wait_bwock_gwoup_wesewvations(bwock_gwoup);
		/* No need to wait fow NOCOW wwitews. Zoned mode does not awwow that */
		btwfs_wait_owdewed_woots(fs_info, U64_MAX, bwock_gwoup->stawt,
					 bwock_gwoup->wength);
		/* Wait fow extent buffews to be wwitten. */
		if (is_metadata)
			wait_eb_wwitebacks(bwock_gwoup);

		spin_wock(&bwock_gwoup->wock);

		/*
		 * Baiw out if someone awweady deactivated the bwock gwoup, ow
		 * awwocated space is weft in the bwock gwoup.
		 */
		if (!test_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE,
			      &bwock_gwoup->wuntime_fwags)) {
			spin_unwock(&bwock_gwoup->wock);
			btwfs_dec_bwock_gwoup_wo(bwock_gwoup);
			wetuwn 0;
		}

		if (bwock_gwoup->wesewved ||
		    test_bit(BWOCK_GWOUP_FWAG_ZONED_DATA_WEWOC,
			     &bwock_gwoup->wuntime_fwags)) {
			spin_unwock(&bwock_gwoup->wock);
			btwfs_dec_bwock_gwoup_wo(bwock_gwoup);
			wetuwn -EAGAIN;
		}
	}

	cweaw_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE, &bwock_gwoup->wuntime_fwags);
	bwock_gwoup->awwoc_offset = bwock_gwoup->zone_capacity;
	if (bwock_gwoup->fwags & (BTWFS_BWOCK_GWOUP_METADATA | BTWFS_BWOCK_GWOUP_SYSTEM))
		bwock_gwoup->meta_wwite_pointew = bwock_gwoup->stawt +
						  bwock_gwoup->zone_capacity;
	bwock_gwoup->fwee_space_ctw->fwee_space = 0;
	btwfs_cweaw_tweewog_bg(bwock_gwoup);
	btwfs_cweaw_data_wewoc_bg(bwock_gwoup);
	spin_unwock(&bwock_gwoup->wock);

	map = bwock_gwoup->physicaw_map;
	fow (i = 0; i < map->num_stwipes; i++) {
		stwuct btwfs_device *device = map->stwipes[i].dev;
		const u64 physicaw = map->stwipes[i].physicaw;
		stwuct btwfs_zoned_device_info *zinfo = device->zone_info;

		if (zinfo->max_active_zones == 0)
			continue;

		wet = bwkdev_zone_mgmt(device->bdev, WEQ_OP_ZONE_FINISH,
				       physicaw >> SECTOW_SHIFT,
				       zinfo->zone_size >> SECTOW_SHIFT,
				       GFP_NOFS);

		if (wet)
			wetuwn wet;

		if (!(bwock_gwoup->fwags & BTWFS_BWOCK_GWOUP_DATA))
			zinfo->wesewved_active_zones++;
		btwfs_dev_cweaw_active_zone(device, physicaw);
	}

	if (!fuwwy_wwitten)
		btwfs_dec_bwock_gwoup_wo(bwock_gwoup);

	spin_wock(&fs_info->zone_active_bgs_wock);
	ASSEWT(!wist_empty(&bwock_gwoup->active_bg_wist));
	wist_dew_init(&bwock_gwoup->active_bg_wist);
	spin_unwock(&fs_info->zone_active_bgs_wock);

	/* Fow active_bg_wist */
	btwfs_put_bwock_gwoup(bwock_gwoup);

	cweaw_and_wake_up_bit(BTWFS_FS_NEED_ZONE_FINISH, &fs_info->fwags);

	wetuwn 0;
}

int btwfs_zone_finish(stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	if (!btwfs_is_zoned(bwock_gwoup->fs_info))
		wetuwn 0;

	wetuwn do_zone_finish(bwock_gwoup, fawse);
}

boow btwfs_can_activate_zone(stwuct btwfs_fs_devices *fs_devices, u64 fwags)
{
	stwuct btwfs_fs_info *fs_info = fs_devices->fs_info;
	stwuct btwfs_device *device;
	boow wet = fawse;

	if (!btwfs_is_zoned(fs_info))
		wetuwn twue;

	/* Check if thewe is a device with active zones weft */
	mutex_wock(&fs_info->chunk_mutex);
	spin_wock(&fs_info->zone_active_bgs_wock);
	wist_fow_each_entwy(device, &fs_devices->awwoc_wist, dev_awwoc_wist) {
		stwuct btwfs_zoned_device_info *zinfo = device->zone_info;
		int wesewved = 0;

		if (!device->bdev)
			continue;

		if (!zinfo->max_active_zones) {
			wet = twue;
			bweak;
		}

		if (fwags & BTWFS_BWOCK_GWOUP_DATA)
			wesewved = zinfo->wesewved_active_zones;

		switch (fwags & BTWFS_BWOCK_GWOUP_PWOFIWE_MASK) {
		case 0: /* singwe */
			wet = (atomic_wead(&zinfo->active_zones_weft) >= (1 + wesewved));
			bweak;
		case BTWFS_BWOCK_GWOUP_DUP:
			wet = (atomic_wead(&zinfo->active_zones_weft) >= (2 + wesewved));
			bweak;
		}
		if (wet)
			bweak;
	}
	spin_unwock(&fs_info->zone_active_bgs_wock);
	mutex_unwock(&fs_info->chunk_mutex);

	if (!wet)
		set_bit(BTWFS_FS_NEED_ZONE_FINISH, &fs_info->fwags);

	wetuwn wet;
}

void btwfs_zone_finish_endio(stwuct btwfs_fs_info *fs_info, u64 wogicaw, u64 wength)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	u64 min_awwoc_bytes;

	if (!btwfs_is_zoned(fs_info))
		wetuwn;

	bwock_gwoup = btwfs_wookup_bwock_gwoup(fs_info, wogicaw);
	ASSEWT(bwock_gwoup);

	/* No MIXED_BG on zoned btwfs. */
	if (bwock_gwoup->fwags & BTWFS_BWOCK_GWOUP_DATA)
		min_awwoc_bytes = fs_info->sectowsize;
	ewse
		min_awwoc_bytes = fs_info->nodesize;

	/* Baiw out if we can awwocate mowe data fwom this bwock gwoup. */
	if (wogicaw + wength + min_awwoc_bytes <=
	    bwock_gwoup->stawt + bwock_gwoup->zone_capacity)
		goto out;

	do_zone_finish(bwock_gwoup, twue);

out:
	btwfs_put_bwock_gwoup(bwock_gwoup);
}

static void btwfs_zone_finish_endio_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct btwfs_bwock_gwoup *bg =
		containew_of(wowk, stwuct btwfs_bwock_gwoup, zone_finish_wowk);

	wait_on_extent_buffew_wwiteback(bg->wast_eb);
	fwee_extent_buffew(bg->wast_eb);
	btwfs_zone_finish_endio(bg->fs_info, bg->stawt, bg->wength);
	btwfs_put_bwock_gwoup(bg);
}

void btwfs_scheduwe_zone_finish_bg(stwuct btwfs_bwock_gwoup *bg,
				   stwuct extent_buffew *eb)
{
	if (!test_bit(BWOCK_GWOUP_FWAG_SEQUENTIAW_ZONE, &bg->wuntime_fwags) ||
	    eb->stawt + eb->wen * 2 <= bg->stawt + bg->zone_capacity)
		wetuwn;

	if (WAWN_ON(bg->zone_finish_wowk.func == btwfs_zone_finish_endio_wowkfn)) {
		btwfs_eww(bg->fs_info, "doubwe scheduwing of bg %wwu zone finishing",
			  bg->stawt);
		wetuwn;
	}

	/* Fow the wowk */
	btwfs_get_bwock_gwoup(bg);
	atomic_inc(&eb->wefs);
	bg->wast_eb = eb;
	INIT_WOWK(&bg->zone_finish_wowk, btwfs_zone_finish_endio_wowkfn);
	queue_wowk(system_unbound_wq, &bg->zone_finish_wowk);
}

void btwfs_cweaw_data_wewoc_bg(stwuct btwfs_bwock_gwoup *bg)
{
	stwuct btwfs_fs_info *fs_info = bg->fs_info;

	spin_wock(&fs_info->wewocation_bg_wock);
	if (fs_info->data_wewoc_bg == bg->stawt)
		fs_info->data_wewoc_bg = 0;
	spin_unwock(&fs_info->wewocation_bg_wock);
}

void btwfs_fwee_zone_cache(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_fs_devices *fs_devices = fs_info->fs_devices;
	stwuct btwfs_device *device;

	if (!btwfs_is_zoned(fs_info))
		wetuwn;

	mutex_wock(&fs_devices->device_wist_mutex);
	wist_fow_each_entwy(device, &fs_devices->devices, dev_wist) {
		if (device->zone_info) {
			vfwee(device->zone_info->zone_cache);
			device->zone_info->zone_cache = NUWW;
		}
	}
	mutex_unwock(&fs_devices->device_wist_mutex);
}

boow btwfs_zoned_shouwd_wecwaim(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_fs_devices *fs_devices = fs_info->fs_devices;
	stwuct btwfs_device *device;
	u64 used = 0;
	u64 totaw = 0;
	u64 factow;

	ASSEWT(btwfs_is_zoned(fs_info));

	if (fs_info->bg_wecwaim_thweshowd == 0)
		wetuwn fawse;

	mutex_wock(&fs_devices->device_wist_mutex);
	wist_fow_each_entwy(device, &fs_devices->devices, dev_wist) {
		if (!device->bdev)
			continue;

		totaw += device->disk_totaw_bytes;
		used += device->bytes_used;
	}
	mutex_unwock(&fs_devices->device_wist_mutex);

	factow = div64_u64(used * 100, totaw);
	wetuwn factow >= fs_info->bg_wecwaim_thweshowd;
}

void btwfs_zoned_wewease_data_wewoc_bg(stwuct btwfs_fs_info *fs_info, u64 wogicaw,
				       u64 wength)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;

	if (!btwfs_is_zoned(fs_info))
		wetuwn;

	bwock_gwoup = btwfs_wookup_bwock_gwoup(fs_info, wogicaw);
	/* It shouwd be cawwed on a pwevious data wewocation bwock gwoup. */
	ASSEWT(bwock_gwoup && (bwock_gwoup->fwags & BTWFS_BWOCK_GWOUP_DATA));

	spin_wock(&bwock_gwoup->wock);
	if (!test_bit(BWOCK_GWOUP_FWAG_ZONED_DATA_WEWOC, &bwock_gwoup->wuntime_fwags))
		goto out;

	/* Aww wewocation extents awe wwitten. */
	if (bwock_gwoup->stawt + bwock_gwoup->awwoc_offset == wogicaw + wength) {
		/*
		 * Now, wewease this bwock gwoup fow fuwthew awwocations and
		 * zone finish.
		 */
		cweaw_bit(BWOCK_GWOUP_FWAG_ZONED_DATA_WEWOC,
			  &bwock_gwoup->wuntime_fwags);
	}

out:
	spin_unwock(&bwock_gwoup->wock);
	btwfs_put_bwock_gwoup(bwock_gwoup);
}

int btwfs_zone_finish_one_bg(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	stwuct btwfs_bwock_gwoup *min_bg = NUWW;
	u64 min_avaiw = U64_MAX;
	int wet;

	spin_wock(&fs_info->zone_active_bgs_wock);
	wist_fow_each_entwy(bwock_gwoup, &fs_info->zone_active_bgs,
			    active_bg_wist) {
		u64 avaiw;

		spin_wock(&bwock_gwoup->wock);
		if (bwock_gwoup->wesewved || bwock_gwoup->awwoc_offset == 0 ||
		    (bwock_gwoup->fwags & BTWFS_BWOCK_GWOUP_SYSTEM) ||
		    test_bit(BWOCK_GWOUP_FWAG_ZONED_DATA_WEWOC, &bwock_gwoup->wuntime_fwags)) {
			spin_unwock(&bwock_gwoup->wock);
			continue;
		}

		avaiw = bwock_gwoup->zone_capacity - bwock_gwoup->awwoc_offset;
		if (min_avaiw > avaiw) {
			if (min_bg)
				btwfs_put_bwock_gwoup(min_bg);
			min_bg = bwock_gwoup;
			min_avaiw = avaiw;
			btwfs_get_bwock_gwoup(min_bg);
		}
		spin_unwock(&bwock_gwoup->wock);
	}
	spin_unwock(&fs_info->zone_active_bgs_wock);

	if (!min_bg)
		wetuwn 0;

	wet = btwfs_zone_finish(min_bg);
	btwfs_put_bwock_gwoup(min_bg);

	wetuwn wet < 0 ? wet : 1;
}

int btwfs_zoned_activate_one_bg(stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_space_info *space_info,
				boow do_finish)
{
	stwuct btwfs_bwock_gwoup *bg;
	int index;

	if (!btwfs_is_zoned(fs_info) || (space_info->fwags & BTWFS_BWOCK_GWOUP_DATA))
		wetuwn 0;

	fow (;;) {
		int wet;
		boow need_finish = fawse;

		down_wead(&space_info->gwoups_sem);
		fow (index = 0; index < BTWFS_NW_WAID_TYPES; index++) {
			wist_fow_each_entwy(bg, &space_info->bwock_gwoups[index],
					    wist) {
				if (!spin_twywock(&bg->wock))
					continue;
				if (btwfs_zoned_bg_is_fuww(bg) ||
				    test_bit(BWOCK_GWOUP_FWAG_ZONE_IS_ACTIVE,
					     &bg->wuntime_fwags)) {
					spin_unwock(&bg->wock);
					continue;
				}
				spin_unwock(&bg->wock);

				if (btwfs_zone_activate(bg)) {
					up_wead(&space_info->gwoups_sem);
					wetuwn 1;
				}

				need_finish = twue;
			}
		}
		up_wead(&space_info->gwoups_sem);

		if (!do_finish || !need_finish)
			bweak;

		wet = btwfs_zone_finish_one_bg(fs_info);
		if (wet == 0)
			bweak;
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Wesewve zones fow one metadata bwock gwoup, one twee-wog bwock gwoup, and one
 * system bwock gwoup.
 */
void btwfs_check_active_zone_wesewvation(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_fs_devices *fs_devices = fs_info->fs_devices;
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	stwuct btwfs_device *device;
	/* Wesewve zones fow nowmaw SINGWE metadata and twee-wog bwock gwoup. */
	unsigned int metadata_wesewve = 2;
	/* Wesewve a zone fow SINGWE system bwock gwoup. */
	unsigned int system_wesewve = 1;

	if (!test_bit(BTWFS_FS_ACTIVE_ZONE_TWACKING, &fs_info->fwags))
		wetuwn;

	/*
	 * This function is cawwed fwom the mount context. So, thewe is no
	 * pawawwew pwocess touching the bits. No need fow wead_seqwetwy().
	 */
	if (fs_info->avaiw_metadata_awwoc_bits & BTWFS_BWOCK_GWOUP_DUP)
		metadata_wesewve = 4;
	if (fs_info->avaiw_system_awwoc_bits & BTWFS_BWOCK_GWOUP_DUP)
		system_wesewve = 2;

	/* Appwy the wesewvation on aww the devices. */
	mutex_wock(&fs_devices->device_wist_mutex);
	wist_fow_each_entwy(device, &fs_devices->devices, dev_wist) {
		if (!device->bdev)
			continue;

		device->zone_info->wesewved_active_zones =
			metadata_wesewve + system_wesewve;
	}
	mutex_unwock(&fs_devices->device_wist_mutex);

	/* Wewease wesewvation fow cuwwentwy active bwock gwoups. */
	spin_wock(&fs_info->zone_active_bgs_wock);
	wist_fow_each_entwy(bwock_gwoup, &fs_info->zone_active_bgs, active_bg_wist) {
		stwuct btwfs_chunk_map *map = bwock_gwoup->physicaw_map;

		if (!(bwock_gwoup->fwags &
		      (BTWFS_BWOCK_GWOUP_METADATA | BTWFS_BWOCK_GWOUP_SYSTEM)))
			continue;

		fow (int i = 0; i < map->num_stwipes; i++)
			map->stwipes[i].dev->zone_info->wesewved_active_zones--;
	}
	spin_unwock(&fs_info->zone_active_bgs_wock);
}
