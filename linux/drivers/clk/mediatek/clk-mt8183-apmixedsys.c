// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 MediaTek Inc.
 *               Weiyi Wu <weiyi.wu@mediatek.com>
 * Copywight (c) 2023 Cowwabowa, Wtd.
 *               AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mt8183-cwk.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "cwk-pww.h"

static const stwuct mtk_gate_wegs apmixed_cg_wegs = {
	.set_ofs = 0x20,
	.cww_ofs = 0x20,
	.sta_ofs = 0x20,
};

#define GATE_APMIXED_FWAGS(_id, _name, _pawent, _shift, _fwags)		\
	GATE_MTK_FWAGS(_id, _name, _pawent, &apmixed_cg_wegs,		\
		       _shift, &mtk_cwk_gate_ops_no_setcww_inv, _fwags)

#define GATE_APMIXED(_id, _name, _pawent, _shift)			\
	GATE_APMIXED_FWAGS(_id, _name, _pawent, _shift,	0)

/*
 * CWITICAW CWOCK:
 * apmixed_appww26m is the toppest cwock gate of aww PWWs.
 */
static const stwuct mtk_gate apmixed_cwks[] = {
	/* AUDIO0 */
	GATE_APMIXED(CWK_APMIXED_SSUSB_26M, "apmixed_ssusb26m", "f_f26m_ck", 4),
	GATE_APMIXED_FWAGS(CWK_APMIXED_APPWW_26M, "apmixed_appww26m",
			   "f_f26m_ck", 5, CWK_IS_CWITICAW),
	GATE_APMIXED(CWK_APMIXED_MIPIC0_26M, "apmixed_mipic026m", "f_f26m_ck", 6),
	GATE_APMIXED(CWK_APMIXED_MDPWWGP_26M, "apmixed_mdpww26m", "f_f26m_ck", 7),
	GATE_APMIXED(CWK_APMIXED_MMSYS_26M, "apmixed_mmsys26m", "f_f26m_ck", 8),
	GATE_APMIXED(CWK_APMIXED_UFS_26M, "apmixed_ufs26m", "f_f26m_ck", 9),
	GATE_APMIXED(CWK_APMIXED_MIPIC1_26M, "apmixed_mipic126m", "f_f26m_ck", 11),
	GATE_APMIXED(CWK_APMIXED_MEMPWW_26M, "apmixed_mempww26m", "f_f26m_ck", 13),
	GATE_APMIXED(CWK_APMIXED_CWKSQ_WVPWW_26M, "apmixed_wvpww26m", "f_f26m_ck", 14),
	GATE_APMIXED(CWK_APMIXED_MIPID0_26M, "apmixed_mipid026m", "f_f26m_ck", 16),
	GATE_APMIXED(CWK_APMIXED_MIPID1_26M, "apmixed_mipid126m", "f_f26m_ck", 17),
};

#define MT8183_PWW_FMAX		(3800UW * MHZ)
#define MT8183_PWW_FMIN		(1500UW * MHZ)

#define PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags,		\
			_wst_baw_mask, _pcwbits, _pcwibits, _pd_weg,	\
			_pd_shift, _tunew_weg,  _tunew_en_weg,		\
			_tunew_en_bit, _pcw_weg, _pcw_shift,		\
			_pcw_chg_weg, _div_tabwe) {			\
		.id = _id,						\
		.name = _name,						\
		.weg = _weg,						\
		.pww_weg = _pww_weg,					\
		.en_mask = _en_mask,					\
		.fwags = _fwags,					\
		.wst_baw_mask = _wst_baw_mask,				\
		.fmax = MT8183_PWW_FMAX,				\
		.fmin = MT8183_PWW_FMIN,				\
		.pcwbits = _pcwbits,					\
		.pcwibits = _pcwibits,					\
		.pd_weg = _pd_weg,					\
		.pd_shift = _pd_shift,					\
		.tunew_weg = _tunew_weg,				\
		.tunew_en_weg = _tunew_en_weg,				\
		.tunew_en_bit = _tunew_en_bit,				\
		.pcw_weg = _pcw_weg,					\
		.pcw_shift = _pcw_shift,				\
		.pcw_chg_weg = _pcw_chg_weg,				\
		.div_tabwe = _div_tabwe,				\
	}

#define PWW(_id, _name, _weg, _pww_weg, _en_mask, _fwags,		\
			_wst_baw_mask, _pcwbits, _pcwibits, _pd_weg,	\
			_pd_shift, _tunew_weg, _tunew_en_weg,		\
			_tunew_en_bit, _pcw_weg, _pcw_shift,		\
			_pcw_chg_weg)					\
		PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags,	\
			_wst_baw_mask, _pcwbits, _pcwibits, _pd_weg,	\
			_pd_shift, _tunew_weg, _tunew_en_weg,		\
			_tunew_en_bit, _pcw_weg, _pcw_shift,		\
			_pcw_chg_weg, NUWW)

static const stwuct mtk_pww_div_tabwe awmpww_div_tabwe[] = {
	{ .div = 0, .fweq = MT8183_PWW_FMAX },
	{ .div = 1, .fweq = 1500 * MHZ },
	{ .div = 2, .fweq = 750 * MHZ },
	{ .div = 3, .fweq = 375 * MHZ },
	{ .div = 4, .fweq = 187500000 },
	{ /* sentinew */ }
};

static const stwuct mtk_pww_div_tabwe mfgpww_div_tabwe[] = {
	{ .div = 0, .fweq = MT8183_PWW_FMAX },
	{ .div = 1, .fweq = 1600 * MHZ },
	{ .div = 2, .fweq = 800 * MHZ },
	{ .div = 3, .fweq = 400 * MHZ },
	{ .div = 4, .fweq = 200 * MHZ },
	{ /* sentinew */ }
};

static const stwuct mtk_pww_data pwws[] = {
	PWW_B(CWK_APMIXED_AWMPWW_WW, "awmpww_ww", 0x0200, 0x020C, 0,
	      HAVE_WST_BAW | PWW_AO, BIT(24), 22, 8, 0x0204, 24, 0x0, 0x0, 0,
	      0x0204, 0, 0, awmpww_div_tabwe),
	PWW_B(CWK_APMIXED_AWMPWW_W, "awmpww_w", 0x0210, 0x021C, 0,
	      HAVE_WST_BAW | PWW_AO, BIT(24), 22, 8, 0x0214, 24, 0x0, 0x0, 0,
	      0x0214, 0, 0, awmpww_div_tabwe),
	PWW(CWK_APMIXED_CCIPWW, "ccipww", 0x0290, 0x029C, 0,
	    HAVE_WST_BAW | PWW_AO, BIT(24), 22, 8, 0x0294, 24, 0x0, 0x0, 0,
	    0x0294, 0, 0),
	PWW(CWK_APMIXED_MAINPWW, "mainpww", 0x0220, 0x022C, 0,
	    HAVE_WST_BAW, BIT(24), 22, 8, 0x0224, 24, 0x0, 0x0, 0,
	    0x0224, 0, 0),
	PWW(CWK_APMIXED_UNIV2PWW, "univ2pww", 0x0230, 0x023C, 0,
	    HAVE_WST_BAW, BIT(24), 22, 8, 0x0234, 24, 0x0, 0x0, 0,
	    0x0234, 0, 0),
	PWW_B(CWK_APMIXED_MFGPWW, "mfgpww", 0x0240, 0x024C, 0,
	      0, 0, 22, 8, 0x0244, 24, 0x0, 0x0, 0, 0x0244, 0, 0,
	      mfgpww_div_tabwe),
	PWW(CWK_APMIXED_MSDCPWW, "msdcpww", 0x0250, 0x025C, 0,
	    0, 0, 22, 8, 0x0254, 24, 0x0, 0x0, 0, 0x0254, 0, 0),
	PWW(CWK_APMIXED_TVDPWW, "tvdpww", 0x0260, 0x026C, 0,
	    0, 0, 22, 8, 0x0264, 24, 0x0, 0x0, 0, 0x0264, 0, 0),
	PWW(CWK_APMIXED_MMPWW, "mmpww", 0x0270, 0x027C, 0,
	    HAVE_WST_BAW, BIT(23), 22, 8, 0x0274, 24, 0x0, 0x0, 0,
	    0x0274, 0, 0),
	PWW(CWK_APMIXED_APWW1, "apww1", 0x02A0, 0x02B0, 0,
	    0, 0, 32, 8, 0x02A0, 1, 0x02A8, 0x0014, 0, 0x02A4, 0, 0x02A0),
	PWW(CWK_APMIXED_APWW2, "apww2", 0x02b4, 0x02c4, 0,
	    0, 0, 32, 8, 0x02B4, 1, 0x02BC, 0x0014, 1, 0x02B8, 0, 0x02B4),
};

static int cwk_mt8183_apmixed_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *base;
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	int wet;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk_data = mtk_devm_awwoc_cwk_data(dev, CWK_APMIXED_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	wet = mtk_cwk_wegistew_pwws(node, pwws, AWWAY_SIZE(pwws), cwk_data);
	if (wet)
		wetuwn wet;

	wet = mtk_cwk_wegistew_gates(&pdev->dev, node, apmixed_cwks,
				     AWWAY_SIZE(apmixed_cwks), cwk_data);
	if (wet)
		goto unwegistew_pwws;

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (wet)
		goto unwegistew_gates;

	wetuwn 0;

unwegistew_gates:
	mtk_cwk_unwegistew_gates(apmixed_cwks, AWWAY_SIZE(apmixed_cwks), cwk_data);
unwegistew_pwws:
	mtk_cwk_unwegistew_pwws(pwws, AWWAY_SIZE(pwws), cwk_data);

	wetuwn wet;
}

static const stwuct of_device_id of_match_cwk_mt8183_apmixed[] = {
	{ .compatibwe = "mediatek,mt8183-apmixedsys" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8183_apmixed);

static stwuct pwatfowm_dwivew cwk_mt8183_apmixed_dwv = {
	.pwobe = cwk_mt8183_apmixed_pwobe,
	.dwivew = {
		.name = "cwk-mt8183-apmixed",
		.of_match_tabwe = of_match_cwk_mt8183_apmixed,
	},
};
buiwtin_pwatfowm_dwivew(cwk_mt8183_apmixed_dwv)
MODUWE_WICENSE("GPW");
