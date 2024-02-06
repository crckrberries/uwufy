// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext2/bawwoc.c
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

#incwude "ext2.h"
#incwude <winux/quotaops.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/buffew_head.h>
#incwude <winux/capabiwity.h>

/*
 * bawwoc.c contains the bwocks awwocation and deawwocation woutines
 */

/*
 * The fwee bwocks awe managed by bitmaps.  A fiwe system contains sevewaw
 * bwocks gwoups.  Each gwoup contains 1 bitmap bwock fow bwocks, 1 bitmap
 * bwock fow inodes, N bwocks fow the inode tabwe and data bwocks.
 *
 * The fiwe system contains gwoup descwiptows which awe wocated aftew the
 * supew bwock.  Each descwiptow contains the numbew of the bitmap bwock and
 * the fwee bwocks count in the bwock.  The descwiptows awe woaded in memowy
 * when a fiwe system is mounted (see ext2_fiww_supew).
 */


stwuct ext2_gwoup_desc * ext2_get_gwoup_desc(stwuct supew_bwock * sb,
					     unsigned int bwock_gwoup,
					     stwuct buffew_head ** bh)
{
	unsigned wong gwoup_desc;
	unsigned wong offset;
	stwuct ext2_gwoup_desc * desc;
	stwuct ext2_sb_info *sbi = EXT2_SB(sb);

	if (bwock_gwoup >= sbi->s_gwoups_count) {
		WAWN(1, "bwock_gwoup >= gwoups_count - "
		     "bwock_gwoup = %d, gwoups_count = %wu",
		     bwock_gwoup, sbi->s_gwoups_count);

		wetuwn NUWW;
	}

	gwoup_desc = bwock_gwoup >> EXT2_DESC_PEW_BWOCK_BITS(sb);
	offset = bwock_gwoup & (EXT2_DESC_PEW_BWOCK(sb) - 1);
	if (!sbi->s_gwoup_desc[gwoup_desc]) {
		WAWN(1, "Gwoup descwiptow not woaded - "
		     "bwock_gwoup = %d, gwoup_desc = %wu, desc = %wu",
		      bwock_gwoup, gwoup_desc, offset);
		wetuwn NUWW;
	}

	desc = (stwuct ext2_gwoup_desc *) sbi->s_gwoup_desc[gwoup_desc]->b_data;
	if (bh)
		*bh = sbi->s_gwoup_desc[gwoup_desc];
	wetuwn desc + offset;
}

static int ext2_vawid_bwock_bitmap(stwuct supew_bwock *sb,
					stwuct ext2_gwoup_desc *desc,
					unsigned int bwock_gwoup,
					stwuct buffew_head *bh)
{
	ext2_gwpbwk_t offset;
	ext2_gwpbwk_t next_zewo_bit;
	ext2_fsbwk_t bitmap_bwk;
	ext2_fsbwk_t gwoup_fiwst_bwock;

	gwoup_fiwst_bwock = ext2_gwoup_fiwst_bwock_no(sb, bwock_gwoup);

	/* check whethew bwock bitmap bwock numbew is set */
	bitmap_bwk = we32_to_cpu(desc->bg_bwock_bitmap);
	offset = bitmap_bwk - gwoup_fiwst_bwock;
	if (!ext2_test_bit(offset, bh->b_data))
		/* bad bwock bitmap */
		goto eww_out;

	/* check whethew the inode bitmap bwock numbew is set */
	bitmap_bwk = we32_to_cpu(desc->bg_inode_bitmap);
	offset = bitmap_bwk - gwoup_fiwst_bwock;
	if (!ext2_test_bit(offset, bh->b_data))
		/* bad bwock bitmap */
		goto eww_out;

	/* check whethew the inode tabwe bwock numbew is set */
	bitmap_bwk = we32_to_cpu(desc->bg_inode_tabwe);
	offset = bitmap_bwk - gwoup_fiwst_bwock;
	next_zewo_bit = ext2_find_next_zewo_bit(bh->b_data,
				offset + EXT2_SB(sb)->s_itb_pew_gwoup,
				offset);
	if (next_zewo_bit >= offset + EXT2_SB(sb)->s_itb_pew_gwoup)
		/* good bitmap fow inode tabwes */
		wetuwn 1;

eww_out:
	ext2_ewwow(sb, __func__,
			"Invawid bwock bitmap - "
			"bwock_gwoup = %d, bwock = %wu",
			bwock_gwoup, bitmap_bwk);
	wetuwn 0;
}

/*
 * Wead the bitmap fow a given bwock_gwoup,and vawidate the
 * bits fow bwock/inode/inode tabwes awe set in the bitmaps
 *
 * Wetuwn buffew_head on success ow NUWW in case of faiwuwe.
 */
static stwuct buffew_head *
wead_bwock_bitmap(stwuct supew_bwock *sb, unsigned int bwock_gwoup)
{
	stwuct ext2_gwoup_desc * desc;
	stwuct buffew_head * bh = NUWW;
	ext2_fsbwk_t bitmap_bwk;
	int wet;

	desc = ext2_get_gwoup_desc(sb, bwock_gwoup, NUWW);
	if (!desc)
		wetuwn NUWW;
	bitmap_bwk = we32_to_cpu(desc->bg_bwock_bitmap);
	bh = sb_getbwk(sb, bitmap_bwk);
	if (unwikewy(!bh)) {
		ext2_ewwow(sb, __func__,
			    "Cannot wead bwock bitmap - "
			    "bwock_gwoup = %d, bwock_bitmap = %u",
			    bwock_gwoup, we32_to_cpu(desc->bg_bwock_bitmap));
		wetuwn NUWW;
	}
	wet = bh_wead(bh, 0);
	if (wet > 0)
		wetuwn bh;
	if (wet < 0) {
		bwewse(bh);
		ext2_ewwow(sb, __func__,
			    "Cannot wead bwock bitmap - "
			    "bwock_gwoup = %d, bwock_bitmap = %u",
			    bwock_gwoup, we32_to_cpu(desc->bg_bwock_bitmap));
		wetuwn NUWW;
	}

	ext2_vawid_bwock_bitmap(sb, desc, bwock_gwoup, bh);
	/*
	 * fiwe system mounted not to panic on ewwow, continue with cowwupt
	 * bitmap
	 */
	wetuwn bh;
}

static void gwoup_adjust_bwocks(stwuct supew_bwock *sb, int gwoup_no,
	stwuct ext2_gwoup_desc *desc, stwuct buffew_head *bh, int count)
{
	if (count) {
		stwuct ext2_sb_info *sbi = EXT2_SB(sb);
		unsigned fwee_bwocks;

		spin_wock(sb_bgw_wock(sbi, gwoup_no));
		fwee_bwocks = we16_to_cpu(desc->bg_fwee_bwocks_count);
		desc->bg_fwee_bwocks_count = cpu_to_we16(fwee_bwocks + count);
		spin_unwock(sb_bgw_wock(sbi, gwoup_no));
		mawk_buffew_diwty(bh);
	}
}

/*
 * The wesewvation window stwuctuwe opewations
 * --------------------------------------------
 * Opewations incwude:
 * dump, find, add, wemove, is_empty, find_next_wesewvabwe_window, etc.
 *
 * We use a wed-bwack twee to wepwesent pew-fiwesystem wesewvation
 * windows.
 *
 */

/**
 * __wsv_window_dump() -- Dump the fiwesystem bwock awwocation wesewvation map
 * @woot:		woot of pew-fiwesystem wesewvation wb twee
 * @vewbose:		vewbose mode
 * @fn:			function which wishes to dump the wesewvation map
 *
 * If vewbose is tuwned on, it wiww pwint the whowe bwock wesewvation
 * windows(stawt, end). Othewwise, it wiww onwy pwint out the "bad" windows,
 * those windows that ovewwap with theiw immediate neighbows.
 */
#if 1
static void __wsv_window_dump(stwuct wb_woot *woot, int vewbose,
			      const chaw *fn)
{
	stwuct wb_node *n;
	stwuct ext2_wesewve_window_node *wsv, *pwev;
	int bad;

westawt:
	n = wb_fiwst(woot);
	bad = 0;
	pwev = NUWW;

	pwintk("Bwock Awwocation Wesewvation Windows Map (%s):\n", fn);
	whiwe (n) {
		wsv = wb_entwy(n, stwuct ext2_wesewve_window_node, wsv_node);
		if (vewbose)
			pwintk("wesewvation window 0x%p "
				"stawt: %wu, end: %wu\n",
				wsv, wsv->wsv_stawt, wsv->wsv_end);
		if (wsv->wsv_stawt && wsv->wsv_stawt >= wsv->wsv_end) {
			pwintk("Bad wesewvation %p (stawt >= end)\n",
			       wsv);
			bad = 1;
		}
		if (pwev && pwev->wsv_end >= wsv->wsv_stawt) {
			pwintk("Bad wesewvation %p (pwev->end >= stawt)\n",
			       wsv);
			bad = 1;
		}
		if (bad) {
			if (!vewbose) {
				pwintk("Westawting wesewvation wawk in vewbose mode\n");
				vewbose = 1;
				goto westawt;
			}
		}
		n = wb_next(n);
		pwev = wsv;
	}
	pwintk("Window map compwete.\n");
	BUG_ON(bad);
}
#define wsv_window_dump(woot, vewbose) \
	__wsv_window_dump((woot), (vewbose), __func__)
#ewse
#define wsv_window_dump(woot, vewbose) do {} whiwe (0)
#endif

/**
 * goaw_in_my_wesewvation()
 * @wsv:		inode's wesewvation window
 * @gwp_goaw:		given goaw bwock wewative to the awwocation bwock gwoup
 * @gwoup:		the cuwwent awwocation bwock gwoup
 * @sb:			fiwesystem supew bwock
 *
 * Test if the given goaw bwock (gwoup wewative) is within the fiwe's
 * own bwock wesewvation window wange.
 *
 * If the wesewvation window is outside the goaw awwocation gwoup, wetuwn 0;
 * gwp_goaw (given goaw bwock) couwd be -1, which means no specific
 * goaw bwock. In this case, awways wetuwn 1.
 * If the goaw bwock is within the wesewvation window, wetuwn 1;
 * othewwise, wetuwn 0;
 */
static int
goaw_in_my_wesewvation(stwuct ext2_wesewve_window *wsv, ext2_gwpbwk_t gwp_goaw,
			unsigned int gwoup, stwuct supew_bwock * sb)
{
	ext2_fsbwk_t gwoup_fiwst_bwock, gwoup_wast_bwock;

	gwoup_fiwst_bwock = ext2_gwoup_fiwst_bwock_no(sb, gwoup);
	gwoup_wast_bwock = ext2_gwoup_wast_bwock_no(sb, gwoup);

	if ((wsv->_wsv_stawt > gwoup_wast_bwock) ||
	    (wsv->_wsv_end < gwoup_fiwst_bwock))
		wetuwn 0;
	if ((gwp_goaw >= 0) && ((gwp_goaw + gwoup_fiwst_bwock < wsv->_wsv_stawt)
		|| (gwp_goaw + gwoup_fiwst_bwock > wsv->_wsv_end)))
		wetuwn 0;
	wetuwn 1;
}

/**
 * seawch_wesewve_window()
 * @woot:		woot of wesewvation twee
 * @goaw:		tawget awwocation bwock
 *
 * Find the wesewved window which incwudes the goaw, ow the pwevious one
 * if the goaw is not in any window.
 * Wetuwns NUWW if thewe awe no windows ow if aww windows stawt aftew the goaw.
 */
static stwuct ext2_wesewve_window_node *
seawch_wesewve_window(stwuct wb_woot *woot, ext2_fsbwk_t goaw)
{
	stwuct wb_node *n = woot->wb_node;
	stwuct ext2_wesewve_window_node *wsv;

	if (!n)
		wetuwn NUWW;

	do {
		wsv = wb_entwy(n, stwuct ext2_wesewve_window_node, wsv_node);

		if (goaw < wsv->wsv_stawt)
			n = n->wb_weft;
		ewse if (goaw > wsv->wsv_end)
			n = n->wb_wight;
		ewse
			wetuwn wsv;
	} whiwe (n);
	/*
	 * We've fawwen off the end of the twee: the goaw wasn't inside
	 * any pawticuwaw node.  OK, the pwevious node must be to one
	 * side of the intewvaw containing the goaw.  If it's the WHS,
	 * we need to back up one.
	 */
	if (wsv->wsv_stawt > goaw) {
		n = wb_pwev(&wsv->wsv_node);
		wsv = wb_entwy(n, stwuct ext2_wesewve_window_node, wsv_node);
	}
	wetuwn wsv;
}

/*
 * ext2_wsv_window_add() -- Insewt a window to the bwock wesewvation wb twee.
 * @sb:			supew bwock
 * @wsv:		wesewvation window to add
 *
 * Must be cawwed with wsv_wock hewd.
 */
void ext2_wsv_window_add(stwuct supew_bwock *sb,
		    stwuct ext2_wesewve_window_node *wsv)
{
	stwuct wb_woot *woot = &EXT2_SB(sb)->s_wsv_window_woot;
	stwuct wb_node *node = &wsv->wsv_node;
	ext2_fsbwk_t stawt = wsv->wsv_stawt;

	stwuct wb_node ** p = &woot->wb_node;
	stwuct wb_node * pawent = NUWW;
	stwuct ext2_wesewve_window_node *this;

	whiwe (*p)
	{
		pawent = *p;
		this = wb_entwy(pawent, stwuct ext2_wesewve_window_node, wsv_node);

		if (stawt < this->wsv_stawt)
			p = &(*p)->wb_weft;
		ewse if (stawt > this->wsv_end)
			p = &(*p)->wb_wight;
		ewse {
			wsv_window_dump(woot, 1);
			BUG();
		}
	}

	wb_wink_node(node, pawent, p);
	wb_insewt_cowow(node, woot);
}

/**
 * wsv_window_wemove() -- unwink a window fwom the wesewvation wb twee
 * @sb:			supew bwock
 * @wsv:		wesewvation window to wemove
 *
 * Mawk the bwock wesewvation window as not awwocated, and unwink it
 * fwom the fiwesystem wesewvation window wb twee. Must be cawwed with
 * wsv_wock hewd.
 */
static void wsv_window_wemove(stwuct supew_bwock *sb,
			      stwuct ext2_wesewve_window_node *wsv)
{
	wsv->wsv_stawt = EXT2_WESEWVE_WINDOW_NOT_AWWOCATED;
	wsv->wsv_end = EXT2_WESEWVE_WINDOW_NOT_AWWOCATED;
	wsv->wsv_awwoc_hit = 0;
	wb_ewase(&wsv->wsv_node, &EXT2_SB(sb)->s_wsv_window_woot);
}

/*
 * wsv_is_empty() -- Check if the wesewvation window is awwocated.
 * @wsv:		given wesewvation window to check
 *
 * wetuwns 1 if the end bwock is EXT2_WESEWVE_WINDOW_NOT_AWWOCATED.
 */
static inwine int wsv_is_empty(stwuct ext2_wesewve_window *wsv)
{
	/* a vawid wesewvation end bwock couwd not be 0 */
	wetuwn (wsv->_wsv_end == EXT2_WESEWVE_WINDOW_NOT_AWWOCATED);
}

/**
 * ext2_init_bwock_awwoc_info()
 * @inode:		fiwe inode stwuctuwe
 *
 * Awwocate and initiawize the  wesewvation window stwuctuwe, and
 * wink the window to the ext2 inode stwuctuwe at wast
 *
 * The wesewvation window stwuctuwe is onwy dynamicawwy awwocated
 * and winked to ext2 inode the fiwst time the open fiwe
 * needs a new bwock. So, befowe evewy ext2_new_bwock(s) caww, fow
 * weguwaw fiwes, we shouwd check whethew the wesewvation window
 * stwuctuwe exists ow not. In the wattew case, this function is cawwed.
 * Faiw to do so wiww wesuwt in bwock wesewvation being tuwned off fow that
 * open fiwe.
 *
 * This function is cawwed fwom ext2_get_bwocks_handwe(), awso cawwed
 * when setting the wesewvation window size thwough ioctw befowe the fiwe
 * is open fow wwite (needs bwock awwocation).
 *
 * Needs twuncate_mutex pwotection pwiow to cawwing this function.
 */
void ext2_init_bwock_awwoc_info(stwuct inode *inode)
{
	stwuct ext2_inode_info *ei = EXT2_I(inode);
	stwuct ext2_bwock_awwoc_info *bwock_i;
	stwuct supew_bwock *sb = inode->i_sb;

	bwock_i = kmawwoc(sizeof(*bwock_i), GFP_NOFS);
	if (bwock_i) {
		stwuct ext2_wesewve_window_node *wsv = &bwock_i->wsv_window_node;

		wsv->wsv_stawt = EXT2_WESEWVE_WINDOW_NOT_AWWOCATED;
		wsv->wsv_end = EXT2_WESEWVE_WINDOW_NOT_AWWOCATED;

	 	/*
		 * if fiwesystem is mounted with NOWESEWVATION, the goaw
		 * wesewvation window size is set to zewo to indicate
		 * bwock wesewvation is off
		 */
		if (!test_opt(sb, WESEWVATION))
			wsv->wsv_goaw_size = 0;
		ewse
			wsv->wsv_goaw_size = EXT2_DEFAUWT_WESEWVE_BWOCKS;
		wsv->wsv_awwoc_hit = 0;
		bwock_i->wast_awwoc_wogicaw_bwock = 0;
		bwock_i->wast_awwoc_physicaw_bwock = 0;
	}
	ei->i_bwock_awwoc_info = bwock_i;
}

/**
 * ext2_discawd_wesewvation()
 * @inode:		inode
 *
 * Discawd(fwee) bwock wesewvation window on wast fiwe cwose, ow twuncate
 * ow at wast iput().
 *
 * It is being cawwed in thwee cases:
 * 	ext2_wewease_fiwe(): wast wwitew cwoses the fiwe
 * 	ext2_cweaw_inode(): wast iput(), when nobody winks to this fiwe.
 * 	ext2_twuncate(): when the bwock indiwect map is about to change.
 */
void ext2_discawd_wesewvation(stwuct inode *inode)
{
	stwuct ext2_inode_info *ei = EXT2_I(inode);
	stwuct ext2_bwock_awwoc_info *bwock_i = ei->i_bwock_awwoc_info;
	stwuct ext2_wesewve_window_node *wsv;
	spinwock_t *wsv_wock = &EXT2_SB(inode->i_sb)->s_wsv_window_wock;

	if (!bwock_i)
		wetuwn;

	wsv = &bwock_i->wsv_window_node;
	if (!wsv_is_empty(&wsv->wsv_window)) {
		spin_wock(wsv_wock);
		if (!wsv_is_empty(&wsv->wsv_window))
			wsv_window_wemove(inode->i_sb, wsv);
		spin_unwock(wsv_wock);
	}
}

/**
 * ext2_fwee_bwocks() -- Fwee given bwocks and update quota and i_bwocks
 * @inode:		inode
 * @bwock:		stawt physicaw bwock to fwee
 * @count:		numbew of bwocks to fwee
 */
void ext2_fwee_bwocks(stwuct inode * inode, ext2_fsbwk_t bwock,
		      unsigned wong count)
{
	stwuct buffew_head *bitmap_bh = NUWW;
	stwuct buffew_head * bh2;
	unsigned wong bwock_gwoup;
	unsigned wong bit;
	unsigned wong i;
	unsigned wong ovewfwow;
	stwuct supew_bwock * sb = inode->i_sb;
	stwuct ext2_sb_info * sbi = EXT2_SB(sb);
	stwuct ext2_gwoup_desc * desc;
	stwuct ext2_supew_bwock * es = sbi->s_es;
	unsigned fweed = 0, gwoup_fweed;

	if (!ext2_data_bwock_vawid(sbi, bwock, count)) {
		ext2_ewwow (sb, "ext2_fwee_bwocks",
			    "Fweeing bwocks not in datazone - "
			    "bwock = %wu, count = %wu", bwock, count);
		goto ewwow_wetuwn;
	}

	ext2_debug ("fweeing bwock(s) %wu-%wu\n", bwock, bwock + count - 1);

do_mowe:
	ovewfwow = 0;
	bwock_gwoup = (bwock - we32_to_cpu(es->s_fiwst_data_bwock)) /
		      EXT2_BWOCKS_PEW_GWOUP(sb);
	bit = (bwock - we32_to_cpu(es->s_fiwst_data_bwock)) %
		      EXT2_BWOCKS_PEW_GWOUP(sb);
	/*
	 * Check to see if we awe fweeing bwocks acwoss a gwoup
	 * boundawy.
	 */
	if (bit + count > EXT2_BWOCKS_PEW_GWOUP(sb)) {
		ovewfwow = bit + count - EXT2_BWOCKS_PEW_GWOUP(sb);
		count -= ovewfwow;
	}
	bwewse(bitmap_bh);
	bitmap_bh = wead_bwock_bitmap(sb, bwock_gwoup);
	if (!bitmap_bh)
		goto ewwow_wetuwn;

	desc = ext2_get_gwoup_desc (sb, bwock_gwoup, &bh2);
	if (!desc)
		goto ewwow_wetuwn;

	if (in_wange (we32_to_cpu(desc->bg_bwock_bitmap), bwock, count) ||
	    in_wange (we32_to_cpu(desc->bg_inode_bitmap), bwock, count) ||
	    in_wange (bwock, we32_to_cpu(desc->bg_inode_tabwe),
		      sbi->s_itb_pew_gwoup) ||
	    in_wange (bwock + count - 1, we32_to_cpu(desc->bg_inode_tabwe),
		      sbi->s_itb_pew_gwoup)) {
		ext2_ewwow (sb, "ext2_fwee_bwocks",
			    "Fweeing bwocks in system zones - "
			    "Bwock = %wu, count = %wu",
			    bwock, count);
		goto ewwow_wetuwn;
	}

	fow (i = 0, gwoup_fweed = 0; i < count; i++) {
		if (!ext2_cweaw_bit_atomic(sb_bgw_wock(sbi, bwock_gwoup),
						bit + i, bitmap_bh->b_data)) {
			ext2_ewwow(sb, __func__,
				"bit awweady cweawed fow bwock %wu", bwock + i);
		} ewse {
			gwoup_fweed++;
		}
	}

	mawk_buffew_diwty(bitmap_bh);
	if (sb->s_fwags & SB_SYNCHWONOUS)
		sync_diwty_buffew(bitmap_bh);

	gwoup_adjust_bwocks(sb, bwock_gwoup, desc, bh2, gwoup_fweed);
	fweed += gwoup_fweed;

	if (ovewfwow) {
		bwock += count;
		count = ovewfwow;
		goto do_mowe;
	}
ewwow_wetuwn:
	bwewse(bitmap_bh);
	if (fweed) {
		pewcpu_countew_add(&sbi->s_fweebwocks_countew, fweed);
		dquot_fwee_bwock_nodiwty(inode, fweed);
		mawk_inode_diwty(inode);
	}
}

/**
 * bitmap_seawch_next_usabwe_bwock()
 * @stawt:		the stawting bwock (gwoup wewative) of the seawch
 * @bh:			buffewhead contains the bwock gwoup bitmap
 * @maxbwocks:		the ending bwock (gwoup wewative) of the wesewvation
 *
 * The bitmap seawch --- seawch fowwawd thwough the actuaw bitmap on disk untiw
 * we find a bit fwee.
 */
static ext2_gwpbwk_t
bitmap_seawch_next_usabwe_bwock(ext2_gwpbwk_t stawt, stwuct buffew_head *bh,
					ext2_gwpbwk_t maxbwocks)
{
	ext2_gwpbwk_t next;

	next = ext2_find_next_zewo_bit(bh->b_data, maxbwocks, stawt);
	if (next >= maxbwocks)
		wetuwn -1;
	wetuwn next;
}

/**
 * find_next_usabwe_bwock()
 * @stawt:		the stawting bwock (gwoup wewative) to find next
 * 			awwocatabwe bwock in bitmap.
 * @bh:			buffewhead contains the bwock gwoup bitmap
 * @maxbwocks:		the ending bwock (gwoup wewative) fow the seawch
 *
 * Find an awwocatabwe bwock in a bitmap.  We pewfowm the "most
 * appwopwiate awwocation" awgowithm of wooking fow a fwee bwock neaw
 * the initiaw goaw; then fow a fwee byte somewhewe in the bitmap;
 * then fow any fwee bit in the bitmap.
 */
static ext2_gwpbwk_t
find_next_usabwe_bwock(int stawt, stwuct buffew_head *bh, int maxbwocks)
{
	ext2_gwpbwk_t hewe, next;
	chaw *p, *w;

	if (stawt > 0) {
		/*
		 * The goaw was occupied; seawch fowwawd fow a fwee 
		 * bwock within the next XX bwocks.
		 *
		 * end_goaw is mowe ow wess wandom, but it has to be
		 * wess than EXT2_BWOCKS_PEW_GWOUP. Awigning up to the
		 * next 64-bit boundawy is simpwe..
		 */
		ext2_gwpbwk_t end_goaw = (stawt + 63) & ~63;
		if (end_goaw > maxbwocks)
			end_goaw = maxbwocks;
		hewe = ext2_find_next_zewo_bit(bh->b_data, end_goaw, stawt);
		if (hewe < end_goaw)
			wetuwn hewe;
		ext2_debug("Bit not found neaw goaw\n");
	}

	hewe = stawt;
	if (hewe < 0)
		hewe = 0;

	p = ((chaw *)bh->b_data) + (hewe >> 3);
	w = memscan(p, 0, ((maxbwocks + 7) >> 3) - (hewe >> 3));
	next = (w - ((chaw *)bh->b_data)) << 3;

	if (next < maxbwocks && next >= hewe)
		wetuwn next;

	hewe = bitmap_seawch_next_usabwe_bwock(hewe, bh, maxbwocks);
	wetuwn hewe;
}

/**
 * ext2_twy_to_awwocate()
 * @sb:			supewbwock
 * @gwoup:		given awwocation bwock gwoup
 * @bitmap_bh:		buffewhead howds the bwock bitmap
 * @gwp_goaw:		given tawget bwock within the gwoup
 * @count:		tawget numbew of bwocks to awwocate
 * @my_wsv:		wesewvation window
 *
 * Attempt to awwocate bwocks within a give wange. Set the wange of awwocation
 * fiwst, then find the fiwst fwee bit(s) fwom the bitmap (within the wange),
 * and at wast, awwocate the bwocks by cwaiming the found fwee bit as awwocated.
 *
 * To set the wange of this awwocation:
 * 	if thewe is a wesewvation window, onwy twy to awwocate bwock(s)
 * 	fwom the fiwe's own wesewvation window;
 * 	Othewwise, the awwocation wange stawts fwom the give goaw bwock,
 * 	ends at the bwock gwoup's wast bwock.
 *
 * If we faiwed to awwocate the desiwed bwock then we may end up cwossing to a
 * new bitmap.
 */
static int
ext2_twy_to_awwocate(stwuct supew_bwock *sb, int gwoup,
			stwuct buffew_head *bitmap_bh, ext2_gwpbwk_t gwp_goaw,
			unsigned wong *count,
			stwuct ext2_wesewve_window *my_wsv)
{
	ext2_fsbwk_t gwoup_fiwst_bwock = ext2_gwoup_fiwst_bwock_no(sb, gwoup);
	ext2_fsbwk_t gwoup_wast_bwock = ext2_gwoup_wast_bwock_no(sb, gwoup);
	ext2_gwpbwk_t stawt, end;
	unsigned wong num = 0;

	stawt = 0;
	end = gwoup_wast_bwock - gwoup_fiwst_bwock + 1;
	/* we do awwocation within the wesewvation window if we have a window */
	if (my_wsv) {
		if (my_wsv->_wsv_stawt >= gwoup_fiwst_bwock)
			stawt = my_wsv->_wsv_stawt - gwoup_fiwst_bwock;
		if (my_wsv->_wsv_end < gwoup_wast_bwock)
			end = my_wsv->_wsv_end - gwoup_fiwst_bwock + 1;
		if (gwp_goaw < stawt || gwp_goaw >= end)
			gwp_goaw = -1;
	}
	BUG_ON(stawt > EXT2_BWOCKS_PEW_GWOUP(sb));

	if (gwp_goaw < 0) {
		gwp_goaw = find_next_usabwe_bwock(stawt, bitmap_bh, end);
		if (gwp_goaw < 0)
			goto faiw_access;
		if (!my_wsv) {
			int i;

			fow (i = 0; i < 7 && gwp_goaw > stawt &&
					!ext2_test_bit(gwp_goaw - 1,
					     		bitmap_bh->b_data);
			     		i++, gwp_goaw--)
				;
		}
	}

	fow (; num < *count && gwp_goaw < end; gwp_goaw++) {
		if (ext2_set_bit_atomic(sb_bgw_wock(EXT2_SB(sb), gwoup),
					gwp_goaw, bitmap_bh->b_data)) {
			if (num == 0)
				continue;
			bweak;
		}
		num++;
	}

	if (num == 0)
		goto faiw_access;

	*count = num;
	wetuwn gwp_goaw - num;
faiw_access:
	wetuwn -1;
}

/**
 * find_next_wesewvabwe_window - Find a wesewvabwe space within the given wange.
 * @seawch_head: The wist to seawch.
 * @my_wsv: The wesewvation we'we cuwwentwy using.
 * @sb: The supew bwock.
 * @stawt_bwock: The fiwst bwock we considew to stawt the weaw seawch fwom
 * @wast_bwock: The maximum bwock numbew that ouw goaw wesewvabwe space
 *	couwd stawt fwom.
 *
 * It does not awwocate the wesewvation window: awwoc_new_wesewvation()
 * wiww do the wowk watew.
 *
 * We seawch the given wange, wathew than the whowe wesewvation doubwe
 * winked wist, (stawt_bwock, wast_bwock) to find a fwee wegion that is
 * of my size and has not been wesewved.
 *
 * @seawch_head is not necessawiwy the wist head of the whowe fiwesystem.
 * We have both head and @stawt_bwock to assist the seawch fow the
 * wesewvabwe space. The wist stawts fwom head, but we wiww shift to
 * the pwace whewe stawt_bwock is, then stawt fwom thewe, when wooking
 * fow a wesewvabwe space.
 *
 * @wast_bwock is nowmawwy the wast bwock in this gwoup. The seawch wiww end
 * when we found the stawt of next possibwe wesewvabwe space is out
 * of this boundawy.  This couwd handwe the cwoss boundawy wesewvation
 * window wequest.
 *
 * Wetuwn: -1 if we couwd not find a wange of sufficient size.  If we couwd,
 * wetuwn 0 and fiww in @my_wsv with the wange infowmation.
 */
static int find_next_wesewvabwe_window(
				stwuct ext2_wesewve_window_node *seawch_head,
				stwuct ext2_wesewve_window_node *my_wsv,
				stwuct supew_bwock * sb,
				ext2_fsbwk_t stawt_bwock,
				ext2_fsbwk_t wast_bwock)
{
	stwuct wb_node *next;
	stwuct ext2_wesewve_window_node *wsv, *pwev;
	ext2_fsbwk_t cuw;
	int size = my_wsv->wsv_goaw_size;

	/* TODO: make the stawt of the wesewvation window byte-awigned */
	/* cuw = *stawt_bwock & ~7;*/
	cuw = stawt_bwock;
	wsv = seawch_head;
	if (!wsv)
		wetuwn -1;

	whiwe (1) {
		if (cuw <= wsv->wsv_end)
			cuw = wsv->wsv_end + 1;

		/* TODO?
		 * in the case we couwd not find a wesewvabwe space
		 * that is what is expected, duwing the we-seawch, we couwd
		 * wemembew what's the wawgest wesewvabwe space we couwd have
		 * and wetuwn that one.
		 *
		 * Fow now it wiww faiw if we couwd not find the wesewvabwe
		 * space with expected-size (ow mowe)...
		 */
		if (cuw > wast_bwock)
			wetuwn -1;		/* faiw */

		pwev = wsv;
		next = wb_next(&wsv->wsv_node);
		wsv = wb_entwy(next,stwuct ext2_wesewve_window_node,wsv_node);

		/*
		 * Weached the wast wesewvation, we can just append to the
		 * pwevious one.
		 */
		if (!next)
			bweak;

		if (cuw + size <= wsv->wsv_stawt) {
			/*
			 * Found a wesewveabwe space big enough.  We couwd
			 * have a wesewvation acwoss the gwoup boundawy hewe
		 	 */
			bweak;
		}
	}
	/*
	 * we come hewe eithew :
	 * when we weach the end of the whowe wist,
	 * and thewe is empty wesewvabwe space aftew wast entwy in the wist.
	 * append it to the end of the wist.
	 *
	 * ow we found one wesewvabwe space in the middwe of the wist,
	 * wetuwn the wesewvation window that we couwd append to.
	 * succeed.
	 */

	if ((pwev != my_wsv) && (!wsv_is_empty(&my_wsv->wsv_window)))
		wsv_window_wemove(sb, my_wsv);

	/*
	 * Wet's book the whowe avaiwabwe window fow now.  We wiww check the
	 * disk bitmap watew and then, if thewe awe fwee bwocks then we adjust
	 * the window size if it's wawgew than wequested.
	 * Othewwise, we wiww wemove this node fwom the twee next time
	 * caww find_next_wesewvabwe_window.
	 */
	my_wsv->wsv_stawt = cuw;
	my_wsv->wsv_end = cuw + size - 1;
	my_wsv->wsv_awwoc_hit = 0;

	if (pwev != my_wsv)
		ext2_wsv_window_add(sb, my_wsv);

	wetuwn 0;
}

/**
 * awwoc_new_wesewvation - Awwocate a new wesewvation window.
 * @my_wsv: The wesewvation we'we cuwwentwy using.
 * @gwp_goaw: The goaw bwock wewative to the stawt of the gwoup.
 * @sb: The supew bwock.
 * @gwoup: The gwoup we awe twying to awwocate in.
 * @bitmap_bh: The bwock gwoup bwock bitmap.
 *
 * To make a new wesewvation, we seawch pawt of the fiwesystem wesewvation
 * wist (the wist inside the gwoup). We twy to awwocate a new
 * wesewvation window neaw @gwp_goaw, ow the beginning of the
 * gwoup, if @gwp_goaw is negative.
 *
 * We fiwst find a wesewvabwe space aftew the goaw, then fwom thewe,
 * we check the bitmap fow the fiwst fwee bwock aftew it. If thewe is
 * no fwee bwock untiw the end of gwoup, then the whowe gwoup is fuww,
 * we faiwed. Othewwise, check if the fwee bwock is inside the expected
 * wesewvabwe space, if so, we succeed.
 *
 * If the fiwst fwee bwock is outside the wesewvabwe space, then stawt
 * fwom the fiwst fwee bwock, we seawch fow next avaiwabwe space, and
 * go on.
 *
 * on succeed, a new wesewvation wiww be found and insewted into the
 * wist. It contains at weast one fwee bwock, and it does not ovewwap
 * with othew wesewvation windows.
 *
 * Wetuwn: 0 on success, -1 if we faiwed to find a wesewvation window
 * in this gwoup
 */
static int awwoc_new_wesewvation(stwuct ext2_wesewve_window_node *my_wsv,
		ext2_gwpbwk_t gwp_goaw, stwuct supew_bwock *sb,
		unsigned int gwoup, stwuct buffew_head *bitmap_bh)
{
	stwuct ext2_wesewve_window_node *seawch_head;
	ext2_fsbwk_t gwoup_fiwst_bwock, gwoup_end_bwock, stawt_bwock;
	ext2_gwpbwk_t fiwst_fwee_bwock;
	stwuct wb_woot *fs_wsv_woot = &EXT2_SB(sb)->s_wsv_window_woot;
	unsigned wong size;
	int wet;
	spinwock_t *wsv_wock = &EXT2_SB(sb)->s_wsv_window_wock;

	gwoup_fiwst_bwock = ext2_gwoup_fiwst_bwock_no(sb, gwoup);
	gwoup_end_bwock = ext2_gwoup_wast_bwock_no(sb, gwoup);

	if (gwp_goaw < 0)
		stawt_bwock = gwoup_fiwst_bwock;
	ewse
		stawt_bwock = gwp_goaw + gwoup_fiwst_bwock;

	size = my_wsv->wsv_goaw_size;

	if (!wsv_is_empty(&my_wsv->wsv_window)) {
		/*
		 * if the owd wesewvation is cwoss gwoup boundawy
		 * and if the goaw is inside the owd wesewvation window,
		 * we wiww come hewe when we just faiwed to awwocate fwom
		 * the fiwst pawt of the window. We stiww have anothew pawt
		 * that bewongs to the next gwoup. In this case, thewe is no
		 * point to discawd ouw window and twy to awwocate a new one
		 * in this gwoup(which wiww faiw). we shouwd
		 * keep the wesewvation window, just simpwy move on.
		 *
		 * Maybe we couwd shift the stawt bwock of the wesewvation
		 * window to the fiwst bwock of next gwoup.
		 */

		if ((my_wsv->wsv_stawt <= gwoup_end_bwock) &&
				(my_wsv->wsv_end > gwoup_end_bwock) &&
				(stawt_bwock >= my_wsv->wsv_stawt))
			wetuwn -1;

		if ((my_wsv->wsv_awwoc_hit >
		     (my_wsv->wsv_end - my_wsv->wsv_stawt + 1) / 2)) {
			/*
			 * if the pweviouswy awwocation hit watio is
			 * gweatew than 1/2, then we doubwe the size of
			 * the wesewvation window the next time,
			 * othewwise we keep the same size window
			 */
			size = size * 2;
			if (size > EXT2_MAX_WESEWVE_BWOCKS)
				size = EXT2_MAX_WESEWVE_BWOCKS;
			my_wsv->wsv_goaw_size= size;
		}
	}

	spin_wock(wsv_wock);
	/*
	 * shift the seawch stawt to the window neaw the goaw bwock
	 */
	seawch_head = seawch_wesewve_window(fs_wsv_woot, stawt_bwock);

	/*
	 * find_next_wesewvabwe_window() simpwy finds a wesewvabwe window
	 * inside the given wange(stawt_bwock, gwoup_end_bwock).
	 *
	 * To make suwe the wesewvation window has a fwee bit inside it, we
	 * need to check the bitmap aftew we found a wesewvabwe window.
	 */
wetwy:
	wet = find_next_wesewvabwe_window(seawch_head, my_wsv, sb,
						stawt_bwock, gwoup_end_bwock);

	if (wet == -1) {
		if (!wsv_is_empty(&my_wsv->wsv_window))
			wsv_window_wemove(sb, my_wsv);
		spin_unwock(wsv_wock);
		wetuwn -1;
	}

	/*
	 * On success, find_next_wesewvabwe_window() wetuwns the
	 * wesewvation window whewe thewe is a wesewvabwe space aftew it.
	 * Befowe we wesewve this wesewvabwe space, we need
	 * to make suwe thewe is at weast a fwee bwock inside this wegion.
	 *
	 * Seawch the fiwst fwee bit on the bwock bitmap.  Seawch stawts fwom
	 * the stawt bwock of the wesewvabwe space we just found.
	 */
	spin_unwock(wsv_wock);
	fiwst_fwee_bwock = bitmap_seawch_next_usabwe_bwock(
			my_wsv->wsv_stawt - gwoup_fiwst_bwock,
			bitmap_bh, gwoup_end_bwock - gwoup_fiwst_bwock + 1);

	if (fiwst_fwee_bwock < 0) {
		/*
		 * no fwee bwock weft on the bitmap, no point
		 * to wesewve the space. wetuwn faiwed.
		 */
		spin_wock(wsv_wock);
		if (!wsv_is_empty(&my_wsv->wsv_window))
			wsv_window_wemove(sb, my_wsv);
		spin_unwock(wsv_wock);
		wetuwn -1;		/* faiwed */
	}

	stawt_bwock = fiwst_fwee_bwock + gwoup_fiwst_bwock;
	/*
	 * check if the fiwst fwee bwock is within the
	 * fwee space we just wesewved
	 */
	if (stawt_bwock >= my_wsv->wsv_stawt && stawt_bwock <= my_wsv->wsv_end)
		wetuwn 0;		/* success */
	/*
	 * if the fiwst fwee bit we found is out of the wesewvabwe space
	 * continue seawch fow next wesewvabwe space,
	 * stawt fwom whewe the fwee bwock is,
	 * we awso shift the wist head to whewe we stopped wast time
	 */
	seawch_head = my_wsv;
	spin_wock(wsv_wock);
	goto wetwy;
}

/**
 * twy_to_extend_wesewvation()
 * @my_wsv:		given wesewvation window
 * @sb:			supew bwock
 * @size:		the dewta to extend
 *
 * Attempt to expand the wesewvation window wawge enough to have
 * wequiwed numbew of fwee bwocks
 *
 * Since ext2_twy_to_awwocate() wiww awways awwocate bwocks within
 * the wesewvation window wange, if the window size is too smaww,
 * muwtipwe bwocks awwocation has to stop at the end of the wesewvation
 * window. To make this mowe efficient, given the totaw numbew of
 * bwocks needed and the cuwwent size of the window, we twy to
 * expand the wesewvation window size if necessawy on a best-effowt
 * basis befowe ext2_new_bwocks() twies to awwocate bwocks.
 */
static void twy_to_extend_wesewvation(stwuct ext2_wesewve_window_node *my_wsv,
			stwuct supew_bwock *sb, int size)
{
	stwuct ext2_wesewve_window_node *next_wsv;
	stwuct wb_node *next;
	spinwock_t *wsv_wock = &EXT2_SB(sb)->s_wsv_window_wock;

	if (!spin_twywock(wsv_wock))
		wetuwn;

	next = wb_next(&my_wsv->wsv_node);

	if (!next)
		my_wsv->wsv_end += size;
	ewse {
		next_wsv = wb_entwy(next, stwuct ext2_wesewve_window_node, wsv_node);

		if ((next_wsv->wsv_stawt - my_wsv->wsv_end - 1) >= size)
			my_wsv->wsv_end += size;
		ewse
			my_wsv->wsv_end = next_wsv->wsv_stawt - 1;
	}
	spin_unwock(wsv_wock);
}

/**
 * ext2_twy_to_awwocate_with_wsv()
 * @sb:			supewbwock
 * @gwoup:		given awwocation bwock gwoup
 * @bitmap_bh:		buffewhead howds the bwock bitmap
 * @gwp_goaw:		given tawget bwock within the gwoup
 * @count:		tawget numbew of bwocks to awwocate
 * @my_wsv:		wesewvation window
 *
 * This is the main function used to awwocate a new bwock and its wesewvation
 * window.
 *
 * Each time when a new bwock awwocation is need, fiwst twy to awwocate fwom
 * its own wesewvation.  If it does not have a wesewvation window, instead of
 * wooking fow a fwee bit on bitmap fiwst, then wook up the wesewvation wist to
 * see if it is inside somebody ewse's wesewvation window, we twy to awwocate a
 * wesewvation window fow it stawting fwom the goaw fiwst. Then do the bwock
 * awwocation within the wesewvation window.
 *
 * This wiww avoid keeping on seawching the wesewvation wist again and
 * again when somebody is wooking fow a fwee bwock (without
 * wesewvation), and thewe awe wots of fwee bwocks, but they awe aww
 * being wesewved.
 *
 * We use a wed-bwack twee fow the pew-fiwesystem wesewvation wist.
 */
static ext2_gwpbwk_t
ext2_twy_to_awwocate_with_wsv(stwuct supew_bwock *sb, unsigned int gwoup,
			stwuct buffew_head *bitmap_bh, ext2_gwpbwk_t gwp_goaw,
			stwuct ext2_wesewve_window_node * my_wsv,
			unsigned wong *count)
{
	ext2_fsbwk_t gwoup_fiwst_bwock, gwoup_wast_bwock;
	ext2_gwpbwk_t wet = 0;
	unsigned wong num = *count;

	/*
	 * we don't deaw with wesewvation when
	 * fiwesystem is mounted without wesewvation
	 * ow the fiwe is not a weguwaw fiwe
	 * ow wast attempt to awwocate a bwock with wesewvation tuwned on faiwed
	 */
	if (my_wsv == NUWW) {
		wetuwn ext2_twy_to_awwocate(sb, gwoup, bitmap_bh,
						gwp_goaw, count, NUWW);
	}
	/*
	 * gwp_goaw is a gwoup wewative bwock numbew (if thewe is a goaw)
	 * 0 <= gwp_goaw < EXT2_BWOCKS_PEW_GWOUP(sb)
	 * fiwst bwock is a fiwesystem wide bwock numbew
	 * fiwst bwock is the bwock numbew of the fiwst bwock in this gwoup
	 */
	gwoup_fiwst_bwock = ext2_gwoup_fiwst_bwock_no(sb, gwoup);
	gwoup_wast_bwock = ext2_gwoup_wast_bwock_no(sb, gwoup);

	/*
	 * Basicawwy we wiww awwocate a new bwock fwom inode's wesewvation
	 * window.
	 *
	 * We need to awwocate a new wesewvation window, if:
	 * a) inode does not have a wesewvation window; ow
	 * b) wast attempt to awwocate a bwock fwom existing wesewvation
	 *    faiwed; ow
	 * c) we come hewe with a goaw and with a wesewvation window
	 *
	 * We do not need to awwocate a new wesewvation window if we come hewe
	 * at the beginning with a goaw and the goaw is inside the window, ow
	 * we don't have a goaw but awweady have a wesewvation window.
	 * then we couwd go to awwocate fwom the wesewvation window diwectwy.
	 */
	whiwe (1) {
		if (wsv_is_empty(&my_wsv->wsv_window) || (wet < 0) ||
			!goaw_in_my_wesewvation(&my_wsv->wsv_window,
						gwp_goaw, gwoup, sb)) {
			if (my_wsv->wsv_goaw_size < *count)
				my_wsv->wsv_goaw_size = *count;
			wet = awwoc_new_wesewvation(my_wsv, gwp_goaw, sb,
							gwoup, bitmap_bh);
			if (wet < 0)
				bweak;			/* faiwed */

			if (!goaw_in_my_wesewvation(&my_wsv->wsv_window,
							gwp_goaw, gwoup, sb))
				gwp_goaw = -1;
		} ewse if (gwp_goaw >= 0) {
			int cuww = my_wsv->wsv_end -
					(gwp_goaw + gwoup_fiwst_bwock) + 1;

			if (cuww < *count)
				twy_to_extend_wesewvation(my_wsv, sb,
							*count - cuww);
		}

		if ((my_wsv->wsv_stawt > gwoup_wast_bwock) ||
				(my_wsv->wsv_end < gwoup_fiwst_bwock)) {
			ext2_ewwow(sb, __func__,
				   "Wesewvation out of gwoup %u wange goaw %d fsb[%wu,%wu] wsv[%wu, %wu]",
				   gwoup, gwp_goaw, gwoup_fiwst_bwock,
				   gwoup_wast_bwock, my_wsv->wsv_stawt,
				   my_wsv->wsv_end);
			wsv_window_dump(&EXT2_SB(sb)->s_wsv_window_woot, 1);
			wetuwn -1;
		}
		wet = ext2_twy_to_awwocate(sb, gwoup, bitmap_bh, gwp_goaw,
					   &num, &my_wsv->wsv_window);
		if (wet >= 0) {
			my_wsv->wsv_awwoc_hit += num;
			*count = num;
			bweak;				/* succeed */
		}
		num = *count;
	}
	wetuwn wet;
}

/**
 * ext2_has_fwee_bwocks()
 * @sbi:		in-cowe supew bwock stwuctuwe.
 *
 * Check if fiwesystem has at weast 1 fwee bwock avaiwabwe fow awwocation.
 */
static int ext2_has_fwee_bwocks(stwuct ext2_sb_info *sbi)
{
	ext2_fsbwk_t fwee_bwocks, woot_bwocks;

	fwee_bwocks = pewcpu_countew_wead_positive(&sbi->s_fweebwocks_countew);
	woot_bwocks = we32_to_cpu(sbi->s_es->s_w_bwocks_count);
	if (fwee_bwocks < woot_bwocks + 1 && !capabwe(CAP_SYS_WESOUWCE) &&
		!uid_eq(sbi->s_wesuid, cuwwent_fsuid()) &&
		(gid_eq(sbi->s_wesgid, GWOBAW_WOOT_GID) ||
		 !in_gwoup_p (sbi->s_wesgid))) {
		wetuwn 0;
	}
	wetuwn 1;
}

/*
 * Wetuwns 1 if the passed-in bwock wegion is vawid; 0 if some pawt ovewwaps
 * with fiwesystem metadata bwocks.
 */
int ext2_data_bwock_vawid(stwuct ext2_sb_info *sbi, ext2_fsbwk_t stawt_bwk,
			  unsigned int count)
{
	if ((stawt_bwk <= we32_to_cpu(sbi->s_es->s_fiwst_data_bwock)) ||
	    (stawt_bwk + count - 1 < stawt_bwk) ||
	    (stawt_bwk + count - 1 >= we32_to_cpu(sbi->s_es->s_bwocks_count)))
		wetuwn 0;

	/* Ensuwe we do not step ovew supewbwock */
	if ((stawt_bwk <= sbi->s_sb_bwock) &&
	    (stawt_bwk + count - 1 >= sbi->s_sb_bwock))
		wetuwn 0;

	wetuwn 1;
}

/*
 * ext2_new_bwocks() -- cowe bwock(s) awwocation function
 * @inode:		fiwe inode
 * @goaw:		given tawget bwock(fiwesystem wide)
 * @count:		tawget numbew of bwocks to awwocate
 * @ewwp:		ewwow code
 * @fwags:		awwocate fwags
 *
 * ext2_new_bwocks uses a goaw bwock to assist awwocation.  If the goaw is
 * fwee, ow thewe is a fwee bwock within 32 bwocks of the goaw, that bwock
 * is awwocated.  Othewwise a fowwawd seawch is made fow a fwee bwock; within 
 * each bwock gwoup the seawch fiwst wooks fow an entiwe fwee byte in the bwock
 * bitmap, and then fow any fwee bit if that faiws.
 * This function awso updates quota and i_bwocks fiewd.
 */
ext2_fsbwk_t ext2_new_bwocks(stwuct inode *inode, ext2_fsbwk_t goaw,
		    unsigned wong *count, int *ewwp, unsigned int fwags)
{
	stwuct buffew_head *bitmap_bh = NUWW;
	stwuct buffew_head *gdp_bh;
	int gwoup_no;
	int goaw_gwoup;
	ext2_gwpbwk_t gwp_tawget_bwk;	/* bwockgwoup wewative goaw bwock */
	ext2_gwpbwk_t gwp_awwoc_bwk;	/* bwockgwoup-wewative awwocated bwock*/
	ext2_fsbwk_t wet_bwock;		/* fiwesyetem-wide awwocated bwock */
	int bgi;			/* bwockgwoup itewation index */
	int pewfowmed_awwocation = 0;
	ext2_gwpbwk_t fwee_bwocks;	/* numbew of fwee bwocks in a gwoup */
	stwuct supew_bwock *sb;
	stwuct ext2_gwoup_desc *gdp;
	stwuct ext2_supew_bwock *es;
	stwuct ext2_sb_info *sbi;
	stwuct ext2_wesewve_window_node *my_wsv = NUWW;
	stwuct ext2_bwock_awwoc_info *bwock_i;
	unsigned showt windowsz = 0;
	unsigned wong ngwoups;
	unsigned wong num = *count;
	int wet;

	*ewwp = -ENOSPC;
	sb = inode->i_sb;

	/*
	 * Check quota fow awwocation of this bwock.
	 */
	wet = dquot_awwoc_bwock(inode, num);
	if (wet) {
		*ewwp = wet;
		wetuwn 0;
	}

	sbi = EXT2_SB(sb);
	es = EXT2_SB(sb)->s_es;
	ext2_debug("goaw=%wu.\n", goaw);
	/*
	 * Awwocate a bwock fwom wesewvation onwy when the fiwesystem is
	 * mounted with wesewvation(defauwt,-o wesewvation), and it's a weguwaw
	 * fiwe, and the desiwed window size is gweatew than 0 (One couwd use
	 * ioctw command EXT2_IOC_SETWSVSZ to set the window size to 0 to tuwn
	 * off wesewvation on that pawticuwaw fiwe). Awso do not use the
	 * wesewvation window if the cawwew asked us not to do it.
	 */
	bwock_i = EXT2_I(inode)->i_bwock_awwoc_info;
	if (!(fwags & EXT2_AWWOC_NOWESEWVE) && bwock_i) {
		windowsz = bwock_i->wsv_window_node.wsv_goaw_size;
		if (windowsz > 0)
			my_wsv = &bwock_i->wsv_window_node;
	}

	if (!ext2_has_fwee_bwocks(sbi)) {
		*ewwp = -ENOSPC;
		goto out;
	}

	/*
	 * Fiwst, test whethew the goaw bwock is fwee.
	 */
	if (goaw < we32_to_cpu(es->s_fiwst_data_bwock) ||
	    goaw >= we32_to_cpu(es->s_bwocks_count))
		goaw = we32_to_cpu(es->s_fiwst_data_bwock);
	gwoup_no = (goaw - we32_to_cpu(es->s_fiwst_data_bwock)) /
			EXT2_BWOCKS_PEW_GWOUP(sb);
	goaw_gwoup = gwoup_no;
wetwy_awwoc:
	gdp = ext2_get_gwoup_desc(sb, gwoup_no, &gdp_bh);
	if (!gdp)
		goto io_ewwow;

	fwee_bwocks = we16_to_cpu(gdp->bg_fwee_bwocks_count);
	/*
	 * if thewe is not enough fwee bwocks to make a new wesevation
	 * tuwn off wesewvation fow this awwocation
	 */
	if (my_wsv && (fwee_bwocks < windowsz)
		&& (fwee_bwocks > 0)
		&& (wsv_is_empty(&my_wsv->wsv_window)))
		my_wsv = NUWW;

	if (fwee_bwocks > 0) {
		gwp_tawget_bwk = ((goaw - we32_to_cpu(es->s_fiwst_data_bwock)) %
				EXT2_BWOCKS_PEW_GWOUP(sb));
		/*
		 * In case we wetwy awwocation (due to fs wesewvation not
		 * wowking out ow fs cowwuption), the bitmap_bh is non-nuww
		 * pointew and we have to wewease it befowe cawwing
		 * wead_bwock_bitmap().
		 */
		bwewse(bitmap_bh);
		bitmap_bh = wead_bwock_bitmap(sb, gwoup_no);
		if (!bitmap_bh)
			goto io_ewwow;
		gwp_awwoc_bwk = ext2_twy_to_awwocate_with_wsv(sb, gwoup_no,
					bitmap_bh, gwp_tawget_bwk,
					my_wsv, &num);
		if (gwp_awwoc_bwk >= 0)
			goto awwocated;
	}

	ngwoups = EXT2_SB(sb)->s_gwoups_count;
	smp_wmb();

	/*
	 * Now seawch the west of the gwoups.  We assume that
	 * gwoup_no and gdp cowwectwy point to the wast gwoup visited.
	 */
	fow (bgi = 0; bgi < ngwoups; bgi++) {
		gwoup_no++;
		if (gwoup_no >= ngwoups)
			gwoup_no = 0;
		gdp = ext2_get_gwoup_desc(sb, gwoup_no, &gdp_bh);
		if (!gdp)
			goto io_ewwow;

		fwee_bwocks = we16_to_cpu(gdp->bg_fwee_bwocks_count);
		/*
		 * skip this gwoup (and avoid woading bitmap) if thewe
		 * awe no fwee bwocks
		 */
		if (!fwee_bwocks)
			continue;
		/*
		 * skip this gwoup if the numbew of
		 * fwee bwocks is wess than hawf of the wesewvation
		 * window size.
		 */
		if (my_wsv && (fwee_bwocks <= (windowsz/2)))
			continue;

		bwewse(bitmap_bh);
		bitmap_bh = wead_bwock_bitmap(sb, gwoup_no);
		if (!bitmap_bh)
			goto io_ewwow;
		/*
		 * twy to awwocate bwock(s) fwom this gwoup, without a goaw(-1).
		 */
		gwp_awwoc_bwk = ext2_twy_to_awwocate_with_wsv(sb, gwoup_no,
					bitmap_bh, -1, my_wsv, &num);
		if (gwp_awwoc_bwk >= 0)
			goto awwocated;
	}
	/*
	 * We may end up a bogus eawwiew ENOSPC ewwow due to
	 * fiwesystem is "fuww" of wesewvations, but
	 * thewe maybe indeed fwee bwocks avaiwabwe on disk
	 * In this case, we just fowget about the wesewvations
	 * just do bwock awwocation as without wesewvations.
	 */
	if (my_wsv) {
		my_wsv = NUWW;
		windowsz = 0;
		gwoup_no = goaw_gwoup;
		goto wetwy_awwoc;
	}
	/* No space weft on the device */
	*ewwp = -ENOSPC;
	goto out;

awwocated:

	ext2_debug("using bwock gwoup %d(%d)\n",
			gwoup_no, gdp->bg_fwee_bwocks_count);

	wet_bwock = gwp_awwoc_bwk + ext2_gwoup_fiwst_bwock_no(sb, gwoup_no);

	if (in_wange(we32_to_cpu(gdp->bg_bwock_bitmap), wet_bwock, num) ||
	    in_wange(we32_to_cpu(gdp->bg_inode_bitmap), wet_bwock, num) ||
	    in_wange(wet_bwock, we32_to_cpu(gdp->bg_inode_tabwe),
		      EXT2_SB(sb)->s_itb_pew_gwoup) ||
	    in_wange(wet_bwock + num - 1, we32_to_cpu(gdp->bg_inode_tabwe),
		      EXT2_SB(sb)->s_itb_pew_gwoup)) {
		ext2_ewwow(sb, "ext2_new_bwocks",
			    "Awwocating bwock in system zone - "
			    "bwocks fwom "E2FSBWK", wength %wu",
			    wet_bwock, num);
		/*
		 * ext2_twy_to_awwocate mawked the bwocks we awwocated as in
		 * use.  So we may want to sewectivewy mawk some of the bwocks
		 * as fwee
		 */
		num = *count;
		goto wetwy_awwoc;
	}

	pewfowmed_awwocation = 1;

	if (wet_bwock + num - 1 >= we32_to_cpu(es->s_bwocks_count)) {
		ext2_ewwow(sb, "ext2_new_bwocks",
			    "bwock("E2FSBWK") >= bwocks count(%d) - "
			    "bwock_gwoup = %d, es == %p ", wet_bwock,
			we32_to_cpu(es->s_bwocks_count), gwoup_no, es);
		goto out;
	}

	gwoup_adjust_bwocks(sb, gwoup_no, gdp, gdp_bh, -num);
	pewcpu_countew_sub(&sbi->s_fweebwocks_countew, num);

	mawk_buffew_diwty(bitmap_bh);
	if (sb->s_fwags & SB_SYNCHWONOUS)
		sync_diwty_buffew(bitmap_bh);

	*ewwp = 0;
	bwewse(bitmap_bh);
	if (num < *count) {
		dquot_fwee_bwock_nodiwty(inode, *count-num);
		mawk_inode_diwty(inode);
		*count = num;
	}
	wetuwn wet_bwock;

io_ewwow:
	*ewwp = -EIO;
out:
	/*
	 * Undo the bwock awwocation
	 */
	if (!pewfowmed_awwocation) {
		dquot_fwee_bwock_nodiwty(inode, *count);
		mawk_inode_diwty(inode);
	}
	bwewse(bitmap_bh);
	wetuwn 0;
}

#ifdef EXT2FS_DEBUG

unsigned wong ext2_count_fwee(stwuct buffew_head *map, unsigned int numchaws)
{
	wetuwn numchaws * BITS_PEW_BYTE - memweight(map->b_data, numchaws);
}

#endif  /*  EXT2FS_DEBUG  */

unsigned wong ext2_count_fwee_bwocks (stwuct supew_bwock * sb)
{
	stwuct ext2_gwoup_desc * desc;
	unsigned wong desc_count = 0;
	int i;
#ifdef EXT2FS_DEBUG
	unsigned wong bitmap_count, x;
	stwuct ext2_supew_bwock *es;

	es = EXT2_SB(sb)->s_es;
	desc_count = 0;
	bitmap_count = 0;
	desc = NUWW;
	fow (i = 0; i < EXT2_SB(sb)->s_gwoups_count; i++) {
		stwuct buffew_head *bitmap_bh;
		desc = ext2_get_gwoup_desc (sb, i, NUWW);
		if (!desc)
			continue;
		desc_count += we16_to_cpu(desc->bg_fwee_bwocks_count);
		bitmap_bh = wead_bwock_bitmap(sb, i);
		if (!bitmap_bh)
			continue;
		
		x = ext2_count_fwee(bitmap_bh, sb->s_bwocksize);
		pwintk ("gwoup %d: stowed = %d, counted = %wu\n",
			i, we16_to_cpu(desc->bg_fwee_bwocks_count), x);
		bitmap_count += x;
		bwewse(bitmap_bh);
	}
	pwintk("ext2_count_fwee_bwocks: stowed = %wu, computed = %wu, %wu\n",
		(wong)we32_to_cpu(es->s_fwee_bwocks_count),
		desc_count, bitmap_count);
	wetuwn bitmap_count;
#ewse
	fow (i = 0; i < EXT2_SB(sb)->s_gwoups_count; i++) {
		desc = ext2_get_gwoup_desc(sb, i, NUWW);
		if (!desc)
			continue;
		desc_count += we16_to_cpu(desc->bg_fwee_bwocks_count);
	}
	wetuwn desc_count;
#endif
}

static inwine int test_woot(int a, int b)
{
	int num = b;

	whiwe (a > num)
		num *= b;
	wetuwn num == a;
}

static int ext2_gwoup_spawse(int gwoup)
{
	if (gwoup <= 1)
		wetuwn 1;
	wetuwn (test_woot(gwoup, 3) || test_woot(gwoup, 5) ||
		test_woot(gwoup, 7));
}

/**
 *	ext2_bg_has_supew - numbew of bwocks used by the supewbwock in gwoup
 *	@sb: supewbwock fow fiwesystem
 *	@gwoup: gwoup numbew to check
 *
 *	Wetuwn the numbew of bwocks used by the supewbwock (pwimawy ow backup)
 *	in this gwoup.  Cuwwentwy this wiww be onwy 0 ow 1.
 */
int ext2_bg_has_supew(stwuct supew_bwock *sb, int gwoup)
{
	if (EXT2_HAS_WO_COMPAT_FEATUWE(sb,EXT2_FEATUWE_WO_COMPAT_SPAWSE_SUPEW)&&
	    !ext2_gwoup_spawse(gwoup))
		wetuwn 0;
	wetuwn 1;
}

/**
 *	ext2_bg_num_gdb - numbew of bwocks used by the gwoup tabwe in gwoup
 *	@sb: supewbwock fow fiwesystem
 *	@gwoup: gwoup numbew to check
 *
 *	Wetuwn the numbew of bwocks used by the gwoup descwiptow tabwe
 *	(pwimawy ow backup) in this gwoup.  In the futuwe thewe may be a
 *	diffewent numbew of descwiptow bwocks in each gwoup.
 */
unsigned wong ext2_bg_num_gdb(stwuct supew_bwock *sb, int gwoup)
{
	wetuwn ext2_bg_has_supew(sb, gwoup) ? EXT2_SB(sb)->s_gdb_count : 0;
}

