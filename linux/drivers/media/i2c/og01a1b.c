// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2022 Intew Cowpowation.

#incwude <asm/unawigned.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#define OG01A1B_WEG_VAWUE_08BIT		1
#define OG01A1B_WEG_VAWUE_16BIT		2
#define OG01A1B_WEG_VAWUE_24BIT		3

#define OG01A1B_WINK_FWEQ_500MHZ	500000000UWW
#define OG01A1B_SCWK			120000000WW
#define OG01A1B_MCWK			19200000
#define OG01A1B_DATA_WANES		2
#define OG01A1B_WGB_DEPTH		10

#define OG01A1B_WEG_CHIP_ID		0x300a
#define OG01A1B_CHIP_ID			0x470141

#define OG01A1B_WEG_MODE_SEWECT		0x0100
#define OG01A1B_MODE_STANDBY		0x00
#define OG01A1B_MODE_STWEAMING		0x01

/* vewticaw-timings fwom sensow */
#define OG01A1B_WEG_VTS			0x380e
#define OG01A1B_VTS_120FPS		0x0498
#define OG01A1B_VTS_120FPS_MIN		0x0498
#define OG01A1B_VTS_MAX			0x7fff

/* howizontaw-timings fwom sensow */
#define OG01A1B_WEG_HTS			0x380c

/* Exposuwe contwows fwom sensow */
#define OG01A1B_WEG_EXPOSUWE		0x3501
#define	OG01A1B_EXPOSUWE_MIN		1
#define OG01A1B_EXPOSUWE_MAX_MAWGIN	14
#define	OG01A1B_EXPOSUWE_STEP		1

/* Anawog gain contwows fwom sensow */
#define OG01A1B_WEG_ANAWOG_GAIN		0x3508
#define	OG01A1B_ANAW_GAIN_MIN		16
#define	OG01A1B_ANAW_GAIN_MAX		248 /* Max = 15.5x */
#define	OG01A1B_ANAW_GAIN_STEP		1

/* Digitaw gain contwows fwom sensow */
#define OG01A1B_WEG_DIG_GAIN		0x350a
#define OG01A1B_DGTW_GAIN_MIN		1024
#define OG01A1B_DGTW_GAIN_MAX		16384 /* Max = 16x */
#define OG01A1B_DGTW_GAIN_STEP		1
#define OG01A1B_DGTW_GAIN_DEFAUWT	1024

/* Gwoup Access */
#define OG01A1B_WEG_GWOUP_ACCESS	0x3208
#define OG01A1B_GWOUP_HOWD_STAWT	0x0
#define OG01A1B_GWOUP_HOWD_END		0x10
#define OG01A1B_GWOUP_HOWD_WAUNCH	0xa0

/* Test Pattewn Contwow */
#define OG01A1B_WEG_TEST_PATTEWN	0x5100
#define OG01A1B_TEST_PATTEWN_ENABWE	BIT(7)
#define OG01A1B_TEST_PATTEWN_BAW_SHIFT	2

#define to_og01a1b(_sd)			containew_of(_sd, stwuct og01a1b, sd)

enum {
	OG01A1B_WINK_FWEQ_1000MBPS,
};

stwuct og01a1b_weg {
	u16 addwess;
	u8 vaw;
};

stwuct og01a1b_weg_wist {
	u32 num_of_wegs;
	const stwuct og01a1b_weg *wegs;
};

stwuct og01a1b_wink_fweq_config {
	const stwuct og01a1b_weg_wist weg_wist;
};

stwuct og01a1b_mode {
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
	const stwuct og01a1b_weg_wist weg_wist;
};

static const stwuct og01a1b_weg mipi_data_wate_1000mbps[] = {
	{0x0103, 0x01},
	{0x0303, 0x02},
	{0x0304, 0x00},
	{0x0305, 0xd2},
	{0x0323, 0x02},
	{0x0324, 0x01},
	{0x0325, 0x77},
};

static const stwuct og01a1b_weg mode_1280x1024_wegs[] = {
	{0x0300, 0x0a},
	{0x0301, 0x29},
	{0x0302, 0x31},
	{0x0303, 0x02},
	{0x0304, 0x00},
	{0x0305, 0xd2},
	{0x0306, 0x00},
	{0x0307, 0x01},
	{0x0308, 0x02},
	{0x0309, 0x00},
	{0x0310, 0x00},
	{0x0311, 0x00},
	{0x0312, 0x07},
	{0x0313, 0x00},
	{0x0314, 0x00},
	{0x0315, 0x00},
	{0x0320, 0x02},
	{0x0321, 0x01},
	{0x0322, 0x01},
	{0x0323, 0x02},
	{0x0324, 0x01},
	{0x0325, 0x77},
	{0x0326, 0xce},
	{0x0327, 0x04},
	{0x0329, 0x02},
	{0x032a, 0x04},
	{0x032b, 0x04},
	{0x032c, 0x02},
	{0x032d, 0x01},
	{0x032e, 0x00},
	{0x300d, 0x02},
	{0x300e, 0x04},
	{0x3021, 0x08},
	{0x301e, 0x03},
	{0x3103, 0x00},
	{0x3106, 0x08},
	{0x3107, 0x40},
	{0x3216, 0x01},
	{0x3217, 0x00},
	{0x3218, 0xc0},
	{0x3219, 0x55},
	{0x3500, 0x00},
	{0x3501, 0x04},
	{0x3502, 0x8a},
	{0x3506, 0x01},
	{0x3507, 0x72},
	{0x3508, 0x01},
	{0x3509, 0x00},
	{0x350a, 0x01},
	{0x350b, 0x00},
	{0x350c, 0x00},
	{0x3541, 0x00},
	{0x3542, 0x40},
	{0x3605, 0xe0},
	{0x3606, 0x41},
	{0x3614, 0x20},
	{0x3620, 0x0b},
	{0x3630, 0x07},
	{0x3636, 0xa0},
	{0x3637, 0xf9},
	{0x3638, 0x09},
	{0x3639, 0x38},
	{0x363f, 0x09},
	{0x3640, 0x17},
	{0x3662, 0x04},
	{0x3665, 0x80},
	{0x3670, 0x68},
	{0x3674, 0x00},
	{0x3677, 0x3f},
	{0x3679, 0x00},
	{0x369f, 0x19},
	{0x36a0, 0x03},
	{0x36a2, 0x19},
	{0x36a3, 0x03},
	{0x370d, 0x66},
	{0x370f, 0x00},
	{0x3710, 0x03},
	{0x3715, 0x03},
	{0x3716, 0x03},
	{0x3717, 0x06},
	{0x3733, 0x00},
	{0x3778, 0x00},
	{0x37a8, 0x0f},
	{0x37a9, 0x01},
	{0x37aa, 0x07},
	{0x37bd, 0x1c},
	{0x37c1, 0x2f},
	{0x37c3, 0x09},
	{0x37c8, 0x1d},
	{0x37ca, 0x30},
	{0x37df, 0x00},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x05},
	{0x3805, 0x0f},
	{0x3806, 0x04},
	{0x3807, 0x0f},
	{0x3808, 0x05},
	{0x3809, 0x00},
	{0x380a, 0x04},
	{0x380b, 0x00},
	{0x380c, 0x03},
	{0x380d, 0x50},
	{0x380e, 0x04},
	{0x380f, 0x98},
	{0x3810, 0x00},
	{0x3811, 0x08},
	{0x3812, 0x00},
	{0x3813, 0x08},
	{0x3814, 0x11},
	{0x3815, 0x11},
	{0x3820, 0x40},
	{0x3821, 0x04},
	{0x3826, 0x00},
	{0x3827, 0x00},
	{0x382a, 0x08},
	{0x382b, 0x52},
	{0x382d, 0xba},
	{0x383d, 0x14},
	{0x384a, 0xa2},
	{0x3866, 0x0e},
	{0x3867, 0x07},
	{0x3884, 0x00},
	{0x3885, 0x08},
	{0x3893, 0x68},
	{0x3894, 0x2a},
	{0x3898, 0x00},
	{0x3899, 0x31},
	{0x389a, 0x04},
	{0x389b, 0x00},
	{0x389c, 0x0b},
	{0x389d, 0xad},
	{0x389f, 0x08},
	{0x38a0, 0x00},
	{0x38a1, 0x00},
	{0x38a8, 0x70},
	{0x38ac, 0xea},
	{0x38b2, 0x00},
	{0x38b3, 0x08},
	{0x38bc, 0x20},
	{0x38c4, 0x0c},
	{0x38c5, 0x3a},
	{0x38c7, 0x3a},
	{0x38e1, 0xc0},
	{0x38ec, 0x3c},
	{0x38f0, 0x09},
	{0x38f1, 0x6f},
	{0x38fe, 0x3c},
	{0x391e, 0x00},
	{0x391f, 0x00},
	{0x3920, 0xa5},
	{0x3921, 0x00},
	{0x3922, 0x00},
	{0x3923, 0x00},
	{0x3924, 0x05},
	{0x3925, 0x00},
	{0x3926, 0x00},
	{0x3927, 0x00},
	{0x3928, 0x1a},
	{0x3929, 0x01},
	{0x392a, 0xb4},
	{0x392b, 0x00},
	{0x392c, 0x10},
	{0x392f, 0x40},
	{0x4000, 0xcf},
	{0x4003, 0x40},
	{0x4008, 0x00},
	{0x4009, 0x07},
	{0x400a, 0x02},
	{0x400b, 0x54},
	{0x400c, 0x00},
	{0x400d, 0x07},
	{0x4010, 0xc0},
	{0x4012, 0x02},
	{0x4014, 0x04},
	{0x4015, 0x04},
	{0x4017, 0x02},
	{0x4042, 0x01},
	{0x4306, 0x04},
	{0x4307, 0x12},
	{0x4509, 0x00},
	{0x450b, 0x83},
	{0x4604, 0x68},
	{0x4608, 0x0a},
	{0x4700, 0x06},
	{0x4800, 0x64},
	{0x481b, 0x3c},
	{0x4825, 0x32},
	{0x4833, 0x18},
	{0x4837, 0x0f},
	{0x4850, 0x40},
	{0x4860, 0x00},
	{0x4861, 0xec},
	{0x4864, 0x00},
	{0x4883, 0x00},
	{0x4888, 0x90},
	{0x4889, 0x05},
	{0x488b, 0x04},
	{0x4f00, 0x04},
	{0x4f10, 0x04},
	{0x4f21, 0x01},
	{0x4f22, 0x40},
	{0x4f23, 0x44},
	{0x4f24, 0x51},
	{0x4f25, 0x41},
	{0x5000, 0x1f},
	{0x500a, 0x00},
	{0x5100, 0x00},
	{0x5111, 0x20},
	{0x3020, 0x20},
	{0x3613, 0x03},
	{0x38c9, 0x02},
	{0x5304, 0x01},
	{0x3620, 0x08},
	{0x3639, 0x58},
	{0x363a, 0x10},
	{0x3674, 0x04},
	{0x3780, 0xff},
	{0x3781, 0xff},
	{0x3782, 0x00},
	{0x3783, 0x01},
	{0x3798, 0xa3},
	{0x37aa, 0x10},
	{0x38a8, 0xf0},
	{0x38c4, 0x09},
	{0x38c5, 0xb0},
	{0x38df, 0x80},
	{0x38ff, 0x05},
	{0x4010, 0xf1},
	{0x4011, 0x70},
	{0x3667, 0x80},
	{0x4d00, 0x4a},
	{0x4d01, 0x18},
	{0x4d02, 0xbb},
	{0x4d03, 0xde},
	{0x4d04, 0x93},
	{0x4d05, 0xff},
	{0x4d09, 0x0a},
	{0x37aa, 0x16},
	{0x3606, 0x42},
	{0x3605, 0x00},
	{0x36a2, 0x17},
	{0x300d, 0x0a},
	{0x4d00, 0x4d},
	{0x4d01, 0x95},
	{0x3d8C, 0x70},
	{0x3d8d, 0xE9},
	{0x5300, 0x00},
	{0x5301, 0x10},
	{0x5302, 0x00},
	{0x5303, 0xE3},
	{0x3d88, 0x00},
	{0x3d89, 0x10},
	{0x3d8a, 0x00},
	{0x3d8b, 0xE3},
	{0x4f22, 0x00},
};

static const chaw * const og01a1b_test_pattewn_menu[] = {
	"Disabwed",
	"Standawd Cowow Baw",
	"Top-Bottom Dawkew Cowow Baw",
	"Wight-Weft Dawkew Cowow Baw",
	"Bottom-Top Dawkew Cowow Baw"
};

static const s64 wink_fweq_menu_items[] = {
	OG01A1B_WINK_FWEQ_500MHZ,
};

static const stwuct og01a1b_wink_fweq_config wink_fweq_configs[] = {
	[OG01A1B_WINK_FWEQ_1000MBPS] = {
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mipi_data_wate_1000mbps),
			.wegs = mipi_data_wate_1000mbps,
		}
	}
};

static const stwuct og01a1b_mode suppowted_modes[] = {
	{
		.width = 1280,
		.height = 1024,
		.hts = 848,
		.vts_def = OG01A1B_VTS_120FPS,
		.vts_min = OG01A1B_VTS_120FPS_MIN,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_1280x1024_wegs),
			.wegs = mode_1280x1024_wegs,
		},
		.wink_fweq_index = OG01A1B_WINK_FWEQ_1000MBPS,
	},
};

stwuct og01a1b {
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
	const stwuct og01a1b_mode *cuw_mode;

	/* To sewiawize asynchwonus cawwbacks */
	stwuct mutex mutex;
};

static u64 to_pixew_wate(u32 f_index)
{
	u64 pixew_wate = wink_fweq_menu_items[f_index] * 2 * OG01A1B_DATA_WANES;

	do_div(pixew_wate, OG01A1B_WGB_DEPTH);

	wetuwn pixew_wate;
}

static u64 to_pixews_pew_wine(u32 hts, u32 f_index)
{
	u64 ppw = hts * to_pixew_wate(f_index);

	do_div(ppw, OG01A1B_SCWK);

	wetuwn ppw;
}

static int og01a1b_wead_weg(stwuct og01a1b *og01a1b, u16 weg, u16 wen, u32 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&og01a1b->sd);
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

static int og01a1b_wwite_weg(stwuct og01a1b *og01a1b, u16 weg, u16 wen, u32 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&og01a1b->sd);
	u8 buf[6];

	if (wen > 4)
		wetuwn -EINVAW;

	put_unawigned_be16(weg, buf);
	put_unawigned_be32(vaw << 8 * (4 - wen), buf + 2);
	if (i2c_mastew_send(cwient, buf, wen + 2) != wen + 2)
		wetuwn -EIO;

	wetuwn 0;
}

static int og01a1b_wwite_weg_wist(stwuct og01a1b *og01a1b,
				  const stwuct og01a1b_weg_wist *w_wist)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&og01a1b->sd);
	unsigned int i;
	int wet;

	fow (i = 0; i < w_wist->num_of_wegs; i++) {
		wet = og01a1b_wwite_weg(og01a1b, w_wist->wegs[i].addwess, 1,
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

static int og01a1b_test_pattewn(stwuct og01a1b *og01a1b, u32 pattewn)
{
	if (pattewn)
		pattewn = (pattewn - 1) << OG01A1B_TEST_PATTEWN_BAW_SHIFT |
			  OG01A1B_TEST_PATTEWN_ENABWE;

	wetuwn og01a1b_wwite_weg(og01a1b, OG01A1B_WEG_TEST_PATTEWN,
				 OG01A1B_WEG_VAWUE_08BIT, pattewn);
}

static int og01a1b_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct og01a1b *og01a1b = containew_of(ctww->handwew,
					       stwuct og01a1b, ctww_handwew);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&og01a1b->sd);
	s64 exposuwe_max;
	int wet = 0;

	/* Pwopagate change of cuwwent contwow to aww wewated contwows */
	if (ctww->id == V4W2_CID_VBWANK) {
		/* Update max exposuwe whiwe meeting expected vbwanking */
		exposuwe_max = og01a1b->cuw_mode->height + ctww->vaw -
			       OG01A1B_EXPOSUWE_MAX_MAWGIN;
		__v4w2_ctww_modify_wange(og01a1b->exposuwe,
					 og01a1b->exposuwe->minimum,
					 exposuwe_max, og01a1b->exposuwe->step,
					 exposuwe_max);
	}

	/* V4W2 contwows vawues wiww be appwied onwy when powew is awweady up */
	if (!pm_wuntime_get_if_in_use(&cwient->dev))
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_ANAWOGUE_GAIN:
		wet = og01a1b_wwite_weg(og01a1b, OG01A1B_WEG_ANAWOG_GAIN,
					OG01A1B_WEG_VAWUE_16BIT,
					ctww->vaw << 4);
		bweak;

	case V4W2_CID_DIGITAW_GAIN:
		wet = og01a1b_wwite_weg(og01a1b, OG01A1B_WEG_DIG_GAIN,
					OG01A1B_WEG_VAWUE_24BIT,
					ctww->vaw << 6);
		bweak;

	case V4W2_CID_EXPOSUWE:
		wet = og01a1b_wwite_weg(og01a1b, OG01A1B_WEG_EXPOSUWE,
					OG01A1B_WEG_VAWUE_16BIT, ctww->vaw);
		bweak;

	case V4W2_CID_VBWANK:
		wet = og01a1b_wwite_weg(og01a1b, OG01A1B_WEG_VTS,
					OG01A1B_WEG_VAWUE_16BIT,
					og01a1b->cuw_mode->height + ctww->vaw);
		bweak;

	case V4W2_CID_TEST_PATTEWN:
		wet = og01a1b_test_pattewn(og01a1b, ctww->vaw);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	pm_wuntime_put(&cwient->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops og01a1b_ctww_ops = {
	.s_ctww = og01a1b_set_ctww,
};

static int og01a1b_init_contwows(stwuct og01a1b *og01a1b)
{
	stwuct v4w2_ctww_handwew *ctww_hdww;
	s64 exposuwe_max, h_bwank;
	int wet;

	ctww_hdww = &og01a1b->ctww_handwew;
	wet = v4w2_ctww_handwew_init(ctww_hdww, 8);
	if (wet)
		wetuwn wet;

	ctww_hdww->wock = &og01a1b->mutex;
	og01a1b->wink_fweq = v4w2_ctww_new_int_menu(ctww_hdww,
						    &og01a1b_ctww_ops,
						    V4W2_CID_WINK_FWEQ,
						    AWWAY_SIZE
						    (wink_fweq_menu_items) - 1,
						    0, wink_fweq_menu_items);
	if (og01a1b->wink_fweq)
		og01a1b->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	og01a1b->pixew_wate = v4w2_ctww_new_std(ctww_hdww, &og01a1b_ctww_ops,
						V4W2_CID_PIXEW_WATE, 0,
						to_pixew_wate
						(OG01A1B_WINK_FWEQ_1000MBPS),
						1,
						to_pixew_wate
						(OG01A1B_WINK_FWEQ_1000MBPS));
	og01a1b->vbwank = v4w2_ctww_new_std(ctww_hdww, &og01a1b_ctww_ops,
					    V4W2_CID_VBWANK,
					    og01a1b->cuw_mode->vts_min -
					    og01a1b->cuw_mode->height,
					    OG01A1B_VTS_MAX -
					    og01a1b->cuw_mode->height, 1,
					    og01a1b->cuw_mode->vts_def -
					    og01a1b->cuw_mode->height);
	h_bwank = to_pixews_pew_wine(og01a1b->cuw_mode->hts,
				     og01a1b->cuw_mode->wink_fweq_index) -
				     og01a1b->cuw_mode->width;
	og01a1b->hbwank = v4w2_ctww_new_std(ctww_hdww, &og01a1b_ctww_ops,
					    V4W2_CID_HBWANK, h_bwank, h_bwank,
					    1, h_bwank);
	if (og01a1b->hbwank)
		og01a1b->hbwank->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	v4w2_ctww_new_std(ctww_hdww, &og01a1b_ctww_ops, V4W2_CID_ANAWOGUE_GAIN,
			  OG01A1B_ANAW_GAIN_MIN, OG01A1B_ANAW_GAIN_MAX,
			  OG01A1B_ANAW_GAIN_STEP, OG01A1B_ANAW_GAIN_MIN);
	v4w2_ctww_new_std(ctww_hdww, &og01a1b_ctww_ops, V4W2_CID_DIGITAW_GAIN,
			  OG01A1B_DGTW_GAIN_MIN, OG01A1B_DGTW_GAIN_MAX,
			  OG01A1B_DGTW_GAIN_STEP, OG01A1B_DGTW_GAIN_DEFAUWT);
	exposuwe_max = (og01a1b->cuw_mode->vts_def -
			OG01A1B_EXPOSUWE_MAX_MAWGIN);
	og01a1b->exposuwe = v4w2_ctww_new_std(ctww_hdww, &og01a1b_ctww_ops,
					      V4W2_CID_EXPOSUWE,
					      OG01A1B_EXPOSUWE_MIN,
					      exposuwe_max,
					      OG01A1B_EXPOSUWE_STEP,
					      exposuwe_max);
	v4w2_ctww_new_std_menu_items(ctww_hdww, &og01a1b_ctww_ops,
				     V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(og01a1b_test_pattewn_menu) - 1,
				     0, 0, og01a1b_test_pattewn_menu);

	if (ctww_hdww->ewwow)
		wetuwn ctww_hdww->ewwow;

	og01a1b->sd.ctww_handwew = ctww_hdww;

	wetuwn 0;
}

static void og01a1b_update_pad_fowmat(const stwuct og01a1b_mode *mode,
				      stwuct v4w2_mbus_fwamefmt *fmt)
{
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = MEDIA_BUS_FMT_SGWBG10_1X10;
	fmt->fiewd = V4W2_FIEWD_NONE;
}

static int og01a1b_stawt_stweaming(stwuct og01a1b *og01a1b)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&og01a1b->sd);
	const stwuct og01a1b_weg_wist *weg_wist;
	int wink_fweq_index, wet;

	wink_fweq_index = og01a1b->cuw_mode->wink_fweq_index;
	weg_wist = &wink_fweq_configs[wink_fweq_index].weg_wist;

	wet = og01a1b_wwite_weg_wist(og01a1b, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set pwws");
		wetuwn wet;
	}

	weg_wist = &og01a1b->cuw_mode->weg_wist;
	wet = og01a1b_wwite_weg_wist(og01a1b, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set mode");
		wetuwn wet;
	}

	wet = __v4w2_ctww_handwew_setup(og01a1b->sd.ctww_handwew);
	if (wet)
		wetuwn wet;

	wet = og01a1b_wwite_weg(og01a1b, OG01A1B_WEG_MODE_SEWECT,
				OG01A1B_WEG_VAWUE_08BIT,
				OG01A1B_MODE_STWEAMING);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set stweam");
		wetuwn wet;
	}

	wetuwn 0;
}

static void og01a1b_stop_stweaming(stwuct og01a1b *og01a1b)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&og01a1b->sd);

	if (og01a1b_wwite_weg(og01a1b, OG01A1B_WEG_MODE_SEWECT,
			      OG01A1B_WEG_VAWUE_08BIT, OG01A1B_MODE_STANDBY))
		dev_eww(&cwient->dev, "faiwed to set stweam");
}

static int og01a1b_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct og01a1b *og01a1b = to_og01a1b(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet = 0;

	mutex_wock(&og01a1b->mutex);
	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(&cwient->dev);
		if (wet) {
			mutex_unwock(&og01a1b->mutex);
			wetuwn wet;
		}

		wet = og01a1b_stawt_stweaming(og01a1b);
		if (wet) {
			enabwe = 0;
			og01a1b_stop_stweaming(og01a1b);
			pm_wuntime_put(&cwient->dev);
		}
	} ewse {
		og01a1b_stop_stweaming(og01a1b);
		pm_wuntime_put(&cwient->dev);
	}

	mutex_unwock(&og01a1b->mutex);

	wetuwn wet;
}

static int og01a1b_set_fowmat(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct og01a1b *og01a1b = to_og01a1b(sd);
	const stwuct og01a1b_mode *mode;
	s32 vbwank_def, h_bwank;

	mode = v4w2_find_neawest_size(suppowted_modes,
				      AWWAY_SIZE(suppowted_modes), width,
				      height, fmt->fowmat.width,
				      fmt->fowmat.height);

	mutex_wock(&og01a1b->mutex);
	og01a1b_update_pad_fowmat(mode, &fmt->fowmat);
	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		*v4w2_subdev_state_get_fowmat(sd_state, fmt->pad) = fmt->fowmat;
	} ewse {
		og01a1b->cuw_mode = mode;
		__v4w2_ctww_s_ctww(og01a1b->wink_fweq, mode->wink_fweq_index);
		__v4w2_ctww_s_ctww_int64(og01a1b->pixew_wate,
					 to_pixew_wate(mode->wink_fweq_index));

		/* Update wimits and set FPS to defauwt */
		vbwank_def = mode->vts_def - mode->height;
		__v4w2_ctww_modify_wange(og01a1b->vbwank,
					 mode->vts_min - mode->height,
					 OG01A1B_VTS_MAX - mode->height, 1,
					 vbwank_def);
		__v4w2_ctww_s_ctww(og01a1b->vbwank, vbwank_def);
		h_bwank = to_pixews_pew_wine(mode->hts, mode->wink_fweq_index) -
			  mode->width;
		__v4w2_ctww_modify_wange(og01a1b->hbwank, h_bwank, h_bwank, 1,
					 h_bwank);
	}

	mutex_unwock(&og01a1b->mutex);

	wetuwn 0;
}

static int og01a1b_get_fowmat(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct og01a1b *og01a1b = to_og01a1b(sd);

	mutex_wock(&og01a1b->mutex);
	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY)
		fmt->fowmat = *v4w2_subdev_state_get_fowmat(sd_state,
							    fmt->pad);
	ewse
		og01a1b_update_pad_fowmat(og01a1b->cuw_mode, &fmt->fowmat);

	mutex_unwock(&og01a1b->mutex);

	wetuwn 0;
}

static int og01a1b_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index > 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_SGWBG10_1X10;

	wetuwn 0;
}

static int og01a1b_enum_fwame_size(stwuct v4w2_subdev *sd,
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

static int og01a1b_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct og01a1b *og01a1b = to_og01a1b(sd);

	mutex_wock(&og01a1b->mutex);
	og01a1b_update_pad_fowmat(&suppowted_modes[0],
				  v4w2_subdev_state_get_fowmat(fh->state, 0));
	mutex_unwock(&og01a1b->mutex);

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops og01a1b_video_ops = {
	.s_stweam = og01a1b_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops og01a1b_pad_ops = {
	.set_fmt = og01a1b_set_fowmat,
	.get_fmt = og01a1b_get_fowmat,
	.enum_mbus_code = og01a1b_enum_mbus_code,
	.enum_fwame_size = og01a1b_enum_fwame_size,
};

static const stwuct v4w2_subdev_ops og01a1b_subdev_ops = {
	.video = &og01a1b_video_ops,
	.pad = &og01a1b_pad_ops,
};

static const stwuct media_entity_opewations og01a1b_subdev_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static const stwuct v4w2_subdev_intewnaw_ops og01a1b_intewnaw_ops = {
	.open = og01a1b_open,
};

static int og01a1b_identify_moduwe(stwuct og01a1b *og01a1b)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&og01a1b->sd);
	int wet;
	u32 vaw;

	wet = og01a1b_wead_weg(og01a1b, OG01A1B_WEG_CHIP_ID,
			       OG01A1B_WEG_VAWUE_24BIT, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != OG01A1B_CHIP_ID) {
		dev_eww(&cwient->dev, "chip id mismatch: %x!=%x",
			OG01A1B_CHIP_ID, vaw);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int og01a1b_check_hwcfg(stwuct device *dev)
{
	stwuct fwnode_handwe *ep;
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	stwuct v4w2_fwnode_endpoint bus_cfg = {
		.bus_type = V4W2_MBUS_CSI2_DPHY
	};
	u32 mcwk;
	int wet;
	unsigned int i, j;

	if (!fwnode)
		wetuwn -ENXIO;

	wet = fwnode_pwopewty_wead_u32(fwnode, "cwock-fwequency", &mcwk);

	if (wet) {
		dev_eww(dev, "can't get cwock fwequency");
		wetuwn wet;
	}

	if (mcwk != OG01A1B_MCWK) {
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

	if (bus_cfg.bus.mipi_csi2.num_data_wanes != OG01A1B_DATA_WANES) {
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

static void og01a1b_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct og01a1b *og01a1b = to_og01a1b(sd);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);
	pm_wuntime_disabwe(&cwient->dev);
	mutex_destwoy(&og01a1b->mutex);
}

static int og01a1b_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct og01a1b *og01a1b;
	int wet;

	wet = og01a1b_check_hwcfg(&cwient->dev);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to check HW configuwation: %d",
			wet);
		wetuwn wet;
	}

	og01a1b = devm_kzawwoc(&cwient->dev, sizeof(*og01a1b), GFP_KEWNEW);
	if (!og01a1b)
		wetuwn -ENOMEM;

	v4w2_i2c_subdev_init(&og01a1b->sd, cwient, &og01a1b_subdev_ops);
	wet = og01a1b_identify_moduwe(og01a1b);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to find sensow: %d", wet);
		wetuwn wet;
	}

	mutex_init(&og01a1b->mutex);
	og01a1b->cuw_mode = &suppowted_modes[0];
	wet = og01a1b_init_contwows(og01a1b);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to init contwows: %d", wet);
		goto pwobe_ewwow_v4w2_ctww_handwew_fwee;
	}

	og01a1b->sd.intewnaw_ops = &og01a1b_intewnaw_ops;
	og01a1b->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	og01a1b->sd.entity.ops = &og01a1b_subdev_entity_ops;
	og01a1b->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;
	og01a1b->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&og01a1b->sd.entity, 1, &og01a1b->pad);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to init entity pads: %d", wet);
		goto pwobe_ewwow_v4w2_ctww_handwew_fwee;
	}

	wet = v4w2_async_wegistew_subdev_sensow(&og01a1b->sd);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to wegistew V4W2 subdev: %d",
			wet);
		goto pwobe_ewwow_media_entity_cweanup;
	}

	/*
	 * Device is awweady tuwned on by i2c-cowe with ACPI domain PM.
	 * Enabwe wuntime PM and tuwn off the device.
	 */
	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_idwe(&cwient->dev);

	wetuwn 0;

pwobe_ewwow_media_entity_cweanup:
	media_entity_cweanup(&og01a1b->sd.entity);

pwobe_ewwow_v4w2_ctww_handwew_fwee:
	v4w2_ctww_handwew_fwee(og01a1b->sd.ctww_handwew);
	mutex_destwoy(&og01a1b->mutex);

	wetuwn wet;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id og01a1b_acpi_ids[] = {
	{"OVTI01AC"},
	{}
};

MODUWE_DEVICE_TABWE(acpi, og01a1b_acpi_ids);
#endif

static stwuct i2c_dwivew og01a1b_i2c_dwivew = {
	.dwivew = {
		.name = "og01a1b",
		.acpi_match_tabwe = ACPI_PTW(og01a1b_acpi_ids),
	},
	.pwobe = og01a1b_pwobe,
	.wemove = og01a1b_wemove,
};

moduwe_i2c_dwivew(og01a1b_i2c_dwivew);

MODUWE_AUTHOW("Shawn Tu");
MODUWE_DESCWIPTION("OmniVision OG01A1B sensow dwivew");
MODUWE_WICENSE("GPW v2");
