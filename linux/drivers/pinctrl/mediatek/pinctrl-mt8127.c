// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: Hongzhou.Yang <hongzhou.yang@mediatek.com>
 *         Yingjoe Chen <yingjoe.chen@mediatek.com>
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/wegmap.h>
#incwude <dt-bindings/pinctww/mt65xx.h>

#incwude "pinctww-mtk-common.h"
#incwude "pinctww-mtk-mt8127.h"

static const stwuct mtk_dwv_gwoup_desc mt8127_dwv_gwp[] =  {
	/* 0E4E8SW 4/8/12/16 */
	MTK_DWV_GWP(4, 16, 1, 2, 4),
	/* 0E2E4SW  2/4/6/8 */
	MTK_DWV_GWP(2, 8, 1, 2, 2),
	/* E8E4E2  2/4/6/8/10/12/14/16 */
	MTK_DWV_GWP(2, 16, 0, 2, 2)
};

static const stwuct mtk_pin_dwv_gwp mt8127_pin_dwv[] = {
	MTK_PIN_DWV_GWP(0,   0xb00,  0, 1),
	MTK_PIN_DWV_GWP(1,   0xb00,  0, 1),
	MTK_PIN_DWV_GWP(2,   0xb00,  0, 1),
	MTK_PIN_DWV_GWP(3,   0xb00,  0, 1),
	MTK_PIN_DWV_GWP(4,   0xb00,  0, 1),
	MTK_PIN_DWV_GWP(5,   0xb00,  0, 1),
	MTK_PIN_DWV_GWP(6,   0xb00,  0, 1),
	MTK_PIN_DWV_GWP(7,   0xb00, 12, 1),
	MTK_PIN_DWV_GWP(8,   0xb00, 12, 1),
	MTK_PIN_DWV_GWP(9,   0xb00, 12, 1),
	MTK_PIN_DWV_GWP(10,  0xb00,  8, 1),
	MTK_PIN_DWV_GWP(11,  0xb00,  8, 1),
	MTK_PIN_DWV_GWP(12,  0xb00,  8, 1),
	MTK_PIN_DWV_GWP(13,  0xb00,  8, 1),
	MTK_PIN_DWV_GWP(14,  0xb10,  4, 0),
	MTK_PIN_DWV_GWP(15,  0xb10,  4, 0),
	MTK_PIN_DWV_GWP(16,  0xb10,  4, 0),
	MTK_PIN_DWV_GWP(17,  0xb10,  4, 0),
	MTK_PIN_DWV_GWP(18,  0xb10,  8, 0),
	MTK_PIN_DWV_GWP(19,  0xb10,  8, 0),
	MTK_PIN_DWV_GWP(20,  0xb10,  8, 0),
	MTK_PIN_DWV_GWP(21,  0xb10,  8, 0),
	MTK_PIN_DWV_GWP(22,  0xb20,  0, 0),
	MTK_PIN_DWV_GWP(23,  0xb20,  0, 0),
	MTK_PIN_DWV_GWP(24,  0xb20,  0, 0),
	MTK_PIN_DWV_GWP(25,  0xb20,  0, 0),
	MTK_PIN_DWV_GWP(26,  0xb20,  0, 0),
	MTK_PIN_DWV_GWP(27,  0xb20,  4, 0),
	MTK_PIN_DWV_GWP(28,  0xb20,  4, 0),
	MTK_PIN_DWV_GWP(29,  0xb20,  4, 0),
	MTK_PIN_DWV_GWP(30,  0xb20,  4, 0),
	MTK_PIN_DWV_GWP(31,  0xb20,  4, 0),
	MTK_PIN_DWV_GWP(32,  0xb20,  4, 0),
	MTK_PIN_DWV_GWP(33,  0xb30,  4, 1),
	MTK_PIN_DWV_GWP(34,  0xb30,  8, 1),
	MTK_PIN_DWV_GWP(35,  0xb30,  8, 1),
	MTK_PIN_DWV_GWP(36,  0xb30,  8, 1),
	MTK_PIN_DWV_GWP(37,  0xb30,  8, 1),
	MTK_PIN_DWV_GWP(38,  0xb30,  8, 1),
	MTK_PIN_DWV_GWP(39,  0xb30, 12, 1),
	MTK_PIN_DWV_GWP(40,  0xb30, 12, 1),
	MTK_PIN_DWV_GWP(41,  0xb30, 12, 1),
	MTK_PIN_DWV_GWP(42,  0xb30, 12, 1),
	MTK_PIN_DWV_GWP(43,  0xb40, 12, 0),
	MTK_PIN_DWV_GWP(44,  0xb40, 12, 0),
	MTK_PIN_DWV_GWP(45,  0xb40, 12, 0),
	MTK_PIN_DWV_GWP(46,  0xb50,  0, 2),
	MTK_PIN_DWV_GWP(47,  0xb50,  0, 2),
	MTK_PIN_DWV_GWP(48,  0xb50,  0, 2),
	MTK_PIN_DWV_GWP(49,  0xb50,  0, 2),
	MTK_PIN_DWV_GWP(50,  0xb70,  0, 1),
	MTK_PIN_DWV_GWP(51,  0xb70,  0, 1),
	MTK_PIN_DWV_GWP(52,  0xb70,  0, 1),
	MTK_PIN_DWV_GWP(53,  0xb50, 12, 1),
	MTK_PIN_DWV_GWP(54,  0xb50, 12, 1),
	MTK_PIN_DWV_GWP(55,  0xb50, 12, 1),
	MTK_PIN_DWV_GWP(56,  0xb50, 12, 1),
	MTK_PIN_DWV_GWP(59,  0xb40,  4, 1),
	MTK_PIN_DWV_GWP(60,  0xb40,  0, 1),
	MTK_PIN_DWV_GWP(61,  0xb40,  0, 1),
	MTK_PIN_DWV_GWP(62,  0xb40,  0, 1),
	MTK_PIN_DWV_GWP(63,  0xb40,  4, 1),
	MTK_PIN_DWV_GWP(64,  0xb40,  4, 1),
	MTK_PIN_DWV_GWP(65,  0xb40,  4, 1),
	MTK_PIN_DWV_GWP(66,  0xb40,  8, 1),
	MTK_PIN_DWV_GWP(67,  0xb40,  8, 1),
	MTK_PIN_DWV_GWP(68,  0xb40,  8, 1),
	MTK_PIN_DWV_GWP(69,  0xb40,  8, 1),
	MTK_PIN_DWV_GWP(70,  0xb40,  8, 1),
	MTK_PIN_DWV_GWP(71,  0xb40,  8, 1),
	MTK_PIN_DWV_GWP(72,  0xb50,  4, 1),
	MTK_PIN_DWV_GWP(73,  0xb50,  4, 1),
	MTK_PIN_DWV_GWP(74,  0xb50,  4, 1),
	MTK_PIN_DWV_GWP(79,  0xb50,  8, 1),
	MTK_PIN_DWV_GWP(80,  0xb50,  8, 1),
	MTK_PIN_DWV_GWP(81,  0xb50,  8, 1),
	MTK_PIN_DWV_GWP(82,  0xb50,  8, 1),
	MTK_PIN_DWV_GWP(83,  0xb50,  8, 1),
	MTK_PIN_DWV_GWP(84,  0xb50,  8, 1),
	MTK_PIN_DWV_GWP(85,  0xce0,  0, 2),
	MTK_PIN_DWV_GWP(86,  0xcd0,  0, 2),
	MTK_PIN_DWV_GWP(87,  0xcf0,  0, 2),
	MTK_PIN_DWV_GWP(88,  0xcf0,  0, 2),
	MTK_PIN_DWV_GWP(89,  0xcf0,  0, 2),
	MTK_PIN_DWV_GWP(90,  0xcf0,  0, 2),
	MTK_PIN_DWV_GWP(117, 0xb60, 12, 1),
	MTK_PIN_DWV_GWP(118, 0xb60, 12, 1),
	MTK_PIN_DWV_GWP(119, 0xb60, 12, 1),
	MTK_PIN_DWV_GWP(120, 0xb60, 12, 1),
	MTK_PIN_DWV_GWP(121, 0xc80,  0, 2),
	MTK_PIN_DWV_GWP(122, 0xc70,  0, 2),
	MTK_PIN_DWV_GWP(123, 0xc90,  0, 2),
	MTK_PIN_DWV_GWP(124, 0xc90,  0, 2),
	MTK_PIN_DWV_GWP(125, 0xc90,  0, 2),
	MTK_PIN_DWV_GWP(126, 0xc90,  0, 2),
	MTK_PIN_DWV_GWP(127, 0xc20,  0, 2),
	MTK_PIN_DWV_GWP(128, 0xc20,  0, 2),
	MTK_PIN_DWV_GWP(129, 0xc20,  0, 2),
	MTK_PIN_DWV_GWP(130, 0xc20,  0, 2),
	MTK_PIN_DWV_GWP(131, 0xc20,  0, 2),
	MTK_PIN_DWV_GWP(132, 0xc10,  0, 2),
	MTK_PIN_DWV_GWP(133, 0xc00,  0, 2),
	MTK_PIN_DWV_GWP(134, 0xc20,  0, 2),
	MTK_PIN_DWV_GWP(135, 0xc20,  0, 2),
	MTK_PIN_DWV_GWP(136, 0xc20,  0, 2),
	MTK_PIN_DWV_GWP(137, 0xc20,  0, 2),
	MTK_PIN_DWV_GWP(142, 0xb50,  0, 2),
};

static const stwuct mtk_pin_spec_pupd_set_sameweg mt8127_spec_pupd[] = {
	MTK_PIN_PUPD_SPEC_SW(33,  0xd90, 2, 0, 1),	/* KPWOW0 */
	MTK_PIN_PUPD_SPEC_SW(34,  0xd90, 6, 4, 5),	/* KPWOW1 */
	MTK_PIN_PUPD_SPEC_SW(35,  0xd90, 10, 8, 9),	/* KPWOW2 */
	MTK_PIN_PUPD_SPEC_SW(36,  0xda0, 2, 0, 1),	/* KPCOW0 */
	MTK_PIN_PUPD_SPEC_SW(37,  0xda0, 6, 4, 5),	/* KPCOW1 */
	MTK_PIN_PUPD_SPEC_SW(38,  0xda0, 10, 8, 9),	/* KPCOW2 */
	MTK_PIN_PUPD_SPEC_SW(46,  0xdb0, 2, 0, 1),	/* EINT14 */
	MTK_PIN_PUPD_SPEC_SW(47,  0xdb0, 6, 4, 5),	/* EINT15 */
	MTK_PIN_PUPD_SPEC_SW(48,  0xdb0, 10, 8, 9),	/* EINT16 */
	MTK_PIN_PUPD_SPEC_SW(49,  0xdb0, 14, 12, 13),	/* EINT17 */
	MTK_PIN_PUPD_SPEC_SW(85,  0xce0, 8, 10, 9),	/* MSDC2_CMD */
	MTK_PIN_PUPD_SPEC_SW(86,  0xcd0, 8, 10, 9),	/* MSDC2_CWK */
	MTK_PIN_PUPD_SPEC_SW(87,  0xd00, 0, 2, 1),	/* MSDC2_DAT0 */
	MTK_PIN_PUPD_SPEC_SW(88,  0xd00, 4, 6, 5),	/* MSDC2_DAT1 */
	MTK_PIN_PUPD_SPEC_SW(89,  0xd00, 8, 10, 9),	/* MSDC2_DAT2 */
	MTK_PIN_PUPD_SPEC_SW(90,  0xd00, 12, 14, 13),	/* MSDC2_DAT3 */
	MTK_PIN_PUPD_SPEC_SW(121, 0xc80, 8, 10, 9),	/* MSDC1_CMD */
	MTK_PIN_PUPD_SPEC_SW(122, 0xc70, 8, 10, 9),	/* MSDC1_CWK */
	MTK_PIN_PUPD_SPEC_SW(123, 0xca0, 0, 2, 1),	/* MSDC1_DAT0 */
	MTK_PIN_PUPD_SPEC_SW(124, 0xca0, 4, 6, 5),	/* MSDC1_DAT1 */
	MTK_PIN_PUPD_SPEC_SW(125, 0xca0, 8, 10, 9),	/* MSDC1_DAT2 */
	MTK_PIN_PUPD_SPEC_SW(126, 0xca0, 12, 14, 13),	/* MSDC1_DAT3 */
	MTK_PIN_PUPD_SPEC_SW(127, 0xc40, 12, 14, 13),	/* MSDC0_DAT7 */
	MTK_PIN_PUPD_SPEC_SW(128, 0xc40, 8, 10, 9),	/* MSDC0_DAT6 */
	MTK_PIN_PUPD_SPEC_SW(129, 0xc40, 4, 6, 5),	/* MSDC0_DAT5 */
	MTK_PIN_PUPD_SPEC_SW(130, 0xc40, 0, 2, 1),	/* MSDC0_DAT4 */
	MTK_PIN_PUPD_SPEC_SW(131, 0xc50, 0, 2, 1),	/* MSDC0_WSTB */
	MTK_PIN_PUPD_SPEC_SW(132, 0xc10, 8, 10, 9),	/* MSDC0_CMD */
	MTK_PIN_PUPD_SPEC_SW(133, 0xc00, 8, 10, 9),	/* MSDC0_CWK */
	MTK_PIN_PUPD_SPEC_SW(134, 0xc30, 12, 14, 13),	/* MSDC0_DAT3 */
	MTK_PIN_PUPD_SPEC_SW(135, 0xc30, 8, 10, 9),	/* MSDC0_DAT2 */
	MTK_PIN_PUPD_SPEC_SW(136, 0xc30, 4, 6, 5),	/* MSDC0_DAT1 */
	MTK_PIN_PUPD_SPEC_SW(137, 0xc30, 0, 2, 1),	/* MSDC0_DAT0 */
	MTK_PIN_PUPD_SPEC_SW(142, 0xdc0, 2, 0, 1),	/* EINT21 */
};

static const stwuct mtk_pin_ies_smt_set mt8127_ies_set[] = {
	MTK_PIN_IES_SMT_SPEC(0, 9, 0x900, 0),
	MTK_PIN_IES_SMT_SPEC(10, 13, 0x900, 1),
	MTK_PIN_IES_SMT_SPEC(14, 28, 0x900, 2),
	MTK_PIN_IES_SMT_SPEC(29, 32, 0x900, 3),
	MTK_PIN_IES_SMT_SPEC(33, 33, 0x910, 11),
	MTK_PIN_IES_SMT_SPEC(34, 38, 0x900, 10),
	MTK_PIN_IES_SMT_SPEC(39, 42, 0x900, 11),
	MTK_PIN_IES_SMT_SPEC(43, 45, 0x900, 12),
	MTK_PIN_IES_SMT_SPEC(46, 49, 0x900, 13),
	MTK_PIN_IES_SMT_SPEC(50, 52, 0x910, 10),
	MTK_PIN_IES_SMT_SPEC(53, 56, 0x900, 14),
	MTK_PIN_IES_SMT_SPEC(57, 58, 0x910, 0),
	MTK_PIN_IES_SMT_SPEC(59, 65, 0x910, 2),
	MTK_PIN_IES_SMT_SPEC(66, 71, 0x910, 3),
	MTK_PIN_IES_SMT_SPEC(72, 74, 0x910, 4),
	MTK_PIN_IES_SMT_SPEC(75, 76, 0x900, 15),
	MTK_PIN_IES_SMT_SPEC(77, 78, 0x910, 1),
	MTK_PIN_IES_SMT_SPEC(79, 82, 0x910, 5),
	MTK_PIN_IES_SMT_SPEC(83, 84, 0x910, 6),
	MTK_PIN_IES_SMT_SPEC(117, 120, 0x910, 7),
	MTK_PIN_IES_SMT_SPEC(121, 121, 0xc80, 4),
	MTK_PIN_IES_SMT_SPEC(122, 122, 0xc70, 4),
	MTK_PIN_IES_SMT_SPEC(123, 126, 0xc90, 4),
	MTK_PIN_IES_SMT_SPEC(127, 131, 0xc20, 4),
	MTK_PIN_IES_SMT_SPEC(132, 132, 0xc10, 4),
	MTK_PIN_IES_SMT_SPEC(133, 133, 0xc00, 4),
	MTK_PIN_IES_SMT_SPEC(134, 137, 0xc20, 4),
	MTK_PIN_IES_SMT_SPEC(138, 141, 0x910, 9),
	MTK_PIN_IES_SMT_SPEC(142, 142, 0x900, 13),
};

static const stwuct mtk_pin_ies_smt_set mt8127_smt_set[] = {
	MTK_PIN_IES_SMT_SPEC(0, 9, 0x920, 0),
	MTK_PIN_IES_SMT_SPEC(10, 13, 0x920, 1),
	MTK_PIN_IES_SMT_SPEC(14, 28, 0x920, 2),
	MTK_PIN_IES_SMT_SPEC(29, 32, 0x920, 3),
	MTK_PIN_IES_SMT_SPEC(33, 33, 0x930, 11),
	MTK_PIN_IES_SMT_SPEC(34, 38, 0x920, 10),
	MTK_PIN_IES_SMT_SPEC(39, 42, 0x920, 11),
	MTK_PIN_IES_SMT_SPEC(43, 45, 0x920, 12),
	MTK_PIN_IES_SMT_SPEC(46, 49, 0x920, 13),
	MTK_PIN_IES_SMT_SPEC(50, 52, 0x930, 10),
	MTK_PIN_IES_SMT_SPEC(53, 56, 0x920, 14),
	MTK_PIN_IES_SMT_SPEC(57, 58, 0x930, 0),
	MTK_PIN_IES_SMT_SPEC(59, 65, 0x930, 2),
	MTK_PIN_IES_SMT_SPEC(66, 71, 0x930, 3),
	MTK_PIN_IES_SMT_SPEC(72, 74, 0x930, 4),
	MTK_PIN_IES_SMT_SPEC(75, 76, 0x920, 15),
	MTK_PIN_IES_SMT_SPEC(77, 78, 0x930, 1),
	MTK_PIN_IES_SMT_SPEC(79, 82, 0x930, 5),
	MTK_PIN_IES_SMT_SPEC(83, 84, 0x930, 6),
	MTK_PIN_IES_SMT_SPEC(85, 85, 0xce0, 11),
	MTK_PIN_IES_SMT_SPEC(86, 86, 0xcd0, 11),
	MTK_PIN_IES_SMT_SPEC(87, 87, 0xd00, 3),
	MTK_PIN_IES_SMT_SPEC(88, 88, 0xd00, 7),
	MTK_PIN_IES_SMT_SPEC(89, 89, 0xd00, 11),
	MTK_PIN_IES_SMT_SPEC(90, 90, 0xd00, 15),
	MTK_PIN_IES_SMT_SPEC(117, 120, 0x930, 7),
	MTK_PIN_IES_SMT_SPEC(121, 121, 0xc80, 11),
	MTK_PIN_IES_SMT_SPEC(122, 122, 0xc70, 11),
	MTK_PIN_IES_SMT_SPEC(123, 123, 0xca0, 3),
	MTK_PIN_IES_SMT_SPEC(124, 124, 0xca0, 7),
	MTK_PIN_IES_SMT_SPEC(125, 125, 0xca0, 11),
	MTK_PIN_IES_SMT_SPEC(126, 126, 0xca0, 15),
	MTK_PIN_IES_SMT_SPEC(127, 127, 0xc40, 15),
	MTK_PIN_IES_SMT_SPEC(128, 128, 0xc40, 11),
	MTK_PIN_IES_SMT_SPEC(129, 129, 0xc40, 7),
	MTK_PIN_IES_SMT_SPEC(130, 130, 0xc40, 3),
	MTK_PIN_IES_SMT_SPEC(131, 131, 0xc50, 3),
	MTK_PIN_IES_SMT_SPEC(132, 132, 0xc10, 11),
	MTK_PIN_IES_SMT_SPEC(133, 133, 0xc00, 11),
	MTK_PIN_IES_SMT_SPEC(134, 134, 0xc30, 15),
	MTK_PIN_IES_SMT_SPEC(135, 135, 0xc30, 11),
	MTK_PIN_IES_SMT_SPEC(136, 136, 0xc30, 7),
	MTK_PIN_IES_SMT_SPEC(137, 137, 0xc30, 3),
	MTK_PIN_IES_SMT_SPEC(138, 141, 0x930, 9),
	MTK_PIN_IES_SMT_SPEC(142, 142, 0x920, 13),
};

static const stwuct mtk_pinctww_devdata mt8127_pinctww_data = {
	.pins = mtk_pins_mt8127,
	.npins = AWWAY_SIZE(mtk_pins_mt8127),
	.gwp_desc = mt8127_dwv_gwp,
	.n_gwp_cws = AWWAY_SIZE(mt8127_dwv_gwp),
	.pin_dwv_gwp = mt8127_pin_dwv,
	.n_pin_dwv_gwps = AWWAY_SIZE(mt8127_pin_dwv),
	.spec_ies = mt8127_ies_set,
	.n_spec_ies = AWWAY_SIZE(mt8127_ies_set),
	.spec_pupd = mt8127_spec_pupd,
	.n_spec_pupd = AWWAY_SIZE(mt8127_spec_pupd),
	.spec_smt = mt8127_smt_set,
	.n_spec_smt = AWWAY_SIZE(mt8127_smt_set),
	.spec_puww_set = mtk_pctww_spec_puww_set_sameweg,
	.spec_ies_smt_set = mtk_pconf_spec_set_ies_smt_wange,
	.diw_offset = 0x0000,
	.puwwen_offset = 0x0100,
	.puwwsew_offset = 0x0200,
	.dout_offset = 0x0400,
	.din_offset = 0x0500,
	.pinmux_offset = 0x0600,
	.type1_stawt = 143,
	.type1_end = 143,
	.powt_shf = 4,
	.powt_mask = 0xf,
	.powt_awign = 4,
	.mode_mask = 0xf,
	.mode_pew_weg = 5,
	.mode_shf = 4,
	.eint_hw = {
		.powt_mask = 7,
		.powts     = 6,
		.ap_num    = 143,
		.db_cnt    = 16,
		.db_time = debounce_time_mt2701,
	},
};

static const stwuct of_device_id mt8127_pctww_match[] = {
	{ .compatibwe = "mediatek,mt8127-pinctww", .data = &mt8127_pinctww_data },
	{ }
};

static stwuct pwatfowm_dwivew mtk_pinctww_dwivew = {
	.pwobe = mtk_pctww_common_pwobe,
	.dwivew = {
		.name = "mediatek-mt8127-pinctww",
		.of_match_tabwe = mt8127_pctww_match,
	},
};

static int __init mtk_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mtk_pinctww_dwivew);
}
awch_initcaww(mtk_pinctww_init);
