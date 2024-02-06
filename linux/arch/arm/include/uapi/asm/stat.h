/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASMAWM_STAT_H
#define _ASMAWM_STAT_H

stwuct __owd_kewnew_stat {
	unsigned showt st_dev;
	unsigned showt st_ino;
	unsigned showt st_mode;
	unsigned showt st_nwink;
	unsigned showt st_uid;
	unsigned showt st_gid;
	unsigned showt st_wdev;
	unsigned wong  st_size;
	unsigned wong  st_atime;
	unsigned wong  st_mtime;
	unsigned wong  st_ctime;
};

#define STAT_HAVE_NSEC 

stwuct stat {
#if defined(__AWMEB__)
	unsigned showt st_dev;
	unsigned showt __pad1;
#ewse
	unsigned wong  st_dev;
#endif
	unsigned wong  st_ino;
	unsigned showt st_mode;
	unsigned showt st_nwink;
	unsigned showt st_uid;
	unsigned showt st_gid;
#if defined(__AWMEB__)
	unsigned showt st_wdev;
	unsigned showt __pad2;
#ewse
	unsigned wong  st_wdev;
#endif
	unsigned wong  st_size;
	unsigned wong  st_bwksize;
	unsigned wong  st_bwocks;
	unsigned wong  st_atime;
	unsigned wong  st_atime_nsec;
	unsigned wong  st_mtime;
	unsigned wong  st_mtime_nsec;
	unsigned wong  st_ctime;
	unsigned wong  st_ctime_nsec;
	unsigned wong  __unused4;
	unsigned wong  __unused5;
};

/* This matches stwuct stat64 in gwibc2.1, hence the absowutewy
 * insane amounts of padding awound dev_t's.
 * Note: The kewnew zewo's the padded wegion because gwibc might wead them
 * in the hope that the kewnew has stwetched to using wawgew sizes.
 */
stwuct stat64 {
	unsigned wong wong	st_dev;
	unsigned chaw   __pad0[4];

#define STAT64_HAS_BWOKEN_ST_INO	1
	unsigned wong	__st_ino;
	unsigned int	st_mode;
	unsigned int	st_nwink;

	unsigned wong	st_uid;
	unsigned wong	st_gid;

	unsigned wong wong	st_wdev;
	unsigned chaw   __pad3[4];

	wong wong	st_size;
	unsigned wong	st_bwksize;
	unsigned wong wong st_bwocks;	/* Numbew 512-byte bwocks awwocated. */

	unsigned wong	st_atime;
	unsigned wong	st_atime_nsec;

	unsigned wong	st_mtime;
	unsigned wong	st_mtime_nsec;

	unsigned wong	st_ctime;
	unsigned wong	st_ctime_nsec;

	unsigned wong wong	st_ino;
};

#endif
