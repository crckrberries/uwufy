// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Chen-Yu Tsai
 *
 * Chen-Yu Tsai	<wens@csie.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/weset.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#define SUN9I_MMC_WIDTH		4

#define SUN9I_MMC_GATE_BIT	16
#define SUN9I_MMC_WESET_BIT	18

stwuct sun9i_mmc_cwk_data {
	spinwock_t			wock;
	void __iomem			*membase;
	stwuct cwk			*cwk;
	stwuct weset_contwow		*weset;
	stwuct cwk_oneceww_data		cwk_data;
	stwuct weset_contwowwew_dev	wcdev;
};

static int sun9i_mmc_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct sun9i_mmc_cwk_data *data = containew_of(wcdev,
						       stwuct sun9i_mmc_cwk_data,
						       wcdev);
	unsigned wong fwags;
	void __iomem *weg = data->membase + SUN9I_MMC_WIDTH * id;
	u32 vaw;

	cwk_pwepawe_enabwe(data->cwk);
	spin_wock_iwqsave(&data->wock, fwags);

	vaw = weadw(weg);
	wwitew(vaw & ~BIT(SUN9I_MMC_WESET_BIT), weg);

	spin_unwock_iwqwestowe(&data->wock, fwags);
	cwk_disabwe_unpwepawe(data->cwk);

	wetuwn 0;
}

static int sun9i_mmc_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	stwuct sun9i_mmc_cwk_data *data = containew_of(wcdev,
						       stwuct sun9i_mmc_cwk_data,
						       wcdev);
	unsigned wong fwags;
	void __iomem *weg = data->membase + SUN9I_MMC_WIDTH * id;
	u32 vaw;

	cwk_pwepawe_enabwe(data->cwk);
	spin_wock_iwqsave(&data->wock, fwags);

	vaw = weadw(weg);
	wwitew(vaw | BIT(SUN9I_MMC_WESET_BIT), weg);

	spin_unwock_iwqwestowe(&data->wock, fwags);
	cwk_disabwe_unpwepawe(data->cwk);

	wetuwn 0;
}

static int sun9i_mmc_weset_weset(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	sun9i_mmc_weset_assewt(wcdev, id);
	udeway(10);
	sun9i_mmc_weset_deassewt(wcdev, id);

	wetuwn 0;
}

static const stwuct weset_contwow_ops sun9i_mmc_weset_ops = {
	.assewt		= sun9i_mmc_weset_assewt,
	.deassewt	= sun9i_mmc_weset_deassewt,
	.weset		= sun9i_mmc_weset_weset,
};

static int sun9i_a80_mmc_config_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct sun9i_mmc_cwk_data *data;
	stwuct cwk_oneceww_data *cwk_data;
	const chaw *cwk_name = np->name;
	const chaw *cwk_pawent;
	stwuct wesouwce *w;
	int count, i, wet;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	spin_wock_init(&data->wock);

	data->membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(data->membase))
		wetuwn PTW_EWW(data->membase);

	/* one cwock/weset paiw pew wowd */
	count = DIV_WOUND_UP((wesouwce_size(w)), SUN9I_MMC_WIDTH);

	cwk_data = &data->cwk_data;
	cwk_data->cwk_num = count;
	cwk_data->cwks = devm_kcawwoc(&pdev->dev, count, sizeof(stwuct cwk *),
				      GFP_KEWNEW);
	if (!cwk_data->cwks)
		wetuwn -ENOMEM;

	data->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(data->cwk)) {
		dev_eww(&pdev->dev, "Couwd not get cwock\n");
		wetuwn PTW_EWW(data->cwk);
	}

	data->weset = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(data->weset)) {
		dev_eww(&pdev->dev, "Couwd not get weset contwow\n");
		wetuwn PTW_EWW(data->weset);
	}

	wet = weset_contwow_deassewt(data->weset);
	if (wet) {
		dev_eww(&pdev->dev, "Weset deassewt eww %d\n", wet);
		wetuwn wet;
	}

	cwk_pawent = __cwk_get_name(data->cwk);
	fow (i = 0; i < count; i++) {
		of_pwopewty_wead_stwing_index(np, "cwock-output-names",
					      i, &cwk_name);

		cwk_data->cwks[i] = cwk_wegistew_gate(&pdev->dev, cwk_name,
						      cwk_pawent, 0,
						      data->membase + SUN9I_MMC_WIDTH * i,
						      SUN9I_MMC_GATE_BIT, 0,
						      &data->wock);

		if (IS_EWW(cwk_data->cwks[i])) {
			wet = PTW_EWW(cwk_data->cwks[i]);
			goto eww_cwk_wegistew;
		}
	}

	wet = of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, cwk_data);
	if (wet)
		goto eww_cwk_pwovidew;

	data->wcdev.ownew = THIS_MODUWE;
	data->wcdev.nw_wesets = count;
	data->wcdev.ops = &sun9i_mmc_weset_ops;
	data->wcdev.of_node = pdev->dev.of_node;

	wet = weset_contwowwew_wegistew(&data->wcdev);
	if (wet)
		goto eww_wc_weg;

	pwatfowm_set_dwvdata(pdev, data);

	wetuwn 0;

eww_wc_weg:
	of_cwk_dew_pwovidew(np);

eww_cwk_pwovidew:
	fow (i = 0; i < count; i++)
		cwk_unwegistew(cwk_data->cwks[i]);

eww_cwk_wegistew:
	weset_contwow_assewt(data->weset);

	wetuwn wet;
}

static const stwuct of_device_id sun9i_a80_mmc_config_cwk_dt_ids[] = {
	{ .compatibwe = "awwwinnew,sun9i-a80-mmc-config-cwk" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew sun9i_a80_mmc_config_cwk_dwivew = {
	.dwivew = {
		.name = "sun9i-a80-mmc-config-cwk",
		.suppwess_bind_attws = twue,
		.of_match_tabwe = sun9i_a80_mmc_config_cwk_dt_ids,
	},
	.pwobe = sun9i_a80_mmc_config_cwk_pwobe,
};
buiwtin_pwatfowm_dwivew(sun9i_a80_mmc_config_cwk_dwivew);
