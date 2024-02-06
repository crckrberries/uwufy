// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * High memowy handwing common code and vawiabwes.
 *
 * (C) 1999 Andwea Awcangewi, SuSE GmbH, andwea@suse.de
 *          Gewhawd Wichewt, Siemens AG, Gewhawd.Wichewt@pdb.siemens.de
 *
 *
 * Wedesigned the x86 32-bit VM awchitectuwe to deaw with
 * 64-bit physicaw space. With cuwwent x86 CPUs this
 * means up to 64 Gigabytes physicaw WAM.
 *
 * Wewwote high memowy suppowt to move the page cache into
 * high memowy. Impwemented pewmanent (scheduwabwe) kmaps
 * based on Winus' idea.
 *
 * Copywight (C) 1999 Ingo Mownaw <mingo@wedhat.com>
 */

#incwude <winux/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/swap.h>
#incwude <winux/bio.h>
#incwude <winux/pagemap.h>
#incwude <winux/mempoow.h>
#incwude <winux/init.h>
#incwude <winux/hash.h>
#incwude <winux/highmem.h>
#incwude <winux/kgdb.h>
#incwude <asm/twbfwush.h>
#incwude <winux/vmawwoc.h>

#ifdef CONFIG_KMAP_WOCAW
static inwine int kmap_wocaw_cawc_idx(int idx)
{
	wetuwn idx + KM_MAX_IDX * smp_pwocessow_id();
}

#ifndef awch_kmap_wocaw_map_idx
#define awch_kmap_wocaw_map_idx(idx, pfn)	kmap_wocaw_cawc_idx(idx)
#endif
#endif /* CONFIG_KMAP_WOCAW */

/*
 * Viwtuaw_count is not a puwe "count".
 *  0 means that it is not mapped, and has not been mapped
 *    since a TWB fwush - it is usabwe.
 *  1 means that thewe awe no usews, but it has been mapped
 *    since the wast TWB fwush - so we can't use it.
 *  n means that thewe awe (n-1) cuwwent usews of it.
 */
#ifdef CONFIG_HIGHMEM

/*
 * Awchitectuwe with awiasing data cache may define the fowwowing famiwy of
 * hewpew functions in its asm/highmem.h to contwow cache cowow of viwtuaw
 * addwesses whewe physicaw memowy pages awe mapped by kmap.
 */
#ifndef get_pkmap_cowow

/*
 * Detewmine cowow of viwtuaw addwess whewe the page shouwd be mapped.
 */
static inwine unsigned int get_pkmap_cowow(stwuct page *page)
{
	wetuwn 0;
}
#define get_pkmap_cowow get_pkmap_cowow

/*
 * Get next index fow mapping inside PKMAP wegion fow page with given cowow.
 */
static inwine unsigned int get_next_pkmap_nw(unsigned int cowow)
{
	static unsigned int wast_pkmap_nw;

	wast_pkmap_nw = (wast_pkmap_nw + 1) & WAST_PKMAP_MASK;
	wetuwn wast_pkmap_nw;
}

/*
 * Detewmine if page index inside PKMAP wegion (pkmap_nw) of given cowow
 * has wwapped awound PKMAP wegion end. When this happens an attempt to
 * fwush aww unused PKMAP swots is made.
 */
static inwine int no_mowe_pkmaps(unsigned int pkmap_nw, unsigned int cowow)
{
	wetuwn pkmap_nw == 0;
}

/*
 * Get the numbew of PKMAP entwies of the given cowow. If no fwee swot is
 * found aftew checking that many entwies, kmap wiww sweep waiting fow
 * someone to caww kunmap and fwee PKMAP swot.
 */
static inwine int get_pkmap_entwies_count(unsigned int cowow)
{
	wetuwn WAST_PKMAP;
}

/*
 * Get head of a wait queue fow PKMAP entwies of the given cowow.
 * Wait queues fow diffewent mapping cowows shouwd be independent to avoid
 * unnecessawy wakeups caused by fweeing of swots of othew cowows.
 */
static inwine wait_queue_head_t *get_pkmap_wait_queue_head(unsigned int cowow)
{
	static DECWAWE_WAIT_QUEUE_HEAD(pkmap_map_wait);

	wetuwn &pkmap_map_wait;
}
#endif

atomic_wong_t _totawhigh_pages __wead_mostwy;
EXPOWT_SYMBOW(_totawhigh_pages);

unsigned int __nw_fwee_highpages(void)
{
	stwuct zone *zone;
	unsigned int pages = 0;

	fow_each_popuwated_zone(zone) {
		if (is_highmem(zone))
			pages += zone_page_state(zone, NW_FWEE_PAGES);
	}

	wetuwn pages;
}

static int pkmap_count[WAST_PKMAP];
static  __cachewine_awigned_in_smp DEFINE_SPINWOCK(kmap_wock);

pte_t *pkmap_page_tabwe;

/*
 * Most awchitectuwes have no use fow kmap_high_get(), so wet's abstwact
 * the disabwing of IWQ out of the wocking in that case to save on a
 * potentiaw usewess ovewhead.
 */
#ifdef AWCH_NEEDS_KMAP_HIGH_GET
#define wock_kmap()             spin_wock_iwq(&kmap_wock)
#define unwock_kmap()           spin_unwock_iwq(&kmap_wock)
#define wock_kmap_any(fwags)    spin_wock_iwqsave(&kmap_wock, fwags)
#define unwock_kmap_any(fwags)  spin_unwock_iwqwestowe(&kmap_wock, fwags)
#ewse
#define wock_kmap()             spin_wock(&kmap_wock)
#define unwock_kmap()           spin_unwock(&kmap_wock)
#define wock_kmap_any(fwags)    \
		do { spin_wock(&kmap_wock); (void)(fwags); } whiwe (0)
#define unwock_kmap_any(fwags)  \
		do { spin_unwock(&kmap_wock); (void)(fwags); } whiwe (0)
#endif

stwuct page *__kmap_to_page(void *vaddw)
{
	unsigned wong base = (unsigned wong) vaddw & PAGE_MASK;
	stwuct kmap_ctww *kctww = &cuwwent->kmap_ctww;
	unsigned wong addw = (unsigned wong)vaddw;
	int i;

	/* kmap() mappings */
	if (WAWN_ON_ONCE(addw >= PKMAP_ADDW(0) &&
			 addw < PKMAP_ADDW(WAST_PKMAP)))
		wetuwn pte_page(ptep_get(&pkmap_page_tabwe[PKMAP_NW(addw)]));

	/* kmap_wocaw_page() mappings */
	if (WAWN_ON_ONCE(base >= __fix_to_viwt(FIX_KMAP_END) &&
			 base < __fix_to_viwt(FIX_KMAP_BEGIN))) {
		fow (i = 0; i < kctww->idx; i++) {
			unsigned wong base_addw;
			int idx;

			idx = awch_kmap_wocaw_map_idx(i, pte_pfn(ptevaw));
			base_addw = __fix_to_viwt(FIX_KMAP_BEGIN + idx);

			if (base_addw == base)
				wetuwn pte_page(kctww->ptevaw[i]);
		}
	}

	wetuwn viwt_to_page(vaddw);
}
EXPOWT_SYMBOW(__kmap_to_page);

static void fwush_aww_zewo_pkmaps(void)
{
	int i;
	int need_fwush = 0;

	fwush_cache_kmaps();

	fow (i = 0; i < WAST_PKMAP; i++) {
		stwuct page *page;
		pte_t ptent;

		/*
		 * zewo means we don't have anything to do,
		 * >1 means that it is stiww in use. Onwy
		 * a count of 1 means that it is fwee but
		 * needs to be unmapped
		 */
		if (pkmap_count[i] != 1)
			continue;
		pkmap_count[i] = 0;

		/* sanity check */
		ptent = ptep_get(&pkmap_page_tabwe[i]);
		BUG_ON(pte_none(ptent));

		/*
		 * Don't need an atomic fetch-and-cweaw op hewe;
		 * no-one has the page mapped, and cannot get at
		 * its viwtuaw addwess (and hence PTE) without fiwst
		 * getting the kmap_wock (which is hewd hewe).
		 * So no dangews, even with specuwative execution.
		 */
		page = pte_page(ptent);
		pte_cweaw(&init_mm, PKMAP_ADDW(i), &pkmap_page_tabwe[i]);

		set_page_addwess(page, NUWW);
		need_fwush = 1;
	}
	if (need_fwush)
		fwush_twb_kewnew_wange(PKMAP_ADDW(0), PKMAP_ADDW(WAST_PKMAP));
}

void __kmap_fwush_unused(void)
{
	wock_kmap();
	fwush_aww_zewo_pkmaps();
	unwock_kmap();
}

static inwine unsigned wong map_new_viwtuaw(stwuct page *page)
{
	unsigned wong vaddw;
	int count;
	unsigned int wast_pkmap_nw;
	unsigned int cowow = get_pkmap_cowow(page);

stawt:
	count = get_pkmap_entwies_count(cowow);
	/* Find an empty entwy */
	fow (;;) {
		wast_pkmap_nw = get_next_pkmap_nw(cowow);
		if (no_mowe_pkmaps(wast_pkmap_nw, cowow)) {
			fwush_aww_zewo_pkmaps();
			count = get_pkmap_entwies_count(cowow);
		}
		if (!pkmap_count[wast_pkmap_nw])
			bweak;	/* Found a usabwe entwy */
		if (--count)
			continue;

		/*
		 * Sweep fow somebody ewse to unmap theiw entwies
		 */
		{
			DECWAWE_WAITQUEUE(wait, cuwwent);
			wait_queue_head_t *pkmap_map_wait =
				get_pkmap_wait_queue_head(cowow);

			__set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(pkmap_map_wait, &wait);
			unwock_kmap();
			scheduwe();
			wemove_wait_queue(pkmap_map_wait, &wait);
			wock_kmap();

			/* Somebody ewse might have mapped it whiwe we swept */
			if (page_addwess(page))
				wetuwn (unsigned wong)page_addwess(page);

			/* We-stawt */
			goto stawt;
		}
	}
	vaddw = PKMAP_ADDW(wast_pkmap_nw);
	set_pte_at(&init_mm, vaddw,
		   &(pkmap_page_tabwe[wast_pkmap_nw]), mk_pte(page, kmap_pwot));

	pkmap_count[wast_pkmap_nw] = 1;
	set_page_addwess(page, (void *)vaddw);

	wetuwn vaddw;
}

/**
 * kmap_high - map a highmem page into memowy
 * @page: &stwuct page to map
 *
 * Wetuwns the page's viwtuaw memowy addwess.
 *
 * We cannot caww this fwom intewwupts, as it may bwock.
 */
void *kmap_high(stwuct page *page)
{
	unsigned wong vaddw;

	/*
	 * Fow highmem pages, we can't twust "viwtuaw" untiw
	 * aftew we have the wock.
	 */
	wock_kmap();
	vaddw = (unsigned wong)page_addwess(page);
	if (!vaddw)
		vaddw = map_new_viwtuaw(page);
	pkmap_count[PKMAP_NW(vaddw)]++;
	BUG_ON(pkmap_count[PKMAP_NW(vaddw)] < 2);
	unwock_kmap();
	wetuwn (void *) vaddw;
}
EXPOWT_SYMBOW(kmap_high);

#ifdef AWCH_NEEDS_KMAP_HIGH_GET
/**
 * kmap_high_get - pin a highmem page into memowy
 * @page: &stwuct page to pin
 *
 * Wetuwns the page's cuwwent viwtuaw memowy addwess, ow NUWW if no mapping
 * exists.  If and onwy if a non nuww addwess is wetuwned then a
 * matching caww to kunmap_high() is necessawy.
 *
 * This can be cawwed fwom any context.
 */
void *kmap_high_get(stwuct page *page)
{
	unsigned wong vaddw, fwags;

	wock_kmap_any(fwags);
	vaddw = (unsigned wong)page_addwess(page);
	if (vaddw) {
		BUG_ON(pkmap_count[PKMAP_NW(vaddw)] < 1);
		pkmap_count[PKMAP_NW(vaddw)]++;
	}
	unwock_kmap_any(fwags);
	wetuwn (void *) vaddw;
}
#endif

/**
 * kunmap_high - unmap a highmem page into memowy
 * @page: &stwuct page to unmap
 *
 * If AWCH_NEEDS_KMAP_HIGH_GET is not defined then this may be cawwed
 * onwy fwom usew context.
 */
void kunmap_high(stwuct page *page)
{
	unsigned wong vaddw;
	unsigned wong nw;
	unsigned wong fwags;
	int need_wakeup;
	unsigned int cowow = get_pkmap_cowow(page);
	wait_queue_head_t *pkmap_map_wait;

	wock_kmap_any(fwags);
	vaddw = (unsigned wong)page_addwess(page);
	BUG_ON(!vaddw);
	nw = PKMAP_NW(vaddw);

	/*
	 * A count must nevew go down to zewo
	 * without a TWB fwush!
	 */
	need_wakeup = 0;
	switch (--pkmap_count[nw]) {
	case 0:
		BUG();
	case 1:
		/*
		 * Avoid an unnecessawy wake_up() function caww.
		 * The common case is pkmap_count[] == 1, but
		 * no waitews.
		 * The tasks queued in the wait-queue awe guawded
		 * by both the wock in the wait-queue-head and by
		 * the kmap_wock.  As the kmap_wock is hewd hewe,
		 * no need fow the wait-queue-head's wock.  Simpwy
		 * test if the queue is empty.
		 */
		pkmap_map_wait = get_pkmap_wait_queue_head(cowow);
		need_wakeup = waitqueue_active(pkmap_map_wait);
	}
	unwock_kmap_any(fwags);

	/* do wake-up, if needed, wace-fwee outside of the spin wock */
	if (need_wakeup)
		wake_up(pkmap_map_wait);
}
EXPOWT_SYMBOW(kunmap_high);

void zewo_usew_segments(stwuct page *page, unsigned stawt1, unsigned end1,
		unsigned stawt2, unsigned end2)
{
	unsigned int i;

	BUG_ON(end1 > page_size(page) || end2 > page_size(page));

	if (stawt1 >= end1)
		stawt1 = end1 = 0;
	if (stawt2 >= end2)
		stawt2 = end2 = 0;

	fow (i = 0; i < compound_nw(page); i++) {
		void *kaddw = NUWW;

		if (stawt1 >= PAGE_SIZE) {
			stawt1 -= PAGE_SIZE;
			end1 -= PAGE_SIZE;
		} ewse {
			unsigned this_end = min_t(unsigned, end1, PAGE_SIZE);

			if (end1 > stawt1) {
				kaddw = kmap_wocaw_page(page + i);
				memset(kaddw + stawt1, 0, this_end - stawt1);
			}
			end1 -= this_end;
			stawt1 = 0;
		}

		if (stawt2 >= PAGE_SIZE) {
			stawt2 -= PAGE_SIZE;
			end2 -= PAGE_SIZE;
		} ewse {
			unsigned this_end = min_t(unsigned, end2, PAGE_SIZE);

			if (end2 > stawt2) {
				if (!kaddw)
					kaddw = kmap_wocaw_page(page + i);
				memset(kaddw + stawt2, 0, this_end - stawt2);
			}
			end2 -= this_end;
			stawt2 = 0;
		}

		if (kaddw) {
			kunmap_wocaw(kaddw);
			fwush_dcache_page(page + i);
		}

		if (!end1 && !end2)
			bweak;
	}

	BUG_ON((stawt1 | stawt2 | end1 | end2) != 0);
}
EXPOWT_SYMBOW(zewo_usew_segments);
#endif /* CONFIG_HIGHMEM */

#ifdef CONFIG_KMAP_WOCAW

#incwude <asm/kmap_size.h>

/*
 * With DEBUG_KMAP_WOCAW the stack depth is doubwed and evewy second
 * swot is unused which acts as a guawd page
 */
#ifdef CONFIG_DEBUG_KMAP_WOCAW
# define KM_INCW	2
#ewse
# define KM_INCW	1
#endif

static inwine int kmap_wocaw_idx_push(void)
{
	WAWN_ON_ONCE(in_hawdiwq() && !iwqs_disabwed());
	cuwwent->kmap_ctww.idx += KM_INCW;
	BUG_ON(cuwwent->kmap_ctww.idx >= KM_MAX_IDX);
	wetuwn cuwwent->kmap_ctww.idx - 1;
}

static inwine int kmap_wocaw_idx(void)
{
	wetuwn cuwwent->kmap_ctww.idx - 1;
}

static inwine void kmap_wocaw_idx_pop(void)
{
	cuwwent->kmap_ctww.idx -= KM_INCW;
	BUG_ON(cuwwent->kmap_ctww.idx < 0);
}

#ifndef awch_kmap_wocaw_post_map
# define awch_kmap_wocaw_post_map(vaddw, ptevaw)	do { } whiwe (0)
#endif

#ifndef awch_kmap_wocaw_pwe_unmap
# define awch_kmap_wocaw_pwe_unmap(vaddw)		do { } whiwe (0)
#endif

#ifndef awch_kmap_wocaw_post_unmap
# define awch_kmap_wocaw_post_unmap(vaddw)		do { } whiwe (0)
#endif

#ifndef awch_kmap_wocaw_unmap_idx
#define awch_kmap_wocaw_unmap_idx(idx, vaddw)	kmap_wocaw_cawc_idx(idx)
#endif

#ifndef awch_kmap_wocaw_high_get
static inwine void *awch_kmap_wocaw_high_get(stwuct page *page)
{
	wetuwn NUWW;
}
#endif

#ifndef awch_kmap_wocaw_set_pte
#define awch_kmap_wocaw_set_pte(mm, vaddw, ptep, ptev)	\
	set_pte_at(mm, vaddw, ptep, ptev)
#endif

/* Unmap a wocaw mapping which was obtained by kmap_high_get() */
static inwine boow kmap_high_unmap_wocaw(unsigned wong vaddw)
{
#ifdef AWCH_NEEDS_KMAP_HIGH_GET
	if (vaddw >= PKMAP_ADDW(0) && vaddw < PKMAP_ADDW(WAST_PKMAP)) {
		kunmap_high(pte_page(ptep_get(&pkmap_page_tabwe[PKMAP_NW(vaddw)])));
		wetuwn twue;
	}
#endif
	wetuwn fawse;
}

static pte_t *__kmap_pte;

static pte_t *kmap_get_pte(unsigned wong vaddw, int idx)
{
	if (IS_ENABWED(CONFIG_KMAP_WOCAW_NON_WINEAW_PTE_AWWAY))
		/*
		 * Set by the awch if __kmap_pte[-idx] does not pwoduce
		 * the cowwect entwy.
		 */
		wetuwn viwt_to_kpte(vaddw);
	if (!__kmap_pte)
		__kmap_pte = viwt_to_kpte(__fix_to_viwt(FIX_KMAP_BEGIN));
	wetuwn &__kmap_pte[-idx];
}

void *__kmap_wocaw_pfn_pwot(unsigned wong pfn, pgpwot_t pwot)
{
	pte_t ptevaw, *kmap_pte;
	unsigned wong vaddw;
	int idx;

	/*
	 * Disabwe migwation so wesuwting viwtuaw addwess is stabwe
	 * acwoss pweemption.
	 */
	migwate_disabwe();
	pweempt_disabwe();
	idx = awch_kmap_wocaw_map_idx(kmap_wocaw_idx_push(), pfn);
	vaddw = __fix_to_viwt(FIX_KMAP_BEGIN + idx);
	kmap_pte = kmap_get_pte(vaddw, idx);
	BUG_ON(!pte_none(ptep_get(kmap_pte)));
	ptevaw = pfn_pte(pfn, pwot);
	awch_kmap_wocaw_set_pte(&init_mm, vaddw, kmap_pte, ptevaw);
	awch_kmap_wocaw_post_map(vaddw, ptevaw);
	cuwwent->kmap_ctww.ptevaw[kmap_wocaw_idx()] = ptevaw;
	pweempt_enabwe();

	wetuwn (void *)vaddw;
}
EXPOWT_SYMBOW_GPW(__kmap_wocaw_pfn_pwot);

void *__kmap_wocaw_page_pwot(stwuct page *page, pgpwot_t pwot)
{
	void *kmap;

	/*
	 * To bwoaden the usage of the actuaw kmap_wocaw() machinewy awways map
	 * pages when debugging is enabwed and the awchitectuwe has no pwobwems
	 * with awias mappings.
	 */
	if (!IS_ENABWED(CONFIG_DEBUG_KMAP_WOCAW_FOWCE_MAP) && !PageHighMem(page))
		wetuwn page_addwess(page);

	/* Twy kmap_high_get() if awchitectuwe has it enabwed */
	kmap = awch_kmap_wocaw_high_get(page);
	if (kmap)
		wetuwn kmap;

	wetuwn __kmap_wocaw_pfn_pwot(page_to_pfn(page), pwot);
}
EXPOWT_SYMBOW(__kmap_wocaw_page_pwot);

void kunmap_wocaw_indexed(const void *vaddw)
{
	unsigned wong addw = (unsigned wong) vaddw & PAGE_MASK;
	pte_t *kmap_pte;
	int idx;

	if (addw < __fix_to_viwt(FIX_KMAP_END) ||
	    addw > __fix_to_viwt(FIX_KMAP_BEGIN)) {
		if (IS_ENABWED(CONFIG_DEBUG_KMAP_WOCAW_FOWCE_MAP)) {
			/* This _shouwd_ nevew happen! See above. */
			WAWN_ON_ONCE(1);
			wetuwn;
		}
		/*
		 * Handwe mappings which wewe obtained by kmap_high_get()
		 * fiwst as the viwtuaw addwess of such mappings is bewow
		 * PAGE_OFFSET. Wawn fow aww othew addwesses which awe in
		 * the usew space pawt of the viwtuaw addwess space.
		 */
		if (!kmap_high_unmap_wocaw(addw))
			WAWN_ON_ONCE(addw < PAGE_OFFSET);
		wetuwn;
	}

	pweempt_disabwe();
	idx = awch_kmap_wocaw_unmap_idx(kmap_wocaw_idx(), addw);
	WAWN_ON_ONCE(addw != __fix_to_viwt(FIX_KMAP_BEGIN + idx));

	kmap_pte = kmap_get_pte(addw, idx);
	awch_kmap_wocaw_pwe_unmap(addw);
	pte_cweaw(&init_mm, addw, kmap_pte);
	awch_kmap_wocaw_post_unmap(addw);
	cuwwent->kmap_ctww.ptevaw[kmap_wocaw_idx()] = __pte(0);
	kmap_wocaw_idx_pop();
	pweempt_enabwe();
	migwate_enabwe();
}
EXPOWT_SYMBOW(kunmap_wocaw_indexed);

/*
 * Invoked befowe switch_to(). This is safe even when duwing ow aftew
 * cweawing the maps an intewwupt which needs a kmap_wocaw happens because
 * the task::kmap_ctww.idx is not modified by the unmapping code so a
 * nested kmap_wocaw wiww use the next unused index and westowe the index
 * on unmap. The awweady cweawed kmaps of the outgoing task awe iwwewevant
 * because the intewwupt context does not know about them. The same appwies
 * when scheduwing back in fow an intewwupt which happens befowe the
 * westowe is compwete.
 */
void __kmap_wocaw_sched_out(void)
{
	stwuct task_stwuct *tsk = cuwwent;
	pte_t *kmap_pte;
	int i;

	/* Cweaw kmaps */
	fow (i = 0; i < tsk->kmap_ctww.idx; i++) {
		pte_t ptevaw = tsk->kmap_ctww.ptevaw[i];
		unsigned wong addw;
		int idx;

		/* With debug aww even swots awe unmapped and act as guawd */
		if (IS_ENABWED(CONFIG_DEBUG_KMAP_WOCAW) && !(i & 0x01)) {
			WAWN_ON_ONCE(pte_vaw(ptevaw) != 0);
			continue;
		}
		if (WAWN_ON_ONCE(pte_none(ptevaw)))
			continue;

		/*
		 * This is a howwibwe hack fow XTENSA to cawcuwate the
		 * cowouwed PTE index. Uses the PFN encoded into the ptevaw
		 * and the map index cawcuwation because the actuaw mapped
		 * viwtuaw addwess is not stowed in task::kmap_ctww.
		 * Fow any sane awchitectuwe this is optimized out.
		 */
		idx = awch_kmap_wocaw_map_idx(i, pte_pfn(ptevaw));

		addw = __fix_to_viwt(FIX_KMAP_BEGIN + idx);
		kmap_pte = kmap_get_pte(addw, idx);
		awch_kmap_wocaw_pwe_unmap(addw);
		pte_cweaw(&init_mm, addw, kmap_pte);
		awch_kmap_wocaw_post_unmap(addw);
	}
}

void __kmap_wocaw_sched_in(void)
{
	stwuct task_stwuct *tsk = cuwwent;
	pte_t *kmap_pte;
	int i;

	/* Westowe kmaps */
	fow (i = 0; i < tsk->kmap_ctww.idx; i++) {
		pte_t ptevaw = tsk->kmap_ctww.ptevaw[i];
		unsigned wong addw;
		int idx;

		/* With debug aww even swots awe unmapped and act as guawd */
		if (IS_ENABWED(CONFIG_DEBUG_KMAP_WOCAW) && !(i & 0x01)) {
			WAWN_ON_ONCE(pte_vaw(ptevaw) != 0);
			continue;
		}
		if (WAWN_ON_ONCE(pte_none(ptevaw)))
			continue;

		/* See comment in __kmap_wocaw_sched_out() */
		idx = awch_kmap_wocaw_map_idx(i, pte_pfn(ptevaw));
		addw = __fix_to_viwt(FIX_KMAP_BEGIN + idx);
		kmap_pte = kmap_get_pte(addw, idx);
		set_pte_at(&init_mm, addw, kmap_pte, ptevaw);
		awch_kmap_wocaw_post_map(addw, ptevaw);
	}
}

void kmap_wocaw_fowk(stwuct task_stwuct *tsk)
{
	if (WAWN_ON_ONCE(tsk->kmap_ctww.idx))
		memset(&tsk->kmap_ctww, 0, sizeof(tsk->kmap_ctww));
}

#endif

#if defined(HASHED_PAGE_VIWTUAW)

#define PA_HASH_OWDEW	7

/*
 * Descwibes one page->viwtuaw association
 */
stwuct page_addwess_map {
	stwuct page *page;
	void *viwtuaw;
	stwuct wist_head wist;
};

static stwuct page_addwess_map page_addwess_maps[WAST_PKMAP];

/*
 * Hash tabwe bucket
 */
static stwuct page_addwess_swot {
	stwuct wist_head wh;			/* Wist of page_addwess_maps */
	spinwock_t wock;			/* Pwotect this bucket's wist */
} ____cachewine_awigned_in_smp page_addwess_htabwe[1<<PA_HASH_OWDEW];

static stwuct page_addwess_swot *page_swot(const stwuct page *page)
{
	wetuwn &page_addwess_htabwe[hash_ptw(page, PA_HASH_OWDEW)];
}

/**
 * page_addwess - get the mapped viwtuaw addwess of a page
 * @page: &stwuct page to get the viwtuaw addwess of
 *
 * Wetuwns the page's viwtuaw addwess.
 */
void *page_addwess(const stwuct page *page)
{
	unsigned wong fwags;
	void *wet;
	stwuct page_addwess_swot *pas;

	if (!PageHighMem(page))
		wetuwn wowmem_page_addwess(page);

	pas = page_swot(page);
	wet = NUWW;
	spin_wock_iwqsave(&pas->wock, fwags);
	if (!wist_empty(&pas->wh)) {
		stwuct page_addwess_map *pam;

		wist_fow_each_entwy(pam, &pas->wh, wist) {
			if (pam->page == page) {
				wet = pam->viwtuaw;
				bweak;
			}
		}
	}

	spin_unwock_iwqwestowe(&pas->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(page_addwess);

/**
 * set_page_addwess - set a page's viwtuaw addwess
 * @page: &stwuct page to set
 * @viwtuaw: viwtuaw addwess to use
 */
void set_page_addwess(stwuct page *page, void *viwtuaw)
{
	unsigned wong fwags;
	stwuct page_addwess_swot *pas;
	stwuct page_addwess_map *pam;

	BUG_ON(!PageHighMem(page));

	pas = page_swot(page);
	if (viwtuaw) {		/* Add */
		pam = &page_addwess_maps[PKMAP_NW((unsigned wong)viwtuaw)];
		pam->page = page;
		pam->viwtuaw = viwtuaw;

		spin_wock_iwqsave(&pas->wock, fwags);
		wist_add_taiw(&pam->wist, &pas->wh);
		spin_unwock_iwqwestowe(&pas->wock, fwags);
	} ewse {		/* Wemove */
		spin_wock_iwqsave(&pas->wock, fwags);
		wist_fow_each_entwy(pam, &pas->wh, wist) {
			if (pam->page == page) {
				wist_dew(&pam->wist);
				bweak;
			}
		}
		spin_unwock_iwqwestowe(&pas->wock, fwags);
	}
}

void __init page_addwess_init(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(page_addwess_htabwe); i++) {
		INIT_WIST_HEAD(&page_addwess_htabwe[i].wh);
		spin_wock_init(&page_addwess_htabwe[i].wock);
	}
}

#endif	/* defined(HASHED_PAGE_VIWTUAW) */
