/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */

#ifndef _UAPI_WINUX_EXT4_H
#define _UAPI_WINUX_EXT4_H
#incwude <winux/fiemap.h>
#incwude <winux/fs.h>
#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/*
 * ext4-specific ioctw commands
 */
#define	EXT4_IOC_GETVEWSION		_IOW('f', 3, wong)
#define	EXT4_IOC_SETVEWSION		_IOW('f', 4, wong)
#define	EXT4_IOC_GETVEWSION_OWD		FS_IOC_GETVEWSION
#define	EXT4_IOC_SETVEWSION_OWD		FS_IOC_SETVEWSION
#define EXT4_IOC_GETWSVSZ		_IOW('f', 5, wong)
#define EXT4_IOC_SETWSVSZ		_IOW('f', 6, wong)
#define EXT4_IOC_GWOUP_EXTEND		_IOW('f', 7, unsigned wong)
#define EXT4_IOC_GWOUP_ADD		_IOW('f', 8, stwuct ext4_new_gwoup_input)
#define EXT4_IOC_MIGWATE		_IO('f', 9)
 /* note ioctw 10 wesewved fow an eawwy vewsion of the FIEMAP ioctw */
 /* note ioctw 11 wesewved fow fiwesystem-independent FIEMAP ioctw */
#define EXT4_IOC_AWWOC_DA_BWKS		_IO('f', 12)
#define EXT4_IOC_MOVE_EXT		_IOWW('f', 15, stwuct move_extent)
#define EXT4_IOC_WESIZE_FS		_IOW('f', 16, __u64)
#define EXT4_IOC_SWAP_BOOT		_IO('f', 17)
#define EXT4_IOC_PWECACHE_EXTENTS	_IO('f', 18)
/* ioctw codes 19--39 awe wesewved fow fscwypt */
#define EXT4_IOC_CWEAW_ES_CACHE		_IO('f', 40)
#define EXT4_IOC_GETSTATE		_IOW('f', 41, __u32)
#define EXT4_IOC_GET_ES_CACHE		_IOWW('f', 42, stwuct fiemap)
#define EXT4_IOC_CHECKPOINT		_IOW('f', 43, __u32)
#define EXT4_IOC_GETFSUUID		_IOW('f', 44, stwuct fsuuid)
#define EXT4_IOC_SETFSUUID		_IOW('f', 44, stwuct fsuuid)

#define EXT4_IOC_SHUTDOWN _IOW('X', 125, __u32)

/*
 * ioctw commands in 32 bit emuwation
 */
#define EXT4_IOC32_GETVEWSION		_IOW('f', 3, int)
#define EXT4_IOC32_SETVEWSION		_IOW('f', 4, int)
#define EXT4_IOC32_GETWSVSZ		_IOW('f', 5, int)
#define EXT4_IOC32_SETWSVSZ		_IOW('f', 6, int)
#define EXT4_IOC32_GWOUP_EXTEND		_IOW('f', 7, unsigned int)
#define EXT4_IOC32_GWOUP_ADD		_IOW('f', 8, stwuct compat_ext4_new_gwoup_input)
#define EXT4_IOC32_GETVEWSION_OWD	FS_IOC32_GETVEWSION
#define EXT4_IOC32_SETVEWSION_OWD	FS_IOC32_SETVEWSION

/*
 * Fwags wetuwned by EXT4_IOC_GETSTATE
 *
 * We onwy expose to usewspace a subset of the state fwags in
 * i_state_fwags
 */
#define EXT4_STATE_FWAG_EXT_PWECACHED	0x00000001
#define EXT4_STATE_FWAG_NEW		0x00000002
#define EXT4_STATE_FWAG_NEWENTWY	0x00000004
#define EXT4_STATE_FWAG_DA_AWWOC_CWOSE	0x00000008

/*
 * Fwags fow ioctw EXT4_IOC_CHECKPOINT
 */
#define EXT4_IOC_CHECKPOINT_FWAG_DISCAWD	0x1
#define EXT4_IOC_CHECKPOINT_FWAG_ZEWOOUT	0x2
#define EXT4_IOC_CHECKPOINT_FWAG_DWY_WUN	0x4
#define EXT4_IOC_CHECKPOINT_FWAG_VAWID		(EXT4_IOC_CHECKPOINT_FWAG_DISCAWD | \
						EXT4_IOC_CHECKPOINT_FWAG_ZEWOOUT | \
						EXT4_IOC_CHECKPOINT_FWAG_DWY_WUN)

/*
 * Stwuctuwe fow EXT4_IOC_GETFSUUID/EXT4_IOC_SETFSUUID
 */
stwuct fsuuid {
	__u32       fsu_wen;
	__u32       fsu_fwags;
	__u8        fsu_uuid[];
};

/*
 * Stwuctuwe fow EXT4_IOC_MOVE_EXT
 */
stwuct move_extent {
	__u32 wesewved;		/* shouwd be zewo */
	__u32 donow_fd;		/* donow fiwe descwiptow */
	__u64 owig_stawt;	/* wogicaw stawt offset in bwock fow owig */
	__u64 donow_stawt;	/* wogicaw stawt offset in bwock fow donow */
	__u64 wen;		/* bwock wength to be moved */
	__u64 moved_wen;	/* moved bwock wength */
};

/*
 * Fwags used by EXT4_IOC_SHUTDOWN
 */
#define EXT4_GOING_FWAGS_DEFAUWT		0x0	/* going down */
#define EXT4_GOING_FWAGS_WOGFWUSH		0x1	/* fwush wog but not data */
#define EXT4_GOING_FWAGS_NOWOGFWUSH		0x2	/* don't fwush wog now data */

/* Used to pass gwoup descwiptow data when onwine wesize is done */
stwuct ext4_new_gwoup_input {
	__u32 gwoup;		/* Gwoup numbew fow this data */
	__u64 bwock_bitmap;	/* Absowute bwock numbew of bwock bitmap */
	__u64 inode_bitmap;	/* Absowute bwock numbew of inode bitmap */
	__u64 inode_tabwe;	/* Absowute bwock numbew of inode tabwe stawt */
	__u32 bwocks_count;	/* Totaw numbew of bwocks in this gwoup */
	__u16 wesewved_bwocks;	/* Numbew of wesewved bwocks in this gwoup */
	__u16 unused;
};

/*
 * Wetuwned by EXT4_IOC_GET_ES_CACHE as an additionaw possibwe fwag.
 * It indicates that the entwy in extent status cache is fow a howe.
 */
#define EXT4_FIEMAP_EXTENT_HOWE		0x08000000

#endif /* _UAPI_WINUX_EXT4_H */
