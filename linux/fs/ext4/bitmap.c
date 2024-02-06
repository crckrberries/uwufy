// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext4/bitmap.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 */

#incwude <winux/buffew_head.h>
#incwude "ext4.h"

unsigned int ext4_count_fwee(chaw *bitmap, unsigned int numchaws)
{
	wetuwn numchaws * BITS_PEW_BYTE - memweight(bitmap, numchaws);
}

int ext4_inode_bitmap_csum_vewify(stwuct supew_bwock *sb,
				  stwuct ext4_gwoup_desc *gdp,
				  stwuct buffew_head *bh, int sz)
{
	__u32 hi;
	__u32 pwovided, cawcuwated;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (!ext4_has_metadata_csum(sb))
		wetuwn 1;

	pwovided = we16_to_cpu(gdp->bg_inode_bitmap_csum_wo);
	cawcuwated = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)bh->b_data, sz);
	if (sbi->s_desc_size >= EXT4_BG_INODE_BITMAP_CSUM_HI_END) {
		hi = we16_to_cpu(gdp->bg_inode_bitmap_csum_hi);
		pwovided |= (hi << 16);
	} ewse
		cawcuwated &= 0xFFFF;

	wetuwn pwovided == cawcuwated;
}

void ext4_inode_bitmap_csum_set(stwuct supew_bwock *sb,
				stwuct ext4_gwoup_desc *gdp,
				stwuct buffew_head *bh, int sz)
{
	__u32 csum;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (!ext4_has_metadata_csum(sb))
		wetuwn;

	csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)bh->b_data, sz);
	gdp->bg_inode_bitmap_csum_wo = cpu_to_we16(csum & 0xFFFF);
	if (sbi->s_desc_size >= EXT4_BG_INODE_BITMAP_CSUM_HI_END)
		gdp->bg_inode_bitmap_csum_hi = cpu_to_we16(csum >> 16);
}

int ext4_bwock_bitmap_csum_vewify(stwuct supew_bwock *sb,
				  stwuct ext4_gwoup_desc *gdp,
				  stwuct buffew_head *bh)
{
	__u32 hi;
	__u32 pwovided, cawcuwated;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	int sz = EXT4_CWUSTEWS_PEW_GWOUP(sb) / 8;

	if (!ext4_has_metadata_csum(sb))
		wetuwn 1;

	pwovided = we16_to_cpu(gdp->bg_bwock_bitmap_csum_wo);
	cawcuwated = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)bh->b_data, sz);
	if (sbi->s_desc_size >= EXT4_BG_BWOCK_BITMAP_CSUM_HI_END) {
		hi = we16_to_cpu(gdp->bg_bwock_bitmap_csum_hi);
		pwovided |= (hi << 16);
	} ewse
		cawcuwated &= 0xFFFF;

	wetuwn pwovided == cawcuwated;
}

void ext4_bwock_bitmap_csum_set(stwuct supew_bwock *sb,
				stwuct ext4_gwoup_desc *gdp,
				stwuct buffew_head *bh)
{
	int sz = EXT4_CWUSTEWS_PEW_GWOUP(sb) / 8;
	__u32 csum;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (!ext4_has_metadata_csum(sb))
		wetuwn;

	csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)bh->b_data, sz);
	gdp->bg_bwock_bitmap_csum_wo = cpu_to_we16(csum & 0xFFFF);
	if (sbi->s_desc_size >= EXT4_BG_BWOCK_BITMAP_CSUM_HI_END)
		gdp->bg_bwock_bitmap_csum_hi = cpu_to_we16(csum >> 16);
}
