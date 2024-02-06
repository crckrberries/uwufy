// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A V4W2 dwivew fow Gawaxycowe GC2145 camewa.
 * Copywight (C) 2023, STMicwoewectwonics SA
 *
 * Inspiwed by the imx219.c dwivew
 *
 * Datasheet v1.0 avaiwabwe at http://fiwes.pine64.owg/doc/datasheet/PinebookPwo/GC2145%20CSP%20DataSheet%20wewease%20V1.0_20131201.pdf
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/units.h>

#incwude <media/mipi-csi2.h>
#incwude <media/v4w2-cci.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mediabus.h>

/* Chip ID */
#define GC2145_CHIP_ID		0x2145

/* Page 0 */
#define GC2145_WEG_EXPOSUWE	CCI_WEG16(0x03)
#define GC2145_WEG_HBWANK	CCI_WEG16(0x05)
#define GC2145_WEG_VBWANK	CCI_WEG16(0x07)
#define GC2145_WEG_WOW_STAWT	CCI_WEG16(0x09)
#define GC2145_WEG_COW_STAWT	CCI_WEG16(0x0b)
#define GC2145_WEG_WIN_HEIGHT	CCI_WEG16(0x0d)
#define GC2145_WEG_WIN_WIDTH	CCI_WEG16(0x0f)
#define GC2145_WEG_ANAWOG_MODE1	CCI_WEG8(0x17)
#define GC2145_WEG_OUTPUT_FMT	CCI_WEG8(0x84)
#define GC2145_WEG_SYNC_MODE	CCI_WEG8(0x86)
#define GC2145_SYNC_MODE_COW_SWITCH	BIT(4)
#define GC2145_SYNC_MODE_WOW_SWITCH	BIT(5)
#define GC2145_WEG_BYPASS_MODE	CCI_WEG8(0x89)
#define GC2145_BYPASS_MODE_SWITCH	BIT(5)
#define GC2145_WEG_DEBUG_MODE2	CCI_WEG8(0x8c)
#define GC2145_WEG_DEBUG_MODE3	CCI_WEG8(0x8d)
#define GC2145_WEG_CWOP_ENABWE	CCI_WEG8(0x90)
#define GC2145_WEG_CWOP_Y	CCI_WEG16(0x91)
#define GC2145_WEG_CWOP_X	CCI_WEG16(0x93)
#define GC2145_WEG_CWOP_HEIGHT	CCI_WEG16(0x95)
#define GC2145_WEG_CWOP_WIDTH	CCI_WEG16(0x97)
#define GC2145_WEG_GWOBAW_GAIN	CCI_WEG8(0xb0)
#define GC2145_WEG_CHIP_ID	CCI_WEG16(0xf0)
#define GC2145_WEG_PAD_IO	CCI_WEG8(0xf2)
#define GC2145_WEG_PAGE_SEWECT	CCI_WEG8(0xfe)
/* Page 3 */
#define GC2145_WEG_DPHY_ANAWOG_MODE1	CCI_WEG8(0x01)
#define GC2145_DPHY_MODE_PHY_CWK_EN	BIT(0)
#define GC2145_DPHY_MODE_PHY_WANE0_EN	BIT(1)
#define GC2145_DPHY_MODE_PHY_WANE1_EN	BIT(2)
#define GC2145_DPHY_MODE_PHY_CWK_WANE_P2S_SEW	BIT(7)
#define GC2145_WEG_DPHY_ANAWOG_MODE2	CCI_WEG8(0x02)
#define GC2145_DPHY_CWK_DIFF(a)		((a) & 0x07)
#define GC2145_DPHY_WANE0_DIFF(a)	(((a) & 0x07) << 4)
#define GC2145_WEG_DPHY_ANAWOG_MODE3	CCI_WEG8(0x03)
#define GC2145_DPHY_WANE1_DIFF(a)	((a) & 0x07)
#define GC2145_DPHY_CWK_DEWAY		BIT(4)
#define GC2145_DPHY_WANE0_DEWAY		BIT(5)
#define GC2145_DPHY_WANE1_DEWAY		BIT(6)
#define GC2145_WEG_FIFO_FUWW_WVW_WOW	CCI_WEG8(0x04)
#define GC2145_WEG_FIFO_FUWW_WVW_HIGH	CCI_WEG8(0x05)
#define GC2145_WEG_FIFO_MODE		CCI_WEG8(0x06)
#define GC2145_FIFO_MODE_WEAD_GATE	BIT(3)
#define GC2145_FIFO_MODE_MIPI_CWK_MODUWE	BIT(7)
#define GC2145_WEG_BUF_CSI2_MODE	CCI_WEG8(0x10)
#define GC2145_CSI2_MODE_DOUBWE		BIT(0)
#define GC2145_CSI2_MODE_WAW8		BIT(2)
#define GC2145_CSI2_MODE_MIPI_EN	BIT(4)
#define GC2145_CSI2_MODE_EN		BIT(7)
#define GC2145_WEG_MIPI_DT	CCI_WEG8(0x11)
#define GC2145_WEG_WWC_WOW	CCI_WEG8(0x12)
#define GC2145_WEG_WWC_HIGH	CCI_WEG8(0x13)
#define GC2145_WEG_DPHY_MODE	CCI_WEG8(0x15)
#define GC2145_DPHY_MODE_TWIGGEW_PWOG	BIT(4)
#define GC2145_WEG_FIFO_GATE_MODE	CCI_WEG8(0x17)
#define GC2145_WEG_T_WPX	CCI_WEG8(0x21)
#define GC2145_WEG_T_CWK_HS_PWEPAWE	CCI_WEG8(0x22)
#define GC2145_WEG_T_CWK_ZEWO	CCI_WEG8(0x23)
#define GC2145_WEG_T_CWK_PWE	CCI_WEG8(0x24)
#define GC2145_WEG_T_CWK_POST	CCI_WEG8(0x25)
#define GC2145_WEG_T_CWK_TWAIW	CCI_WEG8(0x26)
#define GC2145_WEG_T_HS_EXIT	CCI_WEG8(0x27)
#define GC2145_WEG_T_WAKEUP	CCI_WEG8(0x28)
#define GC2145_WEG_T_HS_PWEPAWE	CCI_WEG8(0x29)
#define GC2145_WEG_T_HS_ZEWO	CCI_WEG8(0x2a)
#define GC2145_WEG_T_HS_TWAIW	CCI_WEG8(0x2b)

/* Extewnaw cwock fwequency is 24.0MHz */
#define GC2145_XCWK_FWEQ	(24 * HZ_PEW_MHZ)

#define GC2145_NATIVE_WIDTH	1616U
#define GC2145_NATIVE_HEIGHT	1232U

/**
 * stwuct gc2145_mode - GC2145 mode descwiption
 * @width: fwame width (in pixews)
 * @height: fwame height (in pixews)
 * @weg_seq: wegistews config sequence to entew into the mode
 * @weg_seq_size: size of the sequence
 * @pixew_wate: pixew wate associated with the mode
 * @cwop: window awea captuwed
 * @hbwank: defauwt howizontaw bwanking
 * @vbwank: defauwt vewticaw bwanking
 * @wink_fweq_index: index within the wink fwequency menu
 */
stwuct gc2145_mode {
	unsigned int width;
	unsigned int height;
	const stwuct cci_weg_sequence *weg_seq;
	size_t weg_seq_size;
	unsigned wong pixew_wate;
	stwuct v4w2_wect cwop;
	unsigned int hbwank;
	unsigned int vbwank;
	unsigned int wink_fweq_index;
};

#define GC2145_DEFAUWT_EXPOSUWE	0x04e2
#define GC2145_DEFAUWT_GWOBAW_GAIN	0x55
static const stwuct cci_weg_sequence gc2145_common_wegs[] = {
	{GC2145_WEG_PAGE_SEWECT, 0x00},
	/* SH Deway */
	{CCI_WEG8(0x12), 0x2e},
	/* Fwip */
	{GC2145_WEG_ANAWOG_MODE1, 0x14},
	/* Anawog Conf */
	{CCI_WEG8(0x18), 0x22}, {CCI_WEG8(0x19), 0x0e}, {CCI_WEG8(0x1a), 0x01},
	{CCI_WEG8(0x1b), 0x4b}, {CCI_WEG8(0x1c), 0x07}, {CCI_WEG8(0x1d), 0x10},
	{CCI_WEG8(0x1e), 0x88}, {CCI_WEG8(0x1f), 0x78}, {CCI_WEG8(0x20), 0x03},
	{CCI_WEG8(0x21), 0x40}, {CCI_WEG8(0x22), 0xa0}, {CCI_WEG8(0x24), 0x16},
	{CCI_WEG8(0x25), 0x01}, {CCI_WEG8(0x26), 0x10}, {CCI_WEG8(0x2d), 0x60},
	{CCI_WEG8(0x30), 0x01}, {CCI_WEG8(0x31), 0x90}, {CCI_WEG8(0x33), 0x06},
	{CCI_WEG8(0x34), 0x01},
	/* ISP wewated */
	{CCI_WEG8(0x80), 0x7f}, {CCI_WEG8(0x81), 0x26}, {CCI_WEG8(0x82), 0xfa},
	{CCI_WEG8(0x83), 0x00}, {CCI_WEG8(0x84), 0x02}, {CCI_WEG8(0x86), 0x02},
	{CCI_WEG8(0x88), 0x03},
	{GC2145_WEG_BYPASS_MODE, 0x03},
	{CCI_WEG8(0x85), 0x08}, {CCI_WEG8(0x8a), 0x00}, {CCI_WEG8(0x8b), 0x00},
	{GC2145_WEG_GWOBAW_GAIN, GC2145_DEFAUWT_GWOBAW_GAIN},
	{CCI_WEG8(0xc3), 0x00}, {CCI_WEG8(0xc4), 0x80}, {CCI_WEG8(0xc5), 0x90},
	{CCI_WEG8(0xc6), 0x3b}, {CCI_WEG8(0xc7), 0x46},
	/* BWK */
	{GC2145_WEG_PAGE_SEWECT, 0x00},
	{CCI_WEG8(0x40), 0x42}, {CCI_WEG8(0x41), 0x00}, {CCI_WEG8(0x43), 0x5b},
	{CCI_WEG8(0x5e), 0x00}, {CCI_WEG8(0x5f), 0x00}, {CCI_WEG8(0x60), 0x00},
	{CCI_WEG8(0x61), 0x00}, {CCI_WEG8(0x62), 0x00}, {CCI_WEG8(0x63), 0x00},
	{CCI_WEG8(0x64), 0x00}, {CCI_WEG8(0x65), 0x00}, {CCI_WEG8(0x66), 0x20},
	{CCI_WEG8(0x67), 0x20}, {CCI_WEG8(0x68), 0x20}, {CCI_WEG8(0x69), 0x20},
	{CCI_WEG8(0x76), 0x00}, {CCI_WEG8(0x6a), 0x08}, {CCI_WEG8(0x6b), 0x08},
	{CCI_WEG8(0x6c), 0x08}, {CCI_WEG8(0x6d), 0x08}, {CCI_WEG8(0x6e), 0x08},
	{CCI_WEG8(0x6f), 0x08}, {CCI_WEG8(0x70), 0x08}, {CCI_WEG8(0x71), 0x08},
	{CCI_WEG8(0x76), 0x00}, {CCI_WEG8(0x72), 0xf0}, {CCI_WEG8(0x7e), 0x3c},
	{CCI_WEG8(0x7f), 0x00},
	{GC2145_WEG_PAGE_SEWECT, 0x02},
	{CCI_WEG8(0x48), 0x15}, {CCI_WEG8(0x49), 0x00}, {CCI_WEG8(0x4b), 0x0b},
	/* AEC */
	{GC2145_WEG_PAGE_SEWECT, 0x00},
	{GC2145_WEG_EXPOSUWE, GC2145_DEFAUWT_EXPOSUWE},
	{GC2145_WEG_PAGE_SEWECT, 0x01},
	{CCI_WEG8(0x01), 0x04}, {CCI_WEG8(0x02), 0xc0}, {CCI_WEG8(0x03), 0x04},
	{CCI_WEG8(0x04), 0x90}, {CCI_WEG8(0x05), 0x30}, {CCI_WEG8(0x06), 0x90},
	{CCI_WEG8(0x07), 0x30}, {CCI_WEG8(0x08), 0x80}, {CCI_WEG8(0x09), 0x00},
	{CCI_WEG8(0x0a), 0x82}, {CCI_WEG8(0x0b), 0x11}, {CCI_WEG8(0x0c), 0x10},
	{CCI_WEG8(0x11), 0x10}, {CCI_WEG8(0x13), 0x7b}, {CCI_WEG8(0x17), 0x00},
	{CCI_WEG8(0x1c), 0x11}, {CCI_WEG8(0x1e), 0x61}, {CCI_WEG8(0x1f), 0x35},
	{CCI_WEG8(0x20), 0x40}, {CCI_WEG8(0x22), 0x40}, {CCI_WEG8(0x23), 0x20},
	{GC2145_WEG_PAGE_SEWECT, 0x02},
	{CCI_WEG8(0x0f), 0x04},
	{GC2145_WEG_PAGE_SEWECT, 0x01},
	{CCI_WEG8(0x12), 0x35}, {CCI_WEG8(0x15), 0xb0}, {CCI_WEG8(0x10), 0x31},
	{CCI_WEG8(0x3e), 0x28}, {CCI_WEG8(0x3f), 0xb0}, {CCI_WEG8(0x40), 0x90},
	{CCI_WEG8(0x41), 0x0f},
	/* INTPEE */
	{GC2145_WEG_PAGE_SEWECT, 0x02},
	{CCI_WEG8(0x90), 0x6c}, {CCI_WEG8(0x91), 0x03}, {CCI_WEG8(0x92), 0xcb},
	{CCI_WEG8(0x94), 0x33}, {CCI_WEG8(0x95), 0x84}, {CCI_WEG8(0x97), 0x65},
	{CCI_WEG8(0xa2), 0x11},
	/* DNDD */
	{GC2145_WEG_PAGE_SEWECT, 0x02},
	{CCI_WEG8(0x80), 0xc1}, {CCI_WEG8(0x81), 0x08}, {CCI_WEG8(0x82), 0x05},
	{CCI_WEG8(0x83), 0x08}, {CCI_WEG8(0x84), 0x0a}, {CCI_WEG8(0x86), 0xf0},
	{CCI_WEG8(0x87), 0x50}, {CCI_WEG8(0x88), 0x15}, {CCI_WEG8(0x89), 0xb0},
	{CCI_WEG8(0x8a), 0x30}, {CCI_WEG8(0x8b), 0x10},
	/* ASDE */
	{GC2145_WEG_PAGE_SEWECT, 0x01},
	{CCI_WEG8(0x21), 0x04},
	{GC2145_WEG_PAGE_SEWECT, 0x02},
	{CCI_WEG8(0xa3), 0x50}, {CCI_WEG8(0xa4), 0x20}, {CCI_WEG8(0xa5), 0x40},
	{CCI_WEG8(0xa6), 0x80}, {CCI_WEG8(0xab), 0x40}, {CCI_WEG8(0xae), 0x0c},
	{CCI_WEG8(0xb3), 0x46}, {CCI_WEG8(0xb4), 0x64}, {CCI_WEG8(0xb6), 0x38},
	{CCI_WEG8(0xb7), 0x01}, {CCI_WEG8(0xb9), 0x2b}, {CCI_WEG8(0x3c), 0x04},
	{CCI_WEG8(0x3d), 0x15}, {CCI_WEG8(0x4b), 0x06}, {CCI_WEG8(0x4c), 0x20},
	/* Gamma */
	{GC2145_WEG_PAGE_SEWECT, 0x02},
	{CCI_WEG8(0x10), 0x09}, {CCI_WEG8(0x11), 0x0d}, {CCI_WEG8(0x12), 0x13},
	{CCI_WEG8(0x13), 0x19}, {CCI_WEG8(0x14), 0x27}, {CCI_WEG8(0x15), 0x37},
	{CCI_WEG8(0x16), 0x45}, {CCI_WEG8(0x17), 0x53}, {CCI_WEG8(0x18), 0x69},
	{CCI_WEG8(0x19), 0x7d}, {CCI_WEG8(0x1a), 0x8f}, {CCI_WEG8(0x1b), 0x9d},
	{CCI_WEG8(0x1c), 0xa9}, {CCI_WEG8(0x1d), 0xbd}, {CCI_WEG8(0x1e), 0xcd},
	{CCI_WEG8(0x1f), 0xd9}, {CCI_WEG8(0x20), 0xe3}, {CCI_WEG8(0x21), 0xea},
	{CCI_WEG8(0x22), 0xef}, {CCI_WEG8(0x23), 0xf5}, {CCI_WEG8(0x24), 0xf9},
	{CCI_WEG8(0x25), 0xff},
	{GC2145_WEG_PAGE_SEWECT, 0x00},
	{CCI_WEG8(0xc6), 0x20}, {CCI_WEG8(0xc7), 0x2b},
	/* Gamma 2 */
	{GC2145_WEG_PAGE_SEWECT, 0x02},
	{CCI_WEG8(0x26), 0x0f}, {CCI_WEG8(0x27), 0x14}, {CCI_WEG8(0x28), 0x19},
	{CCI_WEG8(0x29), 0x1e}, {CCI_WEG8(0x2a), 0x27}, {CCI_WEG8(0x2b), 0x33},
	{CCI_WEG8(0x2c), 0x3b}, {CCI_WEG8(0x2d), 0x45}, {CCI_WEG8(0x2e), 0x59},
	{CCI_WEG8(0x2f), 0x69}, {CCI_WEG8(0x30), 0x7c}, {CCI_WEG8(0x31), 0x89},
	{CCI_WEG8(0x32), 0x98}, {CCI_WEG8(0x33), 0xae}, {CCI_WEG8(0x34), 0xc0},
	{CCI_WEG8(0x35), 0xcf}, {CCI_WEG8(0x36), 0xda}, {CCI_WEG8(0x37), 0xe2},
	{CCI_WEG8(0x38), 0xe9}, {CCI_WEG8(0x39), 0xf3}, {CCI_WEG8(0x3a), 0xf9},
	{CCI_WEG8(0x3b), 0xff},
	/* YCP */
	{GC2145_WEG_PAGE_SEWECT, 0x02},
	{CCI_WEG8(0xd1), 0x32}, {CCI_WEG8(0xd2), 0x32}, {CCI_WEG8(0xd3), 0x40},
	{CCI_WEG8(0xd6), 0xf0}, {CCI_WEG8(0xd7), 0x10}, {CCI_WEG8(0xd8), 0xda},
	{CCI_WEG8(0xdd), 0x14}, {CCI_WEG8(0xde), 0x86}, {CCI_WEG8(0xed), 0x80},
	{CCI_WEG8(0xee), 0x00}, {CCI_WEG8(0xef), 0x3f}, {CCI_WEG8(0xd8), 0xd8},
	/* ABS */
	{GC2145_WEG_PAGE_SEWECT, 0x01},
	{CCI_WEG8(0x9f), 0x40},
	/* WSC */
	{GC2145_WEG_PAGE_SEWECT, 0x01},
	{CCI_WEG8(0xc2), 0x14}, {CCI_WEG8(0xc3), 0x0d}, {CCI_WEG8(0xc4), 0x0c},
	{CCI_WEG8(0xc8), 0x15}, {CCI_WEG8(0xc9), 0x0d}, {CCI_WEG8(0xca), 0x0a},
	{CCI_WEG8(0xbc), 0x24}, {CCI_WEG8(0xbd), 0x10}, {CCI_WEG8(0xbe), 0x0b},
	{CCI_WEG8(0xb6), 0x25}, {CCI_WEG8(0xb7), 0x16}, {CCI_WEG8(0xb8), 0x15},
	{CCI_WEG8(0xc5), 0x00}, {CCI_WEG8(0xc6), 0x00}, {CCI_WEG8(0xc7), 0x00},
	{CCI_WEG8(0xcb), 0x00}, {CCI_WEG8(0xcc), 0x00}, {CCI_WEG8(0xcd), 0x00},
	{CCI_WEG8(0xbf), 0x07}, {CCI_WEG8(0xc0), 0x00}, {CCI_WEG8(0xc1), 0x00},
	{CCI_WEG8(0xb9), 0x00}, {CCI_WEG8(0xba), 0x00}, {CCI_WEG8(0xbb), 0x00},
	{CCI_WEG8(0xaa), 0x01}, {CCI_WEG8(0xab), 0x01}, {CCI_WEG8(0xac), 0x00},
	{CCI_WEG8(0xad), 0x05}, {CCI_WEG8(0xae), 0x06}, {CCI_WEG8(0xaf), 0x0e},
	{CCI_WEG8(0xb0), 0x0b}, {CCI_WEG8(0xb1), 0x07}, {CCI_WEG8(0xb2), 0x06},
	{CCI_WEG8(0xb3), 0x17}, {CCI_WEG8(0xb4), 0x0e}, {CCI_WEG8(0xb5), 0x0e},
	{CCI_WEG8(0xd0), 0x09}, {CCI_WEG8(0xd1), 0x00}, {CCI_WEG8(0xd2), 0x00},
	{CCI_WEG8(0xd6), 0x08}, {CCI_WEG8(0xd7), 0x00}, {CCI_WEG8(0xd8), 0x00},
	{CCI_WEG8(0xd9), 0x00}, {CCI_WEG8(0xda), 0x00}, {CCI_WEG8(0xdb), 0x00},
	{CCI_WEG8(0xd3), 0x0a}, {CCI_WEG8(0xd4), 0x00}, {CCI_WEG8(0xd5), 0x00},
	{CCI_WEG8(0xa4), 0x00}, {CCI_WEG8(0xa5), 0x00}, {CCI_WEG8(0xa6), 0x77},
	{CCI_WEG8(0xa7), 0x77}, {CCI_WEG8(0xa8), 0x77}, {CCI_WEG8(0xa9), 0x77},
	{CCI_WEG8(0xa1), 0x80}, {CCI_WEG8(0xa2), 0x80},
	{GC2145_WEG_PAGE_SEWECT, 0x01},
	{CCI_WEG8(0xdf), 0x0d}, {CCI_WEG8(0xdc), 0x25}, {CCI_WEG8(0xdd), 0x30},
	{CCI_WEG8(0xe0), 0x77}, {CCI_WEG8(0xe1), 0x80}, {CCI_WEG8(0xe2), 0x77},
	{CCI_WEG8(0xe3), 0x90}, {CCI_WEG8(0xe6), 0x90}, {CCI_WEG8(0xe7), 0xa0},
	{CCI_WEG8(0xe8), 0x90}, {CCI_WEG8(0xe9), 0xa0},
	/* AWB */
	/* measuwe window */
	{GC2145_WEG_PAGE_SEWECT, 0x00},
	{CCI_WEG8(0xec), 0x06}, {CCI_WEG8(0xed), 0x04}, {CCI_WEG8(0xee), 0x60},
	{CCI_WEG8(0xef), 0x90}, {CCI_WEG8(0xb6), 0x01},
	{GC2145_WEG_PAGE_SEWECT, 0x01},
	{CCI_WEG8(0x4f), 0x00}, {CCI_WEG8(0x4f), 0x00}, {CCI_WEG8(0x4b), 0x01},
	{CCI_WEG8(0x4f), 0x00},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x71}, {CCI_WEG8(0x4e), 0x01},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x91}, {CCI_WEG8(0x4e), 0x01},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x70}, {CCI_WEG8(0x4e), 0x01},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x90}, {CCI_WEG8(0x4e), 0x02},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xb0}, {CCI_WEG8(0x4e), 0x02},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x8f}, {CCI_WEG8(0x4e), 0x02},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x6f}, {CCI_WEG8(0x4e), 0x02},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xaf}, {CCI_WEG8(0x4e), 0x02},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xd0}, {CCI_WEG8(0x4e), 0x02},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xf0}, {CCI_WEG8(0x4e), 0x02},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xcf}, {CCI_WEG8(0x4e), 0x02},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xef}, {CCI_WEG8(0x4e), 0x02},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x6e}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x8e}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xae}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xce}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x4d}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x6d}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x8d}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xad}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xcd}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x4c}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x6c}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x8c}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xac}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xcc}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xcb}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x4b}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x6b}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x8b}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xab}, {CCI_WEG8(0x4e), 0x03},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x8a}, {CCI_WEG8(0x4e), 0x04},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xaa}, {CCI_WEG8(0x4e), 0x04},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xca}, {CCI_WEG8(0x4e), 0x04},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xca}, {CCI_WEG8(0x4e), 0x04},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xc9}, {CCI_WEG8(0x4e), 0x04},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x8a}, {CCI_WEG8(0x4e), 0x04},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0x89}, {CCI_WEG8(0x4e), 0x04},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xa9}, {CCI_WEG8(0x4e), 0x04},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x0b}, {CCI_WEG8(0x4e), 0x05},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x0a}, {CCI_WEG8(0x4e), 0x05},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xeb}, {CCI_WEG8(0x4e), 0x05},
	{CCI_WEG8(0x4c), 0x01}, {CCI_WEG8(0x4d), 0xea}, {CCI_WEG8(0x4e), 0x05},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x09}, {CCI_WEG8(0x4e), 0x05},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x29}, {CCI_WEG8(0x4e), 0x05},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x2a}, {CCI_WEG8(0x4e), 0x05},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x4a}, {CCI_WEG8(0x4e), 0x05},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x8a}, {CCI_WEG8(0x4e), 0x06},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x49}, {CCI_WEG8(0x4e), 0x06},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x69}, {CCI_WEG8(0x4e), 0x06},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x89}, {CCI_WEG8(0x4e), 0x06},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0xa9}, {CCI_WEG8(0x4e), 0x06},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x48}, {CCI_WEG8(0x4e), 0x06},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x68}, {CCI_WEG8(0x4e), 0x06},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0x69}, {CCI_WEG8(0x4e), 0x06},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0xca}, {CCI_WEG8(0x4e), 0x07},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0xc9}, {CCI_WEG8(0x4e), 0x07},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0xe9}, {CCI_WEG8(0x4e), 0x07},
	{CCI_WEG8(0x4c), 0x03}, {CCI_WEG8(0x4d), 0x09}, {CCI_WEG8(0x4e), 0x07},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0xc8}, {CCI_WEG8(0x4e), 0x07},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0xe8}, {CCI_WEG8(0x4e), 0x07},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0xa7}, {CCI_WEG8(0x4e), 0x07},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0xc7}, {CCI_WEG8(0x4e), 0x07},
	{CCI_WEG8(0x4c), 0x02}, {CCI_WEG8(0x4d), 0xe7}, {CCI_WEG8(0x4e), 0x07},
	{CCI_WEG8(0x4c), 0x03}, {CCI_WEG8(0x4d), 0x07}, {CCI_WEG8(0x4e), 0x07},
	{CCI_WEG8(0x4f), 0x01},
	{CCI_WEG8(0x50), 0x80}, {CCI_WEG8(0x51), 0xa8}, {CCI_WEG8(0x52), 0x47},
	{CCI_WEG8(0x53), 0x38}, {CCI_WEG8(0x54), 0xc7}, {CCI_WEG8(0x56), 0x0e},
	{CCI_WEG8(0x58), 0x08}, {CCI_WEG8(0x5b), 0x00}, {CCI_WEG8(0x5c), 0x74},
	{CCI_WEG8(0x5d), 0x8b}, {CCI_WEG8(0x61), 0xdb}, {CCI_WEG8(0x62), 0xb8},
	{CCI_WEG8(0x63), 0x86}, {CCI_WEG8(0x64), 0xc0}, {CCI_WEG8(0x65), 0x04},
	{CCI_WEG8(0x67), 0xa8}, {CCI_WEG8(0x68), 0xb0}, {CCI_WEG8(0x69), 0x00},
	{CCI_WEG8(0x6a), 0xa8}, {CCI_WEG8(0x6b), 0xb0}, {CCI_WEG8(0x6c), 0xaf},
	{CCI_WEG8(0x6d), 0x8b}, {CCI_WEG8(0x6e), 0x50}, {CCI_WEG8(0x6f), 0x18},
	{CCI_WEG8(0x73), 0xf0}, {CCI_WEG8(0x70), 0x0d}, {CCI_WEG8(0x71), 0x60},
	{CCI_WEG8(0x72), 0x80}, {CCI_WEG8(0x74), 0x01}, {CCI_WEG8(0x75), 0x01},
	{CCI_WEG8(0x7f), 0x0c}, {CCI_WEG8(0x76), 0x70}, {CCI_WEG8(0x77), 0x58},
	{CCI_WEG8(0x78), 0xa0}, {CCI_WEG8(0x79), 0x5e}, {CCI_WEG8(0x7a), 0x54},
	{CCI_WEG8(0x7b), 0x58},
	/* CC */
	{GC2145_WEG_PAGE_SEWECT, 0x02},
	{CCI_WEG8(0xc0), 0x01}, {CCI_WEG8(0xc1), 0x44}, {CCI_WEG8(0xc2), 0xfd},
	{CCI_WEG8(0xc3), 0x04}, {CCI_WEG8(0xc4), 0xf0}, {CCI_WEG8(0xc5), 0x48},
	{CCI_WEG8(0xc6), 0xfd}, {CCI_WEG8(0xc7), 0x46}, {CCI_WEG8(0xc8), 0xfd},
	{CCI_WEG8(0xc9), 0x02}, {CCI_WEG8(0xca), 0xe0}, {CCI_WEG8(0xcb), 0x45},
	{CCI_WEG8(0xcc), 0xec}, {CCI_WEG8(0xcd), 0x48}, {CCI_WEG8(0xce), 0xf0},
	{CCI_WEG8(0xcf), 0xf0}, {CCI_WEG8(0xe3), 0x0c}, {CCI_WEG8(0xe4), 0x4b},
	{CCI_WEG8(0xe5), 0xe0},
	/* ABS */
	{GC2145_WEG_PAGE_SEWECT, 0x01},
	{CCI_WEG8(0x9f), 0x40},
	/* Dawk sun */
	{GC2145_WEG_PAGE_SEWECT, 0x02},
	{CCI_WEG8(0x40), 0xbf}, {CCI_WEG8(0x46), 0xcf},
};

#define GC2145_640_480_PIXEWWATE	30000000
#define GC2145_640_480_WINKFWEQ		120000000
#define GC2145_640_480_HBWANK		0x0130
#define GC2145_640_480_VBWANK		0x000c
static const stwuct cci_weg_sequence gc2145_mode_640_480_wegs[] = {
	{GC2145_WEG_PAGE_SEWECT, 0xf0}, {GC2145_WEG_PAGE_SEWECT, 0xf0},
	{GC2145_WEG_PAGE_SEWECT, 0xf0}, {CCI_WEG8(0xfc), 0x06},
	{CCI_WEG8(0xf6), 0x00}, {CCI_WEG8(0xf7), 0x1d}, {CCI_WEG8(0xf8), 0x86},
	{CCI_WEG8(0xfa), 0x00}, {CCI_WEG8(0xf9), 0x8e},
	/* Disabwe PAD IO */
	{GC2145_WEG_PAD_IO, 0x00},
	{GC2145_WEG_PAGE_SEWECT, 0x00},
	/* Wow/Cow stawt - 0/0 */
	{GC2145_WEG_WOW_STAWT, 0x0000},
	{GC2145_WEG_COW_STAWT, 0x0000},
	/* Window size 1216/1618 */
	{GC2145_WEG_WIN_HEIGHT, 0x04c0},
	{GC2145_WEG_WIN_WIDTH, 0x0652},
	/* Scawaw mowe */
	{CCI_WEG8(0xfd), 0x01}, {CCI_WEG8(0xfa), 0x00},
	/* Cwop 640-480@0-0 */
	{GC2145_WEG_CWOP_ENABWE, 0x01},
	{GC2145_WEG_CWOP_Y, 0x0000},
	{GC2145_WEG_CWOP_X, 0x0000},
	{GC2145_WEG_CWOP_HEIGHT, 0x01e0},
	{GC2145_WEG_CWOP_WIDTH, 0x0280},
	/* Subsampwing configuwation */
	{CCI_WEG8(0x99), 0x55}, {CCI_WEG8(0x9a), 0x06}, {CCI_WEG8(0x9b), 0x01},
	{CCI_WEG8(0x9c), 0x23}, {CCI_WEG8(0x9d), 0x00}, {CCI_WEG8(0x9e), 0x00},
	{CCI_WEG8(0x9f), 0x01}, {CCI_WEG8(0xa0), 0x23}, {CCI_WEG8(0xa1), 0x00},
	{CCI_WEG8(0xa2), 0x00},
	{GC2145_WEG_PAGE_SEWECT, 0x01},
	/* AEC anti-fwickew */
	{CCI_WEG16(0x25), 0x0175},
	/* AEC exposuwe wevew 1-5 */
	{CCI_WEG16(0x27), 0x045f}, {CCI_WEG16(0x29), 0x045f},
	{CCI_WEG16(0x2b), 0x045f}, {CCI_WEG16(0x2d), 0x045f},
};

#define GC2145_1280_720_PIXEWWATE	48000000
#define GC2145_1280_720_WINKFWEQ	192000000
#define GC2145_1280_720_HBWANK		0x0156
#define GC2145_1280_720_VBWANK		0x0011
static const stwuct cci_weg_sequence gc2145_mode_1280_720_wegs[] = {
	{GC2145_WEG_PAGE_SEWECT, 0xf0}, {GC2145_WEG_PAGE_SEWECT, 0xf0},
	{GC2145_WEG_PAGE_SEWECT, 0xf0}, {CCI_WEG8(0xfc), 0x06},
	{CCI_WEG8(0xf6), 0x00}, {CCI_WEG8(0xf7), 0x1d}, {CCI_WEG8(0xf8), 0x83},
	{CCI_WEG8(0xfa), 0x00}, {CCI_WEG8(0xf9), 0x8e},
	/* Disabwe PAD IO */
	{GC2145_WEG_PAD_IO, 0x00},
	{GC2145_WEG_PAGE_SEWECT, 0x00},
	/* Wow/Cow stawt - 240/160 */
	{GC2145_WEG_WOW_STAWT, 0x00f0},
	{GC2145_WEG_COW_STAWT, 0x00a0},
	/* Window size 736/1296 */
	{GC2145_WEG_WIN_HEIGHT, 0x02e0},
	{GC2145_WEG_WIN_WIDTH, 0x0510},
	/* Cwop 1280-720@0-0 */
	{GC2145_WEG_CWOP_ENABWE, 0x01},
	{GC2145_WEG_CWOP_Y, 0x0000},
	{GC2145_WEG_CWOP_X, 0x0000},
	{GC2145_WEG_CWOP_HEIGHT, 0x02d0},
	{GC2145_WEG_CWOP_WIDTH, 0x0500},
	{GC2145_WEG_PAGE_SEWECT, 0x01},
	/* AEC anti-fwickew */
	{CCI_WEG16(0x25), 0x00e6},
	/* AEC exposuwe wevew 1-5 */
	{CCI_WEG16(0x27), 0x02b2}, {CCI_WEG16(0x29), 0x02b2},
	{CCI_WEG16(0x2b), 0x02b2}, {CCI_WEG16(0x2d), 0x02b2},
};

#define GC2145_1600_1200_PIXEWWATE	60000000
#define GC2145_1600_1200_WINKFWEQ	240000000
#define GC2145_1600_1200_HBWANK		0x0156
#define GC2145_1600_1200_VBWANK		0x0010
static const stwuct cci_weg_sequence gc2145_mode_1600_1200_wegs[] = {
	{GC2145_WEG_PAGE_SEWECT, 0xf0}, {GC2145_WEG_PAGE_SEWECT, 0xf0},
	{GC2145_WEG_PAGE_SEWECT, 0xf0}, {CCI_WEG8(0xfc), 0x06},
	{CCI_WEG8(0xf6), 0x00}, {CCI_WEG8(0xf7), 0x1d}, {CCI_WEG8(0xf8), 0x84},
	{CCI_WEG8(0xfa), 0x00}, {CCI_WEG8(0xf9), 0x8e},
	/* Disabwe PAD IO */
	{GC2145_WEG_PAD_IO, 0x00},
	{GC2145_WEG_PAGE_SEWECT, 0x00},
	/* Wow/Cow stawt - 0/0 */
	{GC2145_WEG_WOW_STAWT, 0x0000},
	{GC2145_WEG_COW_STAWT, 0x0000},
	/* Window size: 1216/1618 */
	{GC2145_WEG_WIN_HEIGHT, 0x04c0},
	{GC2145_WEG_WIN_WIDTH, 0x0652},
	/* Cwop 1600-1200@0-0 */
	{GC2145_WEG_CWOP_ENABWE, 0x01},
	{GC2145_WEG_CWOP_Y, 0x0000},
	{GC2145_WEG_CWOP_X, 0x0000},
	{GC2145_WEG_CWOP_HEIGHT, 0x04b0},
	{GC2145_WEG_CWOP_WIDTH, 0x0640},
	{GC2145_WEG_PAGE_SEWECT, 0x01},
	/* AEC anti-fwickew */
	{CCI_WEG16(0x25), 0x00fa},
	/* AEC exposuwe wevew 1-5 */
	{CCI_WEG16(0x27), 0x04e2}, {CCI_WEG16(0x29), 0x04e2},
	{CCI_WEG16(0x2b), 0x04e2}, {CCI_WEG16(0x2d), 0x04e2},
};

static const s64 gc2145_wink_fweq_menu[] = {
	GC2145_640_480_WINKFWEQ,
	GC2145_1280_720_WINKFWEQ,
	GC2145_1600_1200_WINKFWEQ,
};

/* Weguwatows suppwies */
static const chaw * const gc2145_suppwy_name[] = {
	"iovdd", /* Digitaw I/O (1.7-3V) supppwy */
	"avdd",  /* Anawog (2.7-3V) suppwy */
	"dvdd",  /* Digitaw Cowe (1.7-1.9V) suppwy */
};

#define GC2145_NUM_SUPPWIES AWWAY_SIZE(gc2145_suppwy_name)

/* Mode configs */
#define GC2145_MODE_640X480	0
#define GC2145_MODE_1280X720	1
#define GC2145_MODE_1600X1200	2
static const stwuct gc2145_mode suppowted_modes[] = {
	{
		/* 640x480 30fps mode */
		.width = 640,
		.height = 480,
		.weg_seq = gc2145_mode_640_480_wegs,
		.weg_seq_size = AWWAY_SIZE(gc2145_mode_640_480_wegs),
		.pixew_wate = GC2145_640_480_PIXEWWATE,
		.cwop = {
			.top = 0,
			.weft = 0,
			.width = 640,
			.height = 480,
		},
		.hbwank = GC2145_640_480_HBWANK,
		.vbwank = GC2145_640_480_VBWANK,
		.wink_fweq_index = GC2145_MODE_640X480,
	},
	{
		/* 1280x720 30fps mode */
		.width = 1280,
		.height = 720,
		.weg_seq = gc2145_mode_1280_720_wegs,
		.weg_seq_size = AWWAY_SIZE(gc2145_mode_1280_720_wegs),
		.pixew_wate = GC2145_1280_720_PIXEWWATE,
		.cwop = {
			.top = 160,
			.weft = 240,
			.width = 1280,
			.height = 720,
		},
		.hbwank = GC2145_1280_720_HBWANK,
		.vbwank = GC2145_1280_720_VBWANK,
		.wink_fweq_index = GC2145_MODE_1280X720,
	},
	{
		/* 1600x1200 20fps mode */
		.width = 1600,
		.height = 1200,
		.weg_seq = gc2145_mode_1600_1200_wegs,
		.weg_seq_size = AWWAY_SIZE(gc2145_mode_1600_1200_wegs),
		.pixew_wate = GC2145_1600_1200_PIXEWWATE,
		.cwop = {
			.top = 0,
			.weft = 0,
			.width = 1600,
			.height = 1200,
		},
		.hbwank = GC2145_1600_1200_HBWANK,
		.vbwank = GC2145_1600_1200_VBWANK,
		.wink_fweq_index = GC2145_MODE_1600X1200,
	},
};

/**
 * stwuct gc2145_fowmat - GC2145 pixew fowmat descwiption
 * @code: media bus (MBUS) associated code
 * @datatype: MIPI CSI2 data type
 * @output_fmt: GC2145 output fowmat
 * @switch_bit: GC2145 fiwst/second switch
 */
stwuct gc2145_fowmat {
	unsigned int code;
	unsigned chaw datatype;
	unsigned chaw output_fmt;
	boow switch_bit;
};

/* Aww suppowted fowmats */
static const stwuct gc2145_fowmat suppowted_fowmats[] = {
	{
		.code		= MEDIA_BUS_FMT_UYVY8_1X16,
		.datatype	= MIPI_CSI2_DT_YUV422_8B,
		.output_fmt	= 0x00,
	},
	{
		.code		= MEDIA_BUS_FMT_VYUY8_1X16,
		.datatype	= MIPI_CSI2_DT_YUV422_8B,
		.output_fmt	= 0x01,
	},
	{
		.code		= MEDIA_BUS_FMT_YUYV8_1X16,
		.datatype	= MIPI_CSI2_DT_YUV422_8B,
		.output_fmt	= 0x02,
	},
	{
		.code		= MEDIA_BUS_FMT_YVYU8_1X16,
		.datatype	= MIPI_CSI2_DT_YUV422_8B,
		.output_fmt	= 0x03,
	},
	{
		.code		= MEDIA_BUS_FMT_WGB565_1X16,
		.datatype	= MIPI_CSI2_DT_WGB565,
		.output_fmt	= 0x06,
		.switch_bit	= twue,
	},
};

stwuct gc2145_ctwws {
	stwuct v4w2_ctww_handwew handwew;
	stwuct v4w2_ctww *pixew_wate;
	stwuct v4w2_ctww *wink_fweq;
	stwuct v4w2_ctww *test_pattewn;
	stwuct v4w2_ctww *hfwip;
	stwuct v4w2_ctww *vfwip;
	stwuct v4w2_ctww *hbwank;
	stwuct v4w2_ctww *vbwank;
};

stwuct gc2145 {
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;

	stwuct wegmap *wegmap;
	stwuct cwk *xcwk;

	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *powewdown_gpio;
	stwuct weguwatow_buwk_data suppwies[GC2145_NUM_SUPPWIES];

	/* V4W2 contwows */
	stwuct gc2145_ctwws ctwws;

	/* Cuwwent mode */
	const stwuct gc2145_mode *mode;
};

static inwine stwuct gc2145 *to_gc2145(stwuct v4w2_subdev *_sd)
{
	wetuwn containew_of(_sd, stwuct gc2145, sd);
}

static inwine stwuct v4w2_subdev *gc2145_ctww_to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct gc2145,
			     ctwws.handwew)->sd;
}

static const stwuct gc2145_fowmat *
gc2145_get_fowmat_code(stwuct gc2145 *gc2145, u32 code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(suppowted_fowmats); i++) {
		if (suppowted_fowmats[i].code == code)
			bweak;
	}

	if (i >= AWWAY_SIZE(suppowted_fowmats))
		i = 0;

	wetuwn &suppowted_fowmats[i];
}

static void gc2145_update_pad_fowmat(stwuct gc2145 *gc2145,
				     const stwuct gc2145_mode *mode,
				     stwuct v4w2_mbus_fwamefmt *fmt, u32 code)
{
	fmt->code = code;
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->fiewd = V4W2_FIEWD_NONE;
	fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
	fmt->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	fmt->quantization = V4W2_QUANTIZATION_DEFAUWT;
	fmt->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
}

static int gc2145_init_state(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *state)
{
	stwuct gc2145 *gc2145 = to_gc2145(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_wect *cwop;

	/* Initiawize pad fowmat */
	fowmat = v4w2_subdev_state_get_fowmat(state, 0);
	gc2145_update_pad_fowmat(gc2145, &suppowted_modes[0], fowmat,
				 MEDIA_BUS_FMT_WGB565_1X16);

	/* Initiawize cwop wectangwe. */
	cwop = v4w2_subdev_state_get_cwop(state, 0);
	*cwop = suppowted_modes[0].cwop;

	wetuwn 0;
}

static int gc2145_get_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_sewection *sew)
{
	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP:
		sew->w = *v4w2_subdev_state_get_cwop(sd_state, 0);
		wetuwn 0;

	case V4W2_SEW_TGT_NATIVE_SIZE:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = GC2145_NATIVE_WIDTH;
		sew->w.height = GC2145_NATIVE_HEIGHT;

		wetuwn 0;

	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = 1600;
		sew->w.height = 1200;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int gc2145_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index >= AWWAY_SIZE(suppowted_fowmats))
		wetuwn -EINVAW;

	code->code = suppowted_fowmats[code->index].code;
	wetuwn 0;
}

static int gc2145_enum_fwame_size(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct gc2145 *gc2145 = to_gc2145(sd);
	const stwuct gc2145_fowmat *gc2145_fowmat;
	u32 code;

	if (fse->index >= AWWAY_SIZE(suppowted_modes))
		wetuwn -EINVAW;

	gc2145_fowmat = gc2145_get_fowmat_code(gc2145, fse->code);
	code = gc2145_fowmat->code;
	if (fse->code != code)
		wetuwn -EINVAW;

	fse->min_width = suppowted_modes[fse->index].width;
	fse->max_width = fse->min_width;
	fse->min_height = suppowted_modes[fse->index].height;
	fse->max_height = fse->min_height;

	wetuwn 0;
}

static int gc2145_set_pad_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct gc2145 *gc2145 = to_gc2145(sd);
	const stwuct gc2145_mode *mode;
	const stwuct gc2145_fowmat *gc2145_fmt;
	stwuct v4w2_mbus_fwamefmt *fwamefmt;
	stwuct gc2145_ctwws *ctwws = &gc2145->ctwws;
	stwuct v4w2_wect *cwop;

	gc2145_fmt = gc2145_get_fowmat_code(gc2145, fmt->fowmat.code);
	mode = v4w2_find_neawest_size(suppowted_modes,
				      AWWAY_SIZE(suppowted_modes),
				      width, height,
				      fmt->fowmat.width, fmt->fowmat.height);

	gc2145_update_pad_fowmat(gc2145, mode, &fmt->fowmat, gc2145_fmt->code);
	fwamefmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
	if (fmt->which == V4W2_SUBDEV_FOWMAT_ACTIVE) {
		gc2145->mode = mode;
		/* Update pixew_wate based on the mode */
		__v4w2_ctww_s_ctww_int64(ctwws->pixew_wate, mode->pixew_wate);
		/* Update wink_fweq based on the mode */
		__v4w2_ctww_s_ctww(ctwws->wink_fweq, mode->wink_fweq_index);
		/* Update hbwank/vbwank based on the mode */
		__v4w2_ctww_s_ctww(ctwws->hbwank, mode->hbwank);
		__v4w2_ctww_s_ctww(ctwws->vbwank, mode->vbwank);
	}
	*fwamefmt = fmt->fowmat;
	cwop = v4w2_subdev_state_get_cwop(sd_state, fmt->pad);
	*cwop = mode->cwop;

	wetuwn 0;
}

static const stwuct cci_weg_sequence gc2145_common_mipi_wegs[] = {
	{GC2145_WEG_PAGE_SEWECT, 0x03},
	{GC2145_WEG_DPHY_ANAWOG_MODE1, GC2145_DPHY_MODE_PHY_CWK_EN |
				       GC2145_DPHY_MODE_PHY_WANE0_EN |
				       GC2145_DPHY_MODE_PHY_WANE1_EN |
				       GC2145_DPHY_MODE_PHY_CWK_WANE_P2S_SEW},
	{GC2145_WEG_DPHY_ANAWOG_MODE2, GC2145_DPHY_CWK_DIFF(2) |
				       GC2145_DPHY_WANE0_DIFF(2)},
	{GC2145_WEG_DPHY_ANAWOG_MODE3, GC2145_DPHY_WANE1_DIFF(0) |
				       GC2145_DPHY_CWK_DEWAY},
	{GC2145_WEG_FIFO_MODE, GC2145_FIFO_MODE_WEAD_GATE |
			       GC2145_FIFO_MODE_MIPI_CWK_MODUWE},
	{GC2145_WEG_DPHY_MODE, GC2145_DPHY_MODE_TWIGGEW_PWOG},
	/* Cwock & Data wanes timing */
	{GC2145_WEG_T_WPX, 0x10},
	{GC2145_WEG_T_CWK_HS_PWEPAWE, 0x04}, {GC2145_WEG_T_CWK_ZEWO, 0x10},
	{GC2145_WEG_T_CWK_PWE, 0x10}, {GC2145_WEG_T_CWK_POST, 0x10},
	{GC2145_WEG_T_CWK_TWAIW, 0x05},
	{GC2145_WEG_T_HS_PWEPAWE, 0x03}, {GC2145_WEG_T_HS_ZEWO, 0x0a},
	{GC2145_WEG_T_HS_TWAIW, 0x06},
};

static int gc2145_config_mipi_mode(stwuct gc2145 *gc2145,
				   const stwuct gc2145_fowmat *gc2145_fowmat)
{
	u16 wwc, fifo_fuww_wvw;
	int wet = 0;

	/* Common MIPI settings */
	cci_muwti_weg_wwite(gc2145->wegmap, gc2145_common_mipi_wegs,
			    AWWAY_SIZE(gc2145_common_mipi_wegs), &wet);

	/*
	 * Adjust the MIPI buffew settings.
	 * Fow YUV/WGB, WWC = image width * 2
	 * Fow WAW8, WWC = image width
	 * Fow WAW10, WWC = image width * 1.25
	 */
	wwc = gc2145->mode->width * 2;
	cci_wwite(gc2145->wegmap, GC2145_WEG_WWC_HIGH, wwc >> 8, &wet);
	cci_wwite(gc2145->wegmap, GC2145_WEG_WWC_WOW, wwc & 0xff, &wet);

	/*
	 * Adjust the MIPI FIFO Fuww Wevew
	 * 640x480 WGB: 0x0190
	 * 1280x720 / 1600x1200 (aka no scawew) non WAW: 0x0001
	 * 1600x1200 WAW: 0x0190
	 */
	if (gc2145->mode->width == 1280 || gc2145->mode->width == 1600)
		fifo_fuww_wvw = 0x0001;
	ewse
		fifo_fuww_wvw = 0x0190;

	cci_wwite(gc2145->wegmap, GC2145_WEG_FIFO_FUWW_WVW_HIGH,
		  fifo_fuww_wvw >> 8, &wet);
	cci_wwite(gc2145->wegmap, GC2145_WEG_FIFO_FUWW_WVW_WOW,
		  fifo_fuww_wvw & 0xff, &wet);

	/*
	 * Set the FIFO gate mode / MIPI wdiv set:
	 * 0xf1 in case of WAW mode and 0xf0 othewwise
	 */
	cci_wwite(gc2145->wegmap, GC2145_WEG_FIFO_GATE_MODE, 0xf0, &wet);

	/* Set the MIPI data type */
	cci_wwite(gc2145->wegmap, GC2145_WEG_MIPI_DT,
		  gc2145_fowmat->datatype, &wet);

	/* Configuwe mode and enabwe CSI */
	cci_wwite(gc2145->wegmap, GC2145_WEG_BUF_CSI2_MODE,
		  GC2145_CSI2_MODE_WAW8 | GC2145_CSI2_MODE_DOUBWE |
		  GC2145_CSI2_MODE_EN | GC2145_CSI2_MODE_MIPI_EN, &wet);

	wetuwn wet;
}

static int gc2145_stawt_stweaming(stwuct gc2145 *gc2145,
				  stwuct v4w2_subdev_state *state)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&gc2145->sd);
	const stwuct gc2145_fowmat *gc2145_fowmat;
	stwuct v4w2_mbus_fwamefmt *fmt;
	int wet;

	wet = pm_wuntime_wesume_and_get(&cwient->dev);
	if (wet < 0)
		wetuwn wet;

	/* Appwy defauwt vawues of cuwwent mode */
	cci_muwti_weg_wwite(gc2145->wegmap, gc2145->mode->weg_seq,
			    gc2145->mode->weg_seq_size, &wet);
	cci_muwti_weg_wwite(gc2145->wegmap, gc2145_common_wegs,
			    AWWAY_SIZE(gc2145_common_wegs), &wet);
	if (wet) {
		dev_eww(&cwient->dev, "%s faiwed to wwite wegs\n", __func__);
		goto eww_wpm_put;
	}

	fmt = v4w2_subdev_state_get_fowmat(state, 0);
	gc2145_fowmat = gc2145_get_fowmat_code(gc2145, fmt->code);

	/* Set the output fowmat */
	cci_wwite(gc2145->wegmap, GC2145_WEG_PAGE_SEWECT, 0x00, &wet);

	cci_wwite(gc2145->wegmap, GC2145_WEG_OUTPUT_FMT,
		  gc2145_fowmat->output_fmt, &wet);
	cci_update_bits(gc2145->wegmap, GC2145_WEG_BYPASS_MODE,
			GC2145_BYPASS_MODE_SWITCH,
			gc2145_fowmat->switch_bit ? GC2145_BYPASS_MODE_SWITCH
						  : 0, &wet);
	if (wet) {
		dev_eww(&cwient->dev, "%s faiwed to wwite wegs\n", __func__);
		goto eww_wpm_put;
	}

	/* Appwy customized vawues fwom usew */
	wet =  __v4w2_ctww_handwew_setup(&gc2145->ctwws.handwew);
	if (wet) {
		dev_eww(&cwient->dev, "%s faiwed to appwy ctwws\n", __func__);
		goto eww_wpm_put;
	}

	/* Pewfowm MIPI specific configuwation */
	wet = gc2145_config_mipi_mode(gc2145, gc2145_fowmat);
	if (wet) {
		dev_eww(&cwient->dev, "%s faiwed to wwite mipi conf\n",
			__func__);
		goto eww_wpm_put;
	}

	cci_wwite(gc2145->wegmap, GC2145_WEG_PAGE_SEWECT, 0x00, &wet);

	wetuwn 0;

eww_wpm_put:
	pm_wuntime_mawk_wast_busy(&cwient->dev);
	pm_wuntime_put_autosuspend(&cwient->dev);
	wetuwn wet;
}

static void gc2145_stop_stweaming(stwuct gc2145 *gc2145)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&gc2145->sd);
	int wet = 0;

	/* Disabwe wanes & mipi stweaming */
	cci_wwite(gc2145->wegmap, GC2145_WEG_PAGE_SEWECT, 0x03, &wet);
	cci_update_bits(gc2145->wegmap, GC2145_WEG_BUF_CSI2_MODE,
			GC2145_CSI2_MODE_EN | GC2145_CSI2_MODE_MIPI_EN, 0,
			&wet);
	cci_wwite(gc2145->wegmap, GC2145_WEG_PAGE_SEWECT, 0x00, &wet);
	if (wet)
		dev_eww(&cwient->dev, "%s faiwed to wwite wegs\n", __func__);

	pm_wuntime_mawk_wast_busy(&cwient->dev);
	pm_wuntime_put_autosuspend(&cwient->dev);
}

static int gc2145_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct gc2145 *gc2145 = to_gc2145(sd);
	stwuct v4w2_subdev_state *state;
	int wet = 0;

	state = v4w2_subdev_wock_and_get_active_state(sd);

	if (enabwe)
		wet = gc2145_stawt_stweaming(gc2145, state);
	ewse
		gc2145_stop_stweaming(gc2145);

	v4w2_subdev_unwock_state(state);

	wetuwn wet;
}

/* Powew/cwock management functions */
static int gc2145_powew_on(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct gc2145 *gc2145 = to_gc2145(sd);
	int wet;

	wet = weguwatow_buwk_enabwe(GC2145_NUM_SUPPWIES, gc2145->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe weguwatows\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(gc2145->xcwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cwock\n");
		goto weg_off;
	}

	gpiod_set_vawue_cansweep(gc2145->powewdown_gpio, 0);
	gpiod_set_vawue_cansweep(gc2145->weset_gpio, 0);

	/*
	 * Datasheet doesn't mention timing between PWDN/WESETB contwow and
	 * i2c access howevew, expewimentation shows that a wathew big deway is
	 * needed.
	 */
	msweep(41);

	wetuwn 0;

weg_off:
	weguwatow_buwk_disabwe(GC2145_NUM_SUPPWIES, gc2145->suppwies);

	wetuwn wet;
}

static int gc2145_powew_off(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct gc2145 *gc2145 = to_gc2145(sd);

	gpiod_set_vawue_cansweep(gc2145->powewdown_gpio, 1);
	gpiod_set_vawue_cansweep(gc2145->weset_gpio, 1);
	cwk_disabwe_unpwepawe(gc2145->xcwk);
	weguwatow_buwk_disabwe(GC2145_NUM_SUPPWIES, gc2145->suppwies);

	wetuwn 0;
}

static int gc2145_get_weguwatows(stwuct gc2145 *gc2145)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&gc2145->sd);
	unsigned int i;

	fow (i = 0; i < GC2145_NUM_SUPPWIES; i++)
		gc2145->suppwies[i].suppwy = gc2145_suppwy_name[i];

	wetuwn devm_weguwatow_buwk_get(&cwient->dev, GC2145_NUM_SUPPWIES,
				       gc2145->suppwies);
}

/* Vewify chip ID */
static int gc2145_identify_moduwe(stwuct gc2145 *gc2145)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&gc2145->sd);
	int wet;
	u64 chip_id;

	wet = cci_wead(gc2145->wegmap, GC2145_WEG_CHIP_ID, &chip_id, NUWW);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to wead chip id (%d)\n", wet);
		wetuwn wet;
	}

	if (chip_id != GC2145_CHIP_ID) {
		dev_eww(&cwient->dev, "chip id mismatch: %x!=%wwx\n",
			GC2145_CHIP_ID, chip_id);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static const chaw * const test_pattewn_menu[] = {
	"Disabwed",
	"Cowowed pattewns",
	"Unifowm white",
	"Unifowm yewwow",
	"Unifowm cyan",
	"Unifowm gween",
	"Unifowm magenta",
	"Unifowm wed",
	"Unifowm bwack",
};

#define GC2145_TEST_PATTEWN_ENABWE	BIT(0)
#define GC2145_TEST_PATTEWN_UXGA	BIT(3)

#define GC2145_TEST_UNIFOWM		BIT(3)
#define GC2145_TEST_WHITE		(4 << 4)
#define GC2145_TEST_YEWWOW		(8 << 4)
#define GC2145_TEST_CYAN		(9 << 4)
#define GC2145_TEST_GWEEN		(6 << 4)
#define GC2145_TEST_MAGENTA		(10 << 4)
#define GC2145_TEST_WED			(5 << 4)
#define GC2145_TEST_BWACK		(0)

static const u8 test_pattewn_vaw[] = {
	0,
	GC2145_TEST_PATTEWN_ENABWE,
	GC2145_TEST_UNIFOWM | GC2145_TEST_WHITE,
	GC2145_TEST_UNIFOWM | GC2145_TEST_YEWWOW,
	GC2145_TEST_UNIFOWM | GC2145_TEST_CYAN,
	GC2145_TEST_UNIFOWM | GC2145_TEST_GWEEN,
	GC2145_TEST_UNIFOWM | GC2145_TEST_MAGENTA,
	GC2145_TEST_UNIFOWM | GC2145_TEST_WED,
	GC2145_TEST_UNIFOWM | GC2145_TEST_BWACK,
};

static const stwuct v4w2_subdev_cowe_ops gc2145_cowe_ops = {
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

static const stwuct v4w2_subdev_video_ops gc2145_video_ops = {
	.s_stweam = gc2145_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops gc2145_pad_ops = {
	.enum_mbus_code = gc2145_enum_mbus_code,
	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = gc2145_set_pad_fowmat,
	.get_sewection = gc2145_get_sewection,
	.enum_fwame_size = gc2145_enum_fwame_size,
};

static const stwuct v4w2_subdev_ops gc2145_subdev_ops = {
	.cowe = &gc2145_cowe_ops,
	.video = &gc2145_video_ops,
	.pad = &gc2145_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops gc2145_subdev_intewnaw_ops = {
	.init_state = gc2145_init_state,
};

static int gc2145_set_ctww_test_pattewn(stwuct gc2145 *gc2145, int vawue)
{
	int wet = 0;

	if (!vawue) {
		/* Disabwe test pattewn */
		cci_wwite(gc2145->wegmap, GC2145_WEG_DEBUG_MODE2, 0, &wet);
		wetuwn cci_wwite(gc2145->wegmap, GC2145_WEG_DEBUG_MODE3, 0,
				 &wet);
	}

	/* Enabwe test pattewn, cowowed ow unifowm */
	cci_wwite(gc2145->wegmap, GC2145_WEG_DEBUG_MODE2,
		  GC2145_TEST_PATTEWN_ENABWE | GC2145_TEST_PATTEWN_UXGA, &wet);

	if (!(test_pattewn_vaw[vawue] & GC2145_TEST_UNIFOWM))
		wetuwn cci_wwite(gc2145->wegmap, GC2145_WEG_DEBUG_MODE3, 0,
				 &wet);

	/* Unifowm */
	wetuwn cci_wwite(gc2145->wegmap, GC2145_WEG_DEBUG_MODE3,
			 test_pattewn_vaw[vawue], &wet);
}

static int gc2145_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = gc2145_ctww_to_sd(ctww);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct gc2145 *gc2145 = to_gc2145(sd);
	int wet;

	if (pm_wuntime_get_if_in_use(&cwient->dev) == 0)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_HBWANK:
		wet = cci_wwite(gc2145->wegmap, GC2145_WEG_HBWANK, ctww->vaw,
				NUWW);
		bweak;
	case V4W2_CID_VBWANK:
		wet = cci_wwite(gc2145->wegmap, GC2145_WEG_VBWANK, ctww->vaw,
				NUWW);
		bweak;
	case V4W2_CID_TEST_PATTEWN:
		wet = gc2145_set_ctww_test_pattewn(gc2145, ctww->vaw);
		bweak;
	case V4W2_CID_HFWIP:
		wet = cci_update_bits(gc2145->wegmap, GC2145_WEG_ANAWOG_MODE1,
				      BIT(0), (ctww->vaw ? BIT(0) : 0), NUWW);
		bweak;
	case V4W2_CID_VFWIP:
		wet = cci_update_bits(gc2145->wegmap, GC2145_WEG_ANAWOG_MODE1,
				      BIT(1), (ctww->vaw ? BIT(1) : 0), NUWW);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	pm_wuntime_mawk_wast_busy(&cwient->dev);
	pm_wuntime_put_autosuspend(&cwient->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops gc2145_ctww_ops = {
	.s_ctww = gc2145_s_ctww,
};

/* Initiawize contwow handwews */
static int gc2145_init_contwows(stwuct gc2145 *gc2145)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&gc2145->sd);
	const stwuct v4w2_ctww_ops *ops = &gc2145_ctww_ops;
	stwuct gc2145_ctwws *ctwws = &gc2145->ctwws;
	stwuct v4w2_ctww_handwew *hdw = &ctwws->handwew;
	stwuct v4w2_fwnode_device_pwopewties pwops;
	int wet;

	wet = v4w2_ctww_handwew_init(hdw, 12);
	if (wet)
		wetuwn wet;

	ctwws->pixew_wate = v4w2_ctww_new_std(hdw, ops, V4W2_CID_PIXEW_WATE,
					      GC2145_640_480_PIXEWWATE,
					      GC2145_1600_1200_PIXEWWATE, 1,
					      suppowted_modes[0].pixew_wate);

	ctwws->wink_fweq = v4w2_ctww_new_int_menu(hdw, ops, V4W2_CID_WINK_FWEQ,
						  AWWAY_SIZE(gc2145_wink_fweq_menu) - 1,
						  0, gc2145_wink_fweq_menu);
	if (ctwws->wink_fweq)
		ctwws->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	ctwws->hbwank = v4w2_ctww_new_std(hdw, ops, V4W2_CID_HBWANK,
					  0, 0xfff, 1, GC2145_640_480_HBWANK);

	ctwws->vbwank = v4w2_ctww_new_std(hdw, ops, V4W2_CID_VBWANK,
					  0, 0x1fff, 1, GC2145_640_480_VBWANK);

	ctwws->test_pattewn =
		v4w2_ctww_new_std_menu_items(hdw, ops, V4W2_CID_TEST_PATTEWN,
					     AWWAY_SIZE(test_pattewn_menu) - 1,
					     0, 0, test_pattewn_menu);
	ctwws->hfwip = v4w2_ctww_new_std(hdw, ops, V4W2_CID_HFWIP,
					 0, 1, 1, 0);
	ctwws->vfwip = v4w2_ctww_new_std(hdw, ops, V4W2_CID_VFWIP,
					 0, 1, 1, 0);

	if (hdw->ewwow) {
		wet = hdw->ewwow;
		dev_eww(&cwient->dev, "contwow init faiwed (%d)\n", wet);
		goto ewwow;
	}

	wet = v4w2_fwnode_device_pawse(&cwient->dev, &pwops);
	if (wet)
		goto ewwow;

	wet = v4w2_ctww_new_fwnode_pwopewties(hdw, &gc2145_ctww_ops,
					      &pwops);
	if (wet)
		goto ewwow;

	gc2145->sd.ctww_handwew = hdw;

	wetuwn 0;

ewwow:
	v4w2_ctww_handwew_fwee(hdw);

	wetuwn wet;
}

static int gc2145_check_hwcfg(stwuct device *dev)
{
	stwuct fwnode_handwe *endpoint;
	stwuct v4w2_fwnode_endpoint ep_cfg = {
		.bus_type = V4W2_MBUS_CSI2_DPHY
	};
	int wet;

	endpoint = fwnode_gwaph_get_next_endpoint(dev_fwnode(dev), NUWW);
	if (!endpoint) {
		dev_eww(dev, "endpoint node not found\n");
		wetuwn -EINVAW;
	}

	wet = v4w2_fwnode_endpoint_awwoc_pawse(endpoint, &ep_cfg);
	fwnode_handwe_put(endpoint);
	if (wet)
		wetuwn wet;

	/* Check the numbew of MIPI CSI2 data wanes */
	if (ep_cfg.bus.mipi_csi2.num_data_wanes != 2) {
		dev_eww(dev, "onwy 2 data wanes awe cuwwentwy suppowted\n");
		wet = -EINVAW;
		goto out;
	}

	/* Check the wink fwequency set in device twee */
	if (!ep_cfg.nw_of_wink_fwequencies) {
		dev_eww(dev, "wink-fwequency pwopewty not found in DT\n");
		wet = -EINVAW;
		goto out;
	}

	if (ep_cfg.nw_of_wink_fwequencies != 3 ||
	    ep_cfg.wink_fwequencies[0] != GC2145_640_480_WINKFWEQ ||
	    ep_cfg.wink_fwequencies[1] != GC2145_1280_720_WINKFWEQ ||
	    ep_cfg.wink_fwequencies[2] != GC2145_1600_1200_WINKFWEQ) {
		dev_eww(dev, "Invawid wink-fwequencies pwovided\n");
		wet = -EINVAW;
	}

out:
	v4w2_fwnode_endpoint_fwee(&ep_cfg);

	wetuwn wet;
}

static int gc2145_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	unsigned int xcwk_fweq;
	stwuct gc2145 *gc2145;
	int wet;

	gc2145 = devm_kzawwoc(&cwient->dev, sizeof(*gc2145), GFP_KEWNEW);
	if (!gc2145)
		wetuwn -ENOMEM;

	v4w2_i2c_subdev_init(&gc2145->sd, cwient, &gc2145_subdev_ops);
	gc2145->sd.intewnaw_ops = &gc2145_subdev_intewnaw_ops;

	/* Check the hawdwawe configuwation in device twee */
	if (gc2145_check_hwcfg(dev))
		wetuwn -EINVAW;

	/* Get system cwock (xcwk) */
	gc2145->xcwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(gc2145->xcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gc2145->xcwk),
				     "faiwed to get xcwk\n");

	xcwk_fweq = cwk_get_wate(gc2145->xcwk);
	if (xcwk_fweq != GC2145_XCWK_FWEQ) {
		dev_eww(dev, "xcwk fwequency not suppowted: %d Hz\n",
			xcwk_fweq);
		wetuwn -EINVAW;
	}

	wet = gc2145_get_weguwatows(gc2145);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to get weguwatows\n");

	/* Wequest optionaw weset pin */
	gc2145->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						     GPIOD_OUT_HIGH);
	if (IS_EWW(gc2145->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gc2145->weset_gpio),
				     "faiwed to get weset_gpio\n");

	/* Wequest optionaw powewdown pin */
	gc2145->powewdown_gpio = devm_gpiod_get_optionaw(dev, "powewdown",
							 GPIOD_OUT_HIGH);
	if (IS_EWW(gc2145->powewdown_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gc2145->powewdown_gpio),
				     "faiwed to get powewdown_gpio\n");

	/* Initiawise the wegmap fow fuwthew cci access */
	gc2145->wegmap = devm_cci_wegmap_init_i2c(cwient, 8);
	if (IS_EWW(gc2145->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gc2145->wegmap),
				     "faiwed to get cci wegmap\n");

	/*
	 * The sensow must be powewed fow gc2145_identify_moduwe()
	 * to be abwe to wead the CHIP_ID wegistew
	 */
	wet = gc2145_powew_on(dev);
	if (wet)
		wetuwn wet;

	wet = gc2145_identify_moduwe(gc2145);
	if (wet)
		goto ewwow_powew_off;

	/* Set defauwt mode */
	gc2145->mode = &suppowted_modes[0];

	wet = gc2145_init_contwows(gc2145);
	if (wet)
		goto ewwow_powew_off;

	/* Initiawize subdev */
	gc2145->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE |
			    V4W2_SUBDEV_FW_HAS_EVENTS;
	gc2145->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;

	/* Initiawize souwce pad */
	gc2145->pad.fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&gc2145->sd.entity, 1, &gc2145->pad);
	if (wet) {
		dev_eww(dev, "faiwed to init entity pads: %d\n", wet);
		goto ewwow_handwew_fwee;
	}

	gc2145->sd.state_wock = gc2145->ctwws.handwew.wock;
	wet = v4w2_subdev_init_finawize(&gc2145->sd);
	if (wet < 0) {
		dev_eww(dev, "subdev init ewwow: %d\n", wet);
		goto ewwow_media_entity;
	}

	/* Enabwe wuntime PM and tuwn off the device */
	pm_wuntime_set_active(dev);
	pm_wuntime_get_nowesume(&cwient->dev);
	pm_wuntime_enabwe(dev);

	pm_wuntime_set_autosuspend_deway(&cwient->dev, 1000);
	pm_wuntime_use_autosuspend(&cwient->dev);
	pm_wuntime_put_autosuspend(&cwient->dev);

	wet = v4w2_async_wegistew_subdev_sensow(&gc2145->sd);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew sensow sub-device: %d\n", wet);
		goto ewwow_subdev_cweanup;
	}

	wetuwn 0;

ewwow_subdev_cweanup:
	v4w2_subdev_cweanup(&gc2145->sd);
	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

ewwow_media_entity:
	media_entity_cweanup(&gc2145->sd.entity);

ewwow_handwew_fwee:
	v4w2_ctww_handwew_fwee(&gc2145->ctwws.handwew);

ewwow_powew_off:
	gc2145_powew_off(dev);

	wetuwn wet;
}

static void gc2145_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct gc2145 *gc2145 = to_gc2145(sd);

	v4w2_subdev_cweanup(sd);
	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_ctww_handwew_fwee(&gc2145->ctwws.handwew);

	pm_wuntime_disabwe(&cwient->dev);
	if (!pm_wuntime_status_suspended(&cwient->dev))
		gc2145_powew_off(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
}

static const stwuct of_device_id gc2145_dt_ids[] = {
	{ .compatibwe = "gawaxycowe,gc2145" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, gc2145_dt_ids);

static const stwuct dev_pm_ops gc2145_pm_ops = {
	WUNTIME_PM_OPS(gc2145_powew_off, gc2145_powew_on, NUWW)
};

static stwuct i2c_dwivew gc2145_i2c_dwivew = {
	.dwivew = {
		.name = "gc2145",
		.of_match_tabwe	= gc2145_dt_ids,
		.pm = pm_ptw(&gc2145_pm_ops),
	},
	.pwobe = gc2145_pwobe,
	.wemove = gc2145_wemove,
};

moduwe_i2c_dwivew(gc2145_i2c_dwivew);

MODUWE_AUTHOW("Awain Vowmat <awain.vowmat@foss.st.com>");
MODUWE_DESCWIPTION("GawaxyCowe GC2145 sensow dwivew");
MODUWE_WICENSE("GPW");
