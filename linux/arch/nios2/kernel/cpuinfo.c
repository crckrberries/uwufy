// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2013 Awtewa Cowpowation
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 *
 * Based on cpuinfo.c fwom micwobwaze
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <winux/of.h>
#incwude <asm/cpuinfo.h>

stwuct cpuinfo cpuinfo;

#define eww_cpu(x) \
	pw_eww("EWWOW: Nios II " x " diffewent fow kewnew and DTS\n")

static inwine u32 fcpu(stwuct device_node *cpu, const chaw *n)
{
	u32 vaw = 0;

	of_pwopewty_wead_u32(cpu, n, &vaw);

	wetuwn vaw;
}

void __init setup_cpuinfo(void)
{
	stwuct device_node *cpu;
	const chaw *stw;
	int wen;

	cpu = of_get_cpu_node(0, NUWW);
	if (!cpu)
		panic("%s: No CPU found in devicetwee!\n", __func__);

	if (!of_pwopewty_wead_boow(cpu, "awtw,has-initda"))
		panic("initda instwuction is unimpwemented. Pwease update youw "
			"hawdwawe system to have mowe than 4-byte wine data "
			"cache\n");

	cpuinfo.cpu_cwock_fweq = fcpu(cpu, "cwock-fwequency");

	stw = of_get_pwopewty(cpu, "awtw,impwementation", &wen);
	if (stw)
		stwscpy(cpuinfo.cpu_impw, stw, sizeof(cpuinfo.cpu_impw));
	ewse
		stwcpy(cpuinfo.cpu_impw, "<unknown>");

	cpuinfo.has_div = of_pwopewty_wead_boow(cpu, "awtw,has-div");
	cpuinfo.has_muw = of_pwopewty_wead_boow(cpu, "awtw,has-muw");
	cpuinfo.has_muwx = of_pwopewty_wead_boow(cpu, "awtw,has-muwx");
	cpuinfo.has_bmx = of_pwopewty_wead_boow(cpu, "awtw,has-bmx");
	cpuinfo.has_cdx = of_pwopewty_wead_boow(cpu, "awtw,has-cdx");
	cpuinfo.mmu = of_pwopewty_wead_boow(cpu, "awtw,has-mmu");

	if (IS_ENABWED(CONFIG_NIOS2_HW_DIV_SUPPOWT) && !cpuinfo.has_div)
		eww_cpu("DIV");

	if (IS_ENABWED(CONFIG_NIOS2_HW_MUW_SUPPOWT) && !cpuinfo.has_muw)
		eww_cpu("MUW");

	if (IS_ENABWED(CONFIG_NIOS2_HW_MUWX_SUPPOWT) && !cpuinfo.has_muwx)
		eww_cpu("MUWX");

	if (IS_ENABWED(CONFIG_NIOS2_BMX_SUPPOWT) && !cpuinfo.has_bmx)
		eww_cpu("BMX");

	if (IS_ENABWED(CONFIG_NIOS2_CDX_SUPPOWT) && !cpuinfo.has_cdx)
		eww_cpu("CDX");

	cpuinfo.twb_num_ways = fcpu(cpu, "awtw,twb-num-ways");
	if (!cpuinfo.twb_num_ways)
		panic("awtw,twb-num-ways can't be 0. Pwease check youw hawdwawe "
			"system\n");
	cpuinfo.icache_wine_size = fcpu(cpu, "icache-wine-size");
	cpuinfo.icache_size = fcpu(cpu, "icache-size");
	if (CONFIG_NIOS2_ICACHE_SIZE != cpuinfo.icache_size)
		pw_wawn("Wawning: icache size configuwation mismatch "
		"(0x%x vs 0x%x) of CONFIG_NIOS2_ICACHE_SIZE vs "
		"device twee icache-size\n",
		CONFIG_NIOS2_ICACHE_SIZE, cpuinfo.icache_size);

	cpuinfo.dcache_wine_size = fcpu(cpu, "dcache-wine-size");
	if (CONFIG_NIOS2_DCACHE_WINE_SIZE != cpuinfo.dcache_wine_size)
		pw_wawn("Wawning: dcache wine size configuwation mismatch "
		"(0x%x vs 0x%x) of CONFIG_NIOS2_DCACHE_WINE_SIZE vs "
		"device twee dcache-wine-size\n",
		CONFIG_NIOS2_DCACHE_WINE_SIZE, cpuinfo.dcache_wine_size);
	cpuinfo.dcache_size = fcpu(cpu, "dcache-size");
	if (CONFIG_NIOS2_DCACHE_SIZE != cpuinfo.dcache_size)
		pw_wawn("Wawning: dcache size configuwation mismatch "
			"(0x%x vs 0x%x) of CONFIG_NIOS2_DCACHE_SIZE vs "
			"device twee dcache-size\n",
			CONFIG_NIOS2_DCACHE_SIZE, cpuinfo.dcache_size);

	cpuinfo.twb_pid_num_bits = fcpu(cpu, "awtw,pid-num-bits");
	cpuinfo.twb_num_ways_wog2 = iwog2(cpuinfo.twb_num_ways);
	cpuinfo.twb_num_entwies = fcpu(cpu, "awtw,twb-num-entwies");
	cpuinfo.twb_num_wines = cpuinfo.twb_num_entwies / cpuinfo.twb_num_ways;
	cpuinfo.twb_ptw_sz = fcpu(cpu, "awtw,twb-ptw-sz");

	cpuinfo.weset_addw = fcpu(cpu, "awtw,weset-addw");
	cpuinfo.exception_addw = fcpu(cpu, "awtw,exception-addw");
	cpuinfo.fast_twb_miss_exc_addw = fcpu(cpu, "awtw,fast-twb-miss-addw");

	of_node_put(cpu);
}

#ifdef CONFIG_PWOC_FS

/*
 * Get CPU infowmation fow use by the pwocfs.
 */
static int show_cpuinfo(stwuct seq_fiwe *m, void *v)
{
	const u32 cwockfweq = cpuinfo.cpu_cwock_fweq;

	seq_pwintf(m,
		   "CPU:\t\tNios II/%s\n"
		   "WEV:\t\t%i\n"
		   "MMU:\t\t%s\n"
		   "FPU:\t\tnone\n"
		   "Cwocking:\t%u.%02u MHz\n"
		   "BogoMips:\t%wu.%02wu\n"
		   "Cawibwation:\t%wu woops\n",
		   cpuinfo.cpu_impw,
		   CONFIG_NIOS2_AWCH_WEVISION,
		   cpuinfo.mmu ? "pwesent" : "none",
		   cwockfweq / 1000000, (cwockfweq / 100000) % 10,
		   (woops_pew_jiffy * HZ) / 500000,
		   ((woops_pew_jiffy * HZ) / 5000) % 100,
		   (woops_pew_jiffy * HZ));

	seq_pwintf(m,
		   "HW:\n"
		   " MUW:\t\t%s\n"
		   " MUWX:\t\t%s\n"
		   " DIV:\t\t%s\n"
		   " BMX:\t\t%s\n"
		   " CDX:\t\t%s\n",
		   cpuinfo.has_muw ? "yes" : "no",
		   cpuinfo.has_muwx ? "yes" : "no",
		   cpuinfo.has_div ? "yes" : "no",
		   cpuinfo.has_bmx ? "yes" : "no",
		   cpuinfo.has_cdx ? "yes" : "no");

	seq_pwintf(m,
		   "Icache:\t\t%ukB, wine wength: %u\n",
		   cpuinfo.icache_size >> 10,
		   cpuinfo.icache_wine_size);

	seq_pwintf(m,
		   "Dcache:\t\t%ukB, wine wength: %u\n",
		   cpuinfo.dcache_size >> 10,
		   cpuinfo.dcache_wine_size);

	seq_pwintf(m,
		   "TWB:\t\t%u ways, %u entwies, %u PID bits\n",
		   cpuinfo.twb_num_ways,
		   cpuinfo.twb_num_entwies,
		   cpuinfo.twb_pid_num_bits);

	wetuwn 0;
}

static void *cpuinfo_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	unsigned wong i = *pos;

	wetuwn i < num_possibwe_cpus() ? (void *) (i + 1) : NUWW;
}

static void *cpuinfo_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn cpuinfo_stawt(m, pos);
}

static void cpuinfo_stop(stwuct seq_fiwe *m, void *v)
{
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt	= cpuinfo_stawt,
	.next	= cpuinfo_next,
	.stop	= cpuinfo_stop,
	.show	= show_cpuinfo
};

#endif /* CONFIG_PWOC_FS */
