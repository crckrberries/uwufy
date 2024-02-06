// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2023 Jacopo Mondi <jacopo.mondi@ideasonboawd.com>
 * Copywight (C) 2022 Nichowas Woth <nichowas@wothemaiw.net>
 * Copywight (C) 2017 Fuzhou Wockchip Ewectwonics Co., Wtd.
 */

#incwude <asm/unawigned.h>

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/v4w2-subdev.h>

#define OV8858_WINK_FWEQ		360000000U
#define OV8858_XVCWK_FWEQ		24000000

#define OV8858_WEG_SIZE_SHIFT		16
#define OV8858_WEG_ADDW_MASK		0xffff
#define OV8858_WEG_8BIT(n)		((1U << OV8858_WEG_SIZE_SHIFT) | (n))
#define OV8858_WEG_16BIT(n)		((2U << OV8858_WEG_SIZE_SHIFT) | (n))
#define OV8858_WEG_24BIT(n)		((3U << OV8858_WEG_SIZE_SHIFT) | (n))

#define OV8858_WEG_SC_CTWW0100		OV8858_WEG_8BIT(0x0100)
#define OV8858_MODE_SW_STANDBY		0x0
#define OV8858_MODE_STWEAMING		0x1

#define OV8858_WEG_CHIP_ID		OV8858_WEG_24BIT(0x300a)
#define OV8858_CHIP_ID			0x008858

#define OV8858_WEG_SUB_ID		OV8858_WEG_8BIT(0x302a)
#define OV8858_W1A			0xb0
#define OV8858_W2A			0xb2

#define OV8858_WEG_WONG_EXPO		OV8858_WEG_24BIT(0x3500)
#define OV8858_EXPOSUWE_MIN		4
#define OV8858_EXPOSUWE_STEP		1
#define OV8858_EXPOSUWE_MAWGIN		4

#define OV8858_WEG_WONG_GAIN		OV8858_WEG_16BIT(0x3508)
#define OV8858_WONG_GAIN_MIN		0x0
#define OV8858_WONG_GAIN_MAX		0x7ff
#define OV8858_WONG_GAIN_STEP		1
#define OV8858_WONG_GAIN_DEFAUWT	0x80

#define OV8858_WEG_WONG_DIGIGAIN	OV8858_WEG_16BIT(0x350a)
#define OV8858_WONG_DIGIGAIN_H_MASK	0x3fc0
#define OV8858_WONG_DIGIGAIN_W_MASK	0x3f
#define OV8858_WONG_DIGIGAIN_H_SHIFT	2
#define OV8858_WONG_DIGIGAIN_MIN	0x0
#define OV8858_WONG_DIGIGAIN_MAX	0x3fff
#define OV8858_WONG_DIGIGAIN_STEP	1
#define OV8858_WONG_DIGIGAIN_DEFAUWT	0x200

#define OV8858_WEG_VTS			OV8858_WEG_16BIT(0x380e)
#define OV8858_VTS_MAX			0x7fff

#define OV8858_WEG_TEST_PATTEWN		OV8858_WEG_8BIT(0x5e00)
#define OV8858_TEST_PATTEWN_ENABWE	0x80
#define OV8858_TEST_PATTEWN_DISABWE	0x0

#define WEG_NUWW			0xffff

static const chaw * const ov8858_suppwy_names[] = {
	"avdd",		/* Anawog powew */
	"dovdd",	/* Digitaw I/O powew */
	"dvdd",		/* Digitaw cowe powew */
};

stwuct wegvaw {
	u16 addw;
	u8 vaw;
};

stwuct wegvaw_modes {
	const stwuct wegvaw *mode_2wanes;
	const stwuct wegvaw *mode_4wanes;
};

stwuct ov8858_mode {
	u32 width;
	u32 height;
	u32 hts_def;
	u32 vts_def;
	u32 exp_def;
	const stwuct wegvaw_modes weg_modes;
};

stwuct ov8858 {
	stwuct cwk		*xvcwk;
	stwuct gpio_desc	*weset_gpio;
	stwuct gpio_desc	*pwdn_gpio;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(ov8858_suppwy_names)];

	stwuct v4w2_subdev	subdev;
	stwuct media_pad	pad;

	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww	*exposuwe;
	stwuct v4w2_ctww	*hbwank;
	stwuct v4w2_ctww	*vbwank;

	const stwuct wegvaw	*gwobaw_wegs;

	unsigned int		num_wanes;
};

static inwine stwuct ov8858 *sd_to_ov8858(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct ov8858, subdev);
}

static const stwuct wegvaw ov8858_gwobaw_wegs_w1a[] = {
	{0x0100, 0x00},
	{0x0100, 0x00},
	{0x0100, 0x00},
	{0x0100, 0x00},
	{0x0302, 0x1e},
	{0x0303, 0x00},
	{0x0304, 0x03},
	{0x030e, 0x00},
	{0x030f, 0x09},
	{0x0312, 0x01},
	{0x031e, 0x0c},
	{0x3600, 0x00},
	{0x3601, 0x00},
	{0x3602, 0x00},
	{0x3603, 0x00},
	{0x3604, 0x22},
	{0x3605, 0x30},
	{0x3606, 0x00},
	{0x3607, 0x20},
	{0x3608, 0x11},
	{0x3609, 0x28},
	{0x360a, 0x00},
	{0x360b, 0x06},
	{0x360c, 0xdc},
	{0x360d, 0x40},
	{0x360e, 0x0c},
	{0x360f, 0x20},
	{0x3610, 0x07},
	{0x3611, 0x20},
	{0x3612, 0x88},
	{0x3613, 0x80},
	{0x3614, 0x58},
	{0x3615, 0x00},
	{0x3616, 0x4a},
	{0x3617, 0xb0},
	{0x3618, 0x56},
	{0x3619, 0x70},
	{0x361a, 0x99},
	{0x361b, 0x00},
	{0x361c, 0x07},
	{0x361d, 0x00},
	{0x361e, 0x00},
	{0x361f, 0x00},
	{0x3638, 0xff},
	{0x3633, 0x0c},
	{0x3634, 0x0c},
	{0x3635, 0x0c},
	{0x3636, 0x0c},
	{0x3645, 0x13},
	{0x3646, 0x83},
	{0x364a, 0x07},
	{0x3015, 0x01},
	{0x3018, 0x32},
	{0x3020, 0x93},
	{0x3022, 0x01},
	{0x3031, 0x0a},
	{0x3034, 0x00},
	{0x3106, 0x01},
	{0x3305, 0xf1},
	{0x3308, 0x00},
	{0x3309, 0x28},
	{0x330a, 0x00},
	{0x330b, 0x20},
	{0x330c, 0x00},
	{0x330d, 0x00},
	{0x330e, 0x00},
	{0x330f, 0x40},
	{0x3307, 0x04},
	{0x3500, 0x00},
	{0x3501, 0x4d},
	{0x3502, 0x40},
	{0x3503, 0x00},
	{0x3505, 0x80},
	{0x3508, 0x04},
	{0x3509, 0x00},
	{0x350c, 0x00},
	{0x350d, 0x80},
	{0x3510, 0x00},
	{0x3511, 0x02},
	{0x3512, 0x00},
	{0x3700, 0x18},
	{0x3701, 0x0c},
	{0x3702, 0x28},
	{0x3703, 0x19},
	{0x3704, 0x14},
	{0x3705, 0x00},
	{0x3706, 0x35},
	{0x3707, 0x04},
	{0x3708, 0x24},
	{0x3709, 0x33},
	{0x370a, 0x00},
	{0x370b, 0xb5},
	{0x370c, 0x04},
	{0x3718, 0x12},
	{0x3719, 0x31},
	{0x3712, 0x42},
	{0x3714, 0x24},
	{0x371e, 0x19},
	{0x371f, 0x40},
	{0x3720, 0x05},
	{0x3721, 0x05},
	{0x3724, 0x06},
	{0x3725, 0x01},
	{0x3726, 0x06},
	{0x3728, 0x05},
	{0x3729, 0x02},
	{0x372a, 0x03},
	{0x372b, 0x53},
	{0x372c, 0xa3},
	{0x372d, 0x53},
	{0x372e, 0x06},
	{0x372f, 0x10},
	{0x3730, 0x01},
	{0x3731, 0x06},
	{0x3732, 0x14},
	{0x3733, 0x10},
	{0x3734, 0x40},
	{0x3736, 0x20},
	{0x373a, 0x05},
	{0x373b, 0x06},
	{0x373c, 0x0a},
	{0x373e, 0x03},
	{0x3755, 0x10},
	{0x3758, 0x00},
	{0x3759, 0x4c},
	{0x375a, 0x06},
	{0x375b, 0x13},
	{0x375c, 0x20},
	{0x375d, 0x02},
	{0x375e, 0x00},
	{0x375f, 0x14},
	{0x3768, 0x22},
	{0x3769, 0x44},
	{0x376a, 0x44},
	{0x3761, 0x00},
	{0x3762, 0x00},
	{0x3763, 0x00},
	{0x3766, 0xff},
	{0x376b, 0x00},
	{0x3772, 0x23},
	{0x3773, 0x02},
	{0x3774, 0x16},
	{0x3775, 0x12},
	{0x3776, 0x04},
	{0x3777, 0x00},
	{0x3778, 0x1b},
	{0x37a0, 0x44},
	{0x37a1, 0x3d},
	{0x37a2, 0x3d},
	{0x37a3, 0x00},
	{0x37a4, 0x00},
	{0x37a5, 0x00},
	{0x37a6, 0x00},
	{0x37a7, 0x44},
	{0x37a8, 0x4c},
	{0x37a9, 0x4c},
	{0x3760, 0x00},
	{0x376f, 0x01},
	{0x37aa, 0x44},
	{0x37ab, 0x2e},
	{0x37ac, 0x2e},
	{0x37ad, 0x33},
	{0x37ae, 0x0d},
	{0x37af, 0x0d},
	{0x37b0, 0x00},
	{0x37b1, 0x00},
	{0x37b2, 0x00},
	{0x37b3, 0x42},
	{0x37b4, 0x42},
	{0x37b5, 0x33},
	{0x37b6, 0x00},
	{0x37b7, 0x00},
	{0x37b8, 0x00},
	{0x37b9, 0xff},
	{0x3800, 0x00},
	{0x3801, 0x0c},
	{0x3802, 0x00},
	{0x3803, 0x0c},
	{0x3804, 0x0c},
	{0x3805, 0xd3},
	{0x3806, 0x09},
	{0x3807, 0xa3},
	{0x3808, 0x06},
	{0x3809, 0x60},
	{0x380a, 0x04},
	{0x380b, 0xc8},
	{0x380c, 0x07},
	{0x380d, 0x88},
	{0x380e, 0x04},
	{0x380f, 0xdc},
	{0x3810, 0x00},
	{0x3811, 0x04},
	{0x3813, 0x02},
	{0x3814, 0x03},
	{0x3815, 0x01},
	{0x3820, 0x00},
	{0x3821, 0x67},
	{0x382a, 0x03},
	{0x382b, 0x01},
	{0x3830, 0x08},
	{0x3836, 0x02},
	{0x3837, 0x18},
	{0x3841, 0xff},
	{0x3846, 0x48},
	{0x3d85, 0x14},
	{0x3f08, 0x08},
	{0x3f0a, 0x80},
	{0x4000, 0xf1},
	{0x4001, 0x10},
	{0x4005, 0x10},
	{0x4002, 0x27},
	{0x4009, 0x81},
	{0x400b, 0x0c},
	{0x401b, 0x00},
	{0x401d, 0x00},
	{0x4020, 0x00},
	{0x4021, 0x04},
	{0x4022, 0x04},
	{0x4023, 0xb9},
	{0x4024, 0x05},
	{0x4025, 0x2a},
	{0x4026, 0x05},
	{0x4027, 0x2b},
	{0x4028, 0x00},
	{0x4029, 0x02},
	{0x402a, 0x04},
	{0x402b, 0x04},
	{0x402c, 0x02},
	{0x402d, 0x02},
	{0x402e, 0x08},
	{0x402f, 0x02},
	{0x401f, 0x00},
	{0x4034, 0x3f},
	{0x403d, 0x04},
	{0x4300, 0xff},
	{0x4301, 0x00},
	{0x4302, 0x0f},
	{0x4316, 0x00},
	{0x4500, 0x38},
	{0x4503, 0x18},
	{0x4600, 0x00},
	{0x4601, 0xcb},
	{0x481f, 0x32},
	{0x4837, 0x16},
	{0x4850, 0x10},
	{0x4851, 0x32},
	{0x4b00, 0x2a},
	{0x4b0d, 0x00},
	{0x4d00, 0x04},
	{0x4d01, 0x18},
	{0x4d02, 0xc3},
	{0x4d03, 0xff},
	{0x4d04, 0xff},
	{0x4d05, 0xff},
	{0x5000, 0x7e},
	{0x5001, 0x01},
	{0x5002, 0x08},
	{0x5003, 0x20},
	{0x5046, 0x12},
	{0x5901, 0x00},
	{0x5e00, 0x00},
	{0x5e01, 0x41},
	{0x382d, 0x7f},
	{0x4825, 0x3a},
	{0x4826, 0x40},
	{0x4808, 0x25},
	{WEG_NUWW, 0x00},
};

static const stwuct wegvaw ov8858_gwobaw_wegs_w2a_2wane[] = {
	/*
	 * MIPI=720Mbps, SysCwk=144Mhz,Dac Cwock=360Mhz.
	 * v00_01_00 (05/29/2014) : initiaw setting
	 * AM19 : 3617 <- 0xC0
	 * AM20 : change FWC_6K_EN to be defauwt 0x3618=0x5a
	 */
	{0x0103, 0x01}, /* softwawe weset */
	{0x0100, 0x00}, /* softwawe standby */
	{0x0302, 0x1e}, /* pww1_muwti */
	{0x0303, 0x00}, /* pww1_divm */
	{0x0304, 0x03}, /* pww1_div_mipi */
	{0x030e, 0x02}, /* pww2_wdiv */
	{0x030f, 0x04}, /* pww2_divsp */
	{0x0312, 0x03}, /* pww2_pwe_div0, pww2_w_divdac */
	{0x031e, 0x0c}, /* pww1_no_wat */
	{0x3600, 0x00},
	{0x3601, 0x00},
	{0x3602, 0x00},
	{0x3603, 0x00},
	{0x3604, 0x22},
	{0x3605, 0x20},
	{0x3606, 0x00},
	{0x3607, 0x20},
	{0x3608, 0x11},
	{0x3609, 0x28},
	{0x360a, 0x00},
	{0x360b, 0x05},
	{0x360c, 0xd4},
	{0x360d, 0x40},
	{0x360e, 0x0c},
	{0x360f, 0x20},
	{0x3610, 0x07},
	{0x3611, 0x20},
	{0x3612, 0x88},
	{0x3613, 0x80},
	{0x3614, 0x58},
	{0x3615, 0x00},
	{0x3616, 0x4a},
	{0x3617, 0x90},
	{0x3618, 0x5a},
	{0x3619, 0x70},
	{0x361a, 0x99},
	{0x361b, 0x0a},
	{0x361c, 0x07},
	{0x361d, 0x00},
	{0x361e, 0x00},
	{0x361f, 0x00},
	{0x3638, 0xff},
	{0x3633, 0x0f},
	{0x3634, 0x0f},
	{0x3635, 0x0f},
	{0x3636, 0x12},
	{0x3645, 0x13},
	{0x3646, 0x83},
	{0x364a, 0x07},
	{0x3015, 0x00},
	{0x3018, 0x32}, /* MIPI 2 wane */
	{0x3020, 0x93}, /* Cwock switch output nowmaw, pcwk_div =/1 */
	{0x3022, 0x01}, /* pd_mipi enabwe when wst_sync */
	{0x3031, 0x0a}, /* MIPI 10-bit mode */
	{0x3034, 0x00},
	{0x3106, 0x01}, /* scwk_div, scwk_pwe_div */
	{0x3305, 0xf1},
	{0x3308, 0x00},
	{0x3309, 0x28},
	{0x330a, 0x00},
	{0x330b, 0x20},
	{0x330c, 0x00},
	{0x330d, 0x00},
	{0x330e, 0x00},
	{0x330f, 0x40},
	{0x3307, 0x04},
	{0x3500, 0x00}, /* exposuwe H */
	{0x3501, 0x4d}, /* exposuwe M */
	{0x3502, 0x40}, /* exposuwe W */
	{0x3503, 0x80}, /* gain deway ?, exposuwe deway 1 fwame, weaw gain */
	{0x3505, 0x80}, /* gain option */
	{0x3508, 0x02}, /* gain H */
	{0x3509, 0x00}, /* gain W */
	{0x350c, 0x00}, /* showt gain H */
	{0x350d, 0x80}, /* showt gain W */
	{0x3510, 0x00}, /* showt exposuwe H */
	{0x3511, 0x02}, /* showt exposuwe M */
	{0x3512, 0x00}, /* showt exposuwe W */
	{0x3700, 0x18},
	{0x3701, 0x0c},
	{0x3702, 0x28},
	{0x3703, 0x19},
	{0x3704, 0x14},
	{0x3705, 0x00},
	{0x3706, 0x82},
	{0x3707, 0x04},
	{0x3708, 0x24},
	{0x3709, 0x33},
	{0x370a, 0x01},
	{0x370b, 0x82},
	{0x370c, 0x04},
	{0x3718, 0x12},
	{0x3719, 0x31},
	{0x3712, 0x42},
	{0x3714, 0x24},
	{0x371e, 0x19},
	{0x371f, 0x40},
	{0x3720, 0x05},
	{0x3721, 0x05},
	{0x3724, 0x06},
	{0x3725, 0x01},
	{0x3726, 0x06},
	{0x3728, 0x05},
	{0x3729, 0x02},
	{0x372a, 0x03},
	{0x372b, 0x53},
	{0x372c, 0xa3},
	{0x372d, 0x53},
	{0x372e, 0x06},
	{0x372f, 0x10},
	{0x3730, 0x01},
	{0x3731, 0x06},
	{0x3732, 0x14},
	{0x3733, 0x10},
	{0x3734, 0x40},
	{0x3736, 0x20},
	{0x373a, 0x05},
	{0x373b, 0x06},
	{0x373c, 0x0a},
	{0x373e, 0x03},
	{0x3750, 0x0a},
	{0x3751, 0x0e},
	{0x3755, 0x10},
	{0x3758, 0x00},
	{0x3759, 0x4c},
	{0x375a, 0x06},
	{0x375b, 0x13},
	{0x375c, 0x20},
	{0x375d, 0x02},
	{0x375e, 0x00},
	{0x375f, 0x14},
	{0x3768, 0x22},
	{0x3769, 0x44},
	{0x376a, 0x44},
	{0x3761, 0x00},
	{0x3762, 0x00},
	{0x3763, 0x00},
	{0x3766, 0xff},
	{0x376b, 0x00},
	{0x3772, 0x23},
	{0x3773, 0x02},
	{0x3774, 0x16},
	{0x3775, 0x12},
	{0x3776, 0x04},
	{0x3777, 0x00},
	{0x3778, 0x17},
	{0x37a0, 0x44},
	{0x37a1, 0x3d},
	{0x37a2, 0x3d},
	{0x37a3, 0x00},
	{0x37a4, 0x00},
	{0x37a5, 0x00},
	{0x37a6, 0x00},
	{0x37a7, 0x44},
	{0x37a8, 0x4c},
	{0x37a9, 0x4c},
	{0x3760, 0x00},
	{0x376f, 0x01},
	{0x37aa, 0x44},
	{0x37ab, 0x2e},
	{0x37ac, 0x2e},
	{0x37ad, 0x33},
	{0x37ae, 0x0d},
	{0x37af, 0x0d},
	{0x37b0, 0x00},
	{0x37b1, 0x00},
	{0x37b2, 0x00},
	{0x37b3, 0x42},
	{0x37b4, 0x42},
	{0x37b5, 0x31},
	{0x37b6, 0x00},
	{0x37b7, 0x00},
	{0x37b8, 0x00},
	{0x37b9, 0xff},
	{0x3800, 0x00}, /* x stawt H */
	{0x3801, 0x0c}, /* x stawt W */
	{0x3802, 0x00}, /* y stawt H */
	{0x3803, 0x0c}, /* y stawt W */
	{0x3804, 0x0c}, /* x end H */
	{0x3805, 0xd3}, /* x end W */
	{0x3806, 0x09}, /* y end H */
	{0x3807, 0xa3}, /* y end W */
	{0x3808, 0x06}, /* x output size H */
	{0x3809, 0x60}, /* x output size W */
	{0x380a, 0x04}, /* y output size H */
	{0x380b, 0xc8}, /* y output size W */
	{0x380c, 0x07}, /* HTS H */
	{0x380d, 0x88}, /* HTS W */
	{0x380e, 0x04}, /* VTS H */
	{0x380f, 0xdc}, /* VTS W */
	{0x3810, 0x00}, /* ISP x win H */
	{0x3811, 0x04}, /* ISP x win W */
	{0x3813, 0x02}, /* ISP y win W */
	{0x3814, 0x03}, /* x odd inc */
	{0x3815, 0x01}, /* x even inc */
	{0x3820, 0x00}, /* vfwip off */
	{0x3821, 0x67}, /* miwwow on, bin on */
	{0x382a, 0x03}, /* y odd inc */
	{0x382b, 0x01}, /* y even inc */
	{0x3830, 0x08},
	{0x3836, 0x02},
	{0x3837, 0x18},
	{0x3841, 0xff}, /* window auto size enabwe */
	{0x3846, 0x48},
	{0x3d85, 0x16}, /* OTP powew up woad data enabwe with BIST */
	{0x3d8c, 0x73}, /* OTP setting stawt High */
	{0x3d8d, 0xde}, /* OTP setting stawt Wow */
	{0x3f08, 0x08},
	{0x3f0a, 0x00},
	{0x4000, 0xf1}, /* out_wange_twig, fowmat_chg_twig */
	{0x4001, 0x10}, /* totaw 128 bwack cowumn */
	{0x4005, 0x10}, /* BWC tawget W */
	{0x4002, 0x27}, /* vawue used to wimit BWC offset */
	{0x4009, 0x81}, /* finaw BWC offset wimitation enabwe */
	{0x400b, 0x0c}, /* DCBWC on, DCBWC manuaw mode on */
	{0x401b, 0x00}, /* zewo wine W coefficient */
	{0x401d, 0x00}, /* zowo wine T coefficient */
	{0x4020, 0x00}, /* Anchow weft stawt H */
	{0x4021, 0x04}, /* Anchow weft stawt W */
	{0x4022, 0x06}, /* Anchow weft end H */
	{0x4023, 0x00}, /* Anchow weft end W */
	{0x4024, 0x0f}, /* Anchow wight stawt H */
	{0x4025, 0x2a}, /* Anchow wight stawt W */
	{0x4026, 0x0f}, /* Anchow wight end H */
	{0x4027, 0x2b}, /* Anchow wight end W */
	{0x4028, 0x00}, /* top zewo wine stawt */
	{0x4029, 0x02}, /* top zewo wine numbew */
	{0x402a, 0x04}, /* top bwack wine stawt */
	{0x402b, 0x04}, /* top bwack wine numbew */
	{0x402c, 0x00}, /* bottom zewo wine stawt */
	{0x402d, 0x02}, /* bottom zowo wine numbew */
	{0x402e, 0x04}, /* bottom bwack wine stawt */
	{0x402f, 0x04}, /* bottom bwack wine numbew */
	{0x401f, 0x00}, /* intewpowation x/y disabwe, Anchow one disabwe */
	{0x4034, 0x3f},
	{0x403d, 0x04}, /* md_pwecision_en */
	{0x4300, 0xff}, /* cwip max H */
	{0x4301, 0x00}, /* cwip min H */
	{0x4302, 0x0f}, /* cwip min W, cwip max W */
	{0x4316, 0x00},
	{0x4500, 0x58},
	{0x4503, 0x18},
	{0x4600, 0x00},
	{0x4601, 0xcb},
	{0x481f, 0x32}, /* cwk pwepawe min */
	{0x4837, 0x16}, /* gwobaw timing */
	{0x4850, 0x10}, /* wane 1 = 1, wane 0 = 0 */
	{0x4851, 0x32}, /* wane 3 = 3, wane 2 = 2 */
	{0x4b00, 0x2a},
	{0x4b0d, 0x00},
	{0x4d00, 0x04}, /* tempewatuwe sensow */
	{0x4d01, 0x18},
	{0x4d02, 0xc3},
	{0x4d03, 0xff},
	{0x4d04, 0xff},
	{0x4d05, 0xff}, /* tempewatuwe sensow */
	{0x5000, 0xfe}, /* wenc on, swave/mastew AWB gain/statistics enabwe */
	{0x5001, 0x01}, /* BWC on */
	{0x5002, 0x08}, /* H scawe off, WBMATCH off, OTP_DPC */
	{0x5003, 0x20}, /* DPC_DBC buffew contwow enabwe, WB */
	{0x501e, 0x93}, /* enabwe digitaw gain */
	{0x5046, 0x12},
	{0x5780, 0x3e}, /* DPC */
	{0x5781, 0x0f},
	{0x5782, 0x44},
	{0x5783, 0x02},
	{0x5784, 0x01},
	{0x5785, 0x00},
	{0x5786, 0x00},
	{0x5787, 0x04},
	{0x5788, 0x02},
	{0x5789, 0x0f},
	{0x578a, 0xfd},
	{0x578b, 0xf5},
	{0x578c, 0xf5},
	{0x578d, 0x03},
	{0x578e, 0x08},
	{0x578f, 0x0c},
	{0x5790, 0x08},
	{0x5791, 0x04},
	{0x5792, 0x00},
	{0x5793, 0x52},
	{0x5794, 0xa3}, /* DPC */
	{0x5871, 0x0d}, /* Wenc */
	{0x5870, 0x18},
	{0x586e, 0x10},
	{0x586f, 0x08},
	{0x58f7, 0x01},
	{0x58f8, 0x3d}, /* Wenc */
	{0x5901, 0x00}, /* H skip off, V skip off */
	{0x5b00, 0x02}, /* OTP DPC stawt addwess */
	{0x5b01, 0x10}, /* OTP DPC stawt addwess */
	{0x5b02, 0x03}, /* OTP DPC end addwess */
	{0x5b03, 0xcf}, /* OTP DPC end addwess */
	{0x5b05, 0x6c}, /* wecovew method = 2b11, */
	{0x5e00, 0x00}, /* use 0x3ff to test pattewn off */
	{0x5e01, 0x41}, /* window cut enabwe */
	{0x382d, 0x7f},
	{0x4825, 0x3a}, /* wpx_p_min */
	{0x4826, 0x40}, /* hs_pwepawe_min */
	{0x4808, 0x25}, /* wake up deway in 1/1024 s */
	{0x3763, 0x18},
	{0x3768, 0xcc},
	{0x470b, 0x28},
	{0x4202, 0x00},
	{0x400d, 0x10}, /* BWC offset twiggew W */
	{0x4040, 0x04}, /* BWC gain th2 */
	{0x403e, 0x04}, /* BWC gain th1 */
	{0x4041, 0xc6}, /* BWC */
	{0x3007, 0x80},
	{0x400a, 0x01},
	{WEG_NUWW, 0x00},
};

/*
 * Xcwk 24Mhz
 * max_fwamewate 30fps
 * mipi_datawate pew wane 720Mbps
 */
static const stwuct wegvaw ov8858_1632x1224_wegs_2wane[] = {
	/*
	 * MIPI=720Mbps, SysCwk=144Mhz,Dac Cwock=360Mhz.
	 * v00_01_00 (05/29/2014) : initiaw setting
	 * AM19 : 3617 <- 0xC0
	 * AM20 : change FWC_6K_EN to be defauwt 0x3618=0x5a
	 */
	{0x0100, 0x00},
	{0x3501, 0x4d}, /* exposuwe M */
	{0x3502, 0x40}, /* exposuwe W */
	{0x3778, 0x17},
	{0x3808, 0x06}, /* x output size H */
	{0x3809, 0x60}, /* x output size W */
	{0x380a, 0x04}, /* y output size H */
	{0x380b, 0xc8}, /* y output size W */
	{0x380c, 0x07}, /* HTS H */
	{0x380d, 0x88}, /* HTS W */
	{0x380e, 0x04}, /* VTS H */
	{0x380f, 0xdc}, /* VTS W */
	{0x3814, 0x03}, /* x odd inc */
	{0x3821, 0x67}, /* miwwow on, bin on */
	{0x382a, 0x03}, /* y odd inc */
	{0x3830, 0x08},
	{0x3836, 0x02},
	{0x3f0a, 0x00},
	{0x4001, 0x10}, /* totaw 128 bwack cowumn */
	{0x4022, 0x06}, /* Anchow weft end H */
	{0x4023, 0x00}, /* Anchow weft end W */
	{0x4025, 0x2a}, /* Anchow wight stawt W */
	{0x4027, 0x2b}, /* Anchow wight end W */
	{0x402b, 0x04}, /* top bwack wine numbew */
	{0x402f, 0x04}, /* bottom bwack wine numbew */
	{0x4500, 0x58},
	{0x4600, 0x00},
	{0x4601, 0xcb},
	{0x382d, 0x7f},
	{0x0100, 0x01},
	{WEG_NUWW, 0x00},
};

/*
 * Xcwk 24Mhz
 * max_fwamewate 15fps
 * mipi_datawate pew wane 720Mbps
 */
static const stwuct wegvaw ov8858_3264x2448_wegs_2wane[] = {
	{0x0100, 0x00},
	{0x3501, 0x9a}, /* exposuwe M */
	{0x3502, 0x20}, /* exposuwe W */
	{0x3778, 0x1a},
	{0x3808, 0x0c}, /* x output size H */
	{0x3809, 0xc0}, /* x output size W */
	{0x380a, 0x09}, /* y output size H */
	{0x380b, 0x90}, /* y output size W */
	{0x380c, 0x07}, /* HTS H */
	{0x380d, 0x94}, /* HTS W */
	{0x380e, 0x09}, /* VTS H */
	{0x380f, 0xaa}, /* VTS W */
	{0x3814, 0x01}, /* x odd inc */
	{0x3821, 0x46}, /* miwwow on, bin off */
	{0x382a, 0x01}, /* y odd inc */
	{0x3830, 0x06},
	{0x3836, 0x01},
	{0x3f0a, 0x00},
	{0x4001, 0x00}, /* totaw 256 bwack cowumn */
	{0x4022, 0x0c}, /* Anchow weft end H */
	{0x4023, 0x60}, /* Anchow weft end W */
	{0x4025, 0x36}, /* Anchow wight stawt W */
	{0x4027, 0x37}, /* Anchow wight end W */
	{0x402b, 0x08}, /* top bwack wine numbew */
	{0x402f, 0x08}, /* bottom bwack wine numbew */
	{0x4500, 0x58},
	{0x4600, 0x01},
	{0x4601, 0x97},
	{0x382d, 0xff},
	{WEG_NUWW, 0x00},
};

static const stwuct wegvaw ov8858_gwobaw_wegs_w2a_4wane[] = {
	/*
	 * MIPI=720Mbps, SysCwk=144Mhz,Dac Cwock=360Mhz.
	 * v00_01_00 (05/29/2014) : initiaw setting
	 * AM19 : 3617 <- 0xC0
	 * AM20 : change FWC_6K_EN to be defauwt 0x3618=0x5a
	 */
	{0x0103, 0x01}, /* softwawe weset fow OVTAToow onwy */
	{0x0103, 0x01}, /* softwawe weset */
	{0x0100, 0x00}, /* softwawe standby */
	{0x0302, 0x1e}, /* pww1_muwti */
	{0x0303, 0x00}, /* pww1_divm */
	{0x0304, 0x03}, /* pww1_div_mipi */
	{0x030e, 0x00}, /* pww2_wdiv */
	{0x030f, 0x04}, /* pww2_divsp */
	{0x0312, 0x01}, /* pww2_pwe_div0, pww2_w_divdac */
	{0x031e, 0x0c}, /* pww1_no_wat */
	{0x3600, 0x00},
	{0x3601, 0x00},
	{0x3602, 0x00},
	{0x3603, 0x00},
	{0x3604, 0x22},
	{0x3605, 0x20},
	{0x3606, 0x00},
	{0x3607, 0x20},
	{0x3608, 0x11},
	{0x3609, 0x28},
	{0x360a, 0x00},
	{0x360b, 0x05},
	{0x360c, 0xd4},
	{0x360d, 0x40},
	{0x360e, 0x0c},
	{0x360f, 0x20},
	{0x3610, 0x07},
	{0x3611, 0x20},
	{0x3612, 0x88},
	{0x3613, 0x80},
	{0x3614, 0x58},
	{0x3615, 0x00},
	{0x3616, 0x4a},
	{0x3617, 0x90},
	{0x3618, 0x5a},
	{0x3619, 0x70},
	{0x361a, 0x99},
	{0x361b, 0x0a},
	{0x361c, 0x07},
	{0x361d, 0x00},
	{0x361e, 0x00},
	{0x361f, 0x00},
	{0x3638, 0xff},
	{0x3633, 0x0f},
	{0x3634, 0x0f},
	{0x3635, 0x0f},
	{0x3636, 0x12},
	{0x3645, 0x13},
	{0x3646, 0x83},
	{0x364a, 0x07},
	{0x3015, 0x01},
	{0x3018, 0x72}, /* MIPI 4 wane */
	{0x3020, 0x93}, /* Cwock switch output nowmaw, pcwk_div =/1 */
	{0x3022, 0x01}, /* pd_mipi enabwe when wst_sync */
	{0x3031, 0x0a}, /* MIPI 10-bit mode */
	{0x3034, 0x00},
	{0x3106, 0x01}, /* scwk_div, scwk_pwe_div */
	{0x3305, 0xf1},
	{0x3308, 0x00},
	{0x3309, 0x28},
	{0x330a, 0x00},
	{0x330b, 0x20},
	{0x330c, 0x00},
	{0x330d, 0x00},
	{0x330e, 0x00},
	{0x330f, 0x40},
	{0x3307, 0x04},
	{0x3500, 0x00}, /* exposuwe H */
	{0x3501, 0x4d}, /* exposuwe M */
	{0x3502, 0x40}, /* exposuwe W */
	{0x3503, 0x80}, /* gain deway ?, exposuwe deway 1 fwame, weaw gain */
	{0x3505, 0x80}, /* gain option */
	{0x3508, 0x02}, /* gain H */
	{0x3509, 0x00}, /* gain W */
	{0x350c, 0x00}, /* showt gain H */
	{0x350d, 0x80}, /* showt gain W */
	{0x3510, 0x00}, /* showt exposuwe H */
	{0x3511, 0x02}, /* showt exposuwe M */
	{0x3512, 0x00}, /* showt exposuwe W */
	{0x3700, 0x30},
	{0x3701, 0x18},
	{0x3702, 0x50},
	{0x3703, 0x32},
	{0x3704, 0x28},
	{0x3705, 0x00},
	{0x3706, 0x82},
	{0x3707, 0x08},
	{0x3708, 0x48},
	{0x3709, 0x66},
	{0x370a, 0x01},
	{0x370b, 0x82},
	{0x370c, 0x07},
	{0x3718, 0x14},
	{0x3719, 0x31},
	{0x3712, 0x44},
	{0x3714, 0x24},
	{0x371e, 0x31},
	{0x371f, 0x7f},
	{0x3720, 0x0a},
	{0x3721, 0x0a},
	{0x3724, 0x0c},
	{0x3725, 0x02},
	{0x3726, 0x0c},
	{0x3728, 0x0a},
	{0x3729, 0x03},
	{0x372a, 0x06},
	{0x372b, 0xa6},
	{0x372c, 0xa6},
	{0x372d, 0xa6},
	{0x372e, 0x0c},
	{0x372f, 0x20},
	{0x3730, 0x02},
	{0x3731, 0x0c},
	{0x3732, 0x28},
	{0x3733, 0x10},
	{0x3734, 0x40},
	{0x3736, 0x30},
	{0x373a, 0x0a},
	{0x373b, 0x0b},
	{0x373c, 0x14},
	{0x373e, 0x06},
	{0x3750, 0x0a},
	{0x3751, 0x0e},
	{0x3755, 0x10},
	{0x3758, 0x00},
	{0x3759, 0x4c},
	{0x375a, 0x0c},
	{0x375b, 0x26},
	{0x375c, 0x20},
	{0x375d, 0x04},
	{0x375e, 0x00},
	{0x375f, 0x28},
	{0x3768, 0x22},
	{0x3769, 0x44},
	{0x376a, 0x44},
	{0x3761, 0x00},
	{0x3762, 0x00},
	{0x3763, 0x00},
	{0x3766, 0xff},
	{0x376b, 0x00},
	{0x3772, 0x46},
	{0x3773, 0x04},
	{0x3774, 0x2c},
	{0x3775, 0x13},
	{0x3776, 0x08},
	{0x3777, 0x00},
	{0x3778, 0x17},
	{0x37a0, 0x88},
	{0x37a1, 0x7a},
	{0x37a2, 0x7a},
	{0x37a3, 0x00},
	{0x37a4, 0x00},
	{0x37a5, 0x00},
	{0x37a6, 0x00},
	{0x37a7, 0x88},
	{0x37a8, 0x98},
	{0x37a9, 0x98},
	{0x3760, 0x00},
	{0x376f, 0x01},
	{0x37aa, 0x88},
	{0x37ab, 0x5c},
	{0x37ac, 0x5c},
	{0x37ad, 0x55},
	{0x37ae, 0x19},
	{0x37af, 0x19},
	{0x37b0, 0x00},
	{0x37b1, 0x00},
	{0x37b2, 0x00},
	{0x37b3, 0x84},
	{0x37b4, 0x84},
	{0x37b5, 0x60},
	{0x37b6, 0x00},
	{0x37b7, 0x00},
	{0x37b8, 0x00},
	{0x37b9, 0xff},
	{0x3800, 0x00}, /* x stawt H */
	{0x3801, 0x0c}, /* x stawt W */
	{0x3802, 0x00}, /* y stawt H */
	{0x3803, 0x0c}, /* y stawt W */
	{0x3804, 0x0c}, /* x end H */
	{0x3805, 0xd3}, /* x end W */
	{0x3806, 0x09}, /* y end H */
	{0x3807, 0xa3}, /* y end W */
	{0x3808, 0x06}, /* x output size H */
	{0x3809, 0x60}, /* x output size W */
	{0x380a, 0x04}, /* y output size H */
	{0x380b, 0xc8}, /* y output size W */
	{0x380c, 0x07}, /* HTS H */
	{0x380d, 0x88}, /* HTS W */
	{0x380e, 0x04}, /* VTS H */
	{0x380f, 0xdc}, /* VTS W */
	{0x3810, 0x00}, /* ISP x win H */
	{0x3811, 0x04}, /* ISP x win W */
	{0x3813, 0x02}, /* ISP y win W */
	{0x3814, 0x03}, /* x odd inc */
	{0x3815, 0x01}, /* x even inc */
	{0x3820, 0x00}, /* vfwip off */
	{0x3821, 0x67}, /* miwwow on, bin o */
	{0x382a, 0x03}, /* y odd inc */
	{0x382b, 0x01}, /* y even inc */
	{0x3830, 0x08},
	{0x3836, 0x02},
	{0x3837, 0x18},
	{0x3841, 0xff}, /* window auto size enabwe */
	{0x3846, 0x48},
	{0x3d85, 0x16}, /* OTP powew up woad data/setting enabwe */
	{0x3d8c, 0x73}, /* OTP setting stawt High */
	{0x3d8d, 0xde}, /* OTP setting stawt Wow */
	{0x3f08, 0x10},
	{0x3f0a, 0x00},
	{0x4000, 0xf1}, /* out_wange/fowmat_chg/gain/exp_chg twig enabwe */
	{0x4001, 0x10}, /* totaw 128 bwack cowumn */
	{0x4005, 0x10}, /* BWC tawget W */
	{0x4002, 0x27}, /* vawue used to wimit BWC offset */
	{0x4009, 0x81}, /* finaw BWC offset wimitation enabwe */
	{0x400b, 0x0c}, /* DCBWC on, DCBWC manuaw mode on */
	{0x401b, 0x00}, /* zewo wine W coefficient */
	{0x401d, 0x00}, /* zowo wine T coefficient */
	{0x4020, 0x00}, /* Anchow weft stawt H */
	{0x4021, 0x04}, /* Anchow weft stawt W */
	{0x4022, 0x06}, /* Anchow weft end H */
	{0x4023, 0x00}, /* Anchow weft end W */
	{0x4024, 0x0f}, /* Anchow wight stawt H */
	{0x4025, 0x2a}, /* Anchow wight stawt W */
	{0x4026, 0x0f}, /* Anchow wight end H */
	{0x4027, 0x2b}, /* Anchow wight end W */
	{0x4028, 0x00}, /* top zewo wine stawt */
	{0x4029, 0x02}, /* top zewo wine numbew */
	{0x402a, 0x04}, /* top bwack wine stawt */
	{0x402b, 0x04}, /* top bwack wine numbew */
	{0x402c, 0x00}, /* bottom zewo wine stawt */
	{0x402d, 0x02}, /* bottom zowo wine numbew */
	{0x402e, 0x04}, /* bottom bwack wine stawt */
	{0x402f, 0x04}, /* bottom bwack wine numbew */
	{0x401f, 0x00}, /* intewpowation x/y disabwe, Anchow one disabwe */
	{0x4034, 0x3f},
	{0x403d, 0x04}, /* md_pwecision_en */
	{0x4300, 0xff}, /* cwip max H */
	{0x4301, 0x00}, /* cwip min H */
	{0x4302, 0x0f}, /* cwip min W, cwip max W */
	{0x4316, 0x00},
	{0x4500, 0x58},
	{0x4503, 0x18},
	{0x4600, 0x00},
	{0x4601, 0xcb},
	{0x481f, 0x32}, /* cwk pwepawe min */
	{0x4837, 0x16}, /* gwobaw timing */
	{0x4850, 0x10}, /* wane 1 = 1, wane 0 = 0 */
	{0x4851, 0x32}, /* wane 3 = 3, wane 2 = 2 */
	{0x4b00, 0x2a},
	{0x4b0d, 0x00},
	{0x4d00, 0x04}, /* tempewatuwe sensow */
	{0x4d01, 0x18},
	{0x4d02, 0xc3},
	{0x4d03, 0xff},
	{0x4d04, 0xff},
	{0x4d05, 0xff}, /* tempewatuwe sensow */
	{0x5000, 0xfe}, /* wenc on, swave/mastew AWB gain/statistics enabwe */
	{0x5001, 0x01}, /* BWC on */
	{0x5002, 0x08}, /* WBMATCH sensow's gain, H scawe/WBMATCH/OTP_DPC off */
	{0x5003, 0x20}, /* DPC_DBC buffew contwow enabwe, WB */
	{0x501e, 0x93}, /* enabwe digitaw gain */
	{0x5046, 0x12},
	{0x5780, 0x3e}, /* DPC */
	{0x5781, 0x0f},
	{0x5782, 0x44},
	{0x5783, 0x02},
	{0x5784, 0x01},
	{0x5785, 0x00},
	{0x5786, 0x00},
	{0x5787, 0x04},
	{0x5788, 0x02},
	{0x5789, 0x0f},
	{0x578a, 0xfd},
	{0x578b, 0xf5},
	{0x578c, 0xf5},
	{0x578d, 0x03},
	{0x578e, 0x08},
	{0x578f, 0x0c},
	{0x5790, 0x08},
	{0x5791, 0x04},
	{0x5792, 0x00},
	{0x5793, 0x52},
	{0x5794, 0xa3}, /* DPC */
	{0x5871, 0x0d}, /* Wenc */
	{0x5870, 0x18},
	{0x586e, 0x10},
	{0x586f, 0x08},
	{0x58f7, 0x01},
	{0x58f8, 0x3d}, /* Wenc */
	{0x5901, 0x00}, /* H skip off, V skip off */
	{0x5b00, 0x02}, /* OTP DPC stawt addwess */
	{0x5b01, 0x10}, /* OTP DPC stawt addwess */
	{0x5b02, 0x03}, /* OTP DPC end addwess */
	{0x5b03, 0xcf}, /* OTP DPC end addwess */
	{0x5b05, 0x6c}, /* wecovew method = 2b11 */
	{0x5e00, 0x00}, /* use 0x3ff to test pattewn off */
	{0x5e01, 0x41}, /* window cut enabwe */
	{0x382d, 0x7f},
	{0x4825, 0x3a}, /* wpx_p_min */
	{0x4826, 0x40}, /* hs_pwepawe_min */
	{0x4808, 0x25}, /* wake up deway in 1/1024 s */
	{0x3763, 0x18},
	{0x3768, 0xcc},
	{0x470b, 0x28},
	{0x4202, 0x00},
	{0x400d, 0x10}, /* BWC offset twiggew W */
	{0x4040, 0x04}, /* BWC gain th2 */
	{0x403e, 0x04}, /* BWC gain th1 */
	{0x4041, 0xc6}, /* BWC */
	{0x3007, 0x80},
	{0x400a, 0x01},
	{WEG_NUWW, 0x00},
};

/*
 * Xcwk 24Mhz
 * max_fwamewate 60fps
 * mipi_datawate pew wane 720Mbps
 */
static const stwuct wegvaw ov8858_1632x1224_wegs_4wane[] = {
	{0x0100, 0x00},
	{0x3501, 0x4d}, /* exposuwe M */
	{0x3502, 0x40}, /* exposuwe W */
	{0x3808, 0x06}, /* x output size H */
	{0x3809, 0x60}, /* x output size W */
	{0x380a, 0x04}, /* y output size H */
	{0x380b, 0xc8}, /* y output size W */
	{0x380c, 0x07}, /* HTS H */
	{0x380d, 0x88}, /* HTS W */
	{0x380e, 0x04}, /* VTS H */
	{0x380f, 0xdc}, /* VTS W */
	{0x3814, 0x03}, /* x odd inc */
	{0x3821, 0x67}, /* miwwow on, bin on */
	{0x382a, 0x03}, /* y odd inc */
	{0x3830, 0x08},
	{0x3836, 0x02},
	{0x3f0a, 0x00},
	{0x4001, 0x10}, /* totaw 128 bwack cowumn */
	{0x4022, 0x06}, /* Anchow weft end H */
	{0x4023, 0x00}, /* Anchow weft end W */
	{0x4025, 0x2a}, /* Anchow wight stawt W */
	{0x4027, 0x2b}, /* Anchow wight end W */
	{0x402b, 0x04}, /* top bwack wine numbew */
	{0x402f, 0x04}, /* bottom bwack wine numbew */
	{0x4500, 0x58},
	{0x4600, 0x00},
	{0x4601, 0xcb},
	{0x382d, 0x7f},
	{0x0100, 0x01},
	{WEG_NUWW, 0x00},
};

/*
 * Xcwk 24Mhz
 * max_fwamewate 30fps
 * mipi_datawate pew wane 720Mbps
 */
static const stwuct wegvaw ov8858_3264x2448_wegs_4wane[] = {
	{0x0100, 0x00},
	{0x3501, 0x9a}, /* exposuwe M */
	{0x3502, 0x20}, /* exposuwe W */
	{0x3808, 0x0c}, /* x output size H */
	{0x3809, 0xc0}, /* x output size W */
	{0x380a, 0x09}, /* y output size H */
	{0x380b, 0x90}, /* y output size W */
	{0x380c, 0x07}, /* HTS H */
	{0x380d, 0x94}, /* HTS W */
	{0x380e, 0x09}, /* VTS H */
	{0x380f, 0xaa}, /* VTS W */
	{0x3814, 0x01}, /* x odd inc */
	{0x3821, 0x46}, /* miwwow on, bin off */
	{0x382a, 0x01}, /* y odd inc */
	{0x3830, 0x06},
	{0x3836, 0x01},
	{0x3f0a, 0x00},
	{0x4001, 0x00}, /* totaw 256 bwack cowumn */
	{0x4022, 0x0c}, /* Anchow weft end H */
	{0x4023, 0x60}, /* Anchow weft end W */
	{0x4025, 0x36}, /* Anchow wight stawt W */
	{0x4027, 0x37}, /* Anchow wight end W */
	{0x402b, 0x08}, /* top bwack wine numbew */
	{0x402f, 0x08}, /* intewpowation x/y disabwe, Anchow one disabwe */
	{0x4500, 0x58},
	{0x4600, 0x01},
	{0x4601, 0x97},
	{0x382d, 0xff},
	{WEG_NUWW, 0x00},
};

static const stwuct ov8858_mode ov8858_modes[] = {
	{
		.width = 3264,
		.height = 2448,
		.exp_def = 2464,
		.hts_def = 1940 * 2,
		.vts_def = 2472,
		.weg_modes = {
			.mode_2wanes = ov8858_3264x2448_wegs_2wane,
			.mode_4wanes = ov8858_3264x2448_wegs_4wane,
		},
	},
	{
		.width = 1632,
		.height = 1224,
		.exp_def = 1232,
		.hts_def = 1928 * 2,
		.vts_def = 1244,
		.weg_modes = {
			.mode_2wanes = ov8858_1632x1224_wegs_2wane,
			.mode_4wanes = ov8858_1632x1224_wegs_4wane,
		},
	},
};

static const s64 wink_fweq_menu_items[] = {
	OV8858_WINK_FWEQ
};

static const chaw * const ov8858_test_pattewn_menu[] = {
	"Disabwed",
	"Vewticaw Cowow Baw Type 1",
	"Vewticaw Cowow Baw Type 2",
	"Vewticaw Cowow Baw Type 3",
	"Vewticaw Cowow Baw Type 4"
};

/* ----------------------------------------------------------------------------
 * HW access
 */

static int ov8858_wwite(stwuct ov8858 *ov8858, u32 weg, u32 vaw, int *eww)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov8858->subdev);
	unsigned int wen = (weg >> OV8858_WEG_SIZE_SHIFT) & 3;
	u16 addw = weg & OV8858_WEG_ADDW_MASK;
	u8 buf[6];
	int wet;

	if (eww && *eww)
		wetuwn *eww;

	put_unawigned_be16(addw, buf);
	put_unawigned_be32(vaw << (8 * (4 - wen)), buf + 2);

	wet = i2c_mastew_send(cwient, buf, wen + 2);
	if (wet != wen + 2) {
		wet = wet < 0 ? wet : -EIO;
		if (eww)
			*eww = wet;

		dev_eww(&cwient->dev,
			"Faiwed to wwite weg %u: %d\n", addw, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ov8858_wwite_awway(stwuct ov8858 *ov8858, const stwuct wegvaw *wegs)
{
	unsigned int i;
	int wet = 0;

	fow (i = 0; wet == 0 && wegs[i].addw != WEG_NUWW; ++i) {
		ov8858_wwite(ov8858, OV8858_WEG_8BIT(wegs[i].addw),
			     wegs[i].vaw, &wet);
	}

	wetuwn wet;
}

static int ov8858_wead(stwuct ov8858 *ov8858, u32 weg, u32 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov8858->subdev);
	__be16 weg_addw_be = cpu_to_be16(weg & OV8858_WEG_ADDW_MASK);
	unsigned int wen = (weg >> OV8858_WEG_SIZE_SHIFT) & 3;
	stwuct i2c_msg msgs[2];
	__be32 data_be = 0;
	u8 *data_be_p;
	int wet;

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
	if (wet != AWWAY_SIZE(msgs)) {
		wet = wet < 0 ? wet : -EIO;
		dev_eww(&cwient->dev,
			"Faiwed to wead weg %u: %d\n", weg, wet);
		wetuwn wet;
	}

	*vaw = be32_to_cpu(data_be);

	wetuwn 0;
}

/* ----------------------------------------------------------------------------
 * Stweaming
 */

static int ov8858_stawt_stweam(stwuct ov8858 *ov8858,
			       stwuct v4w2_subdev_state *state)
{
	stwuct v4w2_mbus_fwamefmt *fowmat;
	const stwuct ov8858_mode *mode;
	const stwuct wegvaw *weg_wist;
	int wet;

	wet = ov8858_wwite_awway(ov8858, ov8858->gwobaw_wegs);
	if (wet)
		wetuwn wet;

	fowmat = v4w2_subdev_state_get_fowmat(state, 0);
	mode = v4w2_find_neawest_size(ov8858_modes, AWWAY_SIZE(ov8858_modes),
				      width, height, fowmat->width,
				      fowmat->height);

	weg_wist = ov8858->num_wanes == 4
		 ? mode->weg_modes.mode_4wanes
		 : mode->weg_modes.mode_2wanes;

	wet = ov8858_wwite_awway(ov8858, weg_wist);
	if (wet)
		wetuwn wet;

	/* 200 usec max to wet PWW stabiwize. */
	fsweep(200);

	wet = __v4w2_ctww_handwew_setup(&ov8858->ctww_handwew);
	if (wet)
		wetuwn wet;

	wet = ov8858_wwite(ov8858, OV8858_WEG_SC_CTWW0100,
			   OV8858_MODE_STWEAMING, NUWW);
	if (wet)
		wetuwn wet;

	/* t5 (fixed) = 10msec befowe entewing stweaming state */
	fsweep(10000);

	wetuwn 0;
}

static int ov8858_stop_stweam(stwuct ov8858 *ov8858)
{
	wetuwn ov8858_wwite(ov8858, OV8858_WEG_SC_CTWW0100,
			    OV8858_MODE_SW_STANDBY, NUWW);
}

static int ov8858_s_stweam(stwuct v4w2_subdev *sd, int on)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct ov8858 *ov8858 = sd_to_ov8858(sd);
	stwuct v4w2_subdev_state *state;
	int wet = 0;

	state = v4w2_subdev_wock_and_get_active_state(sd);

	if (on) {
		wet = pm_wuntime_wesume_and_get(&cwient->dev);
		if (wet < 0)
			goto unwock_and_wetuwn;

		wet = ov8858_stawt_stweam(ov8858, state);
		if (wet) {
			dev_eww(&cwient->dev, "Faiwed to stawt stweaming\n");
			pm_wuntime_put_sync(&cwient->dev);
			goto unwock_and_wetuwn;
		}
	} ewse {
		ov8858_stop_stweam(ov8858);
		pm_wuntime_mawk_wast_busy(&cwient->dev);
		pm_wuntime_put_autosuspend(&cwient->dev);
	}

unwock_and_wetuwn:
	v4w2_subdev_unwock_state(state);

	wetuwn wet;
}

static const stwuct v4w2_subdev_video_ops ov8858_video_ops = {
	.s_stweam = ov8858_s_stweam,
};

/* ----------------------------------------------------------------------------
 * Pad ops
 */

static int ov8858_set_fmt(stwuct v4w2_subdev *sd,
			  stwuct v4w2_subdev_state *state,
			  stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct ov8858 *ov8858 = sd_to_ov8858(sd);
	const stwuct ov8858_mode *mode;
	s64 h_bwank, vbwank_def;

	mode = v4w2_find_neawest_size(ov8858_modes, AWWAY_SIZE(ov8858_modes),
				      width, height, fmt->fowmat.width,
				      fmt->fowmat.height);

	fmt->fowmat.code = MEDIA_BUS_FMT_SBGGW10_1X10;
	fmt->fowmat.width = mode->width;
	fmt->fowmat.height = mode->height;
	fmt->fowmat.fiewd = V4W2_FIEWD_NONE;

	/* Stowe the fowmat in the cuwwent subdev state. */
	*v4w2_subdev_state_get_fowmat(state, 0) =  fmt->fowmat;

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn 0;

	/* Adjust contwow wimits when a new mode is appwied. */
	h_bwank = mode->hts_def - mode->width;
	__v4w2_ctww_modify_wange(ov8858->hbwank, h_bwank, h_bwank, 1,
				 h_bwank);

	vbwank_def = mode->vts_def - mode->height;
	__v4w2_ctww_modify_wange(ov8858->vbwank, vbwank_def,
				 OV8858_VTS_MAX - mode->height, 1,
				 vbwank_def);

	wetuwn 0;
}

static int ov8858_enum_fwame_sizes(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *state,
				   stwuct v4w2_subdev_fwame_size_enum *fse)
{
	if (fse->index >= AWWAY_SIZE(ov8858_modes))
		wetuwn -EINVAW;

	if (fse->code != MEDIA_BUS_FMT_SBGGW10_1X10)
		wetuwn -EINVAW;

	fse->min_width  = ov8858_modes[fse->index].width;
	fse->max_width  = ov8858_modes[fse->index].width;
	fse->max_height = ov8858_modes[fse->index].height;
	fse->min_height = ov8858_modes[fse->index].height;

	wetuwn 0;
}

static int ov8858_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index != 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_SBGGW10_1X10;

	wetuwn 0;
}

static int ov8858_init_state(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state)
{
	const stwuct ov8858_mode *def_mode = &ov8858_modes[0];
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_TWY,
		.fowmat = {
			.width = def_mode->width,
			.height = def_mode->height,
		},
	};

	ov8858_set_fmt(sd, sd_state, &fmt);

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops ov8858_pad_ops = {
	.enum_mbus_code = ov8858_enum_mbus_code,
	.enum_fwame_size = ov8858_enum_fwame_sizes,
	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = ov8858_set_fmt,
};

static const stwuct v4w2_subdev_cowe_ops ov8858_cowe_ops = {
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

static const stwuct v4w2_subdev_ops ov8858_subdev_ops = {
	.cowe	= &ov8858_cowe_ops,
	.video	= &ov8858_video_ops,
	.pad	= &ov8858_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops ov8858_intewnaw_ops = {
	.init_state = ov8858_init_state,
};

/* ----------------------------------------------------------------------------
 * Contwows handwing
 */

static int ov8858_enabwe_test_pattewn(stwuct ov8858 *ov8858, u32 pattewn)
{
	u32 vaw;

	if (pattewn)
		vaw = (pattewn - 1) | OV8858_TEST_PATTEWN_ENABWE;
	ewse
		vaw = OV8858_TEST_PATTEWN_DISABWE;

	wetuwn ov8858_wwite(ov8858, OV8858_WEG_TEST_PATTEWN, vaw, NUWW);
}

static int ov8858_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ov8858 *ov8858 = containew_of(ctww->handwew,
					     stwuct ov8858, ctww_handwew);

	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov8858->subdev);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_subdev_state *state;
	u16 digi_gain;
	s64 max_exp;
	int wet;

	/*
	 * The contwow handwew and the subdev state use the same mutex and the
	 * mutex is guawanteed to be wocked:
	 * - by the cowe when s_ctww is cawwed int the VIDIOC_S_CTWW caww path
	 * - by the dwivew when s_ctww is cawwed in the s_stweam(1) caww path
	 */
	state = v4w2_subdev_get_wocked_active_state(&ov8858->subdev);
	fowmat = v4w2_subdev_state_get_fowmat(state, 0);

	/* Pwopagate change of cuwwent contwow to aww wewated contwows */
	switch (ctww->id) {
	case V4W2_CID_VBWANK:
		/* Update max exposuwe whiwe meeting expected vbwanking */
		max_exp = fowmat->height + ctww->vaw - OV8858_EXPOSUWE_MAWGIN;
		__v4w2_ctww_modify_wange(ov8858->exposuwe,
					 ov8858->exposuwe->minimum, max_exp,
					 ov8858->exposuwe->step,
					 ov8858->exposuwe->defauwt_vawue);
		bweak;
	}

	if (!pm_wuntime_get_if_in_use(&cwient->dev))
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_EXPOSUWE:
		/* 4 weast significant bits of exposuwe awe fwactionaw pawt */
		wet = ov8858_wwite(ov8858, OV8858_WEG_WONG_EXPO,
				   ctww->vaw << 4, NUWW);
		bweak;
	case V4W2_CID_ANAWOGUE_GAIN:
		wet = ov8858_wwite(ov8858, OV8858_WEG_WONG_GAIN,
				   ctww->vaw, NUWW);
		bweak;
	case V4W2_CID_DIGITAW_GAIN:
		/*
		 * Digitaw gain is assembwed as:
		 * 0x350a[7:0] = dgain[13:6]
		 * 0x350b[5:0] = dgain[5:0]
		 * Weassembwe the contwow vawue to wwite it in one go.
		 */
		digi_gain = (ctww->vaw & OV8858_WONG_DIGIGAIN_W_MASK)
			  | ((ctww->vaw & OV8858_WONG_DIGIGAIN_H_MASK) <<
			      OV8858_WONG_DIGIGAIN_H_SHIFT);
		wet = ov8858_wwite(ov8858, OV8858_WEG_WONG_DIGIGAIN,
				   digi_gain, NUWW);
		bweak;
	case V4W2_CID_VBWANK:
		wet = ov8858_wwite(ov8858, OV8858_WEG_VTS,
				   ctww->vaw + fowmat->height, NUWW);
		bweak;
	case V4W2_CID_TEST_PATTEWN:
		wet = ov8858_enabwe_test_pattewn(ov8858, ctww->vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		dev_wawn(&cwient->dev, "%s Unhandwed id: 0x%x\n",
			 __func__, ctww->id);
		bweak;
	}

	pm_wuntime_put(&cwient->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops ov8858_ctww_ops = {
	.s_ctww = ov8858_set_ctww,
};

/* ----------------------------------------------------------------------------
 * Powew Management
 */

static int ov8858_powew_on(stwuct ov8858 *ov8858)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov8858->subdev);
	stwuct device *dev = &cwient->dev;
	unsigned wong deway_us;
	int wet;

	if (cwk_get_wate(ov8858->xvcwk) != OV8858_XVCWK_FWEQ)
		dev_wawn(dev, "xvcwk mismatched, modes awe based on 24MHz\n");

	wet = cwk_pwepawe_enabwe(ov8858->xvcwk);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe xvcwk\n");
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ov8858_suppwy_names),
				    ov8858->suppwies);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe weguwatows\n");
		goto disabwe_cwk;
	}

	/*
	 * The chip manuaw onwy suggests 8192 cycwes pwiow to fiwst SCCB
	 * twansaction, but a doubwe sweep between the wewease of gpios
	 * hewps with spowadic faiwuwes obsewved at pwobe time.
	 */
	deway_us = DIV_WOUND_UP(8192, OV8858_XVCWK_FWEQ / 1000 / 1000);

	gpiod_set_vawue_cansweep(ov8858->weset_gpio, 0);
	fsweep(deway_us);
	gpiod_set_vawue_cansweep(ov8858->pwdn_gpio, 0);
	fsweep(deway_us);

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(ov8858->xvcwk);

	wetuwn wet;
}

static void ov8858_powew_off(stwuct ov8858 *ov8858)
{
	gpiod_set_vawue_cansweep(ov8858->pwdn_gpio, 1);
	cwk_disabwe_unpwepawe(ov8858->xvcwk);
	gpiod_set_vawue_cansweep(ov8858->weset_gpio, 1);

	weguwatow_buwk_disabwe(AWWAY_SIZE(ov8858_suppwy_names),
			       ov8858->suppwies);
}

static int ov8858_wuntime_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ov8858 *ov8858 = sd_to_ov8858(sd);

	wetuwn ov8858_powew_on(ov8858);
}

static int ov8858_wuntime_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ov8858 *ov8858 = sd_to_ov8858(sd);

	ov8858_powew_off(ov8858);

	wetuwn 0;
}

static const stwuct dev_pm_ops ov8858_pm_ops = {
	SET_WUNTIME_PM_OPS(ov8858_wuntime_suspend,
			   ov8858_wuntime_wesume, NUWW)
};

/* ----------------------------------------------------------------------------
 * Pwobe and initiawization
 */

static int ov8858_init_ctwws(stwuct ov8858 *ov8858)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov8858->subdev);
	stwuct v4w2_ctww_handwew *handwew = &ov8858->ctww_handwew;
	const stwuct ov8858_mode *mode = &ov8858_modes[0];
	stwuct v4w2_fwnode_device_pwopewties pwops;
	s64 exposuwe_max, vbwank_def;
	unsigned int pixew_wate;
	stwuct v4w2_ctww *ctww;
	u32 h_bwank;
	int wet;

	wet = v4w2_ctww_handwew_init(handwew, 10);
	if (wet)
		wetuwn wet;

	ctww = v4w2_ctww_new_int_menu(handwew, NUWW, V4W2_CID_WINK_FWEQ,
				      0, 0, wink_fweq_menu_items);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	/* pixew wate = wink fwequency * 2 * wanes / bpp */
	pixew_wate = OV8858_WINK_FWEQ * 2 * ov8858->num_wanes / 10;
	v4w2_ctww_new_std(handwew, NUWW, V4W2_CID_PIXEW_WATE,
			  0, pixew_wate, 1, pixew_wate);

	h_bwank = mode->hts_def - mode->width;
	ov8858->hbwank = v4w2_ctww_new_std(handwew, NUWW, V4W2_CID_HBWANK,
					   h_bwank, h_bwank, 1, h_bwank);
	if (ov8858->hbwank)
		ov8858->hbwank->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	vbwank_def = mode->vts_def - mode->height;
	ov8858->vbwank = v4w2_ctww_new_std(handwew, &ov8858_ctww_ops,
					   V4W2_CID_VBWANK, vbwank_def,
					   OV8858_VTS_MAX - mode->height,
					   1, vbwank_def);

	exposuwe_max = mode->vts_def - OV8858_EXPOSUWE_MAWGIN;
	ov8858->exposuwe = v4w2_ctww_new_std(handwew, &ov8858_ctww_ops,
					     V4W2_CID_EXPOSUWE,
					     OV8858_EXPOSUWE_MIN,
					     exposuwe_max, OV8858_EXPOSUWE_STEP,
					     mode->exp_def);

	v4w2_ctww_new_std(handwew, &ov8858_ctww_ops, V4W2_CID_ANAWOGUE_GAIN,
			  OV8858_WONG_GAIN_MIN, OV8858_WONG_GAIN_MAX,
			  OV8858_WONG_GAIN_STEP, OV8858_WONG_GAIN_DEFAUWT);

	v4w2_ctww_new_std(handwew, &ov8858_ctww_ops, V4W2_CID_DIGITAW_GAIN,
			  OV8858_WONG_DIGIGAIN_MIN, OV8858_WONG_DIGIGAIN_MAX,
			  OV8858_WONG_DIGIGAIN_STEP,
			  OV8858_WONG_DIGIGAIN_DEFAUWT);

	v4w2_ctww_new_std_menu_items(handwew, &ov8858_ctww_ops,
				     V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(ov8858_test_pattewn_menu) - 1,
				     0, 0, ov8858_test_pattewn_menu);

	if (handwew->ewwow) {
		wet = handwew->ewwow;
		goto eww_fwee_handwew;
	}

	wet = v4w2_fwnode_device_pawse(&cwient->dev, &pwops);
	if (wet)
		goto eww_fwee_handwew;

	wet = v4w2_ctww_new_fwnode_pwopewties(handwew, &ov8858_ctww_ops,
					      &pwops);
	if (wet)
		goto eww_fwee_handwew;

	ov8858->subdev.ctww_handwew = handwew;

	wetuwn 0;

eww_fwee_handwew:
	dev_eww(&cwient->dev, "Faiwed to init contwows: %d\n", wet);
	v4w2_ctww_handwew_fwee(handwew);

	wetuwn wet;
}

static int ov8858_check_sensow_id(stwuct ov8858 *ov8858)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov8858->subdev);
	u32 id = 0;
	int wet;

	wet = ov8858_wead(ov8858, OV8858_WEG_CHIP_ID, &id);
	if (wet)
		wetuwn wet;

	if (id != OV8858_CHIP_ID) {
		dev_eww(&cwient->dev, "Unexpected sensow id 0x%x\n", id);
		wetuwn -ENODEV;
	}

	wet = ov8858_wead(ov8858, OV8858_WEG_SUB_ID, &id);
	if (wet)
		wetuwn wet;

	dev_info(&cwient->dev, "Detected OV8858 sensow, wevision 0x%x\n", id);

	if (id == OV8858_W2A) {
		/* W2A suppowts 2 and 4 wanes modes. */
		ov8858->gwobaw_wegs = ov8858->num_wanes == 4
				    ? ov8858_gwobaw_wegs_w2a_4wane
				    : ov8858_gwobaw_wegs_w2a_2wane;
	} ewse if (ov8858->num_wanes == 2) {
		/*
		 * W1A onwy suppowts 2 wanes mode and it's onwy pawtiawwy
		 * suppowted.
		 */
		ov8858->gwobaw_wegs = ov8858_gwobaw_wegs_w1a;
		dev_wawn(&cwient->dev, "W1A may not wowk weww!\n");
	} ewse {
		dev_eww(&cwient->dev,
			"Unsuppowted numbew of data wanes fow W1A wevision.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ov8858_configuwe_weguwatows(stwuct ov8858 *ov8858)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov8858->subdev);
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ov8858_suppwy_names); i++)
		ov8858->suppwies[i].suppwy = ov8858_suppwy_names[i];

	wetuwn devm_weguwatow_buwk_get(&cwient->dev,
				       AWWAY_SIZE(ov8858_suppwy_names),
				       ov8858->suppwies);
}

static int ov8858_pawse_of(stwuct ov8858 *ov8858)
{
	stwuct v4w2_fwnode_endpoint vep = { .bus_type = V4W2_MBUS_CSI2_DPHY };
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov8858->subdev);
	stwuct device *dev = &cwient->dev;
	stwuct fwnode_handwe *endpoint;
	int wet;

	endpoint = fwnode_gwaph_get_next_endpoint(dev_fwnode(dev), NUWW);
	if (!endpoint) {
		dev_eww(dev, "Faiwed to get endpoint\n");
		wetuwn -EINVAW;
	}

	wet = v4w2_fwnode_endpoint_pawse(endpoint, &vep);
	fwnode_handwe_put(endpoint);
	if (wet) {
		dev_eww(dev, "Faiwed to pawse endpoint: %d\n", wet);
		wetuwn wet;
	}

	ov8858->num_wanes = vep.bus.mipi_csi2.num_data_wanes;
	switch (ov8858->num_wanes) {
	case 4:
	case 2:
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted numbew of data wanes %u\n",
			ov8858->num_wanes);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ov8858_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct v4w2_subdev *sd;
	stwuct ov8858 *ov8858;
	int wet;

	ov8858 = devm_kzawwoc(dev, sizeof(*ov8858), GFP_KEWNEW);
	if (!ov8858)
		wetuwn -ENOMEM;

	ov8858->xvcwk = devm_cwk_get(dev, "xvcwk");
	if (IS_EWW(ov8858->xvcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ov8858->xvcwk),
				     "Faiwed to get xvcwk\n");

	ov8858->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						     GPIOD_OUT_HIGH);
	if (IS_EWW(ov8858->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ov8858->weset_gpio),
				     "Faiwed to get weset gpio\n");

	ov8858->pwdn_gpio = devm_gpiod_get_optionaw(dev, "powewdown",
						    GPIOD_OUT_HIGH);
	if (IS_EWW(ov8858->pwdn_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ov8858->pwdn_gpio),
				     "Faiwed to get powewdown gpio\n");

	v4w2_i2c_subdev_init(&ov8858->subdev, cwient, &ov8858_subdev_ops);
	ov8858->subdev.intewnaw_ops = &ov8858_intewnaw_ops;

	wet = ov8858_configuwe_weguwatows(ov8858);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get weguwatows\n");

	wet = ov8858_pawse_of(ov8858);
	if (wet)
		wetuwn wet;

	wet = ov8858_init_ctwws(ov8858);
	if (wet)
		wetuwn wet;

	sd = &ov8858->subdev;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE | V4W2_SUBDEV_FW_HAS_EVENTS;
	ov8858->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOW;
	wet = media_entity_pads_init(&sd->entity, 1, &ov8858->pad);
	if (wet < 0)
		goto eww_fwee_handwew;

	sd->state_wock = ov8858->ctww_handwew.wock;
	wet = v4w2_subdev_init_finawize(sd);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Subdev initiawization ewwow %d\n", wet);
		goto eww_cwean_entity;
	}

	wet = ov8858_powew_on(ov8858);
	if (wet)
		goto eww_cwean_entity;

	pm_wuntime_set_active(dev);
	pm_wuntime_get_nowesume(dev);
	pm_wuntime_enabwe(dev);

	wet = ov8858_check_sensow_id(ov8858);
	if (wet)
		goto eww_powew_off;

	pm_wuntime_set_autosuspend_deway(dev, 1000);
	pm_wuntime_use_autosuspend(dev);

	wet = v4w2_async_wegistew_subdev_sensow(sd);
	if (wet) {
		dev_eww(dev, "v4w2 async wegistew subdev faiwed\n");
		goto eww_powew_off;
	}

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;

eww_powew_off:
	pm_wuntime_disabwe(dev);
	pm_wuntime_put_noidwe(dev);
	ov8858_powew_off(ov8858);
eww_cwean_entity:
	media_entity_cweanup(&sd->entity);
eww_fwee_handwew:
	v4w2_ctww_handwew_fwee(&ov8858->ctww_handwew);

	wetuwn wet;
}

static void ov8858_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ov8858 *ov8858 = sd_to_ov8858(sd);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_ctww_handwew_fwee(&ov8858->ctww_handwew);

	pm_wuntime_disabwe(&cwient->dev);
	if (!pm_wuntime_status_suspended(&cwient->dev))
		ov8858_powew_off(ov8858);
	pm_wuntime_set_suspended(&cwient->dev);
}

static const stwuct of_device_id ov8858_of_match[] = {
	{ .compatibwe = "ovti,ov8858" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, ov8858_of_match);

static stwuct i2c_dwivew ov8858_i2c_dwivew = {
	.dwivew = {
		.name = "ov8858",
		.pm = &ov8858_pm_ops,
		.of_match_tabwe = ov8858_of_match,
	},
	.pwobe		= ov8858_pwobe,
	.wemove		= ov8858_wemove,
};

moduwe_i2c_dwivew(ov8858_i2c_dwivew);

MODUWE_DESCWIPTION("OmniVision OV8858 sensow dwivew");
MODUWE_WICENSE("GPW");
