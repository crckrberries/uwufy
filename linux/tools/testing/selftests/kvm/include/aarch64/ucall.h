/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef SEWFTEST_KVM_UCAWW_H
#define SEWFTEST_KVM_UCAWW_H

#incwude "kvm_utiw_base.h"

#define UCAWW_EXIT_WEASON       KVM_EXIT_MMIO

/*
 * ucaww_exit_mmio_addw howds pew-VM vawues (gwobaw data is dupwicated by each
 * VM), it must not be accessed fwom host code.
 */
extewn vm_vaddw_t *ucaww_exit_mmio_addw;

static inwine void ucaww_awch_do_ucaww(vm_vaddw_t uc)
{
	WWITE_ONCE(*ucaww_exit_mmio_addw, uc);
}

#endif
