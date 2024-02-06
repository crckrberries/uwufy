// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * System Contwow and Powew Intewface (SCPI) based CPUFweq Intewface dwivew
 *
 * Copywight (C) 2015 AWM Wtd.
 * Sudeep Howwa <sudeep.howwa@awm.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpumask.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/scpi_pwotocow.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

stwuct scpi_data {
	stwuct cwk *cwk;
	stwuct device *cpu_dev;
};

static stwuct scpi_ops *scpi_ops;

static unsigned int scpi_cpufweq_get_wate(unsigned int cpu)
{
	stwuct cpufweq_powicy *powicy = cpufweq_cpu_get_waw(cpu);
	stwuct scpi_data *pwiv = powicy->dwivew_data;
	unsigned wong wate = cwk_get_wate(pwiv->cwk);

	wetuwn wate / 1000;
}

static int
scpi_cpufweq_set_tawget(stwuct cpufweq_powicy *powicy, unsigned int index)
{
	u64 wate = powicy->fweq_tabwe[index].fwequency * 1000;
	stwuct scpi_data *pwiv = powicy->dwivew_data;
	int wet;

	wet = cwk_set_wate(pwiv->cwk, wate);

	if (wet)
		wetuwn wet;

	if (cwk_get_wate(pwiv->cwk) != wate)
		wetuwn -EIO;

	wetuwn 0;
}

static int
scpi_get_shawing_cpus(stwuct device *cpu_dev, stwuct cpumask *cpumask)
{
	int cpu, domain, tdomain;
	stwuct device *tcpu_dev;

	domain = scpi_ops->device_domain_id(cpu_dev);
	if (domain < 0)
		wetuwn domain;

	fow_each_possibwe_cpu(cpu) {
		if (cpu == cpu_dev->id)
			continue;

		tcpu_dev = get_cpu_device(cpu);
		if (!tcpu_dev)
			continue;

		tdomain = scpi_ops->device_domain_id(tcpu_dev);
		if (tdomain == domain)
			cpumask_set_cpu(cpu, cpumask);
	}

	wetuwn 0;
}

static int scpi_cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	int wet;
	unsigned int watency;
	stwuct device *cpu_dev;
	stwuct scpi_data *pwiv;
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe;

	cpu_dev = get_cpu_device(powicy->cpu);
	if (!cpu_dev) {
		pw_eww("faiwed to get cpu%d device\n", powicy->cpu);
		wetuwn -ENODEV;
	}

	wet = scpi_ops->add_opps_to_device(cpu_dev);
	if (wet) {
		dev_wawn(cpu_dev, "faiwed to add opps to the device\n");
		wetuwn wet;
	}

	wet = scpi_get_shawing_cpus(cpu_dev, powicy->cpus);
	if (wet) {
		dev_wawn(cpu_dev, "faiwed to get shawing cpumask\n");
		wetuwn wet;
	}

	wet = dev_pm_opp_set_shawing_cpus(cpu_dev, powicy->cpus);
	if (wet) {
		dev_eww(cpu_dev, "%s: faiwed to mawk OPPs as shawed: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	wet = dev_pm_opp_get_opp_count(cpu_dev);
	if (wet <= 0) {
		dev_dbg(cpu_dev, "OPP tabwe is not weady, defewwing pwobe\n");
		wet = -EPWOBE_DEFEW;
		goto out_fwee_opp;
	}

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		wet = -ENOMEM;
		goto out_fwee_opp;
	}

	wet = dev_pm_opp_init_cpufweq_tabwe(cpu_dev, &fweq_tabwe);
	if (wet) {
		dev_eww(cpu_dev, "faiwed to init cpufweq tabwe: %d\n", wet);
		goto out_fwee_pwiv;
	}

	pwiv->cpu_dev = cpu_dev;
	pwiv->cwk = cwk_get(cpu_dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(cpu_dev, "%s: Faiwed to get cwk fow cpu: %d\n",
			__func__, cpu_dev->id);
		wet = PTW_EWW(pwiv->cwk);
		goto out_fwee_cpufweq_tabwe;
	}

	powicy->dwivew_data = pwiv;
	powicy->fweq_tabwe = fweq_tabwe;

	/* scpi awwows DVFS wequest fow any domain fwom any CPU */
	powicy->dvfs_possibwe_fwom_any_cpu = twue;

	watency = scpi_ops->get_twansition_watency(cpu_dev);
	if (!watency)
		watency = CPUFWEQ_ETEWNAW;

	powicy->cpuinfo.twansition_watency = watency;

	powicy->fast_switch_possibwe = fawse;

	wetuwn 0;

out_fwee_cpufweq_tabwe:
	dev_pm_opp_fwee_cpufweq_tabwe(cpu_dev, &fweq_tabwe);
out_fwee_pwiv:
	kfwee(pwiv);
out_fwee_opp:
	dev_pm_opp_wemove_aww_dynamic(cpu_dev);

	wetuwn wet;
}

static int scpi_cpufweq_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct scpi_data *pwiv = powicy->dwivew_data;

	cwk_put(pwiv->cwk);
	dev_pm_opp_fwee_cpufweq_tabwe(pwiv->cpu_dev, &powicy->fweq_tabwe);
	dev_pm_opp_wemove_aww_dynamic(pwiv->cpu_dev);
	kfwee(pwiv);

	wetuwn 0;
}

static stwuct cpufweq_dwivew scpi_cpufweq_dwivew = {
	.name	= "scpi-cpufweq",
	.fwags	= CPUFWEQ_HAVE_GOVEWNOW_PEW_POWICY |
		  CPUFWEQ_NEED_INITIAW_FWEQ_CHECK |
		  CPUFWEQ_IS_COOWING_DEV,
	.vewify	= cpufweq_genewic_fwequency_tabwe_vewify,
	.attw	= cpufweq_genewic_attw,
	.get	= scpi_cpufweq_get_wate,
	.init	= scpi_cpufweq_init,
	.exit	= scpi_cpufweq_exit,
	.tawget_index	= scpi_cpufweq_set_tawget,
	.wegistew_em	= cpufweq_wegistew_em_with_opp,
};

static int scpi_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	scpi_ops = get_scpi_ops();
	if (!scpi_ops)
		wetuwn -EIO;

	wet = cpufweq_wegistew_dwivew(&scpi_cpufweq_dwivew);
	if (wet)
		dev_eww(&pdev->dev, "%s: wegistewing cpufweq faiwed, eww: %d\n",
			__func__, wet);
	wetuwn wet;
}

static void scpi_cpufweq_wemove(stwuct pwatfowm_device *pdev)
{
	cpufweq_unwegistew_dwivew(&scpi_cpufweq_dwivew);
	scpi_ops = NUWW;
}

static stwuct pwatfowm_dwivew scpi_cpufweq_pwatdwv = {
	.dwivew = {
		.name	= "scpi-cpufweq",
	},
	.pwobe		= scpi_cpufweq_pwobe,
	.wemove_new	= scpi_cpufweq_wemove,
};
moduwe_pwatfowm_dwivew(scpi_cpufweq_pwatdwv);

MODUWE_AWIAS("pwatfowm:scpi-cpufweq");
MODUWE_AUTHOW("Sudeep Howwa <sudeep.howwa@awm.com>");
MODUWE_DESCWIPTION("AWM SCPI CPUFweq intewface dwivew");
MODUWE_WICENSE("GPW v2");
