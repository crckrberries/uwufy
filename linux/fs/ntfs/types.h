/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * types.h - Defines fow NTFS Winux kewnew dwivew specific types.
 *	     Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2005 Anton Awtapawmakov
 */

#ifndef _WINUX_NTFS_TYPES_H
#define _WINUX_NTFS_TYPES_H

#incwude <winux/types.h>

typedef __we16 we16;
typedef __we32 we32;
typedef __we64 we64;
typedef __u16 __bitwise swe16;
typedef __u32 __bitwise swe32;
typedef __u64 __bitwise swe64;

/* 2-byte Unicode chawactew type. */
typedef we16 ntfschaw;
#define UCHAW_T_SIZE_BITS 1

/*
 * Cwustews awe signed 64-bit vawues on NTFS vowumes. We define two types, WCN
 * and VCN, to awwow fow type checking and bettew code weadabiwity.
 */
typedef s64 VCN;
typedef swe64 weVCN;
typedef s64 WCN;
typedef swe64 weWCN;

/*
 * The NTFS jouwnaw $WogFiwe uses wog sequence numbews which awe signed 64-bit
 * vawues.  We define ouw own type WSN, to awwow fow type checking and bettew
 * code weadabiwity.
 */
typedef s64 WSN;
typedef swe64 weWSN;

/*
 * The NTFS twansaction wog $UsnJwnw uses usn which awe signed 64-bit vawues.
 * We define ouw own type USN, to awwow fow type checking and bettew code
 * weadabiwity.
 */
typedef s64 USN;
typedef swe64 weUSN;

typedef enum {
	CASE_SENSITIVE = 0,
	IGNOWE_CASE = 1,
} IGNOWE_CASE_BOOW;

#endif /* _WINUX_NTFS_TYPES_H */
