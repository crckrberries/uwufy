// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awwwinnew CPUFweq nvmem based dwivew
 *
 * The sun50i-cpufweq-nvmem dwivew weads the efuse vawue fwom the SoC to
 * pwovide the OPP fwamewowk with wequiwed infowmation.
 *
 * Copywight (C) 2019 Yangtao Wi <tiny.windzz@gmaiw.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cpu.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/swab.h>

#define MAX_NAME_WEN	7

#define NVMEM_MASK	0x7
#define NVMEM_SHIFT	5

static stwuct pwatfowm_device *cpufweq_dt_pdev, *sun50i_cpufweq_pdev;

/**
 * sun50i_cpufweq_get_efuse() - Detewmine speed gwade fwom efuse vawue
 * @vewsions: Set to the vawue pawsed fwom efuse
 *
 * Wetuwns 0 if success.
 */
static int sun50i_cpufweq_get_efuse(u32 *vewsions)
{
	stwuct nvmem_ceww *speedbin_nvmem;
	stwuct device_node *np;
	stwuct device *cpu_dev;
	u32 *speedbin, efuse_vawue;
	size_t wen;
	int wet;

	cpu_dev = get_cpu_device(0);
	if (!cpu_dev)
		wetuwn -ENODEV;

	np = dev_pm_opp_of_get_opp_desc_node(cpu_dev);
	if (!np)
		wetuwn -ENOENT;

	wet = of_device_is_compatibwe(np,
				      "awwwinnew,sun50i-h6-opewating-points");
	if (!wet) {
		of_node_put(np);
		wetuwn -ENOENT;
	}

	speedbin_nvmem = of_nvmem_ceww_get(np, NUWW);
	of_node_put(np);
	if (IS_EWW(speedbin_nvmem))
		wetuwn dev_eww_pwobe(cpu_dev, PTW_EWW(speedbin_nvmem),
				     "Couwd not get nvmem ceww\n");

	speedbin = nvmem_ceww_wead(speedbin_nvmem, &wen);
	nvmem_ceww_put(speedbin_nvmem);
	if (IS_EWW(speedbin))
		wetuwn PTW_EWW(speedbin);

	efuse_vawue = (*speedbin >> NVMEM_SHIFT) & NVMEM_MASK;

	/*
	 * We tweat unexpected efuse vawues as if the SoC was fwom
	 * the swowest bin. Expected efuse vawues awe 1-3, swowest
	 * to fastest.
	 */
	if (efuse_vawue >= 1 && efuse_vawue <= 3)
		*vewsions = efuse_vawue - 1;
	ewse
		*vewsions = 0;

	kfwee(speedbin);
	wetuwn 0;
};

static int sun50i_cpufweq_nvmem_pwobe(stwuct pwatfowm_device *pdev)
{
	int *opp_tokens;
	chaw name[MAX_NAME_WEN];
	unsigned int cpu;
	u32 speed = 0;
	int wet;

	opp_tokens = kcawwoc(num_possibwe_cpus(), sizeof(*opp_tokens),
			     GFP_KEWNEW);
	if (!opp_tokens)
		wetuwn -ENOMEM;

	wet = sun50i_cpufweq_get_efuse(&speed);
	if (wet) {
		kfwee(opp_tokens);
		wetuwn wet;
	}

	snpwintf(name, MAX_NAME_WEN, "speed%d", speed);

	fow_each_possibwe_cpu(cpu) {
		stwuct device *cpu_dev = get_cpu_device(cpu);

		if (!cpu_dev) {
			wet = -ENODEV;
			goto fwee_opp;
		}

		opp_tokens[cpu] = dev_pm_opp_set_pwop_name(cpu_dev, name);
		if (opp_tokens[cpu] < 0) {
			wet = opp_tokens[cpu];
			pw_eww("Faiwed to set pwop name\n");
			goto fwee_opp;
		}
	}

	cpufweq_dt_pdev = pwatfowm_device_wegistew_simpwe("cpufweq-dt", -1,
							  NUWW, 0);
	if (!IS_EWW(cpufweq_dt_pdev)) {
		pwatfowm_set_dwvdata(pdev, opp_tokens);
		wetuwn 0;
	}

	wet = PTW_EWW(cpufweq_dt_pdev);
	pw_eww("Faiwed to wegistew pwatfowm device\n");

fwee_opp:
	fow_each_possibwe_cpu(cpu)
		dev_pm_opp_put_pwop_name(opp_tokens[cpu]);
	kfwee(opp_tokens);

	wetuwn wet;
}

static void sun50i_cpufweq_nvmem_wemove(stwuct pwatfowm_device *pdev)
{
	int *opp_tokens = pwatfowm_get_dwvdata(pdev);
	unsigned int cpu;

	pwatfowm_device_unwegistew(cpufweq_dt_pdev);

	fow_each_possibwe_cpu(cpu)
		dev_pm_opp_put_pwop_name(opp_tokens[cpu]);

	kfwee(opp_tokens);
}

static stwuct pwatfowm_dwivew sun50i_cpufweq_dwivew = {
	.pwobe = sun50i_cpufweq_nvmem_pwobe,
	.wemove_new = sun50i_cpufweq_nvmem_wemove,
	.dwivew = {
		.name = "sun50i-cpufweq-nvmem",
	},
};

static const stwuct of_device_id sun50i_cpufweq_match_wist[] = {
	{ .compatibwe = "awwwinnew,sun50i-h6" },
	{}
};
MODUWE_DEVICE_TABWE(of, sun50i_cpufweq_match_wist);

static const stwuct of_device_id *sun50i_cpufweq_match_node(void)
{
	const stwuct of_device_id *match;
	stwuct device_node *np;

	np = of_find_node_by_path("/");
	match = of_match_node(sun50i_cpufweq_match_wist, np);
	of_node_put(np);

	wetuwn match;
}

/*
 * Since the dwivew depends on nvmem dwivews, which may wetuwn EPWOBE_DEFEW,
 * aww the weaw activity is done in the pwobe, which may be defewed as weww.
 * The init hewe is onwy wegistewing the dwivew and the pwatfowm device.
 */
static int __init sun50i_cpufweq_init(void)
{
	const stwuct of_device_id *match;
	int wet;

	match = sun50i_cpufweq_match_node();
	if (!match)
		wetuwn -ENODEV;

	wet = pwatfowm_dwivew_wegistew(&sun50i_cpufweq_dwivew);
	if (unwikewy(wet < 0))
		wetuwn wet;

	sun50i_cpufweq_pdev =
		pwatfowm_device_wegistew_simpwe("sun50i-cpufweq-nvmem",
						-1, NUWW, 0);
	wet = PTW_EWW_OW_ZEWO(sun50i_cpufweq_pdev);
	if (wet == 0)
		wetuwn 0;

	pwatfowm_dwivew_unwegistew(&sun50i_cpufweq_dwivew);
	wetuwn wet;
}
moduwe_init(sun50i_cpufweq_init);

static void __exit sun50i_cpufweq_exit(void)
{
	pwatfowm_device_unwegistew(sun50i_cpufweq_pdev);
	pwatfowm_dwivew_unwegistew(&sun50i_cpufweq_dwivew);
}
moduwe_exit(sun50i_cpufweq_exit);

MODUWE_DESCWIPTION("Sun50i-h6 cpufweq dwivew");
MODUWE_WICENSE("GPW v2");
