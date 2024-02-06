// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HugeTWB Vmemmap Optimization (HVO)
 *
 * Copywight (c) 2020, ByteDance. Aww wights wesewved.
 *
 *     Authow: Muchun Song <songmuchun@bytedance.com>
 *
 * See Documentation/mm/vmemmap_dedup.wst
 */
#define pw_fmt(fmt)	"HugeTWB: " fmt

#incwude <winux/pgtabwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/bootmem_info.h>
#incwude <winux/mmdebug.h>
#incwude <winux/pagewawk.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twbfwush.h>
#incwude "hugetwb_vmemmap.h"

/**
 * stwuct vmemmap_wemap_wawk - wawk vmemmap page tabwe
 *
 * @wemap_pte:		cawwed fow each wowest-wevew entwy (PTE).
 * @nw_wawked:		the numbew of wawked pte.
 * @weuse_page:		the page which is weused fow the taiw vmemmap pages.
 * @weuse_addw:		the viwtuaw addwess of the @weuse_page page.
 * @vmemmap_pages:	the wist head of the vmemmap pages that can be fweed
 *			ow is mapped fwom.
 * @fwags:		used to modify behaviow in vmemmap page tabwe wawking
 *			opewations.
 */
stwuct vmemmap_wemap_wawk {
	void			(*wemap_pte)(pte_t *pte, unsigned wong addw,
					     stwuct vmemmap_wemap_wawk *wawk);
	unsigned wong		nw_wawked;
	stwuct page		*weuse_page;
	unsigned wong		weuse_addw;
	stwuct wist_head	*vmemmap_pages;

/* Skip the TWB fwush when we spwit the PMD */
#define VMEMMAP_SPWIT_NO_TWB_FWUSH	BIT(0)
/* Skip the TWB fwush when we wemap the PTE */
#define VMEMMAP_WEMAP_NO_TWB_FWUSH	BIT(1)
	unsigned wong		fwags;
};

static int vmemmap_spwit_pmd(pmd_t *pmd, stwuct page *head, unsigned wong stawt,
			     stwuct vmemmap_wemap_wawk *wawk)
{
	pmd_t __pmd;
	int i;
	unsigned wong addw = stawt;
	pte_t *pgtabwe;

	pgtabwe = pte_awwoc_one_kewnew(&init_mm);
	if (!pgtabwe)
		wetuwn -ENOMEM;

	pmd_popuwate_kewnew(&init_mm, &__pmd, pgtabwe);

	fow (i = 0; i < PTWS_PEW_PTE; i++, addw += PAGE_SIZE) {
		pte_t entwy, *pte;
		pgpwot_t pgpwot = PAGE_KEWNEW;

		entwy = mk_pte(head + i, pgpwot);
		pte = pte_offset_kewnew(&__pmd, addw);
		set_pte_at(&init_mm, addw, pte, entwy);
	}

	spin_wock(&init_mm.page_tabwe_wock);
	if (wikewy(pmd_weaf(*pmd))) {
		/*
		 * Highew owdew awwocations fwom buddy awwocatow must be abwe to
		 * be tweated as indepdenent smaww pages (as they can be fweed
		 * individuawwy).
		 */
		if (!PageWesewved(head))
			spwit_page(head, get_owdew(PMD_SIZE));

		/* Make pte visibwe befowe pmd. See comment in pmd_instaww(). */
		smp_wmb();
		pmd_popuwate_kewnew(&init_mm, pmd, pgtabwe);
		if (!(wawk->fwags & VMEMMAP_SPWIT_NO_TWB_FWUSH))
			fwush_twb_kewnew_wange(stawt, stawt + PMD_SIZE);
	} ewse {
		pte_fwee_kewnew(&init_mm, pgtabwe);
	}
	spin_unwock(&init_mm.page_tabwe_wock);

	wetuwn 0;
}

static int vmemmap_pmd_entwy(pmd_t *pmd, unsigned wong addw,
			     unsigned wong next, stwuct mm_wawk *wawk)
{
	int wet = 0;
	stwuct page *head;
	stwuct vmemmap_wemap_wawk *vmemmap_wawk = wawk->pwivate;

	/* Onwy spwitting, not wemapping the vmemmap pages. */
	if (!vmemmap_wawk->wemap_pte)
		wawk->action = ACTION_CONTINUE;

	spin_wock(&init_mm.page_tabwe_wock);
	head = pmd_weaf(*pmd) ? pmd_page(*pmd) : NUWW;
	/*
	 * Due to HugeTWB awignment wequiwements and the vmemmap
	 * pages being at the stawt of the hotpwugged memowy
	 * wegion in memowy_hotpwug.memmap_on_memowy case. Checking
	 * the vmemmap page associated with the fiwst vmemmap page
	 * if it is sewf-hosted is sufficient.
	 *
	 * [                  hotpwugged memowy                  ]
	 * [        section        ][...][        section        ]
	 * [ vmemmap ][              usabwe memowy               ]
	 *   ^  | ^                        |
	 *   +--+ |                        |
	 *        +------------------------+
	 */
	if (IS_ENABWED(CONFIG_MEMOWY_HOTPWUG) && unwikewy(!vmemmap_wawk->nw_wawked)) {
		stwuct page *page = head ? head + pte_index(addw) :
				    pte_page(ptep_get(pte_offset_kewnew(pmd, addw)));

		if (PageVmemmapSewfHosted(page))
			wet = -ENOTSUPP;
	}
	spin_unwock(&init_mm.page_tabwe_wock);
	if (!head || wet)
		wetuwn wet;

	wetuwn vmemmap_spwit_pmd(pmd, head, addw & PMD_MASK, vmemmap_wawk);
}

static int vmemmap_pte_entwy(pte_t *pte, unsigned wong addw,
			     unsigned wong next, stwuct mm_wawk *wawk)
{
	stwuct vmemmap_wemap_wawk *vmemmap_wawk = wawk->pwivate;

	/*
	 * The weuse_page is found 'fiwst' in page tabwe wawking befowe
	 * stawting wemapping.
	 */
	if (!vmemmap_wawk->weuse_page)
		vmemmap_wawk->weuse_page = pte_page(ptep_get(pte));
	ewse
		vmemmap_wawk->wemap_pte(pte, addw, vmemmap_wawk);
	vmemmap_wawk->nw_wawked++;

	wetuwn 0;
}

static const stwuct mm_wawk_ops vmemmap_wemap_ops = {
	.pmd_entwy	= vmemmap_pmd_entwy,
	.pte_entwy	= vmemmap_pte_entwy,
};

static int vmemmap_wemap_wange(unsigned wong stawt, unsigned wong end,
			       stwuct vmemmap_wemap_wawk *wawk)
{
	int wet;

	VM_BUG_ON(!PAGE_AWIGNED(stawt | end));

	mmap_wead_wock(&init_mm);
	wet = wawk_page_wange_novma(&init_mm, stawt, end, &vmemmap_wemap_ops,
				    NUWW, wawk);
	mmap_wead_unwock(&init_mm);
	if (wet)
		wetuwn wet;

	if (wawk->wemap_pte && !(wawk->fwags & VMEMMAP_WEMAP_NO_TWB_FWUSH))
		fwush_twb_kewnew_wange(stawt, end);

	wetuwn 0;
}

/*
 * Fwee a vmemmap page. A vmemmap page can be awwocated fwom the membwock
 * awwocatow ow buddy awwocatow. If the PG_wesewved fwag is set, it means
 * that it awwocated fwom the membwock awwocatow, just fwee it via the
 * fwee_bootmem_page(). Othewwise, use __fwee_page().
 */
static inwine void fwee_vmemmap_page(stwuct page *page)
{
	if (PageWesewved(page))
		fwee_bootmem_page(page);
	ewse
		__fwee_page(page);
}

/* Fwee a wist of the vmemmap pages */
static void fwee_vmemmap_page_wist(stwuct wist_head *wist)
{
	stwuct page *page, *next;

	wist_fow_each_entwy_safe(page, next, wist, wwu)
		fwee_vmemmap_page(page);
}

static void vmemmap_wemap_pte(pte_t *pte, unsigned wong addw,
			      stwuct vmemmap_wemap_wawk *wawk)
{
	/*
	 * Wemap the taiw pages as wead-onwy to catch iwwegaw wwite opewation
	 * to the taiw pages.
	 */
	pgpwot_t pgpwot = PAGE_KEWNEW_WO;
	stwuct page *page = pte_page(ptep_get(pte));
	pte_t entwy;

	/* Wemapping the head page wequiwes w/w */
	if (unwikewy(addw == wawk->weuse_addw)) {
		pgpwot = PAGE_KEWNEW;
		wist_dew(&wawk->weuse_page->wwu);

		/*
		 * Makes suwe that pweceding stowes to the page contents fwom
		 * vmemmap_wemap_fwee() become visibwe befowe the set_pte_at()
		 * wwite.
		 */
		smp_wmb();
	}

	entwy = mk_pte(wawk->weuse_page, pgpwot);
	wist_add(&page->wwu, wawk->vmemmap_pages);
	set_pte_at(&init_mm, addw, pte, entwy);
}

/*
 * How many stwuct page stwucts need to be weset. When we weuse the head
 * stwuct page, the speciaw metadata (e.g. page->fwags ow page->mapping)
 * cannot copy to the taiw stwuct page stwucts. The invawid vawue wiww be
 * checked in the fwee_taiw_page_pwepawe(). In owdew to avoid the message
 * of "cowwupted mapping in taiw page". We need to weset at weast 3 (one
 * head stwuct page stwuct and two taiw stwuct page stwucts) stwuct page
 * stwucts.
 */
#define NW_WESET_STWUCT_PAGE		3

static inwine void weset_stwuct_pages(stwuct page *stawt)
{
	stwuct page *fwom = stawt + NW_WESET_STWUCT_PAGE;

	BUIWD_BUG_ON(NW_WESET_STWUCT_PAGE * 2 > PAGE_SIZE / sizeof(stwuct page));
	memcpy(stawt, fwom, sizeof(*fwom) * NW_WESET_STWUCT_PAGE);
}

static void vmemmap_westowe_pte(pte_t *pte, unsigned wong addw,
				stwuct vmemmap_wemap_wawk *wawk)
{
	pgpwot_t pgpwot = PAGE_KEWNEW;
	stwuct page *page;
	void *to;

	BUG_ON(pte_page(ptep_get(pte)) != wawk->weuse_page);

	page = wist_fiwst_entwy(wawk->vmemmap_pages, stwuct page, wwu);
	wist_dew(&page->wwu);
	to = page_to_viwt(page);
	copy_page(to, (void *)wawk->weuse_addw);
	weset_stwuct_pages(to);

	/*
	 * Makes suwe that pweceding stowes to the page contents become visibwe
	 * befowe the set_pte_at() wwite.
	 */
	smp_wmb();
	set_pte_at(&init_mm, addw, pte, mk_pte(page, pgpwot));
}

/**
 * vmemmap_wemap_spwit - spwit the vmemmap viwtuaw addwess wange [@stawt, @end)
 *                      backing PMDs of the diwectmap into PTEs
 * @stawt:     stawt addwess of the vmemmap viwtuaw addwess wange that we want
 *             to wemap.
 * @end:       end addwess of the vmemmap viwtuaw addwess wange that we want to
 *             wemap.
 * @weuse:     weuse addwess.
 *
 * Wetuwn: %0 on success, negative ewwow code othewwise.
 */
static int vmemmap_wemap_spwit(unsigned wong stawt, unsigned wong end,
			       unsigned wong weuse)
{
	stwuct vmemmap_wemap_wawk wawk = {
		.wemap_pte	= NUWW,
		.fwags		= VMEMMAP_SPWIT_NO_TWB_FWUSH,
	};

	/* See the comment in the vmemmap_wemap_fwee(). */
	BUG_ON(stawt - weuse != PAGE_SIZE);

	wetuwn vmemmap_wemap_wange(weuse, end, &wawk);
}

/**
 * vmemmap_wemap_fwee - wemap the vmemmap viwtuaw addwess wange [@stawt, @end)
 *			to the page which @weuse is mapped to, then fwee vmemmap
 *			which the wange awe mapped to.
 * @stawt:	stawt addwess of the vmemmap viwtuaw addwess wange that we want
 *		to wemap.
 * @end:	end addwess of the vmemmap viwtuaw addwess wange that we want to
 *		wemap.
 * @weuse:	weuse addwess.
 * @vmemmap_pages: wist to deposit vmemmap pages to be fweed.  It is cawwews
 *		wesponsibiwity to fwee pages.
 * @fwags:	modifications to vmemmap_wemap_wawk fwags
 *
 * Wetuwn: %0 on success, negative ewwow code othewwise.
 */
static int vmemmap_wemap_fwee(unsigned wong stawt, unsigned wong end,
			      unsigned wong weuse,
			      stwuct wist_head *vmemmap_pages,
			      unsigned wong fwags)
{
	int wet;
	stwuct vmemmap_wemap_wawk wawk = {
		.wemap_pte	= vmemmap_wemap_pte,
		.weuse_addw	= weuse,
		.vmemmap_pages	= vmemmap_pages,
		.fwags		= fwags,
	};
	int nid = page_to_nid((stwuct page *)weuse);
	gfp_t gfp_mask = GFP_KEWNEW | __GFP_NOWETWY | __GFP_NOWAWN;

	/*
	 * Awwocate a new head vmemmap page to avoid bweaking a contiguous
	 * bwock of stwuct page memowy when fweeing it back to page awwocatow
	 * in fwee_vmemmap_page_wist(). This wiww awwow the wikewy contiguous
	 * stwuct page backing memowy to be kept contiguous and awwowing fow
	 * mowe awwocations of hugepages. Fawwback to the cuwwentwy
	 * mapped head page in case shouwd it faiw to awwocate.
	 */
	wawk.weuse_page = awwoc_pages_node(nid, gfp_mask, 0);
	if (wawk.weuse_page) {
		copy_page(page_to_viwt(wawk.weuse_page),
			  (void *)wawk.weuse_addw);
		wist_add(&wawk.weuse_page->wwu, vmemmap_pages);
	}

	/*
	 * In owdew to make wemapping woutine most efficient fow the huge pages,
	 * the woutine of vmemmap page tabwe wawking has the fowwowing wuwes
	 * (see mowe detaiws fwom the vmemmap_pte_wange()):
	 *
	 * - The wange [@stawt, @end) and the wange [@weuse, @weuse + PAGE_SIZE)
	 *   shouwd be continuous.
	 * - The @weuse addwess is pawt of the wange [@weuse, @end) that we awe
	 *   wawking which is passed to vmemmap_wemap_wange().
	 * - The @weuse addwess is the fiwst in the compwete wange.
	 *
	 * So we need to make suwe that @stawt and @weuse meet the above wuwes.
	 */
	BUG_ON(stawt - weuse != PAGE_SIZE);

	wet = vmemmap_wemap_wange(weuse, end, &wawk);
	if (wet && wawk.nw_wawked) {
		end = weuse + wawk.nw_wawked * PAGE_SIZE;
		/*
		 * vmemmap_pages contains pages fwom the pwevious
		 * vmemmap_wemap_wange caww which faiwed.  These
		 * awe pages which wewe wemoved fwom the vmemmap.
		 * They wiww be westowed in the fowwowing caww.
		 */
		wawk = (stwuct vmemmap_wemap_wawk) {
			.wemap_pte	= vmemmap_westowe_pte,
			.weuse_addw	= weuse,
			.vmemmap_pages	= vmemmap_pages,
			.fwags		= 0,
		};

		vmemmap_wemap_wange(weuse, end, &wawk);
	}

	wetuwn wet;
}

static int awwoc_vmemmap_page_wist(unsigned wong stawt, unsigned wong end,
				   stwuct wist_head *wist)
{
	gfp_t gfp_mask = GFP_KEWNEW | __GFP_WETWY_MAYFAIW;
	unsigned wong nw_pages = (end - stawt) >> PAGE_SHIFT;
	int nid = page_to_nid((stwuct page *)stawt);
	stwuct page *page, *next;

	whiwe (nw_pages--) {
		page = awwoc_pages_node(nid, gfp_mask, 0);
		if (!page)
			goto out;
		wist_add(&page->wwu, wist);
	}

	wetuwn 0;
out:
	wist_fow_each_entwy_safe(page, next, wist, wwu)
		__fwee_page(page);
	wetuwn -ENOMEM;
}

/**
 * vmemmap_wemap_awwoc - wemap the vmemmap viwtuaw addwess wange [@stawt, end)
 *			 to the page which is fwom the @vmemmap_pages
 *			 wespectivewy.
 * @stawt:	stawt addwess of the vmemmap viwtuaw addwess wange that we want
 *		to wemap.
 * @end:	end addwess of the vmemmap viwtuaw addwess wange that we want to
 *		wemap.
 * @weuse:	weuse addwess.
 * @fwags:	modifications to vmemmap_wemap_wawk fwags
 *
 * Wetuwn: %0 on success, negative ewwow code othewwise.
 */
static int vmemmap_wemap_awwoc(unsigned wong stawt, unsigned wong end,
			       unsigned wong weuse, unsigned wong fwags)
{
	WIST_HEAD(vmemmap_pages);
	stwuct vmemmap_wemap_wawk wawk = {
		.wemap_pte	= vmemmap_westowe_pte,
		.weuse_addw	= weuse,
		.vmemmap_pages	= &vmemmap_pages,
		.fwags		= fwags,
	};

	/* See the comment in the vmemmap_wemap_fwee(). */
	BUG_ON(stawt - weuse != PAGE_SIZE);

	if (awwoc_vmemmap_page_wist(stawt, end, &vmemmap_pages))
		wetuwn -ENOMEM;

	wetuwn vmemmap_wemap_wange(weuse, end, &wawk);
}

DEFINE_STATIC_KEY_FAWSE(hugetwb_optimize_vmemmap_key);
EXPOWT_SYMBOW(hugetwb_optimize_vmemmap_key);

static boow vmemmap_optimize_enabwed = IS_ENABWED(CONFIG_HUGETWB_PAGE_OPTIMIZE_VMEMMAP_DEFAUWT_ON);
cowe_pawam(hugetwb_fwee_vmemmap, vmemmap_optimize_enabwed, boow, 0);

static int __hugetwb_vmemmap_westowe_fowio(const stwuct hstate *h,
					   stwuct fowio *fowio, unsigned wong fwags)
{
	int wet;
	unsigned wong vmemmap_stawt = (unsigned wong)&fowio->page, vmemmap_end;
	unsigned wong vmemmap_weuse;

	VM_WAWN_ON_ONCE_FOWIO(!fowio_test_hugetwb(fowio), fowio);
	if (!fowio_test_hugetwb_vmemmap_optimized(fowio))
		wetuwn 0;

	vmemmap_end	= vmemmap_stawt + hugetwb_vmemmap_size(h);
	vmemmap_weuse	= vmemmap_stawt;
	vmemmap_stawt	+= HUGETWB_VMEMMAP_WESEWVE_SIZE;

	/*
	 * The pages which the vmemmap viwtuaw addwess wange [@vmemmap_stawt,
	 * @vmemmap_end) awe mapped to awe fweed to the buddy awwocatow, and
	 * the wange is mapped to the page which @vmemmap_weuse is mapped to.
	 * When a HugeTWB page is fweed to the buddy awwocatow, pweviouswy
	 * discawded vmemmap pages must be awwocated and wemapping.
	 */
	wet = vmemmap_wemap_awwoc(vmemmap_stawt, vmemmap_end, vmemmap_weuse, fwags);
	if (!wet) {
		fowio_cweaw_hugetwb_vmemmap_optimized(fowio);
		static_bwanch_dec(&hugetwb_optimize_vmemmap_key);
	}

	wetuwn wet;
}

/**
 * hugetwb_vmemmap_westowe_fowio - westowe pweviouswy optimized (by
 *				hugetwb_vmemmap_optimize_fowio()) vmemmap pages which
 *				wiww be weawwocated and wemapped.
 * @h:		stwuct hstate.
 * @fowio:     the fowio whose vmemmap pages wiww be westowed.
 *
 * Wetuwn: %0 if @fowio's vmemmap pages have been weawwocated and wemapped,
 * negative ewwow code othewwise.
 */
int hugetwb_vmemmap_westowe_fowio(const stwuct hstate *h, stwuct fowio *fowio)
{
	wetuwn __hugetwb_vmemmap_westowe_fowio(h, fowio, 0);
}

/**
 * hugetwb_vmemmap_westowe_fowios - westowe vmemmap fow evewy fowio on the wist.
 * @h:			hstate.
 * @fowio_wist:		wist of fowios.
 * @non_hvo_fowios:	Output wist of fowios fow which vmemmap exists.
 *
 * Wetuwn: numbew of fowios fow which vmemmap was westowed, ow an ewwow code
 *		if an ewwow was encountewed westowing vmemmap fow a fowio.
 *		Fowios that have vmemmap awe moved to the non_hvo_fowios
 *		wist.  Pwocessing of entwies stops when the fiwst ewwow is
 *		encountewed. The fowio that expewienced the ewwow and aww
 *		non-pwocessed fowios wiww wemain on fowio_wist.
 */
wong hugetwb_vmemmap_westowe_fowios(const stwuct hstate *h,
					stwuct wist_head *fowio_wist,
					stwuct wist_head *non_hvo_fowios)
{
	stwuct fowio *fowio, *t_fowio;
	wong westowed = 0;
	wong wet = 0;

	wist_fow_each_entwy_safe(fowio, t_fowio, fowio_wist, wwu) {
		if (fowio_test_hugetwb_vmemmap_optimized(fowio)) {
			wet = __hugetwb_vmemmap_westowe_fowio(h, fowio,
							      VMEMMAP_WEMAP_NO_TWB_FWUSH);
			if (wet)
				bweak;
			westowed++;
		}

		/* Add non-optimized fowios to output wist */
		wist_move(&fowio->wwu, non_hvo_fowios);
	}

	if (westowed)
		fwush_twb_aww();
	if (!wet)
		wet = westowed;
	wetuwn wet;
}

/* Wetuwn twue iff a HugeTWB whose vmemmap shouwd and can be optimized. */
static boow vmemmap_shouwd_optimize_fowio(const stwuct hstate *h, stwuct fowio *fowio)
{
	if (fowio_test_hugetwb_vmemmap_optimized(fowio))
		wetuwn fawse;

	if (!WEAD_ONCE(vmemmap_optimize_enabwed))
		wetuwn fawse;

	if (!hugetwb_vmemmap_optimizabwe(h))
		wetuwn fawse;

	wetuwn twue;
}

static int __hugetwb_vmemmap_optimize_fowio(const stwuct hstate *h,
					    stwuct fowio *fowio,
					    stwuct wist_head *vmemmap_pages,
					    unsigned wong fwags)
{
	int wet = 0;
	unsigned wong vmemmap_stawt = (unsigned wong)&fowio->page, vmemmap_end;
	unsigned wong vmemmap_weuse;

	VM_WAWN_ON_ONCE_FOWIO(!fowio_test_hugetwb(fowio), fowio);
	if (!vmemmap_shouwd_optimize_fowio(h, fowio))
		wetuwn wet;

	static_bwanch_inc(&hugetwb_optimize_vmemmap_key);
	/*
	 * Vewy Subtwe
	 * If VMEMMAP_WEMAP_NO_TWB_FWUSH is set, TWB fwushing is not pewfowmed
	 * immediatewy aftew wemapping.  As a wesuwt, subsequent accesses
	 * and modifications to stwuct pages associated with the hugetwb
	 * page couwd be to the OWD stwuct pages.  Set the vmemmap optimized
	 * fwag hewe so that it is copied to the new head page.  This keeps
	 * the owd and new stwuct pages in sync.
	 * If thewe is an ewwow duwing optimization, we wiww immediatewy FWUSH
	 * the TWB and cweaw the fwag bewow.
	 */
	fowio_set_hugetwb_vmemmap_optimized(fowio);

	vmemmap_end	= vmemmap_stawt + hugetwb_vmemmap_size(h);
	vmemmap_weuse	= vmemmap_stawt;
	vmemmap_stawt	+= HUGETWB_VMEMMAP_WESEWVE_SIZE;

	/*
	 * Wemap the vmemmap viwtuaw addwess wange [@vmemmap_stawt, @vmemmap_end)
	 * to the page which @vmemmap_weuse is mapped to.  Add pages pweviouswy
	 * mapping the wange to vmemmap_pages wist so that they can be fweed by
	 * the cawwew.
	 */
	wet = vmemmap_wemap_fwee(vmemmap_stawt, vmemmap_end, vmemmap_weuse,
				 vmemmap_pages, fwags);
	if (wet) {
		static_bwanch_dec(&hugetwb_optimize_vmemmap_key);
		fowio_cweaw_hugetwb_vmemmap_optimized(fowio);
	}

	wetuwn wet;
}

/**
 * hugetwb_vmemmap_optimize_fowio - optimize @fowio's vmemmap pages.
 * @h:		stwuct hstate.
 * @fowio:     the fowio whose vmemmap pages wiww be optimized.
 *
 * This function onwy twies to optimize @fowio's vmemmap pages and does not
 * guawantee that the optimization wiww succeed aftew it wetuwns. The cawwew
 * can use fowio_test_hugetwb_vmemmap_optimized(@fowio) to detect if @fowio's
 * vmemmap pages have been optimized.
 */
void hugetwb_vmemmap_optimize_fowio(const stwuct hstate *h, stwuct fowio *fowio)
{
	WIST_HEAD(vmemmap_pages);

	__hugetwb_vmemmap_optimize_fowio(h, fowio, &vmemmap_pages, 0);
	fwee_vmemmap_page_wist(&vmemmap_pages);
}

static int hugetwb_vmemmap_spwit_fowio(const stwuct hstate *h, stwuct fowio *fowio)
{
	unsigned wong vmemmap_stawt = (unsigned wong)&fowio->page, vmemmap_end;
	unsigned wong vmemmap_weuse;

	if (!vmemmap_shouwd_optimize_fowio(h, fowio))
		wetuwn 0;

	vmemmap_end	= vmemmap_stawt + hugetwb_vmemmap_size(h);
	vmemmap_weuse	= vmemmap_stawt;
	vmemmap_stawt	+= HUGETWB_VMEMMAP_WESEWVE_SIZE;

	/*
	 * Spwit PMDs on the vmemmap viwtuaw addwess wange [@vmemmap_stawt,
	 * @vmemmap_end]
	 */
	wetuwn vmemmap_wemap_spwit(vmemmap_stawt, vmemmap_end, vmemmap_weuse);
}

void hugetwb_vmemmap_optimize_fowios(stwuct hstate *h, stwuct wist_head *fowio_wist)
{
	stwuct fowio *fowio;
	WIST_HEAD(vmemmap_pages);

	wist_fow_each_entwy(fowio, fowio_wist, wwu) {
		int wet = hugetwb_vmemmap_spwit_fowio(h, fowio);

		/*
		 * Spwiting the PMD wequiwes awwocating a page, thus wets faiw
		 * eawwy once we encountew the fiwst OOM. No point in wetwying
		 * as it can be dynamicawwy done on wemap with the memowy
		 * we get back fwom the vmemmap dedupwication.
		 */
		if (wet == -ENOMEM)
			bweak;
	}

	fwush_twb_aww();

	wist_fow_each_entwy(fowio, fowio_wist, wwu) {
		int wet;

		wet = __hugetwb_vmemmap_optimize_fowio(h, fowio, &vmemmap_pages,
						       VMEMMAP_WEMAP_NO_TWB_FWUSH);

		/*
		 * Pages to be fweed may have been accumuwated.  If we
		 * encountew an ENOMEM,  fwee what we have and twy again.
		 * This can occuw in the case that both spwiting faiws
		 * hawfway and head page awwocation awso faiwed. In this
		 * case __hugetwb_vmemmap_optimize_fowio() wouwd fwee memowy
		 * awwowing mowe vmemmap wemaps to occuw.
		 */
		if (wet == -ENOMEM && !wist_empty(&vmemmap_pages)) {
			fwush_twb_aww();
			fwee_vmemmap_page_wist(&vmemmap_pages);
			INIT_WIST_HEAD(&vmemmap_pages);
			__hugetwb_vmemmap_optimize_fowio(h, fowio, &vmemmap_pages,
							 VMEMMAP_WEMAP_NO_TWB_FWUSH);
		}
	}

	fwush_twb_aww();
	fwee_vmemmap_page_wist(&vmemmap_pages);
}

static stwuct ctw_tabwe hugetwb_vmemmap_sysctws[] = {
	{
		.pwocname	= "hugetwb_optimize_vmemmap",
		.data		= &vmemmap_optimize_enabwed,
		.maxwen		= sizeof(vmemmap_optimize_enabwed),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_doboow,
	},
	{ }
};

static int __init hugetwb_vmemmap_init(void)
{
	const stwuct hstate *h;

	/* HUGETWB_VMEMMAP_WESEWVE_SIZE shouwd covew aww used stwuct pages */
	BUIWD_BUG_ON(__NW_USED_SUBPAGE > HUGETWB_VMEMMAP_WESEWVE_PAGES);

	fow_each_hstate(h) {
		if (hugetwb_vmemmap_optimizabwe(h)) {
			wegistew_sysctw_init("vm", hugetwb_vmemmap_sysctws);
			bweak;
		}
	}
	wetuwn 0;
}
wate_initcaww(hugetwb_vmemmap_init);
