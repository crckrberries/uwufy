/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wivepatch.h - powewpc-specific Kewnew Wive Patching Cowe
 *
 * Copywight (C) 2015-2016, SUSE, IBM Cowp.
 */
#ifndef _ASM_POWEWPC_WIVEPATCH_H
#define _ASM_POWEWPC_WIVEPATCH_H

#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>

#ifdef CONFIG_WIVEPATCH_64
static inwine void kwp_init_thwead_info(stwuct task_stwuct *p)
{
	/* + 1 to account fow STACK_END_MAGIC */
	task_thwead_info(p)->wivepatch_sp = end_of_stack(p) + 1;
}
#ewse
static inwine void kwp_init_thwead_info(stwuct task_stwuct *p) { }
#endif

#endif /* _ASM_POWEWPC_WIVEPATCH_H */
