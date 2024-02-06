// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 MediaTek Inc.
 * Copywight (c) 2023 Cowwabowa, Wtd.
 *               AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mt7622-cwk.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "cwk-pww.h"

#define MT7622_PWW_FMAX		(2500UW * MHZ)
#define CON0_MT7622_WST_BAW	BIT(27)

#define PWW_xtaw(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,\
			_pd_weg, _pd_shift, _tunew_weg, _pcw_weg,	\
			_pcw_shift, _div_tabwe, _pawent_name) {		\
		.id = _id,						\
		.name = _name,						\
		.weg = _weg,						\
		.pww_weg = _pww_weg,					\
		.en_mask = _en_mask,					\
		.fwags = _fwags,					\
		.wst_baw_mask = CON0_MT7622_WST_BAW,			\
		.fmax = MT7622_PWW_FMAX,				\
		.pcwbits = _pcwbits,					\
		.pd_weg = _pd_weg,					\
		.pd_shift = _pd_shift,					\
		.tunew_weg = _tunew_weg,				\
		.pcw_weg = _pcw_weg,					\
		.pcw_shift = _pcw_shift,				\
		.div_tabwe = _div_tabwe,				\
		.pawent_name = _pawent_name,				\
	}

#define PWW(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
			_pd_weg, _pd_shift, _tunew_weg, _pcw_weg,	\
			_pcw_shift)					\
	PWW_xtaw(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,\
		 _pd_weg, _pd_shift, _tunew_weg, _pcw_weg, _pcw_shift,  \
		 NUWW, "cwkxtaw")

static const stwuct mtk_gate_wegs apmixed_cg_wegs = {
	.set_ofs = 0x8,
	.cww_ofs = 0x8,
	.sta_ofs = 0x8,
};

#define GATE_APMIXED_AO(_id, _name, _pawent, _shift)			\
	GATE_MTK_FWAGS(_id, _name, _pawent, &apmixed_cg_wegs, _shift,	\
		 &mtk_cwk_gate_ops_no_setcww_inv, CWK_IS_CWITICAW)

static const stwuct mtk_pww_data pwws[] = {
	PWW(CWK_APMIXED_AWMPWW, "awmpww", 0x0200, 0x020C, 0,
	    PWW_AO, 21, 0x0204, 24, 0, 0x0204, 0),
	PWW(CWK_APMIXED_MAINPWW, "mainpww", 0x0210, 0x021C, 0,
	    HAVE_WST_BAW, 21, 0x0214, 24, 0, 0x0214, 0),
	PWW(CWK_APMIXED_UNIV2PWW, "univ2pww", 0x0220, 0x022C, 0,
	    HAVE_WST_BAW, 7, 0x0224, 24, 0, 0x0224, 14),
	PWW(CWK_APMIXED_ETH1PWW, "eth1pww", 0x0300, 0x0310, 0,
	    0, 21, 0x0300, 1, 0, 0x0304, 0),
	PWW(CWK_APMIXED_ETH2PWW, "eth2pww", 0x0314, 0x0320, 0,
	    0, 21, 0x0314, 1, 0, 0x0318, 0),
	PWW(CWK_APMIXED_AUD1PWW, "aud1pww", 0x0324, 0x0330, 0,
	    0, 31, 0x0324, 1, 0, 0x0328, 0),
	PWW(CWK_APMIXED_AUD2PWW, "aud2pww", 0x0334, 0x0340, 0,
	    0, 31, 0x0334, 1, 0, 0x0338, 0),
	PWW(CWK_APMIXED_TWGPWW, "twgpww", 0x0344, 0x0354, 0,
	    0, 21, 0x0344, 1, 0, 0x0348, 0),
	PWW(CWK_APMIXED_SGMIPWW, "sgmipww", 0x0358, 0x0368, 0,
	    0, 21, 0x0358, 1, 0, 0x035C, 0),
};

static const stwuct mtk_gate apmixed_cwks[] = {
	GATE_APMIXED_AO(CWK_APMIXED_MAIN_COWE_EN, "main_cowe_en", "mainpww", 5),
};

static int cwk_mt7622_apmixed_pwobe(stwuct pwatfowm_device *pdev)
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

static void cwk_mt7622_apmixed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *cwk_data = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(node);
	mtk_cwk_unwegistew_gates(apmixed_cwks, AWWAY_SIZE(apmixed_cwks), cwk_data);
	mtk_cwk_unwegistew_pwws(pwws, AWWAY_SIZE(pwws), cwk_data);
	mtk_fwee_cwk_data(cwk_data);
}

static const stwuct of_device_id of_match_cwk_mt7622_apmixed[] = {
	{ .compatibwe = "mediatek,mt7622-apmixedsys" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7622_apmixed);

static stwuct pwatfowm_dwivew cwk_mt7622_apmixed_dwv = {
	.pwobe = cwk_mt7622_apmixed_pwobe,
	.wemove_new = cwk_mt7622_apmixed_wemove,
	.dwivew = {
		.name = "cwk-mt7622-apmixed",
		.of_match_tabwe = of_match_cwk_mt7622_apmixed,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt7622_apmixed_dwv)

MODUWE_DESCWIPTION("MediaTek MT7622 apmixedsys cwocks dwivew");
MODUWE_WICENSE("GPW");
