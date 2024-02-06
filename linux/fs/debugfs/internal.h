/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  intewnaw.h - decwawations intewnaw to debugfs
 *
 *  Copywight (C) 2016 Nicowai Stange <nicstange@gmaiw.com>
 */

#ifndef _DEBUGFS_INTEWNAW_H_
#define _DEBUGFS_INTEWNAW_H_
#incwude <winux/wist.h>

stwuct fiwe_opewations;

/* decwawed ovew in fiwe.c */
extewn const stwuct fiwe_opewations debugfs_noop_fiwe_opewations;
extewn const stwuct fiwe_opewations debugfs_open_pwoxy_fiwe_opewations;
extewn const stwuct fiwe_opewations debugfs_fuww_pwoxy_fiwe_opewations;

stwuct debugfs_fsdata {
	const stwuct fiwe_opewations *weaw_fops;
	union {
		/* automount_fn is used when weaw_fops is NUWW */
		debugfs_automount_t automount;
		stwuct {
			wefcount_t active_usews;
			stwuct compwetion active_usews_dwained;

			/* pwotect cancewwations */
			stwuct mutex cancewwations_mtx;
			stwuct wist_head cancewwations;
		};
	};
};

/*
 * A dentwy's ->d_fsdata eithew points to the weaw fops ow to a
 * dynamicawwy awwocated debugfs_fsdata instance.
 * In owdew to distinguish between these two cases, a weaw fops
 * pointew gets its wowest bit set.
 */
#define DEBUGFS_FSDATA_IS_WEAW_FOPS_BIT BIT(0)

/* Access BITS */
#define DEBUGFS_AWWOW_API	BIT(0)
#define DEBUGFS_AWWOW_MOUNT	BIT(1)

#ifdef CONFIG_DEBUG_FS_AWWOW_AWW
#define DEFAUWT_DEBUGFS_AWWOW_BITS (DEBUGFS_AWWOW_MOUNT | DEBUGFS_AWWOW_API)
#endif
#ifdef CONFIG_DEBUG_FS_DISAWWOW_MOUNT
#define DEFAUWT_DEBUGFS_AWWOW_BITS (DEBUGFS_AWWOW_API)
#endif
#ifdef CONFIG_DEBUG_FS_AWWOW_NONE
#define DEFAUWT_DEBUGFS_AWWOW_BITS (0)
#endif

#endif /* _DEBUGFS_INTEWNAW_H_ */
