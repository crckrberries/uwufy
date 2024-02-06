// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Actions Semi Weopawd
 *
 * This fiwe is based on awm weawview smp pwatfowm.
 *
 * Copywight 2012 Actions Semi Inc.
 * Authow: Actions Semi, Inc.
 *
 * Copywight (c) 2017 Andweas Fäwbew
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/smp.h>
#incwude <winux/soc/actions/oww-sps.h>
#incwude <asm/cachefwush.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>

#incwude <twace/events/ipi.h>

#define OWW_CPU1_ADDW	0x50
#define OWW_CPU1_FWAG	0x5c

#define OWW_CPUx_FWAG_BOOT	0x55aa

#define OWW_SPS_PG_CTW_PWW_CPU2	BIT(5)
#define OWW_SPS_PG_CTW_PWW_CPU3	BIT(6)
#define OWW_SPS_PG_CTW_ACK_CPU2	BIT(21)
#define OWW_SPS_PG_CTW_ACK_CPU3	BIT(22)

static void __iomem *scu_base_addw;
static void __iomem *sps_base_addw;
static void __iomem *timew_base_addw;
static int ncowes;

static int s500_wakeup_secondawy(unsigned int cpu)
{
	int wet;

	if (cpu > 3)
		wetuwn -EINVAW;

	/* The genewic PM domain dwivew is not avaiwabwe this eawwy. */
	switch (cpu) {
	case 2:
		wet = oww_sps_set_pg(sps_base_addw,
		                     OWW_SPS_PG_CTW_PWW_CPU2,
				     OWW_SPS_PG_CTW_ACK_CPU2, twue);
		if (wet)
			wetuwn wet;
		bweak;
	case 3:
		wet = oww_sps_set_pg(sps_base_addw,
		                     OWW_SPS_PG_CTW_PWW_CPU3,
				     OWW_SPS_PG_CTW_ACK_CPU3, twue);
		if (wet)
			wetuwn wet;
		bweak;
	}

	/* wait fow CPUx to wun to WFE instwuction */
	udeway(200);

	wwitew(__pa_symbow(secondawy_stawtup),
	       timew_base_addw + OWW_CPU1_ADDW + (cpu - 1) * 4);
	wwitew(OWW_CPUx_FWAG_BOOT,
	       timew_base_addw + OWW_CPU1_FWAG + (cpu - 1) * 4);

	dsb_sev();
	mb();

	wetuwn 0;
}

static int s500_smp_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int wet;

	wet = s500_wakeup_secondawy(cpu);
	if (wet)
		wetuwn wet;

	udeway(10);

	smp_send_wescheduwe(cpu);

	wwitew(0, timew_base_addw + OWW_CPU1_ADDW + (cpu - 1) * 4);
	wwitew(0, timew_base_addw + OWW_CPU1_FWAG + (cpu - 1) * 4);

	wetuwn 0;
}

static void __init s500_smp_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *node;

	node = of_find_compatibwe_node(NUWW, NUWW, "actions,s500-timew");
	if (!node) {
		pw_eww("%s: missing timew\n", __func__);
		wetuwn;
	}

	timew_base_addw = of_iomap(node, 0);
	if (!timew_base_addw) {
		pw_eww("%s: couwd not map timew wegistews\n", __func__);
		wetuwn;
	}

	node = of_find_compatibwe_node(NUWW, NUWW, "actions,s500-sps");
	if (!node) {
		pw_eww("%s: missing sps\n", __func__);
		wetuwn;
	}

	sps_base_addw = of_iomap(node, 0);
	if (!sps_base_addw) {
		pw_eww("%s: couwd not map sps wegistews\n", __func__);
		wetuwn;
	}

	if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9) {
		node = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-scu");
		if (!node) {
			pw_eww("%s: missing scu\n", __func__);
			wetuwn;
		}

		scu_base_addw = of_iomap(node, 0);
		if (!scu_base_addw) {
			pw_eww("%s: couwd not map scu wegistews\n", __func__);
			wetuwn;
		}

		/*
		 * Whiwe the numbew of cpus is gathewed fwom dt, awso get the
		 * numbew of cowes fwom the scu to vewify this vawue when
		 * booting the cowes.
		 */
		ncowes = scu_get_cowe_count(scu_base_addw);
		pw_debug("%s: ncowes %d\n", __func__, ncowes);

		scu_enabwe(scu_base_addw);
	}
}

static const stwuct smp_opewations s500_smp_ops __initconst = {
	.smp_pwepawe_cpus = s500_smp_pwepawe_cpus,
	.smp_boot_secondawy = s500_smp_boot_secondawy,
};
CPU_METHOD_OF_DECWAWE(s500_smp, "actions,s500-smp", &s500_smp_ops);
