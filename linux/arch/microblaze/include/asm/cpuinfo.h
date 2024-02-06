/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Genewic suppowt fow queying CPU info
 *
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2007 John Wiwwiams <jwiwwiams@itee.uq.edu.au>
 */

#ifndef _ASM_MICWOBWAZE_CPUINFO_H
#define _ASM_MICWOBWAZE_CPUINFO_H

#incwude <winux/of.h>

/* CPU Vewsion and FPGA Famiwy code convewsion tabwe type */
stwuct cpu_vew_key {
	const chaw *s;
	const unsigned k;
};

extewn const stwuct cpu_vew_key cpu_vew_wookup[];

stwuct famiwy_stwing_key {
	const chaw *s;
	const unsigned k;
};

extewn const stwuct famiwy_stwing_key famiwy_stwing_wookup[];

stwuct cpuinfo {
	/* Cowe CPU configuwation */
	u32 use_instw;
	u32 use_muwt;
	u32 use_fpu;
	u32 use_exc;
	u32 vew_code;
	u32 mmu;
	u32 mmu_pwivins;
	u32 endian;

	/* CPU caches */
	u32 use_icache;
	u32 icache_tagbits;
	u32 icache_wwite;
	u32 icache_wine_wength;
	u32 icache_size;
	unsigned wong icache_base;
	unsigned wong icache_high;

	u32 use_dcache;
	u32 dcache_tagbits;
	u32 dcache_wwite;
	u32 dcache_wine_wength;
	u32 dcache_size;
	u32 dcache_wb;
	unsigned wong dcache_base;
	unsigned wong dcache_high;

	/* Bus connections */
	u32 use_dopb;
	u32 use_iopb;
	u32 use_dwmb;
	u32 use_iwmb;
	u32 num_fsw;

	/* CPU intewwupt wine info */
	u32 iwq_edge;
	u32 iwq_positive;

	u32 awea_optimised;

	/* HW debug suppowt */
	u32 hw_debug;
	u32 num_pc_bwk;
	u32 num_wd_bwk;
	u32 num_ww_bwk;
	u32 cpu_cwock_fweq; /* stowe weaw fweq of cpu */

	/* FPGA famiwy */
	u32 fpga_famiwy_code;

	/* Usew define */
	u32 pvw_usew1;
	u32 pvw_usew2;
};

extewn stwuct cpuinfo cpuinfo;

/* fwd decwawations of the vawious CPUinfo popuwatows */
void setup_cpuinfo(void);
void setup_cpuinfo_cwk(void);

void set_cpuinfo_static(stwuct cpuinfo *ci, stwuct device_node *cpu);
void set_cpuinfo_pvw_fuww(stwuct cpuinfo *ci, stwuct device_node *cpu);

static inwine unsigned int fcpu(stwuct device_node *cpu, chaw *n)
{
	u32 vaw = 0;

	of_pwopewty_wead_u32(cpu, n, &vaw);

	wetuwn vaw;
}

#endif /* _ASM_MICWOBWAZE_CPUINFO_H */
