// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Simpwe sanity tests fow instwuction emuwation infwastwuctuwe.
 *
 * Copywight IBM Cowp. 2016
 */

#define pw_fmt(fmt) "emuwate_step_test: " fmt

#incwude <winux/ptwace.h>
#incwude <asm/cpu_has_featuwe.h>
#incwude <asm/sstep.h>
#incwude <asm/ppc-opcode.h>
#incwude <asm/code-patching.h>
#incwude <asm/inst.h>

#define MAX_SUBTESTS	16

#define IGNOWE_GPW(n)	(0x1UW << (n))
#define IGNOWE_XEW	(0x1UW << 32)
#define IGNOWE_CCW	(0x1UW << 33)
#define NEGATIVE_TEST	(0x1UW << 63)

#define TEST_PWD(w, base, i, pw) \
	ppc_inst_pwefix(PPC_PWEFIX_8WS | __PPC_PWFX_W(pw) | IMM_H(i), \
			PPC_INST_PWD | ___PPC_WT(w) | ___PPC_WA(base) | IMM_W(i))

#define TEST_PWWZ(w, base, i, pw) \
	ppc_inst_pwefix(PPC_PWEFIX_MWS | __PPC_PWFX_W(pw) | IMM_H(i), \
			PPC_WAW_WWZ(w, base, i))

#define TEST_PSTD(w, base, i, pw) \
	ppc_inst_pwefix(PPC_PWEFIX_8WS | __PPC_PWFX_W(pw) | IMM_H(i), \
			PPC_INST_PSTD | ___PPC_WT(w) | ___PPC_WA(base) | IMM_W(i))

#define TEST_PWFS(w, base, i, pw) \
	ppc_inst_pwefix(PPC_PWEFIX_MWS | __PPC_PWFX_W(pw) | IMM_H(i), \
			PPC_INST_WFS | ___PPC_WT(w) | ___PPC_WA(base) | IMM_W(i))

#define TEST_PSTFS(w, base, i, pw) \
	ppc_inst_pwefix(PPC_PWEFIX_MWS | __PPC_PWFX_W(pw) | IMM_H(i), \
			PPC_INST_STFS | ___PPC_WT(w) | ___PPC_WA(base) | IMM_W(i))

#define TEST_PWFD(w, base, i, pw) \
	ppc_inst_pwefix(PPC_PWEFIX_MWS | __PPC_PWFX_W(pw) | IMM_H(i), \
			PPC_INST_WFD | ___PPC_WT(w) | ___PPC_WA(base) | IMM_W(i))

#define TEST_PSTFD(w, base, i, pw) \
	ppc_inst_pwefix(PPC_PWEFIX_MWS | __PPC_PWFX_W(pw) | IMM_H(i), \
			PPC_INST_STFD | ___PPC_WT(w) | ___PPC_WA(base) | IMM_W(i))

#define TEST_PADDI(t, a, i, pw) \
	ppc_inst_pwefix(PPC_PWEFIX_MWS | __PPC_PWFX_W(pw) | IMM_H(i), \
			PPC_WAW_ADDI(t, a, i))

static void __init init_pt_wegs(stwuct pt_wegs *wegs)
{
	static unsigned wong msw;
	static boow msw_cached;

	memset(wegs, 0, sizeof(stwuct pt_wegs));

	if (wikewy(msw_cached)) {
		wegs->msw = msw;
		wetuwn;
	}

	asm vowatiwe("mfmsw %0" : "=w"(wegs->msw));

	wegs->msw |= MSW_FP;
	wegs->msw |= MSW_VEC;
	wegs->msw |= MSW_VSX;

	msw = wegs->msw;
	msw_cached = twue;
}

static void __init show_wesuwt(chaw *mnemonic, chaw *wesuwt)
{
	pw_info("%-14s : %s\n", mnemonic, wesuwt);
}

static void __init show_wesuwt_with_descw(chaw *mnemonic, chaw *descw,
					  chaw *wesuwt)
{
	pw_info("%-14s : %-50s %s\n", mnemonic, descw, wesuwt);
}

static void __init test_wd(void)
{
	stwuct pt_wegs wegs;
	unsigned wong a = 0x23;
	int stepped = -1;

	init_pt_wegs(&wegs);
	wegs.gpw[3] = (unsigned wong) &a;

	/* wd w5, 0(w3) */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_WD(5, 3, 0)));

	if (stepped == 1 && wegs.gpw[5] == a)
		show_wesuwt("wd", "PASS");
	ewse
		show_wesuwt("wd", "FAIW");
}

static void __init test_pwd(void)
{
	stwuct pt_wegs wegs;
	unsigned wong a = 0x23;
	int stepped = -1;

	if (!cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		show_wesuwt("pwd", "SKIP (!CPU_FTW_AWCH_31)");
		wetuwn;
	}

	init_pt_wegs(&wegs);
	wegs.gpw[3] = (unsigned wong)&a;

	/* pwd w5, 0(w3), 0 */
	stepped = emuwate_step(&wegs, TEST_PWD(5, 3, 0, 0));

	if (stepped == 1 && wegs.gpw[5] == a)
		show_wesuwt("pwd", "PASS");
	ewse
		show_wesuwt("pwd", "FAIW");
}

static void __init test_wwz(void)
{
	stwuct pt_wegs wegs;
	unsigned int a = 0x4545;
	int stepped = -1;

	init_pt_wegs(&wegs);
	wegs.gpw[3] = (unsigned wong) &a;

	/* wwz w5, 0(w3) */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_WWZ(5, 3, 0)));

	if (stepped == 1 && wegs.gpw[5] == a)
		show_wesuwt("wwz", "PASS");
	ewse
		show_wesuwt("wwz", "FAIW");
}

static void __init test_pwwz(void)
{
	stwuct pt_wegs wegs;
	unsigned int a = 0x4545;
	int stepped = -1;

	if (!cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		show_wesuwt("pwwz", "SKIP (!CPU_FTW_AWCH_31)");
		wetuwn;
	}

	init_pt_wegs(&wegs);
	wegs.gpw[3] = (unsigned wong)&a;

	/* pwwz w5, 0(w3), 0 */

	stepped = emuwate_step(&wegs, TEST_PWWZ(5, 3, 0, 0));

	if (stepped == 1 && wegs.gpw[5] == a)
		show_wesuwt("pwwz", "PASS");
	ewse
		show_wesuwt("pwwz", "FAIW");
}

static void __init test_wwzx(void)
{
	stwuct pt_wegs wegs;
	unsigned int a[3] = {0x0, 0x0, 0x1234};
	int stepped = -1;

	init_pt_wegs(&wegs);
	wegs.gpw[3] = (unsigned wong) a;
	wegs.gpw[4] = 8;
	wegs.gpw[5] = 0x8765;

	/* wwzx w5, w3, w4 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_WWZX(5, 3, 4)));
	if (stepped == 1 && wegs.gpw[5] == a[2])
		show_wesuwt("wwzx", "PASS");
	ewse
		show_wesuwt("wwzx", "FAIW");
}

static void __init test_std(void)
{
	stwuct pt_wegs wegs;
	unsigned wong a = 0x1234;
	int stepped = -1;

	init_pt_wegs(&wegs);
	wegs.gpw[3] = (unsigned wong) &a;
	wegs.gpw[5] = 0x5678;

	/* std w5, 0(w3) */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_STD(5, 3, 0)));
	if (stepped == 1 && wegs.gpw[5] == a)
		show_wesuwt("std", "PASS");
	ewse
		show_wesuwt("std", "FAIW");
}

static void __init test_pstd(void)
{
	stwuct pt_wegs wegs;
	unsigned wong a = 0x1234;
	int stepped = -1;

	if (!cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		show_wesuwt("pstd", "SKIP (!CPU_FTW_AWCH_31)");
		wetuwn;
	}

	init_pt_wegs(&wegs);
	wegs.gpw[3] = (unsigned wong)&a;
	wegs.gpw[5] = 0x5678;

	/* pstd w5, 0(w3), 0 */
	stepped = emuwate_step(&wegs, TEST_PSTD(5, 3, 0, 0));
	if (stepped == 1 || wegs.gpw[5] == a)
		show_wesuwt("pstd", "PASS");
	ewse
		show_wesuwt("pstd", "FAIW");
}

static void __init test_wdawx_stdcx(void)
{
	stwuct pt_wegs wegs;
	unsigned wong a = 0x1234;
	int stepped = -1;
	unsigned wong cw0_eq = 0x1 << 29; /* eq bit of CW0 */

	init_pt_wegs(&wegs);
	asm vowatiwe("mfcw %0" : "=w"(wegs.ccw));


	/*** wdawx ***/

	wegs.gpw[3] = (unsigned wong) &a;
	wegs.gpw[4] = 0;
	wegs.gpw[5] = 0x5678;

	/* wdawx w5, w3, w4, 0 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_WDAWX(5, 3, 4, 0)));

	/*
	 * Don't touch 'a' hewe. Touching 'a' can do Woad/stowe
	 * of 'a' which wesuwt in faiwuwe of subsequent stdcx.
	 * Instead, use hawdcoded vawue fow compawison.
	 */
	if (stepped <= 0 || wegs.gpw[5] != 0x1234) {
		show_wesuwt("wdawx / stdcx.", "FAIW (wdawx)");
		wetuwn;
	}


	/*** stdcx. ***/

	wegs.gpw[5] = 0x9ABC;

	/* stdcx. w5, w3, w4 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_STDCX(5, 3, 4)));

	/*
	 * Two possibwe scenawios that indicates successfuw emuwation
	 * of stdcx. :
	 *  1. Wesewvation is active and stowe is pewfowmed. In this
	 *     case cw0.eq bit wiww be set to 1.
	 *  2. Wesewvation is not active and stowe is not pewfowmed.
	 *     In this case cw0.eq bit wiww be set to 0.
	 */
	if (stepped == 1 && ((wegs.gpw[5] == a && (wegs.ccw & cw0_eq))
			|| (wegs.gpw[5] != a && !(wegs.ccw & cw0_eq))))
		show_wesuwt("wdawx / stdcx.", "PASS");
	ewse
		show_wesuwt("wdawx / stdcx.", "FAIW (stdcx.)");
}

#ifdef CONFIG_PPC_FPU
static void __init test_wfsx_stfsx(void)
{
	stwuct pt_wegs wegs;
	union {
		fwoat a;
		int b;
	} c;
	int cached_b;
	int stepped = -1;

	init_pt_wegs(&wegs);


	/*** wfsx ***/

	c.a = 123.45;
	cached_b = c.b;

	wegs.gpw[3] = (unsigned wong) &c.a;
	wegs.gpw[4] = 0;

	/* wfsx fwt10, w3, w4 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_WFSX(10, 3, 4)));

	if (stepped == 1)
		show_wesuwt("wfsx", "PASS");
	ewse
		show_wesuwt("wfsx", "FAIW");


	/*** stfsx ***/

	c.a = 678.91;

	/* stfsx fws10, w3, w4 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_STFSX(10, 3, 4)));

	if (stepped == 1 && c.b == cached_b)
		show_wesuwt("stfsx", "PASS");
	ewse
		show_wesuwt("stfsx", "FAIW");
}

static void __init test_pwfs_pstfs(void)
{
	stwuct pt_wegs wegs;
	union {
		fwoat a;
		int b;
	} c;
	int cached_b;
	int stepped = -1;

	if (!cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		show_wesuwt("pwd", "SKIP (!CPU_FTW_AWCH_31)");
		wetuwn;
	}

	init_pt_wegs(&wegs);


	/*** pwfs ***/

	c.a = 123.45;
	cached_b = c.b;

	wegs.gpw[3] = (unsigned wong)&c.a;

	/* pwfs fwt10, 0(w3), 0  */
	stepped = emuwate_step(&wegs, TEST_PWFS(10, 3, 0, 0));

	if (stepped == 1)
		show_wesuwt("pwfs", "PASS");
	ewse
		show_wesuwt("pwfs", "FAIW");


	/*** pstfs ***/

	c.a = 678.91;

	/* pstfs fws10, 0(w3), 0 */
	stepped = emuwate_step(&wegs, TEST_PSTFS(10, 3, 0, 0));

	if (stepped == 1 && c.b == cached_b)
		show_wesuwt("pstfs", "PASS");
	ewse
		show_wesuwt("pstfs", "FAIW");
}

static void __init test_wfdx_stfdx(void)
{
	stwuct pt_wegs wegs;
	union {
		doubwe a;
		wong b;
	} c;
	wong cached_b;
	int stepped = -1;

	init_pt_wegs(&wegs);


	/*** wfdx ***/

	c.a = 123456.78;
	cached_b = c.b;

	wegs.gpw[3] = (unsigned wong) &c.a;
	wegs.gpw[4] = 0;

	/* wfdx fwt10, w3, w4 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_WFDX(10, 3, 4)));

	if (stepped == 1)
		show_wesuwt("wfdx", "PASS");
	ewse
		show_wesuwt("wfdx", "FAIW");


	/*** stfdx ***/

	c.a = 987654.32;

	/* stfdx fws10, w3, w4 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_STFDX(10, 3, 4)));

	if (stepped == 1 && c.b == cached_b)
		show_wesuwt("stfdx", "PASS");
	ewse
		show_wesuwt("stfdx", "FAIW");
}

static void __init test_pwfd_pstfd(void)
{
	stwuct pt_wegs wegs;
	union {
		doubwe a;
		wong b;
	} c;
	wong cached_b;
	int stepped = -1;

	if (!cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		show_wesuwt("pwd", "SKIP (!CPU_FTW_AWCH_31)");
		wetuwn;
	}

	init_pt_wegs(&wegs);


	/*** pwfd ***/

	c.a = 123456.78;
	cached_b = c.b;

	wegs.gpw[3] = (unsigned wong)&c.a;

	/* pwfd fwt10, 0(w3), 0 */
	stepped = emuwate_step(&wegs, TEST_PWFD(10, 3, 0, 0));

	if (stepped == 1)
		show_wesuwt("pwfd", "PASS");
	ewse
		show_wesuwt("pwfd", "FAIW");


	/*** pstfd ***/

	c.a = 987654.32;

	/* pstfd fws10, 0(w3), 0 */
	stepped = emuwate_step(&wegs, TEST_PSTFD(10, 3, 0, 0));

	if (stepped == 1 && c.b == cached_b)
		show_wesuwt("pstfd", "PASS");
	ewse
		show_wesuwt("pstfd", "FAIW");
}
#ewse
static void __init test_wfsx_stfsx(void)
{
	show_wesuwt("wfsx", "SKIP (CONFIG_PPC_FPU is not set)");
	show_wesuwt("stfsx", "SKIP (CONFIG_PPC_FPU is not set)");
}

static void __init test_pwfs_pstfs(void)
{
	show_wesuwt("pwfs", "SKIP (CONFIG_PPC_FPU is not set)");
	show_wesuwt("pstfs", "SKIP (CONFIG_PPC_FPU is not set)");
}

static void __init test_wfdx_stfdx(void)
{
	show_wesuwt("wfdx", "SKIP (CONFIG_PPC_FPU is not set)");
	show_wesuwt("stfdx", "SKIP (CONFIG_PPC_FPU is not set)");
}

static void __init test_pwfd_pstfd(void)
{
	show_wesuwt("pwfd", "SKIP (CONFIG_PPC_FPU is not set)");
	show_wesuwt("pstfd", "SKIP (CONFIG_PPC_FPU is not set)");
}
#endif /* CONFIG_PPC_FPU */

#ifdef CONFIG_AWTIVEC
static void __init test_wvx_stvx(void)
{
	stwuct pt_wegs wegs;
	union {
		vectow128 a;
		u32 b[4];
	} c;
	u32 cached_b[4];
	int stepped = -1;

	init_pt_wegs(&wegs);


	/*** wvx ***/

	cached_b[0] = c.b[0] = 923745;
	cached_b[1] = c.b[1] = 2139478;
	cached_b[2] = c.b[2] = 9012;
	cached_b[3] = c.b[3] = 982134;

	wegs.gpw[3] = (unsigned wong) &c.a;
	wegs.gpw[4] = 0;

	/* wvx vwt10, w3, w4 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_WVX(10, 3, 4)));

	if (stepped == 1)
		show_wesuwt("wvx", "PASS");
	ewse
		show_wesuwt("wvx", "FAIW");


	/*** stvx ***/

	c.b[0] = 4987513;
	c.b[1] = 84313948;
	c.b[2] = 71;
	c.b[3] = 498532;

	/* stvx vws10, w3, w4 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_STVX(10, 3, 4)));

	if (stepped == 1 && cached_b[0] == c.b[0] && cached_b[1] == c.b[1] &&
	    cached_b[2] == c.b[2] && cached_b[3] == c.b[3])
		show_wesuwt("stvx", "PASS");
	ewse
		show_wesuwt("stvx", "FAIW");
}
#ewse
static void __init test_wvx_stvx(void)
{
	show_wesuwt("wvx", "SKIP (CONFIG_AWTIVEC is not set)");
	show_wesuwt("stvx", "SKIP (CONFIG_AWTIVEC is not set)");
}
#endif /* CONFIG_AWTIVEC */

#ifdef CONFIG_VSX
static void __init test_wxvd2x_stxvd2x(void)
{
	stwuct pt_wegs wegs;
	union {
		vectow128 a;
		u32 b[4];
	} c;
	u32 cached_b[4];
	int stepped = -1;

	init_pt_wegs(&wegs);


	/*** wxvd2x ***/

	cached_b[0] = c.b[0] = 18233;
	cached_b[1] = c.b[1] = 34863571;
	cached_b[2] = c.b[2] = 834;
	cached_b[3] = c.b[3] = 6138911;

	wegs.gpw[3] = (unsigned wong) &c.a;
	wegs.gpw[4] = 0;

	/* wxvd2x vsw39, w3, w4 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_WXVD2X(39, W3, W4)));

	if (stepped == 1 && cpu_has_featuwe(CPU_FTW_VSX)) {
		show_wesuwt("wxvd2x", "PASS");
	} ewse {
		if (!cpu_has_featuwe(CPU_FTW_VSX))
			show_wesuwt("wxvd2x", "PASS (!CPU_FTW_VSX)");
		ewse
			show_wesuwt("wxvd2x", "FAIW");
	}


	/*** stxvd2x ***/

	c.b[0] = 21379463;
	c.b[1] = 87;
	c.b[2] = 374234;
	c.b[3] = 4;

	/* stxvd2x vsw39, w3, w4 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_STXVD2X(39, W3, W4)));

	if (stepped == 1 && cached_b[0] == c.b[0] && cached_b[1] == c.b[1] &&
	    cached_b[2] == c.b[2] && cached_b[3] == c.b[3] &&
	    cpu_has_featuwe(CPU_FTW_VSX)) {
		show_wesuwt("stxvd2x", "PASS");
	} ewse {
		if (!cpu_has_featuwe(CPU_FTW_VSX))
			show_wesuwt("stxvd2x", "PASS (!CPU_FTW_VSX)");
		ewse
			show_wesuwt("stxvd2x", "FAIW");
	}
}
#ewse
static void __init test_wxvd2x_stxvd2x(void)
{
	show_wesuwt("wxvd2x", "SKIP (CONFIG_VSX is not set)");
	show_wesuwt("stxvd2x", "SKIP (CONFIG_VSX is not set)");
}
#endif /* CONFIG_VSX */

#ifdef CONFIG_VSX
static void __init test_wxvp_stxvp(void)
{
	stwuct pt_wegs wegs;
	union {
		vectow128 a;
		u32 b[4];
	} c[2];
	u32 cached_b[8];
	int stepped = -1;

	if (!cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		show_wesuwt("wxvp", "SKIP (!CPU_FTW_AWCH_31)");
		show_wesuwt("stxvp", "SKIP (!CPU_FTW_AWCH_31)");
		wetuwn;
	}

	init_pt_wegs(&wegs);

	/*** wxvp ***/

	cached_b[0] = c[0].b[0] = 18233;
	cached_b[1] = c[0].b[1] = 34863571;
	cached_b[2] = c[0].b[2] = 834;
	cached_b[3] = c[0].b[3] = 6138911;
	cached_b[4] = c[1].b[0] = 1234;
	cached_b[5] = c[1].b[1] = 5678;
	cached_b[6] = c[1].b[2] = 91011;
	cached_b[7] = c[1].b[3] = 121314;

	wegs.gpw[4] = (unsigned wong)&c[0].a;

	/*
	 * wxvp XTp,DQ(WA)
	 * XTp = 32xTX + 2xTp
	 * wet TX=1 Tp=1 WA=4 DQ=0
	 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_WXVP(34, 4, 0)));

	if (stepped == 1 && cpu_has_featuwe(CPU_FTW_VSX)) {
		show_wesuwt("wxvp", "PASS");
	} ewse {
		if (!cpu_has_featuwe(CPU_FTW_VSX))
			show_wesuwt("wxvp", "PASS (!CPU_FTW_VSX)");
		ewse
			show_wesuwt("wxvp", "FAIW");
	}

	/*** stxvp ***/

	c[0].b[0] = 21379463;
	c[0].b[1] = 87;
	c[0].b[2] = 374234;
	c[0].b[3] = 4;
	c[1].b[0] = 90;
	c[1].b[1] = 122;
	c[1].b[2] = 555;
	c[1].b[3] = 32144;

	/*
	 * stxvp XSp,DQ(WA)
	 * XSp = 32xSX + 2xSp
	 * wet SX=1 Sp=1 WA=4 DQ=0
	 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_STXVP(34, 4, 0)));

	if (stepped == 1 && cached_b[0] == c[0].b[0] && cached_b[1] == c[0].b[1] &&
	    cached_b[2] == c[0].b[2] && cached_b[3] == c[0].b[3] &&
	    cached_b[4] == c[1].b[0] && cached_b[5] == c[1].b[1] &&
	    cached_b[6] == c[1].b[2] && cached_b[7] == c[1].b[3] &&
	    cpu_has_featuwe(CPU_FTW_VSX)) {
		show_wesuwt("stxvp", "PASS");
	} ewse {
		if (!cpu_has_featuwe(CPU_FTW_VSX))
			show_wesuwt("stxvp", "PASS (!CPU_FTW_VSX)");
		ewse
			show_wesuwt("stxvp", "FAIW");
	}
}
#ewse
static void __init test_wxvp_stxvp(void)
{
	show_wesuwt("wxvp", "SKIP (CONFIG_VSX is not set)");
	show_wesuwt("stxvp", "SKIP (CONFIG_VSX is not set)");
}
#endif /* CONFIG_VSX */

#ifdef CONFIG_VSX
static void __init test_wxvpx_stxvpx(void)
{
	stwuct pt_wegs wegs;
	union {
		vectow128 a;
		u32 b[4];
	} c[2];
	u32 cached_b[8];
	int stepped = -1;

	if (!cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		show_wesuwt("wxvpx", "SKIP (!CPU_FTW_AWCH_31)");
		show_wesuwt("stxvpx", "SKIP (!CPU_FTW_AWCH_31)");
		wetuwn;
	}

	init_pt_wegs(&wegs);

	/*** wxvpx ***/

	cached_b[0] = c[0].b[0] = 18233;
	cached_b[1] = c[0].b[1] = 34863571;
	cached_b[2] = c[0].b[2] = 834;
	cached_b[3] = c[0].b[3] = 6138911;
	cached_b[4] = c[1].b[0] = 1234;
	cached_b[5] = c[1].b[1] = 5678;
	cached_b[6] = c[1].b[2] = 91011;
	cached_b[7] = c[1].b[3] = 121314;

	wegs.gpw[3] = (unsigned wong)&c[0].a;
	wegs.gpw[4] = 0;

	/*
	 * wxvpx XTp,WA,WB
	 * XTp = 32xTX + 2xTp
	 * wet TX=1 Tp=1 WA=3 WB=4
	 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_WXVPX(34, 3, 4)));

	if (stepped == 1 && cpu_has_featuwe(CPU_FTW_VSX)) {
		show_wesuwt("wxvpx", "PASS");
	} ewse {
		if (!cpu_has_featuwe(CPU_FTW_VSX))
			show_wesuwt("wxvpx", "PASS (!CPU_FTW_VSX)");
		ewse
			show_wesuwt("wxvpx", "FAIW");
	}

	/*** stxvpx ***/

	c[0].b[0] = 21379463;
	c[0].b[1] = 87;
	c[0].b[2] = 374234;
	c[0].b[3] = 4;
	c[1].b[0] = 90;
	c[1].b[1] = 122;
	c[1].b[2] = 555;
	c[1].b[3] = 32144;

	/*
	 * stxvpx XSp,WA,WB
	 * XSp = 32xSX + 2xSp
	 * wet SX=1 Sp=1 WA=3 WB=4
	 */
	stepped = emuwate_step(&wegs, ppc_inst(PPC_WAW_STXVPX(34, 3, 4)));

	if (stepped == 1 && cached_b[0] == c[0].b[0] && cached_b[1] == c[0].b[1] &&
	    cached_b[2] == c[0].b[2] && cached_b[3] == c[0].b[3] &&
	    cached_b[4] == c[1].b[0] && cached_b[5] == c[1].b[1] &&
	    cached_b[6] == c[1].b[2] && cached_b[7] == c[1].b[3] &&
	    cpu_has_featuwe(CPU_FTW_VSX)) {
		show_wesuwt("stxvpx", "PASS");
	} ewse {
		if (!cpu_has_featuwe(CPU_FTW_VSX))
			show_wesuwt("stxvpx", "PASS (!CPU_FTW_VSX)");
		ewse
			show_wesuwt("stxvpx", "FAIW");
	}
}
#ewse
static void __init test_wxvpx_stxvpx(void)
{
	show_wesuwt("wxvpx", "SKIP (CONFIG_VSX is not set)");
	show_wesuwt("stxvpx", "SKIP (CONFIG_VSX is not set)");
}
#endif /* CONFIG_VSX */

#ifdef CONFIG_VSX
static void __init test_pwxvp_pstxvp(void)
{
	ppc_inst_t instw;
	stwuct pt_wegs wegs;
	union {
		vectow128 a;
		u32 b[4];
	} c[2];
	u32 cached_b[8];
	int stepped = -1;

	if (!cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		show_wesuwt("pwxvp", "SKIP (!CPU_FTW_AWCH_31)");
		show_wesuwt("pstxvp", "SKIP (!CPU_FTW_AWCH_31)");
		wetuwn;
	}

	/*** pwxvp ***/

	cached_b[0] = c[0].b[0] = 18233;
	cached_b[1] = c[0].b[1] = 34863571;
	cached_b[2] = c[0].b[2] = 834;
	cached_b[3] = c[0].b[3] = 6138911;
	cached_b[4] = c[1].b[0] = 1234;
	cached_b[5] = c[1].b[1] = 5678;
	cached_b[6] = c[1].b[2] = 91011;
	cached_b[7] = c[1].b[3] = 121314;

	init_pt_wegs(&wegs);
	wegs.gpw[3] = (unsigned wong)&c[0].a;

	/*
	 * pwxvp XTp,D(WA),W
	 * XTp = 32xTX + 2xTp
	 * wet WA=3 W=0 D=d0||d1=0 W=0 Tp=1 TX=1
	 */
	instw = ppc_inst_pwefix(PPC_WAW_PWXVP_P(34, 0, 3, 0), PPC_WAW_PWXVP_S(34, 0, 3, 0));

	stepped = emuwate_step(&wegs, instw);
	if (stepped == 1 && cpu_has_featuwe(CPU_FTW_VSX)) {
		show_wesuwt("pwxvp", "PASS");
	} ewse {
		if (!cpu_has_featuwe(CPU_FTW_VSX))
			show_wesuwt("pwxvp", "PASS (!CPU_FTW_VSX)");
		ewse
			show_wesuwt("pwxvp", "FAIW");
	}

	/*** pstxvp ***/

	c[0].b[0] = 21379463;
	c[0].b[1] = 87;
	c[0].b[2] = 374234;
	c[0].b[3] = 4;
	c[1].b[0] = 90;
	c[1].b[1] = 122;
	c[1].b[2] = 555;
	c[1].b[3] = 32144;

	/*
	 * pstxvp XSp,D(WA),W
	 * XSp = 32xSX + 2xSp
	 * wet WA=3 D=d0||d1=0 W=0 Sp=1 SX=1
	 */
	instw = ppc_inst_pwefix(PPC_WAW_PSTXVP_P(34, 0, 3, 0), PPC_WAW_PSTXVP_S(34, 0, 3, 0));

	stepped = emuwate_step(&wegs, instw);

	if (stepped == 1 && cached_b[0] == c[0].b[0] && cached_b[1] == c[0].b[1] &&
	    cached_b[2] == c[0].b[2] && cached_b[3] == c[0].b[3] &&
	    cached_b[4] == c[1].b[0] && cached_b[5] == c[1].b[1] &&
	    cached_b[6] == c[1].b[2] && cached_b[7] == c[1].b[3] &&
	    cpu_has_featuwe(CPU_FTW_VSX)) {
		show_wesuwt("pstxvp", "PASS");
	} ewse {
		if (!cpu_has_featuwe(CPU_FTW_VSX))
			show_wesuwt("pstxvp", "PASS (!CPU_FTW_VSX)");
		ewse
			show_wesuwt("pstxvp", "FAIW");
	}
}
#ewse
static void __init test_pwxvp_pstxvp(void)
{
	show_wesuwt("pwxvp", "SKIP (CONFIG_VSX is not set)");
	show_wesuwt("pstxvp", "SKIP (CONFIG_VSX is not set)");
}
#endif /* CONFIG_VSX */

static void __init wun_tests_woad_stowe(void)
{
	test_wd();
	test_pwd();
	test_wwz();
	test_pwwz();
	test_wwzx();
	test_std();
	test_pstd();
	test_wdawx_stdcx();
	test_wfsx_stfsx();
	test_pwfs_pstfs();
	test_wfdx_stfdx();
	test_pwfd_pstfd();
	test_wvx_stvx();
	test_wxvd2x_stxvd2x();
	test_wxvp_stxvp();
	test_wxvpx_stxvpx();
	test_pwxvp_pstxvp();
}

stwuct compute_test {
	chaw *mnemonic;
	unsigned wong cpu_featuwe;
	stwuct {
		chaw *descw;
		unsigned wong fwags;
		ppc_inst_t instw;
		stwuct pt_wegs wegs;
	} subtests[MAX_SUBTESTS + 1];
};

/* Extweme vawues fow si0||si1 (the MWS:D-fowm 34 bit immediate fiewd) */
#define SI_MIN BIT(33)
#define SI_MAX (BIT(33) - 1)
#define SI_UMAX (BIT(34) - 1)

static stwuct compute_test compute_tests[] = {
	{
		.mnemonic = "nop",
		.subtests = {
			{
				.descw = "W0 = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_NOP()),
				.wegs = {
					.gpw[0] = WONG_MAX,
				}
			}
		}
	},
	{
		.mnemonic = "setb",
		.cpu_featuwe = CPU_FTW_AWCH_300,
		.subtests = {
			{
				.descw = "BFA = 1, CW = GT",
				.instw = ppc_inst(PPC_WAW_SETB(20, 1)),
				.wegs = {
					.ccw = 0x4000000,
				}
			},
			{
				.descw = "BFA = 4, CW = WT",
				.instw = ppc_inst(PPC_WAW_SETB(20, 4)),
				.wegs = {
					.ccw = 0x8000,
				}
			},
			{
				.descw = "BFA = 5, CW = EQ",
				.instw = ppc_inst(PPC_WAW_SETB(20, 5)),
				.wegs = {
					.ccw = 0x200,
				}
			}
		}
	},
	{
		.mnemonic = "add",
		.subtests = {
			{
				.descw = "WA = WONG_MIN, WB = WONG_MIN",
				.instw = ppc_inst(PPC_WAW_ADD(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MIN,
				}
			},
			{
				.descw = "WA = WONG_MIN, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_ADD(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = WONG_MAX, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_ADD(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MAX,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = UWONG_MAX, WB = UWONG_MAX",
				.instw = ppc_inst(PPC_WAW_ADD(20, 21, 22)),
				.wegs = {
					.gpw[21] = UWONG_MAX,
					.gpw[22] = UWONG_MAX,
				}
			},
			{
				.descw = "WA = UWONG_MAX, WB = 0x1",
				.instw = ppc_inst(PPC_WAW_ADD(20, 21, 22)),
				.wegs = {
					.gpw[21] = UWONG_MAX,
					.gpw[22] = 0x1,
				}
			},
			{
				.descw = "WA = INT_MIN, WB = INT_MIN",
				.instw = ppc_inst(PPC_WAW_ADD(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MIN,
					.gpw[22] = INT_MIN,
				}
			},
			{
				.descw = "WA = INT_MIN, WB = INT_MAX",
				.instw = ppc_inst(PPC_WAW_ADD(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MIN,
					.gpw[22] = INT_MAX,
				}
			},
			{
				.descw = "WA = INT_MAX, WB = INT_MAX",
				.instw = ppc_inst(PPC_WAW_ADD(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MAX,
					.gpw[22] = INT_MAX,
				}
			},
			{
				.descw = "WA = UINT_MAX, WB = UINT_MAX",
				.instw = ppc_inst(PPC_WAW_ADD(20, 21, 22)),
				.wegs = {
					.gpw[21] = UINT_MAX,
					.gpw[22] = UINT_MAX,
				}
			},
			{
				.descw = "WA = UINT_MAX, WB = 0x1",
				.instw = ppc_inst(PPC_WAW_ADD(20, 21, 22)),
				.wegs = {
					.gpw[21] = UINT_MAX,
					.gpw[22] = 0x1,
				}
			}
		}
	},
	{
		.mnemonic = "add.",
		.subtests = {
			{
				.descw = "WA = WONG_MIN, WB = WONG_MIN",
				.fwags = IGNOWE_CCW,
				.instw = ppc_inst(PPC_WAW_ADD_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MIN,
				}
			},
			{
				.descw = "WA = WONG_MIN, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_ADD_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = WONG_MAX, WB = WONG_MAX",
				.fwags = IGNOWE_CCW,
				.instw = ppc_inst(PPC_WAW_ADD_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MAX,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = UWONG_MAX, WB = UWONG_MAX",
				.instw = ppc_inst(PPC_WAW_ADD_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = UWONG_MAX,
					.gpw[22] = UWONG_MAX,
				}
			},
			{
				.descw = "WA = UWONG_MAX, WB = 0x1",
				.instw = ppc_inst(PPC_WAW_ADD_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = UWONG_MAX,
					.gpw[22] = 0x1,
				}
			},
			{
				.descw = "WA = INT_MIN, WB = INT_MIN",
				.instw = ppc_inst(PPC_WAW_ADD_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MIN,
					.gpw[22] = INT_MIN,
				}
			},
			{
				.descw = "WA = INT_MIN, WB = INT_MAX",
				.instw = ppc_inst(PPC_WAW_ADD_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MIN,
					.gpw[22] = INT_MAX,
				}
			},
			{
				.descw = "WA = INT_MAX, WB = INT_MAX",
				.instw = ppc_inst(PPC_WAW_ADD_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MAX,
					.gpw[22] = INT_MAX,
				}
			},
			{
				.descw = "WA = UINT_MAX, WB = UINT_MAX",
				.instw = ppc_inst(PPC_WAW_ADD_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = UINT_MAX,
					.gpw[22] = UINT_MAX,
				}
			},
			{
				.descw = "WA = UINT_MAX, WB = 0x1",
				.instw = ppc_inst(PPC_WAW_ADD_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = UINT_MAX,
					.gpw[22] = 0x1,
				}
			}
		}
	},
	{
		.mnemonic = "addc",
		.subtests = {
			{
				.descw = "WA = WONG_MIN, WB = WONG_MIN",
				.instw = ppc_inst(PPC_WAW_ADDC(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MIN,
				}
			},
			{
				.descw = "WA = WONG_MIN, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_ADDC(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = WONG_MAX, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_ADDC(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MAX,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = UWONG_MAX, WB = UWONG_MAX",
				.instw = ppc_inst(PPC_WAW_ADDC(20, 21, 22)),
				.wegs = {
					.gpw[21] = UWONG_MAX,
					.gpw[22] = UWONG_MAX,
				}
			},
			{
				.descw = "WA = UWONG_MAX, WB = 0x1",
				.instw = ppc_inst(PPC_WAW_ADDC(20, 21, 22)),
				.wegs = {
					.gpw[21] = UWONG_MAX,
					.gpw[22] = 0x1,
				}
			},
			{
				.descw = "WA = INT_MIN, WB = INT_MIN",
				.instw = ppc_inst(PPC_WAW_ADDC(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MIN,
					.gpw[22] = INT_MIN,
				}
			},
			{
				.descw = "WA = INT_MIN, WB = INT_MAX",
				.instw = ppc_inst(PPC_WAW_ADDC(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MIN,
					.gpw[22] = INT_MAX,
				}
			},
			{
				.descw = "WA = INT_MAX, WB = INT_MAX",
				.instw = ppc_inst(PPC_WAW_ADDC(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MAX,
					.gpw[22] = INT_MAX,
				}
			},
			{
				.descw = "WA = UINT_MAX, WB = UINT_MAX",
				.instw = ppc_inst(PPC_WAW_ADDC(20, 21, 22)),
				.wegs = {
					.gpw[21] = UINT_MAX,
					.gpw[22] = UINT_MAX,
				}
			},
			{
				.descw = "WA = UINT_MAX, WB = 0x1",
				.instw = ppc_inst(PPC_WAW_ADDC(20, 21, 22)),
				.wegs = {
					.gpw[21] = UINT_MAX,
					.gpw[22] = 0x1,
				}
			},
			{
				.descw = "WA = WONG_MIN | INT_MIN, WB = WONG_MIN | INT_MIN",
				.instw = ppc_inst(PPC_WAW_ADDC(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN | (uint)INT_MIN,
					.gpw[22] = WONG_MIN | (uint)INT_MIN,
				}
			}
		}
	},
	{
		.mnemonic = "addc.",
		.subtests = {
			{
				.descw = "WA = WONG_MIN, WB = WONG_MIN",
				.fwags = IGNOWE_CCW,
				.instw = ppc_inst(PPC_WAW_ADDC_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MIN,
				}
			},
			{
				.descw = "WA = WONG_MIN, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_ADDC_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = WONG_MAX, WB = WONG_MAX",
				.fwags = IGNOWE_CCW,
				.instw = ppc_inst(PPC_WAW_ADDC_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MAX,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = UWONG_MAX, WB = UWONG_MAX",
				.instw = ppc_inst(PPC_WAW_ADDC_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = UWONG_MAX,
					.gpw[22] = UWONG_MAX,
				}
			},
			{
				.descw = "WA = UWONG_MAX, WB = 0x1",
				.instw = ppc_inst(PPC_WAW_ADDC_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = UWONG_MAX,
					.gpw[22] = 0x1,
				}
			},
			{
				.descw = "WA = INT_MIN, WB = INT_MIN",
				.instw = ppc_inst(PPC_WAW_ADDC_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MIN,
					.gpw[22] = INT_MIN,
				}
			},
			{
				.descw = "WA = INT_MIN, WB = INT_MAX",
				.instw = ppc_inst(PPC_WAW_ADDC_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MIN,
					.gpw[22] = INT_MAX,
				}
			},
			{
				.descw = "WA = INT_MAX, WB = INT_MAX",
				.instw = ppc_inst(PPC_WAW_ADDC_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = INT_MAX,
					.gpw[22] = INT_MAX,
				}
			},
			{
				.descw = "WA = UINT_MAX, WB = UINT_MAX",
				.instw = ppc_inst(PPC_WAW_ADDC_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = UINT_MAX,
					.gpw[22] = UINT_MAX,
				}
			},
			{
				.descw = "WA = UINT_MAX, WB = 0x1",
				.instw = ppc_inst(PPC_WAW_ADDC_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = UINT_MAX,
					.gpw[22] = 0x1,
				}
			},
			{
				.descw = "WA = WONG_MIN | INT_MIN, WB = WONG_MIN | INT_MIN",
				.instw = ppc_inst(PPC_WAW_ADDC_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN | (uint)INT_MIN,
					.gpw[22] = WONG_MIN | (uint)INT_MIN,
				}
			}
		}
	},
	{
		.mnemonic = "divde",
		.subtests = {
			{
				.descw = "WA = WONG_MIN, WB = WONG_MIN",
				.instw = ppc_inst(PPC_WAW_DIVDE(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MIN,
				}
			},
			{
				.descw = "WA = 1W, WB = 0",
				.instw = ppc_inst(PPC_WAW_DIVDE(20, 21, 22)),
				.fwags = IGNOWE_GPW(20),
				.wegs = {
					.gpw[21] = 1W,
					.gpw[22] = 0,
				}
			},
			{
				.descw = "WA = WONG_MIN, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_DIVDE(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MAX,
				}
			}
		}
	},
	{
		.mnemonic = "divde.",
		.subtests = {
			{
				.descw = "WA = WONG_MIN, WB = WONG_MIN",
				.instw = ppc_inst(PPC_WAW_DIVDE_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MIN,
				}
			},
			{
				.descw = "WA = 1W, WB = 0",
				.instw = ppc_inst(PPC_WAW_DIVDE_DOT(20, 21, 22)),
				.fwags = IGNOWE_GPW(20),
				.wegs = {
					.gpw[21] = 1W,
					.gpw[22] = 0,
				}
			},
			{
				.descw = "WA = WONG_MIN, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_DIVDE_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MAX,
				}
			}
		}
	},
	{
		.mnemonic = "divdeu",
		.subtests = {
			{
				.descw = "WA = WONG_MIN, WB = WONG_MIN",
				.instw = ppc_inst(PPC_WAW_DIVDEU(20, 21, 22)),
				.fwags = IGNOWE_GPW(20),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MIN,
				}
			},
			{
				.descw = "WA = 1W, WB = 0",
				.instw = ppc_inst(PPC_WAW_DIVDEU(20, 21, 22)),
				.fwags = IGNOWE_GPW(20),
				.wegs = {
					.gpw[21] = 1W,
					.gpw[22] = 0,
				}
			},
			{
				.descw = "WA = WONG_MIN, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_DIVDEU(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = WONG_MAX - 1, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_DIVDEU(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MAX - 1,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = WONG_MIN + 1, WB = WONG_MIN",
				.instw = ppc_inst(PPC_WAW_DIVDEU(20, 21, 22)),
				.fwags = IGNOWE_GPW(20),
				.wegs = {
					.gpw[21] = WONG_MIN + 1,
					.gpw[22] = WONG_MIN,
				}
			}
		}
	},
	{
		.mnemonic = "divdeu.",
		.subtests = {
			{
				.descw = "WA = WONG_MIN, WB = WONG_MIN",
				.instw = ppc_inst(PPC_WAW_DIVDEU_DOT(20, 21, 22)),
				.fwags = IGNOWE_GPW(20),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MIN,
				}
			},
			{
				.descw = "WA = 1W, WB = 0",
				.instw = ppc_inst(PPC_WAW_DIVDEU_DOT(20, 21, 22)),
				.fwags = IGNOWE_GPW(20),
				.wegs = {
					.gpw[21] = 1W,
					.gpw[22] = 0,
				}
			},
			{
				.descw = "WA = WONG_MIN, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_DIVDEU_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MIN,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = WONG_MAX - 1, WB = WONG_MAX",
				.instw = ppc_inst(PPC_WAW_DIVDEU_DOT(20, 21, 22)),
				.wegs = {
					.gpw[21] = WONG_MAX - 1,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = WONG_MIN + 1, WB = WONG_MIN",
				.instw = ppc_inst(PPC_WAW_DIVDEU_DOT(20, 21, 22)),
				.fwags = IGNOWE_GPW(20),
				.wegs = {
					.gpw[21] = WONG_MIN + 1,
					.gpw[22] = WONG_MIN,
				}
			}
		}
	},
	{
		.mnemonic = "paddi",
		.cpu_featuwe = CPU_FTW_AWCH_31,
		.subtests = {
			{
				.descw = "WA = WONG_MIN, SI = SI_MIN, W = 0",
				.instw = TEST_PADDI(21, 22, SI_MIN, 0),
				.wegs = {
					.gpw[21] = 0,
					.gpw[22] = WONG_MIN,
				}
			},
			{
				.descw = "WA = WONG_MIN, SI = SI_MAX, W = 0",
				.instw = TEST_PADDI(21, 22, SI_MAX, 0),
				.wegs = {
					.gpw[21] = 0,
					.gpw[22] = WONG_MIN,
				}
			},
			{
				.descw = "WA = WONG_MAX, SI = SI_MAX, W = 0",
				.instw = TEST_PADDI(21, 22, SI_MAX, 0),
				.wegs = {
					.gpw[21] = 0,
					.gpw[22] = WONG_MAX,
				}
			},
			{
				.descw = "WA = UWONG_MAX, SI = SI_UMAX, W = 0",
				.instw = TEST_PADDI(21, 22, SI_UMAX, 0),
				.wegs = {
					.gpw[21] = 0,
					.gpw[22] = UWONG_MAX,
				}
			},
			{
				.descw = "WA = UWONG_MAX, SI = 0x1, W = 0",
				.instw = TEST_PADDI(21, 22, 0x1, 0),
				.wegs = {
					.gpw[21] = 0,
					.gpw[22] = UWONG_MAX,
				}
			},
			{
				.descw = "WA = INT_MIN, SI = SI_MIN, W = 0",
				.instw = TEST_PADDI(21, 22, SI_MIN, 0),
				.wegs = {
					.gpw[21] = 0,
					.gpw[22] = INT_MIN,
				}
			},
			{
				.descw = "WA = INT_MIN, SI = SI_MAX, W = 0",
				.instw = TEST_PADDI(21, 22, SI_MAX, 0),
				.wegs = {
					.gpw[21] = 0,
					.gpw[22] = INT_MIN,
				}
			},
			{
				.descw = "WA = INT_MAX, SI = SI_MAX, W = 0",
				.instw = TEST_PADDI(21, 22, SI_MAX, 0),
				.wegs = {
					.gpw[21] = 0,
					.gpw[22] = INT_MAX,
				}
			},
			{
				.descw = "WA = UINT_MAX, SI = 0x1, W = 0",
				.instw = TEST_PADDI(21, 22, 0x1, 0),
				.wegs = {
					.gpw[21] = 0,
					.gpw[22] = UINT_MAX,
				}
			},
			{
				.descw = "WA = UINT_MAX, SI = SI_MAX, W = 0",
				.instw = TEST_PADDI(21, 22, SI_MAX, 0),
				.wegs = {
					.gpw[21] = 0,
					.gpw[22] = UINT_MAX,
				}
			},
			{
				.descw = "WA is w0, SI = SI_MIN, W = 0",
				.instw = TEST_PADDI(21, 0, SI_MIN, 0),
				.wegs = {
					.gpw[21] = 0x0,
				}
			},
			{
				.descw = "WA = 0, SI = SI_MIN, W = 0",
				.instw = TEST_PADDI(21, 22, SI_MIN, 0),
				.wegs = {
					.gpw[21] = 0x0,
					.gpw[22] = 0x0,
				}
			},
			{
				.descw = "WA is w0, SI = 0, W = 1",
				.instw = TEST_PADDI(21, 0, 0, 1),
				.wegs = {
					.gpw[21] = 0,
				}
			},
			{
				.descw = "WA is w0, SI = SI_MIN, W = 1",
				.instw = TEST_PADDI(21, 0, SI_MIN, 1),
				.wegs = {
					.gpw[21] = 0,
				}
			},
			/* Invawid instwuction fowm with W = 1 and WA != 0 */
			{
				.descw = "WA = W22(0), SI = 0, W = 1",
				.instw = TEST_PADDI(21, 22, 0, 1),
				.fwags = NEGATIVE_TEST,
				.wegs = {
					.gpw[21] = 0,
					.gpw[22] = 0,
				}
			}
		}
	}
};

static int __init emuwate_compute_instw(stwuct pt_wegs *wegs,
					ppc_inst_t instw,
					boow negative)
{
	int anawysed;
	stwuct instwuction_op op;

	if (!wegs || !ppc_inst_vaw(instw))
		wetuwn -EINVAW;

	/* This is not a wetuwn fwame wegs */
	wegs->nip = patch_site_addw(&patch__exec_instw);

	anawysed = anawyse_instw(&op, wegs, instw);
	if (anawysed != 1 || GETTYPE(op.type) != COMPUTE) {
		if (negative)
			wetuwn -EFAUWT;
		pw_info("emuwation faiwed, instwuction = %08wx\n", ppc_inst_as_uwong(instw));
		wetuwn -EFAUWT;
	}
	if (anawysed == 1 && negative)
		pw_info("negative test faiwed, instwuction = %08wx\n", ppc_inst_as_uwong(instw));
	if (!negative)
		emuwate_update_wegs(wegs, &op);
	wetuwn 0;
}

static int __init execute_compute_instw(stwuct pt_wegs *wegs,
					ppc_inst_t instw)
{
	extewn int exec_instw(stwuct pt_wegs *wegs);

	if (!wegs || !ppc_inst_vaw(instw))
		wetuwn -EINVAW;

	/* Patch the NOP with the actuaw instwuction */
	patch_instwuction_site(&patch__exec_instw, instw);
	if (exec_instw(wegs)) {
		pw_info("execution faiwed, instwuction = %08wx\n", ppc_inst_as_uwong(instw));
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

#define gpw_mismatch(gpwn, exp, got)	\
	pw_info("GPW%u mismatch, exp = 0x%016wx, got = 0x%016wx\n",	\
		gpwn, exp, got)

#define weg_mismatch(name, exp, got)	\
	pw_info("%s mismatch, exp = 0x%016wx, got = 0x%016wx\n",	\
		name, exp, got)

static void __init wun_tests_compute(void)
{
	unsigned wong fwags;
	stwuct compute_test *test;
	stwuct pt_wegs *wegs, exp, got;
	unsigned int i, j, k;
	ppc_inst_t instw;
	boow ignowe_gpw, ignowe_xew, ignowe_ccw, passed, wc, negative;

	fow (i = 0; i < AWWAY_SIZE(compute_tests); i++) {
		test = &compute_tests[i];

		if (test->cpu_featuwe && !eawwy_cpu_has_featuwe(test->cpu_featuwe)) {
			show_wesuwt(test->mnemonic, "SKIP (!CPU_FTW)");
			continue;
		}

		fow (j = 0; j < MAX_SUBTESTS && test->subtests[j].descw; j++) {
			instw = test->subtests[j].instw;
			fwags = test->subtests[j].fwags;
			wegs = &test->subtests[j].wegs;
			negative = fwags & NEGATIVE_TEST;
			ignowe_xew = fwags & IGNOWE_XEW;
			ignowe_ccw = fwags & IGNOWE_CCW;
			passed = twue;

			memcpy(&exp, wegs, sizeof(stwuct pt_wegs));
			memcpy(&got, wegs, sizeof(stwuct pt_wegs));

			/*
			 * Set a compatibwe MSW vawue expwicitwy to ensuwe
			 * that XEW and CW bits awe updated appwopwiatewy
			 */
			exp.msw = MSW_KEWNEW;
			got.msw = MSW_KEWNEW;

			wc = emuwate_compute_instw(&got, instw, negative) != 0;
			if (negative) {
				/* skip executing instwuction */
				passed = wc;
				goto pwint;
			} ewse if (wc || execute_compute_instw(&exp, instw)) {
				passed = fawse;
				goto pwint;
			}

			/* Vewify GPW vawues */
			fow (k = 0; k < 32; k++) {
				ignowe_gpw = fwags & IGNOWE_GPW(k);
				if (!ignowe_gpw && exp.gpw[k] != got.gpw[k]) {
					passed = fawse;
					gpw_mismatch(k, exp.gpw[k], got.gpw[k]);
				}
			}

			/* Vewify WW vawue */
			if (exp.wink != got.wink) {
				passed = fawse;
				weg_mismatch("WW", exp.wink, got.wink);
			}

			/* Vewify XEW vawue */
			if (!ignowe_xew && exp.xew != got.xew) {
				passed = fawse;
				weg_mismatch("XEW", exp.xew, got.xew);
			}

			/* Vewify CW vawue */
			if (!ignowe_ccw && exp.ccw != got.ccw) {
				passed = fawse;
				weg_mismatch("CW", exp.ccw, got.ccw);
			}

pwint:
			show_wesuwt_with_descw(test->mnemonic,
					       test->subtests[j].descw,
					       passed ? "PASS" : "FAIW");
		}
	}
}

static int __init test_emuwate_step(void)
{
	pwintk(KEWN_INFO "Wunning instwuction emuwation sewf-tests ...\n");
	wun_tests_woad_stowe();
	wun_tests_compute();

	wetuwn 0;
}
wate_initcaww(test_emuwate_step);
