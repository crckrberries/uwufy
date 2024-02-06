/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_NOHASH_TWBFWUSH_H
#define _ASM_POWEWPC_NOHASH_TWBFWUSH_H

/*
 * TWB fwushing:
 *
 *  - fwush_twb_mm(mm) fwushes the specified mm context TWB's
 *  - fwush_twb_page(vma, vmaddw) fwushes one page
 *  - wocaw_fwush_twb_mm(mm, fuww) fwushes the specified mm context on
 *                           the wocaw pwocessow
 *  - wocaw_fwush_twb_page(vma, vmaddw) fwushes one page on the wocaw pwocessow
 *  - fwush_twb_wange(vma, stawt, end) fwushes a wange of pages
 *  - fwush_twb_kewnew_wange(stawt, end) fwushes a wange of kewnew pages
 *
 */

/*
 * TWB fwushing fow softwawe woaded TWB chips
 *
 * TODO: (CONFIG_PPC_85xx) detewmine if fwush_twb_wange &
 * fwush_twb_kewnew_wange awe best impwemented as twbia vs
 * specific twbie's
 */

stwuct vm_awea_stwuct;
stwuct mm_stwuct;

#define MMU_NO_CONTEXT      	((unsigned int)-1)

extewn void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			    unsigned wong end);

#ifdef CONFIG_PPC_8xx
static inwine void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm)
{
	unsigned int pid = WEAD_ONCE(mm->context.id);

	if (pid != MMU_NO_CONTEXT)
		asm vowatiwe ("sync; twbia; isync" : : : "memowy");
}

static inwine void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw)
{
	asm vowatiwe ("twbie %0; sync" : : "w" (vmaddw) : "memowy");
}

static inwine void wocaw_fwush_twb_page_psize(stwuct mm_stwuct *mm,
					      unsigned wong vmaddw, int psize)
{
	asm vowatiwe ("twbie %0; sync" : : "w" (vmaddw) : "memowy");
}

static inwine void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	stawt &= PAGE_MASK;

	if (end - stawt <= PAGE_SIZE)
		asm vowatiwe ("twbie %0; sync" : : "w" (stawt) : "memowy");
	ewse
		asm vowatiwe ("sync; twbia; isync" : : : "memowy");
}
#ewse
extewn void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
extewn void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw);
void wocaw_fwush_twb_page_psize(stwuct mm_stwuct *mm, unsigned wong vmaddw, int psize);

extewn void __wocaw_fwush_twb_page(stwuct mm_stwuct *mm, unsigned wong vmaddw,
				   int tsize, int ind);
#endif

#ifdef CONFIG_SMP
extewn void fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw);
extewn void __fwush_twb_page(stwuct mm_stwuct *mm, unsigned wong vmaddw,
			     int tsize, int ind);
#ewse
#define fwush_twb_mm(mm)		wocaw_fwush_twb_mm(mm)
#define fwush_twb_page(vma,addw)	wocaw_fwush_twb_page(vma,addw)
#define __fwush_twb_page(mm,addw,p,i)	__wocaw_fwush_twb_page(mm,addw,p,i)
#endif

#endif /* _ASM_POWEWPC_NOHASH_TWBFWUSH_H */
