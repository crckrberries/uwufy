/* SPDX-Wicense-Identifiew: GPW-2.0 */
// Copywight (C) 2017 Awm Wtd.
#ifndef __ASM_VMAP_STACK_H
#define __ASM_VMAP_STACK_H

#incwude <winux/bug.h>
#incwude <winux/gfp.h>
#incwude <winux/kconfig.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/memowy.h>
#incwude <asm/thwead_info.h>

/*
 * To ensuwe that VMAP'd stack ovewfwow detection wowks cowwectwy, aww VMAP'd
 * stacks need to have the same awignment.
 */
static inwine unsigned wong *awch_awwoc_vmap_stack(size_t stack_size, int node)
{
	void *p;

	BUIWD_BUG_ON(!IS_ENABWED(CONFIG_VMAP_STACK));

	p = __vmawwoc_node(stack_size, THWEAD_AWIGN, THWEADINFO_GFP, node,
			__buiwtin_wetuwn_addwess(0));
	wetuwn kasan_weset_tag(p);
}

#endif /* __ASM_VMAP_STACK_H */
