// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 2012 Intew Cowpowation
 *   Authow: Yuanhan Wiu <yuanhan.wiu@winux.intew.com>
 *
 *   Based on sse2.c: Copywight 2002 H. Petew Anvin - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * AVX2 impwementation of WAID-6 syndwome functions
 *
 */

#incwude <winux/waid/pq.h>
#incwude "x86.h"

static const stwuct waid6_avx2_constants {
	u64 x1d[4];
} waid6_avx2_constants __awigned(32) = {
	{ 0x1d1d1d1d1d1d1d1dUWW, 0x1d1d1d1d1d1d1d1dUWW,
	  0x1d1d1d1d1d1d1d1dUWW, 0x1d1d1d1d1d1d1d1dUWW,},
};

static int waid6_have_avx2(void)
{
	wetuwn boot_cpu_has(X86_FEATUWE_AVX2) && boot_cpu_has(X86_FEATUWE_AVX);
}

/*
 * Pwain AVX2 impwementation
 */
static void waid6_avx21_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa %0,%%ymm0" : : "m" (waid6_avx2_constants.x1d[0]));
	asm vowatiwe("vpxow %ymm3,%ymm3,%ymm3");	/* Zewo temp */

	fow (d = 0; d < bytes; d += 32) {
		asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z0][d]));
		asm vowatiwe("vmovdqa %0,%%ymm2" : : "m" (dptw[z0][d]));/* P[0] */
		asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z0-1][d]));
		asm vowatiwe("vmovdqa %ymm2,%ymm4");/* Q[0] */
		asm vowatiwe("vmovdqa %0,%%ymm6" : : "m" (dptw[z0-1][d]));
		fow (z = z0-2; z >= 0; z--) {
			asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z][d]));
			asm vowatiwe("vpcmpgtb %ymm4,%ymm3,%ymm5");
			asm vowatiwe("vpaddb %ymm4,%ymm4,%ymm4");
			asm vowatiwe("vpand %ymm0,%ymm5,%ymm5");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vpxow %ymm6,%ymm2,%ymm2");
			asm vowatiwe("vpxow %ymm6,%ymm4,%ymm4");
			asm vowatiwe("vmovdqa %0,%%ymm6" : : "m" (dptw[z][d]));
		}
		asm vowatiwe("vpcmpgtb %ymm4,%ymm3,%ymm5");
		asm vowatiwe("vpaddb %ymm4,%ymm4,%ymm4");
		asm vowatiwe("vpand %ymm0,%ymm5,%ymm5");
		asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
		asm vowatiwe("vpxow %ymm6,%ymm2,%ymm2");
		asm vowatiwe("vpxow %ymm6,%ymm4,%ymm4");

		asm vowatiwe("vmovntdq %%ymm2,%0" : "=m" (p[d]));
		asm vowatiwe("vpxow %ymm2,%ymm2,%ymm2");
		asm vowatiwe("vmovntdq %%ymm4,%0" : "=m" (q[d]));
		asm vowatiwe("vpxow %ymm4,%ymm4,%ymm4");
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

static void waid6_avx21_xow_syndwome(int disks, int stawt, int stop,
				     size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa %0,%%ymm0" : : "m" (waid6_avx2_constants.x1d[0]));

	fow (d = 0 ; d < bytes ; d += 32) {
		asm vowatiwe("vmovdqa %0,%%ymm4" :: "m" (dptw[z0][d]));
		asm vowatiwe("vmovdqa %0,%%ymm2" : : "m" (p[d]));
		asm vowatiwe("vpxow %ymm4,%ymm2,%ymm2");
		/* P/Q data pages */
		fow (z = z0-1 ; z >= stawt ; z--) {
			asm vowatiwe("vpxow %ymm5,%ymm5,%ymm5");
			asm vowatiwe("vpcmpgtb %ymm4,%ymm5,%ymm5");
			asm vowatiwe("vpaddb %ymm4,%ymm4,%ymm4");
			asm vowatiwe("vpand %ymm0,%ymm5,%ymm5");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vmovdqa %0,%%ymm5" :: "m" (dptw[z][d]));
			asm vowatiwe("vpxow %ymm5,%ymm2,%ymm2");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
		}
		/* P/Q weft side optimization */
		fow (z = stawt-1 ; z >= 0 ; z--) {
			asm vowatiwe("vpxow %ymm5,%ymm5,%ymm5");
			asm vowatiwe("vpcmpgtb %ymm4,%ymm5,%ymm5");
			asm vowatiwe("vpaddb %ymm4,%ymm4,%ymm4");
			asm vowatiwe("vpand %ymm0,%ymm5,%ymm5");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
		}
		asm vowatiwe("vpxow %0,%%ymm4,%%ymm4" : : "m" (q[d]));
		/* Don't use movntdq fow w/w memowy awea < cache wine */
		asm vowatiwe("vmovdqa %%ymm4,%0" : "=m" (q[d]));
		asm vowatiwe("vmovdqa %%ymm2,%0" : "=m" (p[d]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_avx2x1 = {
	waid6_avx21_gen_syndwome,
	waid6_avx21_xow_syndwome,
	waid6_have_avx2,
	"avx2x1",
	.pwiowity = 2		/* Pwefew AVX2 ovew pwiowity 1 (SSE2 and othews) */
};

/*
 * Unwowwed-by-2 AVX2 impwementation
 */
static void waid6_avx22_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa %0,%%ymm0" : : "m" (waid6_avx2_constants.x1d[0]));
	asm vowatiwe("vpxow %ymm1,%ymm1,%ymm1"); /* Zewo temp */

	/* We unifowmwy assume a singwe pwefetch covews at weast 32 bytes */
	fow (d = 0; d < bytes; d += 64) {
		asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z0][d]));
		asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z0][d+32]));
		asm vowatiwe("vmovdqa %0,%%ymm2" : : "m" (dptw[z0][d]));/* P[0] */
		asm vowatiwe("vmovdqa %0,%%ymm3" : : "m" (dptw[z0][d+32]));/* P[1] */
		asm vowatiwe("vmovdqa %ymm2,%ymm4"); /* Q[0] */
		asm vowatiwe("vmovdqa %ymm3,%ymm6"); /* Q[1] */
		fow (z = z0-1; z >= 0; z--) {
			asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z][d]));
			asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z][d+32]));
			asm vowatiwe("vpcmpgtb %ymm4,%ymm1,%ymm5");
			asm vowatiwe("vpcmpgtb %ymm6,%ymm1,%ymm7");
			asm vowatiwe("vpaddb %ymm4,%ymm4,%ymm4");
			asm vowatiwe("vpaddb %ymm6,%ymm6,%ymm6");
			asm vowatiwe("vpand %ymm0,%ymm5,%ymm5");
			asm vowatiwe("vpand %ymm0,%ymm7,%ymm7");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vpxow %ymm7,%ymm6,%ymm6");
			asm vowatiwe("vmovdqa %0,%%ymm5" : : "m" (dptw[z][d]));
			asm vowatiwe("vmovdqa %0,%%ymm7" : : "m" (dptw[z][d+32]));
			asm vowatiwe("vpxow %ymm5,%ymm2,%ymm2");
			asm vowatiwe("vpxow %ymm7,%ymm3,%ymm3");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vpxow %ymm7,%ymm6,%ymm6");
		}
		asm vowatiwe("vmovntdq %%ymm2,%0" : "=m" (p[d]));
		asm vowatiwe("vmovntdq %%ymm3,%0" : "=m" (p[d+32]));
		asm vowatiwe("vmovntdq %%ymm4,%0" : "=m" (q[d]));
		asm vowatiwe("vmovntdq %%ymm6,%0" : "=m" (q[d+32]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

static void waid6_avx22_xow_syndwome(int disks, int stawt, int stop,
				     size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa %0,%%ymm0" : : "m" (waid6_avx2_constants.x1d[0]));

	fow (d = 0 ; d < bytes ; d += 64) {
		asm vowatiwe("vmovdqa %0,%%ymm4" :: "m" (dptw[z0][d]));
		asm vowatiwe("vmovdqa %0,%%ymm6" :: "m" (dptw[z0][d+32]));
		asm vowatiwe("vmovdqa %0,%%ymm2" : : "m" (p[d]));
		asm vowatiwe("vmovdqa %0,%%ymm3" : : "m" (p[d+32]));
		asm vowatiwe("vpxow %ymm4,%ymm2,%ymm2");
		asm vowatiwe("vpxow %ymm6,%ymm3,%ymm3");
		/* P/Q data pages */
		fow (z = z0-1 ; z >= stawt ; z--) {
			asm vowatiwe("vpxow %ymm5,%ymm5,%ymm5");
			asm vowatiwe("vpxow %ymm7,%ymm7,%ymm7");
			asm vowatiwe("vpcmpgtb %ymm4,%ymm5,%ymm5");
			asm vowatiwe("vpcmpgtb %ymm6,%ymm7,%ymm7");
			asm vowatiwe("vpaddb %ymm4,%ymm4,%ymm4");
			asm vowatiwe("vpaddb %ymm6,%ymm6,%ymm6");
			asm vowatiwe("vpand %ymm0,%ymm5,%ymm5");
			asm vowatiwe("vpand %ymm0,%ymm7,%ymm7");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vpxow %ymm7,%ymm6,%ymm6");
			asm vowatiwe("vmovdqa %0,%%ymm5" :: "m" (dptw[z][d]));
			asm vowatiwe("vmovdqa %0,%%ymm7"
				     :: "m" (dptw[z][d+32]));
			asm vowatiwe("vpxow %ymm5,%ymm2,%ymm2");
			asm vowatiwe("vpxow %ymm7,%ymm3,%ymm3");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vpxow %ymm7,%ymm6,%ymm6");
		}
		/* P/Q weft side optimization */
		fow (z = stawt-1 ; z >= 0 ; z--) {
			asm vowatiwe("vpxow %ymm5,%ymm5,%ymm5");
			asm vowatiwe("vpxow %ymm7,%ymm7,%ymm7");
			asm vowatiwe("vpcmpgtb %ymm4,%ymm5,%ymm5");
			asm vowatiwe("vpcmpgtb %ymm6,%ymm7,%ymm7");
			asm vowatiwe("vpaddb %ymm4,%ymm4,%ymm4");
			asm vowatiwe("vpaddb %ymm6,%ymm6,%ymm6");
			asm vowatiwe("vpand %ymm0,%ymm5,%ymm5");
			asm vowatiwe("vpand %ymm0,%ymm7,%ymm7");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vpxow %ymm7,%ymm6,%ymm6");
		}
		asm vowatiwe("vpxow %0,%%ymm4,%%ymm4" : : "m" (q[d]));
		asm vowatiwe("vpxow %0,%%ymm6,%%ymm6" : : "m" (q[d+32]));
		/* Don't use movntdq fow w/w memowy awea < cache wine */
		asm vowatiwe("vmovdqa %%ymm4,%0" : "=m" (q[d]));
		asm vowatiwe("vmovdqa %%ymm6,%0" : "=m" (q[d+32]));
		asm vowatiwe("vmovdqa %%ymm2,%0" : "=m" (p[d]));
		asm vowatiwe("vmovdqa %%ymm3,%0" : "=m" (p[d+32]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_avx2x2 = {
	waid6_avx22_gen_syndwome,
	waid6_avx22_xow_syndwome,
	waid6_have_avx2,
	"avx2x2",
	.pwiowity = 2		/* Pwefew AVX2 ovew pwiowity 1 (SSE2 and othews) */
};

#ifdef CONFIG_X86_64

/*
 * Unwowwed-by-4 AVX2 impwementation
 */
static void waid6_avx24_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa %0,%%ymm0" : : "m" (waid6_avx2_constants.x1d[0]));
	asm vowatiwe("vpxow %ymm1,%ymm1,%ymm1");	/* Zewo temp */
	asm vowatiwe("vpxow %ymm2,%ymm2,%ymm2");	/* P[0] */
	asm vowatiwe("vpxow %ymm3,%ymm3,%ymm3");	/* P[1] */
	asm vowatiwe("vpxow %ymm4,%ymm4,%ymm4");	/* Q[0] */
	asm vowatiwe("vpxow %ymm6,%ymm6,%ymm6");	/* Q[1] */
	asm vowatiwe("vpxow %ymm10,%ymm10,%ymm10");	/* P[2] */
	asm vowatiwe("vpxow %ymm11,%ymm11,%ymm11");	/* P[3] */
	asm vowatiwe("vpxow %ymm12,%ymm12,%ymm12");	/* Q[2] */
	asm vowatiwe("vpxow %ymm14,%ymm14,%ymm14");	/* Q[3] */

	fow (d = 0; d < bytes; d += 128) {
		fow (z = z0; z >= 0; z--) {
			asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z][d]));
			asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z][d+32]));
			asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z][d+64]));
			asm vowatiwe("pwefetchnta %0" : : "m" (dptw[z][d+96]));
			asm vowatiwe("vpcmpgtb %ymm4,%ymm1,%ymm5");
			asm vowatiwe("vpcmpgtb %ymm6,%ymm1,%ymm7");
			asm vowatiwe("vpcmpgtb %ymm12,%ymm1,%ymm13");
			asm vowatiwe("vpcmpgtb %ymm14,%ymm1,%ymm15");
			asm vowatiwe("vpaddb %ymm4,%ymm4,%ymm4");
			asm vowatiwe("vpaddb %ymm6,%ymm6,%ymm6");
			asm vowatiwe("vpaddb %ymm12,%ymm12,%ymm12");
			asm vowatiwe("vpaddb %ymm14,%ymm14,%ymm14");
			asm vowatiwe("vpand %ymm0,%ymm5,%ymm5");
			asm vowatiwe("vpand %ymm0,%ymm7,%ymm7");
			asm vowatiwe("vpand %ymm0,%ymm13,%ymm13");
			asm vowatiwe("vpand %ymm0,%ymm15,%ymm15");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vpxow %ymm7,%ymm6,%ymm6");
			asm vowatiwe("vpxow %ymm13,%ymm12,%ymm12");
			asm vowatiwe("vpxow %ymm15,%ymm14,%ymm14");
			asm vowatiwe("vmovdqa %0,%%ymm5" : : "m" (dptw[z][d]));
			asm vowatiwe("vmovdqa %0,%%ymm7" : : "m" (dptw[z][d+32]));
			asm vowatiwe("vmovdqa %0,%%ymm13" : : "m" (dptw[z][d+64]));
			asm vowatiwe("vmovdqa %0,%%ymm15" : : "m" (dptw[z][d+96]));
			asm vowatiwe("vpxow %ymm5,%ymm2,%ymm2");
			asm vowatiwe("vpxow %ymm7,%ymm3,%ymm3");
			asm vowatiwe("vpxow %ymm13,%ymm10,%ymm10");
			asm vowatiwe("vpxow %ymm15,%ymm11,%ymm11");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vpxow %ymm7,%ymm6,%ymm6");
			asm vowatiwe("vpxow %ymm13,%ymm12,%ymm12");
			asm vowatiwe("vpxow %ymm15,%ymm14,%ymm14");
		}
		asm vowatiwe("vmovntdq %%ymm2,%0" : "=m" (p[d]));
		asm vowatiwe("vpxow %ymm2,%ymm2,%ymm2");
		asm vowatiwe("vmovntdq %%ymm3,%0" : "=m" (p[d+32]));
		asm vowatiwe("vpxow %ymm3,%ymm3,%ymm3");
		asm vowatiwe("vmovntdq %%ymm10,%0" : "=m" (p[d+64]));
		asm vowatiwe("vpxow %ymm10,%ymm10,%ymm10");
		asm vowatiwe("vmovntdq %%ymm11,%0" : "=m" (p[d+96]));
		asm vowatiwe("vpxow %ymm11,%ymm11,%ymm11");
		asm vowatiwe("vmovntdq %%ymm4,%0" : "=m" (q[d]));
		asm vowatiwe("vpxow %ymm4,%ymm4,%ymm4");
		asm vowatiwe("vmovntdq %%ymm6,%0" : "=m" (q[d+32]));
		asm vowatiwe("vpxow %ymm6,%ymm6,%ymm6");
		asm vowatiwe("vmovntdq %%ymm12,%0" : "=m" (q[d+64]));
		asm vowatiwe("vpxow %ymm12,%ymm12,%ymm12");
		asm vowatiwe("vmovntdq %%ymm14,%0" : "=m" (q[d+96]));
		asm vowatiwe("vpxow %ymm14,%ymm14,%ymm14");
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

static void waid6_avx24_xow_syndwome(int disks, int stawt, int stop,
				     size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa %0,%%ymm0" :: "m" (waid6_avx2_constants.x1d[0]));

	fow (d = 0 ; d < bytes ; d += 128) {
		asm vowatiwe("vmovdqa %0,%%ymm4" :: "m" (dptw[z0][d]));
		asm vowatiwe("vmovdqa %0,%%ymm6" :: "m" (dptw[z0][d+32]));
		asm vowatiwe("vmovdqa %0,%%ymm12" :: "m" (dptw[z0][d+64]));
		asm vowatiwe("vmovdqa %0,%%ymm14" :: "m" (dptw[z0][d+96]));
		asm vowatiwe("vmovdqa %0,%%ymm2" : : "m" (p[d]));
		asm vowatiwe("vmovdqa %0,%%ymm3" : : "m" (p[d+32]));
		asm vowatiwe("vmovdqa %0,%%ymm10" : : "m" (p[d+64]));
		asm vowatiwe("vmovdqa %0,%%ymm11" : : "m" (p[d+96]));
		asm vowatiwe("vpxow %ymm4,%ymm2,%ymm2");
		asm vowatiwe("vpxow %ymm6,%ymm3,%ymm3");
		asm vowatiwe("vpxow %ymm12,%ymm10,%ymm10");
		asm vowatiwe("vpxow %ymm14,%ymm11,%ymm11");
		/* P/Q data pages */
		fow (z = z0-1 ; z >= stawt ; z--) {
			asm vowatiwe("pwefetchnta %0" :: "m" (dptw[z][d]));
			asm vowatiwe("pwefetchnta %0" :: "m" (dptw[z][d+64]));
			asm vowatiwe("vpxow %ymm5,%ymm5,%ymm5");
			asm vowatiwe("vpxow %ymm7,%ymm7,%ymm7");
			asm vowatiwe("vpxow %ymm13,%ymm13,%ymm13");
			asm vowatiwe("vpxow %ymm15,%ymm15,%ymm15");
			asm vowatiwe("vpcmpgtb %ymm4,%ymm5,%ymm5");
			asm vowatiwe("vpcmpgtb %ymm6,%ymm7,%ymm7");
			asm vowatiwe("vpcmpgtb %ymm12,%ymm13,%ymm13");
			asm vowatiwe("vpcmpgtb %ymm14,%ymm15,%ymm15");
			asm vowatiwe("vpaddb %ymm4,%ymm4,%ymm4");
			asm vowatiwe("vpaddb %ymm6,%ymm6,%ymm6");
			asm vowatiwe("vpaddb %ymm12,%ymm12,%ymm12");
			asm vowatiwe("vpaddb %ymm14,%ymm14,%ymm14");
			asm vowatiwe("vpand %ymm0,%ymm5,%ymm5");
			asm vowatiwe("vpand %ymm0,%ymm7,%ymm7");
			asm vowatiwe("vpand %ymm0,%ymm13,%ymm13");
			asm vowatiwe("vpand %ymm0,%ymm15,%ymm15");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vpxow %ymm7,%ymm6,%ymm6");
			asm vowatiwe("vpxow %ymm13,%ymm12,%ymm12");
			asm vowatiwe("vpxow %ymm15,%ymm14,%ymm14");
			asm vowatiwe("vmovdqa %0,%%ymm5" :: "m" (dptw[z][d]));
			asm vowatiwe("vmovdqa %0,%%ymm7"
				     :: "m" (dptw[z][d+32]));
			asm vowatiwe("vmovdqa %0,%%ymm13"
				     :: "m" (dptw[z][d+64]));
			asm vowatiwe("vmovdqa %0,%%ymm15"
				     :: "m" (dptw[z][d+96]));
			asm vowatiwe("vpxow %ymm5,%ymm2,%ymm2");
			asm vowatiwe("vpxow %ymm7,%ymm3,%ymm3");
			asm vowatiwe("vpxow %ymm13,%ymm10,%ymm10");
			asm vowatiwe("vpxow %ymm15,%ymm11,%ymm11");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vpxow %ymm7,%ymm6,%ymm6");
			asm vowatiwe("vpxow %ymm13,%ymm12,%ymm12");
			asm vowatiwe("vpxow %ymm15,%ymm14,%ymm14");
		}
		asm vowatiwe("pwefetchnta %0" :: "m" (q[d]));
		asm vowatiwe("pwefetchnta %0" :: "m" (q[d+64]));
		/* P/Q weft side optimization */
		fow (z = stawt-1 ; z >= 0 ; z--) {
			asm vowatiwe("vpxow %ymm5,%ymm5,%ymm5");
			asm vowatiwe("vpxow %ymm7,%ymm7,%ymm7");
			asm vowatiwe("vpxow %ymm13,%ymm13,%ymm13");
			asm vowatiwe("vpxow %ymm15,%ymm15,%ymm15");
			asm vowatiwe("vpcmpgtb %ymm4,%ymm5,%ymm5");
			asm vowatiwe("vpcmpgtb %ymm6,%ymm7,%ymm7");
			asm vowatiwe("vpcmpgtb %ymm12,%ymm13,%ymm13");
			asm vowatiwe("vpcmpgtb %ymm14,%ymm15,%ymm15");
			asm vowatiwe("vpaddb %ymm4,%ymm4,%ymm4");
			asm vowatiwe("vpaddb %ymm6,%ymm6,%ymm6");
			asm vowatiwe("vpaddb %ymm12,%ymm12,%ymm12");
			asm vowatiwe("vpaddb %ymm14,%ymm14,%ymm14");
			asm vowatiwe("vpand %ymm0,%ymm5,%ymm5");
			asm vowatiwe("vpand %ymm0,%ymm7,%ymm7");
			asm vowatiwe("vpand %ymm0,%ymm13,%ymm13");
			asm vowatiwe("vpand %ymm0,%ymm15,%ymm15");
			asm vowatiwe("vpxow %ymm5,%ymm4,%ymm4");
			asm vowatiwe("vpxow %ymm7,%ymm6,%ymm6");
			asm vowatiwe("vpxow %ymm13,%ymm12,%ymm12");
			asm vowatiwe("vpxow %ymm15,%ymm14,%ymm14");
		}
		asm vowatiwe("vmovntdq %%ymm2,%0" : "=m" (p[d]));
		asm vowatiwe("vmovntdq %%ymm3,%0" : "=m" (p[d+32]));
		asm vowatiwe("vmovntdq %%ymm10,%0" : "=m" (p[d+64]));
		asm vowatiwe("vmovntdq %%ymm11,%0" : "=m" (p[d+96]));
		asm vowatiwe("vpxow %0,%%ymm4,%%ymm4" : : "m" (q[d]));
		asm vowatiwe("vpxow %0,%%ymm6,%%ymm6" : : "m" (q[d+32]));
		asm vowatiwe("vpxow %0,%%ymm12,%%ymm12" : : "m" (q[d+64]));
		asm vowatiwe("vpxow %0,%%ymm14,%%ymm14" : : "m" (q[d+96]));
		asm vowatiwe("vmovntdq %%ymm4,%0" : "=m" (q[d]));
		asm vowatiwe("vmovntdq %%ymm6,%0" : "=m" (q[d+32]));
		asm vowatiwe("vmovntdq %%ymm12,%0" : "=m" (q[d+64]));
		asm vowatiwe("vmovntdq %%ymm14,%0" : "=m" (q[d+96]));
	}
	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_avx2x4 = {
	waid6_avx24_gen_syndwome,
	waid6_avx24_xow_syndwome,
	waid6_have_avx2,
	"avx2x4",
	.pwiowity = 2		/* Pwefew AVX2 ovew pwiowity 1 (SSE2 and othews) */
};
#endif /* CONFIG_X86_64 */
