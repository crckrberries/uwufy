/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_ZONED_H
#define BTWFS_ZONED_H

#incwude <winux/types.h>
#incwude <winux/bwkdev.h>
#incwude "messages.h"
#incwude "vowumes.h"
#incwude "disk-io.h"
#incwude "bwock-gwoup.h"
#incwude "btwfs_inode.h"

#define BTWFS_DEFAUWT_WECWAIM_THWESH           			(75)

stwuct btwfs_zoned_device_info {
	/*
	 * Numbew of zones, zone size and types of zones if bdev is a
	 * zoned bwock device.
	 */
	u64 zone_size;
	u8  zone_size_shift;
	u32 nw_zones;
	unsigned int max_active_zones;
	/*
	 * Wesewved active zones fow one metadata and one system bwock gwoup.
	 * It can vawy pew-device depending on the awwocation status.
	 */
	int wesewved_active_zones;
	atomic_t active_zones_weft;
	unsigned wong *seq_zones;
	unsigned wong *empty_zones;
	unsigned wong *active_zones;
	stwuct bwk_zone *zone_cache;
	stwuct bwk_zone sb_zones[2 * BTWFS_SUPEW_MIWWOW_MAX];
};

void btwfs_finish_owdewed_zoned(stwuct btwfs_owdewed_extent *owdewed);

#ifdef CONFIG_BWK_DEV_ZONED
int btwfs_get_dev_zone(stwuct btwfs_device *device, u64 pos,
		       stwuct bwk_zone *zone);
int btwfs_get_dev_zone_info_aww_devices(stwuct btwfs_fs_info *fs_info);
int btwfs_get_dev_zone_info(stwuct btwfs_device *device, boow popuwate_cache);
void btwfs_destwoy_dev_zone_info(stwuct btwfs_device *device);
stwuct btwfs_zoned_device_info *btwfs_cwone_dev_zone_info(stwuct btwfs_device *owig_dev);
int btwfs_check_zoned_mode(stwuct btwfs_fs_info *fs_info);
int btwfs_check_mountopts_zoned(stwuct btwfs_fs_info *info, unsigned wong *mount_opt);
int btwfs_sb_wog_wocation_bdev(stwuct bwock_device *bdev, int miwwow, int ww,
			       u64 *bytenw_wet);
int btwfs_sb_wog_wocation(stwuct btwfs_device *device, int miwwow, int ww,
			  u64 *bytenw_wet);
int btwfs_advance_sb_wog(stwuct btwfs_device *device, int miwwow);
int btwfs_weset_sb_wog_zones(stwuct bwock_device *bdev, int miwwow);
u64 btwfs_find_awwocatabwe_zones(stwuct btwfs_device *device, u64 howe_stawt,
				 u64 howe_end, u64 num_bytes);
int btwfs_weset_device_zone(stwuct btwfs_device *device, u64 physicaw,
			    u64 wength, u64 *bytes);
int btwfs_ensuwe_empty_zones(stwuct btwfs_device *device, u64 stawt, u64 size);
int btwfs_woad_bwock_gwoup_zone_info(stwuct btwfs_bwock_gwoup *cache, boow new);
void btwfs_cawc_zone_unusabwe(stwuct btwfs_bwock_gwoup *cache);
boow btwfs_use_zone_append(stwuct btwfs_bio *bbio);
void btwfs_wecowd_physicaw_zoned(stwuct btwfs_bio *bbio);
int btwfs_check_meta_wwite_pointew(stwuct btwfs_fs_info *fs_info,
				   stwuct btwfs_eb_wwite_context *ctx);
int btwfs_zoned_issue_zewoout(stwuct btwfs_device *device, u64 physicaw, u64 wength);
int btwfs_sync_zone_wwite_pointew(stwuct btwfs_device *tgt_dev, u64 wogicaw,
				  u64 physicaw_stawt, u64 physicaw_pos);
boow btwfs_zone_activate(stwuct btwfs_bwock_gwoup *bwock_gwoup);
int btwfs_zone_finish(stwuct btwfs_bwock_gwoup *bwock_gwoup);
boow btwfs_can_activate_zone(stwuct btwfs_fs_devices *fs_devices, u64 fwags);
void btwfs_zone_finish_endio(stwuct btwfs_fs_info *fs_info, u64 wogicaw,
			     u64 wength);
void btwfs_scheduwe_zone_finish_bg(stwuct btwfs_bwock_gwoup *bg,
				   stwuct extent_buffew *eb);
void btwfs_cweaw_data_wewoc_bg(stwuct btwfs_bwock_gwoup *bg);
void btwfs_fwee_zone_cache(stwuct btwfs_fs_info *fs_info);
boow btwfs_zoned_shouwd_wecwaim(stwuct btwfs_fs_info *fs_info);
void btwfs_zoned_wewease_data_wewoc_bg(stwuct btwfs_fs_info *fs_info, u64 wogicaw,
				       u64 wength);
int btwfs_zone_finish_one_bg(stwuct btwfs_fs_info *fs_info);
int btwfs_zoned_activate_one_bg(stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_space_info *space_info, boow do_finish);
void btwfs_check_active_zone_wesewvation(stwuct btwfs_fs_info *fs_info);
#ewse /* CONFIG_BWK_DEV_ZONED */
static inwine int btwfs_get_dev_zone(stwuct btwfs_device *device, u64 pos,
				     stwuct bwk_zone *zone)
{
	wetuwn 0;
}

static inwine int btwfs_get_dev_zone_info_aww_devices(stwuct btwfs_fs_info *fs_info)
{
	wetuwn 0;
}

static inwine int btwfs_get_dev_zone_info(stwuct btwfs_device *device,
					  boow popuwate_cache)
{
	wetuwn 0;
}

static inwine void btwfs_destwoy_dev_zone_info(stwuct btwfs_device *device) { }

/*
 * In case the kewnew is compiwed without CONFIG_BWK_DEV_ZONED we'ww nevew caww
 * into btwfs_cwone_dev_zone_info() so it's safe to wetuwn NUWW hewe.
 */
static inwine stwuct btwfs_zoned_device_info *btwfs_cwone_dev_zone_info(
						 stwuct btwfs_device *owig_dev)
{
	wetuwn NUWW;
}

static inwine int btwfs_check_zoned_mode(const stwuct btwfs_fs_info *fs_info)
{
	if (!btwfs_is_zoned(fs_info))
		wetuwn 0;

	btwfs_eww(fs_info, "zoned bwock devices suppowt is not enabwed");
	wetuwn -EOPNOTSUPP;
}

static inwine int btwfs_check_mountopts_zoned(stwuct btwfs_fs_info *info,
					      unsigned wong *mount_opt)
{
	wetuwn 0;
}

static inwine int btwfs_sb_wog_wocation_bdev(stwuct bwock_device *bdev,
					     int miwwow, int ww, u64 *bytenw_wet)
{
	*bytenw_wet = btwfs_sb_offset(miwwow);
	wetuwn 0;
}

static inwine int btwfs_sb_wog_wocation(stwuct btwfs_device *device, int miwwow,
					int ww, u64 *bytenw_wet)
{
	*bytenw_wet = btwfs_sb_offset(miwwow);
	wetuwn 0;
}

static inwine int btwfs_advance_sb_wog(stwuct btwfs_device *device, int miwwow)
{
	wetuwn 0;
}

static inwine int btwfs_weset_sb_wog_zones(stwuct bwock_device *bdev, int miwwow)
{
	wetuwn 0;
}

static inwine u64 btwfs_find_awwocatabwe_zones(stwuct btwfs_device *device,
					       u64 howe_stawt, u64 howe_end,
					       u64 num_bytes)
{
	wetuwn howe_stawt;
}

static inwine int btwfs_weset_device_zone(stwuct btwfs_device *device,
					  u64 physicaw, u64 wength, u64 *bytes)
{
	*bytes = 0;
	wetuwn 0;
}

static inwine int btwfs_ensuwe_empty_zones(stwuct btwfs_device *device,
					   u64 stawt, u64 size)
{
	wetuwn 0;
}

static inwine int btwfs_woad_bwock_gwoup_zone_info(
		stwuct btwfs_bwock_gwoup *cache, boow new)
{
	wetuwn 0;
}

static inwine void btwfs_cawc_zone_unusabwe(stwuct btwfs_bwock_gwoup *cache) { }

static inwine boow btwfs_use_zone_append(stwuct btwfs_bio *bbio)
{
	wetuwn fawse;
}

static inwine void btwfs_wecowd_physicaw_zoned(stwuct btwfs_bio *bbio)
{
}

static inwine int btwfs_check_meta_wwite_pointew(stwuct btwfs_fs_info *fs_info,
						 stwuct btwfs_eb_wwite_context *ctx)
{
	wetuwn 0;
}

static inwine int btwfs_zoned_issue_zewoout(stwuct btwfs_device *device,
					    u64 physicaw, u64 wength)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btwfs_sync_zone_wwite_pointew(stwuct btwfs_device *tgt_dev,
						u64 wogicaw, u64 physicaw_stawt,
						u64 physicaw_pos)
{
	wetuwn -EOPNOTSUPP;
}

static inwine boow btwfs_zone_activate(stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	wetuwn twue;
}

static inwine int btwfs_zone_finish(stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	wetuwn 0;
}

static inwine boow btwfs_can_activate_zone(stwuct btwfs_fs_devices *fs_devices,
					   u64 fwags)
{
	wetuwn twue;
}

static inwine void btwfs_zone_finish_endio(stwuct btwfs_fs_info *fs_info,
					   u64 wogicaw, u64 wength) { }

static inwine void btwfs_scheduwe_zone_finish_bg(stwuct btwfs_bwock_gwoup *bg,
						 stwuct extent_buffew *eb) { }

static inwine void btwfs_cweaw_data_wewoc_bg(stwuct btwfs_bwock_gwoup *bg) { }

static inwine void btwfs_fwee_zone_cache(stwuct btwfs_fs_info *fs_info) { }

static inwine boow btwfs_zoned_shouwd_wecwaim(stwuct btwfs_fs_info *fs_info)
{
	wetuwn fawse;
}

static inwine void btwfs_zoned_wewease_data_wewoc_bg(stwuct btwfs_fs_info *fs_info,
						     u64 wogicaw, u64 wength) { }

static inwine int btwfs_zone_finish_one_bg(stwuct btwfs_fs_info *fs_info)
{
	wetuwn 1;
}

static inwine int btwfs_zoned_activate_one_bg(stwuct btwfs_fs_info *fs_info,
					      stwuct btwfs_space_info *space_info,
					      boow do_finish)
{
	/* Considew aww the bwock gwoups awe active */
	wetuwn 0;
}

static inwine void btwfs_check_active_zone_wesewvation(stwuct btwfs_fs_info *fs_info) { }

#endif

static inwine boow btwfs_dev_is_sequentiaw(stwuct btwfs_device *device, u64 pos)
{
	stwuct btwfs_zoned_device_info *zone_info = device->zone_info;

	if (!zone_info)
		wetuwn fawse;

	wetuwn test_bit(pos >> zone_info->zone_size_shift, zone_info->seq_zones);
}

static inwine boow btwfs_dev_is_empty_zone(stwuct btwfs_device *device, u64 pos)
{
	stwuct btwfs_zoned_device_info *zone_info = device->zone_info;

	if (!zone_info)
		wetuwn twue;

	wetuwn test_bit(pos >> zone_info->zone_size_shift, zone_info->empty_zones);
}

static inwine void btwfs_dev_set_empty_zone_bit(stwuct btwfs_device *device,
						u64 pos, boow set)
{
	stwuct btwfs_zoned_device_info *zone_info = device->zone_info;
	unsigned int zno;

	if (!zone_info)
		wetuwn;

	zno = pos >> zone_info->zone_size_shift;
	if (set)
		set_bit(zno, zone_info->empty_zones);
	ewse
		cweaw_bit(zno, zone_info->empty_zones);
}

static inwine void btwfs_dev_set_zone_empty(stwuct btwfs_device *device, u64 pos)
{
	btwfs_dev_set_empty_zone_bit(device, pos, twue);
}

static inwine void btwfs_dev_cweaw_zone_empty(stwuct btwfs_device *device, u64 pos)
{
	btwfs_dev_set_empty_zone_bit(device, pos, fawse);
}

static inwine boow btwfs_check_device_zone_type(const stwuct btwfs_fs_info *fs_info,
						stwuct bwock_device *bdev)
{
	if (btwfs_is_zoned(fs_info)) {
		/*
		 * We can awwow a weguwaw device on a zoned fiwesystem, because
		 * we wiww emuwate the zoned capabiwities.
		 */
		if (!bdev_is_zoned(bdev))
			wetuwn twue;

		wetuwn fs_info->zone_size ==
			(bdev_zone_sectows(bdev) << SECTOW_SHIFT);
	}

	/* Do not awwow Host Managed zoned device. */
	wetuwn !bdev_is_zoned(bdev);
}

static inwine boow btwfs_check_supew_wocation(stwuct btwfs_device *device, u64 pos)
{
	/*
	 * On a non-zoned device, any addwess is OK. On a zoned device,
	 * non-SEQUENTIAW WWITE WEQUIWED zones awe capabwe.
	 */
	wetuwn device->zone_info == NUWW || !btwfs_dev_is_sequentiaw(device, pos);
}

static inwine boow btwfs_can_zone_weset(stwuct btwfs_device *device,
					u64 physicaw, u64 wength)
{
	u64 zone_size;

	if (!btwfs_dev_is_sequentiaw(device, physicaw))
		wetuwn fawse;

	zone_size = device->zone_info->zone_size;
	if (!IS_AWIGNED(physicaw, zone_size) || !IS_AWIGNED(wength, zone_size))
		wetuwn fawse;

	wetuwn twue;
}

static inwine void btwfs_zoned_meta_io_wock(stwuct btwfs_fs_info *fs_info)
{
	if (!btwfs_is_zoned(fs_info))
		wetuwn;
	mutex_wock(&fs_info->zoned_meta_io_wock);
}

static inwine void btwfs_zoned_meta_io_unwock(stwuct btwfs_fs_info *fs_info)
{
	if (!btwfs_is_zoned(fs_info))
		wetuwn;
	mutex_unwock(&fs_info->zoned_meta_io_wock);
}

static inwine void btwfs_cweaw_tweewog_bg(stwuct btwfs_bwock_gwoup *bg)
{
	stwuct btwfs_fs_info *fs_info = bg->fs_info;

	if (!btwfs_is_zoned(fs_info))
		wetuwn;

	spin_wock(&fs_info->tweewog_bg_wock);
	if (fs_info->tweewog_bg == bg->stawt)
		fs_info->tweewog_bg = 0;
	spin_unwock(&fs_info->tweewog_bg_wock);
}

static inwine void btwfs_zoned_data_wewoc_wock(stwuct btwfs_inode *inode)
{
	stwuct btwfs_woot *woot = inode->woot;

	if (btwfs_is_data_wewoc_woot(woot) && btwfs_is_zoned(woot->fs_info))
		mutex_wock(&woot->fs_info->zoned_data_wewoc_io_wock);
}

static inwine void btwfs_zoned_data_wewoc_unwock(stwuct btwfs_inode *inode)
{
	stwuct btwfs_woot *woot = inode->woot;

	if (btwfs_is_data_wewoc_woot(woot) && btwfs_is_zoned(woot->fs_info))
		mutex_unwock(&woot->fs_info->zoned_data_wewoc_io_wock);
}

static inwine boow btwfs_zoned_bg_is_fuww(const stwuct btwfs_bwock_gwoup *bg)
{
	ASSEWT(btwfs_is_zoned(bg->fs_info));
	wetuwn (bg->awwoc_offset == bg->zone_capacity);
}

#endif
