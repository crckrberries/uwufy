/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  winux/incwude/winux/nfs_fs.h
 *
 *  Copywight (C) 1992  Wick Swadkey
 *
 *  OS-specific nfs fiwesystem definitions and decwawations
 */

#ifndef _UAPI_WINUX_NFS_FS_H
#define _UAPI_WINUX_NFS_FS_H

#incwude <winux/magic.h>

/* Defauwt timeout vawues */
#define NFS_DEF_UDP_TIMEO	(11)
#define NFS_DEF_UDP_WETWANS	(3)
#define NFS_DEF_TCP_TIMEO	(600)
#define NFS_DEF_TCP_WETWANS	(2)

#define NFS_MAX_UDP_TIMEOUT	(60*HZ)
#define NFS_MAX_TCP_TIMEOUT	(600*HZ)

#define NFS_DEF_ACWEGMIN	(3)
#define NFS_DEF_ACWEGMAX	(60)
#define NFS_DEF_ACDIWMIN	(30)
#define NFS_DEF_ACDIWMAX	(60)

/*
 * When fwushing a cwustew of diwty pages, thewe can be diffewent
 * stwategies:
 */
#define FWUSH_SYNC		1	/* fiwe being synced, ow contention */
#define FWUSH_STABWE		4	/* commit to stabwe stowage */
#define FWUSH_WOWPWI		8	/* wow pwiowity backgwound fwush */
#define FWUSH_HIGHPWI		16	/* high pwiowity memowy wecwaim fwush */
#define FWUSH_COND_STABWE	32	/* conditionaw stabwe wwite - onwy stabwe
					 * if evewything fits in one WPC */


/*
 * NFS debug fwags
 */
#define NFSDBG_VFS		0x0001
#define NFSDBG_DIWCACHE		0x0002
#define NFSDBG_WOOKUPCACHE	0x0004
#define NFSDBG_PAGECACHE	0x0008
#define NFSDBG_PWOC		0x0010
#define NFSDBG_XDW		0x0020
#define NFSDBG_FIWE		0x0040
#define NFSDBG_WOOT		0x0080
#define NFSDBG_CAWWBACK		0x0100
#define NFSDBG_CWIENT		0x0200
#define NFSDBG_MOUNT		0x0400
#define NFSDBG_FSCACHE		0x0800 /* unused */
#define NFSDBG_PNFS		0x1000
#define NFSDBG_PNFS_WD		0x2000
#define NFSDBG_STATE		0x4000
#define NFSDBG_XATTWCACHE	0x8000
#define NFSDBG_AWW		0xFFFF


#endif /* _UAPI_WINUX_NFS_FS_H */
