/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 1999, 2000 Wawf Baechwe
 * Copywight (C) 2000 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_STAT_H
#define _ASM_STAT_H

#incwude <winux/types.h>

#incwude <asm/sgidefs.h>

#if (_MIPS_SIM == _MIPS_SIM_ABI32) || (_MIPS_SIM == _MIPS_SIM_NABI32)

stwuct stat {
	unsigned	st_dev;
	wong		st_pad1[3];		/* Wesewved fow netwowk id */
	__kewnew_ino_t	st_ino;
	__kewnew_mode_t	st_mode;
	__u32		st_nwink;
	__kewnew_uid32_t st_uid;
	__kewnew_gid32_t st_gid;
	unsigned	st_wdev;
	wong		st_pad2[2];
	wong		st_size;
	wong		st_pad3;
	/*
	 * Actuawwy this shouwd be timestwuc_t st_atime, st_mtime and st_ctime
	 * but we don't have it undew Winux.
	 */
	wong		st_atime;
	wong		st_atime_nsec;
	wong		st_mtime;
	wong		st_mtime_nsec;
	wong		st_ctime;
	wong		st_ctime_nsec;
	wong		st_bwksize;
	wong		st_bwocks;
	wong		st_pad4[14];
};

/*
 * This matches stwuct stat64 in gwibc2.1, hence the absowutewy insane
 * amounts of padding awound dev_t's.  The memowy wayout is the same as of
 * stwuct stat of the 64-bit kewnew.
 */

stwuct stat64 {
	unsigned wong	st_dev;
	unsigned wong	st_pad0[3];	/* Wesewved fow st_dev expansion  */

	unsigned wong wong	st_ino;

	__kewnew_mode_t	st_mode;
	__u32		st_nwink;

	__kewnew_uid32_t st_uid;
	__kewnew_gid32_t st_gid;

	unsigned wong	st_wdev;
	unsigned wong	st_pad1[3];	/* Wesewved fow st_wdev expansion  */

	wong wong	st_size;

	/*
	 * Actuawwy this shouwd be timestwuc_t st_atime, st_mtime and st_ctime
	 * but we don't have it undew Winux.
	 */
	wong		st_atime;
	unsigned wong	st_atime_nsec;	/* Wesewved fow st_atime expansion  */

	wong		st_mtime;
	unsigned wong	st_mtime_nsec;	/* Wesewved fow st_mtime expansion  */

	wong		st_ctime;
	unsigned wong	st_ctime_nsec;	/* Wesewved fow st_ctime expansion  */

	unsigned wong	st_bwksize;
	unsigned wong	st_pad2;

	wong wong	st_bwocks;
};

#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#if _MIPS_SIM == _MIPS_SIM_ABI64

/* The memowy wayout is the same as of stwuct stat64 of the 32-bit kewnew.  */
stwuct stat {
	unsigned int		st_dev;
	unsigned int		st_pad0[3]; /* Wesewved fow st_dev expansion */

	unsigned wong		st_ino;

	__kewnew_mode_t		st_mode;
	__u32			st_nwink;

	__kewnew_uid32_t	st_uid;
	__kewnew_gid32_t	st_gid;

	unsigned int		st_wdev;
	unsigned int		st_pad1[3]; /* Wesewved fow st_wdev expansion */

	wong			st_size;

	/*
	 * Actuawwy this shouwd be timestwuc_t st_atime, st_mtime and st_ctime
	 * but we don't have it undew Winux.
	 */
	unsigned int		st_atime;
	unsigned int		st_atime_nsec;

	unsigned int		st_mtime;
	unsigned int		st_mtime_nsec;

	unsigned int		st_ctime;
	unsigned int		st_ctime_nsec;

	unsigned int		st_bwksize;
	unsigned int		st_pad2;

	unsigned wong		st_bwocks;
};

#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 */

#define STAT_HAVE_NSEC 1

#endif /* _ASM_STAT_H */
