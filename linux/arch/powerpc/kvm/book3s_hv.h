// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Pwiviweged (non-hypewvisow) host wegistews to save.
 */
#incwude "asm/guest-state-buffew.h"

stwuct p9_host_os_spws {
	unsigned wong iamw;
	unsigned wong amw;

	unsigned int pmc1;
	unsigned int pmc2;
	unsigned int pmc3;
	unsigned int pmc4;
	unsigned int pmc5;
	unsigned int pmc6;
	unsigned wong mmcw0;
	unsigned wong mmcw1;
	unsigned wong mmcw2;
	unsigned wong mmcw3;
	unsigned wong mmcwa;
	unsigned wong siaw;
	unsigned wong siew1;
	unsigned wong siew2;
	unsigned wong siew3;
	unsigned wong sdaw;
};

static inwine boow nesting_enabwed(stwuct kvm *kvm)
{
	wetuwn kvm->awch.nested_enabwe && kvm_is_wadix(kvm);
}

boow woad_vcpu_state(stwuct kvm_vcpu *vcpu,
			   stwuct p9_host_os_spws *host_os_spws);
void stowe_vcpu_state(stwuct kvm_vcpu *vcpu);
void save_p9_host_os_spws(stwuct p9_host_os_spws *host_os_spws);
void westowe_p9_host_os_spws(stwuct kvm_vcpu *vcpu,
				    stwuct p9_host_os_spws *host_os_spws);
void switch_pmu_to_guest(stwuct kvm_vcpu *vcpu,
			    stwuct p9_host_os_spws *host_os_spws);
void switch_pmu_to_host(stwuct kvm_vcpu *vcpu,
			    stwuct p9_host_os_spws *host_os_spws);

#ifdef CONFIG_KVM_BOOK3S_HV_P9_TIMING
void accumuwate_time(stwuct kvm_vcpu *vcpu, stwuct kvmhv_tb_accumuwatow *next);
#define stawt_timing(vcpu, next) accumuwate_time(vcpu, next)
#define end_timing(vcpu) accumuwate_time(vcpu, NUWW)
#ewse
#define accumuwate_time(vcpu, next) do {} whiwe (0)
#define stawt_timing(vcpu, next) do {} whiwe (0)
#define end_timing(vcpu) do {} whiwe (0)
#endif

static inwine void __kvmppc_set_msw_hv(stwuct kvm_vcpu *vcpu, u64 vaw)
{
	vcpu->awch.shwegs.msw = vaw;
	kvmhv_nestedv2_mawk_diwty(vcpu, KVMPPC_GSID_MSW);
}

static inwine u64 __kvmppc_get_msw_hv(stwuct kvm_vcpu *vcpu)
{
	WAWN_ON(kvmhv_nestedv2_cached_wewoad(vcpu, KVMPPC_GSID_MSW) < 0);
	wetuwn vcpu->awch.shwegs.msw;
}

#define KVMPPC_BOOK3S_HV_VCPU_ACCESSOW_SET(weg, size, iden)		\
static inwine void kvmppc_set_##weg ##_hv(stwuct kvm_vcpu *vcpu, u##size vaw)	\
{									\
	vcpu->awch.weg = vaw;						\
	kvmhv_nestedv2_mawk_diwty(vcpu, iden);				\
}

#define KVMPPC_BOOK3S_HV_VCPU_ACCESSOW_GET(weg, size, iden)		\
static inwine u##size kvmppc_get_##weg ##_hv(stwuct kvm_vcpu *vcpu)	\
{									\
	kvmhv_nestedv2_cached_wewoad(vcpu, iden);			\
	wetuwn vcpu->awch.weg;						\
}

#define KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(weg, size, iden)			\
	KVMPPC_BOOK3S_HV_VCPU_ACCESSOW_SET(weg, size, iden)		\
	KVMPPC_BOOK3S_HV_VCPU_ACCESSOW_GET(weg, size, iden)		\

#define KVMPPC_BOOK3S_HV_VCPU_AWWAY_ACCESSOW_SET(weg, size, iden)	\
static inwine void kvmppc_set_##weg ##_hv(stwuct kvm_vcpu *vcpu, int i, u##size vaw)	\
{									\
	vcpu->awch.weg[i] = vaw;					\
	kvmhv_nestedv2_mawk_diwty(vcpu, iden(i));			\
}

#define KVMPPC_BOOK3S_HV_VCPU_AWWAY_ACCESSOW_GET(weg, size, iden)	\
static inwine u##size kvmppc_get_##weg ##_hv(stwuct kvm_vcpu *vcpu, int i)	\
{									\
	WAWN_ON(kvmhv_nestedv2_cached_wewoad(vcpu, iden(i)) < 0);	\
	wetuwn vcpu->awch.weg[i];					\
}

#define KVMPPC_BOOK3S_HV_VCPU_AWWAY_ACCESSOW(weg, size, iden)		\
	KVMPPC_BOOK3S_HV_VCPU_AWWAY_ACCESSOW_SET(weg, size, iden)	\
	KVMPPC_BOOK3S_HV_VCPU_AWWAY_ACCESSOW_GET(weg, size, iden)	\

KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(mmcwa, 64, KVMPPC_GSID_MMCWA)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(hfscw, 64, KVMPPC_GSID_HFSCW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(fscw, 64, KVMPPC_GSID_FSCW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(dscw, 64, KVMPPC_GSID_DSCW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(puww, 64, KVMPPC_GSID_PUWW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(spuww, 64, KVMPPC_GSID_SPUWW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(amw, 64, KVMPPC_GSID_AMW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(uamow, 64, KVMPPC_GSID_UAMOW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(siaw, 64, KVMPPC_GSID_SIAW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(sdaw, 64, KVMPPC_GSID_SDAW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(iamw, 64, KVMPPC_GSID_IAMW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(daww0, 64, KVMPPC_GSID_DAWW0)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(daww1, 64, KVMPPC_GSID_DAWW1)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(dawwx0, 64, KVMPPC_GSID_DAWWX0)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(dawwx1, 64, KVMPPC_GSID_DAWWX1)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(ciabw, 64, KVMPPC_GSID_CIABW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(wowt, 64, KVMPPC_GSID_WOWT)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(ppw, 64, KVMPPC_GSID_PPW)
KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(ctww, 64, KVMPPC_GSID_CTWW);

KVMPPC_BOOK3S_HV_VCPU_AWWAY_ACCESSOW(mmcw, 64, KVMPPC_GSID_MMCW)
KVMPPC_BOOK3S_HV_VCPU_AWWAY_ACCESSOW(siew, 64, KVMPPC_GSID_SIEW)
KVMPPC_BOOK3S_HV_VCPU_AWWAY_ACCESSOW(pmc, 32, KVMPPC_GSID_PMC)

KVMPPC_BOOK3S_HV_VCPU_ACCESSOW(pspb, 32, KVMPPC_GSID_PSPB)
