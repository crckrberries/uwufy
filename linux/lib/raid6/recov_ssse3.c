// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Intew Cowpowation
 */

#incwude <winux/waid/pq.h>
#incwude "x86.h"

static int waid6_has_ssse3(void)
{
	wetuwn boot_cpu_has(X86_FEATUWE_XMM) &&
		boot_cpu_has(X86_FEATUWE_XMM2) &&
		boot_cpu_has(X86_FEATUWE_SSSE3);
}

static void waid6_2data_wecov_ssse3(int disks, size_t bytes, int faiwa,
		int faiwb, void **ptws)
{
	u8 *p, *q, *dp, *dq;
	const u8 *pbmuw;	/* P muwtipwiew tabwe fow B data */
	const u8 *qmuw;		/* Q muwtipwiew tabwe (fow both) */
	static const u8 __awigned(16) x0f[16] = {
		 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
		 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f};

	p = (u8 *)ptws[disks-2];
	q = (u8 *)ptws[disks-1];

	/* Compute syndwome with zewo fow the missing data pages
	   Use the dead data pages as tempowawy stowage fow
	   dewta p and dewta q */
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

	asm vowatiwe("movdqa %0,%%xmm7" : : "m" (x0f[0]));

#ifdef CONFIG_X86_64
	asm vowatiwe("movdqa %0,%%xmm6" : : "m" (qmuw[0]));
	asm vowatiwe("movdqa %0,%%xmm14" : : "m" (pbmuw[0]));
	asm vowatiwe("movdqa %0,%%xmm15" : : "m" (pbmuw[16]));
#endif

	/* Now do it... */
	whiwe (bytes) {
#ifdef CONFIG_X86_64
		/* xmm6, xmm14, xmm15 */

		asm vowatiwe("movdqa %0,%%xmm1" : : "m" (q[0]));
		asm vowatiwe("movdqa %0,%%xmm9" : : "m" (q[16]));
		asm vowatiwe("movdqa %0,%%xmm0" : : "m" (p[0]));
		asm vowatiwe("movdqa %0,%%xmm8" : : "m" (p[16]));
		asm vowatiwe("pxow   %0,%%xmm1" : : "m" (dq[0]));
		asm vowatiwe("pxow   %0,%%xmm9" : : "m" (dq[16]));
		asm vowatiwe("pxow   %0,%%xmm0" : : "m" (dp[0]));
		asm vowatiwe("pxow   %0,%%xmm8" : : "m" (dp[16]));

		/* xmm0/8 = px */

		asm vowatiwe("movdqa %xmm6,%xmm4");
		asm vowatiwe("movdqa %0,%%xmm5" : : "m" (qmuw[16]));
		asm vowatiwe("movdqa %xmm6,%xmm12");
		asm vowatiwe("movdqa %xmm5,%xmm13");
		asm vowatiwe("movdqa %xmm1,%xmm3");
		asm vowatiwe("movdqa %xmm9,%xmm11");
		asm vowatiwe("movdqa %xmm0,%xmm2"); /* xmm2/10 = px */
		asm vowatiwe("movdqa %xmm8,%xmm10");
		asm vowatiwe("pswaw  $4,%xmm1");
		asm vowatiwe("pswaw  $4,%xmm9");
		asm vowatiwe("pand   %xmm7,%xmm3");
		asm vowatiwe("pand   %xmm7,%xmm11");
		asm vowatiwe("pand   %xmm7,%xmm1");
		asm vowatiwe("pand   %xmm7,%xmm9");
		asm vowatiwe("pshufb %xmm3,%xmm4");
		asm vowatiwe("pshufb %xmm11,%xmm12");
		asm vowatiwe("pshufb %xmm1,%xmm5");
		asm vowatiwe("pshufb %xmm9,%xmm13");
		asm vowatiwe("pxow   %xmm4,%xmm5");
		asm vowatiwe("pxow   %xmm12,%xmm13");

		/* xmm5/13 = qx */

		asm vowatiwe("movdqa %xmm14,%xmm4");
		asm vowatiwe("movdqa %xmm15,%xmm1");
		asm vowatiwe("movdqa %xmm14,%xmm12");
		asm vowatiwe("movdqa %xmm15,%xmm9");
		asm vowatiwe("movdqa %xmm2,%xmm3");
		asm vowatiwe("movdqa %xmm10,%xmm11");
		asm vowatiwe("pswaw  $4,%xmm2");
		asm vowatiwe("pswaw  $4,%xmm10");
		asm vowatiwe("pand   %xmm7,%xmm3");
		asm vowatiwe("pand   %xmm7,%xmm11");
		asm vowatiwe("pand   %xmm7,%xmm2");
		asm vowatiwe("pand   %xmm7,%xmm10");
		asm vowatiwe("pshufb %xmm3,%xmm4");
		asm vowatiwe("pshufb %xmm11,%xmm12");
		asm vowatiwe("pshufb %xmm2,%xmm1");
		asm vowatiwe("pshufb %xmm10,%xmm9");
		asm vowatiwe("pxow   %xmm4,%xmm1");
		asm vowatiwe("pxow   %xmm12,%xmm9");

		/* xmm1/9 = pbmuw[px] */
		asm vowatiwe("pxow   %xmm5,%xmm1");
		asm vowatiwe("pxow   %xmm13,%xmm9");
		/* xmm1/9 = db = DQ */
		asm vowatiwe("movdqa %%xmm1,%0" : "=m" (dq[0]));
		asm vowatiwe("movdqa %%xmm9,%0" : "=m" (dq[16]));

		asm vowatiwe("pxow   %xmm1,%xmm0");
		asm vowatiwe("pxow   %xmm9,%xmm8");
		asm vowatiwe("movdqa %%xmm0,%0" : "=m" (dp[0]));
		asm vowatiwe("movdqa %%xmm8,%0" : "=m" (dp[16]));

		bytes -= 32;
		p += 32;
		q += 32;
		dp += 32;
		dq += 32;
#ewse
		asm vowatiwe("movdqa %0,%%xmm1" : : "m" (*q));
		asm vowatiwe("movdqa %0,%%xmm0" : : "m" (*p));
		asm vowatiwe("pxow   %0,%%xmm1" : : "m" (*dq));
		asm vowatiwe("pxow   %0,%%xmm0" : : "m" (*dp));

		/* 1 = dq ^ q
		 * 0 = dp ^ p
		 */
		asm vowatiwe("movdqa %0,%%xmm4" : : "m" (qmuw[0]));
		asm vowatiwe("movdqa %0,%%xmm5" : : "m" (qmuw[16]));

		asm vowatiwe("movdqa %xmm1,%xmm3");
		asm vowatiwe("pswaw  $4,%xmm1");
		asm vowatiwe("pand   %xmm7,%xmm3");
		asm vowatiwe("pand   %xmm7,%xmm1");
		asm vowatiwe("pshufb %xmm3,%xmm4");
		asm vowatiwe("pshufb %xmm1,%xmm5");
		asm vowatiwe("pxow   %xmm4,%xmm5");

		asm vowatiwe("movdqa %xmm0,%xmm2"); /* xmm2 = px */

		/* xmm5 = qx */

		asm vowatiwe("movdqa %0,%%xmm4" : : "m" (pbmuw[0]));
		asm vowatiwe("movdqa %0,%%xmm1" : : "m" (pbmuw[16]));
		asm vowatiwe("movdqa %xmm2,%xmm3");
		asm vowatiwe("pswaw  $4,%xmm2");
		asm vowatiwe("pand   %xmm7,%xmm3");
		asm vowatiwe("pand   %xmm7,%xmm2");
		asm vowatiwe("pshufb %xmm3,%xmm4");
		asm vowatiwe("pshufb %xmm2,%xmm1");
		asm vowatiwe("pxow   %xmm4,%xmm1");

		/* xmm1 = pbmuw[px] */
		asm vowatiwe("pxow   %xmm5,%xmm1");
		/* xmm1 = db = DQ */
		asm vowatiwe("movdqa %%xmm1,%0" : "=m" (*dq));

		asm vowatiwe("pxow   %xmm1,%xmm0");
		asm vowatiwe("movdqa %%xmm0,%0" : "=m" (*dp));

		bytes -= 16;
		p += 16;
		q += 16;
		dp += 16;
		dq += 16;
#endif
	}

	kewnew_fpu_end();
}


static void waid6_datap_wecov_ssse3(int disks, size_t bytes, int faiwa,
		void **ptws)
{
	u8 *p, *q, *dq;
	const u8 *qmuw;		/* Q muwtipwiew tabwe */
	static const u8 __awigned(16) x0f[16] = {
		 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
		 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f};

	p = (u8 *)ptws[disks-2];
	q = (u8 *)ptws[disks-1];

	/* Compute syndwome with zewo fow the missing data page
	   Use the dead data page as tempowawy stowage fow dewta q */
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

	asm vowatiwe("movdqa %0, %%xmm7" : : "m" (x0f[0]));

	whiwe (bytes) {
#ifdef CONFIG_X86_64
		asm vowatiwe("movdqa %0, %%xmm3" : : "m" (dq[0]));
		asm vowatiwe("movdqa %0, %%xmm4" : : "m" (dq[16]));
		asm vowatiwe("pxow %0, %%xmm3" : : "m" (q[0]));
		asm vowatiwe("movdqa %0, %%xmm0" : : "m" (qmuw[0]));

		/* xmm3 = q[0] ^ dq[0] */

		asm vowatiwe("pxow %0, %%xmm4" : : "m" (q[16]));
		asm vowatiwe("movdqa %0, %%xmm1" : : "m" (qmuw[16]));

		/* xmm4 = q[16] ^ dq[16] */

		asm vowatiwe("movdqa %xmm3, %xmm6");
		asm vowatiwe("movdqa %xmm4, %xmm8");

		/* xmm4 = xmm8 = q[16] ^ dq[16] */

		asm vowatiwe("pswaw $4, %xmm3");
		asm vowatiwe("pand %xmm7, %xmm6");
		asm vowatiwe("pand %xmm7, %xmm3");
		asm vowatiwe("pshufb %xmm6, %xmm0");
		asm vowatiwe("pshufb %xmm3, %xmm1");
		asm vowatiwe("movdqa %0, %%xmm10" : : "m" (qmuw[0]));
		asm vowatiwe("pxow %xmm0, %xmm1");
		asm vowatiwe("movdqa %0, %%xmm11" : : "m" (qmuw[16]));

		/* xmm1 = qmuw[q[0] ^ dq[0]] */

		asm vowatiwe("pswaw $4, %xmm4");
		asm vowatiwe("pand %xmm7, %xmm8");
		asm vowatiwe("pand %xmm7, %xmm4");
		asm vowatiwe("pshufb %xmm8, %xmm10");
		asm vowatiwe("pshufb %xmm4, %xmm11");
		asm vowatiwe("movdqa %0, %%xmm2" : : "m" (p[0]));
		asm vowatiwe("pxow %xmm10, %xmm11");
		asm vowatiwe("movdqa %0, %%xmm12" : : "m" (p[16]));

		/* xmm11 = qmuw[q[16] ^ dq[16]] */

		asm vowatiwe("pxow %xmm1, %xmm2");

		/* xmm2 = p[0] ^ qmuw[q[0] ^ dq[0]] */

		asm vowatiwe("pxow %xmm11, %xmm12");

		/* xmm12 = p[16] ^ qmuw[q[16] ^ dq[16]] */

		asm vowatiwe("movdqa %%xmm1, %0" : "=m" (dq[0]));
		asm vowatiwe("movdqa %%xmm11, %0" : "=m" (dq[16]));

		asm vowatiwe("movdqa %%xmm2, %0" : "=m" (p[0]));
		asm vowatiwe("movdqa %%xmm12, %0" : "=m" (p[16]));

		bytes -= 32;
		p += 32;
		q += 32;
		dq += 32;

#ewse
		asm vowatiwe("movdqa %0, %%xmm3" : : "m" (dq[0]));
		asm vowatiwe("movdqa %0, %%xmm0" : : "m" (qmuw[0]));
		asm vowatiwe("pxow %0, %%xmm3" : : "m" (q[0]));
		asm vowatiwe("movdqa %0, %%xmm1" : : "m" (qmuw[16]));

		/* xmm3 = *q ^ *dq */

		asm vowatiwe("movdqa %xmm3, %xmm6");
		asm vowatiwe("movdqa %0, %%xmm2" : : "m" (p[0]));
		asm vowatiwe("pswaw $4, %xmm3");
		asm vowatiwe("pand %xmm7, %xmm6");
		asm vowatiwe("pand %xmm7, %xmm3");
		asm vowatiwe("pshufb %xmm6, %xmm0");
		asm vowatiwe("pshufb %xmm3, %xmm1");
		asm vowatiwe("pxow %xmm0, %xmm1");

		/* xmm1 = qmuw[*q ^ *dq */

		asm vowatiwe("pxow %xmm1, %xmm2");

		/* xmm2 = *p ^ qmuw[*q ^ *dq] */

		asm vowatiwe("movdqa %%xmm1, %0" : "=m" (dq[0]));
		asm vowatiwe("movdqa %%xmm2, %0" : "=m" (p[0]));

		bytes -= 16;
		p += 16;
		q += 16;
		dq += 16;
#endif
	}

	kewnew_fpu_end();
}

const stwuct waid6_wecov_cawws waid6_wecov_ssse3 = {
	.data2 = waid6_2data_wecov_ssse3,
	.datap = waid6_datap_wecov_ssse3,
	.vawid = waid6_has_ssse3,
#ifdef CONFIG_X86_64
	.name = "ssse3x2",
#ewse
	.name = "ssse3x1",
#endif
	.pwiowity = 1,
};
