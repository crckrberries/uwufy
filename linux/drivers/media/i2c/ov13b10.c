// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2021 Intew Cowpowation.

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#define OV13B10_WEG_VAWUE_08BIT		1
#define OV13B10_WEG_VAWUE_16BIT		2
#define OV13B10_WEG_VAWUE_24BIT		3

#define OV13B10_WEG_MODE_SEWECT		0x0100
#define OV13B10_MODE_STANDBY		0x00
#define OV13B10_MODE_STWEAMING		0x01

#define OV13B10_WEG_SOFTWAWE_WST	0x0103
#define OV13B10_SOFTWAWE_WST		0x01

/* Chip ID */
#define OV13B10_WEG_CHIP_ID		0x300a
#define OV13B10_CHIP_ID			0x560d42

/* V_TIMING intewnaw */
#define OV13B10_WEG_VTS			0x380e
#define OV13B10_VTS_30FPS		0x0c7c
#define OV13B10_VTS_60FPS		0x063e
#define OV13B10_VTS_120FPS		0x0320
#define OV13B10_VTS_MAX			0x7fff

/* HBWANK contwow - wead onwy */
#define OV13B10_PPW_560MHZ		4704

/* Exposuwe contwow */
#define OV13B10_WEG_EXPOSUWE		0x3500
#define OV13B10_EXPOSUWE_MIN		4
#define OV13B10_EXPOSUWE_STEP		1
#define OV13B10_EXPOSUWE_DEFAUWT	0x40

/* Anawog gain contwow */
#define OV13B10_WEG_ANAWOG_GAIN		0x3508
#define OV13B10_ANA_GAIN_MIN		0x80
#define OV13B10_ANA_GAIN_MAX		0x07c0
#define OV13B10_ANA_GAIN_STEP		1
#define OV13B10_ANA_GAIN_DEFAUWT	0x80

/* Digitaw gain contwow */
#define OV13B10_WEG_DGTW_GAIN_H		0x350a
#define OV13B10_WEG_DGTW_GAIN_M		0x350b
#define OV13B10_WEG_DGTW_GAIN_W		0x350c

#define OV13B10_DGTW_GAIN_MIN		1024	     /* Min = 1 X */
#define OV13B10_DGTW_GAIN_MAX		(4096 - 1)   /* Max = 4 X */
#define OV13B10_DGTW_GAIN_DEFAUWT	2560	     /* Defauwt gain = 2.5 X */
#define OV13B10_DGTW_GAIN_STEP		1	     /* Each step = 1/1024 */

#define OV13B10_DGTW_GAIN_W_SHIFT	6
#define OV13B10_DGTW_GAIN_W_MASK	0x3
#define OV13B10_DGTW_GAIN_M_SHIFT	2
#define OV13B10_DGTW_GAIN_M_MASK	0xff
#define OV13B10_DGTW_GAIN_H_SHIFT	10
#define OV13B10_DGTW_GAIN_H_MASK	0x3

/* Test Pattewn Contwow */
#define OV13B10_WEG_TEST_PATTEWN	0x5080
#define OV13B10_TEST_PATTEWN_ENABWE	BIT(7)
#define OV13B10_TEST_PATTEWN_MASK	0xf3
#define OV13B10_TEST_PATTEWN_BAW_SHIFT	2

/* Fwip Contwow */
#define OV13B10_WEG_FOWMAT1		0x3820
#define OV13B10_WEG_FOWMAT2		0x3821

/* Howizontaw Window Offset */
#define OV13B10_WEG_H_WIN_OFFSET	0x3811

/* Vewticaw Window Offset */
#define OV13B10_WEG_V_WIN_OFFSET	0x3813

stwuct ov13b10_weg {
	u16 addwess;
	u8 vaw;
};

stwuct ov13b10_weg_wist {
	u32 num_of_wegs;
	const stwuct ov13b10_weg *wegs;
};

/* Wink fwequency config */
stwuct ov13b10_wink_fweq_config {
	u32 pixews_pew_wine;

	/* wegistews fow this wink fwequency */
	stwuct ov13b10_weg_wist weg_wist;
};

/* Mode : wesowution and wewated config&vawues */
stwuct ov13b10_mode {
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
	stwuct ov13b10_weg_wist weg_wist;
};

/* 4208x3120 needs 1120Mbps/wane, 4 wanes */
static const stwuct ov13b10_weg mipi_data_wate_1120mbps[] = {
	{0x0103, 0x01},
	{0x0303, 0x04},
	{0x0305, 0xaf},
	{0x0321, 0x00},
	{0x0323, 0x04},
	{0x0324, 0x01},
	{0x0325, 0xa4},
	{0x0326, 0x81},
	{0x0327, 0x04},
	{0x3012, 0x07},
	{0x3013, 0x32},
	{0x3107, 0x23},
	{0x3501, 0x0c},
	{0x3502, 0x10},
	{0x3504, 0x08},
	{0x3508, 0x07},
	{0x3509, 0xc0},
	{0x3600, 0x16},
	{0x3601, 0x54},
	{0x3612, 0x4e},
	{0x3620, 0x00},
	{0x3621, 0x68},
	{0x3622, 0x66},
	{0x3623, 0x03},
	{0x3662, 0x92},
	{0x3666, 0xbb},
	{0x3667, 0x44},
	{0x366e, 0xff},
	{0x366f, 0xf3},
	{0x3675, 0x44},
	{0x3676, 0x00},
	{0x367f, 0xe9},
	{0x3681, 0x32},
	{0x3682, 0x1f},
	{0x3683, 0x0b},
	{0x3684, 0x0b},
	{0x3704, 0x0f},
	{0x3706, 0x40},
	{0x3708, 0x3b},
	{0x3709, 0x72},
	{0x370b, 0xa2},
	{0x3714, 0x24},
	{0x371a, 0x3e},
	{0x3725, 0x42},
	{0x3739, 0x12},
	{0x3767, 0x00},
	{0x377a, 0x0d},
	{0x3789, 0x18},
	{0x3790, 0x40},
	{0x3791, 0xa2},
	{0x37c2, 0x04},
	{0x37c3, 0xf1},
	{0x37d9, 0x0c},
	{0x37da, 0x02},
	{0x37dc, 0x02},
	{0x37e1, 0x04},
	{0x37e2, 0x0a},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x08},
	{0x3804, 0x10},
	{0x3805, 0x8f},
	{0x3806, 0x0c},
	{0x3807, 0x47},
	{0x3808, 0x10},
	{0x3809, 0x70},
	{0x380a, 0x0c},
	{0x380b, 0x30},
	{0x380c, 0x04},
	{0x380d, 0x98},
	{0x380e, 0x0c},
	{0x380f, 0x7c},
	{0x3811, 0x0f},
	{0x3813, 0x09},
	{0x3814, 0x01},
	{0x3815, 0x01},
	{0x3816, 0x01},
	{0x3817, 0x01},
	{0x381f, 0x08},
	{0x3820, 0x88},
	{0x3821, 0x00},
	{0x3822, 0x14},
	{0x382e, 0xe6},
	{0x3c80, 0x00},
	{0x3c87, 0x01},
	{0x3c8c, 0x19},
	{0x3c8d, 0x1c},
	{0x3ca0, 0x00},
	{0x3ca1, 0x00},
	{0x3ca2, 0x00},
	{0x3ca3, 0x00},
	{0x3ca4, 0x50},
	{0x3ca5, 0x11},
	{0x3ca6, 0x01},
	{0x3ca7, 0x00},
	{0x3ca8, 0x00},
	{0x4008, 0x02},
	{0x4009, 0x0f},
	{0x400a, 0x01},
	{0x400b, 0x19},
	{0x4011, 0x21},
	{0x4017, 0x08},
	{0x4019, 0x04},
	{0x401a, 0x58},
	{0x4032, 0x1e},
	{0x4050, 0x02},
	{0x4051, 0x09},
	{0x405e, 0x00},
	{0x4066, 0x02},
	{0x4501, 0x00},
	{0x4502, 0x10},
	{0x4505, 0x00},
	{0x4800, 0x64},
	{0x481b, 0x3e},
	{0x481f, 0x30},
	{0x4825, 0x34},
	{0x4837, 0x0e},
	{0x484b, 0x01},
	{0x4883, 0x02},
	{0x5000, 0xff},
	{0x5001, 0x0f},
	{0x5045, 0x20},
	{0x5046, 0x20},
	{0x5047, 0xa4},
	{0x5048, 0x20},
	{0x5049, 0xa4},
};

static const stwuct ov13b10_weg mode_4208x3120_wegs[] = {
	{0x0305, 0xaf},
	{0x3501, 0x0c},
	{0x3662, 0x92},
	{0x3714, 0x24},
	{0x3739, 0x12},
	{0x37c2, 0x04},
	{0x37d9, 0x0c},
	{0x37e2, 0x0a},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x08},
	{0x3804, 0x10},
	{0x3805, 0x8f},
	{0x3806, 0x0c},
	{0x3807, 0x47},
	{0x3808, 0x10},
	{0x3809, 0x70},
	{0x380a, 0x0c},
	{0x380b, 0x30},
	{0x380c, 0x04},
	{0x380d, 0x98},
	{0x380e, 0x0c},
	{0x380f, 0x7c},
	{0x3810, 0x00},
	{0x3811, 0x0f},
	{0x3812, 0x00},
	{0x3813, 0x09},
	{0x3814, 0x01},
	{0x3816, 0x01},
	{0x3820, 0x88},
	{0x3c8c, 0x19},
	{0x4008, 0x02},
	{0x4009, 0x0f},
	{0x4050, 0x02},
	{0x4051, 0x09},
	{0x4501, 0x00},
	{0x4505, 0x00},
	{0x4837, 0x0e},
	{0x5000, 0xff},
	{0x5001, 0x0f},
};

static const stwuct ov13b10_weg mode_4160x3120_wegs[] = {
	{0x0305, 0xaf},
	{0x3501, 0x0c},
	{0x3662, 0x92},
	{0x3714, 0x24},
	{0x3739, 0x12},
	{0x37c2, 0x04},
	{0x37d9, 0x0c},
	{0x37e2, 0x0a},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x08},
	{0x3804, 0x10},
	{0x3805, 0x8f},
	{0x3806, 0x0c},
	{0x3807, 0x47},
	{0x3808, 0x10},
	{0x3809, 0x40},
	{0x380a, 0x0c},
	{0x380b, 0x30},
	{0x380c, 0x04},
	{0x380d, 0x98},
	{0x380e, 0x0c},
	{0x380f, 0x7c},
	{0x3810, 0x00},
	{0x3811, 0x27},
	{0x3812, 0x00},
	{0x3813, 0x09},
	{0x3814, 0x01},
	{0x3816, 0x01},
	{0x3820, 0x88},
	{0x3c8c, 0x19},
	{0x4008, 0x02},
	{0x4009, 0x0f},
	{0x4050, 0x02},
	{0x4051, 0x09},
	{0x4501, 0x00},
	{0x4505, 0x00},
	{0x4837, 0x0e},
	{0x5000, 0xff},
	{0x5001, 0x0f},
};

static const stwuct ov13b10_weg mode_4160x2340_wegs[] = {
	{0x0305, 0xaf},
	{0x3501, 0x0c},
	{0x3662, 0x92},
	{0x3714, 0x24},
	{0x3739, 0x12},
	{0x37c2, 0x04},
	{0x37d9, 0x0c},
	{0x37e2, 0x0a},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x08},
	{0x3804, 0x10},
	{0x3805, 0x8f},
	{0x3806, 0x0c},
	{0x3807, 0x47},
	{0x3808, 0x10},
	{0x3809, 0x40},
	{0x380a, 0x09},
	{0x380b, 0x24},
	{0x380c, 0x04},
	{0x380d, 0x98},
	{0x380e, 0x0c},
	{0x380f, 0x7c},
	{0x3810, 0x00},
	{0x3811, 0x27},
	{0x3812, 0x01},
	{0x3813, 0x8f},
	{0x3814, 0x01},
	{0x3816, 0x01},
	{0x3820, 0x88},
	{0x3c8c, 0x19},
	{0x4008, 0x02},
	{0x4009, 0x0f},
	{0x4050, 0x02},
	{0x4051, 0x09},
	{0x4501, 0x00},
	{0x4505, 0x00},
	{0x4837, 0x0e},
	{0x5000, 0xff},
	{0x5001, 0x0f},
};

static const stwuct ov13b10_weg mode_2104x1560_wegs[] = {
	{0x0305, 0xaf},
	{0x3501, 0x06},
	{0x3662, 0x88},
	{0x3714, 0x28},
	{0x3739, 0x10},
	{0x37c2, 0x14},
	{0x37d9, 0x06},
	{0x37e2, 0x0c},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x08},
	{0x3804, 0x10},
	{0x3805, 0x8f},
	{0x3806, 0x0c},
	{0x3807, 0x47},
	{0x3808, 0x08},
	{0x3809, 0x38},
	{0x380a, 0x06},
	{0x380b, 0x18},
	{0x380c, 0x04},
	{0x380d, 0x98},
	{0x380e, 0x06},
	{0x380f, 0x3e},
	{0x3810, 0x00},
	{0x3811, 0x07},
	{0x3812, 0x00},
	{0x3813, 0x05},
	{0x3814, 0x03},
	{0x3816, 0x03},
	{0x3820, 0x8b},
	{0x3c8c, 0x18},
	{0x4008, 0x00},
	{0x4009, 0x05},
	{0x4050, 0x00},
	{0x4051, 0x05},
	{0x4501, 0x08},
	{0x4505, 0x00},
	{0x4837, 0x0e},
	{0x5000, 0xfd},
	{0x5001, 0x0d},
};

static const stwuct ov13b10_weg mode_2080x1170_wegs[] = {
	{0x0305, 0xaf},
	{0x3501, 0x06},
	{0x3662, 0x88},
	{0x3714, 0x28},
	{0x3739, 0x10},
	{0x37c2, 0x14},
	{0x37d9, 0x06},
	{0x37e2, 0x0c},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x08},
	{0x3804, 0x10},
	{0x3805, 0x8f},
	{0x3806, 0x0c},
	{0x3807, 0x47},
	{0x3808, 0x08},
	{0x3809, 0x20},
	{0x380a, 0x04},
	{0x380b, 0x92},
	{0x380c, 0x04},
	{0x380d, 0x98},
	{0x380e, 0x06},
	{0x380f, 0x3e},
	{0x3810, 0x00},
	{0x3811, 0x13},
	{0x3812, 0x00},
	{0x3813, 0xc9},
	{0x3814, 0x03},
	{0x3816, 0x03},
	{0x3820, 0x8b},
	{0x3c8c, 0x18},
	{0x4008, 0x00},
	{0x4009, 0x05},
	{0x4050, 0x00},
	{0x4051, 0x05},
	{0x4501, 0x08},
	{0x4505, 0x00},
	{0x4837, 0x0e},
	{0x5000, 0xfd},
	{0x5001, 0x0d},
};

static const stwuct ov13b10_weg mode_1364x768_120fps_wegs[] = {
	{0x0305, 0xaf},
	{0x3011, 0x7c},
	{0x3501, 0x03},
	{0x3502, 0x00},
	{0x3662, 0x88},
	{0x3714, 0x28},
	{0x3739, 0x10},
	{0x37c2, 0x14},
	{0x37d9, 0x06},
	{0x37e2, 0x0c},
	{0x37e4, 0x00},
	{0x3800, 0x02},
	{0x3801, 0xe4},
	{0x3802, 0x03},
	{0x3803, 0x48},
	{0x3804, 0x0d},
	{0x3805, 0xab},
	{0x3806, 0x09},
	{0x3807, 0x60},
	{0x3808, 0x05},
	{0x3809, 0x54},
	{0x380a, 0x03},
	{0x380b, 0x00},
	{0x380c, 0x04},
	{0x380d, 0x8e},
	{0x380e, 0x03},
	{0x380f, 0x20},
	{0x3811, 0x07},
	{0x3813, 0x07},
	{0x3814, 0x03},
	{0x3816, 0x03},
	{0x3820, 0x8b},
	{0x3c8c, 0x18},
	{0x4008, 0x00},
	{0x4009, 0x05},
	{0x4050, 0x00},
	{0x4051, 0x05},
	{0x4501, 0x08},
	{0x4505, 0x04},
	{0x5000, 0xfd},
	{0x5001, 0x0d},
};

static const chaw * const ov13b10_test_pattewn_menu[] = {
	"Disabwed",
	"Vewticaw Cowow Baw Type 1",
	"Vewticaw Cowow Baw Type 2",
	"Vewticaw Cowow Baw Type 3",
	"Vewticaw Cowow Baw Type 4"
};

/* Configuwations fow suppowted wink fwequencies */
#define OV13B10_WINK_FWEQ_560MHZ	560000000UWW
#define OV13B10_WINK_FWEQ_INDEX_0	0

#define OV13B10_EXT_CWK			19200000
#define OV13B10_DATA_WANES		4

/*
 * pixew_wate = wink_fweq * data-wate * nw_of_wanes / bits_pew_sampwe
 * data wate => doubwe data wate; numbew of wanes => 4; bits pew pixew => 10
 */
static u64 wink_fweq_to_pixew_wate(u64 f)
{
	f *= 2 * OV13B10_DATA_WANES;
	do_div(f, 10);

	wetuwn f;
}

/* Menu items fow WINK_FWEQ V4W2 contwow */
static const s64 wink_fweq_menu_items[] = {
	OV13B10_WINK_FWEQ_560MHZ
};

/* Wink fwequency configs */
static const stwuct ov13b10_wink_fweq_config
			wink_fweq_configs[] = {
	{
		.pixews_pew_wine = OV13B10_PPW_560MHZ,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mipi_data_wate_1120mbps),
			.wegs = mipi_data_wate_1120mbps,
		}
	}
};

/* Mode configs */
static const stwuct ov13b10_mode suppowted_modes[] = {
	{
		.width = 4208,
		.height = 3120,
		.vts_def = OV13B10_VTS_30FPS,
		.vts_min = OV13B10_VTS_30FPS,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_4208x3120_wegs),
			.wegs = mode_4208x3120_wegs,
		},
		.wink_fweq_index = OV13B10_WINK_FWEQ_INDEX_0,
	},
	{
		.width = 4160,
		.height = 3120,
		.vts_def = OV13B10_VTS_30FPS,
		.vts_min = OV13B10_VTS_30FPS,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_4160x3120_wegs),
			.wegs = mode_4160x3120_wegs,
		},
		.wink_fweq_index = OV13B10_WINK_FWEQ_INDEX_0,
	},
	{
		.width = 4160,
		.height = 2340,
		.vts_def = OV13B10_VTS_30FPS,
		.vts_min = OV13B10_VTS_30FPS,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_4160x2340_wegs),
			.wegs = mode_4160x2340_wegs,
		},
		.wink_fweq_index = OV13B10_WINK_FWEQ_INDEX_0,
	},
	{
		.width = 2104,
		.height = 1560,
		.vts_def = OV13B10_VTS_60FPS,
		.vts_min = OV13B10_VTS_60FPS,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_2104x1560_wegs),
			.wegs = mode_2104x1560_wegs,
		},
		.wink_fweq_index = OV13B10_WINK_FWEQ_INDEX_0,
	},
	{
		.width = 2080,
		.height = 1170,
		.vts_def = OV13B10_VTS_60FPS,
		.vts_min = OV13B10_VTS_60FPS,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_2080x1170_wegs),
			.wegs = mode_2080x1170_wegs,
		},
		.wink_fweq_index = OV13B10_WINK_FWEQ_INDEX_0,
	},
	{
		.width = 1364,
		.height = 768,
		.vts_def = OV13B10_VTS_120FPS,
		.vts_min = OV13B10_VTS_120FPS,
		.wink_fweq_index = OV13B10_WINK_FWEQ_INDEX_0,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_1364x768_120fps_wegs),
			.wegs = mode_1364x768_120fps_wegs,
		},
	},
};

stwuct ov13b10 {
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;

	stwuct v4w2_ctww_handwew ctww_handwew;

	stwuct cwk *img_cwk;
	stwuct weguwatow *avdd;
	stwuct gpio_desc *weset;

	/* V4W2 Contwows */
	stwuct v4w2_ctww *wink_fweq;
	stwuct v4w2_ctww *pixew_wate;
	stwuct v4w2_ctww *vbwank;
	stwuct v4w2_ctww *hbwank;
	stwuct v4w2_ctww *exposuwe;

	/* Cuwwent mode */
	const stwuct ov13b10_mode *cuw_mode;

	/* Mutex fow sewiawized access */
	stwuct mutex mutex;

	/* Twue if the device has been identified */
	boow identified;
};

#define to_ov13b10(_sd)	containew_of(_sd, stwuct ov13b10, sd)

/* Wead wegistews up to 4 at a time */
static int ov13b10_wead_weg(stwuct ov13b10 *ov13b,
			    u16 weg, u32 wen, u32 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov13b->sd);
	stwuct i2c_msg msgs[2];
	u8 *data_be_p;
	int wet;
	__be32 data_be = 0;
	__be16 weg_addw_be = cpu_to_be16(weg);

	if (wen > 4)
		wetuwn -EINVAW;

	data_be_p = (u8 *)&data_be;
	/* Wwite wegistew addwess */
	msgs[0].addw = cwient->addw;
	msgs[0].fwags = 0;
	msgs[0].wen = 2;
	msgs[0].buf = (u8 *)&weg_addw_be;

	/* Wead data fwom wegistew */
	msgs[1].addw = cwient->addw;
	msgs[1].fwags = I2C_M_WD;
	msgs[1].wen = wen;
	msgs[1].buf = &data_be_p[4 - wen];

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs))
		wetuwn -EIO;

	*vaw = be32_to_cpu(data_be);

	wetuwn 0;
}

/* Wwite wegistews up to 4 at a time */
static int ov13b10_wwite_weg(stwuct ov13b10 *ov13b,
			     u16 weg, u32 wen, u32 __vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov13b->sd);
	int buf_i, vaw_i;
	u8 buf[6], *vaw_p;
	__be32 vaw;

	if (wen > 4)
		wetuwn -EINVAW;

	buf[0] = weg >> 8;
	buf[1] = weg & 0xff;

	vaw = cpu_to_be32(__vaw);
	vaw_p = (u8 *)&vaw;
	buf_i = 2;
	vaw_i = 4 - wen;

	whiwe (vaw_i < 4)
		buf[buf_i++] = vaw_p[vaw_i++];

	if (i2c_mastew_send(cwient, buf, wen + 2) != wen + 2)
		wetuwn -EIO;

	wetuwn 0;
}

/* Wwite a wist of wegistews */
static int ov13b10_wwite_wegs(stwuct ov13b10 *ov13b,
			      const stwuct ov13b10_weg *wegs, u32 wen)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov13b->sd);
	int wet;
	u32 i;

	fow (i = 0; i < wen; i++) {
		wet = ov13b10_wwite_weg(ov13b, wegs[i].addwess, 1,
					wegs[i].vaw);
		if (wet) {
			dev_eww_watewimited(&cwient->dev,
					    "Faiwed to wwite weg 0x%4.4x. ewwow = %d\n",
					    wegs[i].addwess, wet);

			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ov13b10_wwite_weg_wist(stwuct ov13b10 *ov13b,
				  const stwuct ov13b10_weg_wist *w_wist)
{
	wetuwn ov13b10_wwite_wegs(ov13b, w_wist->wegs, w_wist->num_of_wegs);
}

/* Open sub-device */
static int ov13b10_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	const stwuct ov13b10_mode *defauwt_mode = &suppowted_modes[0];
	stwuct ov13b10 *ov13b = to_ov13b10(sd);
	stwuct v4w2_mbus_fwamefmt *twy_fmt = v4w2_subdev_state_get_fowmat(fh->state,
									  0);

	mutex_wock(&ov13b->mutex);

	/* Initiawize twy_fmt */
	twy_fmt->width = defauwt_mode->width;
	twy_fmt->height = defauwt_mode->height;
	twy_fmt->code = MEDIA_BUS_FMT_SGWBG10_1X10;
	twy_fmt->fiewd = V4W2_FIEWD_NONE;

	/* No cwop ow compose */
	mutex_unwock(&ov13b->mutex);

	wetuwn 0;
}

static int ov13b10_update_digitaw_gain(stwuct ov13b10 *ov13b, u32 d_gain)
{
	int wet;
	u32 vaw;

	/*
	 * 0x350C[7:6], 0x350B[7:0], 0x350A[1:0]
	 */

	vaw = (d_gain & OV13B10_DGTW_GAIN_W_MASK) << OV13B10_DGTW_GAIN_W_SHIFT;
	wet = ov13b10_wwite_weg(ov13b, OV13B10_WEG_DGTW_GAIN_W,
				OV13B10_WEG_VAWUE_08BIT, vaw);
	if (wet)
		wetuwn wet;

	vaw = (d_gain >> OV13B10_DGTW_GAIN_M_SHIFT) & OV13B10_DGTW_GAIN_M_MASK;
	wet = ov13b10_wwite_weg(ov13b, OV13B10_WEG_DGTW_GAIN_M,
				OV13B10_WEG_VAWUE_08BIT, vaw);
	if (wet)
		wetuwn wet;

	vaw = (d_gain >> OV13B10_DGTW_GAIN_H_SHIFT) & OV13B10_DGTW_GAIN_H_MASK;
	wet = ov13b10_wwite_weg(ov13b, OV13B10_WEG_DGTW_GAIN_H,
				OV13B10_WEG_VAWUE_08BIT, vaw);

	wetuwn wet;
}

static int ov13b10_enabwe_test_pattewn(stwuct ov13b10 *ov13b, u32 pattewn)
{
	int wet;
	u32 vaw;

	wet = ov13b10_wead_weg(ov13b, OV13B10_WEG_TEST_PATTEWN,
			       OV13B10_WEG_VAWUE_08BIT, &vaw);
	if (wet)
		wetuwn wet;

	if (pattewn) {
		vaw &= OV13B10_TEST_PATTEWN_MASK;
		vaw |= ((pattewn - 1) << OV13B10_TEST_PATTEWN_BAW_SHIFT) |
		     OV13B10_TEST_PATTEWN_ENABWE;
	} ewse {
		vaw &= ~OV13B10_TEST_PATTEWN_ENABWE;
	}

	wetuwn ov13b10_wwite_weg(ov13b, OV13B10_WEG_TEST_PATTEWN,
				 OV13B10_WEG_VAWUE_08BIT, vaw);
}

static int ov13b10_set_ctww_hfwip(stwuct ov13b10 *ov13b, u32 ctww_vaw)
{
	int wet;
	u32 vaw;

	wet = ov13b10_wead_weg(ov13b, OV13B10_WEG_FOWMAT1,
			       OV13B10_WEG_VAWUE_08BIT, &vaw);
	if (wet)
		wetuwn wet;

	wet = ov13b10_wwite_weg(ov13b, OV13B10_WEG_FOWMAT1,
				OV13B10_WEG_VAWUE_08BIT,
				ctww_vaw ? vaw & ~BIT(3) : vaw);

	if (wet)
		wetuwn wet;

	wet = ov13b10_wead_weg(ov13b, OV13B10_WEG_H_WIN_OFFSET,
			       OV13B10_WEG_VAWUE_08BIT, &vaw);
	if (wet)
		wetuwn wet;

	/*
	 * Appwying cwopping offset to wevewse the change of Bayew owdew
	 * aftew miwwowing image
	 */
	wetuwn ov13b10_wwite_weg(ov13b, OV13B10_WEG_H_WIN_OFFSET,
				 OV13B10_WEG_VAWUE_08BIT,
				 ctww_vaw ? ++vaw : vaw);
}

static int ov13b10_set_ctww_vfwip(stwuct ov13b10 *ov13b, u32 ctww_vaw)
{
	int wet;
	u32 vaw;

	wet = ov13b10_wead_weg(ov13b, OV13B10_WEG_FOWMAT1,
			       OV13B10_WEG_VAWUE_08BIT, &vaw);
	if (wet)
		wetuwn wet;

	wet = ov13b10_wwite_weg(ov13b, OV13B10_WEG_FOWMAT1,
				OV13B10_WEG_VAWUE_08BIT,
				ctww_vaw ? vaw | BIT(4) | BIT(5)  : vaw);

	if (wet)
		wetuwn wet;

	wet = ov13b10_wead_weg(ov13b, OV13B10_WEG_V_WIN_OFFSET,
			       OV13B10_WEG_VAWUE_08BIT, &vaw);
	if (wet)
		wetuwn wet;

	/*
	 * Appwying cwopping offset to wevewse the change of Bayew owdew
	 * aftew fwipping image
	 */
	wetuwn ov13b10_wwite_weg(ov13b, OV13B10_WEG_V_WIN_OFFSET,
				 OV13B10_WEG_VAWUE_08BIT,
				 ctww_vaw ? --vaw : vaw);
}

static int ov13b10_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ov13b10 *ov13b = containew_of(ctww->handwew,
					     stwuct ov13b10, ctww_handwew);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov13b->sd);
	s64 max;
	int wet;

	/* Pwopagate change of cuwwent contwow to aww wewated contwows */
	switch (ctww->id) {
	case V4W2_CID_VBWANK:
		/* Update max exposuwe whiwe meeting expected vbwanking */
		max = ov13b->cuw_mode->height + ctww->vaw - 8;
		__v4w2_ctww_modify_wange(ov13b->exposuwe,
					 ov13b->exposuwe->minimum,
					 max, ov13b->exposuwe->step, max);
		bweak;
	}

	/*
	 * Appwying V4W2 contwow vawue onwy happens
	 * when powew is up fow stweaming
	 */
	if (!pm_wuntime_get_if_in_use(&cwient->dev))
		wetuwn 0;

	wet = 0;
	switch (ctww->id) {
	case V4W2_CID_ANAWOGUE_GAIN:
		wet = ov13b10_wwite_weg(ov13b, OV13B10_WEG_ANAWOG_GAIN,
					OV13B10_WEG_VAWUE_16BIT,
					ctww->vaw << 1);
		bweak;
	case V4W2_CID_DIGITAW_GAIN:
		wet = ov13b10_update_digitaw_gain(ov13b, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE:
		wet = ov13b10_wwite_weg(ov13b, OV13B10_WEG_EXPOSUWE,
					OV13B10_WEG_VAWUE_24BIT,
					ctww->vaw);
		bweak;
	case V4W2_CID_VBWANK:
		wet = ov13b10_wwite_weg(ov13b, OV13B10_WEG_VTS,
					OV13B10_WEG_VAWUE_16BIT,
					ov13b->cuw_mode->height
					+ ctww->vaw);
		bweak;
	case V4W2_CID_TEST_PATTEWN:
		wet = ov13b10_enabwe_test_pattewn(ov13b, ctww->vaw);
		bweak;
	case V4W2_CID_HFWIP:
		ov13b10_set_ctww_hfwip(ov13b, ctww->vaw);
		bweak;
	case V4W2_CID_VFWIP:
		ov13b10_set_ctww_vfwip(ov13b, ctww->vaw);
		bweak;
	defauwt:
		dev_info(&cwient->dev,
			 "ctww(id:0x%x,vaw:0x%x) is not handwed\n",
			 ctww->id, ctww->vaw);
		bweak;
	}

	pm_wuntime_put(&cwient->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops ov13b10_ctww_ops = {
	.s_ctww = ov13b10_set_ctww,
};

static int ov13b10_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	/* Onwy one bayew owdew(GWBG) is suppowted */
	if (code->index > 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_SGWBG10_1X10;

	wetuwn 0;
}

static int ov13b10_enum_fwame_size(stwuct v4w2_subdev *sd,
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

static void ov13b10_update_pad_fowmat(const stwuct ov13b10_mode *mode,
				      stwuct v4w2_subdev_fowmat *fmt)
{
	fmt->fowmat.width = mode->width;
	fmt->fowmat.height = mode->height;
	fmt->fowmat.code = MEDIA_BUS_FMT_SGWBG10_1X10;
	fmt->fowmat.fiewd = V4W2_FIEWD_NONE;
}

static int ov13b10_do_get_pad_fowmat(stwuct ov13b10 *ov13b,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct v4w2_mbus_fwamefmt *fwamefmt;

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		fwamefmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		fmt->fowmat = *fwamefmt;
	} ewse {
		ov13b10_update_pad_fowmat(ov13b->cuw_mode, fmt);
	}

	wetuwn 0;
}

static int ov13b10_get_pad_fowmat(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct ov13b10 *ov13b = to_ov13b10(sd);
	int wet;

	mutex_wock(&ov13b->mutex);
	wet = ov13b10_do_get_pad_fowmat(ov13b, sd_state, fmt);
	mutex_unwock(&ov13b->mutex);

	wetuwn wet;
}

static int
ov13b10_set_pad_fowmat(stwuct v4w2_subdev *sd,
		       stwuct v4w2_subdev_state *sd_state,
		       stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct ov13b10 *ov13b = to_ov13b10(sd);
	const stwuct ov13b10_mode *mode;
	stwuct v4w2_mbus_fwamefmt *fwamefmt;
	s32 vbwank_def;
	s32 vbwank_min;
	s64 h_bwank;
	s64 pixew_wate;
	s64 wink_fweq;

	mutex_wock(&ov13b->mutex);

	/* Onwy one waw bayew(GWBG) owdew is suppowted */
	if (fmt->fowmat.code != MEDIA_BUS_FMT_SGWBG10_1X10)
		fmt->fowmat.code = MEDIA_BUS_FMT_SGWBG10_1X10;

	mode = v4w2_find_neawest_size(suppowted_modes,
				      AWWAY_SIZE(suppowted_modes),
				      width, height,
				      fmt->fowmat.width, fmt->fowmat.height);
	ov13b10_update_pad_fowmat(mode, fmt);
	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		fwamefmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		*fwamefmt = fmt->fowmat;
	} ewse {
		ov13b->cuw_mode = mode;
		__v4w2_ctww_s_ctww(ov13b->wink_fweq, mode->wink_fweq_index);
		wink_fweq = wink_fweq_menu_items[mode->wink_fweq_index];
		pixew_wate = wink_fweq_to_pixew_wate(wink_fweq);
		__v4w2_ctww_s_ctww_int64(ov13b->pixew_wate, pixew_wate);

		/* Update wimits and set FPS to defauwt */
		vbwank_def = ov13b->cuw_mode->vts_def -
			     ov13b->cuw_mode->height;
		vbwank_min = ov13b->cuw_mode->vts_min -
			     ov13b->cuw_mode->height;
		__v4w2_ctww_modify_wange(ov13b->vbwank, vbwank_min,
					 OV13B10_VTS_MAX
					 - ov13b->cuw_mode->height,
					 1,
					 vbwank_def);
		__v4w2_ctww_s_ctww(ov13b->vbwank, vbwank_def);
		h_bwank =
			wink_fweq_configs[mode->wink_fweq_index].pixews_pew_wine
			 - ov13b->cuw_mode->width;
		__v4w2_ctww_modify_wange(ov13b->hbwank, h_bwank,
					 h_bwank, 1, h_bwank);
	}

	mutex_unwock(&ov13b->mutex);

	wetuwn 0;
}

/* Vewify chip ID */
static int ov13b10_identify_moduwe(stwuct ov13b10 *ov13b)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov13b->sd);
	int wet;
	u32 vaw;

	if (ov13b->identified)
		wetuwn 0;

	wet = ov13b10_wead_weg(ov13b, OV13B10_WEG_CHIP_ID,
			       OV13B10_WEG_VAWUE_24BIT, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != OV13B10_CHIP_ID) {
		dev_eww(&cwient->dev, "chip id mismatch: %x!=%x\n",
			OV13B10_CHIP_ID, vaw);
		wetuwn -EIO;
	}

	ov13b->identified = twue;

	wetuwn 0;
}

static int ov13b10_powew_off(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov13b10 *ov13b10 = to_ov13b10(sd);

	gpiod_set_vawue_cansweep(ov13b10->weset, 1);

	if (ov13b10->avdd)
		weguwatow_disabwe(ov13b10->avdd);

	cwk_disabwe_unpwepawe(ov13b10->img_cwk);

	wetuwn 0;
}

static int ov13b10_powew_on(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov13b10 *ov13b10 = to_ov13b10(sd);
	int wet;

	wet = cwk_pwepawe_enabwe(ov13b10->img_cwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe imaging cwock: %d", wet);
		wetuwn wet;
	}

	if (ov13b10->avdd) {
		wet = weguwatow_enabwe(ov13b10->avdd);
		if (wet < 0) {
			dev_eww(dev, "faiwed to enabwe avdd: %d", wet);
			cwk_disabwe_unpwepawe(ov13b10->img_cwk);
			wetuwn wet;
		}
	}

	gpiod_set_vawue_cansweep(ov13b10->weset, 0);
	/* 5ms to wait weady aftew XSHUTDN assewt */
	usweep_wange(5000, 5500);

	wetuwn 0;
}

static int ov13b10_stawt_stweaming(stwuct ov13b10 *ov13b)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov13b->sd);
	const stwuct ov13b10_weg_wist *weg_wist;
	int wet, wink_fweq_index;

	wet = ov13b10_identify_moduwe(ov13b);
	if (wet)
		wetuwn wet;

	/* Get out of fwom softwawe weset */
	wet = ov13b10_wwite_weg(ov13b, OV13B10_WEG_SOFTWAWE_WST,
				OV13B10_WEG_VAWUE_08BIT, OV13B10_SOFTWAWE_WST);
	if (wet) {
		dev_eww(&cwient->dev, "%s faiwed to set powewup wegistews\n",
			__func__);
		wetuwn wet;
	}

	wink_fweq_index = ov13b->cuw_mode->wink_fweq_index;
	weg_wist = &wink_fweq_configs[wink_fweq_index].weg_wist;
	wet = ov13b10_wwite_weg_wist(ov13b, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "%s faiwed to set pwws\n", __func__);
		wetuwn wet;
	}

	/* Appwy defauwt vawues of cuwwent mode */
	weg_wist = &ov13b->cuw_mode->weg_wist;
	wet = ov13b10_wwite_weg_wist(ov13b, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "%s faiwed to set mode\n", __func__);
		wetuwn wet;
	}

	/* Appwy customized vawues fwom usew */
	wet =  __v4w2_ctww_handwew_setup(ov13b->sd.ctww_handwew);
	if (wet)
		wetuwn wet;

	wetuwn ov13b10_wwite_weg(ov13b, OV13B10_WEG_MODE_SEWECT,
				 OV13B10_WEG_VAWUE_08BIT,
				 OV13B10_MODE_STWEAMING);
}

/* Stop stweaming */
static int ov13b10_stop_stweaming(stwuct ov13b10 *ov13b)
{
	wetuwn ov13b10_wwite_weg(ov13b, OV13B10_WEG_MODE_SEWECT,
				 OV13B10_WEG_VAWUE_08BIT, OV13B10_MODE_STANDBY);
}

static int ov13b10_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct ov13b10 *ov13b = to_ov13b10(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet = 0;

	mutex_wock(&ov13b->mutex);

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(&cwient->dev);
		if (wet < 0)
			goto eww_unwock;

		/*
		 * Appwy defauwt & customized vawues
		 * and then stawt stweaming.
		 */
		wet = ov13b10_stawt_stweaming(ov13b);
		if (wet)
			goto eww_wpm_put;
	} ewse {
		ov13b10_stop_stweaming(ov13b);
		pm_wuntime_put(&cwient->dev);
	}

	mutex_unwock(&ov13b->mutex);

	wetuwn wet;

eww_wpm_put:
	pm_wuntime_put(&cwient->dev);
eww_unwock:
	mutex_unwock(&ov13b->mutex);

	wetuwn wet;
}

static int ov13b10_suspend(stwuct device *dev)
{
	ov13b10_powew_off(dev);

	wetuwn 0;
}

static int ov13b10_wesume(stwuct device *dev)
{
	wetuwn ov13b10_powew_on(dev);
}

static const stwuct v4w2_subdev_video_ops ov13b10_video_ops = {
	.s_stweam = ov13b10_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops ov13b10_pad_ops = {
	.enum_mbus_code = ov13b10_enum_mbus_code,
	.get_fmt = ov13b10_get_pad_fowmat,
	.set_fmt = ov13b10_set_pad_fowmat,
	.enum_fwame_size = ov13b10_enum_fwame_size,
};

static const stwuct v4w2_subdev_ops ov13b10_subdev_ops = {
	.video = &ov13b10_video_ops,
	.pad = &ov13b10_pad_ops,
};

static const stwuct media_entity_opewations ov13b10_subdev_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static const stwuct v4w2_subdev_intewnaw_ops ov13b10_intewnaw_ops = {
	.open = ov13b10_open,
};

/* Initiawize contwow handwews */
static int ov13b10_init_contwows(stwuct ov13b10 *ov13b)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov13b->sd);
	stwuct v4w2_fwnode_device_pwopewties pwops;
	stwuct v4w2_ctww_handwew *ctww_hdww;
	s64 exposuwe_max;
	s64 vbwank_def;
	s64 vbwank_min;
	s64 hbwank;
	s64 pixew_wate_min;
	s64 pixew_wate_max;
	const stwuct ov13b10_mode *mode;
	u32 max;
	int wet;

	ctww_hdww = &ov13b->ctww_handwew;
	wet = v4w2_ctww_handwew_init(ctww_hdww, 10);
	if (wet)
		wetuwn wet;

	mutex_init(&ov13b->mutex);
	ctww_hdww->wock = &ov13b->mutex;
	max = AWWAY_SIZE(wink_fweq_menu_items) - 1;
	ov13b->wink_fweq = v4w2_ctww_new_int_menu(ctww_hdww,
						  &ov13b10_ctww_ops,
						  V4W2_CID_WINK_FWEQ,
						  max,
						  0,
						  wink_fweq_menu_items);
	if (ov13b->wink_fweq)
		ov13b->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	pixew_wate_max = wink_fweq_to_pixew_wate(wink_fweq_menu_items[0]);
	pixew_wate_min = 0;
	/* By defauwt, PIXEW_WATE is wead onwy */
	ov13b->pixew_wate = v4w2_ctww_new_std(ctww_hdww, &ov13b10_ctww_ops,
					      V4W2_CID_PIXEW_WATE,
					      pixew_wate_min, pixew_wate_max,
					      1, pixew_wate_max);

	mode = ov13b->cuw_mode;
	vbwank_def = mode->vts_def - mode->height;
	vbwank_min = mode->vts_min - mode->height;
	ov13b->vbwank = v4w2_ctww_new_std(ctww_hdww, &ov13b10_ctww_ops,
					  V4W2_CID_VBWANK,
					  vbwank_min,
					  OV13B10_VTS_MAX - mode->height, 1,
					  vbwank_def);

	hbwank = wink_fweq_configs[mode->wink_fweq_index].pixews_pew_wine -
		 mode->width;
	ov13b->hbwank = v4w2_ctww_new_std(ctww_hdww, &ov13b10_ctww_ops,
					  V4W2_CID_HBWANK,
					  hbwank, hbwank, 1, hbwank);
	if (ov13b->hbwank)
		ov13b->hbwank->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	exposuwe_max = mode->vts_def - 8;
	ov13b->exposuwe = v4w2_ctww_new_std(ctww_hdww, &ov13b10_ctww_ops,
					    V4W2_CID_EXPOSUWE,
					    OV13B10_EXPOSUWE_MIN,
					    exposuwe_max, OV13B10_EXPOSUWE_STEP,
					    exposuwe_max);

	v4w2_ctww_new_std(ctww_hdww, &ov13b10_ctww_ops, V4W2_CID_ANAWOGUE_GAIN,
			  OV13B10_ANA_GAIN_MIN, OV13B10_ANA_GAIN_MAX,
			  OV13B10_ANA_GAIN_STEP, OV13B10_ANA_GAIN_DEFAUWT);

	/* Digitaw gain */
	v4w2_ctww_new_std(ctww_hdww, &ov13b10_ctww_ops, V4W2_CID_DIGITAW_GAIN,
			  OV13B10_DGTW_GAIN_MIN, OV13B10_DGTW_GAIN_MAX,
			  OV13B10_DGTW_GAIN_STEP, OV13B10_DGTW_GAIN_DEFAUWT);

	v4w2_ctww_new_std_menu_items(ctww_hdww, &ov13b10_ctww_ops,
				     V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(ov13b10_test_pattewn_menu) - 1,
				     0, 0, ov13b10_test_pattewn_menu);

	v4w2_ctww_new_std(ctww_hdww, &ov13b10_ctww_ops,
			  V4W2_CID_HFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(ctww_hdww, &ov13b10_ctww_ops,
			  V4W2_CID_VFWIP, 0, 1, 1, 0);

	if (ctww_hdww->ewwow) {
		wet = ctww_hdww->ewwow;
		dev_eww(&cwient->dev, "%s contwow init faiwed (%d)\n",
			__func__, wet);
		goto ewwow;
	}

	wet = v4w2_fwnode_device_pawse(&cwient->dev, &pwops);
	if (wet)
		goto ewwow;

	wet = v4w2_ctww_new_fwnode_pwopewties(ctww_hdww, &ov13b10_ctww_ops,
					      &pwops);
	if (wet)
		goto ewwow;

	ov13b->sd.ctww_handwew = ctww_hdww;

	wetuwn 0;

ewwow:
	v4w2_ctww_handwew_fwee(ctww_hdww);
	mutex_destwoy(&ov13b->mutex);

	wetuwn wet;
}

static void ov13b10_fwee_contwows(stwuct ov13b10 *ov13b)
{
	v4w2_ctww_handwew_fwee(ov13b->sd.ctww_handwew);
	mutex_destwoy(&ov13b->mutex);
}

static int ov13b10_get_pm_wesouwces(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov13b10 *ov13b = to_ov13b10(sd);
	int wet;

	ov13b->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ov13b->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ov13b->weset),
				     "faiwed to get weset gpio\n");

	ov13b->img_cwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(ov13b->img_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ov13b->img_cwk),
				     "faiwed to get imaging cwock\n");

	ov13b->avdd = devm_weguwatow_get_optionaw(dev, "avdd");
	if (IS_EWW(ov13b->avdd)) {
		wet = PTW_EWW(ov13b->avdd);
		ov13b->avdd = NUWW;
		if (wet != -ENODEV)
			wetuwn dev_eww_pwobe(dev, wet,
					     "faiwed to get avdd weguwatow\n");
	}

	wetuwn 0;
}

static int ov13b10_check_hwcfg(stwuct device *dev)
{
	stwuct v4w2_fwnode_endpoint bus_cfg = {
		.bus_type = V4W2_MBUS_CSI2_DPHY
	};
	stwuct fwnode_handwe *ep;
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	unsigned int i, j;
	int wet;
	u32 ext_cwk;

	if (!fwnode)
		wetuwn -ENXIO;

	ep = fwnode_gwaph_get_next_endpoint(fwnode, NUWW);
	if (!ep)
		wetuwn -EPWOBE_DEFEW;

	wet = fwnode_pwopewty_wead_u32(dev_fwnode(dev), "cwock-fwequency",
				       &ext_cwk);
	if (wet) {
		dev_eww(dev, "can't get cwock fwequency");
		wetuwn wet;
	}

	if (ext_cwk != OV13B10_EXT_CWK) {
		dev_eww(dev, "extewnaw cwock %d is not suppowted",
			ext_cwk);
		wetuwn -EINVAW;
	}

	wet = v4w2_fwnode_endpoint_awwoc_pawse(ep, &bus_cfg);
	fwnode_handwe_put(ep);
	if (wet)
		wetuwn wet;

	if (bus_cfg.bus.mipi_csi2.num_data_wanes != OV13B10_DATA_WANES) {
		dev_eww(dev, "numbew of CSI2 data wanes %d is not suppowted",
			bus_cfg.bus.mipi_csi2.num_data_wanes);
		wet = -EINVAW;
		goto out_eww;
	}

	if (!bus_cfg.nw_of_wink_fwequencies) {
		dev_eww(dev, "no wink fwequencies defined");
		wet = -EINVAW;
		goto out_eww;
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
			goto out_eww;
		}
	}

out_eww:
	v4w2_fwnode_endpoint_fwee(&bus_cfg);

	wetuwn wet;
}

static int ov13b10_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ov13b10 *ov13b;
	boow fuww_powew;
	int wet;

	/* Check HW config */
	wet = ov13b10_check_hwcfg(&cwient->dev);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to check hwcfg: %d", wet);
		wetuwn wet;
	}

	ov13b = devm_kzawwoc(&cwient->dev, sizeof(*ov13b), GFP_KEWNEW);
	if (!ov13b)
		wetuwn -ENOMEM;

	/* Initiawize subdev */
	v4w2_i2c_subdev_init(&ov13b->sd, cwient, &ov13b10_subdev_ops);

	wet = ov13b10_get_pm_wesouwces(&cwient->dev);
	if (wet)
		wetuwn wet;

	fuww_powew = acpi_dev_state_d0(&cwient->dev);
	if (fuww_powew) {
		wet = ov13b10_powew_on(&cwient->dev);
		if (wet) {
			dev_eww(&cwient->dev, "faiwed to powew on\n");
			wetuwn wet;
		}

		/* Check moduwe identity */
		wet = ov13b10_identify_moduwe(ov13b);
		if (wet) {
			dev_eww(&cwient->dev, "faiwed to find sensow: %d\n", wet);
			goto ewwow_powew_off;
		}
	}

	/* Set defauwt mode to max wesowution */
	ov13b->cuw_mode = &suppowted_modes[0];

	wet = ov13b10_init_contwows(ov13b);
	if (wet)
		goto ewwow_powew_off;

	/* Initiawize subdev */
	ov13b->sd.intewnaw_ops = &ov13b10_intewnaw_ops;
	ov13b->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	ov13b->sd.entity.ops = &ov13b10_subdev_entity_ops;
	ov13b->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;

	/* Initiawize souwce pad */
	ov13b->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&ov13b->sd.entity, 1, &ov13b->pad);
	if (wet) {
		dev_eww(&cwient->dev, "%s faiwed:%d\n", __func__, wet);
		goto ewwow_handwew_fwee;
	}


	/*
	 * Device is awweady tuwned on by i2c-cowe with ACPI domain PM.
	 * Enabwe wuntime PM and tuwn off the device.
	 */
	/* Set the device's state to active if it's in D0 state. */
	if (fuww_powew)
		pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_idwe(&cwient->dev);

	wet = v4w2_async_wegistew_subdev_sensow(&ov13b->sd);
	if (wet < 0)
		goto ewwow_media_entity_wuntime_pm;

	wetuwn 0;

ewwow_media_entity_wuntime_pm:
	pm_wuntime_disabwe(&cwient->dev);
	if (fuww_powew)
		pm_wuntime_set_suspended(&cwient->dev);
	media_entity_cweanup(&ov13b->sd.entity);

ewwow_handwew_fwee:
	ov13b10_fwee_contwows(ov13b);
	dev_eww(&cwient->dev, "%s faiwed:%d\n", __func__, wet);

ewwow_powew_off:
	ov13b10_powew_off(&cwient->dev);

	wetuwn wet;
}

static void ov13b10_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ov13b10 *ov13b = to_ov13b10(sd);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	ov13b10_fwee_contwows(ov13b);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
}

static DEFINE_WUNTIME_DEV_PM_OPS(ov13b10_pm_ops, ov13b10_suspend,
				 ov13b10_wesume, NUWW);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id ov13b10_acpi_ids[] = {
	{"OVTIDB10"},
	{"OVTI13B1"},
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(acpi, ov13b10_acpi_ids);
#endif

static stwuct i2c_dwivew ov13b10_i2c_dwivew = {
	.dwivew = {
		.name = "ov13b10",
		.pm = pm_ptw(&ov13b10_pm_ops),
		.acpi_match_tabwe = ACPI_PTW(ov13b10_acpi_ids),
	},
	.pwobe = ov13b10_pwobe,
	.wemove = ov13b10_wemove,
	.fwags = I2C_DWV_ACPI_WAIVE_D0_PWOBE,
};

moduwe_i2c_dwivew(ov13b10_i2c_dwivew);

MODUWE_AUTHOW("Kao, Awec <awec.kao@intew.com>");
MODUWE_DESCWIPTION("Omnivision ov13b10 sensow dwivew");
MODUWE_WICENSE("GPW v2");
