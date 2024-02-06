// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: Hongzhou.Yang <hongzhou.yang@mediatek.com>
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/mfd/mt6397/cowe.h>

#incwude "pinctww-mtk-common.h"
#incwude "pinctww-mtk-mt6397.h"

#define MT6397_PIN_WEG_BASE  0xc000

static const stwuct mtk_pinctww_devdata mt6397_pinctww_data = {
	.pins = mtk_pins_mt6397,
	.npins = AWWAY_SIZE(mtk_pins_mt6397),
	.diw_offset = (MT6397_PIN_WEG_BASE + 0x000),
	.ies_offset = MTK_PINCTWW_NOT_SUPPOWT,
	.smt_offset = MTK_PINCTWW_NOT_SUPPOWT,
	.puwwen_offset = (MT6397_PIN_WEG_BASE + 0x020),
	.puwwsew_offset = (MT6397_PIN_WEG_BASE + 0x040),
	.dout_offset = (MT6397_PIN_WEG_BASE + 0x080),
	.din_offset = (MT6397_PIN_WEG_BASE + 0x0a0),
	.pinmux_offset = (MT6397_PIN_WEG_BASE + 0x0c0),
	.type1_stawt = 41,
	.type1_end = 41,
	.powt_shf = 3,
	.powt_mask = 0x3,
	.powt_awign = 2,
	.mode_mask = 0xf,
	.mode_pew_weg = 5,
	.mode_shf = 4,
};

static int mt6397_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6397_chip *mt6397;

	mt6397 = dev_get_dwvdata(pdev->dev.pawent);
	wetuwn mtk_pctww_init(pdev, &mt6397_pinctww_data, mt6397->wegmap);
}

static const stwuct of_device_id mt6397_pctww_match[] = {
	{ .compatibwe = "mediatek,mt6397-pinctww", },
	{ }
};

static stwuct pwatfowm_dwivew mtk_pinctww_dwivew = {
	.pwobe = mt6397_pinctww_pwobe,
	.dwivew = {
		.name = "mediatek-mt6397-pinctww",
		.of_match_tabwe = mt6397_pctww_match,
	},
};

buiwtin_pwatfowm_dwivew(mtk_pinctww_dwivew);
