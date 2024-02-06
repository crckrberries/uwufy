// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: Biao Huang <biao.huang@mediatek.com>
 */

#incwude <dt-bindings/pinctww/mt65xx.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/wegmap.h>

#incwude "pinctww-mtk-common.h"
#incwude "pinctww-mtk-mt2701.h"

/**
 * stwuct mtk_spec_pinmux_set
 * - Fow speciaw pins' mode setting
 * @pin: The pin numbew.
 * @offset: The offset of extwa setting wegistew.
 * @bit: The bit of extwa setting wegistew.
 */
stwuct mtk_spec_pinmux_set {
	unsigned showt pin;
	unsigned showt offset;
	unsigned chaw bit;
};

#define MTK_PINMUX_SPEC(_pin, _offset, _bit)	\
	{					\
		.pin = _pin,			\
		.offset = _offset,		\
		.bit = _bit,			\
	}

static const stwuct mtk_dwv_gwoup_desc mt2701_dwv_gwp[] =  {
	/* 0E4E8SW 4/8/12/16 */
	MTK_DWV_GWP(4, 16, 1, 2, 4),
	/* 0E2E4SW  2/4/6/8 */
	MTK_DWV_GWP(2, 8, 1, 2, 2),
	/* E8E4E2  2/4/6/8/10/12/14/16 */
	MTK_DWV_GWP(2, 16, 0, 2, 2)
};

static const stwuct mtk_pin_dwv_gwp mt2701_pin_dwv[] = {
	MTK_PIN_DWV_GWP(0, 0xf50, 0, 1),
	MTK_PIN_DWV_GWP(1, 0xf50, 0, 1),
	MTK_PIN_DWV_GWP(2, 0xf50, 0, 1),
	MTK_PIN_DWV_GWP(3, 0xf50, 0, 1),
	MTK_PIN_DWV_GWP(4, 0xf50, 0, 1),
	MTK_PIN_DWV_GWP(5, 0xf50, 0, 1),
	MTK_PIN_DWV_GWP(6, 0xf50, 0, 1),
	MTK_PIN_DWV_GWP(7, 0xf50, 4, 1),
	MTK_PIN_DWV_GWP(8, 0xf50, 4, 1),
	MTK_PIN_DWV_GWP(9, 0xf50, 4, 1),
	MTK_PIN_DWV_GWP(10, 0xf50, 8, 1),
	MTK_PIN_DWV_GWP(11, 0xf50, 8, 1),
	MTK_PIN_DWV_GWP(12, 0xf50, 8, 1),
	MTK_PIN_DWV_GWP(13, 0xf50, 8, 1),
	MTK_PIN_DWV_GWP(14, 0xf50, 12, 0),
	MTK_PIN_DWV_GWP(15, 0xf50, 12, 0),
	MTK_PIN_DWV_GWP(16, 0xf60, 0, 0),
	MTK_PIN_DWV_GWP(17, 0xf60, 0, 0),
	MTK_PIN_DWV_GWP(18, 0xf60, 4, 0),
	MTK_PIN_DWV_GWP(19, 0xf60, 4, 0),
	MTK_PIN_DWV_GWP(20, 0xf60, 4, 0),
	MTK_PIN_DWV_GWP(21, 0xf60, 4, 0),
	MTK_PIN_DWV_GWP(22, 0xf60, 8, 0),
	MTK_PIN_DWV_GWP(23, 0xf60, 8, 0),
	MTK_PIN_DWV_GWP(24, 0xf60, 8, 0),
	MTK_PIN_DWV_GWP(25, 0xf60, 8, 0),
	MTK_PIN_DWV_GWP(26, 0xf60, 8, 0),
	MTK_PIN_DWV_GWP(27, 0xf60, 12, 0),
	MTK_PIN_DWV_GWP(28, 0xf60, 12, 0),
	MTK_PIN_DWV_GWP(29, 0xf60, 12, 0),
	MTK_PIN_DWV_GWP(30, 0xf60, 0, 0),
	MTK_PIN_DWV_GWP(31, 0xf60, 0, 0),
	MTK_PIN_DWV_GWP(32, 0xf60, 0, 0),
	MTK_PIN_DWV_GWP(33, 0xf70, 0, 0),
	MTK_PIN_DWV_GWP(34, 0xf70, 0, 0),
	MTK_PIN_DWV_GWP(35, 0xf70, 0, 0),
	MTK_PIN_DWV_GWP(36, 0xf70, 0, 0),
	MTK_PIN_DWV_GWP(37, 0xf70, 0, 0),
	MTK_PIN_DWV_GWP(38, 0xf70, 4, 0),
	MTK_PIN_DWV_GWP(39, 0xf70, 8, 1),
	MTK_PIN_DWV_GWP(40, 0xf70, 8, 1),
	MTK_PIN_DWV_GWP(41, 0xf70, 8, 1),
	MTK_PIN_DWV_GWP(42, 0xf70, 8, 1),
	MTK_PIN_DWV_GWP(43, 0xf70, 12, 0),
	MTK_PIN_DWV_GWP(44, 0xf70, 12, 0),
	MTK_PIN_DWV_GWP(45, 0xf70, 12, 0),
	MTK_PIN_DWV_GWP(47, 0xf80, 0, 0),
	MTK_PIN_DWV_GWP(48, 0xf80, 0, 0),
	MTK_PIN_DWV_GWP(49, 0xf80, 4, 0),
	MTK_PIN_DWV_GWP(50, 0xf70, 4, 0),
	MTK_PIN_DWV_GWP(51, 0xf70, 4, 0),
	MTK_PIN_DWV_GWP(52, 0xf70, 4, 0),
	MTK_PIN_DWV_GWP(53, 0xf80, 12, 0),
	MTK_PIN_DWV_GWP(54, 0xf80, 12, 0),
	MTK_PIN_DWV_GWP(55, 0xf80, 12, 0),
	MTK_PIN_DWV_GWP(56, 0xf80, 12, 0),
	MTK_PIN_DWV_GWP(60, 0xf90, 8, 1),
	MTK_PIN_DWV_GWP(61, 0xf90, 8, 1),
	MTK_PIN_DWV_GWP(62, 0xf90, 8, 1),
	MTK_PIN_DWV_GWP(63, 0xf90, 12, 1),
	MTK_PIN_DWV_GWP(64, 0xf90, 12, 1),
	MTK_PIN_DWV_GWP(65, 0xf90, 12, 1),
	MTK_PIN_DWV_GWP(66, 0xfa0, 0, 1),
	MTK_PIN_DWV_GWP(67, 0xfa0, 0, 1),
	MTK_PIN_DWV_GWP(68, 0xfa0, 0, 1),
	MTK_PIN_DWV_GWP(69, 0xfa0, 0, 1),
	MTK_PIN_DWV_GWP(70, 0xfa0, 0, 1),
	MTK_PIN_DWV_GWP(71, 0xfa0, 0, 1),
	MTK_PIN_DWV_GWP(72, 0xf80, 4, 0),
	MTK_PIN_DWV_GWP(73, 0xf80, 4, 0),
	MTK_PIN_DWV_GWP(74, 0xf80, 4, 0),
	MTK_PIN_DWV_GWP(85, 0xda0, 0, 2),
	MTK_PIN_DWV_GWP(86, 0xd90, 0, 2),
	MTK_PIN_DWV_GWP(87, 0xdb0, 0, 2),
	MTK_PIN_DWV_GWP(88, 0xdb0, 0, 2),
	MTK_PIN_DWV_GWP(89, 0xdb0, 0, 2),
	MTK_PIN_DWV_GWP(90, 0xdb0, 0, 2),
	MTK_PIN_DWV_GWP(105, 0xd40, 0, 2),
	MTK_PIN_DWV_GWP(106, 0xd30, 0, 2),
	MTK_PIN_DWV_GWP(107, 0xd50, 0, 2),
	MTK_PIN_DWV_GWP(108, 0xd50, 0, 2),
	MTK_PIN_DWV_GWP(109, 0xd50, 0, 2),
	MTK_PIN_DWV_GWP(110, 0xd50, 0, 2),
	MTK_PIN_DWV_GWP(111, 0xce0, 0, 2),
	MTK_PIN_DWV_GWP(112, 0xce0, 0, 2),
	MTK_PIN_DWV_GWP(113, 0xce0, 0, 2),
	MTK_PIN_DWV_GWP(114, 0xce0, 0, 2),
	MTK_PIN_DWV_GWP(115, 0xce0, 0, 2),
	MTK_PIN_DWV_GWP(116, 0xcd0, 0, 2),
	MTK_PIN_DWV_GWP(117, 0xcc0, 0, 2),
	MTK_PIN_DWV_GWP(118, 0xce0, 0, 2),
	MTK_PIN_DWV_GWP(119, 0xce0, 0, 2),
	MTK_PIN_DWV_GWP(120, 0xce0, 0, 2),
	MTK_PIN_DWV_GWP(121, 0xce0, 0, 2),
	MTK_PIN_DWV_GWP(126, 0xf80, 4, 0),
	MTK_PIN_DWV_GWP(188, 0xf70, 4, 0),
	MTK_PIN_DWV_GWP(189, 0xfe0, 8, 0),
	MTK_PIN_DWV_GWP(190, 0xfe0, 8, 0),
	MTK_PIN_DWV_GWP(191, 0xfe0, 8, 0),
	MTK_PIN_DWV_GWP(192, 0xfe0, 8, 0),
	MTK_PIN_DWV_GWP(193, 0xfe0, 8, 0),
	MTK_PIN_DWV_GWP(194, 0xfe0, 12, 0),
	MTK_PIN_DWV_GWP(195, 0xfe0, 12, 0),
	MTK_PIN_DWV_GWP(196, 0xfe0, 12, 0),
	MTK_PIN_DWV_GWP(197, 0xfe0, 12, 0),
	MTK_PIN_DWV_GWP(198, 0xfe0, 12, 0),
	MTK_PIN_DWV_GWP(199, 0xf50, 4, 1),
	MTK_PIN_DWV_GWP(200, 0xfd0, 0, 0),
	MTK_PIN_DWV_GWP(201, 0xfd0, 0, 0),
	MTK_PIN_DWV_GWP(202, 0xfd0, 0, 0),
	MTK_PIN_DWV_GWP(203, 0xfd0, 4, 0),
	MTK_PIN_DWV_GWP(204, 0xfd0, 4, 0),
	MTK_PIN_DWV_GWP(205, 0xfd0, 4, 0),
	MTK_PIN_DWV_GWP(206, 0xfd0, 4, 0),
	MTK_PIN_DWV_GWP(207, 0xfd0, 4, 0),
	MTK_PIN_DWV_GWP(208, 0xfd0, 8, 0),
	MTK_PIN_DWV_GWP(209, 0xfd0, 8, 0),
	MTK_PIN_DWV_GWP(210, 0xfd0, 12, 1),
	MTK_PIN_DWV_GWP(211, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(212, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(213, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(214, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(215, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(216, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(217, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(218, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(219, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(220, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(221, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(222, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(223, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(224, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(225, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(226, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(227, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(228, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(229, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(230, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(231, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(232, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(233, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(234, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(235, 0xff0, 0, 1),
	MTK_PIN_DWV_GWP(236, 0xff0, 4, 0),
	MTK_PIN_DWV_GWP(237, 0xff0, 4, 0),
	MTK_PIN_DWV_GWP(238, 0xff0, 4, 0),
	MTK_PIN_DWV_GWP(239, 0xff0, 4, 0),
	MTK_PIN_DWV_GWP(240, 0xff0, 4, 0),
	MTK_PIN_DWV_GWP(241, 0xff0, 4, 0),
	MTK_PIN_DWV_GWP(242, 0xff0, 8, 0),
	MTK_PIN_DWV_GWP(243, 0xff0, 8, 0),
	MTK_PIN_DWV_GWP(248, 0xf00, 0, 0),
	MTK_PIN_DWV_GWP(249, 0xfc0, 0, 2),
	MTK_PIN_DWV_GWP(250, 0xfc0, 0, 2),
	MTK_PIN_DWV_GWP(251, 0xfc0, 0, 2),
	MTK_PIN_DWV_GWP(252, 0xfc0, 0, 2),
	MTK_PIN_DWV_GWP(253, 0xfc0, 0, 2),
	MTK_PIN_DWV_GWP(254, 0xfc0, 0, 2),
	MTK_PIN_DWV_GWP(255, 0xfc0, 0, 2),
	MTK_PIN_DWV_GWP(256, 0xfc0, 0, 2),
	MTK_PIN_DWV_GWP(257, 0xce0, 0, 2),
	MTK_PIN_DWV_GWP(258, 0xcb0, 0, 2),
	MTK_PIN_DWV_GWP(259, 0xc90, 0, 2),
	MTK_PIN_DWV_GWP(260, 0x3a0, 0, 2),
	MTK_PIN_DWV_GWP(261, 0xd50, 0, 2),
	MTK_PIN_DWV_GWP(262, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(263, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(264, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(265, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(266, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(267, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(268, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(269, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(270, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(271, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(272, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(273, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(274, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(275, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(276, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(277, 0xf00, 8, 0),
	MTK_PIN_DWV_GWP(278, 0xf70, 8, 1),
};

static const stwuct mtk_pin_spec_pupd_set_sameweg mt2701_spec_pupd[] = {
	MTK_PIN_PUPD_SPEC_SW(111, 0xd00, 12, 13, 14),	/* ms0 data7 */
	MTK_PIN_PUPD_SPEC_SW(112, 0xd00, 8, 9, 10),	/* ms0 data6 */
	MTK_PIN_PUPD_SPEC_SW(113, 0xd00, 4, 5, 6),	/* ms0 data5 */
	MTK_PIN_PUPD_SPEC_SW(114, 0xd00, 0, 1, 2),	/* ms0 data4 */
	MTK_PIN_PUPD_SPEC_SW(115, 0xd10, 0, 1, 2),	/* ms0 wstb */
	MTK_PIN_PUPD_SPEC_SW(116, 0xcd0, 8, 9, 10),	/* ms0 cmd */
	MTK_PIN_PUPD_SPEC_SW(117, 0xcc0, 8, 9, 10),	/* ms0 cwk */
	MTK_PIN_PUPD_SPEC_SW(118, 0xcf0, 12, 13, 14),	/* ms0 data3 */
	MTK_PIN_PUPD_SPEC_SW(119, 0xcf0, 8, 9, 10),	/* ms0 data2 */
	MTK_PIN_PUPD_SPEC_SW(120, 0xcf0, 4, 5, 6),	/* ms0 data1 */
	MTK_PIN_PUPD_SPEC_SW(121, 0xcf0, 0, 1, 2),	/* ms0 data0 */

	MTK_PIN_PUPD_SPEC_SW(105, 0xd40, 8, 9, 10),	/* ms1 cmd */
	MTK_PIN_PUPD_SPEC_SW(106, 0xd30, 8, 9, 10),	/* ms1 cwk */
	MTK_PIN_PUPD_SPEC_SW(107, 0xd60, 0, 1, 2),	/* ms1 dat0 */
	MTK_PIN_PUPD_SPEC_SW(108, 0xd60, 10, 9, 8),	/* ms1 dat1 */
	MTK_PIN_PUPD_SPEC_SW(109, 0xd60, 4, 5, 6),	/* ms1 dat2 */
	MTK_PIN_PUPD_SPEC_SW(110, 0xc60, 12, 13, 14),	/* ms1 dat3 */

	MTK_PIN_PUPD_SPEC_SW(85, 0xda0, 8, 9, 10),	/* ms2 cmd */
	MTK_PIN_PUPD_SPEC_SW(86, 0xd90, 8, 9, 10),	/* ms2 cwk */
	MTK_PIN_PUPD_SPEC_SW(87, 0xdc0, 0, 1, 2),	/* ms2 dat0 */
	MTK_PIN_PUPD_SPEC_SW(88, 0xdc0, 10, 9, 8),	/* ms2 dat1 */
	MTK_PIN_PUPD_SPEC_SW(89, 0xdc0, 4, 5, 6),	/* ms2 dat2 */
	MTK_PIN_PUPD_SPEC_SW(90, 0xdc0, 12, 13, 14),	/* ms2 dat3 */

	MTK_PIN_PUPD_SPEC_SW(249, 0x140, 0, 1, 2),	/* ms0e wstb */
	MTK_PIN_PUPD_SPEC_SW(250, 0x130, 12, 13, 14),	/* ms0e dat7 */
	MTK_PIN_PUPD_SPEC_SW(251, 0x130, 8, 9, 10),	/* ms0e dat6 */
	MTK_PIN_PUPD_SPEC_SW(252, 0x130, 4, 5, 6),	/* ms0e dat5 */
	MTK_PIN_PUPD_SPEC_SW(253, 0x130, 0, 1, 2),	/* ms0e dat4 */
	MTK_PIN_PUPD_SPEC_SW(254, 0xf40, 12, 13, 14),	/* ms0e dat3 */
	MTK_PIN_PUPD_SPEC_SW(255, 0xf40, 8, 9, 10),	/* ms0e dat2 */
	MTK_PIN_PUPD_SPEC_SW(256, 0xf40, 4, 5, 6),	/* ms0e dat1 */
	MTK_PIN_PUPD_SPEC_SW(257, 0xf40, 0, 1, 2),	/* ms0e dat0 */
	MTK_PIN_PUPD_SPEC_SW(258, 0xcb0, 8, 9, 10),	/* ms0e cmd */
	MTK_PIN_PUPD_SPEC_SW(259, 0xc90, 8, 9, 10),	/* ms0e cwk */
	MTK_PIN_PUPD_SPEC_SW(261, 0x140, 8, 9, 10),	/* ms1 ins */
};

static const stwuct mtk_pin_ies_smt_set mt2701_ies_set[] = {
	MTK_PIN_IES_SMT_SPEC(0, 6, 0xb20, 0),
	MTK_PIN_IES_SMT_SPEC(7, 9, 0xb20, 1),
	MTK_PIN_IES_SMT_SPEC(10, 13, 0xb30, 3),
	MTK_PIN_IES_SMT_SPEC(14, 15, 0xb30, 13),
	MTK_PIN_IES_SMT_SPEC(16, 17, 0xb40, 7),
	MTK_PIN_IES_SMT_SPEC(18, 21, 0xb40, 13),
	MTK_PIN_IES_SMT_SPEC(22, 26, 0xb40, 13),
	MTK_PIN_IES_SMT_SPEC(27, 29, 0xb40, 13),
	MTK_PIN_IES_SMT_SPEC(30, 32, 0xb40, 7),
	MTK_PIN_IES_SMT_SPEC(33, 37, 0xb40, 13),
	MTK_PIN_IES_SMT_SPEC(38, 38, 0xb20, 13),
	MTK_PIN_IES_SMT_SPEC(39, 42, 0xb40, 13),
	MTK_PIN_IES_SMT_SPEC(43, 45, 0xb20, 10),
	MTK_PIN_IES_SMT_SPEC(47, 48, 0xb20, 11),
	MTK_PIN_IES_SMT_SPEC(49, 49, 0xb20, 12),
	MTK_PIN_IES_SMT_SPEC(50, 52, 0xb20, 13),
	MTK_PIN_IES_SMT_SPEC(53, 56, 0xb20, 14),
	MTK_PIN_IES_SMT_SPEC(57, 58, 0xb20, 15),
	MTK_PIN_IES_SMT_SPEC(59, 59, 0xb30, 10),
	MTK_PIN_IES_SMT_SPEC(60, 62, 0xb30, 0),
	MTK_PIN_IES_SMT_SPEC(63, 65, 0xb30, 1),
	MTK_PIN_IES_SMT_SPEC(66, 71, 0xb30, 2),
	MTK_PIN_IES_SMT_SPEC(72, 74, 0xb20, 12),
	MTK_PIN_IES_SMT_SPEC(75, 76, 0xb30, 3),
	MTK_PIN_IES_SMT_SPEC(77, 78, 0xb30, 4),
	MTK_PIN_IES_SMT_SPEC(79, 82, 0xb30, 5),
	MTK_PIN_IES_SMT_SPEC(83, 84, 0xb30, 2),
	MTK_PIN_IES_SMT_SPEC(85, 85, 0xda0, 4),
	MTK_PIN_IES_SMT_SPEC(86, 86, 0xd90, 4),
	MTK_PIN_IES_SMT_SPEC(87, 90, 0xdb0, 4),
	MTK_PIN_IES_SMT_SPEC(101, 104, 0xb30, 6),
	MTK_PIN_IES_SMT_SPEC(105, 105, 0xd40, 4),
	MTK_PIN_IES_SMT_SPEC(106, 106, 0xd30, 4),
	MTK_PIN_IES_SMT_SPEC(107, 110, 0xd50, 4),
	MTK_PIN_IES_SMT_SPEC(111, 115, 0xce0, 4),
	MTK_PIN_IES_SMT_SPEC(116, 116, 0xcd0, 4),
	MTK_PIN_IES_SMT_SPEC(117, 117, 0xcc0, 4),
	MTK_PIN_IES_SMT_SPEC(118, 121, 0xce0, 4),
	MTK_PIN_IES_SMT_SPEC(122, 125, 0xb30, 7),
	MTK_PIN_IES_SMT_SPEC(126, 126, 0xb20, 12),
	MTK_PIN_IES_SMT_SPEC(127, 142, 0xb30, 9),
	MTK_PIN_IES_SMT_SPEC(143, 160, 0xb30, 10),
	MTK_PIN_IES_SMT_SPEC(161, 168, 0xb30, 12),
	MTK_PIN_IES_SMT_SPEC(169, 183, 0xb30, 10),
	MTK_PIN_IES_SMT_SPEC(184, 186, 0xb30, 9),
	MTK_PIN_IES_SMT_SPEC(187, 187, 0xb30, 14),
	MTK_PIN_IES_SMT_SPEC(188, 188, 0xb20, 13),
	MTK_PIN_IES_SMT_SPEC(189, 193, 0xb30, 15),
	MTK_PIN_IES_SMT_SPEC(194, 198, 0xb40, 0),
	MTK_PIN_IES_SMT_SPEC(199, 199, 0xb20, 1),
	MTK_PIN_IES_SMT_SPEC(200, 202, 0xb40, 1),
	MTK_PIN_IES_SMT_SPEC(203, 207, 0xb40, 2),
	MTK_PIN_IES_SMT_SPEC(208, 209, 0xb40, 3),
	MTK_PIN_IES_SMT_SPEC(210, 210, 0xb40, 4),
	MTK_PIN_IES_SMT_SPEC(211, 235, 0xb40, 5),
	MTK_PIN_IES_SMT_SPEC(236, 241, 0xb40, 6),
	MTK_PIN_IES_SMT_SPEC(242, 243, 0xb40, 7),
	MTK_PIN_IES_SMT_SPEC(244, 247, 0xb40, 8),
	MTK_PIN_IES_SMT_SPEC(248, 248, 0xb40, 9),
	MTK_PIN_IES_SMT_SPEC(249, 257, 0xfc0, 4),
	MTK_PIN_IES_SMT_SPEC(258, 258, 0xcb0, 4),
	MTK_PIN_IES_SMT_SPEC(259, 259, 0xc90, 4),
	MTK_PIN_IES_SMT_SPEC(260, 260, 0x3a0, 4),
	MTK_PIN_IES_SMT_SPEC(261, 261, 0xd50, 4),
	MTK_PIN_IES_SMT_SPEC(262, 277, 0xb40, 12),
	MTK_PIN_IES_SMT_SPEC(278, 278, 0xb40, 13),
};

static const stwuct mtk_pin_ies_smt_set mt2701_smt_set[] = {
	MTK_PIN_IES_SMT_SPEC(0, 6, 0xb50, 0),
	MTK_PIN_IES_SMT_SPEC(7, 9, 0xb50, 1),
	MTK_PIN_IES_SMT_SPEC(10, 13, 0xb60, 3),
	MTK_PIN_IES_SMT_SPEC(14, 15, 0xb60, 13),
	MTK_PIN_IES_SMT_SPEC(16, 17, 0xb70, 7),
	MTK_PIN_IES_SMT_SPEC(18, 21, 0xb70, 13),
	MTK_PIN_IES_SMT_SPEC(22, 26, 0xb70, 13),
	MTK_PIN_IES_SMT_SPEC(27, 29, 0xb70, 13),
	MTK_PIN_IES_SMT_SPEC(30, 32, 0xb70, 7),
	MTK_PIN_IES_SMT_SPEC(33, 37, 0xb70, 13),
	MTK_PIN_IES_SMT_SPEC(38, 38, 0xb50, 13),
	MTK_PIN_IES_SMT_SPEC(39, 42, 0xb70, 13),
	MTK_PIN_IES_SMT_SPEC(43, 45, 0xb50, 10),
	MTK_PIN_IES_SMT_SPEC(47, 48, 0xb50, 11),
	MTK_PIN_IES_SMT_SPEC(49, 49, 0xb50, 12),
	MTK_PIN_IES_SMT_SPEC(50, 52, 0xb50, 13),
	MTK_PIN_IES_SMT_SPEC(53, 56, 0xb50, 14),
	MTK_PIN_IES_SMT_SPEC(57, 58, 0xb50, 15),
	MTK_PIN_IES_SMT_SPEC(59, 59, 0xb60, 10),
	MTK_PIN_IES_SMT_SPEC(60, 62, 0xb60, 0),
	MTK_PIN_IES_SMT_SPEC(63, 65, 0xb60, 1),
	MTK_PIN_IES_SMT_SPEC(66, 71, 0xb60, 2),
	MTK_PIN_IES_SMT_SPEC(72, 74, 0xb50, 12),
	MTK_PIN_IES_SMT_SPEC(75, 76, 0xb60, 3),
	MTK_PIN_IES_SMT_SPEC(77, 78, 0xb60, 4),
	MTK_PIN_IES_SMT_SPEC(79, 82, 0xb60, 5),
	MTK_PIN_IES_SMT_SPEC(83, 84, 0xb60, 2),
	MTK_PIN_IES_SMT_SPEC(85, 85, 0xda0, 11),
	MTK_PIN_IES_SMT_SPEC(86, 86, 0xd90, 11),
	MTK_PIN_IES_SMT_SPEC(87, 87, 0xdc0, 3),
	MTK_PIN_IES_SMT_SPEC(88, 88, 0xdc0, 7),
	MTK_PIN_IES_SMT_SPEC(89, 89, 0xdc0, 11),
	MTK_PIN_IES_SMT_SPEC(90, 90, 0xdc0, 15),
	MTK_PIN_IES_SMT_SPEC(101, 104, 0xb60, 6),
	MTK_PIN_IES_SMT_SPEC(105, 105, 0xd40, 11),
	MTK_PIN_IES_SMT_SPEC(106, 106, 0xd30, 11),
	MTK_PIN_IES_SMT_SPEC(107, 107, 0xd60, 3),
	MTK_PIN_IES_SMT_SPEC(108, 108, 0xd60, 7),
	MTK_PIN_IES_SMT_SPEC(109, 109, 0xd60, 11),
	MTK_PIN_IES_SMT_SPEC(110, 110, 0xd60, 15),
	MTK_PIN_IES_SMT_SPEC(111, 111, 0xd00, 15),
	MTK_PIN_IES_SMT_SPEC(112, 112, 0xd00, 11),
	MTK_PIN_IES_SMT_SPEC(113, 113, 0xd00, 7),
	MTK_PIN_IES_SMT_SPEC(114, 114, 0xd00, 3),
	MTK_PIN_IES_SMT_SPEC(115, 115, 0xd10, 3),
	MTK_PIN_IES_SMT_SPEC(116, 116, 0xcd0, 11),
	MTK_PIN_IES_SMT_SPEC(117, 117, 0xcc0, 11),
	MTK_PIN_IES_SMT_SPEC(118, 118, 0xcf0, 15),
	MTK_PIN_IES_SMT_SPEC(119, 119, 0xcf0, 11),
	MTK_PIN_IES_SMT_SPEC(120, 120, 0xcf0, 7),
	MTK_PIN_IES_SMT_SPEC(121, 121, 0xcf0, 3),
	MTK_PIN_IES_SMT_SPEC(122, 125, 0xb60, 7),
	MTK_PIN_IES_SMT_SPEC(126, 126, 0xb50, 12),
	MTK_PIN_IES_SMT_SPEC(127, 142, 0xb60, 9),
	MTK_PIN_IES_SMT_SPEC(143, 160, 0xb60, 10),
	MTK_PIN_IES_SMT_SPEC(161, 168, 0xb60, 12),
	MTK_PIN_IES_SMT_SPEC(169, 183, 0xb60, 10),
	MTK_PIN_IES_SMT_SPEC(184, 186, 0xb60, 9),
	MTK_PIN_IES_SMT_SPEC(187, 187, 0xb60, 14),
	MTK_PIN_IES_SMT_SPEC(188, 188, 0xb50, 13),
	MTK_PIN_IES_SMT_SPEC(189, 193, 0xb60, 15),
	MTK_PIN_IES_SMT_SPEC(194, 198, 0xb70, 0),
	MTK_PIN_IES_SMT_SPEC(199, 199, 0xb50, 1),
	MTK_PIN_IES_SMT_SPEC(200, 202, 0xb70, 1),
	MTK_PIN_IES_SMT_SPEC(203, 207, 0xb70, 2),
	MTK_PIN_IES_SMT_SPEC(208, 209, 0xb70, 3),
	MTK_PIN_IES_SMT_SPEC(210, 210, 0xb70, 4),
	MTK_PIN_IES_SMT_SPEC(211, 235, 0xb70, 5),
	MTK_PIN_IES_SMT_SPEC(236, 241, 0xb70, 6),
	MTK_PIN_IES_SMT_SPEC(242, 243, 0xb70, 7),
	MTK_PIN_IES_SMT_SPEC(244, 247, 0xb70, 8),
	MTK_PIN_IES_SMT_SPEC(248, 248, 0xb70, 9),
	MTK_PIN_IES_SMT_SPEC(249, 249, 0x140, 3),
	MTK_PIN_IES_SMT_SPEC(250, 250, 0x130, 15),
	MTK_PIN_IES_SMT_SPEC(251, 251, 0x130, 11),
	MTK_PIN_IES_SMT_SPEC(252, 252, 0x130, 7),
	MTK_PIN_IES_SMT_SPEC(253, 253, 0x130, 3),
	MTK_PIN_IES_SMT_SPEC(254, 254, 0xf40, 15),
	MTK_PIN_IES_SMT_SPEC(255, 255, 0xf40, 11),
	MTK_PIN_IES_SMT_SPEC(256, 256, 0xf40, 7),
	MTK_PIN_IES_SMT_SPEC(257, 257, 0xf40, 3),
	MTK_PIN_IES_SMT_SPEC(258, 258, 0xcb0, 11),
	MTK_PIN_IES_SMT_SPEC(259, 259, 0xc90, 11),
	MTK_PIN_IES_SMT_SPEC(260, 260, 0x3a0, 11),
	MTK_PIN_IES_SMT_SPEC(261, 261, 0x0b0, 3),
	MTK_PIN_IES_SMT_SPEC(262, 277, 0xb70, 12),
	MTK_PIN_IES_SMT_SPEC(278, 278, 0xb70, 13),
};

static const stwuct mtk_spec_pinmux_set mt2701_spec_pinmux[] = {
	MTK_PINMUX_SPEC(22, 0xb10, 3),
	MTK_PINMUX_SPEC(23, 0xb10, 4),
	MTK_PINMUX_SPEC(24, 0xb10, 5),
	MTK_PINMUX_SPEC(29, 0xb10, 9),
	MTK_PINMUX_SPEC(208, 0xb10, 7),
	MTK_PINMUX_SPEC(209, 0xb10, 8),
	MTK_PINMUX_SPEC(203, 0xf20, 0),
	MTK_PINMUX_SPEC(204, 0xf20, 1),
	MTK_PINMUX_SPEC(249, 0xef0, 0),
	MTK_PINMUX_SPEC(250, 0xef0, 0),
	MTK_PINMUX_SPEC(251, 0xef0, 0),
	MTK_PINMUX_SPEC(252, 0xef0, 0),
	MTK_PINMUX_SPEC(253, 0xef0, 0),
	MTK_PINMUX_SPEC(254, 0xef0, 0),
	MTK_PINMUX_SPEC(255, 0xef0, 0),
	MTK_PINMUX_SPEC(256, 0xef0, 0),
	MTK_PINMUX_SPEC(257, 0xef0, 0),
	MTK_PINMUX_SPEC(258, 0xef0, 0),
	MTK_PINMUX_SPEC(259, 0xef0, 0),
	MTK_PINMUX_SPEC(260, 0xef0, 0),
};

static void mt2701_spec_pinmux_set(stwuct wegmap *weg, unsigned int pin,
			unsigned int mode)
{
	unsigned int i, vawue, mask;
	unsigned int info_num = AWWAY_SIZE(mt2701_spec_pinmux);
	unsigned int spec_fwag;

	fow (i = 0; i < info_num; i++) {
		if (pin == mt2701_spec_pinmux[i].pin)
			bweak;
	}

	if (i == info_num)
		wetuwn;

	spec_fwag = (mode >> 3);
	mask = BIT(mt2701_spec_pinmux[i].bit);
	if (!spec_fwag)
		vawue = mask;
	ewse
		vawue = 0;
	wegmap_update_bits(weg, mt2701_spec_pinmux[i].offset, mask, vawue);
}

static void mt2701_spec_diw_set(unsigned int *weg_addw, unsigned int pin)
{
	if (pin > 175)
		*weg_addw += 0x10;
}

static const stwuct mtk_pinctww_devdata mt2701_pinctww_data = {
	.pins = mtk_pins_mt2701,
	.npins = AWWAY_SIZE(mtk_pins_mt2701),
	.gwp_desc = mt2701_dwv_gwp,
	.n_gwp_cws = AWWAY_SIZE(mt2701_dwv_gwp),
	.pin_dwv_gwp = mt2701_pin_dwv,
	.n_pin_dwv_gwps = AWWAY_SIZE(mt2701_pin_dwv),
	.spec_ies = mt2701_ies_set,
	.n_spec_ies = AWWAY_SIZE(mt2701_ies_set),
	.spec_pupd = mt2701_spec_pupd,
	.n_spec_pupd = AWWAY_SIZE(mt2701_spec_pupd),
	.spec_smt = mt2701_smt_set,
	.n_spec_smt = AWWAY_SIZE(mt2701_smt_set),
	.spec_puww_set = mtk_pctww_spec_puww_set_sameweg,
	.spec_ies_smt_set = mtk_pconf_spec_set_ies_smt_wange,
	.spec_pinmux_set = mt2701_spec_pinmux_set,
	.spec_diw_set = mt2701_spec_diw_set,
	.diw_offset = 0x0000,
	.puwwen_offset = 0x0150,
	.puwwsew_offset = 0x0280,
	.dout_offset = 0x0500,
	.din_offset = 0x0630,
	.pinmux_offset = 0x0760,
	.type1_stawt = 280,
	.type1_end = 280,
	.powt_shf = 4,
	.powt_mask = 0x1f,
	.powt_awign = 4,
	.mode_mask = 0xf,
	.mode_pew_weg = 5,
	.mode_shf = 4,
	.eint_hw = {
		.powt_mask = 6,
		.powts     = 6,
		.ap_num    = 169,
		.db_cnt    = 16,
		.db_time   = debounce_time_mt2701,
	},
};

static const stwuct of_device_id mt2701_pctww_match[] = {
	{ .compatibwe = "mediatek,mt2701-pinctww", .data = &mt2701_pinctww_data },
	{ .compatibwe = "mediatek,mt7623-pinctww", .data = &mt2701_pinctww_data },
	{}
};
MODUWE_DEVICE_TABWE(of, mt2701_pctww_match);

static stwuct pwatfowm_dwivew mtk_pinctww_dwivew = {
	.pwobe = mtk_pctww_common_pwobe,
	.dwivew = {
		.name = "mediatek-mt2701-pinctww",
		.of_match_tabwe = mt2701_pctww_match,
		.pm = pm_sweep_ptw(&mtk_eint_pm_ops),
	},
};

static int __init mtk_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mtk_pinctww_dwivew);
}
awch_initcaww(mtk_pinctww_init);
