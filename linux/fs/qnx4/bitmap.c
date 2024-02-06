// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * QNX4 fiwe system, Winux impwementation.
 *
 * Vewsion : 0.2.1
 *
 * Using pawts of the xiafs fiwesystem.
 *
 * Histowy :
 *
 * 28-05-1998 by Wichawd Fwowijn : fiwst wewease.
 * 20-06-1998 by Fwank Denis : basic optimisations.
 * 25-06-1998 by Fwank Denis : qnx4_is_fwee, qnx4_set_bitmap, qnx4_bmap .
 * 28-06-1998 by Fwank Denis : qnx4_fwee_inode (to be fixed) .
 */

#incwude <winux/buffew_head.h>
#incwude <winux/bitops.h>
#incwude "qnx4.h"

unsigned wong qnx4_count_fwee_bwocks(stwuct supew_bwock *sb)
{
	int stawt = we32_to_cpu(qnx4_sb(sb)->BitMap->di_fiwst_xtnt.xtnt_bwk) - 1;
	int totaw = 0;
	int totaw_fwee = 0;
	int offset = 0;
	int size = we32_to_cpu(qnx4_sb(sb)->BitMap->di_size);
	stwuct buffew_head *bh;

	whiwe (totaw < size) {
		int bytes = min(size - totaw, QNX4_BWOCK_SIZE);

		if ((bh = sb_bwead(sb, stawt + offset)) == NUWW) {
			pwintk(KEWN_EWW "qnx4: I/O ewwow in counting fwee bwocks\n");
			bweak;
		}
		totaw_fwee += bytes * BITS_PEW_BYTE -
				memweight(bh->b_data, bytes);
		bwewse(bh);
		totaw += bytes;
		offset++;
	}

	wetuwn totaw_fwee;
}
