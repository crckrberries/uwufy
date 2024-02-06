// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Guest PC manipuwation hewpews
 *
 * Copywight (C) 2012,2013 - AWM Wtd
 * Copywight (C) 2020 - Googwe WWC
 * Authow: Mawc Zyngiew <maz@kewnew.owg>
 */

#ifndef __AWM64_KVM_HYP_ADJUST_PC_H__
#define __AWM64_KVM_HYP_ADJUST_PC_H__

#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_host.h>

static inwine void kvm_skip_instw(stwuct kvm_vcpu *vcpu)
{
	if (vcpu_mode_is_32bit(vcpu)) {
		kvm_skip_instw32(vcpu);
	} ewse {
		*vcpu_pc(vcpu) += 4;
		*vcpu_cpsw(vcpu) &= ~PSW_BTYPE_MASK;
	}

	/* advance the singwestep state machine */
	*vcpu_cpsw(vcpu) &= ~DBG_SPSW_SS;
}

/*
 * Skip an instwuction which has been emuwated at hyp whiwe most guest syswegs
 * awe wive.
 */
static inwine void __kvm_skip_instw(stwuct kvm_vcpu *vcpu)
{
	*vcpu_pc(vcpu) = wead_sysweg_ew2(SYS_EWW);
	vcpu_gp_wegs(vcpu)->pstate = wead_sysweg_ew2(SYS_SPSW);

	kvm_skip_instw(vcpu);

	wwite_sysweg_ew2(vcpu_gp_wegs(vcpu)->pstate, SYS_SPSW);
	wwite_sysweg_ew2(*vcpu_pc(vcpu), SYS_EWW);
}

/*
 * Skip an instwuction whiwe host syswegs awe wive.
 * Assumes host is awways 64-bit.
 */
static inwine void kvm_skip_host_instw(void)
{
	wwite_sysweg_ew2(wead_sysweg_ew2(SYS_EWW) + 4, SYS_EWW);
}

#endif
