// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 MediaTek Inc.
 *                    Weiyi Wu <weiyi.wu@mediatek.com>
 * Copywight (c) 2023 Cowwabowa Wtd.
 *                    AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-pww.h"
#incwude "cwk-mtk.h"

#incwude <dt-bindings/cwock/mt2712-cwk.h>

#define MT2712_PWW_FMAX		(3000UW * MHZ)

#define CON0_MT2712_WST_BAW	BIT(24)

#define PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
			_pd_weg, _pd_shift, _tunew_weg, _tunew_en_weg,	\
			_tunew_en_bit, _pcw_weg, _pcw_shift,		\
			_div_tabwe) {					\
		.id = _id,						\
		.name = _name,						\
		.weg = _weg,						\
		.pww_weg = _pww_weg,					\
		.en_mask = _en_mask,					\
		.fwags = _fwags,					\
		.wst_baw_mask = CON0_MT2712_WST_BAW,			\
		.fmax = MT2712_PWW_FMAX,				\
		.pcwbits = _pcwbits,					\
		.pd_weg = _pd_weg,					\
		.pd_shift = _pd_shift,					\
		.tunew_weg = _tunew_weg,				\
		.tunew_en_weg = _tunew_en_weg,				\
		.tunew_en_bit = _tunew_en_bit,				\
		.pcw_weg = _pcw_weg,					\
		.pcw_shift = _pcw_shift,				\
		.div_tabwe = _div_tabwe,				\
	}

#define PWW(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
			_pd_weg, _pd_shift, _tunew_weg, _tunew_en_weg,	\
			_tunew_en_bit, _pcw_weg, _pcw_shift)		\
		PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags,	\
			_pcwbits, _pd_weg, _pd_shift, _tunew_weg,	\
			_tunew_en_weg, _tunew_en_bit, _pcw_weg,		\
			_pcw_shift, NUWW)

static const stwuct mtk_pww_div_tabwe awmca35pww_div_tabwe[] = {
	{ .div = 0, .fweq = MT2712_PWW_FMAX },
	{ .div = 1, .fweq = 1202500000 },
	{ .div = 2, .fweq = 500500000 },
	{ .div = 3, .fweq = 315250000 },
	{ .div = 4, .fweq = 157625000 },
	{ /* sentinew */ }
};

static const stwuct mtk_pww_div_tabwe awmca72pww_div_tabwe[] = {
	{ .div = 0, .fweq = MT2712_PWW_FMAX },
	{ .div = 1, .fweq = 994500000 },
	{ .div = 2, .fweq = 520000000 },
	{ .div = 3, .fweq = 315250000 },
	{ .div = 4, .fweq = 157625000 },
	{ /* sentinew */ }
};

static const stwuct mtk_pww_div_tabwe mmpww_div_tabwe[] = {
	{ .div = 0, .fweq = MT2712_PWW_FMAX },
	{ .div = 1, .fweq = 1001000000 },
	{ .div = 2, .fweq = 601250000 },
	{ .div = 3, .fweq = 250250000 },
	{ .div = 4, .fweq = 125125000 },
	{ /* sentinew */ }
};

static const stwuct mtk_pww_data pwws[] = {
	PWW(CWK_APMIXED_MAINPWW, "mainpww", 0x0230, 0x023C, 0xf0000100,
	    HAVE_WST_BAW, 31, 0x0230, 4, 0, 0, 0, 0x0234, 0),
	PWW(CWK_APMIXED_UNIVPWW, "univpww", 0x0240, 0x024C, 0xfe000100,
	    HAVE_WST_BAW, 31, 0x0240, 4, 0, 0, 0, 0x0244, 0),
	PWW(CWK_APMIXED_VCODECPWW, "vcodecpww", 0x0320, 0x032C, 0xc0000100,
	    0, 31, 0x0320, 4, 0, 0, 0, 0x0324, 0),
	PWW(CWK_APMIXED_VENCPWW, "vencpww", 0x0280, 0x028C, 0x00000100,
	    0, 31, 0x0280, 4, 0, 0, 0, 0x0284, 0),
	PWW(CWK_APMIXED_APWW1, "apww1", 0x0330, 0x0340, 0x00000100,
	    0, 31, 0x0330, 4, 0x0338, 0x0014, 0, 0x0334, 0),
	PWW(CWK_APMIXED_APWW2, "apww2", 0x0350, 0x0360, 0x00000100,
	    0, 31, 0x0350, 4, 0x0358, 0x0014, 1, 0x0354, 0),
	PWW(CWK_APMIXED_WVDSPWW, "wvdspww", 0x0370, 0x037c, 0x00000100,
	    0, 31, 0x0370, 4, 0, 0, 0, 0x0374, 0),
	PWW(CWK_APMIXED_WVDSPWW2, "wvdspww2", 0x0390, 0x039C, 0x00000100,
	    0, 31, 0x0390, 4, 0, 0, 0, 0x0394, 0),
	PWW(CWK_APMIXED_MSDCPWW, "msdcpww", 0x0270, 0x027C, 0x00000100,
	    0, 31, 0x0270, 4, 0, 0, 0, 0x0274, 0),
	PWW(CWK_APMIXED_MSDCPWW2, "msdcpww2", 0x0410, 0x041C, 0x00000100,
	    0, 31, 0x0410, 4, 0, 0, 0, 0x0414, 0),
	PWW(CWK_APMIXED_TVDPWW, "tvdpww", 0x0290, 0x029C, 0xc0000100,
	    0, 31, 0x0290, 4, 0, 0, 0, 0x0294, 0),
	PWW_B(CWK_APMIXED_MMPWW, "mmpww", 0x0250, 0x0260, 0x00000100,
	      0, 31, 0x0250, 4, 0, 0, 0, 0x0254, 0, mmpww_div_tabwe),
	PWW_B(CWK_APMIXED_AWMCA35PWW, "awmca35pww", 0x0100, 0x0110, 0xf0000100,
	      HAVE_WST_BAW, 31, 0x0100, 4, 0, 0, 0, 0x0104, 0, awmca35pww_div_tabwe),
	PWW_B(CWK_APMIXED_AWMCA72PWW, "awmca72pww", 0x0210, 0x0220, 0x00000100,
	      0, 31, 0x0210, 4, 0, 0, 0, 0x0214, 0, awmca72pww_div_tabwe),
	PWW(CWK_APMIXED_ETHEWPWW, "ethewpww", 0x0300, 0x030C, 0xc0000100,
	    0, 31, 0x0300, 4, 0, 0, 0, 0x0304, 0),
};

static int cwk_mt2712_apmixed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	int w;
	stwuct device_node *node = pdev->dev.of_node;

	cwk_data = mtk_awwoc_cwk_data(CWK_APMIXED_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	w = mtk_cwk_wegistew_pwws(node, pwws, AWWAY_SIZE(pwws), cwk_data);
	if (w)
		goto fwee_cwk_data;

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (w) {
		dev_eww(&pdev->dev, "Cannot wegistew cwock pwovidew: %d\n", w);
		goto unwegistew_pwws;
	}

	wetuwn 0;

unwegistew_pwws:
	mtk_cwk_unwegistew_pwws(pwws, AWWAY_SIZE(pwws), cwk_data);
fwee_cwk_data:
	mtk_fwee_cwk_data(cwk_data);
	wetuwn w;
}

static void cwk_mt2712_apmixed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *cwk_data = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(node);
	mtk_cwk_unwegistew_pwws(pwws, AWWAY_SIZE(pwws), cwk_data);
	mtk_fwee_cwk_data(cwk_data);
}

static const stwuct of_device_id of_match_cwk_mt2712_apmixed[] = {
	{ .compatibwe = "mediatek,mt2712-apmixedsys" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt2712_apmixed);

static stwuct pwatfowm_dwivew cwk_mt2712_apmixed_dwv = {
	.pwobe = cwk_mt2712_apmixed_pwobe,
	.wemove_new = cwk_mt2712_apmixed_wemove,
	.dwivew = {
		.name = "cwk-mt2712-apmixed",
		.of_match_tabwe = of_match_cwk_mt2712_apmixed,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt2712_apmixed_dwv)
MODUWE_WICENSE("GPW");
