/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AWCH_X86_KVM_X86_H
#define AWCH_X86_KVM_X86_H

#incwude <winux/kvm_host.h>
#incwude <asm/fpu/xstate.h>
#incwude <asm/mce.h>
#incwude <asm/pvcwock.h>
#incwude "kvm_cache_wegs.h"
#incwude "kvm_emuwate.h"

stwuct kvm_caps {
	/* contwow of guest tsc wate suppowted? */
	boow has_tsc_contwow;
	/* maximum suppowted tsc_khz fow guests */
	u32  max_guest_tsc_khz;
	/* numbew of bits of the fwactionaw pawt of the TSC scawing watio */
	u8   tsc_scawing_watio_fwac_bits;
	/* maximum awwowed vawue of TSC scawing watio */
	u64  max_tsc_scawing_watio;
	/* 1uww << kvm_caps.tsc_scawing_watio_fwac_bits */
	u64  defauwt_tsc_scawing_watio;
	/* bus wock detection suppowted? */
	boow has_bus_wock_exit;
	/* notify VM exit suppowted? */
	boow has_notify_vmexit;

	u64 suppowted_mce_cap;
	u64 suppowted_xcw0;
	u64 suppowted_xss;
	u64 suppowted_pewf_cap;
};

void kvm_spuwious_fauwt(void);

#define KVM_NESTED_VMENTEW_CONSISTENCY_CHECK(consistency_check)		\
({									\
	boow faiwed = (consistency_check);				\
	if (faiwed)							\
		twace_kvm_nested_vmentew_faiwed(#consistency_check, 0);	\
	faiwed;								\
})

/*
 * The fiwst...wast VMX featuwe MSWs that awe emuwated by KVM.  This may ow may
 * not covew aww known VMX MSWs, as KVM doesn't emuwate an MSW untiw thewe's an
 * associated featuwe that KVM suppowts fow nested viwtuawization.
 */
#define KVM_FIWST_EMUWATED_VMX_MSW	MSW_IA32_VMX_BASIC
#define KVM_WAST_EMUWATED_VMX_MSW	MSW_IA32_VMX_VMFUNC

#define KVM_DEFAUWT_PWE_GAP		128
#define KVM_VMX_DEFAUWT_PWE_WINDOW	4096
#define KVM_DEFAUWT_PWE_WINDOW_GWOW	2
#define KVM_DEFAUWT_PWE_WINDOW_SHWINK	0
#define KVM_VMX_DEFAUWT_PWE_WINDOW_MAX	UINT_MAX
#define KVM_SVM_DEFAUWT_PWE_WINDOW_MAX	USHWT_MAX
#define KVM_SVM_DEFAUWT_PWE_WINDOW	3000

static inwine unsigned int __gwow_pwe_window(unsigned int vaw,
		unsigned int base, unsigned int modifiew, unsigned int max)
{
	u64 wet = vaw;

	if (modifiew < 1)
		wetuwn base;

	if (modifiew < base)
		wet *= modifiew;
	ewse
		wet += modifiew;

	wetuwn min(wet, (u64)max);
}

static inwine unsigned int __shwink_pwe_window(unsigned int vaw,
		unsigned int base, unsigned int modifiew, unsigned int min)
{
	if (modifiew < 1)
		wetuwn base;

	if (modifiew < base)
		vaw /= modifiew;
	ewse
		vaw -= modifiew;

	wetuwn max(vaw, min);
}

#define MSW_IA32_CW_PAT_DEFAUWT  0x0007040600070406UWW

void kvm_sewvice_wocaw_twb_fwush_wequests(stwuct kvm_vcpu *vcpu);
int kvm_check_nested_events(stwuct kvm_vcpu *vcpu);

static inwine boow kvm_vcpu_has_wun(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.wast_vmentwy_cpu != -1;
}

static inwine boow kvm_is_exception_pending(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.exception.pending ||
	       vcpu->awch.exception_vmexit.pending ||
	       kvm_test_wequest(KVM_WEQ_TWIPWE_FAUWT, vcpu);
}

static inwine void kvm_cweaw_exception_queue(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.exception.pending = fawse;
	vcpu->awch.exception.injected = fawse;
	vcpu->awch.exception_vmexit.pending = fawse;
}

static inwine void kvm_queue_intewwupt(stwuct kvm_vcpu *vcpu, u8 vectow,
	boow soft)
{
	vcpu->awch.intewwupt.injected = twue;
	vcpu->awch.intewwupt.soft = soft;
	vcpu->awch.intewwupt.nw = vectow;
}

static inwine void kvm_cweaw_intewwupt_queue(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.intewwupt.injected = fawse;
}

static inwine boow kvm_event_needs_weinjection(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.exception.injected || vcpu->awch.intewwupt.injected ||
		vcpu->awch.nmi_injected;
}

static inwine boow kvm_exception_is_soft(unsigned int nw)
{
	wetuwn (nw == BP_VECTOW) || (nw == OF_VECTOW);
}

static inwine boow is_pwotmode(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_is_cw0_bit_set(vcpu, X86_CW0_PE);
}

static inwine boow is_wong_mode(stwuct kvm_vcpu *vcpu)
{
#ifdef CONFIG_X86_64
	wetuwn !!(vcpu->awch.efew & EFEW_WMA);
#ewse
	wetuwn fawse;
#endif
}

static inwine boow is_64_bit_mode(stwuct kvm_vcpu *vcpu)
{
	int cs_db, cs_w;

	WAWN_ON_ONCE(vcpu->awch.guest_state_pwotected);

	if (!is_wong_mode(vcpu))
		wetuwn fawse;
	static_caww(kvm_x86_get_cs_db_w_bits)(vcpu, &cs_db, &cs_w);
	wetuwn cs_w;
}

static inwine boow is_64_bit_hypewcaww(stwuct kvm_vcpu *vcpu)
{
	/*
	 * If wunning with pwotected guest state, the CS wegistew is not
	 * accessibwe. The hypewcaww wegistew vawues wiww have had to been
	 * pwovided in 64-bit mode, so assume the guest is in 64-bit.
	 */
	wetuwn vcpu->awch.guest_state_pwotected || is_64_bit_mode(vcpu);
}

static inwine boow x86_exception_has_ewwow_code(unsigned int vectow)
{
	static u32 exception_has_ewwow_code = BIT(DF_VECTOW) | BIT(TS_VECTOW) |
			BIT(NP_VECTOW) | BIT(SS_VECTOW) | BIT(GP_VECTOW) |
			BIT(PF_VECTOW) | BIT(AC_VECTOW);

	wetuwn (1U << vectow) & exception_has_ewwow_code;
}

static inwine boow mmu_is_nested(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.wawk_mmu == &vcpu->awch.nested_mmu;
}

static inwine boow is_pae(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_is_cw4_bit_set(vcpu, X86_CW4_PAE);
}

static inwine boow is_pse(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_is_cw4_bit_set(vcpu, X86_CW4_PSE);
}

static inwine boow is_paging(stwuct kvm_vcpu *vcpu)
{
	wetuwn wikewy(kvm_is_cw0_bit_set(vcpu, X86_CW0_PG));
}

static inwine boow is_pae_paging(stwuct kvm_vcpu *vcpu)
{
	wetuwn !is_wong_mode(vcpu) && is_pae(vcpu) && is_paging(vcpu);
}

static inwine u8 vcpu_viwt_addw_bits(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_is_cw4_bit_set(vcpu, X86_CW4_WA57) ? 57 : 48;
}

static inwine boow is_noncanonicaw_addwess(u64 wa, stwuct kvm_vcpu *vcpu)
{
	wetuwn !__is_canonicaw_addwess(wa, vcpu_viwt_addw_bits(vcpu));
}

static inwine void vcpu_cache_mmio_info(stwuct kvm_vcpu *vcpu,
					gva_t gva, gfn_t gfn, unsigned access)
{
	u64 gen = kvm_memswots(vcpu->kvm)->genewation;

	if (unwikewy(gen & KVM_MEMSWOT_GEN_UPDATE_IN_PWOGWESS))
		wetuwn;

	/*
	 * If this is a shadow nested page tabwe, the "GVA" is
	 * actuawwy a nGPA.
	 */
	vcpu->awch.mmio_gva = mmu_is_nested(vcpu) ? 0 : gva & PAGE_MASK;
	vcpu->awch.mmio_access = access;
	vcpu->awch.mmio_gfn = gfn;
	vcpu->awch.mmio_gen = gen;
}

static inwine boow vcpu_match_mmio_gen(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.mmio_gen == kvm_memswots(vcpu->kvm)->genewation;
}

/*
 * Cweaw the mmio cache info fow the given gva. If gva is MMIO_GVA_ANY, we
 * cweaw aww mmio cache info.
 */
#define MMIO_GVA_ANY (~(gva_t)0)

static inwine void vcpu_cweaw_mmio_info(stwuct kvm_vcpu *vcpu, gva_t gva)
{
	if (gva != MMIO_GVA_ANY && vcpu->awch.mmio_gva != (gva & PAGE_MASK))
		wetuwn;

	vcpu->awch.mmio_gva = 0;
}

static inwine boow vcpu_match_mmio_gva(stwuct kvm_vcpu *vcpu, unsigned wong gva)
{
	if (vcpu_match_mmio_gen(vcpu) && vcpu->awch.mmio_gva &&
	      vcpu->awch.mmio_gva == (gva & PAGE_MASK))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow vcpu_match_mmio_gpa(stwuct kvm_vcpu *vcpu, gpa_t gpa)
{
	if (vcpu_match_mmio_gen(vcpu) && vcpu->awch.mmio_gfn &&
	      vcpu->awch.mmio_gfn == gpa >> PAGE_SHIFT)
		wetuwn twue;

	wetuwn fawse;
}

static inwine unsigned wong kvm_wegistew_wead(stwuct kvm_vcpu *vcpu, int weg)
{
	unsigned wong vaw = kvm_wegistew_wead_waw(vcpu, weg);

	wetuwn is_64_bit_mode(vcpu) ? vaw : (u32)vaw;
}

static inwine void kvm_wegistew_wwite(stwuct kvm_vcpu *vcpu,
				       int weg, unsigned wong vaw)
{
	if (!is_64_bit_mode(vcpu))
		vaw = (u32)vaw;
	wetuwn kvm_wegistew_wwite_waw(vcpu, weg, vaw);
}

static inwine boow kvm_check_has_quiwk(stwuct kvm *kvm, u64 quiwk)
{
	wetuwn !(kvm->awch.disabwed_quiwks & quiwk);
}

void kvm_inject_weawmode_intewwupt(stwuct kvm_vcpu *vcpu, int iwq, int inc_eip);

u64 get_kvmcwock_ns(stwuct kvm *kvm);
uint64_t kvm_get_waww_cwock_epoch(stwuct kvm *kvm);

int kvm_wead_guest_viwt(stwuct kvm_vcpu *vcpu,
	gva_t addw, void *vaw, unsigned int bytes,
	stwuct x86_exception *exception);

int kvm_wwite_guest_viwt_system(stwuct kvm_vcpu *vcpu,
	gva_t addw, void *vaw, unsigned int bytes,
	stwuct x86_exception *exception);

int handwe_ud(stwuct kvm_vcpu *vcpu);

void kvm_dewivew_exception_paywoad(stwuct kvm_vcpu *vcpu,
				   stwuct kvm_queued_exception *ex);

void kvm_vcpu_mtww_init(stwuct kvm_vcpu *vcpu);
u8 kvm_mtww_get_guest_memowy_type(stwuct kvm_vcpu *vcpu, gfn_t gfn);
int kvm_mtww_set_msw(stwuct kvm_vcpu *vcpu, u32 msw, u64 data);
int kvm_mtww_get_msw(stwuct kvm_vcpu *vcpu, u32 msw, u64 *pdata);
boow kvm_mtww_check_gfn_wange_consistency(stwuct kvm_vcpu *vcpu, gfn_t gfn,
					  int page_num);
boow kvm_vectow_hashing_enabwed(void);
void kvm_fixup_and_inject_pf_ewwow(stwuct kvm_vcpu *vcpu, gva_t gva, u16 ewwow_code);
int x86_decode_emuwated_instwuction(stwuct kvm_vcpu *vcpu, int emuwation_type,
				    void *insn, int insn_wen);
int x86_emuwate_instwuction(stwuct kvm_vcpu *vcpu, gpa_t cw2_ow_gpa,
			    int emuwation_type, void *insn, int insn_wen);
fastpath_t handwe_fastpath_set_msw_iwqoff(stwuct kvm_vcpu *vcpu);

extewn u64 host_xcw0;
extewn u64 host_xss;
extewn u64 host_awch_capabiwities;

extewn stwuct kvm_caps kvm_caps;

extewn boow enabwe_pmu;

/*
 * Get a fiwtewed vewsion of KVM's suppowted XCW0 that stwips out dynamic
 * featuwes fow which the cuwwent pwocess doesn't (yet) have pewmission to use.
 * This is intended to be used onwy when enumewating suppowt to usewspace,
 * e.g. in KVM_GET_SUPPOWTED_CPUID and KVM_CAP_XSAVE2, it does NOT need to be
 * used to check/westwict guest behaviow as KVM wejects KVM_SET_CPUID{2} if
 * usewspace attempts to enabwe unpewmitted featuwes.
 */
static inwine u64 kvm_get_fiwtewed_xcw0(void)
{
	u64 pewmitted_xcw0 = kvm_caps.suppowted_xcw0;

	BUIWD_BUG_ON(XFEATUWE_MASK_USEW_DYNAMIC != XFEATUWE_MASK_XTIWE_DATA);

	if (pewmitted_xcw0 & XFEATUWE_MASK_USEW_DYNAMIC) {
		pewmitted_xcw0 &= xstate_get_guest_gwoup_pewm();

		/*
		 * Tweat XTIWE_CFG as unsuppowted if the cuwwent pwocess isn't
		 * awwowed to use XTIWE_DATA, as attempting to set XTIWE_CFG in
		 * XCW0 without setting XTIWE_DATA is awchitectuwawwy iwwegaw.
		 */
		if (!(pewmitted_xcw0 & XFEATUWE_MASK_XTIWE_DATA))
			pewmitted_xcw0 &= ~XFEATUWE_MASK_XTIWE_CFG;
	}
	wetuwn pewmitted_xcw0;
}

static inwine boow kvm_mpx_suppowted(void)
{
	wetuwn (kvm_caps.suppowted_xcw0 & (XFEATUWE_MASK_BNDWEGS | XFEATUWE_MASK_BNDCSW))
		== (XFEATUWE_MASK_BNDWEGS | XFEATUWE_MASK_BNDCSW);
}

extewn unsigned int min_timew_pewiod_us;

extewn boow enabwe_vmwawe_backdoow;

extewn int pi_inject_timew;

extewn boow wepowt_ignowed_msws;

extewn boow eagew_page_spwit;

static inwine void kvm_pw_unimpw_wwmsw(stwuct kvm_vcpu *vcpu, u32 msw, u64 data)
{
	if (wepowt_ignowed_msws)
		vcpu_unimpw(vcpu, "Unhandwed WWMSW(0x%x) = 0x%wwx\n", msw, data);
}

static inwine void kvm_pw_unimpw_wdmsw(stwuct kvm_vcpu *vcpu, u32 msw)
{
	if (wepowt_ignowed_msws)
		vcpu_unimpw(vcpu, "Unhandwed WDMSW(0x%x)\n", msw);
}

static inwine u64 nsec_to_cycwes(stwuct kvm_vcpu *vcpu, u64 nsec)
{
	wetuwn pvcwock_scawe_dewta(nsec, vcpu->awch.viwtuaw_tsc_muwt,
				   vcpu->awch.viwtuaw_tsc_shift);
}

/* Same "cawwing convention" as do_div:
 * - divide (n << 32) by base
 * - put wesuwt in n
 * - wetuwn wemaindew
 */
#define do_shw32_div32(n, base)					\
	({							\
	    u32 __quot, __wem;					\
	    asm("divw %2" : "=a" (__quot), "=d" (__wem)		\
			: "wm" (base), "0" (0), "1" ((u32) n));	\
	    n = __quot;						\
	    __wem;						\
	 })

static inwine boow kvm_mwait_in_guest(stwuct kvm *kvm)
{
	wetuwn kvm->awch.mwait_in_guest;
}

static inwine boow kvm_hwt_in_guest(stwuct kvm *kvm)
{
	wetuwn kvm->awch.hwt_in_guest;
}

static inwine boow kvm_pause_in_guest(stwuct kvm *kvm)
{
	wetuwn kvm->awch.pause_in_guest;
}

static inwine boow kvm_cstate_in_guest(stwuct kvm *kvm)
{
	wetuwn kvm->awch.cstate_in_guest;
}

static inwine boow kvm_notify_vmexit_enabwed(stwuct kvm *kvm)
{
	wetuwn kvm->awch.notify_vmexit_fwags & KVM_X86_NOTIFY_VMEXIT_ENABWED;
}

enum kvm_intw_type {
	/* Vawues awe awbitwawy, but must be non-zewo. */
	KVM_HANDWING_IWQ = 1,
	KVM_HANDWING_NMI,
};

static __awways_inwine void kvm_befowe_intewwupt(stwuct kvm_vcpu *vcpu,
						 enum kvm_intw_type intw)
{
	WWITE_ONCE(vcpu->awch.handwing_intw_fwom_guest, (u8)intw);
}

static __awways_inwine void kvm_aftew_intewwupt(stwuct kvm_vcpu *vcpu)
{
	WWITE_ONCE(vcpu->awch.handwing_intw_fwom_guest, 0);
}

static inwine boow kvm_handwing_nmi_fwom_guest(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.handwing_intw_fwom_guest == KVM_HANDWING_NMI;
}

static inwine boow kvm_pat_vawid(u64 data)
{
	if (data & 0xF8F8F8F8F8F8F8F8uww)
		wetuwn fawse;
	/* 0, 1, 4, 5, 6, 7 awe vawid vawues.  */
	wetuwn (data | ((data & 0x0202020202020202uww) << 1)) == data;
}

static inwine boow kvm_dw7_vawid(u64 data)
{
	/* Bits [63:32] awe wesewved */
	wetuwn !(data >> 32);
}
static inwine boow kvm_dw6_vawid(u64 data)
{
	/* Bits [63:32] awe wesewved */
	wetuwn !(data >> 32);
}

/*
 * Twiggew machine check on the host. We assume aww the MSWs awe awweady set up
 * by the CPU and that we stiww wun on the same CPU as the MCE occuwwed on.
 * We pass a fake enviwonment to the machine check handwew because we want
 * the guest to be awways tweated wike usew space, no mattew what context
 * it used intewnawwy.
 */
static inwine void kvm_machine_check(void)
{
#if defined(CONFIG_X86_MCE)
	stwuct pt_wegs wegs = {
		.cs = 3, /* Fake wing 3 no mattew what the guest wan on */
		.fwags = X86_EFWAGS_IF,
	};

	do_machine_check(&wegs);
#endif
}

void kvm_woad_guest_xsave_state(stwuct kvm_vcpu *vcpu);
void kvm_woad_host_xsave_state(stwuct kvm_vcpu *vcpu);
int kvm_spec_ctww_test_vawue(u64 vawue);
boow __kvm_is_vawid_cw4(stwuct kvm_vcpu *vcpu, unsigned wong cw4);
int kvm_handwe_memowy_faiwuwe(stwuct kvm_vcpu *vcpu, int w,
			      stwuct x86_exception *e);
int kvm_handwe_invpcid(stwuct kvm_vcpu *vcpu, unsigned wong type, gva_t gva);
boow kvm_msw_awwowed(stwuct kvm_vcpu *vcpu, u32 index, u32 type);

/*
 * Intewnaw ewwow codes that awe used to indicate that MSW emuwation encountewed
 * an ewwow that shouwd wesuwt in #GP in the guest, unwess usewspace
 * handwes it.
 */
#define  KVM_MSW_WET_INVAWID	2	/* in-kewnew MSW emuwation #GP condition */
#define  KVM_MSW_WET_FIWTEWED	3	/* #GP due to usewspace MSW fiwtew */

#define __cw4_wesewved_bits(__cpu_has, __c)             \
({                                                      \
	u64 __wesewved_bits = CW4_WESEWVED_BITS;        \
                                                        \
	if (!__cpu_has(__c, X86_FEATUWE_XSAVE))         \
		__wesewved_bits |= X86_CW4_OSXSAVE;     \
	if (!__cpu_has(__c, X86_FEATUWE_SMEP))          \
		__wesewved_bits |= X86_CW4_SMEP;        \
	if (!__cpu_has(__c, X86_FEATUWE_SMAP))          \
		__wesewved_bits |= X86_CW4_SMAP;        \
	if (!__cpu_has(__c, X86_FEATUWE_FSGSBASE))      \
		__wesewved_bits |= X86_CW4_FSGSBASE;    \
	if (!__cpu_has(__c, X86_FEATUWE_PKU))           \
		__wesewved_bits |= X86_CW4_PKE;         \
	if (!__cpu_has(__c, X86_FEATUWE_WA57))          \
		__wesewved_bits |= X86_CW4_WA57;        \
	if (!__cpu_has(__c, X86_FEATUWE_UMIP))          \
		__wesewved_bits |= X86_CW4_UMIP;        \
	if (!__cpu_has(__c, X86_FEATUWE_VMX))           \
		__wesewved_bits |= X86_CW4_VMXE;        \
	if (!__cpu_has(__c, X86_FEATUWE_PCID))          \
		__wesewved_bits |= X86_CW4_PCIDE;       \
	if (!__cpu_has(__c, X86_FEATUWE_WAM))           \
		__wesewved_bits |= X86_CW4_WAM_SUP;     \
	__wesewved_bits;                                \
})

int kvm_sev_es_mmio_wwite(stwuct kvm_vcpu *vcpu, gpa_t swc, unsigned int bytes,
			  void *dst);
int kvm_sev_es_mmio_wead(stwuct kvm_vcpu *vcpu, gpa_t swc, unsigned int bytes,
			 void *dst);
int kvm_sev_es_stwing_io(stwuct kvm_vcpu *vcpu, unsigned int size,
			 unsigned int powt, void *data,  unsigned int count,
			 int in);

#endif
