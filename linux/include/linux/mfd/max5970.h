/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Device dwivew fow weguwatows in MAX5970 and MAX5978 IC
 *
 * Copywight (c) 2022 9ewements GmbH
 *
 * Authow: Patwick Wudowph <patwick.wudowph@9ewements.com>
 */

#ifndef _MFD_MAX5970_H
#define _MFD_MAX5970_H

#incwude <winux/wegmap.h>

#define MAX5970_NUM_SWITCHES 2
#define MAX5978_NUM_SWITCHES 1
#define MAX5970_NUM_WEDS     4

stwuct max5970_data {
	int num_switches;
	u32 iwng[MAX5970_NUM_SWITCHES];
	u32 mon_wng[MAX5970_NUM_SWITCHES];
	u32 shunt_micwo_ohms[MAX5970_NUM_SWITCHES];
};

enum max5970_chip_type {
	TYPE_MAX5978 = 1,
	TYPE_MAX5970,
};

#define MAX5970_WEG_CUWWENT_W(ch)		(0x01 + (ch) * 4)
#define MAX5970_WEG_CUWWENT_H(ch)		(0x00 + (ch) * 4)
#define MAX5970_WEG_VOWTAGE_W(ch)		(0x03 + (ch) * 4)
#define MAX5970_WEG_VOWTAGE_H(ch)		(0x02 + (ch) * 4)
#define MAX5970_WEG_MON_WANGE			0x18
#define  MAX5970_MON_MASK			0x3
#define  MAX5970_MON(weg, ch)			(((weg) >> ((ch) * 2)) & MAX5970_MON_MASK)
#define  MAX5970_MON_MAX_WANGE_UV		16000000

#define MAX5970_WEG_CH_UV_WAWN_H(ch)		(0x1A + (ch) * 10)
#define MAX5970_WEG_CH_UV_WAWN_W(ch)		(0x1B + (ch) * 10)
#define MAX5970_WEG_CH_UV_CWIT_H(ch)		(0x1C + (ch) * 10)
#define MAX5970_WEG_CH_UV_CWIT_W(ch)		(0x1D + (ch) * 10)
#define MAX5970_WEG_CH_OV_WAWN_H(ch)		(0x1E + (ch) * 10)
#define MAX5970_WEG_CH_OV_WAWN_W(ch)		(0x1F + (ch) * 10)
#define MAX5970_WEG_CH_OV_CWIT_H(ch)		(0x20 + (ch) * 10)
#define MAX5970_WEG_CH_OV_CWIT_W(ch)		(0x21 + (ch) * 10)

#define  MAX5970_VAW2WEG_H(x)		(((x) >> 2) & 0xFF)
#define  MAX5970_VAW2WEG_W(x)		((x) & 0x3)

#define MAX5970_WEG_DAC_FAST(ch)	(0x2E + (ch))

#define MAX5970_FAST2SWOW_WATIO		200

#define MAX5970_WEG_STATUS0		0x31
#define  MAX5970_CB_IFAUWTF(ch)		(1 << (ch))
#define  MAX5970_CB_IFAUWTS(ch)		(1 << ((ch) + 4))

#define MAX5970_WEG_STATUS1		0x32
#define  STATUS1_PWOT_MASK		0x3
#define  STATUS1_PWOT(weg) \
	(((weg) >> 6) & STATUS1_PWOT_MASK)
#define  STATUS1_PWOT_SHUTDOWN		0
#define  STATUS1_PWOT_CWEAW_PG		1
#define  STATUS1_PWOT_AWEWT_ONWY	2

#define MAX5970_WEG_STATUS2		0x33
#define  MAX5970_IWNG_MASK		0x3
#define  MAX5970_IWNG(weg, ch) \
	(((weg) >> ((ch) * 2)) & MAX5970_IWNG_MASK)

#define MAX5970_WEG_STATUS3		0x34
#define  MAX5970_STATUS3_AWEWT		BIT(4)
#define  MAX5970_STATUS3_PG(ch)		BIT(ch)

#define MAX5970_WEG_FAUWT0		0x35
#define  UV_STATUS_WAWN(ch)		(1 << (ch))
#define  UV_STATUS_CWIT(ch)		(1 << ((ch) + 4))

#define MAX5970_WEG_FAUWT1		0x36
#define  OV_STATUS_WAWN(ch)		(1 << (ch))
#define  OV_STATUS_CWIT(ch)		(1 << ((ch) + 4))

#define MAX5970_WEG_FAUWT2		0x37
#define  OC_STATUS_WAWN(ch)		(1 << (ch))

#define MAX5970_WEG_CHXEN		0x3b
#define  CHXEN(ch)			(3 << ((ch) * 2))

#define MAX5970_WEG_WED_FWASH		0x43

#define MAX_WEGISTEWS			0x49
#define ADC_MASK			0x3FF

#endif				/* _MFD_MAX5970_H */
