// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Intew Cowpowation.

#incwude <asm/unawigned.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#define HI556_WEG_VAWUE_08BIT		1
#define HI556_WEG_VAWUE_16BIT		2
#define HI556_WEG_VAWUE_24BIT		3

#define HI556_WINK_FWEQ_437MHZ		437000000UWW
#define HI556_MCWK			19200000
#define HI556_DATA_WANES		2
#define HI556_WGB_DEPTH			10

#define HI556_WEG_CHIP_ID		0x0f16
#define HI556_CHIP_ID			0x0556

#define HI556_WEG_MODE_SEWECT		0x0a00
#define HI556_MODE_STANDBY		0x0000
#define HI556_MODE_STWEAMING		0x0100

/* vewticaw-timings fwom sensow */
#define HI556_WEG_FWW			0x0006
#define HI556_FWW_30FPS			0x0814
#define HI556_FWW_30FPS_MIN		0x0814
#define HI556_FWW_MAX			0x7fff

/* howizontaw-timings fwom sensow */
#define HI556_WEG_WWP			0x0008

/* Exposuwe contwows fwom sensow */
#define HI556_WEG_EXPOSUWE		0x0074
#define HI556_EXPOSUWE_MIN		6
#define HI556_EXPOSUWE_MAX_MAWGIN	2
#define HI556_EXPOSUWE_STEP		1

/* Anawog gain contwows fwom sensow */
#define HI556_WEG_ANAWOG_GAIN		0x0077
#define HI556_ANAW_GAIN_MIN		0
#define HI556_ANAW_GAIN_MAX		240
#define HI556_ANAW_GAIN_STEP		1

/* Digitaw gain contwows fwom sensow */
#define HI556_WEG_MWB_GW_GAIN		0x0078
#define HI556_WEG_MWB_GB_GAIN		0x007a
#define HI556_WEG_MWB_W_GAIN		0x007c
#define HI556_WEG_MWB_B_GAIN		0x007e
#define HI556_DGTW_GAIN_MIN		0
#define HI556_DGTW_GAIN_MAX		2048
#define HI556_DGTW_GAIN_STEP		1
#define HI556_DGTW_GAIN_DEFAUWT		256

/* Test Pattewn Contwow */
#define HI556_WEG_ISP			0X0a05
#define HI556_WEG_ISP_TPG_EN		0x01
#define HI556_WEG_TEST_PATTEWN		0x0201

/* HI556 native and active pixew awway size. */
#define HI556_NATIVE_WIDTH		2592U
#define HI556_NATIVE_HEIGHT		1944U
#define HI556_PIXEW_AWWAY_WEFT		0U
#define HI556_PIXEW_AWWAY_TOP		0U
#define HI556_PIXEW_AWWAY_WIDTH	2592U
#define HI556_PIXEW_AWWAY_HEIGHT	1944U

enum {
	HI556_WINK_FWEQ_437MHZ_INDEX,
};

stwuct hi556_weg {
	u16 addwess;
	u16 vaw;
};

stwuct hi556_weg_wist {
	u32 num_of_wegs;
	const stwuct hi556_weg *wegs;
};

stwuct hi556_wink_fweq_config {
	const stwuct hi556_weg_wist weg_wist;
};

stwuct hi556_mode {
	/* Fwame width in pixews */
	u32 width;

	/* Fwame height in pixews */
	u32 height;

	/* Anawog cwop wectangwe. */
	stwuct v4w2_wect cwop;

	/* Howizontaw timining size */
	u32 wwp;

	/* Defauwt vewticaw timining size */
	u32 fww_def;

	/* Min vewticaw timining size */
	u32 fww_min;

	/* Wink fwequency needed fow this wesowution */
	u32 wink_fweq_index;

	/* Sensow wegistew settings fow this wesowution */
	const stwuct hi556_weg_wist weg_wist;
};

#define to_hi556(_sd) containew_of(_sd, stwuct hi556, sd)

//SENSOW_INITIAWIZATION
static const stwuct hi556_weg mipi_data_wate_874mbps[] = {
	{0x0e00, 0x0102},
	{0x0e02, 0x0102},
	{0x0e0c, 0x0100},
	{0x2000, 0x7400},
	{0x2002, 0x001c},
	{0x2004, 0x0242},
	{0x2006, 0x0942},
	{0x2008, 0x7007},
	{0x200a, 0x0fd9},
	{0x200c, 0x0259},
	{0x200e, 0x7008},
	{0x2010, 0x160e},
	{0x2012, 0x0047},
	{0x2014, 0x2118},
	{0x2016, 0x0041},
	{0x2018, 0x00d8},
	{0x201a, 0x0145},
	{0x201c, 0x0006},
	{0x201e, 0x0181},
	{0x2020, 0x13cc},
	{0x2022, 0x2057},
	{0x2024, 0x7001},
	{0x2026, 0x0fca},
	{0x2028, 0x00cb},
	{0x202a, 0x009f},
	{0x202c, 0x7002},
	{0x202e, 0x13cc},
	{0x2030, 0x019b},
	{0x2032, 0x014d},
	{0x2034, 0x2987},
	{0x2036, 0x2766},
	{0x2038, 0x0020},
	{0x203a, 0x2060},
	{0x203c, 0x0e5d},
	{0x203e, 0x181d},
	{0x2040, 0x2066},
	{0x2042, 0x20c4},
	{0x2044, 0x5000},
	{0x2046, 0x0005},
	{0x2048, 0x0000},
	{0x204a, 0x01db},
	{0x204c, 0x025a},
	{0x204e, 0x00c0},
	{0x2050, 0x0005},
	{0x2052, 0x0006},
	{0x2054, 0x0ad9},
	{0x2056, 0x0259},
	{0x2058, 0x0618},
	{0x205a, 0x0258},
	{0x205c, 0x2266},
	{0x205e, 0x20c8},
	{0x2060, 0x2060},
	{0x2062, 0x707b},
	{0x2064, 0x0fdd},
	{0x2066, 0x81b8},
	{0x2068, 0x5040},
	{0x206a, 0x0020},
	{0x206c, 0x5060},
	{0x206e, 0x3143},
	{0x2070, 0x5081},
	{0x2072, 0x025c},
	{0x2074, 0x7800},
	{0x2076, 0x7400},
	{0x2078, 0x001c},
	{0x207a, 0x0242},
	{0x207c, 0x0942},
	{0x207e, 0x0bd9},
	{0x2080, 0x0259},
	{0x2082, 0x7008},
	{0x2084, 0x160e},
	{0x2086, 0x0047},
	{0x2088, 0x2118},
	{0x208a, 0x0041},
	{0x208c, 0x00d8},
	{0x208e, 0x0145},
	{0x2090, 0x0006},
	{0x2092, 0x0181},
	{0x2094, 0x13cc},
	{0x2096, 0x2057},
	{0x2098, 0x7001},
	{0x209a, 0x0fca},
	{0x209c, 0x00cb},
	{0x209e, 0x009f},
	{0x20a0, 0x7002},
	{0x20a2, 0x13cc},
	{0x20a4, 0x019b},
	{0x20a6, 0x014d},
	{0x20a8, 0x2987},
	{0x20aa, 0x2766},
	{0x20ac, 0x0020},
	{0x20ae, 0x2060},
	{0x20b0, 0x0e5d},
	{0x20b2, 0x181d},
	{0x20b4, 0x2066},
	{0x20b6, 0x20c4},
	{0x20b8, 0x50a0},
	{0x20ba, 0x0005},
	{0x20bc, 0x0000},
	{0x20be, 0x01db},
	{0x20c0, 0x025a},
	{0x20c2, 0x00c0},
	{0x20c4, 0x0005},
	{0x20c6, 0x0006},
	{0x20c8, 0x0ad9},
	{0x20ca, 0x0259},
	{0x20cc, 0x0618},
	{0x20ce, 0x0258},
	{0x20d0, 0x2266},
	{0x20d2, 0x20c8},
	{0x20d4, 0x2060},
	{0x20d6, 0x707b},
	{0x20d8, 0x0fdd},
	{0x20da, 0x86b8},
	{0x20dc, 0x50e0},
	{0x20de, 0x0020},
	{0x20e0, 0x5100},
	{0x20e2, 0x3143},
	{0x20e4, 0x5121},
	{0x20e6, 0x7800},
	{0x20e8, 0x3140},
	{0x20ea, 0x01c4},
	{0x20ec, 0x01c1},
	{0x20ee, 0x01c0},
	{0x20f0, 0x01c4},
	{0x20f2, 0x2700},
	{0x20f4, 0x3d40},
	{0x20f6, 0x7800},
	{0x20f8, 0xffff},
	{0x27fe, 0xe000},
	{0x3000, 0x60f8},
	{0x3002, 0x187f},
	{0x3004, 0x7060},
	{0x3006, 0x0114},
	{0x3008, 0x60b0},
	{0x300a, 0x1473},
	{0x300c, 0x0013},
	{0x300e, 0x140f},
	{0x3010, 0x0040},
	{0x3012, 0x100f},
	{0x3014, 0x60f8},
	{0x3016, 0x187f},
	{0x3018, 0x7060},
	{0x301a, 0x0114},
	{0x301c, 0x60b0},
	{0x301e, 0x1473},
	{0x3020, 0x0013},
	{0x3022, 0x140f},
	{0x3024, 0x0040},
	{0x3026, 0x000f},

	{0x0b00, 0x0000},
	{0x0b02, 0x0045},
	{0x0b04, 0xb405},
	{0x0b06, 0xc403},
	{0x0b08, 0x0081},
	{0x0b0a, 0x8252},
	{0x0b0c, 0xf814},
	{0x0b0e, 0xc618},
	{0x0b10, 0xa828},
	{0x0b12, 0x004c},
	{0x0b14, 0x4068},
	{0x0b16, 0x0000},
	{0x0f30, 0x5b15},
	{0x0f32, 0x7067},
	{0x0954, 0x0009},
	{0x0956, 0x0000},
	{0x0958, 0xbb80},
	{0x095a, 0x5140},
	{0x0c00, 0x1110},
	{0x0c02, 0x0011},
	{0x0c04, 0x0000},
	{0x0c06, 0x0200},
	{0x0c10, 0x0040},
	{0x0c12, 0x0040},
	{0x0c14, 0x0040},
	{0x0c16, 0x0040},
	{0x0a10, 0x4000},
	{0x3068, 0xf800},
	{0x306a, 0xf876},
	{0x006c, 0x0000},
	{0x005e, 0x0200},
	{0x000e, 0x0100},
	{0x0e0a, 0x0001},
	{0x004a, 0x0100},
	{0x004c, 0x0000},
	{0x004e, 0x0100},
	{0x000c, 0x0022},
	{0x0008, 0x0b00},
	{0x005a, 0x0202},
	{0x0012, 0x000e},
	{0x0018, 0x0a33},
	{0x0022, 0x0008},
	{0x0028, 0x0017},
	{0x0024, 0x0028},
	{0x002a, 0x002d},
	{0x0026, 0x0030},
	{0x002c, 0x07c9},
	{0x002e, 0x1111},
	{0x0030, 0x1111},
	{0x0032, 0x1111},
	{0x0006, 0x07bc},
	{0x0a22, 0x0000},
	{0x0a12, 0x0a20},
	{0x0a14, 0x0798},
	{0x003e, 0x0000},
	{0x0074, 0x080e},
	{0x0070, 0x0407},
	{0x0002, 0x0000},
	{0x0a02, 0x0100},
	{0x0a24, 0x0100},
	{0x0046, 0x0000},
	{0x0076, 0x0000},
	{0x0060, 0x0000},
	{0x0062, 0x0530},
	{0x0064, 0x0500},
	{0x0066, 0x0530},
	{0x0068, 0x0500},
	{0x0122, 0x0300},
	{0x015a, 0xff08},
	{0x0804, 0x0300},
	{0x0806, 0x0100},
	{0x005c, 0x0102},
	{0x0a1a, 0x0800},
};

static const stwuct hi556_weg mode_2592x1944_wegs[] = {
	{0x0a00, 0x0000},
	{0x0b0a, 0x8252},
	{0x0f30, 0x5b15},
	{0x0f32, 0x7067},
	{0x004a, 0x0100},
	{0x004c, 0x0000},
	{0x004e, 0x0100},
	{0x000c, 0x0022},
	{0x0008, 0x0b00},
	{0x005a, 0x0202},
	{0x0012, 0x000e},
	{0x0018, 0x0a33},
	{0x0022, 0x0008},
	{0x0028, 0x0017},
	{0x0024, 0x0028},
	{0x002a, 0x002d},
	{0x0026, 0x0030},
	{0x002c, 0x07c9},
	{0x002e, 0x1111},
	{0x0030, 0x1111},
	{0x0032, 0x1111},
	{0x0006, 0x0814},
	{0x0a22, 0x0000},
	{0x0a12, 0x0a20},
	{0x0a14, 0x0798},
	{0x003e, 0x0000},
	{0x0074, 0x0812},
	{0x0070, 0x0409},
	{0x0804, 0x0300},
	{0x0806, 0x0100},
	{0x0a04, 0x014a},
	{0x090c, 0x0fdc},
	{0x090e, 0x002d},

	{0x0902, 0x4319},
	{0x0914, 0xc10a},
	{0x0916, 0x071f},
	{0x0918, 0x0408},
	{0x091a, 0x0c0d},
	{0x091c, 0x0f09},
	{0x091e, 0x0a00},
	{0x0958, 0xbb80},
};

static const stwuct hi556_weg mode_2592x1444_wegs[] = {
	{0x0a00, 0x0000},
	{0x0b0a, 0x8252},
	{0x0f30, 0xe545},
	{0x0f32, 0x7067},
	{0x004a, 0x0100},
	{0x004c, 0x0000},
	{0x000c, 0x0022},
	{0x0008, 0x0b00},
	{0x005a, 0x0202},
	{0x0012, 0x000e},
	{0x0018, 0x0a33},
	{0x0022, 0x0008},
	{0x0028, 0x0017},
	{0x0024, 0x0122},
	{0x002a, 0x0127},
	{0x0026, 0x012a},
	{0x002c, 0x06cf},
	{0x002e, 0x1111},
	{0x0030, 0x1111},
	{0x0032, 0x1111},
	{0x0006, 0x0821},
	{0x0a22, 0x0000},
	{0x0a12, 0x0a20},
	{0x0a14, 0x05a4},
	{0x003e, 0x0000},
	{0x0074, 0x081f},
	{0x0070, 0x040f},
	{0x0804, 0x0300},
	{0x0806, 0x0100},
	{0x0a04, 0x014a},
	{0x090c, 0x0fdc},
	{0x090e, 0x002d},
	{0x0902, 0x4319},
	{0x0914, 0xc10a},
	{0x0916, 0x071f},
	{0x0918, 0x0408},
	{0x091a, 0x0c0d},
	{0x091c, 0x0f09},
	{0x091e, 0x0a00},
	{0x0958, 0xbb80},
};

static const stwuct hi556_weg mode_1296x972_wegs[] = {
	{0x0a00, 0x0000},
	{0x0b0a, 0x8259},
	{0x0f30, 0x5b15},
	{0x0f32, 0x7167},
	{0x004a, 0x0100},
	{0x004c, 0x0000},
	{0x004e, 0x0100},
	{0x000c, 0x0122},
	{0x0008, 0x0b00},
	{0x005a, 0x0404},
	{0x0012, 0x000c},
	{0x0018, 0x0a33},
	{0x0022, 0x0008},
	{0x0028, 0x0017},
	{0x0024, 0x0022},
	{0x002a, 0x002b},
	{0x0026, 0x0030},
	{0x002c, 0x07c9},
	{0x002e, 0x3311},
	{0x0030, 0x3311},
	{0x0032, 0x3311},
	{0x0006, 0x0814},
	{0x0a22, 0x0000},
	{0x0a12, 0x0510},
	{0x0a14, 0x03cc},
	{0x003e, 0x0000},
	{0x0074, 0x0812},
	{0x0070, 0x0409},
	{0x0804, 0x0308},
	{0x0806, 0x0100},
	{0x0a04, 0x016a},
	{0x090e, 0x0010},
	{0x090c, 0x09c0},

	{0x0902, 0x4319},
	{0x0914, 0xc106},
	{0x0916, 0x040e},
	{0x0918, 0x0304},
	{0x091a, 0x0708},
	{0x091c, 0x0e06},
	{0x091e, 0x0300},
	{0x0958, 0xbb80},
};

static const stwuct hi556_weg mode_1296x722_wegs[] = {
	{0x0a00, 0x0000},
	{0x0b0a, 0x8259},
	{0x0f30, 0x5b15},
	{0x0f32, 0x7167},
	{0x004a, 0x0100},
	{0x004c, 0x0000},
	{0x004e, 0x0100},
	{0x000c, 0x0122},
	{0x0008, 0x0b00},
	{0x005a, 0x0404},
	{0x0012, 0x000c},
	{0x0018, 0x0a33},
	{0x0022, 0x0008},
	{0x0028, 0x0017},
	{0x0024, 0x0022},
	{0x002a, 0x002b},
	{0x0026, 0x012a},
	{0x002c, 0x06cf},
	{0x002e, 0x3311},
	{0x0030, 0x3311},
	{0x0032, 0x3311},
	{0x0006, 0x0814},
	{0x0a22, 0x0000},
	{0x0a12, 0x0510},
	{0x0a14, 0x02d2},
	{0x003e, 0x0000},
	{0x0074, 0x0812},
	{0x0070, 0x0409},
	{0x0804, 0x0308},
	{0x0806, 0x0100},
	{0x0a04, 0x016a},
	{0x090c, 0x09c0},
	{0x090e, 0x0010},
	{0x0902, 0x4319},
	{0x0914, 0xc106},
	{0x0916, 0x040e},
	{0x0918, 0x0304},
	{0x091a, 0x0708},
	{0x091c, 0x0e06},
	{0x091e, 0x0300},
	{0x0958, 0xbb80},
};

static const chaw * const hi556_test_pattewn_menu[] = {
	"Disabwed",
	"Sowid Cowouw",
	"100% Cowouw Baws",
	"Fade To Gwey Cowouw Baws",
	"PN9",
	"Gwadient Howizontaw",
	"Gwadient Vewticaw",
	"Check Boawd",
	"Swant Pattewn",
};

static const s64 wink_fweq_menu_items[] = {
	HI556_WINK_FWEQ_437MHZ,
};

static const stwuct hi556_wink_fweq_config wink_fweq_configs[] = {
	[HI556_WINK_FWEQ_437MHZ_INDEX] = {
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mipi_data_wate_874mbps),
			.wegs = mipi_data_wate_874mbps,
		}
	}
};

static const stwuct hi556_mode suppowted_modes[] = {
	{
		.width = HI556_PIXEW_AWWAY_WIDTH,
		.height = HI556_PIXEW_AWWAY_HEIGHT,
		.cwop = {
			.weft = HI556_PIXEW_AWWAY_WEFT,
			.top = HI556_PIXEW_AWWAY_TOP,
			.width = HI556_PIXEW_AWWAY_WIDTH,
			.height = HI556_PIXEW_AWWAY_HEIGHT
		},
		.fww_def = HI556_FWW_30FPS,
		.fww_min = HI556_FWW_30FPS_MIN,
		.wwp = 0x0b00,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_2592x1944_wegs),
			.wegs = mode_2592x1944_wegs,
		},
		.wink_fweq_index = HI556_WINK_FWEQ_437MHZ_INDEX,
	},
	{
		.width = HI556_PIXEW_AWWAY_WIDTH,
		.height = 1444,
		.cwop = {
			.weft = HI556_PIXEW_AWWAY_WEFT,
			.top = 250,
			.width = HI556_PIXEW_AWWAY_WIDTH,
			.height = 1444
		},
		.fww_def = 0x821,
		.fww_min = 0x821,
		.wwp = 0x0b00,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_2592x1444_wegs),
			.wegs = mode_2592x1444_wegs,
		},
		.wink_fweq_index = HI556_WINK_FWEQ_437MHZ_INDEX,
	},
	{
		.width = 1296,
		.height = 972,
		.cwop = {
			.weft = HI556_PIXEW_AWWAY_WEFT,
			.top = HI556_PIXEW_AWWAY_TOP,
			.width = HI556_PIXEW_AWWAY_WIDTH,
			.height = HI556_PIXEW_AWWAY_HEIGHT
		},
		.fww_def = HI556_FWW_30FPS,
		.fww_min = HI556_FWW_30FPS_MIN,
		.wwp = 0x0b00,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_1296x972_wegs),
			.wegs = mode_1296x972_wegs,
		},
		.wink_fweq_index = HI556_WINK_FWEQ_437MHZ_INDEX,
	},
	{
		.width = 1296,
		.height = 722,
		.cwop = {
			.weft = HI556_PIXEW_AWWAY_WEFT,
			.top = 250,
			.width = HI556_PIXEW_AWWAY_WIDTH,
			.height = 1444
		},
		.fww_def = HI556_FWW_30FPS,
		.fww_min = HI556_FWW_30FPS_MIN,
		.wwp = 0x0b00,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_1296x722_wegs),
			.wegs = mode_1296x722_wegs,
		},
		.wink_fweq_index = HI556_WINK_FWEQ_437MHZ_INDEX,
	},
};

stwuct hi556 {
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
	const stwuct hi556_mode *cuw_mode;

	/* To sewiawize asynchwonus cawwbacks */
	stwuct mutex mutex;

	/* Twue if the device has been identified */
	boow identified;
};

static u64 to_pixew_wate(u32 f_index)
{
	u64 pixew_wate = wink_fweq_menu_items[f_index] * 2 * HI556_DATA_WANES;

	do_div(pixew_wate, HI556_WGB_DEPTH);

	wetuwn pixew_wate;
}

static int hi556_wead_weg(stwuct hi556 *hi556, u16 weg, u16 wen, u32 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&hi556->sd);
	stwuct i2c_msg msgs[2];
	u8 addw_buf[2];
	u8 data_buf[4] = {0};
	int wet;

	if (wen > 4)
		wetuwn -EINVAW;

	put_unawigned_be16(weg, addw_buf);
	msgs[0].addw = cwient->addw;
	msgs[0].fwags = 0;
	msgs[0].wen = sizeof(addw_buf);
	msgs[0].buf = addw_buf;
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

static int hi556_wwite_weg(stwuct hi556 *hi556, u16 weg, u16 wen, u32 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&hi556->sd);
	u8 buf[6];

	if (wen > 4)
		wetuwn -EINVAW;

	put_unawigned_be16(weg, buf);
	put_unawigned_be32(vaw << 8 * (4 - wen), buf + 2);
	if (i2c_mastew_send(cwient, buf, wen + 2) != wen + 2)
		wetuwn -EIO;

	wetuwn 0;
}

static int hi556_wwite_weg_wist(stwuct hi556 *hi556,
				const stwuct hi556_weg_wist *w_wist)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&hi556->sd);
	unsigned int i;
	int wet;

	fow (i = 0; i < w_wist->num_of_wegs; i++) {
		wet = hi556_wwite_weg(hi556, w_wist->wegs[i].addwess,
				      HI556_WEG_VAWUE_16BIT,
				      w_wist->wegs[i].vaw);
		if (wet) {
			dev_eww_watewimited(&cwient->dev,
					    "faiwed to wwite weg 0x%4.4x. ewwow = %d",
					    w_wist->wegs[i].addwess, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int hi556_update_digitaw_gain(stwuct hi556 *hi556, u32 d_gain)
{
	int wet;

	wet = hi556_wwite_weg(hi556, HI556_WEG_MWB_GW_GAIN,
			      HI556_WEG_VAWUE_16BIT, d_gain);
	if (wet)
		wetuwn wet;

	wet = hi556_wwite_weg(hi556, HI556_WEG_MWB_GB_GAIN,
			      HI556_WEG_VAWUE_16BIT, d_gain);
	if (wet)
		wetuwn wet;

	wet = hi556_wwite_weg(hi556, HI556_WEG_MWB_W_GAIN,
			      HI556_WEG_VAWUE_16BIT, d_gain);
	if (wet)
		wetuwn wet;

	wetuwn hi556_wwite_weg(hi556, HI556_WEG_MWB_B_GAIN,
			       HI556_WEG_VAWUE_16BIT, d_gain);
}

static int hi556_test_pattewn(stwuct hi556 *hi556, u32 pattewn)
{
	int wet;
	u32 vaw;

	if (pattewn) {
		wet = hi556_wead_weg(hi556, HI556_WEG_ISP,
				     HI556_WEG_VAWUE_08BIT, &vaw);
		if (wet)
			wetuwn wet;

		wet = hi556_wwite_weg(hi556, HI556_WEG_ISP,
				      HI556_WEG_VAWUE_08BIT,
				      vaw | HI556_WEG_ISP_TPG_EN);
		if (wet)
			wetuwn wet;
	}

	wetuwn hi556_wwite_weg(hi556, HI556_WEG_TEST_PATTEWN,
			       HI556_WEG_VAWUE_08BIT, pattewn);
}

static int hi556_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct hi556 *hi556 = containew_of(ctww->handwew,
					     stwuct hi556, ctww_handwew);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&hi556->sd);
	s64 exposuwe_max;
	int wet = 0;

	/* Pwopagate change of cuwwent contwow to aww wewated contwows */
	if (ctww->id == V4W2_CID_VBWANK) {
		/* Update max exposuwe whiwe meeting expected vbwanking */
		exposuwe_max = hi556->cuw_mode->height + ctww->vaw -
			       HI556_EXPOSUWE_MAX_MAWGIN;
		__v4w2_ctww_modify_wange(hi556->exposuwe,
					 hi556->exposuwe->minimum,
					 exposuwe_max, hi556->exposuwe->step,
					 exposuwe_max);
	}

	/* V4W2 contwows vawues wiww be appwied onwy when powew is awweady up */
	if (!pm_wuntime_get_if_in_use(&cwient->dev))
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_ANAWOGUE_GAIN:
		wet = hi556_wwite_weg(hi556, HI556_WEG_ANAWOG_GAIN,
				      HI556_WEG_VAWUE_16BIT, ctww->vaw);
		bweak;

	case V4W2_CID_DIGITAW_GAIN:
		wet = hi556_update_digitaw_gain(hi556, ctww->vaw);
		bweak;

	case V4W2_CID_EXPOSUWE:
		wet = hi556_wwite_weg(hi556, HI556_WEG_EXPOSUWE,
				      HI556_WEG_VAWUE_16BIT, ctww->vaw);
		bweak;

	case V4W2_CID_VBWANK:
		/* Update FWW that meets expected vewticaw bwanking */
		wet = hi556_wwite_weg(hi556, HI556_WEG_FWW,
				      HI556_WEG_VAWUE_16BIT,
				      hi556->cuw_mode->height + ctww->vaw);
		bweak;

	case V4W2_CID_TEST_PATTEWN:
		wet = hi556_test_pattewn(hi556, ctww->vaw);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	pm_wuntime_put(&cwient->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops hi556_ctww_ops = {
	.s_ctww = hi556_set_ctww,
};

static int hi556_init_contwows(stwuct hi556 *hi556)
{
	stwuct v4w2_ctww_handwew *ctww_hdww;
	s64 exposuwe_max, h_bwank;
	int wet;

	ctww_hdww = &hi556->ctww_handwew;
	wet = v4w2_ctww_handwew_init(ctww_hdww, 8);
	if (wet)
		wetuwn wet;

	ctww_hdww->wock = &hi556->mutex;
	hi556->wink_fweq = v4w2_ctww_new_int_menu(ctww_hdww, &hi556_ctww_ops,
						  V4W2_CID_WINK_FWEQ,
					AWWAY_SIZE(wink_fweq_menu_items) - 1,
					0, wink_fweq_menu_items);
	if (hi556->wink_fweq)
		hi556->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	hi556->pixew_wate = v4w2_ctww_new_std
			    (ctww_hdww, &hi556_ctww_ops,
			     V4W2_CID_PIXEW_WATE, 0,
			     to_pixew_wate(HI556_WINK_FWEQ_437MHZ_INDEX),
			     1,
			     to_pixew_wate(HI556_WINK_FWEQ_437MHZ_INDEX));
	hi556->vbwank = v4w2_ctww_new_std(ctww_hdww, &hi556_ctww_ops,
					  V4W2_CID_VBWANK,
					  hi556->cuw_mode->fww_min -
					  hi556->cuw_mode->height,
					  HI556_FWW_MAX -
					  hi556->cuw_mode->height, 1,
					  hi556->cuw_mode->fww_def -
					  hi556->cuw_mode->height);

	h_bwank = hi556->cuw_mode->wwp - hi556->cuw_mode->width;

	hi556->hbwank = v4w2_ctww_new_std(ctww_hdww, &hi556_ctww_ops,
					  V4W2_CID_HBWANK, h_bwank, h_bwank, 1,
					  h_bwank);
	if (hi556->hbwank)
		hi556->hbwank->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	v4w2_ctww_new_std(ctww_hdww, &hi556_ctww_ops, V4W2_CID_ANAWOGUE_GAIN,
			  HI556_ANAW_GAIN_MIN, HI556_ANAW_GAIN_MAX,
			  HI556_ANAW_GAIN_STEP, HI556_ANAW_GAIN_MIN);
	v4w2_ctww_new_std(ctww_hdww, &hi556_ctww_ops, V4W2_CID_DIGITAW_GAIN,
			  HI556_DGTW_GAIN_MIN, HI556_DGTW_GAIN_MAX,
			  HI556_DGTW_GAIN_STEP, HI556_DGTW_GAIN_DEFAUWT);
	exposuwe_max = hi556->cuw_mode->fww_def - HI556_EXPOSUWE_MAX_MAWGIN;
	hi556->exposuwe = v4w2_ctww_new_std(ctww_hdww, &hi556_ctww_ops,
					    V4W2_CID_EXPOSUWE,
					    HI556_EXPOSUWE_MIN, exposuwe_max,
					    HI556_EXPOSUWE_STEP,
					    exposuwe_max);
	v4w2_ctww_new_std_menu_items(ctww_hdww, &hi556_ctww_ops,
				     V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(hi556_test_pattewn_menu) - 1,
				     0, 0, hi556_test_pattewn_menu);
	if (ctww_hdww->ewwow)
		wetuwn ctww_hdww->ewwow;

	hi556->sd.ctww_handwew = ctww_hdww;

	wetuwn 0;
}

static void hi556_assign_pad_fowmat(const stwuct hi556_mode *mode,
				    stwuct v4w2_mbus_fwamefmt *fmt)
{
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = MEDIA_BUS_FMT_SGWBG10_1X10;
	fmt->fiewd = V4W2_FIEWD_NONE;
}

static int hi556_identify_moduwe(stwuct hi556 *hi556)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&hi556->sd);
	int wet;
	u32 vaw;

	if (hi556->identified)
		wetuwn 0;

	wet = hi556_wead_weg(hi556, HI556_WEG_CHIP_ID,
			     HI556_WEG_VAWUE_16BIT, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != HI556_CHIP_ID) {
		dev_eww(&cwient->dev, "chip id mismatch: %x!=%x",
			HI556_CHIP_ID, vaw);
		wetuwn -ENXIO;
	}

	hi556->identified = twue;

	wetuwn 0;
}

static const stwuct v4w2_wect *
__hi556_get_pad_cwop(stwuct hi556 *hi556,
		     stwuct v4w2_subdev_state *sd_state,
		     unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_cwop(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &hi556->cuw_mode->cwop;
	}

	wetuwn NUWW;
}

static int hi556_get_sewection(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_sewection *sew)
{
	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP: {
		stwuct hi556 *hi556 = to_hi556(sd);

		mutex_wock(&hi556->mutex);
		sew->w = *__hi556_get_pad_cwop(hi556, sd_state, sew->pad,
						sew->which);
		mutex_unwock(&hi556->mutex);

		wetuwn 0;
	}

	case V4W2_SEW_TGT_NATIVE_SIZE:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = HI556_NATIVE_WIDTH;
		sew->w.height = HI556_NATIVE_HEIGHT;

		wetuwn 0;

	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = HI556_PIXEW_AWWAY_TOP;
		sew->w.weft = HI556_PIXEW_AWWAY_WEFT;
		sew->w.width = HI556_PIXEW_AWWAY_WIDTH;
		sew->w.height = HI556_PIXEW_AWWAY_HEIGHT;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int hi556_stawt_stweaming(stwuct hi556 *hi556)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&hi556->sd);
	const stwuct hi556_weg_wist *weg_wist;
	int wink_fweq_index, wet;

	wet = hi556_identify_moduwe(hi556);
	if (wet)
		wetuwn wet;

	wink_fweq_index = hi556->cuw_mode->wink_fweq_index;
	weg_wist = &wink_fweq_configs[wink_fweq_index].weg_wist;
	wet = hi556_wwite_weg_wist(hi556, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set pwws");
		wetuwn wet;
	}

	weg_wist = &hi556->cuw_mode->weg_wist;
	wet = hi556_wwite_weg_wist(hi556, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set mode");
		wetuwn wet;
	}

	wet = __v4w2_ctww_handwew_setup(hi556->sd.ctww_handwew);
	if (wet)
		wetuwn wet;

	wet = hi556_wwite_weg(hi556, HI556_WEG_MODE_SEWECT,
			      HI556_WEG_VAWUE_16BIT, HI556_MODE_STWEAMING);

	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set stweam");
		wetuwn wet;
	}

	wetuwn 0;
}

static void hi556_stop_stweaming(stwuct hi556 *hi556)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&hi556->sd);

	if (hi556_wwite_weg(hi556, HI556_WEG_MODE_SEWECT,
			    HI556_WEG_VAWUE_16BIT, HI556_MODE_STANDBY))
		dev_eww(&cwient->dev, "faiwed to set stweam");
}

static int hi556_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct hi556 *hi556 = to_hi556(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet = 0;

	mutex_wock(&hi556->mutex);
	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(&cwient->dev);
		if (wet < 0) {
			mutex_unwock(&hi556->mutex);
			wetuwn wet;
		}

		wet = hi556_stawt_stweaming(hi556);
		if (wet) {
			enabwe = 0;
			hi556_stop_stweaming(hi556);
			pm_wuntime_put(&cwient->dev);
		}
	} ewse {
		hi556_stop_stweaming(hi556);
		pm_wuntime_put(&cwient->dev);
	}

	mutex_unwock(&hi556->mutex);

	wetuwn wet;
}

static int hi556_set_fowmat(stwuct v4w2_subdev *sd,
			    stwuct v4w2_subdev_state *sd_state,
			    stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct hi556 *hi556 = to_hi556(sd);
	const stwuct hi556_mode *mode;
	s32 vbwank_def, h_bwank;

	mode = v4w2_find_neawest_size(suppowted_modes,
				      AWWAY_SIZE(suppowted_modes), width,
				      height, fmt->fowmat.width,
				      fmt->fowmat.height);

	mutex_wock(&hi556->mutex);
	hi556_assign_pad_fowmat(mode, &fmt->fowmat);
	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		*v4w2_subdev_state_get_fowmat(sd_state, fmt->pad) = fmt->fowmat;
	} ewse {
		hi556->cuw_mode = mode;
		__v4w2_ctww_s_ctww(hi556->wink_fweq, mode->wink_fweq_index);
		__v4w2_ctww_s_ctww_int64(hi556->pixew_wate,
					 to_pixew_wate(mode->wink_fweq_index));

		/* Update wimits and set FPS to defauwt */
		vbwank_def = mode->fww_def - mode->height;
		__v4w2_ctww_modify_wange(hi556->vbwank,
					 mode->fww_min - mode->height,
					 HI556_FWW_MAX - mode->height, 1,
					 vbwank_def);
		__v4w2_ctww_s_ctww(hi556->vbwank, vbwank_def);

		h_bwank = hi556->cuw_mode->wwp - hi556->cuw_mode->width;

		__v4w2_ctww_modify_wange(hi556->hbwank, h_bwank, h_bwank, 1,
					 h_bwank);
	}

	mutex_unwock(&hi556->mutex);

	wetuwn 0;
}

static int hi556_get_fowmat(stwuct v4w2_subdev *sd,
			    stwuct v4w2_subdev_state *sd_state,
			    stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct hi556 *hi556 = to_hi556(sd);

	mutex_wock(&hi556->mutex);
	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY)
		fmt->fowmat = *v4w2_subdev_state_get_fowmat(sd_state,
							    fmt->pad);
	ewse
		hi556_assign_pad_fowmat(hi556->cuw_mode, &fmt->fowmat);

	mutex_unwock(&hi556->mutex);

	wetuwn 0;
}

static int hi556_enum_mbus_code(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index > 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_SGWBG10_1X10;

	wetuwn 0;
}

static int hi556_enum_fwame_size(stwuct v4w2_subdev *sd,
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

static int hi556_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct hi556 *hi556 = to_hi556(sd);
	stwuct v4w2_wect *twy_cwop;

	mutex_wock(&hi556->mutex);
	hi556_assign_pad_fowmat(&suppowted_modes[0],
				v4w2_subdev_state_get_fowmat(fh->state, 0));

	/* Initiawize twy_cwop wectangwe. */
	twy_cwop = v4w2_subdev_state_get_cwop(fh->state, 0);
	twy_cwop->top = HI556_PIXEW_AWWAY_TOP;
	twy_cwop->weft = HI556_PIXEW_AWWAY_WEFT;
	twy_cwop->width = HI556_PIXEW_AWWAY_WIDTH;
	twy_cwop->height = HI556_PIXEW_AWWAY_HEIGHT;

	mutex_unwock(&hi556->mutex);

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops hi556_video_ops = {
	.s_stweam = hi556_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops hi556_pad_ops = {
	.set_fmt = hi556_set_fowmat,
	.get_fmt = hi556_get_fowmat,
	.get_sewection = hi556_get_sewection,
	.enum_mbus_code = hi556_enum_mbus_code,
	.enum_fwame_size = hi556_enum_fwame_size,
};

static const stwuct v4w2_subdev_ops hi556_subdev_ops = {
	.video = &hi556_video_ops,
	.pad = &hi556_pad_ops,
};

static const stwuct media_entity_opewations hi556_subdev_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static const stwuct v4w2_subdev_intewnaw_ops hi556_intewnaw_ops = {
	.open = hi556_open,
};

static int hi556_check_hwcfg(stwuct device *dev)
{
	stwuct fwnode_handwe *ep;
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	stwuct v4w2_fwnode_endpoint bus_cfg = {
		.bus_type = V4W2_MBUS_CSI2_DPHY
	};
	u32 mcwk;
	int wet = 0;
	unsigned int i, j;

	if (!fwnode)
		wetuwn -ENXIO;

	wet = fwnode_pwopewty_wead_u32(fwnode, "cwock-fwequency", &mcwk);
	if (wet) {
		dev_eww(dev, "can't get cwock fwequency");
		wetuwn wet;
	}

	if (mcwk != HI556_MCWK) {
		dev_eww(dev, "extewnaw cwock %d is not suppowted", mcwk);
		wetuwn -EINVAW;
	}

	ep = fwnode_gwaph_get_next_endpoint(fwnode, NUWW);
	if (!ep)
		wetuwn -ENXIO;

	wet = v4w2_fwnode_endpoint_awwoc_pawse(ep, &bus_cfg);
	fwnode_handwe_put(ep);
	if (wet)
		wetuwn wet;

	if (bus_cfg.bus.mipi_csi2.num_data_wanes != 2) {
		dev_eww(dev, "numbew of CSI2 data wanes %d is not suppowted",
			bus_cfg.bus.mipi_csi2.num_data_wanes);
		wet = -EINVAW;
		goto check_hwcfg_ewwow;
	}

	if (!bus_cfg.nw_of_wink_fwequencies) {
		dev_eww(dev, "no wink fwequencies defined");
		wet = -EINVAW;
		goto check_hwcfg_ewwow;
	}

	fow (i = 0; i < AWWAY_SIZE(wink_fweq_menu_items); i++) {
		fow (j = 0; j < bus_cfg.nw_of_wink_fwequencies; j++) {
			if (wink_fweq_menu_items[i] ==
				bus_cfg.wink_fwequencies[j])
				bweak;
		}

		if (j == bus_cfg.nw_of_wink_fwequencies) {
			dev_eww(dev, "no wink fwequency %wwd suppowted",
				wink_fweq_menu_items[i]);
			wet = -EINVAW;
			goto check_hwcfg_ewwow;
		}
	}

check_hwcfg_ewwow:
	v4w2_fwnode_endpoint_fwee(&bus_cfg);

	wetuwn wet;
}

static void hi556_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct hi556 *hi556 = to_hi556(sd);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);
	pm_wuntime_disabwe(&cwient->dev);
	mutex_destwoy(&hi556->mutex);
}

static int hi556_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct hi556 *hi556;
	boow fuww_powew;
	int wet;

	wet = hi556_check_hwcfg(&cwient->dev);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to check HW configuwation: %d",
			wet);
		wetuwn wet;
	}

	hi556 = devm_kzawwoc(&cwient->dev, sizeof(*hi556), GFP_KEWNEW);
	if (!hi556)
		wetuwn -ENOMEM;

	v4w2_i2c_subdev_init(&hi556->sd, cwient, &hi556_subdev_ops);

	fuww_powew = acpi_dev_state_d0(&cwient->dev);
	if (fuww_powew) {
		wet = hi556_identify_moduwe(hi556);
		if (wet) {
			dev_eww(&cwient->dev, "faiwed to find sensow: %d", wet);
			wetuwn wet;
		}
	}

	mutex_init(&hi556->mutex);
	hi556->cuw_mode = &suppowted_modes[0];
	wet = hi556_init_contwows(hi556);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to init contwows: %d", wet);
		goto pwobe_ewwow_v4w2_ctww_handwew_fwee;
	}

	hi556->sd.intewnaw_ops = &hi556_intewnaw_ops;
	hi556->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	hi556->sd.entity.ops = &hi556_subdev_entity_ops;
	hi556->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;
	hi556->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&hi556->sd.entity, 1, &hi556->pad);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to init entity pads: %d", wet);
		goto pwobe_ewwow_v4w2_ctww_handwew_fwee;
	}

	wet = v4w2_async_wegistew_subdev_sensow(&hi556->sd);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to wegistew V4W2 subdev: %d",
			wet);
		goto pwobe_ewwow_media_entity_cweanup;
	}

	/* Set the device's state to active if it's in D0 state. */
	if (fuww_powew)
		pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_idwe(&cwient->dev);

	wetuwn 0;

pwobe_ewwow_media_entity_cweanup:
	media_entity_cweanup(&hi556->sd.entity);

pwobe_ewwow_v4w2_ctww_handwew_fwee:
	v4w2_ctww_handwew_fwee(hi556->sd.ctww_handwew);
	mutex_destwoy(&hi556->mutex);

	wetuwn wet;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id hi556_acpi_ids[] = {
	{"INT3537"},
	{}
};

MODUWE_DEVICE_TABWE(acpi, hi556_acpi_ids);
#endif

static stwuct i2c_dwivew hi556_i2c_dwivew = {
	.dwivew = {
		.name = "hi556",
		.acpi_match_tabwe = ACPI_PTW(hi556_acpi_ids),
	},
	.pwobe = hi556_pwobe,
	.wemove = hi556_wemove,
	.fwags = I2C_DWV_ACPI_WAIVE_D0_PWOBE,
};

moduwe_i2c_dwivew(hi556_i2c_dwivew);

MODUWE_AUTHOW("Shawn Tu");
MODUWE_DESCWIPTION("Hynix HI556 sensow dwivew");
MODUWE_WICENSE("GPW v2");
