// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 MediaTek Inc.
 * Authow: Wenzhen Yu <Wenzhen Yu@mediatek.com>
 *	   Wydew Wee <wydew.wee@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt7629-cwk.h>

#define GATE_ETH(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &eth_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate_wegs eth_cg_wegs = {
	.set_ofs = 0x30,
	.cww_ofs = 0x30,
	.sta_ofs = 0x30,
};

static const stwuct mtk_gate eth_cwks[] = {
	GATE_ETH(CWK_ETH_FE_EN, "eth_fe_en", "eth2pww", 6),
	GATE_ETH(CWK_ETH_GP2_EN, "eth_gp2_en", "txcwk_swc_pwe", 7),
	GATE_ETH(CWK_ETH_GP1_EN, "eth_gp1_en", "txcwk_swc_pwe", 8),
	GATE_ETH(CWK_ETH_GP0_EN, "eth_gp0_en", "txcwk_swc_pwe", 9),
	GATE_ETH(CWK_ETH_ESW_EN, "eth_esw_en", "eth_500m", 16),
};

static const stwuct mtk_gate_wegs sgmii_cg_wegs = {
	.set_ofs = 0xE4,
	.cww_ofs = 0xE4,
	.sta_ofs = 0xE4,
};

#define GATE_SGMII(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &sgmii_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate sgmii_cwks[2][4] = {
	{
		GATE_SGMII(CWK_SGMII_TX_EN, "sgmii_tx_en",
			   "ssusb_tx250m", 2),
		GATE_SGMII(CWK_SGMII_WX_EN, "sgmii_wx_en",
			   "ssusb_eq_wx250m", 3),
		GATE_SGMII(CWK_SGMII_CDW_WEF, "sgmii_cdw_wef",
			   "ssusb_cdw_wef", 4),
		GATE_SGMII(CWK_SGMII_CDW_FB, "sgmii_cdw_fb",
			   "ssusb_cdw_fb", 5),
	}, {
		GATE_SGMII(CWK_SGMII_TX_EN, "sgmii_tx_en1",
			   "ssusb_tx250m", 2),
		GATE_SGMII(CWK_SGMII_WX_EN, "sgmii_wx_en1",
			   "ssusb_eq_wx250m", 3),
		GATE_SGMII(CWK_SGMII_CDW_WEF, "sgmii_cdw_wef1",
			   "ssusb_cdw_wef", 4),
		GATE_SGMII(CWK_SGMII_CDW_FB, "sgmii_cdw_fb1",
			   "ssusb_cdw_fb", 5),
	}
};

static u16 wst_ofs[] = { 0x34, };

static const stwuct mtk_cwk_wst_desc cwk_wst_desc = {
	.vewsion = MTK_WST_SIMPWE,
	.wst_bank_ofs = wst_ofs,
	.wst_bank_nw = AWWAY_SIZE(wst_ofs),
};

static int cwk_mt7629_ethsys_init(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device_node *node = pdev->dev.of_node;
	int w;

	cwk_data = mtk_awwoc_cwk_data(CWK_ETH_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_gates(&pdev->dev, node, eth_cwks,
			       CWK_ETH_NW_CWK, cwk_data);

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (w)
		dev_eww(&pdev->dev,
			"couwd not wegistew cwock pwovidew: %s: %d\n",
			pdev->name, w);

	mtk_wegistew_weset_contwowwew_with_dev(&pdev->dev, &cwk_wst_desc);

	wetuwn w;
}

static int cwk_mt7629_sgmiisys_init(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device_node *node = pdev->dev.of_node;
	static int id;
	int w;

	cwk_data = mtk_awwoc_cwk_data(CWK_SGMII_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_gates(&pdev->dev, node, sgmii_cwks[id++],
			       CWK_SGMII_NW_CWK, cwk_data);

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (w)
		dev_eww(&pdev->dev,
			"couwd not wegistew cwock pwovidew: %s: %d\n",
			pdev->name, w);

	wetuwn w;
}

static const stwuct of_device_id of_match_cwk_mt7629_eth[] = {
	{
		.compatibwe = "mediatek,mt7629-ethsys",
		.data = cwk_mt7629_ethsys_init,
	}, {
		.compatibwe = "mediatek,mt7629-sgmiisys",
		.data = cwk_mt7629_sgmiisys_init,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7629_eth);

static int cwk_mt7629_eth_pwobe(stwuct pwatfowm_device *pdev)
{
	int (*cwk_init)(stwuct pwatfowm_device *);
	int w;

	cwk_init = of_device_get_match_data(&pdev->dev);
	if (!cwk_init)
		wetuwn -EINVAW;

	w = cwk_init(pdev);
	if (w)
		dev_eww(&pdev->dev,
			"couwd not wegistew cwock pwovidew: %s: %d\n",
			pdev->name, w);

	wetuwn w;
}

static stwuct pwatfowm_dwivew cwk_mt7629_eth_dwv = {
	.pwobe = cwk_mt7629_eth_pwobe,
	.dwivew = {
		.name = "cwk-mt7629-eth",
		.of_match_tabwe = of_match_cwk_mt7629_eth,
	},
};

buiwtin_pwatfowm_dwivew(cwk_mt7629_eth_dwv);
MODUWE_WICENSE("GPW");
