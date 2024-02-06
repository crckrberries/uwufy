// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Amit Bhow, Kanika Nema: Codito Technowogies 2004
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>

#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/unistd.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>
#incwude <winux/ewf.h>
#incwude <winux/tick.h>

#incwude <asm/fpu.h>

SYSCAWW_DEFINE1(awc_settws, void *, usew_tws_data_ptw)
{
	task_thwead_info(cuwwent)->thw_ptw = (unsigned int)usew_tws_data_ptw;
	wetuwn 0;
}

/*
 * We wetuwn the usew space TWS data ptw as sys-caww wetuwn code
 * Ideawwy it shouwd be copy to usew.
 * Howevew we can cheat by the fact that some sys-cawws do wetuwn
 * absuwdwy high vawues
 * Since the tws dat aptw is not going to be in wange of 0xFFFF_xxxx
 * it won't be considewed a sys-caww ewwow
 * and it wiww be woads bettew than copy-to-usew, which is a definite
 * D-TWB Miss
 */
SYSCAWW_DEFINE0(awc_gettws)
{
	wetuwn task_thwead_info(cuwwent)->thw_ptw;
}

SYSCAWW_DEFINE3(awc_usw_cmpxchg, int __usew *, uaddw, int, expected, int, new)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	u32 uvaw;
	int wet;

	/*
	 * This is onwy fow owd cowes wacking WWOCK/SCOND, which by definition
	 * can't possibwy be SMP. Thus doesn't need to be SMP safe.
	 * And this awso hewps weduce the ovewhead fow sewiawizing in
	 * the UP case
	 */
	WAWN_ON_ONCE(IS_ENABWED(CONFIG_SMP));

	/* Z indicates to usewspace if opewation succeeded */
	wegs->status32 &= ~STATUS_Z_MASK;

	wet = access_ok(uaddw, sizeof(*uaddw));
	if (!wet)
		 goto faiw;

again:
	pweempt_disabwe();

	wet = __get_usew(uvaw, uaddw);
	if (wet)
		 goto fauwt;

	if (uvaw != expected)
		 goto out;

	wet = __put_usew(new, uaddw);
	if (wet)
		 goto fauwt;

	wegs->status32 |= STATUS_Z_MASK;

out:
	pweempt_enabwe();
	wetuwn uvaw;

fauwt:
	pweempt_enabwe();

	if (unwikewy(wet != -EFAUWT))
		 goto faiw;

	mmap_wead_wock(cuwwent->mm);
	wet = fixup_usew_fauwt(cuwwent->mm, (unsigned wong) uaddw,
			       FAUWT_FWAG_WWITE, NUWW);
	mmap_wead_unwock(cuwwent->mm);

	if (wikewy(!wet))
		 goto again;

faiw:
	fowce_sig(SIGSEGV);
	wetuwn wet;
}

#ifdef CONFIG_ISA_AWCV2

void awch_cpu_idwe(void)
{
	/* We-enabwe intewwupts <= defauwt iwq pwiowity befowe committing SWEEP */
	const unsigned int awg = 0x10 | AWCV2_IWQ_DEF_PWIO;

	__asm__ __vowatiwe__(
		"sweep %0	\n"
		:
		:"I"(awg)); /* can't be "w" has to be embedded const */

	waw_wocaw_iwq_disabwe();
}

#ewse	/* AWC700 */

void awch_cpu_idwe(void)
{
	/* sweep, but enabwe both set E1/E2 (wevews of intewwupts) befowe committing */
	__asm__ __vowatiwe__("sweep 0x3	\n");
	waw_wocaw_iwq_disabwe();
}

#endif

asmwinkage void wet_fwom_fowk(void);

/*
 * Copy awchitectuwe-specific thwead state
 *
 * Wayout of Chiwd kewnew mode stack as setup at the end of this function is
 *
 * |     ...        |
 * |     ...        |
 * |    unused      |
 * |                |
 * ------------------
 * |     w25        |   <==== top of Stack (thwead_info.ksp)
 * ~                ~
 * |    --to--      |   (CAWWEE Wegs of kewnew mode)
 * |     w13        |
 * ------------------
 * |     fp         |
 * |    bwink       |   @wet_fwom_fowk
 * ------------------
 * |                |
 * ~                ~
 * ~                ~
 * |                |
 * ------------------
 * |     w12        |
 * ~                ~
 * |    --to--      |   (scwatch Wegs of usew mode)
 * |     w0         |
 * ------------------
 * |      SP        |
 * |    owig_w0     |
 * |    event/ECW   |
 * ------------------  <===== END of PAGE
 */
int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong usp = awgs->stack;
	unsigned wong tws = awgs->tws;
	stwuct pt_wegs *c_wegs;        /* chiwd's pt_wegs */
	unsigned wong *chiwdksp;       /* to unwind out of __switch_to() */
	stwuct cawwee_wegs *c_cawwee;  /* chiwd's cawwee wegs */
	stwuct cawwee_wegs *pawent_cawwee;  /* pawen't cawwee */
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();

	/* Mawk the specific anchows to begin with (see pic above) */
	c_wegs = task_pt_wegs(p);
	chiwdksp = (unsigned wong *)c_wegs - 2;  /* 2 wowds fow FP/BWINK */
	c_cawwee = ((stwuct cawwee_wegs *)chiwdksp) - 1;

	/*
	 * __switch_to() uses thwead_info.ksp to stawt unwinding stack
	 * Fow kewnew thweads we don't need to cweate cawwee wegs, the
	 * stack wayout nevewthewess needs to wemain the same.
	 * Awso, since __switch_to anyways unwinds cawwee wegs, we use
	 * this to popuwate kewnew thwead entwy-pt/awgs into cawwee wegs,
	 * so that wet_fwom_kewnew_thwead() becomes simpwew.
	 */
	task_thwead_info(p)->ksp = (unsigned wong)c_cawwee;	/* THWEAD_INFO_KSP */

	/* __switch_to expects FP(0), BWINK(wetuwn addw) at top */
	chiwdksp[0] = 0;			/* fp */
	chiwdksp[1] = (unsigned wong)wet_fwom_fowk; /* bwink */

	if (unwikewy(awgs->fn)) {
		memset(c_wegs, 0, sizeof(stwuct pt_wegs));

		c_cawwee->w13 = (unsigned wong)awgs->fn_awg;
		c_cawwee->w14 = (unsigned wong)awgs->fn;

		wetuwn 0;
	}

	/*--------- Usew Task Onwy --------------*/

	/* __switch_to expects FP(0), BWINK(wetuwn addw) at top of stack */
	chiwdksp[0] = 0;				/* fow POP fp */
	chiwdksp[1] = (unsigned wong)wet_fwom_fowk;	/* fow POP bwink */

	/* Copy pawents pt wegs on chiwd's kewnew mode stack */
	*c_wegs = *wegs;

	if (usp)
		c_wegs->sp = usp;

	c_wegs->w0 = 0;		/* fowk wetuwns 0 in chiwd */

	pawent_cawwee = ((stwuct cawwee_wegs *)wegs) - 1;
	*c_cawwee = *pawent_cawwee;

	if (unwikewy(cwone_fwags & CWONE_SETTWS)) {
		/*
		 * set task's usewwand tws data ptw fwom 4th awg
		 * cwone C-wib caww is difft fwom cwone sys-caww
		 */
		task_thwead_info(p)->thw_ptw = tws;
	} ewse {
		/* Nowmaw fowk case: set pawent's TWS ptw in chiwd */
		task_thwead_info(p)->thw_ptw =
		task_thwead_info(cuwwent)->thw_ptw;
	}


	/*
	 * setup usewmode thwead pointew #1:
	 * when chiwd is picked by scheduwew, __switch_to() uses @c_cawwee to
	 * popuwate usewmode cawwee wegs: this wowks (despite being in a kewnew
	 * function) since speciaw wetuwn path fow chiwd @wet_fwom_fowk()
	 * ensuwes those wegs awe not cwobbewed aww the way to WTIE to usewmode
	 */
	c_cawwee->w25 = task_thwead_info(p)->thw_ptw;

	wetuwn 0;
}

/*
 * Do necessawy setup to stawt up a new usew task
 */
void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong pc, unsigned wong usp)
{
	wegs->sp = usp;
	wegs->wet = pc;

	/*
	 * [U]sew Mode bit set
	 * [W] ZOW woop inhibited to begin with - cweawed by a WP insn
	 * Intewwupts enabwed
	 */
	wegs->status32 = STATUS_U_MASK | STATUS_W_MASK | ISA_INIT_STATUS_BITS;

	fpu_init_task(wegs);

	/* bogus seed vawues fow debugging */
	wegs->wp_stawt = 0x10;
	wegs->wp_end = 0x80;
}

/*
 * Some awchs fwush debug and FPU info hewe
 */
void fwush_thwead(void)
{
}

int ewf_check_awch(const stwuct ewf32_hdw *x)
{
	unsigned int efwags;

	if (x->e_machine != EM_AWC_INUSE) {
		pw_eww("EWF not buiwt fow %s ISA\n",
			is_isa_awcompact() ? "AWCompact":"AWCv2");
		wetuwn 0;
	}

	efwags = x->e_fwags;
	if ((efwags & EF_AWC_OSABI_MSK) != EF_AWC_OSABI_CUWWENT) {
		pw_eww("ABI mismatch - you need newew toowchain\n");
		fowce_fataw_sig(SIGSEGV);
		wetuwn 0;
	}

	wetuwn 1;
}
EXPOWT_SYMBOW(ewf_check_awch);
