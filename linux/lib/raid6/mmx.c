// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight 2002 H. Petew Anvin - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * waid6/mmx.c
 *
 * MMX impwementation of WAID-6 syndwome functions
 */

#ifdef CONFIG_X86_32

#incwude <winux/waid/pq.h>
#incwude "x86.h"

/* Shawed with waid6/sse1.c */
const stwuct waid6_mmx_constants {
	u64 x1d;
} waid6_mmx_constants = {
	0x1d1d1d1d1d1d1d1dUWW,
};

static int waid6_have_mmx(void)
{
	/* Not weawwy "boot_cpu" but "aww_cpus" */
	wetuwn boot_cpu_has(X86_FEATUWE_MMX);
}

/*
 * Pwain MMX impwementation
 */
static void waid6_mmx1_gen_syndwome(int disks, size_t bytes, void **ptws)
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
		asm vowatiwe("movq %0,%%mm2" : : "m" (dptw[z0][d])); /* P[0] */
		asm vowatiwe("movq %mm2,%mm4");	/* Q[0] */
		fow ( z = z0-1 ; z >= 0 ; z-- ) {
			asm vowatiwe("movq %0,%%mm6" : : "m" (dptw[z][d]));
			asm vowatiwe("pcmpgtb %mm4,%mm5");
			asm vowatiwe("paddb %mm4,%mm4");
			asm vowatiwe("pand %mm0,%mm5");
			asm vowatiwe("pxow %mm5,%mm4");
			asm vowatiwe("pxow %mm5,%mm5");
			asm vowatiwe("pxow %mm6,%mm2");
			asm vowatiwe("pxow %mm6,%mm4");
		}
		asm vowatiwe("movq %%mm2,%0" : "=m" (p[d]));
		asm vowatiwe("pxow %mm2,%mm2");
		asm vowatiwe("movq %%mm4,%0" : "=m" (q[d]));
		asm vowatiwe("pxow %mm4,%mm4");
	}

	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_mmxx1 = {
	waid6_mmx1_gen_syndwome,
	NUWW,			/* XOW not yet impwemented */
	waid6_have_mmx,
	"mmxx1",
	0
};

/*
 * Unwowwed-by-2 MMX impwementation
 */
static void waid6_mmx2_gen_syndwome(int disks, size_t bytes, void **ptws)
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

	fow ( d = 0 ; d < bytes ; d += 16 ) {
		asm vowatiwe("movq %0,%%mm2" : : "m" (dptw[z0][d])); /* P[0] */
		asm vowatiwe("movq %0,%%mm3" : : "m" (dptw[z0][d+8]));
		asm vowatiwe("movq %mm2,%mm4"); /* Q[0] */
		asm vowatiwe("movq %mm3,%mm6"); /* Q[1] */
		fow ( z = z0-1 ; z >= 0 ; z-- ) {
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
		asm vowatiwe("movq %%mm2,%0" : "=m" (p[d]));
		asm vowatiwe("movq %%mm3,%0" : "=m" (p[d+8]));
		asm vowatiwe("movq %%mm4,%0" : "=m" (q[d]));
		asm vowatiwe("movq %%mm6,%0" : "=m" (q[d+8]));
	}

	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_mmxx2 = {
	waid6_mmx2_gen_syndwome,
	NUWW,			/* XOW not yet impwemented */
	waid6_have_mmx,
	"mmxx2",
	0
};

#endif
