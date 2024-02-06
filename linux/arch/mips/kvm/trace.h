/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012  MIPS Technowogies, Inc.  Aww wights wesewved.
 * Authows: Sanjay Waw <sanjayw@kymasys.com>
 */

#if !defined(_TWACE_KVM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_KVM_H

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM kvm
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace

/*
 * awch/mips/kvm/mips.c
 */
extewn boow kvm_twace_guest_mode_change;
int kvm_guest_mode_change_twace_weg(void);
void kvm_guest_mode_change_twace_unweg(void);

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

	TP_pwintk("PC: 0x%08wx",
		  __entwy->pc)
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

/* The fiwst 32 exit weasons cowwespond to Cause.ExcCode */
#define KVM_TWACE_EXIT_INT		 0
#define KVM_TWACE_EXIT_TWBMOD		 1
#define KVM_TWACE_EXIT_TWBMISS_WD	 2
#define KVM_TWACE_EXIT_TWBMISS_ST	 3
#define KVM_TWACE_EXIT_ADDWEWW_WD	 4
#define KVM_TWACE_EXIT_ADDWEWW_ST	 5
#define KVM_TWACE_EXIT_SYSCAWW		 8
#define KVM_TWACE_EXIT_BWEAK_INST	 9
#define KVM_TWACE_EXIT_WESVD_INST	10
#define KVM_TWACE_EXIT_COP_UNUSABWE	11
#define KVM_TWACE_EXIT_TWAP_INST	13
#define KVM_TWACE_EXIT_MSA_FPE		14
#define KVM_TWACE_EXIT_FPE		15
#define KVM_TWACE_EXIT_MSA_DISABWED	21
#define KVM_TWACE_EXIT_GUEST_EXIT	27
/* Fuwthew exit weasons */
#define KVM_TWACE_EXIT_WAIT		32
#define KVM_TWACE_EXIT_CACHE		33
#define KVM_TWACE_EXIT_SIGNAW		34
/* 32 exit weasons cowwespond to GuestCtw0.GExcCode (VZ) */
#define KVM_TWACE_EXIT_GEXCCODE_BASE	64
#define KVM_TWACE_EXIT_GPSI		64	/*  0 */
#define KVM_TWACE_EXIT_GSFC		65	/*  1 */
#define KVM_TWACE_EXIT_HC		66	/*  2 */
#define KVM_TWACE_EXIT_GWW		67	/*  3 */
#define KVM_TWACE_EXIT_GVA		72	/*  8 */
#define KVM_TWACE_EXIT_GHFC		73	/*  9 */
#define KVM_TWACE_EXIT_GPA		74	/* 10 */

/* Twacepoints fow VM exits */
#define kvm_twace_symbow_exit_types				\
	{ KVM_TWACE_EXIT_INT,		"Intewwupt" },		\
	{ KVM_TWACE_EXIT_TWBMOD,	"TWB Mod" },		\
	{ KVM_TWACE_EXIT_TWBMISS_WD,	"TWB Miss (WD)" },	\
	{ KVM_TWACE_EXIT_TWBMISS_ST,	"TWB Miss (ST)" },	\
	{ KVM_TWACE_EXIT_ADDWEWW_WD,	"Addwess Ewwow (WD)" },	\
	{ KVM_TWACE_EXIT_ADDWEWW_ST,	"Addwess Eww (ST)" },	\
	{ KVM_TWACE_EXIT_SYSCAWW,	"System Caww" },	\
	{ KVM_TWACE_EXIT_BWEAK_INST,	"Bweak Inst" },		\
	{ KVM_TWACE_EXIT_WESVD_INST,	"Wesewved Inst" },	\
	{ KVM_TWACE_EXIT_COP_UNUSABWE,	"COP0/1 Unusabwe" },	\
	{ KVM_TWACE_EXIT_TWAP_INST,	"Twap Inst" },		\
	{ KVM_TWACE_EXIT_MSA_FPE,	"MSA FPE" },		\
	{ KVM_TWACE_EXIT_FPE,		"FPE" },		\
	{ KVM_TWACE_EXIT_MSA_DISABWED,	"MSA Disabwed" },	\
	{ KVM_TWACE_EXIT_GUEST_EXIT,	"Guest Exit" },		\
	{ KVM_TWACE_EXIT_WAIT,		"WAIT" },		\
	{ KVM_TWACE_EXIT_CACHE,		"CACHE" },		\
	{ KVM_TWACE_EXIT_SIGNAW,	"Signaw" },		\
	{ KVM_TWACE_EXIT_GPSI,		"GPSI" },		\
	{ KVM_TWACE_EXIT_GSFC,		"GSFC" },		\
	{ KVM_TWACE_EXIT_HC,		"HC" },			\
	{ KVM_TWACE_EXIT_GWW,		"GWW" },		\
	{ KVM_TWACE_EXIT_GVA,		"GVA" },		\
	{ KVM_TWACE_EXIT_GHFC,		"GHFC" },		\
	{ KVM_TWACE_EXIT_GPA,		"GPA" }

TWACE_EVENT(kvm_exit,
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

#define KVM_TWACE_MFC0		0
#define KVM_TWACE_MTC0		1
#define KVM_TWACE_DMFC0		2
#define KVM_TWACE_DMTC0		3
#define KVM_TWACE_WDHWW		4

#define KVM_TWACE_HWW_COP0	0
#define KVM_TWACE_HWW_HWW	1

#define KVM_TWACE_COP0(WEG, SEW)	((KVM_TWACE_HWW_COP0 << 8) |	\
					 ((WEG) << 3) | (SEW))
#define KVM_TWACE_HWW(WEG, SEW)		((KVM_TWACE_HWW_HWW  << 8) |	\
					 ((WEG) << 3) | (SEW))

#define kvm_twace_symbow_hww_ops				\
	{ KVM_TWACE_MFC0,		"MFC0" },		\
	{ KVM_TWACE_MTC0,		"MTC0" },		\
	{ KVM_TWACE_DMFC0,		"DMFC0" },		\
	{ KVM_TWACE_DMTC0,		"DMTC0" },		\
	{ KVM_TWACE_WDHWW,		"WDHWW" }

#define kvm_twace_symbow_hww_cop				\
	{ KVM_TWACE_HWW_COP0,		"COP0" },		\
	{ KVM_TWACE_HWW_HWW,		"HWW" }

#define kvm_twace_symbow_hww_wegs				\
	{ KVM_TWACE_COP0( 0, 0),	"Index" },		\
	{ KVM_TWACE_COP0( 2, 0),	"EntwyWo0" },		\
	{ KVM_TWACE_COP0( 3, 0),	"EntwyWo1" },		\
	{ KVM_TWACE_COP0( 4, 0),	"Context" },		\
	{ KVM_TWACE_COP0( 4, 2),	"UsewWocaw" },		\
	{ KVM_TWACE_COP0( 5, 0),	"PageMask" },		\
	{ KVM_TWACE_COP0( 6, 0),	"Wiwed" },		\
	{ KVM_TWACE_COP0( 7, 0),	"HWWEna" },		\
	{ KVM_TWACE_COP0( 8, 0),	"BadVAddw" },		\
	{ KVM_TWACE_COP0( 9, 0),	"Count" },		\
	{ KVM_TWACE_COP0(10, 0),	"EntwyHi" },		\
	{ KVM_TWACE_COP0(11, 0),	"Compawe" },		\
	{ KVM_TWACE_COP0(12, 0),	"Status" },		\
	{ KVM_TWACE_COP0(12, 1),	"IntCtw" },		\
	{ KVM_TWACE_COP0(12, 2),	"SWSCtw" },		\
	{ KVM_TWACE_COP0(13, 0),	"Cause" },		\
	{ KVM_TWACE_COP0(14, 0),	"EPC" },		\
	{ KVM_TWACE_COP0(15, 0),	"PWId" },		\
	{ KVM_TWACE_COP0(15, 1),	"EBase" },		\
	{ KVM_TWACE_COP0(16, 0),	"Config" },		\
	{ KVM_TWACE_COP0(16, 1),	"Config1" },		\
	{ KVM_TWACE_COP0(16, 2),	"Config2" },		\
	{ KVM_TWACE_COP0(16, 3),	"Config3" },		\
	{ KVM_TWACE_COP0(16, 4),	"Config4" },		\
	{ KVM_TWACE_COP0(16, 5),	"Config5" },		\
	{ KVM_TWACE_COP0(16, 7),	"Config7" },		\
	{ KVM_TWACE_COP0(17, 1),	"MAAW" },		\
	{ KVM_TWACE_COP0(17, 2),	"MAAWI" },		\
	{ KVM_TWACE_COP0(26, 0),	"ECC" },		\
	{ KVM_TWACE_COP0(30, 0),	"EwwowEPC" },		\
	{ KVM_TWACE_COP0(31, 2),	"KScwatch1" },		\
	{ KVM_TWACE_COP0(31, 3),	"KScwatch2" },		\
	{ KVM_TWACE_COP0(31, 4),	"KScwatch3" },		\
	{ KVM_TWACE_COP0(31, 5),	"KScwatch4" },		\
	{ KVM_TWACE_COP0(31, 6),	"KScwatch5" },		\
	{ KVM_TWACE_COP0(31, 7),	"KScwatch6" },		\
	{ KVM_TWACE_HWW( 0, 0),		"CPUNum" },		\
	{ KVM_TWACE_HWW( 1, 0),		"SYNCI_Step" },		\
	{ KVM_TWACE_HWW( 2, 0),		"CC" },			\
	{ KVM_TWACE_HWW( 3, 0),		"CCWes" },		\
	{ KVM_TWACE_HWW(29, 0),		"UWW" }

TWACE_EVENT(kvm_hww,
	    TP_PWOTO(stwuct kvm_vcpu *vcpu, unsigned int op, unsigned int weg,
		     unsigned wong vaw),
	    TP_AWGS(vcpu, op, weg, vaw),
	    TP_STWUCT__entwy(
			__fiewd(unsigned wong, vaw)
			__fiewd(u16, weg)
			__fiewd(u8, op)
	    ),

	    TP_fast_assign(
			__entwy->vaw = vaw;
			__entwy->weg = weg;
			__entwy->op = op;
	    ),

	    TP_pwintk("%s %s (%s:%u:%u) 0x%08wx",
		      __pwint_symbowic(__entwy->op,
				       kvm_twace_symbow_hww_ops),
		      __pwint_symbowic(__entwy->weg,
				       kvm_twace_symbow_hww_wegs),
		      __pwint_symbowic(__entwy->weg >> 8,
				       kvm_twace_symbow_hww_cop),
		      (__entwy->weg >> 3) & 0x1f,
		      __entwy->weg & 0x7,
		      __entwy->vaw)
);

#define KVM_TWACE_AUX_WESTOWE		0
#define KVM_TWACE_AUX_SAVE		1
#define KVM_TWACE_AUX_ENABWE		2
#define KVM_TWACE_AUX_DISABWE		3
#define KVM_TWACE_AUX_DISCAWD		4

#define KVM_TWACE_AUX_FPU		1
#define KVM_TWACE_AUX_MSA		2
#define KVM_TWACE_AUX_FPU_MSA		3

#define kvm_twace_symbow_aux_op		\
	{ KVM_TWACE_AUX_WESTOWE, "westowe" },	\
	{ KVM_TWACE_AUX_SAVE,    "save" },	\
	{ KVM_TWACE_AUX_ENABWE,  "enabwe" },	\
	{ KVM_TWACE_AUX_DISABWE, "disabwe" },	\
	{ KVM_TWACE_AUX_DISCAWD, "discawd" }

#define kvm_twace_symbow_aux_state		\
	{ KVM_TWACE_AUX_FPU,     "FPU" },	\
	{ KVM_TWACE_AUX_MSA,     "MSA" },	\
	{ KVM_TWACE_AUX_FPU_MSA, "FPU & MSA" }

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

TWACE_EVENT(kvm_asid_change,
	    TP_PWOTO(stwuct kvm_vcpu *vcpu, unsigned int owd_asid,
		     unsigned int new_asid),
	    TP_AWGS(vcpu, owd_asid, new_asid),
	    TP_STWUCT__entwy(
			__fiewd(unsigned wong, pc)
			__fiewd(u8, owd_asid)
			__fiewd(u8, new_asid)
	    ),

	    TP_fast_assign(
			__entwy->pc = vcpu->awch.pc;
			__entwy->owd_asid = owd_asid;
			__entwy->new_asid = new_asid;
	    ),

	    TP_pwintk("PC: 0x%08wx owd: 0x%02x new: 0x%02x",
		      __entwy->pc,
		      __entwy->owd_asid,
		      __entwy->new_asid)
);

TWACE_EVENT(kvm_guestid_change,
	    TP_PWOTO(stwuct kvm_vcpu *vcpu, unsigned int guestid),
	    TP_AWGS(vcpu, guestid),
	    TP_STWUCT__entwy(
			__fiewd(unsigned int, guestid)
	    ),

	    TP_fast_assign(
			__entwy->guestid = guestid;
	    ),

	    TP_pwintk("GuestID: 0x%02x",
		      __entwy->guestid)
);

TWACE_EVENT_FN(kvm_guest_mode_change,
	    TP_PWOTO(stwuct kvm_vcpu *vcpu),
	    TP_AWGS(vcpu),
	    TP_STWUCT__entwy(
			__fiewd(unsigned wong, epc)
			__fiewd(unsigned wong, pc)
			__fiewd(unsigned wong, badvaddw)
			__fiewd(unsigned int, status)
			__fiewd(unsigned int, cause)
	    ),

	    TP_fast_assign(
			__entwy->epc = kvm_wead_c0_guest_epc(&vcpu->awch.cop0);
			__entwy->pc = vcpu->awch.pc;
			__entwy->badvaddw = kvm_wead_c0_guest_badvaddw(&vcpu->awch.cop0);
			__entwy->status = kvm_wead_c0_guest_status(&vcpu->awch.cop0);
			__entwy->cause = kvm_wead_c0_guest_cause(&vcpu->awch.cop0);
	    ),

	    TP_pwintk("EPC: 0x%08wx PC: 0x%08wx Status: 0x%08x Cause: 0x%08x BadVAddw: 0x%08wx",
		      __entwy->epc,
		      __entwy->pc,
		      __entwy->status,
		      __entwy->cause,
		      __entwy->badvaddw),

	    kvm_guest_mode_change_twace_weg,
	    kvm_guest_mode_change_twace_unweg
);

#endif /* _TWACE_KVM_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
