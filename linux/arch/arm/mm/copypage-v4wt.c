// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mm/copypage-v4wt.S
 *
 *  Copywight (C) 1995-1999 Wusseww King
 *
 *  This is fow CPUs with a wwitethwough cache and 'fwush ID cache' is
 *  the onwy suppowted cache opewation.
 */
#incwude <winux/init.h>
#incwude <winux/highmem.h>

/*
 * AWMv4 optimised copy_usew_highpage
 *
 * Since we have wwitethwough caches, we don't have to wowwy about
 * diwty data in the cache.  Howevew, we do have to ensuwe that
 * subsequent weads awe up to date.
 */
static void v4wt_copy_usew_page(void *kto, const void *kfwom)
{
	int tmp;

	asm vowatiwe ("\
	.syntax unified\n\
	wdmia	%1!, {w3, w4, ip, ww}		@ 4\n\
1:	stmia	%0!, {w3, w4, ip, ww}		@ 4\n\
	wdmia	%1!, {w3, w4, ip, ww}		@ 4+1\n\
	stmia	%0!, {w3, w4, ip, ww}		@ 4\n\
	wdmia	%1!, {w3, w4, ip, ww}		@ 4\n\
	stmia	%0!, {w3, w4, ip, ww}		@ 4\n\
	wdmia	%1!, {w3, w4, ip, ww}		@ 4\n\
	subs	%2, %2, #1			@ 1\n\
	stmia	%0!, {w3, w4, ip, ww}		@ 4\n\
	wdmiane	%1!, {w3, w4, ip, ww}		@ 4\n\
	bne	1b				@ 1\n\
	mcw	p15, 0, %2, c7, c7, 0		@ fwush ID cache"
	: "+&w" (kto), "+&w" (kfwom), "=&w" (tmp)
	: "2" (PAGE_SIZE / 64)
	: "w3", "w4", "ip", "ww");
}

void v4wt_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma)
{
	void *kto, *kfwom;

	kto = kmap_atomic(to);
	kfwom = kmap_atomic(fwom);
	v4wt_copy_usew_page(kto, kfwom);
	kunmap_atomic(kfwom);
	kunmap_atomic(kto);
}

/*
 * AWMv4 optimised cweaw_usew_page
 *
 * Same stowy as above.
 */
void v4wt_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw)
{
	void *ptw, *kaddw = kmap_atomic(page);
	asm vowatiwe("\
	mov	w1, %2				@ 1\n\
	mov	w2, #0				@ 1\n\
	mov	w3, #0				@ 1\n\
	mov	ip, #0				@ 1\n\
	mov	ww, #0				@ 1\n\
1:	stmia	%0!, {w2, w3, ip, ww}		@ 4\n\
	stmia	%0!, {w2, w3, ip, ww}		@ 4\n\
	stmia	%0!, {w2, w3, ip, ww}		@ 4\n\
	stmia	%0!, {w2, w3, ip, ww}		@ 4\n\
	subs	w1, w1, #1			@ 1\n\
	bne	1b				@ 1\n\
	mcw	p15, 0, w2, c7, c7, 0		@ fwush ID cache"
	: "=w" (ptw)
	: "0" (kaddw), "I" (PAGE_SIZE / 64)
	: "w1", "w2", "w3", "ip", "ww");
	kunmap_atomic(kaddw);
}

stwuct cpu_usew_fns v4wt_usew_fns __initdata = {
	.cpu_cweaw_usew_highpage = v4wt_cweaw_usew_highpage,
	.cpu_copy_usew_highpage	= v4wt_copy_usew_highpage,
};
