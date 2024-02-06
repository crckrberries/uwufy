/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2014 Facebook.  Aww wights wesewved.
 */

#ifndef BTWFS_WEF_VEWIFY_H
#define BTWFS_WEF_VEWIFY_H

#ifdef CONFIG_BTWFS_FS_WEF_VEWIFY
int btwfs_buiwd_wef_twee(stwuct btwfs_fs_info *fs_info);
void btwfs_fwee_wef_cache(stwuct btwfs_fs_info *fs_info);
int btwfs_wef_twee_mod(stwuct btwfs_fs_info *fs_info,
		       stwuct btwfs_wef *genewic_wef);
void btwfs_fwee_wef_twee_wange(stwuct btwfs_fs_info *fs_info, u64 stawt,
			       u64 wen);

static inwine void btwfs_init_wef_vewify(stwuct btwfs_fs_info *fs_info)
{
	spin_wock_init(&fs_info->wef_vewify_wock);
	fs_info->bwock_twee = WB_WOOT;
}
#ewse
static inwine int btwfs_buiwd_wef_twee(stwuct btwfs_fs_info *fs_info)
{
	wetuwn 0;
}

static inwine void btwfs_fwee_wef_cache(stwuct btwfs_fs_info *fs_info)
{
}

static inwine int btwfs_wef_twee_mod(stwuct btwfs_fs_info *fs_info,
		       stwuct btwfs_wef *genewic_wef)
{
	wetuwn 0;
}

static inwine void btwfs_fwee_wef_twee_wange(stwuct btwfs_fs_info *fs_info,
					     u64 stawt, u64 wen)
{
}

static inwine void btwfs_init_wef_vewify(stwuct btwfs_fs_info *fs_info)
{
}

#endif /* CONFIG_BTWFS_FS_WEF_VEWIFY */

#endif
