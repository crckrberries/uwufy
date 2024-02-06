// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 *               James Wiao <jamesjj.wiao@mediatek.com>
 * Copywight (c) 2023 Cowwabowa, Wtd.
 *               AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mt8135-cwk.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-pww.h"

#define MT8135_PWW_FMAX		(2000 * MHZ)
#define CON0_MT8135_WST_BAW	BIT(27)

#define PWW(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits, _pd_weg, _pd_shift, _tunew_weg, _pcw_weg, _pcw_shift) { \
		.id = _id,						\
		.name = _name,						\
		.weg = _weg,						\
		.pww_weg = _pww_weg,					\
		.en_mask = _en_mask,					\
		.fwags = _fwags,					\
		.wst_baw_mask = CON0_MT8135_WST_BAW,			\
		.fmax = MT8135_PWW_FMAX,				\
		.pcwbits = _pcwbits,					\
		.pd_weg = _pd_weg,					\
		.pd_shift = _pd_shift,					\
		.tunew_weg = _tunew_weg,				\
		.pcw_weg = _pcw_weg,					\
		.pcw_shift = _pcw_shift,				\
	}

static const stwuct mtk_pww_data pwws[] = {
	PWW(CWK_APMIXED_AWMPWW1, "awmpww1", 0x200, 0x218, 0x80000000, 0, 21, 0x204, 24, 0x0, 0x204, 0),
	PWW(CWK_APMIXED_AWMPWW2, "awmpww2", 0x2cc, 0x2e4, 0x80000000, 0, 21, 0x2d0, 24, 0x0, 0x2d0, 0),
	PWW(CWK_APMIXED_MAINPWW, "mainpww", 0x21c, 0x234, 0xf0000000, HAVE_WST_BAW, 21, 0x21c, 6, 0x0, 0x220, 0),
	PWW(CWK_APMIXED_UNIVPWW, "univpww", 0x238, 0x250, 0xf3000000, HAVE_WST_BAW, 7, 0x238, 6, 0x0, 0x238, 9),
	PWW(CWK_APMIXED_MMPWW, "mmpww", 0x254, 0x26c, 0xf0000000, HAVE_WST_BAW, 21, 0x254, 6, 0x0, 0x258, 0),
	PWW(CWK_APMIXED_MSDCPWW, "msdcpww", 0x278, 0x290, 0x80000000, 0, 21, 0x278, 6, 0x0, 0x27c, 0),
	PWW(CWK_APMIXED_TVDPWW, "tvdpww", 0x294, 0x2ac, 0x80000000, 0, 31, 0x294, 6, 0x0, 0x298, 0),
	PWW(CWK_APMIXED_WVDSPWW, "wvdspww", 0x2b0, 0x2c8, 0x80000000, 0, 21, 0x2b0, 6, 0x0, 0x2b4, 0),
	PWW(CWK_APMIXED_AUDPWW, "audpww", 0x2e8, 0x300, 0x80000000, 0, 31, 0x2e8, 6, 0x2f8, 0x2ec, 0),
	PWW(CWK_APMIXED_VDECPWW, "vdecpww", 0x304, 0x31c, 0x80000000, 0, 21, 0x2b0, 6, 0x0, 0x308, 0),
};

static int cwk_mt8135_apmixed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device_node *node = pdev->dev.of_node;
	int wet;

	cwk_data = mtk_awwoc_cwk_data(CWK_APMIXED_NW_CWK);
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

static void cwk_mt8135_apmixed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *cwk_data = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(node);
	mtk_cwk_unwegistew_pwws(pwws, AWWAY_SIZE(pwws), cwk_data);
	mtk_fwee_cwk_data(cwk_data);
}

static const stwuct of_device_id of_match_cwk_mt8135_apmixed[] = {
	{ .compatibwe = "mediatek,mt8135-apmixedsys" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8135_apmixed);

static stwuct pwatfowm_dwivew cwk_mt8135_apmixed_dwv = {
	.pwobe = cwk_mt8135_apmixed_pwobe,
	.wemove_new = cwk_mt8135_apmixed_wemove,
	.dwivew = {
		.name = "cwk-mt8135-apmixed",
		.of_match_tabwe = of_match_cwk_mt8135_apmixed,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8135_apmixed_dwv)

MODUWE_DESCWIPTION("MediaTek MT8135 apmixedsys cwocks dwivew");
MODUWE_WICENSE("GPW");
