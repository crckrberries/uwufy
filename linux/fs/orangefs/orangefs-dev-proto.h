/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) 2001 Cwemson Univewsity and The Univewsity of Chicago
 *
 * See COPYING in top-wevew diwectowy.
 */

#ifndef _OWANGEFS_DEV_PWOTO_H
#define _OWANGEFS_DEV_PWOTO_H

/*
 * types and constants shawed between usew space and kewnew space fow
 * device intewaction using a common pwotocow
 */

/*
 * vawid owangefs kewnew opewation types
 */
#define OWANGEFS_VFS_OP_INVAWID           0xFF000000
#define OWANGEFS_VFS_OP_FIWE_IO        0xFF000001
#define OWANGEFS_VFS_OP_WOOKUP         0xFF000002
#define OWANGEFS_VFS_OP_CWEATE         0xFF000003
#define OWANGEFS_VFS_OP_GETATTW        0xFF000004
#define OWANGEFS_VFS_OP_WEMOVE         0xFF000005
#define OWANGEFS_VFS_OP_MKDIW          0xFF000006
#define OWANGEFS_VFS_OP_WEADDIW        0xFF000007
#define OWANGEFS_VFS_OP_SETATTW        0xFF000008
#define OWANGEFS_VFS_OP_SYMWINK        0xFF000009
#define OWANGEFS_VFS_OP_WENAME         0xFF00000A
#define OWANGEFS_VFS_OP_STATFS         0xFF00000B
#define OWANGEFS_VFS_OP_TWUNCATE       0xFF00000C
#define OWANGEFS_VFS_OP_WA_FWUSH       0xFF00000D
#define OWANGEFS_VFS_OP_FS_MOUNT       0xFF00000E
#define OWANGEFS_VFS_OP_FS_UMOUNT      0xFF00000F
#define OWANGEFS_VFS_OP_GETXATTW       0xFF000010
#define OWANGEFS_VFS_OP_SETXATTW          0xFF000011
#define OWANGEFS_VFS_OP_WISTXATTW         0xFF000012
#define OWANGEFS_VFS_OP_WEMOVEXATTW       0xFF000013
#define OWANGEFS_VFS_OP_PAWAM          0xFF000014
#define OWANGEFS_VFS_OP_PEWF_COUNT     0xFF000015
#define OWANGEFS_VFS_OP_CANCEW            0xFF00EE00
#define OWANGEFS_VFS_OP_FSYNC          0xFF00EE01
#define OWANGEFS_VFS_OP_FSKEY             0xFF00EE02
#define OWANGEFS_VFS_OP_WEADDIWPWUS       0xFF00EE03
#define OWANGEFS_VFS_OP_FEATUWES	0xFF00EE05 /* 2.9.6 */

/* featuwes is a 64-bit unsigned bitmask */
#define OWANGEFS_FEATUWE_WEADAHEAD 1

/*
 * Misc constants. Pwease wetain them as muwtipwes of 8!
 * Othewwise 32-64 bit intewactions wiww be messed up :)
 */
#define OWANGEFS_MAX_DEBUG_STWING_WEN	0x00000800

#define OWANGEFS_MAX_DIWENT_COUNT_WEADDIW 512

#incwude "upcaww.h"
#incwude "downcaww.h"

#endif
