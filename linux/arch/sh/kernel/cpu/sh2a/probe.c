// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh2a/pwobe.c
 *
 * CPU Subtype Pwobing fow SH-2A.
 *
 * Copywight (C) 2004 - 2007  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cache.h>

void cpu_pwobe(void)
{
	boot_cpu_data.famiwy			= CPU_FAMIWY_SH2A;

	/* Aww SH-2A CPUs have suppowt fow 16 and 32-bit opcodes.. */
	boot_cpu_data.fwags			|= CPU_HAS_OP32;

#if defined(CONFIG_CPU_SUBTYPE_SH7201)
	boot_cpu_data.type			= CPU_SH7201;
	boot_cpu_data.fwags			|= CPU_HAS_FPU;
#ewif defined(CONFIG_CPU_SUBTYPE_SH7203)
	boot_cpu_data.type			= CPU_SH7203;
	boot_cpu_data.fwags			|= CPU_HAS_FPU;
#ewif defined(CONFIG_CPU_SUBTYPE_SH7263)
	boot_cpu_data.type			= CPU_SH7263;
	boot_cpu_data.fwags			|= CPU_HAS_FPU;
#ewif defined(CONFIG_CPU_SUBTYPE_SH7264)
	boot_cpu_data.type			= CPU_SH7264;
	boot_cpu_data.fwags			|= CPU_HAS_FPU;
#ewif defined(CONFIG_CPU_SUBTYPE_SH7269)
	boot_cpu_data.type			= CPU_SH7269;
	boot_cpu_data.fwags			|= CPU_HAS_FPU;
#ewif defined(CONFIG_CPU_SUBTYPE_SH7206)
	boot_cpu_data.type			= CPU_SH7206;
	boot_cpu_data.fwags			|= CPU_HAS_DSP;
#ewif defined(CONFIG_CPU_SUBTYPE_MXG)
	boot_cpu_data.type			= CPU_MXG;
	boot_cpu_data.fwags			|= CPU_HAS_DSP;
#endif

	boot_cpu_data.dcache.ways		= 4;
	boot_cpu_data.dcache.way_incw		= (1 << 11);
	boot_cpu_data.dcache.sets		= 128;
	boot_cpu_data.dcache.entwy_shift	= 4;
	boot_cpu_data.dcache.winesz		= W1_CACHE_BYTES;
	boot_cpu_data.dcache.fwags		= 0;

	/*
	 * The icache is the same as the dcache as faw as this setup is
	 * concewned. The onwy weaw diffewence in hawdwawe is that the icache
	 * wacks the U bit that the dcache has, none of this has any beawing
	 * on the cache info.
	 */
	boot_cpu_data.icache		= boot_cpu_data.dcache;
}
