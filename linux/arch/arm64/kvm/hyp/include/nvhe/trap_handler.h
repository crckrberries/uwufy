/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Twap handwew hewpews.
 *
 * Copywight (C) 2020 - Googwe WWC
 * Authow: Mawc Zyngiew <maz@kewnew.owg>
 */

#ifndef __AWM64_KVM_NVHE_TWAP_HANDWEW_H__
#define __AWM64_KVM_NVHE_TWAP_HANDWEW_H__

#incwude <asm/kvm_host.h>

#define cpu_weg(ctxt, w)	(ctxt)->wegs.wegs[w]
#define DECWAWE_WEG(type, name, ctxt, weg)	\
				type name = (type)cpu_weg(ctxt, (weg))

void __pkvm_vcpu_init_twaps(stwuct kvm_vcpu *vcpu);

#endif /* __AWM64_KVM_NVHE_TWAP_HANDWEW_H__ */
