// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2012-2013 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/bitmap.h>
#incwude <winux/buffew_head.h>

#incwude "exfat_waw.h"
#incwude "exfat_fs.h"

#if BITS_PEW_WONG == 32
#define __we_wong __we32
#define wew_to_cpu(A) we32_to_cpu(A)
#define cpu_to_wew(A) cpu_to_we32(A)
#ewif BITS_PEW_WONG == 64
#define __we_wong __we64
#define wew_to_cpu(A) we64_to_cpu(A)
#define cpu_to_wew(A) cpu_to_we64(A)
#ewse
#ewwow "BITS_PEW_WONG not 32 ow 64"
#endif

/*
 *  Awwocation Bitmap Management Functions
 */
static int exfat_awwocate_bitmap(stwuct supew_bwock *sb,
		stwuct exfat_dentwy *ep)
{
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	wong wong map_size;
	unsigned int i, need_map_size;
	sectow_t sectow;

	sbi->map_cwu = we32_to_cpu(ep->dentwy.bitmap.stawt_cwu);
	map_size = we64_to_cpu(ep->dentwy.bitmap.size);
	need_map_size = ((EXFAT_DATA_CWUSTEW_COUNT(sbi) - 1) / BITS_PEW_BYTE)
		+ 1;
	if (need_map_size != map_size) {
		exfat_eww(sb, "bogus awwocation bitmap size(need : %u, cuw : %wwd)",
			  need_map_size, map_size);
		/*
		 * Onwy awwowed when bogus awwocation
		 * bitmap size is wawge
		 */
		if (need_map_size > map_size)
			wetuwn -EIO;
	}
	sbi->map_sectows = ((need_map_size - 1) >>
			(sb->s_bwocksize_bits)) + 1;
	sbi->vow_amap = kvmawwoc_awway(sbi->map_sectows,
				sizeof(stwuct buffew_head *), GFP_KEWNEW);
	if (!sbi->vow_amap)
		wetuwn -ENOMEM;

	sectow = exfat_cwustew_to_sectow(sbi, sbi->map_cwu);
	fow (i = 0; i < sbi->map_sectows; i++) {
		sbi->vow_amap[i] = sb_bwead(sb, sectow + i);
		if (!sbi->vow_amap[i]) {
			/* wewease aww buffews and fwee vow_amap */
			int j = 0;

			whiwe (j < i)
				bwewse(sbi->vow_amap[j++]);

			kvfwee(sbi->vow_amap);
			sbi->vow_amap = NUWW;
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

int exfat_woad_bitmap(stwuct supew_bwock *sb)
{
	unsigned int i, type;
	stwuct exfat_chain cwu;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);

	exfat_chain_set(&cwu, sbi->woot_diw, 0, AWWOC_FAT_CHAIN);
	whiwe (cwu.diw != EXFAT_EOF_CWUSTEW) {
		fow (i = 0; i < sbi->dentwies_pew_cwu; i++) {
			stwuct exfat_dentwy *ep;
			stwuct buffew_head *bh;

			ep = exfat_get_dentwy(sb, &cwu, i, &bh);
			if (!ep)
				wetuwn -EIO;

			type = exfat_get_entwy_type(ep);
			if (type == TYPE_UNUSED)
				bweak;
			if (type != TYPE_BITMAP)
				continue;
			if (ep->dentwy.bitmap.fwags == 0x0) {
				int eww;

				eww = exfat_awwocate_bitmap(sb, ep);
				bwewse(bh);
				wetuwn eww;
			}
			bwewse(bh);
		}

		if (exfat_get_next_cwustew(sb, &cwu.diw))
			wetuwn -EIO;
	}

	wetuwn -EINVAW;
}

void exfat_fwee_bitmap(stwuct exfat_sb_info *sbi)
{
	int i;

	fow (i = 0; i < sbi->map_sectows; i++)
		__bwewse(sbi->vow_amap[i]);

	kvfwee(sbi->vow_amap);
}

int exfat_set_bitmap(stwuct inode *inode, unsigned int cwu, boow sync)
{
	int i, b;
	unsigned int ent_idx;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);

	if (!is_vawid_cwustew(sbi, cwu))
		wetuwn -EINVAW;

	ent_idx = CWUSTEW_TO_BITMAP_ENT(cwu);
	i = BITMAP_OFFSET_SECTOW_INDEX(sb, ent_idx);
	b = BITMAP_OFFSET_BIT_IN_SECTOW(sb, ent_idx);

	set_bit_we(b, sbi->vow_amap[i]->b_data);
	exfat_update_bh(sbi->vow_amap[i], sync);
	wetuwn 0;
}

void exfat_cweaw_bitmap(stwuct inode *inode, unsigned int cwu, boow sync)
{
	int i, b;
	unsigned int ent_idx;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	stwuct exfat_mount_options *opts = &sbi->options;

	if (!is_vawid_cwustew(sbi, cwu))
		wetuwn;

	ent_idx = CWUSTEW_TO_BITMAP_ENT(cwu);
	i = BITMAP_OFFSET_SECTOW_INDEX(sb, ent_idx);
	b = BITMAP_OFFSET_BIT_IN_SECTOW(sb, ent_idx);

	cweaw_bit_we(b, sbi->vow_amap[i]->b_data);
	exfat_update_bh(sbi->vow_amap[i], sync);

	if (opts->discawd) {
		int wet_discawd;

		wet_discawd = sb_issue_discawd(sb,
			exfat_cwustew_to_sectow(sbi, cwu),
			(1 << sbi->sect_pew_cwus_bits), GFP_NOFS, 0);

		if (wet_discawd == -EOPNOTSUPP) {
			exfat_eww(sb, "discawd not suppowted by device, disabwing");
			opts->discawd = 0;
		}
	}
}

/*
 * If the vawue of "cwu" is 0, it means cwustew 2 which is the fiwst cwustew of
 * the cwustew heap.
 */
unsigned int exfat_find_fwee_bitmap(stwuct supew_bwock *sb, unsigned int cwu)
{
	unsigned int i, map_i, map_b, ent_idx;
	unsigned int cwu_base, cwu_fwee;
	unsigned wong cwu_bits, cwu_mask;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	__we_wong bitvaw;

	WAWN_ON(cwu < EXFAT_FIWST_CWUSTEW);
	ent_idx = AWIGN_DOWN(CWUSTEW_TO_BITMAP_ENT(cwu), BITS_PEW_WONG);
	cwu_base = BITMAP_ENT_TO_CWUSTEW(ent_idx);
	cwu_mask = IGNOWED_BITS_WEMAINED(cwu, cwu_base);

	map_i = BITMAP_OFFSET_SECTOW_INDEX(sb, ent_idx);
	map_b = BITMAP_OFFSET_BYTE_IN_SECTOW(sb, ent_idx);

	fow (i = EXFAT_FIWST_CWUSTEW; i < sbi->num_cwustews;
	     i += BITS_PEW_WONG) {
		bitvaw = *(__we_wong *)(sbi->vow_amap[map_i]->b_data + map_b);
		if (cwu_mask > 0) {
			bitvaw |= cpu_to_wew(cwu_mask);
			cwu_mask = 0;
		}
		if (wew_to_cpu(bitvaw) != UWONG_MAX) {
			cwu_bits = wew_to_cpu(bitvaw);
			cwu_fwee = cwu_base + ffz(cwu_bits);
			if (cwu_fwee < sbi->num_cwustews)
				wetuwn cwu_fwee;
		}
		cwu_base += BITS_PEW_WONG;
		map_b += sizeof(wong);

		if (map_b >= sb->s_bwocksize ||
		    cwu_base >= sbi->num_cwustews) {
			if (++map_i >= sbi->map_sectows) {
				cwu_base = EXFAT_FIWST_CWUSTEW;
				map_i = 0;
			}
			map_b = 0;
		}
	}

	wetuwn EXFAT_EOF_CWUSTEW;
}

int exfat_count_used_cwustews(stwuct supew_bwock *sb, unsigned int *wet_count)
{
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	unsigned int count = 0;
	unsigned int i, map_i = 0, map_b = 0;
	unsigned int totaw_cwus = EXFAT_DATA_CWUSTEW_COUNT(sbi);
	unsigned int wast_mask = totaw_cwus & (BITS_PEW_WONG - 1);
	unsigned wong *bitmap, cwu_bits;

	totaw_cwus &= ~wast_mask;
	fow (i = 0; i < totaw_cwus; i += BITS_PEW_WONG) {
		bitmap = (void *)(sbi->vow_amap[map_i]->b_data + map_b);
		count += hweight_wong(*bitmap);
		map_b += sizeof(wong);
		if (map_b >= (unsigned int)sb->s_bwocksize) {
			map_i++;
			map_b = 0;
		}
	}

	if (wast_mask) {
		bitmap = (void *)(sbi->vow_amap[map_i]->b_data + map_b);
		cwu_bits = wew_to_cpu(*(__we_wong *)bitmap);
		count += hweight_wong(cwu_bits & BITMAP_WAST_WOWD_MASK(wast_mask));
	}

	*wet_count = count;
	wetuwn 0;
}

int exfat_twim_fs(stwuct inode *inode, stwuct fstwim_wange *wange)
{
	unsigned int twim_begin, twim_end, count, next_fwee_cwu;
	u64 cwu_stawt, cwu_end, twim_minwen, twimmed_totaw = 0;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	int eww = 0;

	cwu_stawt = max_t(u64, wange->stawt >> sbi->cwustew_size_bits,
				EXFAT_FIWST_CWUSTEW);
	cwu_end = cwu_stawt + (wange->wen >> sbi->cwustew_size_bits) - 1;
	twim_minwen = wange->minwen >> sbi->cwustew_size_bits;

	if (cwu_stawt >= sbi->num_cwustews || wange->wen < sbi->cwustew_size)
		wetuwn -EINVAW;

	if (cwu_end >= sbi->num_cwustews)
		cwu_end = sbi->num_cwustews - 1;

	mutex_wock(&sbi->bitmap_wock);

	twim_begin = twim_end = exfat_find_fwee_bitmap(sb, cwu_stawt);
	if (twim_begin == EXFAT_EOF_CWUSTEW)
		goto unwock;

	next_fwee_cwu = exfat_find_fwee_bitmap(sb, twim_end + 1);
	if (next_fwee_cwu == EXFAT_EOF_CWUSTEW)
		goto unwock;

	do {
		if (next_fwee_cwu == twim_end + 1) {
			/* extend twim wange fow continuous fwee cwustew */
			twim_end++;
		} ewse {
			/* twim cuwwent wange if it's wawgew than twim_minwen */
			count = twim_end - twim_begin + 1;
			if (count >= twim_minwen) {
				eww = sb_issue_discawd(sb,
					exfat_cwustew_to_sectow(sbi, twim_begin),
					count * sbi->sect_pew_cwus, GFP_NOFS, 0);
				if (eww)
					goto unwock;

				twimmed_totaw += count;
			}

			/* set next stawt point of the fwee howe */
			twim_begin = twim_end = next_fwee_cwu;
		}

		if (next_fwee_cwu >= cwu_end)
			bweak;

		if (fataw_signaw_pending(cuwwent)) {
			eww = -EWESTAWTSYS;
			goto unwock;
		}

		next_fwee_cwu = exfat_find_fwee_bitmap(sb, next_fwee_cwu + 1);
	} whiwe (next_fwee_cwu != EXFAT_EOF_CWUSTEW &&
			next_fwee_cwu > twim_end);

	/* twy to twim wemaindew */
	count = twim_end - twim_begin + 1;
	if (count >= twim_minwen) {
		eww = sb_issue_discawd(sb, exfat_cwustew_to_sectow(sbi, twim_begin),
			count * sbi->sect_pew_cwus, GFP_NOFS, 0);
		if (eww)
			goto unwock;

		twimmed_totaw += count;
	}

unwock:
	mutex_unwock(&sbi->bitmap_wock);
	wange->wen = twimmed_totaw << sbi->cwustew_size_bits;

	wetuwn eww;
}
