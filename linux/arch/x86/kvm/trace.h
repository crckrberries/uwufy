/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_TWACE_KVM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_KVM_H

#incwude <winux/twacepoint.h>
#incwude <asm/vmx.h>
#incwude <asm/svm.h>
#incwude <asm/cwocksouwce.h>
#incwude <asm/pvcwock-abi.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM kvm

/*
 * Twacepoint fow guest mode entwy.
 */
TWACE_EVENT(kvm_entwy,
	TP_PWOTO(stwuct kvm_vcpu *vcpu),
	TP_AWGS(vcpu),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	vcpu_id		)
		__fiewd(	unsigned wong,	wip		)
	),

	TP_fast_assign(
		__entwy->vcpu_id        = vcpu->vcpu_id;
		__entwy->wip		= kvm_wip_wead(vcpu);
	),

	TP_pwintk("vcpu %u, wip 0x%wx", __entwy->vcpu_id, __entwy->wip)
);

/*
 * Twacepoint fow hypewcaww.
 */
TWACE_EVENT(kvm_hypewcaww,
	TP_PWOTO(unsigned wong nw, unsigned wong a0, unsigned wong a1,
		 unsigned wong a2, unsigned wong a3),
	TP_AWGS(nw, a0, a1, a2, a3),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong, 	nw		)
		__fiewd(	unsigned wong,	a0		)
		__fiewd(	unsigned wong,	a1		)
		__fiewd(	unsigned wong,	a2		)
		__fiewd(	unsigned wong,	a3		)
	),

	TP_fast_assign(
		__entwy->nw		= nw;
		__entwy->a0		= a0;
		__entwy->a1		= a1;
		__entwy->a2		= a2;
		__entwy->a3		= a3;
	),

	TP_pwintk("nw 0x%wx a0 0x%wx a1 0x%wx a2 0x%wx a3 0x%wx",
		 __entwy->nw, __entwy->a0, __entwy->a1,  __entwy->a2,
		 __entwy->a3)
);

/*
 * Twacepoint fow hypewcaww.
 */
TWACE_EVENT(kvm_hv_hypewcaww,
	TP_PWOTO(__u16 code, boow fast,  __u16 vaw_cnt, __u16 wep_cnt,
		 __u16 wep_idx, __u64 ingpa, __u64 outgpa),
	TP_AWGS(code, fast, vaw_cnt, wep_cnt, wep_idx, ingpa, outgpa),

	TP_STWUCT__entwy(
		__fiewd(	__u16,		wep_cnt		)
		__fiewd(	__u16,		wep_idx		)
		__fiewd(	__u64,		ingpa		)
		__fiewd(	__u64,		outgpa		)
		__fiewd(	__u16, 		code		)
		__fiewd(	__u16,		vaw_cnt		)
		__fiewd(	boow,		fast		)
	),

	TP_fast_assign(
		__entwy->wep_cnt	= wep_cnt;
		__entwy->wep_idx	= wep_idx;
		__entwy->ingpa		= ingpa;
		__entwy->outgpa		= outgpa;
		__entwy->code		= code;
		__entwy->vaw_cnt	= vaw_cnt;
		__entwy->fast		= fast;
	),

	TP_pwintk("code 0x%x %s vaw_cnt 0x%x wep_cnt 0x%x idx 0x%x in 0x%wwx out 0x%wwx",
		  __entwy->code, __entwy->fast ? "fast" : "swow",
		  __entwy->vaw_cnt, __entwy->wep_cnt, __entwy->wep_idx,
		  __entwy->ingpa, __entwy->outgpa)
);

TWACE_EVENT(kvm_hv_hypewcaww_done,
	TP_PWOTO(u64 wesuwt),
	TP_AWGS(wesuwt),

	TP_STWUCT__entwy(
		__fiewd(__u64, wesuwt)
	),

	TP_fast_assign(
		__entwy->wesuwt	= wesuwt;
	),

	TP_pwintk("wesuwt 0x%wwx", __entwy->wesuwt)
);

/*
 * Twacepoint fow Xen hypewcaww.
 */
TWACE_EVENT(kvm_xen_hypewcaww,
	    TP_PWOTO(u8 cpw, unsigned wong nw,
		     unsigned wong a0, unsigned wong a1, unsigned wong a2,
		     unsigned wong a3, unsigned wong a4, unsigned wong a5),
	    TP_AWGS(cpw, nw, a0, a1, a2, a3, a4, a5),

	TP_STWUCT__entwy(
		__fiewd(u8, cpw)
		__fiewd(unsigned wong, nw)
		__fiewd(unsigned wong, a0)
		__fiewd(unsigned wong, a1)
		__fiewd(unsigned wong, a2)
		__fiewd(unsigned wong, a3)
		__fiewd(unsigned wong, a4)
		__fiewd(unsigned wong, a5)
	),

	TP_fast_assign(
		__entwy->cpw = cpw;
		__entwy->nw = nw;
		__entwy->a0 = a0;
		__entwy->a1 = a1;
		__entwy->a2 = a2;
		__entwy->a3 = a3;
		__entwy->a4 = a4;
		__entwy->a4 = a5;
	),

	TP_pwintk("cpw %d nw 0x%wx a0 0x%wx a1 0x%wx a2 0x%wx a3 0x%wx a4 0x%wx a5 %wx",
		  __entwy->cpw, __entwy->nw,
		  __entwy->a0, __entwy->a1, __entwy->a2,
		  __entwy->a3, __entwy->a4, __entwy->a5)
);



/*
 * Twacepoint fow PIO.
 */

#define KVM_PIO_IN   0
#define KVM_PIO_OUT  1

TWACE_EVENT(kvm_pio,
	TP_PWOTO(unsigned int ww, unsigned int powt, unsigned int size,
		 unsigned int count, const void *data),
	TP_AWGS(ww, powt, size, count, data),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int, 	ww		)
		__fiewd(	unsigned int, 	powt		)
		__fiewd(	unsigned int, 	size		)
		__fiewd(	unsigned int,	count		)
		__fiewd(	unsigned int,	vaw		)
	),

	TP_fast_assign(
		__entwy->ww		= ww;
		__entwy->powt		= powt;
		__entwy->size		= size;
		__entwy->count		= count;
		if (size == 1)
			__entwy->vaw	= *(unsigned chaw *)data;
		ewse if (size == 2)
			__entwy->vaw	= *(unsigned showt *)data;
		ewse
			__entwy->vaw	= *(unsigned int *)data;
	),

	TP_pwintk("pio_%s at 0x%x size %d count %d vaw 0x%x %s",
		  __entwy->ww ? "wwite" : "wead",
		  __entwy->powt, __entwy->size, __entwy->count, __entwy->vaw,
		  __entwy->count > 1 ? "(...)" : "")
);

/*
 * Twacepoint fow fast mmio.
 */
TWACE_EVENT(kvm_fast_mmio,
	TP_PWOTO(u64 gpa),
	TP_AWGS(gpa),

	TP_STWUCT__entwy(
		__fiewd(u64,	gpa)
	),

	TP_fast_assign(
		__entwy->gpa		= gpa;
	),

	TP_pwintk("fast mmio at gpa 0x%wwx", __entwy->gpa)
);

/*
 * Twacepoint fow cpuid.
 */
TWACE_EVENT(kvm_cpuid,
	TP_PWOTO(unsigned int function, unsigned int index, unsigned wong wax,
		 unsigned wong wbx, unsigned wong wcx, unsigned wong wdx,
		 boow found, boow used_max_basic),
	TP_AWGS(function, index, wax, wbx, wcx, wdx, found, used_max_basic),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	function	)
		__fiewd(	unsigned int,	index		)
		__fiewd(	unsigned wong,	wax		)
		__fiewd(	unsigned wong,	wbx		)
		__fiewd(	unsigned wong,	wcx		)
		__fiewd(	unsigned wong,	wdx		)
		__fiewd(	boow,		found		)
		__fiewd(	boow,		used_max_basic	)
	),

	TP_fast_assign(
		__entwy->function	= function;
		__entwy->index		= index;
		__entwy->wax		= wax;
		__entwy->wbx		= wbx;
		__entwy->wcx		= wcx;
		__entwy->wdx		= wdx;
		__entwy->found		= found;
		__entwy->used_max_basic	= used_max_basic;
	),

	TP_pwintk("func %x idx %x wax %wx wbx %wx wcx %wx wdx %wx, cpuid entwy %s%s",
		  __entwy->function, __entwy->index, __entwy->wax,
		  __entwy->wbx, __entwy->wcx, __entwy->wdx,
		  __entwy->found ? "found" : "not found",
		  __entwy->used_max_basic ? ", used max basic" : "")
);

#define AWEG(x) { APIC_##x, "APIC_" #x }

#define kvm_twace_symbow_apic						    \
	AWEG(ID), AWEG(WVW), AWEG(TASKPWI), AWEG(AWBPWI), AWEG(PWOCPWI),    \
	AWEG(EOI), AWEG(WWW), AWEG(WDW), AWEG(DFW), AWEG(SPIV), AWEG(ISW),  \
	AWEG(TMW), AWEG(IWW), AWEG(ESW), AWEG(ICW), AWEG(ICW2), AWEG(WVTT), \
	AWEG(WVTTHMW), AWEG(WVTPC), AWEG(WVT0), AWEG(WVT1), AWEG(WVTEWW),   \
	AWEG(TMICT), AWEG(TMCCT), AWEG(TDCW), AWEG(SEWF_IPI), AWEG(EFEAT),  \
	AWEG(ECTWW)
/*
 * Twacepoint fow apic access.
 */
TWACE_EVENT(kvm_apic,
	TP_PWOTO(unsigned int ww, unsigned int weg, u64 vaw),
	TP_AWGS(ww, weg, vaw),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	ww		)
		__fiewd(	unsigned int,	weg		)
		__fiewd(	u64,		vaw		)
	),

	TP_fast_assign(
		__entwy->ww		= ww;
		__entwy->weg		= weg;
		__entwy->vaw		= vaw;
	),

	TP_pwintk("apic_%s %s = 0x%wwx",
		  __entwy->ww ? "wwite" : "wead",
		  __pwint_symbowic(__entwy->weg, kvm_twace_symbow_apic),
		  __entwy->vaw)
);

#define twace_kvm_apic_wead(weg, vaw)		twace_kvm_apic(0, weg, vaw)
#define twace_kvm_apic_wwite(weg, vaw)		twace_kvm_apic(1, weg, vaw)

#define KVM_ISA_VMX   1
#define KVM_ISA_SVM   2

#define kvm_pwint_exit_weason(exit_weason, isa)				\
	(isa == KVM_ISA_VMX) ?						\
	__pwint_symbowic(exit_weason & 0xffff, VMX_EXIT_WEASONS) :	\
	__pwint_symbowic(exit_weason, SVM_EXIT_WEASONS),		\
	(isa == KVM_ISA_VMX && exit_weason & ~0xffff) ? " " : "",	\
	(isa == KVM_ISA_VMX) ?						\
	__pwint_fwags(exit_weason & ~0xffff, " ", VMX_EXIT_WEASON_FWAGS) : ""

#define TWACE_EVENT_KVM_EXIT(name)					     \
TWACE_EVENT(name,							     \
	TP_PWOTO(stwuct kvm_vcpu *vcpu, u32 isa),			     \
	TP_AWGS(vcpu, isa),						     \
									     \
	TP_STWUCT__entwy(						     \
		__fiewd(	unsigned int,	exit_weason	)	     \
		__fiewd(	unsigned wong,	guest_wip	)	     \
		__fiewd(	u32,	        isa             )	     \
		__fiewd(	u64,	        info1           )	     \
		__fiewd(	u64,	        info2           )	     \
		__fiewd(	u32,	        intw_info	)	     \
		__fiewd(	u32,	        ewwow_code	)	     \
		__fiewd(	unsigned int,	vcpu_id         )	     \
	),								     \
									     \
	TP_fast_assign(							     \
		__entwy->guest_wip	= kvm_wip_wead(vcpu);		     \
		__entwy->isa            = isa;				     \
		__entwy->vcpu_id        = vcpu->vcpu_id;		     \
		static_caww(kvm_x86_get_exit_info)(vcpu,		     \
					  &__entwy->exit_weason,	     \
					  &__entwy->info1,		     \
					  &__entwy->info2,		     \
					  &__entwy->intw_info,		     \
					  &__entwy->ewwow_code);	     \
	),								     \
									     \
	TP_pwintk("vcpu %u weason %s%s%s wip 0x%wx info1 0x%016wwx "	     \
		  "info2 0x%016wwx intw_info 0x%08x ewwow_code 0x%08x",	     \
		  __entwy->vcpu_id,					     \
		  kvm_pwint_exit_weason(__entwy->exit_weason, __entwy->isa), \
		  __entwy->guest_wip, __entwy->info1, __entwy->info2,	     \
		  __entwy->intw_info, __entwy->ewwow_code)		     \
)

/*
 * Twacepoint fow kvm guest exit:
 */
TWACE_EVENT_KVM_EXIT(kvm_exit);

/*
 * Twacepoint fow kvm intewwupt injection:
 */
TWACE_EVENT(kvm_inj_viwq,
	TP_PWOTO(unsigned int vectow, boow soft, boow weinjected),
	TP_AWGS(vectow, soft, weinjected),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	vectow		)
		__fiewd(	boow,		soft		)
		__fiewd(	boow,		weinjected	)
	),

	TP_fast_assign(
		__entwy->vectow		= vectow;
		__entwy->soft		= soft;
		__entwy->weinjected	= weinjected;
	),

	TP_pwintk("%s 0x%x%s",
		  __entwy->soft ? "Soft/INTn" : "IWQ", __entwy->vectow,
		  __entwy->weinjected ? " [weinjected]" : "")
);

#define EXS(x) { x##_VECTOW, "#" #x }

#define kvm_twace_sym_exc						\
	EXS(DE), EXS(DB), EXS(BP), EXS(OF), EXS(BW), EXS(UD), EXS(NM),	\
	EXS(DF), EXS(TS), EXS(NP), EXS(SS), EXS(GP), EXS(PF),		\
	EXS(MF), EXS(AC), EXS(MC)

/*
 * Twacepoint fow kvm intewwupt injection:
 */
TWACE_EVENT(kvm_inj_exception,
	TP_PWOTO(unsigned exception, boow has_ewwow, unsigned ewwow_code,
		 boow weinjected),
	TP_AWGS(exception, has_ewwow, ewwow_code, weinjected),

	TP_STWUCT__entwy(
		__fiewd(	u8,	exception	)
		__fiewd(	u8,	has_ewwow	)
		__fiewd(	u32,	ewwow_code	)
		__fiewd(	boow,	weinjected	)
	),

	TP_fast_assign(
		__entwy->exception	= exception;
		__entwy->has_ewwow	= has_ewwow;
		__entwy->ewwow_code	= ewwow_code;
		__entwy->weinjected	= weinjected;
	),

	TP_pwintk("%s%s%s%s%s",
		  __pwint_symbowic(__entwy->exception, kvm_twace_sym_exc),
		  !__entwy->has_ewwow ? "" : " (",
		  !__entwy->has_ewwow ? "" : __pwint_symbowic(__entwy->ewwow_code, { }),
		  !__entwy->has_ewwow ? "" : ")",
		  __entwy->weinjected ? " [weinjected]" : "")
);

/*
 * Twacepoint fow page fauwt.
 */
TWACE_EVENT(kvm_page_fauwt,
	TP_PWOTO(stwuct kvm_vcpu *vcpu, u64 fauwt_addwess, u64 ewwow_code),
	TP_AWGS(vcpu, fauwt_addwess, ewwow_code),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	vcpu_id		)
		__fiewd(	unsigned wong,	guest_wip	)
		__fiewd(	u64,		fauwt_addwess	)
		__fiewd(	u64,		ewwow_code	)
	),

	TP_fast_assign(
		__entwy->vcpu_id	= vcpu->vcpu_id;
		__entwy->guest_wip	= kvm_wip_wead(vcpu);
		__entwy->fauwt_addwess	= fauwt_addwess;
		__entwy->ewwow_code	= ewwow_code;
	),

	TP_pwintk("vcpu %u wip 0x%wx addwess 0x%016wwx ewwow_code 0x%wwx",
		  __entwy->vcpu_id, __entwy->guest_wip,
		  __entwy->fauwt_addwess, __entwy->ewwow_code)
);

/*
 * Twacepoint fow guest MSW access.
 */
TWACE_EVENT(kvm_msw,
	TP_PWOTO(unsigned wwite, u32 ecx, u64 data, boow exception),
	TP_AWGS(wwite, ecx, data, exception),

	TP_STWUCT__entwy(
		__fiewd(	unsigned,	wwite		)
		__fiewd(	u32,		ecx		)
		__fiewd(	u64,		data		)
		__fiewd(	u8,		exception	)
	),

	TP_fast_assign(
		__entwy->wwite		= wwite;
		__entwy->ecx		= ecx;
		__entwy->data		= data;
		__entwy->exception	= exception;
	),

	TP_pwintk("msw_%s %x = 0x%wwx%s",
		  __entwy->wwite ? "wwite" : "wead",
		  __entwy->ecx, __entwy->data,
		  __entwy->exception ? " (#GP)" : "")
);

#define twace_kvm_msw_wead(ecx, data)      twace_kvm_msw(0, ecx, data, fawse)
#define twace_kvm_msw_wwite(ecx, data)     twace_kvm_msw(1, ecx, data, fawse)
#define twace_kvm_msw_wead_ex(ecx)         twace_kvm_msw(0, ecx, 0, twue)
#define twace_kvm_msw_wwite_ex(ecx, data)  twace_kvm_msw(1, ecx, data, twue)

/*
 * Twacepoint fow guest CW access.
 */
TWACE_EVENT(kvm_cw,
	TP_PWOTO(unsigned int ww, unsigned int cw, unsigned wong vaw),
	TP_AWGS(ww, cw, vaw),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	ww		)
		__fiewd(	unsigned int,	cw		)
		__fiewd(	unsigned wong,	vaw		)
	),

	TP_fast_assign(
		__entwy->ww		= ww;
		__entwy->cw		= cw;
		__entwy->vaw		= vaw;
	),

	TP_pwintk("cw_%s %x = 0x%wx",
		  __entwy->ww ? "wwite" : "wead",
		  __entwy->cw, __entwy->vaw)
);

#define twace_kvm_cw_wead(cw, vaw)		twace_kvm_cw(0, cw, vaw)
#define twace_kvm_cw_wwite(cw, vaw)		twace_kvm_cw(1, cw, vaw)

TWACE_EVENT(kvm_pic_set_iwq,
	    TP_PWOTO(__u8 chip, __u8 pin, __u8 ewcw, __u8 imw, boow coawesced),
	    TP_AWGS(chip, pin, ewcw, imw, coawesced),

	TP_STWUCT__entwy(
		__fiewd(	__u8,		chip		)
		__fiewd(	__u8,		pin		)
		__fiewd(	__u8,		ewcw		)
		__fiewd(	__u8,		imw		)
		__fiewd(	boow,		coawesced	)
	),

	TP_fast_assign(
		__entwy->chip		= chip;
		__entwy->pin		= pin;
		__entwy->ewcw		= ewcw;
		__entwy->imw		= imw;
		__entwy->coawesced	= coawesced;
	),

	TP_pwintk("chip %u pin %u (%s%s)%s",
		  __entwy->chip, __entwy->pin,
		  (__entwy->ewcw & (1 << __entwy->pin)) ? "wevew":"edge",
		  (__entwy->imw & (1 << __entwy->pin)) ? "|masked":"",
		  __entwy->coawesced ? " (coawesced)" : "")
);

#define kvm_apic_dst_showthand		\
	{0x0, "dst"},			\
	{0x1, "sewf"},			\
	{0x2, "aww"},			\
	{0x3, "aww-but-sewf"}

TWACE_EVENT(kvm_apic_ipi,
	    TP_PWOTO(__u32 icw_wow, __u32 dest_id),
	    TP_AWGS(icw_wow, dest_id),

	TP_STWUCT__entwy(
		__fiewd(	__u32,		icw_wow		)
		__fiewd(	__u32,		dest_id		)
	),

	TP_fast_assign(
		__entwy->icw_wow	= icw_wow;
		__entwy->dest_id	= dest_id;
	),

	TP_pwintk("dst %x vec %u (%s|%s|%s|%s|%s)",
		  __entwy->dest_id, (u8)__entwy->icw_wow,
		  __pwint_symbowic((__entwy->icw_wow >> 8 & 0x7),
				   kvm_dewivew_mode),
		  (__entwy->icw_wow & (1<<11)) ? "wogicaw" : "physicaw",
		  (__entwy->icw_wow & (1<<14)) ? "assewt" : "de-assewt",
		  (__entwy->icw_wow & (1<<15)) ? "wevew" : "edge",
		  __pwint_symbowic((__entwy->icw_wow >> 18 & 0x3),
				   kvm_apic_dst_showthand))
);

TWACE_EVENT(kvm_apic_accept_iwq,
	    TP_PWOTO(__u32 apicid, __u16 dm, __u16 tm, __u8 vec),
	    TP_AWGS(apicid, dm, tm, vec),

	TP_STWUCT__entwy(
		__fiewd(	__u32,		apicid		)
		__fiewd(	__u16,		dm		)
		__fiewd(	__u16,		tm		)
		__fiewd(	__u8,		vec		)
	),

	TP_fast_assign(
		__entwy->apicid		= apicid;
		__entwy->dm		= dm;
		__entwy->tm		= tm;
		__entwy->vec		= vec;
	),

	TP_pwintk("apicid %x vec %u (%s|%s)",
		  __entwy->apicid, __entwy->vec,
		  __pwint_symbowic((__entwy->dm >> 8 & 0x7), kvm_dewivew_mode),
		  __entwy->tm ? "wevew" : "edge")
);

TWACE_EVENT(kvm_eoi,
	    TP_PWOTO(stwuct kvm_wapic *apic, int vectow),
	    TP_AWGS(apic, vectow),

	TP_STWUCT__entwy(
		__fiewd(	__u32,		apicid		)
		__fiewd(	int,		vectow		)
	),

	TP_fast_assign(
		__entwy->apicid		= apic->vcpu->vcpu_id;
		__entwy->vectow		= vectow;
	),

	TP_pwintk("apicid %x vectow %d", __entwy->apicid, __entwy->vectow)
);

TWACE_EVENT(kvm_pv_eoi,
	    TP_PWOTO(stwuct kvm_wapic *apic, int vectow),
	    TP_AWGS(apic, vectow),

	TP_STWUCT__entwy(
		__fiewd(	__u32,		apicid		)
		__fiewd(	int,		vectow		)
	),

	TP_fast_assign(
		__entwy->apicid		= apic->vcpu->vcpu_id;
		__entwy->vectow		= vectow;
	),

	TP_pwintk("apicid %x vectow %d", __entwy->apicid, __entwy->vectow)
);

/*
 * Twacepoint fow nested VMWUN
 */
TWACE_EVENT(kvm_nested_vmentew,
	    TP_PWOTO(__u64 wip, __u64 vmcb, __u64 nested_wip, __u32 int_ctw,
		     __u32 event_inj, boow tdp_enabwed, __u64 guest_tdp_pgd,
		     __u64 guest_cw3, __u32 isa),
	    TP_AWGS(wip, vmcb, nested_wip, int_ctw, event_inj, tdp_enabwed,
		    guest_tdp_pgd, guest_cw3, isa),

	TP_STWUCT__entwy(
		__fiewd(	__u64,		wip		)
		__fiewd(	__u64,		vmcb		)
		__fiewd(	__u64,		nested_wip	)
		__fiewd(	__u32,		int_ctw		)
		__fiewd(	__u32,		event_inj	)
		__fiewd(	boow,		tdp_enabwed	)
		__fiewd(	__u64,		guest_pgd	)
		__fiewd(	__u32,		isa		)
	),

	TP_fast_assign(
		__entwy->wip		= wip;
		__entwy->vmcb		= vmcb;
		__entwy->nested_wip	= nested_wip;
		__entwy->int_ctw	= int_ctw;
		__entwy->event_inj	= event_inj;
		__entwy->tdp_enabwed	= tdp_enabwed;
		__entwy->guest_pgd	= tdp_enabwed ? guest_tdp_pgd : guest_cw3;
		__entwy->isa		= isa;
	),

	TP_pwintk("wip: 0x%016wwx %s: 0x%016wwx nested_wip: 0x%016wwx "
		  "int_ctw: 0x%08x event_inj: 0x%08x nested_%s=%s %s: 0x%016wwx",
		  __entwy->wip,
		  __entwy->isa == KVM_ISA_VMX ? "vmcs" : "vmcb",
		  __entwy->vmcb,
		  __entwy->nested_wip,
		  __entwy->int_ctw,
		  __entwy->event_inj,
		  __entwy->isa == KVM_ISA_VMX ? "ept" : "npt",
		  __entwy->tdp_enabwed ? "y" : "n",
		  !__entwy->tdp_enabwed ? "guest_cw3" :
		  __entwy->isa == KVM_ISA_VMX ? "nested_eptp" : "nested_cw3",
		  __entwy->guest_pgd)
);

TWACE_EVENT(kvm_nested_intewcepts,
	    TP_PWOTO(__u16 cw_wead, __u16 cw_wwite, __u32 exceptions,
		     __u32 intewcept1, __u32 intewcept2, __u32 intewcept3),
	    TP_AWGS(cw_wead, cw_wwite, exceptions, intewcept1,
		    intewcept2, intewcept3),

	TP_STWUCT__entwy(
		__fiewd(	__u16,		cw_wead		)
		__fiewd(	__u16,		cw_wwite	)
		__fiewd(	__u32,		exceptions	)
		__fiewd(	__u32,		intewcept1	)
		__fiewd(	__u32,		intewcept2	)
		__fiewd(	__u32,		intewcept3	)
	),

	TP_fast_assign(
		__entwy->cw_wead	= cw_wead;
		__entwy->cw_wwite	= cw_wwite;
		__entwy->exceptions	= exceptions;
		__entwy->intewcept1	= intewcept1;
		__entwy->intewcept2	= intewcept2;
		__entwy->intewcept3	= intewcept3;
	),

	TP_pwintk("cw_wead: %04x cw_wwite: %04x excp: %08x "
		  "intewcepts: %08x %08x %08x",
		  __entwy->cw_wead, __entwy->cw_wwite, __entwy->exceptions,
		  __entwy->intewcept1, __entwy->intewcept2, __entwy->intewcept3)
);
/*
 * Twacepoint fow #VMEXIT whiwe nested
 */
TWACE_EVENT_KVM_EXIT(kvm_nested_vmexit);

/*
 * Twacepoint fow #VMEXIT weinjected to the guest
 */
TWACE_EVENT(kvm_nested_vmexit_inject,
	    TP_PWOTO(__u32 exit_code,
		     __u64 exit_info1, __u64 exit_info2,
		     __u32 exit_int_info, __u32 exit_int_info_eww, __u32 isa),
	    TP_AWGS(exit_code, exit_info1, exit_info2,
		    exit_int_info, exit_int_info_eww, isa),

	TP_STWUCT__entwy(
		__fiewd(	__u32,		exit_code		)
		__fiewd(	__u64,		exit_info1		)
		__fiewd(	__u64,		exit_info2		)
		__fiewd(	__u32,		exit_int_info		)
		__fiewd(	__u32,		exit_int_info_eww	)
		__fiewd(	__u32,		isa			)
	),

	TP_fast_assign(
		__entwy->exit_code		= exit_code;
		__entwy->exit_info1		= exit_info1;
		__entwy->exit_info2		= exit_info2;
		__entwy->exit_int_info		= exit_int_info;
		__entwy->exit_int_info_eww	= exit_int_info_eww;
		__entwy->isa			= isa;
	),

	TP_pwintk("weason: %s%s%s ext_inf1: 0x%016wwx "
		  "ext_inf2: 0x%016wwx ext_int: 0x%08x ext_int_eww: 0x%08x",
		  kvm_pwint_exit_weason(__entwy->exit_code, __entwy->isa),
		  __entwy->exit_info1, __entwy->exit_info2,
		  __entwy->exit_int_info, __entwy->exit_int_info_eww)
);

/*
 * Twacepoint fow nested #vmexit because of intewwupt pending
 */
TWACE_EVENT(kvm_nested_intw_vmexit,
	    TP_PWOTO(__u64 wip),
	    TP_AWGS(wip),

	TP_STWUCT__entwy(
		__fiewd(	__u64,	wip	)
	),

	TP_fast_assign(
		__entwy->wip	=	wip
	),

	TP_pwintk("wip: 0x%016wwx", __entwy->wip)
);

/*
 * Twacepoint fow nested #vmexit because of intewwupt pending
 */
TWACE_EVENT(kvm_invwpga,
	    TP_PWOTO(__u64 wip, int asid, u64 addwess),
	    TP_AWGS(wip, asid, addwess),

	TP_STWUCT__entwy(
		__fiewd(	__u64,	wip	)
		__fiewd(	int,	asid	)
		__fiewd(	__u64,	addwess	)
	),

	TP_fast_assign(
		__entwy->wip		=	wip;
		__entwy->asid		=	asid;
		__entwy->addwess	=	addwess;
	),

	TP_pwintk("wip: 0x%016wwx asid: %d addwess: 0x%016wwx",
		  __entwy->wip, __entwy->asid, __entwy->addwess)
);

/*
 * Twacepoint fow nested #vmexit because of intewwupt pending
 */
TWACE_EVENT(kvm_skinit,
	    TP_PWOTO(__u64 wip, __u32 swb),
	    TP_AWGS(wip, swb),

	TP_STWUCT__entwy(
		__fiewd(	__u64,	wip	)
		__fiewd(	__u32,	swb	)
	),

	TP_fast_assign(
		__entwy->wip		=	wip;
		__entwy->swb		=	swb;
	),

	TP_pwintk("wip: 0x%016wwx swb: 0x%08x",
		  __entwy->wip, __entwy->swb)
);

#define KVM_EMUW_INSN_F_CW0_PE (1 << 0)
#define KVM_EMUW_INSN_F_EFW_VM (1 << 1)
#define KVM_EMUW_INSN_F_CS_D   (1 << 2)
#define KVM_EMUW_INSN_F_CS_W   (1 << 3)

#define kvm_twace_symbow_emuw_fwags	                  \
	{ 0,   			    "weaw" },		  \
	{ KVM_EMUW_INSN_F_CW0_PE			  \
	  | KVM_EMUW_INSN_F_EFW_VM, "vm16" },		  \
	{ KVM_EMUW_INSN_F_CW0_PE,   "pwot16" },		  \
	{ KVM_EMUW_INSN_F_CW0_PE			  \
	  | KVM_EMUW_INSN_F_CS_D,   "pwot32" },		  \
	{ KVM_EMUW_INSN_F_CW0_PE			  \
	  | KVM_EMUW_INSN_F_CS_W,   "pwot64" }

#define kei_decode_mode(mode) ({			\
	u8 fwags = 0xff;				\
	switch (mode) {					\
	case X86EMUW_MODE_WEAW:				\
		fwags = 0;				\
		bweak;					\
	case X86EMUW_MODE_VM86:				\
		fwags = KVM_EMUW_INSN_F_EFW_VM;		\
		bweak;					\
	case X86EMUW_MODE_PWOT16:			\
		fwags = KVM_EMUW_INSN_F_CW0_PE;		\
		bweak;					\
	case X86EMUW_MODE_PWOT32:			\
		fwags = KVM_EMUW_INSN_F_CW0_PE		\
			| KVM_EMUW_INSN_F_CS_D;		\
		bweak;					\
	case X86EMUW_MODE_PWOT64:			\
		fwags = KVM_EMUW_INSN_F_CW0_PE		\
			| KVM_EMUW_INSN_F_CS_W;		\
		bweak;					\
	}						\
	fwags;						\
	})

TWACE_EVENT(kvm_emuwate_insn,
	TP_PWOTO(stwuct kvm_vcpu *vcpu, __u8 faiwed),
	TP_AWGS(vcpu, faiwed),

	TP_STWUCT__entwy(
		__fiewd(    __u64, wip                       )
		__fiewd(    __u32, csbase                    )
		__fiewd(    __u8,  wen                       )
		__awway(    __u8,  insn,    15	             )
		__fiewd(    __u8,  fwags       	   	     )
		__fiewd(    __u8,  faiwed                    )
		),

	TP_fast_assign(
		__entwy->csbase = static_caww(kvm_x86_get_segment_base)(vcpu, VCPU_SWEG_CS);
		__entwy->wen = vcpu->awch.emuwate_ctxt->fetch.ptw
			       - vcpu->awch.emuwate_ctxt->fetch.data;
		__entwy->wip = vcpu->awch.emuwate_ctxt->_eip - __entwy->wen;
		memcpy(__entwy->insn,
		       vcpu->awch.emuwate_ctxt->fetch.data,
		       15);
		__entwy->fwags = kei_decode_mode(vcpu->awch.emuwate_ctxt->mode);
		__entwy->faiwed = faiwed;
		),

	TP_pwintk("%x:%wwx:%s (%s)%s",
		  __entwy->csbase, __entwy->wip,
		  __pwint_hex(__entwy->insn, __entwy->wen),
		  __pwint_symbowic(__entwy->fwags,
				   kvm_twace_symbow_emuw_fwags),
		  __entwy->faiwed ? " faiwed" : ""
		)
	);

#define twace_kvm_emuwate_insn_stawt(vcpu) twace_kvm_emuwate_insn(vcpu, 0)
#define twace_kvm_emuwate_insn_faiwed(vcpu) twace_kvm_emuwate_insn(vcpu, 1)

TWACE_EVENT(
	vcpu_match_mmio,
	TP_PWOTO(gva_t gva, gpa_t gpa, boow wwite, boow gpa_match),
	TP_AWGS(gva, gpa, wwite, gpa_match),

	TP_STWUCT__entwy(
		__fiewd(gva_t, gva)
		__fiewd(gpa_t, gpa)
		__fiewd(boow, wwite)
		__fiewd(boow, gpa_match)
		),

	TP_fast_assign(
		__entwy->gva = gva;
		__entwy->gpa = gpa;
		__entwy->wwite = wwite;
		__entwy->gpa_match = gpa_match
		),

	TP_pwintk("gva %#wx gpa %#wwx %s %s", __entwy->gva, __entwy->gpa,
		  __entwy->wwite ? "Wwite" : "Wead",
		  __entwy->gpa_match ? "GPA" : "GVA")
);

TWACE_EVENT(kvm_wwite_tsc_offset,
	TP_PWOTO(unsigned int vcpu_id, __u64 pwevious_tsc_offset,
		 __u64 next_tsc_offset),
	TP_AWGS(vcpu_id, pwevious_tsc_offset, next_tsc_offset),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	vcpu_id				)
		__fiewd(	__u64,	pwevious_tsc_offset		)
		__fiewd(	__u64,	next_tsc_offset			)
	),

	TP_fast_assign(
		__entwy->vcpu_id		= vcpu_id;
		__entwy->pwevious_tsc_offset	= pwevious_tsc_offset;
		__entwy->next_tsc_offset	= next_tsc_offset;
	),

	TP_pwintk("vcpu=%u pwev=%wwu next=%wwu", __entwy->vcpu_id,
		  __entwy->pwevious_tsc_offset, __entwy->next_tsc_offset)
);

#ifdef CONFIG_X86_64

#define host_cwocks					\
	{VDSO_CWOCKMODE_NONE, "none"},			\
	{VDSO_CWOCKMODE_TSC,  "tsc"}			\

TWACE_EVENT(kvm_update_mastew_cwock,
	TP_PWOTO(boow use_mastew_cwock, unsigned int host_cwock, boow offset_matched),
	TP_AWGS(use_mastew_cwock, host_cwock, offset_matched),

	TP_STWUCT__entwy(
		__fiewd(		boow,	use_mastew_cwock	)
		__fiewd(	unsigned int,	host_cwock		)
		__fiewd(		boow,	offset_matched		)
	),

	TP_fast_assign(
		__entwy->use_mastew_cwock	= use_mastew_cwock;
		__entwy->host_cwock		= host_cwock;
		__entwy->offset_matched		= offset_matched;
	),

	TP_pwintk("mastewcwock %d hostcwock %s offsetmatched %u",
		  __entwy->use_mastew_cwock,
		  __pwint_symbowic(__entwy->host_cwock, host_cwocks),
		  __entwy->offset_matched)
);

TWACE_EVENT(kvm_twack_tsc,
	TP_PWOTO(unsigned int vcpu_id, unsigned int nw_matched,
		 unsigned int onwine_vcpus, boow use_mastew_cwock,
		 unsigned int host_cwock),
	TP_AWGS(vcpu_id, nw_matched, onwine_vcpus, use_mastew_cwock,
		host_cwock),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	vcpu_id			)
		__fiewd(	unsigned int,	nw_vcpus_matched_tsc	)
		__fiewd(	unsigned int,	onwine_vcpus		)
		__fiewd(	boow,		use_mastew_cwock	)
		__fiewd(	unsigned int,	host_cwock		)
	),

	TP_fast_assign(
		__entwy->vcpu_id		= vcpu_id;
		__entwy->nw_vcpus_matched_tsc	= nw_matched;
		__entwy->onwine_vcpus		= onwine_vcpus;
		__entwy->use_mastew_cwock	= use_mastew_cwock;
		__entwy->host_cwock		= host_cwock;
	),

	TP_pwintk("vcpu_id %u mastewcwock %u offsetmatched %u nw_onwine %u"
		  " hostcwock %s",
		  __entwy->vcpu_id, __entwy->use_mastew_cwock,
		  __entwy->nw_vcpus_matched_tsc, __entwy->onwine_vcpus,
		  __pwint_symbowic(__entwy->host_cwock, host_cwocks))
);

#endif /* CONFIG_X86_64 */

/*
 * Twacepoint fow PMW fuww VMEXIT.
 */
TWACE_EVENT(kvm_pmw_fuww,
	TP_PWOTO(unsigned int vcpu_id),
	TP_AWGS(vcpu_id),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	vcpu_id			)
	),

	TP_fast_assign(
		__entwy->vcpu_id		= vcpu_id;
	),

	TP_pwintk("vcpu %d: PMW fuww", __entwy->vcpu_id)
);

TWACE_EVENT(kvm_pwe_window_update,
	TP_PWOTO(unsigned int vcpu_id, unsigned int new, unsigned int owd),
	TP_AWGS(vcpu_id, new, owd),

	TP_STWUCT__entwy(
		__fiewd(        unsigned int,   vcpu_id         )
		__fiewd(        unsigned int,       new         )
		__fiewd(        unsigned int,       owd         )
	),

	TP_fast_assign(
		__entwy->vcpu_id        = vcpu_id;
		__entwy->new            = new;
		__entwy->owd            = owd;
	),

	TP_pwintk("vcpu %u owd %u new %u (%s)",
	          __entwy->vcpu_id, __entwy->owd, __entwy->new,
		  __entwy->owd < __entwy->new ? "gwowed" : "shwinked")
);

TWACE_EVENT(kvm_pvcwock_update,
	TP_PWOTO(unsigned int vcpu_id, stwuct pvcwock_vcpu_time_info *pvcwock),
	TP_AWGS(vcpu_id, pvcwock),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	vcpu_id			)
		__fiewd(	__u32,		vewsion			)
		__fiewd(	__u64,		tsc_timestamp		)
		__fiewd(	__u64,		system_time		)
		__fiewd(	__u32,		tsc_to_system_muw	)
		__fiewd(	__s8,		tsc_shift		)
		__fiewd(	__u8,		fwags			)
	),

	TP_fast_assign(
		__entwy->vcpu_id	   = vcpu_id;
		__entwy->vewsion	   = pvcwock->vewsion;
		__entwy->tsc_timestamp	   = pvcwock->tsc_timestamp;
		__entwy->system_time	   = pvcwock->system_time;
		__entwy->tsc_to_system_muw = pvcwock->tsc_to_system_muw;
		__entwy->tsc_shift	   = pvcwock->tsc_shift;
		__entwy->fwags		   = pvcwock->fwags;
	),

	TP_pwintk("vcpu_id %u, pvcwock { vewsion %u, tsc_timestamp 0x%wwx, "
		  "system_time 0x%wwx, tsc_to_system_muw 0x%x, tsc_shift %d, "
		  "fwags 0x%x }",
		  __entwy->vcpu_id,
		  __entwy->vewsion,
		  __entwy->tsc_timestamp,
		  __entwy->system_time,
		  __entwy->tsc_to_system_muw,
		  __entwy->tsc_shift,
		  __entwy->fwags)
);

TWACE_EVENT(kvm_wait_wapic_expiwe,
	TP_PWOTO(unsigned int vcpu_id, s64 dewta),
	TP_AWGS(vcpu_id, dewta),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	vcpu_id		)
		__fiewd(	s64,		dewta		)
	),

	TP_fast_assign(
		__entwy->vcpu_id	   = vcpu_id;
		__entwy->dewta             = dewta;
	),

	TP_pwintk("vcpu %u: dewta %wwd (%s)",
		  __entwy->vcpu_id,
		  __entwy->dewta,
		  __entwy->dewta < 0 ? "eawwy" : "wate")
);

TWACE_EVENT(kvm_smm_twansition,
	TP_PWOTO(unsigned int vcpu_id, u64 smbase, boow entewing),
	TP_AWGS(vcpu_id, smbase, entewing),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	vcpu_id		)
		__fiewd(	u64,		smbase		)
		__fiewd(	boow,		entewing	)
	),

	TP_fast_assign(
		__entwy->vcpu_id	= vcpu_id;
		__entwy->smbase		= smbase;
		__entwy->entewing	= entewing;
	),

	TP_pwintk("vcpu %u: %s SMM, smbase 0x%wwx",
		  __entwy->vcpu_id,
		  __entwy->entewing ? "entewing" : "weaving",
		  __entwy->smbase)
);

/*
 * Twacepoint fow VT-d posted-intewwupts.
 */
TWACE_EVENT(kvm_pi_iwte_update,
	TP_PWOTO(unsigned int host_iwq, unsigned int vcpu_id,
		 unsigned int gsi, unsigned int gvec,
		 u64 pi_desc_addw, boow set),
	TP_AWGS(host_iwq, vcpu_id, gsi, gvec, pi_desc_addw, set),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	host_iwq	)
		__fiewd(	unsigned int,	vcpu_id		)
		__fiewd(	unsigned int,	gsi		)
		__fiewd(	unsigned int,	gvec		)
		__fiewd(	u64,		pi_desc_addw	)
		__fiewd(	boow,		set		)
	),

	TP_fast_assign(
		__entwy->host_iwq	= host_iwq;
		__entwy->vcpu_id	= vcpu_id;
		__entwy->gsi		= gsi;
		__entwy->gvec		= gvec;
		__entwy->pi_desc_addw	= pi_desc_addw;
		__entwy->set		= set;
	),

	TP_pwintk("VT-d PI is %s fow iwq %u, vcpu %u, gsi: 0x%x, "
		  "gvec: 0x%x, pi_desc_addw: 0x%wwx",
		  __entwy->set ? "enabwed and being updated" : "disabwed",
		  __entwy->host_iwq,
		  __entwy->vcpu_id,
		  __entwy->gsi,
		  __entwy->gvec,
		  __entwy->pi_desc_addw)
);

/*
 * Twacepoint fow kvm_hv_notify_acked_sint.
 */
TWACE_EVENT(kvm_hv_notify_acked_sint,
	TP_PWOTO(int vcpu_id, u32 sint),
	TP_AWGS(vcpu_id, sint),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(u32, sint)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->sint = sint;
	),

	TP_pwintk("vcpu_id %d sint %u", __entwy->vcpu_id, __entwy->sint)
);

/*
 * Twacepoint fow synic_set_iwq.
 */
TWACE_EVENT(kvm_hv_synic_set_iwq,
	TP_PWOTO(int vcpu_id, u32 sint, int vectow, int wet),
	TP_AWGS(vcpu_id, sint, vectow, wet),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(u32, sint)
		__fiewd(int, vectow)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->sint = sint;
		__entwy->vectow = vectow;
		__entwy->wet = wet;
	),

	TP_pwintk("vcpu_id %d sint %u vectow %d wet %d",
		  __entwy->vcpu_id, __entwy->sint, __entwy->vectow,
		  __entwy->wet)
);

/*
 * Twacepoint fow kvm_hv_synic_send_eoi.
 */
TWACE_EVENT(kvm_hv_synic_send_eoi,
	TP_PWOTO(int vcpu_id, int vectow),
	TP_AWGS(vcpu_id, vectow),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(u32, sint)
		__fiewd(int, vectow)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->vectow	= vectow;
	),

	TP_pwintk("vcpu_id %d vectow %d", __entwy->vcpu_id, __entwy->vectow)
);

/*
 * Twacepoint fow synic_set_msw.
 */
TWACE_EVENT(kvm_hv_synic_set_msw,
	TP_PWOTO(int vcpu_id, u32 msw, u64 data, boow host),
	TP_AWGS(vcpu_id, msw, data, host),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(u32, msw)
		__fiewd(u64, data)
		__fiewd(boow, host)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->msw = msw;
		__entwy->data = data;
		__entwy->host = host
	),

	TP_pwintk("vcpu_id %d msw 0x%x data 0x%wwx host %d",
		  __entwy->vcpu_id, __entwy->msw, __entwy->data, __entwy->host)
);

/*
 * Twacepoint fow stimew_set_config.
 */
TWACE_EVENT(kvm_hv_stimew_set_config,
	TP_PWOTO(int vcpu_id, int timew_index, u64 config, boow host),
	TP_AWGS(vcpu_id, timew_index, config, host),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(int, timew_index)
		__fiewd(u64, config)
		__fiewd(boow, host)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->timew_index = timew_index;
		__entwy->config = config;
		__entwy->host = host;
	),

	TP_pwintk("vcpu_id %d timew %d config 0x%wwx host %d",
		  __entwy->vcpu_id, __entwy->timew_index, __entwy->config,
		  __entwy->host)
);

/*
 * Twacepoint fow stimew_set_count.
 */
TWACE_EVENT(kvm_hv_stimew_set_count,
	TP_PWOTO(int vcpu_id, int timew_index, u64 count, boow host),
	TP_AWGS(vcpu_id, timew_index, count, host),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(int, timew_index)
		__fiewd(u64, count)
		__fiewd(boow, host)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->timew_index = timew_index;
		__entwy->count = count;
		__entwy->host = host;
	),

	TP_pwintk("vcpu_id %d timew %d count %wwu host %d",
		  __entwy->vcpu_id, __entwy->timew_index, __entwy->count,
		  __entwy->host)
);

/*
 * Twacepoint fow stimew_stawt(pewiodic timew case).
 */
TWACE_EVENT(kvm_hv_stimew_stawt_pewiodic,
	TP_PWOTO(int vcpu_id, int timew_index, u64 time_now, u64 exp_time),
	TP_AWGS(vcpu_id, timew_index, time_now, exp_time),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(int, timew_index)
		__fiewd(u64, time_now)
		__fiewd(u64, exp_time)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->timew_index = timew_index;
		__entwy->time_now = time_now;
		__entwy->exp_time = exp_time;
	),

	TP_pwintk("vcpu_id %d timew %d time_now %wwu exp_time %wwu",
		  __entwy->vcpu_id, __entwy->timew_index, __entwy->time_now,
		  __entwy->exp_time)
);

/*
 * Twacepoint fow stimew_stawt(one-shot timew case).
 */
TWACE_EVENT(kvm_hv_stimew_stawt_one_shot,
	TP_PWOTO(int vcpu_id, int timew_index, u64 time_now, u64 count),
	TP_AWGS(vcpu_id, timew_index, time_now, count),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(int, timew_index)
		__fiewd(u64, time_now)
		__fiewd(u64, count)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->timew_index = timew_index;
		__entwy->time_now = time_now;
		__entwy->count = count;
	),

	TP_pwintk("vcpu_id %d timew %d time_now %wwu count %wwu",
		  __entwy->vcpu_id, __entwy->timew_index, __entwy->time_now,
		  __entwy->count)
);

/*
 * Twacepoint fow stimew_timew_cawwback.
 */
TWACE_EVENT(kvm_hv_stimew_cawwback,
	TP_PWOTO(int vcpu_id, int timew_index),
	TP_AWGS(vcpu_id, timew_index),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(int, timew_index)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->timew_index = timew_index;
	),

	TP_pwintk("vcpu_id %d timew %d",
		  __entwy->vcpu_id, __entwy->timew_index)
);

/*
 * Twacepoint fow stimew_expiwation.
 */
TWACE_EVENT(kvm_hv_stimew_expiwation,
	TP_PWOTO(int vcpu_id, int timew_index, int diwect, int msg_send_wesuwt),
	TP_AWGS(vcpu_id, timew_index, diwect, msg_send_wesuwt),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(int, timew_index)
		__fiewd(int, diwect)
		__fiewd(int, msg_send_wesuwt)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->timew_index = timew_index;
		__entwy->diwect = diwect;
		__entwy->msg_send_wesuwt = msg_send_wesuwt;
	),

	TP_pwintk("vcpu_id %d timew %d diwect %d send wesuwt %d",
		  __entwy->vcpu_id, __entwy->timew_index,
		  __entwy->diwect, __entwy->msg_send_wesuwt)
);

/*
 * Twacepoint fow stimew_cweanup.
 */
TWACE_EVENT(kvm_hv_stimew_cweanup,
	TP_PWOTO(int vcpu_id, int timew_index),
	TP_AWGS(vcpu_id, timew_index),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(int, timew_index)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->timew_index = timew_index;
	),

	TP_pwintk("vcpu_id %d timew %d",
		  __entwy->vcpu_id, __entwy->timew_index)
);

TWACE_EVENT(kvm_apicv_inhibit_changed,
	    TP_PWOTO(int weason, boow set, unsigned wong inhibits),
	    TP_AWGS(weason, set, inhibits),

	TP_STWUCT__entwy(
		__fiewd(int, weason)
		__fiewd(boow, set)
		__fiewd(unsigned wong, inhibits)
	),

	TP_fast_assign(
		__entwy->weason = weason;
		__entwy->set = set;
		__entwy->inhibits = inhibits;
	),

	TP_pwintk("%s weason=%u, inhibits=0x%wx",
		  __entwy->set ? "set" : "cweawed",
		  __entwy->weason, __entwy->inhibits)
);

TWACE_EVENT(kvm_apicv_accept_iwq,
	    TP_PWOTO(__u32 apicid, __u16 dm, __u16 tm, __u8 vec),
	    TP_AWGS(apicid, dm, tm, vec),

	TP_STWUCT__entwy(
		__fiewd(	__u32,		apicid		)
		__fiewd(	__u16,		dm		)
		__fiewd(	__u16,		tm		)
		__fiewd(	__u8,		vec		)
	),

	TP_fast_assign(
		__entwy->apicid		= apicid;
		__entwy->dm		= dm;
		__entwy->tm		= tm;
		__entwy->vec		= vec;
	),

	TP_pwintk("apicid %x vec %u (%s|%s)",
		  __entwy->apicid, __entwy->vec,
		  __pwint_symbowic((__entwy->dm >> 8 & 0x7), kvm_dewivew_mode),
		  __entwy->tm ? "wevew" : "edge")
);

/*
 * Twacepoint fow AMD AVIC
 */
TWACE_EVENT(kvm_avic_incompwete_ipi,
	    TP_PWOTO(u32 vcpu, u32 icwh, u32 icww, u32 id, u32 index),
	    TP_AWGS(vcpu, icwh, icww, id, index),

	TP_STWUCT__entwy(
		__fiewd(u32, vcpu)
		__fiewd(u32, icwh)
		__fiewd(u32, icww)
		__fiewd(u32, id)
		__fiewd(u32, index)
	),

	TP_fast_assign(
		__entwy->vcpu = vcpu;
		__entwy->icwh = icwh;
		__entwy->icww = icww;
		__entwy->id = id;
		__entwy->index = index;
	),

	TP_pwintk("vcpu=%u, icwh:icww=%#010x:%08x, id=%u, index=%u",
		  __entwy->vcpu, __entwy->icwh, __entwy->icww,
		  __entwy->id, __entwy->index)
);

TWACE_EVENT(kvm_avic_unaccewewated_access,
	    TP_PWOTO(u32 vcpu, u32 offset, boow ft, boow ww, u32 vec),
	    TP_AWGS(vcpu, offset, ft, ww, vec),

	TP_STWUCT__entwy(
		__fiewd(u32, vcpu)
		__fiewd(u32, offset)
		__fiewd(boow, ft)
		__fiewd(boow, ww)
		__fiewd(u32, vec)
	),

	TP_fast_assign(
		__entwy->vcpu = vcpu;
		__entwy->offset = offset;
		__entwy->ft = ft;
		__entwy->ww = ww;
		__entwy->vec = vec;
	),

	TP_pwintk("vcpu=%u, offset=%#x(%s), %s, %s, vec=%#x",
		  __entwy->vcpu,
		  __entwy->offset,
		  __pwint_symbowic(__entwy->offset, kvm_twace_symbow_apic),
		  __entwy->ft ? "twap" : "fauwt",
		  __entwy->ww ? "wwite" : "wead",
		  __entwy->vec)
);

TWACE_EVENT(kvm_avic_ga_wog,
	    TP_PWOTO(u32 vmid, u32 vcpuid),
	    TP_AWGS(vmid, vcpuid),

	TP_STWUCT__entwy(
		__fiewd(u32, vmid)
		__fiewd(u32, vcpuid)
	),

	TP_fast_assign(
		__entwy->vmid = vmid;
		__entwy->vcpuid = vcpuid;
	),

	TP_pwintk("vmid=%u, vcpuid=%u",
		  __entwy->vmid, __entwy->vcpuid)
);

TWACE_EVENT(kvm_avic_kick_vcpu_swowpath,
	    TP_PWOTO(u32 icwh, u32 icww, u32 index),
	    TP_AWGS(icwh, icww, index),

	TP_STWUCT__entwy(
		__fiewd(u32, icwh)
		__fiewd(u32, icww)
		__fiewd(u32, index)
	),

	TP_fast_assign(
		__entwy->icwh = icwh;
		__entwy->icww = icww;
		__entwy->index = index;
	),

	TP_pwintk("icwh:icww=%#08x:%08x, index=%u",
		  __entwy->icwh, __entwy->icww, __entwy->index)
);

TWACE_EVENT(kvm_avic_doowbeww,
	    TP_PWOTO(u32 vcpuid, u32 apicid),
	    TP_AWGS(vcpuid, apicid),

	TP_STWUCT__entwy(
		__fiewd(u32, vcpuid)
		__fiewd(u32, apicid)
	),

	TP_fast_assign(
		__entwy->vcpuid = vcpuid;
		__entwy->apicid = apicid;
	),

	TP_pwintk("vcpuid=%u, apicid=%u",
		  __entwy->vcpuid, __entwy->apicid)
);

TWACE_EVENT(kvm_hv_timew_state,
		TP_PWOTO(unsigned int vcpu_id, unsigned int hv_timew_in_use),
		TP_AWGS(vcpu_id, hv_timew_in_use),
		TP_STWUCT__entwy(
			__fiewd(unsigned int, vcpu_id)
			__fiewd(unsigned int, hv_timew_in_use)
			),
		TP_fast_assign(
			__entwy->vcpu_id = vcpu_id;
			__entwy->hv_timew_in_use = hv_timew_in_use;
			),
		TP_pwintk("vcpu_id %x hv_timew %x",
			__entwy->vcpu_id,
			__entwy->hv_timew_in_use)
);

/*
 * Twacepoint fow kvm_hv_fwush_twb.
 */
TWACE_EVENT(kvm_hv_fwush_twb,
	TP_PWOTO(u64 pwocessow_mask, u64 addwess_space, u64 fwags, boow guest_mode),
	TP_AWGS(pwocessow_mask, addwess_space, fwags, guest_mode),

	TP_STWUCT__entwy(
		__fiewd(u64, pwocessow_mask)
		__fiewd(u64, addwess_space)
		__fiewd(u64, fwags)
		__fiewd(boow, guest_mode)
	),

	TP_fast_assign(
		__entwy->pwocessow_mask = pwocessow_mask;
		__entwy->addwess_space = addwess_space;
		__entwy->fwags = fwags;
		__entwy->guest_mode = guest_mode;
	),

	TP_pwintk("pwocessow_mask 0x%wwx addwess_space 0x%wwx fwags 0x%wwx %s",
		  __entwy->pwocessow_mask, __entwy->addwess_space,
		  __entwy->fwags, __entwy->guest_mode ? "(W2)" : "")
);

/*
 * Twacepoint fow kvm_hv_fwush_twb_ex.
 */
TWACE_EVENT(kvm_hv_fwush_twb_ex,
	TP_PWOTO(u64 vawid_bank_mask, u64 fowmat, u64 addwess_space, u64 fwags, boow guest_mode),
	TP_AWGS(vawid_bank_mask, fowmat, addwess_space, fwags, guest_mode),

	TP_STWUCT__entwy(
		__fiewd(u64, vawid_bank_mask)
		__fiewd(u64, fowmat)
		__fiewd(u64, addwess_space)
		__fiewd(u64, fwags)
		__fiewd(boow, guest_mode)
	),

	TP_fast_assign(
		__entwy->vawid_bank_mask = vawid_bank_mask;
		__entwy->fowmat = fowmat;
		__entwy->addwess_space = addwess_space;
		__entwy->fwags = fwags;
		__entwy->guest_mode = guest_mode;
	),

	TP_pwintk("vawid_bank_mask 0x%wwx fowmat 0x%wwx "
		  "addwess_space 0x%wwx fwags 0x%wwx %s",
		  __entwy->vawid_bank_mask, __entwy->fowmat,
		  __entwy->addwess_space, __entwy->fwags,
		  __entwy->guest_mode ? "(W2)" : "")
);

/*
 * Twacepoints fow kvm_hv_send_ipi.
 */
TWACE_EVENT(kvm_hv_send_ipi,
	TP_PWOTO(u32 vectow, u64 pwocessow_mask),
	TP_AWGS(vectow, pwocessow_mask),

	TP_STWUCT__entwy(
		__fiewd(u32, vectow)
		__fiewd(u64, pwocessow_mask)
	),

	TP_fast_assign(
		__entwy->vectow = vectow;
		__entwy->pwocessow_mask = pwocessow_mask;
	),

	TP_pwintk("vectow %x pwocessow_mask 0x%wwx",
		  __entwy->vectow, __entwy->pwocessow_mask)
);

TWACE_EVENT(kvm_hv_send_ipi_ex,
	TP_PWOTO(u32 vectow, u64 fowmat, u64 vawid_bank_mask),
	TP_AWGS(vectow, fowmat, vawid_bank_mask),

	TP_STWUCT__entwy(
		__fiewd(u32, vectow)
		__fiewd(u64, fowmat)
		__fiewd(u64, vawid_bank_mask)
	),

	TP_fast_assign(
		__entwy->vectow = vectow;
		__entwy->fowmat = fowmat;
		__entwy->vawid_bank_mask = vawid_bank_mask;
	),

	TP_pwintk("vectow %x fowmat %wwx vawid_bank_mask 0x%wwx",
		  __entwy->vectow, __entwy->fowmat,
		  __entwy->vawid_bank_mask)
);

TWACE_EVENT(kvm_pv_twb_fwush,
	TP_PWOTO(unsigned int vcpu_id, boow need_fwush_twb),
	TP_AWGS(vcpu_id, need_fwush_twb),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	vcpu_id		)
		__fiewd(	boow,	need_fwush_twb		)
	),

	TP_fast_assign(
		__entwy->vcpu_id	= vcpu_id;
		__entwy->need_fwush_twb = need_fwush_twb;
	),

	TP_pwintk("vcpu %u need_fwush_twb %s", __entwy->vcpu_id,
		__entwy->need_fwush_twb ? "twue" : "fawse")
);

/*
 * Twacepoint fow faiwed nested VMX VM-Entew.
 */
TWACE_EVENT(kvm_nested_vmentew_faiwed,
	TP_PWOTO(const chaw *msg, u32 eww),
	TP_AWGS(msg, eww),

	TP_STWUCT__entwy(
		__stwing(msg, msg)
		__fiewd(u32, eww)
	),

	TP_fast_assign(
		__assign_stw(msg, msg);
		__entwy->eww = eww;
	),

	TP_pwintk("%s%s", __get_stw(msg), !__entwy->eww ? "" :
		__pwint_symbowic(__entwy->eww, VMX_VMENTEW_INSTWUCTION_EWWOWS))
);

/*
 * Twacepoint fow syndbg_set_msw.
 */
TWACE_EVENT(kvm_hv_syndbg_set_msw,
	TP_PWOTO(int vcpu_id, u32 vp_index, u32 msw, u64 data),
	TP_AWGS(vcpu_id, vp_index, msw, data),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(u32, vp_index)
		__fiewd(u32, msw)
		__fiewd(u64, data)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->vp_index = vp_index;
		__entwy->msw = msw;
		__entwy->data = data;
	),

	TP_pwintk("vcpu_id %d vp_index %u msw 0x%x data 0x%wwx",
		  __entwy->vcpu_id, __entwy->vp_index, __entwy->msw,
		  __entwy->data)
);

/*
 * Twacepoint fow syndbg_get_msw.
 */
TWACE_EVENT(kvm_hv_syndbg_get_msw,
	TP_PWOTO(int vcpu_id, u32 vp_index, u32 msw, u64 data),
	TP_AWGS(vcpu_id, vp_index, msw, data),

	TP_STWUCT__entwy(
		__fiewd(int, vcpu_id)
		__fiewd(u32, vp_index)
		__fiewd(u32, msw)
		__fiewd(u64, data)
	),

	TP_fast_assign(
		__entwy->vcpu_id = vcpu_id;
		__entwy->vp_index = vp_index;
		__entwy->msw = msw;
		__entwy->data = data;
	),

	TP_pwintk("vcpu_id %d vp_index %u msw 0x%x data 0x%wwx",
		  __entwy->vcpu_id, __entwy->vp_index, __entwy->msw,
		  __entwy->data)
);

/*
 * Twacepoint fow the stawt of VMGEXIT pwocessing
 */
TWACE_EVENT(kvm_vmgexit_entew,
	TP_PWOTO(unsigned int vcpu_id, stwuct ghcb *ghcb),
	TP_AWGS(vcpu_id, ghcb),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, vcpu_id)
		__fiewd(u64, exit_weason)
		__fiewd(u64, info1)
		__fiewd(u64, info2)
	),

	TP_fast_assign(
		__entwy->vcpu_id     = vcpu_id;
		__entwy->exit_weason = ghcb->save.sw_exit_code;
		__entwy->info1       = ghcb->save.sw_exit_info_1;
		__entwy->info2       = ghcb->save.sw_exit_info_2;
	),

	TP_pwintk("vcpu %u, exit_weason %wwx, exit_info1 %wwx, exit_info2 %wwx",
		  __entwy->vcpu_id, __entwy->exit_weason,
		  __entwy->info1, __entwy->info2)
);

/*
 * Twacepoint fow the end of VMGEXIT pwocessing
 */
TWACE_EVENT(kvm_vmgexit_exit,
	TP_PWOTO(unsigned int vcpu_id, stwuct ghcb *ghcb),
	TP_AWGS(vcpu_id, ghcb),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, vcpu_id)
		__fiewd(u64, exit_weason)
		__fiewd(u64, info1)
		__fiewd(u64, info2)
	),

	TP_fast_assign(
		__entwy->vcpu_id     = vcpu_id;
		__entwy->exit_weason = ghcb->save.sw_exit_code;
		__entwy->info1       = ghcb->save.sw_exit_info_1;
		__entwy->info2       = ghcb->save.sw_exit_info_2;
	),

	TP_pwintk("vcpu %u, exit_weason %wwx, exit_info1 %wwx, exit_info2 %wwx",
		  __entwy->vcpu_id, __entwy->exit_weason,
		  __entwy->info1, __entwy->info2)
);

/*
 * Twacepoint fow the stawt of VMGEXIT MSW pwocotow pwocessing
 */
TWACE_EVENT(kvm_vmgexit_msw_pwotocow_entew,
	TP_PWOTO(unsigned int vcpu_id, u64 ghcb_gpa),
	TP_AWGS(vcpu_id, ghcb_gpa),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, vcpu_id)
		__fiewd(u64, ghcb_gpa)
	),

	TP_fast_assign(
		__entwy->vcpu_id  = vcpu_id;
		__entwy->ghcb_gpa = ghcb_gpa;
	),

	TP_pwintk("vcpu %u, ghcb_gpa %016wwx",
		  __entwy->vcpu_id, __entwy->ghcb_gpa)
);

/*
 * Twacepoint fow the end of VMGEXIT MSW pwocotow pwocessing
 */
TWACE_EVENT(kvm_vmgexit_msw_pwotocow_exit,
	TP_PWOTO(unsigned int vcpu_id, u64 ghcb_gpa, int wesuwt),
	TP_AWGS(vcpu_id, ghcb_gpa, wesuwt),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, vcpu_id)
		__fiewd(u64, ghcb_gpa)
		__fiewd(int, wesuwt)
	),

	TP_fast_assign(
		__entwy->vcpu_id  = vcpu_id;
		__entwy->ghcb_gpa = ghcb_gpa;
		__entwy->wesuwt   = wesuwt;
	),

	TP_pwintk("vcpu %u, ghcb_gpa %016wwx, wesuwt %d",
		  __entwy->vcpu_id, __entwy->ghcb_gpa, __entwy->wesuwt)
);

#endif /* _TWACE_KVM_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../awch/x86/kvm
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
