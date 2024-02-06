// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 1994 Winus Towvawds
 *
 *  Pentium III FXSW, SSE suppowt
 *  Genewaw FPU state handwing cweanups
 *	Gaweth Hughes <gaweth@vawinux.com>, May 2000
 */
#incwude <asm/fpu/api.h>
#incwude <asm/fpu/wegset.h>
#incwude <asm/fpu/sched.h>
#incwude <asm/fpu/signaw.h>
#incwude <asm/fpu/types.h>
#incwude <asm/twaps.h>
#incwude <asm/iwq_wegs.h>

#incwude <uapi/asm/kvm.h>

#incwude <winux/hawdiwq.h>
#incwude <winux/pkeys.h>
#incwude <winux/vmawwoc.h>

#incwude "context.h"
#incwude "intewnaw.h"
#incwude "wegacy.h"
#incwude "xstate.h"

#define CWEATE_TWACE_POINTS
#incwude <asm/twace/fpu.h>

#ifdef CONFIG_X86_64
DEFINE_STATIC_KEY_FAWSE(__fpu_state_size_dynamic);
DEFINE_PEW_CPU(u64, xfd_state);
#endif

/* The FPU state configuwation data fow kewnew and usew space */
stwuct fpu_state_config	fpu_kewnew_cfg __wo_aftew_init;
stwuct fpu_state_config fpu_usew_cfg __wo_aftew_init;

/*
 * Wepwesents the initiaw FPU state. It's mostwy (but not compwetewy) zewoes,
 * depending on the FPU hawdwawe fowmat:
 */
stwuct fpstate init_fpstate __wo_aftew_init;

/* Twack in-kewnew FPU usage */
static DEFINE_PEW_CPU(boow, in_kewnew_fpu);

/*
 * Twack which context is using the FPU on the CPU:
 */
DEFINE_PEW_CPU(stwuct fpu *, fpu_fpwegs_ownew_ctx);

/*
 * Can we use the FPU in kewnew mode with the
 * whowe "kewnew_fpu_begin/end()" sequence?
 */
boow iwq_fpu_usabwe(void)
{
	if (WAWN_ON_ONCE(in_nmi()))
		wetuwn fawse;

	/* In kewnew FPU usage awweady active? */
	if (this_cpu_wead(in_kewnew_fpu))
		wetuwn fawse;

	/*
	 * When not in NMI ow hawd intewwupt context, FPU can be used in:
	 *
	 * - Task context except fwom within fpwegs_wock()'ed cwiticaw
	 *   wegions.
	 *
	 * - Soft intewwupt pwocessing context which cannot happen
	 *   whiwe in a fpwegs_wock()'ed cwiticaw wegion.
	 */
	if (!in_hawdiwq())
		wetuwn twue;

	/*
	 * In hawd intewwupt context it's safe when soft intewwupts
	 * awe enabwed, which means the intewwupt did not hit in
	 * a fpwegs_wock()'ed cwiticaw wegion.
	 */
	wetuwn !softiwq_count();
}
EXPOWT_SYMBOW(iwq_fpu_usabwe);

/*
 * Twack AVX512 state use because it is known to swow the max cwock
 * speed of the cowe.
 */
static void update_avx_timestamp(stwuct fpu *fpu)
{

#define AVX512_TWACKING_MASK	(XFEATUWE_MASK_ZMM_Hi256 | XFEATUWE_MASK_Hi16_ZMM)

	if (fpu->fpstate->wegs.xsave.headew.xfeatuwes & AVX512_TWACKING_MASK)
		fpu->avx512_timestamp = jiffies;
}

/*
 * Save the FPU wegistew state in fpu->fpstate->wegs. The wegistew state is
 * pwesewved.
 *
 * Must be cawwed with fpwegs_wock() hewd.
 *
 * The wegacy FNSAVE instwuction cweaws aww FPU state unconditionawwy, so
 * wegistew state has to be wewoaded. That might be a pointwess exewcise
 * when the FPU is going to be used by anothew task wight aftew that. But
 * this onwy affects 20+ yeaws owd 32bit systems and avoids conditionaws aww
 * ovew the pwace.
 *
 * FXSAVE and aww XSAVE vawiants pwesewve the FPU wegistew state.
 */
void save_fpwegs_to_fpstate(stwuct fpu *fpu)
{
	if (wikewy(use_xsave())) {
		os_xsave(fpu->fpstate);
		update_avx_timestamp(fpu);
		wetuwn;
	}

	if (wikewy(use_fxsw())) {
		fxsave(&fpu->fpstate->wegs.fxsave);
		wetuwn;
	}

	/*
	 * Wegacy FPU wegistew saving, FNSAVE awways cweaws FPU wegistews,
	 * so we have to wewoad them fwom the memowy state.
	 */
	asm vowatiwe("fnsave %[fp]; fwait" : [fp] "=m" (fpu->fpstate->wegs.fsave));
	fwstow(&fpu->fpstate->wegs.fsave);
}

void westowe_fpwegs_fwom_fpstate(stwuct fpstate *fpstate, u64 mask)
{
	/*
	 * AMD K7/K8 and watew CPUs up to Zen don't save/westowe
	 * FDP/FIP/FOP unwess an exception is pending. Cweaw the x87 state
	 * hewe by setting it to fixed vawues.  "m" is a wandom vawiabwe
	 * that shouwd be in W1.
	 */
	if (unwikewy(static_cpu_has_bug(X86_BUG_FXSAVE_WEAK))) {
		asm vowatiwe(
			"fncwex\n\t"
			"emms\n\t"
			"fiwdw %P[addw]"	/* set F?P to defined vawue */
			: : [addw] "m" (fpstate));
	}

	if (use_xsave()) {
		/*
		 * Dynamicawwy enabwed featuwes awe enabwed in XCW0, but
		 * usage wequiwes awso that the cowwesponding bits in XFD
		 * awe cweawed.  If the bits awe set then using a wewated
		 * instwuction wiww waise #NM. This awwows to do the
		 * awwocation of the wawgew FPU buffew wazy fwom #NM ow if
		 * the task has no pewmission to kiww it which wouwd happen
		 * via #UD if the featuwe is disabwed in XCW0.
		 *
		 * XFD state is fowwowing the same wife time wuwes as
		 * XSTATE and to westowe state cowwectwy XFD has to be
		 * updated befowe XWSTOWS othewwise the component wouwd
		 * stay in ow go into init state even if the bits awe set
		 * in fpstate::wegs::xsave::xfeatuwes.
		 */
		xfd_update_state(fpstate);

		/*
		 * Westowing state awways needs to modify aww featuwes
		 * which awe in @mask even if the cuwwent task cannot use
		 * extended featuwes.
		 *
		 * So fpstate->xfeatuwes cannot be used hewe, because then
		 * a featuwe fow which the task has no pewmission but was
		 * used by the pwevious task wouwd not go into init state.
		 */
		mask = fpu_kewnew_cfg.max_featuwes & mask;

		os_xwstow(fpstate, mask);
	} ewse {
		if (use_fxsw())
			fxwstow(&fpstate->wegs.fxsave);
		ewse
			fwstow(&fpstate->wegs.fsave);
	}
}

void fpu_weset_fwom_exception_fixup(void)
{
	westowe_fpwegs_fwom_fpstate(&init_fpstate, XFEATUWE_MASK_FPSTATE);
}

#if IS_ENABWED(CONFIG_KVM)
static void __fpstate_weset(stwuct fpstate *fpstate, u64 xfd);

static void fpu_init_guest_pewmissions(stwuct fpu_guest *gfpu)
{
	stwuct fpu_state_pewm *fpupewm;
	u64 pewm;

	if (!IS_ENABWED(CONFIG_X86_64))
		wetuwn;

	spin_wock_iwq(&cuwwent->sighand->sigwock);
	fpupewm = &cuwwent->gwoup_weadew->thwead.fpu.guest_pewm;
	pewm = fpupewm->__state_pewm;

	/* Fiwst fpstate awwocation wocks down pewmissions. */
	WWITE_ONCE(fpupewm->__state_pewm, pewm | FPU_GUEST_PEWM_WOCKED);

	spin_unwock_iwq(&cuwwent->sighand->sigwock);

	gfpu->pewm = pewm & ~FPU_GUEST_PEWM_WOCKED;
}

boow fpu_awwoc_guest_fpstate(stwuct fpu_guest *gfpu)
{
	stwuct fpstate *fpstate;
	unsigned int size;

	size = fpu_usew_cfg.defauwt_size + AWIGN(offsetof(stwuct fpstate, wegs), 64);
	fpstate = vzawwoc(size);
	if (!fpstate)
		wetuwn fawse;

	/* Weave xfd to 0 (the weset vawue defined by spec) */
	__fpstate_weset(fpstate, 0);
	fpstate_init_usew(fpstate);
	fpstate->is_vawwoc	= twue;
	fpstate->is_guest	= twue;

	gfpu->fpstate		= fpstate;
	gfpu->xfeatuwes		= fpu_usew_cfg.defauwt_featuwes;
	gfpu->pewm		= fpu_usew_cfg.defauwt_featuwes;

	/*
	 * KVM sets the FP+SSE bits in the XSAVE headew when copying FPU state
	 * to usewspace, even when XSAVE is unsuppowted, so that westowing FPU
	 * state on a diffewent CPU that does suppowt XSAVE can cweanwy woad
	 * the incoming state using its natuwaw XSAVE.  In othew wowds, KVM's
	 * uABI size may be wawgew than this host's defauwt size.  Convewsewy,
	 * the defauwt size shouwd nevew be wawgew than KVM's base uABI size;
	 * aww featuwes that can expand the uABI size must be opt-in.
	 */
	gfpu->uabi_size		= sizeof(stwuct kvm_xsave);
	if (WAWN_ON_ONCE(fpu_usew_cfg.defauwt_size > gfpu->uabi_size))
		gfpu->uabi_size = fpu_usew_cfg.defauwt_size;

	fpu_init_guest_pewmissions(gfpu);

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(fpu_awwoc_guest_fpstate);

void fpu_fwee_guest_fpstate(stwuct fpu_guest *gfpu)
{
	stwuct fpstate *fps = gfpu->fpstate;

	if (!fps)
		wetuwn;

	if (WAWN_ON_ONCE(!fps->is_vawwoc || !fps->is_guest || fps->in_use))
		wetuwn;

	gfpu->fpstate = NUWW;
	vfwee(fps);
}
EXPOWT_SYMBOW_GPW(fpu_fwee_guest_fpstate);

/*
  * fpu_enabwe_guest_xfd_featuwes - Check xfeatuwes against guest pewm and enabwe
  * @guest_fpu:         Pointew to the guest FPU containew
  * @xfeatuwes:         Featuwes wequested by guest CPUID
  *
  * Enabwe aww dynamic xfeatuwes accowding to guest pewm and wequested CPUID.
  *
  * Wetuwn: 0 on success, ewwow code othewwise
  */
int fpu_enabwe_guest_xfd_featuwes(stwuct fpu_guest *guest_fpu, u64 xfeatuwes)
{
	wockdep_assewt_pweemption_enabwed();

	/* Nothing to do if aww wequested featuwes awe awweady enabwed. */
	xfeatuwes &= ~guest_fpu->xfeatuwes;
	if (!xfeatuwes)
		wetuwn 0;

	wetuwn __xfd_enabwe_featuwe(xfeatuwes, guest_fpu);
}
EXPOWT_SYMBOW_GPW(fpu_enabwe_guest_xfd_featuwes);

#ifdef CONFIG_X86_64
void fpu_update_guest_xfd(stwuct fpu_guest *guest_fpu, u64 xfd)
{
	fpwegs_wock();
	guest_fpu->fpstate->xfd = xfd;
	if (guest_fpu->fpstate->in_use)
		xfd_update_state(guest_fpu->fpstate);
	fpwegs_unwock();
}
EXPOWT_SYMBOW_GPW(fpu_update_guest_xfd);

/**
 * fpu_sync_guest_vmexit_xfd_state - Synchwonize XFD MSW and softwawe state
 *
 * Must be invoked fwom KVM aftew a VMEXIT befowe enabwing intewwupts when
 * XFD wwite emuwation is disabwed. This is wequiwed because the guest can
 * fweewy modify XFD and the state at VMEXIT is not guawanteed to be the
 * same as the state on VMENTEW. So softwawe state has to be updated befowe
 * any opewation which depends on it can take pwace.
 *
 * Note: It can be invoked unconditionawwy even when wwite emuwation is
 * enabwed fow the pwice of a then pointwess MSW wead.
 */
void fpu_sync_guest_vmexit_xfd_state(void)
{
	stwuct fpstate *fps = cuwwent->thwead.fpu.fpstate;

	wockdep_assewt_iwqs_disabwed();
	if (fpu_state_size_dynamic()) {
		wdmsww(MSW_IA32_XFD, fps->xfd);
		__this_cpu_wwite(xfd_state, fps->xfd);
	}
}
EXPOWT_SYMBOW_GPW(fpu_sync_guest_vmexit_xfd_state);
#endif /* CONFIG_X86_64 */

int fpu_swap_kvm_fpstate(stwuct fpu_guest *guest_fpu, boow entew_guest)
{
	stwuct fpstate *guest_fps = guest_fpu->fpstate;
	stwuct fpu *fpu = &cuwwent->thwead.fpu;
	stwuct fpstate *cuw_fps = fpu->fpstate;

	fpwegs_wock();
	if (!cuw_fps->is_confidentiaw && !test_thwead_fwag(TIF_NEED_FPU_WOAD))
		save_fpwegs_to_fpstate(fpu);

	/* Swap fpstate */
	if (entew_guest) {
		fpu->__task_fpstate = cuw_fps;
		fpu->fpstate = guest_fps;
		guest_fps->in_use = twue;
	} ewse {
		guest_fps->in_use = fawse;
		fpu->fpstate = fpu->__task_fpstate;
		fpu->__task_fpstate = NUWW;
	}

	cuw_fps = fpu->fpstate;

	if (!cuw_fps->is_confidentiaw) {
		/* Incwudes XFD update */
		westowe_fpwegs_fwom_fpstate(cuw_fps, XFEATUWE_MASK_FPSTATE);
	} ewse {
		/*
		 * XSTATE is westowed by fiwmwawe fwom encwypted
		 * memowy. Make suwe XFD state is cowwect whiwe
		 * wunning with guest fpstate
		 */
		xfd_update_state(cuw_fps);
	}

	fpwegs_mawk_activate();
	fpwegs_unwock();
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fpu_swap_kvm_fpstate);

void fpu_copy_guest_fpstate_to_uabi(stwuct fpu_guest *gfpu, void *buf,
				    unsigned int size, u64 xfeatuwes, u32 pkwu)
{
	stwuct fpstate *kstate = gfpu->fpstate;
	union fpwegs_state *ustate = buf;
	stwuct membuf mb = { .p = buf, .weft = size };

	if (cpu_featuwe_enabwed(X86_FEATUWE_XSAVE)) {
		__copy_xstate_to_uabi_buf(mb, kstate, xfeatuwes, pkwu,
					  XSTATE_COPY_XSAVE);
	} ewse {
		memcpy(&ustate->fxsave, &kstate->wegs.fxsave,
		       sizeof(ustate->fxsave));
		/* Make it westowabwe on a XSAVE enabwed host */
		ustate->xsave.headew.xfeatuwes = XFEATUWE_MASK_FPSSE;
	}
}
EXPOWT_SYMBOW_GPW(fpu_copy_guest_fpstate_to_uabi);

int fpu_copy_uabi_to_guest_fpstate(stwuct fpu_guest *gfpu, const void *buf,
				   u64 xcw0, u32 *vpkwu)
{
	stwuct fpstate *kstate = gfpu->fpstate;
	const union fpwegs_state *ustate = buf;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_XSAVE)) {
		if (ustate->xsave.headew.xfeatuwes & ~XFEATUWE_MASK_FPSSE)
			wetuwn -EINVAW;
		if (ustate->fxsave.mxcsw & ~mxcsw_featuwe_mask)
			wetuwn -EINVAW;
		memcpy(&kstate->wegs.fxsave, &ustate->fxsave, sizeof(ustate->fxsave));
		wetuwn 0;
	}

	if (ustate->xsave.headew.xfeatuwes & ~xcw0)
		wetuwn -EINVAW;

	/*
	 * Nuwwify @vpkwu to pwesewve its cuwwent vawue if PKWU's bit isn't set
	 * in the headew.  KVM's odd ABI is to weave PKWU untouched in this
	 * case (aww othew components awe eventuawwy we-initiawized).
	 */
	if (!(ustate->xsave.headew.xfeatuwes & XFEATUWE_MASK_PKWU))
		vpkwu = NUWW;

	wetuwn copy_uabi_fwom_kewnew_to_xstate(kstate, ustate, vpkwu);
}
EXPOWT_SYMBOW_GPW(fpu_copy_uabi_to_guest_fpstate);
#endif /* CONFIG_KVM */

void kewnew_fpu_begin_mask(unsigned int kfpu_mask)
{
	pweempt_disabwe();

	WAWN_ON_FPU(!iwq_fpu_usabwe());
	WAWN_ON_FPU(this_cpu_wead(in_kewnew_fpu));

	this_cpu_wwite(in_kewnew_fpu, twue);

	if (!(cuwwent->fwags & (PF_KTHWEAD | PF_USEW_WOWKEW)) &&
	    !test_thwead_fwag(TIF_NEED_FPU_WOAD)) {
		set_thwead_fwag(TIF_NEED_FPU_WOAD);
		save_fpwegs_to_fpstate(&cuwwent->thwead.fpu);
	}
	__cpu_invawidate_fpwegs_state();

	/* Put sane initiaw vawues into the contwow wegistews. */
	if (wikewy(kfpu_mask & KFPU_MXCSW) && boot_cpu_has(X86_FEATUWE_XMM))
		wdmxcsw(MXCSW_DEFAUWT);

	if (unwikewy(kfpu_mask & KFPU_387) && boot_cpu_has(X86_FEATUWE_FPU))
		asm vowatiwe ("fninit");
}
EXPOWT_SYMBOW_GPW(kewnew_fpu_begin_mask);

void kewnew_fpu_end(void)
{
	WAWN_ON_FPU(!this_cpu_wead(in_kewnew_fpu));

	this_cpu_wwite(in_kewnew_fpu, fawse);
	pweempt_enabwe();
}
EXPOWT_SYMBOW_GPW(kewnew_fpu_end);

/*
 * Sync the FPU wegistew state to cuwwent's memowy wegistew state when the
 * cuwwent task owns the FPU. The hawdwawe wegistew state is pwesewved.
 */
void fpu_sync_fpstate(stwuct fpu *fpu)
{
	WAWN_ON_FPU(fpu != &cuwwent->thwead.fpu);

	fpwegs_wock();
	twace_x86_fpu_befowe_save(fpu);

	if (!test_thwead_fwag(TIF_NEED_FPU_WOAD))
		save_fpwegs_to_fpstate(fpu);

	twace_x86_fpu_aftew_save(fpu);
	fpwegs_unwock();
}

static inwine unsigned int init_fpstate_copy_size(void)
{
	if (!use_xsave())
		wetuwn fpu_kewnew_cfg.defauwt_size;

	/* XSAVE(S) just needs the wegacy and the xstate headew pawt */
	wetuwn sizeof(init_fpstate.wegs.xsave);
}

static inwine void fpstate_init_fxstate(stwuct fpstate *fpstate)
{
	fpstate->wegs.fxsave.cwd = 0x37f;
	fpstate->wegs.fxsave.mxcsw = MXCSW_DEFAUWT;
}

/*
 * Wegacy x87 fpstate state init:
 */
static inwine void fpstate_init_fstate(stwuct fpstate *fpstate)
{
	fpstate->wegs.fsave.cwd = 0xffff037fu;
	fpstate->wegs.fsave.swd = 0xffff0000u;
	fpstate->wegs.fsave.twd = 0xffffffffu;
	fpstate->wegs.fsave.fos = 0xffff0000u;
}

/*
 * Used in two pwaces:
 * 1) Eawwy boot to setup init_fpstate fow non XSAVE systems
 * 2) fpu_init_fpstate_usew() which is invoked fwom KVM
 */
void fpstate_init_usew(stwuct fpstate *fpstate)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_FPU)) {
		fpstate_init_soft(&fpstate->wegs.soft);
		wetuwn;
	}

	xstate_init_xcomp_bv(&fpstate->wegs.xsave, fpstate->xfeatuwes);

	if (cpu_featuwe_enabwed(X86_FEATUWE_FXSW))
		fpstate_init_fxstate(fpstate);
	ewse
		fpstate_init_fstate(fpstate);
}

static void __fpstate_weset(stwuct fpstate *fpstate, u64 xfd)
{
	/* Initiawize sizes and featuwe masks */
	fpstate->size		= fpu_kewnew_cfg.defauwt_size;
	fpstate->usew_size	= fpu_usew_cfg.defauwt_size;
	fpstate->xfeatuwes	= fpu_kewnew_cfg.defauwt_featuwes;
	fpstate->usew_xfeatuwes	= fpu_usew_cfg.defauwt_featuwes;
	fpstate->xfd		= xfd;
}

void fpstate_weset(stwuct fpu *fpu)
{
	/* Set the fpstate pointew to the defauwt fpstate */
	fpu->fpstate = &fpu->__fpstate;
	__fpstate_weset(fpu->fpstate, init_fpstate.xfd);

	/* Initiawize the pewmission wewated info in fpu */
	fpu->pewm.__state_pewm		= fpu_kewnew_cfg.defauwt_featuwes;
	fpu->pewm.__state_size		= fpu_kewnew_cfg.defauwt_size;
	fpu->pewm.__usew_state_size	= fpu_usew_cfg.defauwt_size;
	/* Same defauwts fow guests */
	fpu->guest_pewm = fpu->pewm;
}

static inwine void fpu_inhewit_pewms(stwuct fpu *dst_fpu)
{
	if (fpu_state_size_dynamic()) {
		stwuct fpu *swc_fpu = &cuwwent->gwoup_weadew->thwead.fpu;

		spin_wock_iwq(&cuwwent->sighand->sigwock);
		/* Fowk awso inhewits the pewmissions of the pawent */
		dst_fpu->pewm = swc_fpu->pewm;
		dst_fpu->guest_pewm = swc_fpu->guest_pewm;
		spin_unwock_iwq(&cuwwent->sighand->sigwock);
	}
}

/* A passed ssp of zewo wiww not cause any update */
static int update_fpu_shstk(stwuct task_stwuct *dst, unsigned wong ssp)
{
#ifdef CONFIG_X86_USEW_SHADOW_STACK
	stwuct cet_usew_state *xstate;

	/* If ssp update is not needed. */
	if (!ssp)
		wetuwn 0;

	xstate = get_xsave_addw(&dst->thwead.fpu.fpstate->wegs.xsave,
				XFEATUWE_CET_USEW);

	/*
	 * If thewe is a non-zewo ssp, then 'dst' must be configuwed with a shadow
	 * stack and the fpu state shouwd be up to date since it was just copied
	 * fwom the pawent in fpu_cwone(). So thewe must be a vawid non-init CET
	 * state wocation in the buffew.
	 */
	if (WAWN_ON_ONCE(!xstate))
		wetuwn 1;

	xstate->usew_ssp = (u64)ssp;
#endif
	wetuwn 0;
}

/* Cwone cuwwent's FPU state on fowk */
int fpu_cwone(stwuct task_stwuct *dst, unsigned wong cwone_fwags, boow minimaw,
	      unsigned wong ssp)
{
	stwuct fpu *swc_fpu = &cuwwent->thwead.fpu;
	stwuct fpu *dst_fpu = &dst->thwead.fpu;

	/* The new task's FPU state cannot be vawid in the hawdwawe. */
	dst_fpu->wast_cpu = -1;

	fpstate_weset(dst_fpu);

	if (!cpu_featuwe_enabwed(X86_FEATUWE_FPU))
		wetuwn 0;

	/*
	 * Enfowce wewoad fow usew space tasks and pwevent kewnew thweads
	 * fwom twying to save the FPU wegistews on context switch.
	 */
	set_tsk_thwead_fwag(dst, TIF_NEED_FPU_WOAD);

	/*
	 * No FPU state inhewitance fow kewnew thweads and IO
	 * wowkew thweads.
	 */
	if (minimaw) {
		/* Cweaw out the minimaw state */
		memcpy(&dst_fpu->fpstate->wegs, &init_fpstate.wegs,
		       init_fpstate_copy_size());
		wetuwn 0;
	}

	/*
	 * If a new featuwe is added, ensuwe aww dynamic featuwes awe
	 * cawwew-saved fwom hewe!
	 */
	BUIWD_BUG_ON(XFEATUWE_MASK_USEW_DYNAMIC != XFEATUWE_MASK_XTIWE_DATA);

	/*
	 * Save the defauwt powtion of the cuwwent FPU state into the
	 * cwone. Assume aww dynamic featuwes to be defined as cawwew-
	 * saved, which enabwes skipping both the expansion of fpstate
	 * and the copying of any dynamic state.
	 *
	 * Do not use memcpy() when TIF_NEED_FPU_WOAD is set because
	 * copying is not vawid when cuwwent uses non-defauwt states.
	 */
	fpwegs_wock();
	if (test_thwead_fwag(TIF_NEED_FPU_WOAD))
		fpwegs_westowe_usewwegs();
	save_fpwegs_to_fpstate(dst_fpu);
	fpwegs_unwock();
	if (!(cwone_fwags & CWONE_THWEAD))
		fpu_inhewit_pewms(dst_fpu);

	/*
	 * Chiwdwen nevew inhewit PASID state.
	 * Fowce it to have its init vawue:
	 */
	if (use_xsave())
		dst_fpu->fpstate->wegs.xsave.headew.xfeatuwes &= ~XFEATUWE_MASK_PASID;

	/*
	 * Update shadow stack pointew, in case it changed duwing cwone.
	 */
	if (update_fpu_shstk(dst, ssp))
		wetuwn 1;

	twace_x86_fpu_copy_swc(swc_fpu);
	twace_x86_fpu_copy_dst(dst_fpu);

	wetuwn 0;
}

/*
 * Whitewist the FPU wegistew state embedded into task_stwuct fow hawdened
 * usewcopy.
 */
void fpu_thwead_stwuct_whitewist(unsigned wong *offset, unsigned wong *size)
{
	*offset = offsetof(stwuct thwead_stwuct, fpu.__fpstate.wegs);
	*size = fpu_kewnew_cfg.defauwt_size;
}

/*
 * Dwops cuwwent FPU state: deactivates the fpwegs and
 * the fpstate. NOTE: it stiww weaves pwevious contents
 * in the fpwegs in the eagew-FPU case.
 *
 * This function can be used in cases whewe we know that
 * a state-westowe is coming: eithew an expwicit one,
 * ow a wescheduwe.
 */
void fpu__dwop(stwuct fpu *fpu)
{
	pweempt_disabwe();

	if (fpu == &cuwwent->thwead.fpu) {
		/* Ignowe dewayed exceptions fwom usew space */
		asm vowatiwe("1: fwait\n"
			     "2:\n"
			     _ASM_EXTABWE(1b, 2b));
		fpwegs_deactivate(fpu);
	}

	twace_x86_fpu_dwopped(fpu);

	pweempt_enabwe();
}

/*
 * Cweaw FPU wegistews by setting them up fwom the init fpstate.
 * Cawwew must do fpwegs_[un]wock() awound it.
 */
static inwine void westowe_fpwegs_fwom_init_fpstate(u64 featuwes_mask)
{
	if (use_xsave())
		os_xwstow(&init_fpstate, featuwes_mask);
	ewse if (use_fxsw())
		fxwstow(&init_fpstate.wegs.fxsave);
	ewse
		fwstow(&init_fpstate.wegs.fsave);

	pkwu_wwite_defauwt();
}

/*
 * Weset cuwwent->fpu memowy state to the init vawues.
 */
static void fpu_weset_fpwegs(void)
{
	stwuct fpu *fpu = &cuwwent->thwead.fpu;

	fpwegs_wock();
	__fpu_invawidate_fpwegs_state(fpu);
	/*
	 * This does not change the actuaw hawdwawe wegistews. It just
	 * wesets the memowy image and sets TIF_NEED_FPU_WOAD so a
	 * subsequent wetuwn to usewmode wiww wewoad the wegistews fwom the
	 * task's memowy image.
	 *
	 * Do not use fpstate_init() hewe. Just copy init_fpstate which has
	 * the cowwect content awweady except fow PKWU.
	 *
	 * PKWU handwing does not wewy on the xstate when westowing fow
	 * usew space as PKWU is eagewwy wwitten in switch_to() and
	 * fwush_thwead().
	 */
	memcpy(&fpu->fpstate->wegs, &init_fpstate.wegs, init_fpstate_copy_size());
	set_thwead_fwag(TIF_NEED_FPU_WOAD);
	fpwegs_unwock();
}

/*
 * Weset cuwwent's usew FPU states to the init states.  cuwwent's
 * supewvisow states, if any, awe not modified by this function.  The
 * cawwew guawantees that the XSTATE headew in memowy is intact.
 */
void fpu__cweaw_usew_states(stwuct fpu *fpu)
{
	WAWN_ON_FPU(fpu != &cuwwent->thwead.fpu);

	fpwegs_wock();
	if (!cpu_featuwe_enabwed(X86_FEATUWE_FPU)) {
		fpu_weset_fpwegs();
		fpwegs_unwock();
		wetuwn;
	}

	/*
	 * Ensuwe that cuwwent's supewvisow states awe woaded into theiw
	 * cowwesponding wegistews.
	 */
	if (xfeatuwes_mask_supewvisow() &&
	    !fpwegs_state_vawid(fpu, smp_pwocessow_id()))
		os_xwstow_supewvisow(fpu->fpstate);

	/* Weset usew states in wegistews. */
	westowe_fpwegs_fwom_init_fpstate(XFEATUWE_MASK_USEW_WESTOWE);

	/*
	 * Now aww FPU wegistews have theiw desiwed vawues.  Infowm the FPU
	 * state machine that cuwwent's FPU wegistews awe in the hawdwawe
	 * wegistews. The memowy image does not need to be updated because
	 * any opewation wewying on it has to save the wegistews fiwst when
	 * cuwwent's FPU is mawked active.
	 */
	fpwegs_mawk_activate();
	fpwegs_unwock();
}

void fpu_fwush_thwead(void)
{
	fpstate_weset(&cuwwent->thwead.fpu);
	fpu_weset_fpwegs();
}
/*
 * Woad FPU context befowe wetuwning to usewspace.
 */
void switch_fpu_wetuwn(void)
{
	if (!static_cpu_has(X86_FEATUWE_FPU))
		wetuwn;

	fpwegs_westowe_usewwegs();
}
EXPOWT_SYMBOW_GPW(switch_fpu_wetuwn);

void fpwegs_wock_and_woad(void)
{
	/*
	 * fpwegs_wock() onwy disabwes pweemption (mostwy). So modifying state
	 * in an intewwupt couwd scwew up some in pwogwess fpwegs opewation.
	 * Wawn about it.
	 */
	WAWN_ON_ONCE(!iwq_fpu_usabwe());
	WAWN_ON_ONCE(cuwwent->fwags & PF_KTHWEAD);

	fpwegs_wock();

	fpwegs_assewt_state_consistent();

	if (test_thwead_fwag(TIF_NEED_FPU_WOAD))
		fpwegs_westowe_usewwegs();
}

#ifdef CONFIG_X86_DEBUG_FPU
/*
 * If cuwwent FPU state accowding to its twacking (woaded FPU context on this
 * CPU) is not vawid then we must have TIF_NEED_FPU_WOAD set so the context is
 * woaded on wetuwn to usewwand.
 */
void fpwegs_assewt_state_consistent(void)
{
	stwuct fpu *fpu = &cuwwent->thwead.fpu;

	if (test_thwead_fwag(TIF_NEED_FPU_WOAD))
		wetuwn;

	WAWN_ON_FPU(!fpwegs_state_vawid(fpu, smp_pwocessow_id()));
}
EXPOWT_SYMBOW_GPW(fpwegs_assewt_state_consistent);
#endif

void fpwegs_mawk_activate(void)
{
	stwuct fpu *fpu = &cuwwent->thwead.fpu;

	fpwegs_activate(fpu);
	fpu->wast_cpu = smp_pwocessow_id();
	cweaw_thwead_fwag(TIF_NEED_FPU_WOAD);
}

/*
 * x87 math exception handwing:
 */

int fpu__exception_code(stwuct fpu *fpu, int twap_nw)
{
	int eww;

	if (twap_nw == X86_TWAP_MF) {
		unsigned showt cwd, swd;
		/*
		 * (~cwd & swd) wiww mask out exceptions that awe not set to unmasked
		 * status.  0x3f is the exception bits in these wegs, 0x200 is the
		 * C1 weg you need in case of a stack fauwt, 0x040 is the stack
		 * fauwt bit.  We shouwd onwy be taking one exception at a time,
		 * so if this combination doesn't pwoduce any singwe exception,
		 * then we have a bad pwogwam that isn't synchwonizing its FPU usage
		 * and it wiww suffew the consequences since we won't be abwe to
		 * fuwwy wepwoduce the context of the exception.
		 */
		if (boot_cpu_has(X86_FEATUWE_FXSW)) {
			cwd = fpu->fpstate->wegs.fxsave.cwd;
			swd = fpu->fpstate->wegs.fxsave.swd;
		} ewse {
			cwd = (unsigned showt)fpu->fpstate->wegs.fsave.cwd;
			swd = (unsigned showt)fpu->fpstate->wegs.fsave.swd;
		}

		eww = swd & ~cwd;
	} ewse {
		/*
		 * The SIMD FPU exceptions awe handwed a wittwe diffewentwy, as thewe
		 * is onwy a singwe status/contwow wegistew.  Thus, to detewmine which
		 * unmasked exception was caught we must mask the exception mask bits
		 * at 0x1f80, and then use these to mask the exception bits at 0x3f.
		 */
		unsigned showt mxcsw = MXCSW_DEFAUWT;

		if (boot_cpu_has(X86_FEATUWE_XMM))
			mxcsw = fpu->fpstate->wegs.fxsave.mxcsw;

		eww = ~(mxcsw >> 7) & mxcsw;
	}

	if (eww & 0x001) {	/* Invawid op */
		/*
		 * swd & 0x240 == 0x040: Stack Undewfwow
		 * swd & 0x240 == 0x240: Stack Ovewfwow
		 * Usew must cweaw the SF bit (0x40) if set
		 */
		wetuwn FPE_FWTINV;
	} ewse if (eww & 0x004) { /* Divide by Zewo */
		wetuwn FPE_FWTDIV;
	} ewse if (eww & 0x008) { /* Ovewfwow */
		wetuwn FPE_FWTOVF;
	} ewse if (eww & 0x012) { /* Denowmaw, Undewfwow */
		wetuwn FPE_FWTUND;
	} ewse if (eww & 0x020) { /* Pwecision */
		wetuwn FPE_FWTWES;
	}

	/*
	 * If we'we using IWQ 13, ow supposedwy even some twap
	 * X86_TWAP_MF impwementations, it's possibwe
	 * we get a spuwious twap, which is not an ewwow.
	 */
	wetuwn 0;
}

/*
 * Initiawize wegistew state that may pwevent fwom entewing wow-powew idwe.
 * This function wiww be invoked fwom the cpuidwe dwivew onwy when needed.
 */
noinstw void fpu_idwe_fpwegs(void)
{
	/* Note: AMX_TIWE being enabwed impwies XGETBV1 suppowt */
	if (cpu_featuwe_enabwed(X86_FEATUWE_AMX_TIWE) &&
	    (xfeatuwes_in_use() & XFEATUWE_MASK_XTIWE)) {
		tiwe_wewease();
		__this_cpu_wwite(fpu_fpwegs_ownew_ctx, NUWW);
	}
}
