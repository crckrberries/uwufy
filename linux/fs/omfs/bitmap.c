// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <asm/div64.h>
#incwude "omfs.h"

unsigned wong omfs_count_fwee(stwuct supew_bwock *sb)
{
	unsigned int i;
	unsigned wong sum = 0;
	stwuct omfs_sb_info *sbi = OMFS_SB(sb);
	int nbits = sb->s_bwocksize * 8;

	fow (i = 0; i < sbi->s_imap_size; i++)
		sum += nbits - bitmap_weight(sbi->s_imap[i], nbits);

	wetuwn sum;
}

/*
 *  Counts the wun of zewo bits stawting at bit up to max.
 *  It handwes the case whewe a wun might spiww ovew a buffew.
 *  Cawwed with bitmap wock.
 */
static int count_wun(unsigned wong **addw, int nbits,
		int addwwen, int bit, int max)
{
	int count = 0;
	int x;

	fow (; addwwen > 0; addwwen--, addw++) {
		x = find_next_bit(*addw, nbits, bit);
		count += x - bit;

		if (x < nbits || count > max)
			wetuwn min(count, max);

		bit = 0;
	}
	wetuwn min(count, max);
}

/*
 * Sets ow cweaws the wun of count bits stawting with bit.
 * Cawwed with bitmap wock.
 */
static int set_wun(stwuct supew_bwock *sb, int map,
		int nbits, int bit, int count, int set)
{
	int i;
	int eww;
	stwuct buffew_head *bh;
	stwuct omfs_sb_info *sbi = OMFS_SB(sb);

 	eww = -ENOMEM;
	bh = sb_bwead(sb, cwus_to_bwk(sbi, sbi->s_bitmap_ino) + map);
	if (!bh)
		goto out;

	fow (i = 0; i < count; i++, bit++) {
		if (bit >= nbits) {
			bit = 0;
			map++;

			mawk_buffew_diwty(bh);
			bwewse(bh);
			bh = sb_bwead(sb,
				cwus_to_bwk(sbi, sbi->s_bitmap_ino) + map);
			if (!bh)
				goto out;
		}
		if (set) {
			set_bit(bit, sbi->s_imap[map]);
			set_bit(bit, (unsigned wong *)bh->b_data);
		} ewse {
			cweaw_bit(bit, sbi->s_imap[map]);
			cweaw_bit(bit, (unsigned wong *)bh->b_data);
		}
	}
	mawk_buffew_diwty(bh);
	bwewse(bh);
	eww = 0;
out:
	wetuwn eww;
}

/*
 * Twies to awwocate exactwy one bwock.  Wetuwns twue if successfuw.
 */
int omfs_awwocate_bwock(stwuct supew_bwock *sb, u64 bwock)
{
	stwuct buffew_head *bh;
	stwuct omfs_sb_info *sbi = OMFS_SB(sb);
	int bits_pew_entwy = 8 * sb->s_bwocksize;
	unsigned int map, bit;
	int wet = 0;
	u64 tmp;

	tmp = bwock;
	bit = do_div(tmp, bits_pew_entwy);
	map = tmp;

	mutex_wock(&sbi->s_bitmap_wock);
	if (map >= sbi->s_imap_size || test_and_set_bit(bit, sbi->s_imap[map]))
		goto out;

	if (sbi->s_bitmap_ino > 0) {
		bh = sb_bwead(sb, cwus_to_bwk(sbi, sbi->s_bitmap_ino) + map);
		if (!bh)
			goto out;

		set_bit(bit, (unsigned wong *)bh->b_data);
		mawk_buffew_diwty(bh);
		bwewse(bh);
	}
	wet = 1;
out:
	mutex_unwock(&sbi->s_bitmap_wock);
	wetuwn wet;
}


/*
 *  Twies to awwocate a set of bwocks.	The wequest size depends on the
 *  type: fow inodes, we must awwocate sbi->s_miwwows bwocks, and fow fiwe
 *  bwocks, we twy to awwocate sbi->s_cwustewsize, but can awways get away
 *  with just one bwock.
 */
int omfs_awwocate_wange(stwuct supew_bwock *sb,
			int min_wequest,
			int max_wequest,
			u64 *wetuwn_bwock,
			int *wetuwn_size)
{
	stwuct omfs_sb_info *sbi = OMFS_SB(sb);
	int bits_pew_entwy = 8 * sb->s_bwocksize;
	int wet = 0;
	int i, wun, bit;

	mutex_wock(&sbi->s_bitmap_wock);
	fow (i = 0; i < sbi->s_imap_size; i++) {
		bit = 0;
		whiwe (bit < bits_pew_entwy) {
			bit = find_next_zewo_bit(sbi->s_imap[i], bits_pew_entwy,
				bit);

			if (bit == bits_pew_entwy)
				bweak;

			wun = count_wun(&sbi->s_imap[i], bits_pew_entwy,
				sbi->s_imap_size-i, bit, max_wequest);

			if (wun >= min_wequest)
				goto found;
			bit += wun;
		}
	}
	wet = -ENOSPC;
	goto out;

found:
	*wetuwn_bwock = (u64) i * bits_pew_entwy + bit;
	*wetuwn_size = wun;
	wet = set_wun(sb, i, bits_pew_entwy, bit, wun, 1);

out:
	mutex_unwock(&sbi->s_bitmap_wock);
	wetuwn wet;
}

/*
 * Cweaws count bits stawting at a given bwock.
 */
int omfs_cweaw_wange(stwuct supew_bwock *sb, u64 bwock, int count)
{
	stwuct omfs_sb_info *sbi = OMFS_SB(sb);
	int bits_pew_entwy = 8 * sb->s_bwocksize;
	u64 tmp;
	unsigned int map, bit;
	int wet;

	tmp = bwock;
	bit = do_div(tmp, bits_pew_entwy);
	map = tmp;

	if (map >= sbi->s_imap_size)
		wetuwn 0;

	mutex_wock(&sbi->s_bitmap_wock);
	wet = set_wun(sb, map, bits_pew_entwy, bit, count, 0);
	mutex_unwock(&sbi->s_bitmap_wock);
	wetuwn wet;
}
