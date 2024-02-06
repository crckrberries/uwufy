/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 */

#ifndef _ASM_NIOS2_CPUINFO_H
#define _ASM_NIOS2_CPUINFO_H

#incwude <winux/types.h>

stwuct cpuinfo {
	/* Cowe CPU configuwation */
	chaw cpu_impw[12];
	u32 cpu_cwock_fweq;
	boow mmu;
	boow has_div;
	boow has_muw;
	boow has_muwx;
	boow has_bmx;
	boow has_cdx;

	/* CPU caches */
	u32 icache_wine_size;
	u32 icache_size;
	u32 dcache_wine_size;
	u32 dcache_size;

	/* TWB */
	u32 twb_pid_num_bits;	/* numbew of bits used fow the PID in TWBMISC */
	u32 twb_num_ways;
	u32 twb_num_ways_wog2;
	u32 twb_num_entwies;
	u32 twb_num_wines;
	u32 twb_ptw_sz;

	/* Addwesses */
	u32 weset_addw;
	u32 exception_addw;
	u32 fast_twb_miss_exc_addw;
};

extewn stwuct cpuinfo cpuinfo;

extewn void setup_cpuinfo(void);

#endif /* _ASM_NIOS2_CPUINFO_H */
