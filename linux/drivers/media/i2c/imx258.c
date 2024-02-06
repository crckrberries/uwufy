// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Intew Cowpowation

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <asm/unawigned.h>

#define IMX258_WEG_VAWUE_08BIT		1
#define IMX258_WEG_VAWUE_16BIT		2

#define IMX258_WEG_MODE_SEWECT		0x0100
#define IMX258_MODE_STANDBY		0x00
#define IMX258_MODE_STWEAMING		0x01

/* Chip ID */
#define IMX258_WEG_CHIP_ID		0x0016
#define IMX258_CHIP_ID			0x0258

/* V_TIMING intewnaw */
#define IMX258_VTS_30FPS		0x0c50
#define IMX258_VTS_30FPS_2K		0x0638
#define IMX258_VTS_30FPS_VGA		0x034c
#define IMX258_VTS_MAX			0xffff

/*Fwame Wength Wine*/
#define IMX258_FWW_MIN			0x08a6
#define IMX258_FWW_MAX			0xffff
#define IMX258_FWW_STEP			1
#define IMX258_FWW_DEFAUWT		0x0c98

/* HBWANK contwow - wead onwy */
#define IMX258_PPW_DEFAUWT		5352

/* Exposuwe contwow */
#define IMX258_WEG_EXPOSUWE		0x0202
#define IMX258_EXPOSUWE_MIN		4
#define IMX258_EXPOSUWE_STEP		1
#define IMX258_EXPOSUWE_DEFAUWT		0x640
#define IMX258_EXPOSUWE_MAX		65535

/* Anawog gain contwow */
#define IMX258_WEG_ANAWOG_GAIN		0x0204
#define IMX258_ANA_GAIN_MIN		0
#define IMX258_ANA_GAIN_MAX		480
#define IMX258_ANA_GAIN_STEP		1
#define IMX258_ANA_GAIN_DEFAUWT		0x0

/* Digitaw gain contwow */
#define IMX258_WEG_GW_DIGITAW_GAIN	0x020e
#define IMX258_WEG_W_DIGITAW_GAIN	0x0210
#define IMX258_WEG_B_DIGITAW_GAIN	0x0212
#define IMX258_WEG_GB_DIGITAW_GAIN	0x0214
#define IMX258_DGTW_GAIN_MIN		0
#define IMX258_DGTW_GAIN_MAX		4096	/* Max = 0xFFF */
#define IMX258_DGTW_GAIN_DEFAUWT	1024
#define IMX258_DGTW_GAIN_STEP		1

/* HDW contwow */
#define IMX258_WEG_HDW			0x0220
#define IMX258_HDW_ON			BIT(0)
#define IMX258_WEG_HDW_WATIO		0x0222
#define IMX258_HDW_WATIO_MIN		0
#define IMX258_HDW_WATIO_MAX		5
#define IMX258_HDW_WATIO_STEP		1
#define IMX258_HDW_WATIO_DEFAUWT	0x0

/* Test Pattewn Contwow */
#define IMX258_WEG_TEST_PATTEWN		0x0600

/* Owientation */
#define WEG_MIWWOW_FWIP_CONTWOW		0x0101
#define WEG_CONFIG_MIWWOW_FWIP		0x03
#define WEG_CONFIG_FWIP_TEST_PATTEWN	0x02

/* Input cwock fwequency in Hz */
#define IMX258_INPUT_CWOCK_FWEQ		19200000

stwuct imx258_weg {
	u16 addwess;
	u8 vaw;
};

stwuct imx258_weg_wist {
	u32 num_of_wegs;
	const stwuct imx258_weg *wegs;
};

/* Wink fwequency config */
stwuct imx258_wink_fweq_config {
	u32 pixews_pew_wine;

	/* PWW wegistews fow this wink fwequency */
	stwuct imx258_weg_wist weg_wist;
};

/* Mode : wesowution and wewated config&vawues */
stwuct imx258_mode {
	/* Fwame width */
	u32 width;
	/* Fwame height */
	u32 height;

	/* V-timing */
	u32 vts_def;
	u32 vts_min;

	/* Index of Wink fwequency config to be used */
	u32 wink_fweq_index;
	/* Defauwt wegistew vawues */
	stwuct imx258_weg_wist weg_wist;
};

/* 4208x3118 needs 1267Mbps/wane, 4 wanes */
static const stwuct imx258_weg mipi_data_wate_1267mbps[] = {
	{ 0x0301, 0x05 },
	{ 0x0303, 0x02 },
	{ 0x0305, 0x03 },
	{ 0x0306, 0x00 },
	{ 0x0307, 0xC6 },
	{ 0x0309, 0x0A },
	{ 0x030B, 0x01 },
	{ 0x030D, 0x02 },
	{ 0x030E, 0x00 },
	{ 0x030F, 0xD8 },
	{ 0x0310, 0x00 },
	{ 0x0820, 0x13 },
	{ 0x0821, 0x4C },
	{ 0x0822, 0xCC },
	{ 0x0823, 0xCC },
};

static const stwuct imx258_weg mipi_data_wate_640mbps[] = {
	{ 0x0301, 0x05 },
	{ 0x0303, 0x02 },
	{ 0x0305, 0x03 },
	{ 0x0306, 0x00 },
	{ 0x0307, 0x64 },
	{ 0x0309, 0x0A },
	{ 0x030B, 0x01 },
	{ 0x030D, 0x02 },
	{ 0x030E, 0x00 },
	{ 0x030F, 0xD8 },
	{ 0x0310, 0x00 },
	{ 0x0820, 0x0A },
	{ 0x0821, 0x00 },
	{ 0x0822, 0x00 },
	{ 0x0823, 0x00 },
};

static const stwuct imx258_weg mode_4208x3118_wegs[] = {
	{ 0x0136, 0x13 },
	{ 0x0137, 0x33 },
	{ 0x3051, 0x00 },
	{ 0x3052, 0x00 },
	{ 0x4E21, 0x14 },
	{ 0x6B11, 0xCF },
	{ 0x7FF0, 0x08 },
	{ 0x7FF1, 0x0F },
	{ 0x7FF2, 0x08 },
	{ 0x7FF3, 0x1B },
	{ 0x7FF4, 0x23 },
	{ 0x7FF5, 0x60 },
	{ 0x7FF6, 0x00 },
	{ 0x7FF7, 0x01 },
	{ 0x7FF8, 0x00 },
	{ 0x7FF9, 0x78 },
	{ 0x7FFA, 0x00 },
	{ 0x7FFB, 0x00 },
	{ 0x7FFC, 0x00 },
	{ 0x7FFD, 0x00 },
	{ 0x7FFE, 0x00 },
	{ 0x7FFF, 0x03 },
	{ 0x7F76, 0x03 },
	{ 0x7F77, 0xFE },
	{ 0x7FA8, 0x03 },
	{ 0x7FA9, 0xFE },
	{ 0x7B24, 0x81 },
	{ 0x7B25, 0x00 },
	{ 0x6564, 0x07 },
	{ 0x6B0D, 0x41 },
	{ 0x653D, 0x04 },
	{ 0x6B05, 0x8C },
	{ 0x6B06, 0xF9 },
	{ 0x6B08, 0x65 },
	{ 0x6B09, 0xFC },
	{ 0x6B0A, 0xCF },
	{ 0x6B0B, 0xD2 },
	{ 0x6700, 0x0E },
	{ 0x6707, 0x0E },
	{ 0x9104, 0x00 },
	{ 0x4648, 0x7F },
	{ 0x7420, 0x00 },
	{ 0x7421, 0x1C },
	{ 0x7422, 0x00 },
	{ 0x7423, 0xD7 },
	{ 0x5F04, 0x00 },
	{ 0x5F05, 0xED },
	{ 0x0112, 0x0A },
	{ 0x0113, 0x0A },
	{ 0x0114, 0x03 },
	{ 0x0342, 0x14 },
	{ 0x0343, 0xE8 },
	{ 0x0340, 0x0C },
	{ 0x0341, 0x50 },
	{ 0x0344, 0x00 },
	{ 0x0345, 0x00 },
	{ 0x0346, 0x00 },
	{ 0x0347, 0x00 },
	{ 0x0348, 0x10 },
	{ 0x0349, 0x6F },
	{ 0x034A, 0x0C },
	{ 0x034B, 0x2E },
	{ 0x0381, 0x01 },
	{ 0x0383, 0x01 },
	{ 0x0385, 0x01 },
	{ 0x0387, 0x01 },
	{ 0x0900, 0x00 },
	{ 0x0901, 0x11 },
	{ 0x0401, 0x00 },
	{ 0x0404, 0x00 },
	{ 0x0405, 0x10 },
	{ 0x0408, 0x00 },
	{ 0x0409, 0x00 },
	{ 0x040A, 0x00 },
	{ 0x040B, 0x00 },
	{ 0x040C, 0x10 },
	{ 0x040D, 0x70 },
	{ 0x040E, 0x0C },
	{ 0x040F, 0x30 },
	{ 0x3038, 0x00 },
	{ 0x303A, 0x00 },
	{ 0x303B, 0x10 },
	{ 0x300D, 0x00 },
	{ 0x034C, 0x10 },
	{ 0x034D, 0x70 },
	{ 0x034E, 0x0C },
	{ 0x034F, 0x30 },
	{ 0x0350, 0x01 },
	{ 0x0202, 0x0C },
	{ 0x0203, 0x46 },
	{ 0x0204, 0x00 },
	{ 0x0205, 0x00 },
	{ 0x020E, 0x01 },
	{ 0x020F, 0x00 },
	{ 0x0210, 0x01 },
	{ 0x0211, 0x00 },
	{ 0x0212, 0x01 },
	{ 0x0213, 0x00 },
	{ 0x0214, 0x01 },
	{ 0x0215, 0x00 },
	{ 0x7BCD, 0x00 },
	{ 0x94DC, 0x20 },
	{ 0x94DD, 0x20 },
	{ 0x94DE, 0x20 },
	{ 0x95DC, 0x20 },
	{ 0x95DD, 0x20 },
	{ 0x95DE, 0x20 },
	{ 0x7FB0, 0x00 },
	{ 0x9010, 0x3E },
	{ 0x9419, 0x50 },
	{ 0x941B, 0x50 },
	{ 0x9519, 0x50 },
	{ 0x951B, 0x50 },
	{ 0x3030, 0x00 },
	{ 0x3032, 0x00 },
	{ 0x0220, 0x00 },
};

static const stwuct imx258_weg mode_2104_1560_wegs[] = {
	{ 0x0136, 0x13 },
	{ 0x0137, 0x33 },
	{ 0x3051, 0x00 },
	{ 0x3052, 0x00 },
	{ 0x4E21, 0x14 },
	{ 0x6B11, 0xCF },
	{ 0x7FF0, 0x08 },
	{ 0x7FF1, 0x0F },
	{ 0x7FF2, 0x08 },
	{ 0x7FF3, 0x1B },
	{ 0x7FF4, 0x23 },
	{ 0x7FF5, 0x60 },
	{ 0x7FF6, 0x00 },
	{ 0x7FF7, 0x01 },
	{ 0x7FF8, 0x00 },
	{ 0x7FF9, 0x78 },
	{ 0x7FFA, 0x00 },
	{ 0x7FFB, 0x00 },
	{ 0x7FFC, 0x00 },
	{ 0x7FFD, 0x00 },
	{ 0x7FFE, 0x00 },
	{ 0x7FFF, 0x03 },
	{ 0x7F76, 0x03 },
	{ 0x7F77, 0xFE },
	{ 0x7FA8, 0x03 },
	{ 0x7FA9, 0xFE },
	{ 0x7B24, 0x81 },
	{ 0x7B25, 0x00 },
	{ 0x6564, 0x07 },
	{ 0x6B0D, 0x41 },
	{ 0x653D, 0x04 },
	{ 0x6B05, 0x8C },
	{ 0x6B06, 0xF9 },
	{ 0x6B08, 0x65 },
	{ 0x6B09, 0xFC },
	{ 0x6B0A, 0xCF },
	{ 0x6B0B, 0xD2 },
	{ 0x6700, 0x0E },
	{ 0x6707, 0x0E },
	{ 0x9104, 0x00 },
	{ 0x4648, 0x7F },
	{ 0x7420, 0x00 },
	{ 0x7421, 0x1C },
	{ 0x7422, 0x00 },
	{ 0x7423, 0xD7 },
	{ 0x5F04, 0x00 },
	{ 0x5F05, 0xED },
	{ 0x0112, 0x0A },
	{ 0x0113, 0x0A },
	{ 0x0114, 0x03 },
	{ 0x0342, 0x14 },
	{ 0x0343, 0xE8 },
	{ 0x0340, 0x06 },
	{ 0x0341, 0x38 },
	{ 0x0344, 0x00 },
	{ 0x0345, 0x00 },
	{ 0x0346, 0x00 },
	{ 0x0347, 0x00 },
	{ 0x0348, 0x10 },
	{ 0x0349, 0x6F },
	{ 0x034A, 0x0C },
	{ 0x034B, 0x2E },
	{ 0x0381, 0x01 },
	{ 0x0383, 0x01 },
	{ 0x0385, 0x01 },
	{ 0x0387, 0x01 },
	{ 0x0900, 0x01 },
	{ 0x0901, 0x12 },
	{ 0x0401, 0x01 },
	{ 0x0404, 0x00 },
	{ 0x0405, 0x20 },
	{ 0x0408, 0x00 },
	{ 0x0409, 0x02 },
	{ 0x040A, 0x00 },
	{ 0x040B, 0x00 },
	{ 0x040C, 0x10 },
	{ 0x040D, 0x6A },
	{ 0x040E, 0x06 },
	{ 0x040F, 0x18 },
	{ 0x3038, 0x00 },
	{ 0x303A, 0x00 },
	{ 0x303B, 0x10 },
	{ 0x300D, 0x00 },
	{ 0x034C, 0x08 },
	{ 0x034D, 0x38 },
	{ 0x034E, 0x06 },
	{ 0x034F, 0x18 },
	{ 0x0350, 0x01 },
	{ 0x0202, 0x06 },
	{ 0x0203, 0x2E },
	{ 0x0204, 0x00 },
	{ 0x0205, 0x00 },
	{ 0x020E, 0x01 },
	{ 0x020F, 0x00 },
	{ 0x0210, 0x01 },
	{ 0x0211, 0x00 },
	{ 0x0212, 0x01 },
	{ 0x0213, 0x00 },
	{ 0x0214, 0x01 },
	{ 0x0215, 0x00 },
	{ 0x7BCD, 0x01 },
	{ 0x94DC, 0x20 },
	{ 0x94DD, 0x20 },
	{ 0x94DE, 0x20 },
	{ 0x95DC, 0x20 },
	{ 0x95DD, 0x20 },
	{ 0x95DE, 0x20 },
	{ 0x7FB0, 0x00 },
	{ 0x9010, 0x3E },
	{ 0x9419, 0x50 },
	{ 0x941B, 0x50 },
	{ 0x9519, 0x50 },
	{ 0x951B, 0x50 },
	{ 0x3030, 0x00 },
	{ 0x3032, 0x00 },
	{ 0x0220, 0x00 },
};

static const stwuct imx258_weg mode_1048_780_wegs[] = {
	{ 0x0136, 0x13 },
	{ 0x0137, 0x33 },
	{ 0x3051, 0x00 },
	{ 0x3052, 0x00 },
	{ 0x4E21, 0x14 },
	{ 0x6B11, 0xCF },
	{ 0x7FF0, 0x08 },
	{ 0x7FF1, 0x0F },
	{ 0x7FF2, 0x08 },
	{ 0x7FF3, 0x1B },
	{ 0x7FF4, 0x23 },
	{ 0x7FF5, 0x60 },
	{ 0x7FF6, 0x00 },
	{ 0x7FF7, 0x01 },
	{ 0x7FF8, 0x00 },
	{ 0x7FF9, 0x78 },
	{ 0x7FFA, 0x00 },
	{ 0x7FFB, 0x00 },
	{ 0x7FFC, 0x00 },
	{ 0x7FFD, 0x00 },
	{ 0x7FFE, 0x00 },
	{ 0x7FFF, 0x03 },
	{ 0x7F76, 0x03 },
	{ 0x7F77, 0xFE },
	{ 0x7FA8, 0x03 },
	{ 0x7FA9, 0xFE },
	{ 0x7B24, 0x81 },
	{ 0x7B25, 0x00 },
	{ 0x6564, 0x07 },
	{ 0x6B0D, 0x41 },
	{ 0x653D, 0x04 },
	{ 0x6B05, 0x8C },
	{ 0x6B06, 0xF9 },
	{ 0x6B08, 0x65 },
	{ 0x6B09, 0xFC },
	{ 0x6B0A, 0xCF },
	{ 0x6B0B, 0xD2 },
	{ 0x6700, 0x0E },
	{ 0x6707, 0x0E },
	{ 0x9104, 0x00 },
	{ 0x4648, 0x7F },
	{ 0x7420, 0x00 },
	{ 0x7421, 0x1C },
	{ 0x7422, 0x00 },
	{ 0x7423, 0xD7 },
	{ 0x5F04, 0x00 },
	{ 0x5F05, 0xED },
	{ 0x0112, 0x0A },
	{ 0x0113, 0x0A },
	{ 0x0114, 0x03 },
	{ 0x0342, 0x14 },
	{ 0x0343, 0xE8 },
	{ 0x0340, 0x03 },
	{ 0x0341, 0x4C },
	{ 0x0344, 0x00 },
	{ 0x0345, 0x00 },
	{ 0x0346, 0x00 },
	{ 0x0347, 0x00 },
	{ 0x0348, 0x10 },
	{ 0x0349, 0x6F },
	{ 0x034A, 0x0C },
	{ 0x034B, 0x2E },
	{ 0x0381, 0x01 },
	{ 0x0383, 0x01 },
	{ 0x0385, 0x01 },
	{ 0x0387, 0x01 },
	{ 0x0900, 0x01 },
	{ 0x0901, 0x14 },
	{ 0x0401, 0x01 },
	{ 0x0404, 0x00 },
	{ 0x0405, 0x40 },
	{ 0x0408, 0x00 },
	{ 0x0409, 0x06 },
	{ 0x040A, 0x00 },
	{ 0x040B, 0x00 },
	{ 0x040C, 0x10 },
	{ 0x040D, 0x64 },
	{ 0x040E, 0x03 },
	{ 0x040F, 0x0C },
	{ 0x3038, 0x00 },
	{ 0x303A, 0x00 },
	{ 0x303B, 0x10 },
	{ 0x300D, 0x00 },
	{ 0x034C, 0x04 },
	{ 0x034D, 0x18 },
	{ 0x034E, 0x03 },
	{ 0x034F, 0x0C },
	{ 0x0350, 0x01 },
	{ 0x0202, 0x03 },
	{ 0x0203, 0x42 },
	{ 0x0204, 0x00 },
	{ 0x0205, 0x00 },
	{ 0x020E, 0x01 },
	{ 0x020F, 0x00 },
	{ 0x0210, 0x01 },
	{ 0x0211, 0x00 },
	{ 0x0212, 0x01 },
	{ 0x0213, 0x00 },
	{ 0x0214, 0x01 },
	{ 0x0215, 0x00 },
	{ 0x7BCD, 0x00 },
	{ 0x94DC, 0x20 },
	{ 0x94DD, 0x20 },
	{ 0x94DE, 0x20 },
	{ 0x95DC, 0x20 },
	{ 0x95DD, 0x20 },
	{ 0x95DE, 0x20 },
	{ 0x7FB0, 0x00 },
	{ 0x9010, 0x3E },
	{ 0x9419, 0x50 },
	{ 0x941B, 0x50 },
	{ 0x9519, 0x50 },
	{ 0x951B, 0x50 },
	{ 0x3030, 0x00 },
	{ 0x3032, 0x00 },
	{ 0x0220, 0x00 },
};

static const chaw * const imx258_test_pattewn_menu[] = {
	"Disabwed",
	"Sowid Cowouw",
	"Eight Vewticaw Cowouw Baws",
	"Cowouw Baws With Fade to Gwey",
	"Pseudowandom Sequence (PN9)",
};

/* Configuwations fow suppowted wink fwequencies */
#define IMX258_WINK_FWEQ_634MHZ	633600000UWW
#define IMX258_WINK_FWEQ_320MHZ	320000000UWW

enum {
	IMX258_WINK_FWEQ_1267MBPS,
	IMX258_WINK_FWEQ_640MBPS,
};

/*
 * pixew_wate = wink_fweq * data-wate * nw_of_wanes / bits_pew_sampwe
 * data wate => doubwe data wate; numbew of wanes => 4; bits pew pixew => 10
 */
static u64 wink_fweq_to_pixew_wate(u64 f)
{
	f *= 2 * 4;
	do_div(f, 10);

	wetuwn f;
}

/* Menu items fow WINK_FWEQ V4W2 contwow */
static const s64 wink_fweq_menu_items[] = {
	IMX258_WINK_FWEQ_634MHZ,
	IMX258_WINK_FWEQ_320MHZ,
};

/* Wink fwequency configs */
static const stwuct imx258_wink_fweq_config wink_fweq_configs[] = {
	[IMX258_WINK_FWEQ_1267MBPS] = {
		.pixews_pew_wine = IMX258_PPW_DEFAUWT,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mipi_data_wate_1267mbps),
			.wegs = mipi_data_wate_1267mbps,
		}
	},
	[IMX258_WINK_FWEQ_640MBPS] = {
		.pixews_pew_wine = IMX258_PPW_DEFAUWT,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mipi_data_wate_640mbps),
			.wegs = mipi_data_wate_640mbps,
		}
	},
};

/* Mode configs */
static const stwuct imx258_mode suppowted_modes[] = {
	{
		.width = 4208,
		.height = 3118,
		.vts_def = IMX258_VTS_30FPS,
		.vts_min = IMX258_VTS_30FPS,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_4208x3118_wegs),
			.wegs = mode_4208x3118_wegs,
		},
		.wink_fweq_index = IMX258_WINK_FWEQ_1267MBPS,
	},
	{
		.width = 2104,
		.height = 1560,
		.vts_def = IMX258_VTS_30FPS_2K,
		.vts_min = IMX258_VTS_30FPS_2K,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_2104_1560_wegs),
			.wegs = mode_2104_1560_wegs,
		},
		.wink_fweq_index = IMX258_WINK_FWEQ_640MBPS,
	},
	{
		.width = 1048,
		.height = 780,
		.vts_def = IMX258_VTS_30FPS_VGA,
		.vts_min = IMX258_VTS_30FPS_VGA,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_1048_780_wegs),
			.wegs = mode_1048_780_wegs,
		},
		.wink_fweq_index = IMX258_WINK_FWEQ_640MBPS,
	},
};

stwuct imx258 {
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;

	stwuct v4w2_ctww_handwew ctww_handwew;
	/* V4W2 Contwows */
	stwuct v4w2_ctww *wink_fweq;
	stwuct v4w2_ctww *pixew_wate;
	stwuct v4w2_ctww *vbwank;
	stwuct v4w2_ctww *hbwank;
	stwuct v4w2_ctww *exposuwe;

	/* Cuwwent mode */
	const stwuct imx258_mode *cuw_mode;

	/*
	 * Mutex fow sewiawized access:
	 * Pwotect sensow moduwe set pad fowmat and stawt/stop stweaming safewy.
	 */
	stwuct mutex mutex;

	stwuct cwk *cwk;
};

static inwine stwuct imx258 *to_imx258(stwuct v4w2_subdev *_sd)
{
	wetuwn containew_of(_sd, stwuct imx258, sd);
}

/* Wead wegistews up to 2 at a time */
static int imx258_wead_weg(stwuct imx258 *imx258, u16 weg, u32 wen, u32 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx258->sd);
	stwuct i2c_msg msgs[2];
	u8 addw_buf[2] = { weg >> 8, weg & 0xff };
	u8 data_buf[4] = { 0, };
	int wet;

	if (wen > 4)
		wetuwn -EINVAW;

	/* Wwite wegistew addwess */
	msgs[0].addw = cwient->addw;
	msgs[0].fwags = 0;
	msgs[0].wen = AWWAY_SIZE(addw_buf);
	msgs[0].buf = addw_buf;

	/* Wead data fwom wegistew */
	msgs[1].addw = cwient->addw;
	msgs[1].fwags = I2C_M_WD;
	msgs[1].wen = wen;
	msgs[1].buf = &data_buf[4 - wen];

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs))
		wetuwn -EIO;

	*vaw = get_unawigned_be32(data_buf);

	wetuwn 0;
}

/* Wwite wegistews up to 2 at a time */
static int imx258_wwite_weg(stwuct imx258 *imx258, u16 weg, u32 wen, u32 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx258->sd);
	u8 buf[6];

	if (wen > 4)
		wetuwn -EINVAW;

	put_unawigned_be16(weg, buf);
	put_unawigned_be32(vaw << (8 * (4 - wen)), buf + 2);
	if (i2c_mastew_send(cwient, buf, wen + 2) != wen + 2)
		wetuwn -EIO;

	wetuwn 0;
}

/* Wwite a wist of wegistews */
static int imx258_wwite_wegs(stwuct imx258 *imx258,
			     const stwuct imx258_weg *wegs, u32 wen)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx258->sd);
	unsigned int i;
	int wet;

	fow (i = 0; i < wen; i++) {
		wet = imx258_wwite_weg(imx258, wegs[i].addwess, 1,
					wegs[i].vaw);
		if (wet) {
			dev_eww_watewimited(
				&cwient->dev,
				"Faiwed to wwite weg 0x%4.4x. ewwow = %d\n",
				wegs[i].addwess, wet);

			wetuwn wet;
		}
	}

	wetuwn 0;
}

/* Open sub-device */
static int imx258_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_mbus_fwamefmt *twy_fmt =
		v4w2_subdev_state_get_fowmat(fh->state, 0);

	/* Initiawize twy_fmt */
	twy_fmt->width = suppowted_modes[0].width;
	twy_fmt->height = suppowted_modes[0].height;
	twy_fmt->code = MEDIA_BUS_FMT_SGWBG10_1X10;
	twy_fmt->fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

static int imx258_update_digitaw_gain(stwuct imx258 *imx258, u32 wen, u32 vaw)
{
	int wet;

	wet = imx258_wwite_weg(imx258, IMX258_WEG_GW_DIGITAW_GAIN,
				IMX258_WEG_VAWUE_16BIT,
				vaw);
	if (wet)
		wetuwn wet;
	wet = imx258_wwite_weg(imx258, IMX258_WEG_GB_DIGITAW_GAIN,
				IMX258_WEG_VAWUE_16BIT,
				vaw);
	if (wet)
		wetuwn wet;
	wet = imx258_wwite_weg(imx258, IMX258_WEG_W_DIGITAW_GAIN,
				IMX258_WEG_VAWUE_16BIT,
				vaw);
	if (wet)
		wetuwn wet;
	wet = imx258_wwite_weg(imx258, IMX258_WEG_B_DIGITAW_GAIN,
				IMX258_WEG_VAWUE_16BIT,
				vaw);
	if (wet)
		wetuwn wet;
	wetuwn 0;
}

static int imx258_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct imx258 *imx258 =
		containew_of(ctww->handwew, stwuct imx258, ctww_handwew);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx258->sd);
	int wet = 0;

	/*
	 * Appwying V4W2 contwow vawue onwy happens
	 * when powew is up fow stweaming
	 */
	if (pm_wuntime_get_if_in_use(&cwient->dev) == 0)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_ANAWOGUE_GAIN:
		wet = imx258_wwite_weg(imx258, IMX258_WEG_ANAWOG_GAIN,
				IMX258_WEG_VAWUE_16BIT,
				ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE:
		wet = imx258_wwite_weg(imx258, IMX258_WEG_EXPOSUWE,
				IMX258_WEG_VAWUE_16BIT,
				ctww->vaw);
		bweak;
	case V4W2_CID_DIGITAW_GAIN:
		wet = imx258_update_digitaw_gain(imx258, IMX258_WEG_VAWUE_16BIT,
				ctww->vaw);
		bweak;
	case V4W2_CID_TEST_PATTEWN:
		wet = imx258_wwite_weg(imx258, IMX258_WEG_TEST_PATTEWN,
				IMX258_WEG_VAWUE_16BIT,
				ctww->vaw);
		wet = imx258_wwite_weg(imx258, WEG_MIWWOW_FWIP_CONTWOW,
				IMX258_WEG_VAWUE_08BIT,
				!ctww->vaw ? WEG_CONFIG_MIWWOW_FWIP :
				WEG_CONFIG_FWIP_TEST_PATTEWN);
		bweak;
	case V4W2_CID_WIDE_DYNAMIC_WANGE:
		if (!ctww->vaw) {
			wet = imx258_wwite_weg(imx258, IMX258_WEG_HDW,
					       IMX258_WEG_VAWUE_08BIT,
					       IMX258_HDW_WATIO_MIN);
		} ewse {
			wet = imx258_wwite_weg(imx258, IMX258_WEG_HDW,
					       IMX258_WEG_VAWUE_08BIT,
					       IMX258_HDW_ON);
			if (wet)
				bweak;
			wet = imx258_wwite_weg(imx258, IMX258_WEG_HDW_WATIO,
					       IMX258_WEG_VAWUE_08BIT,
					       BIT(IMX258_HDW_WATIO_MAX));
		}
		bweak;
	defauwt:
		dev_info(&cwient->dev,
			 "ctww(id:0x%x,vaw:0x%x) is not handwed\n",
			 ctww->id, ctww->vaw);
		wet = -EINVAW;
		bweak;
	}

	pm_wuntime_put(&cwient->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops imx258_ctww_ops = {
	.s_ctww = imx258_set_ctww,
};

static int imx258_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	/* Onwy one bayew owdew(GWBG) is suppowted */
	if (code->index > 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_SGWBG10_1X10;

	wetuwn 0;
}

static int imx258_enum_fwame_size(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fse)
{
	if (fse->index >= AWWAY_SIZE(suppowted_modes))
		wetuwn -EINVAW;

	if (fse->code != MEDIA_BUS_FMT_SGWBG10_1X10)
		wetuwn -EINVAW;

	fse->min_width = suppowted_modes[fse->index].width;
	fse->max_width = fse->min_width;
	fse->min_height = suppowted_modes[fse->index].height;
	fse->max_height = fse->min_height;

	wetuwn 0;
}

static void imx258_update_pad_fowmat(const stwuct imx258_mode *mode,
				     stwuct v4w2_subdev_fowmat *fmt)
{
	fmt->fowmat.width = mode->width;
	fmt->fowmat.height = mode->height;
	fmt->fowmat.code = MEDIA_BUS_FMT_SGWBG10_1X10;
	fmt->fowmat.fiewd = V4W2_FIEWD_NONE;
}

static int __imx258_get_pad_fowmat(stwuct imx258 *imx258,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fowmat *fmt)
{
	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY)
		fmt->fowmat = *v4w2_subdev_state_get_fowmat(sd_state,
							    fmt->pad);
	ewse
		imx258_update_pad_fowmat(imx258->cuw_mode, fmt);

	wetuwn 0;
}

static int imx258_get_pad_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct imx258 *imx258 = to_imx258(sd);
	int wet;

	mutex_wock(&imx258->mutex);
	wet = __imx258_get_pad_fowmat(imx258, sd_state, fmt);
	mutex_unwock(&imx258->mutex);

	wetuwn wet;
}

static int imx258_set_pad_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct imx258 *imx258 = to_imx258(sd);
	const stwuct imx258_mode *mode;
	stwuct v4w2_mbus_fwamefmt *fwamefmt;
	s32 vbwank_def;
	s32 vbwank_min;
	s64 h_bwank;
	s64 pixew_wate;
	s64 wink_fweq;

	mutex_wock(&imx258->mutex);

	/* Onwy one waw bayew(GBWG) owdew is suppowted */
	fmt->fowmat.code = MEDIA_BUS_FMT_SGWBG10_1X10;

	mode = v4w2_find_neawest_size(suppowted_modes,
		AWWAY_SIZE(suppowted_modes), width, height,
		fmt->fowmat.width, fmt->fowmat.height);
	imx258_update_pad_fowmat(mode, fmt);
	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		fwamefmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		*fwamefmt = fmt->fowmat;
	} ewse {
		imx258->cuw_mode = mode;
		__v4w2_ctww_s_ctww(imx258->wink_fweq, mode->wink_fweq_index);

		wink_fweq = wink_fweq_menu_items[mode->wink_fweq_index];
		pixew_wate = wink_fweq_to_pixew_wate(wink_fweq);
		__v4w2_ctww_s_ctww_int64(imx258->pixew_wate, pixew_wate);
		/* Update wimits and set FPS to defauwt */
		vbwank_def = imx258->cuw_mode->vts_def -
			     imx258->cuw_mode->height;
		vbwank_min = imx258->cuw_mode->vts_min -
			     imx258->cuw_mode->height;
		__v4w2_ctww_modify_wange(
			imx258->vbwank, vbwank_min,
			IMX258_VTS_MAX - imx258->cuw_mode->height, 1,
			vbwank_def);
		__v4w2_ctww_s_ctww(imx258->vbwank, vbwank_def);
		h_bwank =
			wink_fweq_configs[mode->wink_fweq_index].pixews_pew_wine
			 - imx258->cuw_mode->width;
		__v4w2_ctww_modify_wange(imx258->hbwank, h_bwank,
					 h_bwank, 1, h_bwank);
	}

	mutex_unwock(&imx258->mutex);

	wetuwn 0;
}

/* Stawt stweaming */
static int imx258_stawt_stweaming(stwuct imx258 *imx258)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx258->sd);
	const stwuct imx258_weg_wist *weg_wist;
	int wet, wink_fweq_index;

	/* Setup PWW */
	wink_fweq_index = imx258->cuw_mode->wink_fweq_index;
	weg_wist = &wink_fweq_configs[wink_fweq_index].weg_wist;
	wet = imx258_wwite_wegs(imx258, weg_wist->wegs, weg_wist->num_of_wegs);
	if (wet) {
		dev_eww(&cwient->dev, "%s faiwed to set pwws\n", __func__);
		wetuwn wet;
	}

	/* Appwy defauwt vawues of cuwwent mode */
	weg_wist = &imx258->cuw_mode->weg_wist;
	wet = imx258_wwite_wegs(imx258, weg_wist->wegs, weg_wist->num_of_wegs);
	if (wet) {
		dev_eww(&cwient->dev, "%s faiwed to set mode\n", __func__);
		wetuwn wet;
	}

	/* Set Owientation be 180 degwee */
	wet = imx258_wwite_weg(imx258, WEG_MIWWOW_FWIP_CONTWOW,
			       IMX258_WEG_VAWUE_08BIT, WEG_CONFIG_MIWWOW_FWIP);
	if (wet) {
		dev_eww(&cwient->dev, "%s faiwed to set owientation\n",
			__func__);
		wetuwn wet;
	}

	/* Appwy customized vawues fwom usew */
	wet =  __v4w2_ctww_handwew_setup(imx258->sd.ctww_handwew);
	if (wet)
		wetuwn wet;

	/* set stweam on wegistew */
	wetuwn imx258_wwite_weg(imx258, IMX258_WEG_MODE_SEWECT,
				IMX258_WEG_VAWUE_08BIT,
				IMX258_MODE_STWEAMING);
}

/* Stop stweaming */
static int imx258_stop_stweaming(stwuct imx258 *imx258)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx258->sd);
	int wet;

	/* set stweam off wegistew */
	wet = imx258_wwite_weg(imx258, IMX258_WEG_MODE_SEWECT,
		IMX258_WEG_VAWUE_08BIT, IMX258_MODE_STANDBY);
	if (wet)
		dev_eww(&cwient->dev, "%s faiwed to set stweam\n", __func__);

	/*
	 * Wetuwn success even if it was an ewwow, as thewe is nothing the
	 * cawwew can do about it.
	 */
	wetuwn 0;
}

static int imx258_powew_on(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct imx258 *imx258 = to_imx258(sd);
	int wet;

	wet = cwk_pwepawe_enabwe(imx258->cwk);
	if (wet)
		dev_eww(dev, "faiwed to enabwe cwock\n");

	wetuwn wet;
}

static int imx258_powew_off(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct imx258 *imx258 = to_imx258(sd);

	cwk_disabwe_unpwepawe(imx258->cwk);

	wetuwn 0;
}

static int imx258_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct imx258 *imx258 = to_imx258(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet = 0;

	mutex_wock(&imx258->mutex);

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(&cwient->dev);
		if (wet < 0)
			goto eww_unwock;

		/*
		 * Appwy defauwt & customized vawues
		 * and then stawt stweaming.
		 */
		wet = imx258_stawt_stweaming(imx258);
		if (wet)
			goto eww_wpm_put;
	} ewse {
		imx258_stop_stweaming(imx258);
		pm_wuntime_put(&cwient->dev);
	}

	mutex_unwock(&imx258->mutex);

	wetuwn wet;

eww_wpm_put:
	pm_wuntime_put(&cwient->dev);
eww_unwock:
	mutex_unwock(&imx258->mutex);

	wetuwn wet;
}

/* Vewify chip ID */
static int imx258_identify_moduwe(stwuct imx258 *imx258)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx258->sd);
	int wet;
	u32 vaw;

	wet = imx258_wead_weg(imx258, IMX258_WEG_CHIP_ID,
			      IMX258_WEG_VAWUE_16BIT, &vaw);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to wead chip id %x\n",
			IMX258_CHIP_ID);
		wetuwn wet;
	}

	if (vaw != IMX258_CHIP_ID) {
		dev_eww(&cwient->dev, "chip id mismatch: %x!=%x\n",
			IMX258_CHIP_ID, vaw);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops imx258_video_ops = {
	.s_stweam = imx258_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops imx258_pad_ops = {
	.enum_mbus_code = imx258_enum_mbus_code,
	.get_fmt = imx258_get_pad_fowmat,
	.set_fmt = imx258_set_pad_fowmat,
	.enum_fwame_size = imx258_enum_fwame_size,
};

static const stwuct v4w2_subdev_ops imx258_subdev_ops = {
	.video = &imx258_video_ops,
	.pad = &imx258_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops imx258_intewnaw_ops = {
	.open = imx258_open,
};

/* Initiawize contwow handwews */
static int imx258_init_contwows(stwuct imx258 *imx258)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx258->sd);
	stwuct v4w2_fwnode_device_pwopewties pwops;
	stwuct v4w2_ctww_handwew *ctww_hdww;
	stwuct v4w2_ctww *vfwip, *hfwip;
	s64 vbwank_def;
	s64 vbwank_min;
	s64 pixew_wate_min;
	s64 pixew_wate_max;
	int wet;

	ctww_hdww = &imx258->ctww_handwew;
	wet = v4w2_ctww_handwew_init(ctww_hdww, 13);
	if (wet)
		wetuwn wet;

	mutex_init(&imx258->mutex);
	ctww_hdww->wock = &imx258->mutex;
	imx258->wink_fweq = v4w2_ctww_new_int_menu(ctww_hdww,
				&imx258_ctww_ops,
				V4W2_CID_WINK_FWEQ,
				AWWAY_SIZE(wink_fweq_menu_items) - 1,
				0,
				wink_fweq_menu_items);

	if (imx258->wink_fweq)
		imx258->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	/* The dwivew onwy suppowts one bayew owdew and fwips by defauwt. */
	hfwip = v4w2_ctww_new_std(ctww_hdww, &imx258_ctww_ops,
				  V4W2_CID_HFWIP, 1, 1, 1, 1);
	if (hfwip)
		hfwip->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	vfwip = v4w2_ctww_new_std(ctww_hdww, &imx258_ctww_ops,
				  V4W2_CID_VFWIP, 1, 1, 1, 1);
	if (vfwip)
		vfwip->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	pixew_wate_max = wink_fweq_to_pixew_wate(wink_fweq_menu_items[0]);
	pixew_wate_min = wink_fweq_to_pixew_wate(wink_fweq_menu_items[1]);
	/* By defauwt, PIXEW_WATE is wead onwy */
	imx258->pixew_wate = v4w2_ctww_new_std(ctww_hdww, &imx258_ctww_ops,
				V4W2_CID_PIXEW_WATE,
				pixew_wate_min, pixew_wate_max,
				1, pixew_wate_max);


	vbwank_def = imx258->cuw_mode->vts_def - imx258->cuw_mode->height;
	vbwank_min = imx258->cuw_mode->vts_min - imx258->cuw_mode->height;
	imx258->vbwank = v4w2_ctww_new_std(
				ctww_hdww, &imx258_ctww_ops, V4W2_CID_VBWANK,
				vbwank_min,
				IMX258_VTS_MAX - imx258->cuw_mode->height, 1,
				vbwank_def);

	if (imx258->vbwank)
		imx258->vbwank->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	imx258->hbwank = v4w2_ctww_new_std(
				ctww_hdww, &imx258_ctww_ops, V4W2_CID_HBWANK,
				IMX258_PPW_DEFAUWT - imx258->cuw_mode->width,
				IMX258_PPW_DEFAUWT - imx258->cuw_mode->width,
				1,
				IMX258_PPW_DEFAUWT - imx258->cuw_mode->width);

	if (imx258->hbwank)
		imx258->hbwank->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	imx258->exposuwe = v4w2_ctww_new_std(
				ctww_hdww, &imx258_ctww_ops,
				V4W2_CID_EXPOSUWE, IMX258_EXPOSUWE_MIN,
				IMX258_EXPOSUWE_MAX, IMX258_EXPOSUWE_STEP,
				IMX258_EXPOSUWE_DEFAUWT);

	v4w2_ctww_new_std(ctww_hdww, &imx258_ctww_ops, V4W2_CID_ANAWOGUE_GAIN,
				IMX258_ANA_GAIN_MIN, IMX258_ANA_GAIN_MAX,
				IMX258_ANA_GAIN_STEP, IMX258_ANA_GAIN_DEFAUWT);

	v4w2_ctww_new_std(ctww_hdww, &imx258_ctww_ops, V4W2_CID_DIGITAW_GAIN,
				IMX258_DGTW_GAIN_MIN, IMX258_DGTW_GAIN_MAX,
				IMX258_DGTW_GAIN_STEP,
				IMX258_DGTW_GAIN_DEFAUWT);

	v4w2_ctww_new_std(ctww_hdww, &imx258_ctww_ops, V4W2_CID_WIDE_DYNAMIC_WANGE,
				0, 1, 1, IMX258_HDW_WATIO_DEFAUWT);

	v4w2_ctww_new_std_menu_items(ctww_hdww, &imx258_ctww_ops,
				V4W2_CID_TEST_PATTEWN,
				AWWAY_SIZE(imx258_test_pattewn_menu) - 1,
				0, 0, imx258_test_pattewn_menu);

	if (ctww_hdww->ewwow) {
		wet = ctww_hdww->ewwow;
		dev_eww(&cwient->dev, "%s contwow init faiwed (%d)\n",
				__func__, wet);
		goto ewwow;
	}

	wet = v4w2_fwnode_device_pawse(&cwient->dev, &pwops);
	if (wet)
		goto ewwow;

	wet = v4w2_ctww_new_fwnode_pwopewties(ctww_hdww, &imx258_ctww_ops,
					      &pwops);
	if (wet)
		goto ewwow;

	imx258->sd.ctww_handwew = ctww_hdww;

	wetuwn 0;

ewwow:
	v4w2_ctww_handwew_fwee(ctww_hdww);
	mutex_destwoy(&imx258->mutex);

	wetuwn wet;
}

static void imx258_fwee_contwows(stwuct imx258 *imx258)
{
	v4w2_ctww_handwew_fwee(imx258->sd.ctww_handwew);
	mutex_destwoy(&imx258->mutex);
}

static int imx258_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct imx258 *imx258;
	int wet;
	u32 vaw = 0;

	imx258 = devm_kzawwoc(&cwient->dev, sizeof(*imx258), GFP_KEWNEW);
	if (!imx258)
		wetuwn -ENOMEM;

	imx258->cwk = devm_cwk_get_optionaw(&cwient->dev, NUWW);
	if (IS_EWW(imx258->cwk))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(imx258->cwk),
				     "ewwow getting cwock\n");
	if (!imx258->cwk) {
		dev_dbg(&cwient->dev,
			"no cwock pwovided, using cwock-fwequency pwopewty\n");

		device_pwopewty_wead_u32(&cwient->dev, "cwock-fwequency", &vaw);
	} ewse {
		vaw = cwk_get_wate(imx258->cwk);
	}
	if (vaw != IMX258_INPUT_CWOCK_FWEQ) {
		dev_eww(&cwient->dev, "input cwock fwequency not suppowted\n");
		wetuwn -EINVAW;
	}

	/* Initiawize subdev */
	v4w2_i2c_subdev_init(&imx258->sd, cwient, &imx258_subdev_ops);

	/* Wiww be powewed off via pm_wuntime_idwe */
	wet = imx258_powew_on(&cwient->dev);
	if (wet)
		wetuwn wet;

	/* Check moduwe identity */
	wet = imx258_identify_moduwe(imx258);
	if (wet)
		goto ewwow_identify;

	/* Set defauwt mode to max wesowution */
	imx258->cuw_mode = &suppowted_modes[0];

	wet = imx258_init_contwows(imx258);
	if (wet)
		goto ewwow_identify;

	/* Initiawize subdev */
	imx258->sd.intewnaw_ops = &imx258_intewnaw_ops;
	imx258->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	imx258->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;

	/* Initiawize souwce pad */
	imx258->pad.fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&imx258->sd.entity, 1, &imx258->pad);
	if (wet)
		goto ewwow_handwew_fwee;

	wet = v4w2_async_wegistew_subdev_sensow(&imx258->sd);
	if (wet < 0)
		goto ewwow_media_entity;

	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_idwe(&cwient->dev);

	wetuwn 0;

ewwow_media_entity:
	media_entity_cweanup(&imx258->sd.entity);

ewwow_handwew_fwee:
	imx258_fwee_contwows(imx258);

ewwow_identify:
	imx258_powew_off(&cwient->dev);

	wetuwn wet;
}

static void imx258_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct imx258 *imx258 = to_imx258(sd);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	imx258_fwee_contwows(imx258);

	pm_wuntime_disabwe(&cwient->dev);
	if (!pm_wuntime_status_suspended(&cwient->dev))
		imx258_powew_off(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
}

static const stwuct dev_pm_ops imx258_pm_ops = {
	SET_WUNTIME_PM_OPS(imx258_powew_off, imx258_powew_on, NUWW)
};

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id imx258_acpi_ids[] = {
	{ "SONY258A" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(acpi, imx258_acpi_ids);
#endif

static const stwuct of_device_id imx258_dt_ids[] = {
	{ .compatibwe = "sony,imx258" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx258_dt_ids);

static stwuct i2c_dwivew imx258_i2c_dwivew = {
	.dwivew = {
		.name = "imx258",
		.pm = &imx258_pm_ops,
		.acpi_match_tabwe = ACPI_PTW(imx258_acpi_ids),
		.of_match_tabwe	= imx258_dt_ids,
	},
	.pwobe = imx258_pwobe,
	.wemove = imx258_wemove,
};

moduwe_i2c_dwivew(imx258_i2c_dwivew);

MODUWE_AUTHOW("Yeh, Andy <andy.yeh@intew.com>");
MODUWE_AUTHOW("Chiang, Awan");
MODUWE_AUTHOW("Chen, Jason");
MODUWE_DESCWIPTION("Sony IMX258 sensow dwivew");
MODUWE_WICENSE("GPW v2");
