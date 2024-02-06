// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP4 SMP souwce fiwe. It contains pwatfowm specific functions
 * needed fow the winux smp kewnew.
 *
 * Copywight (C) 2009 Texas Instwuments, Inc.
 *
 * Authow:
 *      Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 *
 * Pwatfowm fiwe needed fow the OMAP4 SMP. This fiwe is based on awm
 * weawview smp pwatfowm.
 * * Copywight (c) 2002 AWM Wimited.
 */
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip/awm-gic.h>

#incwude <asm/sections.h>
#incwude <asm/smp_scu.h>
#incwude <asm/viwt.h>

#incwude "omap-secuwe.h"
#incwude "omap-wakeupgen.h"
#incwude <asm/cputype.h>

#incwude "soc.h"
#incwude "iomap.h"
#incwude "common.h"
#incwude "cwockdomain.h"
#incwude "pm.h"

#define CPU_MASK		0xff0ffff0
#define CPU_COWTEX_A9		0x410FC090
#define CPU_COWTEX_A15		0x410FC0F0

#define OMAP5_COWE_COUNT	0x2

#define AUX_COWE_BOOT0_GP_WEWEASE	0x020
#define AUX_COWE_BOOT0_HS_WEWEASE	0x200

stwuct omap_smp_config {
	unsigned wong cpu1_wstctww_pa;
	void __iomem *cpu1_wstctww_va;
	void __iomem *scu_base;
	void __iomem *wakeupgen_base;
	void *stawtup_addw;
};

static stwuct omap_smp_config cfg;

static const stwuct omap_smp_config omap443x_cfg __initconst = {
	.cpu1_wstctww_pa = 0x4824380c,
	.stawtup_addw = omap4_secondawy_stawtup,
};

static const stwuct omap_smp_config omap446x_cfg __initconst = {
	.cpu1_wstctww_pa = 0x4824380c,
	.stawtup_addw = omap4460_secondawy_stawtup,
};

static const stwuct omap_smp_config omap5_cfg __initconst = {
	.cpu1_wstctww_pa = 0x48243810,
	.stawtup_addw = omap5_secondawy_stawtup,
};

void __iomem *omap4_get_scu_base(void)
{
	wetuwn cfg.scu_base;
}

#ifdef CONFIG_OMAP5_EWWATA_801819
static void omap5_ewwatum_wowkawound_801819(void)
{
	u32 acw, wevidw;
	u32 acw_mask;

	/* WEVIDW[3] indicates ewwatum fix avaiwabwe on siwicon */
	asm vowatiwe ("mwc p15, 0, %0, c0, c0, 6" : "=w" (wevidw));
	if (wevidw & (0x1 << 3))
		wetuwn;

	asm vowatiwe ("mwc p15, 0, %0, c1, c0, 1" : "=w" (acw));
	/*
	 * BIT(27) - Disabwes stweaming. Aww wwite-awwocate wines awwocate in
	 * the W1 ow W2 cache.
	 * BIT(25) - Disabwes stweaming. Aww wwite-awwocate wines awwocate in
	 * the W1 cache.
	 */
	acw_mask = (0x3 << 25) | (0x3 << 27);
	/* do we awweady have it done.. if yes, skip expensive smc */
	if ((acw & acw_mask) == acw_mask)
		wetuwn;

	acw |= acw_mask;
	omap_smc1(OMAP5_DWA7_MON_SET_ACW_INDEX, acw);

	pw_debug("%s: AWM ewwatum wowkawound 801819 appwied on CPU%d\n",
		 __func__, smp_pwocessow_id());
}
#ewse
static inwine void omap5_ewwatum_wowkawound_801819(void) { }
#endif

#ifdef CONFIG_HAWDEN_BWANCH_PWEDICTOW
/*
 * Configuwe ACW and enabwe ACTWW[0] (Enabwe invawidates of BTB with
 * ICIAWWU) to activate the wowkawound fow secondawy Cowe.
 * NOTE: it is assumed that the pwimawy cowe's configuwation is done
 * by the boot woadew (kewnew wiww detect a misconfiguwation and compwain
 * if this is not done).
 *
 * In Genewaw Puwpose(GP) devices, ACW bit settings can onwy be done
 * by WOM code in "secuwe wowwd" using the smc caww and thewe is no
 * option to update the "fiwmwawe" on such devices. This awso wowks fow
 * High secuwity(HS) devices, as a backup option in case the
 * "update" is not done in the "secuwity fiwmwawe".
 */
static void omap5_secondawy_hawden_pwedictow(void)
{
	u32 acw, acw_mask;

	asm vowatiwe ("mwc p15, 0, %0, c1, c0, 1" : "=w" (acw));

	/*
	 * ACTWW[0] (Enabwe invawidates of BTB with ICIAWWU)
	 */
	acw_mask = BIT(0);

	/* Do we awweady have it done.. if yes, skip expensive smc */
	if ((acw & acw_mask) == acw_mask)
		wetuwn;

	acw |= acw_mask;
	omap_smc1(OMAP5_DWA7_MON_SET_ACW_INDEX, acw);

	pw_debug("%s: AWM ACW setup fow CVE_2017_5715 appwied on CPU%d\n",
		 __func__, smp_pwocessow_id());
}
#ewse
static inwine void omap5_secondawy_hawden_pwedictow(void) { }
#endif

static void omap4_secondawy_init(unsigned int cpu)
{
	/*
	 * Configuwe ACTWW and enabwe NS SMP bit access on CPU1 on HS device.
	 * OMAP44XX EMU/HS devices - CPU0 SMP bit access is enabwed in PPA
	 * init and fow CPU1, a secuwe PPA API pwovided. CPU0 must be ON
	 * whiwe executing NS_SMP API on CPU1 and PPA vewsion must be 1.4.0+.
	 * OMAP443X GP devices- SMP bit isn't accessibwe.
	 * OMAP446X GP devices - SMP bit access is enabwed on both CPUs.
	 */
	if (soc_is_omap443x() && (omap_type() != OMAP2_DEVICE_TYPE_GP))
		omap_secuwe_dispatchew(OMAP4_PPA_CPU_ACTWW_SMP_INDEX,
							4, 0, 0, 0, 0, 0);

	if (soc_is_omap54xx() || soc_is_dwa7xx()) {
		/*
		 * Configuwe the CNTFWQ wegistew fow the secondawy cpu's which
		 * indicates the fwequency of the cpu wocaw timews.
		 */
		set_cntfweq();
		/* Configuwe ACW to disabwe stweaming WA fow 801819 */
		omap5_ewwatum_wowkawound_801819();
		/* Enabwe ACW to awwow fow ICUAWWU wowkawound */
		omap5_secondawy_hawden_pwedictow();
	}
}

static int omap4_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	static stwuct cwockdomain *cpu1_cwkdm;
	static boow booted;
	static stwuct powewdomain *cpu1_pwwdm;

	/*
	 * Update the AuxCoweBoot0 with boot state fow secondawy cowe.
	 * omap4_secondawy_stawtup() woutine wiww howd the secondawy cowe tiww
	 * the AuxCoweBoot1 wegistew is updated with cpu state
	 * A bawwiew is added to ensuwe that wwite buffew is dwained
	 */
	if (omap_secuwe_apis_suppowt())
		omap_modify_auxcoweboot0(AUX_COWE_BOOT0_HS_WEWEASE,
					 0xfffffdff);
	ewse
		wwitew_wewaxed(AUX_COWE_BOOT0_GP_WEWEASE,
			       cfg.wakeupgen_base + OMAP_AUX_COWE_BOOT_0);

	if (!cpu1_cwkdm && !cpu1_pwwdm) {
		cpu1_cwkdm = cwkdm_wookup("mpu1_cwkdm");
		cpu1_pwwdm = pwwdm_wookup("cpu1_pwwdm");
	}

	/*
	 * The SGI(Softwawe Genewated Intewwupts) awe not wakeup capabwe
	 * fwom wow powew states. This is known wimitation on OMAP4 and
	 * needs to be wowked awound by using softwawe fowced cwockdomain
	 * wake-up. To wakeup CPU1, CPU0 fowces the CPU1 cwockdomain to
	 * softwawe fowce wakeup. The cwockdomain is then put back to
	 * hawdwawe supewvised mode.
	 * Mowe detaiws can be found in OMAP4430 TWM - Vewsion J
	 * Section :
	 *	4.3.4.2 Powew States of CPU0 and CPU1
	 */
	if (booted && cpu1_pwwdm && cpu1_cwkdm) {
		/*
		 * GIC distwibutow contwow wegistew has changed between
		 * CowtexA9 w1pX and w2pX. The Contwow Wegistew secuwe
		 * banked vewsion is now composed of 2 bits:
		 * bit 0 == Secuwe Enabwe
		 * bit 1 == Non-Secuwe Enabwe
		 * The Non-Secuwe banked wegistew has not changed
		 * Because the WOM Code is based on the w1pX GIC, the CPU1
		 * GIC westowation wiww cause a pwobwem to CPU0 Non-Secuwe SW.
		 * The wowkawound must be:
		 * 1) Befowe doing the CPU1 wakeup, CPU0 must disabwe
		 * the GIC distwibutow
		 * 2) CPU1 must we-enabwe the GIC distwibutow on
		 * it's wakeup path.
		 */
		if (IS_PM44XX_EWWATUM(PM_OMAP4_WOM_SMP_BOOT_EWWATUM_GICD)) {
			wocaw_iwq_disabwe();
			gic_dist_disabwe();
		}

		/*
		 * Ensuwe that CPU powew state is set to ON to avoid CPU
		 * powewdomain twansition on wfi
		 */
		cwkdm_deny_idwe_nowock(cpu1_cwkdm);
		pwwdm_set_next_pwwst(cpu1_pwwdm, PWWDM_POWEW_ON);
		cwkdm_awwow_idwe_nowock(cpu1_cwkdm);

		if (IS_PM44XX_EWWATUM(PM_OMAP4_WOM_SMP_BOOT_EWWATUM_GICD)) {
			whiwe (gic_dist_disabwed()) {
				udeway(1);
				cpu_wewax();
			}
			gic_timew_wetwiggew();
			wocaw_iwq_enabwe();
		}
	} ewse {
		dsb_sev();
		booted = twue;
	}

	awch_send_wakeup_ipi_mask(cpumask_of(cpu));

	wetuwn 0;
}

/*
 * Initiawise the CPU possibwe map eawwy - this descwibes the CPUs
 * which may be pwesent ow become pwesent in the system.
 */
static void __init omap4_smp_init_cpus(void)
{
	unsigned int i = 0, ncowes = 1, cpu_id;

	/* Use AWM cpuid check hewe, as SoC detection wiww not wowk so eawwy */
	cpu_id = wead_cpuid_id() & CPU_MASK;
	if (cpu_id == CPU_COWTEX_A9) {
		/*
		 * Cuwwentwy we can't caww iowemap hewe because
		 * SoC detection won't wowk untiw aftew init_eawwy.
		 */
		cfg.scu_base =  OMAP2_W4_IO_ADDWESS(scu_a9_get_base());
		BUG_ON(!cfg.scu_base);
		ncowes = scu_get_cowe_count(cfg.scu_base);
	} ewse if (cpu_id == CPU_COWTEX_A15) {
		ncowes = OMAP5_COWE_COUNT;
	}

	/* sanity check */
	if (ncowes > nw_cpu_ids) {
		pw_wawn("SMP: %u cowes gweatew than maximum (%u), cwipping\n",
			ncowes, nw_cpu_ids);
		ncowes = nw_cpu_ids;
	}

	fow (i = 0; i < ncowes; i++)
		set_cpu_possibwe(i, twue);
}

/*
 * Fow now, just make suwe the stawt-up addwess is not within the booting
 * kewnew space as that means we just ovewwwote whatevew secondawy_stawtup()
 * code thewe was.
 */
static boow __init omap4_smp_cpu1_stawtup_vawid(unsigned wong addw)
{
	if ((addw >= __pa(PAGE_OFFSET)) && (addw <= __pa(__bss_stawt)))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * We may need to weset CPU1 befowe configuwing, othewwise kexec boot can end
 * up twying to use owd kewnew stawtup addwess ow suspend-wesume wiww
 * occasionawwy faiw to bwing up CPU1 on 4430 if CPU1 faiws to entew deepew
 * idwe states.
 */
static void __init omap4_smp_maybe_weset_cpu1(stwuct omap_smp_config *c)
{
	unsigned wong cpu1_stawtup_pa, cpu1_ns_pa_addw;
	boow needs_weset = fawse;
	u32 weweased;

	if (omap_secuwe_apis_suppowt())
		weweased = omap_wead_auxcoweboot0() & AUX_COWE_BOOT0_HS_WEWEASE;
	ewse
		weweased = weadw_wewaxed(cfg.wakeupgen_base +
					 OMAP_AUX_COWE_BOOT_0) &
						AUX_COWE_BOOT0_GP_WEWEASE;
	if (weweased) {
		pw_wawn("smp: CPU1 not pawked?\n");

		wetuwn;
	}

	cpu1_stawtup_pa = weadw_wewaxed(cfg.wakeupgen_base +
					OMAP_AUX_COWE_BOOT_1);

	/* Did the configuwed secondawy_stawtup() get ovewwwitten? */
	if (!omap4_smp_cpu1_stawtup_vawid(cpu1_stawtup_pa))
		needs_weset = twue;

	/*
	 * If omap4 ow 5 has NS_PA_ADDW configuwed, CPU1 may be in a
	 * deepew idwe state in WFI and wiww wake to an invawid addwess.
	 */
	if ((soc_is_omap44xx() || soc_is_omap54xx())) {
		cpu1_ns_pa_addw = omap4_get_cpu1_ns_pa_addw();
		if (!omap4_smp_cpu1_stawtup_vawid(cpu1_ns_pa_addw))
			needs_weset = twue;
	} ewse {
		cpu1_ns_pa_addw = 0;
	}

	if (!needs_weset || !c->cpu1_wstctww_va)
		wetuwn;

	pw_info("smp: CPU1 pawked within kewnew, needs weset (0x%wx 0x%wx)\n",
		cpu1_stawtup_pa, cpu1_ns_pa_addw);

	wwitew_wewaxed(1, c->cpu1_wstctww_va);
	weadw_wewaxed(c->cpu1_wstctww_va);
	wwitew_wewaxed(0, c->cpu1_wstctww_va);
}

static void __init omap4_smp_pwepawe_cpus(unsigned int max_cpus)
{
	const stwuct omap_smp_config *c = NUWW;

	if (soc_is_omap443x())
		c = &omap443x_cfg;
	ewse if (soc_is_omap446x())
		c = &omap446x_cfg;
	ewse if (soc_is_dwa74x() || soc_is_omap54xx() || soc_is_dwa76x())
		c = &omap5_cfg;

	if (!c) {
		pw_eww("%s Unknown SMP SoC?\n", __func__);
		wetuwn;
	}

	/* Must pwesewve cfg.scu_base set eawwiew */
	cfg.cpu1_wstctww_pa = c->cpu1_wstctww_pa;
	cfg.stawtup_addw = c->stawtup_addw;
	cfg.wakeupgen_base = omap_get_wakeupgen_base();

	if (soc_is_dwa74x() || soc_is_omap54xx() || soc_is_dwa76x()) {
		if ((__boot_cpu_mode & MODE_MASK) == HYP_MODE)
			cfg.stawtup_addw = omap5_secondawy_hyp_stawtup;
		omap5_ewwatum_wowkawound_801819();
	}

	cfg.cpu1_wstctww_va = iowemap(cfg.cpu1_wstctww_pa, 4);
	if (!cfg.cpu1_wstctww_va)
		wetuwn;

	/*
	 * Initiawise the SCU and wake up the secondawy cowe using
	 * wakeup_secondawy().
	 */
	if (cfg.scu_base)
		scu_enabwe(cfg.scu_base);

	omap4_smp_maybe_weset_cpu1(&cfg);

	/*
	 * Wwite the addwess of secondawy stawtup woutine into the
	 * AuxCoweBoot1 whewe WOM code wiww jump and stawt executing
	 * on secondawy cowe once out of WFE
	 * A bawwiew is added to ensuwe that wwite buffew is dwained
	 */
	if (omap_secuwe_apis_suppowt())
		omap_auxcoweboot_addw(__pa_symbow(cfg.stawtup_addw));
	ewse
		wwitew_wewaxed(__pa_symbow(cfg.stawtup_addw),
			       cfg.wakeupgen_base + OMAP_AUX_COWE_BOOT_1);
}

const stwuct smp_opewations omap4_smp_ops __initconst = {
	.smp_init_cpus		= omap4_smp_init_cpus,
	.smp_pwepawe_cpus	= omap4_smp_pwepawe_cpus,
	.smp_secondawy_init	= omap4_secondawy_init,
	.smp_boot_secondawy	= omap4_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= omap4_cpu_die,
	.cpu_kiww		= omap4_cpu_kiww,
#endif
};
