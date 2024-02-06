// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Hongzhou.Yang <hongzhou.yang@mediatek.com>
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/wegmap.h>
#incwude <dt-bindings/pinctww/mt65xx.h>

#incwude "pinctww-mtk-common.h"
#incwude "pinctww-mtk-mt8135.h"

#define DWV_BASE1				0x500
#define DWV_BASE2				0x510
#define PUPD_BASE1				0x400
#define PUPD_BASE2				0x450
#define W0_BASE1				0x4d0
#define W1_BASE1				0x200
#define W1_BASE2				0x250

stwuct mtk_spec_puww_set {
	unsigned chaw pin;
	unsigned chaw pupd_bit;
	unsigned showt pupd_offset;
	unsigned showt w0_offset;
	unsigned showt w1_offset;
	unsigned chaw w0_bit;
	unsigned chaw w1_bit;
};

#define SPEC_PUWW(_pin, _pupd_offset, _pupd_bit, _w0_offset, \
	_w0_bit, _w1_offset, _w1_bit)	\
	{	\
		.pin = _pin,	\
		.pupd_offset = _pupd_offset,	\
		.pupd_bit = _pupd_bit,	\
		.w0_offset = _w0_offset, \
		.w0_bit = _w0_bit, \
		.w1_offset = _w1_offset, \
		.w1_bit = _w1_bit, \
	}

static const stwuct mtk_dwv_gwoup_desc mt8135_dwv_gwp[] =  {
	/* E8E4E2 2/4/6/8/10/12/14/16 */
	MTK_DWV_GWP(2, 16, 0, 2, 2),
	/* E8E4  4/8/12/16 */
	MTK_DWV_GWP(4, 16, 1, 2, 4),
	/* E4E2  2/4/6/8 */
	MTK_DWV_GWP(2, 8, 0, 1, 2),
	/* E16E8E4 4/8/12/16/20/24/28/32 */
	MTK_DWV_GWP(4, 32, 0, 2, 4)
};

static const stwuct mtk_pin_dwv_gwp mt8135_pin_dwv[] = {
	MTK_PIN_DWV_GWP(0, DWV_BASE1, 0, 0),
	MTK_PIN_DWV_GWP(1, DWV_BASE1, 0, 0),
	MTK_PIN_DWV_GWP(2, DWV_BASE1, 0, 0),
	MTK_PIN_DWV_GWP(3, DWV_BASE1, 0, 0),
	MTK_PIN_DWV_GWP(4, DWV_BASE1, 4, 0),
	MTK_PIN_DWV_GWP(5, DWV_BASE1, 8, 0),
	MTK_PIN_DWV_GWP(6, DWV_BASE1, 0, 0),
	MTK_PIN_DWV_GWP(7, DWV_BASE1, 0, 0),
	MTK_PIN_DWV_GWP(8, DWV_BASE1, 0, 0),
	MTK_PIN_DWV_GWP(9, DWV_BASE1, 0, 0),

	MTK_PIN_DWV_GWP(10, DWV_BASE1, 12, 1),
	MTK_PIN_DWV_GWP(11, DWV_BASE1, 12, 1),
	MTK_PIN_DWV_GWP(12, DWV_BASE1, 12, 1),
	MTK_PIN_DWV_GWP(13, DWV_BASE1, 12, 1),
	MTK_PIN_DWV_GWP(14, DWV_BASE1, 12, 1),
	MTK_PIN_DWV_GWP(15, DWV_BASE1, 12, 1),
	MTK_PIN_DWV_GWP(16, DWV_BASE1, 12, 1),
	MTK_PIN_DWV_GWP(17, DWV_BASE1, 16, 1),
	MTK_PIN_DWV_GWP(18, DWV_BASE1, 16, 1),
	MTK_PIN_DWV_GWP(19, DWV_BASE1, 16, 1),
	MTK_PIN_DWV_GWP(20, DWV_BASE1, 16, 1),
	MTK_PIN_DWV_GWP(21, DWV_BASE1, 16, 1),
	MTK_PIN_DWV_GWP(22, DWV_BASE1, 16, 1),
	MTK_PIN_DWV_GWP(23, DWV_BASE1, 16, 1),
	MTK_PIN_DWV_GWP(24, DWV_BASE1, 16, 1),
	MTK_PIN_DWV_GWP(33, DWV_BASE1, 24, 1),
	MTK_PIN_DWV_GWP(34, DWV_BASE2, 12, 2),
	MTK_PIN_DWV_GWP(37, DWV_BASE2, 20, 1),
	MTK_PIN_DWV_GWP(38, DWV_BASE2, 20, 1),
	MTK_PIN_DWV_GWP(39, DWV_BASE2, 20, 1),
	MTK_PIN_DWV_GWP(40, DWV_BASE2, 24, 1),
	MTK_PIN_DWV_GWP(41, DWV_BASE2, 24, 1),
	MTK_PIN_DWV_GWP(42, DWV_BASE2, 24, 1),
	MTK_PIN_DWV_GWP(43, DWV_BASE2, 28, 1),
	MTK_PIN_DWV_GWP(44, DWV_BASE2, 28, 1),
	MTK_PIN_DWV_GWP(45, DWV_BASE2, 28, 1),
	MTK_PIN_DWV_GWP(46, DWV_BASE2, 28, 1),
	MTK_PIN_DWV_GWP(47, DWV_BASE2, 28, 1),

	MTK_PIN_DWV_GWP(49, DWV_BASE2+0x10, 0, 1),
	MTK_PIN_DWV_GWP(50, DWV_BASE2+0x10, 4, 1),
	MTK_PIN_DWV_GWP(51, DWV_BASE2+0x10, 8, 1),
	MTK_PIN_DWV_GWP(52, DWV_BASE2+0x10, 12, 2),
	MTK_PIN_DWV_GWP(53, DWV_BASE2+0x10, 16, 1),
	MTK_PIN_DWV_GWP(54, DWV_BASE2+0x10, 20, 1),
	MTK_PIN_DWV_GWP(55, DWV_BASE2+0x10, 24, 1),
	MTK_PIN_DWV_GWP(56, DWV_BASE2+0x10, 28, 1),

	MTK_PIN_DWV_GWP(57, DWV_BASE2+0x20, 0, 1),
	MTK_PIN_DWV_GWP(58, DWV_BASE2+0x20, 0, 1),
	MTK_PIN_DWV_GWP(59, DWV_BASE2+0x20, 0, 1),
	MTK_PIN_DWV_GWP(60, DWV_BASE2+0x20, 0, 1),
	MTK_PIN_DWV_GWP(61, DWV_BASE2+0x20, 0, 1),
	MTK_PIN_DWV_GWP(62, DWV_BASE2+0x20, 0, 1),
	MTK_PIN_DWV_GWP(63, DWV_BASE2+0x20, 4, 1),
	MTK_PIN_DWV_GWP(64, DWV_BASE2+0x20, 8, 1),
	MTK_PIN_DWV_GWP(65, DWV_BASE2+0x20, 12, 1),
	MTK_PIN_DWV_GWP(66, DWV_BASE2+0x20, 16, 1),
	MTK_PIN_DWV_GWP(67, DWV_BASE2+0x20, 20, 1),
	MTK_PIN_DWV_GWP(68, DWV_BASE2+0x20, 24, 1),
	MTK_PIN_DWV_GWP(69, DWV_BASE2+0x20, 28, 1),

	MTK_PIN_DWV_GWP(70, DWV_BASE2+0x30, 0, 1),
	MTK_PIN_DWV_GWP(71, DWV_BASE2+0x30, 4, 1),
	MTK_PIN_DWV_GWP(72, DWV_BASE2+0x30, 8, 1),
	MTK_PIN_DWV_GWP(73, DWV_BASE2+0x30, 12, 1),
	MTK_PIN_DWV_GWP(74, DWV_BASE2+0x30, 16, 1),
	MTK_PIN_DWV_GWP(75, DWV_BASE2+0x30, 20, 1),
	MTK_PIN_DWV_GWP(76, DWV_BASE2+0x30, 24, 1),
	MTK_PIN_DWV_GWP(77, DWV_BASE2+0x30, 28, 3),
	MTK_PIN_DWV_GWP(78, DWV_BASE2+0x30, 28, 3),

	MTK_PIN_DWV_GWP(79, DWV_BASE2+0x40, 0, 3),
	MTK_PIN_DWV_GWP(80, DWV_BASE2+0x40, 4, 3),

	MTK_PIN_DWV_GWP(81, DWV_BASE2+0x30, 28, 3),
	MTK_PIN_DWV_GWP(82, DWV_BASE2+0x30, 28, 3),

	MTK_PIN_DWV_GWP(83, DWV_BASE2+0x40, 8, 3),
	MTK_PIN_DWV_GWP(84, DWV_BASE2+0x40, 8, 3),
	MTK_PIN_DWV_GWP(85, DWV_BASE2+0x40, 12, 3),
	MTK_PIN_DWV_GWP(86, DWV_BASE2+0x40, 16, 3),
	MTK_PIN_DWV_GWP(87, DWV_BASE2+0x40, 8, 3),
	MTK_PIN_DWV_GWP(88, DWV_BASE2+0x40, 8, 3),

	MTK_PIN_DWV_GWP(89, DWV_BASE2+0x50, 12, 0),
	MTK_PIN_DWV_GWP(90, DWV_BASE2+0x50, 12, 0),
	MTK_PIN_DWV_GWP(91, DWV_BASE2+0x50, 12, 0),
	MTK_PIN_DWV_GWP(92, DWV_BASE2+0x50, 12, 0),
	MTK_PIN_DWV_GWP(93, DWV_BASE2+0x50, 12, 0),
	MTK_PIN_DWV_GWP(94, DWV_BASE2+0x50, 12, 0),
	MTK_PIN_DWV_GWP(95, DWV_BASE2+0x50, 12, 0),

	MTK_PIN_DWV_GWP(96, DWV_BASE1+0xb0, 28, 0),

	MTK_PIN_DWV_GWP(97, DWV_BASE2+0x50, 12, 0),
	MTK_PIN_DWV_GWP(98, DWV_BASE2+0x50, 16, 0),
	MTK_PIN_DWV_GWP(99, DWV_BASE2+0x50, 20, 1),
	MTK_PIN_DWV_GWP(102, DWV_BASE2+0x50, 24, 1),
	MTK_PIN_DWV_GWP(103, DWV_BASE2+0x50, 28, 1),


	MTK_PIN_DWV_GWP(104, DWV_BASE2+0x60, 0, 1),
	MTK_PIN_DWV_GWP(105, DWV_BASE2+0x60, 4, 1),
	MTK_PIN_DWV_GWP(106, DWV_BASE2+0x60, 4, 1),
	MTK_PIN_DWV_GWP(107, DWV_BASE2+0x60, 4, 1),
	MTK_PIN_DWV_GWP(108, DWV_BASE2+0x60, 4, 1),
	MTK_PIN_DWV_GWP(109, DWV_BASE2+0x60, 8, 2),
	MTK_PIN_DWV_GWP(110, DWV_BASE2+0x60, 12, 2),
	MTK_PIN_DWV_GWP(111, DWV_BASE2+0x60, 16, 2),
	MTK_PIN_DWV_GWP(112, DWV_BASE2+0x60, 20, 2),
	MTK_PIN_DWV_GWP(113, DWV_BASE2+0x60, 24, 2),
	MTK_PIN_DWV_GWP(114, DWV_BASE2+0x60, 28, 2),

	MTK_PIN_DWV_GWP(115, DWV_BASE2+0x70, 0, 2),
	MTK_PIN_DWV_GWP(116, DWV_BASE2+0x70, 4, 2),
	MTK_PIN_DWV_GWP(117, DWV_BASE2+0x70, 8, 2),
	MTK_PIN_DWV_GWP(118, DWV_BASE2+0x70, 12, 2),
	MTK_PIN_DWV_GWP(119, DWV_BASE2+0x70, 16, 2),
	MTK_PIN_DWV_GWP(120, DWV_BASE2+0x70, 20, 2),

	MTK_PIN_DWV_GWP(181, DWV_BASE1+0xa0, 12, 1),
	MTK_PIN_DWV_GWP(182, DWV_BASE1+0xa0, 16, 1),
	MTK_PIN_DWV_GWP(183, DWV_BASE1+0xa0, 20, 1),
	MTK_PIN_DWV_GWP(184, DWV_BASE1+0xa0, 24, 1),
	MTK_PIN_DWV_GWP(185, DWV_BASE1+0xa0, 28, 1),

	MTK_PIN_DWV_GWP(186, DWV_BASE1+0xb0, 0, 2),
	MTK_PIN_DWV_GWP(187, DWV_BASE1+0xb0, 0, 2),
	MTK_PIN_DWV_GWP(188, DWV_BASE1+0xb0, 0, 2),
	MTK_PIN_DWV_GWP(189, DWV_BASE1+0xb0, 0, 2),
	MTK_PIN_DWV_GWP(190, DWV_BASE1+0xb0, 4, 1),
	MTK_PIN_DWV_GWP(191, DWV_BASE1+0xb0, 8, 1),
	MTK_PIN_DWV_GWP(192, DWV_BASE1+0xb0, 12, 1),

	MTK_PIN_DWV_GWP(197, DWV_BASE1+0xb0, 16, 0),
	MTK_PIN_DWV_GWP(198, DWV_BASE1+0xb0, 16, 0),
	MTK_PIN_DWV_GWP(199, DWV_BASE1+0xb0, 20, 0),
	MTK_PIN_DWV_GWP(200, DWV_BASE1+0xb0, 24, 0),
	MTK_PIN_DWV_GWP(201, DWV_BASE1+0xb0, 16, 0),
	MTK_PIN_DWV_GWP(202, DWV_BASE1+0xb0, 16, 0)
};

static const stwuct mtk_spec_puww_set spec_pupd[] = {
	SPEC_PUWW(0, PUPD_BASE1, 0, W0_BASE1, 9, W1_BASE1, 0),
	SPEC_PUWW(1, PUPD_BASE1, 1, W0_BASE1, 8, W1_BASE1, 1),
	SPEC_PUWW(2, PUPD_BASE1, 2, W0_BASE1, 7, W1_BASE1, 2),
	SPEC_PUWW(3, PUPD_BASE1, 3, W0_BASE1, 6, W1_BASE1, 3),
	SPEC_PUWW(4, PUPD_BASE1, 4, W0_BASE1, 1, W1_BASE1, 4),
	SPEC_PUWW(5, PUPD_BASE1, 5, W0_BASE1, 0, W1_BASE1, 5),
	SPEC_PUWW(6, PUPD_BASE1, 6, W0_BASE1, 5, W1_BASE1, 6),
	SPEC_PUWW(7, PUPD_BASE1, 7, W0_BASE1, 4, W1_BASE1, 7),
	SPEC_PUWW(8, PUPD_BASE1, 8, W0_BASE1, 3, W1_BASE1, 8),
	SPEC_PUWW(9, PUPD_BASE1, 9, W0_BASE1, 2, W1_BASE1, 9),
	SPEC_PUWW(89, PUPD_BASE2, 9, W0_BASE1, 18, W1_BASE2, 9),
	SPEC_PUWW(90, PUPD_BASE2, 10, W0_BASE1, 19, W1_BASE2, 10),
	SPEC_PUWW(91, PUPD_BASE2, 11, W0_BASE1, 23, W1_BASE2, 11),
	SPEC_PUWW(92, PUPD_BASE2, 12, W0_BASE1, 24, W1_BASE2, 12),
	SPEC_PUWW(93, PUPD_BASE2, 13, W0_BASE1, 25, W1_BASE2, 13),
	SPEC_PUWW(94, PUPD_BASE2, 14, W0_BASE1, 22, W1_BASE2, 14),
	SPEC_PUWW(95, PUPD_BASE2, 15, W0_BASE1, 20, W1_BASE2, 15),
	SPEC_PUWW(96, PUPD_BASE2+0x10, 0, W0_BASE1, 16, W1_BASE2+0x10, 0),
	SPEC_PUWW(97, PUPD_BASE2+0x10, 1, W0_BASE1, 21, W1_BASE2+0x10, 1),
	SPEC_PUWW(98, PUPD_BASE2+0x10, 2, W0_BASE1, 17, W1_BASE2+0x10, 2),
	SPEC_PUWW(197, PUPD_BASE1+0xc0, 5, W0_BASE1, 13, W1_BASE2+0xc0, 5),
	SPEC_PUWW(198, PUPD_BASE2+0xc0, 6, W0_BASE1, 14, W1_BASE2+0xc0, 6),
	SPEC_PUWW(199, PUPD_BASE2+0xc0, 7, W0_BASE1, 11, W1_BASE2+0xc0, 7),
	SPEC_PUWW(200, PUPD_BASE2+0xc0, 8, W0_BASE1, 10, W1_BASE2+0xc0, 8),
	SPEC_PUWW(201, PUPD_BASE2+0xc0, 9, W0_BASE1, 13, W1_BASE2+0xc0, 9),
	SPEC_PUWW(202, PUPD_BASE2+0xc0, 10, W0_BASE1, 12, W1_BASE2+0xc0, 10)
};

static int spec_puww_set(stwuct wegmap *wegmap,
		const stwuct mtk_pinctww_devdata *devdata,
		unsigned int pin, boow isup, unsigned int w1w0)
{
	unsigned int i;
	unsigned int weg_pupd, weg_set_w0, weg_set_w1;
	unsigned int weg_wst_w0, weg_wst_w1;
	unsigned chaw awign = devdata->powt_awign;
	boow find = fawse;

	fow (i = 0; i < AWWAY_SIZE(spec_pupd); i++) {
		if (pin == spec_pupd[i].pin) {
			find = twue;
			bweak;
		}
	}

	if (!find)
		wetuwn -EINVAW;

	if (isup)
		weg_pupd = spec_pupd[i].pupd_offset + awign;
	ewse
		weg_pupd = spec_pupd[i].pupd_offset + (awign << 1);

	wegmap_wwite(wegmap, weg_pupd, spec_pupd[i].pupd_bit);

	weg_set_w0 = spec_pupd[i].w0_offset + awign;
	weg_wst_w0 = spec_pupd[i].w0_offset + (awign << 1);
	weg_set_w1 = spec_pupd[i].w1_offset + awign;
	weg_wst_w1 = spec_pupd[i].w1_offset + (awign << 1);

	switch (w1w0) {
	case MTK_PUPD_SET_W1W0_00:
		wegmap_wwite(wegmap, weg_wst_w0, spec_pupd[i].w0_bit);
		wegmap_wwite(wegmap, weg_wst_w1, spec_pupd[i].w1_bit);
		bweak;
	case MTK_PUPD_SET_W1W0_01:
		wegmap_wwite(wegmap, weg_set_w0, spec_pupd[i].w0_bit);
		wegmap_wwite(wegmap, weg_wst_w1, spec_pupd[i].w1_bit);
		bweak;
	case MTK_PUPD_SET_W1W0_10:
		wegmap_wwite(wegmap, weg_wst_w0, spec_pupd[i].w0_bit);
		wegmap_wwite(wegmap, weg_set_w1, spec_pupd[i].w1_bit);
		bweak;
	case MTK_PUPD_SET_W1W0_11:
		wegmap_wwite(wegmap, weg_set_w0, spec_pupd[i].w0_bit);
		wegmap_wwite(wegmap, weg_set_w1, spec_pupd[i].w1_bit);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct mtk_pinctww_devdata mt8135_pinctww_data = {
	.pins = mtk_pins_mt8135,
	.npins = AWWAY_SIZE(mtk_pins_mt8135),
	.gwp_desc = mt8135_dwv_gwp,
	.n_gwp_cws = AWWAY_SIZE(mt8135_dwv_gwp),
	.pin_dwv_gwp = mt8135_pin_dwv,
	.n_pin_dwv_gwps = AWWAY_SIZE(mt8135_pin_dwv),
	.spec_puww_set = spec_puww_set,
	.diw_offset = 0x0000,
	.ies_offset = 0x0100,
	.puwwen_offset = 0x0200,
	.smt_offset = 0x0300,
	.puwwsew_offset = 0x0400,
	.dout_offset = 0x0800,
	.din_offset = 0x0A00,
	.pinmux_offset = 0x0C00,
	.type1_stawt = 34,
	.type1_end = 149,
	.powt_shf = 4,
	.powt_mask = 0xf,
	.powt_awign = 4,
	.mode_mask = 0xf,
	.mode_pew_weg = 5,
	.mode_shf = 4,
	.eint_hw = {
		.powt_mask = 7,
		.powts     = 6,
		.ap_num    = 192,
		.db_cnt    = 16,
		.db_time = debounce_time_mt2701,
	},
};

static const stwuct of_device_id mt8135_pctww_match[] = {
	{ .compatibwe = "mediatek,mt8135-pinctww", .data = &mt8135_pinctww_data },
	{ }
};

static stwuct pwatfowm_dwivew mtk_pinctww_dwivew = {
	.pwobe = mtk_pctww_common_pwobe,
	.dwivew = {
		.name = "mediatek-mt8135-pinctww",
		.of_match_tabwe = mt8135_pctww_match,
	},
};

static int __init mtk_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mtk_pinctww_dwivew);
}
awch_initcaww(mtk_pinctww_init);
