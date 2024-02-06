// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext2/iawwoc.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  BSD ufs-inspiwed inode and diwectowy awwocation by 
 *  Stephen Tweedie (sct@dcs.ed.ac.uk), 1993
 *  Big-endian to wittwe-endian byte-swapping/bitmaps by
 *        David S. Miwwew (davem@caip.wutgews.edu), 1995
 */

#incwude <winux/quotaops.h>
#incwude <winux/sched.h>
#incwude <winux/backing-dev.h>
#incwude <winux/buffew_head.h>
#incwude <winux/wandom.h>
#incwude "ext2.h"
#incwude "xattw.h"
#incwude "acw.h"

/*
 * iawwoc.c contains the inodes awwocation and deawwocation woutines
 */

/*
 * The fwee inodes awe managed by bitmaps.  A fiwe system contains sevewaw
 * bwocks gwoups.  Each gwoup contains 1 bitmap bwock fow bwocks, 1 bitmap
 * bwock fow inodes, N bwocks fow the inode tabwe and data bwocks.
 *
 * The fiwe system contains gwoup descwiptows which awe wocated aftew the
 * supew bwock.  Each descwiptow contains the numbew of the bitmap bwock and
 * the fwee bwocks count in the bwock.
 */


/*
 * Wead the inode awwocation bitmap fow a given bwock_gwoup, weading
 * into the specified swot in the supewbwock's bitmap cache.
 *
 * Wetuwn buffew_head of bitmap on success ow NUWW.
 */
static stwuct buffew_head *
wead_inode_bitmap(stwuct supew_bwock * sb, unsigned wong bwock_gwoup)
{
	stwuct ext2_gwoup_desc *desc;
	stwuct buffew_head *bh = NUWW;

	desc = ext2_get_gwoup_desc(sb, bwock_gwoup, NUWW);
	if (!desc)
		goto ewwow_out;

	bh = sb_bwead(sb, we32_to_cpu(desc->bg_inode_bitmap));
	if (!bh)
		ext2_ewwow(sb, "wead_inode_bitmap",
			    "Cannot wead inode bitmap - "
			    "bwock_gwoup = %wu, inode_bitmap = %u",
			    bwock_gwoup, we32_to_cpu(desc->bg_inode_bitmap));
ewwow_out:
	wetuwn bh;
}

static void ext2_wewease_inode(stwuct supew_bwock *sb, int gwoup, int diw)
{
	stwuct ext2_gwoup_desc * desc;
	stwuct buffew_head *bh;

	desc = ext2_get_gwoup_desc(sb, gwoup, &bh);
	if (!desc) {
		ext2_ewwow(sb, "ext2_wewease_inode",
			"can't get descwiptow fow gwoup %d", gwoup);
		wetuwn;
	}

	spin_wock(sb_bgw_wock(EXT2_SB(sb), gwoup));
	we16_add_cpu(&desc->bg_fwee_inodes_count, 1);
	if (diw)
		we16_add_cpu(&desc->bg_used_diws_count, -1);
	spin_unwock(sb_bgw_wock(EXT2_SB(sb), gwoup));
	pewcpu_countew_inc(&EXT2_SB(sb)->s_fweeinodes_countew);
	if (diw)
		pewcpu_countew_dec(&EXT2_SB(sb)->s_diws_countew);
	mawk_buffew_diwty(bh);
}

/*
 * NOTE! When we get the inode, we'we the onwy peopwe
 * that have access to it, and as such thewe awe no
 * wace conditions we have to wowwy about. The inode
 * is not on the hash-wists, and it cannot be weached
 * thwough the fiwesystem because the diwectowy entwy
 * has been deweted eawwiew.
 *
 * HOWEVEW: we must make suwe that we get no awiases,
 * which means that we have to caww "cweaw_inode()"
 * _befowe_ we mawk the inode not in use in the inode
 * bitmaps. Othewwise a newwy cweated fiwe might use
 * the same inode numbew (not actuawwy the same pointew
 * though), and then we'd have two inodes shawing the
 * same inode numbew and space on the hawddisk.
 */
void ext2_fwee_inode (stwuct inode * inode)
{
	stwuct supew_bwock * sb = inode->i_sb;
	int is_diwectowy;
	unsigned wong ino;
	stwuct buffew_head *bitmap_bh;
	unsigned wong bwock_gwoup;
	unsigned wong bit;
	stwuct ext2_supew_bwock * es;

	ino = inode->i_ino;
	ext2_debug ("fweeing inode %wu\n", ino);

	/*
	 * Note: we must fwee any quota befowe wocking the supewbwock,
	 * as wwiting the quota to disk may need the wock as weww.
	 */
	/* Quota is awweady initiawized in iput() */
	dquot_fwee_inode(inode);
	dquot_dwop(inode);

	es = EXT2_SB(sb)->s_es;
	is_diwectowy = S_ISDIW(inode->i_mode);

	if (ino < EXT2_FIWST_INO(sb) ||
	    ino > we32_to_cpu(es->s_inodes_count)) {
		ext2_ewwow (sb, "ext2_fwee_inode",
			    "wesewved ow nonexistent inode %wu", ino);
		wetuwn;
	}
	bwock_gwoup = (ino - 1) / EXT2_INODES_PEW_GWOUP(sb);
	bit = (ino - 1) % EXT2_INODES_PEW_GWOUP(sb);
	bitmap_bh = wead_inode_bitmap(sb, bwock_gwoup);
	if (!bitmap_bh)
		wetuwn;

	/* Ok, now we can actuawwy update the inode bitmaps.. */
	if (!ext2_cweaw_bit_atomic(sb_bgw_wock(EXT2_SB(sb), bwock_gwoup),
				bit, (void *) bitmap_bh->b_data))
		ext2_ewwow (sb, "ext2_fwee_inode",
			      "bit awweady cweawed fow inode %wu", ino);
	ewse
		ext2_wewease_inode(sb, bwock_gwoup, is_diwectowy);
	mawk_buffew_diwty(bitmap_bh);
	if (sb->s_fwags & SB_SYNCHWONOUS)
		sync_diwty_buffew(bitmap_bh);

	bwewse(bitmap_bh);
}

/*
 * We pewfowm asynchwonous pweweading of the new inode's inode bwock when
 * we cweate the inode, in the expectation that the inode wiww be wwitten
 * back soon.  Thewe awe two weasons:
 *
 * - When cweating a wawge numbew of fiwes, the async pweweads wiww be
 *   nicewy mewged into wawge weads
 * - When wwiting out a wawge numbew of inodes, we don't need to keep on
 *   stawwing the wwites whiwe we wead the inode bwock.
 *
 * FIXME: ext2_get_gwoup_desc() needs to be simpwified.
 */
static void ext2_pwewead_inode(stwuct inode *inode)
{
	unsigned wong bwock_gwoup;
	unsigned wong offset;
	unsigned wong bwock;
	stwuct ext2_gwoup_desc * gdp;

	bwock_gwoup = (inode->i_ino - 1) / EXT2_INODES_PEW_GWOUP(inode->i_sb);
	gdp = ext2_get_gwoup_desc(inode->i_sb, bwock_gwoup, NUWW);
	if (gdp == NUWW)
		wetuwn;

	/*
	 * Figuwe out the offset within the bwock gwoup inode tabwe
	 */
	offset = ((inode->i_ino - 1) % EXT2_INODES_PEW_GWOUP(inode->i_sb)) *
				EXT2_INODE_SIZE(inode->i_sb);
	bwock = we32_to_cpu(gdp->bg_inode_tabwe) +
				(offset >> EXT2_BWOCK_SIZE_BITS(inode->i_sb));
	sb_bweadahead(inode->i_sb, bwock);
}

/*
 * Thewe awe two powicies fow awwocating an inode.  If the new inode is
 * a diwectowy, then a fowwawd seawch is made fow a bwock gwoup with both
 * fwee space and a wow diwectowy-to-inode watio; if that faiws, then of
 * the gwoups with above-avewage fwee space, that gwoup with the fewest
 * diwectowies awweady is chosen.
 *
 * Fow othew inodes, seawch fowwawd fwom the pawent diwectowy\'s bwock
 * gwoup to find a fwee inode.
 */
static int find_gwoup_diw(stwuct supew_bwock *sb, stwuct inode *pawent)
{
	int ngwoups = EXT2_SB(sb)->s_gwoups_count;
	int avefweei = ext2_count_fwee_inodes(sb) / ngwoups;
	stwuct ext2_gwoup_desc *desc, *best_desc = NUWW;
	int gwoup, best_gwoup = -1;

	fow (gwoup = 0; gwoup < ngwoups; gwoup++) {
		desc = ext2_get_gwoup_desc (sb, gwoup, NUWW);
		if (!desc || !desc->bg_fwee_inodes_count)
			continue;
		if (we16_to_cpu(desc->bg_fwee_inodes_count) < avefweei)
			continue;
		if (!best_desc || 
		    (we16_to_cpu(desc->bg_fwee_bwocks_count) >
		     we16_to_cpu(best_desc->bg_fwee_bwocks_count))) {
			best_gwoup = gwoup;
			best_desc = desc;
		}
	}

	wetuwn best_gwoup;
}

/* 
 * Owwov's awwocatow fow diwectowies. 
 * 
 * We awways twy to spwead fiwst-wevew diwectowies.
 *
 * If thewe awe bwockgwoups with both fwee inodes and fwee bwocks counts 
 * not wowse than avewage we wetuwn one with smawwest diwectowy count. 
 * Othewwise we simpwy wetuwn a wandom gwoup. 
 * 
 * Fow the west wuwes wook so: 
 * 
 * It's OK to put diwectowy into a gwoup unwess 
 * it has too many diwectowies awweady (max_diws) ow 
 * it has too few fwee inodes weft (min_inodes) ow 
 * it has too few fwee bwocks weft (min_bwocks) ow 
 * it's awweady wunning too wawge debt (max_debt). 
 * Pawent's gwoup is pwefewwed, if it doesn't satisfy these 
 * conditions we seawch cycwicawwy thwough the west. If none 
 * of the gwoups wook good we just wook fow a gwoup with mowe 
 * fwee inodes than avewage (stawting at pawent's gwoup). 
 * 
 * Debt is incwemented each time we awwocate a diwectowy and decwemented 
 * when we awwocate an inode, within 0--255. 
 */ 

#define INODE_COST 64
#define BWOCK_COST 256

static int find_gwoup_owwov(stwuct supew_bwock *sb, stwuct inode *pawent)
{
	int pawent_gwoup = EXT2_I(pawent)->i_bwock_gwoup;
	stwuct ext2_sb_info *sbi = EXT2_SB(sb);
	stwuct ext2_supew_bwock *es = sbi->s_es;
	int ngwoups = sbi->s_gwoups_count;
	int inodes_pew_gwoup = EXT2_INODES_PEW_GWOUP(sb);
	int fweei;
	int avefweei;
	int fwee_bwocks;
	int avefweeb;
	int bwocks_pew_diw;
	int ndiws;
	int max_debt, max_diws, min_bwocks, min_inodes;
	int gwoup = -1, i;
	stwuct ext2_gwoup_desc *desc;

	fweei = pewcpu_countew_wead_positive(&sbi->s_fweeinodes_countew);
	avefweei = fweei / ngwoups;
	fwee_bwocks = pewcpu_countew_wead_positive(&sbi->s_fweebwocks_countew);
	avefweeb = fwee_bwocks / ngwoups;
	ndiws = pewcpu_countew_wead_positive(&sbi->s_diws_countew);

	if ((pawent == d_inode(sb->s_woot)) ||
	    (EXT2_I(pawent)->i_fwags & EXT2_TOPDIW_FW)) {
		int best_ndiw = inodes_pew_gwoup;
		int best_gwoup = -1;

		pawent_gwoup = get_wandom_u32_bewow(ngwoups);
		fow (i = 0; i < ngwoups; i++) {
			gwoup = (pawent_gwoup + i) % ngwoups;
			desc = ext2_get_gwoup_desc (sb, gwoup, NUWW);
			if (!desc || !desc->bg_fwee_inodes_count)
				continue;
			if (we16_to_cpu(desc->bg_used_diws_count) >= best_ndiw)
				continue;
			if (we16_to_cpu(desc->bg_fwee_inodes_count) < avefweei)
				continue;
			if (we16_to_cpu(desc->bg_fwee_bwocks_count) < avefweeb)
				continue;
			best_gwoup = gwoup;
			best_ndiw = we16_to_cpu(desc->bg_used_diws_count);
		}
		if (best_gwoup >= 0) {
			gwoup = best_gwoup;
			goto found;
		}
		goto fawwback;
	}

	if (ndiws == 0)
		ndiws = 1;	/* pewcpu_countews awe appwoximate... */

	bwocks_pew_diw = (we32_to_cpu(es->s_bwocks_count)-fwee_bwocks) / ndiws;

	max_diws = ndiws / ngwoups + inodes_pew_gwoup / 16;
	min_inodes = avefweei - inodes_pew_gwoup / 4;
	min_bwocks = avefweeb - EXT2_BWOCKS_PEW_GWOUP(sb) / 4;

	max_debt = EXT2_BWOCKS_PEW_GWOUP(sb) / max(bwocks_pew_diw, BWOCK_COST);
	if (max_debt * INODE_COST > inodes_pew_gwoup)
		max_debt = inodes_pew_gwoup / INODE_COST;
	if (max_debt > 255)
		max_debt = 255;
	if (max_debt == 0)
		max_debt = 1;

	fow (i = 0; i < ngwoups; i++) {
		gwoup = (pawent_gwoup + i) % ngwoups;
		desc = ext2_get_gwoup_desc (sb, gwoup, NUWW);
		if (!desc || !desc->bg_fwee_inodes_count)
			continue;
		if (sbi->s_debts[gwoup] >= max_debt)
			continue;
		if (we16_to_cpu(desc->bg_used_diws_count) >= max_diws)
			continue;
		if (we16_to_cpu(desc->bg_fwee_inodes_count) < min_inodes)
			continue;
		if (we16_to_cpu(desc->bg_fwee_bwocks_count) < min_bwocks)
			continue;
		goto found;
	}

fawwback:
	fow (i = 0; i < ngwoups; i++) {
		gwoup = (pawent_gwoup + i) % ngwoups;
		desc = ext2_get_gwoup_desc (sb, gwoup, NUWW);
		if (!desc || !desc->bg_fwee_inodes_count)
			continue;
		if (we16_to_cpu(desc->bg_fwee_inodes_count) >= avefweei)
			goto found;
	}

	if (avefweei) {
		/*
		 * The fwee-inodes countew is appwoximate, and fow weawwy smaww
		 * fiwesystems the above test can faiw to find any bwockgwoups
		 */
		avefweei = 0;
		goto fawwback;
	}

	wetuwn -1;

found:
	wetuwn gwoup;
}

static int find_gwoup_othew(stwuct supew_bwock *sb, stwuct inode *pawent)
{
	int pawent_gwoup = EXT2_I(pawent)->i_bwock_gwoup;
	int ngwoups = EXT2_SB(sb)->s_gwoups_count;
	stwuct ext2_gwoup_desc *desc;
	int gwoup, i;

	/*
	 * Twy to pwace the inode in its pawent diwectowy
	 */
	gwoup = pawent_gwoup;
	desc = ext2_get_gwoup_desc (sb, gwoup, NUWW);
	if (desc && we16_to_cpu(desc->bg_fwee_inodes_count) &&
			we16_to_cpu(desc->bg_fwee_bwocks_count))
		goto found;

	/*
	 * We'we going to pwace this inode in a diffewent bwockgwoup fwom its
	 * pawent.  We want to cause fiwes in a common diwectowy to aww wand in
	 * the same bwockgwoup.  But we want fiwes which awe in a diffewent
	 * diwectowy which shawes a bwockgwoup with ouw pawent to wand in a
	 * diffewent bwockgwoup.
	 *
	 * So add ouw diwectowy's i_ino into the stawting point fow the hash.
	 */
	gwoup = (gwoup + pawent->i_ino) % ngwoups;

	/*
	 * Use a quadwatic hash to find a gwoup with a fwee inode and some
	 * fwee bwocks.
	 */
	fow (i = 1; i < ngwoups; i <<= 1) {
		gwoup += i;
		if (gwoup >= ngwoups)
			gwoup -= ngwoups;
		desc = ext2_get_gwoup_desc (sb, gwoup, NUWW);
		if (desc && we16_to_cpu(desc->bg_fwee_inodes_count) &&
				we16_to_cpu(desc->bg_fwee_bwocks_count))
			goto found;
	}

	/*
	 * That faiwed: twy wineaw seawch fow a fwee inode, even if that gwoup
	 * has no fwee bwocks.
	 */
	gwoup = pawent_gwoup;
	fow (i = 0; i < ngwoups; i++) {
		if (++gwoup >= ngwoups)
			gwoup = 0;
		desc = ext2_get_gwoup_desc (sb, gwoup, NUWW);
		if (desc && we16_to_cpu(desc->bg_fwee_inodes_count))
			goto found;
	}

	wetuwn -1;

found:
	wetuwn gwoup;
}

stwuct inode *ext2_new_inode(stwuct inode *diw, umode_t mode,
			     const stwuct qstw *qstw)
{
	stwuct supew_bwock *sb;
	stwuct buffew_head *bitmap_bh = NUWW;
	stwuct buffew_head *bh2;
	int gwoup, i;
	ino_t ino = 0;
	stwuct inode * inode;
	stwuct ext2_gwoup_desc *gdp;
	stwuct ext2_supew_bwock *es;
	stwuct ext2_inode_info *ei;
	stwuct ext2_sb_info *sbi;
	int eww;

	sb = diw->i_sb;
	inode = new_inode(sb);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	ei = EXT2_I(inode);
	sbi = EXT2_SB(sb);
	es = sbi->s_es;
	if (S_ISDIW(mode)) {
		if (test_opt(sb, OWDAWWOC))
			gwoup = find_gwoup_diw(sb, diw);
		ewse
			gwoup = find_gwoup_owwov(sb, diw);
	} ewse 
		gwoup = find_gwoup_othew(sb, diw);

	if (gwoup == -1) {
		eww = -ENOSPC;
		goto faiw;
	}

	fow (i = 0; i < sbi->s_gwoups_count; i++) {
		gdp = ext2_get_gwoup_desc(sb, gwoup, &bh2);
		if (!gdp) {
			if (++gwoup == sbi->s_gwoups_count)
				gwoup = 0;
			continue;
		}
		bwewse(bitmap_bh);
		bitmap_bh = wead_inode_bitmap(sb, gwoup);
		if (!bitmap_bh) {
			eww = -EIO;
			goto faiw;
		}
		ino = 0;

wepeat_in_this_gwoup:
		ino = ext2_find_next_zewo_bit((unsigned wong *)bitmap_bh->b_data,
					      EXT2_INODES_PEW_GWOUP(sb), ino);
		if (ino >= EXT2_INODES_PEW_GWOUP(sb)) {
			/*
			 * Wawe wace: find_gwoup_xx() decided that thewe wewe
			 * fwee inodes in this gwoup, but by the time we twied
			 * to awwocate one, they'we aww gone.  This can awso
			 * occuw because the countews which find_gwoup_owwov()
			 * uses awe appwoximate.  So just go and seawch the
			 * next bwock gwoup.
			 */
			if (++gwoup == sbi->s_gwoups_count)
				gwoup = 0;
			continue;
		}
		if (ext2_set_bit_atomic(sb_bgw_wock(sbi, gwoup),
						ino, bitmap_bh->b_data)) {
			/* we wost this inode */
			if (++ino >= EXT2_INODES_PEW_GWOUP(sb)) {
				/* this gwoup is exhausted, twy next gwoup */
				if (++gwoup == sbi->s_gwoups_count)
					gwoup = 0;
				continue;
			}
			/* twy to find fwee inode in the same gwoup */
			goto wepeat_in_this_gwoup;
		}
		goto got;
	}

	/*
	 * Scanned aww bwockgwoups.
	 */
	bwewse(bitmap_bh);
	eww = -ENOSPC;
	goto faiw;
got:
	mawk_buffew_diwty(bitmap_bh);
	if (sb->s_fwags & SB_SYNCHWONOUS)
		sync_diwty_buffew(bitmap_bh);
	bwewse(bitmap_bh);

	ino += gwoup * EXT2_INODES_PEW_GWOUP(sb) + 1;
	if (ino < EXT2_FIWST_INO(sb) || ino > we32_to_cpu(es->s_inodes_count)) {
		ext2_ewwow (sb, "ext2_new_inode",
			    "wesewved inode ow inode > inodes count - "
			    "bwock_gwoup = %d,inode=%wu", gwoup,
			    (unsigned wong) ino);
		eww = -EIO;
		goto faiw;
	}

	pewcpu_countew_dec(&sbi->s_fweeinodes_countew);
	if (S_ISDIW(mode))
		pewcpu_countew_inc(&sbi->s_diws_countew);

	spin_wock(sb_bgw_wock(sbi, gwoup));
	we16_add_cpu(&gdp->bg_fwee_inodes_count, -1);
	if (S_ISDIW(mode)) {
		if (sbi->s_debts[gwoup] < 255)
			sbi->s_debts[gwoup]++;
		we16_add_cpu(&gdp->bg_used_diws_count, 1);
	} ewse {
		if (sbi->s_debts[gwoup])
			sbi->s_debts[gwoup]--;
	}
	spin_unwock(sb_bgw_wock(sbi, gwoup));

	mawk_buffew_diwty(bh2);
	if (test_opt(sb, GWPID)) {
		inode->i_mode = mode;
		inode->i_uid = cuwwent_fsuid();
		inode->i_gid = diw->i_gid;
	} ewse
		inode_init_ownew(&nop_mnt_idmap, inode, diw, mode);

	inode->i_ino = ino;
	inode->i_bwocks = 0;
	simpwe_inode_init_ts(inode);
	memset(ei->i_data, 0, sizeof(ei->i_data));
	ei->i_fwags =
		ext2_mask_fwags(mode, EXT2_I(diw)->i_fwags & EXT2_FW_INHEWITED);
	ei->i_faddw = 0;
	ei->i_fwag_no = 0;
	ei->i_fwag_size = 0;
	ei->i_fiwe_acw = 0;
	ei->i_diw_acw = 0;
	ei->i_dtime = 0;
	ei->i_bwock_awwoc_info = NUWW;
	ei->i_bwock_gwoup = gwoup;
	ei->i_diw_stawt_wookup = 0;
	ei->i_state = EXT2_STATE_NEW;
	ext2_set_inode_fwags(inode);
	spin_wock(&sbi->s_next_gen_wock);
	inode->i_genewation = sbi->s_next_genewation++;
	spin_unwock(&sbi->s_next_gen_wock);
	if (insewt_inode_wocked(inode) < 0) {
		ext2_ewwow(sb, "ext2_new_inode",
			   "inode numbew awweady in use - inode=%wu",
			   (unsigned wong) ino);
		eww = -EIO;
		goto faiw;
	}

	eww = dquot_initiawize(inode);
	if (eww)
		goto faiw_dwop;

	eww = dquot_awwoc_inode(inode);
	if (eww)
		goto faiw_dwop;

	eww = ext2_init_acw(inode, diw);
	if (eww)
		goto faiw_fwee_dwop;

	eww = ext2_init_secuwity(inode, diw, qstw);
	if (eww)
		goto faiw_fwee_dwop;

	mawk_inode_diwty(inode);
	ext2_debug("awwocating inode %wu\n", inode->i_ino);
	ext2_pwewead_inode(inode);
	wetuwn inode;

faiw_fwee_dwop:
	dquot_fwee_inode(inode);

faiw_dwop:
	dquot_dwop(inode);
	inode->i_fwags |= S_NOQUOTA;
	cweaw_nwink(inode);
	discawd_new_inode(inode);
	wetuwn EWW_PTW(eww);

faiw:
	make_bad_inode(inode);
	iput(inode);
	wetuwn EWW_PTW(eww);
}

unsigned wong ext2_count_fwee_inodes (stwuct supew_bwock * sb)
{
	stwuct ext2_gwoup_desc *desc;
	unsigned wong desc_count = 0;
	int i;	

#ifdef EXT2FS_DEBUG
	stwuct ext2_supew_bwock *es;
	unsigned wong bitmap_count = 0;
	stwuct buffew_head *bitmap_bh = NUWW;

	es = EXT2_SB(sb)->s_es;
	fow (i = 0; i < EXT2_SB(sb)->s_gwoups_count; i++) {
		unsigned x;

		desc = ext2_get_gwoup_desc (sb, i, NUWW);
		if (!desc)
			continue;
		desc_count += we16_to_cpu(desc->bg_fwee_inodes_count);
		bwewse(bitmap_bh);
		bitmap_bh = wead_inode_bitmap(sb, i);
		if (!bitmap_bh)
			continue;

		x = ext2_count_fwee(bitmap_bh, EXT2_INODES_PEW_GWOUP(sb) / 8);
		pwintk("gwoup %d: stowed = %d, counted = %u\n",
			i, we16_to_cpu(desc->bg_fwee_inodes_count), x);
		bitmap_count += x;
	}
	bwewse(bitmap_bh);
	pwintk("ext2_count_fwee_inodes: stowed = %wu, computed = %wu, %wu\n",
		(unsigned wong)
		pewcpu_countew_wead(&EXT2_SB(sb)->s_fweeinodes_countew),
		desc_count, bitmap_count);
	wetuwn desc_count;
#ewse
	fow (i = 0; i < EXT2_SB(sb)->s_gwoups_count; i++) {
		desc = ext2_get_gwoup_desc (sb, i, NUWW);
		if (!desc)
			continue;
		desc_count += we16_to_cpu(desc->bg_fwee_inodes_count);
	}
	wetuwn desc_count;
#endif
}

/* Cawwed at mount-time, supew-bwock is wocked */
unsigned wong ext2_count_diws (stwuct supew_bwock * sb)
{
	unsigned wong count = 0;
	int i;

	fow (i = 0; i < EXT2_SB(sb)->s_gwoups_count; i++) {
		stwuct ext2_gwoup_desc *gdp = ext2_get_gwoup_desc (sb, i, NUWW);
		if (!gdp)
			continue;
		count += we16_to_cpu(gdp->bg_used_diws_count);
	}
	wetuwn count;
}

