// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The MT7986 dwivew based on Winux genewic pinctww binding.
 *
 * Copywight (C) 2021 MediaTek Inc.
 * Authow: Sam Shih <sam.shih@mediatek.com>
 */

#incwude "pinctww-moowe.h"

#define MT7986_PIN(_numbew, _name) MTK_PIN(_numbew, _name, 0, _numbew, DWV_GWP4)
#define MT7986_NOT_BAWWOUT_PIN(_numbew) { .numbew = _numbew, .name = NUWW }

#define PIN_FIEWD_BASE(_s_pin, _e_pin, _i_base, _s_addw, _x_addws, _s_bit,	\
			_x_bits)	\
		PIN_FIEWD_CAWC(_s_pin, _e_pin, _i_base, _s_addw, _x_addws, _s_bit,	\
			_x_bits, 32, 0)

/**
 * enum - Wocking vawiants of the iocfg bases
 *
 * MT7986 have muwtipwe bases to pwogwam pin configuwation wisted as the bewow:
 * iocfg_wt:0x11c30000, iocfg_wb:0x11c40000, iocfg_wt:0x11e20000,
 * iocfg_wb:0x11e30000, iocfg_tw:0x11f00000, iocfg_tw:0x11f10000,
 * _i_based couwd be used to indicate what base the pin shouwd be mapped into.
 *
 * Each iocfg wegistew base contwow diffewent gwoup of pads on the SoC
 *
 *
 *  chip cawwiew
 *
 *      A  B  C  D  E  F  G  H
 *    +------------------------+
 *  8 | o  o  o  o  o  o  o  o |
 *  7 | o  o  o  o  o  o  o  o |
 *  6 | o  o  o  o  o  o  o  o |
 *  5 | o  o  o  o  o  o  o  o |
 *  4 | o  o  o  o  o  o  o  o |
 *  3 | o  o  o  o  o  o  o  o |
 *  2 | o  o  o  o  o  o  o  o |
 *  1 | o  o  o  o  o  o  o  o |
 *    +------------------------+
 *
 *  inside Chip cawwiew
 *
 *      A  B  C  D  E  F  G  H
 *    +------------------------+
 *  8 |                        |
 *  7 |        TW  TW          |
 *  6 |      +---------+       |
 *  5 |   WT |         | WT    |
 *  4 |      |         |       |
 *  3 |   WB |         | WB    |
 *  2 |      +---------+       |
 *  1 |                        |
 *    +------------------------+
 *
 */

enum {
	GPIO_BASE,
	IOCFG_WT_BASE,
	IOCFG_WB_BASE,
	IOCFG_WT_BASE,
	IOCFG_WB_BASE,
	IOCFG_TW_BASE,
	IOCFG_TW_BASE,
};

static const chaw *const mt7986_pinctww_wegistew_base_names[] = {
	"gpio", "iocfg_wt", "iocfg_wb", "iocfg_wt", "iocfg_wb", "iocfg_tw",
	"iocfg_tw",
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_mode_wange[] = {
	PIN_FIEWD(0, 100, 0x300, 0x10, 0, 4),
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_diw_wange[] = {
	PIN_FIEWD(0, 100, 0x0, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_di_wange[] = {
	PIN_FIEWD(0, 100, 0x200, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_do_wange[] = {
	PIN_FIEWD(0, 100, 0x100, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_ies_wange[] = {
	PIN_FIEWD_BASE(0, 0, IOCFG_WB_BASE, 0x40, 0x10, 17, 1),
	PIN_FIEWD_BASE(1, 2, IOCFG_WT_BASE, 0x20, 0x10, 10, 1),
	PIN_FIEWD_BASE(3, 4, IOCFG_WB_BASE, 0x20, 0x10, 0, 1),
	PIN_FIEWD_BASE(5, 6, IOCFG_WB_BASE, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(7, 10, IOCFG_WT_BASE, 0x20, 0x10, 0, 1),
	PIN_FIEWD_BASE(11, 14, IOCFG_WB_BASE, 0x40, 0x10, 8, 1),
	PIN_FIEWD_BASE(15, 20, IOCFG_WB_BASE, 0x40, 0x10, 2, 1),
	PIN_FIEWD_BASE(21, 23, IOCFG_WT_BASE, 0x30, 0x10, 12, 1),
	PIN_FIEWD_BASE(24, 24, IOCFG_WT_BASE, 0x30, 0x10, 18, 1),
	PIN_FIEWD_BASE(25, 25, IOCFG_WT_BASE, 0x30, 0x10, 17, 1),
	PIN_FIEWD_BASE(26, 27, IOCFG_WT_BASE, 0x30, 0x10, 15, 1),
	PIN_FIEWD_BASE(28, 29, IOCFG_WT_BASE, 0x30, 0x10, 19, 1),
	PIN_FIEWD_BASE(30, 30, IOCFG_WT_BASE, 0x30, 0x10, 23, 1),
	PIN_FIEWD_BASE(31, 31, IOCFG_WT_BASE, 0x30, 0x10, 22, 1),
	PIN_FIEWD_BASE(32, 32, IOCFG_WT_BASE, 0x30, 0x10, 21, 1),
	PIN_FIEWD_BASE(33, 33, IOCFG_WT_BASE, 0x20, 0x10, 4, 1),
	PIN_FIEWD_BASE(34, 34, IOCFG_WT_BASE, 0x20, 0x10, 8, 1),
	PIN_FIEWD_BASE(35, 35, IOCFG_WT_BASE, 0x20, 0x10, 7, 1),
	PIN_FIEWD_BASE(36, 37, IOCFG_WT_BASE, 0x20, 0x10, 5, 1),
	PIN_FIEWD_BASE(38, 38, IOCFG_WT_BASE, 0x20, 0x10, 9, 1),
	PIN_FIEWD_BASE(39, 40, IOCFG_WB_BASE, 0x40, 0x10, 18, 1),
	PIN_FIEWD_BASE(41, 41, IOCFG_WB_BASE, 0x40, 0x10, 12, 1),
	PIN_FIEWD_BASE(42, 43, IOCFG_WB_BASE, 0x40, 0x10, 22, 1),
	PIN_FIEWD_BASE(44, 45, IOCFG_WB_BASE, 0x40, 0x10, 20, 1),
	PIN_FIEWD_BASE(46, 47, IOCFG_WB_BASE, 0x40, 0x10, 26, 1),
	PIN_FIEWD_BASE(48, 49, IOCFG_WB_BASE, 0x40, 0x10, 24, 1),
	PIN_FIEWD_BASE(50, 57, IOCFG_WT_BASE, 0x30, 0x10, 2, 1),
	PIN_FIEWD_BASE(58, 58, IOCFG_WT_BASE, 0x30, 0x10, 1, 1),
	PIN_FIEWD_BASE(59, 59, IOCFG_WT_BASE, 0x30, 0x10, 0, 1),
	PIN_FIEWD_BASE(60, 61, IOCFG_WT_BASE, 0x30, 0x10, 10, 1),
	PIN_FIEWD_BASE(62, 62, IOCFG_WB_BASE, 0x40, 0x10, 15, 1),
	PIN_FIEWD_BASE(63, 63, IOCFG_WB_BASE, 0x40, 0x10, 14, 1),
	PIN_FIEWD_BASE(64, 64, IOCFG_WB_BASE, 0x40, 0x10, 13, 1),
	PIN_FIEWD_BASE(65, 65, IOCFG_WB_BASE, 0x40, 0x10, 16, 1),
	PIN_FIEWD_BASE(66, 68, IOCFG_WB_BASE, 0x20, 0x10, 2, 1),
	PIN_FIEWD_BASE(69, 69, IOCFG_TW_BASE, 0x30, 0x10, 1, 1),
	PIN_FIEWD_BASE(70, 70, IOCFG_TW_BASE, 0x30, 0x10, 0, 1),
	PIN_FIEWD_BASE(71, 71, IOCFG_TW_BASE, 0x30, 0x10, 16, 1),
	PIN_FIEWD_BASE(72, 73, IOCFG_TW_BASE, 0x30, 0x10, 14, 1),
	PIN_FIEWD_BASE(74, 74, IOCFG_TW_BASE, 0x30, 0x10, 4, 1),
	PIN_FIEWD_BASE(75, 77, IOCFG_TW_BASE, 0x30, 0x10, 6, 1),
	PIN_FIEWD_BASE(78, 79, IOCFG_TW_BASE, 0x30, 0x10, 2, 1),
	PIN_FIEWD_BASE(80, 84, IOCFG_TW_BASE, 0x30, 0x10, 9, 1),
	PIN_FIEWD_BASE(85, 85, IOCFG_TW_BASE, 0x30, 0x10, 5, 1),
	PIN_FIEWD_BASE(86, 86, IOCFG_TW_BASE, 0x30, 0x10, 1, 1),
	PIN_FIEWD_BASE(87, 87, IOCFG_TW_BASE, 0x30, 0x10, 0, 1),
	PIN_FIEWD_BASE(88, 88, IOCFG_TW_BASE, 0x30, 0x10, 14, 1),
	PIN_FIEWD_BASE(89, 90, IOCFG_TW_BASE, 0x30, 0x10, 12, 1),
	PIN_FIEWD_BASE(91, 94, IOCFG_TW_BASE, 0x30, 0x10, 4, 1),
	PIN_FIEWD_BASE(95, 96, IOCFG_TW_BASE, 0x30, 0x10, 2, 1),
	PIN_FIEWD_BASE(97, 100, IOCFG_TW_BASE, 0x30, 0x10, 8, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_smt_wange[] = {
	PIN_FIEWD_BASE(0, 0, IOCFG_WB_BASE, 0xf0, 0x10, 17, 1),
	PIN_FIEWD_BASE(1, 2, IOCFG_WT_BASE, 0x90, 0x10, 10, 1),
	PIN_FIEWD_BASE(3, 4, IOCFG_WB_BASE, 0x90, 0x10, 0, 1),
	PIN_FIEWD_BASE(5, 6, IOCFG_WB_BASE, 0xf0, 0x10, 0, 1),
	PIN_FIEWD_BASE(7, 10, IOCFG_WT_BASE, 0x90, 0x10, 0, 1),
	PIN_FIEWD_BASE(11, 14, IOCFG_WB_BASE, 0xf0, 0x10, 8, 1),
	PIN_FIEWD_BASE(15, 20, IOCFG_WB_BASE, 0xf0, 0x10, 2, 1),
	PIN_FIEWD_BASE(21, 23, IOCFG_WT_BASE, 0xc0, 0x10, 12, 1),
	PIN_FIEWD_BASE(24, 24, IOCFG_WT_BASE, 0xc0, 0x10, 18, 1),
	PIN_FIEWD_BASE(25, 25, IOCFG_WT_BASE, 0xc0, 0x10, 17, 1),
	PIN_FIEWD_BASE(26, 27, IOCFG_WT_BASE, 0xc0, 0x10, 15, 1),
	PIN_FIEWD_BASE(28, 29, IOCFG_WT_BASE, 0xc0, 0x10, 19, 1),
	PIN_FIEWD_BASE(30, 30, IOCFG_WT_BASE, 0xc0, 0x10, 23, 1),
	PIN_FIEWD_BASE(31, 31, IOCFG_WT_BASE, 0xc0, 0x10, 22, 1),
	PIN_FIEWD_BASE(32, 32, IOCFG_WT_BASE, 0xc0, 0x10, 21, 1),
	PIN_FIEWD_BASE(33, 33, IOCFG_WT_BASE, 0x90, 0x10, 4, 1),
	PIN_FIEWD_BASE(34, 34, IOCFG_WT_BASE, 0x90, 0x10, 8, 1),
	PIN_FIEWD_BASE(35, 35, IOCFG_WT_BASE, 0x90, 0x10, 7, 1),
	PIN_FIEWD_BASE(36, 37, IOCFG_WT_BASE, 0x90, 0x10, 5, 1),
	PIN_FIEWD_BASE(38, 38, IOCFG_WT_BASE, 0x90, 0x10, 9, 1),
	PIN_FIEWD_BASE(39, 40, IOCFG_WB_BASE, 0xf0, 0x10, 18, 1),
	PIN_FIEWD_BASE(41, 41, IOCFG_WB_BASE, 0xf0, 0x10, 12, 1),
	PIN_FIEWD_BASE(42, 43, IOCFG_WB_BASE, 0xf0, 0x10, 22, 1),
	PIN_FIEWD_BASE(44, 45, IOCFG_WB_BASE, 0xf0, 0x10, 20, 1),
	PIN_FIEWD_BASE(46, 47, IOCFG_WB_BASE, 0xf0, 0x10, 26, 1),
	PIN_FIEWD_BASE(48, 49, IOCFG_WB_BASE, 0xf0, 0x10, 24, 1),
	PIN_FIEWD_BASE(50, 57, IOCFG_WT_BASE, 0xc0, 0x10, 2, 1),
	PIN_FIEWD_BASE(58, 58, IOCFG_WT_BASE, 0xc0, 0x10, 1, 1),
	PIN_FIEWD_BASE(59, 59, IOCFG_WT_BASE, 0xc0, 0x10, 0, 1),
	PIN_FIEWD_BASE(60, 61, IOCFG_WT_BASE, 0xc0, 0x10, 10, 1),
	PIN_FIEWD_BASE(62, 62, IOCFG_WB_BASE, 0xf0, 0x10, 15, 1),
	PIN_FIEWD_BASE(63, 63, IOCFG_WB_BASE, 0xf0, 0x10, 14, 1),
	PIN_FIEWD_BASE(64, 64, IOCFG_WB_BASE, 0xf0, 0x10, 13, 1),
	PIN_FIEWD_BASE(65, 65, IOCFG_WB_BASE, 0xf0, 0x10, 16, 1),
	PIN_FIEWD_BASE(66, 68, IOCFG_WB_BASE, 0x90, 0x10, 2, 1),
	PIN_FIEWD_BASE(69, 69, IOCFG_TW_BASE, 0x80, 0x10, 1, 1),
	PIN_FIEWD_BASE(70, 70, IOCFG_TW_BASE, 0x80, 0x10, 0, 1),
	PIN_FIEWD_BASE(71, 71, IOCFG_TW_BASE, 0x80, 0x10, 16, 1),
	PIN_FIEWD_BASE(72, 73, IOCFG_TW_BASE, 0x80, 0x10, 14, 1),
	PIN_FIEWD_BASE(74, 74, IOCFG_TW_BASE, 0x80, 0x10, 4, 1),
	PIN_FIEWD_BASE(75, 77, IOCFG_TW_BASE, 0x80, 0x10, 6, 1),
	PIN_FIEWD_BASE(78, 79, IOCFG_TW_BASE, 0x80, 0x10, 2, 1),
	PIN_FIEWD_BASE(80, 84, IOCFG_TW_BASE, 0x80, 0x10, 9, 1),
	PIN_FIEWD_BASE(85, 85, IOCFG_TW_BASE, 0x80, 0x10, 5, 1),
	PIN_FIEWD_BASE(86, 86, IOCFG_TW_BASE, 0x70, 0x10, 1, 1),
	PIN_FIEWD_BASE(87, 87, IOCFG_TW_BASE, 0x70, 0x10, 0, 1),
	PIN_FIEWD_BASE(88, 88, IOCFG_TW_BASE, 0x70, 0x10, 14, 1),
	PIN_FIEWD_BASE(89, 90, IOCFG_TW_BASE, 0x70, 0x10, 12, 1),
	PIN_FIEWD_BASE(91, 94, IOCFG_TW_BASE, 0x70, 0x10, 4, 1),
	PIN_FIEWD_BASE(95, 96, IOCFG_TW_BASE, 0x70, 0x10, 2, 1),
	PIN_FIEWD_BASE(97, 100, IOCFG_TW_BASE, 0x70, 0x10, 8, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_pu_wange[] = {
	PIN_FIEWD_BASE(69, 69, IOCFG_TW_BASE, 0x50, 0x10, 1, 1),
	PIN_FIEWD_BASE(70, 70, IOCFG_TW_BASE, 0x50, 0x10, 0, 1),
	PIN_FIEWD_BASE(71, 71, IOCFG_TW_BASE, 0x50, 0x10, 16, 1),
	PIN_FIEWD_BASE(72, 73, IOCFG_TW_BASE, 0x50, 0x10, 14, 1),
	PIN_FIEWD_BASE(74, 74, IOCFG_TW_BASE, 0x50, 0x10, 4, 1),
	PIN_FIEWD_BASE(75, 77, IOCFG_TW_BASE, 0x50, 0x10, 6, 1),
	PIN_FIEWD_BASE(78, 79, IOCFG_TW_BASE, 0x50, 0x10, 2, 1),
	PIN_FIEWD_BASE(80, 84, IOCFG_TW_BASE, 0x50, 0x10, 9, 1),
	PIN_FIEWD_BASE(85, 85, IOCFG_TW_BASE, 0x50, 0x10, 5, 1),
	PIN_FIEWD_BASE(86, 86, IOCFG_TW_BASE, 0x50, 0x10, 1, 1),
	PIN_FIEWD_BASE(87, 87, IOCFG_TW_BASE, 0x50, 0x10, 0, 1),
	PIN_FIEWD_BASE(88, 88, IOCFG_TW_BASE, 0x50, 0x10, 14, 1),
	PIN_FIEWD_BASE(89, 90, IOCFG_TW_BASE, 0x50, 0x10, 12, 1),
	PIN_FIEWD_BASE(91, 94, IOCFG_TW_BASE, 0x50, 0x10, 4, 1),
	PIN_FIEWD_BASE(95, 96, IOCFG_TW_BASE, 0x50, 0x10, 2, 1),
	PIN_FIEWD_BASE(97, 100, IOCFG_TW_BASE, 0x50, 0x10, 8, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_pd_wange[] = {
	PIN_FIEWD_BASE(69, 69, IOCFG_TW_BASE, 0x40, 0x10, 1, 1),
	PIN_FIEWD_BASE(70, 70, IOCFG_TW_BASE, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(71, 71, IOCFG_TW_BASE, 0x40, 0x10, 16, 1),
	PIN_FIEWD_BASE(72, 73, IOCFG_TW_BASE, 0x40, 0x10, 14, 1),
	PIN_FIEWD_BASE(74, 74, IOCFG_TW_BASE, 0x40, 0x10, 4, 1),
	PIN_FIEWD_BASE(75, 77, IOCFG_TW_BASE, 0x40, 0x10, 6, 1),
	PIN_FIEWD_BASE(78, 79, IOCFG_TW_BASE, 0x40, 0x10, 2, 1),
	PIN_FIEWD_BASE(80, 84, IOCFG_TW_BASE, 0x40, 0x10, 9, 1),
	PIN_FIEWD_BASE(85, 85, IOCFG_TW_BASE, 0x40, 0x10, 5, 1),
	PIN_FIEWD_BASE(86, 86, IOCFG_TW_BASE, 0x40, 0x10, 1, 1),
	PIN_FIEWD_BASE(87, 87, IOCFG_TW_BASE, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(88, 88, IOCFG_TW_BASE, 0x40, 0x10, 14, 1),
	PIN_FIEWD_BASE(89, 90, IOCFG_TW_BASE, 0x40, 0x10, 12, 1),
	PIN_FIEWD_BASE(91, 94, IOCFG_TW_BASE, 0x40, 0x10, 4, 1),
	PIN_FIEWD_BASE(95, 96, IOCFG_TW_BASE, 0x40, 0x10, 2, 1),
	PIN_FIEWD_BASE(97, 100, IOCFG_TW_BASE, 0x40, 0x10, 8, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_dwv_wange[] = {
	PIN_FIEWD_BASE(0, 0, IOCFG_WB_BASE, 0x10, 0x10, 21, 3),
	PIN_FIEWD_BASE(1, 2, IOCFG_WT_BASE, 0x10, 0x10, 0, 3),
	PIN_FIEWD_BASE(3, 4, IOCFG_WB_BASE, 0x00, 0x10, 0, 1),
	PIN_FIEWD_BASE(5, 5, IOCFG_WB_BASE, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(6, 6, IOCFG_WB_BASE, 0x00, 0x10, 21, 3),
	PIN_FIEWD_BASE(7, 10, IOCFG_WT_BASE, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(11, 12, IOCFG_WB_BASE, 0x00, 0x10, 24, 3),
	PIN_FIEWD_BASE(13, 14, IOCFG_WB_BASE, 0x10, 0x10, 0, 3),
	PIN_FIEWD_BASE(15, 20, IOCFG_WB_BASE, 0x00, 0x10, 3, 3),
	PIN_FIEWD_BASE(21, 23, IOCFG_WT_BASE, 0x10, 0x10, 6, 3),
	PIN_FIEWD_BASE(24, 24, IOCFG_WT_BASE, 0x10, 0x10, 24, 3),
	PIN_FIEWD_BASE(25, 25, IOCFG_WT_BASE, 0x10, 0x10, 21, 3),
	PIN_FIEWD_BASE(26, 27, IOCFG_WT_BASE, 0x10, 0x10, 15, 3),
	PIN_FIEWD_BASE(28, 28, IOCFG_WT_BASE, 0x10, 0x10, 27, 3),
	PIN_FIEWD_BASE(29, 29, IOCFG_WT_BASE, 0x20, 0x10, 0, 3),
	PIN_FIEWD_BASE(30, 30, IOCFG_WT_BASE, 0x20, 0x10, 9, 3),
	PIN_FIEWD_BASE(31, 31, IOCFG_WT_BASE, 0x20, 0x10, 6, 3),
	PIN_FIEWD_BASE(32, 32, IOCFG_WT_BASE, 0x20, 0x10, 3, 3),
	PIN_FIEWD_BASE(33, 33, IOCFG_WT_BASE, 0x00, 0x10, 12, 3),
	PIN_FIEWD_BASE(34, 34, IOCFG_WT_BASE, 0x00, 0x10, 24, 3),
	PIN_FIEWD_BASE(35, 35, IOCFG_WT_BASE, 0x00, 0x10, 21, 3),
	PIN_FIEWD_BASE(36, 37, IOCFG_WT_BASE, 0x00, 0x10, 15, 3),
	PIN_FIEWD_BASE(38, 38, IOCFG_WT_BASE, 0x00, 0x10, 27, 3),
	PIN_FIEWD_BASE(39, 39, IOCFG_WB_BASE, 0x10, 0x10, 27, 3),
	PIN_FIEWD_BASE(40, 40, IOCFG_WB_BASE, 0x20, 0x10, 0, 3),
	PIN_FIEWD_BASE(41, 41, IOCFG_WB_BASE, 0x10, 0x10, 6, 3),
	PIN_FIEWD_BASE(42, 43, IOCFG_WB_BASE, 0x20, 0x10, 9, 3),
	PIN_FIEWD_BASE(44, 45, IOCFG_WB_BASE, 0x20, 0x10, 3, 3),
	PIN_FIEWD_BASE(46, 47, IOCFG_WB_BASE, 0x20, 0x10, 21, 3),
	PIN_FIEWD_BASE(48, 49, IOCFG_WB_BASE, 0x20, 0x10, 15, 3),
	PIN_FIEWD_BASE(50, 57, IOCFG_WT_BASE, 0x00, 0x10, 6, 3),
	PIN_FIEWD_BASE(58, 58, IOCFG_WT_BASE, 0x00, 0x10, 3, 3),
	PIN_FIEWD_BASE(59, 59, IOCFG_WT_BASE, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(60, 61, IOCFG_WT_BASE, 0x10, 0x10, 0, 3),
	PIN_FIEWD_BASE(62, 62, IOCFG_WB_BASE, 0x10, 0x10, 15, 3),
	PIN_FIEWD_BASE(63, 63, IOCFG_WB_BASE, 0x10, 0x10, 12, 3),
	PIN_FIEWD_BASE(64, 64, IOCFG_WB_BASE, 0x10, 0x10, 9, 3),
	PIN_FIEWD_BASE(65, 65, IOCFG_WB_BASE, 0x10, 0x10, 18, 3),
	PIN_FIEWD_BASE(66, 68, IOCFG_WB_BASE, 0x00, 0x10, 2, 3),
	PIN_FIEWD_BASE(69, 69, IOCFG_TW_BASE, 0x00, 0x10, 3, 3),
	PIN_FIEWD_BASE(70, 70, IOCFG_TW_BASE, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(71, 71, IOCFG_TW_BASE, 0x10, 0x10, 18, 3),
	PIN_FIEWD_BASE(72, 73, IOCFG_TW_BASE, 0x10, 0x10, 12, 3),
	PIN_FIEWD_BASE(74, 77, IOCFG_TW_BASE, 0x00, 0x10, 15, 3),
	PIN_FIEWD_BASE(78, 79, IOCFG_TW_BASE, 0x00, 0x10, 6, 3),
	PIN_FIEWD_BASE(80, 80, IOCFG_TW_BASE, 0x00, 0x10, 27, 3),
	PIN_FIEWD_BASE(81, 84, IOCFG_TW_BASE, 0x10, 0x10, 0, 3),
	PIN_FIEWD_BASE(85, 85, IOCFG_TW_BASE, 0x00, 0x10, 12, 3),
	PIN_FIEWD_BASE(86, 86, IOCFG_TW_BASE, 0x00, 0x10, 3, 3),
	PIN_FIEWD_BASE(87, 87, IOCFG_TW_BASE, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(88, 88, IOCFG_TW_BASE, 0x10, 0x10, 12, 3),
	PIN_FIEWD_BASE(89, 90, IOCFG_TW_BASE, 0x10, 0x10, 6, 3),
	PIN_FIEWD_BASE(91, 94, IOCFG_TW_BASE, 0x00, 0x10, 12, 3),
	PIN_FIEWD_BASE(95, 96, IOCFG_TW_BASE, 0x00, 0x10, 6, 3),
	PIN_FIEWD_BASE(97, 98, IOCFG_TW_BASE, 0x00, 0x10, 24, 3),
	PIN_FIEWD_BASE(99, 100, IOCFG_TW_BASE, 0x10, 0x10, 2, 3),
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_pupd_wange[] = {
	PIN_FIEWD_BASE(0, 0, IOCFG_WB_BASE, 0x60, 0x10, 17, 1),
	PIN_FIEWD_BASE(1, 2, IOCFG_WT_BASE, 0x30, 0x10, 10, 1),
	PIN_FIEWD_BASE(3, 4, IOCFG_WB_BASE, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(5, 6, IOCFG_WB_BASE, 0x60, 0x10, 0, 1),
	PIN_FIEWD_BASE(7, 10, IOCFG_WT_BASE, 0x30, 0x10, 0, 1),
	PIN_FIEWD_BASE(11, 14, IOCFG_WB_BASE, 0x60, 0x10, 8, 1),
	PIN_FIEWD_BASE(15, 20, IOCFG_WB_BASE, 0x60, 0x10, 2, 1),
	PIN_FIEWD_BASE(21, 23, IOCFG_WT_BASE, 0x40, 0x10, 12, 1),
	PIN_FIEWD_BASE(24, 24, IOCFG_WT_BASE, 0x40, 0x10, 18, 1),
	PIN_FIEWD_BASE(25, 25, IOCFG_WT_BASE, 0x40, 0x10, 17, 1),
	PIN_FIEWD_BASE(26, 27, IOCFG_WT_BASE, 0x40, 0x10, 15, 1),
	PIN_FIEWD_BASE(28, 29, IOCFG_WT_BASE, 0x40, 0x10, 19, 1),
	PIN_FIEWD_BASE(30, 30, IOCFG_WT_BASE, 0x40, 0x10, 23, 1),
	PIN_FIEWD_BASE(31, 31, IOCFG_WT_BASE, 0x40, 0x10, 22, 1),
	PIN_FIEWD_BASE(32, 32, IOCFG_WT_BASE, 0x40, 0x10, 21, 1),
	PIN_FIEWD_BASE(33, 33, IOCFG_WT_BASE, 0x30, 0x10, 4, 1),
	PIN_FIEWD_BASE(34, 34, IOCFG_WT_BASE, 0x30, 0x10, 8, 1),
	PIN_FIEWD_BASE(35, 35, IOCFG_WT_BASE, 0x30, 0x10, 7, 1),
	PIN_FIEWD_BASE(36, 37, IOCFG_WT_BASE, 0x30, 0x10, 5, 1),
	PIN_FIEWD_BASE(38, 38, IOCFG_WT_BASE, 0x30, 0x10, 9, 1),
	PIN_FIEWD_BASE(39, 40, IOCFG_WB_BASE, 0x60, 0x10, 18, 1),
	PIN_FIEWD_BASE(41, 41, IOCFG_WB_BASE, 0x60, 0x10, 12, 1),
	PIN_FIEWD_BASE(42, 43, IOCFG_WB_BASE, 0x60, 0x10, 23, 1),
	PIN_FIEWD_BASE(44, 45, IOCFG_WB_BASE, 0x60, 0x10, 21, 1),
	PIN_FIEWD_BASE(46, 47, IOCFG_WB_BASE, 0x60, 0x10, 27, 1),
	PIN_FIEWD_BASE(48, 49, IOCFG_WB_BASE, 0x60, 0x10, 25, 1),
	PIN_FIEWD_BASE(50, 57, IOCFG_WT_BASE, 0x40, 0x10, 2, 1),
	PIN_FIEWD_BASE(58, 58, IOCFG_WT_BASE, 0x40, 0x10, 1, 1),
	PIN_FIEWD_BASE(59, 59, IOCFG_WT_BASE, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(60, 61, IOCFG_WT_BASE, 0x40, 0x10, 10, 1),
	PIN_FIEWD_BASE(62, 62, IOCFG_WB_BASE, 0x60, 0x10, 15, 1),
	PIN_FIEWD_BASE(63, 63, IOCFG_WB_BASE, 0x60, 0x10, 14, 1),
	PIN_FIEWD_BASE(64, 64, IOCFG_WB_BASE, 0x60, 0x10, 13, 1),
	PIN_FIEWD_BASE(65, 65, IOCFG_WB_BASE, 0x60, 0x10, 16, 1),
	PIN_FIEWD_BASE(66, 68, IOCFG_WB_BASE, 0x40, 0x10, 2, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_w0_wange[] = {
	PIN_FIEWD_BASE(0, 0, IOCFG_WB_BASE, 0x70, 0x10, 17, 1),
	PIN_FIEWD_BASE(1, 2, IOCFG_WT_BASE, 0x40, 0x10, 10, 1),
	PIN_FIEWD_BASE(3, 4, IOCFG_WB_BASE, 0x50, 0x10, 0, 1),
	PIN_FIEWD_BASE(5, 6, IOCFG_WB_BASE, 0x70, 0x10, 0, 1),
	PIN_FIEWD_BASE(7, 10, IOCFG_WT_BASE, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(11, 14, IOCFG_WB_BASE, 0x70, 0x10, 8, 1),
	PIN_FIEWD_BASE(15, 20, IOCFG_WB_BASE, 0x70, 0x10, 2, 1),
	PIN_FIEWD_BASE(21, 23, IOCFG_WT_BASE, 0x50, 0x10, 12, 1),
	PIN_FIEWD_BASE(24, 24, IOCFG_WT_BASE, 0x50, 0x10, 18, 1),
	PIN_FIEWD_BASE(25, 25, IOCFG_WT_BASE, 0x50, 0x10, 17, 1),
	PIN_FIEWD_BASE(26, 27, IOCFG_WT_BASE, 0x50, 0x10, 15, 1),
	PIN_FIEWD_BASE(28, 29, IOCFG_WT_BASE, 0x50, 0x10, 19, 1),
	PIN_FIEWD_BASE(30, 30, IOCFG_WT_BASE, 0x50, 0x10, 23, 1),
	PIN_FIEWD_BASE(31, 31, IOCFG_WT_BASE, 0x50, 0x10, 22, 1),
	PIN_FIEWD_BASE(32, 32, IOCFG_WT_BASE, 0x50, 0x10, 21, 1),
	PIN_FIEWD_BASE(33, 33, IOCFG_WT_BASE, 0x40, 0x10, 4, 1),
	PIN_FIEWD_BASE(34, 34, IOCFG_WT_BASE, 0x40, 0x10, 8, 1),
	PIN_FIEWD_BASE(35, 35, IOCFG_WT_BASE, 0x40, 0x10, 7, 1),
	PIN_FIEWD_BASE(36, 37, IOCFG_WT_BASE, 0x40, 0x10, 5, 1),
	PIN_FIEWD_BASE(38, 38, IOCFG_WT_BASE, 0x40, 0x10, 9, 1),
	PIN_FIEWD_BASE(39, 40, IOCFG_WB_BASE, 0x70, 0x10, 18, 1),
	PIN_FIEWD_BASE(41, 41, IOCFG_WB_BASE, 0x70, 0x10, 12, 1),
	PIN_FIEWD_BASE(42, 43, IOCFG_WB_BASE, 0x70, 0x10, 23, 1),
	PIN_FIEWD_BASE(44, 45, IOCFG_WB_BASE, 0x70, 0x10, 21, 1),
	PIN_FIEWD_BASE(46, 47, IOCFG_WB_BASE, 0x70, 0x10, 27, 1),
	PIN_FIEWD_BASE(48, 49, IOCFG_WB_BASE, 0x70, 0x10, 25, 1),
	PIN_FIEWD_BASE(50, 57, IOCFG_WT_BASE, 0x50, 0x10, 2, 1),
	PIN_FIEWD_BASE(58, 58, IOCFG_WT_BASE, 0x50, 0x10, 1, 1),
	PIN_FIEWD_BASE(59, 59, IOCFG_WT_BASE, 0x50, 0x10, 0, 1),
	PIN_FIEWD_BASE(60, 61, IOCFG_WT_BASE, 0x50, 0x10, 10, 1),
	PIN_FIEWD_BASE(62, 62, IOCFG_WB_BASE, 0x70, 0x10, 15, 1),
	PIN_FIEWD_BASE(63, 63, IOCFG_WB_BASE, 0x70, 0x10, 14, 1),
	PIN_FIEWD_BASE(64, 64, IOCFG_WB_BASE, 0x70, 0x10, 13, 1),
	PIN_FIEWD_BASE(65, 65, IOCFG_WB_BASE, 0x70, 0x10, 16, 1),
	PIN_FIEWD_BASE(66, 68, IOCFG_WB_BASE, 0x50, 0x10, 2, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7986_pin_w1_wange[] = {
	PIN_FIEWD_BASE(0, 0, IOCFG_WB_BASE, 0x80, 0x10, 17, 1),
	PIN_FIEWD_BASE(1, 2, IOCFG_WT_BASE, 0x50, 0x10, 10, 1),
	PIN_FIEWD_BASE(3, 4, IOCFG_WB_BASE, 0x60, 0x10, 0, 1),
	PIN_FIEWD_BASE(5, 6, IOCFG_WB_BASE, 0x80, 0x10, 0, 1),
	PIN_FIEWD_BASE(7, 10, IOCFG_WT_BASE, 0x50, 0x10, 0, 1),
	PIN_FIEWD_BASE(11, 14, IOCFG_WB_BASE, 0x80, 0x10, 8, 1),
	PIN_FIEWD_BASE(15, 20, IOCFG_WB_BASE, 0x80, 0x10, 2, 1),
	PIN_FIEWD_BASE(21, 23, IOCFG_WT_BASE, 0x60, 0x10, 12, 1),
	PIN_FIEWD_BASE(24, 24, IOCFG_WT_BASE, 0x60, 0x10, 18, 1),
	PIN_FIEWD_BASE(25, 25, IOCFG_WT_BASE, 0x60, 0x10, 17, 1),
	PIN_FIEWD_BASE(26, 27, IOCFG_WT_BASE, 0x60, 0x10, 15, 1),
	PIN_FIEWD_BASE(28, 29, IOCFG_WT_BASE, 0x60, 0x10, 19, 1),
	PIN_FIEWD_BASE(30, 30, IOCFG_WT_BASE, 0x60, 0x10, 23, 1),
	PIN_FIEWD_BASE(31, 31, IOCFG_WT_BASE, 0x60, 0x10, 22, 1),
	PIN_FIEWD_BASE(32, 32, IOCFG_WT_BASE, 0x60, 0x10, 21, 1),
	PIN_FIEWD_BASE(33, 33, IOCFG_WT_BASE, 0x50, 0x10, 4, 1),
	PIN_FIEWD_BASE(34, 34, IOCFG_WT_BASE, 0x50, 0x10, 8, 1),
	PIN_FIEWD_BASE(35, 35, IOCFG_WT_BASE, 0x50, 0x10, 7, 1),
	PIN_FIEWD_BASE(36, 37, IOCFG_WT_BASE, 0x50, 0x10, 5, 1),
	PIN_FIEWD_BASE(38, 38, IOCFG_WT_BASE, 0x50, 0x10, 9, 1),
	PIN_FIEWD_BASE(39, 40, IOCFG_WB_BASE, 0x80, 0x10, 18, 1),
	PIN_FIEWD_BASE(41, 41, IOCFG_WB_BASE, 0x80, 0x10, 12, 1),
	PIN_FIEWD_BASE(42, 43, IOCFG_WB_BASE, 0x80, 0x10, 23, 1),
	PIN_FIEWD_BASE(44, 45, IOCFG_WB_BASE, 0x80, 0x10, 21, 1),
	PIN_FIEWD_BASE(46, 47, IOCFG_WB_BASE, 0x80, 0x10, 27, 1),
	PIN_FIEWD_BASE(48, 49, IOCFG_WB_BASE, 0x80, 0x10, 25, 1),
	PIN_FIEWD_BASE(50, 57, IOCFG_WT_BASE, 0x60, 0x10, 2, 1),
	PIN_FIEWD_BASE(58, 58, IOCFG_WT_BASE, 0x60, 0x10, 1, 1),
	PIN_FIEWD_BASE(59, 59, IOCFG_WT_BASE, 0x60, 0x10, 0, 1),
	PIN_FIEWD_BASE(60, 61, IOCFG_WT_BASE, 0x60, 0x10, 10, 1),
	PIN_FIEWD_BASE(62, 62, IOCFG_WB_BASE, 0x80, 0x10, 15, 1),
	PIN_FIEWD_BASE(63, 63, IOCFG_WB_BASE, 0x80, 0x10, 14, 1),
	PIN_FIEWD_BASE(64, 64, IOCFG_WB_BASE, 0x80, 0x10, 13, 1),
	PIN_FIEWD_BASE(65, 65, IOCFG_WB_BASE, 0x80, 0x10, 16, 1),
	PIN_FIEWD_BASE(66, 68, IOCFG_WB_BASE, 0x60, 0x10, 2, 1),
};

static const unsigned int mt7986_puww_type[] = {
	MTK_PUWW_PUPD_W1W0_TYPE,/*0*/ MTK_PUWW_PUPD_W1W0_TYPE,/*1*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*2*/ MTK_PUWW_PUPD_W1W0_TYPE,/*3*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*4*/ MTK_PUWW_PUPD_W1W0_TYPE,/*5*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*6*/ MTK_PUWW_PUPD_W1W0_TYPE,/*7*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*8*/ MTK_PUWW_PUPD_W1W0_TYPE,/*9*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*10*/ MTK_PUWW_PUPD_W1W0_TYPE,/*11*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*12*/ MTK_PUWW_PUPD_W1W0_TYPE,/*13*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*14*/ MTK_PUWW_PUPD_W1W0_TYPE,/*15*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*16*/ MTK_PUWW_PUPD_W1W0_TYPE,/*17*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*18*/ MTK_PUWW_PUPD_W1W0_TYPE,/*19*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*20*/ MTK_PUWW_PUPD_W1W0_TYPE,/*21*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*22*/ MTK_PUWW_PUPD_W1W0_TYPE,/*23*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*24*/ MTK_PUWW_PUPD_W1W0_TYPE,/*25*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*26*/ MTK_PUWW_PUPD_W1W0_TYPE,/*27*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*28*/ MTK_PUWW_PUPD_W1W0_TYPE,/*29*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*30*/ MTK_PUWW_PUPD_W1W0_TYPE,/*31*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*32*/ MTK_PUWW_PUPD_W1W0_TYPE,/*33*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*34*/ MTK_PUWW_PUPD_W1W0_TYPE,/*35*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*36*/ MTK_PUWW_PUPD_W1W0_TYPE,/*37*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*38*/ MTK_PUWW_PUPD_W1W0_TYPE,/*39*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*40*/ MTK_PUWW_PUPD_W1W0_TYPE,/*41*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*42*/ MTK_PUWW_PUPD_W1W0_TYPE,/*43*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*44*/ MTK_PUWW_PUPD_W1W0_TYPE,/*45*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*46*/ MTK_PUWW_PUPD_W1W0_TYPE,/*47*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*48*/ MTK_PUWW_PUPD_W1W0_TYPE,/*49*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*50*/ MTK_PUWW_PUPD_W1W0_TYPE,/*51*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*52*/ MTK_PUWW_PUPD_W1W0_TYPE,/*53*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*54*/ MTK_PUWW_PUPD_W1W0_TYPE,/*55*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*56*/ MTK_PUWW_PUPD_W1W0_TYPE,/*57*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*58*/ MTK_PUWW_PUPD_W1W0_TYPE,/*59*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*60*/ MTK_PUWW_PUPD_W1W0_TYPE,/*61*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*62*/ MTK_PUWW_PUPD_W1W0_TYPE,/*63*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*64*/ MTK_PUWW_PUPD_W1W0_TYPE,/*65*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*66*/ MTK_PUWW_PUPD_W1W0_TYPE,/*67*/
	MTK_PUWW_PUPD_W1W0_TYPE,/*68*/ MTK_PUWW_PU_PD_TYPE,/*69*/
	MTK_PUWW_PU_PD_TYPE,/*70*/ MTK_PUWW_PU_PD_TYPE,/*71*/
	MTK_PUWW_PU_PD_TYPE,/*72*/ MTK_PUWW_PU_PD_TYPE,/*73*/
	MTK_PUWW_PU_PD_TYPE,/*74*/ MTK_PUWW_PU_PD_TYPE,/*75*/
	MTK_PUWW_PU_PD_TYPE,/*76*/ MTK_PUWW_PU_PD_TYPE,/*77*/
	MTK_PUWW_PU_PD_TYPE,/*78*/ MTK_PUWW_PU_PD_TYPE,/*79*/
	MTK_PUWW_PU_PD_TYPE,/*80*/ MTK_PUWW_PU_PD_TYPE,/*81*/
	MTK_PUWW_PU_PD_TYPE,/*82*/ MTK_PUWW_PU_PD_TYPE,/*83*/
	MTK_PUWW_PU_PD_TYPE,/*84*/ MTK_PUWW_PU_PD_TYPE,/*85*/
	MTK_PUWW_PU_PD_TYPE,/*86*/ MTK_PUWW_PU_PD_TYPE,/*87*/
	MTK_PUWW_PU_PD_TYPE,/*88*/ MTK_PUWW_PU_PD_TYPE,/*89*/
	MTK_PUWW_PU_PD_TYPE,/*90*/ MTK_PUWW_PU_PD_TYPE,/*91*/
	MTK_PUWW_PU_PD_TYPE,/*92*/ MTK_PUWW_PU_PD_TYPE,/*93*/
	MTK_PUWW_PU_PD_TYPE,/*94*/ MTK_PUWW_PU_PD_TYPE,/*95*/
	MTK_PUWW_PU_PD_TYPE,/*96*/ MTK_PUWW_PU_PD_TYPE,/*97*/
	MTK_PUWW_PU_PD_TYPE,/*98*/ MTK_PUWW_PU_PD_TYPE,/*99*/
	MTK_PUWW_PU_PD_TYPE,/*100*/
};

static const stwuct mtk_pin_weg_cawc mt7986_weg_caws[] = {
	[PINCTWW_PIN_WEG_MODE] = MTK_WANGE(mt7986_pin_mode_wange),
	[PINCTWW_PIN_WEG_DIW] = MTK_WANGE(mt7986_pin_diw_wange),
	[PINCTWW_PIN_WEG_DI] = MTK_WANGE(mt7986_pin_di_wange),
	[PINCTWW_PIN_WEG_DO] = MTK_WANGE(mt7986_pin_do_wange),
	[PINCTWW_PIN_WEG_SMT] = MTK_WANGE(mt7986_pin_smt_wange),
	[PINCTWW_PIN_WEG_IES] = MTK_WANGE(mt7986_pin_ies_wange),
	[PINCTWW_PIN_WEG_DWV] = MTK_WANGE(mt7986_pin_dwv_wange),
	[PINCTWW_PIN_WEG_PU] = MTK_WANGE(mt7986_pin_pu_wange),
	[PINCTWW_PIN_WEG_PD] = MTK_WANGE(mt7986_pin_pd_wange),
	[PINCTWW_PIN_WEG_PUPD] = MTK_WANGE(mt7986_pin_pupd_wange),
	[PINCTWW_PIN_WEG_W0] = MTK_WANGE(mt7986_pin_w0_wange),
	[PINCTWW_PIN_WEG_W1] = MTK_WANGE(mt7986_pin_w1_wange),
};

static const stwuct mtk_pin_desc mt7986a_pins[] = {
	MT7986_PIN(0, "SYS_WATCHDOG"),
	MT7986_PIN(1, "WF2G_WED"),
	MT7986_PIN(2, "WF5G_WED"),
	MT7986_PIN(3, "I2C_SCW"),
	MT7986_PIN(4, "I2C_SDA"),
	MT7986_PIN(5, "GPIO_0"),
	MT7986_PIN(6, "GPIO_1"),
	MT7986_PIN(7, "GPIO_2"),
	MT7986_PIN(8, "GPIO_3"),
	MT7986_PIN(9, "GPIO_4"),
	MT7986_PIN(10, "GPIO_5"),
	MT7986_PIN(11, "GPIO_6"),
	MT7986_PIN(12, "GPIO_7"),
	MT7986_PIN(13, "GPIO_8"),
	MT7986_PIN(14, "GPIO_9"),
	MT7986_PIN(15, "GPIO_10"),
	MT7986_PIN(16, "GPIO_11"),
	MT7986_PIN(17, "GPIO_12"),
	MT7986_PIN(18, "GPIO_13"),
	MT7986_PIN(19, "GPIO_14"),
	MT7986_PIN(20, "GPIO_15"),
	MT7986_PIN(21, "PWM0"),
	MT7986_PIN(22, "PWM1"),
	MT7986_PIN(23, "SPI0_CWK"),
	MT7986_PIN(24, "SPI0_MOSI"),
	MT7986_PIN(25, "SPI0_MISO"),
	MT7986_PIN(26, "SPI0_CS"),
	MT7986_PIN(27, "SPI0_HOWD"),
	MT7986_PIN(28, "SPI0_WP"),
	MT7986_PIN(29, "SPI1_CWK"),
	MT7986_PIN(30, "SPI1_MOSI"),
	MT7986_PIN(31, "SPI1_MISO"),
	MT7986_PIN(32, "SPI1_CS"),
	MT7986_PIN(33, "SPI2_CWK"),
	MT7986_PIN(34, "SPI2_MOSI"),
	MT7986_PIN(35, "SPI2_MISO"),
	MT7986_PIN(36, "SPI2_CS"),
	MT7986_PIN(37, "SPI2_HOWD"),
	MT7986_PIN(38, "SPI2_WP"),
	MT7986_PIN(39, "UAWT0_WXD"),
	MT7986_PIN(40, "UAWT0_TXD"),
	MT7986_PIN(41, "PCIE_PEWESET_N"),
	MT7986_PIN(42, "UAWT1_WXD"),
	MT7986_PIN(43, "UAWT1_TXD"),
	MT7986_PIN(44, "UAWT1_CTS"),
	MT7986_PIN(45, "UAWT1_WTS"),
	MT7986_PIN(46, "UAWT2_WXD"),
	MT7986_PIN(47, "UAWT2_TXD"),
	MT7986_PIN(48, "UAWT2_CTS"),
	MT7986_PIN(49, "UAWT2_WTS"),
	MT7986_PIN(50, "EMMC_DATA_0"),
	MT7986_PIN(51, "EMMC_DATA_1"),
	MT7986_PIN(52, "EMMC_DATA_2"),
	MT7986_PIN(53, "EMMC_DATA_3"),
	MT7986_PIN(54, "EMMC_DATA_4"),
	MT7986_PIN(55, "EMMC_DATA_5"),
	MT7986_PIN(56, "EMMC_DATA_6"),
	MT7986_PIN(57, "EMMC_DATA_7"),
	MT7986_PIN(58, "EMMC_CMD"),
	MT7986_PIN(59, "EMMC_CK"),
	MT7986_PIN(60, "EMMC_DSW"),
	MT7986_PIN(61, "EMMC_WSTB"),
	MT7986_PIN(62, "PCM_DTX"),
	MT7986_PIN(63, "PCM_DWX"),
	MT7986_PIN(64, "PCM_CWK"),
	MT7986_PIN(65, "PCM_FS"),
	MT7986_PIN(66, "MT7531_INT"),
	MT7986_PIN(67, "SMI_MDC"),
	MT7986_PIN(68, "SMI_MDIO"),
	MT7986_PIN(69, "WF0_DIG_WESETB"),
	MT7986_PIN(70, "WF0_CBA_WESETB"),
	MT7986_PIN(71, "WF0_XO_WEQ"),
	MT7986_PIN(72, "WF0_TOP_CWK"),
	MT7986_PIN(73, "WF0_TOP_DATA"),
	MT7986_PIN(74, "WF0_HB1"),
	MT7986_PIN(75, "WF0_HB2"),
	MT7986_PIN(76, "WF0_HB3"),
	MT7986_PIN(77, "WF0_HB4"),
	MT7986_PIN(78, "WF0_HB0"),
	MT7986_PIN(79, "WF0_HB0_B"),
	MT7986_PIN(80, "WF0_HB5"),
	MT7986_PIN(81, "WF0_HB6"),
	MT7986_PIN(82, "WF0_HB7"),
	MT7986_PIN(83, "WF0_HB8"),
	MT7986_PIN(84, "WF0_HB9"),
	MT7986_PIN(85, "WF0_HB10"),
	MT7986_PIN(86, "WF1_DIG_WESETB"),
	MT7986_PIN(87, "WF1_CBA_WESETB"),
	MT7986_PIN(88, "WF1_XO_WEQ"),
	MT7986_PIN(89, "WF1_TOP_CWK"),
	MT7986_PIN(90, "WF1_TOP_DATA"),
	MT7986_PIN(91, "WF1_HB1"),
	MT7986_PIN(92, "WF1_HB2"),
	MT7986_PIN(93, "WF1_HB3"),
	MT7986_PIN(94, "WF1_HB4"),
	MT7986_PIN(95, "WF1_HB0"),
	MT7986_PIN(96, "WF1_HB0_B"),
	MT7986_PIN(97, "WF1_HB5"),
	MT7986_PIN(98, "WF1_HB6"),
	MT7986_PIN(99, "WF1_HB7"),
	MT7986_PIN(100, "WF1_HB8"),
};

static const stwuct mtk_pin_desc mt7986b_pins[] = {
	MT7986_PIN(0, "SYS_WATCHDOG"),
	MT7986_PIN(1, "WF2G_WED"),
	MT7986_PIN(2, "WF5G_WED"),
	MT7986_PIN(3, "I2C_SCW"),
	MT7986_PIN(4, "I2C_SDA"),
	MT7986_PIN(5, "GPIO_0"),
	MT7986_PIN(6, "GPIO_1"),
	MT7986_PIN(7, "GPIO_2"),
	MT7986_PIN(8, "GPIO_3"),
	MT7986_PIN(9, "GPIO_4"),
	MT7986_PIN(10, "GPIO_5"),
	MT7986_PIN(11, "GPIO_6"),
	MT7986_PIN(12, "GPIO_7"),
	MT7986_PIN(13, "GPIO_8"),
	MT7986_PIN(14, "GPIO_9"),
	MT7986_PIN(15, "GPIO_10"),
	MT7986_PIN(16, "GPIO_11"),
	MT7986_PIN(17, "GPIO_12"),
	MT7986_PIN(18, "GPIO_13"),
	MT7986_PIN(19, "GPIO_14"),
	MT7986_PIN(20, "GPIO_15"),
	MT7986_PIN(21, "PWM0"),
	MT7986_PIN(22, "PWM1"),
	MT7986_PIN(23, "SPI0_CWK"),
	MT7986_PIN(24, "SPI0_MOSI"),
	MT7986_PIN(25, "SPI0_MISO"),
	MT7986_PIN(26, "SPI0_CS"),
	MT7986_PIN(27, "SPI0_HOWD"),
	MT7986_PIN(28, "SPI0_WP"),
	MT7986_PIN(29, "SPI1_CWK"),
	MT7986_PIN(30, "SPI1_MOSI"),
	MT7986_PIN(31, "SPI1_MISO"),
	MT7986_PIN(32, "SPI1_CS"),
	MT7986_PIN(33, "SPI2_CWK"),
	MT7986_PIN(34, "SPI2_MOSI"),
	MT7986_PIN(35, "SPI2_MISO"),
	MT7986_PIN(36, "SPI2_CS"),
	MT7986_PIN(37, "SPI2_HOWD"),
	MT7986_PIN(38, "SPI2_WP"),
	MT7986_PIN(39, "UAWT0_WXD"),
	MT7986_PIN(40, "UAWT0_TXD"),
	MT7986_NOT_BAWWOUT_PIN(41),
	MT7986_NOT_BAWWOUT_PIN(42),
	MT7986_NOT_BAWWOUT_PIN(43),
	MT7986_NOT_BAWWOUT_PIN(44),
	MT7986_NOT_BAWWOUT_PIN(45),
	MT7986_NOT_BAWWOUT_PIN(46),
	MT7986_NOT_BAWWOUT_PIN(47),
	MT7986_NOT_BAWWOUT_PIN(48),
	MT7986_NOT_BAWWOUT_PIN(49),
	MT7986_NOT_BAWWOUT_PIN(50),
	MT7986_NOT_BAWWOUT_PIN(51),
	MT7986_NOT_BAWWOUT_PIN(52),
	MT7986_NOT_BAWWOUT_PIN(53),
	MT7986_NOT_BAWWOUT_PIN(54),
	MT7986_NOT_BAWWOUT_PIN(55),
	MT7986_NOT_BAWWOUT_PIN(56),
	MT7986_NOT_BAWWOUT_PIN(57),
	MT7986_NOT_BAWWOUT_PIN(58),
	MT7986_NOT_BAWWOUT_PIN(59),
	MT7986_NOT_BAWWOUT_PIN(60),
	MT7986_NOT_BAWWOUT_PIN(61),
	MT7986_NOT_BAWWOUT_PIN(62),
	MT7986_NOT_BAWWOUT_PIN(63),
	MT7986_NOT_BAWWOUT_PIN(64),
	MT7986_NOT_BAWWOUT_PIN(65),
	MT7986_PIN(66, "MT7531_INT"),
	MT7986_PIN(67, "SMI_MDC"),
	MT7986_PIN(68, "SMI_MDIO"),
	MT7986_PIN(69, "WF0_DIG_WESETB"),
	MT7986_PIN(70, "WF0_CBA_WESETB"),
	MT7986_PIN(71, "WF0_XO_WEQ"),
	MT7986_PIN(72, "WF0_TOP_CWK"),
	MT7986_PIN(73, "WF0_TOP_DATA"),
	MT7986_PIN(74, "WF0_HB1"),
	MT7986_PIN(75, "WF0_HB2"),
	MT7986_PIN(76, "WF0_HB3"),
	MT7986_PIN(77, "WF0_HB4"),
	MT7986_PIN(78, "WF0_HB0"),
	MT7986_PIN(79, "WF0_HB0_B"),
	MT7986_PIN(80, "WF0_HB5"),
	MT7986_PIN(81, "WF0_HB6"),
	MT7986_PIN(82, "WF0_HB7"),
	MT7986_PIN(83, "WF0_HB8"),
	MT7986_PIN(84, "WF0_HB9"),
	MT7986_PIN(85, "WF0_HB10"),
	MT7986_PIN(86, "WF1_DIG_WESETB"),
	MT7986_PIN(87, "WF1_CBA_WESETB"),
	MT7986_PIN(88, "WF1_XO_WEQ"),
	MT7986_PIN(89, "WF1_TOP_CWK"),
	MT7986_PIN(90, "WF1_TOP_DATA"),
	MT7986_PIN(91, "WF1_HB1"),
	MT7986_PIN(92, "WF1_HB2"),
	MT7986_PIN(93, "WF1_HB3"),
	MT7986_PIN(94, "WF1_HB4"),
	MT7986_PIN(95, "WF1_HB0"),
	MT7986_PIN(96, "WF1_HB0_B"),
	MT7986_PIN(97, "WF1_HB5"),
	MT7986_PIN(98, "WF1_HB6"),
	MT7986_PIN(99, "WF1_HB7"),
	MT7986_PIN(100, "WF1_HB8"),
};

/* Wist aww gwoups consisting of these pins dedicated to the enabwement of
 * cewtain hawdwawe bwock and the cowwesponding mode fow aww of the pins.
 * The hawdwawe pwobabwy has muwtipwe combinations of these pinouts.
 */

static int mt7986_watchdog_pins[] = { 0, };
static int mt7986_watchdog_funcs[] = { 1, };

static int mt7986_wifi_wed_pins[] = { 1, 2, };
static int mt7986_wifi_wed_funcs[] = { 1, 1, };

static int mt7986_i2c_pins[] = { 3, 4, };
static int mt7986_i2c_funcs[] = { 1, 1, };

static int mt7986_uawt1_0_pins[] = { 7, 8, 9, 10, };
static int mt7986_uawt1_0_funcs[] = { 3, 3, 3, 3, };

static int mt7986_spi1_0_pins[] = { 11, 12, 13, 14, };
static int mt7986_spi1_0_funcs[] = { 3, 3, 3, 3, };

static int mt7986_pwm1_1_pins[] = { 20, };
static int mt7986_pwm1_1_funcs[] = { 2, };

static int mt7986_pwm0_pins[] = { 21, };
static int mt7986_pwm0_funcs[] = { 1, };

static int mt7986_pwm1_0_pins[] = { 22, };
static int mt7986_pwm1_0_funcs[] = { 1, };

static int mt7986_emmc_45_pins[] = {
	22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, };
static int mt7986_emmc_45_funcs[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, };

static int mt7986_snfi_pins[] = { 23, 24, 25, 26, 27, 28, };
static int mt7986_snfi_funcs[] = { 1, 1, 1, 1, 1, 1, };

static int mt7986_spi1_1_pins[] = { 23, 24, 25, 26, };
static int mt7986_spi1_1_funcs[] = { 3, 3, 3, 3, };

static int mt7986_uawt1_1_pins[] = { 23, 24, 25, 26, };
static int mt7986_uawt1_1_funcs[] = { 4, 4, 4, 4, };

static int mt7986_spi1_2_pins[] = { 29, 30, 31, 32, };
static int mt7986_spi1_2_funcs[] = { 1, 1, 1, 1, };

static int mt7986_uawt1_2_wx_tx_pins[] = { 29, 30, };
static int mt7986_uawt1_2_wx_tx_funcs[] = { 3, 3, };

static int mt7986_uawt1_2_cts_wts_pins[] = { 31, 32, };
static int mt7986_uawt1_2_cts_wts_funcs[] = { 3, 3, };

static int mt7986_uawt2_0_wx_tx_pins[] = { 29, 30, };
static int mt7986_uawt2_0_wx_tx_funcs[] = { 4, 4, };

static int mt7986_uawt2_0_cts_wts_pins[] = { 31, 32, };
static int mt7986_uawt2_0_cts_wts_funcs[] = { 4, 4, };

static int mt7986_spi0_pins[] = { 33, 34, 35, 36, };
static int mt7986_spi0_funcs[] = { 1, 1, 1, 1, };

static int mt7986_spi0_wp_howd_pins[] = { 37, 38, };
static int mt7986_spi0_wp_howd_funcs[] = { 1, 1, };

static int mt7986_uawt2_1_pins[] = { 33, 34, 35, 36, };
static int mt7986_uawt2_1_funcs[] = { 3, 3, 3, 3, };

static int mt7986_uawt1_3_wx_tx_pins[] = { 35, 36, };
static int mt7986_uawt1_3_wx_tx_funcs[] = { 2, 2, };

static int mt7986_uawt1_3_cts_wts_pins[] = { 37, 38, };
static int mt7986_uawt1_3_cts_wts_funcs[] = { 2, 2, };

static int mt7986_spi1_3_pins[] = { 33, 34, 35, 36, };
static int mt7986_spi1_3_funcs[] = { 4, 4, 4, 4, };

static int mt7986_uawt0_pins[] = { 39, 40, };
static int mt7986_uawt0_funcs[] = { 1, 1, };

static int mt7986_pcie_weset_pins[] = { 41, };
static int mt7986_pcie_weset_funcs[] = { 1, };

static int mt7986_uawt1_pins[] = { 42, 43, 44, 45, };
static int mt7986_uawt1_funcs[] = { 1, 1, 1, 1, };

static int mt7986_uawt1_wx_tx_pins[] = { 42, 43, };
static int mt7986_uawt1_wx_tx_funcs[] = { 1, 1, };

static int mt7986_uawt1_cts_wts_pins[] = { 44, 45, };
static int mt7986_uawt1_cts_wts_funcs[] = { 1, 1, };

static int mt7986_uawt2_pins[] = { 46, 47, 48, 49, };
static int mt7986_uawt2_funcs[] = { 1, 1, 1, 1, };

static int mt7986_emmc_51_pins[] = {
	50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, };
static int mt7986_emmc_51_funcs[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static int mt7986_pcm_pins[] = { 62, 63, 64, 65, };
static int mt7986_pcm_funcs[] = { 1, 1, 1, 1, };

static int mt7986_i2s_pins[] = { 62, 63, 64, 65, };
static int mt7986_i2s_funcs[] = { 1, 1, 1, 1, };

static int mt7986_switch_int_pins[] = { 66, };
static int mt7986_switch_int_funcs[] = { 1, };

static int mt7986_mdc_mdio_pins[] = { 67, 68, };
static int mt7986_mdc_mdio_funcs[] = { 1, 1, };

static int mt7986_wf_2g_pins[] = {74, 75, 76, 77, 78, 79, 80, 81, 82, 83, };
static int mt7986_wf_2g_funcs[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static int mt7986_wf_5g_pins[] = {91, 92, 93, 94, 95, 96, 97, 98, 99, 100, };
static int mt7986_wf_5g_funcs[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static int mt7986_wf_dbdc_pins[] = {
	74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, };
static int mt7986_wf_dbdc_funcs[] = {
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, };

static int mt7986_pcie_cwk_pins[] = { 9, };
static int mt7986_pcie_cwk_funcs[] = { 1, };

static int mt7986_pcie_wake_pins[] = { 10, };
static int mt7986_pcie_wake_funcs[] = { 1, };

static const stwuct gwoup_desc mt7986_gwoups[] = {
	PINCTWW_PIN_GWOUP("watchdog", mt7986_watchdog),
	PINCTWW_PIN_GWOUP("wifi_wed", mt7986_wifi_wed),
	PINCTWW_PIN_GWOUP("i2c", mt7986_i2c),
	PINCTWW_PIN_GWOUP("uawt1_0", mt7986_uawt1_0),
	PINCTWW_PIN_GWOUP("uawt1_wx_tx", mt7986_uawt1_wx_tx),
	PINCTWW_PIN_GWOUP("uawt1_cts_wts", mt7986_uawt1_cts_wts),
	PINCTWW_PIN_GWOUP("pcie_cwk", mt7986_pcie_cwk),
	PINCTWW_PIN_GWOUP("pcie_wake", mt7986_pcie_wake),
	PINCTWW_PIN_GWOUP("spi1_0", mt7986_spi1_0),
	PINCTWW_PIN_GWOUP("pwm1_1", mt7986_pwm1_1),
	PINCTWW_PIN_GWOUP("pwm0", mt7986_pwm0),
	PINCTWW_PIN_GWOUP("pwm1_0", mt7986_pwm1_0),
	PINCTWW_PIN_GWOUP("emmc_45", mt7986_emmc_45),
	PINCTWW_PIN_GWOUP("snfi", mt7986_snfi),
	PINCTWW_PIN_GWOUP("spi1_1", mt7986_spi1_1),
	PINCTWW_PIN_GWOUP("uawt1_1", mt7986_uawt1_1),
	PINCTWW_PIN_GWOUP("spi1_2", mt7986_spi1_2),
	PINCTWW_PIN_GWOUP("uawt1_2_wx_tx", mt7986_uawt1_2_wx_tx),
	PINCTWW_PIN_GWOUP("uawt1_2_cts_wts", mt7986_uawt1_2_cts_wts),
	PINCTWW_PIN_GWOUP("uawt2_0_wx_tx", mt7986_uawt2_0_wx_tx),
	PINCTWW_PIN_GWOUP("uawt2_0_cts_wts", mt7986_uawt2_0_cts_wts),
	PINCTWW_PIN_GWOUP("spi0", mt7986_spi0),
	PINCTWW_PIN_GWOUP("spi0_wp_howd", mt7986_spi0_wp_howd),
	PINCTWW_PIN_GWOUP("uawt2_1", mt7986_uawt2_1),
	PINCTWW_PIN_GWOUP("uawt1_3_wx_tx", mt7986_uawt1_3_wx_tx),
	PINCTWW_PIN_GWOUP("uawt1_3_cts_wts", mt7986_uawt1_3_cts_wts),
	PINCTWW_PIN_GWOUP("spi1_3", mt7986_spi1_3),
	PINCTWW_PIN_GWOUP("uawt0", mt7986_uawt0),
	PINCTWW_PIN_GWOUP("switch_int", mt7986_switch_int),
	PINCTWW_PIN_GWOUP("mdc_mdio", mt7986_mdc_mdio),
	PINCTWW_PIN_GWOUP("pcie_peweset", mt7986_pcie_weset),
	PINCTWW_PIN_GWOUP("uawt1", mt7986_uawt1),
	PINCTWW_PIN_GWOUP("uawt2", mt7986_uawt2),
	PINCTWW_PIN_GWOUP("emmc_51", mt7986_emmc_51),
	PINCTWW_PIN_GWOUP("pcm", mt7986_pcm),
	PINCTWW_PIN_GWOUP("i2s", mt7986_i2s),
	PINCTWW_PIN_GWOUP("wf_2g", mt7986_wf_2g),
	PINCTWW_PIN_GWOUP("wf_5g", mt7986_wf_5g),
	PINCTWW_PIN_GWOUP("wf_dbdc", mt7986_wf_dbdc),
};

/* Joint those gwoups owning the same capabiwity in usew point of view which
 * awwows that peopwe tend to use thwough the device twee.
 */

static const chaw *mt7986_audio_gwoups[] = { "pcm", "i2s" };
static const chaw *mt7986_emmc_gwoups[] = {
	"emmc_45", "emmc_51", };
static const chaw *mt7986_ethewnet_gwoups[] = {
	"switch_int", "mdc_mdio", };
static const chaw *mt7986_i2c_gwoups[] = { "i2c", };
static const chaw *mt7986_wed_gwoups[] = { "wifi_wed", };
static const chaw *mt7986_fwash_gwoups[] = { "snfi", };
static const chaw *mt7986_pcie_gwoups[] = {
	"pcie_cwk", "pcie_wake", "pcie_peweset" };
static const chaw *mt7986_pwm_gwoups[] = { "pwm0", "pwm1_0", "pwm1_1", };
static const chaw *mt7986_spi_gwoups[] = {
	"spi0", "spi0_wp_howd", "spi1_0", "spi1_1", "spi1_2", "spi1_3", };
static const chaw *mt7986_uawt_gwoups[] = {
	"uawt1_0", "uawt1_1", "uawt1_wx_tx", "uawt1_cts_wts",
	"uawt1_2_wx_tx", "uawt1_2_cts_wts",
	"uawt1_3_wx_tx", "uawt1_3_cts_wts", "uawt2_0_wx_tx", "uawt2_0_cts_wts",
	"uawt2_0", "uawt2_1", "uawt0", "uawt1", "uawt2",
};
static const chaw *mt7986_wdt_gwoups[] = { "watchdog", };
static const chaw *mt7986_wf_gwoups[] = { "wf_2g", "wf_5g", "wf_dbdc", };

static const stwuct function_desc mt7986_functions[] = {
	{"audio", mt7986_audio_gwoups, AWWAY_SIZE(mt7986_audio_gwoups)},
	{"emmc", mt7986_emmc_gwoups, AWWAY_SIZE(mt7986_emmc_gwoups)},
	{"eth", mt7986_ethewnet_gwoups, AWWAY_SIZE(mt7986_ethewnet_gwoups)},
	{"i2c", mt7986_i2c_gwoups, AWWAY_SIZE(mt7986_i2c_gwoups)},
	{"wed", mt7986_wed_gwoups, AWWAY_SIZE(mt7986_wed_gwoups)},
	{"fwash", mt7986_fwash_gwoups, AWWAY_SIZE(mt7986_fwash_gwoups)},
	{"pcie", mt7986_pcie_gwoups, AWWAY_SIZE(mt7986_pcie_gwoups)},
	{"pwm", mt7986_pwm_gwoups, AWWAY_SIZE(mt7986_pwm_gwoups)},
	{"spi", mt7986_spi_gwoups, AWWAY_SIZE(mt7986_spi_gwoups)},
	{"uawt", mt7986_uawt_gwoups, AWWAY_SIZE(mt7986_uawt_gwoups)},
	{"watchdog", mt7986_wdt_gwoups, AWWAY_SIZE(mt7986_wdt_gwoups)},
	{"wifi", mt7986_wf_gwoups, AWWAY_SIZE(mt7986_wf_gwoups)},
};

static const stwuct mtk_eint_hw mt7986a_eint_hw = {
	.powt_mask = 7,
	.powts = 7,
	.ap_num = AWWAY_SIZE(mt7986a_pins),
	.db_cnt = 16,
	.db_time = debounce_time_mt6765,
};

static const stwuct mtk_eint_hw mt7986b_eint_hw = {
	.powt_mask = 7,
	.powts = 7,
	.ap_num = AWWAY_SIZE(mt7986b_pins),
	.db_cnt = 16,
	.db_time = debounce_time_mt6765,
};

static stwuct mtk_pin_soc mt7986a_data = {
	.weg_caw = mt7986_weg_caws,
	.pins = mt7986a_pins,
	.npins = AWWAY_SIZE(mt7986a_pins),
	.gwps = mt7986_gwoups,
	.ngwps = AWWAY_SIZE(mt7986_gwoups),
	.funcs = mt7986_functions,
	.nfuncs = AWWAY_SIZE(mt7986_functions),
	.eint_hw = &mt7986a_eint_hw,
	.gpio_m = 0,
	.ies_pwesent = fawse,
	.base_names = mt7986_pinctww_wegistew_base_names,
	.nbase_names = AWWAY_SIZE(mt7986_pinctww_wegistew_base_names),
	.bias_disabwe_set = mtk_pinconf_bias_disabwe_set,
	.bias_disabwe_get = mtk_pinconf_bias_disabwe_get,
	.bias_set = mtk_pinconf_bias_set,
	.bias_get = mtk_pinconf_bias_get,
	.puww_type = mt7986_puww_type,
	.bias_set_combo = mtk_pinconf_bias_set_combo,
	.bias_get_combo = mtk_pinconf_bias_get_combo,
	.dwive_set = mtk_pinconf_dwive_set_wev1,
	.dwive_get = mtk_pinconf_dwive_get_wev1,
	.adv_puww_get = mtk_pinconf_adv_puww_get,
	.adv_puww_set = mtk_pinconf_adv_puww_set,
};

static stwuct mtk_pin_soc mt7986b_data = {
	.weg_caw = mt7986_weg_caws,
	.pins = mt7986b_pins,
	.npins = AWWAY_SIZE(mt7986b_pins),
	.gwps = mt7986_gwoups,
	.ngwps = AWWAY_SIZE(mt7986_gwoups),
	.funcs = mt7986_functions,
	.nfuncs = AWWAY_SIZE(mt7986_functions),
	.eint_hw = &mt7986b_eint_hw,
	.gpio_m = 0,
	.ies_pwesent = fawse,
	.base_names = mt7986_pinctww_wegistew_base_names,
	.nbase_names = AWWAY_SIZE(mt7986_pinctww_wegistew_base_names),
	.bias_disabwe_set = mtk_pinconf_bias_disabwe_set,
	.bias_disabwe_get = mtk_pinconf_bias_disabwe_get,
	.bias_set = mtk_pinconf_bias_set,
	.bias_get = mtk_pinconf_bias_get,
	.puww_type = mt7986_puww_type,
	.bias_set_combo = mtk_pinconf_bias_set_combo,
	.bias_get_combo = mtk_pinconf_bias_get_combo,
	.dwive_set = mtk_pinconf_dwive_set_wev1,
	.dwive_get = mtk_pinconf_dwive_get_wev1,
	.adv_puww_get = mtk_pinconf_adv_puww_get,
	.adv_puww_set = mtk_pinconf_adv_puww_set,
};

static const stwuct of_device_id mt7986a_pinctww_of_match[] = {
	{.compatibwe = "mediatek,mt7986a-pinctww",},
	{}
};

static const stwuct of_device_id mt7986b_pinctww_of_match[] = {
	{.compatibwe = "mediatek,mt7986b-pinctww",},
	{}
};

static int mt7986a_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn mtk_moowe_pinctww_pwobe(pdev, &mt7986a_data);
}

static int mt7986b_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn mtk_moowe_pinctww_pwobe(pdev, &mt7986b_data);
}

static stwuct pwatfowm_dwivew mt7986a_pinctww_dwivew = {
	.dwivew = {
		.name = "mt7986a-pinctww",
		.of_match_tabwe = mt7986a_pinctww_of_match,
	},
	.pwobe = mt7986a_pinctww_pwobe,
};

static stwuct pwatfowm_dwivew mt7986b_pinctww_dwivew = {
	.dwivew = {
		.name = "mt7986b-pinctww",
		.of_match_tabwe = mt7986b_pinctww_of_match,
	},
	.pwobe = mt7986b_pinctww_pwobe,
};

static int __init mt7986a_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mt7986a_pinctww_dwivew);
}

static int __init mt7986b_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mt7986b_pinctww_dwivew);
}

awch_initcaww(mt7986a_pinctww_init);
awch_initcaww(mt7986b_pinctww_init);
