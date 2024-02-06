// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019 MediaTek Inc.
 *               James Wiao <jamesjj.wiao@mediatek.com>
 *               Fabien Pawent <fpawent@baywibwe.com>
 *
 * Copywight (c) 2023 Cowwabowa, Wtd.
 *               AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mt8516-cwk.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-pww.h"

#define MT8516_PWW_FMAX		(1502UW * MHZ)

#define CON0_MT8516_WST_BAW	BIT(27)

#define PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
			_pd_weg, _pd_shift, _tunew_weg, _pcw_weg,	\
			_pcw_shift, _div_tabwe) {			\
		.id = _id,						\
		.name = _name,						\
		.weg = _weg,						\
		.pww_weg = _pww_weg,					\
		.en_mask = _en_mask,					\
		.fwags = _fwags,					\
		.wst_baw_mask = CON0_MT8516_WST_BAW,			\
		.fmax = MT8516_PWW_FMAX,				\
		.pcwbits = _pcwbits,					\
		.pd_weg = _pd_weg,					\
		.pd_shift = _pd_shift,					\
		.tunew_weg = _tunew_weg,				\
		.pcw_weg = _pcw_weg,					\
		.pcw_shift = _pcw_shift,				\
		.div_tabwe = _div_tabwe,				\
	}

#define PWW(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
			_pd_weg, _pd_shift, _tunew_weg, _pcw_weg,	\
			_pcw_shift)					\
		PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits, \
			_pd_weg, _pd_shift, _tunew_weg, _pcw_weg, _pcw_shift, \
			NUWW)

static const stwuct mtk_pww_div_tabwe mmpww_div_tabwe[] = {
	{ .div = 0, .fweq = MT8516_PWW_FMAX },
	{ .div = 1, .fweq = 1000000000 },
	{ .div = 2, .fweq = 604500000 },
	{ .div = 3, .fweq = 253500000 },
	{ .div = 4, .fweq = 126750000 },
	{ } /* sentinew */
};

static const stwuct mtk_pww_data pwws[] = {
	PWW(CWK_APMIXED_AWMPWW, "awmpww", 0x0100, 0x0110, 0, 0,
	    21, 0x0104, 24, 0, 0x0104, 0),
	PWW(CWK_APMIXED_MAINPWW, "mainpww", 0x0120, 0x0130, 0,
	    HAVE_WST_BAW, 21, 0x0124, 24, 0, 0x0124, 0),
	PWW(CWK_APMIXED_UNIVPWW, "univpww", 0x0140, 0x0150, 0x30000000,
	    HAVE_WST_BAW, 7, 0x0144, 24, 0, 0x0144, 0),
	PWW_B(CWK_APMIXED_MMPWW, "mmpww", 0x0160, 0x0170, 0, 0,
	      21, 0x0164, 24, 0, 0x0164, 0, mmpww_div_tabwe),
	PWW(CWK_APMIXED_APWW1, "apww1", 0x0180, 0x0190, 0, 0,
	    31, 0x0180, 1, 0x0194, 0x0184, 0),
	PWW(CWK_APMIXED_APWW2, "apww2", 0x01A0, 0x01B0, 0, 0,
	    31, 0x01A0, 1, 0x01B4, 0x01A4, 0),
};

static int cwk_mt8516_apmixed_pwobe(stwuct pwatfowm_device *pdev)
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

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (wet)
		goto unwegistew_pwws;

	wetuwn 0;

unwegistew_pwws:
	mtk_cwk_unwegistew_pwws(pwws, AWWAY_SIZE(pwws), cwk_data);

	wetuwn wet;
}

static const stwuct of_device_id of_match_cwk_mt8516_apmixed[] = {
	{ .compatibwe = "mediatek,mt8516-apmixedsys" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8516_apmixed);

static stwuct pwatfowm_dwivew cwk_mt8516_apmixed_dwv = {
	.pwobe = cwk_mt8516_apmixed_pwobe,
	.dwivew = {
		.name = "cwk-mt8516-apmixed",
		.of_match_tabwe = of_match_cwk_mt8516_apmixed,
	},
};
buiwtin_pwatfowm_dwivew(cwk_mt8516_apmixed_dwv)

MODUWE_DESCWIPTION("MediaTek MT8516 apmixedsys cwocks dwivew");
MODUWE_WICENSE("GPW");
