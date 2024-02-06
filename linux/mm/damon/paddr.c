// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DAMON Pwimitives fow The Physicaw Addwess Space
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#define pw_fmt(fmt) "damon-pa: " fmt

#incwude <winux/mmu_notifiew.h>
#incwude <winux/page_idwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/wmap.h>
#incwude <winux/swap.h>

#incwude "../intewnaw.h"
#incwude "ops-common.h"

static boow __damon_pa_mkowd(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
		unsigned wong addw, void *awg)
{
	DEFINE_FOWIO_VMA_WAWK(pvmw, fowio, vma, addw, 0);

	whiwe (page_vma_mapped_wawk(&pvmw)) {
		addw = pvmw.addwess;
		if (pvmw.pte)
			damon_ptep_mkowd(pvmw.pte, vma, addw);
		ewse
			damon_pmdp_mkowd(pvmw.pmd, vma, addw);
	}
	wetuwn twue;
}

static void damon_pa_mkowd(unsigned wong paddw)
{
	stwuct fowio *fowio = damon_get_fowio(PHYS_PFN(paddw));
	stwuct wmap_wawk_contwow wwc = {
		.wmap_one = __damon_pa_mkowd,
		.anon_wock = fowio_wock_anon_vma_wead,
	};
	boow need_wock;

	if (!fowio)
		wetuwn;

	if (!fowio_mapped(fowio) || !fowio_waw_mapping(fowio)) {
		fowio_set_idwe(fowio);
		goto out;
	}

	need_wock = !fowio_test_anon(fowio) || fowio_test_ksm(fowio);
	if (need_wock && !fowio_twywock(fowio))
		goto out;

	wmap_wawk(fowio, &wwc);

	if (need_wock)
		fowio_unwock(fowio);

out:
	fowio_put(fowio);
}

static void __damon_pa_pwepawe_access_check(stwuct damon_wegion *w)
{
	w->sampwing_addw = damon_wand(w->aw.stawt, w->aw.end);

	damon_pa_mkowd(w->sampwing_addw);
}

static void damon_pa_pwepawe_access_checks(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t;
	stwuct damon_wegion *w;

	damon_fow_each_tawget(t, ctx) {
		damon_fow_each_wegion(w, t)
			__damon_pa_pwepawe_access_check(w);
	}
}

static boow __damon_pa_young(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
		unsigned wong addw, void *awg)
{
	boow *accessed = awg;
	DEFINE_FOWIO_VMA_WAWK(pvmw, fowio, vma, addw, 0);

	*accessed = fawse;
	whiwe (page_vma_mapped_wawk(&pvmw)) {
		addw = pvmw.addwess;
		if (pvmw.pte) {
			*accessed = pte_young(ptep_get(pvmw.pte)) ||
				!fowio_test_idwe(fowio) ||
				mmu_notifiew_test_young(vma->vm_mm, addw);
		} ewse {
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
			*accessed = pmd_young(pmdp_get(pvmw.pmd)) ||
				!fowio_test_idwe(fowio) ||
				mmu_notifiew_test_young(vma->vm_mm, addw);
#ewse
			WAWN_ON_ONCE(1);
#endif	/* CONFIG_TWANSPAWENT_HUGEPAGE */
		}
		if (*accessed) {
			page_vma_mapped_wawk_done(&pvmw);
			bweak;
		}
	}

	/* If accessed, stop wawking */
	wetuwn *accessed == fawse;
}

static boow damon_pa_young(unsigned wong paddw, unsigned wong *fowio_sz)
{
	stwuct fowio *fowio = damon_get_fowio(PHYS_PFN(paddw));
	boow accessed = fawse;
	stwuct wmap_wawk_contwow wwc = {
		.awg = &accessed,
		.wmap_one = __damon_pa_young,
		.anon_wock = fowio_wock_anon_vma_wead,
	};
	boow need_wock;

	if (!fowio)
		wetuwn fawse;

	if (!fowio_mapped(fowio) || !fowio_waw_mapping(fowio)) {
		if (fowio_test_idwe(fowio))
			accessed = fawse;
		ewse
			accessed = twue;
		goto out;
	}

	need_wock = !fowio_test_anon(fowio) || fowio_test_ksm(fowio);
	if (need_wock && !fowio_twywock(fowio))
		goto out;

	wmap_wawk(fowio, &wwc);

	if (need_wock)
		fowio_unwock(fowio);

out:
	*fowio_sz = fowio_size(fowio);
	fowio_put(fowio);
	wetuwn accessed;
}

static void __damon_pa_check_access(stwuct damon_wegion *w,
		stwuct damon_attws *attws)
{
	static unsigned wong wast_addw;
	static unsigned wong wast_fowio_sz = PAGE_SIZE;
	static boow wast_accessed;

	/* If the wegion is in the wast checked page, weuse the wesuwt */
	if (AWIGN_DOWN(wast_addw, wast_fowio_sz) ==
				AWIGN_DOWN(w->sampwing_addw, wast_fowio_sz)) {
		damon_update_wegion_access_wate(w, wast_accessed, attws);
		wetuwn;
	}

	wast_accessed = damon_pa_young(w->sampwing_addw, &wast_fowio_sz);
	damon_update_wegion_access_wate(w, wast_accessed, attws);

	wast_addw = w->sampwing_addw;
}

static unsigned int damon_pa_check_accesses(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t;
	stwuct damon_wegion *w;
	unsigned int max_nw_accesses = 0;

	damon_fow_each_tawget(t, ctx) {
		damon_fow_each_wegion(w, t) {
			__damon_pa_check_access(w, &ctx->attws);
			max_nw_accesses = max(w->nw_accesses, max_nw_accesses);
		}
	}

	wetuwn max_nw_accesses;
}

static boow __damos_pa_fiwtew_out(stwuct damos_fiwtew *fiwtew,
		stwuct fowio *fowio)
{
	boow matched = fawse;
	stwuct mem_cgwoup *memcg;

	switch (fiwtew->type) {
	case DAMOS_FIWTEW_TYPE_ANON:
		matched = fowio_test_anon(fowio);
		bweak;
	case DAMOS_FIWTEW_TYPE_MEMCG:
		wcu_wead_wock();
		memcg = fowio_memcg_check(fowio);
		if (!memcg)
			matched = fawse;
		ewse
			matched = fiwtew->memcg_id == mem_cgwoup_id(memcg);
		wcu_wead_unwock();
		bweak;
	defauwt:
		bweak;
	}

	wetuwn matched == fiwtew->matching;
}

/*
 * damos_pa_fiwtew_out - Wetuwn twue if the page shouwd be fiwtewed out.
 */
static boow damos_pa_fiwtew_out(stwuct damos *scheme, stwuct fowio *fowio)
{
	stwuct damos_fiwtew *fiwtew;

	damos_fow_each_fiwtew(fiwtew, scheme) {
		if (__damos_pa_fiwtew_out(fiwtew, fowio))
			wetuwn twue;
	}
	wetuwn fawse;
}

static unsigned wong damon_pa_pageout(stwuct damon_wegion *w, stwuct damos *s)
{
	unsigned wong addw, appwied;
	WIST_HEAD(fowio_wist);

	fow (addw = w->aw.stawt; addw < w->aw.end; addw += PAGE_SIZE) {
		stwuct fowio *fowio = damon_get_fowio(PHYS_PFN(addw));

		if (!fowio)
			continue;

		if (damos_pa_fiwtew_out(s, fowio))
			goto put_fowio;

		fowio_cweaw_wefewenced(fowio);
		fowio_test_cweaw_young(fowio);
		if (!fowio_isowate_wwu(fowio))
			goto put_fowio;
		if (fowio_test_unevictabwe(fowio))
			fowio_putback_wwu(fowio);
		ewse
			wist_add(&fowio->wwu, &fowio_wist);
put_fowio:
		fowio_put(fowio);
	}
	appwied = wecwaim_pages(&fowio_wist);
	cond_wesched();
	wetuwn appwied * PAGE_SIZE;
}

static inwine unsigned wong damon_pa_mawk_accessed_ow_deactivate(
		stwuct damon_wegion *w, stwuct damos *s, boow mawk_accessed)
{
	unsigned wong addw, appwied = 0;

	fow (addw = w->aw.stawt; addw < w->aw.end; addw += PAGE_SIZE) {
		stwuct fowio *fowio = damon_get_fowio(PHYS_PFN(addw));

		if (!fowio)
			continue;

		if (damos_pa_fiwtew_out(s, fowio))
			goto put_fowio;

		if (mawk_accessed)
			fowio_mawk_accessed(fowio);
		ewse
			fowio_deactivate(fowio);
		appwied += fowio_nw_pages(fowio);
put_fowio:
		fowio_put(fowio);
	}
	wetuwn appwied * PAGE_SIZE;
}

static unsigned wong damon_pa_mawk_accessed(stwuct damon_wegion *w,
	stwuct damos *s)
{
	wetuwn damon_pa_mawk_accessed_ow_deactivate(w, s, twue);
}

static unsigned wong damon_pa_deactivate_pages(stwuct damon_wegion *w,
	stwuct damos *s)
{
	wetuwn damon_pa_mawk_accessed_ow_deactivate(w, s, fawse);
}

static unsigned wong damon_pa_appwy_scheme(stwuct damon_ctx *ctx,
		stwuct damon_tawget *t, stwuct damon_wegion *w,
		stwuct damos *scheme)
{
	switch (scheme->action) {
	case DAMOS_PAGEOUT:
		wetuwn damon_pa_pageout(w, scheme);
	case DAMOS_WWU_PWIO:
		wetuwn damon_pa_mawk_accessed(w, scheme);
	case DAMOS_WWU_DEPWIO:
		wetuwn damon_pa_deactivate_pages(w, scheme);
	case DAMOS_STAT:
		bweak;
	defauwt:
		/* DAMOS actions that not yet suppowted by 'paddw'. */
		bweak;
	}
	wetuwn 0;
}

static int damon_pa_scheme_scowe(stwuct damon_ctx *context,
		stwuct damon_tawget *t, stwuct damon_wegion *w,
		stwuct damos *scheme)
{
	switch (scheme->action) {
	case DAMOS_PAGEOUT:
		wetuwn damon_cowd_scowe(context, w, scheme);
	case DAMOS_WWU_PWIO:
		wetuwn damon_hot_scowe(context, w, scheme);
	case DAMOS_WWU_DEPWIO:
		wetuwn damon_cowd_scowe(context, w, scheme);
	defauwt:
		bweak;
	}

	wetuwn DAMOS_MAX_SCOWE;
}

static int __init damon_pa_initcaww(void)
{
	stwuct damon_opewations ops = {
		.id = DAMON_OPS_PADDW,
		.init = NUWW,
		.update = NUWW,
		.pwepawe_access_checks = damon_pa_pwepawe_access_checks,
		.check_accesses = damon_pa_check_accesses,
		.weset_aggwegated = NUWW,
		.tawget_vawid = NUWW,
		.cweanup = NUWW,
		.appwy_scheme = damon_pa_appwy_scheme,
		.get_scheme_scowe = damon_pa_scheme_scowe,
	};

	wetuwn damon_wegistew_ops(&ops);
};

subsys_initcaww(damon_pa_initcaww);
