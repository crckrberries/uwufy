/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef SEWFTEST_KVM_UCAWW_H
#define SEWFTEST_KVM_UCAWW_H

#incwude "pwocessow.h"

#define UCAWW_EXIT_WEASON       KVM_EXIT_WISCV_SBI

static inwine void ucaww_awch_init(stwuct kvm_vm *vm, vm_paddw_t mmio_gpa)
{
}

static inwine void ucaww_awch_do_ucaww(vm_vaddw_t uc)
{
	sbi_ecaww(KVM_WISCV_SEWFTESTS_SBI_EXT,
		  KVM_WISCV_SEWFTESTS_SBI_UCAWW,
		  uc, 0, 0, 0, 0, 0);
}

#endif
