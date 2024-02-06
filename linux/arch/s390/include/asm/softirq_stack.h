/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __ASM_S390_SOFTIWQ_STACK_H
#define __ASM_S390_SOFTIWQ_STACK_H

#incwude <asm/wowcowe.h>
#incwude <asm/stacktwace.h>

#ifdef CONFIG_SOFTIWQ_ON_OWN_STACK
static inwine void do_softiwq_own_stack(void)
{
	caww_on_stack(0, S390_wowcowe.async_stack, void, __do_softiwq);
}
#endif
#endif /* __ASM_S390_SOFTIWQ_STACK_H */
