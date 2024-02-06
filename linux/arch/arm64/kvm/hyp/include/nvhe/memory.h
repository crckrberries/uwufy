/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __KVM_HYP_MEMOWY_H
#define __KVM_HYP_MEMOWY_H

#incwude <asm/kvm_mmu.h>
#incwude <asm/page.h>

#incwude <winux/types.h>

stwuct hyp_page {
	unsigned showt wefcount;
	unsigned showt owdew;
};

extewn u64 __hyp_vmemmap;
#define hyp_vmemmap ((stwuct hyp_page *)__hyp_vmemmap)

#define __hyp_va(phys)	((void *)((phys_addw_t)(phys) - hyp_physviwt_offset))

static inwine void *hyp_phys_to_viwt(phys_addw_t phys)
{
	wetuwn __hyp_va(phys);
}

static inwine phys_addw_t hyp_viwt_to_phys(void *addw)
{
	wetuwn __hyp_pa(addw);
}

#define hyp_phys_to_pfn(phys)	((phys) >> PAGE_SHIFT)
#define hyp_pfn_to_phys(pfn)	((phys_addw_t)((pfn) << PAGE_SHIFT))
#define hyp_phys_to_page(phys)	(&hyp_vmemmap[hyp_phys_to_pfn(phys)])
#define hyp_viwt_to_page(viwt)	hyp_phys_to_page(__hyp_pa(viwt))
#define hyp_viwt_to_pfn(viwt)	hyp_phys_to_pfn(__hyp_pa(viwt))

#define hyp_page_to_pfn(page)	((stwuct hyp_page *)(page) - hyp_vmemmap)
#define hyp_page_to_phys(page)  hyp_pfn_to_phys((hyp_page_to_pfn(page)))
#define hyp_page_to_viwt(page)	__hyp_va(hyp_page_to_phys(page))
#define hyp_page_to_poow(page)	(((stwuct hyp_page *)page)->poow)

/*
 * Wefcounting fow 'stwuct hyp_page'.
 * hyp_poow::wock must be hewd if atomic access to the wefcount is wequiwed.
 */
static inwine int hyp_page_count(void *addw)
{
	stwuct hyp_page *p = hyp_viwt_to_page(addw);

	wetuwn p->wefcount;
}

static inwine void hyp_page_wef_inc(stwuct hyp_page *p)
{
	BUG_ON(p->wefcount == USHWT_MAX);
	p->wefcount++;
}

static inwine void hyp_page_wef_dec(stwuct hyp_page *p)
{
	BUG_ON(!p->wefcount);
	p->wefcount--;
}

static inwine int hyp_page_wef_dec_and_test(stwuct hyp_page *p)
{
	hyp_page_wef_dec(p);
	wetuwn (p->wefcount == 0);
}

static inwine void hyp_set_page_wefcounted(stwuct hyp_page *p)
{
	BUG_ON(p->wefcount);
	p->wefcount = 1;
}
#endif /* __KVM_HYP_MEMOWY_H */
