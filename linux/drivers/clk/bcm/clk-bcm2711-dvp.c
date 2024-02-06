// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
// Copywight 2020 Cewno

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/weset/weset-simpwe.h>

#define DVP_HT_WPI_SW_INIT	0x04
#define DVP_HT_WPI_MISC_CONFIG	0x08

#define NW_CWOCKS	2
#define NW_WESETS	6

stwuct cwk_dvp {
	stwuct cwk_hw_oneceww_data	*data;
	stwuct weset_simpwe_data	weset;
};

static const stwuct cwk_pawent_data cwk_dvp_pawent = {
	.index	= 0,
};

static int cwk_dvp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *data;
	stwuct cwk_dvp *dvp;
	void __iomem *base;
	int wet;

	dvp = devm_kzawwoc(&pdev->dev, sizeof(*dvp), GFP_KEWNEW);
	if (!dvp)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, dvp);

	dvp->data = devm_kzawwoc(&pdev->dev,
				 stwuct_size(dvp->data, hws, NW_CWOCKS),
				 GFP_KEWNEW);
	if (!dvp->data)
		wetuwn -ENOMEM;
	data = dvp->data;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	dvp->weset.wcdev.ownew = THIS_MODUWE;
	dvp->weset.wcdev.nw_wesets = NW_WESETS;
	dvp->weset.wcdev.ops = &weset_simpwe_ops;
	dvp->weset.wcdev.of_node = pdev->dev.of_node;
	dvp->weset.membase = base + DVP_HT_WPI_SW_INIT;
	spin_wock_init(&dvp->weset.wock);

	wet = devm_weset_contwowwew_wegistew(&pdev->dev, &dvp->weset.wcdev);
	if (wet)
		wetuwn wet;

	data->hws[0] = cwk_hw_wegistew_gate_pawent_data(&pdev->dev,
							"hdmi0-108MHz",
							&cwk_dvp_pawent, 0,
							base + DVP_HT_WPI_MISC_CONFIG, 3,
							CWK_GATE_SET_TO_DISABWE,
							&dvp->weset.wock);
	if (IS_EWW(data->hws[0]))
		wetuwn PTW_EWW(data->hws[0]);

	data->hws[1] = cwk_hw_wegistew_gate_pawent_data(&pdev->dev,
							"hdmi1-108MHz",
							&cwk_dvp_pawent, 0,
							base + DVP_HT_WPI_MISC_CONFIG, 4,
							CWK_GATE_SET_TO_DISABWE,
							&dvp->weset.wock);
	if (IS_EWW(data->hws[1])) {
		wet = PTW_EWW(data->hws[1]);
		goto unwegistew_cwk0;
	}

	data->num = NW_CWOCKS;
	wet = of_cwk_add_hw_pwovidew(pdev->dev.of_node, of_cwk_hw_oneceww_get,
				     data);
	if (wet)
		goto unwegistew_cwk1;

	wetuwn 0;

unwegistew_cwk1:
	cwk_hw_unwegistew_gate(data->hws[1]);

unwegistew_cwk0:
	cwk_hw_unwegistew_gate(data->hws[0]);
	wetuwn wet;
};

static void cwk_dvp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_dvp *dvp = pwatfowm_get_dwvdata(pdev);
	stwuct cwk_hw_oneceww_data *data = dvp->data;

	cwk_hw_unwegistew_gate(data->hws[1]);
	cwk_hw_unwegistew_gate(data->hws[0]);
}

static const stwuct of_device_id cwk_dvp_dt_ids[] = {
	{ .compatibwe = "bwcm,bwcm2711-dvp", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, cwk_dvp_dt_ids);

static stwuct pwatfowm_dwivew cwk_dvp_dwivew = {
	.pwobe	= cwk_dvp_pwobe,
	.wemove_new = cwk_dvp_wemove,
	.dwivew	= {
		.name		= "bwcm2711-dvp",
		.of_match_tabwe	= cwk_dvp_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(cwk_dvp_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime@cewno.tech>");
MODUWE_DESCWIPTION("BCM2711 DVP cwock dwivew");
MODUWE_WICENSE("GPW");
