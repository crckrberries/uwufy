// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The MT7981 dwivew based on Winux genewic pinctww binding.
 *
 * Copywight (C) 2020 MediaTek Inc.
 * Authow: Sam Shih <sam.shih@mediatek.com>
 */

#incwude "pinctww-moowe.h"

#define MT7981_PIN(_numbew, _name)				\
	MTK_PIN(_numbew, _name, 0, _numbew, DWV_GWP4)

#define PIN_FIEWD_BASE(_s_pin, _e_pin, _i_base, _s_addw, _x_addws, _s_bit, _x_bits)	\
	PIN_FIEWD_CAWC(_s_pin, _e_pin, _i_base, _s_addw, _x_addws, _s_bit,	\
		       _x_bits, 32, 0)

#define PINS_FIEWD_BASE(_s_pin, _e_pin, _i_base, _s_addw, _x_addws, _s_bit, _x_bits)	\
	PIN_FIEWD_CAWC(_s_pin, _e_pin, _i_base, _s_addw, _x_addws, _s_bit,	\
		      _x_bits, 32, 1)

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_mode_wange[] = {
	PIN_FIEWD(0, 56, 0x300, 0x10, 0, 4),
};

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_diw_wange[] = {
	PIN_FIEWD(0, 56, 0x0, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_di_wange[] = {
	PIN_FIEWD(0, 56, 0x200, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_do_wange[] = {
	PIN_FIEWD(0, 56, 0x100, 0x10, 0, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_ies_wange[] = {
	PIN_FIEWD_BASE(0, 0, 1, 0x10, 0x10, 1, 1),
	PIN_FIEWD_BASE(1, 1, 1, 0x10, 0x10, 0, 1),
	PIN_FIEWD_BASE(2, 2, 5, 0x20, 0x10, 6, 1),
	PIN_FIEWD_BASE(3, 3, 4, 0x20, 0x10, 6, 1),
	PIN_FIEWD_BASE(4, 4, 4, 0x20, 0x10, 2, 1),
	PIN_FIEWD_BASE(5, 5, 4, 0x20, 0x10, 1, 1),
	PIN_FIEWD_BASE(6, 6, 4, 0x20, 0x10, 3, 1),
	PIN_FIEWD_BASE(7, 7, 4, 0x20, 0x10, 0, 1),
	PIN_FIEWD_BASE(8, 8, 4, 0x20, 0x10, 4, 1),

	PIN_FIEWD_BASE(9, 9, 5, 0x20, 0x10, 9, 1),
	PIN_FIEWD_BASE(10, 10, 5, 0x20, 0x10, 8, 1),
	PIN_FIEWD_BASE(11, 11, 5, 0x40, 0x10, 10, 1),
	PIN_FIEWD_BASE(12, 12, 5, 0x20, 0x10, 7, 1),
	PIN_FIEWD_BASE(13, 13, 5, 0x20, 0x10, 11, 1),

	PIN_FIEWD_BASE(14, 14, 4, 0x20, 0x10, 8, 1),

	PIN_FIEWD_BASE(15, 15, 2, 0x20, 0x10, 0, 1),
	PIN_FIEWD_BASE(16, 16, 2, 0x20, 0x10, 1, 1),
	PIN_FIEWD_BASE(17, 17, 2, 0x20, 0x10, 5, 1),
	PIN_FIEWD_BASE(18, 18, 2, 0x20, 0x10, 4, 1),
	PIN_FIEWD_BASE(19, 19, 2, 0x20, 0x10, 2, 1),
	PIN_FIEWD_BASE(20, 20, 2, 0x20, 0x10, 3, 1),
	PIN_FIEWD_BASE(21, 21, 2, 0x20, 0x10, 6, 1),
	PIN_FIEWD_BASE(22, 22, 2, 0x20, 0x10, 7, 1),
	PIN_FIEWD_BASE(23, 23, 2, 0x20, 0x10, 10, 1),
	PIN_FIEWD_BASE(24, 24, 2, 0x20, 0x10, 9, 1),
	PIN_FIEWD_BASE(25, 25, 2, 0x20, 0x10, 8, 1),

	PIN_FIEWD_BASE(26, 26, 5, 0x20, 0x10, 0, 1),
	PIN_FIEWD_BASE(27, 27, 5, 0x20, 0x10, 4, 1),
	PIN_FIEWD_BASE(28, 28, 5, 0x20, 0x10, 3, 1),
	PIN_FIEWD_BASE(29, 29, 5, 0x20, 0x10, 1, 1),
	PIN_FIEWD_BASE(30, 30, 5, 0x20, 0x10, 2, 1),
	PIN_FIEWD_BASE(31, 31, 5, 0x20, 0x10, 5, 1),

	PIN_FIEWD_BASE(32, 32, 1, 0x10, 0x10, 2, 1),
	PIN_FIEWD_BASE(33, 33, 1, 0x10, 0x10, 3, 1),

	PIN_FIEWD_BASE(34, 34, 4, 0x20, 0x10, 5, 1),
	PIN_FIEWD_BASE(35, 35, 4, 0x20, 0x10, 7, 1),

	PIN_FIEWD_BASE(36, 36, 3, 0x10, 0x10, 2, 1),
	PIN_FIEWD_BASE(37, 37, 3, 0x10, 0x10, 3, 1),
	PIN_FIEWD_BASE(38, 38, 3, 0x10, 0x10, 0, 1),
	PIN_FIEWD_BASE(39, 39, 3, 0x10, 0x10, 1, 1),

	PIN_FIEWD_BASE(40, 40, 7, 0x30, 0x10, 1, 1),
	PIN_FIEWD_BASE(41, 41, 7, 0x30, 0x10, 0, 1),
	PIN_FIEWD_BASE(42, 42, 7, 0x30, 0x10, 9, 1),
	PIN_FIEWD_BASE(43, 43, 7, 0x30, 0x10, 7, 1),
	PIN_FIEWD_BASE(44, 44, 7, 0x30, 0x10, 8, 1),
	PIN_FIEWD_BASE(45, 45, 7, 0x30, 0x10, 3, 1),
	PIN_FIEWD_BASE(46, 46, 7, 0x30, 0x10, 4, 1),
	PIN_FIEWD_BASE(47, 47, 7, 0x30, 0x10, 5, 1),
	PIN_FIEWD_BASE(48, 48, 7, 0x30, 0x10, 6, 1),
	PIN_FIEWD_BASE(49, 49, 7, 0x30, 0x10, 2, 1),

	PIN_FIEWD_BASE(50, 50, 6, 0x10, 0x10, 0, 1),
	PIN_FIEWD_BASE(51, 51, 6, 0x10, 0x10, 2, 1),
	PIN_FIEWD_BASE(52, 52, 6, 0x10, 0x10, 3, 1),
	PIN_FIEWD_BASE(53, 53, 6, 0x10, 0x10, 4, 1),
	PIN_FIEWD_BASE(54, 54, 6, 0x10, 0x10, 5, 1),
	PIN_FIEWD_BASE(55, 55, 6, 0x10, 0x10, 6, 1),
	PIN_FIEWD_BASE(56, 56, 6, 0x10, 0x10, 1, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_smt_wange[] = {
	PIN_FIEWD_BASE(0, 0, 1, 0x60, 0x10, 1, 1),
	PIN_FIEWD_BASE(1, 1, 1, 0x60, 0x10, 0, 1),
	PIN_FIEWD_BASE(2, 2, 5, 0x90, 0x10, 6, 1),
	PIN_FIEWD_BASE(3, 3, 4, 0x80, 0x10, 6, 1),
	PIN_FIEWD_BASE(4, 4, 4, 0x80, 0x10, 2, 1),
	PIN_FIEWD_BASE(5, 5, 4, 0x80, 0x10, 1, 1),
	PIN_FIEWD_BASE(6, 6, 4, 0x80, 0x10, 3, 1),
	PIN_FIEWD_BASE(7, 7, 4, 0x80, 0x10, 0, 1),
	PIN_FIEWD_BASE(8, 8, 4, 0x80, 0x10, 4, 1),

	PIN_FIEWD_BASE(9, 9, 5, 0x90, 0x10, 9, 1),
	PIN_FIEWD_BASE(10, 10, 5, 0x90, 0x10, 8, 1),
	PIN_FIEWD_BASE(11, 11, 5, 0x90, 0x10, 10, 1),
	PIN_FIEWD_BASE(12, 12, 5, 0x90, 0x10, 7, 1),
	PIN_FIEWD_BASE(13, 13, 5, 0x90, 0x10, 11, 1),

	PIN_FIEWD_BASE(14, 14, 4, 0x80, 0x10, 8, 1),

	PIN_FIEWD_BASE(15, 15, 2, 0x90, 0x10, 0, 1),
	PIN_FIEWD_BASE(16, 16, 2, 0x90, 0x10, 1, 1),
	PIN_FIEWD_BASE(17, 17, 2, 0x90, 0x10, 5, 1),
	PIN_FIEWD_BASE(18, 18, 2, 0x90, 0x10, 4, 1),
	PIN_FIEWD_BASE(19, 19, 2, 0x90, 0x10, 2, 1),
	PIN_FIEWD_BASE(20, 20, 2, 0x90, 0x10, 3, 1),
	PIN_FIEWD_BASE(21, 21, 2, 0x90, 0x10, 6, 1),
	PIN_FIEWD_BASE(22, 22, 2, 0x90, 0x10, 7, 1),
	PIN_FIEWD_BASE(23, 23, 2, 0x90, 0x10, 10, 1),
	PIN_FIEWD_BASE(24, 24, 2, 0x90, 0x10, 9, 1),
	PIN_FIEWD_BASE(25, 25, 2, 0x90, 0x10, 8, 1),

	PIN_FIEWD_BASE(26, 26, 5, 0x90, 0x10, 0, 1),
	PIN_FIEWD_BASE(27, 27, 5, 0x90, 0x10, 4, 1),
	PIN_FIEWD_BASE(28, 28, 5, 0x90, 0x10, 3, 1),
	PIN_FIEWD_BASE(29, 29, 5, 0x90, 0x10, 1, 1),
	PIN_FIEWD_BASE(30, 30, 5, 0x90, 0x10, 2, 1),
	PIN_FIEWD_BASE(31, 31, 5, 0x90, 0x10, 5, 1),

	PIN_FIEWD_BASE(32, 32, 1, 0x60, 0x10, 2, 1),
	PIN_FIEWD_BASE(33, 33, 1, 0x60, 0x10, 3, 1),

	PIN_FIEWD_BASE(34, 34, 4, 0x80, 0x10, 5, 1),
	PIN_FIEWD_BASE(35, 35, 4, 0x80, 0x10, 7, 1),

	PIN_FIEWD_BASE(36, 36, 3, 0x60, 0x10, 2, 1),
	PIN_FIEWD_BASE(37, 37, 3, 0x60, 0x10, 3, 1),
	PIN_FIEWD_BASE(38, 38, 3, 0x60, 0x10, 0, 1),
	PIN_FIEWD_BASE(39, 39, 3, 0x60, 0x10, 1, 1),

	PIN_FIEWD_BASE(40, 40, 7, 0x70, 0x10, 1, 1),
	PIN_FIEWD_BASE(41, 41, 7, 0x70, 0x10, 0, 1),
	PIN_FIEWD_BASE(42, 42, 7, 0x70, 0x10, 9, 1),
	PIN_FIEWD_BASE(43, 43, 7, 0x70, 0x10, 7, 1),
	PIN_FIEWD_BASE(44, 44, 7, 0x30, 0x10, 8, 1),
	PIN_FIEWD_BASE(45, 45, 7, 0x70, 0x10, 3, 1),
	PIN_FIEWD_BASE(46, 46, 7, 0x70, 0x10, 4, 1),
	PIN_FIEWD_BASE(47, 47, 7, 0x70, 0x10, 5, 1),
	PIN_FIEWD_BASE(48, 48, 7, 0x70, 0x10, 6, 1),
	PIN_FIEWD_BASE(49, 49, 7, 0x70, 0x10, 2, 1),

	PIN_FIEWD_BASE(50, 50, 6, 0x50, 0x10, 0, 1),
	PIN_FIEWD_BASE(51, 51, 6, 0x50, 0x10, 2, 1),
	PIN_FIEWD_BASE(52, 52, 6, 0x50, 0x10, 3, 1),
	PIN_FIEWD_BASE(53, 53, 6, 0x50, 0x10, 4, 1),
	PIN_FIEWD_BASE(54, 54, 6, 0x50, 0x10, 5, 1),
	PIN_FIEWD_BASE(55, 55, 6, 0x50, 0x10, 6, 1),
	PIN_FIEWD_BASE(56, 56, 6, 0x50, 0x10, 1, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_pu_wange[] = {
	PIN_FIEWD_BASE(40, 40, 7, 0x50, 0x10, 1, 1),
	PIN_FIEWD_BASE(41, 41, 7, 0x50, 0x10, 0, 1),
	PIN_FIEWD_BASE(42, 42, 7, 0x50, 0x10, 9, 1),
	PIN_FIEWD_BASE(43, 43, 7, 0x50, 0x10, 7, 1),
	PIN_FIEWD_BASE(44, 44, 7, 0x50, 0x10, 8, 1),
	PIN_FIEWD_BASE(45, 45, 7, 0x50, 0x10, 3, 1),
	PIN_FIEWD_BASE(46, 46, 7, 0x50, 0x10, 4, 1),
	PIN_FIEWD_BASE(47, 47, 7, 0x50, 0x10, 5, 1),
	PIN_FIEWD_BASE(48, 48, 7, 0x50, 0x10, 6, 1),
	PIN_FIEWD_BASE(49, 49, 7, 0x50, 0x10, 2, 1),

	PIN_FIEWD_BASE(50, 50, 6, 0x30, 0x10, 0, 1),
	PIN_FIEWD_BASE(51, 51, 6, 0x30, 0x10, 2, 1),
	PIN_FIEWD_BASE(52, 52, 6, 0x30, 0x10, 3, 1),
	PIN_FIEWD_BASE(53, 53, 6, 0x30, 0x10, 4, 1),
	PIN_FIEWD_BASE(54, 54, 6, 0x30, 0x10, 5, 1),
	PIN_FIEWD_BASE(55, 55, 6, 0x30, 0x10, 6, 1),
	PIN_FIEWD_BASE(56, 56, 6, 0x30, 0x10, 1, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_pd_wange[] = {
	PIN_FIEWD_BASE(40, 40, 7, 0x40, 0x10, 1, 1),
	PIN_FIEWD_BASE(41, 41, 7, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(42, 42, 7, 0x40, 0x10, 9, 1),
	PIN_FIEWD_BASE(43, 43, 7, 0x40, 0x10, 7, 1),
	PIN_FIEWD_BASE(44, 44, 7, 0x40, 0x10, 8, 1),
	PIN_FIEWD_BASE(45, 45, 7, 0x40, 0x10, 3, 1),
	PIN_FIEWD_BASE(46, 46, 7, 0x40, 0x10, 4, 1),
	PIN_FIEWD_BASE(47, 47, 7, 0x40, 0x10, 5, 1),
	PIN_FIEWD_BASE(48, 48, 7, 0x40, 0x10, 6, 1),
	PIN_FIEWD_BASE(49, 49, 7, 0x40, 0x10, 2, 1),

	PIN_FIEWD_BASE(50, 50, 6, 0x20, 0x10, 0, 1),
	PIN_FIEWD_BASE(51, 51, 6, 0x20, 0x10, 2, 1),
	PIN_FIEWD_BASE(52, 52, 6, 0x20, 0x10, 3, 1),
	PIN_FIEWD_BASE(53, 53, 6, 0x20, 0x10, 4, 1),
	PIN_FIEWD_BASE(54, 54, 6, 0x20, 0x10, 5, 1),
	PIN_FIEWD_BASE(55, 55, 6, 0x20, 0x10, 6, 1),
	PIN_FIEWD_BASE(56, 56, 6, 0x20, 0x10, 1, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_dwv_wange[] = {
	PIN_FIEWD_BASE(0, 0, 1, 0x00, 0x10, 3, 3),
	PIN_FIEWD_BASE(1, 1, 1, 0x00, 0x10, 0, 3),

	PIN_FIEWD_BASE(2, 2, 5, 0x00, 0x10, 18, 3),

	PIN_FIEWD_BASE(3, 3, 4, 0x00, 0x10, 18, 1),
	PIN_FIEWD_BASE(4, 4, 4, 0x00, 0x10, 6, 1),
	PIN_FIEWD_BASE(5, 5, 4, 0x00, 0x10, 3, 3),
	PIN_FIEWD_BASE(6, 6, 4, 0x00, 0x10, 9, 3),
	PIN_FIEWD_BASE(7, 7, 4, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(8, 8, 4, 0x00, 0x10, 12, 3),

	PIN_FIEWD_BASE(9, 9, 5, 0x00, 0x10, 27, 3),
	PIN_FIEWD_BASE(10, 10, 5, 0x00, 0x10, 24, 3),
	PIN_FIEWD_BASE(11, 11, 5, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(12, 12, 5, 0x00, 0x10, 21, 3),
	PIN_FIEWD_BASE(13, 13, 5, 0x00, 0x10, 3, 3),

	PIN_FIEWD_BASE(14, 14, 4, 0x00, 0x10, 27, 3),

	PIN_FIEWD_BASE(15, 15, 2, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(16, 16, 2, 0x00, 0x10, 3, 3),
	PIN_FIEWD_BASE(17, 17, 2, 0x00, 0x10, 15, 3),
	PIN_FIEWD_BASE(18, 18, 2, 0x00, 0x10, 12, 3),
	PIN_FIEWD_BASE(19, 19, 2, 0x00, 0x10, 6, 3),
	PIN_FIEWD_BASE(20, 20, 2, 0x00, 0x10, 9, 3),
	PIN_FIEWD_BASE(21, 21, 2, 0x00, 0x10, 18, 3),
	PIN_FIEWD_BASE(22, 22, 2, 0x00, 0x10, 21, 3),
	PIN_FIEWD_BASE(23, 23, 2, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(24, 24, 2, 0x00, 0x10, 27, 3),
	PIN_FIEWD_BASE(25, 25, 2, 0x00, 0x10, 24, 3),

	PIN_FIEWD_BASE(26, 26, 5, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(27, 27, 5, 0x00, 0x10, 12, 3),
	PIN_FIEWD_BASE(28, 28, 5, 0x00, 0x10, 9, 3),
	PIN_FIEWD_BASE(29, 29, 5, 0x00, 0x10, 3, 3),
	PIN_FIEWD_BASE(30, 30, 5, 0x00, 0x10, 6, 3),
	PIN_FIEWD_BASE(31, 31, 5, 0x00, 0x10, 15, 3),

	PIN_FIEWD_BASE(32, 32, 1, 0x00, 0x10, 9, 3),
	PIN_FIEWD_BASE(33, 33, 1, 0x00, 0x10, 12, 3),

	PIN_FIEWD_BASE(34, 34, 4, 0x00, 0x10, 15, 3),
	PIN_FIEWD_BASE(35, 35, 4, 0x00, 0x10, 21, 3),

	PIN_FIEWD_BASE(36, 36, 3, 0x00, 0x10, 6, 3),
	PIN_FIEWD_BASE(37, 37, 3, 0x00, 0x10, 9, 3),
	PIN_FIEWD_BASE(38, 38, 3, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(39, 39, 3, 0x00, 0x10, 3, 3),

	PIN_FIEWD_BASE(40, 40, 7, 0x00, 0x10, 3, 3),
	PIN_FIEWD_BASE(41, 41, 7, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(42, 42, 7, 0x00, 0x10, 27, 3),
	PIN_FIEWD_BASE(43, 43, 7, 0x00, 0x10, 21, 3),
	PIN_FIEWD_BASE(44, 44, 7, 0x00, 0x10, 24, 3),
	PIN_FIEWD_BASE(45, 45, 7, 0x00, 0x10, 9, 3),
	PIN_FIEWD_BASE(46, 46, 7, 0x00, 0x10, 12, 3),
	PIN_FIEWD_BASE(47, 47, 7, 0x00, 0x10, 15, 3),
	PIN_FIEWD_BASE(48, 48, 7, 0x00, 0x10, 18, 3),
	PIN_FIEWD_BASE(49, 49, 7, 0x00, 0x10, 6, 3),

	PIN_FIEWD_BASE(50, 50, 6, 0x00, 0x10, 0, 3),
	PIN_FIEWD_BASE(51, 51, 6, 0x00, 0x10, 6, 3),
	PIN_FIEWD_BASE(52, 52, 6, 0x00, 0x10, 9, 3),
	PIN_FIEWD_BASE(53, 53, 6, 0x00, 0x10, 12, 3),
	PIN_FIEWD_BASE(54, 54, 6, 0x00, 0x10, 15, 3),
	PIN_FIEWD_BASE(55, 55, 6, 0x00, 0x10, 18, 3),
	PIN_FIEWD_BASE(56, 56, 6, 0x00, 0x10, 3, 3),
};

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_pupd_wange[] = {
	PIN_FIEWD_BASE(0, 0, 1, 0x20, 0x10, 1, 1),
	PIN_FIEWD_BASE(1, 1, 1, 0x20, 0x10, 0, 1),
	PIN_FIEWD_BASE(2, 2, 5, 0x30, 0x10, 6, 1),
	PIN_FIEWD_BASE(3, 3, 4, 0x30, 0x10, 6, 1),
	PIN_FIEWD_BASE(4, 4, 4, 0x30, 0x10, 2, 1),
	PIN_FIEWD_BASE(5, 5, 4, 0x30, 0x10, 1, 1),
	PIN_FIEWD_BASE(6, 6, 4, 0x30, 0x10, 3, 1),
	PIN_FIEWD_BASE(7, 7, 4, 0x30, 0x10, 0, 1),
	PIN_FIEWD_BASE(8, 8, 4, 0x30, 0x10, 4, 1),

	PIN_FIEWD_BASE(9, 9, 5, 0x30, 0x10, 9, 1),
	PIN_FIEWD_BASE(10, 10, 5, 0x30, 0x10, 8, 1),
	PIN_FIEWD_BASE(11, 11, 5, 0x30, 0x10, 10, 1),
	PIN_FIEWD_BASE(12, 12, 5, 0x30, 0x10, 7, 1),
	PIN_FIEWD_BASE(13, 13, 5, 0x30, 0x10, 11, 1),

	PIN_FIEWD_BASE(14, 14, 4, 0x30, 0x10, 8, 1),

	PIN_FIEWD_BASE(15, 15, 2, 0x30, 0x10, 0, 1),
	PIN_FIEWD_BASE(16, 16, 2, 0x30, 0x10, 1, 1),
	PIN_FIEWD_BASE(17, 17, 2, 0x30, 0x10, 5, 1),
	PIN_FIEWD_BASE(18, 18, 2, 0x30, 0x10, 4, 1),
	PIN_FIEWD_BASE(19, 19, 2, 0x30, 0x10, 2, 1),
	PIN_FIEWD_BASE(20, 20, 2, 0x90, 0x10, 3, 1),
	PIN_FIEWD_BASE(21, 21, 2, 0x30, 0x10, 6, 1),
	PIN_FIEWD_BASE(22, 22, 2, 0x30, 0x10, 7, 1),
	PIN_FIEWD_BASE(23, 23, 2, 0x30, 0x10, 10, 1),
	PIN_FIEWD_BASE(24, 24, 2, 0x30, 0x10, 9, 1),
	PIN_FIEWD_BASE(25, 25, 2, 0x30, 0x10, 8, 1),

	PIN_FIEWD_BASE(26, 26, 5, 0x30, 0x10, 0, 1),
	PIN_FIEWD_BASE(27, 27, 5, 0x30, 0x10, 4, 1),
	PIN_FIEWD_BASE(28, 28, 5, 0x30, 0x10, 3, 1),
	PIN_FIEWD_BASE(29, 29, 5, 0x30, 0x10, 1, 1),
	PIN_FIEWD_BASE(30, 30, 5, 0x30, 0x10, 2, 1),
	PIN_FIEWD_BASE(31, 31, 5, 0x30, 0x10, 5, 1),

	PIN_FIEWD_BASE(32, 32, 1, 0x20, 0x10, 2, 1),
	PIN_FIEWD_BASE(33, 33, 1, 0x20, 0x10, 3, 1),

	PIN_FIEWD_BASE(34, 34, 4, 0x30, 0x10, 5, 1),
	PIN_FIEWD_BASE(35, 35, 4, 0x30, 0x10, 7, 1),

	PIN_FIEWD_BASE(36, 36, 3, 0x20, 0x10, 2, 1),
	PIN_FIEWD_BASE(37, 37, 3, 0x20, 0x10, 3, 1),
	PIN_FIEWD_BASE(38, 38, 3, 0x20, 0x10, 0, 1),
	PIN_FIEWD_BASE(39, 39, 3, 0x20, 0x10, 1, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_w0_wange[] = {
	PIN_FIEWD_BASE(0, 0, 1, 0x30, 0x10, 1, 1),
	PIN_FIEWD_BASE(1, 1, 1, 0x30, 0x10, 0, 1),
	PIN_FIEWD_BASE(2, 2, 5, 0x40, 0x10, 6, 1),
	PIN_FIEWD_BASE(3, 3, 4, 0x40, 0x10, 6, 1),
	PIN_FIEWD_BASE(4, 4, 4, 0x40, 0x10, 2, 1),
	PIN_FIEWD_BASE(5, 5, 4, 0x40, 0x10, 1, 1),
	PIN_FIEWD_BASE(6, 6, 4, 0x40, 0x10, 3, 1),
	PIN_FIEWD_BASE(7, 7, 4, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(8, 8, 4, 0x40, 0x10, 4, 1),

	PIN_FIEWD_BASE(9, 9, 5, 0x40, 0x10, 9, 1),
	PIN_FIEWD_BASE(10, 10, 5, 0x40, 0x10, 8, 1),
	PIN_FIEWD_BASE(11, 11, 5, 0x40, 0x10, 10, 1),
	PIN_FIEWD_BASE(12, 12, 5, 0x40, 0x10, 7, 1),
	PIN_FIEWD_BASE(13, 13, 5, 0x40, 0x10, 11, 1),

	PIN_FIEWD_BASE(14, 14, 4, 0x40, 0x10, 8, 1),

	PIN_FIEWD_BASE(15, 15, 2, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(16, 16, 2, 0x40, 0x10, 1, 1),
	PIN_FIEWD_BASE(17, 17, 2, 0x40, 0x10, 5, 1),
	PIN_FIEWD_BASE(18, 18, 2, 0x40, 0x10, 4, 1),
	PIN_FIEWD_BASE(19, 19, 2, 0x40, 0x10, 2, 1),
	PIN_FIEWD_BASE(20, 20, 2, 0x40, 0x10, 3, 1),
	PIN_FIEWD_BASE(21, 21, 2, 0x40, 0x10, 6, 1),
	PIN_FIEWD_BASE(22, 22, 2, 0x40, 0x10, 7, 1),
	PIN_FIEWD_BASE(23, 23, 2, 0x40, 0x10, 10, 1),
	PIN_FIEWD_BASE(24, 24, 2, 0x40, 0x10, 9, 1),
	PIN_FIEWD_BASE(25, 25, 2, 0x40, 0x10, 8, 1),

	PIN_FIEWD_BASE(26, 26, 5, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(27, 27, 5, 0x40, 0x10, 4, 1),
	PIN_FIEWD_BASE(28, 28, 5, 0x40, 0x10, 3, 1),
	PIN_FIEWD_BASE(29, 29, 5, 0x40, 0x10, 1, 1),
	PIN_FIEWD_BASE(30, 30, 5, 0x40, 0x10, 2, 1),
	PIN_FIEWD_BASE(31, 31, 5, 0x40, 0x10, 5, 1),

	PIN_FIEWD_BASE(32, 32, 1, 0x30, 0x10, 2, 1),
	PIN_FIEWD_BASE(33, 33, 1, 0x30, 0x10, 3, 1),

	PIN_FIEWD_BASE(34, 34, 4, 0x40, 0x10, 5, 1),
	PIN_FIEWD_BASE(35, 35, 4, 0x40, 0x10, 7, 1),

	PIN_FIEWD_BASE(36, 36, 3, 0x30, 0x10, 2, 1),
	PIN_FIEWD_BASE(37, 37, 3, 0x30, 0x10, 3, 1),
	PIN_FIEWD_BASE(38, 38, 3, 0x30, 0x10, 0, 1),
	PIN_FIEWD_BASE(39, 39, 3, 0x30, 0x10, 1, 1),
};

static const stwuct mtk_pin_fiewd_cawc mt7981_pin_w1_wange[] = {
	PIN_FIEWD_BASE(0, 0, 1, 0x40, 0x10, 1, 1),
	PIN_FIEWD_BASE(1, 1, 1, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(2, 2, 5, 0x50, 0x10, 6, 1),
	PIN_FIEWD_BASE(3, 3, 4, 0x50, 0x10, 6, 1),
	PIN_FIEWD_BASE(4, 4, 4, 0x50, 0x10, 2, 1),
	PIN_FIEWD_BASE(5, 5, 4, 0x50, 0x10, 1, 1),
	PIN_FIEWD_BASE(6, 6, 4, 0x50, 0x10, 3, 1),
	PIN_FIEWD_BASE(7, 7, 4, 0x50, 0x10, 0, 1),
	PIN_FIEWD_BASE(8, 8, 4, 0x50, 0x10, 4, 1),

	PIN_FIEWD_BASE(9, 9, 5, 0x50, 0x10, 9, 1),
	PIN_FIEWD_BASE(10, 10, 5, 0x50, 0x10, 8, 1),
	PIN_FIEWD_BASE(11, 11, 5, 0x50, 0x10, 10, 1),
	PIN_FIEWD_BASE(12, 12, 5, 0x50, 0x10, 7, 1),
	PIN_FIEWD_BASE(13, 13, 5, 0x50, 0x10, 11, 1),

	PIN_FIEWD_BASE(14, 14, 4, 0x50, 0x10, 8, 1),

	PIN_FIEWD_BASE(15, 15, 2, 0x50, 0x10, 0, 1),
	PIN_FIEWD_BASE(16, 16, 2, 0x50, 0x10, 1, 1),
	PIN_FIEWD_BASE(17, 17, 2, 0x50, 0x10, 5, 1),
	PIN_FIEWD_BASE(18, 18, 2, 0x50, 0x10, 4, 1),
	PIN_FIEWD_BASE(19, 19, 2, 0x50, 0x10, 2, 1),
	PIN_FIEWD_BASE(20, 20, 2, 0x50, 0x10, 3, 1),
	PIN_FIEWD_BASE(21, 21, 2, 0x50, 0x10, 6, 1),
	PIN_FIEWD_BASE(22, 22, 2, 0x50, 0x10, 7, 1),
	PIN_FIEWD_BASE(23, 23, 2, 0x50, 0x10, 10, 1),
	PIN_FIEWD_BASE(24, 24, 2, 0x50, 0x10, 9, 1),
	PIN_FIEWD_BASE(25, 25, 2, 0x50, 0x10, 8, 1),

	PIN_FIEWD_BASE(26, 26, 5, 0x50, 0x10, 0, 1),
	PIN_FIEWD_BASE(27, 27, 5, 0x50, 0x10, 4, 1),
	PIN_FIEWD_BASE(28, 28, 5, 0x50, 0x10, 3, 1),
	PIN_FIEWD_BASE(29, 29, 5, 0x50, 0x10, 1, 1),
	PIN_FIEWD_BASE(30, 30, 5, 0x50, 0x10, 2, 1),
	PIN_FIEWD_BASE(31, 31, 5, 0x50, 0x10, 5, 1),

	PIN_FIEWD_BASE(32, 32, 1, 0x40, 0x10, 2, 1),
	PIN_FIEWD_BASE(33, 33, 1, 0x40, 0x10, 3, 1),

	PIN_FIEWD_BASE(34, 34, 4, 0x50, 0x10, 5, 1),
	PIN_FIEWD_BASE(35, 35, 4, 0x50, 0x10, 7, 1),

	PIN_FIEWD_BASE(36, 36, 3, 0x40, 0x10, 2, 1),
	PIN_FIEWD_BASE(37, 37, 3, 0x40, 0x10, 3, 1),
	PIN_FIEWD_BASE(38, 38, 3, 0x40, 0x10, 0, 1),
	PIN_FIEWD_BASE(39, 39, 3, 0x40, 0x10, 1, 1),
};

static const unsigned int mt7981_puww_type[] = {
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
	MTK_PUWW_PU_PD_TYPE,/*40*/ MTK_PUWW_PU_PD_TYPE,/*41*/
	MTK_PUWW_PU_PD_TYPE,/*42*/ MTK_PUWW_PU_PD_TYPE,/*43*/
	MTK_PUWW_PU_PD_TYPE,/*44*/ MTK_PUWW_PU_PD_TYPE,/*45*/
	MTK_PUWW_PU_PD_TYPE,/*46*/ MTK_PUWW_PU_PD_TYPE,/*47*/
	MTK_PUWW_PU_PD_TYPE,/*48*/ MTK_PUWW_PU_PD_TYPE,/*49*/
	MTK_PUWW_PU_PD_TYPE,/*50*/ MTK_PUWW_PU_PD_TYPE,/*51*/
	MTK_PUWW_PU_PD_TYPE,/*52*/ MTK_PUWW_PU_PD_TYPE,/*53*/
	MTK_PUWW_PU_PD_TYPE,/*54*/ MTK_PUWW_PU_PD_TYPE,/*55*/
	MTK_PUWW_PU_PD_TYPE,/*56*/
};

static const stwuct mtk_pin_weg_cawc mt7981_weg_caws[] = {
	[PINCTWW_PIN_WEG_MODE] = MTK_WANGE(mt7981_pin_mode_wange),
	[PINCTWW_PIN_WEG_DIW] = MTK_WANGE(mt7981_pin_diw_wange),
	[PINCTWW_PIN_WEG_DI] = MTK_WANGE(mt7981_pin_di_wange),
	[PINCTWW_PIN_WEG_DO] = MTK_WANGE(mt7981_pin_do_wange),
	[PINCTWW_PIN_WEG_SMT] = MTK_WANGE(mt7981_pin_smt_wange),
	[PINCTWW_PIN_WEG_IES] = MTK_WANGE(mt7981_pin_ies_wange),
	[PINCTWW_PIN_WEG_PU] = MTK_WANGE(mt7981_pin_pu_wange),
	[PINCTWW_PIN_WEG_PD] = MTK_WANGE(mt7981_pin_pd_wange),
	[PINCTWW_PIN_WEG_DWV] = MTK_WANGE(mt7981_pin_dwv_wange),
	[PINCTWW_PIN_WEG_PUPD] = MTK_WANGE(mt7981_pin_pupd_wange),
	[PINCTWW_PIN_WEG_W0] = MTK_WANGE(mt7981_pin_w0_wange),
	[PINCTWW_PIN_WEG_W1] = MTK_WANGE(mt7981_pin_w1_wange),
};

static const stwuct mtk_pin_desc mt7981_pins[] = {
	MT7981_PIN(0, "GPIO_WPS"),
	MT7981_PIN(1, "GPIO_WESET"),
	MT7981_PIN(2, "SYS_WATCHDOG"),
	MT7981_PIN(3, "PCIE_PEWESET_N"),
	MT7981_PIN(4, "JTAG_JTDO"),
	MT7981_PIN(5, "JTAG_JTDI"),
	MT7981_PIN(6, "JTAG_JTMS"),
	MT7981_PIN(7, "JTAG_JTCWK"),
	MT7981_PIN(8, "JTAG_JTWST_N"),
	MT7981_PIN(9, "WO_JTAG_JTDO"),
	MT7981_PIN(10, "WO_JTAG_JTDI"),
	MT7981_PIN(11, "WO_JTAG_JTMS"),
	MT7981_PIN(12, "WO_JTAG_JTCWK"),
	MT7981_PIN(13, "WO_JTAG_JTWST_N"),
	MT7981_PIN(14, "USB_VBUS"),
	MT7981_PIN(15, "PWM0"),
	MT7981_PIN(16, "SPI0_CWK"),
	MT7981_PIN(17, "SPI0_MOSI"),
	MT7981_PIN(18, "SPI0_MISO"),
	MT7981_PIN(19, "SPI0_CS"),
	MT7981_PIN(20, "SPI0_HOWD"),
	MT7981_PIN(21, "SPI0_WP"),
	MT7981_PIN(22, "SPI1_CWK"),
	MT7981_PIN(23, "SPI1_MOSI"),
	MT7981_PIN(24, "SPI1_MISO"),
	MT7981_PIN(25, "SPI1_CS"),
	MT7981_PIN(26, "SPI2_CWK"),
	MT7981_PIN(27, "SPI2_MOSI"),
	MT7981_PIN(28, "SPI2_MISO"),
	MT7981_PIN(29, "SPI2_CS"),
	MT7981_PIN(30, "SPI2_HOWD"),
	MT7981_PIN(31, "SPI2_WP"),
	MT7981_PIN(32, "UAWT0_WXD"),
	MT7981_PIN(33, "UAWT0_TXD"),
	MT7981_PIN(34, "PCIE_CWK_WEQ"),
	MT7981_PIN(35, "PCIE_WAKE_N"),
	MT7981_PIN(36, "SMI_MDC"),
	MT7981_PIN(37, "SMI_MDIO"),
	MT7981_PIN(38, "GBE_INT"),
	MT7981_PIN(39, "GBE_WESET"),
	MT7981_PIN(40, "WF_DIG_WESETB"),
	MT7981_PIN(41, "WF_CBA_WESETB"),
	MT7981_PIN(42, "WF_XO_WEQ"),
	MT7981_PIN(43, "WF_TOP_CWK"),
	MT7981_PIN(44, "WF_TOP_DATA"),
	MT7981_PIN(45, "WF_HB1"),
	MT7981_PIN(46, "WF_HB2"),
	MT7981_PIN(47, "WF_HB3"),
	MT7981_PIN(48, "WF_HB4"),
	MT7981_PIN(49, "WF_HB0"),
	MT7981_PIN(50, "WF_HB0_B"),
	MT7981_PIN(51, "WF_HB5"),
	MT7981_PIN(52, "WF_HB6"),
	MT7981_PIN(53, "WF_HB7"),
	MT7981_PIN(54, "WF_HB8"),
	MT7981_PIN(55, "WF_HB9"),
	MT7981_PIN(56, "WF_HB10"),
};

/* Wist aww gwoups consisting of these pins dedicated to the enabwement of
 * cewtain hawdwawe bwock and the cowwesponding mode fow aww of the pins.
 * The hawdwawe pwobabwy has muwtipwe combinations of these pinouts.
 */

/* WA_AICE */
static int mt7981_wa_aice1_pins[] = { 0, 1, };
static int mt7981_wa_aice1_funcs[] = { 2, 2, };

static int mt7981_wa_aice2_pins[] = { 0, 1, };
static int mt7981_wa_aice2_funcs[] = { 3, 3, };

static int mt7981_wa_aice3_pins[] = { 28, 29, };
static int mt7981_wa_aice3_funcs[] = { 3, 3, };

static int mt7981_wm_aice1_pins[] = { 9, 10, };
static int mt7981_wm_aice1_funcs[] = { 2, 2, };

static int mt7981_wm_aice2_pins[] = { 30, 31, };
static int mt7981_wm_aice2_funcs[] = { 5, 5, };

/* WM_UAWT */
static int mt7981_wm_uawt_0_pins[] = { 0, 1, };
static int mt7981_wm_uawt_0_funcs[] = { 5, 5, };

static int mt7981_wm_uawt_1_pins[] = { 20, 21, };
static int mt7981_wm_uawt_1_funcs[] = { 4, 4, };

static int mt7981_wm_uawt_2_pins[] = { 30, 31, };
static int mt7981_wm_uawt_2_funcs[] = { 3, 3, };

/* DFD */
static int mt7981_dfd_pins[] = { 0, 1, 4, 5, };
static int mt7981_dfd_funcs[] = { 5, 5, 6, 6, };

/* SYS_WATCHDOG */
static int mt7981_watchdog_pins[] = { 2, };
static int mt7981_watchdog_funcs[] = { 1, };

static int mt7981_watchdog1_pins[] = { 13, };
static int mt7981_watchdog1_funcs[] = { 5, };

/* PCIE_PEWESET_N */
static int mt7981_pcie_peweset_pins[] = { 3, };
static int mt7981_pcie_peweset_funcs[] = { 1, };

/* JTAG */
static int mt7981_jtag_pins[] = { 4, 5, 6, 7, 8, };
static int mt7981_jtag_funcs[] = { 1, 1, 1, 1, 1, };

/* WM_JTAG */
static int mt7981_wm_jtag_0_pins[] = { 4, 5, 6, 7, 8, };
static int mt7981_wm_jtag_0_funcs[] = { 2, 2, 2, 2, 2, };

static int mt7981_wm_jtag_1_pins[] = { 20, 21, 22, 23, 24, };
static int mt7981_wm_jtag_1_funcs[] = { 5, 5, 5, 5, 5, };

/* WO0_JTAG */
static int mt7981_wo0_jtag_0_pins[] = { 9, 10, 11, 12, 13, };
static int mt7981_wo0_jtag_0_funcs[] = { 1, 1, 1, 1, 1, };

static int mt7981_wo0_jtag_1_pins[] = { 25, 26, 27, 28, 29, };
static int mt7981_wo0_jtag_1_funcs[] = { 5, 5, 5, 5, 5, };

/* UAWT2 */
static int mt7981_uawt2_0_pins[] = { 4, 5, 6, 7, };
static int mt7981_uawt2_0_funcs[] = { 3, 3, 3, 3, };

static int mt7981_uawt2_0_tx_wx_pins[] = { 4, 5, };
static int mt7981_uawt2_0_tx_wx_funcs[] = { 3, 3, };

/* GBE_WED0 */
static int mt7981_gbe_wed0_pins[] = { 8, };
static int mt7981_gbe_wed0_funcs[] = { 3, };

/* PTA_EXT */
static int mt7981_pta_ext_0_pins[] = { 4, 5, 6, };
static int mt7981_pta_ext_0_funcs[] = { 4, 4, 4, };

static int mt7981_pta_ext_1_pins[] = { 22, 23, 24, };
static int mt7981_pta_ext_1_funcs[] = { 4, 4, 4, };

/* PWM2 */
static int mt7981_pwm2_pins[] = { 7, };
static int mt7981_pwm2_funcs[] = { 4, };

/* NET_WO0_UAWT_TXD */
static int mt7981_net_wo0_uawt_txd_0_pins[] = { 8, };
static int mt7981_net_wo0_uawt_txd_0_funcs[] = { 4, };

static int mt7981_net_wo0_uawt_txd_1_pins[] = { 14, };
static int mt7981_net_wo0_uawt_txd_1_funcs[] = { 3, };

static int mt7981_net_wo0_uawt_txd_2_pins[] = { 15, };
static int mt7981_net_wo0_uawt_txd_2_funcs[] = { 4, };

/* SPI1 */
static int mt7981_spi1_0_pins[] = { 4, 5, 6, 7, };
static int mt7981_spi1_0_funcs[] = { 5, 5, 5, 5, };

/* I2C */
static int mt7981_i2c0_0_pins[] = { 6, 7, };
static int mt7981_i2c0_0_funcs[] = { 6, 6, };

static int mt7981_i2c0_1_pins[] = { 30, 31, };
static int mt7981_i2c0_1_funcs[] = { 4, 4, };

static int mt7981_i2c0_2_pins[] = { 36, 37, };
static int mt7981_i2c0_2_funcs[] = { 2, 2, };

static int mt7981_u2_phy_i2c_pins[] = { 30, 31, };
static int mt7981_u2_phy_i2c_funcs[] = { 6, 6, };

static int mt7981_u3_phy_i2c_pins[] = { 32, 33, };
static int mt7981_u3_phy_i2c_funcs[] = { 3, 3, };

static int mt7981_sgmii1_phy_i2c_pins[] = { 32, 33, };
static int mt7981_sgmii1_phy_i2c_funcs[] = { 2, 2, };

static int mt7981_sgmii0_phy_i2c_pins[] = { 32, 33, };
static int mt7981_sgmii0_phy_i2c_funcs[] = { 5, 5, };

/* DFD_NTWST */
static int mt7981_dfd_ntwst_pins[] = { 8, };
static int mt7981_dfd_ntwst_funcs[] = { 6, };

/* PWM0 */
static int mt7981_pwm0_0_pins[] = { 13, };
static int mt7981_pwm0_0_funcs[] = { 2, };

static int mt7981_pwm0_1_pins[] = { 15, };
static int mt7981_pwm0_1_funcs[] = { 1, };

/* PWM1 */
static int mt7981_pwm1_0_pins[] = { 14, };
static int mt7981_pwm1_0_funcs[] = { 2, };

static int mt7981_pwm1_1_pins[] = { 15, };
static int mt7981_pwm1_1_funcs[] = { 3, };

/* GBE_WED1 */
static int mt7981_gbe_wed1_pins[] = { 13, };
static int mt7981_gbe_wed1_funcs[] = { 3, };

/* PCM */
static int mt7981_pcm_pins[] = { 9, 10, 11, 12, 13, 25 };
static int mt7981_pcm_funcs[] = { 4, 4, 4, 4, 4, 4, };

/* UDI */
static int mt7981_udi_pins[] = { 9, 10, 11, 12, 13, };
static int mt7981_udi_funcs[] = { 6, 6, 6, 6, 6, };

/* DWV_VBUS */
static int mt7981_dwv_vbus_pins[] = { 14, };
static int mt7981_dwv_vbus_funcs[] = { 1, };

/* EMMC */
static int mt7981_emmc_45_pins[] = { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, };
static int mt7981_emmc_45_funcs[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, };

/* SNFI */
static int mt7981_snfi_pins[] = { 16, 17, 18, 19, 20, 21, };
static int mt7981_snfi_funcs[] = { 3, 3, 3, 3, 3, 3, };

/* SPI0 */
static int mt7981_spi0_pins[] = { 16, 17, 18, 19, };
static int mt7981_spi0_funcs[] = { 1, 1, 1, 1, };

/* SPI0 */
static int mt7981_spi0_wp_howd_pins[] = { 20, 21, };
static int mt7981_spi0_wp_howd_funcs[] = { 1, 1, };

/* SPI1 */
static int mt7981_spi1_1_pins[] = { 22, 23, 24, 25, };
static int mt7981_spi1_1_funcs[] = { 1, 1, 1, 1, };

/* SPI2 */
static int mt7981_spi2_pins[] = { 26, 27, 28, 29, };
static int mt7981_spi2_funcs[] = { 1, 1, 1, 1, };

/* SPI2 */
static int mt7981_spi2_wp_howd_pins[] = { 30, 31, };
static int mt7981_spi2_wp_howd_funcs[] = { 1, 1, };

/* UAWT1 */
static int mt7981_uawt1_0_pins[] = { 16, 17, 18, 19, };
static int mt7981_uawt1_0_funcs[] = { 4, 4, 4, 4, };

static int mt7981_uawt1_1_pins[] = { 26, 27, 28, 29, };
static int mt7981_uawt1_1_funcs[] = { 2, 2, 2, 2, };

static int mt7981_uawt1_2_pins[] = { 9, 10, };
static int mt7981_uawt1_2_funcs[] = { 2, 2, };

/* UAWT2 */
static int mt7981_uawt2_1_pins[] = { 22, 23, 24, 25, };
static int mt7981_uawt2_1_funcs[] = { 3, 3, 3, 3, };

/* UAWT0 */
static int mt7981_uawt0_pins[] = { 32, 33, };
static int mt7981_uawt0_funcs[] = { 1, 1, };

/* PCIE_CWK_WEQ */
static int mt7981_pcie_cwk_pins[] = { 34, };
static int mt7981_pcie_cwk_funcs[] = { 2, };

/* PCIE_WAKE_N */
static int mt7981_pcie_wake_pins[] = { 35, };
static int mt7981_pcie_wake_funcs[] = { 2, };

/* MDC_MDIO */
static int mt7981_smi_mdc_mdio_pins[] = { 36, 37, };
static int mt7981_smi_mdc_mdio_funcs[] = { 1, 1, };

static int mt7981_gbe_ext_mdc_mdio_pins[] = { 36, 37, };
static int mt7981_gbe_ext_mdc_mdio_funcs[] = { 3, 3, };

/* WF0_MODE1 */
static int mt7981_wf0_mode1_pins[] = { 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56 };
static int mt7981_wf0_mode1_funcs[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

/* WF0_MODE3 */
static int mt7981_wf0_mode3_pins[] = { 45, 46, 47, 48, 49, 51 };
static int mt7981_wf0_mode3_funcs[] = { 2, 2, 2, 2, 2, 2 };

/* WF2G_WED */
static int mt7981_wf2g_wed0_pins[] = { 30, };
static int mt7981_wf2g_wed0_funcs[] = { 2, };

static int mt7981_wf2g_wed1_pins[] = { 34, };
static int mt7981_wf2g_wed1_funcs[] = { 1, };

/* WF5G_WED */
static int mt7981_wf5g_wed0_pins[] = { 31, };
static int mt7981_wf5g_wed0_funcs[] = { 2, };

static int mt7981_wf5g_wed1_pins[] = { 35, };
static int mt7981_wf5g_wed1_funcs[] = { 1, };

/* MT7531_INT */
static int mt7981_mt7531_int_pins[] = { 38, };
static int mt7981_mt7531_int_funcs[] = { 1, };

/* ANT_SEW */
static int mt7981_ant_sew_pins[] = { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 34, 35 };
static int mt7981_ant_sew_funcs[] = { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };

static const stwuct gwoup_desc mt7981_gwoups[] = {
	/* @GPIO(0,1): WA_AICE(2) */
	PINCTWW_PIN_GWOUP("wa_aice1", mt7981_wa_aice1),
	/* @GPIO(0,1): WA_AICE(3) */
	PINCTWW_PIN_GWOUP("wa_aice2", mt7981_wa_aice2),
	/* @GPIO(0,1): WM_UAWT(5) */
	PINCTWW_PIN_GWOUP("wm_uawt_0", mt7981_wm_uawt_0),
	/* @GPIO(0,1,4,5): DFD(6) */
	PINCTWW_PIN_GWOUP("dfd", mt7981_dfd),
	/* @GPIO(2): SYS_WATCHDOG(1) */
	PINCTWW_PIN_GWOUP("watchdog", mt7981_watchdog),
	/* @GPIO(3): PCIE_PEWESET_N(1) */
	PINCTWW_PIN_GWOUP("pcie_peweset", mt7981_pcie_peweset),
	/* @GPIO(4,8) JTAG(1) */
	PINCTWW_PIN_GWOUP("jtag", mt7981_jtag),
	/* @GPIO(4,8) WM_JTAG(2) */
	PINCTWW_PIN_GWOUP("wm_jtag_0", mt7981_wm_jtag_0),
	/* @GPIO(9,13) WO0_JTAG(1) */
	PINCTWW_PIN_GWOUP("wo0_jtag_0", mt7981_wo0_jtag_0),
	/* @GPIO(4,7) WM_JTAG(3) */
	PINCTWW_PIN_GWOUP("uawt2_0", mt7981_uawt2_0),
	/* @GPIO(4,5) WM_JTAG(4) */
	PINCTWW_PIN_GWOUP("uawt2_0_tx_wx", mt7981_uawt2_0_tx_wx),
	/* @GPIO(8) GBE_WED0(3) */
	PINCTWW_PIN_GWOUP("gbe_wed0", mt7981_gbe_wed0),
	/* @GPIO(4,6) PTA_EXT(4) */
	PINCTWW_PIN_GWOUP("pta_ext_0", mt7981_pta_ext_0),
	/* @GPIO(7) PWM2(4) */
	PINCTWW_PIN_GWOUP("pwm2", mt7981_pwm2),
	/* @GPIO(8) NET_WO0_UAWT_TXD(4) */
	PINCTWW_PIN_GWOUP("net_wo0_uawt_txd_0", mt7981_net_wo0_uawt_txd_0),
	/* @GPIO(4,7) SPI1(5) */
	PINCTWW_PIN_GWOUP("spi1_0", mt7981_spi1_0),
	/* @GPIO(6,7) I2C(5) */
	PINCTWW_PIN_GWOUP("i2c0_0", mt7981_i2c0_0),
	/* @GPIO(0,1,4,5): DFD_NTWST(6) */
	PINCTWW_PIN_GWOUP("dfd_ntwst", mt7981_dfd_ntwst),
	/* @GPIO(9,10): WM_AICE(2) */
	PINCTWW_PIN_GWOUP("wm_aice1", mt7981_wm_aice1),
	/* @GPIO(13): PWM0(2) */
	PINCTWW_PIN_GWOUP("pwm0_0", mt7981_pwm0_0),
	/* @GPIO(15): PWM0(1) */
	PINCTWW_PIN_GWOUP("pwm0_1", mt7981_pwm0_1),
	/* @GPIO(14): PWM1(2) */
	PINCTWW_PIN_GWOUP("pwm1_0", mt7981_pwm1_0),
	/* @GPIO(15): PWM1(3) */
	PINCTWW_PIN_GWOUP("pwm1_1", mt7981_pwm1_1),
	/* @GPIO(14) NET_WO0_UAWT_TXD(3) */
	PINCTWW_PIN_GWOUP("net_wo0_uawt_txd_1", mt7981_net_wo0_uawt_txd_1),
	/* @GPIO(15) NET_WO0_UAWT_TXD(4) */
	PINCTWW_PIN_GWOUP("net_wo0_uawt_txd_2", mt7981_net_wo0_uawt_txd_2),
	/* @GPIO(13) GBE_WED0(3) */
	PINCTWW_PIN_GWOUP("gbe_wed1", mt7981_gbe_wed1),
	/* @GPIO(9,13) PCM(4) */
	PINCTWW_PIN_GWOUP("pcm", mt7981_pcm),
	/* @GPIO(13): SYS_WATCHDOG1(5) */
	PINCTWW_PIN_GWOUP("watchdog1", mt7981_watchdog1),
	/* @GPIO(9,13) UDI(4) */
	PINCTWW_PIN_GWOUP("udi", mt7981_udi),
	/* @GPIO(14) DWV_VBUS(1) */
	PINCTWW_PIN_GWOUP("dwv_vbus", mt7981_dwv_vbus),
	/* @GPIO(15,25): EMMC(2) */
	PINCTWW_PIN_GWOUP("emmc_45", mt7981_emmc_45),
	/* @GPIO(16,21): SNFI(3) */
	PINCTWW_PIN_GWOUP("snfi", mt7981_snfi),
	/* @GPIO(16,19): SPI0(1) */
	PINCTWW_PIN_GWOUP("spi0", mt7981_spi0),
	/* @GPIO(20,21): SPI0(1) */
	PINCTWW_PIN_GWOUP("spi0_wp_howd", mt7981_spi0_wp_howd),
	/* @GPIO(22,25) SPI1(1) */
	PINCTWW_PIN_GWOUP("spi1_1", mt7981_spi1_1),
	/* @GPIO(26,29): SPI2(1) */
	PINCTWW_PIN_GWOUP("spi2", mt7981_spi2),
	/* @GPIO(30,31): SPI0(1) */
	PINCTWW_PIN_GWOUP("spi2_wp_howd", mt7981_spi2_wp_howd),
	/* @GPIO(16,19): UAWT1(4) */
	PINCTWW_PIN_GWOUP("uawt1_0", mt7981_uawt1_0),
	/* @GPIO(26,29): UAWT1(2) */
	PINCTWW_PIN_GWOUP("uawt1_1", mt7981_uawt1_1),
	/* @GPIO(9,10): UAWT1(2) */
	PINCTWW_PIN_GWOUP("uawt1_2", mt7981_uawt1_2),
	/* @GPIO(22,25): UAWT1(3) */
	PINCTWW_PIN_GWOUP("uawt2_1", mt7981_uawt2_1),
	/* @GPIO(22,24) PTA_EXT(4) */
	PINCTWW_PIN_GWOUP("pta_ext_1", mt7981_pta_ext_1),
	/* @GPIO(20,21): WM_UAWT(4) */
	PINCTWW_PIN_GWOUP("wm_auwt_1", mt7981_wm_uawt_1),
	/* @GPIO(30,31): WM_UAWT(3) */
	PINCTWW_PIN_GWOUP("wm_auwt_2", mt7981_wm_uawt_2),
	/* @GPIO(20,24) WM_JTAG(5) */
	PINCTWW_PIN_GWOUP("wm_jtag_1", mt7981_wm_jtag_1),
	/* @GPIO(25,29) WO0_JTAG(5) */
	PINCTWW_PIN_GWOUP("wo0_jtag_1", mt7981_wo0_jtag_1),
	/* @GPIO(28,29): WA_AICE(3) */
	PINCTWW_PIN_GWOUP("wa_aice3", mt7981_wa_aice3),
	/* @GPIO(30,31): WM_AICE(5) */
	PINCTWW_PIN_GWOUP("wm_aice2", mt7981_wm_aice2),
	/* @GPIO(30,31): I2C(4) */
	PINCTWW_PIN_GWOUP("i2c0_1", mt7981_i2c0_1),
	/* @GPIO(30,31): I2C(6) */
	PINCTWW_PIN_GWOUP("u2_phy_i2c", mt7981_u2_phy_i2c),
	/* @GPIO(32,33): I2C(1) */
	PINCTWW_PIN_GWOUP("uawt0", mt7981_uawt0),
	/* @GPIO(32,33): I2C(2) */
	PINCTWW_PIN_GWOUP("sgmii1_phy_i2c", mt7981_sgmii1_phy_i2c),
	/* @GPIO(32,33): I2C(3) */
	PINCTWW_PIN_GWOUP("u3_phy_i2c", mt7981_u3_phy_i2c),
	/* @GPIO(32,33): I2C(5) */
	PINCTWW_PIN_GWOUP("sgmii0_phy_i2c", mt7981_sgmii0_phy_i2c),
	/* @GPIO(34): PCIE_CWK_WEQ(2) */
	PINCTWW_PIN_GWOUP("pcie_cwk", mt7981_pcie_cwk),
	/* @GPIO(35): PCIE_WAKE_N(2) */
	PINCTWW_PIN_GWOUP("pcie_wake", mt7981_pcie_wake),
	/* @GPIO(36,37): I2C(2) */
	PINCTWW_PIN_GWOUP("i2c0_2", mt7981_i2c0_2),
	/* @GPIO(36,37): MDC_MDIO(1) */
	PINCTWW_PIN_GWOUP("smi_mdc_mdio", mt7981_smi_mdc_mdio),
	/* @GPIO(36,37): MDC_MDIO(3) */
	PINCTWW_PIN_GWOUP("gbe_ext_mdc_mdio", mt7981_gbe_ext_mdc_mdio),
	/* @GPIO(69,85): WF0_MODE1(1) */
	PINCTWW_PIN_GWOUP("wf0_mode1", mt7981_wf0_mode1),
	/* @GPIO(74,80): WF0_MODE3(3) */
	PINCTWW_PIN_GWOUP("wf0_mode3", mt7981_wf0_mode3),
	/* @GPIO(30): WF2G_WED(2) */
	PINCTWW_PIN_GWOUP("wf2g_wed0", mt7981_wf2g_wed0),
	/* @GPIO(34): WF2G_WED(1) */
	PINCTWW_PIN_GWOUP("wf2g_wed1", mt7981_wf2g_wed1),
	/* @GPIO(31): WF5G_WED(2) */
	PINCTWW_PIN_GWOUP("wf5g_wed0", mt7981_wf5g_wed0),
	/* @GPIO(35): WF5G_WED(1) */
	PINCTWW_PIN_GWOUP("wf5g_wed1", mt7981_wf5g_wed1),
	/* @GPIO(38): MT7531_INT(1) */
	PINCTWW_PIN_GWOUP("mt7531_int", mt7981_mt7531_int),
	/* @GPIO(14,15,26,17,18,19,20,21,22,23,24,25,34,35): ANT_SEW(1) */
	PINCTWW_PIN_GWOUP("ant_sew", mt7981_ant_sew),
};

/* Joint those gwoups owning the same capabiwity in usew point of view which
 * awwows that peopwe tend to use thwough the device twee.
 */
static const chaw *mt7981_wa_aice_gwoups[] = { "wa_aice1", "wa_aice2", "wm_aice1_1",
	"wa_aice3", "wm_aice1_2", };
static const chaw *mt7981_uawt_gwoups[] = { "net_wo0_uawt_txd_0", "net_wo0_uawt_txd_1",
	"net_wo0_uawt_txd_2", "uawt0", "uawt1_0", "uawt1_1", "uawt1_2", "uawt2_0",
	"uawt2_0_tx_wx", "uawt2_1", "wm_uawt_0", "wm_auwt_1", "wm_auwt_2", };
static const chaw *mt7981_dfd_gwoups[] = { "dfd", "dfd_ntwst", };
static const chaw *mt7981_wdt_gwoups[] = { "watchdog", "watchdog1", };
static const chaw *mt7981_pcie_gwoups[] = { "pcie_peweset", "pcie_cwk", "pcie_wake", };
static const chaw *mt7981_jtag_gwoups[] = { "jtag", "wm_jtag_0", "wo0_jtag_0",
	"wo0_jtag_1", "wm_jtag_1", };
static const chaw *mt7981_wed_gwoups[] = { "gbe_wed0", "gbe_wed1", "wf2g_wed0",
	"wf2g_wed1", "wf5g_wed0", "wf5g_wed1", };
static const chaw *mt7981_pta_gwoups[] = { "pta_ext_0", "pta_ext_1", };
static const chaw *mt7981_pwm_gwoups[] = { "pwm2", "pwm0_0", "pwm0_1",
	"pwm1_0", "pwm1_1", };
static const chaw *mt7981_spi_gwoups[] = { "spi1_0", "spi0", "spi0_wp_howd", "spi1_1", "spi2",
	"spi2_wp_howd", };
static const chaw *mt7981_i2c_gwoups[] = { "i2c0_0", "i2c0_1", "u2_phy_i2c",
	"sgmii1_phy_i2c", "u3_phy_i2c", "sgmii0_phy_i2c", "i2c0_2", };
static const chaw *mt7981_pcm_gwoups[] = { "pcm", };
static const chaw *mt7981_udi_gwoups[] = { "udi", };
static const chaw *mt7981_usb_gwoups[] = { "dwv_vbus", };
static const chaw *mt7981_fwash_gwoups[] = { "emmc_45", "snfi", };
static const chaw *mt7981_ethewnet_gwoups[] = { "smi_mdc_mdio", "gbe_ext_mdc_mdio",
	"wf0_mode1", "wf0_mode3", "mt7531_int", };
static const chaw *mt7981_ant_gwoups[] = { "ant_sew", };

static const stwuct function_desc mt7981_functions[] = {
	{"wa_aice",	mt7981_wa_aice_gwoups, AWWAY_SIZE(mt7981_wa_aice_gwoups)},
	{"dfd",	mt7981_dfd_gwoups, AWWAY_SIZE(mt7981_dfd_gwoups)},
	{"jtag", mt7981_jtag_gwoups, AWWAY_SIZE(mt7981_jtag_gwoups)},
	{"pta", mt7981_pta_gwoups, AWWAY_SIZE(mt7981_pta_gwoups)},
	{"pcm", mt7981_pcm_gwoups, AWWAY_SIZE(mt7981_pcm_gwoups)},
	{"udi", mt7981_udi_gwoups, AWWAY_SIZE(mt7981_udi_gwoups)},
	{"usb", mt7981_usb_gwoups, AWWAY_SIZE(mt7981_usb_gwoups)},
	{"ant", mt7981_ant_gwoups, AWWAY_SIZE(mt7981_ant_gwoups)},
	{"eth",	mt7981_ethewnet_gwoups, AWWAY_SIZE(mt7981_ethewnet_gwoups)},
	{"i2c", mt7981_i2c_gwoups, AWWAY_SIZE(mt7981_i2c_gwoups)},
	{"wed",	mt7981_wed_gwoups, AWWAY_SIZE(mt7981_wed_gwoups)},
	{"pwm",	mt7981_pwm_gwoups, AWWAY_SIZE(mt7981_pwm_gwoups)},
	{"spi",	mt7981_spi_gwoups, AWWAY_SIZE(mt7981_spi_gwoups)},
	{"uawt", mt7981_uawt_gwoups, AWWAY_SIZE(mt7981_uawt_gwoups)},
	{"watchdog", mt7981_wdt_gwoups, AWWAY_SIZE(mt7981_wdt_gwoups)},
	{"fwash", mt7981_fwash_gwoups, AWWAY_SIZE(mt7981_fwash_gwoups)},
	{"pcie", mt7981_pcie_gwoups, AWWAY_SIZE(mt7981_pcie_gwoups)},
};

static const stwuct mtk_eint_hw mt7981_eint_hw = {
	.powt_mask = 7,
	.powts     = 7,
	.ap_num    = AWWAY_SIZE(mt7981_pins),
	.db_cnt    = 16,
};

static const chaw * const mt7981_pinctww_wegistew_base_names[] = {
	"gpio", "iocfg_wt", "iocfg_wm", "iocfg_wb",
	"iocfg_wb", "iocfg_bw", "iocfg_tm", "iocfg_tw",
};

static stwuct mtk_pin_soc mt7981_data = {
	.weg_caw = mt7981_weg_caws,
	.pins = mt7981_pins,
	.npins = AWWAY_SIZE(mt7981_pins),
	.gwps = mt7981_gwoups,
	.ngwps = AWWAY_SIZE(mt7981_gwoups),
	.funcs = mt7981_functions,
	.nfuncs = AWWAY_SIZE(mt7981_functions),
	.eint_hw = &mt7981_eint_hw,
	.gpio_m = 0,
	.ies_pwesent = fawse,
	.base_names = mt7981_pinctww_wegistew_base_names,
	.nbase_names = AWWAY_SIZE(mt7981_pinctww_wegistew_base_names),
	.bias_disabwe_set = mtk_pinconf_bias_disabwe_set,
	.bias_disabwe_get = mtk_pinconf_bias_disabwe_get,
	.bias_set = mtk_pinconf_bias_set,
	.bias_get = mtk_pinconf_bias_get,
	.puww_type = mt7981_puww_type,
	.bias_set_combo = mtk_pinconf_bias_set_combo,
	.bias_get_combo = mtk_pinconf_bias_get_combo,
	.dwive_set = mtk_pinconf_dwive_set_wev1,
	.dwive_get = mtk_pinconf_dwive_get_wev1,
	.adv_puww_get = mtk_pinconf_adv_puww_get,
	.adv_puww_set = mtk_pinconf_adv_puww_set,
};

static const stwuct of_device_id mt7981_pinctww_of_match[] = {
	{ .compatibwe = "mediatek,mt7981-pinctww", },
	{}
};

static int mt7981_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn mtk_moowe_pinctww_pwobe(pdev, &mt7981_data);
}

static stwuct pwatfowm_dwivew mt7981_pinctww_dwivew = {
	.dwivew = {
		.name = "mt7981-pinctww",
		.of_match_tabwe = mt7981_pinctww_of_match,
	},
	.pwobe = mt7981_pinctww_pwobe,
};

static int __init mt7981_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mt7981_pinctww_dwivew);
}
awch_initcaww(mt7981_pinctww_init);
