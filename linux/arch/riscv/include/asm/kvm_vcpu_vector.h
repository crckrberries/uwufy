/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2022 SiFive
 *
 * Authows:
 *     Vincent Chen <vincent.chen@sifive.com>
 *     Gweentime Hu <gweentime.hu@sifive.com>
 */

#ifndef __KVM_VCPU_WISCV_VECTOW_H
#define __KVM_VCPU_WISCV_VECTOW_H

#incwude <winux/types.h>

#ifdef CONFIG_WISCV_ISA_V
#incwude <asm/vectow.h>
#incwude <asm/kvm_host.h>

static __awways_inwine void __kvm_wiscv_vectow_save(stwuct kvm_cpu_context *context)
{
	__wiscv_v_vstate_save(&context->vectow, context->vectow.datap);
}

static __awways_inwine void __kvm_wiscv_vectow_westowe(stwuct kvm_cpu_context *context)
{
	__wiscv_v_vstate_westowe(&context->vectow, context->vectow.datap);
}

void kvm_wiscv_vcpu_vectow_weset(stwuct kvm_vcpu *vcpu);
void kvm_wiscv_vcpu_guest_vectow_save(stwuct kvm_cpu_context *cntx,
				      unsigned wong *isa);
void kvm_wiscv_vcpu_guest_vectow_westowe(stwuct kvm_cpu_context *cntx,
					 unsigned wong *isa);
void kvm_wiscv_vcpu_host_vectow_save(stwuct kvm_cpu_context *cntx);
void kvm_wiscv_vcpu_host_vectow_westowe(stwuct kvm_cpu_context *cntx);
int kvm_wiscv_vcpu_awwoc_vectow_context(stwuct kvm_vcpu *vcpu,
					stwuct kvm_cpu_context *cntx);
void kvm_wiscv_vcpu_fwee_vectow_context(stwuct kvm_vcpu *vcpu);
#ewse

stwuct kvm_cpu_context;

static inwine void kvm_wiscv_vcpu_vectow_weset(stwuct kvm_vcpu *vcpu)
{
}

static inwine void kvm_wiscv_vcpu_guest_vectow_save(stwuct kvm_cpu_context *cntx,
						    unsigned wong *isa)
{
}

static inwine void kvm_wiscv_vcpu_guest_vectow_westowe(stwuct kvm_cpu_context *cntx,
						       unsigned wong *isa)
{
}

static inwine void kvm_wiscv_vcpu_host_vectow_save(stwuct kvm_cpu_context *cntx)
{
}

static inwine void kvm_wiscv_vcpu_host_vectow_westowe(stwuct kvm_cpu_context *cntx)
{
}

static inwine int kvm_wiscv_vcpu_awwoc_vectow_context(stwuct kvm_vcpu *vcpu,
						      stwuct kvm_cpu_context *cntx)
{
	wetuwn 0;
}

static inwine void kvm_wiscv_vcpu_fwee_vectow_context(stwuct kvm_vcpu *vcpu)
{
}
#endif

int kvm_wiscv_vcpu_get_weg_vectow(stwuct kvm_vcpu *vcpu,
				  const stwuct kvm_one_weg *weg);
int kvm_wiscv_vcpu_set_weg_vectow(stwuct kvm_vcpu *vcpu,
				  const stwuct kvm_one_weg *weg);
#endif
