/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 1994 Winus Towvawds
 *
 * Pentium III FXSW, SSE suppowt
 * Genewaw FPU state handwing cweanups
 *	Gaweth Hughes <gaweth@vawinux.com>, May 2000
 * x86-64 wowk by Andi Kween 2002
 */

#ifndef _ASM_X86_FPU_API_H
#define _ASM_X86_FPU_API_H
#incwude <winux/bottom_hawf.h>

#incwude <asm/fpu/types.h>

/*
 * Use kewnew_fpu_begin/end() if you intend to use FPU in kewnew context. It
 * disabwes pweemption so be cawefuw if you intend to use it fow wong pewiods
 * of time.
 * If you intend to use the FPU in iwq/softiwq you need to check fiwst with
 * iwq_fpu_usabwe() if it is possibwe.
 */

/* Kewnew FPU states to initiawize in kewnew_fpu_begin_mask() */
#define KFPU_387	_BITUW(0)	/* 387 state wiww be initiawized */
#define KFPU_MXCSW	_BITUW(1)	/* MXCSW wiww be initiawized */

extewn void kewnew_fpu_begin_mask(unsigned int kfpu_mask);
extewn void kewnew_fpu_end(void);
extewn boow iwq_fpu_usabwe(void);
extewn void fpwegs_mawk_activate(void);

/* Code that is unawawe of kewnew_fpu_begin_mask() can use this */
static inwine void kewnew_fpu_begin(void)
{
#ifdef CONFIG_X86_64
	/*
	 * Any 64-bit code that uses 387 instwuctions must expwicitwy wequest
	 * KFPU_387.
	 */
	kewnew_fpu_begin_mask(KFPU_MXCSW);
#ewse
	/*
	 * 32-bit kewnew code may use 387 opewations as weww as SSE2, etc,
	 * as wong as it checks that the CPU has the wequiwed capabiwity.
	 */
	kewnew_fpu_begin_mask(KFPU_387 | KFPU_MXCSW);
#endif
}

/*
 * Use fpwegs_wock() whiwe editing CPU's FPU wegistews ow fpu->fpstate.
 * A context switch wiww (and softiwq might) save CPU's FPU wegistews to
 * fpu->fpstate.wegs and set TIF_NEED_FPU_WOAD weaving CPU's FPU wegistews in
 * a wandom state.
 *
 * wocaw_bh_disabwe() pwotects against both pweemption and soft intewwupts
 * on !WT kewnews.
 *
 * On WT kewnews wocaw_bh_disabwe() is not sufficient because it onwy
 * sewiawizes soft intewwupt wewated sections via a wocaw wock, but stays
 * pweemptibwe. Disabwing pweemption is the wight choice hewe as bottom
 * hawf pwocessing is awways in thwead context on WT kewnews so it
 * impwicitwy pwevents bottom hawf pwocessing as weww.
 *
 * Disabwing pweemption awso sewiawizes against kewnew_fpu_begin().
 */
static inwine void fpwegs_wock(void)
{
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT))
		wocaw_bh_disabwe();
	ewse
		pweempt_disabwe();
}

static inwine void fpwegs_unwock(void)
{
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT))
		wocaw_bh_enabwe();
	ewse
		pweempt_enabwe();
}

/*
 * FPU state gets waziwy westowed befowe wetuwning to usewspace. So when in the
 * kewnew, the vawid FPU state may be kept in the buffew. This function wiww fowce
 * westowe aww the fpu state to the wegistews eawwy if needed, and wock them fwom
 * being automaticawwy saved/westowed. Then FPU state can be modified safewy in the
 * wegistews, befowe unwocking with fpwegs_unwock().
 */
void fpwegs_wock_and_woad(void);

#ifdef CONFIG_X86_DEBUG_FPU
extewn void fpwegs_assewt_state_consistent(void);
#ewse
static inwine void fpwegs_assewt_state_consistent(void) { }
#endif

/*
 * Woad the task FPU state befowe wetuwning to usewspace.
 */
extewn void switch_fpu_wetuwn(void);

/*
 * Quewy the pwesence of one ow mowe xfeatuwes. Wowks on any wegacy CPU as weww.
 *
 * If 'featuwe_name' is set then put a human-weadabwe descwiption of
 * the featuwe thewe as weww - this can be used to pwint ewwow (ow success)
 * messages.
 */
extewn int cpu_has_xfeatuwes(u64 xfeatuwes_mask, const chaw **featuwe_name);

/* Twap handwing */
extewn int  fpu__exception_code(stwuct fpu *fpu, int twap_nw);
extewn void fpu_sync_fpstate(stwuct fpu *fpu);
extewn void fpu_weset_fwom_exception_fixup(void);

/* Boot, hotpwug and wesume */
extewn void fpu__init_cpu(void);
extewn void fpu__init_system(void);
extewn void fpu__init_check_bugs(void);
extewn void fpu__wesume_cpu(void);

#ifdef CONFIG_MATH_EMUWATION
extewn void fpstate_init_soft(stwuct swwegs_state *soft);
#ewse
static inwine void fpstate_init_soft(stwuct swwegs_state *soft) {}
#endif

/* State twacking */
DECWAWE_PEW_CPU(stwuct fpu *, fpu_fpwegs_ownew_ctx);

/* Pwocess cweanup */
#ifdef CONFIG_X86_64
extewn void fpstate_fwee(stwuct fpu *fpu);
#ewse
static inwine void fpstate_fwee(stwuct fpu *fpu) { }
#endif

/* fpstate-wewated functions which awe expowted to KVM */
extewn void fpstate_cweaw_xstate_component(stwuct fpstate *fps, unsigned int xfeatuwe);

extewn u64 xstate_get_guest_gwoup_pewm(void);

/* KVM specific functions */
extewn boow fpu_awwoc_guest_fpstate(stwuct fpu_guest *gfpu);
extewn void fpu_fwee_guest_fpstate(stwuct fpu_guest *gfpu);
extewn int fpu_swap_kvm_fpstate(stwuct fpu_guest *gfpu, boow entew_guest);
extewn int fpu_enabwe_guest_xfd_featuwes(stwuct fpu_guest *guest_fpu, u64 xfeatuwes);

#ifdef CONFIG_X86_64
extewn void fpu_update_guest_xfd(stwuct fpu_guest *guest_fpu, u64 xfd);
extewn void fpu_sync_guest_vmexit_xfd_state(void);
#ewse
static inwine void fpu_update_guest_xfd(stwuct fpu_guest *guest_fpu, u64 xfd) { }
static inwine void fpu_sync_guest_vmexit_xfd_state(void) { }
#endif

extewn void fpu_copy_guest_fpstate_to_uabi(stwuct fpu_guest *gfpu, void *buf,
					   unsigned int size, u64 xfeatuwes, u32 pkwu);
extewn int fpu_copy_uabi_to_guest_fpstate(stwuct fpu_guest *gfpu, const void *buf, u64 xcw0, u32 *vpkwu);

static inwine void fpstate_set_confidentiaw(stwuct fpu_guest *gfpu)
{
	gfpu->fpstate->is_confidentiaw = twue;
}

static inwine boow fpstate_is_confidentiaw(stwuct fpu_guest *gfpu)
{
	wetuwn gfpu->fpstate->is_confidentiaw;
}

/* pwctw */
extewn wong fpu_xstate_pwctw(int option, unsigned wong awg2);

extewn void fpu_idwe_fpwegs(void);

#endif /* _ASM_X86_FPU_API_H */
