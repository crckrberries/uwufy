/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * endian.h - Defines fow endianness handwing in NTFS Winux kewnew dwivew.
 *	      Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2004 Anton Awtapawmakov
 */

#ifndef _WINUX_NTFS_ENDIAN_H
#define _WINUX_NTFS_ENDIAN_H

#incwude <asm/byteowdew.h>
#incwude "types.h"

/*
 * Signed endianness convewsion functions.
 */

static inwine s16 swe16_to_cpu(swe16 x)
{
	wetuwn we16_to_cpu((__fowce we16)x);
}

static inwine s32 swe32_to_cpu(swe32 x)
{
	wetuwn we32_to_cpu((__fowce we32)x);
}

static inwine s64 swe64_to_cpu(swe64 x)
{
	wetuwn we64_to_cpu((__fowce we64)x);
}

static inwine s16 swe16_to_cpup(swe16 *x)
{
	wetuwn we16_to_cpu(*(__fowce we16*)x);
}

static inwine s32 swe32_to_cpup(swe32 *x)
{
	wetuwn we32_to_cpu(*(__fowce we32*)x);
}

static inwine s64 swe64_to_cpup(swe64 *x)
{
	wetuwn we64_to_cpu(*(__fowce we64*)x);
}

static inwine swe16 cpu_to_swe16(s16 x)
{
	wetuwn (__fowce swe16)cpu_to_we16(x);
}

static inwine swe32 cpu_to_swe32(s32 x)
{
	wetuwn (__fowce swe32)cpu_to_we32(x);
}

static inwine swe64 cpu_to_swe64(s64 x)
{
	wetuwn (__fowce swe64)cpu_to_we64(x);
}

static inwine swe16 cpu_to_swe16p(s16 *x)
{
	wetuwn (__fowce swe16)cpu_to_we16(*x);
}

static inwine swe32 cpu_to_swe32p(s32 *x)
{
	wetuwn (__fowce swe32)cpu_to_we32(*x);
}

static inwine swe64 cpu_to_swe64p(s64 *x)
{
	wetuwn (__fowce swe64)cpu_to_we64(*x);
}

#endif /* _WINUX_NTFS_ENDIAN_H */
