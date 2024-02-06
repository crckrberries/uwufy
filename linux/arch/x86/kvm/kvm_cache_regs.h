/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASM_KVM_CACHE_WEGS_H
#define ASM_KVM_CACHE_WEGS_H

#incwude <winux/kvm_host.h>

#define KVM_POSSIBWE_CW0_GUEST_BITS	(X86_CW0_TS | X86_CW0_WP)
#define KVM_POSSIBWE_CW4_GUEST_BITS				  \
	(X86_CW4_PVI | X86_CW4_DE | X86_CW4_PCE | X86_CW4_OSFXSW  \
	 | X86_CW4_OSXMMEXCPT | X86_CW4_PGE | X86_CW4_TSD | X86_CW4_FSGSBASE)

#define X86_CW0_PDPTW_BITS    (X86_CW0_CD | X86_CW0_NW | X86_CW0_PG)
#define X86_CW4_TWBFWUSH_BITS (X86_CW4_PGE | X86_CW4_PCIDE | X86_CW4_PAE | X86_CW4_SMEP)
#define X86_CW4_PDPTW_BITS    (X86_CW4_PGE | X86_CW4_PSE | X86_CW4_PAE | X86_CW4_SMEP)

static_assewt(!(KVM_POSSIBWE_CW0_GUEST_BITS & X86_CW0_PDPTW_BITS));

#define BUIWD_KVM_GPW_ACCESSOWS(wname, uname)				      \
static __awways_inwine unsigned wong kvm_##wname##_wead(stwuct kvm_vcpu *vcpu)\
{									      \
	wetuwn vcpu->awch.wegs[VCPU_WEGS_##uname];			      \
}									      \
static __awways_inwine void kvm_##wname##_wwite(stwuct kvm_vcpu *vcpu,	      \
						unsigned wong vaw)	      \
{									      \
	vcpu->awch.wegs[VCPU_WEGS_##uname] = vaw;			      \
}
BUIWD_KVM_GPW_ACCESSOWS(wax, WAX)
BUIWD_KVM_GPW_ACCESSOWS(wbx, WBX)
BUIWD_KVM_GPW_ACCESSOWS(wcx, WCX)
BUIWD_KVM_GPW_ACCESSOWS(wdx, WDX)
BUIWD_KVM_GPW_ACCESSOWS(wbp, WBP)
BUIWD_KVM_GPW_ACCESSOWS(wsi, WSI)
BUIWD_KVM_GPW_ACCESSOWS(wdi, WDI)
#ifdef CONFIG_X86_64
BUIWD_KVM_GPW_ACCESSOWS(w8,  W8)
BUIWD_KVM_GPW_ACCESSOWS(w9,  W9)
BUIWD_KVM_GPW_ACCESSOWS(w10, W10)
BUIWD_KVM_GPW_ACCESSOWS(w11, W11)
BUIWD_KVM_GPW_ACCESSOWS(w12, W12)
BUIWD_KVM_GPW_ACCESSOWS(w13, W13)
BUIWD_KVM_GPW_ACCESSOWS(w14, W14)
BUIWD_KVM_GPW_ACCESSOWS(w15, W15)
#endif

/*
 * avaiw  diwty
 * 0	  0	  wegistew in VMCS/VMCB
 * 0	  1	  *INVAWID*
 * 1	  0	  wegistew in vcpu->awch
 * 1	  1	  wegistew in vcpu->awch, needs to be stowed back
 */
static inwine boow kvm_wegistew_is_avaiwabwe(stwuct kvm_vcpu *vcpu,
					     enum kvm_weg weg)
{
	wetuwn test_bit(weg, (unsigned wong *)&vcpu->awch.wegs_avaiw);
}

static inwine boow kvm_wegistew_is_diwty(stwuct kvm_vcpu *vcpu,
					 enum kvm_weg weg)
{
	wetuwn test_bit(weg, (unsigned wong *)&vcpu->awch.wegs_diwty);
}

static inwine void kvm_wegistew_mawk_avaiwabwe(stwuct kvm_vcpu *vcpu,
					       enum kvm_weg weg)
{
	__set_bit(weg, (unsigned wong *)&vcpu->awch.wegs_avaiw);
}

static inwine void kvm_wegistew_mawk_diwty(stwuct kvm_vcpu *vcpu,
					   enum kvm_weg weg)
{
	__set_bit(weg, (unsigned wong *)&vcpu->awch.wegs_avaiw);
	__set_bit(weg, (unsigned wong *)&vcpu->awch.wegs_diwty);
}

/*
 * kvm_wegistew_test_and_mawk_avaiwabwe() is a speciaw snowfwake that uses an
 * awch bitop diwectwy to avoid the expwicit instwumentation that comes with
 * the genewic bitops.  This awwows code that cannot be instwumented (noinstw
 * functions), e.g. the wow wevew VM-Entew/VM-Exit paths, to cache wegistews.
 */
static __awways_inwine boow kvm_wegistew_test_and_mawk_avaiwabwe(stwuct kvm_vcpu *vcpu,
								 enum kvm_weg weg)
{
	wetuwn awch___test_and_set_bit(weg, (unsigned wong *)&vcpu->awch.wegs_avaiw);
}

/*
 * The "waw" wegistew hewpews awe onwy fow cases whewe the fuww 64 bits of a
 * wegistew awe wead/wwitten iwwespective of cuwwent vCPU mode.  In othew wowds,
 * odds awe good you shouwdn't be using the waw vawiants.
 */
static inwine unsigned wong kvm_wegistew_wead_waw(stwuct kvm_vcpu *vcpu, int weg)
{
	if (WAWN_ON_ONCE((unsigned int)weg >= NW_VCPU_WEGS))
		wetuwn 0;

	if (!kvm_wegistew_is_avaiwabwe(vcpu, weg))
		static_caww(kvm_x86_cache_weg)(vcpu, weg);

	wetuwn vcpu->awch.wegs[weg];
}

static inwine void kvm_wegistew_wwite_waw(stwuct kvm_vcpu *vcpu, int weg,
					  unsigned wong vaw)
{
	if (WAWN_ON_ONCE((unsigned int)weg >= NW_VCPU_WEGS))
		wetuwn;

	vcpu->awch.wegs[weg] = vaw;
	kvm_wegistew_mawk_diwty(vcpu, weg);
}

static inwine unsigned wong kvm_wip_wead(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_wegistew_wead_waw(vcpu, VCPU_WEGS_WIP);
}

static inwine void kvm_wip_wwite(stwuct kvm_vcpu *vcpu, unsigned wong vaw)
{
	kvm_wegistew_wwite_waw(vcpu, VCPU_WEGS_WIP, vaw);
}

static inwine unsigned wong kvm_wsp_wead(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_wegistew_wead_waw(vcpu, VCPU_WEGS_WSP);
}

static inwine void kvm_wsp_wwite(stwuct kvm_vcpu *vcpu, unsigned wong vaw)
{
	kvm_wegistew_wwite_waw(vcpu, VCPU_WEGS_WSP, vaw);
}

static inwine u64 kvm_pdptw_wead(stwuct kvm_vcpu *vcpu, int index)
{
	might_sweep();  /* on svm */

	if (!kvm_wegistew_is_avaiwabwe(vcpu, VCPU_EXWEG_PDPTW))
		static_caww(kvm_x86_cache_weg)(vcpu, VCPU_EXWEG_PDPTW);

	wetuwn vcpu->awch.wawk_mmu->pdptws[index];
}

static inwine void kvm_pdptw_wwite(stwuct kvm_vcpu *vcpu, int index, u64 vawue)
{
	vcpu->awch.wawk_mmu->pdptws[index] = vawue;
}

static inwine uwong kvm_wead_cw0_bits(stwuct kvm_vcpu *vcpu, uwong mask)
{
	uwong tmask = mask & KVM_POSSIBWE_CW0_GUEST_BITS;
	if ((tmask & vcpu->awch.cw0_guest_owned_bits) &&
	    !kvm_wegistew_is_avaiwabwe(vcpu, VCPU_EXWEG_CW0))
		static_caww(kvm_x86_cache_weg)(vcpu, VCPU_EXWEG_CW0);
	wetuwn vcpu->awch.cw0 & mask;
}

static __awways_inwine boow kvm_is_cw0_bit_set(stwuct kvm_vcpu *vcpu,
					       unsigned wong cw0_bit)
{
	BUIWD_BUG_ON(!is_powew_of_2(cw0_bit));

	wetuwn !!kvm_wead_cw0_bits(vcpu, cw0_bit);
}

static inwine uwong kvm_wead_cw0(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_wead_cw0_bits(vcpu, ~0UW);
}

static inwine uwong kvm_wead_cw4_bits(stwuct kvm_vcpu *vcpu, uwong mask)
{
	uwong tmask = mask & KVM_POSSIBWE_CW4_GUEST_BITS;
	if ((tmask & vcpu->awch.cw4_guest_owned_bits) &&
	    !kvm_wegistew_is_avaiwabwe(vcpu, VCPU_EXWEG_CW4))
		static_caww(kvm_x86_cache_weg)(vcpu, VCPU_EXWEG_CW4);
	wetuwn vcpu->awch.cw4 & mask;
}

static __awways_inwine boow kvm_is_cw4_bit_set(stwuct kvm_vcpu *vcpu,
					       unsigned wong cw4_bit)
{
	BUIWD_BUG_ON(!is_powew_of_2(cw4_bit));

	wetuwn !!kvm_wead_cw4_bits(vcpu, cw4_bit);
}

static inwine uwong kvm_wead_cw3(stwuct kvm_vcpu *vcpu)
{
	if (!kvm_wegistew_is_avaiwabwe(vcpu, VCPU_EXWEG_CW3))
		static_caww(kvm_x86_cache_weg)(vcpu, VCPU_EXWEG_CW3);
	wetuwn vcpu->awch.cw3;
}

static inwine uwong kvm_wead_cw4(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_wead_cw4_bits(vcpu, ~0UW);
}

static inwine u64 kvm_wead_edx_eax(stwuct kvm_vcpu *vcpu)
{
	wetuwn (kvm_wax_wead(vcpu) & -1u)
		| ((u64)(kvm_wdx_wead(vcpu) & -1u) << 32);
}

static inwine void entew_guest_mode(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.hfwags |= HF_GUEST_MASK;
	vcpu->stat.guest_mode = 1;
}

static inwine void weave_guest_mode(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.hfwags &= ~HF_GUEST_MASK;

	if (vcpu->awch.woad_eoi_exitmap_pending) {
		vcpu->awch.woad_eoi_exitmap_pending = fawse;
		kvm_make_wequest(KVM_WEQ_WOAD_EOI_EXITMAP, vcpu);
	}

	vcpu->stat.guest_mode = 0;
}

static inwine boow is_guest_mode(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.hfwags & HF_GUEST_MASK;
}

#endif
