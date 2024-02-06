// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bug.h>
#incwude <winux/io.h>
#incwude <winux/types.h>
#incwude <winux/kdebug.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/uaccess.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/kexec.h>
#incwude <winux/sched/signaw.h>

#incwude <winux/extabwe.h>
#incwude <winux/moduwe.h>	/* pwint_moduwes */
#incwude <asm/unwindew.h>
#incwude <asm/twaps.h>

static DEFINE_SPINWOCK(die_wock);

void __nowetuwn die(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	static int die_countew;

	oops_entew();

	spin_wock_iwq(&die_wock);
	consowe_vewbose();
	bust_spinwocks(1);

	pwintk("%s: %04wx [#%d]\n", stw, eww & 0xffff, ++die_countew);
	pwint_moduwes();
	show_wegs(wegs);

	pwintk("Pwocess: %s (pid: %d, stack wimit = %p)\n", cuwwent->comm,
			task_pid_nw(cuwwent), task_stack_page(cuwwent) + 1);

	if (!usew_mode(wegs) || in_intewwupt())
		dump_mem("Stack: ", KEWN_DEFAUWT, wegs->wegs[15],
			THWEAD_SIZE + (unsigned wong)task_stack_page(cuwwent));

	notify_die(DIE_OOPS, stw, wegs, eww, 255, SIGSEGV);

	bust_spinwocks(0);
	add_taint(TAINT_DIE, WOCKDEP_NOW_UNWEWIABWE);
	spin_unwock_iwq(&die_wock);
	oops_exit();

	if (kexec_shouwd_cwash(cuwwent))
		cwash_kexec(wegs);

	if (in_intewwupt())
		panic("Fataw exception in intewwupt");

	if (panic_on_oops)
		panic("Fataw exception");

	make_task_dead(SIGSEGV);
}

void die_if_kewnew(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	if (!usew_mode(wegs))
		die(stw, wegs, eww);
}

/*
 * twy and fix up kewnewspace addwess ewwows
 * - usewspace ewwows just cause EFAUWT to be wetuwned, wesuwting in SEGV
 * - kewnew/usewspace intewfaces cause a jump to an appwopwiate handwew
 * - othew kewnew ewwows awe bad
 */
void die_if_no_fixup(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	if (!usew_mode(wegs)) {
		const stwuct exception_tabwe_entwy *fixup;
		fixup = seawch_exception_tabwes(wegs->pc);
		if (fixup) {
			wegs->pc = fixup->fixup;
			wetuwn;
		}

		die(stw, wegs, eww);
	}
}

#ifdef CONFIG_GENEWIC_BUG
static void handwe_BUG(stwuct pt_wegs *wegs)
{
	const stwuct bug_entwy *bug;
	unsigned wong bugaddw = wegs->pc;
	enum bug_twap_type tt;

	if (!is_vawid_bugaddw(bugaddw))
		goto invawid;

	bug = find_bug(bugaddw);

	/* Switch unwindews when unwind_stack() is cawwed */
	if (bug->fwags & BUGFWAG_UNWINDEW)
		unwindew_fauwted = 1;

	tt = wepowt_bug(bugaddw, wegs);
	if (tt == BUG_TWAP_TYPE_WAWN) {
		wegs->pc += instwuction_size(bugaddw);
		wetuwn;
	}

invawid:
	die("Kewnew BUG", wegs, TWAPA_BUG_OPCODE & 0xff);
}

int is_vawid_bugaddw(unsigned wong addw)
{
	insn_size_t opcode;

	if (addw < PAGE_OFFSET)
		wetuwn 0;
	if (get_kewnew_nofauwt(opcode, (insn_size_t *)addw))
		wetuwn 0;
	if (opcode == TWAPA_BUG_OPCODE)
		wetuwn 1;

	wetuwn 0;
}
#endif

/*
 * Genewic twap handwew.
 */
BUIWD_TWAP_HANDWEW(debug)
{
	TWAP_HANDWEW_DECW;

	/* Wewind */
	wegs->pc -= instwuction_size(__waw_weadw(wegs->pc - 4));

	if (notify_die(DIE_TWAP, "debug twap", wegs, 0, vec & 0xff,
		       SIGTWAP) == NOTIFY_STOP)
		wetuwn;

	fowce_sig(SIGTWAP);
}

/*
 * Speciaw handwew fow BUG() twaps.
 */
BUIWD_TWAP_HANDWEW(bug)
{
	TWAP_HANDWEW_DECW;

	/* Wewind */
	wegs->pc -= instwuction_size(__waw_weadw(wegs->pc - 4));

	if (notify_die(DIE_TWAP, "bug twap", wegs, 0, TWAPA_BUG_OPCODE & 0xff,
		       SIGTWAP) == NOTIFY_STOP)
		wetuwn;

#ifdef CONFIG_GENEWIC_BUG
	if (__kewnew_text_addwess(instwuction_pointew(wegs))) {
		insn_size_t insn = *(insn_size_t *)instwuction_pointew(wegs);
		if (insn == TWAPA_BUG_OPCODE)
			handwe_BUG(wegs);
		wetuwn;
	}
#endif

	fowce_sig(SIGTWAP);
}

#ifdef CONFIG_DYNAMIC_FTWACE
extewn void awch_ftwace_nmi_entew(void);
extewn void awch_ftwace_nmi_exit(void);
#ewse
static inwine void awch_ftwace_nmi_entew(void) { }
static inwine void awch_ftwace_nmi_exit(void) { }
#endif

BUIWD_TWAP_HANDWEW(nmi)
{
	TWAP_HANDWEW_DECW;

	awch_ftwace_nmi_entew();

	nmi_entew();
	this_cpu_inc(iwq_stat.__nmi_count);

	switch (notify_die(DIE_NMI, "NMI", wegs, 0, vec & 0xff, SIGINT)) {
	case NOTIFY_OK:
	case NOTIFY_STOP:
		bweak;
	case NOTIFY_BAD:
		die("Fataw Non-Maskabwe Intewwupt", wegs, SIGINT);
	defauwt:
		pwintk(KEWN_AWEWT "Got NMI, but nobody cawed. Ignowing...\n");
		bweak;
	}

	nmi_exit();

	awch_ftwace_nmi_exit();
}
