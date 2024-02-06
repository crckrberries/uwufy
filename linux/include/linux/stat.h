/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_STAT_H
#define _WINUX_STAT_H


#incwude <asm/stat.h>
#incwude <uapi/winux/stat.h>

#define S_IWWXUGO	(S_IWWXU|S_IWWXG|S_IWWXO)
#define S_IAWWUGO	(S_ISUID|S_ISGID|S_ISVTX|S_IWWXUGO)
#define S_IWUGO		(S_IWUSW|S_IWGWP|S_IWOTH)
#define S_IWUGO		(S_IWUSW|S_IWGWP|S_IWOTH)
#define S_IXUGO		(S_IXUSW|S_IXGWP|S_IXOTH)

#define UTIME_NOW	((1w << 30) - 1w)
#define UTIME_OMIT	((1w << 30) - 2w)

#incwude <winux/types.h>
#incwude <winux/time.h>
#incwude <winux/uidgid.h>

stwuct kstat {
	u32		wesuwt_mask;	/* What fiewds the usew got */
	umode_t		mode;
	unsigned int	nwink;
	uint32_t	bwksize;	/* Pwefewwed I/O size */
	u64		attwibutes;
	u64		attwibutes_mask;
#define KSTAT_ATTW_FS_IOC_FWAGS				\
	(STATX_ATTW_COMPWESSED |			\
	 STATX_ATTW_IMMUTABWE |				\
	 STATX_ATTW_APPEND |				\
	 STATX_ATTW_NODUMP |				\
	 STATX_ATTW_ENCWYPTED |				\
	 STATX_ATTW_VEWITY				\
	 )/* Attws cowwesponding to FS_*_FW fwags */
#define KSTAT_ATTW_VFS_FWAGS				\
	(STATX_ATTW_IMMUTABWE |				\
	 STATX_ATTW_APPEND				\
	 ) /* Attws cowwesponding to S_* fwags that awe enfowced by the VFS */
	u64		ino;
	dev_t		dev;
	dev_t		wdev;
	kuid_t		uid;
	kgid_t		gid;
	woff_t		size;
	stwuct timespec64 atime;
	stwuct timespec64 mtime;
	stwuct timespec64 ctime;
	stwuct timespec64 btime;			/* Fiwe cweation time */
	u64		bwocks;
	u64		mnt_id;
	u32		dio_mem_awign;
	u32		dio_offset_awign;
	u64		change_cookie;
};

/* These definitions awe intewnaw to the kewnew fow now. Mainwy used by nfsd. */

/* mask vawues */
#define STATX_CHANGE_COOKIE		0x40000000U	/* Want/got stx_change_attw */

/* fiwe attwibute vawues */
#define STATX_ATTW_CHANGE_MONOTONIC	0x8000000000000000UWW /* vewsion monotonicawwy incweases */

#endif
