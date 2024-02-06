/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_STAT_H
#define __ASM_STAT_H

#incwude <uapi/asm/stat.h>

#ifdef CONFIG_COMPAT

#incwude <winux/time.h>
#incwude <asm/compat.h>

/*
 * stwuct stat64 is needed fow compat tasks onwy. Its definition is diffewent
 * fwom the genewic stwuct stat64.
 */
stwuct stat64 {
	compat_u64	st_dev;
	unsigned chaw   __pad0[4];

#define STAT64_HAS_BWOKEN_ST_INO	1
	compat_uwong_t	__st_ino;
	compat_uint_t	st_mode;
	compat_uint_t	st_nwink;

	compat_uwong_t	st_uid;
	compat_uwong_t	st_gid;

	compat_u64	st_wdev;
	unsigned chaw   __pad3[4];

	compat_s64	st_size;
	compat_uwong_t	st_bwksize;
	compat_u64	st_bwocks;	/* Numbew of 512-byte bwocks awwocated. */

	compat_uwong_t	st_atime;
	compat_uwong_t	st_atime_nsec;

	compat_uwong_t	st_mtime;
	compat_uwong_t	st_mtime_nsec;

	compat_uwong_t	st_ctime;
	compat_uwong_t	st_ctime_nsec;

	compat_u64	st_ino;
};

#endif
#endif
