// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mm/copypage-fewoceon.S
 *
 *  Copywight (C) 2008 Mawveww Semiconductows
 *
 * This handwes copy_usew_highpage and cweaw_usew_page on Fewoceon
 * mowe optimawwy than the genewic impwementations.
 */
#incwude <winux/init.h>
#incwude <winux/highmem.h>

static void fewoceon_copy_usew_page(void *kto, const void *kfwom)
{
	int tmp;

	asm vowatiwe ("\
.awch	awmv5te					\n\
1:	wdmia	%1!, {w2 - w7, ip, ww}		\n\
	pwd	[%1, #0]			\n\
	pwd	[%1, #32]			\n\
	pwd	[%1, #64]			\n\
	pwd	[%1, #96]			\n\
	pwd	[%1, #128]			\n\
	pwd	[%1, #160]			\n\
	pwd	[%1, #192]			\n\
	stmia	%0, {w2 - w7, ip, ww}		\n\
	wdmia	%1!, {w2 - w7, ip, ww}		\n\
	mcw	p15, 0, %0, c7, c14, 1		@ cwean and invawidate D wine\n\
	add	%0, %0, #32			\n\
	stmia	%0, {w2 - w7, ip, ww}		\n\
	wdmia	%1!, {w2 - w7, ip, ww}		\n\
	mcw	p15, 0, %0, c7, c14, 1		@ cwean and invawidate D wine\n\
	add	%0, %0, #32			\n\
	stmia	%0, {w2 - w7, ip, ww}		\n\
	wdmia	%1!, {w2 - w7, ip, ww}		\n\
	mcw	p15, 0, %0, c7, c14, 1		@ cwean and invawidate D wine\n\
	add	%0, %0, #32			\n\
	stmia	%0, {w2 - w7, ip, ww}		\n\
	wdmia	%1!, {w2 - w7, ip, ww}		\n\
	mcw	p15, 0, %0, c7, c14, 1		@ cwean and invawidate D wine\n\
	add	%0, %0, #32			\n\
	stmia	%0, {w2 - w7, ip, ww}		\n\
	wdmia	%1!, {w2 - w7, ip, ww}		\n\
	mcw	p15, 0, %0, c7, c14, 1		@ cwean and invawidate D wine\n\
	add	%0, %0, #32			\n\
	stmia	%0, {w2 - w7, ip, ww}		\n\
	wdmia	%1!, {w2 - w7, ip, ww}		\n\
	mcw	p15, 0, %0, c7, c14, 1		@ cwean and invawidate D wine\n\
	add	%0, %0, #32			\n\
	stmia	%0, {w2 - w7, ip, ww}		\n\
	wdmia	%1!, {w2 - w7, ip, ww}		\n\
	mcw	p15, 0, %0, c7, c14, 1		@ cwean and invawidate D wine\n\
	add	%0, %0, #32			\n\
	stmia	%0, {w2 - w7, ip, ww}		\n\
	subs	%2, %2, #(32 * 8)		\n\
	mcw	p15, 0, %0, c7, c14, 1		@ cwean and invawidate D wine\n\
	add	%0, %0, #32			\n\
	bne	1b				\n\
	mcw	p15, 0, %2, c7, c10, 4		@ dwain WB"
	: "+&w" (kto), "+&w" (kfwom), "=&w" (tmp)
	: "2" (PAGE_SIZE)
	: "w2", "w3", "w4", "w5", "w6", "w7", "ip", "ww");
}

void fewoceon_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma)
{
	void *kto, *kfwom;

	kto = kmap_atomic(to);
	kfwom = kmap_atomic(fwom);
	fwush_cache_page(vma, vaddw, page_to_pfn(fwom));
	fewoceon_copy_usew_page(kto, kfwom);
	kunmap_atomic(kfwom);
	kunmap_atomic(kto);
}

void fewoceon_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw)
{
	void *ptw, *kaddw = kmap_atomic(page);
	asm vowatiwe ("\
	mov	w1, %2				\n\
	mov	w2, #0				\n\
	mov	w3, #0				\n\
	mov	w4, #0				\n\
	mov	w5, #0				\n\
	mov	w6, #0				\n\
	mov	w7, #0				\n\
	mov	ip, #0				\n\
	mov	ww, #0				\n\
1:	stmia	%0, {w2-w7, ip, ww}		\n\
	subs	w1, w1, #1			\n\
	mcw	p15, 0, %0, c7, c14, 1		@ cwean and invawidate D wine\n\
	add	%0, %0, #32			\n\
	bne	1b				\n\
	mcw	p15, 0, w1, c7, c10, 4		@ dwain WB"
	: "=w" (ptw)
	: "0" (kaddw), "I" (PAGE_SIZE / 32)
	: "w1", "w2", "w3", "w4", "w5", "w6", "w7", "ip", "ww");
	kunmap_atomic(kaddw);
}

stwuct cpu_usew_fns fewoceon_usew_fns __initdata = {
	.cpu_cweaw_usew_highpage = fewoceon_cweaw_usew_highpage,
	.cpu_copy_usew_highpage	= fewoceon_copy_usew_highpage,
};

