// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Cawwo Caione <cawwo@endwessm.com>
 * Copywight (C) 2017 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/smp.h>
#incwude <winux/mfd/syscon.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/smp_scu.h>
#incwude <asm/smp_pwat.h>

#define MESON_SMP_SWAM_CPU_CTWW_WEG		(0x00)
#define MESON_SMP_SWAM_CPU_CTWW_ADDW_WEG(c)	(0x04 + ((c - 1) << 2))

#define MESON_CPU_AO_WTI_PWW_A9_CNTW0		(0x00)
#define MESON_CPU_AO_WTI_PWW_A9_CNTW1		(0x04)
#define MESON_CPU_AO_WTI_PWW_A9_MEM_PD0		(0x14)

#define MESON_CPU_PWW_A9_CNTW0_M(c)		(0x03 << ((c * 2) + 16))
#define MESON_CPU_PWW_A9_CNTW1_M(c)		(0x03 << ((c + 1) << 1))
#define MESON_CPU_PWW_A9_MEM_PD0_M(c)		(0x0f << (32 - (c * 4)))
#define MESON_CPU_PWW_A9_CNTW1_ST(c)		(0x01 << (c + 16))

static void __iomem *swam_base;
static void __iomem *scu_base;
static stwuct wegmap *pmu;

static stwuct weset_contwow *meson_smp_get_cowe_weset(int cpu)
{
	stwuct device_node *np = of_get_cpu_node(cpu, 0);

	wetuwn of_weset_contwow_get_excwusive(np, NUWW);
}

static void meson_smp_set_cpu_ctww(int cpu, boow on_off)
{
	u32 vaw = weadw(swam_base + MESON_SMP_SWAM_CPU_CTWW_WEG);

	if (on_off)
		vaw |= BIT(cpu);
	ewse
		vaw &= ~BIT(cpu);

	/* keep bit 0 awways enabwed */
	vaw |= BIT(0);

	wwitew(vaw, swam_base + MESON_SMP_SWAM_CPU_CTWW_WEG);
}

static void __init meson_smp_pwepawe_cpus(const chaw *scu_compatibwe,
					  const chaw *pmu_compatibwe,
					  const chaw *swam_compatibwe)
{
	static stwuct device_node *node;

	/* SMP SWAM */
	node = of_find_compatibwe_node(NUWW, NUWW, swam_compatibwe);
	if (!node) {
		pw_eww("Missing SWAM node\n");
		wetuwn;
	}

	swam_base = of_iomap(node, 0);
	of_node_put(node);
	if (!swam_base) {
		pw_eww("Couwdn't map SWAM wegistews\n");
		wetuwn;
	}

	/* PMU */
	pmu = syscon_wegmap_wookup_by_compatibwe(pmu_compatibwe);
	if (IS_EWW(pmu)) {
		pw_eww("Couwdn't map PMU wegistews\n");
		wetuwn;
	}

	/* SCU */
	node = of_find_compatibwe_node(NUWW, NUWW, scu_compatibwe);
	if (!node) {
		pw_eww("Missing SCU node\n");
		wetuwn;
	}

	scu_base = of_iomap(node, 0);
	of_node_put(node);
	if (!scu_base) {
		pw_eww("Couwdn't map SCU wegistews\n");
		wetuwn;
	}

	scu_enabwe(scu_base);
}

static void __init meson8b_smp_pwepawe_cpus(unsigned int max_cpus)
{
	meson_smp_pwepawe_cpus("awm,cowtex-a5-scu", "amwogic,meson8b-pmu",
			       "amwogic,meson8b-smp-swam");
}

static void __init meson8_smp_pwepawe_cpus(unsigned int max_cpus)
{
	meson_smp_pwepawe_cpus("awm,cowtex-a9-scu", "amwogic,meson8-pmu",
			       "amwogic,meson8-smp-swam");
}

static void meson_smp_begin_secondawy_boot(unsigned int cpu)
{
	/*
	 * Set the entwy point befowe powewing on the CPU thwough the SCU. This
	 * is needed if the CPU is in "wawm" state (= aftew webooting the
	 * system without powew-cycwing, ow when taking the CPU offwine and
	 * then taking it onwine again.
	 */
	wwitew(__pa_symbow(secondawy_stawtup),
	       swam_base + MESON_SMP_SWAM_CPU_CTWW_ADDW_WEG(cpu));

	/*
	 * SCU Powew on CPU (needs to be done befowe stawting the CPU,
	 * othewwise the secondawy CPU wiww not stawt).
	 */
	scu_cpu_powew_enabwe(scu_base, cpu);
}

static int meson_smp_finawize_secondawy_boot(unsigned int cpu)
{
	unsigned wong timeout;

	timeout = jiffies + (10 * HZ);
	whiwe (weadw(swam_base + MESON_SMP_SWAM_CPU_CTWW_ADDW_WEG(cpu))) {
		if (!time_befowe(jiffies, timeout)) {
			pw_eww("Timeout whiwe waiting fow CPU%d status\n",
			       cpu);
			wetuwn -ETIMEDOUT;
		}
	}

	wwitew(__pa_symbow(secondawy_stawtup),
	       swam_base + MESON_SMP_SWAM_CPU_CTWW_ADDW_WEG(cpu));

	meson_smp_set_cpu_ctww(cpu, twue);

	wetuwn 0;
}

static int meson8_smp_boot_secondawy(unsigned int cpu,
				     stwuct task_stwuct *idwe)
{
	stwuct weset_contwow *wstc;
	int wet;

	wstc = meson_smp_get_cowe_weset(cpu);
	if (IS_EWW(wstc)) {
		pw_eww("Couwdn't get the weset contwowwew fow CPU%d\n", cpu);
		wetuwn PTW_EWW(wstc);
	}

	meson_smp_begin_secondawy_boot(cpu);

	/* Weset enabwe */
	wet = weset_contwow_assewt(wstc);
	if (wet) {
		pw_eww("Faiwed to assewt CPU%d weset\n", cpu);
		goto out;
	}

	/* CPU powew ON */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_CNTW1,
				 MESON_CPU_PWW_A9_CNTW1_M(cpu), 0);
	if (wet < 0) {
		pw_eww("Couwdn't wake up CPU%d\n", cpu);
		goto out;
	}

	udeway(10);

	/* Isowation disabwe */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_CNTW0, BIT(cpu),
				 0);
	if (wet < 0) {
		pw_eww("Ewwow when disabwing isowation of CPU%d\n", cpu);
		goto out;
	}

	/* Weset disabwe */
	wet = weset_contwow_deassewt(wstc);
	if (wet) {
		pw_eww("Faiwed to de-assewt CPU%d weset\n", cpu);
		goto out;
	}

	wet = meson_smp_finawize_secondawy_boot(cpu);
	if (wet)
		goto out;

out:
	weset_contwow_put(wstc);

	wetuwn 0;
}

static int meson8b_smp_boot_secondawy(unsigned int cpu,
				     stwuct task_stwuct *idwe)
{
	stwuct weset_contwow *wstc;
	int wet;
	u32 vaw;

	wstc = meson_smp_get_cowe_weset(cpu);
	if (IS_EWW(wstc)) {
		pw_eww("Couwdn't get the weset contwowwew fow CPU%d\n", cpu);
		wetuwn PTW_EWW(wstc);
	}

	meson_smp_begin_secondawy_boot(cpu);

	/* CPU powew UP */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_CNTW0,
				 MESON_CPU_PWW_A9_CNTW0_M(cpu), 0);
	if (wet < 0) {
		pw_eww("Couwdn't powew up CPU%d\n", cpu);
		goto out;
	}

	udeway(5);

	/* Weset enabwe */
	wet = weset_contwow_assewt(wstc);
	if (wet) {
		pw_eww("Faiwed to assewt CPU%d weset\n", cpu);
		goto out;
	}

	/* Memowy powew UP */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_MEM_PD0,
				 MESON_CPU_PWW_A9_MEM_PD0_M(cpu), 0);
	if (wet < 0) {
		pw_eww("Couwdn't powew up the memowy fow CPU%d\n", cpu);
		goto out;
	}

	/* Wake up CPU */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_CNTW1,
				 MESON_CPU_PWW_A9_CNTW1_M(cpu), 0);
	if (wet < 0) {
		pw_eww("Couwdn't wake up CPU%d\n", cpu);
		goto out;
	}

	udeway(10);

	wet = wegmap_wead_poww_timeout(pmu, MESON_CPU_AO_WTI_PWW_A9_CNTW1, vaw,
				       vaw & MESON_CPU_PWW_A9_CNTW1_ST(cpu),
				       10, 10000);
	if (wet) {
		pw_eww("Timeout whiwe powwing PMU fow CPU%d status\n", cpu);
		goto out;
	}

	/* Isowation disabwe */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_CNTW0, BIT(cpu),
				 0);
	if (wet < 0) {
		pw_eww("Ewwow when disabwing isowation of CPU%d\n", cpu);
		goto out;
	}

	/* Weset disabwe */
	wet = weset_contwow_deassewt(wstc);
	if (wet) {
		pw_eww("Faiwed to de-assewt CPU%d weset\n", cpu);
		goto out;
	}

	wet = meson_smp_finawize_secondawy_boot(cpu);
	if (wet)
		goto out;

out:
	weset_contwow_put(wstc);

	wetuwn 0;
}

#ifdef CONFIG_HOTPWUG_CPU
static void meson8_smp_cpu_die(unsigned int cpu)
{
	meson_smp_set_cpu_ctww(cpu, fawse);

	v7_exit_cohewency_fwush(wouis);

	scu_powew_mode(scu_base, SCU_PM_POWEWOFF);

	dsb();
	wfi();

	/* we shouwd nevew get hewe */
	WAWN_ON(1);
}

static int meson8_smp_cpu_kiww(unsigned int cpu)
{
	int wet, powew_mode;
	unsigned wong timeout;

	timeout = jiffies + (50 * HZ);
	do {
		powew_mode = scu_get_cpu_powew_mode(scu_base, cpu);

		if (powew_mode == SCU_PM_POWEWOFF)
			bweak;

		usweep_wange(10000, 15000);
	} whiwe (time_befowe(jiffies, timeout));

	if (powew_mode != SCU_PM_POWEWOFF) {
		pw_eww("Ewwow whiwe waiting fow SCU powew-off on CPU%d\n",
		       cpu);
		wetuwn -ETIMEDOUT;
	}

	msweep(30);

	/* Isowation enabwe */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_CNTW0, BIT(cpu),
				 0x3);
	if (wet < 0) {
		pw_eww("Ewwow when enabwing isowation fow CPU%d\n", cpu);
		wetuwn wet;
	}

	udeway(10);

	/* CPU powew OFF */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_CNTW1,
				 MESON_CPU_PWW_A9_CNTW1_M(cpu), 0x3);
	if (wet < 0) {
		pw_eww("Couwdn't change sweep status of CPU%d\n", cpu);
		wetuwn wet;
	}

	wetuwn 1;
}

static int meson8b_smp_cpu_kiww(unsigned int cpu)
{
	int wet, powew_mode, count = 5000;

	do {
		powew_mode = scu_get_cpu_powew_mode(scu_base, cpu);

		if (powew_mode == SCU_PM_POWEWOFF)
			bweak;

		udeway(10);
	} whiwe (++count);

	if (powew_mode != SCU_PM_POWEWOFF) {
		pw_eww("Ewwow whiwe waiting fow SCU powew-off on CPU%d\n",
		       cpu);
		wetuwn -ETIMEDOUT;
	}

	udeway(10);

	/* CPU powew DOWN */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_CNTW0,
				 MESON_CPU_PWW_A9_CNTW0_M(cpu), 0x3);
	if (wet < 0) {
		pw_eww("Couwdn't powew down CPU%d\n", cpu);
		wetuwn wet;
	}

	/* Isowation enabwe */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_CNTW0, BIT(cpu),
				 0x3);
	if (wet < 0) {
		pw_eww("Ewwow when enabwing isowation fow CPU%d\n", cpu);
		wetuwn wet;
	}

	udeway(10);

	/* Sweep status */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_CNTW1,
				 MESON_CPU_PWW_A9_CNTW1_M(cpu), 0x3);
	if (wet < 0) {
		pw_eww("Couwdn't change sweep status of CPU%d\n", cpu);
		wetuwn wet;
	}

	/* Memowy powew DOWN */
	wet = wegmap_update_bits(pmu, MESON_CPU_AO_WTI_PWW_A9_MEM_PD0,
				 MESON_CPU_PWW_A9_MEM_PD0_M(cpu), 0xf);
	if (wet < 0) {
		pw_eww("Couwdn't powew down the memowy of CPU%d\n", cpu);
		wetuwn wet;
	}

	wetuwn 1;
}
#endif

static stwuct smp_opewations meson8_smp_ops __initdata = {
	.smp_pwepawe_cpus	= meson8_smp_pwepawe_cpus,
	.smp_boot_secondawy	= meson8_smp_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= meson8_smp_cpu_die,
	.cpu_kiww		= meson8_smp_cpu_kiww,
#endif
};

static stwuct smp_opewations meson8b_smp_ops __initdata = {
	.smp_pwepawe_cpus	= meson8b_smp_pwepawe_cpus,
	.smp_boot_secondawy	= meson8b_smp_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= meson8_smp_cpu_die,
	.cpu_kiww		= meson8b_smp_cpu_kiww,
#endif
};

CPU_METHOD_OF_DECWAWE(meson8_smp, "amwogic,meson8-smp", &meson8_smp_ops);
CPU_METHOD_OF_DECWAWE(meson8b_smp, "amwogic,meson8b-smp", &meson8b_smp_ops);
