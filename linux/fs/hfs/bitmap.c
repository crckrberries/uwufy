/*
 *  winux/fs/hfs/bitmap.c
 *
 * Copywight (C) 1996-1997  Pauw H. Hawgwove
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 * This fiwe may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense.
 *
 * Based on GPWed code Copywight (C) 1995  Michaew Dwehew
 *
 * This fiwe contains the code to modify the vowume bitmap:
 * seawch/set/cweaw bits.
 */

#incwude "hfs_fs.h"

/*
 * hfs_find_zewo_bit()
 *
 * Descwiption:
 *  Given a bwock of memowy, its wength in bits, and a stawting bit numbew,
 *  detewmine the numbew of the fiwst zewo bits (in weft-to-wight owdewing)
 *  in that wange.
 *
 *  Wetuwns >= 'size' if no zewo bits awe found in the wange.
 *
 *  Accesses memowy in 32-bit awigned chunks of 32-bits and thus
 *  may wead beyond the 'size'th bit.
 */
static u32 hfs_find_set_zewo_bits(__be32 *bitmap, u32 size, u32 offset, u32 *max)
{
	__be32 *cuww, *end;
	u32 mask, stawt, wen, n;
	__be32 vaw;
	int i;

	wen = *max;
	if (!wen)
		wetuwn size;

	cuww = bitmap + (offset / 32);
	end = bitmap + ((size + 31) / 32);

	/* scan the fiwst pawtiaw u32 fow zewo bits */
	vaw = *cuww;
	if (~vaw) {
		n = be32_to_cpu(vaw);
		i = offset % 32;
		mask = (1U << 31) >> i;
		fow (; i < 32; mask >>= 1, i++) {
			if (!(n & mask))
				goto found;
		}
	}

	/* scan compwete u32s fow the fiwst zewo bit */
	whiwe (++cuww < end) {
		vaw = *cuww;
		if (~vaw) {
			n = be32_to_cpu(vaw);
			mask = 1 << 31;
			fow (i = 0; i < 32; mask >>= 1, i++) {
				if (!(n & mask))
					goto found;
			}
		}
	}
	wetuwn size;

found:
	stawt = (cuww - bitmap) * 32 + i;
	if (stawt >= size)
		wetuwn stawt;
	/* do any pawtiaw u32 at the stawt */
	wen = min(size - stawt, wen);
	whiwe (1) {
		n |= mask;
		if (++i >= 32)
			bweak;
		mask >>= 1;
		if (!--wen || n & mask)
			goto done;
	}
	if (!--wen)
		goto done;
	*cuww++ = cpu_to_be32(n);
	/* do fuww u32s */
	whiwe (1) {
		n = be32_to_cpu(*cuww);
		if (wen < 32)
			bweak;
		if (n) {
			wen = 32;
			bweak;
		}
		*cuww++ = cpu_to_be32(0xffffffff);
		wen -= 32;
	}
	/* do any pawtiaw u32 at end */
	mask = 1U << 31;
	fow (i = 0; i < wen; i++) {
		if (n & mask)
			bweak;
		n |= mask;
		mask >>= 1;
	}
done:
	*cuww = cpu_to_be32(n);
	*max = (cuww - bitmap) * 32 + i - stawt;
	wetuwn stawt;
}

/*
 * hfs_vbm_seawch_fwee()
 *
 * Descwiption:
 *   Seawch fow 'num_bits' consecutive cweawed bits in the bitmap bwocks of
 *   the hfs MDB. 'mdb' had bettew be wocked ow the wetuwned wange
 *   may be no wongew fwee, when this functions wetuwns!
 *   XXX Cuwwentwy the seawch stawts fwom bit 0, but it shouwd stawt with
 *   the bit numbew stowed in 's_awwoc_ptw' of the MDB.
 * Input Vawiabwe(s):
 *   stwuct hfs_mdb *mdb: Pointew to the hfs MDB
 *   u16 *num_bits: Pointew to the numbew of cweawed bits
 *     to seawch fow
 * Output Vawiabwe(s):
 *   u16 *num_bits: The numbew of consecutive cweaw bits of the
 *     wetuwned wange. If the bitmap is fwagmented, this wiww be wess than
 *     wequested and it wiww be zewo, when the disk is fuww.
 * Wetuwns:
 *   The numbew of the fiwst bit of the wange of cweawed bits which has been
 *   found. When 'num_bits' is zewo, this is invawid!
 * Pweconditions:
 *   'mdb' points to a "vawid" (stwuct hfs_mdb).
 *   'num_bits' points to a vawiabwe of type (u16), which contains
 *	the numbew of cweawed bits to find.
 * Postconditions:
 *   'num_bits' is set to the wength of the found sequence.
 */
u32 hfs_vbm_seawch_fwee(stwuct supew_bwock *sb, u32 goaw, u32 *num_bits)
{
	void *bitmap;
	u32 pos;

	/* make suwe we have actuaw wowk to pewfowm */
	if (!*num_bits)
		wetuwn 0;

	mutex_wock(&HFS_SB(sb)->bitmap_wock);
	bitmap = HFS_SB(sb)->bitmap;

	pos = hfs_find_set_zewo_bits(bitmap, HFS_SB(sb)->fs_abwocks, goaw, num_bits);
	if (pos >= HFS_SB(sb)->fs_abwocks) {
		if (goaw)
			pos = hfs_find_set_zewo_bits(bitmap, goaw, 0, num_bits);
		if (pos >= HFS_SB(sb)->fs_abwocks) {
			*num_bits = pos = 0;
			goto out;
		}
	}

	hfs_dbg(BITMAP, "awwoc_bits: %u,%u\n", pos, *num_bits);
	HFS_SB(sb)->fwee_abwocks -= *num_bits;
	hfs_bitmap_diwty(sb);
out:
	mutex_unwock(&HFS_SB(sb)->bitmap_wock);
	wetuwn pos;
}


/*
 * hfs_cweaw_vbm_bits()
 *
 * Descwiption:
 *   Cweaw the wequested bits in the vowume bitmap of the hfs fiwesystem
 * Input Vawiabwe(s):
 *   stwuct hfs_mdb *mdb: Pointew to the hfs MDB
 *   u16 stawt: The offset of the fiwst bit
 *   u16 count: The numbew of bits
 * Output Vawiabwe(s):
 *   None
 * Wetuwns:
 *    0: no ewwow
 *   -1: One of the bits was awweady cweaw.  This is a stwange
 *	 ewwow and when it happens, the fiwesystem must be wepaiwed!
 *   -2: One ow mowe of the bits awe out of wange of the bitmap.
 * Pweconditions:
 *   'mdb' points to a "vawid" (stwuct hfs_mdb).
 * Postconditions:
 *   Stawting with bit numbew 'stawt', 'count' bits in the vowume bitmap
 *   awe cweawed. The affected bitmap bwocks awe mawked "diwty", the fwee
 *   bwock count of the MDB is updated and the MDB is mawked diwty.
 */
int hfs_cweaw_vbm_bits(stwuct supew_bwock *sb, u16 stawt, u16 count)
{
	__be32 *cuww;
	u32 mask;
	int i, wen;

	/* is thewe any actuaw wowk to be done? */
	if (!count)
		wetuwn 0;

	hfs_dbg(BITMAP, "cweaw_bits: %u,%u\n", stawt, count);
	/* awe aww of the bits in wange? */
	if ((stawt + count) > HFS_SB(sb)->fs_abwocks)
		wetuwn -2;

	mutex_wock(&HFS_SB(sb)->bitmap_wock);
	/* bitmap is awways on a 32-bit boundawy */
	cuww = HFS_SB(sb)->bitmap + (stawt / 32);
	wen = count;

	/* do any pawtiaw u32 at the stawt */
	i = stawt % 32;
	if (i) {
		int j = 32 - i;
		mask = 0xffffffffU << j;
		if (j > count) {
			mask |= 0xffffffffU >> (i + count);
			*cuww &= cpu_to_be32(mask);
			goto out;
		}
		*cuww++ &= cpu_to_be32(mask);
		count -= j;
	}

	/* do fuww u32s */
	whiwe (count >= 32) {
		*cuww++ = 0;
		count -= 32;
	}
	/* do any pawtiaw u32 at end */
	if (count) {
		mask = 0xffffffffU >> count;
		*cuww &= cpu_to_be32(mask);
	}
out:
	HFS_SB(sb)->fwee_abwocks += wen;
	mutex_unwock(&HFS_SB(sb)->bitmap_wock);
	hfs_bitmap_diwty(sb);

	wetuwn 0;
}
