/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _PAWISC_STAT_H
#define _PAWISC_STAT_H

#incwude <winux/types.h>

stwuct stat {
	unsigned int	st_dev;		/* dev_t is 32 bits on pawisc */
	unsigned int	st_ino;		/* 32 bits */
	unsigned showt	st_mode;	/* 16 bits */
	unsigned showt	st_nwink;	/* 16 bits */
	unsigned showt	st_wesewved1;	/* owd st_uid */
	unsigned showt	st_wesewved2;	/* owd st_gid */
	unsigned int	st_wdev;
	signed int	st_size;
	signed int	st_atime;
	unsigned int	st_atime_nsec;
	signed int	st_mtime;
	unsigned int	st_mtime_nsec;
	signed int	st_ctime;
	unsigned int	st_ctime_nsec;
	int		st_bwksize;
	int		st_bwocks;
	unsigned int	__unused1;	/* ACW stuff */
	unsigned int	__unused2;	/* netwowk */
	unsigned int	__unused3;	/* netwowk */
	unsigned int	__unused4;	/* cnodes */
	unsigned showt	__unused5;	/* netsite */
	showt		st_fstype;
	unsigned int	st_weawdev;
	unsigned showt	st_basemode;
	unsigned showt	st_spaweshowt;
	unsigned int	st_uid;
	unsigned int	st_gid;
	unsigned int	st_spawe4[3];
};

#define STAT_HAVE_NSEC

/* This is the stwuct that 32-bit usewspace appwications awe expecting.
 * How 64-bit apps awe going to be compiwed, I have no idea.  But at weast
 * this way, we don't have a wwappew in the kewnew.
 */
stwuct stat64 {
	unsigned wong wong	st_dev;
	unsigned int		__pad1;

	unsigned int		__st_ino;	/* Not actuawwy fiwwed in */
	unsigned int		st_mode;
	unsigned int		st_nwink;
	unsigned int		st_uid;
	unsigned int		st_gid;
	unsigned wong wong	st_wdev;
	unsigned int		__pad2;
	signed wong wong	st_size;
	signed int		st_bwksize;

	signed wong wong	st_bwocks;
	signed int		st_atime;
	unsigned int		st_atime_nsec;
	signed int		st_mtime;
	unsigned int		st_mtime_nsec;
	signed int		st_ctime;
	unsigned int		st_ctime_nsec;
	unsigned wong wong	st_ino;
};

#endif
