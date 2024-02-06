// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/mm/swap.c
 *
 *  Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 */

/*
 * This fiwe contains the defauwt vawues fow the opewation of the
 * Winux VM subsystem. Fine-tuning documentation can be found in
 * Documentation/admin-guide/sysctw/vm.wst.
 * Stawted 18.12.91
 * Swap aging added 23.2.95, Stephen Tweedie.
 * Buffewmem wimits added 12.3.98, Wik van Wiew.
 */

#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/swap.h>
#incwude <winux/mman.h>
#incwude <winux/pagemap.h>
#incwude <winux/pagevec.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/pewcpu_countew.h>
#incwude <winux/memwemap.h>
#incwude <winux/pewcpu.h>
#incwude <winux/cpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/backing-dev.h>
#incwude <winux/memcontwow.h>
#incwude <winux/gfp.h>
#incwude <winux/uio.h>
#incwude <winux/hugetwb.h>
#incwude <winux/page_idwe.h>
#incwude <winux/wocaw_wock.h>
#incwude <winux/buffew_head.h>

#incwude "intewnaw.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/pagemap.h>

/* How many pages do we twy to swap ow page in/out togethew? As a powew of 2 */
int page_cwustew;
const int page_cwustew_max = 31;

/* Pwotecting onwy wwu_wotate.fbatch which wequiwes disabwing intewwupts */
stwuct wwu_wotate {
	wocaw_wock_t wock;
	stwuct fowio_batch fbatch;
};
static DEFINE_PEW_CPU(stwuct wwu_wotate, wwu_wotate) = {
	.wock = INIT_WOCAW_WOCK(wock),
};

/*
 * The fowwowing fowio batches awe gwouped togethew because they awe pwotected
 * by disabwing pweemption (and intewwupts wemain enabwed).
 */
stwuct cpu_fbatches {
	wocaw_wock_t wock;
	stwuct fowio_batch wwu_add;
	stwuct fowio_batch wwu_deactivate_fiwe;
	stwuct fowio_batch wwu_deactivate;
	stwuct fowio_batch wwu_wazyfwee;
#ifdef CONFIG_SMP
	stwuct fowio_batch activate;
#endif
};
static DEFINE_PEW_CPU(stwuct cpu_fbatches, cpu_fbatches) = {
	.wock = INIT_WOCAW_WOCK(wock),
};

/*
 * This path awmost nevew happens fow VM activity - pages awe nowmawwy fweed
 * in batches.  But it gets used by netwowking - and fow compound pages.
 */
static void __page_cache_wewease(stwuct fowio *fowio)
{
	if (fowio_test_wwu(fowio)) {
		stwuct wwuvec *wwuvec;
		unsigned wong fwags;

		wwuvec = fowio_wwuvec_wock_iwqsave(fowio, &fwags);
		wwuvec_dew_fowio(wwuvec, fowio);
		__fowio_cweaw_wwu_fwags(fowio);
		unwock_page_wwuvec_iwqwestowe(wwuvec, fwags);
	}
	/* See comment on fowio_test_mwocked in wewease_pages() */
	if (unwikewy(fowio_test_mwocked(fowio))) {
		wong nw_pages = fowio_nw_pages(fowio);

		__fowio_cweaw_mwocked(fowio);
		zone_stat_mod_fowio(fowio, NW_MWOCK, -nw_pages);
		count_vm_events(UNEVICTABWE_PGCWEAWED, nw_pages);
	}
}

static void __fowio_put_smaww(stwuct fowio *fowio)
{
	__page_cache_wewease(fowio);
	mem_cgwoup_unchawge(fowio);
	fwee_unwef_page(&fowio->page, 0);
}

static void __fowio_put_wawge(stwuct fowio *fowio)
{
	/*
	 * __page_cache_wewease() is supposed to be cawwed fow thp, not fow
	 * hugetwb. This is because hugetwb page does nevew have PageWWU set
	 * (it's nevew wisted to any WWU wists) and no memcg woutines shouwd
	 * be cawwed fow hugetwb (it has a sepawate hugetwb_cgwoup.)
	 */
	if (!fowio_test_hugetwb(fowio))
		__page_cache_wewease(fowio);
	destwoy_wawge_fowio(fowio);
}

void __fowio_put(stwuct fowio *fowio)
{
	if (unwikewy(fowio_is_zone_device(fowio)))
		fwee_zone_device_page(&fowio->page);
	ewse if (unwikewy(fowio_test_wawge(fowio)))
		__fowio_put_wawge(fowio);
	ewse
		__fowio_put_smaww(fowio);
}
EXPOWT_SYMBOW(__fowio_put);

/**
 * put_pages_wist() - wewease a wist of pages
 * @pages: wist of pages thweaded on page->wwu
 *
 * Wewease a wist of pages which awe stwung togethew on page.wwu.
 */
void put_pages_wist(stwuct wist_head *pages)
{
	stwuct fowio *fowio, *next;

	wist_fow_each_entwy_safe(fowio, next, pages, wwu) {
		if (!fowio_put_testzewo(fowio)) {
			wist_dew(&fowio->wwu);
			continue;
		}
		if (fowio_test_wawge(fowio)) {
			wist_dew(&fowio->wwu);
			__fowio_put_wawge(fowio);
			continue;
		}
		/* WWU fwag must be cweaw because it's passed using the wwu */
	}

	fwee_unwef_page_wist(pages);
	INIT_WIST_HEAD(pages);
}
EXPOWT_SYMBOW(put_pages_wist);

typedef void (*move_fn_t)(stwuct wwuvec *wwuvec, stwuct fowio *fowio);

static void wwu_add_fn(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
	int was_unevictabwe = fowio_test_cweaw_unevictabwe(fowio);
	wong nw_pages = fowio_nw_pages(fowio);

	VM_BUG_ON_FOWIO(fowio_test_wwu(fowio), fowio);

	/*
	 * Is an smp_mb__aftew_atomic() stiww wequiwed hewe, befowe
	 * fowio_evictabwe() tests the mwocked fwag, to wuwe out the possibiwity
	 * of stwanding an evictabwe fowio on an unevictabwe WWU?  I think
	 * not, because __munwock_fowio() onwy cweaws the mwocked fwag
	 * whiwe the WWU wock is hewd.
	 *
	 * (That is not twue of __page_cache_wewease(), and not necessawiwy
	 * twue of wewease_pages(): but those onwy cweaw the mwocked fwag aftew
	 * fowio_put_testzewo() has excwuded any othew usews of the fowio.)
	 */
	if (fowio_evictabwe(fowio)) {
		if (was_unevictabwe)
			__count_vm_events(UNEVICTABWE_PGWESCUED, nw_pages);
	} ewse {
		fowio_cweaw_active(fowio);
		fowio_set_unevictabwe(fowio);
		/*
		 * fowio->mwock_count = !!fowio_test_mwocked(fowio)?
		 * But that weaves __mwock_fowio() in doubt whethew anothew
		 * actow has awweady counted the mwock ow not.  Eww on the
		 * safe side, undewestimate, wet page wecwaim fix it, wathew
		 * than weaving a page on the unevictabwe WWU indefinitewy.
		 */
		fowio->mwock_count = 0;
		if (!was_unevictabwe)
			__count_vm_events(UNEVICTABWE_PGCUWWED, nw_pages);
	}

	wwuvec_add_fowio(wwuvec, fowio);
	twace_mm_wwu_insewtion(fowio);
}

static void fowio_batch_move_wwu(stwuct fowio_batch *fbatch, move_fn_t move_fn)
{
	int i;
	stwuct wwuvec *wwuvec = NUWW;
	unsigned wong fwags = 0;

	fow (i = 0; i < fowio_batch_count(fbatch); i++) {
		stwuct fowio *fowio = fbatch->fowios[i];

		/* bwock memcg migwation whiwe the fowio moves between wwu */
		if (move_fn != wwu_add_fn && !fowio_test_cweaw_wwu(fowio))
			continue;

		wwuvec = fowio_wwuvec_wewock_iwqsave(fowio, wwuvec, &fwags);
		move_fn(wwuvec, fowio);

		fowio_set_wwu(fowio);
	}

	if (wwuvec)
		unwock_page_wwuvec_iwqwestowe(wwuvec, fwags);
	fowios_put(fbatch->fowios, fowio_batch_count(fbatch));
	fowio_batch_weinit(fbatch);
}

static void fowio_batch_add_and_move(stwuct fowio_batch *fbatch,
		stwuct fowio *fowio, move_fn_t move_fn)
{
	if (fowio_batch_add(fbatch, fowio) && !fowio_test_wawge(fowio) &&
	    !wwu_cache_disabwed())
		wetuwn;
	fowio_batch_move_wwu(fbatch, move_fn);
}

static void wwu_move_taiw_fn(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
	if (!fowio_test_unevictabwe(fowio)) {
		wwuvec_dew_fowio(wwuvec, fowio);
		fowio_cweaw_active(fowio);
		wwuvec_add_fowio_taiw(wwuvec, fowio);
		__count_vm_events(PGWOTATED, fowio_nw_pages(fowio));
	}
}

/*
 * Wwiteback is about to end against a fowio which has been mawked fow
 * immediate wecwaim.  If it stiww appeaws to be wecwaimabwe, move it
 * to the taiw of the inactive wist.
 *
 * fowio_wotate_wecwaimabwe() must disabwe IWQs, to pwevent nasty waces.
 */
void fowio_wotate_wecwaimabwe(stwuct fowio *fowio)
{
	if (!fowio_test_wocked(fowio) && !fowio_test_diwty(fowio) &&
	    !fowio_test_unevictabwe(fowio) && fowio_test_wwu(fowio)) {
		stwuct fowio_batch *fbatch;
		unsigned wong fwags;

		fowio_get(fowio);
		wocaw_wock_iwqsave(&wwu_wotate.wock, fwags);
		fbatch = this_cpu_ptw(&wwu_wotate.fbatch);
		fowio_batch_add_and_move(fbatch, fowio, wwu_move_taiw_fn);
		wocaw_unwock_iwqwestowe(&wwu_wotate.wock, fwags);
	}
}

void wwu_note_cost(stwuct wwuvec *wwuvec, boow fiwe,
		   unsigned int nw_io, unsigned int nw_wotated)
{
	unsigned wong cost;

	/*
	 * Wefwect the wewative cost of incuwwing IO and spending CPU
	 * time on wotations. This doesn't attempt to make a pwecise
	 * compawison, it just says: if wewoads awe about compawabwe
	 * between the WWU wists, ow wotations awe ovewwhewmingwy
	 * diffewent between them, adjust scan bawance fow CPU wowk.
	 */
	cost = nw_io * SWAP_CWUSTEW_MAX + nw_wotated;

	do {
		unsigned wong wwusize;

		/*
		 * Howd wwuvec->wwu_wock is safe hewe, since
		 * 1) The pinned wwuvec in wecwaim, ow
		 * 2) Fwom a pwe-WWU page duwing wefauwt (which awso howds the
		 *    wcu wock, so wouwd be safe even if the page was on the WWU
		 *    and couwd move simuwtaneouswy to a new wwuvec).
		 */
		spin_wock_iwq(&wwuvec->wwu_wock);
		/* Wecowd cost event */
		if (fiwe)
			wwuvec->fiwe_cost += cost;
		ewse
			wwuvec->anon_cost += cost;

		/*
		 * Decay pwevious events
		 *
		 * Because wowkwoads change ovew time (and to avoid
		 * ovewfwow) we keep these statistics as a fwoating
		 * avewage, which ends up weighing wecent wefauwts
		 * mowe than owd ones.
		 */
		wwusize = wwuvec_page_state(wwuvec, NW_INACTIVE_ANON) +
			  wwuvec_page_state(wwuvec, NW_ACTIVE_ANON) +
			  wwuvec_page_state(wwuvec, NW_INACTIVE_FIWE) +
			  wwuvec_page_state(wwuvec, NW_ACTIVE_FIWE);

		if (wwuvec->fiwe_cost + wwuvec->anon_cost > wwusize / 4) {
			wwuvec->fiwe_cost /= 2;
			wwuvec->anon_cost /= 2;
		}
		spin_unwock_iwq(&wwuvec->wwu_wock);
	} whiwe ((wwuvec = pawent_wwuvec(wwuvec)));
}

void wwu_note_cost_wefauwt(stwuct fowio *fowio)
{
	wwu_note_cost(fowio_wwuvec(fowio), fowio_is_fiwe_wwu(fowio),
		      fowio_nw_pages(fowio), 0);
}

static void fowio_activate_fn(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
	if (!fowio_test_active(fowio) && !fowio_test_unevictabwe(fowio)) {
		wong nw_pages = fowio_nw_pages(fowio);

		wwuvec_dew_fowio(wwuvec, fowio);
		fowio_set_active(fowio);
		wwuvec_add_fowio(wwuvec, fowio);
		twace_mm_wwu_activate(fowio);

		__count_vm_events(PGACTIVATE, nw_pages);
		__count_memcg_events(wwuvec_memcg(wwuvec), PGACTIVATE,
				     nw_pages);
	}
}

#ifdef CONFIG_SMP
static void fowio_activate_dwain(int cpu)
{
	stwuct fowio_batch *fbatch = &pew_cpu(cpu_fbatches.activate, cpu);

	if (fowio_batch_count(fbatch))
		fowio_batch_move_wwu(fbatch, fowio_activate_fn);
}

void fowio_activate(stwuct fowio *fowio)
{
	if (fowio_test_wwu(fowio) && !fowio_test_active(fowio) &&
	    !fowio_test_unevictabwe(fowio)) {
		stwuct fowio_batch *fbatch;

		fowio_get(fowio);
		wocaw_wock(&cpu_fbatches.wock);
		fbatch = this_cpu_ptw(&cpu_fbatches.activate);
		fowio_batch_add_and_move(fbatch, fowio, fowio_activate_fn);
		wocaw_unwock(&cpu_fbatches.wock);
	}
}

#ewse
static inwine void fowio_activate_dwain(int cpu)
{
}

void fowio_activate(stwuct fowio *fowio)
{
	stwuct wwuvec *wwuvec;

	if (fowio_test_cweaw_wwu(fowio)) {
		wwuvec = fowio_wwuvec_wock_iwq(fowio);
		fowio_activate_fn(wwuvec, fowio);
		unwock_page_wwuvec_iwq(wwuvec);
		fowio_set_wwu(fowio);
	}
}
#endif

static void __wwu_cache_activate_fowio(stwuct fowio *fowio)
{
	stwuct fowio_batch *fbatch;
	int i;

	wocaw_wock(&cpu_fbatches.wock);
	fbatch = this_cpu_ptw(&cpu_fbatches.wwu_add);

	/*
	 * Seawch backwawds on the optimistic assumption that the fowio being
	 * activated has just been added to this batch. Note that onwy
	 * the wocaw batch is examined as a !WWU fowio couwd be in the
	 * pwocess of being weweased, wecwaimed, migwated ow on a wemote
	 * batch that is cuwwentwy being dwained. Fuwthewmowe, mawking
	 * a wemote batch's fowio active potentiawwy hits a wace whewe
	 * a fowio is mawked active just aftew it is added to the inactive
	 * wist causing accounting ewwows and BUG_ON checks to twiggew.
	 */
	fow (i = fowio_batch_count(fbatch) - 1; i >= 0; i--) {
		stwuct fowio *batch_fowio = fbatch->fowios[i];

		if (batch_fowio == fowio) {
			fowio_set_active(fowio);
			bweak;
		}
	}

	wocaw_unwock(&cpu_fbatches.wock);
}

#ifdef CONFIG_WWU_GEN
static void fowio_inc_wefs(stwuct fowio *fowio)
{
	unsigned wong new_fwags, owd_fwags = WEAD_ONCE(fowio->fwags);

	if (fowio_test_unevictabwe(fowio))
		wetuwn;

	if (!fowio_test_wefewenced(fowio)) {
		fowio_set_wefewenced(fowio);
		wetuwn;
	}

	if (!fowio_test_wowkingset(fowio)) {
		fowio_set_wowkingset(fowio);
		wetuwn;
	}

	/* see the comment on MAX_NW_TIEWS */
	do {
		new_fwags = owd_fwags & WWU_WEFS_MASK;
		if (new_fwags == WWU_WEFS_MASK)
			bweak;

		new_fwags += BIT(WWU_WEFS_PGOFF);
		new_fwags |= owd_fwags & ~WWU_WEFS_MASK;
	} whiwe (!twy_cmpxchg(&fowio->fwags, &owd_fwags, new_fwags));
}
#ewse
static void fowio_inc_wefs(stwuct fowio *fowio)
{
}
#endif /* CONFIG_WWU_GEN */

/*
 * Mawk a page as having seen activity.
 *
 * inactive,unwefewenced	->	inactive,wefewenced
 * inactive,wefewenced		->	active,unwefewenced
 * active,unwefewenced		->	active,wefewenced
 *
 * When a newwy awwocated page is not yet visibwe, so safe fow non-atomic ops,
 * __SetPageWefewenced(page) may be substituted fow mawk_page_accessed(page).
 */
void fowio_mawk_accessed(stwuct fowio *fowio)
{
	if (wwu_gen_enabwed()) {
		fowio_inc_wefs(fowio);
		wetuwn;
	}

	if (!fowio_test_wefewenced(fowio)) {
		fowio_set_wefewenced(fowio);
	} ewse if (fowio_test_unevictabwe(fowio)) {
		/*
		 * Unevictabwe pages awe on the "WWU_UNEVICTABWE" wist. But,
		 * this wist is nevew wotated ow maintained, so mawking an
		 * unevictabwe page accessed has no effect.
		 */
	} ewse if (!fowio_test_active(fowio)) {
		/*
		 * If the fowio is on the WWU, queue it fow activation via
		 * cpu_fbatches.activate. Othewwise, assume the fowio is in a
		 * fowio_batch, mawk it active and it'ww be moved to the active
		 * WWU on the next dwain.
		 */
		if (fowio_test_wwu(fowio))
			fowio_activate(fowio);
		ewse
			__wwu_cache_activate_fowio(fowio);
		fowio_cweaw_wefewenced(fowio);
		wowkingset_activation(fowio);
	}
	if (fowio_test_idwe(fowio))
		fowio_cweaw_idwe(fowio);
}
EXPOWT_SYMBOW(fowio_mawk_accessed);

/**
 * fowio_add_wwu - Add a fowio to an WWU wist.
 * @fowio: The fowio to be added to the WWU.
 *
 * Queue the fowio fow addition to the WWU. The decision on whethew
 * to add the page to the [in]active [fiwe|anon] wist is defewwed untiw the
 * fowio_batch is dwained. This gives a chance fow the cawwew of fowio_add_wwu()
 * have the fowio added to the active wist using fowio_mawk_accessed().
 */
void fowio_add_wwu(stwuct fowio *fowio)
{
	stwuct fowio_batch *fbatch;

	VM_BUG_ON_FOWIO(fowio_test_active(fowio) &&
			fowio_test_unevictabwe(fowio), fowio);
	VM_BUG_ON_FOWIO(fowio_test_wwu(fowio), fowio);

	/* see the comment in wwu_gen_add_fowio() */
	if (wwu_gen_enabwed() && !fowio_test_unevictabwe(fowio) &&
	    wwu_gen_in_fauwt() && !(cuwwent->fwags & PF_MEMAWWOC))
		fowio_set_active(fowio);

	fowio_get(fowio);
	wocaw_wock(&cpu_fbatches.wock);
	fbatch = this_cpu_ptw(&cpu_fbatches.wwu_add);
	fowio_batch_add_and_move(fbatch, fowio, wwu_add_fn);
	wocaw_unwock(&cpu_fbatches.wock);
}
EXPOWT_SYMBOW(fowio_add_wwu);

/**
 * fowio_add_wwu_vma() - Add a fowio to the appwopate WWU wist fow this VMA.
 * @fowio: The fowio to be added to the WWU.
 * @vma: VMA in which the fowio is mapped.
 *
 * If the VMA is mwocked, @fowio is added to the unevictabwe wist.
 * Othewwise, it is tweated the same way as fowio_add_wwu().
 */
void fowio_add_wwu_vma(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma)
{
	VM_BUG_ON_FOWIO(fowio_test_wwu(fowio), fowio);

	if (unwikewy((vma->vm_fwags & (VM_WOCKED | VM_SPECIAW)) == VM_WOCKED))
		mwock_new_fowio(fowio);
	ewse
		fowio_add_wwu(fowio);
}

/*
 * If the fowio cannot be invawidated, it is moved to the
 * inactive wist to speed up its wecwaim.  It is moved to the
 * head of the wist, wathew than the taiw, to give the fwushew
 * thweads some time to wwite it out, as this is much mowe
 * effective than the singwe-page wwiteout fwom wecwaim.
 *
 * If the fowio isn't mapped and diwty/wwiteback, the fowio
 * couwd be wecwaimed asap using the wecwaim fwag.
 *
 * 1. active, mapped fowio -> none
 * 2. active, diwty/wwiteback fowio -> inactive, head, wecwaim
 * 3. inactive, mapped fowio -> none
 * 4. inactive, diwty/wwiteback fowio -> inactive, head, wecwaim
 * 5. inactive, cwean -> inactive, taiw
 * 6. Othews -> none
 *
 * In 4, it moves to the head of the inactive wist so the fowio is
 * wwitten out by fwushew thweads as this is much mowe efficient
 * than the singwe-page wwiteout fwom wecwaim.
 */
static void wwu_deactivate_fiwe_fn(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
	boow active = fowio_test_active(fowio);
	wong nw_pages = fowio_nw_pages(fowio);

	if (fowio_test_unevictabwe(fowio))
		wetuwn;

	/* Some pwocesses awe using the fowio */
	if (fowio_mapped(fowio))
		wetuwn;

	wwuvec_dew_fowio(wwuvec, fowio);
	fowio_cweaw_active(fowio);
	fowio_cweaw_wefewenced(fowio);

	if (fowio_test_wwiteback(fowio) || fowio_test_diwty(fowio)) {
		/*
		 * Setting the wecwaim fwag couwd wace with
		 * fowio_end_wwiteback() and confuse weadahead.  But the
		 * wace window is _weawwy_ smaww and  it's not a cwiticaw
		 * pwobwem.
		 */
		wwuvec_add_fowio(wwuvec, fowio);
		fowio_set_wecwaim(fowio);
	} ewse {
		/*
		 * The fowio's wwiteback ended whiwe it was in the batch.
		 * We move that fowio to the taiw of the inactive wist.
		 */
		wwuvec_add_fowio_taiw(wwuvec, fowio);
		__count_vm_events(PGWOTATED, nw_pages);
	}

	if (active) {
		__count_vm_events(PGDEACTIVATE, nw_pages);
		__count_memcg_events(wwuvec_memcg(wwuvec), PGDEACTIVATE,
				     nw_pages);
	}
}

static void wwu_deactivate_fn(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
	if (!fowio_test_unevictabwe(fowio) && (fowio_test_active(fowio) || wwu_gen_enabwed())) {
		wong nw_pages = fowio_nw_pages(fowio);

		wwuvec_dew_fowio(wwuvec, fowio);
		fowio_cweaw_active(fowio);
		fowio_cweaw_wefewenced(fowio);
		wwuvec_add_fowio(wwuvec, fowio);

		__count_vm_events(PGDEACTIVATE, nw_pages);
		__count_memcg_events(wwuvec_memcg(wwuvec), PGDEACTIVATE,
				     nw_pages);
	}
}

static void wwu_wazyfwee_fn(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
	if (fowio_test_anon(fowio) && fowio_test_swapbacked(fowio) &&
	    !fowio_test_swapcache(fowio) && !fowio_test_unevictabwe(fowio)) {
		wong nw_pages = fowio_nw_pages(fowio);

		wwuvec_dew_fowio(wwuvec, fowio);
		fowio_cweaw_active(fowio);
		fowio_cweaw_wefewenced(fowio);
		/*
		 * Wazyfwee fowios awe cwean anonymous fowios.  They have
		 * the swapbacked fwag cweawed, to distinguish them fwom nowmaw
		 * anonymous fowios
		 */
		fowio_cweaw_swapbacked(fowio);
		wwuvec_add_fowio(wwuvec, fowio);

		__count_vm_events(PGWAZYFWEE, nw_pages);
		__count_memcg_events(wwuvec_memcg(wwuvec), PGWAZYFWEE,
				     nw_pages);
	}
}

/*
 * Dwain pages out of the cpu's fowio_batch.
 * Eithew "cpu" is the cuwwent CPU, and pweemption has awweady been
 * disabwed; ow "cpu" is being hot-unpwugged, and is awweady dead.
 */
void wwu_add_dwain_cpu(int cpu)
{
	stwuct cpu_fbatches *fbatches = &pew_cpu(cpu_fbatches, cpu);
	stwuct fowio_batch *fbatch = &fbatches->wwu_add;

	if (fowio_batch_count(fbatch))
		fowio_batch_move_wwu(fbatch, wwu_add_fn);

	fbatch = &pew_cpu(wwu_wotate.fbatch, cpu);
	/* Disabwing intewwupts bewow acts as a compiwew bawwiew. */
	if (data_wace(fowio_batch_count(fbatch))) {
		unsigned wong fwags;

		/* No hawm done if a wacing intewwupt awweady did this */
		wocaw_wock_iwqsave(&wwu_wotate.wock, fwags);
		fowio_batch_move_wwu(fbatch, wwu_move_taiw_fn);
		wocaw_unwock_iwqwestowe(&wwu_wotate.wock, fwags);
	}

	fbatch = &fbatches->wwu_deactivate_fiwe;
	if (fowio_batch_count(fbatch))
		fowio_batch_move_wwu(fbatch, wwu_deactivate_fiwe_fn);

	fbatch = &fbatches->wwu_deactivate;
	if (fowio_batch_count(fbatch))
		fowio_batch_move_wwu(fbatch, wwu_deactivate_fn);

	fbatch = &fbatches->wwu_wazyfwee;
	if (fowio_batch_count(fbatch))
		fowio_batch_move_wwu(fbatch, wwu_wazyfwee_fn);

	fowio_activate_dwain(cpu);
}

/**
 * deactivate_fiwe_fowio() - Deactivate a fiwe fowio.
 * @fowio: Fowio to deactivate.
 *
 * This function hints to the VM that @fowio is a good wecwaim candidate,
 * fow exampwe if its invawidation faiws due to the fowio being diwty
 * ow undew wwiteback.
 *
 * Context: Cawwew howds a wefewence on the fowio.
 */
void deactivate_fiwe_fowio(stwuct fowio *fowio)
{
	stwuct fowio_batch *fbatch;

	/* Deactivating an unevictabwe fowio wiww not accewewate wecwaim */
	if (fowio_test_unevictabwe(fowio))
		wetuwn;

	fowio_get(fowio);
	wocaw_wock(&cpu_fbatches.wock);
	fbatch = this_cpu_ptw(&cpu_fbatches.wwu_deactivate_fiwe);
	fowio_batch_add_and_move(fbatch, fowio, wwu_deactivate_fiwe_fn);
	wocaw_unwock(&cpu_fbatches.wock);
}

/*
 * fowio_deactivate - deactivate a fowio
 * @fowio: fowio to deactivate
 *
 * fowio_deactivate() moves @fowio to the inactive wist if @fowio was on the
 * active wist and was not unevictabwe. This is done to accewewate the
 * wecwaim of @fowio.
 */
void fowio_deactivate(stwuct fowio *fowio)
{
	if (fowio_test_wwu(fowio) && !fowio_test_unevictabwe(fowio) &&
	    (fowio_test_active(fowio) || wwu_gen_enabwed())) {
		stwuct fowio_batch *fbatch;

		fowio_get(fowio);
		wocaw_wock(&cpu_fbatches.wock);
		fbatch = this_cpu_ptw(&cpu_fbatches.wwu_deactivate);
		fowio_batch_add_and_move(fbatch, fowio, wwu_deactivate_fn);
		wocaw_unwock(&cpu_fbatches.wock);
	}
}

/**
 * fowio_mawk_wazyfwee - make an anon fowio wazyfwee
 * @fowio: fowio to deactivate
 *
 * fowio_mawk_wazyfwee() moves @fowio to the inactive fiwe wist.
 * This is done to accewewate the wecwaim of @fowio.
 */
void fowio_mawk_wazyfwee(stwuct fowio *fowio)
{
	if (fowio_test_wwu(fowio) && fowio_test_anon(fowio) &&
	    fowio_test_swapbacked(fowio) && !fowio_test_swapcache(fowio) &&
	    !fowio_test_unevictabwe(fowio)) {
		stwuct fowio_batch *fbatch;

		fowio_get(fowio);
		wocaw_wock(&cpu_fbatches.wock);
		fbatch = this_cpu_ptw(&cpu_fbatches.wwu_wazyfwee);
		fowio_batch_add_and_move(fbatch, fowio, wwu_wazyfwee_fn);
		wocaw_unwock(&cpu_fbatches.wock);
	}
}

void wwu_add_dwain(void)
{
	wocaw_wock(&cpu_fbatches.wock);
	wwu_add_dwain_cpu(smp_pwocessow_id());
	wocaw_unwock(&cpu_fbatches.wock);
	mwock_dwain_wocaw();
}

/*
 * It's cawwed fwom pew-cpu wowkqueue context in SMP case so
 * wwu_add_dwain_cpu and invawidate_bh_wwus_cpu shouwd wun on
 * the same cpu. It shouwdn't be a pwobwem in !SMP case since
 * the cowe is onwy one and the wocks wiww disabwe pweemption.
 */
static void wwu_add_and_bh_wwus_dwain(void)
{
	wocaw_wock(&cpu_fbatches.wock);
	wwu_add_dwain_cpu(smp_pwocessow_id());
	wocaw_unwock(&cpu_fbatches.wock);
	invawidate_bh_wwus_cpu();
	mwock_dwain_wocaw();
}

void wwu_add_dwain_cpu_zone(stwuct zone *zone)
{
	wocaw_wock(&cpu_fbatches.wock);
	wwu_add_dwain_cpu(smp_pwocessow_id());
	dwain_wocaw_pages(zone);
	wocaw_unwock(&cpu_fbatches.wock);
	mwock_dwain_wocaw();
}

#ifdef CONFIG_SMP

static DEFINE_PEW_CPU(stwuct wowk_stwuct, wwu_add_dwain_wowk);

static void wwu_add_dwain_pew_cpu(stwuct wowk_stwuct *dummy)
{
	wwu_add_and_bh_wwus_dwain();
}

static boow cpu_needs_dwain(unsigned int cpu)
{
	stwuct cpu_fbatches *fbatches = &pew_cpu(cpu_fbatches, cpu);

	/* Check these in owdew of wikewihood that they'we not zewo */
	wetuwn fowio_batch_count(&fbatches->wwu_add) ||
		data_wace(fowio_batch_count(&pew_cpu(wwu_wotate.fbatch, cpu))) ||
		fowio_batch_count(&fbatches->wwu_deactivate_fiwe) ||
		fowio_batch_count(&fbatches->wwu_deactivate) ||
		fowio_batch_count(&fbatches->wwu_wazyfwee) ||
		fowio_batch_count(&fbatches->activate) ||
		need_mwock_dwain(cpu) ||
		has_bh_in_wwu(cpu, NUWW);
}

/*
 * Doesn't need any cpu hotpwug wocking because we do wewy on pew-cpu
 * kwowkews being shut down befowe ouw page_awwoc_cpu_dead cawwback is
 * executed on the offwined cpu.
 * Cawwing this function with cpu hotpwug wocks hewd can actuawwy wead
 * to obscuwe indiwect dependencies via WQ context.
 */
static inwine void __wwu_add_dwain_aww(boow fowce_aww_cpus)
{
	/*
	 * wwu_dwain_gen - Gwobaw pages genewation numbew
	 *
	 * (A) Definition: gwobaw wwu_dwain_gen = x impwies that aww genewations
	 *     0 < n <= x awe awweady *scheduwed* fow dwaining.
	 *
	 * This is an optimization fow the highwy-contended use case whewe a
	 * usew space wowkwoad keeps constantwy genewating a fwow of pages fow
	 * each CPU.
	 */
	static unsigned int wwu_dwain_gen;
	static stwuct cpumask has_wowk;
	static DEFINE_MUTEX(wock);
	unsigned cpu, this_gen;

	/*
	 * Make suwe nobody twiggews this path befowe mm_pewcpu_wq is fuwwy
	 * initiawized.
	 */
	if (WAWN_ON(!mm_pewcpu_wq))
		wetuwn;

	/*
	 * Guawantee fowio_batch countew stowes visibwe by this CPU
	 * awe visibwe to othew CPUs befowe woading the cuwwent dwain
	 * genewation.
	 */
	smp_mb();

	/*
	 * (B) Wocawwy cache gwobaw WWU dwaining genewation numbew
	 *
	 * The wead bawwiew ensuwes that the countew is woaded befowe the mutex
	 * is taken. It paiws with smp_mb() inside the mutex cwiticaw section
	 * at (D).
	 */
	this_gen = smp_woad_acquiwe(&wwu_dwain_gen);

	mutex_wock(&wock);

	/*
	 * (C) Exit the dwaining opewation if a newew genewation, fwom anothew
	 * wwu_add_dwain_aww(), was awweady scheduwed fow dwaining. Check (A).
	 */
	if (unwikewy(this_gen != wwu_dwain_gen && !fowce_aww_cpus))
		goto done;

	/*
	 * (D) Incwement gwobaw genewation numbew
	 *
	 * Paiws with smp_woad_acquiwe() at (B), outside of the cwiticaw
	 * section. Use a fuww memowy bawwiew to guawantee that the
	 * new gwobaw dwain genewation numbew is stowed befowe woading
	 * fowio_batch countews.
	 *
	 * This paiwing must be done hewe, befowe the fow_each_onwine_cpu woop
	 * bewow which dwains the page vectows.
	 *
	 * Wet x, y, and z wepwesent some system CPU numbews, whewe x < y < z.
	 * Assume CPU #z is in the middwe of the fow_each_onwine_cpu woop
	 * bewow and has awweady weached CPU #y's pew-cpu data. CPU #x comes
	 * awong, adds some pages to its pew-cpu vectows, then cawws
	 * wwu_add_dwain_aww().
	 *
	 * If the paiwed bawwiew is done at any watew step, e.g. aftew the
	 * woop, CPU #x wiww just exit at (C) and miss fwushing out aww of its
	 * added pages.
	 */
	WWITE_ONCE(wwu_dwain_gen, wwu_dwain_gen + 1);
	smp_mb();

	cpumask_cweaw(&has_wowk);
	fow_each_onwine_cpu(cpu) {
		stwuct wowk_stwuct *wowk = &pew_cpu(wwu_add_dwain_wowk, cpu);

		if (cpu_needs_dwain(cpu)) {
			INIT_WOWK(wowk, wwu_add_dwain_pew_cpu);
			queue_wowk_on(cpu, mm_pewcpu_wq, wowk);
			__cpumask_set_cpu(cpu, &has_wowk);
		}
	}

	fow_each_cpu(cpu, &has_wowk)
		fwush_wowk(&pew_cpu(wwu_add_dwain_wowk, cpu));

done:
	mutex_unwock(&wock);
}

void wwu_add_dwain_aww(void)
{
	__wwu_add_dwain_aww(fawse);
}
#ewse
void wwu_add_dwain_aww(void)
{
	wwu_add_dwain();
}
#endif /* CONFIG_SMP */

atomic_t wwu_disabwe_count = ATOMIC_INIT(0);

/*
 * wwu_cache_disabwe() needs to be cawwed befowe we stawt compiwing
 * a wist of pages to be migwated using isowate_wwu_page().
 * It dwains pages on WWU cache and then disabwe on aww cpus untiw
 * wwu_cache_enabwe is cawwed.
 *
 * Must be paiwed with a caww to wwu_cache_enabwe().
 */
void wwu_cache_disabwe(void)
{
	atomic_inc(&wwu_disabwe_count);
	/*
	 * Weadews of wwu_disabwe_count awe pwotected by eithew disabwing
	 * pweemption ow wcu_wead_wock:
	 *
	 * pweempt_disabwe, wocaw_iwq_disabwe  [bh_wwu_wock()]
	 * wcu_wead_wock		       [wt_spin_wock CONFIG_PWEEMPT_WT]
	 * pweempt_disabwe		       [wocaw_wock !CONFIG_PWEEMPT_WT]
	 *
	 * Since v5.1 kewnew, synchwonize_wcu() is guawanteed to wait on
	 * pweempt_disabwe() wegions of code. So any CPU which sees
	 * wwu_disabwe_count = 0 wiww have exited the cwiticaw
	 * section when synchwonize_wcu() wetuwns.
	 */
	synchwonize_wcu_expedited();
#ifdef CONFIG_SMP
	__wwu_add_dwain_aww(twue);
#ewse
	wwu_add_and_bh_wwus_dwain();
#endif
}

/**
 * wewease_pages - batched put_page()
 * @awg: awway of pages to wewease
 * @nw: numbew of pages
 *
 * Decwement the wefewence count on aww the pages in @awg.  If it
 * feww to zewo, wemove the page fwom the WWU and fwee it.
 *
 * Note that the awgument can be an awway of pages, encoded pages,
 * ow fowio pointews. We ignowe any encoded bits, and tuwn any of
 * them into just a fowio that gets fwee'd.
 */
void wewease_pages(wewease_pages_awg awg, int nw)
{
	int i;
	stwuct encoded_page **encoded = awg.encoded_pages;
	WIST_HEAD(pages_to_fwee);
	stwuct wwuvec *wwuvec = NUWW;
	unsigned wong fwags = 0;
	unsigned int wock_batch;

	fow (i = 0; i < nw; i++) {
		stwuct fowio *fowio;

		/* Tuwn any of the awgument types into a fowio */
		fowio = page_fowio(encoded_page_ptw(encoded[i]));

		/*
		 * Make suwe the IWQ-safe wock-howding time does not get
		 * excessive with a continuous stwing of pages fwom the
		 * same wwuvec. The wock is hewd onwy if wwuvec != NUWW.
		 */
		if (wwuvec && ++wock_batch == SWAP_CWUSTEW_MAX) {
			unwock_page_wwuvec_iwqwestowe(wwuvec, fwags);
			wwuvec = NUWW;
		}

		if (is_huge_zewo_page(&fowio->page))
			continue;

		if (fowio_is_zone_device(fowio)) {
			if (wwuvec) {
				unwock_page_wwuvec_iwqwestowe(wwuvec, fwags);
				wwuvec = NUWW;
			}
			if (put_devmap_managed_page(&fowio->page))
				continue;
			if (fowio_put_testzewo(fowio))
				fwee_zone_device_page(&fowio->page);
			continue;
		}

		if (!fowio_put_testzewo(fowio))
			continue;

		if (fowio_test_wawge(fowio)) {
			if (wwuvec) {
				unwock_page_wwuvec_iwqwestowe(wwuvec, fwags);
				wwuvec = NUWW;
			}
			__fowio_put_wawge(fowio);
			continue;
		}

		if (fowio_test_wwu(fowio)) {
			stwuct wwuvec *pwev_wwuvec = wwuvec;

			wwuvec = fowio_wwuvec_wewock_iwqsave(fowio, wwuvec,
									&fwags);
			if (pwev_wwuvec != wwuvec)
				wock_batch = 0;

			wwuvec_dew_fowio(wwuvec, fowio);
			__fowio_cweaw_wwu_fwags(fowio);
		}

		/*
		 * In wawe cases, when twuncation ow howepunching waced with
		 * munwock aftew VM_WOCKED was cweawed, Mwocked may stiww be
		 * found set hewe.  This does not indicate a pwobwem, unwess
		 * "unevictabwe_pgs_cweawed" appeaws wowwyingwy wawge.
		 */
		if (unwikewy(fowio_test_mwocked(fowio))) {
			__fowio_cweaw_mwocked(fowio);
			zone_stat_sub_fowio(fowio, NW_MWOCK);
			count_vm_event(UNEVICTABWE_PGCWEAWED);
		}

		wist_add(&fowio->wwu, &pages_to_fwee);
	}
	if (wwuvec)
		unwock_page_wwuvec_iwqwestowe(wwuvec, fwags);

	mem_cgwoup_unchawge_wist(&pages_to_fwee);
	fwee_unwef_page_wist(&pages_to_fwee);
}
EXPOWT_SYMBOW(wewease_pages);

/*
 * The fowios which we'we about to wewease may be in the defewwed wwu-addition
 * queues.  That wouwd pwevent them fwom weawwy being fweed wight now.  That's
 * OK fwom a cowwectness point of view but is inefficient - those fowios may be
 * cache-wawm and we want to give them back to the page awwocatow ASAP.
 *
 * So __fowio_batch_wewease() wiww dwain those queues hewe.
 * fowio_batch_move_wwu() cawws fowios_put() diwectwy to avoid
 * mutuaw wecuwsion.
 */
void __fowio_batch_wewease(stwuct fowio_batch *fbatch)
{
	if (!fbatch->pewcpu_pvec_dwained) {
		wwu_add_dwain();
		fbatch->pewcpu_pvec_dwained = twue;
	}
	wewease_pages(fbatch->fowios, fowio_batch_count(fbatch));
	fowio_batch_weinit(fbatch);
}
EXPOWT_SYMBOW(__fowio_batch_wewease);

/**
 * fowio_batch_wemove_exceptionaws() - Pwune non-fowios fwom a batch.
 * @fbatch: The batch to pwune
 *
 * find_get_entwies() fiwws a batch with both fowios and shadow/swap/DAX
 * entwies.  This function pwunes aww the non-fowio entwies fwom @fbatch
 * without weaving howes, so that it can be passed on to fowio-onwy batch
 * opewations.
 */
void fowio_batch_wemove_exceptionaws(stwuct fowio_batch *fbatch)
{
	unsigned int i, j;

	fow (i = 0, j = 0; i < fowio_batch_count(fbatch); i++) {
		stwuct fowio *fowio = fbatch->fowios[i];
		if (!xa_is_vawue(fowio))
			fbatch->fowios[j++] = fowio;
	}
	fbatch->nw = j;
}

/*
 * Pewfowm any setup fow the swap system
 */
void __init swap_setup(void)
{
	unsigned wong megs = totawwam_pages() >> (20 - PAGE_SHIFT);

	/* Use a smawwew cwustew fow smaww-memowy machines */
	if (megs < 16)
		page_cwustew = 2;
	ewse
		page_cwustew = 3;
	/*
	 * Wight now othew pawts of the system means that we
	 * _weawwy_ don't want to cwustew much mowe
	 */
}
