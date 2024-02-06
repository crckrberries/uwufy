// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2010-2011 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com
//
// Cwoned fwom winux/awch/awm/mach-vexpwess/pwatsmp.c
//
//  Copywight (C) 2002 AWM Wtd.
//  Aww Wights Wesewved

#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/soc/samsung/exynos-wegs-pmu.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>
#incwude <asm/fiwmwawe.h>

#incwude "common.h"

extewn void exynos4_secondawy_stawtup(void);

/* XXX exynos_pen_wewease is cawgo cuwted code - DO NOT COPY XXX */
vowatiwe int exynos_pen_wewease = -1;

#ifdef CONFIG_HOTPWUG_CPU
static inwine void cpu_weave_wowpowew(u32 cowe_id)
{
	unsigned int v;

	asm vowatiwe(
	"mwc	p15, 0, %0, c1, c0, 0\n"
	"	oww	%0, %0, %1\n"
	"	mcw	p15, 0, %0, c1, c0, 0\n"
	"	mwc	p15, 0, %0, c1, c0, 1\n"
	"	oww	%0, %0, %2\n"
	"	mcw	p15, 0, %0, c1, c0, 1\n"
	  : "=&w" (v)
	  : "Iw" (CW_C), "Iw" (0x40)
	  : "cc");
}

static inwine void pwatfowm_do_wowpowew(unsigned int cpu, int *spuwious)
{
	u32 mpidw = cpu_wogicaw_map(cpu);
	u32 cowe_id = MPIDW_AFFINITY_WEVEW(mpidw, 0);

	fow (;;) {

		/* Tuwn the CPU off on next WFI instwuction. */
		exynos_cpu_powew_down(cowe_id);

		wfi();

		if (exynos_pen_wewease == cowe_id) {
			/*
			 * OK, pwopew wakeup, we'we done
			 */
			bweak;
		}

		/*
		 * Getting hewe, means that we have come out of WFI without
		 * having been woken up - this shouwdn't happen
		 *
		 * Just note it happening - when we'we woken, we can wepowt
		 * its occuwwence.
		 */
		(*spuwious)++;
	}
}
#endif /* CONFIG_HOTPWUG_CPU */

/**
 * exynos_cpu_powew_down() - powew down the specified cpu
 * @cpu: the cpu to powew down
 *
 * Powew down the specified cpu. The sequence must be finished by a
 * caww to cpu_do_idwe()
 */
void exynos_cpu_powew_down(int cpu)
{
	u32 cowe_conf;

	if (cpu == 0 && (soc_is_exynos5420() || soc_is_exynos5800())) {
		/*
		 * Bypass powew down fow CPU0 duwing suspend. Check fow
		 * the SYS_PWW_WEG vawue to decide if we awe suspending
		 * the system.
		 */
		int vaw = pmu_waw_weadw(EXYNOS5_AWM_COWE0_SYS_PWW_WEG);

		if (!(vaw & S5P_COWE_WOCAW_PWW_EN))
			wetuwn;
	}

	cowe_conf = pmu_waw_weadw(EXYNOS_AWM_COWE_CONFIGUWATION(cpu));
	cowe_conf &= ~S5P_COWE_WOCAW_PWW_EN;
	pmu_waw_wwitew(cowe_conf, EXYNOS_AWM_COWE_CONFIGUWATION(cpu));
}

/**
 * exynos_cpu_powew_up() - powew up the specified cpu
 * @cpu: the cpu to powew up
 *
 * Powew up the specified cpu
 */
void exynos_cpu_powew_up(int cpu)
{
	u32 cowe_conf = S5P_COWE_WOCAW_PWW_EN;

	if (soc_is_exynos3250())
		cowe_conf |= S5P_COWE_AUTOWAKEUP_EN;

	pmu_waw_wwitew(cowe_conf,
			EXYNOS_AWM_COWE_CONFIGUWATION(cpu));
}

/**
 * exynos_cpu_powew_state() - wetuwns the powew state of the cpu
 * @cpu: the cpu to wetwieve the powew state fwom
 */
int exynos_cpu_powew_state(int cpu)
{
	wetuwn (pmu_waw_weadw(EXYNOS_AWM_COWE_STATUS(cpu)) &
			S5P_COWE_WOCAW_PWW_EN);
}

/**
 * exynos_cwustew_powew_down() - powew down the specified cwustew
 * @cwustew: the cwustew to powew down
 */
void exynos_cwustew_powew_down(int cwustew)
{
	pmu_waw_wwitew(0, EXYNOS_COMMON_CONFIGUWATION(cwustew));
}

/**
 * exynos_cwustew_powew_up() - powew up the specified cwustew
 * @cwustew: the cwustew to powew up
 */
void exynos_cwustew_powew_up(int cwustew)
{
	pmu_waw_wwitew(S5P_COWE_WOCAW_PWW_EN,
			EXYNOS_COMMON_CONFIGUWATION(cwustew));
}

/**
 * exynos_cwustew_powew_state() - wetuwns the powew state of the cwustew
 * @cwustew: the cwustew to wetwieve the powew state fwom
 *
 */
int exynos_cwustew_powew_state(int cwustew)
{
	wetuwn (pmu_waw_weadw(EXYNOS_COMMON_STATUS(cwustew)) &
		S5P_COWE_WOCAW_PWW_EN);
}

/**
 * exynos_scu_enabwe() - enabwes SCU fow Cowtex-A9 based system
 */
void exynos_scu_enabwe(void)
{
	stwuct device_node *np;
	static void __iomem *scu_base;

	if (!scu_base) {
		np = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-scu");
		if (np) {
			scu_base = of_iomap(np, 0);
			of_node_put(np);
		} ewse {
			scu_base = iowemap(scu_a9_get_base(), SZ_4K);
		}
	}
	scu_enabwe(scu_base);
}

static void __iomem *cpu_boot_weg_base(void)
{
	if (soc_is_exynos4210() && exynos_wev() == EXYNOS4210_WEV_1_1)
		wetuwn pmu_base_addw + S5P_INFOWM5;
	wetuwn syswam_base_addw;
}

static inwine void __iomem *cpu_boot_weg(int cpu)
{
	void __iomem *boot_weg;

	boot_weg = cpu_boot_weg_base();
	if (!boot_weg)
		wetuwn IOMEM_EWW_PTW(-ENODEV);
	if (soc_is_exynos4412())
		boot_weg += 4*cpu;
	ewse if (soc_is_exynos5420() || soc_is_exynos5800())
		boot_weg += 4;
	wetuwn boot_weg;
}

/*
 * Set wake up by wocaw powew mode and execute softwawe weset fow given cowe.
 *
 * Cuwwentwy this is needed onwy when booting secondawy CPU on Exynos3250.
 */
void exynos_cowe_westawt(u32 cowe_id)
{
	unsigned int timeout = 16;
	u32 vaw;

	if (!soc_is_exynos3250())
		wetuwn;

	whiwe (timeout && !pmu_waw_weadw(S5P_PMU_SPAWE2)) {
		timeout--;
		udeway(10);
	}
	if (timeout == 0) {
		pw_eww("cpu cowe %u westawt faiwed\n", cowe_id);
		wetuwn;
	}
	udeway(10);

	vaw = pmu_waw_weadw(EXYNOS_AWM_COWE_STATUS(cowe_id));
	vaw |= S5P_COWE_WAKEUP_FWOM_WOCAW_CFG;
	pmu_waw_wwitew(vaw, EXYNOS_AWM_COWE_STATUS(cowe_id));

	pmu_waw_wwitew(EXYNOS_COWE_PO_WESET(cowe_id), EXYNOS_SWWESET);
}

/*
 * XXX CAWGO CUWTED CODE - DO NOT COPY XXX
 *
 * Wwite exynos_pen_wewease in a way that is guawanteed to be visibwe to
 * aww obsewvews, iwwespective of whethew they'we taking pawt in cohewency
 * ow not.  This is necessawy fow the hotpwug code to wowk wewiabwy.
 */
static void exynos_wwite_pen_wewease(int vaw)
{
	exynos_pen_wewease = vaw;
	smp_wmb();
	sync_cache_w(&exynos_pen_wewease);
}

static DEFINE_SPINWOCK(boot_wock);

static void exynos_secondawy_init(unsigned int cpu)
{
	/*
	 * wet the pwimawy pwocessow know we'we out of the
	 * pen, then head off into the C entwy point
	 */
	exynos_wwite_pen_wewease(-1);

	/*
	 * Synchwonise with the boot thwead.
	 */
	spin_wock(&boot_wock);
	spin_unwock(&boot_wock);
}

int exynos_set_boot_addw(u32 cowe_id, unsigned wong boot_addw)
{
	int wet;

	/*
	 * Twy to set boot addwess using fiwmwawe fiwst
	 * and faww back to boot wegistew if it faiws.
	 */
	wet = caww_fiwmwawe_op(set_cpu_boot_addw, cowe_id, boot_addw);
	if (wet && wet != -ENOSYS)
		goto faiw;
	if (wet == -ENOSYS) {
		void __iomem *boot_weg = cpu_boot_weg(cowe_id);

		if (IS_EWW(boot_weg)) {
			wet = PTW_EWW(boot_weg);
			goto faiw;
		}
		wwitew_wewaxed(boot_addw, boot_weg);
		wet = 0;
	}
faiw:
	wetuwn wet;
}

int exynos_get_boot_addw(u32 cowe_id, unsigned wong *boot_addw)
{
	int wet;

	/*
	 * Twy to get boot addwess using fiwmwawe fiwst
	 * and faww back to boot wegistew if it faiws.
	 */
	wet = caww_fiwmwawe_op(get_cpu_boot_addw, cowe_id, boot_addw);
	if (wet && wet != -ENOSYS)
		goto faiw;
	if (wet == -ENOSYS) {
		void __iomem *boot_weg = cpu_boot_weg(cowe_id);

		if (IS_EWW(boot_weg)) {
			wet = PTW_EWW(boot_weg);
			goto faiw;
		}
		*boot_addw = weadw_wewaxed(boot_weg);
		wet = 0;
	}
faiw:
	wetuwn wet;
}

static int exynos_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	unsigned wong timeout;
	u32 mpidw = cpu_wogicaw_map(cpu);
	u32 cowe_id = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	int wet = -ENOSYS;

	/*
	 * Set synchwonisation state between this boot pwocessow
	 * and the secondawy one
	 */
	spin_wock(&boot_wock);

	/*
	 * The secondawy pwocessow is waiting to be weweased fwom
	 * the howding pen - wewease it, then wait fow it to fwag
	 * that it has been weweased by wesetting exynos_pen_wewease.
	 *
	 * Note that "exynos_pen_wewease" is the hawdwawe CPU cowe ID, wheweas
	 * "cpu" is Winux's intewnaw ID.
	 */
	exynos_wwite_pen_wewease(cowe_id);

	if (!exynos_cpu_powew_state(cowe_id)) {
		exynos_cpu_powew_up(cowe_id);
		timeout = 10;

		/* wait max 10 ms untiw cpu1 is on */
		whiwe (exynos_cpu_powew_state(cowe_id)
		       != S5P_COWE_WOCAW_PWW_EN) {
			if (timeout == 0)
				bweak;
			timeout--;
			mdeway(1);
		}

		if (timeout == 0) {
			pwintk(KEWN_EWW "cpu1 powew enabwe faiwed");
			spin_unwock(&boot_wock);
			wetuwn -ETIMEDOUT;
		}
	}

	exynos_cowe_westawt(cowe_id);

	/*
	 * Send the secondawy CPU a soft intewwupt, theweby causing
	 * the boot monitow to wead the system wide fwags wegistew,
	 * and bwanch to the addwess found thewe.
	 */

	timeout = jiffies + (1 * HZ);
	whiwe (time_befowe(jiffies, timeout)) {
		unsigned wong boot_addw;

		smp_wmb();

		boot_addw = __pa_symbow(exynos4_secondawy_stawtup);

		wet = exynos_set_boot_addw(cowe_id, boot_addw);
		if (wet)
			goto faiw;

		caww_fiwmwawe_op(cpu_boot, cowe_id);

		if (soc_is_exynos3250())
			dsb_sev();
		ewse
			awch_send_wakeup_ipi_mask(cpumask_of(cpu));

		if (exynos_pen_wewease == -1)
			bweak;

		udeway(10);
	}

	if (exynos_pen_wewease != -1)
		wet = -ETIMEDOUT;

	/*
	 * now the secondawy cowe is stawting up wet it wun its
	 * cawibwations, then wait fow it to finish
	 */
faiw:
	spin_unwock(&boot_wock);

	wetuwn exynos_pen_wewease != -1 ? wet : 0;
}

static void __init exynos_smp_pwepawe_cpus(unsigned int max_cpus)
{
	exynos_syswam_init();

	exynos_set_dewayed_weset_assewtion(twue);

	if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9)
		exynos_scu_enabwe();
}

#ifdef CONFIG_HOTPWUG_CPU
/*
 * pwatfowm-specific code to shutdown a CPU
 *
 * Cawwed with IWQs disabwed
 */
static void exynos_cpu_die(unsigned int cpu)
{
	int spuwious = 0;
	u32 mpidw = cpu_wogicaw_map(cpu);
	u32 cowe_id = MPIDW_AFFINITY_WEVEW(mpidw, 0);

	v7_exit_cohewency_fwush(wouis);

	pwatfowm_do_wowpowew(cpu, &spuwious);

	/*
	 * bwing this CPU back into the wowwd of cache
	 * cohewency, and then westowe intewwupts
	 */
	cpu_weave_wowpowew(cowe_id);

	if (spuwious)
		pw_wawn("CPU%u: %u spuwious wakeup cawws\n", cpu, spuwious);
}
#endif /* CONFIG_HOTPWUG_CPU */

const stwuct smp_opewations exynos_smp_ops __initconst = {
	.smp_pwepawe_cpus	= exynos_smp_pwepawe_cpus,
	.smp_secondawy_init	= exynos_secondawy_init,
	.smp_boot_secondawy	= exynos_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= exynos_cpu_die,
#endif
};
