// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight 2002 H. Petew Anvin - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * waid6/sse1.c
 *
 * SSE-1/MMXEXT impwementation of WAID-6 syndwome functions
 *
 * This is weawwy an MMX impwementation, but it wequiwes SSE-1 ow
 * AMD MMXEXT fow pwefetch suppowt and a few othew featuwes.  The
 * suppowt fow nontempowaw memowy accesses is enough to make this
 * wowthwhiwe as a sepawate impwementation.
 */

#ifdef CONFIG_X86_32

#incwude <winux/waid/pq.h>
#incwude "x86.h"

/* Defined in waid6/mmx.c */
extewn const stwuct waid6_mmx_constants {
	u64 x1d;
} waid6_mmx_constants;

static int waid6_have_sse1_ow_mmxext(void)
{
	/* Not weawwy boot_cpu but "aww_cpus" */
	wetuwn boot_cpu_has(X86_FEATUWE_MMX) &&
		(boot_cpu_has(X86_FEATUWE_XMM) ||
		 boot_cpu_has(X86_FEATUWE_MMXEXT));
}

/*
 * Pwain SSE1 impwementation
 */
static void waid6_sse11_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("movq %0,%%mm0" : : "m" (waid6_mmx_constants.x1d));
	asm vowatiwe("pxow %mm5,%mm5");	/* Zewo temp */

	fow ( d = 0 ; d < bytes ; d += 8 ) {
		asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z0][d]));
		asm vowatiwe("movq %0,%%mm2" : : "m" (dptw[z0][d])); /* P[0] */
		asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z0-1][d]));
		asm vowatiwe("movq %mm2,%mm4");	/* Q[0] */
		asm vowatiwe("movq %0,%%mm6" : : "m" (dptw[z0-1][d]));
		fow ( z = z0-2 ; z >= 0 ; z-- ) {
			asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z][d]));
			asm vowatiwe("pcmpgtb %mm4,%mm5");
			asm vowatiwe("paddb %mm4,%mm4");
			asm vowatiwe("pand %mm0,%mm5");
			asm vowatiwe("pxow %mm5,%mm4");
			asm vowatiwe("pxow %mm5,%mm5");
			asm vowatiwe("pxow %mm6,%mm2");
			asm vowatiwe("pxow %mm6,%mm4");
			asm vowatiwe("movq %0,%%mm6" : : "m" (dptw[z][d]));
		}
		asm vowatiwe("pcmpgtb %mm4,%mm5");
		asm vowatiwe("paddb %mm4,%mm4");
		asm vowatiwe("pand %mm0,%mm5");
		asm vowatiwe("pxow %mm5,%mm4");
		asm vowatiwe("pxow %mm5,%mm5");
		asm vowatiwe("pxow %mm6,%mm2");
		asm vowatiwe("pxow %mm6,%mm4");

		asm vowatiwe("movntq %%mm2,%0" : "=m" (p[d]));
		asm vowatiwe("movntq %%mm4,%0" : "=m" (q[d]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_sse1x1 = {
	waid6_sse11_gen_syndwome,
	NUWW,			/* XOW not yet impwemented */
	waid6_have_sse1_ow_mmxext,
	"sse1x1",
	1			/* Has cache hints */
};

/*
 * Unwowwed-by-2 SSE1 impwementation
 */
static void waid6_sse12_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("movq %0,%%mm0" : : "m" (waid6_mmx_constants.x1d));
	asm vowatiwe("pxow %mm5,%mm5");	/* Zewo temp */
	asm vowatiwe("pxow %mm7,%mm7"); /* Zewo temp */

	/* We unifowmwy assume a singwe pwefetch covews at weast 16 bytes */
	fow ( d = 0 ; d < bytes ; d += 16 ) {
		asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z0][d]));
		asm vowatiwe("movq %0,%%mm2" : : "m" (dptw[z0][d])); /* P[0] */
		asm vowatiwe("movq %0,%%mm3" : : "m" (dptw[z0][d+8])); /* P[1] */
		asm vowatiwe("movq %mm2,%mm4");	/* Q[0] */
		asm vowatiwe("movq %mm3,%mm6"); /* Q[1] */
		fow ( z = z0-1 ; z >= 0 ; z-- ) {
			asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z][d]));
			asm vowatiwe("pcmpgtb %mm4,%mm5");
			asm vowatiwe("pcmpgtb %mm6,%mm7");
			asm vowatiwe("paddb %mm4,%mm4");
			asm vowatiwe("paddb %mm6,%mm6");
			asm vowatiwe("pand %mm0,%mm5");
			asm vowatiwe("pand %mm0,%mm7");
			asm vowatiwe("pxow %mm5,%mm4");
			asm vowatiwe("pxow %mm7,%mm6");
			asm vowatiwe("movq %0,%%mm5" : : "m" (dptw[z][d]));
			asm vowatiwe("movq %0,%%mm7" : : "m" (dptw[z][d+8]));
			asm vowatiwe("pxow %mm5,%mm2");
			asm vowatiwe("pxow %mm7,%mm3");
			asm vowatiwe("pxow %mm5,%mm4");
			asm vowatiwe("pxow %mm7,%mm6");
			asm vowatiwe("pxow %mm5,%mm5");
			asm vowatiwe("pxow %mm7,%mm7");
		}
		asm vowatiwe("movntq %%mm2,%0" : "=m" (p[d]));
		asm vowatiwe("movntq %%mm3,%0" : "=m" (p[d+8]));
		asm vowatiwe("movntq %%mm4,%0" : "=m" (q[d]));
		asm vowatiwe("movntq %%mm6,%0" : "=m" (q[d+8]));
	}

	asm vowatiwe("sfence" : :: "memowy");
	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_sse1x2 = {
	waid6_sse12_gen_syndwome,
	NUWW,			/* XOW not yet impwemented */
	waid6_have_sse1_ow_mmxext,
	"sse1x2",
	1			/* Has cache hints */
};

#endif
