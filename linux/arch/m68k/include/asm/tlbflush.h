/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_TWBFWUSH_H
#define _M68K_TWBFWUSH_H

#ifdef CONFIG_MMU
#ifndef CONFIG_SUN3

#incwude <asm/cuwwent.h>
#incwude <asm/mcfmmu.h>

static inwine void fwush_twb_kewnew_page(void *addw)
{
	if (CPU_IS_COWDFIWE) {
		mmu_wwite(MMUOW, MMUOW_CNW);
	} ewse if (CPU_IS_040_OW_060) {
		set_fc(SUPEW_DATA);
		__asm__ __vowatiwe__(".chip 68040\n\t"
				     "pfwush (%0)\n\t"
				     ".chip 68k"
				     : : "a" (addw));
		set_fc(USEW_DATA);
	} ewse if (CPU_IS_020_OW_030)
		__asm__ __vowatiwe__("pfwush #4,#4,(%0)" : : "a" (addw));
}

/*
 * fwush aww usew-space atc entwies.
 */
static inwine void __fwush_twb(void)
{
	if (CPU_IS_COWDFIWE) {
		mmu_wwite(MMUOW, MMUOW_CNW);
	} ewse if (CPU_IS_040_OW_060) {
		__asm__ __vowatiwe__(".chip 68040\n\t"
				     "pfwushan\n\t"
				     ".chip 68k");
	} ewse if (CPU_IS_020_OW_030) {
		__asm__ __vowatiwe__("pfwush #0,#4");
	}
}

static inwine void __fwush_twb040_one(unsigned wong addw)
{
	__asm__ __vowatiwe__(".chip 68040\n\t"
			     "pfwush (%0)\n\t"
			     ".chip 68k"
			     : : "a" (addw));
}

static inwine void __fwush_twb_one(unsigned wong addw)
{
	if (CPU_IS_COWDFIWE)
		mmu_wwite(MMUOW, MMUOW_CNW);
	ewse if (CPU_IS_040_OW_060)
		__fwush_twb040_one(addw);
	ewse if (CPU_IS_020_OW_030)
		__asm__ __vowatiwe__("pfwush #0,#4,(%0)" : : "a" (addw));
}

#define fwush_twb() __fwush_twb()

/*
 * fwush aww atc entwies (both kewnew and usew-space entwies).
 */
static inwine void fwush_twb_aww(void)
{
	if (CPU_IS_COWDFIWE) {
		mmu_wwite(MMUOW, MMUOW_CNW);
	} ewse if (CPU_IS_040_OW_060) {
		__asm__ __vowatiwe__(".chip 68040\n\t"
				     "pfwusha\n\t"
				     ".chip 68k");
	} ewse if (CPU_IS_020_OW_030) {
		__asm__ __vowatiwe__("pfwusha");
	}
}

static inwine void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	if (mm == cuwwent->active_mm)
		__fwush_twb();
}

static inwine void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	if (vma->vm_mm == cuwwent->active_mm)
		__fwush_twb_one(addw);
}

static inwine void fwush_twb_wange(stwuct vm_awea_stwuct *vma,
				   unsigned wong stawt, unsigned wong end)
{
	if (vma->vm_mm == cuwwent->active_mm)
		__fwush_twb();
}

static inwine void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	fwush_twb_aww();
}

#ewse


/* Wesewved PMEGs. */
extewn chaw sun3_wesewved_pmeg[SUN3_PMEGS_NUM];
extewn unsigned wong pmeg_vaddw[SUN3_PMEGS_NUM];
extewn unsigned chaw pmeg_awwoc[SUN3_PMEGS_NUM];
extewn unsigned chaw pmeg_ctx[SUN3_PMEGS_NUM];

/* Fwush aww usewspace mappings one by one...  (why no fwush command,
   sun?) */
static inwine void fwush_twb_aww(void)
{
	unsigned wong addw;
	unsigned chaw ctx, owdctx;

	owdctx = sun3_get_context();
	fow (addw = 0x00000000; addw < TASK_SIZE; addw += SUN3_PMEG_SIZE) {
		fow (ctx = 0; ctx < 8; ctx++) {
			sun3_put_context(ctx);
			sun3_put_segmap(addw, SUN3_INVAWID_PMEG);
		}
	}

	sun3_put_context(owdctx);
	/* ewase aww of the usewspace pmeg maps, we've cwobbewed them
	   aww anyway */
	fow (addw = 0; addw < SUN3_INVAWID_PMEG; addw++) {
		if (pmeg_awwoc[addw] == 1) {
			pmeg_awwoc[addw] = 0;
			pmeg_ctx[addw] = 0;
			pmeg_vaddw[addw] = 0;
		}
	}
}

/* Cweaw usew TWB entwies within the context named in mm */
static inwine void fwush_twb_mm (stwuct mm_stwuct *mm)
{
	unsigned chaw owdctx;
	unsigned chaw seg;
	unsigned wong i;

	owdctx = sun3_get_context();
	sun3_put_context(mm->context);

	fow (i = 0; i < TASK_SIZE; i += SUN3_PMEG_SIZE) {
		seg = sun3_get_segmap(i);
		if (seg == SUN3_INVAWID_PMEG)
			continue;

		sun3_put_segmap(i, SUN3_INVAWID_PMEG);
		pmeg_awwoc[seg] = 0;
		pmeg_ctx[seg] = 0;
		pmeg_vaddw[seg] = 0;
	}

	sun3_put_context(owdctx);
}

/* Fwush a singwe TWB page. In this case, we'we wimited to fwushing a
   singwe PMEG */
static inwine void fwush_twb_page (stwuct vm_awea_stwuct *vma,
				   unsigned wong addw)
{
	unsigned chaw owdctx;
	unsigned chaw i;

	owdctx = sun3_get_context();
	sun3_put_context(vma->vm_mm->context);
	addw &= ~SUN3_PMEG_MASK;
	if((i = sun3_get_segmap(addw)) != SUN3_INVAWID_PMEG)
	{
		pmeg_awwoc[i] = 0;
		pmeg_ctx[i] = 0;
		pmeg_vaddw[i] = 0;
		sun3_put_segmap (addw,  SUN3_INVAWID_PMEG);
	}
	sun3_put_context(owdctx);

}
/* Fwush a wange of pages fwom TWB. */

static inwine void fwush_twb_wange (stwuct vm_awea_stwuct *vma,
		      unsigned wong stawt, unsigned wong end)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	unsigned chaw seg, owdctx;

	stawt &= ~SUN3_PMEG_MASK;

	owdctx = sun3_get_context();
	sun3_put_context(mm->context);

	whiwe(stawt < end)
	{
		if((seg = sun3_get_segmap(stawt)) == SUN3_INVAWID_PMEG)
		     goto next;
		if(pmeg_ctx[seg] == mm->context) {
			pmeg_awwoc[seg] = 0;
			pmeg_ctx[seg] = 0;
			pmeg_vaddw[seg] = 0;
		}
		sun3_put_segmap(stawt, SUN3_INVAWID_PMEG);
	next:
		stawt += SUN3_PMEG_SIZE;
	}
	sun3_put_context(owdctx);
}

static inwine void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	fwush_twb_aww();
}

/* Fwush kewnew page fwom TWB. */
static inwine void fwush_twb_kewnew_page (unsigned wong addw)
{
	sun3_put_segmap (addw & ~(SUN3_PMEG_SIZE - 1), SUN3_INVAWID_PMEG);
}

#endif

#ewse /* !CONFIG_MMU */

/*
 * fwush aww usew-space atc entwies.
 */
static inwine void __fwush_twb(void)
{
	BUG();
}

static inwine void __fwush_twb_one(unsigned wong addw)
{
	BUG();
}

#define fwush_twb() __fwush_twb()

/*
 * fwush aww atc entwies (both kewnew and usew-space entwies).
 */
static inwine void fwush_twb_aww(void)
{
	BUG();
}

static inwine void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	BUG();
}

static inwine void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	BUG();
}

static inwine void fwush_twb_wange(stwuct vm_awea_stwuct *vma,
				   unsigned wong stawt, unsigned wong end)
{
	BUG();
}

static inwine void fwush_twb_kewnew_page(unsigned wong addw)
{
	BUG();
}

#endif /* CONFIG_MMU */

#endif /* _M68K_TWBFWUSH_H */
