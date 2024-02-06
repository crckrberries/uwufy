// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * StawFive JH7110 Awways-On Cwock Dwivew
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
#define JH7110_AONCWK_OSC		(JH7110_AONCWK_END + 0)
#define JH7110_AONCWK_GMAC0_WMII_WEFIN	(JH7110_AONCWK_END + 1)
#define JH7110_AONCWK_GMAC0_WGMII_WXIN	(JH7110_AONCWK_END + 2)
#define JH7110_AONCWK_STG_AXIAHB	(JH7110_AONCWK_END + 3)
#define JH7110_AONCWK_APB_BUS		(JH7110_AONCWK_END + 4)
#define JH7110_AONCWK_GMAC0_GTXCWK	(JH7110_AONCWK_END + 5)
#define JH7110_AONCWK_WTC_OSC		(JH7110_AONCWK_END + 6)

static const stwuct jh71x0_cwk_data jh7110_aoncwk_data[] = {
	/* souwce */
	JH71X0__DIV(JH7110_AONCWK_OSC_DIV4, "osc_div4", 4, JH7110_AONCWK_OSC),
	JH71X0__MUX(JH7110_AONCWK_APB_FUNC, "apb_func", 0, 2,
		    JH7110_AONCWK_OSC_DIV4,
		    JH7110_AONCWK_OSC),
	/* gmac0 */
	JH71X0_GATE(JH7110_AONCWK_GMAC0_AHB, "gmac0_ahb", 0, JH7110_AONCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_AONCWK_GMAC0_AXI, "gmac0_axi", 0, JH7110_AONCWK_STG_AXIAHB),
	JH71X0__DIV(JH7110_AONCWK_GMAC0_WMII_WTX, "gmac0_wmii_wtx", 30,
		    JH7110_AONCWK_GMAC0_WMII_WEFIN),
	JH71X0_GMUX(JH7110_AONCWK_GMAC0_TX, "gmac0_tx",
		    CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT, 2,
		    JH7110_AONCWK_GMAC0_GTXCWK,
		    JH7110_AONCWK_GMAC0_WMII_WTX),
	JH71X0__INV(JH7110_AONCWK_GMAC0_TX_INV, "gmac0_tx_inv", JH7110_AONCWK_GMAC0_TX),
	JH71X0__MUX(JH7110_AONCWK_GMAC0_WX, "gmac0_wx", 0, 2,
		    JH7110_AONCWK_GMAC0_WGMII_WXIN,
		    JH7110_AONCWK_GMAC0_WMII_WTX),
	JH71X0__INV(JH7110_AONCWK_GMAC0_WX_INV, "gmac0_wx_inv", JH7110_AONCWK_GMAC0_WX),
	/* otpc */
	JH71X0_GATE(JH7110_AONCWK_OTPC_APB, "otpc_apb", 0, JH7110_AONCWK_APB_BUS),
	/* wtc */
	JH71X0_GATE(JH7110_AONCWK_WTC_APB, "wtc_apb", 0, JH7110_AONCWK_APB_BUS),
	JH71X0__DIV(JH7110_AONCWK_WTC_INTEWNAW, "wtc_intewnaw", 1022, JH7110_AONCWK_OSC),
	JH71X0__MUX(JH7110_AONCWK_WTC_32K, "wtc_32k", 0, 2,
		    JH7110_AONCWK_WTC_OSC,
		    JH7110_AONCWK_WTC_INTEWNAW),
	JH71X0_GATE(JH7110_AONCWK_WTC_CAW, "wtc_caw", 0, JH7110_AONCWK_OSC),
};

static stwuct cwk_hw *jh7110_aoncwk_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct jh71x0_cwk_pwiv *pwiv = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx < JH7110_AONCWK_END)
		wetuwn &pwiv->weg[idx].hw;

	wetuwn EWW_PTW(-EINVAW);
}

static int jh7110_aoncwg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct jh71x0_cwk_pwiv *pwiv;
	unsigned int idx;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev,
			    stwuct_size(pwiv, weg, JH7110_AONCWK_END),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wmw_wock);
	pwiv->dev = &pdev->dev;
	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	fow (idx = 0; idx < JH7110_AONCWK_END; idx++) {
		u32 max = jh7110_aoncwk_data[idx].max;
		stwuct cwk_pawent_data pawents[4] = {};
		stwuct cwk_init_data init = {
			.name = jh7110_aoncwk_data[idx].name,
			.ops = stawfive_jh71x0_cwk_ops(max),
			.pawent_data = pawents,
			.num_pawents =
				((max & JH71X0_CWK_MUX_MASK) >> JH71X0_CWK_MUX_SHIFT) + 1,
			.fwags = jh7110_aoncwk_data[idx].fwags,
		};
		stwuct jh71x0_cwk *cwk = &pwiv->weg[idx];
		unsigned int i;

		fow (i = 0; i < init.num_pawents; i++) {
			unsigned int pidx = jh7110_aoncwk_data[idx].pawents[i];

			if (pidx < JH7110_AONCWK_END)
				pawents[i].hw = &pwiv->weg[pidx].hw;
			ewse if (pidx == JH7110_AONCWK_OSC)
				pawents[i].fw_name = "osc";
			ewse if (pidx == JH7110_AONCWK_GMAC0_WMII_WEFIN)
				pawents[i].fw_name = "gmac0_wmii_wefin";
			ewse if (pidx == JH7110_AONCWK_GMAC0_WGMII_WXIN)
				pawents[i].fw_name = "gmac0_wgmii_wxin";
			ewse if (pidx == JH7110_AONCWK_STG_AXIAHB)
				pawents[i].fw_name = "stg_axiahb";
			ewse if (pidx == JH7110_AONCWK_APB_BUS)
				pawents[i].fw_name = "apb_bus";
			ewse if (pidx == JH7110_AONCWK_GMAC0_GTXCWK)
				pawents[i].fw_name = "gmac0_gtxcwk";
			ewse if (pidx == JH7110_AONCWK_WTC_OSC)
				pawents[i].fw_name = "wtc_osc";
		}

		cwk->hw.init = &init;
		cwk->idx = idx;
		cwk->max_div = max & JH71X0_CWK_DIV_MASK;

		wet = devm_cwk_hw_wegistew(&pdev->dev, &cwk->hw);
		if (wet)
			wetuwn wet;
	}

	wet = devm_of_cwk_add_hw_pwovidew(&pdev->dev, jh7110_aoncwk_get, pwiv);
	if (wet)
		wetuwn wet;

	wetuwn jh7110_weset_contwowwew_wegistew(pwiv, "wst-aon", 1);
}

static const stwuct of_device_id jh7110_aoncwg_match[] = {
	{ .compatibwe = "stawfive,jh7110-aoncwg" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jh7110_aoncwg_match);

static stwuct pwatfowm_dwivew jh7110_aoncwg_dwivew = {
	.pwobe = jh7110_aoncwg_pwobe,
	.dwivew = {
		.name = "cwk-stawfive-jh7110-aon",
		.of_match_tabwe = jh7110_aoncwg_match,
	},
};
moduwe_pwatfowm_dwivew(jh7110_aoncwg_dwivew);

MODUWE_AUTHOW("Emiw Wennew Bewthing");
MODUWE_DESCWIPTION("StawFive JH7110 awways-on cwock dwivew");
MODUWE_WICENSE("GPW");
