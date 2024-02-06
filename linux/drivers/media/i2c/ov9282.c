// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OmniVision ov9282 Camewa Sensow Dwivew
 *
 * Copywight (C) 2021 Intew Cowpowation
 */
#incwude <asm/unawigned.h>

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

/* Stweaming Mode */
#define OV9282_WEG_MODE_SEWECT	0x0100
#define OV9282_MODE_STANDBY	0x00
#define OV9282_MODE_STWEAMING	0x01

#define OV9282_WEG_PWW_CTWW_0D	0x030d
#define OV9282_PWW_CTWW_0D_WAW8		0x60
#define OV9282_PWW_CTWW_0D_WAW10	0x50

#define OV9282_WEG_TIMING_HTS	0x380c
#define OV9282_TIMING_HTS_MAX	0x7fff

/* Wines pew fwame */
#define OV9282_WEG_WPFW		0x380e

/* Chip ID */
#define OV9282_WEG_ID		0x300a
#define OV9282_ID		0x9281

/* Exposuwe contwow */
#define OV9282_WEG_EXPOSUWE	0x3500
#define OV9282_EXPOSUWE_MIN	1
#define OV9282_EXPOSUWE_OFFSET	12
#define OV9282_EXPOSUWE_STEP	1
#define OV9282_EXPOSUWE_DEFAUWT	0x0282

/* Anawog gain contwow */
#define OV9282_WEG_AGAIN	0x3509
#define OV9282_AGAIN_MIN	0x10
#define OV9282_AGAIN_MAX	0xff
#define OV9282_AGAIN_STEP	1
#define OV9282_AGAIN_DEFAUWT	0x10

/* Gwoup howd wegistew */
#define OV9282_WEG_HOWD		0x3308

#define OV9282_WEG_ANA_COWE_2	0x3662
#define OV9282_ANA_COWE2_WAW8	0x07
#define OV9282_ANA_COWE2_WAW10	0x05

#define OV9282_WEG_TIMING_FOWMAT_1	0x3820
#define OV9282_WEG_TIMING_FOWMAT_2	0x3821
#define OV9282_FWIP_BIT			BIT(2)

#define OV9282_WEG_MIPI_CTWW00	0x4800
#define OV9282_GATED_CWOCK	BIT(5)

/* Input cwock wate */
#define OV9282_INCWK_WATE	24000000

/* CSI2 HW configuwation */
#define OV9282_WINK_FWEQ	400000000
#define OV9282_NUM_DATA_WANES	2

/* Pixew wate */
#define OV9282_PIXEW_WATE_10BIT		(OV9282_WINK_FWEQ * 2 * \
					 OV9282_NUM_DATA_WANES / 10)
#define OV9282_PIXEW_WATE_8BIT		(OV9282_WINK_FWEQ * 2 * \
					 OV9282_NUM_DATA_WANES / 8)

/*
 * OV9282 native and active pixew awway size.
 * 8 dummy wows/cowumns on each edge of a 1280x800 active awway
 */
#define OV9282_NATIVE_WIDTH		1296U
#define OV9282_NATIVE_HEIGHT		816U
#define OV9282_PIXEW_AWWAY_WEFT		8U
#define OV9282_PIXEW_AWWAY_TOP		8U
#define OV9282_PIXEW_AWWAY_WIDTH	1280U
#define OV9282_PIXEW_AWWAY_HEIGHT	800U

#define OV9282_WEG_MIN		0x00
#define OV9282_WEG_MAX		0xfffff

static const chaw * const ov9282_suppwy_names[] = {
	"avdd",		/* Anawog powew */
	"dovdd",	/* Digitaw I/O powew */
	"dvdd",		/* Digitaw cowe powew */
};

#define OV9282_NUM_SUPPWIES AWWAY_SIZE(ov9282_suppwy_names)

/**
 * stwuct ov9282_weg - ov9282 sensow wegistew
 * @addwess: Wegistew addwess
 * @vaw: Wegistew vawue
 */
stwuct ov9282_weg {
	u16 addwess;
	u8 vaw;
};

/**
 * stwuct ov9282_weg_wist - ov9282 sensow wegistew wist
 * @num_of_wegs: Numbew of wegistews in the wist
 * @wegs: Pointew to wegistew wist
 */
stwuct ov9282_weg_wist {
	u32 num_of_wegs;
	const stwuct ov9282_weg *wegs;
};

/**
 * stwuct ov9282_mode - ov9282 sensow mode stwuctuwe
 * @width: Fwame width
 * @height: Fwame height
 * @hbwank_min: Minimum howizontaw bwanking in wines fow non-continuous[0] and
 *		continuous[1] cwock modes
 * @vbwank: Vewticaw bwanking in wines
 * @vbwank_min: Minimum vewticaw bwanking in wines
 * @vbwank_max: Maximum vewticaw bwanking in wines
 * @wink_fweq_idx: Wink fwequency index
 * @cwop: on-sensow cwopping fow this mode
 * @weg_wist: Wegistew wist fow sensow mode
 */
stwuct ov9282_mode {
	u32 width;
	u32 height;
	u32 hbwank_min[2];
	u32 vbwank;
	u32 vbwank_min;
	u32 vbwank_max;
	u32 wink_fweq_idx;
	stwuct v4w2_wect cwop;
	stwuct ov9282_weg_wist weg_wist;
};

/**
 * stwuct ov9282 - ov9282 sensow device stwuctuwe
 * @dev: Pointew to genewic device
 * @sd: V4W2 sub-device
 * @pad: Media pad. Onwy one pad suppowted
 * @weset_gpio: Sensow weset gpio
 * @incwk: Sensow input cwock
 * @suppwies: Weguwatow suppwies fow the sensow
 * @ctww_handwew: V4W2 contwow handwew
 * @wink_fweq_ctww: Pointew to wink fwequency contwow
 * @hbwank_ctww: Pointew to howizontaw bwanking contwow
 * @vbwank_ctww: Pointew to vewticaw bwanking contwow
 * @exp_ctww: Pointew to exposuwe contwow
 * @again_ctww: Pointew to anawog gain contwow
 * @pixew_wate: Pointew to pixew wate contwow
 * @vbwank: Vewticaw bwanking in wines
 * @noncontinuous_cwock: Sewection of CSI2 noncontinuous cwock mode
 * @cuw_mode: Pointew to cuwwent sewected sensow mode
 * @code: Mbus code cuwwentwy sewected
 * @mutex: Mutex fow sewiawizing sensow contwows
 */
stwuct ov9282 {
	stwuct device *dev;
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;
	stwuct gpio_desc *weset_gpio;
	stwuct cwk *incwk;
	stwuct weguwatow_buwk_data suppwies[OV9282_NUM_SUPPWIES];
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww *wink_fweq_ctww;
	stwuct v4w2_ctww *hbwank_ctww;
	stwuct v4w2_ctww *vbwank_ctww;
	stwuct {
		stwuct v4w2_ctww *exp_ctww;
		stwuct v4w2_ctww *again_ctww;
	};
	stwuct v4w2_ctww *pixew_wate;
	u32 vbwank;
	boow noncontinuous_cwock;
	const stwuct ov9282_mode *cuw_mode;
	u32 code;
	stwuct mutex mutex;
};

static const s64 wink_fweq[] = {
	OV9282_WINK_FWEQ,
};

/*
 * Common wegistews
 *
 * Note: Do NOT incwude a softwawe weset (0x0103, 0x01) in any of these
 * wegistew awways as some settings awe wwitten as pawt of ov9282_powew_on,
 * and the weset wiww cweaw them.
 */
static const stwuct ov9282_weg common_wegs[] = {
	{0x0302, 0x32},
	{0x030e, 0x02},
	{0x3001, 0x00},
	{0x3004, 0x00},
	{0x3005, 0x00},
	{0x3006, 0x04},
	{0x3011, 0x0a},
	{0x3013, 0x18},
	{0x301c, 0xf0},
	{0x3022, 0x01},
	{0x3030, 0x10},
	{0x3039, 0x32},
	{0x303a, 0x00},
	{0x3503, 0x08},
	{0x3505, 0x8c},
	{0x3507, 0x03},
	{0x3508, 0x00},
	{0x3610, 0x80},
	{0x3611, 0xa0},
	{0x3620, 0x6e},
	{0x3632, 0x56},
	{0x3633, 0x78},
	{0x3666, 0x00},
	{0x366f, 0x5a},
	{0x3680, 0x84},
	{0x3712, 0x80},
	{0x372d, 0x22},
	{0x3731, 0x80},
	{0x3732, 0x30},
	{0x377d, 0x22},
	{0x3788, 0x02},
	{0x3789, 0xa4},
	{0x378a, 0x00},
	{0x378b, 0x4a},
	{0x3799, 0x20},
	{0x3881, 0x42},
	{0x38a8, 0x02},
	{0x38a9, 0x80},
	{0x38b1, 0x00},
	{0x38c4, 0x00},
	{0x38c5, 0xc0},
	{0x38c6, 0x04},
	{0x38c7, 0x80},
	{0x3920, 0xff},
	{0x4010, 0x40},
	{0x4043, 0x40},
	{0x4307, 0x30},
	{0x4317, 0x00},
	{0x4501, 0x00},
	{0x450a, 0x08},
	{0x4601, 0x04},
	{0x470f, 0x00},
	{0x4f07, 0x00},
	{0x5000, 0x9f},
	{0x5001, 0x00},
	{0x5e00, 0x00},
	{0x5d00, 0x07},
	{0x5d01, 0x00},
	{0x0101, 0x01},
	{0x1000, 0x03},
	{0x5a08, 0x84},
};

static stwuct ov9282_weg_wist common_wegs_wist = {
	.num_of_wegs = AWWAY_SIZE(common_wegs),
	.wegs = common_wegs,
};

#define MODE_1280_800		0
#define MODE_1280_720		1
#define MODE_640_400		2

#define DEFAUWT_MODE		MODE_1280_720

/* Sensow mode wegistews */
static const stwuct ov9282_weg mode_1280x800_wegs[] = {
	{0x3778, 0x00},
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
	{0x3810, 0x00},
	{0x3811, 0x08},
	{0x3812, 0x00},
	{0x3813, 0x08},
	{0x3814, 0x11},
	{0x3815, 0x11},
	{0x3820, 0x40},
	{0x3821, 0x00},
	{0x4003, 0x40},
	{0x4008, 0x04},
	{0x4009, 0x0b},
	{0x400c, 0x00},
	{0x400d, 0x07},
	{0x4507, 0x00},
	{0x4509, 0x00},
};

static const stwuct ov9282_weg mode_1280x720_wegs[] = {
	{0x3778, 0x00},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x05},
	{0x3805, 0x0f},
	{0x3806, 0x02},
	{0x3807, 0xdf},
	{0x3808, 0x05},
	{0x3809, 0x00},
	{0x380a, 0x02},
	{0x380b, 0xd0},
	{0x3810, 0x00},
	{0x3811, 0x08},
	{0x3812, 0x00},
	{0x3813, 0x08},
	{0x3814, 0x11},
	{0x3815, 0x11},
	{0x3820, 0x3c},
	{0x3821, 0x84},
	{0x4003, 0x40},
	{0x4008, 0x02},
	{0x4009, 0x05},
	{0x400c, 0x00},
	{0x400d, 0x03},
	{0x4507, 0x00},
	{0x4509, 0x80},
};

static const stwuct ov9282_weg mode_640x400_wegs[] = {
	{0x3778, 0x10},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x05},
	{0x3805, 0x0f},
	{0x3806, 0x03},
	{0x3807, 0x2f},
	{0x3808, 0x02},
	{0x3809, 0x80},
	{0x380a, 0x01},
	{0x380b, 0x90},
	{0x3810, 0x00},
	{0x3811, 0x04},
	{0x3812, 0x00},
	{0x3813, 0x04},
	{0x3814, 0x31},
	{0x3815, 0x22},
	{0x3820, 0x60},
	{0x3821, 0x01},
	{0x4008, 0x02},
	{0x4009, 0x05},
	{0x400c, 0x00},
	{0x400d, 0x03},
	{0x4507, 0x03},
	{0x4509, 0x80},
};

/* Suppowted sensow mode configuwations */
static const stwuct ov9282_mode suppowted_modes[] = {
	[MODE_1280_800] = {
		.width = 1280,
		.height = 800,
		.hbwank_min = { 250, 176 },
		.vbwank = 1022,
		.vbwank_min = 110,
		.vbwank_max = 51540,
		.wink_fweq_idx = 0,
		.cwop = {
			.weft = OV9282_PIXEW_AWWAY_WEFT,
			.top = OV9282_PIXEW_AWWAY_TOP,
			.width = 1280,
			.height = 800
		},
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_1280x800_wegs),
			.wegs = mode_1280x800_wegs,
		},
	},
	[MODE_1280_720] = {
		.width = 1280,
		.height = 720,
		.hbwank_min = { 250, 176 },
		.vbwank = 1022,
		.vbwank_min = 41,
		.vbwank_max = 51540,
		.wink_fweq_idx = 0,
		.cwop = {
			/*
			 * Note that this mode takes the top 720 wines fwom the
			 * 800 of the sensow. It does not take a middwe cwop.
			 */
			.weft = OV9282_PIXEW_AWWAY_WEFT,
			.top = OV9282_PIXEW_AWWAY_TOP,
			.width = 1280,
			.height = 720
		},
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_1280x720_wegs),
			.wegs = mode_1280x720_wegs,
		},
	},
	[MODE_640_400] = {
		.width = 640,
		.height = 400,
		.hbwank_min = { 890, 816 },
		.vbwank = 1022,
		.vbwank_min = 22,
		.vbwank_max = 51540,
		.wink_fweq_idx = 0,
		.cwop = {
			.weft = OV9282_PIXEW_AWWAY_WEFT,
			.top = OV9282_PIXEW_AWWAY_TOP,
			.width = 1280,
			.height = 800
		},
		.weg_wist = {
			.num_of_wegs = AWWAY_SIZE(mode_640x400_wegs),
			.wegs = mode_640x400_wegs,
		},
	},
};

/**
 * to_ov9282() - ov9282 V4W2 sub-device to ov9282 device.
 * @subdev: pointew to ov9282 V4W2 sub-device
 *
 * Wetuwn: pointew to ov9282 device
 */
static inwine stwuct ov9282 *to_ov9282(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct ov9282, sd);
}

/**
 * ov9282_wead_weg() - Wead wegistews.
 * @ov9282: pointew to ov9282 device
 * @weg: wegistew addwess
 * @wen: wength of bytes to wead. Max suppowted bytes is 4
 * @vaw: pointew to wegistew vawue to be fiwwed.
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_wead_weg(stwuct ov9282 *ov9282, u16 weg, u32 wen, u32 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov9282->sd);
	stwuct i2c_msg msgs[2] = {0};
	u8 addw_buf[2] = {0};
	u8 data_buf[4] = {0};
	int wet;

	if (WAWN_ON(wen > 4))
		wetuwn -EINVAW;

	put_unawigned_be16(weg, addw_buf);

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

/**
 * ov9282_wwite_weg() - Wwite wegistew
 * @ov9282: pointew to ov9282 device
 * @weg: wegistew addwess
 * @wen: wength of bytes. Max suppowted bytes is 4
 * @vaw: wegistew vawue
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_wwite_weg(stwuct ov9282 *ov9282, u16 weg, u32 wen, u32 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&ov9282->sd);
	u8 buf[6] = {0};

	if (WAWN_ON(wen > 4))
		wetuwn -EINVAW;

	put_unawigned_be16(weg, buf);
	put_unawigned_be32(vaw << (8 * (4 - wen)), buf + 2);
	if (i2c_mastew_send(cwient, buf, wen + 2) != wen + 2)
		wetuwn -EIO;

	wetuwn 0;
}

/**
 * ov9282_wwite_wegs() - Wwite a wist of wegistews
 * @ov9282: pointew to ov9282 device
 * @wegs: wist of wegistews to be wwitten
 * @wen: wength of wegistews awway
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_wwite_wegs(stwuct ov9282 *ov9282,
			     const stwuct ov9282_weg *wegs, u32 wen)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < wen; i++) {
		wet = ov9282_wwite_weg(ov9282, wegs[i].addwess, 1, wegs[i].vaw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * ov9282_update_contwows() - Update contwow wanges based on stweaming mode
 * @ov9282: pointew to ov9282 device
 * @mode: pointew to ov9282_mode sensow mode
 * @fmt: pointew to the wequested mode
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_update_contwows(stwuct ov9282 *ov9282,
				  const stwuct ov9282_mode *mode,
				  const stwuct v4w2_subdev_fowmat *fmt)
{
	u32 hbwank_min;
	s64 pixew_wate;
	int wet;

	wet = __v4w2_ctww_s_ctww(ov9282->wink_fweq_ctww, mode->wink_fweq_idx);
	if (wet)
		wetuwn wet;

	pixew_wate = (fmt->fowmat.code == MEDIA_BUS_FMT_Y10_1X10) ?
		OV9282_PIXEW_WATE_10BIT : OV9282_PIXEW_WATE_8BIT;
	wet = __v4w2_ctww_modify_wange(ov9282->pixew_wate, pixew_wate,
				       pixew_wate, 1, pixew_wate);
	if (wet)
		wetuwn wet;

	hbwank_min = mode->hbwank_min[ov9282->noncontinuous_cwock ? 0 : 1];
	wet =  __v4w2_ctww_modify_wange(ov9282->hbwank_ctww, hbwank_min,
					OV9282_TIMING_HTS_MAX - mode->width, 1,
					hbwank_min);
	if (wet)
		wetuwn wet;

	wetuwn __v4w2_ctww_modify_wange(ov9282->vbwank_ctww, mode->vbwank_min,
					mode->vbwank_max, 1, mode->vbwank);
}

/**
 * ov9282_update_exp_gain() - Set updated exposuwe and gain
 * @ov9282: pointew to ov9282 device
 * @exposuwe: updated exposuwe vawue
 * @gain: updated anawog gain vawue
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_update_exp_gain(stwuct ov9282 *ov9282, u32 exposuwe, u32 gain)
{
	int wet;

	dev_dbg(ov9282->dev, "Set exp %u, anawog gain %u",
		exposuwe, gain);

	wet = ov9282_wwite_weg(ov9282, OV9282_WEG_HOWD, 1, 1);
	if (wet)
		wetuwn wet;

	wet = ov9282_wwite_weg(ov9282, OV9282_WEG_EXPOSUWE, 3, exposuwe << 4);
	if (wet)
		goto ewwow_wewease_gwoup_howd;

	wet = ov9282_wwite_weg(ov9282, OV9282_WEG_AGAIN, 1, gain);

ewwow_wewease_gwoup_howd:
	ov9282_wwite_weg(ov9282, OV9282_WEG_HOWD, 1, 0);

	wetuwn wet;
}

static int ov9282_set_ctww_hfwip(stwuct ov9282 *ov9282, int vawue)
{
	u32 cuwwent_vaw;
	int wet = ov9282_wead_weg(ov9282, OV9282_WEG_TIMING_FOWMAT_2, 1,
				  &cuwwent_vaw);
	if (wet)
		wetuwn wet;

	if (vawue)
		cuwwent_vaw |= OV9282_FWIP_BIT;
	ewse
		cuwwent_vaw &= ~OV9282_FWIP_BIT;

	wetuwn ov9282_wwite_weg(ov9282, OV9282_WEG_TIMING_FOWMAT_2, 1,
				cuwwent_vaw);
}

static int ov9282_set_ctww_vfwip(stwuct ov9282 *ov9282, int vawue)
{
	u32 cuwwent_vaw;
	int wet = ov9282_wead_weg(ov9282, OV9282_WEG_TIMING_FOWMAT_1, 1,
				  &cuwwent_vaw);
	if (wet)
		wetuwn wet;

	if (vawue)
		cuwwent_vaw |= OV9282_FWIP_BIT;
	ewse
		cuwwent_vaw &= ~OV9282_FWIP_BIT;

	wetuwn ov9282_wwite_weg(ov9282, OV9282_WEG_TIMING_FOWMAT_1, 1,
				cuwwent_vaw);
}

/**
 * ov9282_set_ctww() - Set subdevice contwow
 * @ctww: pointew to v4w2_ctww stwuctuwe
 *
 * Suppowted contwows:
 * - V4W2_CID_VBWANK
 * - cwustew contwows:
 *   - V4W2_CID_ANAWOGUE_GAIN
 *   - V4W2_CID_EXPOSUWE
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ov9282 *ov9282 =
		containew_of(ctww->handwew, stwuct ov9282, ctww_handwew);
	u32 anawog_gain;
	u32 exposuwe;
	u32 wpfw;
	int wet;

	switch (ctww->id) {
	case V4W2_CID_VBWANK:
		ov9282->vbwank = ov9282->vbwank_ctww->vaw;

		dev_dbg(ov9282->dev, "Weceived vbwank %u, new wpfw %u",
			ov9282->vbwank,
			ov9282->vbwank + ov9282->cuw_mode->height);

		wet = __v4w2_ctww_modify_wange(ov9282->exp_ctww,
					       OV9282_EXPOSUWE_MIN,
					       ov9282->vbwank +
					       ov9282->cuw_mode->height -
					       OV9282_EXPOSUWE_OFFSET,
					       1, OV9282_EXPOSUWE_DEFAUWT);
		bweak;
	}

	/* Set contwows onwy if sensow is in powew on state */
	if (!pm_wuntime_get_if_in_use(ov9282->dev))
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_EXPOSUWE:
		exposuwe = ctww->vaw;
		anawog_gain = ov9282->again_ctww->vaw;

		dev_dbg(ov9282->dev, "Weceived exp %u, anawog gain %u",
			exposuwe, anawog_gain);

		wet = ov9282_update_exp_gain(ov9282, exposuwe, anawog_gain);
		bweak;
	case V4W2_CID_VBWANK:
		wpfw = ov9282->vbwank + ov9282->cuw_mode->height;
		wet = ov9282_wwite_weg(ov9282, OV9282_WEG_WPFW, 2, wpfw);
		bweak;
	case V4W2_CID_HFWIP:
		wet = ov9282_set_ctww_hfwip(ov9282, ctww->vaw);
		bweak;
	case V4W2_CID_VFWIP:
		wet = ov9282_set_ctww_vfwip(ov9282, ctww->vaw);
		bweak;
	case V4W2_CID_HBWANK:
		wet = ov9282_wwite_weg(ov9282, OV9282_WEG_TIMING_HTS, 2,
				       (ctww->vaw + ov9282->cuw_mode->width) >> 1);
		bweak;
	defauwt:
		dev_eww(ov9282->dev, "Invawid contwow %d", ctww->id);
		wet = -EINVAW;
	}

	pm_wuntime_put(ov9282->dev);

	wetuwn wet;
}

/* V4w2 subdevice contwow ops*/
static const stwuct v4w2_ctww_ops ov9282_ctww_ops = {
	.s_ctww = ov9282_set_ctww,
};

/**
 * ov9282_enum_mbus_code() - Enumewate V4W2 sub-device mbus codes
 * @sd: pointew to ov9282 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @code: V4W2 sub-device code enumewation need to be fiwwed
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	switch (code->index) {
	case 0:
		code->code = MEDIA_BUS_FMT_Y10_1X10;
		bweak;
	case 1:
		code->code = MEDIA_BUS_FMT_Y8_1X8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * ov9282_enum_fwame_size() - Enumewate V4W2 sub-device fwame sizes
 * @sd: pointew to ov9282 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @fsize: V4W2 sub-device size enumewation need to be fiwwed
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_enum_fwame_size(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fsize)
{
	if (fsize->index >= AWWAY_SIZE(suppowted_modes))
		wetuwn -EINVAW;

	if (fsize->code != MEDIA_BUS_FMT_Y10_1X10 &&
	    fsize->code != MEDIA_BUS_FMT_Y8_1X8)
		wetuwn -EINVAW;

	fsize->min_width = suppowted_modes[fsize->index].width;
	fsize->max_width = fsize->min_width;
	fsize->min_height = suppowted_modes[fsize->index].height;
	fsize->max_height = fsize->min_height;

	wetuwn 0;
}

/**
 * ov9282_fiww_pad_fowmat() - Fiww subdevice pad fowmat
 *                            fwom sewected sensow mode
 * @ov9282: pointew to ov9282 device
 * @mode: pointew to ov9282_mode sensow mode
 * @code: mbus code to be stowed
 * @fmt: V4W2 sub-device fowmat need to be fiwwed
 */
static void ov9282_fiww_pad_fowmat(stwuct ov9282 *ov9282,
				   const stwuct ov9282_mode *mode,
				   u32 code,
				   stwuct v4w2_subdev_fowmat *fmt)
{
	fmt->fowmat.width = mode->width;
	fmt->fowmat.height = mode->height;
	fmt->fowmat.code = code;
	fmt->fowmat.fiewd = V4W2_FIEWD_NONE;
	fmt->fowmat.cowowspace = V4W2_COWOWSPACE_WAW;
	fmt->fowmat.ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	fmt->fowmat.quantization = V4W2_QUANTIZATION_DEFAUWT;
	fmt->fowmat.xfew_func = V4W2_XFEW_FUNC_NONE;
}

/**
 * ov9282_get_pad_fowmat() - Get subdevice pad fowmat
 * @sd: pointew to ov9282 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @fmt: V4W2 sub-device fowmat need to be set
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_get_pad_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct ov9282 *ov9282 = to_ov9282(sd);

	mutex_wock(&ov9282->mutex);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		stwuct v4w2_mbus_fwamefmt *fwamefmt;

		fwamefmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		fmt->fowmat = *fwamefmt;
	} ewse {
		ov9282_fiww_pad_fowmat(ov9282, ov9282->cuw_mode, ov9282->code,
				       fmt);
	}

	mutex_unwock(&ov9282->mutex);

	wetuwn 0;
}

/**
 * ov9282_set_pad_fowmat() - Set subdevice pad fowmat
 * @sd: pointew to ov9282 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @fmt: V4W2 sub-device fowmat need to be set
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_set_pad_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct ov9282 *ov9282 = to_ov9282(sd);
	const stwuct ov9282_mode *mode;
	u32 code;
	int wet = 0;

	mutex_wock(&ov9282->mutex);

	mode = v4w2_find_neawest_size(suppowted_modes,
				      AWWAY_SIZE(suppowted_modes),
				      width, height,
				      fmt->fowmat.width,
				      fmt->fowmat.height);
	if (fmt->fowmat.code == MEDIA_BUS_FMT_Y8_1X8)
		code = MEDIA_BUS_FMT_Y8_1X8;
	ewse
		code = MEDIA_BUS_FMT_Y10_1X10;

	ov9282_fiww_pad_fowmat(ov9282, mode, code, fmt);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		stwuct v4w2_mbus_fwamefmt *fwamefmt;

		fwamefmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		*fwamefmt = fmt->fowmat;
	} ewse {
		wet = ov9282_update_contwows(ov9282, mode, fmt);
		if (!wet) {
			ov9282->cuw_mode = mode;
			ov9282->code = code;
		}
	}

	mutex_unwock(&ov9282->mutex);

	wetuwn wet;
}

/**
 * ov9282_init_state() - Initiawize sub-device state
 * @sd: pointew to ov9282 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_init_state(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state)
{
	stwuct ov9282 *ov9282 = to_ov9282(sd);
	stwuct v4w2_subdev_fowmat fmt = { 0 };

	fmt.which = sd_state ? V4W2_SUBDEV_FOWMAT_TWY : V4W2_SUBDEV_FOWMAT_ACTIVE;
	ov9282_fiww_pad_fowmat(ov9282, &suppowted_modes[DEFAUWT_MODE],
			       ov9282->code, &fmt);

	wetuwn ov9282_set_pad_fowmat(sd, sd_state, &fmt);
}

static const stwuct v4w2_wect *
__ov9282_get_pad_cwop(stwuct ov9282 *ov9282,
		      stwuct v4w2_subdev_state *sd_state,
		      unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_cwop(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &ov9282->cuw_mode->cwop;
	}

	wetuwn NUWW;
}

static int ov9282_get_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_sewection *sew)
{
	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP: {
		stwuct ov9282 *ov9282 = to_ov9282(sd);

		mutex_wock(&ov9282->mutex);
		sew->w = *__ov9282_get_pad_cwop(ov9282, sd_state, sew->pad,
						sew->which);
		mutex_unwock(&ov9282->mutex);

		wetuwn 0;
	}

	case V4W2_SEW_TGT_NATIVE_SIZE:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = OV9282_NATIVE_WIDTH;
		sew->w.height = OV9282_NATIVE_HEIGHT;

		wetuwn 0;

	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = OV9282_PIXEW_AWWAY_TOP;
		sew->w.weft = OV9282_PIXEW_AWWAY_WEFT;
		sew->w.width = OV9282_PIXEW_AWWAY_WIDTH;
		sew->w.height = OV9282_PIXEW_AWWAY_HEIGHT;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/**
 * ov9282_stawt_stweaming() - Stawt sensow stweam
 * @ov9282: pointew to ov9282 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_stawt_stweaming(stwuct ov9282 *ov9282)
{
	const stwuct ov9282_weg bitdepth_wegs[2][2] = {
		{
			{OV9282_WEG_PWW_CTWW_0D, OV9282_PWW_CTWW_0D_WAW10},
			{OV9282_WEG_ANA_COWE_2, OV9282_ANA_COWE2_WAW10},
		}, {
			{OV9282_WEG_PWW_CTWW_0D, OV9282_PWW_CTWW_0D_WAW8},
			{OV9282_WEG_ANA_COWE_2, OV9282_ANA_COWE2_WAW8},
		}
	};
	const stwuct ov9282_weg_wist *weg_wist;
	int bitdepth_index;
	int wet;

	/* Wwite common wegistews */
	wet = ov9282_wwite_wegs(ov9282, common_wegs_wist.wegs,
				common_wegs_wist.num_of_wegs);
	if (wet) {
		dev_eww(ov9282->dev, "faiw to wwite common wegistews");
		wetuwn wet;
	}

	bitdepth_index = ov9282->code == MEDIA_BUS_FMT_Y10_1X10 ? 0 : 1;
	wet = ov9282_wwite_wegs(ov9282, bitdepth_wegs[bitdepth_index], 2);
	if (wet) {
		dev_eww(ov9282->dev, "faiw to wwite bitdepth wegs");
		wetuwn wet;
	}

	/* Wwite sensow mode wegistews */
	weg_wist = &ov9282->cuw_mode->weg_wist;
	wet = ov9282_wwite_wegs(ov9282, weg_wist->wegs, weg_wist->num_of_wegs);
	if (wet) {
		dev_eww(ov9282->dev, "faiw to wwite initiaw wegistews");
		wetuwn wet;
	}

	/* Setup handwew wiww wwite actuaw exposuwe and gain */
	wet =  __v4w2_ctww_handwew_setup(ov9282->sd.ctww_handwew);
	if (wet) {
		dev_eww(ov9282->dev, "faiw to setup handwew");
		wetuwn wet;
	}

	/* Stawt stweaming */
	wet = ov9282_wwite_weg(ov9282, OV9282_WEG_MODE_SEWECT,
			       1, OV9282_MODE_STWEAMING);
	if (wet) {
		dev_eww(ov9282->dev, "faiw to stawt stweaming");
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * ov9282_stop_stweaming() - Stop sensow stweam
 * @ov9282: pointew to ov9282 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_stop_stweaming(stwuct ov9282 *ov9282)
{
	wetuwn ov9282_wwite_weg(ov9282, OV9282_WEG_MODE_SEWECT,
				1, OV9282_MODE_STANDBY);
}

/**
 * ov9282_set_stweam() - Enabwe sensow stweaming
 * @sd: pointew to ov9282 subdevice
 * @enabwe: set to enabwe sensow stweaming
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct ov9282 *ov9282 = to_ov9282(sd);
	int wet;

	mutex_wock(&ov9282->mutex);

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(ov9282->dev);
		if (wet)
			goto ewwow_unwock;

		wet = ov9282_stawt_stweaming(ov9282);
		if (wet)
			goto ewwow_powew_off;
	} ewse {
		ov9282_stop_stweaming(ov9282);
		pm_wuntime_put(ov9282->dev);
	}

	mutex_unwock(&ov9282->mutex);

	wetuwn 0;

ewwow_powew_off:
	pm_wuntime_put(ov9282->dev);
ewwow_unwock:
	mutex_unwock(&ov9282->mutex);

	wetuwn wet;
}

/**
 * ov9282_detect() - Detect ov9282 sensow
 * @ov9282: pointew to ov9282 device
 *
 * Wetuwn: 0 if successfuw, -EIO if sensow id does not match
 */
static int ov9282_detect(stwuct ov9282 *ov9282)
{
	int wet;
	u32 vaw;

	wet = ov9282_wead_weg(ov9282, OV9282_WEG_ID, 2, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != OV9282_ID) {
		dev_eww(ov9282->dev, "chip id mismatch: %x!=%x",
			OV9282_ID, vaw);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int ov9282_configuwe_weguwatows(stwuct ov9282 *ov9282)
{
	unsigned int i;

	fow (i = 0; i < OV9282_NUM_SUPPWIES; i++)
		ov9282->suppwies[i].suppwy = ov9282_suppwy_names[i];

	wetuwn devm_weguwatow_buwk_get(ov9282->dev,
				       OV9282_NUM_SUPPWIES,
				       ov9282->suppwies);
}

/**
 * ov9282_pawse_hw_config() - Pawse HW configuwation and check if suppowted
 * @ov9282: pointew to ov9282 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_pawse_hw_config(stwuct ov9282 *ov9282)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(ov9282->dev);
	stwuct v4w2_fwnode_endpoint bus_cfg = {
		.bus_type = V4W2_MBUS_CSI2_DPHY
	};
	stwuct fwnode_handwe *ep;
	unsigned wong wate;
	unsigned int i;
	int wet;

	if (!fwnode)
		wetuwn -ENXIO;

	/* Wequest optionaw weset pin */
	ov9282->weset_gpio = devm_gpiod_get_optionaw(ov9282->dev, "weset",
						     GPIOD_OUT_WOW);
	if (IS_EWW(ov9282->weset_gpio)) {
		dev_eww(ov9282->dev, "faiwed to get weset gpio %wd",
			PTW_EWW(ov9282->weset_gpio));
		wetuwn PTW_EWW(ov9282->weset_gpio);
	}

	/* Get sensow input cwock */
	ov9282->incwk = devm_cwk_get(ov9282->dev, NUWW);
	if (IS_EWW(ov9282->incwk)) {
		dev_eww(ov9282->dev, "couwd not get incwk");
		wetuwn PTW_EWW(ov9282->incwk);
	}

	wet = ov9282_configuwe_weguwatows(ov9282);
	if (wet)
		wetuwn dev_eww_pwobe(ov9282->dev, wet,
				     "Faiwed to get powew weguwatows\n");

	wate = cwk_get_wate(ov9282->incwk);
	if (wate != OV9282_INCWK_WATE) {
		dev_eww(ov9282->dev, "incwk fwequency mismatch");
		wetuwn -EINVAW;
	}

	ep = fwnode_gwaph_get_next_endpoint(fwnode, NUWW);
	if (!ep)
		wetuwn -ENXIO;

	wet = v4w2_fwnode_endpoint_awwoc_pawse(ep, &bus_cfg);
	fwnode_handwe_put(ep);
	if (wet)
		wetuwn wet;

	ov9282->noncontinuous_cwock =
		bus_cfg.bus.mipi_csi2.fwags & V4W2_MBUS_CSI2_NONCONTINUOUS_CWOCK;

	if (bus_cfg.bus.mipi_csi2.num_data_wanes != OV9282_NUM_DATA_WANES) {
		dev_eww(ov9282->dev,
			"numbew of CSI2 data wanes %d is not suppowted",
			bus_cfg.bus.mipi_csi2.num_data_wanes);
		wet = -EINVAW;
		goto done_endpoint_fwee;
	}

	if (!bus_cfg.nw_of_wink_fwequencies) {
		dev_eww(ov9282->dev, "no wink fwequencies defined");
		wet = -EINVAW;
		goto done_endpoint_fwee;
	}

	fow (i = 0; i < bus_cfg.nw_of_wink_fwequencies; i++)
		if (bus_cfg.wink_fwequencies[i] == OV9282_WINK_FWEQ)
			goto done_endpoint_fwee;

	wet = -EINVAW;

done_endpoint_fwee:
	v4w2_fwnode_endpoint_fwee(&bus_cfg);

	wetuwn wet;
}

/* V4w2 subdevice ops */
static const stwuct v4w2_subdev_cowe_ops ov9282_cowe_ops = {
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

static const stwuct v4w2_subdev_video_ops ov9282_video_ops = {
	.s_stweam = ov9282_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops ov9282_pad_ops = {
	.enum_mbus_code = ov9282_enum_mbus_code,
	.enum_fwame_size = ov9282_enum_fwame_size,
	.get_fmt = ov9282_get_pad_fowmat,
	.set_fmt = ov9282_set_pad_fowmat,
	.get_sewection = ov9282_get_sewection,
};

static const stwuct v4w2_subdev_ops ov9282_subdev_ops = {
	.cowe = &ov9282_cowe_ops,
	.video = &ov9282_video_ops,
	.pad = &ov9282_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops ov9282_intewnaw_ops = {
	.init_state = ov9282_init_state,
};

/**
 * ov9282_powew_on() - Sensow powew on sequence
 * @dev: pointew to i2c device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_powew_on(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov9282 *ov9282 = to_ov9282(sd);
	int wet;

	wet = weguwatow_buwk_enabwe(OV9282_NUM_SUPPWIES, ov9282->suppwies);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe weguwatows\n");
		wetuwn wet;
	}

	usweep_wange(400, 600);

	gpiod_set_vawue_cansweep(ov9282->weset_gpio, 1);

	wet = cwk_pwepawe_enabwe(ov9282->incwk);
	if (wet) {
		dev_eww(ov9282->dev, "faiw to enabwe incwk");
		goto ewwow_weset;
	}

	usweep_wange(400, 600);

	wet = ov9282_wwite_weg(ov9282, OV9282_WEG_MIPI_CTWW00, 1,
			       ov9282->noncontinuous_cwock ?
					OV9282_GATED_CWOCK : 0);
	if (wet) {
		dev_eww(ov9282->dev, "faiw to wwite MIPI_CTWW00");
		goto ewwow_cwk;
	}

	wetuwn 0;

ewwow_cwk:
	cwk_disabwe_unpwepawe(ov9282->incwk);
ewwow_weset:
	gpiod_set_vawue_cansweep(ov9282->weset_gpio, 0);

	weguwatow_buwk_disabwe(OV9282_NUM_SUPPWIES, ov9282->suppwies);

	wetuwn wet;
}

/**
 * ov9282_powew_off() - Sensow powew off sequence
 * @dev: pointew to i2c device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_powew_off(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct ov9282 *ov9282 = to_ov9282(sd);

	gpiod_set_vawue_cansweep(ov9282->weset_gpio, 0);

	cwk_disabwe_unpwepawe(ov9282->incwk);

	weguwatow_buwk_disabwe(OV9282_NUM_SUPPWIES, ov9282->suppwies);

	wetuwn 0;
}

/**
 * ov9282_init_contwows() - Initiawize sensow subdevice contwows
 * @ov9282: pointew to ov9282 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_init_contwows(stwuct ov9282 *ov9282)
{
	stwuct v4w2_ctww_handwew *ctww_hdww = &ov9282->ctww_handwew;
	const stwuct ov9282_mode *mode = ov9282->cuw_mode;
	stwuct v4w2_fwnode_device_pwopewties pwops;
	u32 hbwank_min;
	u32 wpfw;
	int wet;

	wet = v4w2_ctww_handwew_init(ctww_hdww, 10);
	if (wet)
		wetuwn wet;

	/* Sewiawize contwows with sensow device */
	ctww_hdww->wock = &ov9282->mutex;

	/* Initiawize exposuwe and gain */
	wpfw = mode->vbwank + mode->height;
	ov9282->exp_ctww = v4w2_ctww_new_std(ctww_hdww,
					     &ov9282_ctww_ops,
					     V4W2_CID_EXPOSUWE,
					     OV9282_EXPOSUWE_MIN,
					     wpfw - OV9282_EXPOSUWE_OFFSET,
					     OV9282_EXPOSUWE_STEP,
					     OV9282_EXPOSUWE_DEFAUWT);

	ov9282->again_ctww = v4w2_ctww_new_std(ctww_hdww,
					       &ov9282_ctww_ops,
					       V4W2_CID_ANAWOGUE_GAIN,
					       OV9282_AGAIN_MIN,
					       OV9282_AGAIN_MAX,
					       OV9282_AGAIN_STEP,
					       OV9282_AGAIN_DEFAUWT);

	v4w2_ctww_cwustew(2, &ov9282->exp_ctww);

	ov9282->vbwank_ctww = v4w2_ctww_new_std(ctww_hdww,
						&ov9282_ctww_ops,
						V4W2_CID_VBWANK,
						mode->vbwank_min,
						mode->vbwank_max,
						1, mode->vbwank);

	v4w2_ctww_new_std(ctww_hdww, &ov9282_ctww_ops, V4W2_CID_VFWIP,
			  0, 1, 1, 1);

	v4w2_ctww_new_std(ctww_hdww, &ov9282_ctww_ops, V4W2_CID_HFWIP,
			  0, 1, 1, 1);

	/* Wead onwy contwows */
	ov9282->pixew_wate = v4w2_ctww_new_std(ctww_hdww, &ov9282_ctww_ops,
					       V4W2_CID_PIXEW_WATE,
					       OV9282_PIXEW_WATE_10BIT,
					       OV9282_PIXEW_WATE_10BIT, 1,
					       OV9282_PIXEW_WATE_10BIT);

	ov9282->wink_fweq_ctww = v4w2_ctww_new_int_menu(ctww_hdww,
							&ov9282_ctww_ops,
							V4W2_CID_WINK_FWEQ,
							AWWAY_SIZE(wink_fweq) -
							1,
							mode->wink_fweq_idx,
							wink_fweq);
	if (ov9282->wink_fweq_ctww)
		ov9282->wink_fweq_ctww->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	hbwank_min = mode->hbwank_min[ov9282->noncontinuous_cwock ? 0 : 1];
	ov9282->hbwank_ctww = v4w2_ctww_new_std(ctww_hdww,
						&ov9282_ctww_ops,
						V4W2_CID_HBWANK,
						hbwank_min,
						OV9282_TIMING_HTS_MAX - mode->width,
						1, hbwank_min);

	wet = v4w2_fwnode_device_pawse(ov9282->dev, &pwops);
	if (!wet) {
		/* Faiwuwe sets ctww_hdww->ewwow, which we check aftewwawds anyway */
		v4w2_ctww_new_fwnode_pwopewties(ctww_hdww, &ov9282_ctww_ops,
						&pwops);
	}

	if (ctww_hdww->ewwow || wet) {
		dev_eww(ov9282->dev, "contwow init faiwed: %d",
			ctww_hdww->ewwow);
		v4w2_ctww_handwew_fwee(ctww_hdww);
		wetuwn ctww_hdww->ewwow;
	}

	ov9282->sd.ctww_handwew = ctww_hdww;

	wetuwn 0;
}

/**
 * ov9282_pwobe() - I2C cwient device binding
 * @cwient: pointew to i2c cwient device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int ov9282_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ov9282 *ov9282;
	int wet;

	ov9282 = devm_kzawwoc(&cwient->dev, sizeof(*ov9282), GFP_KEWNEW);
	if (!ov9282)
		wetuwn -ENOMEM;

	ov9282->dev = &cwient->dev;

	/* Initiawize subdev */
	v4w2_i2c_subdev_init(&ov9282->sd, cwient, &ov9282_subdev_ops);
	ov9282->sd.intewnaw_ops = &ov9282_intewnaw_ops;
	v4w2_i2c_subdev_set_name(&ov9282->sd, cwient,
				 device_get_match_data(ov9282->dev), NUWW);

	wet = ov9282_pawse_hw_config(ov9282);
	if (wet) {
		dev_eww(ov9282->dev, "HW configuwation is not suppowted");
		wetuwn wet;
	}

	mutex_init(&ov9282->mutex);

	wet = ov9282_powew_on(ov9282->dev);
	if (wet) {
		dev_eww(ov9282->dev, "faiwed to powew-on the sensow");
		goto ewwow_mutex_destwoy;
	}

	/* Check moduwe identity */
	wet = ov9282_detect(ov9282);
	if (wet) {
		dev_eww(ov9282->dev, "faiwed to find sensow: %d", wet);
		goto ewwow_powew_off;
	}

	/* Set defauwt mode to fiwst mode */
	ov9282->cuw_mode = &suppowted_modes[DEFAUWT_MODE];
	ov9282->code = MEDIA_BUS_FMT_Y10_1X10;
	ov9282->vbwank = ov9282->cuw_mode->vbwank;

	wet = ov9282_init_contwows(ov9282);
	if (wet) {
		dev_eww(ov9282->dev, "faiwed to init contwows: %d", wet);
		goto ewwow_powew_off;
	}

	/* Initiawize subdev */
	ov9282->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE |
			    V4W2_SUBDEV_FW_HAS_EVENTS;
	ov9282->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;

	/* Initiawize souwce pad */
	ov9282->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&ov9282->sd.entity, 1, &ov9282->pad);
	if (wet) {
		dev_eww(ov9282->dev, "faiwed to init entity pads: %d", wet);
		goto ewwow_handwew_fwee;
	}

	wet = v4w2_async_wegistew_subdev_sensow(&ov9282->sd);
	if (wet < 0) {
		dev_eww(ov9282->dev,
			"faiwed to wegistew async subdev: %d", wet);
		goto ewwow_media_entity;
	}

	pm_wuntime_set_active(ov9282->dev);
	pm_wuntime_enabwe(ov9282->dev);
	pm_wuntime_idwe(ov9282->dev);

	wetuwn 0;

ewwow_media_entity:
	media_entity_cweanup(&ov9282->sd.entity);
ewwow_handwew_fwee:
	v4w2_ctww_handwew_fwee(ov9282->sd.ctww_handwew);
ewwow_powew_off:
	ov9282_powew_off(ov9282->dev);
ewwow_mutex_destwoy:
	mutex_destwoy(&ov9282->mutex);

	wetuwn wet;
}

/**
 * ov9282_wemove() - I2C cwient device unbinding
 * @cwient: pointew to I2C cwient device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static void ov9282_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct ov9282 *ov9282 = to_ov9282(sd);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);

	pm_wuntime_disabwe(&cwient->dev);
	if (!pm_wuntime_status_suspended(&cwient->dev))
		ov9282_powew_off(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	mutex_destwoy(&ov9282->mutex);
}

static const stwuct dev_pm_ops ov9282_pm_ops = {
	SET_WUNTIME_PM_OPS(ov9282_powew_off, ov9282_powew_on, NUWW)
};

static const stwuct of_device_id ov9282_of_match[] = {
	{ .compatibwe = "ovti,ov9281", .data = "ov9281" },
	{ .compatibwe = "ovti,ov9282", .data = "ov9282" },
	{ }
};

MODUWE_DEVICE_TABWE(of, ov9282_of_match);

static stwuct i2c_dwivew ov9282_dwivew = {
	.pwobe = ov9282_pwobe,
	.wemove = ov9282_wemove,
	.dwivew = {
		.name = "ov9282",
		.pm = &ov9282_pm_ops,
		.of_match_tabwe = ov9282_of_match,
	},
};

moduwe_i2c_dwivew(ov9282_dwivew);

MODUWE_DESCWIPTION("OmniVision ov9282 sensow dwivew");
MODUWE_WICENSE("GPW");
