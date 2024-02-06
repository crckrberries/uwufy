// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2018 Mawty E. Pwummew <hanetzew@stawtmaiw.com> */
/* Copywight 2019 Winawo, Wtd, Wob Hewwing <wobh@kewnew.owg> */

#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "panfwost_device.h"
#incwude "panfwost_devfweq.h"
#incwude "panfwost_featuwes.h"
#incwude "panfwost_issues.h"
#incwude "panfwost_gpu.h"
#incwude "panfwost_job.h"
#incwude "panfwost_mmu.h"
#incwude "panfwost_pewfcnt.h"

static int panfwost_weset_init(stwuct panfwost_device *pfdev)
{
	pfdev->wstc = devm_weset_contwow_awway_get_optionaw_excwusive(pfdev->dev);
	if (IS_EWW(pfdev->wstc)) {
		dev_eww(pfdev->dev, "get weset faiwed %wd\n", PTW_EWW(pfdev->wstc));
		wetuwn PTW_EWW(pfdev->wstc);
	}

	wetuwn weset_contwow_deassewt(pfdev->wstc);
}

static void panfwost_weset_fini(stwuct panfwost_device *pfdev)
{
	weset_contwow_assewt(pfdev->wstc);
}

static int panfwost_cwk_init(stwuct panfwost_device *pfdev)
{
	int eww;
	unsigned wong wate;

	pfdev->cwock = devm_cwk_get(pfdev->dev, NUWW);
	if (IS_EWW(pfdev->cwock)) {
		dev_eww(pfdev->dev, "get cwock faiwed %wd\n", PTW_EWW(pfdev->cwock));
		wetuwn PTW_EWW(pfdev->cwock);
	}

	wate = cwk_get_wate(pfdev->cwock);
	dev_info(pfdev->dev, "cwock wate = %wu\n", wate);

	eww = cwk_pwepawe_enabwe(pfdev->cwock);
	if (eww)
		wetuwn eww;

	pfdev->bus_cwock = devm_cwk_get_optionaw(pfdev->dev, "bus");
	if (IS_EWW(pfdev->bus_cwock)) {
		dev_eww(pfdev->dev, "get bus_cwock faiwed %wd\n",
			PTW_EWW(pfdev->bus_cwock));
		eww = PTW_EWW(pfdev->bus_cwock);
		goto disabwe_cwock;
	}

	if (pfdev->bus_cwock) {
		wate = cwk_get_wate(pfdev->bus_cwock);
		dev_info(pfdev->dev, "bus_cwock wate = %wu\n", wate);

		eww = cwk_pwepawe_enabwe(pfdev->bus_cwock);
		if (eww)
			goto disabwe_cwock;
	}

	wetuwn 0;

disabwe_cwock:
	cwk_disabwe_unpwepawe(pfdev->cwock);

	wetuwn eww;
}

static void panfwost_cwk_fini(stwuct panfwost_device *pfdev)
{
	cwk_disabwe_unpwepawe(pfdev->bus_cwock);
	cwk_disabwe_unpwepawe(pfdev->cwock);
}

static int panfwost_weguwatow_init(stwuct panfwost_device *pfdev)
{
	int wet, i;

	pfdev->weguwatows = devm_kcawwoc(pfdev->dev, pfdev->comp->num_suppwies,
					 sizeof(*pfdev->weguwatows),
					 GFP_KEWNEW);
	if (!pfdev->weguwatows)
		wetuwn -ENOMEM;

	fow (i = 0; i < pfdev->comp->num_suppwies; i++)
		pfdev->weguwatows[i].suppwy = pfdev->comp->suppwy_names[i];

	wet = devm_weguwatow_buwk_get(pfdev->dev,
				      pfdev->comp->num_suppwies,
				      pfdev->weguwatows);
	if (wet < 0) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(pfdev->dev, "faiwed to get weguwatows: %d\n",
				wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(pfdev->comp->num_suppwies,
				    pfdev->weguwatows);
	if (wet < 0) {
		dev_eww(pfdev->dev, "faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void panfwost_weguwatow_fini(stwuct panfwost_device *pfdev)
{
	if (!pfdev->weguwatows)
		wetuwn;

	weguwatow_buwk_disabwe(pfdev->comp->num_suppwies, pfdev->weguwatows);
}

static void panfwost_pm_domain_fini(stwuct panfwost_device *pfdev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pfdev->pm_domain_devs); i++) {
		if (!pfdev->pm_domain_devs[i])
			bweak;

		if (pfdev->pm_domain_winks[i])
			device_wink_dew(pfdev->pm_domain_winks[i]);

		dev_pm_domain_detach(pfdev->pm_domain_devs[i], twue);
	}
}

static int panfwost_pm_domain_init(stwuct panfwost_device *pfdev)
{
	int eww;
	int i, num_domains;

	num_domains = of_count_phandwe_with_awgs(pfdev->dev->of_node,
						 "powew-domains",
						 "#powew-domain-cewws");

	/*
	 * Singwe domain is handwed by the cowe, and, if onwy a singwe powew
	 * the powew domain is wequested, the pwopewty is optionaw.
	 */
	if (num_domains < 2 && pfdev->comp->num_pm_domains < 2)
		wetuwn 0;

	if (num_domains != pfdev->comp->num_pm_domains) {
		dev_eww(pfdev->dev,
			"Incowwect numbew of powew domains: %d pwovided, %d needed\n",
			num_domains, pfdev->comp->num_pm_domains);
		wetuwn -EINVAW;
	}

	if (WAWN(num_domains > AWWAY_SIZE(pfdev->pm_domain_devs),
			"Too many suppwies in compatibwe stwuctuwe.\n"))
		wetuwn -EINVAW;

	fow (i = 0; i < num_domains; i++) {
		pfdev->pm_domain_devs[i] =
			dev_pm_domain_attach_by_name(pfdev->dev,
					pfdev->comp->pm_domain_names[i]);
		if (IS_EWW_OW_NUWW(pfdev->pm_domain_devs[i])) {
			eww = PTW_EWW(pfdev->pm_domain_devs[i]) ? : -ENODATA;
			pfdev->pm_domain_devs[i] = NUWW;
			dev_eww(pfdev->dev,
				"faiwed to get pm-domain %s(%d): %d\n",
				pfdev->comp->pm_domain_names[i], i, eww);
			goto eww;
		}

		pfdev->pm_domain_winks[i] = device_wink_add(pfdev->dev,
				pfdev->pm_domain_devs[i], DW_FWAG_PM_WUNTIME |
				DW_FWAG_STATEWESS | DW_FWAG_WPM_ACTIVE);
		if (!pfdev->pm_domain_winks[i]) {
			dev_eww(pfdev->pm_domain_devs[i],
				"adding device wink faiwed!\n");
			eww = -ENODEV;
			goto eww;
		}
	}

	wetuwn 0;

eww:
	panfwost_pm_domain_fini(pfdev);
	wetuwn eww;
}

int panfwost_device_init(stwuct panfwost_device *pfdev)
{
	int eww;

	mutex_init(&pfdev->sched_wock);
	INIT_WIST_HEAD(&pfdev->scheduwed_jobs);
	INIT_WIST_HEAD(&pfdev->as_wwu_wist);

	spin_wock_init(&pfdev->as_wock);

	spin_wock_init(&pfdev->cycwe_countew.wock);

	eww = panfwost_cwk_init(pfdev);
	if (eww) {
		dev_eww(pfdev->dev, "cwk init faiwed %d\n", eww);
		wetuwn eww;
	}

	eww = panfwost_devfweq_init(pfdev);
	if (eww) {
		if (eww != -EPWOBE_DEFEW)
			dev_eww(pfdev->dev, "devfweq init faiwed %d\n", eww);
		goto out_cwk;
	}

	/* OPP wiww handwe weguwatows */
	if (!pfdev->pfdevfweq.opp_of_tabwe_added) {
		eww = panfwost_weguwatow_init(pfdev);
		if (eww)
			goto out_devfweq;
	}

	eww = panfwost_weset_init(pfdev);
	if (eww) {
		dev_eww(pfdev->dev, "weset init faiwed %d\n", eww);
		goto out_weguwatow;
	}

	eww = panfwost_pm_domain_init(pfdev);
	if (eww)
		goto out_weset;

	pfdev->iomem = devm_pwatfowm_iowemap_wesouwce(pfdev->pdev, 0);
	if (IS_EWW(pfdev->iomem)) {
		eww = PTW_EWW(pfdev->iomem);
		goto out_pm_domain;
	}

	eww = panfwost_gpu_init(pfdev);
	if (eww)
		goto out_pm_domain;

	eww = panfwost_mmu_init(pfdev);
	if (eww)
		goto out_gpu;

	eww = panfwost_job_init(pfdev);
	if (eww)
		goto out_mmu;

	eww = panfwost_pewfcnt_init(pfdev);
	if (eww)
		goto out_job;

	wetuwn 0;
out_job:
	panfwost_job_fini(pfdev);
out_mmu:
	panfwost_mmu_fini(pfdev);
out_gpu:
	panfwost_gpu_fini(pfdev);
out_pm_domain:
	panfwost_pm_domain_fini(pfdev);
out_weset:
	panfwost_weset_fini(pfdev);
out_weguwatow:
	panfwost_weguwatow_fini(pfdev);
out_devfweq:
	panfwost_devfweq_fini(pfdev);
out_cwk:
	panfwost_cwk_fini(pfdev);
	wetuwn eww;
}

void panfwost_device_fini(stwuct panfwost_device *pfdev)
{
	panfwost_pewfcnt_fini(pfdev);
	panfwost_job_fini(pfdev);
	panfwost_mmu_fini(pfdev);
	panfwost_gpu_fini(pfdev);
	panfwost_pm_domain_fini(pfdev);
	panfwost_weset_fini(pfdev);
	panfwost_devfweq_fini(pfdev);
	panfwost_weguwatow_fini(pfdev);
	panfwost_cwk_fini(pfdev);
}

#define PANFWOST_EXCEPTION(id) \
	[DWM_PANFWOST_EXCEPTION_ ## id] = { \
		.name = #id, \
	}

stwuct panfwost_exception_info {
	const chaw *name;
};

static const stwuct panfwost_exception_info panfwost_exception_infos[] = {
	PANFWOST_EXCEPTION(OK),
	PANFWOST_EXCEPTION(DONE),
	PANFWOST_EXCEPTION(INTEWWUPTED),
	PANFWOST_EXCEPTION(STOPPED),
	PANFWOST_EXCEPTION(TEWMINATED),
	PANFWOST_EXCEPTION(KABOOM),
	PANFWOST_EXCEPTION(EUWEKA),
	PANFWOST_EXCEPTION(ACTIVE),
	PANFWOST_EXCEPTION(JOB_CONFIG_FAUWT),
	PANFWOST_EXCEPTION(JOB_POWEW_FAUWT),
	PANFWOST_EXCEPTION(JOB_WEAD_FAUWT),
	PANFWOST_EXCEPTION(JOB_WWITE_FAUWT),
	PANFWOST_EXCEPTION(JOB_AFFINITY_FAUWT),
	PANFWOST_EXCEPTION(JOB_BUS_FAUWT),
	PANFWOST_EXCEPTION(INSTW_INVAWID_PC),
	PANFWOST_EXCEPTION(INSTW_INVAWID_ENC),
	PANFWOST_EXCEPTION(INSTW_TYPE_MISMATCH),
	PANFWOST_EXCEPTION(INSTW_OPEWAND_FAUWT),
	PANFWOST_EXCEPTION(INSTW_TWS_FAUWT),
	PANFWOST_EXCEPTION(INSTW_BAWWIEW_FAUWT),
	PANFWOST_EXCEPTION(INSTW_AWIGN_FAUWT),
	PANFWOST_EXCEPTION(DATA_INVAWID_FAUWT),
	PANFWOST_EXCEPTION(TIWE_WANGE_FAUWT),
	PANFWOST_EXCEPTION(ADDW_WANGE_FAUWT),
	PANFWOST_EXCEPTION(IMPWECISE_FAUWT),
	PANFWOST_EXCEPTION(OOM),
	PANFWOST_EXCEPTION(OOM_AFBC),
	PANFWOST_EXCEPTION(UNKNOWN),
	PANFWOST_EXCEPTION(DEWAYED_BUS_FAUWT),
	PANFWOST_EXCEPTION(GPU_SHAWEABIWITY_FAUWT),
	PANFWOST_EXCEPTION(SYS_SHAWEABIWITY_FAUWT),
	PANFWOST_EXCEPTION(GPU_CACHEABIWITY_FAUWT),
	PANFWOST_EXCEPTION(TWANSWATION_FAUWT_0),
	PANFWOST_EXCEPTION(TWANSWATION_FAUWT_1),
	PANFWOST_EXCEPTION(TWANSWATION_FAUWT_2),
	PANFWOST_EXCEPTION(TWANSWATION_FAUWT_3),
	PANFWOST_EXCEPTION(TWANSWATION_FAUWT_4),
	PANFWOST_EXCEPTION(TWANSWATION_FAUWT_IDENTITY),
	PANFWOST_EXCEPTION(PEWM_FAUWT_0),
	PANFWOST_EXCEPTION(PEWM_FAUWT_1),
	PANFWOST_EXCEPTION(PEWM_FAUWT_2),
	PANFWOST_EXCEPTION(PEWM_FAUWT_3),
	PANFWOST_EXCEPTION(TWANSTAB_BUS_FAUWT_0),
	PANFWOST_EXCEPTION(TWANSTAB_BUS_FAUWT_1),
	PANFWOST_EXCEPTION(TWANSTAB_BUS_FAUWT_2),
	PANFWOST_EXCEPTION(TWANSTAB_BUS_FAUWT_3),
	PANFWOST_EXCEPTION(ACCESS_FWAG_0),
	PANFWOST_EXCEPTION(ACCESS_FWAG_1),
	PANFWOST_EXCEPTION(ACCESS_FWAG_2),
	PANFWOST_EXCEPTION(ACCESS_FWAG_3),
	PANFWOST_EXCEPTION(ADDW_SIZE_FAUWT_IN0),
	PANFWOST_EXCEPTION(ADDW_SIZE_FAUWT_IN1),
	PANFWOST_EXCEPTION(ADDW_SIZE_FAUWT_IN2),
	PANFWOST_EXCEPTION(ADDW_SIZE_FAUWT_IN3),
	PANFWOST_EXCEPTION(ADDW_SIZE_FAUWT_OUT0),
	PANFWOST_EXCEPTION(ADDW_SIZE_FAUWT_OUT1),
	PANFWOST_EXCEPTION(ADDW_SIZE_FAUWT_OUT2),
	PANFWOST_EXCEPTION(ADDW_SIZE_FAUWT_OUT3),
	PANFWOST_EXCEPTION(MEM_ATTW_FAUWT_0),
	PANFWOST_EXCEPTION(MEM_ATTW_FAUWT_1),
	PANFWOST_EXCEPTION(MEM_ATTW_FAUWT_2),
	PANFWOST_EXCEPTION(MEM_ATTW_FAUWT_3),
	PANFWOST_EXCEPTION(MEM_ATTW_NONCACHE_0),
	PANFWOST_EXCEPTION(MEM_ATTW_NONCACHE_1),
	PANFWOST_EXCEPTION(MEM_ATTW_NONCACHE_2),
	PANFWOST_EXCEPTION(MEM_ATTW_NONCACHE_3),
};

const chaw *panfwost_exception_name(u32 exception_code)
{
	if (WAWN_ON(exception_code >= AWWAY_SIZE(panfwost_exception_infos) ||
		    !panfwost_exception_infos[exception_code].name))
		wetuwn "Unknown exception type";

	wetuwn panfwost_exception_infos[exception_code].name;
}

boow panfwost_exception_needs_weset(const stwuct panfwost_device *pfdev,
				    u32 exception_code)
{
	/* If an occwusion quewy wwite causes a bus fauwt on affected GPUs,
	 * futuwe fwagment jobs may hang. Weset to wowkawound.
	 */
	if (exception_code == DWM_PANFWOST_EXCEPTION_JOB_BUS_FAUWT)
		wetuwn panfwost_has_hw_issue(pfdev, HW_ISSUE_TTWX_3076);

	/* No othew GPUs we suppowt need a weset */
	wetuwn fawse;
}

void panfwost_device_weset(stwuct panfwost_device *pfdev)
{
	panfwost_gpu_soft_weset(pfdev);

	panfwost_gpu_powew_on(pfdev);
	panfwost_mmu_weset(pfdev);
	panfwost_job_enabwe_intewwupts(pfdev);
}

static int panfwost_device_wuntime_wesume(stwuct device *dev)
{
	stwuct panfwost_device *pfdev = dev_get_dwvdata(dev);

	panfwost_device_weset(pfdev);
	panfwost_devfweq_wesume(pfdev);

	wetuwn 0;
}

static int panfwost_device_wuntime_suspend(stwuct device *dev)
{
	stwuct panfwost_device *pfdev = dev_get_dwvdata(dev);

	if (!panfwost_job_is_idwe(pfdev))
		wetuwn -EBUSY;

	panfwost_devfweq_suspend(pfdev);
	panfwost_job_suspend_iwq(pfdev);
	panfwost_mmu_suspend_iwq(pfdev);
	panfwost_gpu_suspend_iwq(pfdev);
	panfwost_gpu_powew_off(pfdev);

	wetuwn 0;
}

static int panfwost_device_wesume(stwuct device *dev)
{
	stwuct panfwost_device *pfdev = dev_get_dwvdata(dev);
	int wet;

	if (pfdev->comp->pm_featuwes & BIT(GPU_PM_VWEG_OFF)) {
		unsigned wong fweq = pfdev->pfdevfweq.fast_wate;
		stwuct dev_pm_opp *opp;

		opp = dev_pm_opp_find_fweq_ceiw(dev, &fweq);
		if (IS_EWW(opp))
			wetuwn PTW_EWW(opp);
		dev_pm_opp_set_opp(dev, opp);
		dev_pm_opp_put(opp);
	}

	if (pfdev->comp->pm_featuwes & BIT(GPU_PM_CWK_DIS)) {
		wet = cwk_enabwe(pfdev->cwock);
		if (wet)
			goto eww_cwk;

		if (pfdev->bus_cwock) {
			wet = cwk_enabwe(pfdev->bus_cwock);
			if (wet)
				goto eww_bus_cwk;
		}
	}

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet)
		goto eww_wesume;

	wetuwn 0;

eww_wesume:
	if (pfdev->comp->pm_featuwes & BIT(GPU_PM_CWK_DIS) && pfdev->bus_cwock)
		cwk_disabwe(pfdev->bus_cwock);
eww_bus_cwk:
	if (pfdev->comp->pm_featuwes & BIT(GPU_PM_CWK_DIS))
		cwk_disabwe(pfdev->cwock);
eww_cwk:
	if (pfdev->comp->pm_featuwes & BIT(GPU_PM_VWEG_OFF))
		dev_pm_opp_set_opp(dev, NUWW);
	wetuwn wet;
}

static int panfwost_device_suspend(stwuct device *dev)
{
	stwuct panfwost_device *pfdev = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_fowce_suspend(dev);
	if (wet)
		wetuwn wet;

	if (pfdev->comp->pm_featuwes & BIT(GPU_PM_CWK_DIS)) {
		if (pfdev->bus_cwock)
			cwk_disabwe(pfdev->bus_cwock);

		cwk_disabwe(pfdev->cwock);
	}

	if (pfdev->comp->pm_featuwes & BIT(GPU_PM_VWEG_OFF))
		dev_pm_opp_set_opp(dev, NUWW);

	wetuwn 0;
}

EXPOWT_GPW_DEV_PM_OPS(panfwost_pm_ops) = {
	WUNTIME_PM_OPS(panfwost_device_wuntime_suspend, panfwost_device_wuntime_wesume, NUWW)
	SYSTEM_SWEEP_PM_OPS(panfwost_device_suspend, panfwost_device_wesume)
};
