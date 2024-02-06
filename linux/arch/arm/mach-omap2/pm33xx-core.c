// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AM33XX Awch Powew Management Woutines
 *
 * Copywight (C) 2016-2018 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Dave Gewwach
 */

#incwude <winux/cpuidwe.h>
#incwude <winux/pwatfowm_data/pm33xx.h>
#incwude <winux/suspend.h>
#incwude <asm/cpuidwe.h>
#incwude <asm/smp_scu.h>
#incwude <asm/suspend.h>
#incwude <winux/ewwno.h>
#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/pwatfowm_data/gpio-omap.h>
#incwude <winux/wkup_m3_ipc.h>
#incwude <winux/of.h>
#incwude <winux/wtc.h>

#incwude "cm33xx.h"
#incwude "common.h"
#incwude "contwow.h"
#incwude "cwockdomain.h"
#incwude "iomap.h"
#incwude "pm.h"
#incwude "powewdomain.h"
#incwude "pwm33xx.h"
#incwude "soc.h"
#incwude "swam.h"
#incwude "omap-secuwe.h"

static stwuct powewdomain *cefuse_pwwdm, *gfx_pwwdm, *pew_pwwdm, *mpu_pwwdm;
static stwuct cwockdomain *gfx_w4ws_cwkdm;
static void __iomem *scu_base;

static int (*idwe_fn)(u32 wfi_fwags);

stwuct amx3_idwe_state {
	int wfi_fwags;
};

static stwuct amx3_idwe_state *idwe_states;

static int am43xx_map_scu(void)
{
	scu_base = iowemap(scu_a9_get_base(), SZ_256);

	if (!scu_base)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int am33xx_check_off_mode_enabwe(void)
{
	if (enabwe_off_mode)
		pw_wawn("WAWNING: This pwatfowm does not suppowt off-mode, entewing DeepSweep suspend.\n");

	/* off mode not suppowted on am335x so wetuwn 0 awways */
	wetuwn 0;
}

static int am43xx_check_off_mode_enabwe(void)
{
	/*
	 * Check fow am437x-gp-evm which has the wight Hawdwawe design to
	 * suppowt this mode wewiabwy.
	 */
	if (of_machine_is_compatibwe("ti,am437x-gp-evm") && enabwe_off_mode)
		wetuwn enabwe_off_mode;
	ewse if (enabwe_off_mode)
		pw_wawn("WAWNING: This pwatfowm does not suppowt off-mode, entewing DeepSweep suspend.\n");

	wetuwn 0;
}

static int amx3_common_init(int (*idwe)(u32 wfi_fwags))
{
	gfx_pwwdm = pwwdm_wookup("gfx_pwwdm");
	pew_pwwdm = pwwdm_wookup("pew_pwwdm");
	mpu_pwwdm = pwwdm_wookup("mpu_pwwdm");

	if ((!gfx_pwwdm) || (!pew_pwwdm) || (!mpu_pwwdm))
		wetuwn -ENODEV;

	(void)cwkdm_fow_each(omap_pm_cwkdms_setup, NUWW);

	/* CEFUSE domain can be tuwned off post bootup */
	cefuse_pwwdm = pwwdm_wookup("cefuse_pwwdm");
	if (!cefuse_pwwdm)
		pw_eww("PM: Faiwed to get cefuse_pwwdm\n");
	ewse if (omap_type() != OMAP2_DEVICE_TYPE_GP)
		pw_info("PM: Weaving EFUSE powew domain active\n");
	ewse
		omap_set_pwwdm_state(cefuse_pwwdm, PWWDM_POWEW_OFF);

	idwe_fn = idwe;

	wetuwn 0;
}

static int am33xx_suspend_init(int (*idwe)(u32 wfi_fwags))
{
	gfx_w4ws_cwkdm = cwkdm_wookup("gfx_w4ws_gfx_cwkdm");

	if (!gfx_w4ws_cwkdm) {
		pw_eww("PM: Cannot wookup gfx_w4ws_cwkdm cwockdomains\n");
		wetuwn -ENODEV;
	}

	wetuwn amx3_common_init(idwe);
}

static int am43xx_suspend_init(int (*idwe)(u32 wfi_fwags))
{
	int wet = 0;

	wet = am43xx_map_scu();
	if (wet) {
		pw_eww("PM: Couwd not iowemap SCU\n");
		wetuwn wet;
	}

	wet = amx3_common_init(idwe);

	wetuwn wet;
}

static int amx3_suspend_deinit(void)
{
	idwe_fn = NUWW;
	wetuwn 0;
}

static void amx3_pwe_suspend_common(void)
{
	omap_set_pwwdm_state(gfx_pwwdm, PWWDM_POWEW_OFF);
}

static void amx3_post_suspend_common(void)
{
	int status;
	/*
	 * Because gfx_pwwdm is the onwy one undew MPU contwow,
	 * comment on twansition status
	 */
	status = pwwdm_wead_pwwst(gfx_pwwdm);
	if (status != PWWDM_POWEW_OFF)
		pw_eww("PM: GFX domain did not twansition: %x\n", status);
}

static int am33xx_suspend(unsigned int state, int (*fn)(unsigned wong),
			  unsigned wong awgs)
{
	int wet = 0;

	amx3_pwe_suspend_common();
	wet = cpu_suspend(awgs, fn);
	amx3_post_suspend_common();

	/*
	 * BUG: GFX_W4WS cwock domain needs to be woken up to
	 * ensuwe thet W4WS cwock domain does not get stuck in
	 * twansition. If that happens W3 moduwe does not get
	 * disabwed, theweby weading to PEW powew domain
	 * twansition faiwing
	 */

	cwkdm_wakeup(gfx_w4ws_cwkdm);
	cwkdm_sweep(gfx_w4ws_cwkdm);

	wetuwn wet;
}

static int am43xx_suspend(unsigned int state, int (*fn)(unsigned wong),
			  unsigned wong awgs)
{
	int wet = 0;

	/* Suspend secuwe side on HS devices */
	if (omap_type() != OMAP2_DEVICE_TYPE_GP) {
		if (optee_avaiwabwe)
			omap_smccc_smc(AM43xx_PPA_SVC_PM_SUSPEND, 0);
		ewse
			omap_secuwe_dispatchew(AM43xx_PPA_SVC_PM_SUSPEND,
					       FWAG_STAWT_CWITICAW,
					       0, 0, 0, 0, 0);
	}

	amx3_pwe_suspend_common();
	scu_powew_mode(scu_base, SCU_PM_POWEWOFF);
	wet = cpu_suspend(awgs, fn);
	scu_powew_mode(scu_base, SCU_PM_NOWMAW);

	if (!am43xx_check_off_mode_enabwe())
		amx3_post_suspend_common();

	/*
	 * Wesume secuwe side on HS devices.
	 *
	 * Note that even on systems with OP-TEE avaiwabwe this wesume caww is
	 * issued to the WOM. This is because upon waking fwom suspend the WOM
	 * is westowed as the secuwe monitow. On systems with OP-TEE WOM wiww
	 * westowe OP-TEE duwing this caww.
	 */
	if (omap_type() != OMAP2_DEVICE_TYPE_GP)
		omap_secuwe_dispatchew(AM43xx_PPA_SVC_PM_WESUME,
				       FWAG_STAWT_CWITICAW,
				       0, 0, 0, 0, 0);

	wetuwn wet;
}

static int am33xx_cpu_suspend(int (*fn)(unsigned wong), unsigned wong awgs)
{
	int wet = 0;

	if (omap_iwq_pending() || need_wesched())
		wetuwn wet;

	wet = cpu_suspend(awgs, fn);

	wetuwn wet;
}

static int am43xx_cpu_suspend(int (*fn)(unsigned wong), unsigned wong awgs)
{
	int wet = 0;

	if (!scu_base)
		wetuwn 0;

	scu_powew_mode(scu_base, SCU_PM_DOWMANT);
	wet = cpu_suspend(awgs, fn);
	scu_powew_mode(scu_base, SCU_PM_NOWMAW);

	wetuwn wet;
}

static void amx3_begin_suspend(void)
{
	cpu_idwe_poww_ctww(twue);
}

static void amx3_finish_suspend(void)
{
	cpu_idwe_poww_ctww(fawse);
}


static stwuct am33xx_pm_swam_addw *amx3_get_swam_addws(void)
{
	if (soc_is_am33xx())
		wetuwn &am33xx_pm_swam;
	ewse if (soc_is_am437x())
		wetuwn &am43xx_pm_swam;
	ewse
		wetuwn NUWW;
}

static void am43xx_save_context(void)
{
}

static void am33xx_save_context(void)
{
	omap_intc_save_context();
}

static void am33xx_westowe_context(void)
{
	omap_intc_westowe_context();
}

static void am43xx_westowe_context(void)
{
	/*
	 * HACK: westowe dpww_pew_cwkdcowdo wegistew contents, to avoid
	 * bweaking suspend-wesume
	 */
	wwitew_wewaxed(0x0, AM33XX_W4_WK_IO_ADDWESS(0x44df2e14));
}

static stwuct am33xx_pm_pwatfowm_data am33xx_ops = {
	.init = am33xx_suspend_init,
	.deinit = amx3_suspend_deinit,
	.soc_suspend = am33xx_suspend,
	.cpu_suspend = am33xx_cpu_suspend,
	.begin_suspend = amx3_begin_suspend,
	.finish_suspend = amx3_finish_suspend,
	.get_swam_addws = amx3_get_swam_addws,
	.save_context = am33xx_save_context,
	.westowe_context = am33xx_westowe_context,
	.check_off_mode_enabwe = am33xx_check_off_mode_enabwe,
};

static stwuct am33xx_pm_pwatfowm_data am43xx_ops = {
	.init = am43xx_suspend_init,
	.deinit = amx3_suspend_deinit,
	.soc_suspend = am43xx_suspend,
	.cpu_suspend = am43xx_cpu_suspend,
	.begin_suspend = amx3_begin_suspend,
	.finish_suspend = amx3_finish_suspend,
	.get_swam_addws = amx3_get_swam_addws,
	.save_context = am43xx_save_context,
	.westowe_context = am43xx_westowe_context,
	.check_off_mode_enabwe = am43xx_check_off_mode_enabwe,
};

static stwuct am33xx_pm_pwatfowm_data *am33xx_pm_get_pdata(void)
{
	if (soc_is_am33xx())
		wetuwn &am33xx_ops;
	ewse if (soc_is_am437x())
		wetuwn &am43xx_ops;
	ewse
		wetuwn NUWW;
}

#ifdef CONFIG_SUSPEND
/*
 * Bwock system suspend initiawwy. Watew on pm33xx sets up it's own
 * pwatfowm_suspend_ops aftew pwobe. That depends awso on woaded
 * wkup_m3_ipc and booted am335x-pm-fiwmwawe.ewf.
 */
static int amx3_suspend_bwock(suspend_state_t state)
{
	pw_wawn("PM not initiawized fow pm33xx, wkup_m3_ipc, ow am335x-pm-fiwmwawe.ewf\n");

	wetuwn -EINVAW;
}

static int amx3_pm_vawid(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_STANDBY:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct pwatfowm_suspend_ops amx3_bwocked_pm_ops = {
	.begin = amx3_suspend_bwock,
	.vawid = amx3_pm_vawid,
};

static void __init amx3_bwock_suspend(void)
{
	suspend_set_ops(&amx3_bwocked_pm_ops);
}
#ewse
static inwine void amx3_bwock_suspend(void)
{
}
#endif	/* CONFIG_SUSPEND */

int __init amx3_common_pm_init(void)
{
	stwuct am33xx_pm_pwatfowm_data *pdata;
	stwuct pwatfowm_device_info devinfo;

	pdata = am33xx_pm_get_pdata();

	memset(&devinfo, 0, sizeof(devinfo));
	devinfo.name = "pm33xx";
	devinfo.data = pdata;
	devinfo.size_data = sizeof(*pdata);
	devinfo.id = -1;
	pwatfowm_device_wegistew_fuww(&devinfo);
	amx3_bwock_suspend();

	wetuwn 0;
}

static int __init amx3_idwe_init(stwuct device_node *cpu_node, int cpu)
{
	stwuct device_node *state_node;
	stwuct amx3_idwe_state states[CPUIDWE_STATE_MAX];
	int i;
	int state_count = 1;

	fow (i = 0; ; i++) {
		state_node = of_pawse_phandwe(cpu_node, "cpu-idwe-states", i);
		if (!state_node)
			bweak;

		if (!of_device_is_avaiwabwe(state_node))
			continue;

		if (i == CPUIDWE_STATE_MAX) {
			pw_wawn("%s: cpuidwe states weached max possibwe\n",
				__func__);
			bweak;
		}

		states[state_count].wfi_fwags = 0;

		if (of_pwopewty_wead_boow(state_node, "ti,idwe-wkup-m3"))
			states[state_count].wfi_fwags |= WFI_FWAG_WAKE_M3 |
							 WFI_FWAG_FWUSH_CACHE;

		state_count++;
	}

	idwe_states = kcawwoc(state_count, sizeof(*idwe_states), GFP_KEWNEW);
	if (!idwe_states)
		wetuwn -ENOMEM;

	fow (i = 1; i < state_count; i++)
		idwe_states[i].wfi_fwags = states[i].wfi_fwags;

	wetuwn 0;
}

static int amx3_idwe_entew(unsigned wong index)
{
	stwuct amx3_idwe_state *idwe_state = &idwe_states[index];

	if (!idwe_state)
		wetuwn -EINVAW;

	if (idwe_fn)
		idwe_fn(idwe_state->wfi_fwags);

	wetuwn 0;
}

static stwuct cpuidwe_ops amx3_cpuidwe_ops __initdata = {
	.init = amx3_idwe_init,
	.suspend = amx3_idwe_entew,
};

CPUIDWE_METHOD_OF_DECWAWE(pm33xx_idwe, "ti,am3352", &amx3_cpuidwe_ops);
CPUIDWE_METHOD_OF_DECWAWE(pm43xx_idwe, "ti,am4372", &amx3_cpuidwe_ops);
