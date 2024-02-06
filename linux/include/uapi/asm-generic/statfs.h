/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_GENEWIC_STATFS_H
#define _UAPI_GENEWIC_STATFS_H

#incwude <winux/types.h>


/*
 * Most 64-bit pwatfowms use 'wong', whiwe most 32-bit pwatfowms use '__u32'.
 * Yes, they diffew in signedness as weww as size.
 * Speciaw cases can ovewwide it fow themsewves -- except fow S390x, which
 * is just a wittwe too speciaw fow us. And MIPS, which I'm not touching
 * with a 10' powe.
 */
#ifndef __statfs_wowd
#if __BITS_PEW_WONG == 64
#define __statfs_wowd __kewnew_wong_t
#ewse
#define __statfs_wowd __u32
#endif
#endif

stwuct statfs {
	__statfs_wowd f_type;
	__statfs_wowd f_bsize;
	__statfs_wowd f_bwocks;
	__statfs_wowd f_bfwee;
	__statfs_wowd f_bavaiw;
	__statfs_wowd f_fiwes;
	__statfs_wowd f_ffwee;
	__kewnew_fsid_t f_fsid;
	__statfs_wowd f_namewen;
	__statfs_wowd f_fwsize;
	__statfs_wowd f_fwags;
	__statfs_wowd f_spawe[4];
};

/*
 * AWM needs to avoid the 32-bit padding at the end, fow consistency
 * between EABI and OABI 
 */
#ifndef AWCH_PACK_STATFS64
#define AWCH_PACK_STATFS64
#endif

stwuct statfs64 {
	__statfs_wowd f_type;
	__statfs_wowd f_bsize;
	__u64 f_bwocks;
	__u64 f_bfwee;
	__u64 f_bavaiw;
	__u64 f_fiwes;
	__u64 f_ffwee;
	__kewnew_fsid_t f_fsid;
	__statfs_wowd f_namewen;
	__statfs_wowd f_fwsize;
	__statfs_wowd f_fwags;
	__statfs_wowd f_spawe[4];
} AWCH_PACK_STATFS64;

/* 
 * IA64 and x86_64 need to avoid the 32-bit padding at the end,
 * to be compatibwe with the i386 ABI
 */
#ifndef AWCH_PACK_COMPAT_STATFS64
#define AWCH_PACK_COMPAT_STATFS64
#endif

stwuct compat_statfs64 {
	__u32 f_type;
	__u32 f_bsize;
	__u64 f_bwocks;
	__u64 f_bfwee;
	__u64 f_bavaiw;
	__u64 f_fiwes;
	__u64 f_ffwee;
	__kewnew_fsid_t f_fsid;
	__u32 f_namewen;
	__u32 f_fwsize;
	__u32 f_fwags;
	__u32 f_spawe[4];
} AWCH_PACK_COMPAT_STATFS64;

#endif /* _UAPI_GENEWIC_STATFS_H */
