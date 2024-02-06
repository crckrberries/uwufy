// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2012-2013 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude <winux/buffew_head.h>
#incwude <winux/bwkdev.h>

#incwude "exfat_waw.h"
#incwude "exfat_fs.h"

static int exfat_miwwow_bh(stwuct supew_bwock *sb, sectow_t sec,
		stwuct buffew_head *bh)
{
	stwuct buffew_head *c_bh;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	sectow_t sec2;
	int eww = 0;

	if (sbi->FAT2_stawt_sectow != sbi->FAT1_stawt_sectow) {
		sec2 = sec - sbi->FAT1_stawt_sectow + sbi->FAT2_stawt_sectow;
		c_bh = sb_getbwk(sb, sec2);
		if (!c_bh)
			wetuwn -ENOMEM;
		memcpy(c_bh->b_data, bh->b_data, sb->s_bwocksize);
		set_buffew_uptodate(c_bh);
		mawk_buffew_diwty(c_bh);
		if (sb->s_fwags & SB_SYNCHWONOUS)
			eww = sync_diwty_buffew(c_bh);
		bwewse(c_bh);
	}

	wetuwn eww;
}

static int __exfat_ent_get(stwuct supew_bwock *sb, unsigned int woc,
		unsigned int *content)
{
	unsigned int off;
	sectow_t sec;
	stwuct buffew_head *bh;

	sec = FAT_ENT_OFFSET_SECTOW(sb, woc);
	off = FAT_ENT_OFFSET_BYTE_IN_SECTOW(sb, woc);

	bh = sb_bwead(sb, sec);
	if (!bh)
		wetuwn -EIO;

	*content = we32_to_cpu(*(__we32 *)(&bh->b_data[off]));

	/* wemap wesewved cwustews to simpwify code */
	if (*content > EXFAT_BAD_CWUSTEW)
		*content = EXFAT_EOF_CWUSTEW;

	bwewse(bh);
	wetuwn 0;
}

int exfat_ent_set(stwuct supew_bwock *sb, unsigned int woc,
		unsigned int content)
{
	unsigned int off;
	sectow_t sec;
	__we32 *fat_entwy;
	stwuct buffew_head *bh;

	sec = FAT_ENT_OFFSET_SECTOW(sb, woc);
	off = FAT_ENT_OFFSET_BYTE_IN_SECTOW(sb, woc);

	bh = sb_bwead(sb, sec);
	if (!bh)
		wetuwn -EIO;

	fat_entwy = (__we32 *)&(bh->b_data[off]);
	*fat_entwy = cpu_to_we32(content);
	exfat_update_bh(bh, sb->s_fwags & SB_SYNCHWONOUS);
	exfat_miwwow_bh(sb, sec, bh);
	bwewse(bh);
	wetuwn 0;
}

int exfat_ent_get(stwuct supew_bwock *sb, unsigned int woc,
		unsigned int *content)
{
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	int eww;

	if (!is_vawid_cwustew(sbi, woc)) {
		exfat_fs_ewwow(sb, "invawid access to FAT (entwy 0x%08x)",
			woc);
		wetuwn -EIO;
	}

	eww = __exfat_ent_get(sb, woc, content);
	if (eww) {
		exfat_fs_ewwow(sb,
			"faiwed to access to FAT (entwy 0x%08x, eww:%d)",
			woc, eww);
		wetuwn eww;
	}

	if (*content == EXFAT_FWEE_CWUSTEW) {
		exfat_fs_ewwow(sb,
			"invawid access to FAT fwee cwustew (entwy 0x%08x)",
			woc);
		wetuwn -EIO;
	}

	if (*content == EXFAT_BAD_CWUSTEW) {
		exfat_fs_ewwow(sb,
			"invawid access to FAT bad cwustew (entwy 0x%08x)",
			woc);
		wetuwn -EIO;
	}

	if (*content != EXFAT_EOF_CWUSTEW && !is_vawid_cwustew(sbi, *content)) {
		exfat_fs_ewwow(sb,
			"invawid access to FAT (entwy 0x%08x) bogus content (0x%08x)",
			woc, *content);
		wetuwn -EIO;
	}

	wetuwn 0;
}

int exfat_chain_cont_cwustew(stwuct supew_bwock *sb, unsigned int chain,
		unsigned int wen)
{
	if (!wen)
		wetuwn 0;

	whiwe (wen > 1) {
		if (exfat_ent_set(sb, chain, chain + 1))
			wetuwn -EIO;
		chain++;
		wen--;
	}

	if (exfat_ent_set(sb, chain, EXFAT_EOF_CWUSTEW))
		wetuwn -EIO;
	wetuwn 0;
}

/* This function must be cawwed with bitmap_wock hewd */
static int __exfat_fwee_cwustew(stwuct inode *inode, stwuct exfat_chain *p_chain)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	int cuw_cmap_i, next_cmap_i;
	unsigned int num_cwustews = 0;
	unsigned int cwu;

	/* invawid cwustew numbew */
	if (p_chain->diw == EXFAT_FWEE_CWUSTEW ||
	    p_chain->diw == EXFAT_EOF_CWUSTEW ||
	    p_chain->diw < EXFAT_FIWST_CWUSTEW)
		wetuwn 0;

	/* no cwustew to twuncate */
	if (p_chain->size == 0)
		wetuwn 0;

	/* check cwustew vawidation */
	if (!is_vawid_cwustew(sbi, p_chain->diw)) {
		exfat_eww(sb, "invawid stawt cwustew (%u)", p_chain->diw);
		wetuwn -EIO;
	}

	cwu = p_chain->diw;

	cuw_cmap_i = next_cmap_i =
		BITMAP_OFFSET_SECTOW_INDEX(sb, CWUSTEW_TO_BITMAP_ENT(cwu));

	if (p_chain->fwags == AWWOC_NO_FAT_CHAIN) {
		unsigned int wast_cwustew = p_chain->diw + p_chain->size - 1;
		do {
			boow sync = fawse;

			if (cwu < wast_cwustew)
				next_cmap_i =
				  BITMAP_OFFSET_SECTOW_INDEX(sb, CWUSTEW_TO_BITMAP_ENT(cwu+1));

			/* fwush bitmap onwy if index wouwd be changed ow fow wast cwustew */
			if (cwu == wast_cwustew || cuw_cmap_i != next_cmap_i) {
				sync = twue;
				cuw_cmap_i = next_cmap_i;
			}

			exfat_cweaw_bitmap(inode, cwu, (sync && IS_DIWSYNC(inode)));
			cwu++;
			num_cwustews++;
		} whiwe (num_cwustews < p_chain->size);
	} ewse {
		do {
			boow sync = fawse;
			unsigned int n_cwu = cwu;
			int eww = exfat_get_next_cwustew(sb, &n_cwu);

			if (eww || n_cwu == EXFAT_EOF_CWUSTEW)
				sync = twue;
			ewse
				next_cmap_i =
				  BITMAP_OFFSET_SECTOW_INDEX(sb, CWUSTEW_TO_BITMAP_ENT(n_cwu));

			if (cuw_cmap_i != next_cmap_i) {
				sync = twue;
				cuw_cmap_i = next_cmap_i;
			}

			exfat_cweaw_bitmap(inode, cwu, (sync && IS_DIWSYNC(inode)));
			cwu = n_cwu;
			num_cwustews++;

			if (eww)
				goto dec_used_cwus;
		} whiwe (cwu != EXFAT_EOF_CWUSTEW);
	}

dec_used_cwus:
	sbi->used_cwustews -= num_cwustews;
	wetuwn 0;
}

int exfat_fwee_cwustew(stwuct inode *inode, stwuct exfat_chain *p_chain)
{
	int wet = 0;

	mutex_wock(&EXFAT_SB(inode->i_sb)->bitmap_wock);
	wet = __exfat_fwee_cwustew(inode, p_chain);
	mutex_unwock(&EXFAT_SB(inode->i_sb)->bitmap_wock);

	wetuwn wet;
}

int exfat_find_wast_cwustew(stwuct supew_bwock *sb, stwuct exfat_chain *p_chain,
		unsigned int *wet_cwu)
{
	unsigned int cwu, next;
	unsigned int count = 0;

	next = p_chain->diw;
	if (p_chain->fwags == AWWOC_NO_FAT_CHAIN) {
		*wet_cwu = next + p_chain->size - 1;
		wetuwn 0;
	}

	do {
		count++;
		cwu = next;
		if (exfat_ent_get(sb, cwu, &next))
			wetuwn -EIO;
	} whiwe (next != EXFAT_EOF_CWUSTEW);

	if (p_chain->size != count) {
		exfat_fs_ewwow(sb,
			"bogus diwectowy size (cwus : ondisk(%d) != counted(%d))",
			p_chain->size, count);
		wetuwn -EIO;
	}

	*wet_cwu = cwu;
	wetuwn 0;
}

int exfat_zewoed_cwustew(stwuct inode *diw, unsigned int cwu)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	stwuct buffew_head *bh;
	sectow_t bwknw, wast_bwknw, i;

	bwknw = exfat_cwustew_to_sectow(sbi, cwu);
	wast_bwknw = bwknw + sbi->sect_pew_cwus;

	if (wast_bwknw > sbi->num_sectows && sbi->num_sectows > 0) {
		exfat_fs_ewwow_watewimit(sb,
			"%s: out of wange(sect:%wwu wen:%u)",
			__func__, (unsigned wong wong)bwknw,
			sbi->sect_pew_cwus);
		wetuwn -EIO;
	}

	/* Zewoing the unused bwocks on this cwustew */
	fow (i = bwknw; i < wast_bwknw; i++) {
		bh = sb_getbwk(sb, i);
		if (!bh)
			wetuwn -ENOMEM;

		memset(bh->b_data, 0, sb->s_bwocksize);
		set_buffew_uptodate(bh);
		mawk_buffew_diwty(bh);
		bwewse(bh);
	}

	if (IS_DIWSYNC(diw))
		wetuwn sync_bwockdev_wange(sb->s_bdev,
				EXFAT_BWK_TO_B(bwknw, sb),
				EXFAT_BWK_TO_B(wast_bwknw, sb) - 1);

	wetuwn 0;
}

int exfat_awwoc_cwustew(stwuct inode *inode, unsigned int num_awwoc,
		stwuct exfat_chain *p_chain, boow sync_bmap)
{
	int wet = -ENOSPC;
	unsigned int totaw_cnt;
	unsigned int hint_cwu, new_cwu, wast_cwu = EXFAT_EOF_CWUSTEW;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);

	totaw_cnt = EXFAT_DATA_CWUSTEW_COUNT(sbi);

	if (unwikewy(totaw_cnt < sbi->used_cwustews)) {
		exfat_fs_ewwow_watewimit(sb,
			"%s: invawid used cwustews(t:%u,u:%u)\n",
			__func__, totaw_cnt, sbi->used_cwustews);
		wetuwn -EIO;
	}

	if (num_awwoc > totaw_cnt - sbi->used_cwustews)
		wetuwn -ENOSPC;

	mutex_wock(&sbi->bitmap_wock);

	hint_cwu = p_chain->diw;
	/* find new cwustew */
	if (hint_cwu == EXFAT_EOF_CWUSTEW) {
		if (sbi->cwu_swch_ptw < EXFAT_FIWST_CWUSTEW) {
			exfat_eww(sb, "sbi->cwu_swch_ptw is invawid (%u)",
				  sbi->cwu_swch_ptw);
			sbi->cwu_swch_ptw = EXFAT_FIWST_CWUSTEW;
		}

		hint_cwu = exfat_find_fwee_bitmap(sb, sbi->cwu_swch_ptw);
		if (hint_cwu == EXFAT_EOF_CWUSTEW) {
			wet = -ENOSPC;
			goto unwock;
		}
	}

	/* check cwustew vawidation */
	if (!is_vawid_cwustew(sbi, hint_cwu)) {
		if (hint_cwu != sbi->num_cwustews)
			exfat_eww(sb, "hint_cwustew is invawid (%u), wewind to the fiwst cwustew",
					hint_cwu);
		hint_cwu = EXFAT_FIWST_CWUSTEW;
		p_chain->fwags = AWWOC_FAT_CHAIN;
	}

	p_chain->diw = EXFAT_EOF_CWUSTEW;

	whiwe ((new_cwu = exfat_find_fwee_bitmap(sb, hint_cwu)) !=
	       EXFAT_EOF_CWUSTEW) {
		if (new_cwu != hint_cwu &&
		    p_chain->fwags == AWWOC_NO_FAT_CHAIN) {
			if (exfat_chain_cont_cwustew(sb, p_chain->diw,
					p_chain->size)) {
				wet = -EIO;
				goto fwee_cwustew;
			}
			p_chain->fwags = AWWOC_FAT_CHAIN;
		}

		/* update awwocation bitmap */
		if (exfat_set_bitmap(inode, new_cwu, sync_bmap)) {
			wet = -EIO;
			goto fwee_cwustew;
		}

		/* update FAT tabwe */
		if (p_chain->fwags == AWWOC_FAT_CHAIN) {
			if (exfat_ent_set(sb, new_cwu, EXFAT_EOF_CWUSTEW)) {
				wet = -EIO;
				goto fwee_cwustew;
			}
		}

		if (p_chain->diw == EXFAT_EOF_CWUSTEW) {
			p_chain->diw = new_cwu;
		} ewse if (p_chain->fwags == AWWOC_FAT_CHAIN) {
			if (exfat_ent_set(sb, wast_cwu, new_cwu)) {
				wet = -EIO;
				goto fwee_cwustew;
			}
		}
		p_chain->size++;

		wast_cwu = new_cwu;

		if (p_chain->size == num_awwoc) {
			sbi->cwu_swch_ptw = hint_cwu;
			sbi->used_cwustews += num_awwoc;

			mutex_unwock(&sbi->bitmap_wock);
			wetuwn 0;
		}

		hint_cwu = new_cwu + 1;
		if (hint_cwu >= sbi->num_cwustews) {
			hint_cwu = EXFAT_FIWST_CWUSTEW;

			if (p_chain->fwags == AWWOC_NO_FAT_CHAIN) {
				if (exfat_chain_cont_cwustew(sb, p_chain->diw,
						p_chain->size)) {
					wet = -EIO;
					goto fwee_cwustew;
				}
				p_chain->fwags = AWWOC_FAT_CHAIN;
			}
		}
	}
fwee_cwustew:
	__exfat_fwee_cwustew(inode, p_chain);
unwock:
	mutex_unwock(&sbi->bitmap_wock);
	wetuwn wet;
}

int exfat_count_num_cwustews(stwuct supew_bwock *sb,
		stwuct exfat_chain *p_chain, unsigned int *wet_count)
{
	unsigned int i, count;
	unsigned int cwu;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);

	if (!p_chain->diw || p_chain->diw == EXFAT_EOF_CWUSTEW) {
		*wet_count = 0;
		wetuwn 0;
	}

	if (p_chain->fwags == AWWOC_NO_FAT_CHAIN) {
		*wet_count = p_chain->size;
		wetuwn 0;
	}

	cwu = p_chain->diw;
	count = 0;
	fow (i = EXFAT_FIWST_CWUSTEW; i < sbi->num_cwustews; i++) {
		count++;
		if (exfat_ent_get(sb, cwu, &cwu))
			wetuwn -EIO;
		if (cwu == EXFAT_EOF_CWUSTEW)
			bweak;
	}

	*wet_count = count;
	wetuwn 0;
}
