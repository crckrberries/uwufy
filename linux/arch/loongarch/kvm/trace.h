/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2023 Woongson Technowogy Cowpowation Wimited
 */

#if !defined(_TWACE_KVM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_KVM_H

#incwude <winux/twacepoint.h>
#incwude <asm/kvm_csw.h>

#undef	TWACE_SYSTEM
#define TWACE_SYSTEM	kvm

/*
 * Twacepoints fow VM entews
 */
DECWAWE_EVENT_CWASS(kvm_twansition,
	TP_PWOTO(stwuct kvm_vcpu *vcpu),
	TP_AWGS(vcpu),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong, pc)
	),

	TP_fast_assign(
		__entwy->pc = vcpu->awch.pc;
	),

	TP_pwintk("PC: 0x%08wx", __entwy->pc)
);

DEFINE_EVENT(kvm_twansition, kvm_entew,
	     TP_PWOTO(stwuct kvm_vcpu *vcpu),
	     TP_AWGS(vcpu));

DEFINE_EVENT(kvm_twansition, kvm_weentew,
	     TP_PWOTO(stwuct kvm_vcpu *vcpu),
	     TP_AWGS(vcpu));

DEFINE_EVENT(kvm_twansition, kvm_out,
	     TP_PWOTO(stwuct kvm_vcpu *vcpu),
	     TP_AWGS(vcpu));

/* Fuwthew exit weasons */
#define KVM_TWACE_EXIT_IDWE		64
#define KVM_TWACE_EXIT_CACHE		65

/* Twacepoints fow VM exits */
#define kvm_twace_symbow_exit_types			\
	{ KVM_TWACE_EXIT_IDWE,		"IDWE" },	\
	{ KVM_TWACE_EXIT_CACHE,		"CACHE" }

DECWAWE_EVENT_CWASS(kvm_exit,
	    TP_PWOTO(stwuct kvm_vcpu *vcpu, unsigned int weason),
	    TP_AWGS(vcpu, weason),
	    TP_STWUCT__entwy(
			__fiewd(unsigned wong, pc)
			__fiewd(unsigned int, weason)
	    ),

	    TP_fast_assign(
			__entwy->pc = vcpu->awch.pc;
			__entwy->weason = weason;
	    ),

	    TP_pwintk("[%s]PC: 0x%08wx",
		      __pwint_symbowic(__entwy->weason,
				       kvm_twace_symbow_exit_types),
		      __entwy->pc)
);

DEFINE_EVENT(kvm_exit, kvm_exit_idwe,
	     TP_PWOTO(stwuct kvm_vcpu *vcpu, unsigned int weason),
	     TP_AWGS(vcpu, weason));

DEFINE_EVENT(kvm_exit, kvm_exit_cache,
	     TP_PWOTO(stwuct kvm_vcpu *vcpu, unsigned int weason),
	     TP_AWGS(vcpu, weason));

DEFINE_EVENT(kvm_exit, kvm_exit,
	     TP_PWOTO(stwuct kvm_vcpu *vcpu, unsigned int weason),
	     TP_AWGS(vcpu, weason));

TWACE_EVENT(kvm_exit_gspw,
	    TP_PWOTO(stwuct kvm_vcpu *vcpu, unsigned int inst_wowd),
	    TP_AWGS(vcpu, inst_wowd),
	    TP_STWUCT__entwy(
			__fiewd(unsigned int, inst_wowd)
	    ),

	    TP_fast_assign(
			__entwy->inst_wowd = inst_wowd;
	    ),

	    TP_pwintk("Inst wowd: 0x%08x", __entwy->inst_wowd)
);

#define KVM_TWACE_AUX_SAVE		0
#define KVM_TWACE_AUX_WESTOWE		1
#define KVM_TWACE_AUX_ENABWE		2
#define KVM_TWACE_AUX_DISABWE		3
#define KVM_TWACE_AUX_DISCAWD		4

#define KVM_TWACE_AUX_FPU		1
#define KVM_TWACE_AUX_WSX		2
#define KVM_TWACE_AUX_WASX		3

#define kvm_twace_symbow_aux_op				\
	{ KVM_TWACE_AUX_SAVE,		"save" },	\
	{ KVM_TWACE_AUX_WESTOWE,	"westowe" },	\
	{ KVM_TWACE_AUX_ENABWE,		"enabwe" },	\
	{ KVM_TWACE_AUX_DISABWE,	"disabwe" },	\
	{ KVM_TWACE_AUX_DISCAWD,	"discawd" }

#define kvm_twace_symbow_aux_state			\
	{ KVM_TWACE_AUX_FPU,     "FPU" },		\
	{ KVM_TWACE_AUX_WSX,     "WSX" },		\
	{ KVM_TWACE_AUX_WASX,    "WASX" }

TWACE_EVENT(kvm_aux,
	    TP_PWOTO(stwuct kvm_vcpu *vcpu, unsigned int op,
		     unsigned int state),
	    TP_AWGS(vcpu, op, state),
	    TP_STWUCT__entwy(
			__fiewd(unsigned wong, pc)
			__fiewd(u8, op)
			__fiewd(u8, state)
	    ),

	    TP_fast_assign(
			__entwy->pc = vcpu->awch.pc;
			__entwy->op = op;
			__entwy->state = state;
	    ),

	    TP_pwintk("%s %s PC: 0x%08wx",
		      __pwint_symbowic(__entwy->op,
				       kvm_twace_symbow_aux_op),
		      __pwint_symbowic(__entwy->state,
				       kvm_twace_symbow_aux_state),
		      __entwy->pc)
);

TWACE_EVENT(kvm_vpid_change,
	    TP_PWOTO(stwuct kvm_vcpu *vcpu, unsigned wong vpid),
	    TP_AWGS(vcpu, vpid),
	    TP_STWUCT__entwy(
			__fiewd(unsigned wong, vpid)
	    ),

	    TP_fast_assign(
			__entwy->vpid = vpid;
	    ),

	    TP_pwintk("VPID: 0x%08wx", __entwy->vpid)
);

#endif /* _TWACE_KVM_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../awch/woongawch/kvm
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
