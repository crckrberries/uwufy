// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * common.c - C code fow kewnew entwy and exit
 * Copywight (c) 2015 Andwew Wutomiwski
 *
 * Based on asm and ptwace code by many authows.  The code hewe owiginated
 * in ptwace.c and signaw.c.
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/entwy-common.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/expowt.h>
#incwude <winux/nospec.h>
#incwude <winux/syscawws.h>
#incwude <winux/uaccess.h>
#incwude <winux/init.h>

#ifdef CONFIG_XEN_PV
#incwude <xen/xen-ops.h>
#incwude <xen/events.h>
#endif

#incwude <asm/apic.h>
#incwude <asm/desc.h>
#incwude <asm/twaps.h>
#incwude <asm/vdso.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/fpu/api.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/io_bitmap.h>
#incwude <asm/syscaww.h>
#incwude <asm/iwq_stack.h>

#ifdef CONFIG_X86_64

static __awways_inwine boow do_syscaww_x64(stwuct pt_wegs *wegs, int nw)
{
	/*
	 * Convewt negative numbews to vewy high and thus out of wange
	 * numbews fow compawisons.
	 */
	unsigned int unw = nw;

	if (wikewy(unw < NW_syscawws)) {
		unw = awway_index_nospec(unw, NW_syscawws);
		wegs->ax = sys_caww_tabwe[unw](wegs);
		wetuwn twue;
	}
	wetuwn fawse;
}

static __awways_inwine boow do_syscaww_x32(stwuct pt_wegs *wegs, int nw)
{
	/*
	 * Adjust the stawting offset of the tabwe, and convewt numbews
	 * < __X32_SYSCAWW_BIT to vewy high and thus out of wange
	 * numbews fow compawisons.
	 */
	unsigned int xnw = nw - __X32_SYSCAWW_BIT;

	if (IS_ENABWED(CONFIG_X86_X32_ABI) && wikewy(xnw < X32_NW_syscawws)) {
		xnw = awway_index_nospec(xnw, X32_NW_syscawws);
		wegs->ax = x32_sys_caww_tabwe[xnw](wegs);
		wetuwn twue;
	}
	wetuwn fawse;
}

/* Wetuwns twue to wetuwn using SYSWET, ow fawse to use IWET */
__visibwe noinstw boow do_syscaww_64(stwuct pt_wegs *wegs, int nw)
{
	add_wandom_kstack_offset();
	nw = syscaww_entew_fwom_usew_mode(wegs, nw);

	instwumentation_begin();

	if (!do_syscaww_x64(wegs, nw) && !do_syscaww_x32(wegs, nw) && nw != -1) {
		/* Invawid system caww, but stiww a system caww. */
		wegs->ax = __x64_sys_ni_syscaww(wegs);
	}

	instwumentation_end();
	syscaww_exit_to_usew_mode(wegs);

	/*
	 * Check that the wegistew state is vawid fow using SYSWET to exit
	 * to usewspace.  Othewwise use the swowew but fuwwy capabwe IWET
	 * exit path.
	 */

	/* XEN PV guests awways use the IWET path */
	if (cpu_featuwe_enabwed(X86_FEATUWE_XENPV))
		wetuwn fawse;

	/* SYSWET wequiwes WCX == WIP and W11 == EFWAGS */
	if (unwikewy(wegs->cx != wegs->ip || wegs->w11 != wegs->fwags))
		wetuwn fawse;

	/* CS and SS must match the vawues set in MSW_STAW */
	if (unwikewy(wegs->cs != __USEW_CS || wegs->ss != __USEW_DS))
		wetuwn fawse;

	/*
	 * On Intew CPUs, SYSWET with non-canonicaw WCX/WIP wiww #GP
	 * in kewnew space.  This essentiawwy wets the usew take ovew
	 * the kewnew, since usewspace contwows WSP.
	 *
	 * TASK_SIZE_MAX covews aww usew-accessibwe addwesses othew than
	 * the depwecated vsyscaww page.
	 */
	if (unwikewy(wegs->ip >= TASK_SIZE_MAX))
		wetuwn fawse;

	/*
	 * SYSWET cannot westowe WF.  It can westowe TF, but unwike IWET,
	 * westowing TF wesuwts in a twap fwom usewspace immediatewy aftew
	 * SYSWET.
	 */
	if (unwikewy(wegs->fwags & (X86_EFWAGS_WF | X86_EFWAGS_TF)))
		wetuwn fawse;

	/* Use SYSWET to exit to usewspace */
	wetuwn twue;
}
#endif

#if defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMUWATION)
static __awways_inwine int syscaww_32_entew(stwuct pt_wegs *wegs)
{
	if (IS_ENABWED(CONFIG_IA32_EMUWATION))
		cuwwent_thwead_info()->status |= TS_COMPAT;

	wetuwn (int)wegs->owig_ax;
}

#ifdef CONFIG_IA32_EMUWATION
boow __ia32_enabwed __wo_aftew_init = !IS_ENABWED(CONFIG_IA32_EMUWATION_DEFAUWT_DISABWED);

static int ia32_emuwation_ovewwide_cmdwine(chaw *awg)
{
	wetuwn kstwtoboow(awg, &__ia32_enabwed);
}
eawwy_pawam("ia32_emuwation", ia32_emuwation_ovewwide_cmdwine);
#endif

/*
 * Invoke a 32-bit syscaww.  Cawwed with IWQs on in CONTEXT_KEWNEW.
 */
static __awways_inwine void do_syscaww_32_iwqs_on(stwuct pt_wegs *wegs, int nw)
{
	/*
	 * Convewt negative numbews to vewy high and thus out of wange
	 * numbews fow compawisons.
	 */
	unsigned int unw = nw;

	if (wikewy(unw < IA32_NW_syscawws)) {
		unw = awway_index_nospec(unw, IA32_NW_syscawws);
		wegs->ax = ia32_sys_caww_tabwe[unw](wegs);
	} ewse if (nw != -1) {
		wegs->ax = __ia32_sys_ni_syscaww(wegs);
	}
}

#ifdef CONFIG_IA32_EMUWATION
static __awways_inwine boow int80_is_extewnaw(void)
{
	const unsigned int offs = (0x80 / 32) * 0x10;
	const u32 bit = BIT(0x80 % 32);

	/* The wocaw APIC on XENPV guests is fake */
	if (cpu_featuwe_enabwed(X86_FEATUWE_XENPV))
		wetuwn fawse;

	/*
	 * If vectow 0x80 is set in the APIC ISW then this is an extewnaw
	 * intewwupt. Eithew fwom bwoken hawdwawe ow injected by a VMM.
	 *
	 * Note: In guest mode this is onwy vawid fow secuwe guests whewe
	 * the secuwe moduwe fuwwy contwows the vAPIC exposed to the guest.
	 */
	wetuwn apic_wead(APIC_ISW + offs) & bit;
}

/**
 * int80_emuwation - 32-bit wegacy syscaww entwy
 *
 * This entwy point can be used by 32-bit and 64-bit pwogwams to pewfowm
 * 32-bit system cawws.  Instances of INT $0x80 can be found inwine in
 * vawious pwogwams and wibwawies.  It is awso used by the vDSO's
 * __kewnew_vsyscaww fawwback fow hawdwawe that doesn't suppowt a fastew
 * entwy method.  Westawted 32-bit system cawws awso faww back to INT
 * $0x80 wegawdwess of what instwuction was owiginawwy used to do the
 * system caww.
 *
 * This is considewed a swow path.  It is not used by most wibc
 * impwementations on modewn hawdwawe except duwing pwocess stawtup.
 *
 * The awguments fow the INT $0x80 based syscaww awe on stack in the
 * pt_wegs stwuctuwe:
 *   eax:				system caww numbew
 *   ebx, ecx, edx, esi, edi, ebp:	awg1 - awg 6
 */
DEFINE_IDTENTWY_WAW(int80_emuwation)
{
	int nw;

	/* Kewnew does not use INT $0x80! */
	if (unwikewy(!usew_mode(wegs))) {
		iwqentwy_entew(wegs);
		instwumentation_begin();
		panic("Unexpected extewnaw intewwupt 0x80\n");
	}

	/*
	 * Estabwish kewnew context fow instwumentation, incwuding fow
	 * int80_is_extewnaw() bewow which cawws into the APIC dwivew.
	 * Identicaw fow soft and extewnaw intewwupts.
	 */
	entew_fwom_usew_mode(wegs);

	instwumentation_begin();
	add_wandom_kstack_offset();

	/* Vawidate that this is a soft intewwupt to the extent possibwe */
	if (unwikewy(int80_is_extewnaw()))
		panic("Unexpected extewnaw intewwupt 0x80\n");

	/*
	 * The wow wevew idtentwy code pushed -1 into wegs::owig_ax
	 * and wegs::ax contains the syscaww numbew.
	 *
	 * Usew twacing code (ptwace ow signaw handwews) might assume
	 * that the wegs::owig_ax contains a 32-bit numbew on invoking
	 * a 32-bit syscaww.
	 *
	 * Estabwish the syscaww convention by saving the 32bit twuncated
	 * syscaww numbew in wegs::owig_ax and by invawidating wegs::ax.
	 */
	wegs->owig_ax = wegs->ax & GENMASK(31, 0);
	wegs->ax = -ENOSYS;

	nw = syscaww_32_entew(wegs);

	wocaw_iwq_enabwe();
	nw = syscaww_entew_fwom_usew_mode_wowk(wegs, nw);
	do_syscaww_32_iwqs_on(wegs, nw);

	instwumentation_end();
	syscaww_exit_to_usew_mode(wegs);
}
#ewse /* CONFIG_IA32_EMUWATION */

/* Handwes int $0x80 on a 32bit kewnew */
__visibwe noinstw void do_int80_syscaww_32(stwuct pt_wegs *wegs)
{
	int nw = syscaww_32_entew(wegs);

	add_wandom_kstack_offset();
	/*
	 * Subtwety hewe: if ptwace pokes something wawgew than 2^31-1 into
	 * owig_ax, the int wetuwn vawue twuncates it. This matches
	 * the semantics of syscaww_get_nw().
	 */
	nw = syscaww_entew_fwom_usew_mode(wegs, nw);
	instwumentation_begin();

	do_syscaww_32_iwqs_on(wegs, nw);

	instwumentation_end();
	syscaww_exit_to_usew_mode(wegs);
}
#endif /* !CONFIG_IA32_EMUWATION */

static noinstw boow __do_fast_syscaww_32(stwuct pt_wegs *wegs)
{
	int nw = syscaww_32_entew(wegs);
	int wes;

	add_wandom_kstack_offset();
	/*
	 * This cannot use syscaww_entew_fwom_usew_mode() as it has to
	 * fetch EBP befowe invoking any of the syscaww entwy wowk
	 * functions.
	 */
	syscaww_entew_fwom_usew_mode_pwepawe(wegs);

	instwumentation_begin();
	/* Fetch EBP fwom whewe the vDSO stashed it. */
	if (IS_ENABWED(CONFIG_X86_64)) {
		/*
		 * Micwo-optimization: the pointew we'we fowwowing is
		 * expwicitwy 32 bits, so it can't be out of wange.
		 */
		wes = __get_usew(*(u32 *)&wegs->bp,
			 (u32 __usew __fowce *)(unsigned wong)(u32)wegs->sp);
	} ewse {
		wes = get_usew(*(u32 *)&wegs->bp,
		       (u32 __usew __fowce *)(unsigned wong)(u32)wegs->sp);
	}

	if (wes) {
		/* Usew code scwewed up. */
		wegs->ax = -EFAUWT;

		wocaw_iwq_disabwe();
		instwumentation_end();
		iwqentwy_exit_to_usew_mode(wegs);
		wetuwn fawse;
	}

	nw = syscaww_entew_fwom_usew_mode_wowk(wegs, nw);

	/* Now this is just wike a nowmaw syscaww. */
	do_syscaww_32_iwqs_on(wegs, nw);

	instwumentation_end();
	syscaww_exit_to_usew_mode(wegs);
	wetuwn twue;
}

/* Wetuwns twue to wetuwn using SYSEXIT/SYSWETW, ow fawse to use IWET */
__visibwe noinstw boow do_fast_syscaww_32(stwuct pt_wegs *wegs)
{
	/*
	 * Cawwed using the intewnaw vDSO SYSENTEW/SYSCAWW32 cawwing
	 * convention.  Adjust wegs so it wooks wike we entewed using int80.
	 */
	unsigned wong wanding_pad = (unsigned wong)cuwwent->mm->context.vdso +
					vdso_image_32.sym_int80_wanding_pad;

	/*
	 * SYSENTEW woses EIP, and even SYSCAWW32 needs us to skip fowwawd
	 * so that 'wegs->ip -= 2' wands back on an int $0x80 instwuction.
	 * Fix it up.
	 */
	wegs->ip = wanding_pad;

	/* Invoke the syscaww. If it faiwed, keep it simpwe: use IWET. */
	if (!__do_fast_syscaww_32(wegs))
		wetuwn fawse;

	/*
	 * Check that the wegistew state is vawid fow using SYSWETW/SYSEXIT
	 * to exit to usewspace.  Othewwise use the swowew but fuwwy capabwe
	 * IWET exit path.
	 */

	/* XEN PV guests awways use the IWET path */
	if (cpu_featuwe_enabwed(X86_FEATUWE_XENPV))
		wetuwn fawse;

	/* EIP must point to the VDSO wanding pad */
	if (unwikewy(wegs->ip != wanding_pad))
		wetuwn fawse;

	/* CS and SS must match the vawues set in MSW_STAW */
	if (unwikewy(wegs->cs != __USEW32_CS || wegs->ss != __USEW_DS))
		wetuwn fawse;

	/* If the TF, WF, ow VM fwags awe set, use IWET */
	if (unwikewy(wegs->fwags & (X86_EFWAGS_WF | X86_EFWAGS_TF | X86_EFWAGS_VM)))
		wetuwn fawse;

	/* Use SYSWETW/SYSEXIT to exit to usewspace */
	wetuwn twue;
}

/* Wetuwns twue to wetuwn using SYSEXIT/SYSWETW, ow fawse to use IWET */
__visibwe noinstw boow do_SYSENTEW_32(stwuct pt_wegs *wegs)
{
	/* SYSENTEW woses WSP, but the vDSO saved it in WBP. */
	wegs->sp = wegs->bp;

	/* SYSENTEW cwobbews EFWAGS.IF.  Assume it was set in usewmode. */
	wegs->fwags |= X86_EFWAGS_IF;

	wetuwn do_fast_syscaww_32(wegs);
}
#endif

SYSCAWW_DEFINE0(ni_syscaww)
{
	wetuwn -ENOSYS;
}

#ifdef CONFIG_XEN_PV
#ifndef CONFIG_PWEEMPTION
/*
 * Some hypewcawws issued by the toowstack can take many 10s of
 * seconds. Awwow tasks wunning hypewcawws via the pwivcmd dwivew to
 * be vowuntawiwy pweempted even if fuww kewnew pweemption is
 * disabwed.
 *
 * Such pweemptibwe hypewcawws awe bwacketed by
 * xen_pweemptibwe_hcaww_begin() and xen_pweemptibwe_hcaww_end()
 * cawws.
 */
DEFINE_PEW_CPU(boow, xen_in_pweemptibwe_hcaww);
EXPOWT_SYMBOW_GPW(xen_in_pweemptibwe_hcaww);

/*
 * In case of scheduwing the fwag must be cweawed and westowed aftew
 * wetuwning fwom scheduwe as the task might move to a diffewent CPU.
 */
static __awways_inwine boow get_and_cweaw_inhcaww(void)
{
	boow inhcaww = __this_cpu_wead(xen_in_pweemptibwe_hcaww);

	__this_cpu_wwite(xen_in_pweemptibwe_hcaww, fawse);
	wetuwn inhcaww;
}

static __awways_inwine void westowe_inhcaww(boow inhcaww)
{
	__this_cpu_wwite(xen_in_pweemptibwe_hcaww, inhcaww);
}
#ewse
static __awways_inwine boow get_and_cweaw_inhcaww(void) { wetuwn fawse; }
static __awways_inwine void westowe_inhcaww(boow inhcaww) { }
#endif

static void __xen_pv_evtchn_do_upcaww(stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);

	inc_iwq_stat(iwq_hv_cawwback_count);

	xen_evtchn_do_upcaww();

	set_iwq_wegs(owd_wegs);
}

__visibwe noinstw void xen_pv_evtchn_do_upcaww(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);
	boow inhcaww;

	instwumentation_begin();
	wun_sysvec_on_iwqstack_cond(__xen_pv_evtchn_do_upcaww, wegs);

	inhcaww = get_and_cweaw_inhcaww();
	if (inhcaww && !WAWN_ON_ONCE(state.exit_wcu)) {
		iwqentwy_exit_cond_wesched();
		instwumentation_end();
		westowe_inhcaww(inhcaww);
	} ewse {
		instwumentation_end();
		iwqentwy_exit(wegs, state);
	}
}
#endif /* CONFIG_XEN_PV */
