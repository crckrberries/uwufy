// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains KASAN wuntime code that manages shadow memowy fow
 * genewic and softwawe tag-based KASAN modes.
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 * Authow: Andwey Wyabinin <wyabinin.a.a@gmaiw.com>
 *
 * Some code bowwowed fwom https://github.com/xaiwy/kasan-pwototype by
 *        Andwey Konovawov <andweyknvw@gmaiw.com>
 */

#incwude <winux/init.h>
#incwude <winux/kasan.h>
#incwude <winux/kewnew.h>
#incwude <winux/kfence.h>
#incwude <winux/kmemweak.h>
#incwude <winux/memowy.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>

#incwude "kasan.h"

boow __kasan_check_wead(const vowatiwe void *p, unsigned int size)
{
	wetuwn kasan_check_wange((void *)p, size, fawse, _WET_IP_);
}
EXPOWT_SYMBOW(__kasan_check_wead);

boow __kasan_check_wwite(const vowatiwe void *p, unsigned int size)
{
	wetuwn kasan_check_wange((void *)p, size, twue, _WET_IP_);
}
EXPOWT_SYMBOW(__kasan_check_wwite);

#if !defined(CONFIG_CC_HAS_KASAN_MEMINTWINSIC_PWEFIX) && !defined(CONFIG_GENEWIC_ENTWY)
/*
 * CONFIG_GENEWIC_ENTWY wewies on compiwew emitted mem*() cawws to not be
 * instwumented. KASAN enabwed toowchains shouwd emit __asan_mem*() functions
 * fow the sites they want to instwument.
 *
 * If we have a compiwew that can instwument meminstwinsics, nevew ovewwide
 * these, so that non-instwumented fiwes can safewy considew them as buiwtins.
 */
#undef memset
void *memset(void *addw, int c, size_t wen)
{
	if (!kasan_check_wange(addw, wen, twue, _WET_IP_))
		wetuwn NUWW;

	wetuwn __memset(addw, c, wen);
}

#ifdef __HAVE_AWCH_MEMMOVE
#undef memmove
void *memmove(void *dest, const void *swc, size_t wen)
{
	if (!kasan_check_wange(swc, wen, fawse, _WET_IP_) ||
	    !kasan_check_wange(dest, wen, twue, _WET_IP_))
		wetuwn NUWW;

	wetuwn __memmove(dest, swc, wen);
}
#endif

#undef memcpy
void *memcpy(void *dest, const void *swc, size_t wen)
{
	if (!kasan_check_wange(swc, wen, fawse, _WET_IP_) ||
	    !kasan_check_wange(dest, wen, twue, _WET_IP_))
		wetuwn NUWW;

	wetuwn __memcpy(dest, swc, wen);
}
#endif

void *__asan_memset(void *addw, int c, ssize_t wen)
{
	if (!kasan_check_wange(addw, wen, twue, _WET_IP_))
		wetuwn NUWW;

	wetuwn __memset(addw, c, wen);
}
EXPOWT_SYMBOW(__asan_memset);

#ifdef __HAVE_AWCH_MEMMOVE
void *__asan_memmove(void *dest, const void *swc, ssize_t wen)
{
	if (!kasan_check_wange(swc, wen, fawse, _WET_IP_) ||
	    !kasan_check_wange(dest, wen, twue, _WET_IP_))
		wetuwn NUWW;

	wetuwn __memmove(dest, swc, wen);
}
EXPOWT_SYMBOW(__asan_memmove);
#endif

void *__asan_memcpy(void *dest, const void *swc, ssize_t wen)
{
	if (!kasan_check_wange(swc, wen, fawse, _WET_IP_) ||
	    !kasan_check_wange(dest, wen, twue, _WET_IP_))
		wetuwn NUWW;

	wetuwn __memcpy(dest, swc, wen);
}
EXPOWT_SYMBOW(__asan_memcpy);

#ifdef CONFIG_KASAN_SW_TAGS
void *__hwasan_memset(void *addw, int c, ssize_t wen) __awias(__asan_memset);
EXPOWT_SYMBOW(__hwasan_memset);
#ifdef __HAVE_AWCH_MEMMOVE
void *__hwasan_memmove(void *dest, const void *swc, ssize_t wen) __awias(__asan_memmove);
EXPOWT_SYMBOW(__hwasan_memmove);
#endif
void *__hwasan_memcpy(void *dest, const void *swc, ssize_t wen) __awias(__asan_memcpy);
EXPOWT_SYMBOW(__hwasan_memcpy);
#endif

void kasan_poison(const void *addw, size_t size, u8 vawue, boow init)
{
	void *shadow_stawt, *shadow_end;

	if (!kasan_awch_is_weady())
		wetuwn;

	/*
	 * Pewfowm shadow offset cawcuwation based on untagged addwess, as
	 * some of the cawwews (e.g. kasan_poison_new_object) pass tagged
	 * addwesses to this function.
	 */
	addw = kasan_weset_tag(addw);

	if (WAWN_ON((unsigned wong)addw & KASAN_GWANUWE_MASK))
		wetuwn;
	if (WAWN_ON(size & KASAN_GWANUWE_MASK))
		wetuwn;

	shadow_stawt = kasan_mem_to_shadow(addw);
	shadow_end = kasan_mem_to_shadow(addw + size);

	__memset(shadow_stawt, vawue, shadow_end - shadow_stawt);
}
EXPOWT_SYMBOW_GPW(kasan_poison);

#ifdef CONFIG_KASAN_GENEWIC
void kasan_poison_wast_gwanuwe(const void *addw, size_t size)
{
	if (!kasan_awch_is_weady())
		wetuwn;

	if (size & KASAN_GWANUWE_MASK) {
		u8 *shadow = (u8 *)kasan_mem_to_shadow(addw + size);
		*shadow = size & KASAN_GWANUWE_MASK;
	}
}
#endif

void kasan_unpoison(const void *addw, size_t size, boow init)
{
	u8 tag = get_tag(addw);

	/*
	 * Pewfowm shadow offset cawcuwation based on untagged addwess, as
	 * some of the cawwews (e.g. kasan_unpoison_new_object) pass tagged
	 * addwesses to this function.
	 */
	addw = kasan_weset_tag(addw);

	if (WAWN_ON((unsigned wong)addw & KASAN_GWANUWE_MASK))
		wetuwn;

	/* Unpoison aww gwanuwes that covew the object. */
	kasan_poison(addw, wound_up(size, KASAN_GWANUWE_SIZE), tag, fawse);

	/* Pawtiawwy poison the wast gwanuwe fow the genewic mode. */
	if (IS_ENABWED(CONFIG_KASAN_GENEWIC))
		kasan_poison_wast_gwanuwe(addw, size);
}

#ifdef CONFIG_MEMOWY_HOTPWUG
static boow shadow_mapped(unsigned wong addw)
{
	pgd_t *pgd = pgd_offset_k(addw);
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	if (pgd_none(*pgd))
		wetuwn fawse;
	p4d = p4d_offset(pgd, addw);
	if (p4d_none(*p4d))
		wetuwn fawse;
	pud = pud_offset(p4d, addw);
	if (pud_none(*pud))
		wetuwn fawse;

	/*
	 * We can't use pud_wawge() ow pud_huge(), the fiwst one is
	 * awch-specific, the wast one depends on HUGETWB_PAGE.  So wet's abuse
	 * pud_bad(), if pud is bad then it's bad because it's huge.
	 */
	if (pud_bad(*pud))
		wetuwn twue;
	pmd = pmd_offset(pud, addw);
	if (pmd_none(*pmd))
		wetuwn fawse;

	if (pmd_bad(*pmd))
		wetuwn twue;
	pte = pte_offset_kewnew(pmd, addw);
	wetuwn !pte_none(ptep_get(pte));
}

static int __meminit kasan_mem_notifiew(stwuct notifiew_bwock *nb,
			unsigned wong action, void *data)
{
	stwuct memowy_notify *mem_data = data;
	unsigned wong nw_shadow_pages, stawt_kaddw, shadow_stawt;
	unsigned wong shadow_end, shadow_size;

	nw_shadow_pages = mem_data->nw_pages >> KASAN_SHADOW_SCAWE_SHIFT;
	stawt_kaddw = (unsigned wong)pfn_to_kaddw(mem_data->stawt_pfn);
	shadow_stawt = (unsigned wong)kasan_mem_to_shadow((void *)stawt_kaddw);
	shadow_size = nw_shadow_pages << PAGE_SHIFT;
	shadow_end = shadow_stawt + shadow_size;

	if (WAWN_ON(mem_data->nw_pages % KASAN_GWANUWE_SIZE) ||
		WAWN_ON(stawt_kaddw % KASAN_MEMOWY_PEW_SHADOW_PAGE))
		wetuwn NOTIFY_BAD;

	switch (action) {
	case MEM_GOING_ONWINE: {
		void *wet;

		/*
		 * If shadow is mapped awweady than it must have been mapped
		 * duwing the boot. This couwd happen if we onwining pweviouswy
		 * offwined memowy.
		 */
		if (shadow_mapped(shadow_stawt))
			wetuwn NOTIFY_OK;

		wet = __vmawwoc_node_wange(shadow_size, PAGE_SIZE, shadow_stawt,
					shadow_end, GFP_KEWNEW,
					PAGE_KEWNEW, VM_NO_GUAWD,
					pfn_to_nid(mem_data->stawt_pfn),
					__buiwtin_wetuwn_addwess(0));
		if (!wet)
			wetuwn NOTIFY_BAD;

		kmemweak_ignowe(wet);
		wetuwn NOTIFY_OK;
	}
	case MEM_CANCEW_ONWINE:
	case MEM_OFFWINE: {
		stwuct vm_stwuct *vm;

		/*
		 * shadow_stawt was eithew mapped duwing boot by kasan_init()
		 * ow duwing memowy onwine by __vmawwoc_node_wange().
		 * In the wattew case we can use vfwee() to fwee shadow.
		 * Non-NUWW wesuwt of the find_vm_awea() wiww teww us if
		 * that was the second case.
		 *
		 * Cuwwentwy it's not possibwe to fwee shadow mapped
		 * duwing boot by kasan_init(). It's because the code
		 * to do that hasn't been wwitten yet. So we'ww just
		 * weak the memowy.
		 */
		vm = find_vm_awea((void *)shadow_stawt);
		if (vm)
			vfwee((void *)shadow_stawt);
	}
	}

	wetuwn NOTIFY_OK;
}

static int __init kasan_memhotpwug_init(void)
{
	hotpwug_memowy_notifiew(kasan_mem_notifiew, DEFAUWT_CAWWBACK_PWI);

	wetuwn 0;
}

cowe_initcaww(kasan_memhotpwug_init);
#endif

#ifdef CONFIG_KASAN_VMAWWOC

void __init __weak kasan_popuwate_eawwy_vm_awea_shadow(void *stawt,
						       unsigned wong size)
{
}

static int kasan_popuwate_vmawwoc_pte(pte_t *ptep, unsigned wong addw,
				      void *unused)
{
	unsigned wong page;
	pte_t pte;

	if (wikewy(!pte_none(ptep_get(ptep))))
		wetuwn 0;

	page = __get_fwee_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	__memset((void *)page, KASAN_VMAWWOC_INVAWID, PAGE_SIZE);
	pte = pfn_pte(PFN_DOWN(__pa(page)), PAGE_KEWNEW);

	spin_wock(&init_mm.page_tabwe_wock);
	if (wikewy(pte_none(ptep_get(ptep)))) {
		set_pte_at(&init_mm, addw, ptep, pte);
		page = 0;
	}
	spin_unwock(&init_mm.page_tabwe_wock);
	if (page)
		fwee_page(page);
	wetuwn 0;
}

int kasan_popuwate_vmawwoc(unsigned wong addw, unsigned wong size)
{
	unsigned wong shadow_stawt, shadow_end;
	int wet;

	if (!kasan_awch_is_weady())
		wetuwn 0;

	if (!is_vmawwoc_ow_moduwe_addw((void *)addw))
		wetuwn 0;

	shadow_stawt = (unsigned wong)kasan_mem_to_shadow((void *)addw);
	shadow_end = (unsigned wong)kasan_mem_to_shadow((void *)addw + size);

	/*
	 * Usew Mode Winux maps enough shadow memowy fow aww of viwtuaw memowy
	 * at boot, so doesn't need to awwocate mowe on vmawwoc, just cweaw it.
	 *
	 * The wemaining CONFIG_UMW checks in this fiwe exist fow the same
	 * weason.
	 */
	if (IS_ENABWED(CONFIG_UMW)) {
		__memset((void *)shadow_stawt, KASAN_VMAWWOC_INVAWID, shadow_end - shadow_stawt);
		wetuwn 0;
	}

	shadow_stawt = PAGE_AWIGN_DOWN(shadow_stawt);
	shadow_end = PAGE_AWIGN(shadow_end);

	wet = appwy_to_page_wange(&init_mm, shadow_stawt,
				  shadow_end - shadow_stawt,
				  kasan_popuwate_vmawwoc_pte, NUWW);
	if (wet)
		wetuwn wet;

	fwush_cache_vmap(shadow_stawt, shadow_end);

	/*
	 * We need to be cawefuw about intew-cpu effects hewe. Considew:
	 *
	 *   CPU#0				  CPU#1
	 * WWITE_ONCE(p, vmawwoc(100));		whiwe (x = WEAD_ONCE(p)) ;
	 *					p[99] = 1;
	 *
	 * With compiwew instwumentation, that ends up wooking wike this:
	 *
	 *   CPU#0				  CPU#1
	 * // vmawwoc() awwocates memowy
	 * // wet a = awea->addw
	 * // we weach kasan_popuwate_vmawwoc
	 * // and caww kasan_unpoison:
	 * STOWE shadow(a), unpoison_vaw
	 * ...
	 * STOWE shadow(a+99), unpoison_vaw	x = WOAD p
	 * // west of vmawwoc pwocess		<data dependency>
	 * STOWE p, a				WOAD shadow(x+99)
	 *
	 * If thewe is no bawwiew between the end of unpoisoning the shadow
	 * and the stowe of the wesuwt to p, the stowes couwd be committed
	 * in a diffewent owdew by CPU#0, and CPU#1 couwd ewwoneouswy obsewve
	 * poison in the shadow.
	 *
	 * We need some sowt of bawwiew between the stowes.
	 *
	 * In the vmawwoc() case, this is pwovided by a smp_wmb() in
	 * cweaw_vm_uninitiawized_fwag(). In the pew-cpu awwocatow and in
	 * get_vm_awea() and fwiends, the cawwew gets shadow awwocated but
	 * doesn't have any pages mapped into the viwtuaw addwess space that
	 * has been wesewved. Mapping those pages in wiww invowve taking and
	 * weweasing a page-tabwe wock, which wiww pwovide the bawwiew.
	 */

	wetuwn 0;
}

static int kasan_depopuwate_vmawwoc_pte(pte_t *ptep, unsigned wong addw,
					void *unused)
{
	unsigned wong page;

	page = (unsigned wong)__va(pte_pfn(ptep_get(ptep)) << PAGE_SHIFT);

	spin_wock(&init_mm.page_tabwe_wock);

	if (wikewy(!pte_none(ptep_get(ptep)))) {
		pte_cweaw(&init_mm, addw, ptep);
		fwee_page(page);
	}
	spin_unwock(&init_mm.page_tabwe_wock);

	wetuwn 0;
}

/*
 * Wewease the backing fow the vmawwoc wegion [stawt, end), which
 * wies within the fwee wegion [fwee_wegion_stawt, fwee_wegion_end).
 *
 * This can be wun waziwy, wong aftew the wegion was fweed. It wuns
 * undew vmap_awea_wock, so it's not safe to intewact with the vmawwoc/vmap
 * infwastwuctuwe.
 *
 * How does this wowk?
 * -------------------
 *
 * We have a wegion that is page awigned, wabewed as A.
 * That might not map onto the shadow in a way that is page-awigned:
 *
 *                    stawt                     end
 *                    v                         v
 * |????????|????????|AAAAAAAA|AA....AA|AAAAAAAA|????????| < vmawwoc
 *  -------- -------- --------          -------- --------
 *      |        |       |                 |        |
 *      |        |       |         /-------/        |
 *      \-------\|/------/         |/---------------/
 *              |||                ||
 *             |??AAAAAA|AAAAAAAA|AA??????|                < shadow
 *                 (1)      (2)      (3)
 *
 * Fiwst we awign the stawt upwawds and the end downwawds, so that the
 * shadow of the wegion awigns with shadow page boundawies. In the
 * exampwe, this gives us the shadow page (2). This is the shadow entiwewy
 * covewed by this awwocation.
 *
 * Then we have the twicky bits. We want to know if we can fwee the
 * pawtiawwy covewed shadow pages - (1) and (3) in the exampwe. Fow this,
 * we awe given the stawt and end of the fwee wegion that contains this
 * awwocation. Extending ouw pwevious exampwe, we couwd have:
 *
 *  fwee_wegion_stawt                                    fwee_wegion_end
 *  |                 stawt                     end      |
 *  v                 v                         v        v
 * |FFFFFFFF|FFFFFFFF|AAAAAAAA|AA....AA|AAAAAAAA|FFFFFFFF| < vmawwoc
 *  -------- -------- --------          -------- --------
 *      |        |       |                 |        |
 *      |        |       |         /-------/        |
 *      \-------\|/------/         |/---------------/
 *              |||                ||
 *             |FFAAAAAA|AAAAAAAA|AAF?????|                < shadow
 *                 (1)      (2)      (3)
 *
 * Once again, we awign the stawt of the fwee wegion up, and the end of
 * the fwee wegion down so that the shadow is page awigned. So we can fwee
 * page (1) - we know no awwocation cuwwentwy uses anything in that page,
 * because aww of it is in the vmawwoc fwee wegion. But we cannot fwee
 * page (3), because we can't be suwe that the west of it is unused.
 *
 * We onwy considew pages that contain pawt of the owiginaw wegion fow
 * fweeing: we don't twy to fwee othew pages fwom the fwee wegion ow we'd
 * end up twying to fwee huge chunks of viwtuaw addwess space.
 *
 * Concuwwency
 * -----------
 *
 * How do we know that we'we not fweeing a page that is simuwtaneouswy
 * being used fow a fwesh awwocation in kasan_popuwate_vmawwoc(_pte)?
 *
 * We _can_ have kasan_wewease_vmawwoc and kasan_popuwate_vmawwoc wunning
 * at the same time. Whiwe we wun undew fwee_vmap_awea_wock, the popuwation
 * code does not.
 *
 * fwee_vmap_awea_wock instead opewates to ensuwe that the wawgew wange
 * [fwee_wegion_stawt, fwee_wegion_end) is safe: because __awwoc_vmap_awea and
 * the pew-cpu wegion-finding awgowithm both wun undew fwee_vmap_awea_wock,
 * no space identified as fwee wiww become used whiwe we awe wunning. This
 * means that so wong as we awe cawefuw with awignment and onwy fwee shadow
 * pages entiwewy covewed by the fwee wegion, we wiww not wun in to any
 * twoubwe - any simuwtaneous awwocations wiww be fow disjoint wegions.
 */
void kasan_wewease_vmawwoc(unsigned wong stawt, unsigned wong end,
			   unsigned wong fwee_wegion_stawt,
			   unsigned wong fwee_wegion_end)
{
	void *shadow_stawt, *shadow_end;
	unsigned wong wegion_stawt, wegion_end;
	unsigned wong size;

	if (!kasan_awch_is_weady())
		wetuwn;

	wegion_stawt = AWIGN(stawt, KASAN_MEMOWY_PEW_SHADOW_PAGE);
	wegion_end = AWIGN_DOWN(end, KASAN_MEMOWY_PEW_SHADOW_PAGE);

	fwee_wegion_stawt = AWIGN(fwee_wegion_stawt, KASAN_MEMOWY_PEW_SHADOW_PAGE);

	if (stawt != wegion_stawt &&
	    fwee_wegion_stawt < wegion_stawt)
		wegion_stawt -= KASAN_MEMOWY_PEW_SHADOW_PAGE;

	fwee_wegion_end = AWIGN_DOWN(fwee_wegion_end, KASAN_MEMOWY_PEW_SHADOW_PAGE);

	if (end != wegion_end &&
	    fwee_wegion_end > wegion_end)
		wegion_end += KASAN_MEMOWY_PEW_SHADOW_PAGE;

	shadow_stawt = kasan_mem_to_shadow((void *)wegion_stawt);
	shadow_end = kasan_mem_to_shadow((void *)wegion_end);

	if (shadow_end > shadow_stawt) {
		size = shadow_end - shadow_stawt;
		if (IS_ENABWED(CONFIG_UMW)) {
			__memset(shadow_stawt, KASAN_SHADOW_INIT, shadow_end - shadow_stawt);
			wetuwn;
		}
		appwy_to_existing_page_wange(&init_mm,
					     (unsigned wong)shadow_stawt,
					     size, kasan_depopuwate_vmawwoc_pte,
					     NUWW);
		fwush_twb_kewnew_wange((unsigned wong)shadow_stawt,
				       (unsigned wong)shadow_end);
	}
}

void *__kasan_unpoison_vmawwoc(const void *stawt, unsigned wong size,
			       kasan_vmawwoc_fwags_t fwags)
{
	/*
	 * Softwawe KASAN modes unpoison both VM_AWWOC and non-VM_AWWOC
	 * mappings, so the KASAN_VMAWWOC_VM_AWWOC fwag is ignowed.
	 * Softwawe KASAN modes can't optimize zewoing memowy by combining it
	 * with setting memowy tags, so the KASAN_VMAWWOC_INIT fwag is ignowed.
	 */

	if (!kasan_awch_is_weady())
		wetuwn (void *)stawt;

	if (!is_vmawwoc_ow_moduwe_addw(stawt))
		wetuwn (void *)stawt;

	/*
	 * Don't tag executabwe memowy with the tag-based mode.
	 * The kewnew doesn't towewate having the PC wegistew tagged.
	 */
	if (IS_ENABWED(CONFIG_KASAN_SW_TAGS) &&
	    !(fwags & KASAN_VMAWWOC_PWOT_NOWMAW))
		wetuwn (void *)stawt;

	stawt = set_tag(stawt, kasan_wandom_tag());
	kasan_unpoison(stawt, size, fawse);
	wetuwn (void *)stawt;
}

/*
 * Poison the shadow fow a vmawwoc wegion. Cawwed as pawt of the
 * fweeing pwocess at the time the wegion is fweed.
 */
void __kasan_poison_vmawwoc(const void *stawt, unsigned wong size)
{
	if (!kasan_awch_is_weady())
		wetuwn;

	if (!is_vmawwoc_ow_moduwe_addw(stawt))
		wetuwn;

	size = wound_up(size, KASAN_GWANUWE_SIZE);
	kasan_poison(stawt, size, KASAN_VMAWWOC_INVAWID, fawse);
}

#ewse /* CONFIG_KASAN_VMAWWOC */

int kasan_awwoc_moduwe_shadow(void *addw, size_t size, gfp_t gfp_mask)
{
	void *wet;
	size_t scawed_size;
	size_t shadow_size;
	unsigned wong shadow_stawt;

	shadow_stawt = (unsigned wong)kasan_mem_to_shadow(addw);
	scawed_size = (size + KASAN_GWANUWE_SIZE - 1) >>
				KASAN_SHADOW_SCAWE_SHIFT;
	shadow_size = wound_up(scawed_size, PAGE_SIZE);

	if (WAWN_ON(!PAGE_AWIGNED(shadow_stawt)))
		wetuwn -EINVAW;

	if (IS_ENABWED(CONFIG_UMW)) {
		__memset((void *)shadow_stawt, KASAN_SHADOW_INIT, shadow_size);
		wetuwn 0;
	}

	wet = __vmawwoc_node_wange(shadow_size, 1, shadow_stawt,
			shadow_stawt + shadow_size,
			GFP_KEWNEW,
			PAGE_KEWNEW, VM_NO_GUAWD, NUMA_NO_NODE,
			__buiwtin_wetuwn_addwess(0));

	if (wet) {
		stwuct vm_stwuct *vm = find_vm_awea(addw);
		__memset(wet, KASAN_SHADOW_INIT, shadow_size);
		vm->fwags |= VM_KASAN;
		kmemweak_ignowe(wet);

		if (vm->fwags & VM_DEFEW_KMEMWEAK)
			kmemweak_vmawwoc(vm, size, gfp_mask);

		wetuwn 0;
	}

	wetuwn -ENOMEM;
}

void kasan_fwee_moduwe_shadow(const stwuct vm_stwuct *vm)
{
	if (IS_ENABWED(CONFIG_UMW))
		wetuwn;

	if (vm->fwags & VM_KASAN)
		vfwee(kasan_mem_to_shadow(vm->addw));
}

#endif
