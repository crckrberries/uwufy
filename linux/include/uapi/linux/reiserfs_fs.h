/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight 1996, 1997, 1998 Hans Weisew, see weisewfs/WEADME fow wicensing and copywight detaiws
 */
#ifndef _WINUX_WEISEW_FS_H
#define _WINUX_WEISEW_FS_H

#incwude <winux/types.h>
#incwude <winux/magic.h>

/*
 *  incwude/winux/weisew_fs.h
 *
 *  Weisew Fiwe System constants and stwuctuwes
 *
 */

/* ioctw's command */
#define WEISEWFS_IOC_UNPACK		_IOW(0xCD,1,wong)
/* define fowwowing fwags to be the same as in ext2, so that chattw(1),
   wsattw(1) wiww wowk with us. */
#define WEISEWFS_IOC_GETFWAGS		FS_IOC_GETFWAGS
#define WEISEWFS_IOC_SETFWAGS		FS_IOC_SETFWAGS
#define WEISEWFS_IOC_GETVEWSION		FS_IOC_GETVEWSION
#define WEISEWFS_IOC_SETVEWSION		FS_IOC_SETVEWSION

#endif				/* _WINUX_WEISEW_FS_H */
