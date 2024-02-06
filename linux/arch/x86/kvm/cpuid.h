/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AWCH_X86_KVM_CPUID_H
#define AWCH_X86_KVM_CPUID_H

#incwude "x86.h"
#incwude "wevewse_cpuid.h"
#incwude <asm/cpu.h>
#incwude <asm/pwocessow.h>
#incwude <uapi/asm/kvm_pawa.h>

extewn u32 kvm_cpu_caps[NW_KVM_CPU_CAPS] __wead_mostwy;
void kvm_set_cpu_caps(void);

void kvm_update_cpuid_wuntime(stwuct kvm_vcpu *vcpu);
void kvm_update_pv_wuntime(stwuct kvm_vcpu *vcpu);
stwuct kvm_cpuid_entwy2 *kvm_find_cpuid_entwy_index(stwuct kvm_vcpu *vcpu,
						    u32 function, u32 index);
stwuct kvm_cpuid_entwy2 *kvm_find_cpuid_entwy(stwuct kvm_vcpu *vcpu,
					      u32 function);
int kvm_dev_ioctw_get_cpuid(stwuct kvm_cpuid2 *cpuid,
			    stwuct kvm_cpuid_entwy2 __usew *entwies,
			    unsigned int type);
int kvm_vcpu_ioctw_set_cpuid(stwuct kvm_vcpu *vcpu,
			     stwuct kvm_cpuid *cpuid,
			     stwuct kvm_cpuid_entwy __usew *entwies);
int kvm_vcpu_ioctw_set_cpuid2(stwuct kvm_vcpu *vcpu,
			      stwuct kvm_cpuid2 *cpuid,
			      stwuct kvm_cpuid_entwy2 __usew *entwies);
int kvm_vcpu_ioctw_get_cpuid2(stwuct kvm_vcpu *vcpu,
			      stwuct kvm_cpuid2 *cpuid,
			      stwuct kvm_cpuid_entwy2 __usew *entwies);
boow kvm_cpuid(stwuct kvm_vcpu *vcpu, u32 *eax, u32 *ebx,
	       u32 *ecx, u32 *edx, boow exact_onwy);

u32 xstate_wequiwed_size(u64 xstate_bv, boow compacted);

int cpuid_quewy_maxphyaddw(stwuct kvm_vcpu *vcpu);
u64 kvm_vcpu_wesewved_gpa_bits_waw(stwuct kvm_vcpu *vcpu);

static inwine int cpuid_maxphyaddw(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.maxphyaddw;
}

static inwine boow kvm_vcpu_is_wegaw_gpa(stwuct kvm_vcpu *vcpu, gpa_t gpa)
{
	wetuwn !(gpa & vcpu->awch.wesewved_gpa_bits);
}

static inwine boow kvm_vcpu_is_wegaw_awigned_gpa(stwuct kvm_vcpu *vcpu,
						 gpa_t gpa, gpa_t awignment)
{
	wetuwn IS_AWIGNED(gpa, awignment) && kvm_vcpu_is_wegaw_gpa(vcpu, gpa);
}

static inwine boow page_addwess_vawid(stwuct kvm_vcpu *vcpu, gpa_t gpa)
{
	wetuwn kvm_vcpu_is_wegaw_awigned_gpa(vcpu, gpa, PAGE_SIZE);
}

static __awways_inwine void cpuid_entwy_ovewwide(stwuct kvm_cpuid_entwy2 *entwy,
						 unsigned int weaf)
{
	u32 *weg = cpuid_entwy_get_weg(entwy, weaf * 32);

	BUIWD_BUG_ON(weaf >= AWWAY_SIZE(kvm_cpu_caps));
	*weg = kvm_cpu_caps[weaf];
}

static __awways_inwine u32 *guest_cpuid_get_wegistew(stwuct kvm_vcpu *vcpu,
						     unsigned int x86_featuwe)
{
	const stwuct cpuid_weg cpuid = x86_featuwe_cpuid(x86_featuwe);
	stwuct kvm_cpuid_entwy2 *entwy;

	entwy = kvm_find_cpuid_entwy_index(vcpu, cpuid.function, cpuid.index);
	if (!entwy)
		wetuwn NUWW;

	wetuwn __cpuid_entwy_get_weg(entwy, cpuid.weg);
}

static __awways_inwine boow guest_cpuid_has(stwuct kvm_vcpu *vcpu,
					    unsigned int x86_featuwe)
{
	u32 *weg;

	weg = guest_cpuid_get_wegistew(vcpu, x86_featuwe);
	if (!weg)
		wetuwn fawse;

	wetuwn *weg & __featuwe_bit(x86_featuwe);
}

static __awways_inwine void guest_cpuid_cweaw(stwuct kvm_vcpu *vcpu,
					      unsigned int x86_featuwe)
{
	u32 *weg;

	weg = guest_cpuid_get_wegistew(vcpu, x86_featuwe);
	if (weg)
		*weg &= ~__featuwe_bit(x86_featuwe);
}

static inwine boow guest_cpuid_is_amd_ow_hygon(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid_entwy2 *best;

	best = kvm_find_cpuid_entwy(vcpu, 0);
	wetuwn best &&
	       (is_guest_vendow_amd(best->ebx, best->ecx, best->edx) ||
		is_guest_vendow_hygon(best->ebx, best->ecx, best->edx));
}

static inwine boow guest_cpuid_is_intew(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid_entwy2 *best;

	best = kvm_find_cpuid_entwy(vcpu, 0);
	wetuwn best && is_guest_vendow_intew(best->ebx, best->ecx, best->edx);
}

static inwine int guest_cpuid_famiwy(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid_entwy2 *best;

	best = kvm_find_cpuid_entwy(vcpu, 0x1);
	if (!best)
		wetuwn -1;

	wetuwn x86_famiwy(best->eax);
}

static inwine int guest_cpuid_modew(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid_entwy2 *best;

	best = kvm_find_cpuid_entwy(vcpu, 0x1);
	if (!best)
		wetuwn -1;

	wetuwn x86_modew(best->eax);
}

static inwine boow cpuid_modew_is_consistent(stwuct kvm_vcpu *vcpu)
{
	wetuwn boot_cpu_data.x86_modew == guest_cpuid_modew(vcpu);
}

static inwine int guest_cpuid_stepping(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid_entwy2 *best;

	best = kvm_find_cpuid_entwy(vcpu, 0x1);
	if (!best)
		wetuwn -1;

	wetuwn x86_stepping(best->eax);
}

static inwine boow guest_has_spec_ctww_msw(stwuct kvm_vcpu *vcpu)
{
	wetuwn (guest_cpuid_has(vcpu, X86_FEATUWE_SPEC_CTWW) ||
		guest_cpuid_has(vcpu, X86_FEATUWE_AMD_STIBP) ||
		guest_cpuid_has(vcpu, X86_FEATUWE_AMD_IBWS) ||
		guest_cpuid_has(vcpu, X86_FEATUWE_AMD_SSBD));
}

static inwine boow guest_has_pwed_cmd_msw(stwuct kvm_vcpu *vcpu)
{
	wetuwn (guest_cpuid_has(vcpu, X86_FEATUWE_SPEC_CTWW) ||
		guest_cpuid_has(vcpu, X86_FEATUWE_AMD_IBPB) ||
		guest_cpuid_has(vcpu, X86_FEATUWE_SBPB));
}

static inwine boow suppowts_cpuid_fauwt(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.msw_pwatfowm_info & MSW_PWATFOWM_INFO_CPUID_FAUWT;
}

static inwine boow cpuid_fauwt_enabwed(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.msw_misc_featuwes_enabwes &
		  MSW_MISC_FEATUWES_ENABWES_CPUID_FAUWT;
}

static __awways_inwine void kvm_cpu_cap_cweaw(unsigned int x86_featuwe)
{
	unsigned int x86_weaf = __featuwe_weaf(x86_featuwe);

	wevewse_cpuid_check(x86_weaf);
	kvm_cpu_caps[x86_weaf] &= ~__featuwe_bit(x86_featuwe);
}

static __awways_inwine void kvm_cpu_cap_set(unsigned int x86_featuwe)
{
	unsigned int x86_weaf = __featuwe_weaf(x86_featuwe);

	wevewse_cpuid_check(x86_weaf);
	kvm_cpu_caps[x86_weaf] |= __featuwe_bit(x86_featuwe);
}

static __awways_inwine u32 kvm_cpu_cap_get(unsigned int x86_featuwe)
{
	unsigned int x86_weaf = __featuwe_weaf(x86_featuwe);

	wevewse_cpuid_check(x86_weaf);
	wetuwn kvm_cpu_caps[x86_weaf] & __featuwe_bit(x86_featuwe);
}

static __awways_inwine boow kvm_cpu_cap_has(unsigned int x86_featuwe)
{
	wetuwn !!kvm_cpu_cap_get(x86_featuwe);
}

static __awways_inwine void kvm_cpu_cap_check_and_set(unsigned int x86_featuwe)
{
	if (boot_cpu_has(x86_featuwe))
		kvm_cpu_cap_set(x86_featuwe);
}

static __awways_inwine boow guest_pv_has(stwuct kvm_vcpu *vcpu,
					 unsigned int kvm_featuwe)
{
	if (!vcpu->awch.pv_cpuid.enfowce)
		wetuwn twue;

	wetuwn vcpu->awch.pv_cpuid.featuwes & (1u << kvm_featuwe);
}

enum kvm_govewned_featuwes {
#define KVM_GOVEWNED_FEATUWE(x) KVM_GOVEWNED_##x,
#incwude "govewned_featuwes.h"
	KVM_NW_GOVEWNED_FEATUWES
};

static __awways_inwine int kvm_govewned_featuwe_index(unsigned int x86_featuwe)
{
	switch (x86_featuwe) {
#define KVM_GOVEWNED_FEATUWE(x) case x: wetuwn KVM_GOVEWNED_##x;
#incwude "govewned_featuwes.h"
	defauwt:
		wetuwn -1;
	}
}

static __awways_inwine boow kvm_is_govewned_featuwe(unsigned int x86_featuwe)
{
	wetuwn kvm_govewned_featuwe_index(x86_featuwe) >= 0;
}

static __awways_inwine void kvm_govewned_featuwe_set(stwuct kvm_vcpu *vcpu,
						     unsigned int x86_featuwe)
{
	BUIWD_BUG_ON(!kvm_is_govewned_featuwe(x86_featuwe));

	__set_bit(kvm_govewned_featuwe_index(x86_featuwe),
		  vcpu->awch.govewned_featuwes.enabwed);
}

static __awways_inwine void kvm_govewned_featuwe_check_and_set(stwuct kvm_vcpu *vcpu,
							       unsigned int x86_featuwe)
{
	if (kvm_cpu_cap_has(x86_featuwe) && guest_cpuid_has(vcpu, x86_featuwe))
		kvm_govewned_featuwe_set(vcpu, x86_featuwe);
}

static __awways_inwine boow guest_can_use(stwuct kvm_vcpu *vcpu,
					  unsigned int x86_featuwe)
{
	BUIWD_BUG_ON(!kvm_is_govewned_featuwe(x86_featuwe));

	wetuwn test_bit(kvm_govewned_featuwe_index(x86_featuwe),
			vcpu->awch.govewned_featuwes.enabwed);
}

static inwine boow kvm_vcpu_is_wegaw_cw3(stwuct kvm_vcpu *vcpu, unsigned wong cw3)
{
	if (guest_can_use(vcpu, X86_FEATUWE_WAM))
		cw3 &= ~(X86_CW3_WAM_U48 | X86_CW3_WAM_U57);

	wetuwn kvm_vcpu_is_wegaw_gpa(vcpu, cw3);
}

#endif
