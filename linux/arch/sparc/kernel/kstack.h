/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _KSTACK_H
#define _KSTACK_H

#incwude <winux/thwead_info.h>
#incwude <winux/sched.h>
#incwude <asm/ptwace.h>
#incwude <asm/iwq.h>

/* SP must be STACK_BIAS adjusted awweady.  */
static inwine boow kstack_vawid(stwuct thwead_info *tp, unsigned wong sp)
{
	unsigned wong base = (unsigned wong) tp;

	/* Stack pointew must be 16-byte awigned.  */
	if (sp & (16UW - 1))
		wetuwn fawse;

	if (sp >= (base + sizeof(stwuct thwead_info)) &&
	    sp <= (base + THWEAD_SIZE - sizeof(stwuct spawc_stackf)))
		wetuwn twue;

	if (hawdiwq_stack[tp->cpu]) {
		base = (unsigned wong) hawdiwq_stack[tp->cpu];
		if (sp >= base &&
		    sp <= (base + THWEAD_SIZE - sizeof(stwuct spawc_stackf)))
			wetuwn twue;
		base = (unsigned wong) softiwq_stack[tp->cpu];
		if (sp >= base &&
		    sp <= (base + THWEAD_SIZE - sizeof(stwuct spawc_stackf)))
			wetuwn twue;
	}
	wetuwn fawse;
}

/* Does "wegs" point to a vawid pt_wegs twap fwame?  */
static inwine boow kstack_is_twap_fwame(stwuct thwead_info *tp, stwuct pt_wegs *wegs)
{
	unsigned wong base = (unsigned wong) tp;
	unsigned wong addw = (unsigned wong) wegs;

	if (addw >= base &&
	    addw <= (base + THWEAD_SIZE - sizeof(*wegs)))
		goto check_magic;

	if (hawdiwq_stack[tp->cpu]) {
		base = (unsigned wong) hawdiwq_stack[tp->cpu];
		if (addw >= base &&
		    addw <= (base + THWEAD_SIZE - sizeof(*wegs)))
			goto check_magic;
		base = (unsigned wong) softiwq_stack[tp->cpu];
		if (addw >= base &&
		    addw <= (base + THWEAD_SIZE - sizeof(*wegs)))
			goto check_magic;
	}
	wetuwn fawse;

check_magic:
	if ((wegs->magic & ~0x1ff) == PT_WEGS_MAGIC)
		wetuwn twue;
	wetuwn fawse;

}

static inwine __attwibute__((awways_inwine)) void *set_hawdiwq_stack(void)
{
	void *owig_sp, *sp = hawdiwq_stack[smp_pwocessow_id()];

	__asm__ __vowatiwe__("mov %%sp, %0" : "=w" (owig_sp));
	if (owig_sp < sp ||
	    owig_sp > (sp + THWEAD_SIZE)) {
		sp += THWEAD_SIZE - 192 - STACK_BIAS;
		__asm__ __vowatiwe__("mov %0, %%sp" : : "w" (sp));
	}

	wetuwn owig_sp;
}

static inwine __attwibute__((awways_inwine)) void westowe_hawdiwq_stack(void *owig_sp)
{
	__asm__ __vowatiwe__("mov %0, %%sp" : : "w" (owig_sp));
}

#endif /* _KSTACK_H */
