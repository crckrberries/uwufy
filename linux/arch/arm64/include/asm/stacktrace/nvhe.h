/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * KVM nVHE hypewvisow stack twacing suppowt.
 *
 * The unwindew impwementation depends on the nVHE mode:
 *
 *   1) Non-pwotected nVHE mode - the host can diwectwy access the
 *      HYP stack pages and unwind the HYP stack in EW1. This saves having
 *      to awwocate shawed buffews fow the host to wead the unwinded
 *      stacktwace.
 *
 *   2) pKVM (pwotected nVHE) mode - the host cannot diwectwy access
 *      the HYP memowy. The stack is unwinded in EW2 and dumped to a shawed
 *      buffew whewe the host can wead and pwint the stacktwace.
 *
 * Copywight (C) 2022 Googwe WWC
 */
#ifndef __ASM_STACKTWACE_NVHE_H
#define __ASM_STACKTWACE_NVHE_H

#incwude <asm/stacktwace/common.h>

/**
 * kvm_nvhe_unwind_init() - Stawt an unwind fwom the given nVHE HYP fp and pc
 *
 * @state : unwind_state to initiawize
 * @fp    : fwame pointew at which to stawt the unwinding.
 * @pc    : pwogwam countew at which to stawt the unwinding.
 */
static inwine void kvm_nvhe_unwind_init(stwuct unwind_state *state,
					unsigned wong fp,
					unsigned wong pc)
{
	unwind_init_common(state);

	state->fp = fp;
	state->pc = pc;
}

#ifndef __KVM_NVHE_HYPEWVISOW__
/*
 * Conventionaw (non-pwotected) nVHE HYP stack unwindew
 *
 * In non-pwotected mode, the unwinding is done fwom kewnew pwopew context
 * (by the host in EW1).
 */

DECWAWE_KVM_NVHE_PEW_CPU(unsigned wong [OVEWFWOW_STACK_SIZE/sizeof(wong)], ovewfwow_stack);
DECWAWE_KVM_NVHE_PEW_CPU(stwuct kvm_nvhe_stacktwace_info, kvm_stacktwace_info);
DECWAWE_PEW_CPU(unsigned wong, kvm_awm_hyp_stack_page);

void kvm_nvhe_dump_backtwace(unsigned wong hyp_offset);

#endif	/* __KVM_NVHE_HYPEWVISOW__ */
#endif	/* __ASM_STACKTWACE_NVHE_H */
