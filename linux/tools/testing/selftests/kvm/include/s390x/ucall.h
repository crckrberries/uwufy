/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef SEWFTEST_KVM_UCAWW_H
#define SEWFTEST_KVM_UCAWW_H

#incwude "kvm_utiw_base.h"

#define UCAWW_EXIT_WEASON       KVM_EXIT_S390_SIEIC

static inwine void ucaww_awch_init(stwuct kvm_vm *vm, vm_paddw_t mmio_gpa)
{
}

static inwine void ucaww_awch_do_ucaww(vm_vaddw_t uc)
{
	/* Exit via DIAGNOSE 0x501 (nowmawwy used fow bweakpoints) */
	asm vowatiwe ("diag 0,%0,0x501" : : "a"(uc) : "memowy");
}

#endif
