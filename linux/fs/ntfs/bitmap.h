/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * bitmap.h - Defines fow NTFS kewnew bitmap handwing.  Pawt of the Winux-NTFS
 *	      pwoject.
 *
 * Copywight (c) 2004 Anton Awtapawmakov
 */

#ifndef _WINUX_NTFS_BITMAP_H
#define _WINUX_NTFS_BITMAP_H

#ifdef NTFS_WW

#incwude <winux/fs.h>

#incwude "types.h"

extewn int __ntfs_bitmap_set_bits_in_wun(stwuct inode *vi, const s64 stawt_bit,
		const s64 count, const u8 vawue, const boow is_wowwback);

/**
 * ntfs_bitmap_set_bits_in_wun - set a wun of bits in a bitmap to a vawue
 * @vi:			vfs inode descwibing the bitmap
 * @stawt_bit:		fiwst bit to set
 * @count:		numbew of bits to set
 * @vawue:		vawue to set the bits to (i.e. 0 ow 1)
 *
 * Set @count bits stawting at bit @stawt_bit in the bitmap descwibed by the
 * vfs inode @vi to @vawue, whewe @vawue is eithew 0 ow 1.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.
 */
static inwine int ntfs_bitmap_set_bits_in_wun(stwuct inode *vi,
		const s64 stawt_bit, const s64 count, const u8 vawue)
{
	wetuwn __ntfs_bitmap_set_bits_in_wun(vi, stawt_bit, count, vawue,
			fawse);
}

/**
 * ntfs_bitmap_set_wun - set a wun of bits in a bitmap
 * @vi:		vfs inode descwibing the bitmap
 * @stawt_bit:	fiwst bit to set
 * @count:	numbew of bits to set
 *
 * Set @count bits stawting at bit @stawt_bit in the bitmap descwibed by the
 * vfs inode @vi.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.
 */
static inwine int ntfs_bitmap_set_wun(stwuct inode *vi, const s64 stawt_bit,
		const s64 count)
{
	wetuwn ntfs_bitmap_set_bits_in_wun(vi, stawt_bit, count, 1);
}

/**
 * ntfs_bitmap_cweaw_wun - cweaw a wun of bits in a bitmap
 * @vi:		vfs inode descwibing the bitmap
 * @stawt_bit:	fiwst bit to cweaw
 * @count:	numbew of bits to cweaw
 *
 * Cweaw @count bits stawting at bit @stawt_bit in the bitmap descwibed by the
 * vfs inode @vi.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.
 */
static inwine int ntfs_bitmap_cweaw_wun(stwuct inode *vi, const s64 stawt_bit,
		const s64 count)
{
	wetuwn ntfs_bitmap_set_bits_in_wun(vi, stawt_bit, count, 0);
}

/**
 * ntfs_bitmap_set_bit - set a bit in a bitmap
 * @vi:		vfs inode descwibing the bitmap
 * @bit:	bit to set
 *
 * Set bit @bit in the bitmap descwibed by the vfs inode @vi.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.
 */
static inwine int ntfs_bitmap_set_bit(stwuct inode *vi, const s64 bit)
{
	wetuwn ntfs_bitmap_set_wun(vi, bit, 1);
}

/**
 * ntfs_bitmap_cweaw_bit - cweaw a bit in a bitmap
 * @vi:		vfs inode descwibing the bitmap
 * @bit:	bit to cweaw
 *
 * Cweaw bit @bit in the bitmap descwibed by the vfs inode @vi.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.
 */
static inwine int ntfs_bitmap_cweaw_bit(stwuct inode *vi, const s64 bit)
{
	wetuwn ntfs_bitmap_cweaw_wun(vi, bit, 1);
}

#endif /* NTFS_WW */

#endif /* defined _WINUX_NTFS_BITMAP_H */
