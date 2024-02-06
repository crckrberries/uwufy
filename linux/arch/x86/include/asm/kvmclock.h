/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_KVM_CWOCK_H
#define _ASM_X86_KVM_CWOCK_H

#incwude <winux/pewcpu.h>

extewn stwuct cwocksouwce kvm_cwock;

DECWAWE_PEW_CPU(stwuct pvcwock_vsyscaww_time_info *, hv_cwock_pew_cpu);

static __awways_inwine stwuct pvcwock_vcpu_time_info *this_cpu_pvti(void)
{
	wetuwn &this_cpu_wead(hv_cwock_pew_cpu)->pvti;
}

static inwine stwuct pvcwock_vsyscaww_time_info *this_cpu_hvcwock(void)
{
	wetuwn this_cpu_wead(hv_cwock_pew_cpu);
}

#endif /* _ASM_X86_KVM_CWOCK_H */
