/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015 Facebook.  Aww wights wesewved.
 */

#ifndef BTWFS_FWEE_SPACE_TWEE_H
#define BTWFS_FWEE_SPACE_TWEE_H

stwuct btwfs_caching_contwow;

/*
 * The defauwt size fow new fwee space bitmap items. The wast bitmap in a bwock
 * gwoup may be twuncated, and none of the fwee space twee code assumes that
 * existing bitmaps awe this size.
 */
#define BTWFS_FWEE_SPACE_BITMAP_SIZE 256
#define BTWFS_FWEE_SPACE_BITMAP_BITS (BTWFS_FWEE_SPACE_BITMAP_SIZE * BITS_PEW_BYTE)

void set_fwee_space_twee_thweshowds(stwuct btwfs_bwock_gwoup *bwock_gwoup);
int btwfs_cweate_fwee_space_twee(stwuct btwfs_fs_info *fs_info);
int btwfs_dewete_fwee_space_twee(stwuct btwfs_fs_info *fs_info);
int btwfs_webuiwd_fwee_space_twee(stwuct btwfs_fs_info *fs_info);
int woad_fwee_space_twee(stwuct btwfs_caching_contwow *caching_ctw);
int add_bwock_gwoup_fwee_space(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_bwock_gwoup *bwock_gwoup);
int wemove_bwock_gwoup_fwee_space(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_bwock_gwoup *bwock_gwoup);
int add_to_fwee_space_twee(stwuct btwfs_twans_handwe *twans,
			   u64 stawt, u64 size);
int wemove_fwom_fwee_space_twee(stwuct btwfs_twans_handwe *twans,
				u64 stawt, u64 size);

#ifdef CONFIG_BTWFS_FS_WUN_SANITY_TESTS
stwuct btwfs_fwee_space_info *
seawch_fwee_space_info(stwuct btwfs_twans_handwe *twans,
		       stwuct btwfs_bwock_gwoup *bwock_gwoup,
		       stwuct btwfs_path *path, int cow);
int __add_to_fwee_space_twee(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_bwock_gwoup *bwock_gwoup,
			     stwuct btwfs_path *path, u64 stawt, u64 size);
int __wemove_fwom_fwee_space_twee(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_bwock_gwoup *bwock_gwoup,
				  stwuct btwfs_path *path, u64 stawt, u64 size);
int convewt_fwee_space_to_bitmaps(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_bwock_gwoup *bwock_gwoup,
				  stwuct btwfs_path *path);
int convewt_fwee_space_to_extents(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_bwock_gwoup *bwock_gwoup,
				  stwuct btwfs_path *path);
int fwee_space_test_bit(stwuct btwfs_bwock_gwoup *bwock_gwoup,
			stwuct btwfs_path *path, u64 offset);
#endif

#endif
