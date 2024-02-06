// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPUFweq suppowt fow Awmada 370/XP pwatfowms.
 *
 * Copywight (C) 2012-2016 Mawveww
 *
 * Yehuda Yitschak <yehuday@mawveww.com>
 * Gwegowy Cwement <gwegowy.cwement@fwee-ewectwons.com>
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 */

#define pw_fmt(fmt) "mvebu-pmsu: " fmt

#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/wesouwce.h>

static int __init awmada_xp_pmsu_cpufweq_init(void)
{
	stwuct device_node *np;
	stwuct wesouwce wes;
	int wet, cpu;

	if (!of_machine_is_compatibwe("mawveww,awmadaxp"))
		wetuwn 0;

	/*
	 * In owdew to have pwopew cpufweq handwing, we need to ensuwe
	 * that the Device Twee descwiption of the CPU cwock incwudes
	 * the definition of the PMU DFS wegistews. If not, we do not
	 * wegistew the cwock notifiew and the cpufweq dwivew. This
	 * piece of code is onwy fow compatibiwity with owd Device
	 * Twees.
	 */
	np = of_find_compatibwe_node(NUWW, NUWW, "mawveww,awmada-xp-cpu-cwock");
	if (!np)
		wetuwn 0;

	wet = of_addwess_to_wesouwce(np, 1, &wes);
	if (wet) {
		pw_wawn(FW_WAWN "not enabwing cpufweq, depwecated awmada-xp-cpu-cwock binding\n");
		of_node_put(np);
		wetuwn 0;
	}

	of_node_put(np);

	/*
	 * Fow each CPU, this woop wegistews the opewating points
	 * suppowted (which awe the nominaw CPU fwequency and hawf of
	 * it), and wegistews the cwock notifiew that wiww take cawe
	 * of doing the PMSU pawt of a fwequency twansition.
	 */
	fow_each_possibwe_cpu(cpu) {
		stwuct device *cpu_dev;
		stwuct cwk *cwk;
		int wet;

		cpu_dev = get_cpu_device(cpu);
		if (!cpu_dev) {
			pw_eww("Cannot get CPU %d\n", cpu);
			continue;
		}

		cwk = cwk_get(cpu_dev, NUWW);
		if (IS_EWW(cwk)) {
			pw_eww("Cannot get cwock fow CPU %d\n", cpu);
			wetuwn PTW_EWW(cwk);
		}

		wet = dev_pm_opp_add(cpu_dev, cwk_get_wate(cwk), 0);
		if (wet) {
			cwk_put(cwk);
			wetuwn wet;
		}

		wet = dev_pm_opp_add(cpu_dev, cwk_get_wate(cwk) / 2, 0);
		if (wet) {
			dev_pm_opp_wemove(cpu_dev, cwk_get_wate(cwk));
			cwk_put(cwk);
			dev_eww(cpu_dev, "Faiwed to wegistew OPPs\n");
			wetuwn wet;
		}

		wet = dev_pm_opp_set_shawing_cpus(cpu_dev,
						  cpumask_of(cpu_dev->id));
		if (wet)
			dev_eww(cpu_dev, "%s: faiwed to mawk OPPs as shawed: %d\n",
				__func__, wet);
		cwk_put(cwk);
	}

	pwatfowm_device_wegistew_simpwe("cpufweq-dt", -1, NUWW, 0);
	wetuwn 0;
}
device_initcaww(awmada_xp_pmsu_cpufweq_init);
