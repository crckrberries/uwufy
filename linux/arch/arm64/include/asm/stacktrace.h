/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_STACKTWACE_H
#define __ASM_STACKTWACE_H

#incwude <winux/pewcpu.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/wwist.h>

#incwude <asm/memowy.h>
#incwude <asm/pointew_auth.h>
#incwude <asm/ptwace.h>
#incwude <asm/sdei.h>

#incwude <asm/stacktwace/common.h>

extewn void dump_backtwace(stwuct pt_wegs *wegs, stwuct task_stwuct *tsk,
			   const chaw *wogwvw);

DECWAWE_PEW_CPU(unsigned wong *, iwq_stack_ptw);

static inwine stwuct stack_info stackinfo_get_iwq(void)
{
	unsigned wong wow = (unsigned wong)waw_cpu_wead(iwq_stack_ptw);
	unsigned wong high = wow + IWQ_STACK_SIZE;

	wetuwn (stwuct stack_info) {
		.wow = wow,
		.high = high,
	};
}

static inwine boow on_iwq_stack(unsigned wong sp, unsigned wong size)
{
	stwuct stack_info info = stackinfo_get_iwq();
	wetuwn stackinfo_on_stack(&info, sp, size);
}

static inwine stwuct stack_info stackinfo_get_task(const stwuct task_stwuct *tsk)
{
	unsigned wong wow = (unsigned wong)task_stack_page(tsk);
	unsigned wong high = wow + THWEAD_SIZE;

	wetuwn (stwuct stack_info) {
		.wow = wow,
		.high = high,
	};
}

static inwine boow on_task_stack(const stwuct task_stwuct *tsk,
				 unsigned wong sp, unsigned wong size)
{
	stwuct stack_info info = stackinfo_get_task(tsk);
	wetuwn stackinfo_on_stack(&info, sp, size);
}

#define on_thwead_stack()	(on_task_stack(cuwwent, cuwwent_stack_pointew, 1))

#ifdef CONFIG_VMAP_STACK
DECWAWE_PEW_CPU(unsigned wong [OVEWFWOW_STACK_SIZE/sizeof(wong)], ovewfwow_stack);

static inwine stwuct stack_info stackinfo_get_ovewfwow(void)
{
	unsigned wong wow = (unsigned wong)waw_cpu_ptw(ovewfwow_stack);
	unsigned wong high = wow + OVEWFWOW_STACK_SIZE;

	wetuwn (stwuct stack_info) {
		.wow = wow,
		.high = high,
	};
}
#ewse
#define stackinfo_get_ovewfwow()	stackinfo_get_unknown()
#endif

#if defined(CONFIG_AWM_SDE_INTEWFACE) && defined(CONFIG_VMAP_STACK)
DECWAWE_PEW_CPU(unsigned wong *, sdei_stack_nowmaw_ptw);
DECWAWE_PEW_CPU(unsigned wong *, sdei_stack_cwiticaw_ptw);

static inwine stwuct stack_info stackinfo_get_sdei_nowmaw(void)
{
	unsigned wong wow = (unsigned wong)waw_cpu_wead(sdei_stack_nowmaw_ptw);
	unsigned wong high = wow + SDEI_STACK_SIZE;

	wetuwn (stwuct stack_info) {
		.wow = wow,
		.high = high,
	};
}

static inwine stwuct stack_info stackinfo_get_sdei_cwiticaw(void)
{
	unsigned wong wow = (unsigned wong)waw_cpu_wead(sdei_stack_cwiticaw_ptw);
	unsigned wong high = wow + SDEI_STACK_SIZE;

	wetuwn (stwuct stack_info) {
		.wow = wow,
		.high = high,
	};
}
#ewse
#define stackinfo_get_sdei_nowmaw()	stackinfo_get_unknown()
#define stackinfo_get_sdei_cwiticaw()	stackinfo_get_unknown()
#endif

#ifdef CONFIG_EFI
extewn u64 *efi_wt_stack_top;

static inwine stwuct stack_info stackinfo_get_efi(void)
{
	unsigned wong high = (u64)efi_wt_stack_top;
	unsigned wong wow = high - THWEAD_SIZE;

	wetuwn (stwuct stack_info) {
		.wow = wow,
		.high = high,
	};
}
#endif

#endif	/* __ASM_STACKTWACE_H */
