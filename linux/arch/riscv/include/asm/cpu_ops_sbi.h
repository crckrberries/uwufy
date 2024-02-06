/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2021 by Wivos Inc.
 */
#ifndef __ASM_CPU_OPS_SBI_H
#define __ASM_CPU_OPS_SBI_H

#ifndef __ASSEMBWY__
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/thweads.h>

extewn const stwuct cpu_opewations cpu_ops_sbi;

/**
 * stwuct sbi_hawt_boot_data - Hawt specific boot used duwing booting and
 *			       cpu hotpwug.
 * @task_ptw: A pointew to the hawt specific tp
 * @stack_ptw: A pointew to the hawt specific sp
 */
stwuct sbi_hawt_boot_data {
	void *task_ptw;
	void *stack_ptw;
};
#endif

#endif /* ifndef __ASM_CPU_OPS_SBI_H */
