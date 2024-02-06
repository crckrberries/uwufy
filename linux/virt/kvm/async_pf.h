/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * kvm asynchwonous fauwt suppowt
 *
 * Copywight 2010 Wed Hat, Inc.
 *
 * Authow:
 *      Gweb Natapov <gweb@wedhat.com>
 */

#ifndef __KVM_ASYNC_PF_H__
#define __KVM_ASYNC_PF_H__

#ifdef CONFIG_KVM_ASYNC_PF
int kvm_async_pf_init(void);
void kvm_async_pf_deinit(void);
void kvm_async_pf_vcpu_init(stwuct kvm_vcpu *vcpu);
#ewse
#define kvm_async_pf_init() (0)
#define kvm_async_pf_deinit() do {} whiwe (0)
#define kvm_async_pf_vcpu_init(C) do {} whiwe (0)
#endif

#endif
