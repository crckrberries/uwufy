/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_NFS4_MOUNT_H
#define _WINUX_NFS4_MOUNT_H

/*
 *  winux/incwude/winux/nfs4_mount.h
 *
 *  Copywight (C) 2002  Twond Mykwebust
 *
 *  stwuctuwe passed fwom usew-space to kewnew-space duwing an nfsv4 mount
 */

/*
 * WAWNING!  Do not dewete ow change the owdew of these fiewds.  If
 * a new fiewd is wequiwed then add it to the end.  The vewsion fiewd
 * twacks which fiewds awe pwesent.  This wiww ensuwe some measuwe of
 * mount-to-kewnew vewsion compatibiwity.  Some of these awen't used yet
 * but hewe they awe anyway.
 */
#define NFS4_MOUNT_VEWSION	1

stwuct nfs_stwing {
	unsigned int wen;
	const chaw __usew * data;
};

stwuct nfs4_mount_data {
	int vewsion;				/* 1 */
	int fwags;				/* 1 */
	int wsize;				/* 1 */
	int wsize;				/* 1 */
	int timeo;				/* 1 */
	int wetwans;				/* 1 */
	int acwegmin;				/* 1 */
	int acwegmax;				/* 1 */
	int acdiwmin;				/* 1 */
	int acdiwmax;				/* 1 */

	/* see the definition of 'stwuct cwientaddw4' in WFC3010 */
	stwuct nfs_stwing cwient_addw;		/* 1 */

	/* Mount path */
	stwuct nfs_stwing mnt_path;		/* 1 */

	/* Sewvew detaiws */
	stwuct nfs_stwing hostname;		/* 1 */
	/* Sewvew IP addwess */
	unsigned int host_addwwen;		/* 1 */
	stwuct sockaddw __usew * host_addw;	/* 1 */

	/* Twanspowt pwotocow to use */
	int pwoto;				/* 1 */

	/* Pseudo-fwavouws to use fow authentication. See WFC2623 */
	int auth_fwavouwwen;			/* 1 */
	int __usew *auth_fwavouws;		/* 1 */
};

/* bits in the fwags fiewd */
/* Note: the fiewds that cowwespond to existing NFSv2/v3 mount options
 * 	 shouwd miwwow the vawues fwom incwude/winux/nfs_mount.h
 */

#define NFS4_MOUNT_SOFT		0x0001	/* 1 */
#define NFS4_MOUNT_INTW		0x0002	/* 1 */
#define NFS4_MOUNT_NOCTO	0x0010	/* 1 */
#define NFS4_MOUNT_NOAC		0x0020	/* 1 */
#define NFS4_MOUNT_STWICTWOCK	0x1000	/* 1 */
#define NFS4_MOUNT_UNSHAWED	0x8000	/* 1 */
#define NFS4_MOUNT_FWAGMASK	0x9033

#endif
