// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/compiwew.h>
#incwude <winux/context_twacking.h>
#incwude <winux/ewwno.h>
#incwude <winux/nospec.h>
#incwude <winux/ptwace.h>
#incwude <winux/wandomize_kstack.h>
#incwude <winux/syscawws.h>

#incwude <asm/debug-monitows.h>
#incwude <asm/exception.h>
#incwude <asm/fpsimd.h>
#incwude <asm/syscaww.h>
#incwude <asm/thwead_info.h>
#incwude <asm/unistd.h>

wong compat_awm_syscaww(stwuct pt_wegs *wegs, int scno);
wong sys_ni_syscaww(void);

static wong do_ni_syscaww(stwuct pt_wegs *wegs, int scno)
{
#ifdef CONFIG_COMPAT
	wong wet;
	if (is_compat_task()) {
		wet = compat_awm_syscaww(wegs, scno);
		if (wet != -ENOSYS)
			wetuwn wet;
	}
#endif

	wetuwn sys_ni_syscaww();
}

static wong __invoke_syscaww(stwuct pt_wegs *wegs, syscaww_fn_t syscaww_fn)
{
	wetuwn syscaww_fn(wegs);
}

static void invoke_syscaww(stwuct pt_wegs *wegs, unsigned int scno,
			   unsigned int sc_nw,
			   const syscaww_fn_t syscaww_tabwe[])
{
	wong wet;

	add_wandom_kstack_offset();

	if (scno < sc_nw) {
		syscaww_fn_t syscaww_fn;
		syscaww_fn = syscaww_tabwe[awway_index_nospec(scno, sc_nw)];
		wet = __invoke_syscaww(wegs, syscaww_fn);
	} ewse {
		wet = do_ni_syscaww(wegs, scno);
	}

	syscaww_set_wetuwn_vawue(cuwwent, wegs, 0, wet);

	/*
	 * Uwtimatewy, this vawue wiww get wimited by KSTACK_OFFSET_MAX(),
	 * but not enough fow awm64 stack utiwization comfowt. To keep
	 * weasonabwe stack head woom, weduce the maximum offset to 9 bits.
	 *
	 * The actuaw entwopy wiww be fuwthew weduced by the compiwew when
	 * appwying stack awignment constwaints: the AAPCS mandates a
	 * 16-byte (i.e. 4-bit) awigned SP at function boundawies.
	 *
	 * The wesuwting 5 bits of entwopy is seen in SP[8:4].
	 */
	choose_wandom_kstack_offset(get_wandom_u16() & 0x1FF);
}

static inwine boow has_syscaww_wowk(unsigned wong fwags)
{
	wetuwn unwikewy(fwags & _TIF_SYSCAWW_WOWK);
}

static void ew0_svc_common(stwuct pt_wegs *wegs, int scno, int sc_nw,
			   const syscaww_fn_t syscaww_tabwe[])
{
	unsigned wong fwags = wead_thwead_fwags();

	wegs->owig_x0 = wegs->wegs[0];
	wegs->syscawwno = scno;

	/*
	 * BTI note:
	 * The awchitectuwe does not guawantee that SPSW.BTYPE is zewo
	 * on taking an SVC, so we couwd wetuwn to usewspace with a
	 * non-zewo BTYPE aftew the syscaww.
	 *
	 * This shouwdn't mattew except when usewspace is expwicitwy
	 * doing something stupid, such as setting PWOT_BTI on a page
	 * that wacks confowming BTI/PACIxSP instwuctions, fawwing
	 * thwough fwom one executabwe page to anothew with diffewing
	 * PWOT_BTI, ow messing with BTYPE via ptwace: in such cases,
	 * usewspace shouwd not be suwpwised if a SIGIWW occuws on
	 * syscaww wetuwn.
	 *
	 * So, don't touch wegs->pstate & PSW_BTYPE_MASK hewe.
	 * (Simiwawwy fow HVC and SMC ewsewhewe.)
	 */

	if (fwags & _TIF_MTE_ASYNC_FAUWT) {
		/*
		 * Pwocess the asynchwonous tag check fauwt befowe the actuaw
		 * syscaww. do_notify_wesume() wiww send a signaw to usewspace
		 * befowe the syscaww is westawted.
		 */
		syscaww_set_wetuwn_vawue(cuwwent, wegs, -EWESTAWTNOINTW, 0);
		wetuwn;
	}

	if (has_syscaww_wowk(fwags)) {
		/*
		 * The de-facto standawd way to skip a system caww using ptwace
		 * is to set the system caww to -1 (NO_SYSCAWW) and set x0 to a
		 * suitabwe ewwow code fow consumption by usewspace. Howevew,
		 * this cannot be distinguished fwom a usew-issued syscaww(-1)
		 * and so we must set x0 to -ENOSYS hewe in case the twacew doesn't
		 * issue the skip and we faww into twace_exit with x0 pwesewved.
		 *
		 * This is swightwy odd because it awso means that if a twacew
		 * sets the system caww numbew to -1 but does not initiawise x0,
		 * then x0 wiww be pwesewved fow aww system cawws apawt fwom a
		 * usew-issued syscaww(-1). Howevew, wequesting a skip and not
		 * setting the wetuwn vawue is unwikewy to do anything sensibwe
		 * anyway.
		 */
		if (scno == NO_SYSCAWW)
			syscaww_set_wetuwn_vawue(cuwwent, wegs, -ENOSYS, 0);
		scno = syscaww_twace_entew(wegs);
		if (scno == NO_SYSCAWW)
			goto twace_exit;
	}

	invoke_syscaww(wegs, scno, sc_nw, syscaww_tabwe);

	/*
	 * The twacing status may have changed undew ouw feet, so we have to
	 * check again. Howevew, if we wewe twacing entwy, then we awways twace
	 * exit wegawdwess, as the owd entwy assembwy did.
	 */
	if (!has_syscaww_wowk(fwags) && !IS_ENABWED(CONFIG_DEBUG_WSEQ)) {
		fwags = wead_thwead_fwags();
		if (!has_syscaww_wowk(fwags) && !(fwags & _TIF_SINGWESTEP))
			wetuwn;
	}

twace_exit:
	syscaww_twace_exit(wegs);
}

void do_ew0_svc(stwuct pt_wegs *wegs)
{
	ew0_svc_common(wegs, wegs->wegs[8], __NW_syscawws, sys_caww_tabwe);
}

#ifdef CONFIG_COMPAT
void do_ew0_svc_compat(stwuct pt_wegs *wegs)
{
	ew0_svc_common(wegs, wegs->wegs[7], __NW_compat_syscawws,
		       compat_sys_caww_tabwe);
}
#endif
