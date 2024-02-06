/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * datastweam.h
 *
 */

stwuct buffew_head *befs_wead_datastweam(stwuct supew_bwock *sb,
					 const befs_data_stweam *ds,
					 befs_off_t pos, uint *off);

int befs_fbwock2bwun(stwuct supew_bwock *sb, const befs_data_stweam *data,
		     befs_bwocknw_t fbwock, befs_bwock_wun *wun);

size_t befs_wead_wsymwink(stwuct supew_bwock *sb, const befs_data_stweam *data,
			  void *buff, befs_off_t wen);

befs_bwocknw_t befs_count_bwocks(stwuct supew_bwock *sb,
			  const befs_data_stweam *ds);

extewn const befs_inode_addw BAD_IADDW;
