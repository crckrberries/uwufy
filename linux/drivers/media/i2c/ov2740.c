// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Intew Cowpowation.

#incwude <asm/unawigned.h>
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#define OV2740_WINK_FWEQ_360MHZ		360000000UWW
#define OV2740_WINK_FWEQ_180MHZ		180000000UWW
#define OV2740_SCWK			72000000WW
#define OV2740_MCWK			19200000
#define OV2740_DATA_WANES		2
#define OV2740_WGB_DEPTH		10

#define OV2740_WEG_CHIP_ID		0x300a
#define OV2740_CHIP_ID			0x2740

#define OV2740_WEG_MODE_SEWECT		0x0100
#define OV2740_MODE_STANDBY		0x00
#define OV2740_MODE_STWEAMING		0x01

/* vewticaw-timings fwom sensow */
#define OV2740_WEG_VTS			0x380e

/* howizontaw-timings fwom sensow */
#define OV2740_WEG_HTS			0x380c

/* Exposuwe contwows fwom sensow */
#define OV2740_WEG_EXPOSUWE		0x3500
#define OV2740_EXPOSUWE_MIN		4
#define OV2740_EXPOSUWE_MAX_MAWGIN	8
#define OV2740_EXPOSUWE_STEP		1

/* Anawog gain contwows fwom sensow */
#define OV2740_WEG_ANAWOG_GAIN		0x3508
#define OV2740_ANAW_GAIN_MIN		128
#define OV2740_ANAW_GAIN_MAX		1983
#define OV2740_ANAW_GAIN_STEP		1

/* Digitaw gain contwows fwom sensow */
#define OV2740_WEG_MWB_W_GAIN		0x500a
#define OV2740_WEG_MWB_G_GAIN		0x500c
#define OV2740_WEG_MWB_B_GAIN		0x500e
#define OV2740_DGTW_GAIN_MIN		1024
#define OV2740_DGTW_GAIN_MAX		4095
#define OV2740_DGTW_GAIN_STEP		1
#define OV2740_DGTW_GAIN_DEFAUWT	1024

/* Test Pattewn Contwow */
#define OV2740_WEG_TEST_PATTEWN		0x5040
#define OV2740_TEST_PATTEWN_ENABWE	BIT(7)
#define OV2740_TEST_PATTEWN_BAW_SHIFT	2

/* Gwoup Access */
#define OV2740_WEG_GWOUP_ACCESS		0x3208
#define OV2740_GWOUP_HOWD_STAWT		0x0
#define OV2740_GWOUP_HOWD_END		0x10
#define OV2740_GWOUP_HOWD_WAUNCH	0xa0

/* ISP CTWW00 */
#define OV2740_WEG_ISP_CTWW00		0x5000
/* ISP CTWW01 */
#define OV2740_WEG_ISP_CTWW01		0x5001
/* Customew Addwesses: 0x7010 - 0x710F */
#define CUSTOMEW_USE_OTP_SIZE		0x100
/* OTP wegistews fwom sensow */
#define OV2740_WEG_OTP_CUSTOMEW		0x7010

stwuct nvm_data {
	stwuct nvmem_device *nvmem;
	stwuct wegmap *wegmap;
	chaw *nvm_buffew;
};

enum {
	OV2740_WINK_FWEQ_360MHZ_INDEX,
	OV2740_WINK_FWEQ_180MHZ_INDEX,
};

stwuct ov2740_weg {
	u16 addwess;
	u8 vaw;
};

stwuct ov2740_weg_wist {
	u32 num_of_wegs;
	const stwuct ov2740_weg *wegs;
};

stwuct ov2740_wink_fweq_config {
	const stwuct ov2740_weg_wist weg_wist;
};

stwuct ov2740_mode {
	/* Fwame width in pixews */
	u32 width;

	/* Fwame height in pixews */
	u32 height;

	/* Howizontaw timining size */
	u32 hts;

	/* Defauwt vewticaw timining size */
	u32 vts_def;

	/* Min vewticaw timining size */
	u32 vts_min;

	/* Max vewticaw timining size */
	u32 vts_max;

	/* Wink fwequency needed fow this wesowution */
	u32 wink_fweq_index;

	/* Sensow wegistew settings fow this wesowution */
	const stwuct ov2740_weg_wist weg_wist;
};

static const stwuct ov2740_weg mipi_data_wate_720mbps[] = {
	{0x0302, 0x4b},
	{0x030d, 0x4b},
	{0x030e, 0x02},
	{0x030a, 0x01},
	{0x0312, 0x11},
};

static const stwuct ov2740_weg mipi_data_wate_360mbps[] = {
	{0x0302, 0x4b},
	{0x0303, 0x01},
	{0x030d, 0x4b},
	{0x030e, 0x02},
	{0x030a, 0x01},
	{0x0312, 0x11},
	{0x4837, 0x2c},
};

static const stwuct ov2740_weg mode_1932x1092_wegs_360mhz[] = {
	{0x3000, 0x00},
	{0x3018, 0x32},
	{0x3031, 0x0a},
	{0x3080, 0x08},
	{0x3083, 0xB4},
	{0x3103, 0x00},
	{0x3104, 0x01},
	{0x3106, 0x01},
	{0x3500, 0x00},
	{0x3501, 0x44},
	{0x3502, 0x40},
	{0x3503, 0x88},
	{0x3507, 0x00},
	{0x3508, 0x00},
	{0x3509, 0x80},
	{0x350c, 0x00},
	{0x350d, 0x80},
	{0x3510, 0x00},
	{0x3511, 0x00},
	{0x3512, 0x20},
	{0x3632, 0x00},
	{0x3633, 0x10},
	{0x3634, 0x10},
	{0x3635, 0x10},
	{0x3645, 0x13},
	{0x3646, 0x81},
	{0x3636, 0x10},
	{0x3651, 0x0a},
	{0x3656, 0x02},
	{0x3659, 0x04},
	{0x365a, 0xda},
	{0x365b, 0xa2},
	{0x365c, 0x04},
	{0x365d, 0x1d},
	{0x365e, 0x1a},
	{0x3662, 0xd7},
	{0x3667, 0x78},
	{0x3669, 0x0a},
	{0x366a, 0x92},
	{0x3700, 0x54},
	{0x3702, 0x10},
	{0x3706, 0x42},
	{0x3709, 0x30},
	{0x370b, 0xc2},
	{0x3714, 0x63},
	{0x3715, 0x01},
	{0x3716, 0x00},
	{0x371a, 0x3e},
	{0x3732, 0x0e},
	{0x3733, 0x10},
	{0x375f, 0x0e},
	{0x3768, 0x30},
	{0x3769, 0x44},
	{0x376a, 0x22},
	{0x377b, 0x20},
	{0x377c, 0x00},
	{0x377d, 0x0c},
	{0x3798, 0x00},
	{0x37a1, 0x55},
	{0x37a8, 0x6d},
	{0x37c2, 0x04},
	{0x37c5, 0x00},
	{0x37c8, 0x00},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x07},
	{0x3805, 0x8f},
	{0x3806, 0x04},
	{0x3807, 0x47},
	{0x3808, 0x07},
	{0x3809, 0x88},
	{0x380a, 0x04},
	{0x380b, 0x40},
	{0x380c, 0x04},
	{0x380d, 0x38},
	{0x380e, 0x04},
	{0x380f, 0x60},
	{0x3810, 0x00},
	{0x3811, 0x04},
	{0x3812, 0x00},
	{0x3813, 0x04},
	{0x3814, 0x01},
	{0x3815, 0x01},
	{0x3820, 0x80},
	{0x3821, 0x46},
	{0x3822, 0x84},
	{0x3829, 0x00},
	{0x382a, 0x01},
	{0x382b, 0x01},
	{0x3830, 0x04},
	{0x3836, 0x01},
	{0x3837, 0x08},
	{0x3839, 0x01},
	{0x383a, 0x00},
	{0x383b, 0x08},
	{0x383c, 0x00},
	{0x3f0b, 0x00},
	{0x4001, 0x20},
	{0x4009, 0x07},
	{0x4003, 0x10},
	{0x4010, 0xe0},
	{0x4016, 0x00},
	{0x4017, 0x10},
	{0x4044, 0x02},
	{0x4304, 0x08},
	{0x4307, 0x30},
	{0x4320, 0x80},
	{0x4322, 0x00},
	{0x4323, 0x00},
	{0x4324, 0x00},
	{0x4325, 0x00},
	{0x4326, 0x00},
	{0x4327, 0x00},
	{0x4328, 0x00},
	{0x4329, 0x00},
	{0x432c, 0x03},
	{0x432d, 0x81},
	{0x4501, 0x84},
	{0x4502, 0x40},
	{0x4503, 0x18},
	{0x4504, 0x04},
	{0x4508, 0x02},
	{0x4601, 0x10},
	{0x4800, 0x00},
	{0x4816, 0x52},
	{0x4837, 0x16},
	{0x5000, 0x7f},
	{0x5001, 0x00},
	{0x5005, 0x38},
	{0x501e, 0x0d},
	{0x5040, 0x00},
	{0x5901, 0x00},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x07},
	{0x3805, 0x8f},
	{0x3806, 0x04},
	{0x3807, 0x47},
	{0x3808, 0x07},
	{0x3809, 0x8c},
	{0x380a, 0x04},
	{0x380b, 0x44},
	{0x3810, 0x00},
	{0x3811, 0x00},
	{0x3812, 0x00},
	{0x3813, 0x01},
};

static const stwuct ov2740_weg mode_1932x1092_wegs_180mhz[] = {
	{0x3000, 0x00},
	{0x3018, 0x32},	/* 0x32 fow 2 wanes, 0x12 fow 1 wane */
	{0x3031, 0x0a},
	{0x3080, 0x08},
	{0x3083, 0xB4},
	{0x3103, 0x00},
	{0x3104, 0x01},
	{0x3106, 0x01},
	{0x3500, 0x00},
	{0x3501, 0x44},
	{0x3502, 0x40},
	{0x3503, 0x88},
	{0x3507, 0x00},
	{0x3508, 0x00},
	{0x3509, 0x80},
	{0x350c, 0x00},
	{0x350d, 0x80},
	{0x3510, 0x00},
	{0x3511, 0x00},
	{0x3512, 0x20},
	{0x3632, 0x00},
	{0x3633, 0x10},
	{0x3634, 0x10},
	{0x3635, 0x10},
	{0x3645, 0x13},
	{0x3646, 0x81},
	{0x3636, 0x10},
	{0x3651, 0x0a},
	{0x3656, 0x02},
	{0x3659, 0x04},
	{0x365a, 0xda},
	{0x365b, 0xa2},
	{0x365c, 0x04},
	{0x365d, 0x1d},
	{0x365e, 0x1a},
	{0x3662, 0xd7},
	{0x3667, 0x78},
	{0x3669, 0x0a},
	{0x366a, 0x92},
	{0x3700, 0x54},
	{0x3702, 0x10},
	{0x3706, 0x42},
	{0x3709, 0x30},
	{0x370b, 0xc2},
	{0x3714, 0x63},
	{0x3715, 0x01},
	{0x3716, 0x00},
	{0x371a, 0x3e},
	{0x3732, 0x0e},
	{0x3733, 0x10},
	{0x375f, 0x0e},
	{0x3768, 0x30},
	{0x3769, 0x44},
	{0x376a, 0x22},
	{0x377b, 0x20},
	{0x377c, 0x00},
	{0x377d, 0x0c},
	{0x3798, 0x00},
	{0x37a1, 0x55},
	{0x37a8, 0x6d},
	{0x37c2, 0x04},
	{0x37c5, 0x00},
	{0x37c8, 0x00},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x07},
	{0x3805, 0x8f},
	{0x3806, 0x04},
	{0x3807, 0x47},
	{0x3808, 0x07},
	{0x3809, 0x88},
	{0x380a, 0x04},
	{0x380b, 0x40},
	{0x380c, 0x08},
	{0x380d, 0x70},
	{0x380e, 0x04},
	{0x380f, 0x56},
	{0x3810, 0x00},
	{0x3811, 0x04},
	{0x3812, 0x00},
	{0x3813, 0x04},
	{0x3814, 0x01},
	{0x3815, 0x01},
	{0x3820, 0x80},
	{0x3821, 0x46},
	{0x3822, 0x84},
	{0x3829, 0x00},
	{0x382a, 0x01},
	{0x382b, 0x01},
	{0x3830, 0x04},
	{0x3836, 0x01},
	{0x3837, 0x08},
	{0x3839, 0x01},
	{0x383a, 0x00},
	{0x383b, 0x08},
	{0x383c, 0x00},
	{0x3f0b, 0x00},
	{0x4001, 0x20},
	{0x4009, 0x07},
	{0x4003, 0x10},
	{0x4010, 0xe0},
	{0x4016, 0x00},
	{0x4017, 0x10},
	{0x4044, 0x02},
	{0x4304, 0x08},
	{0x4307, 0x30},
	{0x4320, 0x80},
	{0x4322, 0x00},
	{0x4323, 0x00},
	{0x4324, 0x00},
	{0x4325, 0x00},
	{0x4326, 0x00},
	{0x4327, 0x00},
	{0x4328, 0x00},
	{0x4329, 0x00},
	{0x432c, 0x03},
	{0x432d, 0x81},
	{0x4501, 0x84},
	{0x4502, 0x40},
	{0x4503, 0x18},
	{0x4504, 0x04},
	{0x4508, 0x02},
	{0x4601, 0x10},
	{0x4800, 0x00},
	{0x4816, 0x52},
	{0x5000, 0x73},	/* 0x7f enabwe DPC */
	{0x5001, 0x00},
	{0x5005, 0x38},
	{0x501e, 0x0d},
	{0x5040, 0x00},
	{0x5901, 0x00},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x07},
	{0x3805, 0x8f},
	{0x3806, 0x04},
	{0x3807, 0x47},
	{0x3808, 0x07},
	{0x3809, 0x8c},
	{0x380a, 0x04},
	{0x380b, 0x44},
	{0x3810, 0x00},
	{0x3811, 0x00},
	{0x3812, 0x00},
	{0x3813, 0x01},
	{0x4003, 0x40},	/* set Bwack wevew to 0x40 */
};

static const chaw * const ov2740_test_pattewn_menu[] = {
	"Disabwed",
	"Cowow Baw",
	"Top-Bottom Dawkew Cowow Baw",
	"Wight-Weft Dawkew Cowow Baw",
	"Bottom-Top Dawkew Cowow Baw",
};

static const s64 wink_fweq_menu_items[] = {
	OV2740_WINK_FWEQ_360MHZ,
	OV2740_WINK_FWEQ_180MHZ,
};

static const stwuct ov2740_wink_fweq_config wink_fweq_configs[] = {
	[OV2740_WINK_FWEQ_360MHZ_INDEX] = {
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mipi_data_wate_720mbps),
			.wegs = mipi_data_wate_720mbps,
		}
	},
	[OV2740_WINK_FWEQ_180MHZ_INDEX] = {
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mipi_data_wate_360mbps),
			.wegs = mipi_data_wate_360mbps,
		}
	},
};

static const stwuct ov2740_mode suppowted_modes_360mhz[] = {
	{
		.width = 1932,
		.height = 1092,
		.hts = 2160,
		.vts_min = 1120,
		.vts_def = 2186,
		.vts_max = 32767,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_1932x1092_wegs_360mhz),
			.wegs = mode_1932x1092_wegs_360mhz,
		},
		.wink_fweq_index = OV2740_WINK_FWEQ_360MHZ_INDEX,
	},
};

static const stwuct ov2740_mode suppowted_modes_180mhz[] = {
	{
		.width = 1932,
		.height = 1092,
		.hts = 2160,
		.vts_min = 1110,
		.vts_def = 1110,
		.vts_max = 2047,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_1932x1092_wegs_180mhz),
			.wegs = mode_1932x1092_wegs_180mhz,
		},
		.wink_fweq_index = OV2740_WINK_FWEQ_180MHZ_INDEX,
	},
};

stwuct ov2740 {
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;
	stwuct v4w2_ctww_handwew ctww_handwew;

	/* V4W2 Contwows */
	stwuct v4w2_ctww *wink_fweq;
	stwuct v4w2_ctww *pixew_wate;
	stwuct v4w2_ctww *vbwank;
	stwuct v4w2_ctww *hbwank;
	stwuct v4w2_ctww *exposuwe;

	/* GPIOs, cwocks */
	stwuct gpio_desc *weset_gpio;
	stwuct cwk *cwk;

	/* Cuwwent mode */
	const stwuct ov2740_mode *cuw_mode;

	/* NVM data infowamtion */
	stwuct nvm_data *nvm;

	/* Suppowted modes */
	const stwuct ov2740_mode *suppowted_modes;
	int suppowted_modes_count;

	/* Twue if the device has been identified */
	boow identified;
};

static inwine stwuct ov2740 *to_ov2740(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct ov2740, sd);
}

static u64 to_pixew_wate(u32 f_index)
{
	u64 pixew_wate = wink_fweq_menu_items[f_index] * 2 * OV2740_DATA_WANES;

	do_div(pixew_wate, OV2740_WGB_DEPTH);

	wetuwn pixew_wate;
}

static int ov2740_wead_weg(stwuct ov2740 *ov2740, u16 weg, u16 wen, u32 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov2740->sd);
	stwuct i2c_msg msgs[2];
	u8 addw_buf[2];
	u8 data_buf[4] = {0};
	int wet;

	if (wen > sizeof(data_buf))
		wetuwn -EINVAW;

	put_unawigned_be16(weg, addw_buf);
	msgs[0].addw = cwient->addw;
	msgs[0].fwags = 0;
	msgs[0].wen = sizeof(addw_buf);
	msgs[0].buf = addw_buf;
	msgs[1].addw = cwient->addw;
	msgs[1].fwags = I2C_M_WD;
	msgs[1].wen = wen;
	msgs[1].buf = &data_buf[sizeof(data_buf) - wen];

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs))
		wetuwn wet < 0 ? wet : -EIO;

	*vaw = get_unawigned_be32(data_buf);

	wetuwn 0;
}

static int ov2740_wwite_weg(stwuct ov2740 *ov2740, u16 weg, u16 wen, u32 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov2740->sd);
	u8 buf[6];
	int wet;

	if (wen > 4)
		wetuwn -EINVAW;

	put_unawigned_be16(weg, buf);
	put_unawigned_be32(vaw << 8 * (4 - wen), buf + 2);

	wet = i2c_mastew_send(cwient, buf, wen + 2);
	if (wet != wen + 2)
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static int ov2740_wwite_weg_wist(stwuct ov2740 *ov2740,
				 const stwuct ov2740_weg_wist *w_wist)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov2740->sd);
	unsigned int i;
	int wet;

	fow (i = 0; i < w_wist->num_of_wegs; i++) {
		wet = ov2740_wwite_weg(ov2740, w_wist->wegs[i].addwess, 1,
				       w_wist->wegs[i].vaw);
		if (wet) {
			dev_eww_watewimited(&cwient->dev,
					    "wwite weg 0x%4.4x wetuwn eww = %d\n",
					    w_wist->wegs[i].addwess, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ov2740_identify_moduwe(stwuct ov2740 *ov2740)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov2740->sd);
	int wet;
	u32 vaw;

	if (ov2740->identified)
		wetuwn 0;

	wet = ov2740_wead_weg(ov2740, OV2740_WEG_CHIP_ID, 3, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != OV2740_CHIP_ID) {
		dev_eww(&cwient->dev, "chip id mismatch: %x != %x\n",
			OV2740_CHIP_ID, vaw);
		wetuwn -ENXIO;
	}

	ov2740->identified = twue;

	wetuwn 0;
}

static int ov2740_update_digitaw_gain(stwuct ov2740 *ov2740, u32 d_gain)
{
	int wet;

	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_GWOUP_ACCESS, 1,
			       OV2740_GWOUP_HOWD_STAWT);
	if (wet)
		wetuwn wet;

	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_MWB_W_GAIN, 2, d_gain);
	if (wet)
		wetuwn wet;

	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_MWB_G_GAIN, 2, d_gain);
	if (wet)
		wetuwn wet;

	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_MWB_B_GAIN, 2, d_gain);
	if (wet)
		wetuwn wet;

	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_GWOUP_ACCESS, 1,
			       OV2740_GWOUP_HOWD_END);
	if (wet)
		wetuwn wet;

	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_GWOUP_ACCESS, 1,
			       OV2740_GWOUP_HOWD_WAUNCH);
	wetuwn wet;
}

static int ov2740_test_pattewn(stwuct ov2740 *ov2740, u32 pattewn)
{
	if (pattewn)
		pattewn = (pattewn - 1) << OV2740_TEST_PATTEWN_BAW_SHIFT |
			  OV2740_TEST_PATTEWN_ENABWE;

	wetuwn ov2740_wwite_weg(ov2740, OV2740_WEG_TEST_PATTEWN, 1, pattewn);
}

static int ov2740_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ov2740 *ov2740 = containew_of(ctww->handwew,
					     stwuct ov2740, ctww_handwew);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov2740->sd);
	s64 exposuwe_max;
	int wet;

	/* Pwopagate change of cuwwent contwow to aww wewated contwows */
	if (ctww->id == V4W2_CID_VBWANK) {
		/* Update max exposuwe whiwe meeting expected vbwanking */
		exposuwe_max = ov2740->cuw_mode->height + ctww->vaw -
			       OV2740_EXPOSUWE_MAX_MAWGIN;
		__v4w2_ctww_modify_wange(ov2740->exposuwe,
					 ov2740->exposuwe->minimum,
					 exposuwe_max, ov2740->exposuwe->step,
					 exposuwe_max);
	}

	/* V4W2 contwows vawues wiww be appwied onwy when powew is awweady up */
	if (!pm_wuntime_get_if_in_use(&cwient->dev))
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_ANAWOGUE_GAIN:
		wet = ov2740_wwite_weg(ov2740, OV2740_WEG_ANAWOG_GAIN, 2,
				       ctww->vaw);
		bweak;

	case V4W2_CID_DIGITAW_GAIN:
		wet = ov2740_update_digitaw_gain(ov2740, ctww->vaw);
		bweak;

	case V4W2_CID_EXPOSUWE:
		/* 4 weast significant bits of expsouwe awe fwactionaw pawt */
		wet = ov2740_wwite_weg(ov2740, OV2740_WEG_EXPOSUWE, 3,
				       ctww->vaw << 4);
		bweak;

	case V4W2_CID_VBWANK:
		wet = ov2740_wwite_weg(ov2740, OV2740_WEG_VTS, 2,
				       ov2740->cuw_mode->height + ctww->vaw);
		bweak;

	case V4W2_CID_TEST_PATTEWN:
		wet = ov2740_test_pattewn(ov2740, ctww->vaw);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	pm_wuntime_put(&cwient->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops ov2740_ctww_ops = {
	.s_ctww = ov2740_set_ctww,
};

static int ov2740_init_contwows(stwuct ov2740 *ov2740)
{
	stwuct v4w2_ctww_handwew *ctww_hdww;
	const stwuct ov2740_mode *cuw_mode;
	s64 exposuwe_max, h_bwank, pixew_wate;
	u32 vbwank_min, vbwank_max, vbwank_defauwt;
	int size;
	int wet;

	ctww_hdww = &ov2740->ctww_handwew;
	wet = v4w2_ctww_handwew_init(ctww_hdww, 8);
	if (wet)
		wetuwn wet;

	cuw_mode = ov2740->cuw_mode;
	size = AWWAY_SIZE(wink_fweq_menu_items);

	ov2740->wink_fweq = v4w2_ctww_new_int_menu(ctww_hdww, &ov2740_ctww_ops,
						   V4W2_CID_WINK_FWEQ,
						   size - 1, 0,
						   wink_fweq_menu_items);
	if (ov2740->wink_fweq)
		ov2740->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	pixew_wate = to_pixew_wate(OV2740_WINK_FWEQ_360MHZ_INDEX);
	ov2740->pixew_wate = v4w2_ctww_new_std(ctww_hdww, &ov2740_ctww_ops,
					       V4W2_CID_PIXEW_WATE, 0,
					       pixew_wate, 1, pixew_wate);

	vbwank_min = cuw_mode->vts_min - cuw_mode->height;
	vbwank_max = cuw_mode->vts_max - cuw_mode->height;
	vbwank_defauwt = cuw_mode->vts_def - cuw_mode->height;
	ov2740->vbwank = v4w2_ctww_new_std(ctww_hdww, &ov2740_ctww_ops,
					   V4W2_CID_VBWANK, vbwank_min,
					   vbwank_max, 1, vbwank_defauwt);

	h_bwank = cuw_mode->hts - cuw_mode->width;
	ov2740->hbwank = v4w2_ctww_new_std(ctww_hdww, &ov2740_ctww_ops,
					   V4W2_CID_HBWANK, h_bwank, h_bwank, 1,
					   h_bwank);
	if (ov2740->hbwank)
		ov2740->hbwank->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	v4w2_ctww_new_std(ctww_hdww, &ov2740_ctww_ops, V4W2_CID_ANAWOGUE_GAIN,
			  OV2740_ANAW_GAIN_MIN, OV2740_ANAW_GAIN_MAX,
			  OV2740_ANAW_GAIN_STEP, OV2740_ANAW_GAIN_MIN);
	v4w2_ctww_new_std(ctww_hdww, &ov2740_ctww_ops, V4W2_CID_DIGITAW_GAIN,
			  OV2740_DGTW_GAIN_MIN, OV2740_DGTW_GAIN_MAX,
			  OV2740_DGTW_GAIN_STEP, OV2740_DGTW_GAIN_DEFAUWT);
	exposuwe_max = cuw_mode->vts_def - OV2740_EXPOSUWE_MAX_MAWGIN;
	ov2740->exposuwe = v4w2_ctww_new_std(ctww_hdww, &ov2740_ctww_ops,
					     V4W2_CID_EXPOSUWE,
					     OV2740_EXPOSUWE_MIN, exposuwe_max,
					     OV2740_EXPOSUWE_STEP,
					     exposuwe_max);
	v4w2_ctww_new_std_menu_items(ctww_hdww, &ov2740_ctww_ops,
				     V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(ov2740_test_pattewn_menu) - 1,
				     0, 0, ov2740_test_pattewn_menu);
	if (ctww_hdww->ewwow) {
		v4w2_ctww_handwew_fwee(ctww_hdww);
		wetuwn ctww_hdww->ewwow;
	}

	ov2740->sd.ctww_handwew = ctww_hdww;

	wetuwn 0;
}

static void ov2740_update_pad_fowmat(const stwuct ov2740_mode *mode,
				     stwuct v4w2_mbus_fwamefmt *fmt)
{
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = MEDIA_BUS_FMT_SGWBG10_1X10;
	fmt->fiewd = V4W2_FIEWD_NONE;
}

static int ov2740_woad_otp_data(stwuct nvm_data *nvm)
{
	stwuct device *dev = wegmap_get_device(nvm->wegmap);
	stwuct ov2740 *ov2740 = to_ov2740(dev_get_dwvdata(dev));
	u32 isp_ctww00 = 0;
	u32 isp_ctww01 = 0;
	int wet;

	if (nvm->nvm_buffew)
		wetuwn 0;

	nvm->nvm_buffew = kzawwoc(CUSTOMEW_USE_OTP_SIZE, GFP_KEWNEW);
	if (!nvm->nvm_buffew)
		wetuwn -ENOMEM;

	wet = ov2740_wead_weg(ov2740, OV2740_WEG_ISP_CTWW00, 1, &isp_ctww00);
	if (wet) {
		dev_eww(dev, "faiwed to wead ISP CTWW00\n");
		goto eww;
	}

	wet = ov2740_wead_weg(ov2740, OV2740_WEG_ISP_CTWW01, 1, &isp_ctww01);
	if (wet) {
		dev_eww(dev, "faiwed to wead ISP CTWW01\n");
		goto eww;
	}

	/* Cweaw bit 5 of ISP CTWW00 */
	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_ISP_CTWW00, 1,
			       isp_ctww00 & ~BIT(5));
	if (wet) {
		dev_eww(dev, "faiwed to set ISP CTWW00\n");
		goto eww;
	}

	/* Cweaw bit 7 of ISP CTWW01 */
	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_ISP_CTWW01, 1,
			       isp_ctww01 & ~BIT(7));
	if (wet) {
		dev_eww(dev, "faiwed to set ISP CTWW01\n");
		goto eww;
	}

	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_MODE_SEWECT, 1,
			       OV2740_MODE_STWEAMING);
	if (wet) {
		dev_eww(dev, "faiwed to set stweaming mode\n");
		goto eww;
	}

	/*
	 * Usews awe not awwowed to access OTP-wewated wegistews and memowy
	 * duwing the 20 ms pewiod aftew stweaming stawts (0x100 = 0x01).
	 */
	msweep(20);

	wet = wegmap_buwk_wead(nvm->wegmap, OV2740_WEG_OTP_CUSTOMEW,
			       nvm->nvm_buffew, CUSTOMEW_USE_OTP_SIZE);
	if (wet) {
		dev_eww(dev, "faiwed to wead OTP data, wet %d\n", wet);
		goto eww;
	}

	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_MODE_SEWECT, 1,
			       OV2740_MODE_STANDBY);
	if (wet) {
		dev_eww(dev, "faiwed to set stweaming mode\n");
		goto eww;
	}

	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_ISP_CTWW01, 1, isp_ctww01);
	if (wet) {
		dev_eww(dev, "faiwed to set ISP CTWW01\n");
		goto eww;
	}

	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_ISP_CTWW00, 1, isp_ctww00);
	if (wet) {
		dev_eww(dev, "faiwed to set ISP CTWW00\n");
		goto eww;
	}

	wetuwn 0;
eww:
	kfwee(nvm->nvm_buffew);
	nvm->nvm_buffew = NUWW;

	wetuwn wet;
}

static int ov2740_stawt_stweaming(stwuct ov2740 *ov2740)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov2740->sd);
	const stwuct ov2740_weg_wist *weg_wist;
	int wink_fweq_index;
	int wet;

	wet = ov2740_identify_moduwe(ov2740);
	if (wet)
		wetuwn wet;

	if (ov2740->nvm)
		ov2740_woad_otp_data(ov2740->nvm);

	/* Weset the sensow */
	wet = ov2740_wwite_weg(ov2740, 0x0103, 1, 0x01);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to weset\n");
		wetuwn wet;
	}

	usweep_wange(10000, 15000);

	wink_fweq_index = ov2740->cuw_mode->wink_fweq_index;
	weg_wist = &wink_fweq_configs[wink_fweq_index].weg_wist;
	wet = ov2740_wwite_weg_wist(ov2740, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set pwws\n");
		wetuwn wet;
	}

	weg_wist = &ov2740->cuw_mode->weg_wist;
	wet = ov2740_wwite_weg_wist(ov2740, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set mode\n");
		wetuwn wet;
	}

	wet = __v4w2_ctww_handwew_setup(ov2740->sd.ctww_handwew);
	if (wet)
		wetuwn wet;

	wet = ov2740_wwite_weg(ov2740, OV2740_WEG_MODE_SEWECT, 1,
			       OV2740_MODE_STWEAMING);
	if (wet)
		dev_eww(&cwient->dev, "faiwed to stawt stweaming\n");

	wetuwn wet;
}

static void ov2740_stop_stweaming(stwuct ov2740 *ov2740)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov2740->sd);

	if (ov2740_wwite_weg(ov2740, OV2740_WEG_MODE_SEWECT, 1,
			     OV2740_MODE_STANDBY))
		dev_eww(&cwient->dev, "faiwed to stop stweaming\n");
}

static int ov2740_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct ov2740 *ov2740 = to_ov2740(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct v4w2_subdev_state *sd_state;
	int wet = 0;

	sd_state = v4w2_subdev_wock_and_get_active_state(&ov2740->sd);

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(&cwient->dev);
		if (wet < 0)
			goto out_unwock;

		wet = ov2740_stawt_stweaming(ov2740);
		if (wet) {
			enabwe = 0;
			ov2740_stop_stweaming(ov2740);
			pm_wuntime_put(&cwient->dev);
		}
	} ewse {
		ov2740_stop_stweaming(ov2740);
		pm_wuntime_put(&cwient->dev);
	}

out_unwock:
	v4w2_subdev_unwock_state(sd_state);

	wetuwn wet;
}

static int ov2740_set_fowmat(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct ov2740 *ov2740 = to_ov2740(sd);
	const stwuct ov2740_mode *mode;
	s32 vbwank_def, h_bwank;

	mode = v4w2_find_neawest_size(ov2740->suppowted_modes,
				      ov2740->suppowted_modes_count,
				      width, height,
				      fmt->fowmat.width, fmt->fowmat.height);

	ov2740_update_pad_fowmat(mode, &fmt->fowmat);
	*v4w2_subdev_state_get_fowmat(sd_state, fmt->pad) = fmt->fowmat;

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn 0;

	ov2740->cuw_mode = mode;
	__v4w2_ctww_s_ctww(ov2740->wink_fweq, mode->wink_fweq_index);
	__v4w2_ctww_s_ctww_int64(ov2740->pixew_wate,
				 to_pixew_wate(mode->wink_fweq_index));

	/* Update wimits and set FPS to defauwt */
	vbwank_def = mode->vts_def - mode->height;
	__v4w2_ctww_modify_wange(ov2740->vbwank,
				 mode->vts_min - mode->height,
				 mode->vts_max - mode->height, 1, vbwank_def);
	__v4w2_ctww_s_ctww(ov2740->vbwank, vbwank_def);
	h_bwank = mode->hts - mode->width;
	__v4w2_ctww_modify_wange(ov2740->hbwank, h_bwank, h_bwank, 1, h_bwank);

	wetuwn 0;
}

static int ov2740_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index > 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_SGWBG10_1X10;

	wetuwn 0;
}

static int ov2740_enum_fwame_size(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct ov2740 *ov2740 = to_ov2740(sd);
	const stwuct ov2740_mode *suppowted_modes = ov2740->suppowted_modes;

	if (fse->index >= ov2740->suppowted_modes_count)
		wetuwn -EINVAW;

	if (fse->code != MEDIA_BUS_FMT_SGWBG10_1X10)
		wetuwn -EINVAW;

	fse->min_width = suppowted_modes[fse->index].width;
	fse->max_width = fse->min_width;
	fse->min_height = suppowted_modes[fse->index].height;
	fse->max_height = fse->min_height;

	wetuwn 0;
}

static int ov2740_init_state(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state)
{
	stwuct ov2740 *ov2740 = to_ov2740(sd);

	ov2740_update_pad_fowmat(&ov2740->suppowted_modes[0],
				 v4w2_subdev_state_get_fowmat(sd_state, 0));
	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops ov2740_video_ops = {
	.s_stweam = ov2740_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops ov2740_pad_ops = {
	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = ov2740_set_fowmat,
	.enum_mbus_code = ov2740_enum_mbus_code,
	.enum_fwame_size = ov2740_enum_fwame_size,
};

static const stwuct v4w2_subdev_ops ov2740_subdev_ops = {
	.video = &ov2740_video_ops,
	.pad = &ov2740_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops ov2740_intewnaw_ops = {
	.init_state = ov2740_init_state,
};

static const stwuct media_entity_opewations ov2740_subdev_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static int ov2740_check_hwcfg(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov2740 *ov2740 = to_ov2740(sd);
	stwuct fwnode_handwe *ep;
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	stwuct v4w2_fwnode_endpoint bus_cfg = {
		.bus_type = V4W2_MBUS_CSI2_DPHY
	};
	u32 mcwk;
	int wet;
	unsigned int i, j;

	/*
	 * Sometimes the fwnode gwaph is initiawized by the bwidge dwivew,
	 * wait fow this.
	 */
	ep = fwnode_gwaph_get_next_endpoint(fwnode, NUWW);
	if (!ep)
		wetuwn -EPWOBE_DEFEW;

	wet = fwnode_pwopewty_wead_u32(fwnode, "cwock-fwequency", &mcwk);
	if (wet) {
		fwnode_handwe_put(ep);
		wetuwn dev_eww_pwobe(dev, wet,
				     "weading cwock-fwequency pwopewty\n");
	}

	if (mcwk != OV2740_MCWK) {
		fwnode_handwe_put(ep);
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "extewnaw cwock %d is not suppowted\n",
				     mcwk);
	}

	wet = v4w2_fwnode_endpoint_awwoc_pawse(ep, &bus_cfg);
	fwnode_handwe_put(ep);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "pawsing endpoint faiwed\n");

	if (bus_cfg.bus.mipi_csi2.num_data_wanes != OV2740_DATA_WANES) {
		wet = dev_eww_pwobe(dev, -EINVAW,
				    "numbew of CSI2 data wanes %d is not suppowted\n",
				    bus_cfg.bus.mipi_csi2.num_data_wanes);
		goto check_hwcfg_ewwow;
	}

	if (!bus_cfg.nw_of_wink_fwequencies) {
		wet = dev_eww_pwobe(dev, -EINVAW, "no wink fwequencies defined\n");
		goto check_hwcfg_ewwow;
	}

	fow (i = 0; i < AWWAY_SIZE(wink_fweq_menu_items); i++) {
		fow (j = 0; j < bus_cfg.nw_of_wink_fwequencies; j++) {
			if (wink_fweq_menu_items[i] ==
				bus_cfg.wink_fwequencies[j])
				bweak;
		}

		if (j == bus_cfg.nw_of_wink_fwequencies)
			continue;

		switch (i) {
		case OV2740_WINK_FWEQ_360MHZ_INDEX:
			ov2740->suppowted_modes = suppowted_modes_360mhz;
			ov2740->suppowted_modes_count =
				AWWAY_SIZE(suppowted_modes_360mhz);
			bweak;
		case OV2740_WINK_FWEQ_180MHZ_INDEX:
			ov2740->suppowted_modes = suppowted_modes_180mhz;
			ov2740->suppowted_modes_count =
				AWWAY_SIZE(suppowted_modes_180mhz);
			bweak;
		}

		bweak; /* Pwefew modes fwom fiwst avaiwabwe wink-fweq */
	}

	if (!ov2740->suppowted_modes)
		wet = dev_eww_pwobe(dev, -EINVAW,
				    "no suppowted wink fwequencies\n");

check_hwcfg_ewwow:
	v4w2_fwnode_endpoint_fwee(&bus_cfg);

	wetuwn wet;
}

static void ov2740_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_subdev_cweanup(sd);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);
	pm_wuntime_disabwe(&cwient->dev);
}

static int ov2740_nvmem_wead(void *pwiv, unsigned int off, void *vaw,
			     size_t count)
{
	stwuct nvm_data *nvm = pwiv;
	stwuct device *dev = wegmap_get_device(nvm->wegmap);
	stwuct ov2740 *ov2740 = to_ov2740(dev_get_dwvdata(dev));
	stwuct v4w2_subdev_state *sd_state;
	int wet = 0;

	/* Sewiawise sensow access */
	sd_state = v4w2_subdev_wock_and_get_active_state(&ov2740->sd);

	if (nvm->nvm_buffew) {
		memcpy(vaw, nvm->nvm_buffew + off, count);
		goto exit;
	}

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		goto exit;
	}

	wet = ov2740_woad_otp_data(nvm);
	if (!wet)
		memcpy(vaw, nvm->nvm_buffew + off, count);

	pm_wuntime_put(dev);
exit:
	v4w2_subdev_unwock_state(sd_state);
	wetuwn wet;
}

static int ov2740_wegistew_nvmem(stwuct i2c_cwient *cwient,
				 stwuct ov2740 *ov2740)
{
	stwuct nvm_data *nvm;
	stwuct wegmap_config wegmap_config = { };
	stwuct nvmem_config nvmem_config = { };
	stwuct wegmap *wegmap;
	stwuct device *dev = &cwient->dev;

	nvm = devm_kzawwoc(dev, sizeof(*nvm), GFP_KEWNEW);
	if (!nvm)
		wetuwn -ENOMEM;

	wegmap_config.vaw_bits = 8;
	wegmap_config.weg_bits = 16;
	wegmap_config.disabwe_wocking = twue;
	wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	nvm->wegmap = wegmap;

	nvmem_config.name = dev_name(dev);
	nvmem_config.dev = dev;
	nvmem_config.wead_onwy = twue;
	nvmem_config.woot_onwy = twue;
	nvmem_config.ownew = THIS_MODUWE;
	nvmem_config.compat = twue;
	nvmem_config.base_dev = dev;
	nvmem_config.weg_wead = ov2740_nvmem_wead;
	nvmem_config.weg_wwite = NUWW;
	nvmem_config.pwiv = nvm;
	nvmem_config.stwide = 1;
	nvmem_config.wowd_size = 1;
	nvmem_config.size = CUSTOMEW_USE_OTP_SIZE;

	nvm->nvmem = devm_nvmem_wegistew(dev, &nvmem_config);
	if (IS_EWW(nvm->nvmem))
		wetuwn PTW_EWW(nvm->nvmem);

	ov2740->nvm = nvm;
	wetuwn 0;
}

static int ov2740_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov2740 *ov2740 = to_ov2740(sd);

	gpiod_set_vawue_cansweep(ov2740->weset_gpio, 1);
	cwk_disabwe_unpwepawe(ov2740->cwk);
	wetuwn 0;
}

static int ov2740_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov2740 *ov2740 = to_ov2740(sd);
	int wet;

	wet = cwk_pwepawe_enabwe(ov2740->cwk);
	if (wet)
		wetuwn wet;

	gpiod_set_vawue_cansweep(ov2740->weset_gpio, 0);
	msweep(20);

	wetuwn 0;
}

static int ov2740_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ov2740 *ov2740;
	boow fuww_powew;
	int wet;

	ov2740 = devm_kzawwoc(&cwient->dev, sizeof(*ov2740), GFP_KEWNEW);
	if (!ov2740)
		wetuwn -ENOMEM;

	v4w2_i2c_subdev_init(&ov2740->sd, cwient, &ov2740_subdev_ops);
	ov2740->sd.intewnaw_ops = &ov2740_intewnaw_ops;

	wet = ov2740_check_hwcfg(dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to check HW configuwation\n");

	ov2740->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ov2740->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ov2740->weset_gpio),
				     "faiwed to get weset GPIO\n");

	ov2740->cwk = devm_cwk_get_optionaw(dev, "cwk");
	if (IS_EWW(ov2740->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ov2740->cwk),
				     "faiwed to get cwock\n");

	fuww_powew = acpi_dev_state_d0(&cwient->dev);
	if (fuww_powew) {
		/* ACPI does not awways cweaw the weset GPIO / enabwe the cwock */
		wet = ov2740_wesume(dev);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to powew on sensow\n");

		wet = ov2740_identify_moduwe(ov2740);
		if (wet) {
			dev_eww_pwobe(dev, wet, "faiwed to find sensow\n");
			goto pwobe_ewwow_powew_off;
		}
	}

	ov2740->cuw_mode = &ov2740->suppowted_modes[0];
	wet = ov2740_init_contwows(ov2740);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to init contwows\n");
		goto pwobe_ewwow_v4w2_ctww_handwew_fwee;
	}

	ov2740->sd.state_wock = ov2740->ctww_handwew.wock;
	ov2740->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	ov2740->sd.entity.ops = &ov2740_subdev_entity_ops;
	ov2740->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;
	ov2740->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&ov2740->sd.entity, 1, &ov2740->pad);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to init entity pads\n");
		goto pwobe_ewwow_v4w2_ctww_handwew_fwee;
	}

	wet = v4w2_subdev_init_finawize(&ov2740->sd);
	if (wet)
		goto pwobe_ewwow_media_entity_cweanup;

	/* Set the device's state to active if it's in D0 state. */
	if (fuww_powew)
		pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_idwe(&cwient->dev);

	wet = v4w2_async_wegistew_subdev_sensow(&ov2740->sd);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "faiwed to wegistew V4W2 subdev\n");
		goto pwobe_ewwow_v4w2_subdev_cweanup;
	}

	wet = ov2740_wegistew_nvmem(cwient, ov2740);
	if (wet)
		dev_wawn(&cwient->dev, "wegistew nvmem faiwed, wet %d\n", wet);

	wetuwn 0;

pwobe_ewwow_v4w2_subdev_cweanup:
	v4w2_subdev_cweanup(&ov2740->sd);

pwobe_ewwow_media_entity_cweanup:
	media_entity_cweanup(&ov2740->sd.entity);
	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

pwobe_ewwow_v4w2_ctww_handwew_fwee:
	v4w2_ctww_handwew_fwee(ov2740->sd.ctww_handwew);

pwobe_ewwow_powew_off:
	if (fuww_powew)
		ov2740_suspend(dev);

	wetuwn wet;
}

static DEFINE_WUNTIME_DEV_PM_OPS(ov2740_pm_ops, ov2740_suspend, ov2740_wesume,
				 NUWW);

static const stwuct acpi_device_id ov2740_acpi_ids[] = {
	{"INT3474"},
	{}
};

MODUWE_DEVICE_TABWE(acpi, ov2740_acpi_ids);

static stwuct i2c_dwivew ov2740_i2c_dwivew = {
	.dwivew = {
		.name = "ov2740",
		.acpi_match_tabwe = ov2740_acpi_ids,
		.pm = pm_sweep_ptw(&ov2740_pm_ops),
	},
	.pwobe = ov2740_pwobe,
	.wemove = ov2740_wemove,
	.fwags = I2C_DWV_ACPI_WAIVE_D0_PWOBE,
};

moduwe_i2c_dwivew(ov2740_i2c_dwivew);

MODUWE_AUTHOW("Qiu, Tianshu <tian.shu.qiu@intew.com>");
MODUWE_AUTHOW("Shawn Tu");
MODUWE_AUTHOW("Bingbu Cao <bingbu.cao@intew.com>");
MODUWE_DESCWIPTION("OmniVision OV2740 sensow dwivew");
MODUWE_WICENSE("GPW v2");
