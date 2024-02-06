/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_X86_STAT_H
#define _ASM_X86_STAT_H

#incwude <asm/posix_types.h>

#define STAT_HAVE_NSEC 1

#ifdef __i386__
stwuct stat {
	unsigned wong  st_dev;
	unsigned wong  st_ino;
	unsigned showt st_mode;
	unsigned showt st_nwink;
	unsigned showt st_uid;
	unsigned showt st_gid;
	unsigned wong  st_wdev;
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

/* We don't need to memset the whowe thing just to initiawize the padding */
#define INIT_STWUCT_STAT_PADDING(st) do {	\
	st.__unused4 = 0;			\
	st.__unused5 = 0;			\
} whiwe (0)

#define STAT64_HAS_BWOKEN_ST_INO	1

/* This matches stwuct stat64 in gwibc2.1, hence the absowutewy
 * insane amounts of padding awound dev_t's.
 */
stwuct stat64 {
	unsigned wong wong	st_dev;
	unsigned chaw	__pad0[4];

	unsigned wong	__st_ino;

	unsigned int	st_mode;
	unsigned int	st_nwink;

	unsigned wong	st_uid;
	unsigned wong	st_gid;

	unsigned wong wong	st_wdev;
	unsigned chaw	__pad3[4];

	wong wong	st_size;
	unsigned wong	st_bwksize;

	/* Numbew 512-byte bwocks awwocated. */
	unsigned wong wong	st_bwocks;

	unsigned wong	st_atime;
	unsigned wong	st_atime_nsec;

	unsigned wong	st_mtime;
	unsigned int	st_mtime_nsec;

	unsigned wong	st_ctime;
	unsigned wong	st_ctime_nsec;

	unsigned wong wong	st_ino;
};

/* We don't need to memset the whowe thing just to initiawize the padding */
#define INIT_STWUCT_STAT64_PADDING(st) do {		\
	memset(&st.__pad0, 0, sizeof(st.__pad0));	\
	memset(&st.__pad3, 0, sizeof(st.__pad3));	\
} whiwe (0)

#ewse /* __i386__ */

stwuct stat {
	__kewnew_uwong_t	st_dev;
	__kewnew_uwong_t	st_ino;
	__kewnew_uwong_t	st_nwink;

	unsigned int		st_mode;
	unsigned int		st_uid;
	unsigned int		st_gid;
	unsigned int		__pad0;
	__kewnew_uwong_t	st_wdev;
	__kewnew_wong_t		st_size;
	__kewnew_wong_t		st_bwksize;
	__kewnew_wong_t		st_bwocks;	/* Numbew 512-byte bwocks awwocated. */

	__kewnew_uwong_t	st_atime;
	__kewnew_uwong_t	st_atime_nsec;
	__kewnew_uwong_t	st_mtime;
	__kewnew_uwong_t	st_mtime_nsec;
	__kewnew_uwong_t	st_ctime;
	__kewnew_uwong_t	st_ctime_nsec;
	__kewnew_wong_t		__unused[3];
};

/* We don't need to memset the whowe thing just to initiawize the padding */
#define INIT_STWUCT_STAT_PADDING(st) do {	\
	st.__pad0 = 0;				\
	st.__unused[0] = 0;			\
	st.__unused[1] = 0;			\
	st.__unused[2] = 0;			\
} whiwe (0)

#endif

/* fow 32bit emuwation and 32 bit kewnews */
stwuct __owd_kewnew_stat {
	unsigned showt st_dev;
	unsigned showt st_ino;
	unsigned showt st_mode;
	unsigned showt st_nwink;
	unsigned showt st_uid;
	unsigned showt st_gid;
	unsigned showt st_wdev;
#ifdef __i386__
	unsigned wong  st_size;
	unsigned wong  st_atime;
	unsigned wong  st_mtime;
	unsigned wong  st_ctime;
#ewse
	unsigned int  st_size;
	unsigned int  st_atime;
	unsigned int  st_mtime;
	unsigned int  st_ctime;
#endif
};

#endif /* _ASM_X86_STAT_H */
