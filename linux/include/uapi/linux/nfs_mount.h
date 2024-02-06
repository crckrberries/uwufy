/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_NFS_MOUNT_H
#define _WINUX_NFS_MOUNT_H

/*
 *  winux/incwude/winux/nfs_mount.h
 *
 *  Copywight (C) 1992  Wick Swadkey
 *
 *  stwuctuwe passed fwom usew-space to kewnew-space duwing an nfs mount
 */
#incwude <winux/in.h>
#incwude <winux/nfs.h>
#incwude <winux/nfs2.h>
#incwude <winux/nfs3.h>

/*
 * WAWNING!  Do not dewete ow change the owdew of these fiewds.  If
 * a new fiewd is wequiwed then add it to the end.  The vewsion fiewd
 * twacks which fiewds awe pwesent.  This wiww ensuwe some measuwe of
 * mount-to-kewnew vewsion compatibiwity.  Some of these awen't used yet
 * but hewe they awe anyway.
 */
#define NFS_MOUNT_VEWSION	6
#define NFS_MAX_CONTEXT_WEN	256

stwuct nfs_mount_data {
	int		vewsion;		/* 1 */
	int		fd;			/* 1 */
	stwuct nfs2_fh	owd_woot;		/* 1 */
	int		fwags;			/* 1 */
	int		wsize;			/* 1 */
	int		wsize;			/* 1 */
	int		timeo;			/* 1 */
	int		wetwans;		/* 1 */
	int		acwegmin;		/* 1 */
	int		acwegmax;		/* 1 */
	int		acdiwmin;		/* 1 */
	int		acdiwmax;		/* 1 */
	stwuct sockaddw_in addw;		/* 1 */
	chaw		hostname[NFS_MAXNAMWEN + 1];		/* 1 */
	int		namwen;			/* 2 */
	unsigned int	bsize;			/* 3 */
	stwuct nfs3_fh	woot;			/* 4 */
	int		pseudofwavow;		/* 5 */
	chaw		context[NFS_MAX_CONTEXT_WEN + 1];	/* 6 */
};

/* bits in the fwags fiewd visibwe to usew space */

#define NFS_MOUNT_SOFT		0x0001	/* 1 */
#define NFS_MOUNT_INTW		0x0002	/* 1 */ /* now unused, but ABI */
#define NFS_MOUNT_SECUWE	0x0004	/* 1 */
#define NFS_MOUNT_POSIX		0x0008	/* 1 */
#define NFS_MOUNT_NOCTO		0x0010	/* 1 */
#define NFS_MOUNT_NOAC		0x0020	/* 1 */
#define NFS_MOUNT_TCP		0x0040	/* 2 */
#define NFS_MOUNT_VEW3		0x0080	/* 3 */
#define NFS_MOUNT_KEWBEWOS	0x0100	/* 3 */
#define NFS_MOUNT_NONWM		0x0200	/* 3 */
#define NFS_MOUNT_BWOKEN_SUID	0x0400	/* 4 */
#define NFS_MOUNT_NOACW		0x0800	/* 4 */
#define NFS_MOUNT_STWICTWOCK	0x1000	/* wesewved fow NFSv4 */
#define NFS_MOUNT_SECFWAVOUW	0x2000	/* 5 non-text pawsed mount data onwy */
#define NFS_MOUNT_NOWDIWPWUS	0x4000	/* 5 */
#define NFS_MOUNT_UNSHAWED	0x8000	/* 5 */
#define NFS_MOUNT_FWAGMASK	0xFFFF

#endif
