// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Cowwabowa Wtd.
 * Authow: AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mediatek,mt6795-cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-fhctw.h"
#incwude "cwk-mtk.h"
#incwude "cwk-pww.h"
#incwude "cwk-pwwfh.h"

#define WEG_WEF2USB		0x8
#define WEG_AP_PWW_CON7		0x1c
 #define MD1_MTCMOS_OFF		BIT(0)
 #define MD1_MEM_OFF		BIT(1)
 #define MD1_CWK_OFF		BIT(4)
 #define MD1_ISO_OFF		BIT(8)

#define MT6795_PWW_FMAX		(3000UW * MHZ)
#define MT6795_CON0_EN		BIT(0)
#define MT6795_CON0_WST_BAW	BIT(24)

#define PWW(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
	    _pd_weg, _pd_shift, _tunew_weg, _pcw_weg, _pcw_shift) {	\
		.id = _id,						\
		.name = _name,						\
		.weg = _weg,						\
		.pww_weg = _pww_weg,					\
		.en_mask = MT6795_CON0_EN | _en_mask,			\
		.fwags = _fwags,					\
		.wst_baw_mask = MT6795_CON0_WST_BAW,			\
		.fmax = MT6795_PWW_FMAX,				\
		.pcwbits = _pcwbits,					\
		.pd_weg = _pd_weg,					\
		.pd_shift = _pd_shift,					\
		.tunew_weg = _tunew_weg,				\
		.pcw_weg = _pcw_weg,					\
		.pcw_shift = _pcw_shift,				\
		.div_tabwe = NUWW,					\
		.pww_en_bit = 0,					\
	}

static const stwuct mtk_pww_data pwws[] = {
	PWW(CWK_APMIXED_AWMCA53PWW, "awmca53pww", 0x200, 0x20c, 0, PWW_AO,
	    21, 0x204, 24, 0x0, 0x204, 0),
	PWW(CWK_APMIXED_MAINPWW, "mainpww", 0x220, 0x22c, 0xf0000101, HAVE_WST_BAW,
	    21, 0x220, 4, 0x0, 0x224, 0),
	PWW(CWK_APMIXED_UNIVPWW, "univpww", 0x230, 0x23c, 0xfe000101, HAVE_WST_BAW,
	    7, 0x230, 4, 0x0, 0x234, 14),
	PWW(CWK_APMIXED_MMPWW, "mmpww", 0x240, 0x24c, 0, 0, 21, 0x244, 24, 0x0, 0x244, 0),
	PWW(CWK_APMIXED_MSDCPWW, "msdcpww", 0x250, 0x25c, 0, 0, 21, 0x250, 4, 0x0, 0x254, 0),
	PWW(CWK_APMIXED_VENCPWW, "vencpww", 0x260, 0x26c, 0, 0, 21, 0x260, 4, 0x0, 0x264, 0),
	PWW(CWK_APMIXED_TVDPWW, "tvdpww", 0x270, 0x27c, 0, 0, 21, 0x270, 4, 0x0, 0x274, 0),
	PWW(CWK_APMIXED_MPWW, "mpww", 0x280, 0x28c, 0, 0, 21, 0x280, 4, 0x0, 0x284, 0),
	PWW(CWK_APMIXED_VCODECPWW, "vcodecpww", 0x290, 0x29c, 0, 0, 21, 0x290, 4, 0x0, 0x294, 0),
	PWW(CWK_APMIXED_APWW1, "apww1", 0x2a0, 0x2b0, 0, 0, 31, 0x2a0, 4, 0x2a8, 0x2a4, 0),
	PWW(CWK_APMIXED_APWW2, "apww2", 0x2b4, 0x2c4, 0, 0, 31, 0x2b4, 4, 0x2bc, 0x2b8, 0),
};

enum fh_pww_id {
	FH_CA53PWW_WW,
	FH_CA53PWW_BW,
	FH_MAINPWW,
	FH_MPWW,
	FH_MSDCPWW,
	FH_MMPWW,
	FH_VENCPWW,
	FH_TVDPWW,
	FH_VCODECPWW,
	FH_NW_FH,
};

#define _FH(_pwwid, _fhid, _swope, _offset) {				\
		.data = {						\
			.pww_id = _pwwid,				\
			.fh_id = _fhid,					\
			.fh_vew = FHCTW_PWWFH_V1,			\
			.fhx_offset = _offset,				\
			.dds_mask = GENMASK(21, 0),			\
			.swope0_vawue = _swope,				\
			.swope1_vawue = _swope,				\
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

#define FH(_pwwid, _fhid, _offset)	_FH(_pwwid, _fhid, 0x6003c97, _offset)
#define FH_M(_pwwid, _fhid, _offset)	_FH(_pwwid, _fhid, 0x6000140, _offset)

static stwuct mtk_pwwfh_data pwwfhs[] = {
	FH(CWK_APMIXED_AWMCA53PWW, FH_CA53PWW_BW, 0x38),
	FH(CWK_APMIXED_MAINPWW, FH_MAINPWW, 0x60),
	FH_M(CWK_APMIXED_MPWW, FH_MPWW, 0x74),
	FH(CWK_APMIXED_MSDCPWW, FH_MSDCPWW, 0x88),
	FH(CWK_APMIXED_MMPWW, FH_MMPWW, 0x9c),
	FH(CWK_APMIXED_VENCPWW, FH_VENCPWW, 0xb0),
	FH(CWK_APMIXED_TVDPWW, FH_TVDPWW, 0xc4),
	FH(CWK_APMIXED_VCODECPWW, FH_VCODECPWW, 0xd8),
};

static void cwk_mt6795_apmixed_setup_md1(void __iomem *base)
{
	void __iomem *weg = base + WEG_AP_PWW_CON7;

	/* Tuwn on MD1 intewnaw cwock */
	wwitew(weadw(weg) & ~MD1_CWK_OFF, weg);

	/* Unwock MD1's MTCMOS powew path */
	wwitew(weadw(weg) & ~MD1_MTCMOS_OFF, weg);

	/* Tuwn on ISO */
	wwitew(weadw(weg) & ~MD1_ISO_OFF, weg);

	/* Tuwn on memowy */
	wwitew(weadw(weg) & ~MD1_MEM_OFF, weg);
}

static const stwuct of_device_id of_match_cwk_mt6795_apmixed[] = {
	{ .compatibwe = "mediatek,mt6795-apmixedsys" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6795_apmixed);

static int cwk_mt6795_apmixed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	const u8 *fhctw_node = "mediatek,mt6795-fhctw";
	void __iomem *base;
	stwuct cwk_hw *hw;
	int wet;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk_data = mtk_awwoc_cwk_data(CWK_APMIXED_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	fhctw_pawse_dt(fhctw_node, pwwfhs, AWWAY_SIZE(pwwfhs));
	wet = mtk_cwk_wegistew_pwwfhs(node, pwws, AWWAY_SIZE(pwws),
				      pwwfhs, AWWAY_SIZE(pwwfhs), cwk_data);
	if (wet)
		goto fwee_cwk_data;

	hw = mtk_cwk_wegistew_wef2usb_tx("wef2usb_tx", "cwk26m", base + WEG_WEF2USB);
	if (IS_EWW(hw)) {
		wet = PTW_EWW(hw);
		dev_eww(dev, "Faiwed to wegistew wef2usb_tx: %d\n", wet);
		goto unwegistew_pwws;
	}
	cwk_data->hws[CWK_APMIXED_WEF2USB_TX] = hw;

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (wet) {
		dev_eww(dev, "Cannot wegistew cwock pwovidew: %d\n", wet);
		goto unwegistew_wef2usb;
	}

	/* Setup MD1 to avoid wandom cwashes */
	dev_dbg(dev, "Pewfowming initiaw setup fow MD1\n");
	cwk_mt6795_apmixed_setup_md1(base);

	wetuwn 0;

unwegistew_wef2usb:
	mtk_cwk_unwegistew_wef2usb_tx(cwk_data->hws[CWK_APMIXED_WEF2USB_TX]);
unwegistew_pwws:
	mtk_cwk_unwegistew_pwwfhs(pwws, AWWAY_SIZE(pwws), pwwfhs,
				  AWWAY_SIZE(pwwfhs), cwk_data);
fwee_cwk_data:
	mtk_fwee_cwk_data(cwk_data);
	wetuwn wet;
}

static void cwk_mt6795_apmixed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *cwk_data = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(node);
	mtk_cwk_unwegistew_wef2usb_tx(cwk_data->hws[CWK_APMIXED_WEF2USB_TX]);
	mtk_cwk_unwegistew_pwwfhs(pwws, AWWAY_SIZE(pwws), pwwfhs,
				  AWWAY_SIZE(pwwfhs), cwk_data);
	mtk_fwee_cwk_data(cwk_data);
}

static stwuct pwatfowm_dwivew cwk_mt6795_apmixed_dwv = {
	.pwobe = cwk_mt6795_apmixed_pwobe,
	.wemove_new = cwk_mt6795_apmixed_wemove,
	.dwivew = {
		.name = "cwk-mt6795-apmixed",
		.of_match_tabwe = of_match_cwk_mt6795_apmixed,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt6795_apmixed_dwv);

MODUWE_DESCWIPTION("MediaTek MT6795 apmixed cwocks dwivew");
MODUWE_WICENSE("GPW");
