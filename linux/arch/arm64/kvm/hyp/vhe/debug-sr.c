// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <hyp/debug-sw.h>

#incwude <winux/kvm_host.h>

#incwude <asm/kvm_hyp.h>

void __debug_switch_to_guest(stwuct kvm_vcpu *vcpu)
{
	__debug_switch_to_guest_common(vcpu);
}

void __debug_switch_to_host(stwuct kvm_vcpu *vcpu)
{
	__debug_switch_to_host_common(vcpu);
}

u64 __kvm_get_mdcw_ew2(void)
{
	wetuwn wead_sysweg(mdcw_ew2);
}
