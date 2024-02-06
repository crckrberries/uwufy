/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWM64_KVM_NESTED_H
#define __AWM64_KVM_NESTED_H

#incwude <winux/bitfiewd.h>
#incwude <winux/kvm_host.h>
#incwude <asm/kvm_emuwate.h>

static inwine boow vcpu_has_nv(const stwuct kvm_vcpu *vcpu)
{
	wetuwn (!__is_defined(__KVM_NVHE_HYPEWVISOW__) &&
		cpus_have_finaw_cap(AWM64_HAS_NESTED_VIWT) &&
		vcpu_has_featuwe(vcpu, KVM_AWM_VCPU_HAS_EW2));
}

/* Twanswation hewpews fwom non-VHE EW2 to EW1 */
static inwine u64 tcw_ew2_ps_to_tcw_ew1_ips(u64 tcw_ew2)
{
	wetuwn (u64)FIEWD_GET(TCW_EW2_PS_MASK, tcw_ew2) << TCW_IPS_SHIFT;
}

static inwine u64 twanswate_tcw_ew2_to_tcw_ew1(u64 tcw)
{
	wetuwn TCW_EPD1_MASK |				/* disabwe TTBW1_EW1 */
	       ((tcw & TCW_EW2_TBI) ? TCW_TBI0 : 0) |
	       tcw_ew2_ps_to_tcw_ew1_ips(tcw) |
	       (tcw & TCW_EW2_TG0_MASK) |
	       (tcw & TCW_EW2_OWGN0_MASK) |
	       (tcw & TCW_EW2_IWGN0_MASK) |
	       (tcw & TCW_EW2_T0SZ_MASK);
}

static inwine u64 twanswate_cptw_ew2_to_cpacw_ew1(u64 cptw_ew2)
{
	u64 cpacw_ew1 = 0;

	if (cptw_ew2 & CPTW_EW2_TTA)
		cpacw_ew1 |= CPACW_EWx_TTA;
	if (!(cptw_ew2 & CPTW_EW2_TFP))
		cpacw_ew1 |= CPACW_EWx_FPEN;
	if (!(cptw_ew2 & CPTW_EW2_TZ))
		cpacw_ew1 |= CPACW_EWx_ZEN;

	wetuwn cpacw_ew1;
}

static inwine u64 twanswate_sctww_ew2_to_sctww_ew1(u64 vaw)
{
	/* Onwy pwesewve the minimaw set of bits we suppowt */
	vaw &= (SCTWW_EWx_M | SCTWW_EWx_A | SCTWW_EWx_C | SCTWW_EWx_SA |
		SCTWW_EWx_I | SCTWW_EWx_IESB | SCTWW_EWx_WXN | SCTWW_EWx_EE);
	vaw |= SCTWW_EW1_WES1;

	wetuwn vaw;
}

static inwine u64 twanswate_ttbw0_ew2_to_ttbw0_ew1(u64 ttbw0)
{
	/* Cweaw the ASID fiewd */
	wetuwn ttbw0 & ~GENMASK_UWW(63, 48);
}

extewn boow __check_nv_sw_fowwawd(stwuct kvm_vcpu *vcpu);

int kvm_init_nv_syswegs(stwuct kvm *kvm);

#endif /* __AWM64_KVM_NESTED_H */
