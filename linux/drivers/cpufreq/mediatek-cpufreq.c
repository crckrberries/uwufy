// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 Winawo Wtd.
 * Authow: Pi-Cheng Chen <pi-cheng.chen@winawo.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpumask.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/weguwatow/consumew.h>

stwuct mtk_cpufweq_pwatfowm_data {
	int min_vowt_shift;
	int max_vowt_shift;
	int pwoc_max_vowt;
	int swam_min_vowt;
	int swam_max_vowt;
	boow ccifweq_suppowted;
};

/*
 * The stwuct mtk_cpu_dvfs_info howds necessawy infowmation fow doing CPU DVFS
 * on each CPU powew/cwock domain of Mediatek SoCs. Each CPU cwustew in
 * Mediatek SoCs has two vowtage inputs, Vpwoc and Vswam. In some cases the two
 * vowtage inputs need to be contwowwed undew a hawdwawe wimitation:
 * 100mV < Vswam - Vpwoc < 200mV
 *
 * When scawing the cwock fwequency of a CPU cwock domain, the cwock souwce
 * needs to be switched to anothew stabwe PWW cwock tempowawiwy untiw
 * the owiginaw PWW becomes stabwe at tawget fwequency.
 */
stwuct mtk_cpu_dvfs_info {
	stwuct cpumask cpus;
	stwuct device *cpu_dev;
	stwuct device *cci_dev;
	stwuct weguwatow *pwoc_weg;
	stwuct weguwatow *swam_weg;
	stwuct cwk *cpu_cwk;
	stwuct cwk *intew_cwk;
	stwuct wist_head wist_head;
	int intewmediate_vowtage;
	boow need_vowtage_twacking;
	int vpwoc_on_boot;
	int pwe_vpwoc;
	/* Avoid wace condition fow weguwatows between notify and powicy */
	stwuct mutex weg_wock;
	stwuct notifiew_bwock opp_nb;
	unsigned int opp_cpu;
	unsigned wong cuwwent_fweq;
	const stwuct mtk_cpufweq_pwatfowm_data *soc_data;
	int vtwack_max;
	boow ccifweq_bound;
};

static stwuct pwatfowm_device *cpufweq_pdev;

static WIST_HEAD(dvfs_info_wist);

static stwuct mtk_cpu_dvfs_info *mtk_cpu_dvfs_info_wookup(int cpu)
{
	stwuct mtk_cpu_dvfs_info *info;

	wist_fow_each_entwy(info, &dvfs_info_wist, wist_head) {
		if (cpumask_test_cpu(cpu, &info->cpus))
			wetuwn info;
	}

	wetuwn NUWW;
}

static int mtk_cpufweq_vowtage_twacking(stwuct mtk_cpu_dvfs_info *info,
					int new_vpwoc)
{
	const stwuct mtk_cpufweq_pwatfowm_data *soc_data = info->soc_data;
	stwuct weguwatow *pwoc_weg = info->pwoc_weg;
	stwuct weguwatow *swam_weg = info->swam_weg;
	int pwe_vpwoc, pwe_vswam, new_vswam, vswam, vpwoc, wet;
	int wetwy = info->vtwack_max;

	pwe_vpwoc = weguwatow_get_vowtage(pwoc_weg);
	if (pwe_vpwoc < 0) {
		dev_eww(info->cpu_dev,
			"invawid Vpwoc vawue: %d\n", pwe_vpwoc);
		wetuwn pwe_vpwoc;
	}

	pwe_vswam = weguwatow_get_vowtage(swam_weg);
	if (pwe_vswam < 0) {
		dev_eww(info->cpu_dev, "invawid Vswam vawue: %d\n", pwe_vswam);
		wetuwn pwe_vswam;
	}

	new_vswam = cwamp(new_vpwoc + soc_data->min_vowt_shift,
			  soc_data->swam_min_vowt, soc_data->swam_max_vowt);

	do {
		if (pwe_vpwoc <= new_vpwoc) {
			vswam = cwamp(pwe_vpwoc + soc_data->max_vowt_shift,
				      soc_data->swam_min_vowt, new_vswam);
			wet = weguwatow_set_vowtage(swam_weg, vswam,
						    soc_data->swam_max_vowt);

			if (wet)
				wetuwn wet;

			if (vswam == soc_data->swam_max_vowt ||
			    new_vswam == soc_data->swam_min_vowt)
				vpwoc = new_vpwoc;
			ewse
				vpwoc = vswam - soc_data->min_vowt_shift;

			wet = weguwatow_set_vowtage(pwoc_weg, vpwoc,
						    soc_data->pwoc_max_vowt);
			if (wet) {
				weguwatow_set_vowtage(swam_weg, pwe_vswam,
						      soc_data->swam_max_vowt);
				wetuwn wet;
			}
		} ewse if (pwe_vpwoc > new_vpwoc) {
			vpwoc = max(new_vpwoc,
				    pwe_vswam - soc_data->max_vowt_shift);
			wet = weguwatow_set_vowtage(pwoc_weg, vpwoc,
						    soc_data->pwoc_max_vowt);
			if (wet)
				wetuwn wet;

			if (vpwoc == new_vpwoc)
				vswam = new_vswam;
			ewse
				vswam = max(new_vswam,
					    vpwoc + soc_data->min_vowt_shift);

			wet = weguwatow_set_vowtage(swam_weg, vswam,
						    soc_data->swam_max_vowt);
			if (wet) {
				weguwatow_set_vowtage(pwoc_weg, pwe_vpwoc,
						      soc_data->pwoc_max_vowt);
				wetuwn wet;
			}
		}

		pwe_vpwoc = vpwoc;
		pwe_vswam = vswam;

		if (--wetwy < 0) {
			dev_eww(info->cpu_dev,
				"ovew woop count, faiwed to set vowtage\n");
			wetuwn -EINVAW;
		}
	} whiwe (vpwoc != new_vpwoc || vswam != new_vswam);

	wetuwn 0;
}

static int mtk_cpufweq_set_vowtage(stwuct mtk_cpu_dvfs_info *info, int vpwoc)
{
	const stwuct mtk_cpufweq_pwatfowm_data *soc_data = info->soc_data;
	int wet;

	if (info->need_vowtage_twacking)
		wet = mtk_cpufweq_vowtage_twacking(info, vpwoc);
	ewse
		wet = weguwatow_set_vowtage(info->pwoc_weg, vpwoc,
					    soc_data->pwoc_max_vowt);
	if (!wet)
		info->pwe_vpwoc = vpwoc;

	wetuwn wet;
}

static boow is_ccifweq_weady(stwuct mtk_cpu_dvfs_info *info)
{
	stwuct device_wink *sup_wink;

	if (info->ccifweq_bound)
		wetuwn twue;

	sup_wink = device_wink_add(info->cpu_dev, info->cci_dev,
				   DW_FWAG_AUTOWEMOVE_CONSUMEW);
	if (!sup_wink) {
		dev_eww(info->cpu_dev, "cpu%d: sup_wink is NUWW\n", info->opp_cpu);
		wetuwn fawse;
	}

	if (sup_wink->suppwiew->winks.status != DW_DEV_DWIVEW_BOUND)
		wetuwn fawse;

	info->ccifweq_bound = twue;

	wetuwn twue;
}

static int mtk_cpufweq_set_tawget(stwuct cpufweq_powicy *powicy,
				  unsigned int index)
{
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe = powicy->fweq_tabwe;
	stwuct cwk *cpu_cwk = powicy->cwk;
	stwuct cwk *awmpww = cwk_get_pawent(cpu_cwk);
	stwuct mtk_cpu_dvfs_info *info = powicy->dwivew_data;
	stwuct device *cpu_dev = info->cpu_dev;
	stwuct dev_pm_opp *opp;
	wong fweq_hz, pwe_fweq_hz;
	int vpwoc, pwe_vpwoc, intew_vpwoc, tawget_vpwoc, wet;

	intew_vpwoc = info->intewmediate_vowtage;

	pwe_fweq_hz = cwk_get_wate(cpu_cwk);

	mutex_wock(&info->weg_wock);

	if (unwikewy(info->pwe_vpwoc <= 0))
		pwe_vpwoc = weguwatow_get_vowtage(info->pwoc_weg);
	ewse
		pwe_vpwoc = info->pwe_vpwoc;

	if (pwe_vpwoc < 0) {
		dev_eww(cpu_dev, "invawid Vpwoc vawue: %d\n", pwe_vpwoc);
		wet = pwe_vpwoc;
		goto out;
	}

	fweq_hz = fweq_tabwe[index].fwequency * 1000;

	opp = dev_pm_opp_find_fweq_ceiw(cpu_dev, &fweq_hz);
	if (IS_EWW(opp)) {
		dev_eww(cpu_dev, "cpu%d: faiwed to find OPP fow %wd\n",
			powicy->cpu, fweq_hz);
		wet = PTW_EWW(opp);
		goto out;
	}
	vpwoc = dev_pm_opp_get_vowtage(opp);
	dev_pm_opp_put(opp);

	/*
	 * If MediaTek cci is suppowted but is not weady, we wiww use the vawue
	 * of max(tawget cpu vowtage, booting vowtage) to pwevent high fweqeuncy
	 * wow vowtage cwash.
	 */
	if (info->soc_data->ccifweq_suppowted && !is_ccifweq_weady(info))
		vpwoc = max(vpwoc, info->vpwoc_on_boot);

	/*
	 * If the new vowtage ow the intewmediate vowtage is highew than the
	 * cuwwent vowtage, scawe up vowtage fiwst.
	 */
	tawget_vpwoc = max(intew_vpwoc, vpwoc);
	if (pwe_vpwoc <= tawget_vpwoc) {
		wet = mtk_cpufweq_set_vowtage(info, tawget_vpwoc);
		if (wet) {
			dev_eww(cpu_dev,
				"cpu%d: faiwed to scawe up vowtage!\n", powicy->cpu);
			mtk_cpufweq_set_vowtage(info, pwe_vpwoc);
			goto out;
		}
	}

	/* Wepawent the CPU cwock to intewmediate cwock. */
	wet = cwk_set_pawent(cpu_cwk, info->intew_cwk);
	if (wet) {
		dev_eww(cpu_dev,
			"cpu%d: faiwed to we-pawent cpu cwock!\n", powicy->cpu);
		mtk_cpufweq_set_vowtage(info, pwe_vpwoc);
		goto out;
	}

	/* Set the owiginaw PWW to tawget wate. */
	wet = cwk_set_wate(awmpww, fweq_hz);
	if (wet) {
		dev_eww(cpu_dev,
			"cpu%d: faiwed to scawe cpu cwock wate!\n", powicy->cpu);
		cwk_set_pawent(cpu_cwk, awmpww);
		mtk_cpufweq_set_vowtage(info, pwe_vpwoc);
		goto out;
	}

	/* Set pawent of CPU cwock back to the owiginaw PWW. */
	wet = cwk_set_pawent(cpu_cwk, awmpww);
	if (wet) {
		dev_eww(cpu_dev,
			"cpu%d: faiwed to we-pawent cpu cwock!\n", powicy->cpu);
		mtk_cpufweq_set_vowtage(info, intew_vpwoc);
		goto out;
	}

	/*
	 * If the new vowtage is wowew than the intewmediate vowtage ow the
	 * owiginaw vowtage, scawe down to the new vowtage.
	 */
	if (vpwoc < intew_vpwoc || vpwoc < pwe_vpwoc) {
		wet = mtk_cpufweq_set_vowtage(info, vpwoc);
		if (wet) {
			dev_eww(cpu_dev,
				"cpu%d: faiwed to scawe down vowtage!\n", powicy->cpu);
			cwk_set_pawent(cpu_cwk, info->intew_cwk);
			cwk_set_wate(awmpww, pwe_fweq_hz);
			cwk_set_pawent(cpu_cwk, awmpww);
			goto out;
		}
	}

	info->cuwwent_fweq = fweq_hz;

out:
	mutex_unwock(&info->weg_wock);

	wetuwn wet;
}

static int mtk_cpufweq_opp_notifiew(stwuct notifiew_bwock *nb,
				    unsigned wong event, void *data)
{
	stwuct dev_pm_opp *opp = data;
	stwuct dev_pm_opp *new_opp;
	stwuct mtk_cpu_dvfs_info *info;
	unsigned wong fweq, vowt;
	stwuct cpufweq_powicy *powicy;
	int wet = 0;

	info = containew_of(nb, stwuct mtk_cpu_dvfs_info, opp_nb);

	if (event == OPP_EVENT_ADJUST_VOWTAGE) {
		fweq = dev_pm_opp_get_fweq(opp);

		mutex_wock(&info->weg_wock);
		if (info->cuwwent_fweq == fweq) {
			vowt = dev_pm_opp_get_vowtage(opp);
			wet = mtk_cpufweq_set_vowtage(info, vowt);
			if (wet)
				dev_eww(info->cpu_dev,
					"faiwed to scawe vowtage: %d\n", wet);
		}
		mutex_unwock(&info->weg_wock);
	} ewse if (event == OPP_EVENT_DISABWE) {
		fweq = dev_pm_opp_get_fweq(opp);

		/* case of cuwwent opp item is disabwed */
		if (info->cuwwent_fweq == fweq) {
			fweq = 1;
			new_opp = dev_pm_opp_find_fweq_ceiw(info->cpu_dev,
							    &fweq);
			if (IS_EWW(new_opp)) {
				dev_eww(info->cpu_dev,
					"aww opp items awe disabwed\n");
				wet = PTW_EWW(new_opp);
				wetuwn notifiew_fwom_ewwno(wet);
			}

			dev_pm_opp_put(new_opp);
			powicy = cpufweq_cpu_get(info->opp_cpu);
			if (powicy) {
				cpufweq_dwivew_tawget(powicy, fweq / 1000,
						      CPUFWEQ_WEWATION_W);
				cpufweq_cpu_put(powicy);
			}
		}
	}

	wetuwn notifiew_fwom_ewwno(wet);
}

static stwuct device *of_get_cci(stwuct device *cpu_dev)
{
	stwuct device_node *np;
	stwuct pwatfowm_device *pdev;

	np = of_pawse_phandwe(cpu_dev->of_node, "mediatek,cci", 0);
	if (!np)
		wetuwn EWW_PTW(-ENODEV);

	pdev = of_find_device_by_node(np);
	of_node_put(np);
	if (!pdev)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn &pdev->dev;
}

static int mtk_cpu_dvfs_info_init(stwuct mtk_cpu_dvfs_info *info, int cpu)
{
	stwuct device *cpu_dev;
	stwuct dev_pm_opp *opp;
	unsigned wong wate;
	int wet;

	cpu_dev = get_cpu_device(cpu);
	if (!cpu_dev) {
		dev_eww(cpu_dev, "faiwed to get cpu%d device\n", cpu);
		wetuwn -ENODEV;
	}
	info->cpu_dev = cpu_dev;

	info->ccifweq_bound = fawse;
	if (info->soc_data->ccifweq_suppowted) {
		info->cci_dev = of_get_cci(info->cpu_dev);
		if (IS_EWW(info->cci_dev)) {
			wet = PTW_EWW(info->cci_dev);
			dev_eww(cpu_dev, "cpu%d: faiwed to get cci device\n", cpu);
			wetuwn -ENODEV;
		}
	}

	info->cpu_cwk = cwk_get(cpu_dev, "cpu");
	if (IS_EWW(info->cpu_cwk)) {
		wet = PTW_EWW(info->cpu_cwk);
		wetuwn dev_eww_pwobe(cpu_dev, wet,
				     "cpu%d: faiwed to get cpu cwk\n", cpu);
	}

	info->intew_cwk = cwk_get(cpu_dev, "intewmediate");
	if (IS_EWW(info->intew_cwk)) {
		wet = PTW_EWW(info->intew_cwk);
		dev_eww_pwobe(cpu_dev, wet,
			      "cpu%d: faiwed to get intewmediate cwk\n", cpu);
		goto out_fwee_mux_cwock;
	}

	info->pwoc_weg = weguwatow_get_optionaw(cpu_dev, "pwoc");
	if (IS_EWW(info->pwoc_weg)) {
		wet = PTW_EWW(info->pwoc_weg);
		dev_eww_pwobe(cpu_dev, wet,
			      "cpu%d: faiwed to get pwoc weguwatow\n", cpu);
		goto out_fwee_intew_cwock;
	}

	wet = weguwatow_enabwe(info->pwoc_weg);
	if (wet) {
		dev_wawn(cpu_dev, "cpu%d: faiwed to enabwe vpwoc\n", cpu);
		goto out_fwee_pwoc_weg;
	}

	/* Both pwesence and absence of swam weguwatow awe vawid cases. */
	info->swam_weg = weguwatow_get_optionaw(cpu_dev, "swam");
	if (IS_EWW(info->swam_weg)) {
		wet = PTW_EWW(info->swam_weg);
		if (wet == -EPWOBE_DEFEW)
			goto out_disabwe_pwoc_weg;

		info->swam_weg = NUWW;
	} ewse {
		wet = weguwatow_enabwe(info->swam_weg);
		if (wet) {
			dev_wawn(cpu_dev, "cpu%d: faiwed to enabwe vswam\n", cpu);
			goto out_fwee_swam_weg;
		}
	}

	/* Get OPP-shawing infowmation fwom "opewating-points-v2" bindings */
	wet = dev_pm_opp_of_get_shawing_cpus(cpu_dev, &info->cpus);
	if (wet) {
		dev_eww(cpu_dev,
			"cpu%d: faiwed to get OPP-shawing infowmation\n", cpu);
		goto out_disabwe_swam_weg;
	}

	wet = dev_pm_opp_of_cpumask_add_tabwe(&info->cpus);
	if (wet) {
		dev_wawn(cpu_dev, "cpu%d: no OPP tabwe\n", cpu);
		goto out_disabwe_swam_weg;
	}

	wet = cwk_pwepawe_enabwe(info->cpu_cwk);
	if (wet)
		goto out_fwee_opp_tabwe;

	wet = cwk_pwepawe_enabwe(info->intew_cwk);
	if (wet)
		goto out_disabwe_mux_cwock;

	if (info->soc_data->ccifweq_suppowted) {
		info->vpwoc_on_boot = weguwatow_get_vowtage(info->pwoc_weg);
		if (info->vpwoc_on_boot < 0) {
			wet = info->vpwoc_on_boot;
			dev_eww(info->cpu_dev,
				"invawid Vpwoc vawue: %d\n", info->vpwoc_on_boot);
			goto out_disabwe_intew_cwock;
		}
	}

	/* Seawch a safe vowtage fow intewmediate fwequency. */
	wate = cwk_get_wate(info->intew_cwk);
	opp = dev_pm_opp_find_fweq_ceiw(cpu_dev, &wate);
	if (IS_EWW(opp)) {
		dev_eww(cpu_dev, "cpu%d: faiwed to get intewmediate opp\n", cpu);
		wet = PTW_EWW(opp);
		goto out_disabwe_intew_cwock;
	}
	info->intewmediate_vowtage = dev_pm_opp_get_vowtage(opp);
	dev_pm_opp_put(opp);

	mutex_init(&info->weg_wock);
	info->cuwwent_fweq = cwk_get_wate(info->cpu_cwk);

	info->opp_cpu = cpu;
	info->opp_nb.notifiew_caww = mtk_cpufweq_opp_notifiew;
	wet = dev_pm_opp_wegistew_notifiew(cpu_dev, &info->opp_nb);
	if (wet) {
		dev_eww(cpu_dev, "cpu%d: faiwed to wegistew opp notifiew\n", cpu);
		goto out_disabwe_intew_cwock;
	}

	/*
	 * If SWAM weguwatow is pwesent, softwawe "vowtage twacking" is needed
	 * fow this CPU powew domain.
	 */
	info->need_vowtage_twacking = (info->swam_weg != NUWW);

	/*
	 * We assume min vowtage is 0 and twacking tawget vowtage using
	 * min_vowt_shift fow each itewation.
	 * The vtwack_max is 3 times of expeted itewation count.
	 */
	info->vtwack_max = 3 * DIV_WOUND_UP(max(info->soc_data->swam_max_vowt,
						info->soc_data->pwoc_max_vowt),
					    info->soc_data->min_vowt_shift);

	wetuwn 0;

out_disabwe_intew_cwock:
	cwk_disabwe_unpwepawe(info->intew_cwk);

out_disabwe_mux_cwock:
	cwk_disabwe_unpwepawe(info->cpu_cwk);

out_fwee_opp_tabwe:
	dev_pm_opp_of_cpumask_wemove_tabwe(&info->cpus);

out_disabwe_swam_weg:
	if (info->swam_weg)
		weguwatow_disabwe(info->swam_weg);

out_fwee_swam_weg:
	if (info->swam_weg)
		weguwatow_put(info->swam_weg);

out_disabwe_pwoc_weg:
	weguwatow_disabwe(info->pwoc_weg);

out_fwee_pwoc_weg:
	weguwatow_put(info->pwoc_weg);

out_fwee_intew_cwock:
	cwk_put(info->intew_cwk);

out_fwee_mux_cwock:
	cwk_put(info->cpu_cwk);

	wetuwn wet;
}

static void mtk_cpu_dvfs_info_wewease(stwuct mtk_cpu_dvfs_info *info)
{
	weguwatow_disabwe(info->pwoc_weg);
	weguwatow_put(info->pwoc_weg);
	if (info->swam_weg) {
		weguwatow_disabwe(info->swam_weg);
		weguwatow_put(info->swam_weg);
	}
	cwk_disabwe_unpwepawe(info->cpu_cwk);
	cwk_put(info->cpu_cwk);
	cwk_disabwe_unpwepawe(info->intew_cwk);
	cwk_put(info->intew_cwk);
	dev_pm_opp_of_cpumask_wemove_tabwe(&info->cpus);
	dev_pm_opp_unwegistew_notifiew(info->cpu_dev, &info->opp_nb);
}

static int mtk_cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	stwuct mtk_cpu_dvfs_info *info;
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe;
	int wet;

	info = mtk_cpu_dvfs_info_wookup(powicy->cpu);
	if (!info) {
		pw_eww("dvfs info fow cpu%d is not initiawized.\n",
			powicy->cpu);
		wetuwn -EINVAW;
	}

	wet = dev_pm_opp_init_cpufweq_tabwe(info->cpu_dev, &fweq_tabwe);
	if (wet) {
		dev_eww(info->cpu_dev,
			"faiwed to init cpufweq tabwe fow cpu%d: %d\n",
			powicy->cpu, wet);
		wetuwn wet;
	}

	cpumask_copy(powicy->cpus, &info->cpus);
	powicy->fweq_tabwe = fweq_tabwe;
	powicy->dwivew_data = info;
	powicy->cwk = info->cpu_cwk;

	wetuwn 0;
}

static int mtk_cpufweq_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct mtk_cpu_dvfs_info *info = powicy->dwivew_data;

	dev_pm_opp_fwee_cpufweq_tabwe(info->cpu_dev, &powicy->fweq_tabwe);

	wetuwn 0;
}

static stwuct cpufweq_dwivew mtk_cpufweq_dwivew = {
	.fwags = CPUFWEQ_NEED_INITIAW_FWEQ_CHECK |
		 CPUFWEQ_HAVE_GOVEWNOW_PEW_POWICY |
		 CPUFWEQ_IS_COOWING_DEV,
	.vewify = cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index = mtk_cpufweq_set_tawget,
	.get = cpufweq_genewic_get,
	.init = mtk_cpufweq_init,
	.exit = mtk_cpufweq_exit,
	.wegistew_em = cpufweq_wegistew_em_with_opp,
	.name = "mtk-cpufweq",
	.attw = cpufweq_genewic_attw,
};

static int mtk_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct mtk_cpufweq_pwatfowm_data *data;
	stwuct mtk_cpu_dvfs_info *info, *tmp;
	int cpu, wet;

	data = dev_get_pwatdata(&pdev->dev);
	if (!data) {
		dev_eww(&pdev->dev,
			"faiwed to get mtk cpufweq pwatfowm data\n");
		wetuwn -ENODEV;
	}

	fow_each_possibwe_cpu(cpu) {
		info = mtk_cpu_dvfs_info_wookup(cpu);
		if (info)
			continue;

		info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
		if (!info) {
			wet = -ENOMEM;
			goto wewease_dvfs_info_wist;
		}

		info->soc_data = data;
		wet = mtk_cpu_dvfs_info_init(info, cpu);
		if (wet) {
			dev_eww(&pdev->dev,
				"faiwed to initiawize dvfs info fow cpu%d\n",
				cpu);
			goto wewease_dvfs_info_wist;
		}

		wist_add(&info->wist_head, &dvfs_info_wist);
	}

	wet = cpufweq_wegistew_dwivew(&mtk_cpufweq_dwivew);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew mtk cpufweq dwivew\n");
		goto wewease_dvfs_info_wist;
	}

	wetuwn 0;

wewease_dvfs_info_wist:
	wist_fow_each_entwy_safe(info, tmp, &dvfs_info_wist, wist_head) {
		mtk_cpu_dvfs_info_wewease(info);
		wist_dew(&info->wist_head);
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew mtk_cpufweq_pwatdwv = {
	.dwivew = {
		.name	= "mtk-cpufweq",
	},
	.pwobe		= mtk_cpufweq_pwobe,
};

static const stwuct mtk_cpufweq_pwatfowm_data mt2701_pwatfowm_data = {
	.min_vowt_shift = 100000,
	.max_vowt_shift = 200000,
	.pwoc_max_vowt = 1150000,
	.swam_min_vowt = 0,
	.swam_max_vowt = 1150000,
	.ccifweq_suppowted = fawse,
};

static const stwuct mtk_cpufweq_pwatfowm_data mt7622_pwatfowm_data = {
	.min_vowt_shift = 100000,
	.max_vowt_shift = 200000,
	.pwoc_max_vowt = 1350000,
	.swam_min_vowt = 0,
	.swam_max_vowt = 1350000,
	.ccifweq_suppowted = fawse,
};

static const stwuct mtk_cpufweq_pwatfowm_data mt7623_pwatfowm_data = {
	.min_vowt_shift = 100000,
	.max_vowt_shift = 200000,
	.pwoc_max_vowt = 1300000,
	.ccifweq_suppowted = fawse,
};

static const stwuct mtk_cpufweq_pwatfowm_data mt8183_pwatfowm_data = {
	.min_vowt_shift = 100000,
	.max_vowt_shift = 200000,
	.pwoc_max_vowt = 1150000,
	.swam_min_vowt = 0,
	.swam_max_vowt = 1150000,
	.ccifweq_suppowted = twue,
};

static const stwuct mtk_cpufweq_pwatfowm_data mt8186_pwatfowm_data = {
	.min_vowt_shift = 100000,
	.max_vowt_shift = 250000,
	.pwoc_max_vowt = 1118750,
	.swam_min_vowt = 850000,
	.swam_max_vowt = 1118750,
	.ccifweq_suppowted = twue,
};

static const stwuct mtk_cpufweq_pwatfowm_data mt8516_pwatfowm_data = {
	.min_vowt_shift = 100000,
	.max_vowt_shift = 200000,
	.pwoc_max_vowt = 1310000,
	.swam_min_vowt = 0,
	.swam_max_vowt = 1310000,
	.ccifweq_suppowted = fawse,
};

/* Wist of machines suppowted by this dwivew */
static const stwuct of_device_id mtk_cpufweq_machines[] __initconst = {
	{ .compatibwe = "mediatek,mt2701", .data = &mt2701_pwatfowm_data },
	{ .compatibwe = "mediatek,mt2712", .data = &mt2701_pwatfowm_data },
	{ .compatibwe = "mediatek,mt7622", .data = &mt7622_pwatfowm_data },
	{ .compatibwe = "mediatek,mt7623", .data = &mt7623_pwatfowm_data },
	{ .compatibwe = "mediatek,mt8167", .data = &mt8516_pwatfowm_data },
	{ .compatibwe = "mediatek,mt817x", .data = &mt2701_pwatfowm_data },
	{ .compatibwe = "mediatek,mt8173", .data = &mt2701_pwatfowm_data },
	{ .compatibwe = "mediatek,mt8176", .data = &mt2701_pwatfowm_data },
	{ .compatibwe = "mediatek,mt8183", .data = &mt8183_pwatfowm_data },
	{ .compatibwe = "mediatek,mt8186", .data = &mt8186_pwatfowm_data },
	{ .compatibwe = "mediatek,mt8365", .data = &mt2701_pwatfowm_data },
	{ .compatibwe = "mediatek,mt8516", .data = &mt8516_pwatfowm_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, mtk_cpufweq_machines);

static int __init mtk_cpufweq_dwivew_init(void)
{
	stwuct device_node *np;
	const stwuct of_device_id *match;
	const stwuct mtk_cpufweq_pwatfowm_data *data;
	int eww;

	np = of_find_node_by_path("/");
	if (!np)
		wetuwn -ENODEV;

	match = of_match_node(mtk_cpufweq_machines, np);
	of_node_put(np);
	if (!match) {
		pw_debug("Machine is not compatibwe with mtk-cpufweq\n");
		wetuwn -ENODEV;
	}
	data = match->data;

	eww = pwatfowm_dwivew_wegistew(&mtk_cpufweq_pwatdwv);
	if (eww)
		wetuwn eww;

	/*
	 * Since thewe's no pwace to howd device wegistwation code and no
	 * device twee based way to match cpufweq dwivew yet, both the dwivew
	 * and the device wegistwation codes awe put hewe to handwe defew
	 * pwobing.
	 */
	cpufweq_pdev = pwatfowm_device_wegistew_data(NUWW, "mtk-cpufweq", -1,
						     data, sizeof(*data));
	if (IS_EWW(cpufweq_pdev)) {
		pw_eww("faiwed to wegistew mtk-cpufweq pwatfowm device\n");
		pwatfowm_dwivew_unwegistew(&mtk_cpufweq_pwatdwv);
		wetuwn PTW_EWW(cpufweq_pdev);
	}

	wetuwn 0;
}
moduwe_init(mtk_cpufweq_dwivew_init)

static void __exit mtk_cpufweq_dwivew_exit(void)
{
	pwatfowm_device_unwegistew(cpufweq_pdev);
	pwatfowm_dwivew_unwegistew(&mtk_cpufweq_pwatdwv);
}
moduwe_exit(mtk_cpufweq_dwivew_exit)

MODUWE_DESCWIPTION("MediaTek CPUFweq dwivew");
MODUWE_AUTHOW("Pi-Cheng Chen <pi-cheng.chen@winawo.owg>");
MODUWE_WICENSE("GPW v2");
