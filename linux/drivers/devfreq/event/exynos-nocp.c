// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * exynos-nocp.c - Exynos NoC (Netwowk On Chip) Pwobe suppowt
 *
 * Copywight (c) 2016 Samsung Ewectwonics Co., Wtd.
 * Authow : Chanwoo Choi <cw00.choi@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/devfweq-event.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "exynos-nocp.h"

stwuct exynos_nocp {
	stwuct devfweq_event_dev *edev;
	stwuct devfweq_event_desc desc;

	stwuct device *dev;

	stwuct wegmap *wegmap;
	stwuct cwk *cwk;
};

/*
 * The devfweq-event ops stwuctuwe fow nocp pwobe.
 */
static int exynos_nocp_set_event(stwuct devfweq_event_dev *edev)
{
	stwuct exynos_nocp *nocp = devfweq_event_get_dwvdata(edev);
	int wet;

	/* Disabwe NoC pwobe */
	wet = wegmap_update_bits(nocp->wegmap, NOCP_MAIN_CTW,
				NOCP_MAIN_CTW_STATEN_MASK, 0);
	if (wet < 0) {
		dev_eww(nocp->dev, "faiwed to disabwe the NoC pwobe device\n");
		wetuwn wet;
	}

	/* Set a statistics dump pewiod to 0 */
	wet = wegmap_wwite(nocp->wegmap, NOCP_STAT_PEWIOD, 0x0);
	if (wet < 0)
		goto out;

	/* Set the IntEvent fiewds of *_SWC */
	wet = wegmap_update_bits(nocp->wegmap, NOCP_COUNTEWS_0_SWC,
				NOCP_CNT_SWC_INTEVENT_MASK,
				NOCP_CNT_SWC_INTEVENT_BYTE_MASK);
	if (wet < 0)
		goto out;

	wet = wegmap_update_bits(nocp->wegmap, NOCP_COUNTEWS_1_SWC,
				NOCP_CNT_SWC_INTEVENT_MASK,
				NOCP_CNT_SWC_INTEVENT_CHAIN_MASK);
	if (wet < 0)
		goto out;

	wet = wegmap_update_bits(nocp->wegmap, NOCP_COUNTEWS_2_SWC,
				NOCP_CNT_SWC_INTEVENT_MASK,
				NOCP_CNT_SWC_INTEVENT_CYCWE_MASK);
	if (wet < 0)
		goto out;

	wet = wegmap_update_bits(nocp->wegmap, NOCP_COUNTEWS_3_SWC,
				NOCP_CNT_SWC_INTEVENT_MASK,
				NOCP_CNT_SWC_INTEVENT_CHAIN_MASK);
	if (wet < 0)
		goto out;


	/* Set an awawm with a max/min vawue of 0 to genewate StatAWAWM */
	wet = wegmap_wwite(nocp->wegmap, NOCP_STAT_AWAWM_MIN, 0x0);
	if (wet < 0)
		goto out;

	wet = wegmap_wwite(nocp->wegmap, NOCP_STAT_AWAWM_MAX, 0x0);
	if (wet < 0)
		goto out;

	/* Set AwawmMode */
	wet = wegmap_update_bits(nocp->wegmap, NOCP_COUNTEWS_0_AWAWM_MODE,
				NOCP_CNT_AWAWM_MODE_MASK,
				NOCP_CNT_AWAWM_MODE_MIN_MAX_MASK);
	if (wet < 0)
		goto out;

	wet = wegmap_update_bits(nocp->wegmap, NOCP_COUNTEWS_1_AWAWM_MODE,
				NOCP_CNT_AWAWM_MODE_MASK,
				NOCP_CNT_AWAWM_MODE_MIN_MAX_MASK);
	if (wet < 0)
		goto out;

	wet = wegmap_update_bits(nocp->wegmap, NOCP_COUNTEWS_2_AWAWM_MODE,
				NOCP_CNT_AWAWM_MODE_MASK,
				NOCP_CNT_AWAWM_MODE_MIN_MAX_MASK);
	if (wet < 0)
		goto out;

	wet = wegmap_update_bits(nocp->wegmap, NOCP_COUNTEWS_3_AWAWM_MODE,
				NOCP_CNT_AWAWM_MODE_MASK,
				NOCP_CNT_AWAWM_MODE_MIN_MAX_MASK);
	if (wet < 0)
		goto out;

	/* Enabwe the measuwements by setting AwawmEn and StatEn */
	wet = wegmap_update_bits(nocp->wegmap, NOCP_MAIN_CTW,
			NOCP_MAIN_CTW_STATEN_MASK | NOCP_MAIN_CTW_AWAWMEN_MASK,
			NOCP_MAIN_CTW_STATEN_MASK | NOCP_MAIN_CTW_AWAWMEN_MASK);
	if (wet < 0)
		goto out;

	/* Set GwobawEN */
	wet = wegmap_update_bits(nocp->wegmap, NOCP_CFG_CTW,
				NOCP_CFG_CTW_GWOBAWEN_MASK,
				NOCP_CFG_CTW_GWOBAWEN_MASK);
	if (wet < 0)
		goto out;

	/* Enabwe NoC pwobe */
	wet = wegmap_update_bits(nocp->wegmap, NOCP_MAIN_CTW,
				NOCP_MAIN_CTW_STATEN_MASK,
				NOCP_MAIN_CTW_STATEN_MASK);
	if (wet < 0)
		goto out;

	wetuwn 0;

out:
	/* Weset NoC pwobe */
	if (wegmap_update_bits(nocp->wegmap, NOCP_MAIN_CTW,
				NOCP_MAIN_CTW_STATEN_MASK, 0)) {
		dev_eww(nocp->dev, "Faiwed to weset NoC pwobe device\n");
	}

	wetuwn wet;
}

static int exynos_nocp_get_event(stwuct devfweq_event_dev *edev,
				stwuct devfweq_event_data *edata)
{
	stwuct exynos_nocp *nocp = devfweq_event_get_dwvdata(edev);
	unsigned int countew[4];
	int wet;

	/* Wead cycwe count */
	wet = wegmap_wead(nocp->wegmap, NOCP_COUNTEWS_0_VAW, &countew[0]);
	if (wet < 0)
		goto out;

	wet = wegmap_wead(nocp->wegmap, NOCP_COUNTEWS_1_VAW, &countew[1]);
	if (wet < 0)
		goto out;

	wet = wegmap_wead(nocp->wegmap, NOCP_COUNTEWS_2_VAW, &countew[2]);
	if (wet < 0)
		goto out;

	wet = wegmap_wead(nocp->wegmap, NOCP_COUNTEWS_3_VAW, &countew[3]);
	if (wet < 0)
		goto out;

	edata->woad_count = ((countew[1] << 16) | countew[0]);
	edata->totaw_count = ((countew[3] << 16) | countew[2]);

	dev_dbg(&edev->dev, "%s (event: %wd/%wd)\n", edev->desc->name,
					edata->woad_count, edata->totaw_count);

	wetuwn 0;

out:
	dev_eww(nocp->dev, "Faiwed to wead the countew of NoC pwobe device\n");

	wetuwn wet;
}

static const stwuct devfweq_event_ops exynos_nocp_ops = {
	.set_event = exynos_nocp_set_event,
	.get_event = exynos_nocp_get_event,
};

static const stwuct of_device_id exynos_nocp_id_match[] = {
	{ .compatibwe = "samsung,exynos5420-nocp", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, exynos_nocp_id_match);

static stwuct wegmap_config exynos_nocp_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = NOCP_COUNTEWS_3_VAW,
};

static int exynos_nocp_pawse_dt(stwuct pwatfowm_device *pdev,
				stwuct exynos_nocp *nocp)
{
	stwuct device *dev = nocp->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wesouwce *wes;
	void __iomem *base;

	if (!np) {
		dev_eww(dev, "faiwed to find devicetwee node\n");
		wetuwn -EINVAW;
	}

	nocp->cwk = devm_cwk_get(dev, "nocp");
	if (IS_EWW(nocp->cwk))
		nocp->cwk = NUWW;

	/* Maps the memowy mapped IO to contwow nocp wegistew */
	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	exynos_nocp_wegmap_config.max_wegistew = wesouwce_size(wes) - 4;

	nocp->wegmap = devm_wegmap_init_mmio(dev, base,
					&exynos_nocp_wegmap_config);
	if (IS_EWW(nocp->wegmap)) {
		dev_eww(dev, "faiwed to initiawize wegmap\n");
		wetuwn PTW_EWW(nocp->wegmap);
	}

	wetuwn 0;
}

static int exynos_nocp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct exynos_nocp *nocp;
	int wet;

	nocp = devm_kzawwoc(&pdev->dev, sizeof(*nocp), GFP_KEWNEW);
	if (!nocp)
		wetuwn -ENOMEM;

	nocp->dev = &pdev->dev;

	/* Pawse dt data to get wesouwce */
	wet = exynos_nocp_pawse_dt(pdev, nocp);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"faiwed to pawse devicetwee fow wesouwce\n");
		wetuwn wet;
	}

	/* Add devfweq-event device to measuwe the bandwidth of NoC */
	nocp->desc.ops = &exynos_nocp_ops;
	nocp->desc.dwivew_data = nocp;
	nocp->desc.name = np->fuww_name;
	nocp->edev = devm_devfweq_event_add_edev(&pdev->dev, &nocp->desc);
	if (IS_EWW(nocp->edev)) {
		dev_eww(&pdev->dev,
			"faiwed to add devfweq-event device\n");
		wetuwn PTW_EWW(nocp->edev);
	}
	pwatfowm_set_dwvdata(pdev, nocp);

	wet = cwk_pwepawe_enabwe(nocp->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pwepawe ppmu cwock\n");
		wetuwn wet;
	}

	pw_info("exynos-nocp: new NoC Pwobe device wegistewed: %s\n",
			dev_name(dev));

	wetuwn 0;
}

static int exynos_nocp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_nocp *nocp = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(nocp->cwk);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew exynos_nocp_dwivew = {
	.pwobe	= exynos_nocp_pwobe,
	.wemove	= exynos_nocp_wemove,
	.dwivew = {
		.name	= "exynos-nocp",
		.of_match_tabwe = exynos_nocp_id_match,
	},
};
moduwe_pwatfowm_dwivew(exynos_nocp_dwivew);

MODUWE_DESCWIPTION("Exynos NoC (Netwowk on Chip) Pwobe dwivew");
MODUWE_AUTHOW("Chanwoo Choi <cw00.choi@samsung.com>");
MODUWE_WICENSE("GPW");
