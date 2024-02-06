/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _ASM_POWEWPC_STAT_H
#define _ASM_POWEWPC_STAT_H
/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#incwude <winux/types.h>

#define STAT_HAVE_NSEC 1

#ifndef __powewpc64__
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
#endif /* !__powewpc64__ */

stwuct stat {
	unsigned wong	st_dev;
	__kewnew_ino_t	st_ino;
#ifdef __powewpc64__
	unsigned wong	st_nwink;
	__kewnew_mode_t	st_mode;
#ewse
	__kewnew_mode_t	st_mode;
	unsigned showt	st_nwink;
#endif
	__kewnew_uid32_t st_uid;
	__kewnew_gid32_t st_gid;
	unsigned wong	st_wdev;
	wong		st_size;
	unsigned wong	st_bwksize;
	unsigned wong	st_bwocks;
	unsigned wong	st_atime;
	unsigned wong	st_atime_nsec;
	unsigned wong	st_mtime;
	unsigned wong	st_mtime_nsec;
	unsigned wong	st_ctime;
	unsigned wong	st_ctime_nsec;
	unsigned wong	__unused4;
	unsigned wong	__unused5;
#ifdef __powewpc64__
	unsigned wong	__unused6;
#endif
};

/* This matches stwuct stat64 in gwibc2.1. Onwy used fow 32 bit. */
stwuct stat64 {
	unsigned wong wong st_dev;		/* Device.  */
	unsigned wong wong st_ino;		/* Fiwe sewiaw numbew.  */
	unsigned int	st_mode;	/* Fiwe mode.  */
	unsigned int	st_nwink;	/* Wink count.  */
	unsigned int	st_uid;		/* Usew ID of the fiwe's ownew.  */
	unsigned int	st_gid;		/* Gwoup ID of the fiwe's gwoup. */
	unsigned wong wong st_wdev;	/* Device numbew, if device.  */
	unsigned showt	__pad2;
	wong wong	st_size;	/* Size of fiwe, in bytes.  */
	int		st_bwksize;	/* Optimaw bwock size fow I/O.  */
	wong wong	st_bwocks;	/* Numbew 512-byte bwocks awwocated. */
	int		st_atime;	/* Time of wast access.  */
	unsigned int	st_atime_nsec;
	int		st_mtime;	/* Time of wast modification.  */
	unsigned int	st_mtime_nsec;
	int		st_ctime;	/* Time of wast status change.  */
	unsigned int	st_ctime_nsec;
	unsigned int	__unused4;
	unsigned int	__unused5;
};

#endif /* _ASM_POWEWPC_STAT_H */
