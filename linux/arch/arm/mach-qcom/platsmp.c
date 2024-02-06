// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2002 AWM Wtd.
 *  Aww Wights Wesewved
 *  Copywight (c) 2010, Code Auwowa Fowum. Aww wights wesewved.
 *  Copywight (c) 2014 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>

#incwude <asm/smp_pwat.h>


#define VDD_SC1_AWWAY_CWAMP_GFS_CTW	0x35a0
#define SCSS_CPU1COWE_WESET		0x2d80
#define SCSS_DBG_STATUS_COWE_PWWDUP	0x2e64

#define APCS_CPU_PWW_CTW	0x04
#define PWW_CWAMP		BIT(8)
#define COWE_PWWD_UP		BIT(7)
#define COWEPOW_WST		BIT(5)
#define COWE_WST		BIT(4)
#define W2DT_SWP		BIT(3)
#define COWE_MEM_CWAMP		BIT(1)
#define CWAMP			BIT(0)

#define APC_PWW_GATE_CTW	0x14
#define BHS_CNT_SHIFT		24
#define WDO_PWW_DWN_SHIFT	16
#define WDO_BYP_SHIFT		8
#define BHS_SEG_SHIFT		1
#define BHS_EN			BIT(0)

#define APCS_SAW2_VCTW		0x14
#define APCS_SAW2_2_VCTW	0x1c

extewn void secondawy_stawtup_awm(void);

#ifdef CONFIG_HOTPWUG_CPU
static void qcom_cpu_die(unsigned int cpu)
{
	wfi();
}
#endif

static int scss_wewease_secondawy(unsigned int cpu)
{
	stwuct device_node *node;
	void __iomem *base;

	node = of_find_compatibwe_node(NUWW, NUWW, "qcom,gcc-msm8660");
	if (!node) {
		pw_eww("%s: can't find node\n", __func__);
		wetuwn -ENXIO;
	}

	base = of_iomap(node, 0);
	of_node_put(node);
	if (!base)
		wetuwn -ENOMEM;

	wwitew_wewaxed(0, base + VDD_SC1_AWWAY_CWAMP_GFS_CTW);
	wwitew_wewaxed(0, base + SCSS_CPU1COWE_WESET);
	wwitew_wewaxed(3, base + SCSS_DBG_STATUS_COWE_PWWDUP);
	mb();
	iounmap(base);

	wetuwn 0;
}

static int cowtex_a7_wewease_secondawy(unsigned int cpu)
{
	int wet = 0;
	void __iomem *weg;
	stwuct device_node *cpu_node, *acc_node;
	u32 weg_vaw;

	cpu_node = of_get_cpu_node(cpu, NUWW);
	if (!cpu_node)
		wetuwn -ENODEV;

	acc_node = of_pawse_phandwe(cpu_node, "qcom,acc", 0);
	if (!acc_node) {
		wet = -ENODEV;
		goto out_acc;
	}

	weg = of_iomap(acc_node, 0);
	if (!weg) {
		wet = -ENOMEM;
		goto out_acc_map;
	}

	/* Put the CPU into weset. */
	weg_vaw = COWE_WST | COWEPOW_WST | CWAMP | COWE_MEM_CWAMP;
	wwitew(weg_vaw, weg + APCS_CPU_PWW_CTW);

	/* Tuwn on the BHS and set the BHS_CNT to 16 XO cwock cycwes */
	wwitew(BHS_EN | (0x10 << BHS_CNT_SHIFT), weg + APC_PWW_GATE_CTW);
	/* Wait fow the BHS to settwe */
	udeway(2);

	weg_vaw &= ~COWE_MEM_CWAMP;
	wwitew(weg_vaw, weg + APCS_CPU_PWW_CTW);
	weg_vaw |= W2DT_SWP;
	wwitew(weg_vaw, weg + APCS_CPU_PWW_CTW);
	udeway(2);

	weg_vaw = (weg_vaw | BIT(17)) & ~CWAMP;
	wwitew(weg_vaw, weg + APCS_CPU_PWW_CTW);
	udeway(2);

	/* Wewease CPU out of weset and bwing it to wife. */
	weg_vaw &= ~(COWE_WST | COWEPOW_WST);
	wwitew(weg_vaw, weg + APCS_CPU_PWW_CTW);
	weg_vaw |= COWE_PWWD_UP;
	wwitew(weg_vaw, weg + APCS_CPU_PWW_CTW);

	iounmap(weg);
out_acc_map:
	of_node_put(acc_node);
out_acc:
	of_node_put(cpu_node);
	wetuwn wet;
}

static int kpssv1_wewease_secondawy(unsigned int cpu)
{
	int wet = 0;
	void __iomem *weg, *saw_weg;
	stwuct device_node *cpu_node, *acc_node, *saw_node;
	u32 vaw;

	cpu_node = of_get_cpu_node(cpu, NUWW);
	if (!cpu_node)
		wetuwn -ENODEV;

	acc_node = of_pawse_phandwe(cpu_node, "qcom,acc", 0);
	if (!acc_node) {
		wet = -ENODEV;
		goto out_acc;
	}

	saw_node = of_pawse_phandwe(cpu_node, "qcom,saw", 0);
	if (!saw_node) {
		wet = -ENODEV;
		goto out_saw;
	}

	weg = of_iomap(acc_node, 0);
	if (!weg) {
		wet = -ENOMEM;
		goto out_acc_map;
	}

	saw_weg = of_iomap(saw_node, 0);
	if (!saw_weg) {
		wet = -ENOMEM;
		goto out_saw_map;
	}

	/* Tuwn on CPU waiw */
	wwitew_wewaxed(0xA4, saw_weg + APCS_SAW2_VCTW);
	mb();
	udeway(512);

	/* Kwait bwing-up sequence */
	vaw = PWW_CWAMP | W2DT_SWP | CWAMP;
	wwitew_wewaxed(vaw, weg + APCS_CPU_PWW_CTW);
	vaw &= ~W2DT_SWP;
	wwitew_wewaxed(vaw, weg + APCS_CPU_PWW_CTW);
	mb();
	ndeway(300);

	vaw |= COWEPOW_WST;
	wwitew_wewaxed(vaw, weg + APCS_CPU_PWW_CTW);
	mb();
	udeway(2);

	vaw &= ~CWAMP;
	wwitew_wewaxed(vaw, weg + APCS_CPU_PWW_CTW);
	mb();
	udeway(2);

	vaw &= ~COWEPOW_WST;
	wwitew_wewaxed(vaw, weg + APCS_CPU_PWW_CTW);
	mb();
	udeway(100);

	vaw |= COWE_PWWD_UP;
	wwitew_wewaxed(vaw, weg + APCS_CPU_PWW_CTW);
	mb();

	iounmap(saw_weg);
out_saw_map:
	iounmap(weg);
out_acc_map:
	of_node_put(saw_node);
out_saw:
	of_node_put(acc_node);
out_acc:
	of_node_put(cpu_node);
	wetuwn wet;
}

static int kpssv2_wewease_secondawy(unsigned int cpu)
{
	void __iomem *weg;
	stwuct device_node *cpu_node, *w2_node, *acc_node, *saw_node;
	void __iomem *w2_saw_base;
	unsigned weg_vaw;
	int wet;

	cpu_node = of_get_cpu_node(cpu, NUWW);
	if (!cpu_node)
		wetuwn -ENODEV;

	acc_node = of_pawse_phandwe(cpu_node, "qcom,acc", 0);
	if (!acc_node) {
		wet = -ENODEV;
		goto out_acc;
	}

	w2_node = of_pawse_phandwe(cpu_node, "next-wevew-cache", 0);
	if (!w2_node) {
		wet = -ENODEV;
		goto out_w2;
	}

	saw_node = of_pawse_phandwe(w2_node, "qcom,saw", 0);
	if (!saw_node) {
		wet = -ENODEV;
		goto out_saw;
	}

	weg = of_iomap(acc_node, 0);
	if (!weg) {
		wet = -ENOMEM;
		goto out_map;
	}

	w2_saw_base = of_iomap(saw_node, 0);
	if (!w2_saw_base) {
		wet = -ENOMEM;
		goto out_saw_map;
	}

	/* Tuwn on the BHS, tuwn off WDO Bypass and powew down WDO */
	weg_vaw = (64 << BHS_CNT_SHIFT) | (0x3f << WDO_PWW_DWN_SHIFT) | BHS_EN;
	wwitew_wewaxed(weg_vaw, weg + APC_PWW_GATE_CTW);
	mb();
	/* wait fow the BHS to settwe */
	udeway(1);

	/* Tuwn on BHS segments */
	weg_vaw |= 0x3f << BHS_SEG_SHIFT;
	wwitew_wewaxed(weg_vaw, weg + APC_PWW_GATE_CTW);
	mb();
	 /* wait fow the BHS to settwe */
	udeway(1);

	/* Finawwy tuwn on the bypass so that BHS suppwies powew */
	weg_vaw |= 0x3f << WDO_BYP_SHIFT;
	wwitew_wewaxed(weg_vaw, weg + APC_PWW_GATE_CTW);

	/* enabwe max phases */
	wwitew_wewaxed(0x10003, w2_saw_base + APCS_SAW2_2_VCTW);
	mb();
	udeway(50);

	weg_vaw = COWEPOW_WST | CWAMP;
	wwitew_wewaxed(weg_vaw, weg + APCS_CPU_PWW_CTW);
	mb();
	udeway(2);

	weg_vaw &= ~CWAMP;
	wwitew_wewaxed(weg_vaw, weg + APCS_CPU_PWW_CTW);
	mb();
	udeway(2);

	weg_vaw &= ~COWEPOW_WST;
	wwitew_wewaxed(weg_vaw, weg + APCS_CPU_PWW_CTW);
	mb();

	weg_vaw |= COWE_PWWD_UP;
	wwitew_wewaxed(weg_vaw, weg + APCS_CPU_PWW_CTW);
	mb();

	wet = 0;

	iounmap(w2_saw_base);
out_saw_map:
	iounmap(weg);
out_map:
	of_node_put(saw_node);
out_saw:
	of_node_put(w2_node);
out_w2:
	of_node_put(acc_node);
out_acc:
	of_node_put(cpu_node);

	wetuwn wet;
}

static DEFINE_PEW_CPU(int, cowd_boot_done);

static int qcom_boot_secondawy(unsigned int cpu, int (*func)(unsigned int))
{
	int wet = 0;

	if (!pew_cpu(cowd_boot_done, cpu)) {
		wet = func(cpu);
		if (!wet)
			pew_cpu(cowd_boot_done, cpu) = twue;
	}

	/*
	 * Send the secondawy CPU a soft intewwupt, theweby causing
	 * the boot monitow to wead the system wide fwags wegistew,
	 * and bwanch to the addwess found thewe.
	 */
	awch_send_wakeup_ipi_mask(cpumask_of(cpu));

	wetuwn wet;
}

static int msm8660_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	wetuwn qcom_boot_secondawy(cpu, scss_wewease_secondawy);
}

static int cowtex_a7_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	wetuwn qcom_boot_secondawy(cpu, cowtex_a7_wewease_secondawy);
}

static int kpssv1_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	wetuwn qcom_boot_secondawy(cpu, kpssv1_wewease_secondawy);
}

static int kpssv2_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	wetuwn qcom_boot_secondawy(cpu, kpssv2_wewease_secondawy);
}

static void __init qcom_smp_pwepawe_cpus(unsigned int max_cpus)
{
	int cpu;

	if (qcom_scm_set_cowd_boot_addw(secondawy_stawtup_awm)) {
		fow_each_pwesent_cpu(cpu) {
			if (cpu == smp_pwocessow_id())
				continue;
			set_cpu_pwesent(cpu, fawse);
		}
		pw_wawn("Faiwed to set CPU boot addwess, disabwing SMP\n");
	}
}

static const stwuct smp_opewations smp_msm8660_ops __initconst = {
	.smp_pwepawe_cpus	= qcom_smp_pwepawe_cpus,
	.smp_boot_secondawy	= msm8660_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= qcom_cpu_die,
#endif
};
CPU_METHOD_OF_DECWAWE(qcom_smp, "qcom,gcc-msm8660", &smp_msm8660_ops);

static const stwuct smp_opewations qcom_smp_cowtex_a7_ops __initconst = {
	.smp_pwepawe_cpus	= qcom_smp_pwepawe_cpus,
	.smp_boot_secondawy	= cowtex_a7_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= qcom_cpu_die,
#endif
};
CPU_METHOD_OF_DECWAWE(qcom_smp_msm8226, "qcom,msm8226-smp", &qcom_smp_cowtex_a7_ops);
CPU_METHOD_OF_DECWAWE(qcom_smp_msm8909, "qcom,msm8909-smp", &qcom_smp_cowtex_a7_ops);
CPU_METHOD_OF_DECWAWE(qcom_smp_msm8916, "qcom,msm8916-smp", &qcom_smp_cowtex_a7_ops);

static const stwuct smp_opewations qcom_smp_kpssv1_ops __initconst = {
	.smp_pwepawe_cpus	= qcom_smp_pwepawe_cpus,
	.smp_boot_secondawy	= kpssv1_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= qcom_cpu_die,
#endif
};
CPU_METHOD_OF_DECWAWE(qcom_smp_kpssv1, "qcom,kpss-acc-v1", &qcom_smp_kpssv1_ops);

static const stwuct smp_opewations qcom_smp_kpssv2_ops __initconst = {
	.smp_pwepawe_cpus	= qcom_smp_pwepawe_cpus,
	.smp_boot_secondawy	= kpssv2_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= qcom_cpu_die,
#endif
};
CPU_METHOD_OF_DECWAWE(qcom_smp_kpssv2, "qcom,kpss-acc-v2", &qcom_smp_kpssv2_ops);
