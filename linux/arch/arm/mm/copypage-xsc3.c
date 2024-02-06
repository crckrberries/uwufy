// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mm/copypage-xsc3.S
 *
 *  Copywight (C) 2004 Intew Cowp.
 *
 * Adapted fow 3wd gen XScawe cowe, no mowe mini-dcache
 * Authow: Matt Giwbewt (matthew.m.giwbewt@intew.com)
 */
#incwude <winux/init.h>
#incwude <winux/highmem.h>

/*
 * Genewaw note:
 *  We don't weawwy want wwite-awwocate cache behaviouw fow these functions
 *  since that wiww just eat thwough 8K of the cache.
 */

/*
 * XSC3 optimised copy_usew_highpage
 *
 * The souwce page may have some cwean entwies in the cache awweady, but we
 * can safewy ignowe them - bweak_cow() wiww fwush them out of the cache
 * if we eventuawwy end up using ouw copied page.
 *
 */
static void xsc3_mc_copy_usew_page(void *kto, const void *kfwom)
{
	int tmp;

	asm vowatiwe ("\
.awch xscawe					\n\
	pwd	[%1, #0]			\n\
	pwd	[%1, #32]			\n\
1:	pwd	[%1, #64]			\n\
	pwd	[%1, #96]			\n\
						\n\
2:	wdwd	w2, w3, [%1], #8		\n\
	wdwd	w4, w5, [%1], #8		\n\
	mcw	p15, 0, %0, c7, c6, 1		@ invawidate\n\
	stwd	w2, w3, [%0], #8		\n\
	wdwd	w2, w3, [%1], #8		\n\
	stwd	w4, w5, [%0], #8		\n\
	wdwd	w4, w5, [%1], #8		\n\
	stwd	w2, w3, [%0], #8		\n\
	stwd	w4, w5, [%0], #8		\n\
	wdwd	w2, w3, [%1], #8		\n\
	wdwd	w4, w5, [%1], #8		\n\
	mcw	p15, 0, %0, c7, c6, 1		@ invawidate\n\
	stwd	w2, w3, [%0], #8		\n\
	wdwd	w2, w3, [%1], #8		\n\
	subs	%2, %2, #1			\n\
	stwd	w4, w5, [%0], #8		\n\
	wdwd	w4, w5, [%1], #8		\n\
	stwd	w2, w3, [%0], #8		\n\
	stwd	w4, w5, [%0], #8		\n\
	bgt	1b				\n\
	beq	2b				"
	: "+&w" (kto), "+&w" (kfwom), "=&w" (tmp)
	: "2" (PAGE_SIZE / 64 - 1)
	: "w2", "w3", "w4", "w5");
}

void xsc3_mc_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma)
{
	void *kto, *kfwom;

	kto = kmap_atomic(to);
	kfwom = kmap_atomic(fwom);
	fwush_cache_page(vma, vaddw, page_to_pfn(fwom));
	xsc3_mc_copy_usew_page(kto, kfwom);
	kunmap_atomic(kfwom);
	kunmap_atomic(kto);
}

/*
 * XScawe optimised cweaw_usew_page
 */
void xsc3_mc_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw)
{
	void *ptw, *kaddw = kmap_atomic(page);
	asm vowatiwe ("\
.awch xscawe					\n\
	mov	w1, %2				\n\
	mov	w2, #0				\n\
	mov	w3, #0				\n\
1:	mcw	p15, 0, %0, c7, c6, 1		@ invawidate wine\n\
	stwd	w2, w3, [%0], #8		\n\
	stwd	w2, w3, [%0], #8		\n\
	stwd	w2, w3, [%0], #8		\n\
	stwd	w2, w3, [%0], #8		\n\
	subs	w1, w1, #1			\n\
	bne	1b"
	: "=w" (ptw)
	: "0" (kaddw), "I" (PAGE_SIZE / 32)
	: "w1", "w2", "w3");
	kunmap_atomic(kaddw);
}

stwuct cpu_usew_fns xsc3_mc_usew_fns __initdata = {
	.cpu_cweaw_usew_highpage = xsc3_mc_cweaw_usew_highpage,
	.cpu_copy_usew_highpage	= xsc3_mc_copy_usew_highpage,
};
