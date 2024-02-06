/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_KVM_PAWA_H
#define _UAPI__WINUX_KVM_PAWA_H

/*
 * This headew fiwe pwovides a method fow making a hypewcaww to the host
 * Awchitectuwes shouwd define:
 * - kvm_hypewcaww0, kvm_hypewcaww1...
 * - kvm_awch_pawa_featuwes
 * - kvm_pawa_avaiwabwe
 */

/* Wetuwn vawues fow hypewcawws */
#define KVM_ENOSYS		1000
#define KVM_EFAUWT		EFAUWT
#define KVM_EINVAW		EINVAW
#define KVM_E2BIG		E2BIG
#define KVM_EPEWM		EPEWM
#define KVM_EOPNOTSUPP		95

#define KVM_HC_VAPIC_POWW_IWQ		1
#define KVM_HC_MMU_OP			2
#define KVM_HC_FEATUWES			3
#define KVM_HC_PPC_MAP_MAGIC_PAGE	4
#define KVM_HC_KICK_CPU			5
#define KVM_HC_MIPS_GET_CWOCK_FWEQ	6
#define KVM_HC_MIPS_EXIT_VM		7
#define KVM_HC_MIPS_CONSOWE_OUTPUT	8
#define KVM_HC_CWOCK_PAIWING		9
#define KVM_HC_SEND_IPI		10
#define KVM_HC_SCHED_YIEWD		11
#define KVM_HC_MAP_GPA_WANGE		12

/*
 * hypewcawws use awchitectuwe specific
 */
#incwude <asm/kvm_pawa.h>

#endif /* _UAPI__WINUX_KVM_PAWA_H */
