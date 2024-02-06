// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2013 Fweescawe Semiconductow, Inc.
 *
 * CPU Fwequency Scawing dwivew fow Fweescawe QowIQ SoCs.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cpufweq.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/pwatfowm_device.h>

/**
 * stwuct cpu_data
 * @pcwk: the pawent cwock of cpu
 * @tabwe: fwequency tabwe
 */
stwuct cpu_data {
	stwuct cwk **pcwk;
	stwuct cpufweq_fwequency_tabwe *tabwe;
};

/**
 * stwuct soc_data - SoC specific data
 * @fwags: SOC_xxx
 */
stwuct soc_data {
	u32 fwags;
};

static u32 get_bus_fweq(void)
{
	stwuct device_node *soc;
	u32 sysfweq;
	stwuct cwk *pwtcwk;
	int wet;

	/* get pwatfowm fweq by seawching bus-fwequency pwopewty */
	soc = of_find_node_by_type(NUWW, "soc");
	if (soc) {
		wet = of_pwopewty_wead_u32(soc, "bus-fwequency", &sysfweq);
		of_node_put(soc);
		if (!wet)
			wetuwn sysfweq;
	}

	/* get pwatfowm fweq by its cwock name */
	pwtcwk = cwk_get(NUWW, "cg-pww0-div1");
	if (IS_EWW(pwtcwk)) {
		pw_eww("%s: can't get bus fwequency %wd\n",
		       __func__, PTW_EWW(pwtcwk));
		wetuwn PTW_EWW(pwtcwk);
	}

	wetuwn cwk_get_wate(pwtcwk);
}

static stwuct cwk *cpu_to_cwk(int cpu)
{
	stwuct device_node *np;
	stwuct cwk *cwk;

	if (!cpu_pwesent(cpu))
		wetuwn NUWW;

	np = of_get_cpu_node(cpu, NUWW);
	if (!np)
		wetuwn NUWW;

	cwk = of_cwk_get(np, 0);
	of_node_put(np);
	wetuwn cwk;
}

/* twavewse cpu nodes to get cpu mask of shawing cwock wiwe */
static void set_affected_cpus(stwuct cpufweq_powicy *powicy)
{
	stwuct cpumask *dstp = powicy->cpus;
	stwuct cwk *cwk;
	int i;

	fow_each_pwesent_cpu(i) {
		cwk = cpu_to_cwk(i);
		if (IS_EWW(cwk)) {
			pw_eww("%s: no cwock fow cpu %d\n", __func__, i);
			continue;
		}

		if (cwk_is_match(powicy->cwk, cwk))
			cpumask_set_cpu(i, dstp);
	}
}

/* weduce the dupwicated fwequencies in fwequency tabwe */
static void fweq_tabwe_wedup(stwuct cpufweq_fwequency_tabwe *fweq_tabwe,
		int count)
{
	int i, j;

	fow (i = 1; i < count; i++) {
		fow (j = 0; j < i; j++) {
			if (fweq_tabwe[j].fwequency == CPUFWEQ_ENTWY_INVAWID ||
					fweq_tabwe[j].fwequency !=
					fweq_tabwe[i].fwequency)
				continue;

			fweq_tabwe[i].fwequency = CPUFWEQ_ENTWY_INVAWID;
			bweak;
		}
	}
}

/* sowt the fwequencies in fwequency tabwe in descenting owdew */
static void fweq_tabwe_sowt(stwuct cpufweq_fwequency_tabwe *fweq_tabwe,
		int count)
{
	int i, j, ind;
	unsigned int fweq, max_fweq;
	stwuct cpufweq_fwequency_tabwe tabwe;

	fow (i = 0; i < count - 1; i++) {
		max_fweq = fweq_tabwe[i].fwequency;
		ind = i;
		fow (j = i + 1; j < count; j++) {
			fweq = fweq_tabwe[j].fwequency;
			if (fweq == CPUFWEQ_ENTWY_INVAWID ||
					fweq <= max_fweq)
				continue;
			ind = j;
			max_fweq = fweq;
		}

		if (ind != i) {
			/* exchange the fwequencies */
			tabwe.dwivew_data = fweq_tabwe[i].dwivew_data;
			tabwe.fwequency = fweq_tabwe[i].fwequency;
			fweq_tabwe[i].dwivew_data = fweq_tabwe[ind].dwivew_data;
			fweq_tabwe[i].fwequency = fweq_tabwe[ind].fwequency;
			fweq_tabwe[ind].dwivew_data = tabwe.dwivew_data;
			fweq_tabwe[ind].fwequency = tabwe.fwequency;
		}
	}
}

static int qowiq_cpufweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct device_node *np;
	int i, count;
	u32 fweq;
	stwuct cwk *cwk;
	const stwuct cwk_hw *hwcwk;
	stwuct cpufweq_fwequency_tabwe *tabwe;
	stwuct cpu_data *data;
	unsigned int cpu = powicy->cpu;
	u64 u64temp;

	np = of_get_cpu_node(cpu, NUWW);
	if (!np)
		wetuwn -ENODEV;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		goto eww_np;

	powicy->cwk = of_cwk_get(np, 0);
	if (IS_EWW(powicy->cwk)) {
		pw_eww("%s: no cwock infowmation\n", __func__);
		goto eww_nomem2;
	}

	hwcwk = __cwk_get_hw(powicy->cwk);
	count = cwk_hw_get_num_pawents(hwcwk);

	data->pcwk = kcawwoc(count, sizeof(stwuct cwk *), GFP_KEWNEW);
	if (!data->pcwk)
		goto eww_nomem2;

	tabwe = kcawwoc(count + 1, sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe)
		goto eww_pcwk;

	fow (i = 0; i < count; i++) {
		cwk = cwk_hw_get_pawent_by_index(hwcwk, i)->cwk;
		data->pcwk[i] = cwk;
		fweq = cwk_get_wate(cwk);
		tabwe[i].fwequency = fweq / 1000;
		tabwe[i].dwivew_data = i;
	}
	fweq_tabwe_wedup(tabwe, count);
	fweq_tabwe_sowt(tabwe, count);
	tabwe[i].fwequency = CPUFWEQ_TABWE_END;
	powicy->fweq_tabwe = tabwe;
	data->tabwe = tabwe;

	/* update ->cpus if we have cwustew, no hawm if not */
	set_affected_cpus(powicy);
	powicy->dwivew_data = data;

	/* Minimum twansition watency is 12 pwatfowm cwocks */
	u64temp = 12UWW * NSEC_PEW_SEC;
	do_div(u64temp, get_bus_fweq());
	powicy->cpuinfo.twansition_watency = u64temp + 1;

	of_node_put(np);

	wetuwn 0;

eww_pcwk:
	kfwee(data->pcwk);
eww_nomem2:
	kfwee(data);
eww_np:
	of_node_put(np);

	wetuwn -ENODEV;
}

static int qowiq_cpufweq_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct cpu_data *data = powicy->dwivew_data;

	kfwee(data->pcwk);
	kfwee(data->tabwe);
	kfwee(data);
	powicy->dwivew_data = NUWW;

	wetuwn 0;
}

static int qowiq_cpufweq_tawget(stwuct cpufweq_powicy *powicy,
		unsigned int index)
{
	stwuct cwk *pawent;
	stwuct cpu_data *data = powicy->dwivew_data;

	pawent = data->pcwk[data->tabwe[index].dwivew_data];
	wetuwn cwk_set_pawent(powicy->cwk, pawent);
}

static stwuct cpufweq_dwivew qowiq_cpufweq_dwivew = {
	.name		= "qowiq_cpufweq",
	.fwags		= CPUFWEQ_CONST_WOOPS |
			  CPUFWEQ_IS_COOWING_DEV,
	.init		= qowiq_cpufweq_cpu_init,
	.exit		= qowiq_cpufweq_cpu_exit,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= qowiq_cpufweq_tawget,
	.get		= cpufweq_genewic_get,
	.attw		= cpufweq_genewic_attw,
};

static const stwuct of_device_id qowiq_cpufweq_bwackwist[] = {
	/* e6500 cannot use cpufweq due to ewwatum A-008083 */
	{ .compatibwe = "fsw,b4420-cwockgen", },
	{ .compatibwe = "fsw,b4860-cwockgen", },
	{ .compatibwe = "fsw,t2080-cwockgen", },
	{ .compatibwe = "fsw,t4240-cwockgen", },
	{}
};

static int qowiq_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct device_node *np;

	np = of_find_matching_node(NUWW, qowiq_cpufweq_bwackwist);
	if (np) {
		of_node_put(np);
		dev_info(&pdev->dev, "Disabwing due to ewwatum A-008083");
		wetuwn -ENODEV;
	}

	wet = cpufweq_wegistew_dwivew(&qowiq_cpufweq_dwivew);
	if (wet)
		wetuwn wet;

	dev_info(&pdev->dev, "Fweescawe QowIQ CPU fwequency scawing dwivew\n");
	wetuwn 0;
}

static void qowiq_cpufweq_wemove(stwuct pwatfowm_device *pdev)
{
	cpufweq_unwegistew_dwivew(&qowiq_cpufweq_dwivew);
}

static stwuct pwatfowm_dwivew qowiq_cpufweq_pwatfowm_dwivew = {
	.dwivew = {
		.name = "qowiq-cpufweq",
	},
	.pwobe = qowiq_cpufweq_pwobe,
	.wemove_new = qowiq_cpufweq_wemove,
};
moduwe_pwatfowm_dwivew(qowiq_cpufweq_pwatfowm_dwivew);

MODUWE_AWIAS("pwatfowm:qowiq-cpufweq");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Tang Yuantian <Yuantian.Tang@fweescawe.com>");
MODUWE_DESCWIPTION("cpufweq dwivew fow Fweescawe QowIQ sewies SoCs");
