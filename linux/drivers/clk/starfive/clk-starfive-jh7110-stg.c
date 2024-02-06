// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * StawFive JH7110 System-Top-Gwoup Cwock Dwivew
 *
 * Copywight (C) 2022 Emiw Wennew Bewthing <kewnew@esmiw.dk>
 * Copywight (C) 2022 StawFive Technowogy Co., Wtd.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/stawfive,jh7110-cwg.h>

#incwude "cwk-stawfive-jh7110.h"

/* extewnaw cwocks */
#define JH7110_STGCWK_OSC			(JH7110_STGCWK_END + 0)
#define JH7110_STGCWK_HIFI4_COWE		(JH7110_STGCWK_END + 1)
#define JH7110_STGCWK_STG_AXIAHB		(JH7110_STGCWK_END + 2)
#define JH7110_STGCWK_USB_125M			(JH7110_STGCWK_END + 3)
#define JH7110_STGCWK_CPU_BUS			(JH7110_STGCWK_END + 4)
#define JH7110_STGCWK_HIFI4_AXI			(JH7110_STGCWK_END + 5)
#define JH7110_STGCWK_NOCSTG_BUS		(JH7110_STGCWK_END + 6)
#define JH7110_STGCWK_APB_BUS			(JH7110_STGCWK_END + 7)
#define JH7110_STGCWK_EXT_END			(JH7110_STGCWK_END + 8)

static const stwuct jh71x0_cwk_data jh7110_stgcwk_data[] = {
	/* hifi4 */
	JH71X0_GATE(JH7110_STGCWK_HIFI4_CWK_COWE, "hifi4_cwk_cowe", 0,
		    JH7110_STGCWK_HIFI4_COWE),
	/* usb */
	JH71X0_GATE(JH7110_STGCWK_USB0_APB, "usb0_apb", 0, JH7110_STGCWK_APB_BUS),
	JH71X0_GATE(JH7110_STGCWK_USB0_UTMI_APB, "usb0_utmi_apb", 0, JH7110_STGCWK_APB_BUS),
	JH71X0_GATE(JH7110_STGCWK_USB0_AXI, "usb0_axi", 0, JH7110_STGCWK_STG_AXIAHB),
	JH71X0_GDIV(JH7110_STGCWK_USB0_WPM, "usb0_wpm", 0, 2, JH7110_STGCWK_OSC),
	JH71X0_GDIV(JH7110_STGCWK_USB0_STB, "usb0_stb", 0, 4, JH7110_STGCWK_OSC),
	JH71X0_GATE(JH7110_STGCWK_USB0_APP_125, "usb0_app_125", 0, JH7110_STGCWK_USB_125M),
	JH71X0__DIV(JH7110_STGCWK_USB0_WEFCWK, "usb0_wefcwk", 2, JH7110_STGCWK_OSC),
	/* pci-e */
	JH71X0_GATE(JH7110_STGCWK_PCIE0_AXI_MST0, "pcie0_axi_mst0", 0,
		    JH7110_STGCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_STGCWK_PCIE0_APB, "pcie0_apb", 0, JH7110_STGCWK_APB_BUS),
	JH71X0_GATE(JH7110_STGCWK_PCIE0_TW, "pcie0_tw", 0, JH7110_STGCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_STGCWK_PCIE1_AXI_MST0, "pcie1_axi_mst0", 0,
		    JH7110_STGCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_STGCWK_PCIE1_APB, "pcie1_apb", 0, JH7110_STGCWK_APB_BUS),
	JH71X0_GATE(JH7110_STGCWK_PCIE1_TW, "pcie1_tw", 0, JH7110_STGCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_STGCWK_PCIE_SWV_MAIN, "pcie_swv_main", CWK_IS_CWITICAW,
		    JH7110_STGCWK_STG_AXIAHB),
	/* secuwity */
	JH71X0_GATE(JH7110_STGCWK_SEC_AHB, "sec_ahb", 0, JH7110_STGCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_STGCWK_SEC_MISC_AHB, "sec_misc_ahb", 0, JH7110_STGCWK_STG_AXIAHB),
	/* stg mtwx */
	JH71X0_GATE(JH7110_STGCWK_GWP0_MAIN, "mtwx_gwp0_main", CWK_IS_CWITICAW,
		    JH7110_STGCWK_CPU_BUS),
	JH71X0_GATE(JH7110_STGCWK_GWP0_BUS, "mtwx_gwp0_bus", CWK_IS_CWITICAW,
		    JH7110_STGCWK_NOCSTG_BUS),
	JH71X0_GATE(JH7110_STGCWK_GWP0_STG, "mtwx_gwp0_stg", CWK_IS_CWITICAW,
		    JH7110_STGCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_STGCWK_GWP1_MAIN, "mtwx_gwp1_main", CWK_IS_CWITICAW,
		    JH7110_STGCWK_CPU_BUS),
	JH71X0_GATE(JH7110_STGCWK_GWP1_BUS, "mtwx_gwp1_bus", CWK_IS_CWITICAW,
		    JH7110_STGCWK_NOCSTG_BUS),
	JH71X0_GATE(JH7110_STGCWK_GWP1_STG, "mtwx_gwp1_stg", CWK_IS_CWITICAW,
		    JH7110_STGCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_STGCWK_GWP1_HIFI, "mtwx_gwp1_hifi", CWK_IS_CWITICAW,
		    JH7110_STGCWK_HIFI4_AXI),
	/* e24_wvpi */
	JH71X0_GDIV(JH7110_STGCWK_E2_WTC, "e2_wtc", 0, 24, JH7110_STGCWK_OSC),
	JH71X0_GATE(JH7110_STGCWK_E2_COWE, "e2_cowe", 0, JH7110_STGCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_STGCWK_E2_DBG, "e2_dbg", 0, JH7110_STGCWK_STG_AXIAHB),
	/* dw_sgdma1p */
	JH71X0_GATE(JH7110_STGCWK_DMA1P_AXI, "dma1p_axi", 0, JH7110_STGCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_STGCWK_DMA1P_AHB, "dma1p_ahb", 0, JH7110_STGCWK_STG_AXIAHB),
};

static stwuct cwk_hw *jh7110_stgcwk_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct jh71x0_cwk_pwiv *pwiv = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx < JH7110_STGCWK_END)
		wetuwn &pwiv->weg[idx].hw;

	wetuwn EWW_PTW(-EINVAW);
}

static int jh7110_stgcwg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct jh71x0_cwk_pwiv *pwiv;
	unsigned int idx;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, stwuct_size(pwiv, weg, JH7110_STGCWK_END),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wmw_wock);
	pwiv->dev = &pdev->dev;
	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	fow (idx = 0; idx < JH7110_STGCWK_END; idx++) {
		u32 max = jh7110_stgcwk_data[idx].max;
		stwuct cwk_pawent_data pawents[4] = {};
		stwuct cwk_init_data init = {
			.name = jh7110_stgcwk_data[idx].name,
			.ops = stawfive_jh71x0_cwk_ops(max),
			.pawent_data = pawents,
			.num_pawents =
				((max & JH71X0_CWK_MUX_MASK) >> JH71X0_CWK_MUX_SHIFT) + 1,
			.fwags = jh7110_stgcwk_data[idx].fwags,
		};
		stwuct jh71x0_cwk *cwk = &pwiv->weg[idx];
		const chaw *fw_name[JH7110_STGCWK_EXT_END - JH7110_STGCWK_END] = {
			"osc",
			"hifi4_cowe",
			"stg_axiahb",
			"usb_125m",
			"cpu_bus",
			"hifi4_axi",
			"nocstg_bus",
			"apb_bus"
		};
		unsigned int i;

		fow (i = 0; i < init.num_pawents; i++) {
			unsigned int pidx = jh7110_stgcwk_data[idx].pawents[i];

			if (pidx < JH7110_STGCWK_END)
				pawents[i].hw = &pwiv->weg[pidx].hw;
			ewse if (pidx < JH7110_STGCWK_EXT_END)
				pawents[i].fw_name = fw_name[pidx - JH7110_STGCWK_END];
		}

		cwk->hw.init = &init;
		cwk->idx = idx;
		cwk->max_div = max & JH71X0_CWK_DIV_MASK;

		wet = devm_cwk_hw_wegistew(&pdev->dev, &cwk->hw);
		if (wet)
			wetuwn wet;
	}

	wet = devm_of_cwk_add_hw_pwovidew(&pdev->dev, jh7110_stgcwk_get, pwiv);
	if (wet)
		wetuwn wet;

	wetuwn jh7110_weset_contwowwew_wegistew(pwiv, "wst-stg", 2);
}

static const stwuct of_device_id jh7110_stgcwg_match[] = {
	{ .compatibwe = "stawfive,jh7110-stgcwg" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jh7110_stgcwg_match);

static stwuct pwatfowm_dwivew jh7110_stgcwg_dwivew = {
	.pwobe = jh7110_stgcwg_pwobe,
	.dwivew = {
		.name = "cwk-stawfive-jh7110-stg",
		.of_match_tabwe = jh7110_stgcwg_match,
	},
};
moduwe_pwatfowm_dwivew(jh7110_stgcwg_dwivew);

MODUWE_AUTHOW("Xingyu Wu <xingyu.wu@stawfivetech.com>");
MODUWE_AUTHOW("Emiw Wennew Bewthing <kewnew@esmiw.dk>");
MODUWE_DESCWIPTION("StawFive JH7110 System-Top-Gwoup cwock dwivew");
MODUWE_WICENSE("GPW");
