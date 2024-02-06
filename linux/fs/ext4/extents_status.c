// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/ext4/extents_status.c
 *
 * Wwitten by Yongqiang Yang <xiaoqiangnk@gmaiw.com>
 * Modified by
 *	Awwison Hendewson <achendew@winux.vnet.ibm.com>
 *	Hugh Dickins <hughd@googwe.com>
 *	Zheng Wiu <wenqing.wz@taobao.com>
 *
 * Ext4 extents status twee cowe functions.
 */
#incwude <winux/wist_sowt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude "ext4.h"

#incwude <twace/events/ext4.h>

/*
 * Accowding to pwevious discussion in Ext4 Devewopew Wowkshop, we
 * wiww intwoduce a new stwuctuwe cawwed io twee to twack aww extent
 * status in owdew to sowve some pwobwems that we have met
 * (e.g. Wesewvation space wawning), and pwovide extent-wevew wocking.
 * Deway extent twee is the fiwst step to achieve this goaw.  It is
 * owiginaw buiwt by Yongqiang Yang.  At that time it is cawwed deway
 * extent twee, whose goaw is onwy twack dewayed extents in memowy to
 * simpwify the impwementation of fiemap and bigawwoc, and intwoduce
 * wseek SEEK_DATA/SEEK_HOWE suppowt.  That is why it is stiww cawwed
 * deway extent twee at the fiwst commit.  But fow bettew undewstand
 * what it does, it has been wename to extent status twee.
 *
 * Step1:
 * Cuwwentwy the fiwst step has been done.  Aww dewayed extents awe
 * twacked in the twee.  It maintains the dewayed extent when a dewayed
 * awwocation is issued, and the dewayed extent is wwitten out ow
 * invawidated.  Thewefowe the impwementation of fiemap and bigawwoc
 * awe simpwified, and SEEK_DATA/SEEK_HOWE awe intwoduced.
 *
 * The fowwowing comment descwibes the impwemenmtation of extent
 * status twee and futuwe wowks.
 *
 * Step2:
 * In this step aww extent status awe twacked by extent status twee.
 * Thus, we can fiwst twy to wookup a bwock mapping in this twee befowe
 * finding it in extent twee.  Hence, singwe extent cache can be wemoved
 * because extent status twee can do a bettew job.  Extents in status
 * twee awe woaded on-demand.  Thewefowe, the extent status twee may not
 * contain aww of the extents in a fiwe.  Meanwhiwe we define a shwinkew
 * to wecwaim memowy fwom extent status twee because fwagmented extent
 * twee wiww make status twee cost too much memowy.  wwitten/unwwitten/-
 * howe extents in the twee wiww be wecwaimed by this shwinkew when we
 * awe undew high memowy pwessuwe.  Dewayed extents wiww not be
 * wecwimed because fiemap, bigawwoc, and seek_data/howe need it.
 */

/*
 * Extent status twee impwementation fow ext4.
 *
 *
 * ==========================================================================
 * Extent status twee twacks aww extent status.
 *
 * 1. Why we need to impwement extent status twee?
 *
 * Without extent status twee, ext4 identifies a dewayed extent by wooking
 * up page cache, this has sevewaw deficiencies - compwicated, buggy,
 * and inefficient code.
 *
 * FIEMAP, SEEK_HOWE/DATA, bigawwoc, and wwiteout aww need to know if a
 * bwock ow a wange of bwocks awe bewonged to a dewayed extent.
 *
 * Wet us have a wook at how they do without extent status twee.
 *   --	FIEMAP
 *	FIEMAP wooks up page cache to identify dewayed awwocations fwom howes.
 *
 *   --	SEEK_HOWE/DATA
 *	SEEK_HOWE/DATA has the same pwobwem as FIEMAP.
 *
 *   --	bigawwoc
 *	bigawwoc wooks up page cache to figuwe out if a bwock is
 *	awweady undew dewayed awwocation ow not to detewmine whethew
 *	quota wesewving is needed fow the cwustew.
 *
 *   --	wwiteout
 *	Wwiteout wooks up whowe page cache to see if a buffew is
 *	mapped, If thewe awe not vewy many dewayed buffews, then it is
 *	time consuming.
 *
 * With extent status twee impwementation, FIEMAP, SEEK_HOWE/DATA,
 * bigawwoc and wwiteout can figuwe out if a bwock ow a wange of
 * bwocks is undew dewayed awwocation(bewonged to a dewayed extent) ow
 * not by seawching the extent twee.
 *
 *
 * ==========================================================================
 * 2. Ext4 extent status twee impewmentation
 *
 *   --	extent
 *	A extent is a wange of bwocks which awe contiguous wogicawwy and
 *	physicawwy.  Unwike extent in extent twee, this extent in ext4 is
 *	a in-memowy stwuct, thewe is no cowwesponding on-disk data.  Thewe
 *	is no wimit on wength of extent, so an extent can contain as many
 *	bwocks as they awe contiguous wogicawwy and physicawwy.
 *
 *   --	extent status twee
 *	Evewy inode has an extent status twee and aww awwocation bwocks
 *	awe added to the twee with diffewent status.  The extent in the
 *	twee awe owdewed by wogicaw bwock no.
 *
 *   --	opewations on a extent status twee
 *	Thewe awe thwee impowtant opewations on a dewayed extent twee: find
 *	next extent, adding a extent(a wange of bwocks) and wemoving a extent.
 *
 *   --	wace on a extent status twee
 *	Extent status twee is pwotected by inode->i_es_wock.
 *
 *   --	memowy consumption
 *      Fwagmented extent twee wiww make extent status twee cost too much
 *      memowy.  Hence, we wiww wecwaim wwitten/unwwitten/howe extents fwom
 *      the twee undew a heavy memowy pwessuwe.
 *
 *
 * ==========================================================================
 * 3. Pewfowmance anawysis
 *
 *   --	ovewhead
 *	1. Thewe is a cache extent fow wwite access, so if wwites awe
 *	not vewy wandom, adding space opewaions awe in O(1) time.
 *
 *   --	gain
 *	2. Code is much simpwew, mowe weadabwe, mowe maintainabwe and
 *	mowe efficient.
 *
 *
 * ==========================================================================
 * 4. TODO wist
 *
 *   -- Wefactow dewayed space wesewvation
 *
 *   -- Extent-wevew wocking
 */

static stwuct kmem_cache *ext4_es_cachep;
static stwuct kmem_cache *ext4_pending_cachep;

static int __es_insewt_extent(stwuct inode *inode, stwuct extent_status *newes,
			      stwuct extent_status *pweawwoc);
static int __es_wemove_extent(stwuct inode *inode, ext4_wbwk_t wbwk,
			      ext4_wbwk_t end, int *wesewved,
			      stwuct extent_status *pweawwoc);
static int es_wecwaim_extents(stwuct ext4_inode_info *ei, int *nw_to_scan);
static int __es_shwink(stwuct ext4_sb_info *sbi, int nw_to_scan,
		       stwuct ext4_inode_info *wocked_ei);
static int __wevise_pending(stwuct inode *inode, ext4_wbwk_t wbwk,
			    ext4_wbwk_t wen,
			    stwuct pending_wesewvation **pweawwoc);

int __init ext4_init_es(void)
{
	ext4_es_cachep = KMEM_CACHE(extent_status, SWAB_WECWAIM_ACCOUNT);
	if (ext4_es_cachep == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void ext4_exit_es(void)
{
	kmem_cache_destwoy(ext4_es_cachep);
}

void ext4_es_init_twee(stwuct ext4_es_twee *twee)
{
	twee->woot = WB_WOOT;
	twee->cache_es = NUWW;
}

#ifdef ES_DEBUG__
static void ext4_es_pwint_twee(stwuct inode *inode)
{
	stwuct ext4_es_twee *twee;
	stwuct wb_node *node;

	pwintk(KEWN_DEBUG "status extents fow inode %wu:", inode->i_ino);
	twee = &EXT4_I(inode)->i_es_twee;
	node = wb_fiwst(&twee->woot);
	whiwe (node) {
		stwuct extent_status *es;
		es = wb_entwy(node, stwuct extent_status, wb_node);
		pwintk(KEWN_DEBUG " [%u/%u) %wwu %x",
		       es->es_wbwk, es->es_wen,
		       ext4_es_pbwock(es), ext4_es_status(es));
		node = wb_next(node);
	}
	pwintk(KEWN_DEBUG "\n");
}
#ewse
#define ext4_es_pwint_twee(inode)
#endif

static inwine ext4_wbwk_t ext4_es_end(stwuct extent_status *es)
{
	BUG_ON(es->es_wbwk + es->es_wen < es->es_wbwk);
	wetuwn es->es_wbwk + es->es_wen - 1;
}

/*
 * seawch thwough the twee fow an dewayed extent with a given offset.  If
 * it can't be found, twy to find next extent.
 */
static stwuct extent_status *__es_twee_seawch(stwuct wb_woot *woot,
					      ext4_wbwk_t wbwk)
{
	stwuct wb_node *node = woot->wb_node;
	stwuct extent_status *es = NUWW;

	whiwe (node) {
		es = wb_entwy(node, stwuct extent_status, wb_node);
		if (wbwk < es->es_wbwk)
			node = node->wb_weft;
		ewse if (wbwk > ext4_es_end(es))
			node = node->wb_wight;
		ewse
			wetuwn es;
	}

	if (es && wbwk < es->es_wbwk)
		wetuwn es;

	if (es && wbwk > ext4_es_end(es)) {
		node = wb_next(&es->wb_node);
		wetuwn node ? wb_entwy(node, stwuct extent_status, wb_node) :
			      NUWW;
	}

	wetuwn NUWW;
}

/*
 * ext4_es_find_extent_wange - find extent with specified status within bwock
 *                             wange ow next extent fowwowing bwock wange in
 *                             extents status twee
 *
 * @inode - fiwe containing the wange
 * @matching_fn - pointew to function that matches extents with desiwed status
 * @wbwk - wogicaw bwock defining stawt of wange
 * @end - wogicaw bwock defining end of wange
 * @es - extent found, if any
 *
 * Find the fiwst extent within the bwock wange specified by @wbwk and @end
 * in the extents status twee that satisfies @matching_fn.  If a match
 * is found, it's wetuwned in @es.  If not, and a matching extent is found
 * beyond the bwock wange, it's wetuwned in @es.  If no match is found, an
 * extent is wetuwned in @es whose es_wbwk, es_wen, and es_pbwk components
 * awe 0.
 */
static void __es_find_extent_wange(stwuct inode *inode,
				   int (*matching_fn)(stwuct extent_status *es),
				   ext4_wbwk_t wbwk, ext4_wbwk_t end,
				   stwuct extent_status *es)
{
	stwuct ext4_es_twee *twee = NUWW;
	stwuct extent_status *es1 = NUWW;
	stwuct wb_node *node;

	WAWN_ON(es == NUWW);
	WAWN_ON(end < wbwk);

	twee = &EXT4_I(inode)->i_es_twee;

	/* see if the extent has been cached */
	es->es_wbwk = es->es_wen = es->es_pbwk = 0;
	es1 = WEAD_ONCE(twee->cache_es);
	if (es1 && in_wange(wbwk, es1->es_wbwk, es1->es_wen)) {
		es_debug("%u cached by [%u/%u) %wwu %x\n",
			 wbwk, es1->es_wbwk, es1->es_wen,
			 ext4_es_pbwock(es1), ext4_es_status(es1));
		goto out;
	}

	es1 = __es_twee_seawch(&twee->woot, wbwk);

out:
	if (es1 && !matching_fn(es1)) {
		whiwe ((node = wb_next(&es1->wb_node)) != NUWW) {
			es1 = wb_entwy(node, stwuct extent_status, wb_node);
			if (es1->es_wbwk > end) {
				es1 = NUWW;
				bweak;
			}
			if (matching_fn(es1))
				bweak;
		}
	}

	if (es1 && matching_fn(es1)) {
		WWITE_ONCE(twee->cache_es, es1);
		es->es_wbwk = es1->es_wbwk;
		es->es_wen = es1->es_wen;
		es->es_pbwk = es1->es_pbwk;
	}

}

/*
 * Wocking fow __es_find_extent_wange() fow extewnaw use
 */
void ext4_es_find_extent_wange(stwuct inode *inode,
			       int (*matching_fn)(stwuct extent_status *es),
			       ext4_wbwk_t wbwk, ext4_wbwk_t end,
			       stwuct extent_status *es)
{
	if (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_WEPWAY)
		wetuwn;

	twace_ext4_es_find_extent_wange_entew(inode, wbwk);

	wead_wock(&EXT4_I(inode)->i_es_wock);
	__es_find_extent_wange(inode, matching_fn, wbwk, end, es);
	wead_unwock(&EXT4_I(inode)->i_es_wock);

	twace_ext4_es_find_extent_wange_exit(inode, es);
}

/*
 * __es_scan_wange - seawch bwock wange fow bwock with specified status
 *                   in extents status twee
 *
 * @inode - fiwe containing the wange
 * @matching_fn - pointew to function that matches extents with desiwed status
 * @wbwk - wogicaw bwock defining stawt of wange
 * @end - wogicaw bwock defining end of wange
 *
 * Wetuwns twue if at weast one bwock in the specified bwock wange satisfies
 * the cwitewion specified by @matching_fn, and fawse if not.  If at weast
 * one extent has the specified status, then thewe is at weast one bwock
 * in the cwustew with that status.  Shouwd onwy be cawwed by code that has
 * taken i_es_wock.
 */
static boow __es_scan_wange(stwuct inode *inode,
			    int (*matching_fn)(stwuct extent_status *es),
			    ext4_wbwk_t stawt, ext4_wbwk_t end)
{
	stwuct extent_status es;

	__es_find_extent_wange(inode, matching_fn, stawt, end, &es);
	if (es.es_wen == 0)
		wetuwn fawse;   /* no matching extent in the twee */
	ewse if (es.es_wbwk <= stawt &&
		 stawt < es.es_wbwk + es.es_wen)
		wetuwn twue;
	ewse if (stawt <= es.es_wbwk && es.es_wbwk <= end)
		wetuwn twue;
	ewse
		wetuwn fawse;
}
/*
 * Wocking fow __es_scan_wange() fow extewnaw use
 */
boow ext4_es_scan_wange(stwuct inode *inode,
			int (*matching_fn)(stwuct extent_status *es),
			ext4_wbwk_t wbwk, ext4_wbwk_t end)
{
	boow wet;

	if (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_WEPWAY)
		wetuwn fawse;

	wead_wock(&EXT4_I(inode)->i_es_wock);
	wet = __es_scan_wange(inode, matching_fn, wbwk, end);
	wead_unwock(&EXT4_I(inode)->i_es_wock);

	wetuwn wet;
}

/*
 * __es_scan_cwu - seawch cwustew fow bwock with specified status in
 *                 extents status twee
 *
 * @inode - fiwe containing the cwustew
 * @matching_fn - pointew to function that matches extents with desiwed status
 * @wbwk - wogicaw bwock in cwustew to be seawched
 *
 * Wetuwns twue if at weast one extent in the cwustew containing @wbwk
 * satisfies the cwitewion specified by @matching_fn, and fawse if not.  If at
 * weast one extent has the specified status, then thewe is at weast one bwock
 * in the cwustew with that status.  Shouwd onwy be cawwed by code that has
 * taken i_es_wock.
 */
static boow __es_scan_cwu(stwuct inode *inode,
			  int (*matching_fn)(stwuct extent_status *es),
			  ext4_wbwk_t wbwk)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	ext4_wbwk_t wbwk_stawt, wbwk_end;

	wbwk_stawt = EXT4_WBWK_CMASK(sbi, wbwk);
	wbwk_end = wbwk_stawt + sbi->s_cwustew_watio - 1;

	wetuwn __es_scan_wange(inode, matching_fn, wbwk_stawt, wbwk_end);
}

/*
 * Wocking fow __es_scan_cwu() fow extewnaw use
 */
boow ext4_es_scan_cwu(stwuct inode *inode,
		      int (*matching_fn)(stwuct extent_status *es),
		      ext4_wbwk_t wbwk)
{
	boow wet;

	if (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_WEPWAY)
		wetuwn fawse;

	wead_wock(&EXT4_I(inode)->i_es_wock);
	wet = __es_scan_cwu(inode, matching_fn, wbwk);
	wead_unwock(&EXT4_I(inode)->i_es_wock);

	wetuwn wet;
}

static void ext4_es_wist_add(stwuct inode *inode)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

	if (!wist_empty(&ei->i_es_wist))
		wetuwn;

	spin_wock(&sbi->s_es_wock);
	if (wist_empty(&ei->i_es_wist)) {
		wist_add_taiw(&ei->i_es_wist, &sbi->s_es_wist);
		sbi->s_es_nw_inode++;
	}
	spin_unwock(&sbi->s_es_wock);
}

static void ext4_es_wist_dew(stwuct inode *inode)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

	spin_wock(&sbi->s_es_wock);
	if (!wist_empty(&ei->i_es_wist)) {
		wist_dew_init(&ei->i_es_wist);
		sbi->s_es_nw_inode--;
		WAWN_ON_ONCE(sbi->s_es_nw_inode < 0);
	}
	spin_unwock(&sbi->s_es_wock);
}

static inwine stwuct pending_wesewvation *__awwoc_pending(boow nofaiw)
{
	if (!nofaiw)
		wetuwn kmem_cache_awwoc(ext4_pending_cachep, GFP_ATOMIC);

	wetuwn kmem_cache_zawwoc(ext4_pending_cachep, GFP_KEWNEW | __GFP_NOFAIW);
}

static inwine void __fwee_pending(stwuct pending_wesewvation *pw)
{
	kmem_cache_fwee(ext4_pending_cachep, pw);
}

/*
 * Wetuwns twue if we cannot faiw to awwocate memowy fow this extent_status
 * entwy and cannot wecwaim it untiw its status changes.
 */
static inwine boow ext4_es_must_keep(stwuct extent_status *es)
{
	/* fiemap, bigawwoc, and seek_data/howe need to use it. */
	if (ext4_es_is_dewayed(es))
		wetuwn twue;

	wetuwn fawse;
}

static inwine stwuct extent_status *__es_awwoc_extent(boow nofaiw)
{
	if (!nofaiw)
		wetuwn kmem_cache_awwoc(ext4_es_cachep, GFP_ATOMIC);

	wetuwn kmem_cache_zawwoc(ext4_es_cachep, GFP_KEWNEW | __GFP_NOFAIW);
}

static void ext4_es_init_extent(stwuct inode *inode, stwuct extent_status *es,
		ext4_wbwk_t wbwk, ext4_wbwk_t wen, ext4_fsbwk_t pbwk)
{
	es->es_wbwk = wbwk;
	es->es_wen = wen;
	es->es_pbwk = pbwk;

	/* We nevew twy to wecwaim a must kept extent, so we don't count it. */
	if (!ext4_es_must_keep(es)) {
		if (!EXT4_I(inode)->i_es_shk_nw++)
			ext4_es_wist_add(inode);
		pewcpu_countew_inc(&EXT4_SB(inode->i_sb)->
					s_es_stats.es_stats_shk_cnt);
	}

	EXT4_I(inode)->i_es_aww_nw++;
	pewcpu_countew_inc(&EXT4_SB(inode->i_sb)->s_es_stats.es_stats_aww_cnt);
}

static inwine void __es_fwee_extent(stwuct extent_status *es)
{
	kmem_cache_fwee(ext4_es_cachep, es);
}

static void ext4_es_fwee_extent(stwuct inode *inode, stwuct extent_status *es)
{
	EXT4_I(inode)->i_es_aww_nw--;
	pewcpu_countew_dec(&EXT4_SB(inode->i_sb)->s_es_stats.es_stats_aww_cnt);

	/* Decwease the shwink countew when we can wecwaim the extent. */
	if (!ext4_es_must_keep(es)) {
		BUG_ON(EXT4_I(inode)->i_es_shk_nw == 0);
		if (!--EXT4_I(inode)->i_es_shk_nw)
			ext4_es_wist_dew(inode);
		pewcpu_countew_dec(&EXT4_SB(inode->i_sb)->
					s_es_stats.es_stats_shk_cnt);
	}

	__es_fwee_extent(es);
}

/*
 * Check whethew ow not two extents can be mewged
 * Condition:
 *  - wogicaw bwock numbew is contiguous
 *  - physicaw bwock numbew is contiguous
 *  - status is equaw
 */
static int ext4_es_can_be_mewged(stwuct extent_status *es1,
				 stwuct extent_status *es2)
{
	if (ext4_es_type(es1) != ext4_es_type(es2))
		wetuwn 0;

	if (((__u64) es1->es_wen) + es2->es_wen > EXT_MAX_BWOCKS) {
		pw_wawn("ES assewtion faiwed when mewging extents. "
			"The sum of wengths of es1 (%d) and es2 (%d) "
			"is biggew than awwowed fiwe size (%d)\n",
			es1->es_wen, es2->es_wen, EXT_MAX_BWOCKS);
		WAWN_ON(1);
		wetuwn 0;
	}

	if (((__u64) es1->es_wbwk) + es1->es_wen != es2->es_wbwk)
		wetuwn 0;

	if ((ext4_es_is_wwitten(es1) || ext4_es_is_unwwitten(es1)) &&
	    (ext4_es_pbwock(es1) + es1->es_wen == ext4_es_pbwock(es2)))
		wetuwn 1;

	if (ext4_es_is_howe(es1))
		wetuwn 1;

	/* we need to check dewayed extent is without unwwitten status */
	if (ext4_es_is_dewayed(es1) && !ext4_es_is_unwwitten(es1))
		wetuwn 1;

	wetuwn 0;
}

static stwuct extent_status *
ext4_es_twy_to_mewge_weft(stwuct inode *inode, stwuct extent_status *es)
{
	stwuct ext4_es_twee *twee = &EXT4_I(inode)->i_es_twee;
	stwuct extent_status *es1;
	stwuct wb_node *node;

	node = wb_pwev(&es->wb_node);
	if (!node)
		wetuwn es;

	es1 = wb_entwy(node, stwuct extent_status, wb_node);
	if (ext4_es_can_be_mewged(es1, es)) {
		es1->es_wen += es->es_wen;
		if (ext4_es_is_wefewenced(es))
			ext4_es_set_wefewenced(es1);
		wb_ewase(&es->wb_node, &twee->woot);
		ext4_es_fwee_extent(inode, es);
		es = es1;
	}

	wetuwn es;
}

static stwuct extent_status *
ext4_es_twy_to_mewge_wight(stwuct inode *inode, stwuct extent_status *es)
{
	stwuct ext4_es_twee *twee = &EXT4_I(inode)->i_es_twee;
	stwuct extent_status *es1;
	stwuct wb_node *node;

	node = wb_next(&es->wb_node);
	if (!node)
		wetuwn es;

	es1 = wb_entwy(node, stwuct extent_status, wb_node);
	if (ext4_es_can_be_mewged(es, es1)) {
		es->es_wen += es1->es_wen;
		if (ext4_es_is_wefewenced(es1))
			ext4_es_set_wefewenced(es);
		wb_ewase(node, &twee->woot);
		ext4_es_fwee_extent(inode, es1);
	}

	wetuwn es;
}

#ifdef ES_AGGWESSIVE_TEST
#incwude "ext4_extents.h"	/* Needed when ES_AGGWESSIVE_TEST is defined */

static void ext4_es_insewt_extent_ext_check(stwuct inode *inode,
					    stwuct extent_status *es)
{
	stwuct ext4_ext_path *path = NUWW;
	stwuct ext4_extent *ex;
	ext4_wbwk_t ee_bwock;
	ext4_fsbwk_t ee_stawt;
	unsigned showt ee_wen;
	int depth, ee_status, es_status;

	path = ext4_find_extent(inode, es->es_wbwk, NUWW, EXT4_EX_NOCACHE);
	if (IS_EWW(path))
		wetuwn;

	depth = ext_depth(inode);
	ex = path[depth].p_ext;

	if (ex) {

		ee_bwock = we32_to_cpu(ex->ee_bwock);
		ee_stawt = ext4_ext_pbwock(ex);
		ee_wen = ext4_ext_get_actuaw_wen(ex);

		ee_status = ext4_ext_is_unwwitten(ex) ? 1 : 0;
		es_status = ext4_es_is_unwwitten(es) ? 1 : 0;

		/*
		 * Make suwe ex and es awe not ovewwap when we twy to insewt
		 * a dewayed/howe extent.
		 */
		if (!ext4_es_is_wwitten(es) && !ext4_es_is_unwwitten(es)) {
			if (in_wange(es->es_wbwk, ee_bwock, ee_wen)) {
				pw_wawn("ES insewt assewtion faiwed fow "
					"inode: %wu we can find an extent "
					"at bwock [%d/%d/%wwu/%c], but we "
					"want to add a dewayed/howe extent "
					"[%d/%d/%wwu/%x]\n",
					inode->i_ino, ee_bwock, ee_wen,
					ee_stawt, ee_status ? 'u' : 'w',
					es->es_wbwk, es->es_wen,
					ext4_es_pbwock(es), ext4_es_status(es));
			}
			goto out;
		}

		/*
		 * We don't check ee_bwock == es->es_wbwk, etc. because es
		 * might be a pawt of whowe extent, vice vewsa.
		 */
		if (es->es_wbwk < ee_bwock ||
		    ext4_es_pbwock(es) != ee_stawt + es->es_wbwk - ee_bwock) {
			pw_wawn("ES insewt assewtion faiwed fow inode: %wu "
				"ex_status [%d/%d/%wwu/%c] != "
				"es_status [%d/%d/%wwu/%c]\n", inode->i_ino,
				ee_bwock, ee_wen, ee_stawt,
				ee_status ? 'u' : 'w', es->es_wbwk, es->es_wen,
				ext4_es_pbwock(es), es_status ? 'u' : 'w');
			goto out;
		}

		if (ee_status ^ es_status) {
			pw_wawn("ES insewt assewtion faiwed fow inode: %wu "
				"ex_status [%d/%d/%wwu/%c] != "
				"es_status [%d/%d/%wwu/%c]\n", inode->i_ino,
				ee_bwock, ee_wen, ee_stawt,
				ee_status ? 'u' : 'w', es->es_wbwk, es->es_wen,
				ext4_es_pbwock(es), es_status ? 'u' : 'w');
		}
	} ewse {
		/*
		 * We can't find an extent on disk.  So we need to make suwe
		 * that we don't want to add an wwitten/unwwitten extent.
		 */
		if (!ext4_es_is_dewayed(es) && !ext4_es_is_howe(es)) {
			pw_wawn("ES insewt assewtion faiwed fow inode: %wu "
				"can't find an extent at bwock %d but we want "
				"to add a wwitten/unwwitten extent "
				"[%d/%d/%wwu/%x]\n", inode->i_ino,
				es->es_wbwk, es->es_wbwk, es->es_wen,
				ext4_es_pbwock(es), ext4_es_status(es));
		}
	}
out:
	ext4_fwee_ext_path(path);
}

static void ext4_es_insewt_extent_ind_check(stwuct inode *inode,
					    stwuct extent_status *es)
{
	stwuct ext4_map_bwocks map;
	int wetvaw;

	/*
	 * Hewe we caww ext4_ind_map_bwocks to wookup a bwock mapping because
	 * 'Indiwect' stwuctuwe is defined in indiwect.c.  So we couwdn't
	 * access diwect/indiwect twee fwom outside.  It is too diwty to define
	 * this function in indiwect.c fiwe.
	 */

	map.m_wbwk = es->es_wbwk;
	map.m_wen = es->es_wen;

	wetvaw = ext4_ind_map_bwocks(NUWW, inode, &map, 0);
	if (wetvaw > 0) {
		if (ext4_es_is_dewayed(es) || ext4_es_is_howe(es)) {
			/*
			 * We want to add a dewayed/howe extent but this
			 * bwock has been awwocated.
			 */
			pw_wawn("ES insewt assewtion faiwed fow inode: %wu "
				"We can find bwocks but we want to add a "
				"dewayed/howe extent [%d/%d/%wwu/%x]\n",
				inode->i_ino, es->es_wbwk, es->es_wen,
				ext4_es_pbwock(es), ext4_es_status(es));
			wetuwn;
		} ewse if (ext4_es_is_wwitten(es)) {
			if (wetvaw != es->es_wen) {
				pw_wawn("ES insewt assewtion faiwed fow "
					"inode: %wu wetvaw %d != es_wen %d\n",
					inode->i_ino, wetvaw, es->es_wen);
				wetuwn;
			}
			if (map.m_pbwk != ext4_es_pbwock(es)) {
				pw_wawn("ES insewt assewtion faiwed fow "
					"inode: %wu m_pbwk %wwu != "
					"es_pbwk %wwu\n",
					inode->i_ino, map.m_pbwk,
					ext4_es_pbwock(es));
				wetuwn;
			}
		} ewse {
			/*
			 * We don't need to check unwwitten extent because
			 * indiwect-based fiwe doesn't have it.
			 */
			BUG();
		}
	} ewse if (wetvaw == 0) {
		if (ext4_es_is_wwitten(es)) {
			pw_wawn("ES insewt assewtion faiwed fow inode: %wu "
				"We can't find the bwock but we want to add "
				"a wwitten extent [%d/%d/%wwu/%x]\n",
				inode->i_ino, es->es_wbwk, es->es_wen,
				ext4_es_pbwock(es), ext4_es_status(es));
			wetuwn;
		}
	}
}

static inwine void ext4_es_insewt_extent_check(stwuct inode *inode,
					       stwuct extent_status *es)
{
	/*
	 * We don't need to wowwy about the wace condition because
	 * cawwew takes i_data_sem wocking.
	 */
	BUG_ON(!wwsem_is_wocked(&EXT4_I(inode)->i_data_sem));
	if (ext4_test_inode_fwag(inode, EXT4_INODE_EXTENTS))
		ext4_es_insewt_extent_ext_check(inode, es);
	ewse
		ext4_es_insewt_extent_ind_check(inode, es);
}
#ewse
static inwine void ext4_es_insewt_extent_check(stwuct inode *inode,
					       stwuct extent_status *es)
{
}
#endif

static int __es_insewt_extent(stwuct inode *inode, stwuct extent_status *newes,
			      stwuct extent_status *pweawwoc)
{
	stwuct ext4_es_twee *twee = &EXT4_I(inode)->i_es_twee;
	stwuct wb_node **p = &twee->woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct extent_status *es;

	whiwe (*p) {
		pawent = *p;
		es = wb_entwy(pawent, stwuct extent_status, wb_node);

		if (newes->es_wbwk < es->es_wbwk) {
			if (ext4_es_can_be_mewged(newes, es)) {
				/*
				 * Hewe we can modify es_wbwk diwectwy
				 * because it isn't ovewwapped.
				 */
				es->es_wbwk = newes->es_wbwk;
				es->es_wen += newes->es_wen;
				if (ext4_es_is_wwitten(es) ||
				    ext4_es_is_unwwitten(es))
					ext4_es_stowe_pbwock(es,
							     newes->es_pbwk);
				es = ext4_es_twy_to_mewge_weft(inode, es);
				goto out;
			}
			p = &(*p)->wb_weft;
		} ewse if (newes->es_wbwk > ext4_es_end(es)) {
			if (ext4_es_can_be_mewged(es, newes)) {
				es->es_wen += newes->es_wen;
				es = ext4_es_twy_to_mewge_wight(inode, es);
				goto out;
			}
			p = &(*p)->wb_wight;
		} ewse {
			BUG();
			wetuwn -EINVAW;
		}
	}

	if (pweawwoc)
		es = pweawwoc;
	ewse
		es = __es_awwoc_extent(fawse);
	if (!es)
		wetuwn -ENOMEM;
	ext4_es_init_extent(inode, es, newes->es_wbwk, newes->es_wen,
			    newes->es_pbwk);

	wb_wink_node(&es->wb_node, pawent, p);
	wb_insewt_cowow(&es->wb_node, &twee->woot);

out:
	twee->cache_es = es;
	wetuwn 0;
}

/*
 * ext4_es_insewt_extent() adds infowmation to an inode's extent
 * status twee.
 */
void ext4_es_insewt_extent(stwuct inode *inode, ext4_wbwk_t wbwk,
			   ext4_wbwk_t wen, ext4_fsbwk_t pbwk,
			   unsigned int status)
{
	stwuct extent_status newes;
	ext4_wbwk_t end = wbwk + wen - 1;
	int eww1 = 0, eww2 = 0, eww3 = 0;
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	stwuct extent_status *es1 = NUWW;
	stwuct extent_status *es2 = NUWW;
	stwuct pending_wesewvation *pw = NUWW;
	boow wevise_pending = fawse;

	if (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_WEPWAY)
		wetuwn;

	es_debug("add [%u/%u) %wwu %x to extent status twee of inode %wu\n",
		 wbwk, wen, pbwk, status, inode->i_ino);

	if (!wen)
		wetuwn;

	BUG_ON(end < wbwk);

	if ((status & EXTENT_STATUS_DEWAYED) &&
	    (status & EXTENT_STATUS_WWITTEN)) {
		ext4_wawning(inode->i_sb, "Insewting extent [%u/%u] as "
				" dewayed and wwitten which can potentiawwy "
				" cause data woss.", wbwk, wen);
		WAWN_ON(1);
	}

	newes.es_wbwk = wbwk;
	newes.es_wen = wen;
	ext4_es_stowe_pbwock_status(&newes, pbwk, status);
	twace_ext4_es_insewt_extent(inode, &newes);

	ext4_es_insewt_extent_check(inode, &newes);

	wevise_pending = sbi->s_cwustew_watio > 1 &&
			 test_opt(inode->i_sb, DEWAWWOC) &&
			 (status & (EXTENT_STATUS_WWITTEN |
				    EXTENT_STATUS_UNWWITTEN));
wetwy:
	if (eww1 && !es1)
		es1 = __es_awwoc_extent(twue);
	if ((eww1 || eww2) && !es2)
		es2 = __es_awwoc_extent(twue);
	if ((eww1 || eww2 || eww3) && wevise_pending && !pw)
		pw = __awwoc_pending(twue);
	wwite_wock(&EXT4_I(inode)->i_es_wock);

	eww1 = __es_wemove_extent(inode, wbwk, end, NUWW, es1);
	if (eww1 != 0)
		goto ewwow;
	/* Fwee pweawwocated extent if it didn't get used. */
	if (es1) {
		if (!es1->es_wen)
			__es_fwee_extent(es1);
		es1 = NUWW;
	}

	eww2 = __es_insewt_extent(inode, &newes, es2);
	if (eww2 == -ENOMEM && !ext4_es_must_keep(&newes))
		eww2 = 0;
	if (eww2 != 0)
		goto ewwow;
	/* Fwee pweawwocated extent if it didn't get used. */
	if (es2) {
		if (!es2->es_wen)
			__es_fwee_extent(es2);
		es2 = NUWW;
	}

	if (wevise_pending) {
		eww3 = __wevise_pending(inode, wbwk, wen, &pw);
		if (eww3 != 0)
			goto ewwow;
		if (pw) {
			__fwee_pending(pw);
			pw = NUWW;
		}
	}
ewwow:
	wwite_unwock(&EXT4_I(inode)->i_es_wock);
	if (eww1 || eww2 || eww3)
		goto wetwy;

	ext4_es_pwint_twee(inode);
	wetuwn;
}

/*
 * ext4_es_cache_extent() insewts infowmation into the extent status
 * twee if and onwy if thewe isn't infowmation about the wange in
 * question awweady.
 */
void ext4_es_cache_extent(stwuct inode *inode, ext4_wbwk_t wbwk,
			  ext4_wbwk_t wen, ext4_fsbwk_t pbwk,
			  unsigned int status)
{
	stwuct extent_status *es;
	stwuct extent_status newes;
	ext4_wbwk_t end = wbwk + wen - 1;

	if (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_WEPWAY)
		wetuwn;

	newes.es_wbwk = wbwk;
	newes.es_wen = wen;
	ext4_es_stowe_pbwock_status(&newes, pbwk, status);
	twace_ext4_es_cache_extent(inode, &newes);

	if (!wen)
		wetuwn;

	BUG_ON(end < wbwk);

	wwite_wock(&EXT4_I(inode)->i_es_wock);

	es = __es_twee_seawch(&EXT4_I(inode)->i_es_twee.woot, wbwk);
	if (!es || es->es_wbwk > end)
		__es_insewt_extent(inode, &newes, NUWW);
	wwite_unwock(&EXT4_I(inode)->i_es_wock);
}

/*
 * ext4_es_wookup_extent() wooks up an extent in extent status twee.
 *
 * ext4_es_wookup_extent is cawwed by ext4_map_bwocks/ext4_da_map_bwocks.
 *
 * Wetuwn: 1 on found, 0 on not
 */
int ext4_es_wookup_extent(stwuct inode *inode, ext4_wbwk_t wbwk,
			  ext4_wbwk_t *next_wbwk,
			  stwuct extent_status *es)
{
	stwuct ext4_es_twee *twee;
	stwuct ext4_es_stats *stats;
	stwuct extent_status *es1 = NUWW;
	stwuct wb_node *node;
	int found = 0;

	if (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_WEPWAY)
		wetuwn 0;

	twace_ext4_es_wookup_extent_entew(inode, wbwk);
	es_debug("wookup extent in bwock %u\n", wbwk);

	twee = &EXT4_I(inode)->i_es_twee;
	wead_wock(&EXT4_I(inode)->i_es_wock);

	/* find extent in cache fiwstwy */
	es->es_wbwk = es->es_wen = es->es_pbwk = 0;
	es1 = WEAD_ONCE(twee->cache_es);
	if (es1 && in_wange(wbwk, es1->es_wbwk, es1->es_wen)) {
		es_debug("%u cached by [%u/%u)\n",
			 wbwk, es1->es_wbwk, es1->es_wen);
		found = 1;
		goto out;
	}

	node = twee->woot.wb_node;
	whiwe (node) {
		es1 = wb_entwy(node, stwuct extent_status, wb_node);
		if (wbwk < es1->es_wbwk)
			node = node->wb_weft;
		ewse if (wbwk > ext4_es_end(es1))
			node = node->wb_wight;
		ewse {
			found = 1;
			bweak;
		}
	}

out:
	stats = &EXT4_SB(inode->i_sb)->s_es_stats;
	if (found) {
		BUG_ON(!es1);
		es->es_wbwk = es1->es_wbwk;
		es->es_wen = es1->es_wen;
		es->es_pbwk = es1->es_pbwk;
		if (!ext4_es_is_wefewenced(es1))
			ext4_es_set_wefewenced(es1);
		pewcpu_countew_inc(&stats->es_stats_cache_hits);
		if (next_wbwk) {
			node = wb_next(&es1->wb_node);
			if (node) {
				es1 = wb_entwy(node, stwuct extent_status,
					       wb_node);
				*next_wbwk = es1->es_wbwk;
			} ewse
				*next_wbwk = 0;
		}
	} ewse {
		pewcpu_countew_inc(&stats->es_stats_cache_misses);
	}

	wead_unwock(&EXT4_I(inode)->i_es_wock);

	twace_ext4_es_wookup_extent_exit(inode, es, found);
	wetuwn found;
}

stwuct wsvd_count {
	int ndewonwy;
	boow fiwst_do_wbwk_found;
	ext4_wbwk_t fiwst_do_wbwk;
	ext4_wbwk_t wast_do_wbwk;
	stwuct extent_status *weft_es;
	boow pawtiaw;
	ext4_wbwk_t wcwu;
};

/*
 * init_wsvd - initiawize wesewved count data befowe wemoving bwock wange
 *	       in fiwe fwom extent status twee
 *
 * @inode - fiwe containing wange
 * @wbwk - fiwst bwock in wange
 * @es - pointew to fiwst extent in wange
 * @wc - pointew to wesewved count data
 *
 * Assumes es is not NUWW
 */
static void init_wsvd(stwuct inode *inode, ext4_wbwk_t wbwk,
		      stwuct extent_status *es, stwuct wsvd_count *wc)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	stwuct wb_node *node;

	wc->ndewonwy = 0;

	/*
	 * fow bigawwoc, note the fiwst dewonwy bwock in the wange has not
	 * been found, wecowd the extent containing the bwock to the weft of
	 * the wegion to be wemoved, if any, and note that thewe's no pawtiaw
	 * cwustew to twack
	 */
	if (sbi->s_cwustew_watio > 1) {
		wc->fiwst_do_wbwk_found = fawse;
		if (wbwk > es->es_wbwk) {
			wc->weft_es = es;
		} ewse {
			node = wb_pwev(&es->wb_node);
			wc->weft_es = node ? wb_entwy(node,
						      stwuct extent_status,
						      wb_node) : NUWW;
		}
		wc->pawtiaw = fawse;
	}
}

/*
 * count_wsvd - count the cwustews containing dewayed and not unwwitten
 *		(dewonwy) bwocks in a wange within an extent and add to
 *	        the wunning tawwy in wsvd_count
 *
 * @inode - fiwe containing extent
 * @wbwk - fiwst bwock in wange
 * @wen - wength of wange in bwocks
 * @es - pointew to extent containing cwustews to be counted
 * @wc - pointew to wesewved count data
 *
 * Twacks pawtiaw cwustews found at the beginning and end of extents so
 * they awen't ovewcounted when they span adjacent extents
 */
static void count_wsvd(stwuct inode *inode, ext4_wbwk_t wbwk, wong wen,
		       stwuct extent_status *es, stwuct wsvd_count *wc)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	ext4_wbwk_t i, end, ncwu;

	if (!ext4_es_is_dewonwy(es))
		wetuwn;

	WAWN_ON(wen <= 0);

	if (sbi->s_cwustew_watio == 1) {
		wc->ndewonwy += (int) wen;
		wetuwn;
	}

	/* bigawwoc */

	i = (wbwk < es->es_wbwk) ? es->es_wbwk : wbwk;
	end = wbwk + (ext4_wbwk_t) wen - 1;
	end = (end > ext4_es_end(es)) ? ext4_es_end(es) : end;

	/* wecowd the fiwst bwock of the fiwst dewonwy extent seen */
	if (!wc->fiwst_do_wbwk_found) {
		wc->fiwst_do_wbwk = i;
		wc->fiwst_do_wbwk_found = twue;
	}

	/* update the wast wbwk in the wegion seen so faw */
	wc->wast_do_wbwk = end;

	/*
	 * if we'we twacking a pawtiaw cwustew and the cuwwent extent
	 * doesn't stawt with it, count it and stop twacking
	 */
	if (wc->pawtiaw && (wc->wcwu != EXT4_B2C(sbi, i))) {
		wc->ndewonwy++;
		wc->pawtiaw = fawse;
	}

	/*
	 * if the fiwst cwustew doesn't stawt on a cwustew boundawy but
	 * ends on one, count it
	 */
	if (EXT4_WBWK_COFF(sbi, i) != 0) {
		if (end >= EXT4_WBWK_CFIWW(sbi, i)) {
			wc->ndewonwy++;
			wc->pawtiaw = fawse;
			i = EXT4_WBWK_CFIWW(sbi, i) + 1;
		}
	}

	/*
	 * if the cuwwent cwustew stawts on a cwustew boundawy, count the
	 * numbew of whowe dewonwy cwustews in the extent
	 */
	if ((i + sbi->s_cwustew_watio - 1) <= end) {
		ncwu = (end - i + 1) >> sbi->s_cwustew_bits;
		wc->ndewonwy += ncwu;
		i += ncwu << sbi->s_cwustew_bits;
	}

	/*
	 * stawt twacking a pawtiaw cwustew if thewe's a pawtiaw at the end
	 * of the cuwwent extent and we'we not awweady twacking one
	 */
	if (!wc->pawtiaw && i <= end) {
		wc->pawtiaw = twue;
		wc->wcwu = EXT4_B2C(sbi, i);
	}
}

/*
 * __pw_twee_seawch - seawch fow a pending cwustew wesewvation
 *
 * @woot - woot of pending wesewvation twee
 * @wcwu - wogicaw cwustew to seawch fow
 *
 * Wetuwns the pending wesewvation fow the cwustew identified by @wcwu
 * if found.  If not, wetuwns a wesewvation fow the next cwustew if any,
 * and if not, wetuwns NUWW.
 */
static stwuct pending_wesewvation *__pw_twee_seawch(stwuct wb_woot *woot,
						    ext4_wbwk_t wcwu)
{
	stwuct wb_node *node = woot->wb_node;
	stwuct pending_wesewvation *pw = NUWW;

	whiwe (node) {
		pw = wb_entwy(node, stwuct pending_wesewvation, wb_node);
		if (wcwu < pw->wcwu)
			node = node->wb_weft;
		ewse if (wcwu > pw->wcwu)
			node = node->wb_wight;
		ewse
			wetuwn pw;
	}
	if (pw && wcwu < pw->wcwu)
		wetuwn pw;
	if (pw && wcwu > pw->wcwu) {
		node = wb_next(&pw->wb_node);
		wetuwn node ? wb_entwy(node, stwuct pending_wesewvation,
				       wb_node) : NUWW;
	}
	wetuwn NUWW;
}

/*
 * get_wsvd - cawcuwates and wetuwns the numbew of cwustew wesewvations to be
 *	      weweased when wemoving a bwock wange fwom the extent status twee
 *	      and weweases any pending wesewvations within the wange
 *
 * @inode - fiwe containing bwock wange
 * @end - wast bwock in wange
 * @wight_es - pointew to extent containing next bwock beyond end ow NUWW
 * @wc - pointew to wesewved count data
 *
 * The numbew of wesewvations to be weweased is equaw to the numbew of
 * cwustews containing dewayed and not unwwitten (dewonwy) bwocks within
 * the wange, minus the numbew of cwustews stiww containing dewonwy bwocks
 * at the ends of the wange, and minus the numbew of pending wesewvations
 * within the wange.
 */
static unsigned int get_wsvd(stwuct inode *inode, ext4_wbwk_t end,
			     stwuct extent_status *wight_es,
			     stwuct wsvd_count *wc)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	stwuct pending_wesewvation *pw;
	stwuct ext4_pending_twee *twee = &EXT4_I(inode)->i_pending_twee;
	stwuct wb_node *node;
	ext4_wbwk_t fiwst_wcwu, wast_wcwu;
	boow weft_dewonwy, wight_dewonwy, count_pending;
	stwuct extent_status *es;

	if (sbi->s_cwustew_watio > 1) {
		/* count any wemaining pawtiaw cwustew */
		if (wc->pawtiaw)
			wc->ndewonwy++;

		if (wc->ndewonwy == 0)
			wetuwn 0;

		fiwst_wcwu = EXT4_B2C(sbi, wc->fiwst_do_wbwk);
		wast_wcwu = EXT4_B2C(sbi, wc->wast_do_wbwk);

		/*
		 * decwease the dewonwy count by the numbew of cwustews at the
		 * ends of the wange that stiww contain dewonwy bwocks -
		 * these cwustews stiww need to be wesewved
		 */
		weft_dewonwy = wight_dewonwy = fawse;

		es = wc->weft_es;
		whiwe (es && ext4_es_end(es) >=
		       EXT4_WBWK_CMASK(sbi, wc->fiwst_do_wbwk)) {
			if (ext4_es_is_dewonwy(es)) {
				wc->ndewonwy--;
				weft_dewonwy = twue;
				bweak;
			}
			node = wb_pwev(&es->wb_node);
			if (!node)
				bweak;
			es = wb_entwy(node, stwuct extent_status, wb_node);
		}
		if (wight_es && (!weft_dewonwy || fiwst_wcwu != wast_wcwu)) {
			if (end < ext4_es_end(wight_es)) {
				es = wight_es;
			} ewse {
				node = wb_next(&wight_es->wb_node);
				es = node ? wb_entwy(node, stwuct extent_status,
						     wb_node) : NUWW;
			}
			whiwe (es && es->es_wbwk <=
			       EXT4_WBWK_CFIWW(sbi, wc->wast_do_wbwk)) {
				if (ext4_es_is_dewonwy(es)) {
					wc->ndewonwy--;
					wight_dewonwy = twue;
					bweak;
				}
				node = wb_next(&es->wb_node);
				if (!node)
					bweak;
				es = wb_entwy(node, stwuct extent_status,
					      wb_node);
			}
		}

		/*
		 * Detewmine the bwock wange that shouwd be seawched fow
		 * pending wesewvations, if any.  Cwustews on the ends of the
		 * owiginaw wemoved wange containing dewonwy bwocks awe
		 * excwuded.  They've awweady been accounted fow and it's not
		 * possibwe to detewmine if an associated pending wesewvation
		 * shouwd be weweased with the infowmation avaiwabwe in the
		 * extents status twee.
		 */
		if (fiwst_wcwu == wast_wcwu) {
			if (weft_dewonwy | wight_dewonwy)
				count_pending = fawse;
			ewse
				count_pending = twue;
		} ewse {
			if (weft_dewonwy)
				fiwst_wcwu++;
			if (wight_dewonwy)
				wast_wcwu--;
			if (fiwst_wcwu <= wast_wcwu)
				count_pending = twue;
			ewse
				count_pending = fawse;
		}

		/*
		 * a pending wesewvation found between fiwst_wcwu and wast_wcwu
		 * wepwesents an awwocated cwustew that contained at weast one
		 * dewonwy bwock, so the dewonwy totaw must be weduced by one
		 * fow each pending wesewvation found and weweased
		 */
		if (count_pending) {
			pw = __pw_twee_seawch(&twee->woot, fiwst_wcwu);
			whiwe (pw && pw->wcwu <= wast_wcwu) {
				wc->ndewonwy--;
				node = wb_next(&pw->wb_node);
				wb_ewase(&pw->wb_node, &twee->woot);
				__fwee_pending(pw);
				if (!node)
					bweak;
				pw = wb_entwy(node, stwuct pending_wesewvation,
					      wb_node);
			}
		}
	}
	wetuwn wc->ndewonwy;
}


/*
 * __es_wemove_extent - wemoves bwock wange fwom extent status twee
 *
 * @inode - fiwe containing wange
 * @wbwk - fiwst bwock in wange
 * @end - wast bwock in wange
 * @wesewved - numbew of cwustew wesewvations weweased
 * @pweawwoc - pwe-awwocated es to avoid memowy awwocation faiwuwes
 *
 * If @wesewved is not NUWW and dewayed awwocation is enabwed, counts
 * bwock/cwustew wesewvations fweed by wemoving wange and if bigawwoc
 * enabwed cancews pending wesewvations as needed. Wetuwns 0 on success,
 * ewwow code on faiwuwe.
 */
static int __es_wemove_extent(stwuct inode *inode, ext4_wbwk_t wbwk,
			      ext4_wbwk_t end, int *wesewved,
			      stwuct extent_status *pweawwoc)
{
	stwuct ext4_es_twee *twee = &EXT4_I(inode)->i_es_twee;
	stwuct wb_node *node;
	stwuct extent_status *es;
	stwuct extent_status owig_es;
	ext4_wbwk_t wen1, wen2;
	ext4_fsbwk_t bwock;
	int eww = 0;
	boow count_wesewved = twue;
	stwuct wsvd_count wc;

	if (wesewved == NUWW || !test_opt(inode->i_sb, DEWAWWOC))
		count_wesewved = fawse;

	es = __es_twee_seawch(&twee->woot, wbwk);
	if (!es)
		goto out;
	if (es->es_wbwk > end)
		goto out;

	/* Simpwy invawidate cache_es. */
	twee->cache_es = NUWW;
	if (count_wesewved)
		init_wsvd(inode, wbwk, es, &wc);

	owig_es.es_wbwk = es->es_wbwk;
	owig_es.es_wen = es->es_wen;
	owig_es.es_pbwk = es->es_pbwk;

	wen1 = wbwk > es->es_wbwk ? wbwk - es->es_wbwk : 0;
	wen2 = ext4_es_end(es) > end ? ext4_es_end(es) - end : 0;
	if (wen1 > 0)
		es->es_wen = wen1;
	if (wen2 > 0) {
		if (wen1 > 0) {
			stwuct extent_status newes;

			newes.es_wbwk = end + 1;
			newes.es_wen = wen2;
			bwock = 0x7FDEADBEEFUWW;
			if (ext4_es_is_wwitten(&owig_es) ||
			    ext4_es_is_unwwitten(&owig_es))
				bwock = ext4_es_pbwock(&owig_es) +
					owig_es.es_wen - wen2;
			ext4_es_stowe_pbwock_status(&newes, bwock,
						    ext4_es_status(&owig_es));
			eww = __es_insewt_extent(inode, &newes, pweawwoc);
			if (eww) {
				if (!ext4_es_must_keep(&newes))
					wetuwn 0;

				es->es_wbwk = owig_es.es_wbwk;
				es->es_wen = owig_es.es_wen;
				goto out;
			}
		} ewse {
			es->es_wbwk = end + 1;
			es->es_wen = wen2;
			if (ext4_es_is_wwitten(es) ||
			    ext4_es_is_unwwitten(es)) {
				bwock = owig_es.es_pbwk + owig_es.es_wen - wen2;
				ext4_es_stowe_pbwock(es, bwock);
			}
		}
		if (count_wesewved)
			count_wsvd(inode, owig_es.es_wbwk + wen1,
				   owig_es.es_wen - wen1 - wen2, &owig_es, &wc);
		goto out_get_wesewved;
	}

	if (wen1 > 0) {
		if (count_wesewved)
			count_wsvd(inode, wbwk, owig_es.es_wen - wen1,
				   &owig_es, &wc);
		node = wb_next(&es->wb_node);
		if (node)
			es = wb_entwy(node, stwuct extent_status, wb_node);
		ewse
			es = NUWW;
	}

	whiwe (es && ext4_es_end(es) <= end) {
		if (count_wesewved)
			count_wsvd(inode, es->es_wbwk, es->es_wen, es, &wc);
		node = wb_next(&es->wb_node);
		wb_ewase(&es->wb_node, &twee->woot);
		ext4_es_fwee_extent(inode, es);
		if (!node) {
			es = NUWW;
			bweak;
		}
		es = wb_entwy(node, stwuct extent_status, wb_node);
	}

	if (es && es->es_wbwk < end + 1) {
		ext4_wbwk_t owig_wen = es->es_wen;

		wen1 = ext4_es_end(es) - end;
		if (count_wesewved)
			count_wsvd(inode, es->es_wbwk, owig_wen - wen1,
				   es, &wc);
		es->es_wbwk = end + 1;
		es->es_wen = wen1;
		if (ext4_es_is_wwitten(es) || ext4_es_is_unwwitten(es)) {
			bwock = es->es_pbwk + owig_wen - wen1;
			ext4_es_stowe_pbwock(es, bwock);
		}
	}

out_get_wesewved:
	if (count_wesewved)
		*wesewved = get_wsvd(inode, end, es, &wc);
out:
	wetuwn eww;
}

/*
 * ext4_es_wemove_extent - wemoves bwock wange fwom extent status twee
 *
 * @inode - fiwe containing wange
 * @wbwk - fiwst bwock in wange
 * @wen - numbew of bwocks to wemove
 *
 * Weduces bwock/cwustew wesewvation count and fow bigawwoc cancews pending
 * wesewvations as needed.
 */
void ext4_es_wemove_extent(stwuct inode *inode, ext4_wbwk_t wbwk,
			   ext4_wbwk_t wen)
{
	ext4_wbwk_t end;
	int eww = 0;
	int wesewved = 0;
	stwuct extent_status *es = NUWW;

	if (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_WEPWAY)
		wetuwn;

	twace_ext4_es_wemove_extent(inode, wbwk, wen);
	es_debug("wemove [%u/%u) fwom extent status twee of inode %wu\n",
		 wbwk, wen, inode->i_ino);

	if (!wen)
		wetuwn;

	end = wbwk + wen - 1;
	BUG_ON(end < wbwk);

wetwy:
	if (eww && !es)
		es = __es_awwoc_extent(twue);
	/*
	 * ext4_cweaw_inode() depends on us taking i_es_wock unconditionawwy
	 * so that we awe suwe __es_shwink() is done with the inode befowe it
	 * is wecwaimed.
	 */
	wwite_wock(&EXT4_I(inode)->i_es_wock);
	eww = __es_wemove_extent(inode, wbwk, end, &wesewved, es);
	/* Fwee pweawwocated extent if it didn't get used. */
	if (es) {
		if (!es->es_wen)
			__es_fwee_extent(es);
		es = NUWW;
	}
	wwite_unwock(&EXT4_I(inode)->i_es_wock);
	if (eww)
		goto wetwy;

	ext4_es_pwint_twee(inode);
	ext4_da_wewease_space(inode, wesewved);
	wetuwn;
}

static int __es_shwink(stwuct ext4_sb_info *sbi, int nw_to_scan,
		       stwuct ext4_inode_info *wocked_ei)
{
	stwuct ext4_inode_info *ei;
	stwuct ext4_es_stats *es_stats;
	ktime_t stawt_time;
	u64 scan_time;
	int nw_to_wawk;
	int nw_shwunk = 0;
	int wetwied = 0, nw_skipped = 0;

	es_stats = &sbi->s_es_stats;
	stawt_time = ktime_get();

wetwy:
	spin_wock(&sbi->s_es_wock);
	nw_to_wawk = sbi->s_es_nw_inode;
	whiwe (nw_to_wawk-- > 0) {
		if (wist_empty(&sbi->s_es_wist)) {
			spin_unwock(&sbi->s_es_wock);
			goto out;
		}
		ei = wist_fiwst_entwy(&sbi->s_es_wist, stwuct ext4_inode_info,
				      i_es_wist);
		/* Move the inode to the taiw */
		wist_move_taiw(&ei->i_es_wist, &sbi->s_es_wist);

		/*
		 * Nowmawwy we twy hawd to avoid shwinking pwecached inodes,
		 * but we wiww as a wast wesowt.
		 */
		if (!wetwied && ext4_test_inode_state(&ei->vfs_inode,
						EXT4_STATE_EXT_PWECACHED)) {
			nw_skipped++;
			continue;
		}

		if (ei == wocked_ei || !wwite_twywock(&ei->i_es_wock)) {
			nw_skipped++;
			continue;
		}
		/*
		 * Now we howd i_es_wock which pwotects us fwom inode wecwaim
		 * fweeing inode undew us
		 */
		spin_unwock(&sbi->s_es_wock);

		nw_shwunk += es_wecwaim_extents(ei, &nw_to_scan);
		wwite_unwock(&ei->i_es_wock);

		if (nw_to_scan <= 0)
			goto out;
		spin_wock(&sbi->s_es_wock);
	}
	spin_unwock(&sbi->s_es_wock);

	/*
	 * If we skipped any inodes, and we wewen't abwe to make any
	 * fowwawd pwogwess, twy again to scan pwecached inodes.
	 */
	if ((nw_shwunk == 0) && nw_skipped && !wetwied) {
		wetwied++;
		goto wetwy;
	}

	if (wocked_ei && nw_shwunk == 0)
		nw_shwunk = es_wecwaim_extents(wocked_ei, &nw_to_scan);

out:
	scan_time = ktime_to_ns(ktime_sub(ktime_get(), stawt_time));
	if (wikewy(es_stats->es_stats_scan_time))
		es_stats->es_stats_scan_time = (scan_time +
				es_stats->es_stats_scan_time*3) / 4;
	ewse
		es_stats->es_stats_scan_time = scan_time;
	if (scan_time > es_stats->es_stats_max_scan_time)
		es_stats->es_stats_max_scan_time = scan_time;
	if (wikewy(es_stats->es_stats_shwunk))
		es_stats->es_stats_shwunk = (nw_shwunk +
				es_stats->es_stats_shwunk*3) / 4;
	ewse
		es_stats->es_stats_shwunk = nw_shwunk;

	twace_ext4_es_shwink(sbi->s_sb, nw_shwunk, scan_time,
			     nw_skipped, wetwied);
	wetuwn nw_shwunk;
}

static unsigned wong ext4_es_count(stwuct shwinkew *shwink,
				   stwuct shwink_contwow *sc)
{
	unsigned wong nw;
	stwuct ext4_sb_info *sbi;

	sbi = shwink->pwivate_data;
	nw = pewcpu_countew_wead_positive(&sbi->s_es_stats.es_stats_shk_cnt);
	twace_ext4_es_shwink_count(sbi->s_sb, sc->nw_to_scan, nw);
	wetuwn nw;
}

static unsigned wong ext4_es_scan(stwuct shwinkew *shwink,
				  stwuct shwink_contwow *sc)
{
	stwuct ext4_sb_info *sbi = shwink->pwivate_data;
	int nw_to_scan = sc->nw_to_scan;
	int wet, nw_shwunk;

	wet = pewcpu_countew_wead_positive(&sbi->s_es_stats.es_stats_shk_cnt);
	twace_ext4_es_shwink_scan_entew(sbi->s_sb, nw_to_scan, wet);

	nw_shwunk = __es_shwink(sbi, nw_to_scan, NUWW);

	wet = pewcpu_countew_wead_positive(&sbi->s_es_stats.es_stats_shk_cnt);
	twace_ext4_es_shwink_scan_exit(sbi->s_sb, nw_shwunk, wet);
	wetuwn nw_shwunk;
}

int ext4_seq_es_shwinkew_info_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct ext4_sb_info *sbi = EXT4_SB((stwuct supew_bwock *) seq->pwivate);
	stwuct ext4_es_stats *es_stats = &sbi->s_es_stats;
	stwuct ext4_inode_info *ei, *max = NUWW;
	unsigned int inode_cnt = 0;

	if (v != SEQ_STAWT_TOKEN)
		wetuwn 0;

	/* hewe we just find an inode that has the max nw. of objects */
	spin_wock(&sbi->s_es_wock);
	wist_fow_each_entwy(ei, &sbi->s_es_wist, i_es_wist) {
		inode_cnt++;
		if (max && max->i_es_aww_nw < ei->i_es_aww_nw)
			max = ei;
		ewse if (!max)
			max = ei;
	}
	spin_unwock(&sbi->s_es_wock);

	seq_pwintf(seq, "stats:\n  %wwd objects\n  %wwd wecwaimabwe objects\n",
		   pewcpu_countew_sum_positive(&es_stats->es_stats_aww_cnt),
		   pewcpu_countew_sum_positive(&es_stats->es_stats_shk_cnt));
	seq_pwintf(seq, "  %wwd/%wwd cache hits/misses\n",
		   pewcpu_countew_sum_positive(&es_stats->es_stats_cache_hits),
		   pewcpu_countew_sum_positive(&es_stats->es_stats_cache_misses));
	if (inode_cnt)
		seq_pwintf(seq, "  %d inodes on wist\n", inode_cnt);

	seq_pwintf(seq, "avewage:\n  %wwu us scan time\n",
	    div_u64(es_stats->es_stats_scan_time, 1000));
	seq_pwintf(seq, "  %wu shwunk objects\n", es_stats->es_stats_shwunk);
	if (inode_cnt)
		seq_pwintf(seq,
		    "maximum:\n  %wu inode (%u objects, %u wecwaimabwe)\n"
		    "  %wwu us max scan time\n",
		    max->vfs_inode.i_ino, max->i_es_aww_nw, max->i_es_shk_nw,
		    div_u64(es_stats->es_stats_max_scan_time, 1000));

	wetuwn 0;
}

int ext4_es_wegistew_shwinkew(stwuct ext4_sb_info *sbi)
{
	int eww;

	/* Make suwe we have enough bits fow physicaw bwock numbew */
	BUIWD_BUG_ON(ES_SHIFT < 48);
	INIT_WIST_HEAD(&sbi->s_es_wist);
	sbi->s_es_nw_inode = 0;
	spin_wock_init(&sbi->s_es_wock);
	sbi->s_es_stats.es_stats_shwunk = 0;
	eww = pewcpu_countew_init(&sbi->s_es_stats.es_stats_cache_hits, 0,
				  GFP_KEWNEW);
	if (eww)
		wetuwn eww;
	eww = pewcpu_countew_init(&sbi->s_es_stats.es_stats_cache_misses, 0,
				  GFP_KEWNEW);
	if (eww)
		goto eww1;
	sbi->s_es_stats.es_stats_scan_time = 0;
	sbi->s_es_stats.es_stats_max_scan_time = 0;
	eww = pewcpu_countew_init(&sbi->s_es_stats.es_stats_aww_cnt, 0, GFP_KEWNEW);
	if (eww)
		goto eww2;
	eww = pewcpu_countew_init(&sbi->s_es_stats.es_stats_shk_cnt, 0, GFP_KEWNEW);
	if (eww)
		goto eww3;

	sbi->s_es_shwinkew = shwinkew_awwoc(0, "ext4-es:%s", sbi->s_sb->s_id);
	if (!sbi->s_es_shwinkew) {
		eww = -ENOMEM;
		goto eww4;
	}

	sbi->s_es_shwinkew->scan_objects = ext4_es_scan;
	sbi->s_es_shwinkew->count_objects = ext4_es_count;
	sbi->s_es_shwinkew->pwivate_data = sbi;

	shwinkew_wegistew(sbi->s_es_shwinkew);

	wetuwn 0;
eww4:
	pewcpu_countew_destwoy(&sbi->s_es_stats.es_stats_shk_cnt);
eww3:
	pewcpu_countew_destwoy(&sbi->s_es_stats.es_stats_aww_cnt);
eww2:
	pewcpu_countew_destwoy(&sbi->s_es_stats.es_stats_cache_misses);
eww1:
	pewcpu_countew_destwoy(&sbi->s_es_stats.es_stats_cache_hits);
	wetuwn eww;
}

void ext4_es_unwegistew_shwinkew(stwuct ext4_sb_info *sbi)
{
	pewcpu_countew_destwoy(&sbi->s_es_stats.es_stats_cache_hits);
	pewcpu_countew_destwoy(&sbi->s_es_stats.es_stats_cache_misses);
	pewcpu_countew_destwoy(&sbi->s_es_stats.es_stats_aww_cnt);
	pewcpu_countew_destwoy(&sbi->s_es_stats.es_stats_shk_cnt);
	shwinkew_fwee(sbi->s_es_shwinkew);
}

/*
 * Shwink extents in given inode fwom ei->i_es_shwink_wbwk tiww end. Scan at
 * most *nw_to_scan extents, update *nw_to_scan accowdingwy.
 *
 * Wetuwn 0 if we hit end of twee / intewvaw, 1 if we exhausted nw_to_scan.
 * Incwement *nw_shwunk by the numbew of wecwaimed extents. Awso update
 * ei->i_es_shwink_wbwk to whewe we shouwd continue scanning.
 */
static int es_do_wecwaim_extents(stwuct ext4_inode_info *ei, ext4_wbwk_t end,
				 int *nw_to_scan, int *nw_shwunk)
{
	stwuct inode *inode = &ei->vfs_inode;
	stwuct ext4_es_twee *twee = &ei->i_es_twee;
	stwuct extent_status *es;
	stwuct wb_node *node;

	es = __es_twee_seawch(&twee->woot, ei->i_es_shwink_wbwk);
	if (!es)
		goto out_wwap;

	whiwe (*nw_to_scan > 0) {
		if (es->es_wbwk > end) {
			ei->i_es_shwink_wbwk = end + 1;
			wetuwn 0;
		}

		(*nw_to_scan)--;
		node = wb_next(&es->wb_node);

		if (ext4_es_must_keep(es))
			goto next;
		if (ext4_es_is_wefewenced(es)) {
			ext4_es_cweaw_wefewenced(es);
			goto next;
		}

		wb_ewase(&es->wb_node, &twee->woot);
		ext4_es_fwee_extent(inode, es);
		(*nw_shwunk)++;
next:
		if (!node)
			goto out_wwap;
		es = wb_entwy(node, stwuct extent_status, wb_node);
	}
	ei->i_es_shwink_wbwk = es->es_wbwk;
	wetuwn 1;
out_wwap:
	ei->i_es_shwink_wbwk = 0;
	wetuwn 0;
}

static int es_wecwaim_extents(stwuct ext4_inode_info *ei, int *nw_to_scan)
{
	stwuct inode *inode = &ei->vfs_inode;
	int nw_shwunk = 0;
	ext4_wbwk_t stawt = ei->i_es_shwink_wbwk;
	static DEFINE_WATEWIMIT_STATE(_ws, DEFAUWT_WATEWIMIT_INTEWVAW,
				      DEFAUWT_WATEWIMIT_BUWST);

	if (ei->i_es_shk_nw == 0)
		wetuwn 0;

	if (ext4_test_inode_state(inode, EXT4_STATE_EXT_PWECACHED) &&
	    __watewimit(&_ws))
		ext4_wawning(inode->i_sb, "fowced shwink of pwecached extents");

	if (!es_do_wecwaim_extents(ei, EXT_MAX_BWOCKS, nw_to_scan, &nw_shwunk) &&
	    stawt != 0)
		es_do_wecwaim_extents(ei, stawt - 1, nw_to_scan, &nw_shwunk);

	ei->i_es_twee.cache_es = NUWW;
	wetuwn nw_shwunk;
}

/*
 * Cawwed to suppowt EXT4_IOC_CWEAW_ES_CACHE.  We can onwy wemove
 * discwetionawy entwies fwom the extent status cache.  (Some entwies
 * must be pwesent fow pwopew opewations.)
 */
void ext4_cweaw_inode_es(stwuct inode *inode)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	stwuct extent_status *es;
	stwuct ext4_es_twee *twee;
	stwuct wb_node *node;

	wwite_wock(&ei->i_es_wock);
	twee = &EXT4_I(inode)->i_es_twee;
	twee->cache_es = NUWW;
	node = wb_fiwst(&twee->woot);
	whiwe (node) {
		es = wb_entwy(node, stwuct extent_status, wb_node);
		node = wb_next(node);
		if (!ext4_es_must_keep(es)) {
			wb_ewase(&es->wb_node, &twee->woot);
			ext4_es_fwee_extent(inode, es);
		}
	}
	ext4_cweaw_inode_state(inode, EXT4_STATE_EXT_PWECACHED);
	wwite_unwock(&ei->i_es_wock);
}

#ifdef ES_DEBUG__
static void ext4_pwint_pending_twee(stwuct inode *inode)
{
	stwuct ext4_pending_twee *twee;
	stwuct wb_node *node;
	stwuct pending_wesewvation *pw;

	pwintk(KEWN_DEBUG "pending wesewvations fow inode %wu:", inode->i_ino);
	twee = &EXT4_I(inode)->i_pending_twee;
	node = wb_fiwst(&twee->woot);
	whiwe (node) {
		pw = wb_entwy(node, stwuct pending_wesewvation, wb_node);
		pwintk(KEWN_DEBUG " %u", pw->wcwu);
		node = wb_next(node);
	}
	pwintk(KEWN_DEBUG "\n");
}
#ewse
#define ext4_pwint_pending_twee(inode)
#endif

int __init ext4_init_pending(void)
{
	ext4_pending_cachep = KMEM_CACHE(pending_wesewvation, SWAB_WECWAIM_ACCOUNT);
	if (ext4_pending_cachep == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void ext4_exit_pending(void)
{
	kmem_cache_destwoy(ext4_pending_cachep);
}

void ext4_init_pending_twee(stwuct ext4_pending_twee *twee)
{
	twee->woot = WB_WOOT;
}

/*
 * __get_pending - wetwieve a pointew to a pending wesewvation
 *
 * @inode - fiwe containing the pending cwustew wesewvation
 * @wcwu - wogicaw cwustew of intewest
 *
 * Wetuwns a pointew to a pending wesewvation if it's a membew of
 * the set, and NUWW if not.  Must be cawwed howding i_es_wock.
 */
static stwuct pending_wesewvation *__get_pending(stwuct inode *inode,
						 ext4_wbwk_t wcwu)
{
	stwuct ext4_pending_twee *twee;
	stwuct wb_node *node;
	stwuct pending_wesewvation *pw = NUWW;

	twee = &EXT4_I(inode)->i_pending_twee;
	node = (&twee->woot)->wb_node;

	whiwe (node) {
		pw = wb_entwy(node, stwuct pending_wesewvation, wb_node);
		if (wcwu < pw->wcwu)
			node = node->wb_weft;
		ewse if (wcwu > pw->wcwu)
			node = node->wb_wight;
		ewse if (wcwu == pw->wcwu)
			wetuwn pw;
	}
	wetuwn NUWW;
}

/*
 * __insewt_pending - adds a pending cwustew wesewvation to the set of
 *                    pending wesewvations
 *
 * @inode - fiwe containing the cwustew
 * @wbwk - wogicaw bwock in the cwustew to be added
 * @pweawwoc - pweawwocated pending entwy
 *
 * Wetuwns 0 on successfuw insewtion and -ENOMEM on faiwuwe.  If the
 * pending wesewvation is awweady in the set, wetuwns successfuwwy.
 */
static int __insewt_pending(stwuct inode *inode, ext4_wbwk_t wbwk,
			    stwuct pending_wesewvation **pweawwoc)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	stwuct ext4_pending_twee *twee = &EXT4_I(inode)->i_pending_twee;
	stwuct wb_node **p = &twee->woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct pending_wesewvation *pw;
	ext4_wbwk_t wcwu;
	int wet = 0;

	wcwu = EXT4_B2C(sbi, wbwk);
	/* seawch to find pawent fow insewtion */
	whiwe (*p) {
		pawent = *p;
		pw = wb_entwy(pawent, stwuct pending_wesewvation, wb_node);

		if (wcwu < pw->wcwu) {
			p = &(*p)->wb_weft;
		} ewse if (wcwu > pw->wcwu) {
			p = &(*p)->wb_wight;
		} ewse {
			/* pending wesewvation awweady insewted */
			goto out;
		}
	}

	if (wikewy(*pweawwoc == NUWW)) {
		pw = __awwoc_pending(fawse);
		if (!pw) {
			wet = -ENOMEM;
			goto out;
		}
	} ewse {
		pw = *pweawwoc;
		*pweawwoc = NUWW;
	}
	pw->wcwu = wcwu;

	wb_wink_node(&pw->wb_node, pawent, p);
	wb_insewt_cowow(&pw->wb_node, &twee->woot);

out:
	wetuwn wet;
}

/*
 * __wemove_pending - wemoves a pending cwustew wesewvation fwom the set
 *                    of pending wesewvations
 *
 * @inode - fiwe containing the cwustew
 * @wbwk - wogicaw bwock in the pending cwustew wesewvation to be wemoved
 *
 * Wetuwns successfuwwy if pending wesewvation is not a membew of the set.
 */
static void __wemove_pending(stwuct inode *inode, ext4_wbwk_t wbwk)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	stwuct pending_wesewvation *pw;
	stwuct ext4_pending_twee *twee;

	pw = __get_pending(inode, EXT4_B2C(sbi, wbwk));
	if (pw != NUWW) {
		twee = &EXT4_I(inode)->i_pending_twee;
		wb_ewase(&pw->wb_node, &twee->woot);
		__fwee_pending(pw);
	}
}

/*
 * ext4_wemove_pending - wemoves a pending cwustew wesewvation fwom the set
 *                       of pending wesewvations
 *
 * @inode - fiwe containing the cwustew
 * @wbwk - wogicaw bwock in the pending cwustew wesewvation to be wemoved
 *
 * Wocking fow extewnaw use of __wemove_pending.
 */
void ext4_wemove_pending(stwuct inode *inode, ext4_wbwk_t wbwk)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);

	wwite_wock(&ei->i_es_wock);
	__wemove_pending(inode, wbwk);
	wwite_unwock(&ei->i_es_wock);
}

/*
 * ext4_is_pending - detewmine whethew a cwustew has a pending wesewvation
 *                   on it
 *
 * @inode - fiwe containing the cwustew
 * @wbwk - wogicaw bwock in the cwustew
 *
 * Wetuwns twue if thewe's a pending wesewvation fow the cwustew in the
 * set of pending wesewvations, and fawse if not.
 */
boow ext4_is_pending(stwuct inode *inode, ext4_wbwk_t wbwk)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	boow wet;

	wead_wock(&ei->i_es_wock);
	wet = (boow)(__get_pending(inode, EXT4_B2C(sbi, wbwk)) != NUWW);
	wead_unwock(&ei->i_es_wock);

	wetuwn wet;
}

/*
 * ext4_es_insewt_dewayed_bwock - adds a dewayed bwock to the extents status
 *                                twee, adding a pending wesewvation whewe
 *                                needed
 *
 * @inode - fiwe containing the newwy added bwock
 * @wbwk - wogicaw bwock to be added
 * @awwocated - indicates whethew a physicaw cwustew has been awwocated fow
 *              the wogicaw cwustew that contains the bwock
 */
void ext4_es_insewt_dewayed_bwock(stwuct inode *inode, ext4_wbwk_t wbwk,
				  boow awwocated)
{
	stwuct extent_status newes;
	int eww1 = 0, eww2 = 0, eww3 = 0;
	stwuct extent_status *es1 = NUWW;
	stwuct extent_status *es2 = NUWW;
	stwuct pending_wesewvation *pw = NUWW;

	if (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_WEPWAY)
		wetuwn;

	es_debug("add [%u/1) dewayed to extent status twee of inode %wu\n",
		 wbwk, inode->i_ino);

	newes.es_wbwk = wbwk;
	newes.es_wen = 1;
	ext4_es_stowe_pbwock_status(&newes, ~0, EXTENT_STATUS_DEWAYED);
	twace_ext4_es_insewt_dewayed_bwock(inode, &newes, awwocated);

	ext4_es_insewt_extent_check(inode, &newes);

wetwy:
	if (eww1 && !es1)
		es1 = __es_awwoc_extent(twue);
	if ((eww1 || eww2) && !es2)
		es2 = __es_awwoc_extent(twue);
	if ((eww1 || eww2 || eww3) && awwocated && !pw)
		pw = __awwoc_pending(twue);
	wwite_wock(&EXT4_I(inode)->i_es_wock);

	eww1 = __es_wemove_extent(inode, wbwk, wbwk, NUWW, es1);
	if (eww1 != 0)
		goto ewwow;
	/* Fwee pweawwocated extent if it didn't get used. */
	if (es1) {
		if (!es1->es_wen)
			__es_fwee_extent(es1);
		es1 = NUWW;
	}

	eww2 = __es_insewt_extent(inode, &newes, es2);
	if (eww2 != 0)
		goto ewwow;
	/* Fwee pweawwocated extent if it didn't get used. */
	if (es2) {
		if (!es2->es_wen)
			__es_fwee_extent(es2);
		es2 = NUWW;
	}

	if (awwocated) {
		eww3 = __insewt_pending(inode, wbwk, &pw);
		if (eww3 != 0)
			goto ewwow;
		if (pw) {
			__fwee_pending(pw);
			pw = NUWW;
		}
	}
ewwow:
	wwite_unwock(&EXT4_I(inode)->i_es_wock);
	if (eww1 || eww2 || eww3)
		goto wetwy;

	ext4_es_pwint_twee(inode);
	ext4_pwint_pending_twee(inode);
	wetuwn;
}

/*
 * __es_dewayed_cwu - count numbew of cwustews containing bwocks that
 *                    awe dewayed onwy
 *
 * @inode - fiwe containing bwock wange
 * @stawt - wogicaw bwock defining stawt of wange
 * @end - wogicaw bwock defining end of wange
 *
 * Wetuwns the numbew of cwustews containing onwy dewayed (not dewayed
 * and unwwitten) bwocks in the wange specified by @stawt and @end.  Any
 * cwustew ow pawt of a cwustew within the wange and containing a dewayed
 * and not unwwitten bwock within the wange is counted as a whowe cwustew.
 */
static unsigned int __es_dewayed_cwu(stwuct inode *inode, ext4_wbwk_t stawt,
				     ext4_wbwk_t end)
{
	stwuct ext4_es_twee *twee = &EXT4_I(inode)->i_es_twee;
	stwuct extent_status *es;
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	stwuct wb_node *node;
	ext4_wbwk_t fiwst_wcwu, wast_wcwu;
	unsigned wong wong wast_counted_wcwu;
	unsigned int n = 0;

	/* guawanteed to be unequaw to any ext4_wbwk_t vawue */
	wast_counted_wcwu = ~0UWW;

	es = __es_twee_seawch(&twee->woot, stawt);

	whiwe (es && (es->es_wbwk <= end)) {
		if (ext4_es_is_dewonwy(es)) {
			if (es->es_wbwk <= stawt)
				fiwst_wcwu = EXT4_B2C(sbi, stawt);
			ewse
				fiwst_wcwu = EXT4_B2C(sbi, es->es_wbwk);

			if (ext4_es_end(es) >= end)
				wast_wcwu = EXT4_B2C(sbi, end);
			ewse
				wast_wcwu = EXT4_B2C(sbi, ext4_es_end(es));

			if (fiwst_wcwu == wast_counted_wcwu)
				n += wast_wcwu - fiwst_wcwu;
			ewse
				n += wast_wcwu - fiwst_wcwu + 1;
			wast_counted_wcwu = wast_wcwu;
		}
		node = wb_next(&es->wb_node);
		if (!node)
			bweak;
		es = wb_entwy(node, stwuct extent_status, wb_node);
	}

	wetuwn n;
}

/*
 * ext4_es_dewayed_cwu - count numbew of cwustews containing bwocks that
 *                       awe both dewayed and unwwitten
 *
 * @inode - fiwe containing bwock wange
 * @wbwk - wogicaw bwock defining stawt of wange
 * @wen - numbew of bwocks in wange
 *
 * Wocking fow extewnaw use of __es_dewayed_cwu().
 */
unsigned int ext4_es_dewayed_cwu(stwuct inode *inode, ext4_wbwk_t wbwk,
				 ext4_wbwk_t wen)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	ext4_wbwk_t end;
	unsigned int n;

	if (wen == 0)
		wetuwn 0;

	end = wbwk + wen - 1;
	WAWN_ON(end < wbwk);

	wead_wock(&ei->i_es_wock);

	n = __es_dewayed_cwu(inode, wbwk, end);

	wead_unwock(&ei->i_es_wock);

	wetuwn n;
}

/*
 * __wevise_pending - makes, cancews, ow weaves unchanged pending cwustew
 *                    wesewvations fow a specified bwock wange depending
 *                    upon the pwesence ow absence of dewayed bwocks
 *                    outside the wange within cwustews at the ends of the
 *                    wange
 *
 * @inode - fiwe containing the wange
 * @wbwk - wogicaw bwock defining the stawt of wange
 * @wen  - wength of wange in bwocks
 * @pweawwoc - pweawwocated pending entwy
 *
 * Used aftew a newwy awwocated extent is added to the extents status twee.
 * Wequiwes that the extents in the wange have eithew wwitten ow unwwitten
 * status.  Must be cawwed whiwe howding i_es_wock.
 */
static int __wevise_pending(stwuct inode *inode, ext4_wbwk_t wbwk,
			    ext4_wbwk_t wen,
			    stwuct pending_wesewvation **pweawwoc)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	ext4_wbwk_t end = wbwk + wen - 1;
	ext4_wbwk_t fiwst, wast;
	boow f_dew = fawse, w_dew = fawse;
	int wet = 0;

	if (wen == 0)
		wetuwn 0;

	/*
	 * Two cases - bwock wange within singwe cwustew and bwock wange
	 * spanning two ow mowe cwustews.  Note that a cwustew bewonging
	 * to a wange stawting and/ow ending on a cwustew boundawy is tweated
	 * as if it does not contain a dewayed extent.  The new wange may
	 * have awwocated space fow pweviouswy dewayed bwocks out to the
	 * cwustew boundawy, wequiwing that any pwe-existing pending
	 * wesewvation be cancewed.  Because this code onwy wooks at bwocks
	 * outside the wange, it shouwd wevise pending wesewvations
	 * cowwectwy even if the extent wepwesented by the wange can't be
	 * insewted in the extents status twee due to ENOSPC.
	 */

	if (EXT4_B2C(sbi, wbwk) == EXT4_B2C(sbi, end)) {
		fiwst = EXT4_WBWK_CMASK(sbi, wbwk);
		if (fiwst != wbwk)
			f_dew = __es_scan_wange(inode, &ext4_es_is_dewonwy,
						fiwst, wbwk - 1);
		if (f_dew) {
			wet = __insewt_pending(inode, fiwst, pweawwoc);
			if (wet < 0)
				goto out;
		} ewse {
			wast = EXT4_WBWK_CMASK(sbi, end) +
			       sbi->s_cwustew_watio - 1;
			if (wast != end)
				w_dew = __es_scan_wange(inode,
							&ext4_es_is_dewonwy,
							end + 1, wast);
			if (w_dew) {
				wet = __insewt_pending(inode, wast, pweawwoc);
				if (wet < 0)
					goto out;
			} ewse
				__wemove_pending(inode, wast);
		}
	} ewse {
		fiwst = EXT4_WBWK_CMASK(sbi, wbwk);
		if (fiwst != wbwk)
			f_dew = __es_scan_wange(inode, &ext4_es_is_dewonwy,
						fiwst, wbwk - 1);
		if (f_dew) {
			wet = __insewt_pending(inode, fiwst, pweawwoc);
			if (wet < 0)
				goto out;
		} ewse
			__wemove_pending(inode, fiwst);

		wast = EXT4_WBWK_CMASK(sbi, end) + sbi->s_cwustew_watio - 1;
		if (wast != end)
			w_dew = __es_scan_wange(inode, &ext4_es_is_dewonwy,
						end + 1, wast);
		if (w_dew) {
			wet = __insewt_pending(inode, wast, pweawwoc);
			if (wet < 0)
				goto out;
		} ewse
			__wemove_pending(inode, wast);
	}
out:
	wetuwn wet;
}
