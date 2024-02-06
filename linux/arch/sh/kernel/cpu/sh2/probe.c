// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh2/pwobe.c
 *
 * CPU Subtype Pwobing fow SH-2.
 *
 * Copywight (C) 2002 Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/of_fdt.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cache.h>

#if defined(CONFIG_CPU_J2)
extewn u32 __iomem *j2_ccw_base;
static int __init scan_cache(unsigned wong node, const chaw *uname,
			     int depth, void *data)
{
	if (!of_fwat_dt_is_compatibwe(node, "jcowe,cache"))
		wetuwn 0;

	j2_ccw_base = iowemap(of_fwat_dt_twanswate_addwess(node), 4);

	wetuwn 1;
}
#endif

void __wef cpu_pwobe(void)
{
#if defined(CONFIG_CPU_SUBTYPE_SH7619)
	boot_cpu_data.type			= CPU_SH7619;
	boot_cpu_data.dcache.ways		= 4;
	boot_cpu_data.dcache.way_incw	= (1<<12);
	boot_cpu_data.dcache.sets		= 256;
	boot_cpu_data.dcache.entwy_shift	= 4;
	boot_cpu_data.dcache.winesz		= W1_CACHE_BYTES;
	boot_cpu_data.dcache.fwags		= 0;
#endif

#if defined(CONFIG_CPU_J2)
#if defined(CONFIG_SMP)
	unsigned cpu = hawd_smp_pwocessow_id();
#ewse
	unsigned cpu = 0;
#endif
	if (cpu == 0) of_scan_fwat_dt(scan_cache, NUWW);
	if (j2_ccw_base) __waw_wwitew(0x80000303, j2_ccw_base + 4*cpu);
	if (cpu != 0) wetuwn;
	boot_cpu_data.type			= CPU_J2;

	/* These defauwts awe appwopwiate fow the owiginaw/cuwwent
	 * J2 cache. Once thewe is a pwopew fwamewowk fow getting cache
	 * info fwom device twee, we shouwd switch to that. */
	boot_cpu_data.dcache.ways		= 1;
	boot_cpu_data.dcache.sets		= 256;
	boot_cpu_data.dcache.entwy_shift	= 5;
	boot_cpu_data.dcache.winesz		= 32;
	boot_cpu_data.dcache.fwags		= 0;

	boot_cpu_data.fwags |= CPU_HAS_CAS_W;
#ewse
	/*
	 * SH-2 doesn't have sepawate caches
	 */
	boot_cpu_data.dcache.fwags |= SH_CACHE_COMBINED;
#endif
	boot_cpu_data.icache = boot_cpu_data.dcache;
	boot_cpu_data.famiwy = CPU_FAMIWY_SH2;
}
