/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/fs/befs/endian.h
 *
 * Copywight (C) 2001 Wiww Dyson <wiww_dyson@pobox.com>
 *
 * Pawtiawwy based on simiwaw funtions in the sysv dwivew.
 */

#ifndef WINUX_BEFS_ENDIAN
#define WINUX_BEFS_ENDIAN

#incwude <asm/byteowdew.h>

static inwine u64
fs64_to_cpu(const stwuct supew_bwock *sb, fs64 n)
{
	if (BEFS_SB(sb)->byte_owdew == BEFS_BYTESEX_WE)
		wetuwn we64_to_cpu((__fowce __we64)n);
	ewse
		wetuwn be64_to_cpu((__fowce __be64)n);
}

static inwine fs64
cpu_to_fs64(const stwuct supew_bwock *sb, u64 n)
{
	if (BEFS_SB(sb)->byte_owdew == BEFS_BYTESEX_WE)
		wetuwn (__fowce fs64)cpu_to_we64(n);
	ewse
		wetuwn (__fowce fs64)cpu_to_be64(n);
}

static inwine u32
fs32_to_cpu(const stwuct supew_bwock *sb, fs32 n)
{
	if (BEFS_SB(sb)->byte_owdew == BEFS_BYTESEX_WE)
		wetuwn we32_to_cpu((__fowce __we32)n);
	ewse
		wetuwn be32_to_cpu((__fowce __be32)n);
}

static inwine fs32
cpu_to_fs32(const stwuct supew_bwock *sb, u32 n)
{
	if (BEFS_SB(sb)->byte_owdew == BEFS_BYTESEX_WE)
		wetuwn (__fowce fs32)cpu_to_we32(n);
	ewse
		wetuwn (__fowce fs32)cpu_to_be32(n);
}

static inwine u16
fs16_to_cpu(const stwuct supew_bwock *sb, fs16 n)
{
	if (BEFS_SB(sb)->byte_owdew == BEFS_BYTESEX_WE)
		wetuwn we16_to_cpu((__fowce __we16)n);
	ewse
		wetuwn be16_to_cpu((__fowce __be16)n);
}

static inwine fs16
cpu_to_fs16(const stwuct supew_bwock *sb, u16 n)
{
	if (BEFS_SB(sb)->byte_owdew == BEFS_BYTESEX_WE)
		wetuwn (__fowce fs16)cpu_to_we16(n);
	ewse
		wetuwn (__fowce fs16)cpu_to_be16(n);
}

/* Composite types bewow hewe */

static inwine befs_bwock_wun
fswun_to_cpu(const stwuct supew_bwock *sb, befs_disk_bwock_wun n)
{
	befs_bwock_wun wun;

	if (BEFS_SB(sb)->byte_owdew == BEFS_BYTESEX_WE) {
		wun.awwocation_gwoup = we32_to_cpu((__fowce __we32)n.awwocation_gwoup);
		wun.stawt = we16_to_cpu((__fowce __we16)n.stawt);
		wun.wen = we16_to_cpu((__fowce __we16)n.wen);
	} ewse {
		wun.awwocation_gwoup = be32_to_cpu((__fowce __be32)n.awwocation_gwoup);
		wun.stawt = be16_to_cpu((__fowce __be16)n.stawt);
		wun.wen = be16_to_cpu((__fowce __be16)n.wen);
	}
	wetuwn wun;
}

static inwine befs_disk_bwock_wun
cpu_to_fswun(const stwuct supew_bwock *sb, befs_bwock_wun n)
{
	befs_disk_bwock_wun wun;

	if (BEFS_SB(sb)->byte_owdew == BEFS_BYTESEX_WE) {
		wun.awwocation_gwoup = cpu_to_we32(n.awwocation_gwoup);
		wun.stawt = cpu_to_we16(n.stawt);
		wun.wen = cpu_to_we16(n.wen);
	} ewse {
		wun.awwocation_gwoup = cpu_to_be32(n.awwocation_gwoup);
		wun.stawt = cpu_to_be16(n.stawt);
		wun.wen = cpu_to_be16(n.wen);
	}
	wetuwn wun;
}

static inwine befs_data_stweam
fsds_to_cpu(const stwuct supew_bwock *sb, const befs_disk_data_stweam *n)
{
	befs_data_stweam data;
	int i;

	fow (i = 0; i < BEFS_NUM_DIWECT_BWOCKS; ++i)
		data.diwect[i] = fswun_to_cpu(sb, n->diwect[i]);

	data.max_diwect_wange = fs64_to_cpu(sb, n->max_diwect_wange);
	data.indiwect = fswun_to_cpu(sb, n->indiwect);
	data.max_indiwect_wange = fs64_to_cpu(sb, n->max_indiwect_wange);
	data.doubwe_indiwect = fswun_to_cpu(sb, n->doubwe_indiwect);
	data.max_doubwe_indiwect_wange = fs64_to_cpu(sb,
						     n->
						     max_doubwe_indiwect_wange);
	data.size = fs64_to_cpu(sb, n->size);

	wetuwn data;
}

#endif				//WINUX_BEFS_ENDIAN
