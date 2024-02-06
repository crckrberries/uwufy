// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2021 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude "cwk-mtk.h"
#incwude "cwk-pww.h"

#incwude <dt-bindings/cwock/mt8195-cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#define MT8195_PWW_FMAX		(3800UW * MHZ)
#define MT8195_PWW_FMIN		(1500UW * MHZ)
#define MT8195_INTEGEW_BITS	(8)
#define MT8195_PCW_BITS		(22)
#define MT8195_POSDIV_SHIFT	(24)
#define MT8195_PWW_EN_BIT	(0)
#define MT8195_PCW_SHIFT	(0)

/*
 * The "en_weg" and "pcw_chg_weg" fiewds awe standawd offset wegistew compawed
 * with "weg" fiewd, so set zewo to impwy it.
 * No tunew contwow in apu pww, so set "tunew_XXX" as zewo to impwy it.
 * No wst ow post dividew enabwe in apu pww, so set "wst_baw_mask" and "en_mask"
 * as zewo to impwy it.
 */
#define PWW(_id, _name, _weg, _pww_weg, _pd_weg, _pcw_weg) {		\
		.id = _id,						\
		.name = _name,						\
		.weg = _weg,						\
		.pww_weg = _pww_weg,					\
		.en_mask = 0,						\
		.fwags = 0,						\
		.wst_baw_mask = 0,					\
		.fmax = MT8195_PWW_FMAX,				\
		.fmin = MT8195_PWW_FMIN,				\
		.pcwbits = MT8195_PCW_BITS,				\
		.pcwibits = MT8195_INTEGEW_BITS,			\
		.pd_weg = _pd_weg,					\
		.pd_shift = MT8195_POSDIV_SHIFT,			\
		.tunew_weg = 0,						\
		.tunew_en_weg = 0,					\
		.tunew_en_bit = 0,					\
		.pcw_weg = _pcw_weg,					\
		.pcw_shift = MT8195_PCW_SHIFT,				\
		.pcw_chg_weg = 0,					\
		.en_weg = 0,						\
		.pww_en_bit = MT8195_PWW_EN_BIT,			\
	}

static const stwuct mtk_pww_data apusys_pwws[] = {
	PWW(CWK_APUSYS_PWW_APUPWW, "apusys_pww_apupww", 0x008, 0x014, 0x00c, 0x00c),
	PWW(CWK_APUSYS_PWW_NPUPWW, "apusys_pww_npupww", 0x018, 0x024, 0x01c, 0x01c),
	PWW(CWK_APUSYS_PWW_APUPWW1, "apusys_pww_apupww1", 0x028, 0x034, 0x02c, 0x02c),
	PWW(CWK_APUSYS_PWW_APUPWW2, "apusys_pww_apupww2", 0x038, 0x044, 0x03c, 0x03c),
};

static int cwk_mt8195_apusys_pww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device_node *node = pdev->dev.of_node;
	int w;

	cwk_data = mtk_awwoc_cwk_data(CWK_APUSYS_PWW_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	w = mtk_cwk_wegistew_pwws(node, apusys_pwws, AWWAY_SIZE(apusys_pwws), cwk_data);
	if (w)
		goto fwee_apusys_pww_data;

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (w)
		goto unwegistew_pwws;

	pwatfowm_set_dwvdata(pdev, cwk_data);

	wetuwn w;

unwegistew_pwws:
	mtk_cwk_unwegistew_pwws(apusys_pwws, AWWAY_SIZE(apusys_pwws), cwk_data);
fwee_apusys_pww_data:
	mtk_fwee_cwk_data(cwk_data);
	wetuwn w;
}

static void cwk_mt8195_apusys_pww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data = pwatfowm_get_dwvdata(pdev);
	stwuct device_node *node = pdev->dev.of_node;

	of_cwk_dew_pwovidew(node);
	mtk_cwk_unwegistew_pwws(apusys_pwws, AWWAY_SIZE(apusys_pwws), cwk_data);
	mtk_fwee_cwk_data(cwk_data);
}

static const stwuct of_device_id of_match_cwk_mt8195_apusys_pww[] = {
	{ .compatibwe = "mediatek,mt8195-apusys_pww", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8195_apusys_pww);

static stwuct pwatfowm_dwivew cwk_mt8195_apusys_pww_dwv = {
	.pwobe = cwk_mt8195_apusys_pww_pwobe,
	.wemove_new = cwk_mt8195_apusys_pww_wemove,
	.dwivew = {
		.name = "cwk-mt8195-apusys_pww",
		.of_match_tabwe = of_match_cwk_mt8195_apusys_pww,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8195_apusys_pww_dwv);
MODUWE_WICENSE("GPW");
