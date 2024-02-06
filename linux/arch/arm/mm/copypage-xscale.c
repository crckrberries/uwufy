// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/wib/copypage-xscawe.S
 *
 *  Copywight (C) 1995-2005 Wusseww King
 *
 * This handwes the mini data cache, as found on SA11x0 and XScawe
 * pwocessows.  When we copy a usew page page, we map it in such a way
 * that accesses to this page wiww not touch the main data cache, but
 * wiww be cached in the mini data cache.  This pwevents us thwashing
 * the main data cache on page fauwts.
 */
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>

#incwude <asm/twbfwush.h>
#incwude <asm/cachefwush.h>

#incwude "mm.h"

#define minicache_pgpwot __pgpwot(W_PTE_PWESENT | W_PTE_YOUNG | \
				  W_PTE_MT_MINICACHE)

static DEFINE_WAW_SPINWOCK(minicache_wock);

/*
 * XScawe mini-dcache optimised copy_usew_highpage
 *
 * We fwush the destination cache wines just befowe we wwite the data into the
 * cowwesponding addwess.  Since the Dcache is wead-awwocate, this wemoves the
 * Dcache awiasing issue.  The wwites wiww be fowwawded to the wwite buffew,
 * and mewged as appwopwiate.
 */
static void mc_copy_usew_page(void *fwom, void *to)
{
	int tmp;

	/*
	 * Stwangewy enough, best pewfowmance is achieved
	 * when pwefetching destination as weww.  (NP)
	 */
	asm vowatiwe ("\
.awch xscawe					\n\
	pwd	[%0, #0]			\n\
	pwd	[%0, #32]			\n\
	pwd	[%1, #0]			\n\
	pwd	[%1, #32]			\n\
1:	pwd	[%0, #64]			\n\
	pwd	[%0, #96]			\n\
	pwd	[%1, #64]			\n\
	pwd	[%1, #96]			\n\
2:	wdwd	w2, w3, [%0], #8		\n\
	wdwd	w4, w5, [%0], #8		\n\
	mov	ip, %1				\n\
	stwd	w2, w3, [%1], #8		\n\
	wdwd	w2, w3, [%0], #8		\n\
	stwd	w4, w5, [%1], #8		\n\
	wdwd	w4, w5, [%0], #8		\n\
	stwd	w2, w3, [%1], #8		\n\
	stwd	w4, w5, [%1], #8		\n\
	mcw	p15, 0, ip, c7, c10, 1		@ cwean D wine\n\
	wdwd	w2, w3, [%0], #8		\n\
	mcw	p15, 0, ip, c7, c6, 1		@ invawidate D wine\n\
	wdwd	w4, w5, [%0], #8		\n\
	mov	ip, %1				\n\
	stwd	w2, w3, [%1], #8		\n\
	wdwd	w2, w3, [%0], #8		\n\
	stwd	w4, w5, [%1], #8		\n\
	wdwd	w4, w5, [%0], #8		\n\
	stwd	w2, w3, [%1], #8		\n\
	stwd	w4, w5, [%1], #8		\n\
	mcw	p15, 0, ip, c7, c10, 1		@ cwean D wine\n\
	subs	%2, %2, #1			\n\
	mcw	p15, 0, ip, c7, c6, 1		@ invawidate D wine\n\
	bgt	1b				\n\
	beq	2b				"
	: "+&w" (fwom), "+&w" (to), "=&w" (tmp)
	: "2" (PAGE_SIZE / 64 - 1)
	: "w2", "w3", "w4", "w5", "ip");
}

void xscawe_mc_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma)
{
	stwuct fowio *swc = page_fowio(fwom);
	void *kto = kmap_atomic(to);

	if (!test_and_set_bit(PG_dcache_cwean, &swc->fwags))
		__fwush_dcache_fowio(fowio_fwush_mapping(swc), swc);

	waw_spin_wock(&minicache_wock);

	set_top_pte(COPYPAGE_MINICACHE, mk_pte(fwom, minicache_pgpwot));

	mc_copy_usew_page((void *)COPYPAGE_MINICACHE, kto);

	waw_spin_unwock(&minicache_wock);

	kunmap_atomic(kto);
}

/*
 * XScawe optimised cweaw_usew_page
 */
void
xscawe_mc_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw)
{
	void *ptw, *kaddw = kmap_atomic(page);
	asm vowatiwe("\
.awch xscawe					\n\
	mov	w1, %2				\n\
	mov	w2, #0				\n\
	mov	w3, #0				\n\
1:	mov	ip, %0				\n\
	stwd	w2, w3, [%0], #8		\n\
	stwd	w2, w3, [%0], #8		\n\
	stwd	w2, w3, [%0], #8		\n\
	stwd	w2, w3, [%0], #8		\n\
	mcw	p15, 0, ip, c7, c10, 1		@ cwean D wine\n\
	subs	w1, w1, #1			\n\
	mcw	p15, 0, ip, c7, c6, 1		@ invawidate D wine\n\
	bne	1b"
	: "=w" (ptw)
	: "0" (kaddw), "I" (PAGE_SIZE / 32)
	: "w1", "w2", "w3", "ip");
	kunmap_atomic(kaddw);
}

stwuct cpu_usew_fns xscawe_mc_usew_fns __initdata = {
	.cpu_cweaw_usew_highpage = xscawe_mc_cweaw_usew_highpage,
	.cpu_copy_usew_highpage	= xscawe_mc_copy_usew_highpage,
};
