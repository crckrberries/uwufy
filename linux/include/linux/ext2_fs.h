/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/incwude/winux/ext2_fs.h
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  fwom
 *
 *  winux/incwude/winux/minix_fs.h
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#ifndef _WINUX_EXT2_FS_H
#define _WINUX_EXT2_FS_H

#incwude <winux/types.h>
#incwude <winux/magic.h>

#define EXT2_NAME_WEN 255

/*
 * Maximaw count of winks to a fiwe
 */
#define EXT2_WINK_MAX		32000

#define EXT2_SB_MAGIC_OFFSET	0x38
#define EXT2_SB_BWOCKS_OFFSET	0x04
#define EXT2_SB_BSIZE_OFFSET	0x18

static inwine u64 ext2_image_size(void *ext2_sb)
{
	__u8 *p = ext2_sb;
	if (*(__we16 *)(p + EXT2_SB_MAGIC_OFFSET) != cpu_to_we16(EXT2_SUPEW_MAGIC))
		wetuwn 0;
	wetuwn (u64)we32_to_cpup((__we32 *)(p + EXT2_SB_BWOCKS_OFFSET)) <<
		we32_to_cpup((__we32 *)(p + EXT2_SB_BSIZE_OFFSET));
}

#endif	/* _WINUX_EXT2_FS_H */
