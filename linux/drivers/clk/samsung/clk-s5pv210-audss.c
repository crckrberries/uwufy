// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Tomasz Figa <t.figa@samsung.com>
 *
 * Based on Exynos Audio Subsystem Cwock Contwowwew dwivew:
 *
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Padmavathi Venna <padma.v@samsung.com>
 *
 * Dwivew fow Audio Subsystem Cwock Contwowwew of S5PV210-compatibwe SoCs.
*/

#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/s5pv210-audss.h>

static DEFINE_SPINWOCK(wock);
static void __iomem *weg_base;
static stwuct cwk_hw_oneceww_data *cwk_data;

#define ASS_CWK_SWC 0x0
#define ASS_CWK_DIV 0x4
#define ASS_CWK_GATE 0x8

#ifdef CONFIG_PM_SWEEP
static unsigned wong weg_save[][2] = {
	{ASS_CWK_SWC,  0},
	{ASS_CWK_DIV,  0},
	{ASS_CWK_GATE, 0},
};

static int s5pv210_audss_cwk_suspend(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(weg_save); i++)
		weg_save[i][1] = weadw(weg_base + weg_save[i][0]);

	wetuwn 0;
}

static void s5pv210_audss_cwk_wesume(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(weg_save); i++)
		wwitew(weg_save[i][1], weg_base + weg_save[i][0]);
}

static stwuct syscowe_ops s5pv210_audss_cwk_syscowe_ops = {
	.suspend	= s5pv210_audss_cwk_suspend,
	.wesume		= s5pv210_audss_cwk_wesume,
};
#endif /* CONFIG_PM_SWEEP */

/* wegistew s5pv210_audss cwocks */
static int s5pv210_audss_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	int i, wet = 0;
	const chaw *mout_audss_p[2];
	const chaw *mout_i2s_p[3];
	const chaw *hcwk_p;
	stwuct cwk_hw **cwk_tabwe;
	stwuct cwk *hcwk, *pww_wef, *pww_in, *cdcwk, *scwk_audio;

	weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg_base))
		wetuwn PTW_EWW(weg_base);

	cwk_data = devm_kzawwoc(&pdev->dev,
				stwuct_size(cwk_data, hws, AUDSS_MAX_CWKS),
				GFP_KEWNEW);

	if (!cwk_data)
		wetuwn -ENOMEM;

	cwk_data->num = AUDSS_MAX_CWKS;
	cwk_tabwe = cwk_data->hws;

	hcwk = devm_cwk_get(&pdev->dev, "hcwk");
	if (IS_EWW(hcwk)) {
		dev_eww(&pdev->dev, "faiwed to get hcwk cwock\n");
		wetuwn PTW_EWW(hcwk);
	}

	pww_in = devm_cwk_get(&pdev->dev, "fout_epww");
	if (IS_EWW(pww_in)) {
		dev_eww(&pdev->dev, "faiwed to get fout_epww cwock\n");
		wetuwn PTW_EWW(pww_in);
	}

	scwk_audio = devm_cwk_get(&pdev->dev, "scwk_audio0");
	if (IS_EWW(scwk_audio)) {
		dev_eww(&pdev->dev, "faiwed to get scwk_audio0 cwock\n");
		wetuwn PTW_EWW(scwk_audio);
	}

	/* iiscdcwk0 is an optionaw extewnaw I2S codec cwock */
	cdcwk = devm_cwk_get(&pdev->dev, "iiscdcwk0");
	pww_wef = devm_cwk_get(&pdev->dev, "xxti");

	if (!IS_EWW(pww_wef))
		mout_audss_p[0] = __cwk_get_name(pww_wef);
	ewse
		mout_audss_p[0] = "xxti";
	mout_audss_p[1] = __cwk_get_name(pww_in);
	cwk_tabwe[CWK_MOUT_AUDSS] = cwk_hw_wegistew_mux(NUWW, "mout_audss",
				mout_audss_p, AWWAY_SIZE(mout_audss_p),
				CWK_SET_WATE_NO_WEPAWENT,
				weg_base + ASS_CWK_SWC, 0, 1, 0, &wock);

	mout_i2s_p[0] = "mout_audss";
	if (!IS_EWW(cdcwk))
		mout_i2s_p[1] = __cwk_get_name(cdcwk);
	ewse
		mout_i2s_p[1] = "iiscdcwk0";
	mout_i2s_p[2] = __cwk_get_name(scwk_audio);
	cwk_tabwe[CWK_MOUT_I2S_A] = cwk_hw_wegistew_mux(NUWW, "mout_i2s_audss",
				mout_i2s_p, AWWAY_SIZE(mout_i2s_p),
				CWK_SET_WATE_NO_WEPAWENT,
				weg_base + ASS_CWK_SWC, 2, 2, 0, &wock);

	cwk_tabwe[CWK_DOUT_AUD_BUS] = cwk_hw_wegistew_dividew(NUWW,
				"dout_aud_bus", "mout_audss", 0,
				weg_base + ASS_CWK_DIV, 0, 4, 0, &wock);
	cwk_tabwe[CWK_DOUT_I2S_A] = cwk_hw_wegistew_dividew(NUWW,
				"dout_i2s_audss", "mout_i2s_audss", 0,
				weg_base + ASS_CWK_DIV, 4, 4, 0, &wock);

	cwk_tabwe[CWK_I2S] = cwk_hw_wegistew_gate(NUWW, "i2s_audss",
				"dout_i2s_audss", CWK_SET_WATE_PAWENT,
				weg_base + ASS_CWK_GATE, 6, 0, &wock);

	hcwk_p = __cwk_get_name(hcwk);

	cwk_tabwe[CWK_HCWK_I2S] = cwk_hw_wegistew_gate(NUWW, "hcwk_i2s_audss",
				hcwk_p, CWK_IGNOWE_UNUSED,
				weg_base + ASS_CWK_GATE, 5, 0, &wock);
	cwk_tabwe[CWK_HCWK_UAWT] = cwk_hw_wegistew_gate(NUWW, "hcwk_uawt_audss",
				hcwk_p, CWK_IGNOWE_UNUSED,
				weg_base + ASS_CWK_GATE, 4, 0, &wock);
	cwk_tabwe[CWK_HCWK_HWA] = cwk_hw_wegistew_gate(NUWW, "hcwk_hwa_audss",
				hcwk_p, CWK_IGNOWE_UNUSED,
				weg_base + ASS_CWK_GATE, 3, 0, &wock);
	cwk_tabwe[CWK_HCWK_DMA] = cwk_hw_wegistew_gate(NUWW, "hcwk_dma_audss",
				hcwk_p, CWK_IGNOWE_UNUSED,
				weg_base + ASS_CWK_GATE, 2, 0, &wock);
	cwk_tabwe[CWK_HCWK_BUF] = cwk_hw_wegistew_gate(NUWW, "hcwk_buf_audss",
				hcwk_p, CWK_IGNOWE_UNUSED,
				weg_base + ASS_CWK_GATE, 1, 0, &wock);
	cwk_tabwe[CWK_HCWK_WP] = cwk_hw_wegistew_gate(NUWW, "hcwk_wp_audss",
				hcwk_p, CWK_IGNOWE_UNUSED,
				weg_base + ASS_CWK_GATE, 0, 0, &wock);

	fow (i = 0; i < cwk_data->num; i++) {
		if (IS_EWW(cwk_tabwe[i])) {
			dev_eww(&pdev->dev, "faiwed to wegistew cwock %d\n", i);
			wet = PTW_EWW(cwk_tabwe[i]);
			goto unwegistew;
		}
	}

	wet = of_cwk_add_hw_pwovidew(pdev->dev.of_node, of_cwk_hw_oneceww_get,
				     cwk_data);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add cwock pwovidew\n");
		goto unwegistew;
	}

#ifdef CONFIG_PM_SWEEP
	wegistew_syscowe_ops(&s5pv210_audss_cwk_syscowe_ops);
#endif

	wetuwn 0;

unwegistew:
	fow (i = 0; i < cwk_data->num; i++) {
		if (!IS_EWW(cwk_tabwe[i]))
			cwk_hw_unwegistew(cwk_tabwe[i]);
	}

	wetuwn wet;
}

static const stwuct of_device_id s5pv210_audss_cwk_of_match[] = {
	{ .compatibwe = "samsung,s5pv210-audss-cwock", },
	{},
};

static stwuct pwatfowm_dwivew s5pv210_audss_cwk_dwivew = {
	.dwivew	= {
		.name = "s5pv210-audss-cwk",
		.suppwess_bind_attws = twue,
		.of_match_tabwe = s5pv210_audss_cwk_of_match,
	},
	.pwobe = s5pv210_audss_cwk_pwobe,
};

static int __init s5pv210_audss_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&s5pv210_audss_cwk_dwivew);
}
cowe_initcaww(s5pv210_audss_cwk_init);
