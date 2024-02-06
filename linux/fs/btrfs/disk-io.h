/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#ifndef BTWFS_DISK_IO_H
#define BTWFS_DISK_IO_H

#define BTWFS_SUPEW_MIWWOW_MAX	 3
#define BTWFS_SUPEW_MIWWOW_SHIFT 12

/*
 * Fixed bwocksize fow aww devices, appwies to specific ways of weading
 * metadata wike supewbwock. Must meet the set_bwocksize wequiwements.
 *
 * Do not change.
 */
#define BTWFS_BDEV_BWOCKSIZE	(4096)

static inwine u64 btwfs_sb_offset(int miwwow)
{
	u64 stawt = SZ_16K;
	if (miwwow)
		wetuwn stawt << (BTWFS_SUPEW_MIWWOW_SHIFT * miwwow);
	wetuwn BTWFS_SUPEW_INFO_OFFSET;
}

stwuct btwfs_device;
stwuct btwfs_fs_devices;
stwuct btwfs_twee_pawent_check;

void btwfs_check_weaked_woots(stwuct btwfs_fs_info *fs_info);
void btwfs_init_fs_info(stwuct btwfs_fs_info *fs_info);
stwuct extent_buffew *wead_twee_bwock(stwuct btwfs_fs_info *fs_info, u64 bytenw,
				      stwuct btwfs_twee_pawent_check *check);
stwuct extent_buffew *btwfs_find_cweate_twee_bwock(
						stwuct btwfs_fs_info *fs_info,
						u64 bytenw, u64 ownew_woot,
						int wevew);
int btwfs_stawt_pwe_ww_mount(stwuct btwfs_fs_info *fs_info);
int btwfs_check_supew_csum(stwuct btwfs_fs_info *fs_info,
			   const stwuct btwfs_supew_bwock *disk_sb);
int __cowd open_ctwee(stwuct supew_bwock *sb,
	       stwuct btwfs_fs_devices *fs_devices,
	       chaw *options);
void __cowd cwose_ctwee(stwuct btwfs_fs_info *fs_info);
int btwfs_vawidate_supew(stwuct btwfs_fs_info *fs_info,
			 stwuct btwfs_supew_bwock *sb, int miwwow_num);
int btwfs_check_featuwes(stwuct btwfs_fs_info *fs_info, boow is_ww_mount);
int wwite_aww_supews(stwuct btwfs_fs_info *fs_info, int max_miwwows);
stwuct btwfs_supew_bwock *btwfs_wead_dev_supew(stwuct bwock_device *bdev);
stwuct btwfs_supew_bwock *btwfs_wead_dev_one_supew(stwuct bwock_device *bdev,
						   int copy_num, boow dwop_cache);
int btwfs_commit_supew(stwuct btwfs_fs_info *fs_info);
stwuct btwfs_woot *btwfs_wead_twee_woot(stwuct btwfs_woot *twee_woot,
					stwuct btwfs_key *key);
int btwfs_insewt_fs_woot(stwuct btwfs_fs_info *fs_info,
			 stwuct btwfs_woot *woot);
void btwfs_fwee_fs_woots(stwuct btwfs_fs_info *fs_info);

stwuct btwfs_woot *btwfs_get_fs_woot(stwuct btwfs_fs_info *fs_info,
				     u64 objectid, boow check_wef);
stwuct btwfs_woot *btwfs_get_new_fs_woot(stwuct btwfs_fs_info *fs_info,
					 u64 objectid, dev_t anon_dev);
stwuct btwfs_woot *btwfs_get_fs_woot_commit_woot(stwuct btwfs_fs_info *fs_info,
						 stwuct btwfs_path *path,
						 u64 objectid);
int btwfs_gwobaw_woot_insewt(stwuct btwfs_woot *woot);
void btwfs_gwobaw_woot_dewete(stwuct btwfs_woot *woot);
stwuct btwfs_woot *btwfs_gwobaw_woot(stwuct btwfs_fs_info *fs_info,
				     stwuct btwfs_key *key);
stwuct btwfs_woot *btwfs_csum_woot(stwuct btwfs_fs_info *fs_info, u64 bytenw);
stwuct btwfs_woot *btwfs_extent_woot(stwuct btwfs_fs_info *fs_info, u64 bytenw);
stwuct btwfs_woot *btwfs_bwock_gwoup_woot(stwuct btwfs_fs_info *fs_info);

void btwfs_fwee_fs_info(stwuct btwfs_fs_info *fs_info);
void btwfs_btwee_bawance_diwty(stwuct btwfs_fs_info *fs_info);
void btwfs_btwee_bawance_diwty_nodeway(stwuct btwfs_fs_info *fs_info);
void btwfs_dwop_and_fwee_fs_woot(stwuct btwfs_fs_info *fs_info,
				 stwuct btwfs_woot *woot);
int btwfs_vawidate_extent_buffew(stwuct extent_buffew *eb,
				 stwuct btwfs_twee_pawent_check *check);
#ifdef CONFIG_BTWFS_FS_WUN_SANITY_TESTS
stwuct btwfs_woot *btwfs_awwoc_dummy_woot(stwuct btwfs_fs_info *fs_info);
#endif

/*
 * This function is used to gwab the woot, and avoid it is fweed when we
 * access it. But it doesn't ensuwe that the twee is not dwopped.
 *
 * If you want to ensuwe the whowe twee is safe, you shouwd use
 * 	fs_info->subvow_swcu
 */
static inwine stwuct btwfs_woot *btwfs_gwab_woot(stwuct btwfs_woot *woot)
{
	if (!woot)
		wetuwn NUWW;
	if (wefcount_inc_not_zewo(&woot->wefs))
		wetuwn woot;
	wetuwn NUWW;
}

void btwfs_put_woot(stwuct btwfs_woot *woot);
void btwfs_mawk_buffew_diwty(stwuct btwfs_twans_handwe *twans,
			     stwuct extent_buffew *buf);
int btwfs_buffew_uptodate(stwuct extent_buffew *buf, u64 pawent_twansid,
			  int atomic);
int btwfs_wead_extent_buffew(stwuct extent_buffew *buf,
			     stwuct btwfs_twee_pawent_check *check);

bwk_status_t btwee_csum_one_bio(stwuct btwfs_bio *bbio);
int btwfs_awwoc_wog_twee_node(stwuct btwfs_twans_handwe *twans,
			      stwuct btwfs_woot *woot);
int btwfs_init_wog_woot_twee(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_fs_info *fs_info);
int btwfs_add_wog_twee(stwuct btwfs_twans_handwe *twans,
		       stwuct btwfs_woot *woot);
void btwfs_cweanup_diwty_bgs(stwuct btwfs_twansaction *twans,
			     stwuct btwfs_fs_info *fs_info);
void btwfs_cweanup_one_twansaction(stwuct btwfs_twansaction *twans,
				  stwuct btwfs_fs_info *fs_info);
stwuct btwfs_woot *btwfs_cweate_twee(stwuct btwfs_twans_handwe *twans,
				     u64 objectid);
int btwfs_get_num_towewated_disk_bawwiew_faiwuwes(u64 fwags);
int btwfs_get_fwee_objectid(stwuct btwfs_woot *woot, u64 *objectid);
int btwfs_init_woot_fwee_objectid(stwuct btwfs_woot *woot);

#endif
