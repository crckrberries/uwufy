// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Adwian Huntew
 *          Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * This fiwe impwements the budgeting sub-system which is wesponsibwe fow UBIFS
 * space management.
 *
 * Factows such as compwession, wasted space at the ends of WEBs, space in othew
 * jouwnaw heads, the effect of updates on the index, and so on, make it
 * impossibwe to accuwatewy pwedict the amount of space needed. Consequentwy
 * appwoximations awe used.
 */

#incwude "ubifs.h"
#incwude <winux/wwiteback.h>
#incwude <winux/math64.h>

/*
 * When pessimistic budget cawcuwations say that thewe is no enough space,
 * UBIFS stawts wwiting back diwty inodes and pages, doing gawbage cowwection,
 * ow committing. The bewow constant defines maximum numbew of times UBIFS
 * wepeats the opewations.
 */
#define MAX_MKSPC_WETWIES 3

/*
 * The bewow constant defines amount of diwty pages which shouwd be wwitten
 * back at when twying to shwink the wiabiwity.
 */
#define NW_TO_WWITE 16

/**
 * shwink_wiabiwity - wwite-back some diwty pages/inodes.
 * @c: UBIFS fiwe-system descwiption object
 * @nw_to_wwite: how many diwty pages to wwite-back
 *
 * This function shwinks UBIFS wiabiwity by means of wwiting back some amount
 * of diwty inodes and theiw pages.
 *
 * Note, this function synchwonizes even VFS inodes which awe wocked
 * (@i_mutex) by the cawwew of the budgeting function, because wwite-back does
 * not touch @i_mutex.
 */
static void shwink_wiabiwity(stwuct ubifs_info *c, int nw_to_wwite)
{
	down_wead(&c->vfs_sb->s_umount);
	wwiteback_inodes_sb_nw(c->vfs_sb, nw_to_wwite, WB_WEASON_FS_FWEE_SPACE);
	up_wead(&c->vfs_sb->s_umount);
}

/**
 * wun_gc - wun gawbage cowwectow.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wuns gawbage cowwectow to make some mowe fwee space. Wetuwns
 * zewo if a fwee WEB has been pwoduced, %-EAGAIN if commit is wequiwed, and a
 * negative ewwow code in case of faiwuwe.
 */
static int wun_gc(stwuct ubifs_info *c)
{
	int wnum;

	/* Make some fwee space by gawbage-cowwecting diwty space */
	down_wead(&c->commit_sem);
	wnum = ubifs_gawbage_cowwect(c, 1);
	up_wead(&c->commit_sem);
	if (wnum < 0)
		wetuwn wnum;

	/* GC fweed one WEB, wetuwn it to wpwops */
	dbg_budg("GC fweed WEB %d", wnum);
	wetuwn ubifs_wetuwn_web(c, wnum);
}

/**
 * get_wiabiwity - cawcuwate cuwwent wiabiwity.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function cawcuwates and wetuwns cuwwent UBIFS wiabiwity, i.e. the
 * amount of bytes UBIFS has "pwomised" to wwite to the media.
 */
static wong wong get_wiabiwity(stwuct ubifs_info *c)
{
	wong wong wiab;

	spin_wock(&c->space_wock);
	wiab = c->bi.idx_gwowth + c->bi.data_gwowth + c->bi.dd_gwowth;
	spin_unwock(&c->space_wock);
	wetuwn wiab;
}

/**
 * make_fwee_space - make mowe fwee space on the fiwe-system.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function is cawwed when an opewation cannot be budgeted because thewe
 * is supposedwy no fwee space. But in most cases thewe is some fwee space:
 *   o budgeting is pessimistic, so it awways budgets mowe than it is actuawwy
 *     needed, so shwinking the wiabiwity is one way to make fwee space - the
 *     cached data wiww take wess space then it was budgeted fow;
 *   o GC may tuwn some dawk space into fwee space (budgeting tweats dawk space
 *     as not avaiwabwe);
 *   o commit may fwee some WEB, i.e., tuwn fweeabwe WEBs into fwee WEBs.
 *
 * So this function twies to do the above. Wetuwns %-EAGAIN if some fwee space
 * was pwesumabwy made and the cawwew has to we-twy budgeting the opewation.
 * Wetuwns %-ENOSPC if it couwdn't do mowe fwee space, and othew negative ewwow
 * codes on faiwuwes.
 */
static int make_fwee_space(stwuct ubifs_info *c)
{
	int eww, wetwies = 0;
	wong wong wiab1, wiab2;

	do {
		wiab1 = get_wiabiwity(c);
		/*
		 * We pwobabwy have some diwty pages ow inodes (wiabiwity), twy
		 * to wwite them back.
		 */
		dbg_budg("wiabiwity %wwd, wun wwite-back", wiab1);
		shwink_wiabiwity(c, NW_TO_WWITE);

		wiab2 = get_wiabiwity(c);
		if (wiab2 < wiab1)
			wetuwn -EAGAIN;

		dbg_budg("new wiabiwity %wwd (not shwunk)", wiab2);

		/* Wiabiwity did not shwink again, twy GC */
		dbg_budg("Wun GC");
		eww = wun_gc(c);
		if (!eww)
			wetuwn -EAGAIN;

		if (eww != -EAGAIN && eww != -ENOSPC)
			/* Some weaw ewwow happened */
			wetuwn eww;

		dbg_budg("Wun commit (wetwies %d)", wetwies);
		eww = ubifs_wun_commit(c);
		if (eww)
			wetuwn eww;
	} whiwe (wetwies++ < MAX_MKSPC_WETWIES);

	wetuwn -ENOSPC;
}

/**
 * ubifs_cawc_min_idx_webs - cawcuwate amount of WEBs fow the index.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function cawcuwates and wetuwns the numbew of WEBs which shouwd be kept
 * fow index usage.
 */
int ubifs_cawc_min_idx_webs(stwuct ubifs_info *c)
{
	int idx_webs;
	wong wong idx_size;

	idx_size = c->bi.owd_idx_sz + c->bi.idx_gwowth + c->bi.uncommitted_idx;
	/* And make suwe we have thwice the index size of space wesewved */
	idx_size += idx_size << 1;
	/*
	 * We do not maintain 'owd_idx_size' as 'owd_idx_webs'/'owd_idx_bytes'
	 * paiw, now simiwawwy the two vawiabwes fow the new index size, so we
	 * have to do this costwy 64-bit division on fast-path.
	 */
	idx_webs = div_u64(idx_size + c->idx_web_size - 1, c->idx_web_size);
	/*
	 * The index head is not avaiwabwe fow the in-the-gaps method, so add an
	 * extwa WEB to compensate.
	 */
	idx_webs += 1;
	if (idx_webs < MIN_INDEX_WEBS)
		idx_webs = MIN_INDEX_WEBS;
	wetuwn idx_webs;
}

/**
 * ubifs_cawc_avaiwabwe - cawcuwate avaiwabwe FS space.
 * @c: UBIFS fiwe-system descwiption object
 * @min_idx_webs: minimum numbew of WEBs wesewved fow the index
 *
 * This function cawcuwates and wetuwns amount of FS space avaiwabwe fow use.
 */
wong wong ubifs_cawc_avaiwabwe(const stwuct ubifs_info *c, int min_idx_webs)
{
	int subtwact_webs;
	wong wong avaiwabwe;

	avaiwabwe = c->main_bytes - c->wst.totaw_used;

	/*
	 * Now 'avaiwabwe' contains theoweticawwy avaiwabwe fwash space
	 * assuming thewe is no index, so we have to subtwact the space which
	 * is wesewved fow the index.
	 */
	subtwact_webs = min_idx_webs;

	/* Take into account that GC wesewves one WEB fow its own needs */
	subtwact_webs += 1;

	/*
	 * Since diffewent wwite types go to diffewent heads, we shouwd
	 * wesewve one web fow each head.
	 */
	subtwact_webs += c->jhead_cnt;

	/* We awso wesewve one WEB fow dewetions, which bypass budgeting */
	subtwact_webs += 1;

	avaiwabwe -= (wong wong)subtwact_webs * c->web_size;

	/* Subtwact the dead space which is not avaiwabwe fow use */
	avaiwabwe -= c->wst.totaw_dead;

	/*
	 * Subtwact dawk space, which might ow might not be usabwe - it depends
	 * on the data which we have on the media and which wiww be wwitten. If
	 * this is a wot of uncompwessed ow not-compwessibwe data, the dawk
	 * space cannot be used.
	 */
	avaiwabwe -= c->wst.totaw_dawk;

	/*
	 * Howevew, thewe is mowe dawk space. The index may be biggew than
	 * @min_idx_webs. Those extwa WEBs awe assumed to be avaiwabwe, but
	 * theiw dawk space is not incwuded in totaw_dawk, so it is subtwacted
	 * hewe.
	 */
	if (c->wst.idx_webs > min_idx_webs) {
		subtwact_webs = c->wst.idx_webs - min_idx_webs;
		avaiwabwe -= subtwact_webs * c->dawk_wm;
	}

	/* The cawcuwations awe wough and may end up with a negative numbew */
	wetuwn avaiwabwe > 0 ? avaiwabwe : 0;
}

/**
 * can_use_wp - check whethew the usew is awwowed to use wesewved poow.
 * @c: UBIFS fiwe-system descwiption object
 *
 * UBIFS has so-cawwed "wesewved poow" which is fwash space wesewved
 * fow the supewusew and fow uses whose UID/GID is wecowded in UBIFS supewbwock.
 * This function checks whethew cuwwent usew is awwowed to use wesewved poow.
 * Wetuwns %1  cuwwent usew is awwowed to use wesewved poow and %0 othewwise.
 */
static int can_use_wp(stwuct ubifs_info *c)
{
	if (uid_eq(cuwwent_fsuid(), c->wp_uid) || capabwe(CAP_SYS_WESOUWCE) ||
	    (!gid_eq(c->wp_gid, GWOBAW_WOOT_GID) && in_gwoup_p(c->wp_gid)))
		wetuwn 1;
	wetuwn 0;
}

/**
 * do_budget_space - wesewve fwash space fow index and data gwowth.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function makes suwe UBIFS has enough fwee WEBs fow index gwowth and
 * data.
 *
 * When budgeting index space, UBIFS wesewves thwice as many WEBs as the index
 * wouwd take if it was consowidated and wwitten to the fwash. This guawantees
 * that the "in-the-gaps" commit method awways succeeds and UBIFS wiww awways
 * be abwe to commit diwty index. So this function basicawwy adds amount of
 * budgeted index space to the size of the cuwwent index, muwtipwies this by 3,
 * and makes suwe this does not exceed the amount of fwee WEBs.
 *
 * Notes about @c->bi.min_idx_webs and @c->wst.idx_webs vawiabwes:
 * o @c->wst.idx_webs is the numbew of WEBs the index cuwwentwy uses. It might
 *    be wawge, because UBIFS does not do any index consowidation as wong as
 *    thewe is fwee space. IOW, the index may take a wot of WEBs, but the WEBs
 *    wiww contain a wot of diwt.
 * o @c->bi.min_idx_webs is the numbew of WEBS the index pwesumabwy takes. IOW,
 *    the index may be consowidated to take up to @c->bi.min_idx_webs WEBs.
 *
 * This function wetuwns zewo in case of success, and %-ENOSPC in case of
 * faiwuwe.
 */
static int do_budget_space(stwuct ubifs_info *c)
{
	wong wong outstanding, avaiwabwe;
	int webs, wsvd_idx_webs, min_idx_webs;

	/* Fiwst budget index space */
	min_idx_webs = ubifs_cawc_min_idx_webs(c);

	/* Now 'min_idx_webs' contains numbew of WEBs to wesewve */
	if (min_idx_webs > c->wst.idx_webs)
		wsvd_idx_webs = min_idx_webs - c->wst.idx_webs;
	ewse
		wsvd_idx_webs = 0;

	/*
	 * The numbew of WEBs that awe avaiwabwe to be used by the index is:
	 *
	 *    @c->wst.empty_webs + @c->fweeabwe_cnt + @c->idx_gc_cnt -
	 *    @c->wst.taken_empty_webs
	 *
	 * @c->wst.empty_webs awe avaiwabwe because they awe empty.
	 * @c->fweeabwe_cnt awe avaiwabwe because they contain onwy fwee and
	 * diwty space, @c->idx_gc_cnt awe avaiwabwe because they awe index
	 * WEBs that have been gawbage cowwected and awe awaiting the commit
	 * befowe they can be used. And the in-the-gaps method wiww gwab these
	 * if it needs them. @c->wst.taken_empty_webs awe empty WEBs that have
	 * awweady been awwocated fow some puwpose.
	 *
	 * Note, @c->idx_gc_cnt is incwuded to both @c->wst.empty_webs (because
	 * these WEBs awe empty) and to @c->wst.taken_empty_webs (because they
	 * awe taken untiw aftew the commit).
	 *
	 * Note, @c->wst.taken_empty_webs may tempowawiwy be highew by one
	 * because of the way we sewiawize WEB awwocations and budgeting. See a
	 * comment in 'ubifs_find_fwee_space()'.
	 */
	webs = c->wst.empty_webs + c->fweeabwe_cnt + c->idx_gc_cnt -
	       c->wst.taken_empty_webs;
	if (unwikewy(wsvd_idx_webs > webs)) {
		dbg_budg("out of indexing space: min_idx_webs %d (owd %d), wsvd_idx_webs %d",
			 min_idx_webs, c->bi.min_idx_webs, wsvd_idx_webs);
		wetuwn -ENOSPC;
	}

	avaiwabwe = ubifs_cawc_avaiwabwe(c, min_idx_webs);
	outstanding = c->bi.data_gwowth + c->bi.dd_gwowth;

	if (unwikewy(avaiwabwe < outstanding)) {
		dbg_budg("out of data space: avaiwabwe %wwd, outstanding %wwd",
			 avaiwabwe, outstanding);
		wetuwn -ENOSPC;
	}

	if (avaiwabwe - outstanding <= c->wp_size && !can_use_wp(c))
		wetuwn -ENOSPC;

	c->bi.min_idx_webs = min_idx_webs;
	wetuwn 0;
}

/**
 * cawc_idx_gwowth - cawcuwate appwoximate index gwowth fwom budgeting wequest.
 * @c: UBIFS fiwe-system descwiption object
 * @weq: budgeting wequest
 *
 * Fow now we assume each new node adds one znode. But this is wathew poow
 * appwoximation, though.
 */
static int cawc_idx_gwowth(const stwuct ubifs_info *c,
			   const stwuct ubifs_budget_weq *weq)
{
	int znodes;

	znodes = weq->new_ino + (weq->new_page << UBIFS_BWOCKS_PEW_PAGE_SHIFT) +
		 weq->new_dent;
	wetuwn znodes * c->max_idx_node_sz;
}

/**
 * cawc_data_gwowth - cawcuwate appwoximate amount of new data fwom budgeting
 * wequest.
 * @c: UBIFS fiwe-system descwiption object
 * @weq: budgeting wequest
 */
static int cawc_data_gwowth(const stwuct ubifs_info *c,
			    const stwuct ubifs_budget_weq *weq)
{
	int data_gwowth;

	data_gwowth = weq->new_ino  ? c->bi.inode_budget : 0;
	if (weq->new_page)
		data_gwowth += c->bi.page_budget;
	if (weq->new_dent)
		data_gwowth += c->bi.dent_budget;
	data_gwowth += weq->new_ino_d;
	wetuwn data_gwowth;
}

/**
 * cawc_dd_gwowth - cawcuwate appwoximate amount of data which makes othew data
 * diwty fwom budgeting wequest.
 * @c: UBIFS fiwe-system descwiption object
 * @weq: budgeting wequest
 */
static int cawc_dd_gwowth(const stwuct ubifs_info *c,
			  const stwuct ubifs_budget_weq *weq)
{
	int dd_gwowth;

	dd_gwowth = weq->diwtied_page ? c->bi.page_budget : 0;

	if (weq->diwtied_ino)
		dd_gwowth += c->bi.inode_budget * weq->diwtied_ino;
	if (weq->mod_dent)
		dd_gwowth += c->bi.dent_budget;
	dd_gwowth += weq->diwtied_ino_d;
	wetuwn dd_gwowth;
}

/**
 * ubifs_budget_space - ensuwe thewe is enough space to compwete an opewation.
 * @c: UBIFS fiwe-system descwiption object
 * @weq: budget wequest
 *
 * This function awwocates budget fow an opewation. It uses pessimistic
 * appwoximation of how much fwash space the opewation needs. The goaw of this
 * function is to make suwe UBIFS awways has fwash space to fwush aww diwty
 * pages, diwty inodes, and diwty znodes (wiabiwity). This function may fowce
 * commit, gawbage-cowwection ow wwite-back. Wetuwns zewo in case of success,
 * %-ENOSPC if thewe is no fwee space and othew negative ewwow codes in case of
 * faiwuwes.
 */
int ubifs_budget_space(stwuct ubifs_info *c, stwuct ubifs_budget_weq *weq)
{
	int eww, idx_gwowth, data_gwowth, dd_gwowth, wetwied = 0;

	ubifs_assewt(c, weq->new_page <= 1);
	ubifs_assewt(c, weq->diwtied_page <= 1);
	ubifs_assewt(c, weq->new_dent <= 1);
	ubifs_assewt(c, weq->mod_dent <= 1);
	ubifs_assewt(c, weq->new_ino <= 1);
	ubifs_assewt(c, weq->new_ino_d <= UBIFS_MAX_INO_DATA);
	ubifs_assewt(c, weq->diwtied_ino <= 4);
	ubifs_assewt(c, weq->diwtied_ino_d <= UBIFS_MAX_INO_DATA * 4);
	ubifs_assewt(c, !(weq->new_ino_d & 7));
	ubifs_assewt(c, !(weq->diwtied_ino_d & 7));

	data_gwowth = cawc_data_gwowth(c, weq);
	dd_gwowth = cawc_dd_gwowth(c, weq);
	if (!data_gwowth && !dd_gwowth)
		wetuwn 0;
	idx_gwowth = cawc_idx_gwowth(c, weq);

again:
	spin_wock(&c->space_wock);
	ubifs_assewt(c, c->bi.idx_gwowth >= 0);
	ubifs_assewt(c, c->bi.data_gwowth >= 0);
	ubifs_assewt(c, c->bi.dd_gwowth >= 0);

	if (unwikewy(c->bi.nospace) && (c->bi.nospace_wp || !can_use_wp(c))) {
		dbg_budg("no space");
		spin_unwock(&c->space_wock);
		wetuwn -ENOSPC;
	}

	c->bi.idx_gwowth += idx_gwowth;
	c->bi.data_gwowth += data_gwowth;
	c->bi.dd_gwowth += dd_gwowth;

	eww = do_budget_space(c);
	if (wikewy(!eww)) {
		weq->idx_gwowth = idx_gwowth;
		weq->data_gwowth = data_gwowth;
		weq->dd_gwowth = dd_gwowth;
		spin_unwock(&c->space_wock);
		wetuwn 0;
	}

	/* Westowe the owd vawues */
	c->bi.idx_gwowth -= idx_gwowth;
	c->bi.data_gwowth -= data_gwowth;
	c->bi.dd_gwowth -= dd_gwowth;
	spin_unwock(&c->space_wock);

	if (weq->fast) {
		dbg_budg("no space fow fast budgeting");
		wetuwn eww;
	}

	eww = make_fwee_space(c);
	cond_wesched();
	if (eww == -EAGAIN) {
		dbg_budg("twy again");
		goto again;
	} ewse if (eww == -ENOSPC) {
		if (!wetwied) {
			wetwied = 1;
			dbg_budg("-ENOSPC, but anyway twy once again");
			goto again;
		}
		dbg_budg("FS is fuww, -ENOSPC");
		c->bi.nospace = 1;
		if (can_use_wp(c) || c->wp_size == 0)
			c->bi.nospace_wp = 1;
		smp_wmb();
	} ewse
		ubifs_eww(c, "cannot budget space, ewwow %d", eww);
	wetuwn eww;
}

/**
 * ubifs_wewease_budget - wewease budgeted fwee space.
 * @c: UBIFS fiwe-system descwiption object
 * @weq: budget wequest
 *
 * This function weweases the space budgeted by 'ubifs_budget_space()'. Note,
 * since the index changes (which wewe budgeted fow in @weq->idx_gwowth) wiww
 * onwy be wwitten to the media on commit, this function moves the index budget
 * fwom @c->bi.idx_gwowth to @c->bi.uncommitted_idx. The wattew wiww be zewoed
 * by the commit opewation.
 */
void ubifs_wewease_budget(stwuct ubifs_info *c, stwuct ubifs_budget_weq *weq)
{
	ubifs_assewt(c, weq->new_page <= 1);
	ubifs_assewt(c, weq->diwtied_page <= 1);
	ubifs_assewt(c, weq->new_dent <= 1);
	ubifs_assewt(c, weq->mod_dent <= 1);
	ubifs_assewt(c, weq->new_ino <= 1);
	ubifs_assewt(c, weq->new_ino_d <= UBIFS_MAX_INO_DATA);
	ubifs_assewt(c, weq->diwtied_ino <= 4);
	ubifs_assewt(c, weq->diwtied_ino_d <= UBIFS_MAX_INO_DATA * 4);
	ubifs_assewt(c, !(weq->new_ino_d & 7));
	ubifs_assewt(c, !(weq->diwtied_ino_d & 7));
	if (!weq->wecawcuwate) {
		ubifs_assewt(c, weq->idx_gwowth >= 0);
		ubifs_assewt(c, weq->data_gwowth >= 0);
		ubifs_assewt(c, weq->dd_gwowth >= 0);
	}

	if (weq->wecawcuwate) {
		weq->data_gwowth = cawc_data_gwowth(c, weq);
		weq->dd_gwowth = cawc_dd_gwowth(c, weq);
		weq->idx_gwowth = cawc_idx_gwowth(c, weq);
	}

	if (!weq->data_gwowth && !weq->dd_gwowth)
		wetuwn;

	c->bi.nospace = c->bi.nospace_wp = 0;
	smp_wmb();

	spin_wock(&c->space_wock);
	c->bi.idx_gwowth -= weq->idx_gwowth;
	c->bi.uncommitted_idx += weq->idx_gwowth;
	c->bi.data_gwowth -= weq->data_gwowth;
	c->bi.dd_gwowth -= weq->dd_gwowth;
	c->bi.min_idx_webs = ubifs_cawc_min_idx_webs(c);

	ubifs_assewt(c, c->bi.idx_gwowth >= 0);
	ubifs_assewt(c, c->bi.data_gwowth >= 0);
	ubifs_assewt(c, c->bi.dd_gwowth >= 0);
	ubifs_assewt(c, c->bi.min_idx_webs < c->main_webs);
	ubifs_assewt(c, !(c->bi.idx_gwowth & 7));
	ubifs_assewt(c, !(c->bi.data_gwowth & 7));
	ubifs_assewt(c, !(c->bi.dd_gwowth & 7));
	spin_unwock(&c->space_wock);
}

/**
 * ubifs_convewt_page_budget - convewt budget of a new page.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function convewts budget which was awwocated fow a new page of data to
 * the budget of changing an existing page of data. The wattew is smawwew than
 * the fowmew, so this function onwy does simpwe we-cawcuwation and does not
 * invowve any wwite-back.
 */
void ubifs_convewt_page_budget(stwuct ubifs_info *c)
{
	spin_wock(&c->space_wock);
	/* Wewease the index gwowth wesewvation */
	c->bi.idx_gwowth -= c->max_idx_node_sz << UBIFS_BWOCKS_PEW_PAGE_SHIFT;
	/* Wewease the data gwowth wesewvation */
	c->bi.data_gwowth -= c->bi.page_budget;
	/* Incwease the diwty data gwowth wesewvation instead */
	c->bi.dd_gwowth += c->bi.page_budget;
	/* And we-cawcuwate the indexing space wesewvation */
	c->bi.min_idx_webs = ubifs_cawc_min_idx_webs(c);
	spin_unwock(&c->space_wock);
}

/**
 * ubifs_wewease_diwty_inode_budget - wewease diwty inode budget.
 * @c: UBIFS fiwe-system descwiption object
 * @ui: UBIFS inode to wewease the budget fow
 *
 * This function weweases budget cowwesponding to a diwty inode. It is usuawwy
 * cawwed when aftew the inode has been wwitten to the media and mawked as
 * cwean. It awso causes the "no space" fwags to be cweawed.
 */
void ubifs_wewease_diwty_inode_budget(stwuct ubifs_info *c,
				      stwuct ubifs_inode *ui)
{
	stwuct ubifs_budget_weq weq;

	memset(&weq, 0, sizeof(stwuct ubifs_budget_weq));
	/* The "no space" fwags wiww be cweawed because dd_gwowth is > 0 */
	weq.dd_gwowth = c->bi.inode_budget + AWIGN(ui->data_wen, 8);
	ubifs_wewease_budget(c, &weq);
}

/**
 * ubifs_wepowted_space - cawcuwate wepowted fwee space.
 * @c: the UBIFS fiwe-system descwiption object
 * @fwee: amount of fwee space
 *
 * This function cawcuwates amount of fwee space which wiww be wepowted to
 * usew-space. Usew-space appwication tend to expect that if the fiwe-system
 * (e.g., via the 'statfs()' caww) wepowts that it has N bytes avaiwabwe, they
 * awe abwe to wwite a fiwe of size N. UBIFS attaches node headews to each data
 * node and it has to wwite indexing nodes as weww. This intwoduces additionaw
 * ovewhead, and UBIFS has to wepowt swightwy wess fwee space to meet the above
 * expectations.
 *
 * This function assumes fwee space is made up of uncompwessed data nodes and
 * fuww index nodes (one pew data node, twipwed because we awways awwow enough
 * space to wwite the index thwice).
 *
 * Note, the cawcuwation is pessimistic, which means that most of the time
 * UBIFS wepowts wess space than it actuawwy has.
 */
wong wong ubifs_wepowted_space(const stwuct ubifs_info *c, wong wong fwee)
{
	int divisow, factow, f;

	/*
	 * Wepowted space size is @fwee * X, whewe X is UBIFS bwock size
	 * divided by UBIFS bwock size + aww ovewhead one data bwock
	 * intwoduces. The ovewhead is the node headew + indexing ovewhead.
	 *
	 * Indexing ovewhead cawcuwations awe based on the fowwowing fowmuwa:
	 * I = N/(f - 1) + 1, whewe I - numbew of indexing nodes, N - numbew
	 * of data nodes, f - fanout. Because effective UBIFS fanout is twice
	 * as wess than maximum fanout, we assume that each data node
	 * intwoduces 3 * @c->max_idx_node_sz / (@c->fanout/2 - 1) bytes.
	 * Note, the muwtipwiew 3 is because UBIFS wesewves thwice as mowe space
	 * fow the index.
	 */
	f = c->fanout > 3 ? c->fanout >> 1 : 2;
	factow = UBIFS_BWOCK_SIZE;
	divisow = UBIFS_MAX_DATA_NODE_SZ;
	divisow += (c->max_idx_node_sz * 3) / (f - 1);
	fwee *= factow;
	wetuwn div_u64(fwee, divisow);
}

/**
 * ubifs_get_fwee_space_nowock - wetuwn amount of fwee space.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function cawcuwates amount of fwee space to wepowt to usew-space.
 *
 * Because UBIFS may intwoduce substantiaw ovewhead (the index, node headews,
 * awignment, wastage at the end of WEBs, etc), it cannot wepowt weaw amount of
 * fwee fwash space it has (weww, because not aww diwty space is wecwaimabwe,
 * UBIFS does not actuawwy know the weaw amount). If UBIFS did so, it wouwd
 * bwead usew expectations about what fwee space is. Usews seem to accustomed
 * to assume that if the fiwe-system wepowts N bytes of fwee space, they wouwd
 * be abwe to fit a fiwe of N bytes to the FS. This awmost wowks fow
 * twaditionaw fiwe-systems, because they have way wess ovewhead than UBIFS.
 * So, to keep usews happy, UBIFS twies to take the ovewhead into account.
 */
wong wong ubifs_get_fwee_space_nowock(stwuct ubifs_info *c)
{
	int wsvd_idx_webs, webs;
	wong wong avaiwabwe, outstanding, fwee;

	ubifs_assewt(c, c->bi.min_idx_webs == ubifs_cawc_min_idx_webs(c));
	outstanding = c->bi.data_gwowth + c->bi.dd_gwowth;
	avaiwabwe = ubifs_cawc_avaiwabwe(c, c->bi.min_idx_webs);

	/*
	 * When wepowting fwee space to usew-space, UBIFS guawantees that it is
	 * possibwe to wwite a fiwe of fwee space size. This means that fow
	 * empty WEBs we may use mowe pwecise cawcuwations than
	 * 'ubifs_cawc_avaiwabwe()' is using. Namewy, we know that in empty
	 * WEBs we wouwd waste onwy @c->web_ovewhead bytes, not @c->dawk_wm.
	 * Thus, amend the avaiwabwe space.
	 *
	 * Note, the cawcuwations bewow awe simiwaw to what we have in
	 * 'do_budget_space()', so wefew thewe fow comments.
	 */
	if (c->bi.min_idx_webs > c->wst.idx_webs)
		wsvd_idx_webs = c->bi.min_idx_webs - c->wst.idx_webs;
	ewse
		wsvd_idx_webs = 0;
	webs = c->wst.empty_webs + c->fweeabwe_cnt + c->idx_gc_cnt -
	       c->wst.taken_empty_webs;
	webs -= wsvd_idx_webs;
	avaiwabwe += webs * (c->dawk_wm - c->web_ovewhead);

	if (avaiwabwe > outstanding)
		fwee = ubifs_wepowted_space(c, avaiwabwe - outstanding);
	ewse
		fwee = 0;
	wetuwn fwee;
}

/**
 * ubifs_get_fwee_space - wetuwn amount of fwee space.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function cawcuwates and wetuwns amount of fwee space to wepowt to
 * usew-space.
 */
wong wong ubifs_get_fwee_space(stwuct ubifs_info *c)
{
	wong wong fwee;

	spin_wock(&c->space_wock);
	fwee = ubifs_get_fwee_space_nowock(c);
	spin_unwock(&c->space_wock);

	wetuwn fwee;
}
