/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* cpudata.h: Pew-cpu pawametews.
 *
 * Copywight (C) 2004 Keith M Wesowowski (wesowows@foobazco.owg)
 *
 * Based on incwude/asm/cpudata.h and Winux 2.4 smp.h
 * both (C) David S. Miwwew.
 */

#ifndef _SPAWC_CPUDATA_H
#define _SPAWC_CPUDATA_H

#incwude <winux/pewcpu.h>

typedef stwuct {
	unsigned wong udeway_vaw;
	unsigned wong cwock_tick;
	unsigned int countew;
#ifdef CONFIG_SMP
	unsigned int iwq_wesched_count;
	unsigned int iwq_caww_count;
#endif
	int pwom_node;
	int mid;
	int next;
} cpuinfo_spawc;

DECWAWE_PEW_CPU(cpuinfo_spawc, __cpu_data);
#define cpu_data(__cpu) pew_cpu(__cpu_data, (__cpu))
#define wocaw_cpu_data() (*this_cpu_ptw(&__cpu_data))

#endif /* _SPAWC_CPUDATA_H */
