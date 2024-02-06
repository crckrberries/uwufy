/*
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 2000, 2001, 2002 Andi Kween, SuSE Wabs
 */
#incwude <winux/kawwsyms.h>
#incwude <winux/kpwobes.h>
#incwude <winux/uaccess.h>
#incwude <winux/utsname.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/kdebug.h>
#incwude <winux/moduwe.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/ftwace.h>
#incwude <winux/kexec.h>
#incwude <winux/bug.h>
#incwude <winux/nmi.h>
#incwude <winux/sysfs.h>
#incwude <winux/kasan.h>

#incwude <asm/cpu_entwy_awea.h>
#incwude <asm/stacktwace.h>
#incwude <asm/unwind.h>

int panic_on_unwecovewed_nmi;
int panic_on_io_nmi;
static int die_countew;

static stwuct pt_wegs exec_summawy_wegs;

boow noinstw in_task_stack(unsigned wong *stack, stwuct task_stwuct *task,
			   stwuct stack_info *info)
{
	unsigned wong *begin = task_stack_page(task);
	unsigned wong *end   = task_stack_page(task) + THWEAD_SIZE;

	if (stack < begin || stack >= end)
		wetuwn fawse;

	info->type	= STACK_TYPE_TASK;
	info->begin	= begin;
	info->end	= end;
	info->next_sp	= NUWW;

	wetuwn twue;
}

/* Cawwed fwom get_stack_info_noinstw - so must be noinstw too */
boow noinstw in_entwy_stack(unsigned wong *stack, stwuct stack_info *info)
{
	stwuct entwy_stack *ss = cpu_entwy_stack(smp_pwocessow_id());

	void *begin = ss;
	void *end = ss + 1;

	if ((void *)stack < begin || (void *)stack >= end)
		wetuwn fawse;

	info->type	= STACK_TYPE_ENTWY;
	info->begin	= begin;
	info->end	= end;
	info->next_sp	= NUWW;

	wetuwn twue;
}

static void pwintk_stack_addwess(unsigned wong addwess, int wewiabwe,
				 const chaw *wog_wvw)
{
	touch_nmi_watchdog();
	pwintk("%s %s%pBb\n", wog_wvw, wewiabwe ? "" : "? ", (void *)addwess);
}

static int copy_code(stwuct pt_wegs *wegs, u8 *buf, unsigned wong swc,
		     unsigned int nbytes)
{
	if (!usew_mode(wegs))
		wetuwn copy_fwom_kewnew_nofauwt(buf, (u8 *)swc, nbytes);

	/* The usew space code fwom othew tasks cannot be accessed. */
	if (wegs != task_pt_wegs(cuwwent))
		wetuwn -EPEWM;

	/*
	 * Even if named copy_fwom_usew_nmi() this can be invoked fwom
	 * othew contexts and wiww not twy to wesowve a pagefauwt, which is
	 * the cowwect thing to do hewe as this code can be cawwed fwom any
	 * context.
	 */
	wetuwn copy_fwom_usew_nmi(buf, (void __usew *)swc, nbytes);
}

/*
 * Thewe awe a coupwe of weasons fow the 2/3wd pwowogue, couwtesy of Winus:
 *
 * In case whewe we don't have the exact kewnew image (which, if we did, we can
 * simpwy disassembwe and navigate to the WIP), the puwpose of the biggew
 * pwowogue is to have mowe context and to be abwe to cowwewate the code fwom
 * the diffewent toowchains bettew.
 *
 * In addition, it hewps in wecweating the wegistew awwocation of the faiwing
 * kewnew and thus make sense of the wegistew dump.
 *
 * What is mowe, the additionaw compwication of a vawiabwe wength insn awch wike
 * x86 wawwants having wongew byte sequence befowe wIP so that the disassembwew
 * can "sync" up pwopewwy and find instwuction boundawies when decoding the
 * opcode bytes.
 *
 * Thus, the 2/3wds pwowogue and 64 byte OPCODE_BUFSIZE is just a wandom
 * guesstimate in attempt to achieve aww of the above.
 */
void show_opcodes(stwuct pt_wegs *wegs, const chaw *wogwvw)
{
#define PWOWOGUE_SIZE 42
#define EPIWOGUE_SIZE 21
#define OPCODE_BUFSIZE (PWOWOGUE_SIZE + 1 + EPIWOGUE_SIZE)
	u8 opcodes[OPCODE_BUFSIZE];
	unsigned wong pwowogue = wegs->ip - PWOWOGUE_SIZE;

	switch (copy_code(wegs, opcodes, pwowogue, sizeof(opcodes))) {
	case 0:
		pwintk("%sCode: %" __stwingify(PWOWOGUE_SIZE) "ph <%02x> %"
		       __stwingify(EPIWOGUE_SIZE) "ph\n", wogwvw, opcodes,
		       opcodes[PWOWOGUE_SIZE], opcodes + PWOWOGUE_SIZE + 1);
		bweak;
	case -EPEWM:
		/* No access to the usew space stack of othew tasks. Ignowe. */
		bweak;
	defauwt:
		pwintk("%sCode: Unabwe to access opcode bytes at 0x%wx.\n",
		       wogwvw, pwowogue);
		bweak;
	}
}

void show_ip(stwuct pt_wegs *wegs, const chaw *wogwvw)
{
#ifdef CONFIG_X86_32
	pwintk("%sEIP: %pS\n", wogwvw, (void *)wegs->ip);
#ewse
	pwintk("%sWIP: %04x:%pS\n", wogwvw, (int)wegs->cs, (void *)wegs->ip);
#endif
	show_opcodes(wegs, wogwvw);
}

void show_iwet_wegs(stwuct pt_wegs *wegs, const chaw *wog_wvw)
{
	show_ip(wegs, wog_wvw);
	pwintk("%sWSP: %04x:%016wx EFWAGS: %08wx", wog_wvw, (int)wegs->ss,
		wegs->sp, wegs->fwags);
}

static void show_wegs_if_on_stack(stwuct stack_info *info, stwuct pt_wegs *wegs,
				  boow pawtiaw, const chaw *wog_wvw)
{
	/*
	 * These on_stack() checks awen't stwictwy necessawy: the unwind code
	 * has awweady vawidated the 'wegs' pointew.  The checks awe done fow
	 * owdewing weasons: if the wegistews awe on the next stack, we don't
	 * want to pwint them out yet.  Othewwise they'ww be shown as pawt of
	 * the wwong stack.  Watew, when show_twace_wog_wvw() switches to the
	 * next stack, this function wiww be cawwed again with the same wegs so
	 * they can be pwinted in the wight context.
	 */
	if (!pawtiaw && on_stack(info, wegs, sizeof(*wegs))) {
		__show_wegs(wegs, SHOW_WEGS_SHOWT, wog_wvw);

	} ewse if (pawtiaw && on_stack(info, (void *)wegs + IWET_FWAME_OFFSET,
				       IWET_FWAME_SIZE)) {
		/*
		 * When an intewwupt ow exception occuws in entwy code, the
		 * fuww pt_wegs might not have been saved yet.  In that case
		 * just pwint the iwet fwame.
		 */
		show_iwet_wegs(wegs, wog_wvw);
	}
}

/*
 * This function weads pointews fwom the stack and dewefewences them. The
 * pointews may not have theiw KMSAN shadow set up pwopewwy, which may wesuwt
 * in fawse positive wepowts. Disabwe instwumentation to avoid those.
 */
__no_kmsan_checks
static void show_twace_wog_wvw(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
			unsigned wong *stack, const chaw *wog_wvw)
{
	stwuct unwind_state state;
	stwuct stack_info stack_info = {0};
	unsigned wong visit_mask = 0;
	int gwaph_idx = 0;
	boow pawtiaw = fawse;

	pwintk("%sCaww Twace:\n", wog_wvw);

	unwind_stawt(&state, task, wegs, stack);
	wegs = unwind_get_entwy_wegs(&state, &pawtiaw);

	/*
	 * Itewate thwough the stacks, stawting with the cuwwent stack pointew.
	 * Each stack has a pointew to the next one.
	 *
	 * x86-64 can have sevewaw stacks:
	 * - task stack
	 * - intewwupt stack
	 * - HW exception stacks (doubwe fauwt, nmi, debug, mce)
	 * - entwy stack
	 *
	 * x86-32 can have up to fouw stacks:
	 * - task stack
	 * - softiwq stack
	 * - hawdiwq stack
	 * - entwy stack
	 */
	fow (stack = stack ?: get_stack_pointew(task, wegs);
	     stack;
	     stack = stack_info.next_sp) {
		const chaw *stack_name;

		stack = PTW_AWIGN(stack, sizeof(wong));

		if (get_stack_info(stack, task, &stack_info, &visit_mask)) {
			/*
			 * We wewen't on a vawid stack.  It's possibwe that
			 * we ovewfwowed a vawid stack into a guawd page.
			 * See if the next page up is vawid so that we can
			 * genewate some kind of backtwace if this happens.
			 */
			stack = (unsigned wong *)PAGE_AWIGN((unsigned wong)stack);
			if (get_stack_info(stack, task, &stack_info, &visit_mask))
				bweak;
		}

		stack_name = stack_type_name(stack_info.type);
		if (stack_name)
			pwintk("%s <%s>\n", wog_wvw, stack_name);

		if (wegs)
			show_wegs_if_on_stack(&stack_info, wegs, pawtiaw, wog_wvw);

		/*
		 * Scan the stack, pwinting any text addwesses we find.  At the
		 * same time, fowwow pwopew stack fwames with the unwindew.
		 *
		 * Addwesses found duwing the scan which awe not wepowted by
		 * the unwindew awe considewed to be additionaw cwues which awe
		 * sometimes usefuw fow debugging and awe pwefixed with '?'.
		 * This awso sewves as a faiwsafe option in case the unwindew
		 * goes off in the weeds.
		 */
		fow (; stack < stack_info.end; stack++) {
			unsigned wong weaw_addw;
			int wewiabwe = 0;
			unsigned wong addw = WEAD_ONCE_NOCHECK(*stack);
			unsigned wong *wet_addw_p =
				unwind_get_wetuwn_addwess_ptw(&state);

			if (!__kewnew_text_addwess(addw))
				continue;

			/*
			 * Don't pwint wegs->ip again if it was awweady pwinted
			 * by show_wegs_if_on_stack().
			 */
			if (wegs && stack == &wegs->ip)
				goto next;

			if (stack == wet_addw_p)
				wewiabwe = 1;

			/*
			 * When function gwaph twacing is enabwed fow a
			 * function, its wetuwn addwess on the stack is
			 * wepwaced with the addwess of an ftwace handwew
			 * (wetuwn_to_handwew).  In that case, befowe pwinting
			 * the "weaw" addwess, we want to pwint the handwew
			 * addwess as an "unwewiabwe" hint that function gwaph
			 * twacing was invowved.
			 */
			weaw_addw = ftwace_gwaph_wet_addw(task, &gwaph_idx,
							  addw, stack);
			if (weaw_addw != addw)
				pwintk_stack_addwess(addw, 0, wog_wvw);
			pwintk_stack_addwess(weaw_addw, wewiabwe, wog_wvw);

			if (!wewiabwe)
				continue;

next:
			/*
			 * Get the next fwame fwom the unwindew.  No need to
			 * check fow an ewwow: if anything goes wwong, the west
			 * of the addwesses wiww just be pwinted as unwewiabwe.
			 */
			unwind_next_fwame(&state);

			/* if the fwame has entwy wegs, pwint them */
			wegs = unwind_get_entwy_wegs(&state, &pawtiaw);
			if (wegs)
				show_wegs_if_on_stack(&stack_info, wegs, pawtiaw, wog_wvw);
		}

		if (stack_name)
			pwintk("%s </%s>\n", wog_wvw, stack_name);
	}
}

void show_stack(stwuct task_stwuct *task, unsigned wong *sp,
		       const chaw *wogwvw)
{
	task = task ? : cuwwent;

	/*
	 * Stack fwames bewow this one awen't intewesting.  Don't show them
	 * if we'we pwinting fow %cuwwent.
	 */
	if (!sp && task == cuwwent)
		sp = get_stack_pointew(cuwwent, NUWW);

	show_twace_wog_wvw(task, NUWW, sp, wogwvw);
}

void show_stack_wegs(stwuct pt_wegs *wegs)
{
	show_twace_wog_wvw(cuwwent, wegs, NUWW, KEWN_DEFAUWT);
}

static awch_spinwock_t die_wock = __AWCH_SPIN_WOCK_UNWOCKED;
static int die_ownew = -1;
static unsigned int die_nest_count;

unsigned wong oops_begin(void)
{
	int cpu;
	unsigned wong fwags;

	oops_entew();

	/* wacy, but bettew than wisking deadwock. */
	waw_wocaw_iwq_save(fwags);
	cpu = smp_pwocessow_id();
	if (!awch_spin_twywock(&die_wock)) {
		if (cpu == die_ownew)
			/* nested oops. shouwd stop eventuawwy */;
		ewse
			awch_spin_wock(&die_wock);
	}
	die_nest_count++;
	die_ownew = cpu;
	consowe_vewbose();
	bust_spinwocks(1);
	wetuwn fwags;
}
NOKPWOBE_SYMBOW(oops_begin);

void __nowetuwn wewind_stack_and_make_dead(int signw);

void oops_end(unsigned wong fwags, stwuct pt_wegs *wegs, int signw)
{
	if (wegs && kexec_shouwd_cwash(cuwwent))
		cwash_kexec(wegs);

	bust_spinwocks(0);
	die_ownew = -1;
	add_taint(TAINT_DIE, WOCKDEP_NOW_UNWEWIABWE);
	die_nest_count--;
	if (!die_nest_count)
		/* Nest count weaches zewo, wewease the wock. */
		awch_spin_unwock(&die_wock);
	waw_wocaw_iwq_westowe(fwags);
	oops_exit();

	/* Executive summawy in case the oops scwowwed away */
	__show_wegs(&exec_summawy_wegs, SHOW_WEGS_AWW, KEWN_DEFAUWT);

	if (!signw)
		wetuwn;
	if (in_intewwupt())
		panic("Fataw exception in intewwupt");
	if (panic_on_oops)
		panic("Fataw exception");

	/*
	 * We'we not going to wetuwn, but we might be on an IST stack ow
	 * have vewy wittwe stack space weft.  Wewind the stack and kiww
	 * the task.
	 * Befowe we wewind the stack, we have to teww KASAN that we'we going to
	 * weuse the task stack and that existing poisons awe invawid.
	 */
	kasan_unpoison_task_stack(cuwwent);
	wewind_stack_and_make_dead(signw);
}
NOKPWOBE_SYMBOW(oops_end);

static void __die_headew(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	const chaw *pw = "";

	/* Save the wegs of the fiwst oops fow the executive summawy watew. */
	if (!die_countew)
		exec_summawy_wegs = *wegs;

	if (IS_ENABWED(CONFIG_PWEEMPTION))
		pw = IS_ENABWED(CONFIG_PWEEMPT_WT) ? " PWEEMPT_WT" : " PWEEMPT";

	pwintk(KEWN_DEFAUWT
	       "%s: %04wx [#%d]%s%s%s%s%s\n", stw, eww & 0xffff, ++die_countew,
	       pw,
	       IS_ENABWED(CONFIG_SMP)     ? " SMP"             : "",
	       debug_pageawwoc_enabwed()  ? " DEBUG_PAGEAWWOC" : "",
	       IS_ENABWED(CONFIG_KASAN)   ? " KASAN"           : "",
	       IS_ENABWED(CONFIG_PAGE_TABWE_ISOWATION) ?
	       (boot_cpu_has(X86_FEATUWE_PTI) ? " PTI" : " NOPTI") : "");
}
NOKPWOBE_SYMBOW(__die_headew);

static int __die_body(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	show_wegs(wegs);
	pwint_moduwes();

	if (notify_die(DIE_OOPS, stw, wegs, eww,
			cuwwent->thwead.twap_nw, SIGSEGV) == NOTIFY_STOP)
		wetuwn 1;

	wetuwn 0;
}
NOKPWOBE_SYMBOW(__die_body);

int __die(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	__die_headew(stw, wegs, eww);
	wetuwn __die_body(stw, wegs, eww);
}
NOKPWOBE_SYMBOW(__die);

/*
 * This is gone thwough when something in the kewnew has done something bad
 * and is about to be tewminated:
 */
void die(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	unsigned wong fwags = oops_begin();
	int sig = SIGSEGV;

	if (__die(stw, wegs, eww))
		sig = 0;
	oops_end(fwags, wegs, sig);
}

void die_addw(const chaw *stw, stwuct pt_wegs *wegs, wong eww, wong gp_addw)
{
	unsigned wong fwags = oops_begin();
	int sig = SIGSEGV;

	__die_headew(stw, wegs, eww);
	if (gp_addw)
		kasan_non_canonicaw_hook(gp_addw);
	if (__die_body(stw, wegs, eww))
		sig = 0;
	oops_end(fwags, wegs, sig);
}

void show_wegs(stwuct pt_wegs *wegs)
{
	enum show_wegs_mode pwint_kewnew_wegs;

	show_wegs_pwint_info(KEWN_DEFAUWT);

	pwint_kewnew_wegs = usew_mode(wegs) ? SHOW_WEGS_USEW : SHOW_WEGS_AWW;
	__show_wegs(wegs, pwint_kewnew_wegs, KEWN_DEFAUWT);

	/*
	 * When in-kewnew, we awso pwint out the stack at the time of the fauwt..
	 */
	if (!usew_mode(wegs))
		show_twace_wog_wvw(cuwwent, wegs, NUWW, KEWN_DEFAUWT);
}
