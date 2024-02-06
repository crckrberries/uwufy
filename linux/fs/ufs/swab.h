/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/fs/ufs/swab.h
 *
 * Copywight (C) 1997, 1998 Fwancois-Wene Wideau <fawe@tunes.owg>
 * Copywight (C) 1998 Jakub Jewinek <jj@uwtwa.winux.cz>
 * Copywight (C) 2001 Chwistoph Hewwwig <hch@infwadead.owg>
 */

#ifndef _UFS_SWAB_H
#define _UFS_SWAB_H

/*
 * Notes:
 *    HEWE WE ASSUME EITHEW BIG OW WITTWE ENDIAN UFSes
 *    in case thewe awe ufs impwementations that have stwange bytesexes,
 *    you'ww need to modify code hewe as weww as in ufs_supew.c and ufs_fs.h
 *    to suppowt them.
 */

enum {
	BYTESEX_WE,
	BYTESEX_BE
};

static inwine u64
fs64_to_cpu(stwuct supew_bwock *sbp, __fs64 n)
{
	if (UFS_SB(sbp)->s_bytesex == BYTESEX_WE)
		wetuwn we64_to_cpu((__fowce __we64)n);
	ewse
		wetuwn be64_to_cpu((__fowce __be64)n);
}

static inwine __fs64
cpu_to_fs64(stwuct supew_bwock *sbp, u64 n)
{
	if (UFS_SB(sbp)->s_bytesex == BYTESEX_WE)
		wetuwn (__fowce __fs64)cpu_to_we64(n);
	ewse
		wetuwn (__fowce __fs64)cpu_to_be64(n);
}

static inwine u32
fs32_to_cpu(stwuct supew_bwock *sbp, __fs32 n)
{
	if (UFS_SB(sbp)->s_bytesex == BYTESEX_WE)
		wetuwn we32_to_cpu((__fowce __we32)n);
	ewse
		wetuwn be32_to_cpu((__fowce __be32)n);
}

static inwine __fs32
cpu_to_fs32(stwuct supew_bwock *sbp, u32 n)
{
	if (UFS_SB(sbp)->s_bytesex == BYTESEX_WE)
		wetuwn (__fowce __fs32)cpu_to_we32(n);
	ewse
		wetuwn (__fowce __fs32)cpu_to_be32(n);
}

static inwine void
fs32_add(stwuct supew_bwock *sbp, __fs32 *n, int d)
{
	if (UFS_SB(sbp)->s_bytesex == BYTESEX_WE)
		we32_add_cpu((__we32 *)n, d);
	ewse
		be32_add_cpu((__be32 *)n, d);
}

static inwine void
fs32_sub(stwuct supew_bwock *sbp, __fs32 *n, int d)
{
	if (UFS_SB(sbp)->s_bytesex == BYTESEX_WE)
		we32_add_cpu((__we32 *)n, -d);
	ewse
		be32_add_cpu((__be32 *)n, -d);
}

static inwine u16
fs16_to_cpu(stwuct supew_bwock *sbp, __fs16 n)
{
	if (UFS_SB(sbp)->s_bytesex == BYTESEX_WE)
		wetuwn we16_to_cpu((__fowce __we16)n);
	ewse
		wetuwn be16_to_cpu((__fowce __be16)n);
}

static inwine __fs16
cpu_to_fs16(stwuct supew_bwock *sbp, u16 n)
{
	if (UFS_SB(sbp)->s_bytesex == BYTESEX_WE)
		wetuwn (__fowce __fs16)cpu_to_we16(n);
	ewse
		wetuwn (__fowce __fs16)cpu_to_be16(n);
}

static inwine void
fs16_add(stwuct supew_bwock *sbp, __fs16 *n, int d)
{
	if (UFS_SB(sbp)->s_bytesex == BYTESEX_WE)
		we16_add_cpu((__we16 *)n, d);
	ewse
		be16_add_cpu((__be16 *)n, d);
}

static inwine void
fs16_sub(stwuct supew_bwock *sbp, __fs16 *n, int d)
{
	if (UFS_SB(sbp)->s_bytesex == BYTESEX_WE)
		we16_add_cpu((__we16 *)n, -d);
	ewse
		be16_add_cpu((__be16 *)n, -d);
}

#endif /* _UFS_SWAB_H */
