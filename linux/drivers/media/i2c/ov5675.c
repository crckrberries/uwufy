// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Intew Cowpowation.

#incwude <asm/unawigned.h>
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#define OV5675_WEG_VAWUE_08BIT		1
#define OV5675_WEG_VAWUE_16BIT		2
#define OV5675_WEG_VAWUE_24BIT		3

#define OV5675_WINK_FWEQ_450MHZ		450000000UWW
#define OV5675_SCWK			90000000WW
#define OV5675_XVCWK_19_2		19200000
#define OV5675_DATA_WANES		2
#define OV5675_WGB_DEPTH		10

#define OV5675_WEG_CHIP_ID		0x300a
#define OV5675_CHIP_ID			0x5675

#define OV5675_WEG_MODE_SEWECT		0x0100
#define OV5675_MODE_STANDBY		0x00
#define OV5675_MODE_STWEAMING		0x01

/* vewticaw-timings fwom sensow */
#define OV5675_WEG_VTS			0x380e
#define OV5675_VTS_30FPS		0x07e4
#define OV5675_VTS_30FPS_MIN		0x07e4
#define OV5675_VTS_MAX			0x7fff

/* howizontaw-timings fwom sensow */
#define OV5675_WEG_HTS			0x380c

/* Exposuwe contwows fwom sensow */
#define OV5675_WEG_EXPOSUWE		0x3500
#define	OV5675_EXPOSUWE_MIN		4
#define OV5675_EXPOSUWE_MAX_MAWGIN	4
#define	OV5675_EXPOSUWE_STEP		1

/* Anawog gain contwows fwom sensow */
#define OV5675_WEG_ANAWOG_GAIN		0x3508
#define	OV5675_ANAW_GAIN_MIN		128
#define	OV5675_ANAW_GAIN_MAX		2047
#define	OV5675_ANAW_GAIN_STEP		1

/* Digitaw gain contwows fwom sensow */
#define OV5675_WEG_DIGITAW_GAIN		0x350a
#define OV5675_WEG_MWB_W_GAIN		0x5019
#define OV5675_WEG_MWB_G_GAIN		0x501b
#define OV5675_WEG_MWB_B_GAIN		0x501d
#define OV5675_DGTW_GAIN_MIN		1024
#define OV5675_DGTW_GAIN_MAX		4095
#define OV5675_DGTW_GAIN_STEP		1
#define OV5675_DGTW_GAIN_DEFAUWT	1024

/* Gwoup Access */
#define OV5675_WEG_GWOUP_ACCESS		0x3208
#define OV5675_GWOUP_HOWD_STAWT		0x0
#define OV5675_GWOUP_HOWD_END		0x10
#define OV5675_GWOUP_HOWD_WAUNCH	0xa0

/* Test Pattewn Contwow */
#define OV5675_WEG_TEST_PATTEWN		0x4503
#define OV5675_TEST_PATTEWN_ENABWE	BIT(7)
#define OV5675_TEST_PATTEWN_BAW_SHIFT	2

/* Fwip Miwwow Contwows fwom sensow */
#define OV5675_WEG_FOWMAT1		0x3820
#define OV5675_WEG_FOWMAT2		0x373d

#define to_ov5675(_sd)			containew_of(_sd, stwuct ov5675, sd)

static const chaw * const ov5675_suppwy_names[] = {
	"avdd",		/* Anawog powew */
	"dovdd",	/* Digitaw I/O powew */
	"dvdd",		/* Digitaw cowe powew */
};

#define OV5675_NUM_SUPPWIES	AWWAY_SIZE(ov5675_suppwy_names)

enum {
	OV5675_WINK_FWEQ_900MBPS,
};

stwuct ov5675_weg {
	u16 addwess;
	u8 vaw;
};

stwuct ov5675_weg_wist {
	u32 num_of_wegs;
	const stwuct ov5675_weg *wegs;
};

stwuct ov5675_wink_fweq_config {
	const stwuct ov5675_weg_wist weg_wist;
};

stwuct ov5675_mode {
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

	/* Wink fwequency needed fow this wesowution */
	u32 wink_fweq_index;

	/* Sensow wegistew settings fow this wesowution */
	const stwuct ov5675_weg_wist weg_wist;
};

static const stwuct ov5675_weg mipi_data_wate_900mbps[] = {
	{0x0103, 0x01},
	{0x0100, 0x00},
	{0x0300, 0x04},
	{0x0302, 0x8d},
	{0x0303, 0x00},
	{0x030d, 0x26},
};

static const stwuct ov5675_weg mode_2592x1944_wegs[] = {
	{0x3002, 0x21},
	{0x3107, 0x23},
	{0x3501, 0x20},
	{0x3503, 0x0c},
	{0x3508, 0x03},
	{0x3509, 0x00},
	{0x3600, 0x66},
	{0x3602, 0x30},
	{0x3610, 0xa5},
	{0x3612, 0x93},
	{0x3620, 0x80},
	{0x3642, 0x0e},
	{0x3661, 0x00},
	{0x3662, 0x10},
	{0x3664, 0xf3},
	{0x3665, 0x9e},
	{0x3667, 0xa5},
	{0x366e, 0x55},
	{0x366f, 0x55},
	{0x3670, 0x11},
	{0x3671, 0x11},
	{0x3672, 0x11},
	{0x3673, 0x11},
	{0x3714, 0x24},
	{0x371a, 0x3e},
	{0x3733, 0x10},
	{0x3734, 0x00},
	{0x373d, 0x24},
	{0x3764, 0x20},
	{0x3765, 0x20},
	{0x3766, 0x12},
	{0x37a1, 0x14},
	{0x37a8, 0x1c},
	{0x37ab, 0x0f},
	{0x37c2, 0x04},
	{0x37cb, 0x00},
	{0x37cc, 0x00},
	{0x37cd, 0x00},
	{0x37ce, 0x00},
	{0x37d8, 0x02},
	{0x37d9, 0x08},
	{0x37dc, 0x04},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x04},
	{0x3804, 0x0a},
	{0x3805, 0x3f},
	{0x3806, 0x07},
	{0x3807, 0xb3},
	{0x3808, 0x0a},
	{0x3809, 0x20},
	{0x380a, 0x07},
	{0x380b, 0x98},
	{0x380c, 0x02},
	{0x380d, 0xee},
	{0x380e, 0x07},
	{0x380f, 0xe4},
	{0x3811, 0x10},
	{0x3813, 0x0d},
	{0x3814, 0x01},
	{0x3815, 0x01},
	{0x3816, 0x01},
	{0x3817, 0x01},
	{0x381e, 0x02},
	{0x3820, 0x88},
	{0x3821, 0x01},
	{0x3832, 0x04},
	{0x3c80, 0x01},
	{0x3c82, 0x00},
	{0x3c83, 0xc8},
	{0x3c8c, 0x0f},
	{0x3c8d, 0xa0},
	{0x3c90, 0x07},
	{0x3c91, 0x00},
	{0x3c92, 0x00},
	{0x3c93, 0x00},
	{0x3c94, 0xd0},
	{0x3c95, 0x50},
	{0x3c96, 0x35},
	{0x3c97, 0x00},
	{0x4001, 0xe0},
	{0x4008, 0x02},
	{0x4009, 0x0d},
	{0x400f, 0x80},
	{0x4013, 0x02},
	{0x4040, 0x00},
	{0x4041, 0x07},
	{0x404c, 0x50},
	{0x404e, 0x20},
	{0x4500, 0x06},
	{0x4503, 0x00},
	{0x450a, 0x04},
	{0x4809, 0x04},
	{0x480c, 0x12},
	{0x4819, 0x70},
	{0x4825, 0x32},
	{0x4826, 0x32},
	{0x482a, 0x06},
	{0x4833, 0x08},
	{0x4837, 0x0d},
	{0x5000, 0x77},
	{0x5b00, 0x01},
	{0x5b01, 0x10},
	{0x5b02, 0x01},
	{0x5b03, 0xdb},
	{0x5b05, 0x6c},
	{0x5e10, 0xfc},
	{0x3500, 0x00},
	{0x3501, 0x3E},
	{0x3502, 0x60},
	{0x3503, 0x08},
	{0x3508, 0x04},
	{0x3509, 0x00},
	{0x3832, 0x48},
	{0x5780, 0x3e},
	{0x5781, 0x0f},
	{0x5782, 0x44},
	{0x5783, 0x02},
	{0x5784, 0x01},
	{0x5785, 0x01},
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
	{0x5791, 0x06},
	{0x5792, 0x00},
	{0x5793, 0x52},
	{0x5794, 0xa3},
	{0x4003, 0x40},
	{0x3107, 0x01},
	{0x3c80, 0x08},
	{0x3c83, 0xb1},
	{0x3c8c, 0x10},
	{0x3c8d, 0x00},
	{0x3c90, 0x00},
	{0x3c94, 0x00},
	{0x3c95, 0x00},
	{0x3c96, 0x00},
	{0x37cb, 0x09},
	{0x37cc, 0x15},
	{0x37cd, 0x1f},
	{0x37ce, 0x1f},
};

static const stwuct ov5675_weg mode_1296x972_wegs[] = {
	{0x3002, 0x21},
	{0x3107, 0x23},
	{0x3501, 0x20},
	{0x3503, 0x0c},
	{0x3508, 0x03},
	{0x3509, 0x00},
	{0x3600, 0x66},
	{0x3602, 0x30},
	{0x3610, 0xa5},
	{0x3612, 0x93},
	{0x3620, 0x80},
	{0x3642, 0x0e},
	{0x3661, 0x00},
	{0x3662, 0x08},
	{0x3664, 0xf3},
	{0x3665, 0x9e},
	{0x3667, 0xa5},
	{0x366e, 0x55},
	{0x366f, 0x55},
	{0x3670, 0x11},
	{0x3671, 0x11},
	{0x3672, 0x11},
	{0x3673, 0x11},
	{0x3714, 0x28},
	{0x371a, 0x3e},
	{0x3733, 0x10},
	{0x3734, 0x00},
	{0x373d, 0x24},
	{0x3764, 0x20},
	{0x3765, 0x20},
	{0x3766, 0x12},
	{0x37a1, 0x14},
	{0x37a8, 0x1c},
	{0x37ab, 0x0f},
	{0x37c2, 0x14},
	{0x37cb, 0x00},
	{0x37cc, 0x00},
	{0x37cd, 0x00},
	{0x37ce, 0x00},
	{0x37d8, 0x02},
	{0x37d9, 0x04},
	{0x37dc, 0x04},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x0a},
	{0x3805, 0x3f},
	{0x3806, 0x07},
	{0x3807, 0xb7},
	{0x3808, 0x05},
	{0x3809, 0x10},
	{0x380a, 0x03},
	{0x380b, 0xcc},
	{0x380c, 0x02},
	{0x380d, 0xee},
	{0x380e, 0x07},
	{0x380f, 0xd0},
	{0x3811, 0x08},
	{0x3813, 0x0d},
	{0x3814, 0x03},
	{0x3815, 0x01},
	{0x3816, 0x03},
	{0x3817, 0x01},
	{0x381e, 0x02},
	{0x3820, 0x8b},
	{0x3821, 0x01},
	{0x3832, 0x04},
	{0x3c80, 0x01},
	{0x3c82, 0x00},
	{0x3c83, 0xc8},
	{0x3c8c, 0x0f},
	{0x3c8d, 0xa0},
	{0x3c90, 0x07},
	{0x3c91, 0x00},
	{0x3c92, 0x00},
	{0x3c93, 0x00},
	{0x3c94, 0xd0},
	{0x3c95, 0x50},
	{0x3c96, 0x35},
	{0x3c97, 0x00},
	{0x4001, 0xe0},
	{0x4008, 0x00},
	{0x4009, 0x07},
	{0x400f, 0x80},
	{0x4013, 0x02},
	{0x4040, 0x00},
	{0x4041, 0x03},
	{0x404c, 0x50},
	{0x404e, 0x20},
	{0x4500, 0x06},
	{0x4503, 0x00},
	{0x450a, 0x04},
	{0x4809, 0x04},
	{0x480c, 0x12},
	{0x4819, 0x70},
	{0x4825, 0x32},
	{0x4826, 0x32},
	{0x482a, 0x06},
	{0x4833, 0x08},
	{0x4837, 0x0d},
	{0x5000, 0x77},
	{0x5b00, 0x01},
	{0x5b01, 0x10},
	{0x5b02, 0x01},
	{0x5b03, 0xdb},
	{0x5b05, 0x6c},
	{0x5e10, 0xfc},
	{0x3500, 0x00},
	{0x3501, 0x1F},
	{0x3502, 0x20},
	{0x3503, 0x08},
	{0x3508, 0x04},
	{0x3509, 0x00},
	{0x3832, 0x48},
	{0x5780, 0x3e},
	{0x5781, 0x0f},
	{0x5782, 0x44},
	{0x5783, 0x02},
	{0x5784, 0x01},
	{0x5785, 0x01},
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
	{0x5791, 0x06},
	{0x5792, 0x00},
	{0x5793, 0x52},
	{0x5794, 0xa3},
	{0x4003, 0x40},
	{0x3107, 0x01},
	{0x3c80, 0x08},
	{0x3c83, 0xb1},
	{0x3c8c, 0x10},
	{0x3c8d, 0x00},
	{0x3c90, 0x00},
	{0x3c94, 0x00},
	{0x3c95, 0x00},
	{0x3c96, 0x00},
	{0x37cb, 0x09},
	{0x37cc, 0x15},
	{0x37cd, 0x1f},
	{0x37ce, 0x1f},
};

static const chaw * const ov5675_test_pattewn_menu[] = {
	"Disabwed",
	"Standawd Cowow Baw",
	"Top-Bottom Dawkew Cowow Baw",
	"Wight-Weft Dawkew Cowow Baw",
	"Bottom-Top Dawkew Cowow Baw"
};

static const s64 wink_fweq_menu_items[] = {
	OV5675_WINK_FWEQ_450MHZ,
};

static const stwuct ov5675_wink_fweq_config wink_fweq_configs[] = {
	[OV5675_WINK_FWEQ_900MBPS] = {
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mipi_data_wate_900mbps),
			.wegs = mipi_data_wate_900mbps,
		}
	}
};

static const stwuct ov5675_mode suppowted_modes[] = {
	{
		.width = 2592,
		.height = 1944,
		.hts = 1500,
		.vts_def = OV5675_VTS_30FPS,
		.vts_min = OV5675_VTS_30FPS_MIN,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_2592x1944_wegs),
			.wegs = mode_2592x1944_wegs,
		},
		.wink_fweq_index = OV5675_WINK_FWEQ_900MBPS,
	},
	{
		.width = 1296,
		.height = 972,
		.hts = 1500,
		.vts_def = OV5675_VTS_30FPS,
		.vts_min = OV5675_VTS_30FPS_MIN,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_1296x972_wegs),
			.wegs = mode_1296x972_wegs,
		},
		.wink_fweq_index = OV5675_WINK_FWEQ_900MBPS,
	}
};

stwuct ov5675 {
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct cwk *xvcwk;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow_buwk_data suppwies[OV5675_NUM_SUPPWIES];

	/* V4W2 Contwows */
	stwuct v4w2_ctww *wink_fweq;
	stwuct v4w2_ctww *pixew_wate;
	stwuct v4w2_ctww *vbwank;
	stwuct v4w2_ctww *hbwank;
	stwuct v4w2_ctww *exposuwe;

	/* Cuwwent mode */
	const stwuct ov5675_mode *cuw_mode;

	/* To sewiawize asynchwonus cawwbacks */
	stwuct mutex mutex;

	/* Twue if the device has been identified */
	boow identified;
};

static u64 to_pixew_wate(u32 f_index)
{
	u64 pixew_wate = wink_fweq_menu_items[f_index] * 2 * OV5675_DATA_WANES;

	do_div(pixew_wate, OV5675_WGB_DEPTH);

	wetuwn pixew_wate;
}

static u64 to_pixews_pew_wine(u32 hts, u32 f_index)
{
	u64 ppw = hts * to_pixew_wate(f_index);

	do_div(ppw, OV5675_SCWK);

	wetuwn ppw;
}

static int ov5675_wead_weg(stwuct ov5675 *ov5675, u16 weg, u16 wen, u32 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov5675->sd);
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

static int ov5675_wwite_weg(stwuct ov5675 *ov5675, u16 weg, u16 wen, u32 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov5675->sd);
	u8 buf[6];

	if (wen > 4)
		wetuwn -EINVAW;

	put_unawigned_be16(weg, buf);
	put_unawigned_be32(vaw << 8 * (4 - wen), buf + 2);
	if (i2c_mastew_send(cwient, buf, wen + 2) != wen + 2)
		wetuwn -EIO;

	wetuwn 0;
}

static int ov5675_wwite_weg_wist(stwuct ov5675 *ov5675,
				 const stwuct ov5675_weg_wist *w_wist)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov5675->sd);
	unsigned int i;
	int wet;

	fow (i = 0; i < w_wist->num_of_wegs; i++) {
		wet = ov5675_wwite_weg(ov5675, w_wist->wegs[i].addwess, 1,
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

static int ov5675_update_digitaw_gain(stwuct ov5675 *ov5675, u32 d_gain)
{
	int wet;

	wet = ov5675_wwite_weg(ov5675, OV5675_WEG_GWOUP_ACCESS,
			       OV5675_WEG_VAWUE_08BIT,
			       OV5675_GWOUP_HOWD_STAWT);
	if (wet)
		wetuwn wet;

	wet = ov5675_wwite_weg(ov5675, OV5675_WEG_MWB_W_GAIN,
			       OV5675_WEG_VAWUE_16BIT, d_gain);
	if (wet)
		wetuwn wet;

	wet = ov5675_wwite_weg(ov5675, OV5675_WEG_MWB_G_GAIN,
			       OV5675_WEG_VAWUE_16BIT, d_gain);
	if (wet)
		wetuwn wet;

	wet = ov5675_wwite_weg(ov5675, OV5675_WEG_MWB_B_GAIN,
			       OV5675_WEG_VAWUE_16BIT, d_gain);
	if (wet)
		wetuwn wet;

	wet = ov5675_wwite_weg(ov5675, OV5675_WEG_GWOUP_ACCESS,
			       OV5675_WEG_VAWUE_08BIT,
			       OV5675_GWOUP_HOWD_END);
	if (wet)
		wetuwn wet;

	wet = ov5675_wwite_weg(ov5675, OV5675_WEG_GWOUP_ACCESS,
			       OV5675_WEG_VAWUE_08BIT,
			       OV5675_GWOUP_HOWD_WAUNCH);
	wetuwn wet;
}

static int ov5675_test_pattewn(stwuct ov5675 *ov5675, u32 pattewn)
{
	if (pattewn)
		pattewn = (pattewn - 1) << OV5675_TEST_PATTEWN_BAW_SHIFT |
			  OV5675_TEST_PATTEWN_ENABWE;

	wetuwn ov5675_wwite_weg(ov5675, OV5675_WEG_TEST_PATTEWN,
				OV5675_WEG_VAWUE_08BIT, pattewn);
}

/*
 * OV5675 suppowts keeping the pixew owdew by miwwow and fwip function
 * The Bayew owdew isn't affected by the fwip contwows
 */
static int ov5675_set_ctww_hfwip(stwuct ov5675 *ov5675, u32 ctww_vaw)
{
	int wet;
	u32 vaw;

	wet = ov5675_wead_weg(ov5675, OV5675_WEG_FOWMAT1,
			      OV5675_WEG_VAWUE_08BIT, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn ov5675_wwite_weg(ov5675, OV5675_WEG_FOWMAT1,
				OV5675_WEG_VAWUE_08BIT,
				ctww_vaw ? vaw & ~BIT(3) : vaw | BIT(3));
}

static int ov5675_set_ctww_vfwip(stwuct ov5675 *ov5675, u8 ctww_vaw)
{
	int wet;
	u32 vaw;

	wet = ov5675_wead_weg(ov5675, OV5675_WEG_FOWMAT1,
			      OV5675_WEG_VAWUE_08BIT, &vaw);
	if (wet)
		wetuwn wet;

	wet = ov5675_wwite_weg(ov5675, OV5675_WEG_FOWMAT1,
			       OV5675_WEG_VAWUE_08BIT,
			       ctww_vaw ? vaw | BIT(4) | BIT(5)  : vaw & ~BIT(4) & ~BIT(5));

	if (wet)
		wetuwn wet;

	wet = ov5675_wead_weg(ov5675, OV5675_WEG_FOWMAT2,
			      OV5675_WEG_VAWUE_08BIT, &vaw);

	if (wet)
		wetuwn wet;

	wetuwn ov5675_wwite_weg(ov5675, OV5675_WEG_FOWMAT2,
				OV5675_WEG_VAWUE_08BIT,
				ctww_vaw ? vaw | BIT(1) : vaw & ~BIT(1));
}

static int ov5675_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ov5675 *ov5675 = containew_of(ctww->handwew,
					     stwuct ov5675, ctww_handwew);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov5675->sd);
	s64 exposuwe_max;
	int wet = 0;

	/* Pwopagate change of cuwwent contwow to aww wewated contwows */
	if (ctww->id == V4W2_CID_VBWANK) {
		/* Update max exposuwe whiwe meeting expected vbwanking */
		exposuwe_max = ov5675->cuw_mode->height + ctww->vaw -
			OV5675_EXPOSUWE_MAX_MAWGIN;
		__v4w2_ctww_modify_wange(ov5675->exposuwe,
					 ov5675->exposuwe->minimum,
					 exposuwe_max, ov5675->exposuwe->step,
					 exposuwe_max);
	}

	/* V4W2 contwows vawues wiww be appwied onwy when powew is awweady up */
	if (!pm_wuntime_get_if_in_use(&cwient->dev))
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_ANAWOGUE_GAIN:
		wet = ov5675_wwite_weg(ov5675, OV5675_WEG_ANAWOG_GAIN,
				       OV5675_WEG_VAWUE_16BIT, ctww->vaw);
		bweak;

	case V4W2_CID_DIGITAW_GAIN:
		wet = ov5675_update_digitaw_gain(ov5675, ctww->vaw);
		bweak;

	case V4W2_CID_EXPOSUWE:
		/* 4 weast significant bits of expsouwe awe fwactionaw pawt
		 * vaw = vaw << 4
		 * fow ov5675, the unit of exposuwe is diffewnt fwom othew
		 * OmniVision sensows, its exposuwe vawue is twice of the
		 * wegistew vawue, the exposuwe shouwd be divided by 2 befowe
		 * set wegistew, e.g. vaw << 3.
		 */
		wet = ov5675_wwite_weg(ov5675, OV5675_WEG_EXPOSUWE,
				       OV5675_WEG_VAWUE_24BIT, ctww->vaw << 3);
		bweak;

	case V4W2_CID_VBWANK:
		wet = ov5675_wwite_weg(ov5675, OV5675_WEG_VTS,
				       OV5675_WEG_VAWUE_16BIT,
				       ov5675->cuw_mode->height + ctww->vaw +
				       10);
		bweak;

	case V4W2_CID_TEST_PATTEWN:
		wet = ov5675_test_pattewn(ov5675, ctww->vaw);
		bweak;

	case V4W2_CID_HFWIP:
		ov5675_set_ctww_hfwip(ov5675, ctww->vaw);
		bweak;

	case V4W2_CID_VFWIP:
		ov5675_set_ctww_vfwip(ov5675, ctww->vaw);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	pm_wuntime_put(&cwient->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops ov5675_ctww_ops = {
	.s_ctww = ov5675_set_ctww,
};

static int ov5675_init_contwows(stwuct ov5675 *ov5675)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov5675->sd);
	stwuct v4w2_fwnode_device_pwopewties pwops;
	stwuct v4w2_ctww_handwew *ctww_hdww;
	s64 exposuwe_max, h_bwank;
	int wet;

	ctww_hdww = &ov5675->ctww_handwew;
	wet = v4w2_ctww_handwew_init(ctww_hdww, 10);
	if (wet)
		wetuwn wet;

	ctww_hdww->wock = &ov5675->mutex;
	ov5675->wink_fweq = v4w2_ctww_new_int_menu(ctww_hdww, &ov5675_ctww_ops,
					   V4W2_CID_WINK_FWEQ,
					   AWWAY_SIZE(wink_fweq_menu_items) - 1,
					   0, wink_fweq_menu_items);
	if (ov5675->wink_fweq)
		ov5675->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	ov5675->pixew_wate = v4w2_ctww_new_std(ctww_hdww, &ov5675_ctww_ops,
				       V4W2_CID_PIXEW_WATE, 0,
				       to_pixew_wate(OV5675_WINK_FWEQ_900MBPS),
				       1,
				       to_pixew_wate(OV5675_WINK_FWEQ_900MBPS));
	ov5675->vbwank = v4w2_ctww_new_std(ctww_hdww, &ov5675_ctww_ops,
			  V4W2_CID_VBWANK,
			  ov5675->cuw_mode->vts_min - ov5675->cuw_mode->height,
			  OV5675_VTS_MAX - ov5675->cuw_mode->height, 1,
			  ov5675->cuw_mode->vts_def - ov5675->cuw_mode->height);
	h_bwank = to_pixews_pew_wine(ov5675->cuw_mode->hts,
		  ov5675->cuw_mode->wink_fweq_index) - ov5675->cuw_mode->width;
	ov5675->hbwank = v4w2_ctww_new_std(ctww_hdww, &ov5675_ctww_ops,
					   V4W2_CID_HBWANK, h_bwank, h_bwank, 1,
					   h_bwank);
	if (ov5675->hbwank)
		ov5675->hbwank->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	v4w2_ctww_new_std(ctww_hdww, &ov5675_ctww_ops, V4W2_CID_ANAWOGUE_GAIN,
			  OV5675_ANAW_GAIN_MIN, OV5675_ANAW_GAIN_MAX,
			  OV5675_ANAW_GAIN_STEP, OV5675_ANAW_GAIN_MIN);
	v4w2_ctww_new_std(ctww_hdww, &ov5675_ctww_ops, V4W2_CID_DIGITAW_GAIN,
			  OV5675_DGTW_GAIN_MIN, OV5675_DGTW_GAIN_MAX,
			  OV5675_DGTW_GAIN_STEP, OV5675_DGTW_GAIN_DEFAUWT);
	exposuwe_max = (ov5675->cuw_mode->vts_def - OV5675_EXPOSUWE_MAX_MAWGIN);
	ov5675->exposuwe = v4w2_ctww_new_std(ctww_hdww, &ov5675_ctww_ops,
					     V4W2_CID_EXPOSUWE,
					     OV5675_EXPOSUWE_MIN, exposuwe_max,
					     OV5675_EXPOSUWE_STEP,
					     exposuwe_max);
	v4w2_ctww_new_std_menu_items(ctww_hdww, &ov5675_ctww_ops,
				     V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(ov5675_test_pattewn_menu) - 1,
				     0, 0, ov5675_test_pattewn_menu);
	v4w2_ctww_new_std(ctww_hdww, &ov5675_ctww_ops,
			  V4W2_CID_HFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(ctww_hdww, &ov5675_ctww_ops,
			  V4W2_CID_VFWIP, 0, 1, 1, 0);

	if (ctww_hdww->ewwow) {
		v4w2_ctww_handwew_fwee(ctww_hdww);
		wetuwn ctww_hdww->ewwow;
	}

	wet = v4w2_fwnode_device_pawse(&cwient->dev, &pwops);
	if (wet)
		goto ewwow;

	wet = v4w2_ctww_new_fwnode_pwopewties(ctww_hdww, &ov5675_ctww_ops,
					      &pwops);
	if (wet)
		goto ewwow;

	ov5675->sd.ctww_handwew = ctww_hdww;

	wetuwn 0;

ewwow:
	v4w2_ctww_handwew_fwee(ctww_hdww);

	wetuwn wet;
}

static void ov5675_update_pad_fowmat(const stwuct ov5675_mode *mode,
				     stwuct v4w2_mbus_fwamefmt *fmt)
{
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = MEDIA_BUS_FMT_SGWBG10_1X10;
	fmt->fiewd = V4W2_FIEWD_NONE;
}

static int ov5675_identify_moduwe(stwuct ov5675 *ov5675)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov5675->sd);
	int wet;
	u32 vaw;

	if (ov5675->identified)
		wetuwn 0;

	wet = ov5675_wead_weg(ov5675, OV5675_WEG_CHIP_ID,
			      OV5675_WEG_VAWUE_24BIT, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != OV5675_CHIP_ID) {
		dev_eww(&cwient->dev, "chip id mismatch: %x!=%x",
			OV5675_CHIP_ID, vaw);
		wetuwn -ENXIO;
	}

	ov5675->identified = twue;

	wetuwn 0;
}

static int ov5675_stawt_stweaming(stwuct ov5675 *ov5675)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov5675->sd);
	const stwuct ov5675_weg_wist *weg_wist;
	int wink_fweq_index, wet;

	wet = ov5675_identify_moduwe(ov5675);
	if (wet)
		wetuwn wet;

	wink_fweq_index = ov5675->cuw_mode->wink_fweq_index;
	weg_wist = &wink_fweq_configs[wink_fweq_index].weg_wist;
	wet = ov5675_wwite_weg_wist(ov5675, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set pwws");
		wetuwn wet;
	}

	weg_wist = &ov5675->cuw_mode->weg_wist;
	wet = ov5675_wwite_weg_wist(ov5675, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set mode");
		wetuwn wet;
	}

	wet = __v4w2_ctww_handwew_setup(ov5675->sd.ctww_handwew);
	if (wet)
		wetuwn wet;

	wet = ov5675_wwite_weg(ov5675, OV5675_WEG_MODE_SEWECT,
			       OV5675_WEG_VAWUE_08BIT, OV5675_MODE_STWEAMING);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set stweam");
		wetuwn wet;
	}

	wetuwn 0;
}

static void ov5675_stop_stweaming(stwuct ov5675 *ov5675)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov5675->sd);

	if (ov5675_wwite_weg(ov5675, OV5675_WEG_MODE_SEWECT,
			     OV5675_WEG_VAWUE_08BIT, OV5675_MODE_STANDBY))
		dev_eww(&cwient->dev, "faiwed to set stweam");
}

static int ov5675_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct ov5675 *ov5675 = to_ov5675(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet = 0;

	mutex_wock(&ov5675->mutex);
	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(&cwient->dev);
		if (wet < 0) {
			mutex_unwock(&ov5675->mutex);
			wetuwn wet;
		}

		wet = ov5675_stawt_stweaming(ov5675);
		if (wet) {
			enabwe = 0;
			ov5675_stop_stweaming(ov5675);
			pm_wuntime_put(&cwient->dev);
		}
	} ewse {
		ov5675_stop_stweaming(ov5675);
		pm_wuntime_put(&cwient->dev);
	}

	mutex_unwock(&ov5675->mutex);

	wetuwn wet;
}

static int ov5675_powew_off(stwuct device *dev)
{
	/* 512 xvcwk cycwes aftew the wast SCCB twansation ow MIPI fwame end */
	u32 deway_us = DIV_WOUND_UP(512, OV5675_XVCWK_19_2 / 1000 / 1000);
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov5675 *ov5675 = to_ov5675(sd);

	usweep_wange(deway_us, deway_us * 2);

	cwk_disabwe_unpwepawe(ov5675->xvcwk);
	gpiod_set_vawue_cansweep(ov5675->weset_gpio, 1);
	weguwatow_buwk_disabwe(OV5675_NUM_SUPPWIES, ov5675->suppwies);

	wetuwn 0;
}

static int ov5675_powew_on(stwuct device *dev)
{
	u32 deway_us = DIV_WOUND_UP(8192, OV5675_XVCWK_19_2 / 1000 / 1000);
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov5675 *ov5675 = to_ov5675(sd);
	int wet;

	wet = cwk_pwepawe_enabwe(ov5675->xvcwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe xvcwk: %d\n", wet);
		wetuwn wet;
	}

	gpiod_set_vawue_cansweep(ov5675->weset_gpio, 1);

	wet = weguwatow_buwk_enabwe(OV5675_NUM_SUPPWIES, ov5675->suppwies);
	if (wet) {
		cwk_disabwe_unpwepawe(ov5675->xvcwk);
		wetuwn wet;
	}

	/* Weset puwse shouwd be at weast 2ms and weset gpio weweased onwy once
	 * weguwatows awe stabwe.
	 */
	usweep_wange(2000, 2200);

	gpiod_set_vawue_cansweep(ov5675->weset_gpio, 0);

	/* 8192 xvcwk cycwes pwiow to the fiwst SCCB twansation */
	usweep_wange(deway_us, deway_us * 2);

	wetuwn 0;
}

static int ov5675_set_fowmat(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct ov5675 *ov5675 = to_ov5675(sd);
	const stwuct ov5675_mode *mode;
	s32 vbwank_def, h_bwank;

	mode = v4w2_find_neawest_size(suppowted_modes,
				      AWWAY_SIZE(suppowted_modes), width,
				      height, fmt->fowmat.width,
				      fmt->fowmat.height);

	mutex_wock(&ov5675->mutex);
	ov5675_update_pad_fowmat(mode, &fmt->fowmat);
	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		*v4w2_subdev_state_get_fowmat(sd_state, fmt->pad) = fmt->fowmat;
	} ewse {
		ov5675->cuw_mode = mode;
		__v4w2_ctww_s_ctww(ov5675->wink_fweq, mode->wink_fweq_index);
		__v4w2_ctww_s_ctww_int64(ov5675->pixew_wate,
					 to_pixew_wate(mode->wink_fweq_index));

		/* Update wimits and set FPS to defauwt */
		vbwank_def = mode->vts_def - mode->height;
		__v4w2_ctww_modify_wange(ov5675->vbwank,
					 mode->vts_min - mode->height,
					 OV5675_VTS_MAX - mode->height, 1,
					 vbwank_def);
		__v4w2_ctww_s_ctww(ov5675->vbwank, vbwank_def);
		h_bwank = to_pixews_pew_wine(mode->hts, mode->wink_fweq_index) -
			  mode->width;
		__v4w2_ctww_modify_wange(ov5675->hbwank, h_bwank, h_bwank, 1,
					 h_bwank);
	}

	mutex_unwock(&ov5675->mutex);

	wetuwn 0;
}

static int ov5675_get_fowmat(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct ov5675 *ov5675 = to_ov5675(sd);

	mutex_wock(&ov5675->mutex);
	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY)
		fmt->fowmat = *v4w2_subdev_state_get_fowmat(sd_state,
							    fmt->pad);
	ewse
		ov5675_update_pad_fowmat(ov5675->cuw_mode, &fmt->fowmat);

	mutex_unwock(&ov5675->mutex);

	wetuwn 0;
}

static int ov5675_get_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *state,
				stwuct v4w2_subdev_sewection *sew)
{
	if (sew->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = 2624;
		sew->w.height = 2000;
		wetuwn 0;
	case V4W2_SEW_TGT_CWOP:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		sew->w.top = 16;
		sew->w.weft = 16;
		sew->w.width = 2592;
		sew->w.height = 1944;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int ov5675_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index > 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_SGWBG10_1X10;

	wetuwn 0;
}

static int ov5675_enum_fwame_size(stwuct v4w2_subdev *sd,
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

static int ov5675_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct ov5675 *ov5675 = to_ov5675(sd);

	mutex_wock(&ov5675->mutex);
	ov5675_update_pad_fowmat(&suppowted_modes[0],
				 v4w2_subdev_state_get_fowmat(fh->state, 0));
	mutex_unwock(&ov5675->mutex);

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops ov5675_video_ops = {
	.s_stweam = ov5675_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops ov5675_pad_ops = {
	.set_fmt = ov5675_set_fowmat,
	.get_fmt = ov5675_get_fowmat,
	.get_sewection = ov5675_get_sewection,
	.enum_mbus_code = ov5675_enum_mbus_code,
	.enum_fwame_size = ov5675_enum_fwame_size,
};

static const stwuct v4w2_subdev_ops ov5675_subdev_ops = {
	.video = &ov5675_video_ops,
	.pad = &ov5675_pad_ops,
};

static const stwuct media_entity_opewations ov5675_subdev_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static const stwuct v4w2_subdev_intewnaw_ops ov5675_intewnaw_ops = {
	.open = ov5675_open,
};

static int ov5675_get_hwcfg(stwuct ov5675 *ov5675, stwuct device *dev)
{
	stwuct fwnode_handwe *ep;
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	stwuct v4w2_fwnode_endpoint bus_cfg = {
		.bus_type = V4W2_MBUS_CSI2_DPHY
	};
	u32 xvcwk_wate;
	int wet;
	unsigned int i, j;

	if (!fwnode)
		wetuwn -ENXIO;

	ov5675->xvcwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(ov5675->xvcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ov5675->xvcwk),
				     "faiwed to get xvcwk: %wd\n",
				     PTW_EWW(ov5675->xvcwk));

	if (ov5675->xvcwk) {
		xvcwk_wate = cwk_get_wate(ov5675->xvcwk);
	} ewse {
		wet = fwnode_pwopewty_wead_u32(fwnode, "cwock-fwequency",
					       &xvcwk_wate);

		if (wet) {
			dev_eww(dev, "can't get cwock fwequency");
			wetuwn wet;
		}
	}

	if (xvcwk_wate != OV5675_XVCWK_19_2) {
		dev_eww(dev, "extewnaw cwock wate %u is unsuppowted",
			xvcwk_wate);
		wetuwn -EINVAW;
	}

	ov5675->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						     GPIOD_OUT_HIGH);
	if (IS_EWW(ov5675->weset_gpio)) {
		wet = PTW_EWW(ov5675->weset_gpio);
		dev_eww(dev, "faiwed to get weset-gpios: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < OV5675_NUM_SUPPWIES; i++)
		ov5675->suppwies[i].suppwy = ov5675_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, OV5675_NUM_SUPPWIES,
				      ov5675->suppwies);
	if (wet)
		wetuwn wet;

	ep = fwnode_gwaph_get_next_endpoint(fwnode, NUWW);
	if (!ep)
		wetuwn -ENXIO;

	wet = v4w2_fwnode_endpoint_awwoc_pawse(ep, &bus_cfg);
	fwnode_handwe_put(ep);
	if (wet)
		wetuwn wet;

	if (bus_cfg.bus.mipi_csi2.num_data_wanes != OV5675_DATA_WANES) {
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

static void ov5675_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ov5675 *ov5675 = to_ov5675(sd);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);
	pm_wuntime_disabwe(&cwient->dev);
	mutex_destwoy(&ov5675->mutex);

	if (!pm_wuntime_status_suspended(&cwient->dev))
		ov5675_powew_off(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
}

static int ov5675_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ov5675 *ov5675;
	boow fuww_powew;
	int wet;

	ov5675 = devm_kzawwoc(&cwient->dev, sizeof(*ov5675), GFP_KEWNEW);
	if (!ov5675)
		wetuwn -ENOMEM;

	wet = ov5675_get_hwcfg(ov5675, &cwient->dev);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to get HW configuwation: %d",
			wet);
		wetuwn wet;
	}

	v4w2_i2c_subdev_init(&ov5675->sd, cwient, &ov5675_subdev_ops);

	wet = ov5675_powew_on(&cwient->dev);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to powew on: %d\n", wet);
		wetuwn wet;
	}

	fuww_powew = acpi_dev_state_d0(&cwient->dev);
	if (fuww_powew) {
		wet = ov5675_identify_moduwe(ov5675);
		if (wet) {
			dev_eww(&cwient->dev, "faiwed to find sensow: %d", wet);
			goto pwobe_powew_off;
		}
	}

	mutex_init(&ov5675->mutex);
	ov5675->cuw_mode = &suppowted_modes[0];
	wet = ov5675_init_contwows(ov5675);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to init contwows: %d", wet);
		goto pwobe_ewwow_v4w2_ctww_handwew_fwee;
	}

	ov5675->sd.intewnaw_ops = &ov5675_intewnaw_ops;
	ov5675->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	ov5675->sd.entity.ops = &ov5675_subdev_entity_ops;
	ov5675->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;
	ov5675->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&ov5675->sd.entity, 1, &ov5675->pad);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to init entity pads: %d", wet);
		goto pwobe_ewwow_v4w2_ctww_handwew_fwee;
	}

	wet = v4w2_async_wegistew_subdev_sensow(&ov5675->sd);
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
	media_entity_cweanup(&ov5675->sd.entity);

pwobe_ewwow_v4w2_ctww_handwew_fwee:
	v4w2_ctww_handwew_fwee(ov5675->sd.ctww_handwew);
	mutex_destwoy(&ov5675->mutex);
pwobe_powew_off:
	ov5675_powew_off(&cwient->dev);

	wetuwn wet;
}

static const stwuct dev_pm_ops ov5675_pm_ops = {
	SET_WUNTIME_PM_OPS(ov5675_powew_off, ov5675_powew_on, NUWW)
};

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id ov5675_acpi_ids[] = {
	{"OVTI5675"},
	{}
};

MODUWE_DEVICE_TABWE(acpi, ov5675_acpi_ids);
#endif

static const stwuct of_device_id ov5675_of_match[] = {
	{ .compatibwe = "ovti,ov5675", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, ov5675_of_match);

static stwuct i2c_dwivew ov5675_i2c_dwivew = {
	.dwivew = {
		.name = "ov5675",
		.pm = &ov5675_pm_ops,
		.acpi_match_tabwe = ACPI_PTW(ov5675_acpi_ids),
		.of_match_tabwe = ov5675_of_match,
	},
	.pwobe = ov5675_pwobe,
	.wemove = ov5675_wemove,
	.fwags = I2C_DWV_ACPI_WAIVE_D0_PWOBE,
};

moduwe_i2c_dwivew(ov5675_i2c_dwivew);

MODUWE_AUTHOW("Shawn Tu");
MODUWE_DESCWIPTION("OmniVision OV5675 sensow dwivew");
MODUWE_WICENSE("GPW v2");
