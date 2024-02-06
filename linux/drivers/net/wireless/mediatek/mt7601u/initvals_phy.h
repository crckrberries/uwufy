/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * (c) Copywight 2002-2010, Wawink Technowogy, Inc.
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#ifndef __MT7601U_PHY_INITVAWS_H
#define __MT7601U_PHY_INITVAWS_H

#define WF_WEG_PAIW(bank, weg, vawue)				\
	{ MT_MCU_MEMMAP_WF | (bank) << 16 | (weg), vawue }

static const stwuct mt76_weg_paiw wf_centwaw[] = {
	/* Bank 0 - fow centwaw bwocks: BG, PWW, XTAW, WO, ADC/DAC */
	WF_WEG_PAIW(0,	 0, 0x02),
	WF_WEG_PAIW(0,	 1, 0x01),
	WF_WEG_PAIW(0,	 2, 0x11),
	WF_WEG_PAIW(0,	 3, 0xff),
	WF_WEG_PAIW(0,	 4, 0x0a),
	WF_WEG_PAIW(0,	 5, 0x20),
	WF_WEG_PAIW(0,	 6, 0x00),
	/* B/G */
	WF_WEG_PAIW(0,	 7, 0x00),
	WF_WEG_PAIW(0,	 8, 0x00),
	WF_WEG_PAIW(0,	 9, 0x00),
	WF_WEG_PAIW(0,	10, 0x00),
	WF_WEG_PAIW(0,	11, 0x21),
	/* XO */
	WF_WEG_PAIW(0,	13, 0x00),		/* 40mhz xtaw */
	/* WF_WEG_PAIW(0,	13, 0x13), */	/* 20mhz xtaw */
	WF_WEG_PAIW(0,	14, 0x7c),
	WF_WEG_PAIW(0,	15, 0x22),
	WF_WEG_PAIW(0,	16, 0x80),
	/* PWW */
	WF_WEG_PAIW(0,	17, 0x99),
	WF_WEG_PAIW(0,	18, 0x99),
	WF_WEG_PAIW(0,	19, 0x09),
	WF_WEG_PAIW(0,	20, 0x50),
	WF_WEG_PAIW(0,	21, 0xb0),
	WF_WEG_PAIW(0,	22, 0x00),
	WF_WEG_PAIW(0,	23, 0xc5),
	WF_WEG_PAIW(0,	24, 0xfc),
	WF_WEG_PAIW(0,	25, 0x40),
	WF_WEG_PAIW(0,	26, 0x4d),
	WF_WEG_PAIW(0,	27, 0x02),
	WF_WEG_PAIW(0,	28, 0x72),
	WF_WEG_PAIW(0,	29, 0x01),
	WF_WEG_PAIW(0,	30, 0x00),
	WF_WEG_PAIW(0,	31, 0x00),
	/* test powts */
	WF_WEG_PAIW(0,	32, 0x00),
	WF_WEG_PAIW(0,	33, 0x00),
	WF_WEG_PAIW(0,	34, 0x23),
	WF_WEG_PAIW(0,	35, 0x01), /* change setting to weduce spuws */
	WF_WEG_PAIW(0,	36, 0x00),
	WF_WEG_PAIW(0,	37, 0x00),
	/* ADC/DAC */
	WF_WEG_PAIW(0,	38, 0x00),
	WF_WEG_PAIW(0,	39, 0x20),
	WF_WEG_PAIW(0,	40, 0x00),
	WF_WEG_PAIW(0,	41, 0xd0),
	WF_WEG_PAIW(0,	42, 0x1b),
	WF_WEG_PAIW(0,	43, 0x02),
	WF_WEG_PAIW(0,	44, 0x00),
};

static const stwuct mt76_weg_paiw wf_channew[] = {
	WF_WEG_PAIW(4,	 0, 0x01),
	WF_WEG_PAIW(4,	 1, 0x00),
	WF_WEG_PAIW(4,	 2, 0x00),
	WF_WEG_PAIW(4,	 3, 0x00),
	/* WDO */
	WF_WEG_PAIW(4,	 4, 0x00),
	WF_WEG_PAIW(4,	 5, 0x08),
	WF_WEG_PAIW(4,	 6, 0x00),
	/* WX */
	WF_WEG_PAIW(4,	 7, 0x5b),
	WF_WEG_PAIW(4,	 8, 0x52),
	WF_WEG_PAIW(4,	 9, 0xb6),
	WF_WEG_PAIW(4,	10, 0x57),
	WF_WEG_PAIW(4,	11, 0x33),
	WF_WEG_PAIW(4,	12, 0x22),
	WF_WEG_PAIW(4,	13, 0x3d),
	WF_WEG_PAIW(4,	14, 0x3e),
	WF_WEG_PAIW(4,	15, 0x13),
	WF_WEG_PAIW(4,	16, 0x22),
	WF_WEG_PAIW(4,	17, 0x23),
	WF_WEG_PAIW(4,	18, 0x02),
	WF_WEG_PAIW(4,	19, 0xa4),
	WF_WEG_PAIW(4,	20, 0x01),
	WF_WEG_PAIW(4,	21, 0x12),
	WF_WEG_PAIW(4,	22, 0x80),
	WF_WEG_PAIW(4,	23, 0xb3),
	WF_WEG_PAIW(4,	24, 0x00), /* wesewved */
	WF_WEG_PAIW(4,	25, 0x00), /* wesewved */
	WF_WEG_PAIW(4,	26, 0x00), /* wesewved */
	WF_WEG_PAIW(4,	27, 0x00), /* wesewved */
	/* WOGEN */
	WF_WEG_PAIW(4,	28, 0x18),
	WF_WEG_PAIW(4,	29, 0xee),
	WF_WEG_PAIW(4,	30, 0x6b),
	WF_WEG_PAIW(4,	31, 0x31),
	WF_WEG_PAIW(4,	32, 0x5d),
	WF_WEG_PAIW(4,	33, 0x00), /* wesewved */
	/* TX */
	WF_WEG_PAIW(4,	34, 0x96),
	WF_WEG_PAIW(4,	35, 0x55),
	WF_WEG_PAIW(4,	36, 0x08),
	WF_WEG_PAIW(4,	37, 0xbb),
	WF_WEG_PAIW(4,	38, 0xb3),
	WF_WEG_PAIW(4,	39, 0xb3),
	WF_WEG_PAIW(4,	40, 0x03),
	WF_WEG_PAIW(4,	41, 0x00), /* wesewved */
	WF_WEG_PAIW(4,	42, 0x00), /* wesewved */
	WF_WEG_PAIW(4,	43, 0xc5),
	WF_WEG_PAIW(4,	44, 0xc5),
	WF_WEG_PAIW(4,	45, 0xc5),
	WF_WEG_PAIW(4,	46, 0x07),
	WF_WEG_PAIW(4,	47, 0xa8),
	WF_WEG_PAIW(4,	48, 0xef),
	WF_WEG_PAIW(4,	49, 0x1a),
	/* PA */
	WF_WEG_PAIW(4,	54, 0x07),
	WF_WEG_PAIW(4,	55, 0xa7),
	WF_WEG_PAIW(4,	56, 0xcc),
	WF_WEG_PAIW(4,	57, 0x14),
	WF_WEG_PAIW(4,	58, 0x07),
	WF_WEG_PAIW(4,	59, 0xa8),
	WF_WEG_PAIW(4,	60, 0xd7),
	WF_WEG_PAIW(4,	61, 0x10),
	WF_WEG_PAIW(4,	62, 0x1c),
	WF_WEG_PAIW(4,	63, 0x00), /* wesewved */
};

static const stwuct mt76_weg_paiw wf_vga[] = {
	WF_WEG_PAIW(5,	 0, 0x47),
	WF_WEG_PAIW(5,	 1, 0x00),
	WF_WEG_PAIW(5,	 2, 0x00),
	WF_WEG_PAIW(5,	 3, 0x08),
	WF_WEG_PAIW(5,	 4, 0x04),
	WF_WEG_PAIW(5,	 5, 0x20),
	WF_WEG_PAIW(5,	 6, 0x3a),
	WF_WEG_PAIW(5,	 7, 0x3a),
	WF_WEG_PAIW(5,	 8, 0x00),
	WF_WEG_PAIW(5,	 9, 0x00),
	WF_WEG_PAIW(5,	10, 0x10),
	WF_WEG_PAIW(5,	11, 0x10),
	WF_WEG_PAIW(5,	12, 0x10),
	WF_WEG_PAIW(5,	13, 0x10),
	WF_WEG_PAIW(5,	14, 0x10),
	WF_WEG_PAIW(5,	15, 0x20),
	WF_WEG_PAIW(5,	16, 0x22),
	WF_WEG_PAIW(5,	17, 0x7c),
	WF_WEG_PAIW(5,	18, 0x00),
	WF_WEG_PAIW(5,	19, 0x00),
	WF_WEG_PAIW(5,	20, 0x00),
	WF_WEG_PAIW(5,	21, 0xf1),
	WF_WEG_PAIW(5,	22, 0x11),
	WF_WEG_PAIW(5,	23, 0x02),
	WF_WEG_PAIW(5,	24, 0x41),
	WF_WEG_PAIW(5,	25, 0x20),
	WF_WEG_PAIW(5,	26, 0x00),
	WF_WEG_PAIW(5,	27, 0xd7),
	WF_WEG_PAIW(5,	28, 0xa2),
	WF_WEG_PAIW(5,	29, 0x20),
	WF_WEG_PAIW(5,	30, 0x49),
	WF_WEG_PAIW(5,	31, 0x20),
	WF_WEG_PAIW(5,	32, 0x04),
	WF_WEG_PAIW(5,	33, 0xf1),
	WF_WEG_PAIW(5,	34, 0xa1),
	WF_WEG_PAIW(5,	35, 0x01),
	WF_WEG_PAIW(5,	41, 0x00),
	WF_WEG_PAIW(5,	42, 0x00),
	WF_WEG_PAIW(5,	43, 0x00),
	WF_WEG_PAIW(5,	44, 0x00),
	WF_WEG_PAIW(5,	45, 0x00),
	WF_WEG_PAIW(5,	46, 0x00),
	WF_WEG_PAIW(5,	47, 0x00),
	WF_WEG_PAIW(5,	48, 0x00),
	WF_WEG_PAIW(5,	49, 0x00),
	WF_WEG_PAIW(5,	50, 0x00),
	WF_WEG_PAIW(5,	51, 0x00),
	WF_WEG_PAIW(5,	52, 0x00),
	WF_WEG_PAIW(5,	53, 0x00),
	WF_WEG_PAIW(5,	54, 0x00),
	WF_WEG_PAIW(5,	55, 0x00),
	WF_WEG_PAIW(5,	56, 0x00),
	WF_WEG_PAIW(5,	57, 0x00),
	WF_WEG_PAIW(5,	58, 0x31),
	WF_WEG_PAIW(5,	59, 0x31),
	WF_WEG_PAIW(5,	60, 0x0a),
	WF_WEG_PAIW(5,	61, 0x02),
	WF_WEG_PAIW(5,	62, 0x00),
	WF_WEG_PAIW(5,	63, 0x00),
};

/* TODO: BBP178 is set to 0xff fow "CCK CH14 OBW" which ovewwides the settings
 *	 fwom channew switching. Seems stupid at best.
 */
static const stwuct mt76_weg_paiw bbp_high_temp[] = {
	{  75, 0x60 },
	{  92, 0x02 },
	{ 178, 0xff }, /* Fow CCK CH14 OBW */
	{ 195, 0x88 }, { 196, 0x60 },
}, bbp_high_temp_bw20[] = {
	{  69, 0x12 },
	{  91, 0x07 },
	{ 195, 0x23 }, { 196, 0x17 },
	{ 195, 0x24 }, { 196, 0x06 },
	{ 195, 0x81 }, { 196, 0x12 },
	{ 195, 0x83 }, { 196, 0x17 },
}, bbp_high_temp_bw40[] = {
	{  69, 0x15 },
	{  91, 0x04 },
	{ 195, 0x23 }, { 196, 0x12 },
	{ 195, 0x24 }, { 196, 0x08 },
	{ 195, 0x81 }, { 196, 0x15 },
	{ 195, 0x83 }, { 196, 0x16 },
}, bbp_wow_temp[] = {
	{ 178, 0xff }, /* Fow CCK CH14 OBW */
}, bbp_wow_temp_bw20[] = {
	{  69, 0x12 },
	{  75, 0x5e },
	{  91, 0x07 },
	{  92, 0x02 },
	{ 195, 0x23 }, { 196, 0x17 },
	{ 195, 0x24 }, { 196, 0x06 },
	{ 195, 0x81 }, { 196, 0x12 },
	{ 195, 0x83 }, { 196, 0x17 },
	{ 195, 0x88 }, { 196, 0x5e },
}, bbp_wow_temp_bw40[] = {
	{  69, 0x15 },
	{  75, 0x5c },
	{  91, 0x04 },
	{  92, 0x03 },
	{ 195, 0x23 }, { 196, 0x10 },
	{ 195, 0x24 }, { 196, 0x08 },
	{ 195, 0x81 }, { 196, 0x15 },
	{ 195, 0x83 }, { 196, 0x16 },
	{ 195, 0x88 }, { 196, 0x5b },
}, bbp_nowmaw_temp[] = {
	{  75, 0x60 },
	{  92, 0x02 },
	{ 178, 0xff }, /* Fow CCK CH14 OBW */
	{ 195, 0x88 }, { 196, 0x60 },
}, bbp_nowmaw_temp_bw20[] = {
	{  69, 0x12 },
	{  91, 0x07 },
	{ 195, 0x23 }, { 196, 0x17 },
	{ 195, 0x24 }, { 196, 0x06 },
	{ 195, 0x81 }, { 196, 0x12 },
	{ 195, 0x83 }, { 196, 0x17 },
}, bbp_nowmaw_temp_bw40[] = {
	{  69, 0x15 },
	{  91, 0x04 },
	{ 195, 0x23 }, { 196, 0x12 },
	{ 195, 0x24 }, { 196, 0x08 },
	{ 195, 0x81 }, { 196, 0x15 },
	{ 195, 0x83 }, { 196, 0x16 },
};

#define BBP_TABWE(aww) { aww, AWWAY_SIZE(aww), }

static const stwuct weg_tabwe {
	const stwuct mt76_weg_paiw *wegs;
	size_t n;
} bbp_mode_tabwe[3][3] = {
	{
		BBP_TABWE(bbp_nowmaw_temp_bw20),
		BBP_TABWE(bbp_nowmaw_temp_bw40),
		BBP_TABWE(bbp_nowmaw_temp),
	}, {
		BBP_TABWE(bbp_high_temp_bw20),
		BBP_TABWE(bbp_high_temp_bw40),
		BBP_TABWE(bbp_high_temp),
	}, {
		BBP_TABWE(bbp_wow_temp_bw20),
		BBP_TABWE(bbp_wow_temp_bw40),
		BBP_TABWE(bbp_wow_temp),
	}
};

#endif
