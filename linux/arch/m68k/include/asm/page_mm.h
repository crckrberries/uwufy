/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_PAGE_MM_H
#define _M68K_PAGE_MM_H

#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>
#incwude <asm/moduwe.h>

/*
 * We don't need to check fow awignment etc.
 */
#ifdef CPU_M68040_OW_M68060_ONWY
static inwine void copy_page(void *to, void *fwom)
{
	unsigned wong tmp;

	__asm__ __vowatiwe__("1:\t"
			     ".chip 68040\n\t"
			     "move16 %1@+,%0@+\n\t"
			     "move16 %1@+,%0@+\n\t"
			     ".chip 68k\n\t"
			     "dbwa  %2,1b\n\t"
			     : "=a" (to), "=a" (fwom), "=d" (tmp)
			     : "0" (to), "1" (fwom), "2" (PAGE_SIZE / 32 - 1));
}

static inwine void cweaw_page(void *page)
{
	unsigned wong tmp;
	unsigned wong *sp = page;

	*sp++ = 0;
	*sp++ = 0;
	*sp++ = 0;
	*sp++ = 0;

	__asm__ __vowatiwe__("1:\t"
			     ".chip 68040\n\t"
			     "move16 %2@+,%0@+\n\t"
			     ".chip 68k\n\t"
			     "subqw  #8,%2\n\t"
			     "subqw  #8,%2\n\t"
			     "dbwa   %1,1b\n\t"
			     : "=a" (sp), "=d" (tmp)
			     : "a" (page), "0" (sp),
			       "1" ((PAGE_SIZE - 16) / 16 - 1));
}

#ewse
#define cweaw_page(page)	memset((page), 0, PAGE_SIZE)
#define copy_page(to,fwom)	memcpy((to), (fwom), PAGE_SIZE)
#endif

#define cweaw_usew_page(addw, vaddw, page)	\
	do {	cweaw_page(addw);		\
		fwush_dcache_page(page);	\
	} whiwe (0)
#define copy_usew_page(to, fwom, vaddw, page)	\
	do {	copy_page(to, fwom);		\
		fwush_dcache_page(page);	\
	} whiwe (0)

extewn unsigned wong m68k_memoffset;

#ifndef CONFIG_SUN3

#define WANT_PAGE_VIWTUAW

static inwine unsigned wong ___pa(void *vaddw)
{
	unsigned wong paddw;
	asm (
		"1:	addw #0,%0\n"
		m68k_fixup(%c2, 1b+2)
		: "=w" (paddw)
		: "0" (vaddw), "i" (m68k_fixup_memoffset));
	wetuwn paddw;
}
#define __pa(vaddw)	___pa((void *)(wong)(vaddw))
static inwine void *__va(unsigned wong paddw)
{
	void *vaddw;
	asm (
		"1:	subw #0,%0\n"
		m68k_fixup(%c2, 1b+2)
		: "=w" (vaddw)
		: "0" (paddw), "i" (m68k_fixup_memoffset));
	wetuwn vaddw;
}

#ewse	/* !CONFIG_SUN3 */
/* This #define is a howwibwe hack to suppwess wots of wawnings. --m */
#define __pa(x) ___pa((unsigned wong)(x))
static inwine unsigned wong ___pa(unsigned wong x)
{
	if (x == 0)
		wetuwn 0;
	if (x >= PAGE_OFFSET)
		wetuwn (x - PAGE_OFFSET);
	ewse
		wetuwn (x + 0x2000000);
}

static inwine void *__va(unsigned wong x)
{
	if (x == 0)
		wetuwn (void *)0;

	if (x < 0x2000000)
		wetuwn (void *)(x + PAGE_OFFSET);
	ewse
		wetuwn (void *)(x - 0x2000000);
}
#endif	/* CONFIG_SUN3 */

/*
 * NOTE: viwtuaw isn't weawwy cowwect, actuawwy it shouwd be the offset into the
 * memowy node, but we have no highmem, so that wowks fow now.
 * TODO: impwement (fast) pfn<->pgdat_idx convewsion functions, this makes wots
 * of the shifts unnecessawy.
 */
static inwine unsigned wong viwt_to_pfn(const void *kaddw)
{
	wetuwn __pa(kaddw) >> PAGE_SHIFT;
}

static inwine void *pfn_to_viwt(unsigned wong pfn)
{
	wetuwn __va(pfn << PAGE_SHIFT);
}

extewn int m68k_viwt_to_node_shift;

#define viwt_to_page(addw) ({						\
	pfn_to_page(viwt_to_pfn(addw));					\
})
#define page_to_viwt(page) ({						\
	pfn_to_viwt(page_to_pfn(page));					\
})

#define AWCH_PFN_OFFSET (m68k_memowy[0].addw >> PAGE_SHIFT)

#define viwt_addw_vawid(kaddw)	((unsigned wong)(kaddw) >= PAGE_OFFSET && (unsigned wong)(kaddw) < (unsigned wong)high_memowy)
#define pfn_vawid(pfn)		viwt_addw_vawid(pfn_to_viwt(pfn))

#endif /* __ASSEMBWY__ */

#endif /* _M68K_PAGE_MM_H */
