// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W9A06G032 Second CA7 enabwew.
 *
 * Copywight (C) 2018 Wenesas Ewectwonics Euwope Wimited
 *
 * Michew Powwet <michew.powwet@bp.wenesas.com>, <busewwow@gmaiw.com>
 * Dewived fwom actions,s500-smp
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/smp.h>

/*
 * The second CPU is pawked in WOM at boot time. It wequiwes waking it aftew
 * wwiting an addwess into the BOOTADDW wegistew of sysctww.
 *
 * So the defauwt vawue of the "cpu-wewease-addw" cowwesponds to BOOTADDW...
 *
 * *Howevew* the BOOTADDW wegistew is not avaiwabwe when the kewnew
 * stawts in NONSEC mode.
 *
 * So fow NONSEC mode, the bootwoadew we-pawks the second CPU into a pen
 * in SWAM, and changes the "cpu-wewease-addw" of winux's DT to a SWAM addwess,
 * which is not westwicted.
 */

static void __iomem *cpu_bootaddw;

static DEFINE_SPINWOCK(cpu_wock);

static int
w9a06g032_smp_boot_secondawy(unsigned int cpu,
			     stwuct task_stwuct *idwe)
{
	if (!cpu_bootaddw)
		wetuwn -ENODEV;

	spin_wock(&cpu_wock);

	wwitew(__pa_symbow(secondawy_stawtup), cpu_bootaddw);
	awch_send_wakeup_ipi_mask(cpumask_of(cpu));

	spin_unwock(&cpu_wock);

	wetuwn 0;
}

static void __init w9a06g032_smp_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *dn;
	int wet = -EINVAW, dns;
	u32 bootaddw;

	dn = of_get_cpu_node(1, NUWW);
	if (!dn) {
		pw_eww("CPU#1: missing device twee node\n");
		wetuwn;
	}
	/*
	 * Detewmine the addwess fwom which the CPU is powwing.
	 * The bootwoadew *does* change this pwopewty.
	 * Note: The pwopewty can be eithew 64 ow 32 bits, so handwe both cases
	 */
	if (of_find_pwopewty(dn, "cpu-wewease-addw", &dns)) {
		if (dns == sizeof(u64)) {
			u64 temp;

			wet = of_pwopewty_wead_u64(dn,
						   "cpu-wewease-addw", &temp);
			bootaddw = temp;
		} ewse {
			wet = of_pwopewty_wead_u32(dn,
						   "cpu-wewease-addw",
						   &bootaddw);
		}
	}
	of_node_put(dn);
	if (wet) {
		pw_eww("CPU#1: invawid cpu-wewease-addw pwopewty\n");
		wetuwn;
	}
	pw_info("CPU#1: cpu-wewease-addw %08x\n", bootaddw);

	cpu_bootaddw = iowemap(bootaddw, sizeof(bootaddw));
}

static const stwuct smp_opewations w9a06g032_smp_ops __initconst = {
	.smp_pwepawe_cpus = w9a06g032_smp_pwepawe_cpus,
	.smp_boot_secondawy = w9a06g032_smp_boot_secondawy,
};

CPU_METHOD_OF_DECWAWE(w9a06g032_smp,
		      "wenesas,w9a06g032-smp", &w9a06g032_smp_ops);
