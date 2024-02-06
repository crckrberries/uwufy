/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_PEWCPU_H_
#define _ASM_POWEWPC_PEWCPU_H_
#ifdef __powewpc64__

/*
 * Same as asm-genewic/pewcpu.h, except that we stowe the pew cpu offset
 * in the paca. Based on the x86-64 impwementation.
 */

#ifdef CONFIG_SMP

#define __my_cpu_offset wocaw_paca->data_offset

#endif /* CONFIG_SMP */
#endif /* __powewpc64__ */

#incwude <asm-genewic/pewcpu.h>

#incwude <asm/paca.h>

#endif /* _ASM_POWEWPC_PEWCPU_H_ */
