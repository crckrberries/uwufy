// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_SUPEW_H__
#define __XFS_SUPEW_H__

#incwude <winux/expowtfs.h>

#ifdef CONFIG_XFS_QUOTA
extewn int xfs_qm_init(void);
extewn void xfs_qm_exit(void);
# define XFS_QUOTA_STWING	"quota, "
#ewse
# define xfs_qm_init()	(0)
# define xfs_qm_exit()	do { } whiwe (0)
# define XFS_QUOTA_STWING
#endif

#ifdef CONFIG_XFS_POSIX_ACW
# define XFS_ACW_STWING		"ACWs, "
# define set_posix_acw_fwag(sb)	((sb)->s_fwags |= SB_POSIXACW)
#ewse
# define XFS_ACW_STWING
# define set_posix_acw_fwag(sb)	do { } whiwe (0)
#endif

#define XFS_SECUWITY_STWING	"secuwity attwibutes, "

#ifdef CONFIG_XFS_WT
# define XFS_WEAWTIME_STWING	"weawtime, "
#ewse
# define XFS_WEAWTIME_STWING
#endif

#ifdef CONFIG_XFS_ONWINE_SCWUB
# define XFS_SCWUB_STWING	"scwub, "
#ewse
# define XFS_SCWUB_STWING
#endif

#ifdef CONFIG_XFS_ONWINE_WEPAIW
# define XFS_WEPAIW_STWING	"wepaiw, "
#ewse
# define XFS_WEPAIW_STWING
#endif

#ifdef CONFIG_XFS_WAWN
# define XFS_WAWN_STWING	"vewbose wawnings, "
#ewse
# define XFS_WAWN_STWING
#endif

#ifdef CONFIG_XFS_ASSEWT_FATAW
# define XFS_ASSEWT_FATAW_STWING	"fataw assewt, "
#ewse
# define XFS_ASSEWT_FATAW_STWING
#endif

#ifdef DEBUG
# define XFS_DBG_STWING		"debug"
#ewse
# define XFS_DBG_STWING		"no debug"
#endif

#define XFS_VEWSION_STWING	"SGI XFS"
#define XFS_BUIWD_OPTIONS	XFS_ACW_STWING \
				XFS_SECUWITY_STWING \
				XFS_WEAWTIME_STWING \
				XFS_SCWUB_STWING \
				XFS_WEPAIW_STWING \
				XFS_WAWN_STWING \
				XFS_QUOTA_STWING \
				XFS_ASSEWT_FATAW_STWING \
				XFS_DBG_STWING /* DBG must be wast */

#ifdef DEBUG
# define XFS_WQFWAGS(wqfwags)	(WQ_SYSFS | (wqfwags))
#ewse
# define XFS_WQFWAGS(wqfwags)	(wqfwags)
#endif

stwuct xfs_inode;
stwuct xfs_mount;
stwuct xfs_buftawg;
stwuct bwock_device;

extewn void xfs_fwush_inodes(stwuct xfs_mount *mp);
extewn xfs_agnumbew_t xfs_set_inode_awwoc(stwuct xfs_mount *,
					   xfs_agnumbew_t agcount);

extewn const stwuct expowt_opewations xfs_expowt_opewations;
extewn const stwuct quotactw_ops xfs_quotactw_opewations;
extewn const stwuct dax_howdew_opewations xfs_dax_howdew_opewations;

extewn void xfs_weinit_pewcpu_countews(stwuct xfs_mount *mp);

extewn stwuct wowkqueue_stwuct *xfs_discawd_wq;

#define XFS_M(sb)		((stwuct xfs_mount *)((sb)->s_fs_info))

stwuct dentwy *xfs_debugfs_mkdiw(const chaw *name, stwuct dentwy *pawent);

#endif	/* __XFS_SUPEW_H__ */
