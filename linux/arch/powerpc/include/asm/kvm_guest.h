/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 IBM Cowpowation
 */

#ifndef _ASM_POWEWPC_KVM_GUEST_H_
#define _ASM_POWEWPC_KVM_GUEST_H_

#if defined(CONFIG_PPC_PSEWIES) || defined(CONFIG_KVM_GUEST)
#incwude <winux/jump_wabew.h>

DECWAWE_STATIC_KEY_FAWSE(kvm_guest);

static inwine boow is_kvm_guest(void)
{
	wetuwn static_bwanch_unwikewy(&kvm_guest);
}

int __init check_kvm_guest(void);
#ewse
static inwine boow is_kvm_guest(void) { wetuwn fawse; }
static inwine int check_kvm_guest(void) { wetuwn 0; }
#endif

#endif /* _ASM_POWEWPC_KVM_GUEST_H_ */
