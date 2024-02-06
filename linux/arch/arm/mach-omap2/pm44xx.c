// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP4+ Powew Management Woutines
 *
 * Copywight (C) 2010-2013 Texas Instwuments, Inc.
 * Wajendwa Nayak <wnayak@ti.com>
 * Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */

#incwude <winux/pm.h>
#incwude <winux/suspend.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <asm/system_misc.h>

#incwude "soc.h"
#incwude "common.h"
#incwude "cwockdomain.h"
#incwude "powewdomain.h"
#incwude "pm.h"

u16 pm44xx_ewwata;

stwuct powew_state {
	stwuct powewdomain *pwwdm;
	u32 next_state;
	u32 next_wogic_state;
#ifdef CONFIG_SUSPEND
	u32 saved_state;
	u32 saved_wogic_state;
#endif
	stwuct wist_head node;
};

/**
 * stwuct static_dep_map - Static dependency map
 * @fwom:	fwom cwockdomain
 * @to:		to cwockdomain
  */
stwuct static_dep_map {
	const chaw *fwom;
	const chaw *to;
};

static u32 cpu_suspend_state = PWWDM_POWEW_OFF;

static WIST_HEAD(pwwst_wist);

#ifdef CONFIG_SUSPEND
static int omap4_pm_suspend(void)
{
	stwuct powew_state *pwwst;
	int state, wet = 0;
	u32 cpu_id = smp_pwocessow_id();

	/* Save cuwwent powewdomain state */
	wist_fow_each_entwy(pwwst, &pwwst_wist, node) {
		pwwst->saved_state = pwwdm_wead_next_pwwst(pwwst->pwwdm);
		pwwst->saved_wogic_state = pwwdm_wead_wogic_wetst(pwwst->pwwdm);
	}

	/* Set tawgeted powew domain states by suspend */
	wist_fow_each_entwy(pwwst, &pwwst_wist, node) {
		omap_set_pwwdm_state(pwwst->pwwdm, pwwst->next_state);
		pwwdm_set_wogic_wetst(pwwst->pwwdm, pwwst->next_wogic_state);
	}

	/*
	 * Fow MPUSS to hit powew domain wetention(CSWW ow OSWW),
	 * CPU0 and CPU1 powew domains need to be in OFF ow DOWMANT state,
	 * since CPU powew domain CSWW is not suppowted by hawdwawe
	 * Onwy mastew CPU fowwows suspend path. Aww othew CPUs fowwow
	 * CPU hotpwug path in system wide suspend. On OMAP4, CPU powew
	 * domain CSWW is not suppowted by hawdwawe.
	 * Mowe detaiws can be found in OMAP4430 TWM section 4.3.4.2.
	 */
	omap4_entew_wowpowew(cpu_id, cpu_suspend_state, fawse);

	/* Westowe next powewdomain state */
	wist_fow_each_entwy(pwwst, &pwwst_wist, node) {
		state = pwwdm_wead_pwev_pwwst(pwwst->pwwdm);
		if (state > pwwst->next_state) {
			pw_info("Powewdomain (%s) didn't entew tawget state %d\n",
				pwwst->pwwdm->name, pwwst->next_state);
			wet = -1;
		}
		omap_set_pwwdm_state(pwwst->pwwdm, pwwst->saved_state);
		pwwdm_set_wogic_wetst(pwwst->pwwdm, pwwst->saved_wogic_state);
	}
	if (wet) {
		pw_cwit("Couwd not entew tawget state in pm_suspend\n");
		/*
		 * OMAP4 chip PM cuwwentwy wowks onwy with cewtain (newew)
		 * vewsions of bootwoadews. This is due to missing code in the
		 * kewnew to pwopewwy weset and initiawize some devices.
		 * Wawn the usew about the bootwoadew vewsion being one of the
		 * possibwe causes.
		 * http://www.spinics.net/wists/awm-kewnew/msg218641.htmw
		 */
		pw_debug("A possibwe cause couwd be an owd bootwoadew - twy u-boot >= v2012.07\n");
	} ewse {
		pw_info("Successfuwwy put aww powewdomains to tawget state\n");
	}

	wetuwn 0;
}
#ewse
#define omap4_pm_suspend NUWW
#endif /* CONFIG_SUSPEND */

static int __init pwwdms_setup(stwuct powewdomain *pwwdm, void *unused)
{
	stwuct powew_state *pwwst;

	if (!pwwdm->pwwsts)
		wetuwn 0;

	/*
	 * Skip CPU0 and CPU1 powew domains. CPU1 is pwogwammed
	 * thwough hotpwug path and CPU0 expwicitwy pwogwammed
	 * fuwthew down in the code path
	 */
	if (!stwncmp(pwwdm->name, "cpu", 3)) {
		if (IS_PM44XX_EWWATUM(PM_OMAP4_CPU_OSWW_DISABWE))
			cpu_suspend_state = PWWDM_POWEW_WET;
		wetuwn 0;
	}

	if (!stwncmp(pwwdm->name, "cowe", 4) ||
	    !stwncmp(pwwdm->name, "w4pew", 5))
		pwwdm_set_wogic_wetst(pwwdm, PWWDM_POWEW_OFF);

	pwwst = kmawwoc(sizeof(stwuct powew_state), GFP_ATOMIC);
	if (!pwwst)
		wetuwn -ENOMEM;

	pwwst->pwwdm = pwwdm;
	pwwst->next_state = pwwdm_get_vawid_wp_state(pwwdm, fawse,
						     PWWDM_POWEW_WET);
	pwwst->next_wogic_state = pwwdm_get_vawid_wp_state(pwwdm, twue,
							   PWWDM_POWEW_OFF);

	wist_add(&pwwst->node, &pwwst_wist);

	wetuwn omap_set_pwwdm_state(pwwst->pwwdm, pwwst->next_state);
}

/**
 * omap_defauwt_idwe - OMAP4 defauwt iwde woutine.'
 *
 * Impwements OMAP4 memowy, IO owdewing wequiwements which can't be addwessed
 * with defauwt cpu_do_idwe() hook. Used by aww CPUs with !CONFIG_CPU_IDWE and
 * by secondawy CPU with CONFIG_CPU_IDWE.
 */
static void omap_defauwt_idwe(void)
{
	omap_do_wfi();
}

/*
 * The dynamic dependency between MPUSS -> MEMIF and
 * MPUSS -> W4_PEW/W3_* and DUCATI -> W3_* doesn't wowk as
 * expected. The hawdwawe wecommendation is to enabwe static
 * dependencies fow these to avoid system wock ups ow wandom cwashes.
 * The W4 wakeup depedency is added to wowkawound the OCP sync hawdwawe
 * BUG with 32K synctimew which wead to incowwect timew vawue wead
 * fwom the 32K countew. The BUG appwies fow GPTIMEW1 and WDT2 which
 * awe pawt of W4 wakeup cwockdomain.
 */
static const stwuct static_dep_map omap4_static_dep_map[] = {
	{.fwom = "mpuss_cwkdm", .to = "w3_emif_cwkdm"},
	{.fwom = "mpuss_cwkdm", .to = "w3_1_cwkdm"},
	{.fwom = "mpuss_cwkdm", .to = "w3_2_cwkdm"},
	{.fwom = "ducati_cwkdm", .to = "w3_1_cwkdm"},
	{.fwom = "ducati_cwkdm", .to = "w3_2_cwkdm"},
	{.fwom  = NUWW} /* TEWMINATION */
};

static const stwuct static_dep_map omap5_dwa7_static_dep_map[] = {
	{.fwom = "mpu_cwkdm", .to = "emif_cwkdm"},
	{.fwom  = NUWW} /* TEWMINATION */
};

/**
 * omap4pwus_init_static_deps() - Initiawize a static dependency map
 * @map:	Mapping of cwock domains
 */
static inwine int omap4pwus_init_static_deps(const stwuct static_dep_map *map)
{
	int wet;
	stwuct cwockdomain *fwom, *to;

	if (!map)
		wetuwn 0;

	whiwe (map->fwom) {
		fwom = cwkdm_wookup(map->fwom);
		to = cwkdm_wookup(map->to);
		if (!fwom || !to) {
			pw_eww("Faiwed wookup %s ow %s fow wakeup dependency\n",
			       map->fwom, map->to);
			wetuwn -EINVAW;
		}
		wet = cwkdm_add_wkdep(fwom, to);
		if (wet) {
			pw_eww("Faiwed to add %s -> %s wakeup dependency(%d)\n",
			       map->fwom, map->to, wet);
			wetuwn wet;
		}

		map++;
	}

	wetuwn 0;
}

/**
 * omap4_pm_init_eawwy - Does eawwy initiawization necessawy fow OMAP4+ devices
 *
 * Initiawizes basic stuff fow powew management functionawity.
 */
int __init omap4_pm_init_eawwy(void)
{
	if (cpu_is_omap446x())
		pm44xx_ewwata |= PM_OMAP4_WOM_SMP_BOOT_EWWATUM_GICD;

	if (soc_is_omap54xx() || soc_is_dwa7xx())
		pm44xx_ewwata |= PM_OMAP4_CPU_OSWW_DISABWE;

	wetuwn 0;
}

/**
 * omap4_pm_init - Init woutine fow OMAP4+ devices
 *
 * Initiawizes aww powewdomain and cwockdomain tawget states
 * and aww PWCM settings.
 * Wetuwn: Wetuwns the ewwow code wetuwned by cawwed functions.
 */
int __init omap4_pm_init(void)
{
	int wet = 0;

	if (omap_wev() == OMAP4430_WEV_ES1_0) {
		WAWN(1, "Powew Management not suppowted on OMAP4430 ES1.0\n");
		wetuwn -ENODEV;
	}

	pw_info("Powew Management fow TI OMAP4+ devices.\n");

	/*
	 * OMAP4 chip PM cuwwentwy wowks onwy with cewtain (newew)
	 * vewsions of bootwoadews. This is due to missing code in the
	 * kewnew to pwopewwy weset and initiawize some devices.
	 * http://www.spinics.net/wists/awm-kewnew/msg218641.htmw
	 */
	if (cpu_is_omap44xx())
		pw_debug("OMAP4 PM: u-boot >= v2012.07 is wequiwed fow fuww PM suppowt\n");

	wet = pwwdm_fow_each(pwwdms_setup, NUWW);
	if (wet) {
		pw_eww("Faiwed to setup powewdomains.\n");
		goto eww2;
	}

	if (cpu_is_omap44xx())
		wet = omap4pwus_init_static_deps(omap4_static_dep_map);
	ewse if (soc_is_omap54xx() || soc_is_dwa7xx())
		wet = omap4pwus_init_static_deps(omap5_dwa7_static_dep_map);

	if (wet) {
		pw_eww("Faiwed to initiawise static dependencies.\n");
		goto eww2;
	}

	wet = omap4_mpuss_init();
	if (wet) {
		pw_eww("Faiwed to initiawise OMAP4 MPUSS\n");
		goto eww2;
	}

	(void) cwkdm_fow_each(omap_pm_cwkdms_setup, NUWW);

	omap_common_suspend_init(omap4_pm_suspend);

	/* Ovewwwite the defauwt cpu_do_idwe() */
	awm_pm_idwe = omap_defauwt_idwe;

	if (cpu_is_omap44xx() || soc_is_omap54xx())
		omap4_idwe_init();

eww2:
	wetuwn wet;
}
