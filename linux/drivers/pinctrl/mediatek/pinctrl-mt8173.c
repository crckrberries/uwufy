// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2015 MediaTek Inc.
 * Authow: Hongzhou.Yang <hongzhou.yang@mediatek.com>
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/wegmap.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <dt-bindings/pinctww/mt65xx.h>

#incwude "pinctww-mtk-common.h"
#incwude "pinctww-mtk-mt8173.h"

#define DWV_BASE				0xb00

static const stwuct mtk_pin_spec_pupd_set_sameweg mt8173_spec_pupd[] = {
	MTK_PIN_PUPD_SPEC_SW(119, 0xe00, 2, 1, 0),  /* KWOW0 */
	MTK_PIN_PUPD_SPEC_SW(120, 0xe00, 6, 5, 4),  /* KWOW1 */
	MTK_PIN_PUPD_SPEC_SW(121, 0xe00, 10, 9, 8), /* KWOW2 */
	MTK_PIN_PUPD_SPEC_SW(122, 0xe10, 2, 1, 0),  /* KCOW0 */
	MTK_PIN_PUPD_SPEC_SW(123, 0xe10, 6, 5, 4),  /* KCOW1 */
	MTK_PIN_PUPD_SPEC_SW(124, 0xe10, 10, 9, 8), /* KCOW2 */

	MTK_PIN_PUPD_SPEC_SW(67, 0xd10, 2, 1, 0),   /* ms0 DS */
	MTK_PIN_PUPD_SPEC_SW(68, 0xd00, 2, 1, 0),   /* ms0 WST */
	MTK_PIN_PUPD_SPEC_SW(66, 0xc10, 2, 1, 0),   /* ms0 cmd */
	MTK_PIN_PUPD_SPEC_SW(65, 0xc00, 2, 1, 0),   /* ms0 cwk */
	MTK_PIN_PUPD_SPEC_SW(57, 0xc20, 2, 1, 0),   /* ms0 data0 */
	MTK_PIN_PUPD_SPEC_SW(58, 0xc20, 2, 1, 0),   /* ms0 data1 */
	MTK_PIN_PUPD_SPEC_SW(59, 0xc20, 2, 1, 0),   /* ms0 data2 */
	MTK_PIN_PUPD_SPEC_SW(60, 0xc20, 2, 1, 0),   /* ms0 data3 */
	MTK_PIN_PUPD_SPEC_SW(61, 0xc20, 2, 1, 0),   /* ms0 data4 */
	MTK_PIN_PUPD_SPEC_SW(62, 0xc20, 2, 1, 0),   /* ms0 data5 */
	MTK_PIN_PUPD_SPEC_SW(63, 0xc20, 2, 1, 0),   /* ms0 data6 */
	MTK_PIN_PUPD_SPEC_SW(64, 0xc20, 2, 1, 0),   /* ms0 data7 */

	MTK_PIN_PUPD_SPEC_SW(78, 0xc50, 2, 1, 0),    /* ms1 cmd */
	MTK_PIN_PUPD_SPEC_SW(73, 0xd20, 2, 1, 0),    /* ms1 dat0 */
	MTK_PIN_PUPD_SPEC_SW(74, 0xd20, 6, 5, 4),    /* ms1 dat1 */
	MTK_PIN_PUPD_SPEC_SW(75, 0xd20, 10, 9, 8),   /* ms1 dat2 */
	MTK_PIN_PUPD_SPEC_SW(76, 0xd20, 14, 13, 12), /* ms1 dat3 */
	MTK_PIN_PUPD_SPEC_SW(77, 0xc40, 2, 1, 0),    /* ms1 cwk */

	MTK_PIN_PUPD_SPEC_SW(100, 0xd40, 2, 1, 0),    /* ms2 dat0 */
	MTK_PIN_PUPD_SPEC_SW(101, 0xd40, 6, 5, 4),    /* ms2 dat1 */
	MTK_PIN_PUPD_SPEC_SW(102, 0xd40, 10, 9, 8),   /* ms2 dat2 */
	MTK_PIN_PUPD_SPEC_SW(103, 0xd40, 14, 13, 12), /* ms2 dat3 */
	MTK_PIN_PUPD_SPEC_SW(104, 0xc80, 2, 1, 0),    /* ms2 cwk */
	MTK_PIN_PUPD_SPEC_SW(105, 0xc90, 2, 1, 0),    /* ms2 cmd */

	MTK_PIN_PUPD_SPEC_SW(22, 0xd60, 2, 1, 0),    /* ms3 dat0 */
	MTK_PIN_PUPD_SPEC_SW(23, 0xd60, 6, 5, 4),    /* ms3 dat1 */
	MTK_PIN_PUPD_SPEC_SW(24, 0xd60, 10, 9, 8),   /* ms3 dat2 */
	MTK_PIN_PUPD_SPEC_SW(25, 0xd60, 14, 13, 12), /* ms3 dat3 */
	MTK_PIN_PUPD_SPEC_SW(26, 0xcc0, 2, 1, 0),    /* ms3 cwk */
	MTK_PIN_PUPD_SPEC_SW(27, 0xcd0, 2, 1, 0)     /* ms3 cmd */
};

static const stwuct mtk_pin_ies_smt_set mt8173_smt_set[] = {
	MTK_PIN_IES_SMT_SPEC(0, 4, 0x930, 1),
	MTK_PIN_IES_SMT_SPEC(5, 9, 0x930, 2),
	MTK_PIN_IES_SMT_SPEC(10, 13, 0x930, 10),
	MTK_PIN_IES_SMT_SPEC(14, 15, 0x940, 10),
	MTK_PIN_IES_SMT_SPEC(16, 16, 0x930, 0),
	MTK_PIN_IES_SMT_SPEC(17, 17, 0x950, 2),
	MTK_PIN_IES_SMT_SPEC(18, 21, 0x940, 3),
	MTK_PIN_IES_SMT_SPEC(22, 25, 0xce0, 13),
	MTK_PIN_IES_SMT_SPEC(26, 26, 0xcc0, 13),
	MTK_PIN_IES_SMT_SPEC(27, 27, 0xcd0, 13),
	MTK_PIN_IES_SMT_SPEC(28, 28, 0xd70, 13),
	MTK_PIN_IES_SMT_SPEC(29, 32, 0x930, 3),
	MTK_PIN_IES_SMT_SPEC(33, 33, 0x930, 4),
	MTK_PIN_IES_SMT_SPEC(34, 36, 0x930, 5),
	MTK_PIN_IES_SMT_SPEC(37, 38, 0x930, 6),
	MTK_PIN_IES_SMT_SPEC(39, 39, 0x930, 7),
	MTK_PIN_IES_SMT_SPEC(40, 41, 0x930, 9),
	MTK_PIN_IES_SMT_SPEC(42, 42, 0x940, 0),
	MTK_PIN_IES_SMT_SPEC(43, 44, 0x930, 11),
	MTK_PIN_IES_SMT_SPEC(45, 46, 0x930, 12),
	MTK_PIN_IES_SMT_SPEC(57, 64, 0xc20, 13),
	MTK_PIN_IES_SMT_SPEC(65, 65, 0xc10, 13),
	MTK_PIN_IES_SMT_SPEC(66, 66, 0xc00, 13),
	MTK_PIN_IES_SMT_SPEC(67, 67, 0xd10, 13),
	MTK_PIN_IES_SMT_SPEC(68, 68, 0xd00, 13),
	MTK_PIN_IES_SMT_SPEC(69, 72, 0x940, 14),
	MTK_PIN_IES_SMT_SPEC(73, 76, 0xc60, 13),
	MTK_PIN_IES_SMT_SPEC(77, 77, 0xc40, 13),
	MTK_PIN_IES_SMT_SPEC(78, 78, 0xc50, 13),
	MTK_PIN_IES_SMT_SPEC(79, 82, 0x940, 15),
	MTK_PIN_IES_SMT_SPEC(83, 83, 0x950, 0),
	MTK_PIN_IES_SMT_SPEC(84, 85, 0x950, 1),
	MTK_PIN_IES_SMT_SPEC(86, 91, 0x950, 2),
	MTK_PIN_IES_SMT_SPEC(92, 92, 0x930, 13),
	MTK_PIN_IES_SMT_SPEC(93, 95, 0x930, 14),
	MTK_PIN_IES_SMT_SPEC(96, 99, 0x930, 15),
	MTK_PIN_IES_SMT_SPEC(100, 103, 0xca0, 13),
	MTK_PIN_IES_SMT_SPEC(104, 104, 0xc80, 13),
	MTK_PIN_IES_SMT_SPEC(105, 105, 0xc90, 13),
	MTK_PIN_IES_SMT_SPEC(106, 107, 0x940, 4),
	MTK_PIN_IES_SMT_SPEC(108, 112, 0x940, 1),
	MTK_PIN_IES_SMT_SPEC(113, 116, 0x940, 2),
	MTK_PIN_IES_SMT_SPEC(117, 118, 0x940, 5),
	MTK_PIN_IES_SMT_SPEC(119, 124, 0x940, 6),
	MTK_PIN_IES_SMT_SPEC(125, 126, 0x940, 7),
	MTK_PIN_IES_SMT_SPEC(127, 127, 0x940, 0),
	MTK_PIN_IES_SMT_SPEC(128, 128, 0x950, 8),
	MTK_PIN_IES_SMT_SPEC(129, 130, 0x950, 9),
	MTK_PIN_IES_SMT_SPEC(131, 132, 0x950, 8),
	MTK_PIN_IES_SMT_SPEC(133, 134, 0x910, 8)
};

static const stwuct mtk_pin_ies_smt_set mt8173_ies_set[] = {
	MTK_PIN_IES_SMT_SPEC(0, 4, 0x900, 1),
	MTK_PIN_IES_SMT_SPEC(5, 9, 0x900, 2),
	MTK_PIN_IES_SMT_SPEC(10, 13, 0x900, 10),
	MTK_PIN_IES_SMT_SPEC(14, 15, 0x910, 10),
	MTK_PIN_IES_SMT_SPEC(16, 16, 0x900, 0),
	MTK_PIN_IES_SMT_SPEC(17, 17, 0x920, 2),
	MTK_PIN_IES_SMT_SPEC(18, 21, 0x910, 3),
	MTK_PIN_IES_SMT_SPEC(22, 25, 0xce0, 14),
	MTK_PIN_IES_SMT_SPEC(26, 26, 0xcc0, 14),
	MTK_PIN_IES_SMT_SPEC(27, 27, 0xcd0, 14),
	MTK_PIN_IES_SMT_SPEC(28, 28, 0xd70, 14),
	MTK_PIN_IES_SMT_SPEC(29, 32, 0x900, 3),
	MTK_PIN_IES_SMT_SPEC(33, 33, 0x900, 4),
	MTK_PIN_IES_SMT_SPEC(34, 36, 0x900, 5),
	MTK_PIN_IES_SMT_SPEC(37, 38, 0x900, 6),
	MTK_PIN_IES_SMT_SPEC(39, 39, 0x900, 7),
	MTK_PIN_IES_SMT_SPEC(40, 41, 0x900, 9),
	MTK_PIN_IES_SMT_SPEC(42, 42, 0x910, 0),
	MTK_PIN_IES_SMT_SPEC(43, 44, 0x900, 11),
	MTK_PIN_IES_SMT_SPEC(45, 46, 0x900, 12),
	MTK_PIN_IES_SMT_SPEC(57, 64, 0xc20, 14),
	MTK_PIN_IES_SMT_SPEC(65, 65, 0xc10, 14),
	MTK_PIN_IES_SMT_SPEC(66, 66, 0xc00, 14),
	MTK_PIN_IES_SMT_SPEC(67, 67, 0xd10, 14),
	MTK_PIN_IES_SMT_SPEC(68, 68, 0xd00, 14),
	MTK_PIN_IES_SMT_SPEC(69, 72, 0x910, 14),
	MTK_PIN_IES_SMT_SPEC(73, 76, 0xc60, 14),
	MTK_PIN_IES_SMT_SPEC(77, 77, 0xc40, 14),
	MTK_PIN_IES_SMT_SPEC(78, 78, 0xc50, 14),
	MTK_PIN_IES_SMT_SPEC(79, 82, 0x910, 15),
	MTK_PIN_IES_SMT_SPEC(83, 83, 0x920, 0),
	MTK_PIN_IES_SMT_SPEC(84, 85, 0x920, 1),
	MTK_PIN_IES_SMT_SPEC(86, 91, 0x920, 2),
	MTK_PIN_IES_SMT_SPEC(92, 92, 0x900, 13),
	MTK_PIN_IES_SMT_SPEC(93, 95, 0x900, 14),
	MTK_PIN_IES_SMT_SPEC(96, 99, 0x900, 15),
	MTK_PIN_IES_SMT_SPEC(100, 103, 0xca0, 14),
	MTK_PIN_IES_SMT_SPEC(104, 104, 0xc80, 14),
	MTK_PIN_IES_SMT_SPEC(105, 105, 0xc90, 14),
	MTK_PIN_IES_SMT_SPEC(106, 107, 0x910, 4),
	MTK_PIN_IES_SMT_SPEC(108, 112, 0x910, 1),
	MTK_PIN_IES_SMT_SPEC(113, 116, 0x910, 2),
	MTK_PIN_IES_SMT_SPEC(117, 118, 0x910, 5),
	MTK_PIN_IES_SMT_SPEC(119, 124, 0x910, 6),
	MTK_PIN_IES_SMT_SPEC(125, 126, 0x910, 7),
	MTK_PIN_IES_SMT_SPEC(127, 127, 0x910, 0),
	MTK_PIN_IES_SMT_SPEC(128, 128, 0x920, 8),
	MTK_PIN_IES_SMT_SPEC(129, 130, 0x920, 9),
	MTK_PIN_IES_SMT_SPEC(131, 132, 0x920, 8),
	MTK_PIN_IES_SMT_SPEC(133, 134, 0x910, 8)
};

static const stwuct mtk_dwv_gwoup_desc mt8173_dwv_gwp[] =  {
	/* 0E4E8SW 4/8/12/16 */
	MTK_DWV_GWP(4, 16, 1, 2, 4),
	/* 0E2E4SW  2/4/6/8 */
	MTK_DWV_GWP(2, 8, 1, 2, 2),
	/* E8E4E2  2/4/6/8/10/12/14/16 */
	MTK_DWV_GWP(2, 16, 0, 2, 2)
};

static const stwuct mtk_pin_dwv_gwp mt8173_pin_dwv[] = {
	MTK_PIN_DWV_GWP(0, DWV_BASE+0x20, 12, 0),
	MTK_PIN_DWV_GWP(1, DWV_BASE+0x20, 12, 0),
	MTK_PIN_DWV_GWP(2, DWV_BASE+0x20, 12, 0),
	MTK_PIN_DWV_GWP(3, DWV_BASE+0x20, 12, 0),
	MTK_PIN_DWV_GWP(4, DWV_BASE+0x20, 12, 0),
	MTK_PIN_DWV_GWP(5, DWV_BASE+0x30, 0, 0),
	MTK_PIN_DWV_GWP(6, DWV_BASE+0x30, 0, 0),
	MTK_PIN_DWV_GWP(7, DWV_BASE+0x30, 0, 0),
	MTK_PIN_DWV_GWP(8, DWV_BASE+0x30, 0, 0),
	MTK_PIN_DWV_GWP(9, DWV_BASE+0x30, 0, 0),
	MTK_PIN_DWV_GWP(10, DWV_BASE+0x30, 4, 1),
	MTK_PIN_DWV_GWP(11, DWV_BASE+0x30, 4, 1),
	MTK_PIN_DWV_GWP(12, DWV_BASE+0x30, 4, 1),
	MTK_PIN_DWV_GWP(13, DWV_BASE+0x30, 4, 1),
	MTK_PIN_DWV_GWP(14, DWV_BASE+0x40, 8, 1),
	MTK_PIN_DWV_GWP(15, DWV_BASE+0x40, 8, 1),
	MTK_PIN_DWV_GWP(16, DWV_BASE, 8, 1),
	MTK_PIN_DWV_GWP(17, 0xce0, 8, 2),
	MTK_PIN_DWV_GWP(22, 0xce0, 8, 2),
	MTK_PIN_DWV_GWP(23, 0xce0, 8, 2),
	MTK_PIN_DWV_GWP(24, 0xce0, 8, 2),
	MTK_PIN_DWV_GWP(25, 0xce0, 8, 2),
	MTK_PIN_DWV_GWP(26, 0xcc0, 8, 2),
	MTK_PIN_DWV_GWP(27, 0xcd0, 8, 2),
	MTK_PIN_DWV_GWP(28, 0xd70, 8, 2),
	MTK_PIN_DWV_GWP(29, DWV_BASE+0x80, 12, 1),
	MTK_PIN_DWV_GWP(30, DWV_BASE+0x80, 12, 1),
	MTK_PIN_DWV_GWP(31, DWV_BASE+0x80, 12, 1),
	MTK_PIN_DWV_GWP(32, DWV_BASE+0x80, 12, 1),
	MTK_PIN_DWV_GWP(33, DWV_BASE+0x10, 12, 1),
	MTK_PIN_DWV_GWP(34, DWV_BASE+0x10, 8, 1),
	MTK_PIN_DWV_GWP(35, DWV_BASE+0x10, 8, 1),
	MTK_PIN_DWV_GWP(36, DWV_BASE+0x10, 8, 1),
	MTK_PIN_DWV_GWP(37, DWV_BASE+0x10, 4, 1),
	MTK_PIN_DWV_GWP(38, DWV_BASE+0x10, 4, 1),
	MTK_PIN_DWV_GWP(39, DWV_BASE+0x20, 0, 0),
	MTK_PIN_DWV_GWP(40, DWV_BASE+0x20, 8, 0),
	MTK_PIN_DWV_GWP(41, DWV_BASE+0x20, 8, 0),
	MTK_PIN_DWV_GWP(42, DWV_BASE+0x50, 8, 1),
	MTK_PIN_DWV_GWP(57, 0xc20, 8, 2),
	MTK_PIN_DWV_GWP(58, 0xc20, 8, 2),
	MTK_PIN_DWV_GWP(59, 0xc20, 8, 2),
	MTK_PIN_DWV_GWP(60, 0xc20, 8, 2),
	MTK_PIN_DWV_GWP(61, 0xc20, 8, 2),
	MTK_PIN_DWV_GWP(62, 0xc20, 8, 2),
	MTK_PIN_DWV_GWP(63, 0xc20, 8, 2),
	MTK_PIN_DWV_GWP(64, 0xc20, 8, 2),
	MTK_PIN_DWV_GWP(65, 0xc00, 8, 2),
	MTK_PIN_DWV_GWP(66, 0xc10, 8, 2),
	MTK_PIN_DWV_GWP(67, 0xd10, 8, 2),
	MTK_PIN_DWV_GWP(68, 0xd00, 8, 2),
	MTK_PIN_DWV_GWP(69, DWV_BASE+0x80, 0, 1),
	MTK_PIN_DWV_GWP(70, DWV_BASE+0x80, 0, 1),
	MTK_PIN_DWV_GWP(71, DWV_BASE+0x80, 0, 1),
	MTK_PIN_DWV_GWP(72, DWV_BASE+0x80, 0, 1),
	MTK_PIN_DWV_GWP(73, 0xc60, 8, 2),
	MTK_PIN_DWV_GWP(74, 0xc60, 8, 2),
	MTK_PIN_DWV_GWP(75, 0xc60, 8, 2),
	MTK_PIN_DWV_GWP(76, 0xc60, 8, 2),
	MTK_PIN_DWV_GWP(77, 0xc40, 8, 2),
	MTK_PIN_DWV_GWP(78, 0xc50, 8, 2),
	MTK_PIN_DWV_GWP(79, DWV_BASE+0x70, 12, 1),
	MTK_PIN_DWV_GWP(80, DWV_BASE+0x70, 12, 1),
	MTK_PIN_DWV_GWP(81, DWV_BASE+0x70, 12, 1),
	MTK_PIN_DWV_GWP(82, DWV_BASE+0x70, 12, 1),
	MTK_PIN_DWV_GWP(83, DWV_BASE, 4, 1),
	MTK_PIN_DWV_GWP(84, DWV_BASE, 0, 1),
	MTK_PIN_DWV_GWP(85, DWV_BASE, 0, 1),
	MTK_PIN_DWV_GWP(85, DWV_BASE+0x60, 8, 1),
	MTK_PIN_DWV_GWP(86, DWV_BASE+0x60, 8, 1),
	MTK_PIN_DWV_GWP(87, DWV_BASE+0x60, 8, 1),
	MTK_PIN_DWV_GWP(88, DWV_BASE+0x60, 8, 1),
	MTK_PIN_DWV_GWP(89, DWV_BASE+0x60, 8, 1),
	MTK_PIN_DWV_GWP(90, DWV_BASE+0x60, 8, 1),
	MTK_PIN_DWV_GWP(91, DWV_BASE+0x60, 8, 1),
	MTK_PIN_DWV_GWP(92, DWV_BASE+0x60, 4, 0),
	MTK_PIN_DWV_GWP(93, DWV_BASE+0x60, 0, 0),
	MTK_PIN_DWV_GWP(94, DWV_BASE+0x60, 0, 0),
	MTK_PIN_DWV_GWP(95, DWV_BASE+0x60, 0, 0),
	MTK_PIN_DWV_GWP(96, DWV_BASE+0x80, 8, 1),
	MTK_PIN_DWV_GWP(97, DWV_BASE+0x80, 8, 1),
	MTK_PIN_DWV_GWP(98, DWV_BASE+0x80, 8, 1),
	MTK_PIN_DWV_GWP(99, DWV_BASE+0x80, 8, 1),
	MTK_PIN_DWV_GWP(100, 0xca0, 8, 2),
	MTK_PIN_DWV_GWP(101, 0xca0, 8, 2),
	MTK_PIN_DWV_GWP(102, 0xca0, 8, 2),
	MTK_PIN_DWV_GWP(103, 0xca0, 8, 2),
	MTK_PIN_DWV_GWP(104, 0xc80, 8, 2),
	MTK_PIN_DWV_GWP(105, 0xc90, 8, 2),
	MTK_PIN_DWV_GWP(108, DWV_BASE+0x50, 0, 1),
	MTK_PIN_DWV_GWP(109, DWV_BASE+0x50, 0, 1),
	MTK_PIN_DWV_GWP(110, DWV_BASE+0x50, 0, 1),
	MTK_PIN_DWV_GWP(111, DWV_BASE+0x50, 0, 1),
	MTK_PIN_DWV_GWP(112, DWV_BASE+0x50, 0, 1),
	MTK_PIN_DWV_GWP(113, DWV_BASE+0x80, 4, 1),
	MTK_PIN_DWV_GWP(114, DWV_BASE+0x80, 4, 1),
	MTK_PIN_DWV_GWP(115, DWV_BASE+0x80, 4, 1),
	MTK_PIN_DWV_GWP(116, DWV_BASE+0x80, 4, 1),
	MTK_PIN_DWV_GWP(117, DWV_BASE+0x90, 0, 1),
	MTK_PIN_DWV_GWP(118, DWV_BASE+0x90, 0, 1),
	MTK_PIN_DWV_GWP(119, DWV_BASE+0x50, 4, 1),
	MTK_PIN_DWV_GWP(120, DWV_BASE+0x50, 4, 1),
	MTK_PIN_DWV_GWP(121, DWV_BASE+0x50, 4, 1),
	MTK_PIN_DWV_GWP(122, DWV_BASE+0x50, 4, 1),
	MTK_PIN_DWV_GWP(123, DWV_BASE+0x50, 4, 1),
	MTK_PIN_DWV_GWP(124, DWV_BASE+0x50, 4, 1),
	MTK_PIN_DWV_GWP(125, DWV_BASE+0x30, 12, 1),
	MTK_PIN_DWV_GWP(126, DWV_BASE+0x30, 12, 1),
	MTK_PIN_DWV_GWP(127, DWV_BASE+0x50, 8, 1),
	MTK_PIN_DWV_GWP(128, DWV_BASE+0x40, 0, 1),
	MTK_PIN_DWV_GWP(129, DWV_BASE+0x40, 0, 1),
	MTK_PIN_DWV_GWP(130, DWV_BASE+0x40, 0, 1),
	MTK_PIN_DWV_GWP(131, DWV_BASE+0x40, 0, 1),
	MTK_PIN_DWV_GWP(132, DWV_BASE+0x40, 0, 1)
};

static const stwuct mtk_pinctww_devdata mt8173_pinctww_data = {
	.pins = mtk_pins_mt8173,
	.npins = AWWAY_SIZE(mtk_pins_mt8173),
	.gwp_desc = mt8173_dwv_gwp,
	.n_gwp_cws = AWWAY_SIZE(mt8173_dwv_gwp),
	.pin_dwv_gwp = mt8173_pin_dwv,
	.n_pin_dwv_gwps = AWWAY_SIZE(mt8173_pin_dwv),
	.spec_ies = mt8173_ies_set,
	.n_spec_ies = AWWAY_SIZE(mt8173_ies_set),
	.spec_pupd = mt8173_spec_pupd,
	.n_spec_pupd = AWWAY_SIZE(mt8173_spec_pupd),
	.spec_smt = mt8173_smt_set,
	.n_spec_smt = AWWAY_SIZE(mt8173_smt_set),
	.spec_puww_set = mtk_pctww_spec_puww_set_sameweg,
	.spec_ies_smt_set = mtk_pconf_spec_set_ies_smt_wange,
	.diw_offset = 0x0000,
	.puwwen_offset = 0x0100,
	.puwwsew_offset = 0x0200,
	.dout_offset = 0x0400,
	.din_offset = 0x0500,
	.pinmux_offset = 0x0600,
	.type1_stawt = 135,
	.type1_end = 135,
	.powt_shf = 4,
	.powt_mask = 0xf,
	.powt_awign = 4,
	.mode_mask = 0xf,
	.mode_pew_weg = 5,
	.mode_shf = 4,
	.eint_hw = {
		.powt_mask = 7,
		.powts     = 6,
		.ap_num    = 224,
		.db_cnt    = 16,
		.db_time   = debounce_time_mt2701,
	},
};

static int mt8173_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn mtk_pctww_init(pdev, &mt8173_pinctww_data, NUWW);
}

static const stwuct of_device_id mt8173_pctww_match[] = {
	{
		.compatibwe = "mediatek,mt8173-pinctww",
	},
	{ }
};

static stwuct pwatfowm_dwivew mtk_pinctww_dwivew = {
	.pwobe = mt8173_pinctww_pwobe,
	.dwivew = {
		.name = "mediatek-mt8173-pinctww",
		.of_match_tabwe = mt8173_pctww_match,
		.pm = pm_sweep_ptw(&mtk_eint_pm_ops),
	},
};

static int __init mtk_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mtk_pinctww_dwivew);
}
awch_initcaww(mtk_pinctww_init);
