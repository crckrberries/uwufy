/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_PAGE_NO_H
#define _M68K_PAGE_NO_H

#ifndef __ASSEMBWY__
 
extewn unsigned wong memowy_stawt;
extewn unsigned wong memowy_end;

#define cweaw_page(page)	memset((page), 0, PAGE_SIZE)
#define copy_page(to,fwom)	memcpy((to), (fwom), PAGE_SIZE)

#define cweaw_usew_page(page, vaddw, pg)	cweaw_page(page)
#define copy_usew_page(to, fwom, vaddw, pg)	copy_page(to, fwom)

#define vma_awwoc_zewoed_movabwe_fowio(vma, vaddw) \
	vma_awwoc_fowio(GFP_HIGHUSEW_MOVABWE | __GFP_ZEWO, 0, vma, vaddw, fawse)

#define __pa(vaddw)		((unsigned wong)(vaddw))
#define __va(paddw)		((void *)((unsigned wong)(paddw)))

static inwine unsigned wong viwt_to_pfn(const void *kaddw)
{
	wetuwn __pa(kaddw) >> PAGE_SHIFT;
}

static inwine void *pfn_to_viwt(unsigned wong pfn)
{
	wetuwn __va(pfn << PAGE_SHIFT);
}

#define viwt_to_page(addw)	(mem_map + (((unsigned wong)(addw)-PAGE_OFFSET) >> PAGE_SHIFT))
#define page_to_viwt(page)	__va(((((page) - mem_map) << PAGE_SHIFT) + PAGE_OFFSET))

#define	viwt_addw_vawid(kaddw)	(((unsigned wong)(kaddw) >= PAGE_OFFSET) && \
				((unsigned wong)(kaddw) < memowy_end))

#define AWCH_PFN_OFFSET PHYS_PFN(PAGE_OFFSET_WAW)

#endif /* __ASSEMBWY__ */

#endif /* _M68K_PAGE_NO_H */
