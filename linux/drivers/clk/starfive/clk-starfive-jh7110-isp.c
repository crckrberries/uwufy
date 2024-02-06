// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * StawFive JH7110 Image-Signaw-Pwocess Cwock Dwivew
 *
 * Copywight (C) 2022-2023 StawFive Technowogy Co., Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <dt-bindings/cwock/stawfive,jh7110-cwg.h>

#incwude "cwk-stawfive-jh7110.h"

/* extewnaw cwocks */
#define JH7110_ISPCWK_ISP_TOP_COWE		(JH7110_ISPCWK_END + 0)
#define JH7110_ISPCWK_ISP_TOP_AXI		(JH7110_ISPCWK_END + 1)
#define JH7110_ISPCWK_NOC_BUS_ISP_AXI		(JH7110_ISPCWK_END + 2)
#define JH7110_ISPCWK_DVP_CWK			(JH7110_ISPCWK_END + 3)
#define JH7110_ISPCWK_EXT_END			(JH7110_ISPCWK_END + 4)

static stwuct cwk_buwk_data jh7110_isp_top_cwks[] = {
	{ .id = "isp_top_cowe" },
	{ .id = "isp_top_axi" }
};

static const stwuct jh71x0_cwk_data jh7110_ispcwk_data[] = {
	/* syscon */
	JH71X0__DIV(JH7110_ISPCWK_DOM4_APB_FUNC, "dom4_apb_func", 15,
		    JH7110_ISPCWK_ISP_TOP_AXI),
	JH71X0__DIV(JH7110_ISPCWK_MIPI_WX0_PXW, "mipi_wx0_pxw", 8,
		    JH7110_ISPCWK_ISP_TOP_COWE),
	JH71X0__INV(JH7110_ISPCWK_DVP_INV, "dvp_inv", JH7110_ISPCWK_DVP_CWK),
	/* vin */
	JH71X0__DIV(JH7110_ISPCWK_M31DPHY_CFG_IN, "m31dphy_cfg_in", 16,
		    JH7110_ISPCWK_ISP_TOP_COWE),
	JH71X0__DIV(JH7110_ISPCWK_M31DPHY_WEF_IN, "m31dphy_wef_in", 16,
		    JH7110_ISPCWK_ISP_TOP_COWE),
	JH71X0__DIV(JH7110_ISPCWK_M31DPHY_TX_ESC_WAN0, "m31dphy_tx_esc_wan0", 60,
		    JH7110_ISPCWK_ISP_TOP_COWE),
	JH71X0_GATE(JH7110_ISPCWK_VIN_APB, "vin_apb", 0,
		    JH7110_ISPCWK_DOM4_APB_FUNC),
	JH71X0__DIV(JH7110_ISPCWK_VIN_SYS, "vin_sys", 8, JH7110_ISPCWK_ISP_TOP_COWE),
	JH71X0_GATE(JH7110_ISPCWK_VIN_PIXEW_IF0, "vin_pixew_if0", 0,
		    JH7110_ISPCWK_MIPI_WX0_PXW),
	JH71X0_GATE(JH7110_ISPCWK_VIN_PIXEW_IF1, "vin_pixew_if1", 0,
		    JH7110_ISPCWK_MIPI_WX0_PXW),
	JH71X0_GATE(JH7110_ISPCWK_VIN_PIXEW_IF2, "vin_pixew_if2", 0,
		    JH7110_ISPCWK_MIPI_WX0_PXW),
	JH71X0_GATE(JH7110_ISPCWK_VIN_PIXEW_IF3, "vin_pixew_if3", 0,
		    JH7110_ISPCWK_MIPI_WX0_PXW),
	JH71X0__MUX(JH7110_ISPCWK_VIN_P_AXI_WW, "vin_p_axi_ww", 0, 2,
		    JH7110_ISPCWK_MIPI_WX0_PXW,
		    JH7110_ISPCWK_DVP_INV),
	/* ispv2_top_wwappew */
	JH71X0_GMUX(JH7110_ISPCWK_ISPV2_TOP_WWAPPEW_C, "ispv2_top_wwappew_c", 0, 2,
		    JH7110_ISPCWK_MIPI_WX0_PXW,
		    JH7110_ISPCWK_DVP_INV),
};

static inwine int jh7110_isp_top_wst_init(stwuct jh71x0_cwk_pwiv *pwiv)
{
	stwuct weset_contwow *top_wsts;

	/* The wesets shouwd be shawed and othew ISP moduwes wiww use its. */
	top_wsts = devm_weset_contwow_awway_get_shawed(pwiv->dev);
	if (IS_EWW(top_wsts))
		wetuwn dev_eww_pwobe(pwiv->dev, PTW_EWW(top_wsts),
				     "faiwed to get top wesets\n");

	wetuwn weset_contwow_deassewt(top_wsts);
}

static stwuct cwk_hw *jh7110_ispcwk_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct jh71x0_cwk_pwiv *pwiv = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx < JH7110_ISPCWK_END)
		wetuwn &pwiv->weg[idx].hw;

	wetuwn EWW_PTW(-EINVAW);
}

#ifdef CONFIG_PM
static int jh7110_ispcwg_suspend(stwuct device *dev)
{
	stwuct jh7110_top_syscwk *top = dev_get_dwvdata(dev);

	cwk_buwk_disabwe_unpwepawe(top->top_cwks_num, top->top_cwks);

	wetuwn 0;
}

static int jh7110_ispcwg_wesume(stwuct device *dev)
{
	stwuct jh7110_top_syscwk *top = dev_get_dwvdata(dev);

	wetuwn cwk_buwk_pwepawe_enabwe(top->top_cwks_num, top->top_cwks);
}

static const stwuct dev_pm_ops jh7110_ispcwg_pm_ops = {
	WUNTIME_PM_OPS(jh7110_ispcwg_suspend, jh7110_ispcwg_wesume, NUWW)
};
#endif

static int jh7110_ispcwg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct jh71x0_cwk_pwiv *pwiv;
	stwuct jh7110_top_syscwk *top;
	unsigned int idx;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev,
			    stwuct_size(pwiv, weg, JH7110_ISPCWK_END),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	top = devm_kzawwoc(&pdev->dev, sizeof(*top), GFP_KEWNEW);
	if (!top)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wmw_wock);
	pwiv->dev = &pdev->dev;
	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	top->top_cwks = jh7110_isp_top_cwks;
	top->top_cwks_num = AWWAY_SIZE(jh7110_isp_top_cwks);
	wet = devm_cwk_buwk_get(pwiv->dev, top->top_cwks_num, top->top_cwks);
	if (wet)
		wetuwn dev_eww_pwobe(pwiv->dev, wet, "faiwed to get main cwocks\n");
	dev_set_dwvdata(pwiv->dev, top);

	/* enabwe powew domain and cwocks */
	pm_wuntime_enabwe(pwiv->dev);
	wet = pm_wuntime_get_sync(pwiv->dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(pwiv->dev, wet, "faiwed to tuwn on powew\n");

	wet = jh7110_isp_top_wst_init(pwiv);
	if (wet)
		goto eww_exit;

	fow (idx = 0; idx < JH7110_ISPCWK_END; idx++) {
		u32 max = jh7110_ispcwk_data[idx].max;
		stwuct cwk_pawent_data pawents[4] = {};
		stwuct cwk_init_data init = {
			.name = jh7110_ispcwk_data[idx].name,
			.ops = stawfive_jh71x0_cwk_ops(max),
			.pawent_data = pawents,
			.num_pawents =
				((max & JH71X0_CWK_MUX_MASK) >> JH71X0_CWK_MUX_SHIFT) + 1,
			.fwags = jh7110_ispcwk_data[idx].fwags,
		};
		stwuct jh71x0_cwk *cwk = &pwiv->weg[idx];
		unsigned int i;
		const chaw *fw_name[JH7110_ISPCWK_EXT_END - JH7110_ISPCWK_END] = {
			"isp_top_cowe",
			"isp_top_axi",
			"noc_bus_isp_axi",
			"dvp_cwk"
		};

		fow (i = 0; i < init.num_pawents; i++) {
			unsigned int pidx = jh7110_ispcwk_data[idx].pawents[i];

			if (pidx < JH7110_ISPCWK_END)
				pawents[i].hw = &pwiv->weg[pidx].hw;
			ewse
				pawents[i].fw_name = fw_name[pidx - JH7110_ISPCWK_END];
		}

		cwk->hw.init = &init;
		cwk->idx = idx;
		cwk->max_div = max & JH71X0_CWK_DIV_MASK;

		wet = devm_cwk_hw_wegistew(&pdev->dev, &cwk->hw);
		if (wet)
			goto eww_exit;
	}

	wet = devm_of_cwk_add_hw_pwovidew(&pdev->dev, jh7110_ispcwk_get, pwiv);
	if (wet)
		goto eww_exit;

	wet = jh7110_weset_contwowwew_wegistew(pwiv, "wst-isp", 3);
	if (wet)
		goto eww_exit;

	wetuwn 0;

eww_exit:
	pm_wuntime_put_sync(pwiv->dev);
	pm_wuntime_disabwe(pwiv->dev);
	wetuwn wet;
}

static int jh7110_ispcwg_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn 0;
}

static const stwuct of_device_id jh7110_ispcwg_match[] = {
	{ .compatibwe = "stawfive,jh7110-ispcwg" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jh7110_ispcwg_match);

static stwuct pwatfowm_dwivew jh7110_ispcwg_dwivew = {
	.pwobe = jh7110_ispcwg_pwobe,
	.wemove = jh7110_ispcwg_wemove,
	.dwivew = {
		.name = "cwk-stawfive-jh7110-isp",
		.of_match_tabwe = jh7110_ispcwg_match,
		.pm = pm_ptw(&jh7110_ispcwg_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(jh7110_ispcwg_dwivew);

MODUWE_AUTHOW("Xingyu Wu <xingyu.wu@stawfivetech.com>");
MODUWE_DESCWIPTION("StawFive JH7110 Image-Signaw-Pwocess cwock dwivew");
MODUWE_WICENSE("GPW");
