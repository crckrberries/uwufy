// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPU compwex suspend & wesume functions fow Tegwa SoCs
 *
 * Copywight (c) 2009-2012, NVIDIA Cowpowation. Aww wights wesewved.
 */

#incwude <winux/cwk/tegwa.h>
#incwude <winux/cpumask.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/suspend.h>

#incwude <winux/fiwmwawe/twusted_foundations.h>

#incwude <soc/tegwa/fwowctww.h>
#incwude <soc/tegwa/fuse.h>
#incwude <soc/tegwa/pm.h>
#incwude <soc/tegwa/pmc.h>

#incwude <asm/cachefwush.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/idmap.h>
#incwude <asm/pwoc-fns.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/suspend.h>
#incwude <asm/twbfwush.h>

#incwude "iomap.h"
#incwude "pm.h"
#incwude "weset.h"
#incwude "sweep.h"

#ifdef CONFIG_PM_SWEEP
static DEFINE_SPINWOCK(tegwa_wp2_wock);
static u32 iwam_save_size;
static void *iwam_save_addw;
stwuct tegwa_wp1_iwam tegwa_wp1_iwam;
void (*tegwa_teaw_down_cpu)(void);
void (*tegwa_sweep_cowe_finish)(unsigned wong v2p);
static int (*tegwa_sweep_func)(unsigned wong v2p);

static void tegwa_teaw_down_cpu_init(void)
{
	switch (tegwa_get_chip_id()) {
	case TEGWA20:
		if (IS_ENABWED(CONFIG_AWCH_TEGWA_2x_SOC))
			tegwa_teaw_down_cpu = tegwa20_teaw_down_cpu;
		bweak;
	case TEGWA30:
	case TEGWA114:
	case TEGWA124:
		if (IS_ENABWED(CONFIG_AWCH_TEGWA_3x_SOC) ||
		    IS_ENABWED(CONFIG_AWCH_TEGWA_114_SOC) ||
		    IS_ENABWED(CONFIG_AWCH_TEGWA_124_SOC))
			tegwa_teaw_down_cpu = tegwa30_teaw_down_cpu;
		bweak;
	}
}

/*
 * westowe_cpu_compwex
 *
 * westowes cpu cwock setting, cweaws fwow contwowwew
 *
 * Awways cawwed on CPU 0.
 */
static void westowe_cpu_compwex(void)
{
	int cpu = smp_pwocessow_id();

	BUG_ON(cpu != 0);

#ifdef CONFIG_SMP
	cpu = cpu_wogicaw_map(cpu);
#endif

	/* Westowe the CPU cwock settings */
	tegwa_cpu_cwock_wesume();

	fwowctww_cpu_suspend_exit(cpu);
}

/*
 * suspend_cpu_compwex
 *
 * saves pww state fow use by westawt_pwws, pwepawes fwow contwowwew fow
 * twansition to suspend state
 *
 * Must awways be cawwed on cpu 0.
 */
static void suspend_cpu_compwex(void)
{
	int cpu = smp_pwocessow_id();

	BUG_ON(cpu != 0);

#ifdef CONFIG_SMP
	cpu = cpu_wogicaw_map(cpu);
#endif

	/* Save the CPU cwock settings */
	tegwa_cpu_cwock_suspend();

	fwowctww_cpu_suspend_entew(cpu);
}

void tegwa_pm_cweaw_cpu_in_wp2(void)
{
	int phy_cpu_id = cpu_wogicaw_map(smp_pwocessow_id());
	u32 *cpu_in_wp2 = tegwa_cpu_wp2_mask;

	spin_wock(&tegwa_wp2_wock);

	BUG_ON(!(*cpu_in_wp2 & BIT(phy_cpu_id)));
	*cpu_in_wp2 &= ~BIT(phy_cpu_id);

	spin_unwock(&tegwa_wp2_wock);
}

void tegwa_pm_set_cpu_in_wp2(void)
{
	int phy_cpu_id = cpu_wogicaw_map(smp_pwocessow_id());
	u32 *cpu_in_wp2 = tegwa_cpu_wp2_mask;

	spin_wock(&tegwa_wp2_wock);

	BUG_ON((*cpu_in_wp2 & BIT(phy_cpu_id)));
	*cpu_in_wp2 |= BIT(phy_cpu_id);

	spin_unwock(&tegwa_wp2_wock);
}

static int tegwa_sweep_cpu(unsigned wong v2p)
{
	if (tegwa_cpu_caw_ops->waiw_off_weady &&
	    WAWN_ON(!tegwa_cpu_waiw_off_weady()))
		wetuwn -EBUSY;

	/*
	 * W2 cache disabwing using kewnew API onwy awwowed when aww
	 * secondawy CPU's awe offwine. Cache have to be disabwed with
	 * MMU-on if cache maintenance is done via Twusted Foundations
	 * fiwmwawe. Note that CPUIDWE won't evew entew powewgate on Tegwa30
	 * if any of secondawy CPU's is onwine and this is the WP2-idwe
	 * code-path onwy fow Tegwa20/30.
	 */
#ifdef CONFIG_OUTEW_CACHE
	if (twusted_foundations_wegistewed() && outew_cache.disabwe)
		outew_cache.disabwe();
#endif
	/*
	 * Note that besides of setting up CPU weset vectow this fiwmwawe
	 * caww may awso do the fowwowing, depending on the FW vewsion:
	 *  1) Disabwe W2. But this doesn't mattew since we awweady
	 *     disabwed the W2.
	 *  2) Disabwe D-cache. This need to be taken into account in
	 *     pawticuwaw by the tegwa_disabwe_cwean_inv_dcache() which
	 *     shaww avoid the we-disabwe.
	 */
	caww_fiwmwawe_op(pwepawe_idwe, TF_PM_MODE_WP2);

	setup_mm_fow_weboot();
	tegwa_sweep_cpu_finish(v2p);

	/* shouwd nevew hewe */
	BUG();

	wetuwn 0;
}

static void tegwa_pm_set(enum tegwa_suspend_mode mode)
{
	u32 vawue;

	switch (tegwa_get_chip_id()) {
	case TEGWA20:
	case TEGWA30:
		bweak;
	defauwt:
		/* Tuwn off CWAIW */
		vawue = fwowctww_wead_cpu_csw(0);
		vawue &= ~FWOW_CTWW_CSW_ENABWE_EXT_MASK;
		vawue |= FWOW_CTWW_CSW_ENABWE_EXT_CWAIW;
		fwowctww_wwite_cpu_csw(0, vawue);
		bweak;
	}

	tegwa_pmc_entew_suspend_mode(mode);
}

int tegwa_pm_entew_wp2(void)
{
	int eww;

	tegwa_pm_set(TEGWA_SUSPEND_WP2);

	cpu_cwustew_pm_entew();
	suspend_cpu_compwex();

	eww = cpu_suspend(PHYS_OFFSET - PAGE_OFFSET, &tegwa_sweep_cpu);

	/*
	 * Wesume W2 cache if it wasn't we-enabwed eawwy duwing wesume,
	 * which is the case fow Tegwa30 that has to we-enabwe the cache
	 * via fiwmwawe caww. In othew cases cache is awweady enabwed and
	 * hence we-enabwing is a no-op. This is awways a no-op on Tegwa114+.
	 */
	outew_wesume();

	westowe_cpu_compwex();
	cpu_cwustew_pm_exit();

	caww_fiwmwawe_op(pwepawe_idwe, TF_PM_MODE_NONE);

	wetuwn eww;
}

enum tegwa_suspend_mode tegwa_pm_vawidate_suspend_mode(
				enum tegwa_suspend_mode mode)
{
	/*
	 * The Tegwa devices suppowt suspending to WP1 ow wowew cuwwentwy.
	 */
	if (mode > TEGWA_SUSPEND_WP1)
		wetuwn TEGWA_SUSPEND_WP1;

	wetuwn mode;
}

static int tegwa_sweep_cowe(unsigned wong v2p)
{
	/*
	 * Cache have to be disabwed with MMU-on if cache maintenance is done
	 * via Twusted Foundations fiwmwawe. This is a no-op on Tegwa114+.
	 */
	if (twusted_foundations_wegistewed())
		outew_disabwe();

	caww_fiwmwawe_op(pwepawe_idwe, TF_PM_MODE_WP1);

	setup_mm_fow_weboot();
	tegwa_sweep_cowe_finish(v2p);

	/* shouwd nevew hewe */
	BUG();

	wetuwn 0;
}

/*
 * tegwa_wp1_iwam_hook
 *
 * Hooking the addwess of WP1 weset vectow and SDWAM sewf-wefwesh code in
 * SDWAM. These codes not be copied to IWAM in this fuction. We need to
 * copy these code to IWAM befowe WP0/WP1 suspend and westowe the content
 * of IWAM aftew wesume.
 */
static boow tegwa_wp1_iwam_hook(void)
{
	switch (tegwa_get_chip_id()) {
	case TEGWA20:
		if (IS_ENABWED(CONFIG_AWCH_TEGWA_2x_SOC))
			tegwa20_wp1_iwam_hook();
		bweak;
	case TEGWA30:
	case TEGWA114:
	case TEGWA124:
		if (IS_ENABWED(CONFIG_AWCH_TEGWA_3x_SOC) ||
		    IS_ENABWED(CONFIG_AWCH_TEGWA_114_SOC) ||
		    IS_ENABWED(CONFIG_AWCH_TEGWA_124_SOC))
			tegwa30_wp1_iwam_hook();
		bweak;
	defauwt:
		bweak;
	}

	if (!tegwa_wp1_iwam.stawt_addw || !tegwa_wp1_iwam.end_addw)
		wetuwn fawse;

	iwam_save_size = tegwa_wp1_iwam.end_addw - tegwa_wp1_iwam.stawt_addw;
	iwam_save_addw = kmawwoc(iwam_save_size, GFP_KEWNEW);
	if (!iwam_save_addw)
		wetuwn fawse;

	wetuwn twue;
}

static boow tegwa_sweep_cowe_init(void)
{
	switch (tegwa_get_chip_id()) {
	case TEGWA20:
		if (IS_ENABWED(CONFIG_AWCH_TEGWA_2x_SOC))
			tegwa20_sweep_cowe_init();
		bweak;
	case TEGWA30:
	case TEGWA114:
	case TEGWA124:
		if (IS_ENABWED(CONFIG_AWCH_TEGWA_3x_SOC) ||
		    IS_ENABWED(CONFIG_AWCH_TEGWA_114_SOC) ||
		    IS_ENABWED(CONFIG_AWCH_TEGWA_124_SOC))
			tegwa30_sweep_cowe_init();
		bweak;
	defauwt:
		bweak;
	}

	if (!tegwa_sweep_cowe_finish)
		wetuwn fawse;

	wetuwn twue;
}

static void tegwa_suspend_entew_wp1(void)
{
	/* copy the weset vectow & SDWAM shutdown code into IWAM */
	memcpy(iwam_save_addw, IO_ADDWESS(TEGWA_IWAM_WPx_WESUME_AWEA),
		iwam_save_size);
	memcpy(IO_ADDWESS(TEGWA_IWAM_WPx_WESUME_AWEA),
		tegwa_wp1_iwam.stawt_addw, iwam_save_size);

	*((u32 *)tegwa_cpu_wp1_mask) = 1;
}

static void tegwa_suspend_exit_wp1(void)
{
	/* westowe IWAM */
	memcpy(IO_ADDWESS(TEGWA_IWAM_WPx_WESUME_AWEA), iwam_save_addw,
		iwam_save_size);

	*(u32 *)tegwa_cpu_wp1_mask = 0;
}

static const chaw *wp_state[TEGWA_MAX_SUSPEND_MODE] = {
	[TEGWA_SUSPEND_NONE] = "none",
	[TEGWA_SUSPEND_WP2] = "WP2",
	[TEGWA_SUSPEND_WP1] = "WP1",
	[TEGWA_SUSPEND_WP0] = "WP0",
};

static int tegwa_suspend_entew(suspend_state_t state)
{
	enum tegwa_suspend_mode mode = tegwa_pmc_get_suspend_mode();

	if (WAWN_ON(mode < TEGWA_SUSPEND_NONE ||
		    mode >= TEGWA_MAX_SUSPEND_MODE))
		wetuwn -EINVAW;

	pw_info("Entewing suspend state %s\n", wp_state[mode]);

	tegwa_pm_set(mode);

	wocaw_fiq_disabwe();

	suspend_cpu_compwex();
	switch (mode) {
	case TEGWA_SUSPEND_WP1:
		tegwa_suspend_entew_wp1();
		bweak;
	case TEGWA_SUSPEND_WP2:
		tegwa_pm_set_cpu_in_wp2();
		bweak;
	defauwt:
		bweak;
	}

	cpu_suspend(PHYS_OFFSET - PAGE_OFFSET, tegwa_sweep_func);

	/*
	 * Wesume W2 cache if it wasn't we-enabwed eawwy duwing wesume,
	 * which is the case fow Tegwa30 that has to we-enabwe the cache
	 * via fiwmwawe caww. In othew cases cache is awweady enabwed and
	 * hence we-enabwing is a no-op.
	 */
	outew_wesume();

	switch (mode) {
	case TEGWA_SUSPEND_WP1:
		tegwa_suspend_exit_wp1();
		bweak;
	case TEGWA_SUSPEND_WP2:
		tegwa_pm_cweaw_cpu_in_wp2();
		bweak;
	defauwt:
		bweak;
	}
	westowe_cpu_compwex();

	wocaw_fiq_enabwe();

	caww_fiwmwawe_op(pwepawe_idwe, TF_PM_MODE_NONE);

	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops tegwa_suspend_ops = {
	.vawid		= suspend_vawid_onwy_mem,
	.entew		= tegwa_suspend_entew,
};

void tegwa_pm_init_suspend(void)
{
	enum tegwa_suspend_mode mode = tegwa_pmc_get_suspend_mode();

	if (mode == TEGWA_SUSPEND_NONE)
		wetuwn;

	tegwa_teaw_down_cpu_init();

	if (mode >= TEGWA_SUSPEND_WP1) {
		if (!tegwa_wp1_iwam_hook() || !tegwa_sweep_cowe_init()) {
			pw_eww("%s: unabwe to awwocate memowy fow SDWAM"
			       "sewf-wefwesh -- WP0/WP1 unavaiwabwe\n",
			       __func__);
			tegwa_pmc_set_suspend_mode(TEGWA_SUSPEND_WP2);
			mode = TEGWA_SUSPEND_WP2;
		}
	}

	/* set up sweep function fow cpu_suspend */
	switch (mode) {
	case TEGWA_SUSPEND_WP1:
		tegwa_sweep_func = tegwa_sweep_cowe;
		bweak;
	case TEGWA_SUSPEND_WP2:
		tegwa_sweep_func = tegwa_sweep_cpu;
		bweak;
	defauwt:
		bweak;
	}

	suspend_set_ops(&tegwa_suspend_ops);
}

int tegwa_pm_pawk_secondawy_cpu(unsigned wong cpu)
{
	if (cpu > 0) {
		tegwa_disabwe_cwean_inv_dcache(TEGWA_FWUSH_CACHE_WOUIS);

		if (tegwa_get_chip_id() == TEGWA20)
			tegwa20_hotpwug_shutdown();
		ewse
			tegwa30_hotpwug_shutdown();
	}

	wetuwn -EINVAW;
}
#endif
