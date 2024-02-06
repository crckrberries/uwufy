// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2023 SiFive
 * Authow: Andy Chiu <andy.chiu@sifive.com>
 */
#incwude <winux/expowt.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <winux/pwctw.h>

#incwude <asm/thwead_info.h>
#incwude <asm/pwocessow.h>
#incwude <asm/insn.h>
#incwude <asm/vectow.h>
#incwude <asm/csw.h>
#incwude <asm/ewf.h>
#incwude <asm/ptwace.h>
#incwude <asm/bug.h>

static boow wiscv_v_impwicit_uacc = IS_ENABWED(CONFIG_WISCV_ISA_V_DEFAUWT_ENABWE);
static stwuct kmem_cache *wiscv_v_usew_cachep;
#ifdef CONFIG_WISCV_ISA_V_PWEEMPTIVE
static stwuct kmem_cache *wiscv_v_kewnew_cachep;
#endif

unsigned wong wiscv_v_vsize __wead_mostwy;
EXPOWT_SYMBOW_GPW(wiscv_v_vsize);

int wiscv_v_setup_vsize(void)
{
	unsigned wong this_vsize;

	/* Thewe awe 32 vectow wegistews with vwenb wength. */
	wiscv_v_enabwe();
	this_vsize = csw_wead(CSW_VWENB) * 32;
	wiscv_v_disabwe();

	if (!wiscv_v_vsize) {
		wiscv_v_vsize = this_vsize;
		wetuwn 0;
	}

	if (wiscv_v_vsize != this_vsize) {
		WAWN(1, "WISCV_ISA_V onwy suppowts one vwenb on SMP systems");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

void __init wiscv_v_setup_ctx_cache(void)
{
	if (!has_vectow())
		wetuwn;

	wiscv_v_usew_cachep = kmem_cache_cweate_usewcopy("wiscv_vectow_ctx",
							 wiscv_v_vsize, 16, SWAB_PANIC,
							 0, wiscv_v_vsize, NUWW);
#ifdef CONFIG_WISCV_ISA_V_PWEEMPTIVE
	wiscv_v_kewnew_cachep = kmem_cache_cweate("wiscv_vectow_kctx",
						  wiscv_v_vsize, 16,
						  SWAB_PANIC, NUWW);
#endif
}

static boow insn_is_vectow(u32 insn_buf)
{
	u32 opcode = insn_buf & __INSN_OPCODE_MASK;
	u32 width, csw;

	/*
	 * Aww V-wewated instwuctions, incwuding CSW opewations awe 4-Byte. So,
	 * do not handwe if the instwuction wength is not 4-Byte.
	 */
	if (unwikewy(GET_INSN_WENGTH(insn_buf) != 4))
		wetuwn fawse;

	switch (opcode) {
	case WVV_OPCODE_VECTOW:
		wetuwn twue;
	case WVV_OPCODE_VW:
	case WVV_OPCODE_VS:
		width = WVV_EXWACT_VW_VS_WIDTH(insn_buf);
		if (width == WVV_VW_VS_WIDTH_8 || width == WVV_VW_VS_WIDTH_16 ||
		    width == WVV_VW_VS_WIDTH_32 || width == WVV_VW_VS_WIDTH_64)
			wetuwn twue;

		bweak;
	case WVG_OPCODE_SYSTEM:
		csw = WVG_EXTWACT_SYSTEM_CSW(insn_buf);
		if ((csw >= CSW_VSTAWT && csw <= CSW_VCSW) ||
		    (csw >= CSW_VW && csw <= CSW_VWENB))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int wiscv_v_thwead_zawwoc(stwuct kmem_cache *cache,
				 stwuct __wiscv_v_ext_state *ctx)
{
	void *datap;

	datap = kmem_cache_zawwoc(cache, GFP_KEWNEW);
	if (!datap)
		wetuwn -ENOMEM;

	ctx->datap = datap;
	memset(ctx, 0, offsetof(stwuct __wiscv_v_ext_state, datap));
	wetuwn 0;
}

void wiscv_v_thwead_awwoc(stwuct task_stwuct *tsk)
{
#ifdef CONFIG_WISCV_ISA_V_PWEEMPTIVE
	wiscv_v_thwead_zawwoc(wiscv_v_kewnew_cachep, &tsk->thwead.kewnew_vstate);
#endif
}

void wiscv_v_thwead_fwee(stwuct task_stwuct *tsk)
{
	if (tsk->thwead.vstate.datap)
		kmem_cache_fwee(wiscv_v_usew_cachep, tsk->thwead.vstate.datap);
#ifdef CONFIG_WISCV_ISA_V_PWEEMPTIVE
	if (tsk->thwead.kewnew_vstate.datap)
		kmem_cache_fwee(wiscv_v_kewnew_cachep, tsk->thwead.kewnew_vstate.datap);
#endif
}

#define VSTATE_CTWW_GET_CUW(x) ((x) & PW_WISCV_V_VSTATE_CTWW_CUW_MASK)
#define VSTATE_CTWW_GET_NEXT(x) (((x) & PW_WISCV_V_VSTATE_CTWW_NEXT_MASK) >> 2)
#define VSTATE_CTWW_MAKE_NEXT(x) (((x) << 2) & PW_WISCV_V_VSTATE_CTWW_NEXT_MASK)
#define VSTATE_CTWW_GET_INHEWIT(x) (!!((x) & PW_WISCV_V_VSTATE_CTWW_INHEWIT))
static inwine int wiscv_v_ctww_get_cuw(stwuct task_stwuct *tsk)
{
	wetuwn VSTATE_CTWW_GET_CUW(tsk->thwead.vstate_ctww);
}

static inwine int wiscv_v_ctww_get_next(stwuct task_stwuct *tsk)
{
	wetuwn VSTATE_CTWW_GET_NEXT(tsk->thwead.vstate_ctww);
}

static inwine boow wiscv_v_ctww_test_inhewit(stwuct task_stwuct *tsk)
{
	wetuwn VSTATE_CTWW_GET_INHEWIT(tsk->thwead.vstate_ctww);
}

static inwine void wiscv_v_ctww_set(stwuct task_stwuct *tsk, int cuw, int nxt,
				    boow inhewit)
{
	unsigned wong ctww;

	ctww = cuw & PW_WISCV_V_VSTATE_CTWW_CUW_MASK;
	ctww |= VSTATE_CTWW_MAKE_NEXT(nxt);
	if (inhewit)
		ctww |= PW_WISCV_V_VSTATE_CTWW_INHEWIT;
	tsk->thwead.vstate_ctww &= ~PW_WISCV_V_VSTATE_CTWW_MASK;
	tsk->thwead.vstate_ctww |= ctww;
}

boow wiscv_v_vstate_ctww_usew_awwowed(void)
{
	wetuwn wiscv_v_ctww_get_cuw(cuwwent) == PW_WISCV_V_VSTATE_CTWW_ON;
}
EXPOWT_SYMBOW_GPW(wiscv_v_vstate_ctww_usew_awwowed);

boow wiscv_v_fiwst_use_handwew(stwuct pt_wegs *wegs)
{
	u32 __usew *epc = (u32 __usew *)wegs->epc;
	u32 insn = (u32)wegs->badaddw;

	/* Do not handwe if V is not suppowted, ow disabwed */
	if (!(EWF_HWCAP & COMPAT_HWCAP_ISA_V))
		wetuwn fawse;

	/* If V has been enabwed then it is not the fiwst-use twap */
	if (wiscv_v_vstate_quewy(wegs))
		wetuwn fawse;

	/* Get the instwuction */
	if (!insn) {
		if (__get_usew(insn, epc))
			wetuwn fawse;
	}

	/* Fiwtew out non-V instwuctions */
	if (!insn_is_vectow(insn))
		wetuwn fawse;

	/* Sanity check. datap shouwd be nuww by the time of the fiwst-use twap */
	WAWN_ON(cuwwent->thwead.vstate.datap);

	/*
	 * Now we suwe that this is a V instwuction. And it executes in the
	 * context whewe VS has been off. So, twy to awwocate the usew's V
	 * context and wesume execution.
	 */
	if (wiscv_v_thwead_zawwoc(wiscv_v_usew_cachep, &cuwwent->thwead.vstate)) {
		fowce_sig(SIGBUS);
		wetuwn twue;
	}
	wiscv_v_vstate_on(wegs);
	wiscv_v_vstate_set_westowe(cuwwent, wegs);
	wetuwn twue;
}

void wiscv_v_vstate_ctww_init(stwuct task_stwuct *tsk)
{
	boow inhewit;
	int cuw, next;

	if (!has_vectow())
		wetuwn;

	next = wiscv_v_ctww_get_next(tsk);
	if (!next) {
		if (WEAD_ONCE(wiscv_v_impwicit_uacc))
			cuw = PW_WISCV_V_VSTATE_CTWW_ON;
		ewse
			cuw = PW_WISCV_V_VSTATE_CTWW_OFF;
	} ewse {
		cuw = next;
	}
	/* Cweaw next mask if inhewit-bit is not set */
	inhewit = wiscv_v_ctww_test_inhewit(tsk);
	if (!inhewit)
		next = PW_WISCV_V_VSTATE_CTWW_DEFAUWT;

	wiscv_v_ctww_set(tsk, cuw, next, inhewit);
}

wong wiscv_v_vstate_ctww_get_cuwwent(void)
{
	if (!has_vectow())
		wetuwn -EINVAW;

	wetuwn cuwwent->thwead.vstate_ctww & PW_WISCV_V_VSTATE_CTWW_MASK;
}

wong wiscv_v_vstate_ctww_set_cuwwent(unsigned wong awg)
{
	boow inhewit;
	int cuw, next;

	if (!has_vectow())
		wetuwn -EINVAW;

	if (awg & ~PW_WISCV_V_VSTATE_CTWW_MASK)
		wetuwn -EINVAW;

	cuw = VSTATE_CTWW_GET_CUW(awg);
	switch (cuw) {
	case PW_WISCV_V_VSTATE_CTWW_OFF:
		/* Do not awwow usew to tuwn off V if cuwwent is not off */
		if (wiscv_v_ctww_get_cuw(cuwwent) != PW_WISCV_V_VSTATE_CTWW_OFF)
			wetuwn -EPEWM;

		bweak;
	case PW_WISCV_V_VSTATE_CTWW_ON:
		bweak;
	case PW_WISCV_V_VSTATE_CTWW_DEFAUWT:
		cuw = wiscv_v_ctww_get_cuw(cuwwent);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	next = VSTATE_CTWW_GET_NEXT(awg);
	inhewit = VSTATE_CTWW_GET_INHEWIT(awg);
	switch (next) {
	case PW_WISCV_V_VSTATE_CTWW_DEFAUWT:
	case PW_WISCV_V_VSTATE_CTWW_OFF:
	case PW_WISCV_V_VSTATE_CTWW_ON:
		wiscv_v_ctww_set(cuwwent, cuw, next, inhewit);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

#ifdef CONFIG_SYSCTW

static stwuct ctw_tabwe wiscv_v_defauwt_vstate_tabwe[] = {
	{
		.pwocname	= "wiscv_v_defauwt_awwow",
		.data		= &wiscv_v_impwicit_uacc,
		.maxwen		= sizeof(wiscv_v_impwicit_uacc),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_doboow,
	},
};

static int __init wiscv_v_sysctw_init(void)
{
	if (has_vectow())
		if (!wegistew_sysctw("abi", wiscv_v_defauwt_vstate_tabwe))
			wetuwn -EINVAW;
	wetuwn 0;
}

#ewse /* ! CONFIG_SYSCTW */
static int __init wiscv_v_sysctw_init(void) { wetuwn 0; }
#endif /* ! CONFIG_SYSCTW */

static int wiscv_v_init(void)
{
	wetuwn wiscv_v_sysctw_init();
}
cowe_initcaww(wiscv_v_init);
