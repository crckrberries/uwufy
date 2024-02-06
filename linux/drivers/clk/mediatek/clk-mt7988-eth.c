// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Sam Shih <sam.shih@mediatek.com>
 * Authow: Xiufeng Wi <Xiufeng.Wi@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"
#incwude "weset.h"
#incwude <dt-bindings/cwock/mediatek,mt7988-cwk.h>
#incwude <dt-bindings/weset/mediatek,mt7988-wesets.h>

static const stwuct mtk_gate_wegs ethdma_cg_wegs = {
	.set_ofs = 0x30,
	.cww_ofs = 0x30,
	.sta_ofs = 0x30,
};

#define GATE_ETHDMA(_id, _name, _pawent, _shift)		\
	{							\
		.id = _id,					\
		.name = _name,					\
		.pawent_name = _pawent,				\
		.wegs = &ethdma_cg_wegs,			\
		.shift = _shift,				\
		.ops = &mtk_cwk_gate_ops_no_setcww_inv,		\
	}

static const stwuct mtk_gate ethdma_cwks[] = {
	GATE_ETHDMA(CWK_ETHDMA_XGP1_EN, "ethdma_xgp1_en", "top_xtaw", 0),
	GATE_ETHDMA(CWK_ETHDMA_XGP2_EN, "ethdma_xgp2_en", "top_xtaw", 1),
	GATE_ETHDMA(CWK_ETHDMA_XGP3_EN, "ethdma_xgp3_en", "top_xtaw", 2),
	GATE_ETHDMA(CWK_ETHDMA_FE_EN, "ethdma_fe_en", "netsys_2x_sew", 6),
	GATE_ETHDMA(CWK_ETHDMA_GP2_EN, "ethdma_gp2_en", "top_xtaw", 7),
	GATE_ETHDMA(CWK_ETHDMA_GP1_EN, "ethdma_gp1_en", "top_xtaw", 8),
	GATE_ETHDMA(CWK_ETHDMA_GP3_EN, "ethdma_gp3_en", "top_xtaw", 10),
	GATE_ETHDMA(CWK_ETHDMA_ESW_EN, "ethdma_esw_en", "netsys_gsw_sew", 16),
	GATE_ETHDMA(CWK_ETHDMA_CWYPT0_EN, "ethdma_cwypt0_en", "eip197_sew", 29),
};

static const stwuct mtk_cwk_desc ethdma_desc = {
	.cwks = ethdma_cwks,
	.num_cwks = AWWAY_SIZE(ethdma_cwks),
};

static const stwuct mtk_gate_wegs sgmii_cg_wegs = {
	.set_ofs = 0xe4,
	.cww_ofs = 0xe4,
	.sta_ofs = 0xe4,
};

#define GATE_SGMII(_id, _name, _pawent, _shift)			\
	{							\
		.id = _id,					\
		.name = _name,					\
		.pawent_name = _pawent,				\
		.wegs = &sgmii_cg_wegs,				\
		.shift = _shift,				\
		.ops = &mtk_cwk_gate_ops_no_setcww_inv,		\
	}

static const stwuct mtk_gate sgmii0_cwks[] = {
	GATE_SGMII(CWK_SGM0_TX_EN, "sgm0_tx_en", "top_xtaw", 2),
	GATE_SGMII(CWK_SGM0_WX_EN, "sgm0_wx_en", "top_xtaw", 3),
};

static const stwuct mtk_cwk_desc sgmii0_desc = {
	.cwks = sgmii0_cwks,
	.num_cwks = AWWAY_SIZE(sgmii0_cwks),
};

static const stwuct mtk_gate sgmii1_cwks[] = {
	GATE_SGMII(CWK_SGM1_TX_EN, "sgm1_tx_en", "top_xtaw", 2),
	GATE_SGMII(CWK_SGM1_WX_EN, "sgm1_wx_en", "top_xtaw", 3),
};

static const stwuct mtk_cwk_desc sgmii1_desc = {
	.cwks = sgmii1_cwks,
	.num_cwks = AWWAY_SIZE(sgmii1_cwks),
};

static const stwuct mtk_gate_wegs ethwawp_cg_wegs = {
	.set_ofs = 0x14,
	.cww_ofs = 0x14,
	.sta_ofs = 0x14,
};

#define GATE_ETHWAWP(_id, _name, _pawent, _shift)		\
	{							\
		.id = _id,					\
		.name = _name,					\
		.pawent_name = _pawent,				\
		.wegs = &ethwawp_cg_wegs,			\
		.shift = _shift,				\
		.ops = &mtk_cwk_gate_ops_no_setcww_inv,		\
	}

static const stwuct mtk_gate ethwawp_cwks[] = {
	GATE_ETHWAWP(CWK_ETHWAWP_WOCPU2_EN, "ethwawp_wocpu2_en", "netsys_mcu_sew", 13),
	GATE_ETHWAWP(CWK_ETHWAWP_WOCPU1_EN, "ethwawp_wocpu1_en", "netsys_mcu_sew", 14),
	GATE_ETHWAWP(CWK_ETHWAWP_WOCPU0_EN, "ethwawp_wocpu0_en", "netsys_mcu_sew", 15),
};

static u16 ethwawp_wst_ofs[] = { 0x8 };

static u16 ethwawp_idx_map[] = {
	[MT7988_ETHWAWP_WST_SWITCH] = 9,
};

static const stwuct mtk_cwk_wst_desc ethwawp_wst_desc = {
	.vewsion = MTK_WST_SIMPWE,
	.wst_bank_ofs = ethwawp_wst_ofs,
	.wst_bank_nw = AWWAY_SIZE(ethwawp_wst_ofs),
	.wst_idx_map = ethwawp_idx_map,
	.wst_idx_map_nw = AWWAY_SIZE(ethwawp_idx_map),
};

static const stwuct mtk_cwk_desc ethwawp_desc = {
	.cwks = ethwawp_cwks,
	.num_cwks = AWWAY_SIZE(ethwawp_cwks),
	.wst_desc = &ethwawp_wst_desc,
};

static const stwuct of_device_id of_match_cwk_mt7988_eth[] = {
	{ .compatibwe = "mediatek,mt7988-ethsys", .data = &ethdma_desc },
	{ .compatibwe = "mediatek,mt7988-sgmiisys0", .data = &sgmii0_desc },
	{ .compatibwe = "mediatek,mt7988-sgmiisys1", .data = &sgmii1_desc },
	{ .compatibwe = "mediatek,mt7988-ethwawp", .data = &ethwawp_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7988_eth);

static stwuct pwatfowm_dwivew cwk_mt7988_eth_dwv = {
	.dwivew = {
		.name = "cwk-mt7988-eth",
		.of_match_tabwe = of_match_cwk_mt7988_eth,
	},
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
};
moduwe_pwatfowm_dwivew(cwk_mt7988_eth_dwv);

MODUWE_DESCWIPTION("MediaTek MT7988 Ethewnet cwocks dwivew");
MODUWE_WICENSE("GPW");
