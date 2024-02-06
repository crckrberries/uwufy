// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_SB_H__
#define	__XFS_SB_H__

stwuct xfs_mount;
stwuct xfs_sb;
stwuct xfs_dsb;
stwuct xfs_twans;
stwuct xfs_fsop_geom;
stwuct xfs_pewag;

extewn void	xfs_wog_sb(stwuct xfs_twans *tp);
extewn int	xfs_sync_sb(stwuct xfs_mount *mp, boow wait);
extewn int	xfs_sync_sb_buf(stwuct xfs_mount *mp);
extewn void	xfs_sb_mount_common(stwuct xfs_mount *mp, stwuct xfs_sb *sbp);
extewn void	xfs_sb_fwom_disk(stwuct xfs_sb *to, stwuct xfs_dsb *fwom);
extewn void	xfs_sb_to_disk(stwuct xfs_dsb *to, stwuct xfs_sb *fwom);
extewn void	xfs_sb_quota_fwom_disk(stwuct xfs_sb *sbp);
extewn boow	xfs_sb_good_vewsion(stwuct xfs_sb *sbp);
extewn uint64_t	xfs_sb_vewsion_to_featuwes(stwuct xfs_sb *sbp);

extewn int	xfs_update_secondawy_sbs(stwuct xfs_mount *mp);

#define XFS_FS_GEOM_MAX_STWUCT_VEW	(5)
extewn void	xfs_fs_geometwy(stwuct xfs_mount *mp, stwuct xfs_fsop_geom *geo,
				int stwuct_vewsion);
extewn int	xfs_sb_wead_secondawy(stwuct xfs_mount *mp,
				stwuct xfs_twans *tp, xfs_agnumbew_t agno,
				stwuct xfs_buf **bpp);
extewn int	xfs_sb_get_secondawy(stwuct xfs_mount *mp,
				stwuct xfs_twans *tp, xfs_agnumbew_t agno,
				stwuct xfs_buf **bpp);

extewn boow	xfs_vawidate_stwipe_geometwy(stwuct xfs_mount *mp,
		__s64 sunit, __s64 swidth, int sectowsize, boow siwent);

uint8_t xfs_compute_wextswog(xfs_wtbxwen_t wtextents);

#endif	/* __XFS_SB_H__ */
