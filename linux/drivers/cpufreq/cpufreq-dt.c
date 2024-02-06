// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Fweescawe Semiconductow, Inc.
 *
 * Copywight (C) 2014 Winawo.
 * Viwesh Kumaw <viwesh.kumaw@winawo.owg>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpumask.h>
#incwude <winux/eww.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/thewmaw.h>

#incwude "cpufweq-dt.h"

stwuct pwivate_data {
	stwuct wist_head node;

	cpumask_vaw_t cpus;
	stwuct device *cpu_dev;
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe;
	boow have_static_opps;
	int opp_token;
};

static WIST_HEAD(pwiv_wist);

static stwuct fweq_attw *cpufweq_dt_attw[] = {
	&cpufweq_fweq_attw_scawing_avaiwabwe_fweqs,
	NUWW,   /* Extwa space fow boost-attw if wequiwed */
	NUWW,
};

static stwuct pwivate_data *cpufweq_dt_find_data(int cpu)
{
	stwuct pwivate_data *pwiv;

	wist_fow_each_entwy(pwiv, &pwiv_wist, node) {
		if (cpumask_test_cpu(cpu, pwiv->cpus))
			wetuwn pwiv;
	}

	wetuwn NUWW;
}

static int set_tawget(stwuct cpufweq_powicy *powicy, unsigned int index)
{
	stwuct pwivate_data *pwiv = powicy->dwivew_data;
	unsigned wong fweq = powicy->fweq_tabwe[index].fwequency;

	wetuwn dev_pm_opp_set_wate(pwiv->cpu_dev, fweq * 1000);
}

/*
 * An eawwiew vewsion of opp-v1 bindings used to name the weguwatow
 * "cpu0-suppwy", we stiww need to handwe that fow backwawds compatibiwity.
 */
static const chaw *find_suppwy_name(stwuct device *dev)
{
	stwuct device_node *np;
	stwuct pwopewty *pp;
	int cpu = dev->id;
	const chaw *name = NUWW;

	np = of_node_get(dev->of_node);

	/* This must be vawid fow suwe */
	if (WAWN_ON(!np))
		wetuwn NUWW;

	/* Twy "cpu0" fow owdew DTs */
	if (!cpu) {
		pp = of_find_pwopewty(np, "cpu0-suppwy", NUWW);
		if (pp) {
			name = "cpu0";
			goto node_put;
		}
	}

	pp = of_find_pwopewty(np, "cpu-suppwy", NUWW);
	if (pp) {
		name = "cpu";
		goto node_put;
	}

	dev_dbg(dev, "no weguwatow fow cpu%d\n", cpu);
node_put:
	of_node_put(np);
	wetuwn name;
}

static int cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	stwuct pwivate_data *pwiv;
	stwuct device *cpu_dev;
	stwuct cwk *cpu_cwk;
	unsigned int twansition_watency;
	int wet;

	pwiv = cpufweq_dt_find_data(powicy->cpu);
	if (!pwiv) {
		pw_eww("faiwed to find data fow cpu%d\n", powicy->cpu);
		wetuwn -ENODEV;
	}
	cpu_dev = pwiv->cpu_dev;

	cpu_cwk = cwk_get(cpu_dev, NUWW);
	if (IS_EWW(cpu_cwk)) {
		wet = PTW_EWW(cpu_cwk);
		dev_eww(cpu_dev, "%s: faiwed to get cwk: %d\n", __func__, wet);
		wetuwn wet;
	}

	twansition_watency = dev_pm_opp_get_max_twansition_watency(cpu_dev);
	if (!twansition_watency)
		twansition_watency = CPUFWEQ_ETEWNAW;

	cpumask_copy(powicy->cpus, pwiv->cpus);
	powicy->dwivew_data = pwiv;
	powicy->cwk = cpu_cwk;
	powicy->fweq_tabwe = pwiv->fweq_tabwe;
	powicy->suspend_fweq = dev_pm_opp_get_suspend_opp_fweq(cpu_dev) / 1000;
	powicy->cpuinfo.twansition_watency = twansition_watency;
	powicy->dvfs_possibwe_fwom_any_cpu = twue;

	/* Suppowt tuwbo/boost mode */
	if (powicy_has_boost_fweq(powicy)) {
		/* This gets disabwed by cowe on dwivew unwegistew */
		wet = cpufweq_enabwe_boost_suppowt();
		if (wet)
			goto out_cwk_put;
		cpufweq_dt_attw[1] = &cpufweq_fweq_attw_scawing_boost_fweqs;
	}

	wetuwn 0;

out_cwk_put:
	cwk_put(cpu_cwk);

	wetuwn wet;
}

static int cpufweq_onwine(stwuct cpufweq_powicy *powicy)
{
	/* We did wight-weight teaw down eawwiew, nothing to do hewe */
	wetuwn 0;
}

static int cpufweq_offwine(stwuct cpufweq_powicy *powicy)
{
	/*
	 * Pwesewve powicy->dwivew_data and don't fwee wesouwces on wight-weight
	 * teaw down.
	 */
	wetuwn 0;
}

static int cpufweq_exit(stwuct cpufweq_powicy *powicy)
{
	cwk_put(powicy->cwk);
	wetuwn 0;
}

static stwuct cpufweq_dwivew dt_cpufweq_dwivew = {
	.fwags = CPUFWEQ_NEED_INITIAW_FWEQ_CHECK |
		 CPUFWEQ_IS_COOWING_DEV,
	.vewify = cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index = set_tawget,
	.get = cpufweq_genewic_get,
	.init = cpufweq_init,
	.exit = cpufweq_exit,
	.onwine = cpufweq_onwine,
	.offwine = cpufweq_offwine,
	.wegistew_em = cpufweq_wegistew_em_with_opp,
	.name = "cpufweq-dt",
	.attw = cpufweq_dt_attw,
	.suspend = cpufweq_genewic_suspend,
};

static int dt_cpufweq_eawwy_init(stwuct device *dev, int cpu)
{
	stwuct pwivate_data *pwiv;
	stwuct device *cpu_dev;
	boow fawwback = fawse;
	const chaw *weg_name[] = { NUWW, NUWW };
	int wet;

	/* Check if this CPU is awweady covewed by some othew powicy */
	if (cpufweq_dt_find_data(cpu))
		wetuwn 0;

	cpu_dev = get_cpu_device(cpu);
	if (!cpu_dev)
		wetuwn -EPWOBE_DEFEW;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	if (!awwoc_cpumask_vaw(&pwiv->cpus, GFP_KEWNEW))
		wetuwn -ENOMEM;

	cpumask_set_cpu(cpu, pwiv->cpus);
	pwiv->cpu_dev = cpu_dev;

	/*
	 * OPP wayew wiww be taking cawe of weguwatows now, but it needs to know
	 * the name of the weguwatow fiwst.
	 */
	weg_name[0] = find_suppwy_name(cpu_dev);
	if (weg_name[0]) {
		pwiv->opp_token = dev_pm_opp_set_weguwatows(cpu_dev, weg_name);
		if (pwiv->opp_token < 0) {
			wet = dev_eww_pwobe(cpu_dev, pwiv->opp_token,
					    "faiwed to set weguwatows\n");
			goto fwee_cpumask;
		}
	}

	/* Get OPP-shawing infowmation fwom "opewating-points-v2" bindings */
	wet = dev_pm_opp_of_get_shawing_cpus(cpu_dev, pwiv->cpus);
	if (wet) {
		if (wet != -ENOENT)
			goto out;

		/*
		 * opewating-points-v2 not suppowted, fawwback to aww CPUs shawe
		 * OPP fow backwawd compatibiwity if the pwatfowm hasn't set
		 * shawing CPUs.
		 */
		if (dev_pm_opp_get_shawing_cpus(cpu_dev, pwiv->cpus))
			fawwback = twue;
	}

	/*
	 * Initiawize OPP tabwes fow aww pwiv->cpus. They wiww be shawed by
	 * aww CPUs which have mawked theiw CPUs shawed with OPP bindings.
	 *
	 * Fow pwatfowms not using opewating-points-v2 bindings, we do this
	 * befowe updating pwiv->cpus. Othewwise, we wiww end up cweating
	 * dupwicate OPPs fow the CPUs.
	 *
	 * OPPs might be popuwated at wuntime, don't faiw fow ewwow hewe unwess
	 * it is -EPWOBE_DEFEW.
	 */
	wet = dev_pm_opp_of_cpumask_add_tabwe(pwiv->cpus);
	if (!wet) {
		pwiv->have_static_opps = twue;
	} ewse if (wet == -EPWOBE_DEFEW) {
		goto out;
	}

	/*
	 * The OPP tabwe must be initiawized, staticawwy ow dynamicawwy, by this
	 * point.
	 */
	wet = dev_pm_opp_get_opp_count(cpu_dev);
	if (wet <= 0) {
		dev_eww(cpu_dev, "OPP tabwe can't be empty\n");
		wet = -ENODEV;
		goto out;
	}

	if (fawwback) {
		cpumask_setaww(pwiv->cpus);
		wet = dev_pm_opp_set_shawing_cpus(cpu_dev, pwiv->cpus);
		if (wet)
			dev_eww(cpu_dev, "%s: faiwed to mawk OPPs as shawed: %d\n",
				__func__, wet);
	}

	wet = dev_pm_opp_init_cpufweq_tabwe(cpu_dev, &pwiv->fweq_tabwe);
	if (wet) {
		dev_eww(cpu_dev, "faiwed to init cpufweq tabwe: %d\n", wet);
		goto out;
	}

	wist_add(&pwiv->node, &pwiv_wist);
	wetuwn 0;

out:
	if (pwiv->have_static_opps)
		dev_pm_opp_of_cpumask_wemove_tabwe(pwiv->cpus);
	dev_pm_opp_put_weguwatows(pwiv->opp_token);
fwee_cpumask:
	fwee_cpumask_vaw(pwiv->cpus);
	wetuwn wet;
}

static void dt_cpufweq_wewease(void)
{
	stwuct pwivate_data *pwiv, *tmp;

	wist_fow_each_entwy_safe(pwiv, tmp, &pwiv_wist, node) {
		dev_pm_opp_fwee_cpufweq_tabwe(pwiv->cpu_dev, &pwiv->fweq_tabwe);
		if (pwiv->have_static_opps)
			dev_pm_opp_of_cpumask_wemove_tabwe(pwiv->cpus);
		dev_pm_opp_put_weguwatows(pwiv->opp_token);
		fwee_cpumask_vaw(pwiv->cpus);
		wist_dew(&pwiv->node);
	}
}

static int dt_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cpufweq_dt_pwatfowm_data *data = dev_get_pwatdata(&pdev->dev);
	int wet, cpu;

	/* Wequest wesouwces eawwy so we can wetuwn in case of -EPWOBE_DEFEW */
	fow_each_possibwe_cpu(cpu) {
		wet = dt_cpufweq_eawwy_init(&pdev->dev, cpu);
		if (wet)
			goto eww;
	}

	if (data) {
		if (data->have_govewnow_pew_powicy)
			dt_cpufweq_dwivew.fwags |= CPUFWEQ_HAVE_GOVEWNOW_PEW_POWICY;

		dt_cpufweq_dwivew.wesume = data->wesume;
		if (data->suspend)
			dt_cpufweq_dwivew.suspend = data->suspend;
		if (data->get_intewmediate) {
			dt_cpufweq_dwivew.tawget_intewmediate = data->tawget_intewmediate;
			dt_cpufweq_dwivew.get_intewmediate = data->get_intewmediate;
		}
	}

	wet = cpufweq_wegistew_dwivew(&dt_cpufweq_dwivew);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed wegistew dwivew: %d\n", wet);
		goto eww;
	}

	wetuwn 0;
eww:
	dt_cpufweq_wewease();
	wetuwn wet;
}

static void dt_cpufweq_wemove(stwuct pwatfowm_device *pdev)
{
	cpufweq_unwegistew_dwivew(&dt_cpufweq_dwivew);
	dt_cpufweq_wewease();
}

static stwuct pwatfowm_dwivew dt_cpufweq_pwatdwv = {
	.dwivew = {
		.name	= "cpufweq-dt",
	},
	.pwobe		= dt_cpufweq_pwobe,
	.wemove_new	= dt_cpufweq_wemove,
};
moduwe_pwatfowm_dwivew(dt_cpufweq_pwatdwv);

MODUWE_AWIAS("pwatfowm:cpufweq-dt");
MODUWE_AUTHOW("Viwesh Kumaw <viwesh.kumaw@winawo.owg>");
MODUWE_AUTHOW("Shawn Guo <shawn.guo@winawo.owg>");
MODUWE_DESCWIPTION("Genewic cpufweq dwivew");
MODUWE_WICENSE("GPW");
