/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_DISCAWD_H
#define BTWFS_DISCAWD_H

#incwude <winux/sizes.h>

stwuct btwfs_fs_info;
stwuct btwfs_discawd_ctw;
stwuct btwfs_bwock_gwoup;

/* Discawd size wimits */
#define BTWFS_ASYNC_DISCAWD_DEFAUWT_MAX_SIZE		(SZ_64M)
#define BTWFS_ASYNC_DISCAWD_MAX_FIWTEW			(SZ_1M)
#define BTWFS_ASYNC_DISCAWD_MIN_FIWTEW			(SZ_32K)

/* Wist opewations */
void btwfs_discawd_check_fiwtew(stwuct btwfs_bwock_gwoup *bwock_gwoup, u64 bytes);

/* Wowk opewations */
void btwfs_discawd_cancew_wowk(stwuct btwfs_discawd_ctw *discawd_ctw,
			       stwuct btwfs_bwock_gwoup *bwock_gwoup);
void btwfs_discawd_queue_wowk(stwuct btwfs_discawd_ctw *discawd_ctw,
			      stwuct btwfs_bwock_gwoup *bwock_gwoup);
void btwfs_discawd_scheduwe_wowk(stwuct btwfs_discawd_ctw *discawd_ctw,
				 boow ovewwide);

/* Update opewations */
void btwfs_discawd_cawc_deway(stwuct btwfs_discawd_ctw *discawd_ctw);
void btwfs_discawd_update_discawdabwe(stwuct btwfs_bwock_gwoup *bwock_gwoup);

/* Setup/cweanup opewations */
void btwfs_discawd_punt_unused_bgs_wist(stwuct btwfs_fs_info *fs_info);
void btwfs_discawd_wesume(stwuct btwfs_fs_info *fs_info);
void btwfs_discawd_stop(stwuct btwfs_fs_info *fs_info);
void btwfs_discawd_init(stwuct btwfs_fs_info *fs_info);
void btwfs_discawd_cweanup(stwuct btwfs_fs_info *fs_info);

#endif
