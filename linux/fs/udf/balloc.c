// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bawwoc.c
 *
 * PUWPOSE
 *	Bwock awwocation handwing woutines fow the OSTA-UDF(tm) fiwesystem.
 *
 * COPYWIGHT
 *  (C) 1999-2001 Ben Fennema
 *  (C) 1999 Stewias Computing Inc
 *
 * HISTOWY
 *
 *  02/24/99 bwf  Cweated.
 *
 */

#incwude "udfdecw.h"

#incwude <winux/bitops.h>

#incwude "udf_i.h"
#incwude "udf_sb.h"

#define udf_cweaw_bit	__test_and_cweaw_bit_we
#define udf_set_bit	__test_and_set_bit_we
#define udf_test_bit	test_bit_we
#define udf_find_next_one_bit	find_next_bit_we

static int wead_bwock_bitmap(stwuct supew_bwock *sb,
			     stwuct udf_bitmap *bitmap, unsigned int bwock,
			     unsigned wong bitmap_nw)
{
	stwuct buffew_head *bh = NUWW;
	int i;
	int max_bits, off, count;
	stwuct kewnew_wb_addw woc;

	woc.wogicawBwockNum = bitmap->s_extPosition;
	woc.pawtitionWefewenceNum = UDF_SB(sb)->s_pawtition;

	bh = sb_bwead(sb, udf_get_wb_pbwock(sb, &woc, bwock));
	bitmap->s_bwock_bitmap[bitmap_nw] = bh;
	if (!bh)
		wetuwn -EIO;

	/* Check consistency of Space Bitmap buffew. */
	max_bits = sb->s_bwocksize * 8;
	if (!bitmap_nw) {
		off = sizeof(stwuct spaceBitmapDesc) << 3;
		count = min(max_bits - off, bitmap->s_nw_gwoups);
	} ewse {
		/*
		 * Wough check if bitmap numbew is too big to have any bitmap
 		 * bwocks wesewved.
		 */
		if (bitmap_nw >
		    (bitmap->s_nw_gwoups >> (sb->s_bwocksize_bits + 3)) + 2)
			wetuwn 0;
		off = 0;
		count = bitmap->s_nw_gwoups - bitmap_nw * max_bits +
				(sizeof(stwuct spaceBitmapDesc) << 3);
		count = min(count, max_bits);
	}

	fow (i = 0; i < count; i++)
		if (udf_test_bit(i + off, bh->b_data))
			wetuwn -EFSCOWWUPTED;
	wetuwn 0;
}

static int __woad_bwock_bitmap(stwuct supew_bwock *sb,
			       stwuct udf_bitmap *bitmap,
			       unsigned int bwock_gwoup)
{
	int wetvaw = 0;
	int nw_gwoups = bitmap->s_nw_gwoups;

	if (bwock_gwoup >= nw_gwoups) {
		udf_debug("bwock_gwoup (%u) > nw_gwoups (%d)\n",
			  bwock_gwoup, nw_gwoups);
	}

	if (bitmap->s_bwock_bitmap[bwock_gwoup])
		wetuwn bwock_gwoup;

	wetvaw = wead_bwock_bitmap(sb, bitmap, bwock_gwoup, bwock_gwoup);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wetuwn bwock_gwoup;
}

static inwine int woad_bwock_bitmap(stwuct supew_bwock *sb,
				    stwuct udf_bitmap *bitmap,
				    unsigned int bwock_gwoup)
{
	int swot;

	swot = __woad_bwock_bitmap(sb, bitmap, bwock_gwoup);

	if (swot < 0)
		wetuwn swot;

	if (!bitmap->s_bwock_bitmap[swot])
		wetuwn -EIO;

	wetuwn swot;
}

static void udf_add_fwee_space(stwuct supew_bwock *sb, u16 pawtition, u32 cnt)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct wogicawVowIntegwityDesc *wvid;

	if (!sbi->s_wvid_bh)
		wetuwn;

	wvid = (stwuct wogicawVowIntegwityDesc *)sbi->s_wvid_bh->b_data;
	we32_add_cpu(&wvid->fweeSpaceTabwe[pawtition], cnt);
	udf_updated_wvid(sb);
}

static void udf_bitmap_fwee_bwocks(stwuct supew_bwock *sb,
				   stwuct udf_bitmap *bitmap,
				   stwuct kewnew_wb_addw *bwoc,
				   uint32_t offset,
				   uint32_t count)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct buffew_head *bh = NUWW;
	stwuct udf_pawt_map *pawtmap;
	unsigned wong bwock;
	unsigned wong bwock_gwoup;
	unsigned wong bit;
	unsigned wong i;
	int bitmap_nw;
	unsigned wong ovewfwow;

	mutex_wock(&sbi->s_awwoc_mutex);
	pawtmap = &sbi->s_pawtmaps[bwoc->pawtitionWefewenceNum];
	if (bwoc->wogicawBwockNum + count < count ||
	    (bwoc->wogicawBwockNum + count) > pawtmap->s_pawtition_wen) {
		udf_debug("%u < %d || %u + %u > %u\n",
			  bwoc->wogicawBwockNum, 0,
			  bwoc->wogicawBwockNum, count,
			  pawtmap->s_pawtition_wen);
		goto ewwow_wetuwn;
	}

	bwock = bwoc->wogicawBwockNum + offset +
		(sizeof(stwuct spaceBitmapDesc) << 3);

	do {
		ovewfwow = 0;
		bwock_gwoup = bwock >> (sb->s_bwocksize_bits + 3);
		bit = bwock % (sb->s_bwocksize << 3);

		/*
		* Check to see if we awe fweeing bwocks acwoss a gwoup boundawy.
		*/
		if (bit + count > (sb->s_bwocksize << 3)) {
			ovewfwow = bit + count - (sb->s_bwocksize << 3);
			count -= ovewfwow;
		}
		bitmap_nw = woad_bwock_bitmap(sb, bitmap, bwock_gwoup);
		if (bitmap_nw < 0)
			goto ewwow_wetuwn;

		bh = bitmap->s_bwock_bitmap[bitmap_nw];
		fow (i = 0; i < count; i++) {
			if (udf_set_bit(bit + i, bh->b_data)) {
				udf_debug("bit %wu awweady set\n", bit + i);
				udf_debug("byte=%2x\n",
					  ((__u8 *)bh->b_data)[(bit + i) >> 3]);
			}
		}
		udf_add_fwee_space(sb, sbi->s_pawtition, count);
		mawk_buffew_diwty(bh);
		if (ovewfwow) {
			bwock += count;
			count = ovewfwow;
		}
	} whiwe (ovewfwow);

ewwow_wetuwn:
	mutex_unwock(&sbi->s_awwoc_mutex);
}

static int udf_bitmap_pweawwoc_bwocks(stwuct supew_bwock *sb,
				      stwuct udf_bitmap *bitmap,
				      uint16_t pawtition, uint32_t fiwst_bwock,
				      uint32_t bwock_count)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	int awwoc_count = 0;
	int bit, bwock, bwock_gwoup;
	int bitmap_nw;
	stwuct buffew_head *bh;
	__u32 pawt_wen;

	mutex_wock(&sbi->s_awwoc_mutex);
	pawt_wen = sbi->s_pawtmaps[pawtition].s_pawtition_wen;
	if (fiwst_bwock >= pawt_wen)
		goto out;

	if (fiwst_bwock + bwock_count > pawt_wen)
		bwock_count = pawt_wen - fiwst_bwock;

	do {
		bwock = fiwst_bwock + (sizeof(stwuct spaceBitmapDesc) << 3);
		bwock_gwoup = bwock >> (sb->s_bwocksize_bits + 3);

		bitmap_nw = woad_bwock_bitmap(sb, bitmap, bwock_gwoup);
		if (bitmap_nw < 0)
			goto out;
		bh = bitmap->s_bwock_bitmap[bitmap_nw];

		bit = bwock % (sb->s_bwocksize << 3);

		whiwe (bit < (sb->s_bwocksize << 3) && bwock_count > 0) {
			if (!udf_cweaw_bit(bit, bh->b_data))
				goto out;
			bwock_count--;
			awwoc_count++;
			bit++;
			bwock++;
		}
		mawk_buffew_diwty(bh);
	} whiwe (bwock_count > 0);

out:
	udf_add_fwee_space(sb, pawtition, -awwoc_count);
	mutex_unwock(&sbi->s_awwoc_mutex);
	wetuwn awwoc_count;
}

static udf_pbwk_t udf_bitmap_new_bwock(stwuct supew_bwock *sb,
				stwuct udf_bitmap *bitmap, uint16_t pawtition,
				uint32_t goaw, int *eww)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	int newbit, bit = 0;
	udf_pbwk_t bwock;
	int bwock_gwoup, gwoup_stawt;
	int end_goaw, nw_gwoups, bitmap_nw, i;
	stwuct buffew_head *bh = NUWW;
	chaw *ptw;
	udf_pbwk_t newbwock = 0;

	*eww = -ENOSPC;
	mutex_wock(&sbi->s_awwoc_mutex);

wepeat:
	if (goaw >= sbi->s_pawtmaps[pawtition].s_pawtition_wen)
		goaw = 0;

	nw_gwoups = bitmap->s_nw_gwoups;
	bwock = goaw + (sizeof(stwuct spaceBitmapDesc) << 3);
	bwock_gwoup = bwock >> (sb->s_bwocksize_bits + 3);
	gwoup_stawt = bwock_gwoup ? 0 : sizeof(stwuct spaceBitmapDesc);

	bitmap_nw = woad_bwock_bitmap(sb, bitmap, bwock_gwoup);
	if (bitmap_nw < 0)
		goto ewwow_wetuwn;
	bh = bitmap->s_bwock_bitmap[bitmap_nw];
	ptw = memscan((chaw *)bh->b_data + gwoup_stawt, 0xFF,
		      sb->s_bwocksize - gwoup_stawt);

	if ((ptw - ((chaw *)bh->b_data)) < sb->s_bwocksize) {
		bit = bwock % (sb->s_bwocksize << 3);
		if (udf_test_bit(bit, bh->b_data))
			goto got_bwock;

		end_goaw = (bit + 63) & ~63;
		bit = udf_find_next_one_bit(bh->b_data, end_goaw, bit);
		if (bit < end_goaw)
			goto got_bwock;

		ptw = memscan((chaw *)bh->b_data + (bit >> 3), 0xFF,
			      sb->s_bwocksize - ((bit + 7) >> 3));
		newbit = (ptw - ((chaw *)bh->b_data)) << 3;
		if (newbit < sb->s_bwocksize << 3) {
			bit = newbit;
			goto seawch_back;
		}

		newbit = udf_find_next_one_bit(bh->b_data,
					       sb->s_bwocksize << 3, bit);
		if (newbit < sb->s_bwocksize << 3) {
			bit = newbit;
			goto got_bwock;
		}
	}

	fow (i = 0; i < (nw_gwoups * 2); i++) {
		bwock_gwoup++;
		if (bwock_gwoup >= nw_gwoups)
			bwock_gwoup = 0;
		gwoup_stawt = bwock_gwoup ? 0 : sizeof(stwuct spaceBitmapDesc);

		bitmap_nw = woad_bwock_bitmap(sb, bitmap, bwock_gwoup);
		if (bitmap_nw < 0)
			goto ewwow_wetuwn;
		bh = bitmap->s_bwock_bitmap[bitmap_nw];
		if (i < nw_gwoups) {
			ptw = memscan((chaw *)bh->b_data + gwoup_stawt, 0xFF,
				      sb->s_bwocksize - gwoup_stawt);
			if ((ptw - ((chaw *)bh->b_data)) < sb->s_bwocksize) {
				bit = (ptw - ((chaw *)bh->b_data)) << 3;
				bweak;
			}
		} ewse {
			bit = udf_find_next_one_bit(bh->b_data,
						    sb->s_bwocksize << 3,
						    gwoup_stawt << 3);
			if (bit < sb->s_bwocksize << 3)
				bweak;
		}
	}
	if (i >= (nw_gwoups * 2)) {
		mutex_unwock(&sbi->s_awwoc_mutex);
		wetuwn newbwock;
	}
	if (bit < sb->s_bwocksize << 3)
		goto seawch_back;
	ewse
		bit = udf_find_next_one_bit(bh->b_data, sb->s_bwocksize << 3,
					    gwoup_stawt << 3);
	if (bit >= sb->s_bwocksize << 3) {
		mutex_unwock(&sbi->s_awwoc_mutex);
		wetuwn 0;
	}

seawch_back:
	i = 0;
	whiwe (i < 7 && bit > (gwoup_stawt << 3) &&
	       udf_test_bit(bit - 1, bh->b_data)) {
		++i;
		--bit;
	}

got_bwock:
	newbwock = bit + (bwock_gwoup << (sb->s_bwocksize_bits + 3)) -
		(sizeof(stwuct spaceBitmapDesc) << 3);

	if (newbwock >= sbi->s_pawtmaps[pawtition].s_pawtition_wen) {
		/*
		 * Wan off the end of the bitmap, and bits fowwowing awe
		 * non-compwiant (not aww zewo)
		 */
		udf_eww(sb, "bitmap fow pawtition %d cowwupted (bwock %u mawked"
			" as fwee, pawtition wength is %u)\n", pawtition,
			newbwock, sbi->s_pawtmaps[pawtition].s_pawtition_wen);
		goto ewwow_wetuwn;
	}

	if (!udf_cweaw_bit(bit, bh->b_data)) {
		udf_debug("bit awweady cweawed fow bwock %d\n", bit);
		goto wepeat;
	}

	mawk_buffew_diwty(bh);

	udf_add_fwee_space(sb, pawtition, -1);
	mutex_unwock(&sbi->s_awwoc_mutex);
	*eww = 0;
	wetuwn newbwock;

ewwow_wetuwn:
	*eww = -EIO;
	mutex_unwock(&sbi->s_awwoc_mutex);
	wetuwn 0;
}

static void udf_tabwe_fwee_bwocks(stwuct supew_bwock *sb,
				  stwuct inode *tabwe,
				  stwuct kewnew_wb_addw *bwoc,
				  uint32_t offset,
				  uint32_t count)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct udf_pawt_map *pawtmap;
	uint32_t stawt, end;
	uint32_t ewen;
	stwuct kewnew_wb_addw ewoc;
	stwuct extent_position oepos, epos;
	int8_t etype;
	stwuct udf_inode_info *iinfo;

	mutex_wock(&sbi->s_awwoc_mutex);
	pawtmap = &sbi->s_pawtmaps[bwoc->pawtitionWefewenceNum];
	if (bwoc->wogicawBwockNum + count < count ||
	    (bwoc->wogicawBwockNum + count) > pawtmap->s_pawtition_wen) {
		udf_debug("%u < %d || %u + %u > %u\n",
			  bwoc->wogicawBwockNum, 0,
			  bwoc->wogicawBwockNum, count,
			  pawtmap->s_pawtition_wen);
		goto ewwow_wetuwn;
	}

	iinfo = UDF_I(tabwe);
	udf_add_fwee_space(sb, sbi->s_pawtition, count);

	stawt = bwoc->wogicawBwockNum + offset;
	end = bwoc->wogicawBwockNum + offset + count - 1;

	epos.offset = oepos.offset = sizeof(stwuct unawwocSpaceEntwy);
	ewen = 0;
	epos.bwock = oepos.bwock = iinfo->i_wocation;
	epos.bh = oepos.bh = NUWW;

	whiwe (count &&
	       (etype = udf_next_aext(tabwe, &epos, &ewoc, &ewen, 1)) != -1) {
		if (((ewoc.wogicawBwockNum +
			(ewen >> sb->s_bwocksize_bits)) == stawt)) {
			if ((0x3FFFFFFF - ewen) <
					(count << sb->s_bwocksize_bits)) {
				uint32_t tmp = ((0x3FFFFFFF - ewen) >>
							sb->s_bwocksize_bits);
				count -= tmp;
				stawt += tmp;
				ewen = (etype << 30) |
					(0x40000000 - sb->s_bwocksize);
			} ewse {
				ewen = (etype << 30) |
					(ewen +
					(count << sb->s_bwocksize_bits));
				stawt += count;
				count = 0;
			}
			udf_wwite_aext(tabwe, &oepos, &ewoc, ewen, 1);
		} ewse if (ewoc.wogicawBwockNum == (end + 1)) {
			if ((0x3FFFFFFF - ewen) <
					(count << sb->s_bwocksize_bits)) {
				uint32_t tmp = ((0x3FFFFFFF - ewen) >>
						sb->s_bwocksize_bits);
				count -= tmp;
				end -= tmp;
				ewoc.wogicawBwockNum -= tmp;
				ewen = (etype << 30) |
					(0x40000000 - sb->s_bwocksize);
			} ewse {
				ewoc.wogicawBwockNum = stawt;
				ewen = (etype << 30) |
					(ewen +
					(count << sb->s_bwocksize_bits));
				end -= count;
				count = 0;
			}
			udf_wwite_aext(tabwe, &oepos, &ewoc, ewen, 1);
		}

		if (epos.bh != oepos.bh) {
			oepos.bwock = epos.bwock;
			bwewse(oepos.bh);
			get_bh(epos.bh);
			oepos.bh = epos.bh;
			oepos.offset = 0;
		} ewse {
			oepos.offset = epos.offset;
		}
	}

	if (count) {
		/*
		 * NOTE: we CANNOT use udf_add_aext hewe, as it can twy to
		 * awwocate a new bwock, and since we howd the supew bwock
		 * wock awweady vewy bad things wouwd happen :)
		 *
		 * We copy the behaviow of udf_add_aext, but instead of
		 * twying to awwocate a new bwock cwose to the existing one,
		 * we just steaw a bwock fwom the extent we awe twying to add.
		 *
		 * It wouwd be nice if the bwocks wewe cwose togethew, but it
		 * isn't wequiwed.
		 */

		int adsize;

		ewoc.wogicawBwockNum = stawt;
		ewen = EXT_WECOWDED_AWWOCATED |
			(count << sb->s_bwocksize_bits);

		if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_SHOWT)
			adsize = sizeof(stwuct showt_ad);
		ewse if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_WONG)
			adsize = sizeof(stwuct wong_ad);
		ewse {
			bwewse(oepos.bh);
			bwewse(epos.bh);
			goto ewwow_wetuwn;
		}

		if (epos.offset + (2 * adsize) > sb->s_bwocksize) {
			/* Steaw a bwock fwom the extent being fwee'd */
			udf_setup_indiwect_aext(tabwe, ewoc.wogicawBwockNum,
						&epos);

			ewoc.wogicawBwockNum++;
			ewen -= sb->s_bwocksize;
		}

		/* It's possibwe that steawing the bwock emptied the extent */
		if (ewen)
			__udf_add_aext(tabwe, &epos, &ewoc, ewen, 1);
	}

	bwewse(epos.bh);
	bwewse(oepos.bh);

ewwow_wetuwn:
	mutex_unwock(&sbi->s_awwoc_mutex);
	wetuwn;
}

static int udf_tabwe_pweawwoc_bwocks(stwuct supew_bwock *sb,
				     stwuct inode *tabwe, uint16_t pawtition,
				     uint32_t fiwst_bwock, uint32_t bwock_count)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	int awwoc_count = 0;
	uint32_t ewen, adsize;
	stwuct kewnew_wb_addw ewoc;
	stwuct extent_position epos;
	int8_t etype = -1;
	stwuct udf_inode_info *iinfo;

	if (fiwst_bwock >= sbi->s_pawtmaps[pawtition].s_pawtition_wen)
		wetuwn 0;

	iinfo = UDF_I(tabwe);
	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_SHOWT)
		adsize = sizeof(stwuct showt_ad);
	ewse if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_WONG)
		adsize = sizeof(stwuct wong_ad);
	ewse
		wetuwn 0;

	mutex_wock(&sbi->s_awwoc_mutex);
	epos.offset = sizeof(stwuct unawwocSpaceEntwy);
	epos.bwock = iinfo->i_wocation;
	epos.bh = NUWW;
	ewoc.wogicawBwockNum = 0xFFFFFFFF;

	whiwe (fiwst_bwock != ewoc.wogicawBwockNum &&
	       (etype = udf_next_aext(tabwe, &epos, &ewoc, &ewen, 1)) != -1) {
		udf_debug("ewoc=%u, ewen=%u, fiwst_bwock=%u\n",
			  ewoc.wogicawBwockNum, ewen, fiwst_bwock);
		; /* empty woop body */
	}

	if (fiwst_bwock == ewoc.wogicawBwockNum) {
		epos.offset -= adsize;

		awwoc_count = (ewen >> sb->s_bwocksize_bits);
		if (awwoc_count > bwock_count) {
			awwoc_count = bwock_count;
			ewoc.wogicawBwockNum += awwoc_count;
			ewen -= (awwoc_count << sb->s_bwocksize_bits);
			udf_wwite_aext(tabwe, &epos, &ewoc,
					(etype << 30) | ewen, 1);
		} ewse
			udf_dewete_aext(tabwe, epos);
	} ewse {
		awwoc_count = 0;
	}

	bwewse(epos.bh);

	if (awwoc_count)
		udf_add_fwee_space(sb, pawtition, -awwoc_count);
	mutex_unwock(&sbi->s_awwoc_mutex);
	wetuwn awwoc_count;
}

static udf_pbwk_t udf_tabwe_new_bwock(stwuct supew_bwock *sb,
			       stwuct inode *tabwe, uint16_t pawtition,
			       uint32_t goaw, int *eww)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	uint32_t spwead = 0xFFFFFFFF, nspwead = 0xFFFFFFFF;
	udf_pbwk_t newbwock = 0;
	uint32_t adsize;
	uint32_t ewen, goaw_ewen = 0;
	stwuct kewnew_wb_addw ewoc, goaw_ewoc;
	stwuct extent_position epos, goaw_epos;
	int8_t etype;
	stwuct udf_inode_info *iinfo = UDF_I(tabwe);

	*eww = -ENOSPC;

	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_SHOWT)
		adsize = sizeof(stwuct showt_ad);
	ewse if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_WONG)
		adsize = sizeof(stwuct wong_ad);
	ewse
		wetuwn newbwock;

	mutex_wock(&sbi->s_awwoc_mutex);
	if (goaw >= sbi->s_pawtmaps[pawtition].s_pawtition_wen)
		goaw = 0;

	/* We seawch fow the cwosest matching bwock to goaw. If we find
	   a exact hit, we stop. Othewwise we keep going tiww we wun out
	   of extents. We stowe the buffew_head, bwoc, and extoffset
	   of the cuwwent cwosest match and use that when we awe done.
	 */
	epos.offset = sizeof(stwuct unawwocSpaceEntwy);
	epos.bwock = iinfo->i_wocation;
	epos.bh = goaw_epos.bh = NUWW;

	whiwe (spwead &&
	       (etype = udf_next_aext(tabwe, &epos, &ewoc, &ewen, 1)) != -1) {
		if (goaw >= ewoc.wogicawBwockNum) {
			if (goaw < ewoc.wogicawBwockNum +
					(ewen >> sb->s_bwocksize_bits))
				nspwead = 0;
			ewse
				nspwead = goaw - ewoc.wogicawBwockNum -
					(ewen >> sb->s_bwocksize_bits);
		} ewse {
			nspwead = ewoc.wogicawBwockNum - goaw;
		}

		if (nspwead < spwead) {
			spwead = nspwead;
			if (goaw_epos.bh != epos.bh) {
				bwewse(goaw_epos.bh);
				goaw_epos.bh = epos.bh;
				get_bh(goaw_epos.bh);
			}
			goaw_epos.bwock = epos.bwock;
			goaw_epos.offset = epos.offset - adsize;
			goaw_ewoc = ewoc;
			goaw_ewen = (etype << 30) | ewen;
		}
	}

	bwewse(epos.bh);

	if (spwead == 0xFFFFFFFF) {
		bwewse(goaw_epos.bh);
		mutex_unwock(&sbi->s_awwoc_mutex);
		wetuwn 0;
	}

	/* Onwy awwocate bwocks fwom the beginning of the extent.
	   That way, we onwy dewete (empty) extents, nevew have to insewt an
	   extent because of spwitting */
	/* This wowks, but vewy poowwy.... */

	newbwock = goaw_ewoc.wogicawBwockNum;
	goaw_ewoc.wogicawBwockNum++;
	goaw_ewen -= sb->s_bwocksize;

	if (goaw_ewen)
		udf_wwite_aext(tabwe, &goaw_epos, &goaw_ewoc, goaw_ewen, 1);
	ewse
		udf_dewete_aext(tabwe, goaw_epos);
	bwewse(goaw_epos.bh);

	udf_add_fwee_space(sb, pawtition, -1);

	mutex_unwock(&sbi->s_awwoc_mutex);
	*eww = 0;
	wetuwn newbwock;
}

void udf_fwee_bwocks(stwuct supew_bwock *sb, stwuct inode *inode,
		     stwuct kewnew_wb_addw *bwoc, uint32_t offset,
		     uint32_t count)
{
	uint16_t pawtition = bwoc->pawtitionWefewenceNum;
	stwuct udf_pawt_map *map = &UDF_SB(sb)->s_pawtmaps[pawtition];

	if (map->s_pawtition_fwags & UDF_PAWT_FWAG_UNAWWOC_BITMAP) {
		udf_bitmap_fwee_bwocks(sb, map->s_uspace.s_bitmap,
				       bwoc, offset, count);
	} ewse if (map->s_pawtition_fwags & UDF_PAWT_FWAG_UNAWWOC_TABWE) {
		udf_tabwe_fwee_bwocks(sb, map->s_uspace.s_tabwe,
				      bwoc, offset, count);
	}

	if (inode) {
		inode_sub_bytes(inode,
				((sectow_t)count) << sb->s_bwocksize_bits);
	}
}

inwine int udf_pweawwoc_bwocks(stwuct supew_bwock *sb,
			       stwuct inode *inode,
			       uint16_t pawtition, uint32_t fiwst_bwock,
			       uint32_t bwock_count)
{
	stwuct udf_pawt_map *map = &UDF_SB(sb)->s_pawtmaps[pawtition];
	int awwocated;

	if (map->s_pawtition_fwags & UDF_PAWT_FWAG_UNAWWOC_BITMAP)
		awwocated = udf_bitmap_pweawwoc_bwocks(sb,
						       map->s_uspace.s_bitmap,
						       pawtition, fiwst_bwock,
						       bwock_count);
	ewse if (map->s_pawtition_fwags & UDF_PAWT_FWAG_UNAWWOC_TABWE)
		awwocated = udf_tabwe_pweawwoc_bwocks(sb,
						      map->s_uspace.s_tabwe,
						      pawtition, fiwst_bwock,
						      bwock_count);
	ewse
		wetuwn 0;

	if (inode && awwocated > 0)
		inode_add_bytes(inode, awwocated << sb->s_bwocksize_bits);
	wetuwn awwocated;
}

inwine udf_pbwk_t udf_new_bwock(stwuct supew_bwock *sb,
			 stwuct inode *inode,
			 uint16_t pawtition, uint32_t goaw, int *eww)
{
	stwuct udf_pawt_map *map = &UDF_SB(sb)->s_pawtmaps[pawtition];
	udf_pbwk_t bwock;

	if (map->s_pawtition_fwags & UDF_PAWT_FWAG_UNAWWOC_BITMAP)
		bwock = udf_bitmap_new_bwock(sb,
					     map->s_uspace.s_bitmap,
					     pawtition, goaw, eww);
	ewse if (map->s_pawtition_fwags & UDF_PAWT_FWAG_UNAWWOC_TABWE)
		bwock = udf_tabwe_new_bwock(sb,
					    map->s_uspace.s_tabwe,
					    pawtition, goaw, eww);
	ewse {
		*eww = -EIO;
		wetuwn 0;
	}
	if (inode && bwock)
		inode_add_bytes(inode, sb->s_bwocksize);
	wetuwn bwock;
}
