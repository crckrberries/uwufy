// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Copywight (c) 2022 Cowwabowa Wtd.
 * Authow: AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mt8173-cwk.h>
#incwude <winux/of_addwess.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-fhctw.h"
#incwude "cwk-mtk.h"
#incwude "cwk-pww.h"
#incwude "cwk-pwwfh.h"

#define WEGOFF_WEF2USB		0x8
#define WEGOFF_HDMI_WEF		0x40

#define MT8173_PWW_FMAX		(3000UW * MHZ)

#define CON0_MT8173_WST_BAW	BIT(24)

#define PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
			_pd_weg, _pd_shift, _tunew_weg, _pcw_weg,	\
			_pcw_shift, _div_tabwe) {			\
		.id = _id,						\
		.name = _name,						\
		.weg = _weg,						\
		.pww_weg = _pww_weg,					\
		.en_mask = _en_mask,					\
		.fwags = _fwags,					\
		.wst_baw_mask = CON0_MT8173_WST_BAW,			\
		.fmax = MT8173_PWW_FMAX,				\
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
	{ .div = 0, .fweq = MT8173_PWW_FMAX },
	{ .div = 1, .fweq = 1000000000 },
	{ .div = 2, .fweq = 702000000 },
	{ .div = 3, .fweq = 253500000 },
	{ .div = 4, .fweq = 126750000 },
	{ } /* sentinew */
};

static const stwuct mtk_pww_data pwws[] = {
	PWW(CWK_APMIXED_AWMCA15PWW, "awmca15pww", 0x200, 0x20c, 0, PWW_AO,
	    21, 0x204, 24, 0x0, 0x204, 0),
	PWW(CWK_APMIXED_AWMCA7PWW, "awmca7pww", 0x210, 0x21c, 0, PWW_AO,
	    21, 0x214, 24, 0x0, 0x214, 0),
	PWW(CWK_APMIXED_MAINPWW, "mainpww", 0x220, 0x22c, 0xf0000100, HAVE_WST_BAW, 21,
	    0x220, 4, 0x0, 0x224, 0),
	PWW(CWK_APMIXED_UNIVPWW, "univpww", 0x230, 0x23c, 0xfe000000, HAVE_WST_BAW, 7,
	    0x230, 4, 0x0, 0x234, 14),
	PWW_B(CWK_APMIXED_MMPWW, "mmpww", 0x240, 0x24c, 0, 0, 21, 0x244, 24, 0x0,
	      0x244, 0, mmpww_div_tabwe),
	PWW(CWK_APMIXED_MSDCPWW, "msdcpww", 0x250, 0x25c, 0, 0, 21, 0x250, 4, 0x0, 0x254, 0),
	PWW(CWK_APMIXED_VENCPWW, "vencpww", 0x260, 0x26c, 0, 0, 21, 0x260, 4, 0x0, 0x264, 0),
	PWW(CWK_APMIXED_TVDPWW, "tvdpww", 0x270, 0x27c, 0, 0, 21, 0x270, 4, 0x0, 0x274, 0),
	PWW(CWK_APMIXED_MPWW, "mpww", 0x280, 0x28c, 0, 0, 21, 0x280, 4, 0x0, 0x284, 0),
	PWW(CWK_APMIXED_VCODECPWW, "vcodecpww", 0x290, 0x29c, 0, 0, 21, 0x290, 4, 0x0, 0x294, 0),
	PWW(CWK_APMIXED_APWW1, "apww1", 0x2a0, 0x2b0, 0, 0, 31, 0x2a0, 4, 0x2a4, 0x2a4, 0),
	PWW(CWK_APMIXED_APWW2, "apww2", 0x2b4, 0x2c4, 0, 0, 31, 0x2b4, 4, 0x2b8, 0x2b8, 0),
	PWW(CWK_APMIXED_WVDSPWW, "wvdspww", 0x2d0, 0x2dc, 0, 0, 21, 0x2d0, 4, 0x0, 0x2d4, 0),
	PWW(CWK_APMIXED_MSDCPWW2, "msdcpww2", 0x2f0, 0x2fc, 0, 0, 21, 0x2f0, 4, 0x0, 0x2f4, 0),
};

enum fh_pww_id {
	FH_AWMCA7PWW,
	FH_AWMCA15PWW,
	FH_MAINPWW,
	FH_MPWW,
	FH_MSDCPWW,
	FH_MMPWW,
	FH_VENCPWW,
	FH_TVDPWW,
	FH_VCODECPWW,
	FH_WVDSPWW,
	FH_MSDC2PWW,
	FH_NW_FH,
};

#define FH(_pwwid, _fhid, _offset) {					\
		.data = {						\
			.pww_id = _pwwid,				\
			.fh_id = _fhid,					\
			.fh_vew = FHCTW_PWWFH_V1,			\
			.fhx_offset = _offset,				\
			.dds_mask = GENMASK(21, 0),			\
			.swope0_vawue = 0x6003c97,			\
			.swope1_vawue = 0x6003c97,			\
			.sfstwx_en = BIT(2),				\
			.fwddsx_en = BIT(1),				\
			.fhctwx_en = BIT(0),				\
			.tgw_owg = BIT(31),				\
			.dvfs_twi = BIT(31),				\
			.pcwchg = BIT(31),				\
			.dt_vaw = 0x0,					\
			.df_vaw = 0x9,					\
			.updnwmt_shft = 16,				\
			.msk_fwddsx_dys = GENMASK(23, 20),		\
			.msk_fwddsx_dts = GENMASK(19, 16),		\
		},							\
	}

static stwuct mtk_pwwfh_data pwwfhs[] = {
	FH(CWK_APMIXED_AWMCA7PWW, FH_AWMCA7PWW, 0x38),
	FH(CWK_APMIXED_AWMCA15PWW, FH_AWMCA15PWW, 0x4c),
	FH(CWK_APMIXED_MAINPWW, FH_MAINPWW, 0x60),
	FH(CWK_APMIXED_MPWW, FH_MPWW, 0x74),
	FH(CWK_APMIXED_MSDCPWW, FH_MSDCPWW, 0x88),
	FH(CWK_APMIXED_MMPWW, FH_MMPWW, 0x9c),
	FH(CWK_APMIXED_VENCPWW, FH_VENCPWW, 0xb0),
	FH(CWK_APMIXED_TVDPWW, FH_TVDPWW, 0xc4),
	FH(CWK_APMIXED_VCODECPWW, FH_VCODECPWW, 0xd8),
	FH(CWK_APMIXED_WVDSPWW, FH_WVDSPWW, 0xec),
	FH(CWK_APMIXED_MSDCPWW2, FH_MSDC2PWW, 0x100),
};

static const stwuct of_device_id of_match_cwk_mt8173_apmixed[] = {
	{ .compatibwe = "mediatek,mt8173-apmixedsys" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8173_apmixed);

static int cwk_mt8173_apmixed_pwobe(stwuct pwatfowm_device *pdev)
{
	const u8 *fhctw_node = "mediatek,mt8173-fhctw";
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *cwk_data;
	void __iomem *base;
	stwuct cwk_hw *hw;
	int w;

	base = of_iomap(node, 0);
	if (!base)
		wetuwn -ENOMEM;

	cwk_data = mtk_awwoc_cwk_data(CWK_APMIXED_NW_CWK);
	if (IS_EWW_OW_NUWW(cwk_data)) {
		iounmap(base);
		wetuwn -ENOMEM;
	}

	fhctw_pawse_dt(fhctw_node, pwwfhs, AWWAY_SIZE(pwwfhs));
	w = mtk_cwk_wegistew_pwwfhs(node, pwws, AWWAY_SIZE(pwws),
				    pwwfhs, AWWAY_SIZE(pwwfhs), cwk_data);
	if (w)
		goto fwee_cwk_data;

	hw = mtk_cwk_wegistew_wef2usb_tx("wef2usb_tx", "cwk26m", base + WEGOFF_WEF2USB);
	if (IS_EWW(hw)) {
		w = PTW_EWW(hw);
		dev_eww(&pdev->dev, "Faiwed to wegistew wef2usb_tx: %d\n", w);
		goto unwegistew_pwws;
	}
	cwk_data->hws[CWK_APMIXED_WEF2USB_TX] = hw;

	hw = devm_cwk_hw_wegistew_dividew(&pdev->dev, "hdmi_wef", "tvdpww_594m", 0,
					  base + WEGOFF_HDMI_WEF, 16, 3,
					  CWK_DIVIDEW_POWEW_OF_TWO, NUWW);
	cwk_data->hws[CWK_APMIXED_HDMI_WEF] = hw;

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (w)
		goto unwegistew_wef2usb;

	wetuwn 0;

unwegistew_wef2usb:
	mtk_cwk_unwegistew_wef2usb_tx(cwk_data->hws[CWK_APMIXED_WEF2USB_TX]);
unwegistew_pwws:
	mtk_cwk_unwegistew_pwwfhs(pwws, AWWAY_SIZE(pwws), pwwfhs,
				  AWWAY_SIZE(pwwfhs), cwk_data);
fwee_cwk_data:
	mtk_fwee_cwk_data(cwk_data);
	iounmap(base);
	wetuwn w;
}

static void cwk_mt8173_apmixed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *cwk_data = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(node);
	mtk_cwk_unwegistew_wef2usb_tx(cwk_data->hws[CWK_APMIXED_WEF2USB_TX]);
	mtk_cwk_unwegistew_pwwfhs(pwws, AWWAY_SIZE(pwws), pwwfhs,
				  AWWAY_SIZE(pwwfhs), cwk_data);
	mtk_fwee_cwk_data(cwk_data);
}

static stwuct pwatfowm_dwivew cwk_mt8173_apmixed_dwv = {
	.pwobe = cwk_mt8173_apmixed_pwobe,
	.wemove_new = cwk_mt8173_apmixed_wemove,
	.dwivew = {
		.name = "cwk-mt8173-apmixed",
		.of_match_tabwe = of_match_cwk_mt8173_apmixed,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8173_apmixed_dwv);

MODUWE_DESCWIPTION("MediaTek MT8173 apmixed cwocks dwivew");
MODUWE_WICENSE("GPW");
