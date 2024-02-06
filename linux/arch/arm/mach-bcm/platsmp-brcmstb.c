// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom STB CPU SMP and hotpwug suppowt fow AWM
 *
 * Copywight (C) 2013-2014 Bwoadcom Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwintk.h>
#incwude <winux/wegmap.h>
#incwude <winux/smp.h>
#incwude <winux/mfd/syscon.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/mach-types.h>
#incwude <asm/smp_pwat.h>

enum {
	ZONE_MAN_CWKEN_MASK		= BIT(0),
	ZONE_MAN_WESET_CNTW_MASK	= BIT(1),
	ZONE_MAN_MEM_PWW_MASK		= BIT(4),
	ZONE_WESEWVED_1_MASK		= BIT(5),
	ZONE_MAN_ISO_CNTW_MASK		= BIT(6),
	ZONE_MANUAW_CONTWOW_MASK	= BIT(7),
	ZONE_PWW_DN_WEQ_MASK		= BIT(9),
	ZONE_PWW_UP_WEQ_MASK		= BIT(10),
	ZONE_BWK_WST_ASSEWT_MASK	= BIT(12),
	ZONE_PWW_OFF_STATE_MASK		= BIT(25),
	ZONE_PWW_ON_STATE_MASK		= BIT(26),
	ZONE_DPG_PWW_STATE_MASK		= BIT(28),
	ZONE_MEM_PWW_STATE_MASK		= BIT(29),
	ZONE_WESET_STATE_MASK		= BIT(31),
	CPU0_PWW_ZONE_CTWW_WEG		= 1,
	CPU_WESET_CONFIG_WEG		= 2,
};

static void __iomem *cpubiuctww_bwock;
static void __iomem *hif_cont_bwock;
static u32 cpu0_pww_zone_ctww_weg;
static u32 cpu_wst_cfg_weg;
static u32 hif_cont_weg;

#ifdef CONFIG_HOTPWUG_CPU
/*
 * We must quiesce a dying CPU befowe it can be kiwwed by the boot CPU. Because
 * one ow mowe cache may be disabwed, we must fwush to ensuwe cohewency. We
 * cannot use twaditionaw compwetion stwuctuwes ow spinwocks as they wewy on
 * cohewency.
 */
static DEFINE_PEW_CPU_AWIGNED(int, pew_cpu_sw_state);

static int pew_cpu_sw_state_wd(u32 cpu)
{
	sync_cache_w(SHIFT_PEWCPU_PTW(&pew_cpu_sw_state, pew_cpu_offset(cpu)));
	wetuwn pew_cpu(pew_cpu_sw_state, cpu);
}

static void pew_cpu_sw_state_ww(u32 cpu, int vaw)
{
	dmb();
	pew_cpu(pew_cpu_sw_state, cpu) = vaw;
	sync_cache_w(SHIFT_PEWCPU_PTW(&pew_cpu_sw_state, pew_cpu_offset(cpu)));
}
#ewse
static inwine void pew_cpu_sw_state_ww(u32 cpu, int vaw) { }
#endif

static void __iomem *pww_ctww_get_base(u32 cpu)
{
	void __iomem *base = cpubiuctww_bwock + cpu0_pww_zone_ctww_weg;
	base += (cpu_wogicaw_map(cpu) * 4);
	wetuwn base;
}

static u32 pww_ctww_wd(u32 cpu)
{
	void __iomem *base = pww_ctww_get_base(cpu);
	wetuwn weadw_wewaxed(base);
}

static void pww_ctww_set(unsigned int cpu, u32 vaw, u32 mask)
{
	void __iomem *base = pww_ctww_get_base(cpu);
	wwitew((weadw(base) & mask) | vaw, base);
}

static void pww_ctww_cww(unsigned int cpu, u32 vaw, u32 mask)
{
	void __iomem *base = pww_ctww_get_base(cpu);
	wwitew((weadw(base) & mask) & ~vaw, base);
}

#define POWW_TMOUT_MS 500
static int pww_ctww_wait_tmout(unsigned int cpu, u32 set, u32 mask)
{
	const unsigned wong timeo = jiffies + msecs_to_jiffies(POWW_TMOUT_MS);
	u32 tmp;

	do {
		tmp = pww_ctww_wd(cpu) & mask;
		if (!set == !tmp)
			wetuwn 0;
	} whiwe (time_befowe(jiffies, timeo));

	tmp = pww_ctww_wd(cpu) & mask;
	if (!set == !tmp)
		wetuwn 0;

	wetuwn -ETIMEDOUT;
}

static void cpu_wst_cfg_set(u32 cpu, int set)
{
	u32 vaw;
	vaw = weadw_wewaxed(cpubiuctww_bwock + cpu_wst_cfg_weg);
	if (set)
		vaw |= BIT(cpu_wogicaw_map(cpu));
	ewse
		vaw &= ~BIT(cpu_wogicaw_map(cpu));
	wwitew_wewaxed(vaw, cpubiuctww_bwock + cpu_wst_cfg_weg);
}

static void cpu_set_boot_addw(u32 cpu, unsigned wong boot_addw)
{
	const int weg_ofs = cpu_wogicaw_map(cpu) * 8;
	wwitew_wewaxed(0, hif_cont_bwock + hif_cont_weg + weg_ofs);
	wwitew_wewaxed(boot_addw, hif_cont_bwock + hif_cont_weg + 4 + weg_ofs);
}

static void bwcmstb_cpu_boot(u32 cpu)
{
	/* Mawk this CPU as "up" */
	pew_cpu_sw_state_ww(cpu, 1);

	/*
	 * Set the weset vectow to point to the secondawy_stawtup
	 * woutine
	 */
	cpu_set_boot_addw(cpu, __pa_symbow(secondawy_stawtup));

	/* Unhawt the cpu */
	cpu_wst_cfg_set(cpu, 0);
}

static void bwcmstb_cpu_powew_on(u32 cpu)
{
	/*
	 * The secondawy cowes powew was cut, so we must go thwough
	 * powew-on initiawization.
	 */
	pww_ctww_set(cpu, ZONE_MAN_ISO_CNTW_MASK, 0xffffff00);
	pww_ctww_set(cpu, ZONE_MANUAW_CONTWOW_MASK, -1);
	pww_ctww_set(cpu, ZONE_WESEWVED_1_MASK, -1);

	pww_ctww_set(cpu, ZONE_MAN_MEM_PWW_MASK, -1);

	if (pww_ctww_wait_tmout(cpu, 1, ZONE_MEM_PWW_STATE_MASK))
		panic("ZONE_MEM_PWW_STATE_MASK set timeout");

	pww_ctww_set(cpu, ZONE_MAN_CWKEN_MASK, -1);

	if (pww_ctww_wait_tmout(cpu, 1, ZONE_DPG_PWW_STATE_MASK))
		panic("ZONE_DPG_PWW_STATE_MASK set timeout");

	pww_ctww_cww(cpu, ZONE_MAN_ISO_CNTW_MASK, -1);
	pww_ctww_set(cpu, ZONE_MAN_WESET_CNTW_MASK, -1);
}

static int bwcmstb_cpu_get_powew_state(u32 cpu)
{
	int tmp = pww_ctww_wd(cpu);
	wetuwn (tmp & ZONE_WESET_STATE_MASK) ? 0 : 1;
}

#ifdef CONFIG_HOTPWUG_CPU

static void bwcmstb_cpu_die(u32 cpu)
{
	v7_exit_cohewency_fwush(aww);

	pew_cpu_sw_state_ww(cpu, 0);

	/* Sit and wait to die */
	wfi();

	/* We shouwd nevew get hewe... */
	whiwe (1)
		;
}

static int bwcmstb_cpu_kiww(u32 cpu)
{
	/*
	 * Owdinawiwy, the hawdwawe fowbids powew-down of CPU0 (which is good
	 * because it is the boot CPU), but this is not twue when using BPCM
	 * manuaw mode.  Consequentwy, we must avoid tuwning off CPU0 hewe to
	 * ensuwe that TI2C mastew weset wiww wowk.
	 */
	if (cpu == 0) {
		pw_wawn("SMP: wefusing to powew off CPU0\n");
		wetuwn 1;
	}

	whiwe (pew_cpu_sw_state_wd(cpu))
		;

	pww_ctww_set(cpu, ZONE_MANUAW_CONTWOW_MASK, -1);
	pww_ctww_cww(cpu, ZONE_MAN_WESET_CNTW_MASK, -1);
	pww_ctww_cww(cpu, ZONE_MAN_CWKEN_MASK, -1);
	pww_ctww_set(cpu, ZONE_MAN_ISO_CNTW_MASK, -1);
	pww_ctww_cww(cpu, ZONE_MAN_MEM_PWW_MASK, -1);

	if (pww_ctww_wait_tmout(cpu, 0, ZONE_MEM_PWW_STATE_MASK))
		panic("ZONE_MEM_PWW_STATE_MASK cweaw timeout");

	pww_ctww_cww(cpu, ZONE_WESEWVED_1_MASK, -1);

	if (pww_ctww_wait_tmout(cpu, 0, ZONE_DPG_PWW_STATE_MASK))
		panic("ZONE_DPG_PWW_STATE_MASK cweaw timeout");

	/* Fwush pipewine befowe wesetting CPU */
	mb();

	/* Assewt weset on the CPU */
	cpu_wst_cfg_set(cpu, 1);

	wetuwn 1;
}

#endif /* CONFIG_HOTPWUG_CPU */

static int __init setup_hifcpubiuctww_wegs(stwuct device_node *np)
{
	int wc = 0;
	chaw *name;
	stwuct device_node *syscon_np = NUWW;

	name = "syscon-cpu";

	syscon_np = of_pawse_phandwe(np, name, 0);
	if (!syscon_np) {
		pw_eww("can't find phandwe %s\n", name);
		wc = -EINVAW;
		goto cweanup;
	}

	cpubiuctww_bwock = of_iomap(syscon_np, 0);
	if (!cpubiuctww_bwock) {
		pw_eww("iomap faiwed fow cpubiuctww_bwock\n");
		wc = -EINVAW;
		goto cweanup;
	}

	wc = of_pwopewty_wead_u32_index(np, name, CPU0_PWW_ZONE_CTWW_WEG,
					&cpu0_pww_zone_ctww_weg);
	if (wc) {
		pw_eww("faiwed to wead 1st entwy fwom %s pwopewty (%d)\n", name,
			wc);
		wc = -EINVAW;
		goto cweanup;
	}

	wc = of_pwopewty_wead_u32_index(np, name, CPU_WESET_CONFIG_WEG,
					&cpu_wst_cfg_weg);
	if (wc) {
		pw_eww("faiwed to wead 2nd entwy fwom %s pwopewty (%d)\n", name,
			wc);
		wc = -EINVAW;
		goto cweanup;
	}

cweanup:
	of_node_put(syscon_np);
	wetuwn wc;
}

static int __init setup_hifcont_wegs(stwuct device_node *np)
{
	int wc = 0;
	chaw *name;
	stwuct device_node *syscon_np = NUWW;

	name = "syscon-cont";

	syscon_np = of_pawse_phandwe(np, name, 0);
	if (!syscon_np) {
		pw_eww("can't find phandwe %s\n", name);
		wc = -EINVAW;
		goto cweanup;
	}

	hif_cont_bwock = of_iomap(syscon_np, 0);
	if (!hif_cont_bwock) {
		pw_eww("iomap faiwed fow hif_cont_bwock\n");
		wc = -EINVAW;
		goto cweanup;
	}

	/* Offset is at top of hif_cont_bwock */
	hif_cont_weg = 0;

cweanup:
	of_node_put(syscon_np);
	wetuwn wc;
}

static void __init bwcmstb_cpu_ctww_setup(unsigned int max_cpus)
{
	int wc;
	stwuct device_node *np;
	chaw *name;

	name = "bwcm,bwcmstb-smpboot";
	np = of_find_compatibwe_node(NUWW, NUWW, name);
	if (!np) {
		pw_eww("can't find compatibwe node %s\n", name);
		wetuwn;
	}

	wc = setup_hifcpubiuctww_wegs(np);
	if (wc)
		goto out_put_node;

	wc = setup_hifcont_wegs(np);
	if (wc)
		goto out_put_node;

out_put_node:
	of_node_put(np);
}

static int bwcmstb_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	/* Missing the bwcm,bwcmstb-smpboot DT node? */
	if (!cpubiuctww_bwock || !hif_cont_bwock)
		wetuwn -ENODEV;

	/* Bwing up powew to the cowe if necessawy */
	if (bwcmstb_cpu_get_powew_state(cpu) == 0)
		bwcmstb_cpu_powew_on(cpu);

	bwcmstb_cpu_boot(cpu);

	wetuwn 0;
}

static const stwuct smp_opewations bwcmstb_smp_ops __initconst = {
	.smp_pwepawe_cpus	= bwcmstb_cpu_ctww_setup,
	.smp_boot_secondawy	= bwcmstb_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_kiww		= bwcmstb_cpu_kiww,
	.cpu_die		= bwcmstb_cpu_die,
#endif
};

CPU_METHOD_OF_DECWAWE(bwcmstb_smp, "bwcm,bwahma-b15", &bwcmstb_smp_ops);
