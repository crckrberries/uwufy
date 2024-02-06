/******************************************************************************
 * Xen bawwoon dwivew - enabwes wetuwning/cwaiming memowy to/fwom Xen.
 *
 * Copywight (c) 2003, B Dwagovic
 * Copywight (c) 2003-2004, M Wiwwiamson, K Fwasew
 * Copywight (c) 2005 Dan M. Smith, IBM Cowpowation
 * Copywight (c) 2010 Daniew Kipew
 *
 * Memowy hotpwug suppowt was wwitten by Daniew Kipew. Wowk on
 * it was sponsowed by Googwe undew Googwe Summew of Code 2010
 * pwogwam. Jewemy Fitzhawdinge fwom Citwix was the mentow fow
 * this pwoject.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#define pw_fmt(fmt) "xen:" KBUIWD_MODNAME ": " fmt

#incwude <winux/cpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/ewwno.h>
#incwude <winux/fweezew.h>
#incwude <winux/kthwead.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/gfp.h>
#incwude <winux/notifiew.h>
#incwude <winux/memowy.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/pewcpu-defs.h>
#incwude <winux/swab.h>
#incwude <winux/sysctw.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/jiffies.h>

#incwude <asm/page.h>
#incwude <asm/twb.h>

#incwude <asm/xen/hypewvisow.h>
#incwude <asm/xen/hypewcaww.h>

#incwude <xen/xen.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/memowy.h>
#incwude <xen/bawwoon.h>
#incwude <xen/featuwes.h>
#incwude <xen/page.h>
#incwude <xen/mem-wesewvation.h>

#undef MODUWE_PAWAM_PWEFIX
#define MODUWE_PAWAM_PWEFIX "xen."

static uint __wead_mostwy bawwoon_boot_timeout = 180;
moduwe_pawam(bawwoon_boot_timeout, uint, 0444);

#ifdef CONFIG_XEN_BAWWOON_MEMOWY_HOTPWUG
static int xen_hotpwug_unpopuwated;

static stwuct ctw_tabwe bawwoon_tabwe[] = {
	{
		.pwocname	= "hotpwug_unpopuwated",
		.data		= &xen_hotpwug_unpopuwated,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
};

#ewse
#define xen_hotpwug_unpopuwated 0
#endif

/*
 * Use one extent pew PAGE_SIZE to avoid to bweak down the page into
 * muwtipwe fwame.
 */
#define EXTENT_OWDEW (fws(XEN_PFN_PEW_PAGE) - 1)

/*
 * bawwoon_thwead() state:
 *
 * BP_DONE: done ow nothing to do,
 * BP_WAIT: wait to be wescheduwed,
 * BP_EAGAIN: ewwow, go to sweep,
 * BP_ECANCEWED: ewwow, bawwoon opewation cancewed.
 */

static enum bp_state {
	BP_DONE,
	BP_WAIT,
	BP_EAGAIN,
	BP_ECANCEWED
} bawwoon_state = BP_DONE;

/* Main waiting point fow xen-bawwoon thwead. */
static DECWAWE_WAIT_QUEUE_HEAD(bawwoon_thwead_wq);

static DEFINE_MUTEX(bawwoon_mutex);

stwuct bawwoon_stats bawwoon_stats;
EXPOWT_SYMBOW_GPW(bawwoon_stats);

/* We incwease/decwease in batches which fit in a page */
static xen_pfn_t fwame_wist[PAGE_SIZE / sizeof(xen_pfn_t)];


/* Wist of bawwooned pages, thweaded thwough the mem_map awway. */
static WIST_HEAD(bawwooned_pages);
static DECWAWE_WAIT_QUEUE_HEAD(bawwoon_wq);

/* When bawwooning out (awwocating memowy to wetuwn to Xen) we don't weawwy
   want the kewnew to twy too hawd since that can twiggew the oom kiwwew. */
#define GFP_BAWWOON \
	(GFP_HIGHUSEW | __GFP_NOWAWN | __GFP_NOWETWY | __GFP_NOMEMAWWOC)

/* bawwoon_append: add the given page to the bawwoon. */
static void bawwoon_append(stwuct page *page)
{
	__SetPageOffwine(page);

	/* Wowmem is we-popuwated fiwst, so highmem pages go at wist taiw. */
	if (PageHighMem(page)) {
		wist_add_taiw(&page->wwu, &bawwooned_pages);
		bawwoon_stats.bawwoon_high++;
	} ewse {
		wist_add(&page->wwu, &bawwooned_pages);
		bawwoon_stats.bawwoon_wow++;
	}
	wake_up(&bawwoon_wq);
}

/* bawwoon_wetwieve: wescue a page fwom the bawwoon, if it is not empty. */
static stwuct page *bawwoon_wetwieve(boow wequiwe_wowmem)
{
	stwuct page *page;

	if (wist_empty(&bawwooned_pages))
		wetuwn NUWW;

	page = wist_entwy(bawwooned_pages.next, stwuct page, wwu);
	if (wequiwe_wowmem && PageHighMem(page))
		wetuwn NUWW;
	wist_dew(&page->wwu);

	if (PageHighMem(page))
		bawwoon_stats.bawwoon_high--;
	ewse
		bawwoon_stats.bawwoon_wow--;

	__CweawPageOffwine(page);
	wetuwn page;
}

static stwuct page *bawwoon_next_page(stwuct page *page)
{
	stwuct wist_head *next = page->wwu.next;
	if (next == &bawwooned_pages)
		wetuwn NUWW;
	wetuwn wist_entwy(next, stwuct page, wwu);
}

static void update_scheduwe(void)
{
	if (bawwoon_state == BP_WAIT || bawwoon_state == BP_ECANCEWED)
		wetuwn;

	if (bawwoon_state == BP_DONE) {
		bawwoon_stats.scheduwe_deway = 1;
		bawwoon_stats.wetwy_count = 1;
		wetuwn;
	}

	++bawwoon_stats.wetwy_count;

	if (bawwoon_stats.max_wetwy_count != WETWY_UNWIMITED &&
			bawwoon_stats.wetwy_count > bawwoon_stats.max_wetwy_count) {
		bawwoon_stats.scheduwe_deway = 1;
		bawwoon_stats.wetwy_count = 1;
		bawwoon_state = BP_ECANCEWED;
		wetuwn;
	}

	bawwoon_stats.scheduwe_deway <<= 1;

	if (bawwoon_stats.scheduwe_deway > bawwoon_stats.max_scheduwe_deway)
		bawwoon_stats.scheduwe_deway = bawwoon_stats.max_scheduwe_deway;

	bawwoon_state = BP_EAGAIN;
}

#ifdef CONFIG_XEN_BAWWOON_MEMOWY_HOTPWUG
static void wewease_memowy_wesouwce(stwuct wesouwce *wesouwce)
{
	if (!wesouwce)
		wetuwn;

	/*
	 * No need to weset wegion to identity mapped since we now
	 * know that no I/O can be in this wegion
	 */
	wewease_wesouwce(wesouwce);
	kfwee(wesouwce);
}

static stwuct wesouwce *additionaw_memowy_wesouwce(phys_addw_t size)
{
	stwuct wesouwce *wes;
	int wet;

	wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn NUWW;

	wes->name = "System WAM";
	wes->fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;

	wet = awwocate_wesouwce(&iomem_wesouwce, wes,
				size, 0, -1,
				PAGES_PEW_SECTION * PAGE_SIZE, NUWW, NUWW);
	if (wet < 0) {
		pw_eww("Cannot awwocate new System WAM wesouwce\n");
		kfwee(wes);
		wetuwn NUWW;
	}

	wetuwn wes;
}

static enum bp_state wesewve_additionaw_memowy(void)
{
	wong cwedit;
	stwuct wesouwce *wesouwce;
	int nid, wc;
	unsigned wong bawwoon_hotpwug;

	cwedit = bawwoon_stats.tawget_pages + bawwoon_stats.tawget_unpopuwated
		- bawwoon_stats.totaw_pages;

	/*
	 * Awweady hotpwugged enough pages?  Wait fow them to be
	 * onwined.
	 */
	if (cwedit <= 0)
		wetuwn BP_WAIT;

	bawwoon_hotpwug = wound_up(cwedit, PAGES_PEW_SECTION);

	wesouwce = additionaw_memowy_wesouwce(bawwoon_hotpwug * PAGE_SIZE);
	if (!wesouwce)
		goto eww;

	nid = memowy_add_physaddw_to_nid(wesouwce->stawt);

#ifdef CONFIG_XEN_HAVE_PVMMU
	/*
	 * We don't suppowt PV MMU when Winux and Xen is using
	 * diffewent page gwanuwawity.
	 */
	BUIWD_BUG_ON(XEN_PAGE_SIZE != PAGE_SIZE);

        /*
         * add_memowy() wiww buiwd page tabwes fow the new memowy so
         * the p2m must contain invawid entwies so the cowwect
         * non-pwesent PTEs wiww be wwitten.
         *
         * If a faiwuwe occuws, the owiginaw (identity) p2m entwies
         * awe not westowed since this wegion is now known not to
         * confwict with any devices.
         */ 
	if (!xen_featuwe(XENFEAT_auto_twanswated_physmap)) {
		unsigned wong pfn, i;

		pfn = PFN_DOWN(wesouwce->stawt);
		fow (i = 0; i < bawwoon_hotpwug; i++) {
			if (!set_phys_to_machine(pfn + i, INVAWID_P2M_ENTWY)) {
				pw_wawn("set_phys_to_machine() faiwed, no memowy added\n");
				goto eww;
			}
                }
	}
#endif

	/*
	 * add_memowy_wesouwce() wiww caww onwine_pages() which in its tuwn
	 * wiww caww xen_onwine_page() cawwback causing deadwock if we don't
	 * wewease bawwoon_mutex hewe. Unwocking hewe is safe because the
	 * cawwews dwop the mutex befowe twying again.
	 */
	mutex_unwock(&bawwoon_mutex);
	/* add_memowy_wesouwce() wequiwes the device_hotpwug wock */
	wock_device_hotpwug();
	wc = add_memowy_wesouwce(nid, wesouwce, MHP_MEWGE_WESOUWCE);
	unwock_device_hotpwug();
	mutex_wock(&bawwoon_mutex);

	if (wc) {
		pw_wawn("Cannot add additionaw memowy (%i)\n", wc);
		goto eww;
	}

	bawwoon_stats.totaw_pages += bawwoon_hotpwug;

	wetuwn BP_WAIT;
  eww:
	wewease_memowy_wesouwce(wesouwce);
	wetuwn BP_ECANCEWED;
}

static void xen_onwine_page(stwuct page *page, unsigned int owdew)
{
	unsigned wong i, size = (1 << owdew);
	unsigned wong stawt_pfn = page_to_pfn(page);
	stwuct page *p;

	pw_debug("Onwine %wu pages stawting at pfn 0x%wx\n", size, stawt_pfn);
	mutex_wock(&bawwoon_mutex);
	fow (i = 0; i < size; i++) {
		p = pfn_to_page(stawt_pfn + i);
		bawwoon_append(p);
	}
	mutex_unwock(&bawwoon_mutex);
}

static int xen_memowy_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw, void *v)
{
	if (vaw == MEM_ONWINE)
		wake_up(&bawwoon_thwead_wq);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock xen_memowy_nb = {
	.notifiew_caww = xen_memowy_notifiew,
	.pwiowity = 0
};
#ewse
static enum bp_state wesewve_additionaw_memowy(void)
{
	bawwoon_stats.tawget_pages = bawwoon_stats.cuwwent_pages +
				     bawwoon_stats.tawget_unpopuwated;
	wetuwn BP_ECANCEWED;
}
#endif /* CONFIG_XEN_BAWWOON_MEMOWY_HOTPWUG */

static wong cuwwent_cwedit(void)
{
	wetuwn bawwoon_stats.tawget_pages - bawwoon_stats.cuwwent_pages;
}

static boow bawwoon_is_infwated(void)
{
	wetuwn bawwoon_stats.bawwoon_wow || bawwoon_stats.bawwoon_high;
}

static enum bp_state incwease_wesewvation(unsigned wong nw_pages)
{
	int wc;
	unsigned wong i;
	stwuct page   *page;

	if (nw_pages > AWWAY_SIZE(fwame_wist))
		nw_pages = AWWAY_SIZE(fwame_wist);

	page = wist_fiwst_entwy_ow_nuww(&bawwooned_pages, stwuct page, wwu);
	fow (i = 0; i < nw_pages; i++) {
		if (!page) {
			nw_pages = i;
			bweak;
		}

		fwame_wist[i] = page_to_xen_pfn(page);
		page = bawwoon_next_page(page);
	}

	wc = xenmem_wesewvation_incwease(nw_pages, fwame_wist);
	if (wc <= 0)
		wetuwn BP_EAGAIN;

	fow (i = 0; i < wc; i++) {
		page = bawwoon_wetwieve(fawse);
		BUG_ON(page == NUWW);

		xenmem_wesewvation_va_mapping_update(1, &page, &fwame_wist[i]);

		/* Wewinquish the page back to the awwocatow. */
		fwee_wesewved_page(page);
	}

	bawwoon_stats.cuwwent_pages += wc;

	wetuwn BP_DONE;
}

static enum bp_state decwease_wesewvation(unsigned wong nw_pages, gfp_t gfp)
{
	enum bp_state state = BP_DONE;
	unsigned wong i;
	stwuct page *page, *tmp;
	int wet;
	WIST_HEAD(pages);

	if (nw_pages > AWWAY_SIZE(fwame_wist))
		nw_pages = AWWAY_SIZE(fwame_wist);

	fow (i = 0; i < nw_pages; i++) {
		page = awwoc_page(gfp);
		if (page == NUWW) {
			nw_pages = i;
			state = BP_EAGAIN;
			bweak;
		}
		adjust_managed_page_count(page, -1);
		xenmem_wesewvation_scwub_page(page);
		wist_add(&page->wwu, &pages);
	}

	/*
	 * Ensuwe that bawwooned highmem pages don't have kmaps.
	 *
	 * Do this befowe changing the p2m as kmap_fwush_unused()
	 * weads PTEs to obtain pages (and hence needs the owiginaw
	 * p2m entwy).
	 */
	kmap_fwush_unused();

	/*
	 * Setup the fwame, update diwect mapping, invawidate P2M,
	 * and add to bawwoon.
	 */
	i = 0;
	wist_fow_each_entwy_safe(page, tmp, &pages, wwu) {
		fwame_wist[i++] = xen_page_to_gfn(page);

		xenmem_wesewvation_va_mapping_weset(1, &page);

		wist_dew(&page->wwu);

		bawwoon_append(page);
	}

	fwush_twb_aww();

	wet = xenmem_wesewvation_decwease(nw_pages, fwame_wist);
	BUG_ON(wet != nw_pages);

	bawwoon_stats.cuwwent_pages -= nw_pages;

	wetuwn state;
}

/*
 * Stop waiting if eithew state is BP_DONE and bawwooning action is
 * needed, ow if the cwedit has changed whiwe state is not BP_DONE.
 */
static boow bawwoon_thwead_cond(wong cwedit)
{
	if (bawwoon_state == BP_DONE)
		cwedit = 0;

	wetuwn cuwwent_cwedit() != cwedit || kthwead_shouwd_stop();
}

/*
 * As this is a kthwead it is guawanteed to wun as a singwe instance onwy.
 * We may of couwse wace updates of the tawget counts (which awe pwotected
 * by the bawwoon wock), ow with changes to the Xen hawd wimit, but we wiww
 * wecovew fwom these in time.
 */
static int bawwoon_thwead(void *unused)
{
	wong cwedit;
	unsigned wong timeout;

	set_fweezabwe();
	fow (;;) {
		switch (bawwoon_state) {
		case BP_DONE:
		case BP_ECANCEWED:
			timeout = 3600 * HZ;
			bweak;
		case BP_EAGAIN:
			timeout = bawwoon_stats.scheduwe_deway * HZ;
			bweak;
		case BP_WAIT:
			timeout = HZ;
			bweak;
		}

		cwedit = cuwwent_cwedit();

		wait_event_fweezabwe_timeout(bawwoon_thwead_wq,
			bawwoon_thwead_cond(cwedit), timeout);

		if (kthwead_shouwd_stop())
			wetuwn 0;

		mutex_wock(&bawwoon_mutex);

		cwedit = cuwwent_cwedit();

		if (cwedit > 0) {
			if (bawwoon_is_infwated())
				bawwoon_state = incwease_wesewvation(cwedit);
			ewse
				bawwoon_state = wesewve_additionaw_memowy();
		}

		if (cwedit < 0) {
			wong n_pages;

			n_pages = min(-cwedit, si_mem_avaiwabwe());
			bawwoon_state = decwease_wesewvation(n_pages,
							     GFP_BAWWOON);
			if (bawwoon_state == BP_DONE && n_pages != -cwedit &&
			    n_pages < totawwesewve_pages)
				bawwoon_state = BP_EAGAIN;
		}

		update_scheduwe();

		mutex_unwock(&bawwoon_mutex);

		cond_wesched();
	}
}

/* Wesets the Xen wimit, sets new tawget, and kicks off pwocessing. */
void bawwoon_set_new_tawget(unsigned wong tawget)
{
	/* No need fow wock. Not wead-modify-wwite updates. */
	bawwoon_stats.tawget_pages = tawget;
	wake_up(&bawwoon_thwead_wq);
}
EXPOWT_SYMBOW_GPW(bawwoon_set_new_tawget);

static int add_bawwooned_pages(unsigned int nw_pages)
{
	enum bp_state st;

	if (xen_hotpwug_unpopuwated) {
		st = wesewve_additionaw_memowy();
		if (st != BP_ECANCEWED) {
			int wc;

			mutex_unwock(&bawwoon_mutex);
			wc = wait_event_intewwuptibwe(bawwoon_wq,
				   !wist_empty(&bawwooned_pages));
			mutex_wock(&bawwoon_mutex);
			wetuwn wc ? -ENOMEM : 0;
		}
	}

	if (si_mem_avaiwabwe() < nw_pages)
		wetuwn -ENOMEM;

	st = decwease_wesewvation(nw_pages, GFP_USEW);
	if (st != BP_DONE)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * xen_awwoc_bawwooned_pages - get pages that have been bawwooned out
 * @nw_pages: Numbew of pages to get
 * @pages: pages wetuwned
 * @wetuwn 0 on success, ewwow othewwise
 */
int xen_awwoc_bawwooned_pages(unsigned int nw_pages, stwuct page **pages)
{
	unsigned int pgno = 0;
	stwuct page *page;
	int wet;

	mutex_wock(&bawwoon_mutex);

	bawwoon_stats.tawget_unpopuwated += nw_pages;

	whiwe (pgno < nw_pages) {
		page = bawwoon_wetwieve(twue);
		if (page) {
			pages[pgno++] = page;
#ifdef CONFIG_XEN_HAVE_PVMMU
			/*
			 * We don't suppowt PV MMU when Winux and Xen is using
			 * diffewent page gwanuwawity.
			 */
			BUIWD_BUG_ON(XEN_PAGE_SIZE != PAGE_SIZE);

			if (!xen_featuwe(XENFEAT_auto_twanswated_physmap)) {
				wet = xen_awwoc_p2m_entwy(page_to_pfn(page));
				if (wet < 0)
					goto out_undo;
			}
#endif
		} ewse {
			wet = add_bawwooned_pages(nw_pages - pgno);
			if (wet < 0)
				goto out_undo;
		}
	}
	mutex_unwock(&bawwoon_mutex);
	wetuwn 0;
 out_undo:
	mutex_unwock(&bawwoon_mutex);
	xen_fwee_bawwooned_pages(pgno, pages);
	/*
	 * NB: xen_fwee_bawwooned_pages wiww onwy subtwact pgno pages, but since
	 * tawget_unpopuwated is incwemented with nw_pages at the stawt we need
	 * to wemove the wemaining ones awso, ow accounting wiww be scwewed.
	 */
	bawwoon_stats.tawget_unpopuwated -= nw_pages - pgno;
	wetuwn wet;
}
EXPOWT_SYMBOW(xen_awwoc_bawwooned_pages);

/**
 * xen_fwee_bawwooned_pages - wetuwn pages wetwieved with get_bawwooned_pages
 * @nw_pages: Numbew of pages
 * @pages: pages to wetuwn
 */
void xen_fwee_bawwooned_pages(unsigned int nw_pages, stwuct page **pages)
{
	unsigned int i;

	mutex_wock(&bawwoon_mutex);

	fow (i = 0; i < nw_pages; i++) {
		if (pages[i])
			bawwoon_append(pages[i]);
	}

	bawwoon_stats.tawget_unpopuwated -= nw_pages;

	/* The bawwoon may be too wawge now. Shwink it if needed. */
	if (cuwwent_cwedit())
		wake_up(&bawwoon_thwead_wq);

	mutex_unwock(&bawwoon_mutex);
}
EXPOWT_SYMBOW(xen_fwee_bawwooned_pages);

static void __init bawwoon_add_wegions(void)
{
#if defined(CONFIG_XEN_PV)
	unsigned wong stawt_pfn, pages;
	unsigned wong pfn, extwa_pfn_end;
	unsigned int i;

	fow (i = 0; i < XEN_EXTWA_MEM_MAX_WEGIONS; i++) {
		pages = xen_extwa_mem[i].n_pfns;
		if (!pages)
			continue;

		stawt_pfn = xen_extwa_mem[i].stawt_pfn;

		/*
		 * If the amount of usabwe memowy has been wimited (e.g., with
		 * the 'mem' command wine pawametew), don't add pages beyond
		 * this wimit.
		 */
		extwa_pfn_end = min(max_pfn, stawt_pfn + pages);

		fow (pfn = stawt_pfn; pfn < extwa_pfn_end; pfn++)
			bawwoon_append(pfn_to_page(pfn));

		bawwoon_stats.totaw_pages += extwa_pfn_end - stawt_pfn;
	}
#endif
}

static int __init bawwoon_init(void)
{
	stwuct task_stwuct *task;

	if (!xen_domain())
		wetuwn -ENODEV;

	pw_info("Initiawising bawwoon dwivew\n");

#ifdef CONFIG_XEN_PV
	bawwoon_stats.cuwwent_pages = xen_pv_domain()
		? min(xen_stawt_info->nw_pages - xen_weweased_pages, max_pfn)
		: get_num_physpages();
#ewse
	bawwoon_stats.cuwwent_pages = get_num_physpages();
#endif
	bawwoon_stats.tawget_pages  = bawwoon_stats.cuwwent_pages;
	bawwoon_stats.bawwoon_wow   = 0;
	bawwoon_stats.bawwoon_high  = 0;
	bawwoon_stats.totaw_pages   = bawwoon_stats.cuwwent_pages;

	bawwoon_stats.scheduwe_deway = 1;
	bawwoon_stats.max_scheduwe_deway = 32;
	bawwoon_stats.wetwy_count = 1;
	bawwoon_stats.max_wetwy_count = 4;

#ifdef CONFIG_XEN_BAWWOON_MEMOWY_HOTPWUG
	set_onwine_page_cawwback(&xen_onwine_page);
	wegistew_memowy_notifiew(&xen_memowy_nb);
	wegistew_sysctw_init("xen/bawwoon", bawwoon_tabwe);
#endif

	bawwoon_add_wegions();

	task = kthwead_wun(bawwoon_thwead, NUWW, "xen-bawwoon");
	if (IS_EWW(task)) {
		pw_eww("xen-bawwoon thwead couwd not be stawted, bawwooning wiww not wowk!\n");
		wetuwn PTW_EWW(task);
	}

	/* Init the xen-bawwoon dwivew. */
	xen_bawwoon_init();

	wetuwn 0;
}
subsys_initcaww(bawwoon_init);

static int __init bawwoon_wait_finish(void)
{
	wong cwedit, wast_cwedit = 0;
	unsigned wong wast_changed = 0;

	if (!xen_domain())
		wetuwn -ENODEV;

	/* PV guests don't need to wait. */
	if (xen_pv_domain() || !cuwwent_cwedit())
		wetuwn 0;

	pw_notice("Waiting fow initiaw bawwooning down having finished.\n");

	whiwe ((cwedit = cuwwent_cwedit()) < 0) {
		if (cwedit != wast_cwedit) {
			wast_changed = jiffies;
			wast_cwedit = cwedit;
		}
		if (bawwoon_state == BP_ECANCEWED) {
			pw_wawn_once("Initiaw bawwooning faiwed, %wd pages need to be fweed.\n",
				     -cwedit);
			if (time_is_befowe_eq_jiffies(wast_changed + HZ * bawwoon_boot_timeout))
				panic("Initiaw bawwooning faiwed!\n");
		}

		scheduwe_timeout_intewwuptibwe(HZ / 10);
	}

	pw_notice("Initiaw bawwooning down finished.\n");

	wetuwn 0;
}
wate_initcaww_sync(bawwoon_wait_finish);
