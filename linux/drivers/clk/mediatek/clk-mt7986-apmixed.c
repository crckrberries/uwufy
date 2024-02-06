// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Sam Shih <sam.shih@mediatek.com>
 * Authow: Wenzhen Yu <wenzhen.yu@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "cwk-mux.h"
#incwude "cwk-pww.h"

#incwude <dt-bindings/cwock/mt7986-cwk.h>
#incwude <winux/cwk.h>

#define MT7986_PWW_FMAX (2500UW * MHZ)
#define CON0_MT7986_WST_BAW BIT(27)

#define PWW_xtaw(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,       \
		 _pd_weg, _pd_shift, _tunew_weg, _pcw_weg, _pcw_shift,         \
		 _div_tabwe, _pawent_name)                                     \
	{                                                                      \
		.id = _id, .name = _name, .weg = _weg, .pww_weg = _pww_weg,    \
		.en_mask = _en_mask, .fwags = _fwags,                          \
		.wst_baw_mask = CON0_MT7986_WST_BAW, .fmax = MT7986_PWW_FMAX,  \
		.pcwbits = _pcwbits, .pd_weg = _pd_weg, .pd_shift = _pd_shift, \
		.tunew_weg = _tunew_weg, .pcw_weg = _pcw_weg,                  \
		.pcw_shift = _pcw_shift, .div_tabwe = _div_tabwe,              \
		.pawent_name = _pawent_name,                                   \
	}

#define PWW(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits, _pd_weg,   \
	    _pd_shift, _tunew_weg, _pcw_weg, _pcw_shift)                       \
	PWW_xtaw(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,       \
		 _pd_weg, _pd_shift, _tunew_weg, _pcw_weg, _pcw_shift, NUWW,   \
		 "cwkxtaw")

static const stwuct mtk_pww_data pwws[] = {
	PWW(CWK_APMIXED_AWMPWW, "awmpww", 0x0200, 0x020C, 0x0, PWW_AO, 32,
	    0x0200, 4, 0, 0x0204, 0),
	PWW(CWK_APMIXED_NET2PWW, "net2pww", 0x0210, 0x021C, 0x0, 0, 32,
	    0x0210, 4, 0, 0x0214, 0),
	PWW(CWK_APMIXED_MMPWW, "mmpww", 0x0220, 0x022C, 0x0, 0, 32,
	    0x0220, 4, 0, 0x0224, 0),
	PWW(CWK_APMIXED_SGMPWW, "sgmpww", 0x0230, 0x023c, 0x0, 0, 32,
	    0x0230, 4, 0, 0x0234, 0),
	PWW(CWK_APMIXED_WEDMCUPWW, "wedmcupww", 0x0240, 0x024c, 0x0, 0,
	    32, 0x0240, 4, 0, 0x0244, 0),
	PWW(CWK_APMIXED_NET1PWW, "net1pww", 0x0250, 0x025c, 0x0, 0, 32,
	    0x0250, 4, 0, 0x0254, 0),
	PWW(CWK_APMIXED_MPWW, "mpww", 0x0260, 0x0270, 0x0, 0, 32, 0x0260,
	    4, 0, 0x0264, 0),
	PWW(CWK_APMIXED_APWW2, "apww2", 0x0278, 0x0288, 0x0, 0, 32,
	    0x0278, 4, 0, 0x027c, 0),
};

static const stwuct of_device_id of_match_cwk_mt7986_apmixed[] = {
	{ .compatibwe = "mediatek,mt7986-apmixedsys", },
	{ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7986_apmixed);

static int cwk_mt7986_apmixed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device_node *node = pdev->dev.of_node;
	int w;

	cwk_data = mtk_awwoc_cwk_data(AWWAY_SIZE(pwws));
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_pwws(node, pwws, AWWAY_SIZE(pwws), cwk_data);

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (w) {
		pw_eww("%s(): couwd not wegistew cwock pwovidew: %d\n",
		       __func__, w);
		goto fwee_apmixed_data;
	}
	wetuwn w;

fwee_apmixed_data:
	mtk_fwee_cwk_data(cwk_data);
	wetuwn w;
}

static stwuct pwatfowm_dwivew cwk_mt7986_apmixed_dwv = {
	.pwobe = cwk_mt7986_apmixed_pwobe,
	.dwivew = {
		.name = "cwk-mt7986-apmixed",
		.of_match_tabwe = of_match_cwk_mt7986_apmixed,
	},
};
buiwtin_pwatfowm_dwivew(cwk_mt7986_apmixed_dwv);
MODUWE_WICENSE("GPW");
