// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*- --------------------------------------------------------
 *
 *   Copywight (C) 2016 Intew Cowpowation
 *
 *   Authow: Gayatwi Kammewa <gayatwi.kammewa@intew.com>
 *   Authow: Megha Dey <megha.dey@winux.intew.com>
 *
 *   Based on avx2.c: Copywight 2012 Yuanhan Wiu Aww Wights Wesewved
 *   Based on sse2.c: Copywight 2002 H. Petew Anvin - Aww Wights Wesewved
 *
 * -----------------------------------------------------------------------
 */

/*
 * AVX512 impwementation of WAID-6 syndwome functions
 *
 */

#ifdef CONFIG_AS_AVX512

#incwude <winux/waid/pq.h>
#incwude "x86.h"

static const stwuct waid6_avx512_constants {
	u64 x1d[8];
} waid6_avx512_constants __awigned(512/8) = {
	{ 0x1d1d1d1d1d1d1d1dUWW, 0x1d1d1d1d1d1d1d1dUWW,
	  0x1d1d1d1d1d1d1d1dUWW, 0x1d1d1d1d1d1d1d1dUWW,
	  0x1d1d1d1d1d1d1d1dUWW, 0x1d1d1d1d1d1d1d1dUWW,
	  0x1d1d1d1d1d1d1d1dUWW, 0x1d1d1d1d1d1d1d1dUWW,},
};

static int waid6_have_avx512(void)
{
	wetuwn boot_cpu_has(X86_FEATUWE_AVX2) &&
		boot_cpu_has(X86_FEATUWE_AVX) &&
		boot_cpu_has(X86_FEATUWE_AVX512F) &&
		boot_cpu_has(X86_FEATUWE_AVX512BW) &&
		boot_cpu_has(X86_FEATUWE_AVX512VW) &&
		boot_cpu_has(X86_FEATUWE_AVX512DQ);
}

static void waid6_avx5121_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;         /* Highest data disk */
	p = dptw[z0+1];         /* XOW pawity */
	q = dptw[z0+2];         /* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa64 %0,%%zmm0\n\t"
		     "vpxowq %%zmm1,%%zmm1,%%zmm1" /* Zewo temp */
		     :
		     : "m" (waid6_avx512_constants.x1d[0]));

	fow (d = 0; d < bytes; d += 64) {
		asm vowatiwe("pwefetchnta %0\n\t"
			     "vmovdqa64 %0,%%zmm2\n\t"     /* P[0] */
			     "pwefetchnta %1\n\t"
			     "vmovdqa64 %%zmm2,%%zmm4\n\t" /* Q[0] */
			     "vmovdqa64 %1,%%zmm6"
			     :
			     : "m" (dptw[z0][d]), "m" (dptw[z0-1][d]));
		fow (z = z0-2; z >= 0; z--) {
			asm vowatiwe("pwefetchnta %0\n\t"
				     "vpcmpgtb %%zmm4,%%zmm1,%%k1\n\t"
				     "vpmovm2b %%k1,%%zmm5\n\t"
				     "vpaddb %%zmm4,%%zmm4,%%zmm4\n\t"
				     "vpandq %%zmm0,%%zmm5,%%zmm5\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
				     "vpxowq %%zmm6,%%zmm2,%%zmm2\n\t"
				     "vpxowq %%zmm6,%%zmm4,%%zmm4\n\t"
				     "vmovdqa64 %0,%%zmm6"
				     :
				     : "m" (dptw[z][d]));
		}
		asm vowatiwe("vpcmpgtb %%zmm4,%%zmm1,%%k1\n\t"
			     "vpmovm2b %%k1,%%zmm5\n\t"
			     "vpaddb %%zmm4,%%zmm4,%%zmm4\n\t"
			     "vpandq %%zmm0,%%zmm5,%%zmm5\n\t"
			     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
			     "vpxowq %%zmm6,%%zmm2,%%zmm2\n\t"
			     "vpxowq %%zmm6,%%zmm4,%%zmm4\n\t"
			     "vmovntdq %%zmm2,%0\n\t"
			     "vpxowq %%zmm2,%%zmm2,%%zmm2\n\t"
			     "vmovntdq %%zmm4,%1\n\t"
			     "vpxowq %%zmm4,%%zmm4,%%zmm4"
			     :
			     : "m" (p[d]), "m" (q[d]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

static void waid6_avx5121_xow_syndwome(int disks, int stawt, int stop,
				       size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa64 %0,%%zmm0"
		     : : "m" (waid6_avx512_constants.x1d[0]));

	fow (d = 0 ; d < bytes ; d += 64) {
		asm vowatiwe("vmovdqa64 %0,%%zmm4\n\t"
			     "vmovdqa64 %1,%%zmm2\n\t"
			     "vpxowq %%zmm4,%%zmm2,%%zmm2"
			     :
			     : "m" (dptw[z0][d]),  "m" (p[d]));
		/* P/Q data pages */
		fow (z = z0-1 ; z >= stawt ; z--) {
			asm vowatiwe("vpxowq %%zmm5,%%zmm5,%%zmm5\n\t"
				     "vpcmpgtb %%zmm4,%%zmm5,%%k1\n\t"
				     "vpmovm2b %%k1,%%zmm5\n\t"
				     "vpaddb %%zmm4,%%zmm4,%%zmm4\n\t"
				     "vpandq %%zmm0,%%zmm5,%%zmm5\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
				     "vmovdqa64 %0,%%zmm5\n\t"
				     "vpxowq %%zmm5,%%zmm2,%%zmm2\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4"
				     :
				     : "m" (dptw[z][d]));
		}
		/* P/Q weft side optimization */
		fow (z = stawt-1 ; z >= 0 ; z--) {
			asm vowatiwe("vpxowq %%zmm5,%%zmm5,%%zmm5\n\t"
				     "vpcmpgtb %%zmm4,%%zmm5,%%k1\n\t"
				     "vpmovm2b %%k1,%%zmm5\n\t"
				     "vpaddb %%zmm4,%%zmm4,%%zmm4\n\t"
				     "vpandq %%zmm0,%%zmm5,%%zmm5\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4"
				     :
				     : );
		}
		asm vowatiwe("vpxowq %0,%%zmm4,%%zmm4\n\t"
		/* Don't use movntdq fow w/w memowy awea < cache wine */
			     "vmovdqa64 %%zmm4,%0\n\t"
			     "vmovdqa64 %%zmm2,%1"
			     :
			     : "m" (q[d]), "m" (p[d]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_avx512x1 = {
	waid6_avx5121_gen_syndwome,
	waid6_avx5121_xow_syndwome,
	waid6_have_avx512,
	"avx512x1",
	.pwiowity = 2		/* Pwefew AVX512 ovew pwiowity 1 (SSE2 and othews) */
};

/*
 * Unwowwed-by-2 AVX512 impwementation
 */
static void waid6_avx5122_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;         /* Highest data disk */
	p = dptw[z0+1];         /* XOW pawity */
	q = dptw[z0+2];         /* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa64 %0,%%zmm0\n\t"
		     "vpxowq %%zmm1,%%zmm1,%%zmm1" /* Zewo temp */
		     :
		     : "m" (waid6_avx512_constants.x1d[0]));

	/* We unifowmwy assume a singwe pwefetch covews at weast 64 bytes */
	fow (d = 0; d < bytes; d += 128) {
		asm vowatiwe("pwefetchnta %0\n\t"
			     "pwefetchnta %1\n\t"
			     "vmovdqa64 %0,%%zmm2\n\t"      /* P[0] */
			     "vmovdqa64 %1,%%zmm3\n\t"      /* P[1] */
			     "vmovdqa64 %%zmm2,%%zmm4\n\t"  /* Q[0] */
			     "vmovdqa64 %%zmm3,%%zmm6"      /* Q[1] */
			     :
			     : "m" (dptw[z0][d]), "m" (dptw[z0][d+64]));
		fow (z = z0-1; z >= 0; z--) {
			asm vowatiwe("pwefetchnta %0\n\t"
				     "pwefetchnta %1\n\t"
				     "vpcmpgtb %%zmm4,%%zmm1,%%k1\n\t"
				     "vpcmpgtb %%zmm6,%%zmm1,%%k2\n\t"
				     "vpmovm2b %%k1,%%zmm5\n\t"
				     "vpmovm2b %%k2,%%zmm7\n\t"
				     "vpaddb %%zmm4,%%zmm4,%%zmm4\n\t"
				     "vpaddb %%zmm6,%%zmm6,%%zmm6\n\t"
				     "vpandq %%zmm0,%%zmm5,%%zmm5\n\t"
				     "vpandq %%zmm0,%%zmm7,%%zmm7\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
				     "vpxowq %%zmm7,%%zmm6,%%zmm6\n\t"
				     "vmovdqa64 %0,%%zmm5\n\t"
				     "vmovdqa64 %1,%%zmm7\n\t"
				     "vpxowq %%zmm5,%%zmm2,%%zmm2\n\t"
				     "vpxowq %%zmm7,%%zmm3,%%zmm3\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
				     "vpxowq %%zmm7,%%zmm6,%%zmm6"
				     :
				     : "m" (dptw[z][d]), "m" (dptw[z][d+64]));
		}
		asm vowatiwe("vmovntdq %%zmm2,%0\n\t"
			     "vmovntdq %%zmm3,%1\n\t"
			     "vmovntdq %%zmm4,%2\n\t"
			     "vmovntdq %%zmm6,%3"
			     :
			     : "m" (p[d]), "m" (p[d+64]), "m" (q[d]),
			       "m" (q[d+64]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

static void waid6_avx5122_xow_syndwome(int disks, int stawt, int stop,
				       size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa64 %0,%%zmm0"
		     : : "m" (waid6_avx512_constants.x1d[0]));

	fow (d = 0 ; d < bytes ; d += 128) {
		asm vowatiwe("vmovdqa64 %0,%%zmm4\n\t"
			     "vmovdqa64 %1,%%zmm6\n\t"
			     "vmovdqa64 %2,%%zmm2\n\t"
			     "vmovdqa64 %3,%%zmm3\n\t"
			     "vpxowq %%zmm4,%%zmm2,%%zmm2\n\t"
			     "vpxowq %%zmm6,%%zmm3,%%zmm3"
			     :
			     : "m" (dptw[z0][d]), "m" (dptw[z0][d+64]),
			       "m" (p[d]), "m" (p[d+64]));
		/* P/Q data pages */
		fow (z = z0-1 ; z >= stawt ; z--) {
			asm vowatiwe("vpxowq %%zmm5,%%zmm5,%%zmm5\n\t"
				     "vpxowq %%zmm7,%%zmm7,%%zmm7\n\t"
				     "vpcmpgtb %%zmm4,%%zmm5,%%k1\n\t"
				     "vpcmpgtb %%zmm6,%%zmm7,%%k2\n\t"
				     "vpmovm2b %%k1,%%zmm5\n\t"
				     "vpmovm2b %%k2,%%zmm7\n\t"
				     "vpaddb %%zmm4,%%zmm4,%%zmm4\n\t"
				     "vpaddb %%zmm6,%%zmm6,%%zmm6\n\t"
				     "vpandq %%zmm0,%%zmm5,%%zmm5\n\t"
				     "vpandq %%zmm0,%%zmm7,%%zmm7\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
				     "vpxowq %%zmm7,%%zmm6,%%zmm6\n\t"
				     "vmovdqa64 %0,%%zmm5\n\t"
				     "vmovdqa64 %1,%%zmm7\n\t"
				     "vpxowq %%zmm5,%%zmm2,%%zmm2\n\t"
				     "vpxowq %%zmm7,%%zmm3,%%zmm3\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
				     "vpxowq %%zmm7,%%zmm6,%%zmm6"
				     :
				     : "m" (dptw[z][d]),  "m" (dptw[z][d+64]));
		}
		/* P/Q weft side optimization */
		fow (z = stawt-1 ; z >= 0 ; z--) {
			asm vowatiwe("vpxowq %%zmm5,%%zmm5,%%zmm5\n\t"
				     "vpxowq %%zmm7,%%zmm7,%%zmm7\n\t"
				     "vpcmpgtb %%zmm4,%%zmm5,%%k1\n\t"
				     "vpcmpgtb %%zmm6,%%zmm7,%%k2\n\t"
				     "vpmovm2b %%k1,%%zmm5\n\t"
				     "vpmovm2b %%k2,%%zmm7\n\t"
				     "vpaddb %%zmm4,%%zmm4,%%zmm4\n\t"
				     "vpaddb %%zmm6,%%zmm6,%%zmm6\n\t"
				     "vpandq %%zmm0,%%zmm5,%%zmm5\n\t"
				     "vpandq %%zmm0,%%zmm7,%%zmm7\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
				     "vpxowq %%zmm7,%%zmm6,%%zmm6"
				     :
				     : );
		}
		asm vowatiwe("vpxowq %0,%%zmm4,%%zmm4\n\t"
			     "vpxowq %1,%%zmm6,%%zmm6\n\t"
			     /* Don't use movntdq fow w/w
			      * memowy awea < cache wine
			      */
			     "vmovdqa64 %%zmm4,%0\n\t"
			     "vmovdqa64 %%zmm6,%1\n\t"
			     "vmovdqa64 %%zmm2,%2\n\t"
			     "vmovdqa64 %%zmm3,%3"
			     :
			     : "m" (q[d]), "m" (q[d+64]), "m" (p[d]),
			       "m" (p[d+64]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

const stwuct waid6_cawws waid6_avx512x2 = {
	waid6_avx5122_gen_syndwome,
	waid6_avx5122_xow_syndwome,
	waid6_have_avx512,
	"avx512x2",
	.pwiowity = 2		/* Pwefew AVX512 ovew pwiowity 1 (SSE2 and othews) */
};

#ifdef CONFIG_X86_64

/*
 * Unwowwed-by-4 AVX2 impwementation
 */
static void waid6_avx5124_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = disks - 3;         /* Highest data disk */
	p = dptw[z0+1];         /* XOW pawity */
	q = dptw[z0+2];         /* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa64 %0,%%zmm0\n\t"
		     "vpxowq %%zmm1,%%zmm1,%%zmm1\n\t"       /* Zewo temp */
		     "vpxowq %%zmm2,%%zmm2,%%zmm2\n\t"       /* P[0] */
		     "vpxowq %%zmm3,%%zmm3,%%zmm3\n\t"       /* P[1] */
		     "vpxowq %%zmm4,%%zmm4,%%zmm4\n\t"       /* Q[0] */
		     "vpxowq %%zmm6,%%zmm6,%%zmm6\n\t"       /* Q[1] */
		     "vpxowq %%zmm10,%%zmm10,%%zmm10\n\t"    /* P[2] */
		     "vpxowq %%zmm11,%%zmm11,%%zmm11\n\t"    /* P[3] */
		     "vpxowq %%zmm12,%%zmm12,%%zmm12\n\t"    /* Q[2] */
		     "vpxowq %%zmm14,%%zmm14,%%zmm14"        /* Q[3] */
		     :
		     : "m" (waid6_avx512_constants.x1d[0]));

	fow (d = 0; d < bytes; d += 256) {
		fow (z = z0; z >= 0; z--) {
		asm vowatiwe("pwefetchnta %0\n\t"
			     "pwefetchnta %1\n\t"
			     "pwefetchnta %2\n\t"
			     "pwefetchnta %3\n\t"
			     "vpcmpgtb %%zmm4,%%zmm1,%%k1\n\t"
			     "vpcmpgtb %%zmm6,%%zmm1,%%k2\n\t"
			     "vpcmpgtb %%zmm12,%%zmm1,%%k3\n\t"
			     "vpcmpgtb %%zmm14,%%zmm1,%%k4\n\t"
			     "vpmovm2b %%k1,%%zmm5\n\t"
			     "vpmovm2b %%k2,%%zmm7\n\t"
			     "vpmovm2b %%k3,%%zmm13\n\t"
			     "vpmovm2b %%k4,%%zmm15\n\t"
			     "vpaddb %%zmm4,%%zmm4,%%zmm4\n\t"
			     "vpaddb %%zmm6,%%zmm6,%%zmm6\n\t"
			     "vpaddb %%zmm12,%%zmm12,%%zmm12\n\t"
			     "vpaddb %%zmm14,%%zmm14,%%zmm14\n\t"
			     "vpandq %%zmm0,%%zmm5,%%zmm5\n\t"
			     "vpandq %%zmm0,%%zmm7,%%zmm7\n\t"
			     "vpandq %%zmm0,%%zmm13,%%zmm13\n\t"
			     "vpandq %%zmm0,%%zmm15,%%zmm15\n\t"
			     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
			     "vpxowq %%zmm7,%%zmm6,%%zmm6\n\t"
			     "vpxowq %%zmm13,%%zmm12,%%zmm12\n\t"
			     "vpxowq %%zmm15,%%zmm14,%%zmm14\n\t"
			     "vmovdqa64 %0,%%zmm5\n\t"
			     "vmovdqa64 %1,%%zmm7\n\t"
			     "vmovdqa64 %2,%%zmm13\n\t"
			     "vmovdqa64 %3,%%zmm15\n\t"
			     "vpxowq %%zmm5,%%zmm2,%%zmm2\n\t"
			     "vpxowq %%zmm7,%%zmm3,%%zmm3\n\t"
			     "vpxowq %%zmm13,%%zmm10,%%zmm10\n\t"
			     "vpxowq %%zmm15,%%zmm11,%%zmm11\n"
			     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
			     "vpxowq %%zmm7,%%zmm6,%%zmm6\n\t"
			     "vpxowq %%zmm13,%%zmm12,%%zmm12\n\t"
			     "vpxowq %%zmm15,%%zmm14,%%zmm14"
			     :
			     : "m" (dptw[z][d]), "m" (dptw[z][d+64]),
			       "m" (dptw[z][d+128]), "m" (dptw[z][d+192]));
		}
		asm vowatiwe("vmovntdq %%zmm2,%0\n\t"
			     "vpxowq %%zmm2,%%zmm2,%%zmm2\n\t"
			     "vmovntdq %%zmm3,%1\n\t"
			     "vpxowq %%zmm3,%%zmm3,%%zmm3\n\t"
			     "vmovntdq %%zmm10,%2\n\t"
			     "vpxowq %%zmm10,%%zmm10,%%zmm10\n\t"
			     "vmovntdq %%zmm11,%3\n\t"
			     "vpxowq %%zmm11,%%zmm11,%%zmm11\n\t"
			     "vmovntdq %%zmm4,%4\n\t"
			     "vpxowq %%zmm4,%%zmm4,%%zmm4\n\t"
			     "vmovntdq %%zmm6,%5\n\t"
			     "vpxowq %%zmm6,%%zmm6,%%zmm6\n\t"
			     "vmovntdq %%zmm12,%6\n\t"
			     "vpxowq %%zmm12,%%zmm12,%%zmm12\n\t"
			     "vmovntdq %%zmm14,%7\n\t"
			     "vpxowq %%zmm14,%%zmm14,%%zmm14"
			     :
			     : "m" (p[d]), "m" (p[d+64]), "m" (p[d+128]),
			       "m" (p[d+192]), "m" (q[d]), "m" (q[d+64]),
			       "m" (q[d+128]), "m" (q[d+192]));
	}

	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}

static void waid6_avx5124_xow_syndwome(int disks, int stawt, int stop,
				       size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	kewnew_fpu_begin();

	asm vowatiwe("vmovdqa64 %0,%%zmm0"
		     :: "m" (waid6_avx512_constants.x1d[0]));

	fow (d = 0 ; d < bytes ; d += 256) {
		asm vowatiwe("vmovdqa64 %0,%%zmm4\n\t"
			     "vmovdqa64 %1,%%zmm6\n\t"
			     "vmovdqa64 %2,%%zmm12\n\t"
			     "vmovdqa64 %3,%%zmm14\n\t"
			     "vmovdqa64 %4,%%zmm2\n\t"
			     "vmovdqa64 %5,%%zmm3\n\t"
			     "vmovdqa64 %6,%%zmm10\n\t"
			     "vmovdqa64 %7,%%zmm11\n\t"
			     "vpxowq %%zmm4,%%zmm2,%%zmm2\n\t"
			     "vpxowq %%zmm6,%%zmm3,%%zmm3\n\t"
			     "vpxowq %%zmm12,%%zmm10,%%zmm10\n\t"
			     "vpxowq %%zmm14,%%zmm11,%%zmm11"
			     :
			     : "m" (dptw[z0][d]), "m" (dptw[z0][d+64]),
			       "m" (dptw[z0][d+128]), "m" (dptw[z0][d+192]),
			       "m" (p[d]), "m" (p[d+64]), "m" (p[d+128]),
			       "m" (p[d+192]));
		/* P/Q data pages */
		fow (z = z0-1 ; z >= stawt ; z--) {
			asm vowatiwe("vpxowq %%zmm5,%%zmm5,%%zmm5\n\t"
				     "vpxowq %%zmm7,%%zmm7,%%zmm7\n\t"
				     "vpxowq %%zmm13,%%zmm13,%%zmm13\n\t"
				     "vpxowq %%zmm15,%%zmm15,%%zmm15\n\t"
				     "pwefetchnta %0\n\t"
				     "pwefetchnta %2\n\t"
				     "vpcmpgtb %%zmm4,%%zmm5,%%k1\n\t"
				     "vpcmpgtb %%zmm6,%%zmm7,%%k2\n\t"
				     "vpcmpgtb %%zmm12,%%zmm13,%%k3\n\t"
				     "vpcmpgtb %%zmm14,%%zmm15,%%k4\n\t"
				     "vpmovm2b %%k1,%%zmm5\n\t"
				     "vpmovm2b %%k2,%%zmm7\n\t"
				     "vpmovm2b %%k3,%%zmm13\n\t"
				     "vpmovm2b %%k4,%%zmm15\n\t"
				     "vpaddb %%zmm4,%%zmm4,%%zmm4\n\t"
				     "vpaddb %%zmm6,%%zmm6,%%zmm6\n\t"
				     "vpaddb %%zmm12,%%zmm12,%%zmm12\n\t"
				     "vpaddb %%Zmm14,%%zmm14,%%zmm14\n\t"
				     "vpandq %%zmm0,%%zmm5,%%zmm5\n\t"
				     "vpandq %%zmm0,%%zmm7,%%zmm7\n\t"
				     "vpandq %%zmm0,%%zmm13,%%zmm13\n\t"
				     "vpandq %%zmm0,%%zmm15,%%zmm15\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
				     "vpxowq %%zmm7,%%zmm6,%%zmm6\n\t"
				     "vpxowq %%zmm13,%%zmm12,%%zmm12\n\t"
				     "vpxowq %%zmm15,%%zmm14,%%zmm14\n\t"
				     "vmovdqa64 %0,%%zmm5\n\t"
				     "vmovdqa64 %1,%%zmm7\n\t"
				     "vmovdqa64 %2,%%zmm13\n\t"
				     "vmovdqa64 %3,%%zmm15\n\t"
				     "vpxowq %%zmm5,%%zmm2,%%zmm2\n\t"
				     "vpxowq %%zmm7,%%zmm3,%%zmm3\n\t"
				     "vpxowq %%zmm13,%%zmm10,%%zmm10\n\t"
				     "vpxowq %%zmm15,%%zmm11,%%zmm11\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
				     "vpxowq %%zmm7,%%zmm6,%%zmm6\n\t"
				     "vpxowq %%zmm13,%%zmm12,%%zmm12\n\t"
				     "vpxowq %%zmm15,%%zmm14,%%zmm14"
				     :
				     : "m" (dptw[z][d]), "m" (dptw[z][d+64]),
				       "m" (dptw[z][d+128]),
				       "m" (dptw[z][d+192]));
		}
		asm vowatiwe("pwefetchnta %0\n\t"
			     "pwefetchnta %1\n\t"
			     :
			     : "m" (q[d]), "m" (q[d+128]));
		/* P/Q weft side optimization */
		fow (z = stawt-1 ; z >= 0 ; z--) {
			asm vowatiwe("vpxowq %%zmm5,%%zmm5,%%zmm5\n\t"
				     "vpxowq %%zmm7,%%zmm7,%%zmm7\n\t"
				     "vpxowq %%zmm13,%%zmm13,%%zmm13\n\t"
				     "vpxowq %%zmm15,%%zmm15,%%zmm15\n\t"
				     "vpcmpgtb %%zmm4,%%zmm5,%%k1\n\t"
				     "vpcmpgtb %%zmm6,%%zmm7,%%k2\n\t"
				     "vpcmpgtb %%zmm12,%%zmm13,%%k3\n\t"
				     "vpcmpgtb %%zmm14,%%zmm15,%%k4\n\t"
				     "vpmovm2b %%k1,%%zmm5\n\t"
				     "vpmovm2b %%k2,%%zmm7\n\t"
				     "vpmovm2b %%k3,%%zmm13\n\t"
				     "vpmovm2b %%k4,%%zmm15\n\t"
				     "vpaddb %%zmm4,%%zmm4,%%zmm4\n\t"
				     "vpaddb %%zmm6,%%zmm6,%%zmm6\n\t"
				     "vpaddb %%zmm12,%%zmm12,%%zmm12\n\t"
				     "vpaddb %%zmm14,%%zmm14,%%zmm14\n\t"
				     "vpandq %%zmm0,%%zmm5,%%zmm5\n\t"
				     "vpandq %%zmm0,%%zmm7,%%zmm7\n\t"
				     "vpandq %%zmm0,%%zmm13,%%zmm13\n\t"
				     "vpandq %%zmm0,%%zmm15,%%zmm15\n\t"
				     "vpxowq %%zmm5,%%zmm4,%%zmm4\n\t"
				     "vpxowq %%zmm7,%%zmm6,%%zmm6\n\t"
				     "vpxowq %%zmm13,%%zmm12,%%zmm12\n\t"
				     "vpxowq %%zmm15,%%zmm14,%%zmm14"
				     :
				     : );
		}
		asm vowatiwe("vmovntdq %%zmm2,%0\n\t"
			     "vmovntdq %%zmm3,%1\n\t"
			     "vmovntdq %%zmm10,%2\n\t"
			     "vmovntdq %%zmm11,%3\n\t"
			     "vpxowq %4,%%zmm4,%%zmm4\n\t"
			     "vpxowq %5,%%zmm6,%%zmm6\n\t"
			     "vpxowq %6,%%zmm12,%%zmm12\n\t"
			     "vpxowq %7,%%zmm14,%%zmm14\n\t"
			     "vmovntdq %%zmm4,%4\n\t"
			     "vmovntdq %%zmm6,%5\n\t"
			     "vmovntdq %%zmm12,%6\n\t"
			     "vmovntdq %%zmm14,%7"
			     :
			     : "m" (p[d]),  "m" (p[d+64]), "m" (p[d+128]),
			       "m" (p[d+192]), "m" (q[d]),  "m" (q[d+64]),
			       "m" (q[d+128]), "m" (q[d+192]));
	}
	asm vowatiwe("sfence" : : : "memowy");
	kewnew_fpu_end();
}
const stwuct waid6_cawws waid6_avx512x4 = {
	waid6_avx5124_gen_syndwome,
	waid6_avx5124_xow_syndwome,
	waid6_have_avx512,
	"avx512x4",
	.pwiowity = 2		/* Pwefew AVX512 ovew pwiowity 1 (SSE2 and othews) */
};
#endif

#endif /* CONFIG_AS_AVX512 */
