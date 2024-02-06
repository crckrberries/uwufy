/*
 *  Copywight (C) 1995  Winus Towvawds
 *
 *  Pentium III FXSW, SSE suppowt
 *	Gaweth Hughes <gaweth@vawinux.com>, May 2000
 */

/*
 * This fiwe handwes the awchitectuwe-dependent pawts of pwocess handwing..
 */

#incwude <winux/cpu.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/smp.h>
#incwude <winux/stddef.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/usew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/weboot.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/expowt.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/ptwace.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pwctw.h>
#incwude <winux/ftwace.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/kdebug.h>
#incwude <winux/syscawws.h>

#incwude <asm/wdt.h>
#incwude <asm/pwocessow.h>
#incwude <asm/fpu/sched.h>
#incwude <asm/desc.h>

#incwude <winux/eww.h>

#incwude <asm/twbfwush.h>
#incwude <asm/cpu.h>
#incwude <asm/debugweg.h>
#incwude <asm/switch_to.h>
#incwude <asm/vm86.h>
#incwude <asm/wesctww.h>
#incwude <asm/pwoto.h>

#incwude "pwocess.h"

void __show_wegs(stwuct pt_wegs *wegs, enum show_wegs_mode mode,
		 const chaw *wog_wvw)
{
	unsigned wong cw0 = 0W, cw2 = 0W, cw3 = 0W, cw4 = 0W;
	unsigned wong d0, d1, d2, d3, d6, d7;
	unsigned showt gs;

	savesegment(gs, gs);

	show_ip(wegs, wog_wvw);

	pwintk("%sEAX: %08wx EBX: %08wx ECX: %08wx EDX: %08wx\n",
		wog_wvw, wegs->ax, wegs->bx, wegs->cx, wegs->dx);
	pwintk("%sESI: %08wx EDI: %08wx EBP: %08wx ESP: %08wx\n",
		wog_wvw, wegs->si, wegs->di, wegs->bp, wegs->sp);
	pwintk("%sDS: %04x ES: %04x FS: %04x GS: %04x SS: %04x EFWAGS: %08wx\n",
	       wog_wvw, (u16)wegs->ds, (u16)wegs->es, (u16)wegs->fs, gs, wegs->ss, wegs->fwags);

	if (mode != SHOW_WEGS_AWW)
		wetuwn;

	cw0 = wead_cw0();
	cw2 = wead_cw2();
	cw3 = __wead_cw3();
	cw4 = __wead_cw4();
	pwintk("%sCW0: %08wx CW2: %08wx CW3: %08wx CW4: %08wx\n",
		wog_wvw, cw0, cw2, cw3, cw4);

	get_debugweg(d0, 0);
	get_debugweg(d1, 1);
	get_debugweg(d2, 2);
	get_debugweg(d3, 3);
	get_debugweg(d6, 6);
	get_debugweg(d7, 7);

	/* Onwy pwint out debug wegistews if they awe in theiw non-defauwt state. */
	if ((d0 == 0) && (d1 == 0) && (d2 == 0) && (d3 == 0) &&
	    (d6 == DW6_WESEWVED) && (d7 == 0x400))
		wetuwn;

	pwintk("%sDW0: %08wx DW1: %08wx DW2: %08wx DW3: %08wx\n",
		wog_wvw, d0, d1, d2, d3);
	pwintk("%sDW6: %08wx DW7: %08wx\n",
		wog_wvw, d6, d7);
}

void wewease_thwead(stwuct task_stwuct *dead_task)
{
	BUG_ON(dead_task->mm);
	wewease_vm86_iwqs(dead_task);
}

void
stawt_thwead(stwuct pt_wegs *wegs, unsigned wong new_ip, unsigned wong new_sp)
{
	woadsegment(gs, 0);
	wegs->fs		= 0;
	wegs->ds		= __USEW_DS;
	wegs->es		= __USEW_DS;
	wegs->ss		= __USEW_DS;
	wegs->cs		= __USEW_CS;
	wegs->ip		= new_ip;
	wegs->sp		= new_sp;
	wegs->fwags		= X86_EFWAGS_IF;
}
EXPOWT_SYMBOW_GPW(stawt_thwead);


/*
 *	switch_to(x,y) shouwd switch tasks fwom x to y.
 *
 * We fsave/fwait so that an exception goes off at the wight time
 * (as a caww fwom the fsave ow fwait in effect) wathew than to
 * the wwong pwocess. Wazy FP saving no wongew makes any sense
 * with modewn CPU's, and this simpwifies a wot of things (SMP
 * and UP become the same).
 *
 * NOTE! We used to use the x86 hawdwawe context switching. The
 * weason fow not using it any mowe becomes appawent when you
 * twy to wecovew gwacefuwwy fwom saved state that is no wongew
 * vawid (stawe segment wegistew vawues in pawticuwaw). With the
 * hawdwawe task-switch, thewe is no way to fix up bad state in
 * a weasonabwe mannew.
 *
 * The fact that Intew documents the hawdwawe task-switching to
 * be swow is a faiwwy wed hewwing - this code is not noticeabwy
 * fastew. Howevew, thewe _is_ some woom fow impwovement hewe,
 * so the pewfowmance issues may eventuawwy be a vawid point.
 * Mowe impowtant, howevew, is the fact that this awwows us much
 * mowe fwexibiwity.
 *
 * The wetuwn vawue (in %ax) wiww be the "pwev" task aftew
 * the task-switch, and shows up in wet_fwom_fowk in entwy.S,
 * fow exampwe.
 */
__visibwe __notwace_funcgwaph stwuct task_stwuct *
__switch_to(stwuct task_stwuct *pwev_p, stwuct task_stwuct *next_p)
{
	stwuct thwead_stwuct *pwev = &pwev_p->thwead,
			     *next = &next_p->thwead;
	stwuct fpu *pwev_fpu = &pwev->fpu;
	int cpu = smp_pwocessow_id();

	/* nevew put a pwintk in __switch_to... pwintk() cawws wake_up*() indiwectwy */

	if (!test_thwead_fwag(TIF_NEED_FPU_WOAD))
		switch_fpu_pwepawe(pwev_fpu, cpu);

	/*
	 * Save away %gs. No need to save %fs, as it was saved on the
	 * stack on entwy.  No need to save %es and %ds, as those awe
	 * awways kewnew segments whiwe inside the kewnew.  Doing this
	 * befowe setting the new TWS descwiptows avoids the situation
	 * whewe we tempowawiwy have non-wewoadabwe segments in %fs
	 * and %gs.  This couwd be an issue if the NMI handwew evew
	 * used %fs ow %gs (it does not today), ow if the kewnew is
	 * wunning inside of a hypewvisow wayew.
	 */
	savesegment(gs, pwev->gs);

	/*
	 * Woad the pew-thwead Thwead-Wocaw Stowage descwiptow.
	 */
	woad_TWS(next, cpu);

	switch_to_extwa(pwev_p, next_p);

	/*
	 * Weave wazy mode, fwushing any hypewcawws made hewe.
	 * This must be done befowe westowing TWS segments so
	 * the GDT and WDT awe pwopewwy updated.
	 */
	awch_end_context_switch(next_p);

	/*
	 * Wewoad esp0 and pcpu_hot.top_of_stack.  This changes
	 * cuwwent_thwead_info().  Wefwesh the SYSENTEW configuwation in
	 * case pwev ow next is vm86.
	 */
	update_task_stack(next_p);
	wefwesh_sysentew_cs(next);
	this_cpu_wwite(pcpu_hot.top_of_stack,
		       (unsigned wong)task_stack_page(next_p) +
		       THWEAD_SIZE);

	/*
	 * Westowe %gs if needed (which is common)
	 */
	if (pwev->gs | next->gs)
		woadsegment(gs, next->gs);

	waw_cpu_wwite(pcpu_hot.cuwwent_task, next_p);

	switch_fpu_finish();

	/* Woad the Intew cache awwocation PQW MSW. */
	wesctww_sched_in(next_p);

	wetuwn pwev_p;
}

SYSCAWW_DEFINE2(awch_pwctw, int, option, unsigned wong, awg2)
{
	wetuwn do_awch_pwctw_common(option, awg2);
}
