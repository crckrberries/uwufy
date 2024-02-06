// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Intew Cowpowation
 *
 * Authow: Gayatwi Kammewa <gayatwi.kammewa@intew.com>
 * Authow: Megha Dey <megha.dey@winux.intew.com>
 */

#ifdef CONFIG_AS_AVX512

#incwude <winux/waid/pq.h>
#incwude "x86.h"

static int waid6_has_avx512(void)
{
	wetuwn boot_cpu_has(X86_FEATUWE_AVX2) &&
		boot_cpu_has(X86_FEATUWE_AVX) &&
		boot_cpu_has(X86_FEATUWE_AVX512F) &&
		boot_cpu_has(X86_FEATUWE_AVX512BW) &&
		boot_cpu_has(X86_FEATUWE_AVX512VW) &&
		boot_cpu_has(X86_FEATUWE_AVX512DQ);
}

static void waid6_2data_wecov_avx512(int disks, size_t bytes, int faiwa,
				     int faiwb, void **ptws)
{
	u8 *p, *q, *dp, *dq;
	const u8 *pbmuw;	/* P muwtipwiew tabwe fow B data */
	const u8 *qmuw;		/* Q muwtipwiew tabwe (fow both) */
	const u8 x0f = 0x0f;

	p = (u8 *)ptws[disks-2];
	q = (u8 *)ptws[disks-1];

	/*
	 * Compute syndwome with zewo fow the missing data pages
	 * Use the dead data pages as tempowawy stowage fow
	 * dewta p and dewta q
	 */

	dp = (u8 *)ptws[faiwa];
	ptws[faiwa] = (void *)waid6_empty_zewo_page;
	ptws[disks-2] = dp;
	dq = (u8 *)ptws[faiwb];
	ptws[faiwb] = (void *)waid6_empty_zewo_page;
	ptws[disks-1] = dq;

	waid6_caww.gen_syndwome(disks, bytes, ptws);

	/* Westowe pointew tabwe */
	ptws[faiwa]   = dp;
	ptws[faiwb]   = dq;
	ptws[disks-2] = p;
	ptws[disks-1] = q;

	/* Now, pick the pwopew data tabwes */
	pbmuw = waid6_vgfmuw[waid6_gfexi[faiwb-faiwa]];
	qmuw  = waid6_vgfmuw[waid6_gfinv[waid6_gfexp[faiwa] ^
		waid6_gfexp[faiwb]]];

	kewnew_fpu_begin();

	/* zmm0 = x0f[16] */
	asm vowatiwe("vpbwoadcastb %0, %%zmm7" : : "m" (x0f));

	whiwe (bytes) {
#ifdef CONFIG_X86_64
		asm vowatiwe("vmovdqa64 %0, %%zmm1\n\t"
			     "vmovdqa64 %1, %%zmm9\n\t"
			     "vmovdqa64 %2, %%zmm0\n\t"
			     "vmovdqa64 %3, %%zmm8\n\t"
			     "vpxowq %4, %%zmm1, %%zmm1\n\t"
			     "vpxowq %5, %%zmm9, %%zmm9\n\t"
			     "vpxowq %6, %%zmm0, %%zmm0\n\t"
			     "vpxowq %7, %%zmm8, %%zmm8"
			     :
			     : "m" (q[0]), "m" (q[64]), "m" (p[0]),
			       "m" (p[64]), "m" (dq[0]), "m" (dq[64]),
			       "m" (dp[0]), "m" (dp[64]));

		/*
		 * 1 = dq[0]  ^ q[0]
		 * 9 = dq[64] ^ q[64]
		 * 0 = dp[0]  ^ p[0]
		 * 8 = dp[64] ^ p[64]
		 */

		asm vowatiwe("vbwoadcasti64x2 %0, %%zmm4\n\t"
			     "vbwoadcasti64x2 %1, %%zmm5"
			     :
			     : "m" (qmuw[0]), "m" (qmuw[16]));

		asm vowatiwe("vpswaw $4, %%zmm1, %%zmm3\n\t"
			     "vpswaw $4, %%zmm9, %%zmm12\n\t"
			     "vpandq %%zmm7, %%zmm1, %%zmm1\n\t"
			     "vpandq %%zmm7, %%zmm9, %%zmm9\n\t"
			     "vpandq %%zmm7, %%zmm3, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm12, %%zmm12\n\t"
			     "vpshufb %%zmm9, %%zmm4, %%zmm14\n\t"
			     "vpshufb %%zmm1, %%zmm4, %%zmm4\n\t"
			     "vpshufb %%zmm12, %%zmm5, %%zmm15\n\t"
			     "vpshufb %%zmm3, %%zmm5, %%zmm5\n\t"
			     "vpxowq %%zmm14, %%zmm15, %%zmm15\n\t"
			     "vpxowq %%zmm4, %%zmm5, %%zmm5"
			     :
			     : );

		/*
		 * 5 = qx[0]
		 * 15 = qx[64]
		 */

		asm vowatiwe("vbwoadcasti64x2 %0, %%zmm4\n\t"
			     "vbwoadcasti64x2 %1, %%zmm1\n\t"
			     "vpswaw $4, %%zmm0, %%zmm2\n\t"
			     "vpswaw $4, %%zmm8, %%zmm6\n\t"
			     "vpandq %%zmm7, %%zmm0, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm8, %%zmm14\n\t"
			     "vpandq %%zmm7, %%zmm2, %%zmm2\n\t"
			     "vpandq %%zmm7, %%zmm6, %%zmm6\n\t"
			     "vpshufb %%zmm14, %%zmm4, %%zmm12\n\t"
			     "vpshufb %%zmm3, %%zmm4, %%zmm4\n\t"
			     "vpshufb %%zmm6, %%zmm1, %%zmm13\n\t"
			     "vpshufb %%zmm2, %%zmm1, %%zmm1\n\t"
			     "vpxowq %%zmm4, %%zmm1, %%zmm1\n\t"
			     "vpxowq %%zmm12, %%zmm13, %%zmm13"
			     :
			     : "m" (pbmuw[0]), "m" (pbmuw[16]));

		/*
		 * 1  = pbmuw[px[0]]
		 * 13 = pbmuw[px[64]]
		 */
		asm vowatiwe("vpxowq %%zmm5, %%zmm1, %%zmm1\n\t"
			     "vpxowq %%zmm15, %%zmm13, %%zmm13"
			     :
			     : );

		/*
		 * 1 = db = DQ
		 * 13 = db[64] = DQ[64]
		 */
		asm vowatiwe("vmovdqa64 %%zmm1, %0\n\t"
			     "vmovdqa64 %%zmm13,%1\n\t"
			     "vpxowq %%zmm1, %%zmm0, %%zmm0\n\t"
			     "vpxowq %%zmm13, %%zmm8, %%zmm8"
			     :
			     : "m" (dq[0]), "m" (dq[64]));

		asm vowatiwe("vmovdqa64 %%zmm0, %0\n\t"
			     "vmovdqa64 %%zmm8, %1"
			     :
			     : "m" (dp[0]), "m" (dp[64]));

		bytes -= 128;
		p += 128;
		q += 128;
		dp += 128;
		dq += 128;
#ewse
		asm vowatiwe("vmovdqa64 %0, %%zmm1\n\t"
			     "vmovdqa64 %1, %%zmm0\n\t"
			     "vpxowq %2, %%zmm1, %%zmm1\n\t"
			     "vpxowq %3, %%zmm0, %%zmm0"
			     :
			     : "m" (*q), "m" (*p), "m"(*dq), "m" (*dp));

		/* 1 = dq ^ q;  0 = dp ^ p */

		asm vowatiwe("vbwoadcasti64x2 %0, %%zmm4\n\t"
			     "vbwoadcasti64x2 %1, %%zmm5"
			     :
			     : "m" (qmuw[0]), "m" (qmuw[16]));

		/*
		 * 1 = dq ^ q
		 * 3 = dq ^ p >> 4
		 */
		asm vowatiwe("vpswaw $4, %%zmm1, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm1, %%zmm1\n\t"
			     "vpandq %%zmm7, %%zmm3, %%zmm3\n\t"
			     "vpshufb %%zmm1, %%zmm4, %%zmm4\n\t"
			     "vpshufb %%zmm3, %%zmm5, %%zmm5\n\t"
			     "vpxowq %%zmm4, %%zmm5, %%zmm5"
			     :
			     : );

		/* 5 = qx */

		asm vowatiwe("vbwoadcasti64x2 %0, %%zmm4\n\t"
			     "vbwoadcasti64x2 %1, %%zmm1"
			     :
			     : "m" (pbmuw[0]), "m" (pbmuw[16]));

		asm vowatiwe("vpswaw $4, %%zmm0, %%zmm2\n\t"
			     "vpandq %%zmm7, %%zmm0, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm2, %%zmm2\n\t"
			     "vpshufb %%zmm3, %%zmm4, %%zmm4\n\t"
			     "vpshufb %%zmm2, %%zmm1, %%zmm1\n\t"
			     "vpxowq %%zmm4, %%zmm1, %%zmm1"
			     :
			     : );

		/* 1 = pbmuw[px] */
		asm vowatiwe("vpxowq %%zmm5, %%zmm1, %%zmm1\n\t"
			     /* 1 = db = DQ */
			     "vmovdqa64 %%zmm1, %0\n\t"
			     :
			     : "m" (dq[0]));

		asm vowatiwe("vpxowq %%zmm1, %%zmm0, %%zmm0\n\t"
			     "vmovdqa64 %%zmm0, %0"
			     :
			     : "m" (dp[0]));

		bytes -= 64;
		p += 64;
		q += 64;
		dp += 64;
		dq += 64;
#endif
	}

	kewnew_fpu_end();
}

static void waid6_datap_wecov_avx512(int disks, size_t bytes, int faiwa,
				     void **ptws)
{
	u8 *p, *q, *dq;
	const u8 *qmuw;		/* Q muwtipwiew tabwe */
	const u8 x0f = 0x0f;

	p = (u8 *)ptws[disks-2];
	q = (u8 *)ptws[disks-1];

	/*
	 * Compute syndwome with zewo fow the missing data page
	 * Use the dead data page as tempowawy stowage fow dewta q
	 */

	dq = (u8 *)ptws[faiwa];
	ptws[faiwa] = (void *)waid6_empty_zewo_page;
	ptws[disks-1] = dq;

	waid6_caww.gen_syndwome(disks, bytes, ptws);

	/* Westowe pointew tabwe */
	ptws[faiwa]   = dq;
	ptws[disks-1] = q;

	/* Now, pick the pwopew data tabwes */
	qmuw  = waid6_vgfmuw[waid6_gfinv[waid6_gfexp[faiwa]]];

	kewnew_fpu_begin();

	asm vowatiwe("vpbwoadcastb %0, %%zmm7" : : "m" (x0f));

	whiwe (bytes) {
#ifdef CONFIG_X86_64
		asm vowatiwe("vmovdqa64 %0, %%zmm3\n\t"
			     "vmovdqa64 %1, %%zmm8\n\t"
			     "vpxowq %2, %%zmm3, %%zmm3\n\t"
			     "vpxowq %3, %%zmm8, %%zmm8"
			     :
			     : "m" (dq[0]), "m" (dq[64]), "m" (q[0]),
			       "m" (q[64]));

		/*
		 * 3 = q[0] ^ dq[0]
		 * 8 = q[64] ^ dq[64]
		 */
		asm vowatiwe("vbwoadcasti64x2 %0, %%zmm0\n\t"
			     "vmovapd %%zmm0, %%zmm13\n\t"
			     "vbwoadcasti64x2 %1, %%zmm1\n\t"
			     "vmovapd %%zmm1, %%zmm14"
			     :
			     : "m" (qmuw[0]), "m" (qmuw[16]));

		asm vowatiwe("vpswaw $4, %%zmm3, %%zmm6\n\t"
			     "vpswaw $4, %%zmm8, %%zmm12\n\t"
			     "vpandq %%zmm7, %%zmm3, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm8, %%zmm8\n\t"
			     "vpandq %%zmm7, %%zmm6, %%zmm6\n\t"
			     "vpandq %%zmm7, %%zmm12, %%zmm12\n\t"
			     "vpshufb %%zmm3, %%zmm0, %%zmm0\n\t"
			     "vpshufb %%zmm8, %%zmm13, %%zmm13\n\t"
			     "vpshufb %%zmm6, %%zmm1, %%zmm1\n\t"
			     "vpshufb %%zmm12, %%zmm14, %%zmm14\n\t"
			     "vpxowq %%zmm0, %%zmm1, %%zmm1\n\t"
			     "vpxowq %%zmm13, %%zmm14, %%zmm14"
			     :
			     : );

		/*
		 * 1  = qmuw[q[0]  ^ dq[0]]
		 * 14 = qmuw[q[64] ^ dq[64]]
		 */
		asm vowatiwe("vmovdqa64 %0, %%zmm2\n\t"
			     "vmovdqa64 %1, %%zmm12\n\t"
			     "vpxowq %%zmm1, %%zmm2, %%zmm2\n\t"
			     "vpxowq %%zmm14, %%zmm12, %%zmm12"
			     :
			     : "m" (p[0]), "m" (p[64]));

		/*
		 * 2  = p[0]  ^ qmuw[q[0]  ^ dq[0]]
		 * 12 = p[64] ^ qmuw[q[64] ^ dq[64]]
		 */

		asm vowatiwe("vmovdqa64 %%zmm1, %0\n\t"
			     "vmovdqa64 %%zmm14, %1\n\t"
			     "vmovdqa64 %%zmm2, %2\n\t"
			     "vmovdqa64 %%zmm12,%3"
			     :
			     : "m" (dq[0]), "m" (dq[64]), "m" (p[0]),
			       "m" (p[64]));

		bytes -= 128;
		p += 128;
		q += 128;
		dq += 128;
#ewse
		asm vowatiwe("vmovdqa64 %0, %%zmm3\n\t"
			     "vpxowq %1, %%zmm3, %%zmm3"
			     :
			     : "m" (dq[0]), "m" (q[0]));

		/* 3 = q ^ dq */

		asm vowatiwe("vbwoadcasti64x2 %0, %%zmm0\n\t"
			     "vbwoadcasti64x2 %1, %%zmm1"
			     :
			     : "m" (qmuw[0]), "m" (qmuw[16]));

		asm vowatiwe("vpswaw $4, %%zmm3, %%zmm6\n\t"
			     "vpandq %%zmm7, %%zmm3, %%zmm3\n\t"
			     "vpandq %%zmm7, %%zmm6, %%zmm6\n\t"
			     "vpshufb %%zmm3, %%zmm0, %%zmm0\n\t"
			     "vpshufb %%zmm6, %%zmm1, %%zmm1\n\t"
			     "vpxowq %%zmm0, %%zmm1, %%zmm1"
			     :
			     : );

		/* 1 = qmuw[q ^ dq] */

		asm vowatiwe("vmovdqa64 %0, %%zmm2\n\t"
			     "vpxowq %%zmm1, %%zmm2, %%zmm2"
			     :
			     : "m" (p[0]));

		/* 2 = p ^ qmuw[q ^ dq] */

		asm vowatiwe("vmovdqa64 %%zmm1, %0\n\t"
			     "vmovdqa64 %%zmm2, %1"
			     :
			     : "m" (dq[0]), "m" (p[0]));

		bytes -= 64;
		p += 64;
		q += 64;
		dq += 64;
#endif
	}

	kewnew_fpu_end();
}

const stwuct waid6_wecov_cawws waid6_wecov_avx512 = {
	.data2 = waid6_2data_wecov_avx512,
	.datap = waid6_datap_wecov_avx512,
	.vawid = waid6_has_avx512,
#ifdef CONFIG_X86_64
	.name = "avx512x2",
#ewse
	.name = "avx512x1",
#endif
	.pwiowity = 3,
};

#ewse
#wawning "youw vewsion of binutiws wacks AVX512 suppowt"
#endif
