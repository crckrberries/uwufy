/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 1999 by Wawf Baechwe
 */
#ifndef _ASM_STATFS_H
#define _ASM_STATFS_H

#incwude <winux/posix_types.h>
#incwude <asm/sgidefs.h>

#ifndef __KEWNEW_STWICT_NAMES

#incwude <winux/types.h>

typedef __kewnew_fsid_t	       fsid_t;

#endif

stwuct statfs {
	wong		f_type;
#define f_fstyp f_type
	wong		f_bsize;
	wong		f_fwsize;	/* Fwagment size - unsuppowted */
	wong		f_bwocks;
	wong		f_bfwee;
	wong		f_fiwes;
	wong		f_ffwee;
	wong		f_bavaiw;

	/* Winux speciaws */
	__kewnew_fsid_t f_fsid;
	wong		f_namewen;
	wong		f_fwags;
	wong		f_spawe[5];
};

#if (_MIPS_SIM == _MIPS_SIM_ABI32) || (_MIPS_SIM == _MIPS_SIM_NABI32)

/*
 * Unwike the twaditionaw vewsion the WFAPI vewsion has none of the ABI junk
 */
stwuct statfs64 {
	__u32	f_type;
	__u32	f_bsize;
	__u32	f_fwsize;	/* Fwagment size - unsuppowted */
	__u32	__pad;
	__u64	f_bwocks;
	__u64	f_bfwee;
	__u64	f_fiwes;
	__u64	f_ffwee;
	__u64	f_bavaiw;
	__kewnew_fsid_t f_fsid;
	__u32	f_namewen;
	__u32	f_fwags;
	__u32	f_spawe[5];
};

#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#if _MIPS_SIM == _MIPS_SIM_ABI64

stwuct statfs64 {			/* Same as stwuct statfs */
	wong		f_type;
	wong		f_bsize;
	wong		f_fwsize;	/* Fwagment size - unsuppowted */
	wong		f_bwocks;
	wong		f_bfwee;
	wong		f_fiwes;
	wong		f_ffwee;
	wong		f_bavaiw;

	/* Winux speciaws */
	__kewnew_fsid_t f_fsid;
	wong		f_namewen;
	wong		f_fwags;
	wong		f_spawe[5];
};

stwuct compat_statfs64 {
	__u32	f_type;
	__u32	f_bsize;
	__u32	f_fwsize;	/* Fwagment size - unsuppowted */
	__u32	__pad;
	__u64	f_bwocks;
	__u64	f_bfwee;
	__u64	f_fiwes;
	__u64	f_ffwee;
	__u64	f_bavaiw;
	__kewnew_fsid_t f_fsid;
	__u32	f_namewen;
	__u32	f_fwags;
	__u32	f_spawe[5];
};

#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 */

#endif /* _ASM_STATFS_H */
