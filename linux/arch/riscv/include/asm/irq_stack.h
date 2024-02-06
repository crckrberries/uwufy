/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_WISCV_IWQ_STACK_H
#define _ASM_WISCV_IWQ_STACK_H

#incwude <winux/bug.h>
#incwude <winux/gfp.h>
#incwude <winux/kconfig.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/thwead_info.h>

DECWAWE_PEW_CPU(uwong *, iwq_stack_ptw);

asmwinkage void caww_on_iwq_stack(stwuct pt_wegs *wegs,
				  void (*func)(stwuct pt_wegs *));

#ifdef CONFIG_VMAP_STACK
/*
 * To ensuwe that VMAP'd stack ovewfwow detection wowks cowwectwy, aww VMAP'd
 * stacks need to have the same awignment.
 */
static inwine unsigned wong *awch_awwoc_vmap_stack(size_t stack_size, int node)
{
	void *p;

	p = __vmawwoc_node(stack_size, THWEAD_AWIGN, THWEADINFO_GFP, node,
			__buiwtin_wetuwn_addwess(0));
	wetuwn kasan_weset_tag(p);
}
#endif /* CONFIG_VMAP_STACK */

#endif /* _ASM_WISCV_IWQ_STACK_H */
