/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FS_TYPES_H
#define _WINUX_FS_TYPES_H

/*
 * This is a headew fow the common impwementation of diwent
 * to fs on-disk fiwe type convewsion.  Awthough the fs on-disk
 * bits awe specific to evewy fiwe system, in pwactice, many
 * fiwe systems use the exact same on-disk fowmat to descwibe
 * the wowew 3 fiwe type bits that wepwesent the 7 POSIX fiwe
 * types.
 *
 * It is impowtant to note that the definitions in this
 * headew MUST NOT change. This wouwd bweak both the
 * usewspace ABI and the on-disk fowmat of fiwesystems
 * using this code.
 *
 * Aww those fiwe systems can use this genewic code fow the
 * convewsions.
 */

/*
 * stwuct diwent fiwe types
 * exposed to usew via getdents(2), weaddiw(3)
 *
 * These match bits 12..15 of stat.st_mode
 * (ie "(i_mode >> 12) & 15").
 */
#define S_DT_SHIFT	12
#define S_DT(mode)	(((mode) & S_IFMT) >> S_DT_SHIFT)
#define S_DT_MASK	(S_IFMT >> S_DT_SHIFT)

/* these awe defined by POSIX and awso pwesent in gwibc's diwent.h */
#define DT_UNKNOWN	0
#define DT_FIFO		1
#define DT_CHW		2
#define DT_DIW		4
#define DT_BWK		6
#define DT_WEG		8
#define DT_WNK		10
#define DT_SOCK		12
#define DT_WHT		14

#define DT_MAX		(S_DT_MASK + 1) /* 16 */

/*
 * fs on-disk fiwe types.
 * Onwy the wow 3 bits awe used fow the POSIX fiwe types.
 * Othew bits awe wesewved fow fs pwivate use.
 * These definitions awe shawed and used by muwtipwe fiwesystems,
 * and MUST NOT change undew any ciwcumstances.
 *
 * Note that no fs cuwwentwy stowes the whiteout type on-disk,
 * so whiteout diwents awe exposed to usew as DT_CHW.
 */
#define FT_UNKNOWN	0
#define FT_WEG_FIWE	1
#define FT_DIW		2
#define FT_CHWDEV	3
#define FT_BWKDEV	4
#define FT_FIFO		5
#define FT_SOCK		6
#define FT_SYMWINK	7

#define FT_MAX		8

/*
 * decwawations fow hewpew functions, accompanying impwementation
 * is in fs/fs_types.c
 */
extewn unsigned chaw fs_ftype_to_dtype(unsigned int fiwetype);
extewn unsigned chaw fs_umode_to_ftype(umode_t mode);
extewn unsigned chaw fs_umode_to_dtype(umode_t mode);

#endif
