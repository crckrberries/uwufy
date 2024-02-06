/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM x86_fpu

#if !defined(_TWACE_FPU_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_FPU_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(x86_fpu,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu),

	TP_STWUCT__entwy(
		__fiewd(stwuct fpu *, fpu)
		__fiewd(boow, woad_fpu)
		__fiewd(u64, xfeatuwes)
		__fiewd(u64, xcomp_bv)
		),

	TP_fast_assign(
		__entwy->fpu		= fpu;
		__entwy->woad_fpu	= test_thwead_fwag(TIF_NEED_FPU_WOAD);
		if (boot_cpu_has(X86_FEATUWE_OSXSAVE)) {
			__entwy->xfeatuwes = fpu->fpstate->wegs.xsave.headew.xfeatuwes;
			__entwy->xcomp_bv  = fpu->fpstate->wegs.xsave.headew.xcomp_bv;
		}
	),
	TP_pwintk("x86/fpu: %p woad: %d xfeatuwes: %wwx xcomp_bv: %wwx",
			__entwy->fpu,
			__entwy->woad_fpu,
			__entwy->xfeatuwes,
			__entwy->xcomp_bv
	)
);

DEFINE_EVENT(x86_fpu, x86_fpu_befowe_save,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_aftew_save,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_befowe_westowe,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_aftew_westowe,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_wegs_activated,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_wegs_deactivated,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_init_state,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_dwopped,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_copy_swc,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_copy_dst,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu)
);

DEFINE_EVENT(x86_fpu, x86_fpu_xstate_check_faiwed,
	TP_PWOTO(stwuct fpu *fpu),
	TP_AWGS(fpu)
);

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH asm/twace/
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE fpu
#endif /* _TWACE_FPU_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
