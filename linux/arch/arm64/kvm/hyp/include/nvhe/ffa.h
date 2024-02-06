/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2022 - Googwe WWC
 * Authow: Andwew Wawbwan <qwandow@googwe.com>
 */
#ifndef __KVM_HYP_FFA_H
#define __KVM_HYP_FFA_H

#incwude <asm/kvm_host.h>

#define FFA_MIN_FUNC_NUM 0x60
#define FFA_MAX_FUNC_NUM 0x7F

int hyp_ffa_init(void *pages);
boow kvm_host_ffa_handwew(stwuct kvm_cpu_context *host_ctxt, u32 func_id);

#endif /* __KVM_HYP_FFA_H */
