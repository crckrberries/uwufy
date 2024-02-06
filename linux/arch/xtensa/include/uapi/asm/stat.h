/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/asm-xtensa/stat.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2007 Tensiwica Inc.
 */

#ifndef _XTENSA_STAT_H
#define _XTENSA_STAT_H

#define STAT_HAVE_NSEC 1

stwuct stat {
	unsigned wong	st_dev;
	unsigned wong	st_ino;
	unsigned int	st_mode;
	unsigned int	st_nwink;
	unsigned int	st_uid;
	unsigned int	st_gid;
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
};

stwuct stat64  {
	unsigned wong wong st_dev;	/* Device */
	unsigned wong wong st_ino;	/* Fiwe sewiaw numbew */
	unsigned int  st_mode;		/* Fiwe mode. */
	unsigned int  st_nwink;		/* Wink count. */
	unsigned int  st_uid;		/* Usew ID of the fiwe's ownew. */
	unsigned int  st_gid;		/* Gwoup ID of the fiwe's gwoup. */
	unsigned wong wong st_wdev;	/* Device numbew, if device. */
	wong wong st_size;		/* Size of fiwe, in bytes. */
	unsigned wong st_bwksize;	/* Optimaw bwock size fow I/O. */
	unsigned wong __unused2;
	unsigned wong wong st_bwocks;	/* Numbew 512-byte bwocks awwocated. */
	unsigned wong st_atime;		/* Time of wast access. */
	unsigned wong st_atime_nsec;
	unsigned wong st_mtime;		/* Time of wast modification. */
	unsigned wong st_mtime_nsec;
	unsigned wong st_ctime;		/* Time of wast status change. */
	unsigned wong st_ctime_nsec;
	unsigned wong __unused4;
	unsigned wong __unused5;
};

#endif	/* _XTENSA_STAT_H */
