/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IWQ suppowt fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_IWQFWAGS_H
#define _ASM_IWQFWAGS_H

#incwude <asm/hexagon_vm.h>
#incwude <winux/types.h>

static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	wetuwn __vmgetie();
}

static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	wetuwn __vmsetie(VM_INT_DISABWE);
}

static inwine boow awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn !fwags;
}

static inwine boow awch_iwqs_disabwed(void)
{
	wetuwn !__vmgetie();
}

static inwine void awch_wocaw_iwq_enabwe(void)
{
	__vmsetie(VM_INT_ENABWE);
}

static inwine void awch_wocaw_iwq_disabwe(void)
{
	__vmsetie(VM_INT_DISABWE);
}

static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	__vmsetie(fwags);
}

#endif
