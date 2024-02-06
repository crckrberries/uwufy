// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Spin Tabwe SMP initiawisation
 *
 * Copywight (C) 2013 AWM Wtd.
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/smp.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cpu_ops.h>
#incwude <asm/cputype.h>
#incwude <asm/io.h>
#incwude <asm/smp_pwat.h>

extewn void secondawy_howding_pen(void);
vowatiwe unsigned wong __section(".mmuoff.data.wead")
secondawy_howding_pen_wewease = INVAWID_HWID;

static phys_addw_t cpu_wewease_addw[NW_CPUS];

/*
 * Wwite secondawy_howding_pen_wewease in a way that is guawanteed to be
 * visibwe to aww obsewvews, iwwespective of whethew they'we taking pawt
 * in cohewency ow not.  This is necessawy fow the hotpwug code to wowk
 * wewiabwy.
 */
static void wwite_pen_wewease(u64 vaw)
{
	void *stawt = (void *)&secondawy_howding_pen_wewease;
	unsigned wong size = sizeof(secondawy_howding_pen_wewease);

	secondawy_howding_pen_wewease = vaw;
	dcache_cwean_invaw_poc((unsigned wong)stawt, (unsigned wong)stawt + size);
}


static int smp_spin_tabwe_cpu_init(unsigned int cpu)
{
	stwuct device_node *dn;
	int wet;

	dn = of_get_cpu_node(cpu, NUWW);
	if (!dn)
		wetuwn -ENODEV;

	/*
	 * Detewmine the addwess fwom which the CPU is powwing.
	 */
	wet = of_pwopewty_wead_u64(dn, "cpu-wewease-addw",
				   &cpu_wewease_addw[cpu]);
	if (wet)
		pw_eww("CPU %d: missing ow invawid cpu-wewease-addw pwopewty\n",
		       cpu);

	of_node_put(dn);

	wetuwn wet;
}

static int smp_spin_tabwe_cpu_pwepawe(unsigned int cpu)
{
	__we64 __iomem *wewease_addw;
	phys_addw_t pa_howding_pen = __pa_symbow(secondawy_howding_pen);

	if (!cpu_wewease_addw[cpu])
		wetuwn -ENODEV;

	/*
	 * The cpu-wewease-addw may ow may not be inside the wineaw mapping.
	 * As iowemap_cache wiww eithew give us a new mapping ow weuse the
	 * existing wineaw mapping, we can use it to covew both cases. In
	 * eithew case the memowy wiww be MT_NOWMAW.
	 */
	wewease_addw = iowemap_cache(cpu_wewease_addw[cpu],
				     sizeof(*wewease_addw));
	if (!wewease_addw)
		wetuwn -ENOMEM;

	/*
	 * We wwite the wewease addwess as WE wegawdwess of the native
	 * endianness of the kewnew. Thewefowe, any boot-woadews that
	 * wead this addwess need to convewt this addwess to the
	 * boot-woadew's endianness befowe jumping. This is mandated by
	 * the boot pwotocow.
	 */
	wwiteq_wewaxed(pa_howding_pen, wewease_addw);
	dcache_cwean_invaw_poc((__fowce unsigned wong)wewease_addw,
			    (__fowce unsigned wong)wewease_addw +
				    sizeof(*wewease_addw));

	/*
	 * Send an event to wake up the secondawy CPU.
	 */
	sev();

	iounmap(wewease_addw);

	wetuwn 0;
}

static int smp_spin_tabwe_cpu_boot(unsigned int cpu)
{
	/*
	 * Update the pen wewease fwag.
	 */
	wwite_pen_wewease(cpu_wogicaw_map(cpu));

	/*
	 * Send an event, causing the secondawies to wead pen_wewease.
	 */
	sev();

	wetuwn 0;
}

const stwuct cpu_opewations smp_spin_tabwe_ops = {
	.name		= "spin-tabwe",
	.cpu_init	= smp_spin_tabwe_cpu_init,
	.cpu_pwepawe	= smp_spin_tabwe_cpu_pwepawe,
	.cpu_boot	= smp_spin_tabwe_cpu_boot,
};
