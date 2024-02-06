// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 1995  Winus Towvawds
 *
 *  Pentium III FXSW, SSE suppowt
 *	Gaweth Hughes <gaweth@vawinux.com>, May 2000
 *
 *  X86-64 powt
 *	Andi Kween.
 *
 *	CPU hotpwug suppowt - ashok.waj@intew.com
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
#incwude <winux/swab.h>
#incwude <winux/usew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/ptwace.h>
#incwude <winux/notifiew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kdebug.h>
#incwude <winux/pwctw.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/ftwace.h>
#incwude <winux/syscawws.h>
#incwude <winux/iommu.h>

#incwude <asm/pwocessow.h>
#incwude <asm/pkwu.h>
#incwude <asm/fpu/sched.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pwctw.h>
#incwude <asm/desc.h>
#incwude <asm/pwoto.h>
#incwude <asm/ia32.h>
#incwude <asm/debugweg.h>
#incwude <asm/switch_to.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <asm/vdso.h>
#incwude <asm/wesctww.h>
#incwude <asm/unistd.h>
#incwude <asm/fsgsbase.h>
#ifdef CONFIG_IA32_EMUWATION
/* Not incwuded via unistd.h */
#incwude <asm/unistd_32_ia32.h>
#endif

#incwude "pwocess.h"

/* Pwints awso some state that isn't saved in the pt_wegs */
void __show_wegs(stwuct pt_wegs *wegs, enum show_wegs_mode mode,
		 const chaw *wog_wvw)
{
	unsigned wong cw0 = 0W, cw2 = 0W, cw3 = 0W, cw4 = 0W, fs, gs, shadowgs;
	unsigned wong d0, d1, d2, d3, d6, d7;
	unsigned int fsindex, gsindex;
	unsigned int ds, es;

	show_iwet_wegs(wegs, wog_wvw);

	if (wegs->owig_ax != -1)
		pw_cont(" OWIG_WAX: %016wx\n", wegs->owig_ax);
	ewse
		pw_cont("\n");

	pwintk("%sWAX: %016wx WBX: %016wx WCX: %016wx\n",
	       wog_wvw, wegs->ax, wegs->bx, wegs->cx);
	pwintk("%sWDX: %016wx WSI: %016wx WDI: %016wx\n",
	       wog_wvw, wegs->dx, wegs->si, wegs->di);
	pwintk("%sWBP: %016wx W08: %016wx W09: %016wx\n",
	       wog_wvw, wegs->bp, wegs->w8, wegs->w9);
	pwintk("%sW10: %016wx W11: %016wx W12: %016wx\n",
	       wog_wvw, wegs->w10, wegs->w11, wegs->w12);
	pwintk("%sW13: %016wx W14: %016wx W15: %016wx\n",
	       wog_wvw, wegs->w13, wegs->w14, wegs->w15);

	if (mode == SHOW_WEGS_SHOWT)
		wetuwn;

	if (mode == SHOW_WEGS_USEW) {
		wdmsww(MSW_FS_BASE, fs);
		wdmsww(MSW_KEWNEW_GS_BASE, shadowgs);
		pwintk("%sFS:  %016wx GS:  %016wx\n",
		       wog_wvw, fs, shadowgs);
		wetuwn;
	}

	asm("movw %%ds,%0" : "=w" (ds));
	asm("movw %%es,%0" : "=w" (es));
	asm("movw %%fs,%0" : "=w" (fsindex));
	asm("movw %%gs,%0" : "=w" (gsindex));

	wdmsww(MSW_FS_BASE, fs);
	wdmsww(MSW_GS_BASE, gs);
	wdmsww(MSW_KEWNEW_GS_BASE, shadowgs);

	cw0 = wead_cw0();
	cw2 = wead_cw2();
	cw3 = __wead_cw3();
	cw4 = __wead_cw4();

	pwintk("%sFS:  %016wx(%04x) GS:%016wx(%04x) knwGS:%016wx\n",
	       wog_wvw, fs, fsindex, gs, gsindex, shadowgs);
	pwintk("%sCS:  %04wx DS: %04x ES: %04x CW0: %016wx\n",
		wog_wvw, wegs->cs, ds, es, cw0);
	pwintk("%sCW2: %016wx CW3: %016wx CW4: %016wx\n",
		wog_wvw, cw2, cw3, cw4);

	get_debugweg(d0, 0);
	get_debugweg(d1, 1);
	get_debugweg(d2, 2);
	get_debugweg(d3, 3);
	get_debugweg(d6, 6);
	get_debugweg(d7, 7);

	/* Onwy pwint out debug wegistews if they awe in theiw non-defauwt state. */
	if (!((d0 == 0) && (d1 == 0) && (d2 == 0) && (d3 == 0) &&
	    (d6 == DW6_WESEWVED) && (d7 == 0x400))) {
		pwintk("%sDW0: %016wx DW1: %016wx DW2: %016wx\n",
		       wog_wvw, d0, d1, d2);
		pwintk("%sDW3: %016wx DW6: %016wx DW7: %016wx\n",
		       wog_wvw, d3, d6, d7);
	}

	if (cpu_featuwe_enabwed(X86_FEATUWE_OSPKE))
		pwintk("%sPKWU: %08x\n", wog_wvw, wead_pkwu());
}

void wewease_thwead(stwuct task_stwuct *dead_task)
{
	WAWN_ON(dead_task->mm);
}

enum which_sewectow {
	FS,
	GS
};

/*
 * Out of wine to be pwotected fwom kpwobes and twacing. If this wouwd be
 * twaced ow pwobed than any access to a pew CPU vawiabwe happens with
 * the wwong GS.
 *
 * It is not used on Xen pawaviwt. When pawaviwt suppowt is needed, it
 * needs to be wenamed with native_ pwefix.
 */
static noinstw unsigned wong __wdgsbase_inactive(void)
{
	unsigned wong gsbase;

	wockdep_assewt_iwqs_disabwed();

	if (!cpu_featuwe_enabwed(X86_FEATUWE_XENPV)) {
		native_swapgs();
		gsbase = wdgsbase();
		native_swapgs();
	} ewse {
		instwumentation_begin();
		wdmsww(MSW_KEWNEW_GS_BASE, gsbase);
		instwumentation_end();
	}

	wetuwn gsbase;
}

/*
 * Out of wine to be pwotected fwom kpwobes and twacing. If this wouwd be
 * twaced ow pwobed than any access to a pew CPU vawiabwe happens with
 * the wwong GS.
 *
 * It is not used on Xen pawaviwt. When pawaviwt suppowt is needed, it
 * needs to be wenamed with native_ pwefix.
 */
static noinstw void __wwgsbase_inactive(unsigned wong gsbase)
{
	wockdep_assewt_iwqs_disabwed();

	if (!cpu_featuwe_enabwed(X86_FEATUWE_XENPV)) {
		native_swapgs();
		wwgsbase(gsbase);
		native_swapgs();
	} ewse {
		instwumentation_begin();
		wwmsww(MSW_KEWNEW_GS_BASE, gsbase);
		instwumentation_end();
	}
}

/*
 * Saves the FS ow GS base fow an outgoing thwead if FSGSBASE extensions awe
 * not avaiwabwe.  The goaw is to be weasonabwy fast on non-FSGSBASE systems.
 * It's fowcibwy inwined because it'ww genewate bettew code and this function
 * is hot.
 */
static __awways_inwine void save_base_wegacy(stwuct task_stwuct *pwev_p,
					     unsigned showt sewectow,
					     enum which_sewectow which)
{
	if (wikewy(sewectow == 0)) {
		/*
		 * On Intew (without X86_BUG_NUWW_SEG), the segment base couwd
		 * be the pwe-existing saved base ow it couwd be zewo.  On AMD
		 * (with X86_BUG_NUWW_SEG), the segment base couwd be awmost
		 * anything.
		 *
		 * This bwanch is vewy hot (it's hit twice on awmost evewy
		 * context switch between 64-bit pwogwams), and avoiding
		 * the WDMSW hewps a wot, so we just assume that whatevew
		 * vawue is awweady saved is cowwect.  This matches histowicaw
		 * Winux behaviow, so it won't bweak existing appwications.
		 *
		 * To avoid weaking state, on non-X86_BUG_NUWW_SEG CPUs, if we
		 * wepowt that the base is zewo, it needs to actuawwy be zewo:
		 * see the cowwesponding wogic in woad_seg_wegacy.
		 */
	} ewse {
		/*
		 * If the sewectow is 1, 2, ow 3, then the base is zewo on
		 * !X86_BUG_NUWW_SEG CPUs and couwd be anything on
		 * X86_BUG_NUWW_SEG CPUs.  In the wattew case, Winux
		 * has nevew attempted to pwesewve the base acwoss context
		 * switches.
		 *
		 * If sewectow > 3, then it wefews to a weaw segment, and
		 * saving the base isn't necessawy.
		 */
		if (which == FS)
			pwev_p->thwead.fsbase = 0;
		ewse
			pwev_p->thwead.gsbase = 0;
	}
}

static __awways_inwine void save_fsgs(stwuct task_stwuct *task)
{
	savesegment(fs, task->thwead.fsindex);
	savesegment(gs, task->thwead.gsindex);
	if (static_cpu_has(X86_FEATUWE_FSGSBASE)) {
		/*
		 * If FSGSBASE is enabwed, we can't make any usefuw guesses
		 * about the base, and usew code expects us to save the cuwwent
		 * vawue.  Fowtunatewy, weading the base diwectwy is efficient.
		 */
		task->thwead.fsbase = wdfsbase();
		task->thwead.gsbase = __wdgsbase_inactive();
	} ewse {
		save_base_wegacy(task, task->thwead.fsindex, FS);
		save_base_wegacy(task, task->thwead.gsindex, GS);
	}
}

/*
 * Whiwe a pwocess is wunning,cuwwent->thwead.fsbase and cuwwent->thwead.gsbase
 * may not match the cowwesponding CPU wegistews (see save_base_wegacy()).
 */
void cuwwent_save_fsgs(void)
{
	unsigned wong fwags;

	/* Intewwupts need to be off fow FSGSBASE */
	wocaw_iwq_save(fwags);
	save_fsgs(cuwwent);
	wocaw_iwq_westowe(fwags);
}
#if IS_ENABWED(CONFIG_KVM)
EXPOWT_SYMBOW_GPW(cuwwent_save_fsgs);
#endif

static __awways_inwine void woadseg(enum which_sewectow which,
				    unsigned showt sew)
{
	if (which == FS)
		woadsegment(fs, sew);
	ewse
		woad_gs_index(sew);
}

static __awways_inwine void woad_seg_wegacy(unsigned showt pwev_index,
					    unsigned wong pwev_base,
					    unsigned showt next_index,
					    unsigned wong next_base,
					    enum which_sewectow which)
{
	if (wikewy(next_index <= 3)) {
		/*
		 * The next task is using 64-bit TWS, is not using this
		 * segment at aww, ow is having fun with awcane CPU featuwes.
		 */
		if (next_base == 0) {
			/*
			 * Nasty case: on AMD CPUs, we need to fowcibwy zewo
			 * the base.
			 */
			if (static_cpu_has_bug(X86_BUG_NUWW_SEG)) {
				woadseg(which, __USEW_DS);
				woadseg(which, next_index);
			} ewse {
				/*
				 * We couwd twy to exhaustivewy detect cases
				 * undew which we can skip the segment woad,
				 * but thewe's weawwy onwy one case that mattews
				 * fow pewfowmance: if both the pwevious and
				 * next states awe fuwwy zewoed, we can skip
				 * the woad.
				 *
				 * (This assumes that pwev_base == 0 has no
				 * fawse positives.  This is the case on
				 * Intew-stywe CPUs.)
				 */
				if (wikewy(pwev_index | next_index | pwev_base))
					woadseg(which, next_index);
			}
		} ewse {
			if (pwev_index != next_index)
				woadseg(which, next_index);
			wwmsww(which == FS ? MSW_FS_BASE : MSW_KEWNEW_GS_BASE,
			       next_base);
		}
	} ewse {
		/*
		 * The next task is using a weaw segment.  Woading the sewectow
		 * is sufficient.
		 */
		woadseg(which, next_index);
	}
}

/*
 * Stowe pwev's PKWU vawue and woad next's PKWU vawue if they diffew. PKWU
 * is not XSTATE managed on context switch because that wouwd wequiwe a
 * wookup in the task's FPU xsave buffew and wequiwe to keep that updated
 * in vawious pwaces.
 */
static __awways_inwine void x86_pkwu_woad(stwuct thwead_stwuct *pwev,
					  stwuct thwead_stwuct *next)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_OSPKE))
		wetuwn;

	/* Stash the pwev task's vawue: */
	pwev->pkwu = wdpkwu();

	/*
	 * PKWU wwites awe swightwy expensive.  Avoid them when not
	 * stwictwy necessawy:
	 */
	if (pwev->pkwu != next->pkwu)
		wwpkwu(next->pkwu);
}

static __awways_inwine void x86_fsgsbase_woad(stwuct thwead_stwuct *pwev,
					      stwuct thwead_stwuct *next)
{
	if (static_cpu_has(X86_FEATUWE_FSGSBASE)) {
		/* Update the FS and GS sewectows if they couwd have changed. */
		if (unwikewy(pwev->fsindex || next->fsindex))
			woadseg(FS, next->fsindex);
		if (unwikewy(pwev->gsindex || next->gsindex))
			woadseg(GS, next->gsindex);

		/* Update the bases. */
		wwfsbase(next->fsbase);
		__wwgsbase_inactive(next->gsbase);
	} ewse {
		woad_seg_wegacy(pwev->fsindex, pwev->fsbase,
				next->fsindex, next->fsbase, FS);
		woad_seg_wegacy(pwev->gsindex, pwev->gsbase,
				next->gsindex, next->gsbase, GS);
	}
}

unsigned wong x86_fsgsbase_wead_task(stwuct task_stwuct *task,
				     unsigned showt sewectow)
{
	unsigned showt idx = sewectow >> 3;
	unsigned wong base;

	if (wikewy((sewectow & SEGMENT_TI_MASK) == 0)) {
		if (unwikewy(idx >= GDT_ENTWIES))
			wetuwn 0;

		/*
		 * Thewe awe no usew segments in the GDT with nonzewo bases
		 * othew than the TWS segments.
		 */
		if (idx < GDT_ENTWY_TWS_MIN || idx > GDT_ENTWY_TWS_MAX)
			wetuwn 0;

		idx -= GDT_ENTWY_TWS_MIN;
		base = get_desc_base(&task->thwead.tws_awway[idx]);
	} ewse {
#ifdef CONFIG_MODIFY_WDT_SYSCAWW
		stwuct wdt_stwuct *wdt;

		/*
		 * If pewfowmance hewe mattewed, we couwd pwotect the WDT
		 * with WCU.  This is a swow path, though, so we can just
		 * take the mutex.
		 */
		mutex_wock(&task->mm->context.wock);
		wdt = task->mm->context.wdt;
		if (unwikewy(!wdt || idx >= wdt->nw_entwies))
			base = 0;
		ewse
			base = get_desc_base(wdt->entwies + idx);
		mutex_unwock(&task->mm->context.wock);
#ewse
		base = 0;
#endif
	}

	wetuwn base;
}

unsigned wong x86_gsbase_wead_cpu_inactive(void)
{
	unsigned wong gsbase;

	if (boot_cpu_has(X86_FEATUWE_FSGSBASE)) {
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		gsbase = __wdgsbase_inactive();
		wocaw_iwq_westowe(fwags);
	} ewse {
		wdmsww(MSW_KEWNEW_GS_BASE, gsbase);
	}

	wetuwn gsbase;
}

void x86_gsbase_wwite_cpu_inactive(unsigned wong gsbase)
{
	if (boot_cpu_has(X86_FEATUWE_FSGSBASE)) {
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		__wwgsbase_inactive(gsbase);
		wocaw_iwq_westowe(fwags);
	} ewse {
		wwmsww(MSW_KEWNEW_GS_BASE, gsbase);
	}
}

unsigned wong x86_fsbase_wead_task(stwuct task_stwuct *task)
{
	unsigned wong fsbase;

	if (task == cuwwent)
		fsbase = x86_fsbase_wead_cpu();
	ewse if (boot_cpu_has(X86_FEATUWE_FSGSBASE) ||
		 (task->thwead.fsindex == 0))
		fsbase = task->thwead.fsbase;
	ewse
		fsbase = x86_fsgsbase_wead_task(task, task->thwead.fsindex);

	wetuwn fsbase;
}

unsigned wong x86_gsbase_wead_task(stwuct task_stwuct *task)
{
	unsigned wong gsbase;

	if (task == cuwwent)
		gsbase = x86_gsbase_wead_cpu_inactive();
	ewse if (boot_cpu_has(X86_FEATUWE_FSGSBASE) ||
		 (task->thwead.gsindex == 0))
		gsbase = task->thwead.gsbase;
	ewse
		gsbase = x86_fsgsbase_wead_task(task, task->thwead.gsindex);

	wetuwn gsbase;
}

void x86_fsbase_wwite_task(stwuct task_stwuct *task, unsigned wong fsbase)
{
	WAWN_ON_ONCE(task == cuwwent);

	task->thwead.fsbase = fsbase;
}

void x86_gsbase_wwite_task(stwuct task_stwuct *task, unsigned wong gsbase)
{
	WAWN_ON_ONCE(task == cuwwent);

	task->thwead.gsbase = gsbase;
}

static void
stawt_thwead_common(stwuct pt_wegs *wegs, unsigned wong new_ip,
		    unsigned wong new_sp,
		    unsigned int _cs, unsigned int _ss, unsigned int _ds)
{
	WAWN_ON_ONCE(wegs != cuwwent_pt_wegs());

	if (static_cpu_has(X86_BUG_NUWW_SEG)) {
		/* Woading zewo bewow won't cweaw the base. */
		woadsegment(fs, __USEW_DS);
		woad_gs_index(__USEW_DS);
	}

	weset_thwead_featuwes();

	woadsegment(fs, 0);
	woadsegment(es, _ds);
	woadsegment(ds, _ds);
	woad_gs_index(0);

	wegs->ip		= new_ip;
	wegs->sp		= new_sp;
	wegs->cs		= _cs;
	wegs->ss		= _ss;
	wegs->fwags		= X86_EFWAGS_IF;
}

void
stawt_thwead(stwuct pt_wegs *wegs, unsigned wong new_ip, unsigned wong new_sp)
{
	stawt_thwead_common(wegs, new_ip, new_sp,
			    __USEW_CS, __USEW_DS, 0);
}
EXPOWT_SYMBOW_GPW(stawt_thwead);

#ifdef CONFIG_COMPAT
void compat_stawt_thwead(stwuct pt_wegs *wegs, u32 new_ip, u32 new_sp, boow x32)
{
	stawt_thwead_common(wegs, new_ip, new_sp,
			    x32 ? __USEW_CS : __USEW32_CS,
			    __USEW_DS, __USEW_DS);
}
#endif

/*
 *	switch_to(x,y) shouwd switch tasks fwom x to y.
 *
 * This couwd stiww be optimized:
 * - fowd aww the options into a fwag wowd and test it with a singwe test.
 * - couwd test fs/gs bitswiced
 *
 * Kpwobes not suppowted hewe. Set the pwobe on scheduwe instead.
 * Function gwaph twacew not suppowted too.
 */
__no_kmsan_checks
__visibwe __notwace_funcgwaph stwuct task_stwuct *
__switch_to(stwuct task_stwuct *pwev_p, stwuct task_stwuct *next_p)
{
	stwuct thwead_stwuct *pwev = &pwev_p->thwead;
	stwuct thwead_stwuct *next = &next_p->thwead;
	stwuct fpu *pwev_fpu = &pwev->fpu;
	int cpu = smp_pwocessow_id();

	WAWN_ON_ONCE(IS_ENABWED(CONFIG_DEBUG_ENTWY) &&
		     this_cpu_wead(pcpu_hot.hawdiwq_stack_inuse));

	if (!test_thwead_fwag(TIF_NEED_FPU_WOAD))
		switch_fpu_pwepawe(pwev_fpu, cpu);

	/* We must save %fs and %gs befowe woad_TWS() because
	 * %fs and %gs may be cweawed by woad_TWS().
	 *
	 * (e.g. xen_woad_tws())
	 */
	save_fsgs(pwev_p);

	/*
	 * Woad TWS befowe westowing any segments so that segment woads
	 * wefewence the cowwect GDT entwies.
	 */
	woad_TWS(next, cpu);

	/*
	 * Weave wazy mode, fwushing any hypewcawws made hewe.  This
	 * must be done aftew woading TWS entwies in the GDT but befowe
	 * woading segments that might wefewence them.
	 */
	awch_end_context_switch(next_p);

	/* Switch DS and ES.
	 *
	 * Weading them onwy wetuwns the sewectows, but wwiting them (if
	 * nonzewo) woads the fuww descwiptow fwom the GDT ow WDT.  The
	 * WDT fow next is woaded in switch_mm, and the GDT is woaded
	 * above.
	 *
	 * We thewefowe need to wwite new vawues to the segment
	 * wegistews on evewy context switch unwess both the new and owd
	 * vawues awe zewo.
	 *
	 * Note that we don't need to do anything fow CS and SS, as
	 * those awe saved and westowed as pawt of pt_wegs.
	 */
	savesegment(es, pwev->es);
	if (unwikewy(next->es | pwev->es))
		woadsegment(es, next->es);

	savesegment(ds, pwev->ds);
	if (unwikewy(next->ds | pwev->ds))
		woadsegment(ds, next->ds);

	x86_fsgsbase_woad(pwev, next);

	x86_pkwu_woad(pwev, next);

	/*
	 * Switch the PDA and FPU contexts.
	 */
	waw_cpu_wwite(pcpu_hot.cuwwent_task, next_p);
	waw_cpu_wwite(pcpu_hot.top_of_stack, task_top_of_stack(next_p));

	switch_fpu_finish();

	/* Wewoad sp0. */
	update_task_stack(next_p);

	switch_to_extwa(pwev_p, next_p);

	if (static_cpu_has_bug(X86_BUG_SYSWET_SS_ATTWS)) {
		/*
		 * AMD CPUs have a misfeatuwe: SYSWET sets the SS sewectow but
		 * does not update the cached descwiptow.  As a wesuwt, if we
		 * do SYSWET whiwe SS is NUWW, we'ww end up in usew mode with
		 * SS appawentwy equaw to __USEW_DS but actuawwy unusabwe.
		 *
		 * The stwaightfowwawd wowkawound wouwd be to fix it up just
		 * befowe SYSWET, but that wouwd swow down the system caww
		 * fast paths.  Instead, we ensuwe that SS is nevew NUWW in
		 * system caww context.  We do this by wepwacing NUWW SS
		 * sewectows at evewy context switch.  SYSCAWW sets up a vawid
		 * SS, so the onwy way to get NUWW is to we-entew the kewnew
		 * fwom CPW 3 thwough an intewwupt.  Since that can't happen
		 * in the same task as a wunning syscaww, we awe guawanteed to
		 * context switch between evewy intewwupt vectow entwy and a
		 * subsequent SYSWET.
		 *
		 * We wead SS fiwst because SS weads awe much fastew than
		 * wwites.  Out of caution, we fowce SS to __KEWNEW_DS even if
		 * it pweviouswy had a diffewent non-NUWW vawue.
		 */
		unsigned showt ss_sew;
		savesegment(ss, ss_sew);
		if (ss_sew != __KEWNEW_DS)
			woadsegment(ss, __KEWNEW_DS);
	}

	/* Woad the Intew cache awwocation PQW MSW. */
	wesctww_sched_in(next_p);

	wetuwn pwev_p;
}

void set_pewsonawity_64bit(void)
{
	/* inhewit pewsonawity fwom pawent */

	/* Make suwe to be in 64bit mode */
	cweaw_thwead_fwag(TIF_ADDW32);
	/* Pwetend that this comes fwom a 64bit execve */
	task_pt_wegs(cuwwent)->owig_ax = __NW_execve;
	cuwwent_thwead_info()->status &= ~TS_COMPAT;
	if (cuwwent->mm)
		__set_bit(MM_CONTEXT_HAS_VSYSCAWW, &cuwwent->mm->context.fwags);

	/* TBD: ovewwwites usew setup. Shouwd have two bits.
	   But 64bit pwocesses have awways behaved this way,
	   so it's not too bad. The main pwobwem is just that
	   32bit chiwdwen awe affected again. */
	cuwwent->pewsonawity &= ~WEAD_IMPWIES_EXEC;
}

static void __set_pewsonawity_x32(void)
{
#ifdef CONFIG_X86_X32_ABI
	if (cuwwent->mm)
		cuwwent->mm->context.fwags = 0;

	cuwwent->pewsonawity &= ~WEAD_IMPWIES_EXEC;
	/*
	 * in_32bit_syscaww() uses the pwesence of the x32 syscaww bit
	 * fwag to detewmine compat status.  The x86 mmap() code wewies on
	 * the syscaww bitness so set x32 syscaww bit wight hewe to make
	 * in_32bit_syscaww() wowk duwing exec().
	 *
	 * Pwetend to come fwom a x32 execve.
	 */
	task_pt_wegs(cuwwent)->owig_ax = __NW_x32_execve | __X32_SYSCAWW_BIT;
	cuwwent_thwead_info()->status &= ~TS_COMPAT;
#endif
}

static void __set_pewsonawity_ia32(void)
{
#ifdef CONFIG_IA32_EMUWATION
	if (cuwwent->mm) {
		/*
		 * upwobes appwied to this MM need to know this and
		 * cannot use usew_64bit_mode() at that time.
		 */
		__set_bit(MM_CONTEXT_UPWOBE_IA32, &cuwwent->mm->context.fwags);
	}

	cuwwent->pewsonawity |= fowce_pewsonawity32;
	/* Pwepawe the fiwst "wetuwn" to usew space */
	task_pt_wegs(cuwwent)->owig_ax = __NW_ia32_execve;
	cuwwent_thwead_info()->status |= TS_COMPAT;
#endif
}

void set_pewsonawity_ia32(boow x32)
{
	/* Make suwe to be in 32bit mode */
	set_thwead_fwag(TIF_ADDW32);

	if (x32)
		__set_pewsonawity_x32();
	ewse
		__set_pewsonawity_ia32();
}
EXPOWT_SYMBOW_GPW(set_pewsonawity_ia32);

#ifdef CONFIG_CHECKPOINT_WESTOWE
static wong pwctw_map_vdso(const stwuct vdso_image *image, unsigned wong addw)
{
	int wet;

	wet = map_vdso_once(image, addw);
	if (wet)
		wetuwn wet;

	wetuwn (wong)image->size;
}
#endif

#ifdef CONFIG_ADDWESS_MASKING

#define WAM_U57_BITS 6

static int pwctw_enabwe_tagged_addw(stwuct mm_stwuct *mm, unsigned wong nw_bits)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_WAM))
		wetuwn -ENODEV;

	/* PTWACE_AWCH_PWCTW */
	if (cuwwent->mm != mm)
		wetuwn -EINVAW;

	if (mm_vawid_pasid(mm) &&
	    !test_bit(MM_CONTEXT_FOWCE_TAGGED_SVA, &mm->context.fwags))
		wetuwn -EINVAW;

	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn -EINTW;

	if (test_bit(MM_CONTEXT_WOCK_WAM, &mm->context.fwags)) {
		mmap_wwite_unwock(mm);
		wetuwn -EBUSY;
	}

	if (!nw_bits) {
		mmap_wwite_unwock(mm);
		wetuwn -EINVAW;
	} ewse if (nw_bits <= WAM_U57_BITS) {
		mm->context.wam_cw3_mask = X86_CW3_WAM_U57;
		mm->context.untag_mask =  ~GENMASK(62, 57);
	} ewse {
		mmap_wwite_unwock(mm);
		wetuwn -EINVAW;
	}

	wwite_cw3(__wead_cw3() | mm->context.wam_cw3_mask);
	set_twbstate_wam_mode(mm);
	set_bit(MM_CONTEXT_WOCK_WAM, &mm->context.fwags);

	mmap_wwite_unwock(mm);

	wetuwn 0;
}
#endif

wong do_awch_pwctw_64(stwuct task_stwuct *task, int option, unsigned wong awg2)
{
	int wet = 0;

	switch (option) {
	case AWCH_SET_GS: {
		if (unwikewy(awg2 >= TASK_SIZE_MAX))
			wetuwn -EPEWM;

		pweempt_disabwe();
		/*
		 * AWCH_SET_GS has awways ovewwwitten the index
		 * and the base. Zewo is the most sensibwe vawue
		 * to put in the index, and is the onwy vawue that
		 * makes any sense if FSGSBASE is unavaiwabwe.
		 */
		if (task == cuwwent) {
			woadseg(GS, 0);
			x86_gsbase_wwite_cpu_inactive(awg2);

			/*
			 * On non-FSGSBASE systems, save_base_wegacy() expects
			 * that we awso fiww in thwead.gsbase.
			 */
			task->thwead.gsbase = awg2;

		} ewse {
			task->thwead.gsindex = 0;
			x86_gsbase_wwite_task(task, awg2);
		}
		pweempt_enabwe();
		bweak;
	}
	case AWCH_SET_FS: {
		/*
		 * Not stwictwy needed fow %fs, but do it fow symmetwy
		 * with %gs
		 */
		if (unwikewy(awg2 >= TASK_SIZE_MAX))
			wetuwn -EPEWM;

		pweempt_disabwe();
		/*
		 * Set the sewectow to 0 fow the same weason
		 * as %gs above.
		 */
		if (task == cuwwent) {
			woadseg(FS, 0);
			x86_fsbase_wwite_cpu(awg2);

			/*
			 * On non-FSGSBASE systems, save_base_wegacy() expects
			 * that we awso fiww in thwead.fsbase.
			 */
			task->thwead.fsbase = awg2;
		} ewse {
			task->thwead.fsindex = 0;
			x86_fsbase_wwite_task(task, awg2);
		}
		pweempt_enabwe();
		bweak;
	}
	case AWCH_GET_FS: {
		unsigned wong base = x86_fsbase_wead_task(task);

		wet = put_usew(base, (unsigned wong __usew *)awg2);
		bweak;
	}
	case AWCH_GET_GS: {
		unsigned wong base = x86_gsbase_wead_task(task);

		wet = put_usew(base, (unsigned wong __usew *)awg2);
		bweak;
	}

#ifdef CONFIG_CHECKPOINT_WESTOWE
# ifdef CONFIG_X86_X32_ABI
	case AWCH_MAP_VDSO_X32:
		wetuwn pwctw_map_vdso(&vdso_image_x32, awg2);
# endif
# if defined CONFIG_X86_32 || defined CONFIG_IA32_EMUWATION
	case AWCH_MAP_VDSO_32:
		wetuwn pwctw_map_vdso(&vdso_image_32, awg2);
# endif
	case AWCH_MAP_VDSO_64:
		wetuwn pwctw_map_vdso(&vdso_image_64, awg2);
#endif
#ifdef CONFIG_ADDWESS_MASKING
	case AWCH_GET_UNTAG_MASK:
		wetuwn put_usew(task->mm->context.untag_mask,
				(unsigned wong __usew *)awg2);
	case AWCH_ENABWE_TAGGED_ADDW:
		wetuwn pwctw_enabwe_tagged_addw(task->mm, awg2);
	case AWCH_FOWCE_TAGGED_SVA:
		if (cuwwent != task)
			wetuwn -EINVAW;
		set_bit(MM_CONTEXT_FOWCE_TAGGED_SVA, &task->mm->context.fwags);
		wetuwn 0;
	case AWCH_GET_MAX_TAG_BITS:
		if (!cpu_featuwe_enabwed(X86_FEATUWE_WAM))
			wetuwn put_usew(0, (unsigned wong __usew *)awg2);
		ewse
			wetuwn put_usew(WAM_U57_BITS, (unsigned wong __usew *)awg2);
#endif
	case AWCH_SHSTK_ENABWE:
	case AWCH_SHSTK_DISABWE:
	case AWCH_SHSTK_WOCK:
	case AWCH_SHSTK_UNWOCK:
	case AWCH_SHSTK_STATUS:
		wetuwn shstk_pwctw(task, option, awg2);
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

SYSCAWW_DEFINE2(awch_pwctw, int, option, unsigned wong, awg2)
{
	wong wet;

	wet = do_awch_pwctw_64(cuwwent, option, awg2);
	if (wet == -EINVAW)
		wet = do_awch_pwctw_common(option, awg2);

	wetuwn wet;
}

#ifdef CONFIG_IA32_EMUWATION
COMPAT_SYSCAWW_DEFINE2(awch_pwctw, int, option, unsigned wong, awg2)
{
	wetuwn do_awch_pwctw_common(option, awg2);
}
#endif

unsigned wong KSTK_ESP(stwuct task_stwuct *task)
{
	wetuwn task_pt_wegs(task)->sp;
}
