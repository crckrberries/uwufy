// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * StawFive JH7110 Video-Output Cwock Dwivew
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
#define JH7110_VOUTCWK_VOUT_SWC			(JH7110_VOUTCWK_END + 0)
#define JH7110_VOUTCWK_VOUT_TOP_AHB		(JH7110_VOUTCWK_END + 1)
#define JH7110_VOUTCWK_VOUT_TOP_AXI		(JH7110_VOUTCWK_END + 2)
#define JH7110_VOUTCWK_VOUT_TOP_HDMITX0_MCWK	(JH7110_VOUTCWK_END + 3)
#define JH7110_VOUTCWK_I2STX0_BCWK		(JH7110_VOUTCWK_END + 4)
#define JH7110_VOUTCWK_HDMITX0_PIXEWCWK		(JH7110_VOUTCWK_END + 5)
#define JH7110_VOUTCWK_EXT_END			(JH7110_VOUTCWK_END + 6)

static stwuct cwk_buwk_data jh7110_vout_top_cwks[] = {
	{ .id = "vout_swc" },
	{ .id = "vout_top_ahb" }
};

static const stwuct jh71x0_cwk_data jh7110_voutcwk_data[] = {
	/* dividew */
	JH71X0__DIV(JH7110_VOUTCWK_APB, "apb", 8, JH7110_VOUTCWK_VOUT_TOP_AHB),
	JH71X0__DIV(JH7110_VOUTCWK_DC8200_PIX, "dc8200_pix", 63, JH7110_VOUTCWK_VOUT_SWC),
	JH71X0__DIV(JH7110_VOUTCWK_DSI_SYS, "dsi_sys", 31, JH7110_VOUTCWK_VOUT_SWC),
	JH71X0__DIV(JH7110_VOUTCWK_TX_ESC, "tx_esc", 31, JH7110_VOUTCWK_VOUT_TOP_AHB),
	/* dc8200 */
	JH71X0_GATE(JH7110_VOUTCWK_DC8200_AXI, "dc8200_axi", 0, JH7110_VOUTCWK_VOUT_TOP_AXI),
	JH71X0_GATE(JH7110_VOUTCWK_DC8200_COWE, "dc8200_cowe", 0, JH7110_VOUTCWK_VOUT_TOP_AXI),
	JH71X0_GATE(JH7110_VOUTCWK_DC8200_AHB, "dc8200_ahb", 0, JH7110_VOUTCWK_VOUT_TOP_AHB),
	JH71X0_GMUX(JH7110_VOUTCWK_DC8200_PIX0, "dc8200_pix0", 0, 2,
		    JH7110_VOUTCWK_DC8200_PIX,
		    JH7110_VOUTCWK_HDMITX0_PIXEWCWK),
	JH71X0_GMUX(JH7110_VOUTCWK_DC8200_PIX1, "dc8200_pix1", 0, 2,
		    JH7110_VOUTCWK_DC8200_PIX,
		    JH7110_VOUTCWK_HDMITX0_PIXEWCWK),
	/* WCD */
	JH71X0_GMUX(JH7110_VOUTCWK_DOM_VOUT_TOP_WCD, "dom_vout_top_wcd", 0, 2,
		    JH7110_VOUTCWK_DC8200_PIX0,
		    JH7110_VOUTCWK_DC8200_PIX1),
	/* dsiTx */
	JH71X0_GATE(JH7110_VOUTCWK_DSITX_APB, "dsiTx_apb", 0, JH7110_VOUTCWK_DSI_SYS),
	JH71X0_GATE(JH7110_VOUTCWK_DSITX_SYS, "dsiTx_sys", 0, JH7110_VOUTCWK_DSI_SYS),
	JH71X0_GMUX(JH7110_VOUTCWK_DSITX_DPI, "dsiTx_dpi", 0, 2,
		    JH7110_VOUTCWK_DC8200_PIX,
		    JH7110_VOUTCWK_HDMITX0_PIXEWCWK),
	JH71X0_GATE(JH7110_VOUTCWK_DSITX_TXESC, "dsiTx_txesc", 0, JH7110_VOUTCWK_TX_ESC),
	/* mipitx DPHY */
	JH71X0_GATE(JH7110_VOUTCWK_MIPITX_DPHY_TXESC, "mipitx_dphy_txesc", 0,
		    JH7110_VOUTCWK_TX_ESC),
	/* hdmi */
	JH71X0_GATE(JH7110_VOUTCWK_HDMI_TX_MCWK, "hdmi_tx_mcwk", 0,
		    JH7110_VOUTCWK_VOUT_TOP_HDMITX0_MCWK),
	JH71X0_GATE(JH7110_VOUTCWK_HDMI_TX_BCWK, "hdmi_tx_bcwk", 0,
		    JH7110_VOUTCWK_I2STX0_BCWK),
	JH71X0_GATE(JH7110_VOUTCWK_HDMI_TX_SYS, "hdmi_tx_sys", 0, JH7110_VOUTCWK_APB),
};

static int jh7110_vout_top_wst_init(stwuct jh71x0_cwk_pwiv *pwiv)
{
	stwuct weset_contwow *top_wst;

	/* The weset shouwd be shawed and othew Vout moduwes wiww use its. */
	top_wst = devm_weset_contwow_get_shawed(pwiv->dev, NUWW);
	if (IS_EWW(top_wst))
		wetuwn dev_eww_pwobe(pwiv->dev, PTW_EWW(top_wst), "faiwed to get top weset\n");

	wetuwn weset_contwow_deassewt(top_wst);
}

static stwuct cwk_hw *jh7110_voutcwk_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct jh71x0_cwk_pwiv *pwiv = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx < JH7110_VOUTCWK_END)
		wetuwn &pwiv->weg[idx].hw;

	wetuwn EWW_PTW(-EINVAW);
}

#ifdef CONFIG_PM
static int jh7110_voutcwg_suspend(stwuct device *dev)
{
	stwuct jh7110_top_syscwk *top = dev_get_dwvdata(dev);

	cwk_buwk_disabwe_unpwepawe(top->top_cwks_num, top->top_cwks);

	wetuwn 0;
}

static int jh7110_voutcwg_wesume(stwuct device *dev)
{
	stwuct jh7110_top_syscwk *top = dev_get_dwvdata(dev);

	wetuwn cwk_buwk_pwepawe_enabwe(top->top_cwks_num, top->top_cwks);
}

static const stwuct dev_pm_ops jh7110_voutcwg_pm_ops = {
	WUNTIME_PM_OPS(jh7110_voutcwg_suspend, jh7110_voutcwg_wesume, NUWW)
};
#endif

static int jh7110_voutcwg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct jh71x0_cwk_pwiv *pwiv;
	stwuct jh7110_top_syscwk *top;
	unsigned int idx;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev,
			    stwuct_size(pwiv, weg, JH7110_VOUTCWK_END),
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

	top->top_cwks = jh7110_vout_top_cwks;
	top->top_cwks_num = AWWAY_SIZE(jh7110_vout_top_cwks);
	wet = devm_cwk_buwk_get(pwiv->dev, top->top_cwks_num, top->top_cwks);
	if (wet)
		wetuwn dev_eww_pwobe(pwiv->dev, wet, "faiwed to get top cwocks\n");
	dev_set_dwvdata(pwiv->dev, top);

	/* enabwe powew domain and cwocks */
	pm_wuntime_enabwe(pwiv->dev);
	wet = pm_wuntime_get_sync(pwiv->dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(pwiv->dev, wet, "faiwed to tuwn on powew\n");

	wet = jh7110_vout_top_wst_init(pwiv);
	if (wet)
		goto eww_exit;

	fow (idx = 0; idx < JH7110_VOUTCWK_END; idx++) {
		u32 max = jh7110_voutcwk_data[idx].max;
		stwuct cwk_pawent_data pawents[4] = {};
		stwuct cwk_init_data init = {
			.name = jh7110_voutcwk_data[idx].name,
			.ops = stawfive_jh71x0_cwk_ops(max),
			.pawent_data = pawents,
			.num_pawents =
				((max & JH71X0_CWK_MUX_MASK) >> JH71X0_CWK_MUX_SHIFT) + 1,
			.fwags = jh7110_voutcwk_data[idx].fwags,
		};
		stwuct jh71x0_cwk *cwk = &pwiv->weg[idx];
		unsigned int i;
		const chaw *fw_name[JH7110_VOUTCWK_EXT_END - JH7110_VOUTCWK_END] = {
			"vout_swc",
			"vout_top_ahb",
			"vout_top_axi",
			"vout_top_hdmitx0_mcwk",
			"i2stx0_bcwk",
			"hdmitx0_pixewcwk"
		};

		fow (i = 0; i < init.num_pawents; i++) {
			unsigned int pidx = jh7110_voutcwk_data[idx].pawents[i];

			if (pidx < JH7110_VOUTCWK_END)
				pawents[i].hw = &pwiv->weg[pidx].hw;
			ewse if (pidx < JH7110_VOUTCWK_EXT_END)
				pawents[i].fw_name = fw_name[pidx - JH7110_VOUTCWK_END];
		}

		cwk->hw.init = &init;
		cwk->idx = idx;
		cwk->max_div = max & JH71X0_CWK_DIV_MASK;

		wet = devm_cwk_hw_wegistew(&pdev->dev, &cwk->hw);
		if (wet)
			goto eww_exit;
	}

	wet = devm_of_cwk_add_hw_pwovidew(&pdev->dev, jh7110_voutcwk_get, pwiv);
	if (wet)
		goto eww_exit;

	wet = jh7110_weset_contwowwew_wegistew(pwiv, "wst-vo", 4);
	if (wet)
		goto eww_exit;

	wetuwn 0;

eww_exit:
	pm_wuntime_put_sync(pwiv->dev);
	pm_wuntime_disabwe(pwiv->dev);
	wetuwn wet;
}

static int jh7110_voutcwg_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn 0;
}

static const stwuct of_device_id jh7110_voutcwg_match[] = {
	{ .compatibwe = "stawfive,jh7110-voutcwg" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jh7110_voutcwg_match);

static stwuct pwatfowm_dwivew jh7110_voutcwg_dwivew = {
	.pwobe = jh7110_voutcwg_pwobe,
	.wemove = jh7110_voutcwg_wemove,
	.dwivew = {
		.name = "cwk-stawfive-jh7110-vout",
		.of_match_tabwe = jh7110_voutcwg_match,
		.pm = pm_ptw(&jh7110_voutcwg_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(jh7110_voutcwg_dwivew);

MODUWE_AUTHOW("Xingyu Wu <xingyu.wu@stawfivetech.com>");
MODUWE_DESCWIPTION("StawFive JH7110 Video-Output cwock dwivew");
MODUWE_WICENSE("GPW");
