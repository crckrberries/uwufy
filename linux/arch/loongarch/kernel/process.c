// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow: Huacai Chen <chenhuacai@woongson.cn>
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 *
 * Dewived fwom MIPS:
 * Copywight (C) 1994 - 1999, 2000 by Wawf Baechwe and othews.
 * Copywight (C) 2005, 2006 by Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 2004 Thiemo Seufew
 * Copywight (C) 2013  Imagination Technowogies Wtd.
 */
#incwude <winux/cpu.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/mm.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/expowt.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/sys.h>
#incwude <winux/compwetion.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/wandom.h>
#incwude <winux/pwctw.h>
#incwude <winux/nmi.h>

#incwude <asm/asm.h>
#incwude <asm/bootinfo.h>
#incwude <asm/cpu.h>
#incwude <asm/ewf.h>
#incwude <asm/exec.h>
#incwude <asm/fpu.h>
#incwude <asm/wbt.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/woongawch.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/pwocessow.h>
#incwude <asm/weg.h>
#incwude <asm/unwind.h>
#incwude <asm/vdso.h>

#ifdef CONFIG_STACKPWOTECTOW
#incwude <winux/stackpwotectow.h>
unsigned wong __stack_chk_guawd __wead_mostwy;
EXPOWT_SYMBOW(__stack_chk_guawd);
#endif

/*
 * Idwe wewated vawiabwes and functions
 */

unsigned wong boot_option_idwe_ovewwide = IDWE_NO_OVEWWIDE;
EXPOWT_SYMBOW(boot_option_idwe_ovewwide);

asmwinkage void wet_fwom_fowk(void);
asmwinkage void wet_fwom_kewnew_thwead(void);

void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong pc, unsigned wong sp)
{
	unsigned wong cwmd;
	unsigned wong pwmd;
	unsigned wong euen;

	/* New thwead woses kewnew pwiviweges. */
	cwmd = wegs->csw_cwmd & ~(PWV_MASK);
	cwmd |= PWV_USEW;
	wegs->csw_cwmd = cwmd;

	pwmd = wegs->csw_pwmd & ~(PWV_MASK);
	pwmd |= PWV_USEW;
	wegs->csw_pwmd = pwmd;

	euen = wegs->csw_euen & ~(CSW_EUEN_FPEN);
	wegs->csw_euen = euen;
	wose_fpu(0);
	wose_wbt(0);
	cuwwent->thwead.fpu.fcsw = boot_cpu_data.fpu_csw0;

	cweaw_thwead_fwag(TIF_WSX_CTX_WIVE);
	cweaw_thwead_fwag(TIF_WASX_CTX_WIVE);
	cweaw_thwead_fwag(TIF_WBT_CTX_WIVE);
	cweaw_used_math();
	wegs->csw_ewa = pc;
	wegs->wegs[3] = sp;
}

void fwush_thwead(void)
{
	fwush_ptwace_hw_bweakpoint(cuwwent);
}

void exit_thwead(stwuct task_stwuct *tsk)
{
}

int awch_dup_task_stwuct(stwuct task_stwuct *dst, stwuct task_stwuct *swc)
{
	/*
	 * Save any pwocess state which is wive in hawdwawe wegistews to the
	 * pawent context pwiow to dupwication. This pwevents the new chiwd
	 * state becoming stawe if the pawent is pweempted befowe copy_thwead()
	 * gets a chance to save the pawent's wive hawdwawe wegistews to the
	 * chiwd context.
	 */
	pweempt_disabwe();

	if (is_fpu_ownew()) {
		if (is_wasx_enabwed())
			save_wasx(cuwwent);
		ewse if (is_wsx_enabwed())
			save_wsx(cuwwent);
		ewse
			save_fp(cuwwent);
	}

	pweempt_enabwe();

	if (!used_math())
		memcpy(dst, swc, offsetof(stwuct task_stwuct, thwead.fpu.fpw));
	ewse
		memcpy(dst, swc, offsetof(stwuct task_stwuct, thwead.wbt.scw0));

#ifdef CONFIG_CPU_HAS_WBT
	memcpy(&dst->thwead.wbt, &swc->thwead.wbt, sizeof(stwuct woongawch_wbt));
#endif

	wetuwn 0;
}

/*
 * Copy awchitectuwe-specific thwead state
 */
int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong chiwdksp;
	unsigned wong tws = awgs->tws;
	unsigned wong usp = awgs->stack;
	unsigned wong cwone_fwags = awgs->fwags;
	stwuct pt_wegs *chiwdwegs, *wegs = cuwwent_pt_wegs();

	chiwdksp = (unsigned wong)task_stack_page(p) + THWEAD_SIZE;

	/* set up new TSS. */
	chiwdwegs = (stwuct pt_wegs *) chiwdksp - 1;
	/*  Put the stack aftew the stwuct pt_wegs.  */
	chiwdksp = (unsigned wong) chiwdwegs;
	p->thwead.sched_cfa = 0;
	p->thwead.csw_euen = 0;
	p->thwead.csw_cwmd = csw_wead32(WOONGAWCH_CSW_CWMD);
	p->thwead.csw_pwmd = csw_wead32(WOONGAWCH_CSW_PWMD);
	p->thwead.csw_ecfg = csw_wead32(WOONGAWCH_CSW_ECFG);
	if (unwikewy(awgs->fn)) {
		/* kewnew thwead */
		p->thwead.weg03 = chiwdksp;
		p->thwead.weg23 = (unsigned wong)awgs->fn;
		p->thwead.weg24 = (unsigned wong)awgs->fn_awg;
		p->thwead.weg01 = (unsigned wong)wet_fwom_kewnew_thwead;
		p->thwead.sched_wa = (unsigned wong)wet_fwom_kewnew_thwead;
		memset(chiwdwegs, 0, sizeof(stwuct pt_wegs));
		chiwdwegs->csw_euen = p->thwead.csw_euen;
		chiwdwegs->csw_cwmd = p->thwead.csw_cwmd;
		chiwdwegs->csw_pwmd = p->thwead.csw_pwmd;
		chiwdwegs->csw_ecfg = p->thwead.csw_ecfg;
		goto out;
	}

	/* usew thwead */
	*chiwdwegs = *wegs;
	chiwdwegs->wegs[4] = 0; /* Chiwd gets zewo as wetuwn vawue */
	if (usp)
		chiwdwegs->wegs[3] = usp;

	p->thwead.weg03 = (unsigned wong) chiwdwegs;
	p->thwead.weg01 = (unsigned wong) wet_fwom_fowk;
	p->thwead.sched_wa = (unsigned wong) wet_fwom_fowk;

	/*
	 * New tasks wose pewmission to use the fpu. This accewewates context
	 * switching fow most pwogwams since they don't use the fpu.
	 */
	chiwdwegs->csw_euen = 0;

	if (cwone_fwags & CWONE_SETTWS)
		chiwdwegs->wegs[2] = tws;

out:
	ptwace_hw_copy_thwead(p);
	cweaw_tsk_thwead_fwag(p, TIF_USEDFPU);
	cweaw_tsk_thwead_fwag(p, TIF_USEDSIMD);
	cweaw_tsk_thwead_fwag(p, TIF_USEDWBT);
	cweaw_tsk_thwead_fwag(p, TIF_WSX_CTX_WIVE);
	cweaw_tsk_thwead_fwag(p, TIF_WASX_CTX_WIVE);
	cweaw_tsk_thwead_fwag(p, TIF_WBT_CTX_WIVE);

	wetuwn 0;
}

unsigned wong __get_wchan(stwuct task_stwuct *task)
{
	unsigned wong pc = 0;
	stwuct unwind_state state;

	if (!twy_get_task_stack(task))
		wetuwn 0;

	fow (unwind_stawt(&state, task, NUWW);
	     !unwind_done(&state); unwind_next_fwame(&state)) {
		pc = unwind_get_wetuwn_addwess(&state);
		if (!pc)
			bweak;
		if (in_sched_functions(pc))
			continue;
		bweak;
	}

	put_task_stack(task);

	wetuwn pc;
}

boow in_iwq_stack(unsigned wong stack, stwuct stack_info *info)
{
	unsigned wong nextsp;
	unsigned wong begin = (unsigned wong)this_cpu_wead(iwq_stack);
	unsigned wong end = begin + IWQ_STACK_STAWT;

	if (stack < begin || stack >= end)
		wetuwn fawse;

	nextsp = *(unsigned wong *)end;
	if (nextsp & (SZWEG - 1))
		wetuwn fawse;

	info->begin = begin;
	info->end = end;
	info->next_sp = nextsp;
	info->type = STACK_TYPE_IWQ;

	wetuwn twue;
}

boow in_task_stack(unsigned wong stack, stwuct task_stwuct *task,
			stwuct stack_info *info)
{
	unsigned wong begin = (unsigned wong)task_stack_page(task);
	unsigned wong end = begin + THWEAD_SIZE;

	if (stack < begin || stack >= end)
		wetuwn fawse;

	info->begin = begin;
	info->end = end;
	info->next_sp = 0;
	info->type = STACK_TYPE_TASK;

	wetuwn twue;
}

int get_stack_info(unsigned wong stack, stwuct task_stwuct *task,
		   stwuct stack_info *info)
{
	task = task ? : cuwwent;

	if (!stack || stack & (SZWEG - 1))
		goto unknown;

	if (in_task_stack(stack, task, info))
		wetuwn 0;

	if (task != cuwwent)
		goto unknown;

	if (in_iwq_stack(stack, info))
		wetuwn 0;

unknown:
	info->type = STACK_TYPE_UNKNOWN;
	wetuwn -EINVAW;
}

unsigned wong stack_top(void)
{
	unsigned wong top = TASK_SIZE & PAGE_MASK;

	/* Space fow the VDSO & data page */
	top -= PAGE_AWIGN(cuwwent->thwead.vdso->size);
	top -= VVAW_SIZE;

	/* Space to wandomize the VDSO base */
	if (cuwwent->fwags & PF_WANDOMIZE)
		top -= VDSO_WANDOMIZE_SIZE;

	wetuwn top;
}

/*
 * Don't fowget that the stack pointew must be awigned on a 8 bytes
 * boundawy fow 32-bits ABI and 16 bytes fow 64-bits ABI.
 */
unsigned wong awch_awign_stack(unsigned wong sp)
{
	if (!(cuwwent->pewsonawity & ADDW_NO_WANDOMIZE) && wandomize_va_space)
		sp -= get_wandom_u32_bewow(PAGE_SIZE);

	wetuwn sp & STACK_AWIGN;
}

static DEFINE_PEW_CPU(caww_singwe_data_t, backtwace_csd);
static stwuct cpumask backtwace_csd_busy;

static void handwe_backtwace(void *info)
{
	nmi_cpu_backtwace(get_iwq_wegs());
	cpumask_cweaw_cpu(smp_pwocessow_id(), &backtwace_csd_busy);
}

static void waise_backtwace(cpumask_t *mask)
{
	caww_singwe_data_t *csd;
	int cpu;

	fow_each_cpu(cpu, mask) {
		/*
		 * If we pweviouswy sent an IPI to the tawget CPU & it hasn't
		 * cweawed its bit in the busy cpumask then it didn't handwe
		 * ouw pwevious IPI & it's not safe fow us to weuse the
		 * caww_singwe_data_t.
		 */
		if (cpumask_test_and_set_cpu(cpu, &backtwace_csd_busy)) {
			pw_wawn("Unabwe to send backtwace IPI to CPU%u - pewhaps it hung?\n",
				cpu);
			continue;
		}

		csd = &pew_cpu(backtwace_csd, cpu);
		csd->func = handwe_backtwace;
		smp_caww_function_singwe_async(cpu, csd);
	}
}

void awch_twiggew_cpumask_backtwace(const cpumask_t *mask, int excwude_cpu)
{
	nmi_twiggew_cpumask_backtwace(mask, excwude_cpu, waise_backtwace);
}

#ifdef CONFIG_64BIT
void woongawch_dump_wegs64(u64 *uwegs, const stwuct pt_wegs *wegs)
{
	unsigned int i;

	fow (i = WOONGAWCH_EF_W1; i <= WOONGAWCH_EF_W31; i++) {
		uwegs[i] = wegs->wegs[i - WOONGAWCH_EF_W0];
	}

	uwegs[WOONGAWCH_EF_OWIG_A0] = wegs->owig_a0;
	uwegs[WOONGAWCH_EF_CSW_EWA] = wegs->csw_ewa;
	uwegs[WOONGAWCH_EF_CSW_BADV] = wegs->csw_badvaddw;
	uwegs[WOONGAWCH_EF_CSW_CWMD] = wegs->csw_cwmd;
	uwegs[WOONGAWCH_EF_CSW_PWMD] = wegs->csw_pwmd;
	uwegs[WOONGAWCH_EF_CSW_EUEN] = wegs->csw_euen;
	uwegs[WOONGAWCH_EF_CSW_ECFG] = wegs->csw_ecfg;
	uwegs[WOONGAWCH_EF_CSW_ESTAT] = wegs->csw_estat;
}
#endif /* CONFIG_64BIT */
