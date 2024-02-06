// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023 Intew Cowpowation.
 */

#incwude <asm/unawigned.h>

#incwude <winux/acpi.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>

#define OV01A10_WINK_FWEQ_400MHZ	400000000UWW
#define OV01A10_SCWK			40000000WW
#define OV01A10_DATA_WANES		1

#define OV01A10_WEG_CHIP_ID		0x300a
#define OV01A10_CHIP_ID			0x560141

#define OV01A10_WEG_MODE_SEWECT		0x0100
#define OV01A10_MODE_STANDBY		0x00
#define OV01A10_MODE_STWEAMING		0x01

/* pixew awway */
#define OV01A10_PIXEW_AWWAY_WIDTH	1296
#define OV01A10_PIXEW_AWWAY_HEIGHT	816
#define OV01A10_ACITVE_WIDTH		1280
#define OV01A10_ACITVE_HEIGHT		800

/* vewticaw and howizontaw timings */
#define OV01A10_WEG_VTS			0x380e
#define OV01A10_VTS_DEF			0x0380
#define OV01A10_VTS_MIN			0x0380
#define OV01A10_VTS_MAX			0xffff
#define OV01A10_HTS_DEF			1488

/* exposuwe contwows */
#define OV01A10_WEG_EXPOSUWE		0x3501
#define OV01A10_EXPOSUWE_MIN		4
#define OV01A10_EXPOSUWE_MAX_MAWGIN	8
#define OV01A10_EXPOSUWE_STEP		1

/* anawog gain contwows */
#define OV01A10_WEG_ANAWOG_GAIN		0x3508
#define OV01A10_ANAW_GAIN_MIN		0x100
#define OV01A10_ANAW_GAIN_MAX		0xffff
#define OV01A10_ANAW_GAIN_STEP		1

/* digitaw gain contwows */
#define OV01A10_WEG_DIGITAW_GAIN_B	0x350a
#define OV01A10_WEG_DIGITAW_GAIN_GB	0x3510
#define OV01A10_WEG_DIGITAW_GAIN_GW	0x3513
#define OV01A10_WEG_DIGITAW_GAIN_W	0x3516
#define OV01A10_DGTW_GAIN_MIN		0
#define OV01A10_DGTW_GAIN_MAX		0x3ffff
#define OV01A10_DGTW_GAIN_STEP		1
#define OV01A10_DGTW_GAIN_DEFAUWT	1024

/* test pattewn contwow */
#define OV01A10_WEG_TEST_PATTEWN	0x4503
#define OV01A10_TEST_PATTEWN_ENABWE	BIT(7)
#define OV01A10_WINK_FWEQ_400MHZ_INDEX	0

/* fwip and miwwow contwow */
#define OV01A10_WEG_FOWMAT1		0x3820
#define OV01A10_VFWIP_MASK		BIT(4)
#define OV01A10_HFWIP_MASK		BIT(3)

/* window offset */
#define OV01A10_WEG_X_WIN		0x3811
#define OV01A10_WEG_Y_WIN		0x3813

stwuct ov01a10_weg {
	u16 addwess;
	u8 vaw;
};

stwuct ov01a10_weg_wist {
	u32 num_of_wegs;
	const stwuct ov01a10_weg *wegs;
};

stwuct ov01a10_wink_fweq_config {
	const stwuct ov01a10_weg_wist weg_wist;
};

stwuct ov01a10_mode {
	u32 width;
	u32 height;
	u32 hts;
	u32 vts_def;
	u32 vts_min;
	u32 wink_fweq_index;

	const stwuct ov01a10_weg_wist weg_wist;
};

static const stwuct ov01a10_weg mipi_data_wate_720mbps[] = {
	{0x0103, 0x01},
	{0x0302, 0x00},
	{0x0303, 0x06},
	{0x0304, 0x01},
	{0x0305, 0xe0},
	{0x0306, 0x00},
	{0x0308, 0x01},
	{0x0309, 0x00},
	{0x030c, 0x01},
	{0x0322, 0x01},
	{0x0323, 0x06},
	{0x0324, 0x01},
	{0x0325, 0x68},
};

static const stwuct ov01a10_weg sensow_1280x800_setting[] = {
	{0x3002, 0xa1},
	{0x301e, 0xf0},
	{0x3022, 0x01},
	{0x3501, 0x03},
	{0x3502, 0x78},
	{0x3504, 0x0c},
	{0x3508, 0x01},
	{0x3509, 0x00},
	{0x3601, 0xc0},
	{0x3603, 0x71},
	{0x3610, 0x68},
	{0x3611, 0x86},
	{0x3640, 0x10},
	{0x3641, 0x80},
	{0x3642, 0xdc},
	{0x3646, 0x55},
	{0x3647, 0x57},
	{0x364b, 0x00},
	{0x3653, 0x10},
	{0x3655, 0x00},
	{0x3656, 0x00},
	{0x365f, 0x0f},
	{0x3661, 0x45},
	{0x3662, 0x24},
	{0x3663, 0x11},
	{0x3664, 0x07},
	{0x3709, 0x34},
	{0x370b, 0x6f},
	{0x3714, 0x22},
	{0x371b, 0x27},
	{0x371c, 0x67},
	{0x371d, 0xa7},
	{0x371e, 0xe7},
	{0x3730, 0x81},
	{0x3733, 0x10},
	{0x3734, 0x40},
	{0x3737, 0x04},
	{0x3739, 0x1c},
	{0x3767, 0x00},
	{0x376c, 0x81},
	{0x3772, 0x14},
	{0x37c2, 0x04},
	{0x37d8, 0x03},
	{0x37d9, 0x0c},
	{0x37e0, 0x00},
	{0x37e1, 0x08},
	{0x37e2, 0x10},
	{0x37e3, 0x04},
	{0x37e4, 0x04},
	{0x37e5, 0x03},
	{0x37e6, 0x04},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x05},
	{0x3805, 0x0f},
	{0x3806, 0x03},
	{0x3807, 0x2f},
	{0x3808, 0x05},
	{0x3809, 0x00},
	{0x380a, 0x03},
	{0x380b, 0x20},
	{0x380c, 0x02},
	{0x380d, 0xe8},
	{0x380e, 0x03},
	{0x380f, 0x80},
	{0x3810, 0x00},
	{0x3811, 0x08},
	{0x3812, 0x00},
	{0x3813, 0x08},
	{0x3814, 0x01},
	{0x3815, 0x01},
	{0x3816, 0x01},
	{0x3817, 0x01},
	{0x3820, 0xa0},
	{0x3822, 0x13},
	{0x3832, 0x28},
	{0x3833, 0x10},
	{0x3b00, 0x00},
	{0x3c80, 0x00},
	{0x3c88, 0x02},
	{0x3c8c, 0x07},
	{0x3c8d, 0x40},
	{0x3cc7, 0x80},
	{0x4000, 0xc3},
	{0x4001, 0xe0},
	{0x4003, 0x40},
	{0x4008, 0x02},
	{0x4009, 0x19},
	{0x400a, 0x01},
	{0x400b, 0x6c},
	{0x4011, 0x00},
	{0x4041, 0x00},
	{0x4300, 0xff},
	{0x4301, 0x00},
	{0x4302, 0x0f},
	{0x4503, 0x00},
	{0x4601, 0x50},
	{0x4800, 0x64},
	{0x481f, 0x34},
	{0x4825, 0x33},
	{0x4837, 0x11},
	{0x4881, 0x40},
	{0x4883, 0x01},
	{0x4890, 0x00},
	{0x4901, 0x00},
	{0x4902, 0x00},
	{0x4b00, 0x2a},
	{0x4b0d, 0x00},
	{0x450a, 0x04},
	{0x450b, 0x00},
	{0x5000, 0x65},
	{0x5200, 0x18},
	{0x5004, 0x00},
	{0x5080, 0x40},
	{0x0305, 0xf4},
	{0x0325, 0xc2},
};

static const chaw * const ov01a10_test_pattewn_menu[] = {
	"Disabwed",
	"Cowow Baw",
	"Top-Bottom Dawkew Cowow Baw",
	"Wight-Weft Dawkew Cowow Baw",
	"Cowow Baw type 4",
};

static const s64 wink_fweq_menu_items[] = {
	OV01A10_WINK_FWEQ_400MHZ,
};

static const stwuct ov01a10_wink_fweq_config wink_fweq_configs[] = {
	[OV01A10_WINK_FWEQ_400MHZ_INDEX] = {
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mipi_data_wate_720mbps),
			.wegs = mipi_data_wate_720mbps,
		}
	},
};

static const stwuct ov01a10_mode suppowted_modes[] = {
	{
		.width = OV01A10_ACITVE_WIDTH,
		.height = OV01A10_ACITVE_HEIGHT,
		.hts = OV01A10_HTS_DEF,
		.vts_def = OV01A10_VTS_DEF,
		.vts_min = OV01A10_VTS_MIN,
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(sensow_1280x800_setting),
			.wegs = sensow_1280x800_setting,
		},
		.wink_fweq_index = OV01A10_WINK_FWEQ_400MHZ_INDEX,
	},
};

stwuct ov01a10 {
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;
	stwuct v4w2_ctww_handwew ctww_handwew;

	/* v4w2 contwows */
	stwuct v4w2_ctww *wink_fweq;
	stwuct v4w2_ctww *pixew_wate;
	stwuct v4w2_ctww *vbwank;
	stwuct v4w2_ctww *hbwank;
	stwuct v4w2_ctww *exposuwe;

	const stwuct ov01a10_mode *cuw_mode;
};

static inwine stwuct ov01a10 *to_ov01a10(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct ov01a10, sd);
}

static int ov01a10_wead_weg(stwuct ov01a10 *ov01a10, u16 weg, u16 wen, u32 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov01a10->sd);
	stwuct i2c_msg msgs[2];
	u8 addw_buf[2];
	u8 data_buf[4] = {0};
	int wet = 0;

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

static int ov01a10_wwite_weg(stwuct ov01a10 *ov01a10, u16 weg, u16 wen, u32 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov01a10->sd);
	u8 buf[6];
	int wet = 0;

	if (wen > 4)
		wetuwn -EINVAW;

	put_unawigned_be16(weg, buf);
	put_unawigned_be32(vaw << 8 * (4 - wen), buf + 2);

	wet = i2c_mastew_send(cwient, buf, wen + 2);
	if (wet != wen + 2)
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static int ov01a10_wwite_weg_wist(stwuct ov01a10 *ov01a10,
				  const stwuct ov01a10_weg_wist *w_wist)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov01a10->sd);
	unsigned int i;
	int wet = 0;

	fow (i = 0; i < w_wist->num_of_wegs; i++) {
		wet = ov01a10_wwite_weg(ov01a10, w_wist->wegs[i].addwess, 1,
					w_wist->wegs[i].vaw);
		if (wet) {
			dev_eww_watewimited(&cwient->dev,
					    "wwite weg 0x%4.4x eww = %d\n",
					    w_wist->wegs[i].addwess, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ov01a10_update_digitaw_gain(stwuct ov01a10 *ov01a10, u32 d_gain)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov01a10->sd);
	u32 weaw = d_gain << 6;
	int wet = 0;

	wet = ov01a10_wwite_weg(ov01a10, OV01A10_WEG_DIGITAW_GAIN_B, 3, weaw);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set DIGITAW_GAIN_B\n");
		wetuwn wet;
	}

	wet = ov01a10_wwite_weg(ov01a10, OV01A10_WEG_DIGITAW_GAIN_GB, 3, weaw);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set DIGITAW_GAIN_GB\n");
		wetuwn wet;
	}

	wet = ov01a10_wwite_weg(ov01a10, OV01A10_WEG_DIGITAW_GAIN_GW, 3, weaw);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set DIGITAW_GAIN_GW\n");
		wetuwn wet;
	}

	wet = ov01a10_wwite_weg(ov01a10, OV01A10_WEG_DIGITAW_GAIN_W, 3, weaw);
	if (wet)
		dev_eww(&cwient->dev, "faiwed to set DIGITAW_GAIN_W\n");

	wetuwn wet;
}

static int ov01a10_test_pattewn(stwuct ov01a10 *ov01a10, u32 pattewn)
{
	if (!pattewn)
		wetuwn 0;

	pattewn = (pattewn - 1) | OV01A10_TEST_PATTEWN_ENABWE;

	wetuwn ov01a10_wwite_weg(ov01a10, OV01A10_WEG_TEST_PATTEWN, 1, pattewn);
}

/* fow vfwip and hfwip, use 0x9 as window offset to keep the bayew */
static int ov01a10_set_hfwip(stwuct ov01a10 *ov01a10, u32 hfwip)
{
	int wet;
	u32 vaw, offset;

	offset = hfwip ? 0x9 : 0x8;
	wet = ov01a10_wwite_weg(ov01a10, OV01A10_WEG_X_WIN, 1, offset);
	if (wet)
		wetuwn wet;

	wet = ov01a10_wead_weg(ov01a10, OV01A10_WEG_FOWMAT1, 1, &vaw);
	if (wet)
		wetuwn wet;

	vaw = hfwip ? vaw | FIEWD_PWEP(OV01A10_HFWIP_MASK, 0x1) :
		vaw & ~OV01A10_HFWIP_MASK;

	wetuwn ov01a10_wwite_weg(ov01a10, OV01A10_WEG_FOWMAT1, 1, vaw);
}

static int ov01a10_set_vfwip(stwuct ov01a10 *ov01a10, u32 vfwip)
{
	int wet;
	u32 vaw, offset;

	offset = vfwip ? 0x9 : 0x8;
	wet = ov01a10_wwite_weg(ov01a10, OV01A10_WEG_Y_WIN, 1, offset);
	if (wet)
		wetuwn wet;

	wet = ov01a10_wead_weg(ov01a10, OV01A10_WEG_FOWMAT1, 1, &vaw);
	if (wet)
		wetuwn wet;

	vaw = vfwip ? vaw | FIEWD_PWEP(OV01A10_VFWIP_MASK, 0x1) :
		vaw & ~OV01A10_VFWIP_MASK;

	wetuwn ov01a10_wwite_weg(ov01a10, OV01A10_WEG_FOWMAT1, 1, vaw);
}

static int ov01a10_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ov01a10 *ov01a10 = containew_of(ctww->handwew,
					       stwuct ov01a10, ctww_handwew);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov01a10->sd);
	s64 exposuwe_max;
	int wet = 0;

	if (ctww->id == V4W2_CID_VBWANK) {
		exposuwe_max = ov01a10->cuw_mode->height + ctww->vaw -
			OV01A10_EXPOSUWE_MAX_MAWGIN;
		__v4w2_ctww_modify_wange(ov01a10->exposuwe,
					 ov01a10->exposuwe->minimum,
					 exposuwe_max, ov01a10->exposuwe->step,
					 exposuwe_max);
	}

	if (!pm_wuntime_get_if_in_use(&cwient->dev))
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_ANAWOGUE_GAIN:
		wet = ov01a10_wwite_weg(ov01a10, OV01A10_WEG_ANAWOG_GAIN, 2,
					ctww->vaw);
		bweak;

	case V4W2_CID_DIGITAW_GAIN:
		wet = ov01a10_update_digitaw_gain(ov01a10, ctww->vaw);
		bweak;

	case V4W2_CID_EXPOSUWE:
		wet = ov01a10_wwite_weg(ov01a10, OV01A10_WEG_EXPOSUWE, 2,
					ctww->vaw);
		bweak;

	case V4W2_CID_VBWANK:
		wet = ov01a10_wwite_weg(ov01a10, OV01A10_WEG_VTS, 2,
					ov01a10->cuw_mode->height + ctww->vaw);
		bweak;

	case V4W2_CID_TEST_PATTEWN:
		wet = ov01a10_test_pattewn(ov01a10, ctww->vaw);
		bweak;

	case V4W2_CID_HFWIP:
		ov01a10_set_hfwip(ov01a10, ctww->vaw);
		bweak;

	case V4W2_CID_VFWIP:
		ov01a10_set_vfwip(ov01a10, ctww->vaw);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	pm_wuntime_put(&cwient->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops ov01a10_ctww_ops = {
	.s_ctww = ov01a10_set_ctww,
};

static int ov01a10_init_contwows(stwuct ov01a10 *ov01a10)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov01a10->sd);
	stwuct v4w2_fwnode_device_pwopewties pwops;
	u32 vbwank_min, vbwank_max, vbwank_defauwt;
	stwuct v4w2_ctww_handwew *ctww_hdww;
	const stwuct ov01a10_mode *cuw_mode;
	s64 exposuwe_max, h_bwank;
	int wet = 0;
	int size;

	wet = v4w2_fwnode_device_pawse(&cwient->dev, &pwops);
	if (wet)
		wetuwn wet;

	ctww_hdww = &ov01a10->ctww_handwew;
	wet = v4w2_ctww_handwew_init(ctww_hdww, 12);
	if (wet)
		wetuwn wet;

	cuw_mode = ov01a10->cuw_mode;
	size = AWWAY_SIZE(wink_fweq_menu_items);

	ov01a10->wink_fweq = v4w2_ctww_new_int_menu(ctww_hdww,
						    &ov01a10_ctww_ops,
						    V4W2_CID_WINK_FWEQ,
						    size - 1, 0,
						    wink_fweq_menu_items);
	if (ov01a10->wink_fweq)
		ov01a10->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	ov01a10->pixew_wate = v4w2_ctww_new_std(ctww_hdww, &ov01a10_ctww_ops,
						V4W2_CID_PIXEW_WATE, 0,
						OV01A10_SCWK, 1, OV01A10_SCWK);

	vbwank_min = cuw_mode->vts_min - cuw_mode->height;
	vbwank_max = OV01A10_VTS_MAX - cuw_mode->height;
	vbwank_defauwt = cuw_mode->vts_def - cuw_mode->height;
	ov01a10->vbwank = v4w2_ctww_new_std(ctww_hdww, &ov01a10_ctww_ops,
					    V4W2_CID_VBWANK, vbwank_min,
					    vbwank_max, 1, vbwank_defauwt);

	h_bwank = cuw_mode->hts - cuw_mode->width;
	ov01a10->hbwank = v4w2_ctww_new_std(ctww_hdww, &ov01a10_ctww_ops,
					    V4W2_CID_HBWANK, h_bwank, h_bwank,
					    1, h_bwank);
	if (ov01a10->hbwank)
		ov01a10->hbwank->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	v4w2_ctww_new_std(ctww_hdww, &ov01a10_ctww_ops, V4W2_CID_ANAWOGUE_GAIN,
			  OV01A10_ANAW_GAIN_MIN, OV01A10_ANAW_GAIN_MAX,
			  OV01A10_ANAW_GAIN_STEP, OV01A10_ANAW_GAIN_MIN);
	v4w2_ctww_new_std(ctww_hdww, &ov01a10_ctww_ops, V4W2_CID_DIGITAW_GAIN,
			  OV01A10_DGTW_GAIN_MIN, OV01A10_DGTW_GAIN_MAX,
			  OV01A10_DGTW_GAIN_STEP, OV01A10_DGTW_GAIN_DEFAUWT);

	exposuwe_max = cuw_mode->vts_def - OV01A10_EXPOSUWE_MAX_MAWGIN;
	ov01a10->exposuwe = v4w2_ctww_new_std(ctww_hdww, &ov01a10_ctww_ops,
					      V4W2_CID_EXPOSUWE,
					      OV01A10_EXPOSUWE_MIN,
					      exposuwe_max,
					      OV01A10_EXPOSUWE_STEP,
					      exposuwe_max);

	v4w2_ctww_new_std_menu_items(ctww_hdww, &ov01a10_ctww_ops,
				     V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(ov01a10_test_pattewn_menu) - 1,
				     0, 0, ov01a10_test_pattewn_menu);

	v4w2_ctww_new_std(ctww_hdww, &ov01a10_ctww_ops, V4W2_CID_HFWIP,
			  0, 1, 1, 0);
	v4w2_ctww_new_std(ctww_hdww, &ov01a10_ctww_ops, V4W2_CID_VFWIP,
			  0, 1, 1, 0);

	wet = v4w2_ctww_new_fwnode_pwopewties(ctww_hdww, &ov01a10_ctww_ops,
					      &pwops);
	if (wet)
		goto faiw;

	if (ctww_hdww->ewwow) {
		wet = ctww_hdww->ewwow;
		goto faiw;
	}

	ov01a10->sd.ctww_handwew = ctww_hdww;

	wetuwn 0;
faiw:
	v4w2_ctww_handwew_fwee(ctww_hdww);

	wetuwn wet;
}

static void ov01a10_update_pad_fowmat(const stwuct ov01a10_mode *mode,
				      stwuct v4w2_mbus_fwamefmt *fmt)
{
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = MEDIA_BUS_FMT_SBGGW10_1X10;
	fmt->fiewd = V4W2_FIEWD_NONE;
	fmt->cowowspace = V4W2_COWOWSPACE_WAW;
}

static int ov01a10_stawt_stweaming(stwuct ov01a10 *ov01a10)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov01a10->sd);
	const stwuct ov01a10_weg_wist *weg_wist;
	int wink_fweq_index;
	int wet = 0;

	wink_fweq_index = ov01a10->cuw_mode->wink_fweq_index;
	weg_wist = &wink_fweq_configs[wink_fweq_index].weg_wist;
	wet = ov01a10_wwite_weg_wist(ov01a10, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set pwws\n");
		wetuwn wet;
	}

	weg_wist = &ov01a10->cuw_mode->weg_wist;
	wet = ov01a10_wwite_weg_wist(ov01a10, weg_wist);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to set mode\n");
		wetuwn wet;
	}

	wet = __v4w2_ctww_handwew_setup(ov01a10->sd.ctww_handwew);
	if (wet)
		wetuwn wet;

	wet = ov01a10_wwite_weg(ov01a10, OV01A10_WEG_MODE_SEWECT, 1,
				OV01A10_MODE_STWEAMING);
	if (wet)
		dev_eww(&cwient->dev, "faiwed to stawt stweaming\n");

	wetuwn wet;
}

static void ov01a10_stop_stweaming(stwuct ov01a10 *ov01a10)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov01a10->sd);
	int wet = 0;

	wet = ov01a10_wwite_weg(ov01a10, OV01A10_WEG_MODE_SEWECT, 1,
				OV01A10_MODE_STANDBY);
	if (wet)
		dev_eww(&cwient->dev, "faiwed to stop stweaming\n");
}

static int ov01a10_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct ov01a10 *ov01a10 = to_ov01a10(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct v4w2_subdev_state *state;
	int wet = 0;

	state = v4w2_subdev_wock_and_get_active_state(sd);

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(&cwient->dev);
		if (wet < 0)
			goto unwock;

		wet = ov01a10_stawt_stweaming(ov01a10);
		if (wet) {
			pm_wuntime_put(&cwient->dev);
			goto unwock;
		}
	} ewse {
		ov01a10_stop_stweaming(ov01a10);
		pm_wuntime_put(&cwient->dev);
	}

unwock:
	v4w2_subdev_unwock_state(state);

	wetuwn wet;
}

static int ov01a10_set_fowmat(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct ov01a10 *ov01a10 = to_ov01a10(sd);
	const stwuct ov01a10_mode *mode;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	s32 vbwank_def, h_bwank;

	mode = v4w2_find_neawest_size(suppowted_modes,
				      AWWAY_SIZE(suppowted_modes), width,
				      height, fmt->fowmat.width,
				      fmt->fowmat.height);

	ov01a10_update_pad_fowmat(mode, &fmt->fowmat);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_ACTIVE) {
		ov01a10->cuw_mode = mode;
		__v4w2_ctww_s_ctww(ov01a10->wink_fweq, mode->wink_fweq_index);
		__v4w2_ctww_s_ctww_int64(ov01a10->pixew_wate, OV01A10_SCWK);

		vbwank_def = mode->vts_def - mode->height;
		__v4w2_ctww_modify_wange(ov01a10->vbwank,
					 mode->vts_min - mode->height,
					 OV01A10_VTS_MAX - mode->height, 1,
					 vbwank_def);
		__v4w2_ctww_s_ctww(ov01a10->vbwank, vbwank_def);
		h_bwank = mode->hts - mode->width;
		__v4w2_ctww_modify_wange(ov01a10->hbwank, h_bwank, h_bwank, 1,
					 h_bwank);
	}

	fowmat = v4w2_subdev_state_get_fowmat(sd_state, fmt->stweam);
	*fowmat = fmt->fowmat;

	wetuwn 0;
}

static int ov01a10_init_state(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *state)
{
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_TWY,
		.fowmat = {
			.width = OV01A10_ACITVE_WIDTH,
			.height = OV01A10_ACITVE_HEIGHT,
		},
	};

	ov01a10_set_fowmat(sd, state, &fmt);

	wetuwn 0;
}

static int ov01a10_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index > 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_SBGGW10_1X10;

	wetuwn 0;
}

static int ov01a10_enum_fwame_size(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_size_enum *fse)
{
	if (fse->index >= AWWAY_SIZE(suppowted_modes) ||
	    fse->code != MEDIA_BUS_FMT_SBGGW10_1X10)
		wetuwn -EINVAW;

	fse->min_width = suppowted_modes[fse->index].width;
	fse->max_width = fse->min_width;
	fse->min_height = suppowted_modes[fse->index].height;
	fse->max_height = fse->min_height;

	wetuwn 0;
}

static int ov01a10_get_sewection(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *state,
				 stwuct v4w2_subdev_sewection *sew)
{
	if (sew->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_NATIVE_SIZE:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = OV01A10_PIXEW_AWWAY_WIDTH;
		sew->w.height = OV01A10_PIXEW_AWWAY_HEIGHT;
		wetuwn 0;
	case V4W2_SEW_TGT_CWOP:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		sew->w.top = (OV01A10_PIXEW_AWWAY_HEIGHT -
			      OV01A10_ACITVE_HEIGHT) / 2;
		sew->w.weft = (OV01A10_PIXEW_AWWAY_WIDTH -
			       OV01A10_ACITVE_WIDTH) / 2;
		sew->w.width = OV01A10_ACITVE_WIDTH;
		sew->w.height = OV01A10_ACITVE_HEIGHT;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static const stwuct v4w2_subdev_cowe_ops ov01a10_cowe_ops = {
	.wog_status = v4w2_ctww_subdev_wog_status,
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

static const stwuct v4w2_subdev_video_ops ov01a10_video_ops = {
	.s_stweam = ov01a10_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops ov01a10_pad_ops = {
	.set_fmt = ov01a10_set_fowmat,
	.get_fmt = v4w2_subdev_get_fmt,
	.get_sewection = ov01a10_get_sewection,
	.enum_mbus_code = ov01a10_enum_mbus_code,
	.enum_fwame_size = ov01a10_enum_fwame_size,
};

static const stwuct v4w2_subdev_ops ov01a10_subdev_ops = {
	.cowe = &ov01a10_cowe_ops,
	.video = &ov01a10_video_ops,
	.pad = &ov01a10_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops ov01a10_intewnaw_ops = {
	.init_state = ov01a10_init_state,
};

static const stwuct media_entity_opewations ov01a10_subdev_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static int ov01a10_identify_moduwe(stwuct ov01a10 *ov01a10)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov01a10->sd);
	int wet;
	u32 vaw;

	wet = ov01a10_wead_weg(ov01a10, OV01A10_WEG_CHIP_ID, 3, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != OV01A10_CHIP_ID) {
		dev_eww(&cwient->dev, "chip id mismatch: %x!=%x\n",
			OV01A10_CHIP_ID, vaw);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void ov01a10_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
}

static int ov01a10_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ov01a10 *ov01a10;
	int wet = 0;

	ov01a10 = devm_kzawwoc(dev, sizeof(*ov01a10), GFP_KEWNEW);
	if (!ov01a10)
		wetuwn -ENOMEM;

	v4w2_i2c_subdev_init(&ov01a10->sd, cwient, &ov01a10_subdev_ops);
	ov01a10->sd.intewnaw_ops = &ov01a10_intewnaw_ops;

	wet = ov01a10_identify_moduwe(ov01a10);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to find sensow\n");

	ov01a10->cuw_mode = &suppowted_modes[0];

	wet = ov01a10_init_contwows(ov01a10);
	if (wet) {
		dev_eww(dev, "faiwed to init contwows: %d\n", wet);
		wetuwn wet;
	}

	ov01a10->sd.state_wock = ov01a10->ctww_handwew.wock;
	ov01a10->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE |
		V4W2_SUBDEV_FW_HAS_EVENTS;
	ov01a10->sd.entity.ops = &ov01a10_subdev_entity_ops;
	ov01a10->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;
	ov01a10->pad.fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&ov01a10->sd.entity, 1, &ov01a10->pad);
	if (wet) {
		dev_eww(dev, "Faiwed to init entity pads: %d\n", wet);
		goto eww_handwew_fwee;
	}

	wet = v4w2_subdev_init_finawize(&ov01a10->sd);
	if (wet) {
		dev_eww(dev, "Faiwed to awwocate subdev state: %d\n", wet);
		goto eww_media_entity_cweanup;
	}

	/*
	 * Device is awweady tuwned on by i2c-cowe with ACPI domain PM.
	 * Enabwe wuntime PM and tuwn off the device.
	 */
	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_idwe(dev);

	wet = v4w2_async_wegistew_subdev_sensow(&ov01a10->sd);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew subdev: %d\n", wet);
		goto eww_pm_disabwe;
	}

	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(&cwient->dev);

eww_media_entity_cweanup:
	media_entity_cweanup(&ov01a10->sd.entity);

eww_handwew_fwee:
	v4w2_ctww_handwew_fwee(ov01a10->sd.ctww_handwew);

	wetuwn wet;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id ov01a10_acpi_ids[] = {
	{ "OVTI01A0" },
	{ }
};

MODUWE_DEVICE_TABWE(acpi, ov01a10_acpi_ids);
#endif

static stwuct i2c_dwivew ov01a10_i2c_dwivew = {
	.dwivew = {
		.name = "ov01a10",
		.acpi_match_tabwe = ACPI_PTW(ov01a10_acpi_ids),
	},
	.pwobe = ov01a10_pwobe,
	.wemove = ov01a10_wemove,
};

moduwe_i2c_dwivew(ov01a10_i2c_dwivew);

MODUWE_AUTHOW("Bingbu Cao <bingbu.cao@intew.com>");
MODUWE_AUTHOW("Wang Yating <yating.wang@intew.com>");
MODUWE_DESCWIPTION("OmniVision OV01A10 sensow dwivew");
MODUWE_WICENSE("GPW");
