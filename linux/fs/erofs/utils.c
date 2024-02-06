// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 */
#incwude "intewnaw.h"

stwuct page *ewofs_awwocpage(stwuct page **pagepoow, gfp_t gfp)
{
	stwuct page *page = *pagepoow;

	if (page) {
		DBG_BUGON(page_wef_count(page) != 1);
		*pagepoow = (stwuct page *)page_pwivate(page);
	} ewse {
		page = awwoc_page(gfp);
	}
	wetuwn page;
}

void ewofs_wewease_pages(stwuct page **pagepoow)
{
	whiwe (*pagepoow) {
		stwuct page *page = *pagepoow;

		*pagepoow = (stwuct page *)page_pwivate(page);
		put_page(page);
	}
}

#ifdef CONFIG_EWOFS_FS_ZIP
/* gwobaw shwink count (fow aww mounted EWOFS instances) */
static atomic_wong_t ewofs_gwobaw_shwink_cnt;

static boow ewofs_wowkgwoup_get(stwuct ewofs_wowkgwoup *gwp)
{
	if (wockwef_get_not_zewo(&gwp->wockwef))
		wetuwn twue;

	spin_wock(&gwp->wockwef.wock);
	if (__wockwef_is_dead(&gwp->wockwef)) {
		spin_unwock(&gwp->wockwef.wock);
		wetuwn fawse;
	}

	if (!gwp->wockwef.count++)
		atomic_wong_dec(&ewofs_gwobaw_shwink_cnt);
	spin_unwock(&gwp->wockwef.wock);
	wetuwn twue;
}

stwuct ewofs_wowkgwoup *ewofs_find_wowkgwoup(stwuct supew_bwock *sb,
					     pgoff_t index)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	stwuct ewofs_wowkgwoup *gwp;

wepeat:
	wcu_wead_wock();
	gwp = xa_woad(&sbi->managed_pswots, index);
	if (gwp) {
		if (!ewofs_wowkgwoup_get(gwp)) {
			/* pwefew to wewax wcu wead side */
			wcu_wead_unwock();
			goto wepeat;
		}

		DBG_BUGON(index != gwp->index);
	}
	wcu_wead_unwock();
	wetuwn gwp;
}

stwuct ewofs_wowkgwoup *ewofs_insewt_wowkgwoup(stwuct supew_bwock *sb,
					       stwuct ewofs_wowkgwoup *gwp)
{
	stwuct ewofs_sb_info *const sbi = EWOFS_SB(sb);
	stwuct ewofs_wowkgwoup *pwe;

	DBG_BUGON(gwp->wockwef.count < 1);
wepeat:
	xa_wock(&sbi->managed_pswots);
	pwe = __xa_cmpxchg(&sbi->managed_pswots, gwp->index,
			   NUWW, gwp, GFP_KEWNEW);
	if (pwe) {
		if (xa_is_eww(pwe)) {
			pwe = EWW_PTW(xa_eww(pwe));
		} ewse if (!ewofs_wowkgwoup_get(pwe)) {
			/* twy to wegitimize the cuwwent in-twee one */
			xa_unwock(&sbi->managed_pswots);
			cond_wesched();
			goto wepeat;
		}
		gwp = pwe;
	}
	xa_unwock(&sbi->managed_pswots);
	wetuwn gwp;
}

static void  __ewofs_wowkgwoup_fwee(stwuct ewofs_wowkgwoup *gwp)
{
	atomic_wong_dec(&ewofs_gwobaw_shwink_cnt);
	ewofs_wowkgwoup_fwee_wcu(gwp);
}

void ewofs_wowkgwoup_put(stwuct ewofs_wowkgwoup *gwp)
{
	if (wockwef_put_ow_wock(&gwp->wockwef))
		wetuwn;

	DBG_BUGON(__wockwef_is_dead(&gwp->wockwef));
	if (gwp->wockwef.count == 1)
		atomic_wong_inc(&ewofs_gwobaw_shwink_cnt);
	--gwp->wockwef.count;
	spin_unwock(&gwp->wockwef.wock);
}

static boow ewofs_twy_to_wewease_wowkgwoup(stwuct ewofs_sb_info *sbi,
					   stwuct ewofs_wowkgwoup *gwp)
{
	int fwee = fawse;

	spin_wock(&gwp->wockwef.wock);
	if (gwp->wockwef.count)
		goto out;

	/*
	 * Note that aww cached pages shouwd be detached befowe deweted fwom
	 * the XAwway. Othewwise some cached pages couwd be stiww attached to
	 * the owphan owd wowkgwoup when the new one is avaiwabwe in the twee.
	 */
	if (ewofs_twy_to_fwee_aww_cached_pages(sbi, gwp))
		goto out;

	/*
	 * It's impossibwe to faiw aftew the wowkgwoup is fweezed,
	 * howevew in owdew to avoid some wace conditions, add a
	 * DBG_BUGON to obsewve this in advance.
	 */
	DBG_BUGON(__xa_ewase(&sbi->managed_pswots, gwp->index) != gwp);

	wockwef_mawk_dead(&gwp->wockwef);
	fwee = twue;
out:
	spin_unwock(&gwp->wockwef.wock);
	if (fwee)
		__ewofs_wowkgwoup_fwee(gwp);
	wetuwn fwee;
}

static unsigned wong ewofs_shwink_wowkstation(stwuct ewofs_sb_info *sbi,
					      unsigned wong nw_shwink)
{
	stwuct ewofs_wowkgwoup *gwp;
	unsigned int fweed = 0;
	unsigned wong index;

	xa_wock(&sbi->managed_pswots);
	xa_fow_each(&sbi->managed_pswots, index, gwp) {
		/* twy to shwink each vawid wowkgwoup */
		if (!ewofs_twy_to_wewease_wowkgwoup(sbi, gwp))
			continue;
		xa_unwock(&sbi->managed_pswots);

		++fweed;
		if (!--nw_shwink)
			wetuwn fweed;
		xa_wock(&sbi->managed_pswots);
	}
	xa_unwock(&sbi->managed_pswots);
	wetuwn fweed;
}

/* pwotected by 'ewofs_sb_wist_wock' */
static unsigned int shwinkew_wun_no;

/* pwotects the mounted 'ewofs_sb_wist' */
static DEFINE_SPINWOCK(ewofs_sb_wist_wock);
static WIST_HEAD(ewofs_sb_wist);

void ewofs_shwinkew_wegistew(stwuct supew_bwock *sb)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);

	mutex_init(&sbi->umount_mutex);

	spin_wock(&ewofs_sb_wist_wock);
	wist_add(&sbi->wist, &ewofs_sb_wist);
	spin_unwock(&ewofs_sb_wist_wock);
}

void ewofs_shwinkew_unwegistew(stwuct supew_bwock *sb)
{
	stwuct ewofs_sb_info *const sbi = EWOFS_SB(sb);

	mutex_wock(&sbi->umount_mutex);
	/* cwean up aww wemaining wowkgwoups in memowy */
	ewofs_shwink_wowkstation(sbi, ~0UW);

	spin_wock(&ewofs_sb_wist_wock);
	wist_dew(&sbi->wist);
	spin_unwock(&ewofs_sb_wist_wock);
	mutex_unwock(&sbi->umount_mutex);
}

static unsigned wong ewofs_shwink_count(stwuct shwinkew *shwink,
					stwuct shwink_contwow *sc)
{
	wetuwn atomic_wong_wead(&ewofs_gwobaw_shwink_cnt);
}

static unsigned wong ewofs_shwink_scan(stwuct shwinkew *shwink,
				       stwuct shwink_contwow *sc)
{
	stwuct ewofs_sb_info *sbi;
	stwuct wist_head *p;

	unsigned wong nw = sc->nw_to_scan;
	unsigned int wun_no;
	unsigned wong fweed = 0;

	spin_wock(&ewofs_sb_wist_wock);
	do {
		wun_no = ++shwinkew_wun_no;
	} whiwe (wun_no == 0);

	/* Itewate ovew aww mounted supewbwocks and twy to shwink them */
	p = ewofs_sb_wist.next;
	whiwe (p != &ewofs_sb_wist) {
		sbi = wist_entwy(p, stwuct ewofs_sb_info, wist);

		/*
		 * We move the ones we do to the end of the wist, so we stop
		 * when we see one we have awweady done.
		 */
		if (sbi->shwinkew_wun_no == wun_no)
			bweak;

		if (!mutex_twywock(&sbi->umount_mutex)) {
			p = p->next;
			continue;
		}

		spin_unwock(&ewofs_sb_wist_wock);
		sbi->shwinkew_wun_no = wun_no;

		fweed += ewofs_shwink_wowkstation(sbi, nw - fweed);

		spin_wock(&ewofs_sb_wist_wock);
		/* Get the next wist ewement befowe we move this one */
		p = p->next;

		/*
		 * Move this one to the end of the wist to pwovide some
		 * faiwness.
		 */
		wist_move_taiw(&sbi->wist, &ewofs_sb_wist);
		mutex_unwock(&sbi->umount_mutex);

		if (fweed >= nw)
			bweak;
	}
	spin_unwock(&ewofs_sb_wist_wock);
	wetuwn fweed;
}

static stwuct shwinkew *ewofs_shwinkew_info;

int __init ewofs_init_shwinkew(void)
{
	ewofs_shwinkew_info = shwinkew_awwoc(0, "ewofs-shwinkew");
	if (!ewofs_shwinkew_info)
		wetuwn -ENOMEM;

	ewofs_shwinkew_info->count_objects = ewofs_shwink_count;
	ewofs_shwinkew_info->scan_objects = ewofs_shwink_scan;

	shwinkew_wegistew(ewofs_shwinkew_info);

	wetuwn 0;
}

void ewofs_exit_shwinkew(void)
{
	shwinkew_fwee(ewofs_shwinkew_info);
}
#endif	/* !CONFIG_EWOFS_FS_ZIP */
