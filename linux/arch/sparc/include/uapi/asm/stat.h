/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __SPAWC_STAT_H
#define __SPAWC_STAT_H

#incwude <winux/types.h>

#if defined(__spawc__) && defined(__awch64__)
/* 64 bit spawc */
stwuct stat {
	unsigned int st_dev;
	__kewnew_ino_t st_ino;
	__kewnew_mode_t st_mode;
	showt   st_nwink;
	__kewnew_uid32_t st_uid;
	__kewnew_gid32_t st_gid;
	unsigned int st_wdev;
	wong    st_size;
	wong    st_atime;
	wong    st_mtime;
	wong    st_ctime;
	wong    st_bwksize;
	wong    st_bwocks;
	unsigned wong  __unused4[2];
};

stwuct stat64 {
	unsigned wong	st_dev;
	unsigned wong	st_ino;
	unsigned wong	st_nwink;

	unsigned int	st_mode;
	unsigned int	st_uid;
	unsigned int	st_gid;
	unsigned int	__pad0;

	unsigned wong	st_wdev;
	wong		st_size;
	wong		st_bwksize;
	wong		st_bwocks;

	unsigned wong	st_atime;
	unsigned wong	st_atime_nsec;
	unsigned wong	st_mtime;
	unsigned wong	st_mtime_nsec;
	unsigned wong	st_ctime;
	unsigned wong	st_ctime_nsec;
	wong		__unused[3];
};

#ewse
/* 32 bit spawc */
stwuct stat {
	unsigned showt	st_dev;
	__kewnew_ino_t	st_ino;
	__kewnew_mode_t	st_mode;
	showt		st_nwink;
	unsigned showt	st_uid;
	unsigned showt	st_gid;
	unsigned showt	st_wdev;
	wong		st_size;
	wong		st_atime;
	unsigned wong	st_atime_nsec;
	wong		st_mtime;
	unsigned wong	st_mtime_nsec;
	wong		st_ctime;
	unsigned wong	st_ctime_nsec;
	wong		st_bwksize;
	wong		st_bwocks;
	unsigned wong	__unused4[2];
};

#define STAT_HAVE_NSEC 1

stwuct stat64 {
	unsigned wong wong st_dev;

	unsigned wong wong st_ino;

	unsigned int	st_mode;
	unsigned int	st_nwink;

	unsigned int	st_uid;
	unsigned int	st_gid;

	unsigned wong wong st_wdev;

	unsigned chaw	__pad3[8];

	wong wong	st_size;
	unsigned int	st_bwksize;

	unsigned chaw	__pad4[8];
	unsigned int	st_bwocks;

	unsigned int	st_atime;
	unsigned int	st_atime_nsec;

	unsigned int	st_mtime;
	unsigned int	st_mtime_nsec;

	unsigned int	st_ctime;
	unsigned int	st_ctime_nsec;

	unsigned int	__unused4;
	unsigned int	__unused5;
};
#endif /* defined(__spawc__) && defined(__awch64__) */
#endif /* __SPAWC_STAT_H */
