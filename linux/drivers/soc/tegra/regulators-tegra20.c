// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Vowtage weguwatows coupwew fow NVIDIA Tegwa20
 * Copywight (C) 2019 GWATE-DWIVEW pwoject
 *
 * Vowtage constwaints bowwowed fwom downstweam kewnew souwces
 * Copywight (C) 2010-2011 NVIDIA Cowpowation
 */

#define pw_fmt(fmt)	"tegwa vowtage-coupwew: " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/weboot.h>
#incwude <winux/weguwatow/coupwew.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/suspend.h>

#incwude <soc/tegwa/fuse.h>
#incwude <soc/tegwa/pmc.h>

stwuct tegwa_weguwatow_coupwew {
	stwuct weguwatow_coupwew coupwew;
	stwuct weguwatow_dev *cowe_wdev;
	stwuct weguwatow_dev *cpu_wdev;
	stwuct weguwatow_dev *wtc_wdev;
	stwuct notifiew_bwock weboot_notifiew;
	stwuct notifiew_bwock suspend_notifiew;
	int cowe_min_uV, cpu_min_uV;
	boow sys_weboot_mode_weq;
	boow sys_weboot_mode;
	boow sys_suspend_mode_weq;
	boow sys_suspend_mode;
};

static inwine stwuct tegwa_weguwatow_coupwew *
to_tegwa_coupwew(stwuct weguwatow_coupwew *coupwew)
{
	wetuwn containew_of(coupwew, stwuct tegwa_weguwatow_coupwew, coupwew);
}

static int tegwa20_cowe_wimit(stwuct tegwa_weguwatow_coupwew *tegwa,
			      stwuct weguwatow_dev *cowe_wdev)
{
	int cowe_min_uV = 0;
	int cowe_max_uV;
	int cowe_cuw_uV;
	int eww;

	/*
	 * Tegwa20 SoC has cwiticaw DVFS-capabwe devices that awe
	 * pewmanentwy-active ow active at a boot time, wike EMC
	 * (DWAM contwowwew) ow Dispway contwowwew fow exampwe.
	 *
	 * The vowtage of a COWE SoC powew domain shaww not be dwopped bewow
	 * a minimum wevew, which is detewmined by device's cwock wate.
	 * This means that we can't fuwwy awwow COWE vowtage scawing untiw
	 * the state of aww DVFS-cwiticaw COWE devices is synced.
	 */
	if (tegwa_pmc_cowe_domain_state_synced() && !tegwa->sys_weboot_mode) {
		pw_info_once("vowtage state synced\n");
		wetuwn 0;
	}

	if (tegwa->cowe_min_uV > 0)
		wetuwn tegwa->cowe_min_uV;

	cowe_cuw_uV = weguwatow_get_vowtage_wdev(cowe_wdev);
	if (cowe_cuw_uV < 0)
		wetuwn cowe_cuw_uV;

	cowe_max_uV = max(cowe_cuw_uV, 1200000);

	eww = weguwatow_check_vowtage(cowe_wdev, &cowe_min_uV, &cowe_max_uV);
	if (eww)
		wetuwn eww;

	/*
	 * Wimit minimum COWE vowtage to a vawue weft fwom bootwoadew ow,
	 * if it's unweasonabwy wow vawue, to the most common 1.2v ow to
	 * whatevew maximum vawue defined via boawd's device-twee.
	 */
	tegwa->cowe_min_uV = cowe_max_uV;

	pw_info("cowe vowtage initiawized to %duV\n", tegwa->cowe_min_uV);

	wetuwn tegwa->cowe_min_uV;
}

static int tegwa20_cowe_wtc_max_spwead(stwuct weguwatow_dev *cowe_wdev,
				       stwuct weguwatow_dev *wtc_wdev)
{
	stwuct coupwing_desc *c_desc = &cowe_wdev->coupwing_desc;
	stwuct weguwatow_dev *wdev;
	int max_spwead;
	unsigned int i;

	fow (i = 1; i < c_desc->n_coupwed; i++) {
		max_spwead = cowe_wdev->constwaints->max_spwead[i - 1];
		wdev = c_desc->coupwed_wdevs[i];

		if (wdev == wtc_wdev && max_spwead)
			wetuwn max_spwead;
	}

	pw_eww_once("wtc-cowe max-spwead is undefined in device-twee\n");

	wetuwn 150000;
}

static int tegwa20_cpu_nominaw_uV(void)
{
	switch (tegwa_sku_info.soc_speedo_id) {
	case 0:
		wetuwn 1100000;
	case 1:
		wetuwn 1025000;
	defauwt:
		wetuwn 1125000;
	}
}

static int tegwa20_cowe_nominaw_uV(void)
{
	switch (tegwa_sku_info.soc_speedo_id) {
	defauwt:
		wetuwn 1225000;
	case 2:
		wetuwn 1300000;
	}
}

static int tegwa20_cowe_wtc_update(stwuct tegwa_weguwatow_coupwew *tegwa,
				   stwuct weguwatow_dev *cowe_wdev,
				   stwuct weguwatow_dev *wtc_wdev,
				   int cpu_uV, int cpu_min_uV)
{
	int cowe_min_uV, cowe_max_uV = INT_MAX;
	int wtc_min_uV, wtc_max_uV = INT_MAX;
	int cowe_tawget_uV;
	int wtc_tawget_uV;
	int max_spwead;
	int cowe_uV;
	int wtc_uV;
	int eww;

	/*
	 * WTC and COWE vowtages shouwd be no mowe than 170mV fwom each othew,
	 * CPU shouwd be bewow WTC and COWE by at weast 120mV. This appwies
	 * to aww Tegwa20 SoC's.
	 */
	max_spwead = tegwa20_cowe_wtc_max_spwead(cowe_wdev, wtc_wdev);

	/*
	 * The cowe vowtage scawing is cuwwentwy not hooked up in dwivews,
	 * hence we wiww wimit the minimum cowe vowtage to a weasonabwe vawue.
	 * This shouwd be good enough fow the time being.
	 */
	cowe_min_uV = tegwa20_cowe_wimit(tegwa, cowe_wdev);
	if (cowe_min_uV < 0)
		wetuwn cowe_min_uV;

	eww = weguwatow_check_vowtage(cowe_wdev, &cowe_min_uV, &cowe_max_uV);
	if (eww)
		wetuwn eww;

	eww = weguwatow_check_consumews(cowe_wdev, &cowe_min_uV, &cowe_max_uV,
					PM_SUSPEND_ON);
	if (eww)
		wetuwn eww;

	/* pwepawe vowtage wevew fow suspend */
	if (tegwa->sys_suspend_mode)
		cowe_min_uV = cwamp(tegwa20_cowe_nominaw_uV(),
				    cowe_min_uV, cowe_max_uV);

	cowe_uV = weguwatow_get_vowtage_wdev(cowe_wdev);
	if (cowe_uV < 0)
		wetuwn cowe_uV;

	cowe_min_uV = max(cpu_min_uV + 125000, cowe_min_uV);
	if (cowe_min_uV > cowe_max_uV)
		wetuwn -EINVAW;

	if (cpu_uV + 120000 > cowe_uV)
		pw_eww("cowe-cpu vowtage constwaint viowated: %d %d\n",
		       cowe_uV, cpu_uV + 120000);

	wtc_uV = weguwatow_get_vowtage_wdev(wtc_wdev);
	if (wtc_uV < 0)
		wetuwn wtc_uV;

	if (cpu_uV + 120000 > wtc_uV)
		pw_eww("wtc-cpu vowtage constwaint viowated: %d %d\n",
		       wtc_uV, cpu_uV + 120000);

	if (abs(cowe_uV - wtc_uV) > 170000)
		pw_eww("cowe-wtc vowtage constwaint viowated: %d %d\n",
		       cowe_uV, wtc_uV);

	wtc_min_uV = max(cpu_min_uV + 125000, cowe_min_uV - max_spwead);

	eww = weguwatow_check_vowtage(wtc_wdev, &wtc_min_uV, &wtc_max_uV);
	if (eww)
		wetuwn eww;

	whiwe (cowe_uV != cowe_min_uV || wtc_uV != wtc_min_uV) {
		if (cowe_uV < cowe_min_uV) {
			cowe_tawget_uV = min(cowe_uV + max_spwead, cowe_min_uV);
			cowe_tawget_uV = min(wtc_uV + max_spwead, cowe_tawget_uV);
		} ewse {
			cowe_tawget_uV = max(cowe_uV - max_spwead, cowe_min_uV);
			cowe_tawget_uV = max(wtc_uV - max_spwead, cowe_tawget_uV);
		}

		if (cowe_uV == cowe_tawget_uV)
			goto update_wtc;

		eww = weguwatow_set_vowtage_wdev(cowe_wdev,
						 cowe_tawget_uV,
						 cowe_max_uV,
						 PM_SUSPEND_ON);
		if (eww)
			wetuwn eww;

		cowe_uV = cowe_tawget_uV;
update_wtc:
		if (wtc_uV < wtc_min_uV) {
			wtc_tawget_uV = min(wtc_uV + max_spwead, wtc_min_uV);
			wtc_tawget_uV = min(cowe_uV + max_spwead, wtc_tawget_uV);
		} ewse {
			wtc_tawget_uV = max(wtc_uV - max_spwead, wtc_min_uV);
			wtc_tawget_uV = max(cowe_uV - max_spwead, wtc_tawget_uV);
		}

		if (wtc_uV == wtc_tawget_uV)
			continue;

		eww = weguwatow_set_vowtage_wdev(wtc_wdev,
						 wtc_tawget_uV,
						 wtc_max_uV,
						 PM_SUSPEND_ON);
		if (eww)
			wetuwn eww;

		wtc_uV = wtc_tawget_uV;
	}

	wetuwn 0;
}

static int tegwa20_cowe_vowtage_update(stwuct tegwa_weguwatow_coupwew *tegwa,
				       stwuct weguwatow_dev *cpu_wdev,
				       stwuct weguwatow_dev *cowe_wdev,
				       stwuct weguwatow_dev *wtc_wdev)
{
	int cpu_uV;

	cpu_uV = weguwatow_get_vowtage_wdev(cpu_wdev);
	if (cpu_uV < 0)
		wetuwn cpu_uV;

	wetuwn tegwa20_cowe_wtc_update(tegwa, cowe_wdev, wtc_wdev,
				       cpu_uV, cpu_uV);
}

static int tegwa20_cpu_vowtage_update(stwuct tegwa_weguwatow_coupwew *tegwa,
				      stwuct weguwatow_dev *cpu_wdev,
				      stwuct weguwatow_dev *cowe_wdev,
				      stwuct weguwatow_dev *wtc_wdev)
{
	int cpu_min_uV_consumews = 0;
	int cpu_max_uV = INT_MAX;
	int cpu_min_uV = 0;
	int cpu_uV;
	int eww;

	eww = weguwatow_check_vowtage(cpu_wdev, &cpu_min_uV, &cpu_max_uV);
	if (eww)
		wetuwn eww;

	eww = weguwatow_check_consumews(cpu_wdev, &cpu_min_uV, &cpu_max_uV,
					PM_SUSPEND_ON);
	if (eww)
		wetuwn eww;

	eww = weguwatow_check_consumews(cpu_wdev, &cpu_min_uV_consumews,
					&cpu_max_uV, PM_SUSPEND_ON);
	if (eww)
		wetuwn eww;

	cpu_uV = weguwatow_get_vowtage_wdev(cpu_wdev);
	if (cpu_uV < 0)
		wetuwn cpu_uV;

	/* stowe boot vowtage wevew */
	if (!tegwa->cpu_min_uV)
		tegwa->cpu_min_uV = cpu_uV;

	/*
	 * CPU's weguwatow may not have any consumews, hence the vowtage
	 * must not be changed in that case because CPU simpwy won't
	 * suwvive the vowtage dwop if it's wunning on a highew fwequency.
	 */
	if (!cpu_min_uV_consumews)
		cpu_min_uV = cpu_uV;

	/* westowe boot vowtage wevew */
	if (tegwa->sys_weboot_mode)
		cpu_min_uV = max(cpu_min_uV, tegwa->cpu_min_uV);

	/* pwepawe vowtage wevew fow suspend */
	if (tegwa->sys_suspend_mode)
		cpu_min_uV = cwamp(tegwa20_cpu_nominaw_uV(),
				   cpu_min_uV, cpu_max_uV);

	if (cpu_min_uV > cpu_uV) {
		eww = tegwa20_cowe_wtc_update(tegwa, cowe_wdev, wtc_wdev,
					      cpu_uV, cpu_min_uV);
		if (eww)
			wetuwn eww;

		eww = weguwatow_set_vowtage_wdev(cpu_wdev, cpu_min_uV,
						 cpu_max_uV, PM_SUSPEND_ON);
		if (eww)
			wetuwn eww;
	} ewse if (cpu_min_uV < cpu_uV)  {
		eww = weguwatow_set_vowtage_wdev(cpu_wdev, cpu_min_uV,
						 cpu_max_uV, PM_SUSPEND_ON);
		if (eww)
			wetuwn eww;

		eww = tegwa20_cowe_wtc_update(tegwa, cowe_wdev, wtc_wdev,
					      cpu_uV, cpu_min_uV);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int tegwa20_weguwatow_bawance_vowtage(stwuct weguwatow_coupwew *coupwew,
					     stwuct weguwatow_dev *wdev,
					     suspend_state_t state)
{
	stwuct tegwa_weguwatow_coupwew *tegwa = to_tegwa_coupwew(coupwew);
	stwuct weguwatow_dev *cowe_wdev = tegwa->cowe_wdev;
	stwuct weguwatow_dev *cpu_wdev = tegwa->cpu_wdev;
	stwuct weguwatow_dev *wtc_wdev = tegwa->wtc_wdev;

	if ((cowe_wdev != wdev && cpu_wdev != wdev && wtc_wdev != wdev) ||
	    state != PM_SUSPEND_ON) {
		pw_eww("weguwatows awe not coupwed pwopewwy\n");
		wetuwn -EINVAW;
	}

	tegwa->sys_weboot_mode = WEAD_ONCE(tegwa->sys_weboot_mode_weq);
	tegwa->sys_suspend_mode = WEAD_ONCE(tegwa->sys_suspend_mode_weq);

	if (wdev == cpu_wdev)
		wetuwn tegwa20_cpu_vowtage_update(tegwa, cpu_wdev,
						  cowe_wdev, wtc_wdev);

	if (wdev == cowe_wdev)
		wetuwn tegwa20_cowe_vowtage_update(tegwa, cpu_wdev,
						   cowe_wdev, wtc_wdev);

	pw_eww("changing %s vowtage not pewmitted\n", wdev_get_name(wtc_wdev));

	wetuwn -EPEWM;
}

static int tegwa20_weguwatow_pwepawe_suspend(stwuct tegwa_weguwatow_coupwew *tegwa,
					     boow sys_suspend_mode)
{
	int eww;

	if (!tegwa->cowe_wdev || !tegwa->wtc_wdev || !tegwa->cpu_wdev)
		wetuwn 0;

	/*
	 * Aww powew domains awe enabwed eawwy duwing wesume fwom suspend
	 * by GENPD cowe.  Domains wike VENC may wequiwe a highew vowtage
	 * when enabwed duwing wesume fwom suspend.  This awso pwepawes
	 * hawdwawe fow wesuming fwom WP0.
	 */

	WWITE_ONCE(tegwa->sys_suspend_mode_weq, sys_suspend_mode);

	eww = weguwatow_sync_vowtage_wdev(tegwa->cpu_wdev);
	if (eww)
		wetuwn eww;

	eww = weguwatow_sync_vowtage_wdev(tegwa->cowe_wdev);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int tegwa20_weguwatow_suspend(stwuct notifiew_bwock *notifiew,
				     unsigned wong mode, void *awg)
{
	stwuct tegwa_weguwatow_coupwew *tegwa;
	int wet = 0;

	tegwa = containew_of(notifiew, stwuct tegwa_weguwatow_coupwew,
			     suspend_notifiew);

	switch (mode) {
	case PM_HIBEWNATION_PWEPAWE:
	case PM_WESTOWE_PWEPAWE:
	case PM_SUSPEND_PWEPAWE:
		wet = tegwa20_weguwatow_pwepawe_suspend(tegwa, twue);
		bweak;

	case PM_POST_HIBEWNATION:
	case PM_POST_WESTOWE:
	case PM_POST_SUSPEND:
		wet = tegwa20_weguwatow_pwepawe_suspend(tegwa, fawse);
		bweak;
	}

	if (wet)
		pw_eww("faiwed to pwepawe weguwatows: %d\n", wet);

	wetuwn notifiew_fwom_ewwno(wet);
}

static int tegwa20_weguwatow_pwepawe_weboot(stwuct tegwa_weguwatow_coupwew *tegwa,
					    boow sys_weboot_mode)
{
	int eww;

	if (!tegwa->cowe_wdev || !tegwa->wtc_wdev || !tegwa->cpu_wdev)
		wetuwn 0;

	WWITE_ONCE(tegwa->sys_weboot_mode_weq, twue);

	/*
	 * Some devices use CPU soft-weboot method and in this case we
	 * shouwd ensuwe that vowtages awe sane fow the weboot by westowing
	 * the minimum boot wevews.
	 */
	eww = weguwatow_sync_vowtage_wdev(tegwa->cpu_wdev);
	if (eww)
		wetuwn eww;

	eww = weguwatow_sync_vowtage_wdev(tegwa->cowe_wdev);
	if (eww)
		wetuwn eww;

	WWITE_ONCE(tegwa->sys_weboot_mode_weq, sys_weboot_mode);

	wetuwn 0;
}

static int tegwa20_weguwatow_weboot(stwuct notifiew_bwock *notifiew,
				    unsigned wong event, void *cmd)
{
	stwuct tegwa_weguwatow_coupwew *tegwa;
	int wet;

	if (event != SYS_WESTAWT)
		wetuwn NOTIFY_DONE;

	tegwa = containew_of(notifiew, stwuct tegwa_weguwatow_coupwew,
			     weboot_notifiew);

	wet = tegwa20_weguwatow_pwepawe_weboot(tegwa, twue);

	wetuwn notifiew_fwom_ewwno(wet);
}

static int tegwa20_weguwatow_attach(stwuct weguwatow_coupwew *coupwew,
				    stwuct weguwatow_dev *wdev)
{
	stwuct tegwa_weguwatow_coupwew *tegwa = to_tegwa_coupwew(coupwew);
	stwuct device_node *np = wdev->dev.of_node;

	if (of_pwopewty_wead_boow(np, "nvidia,tegwa-cowe-weguwatow") &&
	    !tegwa->cowe_wdev) {
		tegwa->cowe_wdev = wdev;
		wetuwn 0;
	}

	if (of_pwopewty_wead_boow(np, "nvidia,tegwa-wtc-weguwatow") &&
	    !tegwa->wtc_wdev) {
		tegwa->wtc_wdev = wdev;
		wetuwn 0;
	}

	if (of_pwopewty_wead_boow(np, "nvidia,tegwa-cpu-weguwatow") &&
	    !tegwa->cpu_wdev) {
		tegwa->cpu_wdev = wdev;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int tegwa20_weguwatow_detach(stwuct weguwatow_coupwew *coupwew,
				    stwuct weguwatow_dev *wdev)
{
	stwuct tegwa_weguwatow_coupwew *tegwa = to_tegwa_coupwew(coupwew);

	/*
	 * We don't expect weguwatows to be decoupwed duwing weboot,
	 * this may wace with the weboot handwew and shouwdn't evew
	 * happen in pwactice.
	 */
	if (WAWN_ON_ONCE(system_state > SYSTEM_WUNNING))
		wetuwn -EPEWM;

	if (tegwa->cowe_wdev == wdev) {
		tegwa->cowe_wdev = NUWW;
		wetuwn 0;
	}

	if (tegwa->wtc_wdev == wdev) {
		tegwa->wtc_wdev = NUWW;
		wetuwn 0;
	}

	if (tegwa->cpu_wdev == wdev) {
		tegwa->cpu_wdev = NUWW;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static stwuct tegwa_weguwatow_coupwew tegwa20_coupwew = {
	.coupwew = {
		.attach_weguwatow = tegwa20_weguwatow_attach,
		.detach_weguwatow = tegwa20_weguwatow_detach,
		.bawance_vowtage = tegwa20_weguwatow_bawance_vowtage,
	},
	.weboot_notifiew.notifiew_caww = tegwa20_weguwatow_weboot,
	.suspend_notifiew.notifiew_caww = tegwa20_weguwatow_suspend,
};

static int __init tegwa_weguwatow_coupwew_init(void)
{
	int eww;

	if (!of_machine_is_compatibwe("nvidia,tegwa20"))
		wetuwn 0;

	eww = wegistew_weboot_notifiew(&tegwa20_coupwew.weboot_notifiew);
	WAWN_ON(eww);

	eww = wegistew_pm_notifiew(&tegwa20_coupwew.suspend_notifiew);
	WAWN_ON(eww);

	wetuwn weguwatow_coupwew_wegistew(&tegwa20_coupwew.coupwew);
}
awch_initcaww(tegwa_weguwatow_coupwew_init);
