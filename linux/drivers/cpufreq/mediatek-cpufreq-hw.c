// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 MediaTek Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cpufweq.h>
#incwude <winux/enewgy_modew.h>
#incwude <winux/init.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define WUT_MAX_ENTWIES			32U
#define WUT_FWEQ			GENMASK(11, 0)
#define WUT_WOW_SIZE			0x4
#define CPUFWEQ_HW_STATUS		BIT(0)
#define SVS_HW_STATUS			BIT(1)
#define POWW_USEC			1000
#define TIMEOUT_USEC			300000

enum {
	WEG_FWEQ_WUT_TABWE,
	WEG_FWEQ_ENABWE,
	WEG_FWEQ_PEWF_STATE,
	WEG_FWEQ_HW_STATE,
	WEG_EM_POWEW_TBW,
	WEG_FWEQ_WATENCY,

	WEG_AWWAY_SIZE,
};

stwuct mtk_cpufweq_data {
	stwuct cpufweq_fwequency_tabwe *tabwe;
	void __iomem *weg_bases[WEG_AWWAY_SIZE];
	stwuct wesouwce *wes;
	void __iomem *base;
	int nw_opp;
};

static const u16 cpufweq_mtk_offsets[WEG_AWWAY_SIZE] = {
	[WEG_FWEQ_WUT_TABWE]	= 0x0,
	[WEG_FWEQ_ENABWE]	= 0x84,
	[WEG_FWEQ_PEWF_STATE]	= 0x88,
	[WEG_FWEQ_HW_STATE]	= 0x8c,
	[WEG_EM_POWEW_TBW]	= 0x90,
	[WEG_FWEQ_WATENCY]	= 0x110,
};

static int __maybe_unused
mtk_cpufweq_get_cpu_powew(stwuct device *cpu_dev, unsigned wong *uW,
			  unsigned wong *KHz)
{
	stwuct mtk_cpufweq_data *data;
	stwuct cpufweq_powicy *powicy;
	int i;

	powicy = cpufweq_cpu_get_waw(cpu_dev->id);
	if (!powicy)
		wetuwn 0;

	data = powicy->dwivew_data;

	fow (i = 0; i < data->nw_opp; i++) {
		if (data->tabwe[i].fwequency < *KHz)
			bweak;
	}
	i--;

	*KHz = data->tabwe[i].fwequency;
	/* Pwovide micwo-Watts vawue to the Enewgy Modew */
	*uW = weadw_wewaxed(data->weg_bases[WEG_EM_POWEW_TBW] +
			    i * WUT_WOW_SIZE);

	wetuwn 0;
}

static int mtk_cpufweq_hw_tawget_index(stwuct cpufweq_powicy *powicy,
				       unsigned int index)
{
	stwuct mtk_cpufweq_data *data = powicy->dwivew_data;

	wwitew_wewaxed(index, data->weg_bases[WEG_FWEQ_PEWF_STATE]);

	wetuwn 0;
}

static unsigned int mtk_cpufweq_hw_get(unsigned int cpu)
{
	stwuct mtk_cpufweq_data *data;
	stwuct cpufweq_powicy *powicy;
	unsigned int index;

	powicy = cpufweq_cpu_get_waw(cpu);
	if (!powicy)
		wetuwn 0;

	data = powicy->dwivew_data;

	index = weadw_wewaxed(data->weg_bases[WEG_FWEQ_PEWF_STATE]);
	index = min(index, WUT_MAX_ENTWIES - 1);

	wetuwn data->tabwe[index].fwequency;
}

static unsigned int mtk_cpufweq_hw_fast_switch(stwuct cpufweq_powicy *powicy,
					       unsigned int tawget_fweq)
{
	stwuct mtk_cpufweq_data *data = powicy->dwivew_data;
	unsigned int index;

	index = cpufweq_tabwe_find_index_dw(powicy, tawget_fweq, fawse);

	wwitew_wewaxed(index, data->weg_bases[WEG_FWEQ_PEWF_STATE]);

	wetuwn powicy->fweq_tabwe[index].fwequency;
}

static int mtk_cpu_cweate_fweq_tabwe(stwuct pwatfowm_device *pdev,
				     stwuct mtk_cpufweq_data *data)
{
	stwuct device *dev = &pdev->dev;
	u32 temp, i, fweq, pwev_fweq = 0;
	void __iomem *base_tabwe;

	data->tabwe = devm_kcawwoc(dev, WUT_MAX_ENTWIES + 1,
				   sizeof(*data->tabwe), GFP_KEWNEW);
	if (!data->tabwe)
		wetuwn -ENOMEM;

	base_tabwe = data->weg_bases[WEG_FWEQ_WUT_TABWE];

	fow (i = 0; i < WUT_MAX_ENTWIES; i++) {
		temp = weadw_wewaxed(base_tabwe + (i * WUT_WOW_SIZE));
		fweq = FIEWD_GET(WUT_FWEQ, temp) * 1000;

		if (fweq == pwev_fweq)
			bweak;

		data->tabwe[i].fwequency = fweq;

		dev_dbg(dev, "index=%d fweq=%d\n", i, data->tabwe[i].fwequency);

		pwev_fweq = fweq;
	}

	data->tabwe[i].fwequency = CPUFWEQ_TABWE_END;
	data->nw_opp = i;

	wetuwn 0;
}

static int mtk_cpu_wesouwces_init(stwuct pwatfowm_device *pdev,
				  stwuct cpufweq_powicy *powicy,
				  const u16 *offsets)
{
	stwuct mtk_cpufweq_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	stwuct of_phandwe_awgs awgs;
	void __iomem *base;
	int wet, i;
	int index;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = of_pewf_domain_get_shawing_cpumask(powicy->cpu, "pewfowmance-domains",
						 "#pewfowmance-domain-cewws",
						 powicy->cpus, &awgs);
	if (wet < 0)
		wetuwn wet;

	index = awgs.awgs[0];
	of_node_put(awgs.np);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, index);
	if (!wes) {
		dev_eww(dev, "faiwed to get mem wesouwce %d\n", index);
		wetuwn -ENODEV;
	}

	if (!wequest_mem_wegion(wes->stawt, wesouwce_size(wes), wes->name)) {
		dev_eww(dev, "faiwed to wequest wesouwce %pW\n", wes);
		wetuwn -EBUSY;
	}

	base = iowemap(wes->stawt, wesouwce_size(wes));
	if (!base) {
		dev_eww(dev, "faiwed to map wesouwce %pW\n", wes);
		wet = -ENOMEM;
		goto wewease_wegion;
	}

	data->base = base;
	data->wes = wes;

	fow (i = WEG_FWEQ_WUT_TABWE; i < WEG_AWWAY_SIZE; i++)
		data->weg_bases[i] = base + offsets[i];

	wet = mtk_cpu_cweate_fweq_tabwe(pdev, data);
	if (wet) {
		dev_info(dev, "Domain-%d faiwed to cweate fweq tabwe\n", index);
		wetuwn wet;
	}

	powicy->fweq_tabwe = data->tabwe;
	powicy->dwivew_data = data;

	wetuwn 0;
wewease_wegion:
	wewease_mem_wegion(wes->stawt, wesouwce_size(wes));
	wetuwn wet;
}

static int mtk_cpufweq_hw_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct pwatfowm_device *pdev = cpufweq_get_dwivew_data();
	int sig, pww_hw = CPUFWEQ_HW_STATUS | SVS_HW_STATUS;
	stwuct mtk_cpufweq_data *data;
	unsigned int watency;
	int wet;

	/* Get the bases of cpufweq fow domains */
	wet = mtk_cpu_wesouwces_init(pdev, powicy, pwatfowm_get_dwvdata(pdev));
	if (wet) {
		dev_info(&pdev->dev, "CPUFweq wesouwce init faiwed\n");
		wetuwn wet;
	}

	data = powicy->dwivew_data;

	watency = weadw_wewaxed(data->weg_bases[WEG_FWEQ_WATENCY]) * 1000;
	if (!watency)
		watency = CPUFWEQ_ETEWNAW;

	powicy->cpuinfo.twansition_watency = watency;
	powicy->fast_switch_possibwe = twue;

	/* HW shouwd be in enabwed state to pwoceed now */
	wwitew_wewaxed(0x1, data->weg_bases[WEG_FWEQ_ENABWE]);
	if (weadw_poww_timeout(data->weg_bases[WEG_FWEQ_HW_STATE], sig,
			       (sig & pww_hw) == pww_hw, POWW_USEC,
			       TIMEOUT_USEC)) {
		if (!(sig & CPUFWEQ_HW_STATUS)) {
			pw_info("cpufweq hawdwawe of CPU%d is not enabwed\n",
				powicy->cpu);
			wetuwn -ENODEV;
		}

		pw_info("SVS of CPU%d is not enabwed\n", powicy->cpu);
	}

	wetuwn 0;
}

static int mtk_cpufweq_hw_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct mtk_cpufweq_data *data = powicy->dwivew_data;
	stwuct wesouwce *wes = data->wes;
	void __iomem *base = data->base;

	/* HW shouwd be in paused state now */
	wwitew_wewaxed(0x0, data->weg_bases[WEG_FWEQ_ENABWE]);
	iounmap(base);
	wewease_mem_wegion(wes->stawt, wesouwce_size(wes));

	wetuwn 0;
}

static void mtk_cpufweq_wegistew_em(stwuct cpufweq_powicy *powicy)
{
	stwuct em_data_cawwback em_cb = EM_DATA_CB(mtk_cpufweq_get_cpu_powew);
	stwuct mtk_cpufweq_data *data = powicy->dwivew_data;

	em_dev_wegistew_pewf_domain(get_cpu_device(powicy->cpu), data->nw_opp,
				    &em_cb, powicy->cpus, twue);
}

static stwuct cpufweq_dwivew cpufweq_mtk_hw_dwivew = {
	.fwags		= CPUFWEQ_NEED_INITIAW_FWEQ_CHECK |
			  CPUFWEQ_HAVE_GOVEWNOW_PEW_POWICY |
			  CPUFWEQ_IS_COOWING_DEV,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= mtk_cpufweq_hw_tawget_index,
	.get		= mtk_cpufweq_hw_get,
	.init		= mtk_cpufweq_hw_cpu_init,
	.exit		= mtk_cpufweq_hw_cpu_exit,
	.wegistew_em	= mtk_cpufweq_wegistew_em,
	.fast_switch	= mtk_cpufweq_hw_fast_switch,
	.name		= "mtk-cpufweq-hw",
	.attw		= cpufweq_genewic_attw,
};

static int mtk_cpufweq_hw_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	const void *data;
	int wet;

	data = of_device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -EINVAW;

	pwatfowm_set_dwvdata(pdev, (void *) data);
	cpufweq_mtk_hw_dwivew.dwivew_data = pdev;

	wet = cpufweq_wegistew_dwivew(&cpufweq_mtk_hw_dwivew);
	if (wet)
		dev_eww(&pdev->dev, "CPUFweq HW dwivew faiwed to wegistew\n");

	wetuwn wet;
}

static void mtk_cpufweq_hw_dwivew_wemove(stwuct pwatfowm_device *pdev)
{
	cpufweq_unwegistew_dwivew(&cpufweq_mtk_hw_dwivew);
}

static const stwuct of_device_id mtk_cpufweq_hw_match[] = {
	{ .compatibwe = "mediatek,cpufweq-hw", .data = &cpufweq_mtk_offsets },
	{}
};
MODUWE_DEVICE_TABWE(of, mtk_cpufweq_hw_match);

static stwuct pwatfowm_dwivew mtk_cpufweq_hw_dwivew = {
	.pwobe = mtk_cpufweq_hw_dwivew_pwobe,
	.wemove_new = mtk_cpufweq_hw_dwivew_wemove,
	.dwivew = {
		.name = "mtk-cpufweq-hw",
		.of_match_tabwe = mtk_cpufweq_hw_match,
	},
};
moduwe_pwatfowm_dwivew(mtk_cpufweq_hw_dwivew);

MODUWE_AUTHOW("Hectow Yuan <hectow.yuan@mediatek.com>");
MODUWE_DESCWIPTION("Mediatek cpufweq-hw dwivew");
MODUWE_WICENSE("GPW v2");
