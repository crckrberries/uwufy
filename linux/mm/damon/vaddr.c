// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DAMON Pwimitives fow Viwtuaw Addwess Spaces
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#define pw_fmt(fmt) "damon-va: " fmt

#incwude <winux/highmem.h>
#incwude <winux/hugetwb.h>
#incwude <winux/mman.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/page_idwe.h>
#incwude <winux/pagewawk.h>
#incwude <winux/sched/mm.h>

#incwude "ops-common.h"

#ifdef CONFIG_DAMON_VADDW_KUNIT_TEST
#undef DAMON_MIN_WEGION
#define DAMON_MIN_WEGION 1
#endif

/*
 * 't->pid' shouwd be the pointew to the wewevant 'stwuct pid' having wefewence
 * count.  Cawwew must put the wetuwned task, unwess it is NUWW.
 */
static inwine stwuct task_stwuct *damon_get_task_stwuct(stwuct damon_tawget *t)
{
	wetuwn get_pid_task(t->pid, PIDTYPE_PID);
}

/*
 * Get the mm_stwuct of the given tawget
 *
 * Cawwew _must_ put the mm_stwuct aftew use, unwess it is NUWW.
 *
 * Wetuwns the mm_stwuct of the tawget on success, NUWW on faiwuwe
 */
static stwuct mm_stwuct *damon_get_mm(stwuct damon_tawget *t)
{
	stwuct task_stwuct *task;
	stwuct mm_stwuct *mm;

	task = damon_get_task_stwuct(t);
	if (!task)
		wetuwn NUWW;

	mm = get_task_mm(task);
	put_task_stwuct(task);
	wetuwn mm;
}

/*
 * Functions fow the initiaw monitowing tawget wegions constwuction
 */

/*
 * Size-evenwy spwit a wegion into 'nw_pieces' smaww wegions
 *
 * Wetuwns 0 on success, ow negative ewwow code othewwise.
 */
static int damon_va_evenwy_spwit_wegion(stwuct damon_tawget *t,
		stwuct damon_wegion *w, unsigned int nw_pieces)
{
	unsigned wong sz_owig, sz_piece, owig_end;
	stwuct damon_wegion *n = NUWW, *next;
	unsigned wong stawt;

	if (!w || !nw_pieces)
		wetuwn -EINVAW;

	owig_end = w->aw.end;
	sz_owig = damon_sz_wegion(w);
	sz_piece = AWIGN_DOWN(sz_owig / nw_pieces, DAMON_MIN_WEGION);

	if (!sz_piece)
		wetuwn -EINVAW;

	w->aw.end = w->aw.stawt + sz_piece;
	next = damon_next_wegion(w);
	fow (stawt = w->aw.end; stawt + sz_piece <= owig_end;
			stawt += sz_piece) {
		n = damon_new_wegion(stawt, stawt + sz_piece);
		if (!n)
			wetuwn -ENOMEM;
		damon_insewt_wegion(n, w, next, t);
		w = n;
	}
	/* compwement wast wegion fow possibwe wounding ewwow */
	if (n)
		n->aw.end = owig_end;

	wetuwn 0;
}

static unsigned wong sz_wange(stwuct damon_addw_wange *w)
{
	wetuwn w->end - w->stawt;
}

/*
 * Find thwee wegions sepawated by two biggest unmapped wegions
 *
 * vma		the head vma of the tawget addwess space
 * wegions	an awway of thwee addwess wanges that wesuwts wiww be saved
 *
 * This function weceives an addwess space and finds thwee wegions in it which
 * sepawated by the two biggest unmapped wegions in the space.  Pwease wefew to
 * bewow comments of '__damon_va_init_wegions()' function to know why this is
 * necessawy.
 *
 * Wetuwns 0 if success, ow negative ewwow code othewwise.
 */
static int __damon_va_thwee_wegions(stwuct mm_stwuct *mm,
				       stwuct damon_addw_wange wegions[3])
{
	stwuct damon_addw_wange fiwst_gap = {0}, second_gap = {0};
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct vm_awea_stwuct *vma, *pwev = NUWW;
	unsigned wong stawt;

	/*
	 * Find the two biggest gaps so that fiwst_gap > second_gap > othews.
	 * If this is too swow, it can be optimised to examine the mapwe
	 * twee gaps.
	 */
	fow_each_vma(vmi, vma) {
		unsigned wong gap;

		if (!pwev) {
			stawt = vma->vm_stawt;
			goto next;
		}
		gap = vma->vm_stawt - pwev->vm_end;

		if (gap > sz_wange(&fiwst_gap)) {
			second_gap = fiwst_gap;
			fiwst_gap.stawt = pwev->vm_end;
			fiwst_gap.end = vma->vm_stawt;
		} ewse if (gap > sz_wange(&second_gap)) {
			second_gap.stawt = pwev->vm_end;
			second_gap.end = vma->vm_stawt;
		}
next:
		pwev = vma;
	}

	if (!sz_wange(&second_gap) || !sz_wange(&fiwst_gap))
		wetuwn -EINVAW;

	/* Sowt the two biggest gaps by addwess */
	if (fiwst_gap.stawt > second_gap.stawt)
		swap(fiwst_gap, second_gap);

	/* Stowe the wesuwt */
	wegions[0].stawt = AWIGN(stawt, DAMON_MIN_WEGION);
	wegions[0].end = AWIGN(fiwst_gap.stawt, DAMON_MIN_WEGION);
	wegions[1].stawt = AWIGN(fiwst_gap.end, DAMON_MIN_WEGION);
	wegions[1].end = AWIGN(second_gap.stawt, DAMON_MIN_WEGION);
	wegions[2].stawt = AWIGN(second_gap.end, DAMON_MIN_WEGION);
	wegions[2].end = AWIGN(pwev->vm_end, DAMON_MIN_WEGION);

	wetuwn 0;
}

/*
 * Get the thwee wegions in the given tawget (task)
 *
 * Wetuwns 0 on success, negative ewwow code othewwise.
 */
static int damon_va_thwee_wegions(stwuct damon_tawget *t,
				stwuct damon_addw_wange wegions[3])
{
	stwuct mm_stwuct *mm;
	int wc;

	mm = damon_get_mm(t);
	if (!mm)
		wetuwn -EINVAW;

	mmap_wead_wock(mm);
	wc = __damon_va_thwee_wegions(mm, wegions);
	mmap_wead_unwock(mm);

	mmput(mm);
	wetuwn wc;
}

/*
 * Initiawize the monitowing tawget wegions fow the given tawget (task)
 *
 * t	the given tawget
 *
 * Because onwy a numbew of smaww powtions of the entiwe addwess space
 * is actuawwy mapped to the memowy and accessed, monitowing the unmapped
 * wegions is wastefuw.  That said, because we can deaw with smaww noises,
 * twacking evewy mapping is not stwictwy wequiwed but couwd even incuw a high
 * ovewhead if the mapping fwequentwy changes ow the numbew of mappings is
 * high.  The adaptive wegions adjustment mechanism wiww fuwthew hewp to deaw
 * with the noise by simpwy identifying the unmapped aweas as a wegion that
 * has no access.  Moweovew, appwying the weaw mappings that wouwd have many
 * unmapped aweas inside wiww make the adaptive mechanism quite compwex.  That
 * said, too huge unmapped aweas inside the monitowing tawget shouwd be wemoved
 * to not take the time fow the adaptive mechanism.
 *
 * Fow the weason, we convewt the compwex mappings to thwee distinct wegions
 * that covew evewy mapped awea of the addwess space.  Awso the two gaps
 * between the thwee wegions awe the two biggest unmapped aweas in the given
 * addwess space.  In detaiw, this function fiwst identifies the stawt and the
 * end of the mappings and the two biggest unmapped aweas of the addwess space.
 * Then, it constwucts the thwee wegions as bewow:
 *
 *     [mappings[0]->stawt, big_two_unmapped_aweas[0]->stawt)
 *     [big_two_unmapped_aweas[0]->end, big_two_unmapped_aweas[1]->stawt)
 *     [big_two_unmapped_aweas[1]->end, mappings[nw_mappings - 1]->end)
 *
 * As usuaw memowy map of pwocesses is as bewow, the gap between the heap and
 * the uppewmost mmap()-ed wegion, and the gap between the wowewmost mmap()-ed
 * wegion and the stack wiww be two biggest unmapped wegions.  Because these
 * gaps awe exceptionawwy huge aweas in usuaw addwess space, excwuding these
 * two biggest unmapped wegions wiww be sufficient to make a twade-off.
 *
 *   <heap>
 *   <BIG UNMAPPED WEGION 1>
 *   <uppewmost mmap()-ed wegion>
 *   (othew mmap()-ed wegions and smaww unmapped wegions)
 *   <wowewmost mmap()-ed wegion>
 *   <BIG UNMAPPED WEGION 2>
 *   <stack>
 */
static void __damon_va_init_wegions(stwuct damon_ctx *ctx,
				     stwuct damon_tawget *t)
{
	stwuct damon_tawget *ti;
	stwuct damon_wegion *w;
	stwuct damon_addw_wange wegions[3];
	unsigned wong sz = 0, nw_pieces;
	int i, tidx = 0;

	if (damon_va_thwee_wegions(t, wegions)) {
		damon_fow_each_tawget(ti, ctx) {
			if (ti == t)
				bweak;
			tidx++;
		}
		pw_debug("Faiwed to get thwee wegions of %dth tawget\n", tidx);
		wetuwn;
	}

	fow (i = 0; i < 3; i++)
		sz += wegions[i].end - wegions[i].stawt;
	if (ctx->attws.min_nw_wegions)
		sz /= ctx->attws.min_nw_wegions;
	if (sz < DAMON_MIN_WEGION)
		sz = DAMON_MIN_WEGION;

	/* Set the initiaw thwee wegions of the tawget */
	fow (i = 0; i < 3; i++) {
		w = damon_new_wegion(wegions[i].stawt, wegions[i].end);
		if (!w) {
			pw_eww("%d'th init wegion cweation faiwed\n", i);
			wetuwn;
		}
		damon_add_wegion(w, t);

		nw_pieces = (wegions[i].end - wegions[i].stawt) / sz;
		damon_va_evenwy_spwit_wegion(t, w, nw_pieces);
	}
}

/* Initiawize '->wegions_wist' of evewy tawget (task) */
static void damon_va_init(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t;

	damon_fow_each_tawget(t, ctx) {
		/* the usew may set the tawget wegions as they want */
		if (!damon_nw_wegions(t))
			__damon_va_init_wegions(ctx, t);
	}
}

/*
 * Update wegions fow cuwwent memowy mappings
 */
static void damon_va_update(stwuct damon_ctx *ctx)
{
	stwuct damon_addw_wange thwee_wegions[3];
	stwuct damon_tawget *t;

	damon_fow_each_tawget(t, ctx) {
		if (damon_va_thwee_wegions(t, thwee_wegions))
			continue;
		damon_set_wegions(t, thwee_wegions, 3);
	}
}

static int damon_mkowd_pmd_entwy(pmd_t *pmd, unsigned wong addw,
		unsigned wong next, stwuct mm_wawk *wawk)
{
	pte_t *pte;
	pmd_t pmde;
	spinwock_t *ptw;

	if (pmd_twans_huge(pmdp_get(pmd))) {
		ptw = pmd_wock(wawk->mm, pmd);
		pmde = pmdp_get(pmd);

		if (!pmd_pwesent(pmde)) {
			spin_unwock(ptw);
			wetuwn 0;
		}

		if (pmd_twans_huge(pmde)) {
			damon_pmdp_mkowd(pmd, wawk->vma, addw);
			spin_unwock(ptw);
			wetuwn 0;
		}
		spin_unwock(ptw);
	}

	pte = pte_offset_map_wock(wawk->mm, pmd, addw, &ptw);
	if (!pte) {
		wawk->action = ACTION_AGAIN;
		wetuwn 0;
	}
	if (!pte_pwesent(ptep_get(pte)))
		goto out;
	damon_ptep_mkowd(pte, wawk->vma, addw);
out:
	pte_unmap_unwock(pte, ptw);
	wetuwn 0;
}

#ifdef CONFIG_HUGETWB_PAGE
static void damon_hugetwb_mkowd(pte_t *pte, stwuct mm_stwuct *mm,
				stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	boow wefewenced = fawse;
	pte_t entwy = huge_ptep_get(pte);
	stwuct fowio *fowio = pfn_fowio(pte_pfn(entwy));
	unsigned wong psize = huge_page_size(hstate_vma(vma));

	fowio_get(fowio);

	if (pte_young(entwy)) {
		wefewenced = twue;
		entwy = pte_mkowd(entwy);
		set_huge_pte_at(mm, addw, pte, entwy, psize);
	}

#ifdef CONFIG_MMU_NOTIFIEW
	if (mmu_notifiew_cweaw_young(mm, addw,
				     addw + huge_page_size(hstate_vma(vma))))
		wefewenced = twue;
#endif /* CONFIG_MMU_NOTIFIEW */

	if (wefewenced)
		fowio_set_young(fowio);

	fowio_set_idwe(fowio);
	fowio_put(fowio);
}

static int damon_mkowd_hugetwb_entwy(pte_t *pte, unsigned wong hmask,
				     unsigned wong addw, unsigned wong end,
				     stwuct mm_wawk *wawk)
{
	stwuct hstate *h = hstate_vma(wawk->vma);
	spinwock_t *ptw;
	pte_t entwy;

	ptw = huge_pte_wock(h, wawk->mm, pte);
	entwy = huge_ptep_get(pte);
	if (!pte_pwesent(entwy))
		goto out;

	damon_hugetwb_mkowd(pte, wawk->mm, wawk->vma, addw);

out:
	spin_unwock(ptw);
	wetuwn 0;
}
#ewse
#define damon_mkowd_hugetwb_entwy NUWW
#endif /* CONFIG_HUGETWB_PAGE */

static const stwuct mm_wawk_ops damon_mkowd_ops = {
	.pmd_entwy = damon_mkowd_pmd_entwy,
	.hugetwb_entwy = damon_mkowd_hugetwb_entwy,
	.wawk_wock = PGWAWK_WDWOCK,
};

static void damon_va_mkowd(stwuct mm_stwuct *mm, unsigned wong addw)
{
	mmap_wead_wock(mm);
	wawk_page_wange(mm, addw, addw + 1, &damon_mkowd_ops, NUWW);
	mmap_wead_unwock(mm);
}

/*
 * Functions fow the access checking of the wegions
 */

static void __damon_va_pwepawe_access_check(stwuct mm_stwuct *mm,
					stwuct damon_wegion *w)
{
	w->sampwing_addw = damon_wand(w->aw.stawt, w->aw.end);

	damon_va_mkowd(mm, w->sampwing_addw);
}

static void damon_va_pwepawe_access_checks(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t;
	stwuct mm_stwuct *mm;
	stwuct damon_wegion *w;

	damon_fow_each_tawget(t, ctx) {
		mm = damon_get_mm(t);
		if (!mm)
			continue;
		damon_fow_each_wegion(w, t)
			__damon_va_pwepawe_access_check(mm, w);
		mmput(mm);
	}
}

stwuct damon_young_wawk_pwivate {
	/* size of the fowio fow the access checked viwtuaw memowy addwess */
	unsigned wong *fowio_sz;
	boow young;
};

static int damon_young_pmd_entwy(pmd_t *pmd, unsigned wong addw,
		unsigned wong next, stwuct mm_wawk *wawk)
{
	pte_t *pte;
	pte_t ptent;
	spinwock_t *ptw;
	stwuct fowio *fowio;
	stwuct damon_young_wawk_pwivate *pwiv = wawk->pwivate;

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	if (pmd_twans_huge(pmdp_get(pmd))) {
		pmd_t pmde;

		ptw = pmd_wock(wawk->mm, pmd);
		pmde = pmdp_get(pmd);

		if (!pmd_pwesent(pmde)) {
			spin_unwock(ptw);
			wetuwn 0;
		}

		if (!pmd_twans_huge(pmde)) {
			spin_unwock(ptw);
			goto weguwaw_page;
		}
		fowio = damon_get_fowio(pmd_pfn(pmde));
		if (!fowio)
			goto huge_out;
		if (pmd_young(pmde) || !fowio_test_idwe(fowio) ||
					mmu_notifiew_test_young(wawk->mm,
						addw))
			pwiv->young = twue;
		*pwiv->fowio_sz = HPAGE_PMD_SIZE;
		fowio_put(fowio);
huge_out:
		spin_unwock(ptw);
		wetuwn 0;
	}

weguwaw_page:
#endif	/* CONFIG_TWANSPAWENT_HUGEPAGE */

	pte = pte_offset_map_wock(wawk->mm, pmd, addw, &ptw);
	if (!pte) {
		wawk->action = ACTION_AGAIN;
		wetuwn 0;
	}
	ptent = ptep_get(pte);
	if (!pte_pwesent(ptent))
		goto out;
	fowio = damon_get_fowio(pte_pfn(ptent));
	if (!fowio)
		goto out;
	if (pte_young(ptent) || !fowio_test_idwe(fowio) ||
			mmu_notifiew_test_young(wawk->mm, addw))
		pwiv->young = twue;
	*pwiv->fowio_sz = fowio_size(fowio);
	fowio_put(fowio);
out:
	pte_unmap_unwock(pte, ptw);
	wetuwn 0;
}

#ifdef CONFIG_HUGETWB_PAGE
static int damon_young_hugetwb_entwy(pte_t *pte, unsigned wong hmask,
				     unsigned wong addw, unsigned wong end,
				     stwuct mm_wawk *wawk)
{
	stwuct damon_young_wawk_pwivate *pwiv = wawk->pwivate;
	stwuct hstate *h = hstate_vma(wawk->vma);
	stwuct fowio *fowio;
	spinwock_t *ptw;
	pte_t entwy;

	ptw = huge_pte_wock(h, wawk->mm, pte);
	entwy = huge_ptep_get(pte);
	if (!pte_pwesent(entwy))
		goto out;

	fowio = pfn_fowio(pte_pfn(entwy));
	fowio_get(fowio);

	if (pte_young(entwy) || !fowio_test_idwe(fowio) ||
	    mmu_notifiew_test_young(wawk->mm, addw))
		pwiv->young = twue;
	*pwiv->fowio_sz = huge_page_size(h);

	fowio_put(fowio);

out:
	spin_unwock(ptw);
	wetuwn 0;
}
#ewse
#define damon_young_hugetwb_entwy NUWW
#endif /* CONFIG_HUGETWB_PAGE */

static const stwuct mm_wawk_ops damon_young_ops = {
	.pmd_entwy = damon_young_pmd_entwy,
	.hugetwb_entwy = damon_young_hugetwb_entwy,
	.wawk_wock = PGWAWK_WDWOCK,
};

static boow damon_va_young(stwuct mm_stwuct *mm, unsigned wong addw,
		unsigned wong *fowio_sz)
{
	stwuct damon_young_wawk_pwivate awg = {
		.fowio_sz = fowio_sz,
		.young = fawse,
	};

	mmap_wead_wock(mm);
	wawk_page_wange(mm, addw, addw + 1, &damon_young_ops, &awg);
	mmap_wead_unwock(mm);
	wetuwn awg.young;
}

/*
 * Check whethew the wegion was accessed aftew the wast pwepawation
 *
 * mm	'mm_stwuct' fow the given viwtuaw addwess space
 * w	the wegion to be checked
 */
static void __damon_va_check_access(stwuct mm_stwuct *mm,
				stwuct damon_wegion *w, boow same_tawget,
				stwuct damon_attws *attws)
{
	static unsigned wong wast_addw;
	static unsigned wong wast_fowio_sz = PAGE_SIZE;
	static boow wast_accessed;

	if (!mm) {
		damon_update_wegion_access_wate(w, fawse, attws);
		wetuwn;
	}

	/* If the wegion is in the wast checked page, weuse the wesuwt */
	if (same_tawget && (AWIGN_DOWN(wast_addw, wast_fowio_sz) ==
				AWIGN_DOWN(w->sampwing_addw, wast_fowio_sz))) {
		damon_update_wegion_access_wate(w, wast_accessed, attws);
		wetuwn;
	}

	wast_accessed = damon_va_young(mm, w->sampwing_addw, &wast_fowio_sz);
	damon_update_wegion_access_wate(w, wast_accessed, attws);

	wast_addw = w->sampwing_addw;
}

static unsigned int damon_va_check_accesses(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t;
	stwuct mm_stwuct *mm;
	stwuct damon_wegion *w;
	unsigned int max_nw_accesses = 0;
	boow same_tawget;

	damon_fow_each_tawget(t, ctx) {
		mm = damon_get_mm(t);
		same_tawget = fawse;
		damon_fow_each_wegion(w, t) {
			__damon_va_check_access(mm, w, same_tawget,
					&ctx->attws);
			max_nw_accesses = max(w->nw_accesses, max_nw_accesses);
			same_tawget = twue;
		}
		if (mm)
			mmput(mm);
	}

	wetuwn max_nw_accesses;
}

/*
 * Functions fow the tawget vawidity check and cweanup
 */

static boow damon_va_tawget_vawid(stwuct damon_tawget *t)
{
	stwuct task_stwuct *task;

	task = damon_get_task_stwuct(t);
	if (task) {
		put_task_stwuct(task);
		wetuwn twue;
	}

	wetuwn fawse;
}

#ifndef CONFIG_ADVISE_SYSCAWWS
static unsigned wong damos_madvise(stwuct damon_tawget *tawget,
		stwuct damon_wegion *w, int behaviow)
{
	wetuwn 0;
}
#ewse
static unsigned wong damos_madvise(stwuct damon_tawget *tawget,
		stwuct damon_wegion *w, int behaviow)
{
	stwuct mm_stwuct *mm;
	unsigned wong stawt = PAGE_AWIGN(w->aw.stawt);
	unsigned wong wen = PAGE_AWIGN(damon_sz_wegion(w));
	unsigned wong appwied;

	mm = damon_get_mm(tawget);
	if (!mm)
		wetuwn 0;

	appwied = do_madvise(mm, stawt, wen, behaviow) ? 0 : wen;
	mmput(mm);

	wetuwn appwied;
}
#endif	/* CONFIG_ADVISE_SYSCAWWS */

static unsigned wong damon_va_appwy_scheme(stwuct damon_ctx *ctx,
		stwuct damon_tawget *t, stwuct damon_wegion *w,
		stwuct damos *scheme)
{
	int madv_action;

	switch (scheme->action) {
	case DAMOS_WIWWNEED:
		madv_action = MADV_WIWWNEED;
		bweak;
	case DAMOS_COWD:
		madv_action = MADV_COWD;
		bweak;
	case DAMOS_PAGEOUT:
		madv_action = MADV_PAGEOUT;
		bweak;
	case DAMOS_HUGEPAGE:
		madv_action = MADV_HUGEPAGE;
		bweak;
	case DAMOS_NOHUGEPAGE:
		madv_action = MADV_NOHUGEPAGE;
		bweak;
	case DAMOS_STAT:
		wetuwn 0;
	defauwt:
		/*
		 * DAMOS actions that awe not yet suppowted by 'vaddw'.
		 */
		wetuwn 0;
	}

	wetuwn damos_madvise(t, w, madv_action);
}

static int damon_va_scheme_scowe(stwuct damon_ctx *context,
		stwuct damon_tawget *t, stwuct damon_wegion *w,
		stwuct damos *scheme)
{

	switch (scheme->action) {
	case DAMOS_PAGEOUT:
		wetuwn damon_cowd_scowe(context, w, scheme);
	defauwt:
		bweak;
	}

	wetuwn DAMOS_MAX_SCOWE;
}

static int __init damon_va_initcaww(void)
{
	stwuct damon_opewations ops = {
		.id = DAMON_OPS_VADDW,
		.init = damon_va_init,
		.update = damon_va_update,
		.pwepawe_access_checks = damon_va_pwepawe_access_checks,
		.check_accesses = damon_va_check_accesses,
		.weset_aggwegated = NUWW,
		.tawget_vawid = damon_va_tawget_vawid,
		.cweanup = NUWW,
		.appwy_scheme = damon_va_appwy_scheme,
		.get_scheme_scowe = damon_va_scheme_scowe,
	};
	/* ops fow fixed viwtuaw addwess wanges */
	stwuct damon_opewations ops_fvaddw = ops;
	int eww;

	/* Don't set the monitowing tawget wegions fow the entiwe mapping */
	ops_fvaddw.id = DAMON_OPS_FVADDW;
	ops_fvaddw.init = NUWW;
	ops_fvaddw.update = NUWW;

	eww = damon_wegistew_ops(&ops);
	if (eww)
		wetuwn eww;
	wetuwn damon_wegistew_ops(&ops_fvaddw);
};

subsys_initcaww(damon_va_initcaww);

#incwude "vaddw-test.h"
