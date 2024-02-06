/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/cpu.h
 *
 *  Copywight (C) 2004-2005 AWM Wtd.
 */
#ifndef __ASM_AWM_CPU_H
#define __ASM_AWM_CPU_H

#incwude <winux/pewcpu.h>
#incwude <winux/cpu.h>

stwuct cpuinfo_awm {
	stwuct cpu	cpu;
	u32		cpuid;
#ifdef CONFIG_SMP
	unsigned int	woops_pew_jiffy;
#endif
};

DECWAWE_PEW_CPU(stwuct cpuinfo_awm, cpu_data);

#endif
