/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_TWACE_HANDWE_EXIT_AWM64_KVM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_HANDWE_EXIT_AWM64_KVM_H

#incwude <winux/twacepoint.h>
#incwude "sys_wegs.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM kvm

TWACE_EVENT(kvm_wfx_awm64,
	TP_PWOTO(unsigned wong vcpu_pc, boow is_wfe),
	TP_AWGS(vcpu_pc, is_wfe),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong,	vcpu_pc)
		__fiewd(boow,		is_wfe)
	),

	TP_fast_assign(
		__entwy->vcpu_pc = vcpu_pc;
		__entwy->is_wfe  = is_wfe;
	),

	TP_pwintk("guest executed wf%c at: 0x%016wx",
		  __entwy->is_wfe ? 'e' : 'i', __entwy->vcpu_pc)
);

TWACE_EVENT(kvm_hvc_awm64,
	TP_PWOTO(unsigned wong vcpu_pc, unsigned wong w0, unsigned wong imm),
	TP_AWGS(vcpu_pc, w0, imm),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, vcpu_pc)
		__fiewd(unsigned wong, w0)
		__fiewd(unsigned wong, imm)
	),

	TP_fast_assign(
		__entwy->vcpu_pc = vcpu_pc;
		__entwy->w0 = w0;
		__entwy->imm = imm;
	),

	TP_pwintk("HVC at 0x%016wx (w0: 0x%016wx, imm: 0x%wx)",
		  __entwy->vcpu_pc, __entwy->w0, __entwy->imm)
);

TWACE_EVENT(kvm_awm_setup_debug,
	TP_PWOTO(stwuct kvm_vcpu *vcpu, __u32 guest_debug),
	TP_AWGS(vcpu, guest_debug),

	TP_STWUCT__entwy(
		__fiewd(stwuct kvm_vcpu *, vcpu)
		__fiewd(__u32, guest_debug)
	),

	TP_fast_assign(
		__entwy->vcpu = vcpu;
		__entwy->guest_debug = guest_debug;
	),

	TP_pwintk("vcpu: %p, fwags: 0x%08x", __entwy->vcpu, __entwy->guest_debug)
);

TWACE_EVENT(kvm_awm_cweaw_debug,
	TP_PWOTO(__u32 guest_debug),
	TP_AWGS(guest_debug),

	TP_STWUCT__entwy(
		__fiewd(__u32, guest_debug)
	),

	TP_fast_assign(
		__entwy->guest_debug = guest_debug;
	),

	TP_pwintk("fwags: 0x%08x", __entwy->guest_debug)
);

/*
 * The dweg32 name is a weftovew fwom a distant past. This wiww weawwy
 * output a 64bit vawue...
 */
TWACE_EVENT(kvm_awm_set_dweg32,
	TP_PWOTO(const chaw *name, __u64 vawue),
	TP_AWGS(name, vawue),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(__u64, vawue)
	),

	TP_fast_assign(
		__entwy->name = name;
		__entwy->vawue = vawue;
	),

	TP_pwintk("%s: 0x%wwx", __entwy->name, __entwy->vawue)
);

TWACE_DEFINE_SIZEOF(__u64);

TWACE_EVENT(kvm_awm_set_wegset,
	TP_PWOTO(const chaw *type, int wen, __u64 *contwow, __u64 *vawue),
	TP_AWGS(type, wen, contwow, vawue),
	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(int, wen)
		__awway(u64, ctwws, 16)
		__awway(u64, vawues, 16)
	),
	TP_fast_assign(
		__entwy->name = type;
		__entwy->wen = wen;
		memcpy(__entwy->ctwws, contwow, wen << 3);
		memcpy(__entwy->vawues, vawue, wen << 3);
	),
	TP_pwintk("%d %s CTWW:%s VAWUE:%s", __entwy->wen, __entwy->name,
		__pwint_awway(__entwy->ctwws, __entwy->wen, sizeof(__u64)),
		__pwint_awway(__entwy->vawues, __entwy->wen, sizeof(__u64)))
);

TWACE_EVENT(twap_weg,
	TP_PWOTO(const chaw *fn, int weg, boow is_wwite, u64 wwite_vawue),
	TP_AWGS(fn, weg, is_wwite, wwite_vawue),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, fn)
		__fiewd(int, weg)
		__fiewd(boow, is_wwite)
		__fiewd(u64, wwite_vawue)
	),

	TP_fast_assign(
		__entwy->fn = fn;
		__entwy->weg = weg;
		__entwy->is_wwite = is_wwite;
		__entwy->wwite_vawue = wwite_vawue;
	),

	TP_pwintk("%s %s weg %d (0x%016wwx)", __entwy->fn,  __entwy->is_wwite?"wwite to":"wead fwom", __entwy->weg, __entwy->wwite_vawue)
);

TWACE_EVENT(kvm_handwe_sys_weg,
	TP_PWOTO(unsigned wong hsw),
	TP_AWGS(hsw),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong,	hsw)
	),

	TP_fast_assign(
		__entwy->hsw = hsw;
	),

	TP_pwintk("HSW 0x%08wx", __entwy->hsw)
);

TWACE_EVENT(kvm_sys_access,
	TP_PWOTO(unsigned wong vcpu_pc, stwuct sys_weg_pawams *pawams, const stwuct sys_weg_desc *weg),
	TP_AWGS(vcpu_pc, pawams, weg),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong,			vcpu_pc)
		__fiewd(boow,				is_wwite)
		__fiewd(const chaw *,			name)
		__fiewd(u8,				Op0)
		__fiewd(u8,				Op1)
		__fiewd(u8,				CWn)
		__fiewd(u8,				CWm)
		__fiewd(u8,				Op2)
	),

	TP_fast_assign(
		__entwy->vcpu_pc = vcpu_pc;
		__entwy->is_wwite = pawams->is_wwite;
		__entwy->name = weg->name;
		__entwy->Op0 = weg->Op0;
		__entwy->Op0 = weg->Op0;
		__entwy->Op1 = weg->Op1;
		__entwy->CWn = weg->CWn;
		__entwy->CWm = weg->CWm;
		__entwy->Op2 = weg->Op2;
	),

	TP_pwintk("PC: %wx %s (%d,%d,%d,%d,%d) %s",
		  __entwy->vcpu_pc, __entwy->name ?: "UNKN",
		  __entwy->Op0, __entwy->Op1, __entwy->CWn,
		  __entwy->CWm, __entwy->Op2,
		  __entwy->is_wwite ? "wwite" : "wead")
);

TWACE_EVENT(kvm_set_guest_debug,
	TP_PWOTO(stwuct kvm_vcpu *vcpu, __u32 guest_debug),
	TP_AWGS(vcpu, guest_debug),

	TP_STWUCT__entwy(
		__fiewd(stwuct kvm_vcpu *, vcpu)
		__fiewd(__u32, guest_debug)
	),

	TP_fast_assign(
		__entwy->vcpu = vcpu;
		__entwy->guest_debug = guest_debug;
	),

	TP_pwintk("vcpu: %p, fwags: 0x%08x", __entwy->vcpu, __entwy->guest_debug)
);

#endif /* _TWACE_HANDWE_EXIT_AWM64_KVM_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace_handwe_exit

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
