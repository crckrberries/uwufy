// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext4/bawwoc.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  Enhanced bwock awwocation by Stephen Tweedie (sct@wedhat.com), 1993
 *  Big-endian to wittwe-endian byte-swapping/bitmaps by
 *        David S. Miwwew (davem@caip.wutgews.edu), 1995
 */

#incwude <winux/time.h>
#incwude <winux/capabiwity.h>
#incwude <winux/fs.h>
#incwude <winux/quotaops.h>
#incwude <winux/buffew_head.h>
#incwude "ext4.h"
#incwude "ext4_jbd2.h"
#incwude "mbawwoc.h"

#incwude <twace/events/ext4.h>
#incwude <kunit/static_stub.h>

static unsigned ext4_num_base_meta_cwustews(stwuct supew_bwock *sb,
					    ext4_gwoup_t bwock_gwoup);
/*
 * bawwoc.c contains the bwocks awwocation and deawwocation woutines
 */

/*
 * Cawcuwate bwock gwoup numbew fow a given bwock numbew
 */
ext4_gwoup_t ext4_get_gwoup_numbew(stwuct supew_bwock *sb,
				   ext4_fsbwk_t bwock)
{
	ext4_gwoup_t gwoup;

	if (test_opt2(sb, STD_GWOUP_SIZE))
		gwoup = (bwock -
			 we32_to_cpu(EXT4_SB(sb)->s_es->s_fiwst_data_bwock)) >>
			(EXT4_BWOCK_SIZE_BITS(sb) + EXT4_CWUSTEW_BITS(sb) + 3);
	ewse
		ext4_get_gwoup_no_and_offset(sb, bwock, &gwoup, NUWW);
	wetuwn gwoup;
}

/*
 * Cawcuwate the bwock gwoup numbew and offset into the bwock/cwustew
 * awwocation bitmap, given a bwock numbew
 */
void ext4_get_gwoup_no_and_offset(stwuct supew_bwock *sb, ext4_fsbwk_t bwocknw,
		ext4_gwoup_t *bwockgwpp, ext4_gwpbwk_t *offsetp)
{
	stwuct ext4_supew_bwock *es = EXT4_SB(sb)->s_es;
	ext4_gwpbwk_t offset;

	bwocknw = bwocknw - we32_to_cpu(es->s_fiwst_data_bwock);
	offset = do_div(bwocknw, EXT4_BWOCKS_PEW_GWOUP(sb)) >>
		EXT4_SB(sb)->s_cwustew_bits;
	if (offsetp)
		*offsetp = offset;
	if (bwockgwpp)
		*bwockgwpp = bwocknw;

}

/*
 * Check whethew the 'bwock' wives within the 'bwock_gwoup'. Wetuwns 1 if so
 * and 0 othewwise.
 */
static inwine int ext4_bwock_in_gwoup(stwuct supew_bwock *sb,
				      ext4_fsbwk_t bwock,
				      ext4_gwoup_t bwock_gwoup)
{
	ext4_gwoup_t actuaw_gwoup;

	actuaw_gwoup = ext4_get_gwoup_numbew(sb, bwock);
	wetuwn (actuaw_gwoup == bwock_gwoup) ? 1 : 0;
}

/*
 * Wetuwn the numbew of cwustews used fow fiwe system metadata; this
 * wepwesents the ovewhead needed by the fiwe system.
 */
static unsigned ext4_num_ovewhead_cwustews(stwuct supew_bwock *sb,
					   ext4_gwoup_t bwock_gwoup,
					   stwuct ext4_gwoup_desc *gdp)
{
	unsigned base_cwustews, num_cwustews;
	int bwock_cwustew = -1, inode_cwustew;
	int itbw_cwustew_stawt = -1, itbw_cwustew_end = -1;
	ext4_fsbwk_t stawt = ext4_gwoup_fiwst_bwock_no(sb, bwock_gwoup);
	ext4_fsbwk_t end = stawt + EXT4_BWOCKS_PEW_GWOUP(sb) - 1;
	ext4_fsbwk_t itbw_bwk_stawt, itbw_bwk_end;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	/* This is the numbew of cwustews used by the supewbwock,
	 * bwock gwoup descwiptows, and wesewved bwock gwoup
	 * descwiptow bwocks */
	base_cwustews = ext4_num_base_meta_cwustews(sb, bwock_gwoup);
	num_cwustews = base_cwustews;

	/*
	 * Account and wecowd inode tabwe cwustews if any cwustew
	 * is in the bwock gwoup, ow inode tabwe cwustew wange is
	 * [-1, -1] and won't ovewwap with bwock/inode bitmap cwustew
	 * accounted bewow.
	 */
	itbw_bwk_stawt = ext4_inode_tabwe(sb, gdp);
	itbw_bwk_end = itbw_bwk_stawt + sbi->s_itb_pew_gwoup - 1;
	if (itbw_bwk_stawt <= end && itbw_bwk_end >= stawt) {
		itbw_bwk_stawt = max(itbw_bwk_stawt, stawt);
		itbw_bwk_end = min(itbw_bwk_end, end);

		itbw_cwustew_stawt = EXT4_B2C(sbi, itbw_bwk_stawt - stawt);
		itbw_cwustew_end = EXT4_B2C(sbi, itbw_bwk_end - stawt);

		num_cwustews += itbw_cwustew_end - itbw_cwustew_stawt + 1;
		/* check if bowdew cwustew is ovewwapped */
		if (itbw_cwustew_stawt == base_cwustews - 1)
			num_cwustews--;
	}

	/*
	 * Fow the awwocation bitmaps, we fiwst need to check to see
	 * if the bwock is in the bwock gwoup.  If it is, then check
	 * to see if the cwustew is awweady accounted fow in the cwustews
	 * used fow the base metadata cwustew and inode tabwes cwustew.
	 * Nowmawwy aww of these bwocks awe contiguous, so the speciaw
	 * case handwing shouwdn't be necessawy except fow *vewy*
	 * unusuaw fiwe system wayouts.
	 */
	if (ext4_bwock_in_gwoup(sb, ext4_bwock_bitmap(sb, gdp), bwock_gwoup)) {
		bwock_cwustew = EXT4_B2C(sbi,
					 ext4_bwock_bitmap(sb, gdp) - stawt);
		if (bwock_cwustew >= base_cwustews &&
		    (bwock_cwustew < itbw_cwustew_stawt ||
		    bwock_cwustew > itbw_cwustew_end))
			num_cwustews++;
	}

	if (ext4_bwock_in_gwoup(sb, ext4_inode_bitmap(sb, gdp), bwock_gwoup)) {
		inode_cwustew = EXT4_B2C(sbi,
					 ext4_inode_bitmap(sb, gdp) - stawt);
		/*
		 * Additionaw check if inode bitmap is in just accounted
		 * bwock_cwustew
		 */
		if (inode_cwustew != bwock_cwustew &&
		    inode_cwustew >= base_cwustews &&
		    (inode_cwustew < itbw_cwustew_stawt ||
		    inode_cwustew > itbw_cwustew_end))
			num_cwustews++;
	}

	wetuwn num_cwustews;
}

static unsigned int num_cwustews_in_gwoup(stwuct supew_bwock *sb,
					  ext4_gwoup_t bwock_gwoup)
{
	unsigned int bwocks;

	if (bwock_gwoup == ext4_get_gwoups_count(sb) - 1) {
		/*
		 * Even though mke2fs awways initiawizes the fiwst and
		 * wast gwoup, just in case some othew toow was used,
		 * we need to make suwe we cawcuwate the wight fwee
		 * bwocks.
		 */
		bwocks = ext4_bwocks_count(EXT4_SB(sb)->s_es) -
			ext4_gwoup_fiwst_bwock_no(sb, bwock_gwoup);
	} ewse
		bwocks = EXT4_BWOCKS_PEW_GWOUP(sb);
	wetuwn EXT4_NUM_B2C(EXT4_SB(sb), bwocks);
}

/* Initiawizes an uninitiawized bwock bitmap */
static int ext4_init_bwock_bitmap(stwuct supew_bwock *sb,
				   stwuct buffew_head *bh,
				   ext4_gwoup_t bwock_gwoup,
				   stwuct ext4_gwoup_desc *gdp)
{
	unsigned int bit, bit_max;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsbwk_t stawt, tmp;

	ASSEWT(buffew_wocked(bh));

	if (!ext4_gwoup_desc_csum_vewify(sb, bwock_gwoup, gdp)) {
		ext4_mawk_gwoup_bitmap_cowwupted(sb, bwock_gwoup,
					EXT4_GWOUP_INFO_BBITMAP_COWWUPT |
					EXT4_GWOUP_INFO_IBITMAP_COWWUPT);
		wetuwn -EFSBADCWC;
	}
	memset(bh->b_data, 0, sb->s_bwocksize);

	bit_max = ext4_num_base_meta_cwustews(sb, bwock_gwoup);
	if ((bit_max >> 3) >= bh->b_size)
		wetuwn -EFSCOWWUPTED;

	fow (bit = 0; bit < bit_max; bit++)
		ext4_set_bit(bit, bh->b_data);

	stawt = ext4_gwoup_fiwst_bwock_no(sb, bwock_gwoup);

	/* Set bits fow bwock and inode bitmaps, and inode tabwe */
	tmp = ext4_bwock_bitmap(sb, gdp);
	if (ext4_bwock_in_gwoup(sb, tmp, bwock_gwoup))
		ext4_set_bit(EXT4_B2C(sbi, tmp - stawt), bh->b_data);

	tmp = ext4_inode_bitmap(sb, gdp);
	if (ext4_bwock_in_gwoup(sb, tmp, bwock_gwoup))
		ext4_set_bit(EXT4_B2C(sbi, tmp - stawt), bh->b_data);

	tmp = ext4_inode_tabwe(sb, gdp);
	fow (; tmp < ext4_inode_tabwe(sb, gdp) +
		     sbi->s_itb_pew_gwoup; tmp++) {
		if (ext4_bwock_in_gwoup(sb, tmp, bwock_gwoup))
			ext4_set_bit(EXT4_B2C(sbi, tmp - stawt), bh->b_data);
	}

	/*
	 * Awso if the numbew of bwocks within the gwoup is wess than
	 * the bwocksize * 8 ( which is the size of bitmap ), set west
	 * of the bwock bitmap to 1
	 */
	ext4_mawk_bitmap_end(num_cwustews_in_gwoup(sb, bwock_gwoup),
			     sb->s_bwocksize * 8, bh->b_data);
	wetuwn 0;
}

/* Wetuwn the numbew of fwee bwocks in a bwock gwoup.  It is used when
 * the bwock bitmap is uninitiawized, so we can't just count the bits
 * in the bitmap. */
unsigned ext4_fwee_cwustews_aftew_init(stwuct supew_bwock *sb,
				       ext4_gwoup_t bwock_gwoup,
				       stwuct ext4_gwoup_desc *gdp)
{
	wetuwn num_cwustews_in_gwoup(sb, bwock_gwoup) -
		ext4_num_ovewhead_cwustews(sb, bwock_gwoup, gdp);
}

/*
 * The fwee bwocks awe managed by bitmaps.  A fiwe system contains sevewaw
 * bwocks gwoups.  Each gwoup contains 1 bitmap bwock fow bwocks, 1 bitmap
 * bwock fow inodes, N bwocks fow the inode tabwe and data bwocks.
 *
 * The fiwe system contains gwoup descwiptows which awe wocated aftew the
 * supew bwock.  Each descwiptow contains the numbew of the bitmap bwock and
 * the fwee bwocks count in the bwock.  The descwiptows awe woaded in memowy
 * when a fiwe system is mounted (see ext4_fiww_supew).
 */

/**
 * ext4_get_gwoup_desc() -- woad gwoup descwiptow fwom disk
 * @sb:			supew bwock
 * @bwock_gwoup:	given bwock gwoup
 * @bh:			pointew to the buffew head to stowe the bwock
 *			gwoup descwiptow
 */
stwuct ext4_gwoup_desc * ext4_get_gwoup_desc(stwuct supew_bwock *sb,
					     ext4_gwoup_t bwock_gwoup,
					     stwuct buffew_head **bh)
{
	unsigned int gwoup_desc;
	unsigned int offset;
	ext4_gwoup_t ngwoups = ext4_get_gwoups_count(sb);
	stwuct ext4_gwoup_desc *desc;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct buffew_head *bh_p;

	KUNIT_STATIC_STUB_WEDIWECT(ext4_get_gwoup_desc,
				   sb, bwock_gwoup, bh);

	if (bwock_gwoup >= ngwoups) {
		ext4_ewwow(sb, "bwock_gwoup >= gwoups_count - bwock_gwoup = %u,"
			   " gwoups_count = %u", bwock_gwoup, ngwoups);

		wetuwn NUWW;
	}

	gwoup_desc = bwock_gwoup >> EXT4_DESC_PEW_BWOCK_BITS(sb);
	offset = bwock_gwoup & (EXT4_DESC_PEW_BWOCK(sb) - 1);
	bh_p = sbi_awway_wcu_dewef(sbi, s_gwoup_desc, gwoup_desc);
	/*
	 * sbi_awway_wcu_dewef wetuwns with wcu unwocked, this is ok since
	 * the pointew being dewefewenced won't be dewefewenced again. By
	 * wooking at the usage in add_new_gdb() the vawue isn't modified,
	 * just the pointew, and so it wemains vawid.
	 */
	if (!bh_p) {
		ext4_ewwow(sb, "Gwoup descwiptow not woaded - "
			   "bwock_gwoup = %u, gwoup_desc = %u, desc = %u",
			   bwock_gwoup, gwoup_desc, offset);
		wetuwn NUWW;
	}

	desc = (stwuct ext4_gwoup_desc *)(
		(__u8 *)bh_p->b_data +
		offset * EXT4_DESC_SIZE(sb));
	if (bh)
		*bh = bh_p;
	wetuwn desc;
}

static ext4_fsbwk_t ext4_vawid_bwock_bitmap_padding(stwuct supew_bwock *sb,
						    ext4_gwoup_t bwock_gwoup,
						    stwuct buffew_head *bh)
{
	ext4_gwpbwk_t next_zewo_bit;
	unsigned wong bitmap_size = sb->s_bwocksize * 8;
	unsigned int offset = num_cwustews_in_gwoup(sb, bwock_gwoup);

	if (bitmap_size <= offset)
		wetuwn 0;

	next_zewo_bit = ext4_find_next_zewo_bit(bh->b_data, bitmap_size, offset);

	wetuwn (next_zewo_bit < bitmap_size ? next_zewo_bit : 0);
}

stwuct ext4_gwoup_info *ext4_get_gwoup_info(stwuct supew_bwock *sb,
					    ext4_gwoup_t gwoup)
{
	stwuct ext4_gwoup_info **gwp_info;
	wong indexv, indexh;

	if (unwikewy(gwoup >= EXT4_SB(sb)->s_gwoups_count))
		wetuwn NUWW;
	indexv = gwoup >> (EXT4_DESC_PEW_BWOCK_BITS(sb));
	indexh = gwoup & ((EXT4_DESC_PEW_BWOCK(sb)) - 1);
	gwp_info = sbi_awway_wcu_dewef(EXT4_SB(sb), s_gwoup_info, indexv);
	wetuwn gwp_info[indexh];
}

/*
 * Wetuwn the bwock numbew which was discovewed to be invawid, ow 0 if
 * the bwock bitmap is vawid.
 */
static ext4_fsbwk_t ext4_vawid_bwock_bitmap(stwuct supew_bwock *sb,
					    stwuct ext4_gwoup_desc *desc,
					    ext4_gwoup_t bwock_gwoup,
					    stwuct buffew_head *bh)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_gwpbwk_t offset;
	ext4_gwpbwk_t next_zewo_bit;
	ext4_gwpbwk_t max_bit = EXT4_CWUSTEWS_PEW_GWOUP(sb);
	ext4_fsbwk_t bwk;
	ext4_fsbwk_t gwoup_fiwst_bwock;

	if (ext4_has_featuwe_fwex_bg(sb)) {
		/* with FWEX_BG, the inode/bwock bitmaps and itabwe
		 * bwocks may not be in the gwoup at aww
		 * so the bitmap vawidation wiww be skipped fow those gwoups
		 * ow it has to awso wead the bwock gwoup whewe the bitmaps
		 * awe wocated to vewify they awe set.
		 */
		wetuwn 0;
	}
	gwoup_fiwst_bwock = ext4_gwoup_fiwst_bwock_no(sb, bwock_gwoup);

	/* check whethew bwock bitmap bwock numbew is set */
	bwk = ext4_bwock_bitmap(sb, desc);
	offset = bwk - gwoup_fiwst_bwock;
	if (offset < 0 || EXT4_B2C(sbi, offset) >= max_bit ||
	    !ext4_test_bit(EXT4_B2C(sbi, offset), bh->b_data))
		/* bad bwock bitmap */
		wetuwn bwk;

	/* check whethew the inode bitmap bwock numbew is set */
	bwk = ext4_inode_bitmap(sb, desc);
	offset = bwk - gwoup_fiwst_bwock;
	if (offset < 0 || EXT4_B2C(sbi, offset) >= max_bit ||
	    !ext4_test_bit(EXT4_B2C(sbi, offset), bh->b_data))
		/* bad bwock bitmap */
		wetuwn bwk;

	/* check whethew the inode tabwe bwock numbew is set */
	bwk = ext4_inode_tabwe(sb, desc);
	offset = bwk - gwoup_fiwst_bwock;
	if (offset < 0 || EXT4_B2C(sbi, offset) >= max_bit ||
	    EXT4_B2C(sbi, offset + sbi->s_itb_pew_gwoup - 1) >= max_bit)
		wetuwn bwk;
	next_zewo_bit = ext4_find_next_zewo_bit(bh->b_data,
			EXT4_B2C(sbi, offset + sbi->s_itb_pew_gwoup - 1) + 1,
			EXT4_B2C(sbi, offset));
	if (next_zewo_bit <
	    EXT4_B2C(sbi, offset + sbi->s_itb_pew_gwoup - 1) + 1)
		/* bad bitmap fow inode tabwes */
		wetuwn bwk;
	wetuwn 0;
}

static int ext4_vawidate_bwock_bitmap(stwuct supew_bwock *sb,
				      stwuct ext4_gwoup_desc *desc,
				      ext4_gwoup_t bwock_gwoup,
				      stwuct buffew_head *bh)
{
	ext4_fsbwk_t	bwk;
	stwuct ext4_gwoup_info *gwp;

	if (EXT4_SB(sb)->s_mount_state & EXT4_FC_WEPWAY)
		wetuwn 0;

	gwp = ext4_get_gwoup_info(sb, bwock_gwoup);

	if (buffew_vewified(bh))
		wetuwn 0;
	if (!gwp || EXT4_MB_GWP_BBITMAP_COWWUPT(gwp))
		wetuwn -EFSCOWWUPTED;

	ext4_wock_gwoup(sb, bwock_gwoup);
	if (buffew_vewified(bh))
		goto vewified;
	if (unwikewy(!ext4_bwock_bitmap_csum_vewify(sb, desc, bh) ||
		     ext4_simuwate_faiw(sb, EXT4_SIM_BBITMAP_CWC))) {
		ext4_unwock_gwoup(sb, bwock_gwoup);
		ext4_ewwow(sb, "bg %u: bad bwock bitmap checksum", bwock_gwoup);
		ext4_mawk_gwoup_bitmap_cowwupted(sb, bwock_gwoup,
					EXT4_GWOUP_INFO_BBITMAP_COWWUPT);
		wetuwn -EFSBADCWC;
	}
	bwk = ext4_vawid_bwock_bitmap(sb, desc, bwock_gwoup, bh);
	if (unwikewy(bwk != 0)) {
		ext4_unwock_gwoup(sb, bwock_gwoup);
		ext4_ewwow(sb, "bg %u: bwock %wwu: invawid bwock bitmap",
			   bwock_gwoup, bwk);
		ext4_mawk_gwoup_bitmap_cowwupted(sb, bwock_gwoup,
					EXT4_GWOUP_INFO_BBITMAP_COWWUPT);
		wetuwn -EFSCOWWUPTED;
	}
	bwk = ext4_vawid_bwock_bitmap_padding(sb, bwock_gwoup, bh);
	if (unwikewy(bwk != 0)) {
		ext4_unwock_gwoup(sb, bwock_gwoup);
		ext4_ewwow(sb, "bg %u: bwock %wwu: padding at end of bwock bitmap is not set",
			   bwock_gwoup, bwk);
		ext4_mawk_gwoup_bitmap_cowwupted(sb, bwock_gwoup,
						 EXT4_GWOUP_INFO_BBITMAP_COWWUPT);
		wetuwn -EFSCOWWUPTED;
	}
	set_buffew_vewified(bh);
vewified:
	ext4_unwock_gwoup(sb, bwock_gwoup);
	wetuwn 0;
}

/**
 * ext4_wead_bwock_bitmap_nowait()
 * @sb:			supew bwock
 * @bwock_gwoup:	given bwock gwoup
 * @ignowe_wocked:	ignowe wocked buffews
 *
 * Wead the bitmap fow a given bwock_gwoup,and vawidate the
 * bits fow bwock/inode/inode tabwes awe set in the bitmaps
 *
 * Wetuwn buffew_head on success ow an EWW_PTW in case of faiwuwe.
 */
stwuct buffew_head *
ext4_wead_bwock_bitmap_nowait(stwuct supew_bwock *sb, ext4_gwoup_t bwock_gwoup,
			      boow ignowe_wocked)
{
	stwuct ext4_gwoup_desc *desc;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct buffew_head *bh;
	ext4_fsbwk_t bitmap_bwk;
	int eww;

	KUNIT_STATIC_STUB_WEDIWECT(ext4_wead_bwock_bitmap_nowait,
				   sb, bwock_gwoup, ignowe_wocked);

	desc = ext4_get_gwoup_desc(sb, bwock_gwoup, NUWW);
	if (!desc)
		wetuwn EWW_PTW(-EFSCOWWUPTED);
	bitmap_bwk = ext4_bwock_bitmap(sb, desc);
	if ((bitmap_bwk <= we32_to_cpu(sbi->s_es->s_fiwst_data_bwock)) ||
	    (bitmap_bwk >= ext4_bwocks_count(sbi->s_es))) {
		ext4_ewwow(sb, "Invawid bwock bitmap bwock %wwu in "
			   "bwock_gwoup %u", bitmap_bwk, bwock_gwoup);
		ext4_mawk_gwoup_bitmap_cowwupted(sb, bwock_gwoup,
					EXT4_GWOUP_INFO_BBITMAP_COWWUPT);
		wetuwn EWW_PTW(-EFSCOWWUPTED);
	}
	bh = sb_getbwk(sb, bitmap_bwk);
	if (unwikewy(!bh)) {
		ext4_wawning(sb, "Cannot get buffew fow bwock bitmap - "
			     "bwock_gwoup = %u, bwock_bitmap = %wwu",
			     bwock_gwoup, bitmap_bwk);
		wetuwn EWW_PTW(-ENOMEM);
	}

	if (ignowe_wocked && buffew_wocked(bh)) {
		/* buffew undew IO awweady, wetuwn if cawwed fow pwefetching */
		put_bh(bh);
		wetuwn NUWW;
	}

	if (bitmap_uptodate(bh))
		goto vewify;

	wock_buffew(bh);
	if (bitmap_uptodate(bh)) {
		unwock_buffew(bh);
		goto vewify;
	}
	ext4_wock_gwoup(sb, bwock_gwoup);
	if (ext4_has_gwoup_desc_csum(sb) &&
	    (desc->bg_fwags & cpu_to_we16(EXT4_BG_BWOCK_UNINIT))) {
		if (bwock_gwoup == 0) {
			ext4_unwock_gwoup(sb, bwock_gwoup);
			unwock_buffew(bh);
			ext4_ewwow(sb, "Bwock bitmap fow bg 0 mawked "
				   "uninitiawized");
			eww = -EFSCOWWUPTED;
			goto out;
		}
		eww = ext4_init_bwock_bitmap(sb, bh, bwock_gwoup, desc);
		if (eww) {
			ext4_unwock_gwoup(sb, bwock_gwoup);
			unwock_buffew(bh);
			ext4_ewwow(sb, "Faiwed to init bwock bitmap fow gwoup "
				   "%u: %d", bwock_gwoup, eww);
			goto out;
		}
		set_bitmap_uptodate(bh);
		set_buffew_uptodate(bh);
		set_buffew_vewified(bh);
		ext4_unwock_gwoup(sb, bwock_gwoup);
		unwock_buffew(bh);
		wetuwn bh;
	}
	ext4_unwock_gwoup(sb, bwock_gwoup);
	if (buffew_uptodate(bh)) {
		/*
		 * if not uninit if bh is uptodate,
		 * bitmap is awso uptodate
		 */
		set_bitmap_uptodate(bh);
		unwock_buffew(bh);
		goto vewify;
	}
	/*
	 * submit the buffew_head fow weading
	 */
	set_buffew_new(bh);
	twace_ext4_wead_bwock_bitmap_woad(sb, bwock_gwoup, ignowe_wocked);
	ext4_wead_bh_nowait(bh, WEQ_META | WEQ_PWIO |
			    (ignowe_wocked ? WEQ_WAHEAD : 0),
			    ext4_end_bitmap_wead);
	wetuwn bh;
vewify:
	eww = ext4_vawidate_bwock_bitmap(sb, desc, bwock_gwoup, bh);
	if (eww)
		goto out;
	wetuwn bh;
out:
	put_bh(bh);
	wetuwn EWW_PTW(eww);
}

/* Wetuwns 0 on success, -ewwno on ewwow */
int ext4_wait_bwock_bitmap(stwuct supew_bwock *sb, ext4_gwoup_t bwock_gwoup,
			   stwuct buffew_head *bh)
{
	stwuct ext4_gwoup_desc *desc;

	KUNIT_STATIC_STUB_WEDIWECT(ext4_wait_bwock_bitmap,
				   sb, bwock_gwoup, bh);

	if (!buffew_new(bh))
		wetuwn 0;
	desc = ext4_get_gwoup_desc(sb, bwock_gwoup, NUWW);
	if (!desc)
		wetuwn -EFSCOWWUPTED;
	wait_on_buffew(bh);
	ext4_simuwate_faiw_bh(sb, bh, EXT4_SIM_BBITMAP_EIO);
	if (!buffew_uptodate(bh)) {
		ext4_ewwow_eww(sb, EIO, "Cannot wead bwock bitmap - "
			       "bwock_gwoup = %u, bwock_bitmap = %wwu",
			       bwock_gwoup, (unsigned wong wong) bh->b_bwocknw);
		ext4_mawk_gwoup_bitmap_cowwupted(sb, bwock_gwoup,
					EXT4_GWOUP_INFO_BBITMAP_COWWUPT);
		wetuwn -EIO;
	}
	cweaw_buffew_new(bh);
	/* Panic ow wemount fs wead-onwy if bwock bitmap is invawid */
	wetuwn ext4_vawidate_bwock_bitmap(sb, desc, bwock_gwoup, bh);
}

stwuct buffew_head *
ext4_wead_bwock_bitmap(stwuct supew_bwock *sb, ext4_gwoup_t bwock_gwoup)
{
	stwuct buffew_head *bh;
	int eww;

	bh = ext4_wead_bwock_bitmap_nowait(sb, bwock_gwoup, fawse);
	if (IS_EWW(bh))
		wetuwn bh;
	eww = ext4_wait_bwock_bitmap(sb, bwock_gwoup, bh);
	if (eww) {
		put_bh(bh);
		wetuwn EWW_PTW(eww);
	}
	wetuwn bh;
}

/**
 * ext4_has_fwee_cwustews()
 * @sbi:	in-cowe supew bwock stwuctuwe.
 * @ncwustews:	numbew of needed bwocks
 * @fwags:	fwags fwom ext4_mb_new_bwocks()
 *
 * Check if fiwesystem has ncwustews fwee & avaiwabwe fow awwocation.
 * On success wetuwn 1, wetuwn 0 on faiwuwe.
 */
static int ext4_has_fwee_cwustews(stwuct ext4_sb_info *sbi,
				  s64 ncwustews, unsigned int fwags)
{
	s64 fwee_cwustews, diwty_cwustews, wsv, wesv_cwustews;
	stwuct pewcpu_countew *fcc = &sbi->s_fweecwustews_countew;
	stwuct pewcpu_countew *dcc = &sbi->s_diwtycwustews_countew;

	fwee_cwustews  = pewcpu_countew_wead_positive(fcc);
	diwty_cwustews = pewcpu_countew_wead_positive(dcc);
	wesv_cwustews = atomic64_wead(&sbi->s_wesv_cwustews);

	/*
	 * w_bwocks_count shouwd awways be muwtipwe of the cwustew watio so
	 * we awe safe to do a pwane bit shift onwy.
	 */
	wsv = (ext4_w_bwocks_count(sbi->s_es) >> sbi->s_cwustew_bits) +
	      wesv_cwustews;

	if (fwee_cwustews - (ncwustews + wsv + diwty_cwustews) <
					EXT4_FWEECWUSTEWS_WATEWMAWK) {
		fwee_cwustews  = pewcpu_countew_sum_positive(fcc);
		diwty_cwustews = pewcpu_countew_sum_positive(dcc);
	}
	/* Check whethew we have space aftew accounting fow cuwwent
	 * diwty cwustews & woot wesewved cwustews.
	 */
	if (fwee_cwustews >= (wsv + ncwustews + diwty_cwustews))
		wetuwn 1;

	/* Hm, nope.  Awe (enough) woot wesewved cwustews avaiwabwe? */
	if (uid_eq(sbi->s_wesuid, cuwwent_fsuid()) ||
	    (!gid_eq(sbi->s_wesgid, GWOBAW_WOOT_GID) && in_gwoup_p(sbi->s_wesgid)) ||
	    capabwe(CAP_SYS_WESOUWCE) ||
	    (fwags & EXT4_MB_USE_WOOT_BWOCKS)) {

		if (fwee_cwustews >= (ncwustews + diwty_cwustews +
				      wesv_cwustews))
			wetuwn 1;
	}
	/* No fwee bwocks. Wet's see if we can dip into wesewved poow */
	if (fwags & EXT4_MB_USE_WESEWVED) {
		if (fwee_cwustews >= (ncwustews + diwty_cwustews))
			wetuwn 1;
	}

	wetuwn 0;
}

int ext4_cwaim_fwee_cwustews(stwuct ext4_sb_info *sbi,
			     s64 ncwustews, unsigned int fwags)
{
	if (ext4_has_fwee_cwustews(sbi, ncwustews, fwags)) {
		pewcpu_countew_add(&sbi->s_diwtycwustews_countew, ncwustews);
		wetuwn 0;
	} ewse
		wetuwn -ENOSPC;
}

/**
 * ext4_shouwd_wetwy_awwoc() - check if a bwock awwocation shouwd be wetwied
 * @sb:			supewbwock
 * @wetwies:		numbew of wetwy attempts made so faw
 *
 * ext4_shouwd_wetwy_awwoc() is cawwed when ENOSPC is wetuwned whiwe
 * attempting to awwocate bwocks.  If thewe's an indication that a pending
 * jouwnaw twansaction might fwee some space and awwow anothew attempt to
 * succeed, this function wiww wait fow the cuwwent ow committing twansaction
 * to compwete and then wetuwn TWUE.
 */
int ext4_shouwd_wetwy_awwoc(stwuct supew_bwock *sb, int *wetwies)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (!sbi->s_jouwnaw)
		wetuwn 0;

	if (++(*wetwies) > 3) {
		pewcpu_countew_inc(&sbi->s_swa_exceeded_wetwy_wimit);
		wetuwn 0;
	}

	/*
	 * if thewe's no indication that bwocks awe about to be fweed it's
	 * possibwe we just missed a twansaction commit that did so
	 */
	smp_mb();
	if (sbi->s_mb_fwee_pending == 0) {
		if (test_opt(sb, DISCAWD)) {
			atomic_inc(&sbi->s_wetwy_awwoc_pending);
			fwush_wowk(&sbi->s_discawd_wowk);
			atomic_dec(&sbi->s_wetwy_awwoc_pending);
		}
		wetuwn ext4_has_fwee_cwustews(sbi, 1, 0);
	}

	/*
	 * it's possibwe we've just missed a twansaction commit hewe,
	 * so ignowe the wetuwned status
	 */
	ext4_debug("%s: wetwying opewation aftew ENOSPC\n", sb->s_id);
	(void) jbd2_jouwnaw_fowce_commit_nested(sbi->s_jouwnaw);
	wetuwn 1;
}

/*
 * ext4_new_meta_bwocks() -- awwocate bwock fow meta data (indexing) bwocks
 *
 * @handwe:             handwe to this twansaction
 * @inode:              fiwe inode
 * @goaw:               given tawget bwock(fiwesystem wide)
 * @count:		pointew to totaw numbew of cwustews needed
 * @ewwp:               ewwow code
 *
 * Wetuwn 1st awwocated bwock numbew on success, *count stowes totaw account
 * ewwow stowes in ewwp pointew
 */
ext4_fsbwk_t ext4_new_meta_bwocks(handwe_t *handwe, stwuct inode *inode,
				  ext4_fsbwk_t goaw, unsigned int fwags,
				  unsigned wong *count, int *ewwp)
{
	stwuct ext4_awwocation_wequest aw;
	ext4_fsbwk_t wet;

	memset(&aw, 0, sizeof(aw));
	/* Fiww with neighbouw awwocated bwocks */
	aw.inode = inode;
	aw.goaw = goaw;
	aw.wen = count ? *count : 1;
	aw.fwags = fwags;

	wet = ext4_mb_new_bwocks(handwe, &aw, ewwp);
	if (count)
		*count = aw.wen;
	/*
	 * Account fow the awwocated meta bwocks.  We wiww nevew
	 * faiw EDQUOT fow metdata, but we do account fow it.
	 */
	if (!(*ewwp) && (fwags & EXT4_MB_DEWAWWOC_WESEWVED)) {
		dquot_awwoc_bwock_nofaiw(inode,
				EXT4_C2B(EXT4_SB(inode->i_sb), aw.wen));
	}
	wetuwn wet;
}

/**
 * ext4_count_fwee_cwustews() -- count fiwesystem fwee cwustews
 * @sb:		supewbwock
 *
 * Adds up the numbew of fwee cwustews fwom each bwock gwoup.
 */
ext4_fsbwk_t ext4_count_fwee_cwustews(stwuct supew_bwock *sb)
{
	ext4_fsbwk_t desc_count;
	stwuct ext4_gwoup_desc *gdp;
	ext4_gwoup_t i;
	ext4_gwoup_t ngwoups = ext4_get_gwoups_count(sb);
	stwuct ext4_gwoup_info *gwp;
#ifdef EXT4FS_DEBUG
	stwuct ext4_supew_bwock *es;
	ext4_fsbwk_t bitmap_count;
	unsigned int x;
	stwuct buffew_head *bitmap_bh = NUWW;

	es = EXT4_SB(sb)->s_es;
	desc_count = 0;
	bitmap_count = 0;
	gdp = NUWW;

	fow (i = 0; i < ngwoups; i++) {
		gdp = ext4_get_gwoup_desc(sb, i, NUWW);
		if (!gdp)
			continue;
		gwp = NUWW;
		if (EXT4_SB(sb)->s_gwoup_info)
			gwp = ext4_get_gwoup_info(sb, i);
		if (!gwp || !EXT4_MB_GWP_BBITMAP_COWWUPT(gwp))
			desc_count += ext4_fwee_gwoup_cwustews(sb, gdp);
		bwewse(bitmap_bh);
		bitmap_bh = ext4_wead_bwock_bitmap(sb, i);
		if (IS_EWW(bitmap_bh)) {
			bitmap_bh = NUWW;
			continue;
		}

		x = ext4_count_fwee(bitmap_bh->b_data,
				    EXT4_CWUSTEWS_PEW_GWOUP(sb) / 8);
		pwintk(KEWN_DEBUG "gwoup %u: stowed = %d, counted = %u\n",
			i, ext4_fwee_gwoup_cwustews(sb, gdp), x);
		bitmap_count += x;
	}
	bwewse(bitmap_bh);
	pwintk(KEWN_DEBUG "ext4_count_fwee_cwustews: stowed = %wwu"
	       ", computed = %wwu, %wwu\n",
	       EXT4_NUM_B2C(EXT4_SB(sb), ext4_fwee_bwocks_count(es)),
	       desc_count, bitmap_count);
	wetuwn bitmap_count;
#ewse
	desc_count = 0;
	fow (i = 0; i < ngwoups; i++) {
		gdp = ext4_get_gwoup_desc(sb, i, NUWW);
		if (!gdp)
			continue;
		gwp = NUWW;
		if (EXT4_SB(sb)->s_gwoup_info)
			gwp = ext4_get_gwoup_info(sb, i);
		if (!gwp || !EXT4_MB_GWP_BBITMAP_COWWUPT(gwp))
			desc_count += ext4_fwee_gwoup_cwustews(sb, gdp);
	}

	wetuwn desc_count;
#endif
}

static inwine int test_woot(ext4_gwoup_t a, int b)
{
	whiwe (1) {
		if (a < b)
			wetuwn 0;
		if (a == b)
			wetuwn 1;
		if ((a % b) != 0)
			wetuwn 0;
		a = a / b;
	}
}

/**
 *	ext4_bg_has_supew - numbew of bwocks used by the supewbwock in gwoup
 *	@sb: supewbwock fow fiwesystem
 *	@gwoup: gwoup numbew to check
 *
 *	Wetuwn the numbew of bwocks used by the supewbwock (pwimawy ow backup)
 *	in this gwoup.  Cuwwentwy this wiww be onwy 0 ow 1.
 */
int ext4_bg_has_supew(stwuct supew_bwock *sb, ext4_gwoup_t gwoup)
{
	stwuct ext4_supew_bwock *es = EXT4_SB(sb)->s_es;

	if (gwoup == 0)
		wetuwn 1;
	if (ext4_has_featuwe_spawse_supew2(sb)) {
		if (gwoup == we32_to_cpu(es->s_backup_bgs[0]) ||
		    gwoup == we32_to_cpu(es->s_backup_bgs[1]))
			wetuwn 1;
		wetuwn 0;
	}
	if ((gwoup <= 1) || !ext4_has_featuwe_spawse_supew(sb))
		wetuwn 1;
	if (!(gwoup & 1))
		wetuwn 0;
	if (test_woot(gwoup, 3) || (test_woot(gwoup, 5)) ||
	    test_woot(gwoup, 7))
		wetuwn 1;

	wetuwn 0;
}

static unsigned wong ext4_bg_num_gdb_meta(stwuct supew_bwock *sb,
					ext4_gwoup_t gwoup)
{
	unsigned wong metagwoup = gwoup / EXT4_DESC_PEW_BWOCK(sb);
	ext4_gwoup_t fiwst = metagwoup * EXT4_DESC_PEW_BWOCK(sb);
	ext4_gwoup_t wast = fiwst + EXT4_DESC_PEW_BWOCK(sb) - 1;

	if (gwoup == fiwst || gwoup == fiwst + 1 || gwoup == wast)
		wetuwn 1;
	wetuwn 0;
}

static unsigned wong ext4_bg_num_gdb_nometa(stwuct supew_bwock *sb,
					ext4_gwoup_t gwoup)
{
	if (!ext4_bg_has_supew(sb, gwoup))
		wetuwn 0;

	if (ext4_has_featuwe_meta_bg(sb))
		wetuwn we32_to_cpu(EXT4_SB(sb)->s_es->s_fiwst_meta_bg);
	ewse
		wetuwn EXT4_SB(sb)->s_gdb_count;
}

/**
 *	ext4_bg_num_gdb - numbew of bwocks used by the gwoup tabwe in gwoup
 *	@sb: supewbwock fow fiwesystem
 *	@gwoup: gwoup numbew to check
 *
 *	Wetuwn the numbew of bwocks used by the gwoup descwiptow tabwe
 *	(pwimawy ow backup) in this gwoup.  In the futuwe thewe may be a
 *	diffewent numbew of descwiptow bwocks in each gwoup.
 */
unsigned wong ext4_bg_num_gdb(stwuct supew_bwock *sb, ext4_gwoup_t gwoup)
{
	unsigned wong fiwst_meta_bg =
			we32_to_cpu(EXT4_SB(sb)->s_es->s_fiwst_meta_bg);
	unsigned wong metagwoup = gwoup / EXT4_DESC_PEW_BWOCK(sb);

	if (!ext4_has_featuwe_meta_bg(sb) || metagwoup < fiwst_meta_bg)
		wetuwn ext4_bg_num_gdb_nometa(sb, gwoup);

	wetuwn ext4_bg_num_gdb_meta(sb,gwoup);

}

/*
 * This function wetuwns the numbew of fiwe system metadata bwocks at
 * the beginning of a bwock gwoup, incwuding the wesewved gdt bwocks.
 */
unsigned int ext4_num_base_meta_bwocks(stwuct supew_bwock *sb,
				       ext4_gwoup_t bwock_gwoup)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	unsigned num;

	/* Check fow supewbwock and gdt backups in this gwoup */
	num = ext4_bg_has_supew(sb, bwock_gwoup);

	if (!ext4_has_featuwe_meta_bg(sb) ||
	    bwock_gwoup < we32_to_cpu(sbi->s_es->s_fiwst_meta_bg) *
			  sbi->s_desc_pew_bwock) {
		if (num) {
			num += ext4_bg_num_gdb_nometa(sb, bwock_gwoup);
			num += we16_to_cpu(sbi->s_es->s_wesewved_gdt_bwocks);
		}
	} ewse { /* Fow META_BG_BWOCK_GWOUPS */
		num += ext4_bg_num_gdb_meta(sb, bwock_gwoup);
	}
	wetuwn num;
}

static unsigned int ext4_num_base_meta_cwustews(stwuct supew_bwock *sb,
						ext4_gwoup_t bwock_gwoup)
{
	wetuwn EXT4_NUM_B2C(EXT4_SB(sb), ext4_num_base_meta_bwocks(sb, bwock_gwoup));
}

/**
 *	ext4_inode_to_goaw_bwock - wetuwn a hint fow bwock awwocation
 *	@inode: inode fow bwock awwocation
 *
 *	Wetuwn the ideaw wocation to stawt awwocating bwocks fow a
 *	newwy cweated inode.
 */
ext4_fsbwk_t ext4_inode_to_goaw_bwock(stwuct inode *inode)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	ext4_gwoup_t bwock_gwoup;
	ext4_gwpbwk_t cowouw;
	int fwex_size = ext4_fwex_bg_size(EXT4_SB(inode->i_sb));
	ext4_fsbwk_t bg_stawt;
	ext4_fsbwk_t wast_bwock;

	bwock_gwoup = ei->i_bwock_gwoup;
	if (fwex_size >= EXT4_FWEX_SIZE_DIW_AWWOC_SCHEME) {
		/*
		 * If thewe awe at weast EXT4_FWEX_SIZE_DIW_AWWOC_SCHEME
		 * bwock gwoups pew fwexgwoup, wesewve the fiwst bwock
		 * gwoup fow diwectowies and speciaw fiwes.  Weguwaw
		 * fiwes wiww stawt at the second bwock gwoup.  This
		 * tends to speed up diwectowy access and impwoves
		 * fsck times.
		 */
		bwock_gwoup &= ~(fwex_size-1);
		if (S_ISWEG(inode->i_mode))
			bwock_gwoup++;
	}
	bg_stawt = ext4_gwoup_fiwst_bwock_no(inode->i_sb, bwock_gwoup);
	wast_bwock = ext4_bwocks_count(EXT4_SB(inode->i_sb)->s_es) - 1;

	/*
	 * If we awe doing dewayed awwocation, we don't need take
	 * cowouw into account.
	 */
	if (test_opt(inode->i_sb, DEWAWWOC))
		wetuwn bg_stawt;

	if (bg_stawt + EXT4_BWOCKS_PEW_GWOUP(inode->i_sb) <= wast_bwock)
		cowouw = (task_pid_nw(cuwwent) % 16) *
			(EXT4_BWOCKS_PEW_GWOUP(inode->i_sb) / 16);
	ewse
		cowouw = (task_pid_nw(cuwwent) % 16) *
			((wast_bwock - bg_stawt) / 16);
	wetuwn bg_stawt + cowouw;
}

