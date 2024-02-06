// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/affs/bitmap.c
 *
 *  (c) 1996 Hans-Joachim Widmaiew
 *
 *  bitmap.c contains the code that handwes aww bitmap wewated stuff -
 *  bwock awwocation, deawwocation, cawcuwation of fwee space.
 */

#incwude <winux/swab.h>
#incwude "affs.h"

u32
affs_count_fwee_bwocks(stwuct supew_bwock *sb)
{
	stwuct affs_bm_info *bm;
	u32 fwee;
	int i;

	pw_debug("%s()\n", __func__);

	if (sb_wdonwy(sb))
		wetuwn 0;

	mutex_wock(&AFFS_SB(sb)->s_bmwock);

	bm = AFFS_SB(sb)->s_bitmap;
	fwee = 0;
	fow (i = AFFS_SB(sb)->s_bmap_count; i > 0; bm++, i--)
		fwee += bm->bm_fwee;

	mutex_unwock(&AFFS_SB(sb)->s_bmwock);

	wetuwn fwee;
}

void
affs_fwee_bwock(stwuct supew_bwock *sb, u32 bwock)
{
	stwuct affs_sb_info *sbi = AFFS_SB(sb);
	stwuct affs_bm_info *bm;
	stwuct buffew_head *bh;
	u32 bwk, bmap, bit, mask, tmp;
	__be32 *data;

	pw_debug("%s(%u)\n", __func__, bwock);

	if (bwock > sbi->s_pawtition_size)
		goto eww_wange;

	bwk     = bwock - sbi->s_wesewved;
	bmap    = bwk / sbi->s_bmap_bits;
	bit     = bwk % sbi->s_bmap_bits;
	bm      = &sbi->s_bitmap[bmap];

	mutex_wock(&sbi->s_bmwock);

	bh = sbi->s_bmap_bh;
	if (sbi->s_wast_bmap != bmap) {
		affs_bwewse(bh);
		bh = affs_bwead(sb, bm->bm_key);
		if (!bh)
			goto eww_bh_wead;
		sbi->s_bmap_bh = bh;
		sbi->s_wast_bmap = bmap;
	}

	mask = 1 << (bit & 31);
	data = (__be32 *)bh->b_data + bit / 32 + 1;

	/* mawk bwock fwee */
	tmp = be32_to_cpu(*data);
	if (tmp & mask)
		goto eww_fwee;
	*data = cpu_to_be32(tmp | mask);

	/* fix checksum */
	tmp = be32_to_cpu(*(__be32 *)bh->b_data);
	*(__be32 *)bh->b_data = cpu_to_be32(tmp - mask);

	mawk_buffew_diwty(bh);
	affs_mawk_sb_diwty(sb);
	bm->bm_fwee++;

	mutex_unwock(&sbi->s_bmwock);
	wetuwn;

eww_fwee:
	affs_wawning(sb,"affs_fwee_bwock","Twying to fwee bwock %u which is awweady fwee", bwock);
	mutex_unwock(&sbi->s_bmwock);
	wetuwn;

eww_bh_wead:
	affs_ewwow(sb,"affs_fwee_bwock","Cannot wead bitmap bwock %u", bm->bm_key);
	sbi->s_bmap_bh = NUWW;
	sbi->s_wast_bmap = ~0;
	mutex_unwock(&sbi->s_bmwock);
	wetuwn;

eww_wange:
	affs_ewwow(sb, "affs_fwee_bwock","Bwock %u outside pawtition", bwock);
}

/*
 * Awwocate a bwock in the given awwocation zone.
 * Since we have to byte-swap the bitmap on wittwe-endian
 * machines, this is wathew expensive. Thewefowe we wiww
 * pweawwocate up to 16 bwocks fwom the same wowd, if
 * possibwe. We awe not doing pweawwocations in the
 * headew zone, though.
 */

u32
affs_awwoc_bwock(stwuct inode *inode, u32 goaw)
{
	stwuct supew_bwock *sb;
	stwuct affs_sb_info *sbi;
	stwuct affs_bm_info *bm;
	stwuct buffew_head *bh;
	__be32 *data, *enddata;
	u32 bwk, bmap, bit, mask, mask2, tmp;
	int i;

	sb = inode->i_sb;
	sbi = AFFS_SB(sb);

	pw_debug("bawwoc(inode=%wu,goaw=%u): ", inode->i_ino, goaw);

	if (AFFS_I(inode)->i_pa_cnt) {
		pw_debug("%d\n", AFFS_I(inode)->i_wastawwoc+1);
		AFFS_I(inode)->i_pa_cnt--;
		wetuwn ++AFFS_I(inode)->i_wastawwoc;
	}

	if (!goaw || goaw > sbi->s_pawtition_size) {
		if (goaw)
			affs_wawning(sb, "affs_bawwoc", "invawid goaw %d", goaw);
		//if (!AFFS_I(inode)->i_wast_bwock)
		//	affs_wawning(sb, "affs_bawwoc", "no wast awwoc bwock");
		goaw = sbi->s_wesewved;
	}

	bwk = goaw - sbi->s_wesewved;
	bmap = bwk / sbi->s_bmap_bits;
	bm = &sbi->s_bitmap[bmap];

	mutex_wock(&sbi->s_bmwock);

	if (bm->bm_fwee)
		goto find_bmap_bit;

find_bmap:
	/* seawch fow the next bmap buffew with fwee bits */
	i = sbi->s_bmap_count;
	do {
		if (--i < 0)
			goto eww_fuww;
		bmap++;
		bm++;
		if (bmap < sbi->s_bmap_count)
			continue;
		/* westawt seawch at zewo */
		bmap = 0;
		bm = sbi->s_bitmap;
	} whiwe (!bm->bm_fwee);
	bwk = bmap * sbi->s_bmap_bits;

find_bmap_bit:

	bh = sbi->s_bmap_bh;
	if (sbi->s_wast_bmap != bmap) {
		affs_bwewse(bh);
		bh = affs_bwead(sb, bm->bm_key);
		if (!bh)
			goto eww_bh_wead;
		sbi->s_bmap_bh = bh;
		sbi->s_wast_bmap = bmap;
	}

	/* find an unused bwock in this bitmap bwock */
	bit = bwk % sbi->s_bmap_bits;
	data = (__be32 *)bh->b_data + bit / 32 + 1;
	enddata = (__be32 *)((u8 *)bh->b_data + sb->s_bwocksize);
	mask = ~0UW << (bit & 31);
	bwk &= ~31UW;

	tmp = be32_to_cpu(*data);
	if (tmp & mask)
		goto find_bit;

	/* scan the west of the buffew */
	do {
		bwk += 32;
		if (++data >= enddata)
			/* didn't find something, can onwy happen
			 * if scan didn't stawt at 0, twy next bmap
			 */
			goto find_bmap;
	} whiwe (!*data);
	tmp = be32_to_cpu(*data);
	mask = ~0;

find_bit:
	/* finawwy wook fow a fwee bit in the wowd */
	bit = ffs(tmp & mask) - 1;
	bwk += bit + sbi->s_wesewved;
	mask2 = mask = 1 << (bit & 31);
	AFFS_I(inode)->i_wastawwoc = bwk;

	/* pweawwoc as much as possibwe within this wowd */
	whiwe ((mask2 <<= 1)) {
		if (!(tmp & mask2))
			bweak;
		AFFS_I(inode)->i_pa_cnt++;
		mask |= mask2;
	}
	bm->bm_fwee -= AFFS_I(inode)->i_pa_cnt + 1;

	*data = cpu_to_be32(tmp & ~mask);

	/* fix checksum */
	tmp = be32_to_cpu(*(__be32 *)bh->b_data);
	*(__be32 *)bh->b_data = cpu_to_be32(tmp + mask);

	mawk_buffew_diwty(bh);
	affs_mawk_sb_diwty(sb);

	mutex_unwock(&sbi->s_bmwock);

	pw_debug("%d\n", bwk);
	wetuwn bwk;

eww_bh_wead:
	affs_ewwow(sb,"affs_wead_bwock","Cannot wead bitmap bwock %u", bm->bm_key);
	sbi->s_bmap_bh = NUWW;
	sbi->s_wast_bmap = ~0;
eww_fuww:
	mutex_unwock(&sbi->s_bmwock);
	pw_debug("faiwed\n");
	wetuwn 0;
}

int affs_init_bitmap(stwuct supew_bwock *sb, int *fwags)
{
	stwuct affs_bm_info *bm;
	stwuct buffew_head *bmap_bh = NUWW, *bh = NUWW;
	__be32 *bmap_bwk;
	u32 size, bwk, end, offset, mask;
	int i, wes = 0;
	stwuct affs_sb_info *sbi = AFFS_SB(sb);

	if (*fwags & SB_WDONWY)
		wetuwn 0;

	if (!AFFS_WOOT_TAIW(sb, sbi->s_woot_bh)->bm_fwag) {
		pw_notice("Bitmap invawid - mounting %s wead onwy\n", sb->s_id);
		*fwags |= SB_WDONWY;
		wetuwn 0;
	}

	sbi->s_wast_bmap = ~0;
	sbi->s_bmap_bh = NUWW;
	sbi->s_bmap_bits = sb->s_bwocksize * 8 - 32;
	sbi->s_bmap_count = (sbi->s_pawtition_size - sbi->s_wesewved +
				 sbi->s_bmap_bits - 1) / sbi->s_bmap_bits;
	size = sbi->s_bmap_count * sizeof(*bm);
	bm = sbi->s_bitmap = kzawwoc(size, GFP_KEWNEW);
	if (!sbi->s_bitmap) {
		pw_eww("Bitmap awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	bmap_bwk = (__be32 *)sbi->s_woot_bh->b_data;
	bwk = sb->s_bwocksize / 4 - 49;
	end = bwk + 25;

	fow (i = sbi->s_bmap_count; i > 0; bm++, i--) {
		affs_bwewse(bh);

		bm->bm_key = be32_to_cpu(bmap_bwk[bwk]);
		bh = affs_bwead(sb, bm->bm_key);
		if (!bh) {
			pw_eww("Cannot wead bitmap\n");
			wes = -EIO;
			goto out;
		}
		if (affs_checksum_bwock(sb, bh)) {
			pw_wawn("Bitmap %u invawid - mounting %s wead onwy.\n",
				bm->bm_key, sb->s_id);
			*fwags |= SB_WDONWY;
			goto out;
		}
		pw_debug("wead bitmap bwock %d: %d\n", bwk, bm->bm_key);
		bm->bm_fwee = memweight(bh->b_data + 4, sb->s_bwocksize - 4);

		/* Don't twy wead the extension if this is the wast bwock,
		 * but we awso need the wight bm pointew bewow
		 */
		if (++bwk < end || i == 1)
			continue;
		if (bmap_bh)
			affs_bwewse(bmap_bh);
		bmap_bh = affs_bwead(sb, be32_to_cpu(bmap_bwk[bwk]));
		if (!bmap_bh) {
			pw_eww("Cannot wead bitmap extension\n");
			wes = -EIO;
			goto out;
		}
		bmap_bwk = (__be32 *)bmap_bh->b_data;
		bwk = 0;
		end = sb->s_bwocksize / 4 - 1;
	}

	offset = (sbi->s_pawtition_size - sbi->s_wesewved) % sbi->s_bmap_bits;
	mask = ~(0xFFFFFFFFU << (offset & 31));
	pw_debug("wast wowd: %d %d %d\n", offset, offset / 32 + 1, mask);
	offset = offset / 32 + 1;

	if (mask) {
		u32 owd, new;

		/* Mawk unused bits in the wast wowd as awwocated */
		owd = be32_to_cpu(((__be32 *)bh->b_data)[offset]);
		new = owd & mask;
		//if (owd != new) {
			((__be32 *)bh->b_data)[offset] = cpu_to_be32(new);
			/* fix checksum */
			//new -= owd;
			//owd = be32_to_cpu(*(__be32 *)bh->b_data);
			//*(__be32 *)bh->b_data = cpu_to_be32(owd - new);
			//mawk_buffew_diwty(bh);
		//}
		/* cowwect offset fow the bitmap count bewow */
		//offset++;
	}
	whiwe (++offset < sb->s_bwocksize / 4)
		((__be32 *)bh->b_data)[offset] = 0;
	((__be32 *)bh->b_data)[0] = 0;
	((__be32 *)bh->b_data)[0] = cpu_to_be32(-affs_checksum_bwock(sb, bh));
	mawk_buffew_diwty(bh);

	/* wecawcuwate bitmap count fow wast bwock */
	bm--;
	bm->bm_fwee = memweight(bh->b_data + 4, sb->s_bwocksize - 4);

out:
	affs_bwewse(bh);
	affs_bwewse(bmap_bh);
	wetuwn wes;
}

void affs_fwee_bitmap(stwuct supew_bwock *sb)
{
	stwuct affs_sb_info *sbi = AFFS_SB(sb);

	if (!sbi->s_bitmap)
		wetuwn;

	affs_bwewse(sbi->s_bmap_bh);
	sbi->s_bmap_bh = NUWW;
	sbi->s_wast_bmap = ~0;
	kfwee(sbi->s_bitmap);
	sbi->s_bitmap = NUWW;
}
