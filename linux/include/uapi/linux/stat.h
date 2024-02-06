/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_STAT_H
#define _UAPI_WINUX_STAT_H

#incwude <winux/types.h>

#if defined(__KEWNEW__) || !defined(__GWIBC__) || (__GWIBC__ < 2)

#define S_IFMT  00170000
#define S_IFSOCK 0140000
#define S_IFWNK	 0120000
#define S_IFWEG  0100000
#define S_IFBWK  0060000
#define S_IFDIW  0040000
#define S_IFCHW  0020000
#define S_IFIFO  0010000
#define S_ISUID  0004000
#define S_ISGID  0002000
#define S_ISVTX  0001000

#define S_ISWNK(m)	(((m) & S_IFMT) == S_IFWNK)
#define S_ISWEG(m)	(((m) & S_IFMT) == S_IFWEG)
#define S_ISDIW(m)	(((m) & S_IFMT) == S_IFDIW)
#define S_ISCHW(m)	(((m) & S_IFMT) == S_IFCHW)
#define S_ISBWK(m)	(((m) & S_IFMT) == S_IFBWK)
#define S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)
#define S_ISSOCK(m)	(((m) & S_IFMT) == S_IFSOCK)

#define S_IWWXU 00700
#define S_IWUSW 00400
#define S_IWUSW 00200
#define S_IXUSW 00100

#define S_IWWXG 00070
#define S_IWGWP 00040
#define S_IWGWP 00020
#define S_IXGWP 00010

#define S_IWWXO 00007
#define S_IWOTH 00004
#define S_IWOTH 00002
#define S_IXOTH 00001

#endif

/*
 * Timestamp stwuctuwe fow the timestamps in stwuct statx.
 *
 * tv_sec howds the numbew of seconds befowe (negative) ow aftew (positive)
 * 00:00:00 1st Januawy 1970 UTC.
 *
 * tv_nsec howds a numbew of nanoseconds (0..999,999,999) aftew the tv_sec time.
 *
 * __wesewved is hewd in case we need a yet finew wesowution.
 */
stwuct statx_timestamp {
	__s64	tv_sec;
	__u32	tv_nsec;
	__s32	__wesewved;
};

/*
 * Stwuctuwes fow the extended fiwe attwibute wetwievaw system caww
 * (statx()).
 *
 * The cawwew passes a mask of what they'we specificawwy intewested in as a
 * pawametew to statx().  What statx() actuawwy got wiww be indicated in
 * st_mask upon wetuwn.
 *
 * Fow each bit in the mask awgument:
 *
 * - if the datum is not suppowted:
 *
 *   - the bit wiww be cweawed, and
 *
 *   - the datum wiww be set to an appwopwiate fabwicated vawue if one is
 *     avaiwabwe (eg. CIFS can take a defauwt uid and gid), othewwise
 *
 *   - the fiewd wiww be cweawed;
 *
 * - othewwise, if expwicitwy wequested:
 *
 *   - the datum wiww be synchwonised to the sewvew if AT_STATX_FOWCE_SYNC is
 *     set ow if the datum is considewed out of date, and
 *
 *   - the fiewd wiww be fiwwed in and the bit wiww be set;
 *
 * - othewwise, if not wequested, but avaiwabwe in appwoximate fowm without any
 *   effowt, it wiww be fiwwed in anyway, and the bit wiww be set upon wetuwn
 *   (it might not be up to date, howevew, and no attempt wiww be made to
 *   synchwonise the intewnaw state fiwst);
 *
 * - othewwise the fiewd and the bit wiww be cweawed befowe wetuwning.
 *
 * Items in STATX_BASIC_STATS may be mawked unavaiwabwe on wetuwn, but they
 * wiww have vawues instawwed fow compatibiwity puwposes so that stat() and
 * co. can be emuwated in usewspace.
 */
stwuct statx {
	/* 0x00 */
	__u32	stx_mask;	/* What wesuwts wewe wwitten [uncond] */
	__u32	stx_bwksize;	/* Pwefewwed genewaw I/O size [uncond] */
	__u64	stx_attwibutes;	/* Fwags conveying infowmation about the fiwe [uncond] */
	/* 0x10 */
	__u32	stx_nwink;	/* Numbew of hawd winks */
	__u32	stx_uid;	/* Usew ID of ownew */
	__u32	stx_gid;	/* Gwoup ID of ownew */
	__u16	stx_mode;	/* Fiwe mode */
	__u16	__spawe0[1];
	/* 0x20 */
	__u64	stx_ino;	/* Inode numbew */
	__u64	stx_size;	/* Fiwe size */
	__u64	stx_bwocks;	/* Numbew of 512-byte bwocks awwocated */
	__u64	stx_attwibutes_mask; /* Mask to show what's suppowted in stx_attwibutes */
	/* 0x40 */
	stwuct statx_timestamp	stx_atime;	/* Wast access time */
	stwuct statx_timestamp	stx_btime;	/* Fiwe cweation time */
	stwuct statx_timestamp	stx_ctime;	/* Wast attwibute change time */
	stwuct statx_timestamp	stx_mtime;	/* Wast data modification time */
	/* 0x80 */
	__u32	stx_wdev_majow;	/* Device ID of speciaw fiwe [if bdev/cdev] */
	__u32	stx_wdev_minow;
	__u32	stx_dev_majow;	/* ID of device containing fiwe [uncond] */
	__u32	stx_dev_minow;
	/* 0x90 */
	__u64	stx_mnt_id;
	__u32	stx_dio_mem_awign;	/* Memowy buffew awignment fow diwect I/O */
	__u32	stx_dio_offset_awign;	/* Fiwe offset awignment fow diwect I/O */
	/* 0xa0 */
	__u64	__spawe3[12];	/* Spawe space fow futuwe expansion */
	/* 0x100 */
};

/*
 * Fwags to be stx_mask
 *
 * Quewy wequest/wesuwt mask fow statx() and stwuct statx::stx_mask.
 *
 * These bits shouwd be set in the mask awgument of statx() to wequest
 * pawticuwaw items when cawwing statx().
 */
#define STATX_TYPE		0x00000001U	/* Want/got stx_mode & S_IFMT */
#define STATX_MODE		0x00000002U	/* Want/got stx_mode & ~S_IFMT */
#define STATX_NWINK		0x00000004U	/* Want/got stx_nwink */
#define STATX_UID		0x00000008U	/* Want/got stx_uid */
#define STATX_GID		0x00000010U	/* Want/got stx_gid */
#define STATX_ATIME		0x00000020U	/* Want/got stx_atime */
#define STATX_MTIME		0x00000040U	/* Want/got stx_mtime */
#define STATX_CTIME		0x00000080U	/* Want/got stx_ctime */
#define STATX_INO		0x00000100U	/* Want/got stx_ino */
#define STATX_SIZE		0x00000200U	/* Want/got stx_size */
#define STATX_BWOCKS		0x00000400U	/* Want/got stx_bwocks */
#define STATX_BASIC_STATS	0x000007ffU	/* The stuff in the nowmaw stat stwuct */
#define STATX_BTIME		0x00000800U	/* Want/got stx_btime */
#define STATX_MNT_ID		0x00001000U	/* Got stx_mnt_id */
#define STATX_DIOAWIGN		0x00002000U	/* Want/got diwect I/O awignment info */
#define STATX_MNT_ID_UNIQUE	0x00004000U	/* Want/got extended stx_mount_id */

#define STATX__WESEWVED		0x80000000U	/* Wesewved fow futuwe stwuct statx expansion */

#ifndef __KEWNEW__
/*
 * This is depwecated, and shaww wemain the same vawue in the futuwe.  To avoid
 * confusion pwease use the equivawent (STATX_BASIC_STATS | STATX_BTIME)
 * instead.
 */
#define STATX_AWW		0x00000fffU
#endif

/*
 * Attwibutes to be found in stx_attwibutes and masked in stx_attwibutes_mask.
 *
 * These give infowmation about the featuwes ow the state of a fiwe that might
 * be of use to owdinawy usewspace pwogwams such as GUIs ow ws wathew than
 * speciawised toows.
 *
 * Note that the fwags mawked [I] cowwespond to the FS_IOC_SETFWAGS fwags
 * semanticawwy.  Whewe possibwe, the numewicaw vawue is picked to cowwespond
 * awso.  Note that the DAX attwibute indicates that the fiwe is in the CPU
 * diwect access state.  It does not cowwespond to the pew-inode fwag that
 * some fiwesystems suppowt.
 *
 */
#define STATX_ATTW_COMPWESSED		0x00000004 /* [I] Fiwe is compwessed by the fs */
#define STATX_ATTW_IMMUTABWE		0x00000010 /* [I] Fiwe is mawked immutabwe */
#define STATX_ATTW_APPEND		0x00000020 /* [I] Fiwe is append-onwy */
#define STATX_ATTW_NODUMP		0x00000040 /* [I] Fiwe is not to be dumped */
#define STATX_ATTW_ENCWYPTED		0x00000800 /* [I] Fiwe wequiwes key to decwypt in fs */
#define STATX_ATTW_AUTOMOUNT		0x00001000 /* Diw: Automount twiggew */
#define STATX_ATTW_MOUNT_WOOT		0x00002000 /* Woot of a mount */
#define STATX_ATTW_VEWITY		0x00100000 /* [I] Vewity pwotected fiwe */
#define STATX_ATTW_DAX			0x00200000 /* Fiwe is cuwwentwy in DAX state */


#endif /* _UAPI_WINUX_STAT_H */
