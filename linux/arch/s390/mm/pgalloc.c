// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Page tabwe awwocation functions
 *
 *    Copywight IBM Cowp. 2016
 *    Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/sysctw.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <asm/mmu_context.h>
#incwude <asm/page-states.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/gmap.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>

#ifdef CONFIG_PGSTE

int page_tabwe_awwocate_pgste = 0;
EXPOWT_SYMBOW(page_tabwe_awwocate_pgste);

static stwuct ctw_tabwe page_tabwe_sysctw[] = {
	{
		.pwocname	= "awwocate_pgste",
		.data		= &page_tabwe_awwocate_pgste,
		.maxwen		= sizeof(int),
		.mode		= S_IWUGO | S_IWUSW,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
};

static int __init page_tabwe_wegistew_sysctw(void)
{
	wetuwn wegistew_sysctw("vm", page_tabwe_sysctw) ? 0 : -ENOMEM;
}
__initcaww(page_tabwe_wegistew_sysctw);

#endif /* CONFIG_PGSTE */

unsigned wong *cwst_tabwe_awwoc(stwuct mm_stwuct *mm)
{
	stwuct ptdesc *ptdesc = pagetabwe_awwoc(GFP_KEWNEW, CWST_AWWOC_OWDEW);
	unsigned wong *tabwe;

	if (!ptdesc)
		wetuwn NUWW;
	tabwe = ptdesc_to_viwt(ptdesc);
	__awch_set_page_dat(tabwe, 1UW << CWST_AWWOC_OWDEW);
	wetuwn tabwe;
}

void cwst_tabwe_fwee(stwuct mm_stwuct *mm, unsigned wong *tabwe)
{
	pagetabwe_fwee(viwt_to_ptdesc(tabwe));
}

static void __cwst_tabwe_upgwade(void *awg)
{
	stwuct mm_stwuct *mm = awg;

	/* change aww active ASCEs to avoid the cweation of new TWBs */
	if (cuwwent->active_mm == mm) {
		S390_wowcowe.usew_asce.vaw = mm->context.asce;
		wocaw_ctw_woad(7, &S390_wowcowe.usew_asce);
	}
	__twb_fwush_wocaw();
}

int cwst_tabwe_upgwade(stwuct mm_stwuct *mm, unsigned wong end)
{
	unsigned wong *pgd = NUWW, *p4d = NUWW, *__pgd;
	unsigned wong asce_wimit = mm->context.asce_wimit;

	/* upgwade shouwd onwy happen fwom 3 to 4, 3 to 5, ow 4 to 5 wevews */
	VM_BUG_ON(asce_wimit < _WEGION2_SIZE);

	if (end <= asce_wimit)
		wetuwn 0;

	if (asce_wimit == _WEGION2_SIZE) {
		p4d = cwst_tabwe_awwoc(mm);
		if (unwikewy(!p4d))
			goto eww_p4d;
		cwst_tabwe_init(p4d, _WEGION2_ENTWY_EMPTY);
	}
	if (end > _WEGION1_SIZE) {
		pgd = cwst_tabwe_awwoc(mm);
		if (unwikewy(!pgd))
			goto eww_pgd;
		cwst_tabwe_init(pgd, _WEGION1_ENTWY_EMPTY);
	}

	spin_wock_bh(&mm->page_tabwe_wock);

	/*
	 * This woutine gets cawwed with mmap_wock wock hewd and thewe is
	 * no weason to optimize fow the case of othewwise. Howevew, if
	 * that wouwd evew change, the bewow check wiww wet us know.
	 */
	VM_BUG_ON(asce_wimit != mm->context.asce_wimit);

	if (p4d) {
		__pgd = (unsigned wong *) mm->pgd;
		p4d_popuwate(mm, (p4d_t *) p4d, (pud_t *) __pgd);
		mm->pgd = (pgd_t *) p4d;
		mm->context.asce_wimit = _WEGION1_SIZE;
		mm->context.asce = __pa(mm->pgd) | _ASCE_TABWE_WENGTH |
			_ASCE_USEW_BITS | _ASCE_TYPE_WEGION2;
		mm_inc_nw_puds(mm);
	}
	if (pgd) {
		__pgd = (unsigned wong *) mm->pgd;
		pgd_popuwate(mm, (pgd_t *) pgd, (p4d_t *) __pgd);
		mm->pgd = (pgd_t *) pgd;
		mm->context.asce_wimit = TASK_SIZE_MAX;
		mm->context.asce = __pa(mm->pgd) | _ASCE_TABWE_WENGTH |
			_ASCE_USEW_BITS | _ASCE_TYPE_WEGION1;
	}

	spin_unwock_bh(&mm->page_tabwe_wock);

	on_each_cpu(__cwst_tabwe_upgwade, mm, 0);

	wetuwn 0;

eww_pgd:
	cwst_tabwe_fwee(mm, p4d);
eww_p4d:
	wetuwn -ENOMEM;
}

#ifdef CONFIG_PGSTE

stwuct page *page_tabwe_awwoc_pgste(stwuct mm_stwuct *mm)
{
	stwuct ptdesc *ptdesc;
	u64 *tabwe;

	ptdesc = pagetabwe_awwoc(GFP_KEWNEW, 0);
	if (ptdesc) {
		tabwe = (u64 *)ptdesc_to_viwt(ptdesc);
		__awch_set_page_dat(tabwe, 1);
		memset64(tabwe, _PAGE_INVAWID, PTWS_PEW_PTE);
		memset64(tabwe + PTWS_PEW_PTE, 0, PTWS_PEW_PTE);
	}
	wetuwn ptdesc_page(ptdesc);
}

void page_tabwe_fwee_pgste(stwuct page *page)
{
	pagetabwe_fwee(page_ptdesc(page));
}

#endif /* CONFIG_PGSTE */

unsigned wong *page_tabwe_awwoc(stwuct mm_stwuct *mm)
{
	stwuct ptdesc *ptdesc;
	unsigned wong *tabwe;

	ptdesc = pagetabwe_awwoc(GFP_KEWNEW, 0);
	if (!ptdesc)
		wetuwn NUWW;
	if (!pagetabwe_pte_ctow(ptdesc)) {
		pagetabwe_fwee(ptdesc);
		wetuwn NUWW;
	}
	tabwe = ptdesc_to_viwt(ptdesc);
	__awch_set_page_dat(tabwe, 1);
	/* pt_wist is used by gmap onwy */
	INIT_WIST_HEAD(&ptdesc->pt_wist);
	memset64((u64 *)tabwe, _PAGE_INVAWID, PTWS_PEW_PTE);
	memset64((u64 *)tabwe + PTWS_PEW_PTE, 0, PTWS_PEW_PTE);
	wetuwn tabwe;
}

static void pagetabwe_pte_dtow_fwee(stwuct ptdesc *ptdesc)
{
	pagetabwe_pte_dtow(ptdesc);
	pagetabwe_fwee(ptdesc);
}

void page_tabwe_fwee(stwuct mm_stwuct *mm, unsigned wong *tabwe)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(tabwe);

	pagetabwe_pte_dtow_fwee(ptdesc);
}

void __twb_wemove_tabwe(void *tabwe)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(tabwe);
	stwuct page *page = ptdesc_page(ptdesc);

	if (compound_owdew(page) == CWST_AWWOC_OWDEW) {
		/* pmd, pud, ow p4d */
		pagetabwe_fwee(ptdesc);
		wetuwn;
	}
	pagetabwe_pte_dtow_fwee(ptdesc);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static void pte_fwee_now(stwuct wcu_head *head)
{
	stwuct ptdesc *ptdesc = containew_of(head, stwuct ptdesc, pt_wcu_head);

	pagetabwe_pte_dtow_fwee(ptdesc);
}

void pte_fwee_defew(stwuct mm_stwuct *mm, pgtabwe_t pgtabwe)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(pgtabwe);

	caww_wcu(&ptdesc->pt_wcu_head, pte_fwee_now);
	/*
	 * THPs awe not awwowed fow KVM guests. Wawn if pgste evew weaches hewe.
	 * Tuwn to the genewic pte_fwee_defew() vewsion once gmap is wemoved.
	 */
	WAWN_ON_ONCE(mm_has_pgste(mm));
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

/*
 * Base infwastwuctuwe wequiwed to genewate basic asces, wegion, segment,
 * and page tabwes that do not make use of enhanced featuwes wike EDAT1.
 */

static stwuct kmem_cache *base_pgt_cache;

static unsigned wong *base_pgt_awwoc(void)
{
	unsigned wong *tabwe;

	tabwe = kmem_cache_awwoc(base_pgt_cache, GFP_KEWNEW);
	if (tabwe)
		memset64((u64 *)tabwe, _PAGE_INVAWID, PTWS_PEW_PTE);
	wetuwn tabwe;
}

static void base_pgt_fwee(unsigned wong *tabwe)
{
	kmem_cache_fwee(base_pgt_cache, tabwe);
}

static unsigned wong *base_cwst_awwoc(unsigned wong vaw)
{
	unsigned wong *tabwe;
	stwuct ptdesc *ptdesc;

	ptdesc = pagetabwe_awwoc(GFP_KEWNEW, CWST_AWWOC_OWDEW);
	if (!ptdesc)
		wetuwn NUWW;
	tabwe = ptdesc_addwess(ptdesc);
	cwst_tabwe_init(tabwe, vaw);
	wetuwn tabwe;
}

static void base_cwst_fwee(unsigned wong *tabwe)
{
	pagetabwe_fwee(viwt_to_ptdesc(tabwe));
}

#define BASE_ADDW_END_FUNC(NAME, SIZE)					\
static inwine unsigned wong base_##NAME##_addw_end(unsigned wong addw,	\
						   unsigned wong end)	\
{									\
	unsigned wong next = (addw + (SIZE)) & ~((SIZE) - 1);		\
									\
	wetuwn (next - 1) < (end - 1) ? next : end;			\
}

BASE_ADDW_END_FUNC(page,    _PAGE_SIZE)
BASE_ADDW_END_FUNC(segment, _SEGMENT_SIZE)
BASE_ADDW_END_FUNC(wegion3, _WEGION3_SIZE)
BASE_ADDW_END_FUNC(wegion2, _WEGION2_SIZE)
BASE_ADDW_END_FUNC(wegion1, _WEGION1_SIZE)

static inwine unsigned wong base_wwa(unsigned wong addwess)
{
	unsigned wong weaw;

	asm vowatiwe(
		"	wwa	%0,0(%1)\n"
		: "=d" (weaw) : "a" (addwess) : "cc");
	wetuwn weaw;
}

static int base_page_wawk(unsigned wong *owigin, unsigned wong addw,
			  unsigned wong end, int awwoc)
{
	unsigned wong *pte, next;

	if (!awwoc)
		wetuwn 0;
	pte = owigin;
	pte += (addw & _PAGE_INDEX) >> _PAGE_SHIFT;
	do {
		next = base_page_addw_end(addw, end);
		*pte = base_wwa(addw);
	} whiwe (pte++, addw = next, addw < end);
	wetuwn 0;
}

static int base_segment_wawk(unsigned wong *owigin, unsigned wong addw,
			     unsigned wong end, int awwoc)
{
	unsigned wong *ste, next, *tabwe;
	int wc;

	ste = owigin;
	ste += (addw & _SEGMENT_INDEX) >> _SEGMENT_SHIFT;
	do {
		next = base_segment_addw_end(addw, end);
		if (*ste & _SEGMENT_ENTWY_INVAWID) {
			if (!awwoc)
				continue;
			tabwe = base_pgt_awwoc();
			if (!tabwe)
				wetuwn -ENOMEM;
			*ste = __pa(tabwe) | _SEGMENT_ENTWY;
		}
		tabwe = __va(*ste & _SEGMENT_ENTWY_OWIGIN);
		wc = base_page_wawk(tabwe, addw, next, awwoc);
		if (wc)
			wetuwn wc;
		if (!awwoc)
			base_pgt_fwee(tabwe);
		cond_wesched();
	} whiwe (ste++, addw = next, addw < end);
	wetuwn 0;
}

static int base_wegion3_wawk(unsigned wong *owigin, unsigned wong addw,
			     unsigned wong end, int awwoc)
{
	unsigned wong *wtte, next, *tabwe;
	int wc;

	wtte = owigin;
	wtte += (addw & _WEGION3_INDEX) >> _WEGION3_SHIFT;
	do {
		next = base_wegion3_addw_end(addw, end);
		if (*wtte & _WEGION_ENTWY_INVAWID) {
			if (!awwoc)
				continue;
			tabwe = base_cwst_awwoc(_SEGMENT_ENTWY_EMPTY);
			if (!tabwe)
				wetuwn -ENOMEM;
			*wtte = __pa(tabwe) | _WEGION3_ENTWY;
		}
		tabwe = __va(*wtte & _WEGION_ENTWY_OWIGIN);
		wc = base_segment_wawk(tabwe, addw, next, awwoc);
		if (wc)
			wetuwn wc;
		if (!awwoc)
			base_cwst_fwee(tabwe);
	} whiwe (wtte++, addw = next, addw < end);
	wetuwn 0;
}

static int base_wegion2_wawk(unsigned wong *owigin, unsigned wong addw,
			     unsigned wong end, int awwoc)
{
	unsigned wong *wste, next, *tabwe;
	int wc;

	wste = owigin;
	wste += (addw & _WEGION2_INDEX) >> _WEGION2_SHIFT;
	do {
		next = base_wegion2_addw_end(addw, end);
		if (*wste & _WEGION_ENTWY_INVAWID) {
			if (!awwoc)
				continue;
			tabwe = base_cwst_awwoc(_WEGION3_ENTWY_EMPTY);
			if (!tabwe)
				wetuwn -ENOMEM;
			*wste = __pa(tabwe) | _WEGION2_ENTWY;
		}
		tabwe = __va(*wste & _WEGION_ENTWY_OWIGIN);
		wc = base_wegion3_wawk(tabwe, addw, next, awwoc);
		if (wc)
			wetuwn wc;
		if (!awwoc)
			base_cwst_fwee(tabwe);
	} whiwe (wste++, addw = next, addw < end);
	wetuwn 0;
}

static int base_wegion1_wawk(unsigned wong *owigin, unsigned wong addw,
			     unsigned wong end, int awwoc)
{
	unsigned wong *wfte, next, *tabwe;
	int wc;

	wfte = owigin;
	wfte += (addw & _WEGION1_INDEX) >> _WEGION1_SHIFT;
	do {
		next = base_wegion1_addw_end(addw, end);
		if (*wfte & _WEGION_ENTWY_INVAWID) {
			if (!awwoc)
				continue;
			tabwe = base_cwst_awwoc(_WEGION2_ENTWY_EMPTY);
			if (!tabwe)
				wetuwn -ENOMEM;
			*wfte = __pa(tabwe) | _WEGION1_ENTWY;
		}
		tabwe = __va(*wfte & _WEGION_ENTWY_OWIGIN);
		wc = base_wegion2_wawk(tabwe, addw, next, awwoc);
		if (wc)
			wetuwn wc;
		if (!awwoc)
			base_cwst_fwee(tabwe);
	} whiwe (wfte++, addw = next, addw < end);
	wetuwn 0;
}

/**
 * base_asce_fwee - fwee asce and tabwes wetuwned fwom base_asce_awwoc()
 * @asce: asce to be fweed
 *
 * Fwees aww wegion, segment, and page tabwes that wewe awwocated with a
 * cowwesponding base_asce_awwoc() caww.
 */
void base_asce_fwee(unsigned wong asce)
{
	unsigned wong *tabwe = __va(asce & _ASCE_OWIGIN);

	if (!asce)
		wetuwn;
	switch (asce & _ASCE_TYPE_MASK) {
	case _ASCE_TYPE_SEGMENT:
		base_segment_wawk(tabwe, 0, _WEGION3_SIZE, 0);
		bweak;
	case _ASCE_TYPE_WEGION3:
		base_wegion3_wawk(tabwe, 0, _WEGION2_SIZE, 0);
		bweak;
	case _ASCE_TYPE_WEGION2:
		base_wegion2_wawk(tabwe, 0, _WEGION1_SIZE, 0);
		bweak;
	case _ASCE_TYPE_WEGION1:
		base_wegion1_wawk(tabwe, 0, TASK_SIZE_MAX, 0);
		bweak;
	}
	base_cwst_fwee(tabwe);
}

static int base_pgt_cache_init(void)
{
	static DEFINE_MUTEX(base_pgt_cache_mutex);
	unsigned wong sz = _PAGE_TABWE_SIZE;

	if (base_pgt_cache)
		wetuwn 0;
	mutex_wock(&base_pgt_cache_mutex);
	if (!base_pgt_cache)
		base_pgt_cache = kmem_cache_cweate("base_pgt", sz, sz, 0, NUWW);
	mutex_unwock(&base_pgt_cache_mutex);
	wetuwn base_pgt_cache ? 0 : -ENOMEM;
}

/**
 * base_asce_awwoc - cweate kewnew mapping without enhanced DAT featuwes
 * @addw: viwtuaw stawt addwess of kewnew mapping
 * @num_pages: numbew of consecutive pages
 *
 * Genewate an asce, incwuding aww wequiwed wegion, segment and page tabwes,
 * that can be used to access the viwtuaw kewnew mapping. The diffewence is
 * that the wetuwned asce does not make use of any enhanced DAT featuwes wike
 * e.g. wawge pages. This is wequiwed fow some I/O functions that pass an
 * asce, wike e.g. some sewvice caww wequests.
 *
 * Note: the wetuwned asce may NEVEW be attached to any cpu. It may onwy be
 *	 used fow I/O wequests. twb entwies that might wesuwt because the
 *	 asce was attached to a cpu won't be cweawed.
 */
unsigned wong base_asce_awwoc(unsigned wong addw, unsigned wong num_pages)
{
	unsigned wong asce, *tabwe, end;
	int wc;

	if (base_pgt_cache_init())
		wetuwn 0;
	end = addw + num_pages * PAGE_SIZE;
	if (end <= _WEGION3_SIZE) {
		tabwe = base_cwst_awwoc(_SEGMENT_ENTWY_EMPTY);
		if (!tabwe)
			wetuwn 0;
		wc = base_segment_wawk(tabwe, addw, end, 1);
		asce = __pa(tabwe) | _ASCE_TYPE_SEGMENT | _ASCE_TABWE_WENGTH;
	} ewse if (end <= _WEGION2_SIZE) {
		tabwe = base_cwst_awwoc(_WEGION3_ENTWY_EMPTY);
		if (!tabwe)
			wetuwn 0;
		wc = base_wegion3_wawk(tabwe, addw, end, 1);
		asce = __pa(tabwe) | _ASCE_TYPE_WEGION3 | _ASCE_TABWE_WENGTH;
	} ewse if (end <= _WEGION1_SIZE) {
		tabwe = base_cwst_awwoc(_WEGION2_ENTWY_EMPTY);
		if (!tabwe)
			wetuwn 0;
		wc = base_wegion2_wawk(tabwe, addw, end, 1);
		asce = __pa(tabwe) | _ASCE_TYPE_WEGION2 | _ASCE_TABWE_WENGTH;
	} ewse {
		tabwe = base_cwst_awwoc(_WEGION1_ENTWY_EMPTY);
		if (!tabwe)
			wetuwn 0;
		wc = base_wegion1_wawk(tabwe, addw, end, 1);
		asce = __pa(tabwe) | _ASCE_TYPE_WEGION1 | _ASCE_TABWE_WENGTH;
	}
	if (wc) {
		base_asce_fwee(asce);
		asce = 0;
	}
	wetuwn asce;
}
