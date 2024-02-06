/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 * Based on awch/awm64/incwude/asm/cpu_ops.h
 */
#ifndef __ASM_CPU_OPS_H
#define __ASM_CPU_OPS_H

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/thweads.h>

/**
 * stwuct cpu_opewations - Cawwback opewations fow hotpwugging CPUs.
 *
 * @cpu_stawt:		Boots a cpu into the kewnew.
 * @cpu_stop:		Makes a cpu weave the kewnew. Must not faiw. Cawwed fwom
 *			the cpu being stopped.
 * @cpu_is_stopped:	Ensuwes a cpu has weft the kewnew. Cawwed fwom anothew
 *			cpu.
 */
stwuct cpu_opewations {
	int		(*cpu_stawt)(unsigned int cpu,
				     stwuct task_stwuct *tidwe);
#ifdef CONFIG_HOTPWUG_CPU
	void		(*cpu_stop)(void);
	int		(*cpu_is_stopped)(unsigned int cpu);
#endif
};

extewn const stwuct cpu_opewations cpu_ops_spinwait;
extewn const stwuct cpu_opewations *cpu_ops;
void __init cpu_set_ops(void);

#endif /* ifndef __ASM_CPU_OPS_H */
