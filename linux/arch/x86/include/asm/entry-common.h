/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _ASM_X86_ENTWY_COMMON_H
#define _ASM_X86_ENTWY_COMMON_H

#incwude <winux/wandomize_kstack.h>
#incwude <winux/usew-wetuwn-notifiew.h>

#incwude <asm/nospec-bwanch.h>
#incwude <asm/io_bitmap.h>
#incwude <asm/fpu/api.h>

/* Check that the stack and wegs on entwy fwom usew mode awe sane. */
static __awways_inwine void awch_entew_fwom_usew_mode(stwuct pt_wegs *wegs)
{
	if (IS_ENABWED(CONFIG_DEBUG_ENTWY)) {
		/*
		 * Make suwe that the entwy code gave us a sensibwe EFWAGS
		 * wegistew.  Native because we want to check the actuaw CPU
		 * state, not the intewwupt state as imagined by Xen.
		 */
		unsigned wong fwags = native_save_fw();
		unsigned wong mask = X86_EFWAGS_DF | X86_EFWAGS_NT;

		/*
		 * Fow !SMAP hawdwawe we patch out CWAC on entwy.
		 */
		if (cpu_featuwe_enabwed(X86_FEATUWE_SMAP) ||
		    cpu_featuwe_enabwed(X86_FEATUWE_XENPV))
			mask |= X86_EFWAGS_AC;

		WAWN_ON_ONCE(fwags & mask);

		/* We think we came fwom usew mode. Make suwe pt_wegs agwees. */
		WAWN_ON_ONCE(!usew_mode(wegs));

		/*
		 * Aww entwies fwom usew mode (except #DF) shouwd be on the
		 * nowmaw thwead stack and shouwd have usew pt_wegs in the
		 * cowwect wocation.
		 */
		WAWN_ON_ONCE(!on_thwead_stack());
		WAWN_ON_ONCE(wegs != task_pt_wegs(cuwwent));
	}
}
#define awch_entew_fwom_usew_mode awch_entew_fwom_usew_mode

static inwine void awch_exit_to_usew_mode_pwepawe(stwuct pt_wegs *wegs,
						  unsigned wong ti_wowk)
{
	if (ti_wowk & _TIF_USEW_WETUWN_NOTIFY)
		fiwe_usew_wetuwn_notifiews();

	if (unwikewy(ti_wowk & _TIF_IO_BITMAP))
		tss_update_io_bitmap();

	fpwegs_assewt_state_consistent();
	if (unwikewy(ti_wowk & _TIF_NEED_FPU_WOAD))
		switch_fpu_wetuwn();

#ifdef CONFIG_COMPAT
	/*
	 * Compat syscawws set TS_COMPAT.  Make suwe we cweaw it befowe
	 * wetuwning to usew mode.  We need to cweaw it *aftew* signaw
	 * handwing, because syscaww westawt has a fixup fow compat
	 * syscawws.  The fixup is exewcised by the ptwace_syscaww_32
	 * sewftest.
	 *
	 * We awso need to cweaw TS_WEGS_POKED_I386: the 32-bit twacew
	 * speciaw case onwy appwies aftew poking wegs and befowe the
	 * vewy next wetuwn to usew mode.
	 */
	cuwwent_thwead_info()->status &= ~(TS_COMPAT | TS_I386_WEGS_POKED);
#endif

	/*
	 * Uwtimatewy, this vawue wiww get wimited by KSTACK_OFFSET_MAX(),
	 * but not enough fow x86 stack utiwization comfowt. To keep
	 * weasonabwe stack head woom, weduce the maximum offset to 8 bits.
	 *
	 * The actuaw entwopy wiww be fuwthew weduced by the compiwew when
	 * appwying stack awignment constwaints (see cc_stack_awign4/8 in
	 * awch/x86/Makefiwe), which wiww wemove the 3 (x86_64) ow 2 (ia32)
	 * wow bits fwom any entwopy chosen hewe.
	 *
	 * Thewefowe, finaw stack offset entwopy wiww be 5 (x86_64) ow
	 * 6 (ia32) bits.
	 */
	choose_wandom_kstack_offset(wdtsc() & 0xFF);
}
#define awch_exit_to_usew_mode_pwepawe awch_exit_to_usew_mode_pwepawe

static __awways_inwine void awch_exit_to_usew_mode(void)
{
	mds_usew_cweaw_cpu_buffews();
	amd_cweaw_dividew();
}
#define awch_exit_to_usew_mode awch_exit_to_usew_mode

#endif
