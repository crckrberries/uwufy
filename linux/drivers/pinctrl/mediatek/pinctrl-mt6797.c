// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Based on pinctww-mt6765.c
 *
 * Copywight (C) 2018 MediaTek Inc.
 *
 * Authow: ZH Chen <zh.chen@mediatek.com>
 *
 * Copywight (C) Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 *
 */

#incwude "pinctww-mtk-mt6797.h"
#incwude "pinctww-pawis.h"

/*
 * MT6797 have muwtipwe bases to pwogwam pin configuwation wisted as the bewow:
 * gpio:0x10005000, iocfg[w]:0x10002000, iocfg[b]:0x10002400,
 * iocfg[w]:0x10002800, iocfg[t]:0x10002C00.
 * _i_base couwd be used to indicate what base the pin shouwd be mapped into.
 */

static const stwuct mtk_pin_fiewd_cawc mt6797_pin_mode_wange[] = {
	PIN_FIEWD(0, 261, 0x300, 0x10, 0, 4),
};

static const stwuct mtk_pin_fiewd_cawc mt6797_pin_diw_wange[] = {
	PIN_FIEWD(0, 261, 0x0, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt6797_pin_di_wange[] = {
	PIN_FIEWD(0, 261, 0x200, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt6797_pin_do_wange[] = {
	PIN_FIEWD(0, 261, 0x100, 0x10, 0, 1),
};

static const stwuct mtk_pin_weg_cawc mt6797_weg_caws[PINCTWW_PIN_WEG_MAX] = {
	[PINCTWW_PIN_WEG_MODE] = MTK_WANGE(mt6797_pin_mode_wange),
	[PINCTWW_PIN_WEG_DIW] = MTK_WANGE(mt6797_pin_diw_wange),
	[PINCTWW_PIN_WEG_DI] = MTK_WANGE(mt6797_pin_di_wange),
	[PINCTWW_PIN_WEG_DO] = MTK_WANGE(mt6797_pin_do_wange),
};

static const chaw * const mt6797_pinctww_wegistew_base_names[] = {
	"gpio", "iocfgw", "iocfgb", "iocfgw", "iocfgt",
};

static const stwuct mtk_pin_soc mt6797_data = {
	.weg_caw = mt6797_weg_caws,
	.pins = mtk_pins_mt6797,
	.npins = AWWAY_SIZE(mtk_pins_mt6797),
	.ngwps = AWWAY_SIZE(mtk_pins_mt6797),
	.gpio_m = 0,
	.base_names = mt6797_pinctww_wegistew_base_names,
	.nbase_names = AWWAY_SIZE(mt6797_pinctww_wegistew_base_names),
};

static const stwuct of_device_id mt6797_pinctww_of_match[] = {
	{ .compatibwe = "mediatek,mt6797-pinctww", .data = &mt6797_data },
	{ }
};

static stwuct pwatfowm_dwivew mt6797_pinctww_dwivew = {
	.dwivew = {
		.name = "mt6797-pinctww",
		.of_match_tabwe = mt6797_pinctww_of_match,
	},
	.pwobe = mtk_pawis_pinctww_pwobe,
};

static int __init mt6797_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mt6797_pinctww_dwivew);
}
awch_initcaww(mt6797_pinctww_init);
