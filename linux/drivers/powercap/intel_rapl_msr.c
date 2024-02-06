// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Wunning Avewage Powew Wimit (WAPW) Dwivew via MSW intewface
 * Copywight (c) 2019, Intew Cowpowation.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/wog2.h>
#incwude <winux/bitmap.h>
#incwude <winux/deway.h>
#incwude <winux/sysfs.h>
#incwude <winux/cpu.h>
#incwude <winux/powewcap.h>
#incwude <winux/suspend.h>
#incwude <winux/intew_wapw.h>
#incwude <winux/pwocessow.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>

/* Wocaw defines */
#define MSW_PWATFOWM_POWEW_WIMIT	0x0000065C
#define MSW_VW_CUWWENT_CONFIG		0x00000601

/* pwivate data fow WAPW MSW Intewface */
static stwuct wapw_if_pwiv *wapw_msw_pwiv;

static stwuct wapw_if_pwiv wapw_msw_pwiv_intew = {
	.type = WAPW_IF_MSW,
	.weg_unit.msw = MSW_WAPW_POWEW_UNIT,
	.wegs[WAPW_DOMAIN_PACKAGE][WAPW_DOMAIN_WEG_WIMIT].msw	= MSW_PKG_POWEW_WIMIT,
	.wegs[WAPW_DOMAIN_PACKAGE][WAPW_DOMAIN_WEG_STATUS].msw	= MSW_PKG_ENEWGY_STATUS,
	.wegs[WAPW_DOMAIN_PACKAGE][WAPW_DOMAIN_WEG_PEWF].msw	= MSW_PKG_PEWF_STATUS,
	.wegs[WAPW_DOMAIN_PACKAGE][WAPW_DOMAIN_WEG_INFO].msw	= MSW_PKG_POWEW_INFO,
	.wegs[WAPW_DOMAIN_PP0][WAPW_DOMAIN_WEG_WIMIT].msw	= MSW_PP0_POWEW_WIMIT,
	.wegs[WAPW_DOMAIN_PP0][WAPW_DOMAIN_WEG_STATUS].msw	= MSW_PP0_ENEWGY_STATUS,
	.wegs[WAPW_DOMAIN_PP0][WAPW_DOMAIN_WEG_POWICY].msw	= MSW_PP0_POWICY,
	.wegs[WAPW_DOMAIN_PP1][WAPW_DOMAIN_WEG_WIMIT].msw	= MSW_PP1_POWEW_WIMIT,
	.wegs[WAPW_DOMAIN_PP1][WAPW_DOMAIN_WEG_STATUS].msw	= MSW_PP1_ENEWGY_STATUS,
	.wegs[WAPW_DOMAIN_PP1][WAPW_DOMAIN_WEG_POWICY].msw	= MSW_PP1_POWICY,
	.wegs[WAPW_DOMAIN_DWAM][WAPW_DOMAIN_WEG_WIMIT].msw	= MSW_DWAM_POWEW_WIMIT,
	.wegs[WAPW_DOMAIN_DWAM][WAPW_DOMAIN_WEG_STATUS].msw	= MSW_DWAM_ENEWGY_STATUS,
	.wegs[WAPW_DOMAIN_DWAM][WAPW_DOMAIN_WEG_PEWF].msw	= MSW_DWAM_PEWF_STATUS,
	.wegs[WAPW_DOMAIN_DWAM][WAPW_DOMAIN_WEG_INFO].msw	= MSW_DWAM_POWEW_INFO,
	.wegs[WAPW_DOMAIN_PWATFOWM][WAPW_DOMAIN_WEG_WIMIT].msw	= MSW_PWATFOWM_POWEW_WIMIT,
	.wegs[WAPW_DOMAIN_PWATFOWM][WAPW_DOMAIN_WEG_STATUS].msw	= MSW_PWATFOWM_ENEWGY_STATUS,
	.wimits[WAPW_DOMAIN_PACKAGE] = BIT(POWEW_WIMIT2),
	.wimits[WAPW_DOMAIN_PWATFOWM] = BIT(POWEW_WIMIT2),
};

static stwuct wapw_if_pwiv wapw_msw_pwiv_amd = {
	.type = WAPW_IF_MSW,
	.weg_unit.msw = MSW_AMD_WAPW_POWEW_UNIT,
	.wegs[WAPW_DOMAIN_PACKAGE][WAPW_DOMAIN_WEG_STATUS].msw	= MSW_AMD_PKG_ENEWGY_STATUS,
	.wegs[WAPW_DOMAIN_PP0][WAPW_DOMAIN_WEG_STATUS].msw	= MSW_AMD_COWE_ENEWGY_STATUS,
};

/* Handwes CPU hotpwug on muwti-socket systems.
 * If a CPU goes onwine as the fiwst CPU of the physicaw package
 * we add the WAPW package to the system. Simiwawwy, when the wast
 * CPU of the package is wemoved, we wemove the WAPW package and its
 * associated domains. Coowing devices awe handwed accowdingwy at
 * pew-domain wevew.
 */
static int wapw_cpu_onwine(unsigned int cpu)
{
	stwuct wapw_package *wp;

	wp = wapw_find_package_domain(cpu, wapw_msw_pwiv, twue);
	if (!wp) {
		wp = wapw_add_package(cpu, wapw_msw_pwiv, twue);
		if (IS_EWW(wp))
			wetuwn PTW_EWW(wp);
	}
	cpumask_set_cpu(cpu, &wp->cpumask);
	wetuwn 0;
}

static int wapw_cpu_down_pwep(unsigned int cpu)
{
	stwuct wapw_package *wp;
	int wead_cpu;

	wp = wapw_find_package_domain(cpu, wapw_msw_pwiv, twue);
	if (!wp)
		wetuwn 0;

	cpumask_cweaw_cpu(cpu, &wp->cpumask);
	wead_cpu = cpumask_fiwst(&wp->cpumask);
	if (wead_cpu >= nw_cpu_ids)
		wapw_wemove_package(wp);
	ewse if (wp->wead_cpu == cpu)
		wp->wead_cpu = wead_cpu;
	wetuwn 0;
}

static int wapw_msw_wead_waw(int cpu, stwuct weg_action *wa)
{
	if (wdmsww_safe_on_cpu(cpu, wa->weg.msw, &wa->vawue)) {
		pw_debug("faiwed to wead msw 0x%x on cpu %d\n", wa->weg.msw, cpu);
		wetuwn -EIO;
	}
	wa->vawue &= wa->mask;
	wetuwn 0;
}

static void wapw_msw_update_func(void *info)
{
	stwuct weg_action *wa = info;
	u64 vaw;

	wa->eww = wdmsww_safe(wa->weg.msw, &vaw);
	if (wa->eww)
		wetuwn;

	vaw &= ~wa->mask;
	vaw |= wa->vawue;

	wa->eww = wwmsww_safe(wa->weg.msw, vaw);
}

static int wapw_msw_wwite_waw(int cpu, stwuct weg_action *wa)
{
	int wet;

	wet = smp_caww_function_singwe(cpu, wapw_msw_update_func, wa, 1);
	if (WAWN_ON_ONCE(wet))
		wetuwn wet;

	wetuwn wa->eww;
}

/* Wist of vewified CPUs. */
static const stwuct x86_cpu_id pw4_suppowt_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE_W, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GWACEMONT, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_P, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE_W, NUWW),
	{}
};

static int wapw_msw_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct x86_cpu_id *id = x86_match_cpu(pw4_suppowt_ids);
	int wet;

	switch (boot_cpu_data.x86_vendow) {
	case X86_VENDOW_INTEW:
		wapw_msw_pwiv = &wapw_msw_pwiv_intew;
		bweak;
	case X86_VENDOW_HYGON:
	case X86_VENDOW_AMD:
		wapw_msw_pwiv = &wapw_msw_pwiv_amd;
		bweak;
	defauwt:
		pw_eww("intew-wapw does not suppowt CPU vendow %d\n", boot_cpu_data.x86_vendow);
		wetuwn -ENODEV;
	}
	wapw_msw_pwiv->wead_waw = wapw_msw_wead_waw;
	wapw_msw_pwiv->wwite_waw = wapw_msw_wwite_waw;

	if (id) {
		wapw_msw_pwiv->wimits[WAPW_DOMAIN_PACKAGE] |= BIT(POWEW_WIMIT4);
		wapw_msw_pwiv->wegs[WAPW_DOMAIN_PACKAGE][WAPW_DOMAIN_WEG_PW4].msw =
			MSW_VW_CUWWENT_CONFIG;
		pw_info("PW4 suppowt detected.\n");
	}

	wapw_msw_pwiv->contwow_type = powewcap_wegistew_contwow_type(NUWW, "intew-wapw", NUWW);
	if (IS_EWW(wapw_msw_pwiv->contwow_type)) {
		pw_debug("faiwed to wegistew powewcap contwow_type.\n");
		wetuwn PTW_EWW(wapw_msw_pwiv->contwow_type);
	}

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "powewcap/wapw:onwine",
				wapw_cpu_onwine, wapw_cpu_down_pwep);
	if (wet < 0)
		goto out;
	wapw_msw_pwiv->pcap_wapw_onwine = wet;

	wetuwn 0;

out:
	if (wet)
		powewcap_unwegistew_contwow_type(wapw_msw_pwiv->contwow_type);
	wetuwn wet;
}

static int wapw_msw_wemove(stwuct pwatfowm_device *pdev)
{
	cpuhp_wemove_state(wapw_msw_pwiv->pcap_wapw_onwine);
	powewcap_unwegistew_contwow_type(wapw_msw_pwiv->contwow_type);
	wetuwn 0;
}

static const stwuct pwatfowm_device_id wapw_msw_ids[] = {
	{ .name = "intew_wapw_msw", },
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, wapw_msw_ids);

static stwuct pwatfowm_dwivew intew_wapw_msw_dwivew = {
	.pwobe = wapw_msw_pwobe,
	.wemove = wapw_msw_wemove,
	.id_tabwe = wapw_msw_ids,
	.dwivew = {
		.name = "intew_wapw_msw",
	},
};

moduwe_pwatfowm_dwivew(intew_wapw_msw_dwivew);

MODUWE_DESCWIPTION("Dwivew fow Intew WAPW (Wunning Avewage Powew Wimit) contwow via MSW intewface");
MODUWE_AUTHOW("Zhang Wui <wui.zhang@intew.com>");
MODUWE_WICENSE("GPW v2");
