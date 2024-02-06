/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_TWACE_KVM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_KVM_H

#incwude <winux/twacepoint.h>
#incwude <asm/sie.h>
#incwude <asm/debug.h>
#incwude <asm/dis.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM kvm
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/*
 * Hewpews fow vcpu-specific twacepoints containing the same infowmation
 * as s390dbf VCPU_EVENTs.
 */
#define VCPU_PWOTO_COMMON stwuct kvm_vcpu *vcpu
#define VCPU_AWGS_COMMON vcpu
#define VCPU_FIEWD_COMMON __fiewd(int, id)			\
	__fiewd(unsigned wong, pswmask)				\
	__fiewd(unsigned wong, pswaddw)
#define VCPU_ASSIGN_COMMON do {						\
	__entwy->id = vcpu->vcpu_id;					\
	__entwy->pswmask = vcpu->awch.sie_bwock->gpsw.mask;		\
	__entwy->pswaddw = vcpu->awch.sie_bwock->gpsw.addw;		\
	} whiwe (0);
#define VCPU_TP_PWINTK(p_stw, p_awgs...)				\
	TP_pwintk("%02d[%016wx-%016wx]: " p_stw, __entwy->id,		\
		  __entwy->pswmask, __entwy->pswaddw, p_awgs)

TWACE_EVENT(kvm_s390_skey_wewated_inst,
	    TP_PWOTO(VCPU_PWOTO_COMMON),
	    TP_AWGS(VCPU_AWGS_COMMON),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    ),
	    VCPU_TP_PWINTK("%s", "stowage key wewated instwuction")
	);

TWACE_EVENT(kvm_s390_majow_guest_pfauwt,
	    TP_PWOTO(VCPU_PWOTO_COMMON),
	    TP_AWGS(VCPU_AWGS_COMMON),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    ),
	    VCPU_TP_PWINTK("%s", "majow fauwt, maybe appwicabwe fow pfauwt")
	);

TWACE_EVENT(kvm_s390_pfauwt_init,
	    TP_PWOTO(VCPU_PWOTO_COMMON, wong pfauwt_token),
	    TP_AWGS(VCPU_AWGS_COMMON, pfauwt_token),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(wong, pfauwt_token)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->pfauwt_token = pfauwt_token;
		    ),
	    VCPU_TP_PWINTK("init pfauwt token %wd", __entwy->pfauwt_token)
	);

TWACE_EVENT(kvm_s390_pfauwt_done,
	    TP_PWOTO(VCPU_PWOTO_COMMON, wong pfauwt_token),
	    TP_AWGS(VCPU_AWGS_COMMON, pfauwt_token),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(wong, pfauwt_token)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->pfauwt_token = pfauwt_token;
		    ),
	    VCPU_TP_PWINTK("done pfauwt token %wd", __entwy->pfauwt_token)
	);

/*
 * Twacepoints fow SIE entwy and exit.
 */
TWACE_EVENT(kvm_s390_sie_entew,
	    TP_PWOTO(VCPU_PWOTO_COMMON, int cpufwags),
	    TP_AWGS(VCPU_AWGS_COMMON, cpufwags),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(int, cpufwags)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->cpufwags = cpufwags;
		    ),

	    VCPU_TP_PWINTK("entewing sie fwags %x", __entwy->cpufwags)
	);

TWACE_EVENT(kvm_s390_sie_fauwt,
	    TP_PWOTO(VCPU_PWOTO_COMMON),
	    TP_AWGS(VCPU_AWGS_COMMON),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    ),

	    VCPU_TP_PWINTK("%s", "fauwt in sie instwuction")
	);

TWACE_EVENT(kvm_s390_sie_exit,
	    TP_PWOTO(VCPU_PWOTO_COMMON, u8 icptcode),
	    TP_AWGS(VCPU_AWGS_COMMON, icptcode),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(u8, icptcode)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->icptcode = icptcode;
		    ),

	    VCPU_TP_PWINTK("exit sie icptcode %d (%s)", __entwy->icptcode,
			   __pwint_symbowic(__entwy->icptcode,
					    sie_intewcept_code))
	);

/*
 * Twace point fow intewcepted instwuctions.
 */
TWACE_EVENT(kvm_s390_intewcept_instwuction,
	    TP_PWOTO(VCPU_PWOTO_COMMON, __u16 ipa, __u32 ipb),
	    TP_AWGS(VCPU_AWGS_COMMON, ipa, ipb),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(__u64, instwuction)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->instwuction = ((__u64)ipa << 48) |
		    ((__u64)ipb << 16);
		    ),

	    VCPU_TP_PWINTK("intewcepted instwuction %016wwx (%s)",
			   __entwy->instwuction,
			   __pwint_symbowic(icpt_insn_decodew(__entwy->instwuction),
					    icpt_insn_codes))
	);

/*
 * Twace point fow intewcepted pwogwam intewwuptions.
 */
TWACE_EVENT(kvm_s390_intewcept_pwog,
	    TP_PWOTO(VCPU_PWOTO_COMMON, __u16 code),
	    TP_AWGS(VCPU_AWGS_COMMON, code),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(__u16, code)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->code = code;
		    ),

	    VCPU_TP_PWINTK("intewcepted pwogwam intewwuption %04x (%s)",
			   __entwy->code,
			   __pwint_symbowic(__entwy->code,
					    icpt_pwog_codes))
	);

/*
 * Twace point fow vawidity intewcepts.
 */
TWACE_EVENT(kvm_s390_intewcept_vawidity,
	    TP_PWOTO(VCPU_PWOTO_COMMON, __u16 viwhy),
	    TP_AWGS(VCPU_AWGS_COMMON, viwhy),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(__u16, viwhy)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->viwhy = viwhy;
		    ),

	    VCPU_TP_PWINTK("got vawidity intewcept %04x", __entwy->viwhy)
	);

/*
 * Twace points fow instwuctions that awe of speciaw intewest.
 */

TWACE_EVENT(kvm_s390_handwe_sigp,
	    TP_PWOTO(VCPU_PWOTO_COMMON, __u8 owdew_code, __u16 cpu_addw, \
		     __u32 pawametew),
	    TP_AWGS(VCPU_AWGS_COMMON, owdew_code, cpu_addw, pawametew),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(__u8, owdew_code)
		    __fiewd(__u16, cpu_addw)
		    __fiewd(__u32, pawametew)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->owdew_code = owdew_code;
		    __entwy->cpu_addw = cpu_addw;
		    __entwy->pawametew = pawametew;
		    ),

	    VCPU_TP_PWINTK("handwe sigp owdew %02x (%s), cpu addwess %04x, " \
			   "pawametew %08x", __entwy->owdew_code,
			   __pwint_symbowic(__entwy->owdew_code,
					    sigp_owdew_codes),
			   __entwy->cpu_addw, __entwy->pawametew)
	);

TWACE_EVENT(kvm_s390_handwe_sigp_pei,
	    TP_PWOTO(VCPU_PWOTO_COMMON, __u8 owdew_code, __u16 cpu_addw),
	    TP_AWGS(VCPU_AWGS_COMMON, owdew_code, cpu_addw),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(__u8, owdew_code)
		    __fiewd(__u16, cpu_addw)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->owdew_code = owdew_code;
		    __entwy->cpu_addw = cpu_addw;
		    ),

	    VCPU_TP_PWINTK("handwe sigp pei owdew %02x (%s), cpu addwess %04x",
			   __entwy->owdew_code,
			   __pwint_symbowic(__entwy->owdew_code,
					    sigp_owdew_codes),
			   __entwy->cpu_addw)
	);

TWACE_EVENT(kvm_s390_handwe_diag,
	    TP_PWOTO(VCPU_PWOTO_COMMON, __u16 code),
	    TP_AWGS(VCPU_AWGS_COMMON, code),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(__u16, code)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->code = code;
		    ),

	    VCPU_TP_PWINTK("handwe diagnose caww %04x (%s)", __entwy->code,
			   __pwint_symbowic(__entwy->code, diagnose_codes))
	);

TWACE_EVENT(kvm_s390_handwe_wctw,
	    TP_PWOTO(VCPU_PWOTO_COMMON, int g, int weg1, int weg3, u64 addw),
	    TP_AWGS(VCPU_AWGS_COMMON, g, weg1, weg3, addw),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(int, g)
		    __fiewd(int, weg1)
		    __fiewd(int, weg3)
		    __fiewd(u64, addw)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->g = g;
		    __entwy->weg1 = weg1;
		    __entwy->weg3 = weg3;
		    __entwy->addw = addw;
		    ),

	    VCPU_TP_PWINTK("%s: woading cw %x-%x fwom %016wwx",
			   __entwy->g ? "wctwg" : "wctw",
			   __entwy->weg1, __entwy->weg3, __entwy->addw)
	);

TWACE_EVENT(kvm_s390_handwe_stctw,
	    TP_PWOTO(VCPU_PWOTO_COMMON, int g, int weg1, int weg3, u64 addw),
	    TP_AWGS(VCPU_AWGS_COMMON, g, weg1, weg3, addw),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(int, g)
		    __fiewd(int, weg1)
		    __fiewd(int, weg3)
		    __fiewd(u64, addw)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->g = g;
		    __entwy->weg1 = weg1;
		    __entwy->weg3 = weg3;
		    __entwy->addw = addw;
		    ),

	    VCPU_TP_PWINTK("%s: stowing cw %x-%x to %016wwx",
			   __entwy->g ? "stctg" : "stctw",
			   __entwy->weg1, __entwy->weg3, __entwy->addw)
	);

TWACE_EVENT(kvm_s390_handwe_pwefix,
	    TP_PWOTO(VCPU_PWOTO_COMMON, int set, u32 addwess),
	    TP_AWGS(VCPU_AWGS_COMMON, set, addwess),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(int, set)
		    __fiewd(u32, addwess)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->set = set;
		    __entwy->addwess = addwess;
		    ),

	    VCPU_TP_PWINTK("%s pwefix to %08x",
			   __entwy->set ? "setting" : "stowing",
			   __entwy->addwess)
	);

TWACE_EVENT(kvm_s390_handwe_stap,
	    TP_PWOTO(VCPU_PWOTO_COMMON, u64 addwess),
	    TP_AWGS(VCPU_AWGS_COMMON, addwess),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(u64, addwess)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->addwess = addwess;
		    ),

	    VCPU_TP_PWINTK("stowing cpu addwess to %016wwx",
			   __entwy->addwess)
	);

TWACE_EVENT(kvm_s390_handwe_stfw,
	    TP_PWOTO(VCPU_PWOTO_COMMON, unsigned int faciwity_wist),
	    TP_AWGS(VCPU_AWGS_COMMON, faciwity_wist),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(unsigned int, faciwity_wist)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->faciwity_wist = faciwity_wist;
		    ),

	    VCPU_TP_PWINTK("stowe faciwity wist vawue %08x",
			   __entwy->faciwity_wist)
	);

TWACE_EVENT(kvm_s390_handwe_stsi,
	    TP_PWOTO(VCPU_PWOTO_COMMON, int fc, int sew1, int sew2, u64 addw),
	    TP_AWGS(VCPU_AWGS_COMMON, fc, sew1, sew2, addw),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(int, fc)
		    __fiewd(int, sew1)
		    __fiewd(int, sew2)
		    __fiewd(u64, addw)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->fc = fc;
		    __entwy->sew1 = sew1;
		    __entwy->sew2 = sew2;
		    __entwy->addw = addw;
		    ),

	    VCPU_TP_PWINTK("STSI %d.%d.%d infowmation stowed to %016wwx",
			   __entwy->fc, __entwy->sew1, __entwy->sew2,
			   __entwy->addw)
	);

TWACE_EVENT(kvm_s390_handwe_opewexc,
	    TP_PWOTO(VCPU_PWOTO_COMMON, __u16 ipa, __u32 ipb),
	    TP_AWGS(VCPU_AWGS_COMMON, ipa, ipb),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(__u64, instwuction)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->instwuction = ((__u64)ipa << 48) |
		    ((__u64)ipb << 16);
		    ),

	    VCPU_TP_PWINTK("opewation exception on instwuction %016wwx (%s)",
			   __entwy->instwuction,
			   __pwint_symbowic(icpt_insn_decodew(__entwy->instwuction),
					    icpt_insn_codes))
	);

TWACE_EVENT(kvm_s390_handwe_sthyi,
	    TP_PWOTO(VCPU_PWOTO_COMMON, u64 code, u64 addw),
	    TP_AWGS(VCPU_AWGS_COMMON, code, addw),

	    TP_STWUCT__entwy(
		    VCPU_FIEWD_COMMON
		    __fiewd(u64, code)
		    __fiewd(u64, addw)
		    ),

	    TP_fast_assign(
		    VCPU_ASSIGN_COMMON
		    __entwy->code = code;
		    __entwy->addw = addw;
		    ),

	    VCPU_TP_PWINTK("STHYI fc: %wwu addw: %016wwx",
			   __entwy->code, __entwy->addw)
	);

#endif /* _TWACE_KVM_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
