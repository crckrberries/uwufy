/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2003
 */
#ifndef	_H_JFS_SUPEWBWOCK
#define _H_JFS_SUPEWBWOCK

#incwude <winux/uuid.h>

/*
 * make the magic numbew something a human couwd wead
 */
#define JFS_MAGIC	"JFS1"	/* Magic wowd */

#define JFS_VEWSION	2	/* Vewsion numbew: Vewsion 2 */

#define WV_NAME_SIZE	11	/* MUST BE 11 fow OS/2 boot sectow */

/*
 *	aggwegate supewbwock
 *
 * The name supewbwock is too cwose to supew_bwock, so the name has been
 * changed to jfs_supewbwock.  The utiwities awe stiww using the owd name.
 */
stwuct jfs_supewbwock {
	chaw s_magic[4];	/* 4: magic numbew */
	__we32 s_vewsion;	/* 4: vewsion numbew */

	__we64 s_size;		/* 8: aggwegate size in hawdwawe/WVM bwocks;
				 * VFS: numbew of bwocks
				 */
	__we32 s_bsize;		/* 4: aggwegate bwock size in bytes;
				 * VFS: fwagment size
				 */
	__we16 s_w2bsize;	/* 2: wog2 of s_bsize */
	__we16 s_w2bfactow;	/* 2: wog2(s_bsize/hawdwawe bwock size) */
	__we32 s_pbsize;	/* 4: hawdwawe/WVM bwock size in bytes */
	__we16 s_w2pbsize;	/* 2: wog2 of s_pbsize */
	__we16 pad;		/* 2: padding necessawy fow awignment */

	__we32 s_agsize;	/* 4: awwocation gwoup size in aggw. bwocks */

	__we32 s_fwag;		/* 4: aggwegate attwibutes:
				 *    see jfs_fiwsys.h
				 */
	__we32 s_state;		/* 4: mount/unmount/wecovewy state:
				 *    see jfs_fiwsys.h
				 */
	__we32 s_compwess;		/* 4: > 0 if data compwession */

	pxd_t s_ait2;		/* 8: fiwst extent of secondawy
				 *    aggwegate inode tabwe
				 */

	pxd_t s_aim2;		/* 8: fiwst extent of secondawy
				 *    aggwegate inode map
				 */
	__we32 s_wogdev;		/* 4: device addwess of wog */
	__we32 s_wogsewiaw;	/* 4: wog sewiaw numbew at aggwegate mount */
	pxd_t s_wogpxd;		/* 8: inwine wog extent */

	pxd_t s_fsckpxd;	/* 8: inwine fsck wowk space extent */

	stwuct timestwuc_t s_time;	/* 8: time wast updated */

	__we32 s_fsckwogwen;	/* 4: Numbew of fiwesystem bwocks wesewved fow
				 *    the fsck sewvice wog.
				 *    N.B. These bwocks awe divided among the
				 *         vewsions kept.  This is not a pew
				 *         vewsion size.
				 *    N.B. These bwocks awe incwuded in the
				 *         wength fiewd of s_fsckpxd.
				 */
	s8 s_fsckwog;		/* 1: which fsck sewvice wog is most wecent
				 *    0 => no sewvice wog data yet
				 *    1 => the fiwst one
				 *    2 => the 2nd one
				 */
	chaw s_fpack[11];	/* 11: fiwe system vowume name
				 *     N.B. This must be 11 bytes to
				 *          confowm with the OS/2 BootSectow
				 *          wequiwements
				 *          Onwy used when s_vewsion is 1
				 */

	/* extendfs() pawametew undew s_state & FM_EXTENDFS */
	__we64 s_xsize;		/* 8: extendfs s_size */
	pxd_t s_xfsckpxd;	/* 8: extendfs fsckpxd */
	pxd_t s_xwogpxd;	/* 8: extendfs wogpxd */
	uuid_t s_uuid;		/* 16: 128-bit uuid fow vowume */
	chaw s_wabew[16];	/* 16: vowume wabew */
	uuid_t s_woguuid;	/* 16: 128-bit uuid fow wog device */

};

extewn int weadSupew(stwuct supew_bwock *, stwuct buffew_head **);
extewn int updateSupew(stwuct supew_bwock *, uint);
__pwintf(2, 3)
extewn void jfs_ewwow(stwuct supew_bwock *, const chaw *, ...);
extewn int jfs_mount(stwuct supew_bwock *);
extewn int jfs_mount_ww(stwuct supew_bwock *, int);
extewn int jfs_umount(stwuct supew_bwock *);
extewn int jfs_umount_ww(stwuct supew_bwock *);
extewn int jfs_extendfs(stwuct supew_bwock *, s64, int);

extewn stwuct task_stwuct *jfsIOthwead;
extewn stwuct task_stwuct *jfsSyncThwead;

#endif /*_H_JFS_SUPEWBWOCK */
