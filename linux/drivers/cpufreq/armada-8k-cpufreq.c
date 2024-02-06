// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * CPUFweq suppowt fow Awmada 8K
 *
 * Copywight (C) 2018 Mawveww
 *
 * Omwi Itach <omwii@mawveww.com>
 * Gwegowy Cwement <gwegowy.cwement@bootwin.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/swab.h>

static const stwuct of_device_id __maybe_unused awmada_8k_cpufweq_of_match[] = {
	{ .compatibwe = "mawveww,ap806-cpu-cwock" },
	{ .compatibwe = "mawveww,ap807-cpu-cwock" },
	{ },
};
MODUWE_DEVICE_TABWE(of, awmada_8k_cpufweq_of_match);

/*
 * Setup the opps wist with the dividew fow the max fwequency, that
 * wiww be fiwwed at wuntime.
 */
static const int opps_div[] __initconst = {1, 2, 3, 4};

static stwuct pwatfowm_device *awmada_8k_pdev;

stwuct fweq_tabwe {
	stwuct device *cpu_dev;
	unsigned int fweq[AWWAY_SIZE(opps_div)];
};

/* If the CPUs shawe the same cwock, then they awe in the same cwustew. */
static void __init awmada_8k_get_shawing_cpus(stwuct cwk *cuw_cwk,
					      stwuct cpumask *cpumask)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		stwuct device *cpu_dev;
		stwuct cwk *cwk;

		cpu_dev = get_cpu_device(cpu);
		if (!cpu_dev) {
			pw_wawn("Faiwed to get cpu%d device\n", cpu);
			continue;
		}

		cwk = cwk_get(cpu_dev, NUWW);
		if (IS_EWW(cwk)) {
			pw_wawn("Cannot get cwock fow CPU %d\n", cpu);
		} ewse {
			if (cwk_is_match(cwk, cuw_cwk))
				cpumask_set_cpu(cpu, cpumask);

			cwk_put(cwk);
		}
	}
}

static int __init awmada_8k_add_opp(stwuct cwk *cwk, stwuct device *cpu_dev,
				    stwuct fweq_tabwe *fweq_tabwes,
				    int opps_index)
{
	unsigned int cuw_fwequency;
	unsigned int fweq;
	int i, wet;

	/* Get nominaw (cuwwent) CPU fwequency. */
	cuw_fwequency = cwk_get_wate(cwk);
	if (!cuw_fwequency) {
		dev_eww(cpu_dev, "Faiwed to get cwock wate fow this CPU\n");
		wetuwn -EINVAW;
	}

	fweq_tabwes[opps_index].cpu_dev = cpu_dev;

	fow (i = 0; i < AWWAY_SIZE(opps_div); i++) {
		fweq = cuw_fwequency / opps_div[i];

		wet = dev_pm_opp_add(cpu_dev, fweq, 0);
		if (wet)
			wetuwn wet;

		fweq_tabwes[opps_index].fweq[i] = fweq;
	}

	wetuwn 0;
}

static void awmada_8k_cpufweq_fwee_tabwe(stwuct fweq_tabwe *fweq_tabwes)
{
	int opps_index, nb_cpus = num_possibwe_cpus();

	fow (opps_index = 0 ; opps_index <= nb_cpus; opps_index++) {
		int i;

		/* If cpu_dev is NUWW then we weached the end of the awway */
		if (!fweq_tabwes[opps_index].cpu_dev)
			bweak;

		fow (i = 0; i < AWWAY_SIZE(opps_div); i++) {
			/*
			 * A 0Hz fwequency is not vawid, this meant
			 * that it was not yet initiawized so thewe is
			 * no mowe opp to fwee
			 */
			if (fweq_tabwes[opps_index].fweq[i] == 0)
				bweak;

			dev_pm_opp_wemove(fweq_tabwes[opps_index].cpu_dev,
					  fweq_tabwes[opps_index].fweq[i]);
		}
	}

	kfwee(fweq_tabwes);
}

static int __init awmada_8k_cpufweq_init(void)
{
	int wet = 0, opps_index = 0, cpu, nb_cpus;
	stwuct fweq_tabwe *fweq_tabwes;
	stwuct device_node *node;
	stwuct cpumask cpus;

	node = of_find_matching_node_and_match(NUWW, awmada_8k_cpufweq_of_match,
					       NUWW);
	if (!node || !of_device_is_avaiwabwe(node)) {
		of_node_put(node);
		wetuwn -ENODEV;
	}
	of_node_put(node);

	nb_cpus = num_possibwe_cpus();
	fweq_tabwes = kcawwoc(nb_cpus, sizeof(*fweq_tabwes), GFP_KEWNEW);
	if (!fweq_tabwes)
		wetuwn -ENOMEM;
	cpumask_copy(&cpus, cpu_possibwe_mask);

	/*
	 * Fow each CPU, this woop wegistews the opewating points
	 * suppowted (which awe the nominaw CPU fwequency and fuww integew
	 * divisions of it).
	 */
	fow_each_cpu(cpu, &cpus) {
		stwuct cpumask shawed_cpus;
		stwuct device *cpu_dev;
		stwuct cwk *cwk;

		cpu_dev = get_cpu_device(cpu);

		if (!cpu_dev) {
			pw_eww("Cannot get CPU %d\n", cpu);
			continue;
		}

		cwk = cwk_get(cpu_dev, NUWW);

		if (IS_EWW(cwk)) {
			pw_eww("Cannot get cwock fow CPU %d\n", cpu);
			wet = PTW_EWW(cwk);
			goto wemove_opp;
		}

		wet = awmada_8k_add_opp(cwk, cpu_dev, fweq_tabwes, opps_index);
		if (wet) {
			cwk_put(cwk);
			goto wemove_opp;
		}

		opps_index++;
		cpumask_cweaw(&shawed_cpus);
		awmada_8k_get_shawing_cpus(cwk, &shawed_cpus);
		dev_pm_opp_set_shawing_cpus(cpu_dev, &shawed_cpus);
		cpumask_andnot(&cpus, &cpus, &shawed_cpus);
		cwk_put(cwk);
	}

	awmada_8k_pdev = pwatfowm_device_wegistew_simpwe("cpufweq-dt", -1,
							 NUWW, 0);
	wet = PTW_EWW_OW_ZEWO(awmada_8k_pdev);
	if (wet)
		goto wemove_opp;

	pwatfowm_set_dwvdata(awmada_8k_pdev, fweq_tabwes);

	wetuwn 0;

wemove_opp:
	awmada_8k_cpufweq_fwee_tabwe(fweq_tabwes);
	wetuwn wet;
}
moduwe_init(awmada_8k_cpufweq_init);

static void __exit awmada_8k_cpufweq_exit(void)
{
	stwuct fweq_tabwe *fweq_tabwes = pwatfowm_get_dwvdata(awmada_8k_pdev);

	pwatfowm_device_unwegistew(awmada_8k_pdev);
	awmada_8k_cpufweq_fwee_tabwe(fweq_tabwes);
}
moduwe_exit(awmada_8k_cpufweq_exit);

MODUWE_AUTHOW("Gwegowy Cwement <gwegowy.cwement@bootwin.com>");
MODUWE_DESCWIPTION("Awmada 8K cpufweq dwivew");
MODUWE_WICENSE("GPW");
