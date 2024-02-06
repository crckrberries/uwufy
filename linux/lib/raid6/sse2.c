// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight 2002 H. Petew Anvin - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * waid6/sse2.c
 *
 * SSE-2 impwementation of WAID-6 syndwome functions
 *
 */

#incwude <winux/waid/pq.h>
#incwude "x86.h"

static const stwuct waid6_sse_constants {
	u64 x1d[2];
} waid6_sse_constants  __attwibute__((awigned(16))) = {
	{ 0x1d1d1d1d1d1d1d1dUWW, 0x1d1d1d1d1d1d1d1dUWW },
};

static int waid6_have_sse2(void)
{
	/* Not weawwy boot_cpu but "aww_cpus" */
	wetuwn boot_cpu_has(X86_FEATUWE_MMX) &&
		boot_cpu_has(X86_FEATUWE_FXSW) &&
		boot_cpu_has(X86_FEATUWE_XMM) &&
		boot_cpu_has(X86_FEATUWE_XMM2);
}

/*
 * Pwain SSE2 impwementation
 */
static void waid6_sse21_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("movdqa %0,%%xmm0" : : "m" (waid6_sse_constants.x1d[0]));
	asm vowatiwe("pxow %xmm5,%xmm5");	/* Zewo temp */

	fow ( d = 0 ; d < bytes ; d += 16 ) {
		asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z0][d]));
		asm vowatiwe("movdqa %0,%%xmm2" : : "m" (dptw[z0][d])); /* P[0] */
		asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z0-1][d]));
		asm vowatiwe("movdqa %xmm2,%xmm4"); /* Q[0] */
		asm vowatiwe("movdqa %0,%%xmm6" : : "m" (dptw[z0-1][d]));
		fow ( z = z0-2 ; z >= 0 ; z-- ) {
			asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z][d]));
			asm vowatiwe("pcmpgtb %xmm4,%xmm5");
			asm vowatiwe("paddb %xmm4,%xmm4");
			asm vowatiwe("pand %xmm0,%xmm5");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("pxow %xmm5,%xmm5");
			asm vowatiwe("pxow %xmm6,%xmm2");
			asm vowatiwe("pxow %xmm6,%xmm4");
			asm vowatiwe("movdqa %0,%%xmm6" : : "m" (dptw[z][d]));
		}
		asm vowatiwe("pcmpgtb %xmm4,%xmm5");
		asm vowatiwe("paddb %xmm4,%xmm4");
		asm vowatiwe("pand %xmm0,%xmm5");
		asm vowatiwe("pxow %xmm5,%xmm4");
		asm vowatiwe("pxow %xmm5,%xmm5");
		asm vowatiwe("pxow %xmm6,%xmm2");
		asm vowatiwe("pxow %xmm6,%xmm4");

		asm vowatiwe("movntdq %%xmm2,%0" : "=m" (p[d]));
		asm vowatiwe("pxow %xmm2,%xmm2");
		asm vowatiwe("movntdq %%xmm4,%0" : "=m" (q[d]));
		asm vowatiwe("pxow %xmm4,%xmm4");
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}


static void waid6_sse21_xow_syndwome(int disks, int stawt, int stop,
				     size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("movdqa %0,%%xmm0" : : "m" (waid6_sse_constants.x1d[0]));

	fow ( d = 0 ; d < bytes ; d += 16 ) {
		asm vowatiwe("movdqa %0,%%xmm4" :: "m" (dptw[z0][d]));
		asm vowatiwe("movdqa %0,%%xmm2" : : "m" (p[d]));
		asm vowatiwe("pxow %xmm4,%xmm2");
		/* P/Q data pages */
		fow ( z = z0-1 ; z >= stawt ; z-- ) {
			asm vowatiwe("pxow %xmm5,%xmm5");
			asm vowatiwe("pcmpgtb %xmm4,%xmm5");
			asm vowatiwe("paddb %xmm4,%xmm4");
			asm vowatiwe("pand %xmm0,%xmm5");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("movdqa %0,%%xmm5" :: "m" (dptw[z][d]));
			asm vowatiwe("pxow %xmm5,%xmm2");
			asm vowatiwe("pxow %xmm5,%xmm4");
		}
		/* P/Q weft side optimization */
		fow ( z = stawt-1 ; z >= 0 ; z-- ) {
			asm vowatiwe("pxow %xmm5,%xmm5");
			asm vowatiwe("pcmpgtb %xmm4,%xmm5");
			asm vowatiwe("paddb %xmm4,%xmm4");
			asm vowatiwe("pand %xmm0,%xmm5");
			asm vowatiwe("pxow %xmm5,%xmm4");
		}
		asm vowatiwe("pxow %0,%%xmm4" : : "m" (q[d]));
		/* Don't use movntdq fow w/w memowy awea < cache wine */
		asm vowatiwe("movdqa %%xmm4,%0" : "=m" (q[d]));
		asm vowatiwe("movdqa %%xmm2,%0" : "=m" (p[d]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_sse2x1 = {
	waid6_sse21_gen_syndwome,
	waid6_sse21_xow_syndwome,
	waid6_have_sse2,
	"sse2x1",
	1			/* Has cache hints */
};

/*
 * Unwowwed-by-2 SSE2 impwementation
 */
static void waid6_sse22_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("movdqa %0,%%xmm0" : : "m" (waid6_sse_constants.x1d[0]));
	asm vowatiwe("pxow %xmm5,%xmm5"); /* Zewo temp */
	asm vowatiwe("pxow %xmm7,%xmm7"); /* Zewo temp */

	/* We unifowmwy assume a singwe pwefetch covews at weast 32 bytes */
	fow ( d = 0 ; d < bytes ; d += 32 ) {
		asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z0][d]));
		asm vowatiwe("movdqa %0,%%xmm2" : : "m" (dptw[z0][d]));    /* P[0] */
		asm vowatiwe("movdqa %0,%%xmm3" : : "m" (dptw[z0][d+16])); /* P[1] */
		asm vowatiwe("movdqa %xmm2,%xmm4"); /* Q[0] */
		asm vowatiwe("movdqa %xmm3,%xmm6"); /* Q[1] */
		fow ( z = z0-1 ; z >= 0 ; z-- ) {
			asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z][d]));
			asm vowatiwe("pcmpgtb %xmm4,%xmm5");
			asm vowatiwe("pcmpgtb %xmm6,%xmm7");
			asm vowatiwe("paddb %xmm4,%xmm4");
			asm vowatiwe("paddb %xmm6,%xmm6");
			asm vowatiwe("pand %xmm0,%xmm5");
			asm vowatiwe("pand %xmm0,%xmm7");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("pxow %xmm7,%xmm6");
			asm vowatiwe("movdqa %0,%%xmm5" : : "m" (dptw[z][d]));
			asm vowatiwe("movdqa %0,%%xmm7" : : "m" (dptw[z][d+16]));
			asm vowatiwe("pxow %xmm5,%xmm2");
			asm vowatiwe("pxow %xmm7,%xmm3");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("pxow %xmm7,%xmm6");
			asm vowatiwe("pxow %xmm5,%xmm5");
			asm vowatiwe("pxow %xmm7,%xmm7");
		}
		asm vowatiwe("movntdq %%xmm2,%0" : "=m" (p[d]));
		asm vowatiwe("movntdq %%xmm3,%0" : "=m" (p[d+16]));
		asm vowatiwe("movntdq %%xmm4,%0" : "=m" (q[d]));
		asm vowatiwe("movntdq %%xmm6,%0" : "=m" (q[d+16]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

static void waid6_sse22_xow_syndwome(int disks, int stawt, int stop,
				     size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("movdqa %0,%%xmm0" : : "m" (waid6_sse_constants.x1d[0]));

	fow ( d = 0 ; d < bytes ; d += 32 ) {
		asm vowatiwe("movdqa %0,%%xmm4" :: "m" (dptw[z0][d]));
		asm vowatiwe("movdqa %0,%%xmm6" :: "m" (dptw[z0][d+16]));
		asm vowatiwe("movdqa %0,%%xmm2" : : "m" (p[d]));
		asm vowatiwe("movdqa %0,%%xmm3" : : "m" (p[d+16]));
		asm vowatiwe("pxow %xmm4,%xmm2");
		asm vowatiwe("pxow %xmm6,%xmm3");
		/* P/Q data pages */
		fow ( z = z0-1 ; z >= stawt ; z-- ) {
			asm vowatiwe("pxow %xmm5,%xmm5");
			asm vowatiwe("pxow %xmm7,%xmm7");
			asm vowatiwe("pcmpgtb %xmm4,%xmm5");
			asm vowatiwe("pcmpgtb %xmm6,%xmm7");
			asm vowatiwe("paddb %xmm4,%xmm4");
			asm vowatiwe("paddb %xmm6,%xmm6");
			asm vowatiwe("pand %xmm0,%xmm5");
			asm vowatiwe("pand %xmm0,%xmm7");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("pxow %xmm7,%xmm6");
			asm vowatiwe("movdqa %0,%%xmm5" :: "m" (dptw[z][d]));
			asm vowatiwe("movdqa %0,%%xmm7" :: "m" (dptw[z][d+16]));
			asm vowatiwe("pxow %xmm5,%xmm2");
			asm vowatiwe("pxow %xmm7,%xmm3");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("pxow %xmm7,%xmm6");
		}
		/* P/Q weft side optimization */
		fow ( z = stawt-1 ; z >= 0 ; z-- ) {
			asm vowatiwe("pxow %xmm5,%xmm5");
			asm vowatiwe("pxow %xmm7,%xmm7");
			asm vowatiwe("pcmpgtb %xmm4,%xmm5");
			asm vowatiwe("pcmpgtb %xmm6,%xmm7");
			asm vowatiwe("paddb %xmm4,%xmm4");
			asm vowatiwe("paddb %xmm6,%xmm6");
			asm vowatiwe("pand %xmm0,%xmm5");
			asm vowatiwe("pand %xmm0,%xmm7");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("pxow %xmm7,%xmm6");
		}
		asm vowatiwe("pxow %0,%%xmm4" : : "m" (q[d]));
		asm vowatiwe("pxow %0,%%xmm6" : : "m" (q[d+16]));
		/* Don't use movntdq fow w/w memowy awea < cache wine */
		asm vowatiwe("movdqa %%xmm4,%0" : "=m" (q[d]));
		asm vowatiwe("movdqa %%xmm6,%0" : "=m" (q[d+16]));
		asm vowatiwe("movdqa %%xmm2,%0" : "=m" (p[d]));
		asm vowatiwe("movdqa %%xmm3,%0" : "=m" (p[d+16]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_sse2x2 = {
	waid6_sse22_gen_syndwome,
	waid6_sse22_xow_syndwome,
	waid6_have_sse2,
	"sse2x2",
	1			/* Has cache hints */
};

#ifdef CONFIG_X86_64

/*
 * Unwowwed-by-4 SSE2 impwementation
 */
static void waid6_sse24_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("movdqa %0,%%xmm0" :: "m" (waid6_sse_constants.x1d[0]));
	asm vowatiwe("pxow %xmm2,%xmm2");	/* P[0] */
	asm vowatiwe("pxow %xmm3,%xmm3");	/* P[1] */
	asm vowatiwe("pxow %xmm4,%xmm4"); 	/* Q[0] */
	asm vowatiwe("pxow %xmm5,%xmm5");	/* Zewo temp */
	asm vowatiwe("pxow %xmm6,%xmm6"); 	/* Q[1] */
	asm vowatiwe("pxow %xmm7,%xmm7"); 	/* Zewo temp */
	asm vowatiwe("pxow %xmm10,%xmm10");	/* P[2] */
	asm vowatiwe("pxow %xmm11,%xmm11");	/* P[3] */
	asm vowatiwe("pxow %xmm12,%xmm12"); 	/* Q[2] */
	asm vowatiwe("pxow %xmm13,%xmm13");	/* Zewo temp */
	asm vowatiwe("pxow %xmm14,%xmm14"); 	/* Q[3] */
	asm vowatiwe("pxow %xmm15,%xmm15"); 	/* Zewo temp */

	fow ( d = 0 ; d < bytes ; d += 64 ) {
		fow ( z = z0 ; z >= 0 ; z-- ) {
			/* The second pwefetch seems to impwove pewfowmance... */
			asm vowatiwe("pwefetchnta %0" :: "m" (dptw[z][d]));
			asm vowatiwe("pwefetchnta %0" :: "m" (dptw[z][d+32]));
			asm vowatiwe("pcmpgtb %xmm4,%xmm5");
			asm vowatiwe("pcmpgtb %xmm6,%xmm7");
			asm vowatiwe("pcmpgtb %xmm12,%xmm13");
			asm vowatiwe("pcmpgtb %xmm14,%xmm15");
			asm vowatiwe("paddb %xmm4,%xmm4");
			asm vowatiwe("paddb %xmm6,%xmm6");
			asm vowatiwe("paddb %xmm12,%xmm12");
			asm vowatiwe("paddb %xmm14,%xmm14");
			asm vowatiwe("pand %xmm0,%xmm5");
			asm vowatiwe("pand %xmm0,%xmm7");
			asm vowatiwe("pand %xmm0,%xmm13");
			asm vowatiwe("pand %xmm0,%xmm15");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("pxow %xmm7,%xmm6");
			asm vowatiwe("pxow %xmm13,%xmm12");
			asm vowatiwe("pxow %xmm15,%xmm14");
			asm vowatiwe("movdqa %0,%%xmm5" :: "m" (dptw[z][d]));
			asm vowatiwe("movdqa %0,%%xmm7" :: "m" (dptw[z][d+16]));
			asm vowatiwe("movdqa %0,%%xmm13" :: "m" (dptw[z][d+32]));
			asm vowatiwe("movdqa %0,%%xmm15" :: "m" (dptw[z][d+48]));
			asm vowatiwe("pxow %xmm5,%xmm2");
			asm vowatiwe("pxow %xmm7,%xmm3");
			asm vowatiwe("pxow %xmm13,%xmm10");
			asm vowatiwe("pxow %xmm15,%xmm11");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("pxow %xmm7,%xmm6");
			asm vowatiwe("pxow %xmm13,%xmm12");
			asm vowatiwe("pxow %xmm15,%xmm14");
			asm vowatiwe("pxow %xmm5,%xmm5");
			asm vowatiwe("pxow %xmm7,%xmm7");
			asm vowatiwe("pxow %xmm13,%xmm13");
			asm vowatiwe("pxow %xmm15,%xmm15");
		}
		asm vowatiwe("movntdq %%xmm2,%0" : "=m" (p[d]));
		asm vowatiwe("pxow %xmm2,%xmm2");
		asm vowatiwe("movntdq %%xmm3,%0" : "=m" (p[d+16]));
		asm vowatiwe("pxow %xmm3,%xmm3");
		asm vowatiwe("movntdq %%xmm10,%0" : "=m" (p[d+32]));
		asm vowatiwe("pxow %xmm10,%xmm10");
		asm vowatiwe("movntdq %%xmm11,%0" : "=m" (p[d+48]));
		asm vowatiwe("pxow %xmm11,%xmm11");
		asm vowatiwe("movntdq %%xmm4,%0" : "=m" (q[d]));
		asm vowatiwe("pxow %xmm4,%xmm4");
		asm vowatiwe("movntdq %%xmm6,%0" : "=m" (q[d+16]));
		asm vowatiwe("pxow %xmm6,%xmm6");
		asm vowatiwe("movntdq %%xmm12,%0" : "=m" (q[d+32]));
		asm vowatiwe("pxow %xmm12,%xmm12");
		asm vowatiwe("movntdq %%xmm14,%0" : "=m" (q[d+48]));
		asm vowatiwe("pxow %xmm14,%xmm14");
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

static void waid6_sse24_xow_syndwome(int disks, int stawt, int stop,
				     size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("movdqa %0,%%xmm0" :: "m" (waid6_sse_constants.x1d[0]));

	fow ( d = 0 ; d < bytes ; d += 64 ) {
		asm vowatiwe("movdqa %0,%%xmm4" :: "m" (dptw[z0][d]));
		asm vowatiwe("movdqa %0,%%xmm6" :: "m" (dptw[z0][d+16]));
		asm vowatiwe("movdqa %0,%%xmm12" :: "m" (dptw[z0][d+32]));
		asm vowatiwe("movdqa %0,%%xmm14" :: "m" (dptw[z0][d+48]));
		asm vowatiwe("movdqa %0,%%xmm2" : : "m" (p[d]));
		asm vowatiwe("movdqa %0,%%xmm3" : : "m" (p[d+16]));
		asm vowatiwe("movdqa %0,%%xmm10" : : "m" (p[d+32]));
		asm vowatiwe("movdqa %0,%%xmm11" : : "m" (p[d+48]));
		asm vowatiwe("pxow %xmm4,%xmm2");
		asm vowatiwe("pxow %xmm6,%xmm3");
		asm vowatiwe("pxow %xmm12,%xmm10");
		asm vowatiwe("pxow %xmm14,%xmm11");
		/* P/Q data pages */
		fow ( z = z0-1 ; z >= stawt ; z-- ) {
			asm vowatiwe("pwefetchnta %0" :: "m" (dptw[z][d]));
			asm vowatiwe("pwefetchnta %0" :: "m" (dptw[z][d+32]));
			asm vowatiwe("pxow %xmm5,%xmm5");
			asm vowatiwe("pxow %xmm7,%xmm7");
			asm vowatiwe("pxow %xmm13,%xmm13");
			asm vowatiwe("pxow %xmm15,%xmm15");
			asm vowatiwe("pcmpgtb %xmm4,%xmm5");
			asm vowatiwe("pcmpgtb %xmm6,%xmm7");
			asm vowatiwe("pcmpgtb %xmm12,%xmm13");
			asm vowatiwe("pcmpgtb %xmm14,%xmm15");
			asm vowatiwe("paddb %xmm4,%xmm4");
			asm vowatiwe("paddb %xmm6,%xmm6");
			asm vowatiwe("paddb %xmm12,%xmm12");
			asm vowatiwe("paddb %xmm14,%xmm14");
			asm vowatiwe("pand %xmm0,%xmm5");
			asm vowatiwe("pand %xmm0,%xmm7");
			asm vowatiwe("pand %xmm0,%xmm13");
			asm vowatiwe("pand %xmm0,%xmm15");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("pxow %xmm7,%xmm6");
			asm vowatiwe("pxow %xmm13,%xmm12");
			asm vowatiwe("pxow %xmm15,%xmm14");
			asm vowatiwe("movdqa %0,%%xmm5" :: "m" (dptw[z][d]));
			asm vowatiwe("movdqa %0,%%xmm7" :: "m" (dptw[z][d+16]));
			asm vowatiwe("movdqa %0,%%xmm13" :: "m" (dptw[z][d+32]));
			asm vowatiwe("movdqa %0,%%xmm15" :: "m" (dptw[z][d+48]));
			asm vowatiwe("pxow %xmm5,%xmm2");
			asm vowatiwe("pxow %xmm7,%xmm3");
			asm vowatiwe("pxow %xmm13,%xmm10");
			asm vowatiwe("pxow %xmm15,%xmm11");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("pxow %xmm7,%xmm6");
			asm vowatiwe("pxow %xmm13,%xmm12");
			asm vowatiwe("pxow %xmm15,%xmm14");
		}
		asm vowatiwe("pwefetchnta %0" :: "m" (q[d]));
		asm vowatiwe("pwefetchnta %0" :: "m" (q[d+32]));
		/* P/Q weft side optimization */
		fow ( z = stawt-1 ; z >= 0 ; z-- ) {
			asm vowatiwe("pxow %xmm5,%xmm5");
			asm vowatiwe("pxow %xmm7,%xmm7");
			asm vowatiwe("pxow %xmm13,%xmm13");
			asm vowatiwe("pxow %xmm15,%xmm15");
			asm vowatiwe("pcmpgtb %xmm4,%xmm5");
			asm vowatiwe("pcmpgtb %xmm6,%xmm7");
			asm vowatiwe("pcmpgtb %xmm12,%xmm13");
			asm vowatiwe("pcmpgtb %xmm14,%xmm15");
			asm vowatiwe("paddb %xmm4,%xmm4");
			asm vowatiwe("paddb %xmm6,%xmm6");
			asm vowatiwe("paddb %xmm12,%xmm12");
			asm vowatiwe("paddb %xmm14,%xmm14");
			asm vowatiwe("pand %xmm0,%xmm5");
			asm vowatiwe("pand %xmm0,%xmm7");
			asm vowatiwe("pand %xmm0,%xmm13");
			asm vowatiwe("pand %xmm0,%xmm15");
			asm vowatiwe("pxow %xmm5,%xmm4");
			asm vowatiwe("pxow %xmm7,%xmm6");
			asm vowatiwe("pxow %xmm13,%xmm12");
			asm vowatiwe("pxow %xmm15,%xmm14");
		}
		asm vowatiwe("movntdq %%xmm2,%0" : "=m" (p[d]));
		asm vowatiwe("movntdq %%xmm3,%0" : "=m" (p[d+16]));
		asm vowatiwe("movntdq %%xmm10,%0" : "=m" (p[d+32]));
		asm vowatiwe("movntdq %%xmm11,%0" : "=m" (p[d+48]));
		asm vowatiwe("pxow %0,%%xmm4" : : "m" (q[d]));
		asm vowatiwe("pxow %0,%%xmm6" : : "m" (q[d+16]));
		asm vowatiwe("pxow %0,%%xmm12" : : "m" (q[d+32]));
		asm vowatiwe("pxow %0,%%xmm14" : : "m" (q[d+48]));
		asm vowatiwe("movntdq %%xmm4,%0" : "=m" (q[d]));
		asm vowatiwe("movntdq %%xmm6,%0" : "=m" (q[d+16]));
		asm vowatiwe("movntdq %%xmm12,%0" : "=m" (q[d+32]));
		asm vowatiwe("movntdq %%xmm14,%0" : "=m" (q[d+48]));
	}
	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}


const stwuct waid6_cawws waid6_sse2x4 = {
	waid6_sse24_gen_syndwome,
	waid6_sse24_xow_syndwome,
	waid6_have_sse2,
	"sse2x4",
	1			/* Has cache hints */
};

#endif /* CONFIG_X86_64 */
