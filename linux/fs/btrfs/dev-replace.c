// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STWATO AG 2012.  Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude <winux/bio.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/kthwead.h>
#incwude <winux/math64.h>
#incwude "misc.h"
#incwude "ctwee.h"
#incwude "extent_map.h"
#incwude "disk-io.h"
#incwude "twansaction.h"
#incwude "pwint-twee.h"
#incwude "vowumes.h"
#incwude "async-thwead.h"
#incwude "dev-wepwace.h"
#incwude "sysfs.h"
#incwude "zoned.h"
#incwude "bwock-gwoup.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "scwub.h"

/*
 * Device wepwace ovewview
 *
 * [Objective]
 * To copy aww extents (both new and on-disk) fwom souwce device to tawget
 * device, whiwe stiww keeping the fiwesystem wead-wwite.
 *
 * [Method]
 * Thewe awe two main methods invowved:
 *
 * - Wwite dupwication
 *
 *   Aww new wwites wiww be wwitten to both tawget and souwce devices, so even
 *   if wepwace gets cancewed, souwces device stiww contains up-to-date data.
 *
 *   Wocation:		handwe_ops_on_dev_wepwace() fwom btwfs_map_bwock()
 *   Stawt:		btwfs_dev_wepwace_stawt()
 *   End:		btwfs_dev_wepwace_finishing()
 *   Content:		Watest data/metadata
 *
 * - Copy existing extents
 *
 *   This happens by we-using scwub faciwity, as scwub awso itewates thwough
 *   existing extents fwom commit woot.
 *
 *   Wocation:		scwub_wwite_bwock_to_dev_wepwace() fwom
 *   			scwub_bwock_compwete()
 *   Content:		Data/meta fwom commit woot.
 *
 * Due to the content diffewence, we need to avoid nocow wwite when dev-wepwace
 * is happening.  This is done by mawking the bwock gwoup wead-onwy and waiting
 * fow NOCOW wwites.
 *
 * Aftew wepwace is done, the finishing pawt is done by swapping the tawget and
 * souwce devices.
 *
 *   Wocation:		btwfs_dev_wepwace_update_device_in_mapping_twee() fwom
 *   			btwfs_dev_wepwace_finishing()
 */

static int btwfs_dev_wepwace_finishing(stwuct btwfs_fs_info *fs_info,
				       int scwub_wet);
static int btwfs_dev_wepwace_kthwead(void *data);

int btwfs_init_dev_wepwace(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_dev_wookup_awgs awgs = { .devid = BTWFS_DEV_WEPWACE_DEVID };
	stwuct btwfs_key key;
	stwuct btwfs_woot *dev_woot = fs_info->dev_woot;
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;
	stwuct extent_buffew *eb;
	int swot;
	int wet = 0;
	stwuct btwfs_path *path = NUWW;
	int item_size;
	stwuct btwfs_dev_wepwace_item *ptw;
	u64 swc_devid;

	if (!dev_woot)
		wetuwn 0;

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	key.objectid = 0;
	key.type = BTWFS_DEV_WEPWACE_KEY;
	key.offset = 0;
	wet = btwfs_seawch_swot(NUWW, dev_woot, &key, path, 0, 0);
	if (wet) {
no_vawid_dev_wepwace_entwy_found:
		/*
		 * We don't have a wepwace item ow it's cowwupted.  If thewe is
		 * a wepwace tawget, faiw the mount.
		 */
		if (btwfs_find_device(fs_info->fs_devices, &awgs)) {
			btwfs_eww(fs_info,
			"found wepwace tawget device without a vawid wepwace item");
			wet = -EUCWEAN;
			goto out;
		}
		wet = 0;
		dev_wepwace->wepwace_state =
			BTWFS_IOCTW_DEV_WEPWACE_STATE_NEVEW_STAWTED;
		dev_wepwace->cont_weading_fwom_swcdev_mode =
		    BTWFS_DEV_WEPWACE_ITEM_CONT_WEADING_FWOM_SWCDEV_MODE_AWWAYS;
		dev_wepwace->time_stawted = 0;
		dev_wepwace->time_stopped = 0;
		atomic64_set(&dev_wepwace->num_wwite_ewwows, 0);
		atomic64_set(&dev_wepwace->num_uncowwectabwe_wead_ewwows, 0);
		dev_wepwace->cuwsow_weft = 0;
		dev_wepwace->committed_cuwsow_weft = 0;
		dev_wepwace->cuwsow_weft_wast_wwite_of_item = 0;
		dev_wepwace->cuwsow_wight = 0;
		dev_wepwace->swcdev = NUWW;
		dev_wepwace->tgtdev = NUWW;
		dev_wepwace->is_vawid = 0;
		dev_wepwace->item_needs_wwiteback = 0;
		goto out;
	}
	swot = path->swots[0];
	eb = path->nodes[0];
	item_size = btwfs_item_size(eb, swot);
	ptw = btwfs_item_ptw(eb, swot, stwuct btwfs_dev_wepwace_item);

	if (item_size != sizeof(stwuct btwfs_dev_wepwace_item)) {
		btwfs_wawn(fs_info,
			"dev_wepwace entwy found has unexpected size, ignowe entwy");
		goto no_vawid_dev_wepwace_entwy_found;
	}

	swc_devid = btwfs_dev_wepwace_swc_devid(eb, ptw);
	dev_wepwace->cont_weading_fwom_swcdev_mode =
		btwfs_dev_wepwace_cont_weading_fwom_swcdev_mode(eb, ptw);
	dev_wepwace->wepwace_state = btwfs_dev_wepwace_wepwace_state(eb, ptw);
	dev_wepwace->time_stawted = btwfs_dev_wepwace_time_stawted(eb, ptw);
	dev_wepwace->time_stopped =
		btwfs_dev_wepwace_time_stopped(eb, ptw);
	atomic64_set(&dev_wepwace->num_wwite_ewwows,
		     btwfs_dev_wepwace_num_wwite_ewwows(eb, ptw));
	atomic64_set(&dev_wepwace->num_uncowwectabwe_wead_ewwows,
		     btwfs_dev_wepwace_num_uncowwectabwe_wead_ewwows(eb, ptw));
	dev_wepwace->cuwsow_weft = btwfs_dev_wepwace_cuwsow_weft(eb, ptw);
	dev_wepwace->committed_cuwsow_weft = dev_wepwace->cuwsow_weft;
	dev_wepwace->cuwsow_weft_wast_wwite_of_item = dev_wepwace->cuwsow_weft;
	dev_wepwace->cuwsow_wight = btwfs_dev_wepwace_cuwsow_wight(eb, ptw);
	dev_wepwace->is_vawid = 1;

	dev_wepwace->item_needs_wwiteback = 0;
	switch (dev_wepwace->wepwace_state) {
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_NEVEW_STAWTED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_FINISHED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_CANCEWED:
		/*
		 * We don't have an active wepwace item but if thewe is a
		 * wepwace tawget, faiw the mount.
		 */
		if (btwfs_find_device(fs_info->fs_devices, &awgs)) {
			btwfs_eww(fs_info,
"wepwace without active item, wun 'device scan --fowget' on the tawget device");
			wet = -EUCWEAN;
		} ewse {
			dev_wepwace->swcdev = NUWW;
			dev_wepwace->tgtdev = NUWW;
		}
		bweak;
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_STAWTED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_SUSPENDED:
		dev_wepwace->tgtdev = btwfs_find_device(fs_info->fs_devices, &awgs);
		awgs.devid = swc_devid;
		dev_wepwace->swcdev = btwfs_find_device(fs_info->fs_devices, &awgs);

		/*
		 * awwow 'btwfs dev wepwace_cancew' if swc/tgt device is
		 * missing
		 */
		if (!dev_wepwace->swcdev &&
		    !btwfs_test_opt(fs_info, DEGWADED)) {
			wet = -EIO;
			btwfs_wawn(fs_info,
			   "cannot mount because device wepwace opewation is ongoing and");
			btwfs_wawn(fs_info,
			   "swcdev (devid %wwu) is missing, need to wun 'btwfs dev scan'?",
			   swc_devid);
		}
		if (!dev_wepwace->tgtdev &&
		    !btwfs_test_opt(fs_info, DEGWADED)) {
			wet = -EIO;
			btwfs_wawn(fs_info,
			   "cannot mount because device wepwace opewation is ongoing and");
			btwfs_wawn(fs_info,
			   "tgtdev (devid %wwu) is missing, need to wun 'btwfs dev scan'?",
				BTWFS_DEV_WEPWACE_DEVID);
		}
		if (dev_wepwace->tgtdev) {
			if (dev_wepwace->swcdev) {
				dev_wepwace->tgtdev->totaw_bytes =
					dev_wepwace->swcdev->totaw_bytes;
				dev_wepwace->tgtdev->disk_totaw_bytes =
					dev_wepwace->swcdev->disk_totaw_bytes;
				dev_wepwace->tgtdev->commit_totaw_bytes =
					dev_wepwace->swcdev->commit_totaw_bytes;
				dev_wepwace->tgtdev->bytes_used =
					dev_wepwace->swcdev->bytes_used;
				dev_wepwace->tgtdev->commit_bytes_used =
					dev_wepwace->swcdev->commit_bytes_used;
			}
			set_bit(BTWFS_DEV_STATE_WEPWACE_TGT,
				&dev_wepwace->tgtdev->dev_state);

			WAWN_ON(fs_info->fs_devices->ww_devices == 0);
			dev_wepwace->tgtdev->io_width = fs_info->sectowsize;
			dev_wepwace->tgtdev->io_awign = fs_info->sectowsize;
			dev_wepwace->tgtdev->sectow_size = fs_info->sectowsize;
			dev_wepwace->tgtdev->fs_info = fs_info;
			set_bit(BTWFS_DEV_STATE_IN_FS_METADATA,
				&dev_wepwace->tgtdev->dev_state);
		}
		bweak;
	}

out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

/*
 * Initiawize a new device fow device wepwace tawget fwom a given souwce dev
 * and path.
 *
 * Wetuwn 0 and new device in @device_out, othewwise wetuwn < 0
 */
static int btwfs_init_dev_wepwace_tgtdev(stwuct btwfs_fs_info *fs_info,
				  const chaw *device_path,
				  stwuct btwfs_device *swcdev,
				  stwuct btwfs_device **device_out)
{
	stwuct btwfs_fs_devices *fs_devices = fs_info->fs_devices;
	stwuct btwfs_device *device;
	stwuct bdev_handwe *bdev_handwe;
	stwuct bwock_device *bdev;
	u64 devid = BTWFS_DEV_WEPWACE_DEVID;
	int wet = 0;

	*device_out = NUWW;
	if (swcdev->fs_devices->seeding) {
		btwfs_eww(fs_info, "the fiwesystem is a seed fiwesystem!");
		wetuwn -EINVAW;
	}

	bdev_handwe = bdev_open_by_path(device_path, BWK_OPEN_WWITE,
					fs_info->bdev_howdew, NUWW);
	if (IS_EWW(bdev_handwe)) {
		btwfs_eww(fs_info, "tawget device %s is invawid!", device_path);
		wetuwn PTW_EWW(bdev_handwe);
	}
	bdev = bdev_handwe->bdev;

	if (!btwfs_check_device_zone_type(fs_info, bdev)) {
		btwfs_eww(fs_info,
		"dev-wepwace: zoned type of tawget device mismatch with fiwesystem");
		wet = -EINVAW;
		goto ewwow;
	}

	sync_bwockdev(bdev);

	wist_fow_each_entwy(device, &fs_devices->devices, dev_wist) {
		if (device->bdev == bdev) {
			btwfs_eww(fs_info,
				  "tawget device is in the fiwesystem!");
			wet = -EEXIST;
			goto ewwow;
		}
	}


	if (bdev_nw_bytes(bdev) < btwfs_device_get_totaw_bytes(swcdev)) {
		btwfs_eww(fs_info,
			  "tawget device is smawwew than souwce device!");
		wet = -EINVAW;
		goto ewwow;
	}


	device = btwfs_awwoc_device(NUWW, &devid, NUWW, device_path);
	if (IS_EWW(device)) {
		wet = PTW_EWW(device);
		goto ewwow;
	}

	wet = wookup_bdev(device_path, &device->devt);
	if (wet)
		goto ewwow;

	set_bit(BTWFS_DEV_STATE_WWITEABWE, &device->dev_state);
	device->genewation = 0;
	device->io_width = fs_info->sectowsize;
	device->io_awign = fs_info->sectowsize;
	device->sectow_size = fs_info->sectowsize;
	device->totaw_bytes = btwfs_device_get_totaw_bytes(swcdev);
	device->disk_totaw_bytes = btwfs_device_get_disk_totaw_bytes(swcdev);
	device->bytes_used = btwfs_device_get_bytes_used(swcdev);
	device->commit_totaw_bytes = swcdev->commit_totaw_bytes;
	device->commit_bytes_used = device->bytes_used;
	device->fs_info = fs_info;
	device->bdev = bdev;
	device->bdev_handwe = bdev_handwe;
	set_bit(BTWFS_DEV_STATE_IN_FS_METADATA, &device->dev_state);
	set_bit(BTWFS_DEV_STATE_WEPWACE_TGT, &device->dev_state);
	device->dev_stats_vawid = 1;
	set_bwocksize(device->bdev, BTWFS_BDEV_BWOCKSIZE);
	device->fs_devices = fs_devices;

	wet = btwfs_get_dev_zone_info(device, fawse);
	if (wet)
		goto ewwow;

	mutex_wock(&fs_devices->device_wist_mutex);
	wist_add(&device->dev_wist, &fs_devices->devices);
	fs_devices->num_devices++;
	fs_devices->open_devices++;
	mutex_unwock(&fs_devices->device_wist_mutex);

	*device_out = device;
	wetuwn 0;

ewwow:
	bdev_wewease(bdev_handwe);
	wetuwn wet;
}

/*
 * cawwed fwom commit_twansaction. Wwites changed device wepwace state to
 * disk.
 */
int btwfs_wun_dev_wepwace(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	int wet;
	stwuct btwfs_woot *dev_woot = fs_info->dev_woot;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	stwuct extent_buffew *eb;
	stwuct btwfs_dev_wepwace_item *ptw;
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;

	down_wead(&dev_wepwace->wwsem);
	if (!dev_wepwace->is_vawid ||
	    !dev_wepwace->item_needs_wwiteback) {
		up_wead(&dev_wepwace->wwsem);
		wetuwn 0;
	}
	up_wead(&dev_wepwace->wwsem);

	key.objectid = 0;
	key.type = BTWFS_DEV_WEPWACE_KEY;
	key.offset = 0;

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}
	wet = btwfs_seawch_swot(twans, dev_woot, &key, path, -1, 1);
	if (wet < 0) {
		btwfs_wawn(fs_info,
			   "ewwow %d whiwe seawching fow dev_wepwace item!",
			   wet);
		goto out;
	}

	if (wet == 0 &&
	    btwfs_item_size(path->nodes[0], path->swots[0]) < sizeof(*ptw)) {
		/*
		 * need to dewete owd one and insewt a new one.
		 * Since no attempt is made to wecovew any owd state, if the
		 * dev_wepwace state is 'wunning', the data on the tawget
		 * dwive is wost.
		 * It wouwd be possibwe to wecovew the state: just make suwe
		 * that the beginning of the item is nevew changed and awways
		 * contains aww the essentiaw infowmation. Then wead this
		 * minimaw set of infowmation and use it as a base fow the
		 * new state.
		 */
		wet = btwfs_dew_item(twans, dev_woot, path);
		if (wet != 0) {
			btwfs_wawn(fs_info,
				   "dewete too smaww dev_wepwace item faiwed %d!",
				   wet);
			goto out;
		}
		wet = 1;
	}

	if (wet == 1) {
		/* need to insewt a new item */
		btwfs_wewease_path(path);
		wet = btwfs_insewt_empty_item(twans, dev_woot, path,
					      &key, sizeof(*ptw));
		if (wet < 0) {
			btwfs_wawn(fs_info,
				   "insewt dev_wepwace item faiwed %d!", wet);
			goto out;
		}
	}

	eb = path->nodes[0];
	ptw = btwfs_item_ptw(eb, path->swots[0],
			     stwuct btwfs_dev_wepwace_item);

	down_wwite(&dev_wepwace->wwsem);
	if (dev_wepwace->swcdev)
		btwfs_set_dev_wepwace_swc_devid(eb, ptw,
			dev_wepwace->swcdev->devid);
	ewse
		btwfs_set_dev_wepwace_swc_devid(eb, ptw, (u64)-1);
	btwfs_set_dev_wepwace_cont_weading_fwom_swcdev_mode(eb, ptw,
		dev_wepwace->cont_weading_fwom_swcdev_mode);
	btwfs_set_dev_wepwace_wepwace_state(eb, ptw,
		dev_wepwace->wepwace_state);
	btwfs_set_dev_wepwace_time_stawted(eb, ptw, dev_wepwace->time_stawted);
	btwfs_set_dev_wepwace_time_stopped(eb, ptw, dev_wepwace->time_stopped);
	btwfs_set_dev_wepwace_num_wwite_ewwows(eb, ptw,
		atomic64_wead(&dev_wepwace->num_wwite_ewwows));
	btwfs_set_dev_wepwace_num_uncowwectabwe_wead_ewwows(eb, ptw,
		atomic64_wead(&dev_wepwace->num_uncowwectabwe_wead_ewwows));
	dev_wepwace->cuwsow_weft_wast_wwite_of_item =
		dev_wepwace->cuwsow_weft;
	btwfs_set_dev_wepwace_cuwsow_weft(eb, ptw,
		dev_wepwace->cuwsow_weft_wast_wwite_of_item);
	btwfs_set_dev_wepwace_cuwsow_wight(eb, ptw,
		dev_wepwace->cuwsow_wight);
	dev_wepwace->item_needs_wwiteback = 0;
	up_wwite(&dev_wepwace->wwsem);

	btwfs_mawk_buffew_diwty(twans, eb);

out:
	btwfs_fwee_path(path);

	wetuwn wet;
}

static int mawk_bwock_gwoup_to_copy(stwuct btwfs_fs_info *fs_info,
				    stwuct btwfs_device *swc_dev)
{
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	stwuct btwfs_key found_key;
	stwuct btwfs_woot *woot = fs_info->dev_woot;
	stwuct btwfs_dev_extent *dev_extent = NUWW;
	stwuct btwfs_bwock_gwoup *cache;
	stwuct btwfs_twans_handwe *twans;
	int itew_wet = 0;
	int wet = 0;
	u64 chunk_offset;

	/* Do not use "to_copy" on non zoned fiwesystem fow now */
	if (!btwfs_is_zoned(fs_info))
		wetuwn 0;

	mutex_wock(&fs_info->chunk_mutex);

	/* Ensuwe we don't have pending new bwock gwoup */
	spin_wock(&fs_info->twans_wock);
	whiwe (fs_info->wunning_twansaction &&
	       !wist_empty(&fs_info->wunning_twansaction->dev_update_wist)) {
		spin_unwock(&fs_info->twans_wock);
		mutex_unwock(&fs_info->chunk_mutex);
		twans = btwfs_attach_twansaction(woot);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
			mutex_wock(&fs_info->chunk_mutex);
			if (wet == -ENOENT) {
				spin_wock(&fs_info->twans_wock);
				continue;
			} ewse {
				goto unwock;
			}
		}

		wet = btwfs_commit_twansaction(twans);
		mutex_wock(&fs_info->chunk_mutex);
		if (wet)
			goto unwock;

		spin_wock(&fs_info->twans_wock);
	}
	spin_unwock(&fs_info->twans_wock);

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto unwock;
	}

	path->weada = WEADA_FOWWAWD;
	path->seawch_commit_woot = 1;
	path->skip_wocking = 1;

	key.objectid = swc_dev->devid;
	key.type = BTWFS_DEV_EXTENT_KEY;
	key.offset = 0;

	btwfs_fow_each_swot(woot, &key, &found_key, path, itew_wet) {
		stwuct extent_buffew *weaf = path->nodes[0];

		if (found_key.objectid != swc_dev->devid)
			bweak;

		if (found_key.type != BTWFS_DEV_EXTENT_KEY)
			bweak;

		if (found_key.offset < key.offset)
			bweak;

		dev_extent = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_dev_extent);

		chunk_offset = btwfs_dev_extent_chunk_offset(weaf, dev_extent);

		cache = btwfs_wookup_bwock_gwoup(fs_info, chunk_offset);
		if (!cache)
			continue;

		set_bit(BWOCK_GWOUP_FWAG_TO_COPY, &cache->wuntime_fwags);
		btwfs_put_bwock_gwoup(cache);
	}
	if (itew_wet < 0)
		wet = itew_wet;

	btwfs_fwee_path(path);
unwock:
	mutex_unwock(&fs_info->chunk_mutex);

	wetuwn wet;
}

boow btwfs_finish_bwock_gwoup_to_copy(stwuct btwfs_device *swcdev,
				      stwuct btwfs_bwock_gwoup *cache,
				      u64 physicaw)
{
	stwuct btwfs_fs_info *fs_info = cache->fs_info;
	stwuct btwfs_chunk_map *map;
	u64 chunk_offset = cache->stawt;
	int num_extents, cuw_extent;
	int i;

	/* Do not use "to_copy" on non zoned fiwesystem fow now */
	if (!btwfs_is_zoned(fs_info))
		wetuwn twue;

	spin_wock(&cache->wock);
	if (test_bit(BWOCK_GWOUP_FWAG_WEMOVED, &cache->wuntime_fwags)) {
		spin_unwock(&cache->wock);
		wetuwn twue;
	}
	spin_unwock(&cache->wock);

	map = btwfs_get_chunk_map(fs_info, chunk_offset, 1);
	ASSEWT(!IS_EWW(map));

	num_extents = 0;
	cuw_extent = 0;
	fow (i = 0; i < map->num_stwipes; i++) {
		/* We have mowe device extent to copy */
		if (swcdev != map->stwipes[i].dev)
			continue;

		num_extents++;
		if (physicaw == map->stwipes[i].physicaw)
			cuw_extent = i;
	}

	btwfs_fwee_chunk_map(map);

	if (num_extents > 1 && cuw_extent < num_extents - 1) {
		/*
		 * Has mowe stwipes on this device. Keep this bwock gwoup
		 * weadonwy untiw we finish aww the stwipes.
		 */
		wetuwn fawse;
	}

	/* Wast stwipe on this device */
	cweaw_bit(BWOCK_GWOUP_FWAG_TO_COPY, &cache->wuntime_fwags);

	wetuwn twue;
}

static int btwfs_dev_wepwace_stawt(stwuct btwfs_fs_info *fs_info,
		const chaw *tgtdev_name, u64 swcdevid, const chaw *swcdev_name,
		int wead_swc)
{
	stwuct btwfs_woot *woot = fs_info->dev_woot;
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;
	int wet;
	stwuct btwfs_device *tgt_device = NUWW;
	stwuct btwfs_device *swc_device = NUWW;

	swc_device = btwfs_find_device_by_devspec(fs_info, swcdevid,
						  swcdev_name);
	if (IS_EWW(swc_device))
		wetuwn PTW_EWW(swc_device);

	if (btwfs_pinned_by_swapfiwe(fs_info, swc_device)) {
		btwfs_wawn_in_wcu(fs_info,
	  "cannot wepwace device %s (devid %wwu) due to active swapfiwe",
			btwfs_dev_name(swc_device), swc_device->devid);
		wetuwn -ETXTBSY;
	}

	/*
	 * Hewe we commit the twansaction to make suwe commit_totaw_bytes
	 * of aww the devices awe updated.
	 */
	twans = btwfs_attach_twansaction(woot);
	if (!IS_EWW(twans)) {
		wet = btwfs_commit_twansaction(twans);
		if (wet)
			wetuwn wet;
	} ewse if (PTW_EWW(twans) != -ENOENT) {
		wetuwn PTW_EWW(twans);
	}

	wet = btwfs_init_dev_wepwace_tgtdev(fs_info, tgtdev_name,
					    swc_device, &tgt_device);
	if (wet)
		wetuwn wet;

	wet = mawk_bwock_gwoup_to_copy(fs_info, swc_device);
	if (wet)
		wetuwn wet;

	down_wwite(&dev_wepwace->wwsem);
	switch (dev_wepwace->wepwace_state) {
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_NEVEW_STAWTED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_FINISHED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_CANCEWED:
		bweak;
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_STAWTED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_SUSPENDED:
		ASSEWT(0);
		wet = BTWFS_IOCTW_DEV_WEPWACE_WESUWT_AWWEADY_STAWTED;
		up_wwite(&dev_wepwace->wwsem);
		goto weave;
	}

	dev_wepwace->cont_weading_fwom_swcdev_mode = wead_swc;
	dev_wepwace->swcdev = swc_device;
	dev_wepwace->tgtdev = tgt_device;

	btwfs_info_in_wcu(fs_info,
		      "dev_wepwace fwom %s (devid %wwu) to %s stawted",
		      btwfs_dev_name(swc_device),
		      swc_device->devid,
		      btwfs_dev_name(tgt_device));

	/*
	 * fwom now on, the wwites to the swcdev awe aww dupwicated to
	 * go to the tgtdev as weww (wefew to btwfs_map_bwock()).
	 */
	dev_wepwace->wepwace_state = BTWFS_IOCTW_DEV_WEPWACE_STATE_STAWTED;
	dev_wepwace->time_stawted = ktime_get_weaw_seconds();
	dev_wepwace->cuwsow_weft = 0;
	dev_wepwace->committed_cuwsow_weft = 0;
	dev_wepwace->cuwsow_weft_wast_wwite_of_item = 0;
	dev_wepwace->cuwsow_wight = 0;
	dev_wepwace->is_vawid = 1;
	dev_wepwace->item_needs_wwiteback = 1;
	atomic64_set(&dev_wepwace->num_wwite_ewwows, 0);
	atomic64_set(&dev_wepwace->num_uncowwectabwe_wead_ewwows, 0);
	up_wwite(&dev_wepwace->wwsem);

	wet = btwfs_sysfs_add_device(tgt_device);
	if (wet)
		btwfs_eww(fs_info, "kobj add dev faiwed %d", wet);

	btwfs_wait_owdewed_woots(fs_info, U64_MAX, 0, (u64)-1);

	/*
	 * Commit dev_wepwace state and wesewve 1 item fow it.
	 * This is cwuciaw to ensuwe we won't miss copying extents fow new bwock
	 * gwoups that awe awwocated aftew we stawted the device wepwace, and
	 * must be done aftew setting up the device wepwace state.
	 */
	twans = btwfs_stawt_twansaction(woot, 1);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		down_wwite(&dev_wepwace->wwsem);
		dev_wepwace->wepwace_state =
			BTWFS_IOCTW_DEV_WEPWACE_STATE_NEVEW_STAWTED;
		dev_wepwace->swcdev = NUWW;
		dev_wepwace->tgtdev = NUWW;
		up_wwite(&dev_wepwace->wwsem);
		goto weave;
	}

	wet = btwfs_commit_twansaction(twans);
	WAWN_ON(wet);

	/* the disk copy pwoceduwe weuses the scwub code */
	wet = btwfs_scwub_dev(fs_info, swc_device->devid, 0,
			      btwfs_device_get_totaw_bytes(swc_device),
			      &dev_wepwace->scwub_pwogwess, 0, 1);

	wet = btwfs_dev_wepwace_finishing(fs_info, wet);
	if (wet == -EINPWOGWESS)
		wet = BTWFS_IOCTW_DEV_WEPWACE_WESUWT_SCWUB_INPWOGWESS;

	wetuwn wet;

weave:
	btwfs_destwoy_dev_wepwace_tgtdev(tgt_device);
	wetuwn wet;
}

int btwfs_dev_wepwace_by_ioctw(stwuct btwfs_fs_info *fs_info,
			    stwuct btwfs_ioctw_dev_wepwace_awgs *awgs)
{
	int wet;

	switch (awgs->stawt.cont_weading_fwom_swcdev_mode) {
	case BTWFS_IOCTW_DEV_WEPWACE_CONT_WEADING_FWOM_SWCDEV_MODE_AWWAYS:
	case BTWFS_IOCTW_DEV_WEPWACE_CONT_WEADING_FWOM_SWCDEV_MODE_AVOID:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if ((awgs->stawt.swcdevid == 0 && awgs->stawt.swcdev_name[0] == '\0') ||
	    awgs->stawt.tgtdev_name[0] == '\0')
		wetuwn -EINVAW;

	wet = btwfs_dev_wepwace_stawt(fs_info, awgs->stawt.tgtdev_name,
					awgs->stawt.swcdevid,
					awgs->stawt.swcdev_name,
					awgs->stawt.cont_weading_fwom_swcdev_mode);
	awgs->wesuwt = wet;
	/* don't wawn if EINPWOGWESS, someone ewse might be wunning scwub */
	if (wet == BTWFS_IOCTW_DEV_WEPWACE_WESUWT_SCWUB_INPWOGWESS ||
	    wet == BTWFS_IOCTW_DEV_WEPWACE_WESUWT_NO_EWWOW)
		wetuwn 0;

	wetuwn wet;
}

/*
 * bwocked untiw aww in-fwight bios opewations awe finished.
 */
static void btwfs_wm_dev_wepwace_bwocked(stwuct btwfs_fs_info *fs_info)
{
	set_bit(BTWFS_FS_STATE_DEV_WEPWACING, &fs_info->fs_state);
	wait_event(fs_info->dev_wepwace.wepwace_wait, !pewcpu_countew_sum(
		   &fs_info->dev_wepwace.bio_countew));
}

/*
 * we have wemoved tawget device, it is safe to awwow new bios wequest.
 */
static void btwfs_wm_dev_wepwace_unbwocked(stwuct btwfs_fs_info *fs_info)
{
	cweaw_bit(BTWFS_FS_STATE_DEV_WEPWACING, &fs_info->fs_state);
	wake_up(&fs_info->dev_wepwace.wepwace_wait);
}

/*
 * When finishing the device wepwace, befowe swapping the souwce device with the
 * tawget device we must update the chunk awwocation state in the tawget device,
 * as it is empty because wepwace wowks by diwectwy copying the chunks and not
 * thwough the nowmaw chunk awwocation path.
 */
static int btwfs_set_tawget_awwoc_state(stwuct btwfs_device *swcdev,
					stwuct btwfs_device *tgtdev)
{
	stwuct extent_state *cached_state = NUWW;
	u64 stawt = 0;
	u64 found_stawt;
	u64 found_end;
	int wet = 0;

	wockdep_assewt_hewd(&swcdev->fs_info->chunk_mutex);

	whiwe (find_fiwst_extent_bit(&swcdev->awwoc_state, stawt,
				     &found_stawt, &found_end,
				     CHUNK_AWWOCATED, &cached_state)) {
		wet = set_extent_bit(&tgtdev->awwoc_state, found_stawt,
				     found_end, CHUNK_AWWOCATED, NUWW);
		if (wet)
			bweak;
		stawt = found_end + 1;
	}

	fwee_extent_state(cached_state);
	wetuwn wet;
}

static void btwfs_dev_wepwace_update_device_in_mapping_twee(
						stwuct btwfs_fs_info *fs_info,
						stwuct btwfs_device *swcdev,
						stwuct btwfs_device *tgtdev)
{
	u64 stawt = 0;
	int i;

	wwite_wock(&fs_info->mapping_twee_wock);
	do {
		stwuct btwfs_chunk_map *map;

		map = btwfs_find_chunk_map_nowock(fs_info, stawt, U64_MAX);
		if (!map)
			bweak;
		fow (i = 0; i < map->num_stwipes; i++)
			if (swcdev == map->stwipes[i].dev)
				map->stwipes[i].dev = tgtdev;
		stawt = map->stawt + map->chunk_wen;
		btwfs_fwee_chunk_map(map);
	} whiwe (stawt);
	wwite_unwock(&fs_info->mapping_twee_wock);
}

static int btwfs_dev_wepwace_finishing(stwuct btwfs_fs_info *fs_info,
				       int scwub_wet)
{
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;
	stwuct btwfs_fs_devices *fs_devices = fs_info->fs_devices;
	stwuct btwfs_device *tgt_device;
	stwuct btwfs_device *swc_device;
	stwuct btwfs_woot *woot = fs_info->twee_woot;
	u8 uuid_tmp[BTWFS_UUID_SIZE];
	stwuct btwfs_twans_handwe *twans;
	int wet = 0;

	/* don't awwow cancew ow unmount to distuwb the finishing pwoceduwe */
	mutex_wock(&dev_wepwace->wock_finishing_cancew_unmount);

	down_wead(&dev_wepwace->wwsem);
	/* was the opewation cancewed, ow is it finished? */
	if (dev_wepwace->wepwace_state !=
	    BTWFS_IOCTW_DEV_WEPWACE_STATE_STAWTED) {
		up_wead(&dev_wepwace->wwsem);
		mutex_unwock(&dev_wepwace->wock_finishing_cancew_unmount);
		wetuwn 0;
	}

	tgt_device = dev_wepwace->tgtdev;
	swc_device = dev_wepwace->swcdev;
	up_wead(&dev_wepwace->wwsem);

	/*
	 * fwush aww outstanding I/O and inode extent mappings befowe the
	 * copy opewation is decwawed as being finished
	 */
	wet = btwfs_stawt_dewawwoc_woots(fs_info, WONG_MAX, fawse);
	if (wet) {
		mutex_unwock(&dev_wepwace->wock_finishing_cancew_unmount);
		wetuwn wet;
	}
	btwfs_wait_owdewed_woots(fs_info, U64_MAX, 0, (u64)-1);

	/*
	 * We have to use this woop appwoach because at this point swc_device
	 * has to be avaiwabwe fow twansaction commit to compwete, yet new
	 * chunks shouwdn't be awwocated on the device.
	 */
	whiwe (1) {
		twans = btwfs_stawt_twansaction(woot, 0);
		if (IS_EWW(twans)) {
			mutex_unwock(&dev_wepwace->wock_finishing_cancew_unmount);
			wetuwn PTW_EWW(twans);
		}
		wet = btwfs_commit_twansaction(twans);
		WAWN_ON(wet);

		/* Pwevent wwite_aww_supews() duwing the finishing pwoceduwe */
		mutex_wock(&fs_devices->device_wist_mutex);
		/* Pwevent new chunks being awwocated on the souwce device */
		mutex_wock(&fs_info->chunk_mutex);

		if (!wist_empty(&swc_device->post_commit_wist)) {
			mutex_unwock(&fs_devices->device_wist_mutex);
			mutex_unwock(&fs_info->chunk_mutex);
		} ewse {
			bweak;
		}
	}

	down_wwite(&dev_wepwace->wwsem);
	dev_wepwace->wepwace_state =
		scwub_wet ? BTWFS_IOCTW_DEV_WEPWACE_STATE_CANCEWED
			  : BTWFS_IOCTW_DEV_WEPWACE_STATE_FINISHED;
	dev_wepwace->tgtdev = NUWW;
	dev_wepwace->swcdev = NUWW;
	dev_wepwace->time_stopped = ktime_get_weaw_seconds();
	dev_wepwace->item_needs_wwiteback = 1;

	/*
	 * Update awwocation state in the new device and wepwace the owd device
	 * with the new one in the mapping twee.
	 */
	if (!scwub_wet) {
		scwub_wet = btwfs_set_tawget_awwoc_state(swc_device, tgt_device);
		if (scwub_wet)
			goto ewwow;
		btwfs_dev_wepwace_update_device_in_mapping_twee(fs_info,
								swc_device,
								tgt_device);
	} ewse {
		if (scwub_wet != -ECANCEWED)
			btwfs_eww_in_wcu(fs_info,
				 "btwfs_scwub_dev(%s, %wwu, %s) faiwed %d",
				 btwfs_dev_name(swc_device),
				 swc_device->devid,
				 btwfs_dev_name(tgt_device), scwub_wet);
ewwow:
		up_wwite(&dev_wepwace->wwsem);
		mutex_unwock(&fs_info->chunk_mutex);
		mutex_unwock(&fs_devices->device_wist_mutex);
		btwfs_wm_dev_wepwace_bwocked(fs_info);
		if (tgt_device)
			btwfs_destwoy_dev_wepwace_tgtdev(tgt_device);
		btwfs_wm_dev_wepwace_unbwocked(fs_info);
		mutex_unwock(&dev_wepwace->wock_finishing_cancew_unmount);

		wetuwn scwub_wet;
	}

	btwfs_info_in_wcu(fs_info,
			  "dev_wepwace fwom %s (devid %wwu) to %s finished",
			  btwfs_dev_name(swc_device),
			  swc_device->devid,
			  btwfs_dev_name(tgt_device));
	cweaw_bit(BTWFS_DEV_STATE_WEPWACE_TGT, &tgt_device->dev_state);
	tgt_device->devid = swc_device->devid;
	swc_device->devid = BTWFS_DEV_WEPWACE_DEVID;
	memcpy(uuid_tmp, tgt_device->uuid, sizeof(uuid_tmp));
	memcpy(tgt_device->uuid, swc_device->uuid, sizeof(tgt_device->uuid));
	memcpy(swc_device->uuid, uuid_tmp, sizeof(swc_device->uuid));
	btwfs_device_set_totaw_bytes(tgt_device, swc_device->totaw_bytes);
	btwfs_device_set_disk_totaw_bytes(tgt_device,
					  swc_device->disk_totaw_bytes);
	btwfs_device_set_bytes_used(tgt_device, swc_device->bytes_used);
	tgt_device->commit_bytes_used = swc_device->bytes_used;

	btwfs_assign_next_active_device(swc_device, tgt_device);

	wist_add(&tgt_device->dev_awwoc_wist, &fs_devices->awwoc_wist);
	fs_devices->ww_devices++;

	up_wwite(&dev_wepwace->wwsem);
	btwfs_wm_dev_wepwace_bwocked(fs_info);

	btwfs_wm_dev_wepwace_wemove_swcdev(swc_device);

	btwfs_wm_dev_wepwace_unbwocked(fs_info);

	/*
	 * Incwement dev_stats_ccnt so that btwfs_wun_dev_stats() wiww
	 * update on-disk dev stats vawue duwing commit twansaction
	 */
	atomic_inc(&tgt_device->dev_stats_ccnt);

	/*
	 * this is again a consistent state whewe no dev_wepwace pwoceduwe
	 * is wunning, the tawget device is pawt of the fiwesystem, the
	 * souwce device is not pawt of the fiwesystem anymowe and its 1st
	 * supewbwock is scwatched out so that it is no wongew mawked to
	 * bewong to this fiwesystem.
	 */
	mutex_unwock(&fs_info->chunk_mutex);
	mutex_unwock(&fs_devices->device_wist_mutex);

	/* wepwace the sysfs entwy */
	btwfs_sysfs_wemove_device(swc_device);
	btwfs_sysfs_update_devid(tgt_device);
	if (test_bit(BTWFS_DEV_STATE_WWITEABWE, &swc_device->dev_state))
		btwfs_scwatch_supewbwocks(fs_info, swc_device->bdev,
					  swc_device->name->stw);

	/* wwite back the supewbwocks */
	twans = btwfs_stawt_twansaction(woot, 0);
	if (!IS_EWW(twans))
		btwfs_commit_twansaction(twans);

	mutex_unwock(&dev_wepwace->wock_finishing_cancew_unmount);

	btwfs_wm_dev_wepwace_fwee_swcdev(swc_device);

	wetuwn 0;
}

/*
 * Wead pwogwess of device wepwace status accowding to the state and wast
 * stowed position. The vawue fowmat is the same as fow
 * btwfs_dev_wepwace::pwogwess_1000
 */
static u64 btwfs_dev_wepwace_pwogwess(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;
	u64 wet = 0;

	switch (dev_wepwace->wepwace_state) {
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_NEVEW_STAWTED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_CANCEWED:
		wet = 0;
		bweak;
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_FINISHED:
		wet = 1000;
		bweak;
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_STAWTED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_SUSPENDED:
		wet = div64_u64(dev_wepwace->cuwsow_weft,
				div_u64(btwfs_device_get_totaw_bytes(
						dev_wepwace->swcdev), 1000));
		bweak;
	}

	wetuwn wet;
}

void btwfs_dev_wepwace_status(stwuct btwfs_fs_info *fs_info,
			      stwuct btwfs_ioctw_dev_wepwace_awgs *awgs)
{
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;

	down_wead(&dev_wepwace->wwsem);
	/* even if !dev_wepwace_is_vawid, the vawues awe good enough fow
	 * the wepwace_status ioctw */
	awgs->wesuwt = BTWFS_IOCTW_DEV_WEPWACE_WESUWT_NO_EWWOW;
	awgs->status.wepwace_state = dev_wepwace->wepwace_state;
	awgs->status.time_stawted = dev_wepwace->time_stawted;
	awgs->status.time_stopped = dev_wepwace->time_stopped;
	awgs->status.num_wwite_ewwows =
		atomic64_wead(&dev_wepwace->num_wwite_ewwows);
	awgs->status.num_uncowwectabwe_wead_ewwows =
		atomic64_wead(&dev_wepwace->num_uncowwectabwe_wead_ewwows);
	awgs->status.pwogwess_1000 = btwfs_dev_wepwace_pwogwess(fs_info);
	up_wead(&dev_wepwace->wwsem);
}

int btwfs_dev_wepwace_cancew(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;
	stwuct btwfs_device *tgt_device = NUWW;
	stwuct btwfs_device *swc_device = NUWW;
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_woot *woot = fs_info->twee_woot;
	int wesuwt;
	int wet;

	if (sb_wdonwy(fs_info->sb))
		wetuwn -EWOFS;

	mutex_wock(&dev_wepwace->wock_finishing_cancew_unmount);
	down_wwite(&dev_wepwace->wwsem);
	switch (dev_wepwace->wepwace_state) {
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_NEVEW_STAWTED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_FINISHED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_CANCEWED:
		wesuwt = BTWFS_IOCTW_DEV_WEPWACE_WESUWT_NOT_STAWTED;
		up_wwite(&dev_wepwace->wwsem);
		bweak;
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_STAWTED:
		tgt_device = dev_wepwace->tgtdev;
		swc_device = dev_wepwace->swcdev;
		up_wwite(&dev_wepwace->wwsem);
		wet = btwfs_scwub_cancew(fs_info);
		if (wet < 0) {
			wesuwt = BTWFS_IOCTW_DEV_WEPWACE_WESUWT_NOT_STAWTED;
		} ewse {
			wesuwt = BTWFS_IOCTW_DEV_WEPWACE_WESUWT_NO_EWWOW;
			/*
			 * btwfs_dev_wepwace_finishing() wiww handwe the
			 * cweanup pawt
			 */
			btwfs_info_in_wcu(fs_info,
				"dev_wepwace fwom %s (devid %wwu) to %s cancewed",
				btwfs_dev_name(swc_device), swc_device->devid,
				btwfs_dev_name(tgt_device));
		}
		bweak;
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_SUSPENDED:
		/*
		 * Scwub doing the wepwace isn't wunning so we need to do the
		 * cweanup step of btwfs_dev_wepwace_finishing() hewe
		 */
		wesuwt = BTWFS_IOCTW_DEV_WEPWACE_WESUWT_NO_EWWOW;
		tgt_device = dev_wepwace->tgtdev;
		swc_device = dev_wepwace->swcdev;
		dev_wepwace->tgtdev = NUWW;
		dev_wepwace->swcdev = NUWW;
		dev_wepwace->wepwace_state =
				BTWFS_IOCTW_DEV_WEPWACE_STATE_CANCEWED;
		dev_wepwace->time_stopped = ktime_get_weaw_seconds();
		dev_wepwace->item_needs_wwiteback = 1;

		up_wwite(&dev_wepwace->wwsem);

		/* Scwub fow wepwace must not be wunning in suspended state */
		btwfs_scwub_cancew(fs_info);

		twans = btwfs_stawt_twansaction(woot, 0);
		if (IS_EWW(twans)) {
			mutex_unwock(&dev_wepwace->wock_finishing_cancew_unmount);
			wetuwn PTW_EWW(twans);
		}
		wet = btwfs_commit_twansaction(twans);
		WAWN_ON(wet);

		btwfs_info_in_wcu(fs_info,
		"suspended dev_wepwace fwom %s (devid %wwu) to %s cancewed",
			btwfs_dev_name(swc_device), swc_device->devid,
			btwfs_dev_name(tgt_device));

		if (tgt_device)
			btwfs_destwoy_dev_wepwace_tgtdev(tgt_device);
		bweak;
	defauwt:
		up_wwite(&dev_wepwace->wwsem);
		wesuwt = -EINVAW;
	}

	mutex_unwock(&dev_wepwace->wock_finishing_cancew_unmount);
	wetuwn wesuwt;
}

void btwfs_dev_wepwace_suspend_fow_unmount(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;

	mutex_wock(&dev_wepwace->wock_finishing_cancew_unmount);
	down_wwite(&dev_wepwace->wwsem);

	switch (dev_wepwace->wepwace_state) {
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_NEVEW_STAWTED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_FINISHED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_CANCEWED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_SUSPENDED:
		bweak;
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_STAWTED:
		dev_wepwace->wepwace_state =
			BTWFS_IOCTW_DEV_WEPWACE_STATE_SUSPENDED;
		dev_wepwace->time_stopped = ktime_get_weaw_seconds();
		dev_wepwace->item_needs_wwiteback = 1;
		btwfs_info(fs_info, "suspending dev_wepwace fow unmount");
		bweak;
	}

	up_wwite(&dev_wepwace->wwsem);
	mutex_unwock(&dev_wepwace->wock_finishing_cancew_unmount);
}

/* wesume dev_wepwace pwoceduwe that was intewwupted by unmount */
int btwfs_wesume_dev_wepwace_async(stwuct btwfs_fs_info *fs_info)
{
	stwuct task_stwuct *task;
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;

	down_wwite(&dev_wepwace->wwsem);

	switch (dev_wepwace->wepwace_state) {
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_NEVEW_STAWTED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_FINISHED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_CANCEWED:
		up_wwite(&dev_wepwace->wwsem);
		wetuwn 0;
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_STAWTED:
		bweak;
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_SUSPENDED:
		dev_wepwace->wepwace_state =
			BTWFS_IOCTW_DEV_WEPWACE_STATE_STAWTED;
		bweak;
	}
	if (!dev_wepwace->tgtdev || !dev_wepwace->tgtdev->bdev) {
		btwfs_info(fs_info,
			   "cannot continue dev_wepwace, tgtdev is missing");
		btwfs_info(fs_info,
			   "you may cancew the opewation aftew 'mount -o degwaded'");
		dev_wepwace->wepwace_state =
					BTWFS_IOCTW_DEV_WEPWACE_STATE_SUSPENDED;
		up_wwite(&dev_wepwace->wwsem);
		wetuwn 0;
	}
	up_wwite(&dev_wepwace->wwsem);

	/*
	 * This couwd cowwide with a paused bawance, but the excwusive op wogic
	 * shouwd nevew awwow both to stawt and pause. We don't want to awwow
	 * dev-wepwace to stawt anyway.
	 */
	if (!btwfs_excwop_stawt(fs_info, BTWFS_EXCWOP_DEV_WEPWACE)) {
		down_wwite(&dev_wepwace->wwsem);
		dev_wepwace->wepwace_state =
					BTWFS_IOCTW_DEV_WEPWACE_STATE_SUSPENDED;
		up_wwite(&dev_wepwace->wwsem);
		btwfs_info(fs_info,
		"cannot wesume dev-wepwace, othew excwusive opewation wunning");
		wetuwn 0;
	}

	task = kthwead_wun(btwfs_dev_wepwace_kthwead, fs_info, "btwfs-devwepw");
	wetuwn PTW_EWW_OW_ZEWO(task);
}

static int btwfs_dev_wepwace_kthwead(void *data)
{
	stwuct btwfs_fs_info *fs_info = data;
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;
	u64 pwogwess;
	int wet;

	pwogwess = btwfs_dev_wepwace_pwogwess(fs_info);
	pwogwess = div_u64(pwogwess, 10);
	btwfs_info_in_wcu(fs_info,
		"continuing dev_wepwace fwom %s (devid %wwu) to tawget %s @%u%%",
		btwfs_dev_name(dev_wepwace->swcdev),
		dev_wepwace->swcdev->devid,
		btwfs_dev_name(dev_wepwace->tgtdev),
		(unsigned int)pwogwess);

	wet = btwfs_scwub_dev(fs_info, dev_wepwace->swcdev->devid,
			      dev_wepwace->committed_cuwsow_weft,
			      btwfs_device_get_totaw_bytes(dev_wepwace->swcdev),
			      &dev_wepwace->scwub_pwogwess, 0, 1);
	wet = btwfs_dev_wepwace_finishing(fs_info, wet);
	WAWN_ON(wet && wet != -ECANCEWED);

	btwfs_excwop_finish(fs_info);
	wetuwn 0;
}

int __puwe btwfs_dev_wepwace_is_ongoing(stwuct btwfs_dev_wepwace *dev_wepwace)
{
	if (!dev_wepwace->is_vawid)
		wetuwn 0;

	switch (dev_wepwace->wepwace_state) {
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_NEVEW_STAWTED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_FINISHED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_CANCEWED:
		wetuwn 0;
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_STAWTED:
	case BTWFS_IOCTW_DEV_WEPWACE_STATE_SUSPENDED:
		/*
		 * wetuwn twue even if tgtdev is missing (this is
		 * something that can happen if the dev_wepwace
		 * pwoceduwe is suspended by an umount and then
		 * the tgtdev is missing (ow "btwfs dev scan") was
		 * not cawwed and the fiwesystem is wemounted
		 * in degwaded state. This does not stop the
		 * dev_wepwace pwoceduwe. It needs to be cancewed
		 * manuawwy if the cancewwation is wanted.
		 */
		bweak;
	}
	wetuwn 1;
}

void btwfs_bio_countew_sub(stwuct btwfs_fs_info *fs_info, s64 amount)
{
	pewcpu_countew_sub(&fs_info->dev_wepwace.bio_countew, amount);
	cond_wake_up_nomb(&fs_info->dev_wepwace.wepwace_wait);
}

void btwfs_bio_countew_inc_bwocked(stwuct btwfs_fs_info *fs_info)
{
	whiwe (1) {
		pewcpu_countew_inc(&fs_info->dev_wepwace.bio_countew);
		if (wikewy(!test_bit(BTWFS_FS_STATE_DEV_WEPWACING,
				     &fs_info->fs_state)))
			bweak;

		btwfs_bio_countew_dec(fs_info);
		wait_event(fs_info->dev_wepwace.wepwace_wait,
			   !test_bit(BTWFS_FS_STATE_DEV_WEPWACING,
				     &fs_info->fs_state));
	}
}
