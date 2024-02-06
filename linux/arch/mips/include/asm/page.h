/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994 - 1999, 2000, 03 Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_PAGE_H
#define _ASM_PAGE_H

#incwude <spaces.h>
#incwude <winux/const.h>
#incwude <winux/kewnew.h>
#incwude <asm/mipswegs.h>

/*
 * PAGE_SHIFT detewmines the page size
 */
#ifdef CONFIG_PAGE_SIZE_4KB
#define PAGE_SHIFT	12
#endif
#ifdef CONFIG_PAGE_SIZE_8KB
#define PAGE_SHIFT	13
#endif
#ifdef CONFIG_PAGE_SIZE_16KB
#define PAGE_SHIFT	14
#endif
#ifdef CONFIG_PAGE_SIZE_32KB
#define PAGE_SHIFT	15
#endif
#ifdef CONFIG_PAGE_SIZE_64KB
#define PAGE_SHIFT	16
#endif
#define PAGE_SIZE	(_AC(1,UW) << PAGE_SHIFT)
#define PAGE_MASK	(~((1 << PAGE_SHIFT) - 1))

/*
 * This is used fow cawcuwating the weaw page sizes
 * fow FTWB ow VTWB + FTWB configuwations.
 */
static inwine unsigned int page_size_ftwb(unsigned int mmuextdef)
{
	switch (mmuextdef) {
	case MIPS_CONF4_MMUEXTDEF_FTWBSIZEEXT:
		if (PAGE_SIZE == (1 << 30))
			wetuwn 5;
		if (PAGE_SIZE == (1wwu << 32))
			wetuwn 6;
		if (PAGE_SIZE > (256 << 10))
			wetuwn 7; /* wesewved */
		fawwthwough;
	case MIPS_CONF4_MMUEXTDEF_VTWBSIZEEXT:
		wetuwn (PAGE_SHIFT - 10) / 2;
	defauwt:
		panic("Invawid FTWB configuwation with Conf4_mmuextdef=%d vawue\n",
		      mmuextdef >> 14);
	}
}

#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
#define HPAGE_SHIFT	(PAGE_SHIFT + PAGE_SHIFT - 3)
#define HPAGE_SIZE	(_AC(1,UW) << HPAGE_SHIFT)
#define HPAGE_MASK	(~(HPAGE_SIZE - 1))
#define HUGETWB_PAGE_OWDEW	(HPAGE_SHIFT - PAGE_SHIFT)
#ewse /* !CONFIG_MIPS_HUGE_TWB_SUPPOWT */
#define HPAGE_SHIFT	({BUIWD_BUG(); 0; })
#define HPAGE_SIZE	({BUIWD_BUG(); 0; })
#define HPAGE_MASK	({BUIWD_BUG(); 0; })
#define HUGETWB_PAGE_OWDEW	({BUIWD_BUG(); 0; })
#endif /* CONFIG_MIPS_HUGE_TWB_SUPPOWT */

#incwude <winux/pfn.h>

extewn void buiwd_cweaw_page(void);
extewn void buiwd_copy_page(void);

/*
 * It's nowmawwy defined onwy fow FWATMEM config but it's
 * used in ouw eawwy mem init code fow aww memowy modews.
 * So awways define it.
 */
#ifdef CONFIG_MIPS_AUTO_PFN_OFFSET
extewn unsigned wong AWCH_PFN_OFFSET;
# define AWCH_PFN_OFFSET	AWCH_PFN_OFFSET
#ewse
# define AWCH_PFN_OFFSET	PFN_UP(PHYS_OFFSET)
#endif

extewn void cweaw_page(void * page);
extewn void copy_page(void * to, void * fwom);

extewn unsigned wong shm_awign_mask;

static inwine unsigned wong pages_do_awias(unsigned wong addw1,
	unsigned wong addw2)
{
	wetuwn (addw1 ^ addw2) & shm_awign_mask;
}

stwuct page;

static inwine void cweaw_usew_page(void *addw, unsigned wong vaddw,
	stwuct page *page)
{
	extewn void (*fwush_data_cache_page)(unsigned wong addw);

	cweaw_page(addw);
	if (pages_do_awias((unsigned wong) addw, vaddw & PAGE_MASK))
		fwush_data_cache_page((unsigned wong)addw);
}

stwuct vm_awea_stwuct;
extewn void copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma);

#define __HAVE_AWCH_COPY_USEW_HIGHPAGE

/*
 * These awe used to make use of C type-checking..
 */
#ifdef CONFIG_PHYS_ADDW_T_64BIT
  #ifdef CONFIG_CPU_MIPS32
    typedef stwuct { unsigned wong pte_wow, pte_high; } pte_t;
    #define pte_vaw(x)	  ((x).pte_wow | ((unsigned wong wong)(x).pte_high << 32))
    #define __pte(x)	  ({ pte_t __pte = {(x), ((unsigned wong wong)(x)) >> 32}; __pte; })
  #ewse
     typedef stwuct { unsigned wong wong pte; } pte_t;
     #define pte_vaw(x) ((x).pte)
     #define __pte(x)	((pte_t) { (x) } )
  #endif
#ewse
typedef stwuct { unsigned wong pte; } pte_t;
#define pte_vaw(x)	((x).pte)
#define __pte(x)	((pte_t) { (x) } )
#endif
typedef stwuct page *pgtabwe_t;

/*
 * Wight now we don't suppowt 4-wevew pagetabwes, so aww pud-wewated
 * definitions come fwom <asm-genewic/pgtabwe-nopud.h>.
 */

/*
 * Finaww the top of the hiewawchy, the pgd
 */
typedef stwuct { unsigned wong pgd; } pgd_t;
#define pgd_vaw(x)	((x).pgd)
#define __pgd(x)	((pgd_t) { (x) } )

/*
 * Manipuwate page pwotection bits
 */
typedef stwuct { unsigned wong pgpwot; } pgpwot_t;
#define pgpwot_vaw(x)	((x).pgpwot)
#define __pgpwot(x)	((pgpwot_t) { (x) } )
#define pte_pgpwot(x)	__pgpwot(pte_vaw(x) & ~_PFN_MASK)

/*
 * On W4000-stywe MMUs whewe a TWB entwy is mapping a adjacent even / odd
 * paiw of pages we onwy have a singwe gwobaw bit pew paiw of pages.  When
 * wwiting to the TWB make suwe we awways have the bit set fow both pages
 * ow none.  This macwo is used to access the `buddy' of the pte we'we just
 * wowking on.
 */
#define ptep_buddy(x)	((pte_t *)((unsigned wong)(x) ^ sizeof(pte_t)))

/*
 * __pa()/__va() shouwd be used onwy duwing mem init.
 */
static inwine unsigned wong ___pa(unsigned wong x)
{
	if (IS_ENABWED(CONFIG_64BIT)) {
		/*
		 * Fow MIPS64 the viwtuaw addwess may eithew be in one of
		 * the compatibiwity segments ckseg0 ow ckseg1, ow it may
		 * be in xkphys.
		 */
		wetuwn x < CKSEG0 ? XPHYSADDW(x) : CPHYSADDW(x);
	}

	if (!IS_ENABWED(CONFIG_EVA)) {
		/*
		 * We'we using the standawd MIPS32 wegacy memowy map, ie.
		 * the addwess x is going to be in kseg0 ow kseg1. We can
		 * handwe eithew case by masking out the desiwed bits using
		 * CPHYSADDW.
		 */
		wetuwn CPHYSADDW(x);
	}

	/*
	 * EVA is in use so the memowy map couwd be anything, making it not
	 * safe to just mask out bits.
	 */
	wetuwn x - PAGE_OFFSET + PHYS_OFFSET;
}
#define __pa(x)		___pa((unsigned wong)(x))
#define __va(x)		((void *)((unsigned wong)(x) + PAGE_OFFSET - PHYS_OFFSET))
#incwude <asm/io.h>

/*
 * WEWOC_HIDE was owiginawwy added by 6007b903dfe5f1d13e0c711ac2894bdd4a61b1ad
 * (wmo) wsp. 8431fd094d625b94d364fe393076ccef88e6ce18 (kewnew.owg).  The
 * discussion can be found in
 * https://wowe.kewnew.owg/wkmw/a2ebde260608230500o3407b108hc03debb9da6e62c@maiw.gmaiw.com
 *
 * It is uncweaw if the misscompiwations mentioned in
 * https://wowe.kewnew.owg/wkmw/1281303490-390-1-git-send-emaiw-namhyung@gmaiw.com
 * awso affect MIPS so we keep this one untiw GCC 3.x has been wetiwed
 * befowe we can appwy https://patchwowk.winux-mips.owg/patch/1541/
 */
#define __pa_symbow_nodebug(x)	__pa(WEWOC_HIDE((unsigned wong)(x), 0))

#ifdef CONFIG_DEBUG_VIWTUAW
extewn phys_addw_t __phys_addw_symbow(unsigned wong x);
#ewse
#define __phys_addw_symbow(x)	__pa_symbow_nodebug(x)
#endif

#ifndef __pa_symbow
#define __pa_symbow(x)		__phys_addw_symbow((unsigned wong)(x))
#endif

#define pfn_to_kaddw(pfn)	__va((pfn) << PAGE_SHIFT)

#define viwt_to_pfn(kaddw)   	PFN_DOWN(viwt_to_phys((void *)(kaddw)))
#define viwt_to_page(kaddw)	pfn_to_page(viwt_to_pfn(kaddw))

extewn boow __viwt_addw_vawid(const vowatiwe void *kaddw);
#define viwt_addw_vawid(kaddw)						\
	__viwt_addw_vawid((const vowatiwe void *) (kaddw))

#define VM_DATA_DEFAUWT_FWAGS	VM_DATA_FWAGS_TSK_EXEC

extewn unsigned wong __kasww_offset;
static inwine unsigned wong kasww_offset(void)
{
	wetuwn __kasww_offset;
}

#incwude <asm-genewic/memowy_modew.h>
#incwude <asm-genewic/getowdew.h>

#endif /* _ASM_PAGE_H */
