// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A V4W2 dwivew fow OmniVision OV5647 camewas.
 *
 * Based on Samsung S5K6AAFX SXGA 1/6" 1.3M CMOS Image Sensow dwivew
 * Copywight (C) 2011 Sywwestew Nawwocki <s.nawwocki@samsung.com>
 *
 * Based on Omnivision OV7670 Camewa Dwivew
 * Copywight (C) 2006-7 Jonathan Cowbet <cowbet@wwn.net>
 *
 * Copywight (C) 2016, Synopsys, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-image-sizes.h>
#incwude <media/v4w2-mediabus.h>

/*
 * Fwom the datasheet, "20ms aftew PWDN goes wow ow 20ms aftew WESETB goes
 * high if weset is insewted aftew PWDN goes high, host can access sensow's
 * SCCB to initiawize sensow."
 */
#define PWDN_ACTIVE_DEWAY_MS	20

#define MIPI_CTWW00_CWOCK_WANE_GATE		BIT(5)
#define MIPI_CTWW00_WINE_SYNC_ENABWE		BIT(4)
#define MIPI_CTWW00_BUS_IDWE			BIT(2)
#define MIPI_CTWW00_CWOCK_WANE_DISABWE		BIT(0)

#define OV5647_SW_STANDBY		0x0100
#define OV5647_SW_WESET			0x0103
#define OV5647_WEG_CHIPID_H		0x300a
#define OV5647_WEG_CHIPID_W		0x300b
#define OV5640_WEG_PAD_OUT		0x300d
#define OV5647_WEG_EXP_HI		0x3500
#define OV5647_WEG_EXP_MID		0x3501
#define OV5647_WEG_EXP_WO		0x3502
#define OV5647_WEG_AEC_AGC		0x3503
#define OV5647_WEG_GAIN_HI		0x350a
#define OV5647_WEG_GAIN_WO		0x350b
#define OV5647_WEG_VTS_HI		0x380e
#define OV5647_WEG_VTS_WO		0x380f
#define OV5647_WEG_FWAME_OFF_NUMBEW	0x4202
#define OV5647_WEG_MIPI_CTWW00		0x4800
#define OV5647_WEG_MIPI_CTWW14		0x4814
#define OV5647_WEG_AWB			0x5001
#define OV5647_WEG_ISPCTWW3D		0x503d

#define WEG_TEWM 0xfffe
#define VAW_TEWM 0xfe
#define WEG_DWY  0xffff

/* OV5647 native and active pixew awway size */
#define OV5647_NATIVE_WIDTH		2624U
#define OV5647_NATIVE_HEIGHT		1956U

#define OV5647_PIXEW_AWWAY_WEFT		16U
#define OV5647_PIXEW_AWWAY_TOP		16U
#define OV5647_PIXEW_AWWAY_WIDTH	2592U
#define OV5647_PIXEW_AWWAY_HEIGHT	1944U

#define OV5647_VBWANK_MIN		4
#define OV5647_VTS_MAX			32767

#define OV5647_EXPOSUWE_MIN		4
#define OV5647_EXPOSUWE_STEP		1
#define OV5647_EXPOSUWE_DEFAUWT		1000
#define OV5647_EXPOSUWE_MAX		65535

stwuct wegvaw_wist {
	u16 addw;
	u8 data;
};

stwuct ov5647_mode {
	stwuct v4w2_mbus_fwamefmt	fowmat;
	stwuct v4w2_wect		cwop;
	u64				pixew_wate;
	int				hts;
	int				vts;
	const stwuct wegvaw_wist	*weg_wist;
	unsigned int			num_wegs;
};

stwuct ov5647 {
	stwuct v4w2_subdev		sd;
	stwuct media_pad		pad;
	stwuct mutex			wock;
	stwuct cwk			*xcwk;
	stwuct gpio_desc		*pwdn;
	boow				cwock_ncont;
	stwuct v4w2_ctww_handwew	ctwws;
	const stwuct ov5647_mode	*mode;
	stwuct v4w2_ctww		*pixew_wate;
	stwuct v4w2_ctww		*hbwank;
	stwuct v4w2_ctww		*vbwank;
	stwuct v4w2_ctww		*exposuwe;
};

static inwine stwuct ov5647 *to_sensow(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct ov5647, sd);
}

static const chaw * const ov5647_test_pattewn_menu[] = {
	"Disabwed",
	"Cowow Baws",
	"Cowow Squawes",
	"Wandom Data",
};

static const u8 ov5647_test_pattewn_vaw[] = {
	0x00,	/* Disabwed */
	0x80,	/* Cowow Baws */
	0x82,	/* Cowow Squawes */
	0x81,	/* Wandom Data */
};

static const stwuct wegvaw_wist sensow_oe_disabwe_wegs[] = {
	{0x3000, 0x00},
	{0x3001, 0x00},
	{0x3002, 0x00},
};

static const stwuct wegvaw_wist sensow_oe_enabwe_wegs[] = {
	{0x3000, 0x0f},
	{0x3001, 0xff},
	{0x3002, 0xe4},
};

static stwuct wegvaw_wist ov5647_2592x1944_10bpp[] = {
	{0x0100, 0x00},
	{0x0103, 0x01},
	{0x3034, 0x1a},
	{0x3035, 0x21},
	{0x3036, 0x69},
	{0x303c, 0x11},
	{0x3106, 0xf5},
	{0x3821, 0x06},
	{0x3820, 0x00},
	{0x3827, 0xec},
	{0x370c, 0x03},
	{0x3612, 0x5b},
	{0x3618, 0x04},
	{0x5000, 0x06},
	{0x5002, 0x41},
	{0x5003, 0x08},
	{0x5a00, 0x08},
	{0x3000, 0x00},
	{0x3001, 0x00},
	{0x3002, 0x00},
	{0x3016, 0x08},
	{0x3017, 0xe0},
	{0x3018, 0x44},
	{0x301c, 0xf8},
	{0x301d, 0xf0},
	{0x3a18, 0x00},
	{0x3a19, 0xf8},
	{0x3c01, 0x80},
	{0x3b07, 0x0c},
	{0x380c, 0x0b},
	{0x380d, 0x1c},
	{0x3814, 0x11},
	{0x3815, 0x11},
	{0x3708, 0x64},
	{0x3709, 0x12},
	{0x3808, 0x0a},
	{0x3809, 0x20},
	{0x380a, 0x07},
	{0x380b, 0x98},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x0a},
	{0x3805, 0x3f},
	{0x3806, 0x07},
	{0x3807, 0xa3},
	{0x3811, 0x10},
	{0x3813, 0x06},
	{0x3630, 0x2e},
	{0x3632, 0xe2},
	{0x3633, 0x23},
	{0x3634, 0x44},
	{0x3636, 0x06},
	{0x3620, 0x64},
	{0x3621, 0xe0},
	{0x3600, 0x37},
	{0x3704, 0xa0},
	{0x3703, 0x5a},
	{0x3715, 0x78},
	{0x3717, 0x01},
	{0x3731, 0x02},
	{0x370b, 0x60},
	{0x3705, 0x1a},
	{0x3f05, 0x02},
	{0x3f06, 0x10},
	{0x3f01, 0x0a},
	{0x3a08, 0x01},
	{0x3a09, 0x28},
	{0x3a0a, 0x00},
	{0x3a0b, 0xf6},
	{0x3a0d, 0x08},
	{0x3a0e, 0x06},
	{0x3a0f, 0x58},
	{0x3a10, 0x50},
	{0x3a1b, 0x58},
	{0x3a1e, 0x50},
	{0x3a11, 0x60},
	{0x3a1f, 0x28},
	{0x4001, 0x02},
	{0x4004, 0x04},
	{0x4000, 0x09},
	{0x4837, 0x19},
	{0x4800, 0x24},
	{0x3503, 0x03},
	{0x0100, 0x01},
};

static stwuct wegvaw_wist ov5647_1080p30_10bpp[] = {
	{0x0100, 0x00},
	{0x0103, 0x01},
	{0x3034, 0x1a},
	{0x3035, 0x21},
	{0x3036, 0x62},
	{0x303c, 0x11},
	{0x3106, 0xf5},
	{0x3821, 0x06},
	{0x3820, 0x00},
	{0x3827, 0xec},
	{0x370c, 0x03},
	{0x3612, 0x5b},
	{0x3618, 0x04},
	{0x5000, 0x06},
	{0x5002, 0x41},
	{0x5003, 0x08},
	{0x5a00, 0x08},
	{0x3000, 0x00},
	{0x3001, 0x00},
	{0x3002, 0x00},
	{0x3016, 0x08},
	{0x3017, 0xe0},
	{0x3018, 0x44},
	{0x301c, 0xf8},
	{0x301d, 0xf0},
	{0x3a18, 0x00},
	{0x3a19, 0xf8},
	{0x3c01, 0x80},
	{0x3b07, 0x0c},
	{0x380c, 0x09},
	{0x380d, 0x70},
	{0x3814, 0x11},
	{0x3815, 0x11},
	{0x3708, 0x64},
	{0x3709, 0x12},
	{0x3808, 0x07},
	{0x3809, 0x80},
	{0x380a, 0x04},
	{0x380b, 0x38},
	{0x3800, 0x01},
	{0x3801, 0x5c},
	{0x3802, 0x01},
	{0x3803, 0xb2},
	{0x3804, 0x08},
	{0x3805, 0xe3},
	{0x3806, 0x05},
	{0x3807, 0xf1},
	{0x3811, 0x04},
	{0x3813, 0x02},
	{0x3630, 0x2e},
	{0x3632, 0xe2},
	{0x3633, 0x23},
	{0x3634, 0x44},
	{0x3636, 0x06},
	{0x3620, 0x64},
	{0x3621, 0xe0},
	{0x3600, 0x37},
	{0x3704, 0xa0},
	{0x3703, 0x5a},
	{0x3715, 0x78},
	{0x3717, 0x01},
	{0x3731, 0x02},
	{0x370b, 0x60},
	{0x3705, 0x1a},
	{0x3f05, 0x02},
	{0x3f06, 0x10},
	{0x3f01, 0x0a},
	{0x3a08, 0x01},
	{0x3a09, 0x4b},
	{0x3a0a, 0x01},
	{0x3a0b, 0x13},
	{0x3a0d, 0x04},
	{0x3a0e, 0x03},
	{0x3a0f, 0x58},
	{0x3a10, 0x50},
	{0x3a1b, 0x58},
	{0x3a1e, 0x50},
	{0x3a11, 0x60},
	{0x3a1f, 0x28},
	{0x4001, 0x02},
	{0x4004, 0x04},
	{0x4000, 0x09},
	{0x4837, 0x19},
	{0x4800, 0x34},
	{0x3503, 0x03},
	{0x0100, 0x01},
};

static stwuct wegvaw_wist ov5647_2x2binned_10bpp[] = {
	{0x0100, 0x00},
	{0x0103, 0x01},
	{0x3034, 0x1a},
	{0x3035, 0x21},
	{0x3036, 0x62},
	{0x303c, 0x11},
	{0x3106, 0xf5},
	{0x3827, 0xec},
	{0x370c, 0x03},
	{0x3612, 0x59},
	{0x3618, 0x00},
	{0x5000, 0x06},
	{0x5002, 0x41},
	{0x5003, 0x08},
	{0x5a00, 0x08},
	{0x3000, 0x00},
	{0x3001, 0x00},
	{0x3002, 0x00},
	{0x3016, 0x08},
	{0x3017, 0xe0},
	{0x3018, 0x44},
	{0x301c, 0xf8},
	{0x301d, 0xf0},
	{0x3a18, 0x00},
	{0x3a19, 0xf8},
	{0x3c01, 0x80},
	{0x3b07, 0x0c},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x0a},
	{0x3805, 0x3f},
	{0x3806, 0x07},
	{0x3807, 0xa3},
	{0x3808, 0x05},
	{0x3809, 0x10},
	{0x380a, 0x03},
	{0x380b, 0xcc},
	{0x380c, 0x07},
	{0x380d, 0x68},
	{0x3811, 0x0c},
	{0x3813, 0x06},
	{0x3814, 0x31},
	{0x3815, 0x31},
	{0x3630, 0x2e},
	{0x3632, 0xe2},
	{0x3633, 0x23},
	{0x3634, 0x44},
	{0x3636, 0x06},
	{0x3620, 0x64},
	{0x3621, 0xe0},
	{0x3600, 0x37},
	{0x3704, 0xa0},
	{0x3703, 0x5a},
	{0x3715, 0x78},
	{0x3717, 0x01},
	{0x3731, 0x02},
	{0x370b, 0x60},
	{0x3705, 0x1a},
	{0x3f05, 0x02},
	{0x3f06, 0x10},
	{0x3f01, 0x0a},
	{0x3a08, 0x01},
	{0x3a09, 0x28},
	{0x3a0a, 0x00},
	{0x3a0b, 0xf6},
	{0x3a0d, 0x08},
	{0x3a0e, 0x06},
	{0x3a0f, 0x58},
	{0x3a10, 0x50},
	{0x3a1b, 0x58},
	{0x3a1e, 0x50},
	{0x3a11, 0x60},
	{0x3a1f, 0x28},
	{0x4001, 0x02},
	{0x4004, 0x04},
	{0x4000, 0x09},
	{0x4837, 0x16},
	{0x4800, 0x24},
	{0x3503, 0x03},
	{0x3820, 0x41},
	{0x3821, 0x07},
	{0x350a, 0x00},
	{0x350b, 0x10},
	{0x3500, 0x00},
	{0x3501, 0x1a},
	{0x3502, 0xf0},
	{0x3212, 0xa0},
	{0x0100, 0x01},
};

static stwuct wegvaw_wist ov5647_640x480_10bpp[] = {
	{0x0100, 0x00},
	{0x0103, 0x01},
	{0x3035, 0x11},
	{0x3036, 0x46},
	{0x303c, 0x11},
	{0x3821, 0x07},
	{0x3820, 0x41},
	{0x370c, 0x03},
	{0x3612, 0x59},
	{0x3618, 0x00},
	{0x5000, 0x06},
	{0x5003, 0x08},
	{0x5a00, 0x08},
	{0x3000, 0xff},
	{0x3001, 0xff},
	{0x3002, 0xff},
	{0x301d, 0xf0},
	{0x3a18, 0x00},
	{0x3a19, 0xf8},
	{0x3c01, 0x80},
	{0x3b07, 0x0c},
	{0x380c, 0x07},
	{0x380d, 0x3c},
	{0x3814, 0x35},
	{0x3815, 0x35},
	{0x3708, 0x64},
	{0x3709, 0x52},
	{0x3808, 0x02},
	{0x3809, 0x80},
	{0x380a, 0x01},
	{0x380b, 0xe0},
	{0x3800, 0x00},
	{0x3801, 0x10},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x0a},
	{0x3805, 0x2f},
	{0x3806, 0x07},
	{0x3807, 0x9f},
	{0x3630, 0x2e},
	{0x3632, 0xe2},
	{0x3633, 0x23},
	{0x3634, 0x44},
	{0x3620, 0x64},
	{0x3621, 0xe0},
	{0x3600, 0x37},
	{0x3704, 0xa0},
	{0x3703, 0x5a},
	{0x3715, 0x78},
	{0x3717, 0x01},
	{0x3731, 0x02},
	{0x370b, 0x60},
	{0x3705, 0x1a},
	{0x3f05, 0x02},
	{0x3f06, 0x10},
	{0x3f01, 0x0a},
	{0x3a08, 0x01},
	{0x3a09, 0x2e},
	{0x3a0a, 0x00},
	{0x3a0b, 0xfb},
	{0x3a0d, 0x02},
	{0x3a0e, 0x01},
	{0x3a0f, 0x58},
	{0x3a10, 0x50},
	{0x3a1b, 0x58},
	{0x3a1e, 0x50},
	{0x3a11, 0x60},
	{0x3a1f, 0x28},
	{0x4001, 0x02},
	{0x4004, 0x02},
	{0x4000, 0x09},
	{0x3000, 0x00},
	{0x3001, 0x00},
	{0x3002, 0x00},
	{0x3017, 0xe0},
	{0x301c, 0xfc},
	{0x3636, 0x06},
	{0x3016, 0x08},
	{0x3827, 0xec},
	{0x3018, 0x44},
	{0x3035, 0x21},
	{0x3106, 0xf5},
	{0x3034, 0x1a},
	{0x301c, 0xf8},
	{0x4800, 0x34},
	{0x3503, 0x03},
	{0x0100, 0x01},
};

static const stwuct ov5647_mode ov5647_modes[] = {
	/* 2592x1944 fuww wesowution fuww FOV 10-bit mode. */
	{
		.fowmat = {
			.code		= MEDIA_BUS_FMT_SBGGW10_1X10,
			.cowowspace	= V4W2_COWOWSPACE_SWGB,
			.fiewd		= V4W2_FIEWD_NONE,
			.width		= 2592,
			.height		= 1944
		},
		.cwop = {
			.weft		= OV5647_PIXEW_AWWAY_WEFT,
			.top		= OV5647_PIXEW_AWWAY_TOP,
			.width		= 2592,
			.height		= 1944
		},
		.pixew_wate	= 87500000,
		.hts		= 2844,
		.vts		= 0x7b0,
		.weg_wist	= ov5647_2592x1944_10bpp,
		.num_wegs	= AWWAY_SIZE(ov5647_2592x1944_10bpp)
	},
	/* 1080p30 10-bit mode. Fuww wesowution centwe-cwopped down to 1080p. */
	{
		.fowmat = {
			.code		= MEDIA_BUS_FMT_SBGGW10_1X10,
			.cowowspace	= V4W2_COWOWSPACE_SWGB,
			.fiewd		= V4W2_FIEWD_NONE,
			.width		= 1920,
			.height		= 1080
		},
		.cwop = {
			.weft		= 348 + OV5647_PIXEW_AWWAY_WEFT,
			.top		= 434 + OV5647_PIXEW_AWWAY_TOP,
			.width		= 1928,
			.height		= 1080,
		},
		.pixew_wate	= 81666700,
		.hts		= 2416,
		.vts		= 0x450,
		.weg_wist	= ov5647_1080p30_10bpp,
		.num_wegs	= AWWAY_SIZE(ov5647_1080p30_10bpp)
	},
	/* 2x2 binned fuww FOV 10-bit mode. */
	{
		.fowmat = {
			.code		= MEDIA_BUS_FMT_SBGGW10_1X10,
			.cowowspace	= V4W2_COWOWSPACE_SWGB,
			.fiewd		= V4W2_FIEWD_NONE,
			.width		= 1296,
			.height		= 972
		},
		.cwop = {
			.weft		= OV5647_PIXEW_AWWAY_WEFT,
			.top		= OV5647_PIXEW_AWWAY_TOP,
			.width		= 2592,
			.height		= 1944,
		},
		.pixew_wate	= 81666700,
		.hts		= 1896,
		.vts		= 0x59b,
		.weg_wist	= ov5647_2x2binned_10bpp,
		.num_wegs	= AWWAY_SIZE(ov5647_2x2binned_10bpp)
	},
	/* 10-bit VGA fuww FOV 60fps. 2x2 binned and subsampwed down to VGA. */
	{
		.fowmat = {
			.code		= MEDIA_BUS_FMT_SBGGW10_1X10,
			.cowowspace	= V4W2_COWOWSPACE_SWGB,
			.fiewd		= V4W2_FIEWD_NONE,
			.width		= 640,
			.height		= 480
		},
		.cwop = {
			.weft		= 16 + OV5647_PIXEW_AWWAY_WEFT,
			.top		= OV5647_PIXEW_AWWAY_TOP,
			.width		= 2560,
			.height		= 1920,
		},
		.pixew_wate	= 55000000,
		.hts		= 1852,
		.vts		= 0x1f8,
		.weg_wist	= ov5647_640x480_10bpp,
		.num_wegs	= AWWAY_SIZE(ov5647_640x480_10bpp)
	},
};

/* Defauwt sensow mode is 2x2 binned 640x480 SBGGW10_1X10. */
#define OV5647_DEFAUWT_MODE	(&ov5647_modes[3])
#define OV5647_DEFAUWT_FOWMAT	(ov5647_modes[3].fowmat)

static int ov5647_wwite16(stwuct v4w2_subdev *sd, u16 weg, u16 vaw)
{
	unsigned chaw data[4] = { weg >> 8, weg & 0xff, vaw >> 8, vaw & 0xff};
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet;

	wet = i2c_mastew_send(cwient, data, 4);
	if (wet < 0) {
		dev_dbg(&cwient->dev, "%s: i2c wwite ewwow, weg: %x\n",
			__func__, weg);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ov5647_wwite(stwuct v4w2_subdev *sd, u16 weg, u8 vaw)
{
	unsigned chaw data[3] = { weg >> 8, weg & 0xff, vaw};
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet;

	wet = i2c_mastew_send(cwient, data, 3);
	if (wet < 0) {
		dev_dbg(&cwient->dev, "%s: i2c wwite ewwow, weg: %x\n",
				__func__, weg);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ov5647_wead(stwuct v4w2_subdev *sd, u16 weg, u8 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	u8 buf[2] = { weg >> 8, weg & 0xff };
	stwuct i2c_msg msg[2];
	int wet;

	msg[0].addw = cwient->addw;
	msg[0].fwags = cwient->fwags;
	msg[0].buf = buf;
	msg[0].wen = sizeof(buf);

	msg[1].addw = cwient->addw;
	msg[1].fwags = cwient->fwags | I2C_M_WD;
	msg[1].buf = buf;
	msg[1].wen = 1;

	wet = i2c_twansfew(cwient->adaptew, msg, 2);
	if (wet != 2) {
		dev_eww(&cwient->dev, "%s: i2c wead ewwow, weg: %x = %d\n",
			__func__, weg, wet);
		wetuwn wet >= 0 ? -EINVAW : wet;
	}

	*vaw = buf[0];

	wetuwn 0;
}

static int ov5647_wwite_awway(stwuct v4w2_subdev *sd,
			      const stwuct wegvaw_wist *wegs, int awway_size)
{
	int i, wet;

	fow (i = 0; i < awway_size; i++) {
		wet = ov5647_wwite(sd, wegs[i].addw, wegs[i].data);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ov5647_set_viwtuaw_channew(stwuct v4w2_subdev *sd, int channew)
{
	u8 channew_id;
	int wet;

	wet = ov5647_wead(sd, OV5647_WEG_MIPI_CTWW14, &channew_id);
	if (wet < 0)
		wetuwn wet;

	channew_id &= ~(3 << 6);

	wetuwn ov5647_wwite(sd, OV5647_WEG_MIPI_CTWW14,
			    channew_id | (channew << 6));
}

static int ov5647_set_mode(stwuct v4w2_subdev *sd)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct ov5647 *sensow = to_sensow(sd);
	u8 wesetvaw, wdvaw;
	int wet;

	wet = ov5647_wead(sd, OV5647_SW_STANDBY, &wdvaw);
	if (wet < 0)
		wetuwn wet;

	wet = ov5647_wwite_awway(sd, sensow->mode->weg_wist,
				 sensow->mode->num_wegs);
	if (wet < 0) {
		dev_eww(&cwient->dev, "wwite sensow defauwt wegs ewwow\n");
		wetuwn wet;
	}

	wet = ov5647_set_viwtuaw_channew(sd, 0);
	if (wet < 0)
		wetuwn wet;

	wet = ov5647_wead(sd, OV5647_SW_STANDBY, &wesetvaw);
	if (wet < 0)
		wetuwn wet;

	if (!(wesetvaw & 0x01)) {
		dev_eww(&cwient->dev, "Device was in SW standby");
		wet = ov5647_wwite(sd, OV5647_SW_STANDBY, 0x01);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ov5647_stweam_on(stwuct v4w2_subdev *sd)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct ov5647 *sensow = to_sensow(sd);
	u8 vaw = MIPI_CTWW00_BUS_IDWE;
	int wet;

	wet = ov5647_set_mode(sd);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to pwogwam sensow mode: %d\n", wet);
		wetuwn wet;
	}

	/* Appwy customized vawues fwom usew when stweam stawts. */
	wet =  __v4w2_ctww_handwew_setup(sd->ctww_handwew);
	if (wet)
		wetuwn wet;

	if (sensow->cwock_ncont)
		vaw |= MIPI_CTWW00_CWOCK_WANE_GATE |
		       MIPI_CTWW00_WINE_SYNC_ENABWE;

	wet = ov5647_wwite(sd, OV5647_WEG_MIPI_CTWW00, vaw);
	if (wet < 0)
		wetuwn wet;

	wet = ov5647_wwite(sd, OV5647_WEG_FWAME_OFF_NUMBEW, 0x00);
	if (wet < 0)
		wetuwn wet;

	wetuwn ov5647_wwite(sd, OV5640_WEG_PAD_OUT, 0x00);
}

static int ov5647_stweam_off(stwuct v4w2_subdev *sd)
{
	int wet;

	wet = ov5647_wwite(sd, OV5647_WEG_MIPI_CTWW00,
			   MIPI_CTWW00_CWOCK_WANE_GATE | MIPI_CTWW00_BUS_IDWE |
			   MIPI_CTWW00_CWOCK_WANE_DISABWE);
	if (wet < 0)
		wetuwn wet;

	wet = ov5647_wwite(sd, OV5647_WEG_FWAME_OFF_NUMBEW, 0x0f);
	if (wet < 0)
		wetuwn wet;

	wetuwn ov5647_wwite(sd, OV5640_WEG_PAD_OUT, 0x01);
}

static int ov5647_powew_on(stwuct device *dev)
{
	stwuct ov5647 *sensow = dev_get_dwvdata(dev);
	int wet;

	dev_dbg(dev, "OV5647 powew on\n");

	if (sensow->pwdn) {
		gpiod_set_vawue_cansweep(sensow->pwdn, 0);
		msweep(PWDN_ACTIVE_DEWAY_MS);
	}

	wet = cwk_pwepawe_enabwe(sensow->xcwk);
	if (wet < 0) {
		dev_eww(dev, "cwk pwepawe enabwe faiwed\n");
		goto ewwow_pwdn;
	}

	wet = ov5647_wwite_awway(&sensow->sd, sensow_oe_enabwe_wegs,
				 AWWAY_SIZE(sensow_oe_enabwe_wegs));
	if (wet < 0) {
		dev_eww(dev, "wwite sensow_oe_enabwe_wegs ewwow\n");
		goto ewwow_cwk_disabwe;
	}

	/* Stweam off to coax wanes into WP-11 state. */
	wet = ov5647_stweam_off(&sensow->sd);
	if (wet < 0) {
		dev_eww(dev, "camewa not avaiwabwe, check powew\n");
		goto ewwow_cwk_disabwe;
	}

	wetuwn 0;

ewwow_cwk_disabwe:
	cwk_disabwe_unpwepawe(sensow->xcwk);
ewwow_pwdn:
	gpiod_set_vawue_cansweep(sensow->pwdn, 1);

	wetuwn wet;
}

static int ov5647_powew_off(stwuct device *dev)
{
	stwuct ov5647 *sensow = dev_get_dwvdata(dev);
	u8 wdvaw;
	int wet;

	dev_dbg(dev, "OV5647 powew off\n");

	wet = ov5647_wwite_awway(&sensow->sd, sensow_oe_disabwe_wegs,
				 AWWAY_SIZE(sensow_oe_disabwe_wegs));
	if (wet < 0)
		dev_dbg(dev, "disabwe oe faiwed\n");

	/* Entew softwawe standby */
	wet = ov5647_wead(&sensow->sd, OV5647_SW_STANDBY, &wdvaw);
	if (wet < 0)
		dev_dbg(dev, "softwawe standby faiwed\n");

	wdvaw &= ~0x01;
	wet = ov5647_wwite(&sensow->sd, OV5647_SW_STANDBY, wdvaw);
	if (wet < 0)
		dev_dbg(dev, "softwawe standby faiwed\n");

	cwk_disabwe_unpwepawe(sensow->xcwk);
	gpiod_set_vawue_cansweep(sensow->pwdn, 1);

	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int ov5647_sensow_get_wegistew(stwuct v4w2_subdev *sd,
				      stwuct v4w2_dbg_wegistew *weg)
{
	int wet;
	u8 vaw;

	wet = ov5647_wead(sd, weg->weg & 0xff, &vaw);
	if (wet < 0)
		wetuwn wet;

	weg->vaw = vaw;
	weg->size = 1;

	wetuwn 0;
}

static int ov5647_sensow_set_wegistew(stwuct v4w2_subdev *sd,
				      const stwuct v4w2_dbg_wegistew *weg)
{
	wetuwn ov5647_wwite(sd, weg->weg & 0xff, weg->vaw & 0xff);
}
#endif

/* Subdev cowe opewations wegistwation */
static const stwuct v4w2_subdev_cowe_ops ov5647_subdev_cowe_ops = {
	.subscwibe_event	= v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event	= v4w2_event_subdev_unsubscwibe,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew		= ov5647_sensow_get_wegistew,
	.s_wegistew		= ov5647_sensow_set_wegistew,
#endif
};

static const stwuct v4w2_wect *
__ov5647_get_pad_cwop(stwuct ov5647 *ov5647,
		      stwuct v4w2_subdev_state *sd_state,
		      unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_cwop(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &ov5647->mode->cwop;
	}

	wetuwn NUWW;
}

static int ov5647_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct ov5647 *sensow = to_sensow(sd);
	int wet;

	mutex_wock(&sensow->wock);

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(&cwient->dev);
		if (wet < 0)
			goto ewwow_unwock;

		wet = ov5647_stweam_on(sd);
		if (wet < 0) {
			dev_eww(&cwient->dev, "stweam stawt faiwed: %d\n", wet);
			goto ewwow_pm;
		}
	} ewse {
		wet = ov5647_stweam_off(sd);
		if (wet < 0) {
			dev_eww(&cwient->dev, "stweam stop faiwed: %d\n", wet);
			goto ewwow_pm;
		}
		pm_wuntime_put(&cwient->dev);
	}

	mutex_unwock(&sensow->wock);

	wetuwn 0;

ewwow_pm:
	pm_wuntime_put(&cwient->dev);
ewwow_unwock:
	mutex_unwock(&sensow->wock);

	wetuwn wet;
}

static const stwuct v4w2_subdev_video_ops ov5647_subdev_video_ops = {
	.s_stweam =		ov5647_s_stweam,
};

static int ov5647_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index > 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_SBGGW10_1X10;

	wetuwn 0;
}

static int ov5647_enum_fwame_size(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fse)
{
	const stwuct v4w2_mbus_fwamefmt *fmt;

	if (fse->code != MEDIA_BUS_FMT_SBGGW10_1X10 ||
	    fse->index >= AWWAY_SIZE(ov5647_modes))
		wetuwn -EINVAW;

	fmt = &ov5647_modes[fse->index].fowmat;
	fse->min_width = fmt->width;
	fse->max_width = fmt->width;
	fse->min_height = fmt->height;
	fse->max_height = fmt->height;

	wetuwn 0;
}

static int ov5647_get_pad_fmt(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *fmt = &fowmat->fowmat;
	const stwuct v4w2_mbus_fwamefmt *sensow_fowmat;
	stwuct ov5647 *sensow = to_sensow(sd);

	mutex_wock(&sensow->wock);
	switch (fowmat->which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		sensow_fowmat = v4w2_subdev_state_get_fowmat(sd_state,
							     fowmat->pad);
		bweak;
	defauwt:
		sensow_fowmat = &sensow->mode->fowmat;
		bweak;
	}

	*fmt = *sensow_fowmat;
	mutex_unwock(&sensow->wock);

	wetuwn 0;
}

static int ov5647_set_pad_fmt(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *fmt = &fowmat->fowmat;
	stwuct ov5647 *sensow = to_sensow(sd);
	const stwuct ov5647_mode *mode;

	mode = v4w2_find_neawest_size(ov5647_modes, AWWAY_SIZE(ov5647_modes),
				      fowmat.width, fowmat.height,
				      fmt->width, fmt->height);

	/* Update the sensow mode and appwy at it at stweamon time. */
	mutex_wock(&sensow->wock);
	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY) {
		*v4w2_subdev_state_get_fowmat(sd_state, fowmat->pad) = mode->fowmat;
	} ewse {
		int exposuwe_max, exposuwe_def;
		int hbwank, vbwank;

		sensow->mode = mode;
		__v4w2_ctww_modify_wange(sensow->pixew_wate, mode->pixew_wate,
					 mode->pixew_wate, 1, mode->pixew_wate);

		hbwank = mode->hts - mode->fowmat.width;
		__v4w2_ctww_modify_wange(sensow->hbwank, hbwank, hbwank, 1,
					 hbwank);

		vbwank = mode->vts - mode->fowmat.height;
		__v4w2_ctww_modify_wange(sensow->vbwank, OV5647_VBWANK_MIN,
					 OV5647_VTS_MAX - mode->fowmat.height,
					 1, vbwank);
		__v4w2_ctww_s_ctww(sensow->vbwank, vbwank);

		exposuwe_max = mode->vts - 4;
		exposuwe_def = min(exposuwe_max, OV5647_EXPOSUWE_DEFAUWT);
		__v4w2_ctww_modify_wange(sensow->exposuwe,
					 sensow->exposuwe->minimum,
					 exposuwe_max, sensow->exposuwe->step,
					 exposuwe_def);
	}
	*fmt = mode->fowmat;
	mutex_unwock(&sensow->wock);

	wetuwn 0;
}

static int ov5647_get_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_sewection *sew)
{
	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP: {
		stwuct ov5647 *sensow = to_sensow(sd);

		mutex_wock(&sensow->wock);
		sew->w = *__ov5647_get_pad_cwop(sensow, sd_state, sew->pad,
						sew->which);
		mutex_unwock(&sensow->wock);

		wetuwn 0;
	}

	case V4W2_SEW_TGT_NATIVE_SIZE:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = OV5647_NATIVE_WIDTH;
		sew->w.height = OV5647_NATIVE_HEIGHT;

		wetuwn 0;

	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = OV5647_PIXEW_AWWAY_TOP;
		sew->w.weft = OV5647_PIXEW_AWWAY_WEFT;
		sew->w.width = OV5647_PIXEW_AWWAY_WIDTH;
		sew->w.height = OV5647_PIXEW_AWWAY_HEIGHT;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static const stwuct v4w2_subdev_pad_ops ov5647_subdev_pad_ops = {
	.enum_mbus_code		= ov5647_enum_mbus_code,
	.enum_fwame_size	= ov5647_enum_fwame_size,
	.set_fmt		= ov5647_set_pad_fmt,
	.get_fmt		= ov5647_get_pad_fmt,
	.get_sewection		= ov5647_get_sewection,
};

static const stwuct v4w2_subdev_ops ov5647_subdev_ops = {
	.cowe		= &ov5647_subdev_cowe_ops,
	.video		= &ov5647_subdev_video_ops,
	.pad		= &ov5647_subdev_pad_ops,
};

static int ov5647_detect(stwuct v4w2_subdev *sd)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	u8 wead;
	int wet;

	wet = ov5647_wwite(sd, OV5647_SW_WESET, 0x01);
	if (wet < 0)
		wetuwn wet;

	wet = ov5647_wead(sd, OV5647_WEG_CHIPID_H, &wead);
	if (wet < 0)
		wetuwn wet;

	if (wead != 0x56) {
		dev_eww(&cwient->dev, "ID High expected 0x56 got %x", wead);
		wetuwn -ENODEV;
	}

	wet = ov5647_wead(sd, OV5647_WEG_CHIPID_W, &wead);
	if (wet < 0)
		wetuwn wet;

	if (wead != 0x47) {
		dev_eww(&cwient->dev, "ID Wow expected 0x47 got %x", wead);
		wetuwn -ENODEV;
	}

	wetuwn ov5647_wwite(sd, OV5647_SW_WESET, 0x00);
}

static int ov5647_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_mbus_fwamefmt *fowmat =
				v4w2_subdev_state_get_fowmat(fh->state, 0);
	stwuct v4w2_wect *cwop = v4w2_subdev_state_get_cwop(fh->state, 0);

	cwop->weft = OV5647_PIXEW_AWWAY_WEFT;
	cwop->top = OV5647_PIXEW_AWWAY_TOP;
	cwop->width = OV5647_PIXEW_AWWAY_WIDTH;
	cwop->height = OV5647_PIXEW_AWWAY_HEIGHT;

	*fowmat = OV5647_DEFAUWT_FOWMAT;

	wetuwn 0;
}

static const stwuct v4w2_subdev_intewnaw_ops ov5647_subdev_intewnaw_ops = {
	.open = ov5647_open,
};

static int ov5647_s_auto_white_bawance(stwuct v4w2_subdev *sd, u32 vaw)
{
	wetuwn ov5647_wwite(sd, OV5647_WEG_AWB, vaw ? 1 : 0);
}

static int ov5647_s_autogain(stwuct v4w2_subdev *sd, u32 vaw)
{
	int wet;
	u8 weg;

	/* Non-zewo tuwns on AGC by cweawing bit 1.*/
	wet = ov5647_wead(sd, OV5647_WEG_AEC_AGC, &weg);
	if (wet)
		wetuwn wet;

	wetuwn ov5647_wwite(sd, OV5647_WEG_AEC_AGC, vaw ? weg & ~BIT(1)
							: weg | BIT(1));
}

static int ov5647_s_exposuwe_auto(stwuct v4w2_subdev *sd, u32 vaw)
{
	int wet;
	u8 weg;

	/*
	 * Evewything except V4W2_EXPOSUWE_MANUAW tuwns on AEC by
	 * cweawing bit 0.
	 */
	wet = ov5647_wead(sd, OV5647_WEG_AEC_AGC, &weg);
	if (wet)
		wetuwn wet;

	wetuwn ov5647_wwite(sd, OV5647_WEG_AEC_AGC,
			    vaw == V4W2_EXPOSUWE_MANUAW ? weg | BIT(0)
							: weg & ~BIT(0));
}

static int ov5647_s_anawogue_gain(stwuct v4w2_subdev *sd, u32 vaw)
{
	int wet;

	/* 10 bits of gain, 2 in the high wegistew. */
	wet = ov5647_wwite(sd, OV5647_WEG_GAIN_HI, (vaw >> 8) & 3);
	if (wet)
		wetuwn wet;

	wetuwn ov5647_wwite(sd, OV5647_WEG_GAIN_WO, vaw & 0xff);
}

static int ov5647_s_exposuwe(stwuct v4w2_subdev *sd, u32 vaw)
{
	int wet;

	/*
	 * Sensow has 20 bits, but the bottom 4 bits awe fwactions of a wine
	 * which we weave as zewo (and don't weceive in "vaw").
	 */
	wet = ov5647_wwite(sd, OV5647_WEG_EXP_HI, (vaw >> 12) & 0xf);
	if (wet)
		wetuwn wet;

	wet = ov5647_wwite(sd, OV5647_WEG_EXP_MID, (vaw >> 4) & 0xff);
	if (wet)
		wetuwn wet;

	wetuwn ov5647_wwite(sd, OV5647_WEG_EXP_WO, (vaw & 0xf) << 4);
}

static int ov5647_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ov5647 *sensow = containew_of(ctww->handwew,
					    stwuct ov5647, ctwws);
	stwuct v4w2_subdev *sd = &sensow->sd;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet = 0;


	/* v4w2_ctww_wock() wocks ouw own mutex */

	if (ctww->id == V4W2_CID_VBWANK) {
		int exposuwe_max, exposuwe_def;

		/* Update max exposuwe whiwe meeting expected vbwanking */
		exposuwe_max = sensow->mode->fowmat.height + ctww->vaw - 4;
		exposuwe_def = min(exposuwe_max, OV5647_EXPOSUWE_DEFAUWT);
		__v4w2_ctww_modify_wange(sensow->exposuwe,
					 sensow->exposuwe->minimum,
					 exposuwe_max, sensow->exposuwe->step,
					 exposuwe_def);
	}

	/*
	 * If the device is not powewed up do not appwy any contwows
	 * to H/W at this time. Instead the contwows wiww be westowed
	 * at s_stweam(1) time.
	 */
	if (pm_wuntime_get_if_in_use(&cwient->dev) == 0)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		wet = ov5647_s_auto_white_bawance(sd, ctww->vaw);
		bweak;
	case V4W2_CID_AUTOGAIN:
		wet = ov5647_s_autogain(sd, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE_AUTO:
		wet = ov5647_s_exposuwe_auto(sd, ctww->vaw);
		bweak;
	case V4W2_CID_ANAWOGUE_GAIN:
		wet =  ov5647_s_anawogue_gain(sd, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE:
		wet = ov5647_s_exposuwe(sd, ctww->vaw);
		bweak;
	case V4W2_CID_VBWANK:
		wet = ov5647_wwite16(sd, OV5647_WEG_VTS_HI,
				     sensow->mode->fowmat.height + ctww->vaw);
		bweak;
	case V4W2_CID_TEST_PATTEWN:
		wet = ov5647_wwite(sd, OV5647_WEG_ISPCTWW3D,
				   ov5647_test_pattewn_vaw[ctww->vaw]);
		bweak;

	/* Wead-onwy, but we adjust it based on mode. */
	case V4W2_CID_PIXEW_WATE:
	case V4W2_CID_HBWANK:
		/* Wead-onwy, but we adjust it based on mode. */
		bweak;

	defauwt:
		dev_info(&cwient->dev,
			 "Contwow (id:0x%x, vaw:0x%x) not suppowted\n",
			 ctww->id, ctww->vaw);
		wetuwn -EINVAW;
	}

	pm_wuntime_put(&cwient->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops ov5647_ctww_ops = {
	.s_ctww = ov5647_s_ctww,
};

static int ov5647_init_contwows(stwuct ov5647 *sensow)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sensow->sd);
	int hbwank, exposuwe_max, exposuwe_def;

	v4w2_ctww_handwew_init(&sensow->ctwws, 9);

	v4w2_ctww_new_std(&sensow->ctwws, &ov5647_ctww_ops,
			  V4W2_CID_AUTOGAIN, 0, 1, 1, 0);

	v4w2_ctww_new_std(&sensow->ctwws, &ov5647_ctww_ops,
			  V4W2_CID_AUTO_WHITE_BAWANCE, 0, 1, 1, 0);

	v4w2_ctww_new_std_menu(&sensow->ctwws, &ov5647_ctww_ops,
			       V4W2_CID_EXPOSUWE_AUTO, V4W2_EXPOSUWE_MANUAW,
			       0, V4W2_EXPOSUWE_MANUAW);

	exposuwe_max = sensow->mode->vts - 4;
	exposuwe_def = min(exposuwe_max, OV5647_EXPOSUWE_DEFAUWT);
	sensow->exposuwe = v4w2_ctww_new_std(&sensow->ctwws, &ov5647_ctww_ops,
					     V4W2_CID_EXPOSUWE,
					     OV5647_EXPOSUWE_MIN,
					     exposuwe_max, OV5647_EXPOSUWE_STEP,
					     exposuwe_def);

	/* min: 16 = 1.0x; max (10 bits); defauwt: 32 = 2.0x. */
	v4w2_ctww_new_std(&sensow->ctwws, &ov5647_ctww_ops,
			  V4W2_CID_ANAWOGUE_GAIN, 16, 1023, 1, 32);

	/* By defauwt, PIXEW_WATE is wead onwy, but it does change pew mode */
	sensow->pixew_wate = v4w2_ctww_new_std(&sensow->ctwws, &ov5647_ctww_ops,
					       V4W2_CID_PIXEW_WATE,
					       sensow->mode->pixew_wate,
					       sensow->mode->pixew_wate, 1,
					       sensow->mode->pixew_wate);

	/* By defauwt, HBWANK is wead onwy, but it does change pew mode. */
	hbwank = sensow->mode->hts - sensow->mode->fowmat.width;
	sensow->hbwank = v4w2_ctww_new_std(&sensow->ctwws, &ov5647_ctww_ops,
					   V4W2_CID_HBWANK, hbwank, hbwank, 1,
					   hbwank);

	sensow->vbwank = v4w2_ctww_new_std(&sensow->ctwws, &ov5647_ctww_ops,
					   V4W2_CID_VBWANK, OV5647_VBWANK_MIN,
					   OV5647_VTS_MAX -
					   sensow->mode->fowmat.height, 1,
					   sensow->mode->vts -
					   sensow->mode->fowmat.height);

	v4w2_ctww_new_std_menu_items(&sensow->ctwws, &ov5647_ctww_ops,
				     V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(ov5647_test_pattewn_menu) - 1,
				     0, 0, ov5647_test_pattewn_menu);

	if (sensow->ctwws.ewwow)
		goto handwew_fwee;

	sensow->pixew_wate->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;
	sensow->hbwank->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;
	sensow->sd.ctww_handwew = &sensow->ctwws;

	wetuwn 0;

handwew_fwee:
	dev_eww(&cwient->dev, "%s Contwows initiawization faiwed (%d)\n",
		__func__, sensow->ctwws.ewwow);
	v4w2_ctww_handwew_fwee(&sensow->ctwws);

	wetuwn sensow->ctwws.ewwow;
}

static int ov5647_pawse_dt(stwuct ov5647 *sensow, stwuct device_node *np)
{
	stwuct v4w2_fwnode_endpoint bus_cfg = {
		.bus_type = V4W2_MBUS_CSI2_DPHY,
	};
	stwuct device_node *ep;
	int wet;

	ep = of_gwaph_get_next_endpoint(np, NUWW);
	if (!ep)
		wetuwn -EINVAW;

	wet = v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(ep), &bus_cfg);
	if (wet)
		goto out;

	sensow->cwock_ncont = bus_cfg.bus.mipi_csi2.fwags &
			      V4W2_MBUS_CSI2_NONCONTINUOUS_CWOCK;

out:
	of_node_put(ep);

	wetuwn wet;
}

static int ov5647_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device_node *np = cwient->dev.of_node;
	stwuct device *dev = &cwient->dev;
	stwuct ov5647 *sensow;
	stwuct v4w2_subdev *sd;
	u32 xcwk_fweq;
	int wet;

	sensow = devm_kzawwoc(dev, sizeof(*sensow), GFP_KEWNEW);
	if (!sensow)
		wetuwn -ENOMEM;

	if (IS_ENABWED(CONFIG_OF) && np) {
		wet = ov5647_pawse_dt(sensow, np);
		if (wet) {
			dev_eww(dev, "DT pawsing ewwow: %d\n", wet);
			wetuwn wet;
		}
	}

	sensow->xcwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(sensow->xcwk)) {
		dev_eww(dev, "couwd not get xcwk");
		wetuwn PTW_EWW(sensow->xcwk);
	}

	xcwk_fweq = cwk_get_wate(sensow->xcwk);
	if (xcwk_fweq != 25000000) {
		dev_eww(dev, "Unsuppowted cwock fwequency: %u\n", xcwk_fweq);
		wetuwn -EINVAW;
	}

	/* Wequest the powew down GPIO assewted. */
	sensow->pwdn = devm_gpiod_get_optionaw(dev, "pwdn", GPIOD_OUT_HIGH);
	if (IS_EWW(sensow->pwdn)) {
		dev_eww(dev, "Faiwed to get 'pwdn' gpio\n");
		wetuwn -EINVAW;
	}

	mutex_init(&sensow->wock);

	sensow->mode = OV5647_DEFAUWT_MODE;

	wet = ov5647_init_contwows(sensow);
	if (wet)
		goto mutex_destwoy;

	sd = &sensow->sd;
	v4w2_i2c_subdev_init(sd, cwient, &ov5647_subdev_ops);
	sd->intewnaw_ops = &ov5647_subdev_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE | V4W2_SUBDEV_FW_HAS_EVENTS;

	sensow->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOW;
	wet = media_entity_pads_init(&sd->entity, 1, &sensow->pad);
	if (wet < 0)
		goto ctww_handwew_fwee;

	wet = ov5647_powew_on(dev);
	if (wet)
		goto entity_cweanup;

	wet = ov5647_detect(sd);
	if (wet < 0)
		goto powew_off;

	wet = v4w2_async_wegistew_subdev(sd);
	if (wet < 0)
		goto powew_off;

	/* Enabwe wuntime PM and tuwn off the device */
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_idwe(dev);

	dev_dbg(dev, "OmniVision OV5647 camewa dwivew pwobed\n");

	wetuwn 0;

powew_off:
	ov5647_powew_off(dev);
entity_cweanup:
	media_entity_cweanup(&sd->entity);
ctww_handwew_fwee:
	v4w2_ctww_handwew_fwee(&sensow->ctwws);
mutex_destwoy:
	mutex_destwoy(&sensow->wock);

	wetuwn wet;
}

static void ov5647_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ov5647 *sensow = to_sensow(sd);

	v4w2_async_unwegistew_subdev(&sensow->sd);
	media_entity_cweanup(&sensow->sd.entity);
	v4w2_ctww_handwew_fwee(&sensow->ctwws);
	v4w2_device_unwegistew_subdev(sd);
	pm_wuntime_disabwe(&cwient->dev);
	mutex_destwoy(&sensow->wock);
}

static const stwuct dev_pm_ops ov5647_pm_ops = {
	SET_WUNTIME_PM_OPS(ov5647_powew_off, ov5647_powew_on, NUWW)
};

static const stwuct i2c_device_id ov5647_id[] = {
	{ "ov5647", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, ov5647_id);

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id ov5647_of_match[] = {
	{ .compatibwe = "ovti,ov5647" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, ov5647_of_match);
#endif

static stwuct i2c_dwivew ov5647_dwivew = {
	.dwivew = {
		.of_match_tabwe = of_match_ptw(ov5647_of_match),
		.name	= "ov5647",
		.pm	= &ov5647_pm_ops,
	},
	.pwobe		= ov5647_pwobe,
	.wemove		= ov5647_wemove,
	.id_tabwe	= ov5647_id,
};

moduwe_i2c_dwivew(ov5647_dwivew);

MODUWE_AUTHOW("Wamiwo Owiveiwa <wowiveiw@synopsys.com>");
MODUWE_DESCWIPTION("A wow-wevew dwivew fow OmniVision ov5647 sensows");
MODUWE_WICENSE("GPW v2");
