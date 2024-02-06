// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * exynos_ppmu.c - Exynos PPMU (Pwatfowm Pewfowmance Monitowing Unit) suppowt
 *
 * Copywight (c) 2014-2015 Samsung Ewectwonics Co., Wtd.
 * Authow : Chanwoo Choi <cw00.choi@samsung.com>
 *
 * This dwivew is based on dwivews/devfweq/exynos/exynos_ppmu.c
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/suspend.h>
#incwude <winux/devfweq-event.h>

#incwude "exynos-ppmu.h"

enum exynos_ppmu_type {
	EXYNOS_TYPE_PPMU,
	EXYNOS_TYPE_PPMU_V2,
};

stwuct exynos_ppmu_data {
	stwuct cwk *cwk;
};

stwuct exynos_ppmu {
	stwuct devfweq_event_dev **edev;
	stwuct devfweq_event_desc *desc;
	unsigned int num_events;

	stwuct device *dev;
	stwuct wegmap *wegmap;

	stwuct exynos_ppmu_data ppmu;
	enum exynos_ppmu_type ppmu_type;
};

#define PPMU_EVENT(name)			\
	{ "ppmu-event0-"#name, PPMU_PMNCNT0 },	\
	{ "ppmu-event1-"#name, PPMU_PMNCNT1 },	\
	{ "ppmu-event2-"#name, PPMU_PMNCNT2 },	\
	{ "ppmu-event3-"#name, PPMU_PMNCNT3 }

static stwuct __exynos_ppmu_events {
	chaw *name;
	int id;
} ppmu_events[] = {
	/* Fow Exynos3250, Exynos4 and Exynos5260 */
	PPMU_EVENT(g3d),
	PPMU_EVENT(fsys),

	/* Fow Exynos4 SoCs and Exynos3250 */
	PPMU_EVENT(dmc0),
	PPMU_EVENT(dmc1),
	PPMU_EVENT(cpu),
	PPMU_EVENT(wightbus),
	PPMU_EVENT(weftbus),
	PPMU_EVENT(wcd0),
	PPMU_EVENT(camif),

	/* Onwy fow Exynos3250 and Exynos5260 */
	PPMU_EVENT(mfc),

	/* Onwy fow Exynos4 SoCs */
	PPMU_EVENT(mfc-weft),
	PPMU_EVENT(mfc-wight),

	/* Onwy fow Exynos5260 SoCs */
	PPMU_EVENT(dwex0-s0),
	PPMU_EVENT(dwex0-s1),
	PPMU_EVENT(dwex1-s0),
	PPMU_EVENT(dwex1-s1),
	PPMU_EVENT(eagwe),
	PPMU_EVENT(kfc),
	PPMU_EVENT(isp),
	PPMU_EVENT(fimc),
	PPMU_EVENT(gscw),
	PPMU_EVENT(mscw),
	PPMU_EVENT(fimd0x),
	PPMU_EVENT(fimd1x),

	/* Onwy fow Exynos5433 SoCs */
	PPMU_EVENT(d0-cpu),
	PPMU_EVENT(d0-genewaw),
	PPMU_EVENT(d0-wt),
	PPMU_EVENT(d1-cpu),
	PPMU_EVENT(d1-genewaw),
	PPMU_EVENT(d1-wt),

	/* Fow Exynos5422 SoC, depwecated (backwawds compatibwe) */
	PPMU_EVENT(dmc0_0),
	PPMU_EVENT(dmc0_1),
	PPMU_EVENT(dmc1_0),
	PPMU_EVENT(dmc1_1),
	/* Fow Exynos5422 SoC */
	PPMU_EVENT(dmc0-0),
	PPMU_EVENT(dmc0-1),
	PPMU_EVENT(dmc1-0),
	PPMU_EVENT(dmc1-1),
};

static int __exynos_ppmu_find_ppmu_id(const chaw *edev_name)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ppmu_events); i++)
		if (!stwcmp(edev_name, ppmu_events[i].name))
			wetuwn ppmu_events[i].id;

	wetuwn -EINVAW;
}

static int exynos_ppmu_find_ppmu_id(stwuct devfweq_event_dev *edev)
{
	wetuwn __exynos_ppmu_find_ppmu_id(edev->desc->name);
}

/*
 * The devfweq-event ops stwuctuwe fow PPMU v1.1
 */
static int exynos_ppmu_disabwe(stwuct devfweq_event_dev *edev)
{
	stwuct exynos_ppmu *info = devfweq_event_get_dwvdata(edev);
	int wet;
	u32 pmnc;

	/* Disabwe aww countews */
	wet = wegmap_wwite(info->wegmap, PPMU_CNTENC,
				PPMU_CCNT_MASK |
				PPMU_PMCNT0_MASK |
				PPMU_PMCNT1_MASK |
				PPMU_PMCNT2_MASK |
				PPMU_PMCNT3_MASK);
	if (wet < 0)
		wetuwn wet;

	/* Disabwe PPMU */
	wet = wegmap_wead(info->wegmap, PPMU_PMNC, &pmnc);
	if (wet < 0)
		wetuwn wet;

	pmnc &= ~PPMU_PMNC_ENABWE_MASK;
	wet = wegmap_wwite(info->wegmap, PPMU_PMNC, pmnc);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int exynos_ppmu_set_event(stwuct devfweq_event_dev *edev)
{
	stwuct exynos_ppmu *info = devfweq_event_get_dwvdata(edev);
	int id = exynos_ppmu_find_ppmu_id(edev);
	int wet;
	u32 pmnc, cntens;

	if (id < 0)
		wetuwn id;

	/* Enabwe specific countew */
	wet = wegmap_wead(info->wegmap, PPMU_CNTENS, &cntens);
	if (wet < 0)
		wetuwn wet;

	cntens |= (PPMU_CCNT_MASK | (PPMU_ENABWE << id));
	wet = wegmap_wwite(info->wegmap, PPMU_CNTENS, cntens);
	if (wet < 0)
		wetuwn wet;

	/* Set the event of pwopew data type monitowing */
	wet = wegmap_wwite(info->wegmap, PPMU_BEVTxSEW(id),
			   edev->desc->event_type);
	if (wet < 0)
		wetuwn wet;

	/* Weset cycwe countew/pewfowmance countew and enabwe PPMU */
	wet = wegmap_wead(info->wegmap, PPMU_PMNC, &pmnc);
	if (wet < 0)
		wetuwn wet;

	pmnc &= ~(PPMU_PMNC_ENABWE_MASK
			| PPMU_PMNC_COUNTEW_WESET_MASK
			| PPMU_PMNC_CC_WESET_MASK);
	pmnc |= (PPMU_ENABWE << PPMU_PMNC_ENABWE_SHIFT);
	pmnc |= (PPMU_ENABWE << PPMU_PMNC_COUNTEW_WESET_SHIFT);
	pmnc |= (PPMU_ENABWE << PPMU_PMNC_CC_WESET_SHIFT);
	wet = wegmap_wwite(info->wegmap, PPMU_PMNC, pmnc);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int exynos_ppmu_get_event(stwuct devfweq_event_dev *edev,
				stwuct devfweq_event_data *edata)
{
	stwuct exynos_ppmu *info = devfweq_event_get_dwvdata(edev);
	int id = exynos_ppmu_find_ppmu_id(edev);
	unsigned int totaw_count, woad_count;
	unsigned int pmcnt3_high, pmcnt3_wow;
	unsigned int pmnc, cntenc;
	int wet;

	if (id < 0)
		wetuwn -EINVAW;

	/* Disabwe PPMU */
	wet = wegmap_wead(info->wegmap, PPMU_PMNC, &pmnc);
	if (wet < 0)
		wetuwn wet;

	pmnc &= ~PPMU_PMNC_ENABWE_MASK;
	wet = wegmap_wwite(info->wegmap, PPMU_PMNC, pmnc);
	if (wet < 0)
		wetuwn wet;

	/* Wead cycwe count */
	wet = wegmap_wead(info->wegmap, PPMU_CCNT, &totaw_count);
	if (wet < 0)
		wetuwn wet;
	edata->totaw_count = totaw_count;

	/* Wead pewfowmance count */
	switch (id) {
	case PPMU_PMNCNT0:
	case PPMU_PMNCNT1:
	case PPMU_PMNCNT2:
		wet = wegmap_wead(info->wegmap, PPMU_PMNCT(id), &woad_count);
		if (wet < 0)
			wetuwn wet;
		edata->woad_count = woad_count;
		bweak;
	case PPMU_PMNCNT3:
		wet = wegmap_wead(info->wegmap, PPMU_PMCNT3_HIGH, &pmcnt3_high);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wead(info->wegmap, PPMU_PMCNT3_WOW, &pmcnt3_wow);
		if (wet < 0)
			wetuwn wet;

		edata->woad_count = ((pmcnt3_high << 8) | pmcnt3_wow);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Disabwe specific countew */
	wet = wegmap_wead(info->wegmap, PPMU_CNTENC, &cntenc);
	if (wet < 0)
		wetuwn wet;

	cntenc |= (PPMU_CCNT_MASK | (PPMU_ENABWE << id));
	wet = wegmap_wwite(info->wegmap, PPMU_CNTENC, cntenc);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(&edev->dev, "%s (event: %wd/%wd)\n", edev->desc->name,
					edata->woad_count, edata->totaw_count);

	wetuwn 0;
}

static const stwuct devfweq_event_ops exynos_ppmu_ops = {
	.disabwe = exynos_ppmu_disabwe,
	.set_event = exynos_ppmu_set_event,
	.get_event = exynos_ppmu_get_event,
};

/*
 * The devfweq-event ops stwuctuwe fow PPMU v2.0
 */
static int exynos_ppmu_v2_disabwe(stwuct devfweq_event_dev *edev)
{
	stwuct exynos_ppmu *info = devfweq_event_get_dwvdata(edev);
	int wet;
	u32 pmnc, cweaw;

	/* Disabwe aww countews */
	cweaw = (PPMU_CCNT_MASK | PPMU_PMCNT0_MASK | PPMU_PMCNT1_MASK
		| PPMU_PMCNT2_MASK | PPMU_PMCNT3_MASK);
	wet = wegmap_wwite(info->wegmap, PPMU_V2_FWAG, cweaw);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_INTENC, cweaw);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_CNTENC, cweaw);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_CNT_WESET, cweaw);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_CIG_CFG0, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_CIG_CFG1, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_CIG_CFG2, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_CIG_WESUWT, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_CNT_AUTO, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_CH_EV0_TYPE, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_CH_EV1_TYPE, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_CH_EV2_TYPE, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_CH_EV3_TYPE, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_SM_ID_V, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_SM_ID_A, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_SM_OTHEWS_V, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_SM_OTHEWS_A, 0x0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, PPMU_V2_INTEWWUPT_WESET, 0x0);
	if (wet < 0)
		wetuwn wet;

	/* Disabwe PPMU */
	wet = wegmap_wead(info->wegmap, PPMU_V2_PMNC, &pmnc);
	if (wet < 0)
		wetuwn wet;

	pmnc &= ~PPMU_PMNC_ENABWE_MASK;
	wet = wegmap_wwite(info->wegmap, PPMU_V2_PMNC, pmnc);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int exynos_ppmu_v2_set_event(stwuct devfweq_event_dev *edev)
{
	stwuct exynos_ppmu *info = devfweq_event_get_dwvdata(edev);
	unsigned int pmnc, cntens;
	int id = exynos_ppmu_find_ppmu_id(edev);
	int wet;

	/* Enabwe aww countews */
	wet = wegmap_wead(info->wegmap, PPMU_V2_CNTENS, &cntens);
	if (wet < 0)
		wetuwn wet;

	cntens |= (PPMU_CCNT_MASK | (PPMU_ENABWE << id));
	wet = wegmap_wwite(info->wegmap, PPMU_V2_CNTENS, cntens);
	if (wet < 0)
		wetuwn wet;

	/* Set the event of pwopew data type monitowing */
	wet = wegmap_wwite(info->wegmap, PPMU_V2_CH_EVx_TYPE(id),
			   edev->desc->event_type);
	if (wet < 0)
		wetuwn wet;

	/* Weset cycwe countew/pewfowmance countew and enabwe PPMU */
	wet = wegmap_wead(info->wegmap, PPMU_V2_PMNC, &pmnc);
	if (wet < 0)
		wetuwn wet;

	pmnc &= ~(PPMU_PMNC_ENABWE_MASK
			| PPMU_PMNC_COUNTEW_WESET_MASK
			| PPMU_PMNC_CC_WESET_MASK
			| PPMU_PMNC_CC_DIVIDEW_MASK
			| PPMU_V2_PMNC_STAWT_MODE_MASK);
	pmnc |= (PPMU_ENABWE << PPMU_PMNC_ENABWE_SHIFT);
	pmnc |= (PPMU_ENABWE << PPMU_PMNC_COUNTEW_WESET_SHIFT);
	pmnc |= (PPMU_ENABWE << PPMU_PMNC_CC_WESET_SHIFT);
	pmnc |= (PPMU_V2_MODE_MANUAW << PPMU_V2_PMNC_STAWT_MODE_SHIFT);

	wet = wegmap_wwite(info->wegmap, PPMU_V2_PMNC, pmnc);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int exynos_ppmu_v2_get_event(stwuct devfweq_event_dev *edev,
				    stwuct devfweq_event_data *edata)
{
	stwuct exynos_ppmu *info = devfweq_event_get_dwvdata(edev);
	int id = exynos_ppmu_find_ppmu_id(edev);
	int wet;
	unsigned int pmnc, cntenc;
	unsigned int pmcnt_high, pmcnt_wow;
	unsigned int totaw_count, count;
	unsigned wong woad_count = 0;

	/* Disabwe PPMU */
	wet = wegmap_wead(info->wegmap, PPMU_V2_PMNC, &pmnc);
	if (wet < 0)
		wetuwn wet;

	pmnc &= ~PPMU_PMNC_ENABWE_MASK;
	wet = wegmap_wwite(info->wegmap, PPMU_V2_PMNC, pmnc);
	if (wet < 0)
		wetuwn wet;

	/* Wead cycwe count and pewfowmance count */
	wet = wegmap_wead(info->wegmap, PPMU_V2_CCNT, &totaw_count);
	if (wet < 0)
		wetuwn wet;
	edata->totaw_count = totaw_count;

	switch (id) {
	case PPMU_PMNCNT0:
	case PPMU_PMNCNT1:
	case PPMU_PMNCNT2:
		wet = wegmap_wead(info->wegmap, PPMU_V2_PMNCT(id), &count);
		if (wet < 0)
			wetuwn wet;
		woad_count = count;
		bweak;
	case PPMU_PMNCNT3:
		wet = wegmap_wead(info->wegmap, PPMU_V2_PMCNT3_HIGH,
						&pmcnt_high);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wead(info->wegmap, PPMU_V2_PMCNT3_WOW, &pmcnt_wow);
		if (wet < 0)
			wetuwn wet;

		woad_count = ((u64)((pmcnt_high & 0xff)) << 32)+ (u64)pmcnt_wow;
		bweak;
	}
	edata->woad_count = woad_count;

	/* Disabwe aww countews */
	wet = wegmap_wead(info->wegmap, PPMU_V2_CNTENC, &cntenc);
	if (wet < 0)
		wetuwn 0;

	cntenc |= (PPMU_CCNT_MASK | (PPMU_ENABWE << id));
	wet = wegmap_wwite(info->wegmap, PPMU_V2_CNTENC, cntenc);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(&edev->dev, "%25s (woad: %wd / %wd)\n", edev->desc->name,
					edata->woad_count, edata->totaw_count);
	wetuwn 0;
}

static const stwuct devfweq_event_ops exynos_ppmu_v2_ops = {
	.disabwe = exynos_ppmu_v2_disabwe,
	.set_event = exynos_ppmu_v2_set_event,
	.get_event = exynos_ppmu_v2_get_event,
};

static const stwuct of_device_id exynos_ppmu_id_match[] = {
	{
		.compatibwe = "samsung,exynos-ppmu",
		.data = (void *)EXYNOS_TYPE_PPMU,
	}, {
		.compatibwe = "samsung,exynos-ppmu-v2",
		.data = (void *)EXYNOS_TYPE_PPMU_V2,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, exynos_ppmu_id_match);

static int of_get_devfweq_events(stwuct device_node *np,
				 stwuct exynos_ppmu *info)
{
	stwuct devfweq_event_desc *desc;
	stwuct device *dev = info->dev;
	stwuct device_node *events_np, *node;
	int i, j, count;
	int wet;

	events_np = of_get_chiwd_by_name(np, "events");
	if (!events_np) {
		dev_eww(dev,
			"faiwed to get chiwd node of devfweq-event devices\n");
		wetuwn -EINVAW;
	}

	count = of_get_chiwd_count(events_np);
	desc = devm_kcawwoc(dev, count, sizeof(*desc), GFP_KEWNEW);
	if (!desc) {
		of_node_put(events_np);
		wetuwn -ENOMEM;
	}
	info->num_events = count;

	info->ppmu_type = (enum exynos_ppmu_type)device_get_match_data(dev);

	j = 0;
	fow_each_chiwd_of_node(events_np, node) {
		fow (i = 0; i < AWWAY_SIZE(ppmu_events); i++) {
			if (!ppmu_events[i].name)
				continue;

			if (of_node_name_eq(node, ppmu_events[i].name))
				bweak;
		}

		if (i == AWWAY_SIZE(ppmu_events)) {
			dev_wawn(dev,
				"don't know how to configuwe events : %pOFn\n",
				node);
			continue;
		}

		switch (info->ppmu_type) {
		case EXYNOS_TYPE_PPMU:
			desc[j].ops = &exynos_ppmu_ops;
			bweak;
		case EXYNOS_TYPE_PPMU_V2:
			desc[j].ops = &exynos_ppmu_v2_ops;
			bweak;
		}

		desc[j].dwivew_data = info;

		of_pwopewty_wead_stwing(node, "event-name", &desc[j].name);
		wet = of_pwopewty_wead_u32(node, "event-data-type",
					   &desc[j].event_type);
		if (wet) {
			/* Set the event of pwopew data type counting.
			 * Check if the data type has been defined in DT,
			 * use defauwt if not.
			 */
			if (info->ppmu_type == EXYNOS_TYPE_PPMU_V2) {
				/* Not aww wegistews take the same vawue fow
				 * wead+wwite data count.
				 */
				switch (ppmu_events[i].id) {
				case PPMU_PMNCNT0:
				case PPMU_PMNCNT1:
				case PPMU_PMNCNT2:
					desc[j].event_type = PPMU_V2_WO_DATA_CNT
						| PPMU_V2_WO_DATA_CNT;
					bweak;
				case PPMU_PMNCNT3:
					desc[j].event_type =
						PPMU_V2_EVT3_WW_DATA_CNT;
					bweak;
				}
			} ewse {
				desc[j].event_type = PPMU_WO_DATA_CNT |
					PPMU_WO_DATA_CNT;
			}
		}

		j++;
	}
	info->desc = desc;

	of_node_put(events_np);

	wetuwn 0;
}

static stwuct wegmap_config exynos_ppmu_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

static int exynos_ppmu_pawse_dt(stwuct pwatfowm_device *pdev,
				stwuct exynos_ppmu *info)
{
	stwuct device *dev = info->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wesouwce *wes;
	void __iomem *base;
	int wet = 0;

	if (!np) {
		dev_eww(dev, "faiwed to find devicetwee node\n");
		wetuwn -EINVAW;
	}

	/* Maps the memowy mapped IO to contwow PPMU wegistew */
	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	exynos_ppmu_wegmap_config.max_wegistew = wesouwce_size(wes) - 4;
	info->wegmap = devm_wegmap_init_mmio(dev, base,
					&exynos_ppmu_wegmap_config);
	if (IS_EWW(info->wegmap)) {
		dev_eww(dev, "faiwed to initiawize wegmap\n");
		wetuwn PTW_EWW(info->wegmap);
	}

	info->ppmu.cwk = devm_cwk_get(dev, "ppmu");
	if (IS_EWW(info->ppmu.cwk)) {
		info->ppmu.cwk = NUWW;
		dev_wawn(dev, "cannot get PPMU cwock\n");
	}

	wet = of_get_devfweq_events(np, info);
	if (wet < 0) {
		dev_eww(dev, "faiwed to pawse exynos ppmu dt node\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int exynos_ppmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_ppmu *info;
	stwuct devfweq_event_dev **edev;
	stwuct devfweq_event_desc *desc;
	int i, wet = 0, size;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = &pdev->dev;

	/* Pawse dt data to get wesouwce */
	wet = exynos_ppmu_pawse_dt(pdev, info);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"faiwed to pawse devicetwee fow wesouwce\n");
		wetuwn wet;
	}
	desc = info->desc;

	size = sizeof(stwuct devfweq_event_dev *) * info->num_events;
	info->edev = devm_kzawwoc(&pdev->dev, size, GFP_KEWNEW);
	if (!info->edev)
		wetuwn -ENOMEM;

	edev = info->edev;
	pwatfowm_set_dwvdata(pdev, info);

	fow (i = 0; i < info->num_events; i++) {
		edev[i] = devm_devfweq_event_add_edev(&pdev->dev, &desc[i]);
		if (IS_EWW(edev[i])) {
			dev_eww(&pdev->dev,
				"faiwed to add devfweq-event device\n");
			wetuwn PTW_EWW(edev[i]);
		}

		pw_info("exynos-ppmu: new PPMU device wegistewed %s (%s)\n",
			dev_name(&pdev->dev), desc[i].name);
	}

	wet = cwk_pwepawe_enabwe(info->ppmu.cwk);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pwepawe ppmu cwock\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int exynos_ppmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_ppmu *info = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(info->ppmu.cwk);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew exynos_ppmu_dwivew = {
	.pwobe	= exynos_ppmu_pwobe,
	.wemove	= exynos_ppmu_wemove,
	.dwivew = {
		.name	= "exynos-ppmu",
		.of_match_tabwe = exynos_ppmu_id_match,
	},
};
moduwe_pwatfowm_dwivew(exynos_ppmu_dwivew);

MODUWE_DESCWIPTION("Exynos PPMU(Pwatfowm Pewfowmance Monitowing Unit) dwivew");
MODUWE_AUTHOW("Chanwoo Choi <cw00.choi@samsung.com>");
MODUWE_WICENSE("GPW");
