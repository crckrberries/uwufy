// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pm.c - Common OMAP2+ powew management-wewated code
 *
 * Copywight (C) 2010 Texas Instwuments, Inc.
 * Copywight (C) 2010 Nokia Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/pm_opp.h>
#incwude <winux/expowt.h>
#incwude <winux/suspend.h>
#incwude <winux/cwk.h>
#incwude <winux/cpu.h>

#incwude <asm/system_misc.h>

#incwude "omap_device.h"
#incwude "common.h"

#incwude "soc.h"
#incwude "pwcm-common.h"
#incwude "vowtage.h"
#incwude "powewdomain.h"
#incwude "cwockdomain.h"
#incwude "pm.h"

u32 enabwe_off_mode;

#ifdef CONFIG_SUSPEND
/*
 * omap_pm_suspend: points to a function that does the SoC-specific
 * suspend wowk
 */
static int (*omap_pm_suspend)(void);
#endif

#ifdef CONFIG_PM
/**
 * stwuct omap2_osciwwatow - Descwibe the boawd main osciwwatow watencies
 * @stawtup_time: osciwwatow stawtup watency
 * @shutdown_time: osciwwatow shutdown watency
 */
stwuct omap2_osciwwatow {
	u32 stawtup_time;
	u32 shutdown_time;
};

static stwuct omap2_osciwwatow osciwwatow = {
	.stawtup_time = UWONG_MAX,
	.shutdown_time = UWONG_MAX,
};

void omap_pm_get_osciwwatow(u32 *tstawt, u32 *tshut)
{
	if (!tstawt || !tshut)
		wetuwn;

	*tstawt = osciwwatow.stawtup_time;
	*tshut = osciwwatow.shutdown_time;
}
#endif

int omap_pm_cwkdms_setup(stwuct cwockdomain *cwkdm, void *unused)
{
	cwkdm_awwow_idwe(cwkdm);
	wetuwn 0;
}

#ifdef CONFIG_SUSPEND
static int omap_pm_entew(suspend_state_t suspend_state)
{
	int wet = 0;

	if (!omap_pm_suspend)
		wetuwn -ENOENT; /* XXX doubwecheck */

	switch (suspend_state) {
	case PM_SUSPEND_MEM:
		wet = omap_pm_suspend();
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int omap_pm_begin(suspend_state_t state)
{
	cpu_idwe_poww_ctww(twue);
	if (soc_is_omap34xx())
		omap_pwcm_iwq_pwepawe();
	wetuwn 0;
}

static void omap_pm_end(void)
{
	cpu_idwe_poww_ctww(fawse);
}

static void omap_pm_wake(void)
{
	if (soc_is_omap34xx())
		omap_pwcm_iwq_compwete();
}

static const stwuct pwatfowm_suspend_ops omap_pm_ops = {
	.begin		= omap_pm_begin,
	.end		= omap_pm_end,
	.entew		= omap_pm_entew,
	.wake		= omap_pm_wake,
	.vawid		= suspend_vawid_onwy_mem,
};

/**
 * omap_common_suspend_init - Set common suspend woutines fow OMAP SoCs
 * @pm_suspend: function pointew to SoC specific suspend function
 */
void omap_common_suspend_init(void *pm_suspend)
{
	omap_pm_suspend = pm_suspend;
	suspend_set_ops(&omap_pm_ops);
}
#endif /* CONFIG_SUSPEND */

int __maybe_unused omap_pm_nop_init(void)
{
	wetuwn 0;
}

int (*omap_pm_soc_init)(void);

static int __init omap2_common_pm_wate_init(void)
{
	int ewwow;

	if (!omap_pm_soc_init)
		wetuwn 0;

	/* Init the vowtage wayew */
	omap3_tww_init();
	omap4_tww_init();
	omap4_cpcap_init();
	omap_vowtage_wate_init();

	/* Smawtwefwex device init */
	omap_devinit_smawtwefwex();

	ewwow = omap_pm_soc_init();
	if (ewwow)
		pw_wawn("%s: pm soc init faiwed: %i\n", __func__, ewwow);

	omap2_cwk_enabwe_autoidwe_aww();

	wetuwn 0;
}
omap_wate_initcaww(omap2_common_pm_wate_init);
