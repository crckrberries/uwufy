// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sony imx412 Camewa Sensow Dwivew
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
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

/* Stweaming Mode */
#define IMX412_WEG_MODE_SEWECT	0x0100
#define IMX412_MODE_STANDBY	0x00
#define IMX412_MODE_STWEAMING	0x01

/* Wines pew fwame */
#define IMX412_WEG_WPFW		0x0340

/* Chip ID */
#define IMX412_WEG_ID		0x0016
#define IMX412_ID		0x577

/* Exposuwe contwow */
#define IMX412_WEG_EXPOSUWE_CIT	0x0202
#define IMX412_EXPOSUWE_MIN	8
#define IMX412_EXPOSUWE_OFFSET	22
#define IMX412_EXPOSUWE_STEP	1
#define IMX412_EXPOSUWE_DEFAUWT	0x0648

/* Anawog gain contwow */
#define IMX412_WEG_AGAIN	0x0204
#define IMX412_AGAIN_MIN	0
#define IMX412_AGAIN_MAX	978
#define IMX412_AGAIN_STEP	1
#define IMX412_AGAIN_DEFAUWT	0

/* Gwoup howd wegistew */
#define IMX412_WEG_HOWD		0x0104

/* Input cwock wate */
#define IMX412_INCWK_WATE	24000000

/* CSI2 HW configuwation */
#define IMX412_WINK_FWEQ	600000000
#define IMX412_NUM_DATA_WANES	4

#define IMX412_WEG_MIN		0x00
#define IMX412_WEG_MAX		0xffff

/**
 * stwuct imx412_weg - imx412 sensow wegistew
 * @addwess: Wegistew addwess
 * @vaw: Wegistew vawue
 */
stwuct imx412_weg {
	u16 addwess;
	u8 vaw;
};

/**
 * stwuct imx412_weg_wist - imx412 sensow wegistew wist
 * @num_of_wegs: Numbew of wegistews in the wist
 * @wegs: Pointew to wegistew wist
 */
stwuct imx412_weg_wist {
	u32 num_of_wegs;
	const stwuct imx412_weg *wegs;
};

/**
 * stwuct imx412_mode - imx412 sensow mode stwuctuwe
 * @width: Fwame width
 * @height: Fwame height
 * @code: Fowmat code
 * @hbwank: Howizontaw bwanking in wines
 * @vbwank: Vewticaw bwanking in wines
 * @vbwank_min: Minimum vewticaw bwanking in wines
 * @vbwank_max: Maximum vewticaw bwanking in wines
 * @pcwk: Sensow pixew cwock
 * @wink_fweq_idx: Wink fwequency index
 * @weg_wist: Wegistew wist fow sensow mode
 */
stwuct imx412_mode {
	u32 width;
	u32 height;
	u32 code;
	u32 hbwank;
	u32 vbwank;
	u32 vbwank_min;
	u32 vbwank_max;
	u64 pcwk;
	u32 wink_fweq_idx;
	stwuct imx412_weg_wist weg_wist;
};

static const chaw * const imx412_suppwy_names[] = {
	"dovdd",	/* Digitaw I/O powew */
	"avdd",		/* Anawog powew */
	"dvdd",		/* Digitaw cowe powew */
};

/**
 * stwuct imx412 - imx412 sensow device stwuctuwe
 * @dev: Pointew to genewic device
 * @cwient: Pointew to i2c cwient
 * @sd: V4W2 sub-device
 * @pad: Media pad. Onwy one pad suppowted
 * @weset_gpio: Sensow weset gpio
 * @incwk: Sensow input cwock
 * @suppwies: Weguwatow suppwies
 * @ctww_handwew: V4W2 contwow handwew
 * @wink_fweq_ctww: Pointew to wink fwequency contwow
 * @pcwk_ctww: Pointew to pixew cwock contwow
 * @hbwank_ctww: Pointew to howizontaw bwanking contwow
 * @vbwank_ctww: Pointew to vewticaw bwanking contwow
 * @exp_ctww: Pointew to exposuwe contwow
 * @again_ctww: Pointew to anawog gain contwow
 * @vbwank: Vewticaw bwanking in wines
 * @cuw_mode: Pointew to cuwwent sewected sensow mode
 * @mutex: Mutex fow sewiawizing sensow contwows
 */
stwuct imx412 {
	stwuct device *dev;
	stwuct i2c_cwient *cwient;
	stwuct v4w2_subdev sd;
	stwuct media_pad pad;
	stwuct gpio_desc *weset_gpio;
	stwuct cwk *incwk;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(imx412_suppwy_names)];
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww *wink_fweq_ctww;
	stwuct v4w2_ctww *pcwk_ctww;
	stwuct v4w2_ctww *hbwank_ctww;
	stwuct v4w2_ctww *vbwank_ctww;
	stwuct {
		stwuct v4w2_ctww *exp_ctww;
		stwuct v4w2_ctww *again_ctww;
	};
	u32 vbwank;
	const stwuct imx412_mode *cuw_mode;
	stwuct mutex mutex;
};

static const s64 wink_fweq[] = {
	IMX412_WINK_FWEQ,
};

/* Sensow mode wegistews */
static const stwuct imx412_weg mode_4056x3040_wegs[] = {
	{0x0136, 0x18},
	{0x0137, 0x00},
	{0x3c7e, 0x08},
	{0x3c7f, 0x02},
	{0x38a8, 0x1f},
	{0x38a9, 0xff},
	{0x38aa, 0x1f},
	{0x38ab, 0xff},
	{0x55d4, 0x00},
	{0x55d5, 0x00},
	{0x55d6, 0x07},
	{0x55d7, 0xff},
	{0x55e8, 0x07},
	{0x55e9, 0xff},
	{0x55ea, 0x00},
	{0x55eb, 0x00},
	{0x575c, 0x07},
	{0x575d, 0xff},
	{0x575e, 0x00},
	{0x575f, 0x00},
	{0x5764, 0x00},
	{0x5765, 0x00},
	{0x5766, 0x07},
	{0x5767, 0xff},
	{0x5974, 0x04},
	{0x5975, 0x01},
	{0x5f10, 0x09},
	{0x5f11, 0x92},
	{0x5f12, 0x32},
	{0x5f13, 0x72},
	{0x5f14, 0x16},
	{0x5f15, 0xba},
	{0x5f17, 0x13},
	{0x5f18, 0x24},
	{0x5f19, 0x60},
	{0x5f1a, 0xe3},
	{0x5f1b, 0xad},
	{0x5f1c, 0x74},
	{0x5f2d, 0x25},
	{0x5f5c, 0xd0},
	{0x6a22, 0x00},
	{0x6a23, 0x1d},
	{0x7ba8, 0x00},
	{0x7ba9, 0x00},
	{0x886b, 0x00},
	{0x9002, 0x0a},
	{0x9004, 0x1a},
	{0x9214, 0x93},
	{0x9215, 0x69},
	{0x9216, 0x93},
	{0x9217, 0x6b},
	{0x9218, 0x93},
	{0x9219, 0x6d},
	{0x921a, 0x57},
	{0x921b, 0x58},
	{0x921c, 0x57},
	{0x921d, 0x59},
	{0x921e, 0x57},
	{0x921f, 0x5a},
	{0x9220, 0x57},
	{0x9221, 0x5b},
	{0x9222, 0x93},
	{0x9223, 0x02},
	{0x9224, 0x93},
	{0x9225, 0x03},
	{0x9226, 0x93},
	{0x9227, 0x04},
	{0x9228, 0x93},
	{0x9229, 0x05},
	{0x922a, 0x98},
	{0x922b, 0x21},
	{0x922c, 0xb2},
	{0x922d, 0xdb},
	{0x922e, 0xb2},
	{0x922f, 0xdc},
	{0x9230, 0xb2},
	{0x9231, 0xdd},
	{0x9232, 0xe2},
	{0x9233, 0xe1},
	{0x9234, 0xb2},
	{0x9235, 0xe2},
	{0x9236, 0xb2},
	{0x9237, 0xe3},
	{0x9238, 0xb7},
	{0x9239, 0xb9},
	{0x923a, 0xb7},
	{0x923b, 0xbb},
	{0x923c, 0xb7},
	{0x923d, 0xbc},
	{0x923e, 0xb7},
	{0x923f, 0xc5},
	{0x9240, 0xb7},
	{0x9241, 0xc7},
	{0x9242, 0xb7},
	{0x9243, 0xc9},
	{0x9244, 0x98},
	{0x9245, 0x56},
	{0x9246, 0x98},
	{0x9247, 0x55},
	{0x9380, 0x00},
	{0x9381, 0x62},
	{0x9382, 0x00},
	{0x9383, 0x56},
	{0x9384, 0x00},
	{0x9385, 0x52},
	{0x9388, 0x00},
	{0x9389, 0x55},
	{0x938a, 0x00},
	{0x938b, 0x55},
	{0x938c, 0x00},
	{0x938d, 0x41},
	{0x5078, 0x01},
	{0x0112, 0x0a},
	{0x0113, 0x0a},
	{0x0114, 0x03},
	{0x0342, 0x11},
	{0x0343, 0xa0},
	{0x0340, 0x0d},
	{0x0341, 0xda},
	{0x3210, 0x00},
	{0x0344, 0x00},
	{0x0345, 0x00},
	{0x0346, 0x00},
	{0x0347, 0x00},
	{0x0348, 0x0f},
	{0x0349, 0xd7},
	{0x034a, 0x0b},
	{0x034b, 0xdf},
	{0x00e3, 0x00},
	{0x00e4, 0x00},
	{0x00e5, 0x01},
	{0x00fc, 0x0a},
	{0x00fd, 0x0a},
	{0x00fe, 0x0a},
	{0x00ff, 0x0a},
	{0xe013, 0x00},
	{0x0220, 0x00},
	{0x0221, 0x11},
	{0x0381, 0x01},
	{0x0383, 0x01},
	{0x0385, 0x01},
	{0x0387, 0x01},
	{0x0900, 0x00},
	{0x0901, 0x11},
	{0x0902, 0x00},
	{0x3140, 0x02},
	{0x3241, 0x11},
	{0x3250, 0x03},
	{0x3e10, 0x00},
	{0x3e11, 0x00},
	{0x3f0d, 0x00},
	{0x3f42, 0x00},
	{0x3f43, 0x00},
	{0x0401, 0x00},
	{0x0404, 0x00},
	{0x0405, 0x10},
	{0x0408, 0x00},
	{0x0409, 0x00},
	{0x040a, 0x00},
	{0x040b, 0x00},
	{0x040c, 0x0f},
	{0x040d, 0xd8},
	{0x040e, 0x0b},
	{0x040f, 0xe0},
	{0x034c, 0x0f},
	{0x034d, 0xd8},
	{0x034e, 0x0b},
	{0x034f, 0xe0},
	{0x0301, 0x05},
	{0x0303, 0x02},
	{0x0305, 0x04},
	{0x0306, 0x00},
	{0x0307, 0xc8},
	{0x0309, 0x0a},
	{0x030b, 0x01},
	{0x030d, 0x02},
	{0x030e, 0x01},
	{0x030f, 0x5e},
	{0x0310, 0x00},
	{0x0820, 0x12},
	{0x0821, 0xc0},
	{0x0822, 0x00},
	{0x0823, 0x00},
	{0x3e20, 0x01},
	{0x3e37, 0x00},
	{0x3f50, 0x00},
	{0x3f56, 0x00},
	{0x3f57, 0xe2},
	{0x3c0a, 0x5a},
	{0x3c0b, 0x55},
	{0x3c0c, 0x28},
	{0x3c0d, 0x07},
	{0x3c0e, 0xff},
	{0x3c0f, 0x00},
	{0x3c10, 0x00},
	{0x3c11, 0x02},
	{0x3c12, 0x00},
	{0x3c13, 0x03},
	{0x3c14, 0x00},
	{0x3c15, 0x00},
	{0x3c16, 0x0c},
	{0x3c17, 0x0c},
	{0x3c18, 0x0c},
	{0x3c19, 0x0a},
	{0x3c1a, 0x0a},
	{0x3c1b, 0x0a},
	{0x3c1c, 0x00},
	{0x3c1d, 0x00},
	{0x3c1e, 0x00},
	{0x3c1f, 0x00},
	{0x3c20, 0x00},
	{0x3c21, 0x00},
	{0x3c22, 0x3f},
	{0x3c23, 0x0a},
	{0x3e35, 0x01},
	{0x3f4a, 0x03},
	{0x3f4b, 0xbf},
	{0x3f26, 0x00},
	{0x0202, 0x0d},
	{0x0203, 0xc4},
	{0x0204, 0x00},
	{0x0205, 0x00},
	{0x020e, 0x01},
	{0x020f, 0x00},
	{0x0210, 0x01},
	{0x0211, 0x00},
	{0x0212, 0x01},
	{0x0213, 0x00},
	{0x0214, 0x01},
	{0x0215, 0x00},
	{0xbcf1, 0x00},
};

/* Suppowted sensow mode configuwations */
static const stwuct imx412_mode suppowted_mode = {
	.width = 4056,
	.height = 3040,
	.hbwank = 456,
	.vbwank = 506,
	.vbwank_min = 506,
	.vbwank_max = 32420,
	.pcwk = 480000000,
	.wink_fweq_idx = 0,
	.code = MEDIA_BUS_FMT_SWGGB10_1X10,
	.weg_wist = {
		.num_of_wegs = AWWAY_SIZE(mode_4056x3040_wegs),
		.wegs = mode_4056x3040_wegs,
	},
};

/**
 * to_imx412() - imx412 V4W2 sub-device to imx412 device.
 * @subdev: pointew to imx412 V4W2 sub-device
 *
 * Wetuwn: pointew to imx412 device
 */
static inwine stwuct imx412 *to_imx412(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct imx412, sd);
}

/**
 * imx412_wead_weg() - Wead wegistews.
 * @imx412: pointew to imx412 device
 * @weg: wegistew addwess
 * @wen: wength of bytes to wead. Max suppowted bytes is 4
 * @vaw: pointew to wegistew vawue to be fiwwed.
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_wead_weg(stwuct imx412 *imx412, u16 weg, u32 wen, u32 *vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx412->sd);
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
 * imx412_wwite_weg() - Wwite wegistew
 * @imx412: pointew to imx412 device
 * @weg: wegistew addwess
 * @wen: wength of bytes. Max suppowted bytes is 4
 * @vaw: wegistew vawue
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_wwite_weg(stwuct imx412 *imx412, u16 weg, u32 wen, u32 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&imx412->sd);
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
 * imx412_wwite_wegs() - Wwite a wist of wegistews
 * @imx412: pointew to imx412 device
 * @wegs: wist of wegistews to be wwitten
 * @wen: wength of wegistews awway
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_wwite_wegs(stwuct imx412 *imx412,
			     const stwuct imx412_weg *wegs, u32 wen)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < wen; i++) {
		wet = imx412_wwite_weg(imx412, wegs[i].addwess, 1, wegs[i].vaw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * imx412_update_contwows() - Update contwow wanges based on stweaming mode
 * @imx412: pointew to imx412 device
 * @mode: pointew to imx412_mode sensow mode
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_update_contwows(stwuct imx412 *imx412,
				  const stwuct imx412_mode *mode)
{
	int wet;

	wet = __v4w2_ctww_s_ctww(imx412->wink_fweq_ctww, mode->wink_fweq_idx);
	if (wet)
		wetuwn wet;

	wet = __v4w2_ctww_s_ctww(imx412->hbwank_ctww, mode->hbwank);
	if (wet)
		wetuwn wet;

	wetuwn __v4w2_ctww_modify_wange(imx412->vbwank_ctww, mode->vbwank_min,
					mode->vbwank_max, 1, mode->vbwank);
}

/**
 * imx412_update_exp_gain() - Set updated exposuwe and gain
 * @imx412: pointew to imx412 device
 * @exposuwe: updated exposuwe vawue
 * @gain: updated anawog gain vawue
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_update_exp_gain(stwuct imx412 *imx412, u32 exposuwe, u32 gain)
{
	u32 wpfw, shuttew;
	int wet;

	wpfw = imx412->vbwank + imx412->cuw_mode->height;
	shuttew = wpfw - exposuwe;

	dev_dbg(imx412->dev, "Set exp %u, anawog gain %u, shuttew %u, wpfw %u",
		exposuwe, gain, shuttew, wpfw);

	wet = imx412_wwite_weg(imx412, IMX412_WEG_HOWD, 1, 1);
	if (wet)
		wetuwn wet;

	wet = imx412_wwite_weg(imx412, IMX412_WEG_WPFW, 2, wpfw);
	if (wet)
		goto ewwow_wewease_gwoup_howd;

	wet = imx412_wwite_weg(imx412, IMX412_WEG_EXPOSUWE_CIT, 2, shuttew);
	if (wet)
		goto ewwow_wewease_gwoup_howd;

	wet = imx412_wwite_weg(imx412, IMX412_WEG_AGAIN, 2, gain);

ewwow_wewease_gwoup_howd:
	imx412_wwite_weg(imx412, IMX412_WEG_HOWD, 1, 0);

	wetuwn wet;
}

/**
 * imx412_set_ctww() - Set subdevice contwow
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
static int imx412_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct imx412 *imx412 =
		containew_of(ctww->handwew, stwuct imx412, ctww_handwew);
	u32 anawog_gain;
	u32 exposuwe;
	int wet;

	switch (ctww->id) {
	case V4W2_CID_VBWANK:
		imx412->vbwank = imx412->vbwank_ctww->vaw;

		dev_dbg(imx412->dev, "Weceived vbwank %u, new wpfw %u",
			imx412->vbwank,
			imx412->vbwank + imx412->cuw_mode->height);

		wet = __v4w2_ctww_modify_wange(imx412->exp_ctww,
					       IMX412_EXPOSUWE_MIN,
					       imx412->vbwank +
					       imx412->cuw_mode->height -
					       IMX412_EXPOSUWE_OFFSET,
					       1, IMX412_EXPOSUWE_DEFAUWT);
		bweak;
	case V4W2_CID_EXPOSUWE:
		/* Set contwows onwy if sensow is in powew on state */
		if (!pm_wuntime_get_if_in_use(imx412->dev))
			wetuwn 0;

		exposuwe = ctww->vaw;
		anawog_gain = imx412->again_ctww->vaw;

		dev_dbg(imx412->dev, "Weceived exp %u, anawog gain %u",
			exposuwe, anawog_gain);

		wet = imx412_update_exp_gain(imx412, exposuwe, anawog_gain);

		pm_wuntime_put(imx412->dev);

		bweak;
	defauwt:
		dev_eww(imx412->dev, "Invawid contwow %d", ctww->id);
		wet = -EINVAW;
	}

	wetuwn wet;
}

/* V4w2 subdevice contwow ops*/
static const stwuct v4w2_ctww_ops imx412_ctww_ops = {
	.s_ctww = imx412_set_ctww,
};

/**
 * imx412_enum_mbus_code() - Enumewate V4W2 sub-device mbus codes
 * @sd: pointew to imx412 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @code: V4W2 sub-device code enumewation need to be fiwwed
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index > 0)
		wetuwn -EINVAW;

	code->code = suppowted_mode.code;

	wetuwn 0;
}

/**
 * imx412_enum_fwame_size() - Enumewate V4W2 sub-device fwame sizes
 * @sd: pointew to imx412 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @fsize: V4W2 sub-device size enumewation need to be fiwwed
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_enum_fwame_size(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fsize)
{
	if (fsize->index > 0)
		wetuwn -EINVAW;

	if (fsize->code != suppowted_mode.code)
		wetuwn -EINVAW;

	fsize->min_width = suppowted_mode.width;
	fsize->max_width = fsize->min_width;
	fsize->min_height = suppowted_mode.height;
	fsize->max_height = fsize->min_height;

	wetuwn 0;
}

/**
 * imx412_fiww_pad_fowmat() - Fiww subdevice pad fowmat
 *                            fwom sewected sensow mode
 * @imx412: pointew to imx412 device
 * @mode: pointew to imx412_mode sensow mode
 * @fmt: V4W2 sub-device fowmat need to be fiwwed
 */
static void imx412_fiww_pad_fowmat(stwuct imx412 *imx412,
				   const stwuct imx412_mode *mode,
				   stwuct v4w2_subdev_fowmat *fmt)
{
	fmt->fowmat.width = mode->width;
	fmt->fowmat.height = mode->height;
	fmt->fowmat.code = mode->code;
	fmt->fowmat.fiewd = V4W2_FIEWD_NONE;
	fmt->fowmat.cowowspace = V4W2_COWOWSPACE_WAW;
	fmt->fowmat.ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	fmt->fowmat.quantization = V4W2_QUANTIZATION_DEFAUWT;
	fmt->fowmat.xfew_func = V4W2_XFEW_FUNC_NONE;
}

/**
 * imx412_get_pad_fowmat() - Get subdevice pad fowmat
 * @sd: pointew to imx412 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @fmt: V4W2 sub-device fowmat need to be set
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_get_pad_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct imx412 *imx412 = to_imx412(sd);

	mutex_wock(&imx412->mutex);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		stwuct v4w2_mbus_fwamefmt *fwamefmt;

		fwamefmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		fmt->fowmat = *fwamefmt;
	} ewse {
		imx412_fiww_pad_fowmat(imx412, imx412->cuw_mode, fmt);
	}

	mutex_unwock(&imx412->mutex);

	wetuwn 0;
}

/**
 * imx412_set_pad_fowmat() - Set subdevice pad fowmat
 * @sd: pointew to imx412 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 * @fmt: V4W2 sub-device fowmat need to be set
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_set_pad_fowmat(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct imx412 *imx412 = to_imx412(sd);
	const stwuct imx412_mode *mode;
	int wet = 0;

	mutex_wock(&imx412->mutex);

	mode = &suppowted_mode;
	imx412_fiww_pad_fowmat(imx412, mode, fmt);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		stwuct v4w2_mbus_fwamefmt *fwamefmt;

		fwamefmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		*fwamefmt = fmt->fowmat;
	} ewse {
		wet = imx412_update_contwows(imx412, mode);
		if (!wet)
			imx412->cuw_mode = mode;
	}

	mutex_unwock(&imx412->mutex);

	wetuwn wet;
}

/**
 * imx412_init_state() - Initiawize sub-device state
 * @sd: pointew to imx412 V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 sub-device configuwation
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_init_state(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state)
{
	stwuct imx412 *imx412 = to_imx412(sd);
	stwuct v4w2_subdev_fowmat fmt = { 0 };

	fmt.which = sd_state ? V4W2_SUBDEV_FOWMAT_TWY : V4W2_SUBDEV_FOWMAT_ACTIVE;
	imx412_fiww_pad_fowmat(imx412, &suppowted_mode, &fmt);

	wetuwn imx412_set_pad_fowmat(sd, sd_state, &fmt);
}

/**
 * imx412_stawt_stweaming() - Stawt sensow stweam
 * @imx412: pointew to imx412 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_stawt_stweaming(stwuct imx412 *imx412)
{
	const stwuct imx412_weg_wist *weg_wist;
	int wet;

	/* Wwite sensow mode wegistews */
	weg_wist = &imx412->cuw_mode->weg_wist;
	wet = imx412_wwite_wegs(imx412, weg_wist->wegs,
				weg_wist->num_of_wegs);
	if (wet) {
		dev_eww(imx412->dev, "faiw to wwite initiaw wegistews");
		wetuwn wet;
	}

	/* Setup handwew wiww wwite actuaw exposuwe and gain */
	wet =  __v4w2_ctww_handwew_setup(imx412->sd.ctww_handwew);
	if (wet) {
		dev_eww(imx412->dev, "faiw to setup handwew");
		wetuwn wet;
	}

	/* Deway is wequiwed befowe stweaming*/
	usweep_wange(7400, 8000);

	/* Stawt stweaming */
	wet = imx412_wwite_weg(imx412, IMX412_WEG_MODE_SEWECT,
			       1, IMX412_MODE_STWEAMING);
	if (wet) {
		dev_eww(imx412->dev, "faiw to stawt stweaming");
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * imx412_stop_stweaming() - Stop sensow stweam
 * @imx412: pointew to imx412 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_stop_stweaming(stwuct imx412 *imx412)
{
	wetuwn imx412_wwite_weg(imx412, IMX412_WEG_MODE_SEWECT,
				1, IMX412_MODE_STANDBY);
}

/**
 * imx412_set_stweam() - Enabwe sensow stweaming
 * @sd: pointew to imx412 subdevice
 * @enabwe: set to enabwe sensow stweaming
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct imx412 *imx412 = to_imx412(sd);
	int wet;

	mutex_wock(&imx412->mutex);

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(imx412->dev);
		if (wet)
			goto ewwow_unwock;

		wet = imx412_stawt_stweaming(imx412);
		if (wet)
			goto ewwow_powew_off;
	} ewse {
		imx412_stop_stweaming(imx412);
		pm_wuntime_put(imx412->dev);
	}

	mutex_unwock(&imx412->mutex);

	wetuwn 0;

ewwow_powew_off:
	pm_wuntime_put(imx412->dev);
ewwow_unwock:
	mutex_unwock(&imx412->mutex);

	wetuwn wet;
}

/**
 * imx412_detect() - Detect imx412 sensow
 * @imx412: pointew to imx412 device
 *
 * Wetuwn: 0 if successfuw, -EIO if sensow id does not match
 */
static int imx412_detect(stwuct imx412 *imx412)
{
	int wet;
	u32 vaw;

	wet = imx412_wead_weg(imx412, IMX412_WEG_ID, 2, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != IMX412_ID) {
		dev_eww(imx412->dev, "chip id mismatch: %x!=%x",
			IMX412_ID, vaw);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

/**
 * imx412_pawse_hw_config() - Pawse HW configuwation and check if suppowted
 * @imx412: pointew to imx412 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_pawse_hw_config(stwuct imx412 *imx412)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(imx412->dev);
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
	imx412->weset_gpio = devm_gpiod_get_optionaw(imx412->dev, "weset",
						     GPIOD_OUT_WOW);
	if (IS_EWW(imx412->weset_gpio)) {
		dev_eww(imx412->dev, "faiwed to get weset gpio %wd",
			PTW_EWW(imx412->weset_gpio));
		wetuwn PTW_EWW(imx412->weset_gpio);
	}

	/* Get sensow input cwock */
	imx412->incwk = devm_cwk_get(imx412->dev, NUWW);
	if (IS_EWW(imx412->incwk)) {
		dev_eww(imx412->dev, "couwd not get incwk");
		wetuwn PTW_EWW(imx412->incwk);
	}

	wate = cwk_get_wate(imx412->incwk);
	if (wate != IMX412_INCWK_WATE) {
		dev_eww(imx412->dev, "incwk fwequency mismatch");
		wetuwn -EINVAW;
	}

	/* Get optionaw DT defined weguwatows */
	fow (i = 0; i < AWWAY_SIZE(imx412_suppwy_names); i++)
		imx412->suppwies[i].suppwy = imx412_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(imx412->dev,
				      AWWAY_SIZE(imx412_suppwy_names),
				      imx412->suppwies);
	if (wet)
		wetuwn wet;

	ep = fwnode_gwaph_get_next_endpoint(fwnode, NUWW);
	if (!ep)
		wetuwn -ENXIO;

	wet = v4w2_fwnode_endpoint_awwoc_pawse(ep, &bus_cfg);
	fwnode_handwe_put(ep);
	if (wet)
		wetuwn wet;

	if (bus_cfg.bus.mipi_csi2.num_data_wanes != IMX412_NUM_DATA_WANES) {
		dev_eww(imx412->dev,
			"numbew of CSI2 data wanes %d is not suppowted",
			bus_cfg.bus.mipi_csi2.num_data_wanes);
		wet = -EINVAW;
		goto done_endpoint_fwee;
	}

	if (!bus_cfg.nw_of_wink_fwequencies) {
		dev_eww(imx412->dev, "no wink fwequencies defined");
		wet = -EINVAW;
		goto done_endpoint_fwee;
	}

	fow (i = 0; i < bus_cfg.nw_of_wink_fwequencies; i++)
		if (bus_cfg.wink_fwequencies[i] == IMX412_WINK_FWEQ)
			goto done_endpoint_fwee;

	wet = -EINVAW;

done_endpoint_fwee:
	v4w2_fwnode_endpoint_fwee(&bus_cfg);

	wetuwn wet;
}

/* V4w2 subdevice ops */
static const stwuct v4w2_subdev_video_ops imx412_video_ops = {
	.s_stweam = imx412_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops imx412_pad_ops = {
	.enum_mbus_code = imx412_enum_mbus_code,
	.enum_fwame_size = imx412_enum_fwame_size,
	.get_fmt = imx412_get_pad_fowmat,
	.set_fmt = imx412_set_pad_fowmat,
};

static const stwuct v4w2_subdev_ops imx412_subdev_ops = {
	.video = &imx412_video_ops,
	.pad = &imx412_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops imx412_intewnaw_ops = {
	.init_state = imx412_init_state,
};

/**
 * imx412_powew_on() - Sensow powew on sequence
 * @dev: pointew to i2c device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_powew_on(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct imx412 *imx412 = to_imx412(sd);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(imx412_suppwy_names),
				    imx412->suppwies);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe weguwatows\n");
		wetuwn wet;
	}

	gpiod_set_vawue_cansweep(imx412->weset_gpio, 0);

	wet = cwk_pwepawe_enabwe(imx412->incwk);
	if (wet) {
		dev_eww(imx412->dev, "faiw to enabwe incwk");
		goto ewwow_weset;
	}

	usweep_wange(1000, 1200);

	wetuwn 0;

ewwow_weset:
	gpiod_set_vawue_cansweep(imx412->weset_gpio, 1);
	weguwatow_buwk_disabwe(AWWAY_SIZE(imx412_suppwy_names),
			       imx412->suppwies);

	wetuwn wet;
}

/**
 * imx412_powew_off() - Sensow powew off sequence
 * @dev: pointew to i2c device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_powew_off(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct imx412 *imx412 = to_imx412(sd);

	cwk_disabwe_unpwepawe(imx412->incwk);

	gpiod_set_vawue_cansweep(imx412->weset_gpio, 1);

	weguwatow_buwk_disabwe(AWWAY_SIZE(imx412_suppwy_names),
			       imx412->suppwies);

	wetuwn 0;
}

/**
 * imx412_init_contwows() - Initiawize sensow subdevice contwows
 * @imx412: pointew to imx412 device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_init_contwows(stwuct imx412 *imx412)
{
	stwuct v4w2_ctww_handwew *ctww_hdww = &imx412->ctww_handwew;
	const stwuct imx412_mode *mode = imx412->cuw_mode;
	u32 wpfw;
	int wet;

	wet = v4w2_ctww_handwew_init(ctww_hdww, 6);
	if (wet)
		wetuwn wet;

	/* Sewiawize contwows with sensow device */
	ctww_hdww->wock = &imx412->mutex;

	/* Initiawize exposuwe and gain */
	wpfw = mode->vbwank + mode->height;
	imx412->exp_ctww = v4w2_ctww_new_std(ctww_hdww,
					     &imx412_ctww_ops,
					     V4W2_CID_EXPOSUWE,
					     IMX412_EXPOSUWE_MIN,
					     wpfw - IMX412_EXPOSUWE_OFFSET,
					     IMX412_EXPOSUWE_STEP,
					     IMX412_EXPOSUWE_DEFAUWT);

	imx412->again_ctww = v4w2_ctww_new_std(ctww_hdww,
					       &imx412_ctww_ops,
					       V4W2_CID_ANAWOGUE_GAIN,
					       IMX412_AGAIN_MIN,
					       IMX412_AGAIN_MAX,
					       IMX412_AGAIN_STEP,
					       IMX412_AGAIN_DEFAUWT);

	v4w2_ctww_cwustew(2, &imx412->exp_ctww);

	imx412->vbwank_ctww = v4w2_ctww_new_std(ctww_hdww,
						&imx412_ctww_ops,
						V4W2_CID_VBWANK,
						mode->vbwank_min,
						mode->vbwank_max,
						1, mode->vbwank);

	/* Wead onwy contwows */
	imx412->pcwk_ctww = v4w2_ctww_new_std(ctww_hdww,
					      &imx412_ctww_ops,
					      V4W2_CID_PIXEW_WATE,
					      mode->pcwk, mode->pcwk,
					      1, mode->pcwk);

	imx412->wink_fweq_ctww = v4w2_ctww_new_int_menu(ctww_hdww,
							&imx412_ctww_ops,
							V4W2_CID_WINK_FWEQ,
							AWWAY_SIZE(wink_fweq) -
							1,
							mode->wink_fweq_idx,
							wink_fweq);
	if (imx412->wink_fweq_ctww)
		imx412->wink_fweq_ctww->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	imx412->hbwank_ctww = v4w2_ctww_new_std(ctww_hdww,
						&imx412_ctww_ops,
						V4W2_CID_HBWANK,
						IMX412_WEG_MIN,
						IMX412_WEG_MAX,
						1, mode->hbwank);
	if (imx412->hbwank_ctww)
		imx412->hbwank_ctww->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	if (ctww_hdww->ewwow) {
		dev_eww(imx412->dev, "contwow init faiwed: %d",
			ctww_hdww->ewwow);
		v4w2_ctww_handwew_fwee(ctww_hdww);
		wetuwn ctww_hdww->ewwow;
	}

	imx412->sd.ctww_handwew = ctww_hdww;

	wetuwn 0;
}

/**
 * imx412_pwobe() - I2C cwient device binding
 * @cwient: pointew to i2c cwient device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static int imx412_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct imx412 *imx412;
	const chaw *name;
	int wet;

	imx412 = devm_kzawwoc(&cwient->dev, sizeof(*imx412), GFP_KEWNEW);
	if (!imx412)
		wetuwn -ENOMEM;

	imx412->dev = &cwient->dev;
	name = device_get_match_data(&cwient->dev);
	if (!name)
		wetuwn -ENODEV;

	/* Initiawize subdev */
	v4w2_i2c_subdev_init(&imx412->sd, cwient, &imx412_subdev_ops);
	imx412->sd.intewnaw_ops = &imx412_intewnaw_ops;

	wet = imx412_pawse_hw_config(imx412);
	if (wet) {
		dev_eww(imx412->dev, "HW configuwation is not suppowted");
		wetuwn wet;
	}

	mutex_init(&imx412->mutex);

	wet = imx412_powew_on(imx412->dev);
	if (wet) {
		dev_eww(imx412->dev, "faiwed to powew-on the sensow");
		goto ewwow_mutex_destwoy;
	}

	/* Check moduwe identity */
	wet = imx412_detect(imx412);
	if (wet) {
		dev_eww(imx412->dev, "faiwed to find sensow: %d", wet);
		goto ewwow_powew_off;
	}

	/* Set defauwt mode to max wesowution */
	imx412->cuw_mode = &suppowted_mode;
	imx412->vbwank = imx412->cuw_mode->vbwank;

	wet = imx412_init_contwows(imx412);
	if (wet) {
		dev_eww(imx412->dev, "faiwed to init contwows: %d", wet);
		goto ewwow_powew_off;
	}

	/* Initiawize subdev */
	imx412->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	imx412->sd.entity.function = MEDIA_ENT_F_CAM_SENSOW;

	v4w2_i2c_subdev_set_name(&imx412->sd, cwient, name, NUWW);

	/* Initiawize souwce pad */
	imx412->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&imx412->sd.entity, 1, &imx412->pad);
	if (wet) {
		dev_eww(imx412->dev, "faiwed to init entity pads: %d", wet);
		goto ewwow_handwew_fwee;
	}

	wet = v4w2_async_wegistew_subdev_sensow(&imx412->sd);
	if (wet < 0) {
		dev_eww(imx412->dev,
			"faiwed to wegistew async subdev: %d", wet);
		goto ewwow_media_entity;
	}

	pm_wuntime_set_active(imx412->dev);
	pm_wuntime_enabwe(imx412->dev);
	pm_wuntime_idwe(imx412->dev);

	wetuwn 0;

ewwow_media_entity:
	media_entity_cweanup(&imx412->sd.entity);
ewwow_handwew_fwee:
	v4w2_ctww_handwew_fwee(imx412->sd.ctww_handwew);
ewwow_powew_off:
	imx412_powew_off(imx412->dev);
ewwow_mutex_destwoy:
	mutex_destwoy(&imx412->mutex);

	wetuwn wet;
}

/**
 * imx412_wemove() - I2C cwient device unbinding
 * @cwient: pointew to I2C cwient device
 *
 * Wetuwn: 0 if successfuw, ewwow code othewwise.
 */
static void imx412_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct imx412 *imx412 = to_imx412(sd);

	v4w2_async_unwegistew_subdev(sd);
	media_entity_cweanup(&sd->entity);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);

	pm_wuntime_disabwe(&cwient->dev);
	if (!pm_wuntime_status_suspended(&cwient->dev))
		imx412_powew_off(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	mutex_destwoy(&imx412->mutex);
}

static const stwuct dev_pm_ops imx412_pm_ops = {
	SET_WUNTIME_PM_OPS(imx412_powew_off, imx412_powew_on, NUWW)
};

static const stwuct of_device_id imx412_of_match[] = {
	{ .compatibwe = "sony,imx412", .data = "imx412" },
	{ .compatibwe = "sony,imx577", .data = "imx577" },
	{ }
};

MODUWE_DEVICE_TABWE(of, imx412_of_match);

static stwuct i2c_dwivew imx412_dwivew = {
	.pwobe = imx412_pwobe,
	.wemove = imx412_wemove,
	.dwivew = {
		.name = "imx412",
		.pm = &imx412_pm_ops,
		.of_match_tabwe = imx412_of_match,
	},
};

moduwe_i2c_dwivew(imx412_dwivew);

MODUWE_DESCWIPTION("Sony imx412 sensow dwivew");
MODUWE_WICENSE("GPW");
