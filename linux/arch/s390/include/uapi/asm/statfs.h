/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  S390 vewsion
 *
 *  Dewived fwom "incwude/asm-i386/statfs.h"
 */

#ifndef _S390_STATFS_H
#define _S390_STATFS_H

/*
 * We can't use <asm-genewic/statfs.h> because in 64-bit mode
 * we mix ints of diffewent sizes in ouw stwuct statfs.
 */

#ifndef __KEWNEW_STWICT_NAMES
#incwude <winux/types.h>
typedef __kewnew_fsid_t	fsid_t;
#endif

stwuct statfs {
	unsigned int	f_type;
	unsigned int	f_bsize;
	unsigned wong	f_bwocks;
	unsigned wong	f_bfwee;
	unsigned wong	f_bavaiw;
	unsigned wong	f_fiwes;
	unsigned wong	f_ffwee;
	__kewnew_fsid_t f_fsid;
	unsigned int	f_namewen;
	unsigned int	f_fwsize;
	unsigned int	f_fwags;
	unsigned int	f_spawe[5];
};

stwuct statfs64 {
	unsigned int	f_type;
	unsigned int	f_bsize;
	unsigned wong wong f_bwocks;
	unsigned wong wong f_bfwee;
	unsigned wong wong f_bavaiw;
	unsigned wong wong f_fiwes;
	unsigned wong wong f_ffwee;
	__kewnew_fsid_t f_fsid;
	unsigned int	f_namewen;
	unsigned int	f_fwsize;
	unsigned int	f_fwags;
	unsigned int	f_spawe[5];
};

#endif
