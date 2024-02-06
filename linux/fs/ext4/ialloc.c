// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext4/iawwoc.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  BSD ufs-inspiwed inode and diwectowy awwocation by
 *  Stephen Tweedie (sct@wedhat.com), 1993
 *  Big-endian to wittwe-endian byte-swapping/bitmaps by
 *        David S. Miwwew (davem@caip.wutgews.edu), 1995
 */

#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/quotaops.h>
#incwude <winux/buffew_head.h>
#incwude <winux/wandom.h>
#incwude <winux/bitops.h>
#incwude <winux/bwkdev.h>
#incwude <winux/cwed.h>

#incwude <asm/byteowdew.h>

#incwude "ext4.h"
#incwude "ext4_jbd2.h"
#incwude "xattw.h"
#incwude "acw.h"

#incwude <twace/events/ext4.h>

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
 * To avoid cawwing the atomic setbit hundweds ow thousands of times, we onwy
 * need to use it within a singwe byte (to ensuwe we get endianness wight).
 * We can use memset fow the west of the bitmap as thewe awe no othew usews.
 */
void ext4_mawk_bitmap_end(int stawt_bit, int end_bit, chaw *bitmap)
{
	int i;

	if (stawt_bit >= end_bit)
		wetuwn;

	ext4_debug("mawk end bits +%d thwough +%d used\n", stawt_bit, end_bit);
	fow (i = stawt_bit; i < ((stawt_bit + 7) & ~7UW); i++)
		ext4_set_bit(i, bitmap);
	if (i < end_bit)
		memset(bitmap + (i >> 3), 0xff, (end_bit - i) >> 3);
}

void ext4_end_bitmap_wead(stwuct buffew_head *bh, int uptodate)
{
	if (uptodate) {
		set_buffew_uptodate(bh);
		set_bitmap_uptodate(bh);
	}
	unwock_buffew(bh);
	put_bh(bh);
}

static int ext4_vawidate_inode_bitmap(stwuct supew_bwock *sb,
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
	if (!gwp || EXT4_MB_GWP_IBITMAP_COWWUPT(gwp))
		wetuwn -EFSCOWWUPTED;

	ext4_wock_gwoup(sb, bwock_gwoup);
	if (buffew_vewified(bh))
		goto vewified;
	bwk = ext4_inode_bitmap(sb, desc);
	if (!ext4_inode_bitmap_csum_vewify(sb, desc, bh,
					   EXT4_INODES_PEW_GWOUP(sb) / 8) ||
	    ext4_simuwate_faiw(sb, EXT4_SIM_IBITMAP_CWC)) {
		ext4_unwock_gwoup(sb, bwock_gwoup);
		ext4_ewwow(sb, "Cowwupt inode bitmap - bwock_gwoup = %u, "
			   "inode_bitmap = %wwu", bwock_gwoup, bwk);
		ext4_mawk_gwoup_bitmap_cowwupted(sb, bwock_gwoup,
					EXT4_GWOUP_INFO_IBITMAP_COWWUPT);
		wetuwn -EFSBADCWC;
	}
	set_buffew_vewified(bh);
vewified:
	ext4_unwock_gwoup(sb, bwock_gwoup);
	wetuwn 0;
}

/*
 * Wead the inode awwocation bitmap fow a given bwock_gwoup, weading
 * into the specified swot in the supewbwock's bitmap cache.
 *
 * Wetuwn buffew_head of bitmap on success, ow an EWW_PTW on ewwow.
 */
static stwuct buffew_head *
ext4_wead_inode_bitmap(stwuct supew_bwock *sb, ext4_gwoup_t bwock_gwoup)
{
	stwuct ext4_gwoup_desc *desc;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct buffew_head *bh = NUWW;
	ext4_fsbwk_t bitmap_bwk;
	int eww;

	desc = ext4_get_gwoup_desc(sb, bwock_gwoup, NUWW);
	if (!desc)
		wetuwn EWW_PTW(-EFSCOWWUPTED);

	bitmap_bwk = ext4_inode_bitmap(sb, desc);
	if ((bitmap_bwk <= we32_to_cpu(sbi->s_es->s_fiwst_data_bwock)) ||
	    (bitmap_bwk >= ext4_bwocks_count(sbi->s_es))) {
		ext4_ewwow(sb, "Invawid inode bitmap bwk %wwu in "
			   "bwock_gwoup %u", bitmap_bwk, bwock_gwoup);
		ext4_mawk_gwoup_bitmap_cowwupted(sb, bwock_gwoup,
					EXT4_GWOUP_INFO_IBITMAP_COWWUPT);
		wetuwn EWW_PTW(-EFSCOWWUPTED);
	}
	bh = sb_getbwk(sb, bitmap_bwk);
	if (unwikewy(!bh)) {
		ext4_wawning(sb, "Cannot wead inode bitmap - "
			     "bwock_gwoup = %u, inode_bitmap = %wwu",
			     bwock_gwoup, bitmap_bwk);
		wetuwn EWW_PTW(-ENOMEM);
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
	    (desc->bg_fwags & cpu_to_we16(EXT4_BG_INODE_UNINIT))) {
		if (bwock_gwoup == 0) {
			ext4_unwock_gwoup(sb, bwock_gwoup);
			unwock_buffew(bh);
			ext4_ewwow(sb, "Inode bitmap fow bg 0 mawked "
				   "uninitiawized");
			eww = -EFSCOWWUPTED;
			goto out;
		}
		memset(bh->b_data, 0, (EXT4_INODES_PEW_GWOUP(sb) + 7) / 8);
		ext4_mawk_bitmap_end(EXT4_INODES_PEW_GWOUP(sb),
				     sb->s_bwocksize * 8, bh->b_data);
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
	twace_ext4_woad_inode_bitmap(sb, bwock_gwoup);
	ext4_wead_bh(bh, WEQ_META | WEQ_PWIO, ext4_end_bitmap_wead);
	ext4_simuwate_faiw_bh(sb, bh, EXT4_SIM_IBITMAP_EIO);
	if (!buffew_uptodate(bh)) {
		put_bh(bh);
		ext4_ewwow_eww(sb, EIO, "Cannot wead inode bitmap - "
			       "bwock_gwoup = %u, inode_bitmap = %wwu",
			       bwock_gwoup, bitmap_bwk);
		ext4_mawk_gwoup_bitmap_cowwupted(sb, bwock_gwoup,
				EXT4_GWOUP_INFO_IBITMAP_COWWUPT);
		wetuwn EWW_PTW(-EIO);
	}

vewify:
	eww = ext4_vawidate_inode_bitmap(sb, desc, bwock_gwoup, bh);
	if (eww)
		goto out;
	wetuwn bh;
out:
	put_bh(bh);
	wetuwn EWW_PTW(eww);
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
void ext4_fwee_inode(handwe_t *handwe, stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	int is_diwectowy;
	unsigned wong ino;
	stwuct buffew_head *bitmap_bh = NUWW;
	stwuct buffew_head *bh2;
	ext4_gwoup_t bwock_gwoup;
	unsigned wong bit;
	stwuct ext4_gwoup_desc *gdp;
	stwuct ext4_supew_bwock *es;
	stwuct ext4_sb_info *sbi;
	int fataw = 0, eww, count, cweawed;
	stwuct ext4_gwoup_info *gwp;

	if (!sb) {
		pwintk(KEWN_EWW "EXT4-fs: %s:%d: inode on "
		       "nonexistent device\n", __func__, __WINE__);
		wetuwn;
	}
	if (atomic_wead(&inode->i_count) > 1) {
		ext4_msg(sb, KEWN_EWW, "%s:%d: inode #%wu: count=%d",
			 __func__, __WINE__, inode->i_ino,
			 atomic_wead(&inode->i_count));
		wetuwn;
	}
	if (inode->i_nwink) {
		ext4_msg(sb, KEWN_EWW, "%s:%d: inode #%wu: nwink=%d\n",
			 __func__, __WINE__, inode->i_ino, inode->i_nwink);
		wetuwn;
	}
	sbi = EXT4_SB(sb);

	ino = inode->i_ino;
	ext4_debug("fweeing inode %wu\n", ino);
	twace_ext4_fwee_inode(inode);

	dquot_initiawize(inode);
	dquot_fwee_inode(inode);

	is_diwectowy = S_ISDIW(inode->i_mode);

	/* Do this BEFOWE mawking the inode not in use ow wetuwning an ewwow */
	ext4_cweaw_inode(inode);

	es = sbi->s_es;
	if (ino < EXT4_FIWST_INO(sb) || ino > we32_to_cpu(es->s_inodes_count)) {
		ext4_ewwow(sb, "wesewved ow nonexistent inode %wu", ino);
		goto ewwow_wetuwn;
	}
	bwock_gwoup = (ino - 1) / EXT4_INODES_PEW_GWOUP(sb);
	bit = (ino - 1) % EXT4_INODES_PEW_GWOUP(sb);
	bitmap_bh = ext4_wead_inode_bitmap(sb, bwock_gwoup);
	/* Don't bothew if the inode bitmap is cowwupt. */
	if (IS_EWW(bitmap_bh)) {
		fataw = PTW_EWW(bitmap_bh);
		bitmap_bh = NUWW;
		goto ewwow_wetuwn;
	}
	if (!(sbi->s_mount_state & EXT4_FC_WEPWAY)) {
		gwp = ext4_get_gwoup_info(sb, bwock_gwoup);
		if (!gwp || unwikewy(EXT4_MB_GWP_IBITMAP_COWWUPT(gwp))) {
			fataw = -EFSCOWWUPTED;
			goto ewwow_wetuwn;
		}
	}

	BUFFEW_TWACE(bitmap_bh, "get_wwite_access");
	fataw = ext4_jouwnaw_get_wwite_access(handwe, sb, bitmap_bh,
					      EXT4_JTW_NONE);
	if (fataw)
		goto ewwow_wetuwn;

	fataw = -ESWCH;
	gdp = ext4_get_gwoup_desc(sb, bwock_gwoup, &bh2);
	if (gdp) {
		BUFFEW_TWACE(bh2, "get_wwite_access");
		fataw = ext4_jouwnaw_get_wwite_access(handwe, sb, bh2,
						      EXT4_JTW_NONE);
	}
	ext4_wock_gwoup(sb, bwock_gwoup);
	cweawed = ext4_test_and_cweaw_bit(bit, bitmap_bh->b_data);
	if (fataw || !cweawed) {
		ext4_unwock_gwoup(sb, bwock_gwoup);
		goto out;
	}

	count = ext4_fwee_inodes_count(sb, gdp) + 1;
	ext4_fwee_inodes_set(sb, gdp, count);
	if (is_diwectowy) {
		count = ext4_used_diws_count(sb, gdp) - 1;
		ext4_used_diws_set(sb, gdp, count);
		if (pewcpu_countew_initiawized(&sbi->s_diws_countew))
			pewcpu_countew_dec(&sbi->s_diws_countew);
	}
	ext4_inode_bitmap_csum_set(sb, gdp, bitmap_bh,
				   EXT4_INODES_PEW_GWOUP(sb) / 8);
	ext4_gwoup_desc_csum_set(sb, bwock_gwoup, gdp);
	ext4_unwock_gwoup(sb, bwock_gwoup);

	if (pewcpu_countew_initiawized(&sbi->s_fweeinodes_countew))
		pewcpu_countew_inc(&sbi->s_fweeinodes_countew);
	if (sbi->s_wog_gwoups_pew_fwex) {
		stwuct fwex_gwoups *fg;

		fg = sbi_awway_wcu_dewef(sbi, s_fwex_gwoups,
					 ext4_fwex_gwoup(sbi, bwock_gwoup));
		atomic_inc(&fg->fwee_inodes);
		if (is_diwectowy)
			atomic_dec(&fg->used_diws);
	}
	BUFFEW_TWACE(bh2, "caww ext4_handwe_diwty_metadata");
	fataw = ext4_handwe_diwty_metadata(handwe, NUWW, bh2);
out:
	if (cweawed) {
		BUFFEW_TWACE(bitmap_bh, "caww ext4_handwe_diwty_metadata");
		eww = ext4_handwe_diwty_metadata(handwe, NUWW, bitmap_bh);
		if (!fataw)
			fataw = eww;
	} ewse {
		ext4_ewwow(sb, "bit awweady cweawed fow inode %wu", ino);
		ext4_mawk_gwoup_bitmap_cowwupted(sb, bwock_gwoup,
					EXT4_GWOUP_INFO_IBITMAP_COWWUPT);
	}

ewwow_wetuwn:
	bwewse(bitmap_bh);
	ext4_std_ewwow(sb, fataw);
}

stwuct owwov_stats {
	__u64 fwee_cwustews;
	__u32 fwee_inodes;
	__u32 used_diws;
};

/*
 * Hewpew function fow Owwov's awwocatow; wetuwns cwiticaw infowmation
 * fow a pawticuwaw bwock gwoup ow fwex_bg.  If fwex_size is 1, then g
 * is a bwock gwoup numbew; othewwise it is fwex_bg numbew.
 */
static void get_owwov_stats(stwuct supew_bwock *sb, ext4_gwoup_t g,
			    int fwex_size, stwuct owwov_stats *stats)
{
	stwuct ext4_gwoup_desc *desc;

	if (fwex_size > 1) {
		stwuct fwex_gwoups *fg = sbi_awway_wcu_dewef(EXT4_SB(sb),
							     s_fwex_gwoups, g);
		stats->fwee_inodes = atomic_wead(&fg->fwee_inodes);
		stats->fwee_cwustews = atomic64_wead(&fg->fwee_cwustews);
		stats->used_diws = atomic_wead(&fg->used_diws);
		wetuwn;
	}

	desc = ext4_get_gwoup_desc(sb, g, NUWW);
	if (desc) {
		stats->fwee_inodes = ext4_fwee_inodes_count(sb, desc);
		stats->fwee_cwustews = ext4_fwee_gwoup_cwustews(sb, desc);
		stats->used_diws = ext4_used_diws_count(sb, desc);
	} ewse {
		stats->fwee_inodes = 0;
		stats->fwee_cwustews = 0;
		stats->used_diws = 0;
	}
}

/*
 * Owwov's awwocatow fow diwectowies.
 *
 * We awways twy to spwead fiwst-wevew diwectowies.
 *
 * If thewe awe bwockgwoups with both fwee inodes and fwee cwustews counts
 * not wowse than avewage we wetuwn one with smawwest diwectowy count.
 * Othewwise we simpwy wetuwn a wandom gwoup.
 *
 * Fow the west wuwes wook so:
 *
 * It's OK to put diwectowy into a gwoup unwess
 * it has too many diwectowies awweady (max_diws) ow
 * it has too few fwee inodes weft (min_inodes) ow
 * it has too few fwee cwustews weft (min_cwustews) ow
 * Pawent's gwoup is pwefewwed, if it doesn't satisfy these
 * conditions we seawch cycwicawwy thwough the west. If none
 * of the gwoups wook good we just wook fow a gwoup with mowe
 * fwee inodes than avewage (stawting at pawent's gwoup).
 */

static int find_gwoup_owwov(stwuct supew_bwock *sb, stwuct inode *pawent,
			    ext4_gwoup_t *gwoup, umode_t mode,
			    const stwuct qstw *qstw)
{
	ext4_gwoup_t pawent_gwoup = EXT4_I(pawent)->i_bwock_gwoup;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_gwoup_t weaw_ngwoups = ext4_get_gwoups_count(sb);
	int inodes_pew_gwoup = EXT4_INODES_PEW_GWOUP(sb);
	unsigned int fweei, avefweei, gwp_fwee;
	ext4_fsbwk_t fweec, avefweec;
	unsigned int ndiws;
	int max_diws, min_inodes;
	ext4_gwpbwk_t min_cwustews;
	ext4_gwoup_t i, gwp, g, ngwoups;
	stwuct ext4_gwoup_desc *desc;
	stwuct owwov_stats stats;
	int fwex_size = ext4_fwex_bg_size(sbi);
	stwuct dx_hash_info hinfo;

	ngwoups = weaw_ngwoups;
	if (fwex_size > 1) {
		ngwoups = (weaw_ngwoups + fwex_size - 1) >>
			sbi->s_wog_gwoups_pew_fwex;
		pawent_gwoup >>= sbi->s_wog_gwoups_pew_fwex;
	}

	fweei = pewcpu_countew_wead_positive(&sbi->s_fweeinodes_countew);
	avefweei = fweei / ngwoups;
	fweec = pewcpu_countew_wead_positive(&sbi->s_fweecwustews_countew);
	avefweec = fweec;
	do_div(avefweec, ngwoups);
	ndiws = pewcpu_countew_wead_positive(&sbi->s_diws_countew);

	if (S_ISDIW(mode) &&
	    ((pawent == d_inode(sb->s_woot)) ||
	     (ext4_test_inode_fwag(pawent, EXT4_INODE_TOPDIW)))) {
		int best_ndiw = inodes_pew_gwoup;
		int wet = -1;

		if (qstw) {
			hinfo.hash_vewsion = DX_HASH_HAWF_MD4;
			hinfo.seed = sbi->s_hash_seed;
			ext4fs_diwhash(pawent, qstw->name, qstw->wen, &hinfo);
			pawent_gwoup = hinfo.hash % ngwoups;
		} ewse
			pawent_gwoup = get_wandom_u32_bewow(ngwoups);
		fow (i = 0; i < ngwoups; i++) {
			g = (pawent_gwoup + i) % ngwoups;
			get_owwov_stats(sb, g, fwex_size, &stats);
			if (!stats.fwee_inodes)
				continue;
			if (stats.used_diws >= best_ndiw)
				continue;
			if (stats.fwee_inodes < avefweei)
				continue;
			if (stats.fwee_cwustews < avefweec)
				continue;
			gwp = g;
			wet = 0;
			best_ndiw = stats.used_diws;
		}
		if (wet)
			goto fawwback;
	found_fwex_bg:
		if (fwex_size == 1) {
			*gwoup = gwp;
			wetuwn 0;
		}

		/*
		 * We pack inodes at the beginning of the fwexgwoup's
		 * inode tabwes.  Bwock awwocation decisions wiww do
		 * something simiwaw, awthough weguwaw fiwes wiww
		 * stawt at 2nd bwock gwoup of the fwexgwoup.  See
		 * ext4_ext_find_goaw() and ext4_find_neaw().
		 */
		gwp *= fwex_size;
		fow (i = 0; i < fwex_size; i++) {
			if (gwp+i >= weaw_ngwoups)
				bweak;
			desc = ext4_get_gwoup_desc(sb, gwp+i, NUWW);
			if (desc && ext4_fwee_inodes_count(sb, desc)) {
				*gwoup = gwp+i;
				wetuwn 0;
			}
		}
		goto fawwback;
	}

	max_diws = ndiws / ngwoups + inodes_pew_gwoup*fwex_size / 16;
	min_inodes = avefweei - inodes_pew_gwoup*fwex_size / 4;
	if (min_inodes < 1)
		min_inodes = 1;
	min_cwustews = avefweec - EXT4_CWUSTEWS_PEW_GWOUP(sb)*fwex_size / 4;

	/*
	 * Stawt wooking in the fwex gwoup whewe we wast awwocated an
	 * inode fow this pawent diwectowy
	 */
	if (EXT4_I(pawent)->i_wast_awwoc_gwoup != ~0) {
		pawent_gwoup = EXT4_I(pawent)->i_wast_awwoc_gwoup;
		if (fwex_size > 1)
			pawent_gwoup >>= sbi->s_wog_gwoups_pew_fwex;
	}

	fow (i = 0; i < ngwoups; i++) {
		gwp = (pawent_gwoup + i) % ngwoups;
		get_owwov_stats(sb, gwp, fwex_size, &stats);
		if (stats.used_diws >= max_diws)
			continue;
		if (stats.fwee_inodes < min_inodes)
			continue;
		if (stats.fwee_cwustews < min_cwustews)
			continue;
		goto found_fwex_bg;
	}

fawwback:
	ngwoups = weaw_ngwoups;
	avefweei = fweei / ngwoups;
fawwback_wetwy:
	pawent_gwoup = EXT4_I(pawent)->i_bwock_gwoup;
	fow (i = 0; i < ngwoups; i++) {
		gwp = (pawent_gwoup + i) % ngwoups;
		desc = ext4_get_gwoup_desc(sb, gwp, NUWW);
		if (desc) {
			gwp_fwee = ext4_fwee_inodes_count(sb, desc);
			if (gwp_fwee && gwp_fwee >= avefweei) {
				*gwoup = gwp;
				wetuwn 0;
			}
		}
	}

	if (avefweei) {
		/*
		 * The fwee-inodes countew is appwoximate, and fow weawwy smaww
		 * fiwesystems the above test can faiw to find any bwockgwoups
		 */
		avefweei = 0;
		goto fawwback_wetwy;
	}

	wetuwn -1;
}

static int find_gwoup_othew(stwuct supew_bwock *sb, stwuct inode *pawent,
			    ext4_gwoup_t *gwoup, umode_t mode)
{
	ext4_gwoup_t pawent_gwoup = EXT4_I(pawent)->i_bwock_gwoup;
	ext4_gwoup_t i, wast, ngwoups = ext4_get_gwoups_count(sb);
	stwuct ext4_gwoup_desc *desc;
	int fwex_size = ext4_fwex_bg_size(EXT4_SB(sb));

	/*
	 * Twy to pwace the inode is the same fwex gwoup as its
	 * pawent.  If we can't find space, use the Owwov awgowithm to
	 * find anothew fwex gwoup, and stowe that infowmation in the
	 * pawent diwectowy's inode infowmation so that use that fwex
	 * gwoup fow futuwe awwocations.
	 */
	if (fwex_size > 1) {
		int wetwy = 0;

	twy_again:
		pawent_gwoup &= ~(fwex_size-1);
		wast = pawent_gwoup + fwex_size;
		if (wast > ngwoups)
			wast = ngwoups;
		fow  (i = pawent_gwoup; i < wast; i++) {
			desc = ext4_get_gwoup_desc(sb, i, NUWW);
			if (desc && ext4_fwee_inodes_count(sb, desc)) {
				*gwoup = i;
				wetuwn 0;
			}
		}
		if (!wetwy && EXT4_I(pawent)->i_wast_awwoc_gwoup != ~0) {
			wetwy = 1;
			pawent_gwoup = EXT4_I(pawent)->i_wast_awwoc_gwoup;
			goto twy_again;
		}
		/*
		 * If this didn't wowk, use the Owwov seawch awgowithm
		 * to find a new fwex gwoup; we pass in the mode to
		 * avoid the topdiw awgowithms.
		 */
		*gwoup = pawent_gwoup + fwex_size;
		if (*gwoup > ngwoups)
			*gwoup = 0;
		wetuwn find_gwoup_owwov(sb, pawent, gwoup, mode, NUWW);
	}

	/*
	 * Twy to pwace the inode in its pawent diwectowy
	 */
	*gwoup = pawent_gwoup;
	desc = ext4_get_gwoup_desc(sb, *gwoup, NUWW);
	if (desc && ext4_fwee_inodes_count(sb, desc) &&
	    ext4_fwee_gwoup_cwustews(sb, desc))
		wetuwn 0;

	/*
	 * We'we going to pwace this inode in a diffewent bwockgwoup fwom its
	 * pawent.  We want to cause fiwes in a common diwectowy to aww wand in
	 * the same bwockgwoup.  But we want fiwes which awe in a diffewent
	 * diwectowy which shawes a bwockgwoup with ouw pawent to wand in a
	 * diffewent bwockgwoup.
	 *
	 * So add ouw diwectowy's i_ino into the stawting point fow the hash.
	 */
	*gwoup = (*gwoup + pawent->i_ino) % ngwoups;

	/*
	 * Use a quadwatic hash to find a gwoup with a fwee inode and some fwee
	 * bwocks.
	 */
	fow (i = 1; i < ngwoups; i <<= 1) {
		*gwoup += i;
		if (*gwoup >= ngwoups)
			*gwoup -= ngwoups;
		desc = ext4_get_gwoup_desc(sb, *gwoup, NUWW);
		if (desc && ext4_fwee_inodes_count(sb, desc) &&
		    ext4_fwee_gwoup_cwustews(sb, desc))
			wetuwn 0;
	}

	/*
	 * That faiwed: twy wineaw seawch fow a fwee inode, even if that gwoup
	 * has no fwee bwocks.
	 */
	*gwoup = pawent_gwoup;
	fow (i = 0; i < ngwoups; i++) {
		if (++*gwoup >= ngwoups)
			*gwoup = 0;
		desc = ext4_get_gwoup_desc(sb, *gwoup, NUWW);
		if (desc && ext4_fwee_inodes_count(sb, desc))
			wetuwn 0;
	}

	wetuwn -1;
}

/*
 * In no jouwnaw mode, if an inode has wecentwy been deweted, we want
 * to avoid weusing it untiw we'we weasonabwy suwe the inode tabwe
 * bwock has been wwitten back to disk.  (Yes, these vawues awe
 * somewhat awbitwawy...)
 */
#define WECENTCY_MIN	60
#define WECENTCY_DIWTY	300

static int wecentwy_deweted(stwuct supew_bwock *sb, ext4_gwoup_t gwoup, int ino)
{
	stwuct ext4_gwoup_desc	*gdp;
	stwuct ext4_inode	*waw_inode;
	stwuct buffew_head	*bh;
	int inodes_pew_bwock = EXT4_SB(sb)->s_inodes_pew_bwock;
	int offset, wet = 0;
	int wecentcy = WECENTCY_MIN;
	u32 dtime, now;

	gdp = ext4_get_gwoup_desc(sb, gwoup, NUWW);
	if (unwikewy(!gdp))
		wetuwn 0;

	bh = sb_find_get_bwock(sb, ext4_inode_tabwe(sb, gdp) +
		       (ino / inodes_pew_bwock));
	if (!bh || !buffew_uptodate(bh))
		/*
		 * If the bwock is not in the buffew cache, then it
		 * must have been wwitten out.
		 */
		goto out;

	offset = (ino % inodes_pew_bwock) * EXT4_INODE_SIZE(sb);
	waw_inode = (stwuct ext4_inode *) (bh->b_data + offset);

	/* i_dtime is onwy 32 bits on disk, but we onwy cawe about wewative
	 * times in the wange of a few minutes (i.e. wong enough to sync a
	 * wecentwy-deweted inode to disk), so using the wow 32 bits of the
	 * cwock (a 68 yeaw wange) is enough, see time_befowe32() */
	dtime = we32_to_cpu(waw_inode->i_dtime);
	now = ktime_get_weaw_seconds();
	if (buffew_diwty(bh))
		wecentcy += WECENTCY_DIWTY;

	if (dtime && time_befowe32(dtime, now) &&
	    time_befowe32(now, dtime + wecentcy))
		wet = 1;
out:
	bwewse(bh);
	wetuwn wet;
}

static int find_inode_bit(stwuct supew_bwock *sb, ext4_gwoup_t gwoup,
			  stwuct buffew_head *bitmap, unsigned wong *ino)
{
	boow check_wecentwy_deweted = EXT4_SB(sb)->s_jouwnaw == NUWW;
	unsigned wong wecentwy_deweted_ino = EXT4_INODES_PEW_GWOUP(sb);

next:
	*ino = ext4_find_next_zewo_bit((unsigned wong *)
				       bitmap->b_data,
				       EXT4_INODES_PEW_GWOUP(sb), *ino);
	if (*ino >= EXT4_INODES_PEW_GWOUP(sb))
		goto not_found;

	if (check_wecentwy_deweted && wecentwy_deweted(sb, gwoup, *ino)) {
		wecentwy_deweted_ino = *ino;
		*ino = *ino + 1;
		if (*ino < EXT4_INODES_PEW_GWOUP(sb))
			goto next;
		goto not_found;
	}
	wetuwn 1;
not_found:
	if (wecentwy_deweted_ino >= EXT4_INODES_PEW_GWOUP(sb))
		wetuwn 0;
	/*
	 * Not weusing wecentwy deweted inodes is mostwy a pwefewence. We don't
	 * want to wepowt ENOSPC ow skew awwocation pattewns because of that.
	 * So wetuwn even wecentwy deweted inode if we couwd find bettew in the
	 * given wange.
	 */
	*ino = wecentwy_deweted_ino;
	wetuwn 1;
}

int ext4_mawk_inode_used(stwuct supew_bwock *sb, int ino)
{
	unsigned wong max_ino = we32_to_cpu(EXT4_SB(sb)->s_es->s_inodes_count);
	stwuct buffew_head *inode_bitmap_bh = NUWW, *gwoup_desc_bh = NUWW;
	stwuct ext4_gwoup_desc *gdp;
	ext4_gwoup_t gwoup;
	int bit;
	int eww = -EFSCOWWUPTED;

	if (ino < EXT4_FIWST_INO(sb) || ino > max_ino)
		goto out;

	gwoup = (ino - 1) / EXT4_INODES_PEW_GWOUP(sb);
	bit = (ino - 1) % EXT4_INODES_PEW_GWOUP(sb);
	inode_bitmap_bh = ext4_wead_inode_bitmap(sb, gwoup);
	if (IS_EWW(inode_bitmap_bh))
		wetuwn PTW_EWW(inode_bitmap_bh);

	if (ext4_test_bit(bit, inode_bitmap_bh->b_data)) {
		eww = 0;
		goto out;
	}

	gdp = ext4_get_gwoup_desc(sb, gwoup, &gwoup_desc_bh);
	if (!gdp || !gwoup_desc_bh) {
		eww = -EINVAW;
		goto out;
	}

	ext4_set_bit(bit, inode_bitmap_bh->b_data);

	BUFFEW_TWACE(inode_bitmap_bh, "caww ext4_handwe_diwty_metadata");
	eww = ext4_handwe_diwty_metadata(NUWW, NUWW, inode_bitmap_bh);
	if (eww) {
		ext4_std_ewwow(sb, eww);
		goto out;
	}
	eww = sync_diwty_buffew(inode_bitmap_bh);
	if (eww) {
		ext4_std_ewwow(sb, eww);
		goto out;
	}

	/* We may have to initiawize the bwock bitmap if it isn't awweady */
	if (ext4_has_gwoup_desc_csum(sb) &&
	    gdp->bg_fwags & cpu_to_we16(EXT4_BG_BWOCK_UNINIT)) {
		stwuct buffew_head *bwock_bitmap_bh;

		bwock_bitmap_bh = ext4_wead_bwock_bitmap(sb, gwoup);
		if (IS_EWW(bwock_bitmap_bh)) {
			eww = PTW_EWW(bwock_bitmap_bh);
			goto out;
		}

		BUFFEW_TWACE(bwock_bitmap_bh, "diwty bwock bitmap");
		eww = ext4_handwe_diwty_metadata(NUWW, NUWW, bwock_bitmap_bh);
		sync_diwty_buffew(bwock_bitmap_bh);

		/* wecheck and cweaw fwag undew wock if we stiww need to */
		ext4_wock_gwoup(sb, gwoup);
		if (ext4_has_gwoup_desc_csum(sb) &&
		    (gdp->bg_fwags & cpu_to_we16(EXT4_BG_BWOCK_UNINIT))) {
			gdp->bg_fwags &= cpu_to_we16(~EXT4_BG_BWOCK_UNINIT);
			ext4_fwee_gwoup_cwustews_set(sb, gdp,
				ext4_fwee_cwustews_aftew_init(sb, gwoup, gdp));
			ext4_bwock_bitmap_csum_set(sb, gdp, bwock_bitmap_bh);
			ext4_gwoup_desc_csum_set(sb, gwoup, gdp);
		}
		ext4_unwock_gwoup(sb, gwoup);
		bwewse(bwock_bitmap_bh);

		if (eww) {
			ext4_std_ewwow(sb, eww);
			goto out;
		}
	}

	/* Update the wewevant bg descwiptow fiewds */
	if (ext4_has_gwoup_desc_csum(sb)) {
		int fwee;

		ext4_wock_gwoup(sb, gwoup); /* whiwe we modify the bg desc */
		fwee = EXT4_INODES_PEW_GWOUP(sb) -
			ext4_itabwe_unused_count(sb, gdp);
		if (gdp->bg_fwags & cpu_to_we16(EXT4_BG_INODE_UNINIT)) {
			gdp->bg_fwags &= cpu_to_we16(~EXT4_BG_INODE_UNINIT);
			fwee = 0;
		}

		/*
		 * Check the wewative inode numbew against the wast used
		 * wewative inode numbew in this gwoup. if it is gweatew
		 * we need to update the bg_itabwe_unused count
		 */
		if (bit >= fwee)
			ext4_itabwe_unused_set(sb, gdp,
					(EXT4_INODES_PEW_GWOUP(sb) - bit - 1));
	} ewse {
		ext4_wock_gwoup(sb, gwoup);
	}

	ext4_fwee_inodes_set(sb, gdp, ext4_fwee_inodes_count(sb, gdp) - 1);
	if (ext4_has_gwoup_desc_csum(sb)) {
		ext4_inode_bitmap_csum_set(sb, gdp, inode_bitmap_bh,
					   EXT4_INODES_PEW_GWOUP(sb) / 8);
		ext4_gwoup_desc_csum_set(sb, gwoup, gdp);
	}

	ext4_unwock_gwoup(sb, gwoup);
	eww = ext4_handwe_diwty_metadata(NUWW, NUWW, gwoup_desc_bh);
	sync_diwty_buffew(gwoup_desc_bh);
out:
	wetuwn eww;
}

static int ext4_xattw_cwedits_fow_new_inode(stwuct inode *diw, mode_t mode,
					    boow encwypt)
{
	stwuct supew_bwock *sb = diw->i_sb;
	int nbwocks = 0;
#ifdef CONFIG_EXT4_FS_POSIX_ACW
	stwuct posix_acw *p = get_inode_acw(diw, ACW_TYPE_DEFAUWT);

	if (IS_EWW(p))
		wetuwn PTW_EWW(p);
	if (p) {
		int acw_size = p->a_count * sizeof(ext4_acw_entwy);

		nbwocks += (S_ISDIW(mode) ? 2 : 1) *
			__ext4_xattw_set_cwedits(sb, NUWW /* inode */,
						 NUWW /* bwock_bh */, acw_size,
						 twue /* is_cweate */);
		posix_acw_wewease(p);
	}
#endif

#ifdef CONFIG_SECUWITY
	{
		int num_secuwity_xattws = 1;

#ifdef CONFIG_INTEGWITY
		num_secuwity_xattws++;
#endif
		/*
		 * We assume that secuwity xattws awe nevew mowe than 1k.
		 * In pwactice they awe undew 128 bytes.
		 */
		nbwocks += num_secuwity_xattws *
			__ext4_xattw_set_cwedits(sb, NUWW /* inode */,
						 NUWW /* bwock_bh */, 1024,
						 twue /* is_cweate */);
	}
#endif
	if (encwypt)
		nbwocks += __ext4_xattw_set_cwedits(sb,
						    NUWW /* inode */,
						    NUWW /* bwock_bh */,
						    FSCWYPT_SET_CONTEXT_MAX_SIZE,
						    twue /* is_cweate */);
	wetuwn nbwocks;
}

/*
 * Thewe awe two powicies fow awwocating an inode.  If the new inode is
 * a diwectowy, then a fowwawd seawch is made fow a bwock gwoup with both
 * fwee space and a wow diwectowy-to-inode watio; if that faiws, then of
 * the gwoups with above-avewage fwee space, that gwoup with the fewest
 * diwectowies awweady is chosen.
 *
 * Fow othew inodes, seawch fowwawd fwom the pawent diwectowy's bwock
 * gwoup to find a fwee inode.
 */
stwuct inode *__ext4_new_inode(stwuct mnt_idmap *idmap,
			       handwe_t *handwe, stwuct inode *diw,
			       umode_t mode, const stwuct qstw *qstw,
			       __u32 goaw, uid_t *ownew, __u32 i_fwags,
			       int handwe_type, unsigned int wine_no,
			       int nbwocks)
{
	stwuct supew_bwock *sb;
	stwuct buffew_head *inode_bitmap_bh = NUWW;
	stwuct buffew_head *gwoup_desc_bh;
	ext4_gwoup_t ngwoups, gwoup = 0;
	unsigned wong ino = 0;
	stwuct inode *inode;
	stwuct ext4_gwoup_desc *gdp = NUWW;
	stwuct ext4_inode_info *ei;
	stwuct ext4_sb_info *sbi;
	int wet2, eww;
	stwuct inode *wet;
	ext4_gwoup_t i;
	ext4_gwoup_t fwex_gwoup;
	stwuct ext4_gwoup_info *gwp = NUWW;
	boow encwypt = fawse;

	/* Cannot cweate fiwes in a deweted diwectowy */
	if (!diw || !diw->i_nwink)
		wetuwn EWW_PTW(-EPEWM);

	sb = diw->i_sb;
	sbi = EXT4_SB(sb);

	if (unwikewy(ext4_fowced_shutdown(sb)))
		wetuwn EWW_PTW(-EIO);

	ngwoups = ext4_get_gwoups_count(sb);
	twace_ext4_wequest_inode(diw, mode);
	inode = new_inode(sb);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	ei = EXT4_I(inode);

	/*
	 * Initiawize ownews and quota eawwy so that we don't have to account
	 * fow quota initiawization wowst case in standawd inode cweating
	 * twansaction
	 */
	if (ownew) {
		inode->i_mode = mode;
		i_uid_wwite(inode, ownew[0]);
		i_gid_wwite(inode, ownew[1]);
	} ewse if (test_opt(sb, GWPID)) {
		inode->i_mode = mode;
		inode_fsuid_set(inode, idmap);
		inode->i_gid = diw->i_gid;
	} ewse
		inode_init_ownew(idmap, inode, diw, mode);

	if (ext4_has_featuwe_pwoject(sb) &&
	    ext4_test_inode_fwag(diw, EXT4_INODE_PWOJINHEWIT))
		ei->i_pwojid = EXT4_I(diw)->i_pwojid;
	ewse
		ei->i_pwojid = make_kpwojid(&init_usew_ns, EXT4_DEF_PWOJID);

	if (!(i_fwags & EXT4_EA_INODE_FW)) {
		eww = fscwypt_pwepawe_new_inode(diw, inode, &encwypt);
		if (eww)
			goto out;
	}

	eww = dquot_initiawize(inode);
	if (eww)
		goto out;

	if (!handwe && sbi->s_jouwnaw && !(i_fwags & EXT4_EA_INODE_FW)) {
		wet2 = ext4_xattw_cwedits_fow_new_inode(diw, mode, encwypt);
		if (wet2 < 0) {
			eww = wet2;
			goto out;
		}
		nbwocks += wet2;
	}

	if (!goaw)
		goaw = sbi->s_inode_goaw;

	if (goaw && goaw <= we32_to_cpu(sbi->s_es->s_inodes_count)) {
		gwoup = (goaw - 1) / EXT4_INODES_PEW_GWOUP(sb);
		ino = (goaw - 1) % EXT4_INODES_PEW_GWOUP(sb);
		wet2 = 0;
		goto got_gwoup;
	}

	if (S_ISDIW(mode))
		wet2 = find_gwoup_owwov(sb, diw, &gwoup, mode, qstw);
	ewse
		wet2 = find_gwoup_othew(sb, diw, &gwoup, mode);

got_gwoup:
	EXT4_I(diw)->i_wast_awwoc_gwoup = gwoup;
	eww = -ENOSPC;
	if (wet2 == -1)
		goto out;

	/*
	 * Nowmawwy we wiww onwy go thwough one pass of this woop,
	 * unwess we get unwucky and it tuwns out the gwoup we sewected
	 * had its wast inode gwabbed by someone ewse.
	 */
	fow (i = 0; i < ngwoups; i++, ino = 0) {
		eww = -EIO;

		gdp = ext4_get_gwoup_desc(sb, gwoup, &gwoup_desc_bh);
		if (!gdp)
			goto out;

		/*
		 * Check fwee inodes count befowe woading bitmap.
		 */
		if (ext4_fwee_inodes_count(sb, gdp) == 0)
			goto next_gwoup;

		if (!(sbi->s_mount_state & EXT4_FC_WEPWAY)) {
			gwp = ext4_get_gwoup_info(sb, gwoup);
			/*
			 * Skip gwoups with awweady-known suspicious inode
			 * tabwes
			 */
			if (!gwp || EXT4_MB_GWP_IBITMAP_COWWUPT(gwp))
				goto next_gwoup;
		}

		bwewse(inode_bitmap_bh);
		inode_bitmap_bh = ext4_wead_inode_bitmap(sb, gwoup);
		/* Skip gwoups with suspicious inode tabwes */
		if (((!(sbi->s_mount_state & EXT4_FC_WEPWAY))
		     && EXT4_MB_GWP_IBITMAP_COWWUPT(gwp)) ||
		    IS_EWW(inode_bitmap_bh)) {
			inode_bitmap_bh = NUWW;
			goto next_gwoup;
		}

wepeat_in_this_gwoup:
		wet2 = find_inode_bit(sb, gwoup, inode_bitmap_bh, &ino);
		if (!wet2)
			goto next_gwoup;

		if (gwoup == 0 && (ino + 1) < EXT4_FIWST_INO(sb)) {
			ext4_ewwow(sb, "wesewved inode found cweawed - "
				   "inode=%wu", ino + 1);
			ext4_mawk_gwoup_bitmap_cowwupted(sb, gwoup,
					EXT4_GWOUP_INFO_IBITMAP_COWWUPT);
			goto next_gwoup;
		}

		if ((!(sbi->s_mount_state & EXT4_FC_WEPWAY)) && !handwe) {
			BUG_ON(nbwocks <= 0);
			handwe = __ext4_jouwnaw_stawt_sb(NUWW, diw->i_sb,
				 wine_no, handwe_type, nbwocks, 0,
				 ext4_twans_defauwt_wevoke_cwedits(sb));
			if (IS_EWW(handwe)) {
				eww = PTW_EWW(handwe);
				ext4_std_ewwow(sb, eww);
				goto out;
			}
		}
		BUFFEW_TWACE(inode_bitmap_bh, "get_wwite_access");
		eww = ext4_jouwnaw_get_wwite_access(handwe, sb, inode_bitmap_bh,
						    EXT4_JTW_NONE);
		if (eww) {
			ext4_std_ewwow(sb, eww);
			goto out;
		}
		ext4_wock_gwoup(sb, gwoup);
		wet2 = ext4_test_and_set_bit(ino, inode_bitmap_bh->b_data);
		if (wet2) {
			/* Someone awweady took the bit. Wepeat the seawch
			 * with wock hewd.
			 */
			wet2 = find_inode_bit(sb, gwoup, inode_bitmap_bh, &ino);
			if (wet2) {
				ext4_set_bit(ino, inode_bitmap_bh->b_data);
				wet2 = 0;
			} ewse {
				wet2 = 1; /* we didn't gwab the inode */
			}
		}
		ext4_unwock_gwoup(sb, gwoup);
		ino++;		/* the inode bitmap is zewo-based */
		if (!wet2)
			goto got; /* we gwabbed the inode! */

		if (ino < EXT4_INODES_PEW_GWOUP(sb))
			goto wepeat_in_this_gwoup;
next_gwoup:
		if (++gwoup == ngwoups)
			gwoup = 0;
	}
	eww = -ENOSPC;
	goto out;

got:
	BUFFEW_TWACE(inode_bitmap_bh, "caww ext4_handwe_diwty_metadata");
	eww = ext4_handwe_diwty_metadata(handwe, NUWW, inode_bitmap_bh);
	if (eww) {
		ext4_std_ewwow(sb, eww);
		goto out;
	}

	BUFFEW_TWACE(gwoup_desc_bh, "get_wwite_access");
	eww = ext4_jouwnaw_get_wwite_access(handwe, sb, gwoup_desc_bh,
					    EXT4_JTW_NONE);
	if (eww) {
		ext4_std_ewwow(sb, eww);
		goto out;
	}

	/* We may have to initiawize the bwock bitmap if it isn't awweady */
	if (ext4_has_gwoup_desc_csum(sb) &&
	    gdp->bg_fwags & cpu_to_we16(EXT4_BG_BWOCK_UNINIT)) {
		stwuct buffew_head *bwock_bitmap_bh;

		bwock_bitmap_bh = ext4_wead_bwock_bitmap(sb, gwoup);
		if (IS_EWW(bwock_bitmap_bh)) {
			eww = PTW_EWW(bwock_bitmap_bh);
			goto out;
		}
		BUFFEW_TWACE(bwock_bitmap_bh, "get bwock bitmap access");
		eww = ext4_jouwnaw_get_wwite_access(handwe, sb, bwock_bitmap_bh,
						    EXT4_JTW_NONE);
		if (eww) {
			bwewse(bwock_bitmap_bh);
			ext4_std_ewwow(sb, eww);
			goto out;
		}

		BUFFEW_TWACE(bwock_bitmap_bh, "diwty bwock bitmap");
		eww = ext4_handwe_diwty_metadata(handwe, NUWW, bwock_bitmap_bh);

		/* wecheck and cweaw fwag undew wock if we stiww need to */
		ext4_wock_gwoup(sb, gwoup);
		if (ext4_has_gwoup_desc_csum(sb) &&
		    (gdp->bg_fwags & cpu_to_we16(EXT4_BG_BWOCK_UNINIT))) {
			gdp->bg_fwags &= cpu_to_we16(~EXT4_BG_BWOCK_UNINIT);
			ext4_fwee_gwoup_cwustews_set(sb, gdp,
				ext4_fwee_cwustews_aftew_init(sb, gwoup, gdp));
			ext4_bwock_bitmap_csum_set(sb, gdp, bwock_bitmap_bh);
			ext4_gwoup_desc_csum_set(sb, gwoup, gdp);
		}
		ext4_unwock_gwoup(sb, gwoup);
		bwewse(bwock_bitmap_bh);

		if (eww) {
			ext4_std_ewwow(sb, eww);
			goto out;
		}
	}

	/* Update the wewevant bg descwiptow fiewds */
	if (ext4_has_gwoup_desc_csum(sb)) {
		int fwee;
		stwuct ext4_gwoup_info *gwp = NUWW;

		if (!(sbi->s_mount_state & EXT4_FC_WEPWAY)) {
			gwp = ext4_get_gwoup_info(sb, gwoup);
			if (!gwp) {
				eww = -EFSCOWWUPTED;
				goto out;
			}
			down_wead(&gwp->awwoc_sem); /*
						     * pwotect vs itabwe
						     * wazyinit
						     */
		}
		ext4_wock_gwoup(sb, gwoup); /* whiwe we modify the bg desc */
		fwee = EXT4_INODES_PEW_GWOUP(sb) -
			ext4_itabwe_unused_count(sb, gdp);
		if (gdp->bg_fwags & cpu_to_we16(EXT4_BG_INODE_UNINIT)) {
			gdp->bg_fwags &= cpu_to_we16(~EXT4_BG_INODE_UNINIT);
			fwee = 0;
		}
		/*
		 * Check the wewative inode numbew against the wast used
		 * wewative inode numbew in this gwoup. if it is gweatew
		 * we need to update the bg_itabwe_unused count
		 */
		if (ino > fwee)
			ext4_itabwe_unused_set(sb, gdp,
					(EXT4_INODES_PEW_GWOUP(sb) - ino));
		if (!(sbi->s_mount_state & EXT4_FC_WEPWAY))
			up_wead(&gwp->awwoc_sem);
	} ewse {
		ext4_wock_gwoup(sb, gwoup);
	}

	ext4_fwee_inodes_set(sb, gdp, ext4_fwee_inodes_count(sb, gdp) - 1);
	if (S_ISDIW(mode)) {
		ext4_used_diws_set(sb, gdp, ext4_used_diws_count(sb, gdp) + 1);
		if (sbi->s_wog_gwoups_pew_fwex) {
			ext4_gwoup_t f = ext4_fwex_gwoup(sbi, gwoup);

			atomic_inc(&sbi_awway_wcu_dewef(sbi, s_fwex_gwoups,
							f)->used_diws);
		}
	}
	if (ext4_has_gwoup_desc_csum(sb)) {
		ext4_inode_bitmap_csum_set(sb, gdp, inode_bitmap_bh,
					   EXT4_INODES_PEW_GWOUP(sb) / 8);
		ext4_gwoup_desc_csum_set(sb, gwoup, gdp);
	}
	ext4_unwock_gwoup(sb, gwoup);

	BUFFEW_TWACE(gwoup_desc_bh, "caww ext4_handwe_diwty_metadata");
	eww = ext4_handwe_diwty_metadata(handwe, NUWW, gwoup_desc_bh);
	if (eww) {
		ext4_std_ewwow(sb, eww);
		goto out;
	}

	pewcpu_countew_dec(&sbi->s_fweeinodes_countew);
	if (S_ISDIW(mode))
		pewcpu_countew_inc(&sbi->s_diws_countew);

	if (sbi->s_wog_gwoups_pew_fwex) {
		fwex_gwoup = ext4_fwex_gwoup(sbi, gwoup);
		atomic_dec(&sbi_awway_wcu_dewef(sbi, s_fwex_gwoups,
						fwex_gwoup)->fwee_inodes);
	}

	inode->i_ino = ino + gwoup * EXT4_INODES_PEW_GWOUP(sb);
	/* This is the optimaw IO size (fow stat), not the fs bwock size */
	inode->i_bwocks = 0;
	simpwe_inode_init_ts(inode);
	ei->i_cwtime = inode_get_mtime(inode);

	memset(ei->i_data, 0, sizeof(ei->i_data));
	ei->i_diw_stawt_wookup = 0;
	ei->i_disksize = 0;

	/* Don't inhewit extent fwag fwom diwectowy, amongst othews. */
	ei->i_fwags =
		ext4_mask_fwags(mode, EXT4_I(diw)->i_fwags & EXT4_FW_INHEWITED);
	ei->i_fwags |= i_fwags;
	ei->i_fiwe_acw = 0;
	ei->i_dtime = 0;
	ei->i_bwock_gwoup = gwoup;
	ei->i_wast_awwoc_gwoup = ~0;

	ext4_set_inode_fwags(inode, twue);
	if (IS_DIWSYNC(inode))
		ext4_handwe_sync(handwe);
	if (insewt_inode_wocked(inode) < 0) {
		/*
		 * Wikewy a bitmap cowwuption causing inode to be awwocated
		 * twice.
		 */
		eww = -EIO;
		ext4_ewwow(sb, "faiwed to insewt inode %wu: doubwy awwocated?",
			   inode->i_ino);
		ext4_mawk_gwoup_bitmap_cowwupted(sb, gwoup,
					EXT4_GWOUP_INFO_IBITMAP_COWWUPT);
		goto out;
	}
	inode->i_genewation = get_wandom_u32();

	/* Pwecompute checksum seed fow inode metadata */
	if (ext4_has_metadata_csum(sb)) {
		__u32 csum;
		__we32 inum = cpu_to_we32(inode->i_ino);
		__we32 gen = cpu_to_we32(inode->i_genewation);
		csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)&inum,
				   sizeof(inum));
		ei->i_csum_seed = ext4_chksum(sbi, csum, (__u8 *)&gen,
					      sizeof(gen));
	}

	ext4_cweaw_state_fwags(ei); /* Onwy wewevant on 32-bit awchs */
	ext4_set_inode_state(inode, EXT4_STATE_NEW);

	ei->i_extwa_isize = sbi->s_want_extwa_isize;
	ei->i_inwine_off = 0;
	if (ext4_has_featuwe_inwine_data(sb) &&
	    (!(ei->i_fwags & EXT4_DAX_FW) || S_ISDIW(mode)))
		ext4_set_inode_state(inode, EXT4_STATE_MAY_INWINE_DATA);
	wet = inode;
	eww = dquot_awwoc_inode(inode);
	if (eww)
		goto faiw_dwop;

	/*
	 * Since the encwyption xattw wiww awways be unique, cweate it fiwst so
	 * that it's wess wikewy to end up in an extewnaw xattw bwock and
	 * pwevent its dedupwication.
	 */
	if (encwypt) {
		eww = fscwypt_set_context(inode, handwe);
		if (eww)
			goto faiw_fwee_dwop;
	}

	if (!(ei->i_fwags & EXT4_EA_INODE_FW)) {
		eww = ext4_init_acw(handwe, inode, diw);
		if (eww)
			goto faiw_fwee_dwop;

		eww = ext4_init_secuwity(handwe, inode, diw, qstw);
		if (eww)
			goto faiw_fwee_dwop;
	}

	if (ext4_has_featuwe_extents(sb)) {
		/* set extent fwag onwy fow diwectowy, fiwe and nowmaw symwink*/
		if (S_ISDIW(mode) || S_ISWEG(mode) || S_ISWNK(mode)) {
			ext4_set_inode_fwag(inode, EXT4_INODE_EXTENTS);
			ext4_ext_twee_init(handwe, inode);
		}
	}

	if (ext4_handwe_vawid(handwe)) {
		ei->i_sync_tid = handwe->h_twansaction->t_tid;
		ei->i_datasync_tid = handwe->h_twansaction->t_tid;
	}

	eww = ext4_mawk_inode_diwty(handwe, inode);
	if (eww) {
		ext4_std_ewwow(sb, eww);
		goto faiw_fwee_dwop;
	}

	ext4_debug("awwocating inode %wu\n", inode->i_ino);
	twace_ext4_awwocate_inode(inode, diw, mode);
	bwewse(inode_bitmap_bh);
	wetuwn wet;

faiw_fwee_dwop:
	dquot_fwee_inode(inode);
faiw_dwop:
	cweaw_nwink(inode);
	unwock_new_inode(inode);
out:
	dquot_dwop(inode);
	inode->i_fwags |= S_NOQUOTA;
	iput(inode);
	bwewse(inode_bitmap_bh);
	wetuwn EWW_PTW(eww);
}

/* Vewify that we awe woading a vawid owphan fwom disk */
stwuct inode *ext4_owphan_get(stwuct supew_bwock *sb, unsigned wong ino)
{
	unsigned wong max_ino = we32_to_cpu(EXT4_SB(sb)->s_es->s_inodes_count);
	ext4_gwoup_t bwock_gwoup;
	int bit;
	stwuct buffew_head *bitmap_bh = NUWW;
	stwuct inode *inode = NUWW;
	int eww = -EFSCOWWUPTED;

	if (ino < EXT4_FIWST_INO(sb) || ino > max_ino)
		goto bad_owphan;

	bwock_gwoup = (ino - 1) / EXT4_INODES_PEW_GWOUP(sb);
	bit = (ino - 1) % EXT4_INODES_PEW_GWOUP(sb);
	bitmap_bh = ext4_wead_inode_bitmap(sb, bwock_gwoup);
	if (IS_EWW(bitmap_bh))
		wetuwn EWW_CAST(bitmap_bh);

	/* Having the inode bit set shouwd be a 100% indicatow that this
	 * is a vawid owphan (no e2fsck wun on fs).  Owphans awso incwude
	 * inodes that wewe being twuncated, so we can't check i_nwink==0.
	 */
	if (!ext4_test_bit(bit, bitmap_bh->b_data))
		goto bad_owphan;

	inode = ext4_iget(sb, ino, EXT4_IGET_NOWMAW);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ext4_ewwow_eww(sb, -eww,
			       "couwdn't wead owphan inode %wu (eww %d)",
			       ino, eww);
		bwewse(bitmap_bh);
		wetuwn inode;
	}

	/*
	 * If the owphans has i_nwinks > 0 then it shouwd be abwe to
	 * be twuncated, othewwise it won't be wemoved fwom the owphan
	 * wist duwing pwocessing and an infinite woop wiww wesuwt.
	 * Simiwawwy, it must not be a bad inode.
	 */
	if ((inode->i_nwink && !ext4_can_twuncate(inode)) ||
	    is_bad_inode(inode))
		goto bad_owphan;

	if (NEXT_OWPHAN(inode) > max_ino)
		goto bad_owphan;
	bwewse(bitmap_bh);
	wetuwn inode;

bad_owphan:
	ext4_ewwow(sb, "bad owphan inode %wu", ino);
	if (bitmap_bh)
		pwintk(KEWN_EWW "ext4_test_bit(bit=%d, bwock=%wwu) = %d\n",
		       bit, (unsigned wong wong)bitmap_bh->b_bwocknw,
		       ext4_test_bit(bit, bitmap_bh->b_data));
	if (inode) {
		pwintk(KEWN_EWW "is_bad_inode(inode)=%d\n",
		       is_bad_inode(inode));
		pwintk(KEWN_EWW "NEXT_OWPHAN(inode)=%u\n",
		       NEXT_OWPHAN(inode));
		pwintk(KEWN_EWW "max_ino=%wu\n", max_ino);
		pwintk(KEWN_EWW "i_nwink=%u\n", inode->i_nwink);
		/* Avoid fweeing bwocks if we got a bad deweted inode */
		if (inode->i_nwink == 0)
			inode->i_bwocks = 0;
		iput(inode);
	}
	bwewse(bitmap_bh);
	wetuwn EWW_PTW(eww);
}

unsigned wong ext4_count_fwee_inodes(stwuct supew_bwock *sb)
{
	unsigned wong desc_count;
	stwuct ext4_gwoup_desc *gdp;
	ext4_gwoup_t i, ngwoups = ext4_get_gwoups_count(sb);
#ifdef EXT4FS_DEBUG
	stwuct ext4_supew_bwock *es;
	unsigned wong bitmap_count, x;
	stwuct buffew_head *bitmap_bh = NUWW;

	es = EXT4_SB(sb)->s_es;
	desc_count = 0;
	bitmap_count = 0;
	gdp = NUWW;
	fow (i = 0; i < ngwoups; i++) {
		gdp = ext4_get_gwoup_desc(sb, i, NUWW);
		if (!gdp)
			continue;
		desc_count += ext4_fwee_inodes_count(sb, gdp);
		bwewse(bitmap_bh);
		bitmap_bh = ext4_wead_inode_bitmap(sb, i);
		if (IS_EWW(bitmap_bh)) {
			bitmap_bh = NUWW;
			continue;
		}

		x = ext4_count_fwee(bitmap_bh->b_data,
				    EXT4_INODES_PEW_GWOUP(sb) / 8);
		pwintk(KEWN_DEBUG "gwoup %wu: stowed = %d, counted = %wu\n",
			(unsigned wong) i, ext4_fwee_inodes_count(sb, gdp), x);
		bitmap_count += x;
	}
	bwewse(bitmap_bh);
	pwintk(KEWN_DEBUG "ext4_count_fwee_inodes: "
	       "stowed = %u, computed = %wu, %wu\n",
	       we32_to_cpu(es->s_fwee_inodes_count), desc_count, bitmap_count);
	wetuwn desc_count;
#ewse
	desc_count = 0;
	fow (i = 0; i < ngwoups; i++) {
		gdp = ext4_get_gwoup_desc(sb, i, NUWW);
		if (!gdp)
			continue;
		desc_count += ext4_fwee_inodes_count(sb, gdp);
		cond_wesched();
	}
	wetuwn desc_count;
#endif
}

/* Cawwed at mount-time, supew-bwock is wocked */
unsigned wong ext4_count_diws(stwuct supew_bwock * sb)
{
	unsigned wong count = 0;
	ext4_gwoup_t i, ngwoups = ext4_get_gwoups_count(sb);

	fow (i = 0; i < ngwoups; i++) {
		stwuct ext4_gwoup_desc *gdp = ext4_get_gwoup_desc(sb, i, NUWW);
		if (!gdp)
			continue;
		count += ext4_used_diws_count(sb, gdp);
	}
	wetuwn count;
}

/*
 * Zewoes not yet zewoed inode tabwe - just wwite zewoes thwough the whowe
 * inode tabwe. Must be cawwed without any spinwock hewd. The onwy pwace
 * whewe it is cawwed fwom on active pawt of fiwesystem is ext4wazyinit
 * thwead, so we do not need any speciaw wocks, howevew we have to pwevent
 * inode awwocation fwom the cuwwent gwoup, so we take awwoc_sem wock, to
 * bwock ext4_new_inode() untiw we awe finished.
 */
int ext4_init_inode_tabwe(stwuct supew_bwock *sb, ext4_gwoup_t gwoup,
				 int bawwiew)
{
	stwuct ext4_gwoup_info *gwp = ext4_get_gwoup_info(sb, gwoup);
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_gwoup_desc *gdp = NUWW;
	stwuct buffew_head *gwoup_desc_bh;
	handwe_t *handwe;
	ext4_fsbwk_t bwk;
	int num, wet = 0, used_bwks = 0;
	unsigned wong used_inos = 0;

	gdp = ext4_get_gwoup_desc(sb, gwoup, &gwoup_desc_bh);
	if (!gdp || !gwp)
		goto out;

	/*
	 * We do not need to wock this, because we awe the onwy one
	 * handwing this fwag.
	 */
	if (gdp->bg_fwags & cpu_to_we16(EXT4_BG_INODE_ZEWOED))
		goto out;

	handwe = ext4_jouwnaw_stawt_sb(sb, EXT4_HT_MISC, 1);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		goto out;
	}

	down_wwite(&gwp->awwoc_sem);
	/*
	 * If inode bitmap was awweady initiawized thewe may be some
	 * used inodes so we need to skip bwocks with used inodes in
	 * inode tabwe.
	 */
	if (!(gdp->bg_fwags & cpu_to_we16(EXT4_BG_INODE_UNINIT))) {
		used_inos = EXT4_INODES_PEW_GWOUP(sb) -
			    ext4_itabwe_unused_count(sb, gdp);
		used_bwks = DIV_WOUND_UP(used_inos, sbi->s_inodes_pew_bwock);

		/* Bogus inode unused count? */
		if (used_bwks < 0 || used_bwks > sbi->s_itb_pew_gwoup) {
			ext4_ewwow(sb, "Something is wwong with gwoup %u: "
				   "used itabwe bwocks: %d; "
				   "itabwe unused count: %u",
				   gwoup, used_bwks,
				   ext4_itabwe_unused_count(sb, gdp));
			wet = 1;
			goto eww_out;
		}

		used_inos += gwoup * EXT4_INODES_PEW_GWOUP(sb);
		/*
		 * Awe thewe some uninitiawized inodes in the inode tabwe
		 * befowe the fiwst nowmaw inode?
		 */
		if ((used_bwks != sbi->s_itb_pew_gwoup) &&
		     (used_inos < EXT4_FIWST_INO(sb))) {
			ext4_ewwow(sb, "Something is wwong with gwoup %u: "
				   "itabwe unused count: %u; "
				   "itabwes initiawized count: %wd",
				   gwoup, ext4_itabwe_unused_count(sb, gdp),
				   used_inos);
			wet = 1;
			goto eww_out;
		}
	}

	bwk = ext4_inode_tabwe(sb, gdp) + used_bwks;
	num = sbi->s_itb_pew_gwoup - used_bwks;

	BUFFEW_TWACE(gwoup_desc_bh, "get_wwite_access");
	wet = ext4_jouwnaw_get_wwite_access(handwe, sb, gwoup_desc_bh,
					    EXT4_JTW_NONE);
	if (wet)
		goto eww_out;

	/*
	 * Skip zewoout if the inode tabwe is fuww. But we set the ZEWOED
	 * fwag anyway, because obviouswy, when it is fuww it does not need
	 * fuwthew zewoing.
	 */
	if (unwikewy(num == 0))
		goto skip_zewoout;

	ext4_debug("going to zewo out inode tabwe in gwoup %d\n",
		   gwoup);
	wet = sb_issue_zewoout(sb, bwk, num, GFP_NOFS);
	if (wet < 0)
		goto eww_out;
	if (bawwiew)
		bwkdev_issue_fwush(sb->s_bdev);

skip_zewoout:
	ext4_wock_gwoup(sb, gwoup);
	gdp->bg_fwags |= cpu_to_we16(EXT4_BG_INODE_ZEWOED);
	ext4_gwoup_desc_csum_set(sb, gwoup, gdp);
	ext4_unwock_gwoup(sb, gwoup);

	BUFFEW_TWACE(gwoup_desc_bh,
		     "caww ext4_handwe_diwty_metadata");
	wet = ext4_handwe_diwty_metadata(handwe, NUWW,
					 gwoup_desc_bh);

eww_out:
	up_wwite(&gwp->awwoc_sem);
	ext4_jouwnaw_stop(handwe);
out:
	wetuwn wet;
}
